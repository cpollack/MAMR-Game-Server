#include "Pet.h"
#include "MapGroup.h"

#include "Monster.h"
#include "Network//MsgPetLevelUp.h"
#include "Network//MsgPetAction.h"
#include "Network//MsgUserAttrib.h"
#include "Network//MsgPetInfo.h"

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
		int petId = MapGroup(idProcess)->GetDatabase()->GetInsertId();
		pPet->SetID(petId);
		return pPet;
	}
	else {
		delete pPet;
		return nullptr;
	}
}

bool CPet::UpdateInfo(int nType) {
	CHECKF(m_pOwner);

	int nData = 0;
	switch (nType) {
	case PETACTION_FULLHEAL:
		nData = GetMaxLife();
		break;
	}
		
	CMsgPetAction msg;
	if (msg.Create(GetID(), nData, (PETACTION)nType))
		m_pOwner->SendMsg(&msg);

	return true;
}

//////////////////////////////////////////////////////////////////////
void CPet::SaveInfo() {
	data.SaveInfo();
}

void CPet::AwardBattleExp(int nExp, bool bGemEffect) {
	if (nExp == 0)
		return;

	//Max level 
	int maxLev = MAX_PET_LEV;
	if (this->IsUnevo()) 
		maxLev += (this->GetGeneration() * PET_UNEVOGEN_BONUS);
	if (m_pOwner && m_pOwner->GetMasterType() == MASTER_PET)
		maxLev += PET_MASTER_BONUS;
	if (this->GetLev() >= maxLev) 
		return;

	int nLevupExp = this->GetLev() * (this->GetLev() + 1) * 0.75;
	int nNewExp = nExp + this->GetExp();
	if (nNewExp >= nLevupExp) {
		this->IncLev(true);
		if (m_pOwner) {
			//CMsgPetInfo msg;
			//msg.Create(this, PETINFO_ACTIONUPDATE);
			//m_pOwner->SendMsg(&msg);
			CMsgPetLevelUp msg;
			if (msg.Create(this))
				m_pOwner->SendMsg(&msg);
		}
	}
	else {
		this->SetExp(nNewExp);
		data.SaveInfo();
	}
}

void CPet::IncLev(bool bUpdate) {
	this->SetExp(0, false);

	this->SetLevel(this->GetLev() + 1);

	//loyalty
	if (this->GetLev() % 5 == 0 && this->GetLoyalty() < 150) {
		this->SetLoyalty(this->GetLoyalty() + 1);
	}

	//Pet raising
	if (m_pOwner) {
		int nPetRaise = m_pOwner->GetPetRaising();
		
		if (this->GetDefence() / this->GetLev() < 1) nPetRaise++;
		if (this->GetLife() == this->GetMaxLife()) nPetRaise += 2;

		nPetRaise += (this->GetLev() / 150) + 1;
		nPetRaise += (this->GetLev() / 200);
		nPetRaise += (this->GetLev() / 300);
		m_pOwner->SetPetRaising(nPetRaise);
	}

	//Growth adjustments
	double dGrLifeAdjuster = 0;
	if (this->GetLife() < this->GetMaxLife()) {
		if (this->GetLife() <= this->GetMaxLife() * 0.9) 
			dGrLifeAdjuster = 0.05;
		if (this->GetLife() >= this->GetMaxLife() * 0.8) 
			dGrLifeAdjuster = -0.1;
	}
	else dGrLifeAdjuster = 0.1;

	double dLoyalty = this->GetLoyalty();
	if (dLoyalty > 100) dLoyalty = 100;
	double dGrLoyAdjuster = (dLoyalty - 90.0) / 400.0 + dGrLifeAdjuster;

	double dGrowth = (RandomRateGet(0.2) + dGrLoyAdjuster) * this->GetGrowth() + GetLevelCapModifier();
	double dAddAtk = this->GetAttackRate() * dGrowth / 100;
	double dAddDef = this->GetDefenceRate() * dGrowth / 100;
	double dAddDex = this->GetDexterityRate() * dGrowth / 100;
	this->SetAttack(this->GetAttack() + dAddAtk);
	this->SetDefence(this->GetDefence() + dAddDef);
	this->SetDexterity(this->GetDexterity() + dAddDex);

	double dLife = (RandomRateGet(0.2) + dGrLoyAdjuster) * this->GetLifeGrowth() + GetLevelCapModifier();
	this->SetMaxLife(this->GetMaxLife() + dLife);
	//this->SetLife(this->GetMaxLife()); //doesnt work with old client

	if (bUpdate)
		data.SaveInfo();

	if (m_pOwner) {
		CMsgUserAttrib msg;
		msg.Create(m_pOwner->GetID(), _USERATTRIB_PETRAISE, m_pOwner->GetPetRaising());
		m_pOwner->SendMsg(&msg);
	}
}

double CPet::GetLevelCapModifier() {
	int nDif = this->GetLev() - this->GetCapLev();
	if (nDif > 800) nDif = 800;
	return (double)nDif * 0.001;
}

//////////////////////////////////////////////////////////////////////
bool CPet::UseItem(OBJID idItem, bool bSynchro)
{
	/*if (!this->TryItem(idItem))
		return false;

	CItemPtr pItem = GetItem(idItem);
	if (!pItem)
		return false;

	if (!ChkUseItem(pItem, this->QueryRole()))
		return false;

	if (pItem->IsEatEnable())
	{
		int	nAddLife = pItem->GetInt(ITEMDATA_LIFE);
		int	nAddMana = pItem->GetInt(ITEMDATA_POWER);

		//		if(nAddLife >= MINI_ADDLIFE_DRAG && m_setSlowHealUp2Life.Size() > 1)		// 限制吃药速度
		//			return false;

		DEBUG_TRY	// VVVVVVVVVVVVVV
			int nTimes = 1; // pItem->GetInt(ITEMDATA_ATKSPEED);	// 补血的次数
		IF_NOT(SpendItem(pItem))		//??? 能吃的一定能删除, 先删除，防作弊
			return false;

		// 2003.2.8 修改加血变成慢慢加。
		if (nAddLife > 0)
		{
			int nFirstAdd = (nTimes < 2) ? nAddLife : 2 * nAddLife / (nTimes + 1);
			int nNextAdd = (nTimes >= 2) ? (nAddLife - nFirstAdd) / (nTimes - 1) : 0;
			int nLastAdd = nAddLife - nFirstAdd;
			if (nTimes > 2)
				nLastAdd -= nNextAdd * (nTimes - 2);

			typedef std::vector<int>	ADDLIFE_LIST;
			ADDLIFE_LIST	setAddLife;
			// first
			if (m_setSlowHealUp2Life.Size() == 0)
			{
				AddAttrib(_USERATTRIB_LIFE, nFirstAdd, SYNCHRO_TRUE);
				//this->BroadcastTeamLife();
			}
			else
				setAddLife.push_back(nFirstAdd);
			if (nNextAdd > 0)
			{
				for (int i = 1; i < nTimes - 1; i++)
					setAddLife.push_back(nNextAdd);
			}
			if (nLastAdd > 0)
				setAddLife.push_back(nLastAdd);

			int nMinNum = __min(setAddLife.size(), m_setSlowHealUp2Life.Size());
			for (int i = 0; i < nMinNum; i++)
			{
				if (setAddLife[i] > m_setSlowHealUp2Life[i])
					m_setSlowHealUp2Life[i] = setAddLife[i];
			}
			for (int i = nMinNum; i < setAddLife.size(); i++)
				m_setSlowHealUp2Life.Push(setAddLife[i]);

			m_tSlowHealLife.Update();
		}
		else if (nAddLife < 0)
		{
			//AddAttrib(_USERATTRIB_LIFE, nAddLife, SYNCHRO_TRUE);
			//this->BroadcastTeamLife();
		}

		if (nAddMana > 0)
		{
			int nFirstAdd = (nTimes < 2) ? nAddMana : 2 * nAddMana / (nTimes + 1);
			int nNextAdd = (nTimes >= 2) ? (nAddMana - nFirstAdd) / (nTimes - 1) : 0;
			int nLastAdd = nAddMana - nFirstAdd;
			if (nTimes > 2)
				nLastAdd -= nNextAdd * (nTimes - 2);

			typedef std::vector<int>	ADDMANA_LIST;
			ADDMANA_LIST	setAddMana;
			// first
			if (m_setSlowHealUp2Mana.Size() == 0)
			{
				AddAttrib(_USERATTRIB_MANA, nFirstAdd, SYNCHRO_TRUE);
			}
			else
				setAddMana.push_back(nFirstAdd);
			if (nNextAdd > 0)
			{
				for (int i = 1; i < nTimes - 1; i++)
					setAddMana.push_back(nNextAdd);
			}
			if (nLastAdd > 0)
				setAddMana.push_back(nLastAdd);

			int nMinNum = __min(setAddMana.size(), m_setSlowHealUp2Mana.Size());
			for (int i = 0; i < nMinNum; i++)
			{
				if (setAddMana[i] > m_setSlowHealUp2Mana[i])
					m_setSlowHealUp2Mana[i] = setAddMana[i];
			}
			for (int i = nMinNum; i < setAddMana.size(); i++)
				m_setSlowHealUp2Mana.Push(setAddMana[i]);

			m_tSlowHealMana.Update();
		}
		else if (nAddMana < 0)
		{
			//AddAttrib(_USERATTRIB_MANA, nAddMana, SYNCHRO_TRUE);
		}
		DEBUG_CATCH("PetUseItem") // AAAAAAAAAAAAAAAAA

		//UpdateWeight();
			return true;
	}*/

	return false;
}