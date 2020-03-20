#include "Pet.h"
#include "MapGroup.h"

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
