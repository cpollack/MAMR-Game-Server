#include "Monster.h"
#include "MapGroup.h"

DWORD NEXT_MONSTERID = _IDMSK_MONSTER + 1;

DWORD GetNext_MonsterID() { 
	return NEXT_MONSTERID++;
}

MYHEAP_IMPLEMENTATION(CMonster, s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMonster::CMonster()
{
	SetObjType(OBJ_MONSTER);
	pType = NULL;
	ID = ID_NONE;
	//m_pBattleSystem	= NULL;
	pData = NULL;

	m_tFootPrint = 0;
	m_posFootPrint.x = 0;
	m_posFootPrint.y = 0;

	m_link.Init(this);

	m_bDecRole = false;

	m_nKillNum = 0;
	m_nKillNum4Potential = 0;
	m_nKillNum4RelationShip = 0;
}

//////////////////////////////////////////////////////////////////////
CMonster::~CMonster()
{
	if (pData) SAFE_RELEASE(pData);
	//{
		//if (IsSynPet())
		//	MapManager()->RecyclePetID(GetID());
		//else if (IsCallPet())
		//	MapManager()->RecycleCallPetID(GetID());

		//if (m_pData->GetInt(PETDATA_LIFE) > 0)		// flag to die
		//	SaveInfo();
		//m_pData->Release();
	//}

	//if (m_pBattleSystem)
	//{
	//	delete m_pBattleSystem;
	//	m_pBattleSystem	= NULL;
	//}


	SAFE_RELEASE(m_setStatus);
}

//////////////////////////////////////////////////////////////////////
bool CMonster::Create(PROCESS_ID idProcess, const ST_CREATENEWMONSTER* pInfo, LPCTSTR pszName/*=NULL*/)
{
	m_idProcess = idProcess;

	ID = pInfo->id;
	pData = CMonsterData::CreateNew();
	IF_OK(pData)
	{
		IF_OK(pData->Create(ID))
		{
			pData->SetID(GetNext_MonsterID());
			pType = MonsterType()->GetObj(ID);
			ID = pData->GetID();
			
			//Data loaded in Create() modify it here

			if (pInfo->iLevel == 0) {
				Create_LevelBase();
			}
			else {
				if (pInfo->iLevel == 1) {
					Create_LevelOne();
				}
				else {
					pData->SetLevel(pInfo->iLevel);
					Create_LevelAny();
				}
			}
		}
	}


	//m_nDir = ::RandGet(8);
	//m_pMap = MapManager()->GetGameMap(pInfo->idMap);
	//m_nPosX = pInfo->usPosX;
	//m_nPosY = pInfo->usPosY;
	//	m_dwStatus		= STATUS_NORMAL;
	//m_i64Effect = KEEPEFFECT_NORMAL;
	//m_nPose = POSE_STAND;
	//m_idGen = pInfo->idData;

	LifeCurrent = pData->GetLife();

	int monsterClass = pData->GetClass();
	if (IsSuper() || IsUnevo()) {
		element = (ELEMENT)(monsterClass % 10000 / 1000);
	}
	else {
		element = (ELEMENT)(monsterClass / 10000);
	}

	//m_nCurrMana = m_pType->GetInt(NPCTYPEDATA_MANA);
	//m_tFight.SetInterval(m_pType->GetInt(NPCTYPEDATA_ATKSPEED));
	//m_tFight.Update();

	//if (!m_pMap)
	//	return false;

	//m_pBattleSystem	= new CBattleSystem(this->m_idProcess, this);
	//CHECKF(m_pBattleSystem);
	//m_setStatus = CStatusSet::CreateNew(true);
	//CHECKF(m_setStatus);

	//if (!IsCallPet() && !IsEudemon())	// synchro outside
	//{
	//	CMsgMonsterInfo	msg;
	//	IF_OK(msg.Create(pInfo))
	//		this->SendMsg(&msg);
	//}

	//if (!IsSynPet() || pInfo->idOwner == ID_NONE)		// need not save to database
	//	return true;

	/////////////////////////////////////////////////////////////////////////
	// create record
	/*m_pData = CPetData::CreateNew();
	IF_OK(m_pData)
	{
	IF_OK(m_pData->Create(GameDataDefault()->GetPetData(), ID_NONE))
	{
	m_pData->SetInt(PETDATA_OWNERID, pInfo->idOwner);
	m_pData->SetInt(PETDATA_OWNERTYPE, pInfo->ucOwnerType);
	m_pData->SetInt(PETDATA_GENID, pInfo->idData);
	m_pData->SetInt(PETDATA_TYPE, pInfo->usType);
	if(pszName)
	m_pData->SetStr(PETDATA_NAME, pszName, _MAX_NAMESIZE);
	else
	m_pData->SetStr(PETDATA_NAME, pType->GetStr(NPCTYPEDATA_NAME), _MAX_NAMESIZE);
	m_pData->SetInt(PETDATA_LIFE, m_nCurrLife);
	m_pData->SetInt(PETDATA_MANA, m_nCurrMana);
	m_pData->SetInt(PETDATA_MAPID, pInfo->idMap);
	m_pData->SetInt(PETDATA_RECORD_X, pInfo->usPosX);
	m_pData->SetInt(PETDATA_RECORD_Y, pInfo->usPosY);
	m_pData->SetInt(PETDATA_DATA, pInfo->nData);
	OBJID idPet = m_pData->InsertRecord();

	return idPet != ID_NONE;
	}
	else
	{
	SAFE_RELEASE(m_pData);
	}
	}*/
	return true;
}

void CMonster::Create_LevelBase() {
	//All base stats
	pData->SetLevel(1);
}

void CMonster::Create_LevelOne() {
	/*
	3A: +-40% varience + fixed 25% * raw stat (85% > 165%)
	Life: +-80% + fixed 25% * rawlife (45% > 205%)

	Stat varience = 3A +(life/10) / (base3A + (baselife/10)
	growth/lifegrow = base +-40% * varience

	stat rates:
	stat with greatest difference from base (taking into account 0.8 is better than 0.7 even though both negative) gets +8, other two get -4*/

	float fRawAttack = GetCalcAttack();
	float fRawDef = GetCalcDefence();
	float fRawDex = GetCalcDexterity();
	float fRawLife = GetCalcLife();
	float fRawTotal = fRawAttack + fRawDef + fRawDex + (fRawLife / 10);
	
	pData->SetAttack(fRawAttack * (RandomRateGet(0.4) + 0.25));
	pData->SetDefence(fRawDef * (RandomRateGet(0.4) + 0.25));
	pData->SetDexterity(fRawDex * (RandomRateGet(0.4) + 0.25));
	pData->SetLife(fRawLife * (RandomRateGet(0.8) + 0.25));

	float varience = (pData->GetAttack() + pData->GetDefence() + pData->GetDexterity() + (pData->GetLife() / 10)) / fRawTotal;

	pData->SetGrowth(pData->GetGrowth() * RandomRateGet(0.4) * varience);
	pData->SetLifeRise(pData->GetLifeRise() * RandomRateGet(0.4) * varience);

	//adjust 3a rates
	float fAtkDif = pData->GetAttack() - GetCalcAttack();
	float fDefDif = pData->GetDefence() - GetCalcDefence();
	float fDexDif = pData->GetDexterity() - GetCalcDexterity();
	int adjAtk, adjDef, adjDex;
	if (fAtkDif > fDefDif) {
		if (fAtkDif > fDexDif) {
			adjAtk = 8;
			adjDef = -4;
			adjDex = -4;
		}
		else {
			adjAtk = -4;
			adjDef = -4;
			adjDex = 8;
		}
	}
	else {
		if (fDefDif > fDexDif) {
			adjAtk = -4;
			adjDef = 8;
			adjDex = -4;
		}
		else {
			adjAtk = -4;
			adjDef = -4;
			adjDex = 8;
		}
	}
	pData->SetRateAttack(pData->GetRateAttack() + adjAtk);
	pData->SetRateDefence(pData->GetRateDefence() + adjDef);
	pData->SetRateDexterity(pData->GetRateDexterity() + adjDex);
}

void CMonster::Create_LevelAny() {
	/*
	Attack,Defence,Dex,Life 75-85% max
	Growth: grow_point * +-0.3 - 0.1
	aka (0.7 to 1.3) - 0.1 = 0.6>1.2*/

	pData->SetAttack(GetCalcAttack() * ((float)(RandGet(10, 0) + 75) / 100.0));
	pData->SetDefence(GetCalcDefence() * ((float)(RandGet(10, 0) + 75) / 100.0));
	pData->SetDexterity(GetCalcDexterity() * ((float)(RandGet(10, 0) + 75) / 100.0));
	pData->SetGrowth(pData->GetGrowth() * (RandomRateGet(0.3) - 0.1));
	//Add liferise?
}

float CMonster::GetCalcAttack() {
	float perLevel = (pData->GetRateAttack() / 100.0) * pData->GetGrowth();
	float fAttack = (float)(pData->GetLevel() - 1) * perLevel;
	return pData->GetBaseAttack() + fAttack;
}

float CMonster::GetCalcDefence() {
	float perLevel = (pData->GetRateDefence() / 100.0) * pData->GetGrowth();
	float fDef = (float)(pData->GetLevel() - 1) * perLevel;
	return pData->GetBaseDefence() + fDef;
}

float CMonster::GetCalcDexterity() {
	float perLevel = (pData->GetRateDexterity() / 100.0) * pData->GetGrowth();
	float fDex = (float)(pData->GetLevel() - 1) * perLevel;
	return pData->GetBaseDexterity() + fDex;
}

float CMonster::GetCalcLife() {
	float fLife = (float)(pData->GetLevel() - 1) * pData->GetLifeRise();
	return pData->GetBaseLife() + fLife;
}

void CMonster::SetLife(int nLife, BOOL bUpdate) { //update not used here
	if (nLife < 0) nLife = 0;
	LifeCurrent = nLife;
}
