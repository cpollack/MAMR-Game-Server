#include "Pet.h"
#include "MapGroup.h"

#include "Monster.h"

DWORD NEXT_PETID = _IDMSK_PET;

DWORD GetNext_PetID(IDatabase *pDb) {
	if (NEXT_PETID == _IDMSK_PET) {
		CHECKF(pDb);

		SQLBUF	szSQL;
		sprintf(szSQL, "select MAX(id) from %s", _TBL_PET);
		IRecordset* pRecs = pDb->CreateNewRecordset(szSQL);	//VVVVVVVVV
		if (pRecs)
		{
			NEXT_PETID = pRecs->GetInt(0) + 1;
			pRecs->Release();		//AAAAAAAAAAAAAA
		}
	}

	return NEXT_PETID++;
}

MYHEAP_IMPLEMENTATION(CPet, s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPet::CPet()
{
	SetObjType(OBJ_PET);
	pType = NULL;
	ID = ID_NONE;
	//m_pBattleSystem	= NULL;
	//pData = NULL;

	m_tFootPrint = 0;
	m_posFootPrint.x = 0;
	m_posFootPrint.y = 0;

	//m_link.Init(this);

	m_bDecRole = false;

	m_nKillNum = 0;
	m_nKillNum4Potential = 0;
	m_nKillNum4RelationShip = 0;
}

//////////////////////////////////////////////////////////////////////
CPet::~CPet()
{
	//if (pData) SAFE_RELEASE(pData);
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
bool CPet::Create(PROCESS_ID idProcess, OBJID idPet)
{
	CHECKF(CMapGroup::IsValidMapGroupProcessID(idProcess));
	m_idProcess = idProcess;

	ID = idPet;

	if (!data.Create(idPet, Database()))
		return false;

	//m_nDir = ::RandGet(8);
	//m_pMap = MapManager()->GetGameMap(pInfo->idMap);
	//m_nPosX = pInfo->usPosX;
	//m_nPosY = pInfo->usPosY;
	//	m_dwStatus		= STATUS_NORMAL;
	//m_i64Effect = KEEPEFFECT_NORMAL;
	//m_nPose = POSE_STAND;
	//m_idGen = pInfo->idData;

	int monsterClass = data.GetClass();
	if (IsSuper() || IsUnevo()) {
		element = (ELEMENT)(monsterClass % 10000 / 1000);
	}
	else {
		element = (ELEMENT)(monsterClass / 10000);
	}

	//LifeCurrent = data.GetLife();
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

	return true;
}


CPet* CPet::CreateNewPet(PROCESS_ID idProcess, OBJID ownerId, CMonster* pMonster) {
	ASSERT(pMonster);
	if (!pMonster) return nullptr;

	CPet* pPet = CPet::CreateNew();
	ASSERT(pPet);
	if (!pPet) return nullptr;
	
	LPCTSTR szName = pMonster->GetName();
	int nLook = pMonster->GetLook();

	int nLevel = pMonster->GetLev();
	int nCapLevel = nLevel;
	const int nExp = 0;
	const int nGeneration = 0;
	const int DEFAULT_FIDELITY = 100;
	//captured in battle should default to 60

	int nClass = pMonster->GetClass();

	float fAttack = pMonster->GetAttack();
	float fDefence = pMonster->GetDefence();
	float fDexterity = pMonster->GetDexterity();
	float fBaseAttack = pMonster->GetBaseAttack();
	float fBaseDefence = pMonster->GetBaseDefence();
	float fBaseDexterity = pMonster->GetBaseDexterity();
	int nAttackRate = pMonster->GetAttackRate();
	int nDefenceRate = pMonster->GetDefenceRate();
	int nDexterityRate = pMonster->GetDexterityRate();
	float fGrowRate = pMonster->GetGrowRate();
	float fOrgGrowrate = fGrowRate;

	int nLife = pMonster->GetLife();
	float fBaseLife = pMonster->GetMaxLife();
	float fMaxLife = pMonster->GetMaxLife();
	float fLifeRise = pMonster->GetLifeRate();

	HSB hsb[3];
	for (int i = 0; i < 3; i++) hsb[i] = pMonster->GetHSB(i);

	SQLBUF	szSQL;
	sprintf(szSQL, "INSERT %s SET owner_id=%u,name='%s',look=%d,class=%d, level=%d,cap_lev=%d,exp=%d,generation=%d,fidelity=%d, \
		attack=%.2f,defence=%.2f,dexterity=%.2f,base_attack=%.2f,base_defence=%.2f,base_dexterity=%.2f,attack_rate=%d,defence_rate=%d,dexterity_rate=%d,grow_rate=%.2f,org_growrate=%.2f, \
		life=%d,base_life=%.2f,max_life=%.2f,life_rise=%.2f, \
		hue0=%d,saturation0=%d,bright0=%d,hue1=%d,saturation1=%d,bright1=%d,hue2=%d,saturation2=%d,bright2=%d ",
		_TBL_PET,
		ownerId, szName, nLook, nClass, nLevel, nCapLevel, nExp, nGeneration, DEFAULT_FIDELITY,
		fAttack, fDefence, fDexterity, fBaseAttack, fBaseDefence, fBaseDexterity, nAttackRate, nDefenceRate, nDexterityRate, fGrowRate, fOrgGrowrate,
		nLife, fBaseLife, fMaxLife, fLifeRise,
		hsb[0].hue, hsb[0].sat, hsb[0].bright, hsb[1].hue, hsb[1].sat, hsb[1].bright, hsb[2].hue, hsb[2].sat, hsb[2].bright);

	if (MapGroup(idProcess)->GetDatabase()->ExecuteSQL(szSQL)) {
		return pPet;
	}
	else {
		delete pPet;
		return nullptr;
	}
}