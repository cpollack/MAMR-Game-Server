// AINpc.cpp: implementation of the CAiNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "Network/AllMsg.h"
#include "GameMap.h"
#include "AINpc.h"
#include "MapGroup.h"
//#include "MapItem.h"
#include "basefunc.h"
#include "ActionDefine.h"
//#include "MapTrap.h"
#include "UserTable.h"
#include "Item.h"
#include "DeadLoop.h"

//#include "DropRuleMap.h"	//add by zlong 2003-11-15

//////////////////////////////////////////////////////////////////////
const int	RECRUITMAGIC_SECS					= 10;			// 每10秒使用一次加血魔法
const int	DEFAULT_MONSTER_MAGIC_LEVEL			= 0;
const int	UNIDENT_PERCENT						= 20;			// 掉普通物品时，未鉴定的比率

const int	AUTO_INC_LIFE_SECS					= 10;			// 每10秒自动增长生命
const int	AUTO_INC_LIFE_PERCENT				= 10;			// 每次增长最大生命的一半

const int	SORB_REFLECT_SECS					= 6;			// 吸收反射状态每隔6秒作用一次

//////////////////////////////////////////////////////////////////////
//---jinggy---begin
#define EXPLODEMONEY_RATE	4	//暴钱几率 
#define EXPLODEMONEY_DOUBLE	15  //暴钱时的倍数
//---jinggy---end
//////////////////////////////////////////////////////////////////////
MYHEAP_IMPLEMENTATION(CAiNpc,s_heap)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAiNpc::CAiNpc()
{
	SetObjType(OBJ_NPCTYPE);
	m_pType			= NULL;
	m_idNpc			= ID_NONE;
	//m_pBattleSystem	= NULL;
	//m_pData			= NULL;

	m_tFootPrint	= 0;
	m_posFootPrint.x	= 0;
	m_posFootPrint.y	= 0;

	m_link.Init(this);
	m_pMagicType	= NULL;
	m_pMagic		= NULL;

//	memset(&m_AddInfo, 0, sizeof(m_AddInfo));
	m_nPotential	= DEFAULT_EUDEMON_POTENTIAL;
	m_dwMaskData	= 0;

	m_bDecRole		= false;

	m_nKillNum		= 0;
	m_nKillNum4Potential	= 0;
	m_nKillNum4RelationShip	= 0;
	
	m_nAtkMode		= EATK_MODE_NONE;		// 默认攻击类型为无	
}

//////////////////////////////////////////////////////////////////////
CAiNpc::~CAiNpc()
{
	/*if(m_pData)
	{
		if(IsSynPet())
			MapManager()->RecyclePetID(GetID());
		else if(IsCallPet())
			MapManager()->RecycleCallPetID(GetID());

		if(m_pData->GetInt(PETDATA_LIFE) > 0)		// flag to die
			SaveInfo();
		else
			m_pData->DeleteRecord();
		m_pData->Release();
	}*/
	if(m_idNpc != ID_NONE)
	{
		LeaveMapGroup();
		m_idNpc = ID_NONE;
	}
	//if (m_pBattleSystem)
	//{
	//	delete m_pBattleSystem;
	//	m_pBattleSystem	= NULL;
	//}
	
	if (m_pMagic)
		m_pMagic->ReleaseByOwner();
	
	SAFE_RELEASE (m_setStatus);
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::Create(PROCESS_ID idProcess, IRecordset* pRes)
{
	m_idProcess		= idProcess;

	//ASSERT(!m_pData);

	//m_pData = CPetData::CreateNew();
	//CHECKF(m_pData);
	//IF_NOT(m_pData->Create(pRes))
	//	return false;

	//OBJID idType = m_pData->GetInt(PETDATA_TYPE);
	//m_pType			= NpcType()->GetObj(idType);
	CHECKF(m_pType);

	m_nDir			= ::RandGet(8);
	//m_pMap			= MapManager()->GetGameMap(m_pData->GetInt(PETDATA_MAPID), false);		// false: not load dynamic map
	if(!m_pMap)
	{
		//m_pData->Release();
		//m_pData = NULL;
		return false;		// not this map group, or in dynamic map
	}

	m_idNpc			= MapManager()->SpawnNewPetID();		//? mast follow m_pMap
	//m_nPosX			= m_pData->GetInt(PETDATA_RECORD_X);
	//m_nPosY			= m_pData->GetInt(PETDATA_RECORD_Y);
//	m_dwStatus		= STATUS_NORMAL;
	m_i64Effect		= KEEPEFFECT_NORMAL;
//	if((m_pType->GetInt(NPCTYPEDATA_ATKUSER) & ATKUSER_WING))
//		m_i64Effect		= KEEPEFFECT_WING;
	m_nPose			= POSE_STAND;
	//m_idGen			= m_pData->GetInt(PETDATA_GENID);

	//m_nCurrLife		= m_pData->GetInt(PETDATA_LIFE);
	//m_nCurrMana		= m_pData->GetInt(PETDATA_MANA);
	m_tFight.SetInterval(m_pType->GetInt(NPCTYPEDATA_ATKSPEED));
	m_tFight.Update();

	m_tSorbReflect.Clear();
	m_nTotalDamage	= 0;
	
	//m_pBattleSystem	= new CBattleSystem(this->m_idProcess, this);
	//CHECKF(m_pBattleSystem);
	m_setStatus = CStatusSet::CreateNew(true);
	CHECKF(m_setStatus);

	// synchro
	ST_CREATENEWNPC	info;
	memset(&info, 0, sizeof(ST_CREATENEWNPC));
	info.id				= GetID();
	info.usAction		= MSGAINPCINFO_CREATENEW;
	info.usType			= GetType();
	//info.ucOwnerType	= m_pData->GetInt(PETDATA_OWNERTYPE);
	//info.idOwner		= m_pData->GetInt(PETDATA_OWNERID);
	info.idMap			= GetMap()->GetID();
	info.usPosX			= GetPosX();
	info.usPosY			= GetPosY();
	//info.idData			= m_pData->GetInt(PETDATA_GENID);
	info.nData			= GetData();
	CMsgMonsterInfo	msg;
	IF_OK(msg.Create(&info))
		this->SendMsg(&msg);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::Create(PROCESS_ID idProcess, CNpcType* pType, const ST_CREATENEWNPC* pInfo, CUser* pUser, OBJID idItem)
{
	CHECKF(pType && pInfo && pUser);

	IF_OK(Create(idProcess, pType, pInfo, pUser->GetName()))
	{
		CHECKF(IsCallPet());

		if(IsMagicAtk())
		{
			m_pMagicType	= CMagic::FindMagicType(GetMagicType(), DEFAULT_MONSTER_MAGIC_LEVEL);
			IF_NOT(m_pMagicType)
			{
				LOGERROR("Can't find magic type [%d] in monster type [%d]", GetMagicType(), pType->GetID());
				return false;
			}
		}

		m_pMagic = CMagic::CreateNew(idProcess, this->QueryRole());
		if (!m_pMagic || !m_pMagic->CreateAll())
			return false;

		// synchro
		CMsgCallPetInfo	msg;
		IF_OK(msg.Create(GetID(), GetLookFace(), pType->GetInt(NPCTYPEDATA_AITYPE), GetPosX(), GetPosY(), idItem))
			pUser->SendMsg(&msg);

		m_pOwner		= pUser->QueryLink();
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::Create(PROCESS_ID idProcess, CNpcType* pType, const ST_CREATENEWNPC* pInfo, LPCTSTR pszName/*=NULL*/)
{
	m_idProcess		= idProcess;

	CHECKF(pType);

	m_idNpc			= pInfo->id;
	m_nDir			= ::RandGet(8);
	m_pMap			= MapManager()->GetGameMap(pInfo->idMap);
	m_nPosX			= pInfo->usPosX;
	m_nPosY			= pInfo->usPosY;
//	m_dwStatus		= STATUS_NORMAL;
	m_i64Effect		= KEEPEFFECT_NORMAL;
	m_nPose			= POSE_STAND;
	m_idGen			= pInfo->idData;

	m_pType			= pType;

	m_nCurrLife		= m_pType->GetInt(NPCTYPEDATA_LIFE);
	m_nCurrMana		= m_pType->GetInt(NPCTYPEDATA_MANA);
	m_tFight.SetInterval(m_pType->GetInt(NPCTYPEDATA_ATKSPEED));
	m_tFight.Update();

	if(!m_pMap)
		return false;

	//m_pBattleSystem	= new CBattleSystem(this->m_idProcess, this);
	//CHECKF(m_pBattleSystem);
	m_setStatus = CStatusSet::CreateNew(true);
	CHECKF(m_setStatus);

	if(!IsCallPet())	// synchro outside
	{
		CMsgMonsterInfo	msg;
		IF_OK(msg.Create(pInfo))
			this->SendMsg(&msg);
	}

	if(!IsSynPet() || pInfo->idOwner == ID_NONE)		// need not save to database
		return true;

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
	return false;
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::OnTimer(time_t tCurr)
{
	if(!this->IsAlive() && !m_bLeaveMap)
	{
		if ((m_tDie.IsActive() && m_tDie.GetRemain() < NPCDIEDELAY_SECS/2)			// 
			&& !(m_i64Effect & KEEPEFFECT_DISAPPEARING)		// 已经设置了尸体消失状态，避免重复设置
			&& !this->QueryStatus(STATUS_LOCK))				// 如果处于锁定状态则不消失
		{
			this->SetStatus(STATUS_DISAPPEARING);
		}
	}
	if(IsDeleted())
		return ;	// no timer

	// add life ------------------------------------------------------
	DEBUG_TRY
	if (IsAlive() && m_pType->GetInt(NPCTYPEDATA_MAGIC_TYPE) == SIMPLEMAGIC_RECRUIT && m_tAddLife.IsActive() && m_tAddLife.ToNextTime(RECRUITMAGIC_SECS))
	{
		if(GetLife() < GetMaxLife())
		{
			int nAddLife = GetMaxLife() * GetRecruitMagicPercent() / 100;
			int nLoseLife = ::CutRange((int)GetMaxLife() - (int)GetLife(), (int)0, (int)GetMaxLife());
			nAddLife = ::CutOverflow(nAddLife, nLoseLife);
			AddAttrib(_USERATTRIB_LIFE, nAddLife, SYNCHRO_TRUE);

			// synchro
			CMsgMagicEffect	msg;
			IF_OK(msg.Create(GetID(), SIMPLEMAGIC_RECRUIT, 0, GetID(), nAddLife, GetDir()))
				BroadcastRoomMsg(&msg, EXCLUDE_SELF);

			m_nFightPause	+= 1000;		// delay
		}
		else
		{
			m_tAddLife.Clear();
		}
	}
	DEBUG_CATCH("CAiNpc add life");

	// 吸收伤害反射 -------------------------------------------------
	/*DEBUG_TRY
	if (m_tSorbReflect.IsActive() && m_tSorbReflect.ToNextTime())
	{
		if (m_pBattleSystem && m_pBattleSystem->IsActived() && m_nTotalDamage>0)
		{
			IRole* pTarget = this->FindAroundRole(m_pBattleSystem->GetTargetID());
			if (pTarget)
			{
				int nLifeLost = __min(m_nTotalDamage, pTarget->GetLife());
				pTarget->AddAttrib(_USERATTRIB_LIFE, -1*nLifeLost, SYNCHRO_TRUE);
				pTarget->BeAttack(BY_WEAPON, this, nLifeLost);
				if (!pTarget->IsAlive())
					this->Kill(pTarget, DIE_NORMAL);
			}
		}

		m_nTotalDamage = 0;		// 无论成功与否，一定要记得清0
	}
	DEBUG_CATCH("CAiNpc sorb reflect timer crash.")*/

	// 自动攻击 ------------------------------------------------------
	/*DEBUG_TRY
	if (m_pBattleSystem && m_pBattleSystem->IsActived() 
		&& m_tFight.ToNextTick(GetInterAtkRate() + m_nFightPause)
		&& (!QueryMagic() || !QueryMagic()->IsActive()))
	{
		m_pBattleSystem->ProcAttack_Hand2Hand();
		m_nFightPause	= 0;
	}
	DEBUG_CATCH("CAiNpc ProcAttack_Hand2Hand");*/

	/*if (m_pMagic)
	{
		DEBUG_TRY
		DEADLOOP_CHECK(PID, "QueryMagic()->OnTimer")
		m_pMagic->OnTimer(tCurr);
		DEBUG_CATCH("CAiNpc magic timer crash.")
	}*/

	// status --------------------------------------------------------
	DEBUG_TRY
	// 以下增加部分代码用于判断是否解除结界系统状态
	// bDetachTeamStatus = true 表示需要解除所有与结界相关的状态
	bool	bDetachTeamStatus = true;
	bool	bDetachAddExpStatus = true;		// 是否解除STATUS_ADD_EXP
	if (IsAlive())
	{
		if (m_pOwner)
		{
			CTeam* pTeam = m_pOwner->GetTeam();
			if (pTeam)
			{
				CUser* pLeader = UserManager()->GetUser(pTeam->GetLeader());
				if (pLeader && pLeader->IsAlive()
					&& this->GetMap()->GetID() == pLeader->GetMap()->GetID()
					&& this->GetDistance(pLeader->QueryMapThing()) <= _RANGE_TEAM_STATUS)
				{
					bDetachTeamStatus = false;
				}
				if (pLeader && pLeader->QueryStatus(STATUS_ADD_EXP))
					bDetachAddExpStatus = false;
			}
		}
	}

	for(int i = QueryStatusSet()->GetAmount()-1; i >= 0; i--)
	{
		IStatus* pStatus = QueryStatusSet()->GetObjByIndex(i);
		if(pStatus)
		{
			pStatus->OnTimer(tCurr);
			if(!pStatus->IsValid()
				|| (bDetachTeamStatus && pStatus->GetID() >= STATUS_TEAM_BEGIN && pStatus->GetID() <= STATUS_TEAM_END)
				|| (bDetachAddExpStatus && pStatus->GetID() == STATUS_ADD_EXP))
			{
				QueryStatusSet()->DelObj(pStatus->GetID());
			}
		}
	}
	DEBUG_CATCH("monster magic poison")

	// 死亡 -----------------------------------------------------
	DEBUG_TRY
	if((IsCallPet()) && m_pOwner == NULL)
	{
		if(!IsDeleted())
		{
			LOGERROR("Call pet don't find owner! del self.");
			DelMonster(DEL_NOW);
		}
	}
	DEBUG_CATCH("RoleManager()->QuerySet()->DelObj")
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::ClearAllStatus()
{
	for(int i = QueryStatusSet()->GetAmount() - 1; i >= 0; i--)
	{
		IStatus* pStatus = QueryStatusSet()->GetObjByIndex(i);
		if(pStatus)
			QueryStatusSet()->DelObj(pStatus->GetID());
	}
}

//////////////////////////////////////////////////////////////////////
/*
int	 CAiNpc::AdjustData(int nData, int nAdjust, int nMaxData/ *=0* /)
{
	if(nAdjust>=ADJUST_PERCENT)
		return MulDiv(nData, nAdjust-ADJUST_PERCENT, 100);

	if(nAdjust<=ADJUST_SET)
		return -1*nAdjust + ADJUST_SET;

	if(nAdjust==ADJUST_FULL)
	{
		ASSERT(nMaxData != 0);
		return nMaxData;
	}

	return nData + nAdjust;
}
*/

//////////////////////////////////////////////////////////////////////
bool CAiNpc::SendMsg(CNetMsg* pMsg)
{
	if (this->IsCallPet() && m_pOwner)
		return m_pOwner->SendMsg(pMsg);
	else
		return MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(m_idNpc, pMsg);
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::BroadcastRoomMsg(CNetMsg* pMsg, bool bSendSelf /*= false*/)
{
	CRole::BroadcastRoomMsg(pMsg, bSendSelf);
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::BroadcastRoomMsg(LPCTSTR szMsg, bool bSendSelf /*= false*/)
{
	CMsgTalk	msg;
	if(msg.Create(GetName(), ALLUSERS_NAME, szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		this->BroadcastRoomMsg(&msg, bSendSelf);
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::BroadcastMapMsg(CNetMsg* pMsg, bool bSendSelf /*= false*/)
{ 
	CMapPtr pMap = this->GetMap();
	if(pMap)
		UserManager()->BroadcastMapMsg(pMap->GetID(), pMsg);
	if(bSendSelf)
	{
		if (IsCallPet() && m_pOwner)
			m_pOwner->SendMsg(pMsg);
		else
			MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(ID_NONE, pMsg);
	}
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::BroadcastMapMsg(LPCTSTR szMsg, bool bSendSelf /*= false*/)
{
	CMsgTalk	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		this->BroadcastMapMsg(&msg, bSendSelf);
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::SendSelfToBlock()
{
	// brocast my info
	CMsgPlayer msg;
	if (msg.Create((IRole*)this))
		this->BroadcastRoomMsg(&msg);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::SendLeaveFromBlock()
{
	if(!m_bLeaveMap)
	{
		m_bLeaveMap = true;

		CMsgAction	msg;
		if(msg.Create(GetID(), 0, 0, 0, actionLeaveMap))
			this->BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// role
/////////////////////////////////////////////////////////////////////////////
void CAiNpc::SendShow(IRole* pRole)
{
	CHECK(pRole);

	CMsgPlayer	msg;
	if(msg.Create((IRole*)this))
		pRole->SendMsg(&msg);
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::SendSysMsg(const char* fmt, ...)
{ 
	MSGBUF	szMsg;
    vsprintf( szMsg, fmt, (char*) ((&fmt)+1) );

	CMsgTalk msg;
	if (msg.Create(SYSTEM_NAME, GetName(), szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		return this->SendMsg(&msg);

	return false;
}

//////////////////////////////////////////////////////////////////////
// modify attrib
//////////////////////////////////////////////////////////////////////
bool CAiNpc::AddAttrib(int idxAttr, __int64 i64Data, int nSynchro)
{
	CMsgUserAttrib	msg;
	if(!msg.Create(GetID(), _USERATTRIB_NONE, _USERATTRIB_NONE))			// _USERATTRIB_NONE : 不添加
		return false;

	if(i64Data)
	{
		switch(idxAttr)
		{
		case	_USERATTRIB_LIFE:
			{
				if ((int)this->GetLife() + i64Data <= 0)
				{
//						this->SetStatus(STATUS_DIE);
					m_nCurrLife	= 0;
				}
				else
					m_nCurrLife	= this->GetLife() + i64Data;

				// 血超过70%的时候解除狂暴状态
				if (GetLife()*100/GetMaxLife() > MAX_FRENZY_LIFE_PERCENT)
				{
					CRole::DetachStatus(this->QueryRole(), STATUS_FRENZY);
				}

				IF_NOT (msg.Append(_USERATTRIB_LIFE, GetLife()))
					return false;
			}
			break;
		case	_USERATTRIB_POTENTIAL:
			break;
		case	_USERATTRIB_MANA:
			{
//				m_nCurrMana	= (__max(GetMana() + i64Data, 0));
//				IF_NOT (msg.Append(_USERATTRIB_MANA, GetMana()))
					return false;
			}
			break;
		case	_USERATTRIB_EXP:
			{
//				IF_NOT (msg.Append(_USERATTRIB_EXP, GetExp()))
					return false;
			}
			break;
		case	_USERATTRIB_MONEY:
			{
//				IF_NOT (msg.Append(_USERATTRIB_MONEY, GetMoney()))
					return false;
			}
			break;
		default:
			return false;
		}
	}

	if(nSynchro != SYNCHRO_FALSE)
	{
		switch(nSynchro)
		{
		case SYNCHRO_TRUE:
			this->SendMsg(&msg);
			break;

		case SYNCHRO_BROADCAST:
			this->BroadcastRoomMsg(&msg, INCLUDE_SELF);
			break;

		default:
			break;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::ProcessAfterMove()
{
	/*IThingSet* pSet = GetMap()->QueryBlock(GetPosX(), GetPosY()).QuerySet();
	for(int i = 0; i < pSet->GetAmount(); i++)
	{
		IMapThing* pTarget = pSet->GetObjByIndex(i);
		CMapTrap* pTrap;
		if(pTarget && pTarget->QueryObj(OBJ_TRAP, IPP_OF(pTrap))
				&& pTrap->IsTrapSort() && pTarget->GetPosX() == GetPosX() && pTarget->GetPosY() == GetPosY())
		{
			pTrap->TrapAttack(QueryRole());
		}
	}*/
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::ProcessOnMove(int nMoveMode)
{
	SetPose(_ACTION_STANDBY);
	// stop fight
	if(nMoveMode != MOVEMODE_JUMPMAGICATTCK && nMoveMode != MOVEMODE_COLLIDE && nMoveMode != MOVEMODE_SYNCHRO)
		ClrAttackTarget();

	m_tFootPrint = ::TimeGet();
	m_posFootPrint.x = this->GetPosX();
	m_posFootPrint.y = this->GetPosY();
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::GetFootPrint	(int& nPosX, int& nPosY)
{
	if (::TimeGet()-m_tFootPrint >= TIME_FOOTPRINT)
	{	// time out
		nPosX = this->GetPosX();
		nPosY = this->GetPosY();
	}
	else
	{
		nPosX = m_posFootPrint.x;
		nPosY = m_posFootPrint.y;
	}
}

//////////////////////////////////////////////////////////////////////
// interactive
//////////////////////////////////////////////////////////////////////
bool CAiNpc::Freeze(int nPower)								// return false: 解穴不成功
{
	if(IsAlive())
	{
		if(nPower > 0)
		{
			return false;								// 不显示被点状态
		}
		else
		{
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
// fight
//////////////////////////////////////////////////////////////////////
bool CAiNpc::SetAttackTarget(IRole* pTarget /*= NULL*/)
{
	/*if(pTarget == NULL)
	{
		m_pBattleSystem->ResetBattle();
		return true;
	}

	if(pTarget->QueryOwnerUser() && GetMap()->IsInRegionType(REGION_PK_PROTECTED, GetPosX(), GetPosY()))
		return false;
	
	if(this->GetDistance(pTarget->QueryMapThing()) > GetAttackRange(pTarget->GetSizeAdd()))
		return false;

	m_pBattleSystem->CreateBattle(pTarget->GetID());*/
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::AutoSkillAttack(IRole* pTarget)
{
	CHECKF(pTarget);

	if (m_pMagic && m_pMagic->AutoAttackTarget(pTarget))
		return true;

	if(!IsMagicAtk())
		return false;

	CHECKF(m_pMagicType);
	switch(m_pMagicType->GetInt(MAGICTYPEDATA_SORT))
	{
	case	MAGICSORT_RECRUIT:
		{
			if(m_pOwner && m_tMagic.ToNextTime(m_pMagicType->GetInt(MAGICTYPEDATA_STEP)))
			{
				if(m_pOwner->GetLife() < m_pOwner->GetMaxLife())
				{
					int nAdd = m_pMagicType->GetInt(MAGICTYPEDATA_POWER);
					m_pOwner->AddAttrib(_USERATTRIB_LIFE, nAdd, SYNCHRO_TRUE);

					// effect
					CMsgMagicEffect	msg;
					IF_OK(msg.Create(GetID(), GetMagicType(), DEFAULT_MONSTER_MAGIC_LEVEL, m_pOwner->GetID(), nAdd, GetDir()))
						BroadcastRoomMsg(&msg, INCLUDE_SELF);
				}
			}
		}
		break;
	case	MAGICSORT_ADDMANA:
		{
			if(m_pOwner && m_tMagic.ToNextTime(m_pMagicType->GetInt(MAGICTYPEDATA_STEP)))
			{
				if(m_pOwner->GetMana() < m_pOwner->GetMaxMana())
				{
					int nAdd = m_pMagicType->GetInt(MAGICTYPEDATA_POWER);
					m_pOwner->AddAttrib(_USERATTRIB_MANA, nAdd, SYNCHRO_TRUE);

					// effect
					CMsgMagicEffect	msg;
					IF_OK(msg.Create(GetID(), GetMagicType(), DEFAULT_MONSTER_MAGIC_LEVEL, m_pOwner->GetID(), nAdd, GetDir()))
						BroadcastRoomMsg(&msg, INCLUDE_SELF);
				}
			}
		}
		break;
	case	MAGICSORT_BOMB:
		{
			DEBUG_TRY
			{
				if(!IsCallPet())
					ProcessBomb();
				else
					return false;
			}
			DEBUG_CATCH("CAiNpc::ProcessBomb()")
		}
		break;
	case	MAGICSORT_VAMPIRE:
	case	MAGICSORT_INSTEAD:
		{
			return false;
		}
		break;
	default:
		ASSERT(!"Nonsupport monster magic sort!!!");
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::AdditionMagic(int nLifeLost, int nDamage)
{
	if(!IsMagicAtk())
		return false;

	CHECKF(m_pMagicType);
	switch(m_pMagicType->GetInt(MAGICTYPEDATA_SORT))
	{
	case	MAGICSORT_RECRUIT:
	case	MAGICSORT_ADDMANA:
	case	MAGICSORT_BOMB:
	case	MAGICSORT_INSTEAD:
		{
			return false;
		}
		break;
	case	MAGICSORT_VAMPIRE:
		{
			if(m_pOwner && nLifeLost)
			{
				if(m_pOwner->GetLife() < m_pOwner->GetMaxLife())
				{
					int nAdd = ::CutTrail(0, CRole::AdjustDataEx(nLifeLost, m_pMagicType->GetInt(MAGICTYPEDATA_POWER)));
					if(nAdd)
						m_pOwner->AddAttrib(_USERATTRIB_LIFE, nAdd, SYNCHRO_TRUE);
				}
			}
		}
		break;
	default:
		ASSERT(!"Nonsupport monster magic sort !!!");
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
int CAiNpc::GetDieMode()
{
	CHECKF(m_pMagicType);

	if (m_pMagicType->GetInt(MAGICTYPEDATA_WEAPON_HIT) == CMagic::HIT_BY_MAGIC)
		return DIE_MAGIC;
	else if (IsBowman())
		return DIE_ARROWSHOOT;
	else
		return DIE_NORMAL;
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::ProcessBomb()
{
	CHECK(IsMagicAtk());
	CHECK(m_pMagicType);
	CHECK(m_pOwner);

	int	nPower = m_pMagicType->GetInt(MAGICTYPEDATA_POWER);
	int	nRange = m_pMagicType->GetInt(MAGICTYPEDATA_RANGE);

	POINT	pos;
	pos.x			= GetPosX();
	pos.y			= GetPosY();
	int	nSize		= nRange*2 + 1;
	int	nBufSize	= nSize * nSize;
	MAPTHING_SET	setTarget;
	GetMap()->CollectMapThing(setTarget, pos, nRange, OBJ_USER|OBJ_MONSTER|OBJ_NPC);
	vector<IRole*>	setRole;
	vector<int>		setPower;

	for(int i = ::CutTrail<int>(pos.x-nRange, 0); i <= pos.x+nRange && i < GetMap()->GetWidth(); i++)
	{
		for(int j = ::CutTrail<int>(pos.y-nRange, 0); j <= pos.y+nRange && j < GetMap()->GetHeight(); j++)
		{
			POINT posThis;
			posThis.x	= i;
			posThis.y	= j;
			if(!CUser::IsInCircle(posThis, pos, nRange))
				continue;

			int idx = POS2INDEX(posThis.x - pos.x + nRange, posThis.y - pos.y + nRange, nSize, nSize);
			ASSERT(idx>=0 && idx<setTarget.size());
			if(setTarget[idx])
			{
				IRole* pRole = NULL;
				if(setTarget[idx]->QueryRole(IPP_OF(pRole)) && pRole->IsAlive() && !IsImmunity(pRole))
				{
					bool bByMagic = m_pMagicType->GetInt(MAGICTYPEDATA_WEAPON_HIT) == CMagic::HIT_BY_MAGIC;
					int	nPower = 0; // CBattleSystem::CalcPower(bByMagic, QueryRole(), pRole, m_pMagicType->GetInt(MAGICTYPEDATA_POWER));

					{
						setRole.push_back(pRole);
						setPower.push_back(nPower);
					}
				}
			}
		}
	}

	// 广播法术效果
	CMsgMagicEffect	msg;
	IF_OK(msg.CreateByPos(GetID(), GetMagicType(), DEFAULT_MONSTER_MAGIC_LEVEL, pos.x, pos.y, GetDir()))
	{
		for(int i = 0; i < setRole.size(); i++)
			msg.AppendRole(setRole[i]->GetID(), setPower[i]);
		BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}

	// set crime status
	for(int i = 0; i < setRole.size(); i++)
	{
		if(m_pOwner->CheckCrime(setRole.at(i)))
			break;
	}

	int	nExp = 0;
	for (int i = 0; i < setRole.size(); i++)
	{
		int nLifeLost = __min(setRole[i]->GetLife(), setPower[i]);
		setRole[i]->AddAttrib(_USERATTRIB_LIFE, -1*nLifeLost, SYNCHRO_TRUE);
		CNpc* pNpc;
		if(setRole[i]->QueryObj(OBJ_NPC, IPP_OF(pNpc)) && pNpc->IsAwardScore())
			m_pOwner->AwardSynWarScore(pNpc, nLifeLost);

		if (setRole[i]->IsMonster())			// || pNpc && pNpc->IsGoal() && GetLev() >= pNpc->GetLev()
		{
			nExp += m_pOwner->AdjustExp(setRole[i], nLifeLost);
			/*if (!setRole[i]->IsAlive())
			{
				// 有组队，并且队伍中有其他队员，则奖励其他队员经验
				int	nBonusExp	= setRole[i]->GetMaxLife()*KILLBONUS_PERCENT/100;
				OtherMemberAwardExp(setRole[i], nBonusExp);

				nExp += AdjustExp(setRole[i], nBonusExp, true);
			}*/
		}

		setRole[i]->BeAttack(BY_MAGIC, QueryRole(), setPower[i]);
		if(!setRole[i]->IsAlive())
			Kill(setRole[i], GetDieMode());
	}

	AwardBattleExp(nExp);
}

//////////////////////////////////////////////////////////////////////
// precondition is dodge failed
int CAiNpc::Attack(IRole* pTarget)		// return : lose life
{
	CHECKF(pTarget);

	int nTempAdjust = 0;
	int nDamage = 0; // CBattleSystem::CalcPower(IsSimpleMagicAtk(), QueryRole(), pTarget, nTempAdjust, true);

	//护盾转移伤害
	if (pTarget->TransferShield(BY_WEAPON, QueryRole(), nDamage))
	{
	}
	else
	{
		int nLoseLife = ::CutOverflow(nDamage, (int)pTarget->GetLife());
		if (nLoseLife > 0)
			pTarget->AddAttrib(_USERATTRIB_LIFE, -1*nLoseLife, SYNCHRO_TRUE);

		pTarget->BeAttack(BY_WEAPON, QueryRole(), nDamage);
	}

	CGameMap* pMap = this->GetMap();
	if (pMap && m_pOwner)
	{
		// crime
		if (!pTarget->IsEvil()				// 只有pk白名才闪蓝
			&& !pMap->IsDeadIsland())	// 死亡岛杀人不闪蓝
		{
			if (!m_pOwner->QueryStatus(STATUS_CRIME))
				m_pOwner->SetCrimeStatus();
		}
	}

	IStatus* pStatus = QueryStatus(STATUS_DMG2LIFE);
	if (pStatus)
	{
		int nLifeGot = ::CutTrail(0, MulDiv(nDamage, pStatus->GetPower(), 100));
		if (nLifeGot > 0)
			this->AddAttrib(_USERATTRIB_LIFE, nLifeGot, SYNCHRO_TRUE);
	}

	return nDamage;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::BeAttack(bool bMagic, IRole* pTarget, int nPower, bool bReflectEnable/*=true*/)
{
	if (m_pType->GetInt(NPCTYPEDATA_MAGIC_TYPE) == SIMPLEMAGIC_RECRUIT && !m_tAddLife.IsActive())
		m_tAddLife.Startup(RECRUITMAGIC_SECS);
	
	CRole::DetachStatus(this->QueryRole(), STATUS_FREEZE);
	
	if (QueryStatus(STATUS_SORB_REFLECT))
		m_nTotalDamage += nPower;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::Kill(IRole* pTarget, DWORD dwDieWay)
{
	CHECK(pTarget);

	CMsgInteract msg;
	if(msg.Create(INTERACT_KILL, this->GetID(), pTarget->GetID(), pTarget->GetPosX(), pTarget->GetPosY(), dwDieWay))
		pTarget->BroadcastRoomMsg(&msg, true);

#ifdef	LOCAL_DEBUG
	CAiNpc* pMonster;
	if(pTarget->QueryObj(OBJ_NPC, IPP_OF(pMonster)))
		LOGERROR("怪物[%s][%d]在[%d,%d]杀死了[%s][%d]", GetName(), GetType(), 
						GetPosX(), GetPosY(), pMonster->GetName(), pMonster->GetType());
#endif

	if(m_pOwner)
	{
		CUser*	pTargetUser=NULL;
		if(pTarget->QueryObj(OBJ_USER, IPP_OF(pTargetUser)))
			m_pOwner->ProcessPk(pTargetUser);
	}

	if (QueryStatus(STATUS_FRENZY2))
		++m_nKillNum;

	pTarget->BeKill((IRole*)this);
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::BeKill(IRole* pRole /*= NULL*/)
{
	if(IsDeleted())
		return ;

	// pet
	/*if(m_pData)
	{
		m_pData->SetInt(PETDATA_LIFE, 0);		// set flag to die
	}*/

	CUser* pActionUser = NULL;
	if(pRole)
		pActionUser = pRole->QueryOwnerUser();			// pActionUser for call action
	OBJID idMapItemOwner = NULL;		// idMapItemOwner for map item owner
	if(pActionUser)
		idMapItemOwner = pActionUser->GetID();

	// bomb
	if((IsCallPet()/* || IsEudemon()*/) && IsMagicAtk() && m_pMagicType && m_pMagicType->GetInt(MAGICTYPEDATA_SORT) == MAGICSORT_BOMB)
	{
		DEBUG_TRY
		ProcessBomb();
		DEBUG_CATCH("CAiNpc::ProcessBomb()")
	}

	////////////////////////////////////////////////////////////////////
	// 怪物死亡后掉宝规则修改：
	// 取消原来的掉钱或者掉药品代码，改用新的掉物品规则
	// 若Action不存在，则根据cq_dropitemrule表中相应的规则掉宝
	//
	// 冷紫龙 2003-11-13
	////////////////////////////////////////////////////////////////////

	IStatus * pStatus = pRole->QueryStatus(STATUS_ADJUST_DROPMONEY);

	//drop money
	int nChanceAdjust = 100;
	CUser* pUser = NULL;
	// 玩家攻击绿名则掉钱/爆钱率调整为原来的20%
	if (pRole->QueryObj(OBJ_USER, IPP_OF(pUser)) && (NAME_GREEN == CAiNpc::GetNameType(pRole->GetLev(), this->GetLev())))
		nChanceAdjust = 20;

	if (::RandGet(100) < (m_pType->GetInt(NPCTYPEDATA_DROP_MONEY_CHANCE)*nChanceAdjust/100))
	{
		DWORD dwMoneyMin = m_pType->GetInt(NPCTYPEDATA_DROPMONEY_MIN);
		DWORD dwMoneyMax = m_pType->GetInt(NPCTYPEDATA_DROPMONEY_MAX);
		DWORD dwMoney = dwMoneyMin + ::RandGet(dwMoneyMax - dwMoneyMin + 1);
		//---jinggy---begin
		//玩家特殊状态调节掉钱数量
		if (pStatus)
			dwMoney = ::CutTrail(0, AdjustData(dwMoney, pStatus->GetPower()));						
		//---jinggy---end

		this->DropMoney(dwMoney, idMapItemOwner);
	}
	//---jinggy---暴钱---begin
	if (::RandGet(100) < (EXPLODEMONEY_RATE*nChanceAdjust/100))
	{
		DWORD dwMoneyMin = m_pType->GetInt(NPCTYPEDATA_DROPMONEY_MIN);
		DWORD dwMoneyMax = m_pType->GetInt(NPCTYPEDATA_DROPMONEY_MAX);
		DWORD dwMoney = (dwMoneyMin + ::RandGet(dwMoneyMax - dwMoneyMin + 1)) * EXPLODEMONEY_DOUBLE;
		
		//玩家特殊状态调节掉钱数量
		if (pStatus)
			dwMoney = ::CutTrail(0, AdjustData(dwMoney, pStatus->GetPower()));						

		int nHeapNum = 5 + ::RandGet(4); //堆数
		DWORD dwMoneyAve = dwMoney / nHeapNum;
		for(int i=0; i<nHeapNum; i++)
		{
			DWORD dwMoneyTmp = MulDiv(dwMoneyAve, 90 + RandGet(21), 100);
			this->DropMoney(dwMoneyTmp, idMapItemOwner);
		}
	}
	//---jinggy---暴钱---end

	// do action...
	if (m_pType->GetInt(NPCTYPEDATA_ACTION))
	{
		GameAction()->ProcessAction(m_pType->GetInt(NPCTYPEDATA_ACTION), pActionUser, this);
	}
//	else
	{
		// TODO: 增加采用新规则计算掉物品金钱代码
		/////////// 如果Action不存在，则采用新规则计算掉物品、金钱 <- Action用于其他用途，因此Action与掉物品并行执行
		// 冷紫龙 2003-11-13
		/*OBJID	idRuleGroup = m_pType->GetInt(NPCTYPEDATA_DROP_ITEM_RULE);
		CDropRuleGroup*	pDropRuleGroup = NULL;
		if ((ID_NONE != idRuleGroup) && (pDropRuleGroup	= DropRuleMap()->GetObjByIndex(idRuleGroup)))
		{
			int nDropNum = 0;
			int nAtkLev = this->GetLev();
			if(pRole)
				nAtkLev = pRole->GetLev();

			int nRate = ::RandGet(10000);

			//需要根据等级调整实际的掉宝几率
			int nChance = CBattleSystem::AdjustDrop(m_pType->GetInt(NPCTYPEDATA_EXPLODE_ITEM_CHANCE3), nAtkLev, this->GetLev());
			if (nRate < __min(10000, nChance))
			{
				nDropNum = 10 + ::RandGet(6);	//大爆drop 10 ~ 15 item
			} else {
				nChance += CBattleSystem::AdjustDrop(m_pType->GetInt(NPCTYPEDATA_EXPLODE_ITEM_CHANCE2), nAtkLev, this->GetLev());
				if (nRate < __min(10000, nChance))
				{
					nDropNum = 6 + ::RandGet(4);	//中爆drop 6 ~ 9 item
				} else {
					nChance += CBattleSystem::AdjustDrop(m_pType->GetInt(NPCTYPEDATA_EXPLODE_ITEM_CHANCE1), nAtkLev, this->GetLev());
					if (nRate < __min(10000, nChance))
					{
						nDropNum = 2 + ::RandGet(4);	//小爆drop 2 ~ 5 item
					} else {
						nChance += CBattleSystem::AdjustDrop(m_pType->GetInt(NPCTYPEDATA_DROP_ITEM_CHANCE), nAtkLev, this->GetLev());
						if (nRate < __min(10000, nChance))
							nDropNum = 1;	//普通drop 1 item
					}
				}
			}

			//??如果掉物品规则不是百分百掉，则实际掉的物品数有可能少于nDropNum
			for (int i=0; i<nDropNum; i++)
			{
				OBJID	idItemType = pDropRuleGroup->GetDropItem();
				if (idItemType != ID_NONE)
				{
					int nAddLuck = 0;
					int nAddAtk = 0;*/
/*
					if (CItem::IsEquipment(idItemType) && !CItem::IsMount(idItemType) && !CItem::IsSprite(idItemType))
					{
						//仅对除了座骑、精灵以外的其他装备加成
						int nRate = ::RandGet(1000);
						if (nRate < 1)				// 0.10% chance +3 luck
							nAddLuck = 3;
						else if (nRate < 5+1)			// 0.50% chance +2 luck
							nAddLuck = 2;
						else if (nRate < 25+5+1)		// 2.50% chance +1 luck
							nAddLuck = 1;

						if (::RandGet(1000) < 25)	// 2.50% chance + atk/def
						{
							CItemTypeData* pType = ItemType()->QueryItemType(idItemType);
							if(!pType)
							{
								LOGWARNING("怪物掉物品错误：错误的item_type[%u]!", idItemType);
								break;
							}
							int nLev = pType->GetInt(ITEMTYPEDATA_LEVEL);
							nAddAtk = __min(99, nLev*10) - (int)sqrt(::RandGet(__min(9801, nLev*nLev*100)));
							ASSERT(nAddAtk > 0 && nAddAtk < 100);
						}
					}
*//*

					int	nUserLuck = 0;
					if(pRole)
						nUserLuck = pRole->GetLuck();
					if (!this->DropItem(idItemType, idMapItemOwner, nAddLuck, nAddAtk, nUserLuck,true))
						break;
				}
			}
		}*/
	}

	this->SetStatus(STATUS_DIE);
	DelMonster();

	DEBUG_TRY
	if(IsInsteadMagic() && m_pOwner)
	{
		m_pOwner->BeKill();		// BeKill(pRole)
	}
	DEBUG_CATCH("instead kill!")
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::DelMonster(bool bNow/*=false*/)			// call this mast !IsDeleted()
{
	CHECK(!IsDeleted());

	// 因为打开了WITH_BLOCK开关，为了在死亡后尸体允许穿透，需要减地图上的角色数
	//if (GetMap() && !this->IsAlive())
	if (!m_bDecRole)
	{
		m_bDecRole	= true;
		GetMap()->DecRole(this->GetPosX(), this->GetPosY());
	}

	// pet
	/*if(m_pData)
	{
		m_pData->SetInt(PETDATA_LIFE, 0);		// set flag to die
	}*/

	// synchro npc server to del npc object
	if(bNow)
	{
		m_tDie.Startup(0);
		SendLeaveFromBlock();

		ClrBroadcastSet();
	}
	else
		// die status
		m_tDie.Startup(NPCDIEDELAY_SECS);
}

//////////////////////////////////////////////////////////////////////
void CAiNpc::SendDamageMsg(OBJID idTarget, int nDamage)
{
	if(IsSimpleMagicAtk())
	{
		CMsgMagicEffect	msg;
		IF_OK(msg.Create(GetID(), m_pType->GetInt(NPCTYPEDATA_MAGIC_TYPE), 0, idTarget, nDamage, GetDir()))
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}
	else if(IsBowman())
	{
		CMsgInteract msg;
		IF_OK(msg.Create(INTERACT_SHOOT, GetID(), idTarget, GetPosX(), GetPosY(), nDamage))
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}
	else
	{
		CMsgInteract msg;
		IF_OK(msg.Create(INTERACT_ATTACK, GetID(), idTarget, GetPosX(), GetPosY(), nDamage))
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}
}

////////////////////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetDropMoneyAvg()
{
	DWORD dwMoneyMin = m_pType->GetInt(NPCTYPEDATA_DROPMONEY_MIN);
	DWORD dwMoneyMax = m_pType->GetInt(NPCTYPEDATA_DROPMONEY_MAX);
	return (dwMoneyMin+dwMoneyMax)/2;
}

////////////////////////////////////////////////////////////////////////////////////
// drop
////////////////////////////////////////////////////////////////////////////////////
bool CAiNpc::DropMoney(DWORD dwMoney, OBJID idOwner)
{
	if (dwMoney <= 0)
		return true;

	if (this->GetLev() >= 80 && dwMoney <= 10)
		return true;

#ifdef _DEBUG
	// temp code
	FILE* fp = fopen("money.ini", "a+");
	if (fp)
	{
		fprintf(fp, "monster:%03u money ,%06u\n", 
			this->GetID(), dwMoney);
	}
	fclose(fp);
#endif

	POINT	pos;
	pos.x	= GetPosX();
	pos.y	= GetPosY();
	/*if(GetMap()->FindDropItemCell(MONSTERDROPITEM_RANGE, &pos))
	{
		CMapItem* pMapItem = CMapItem::CreateNew();
		if(pMapItem)
		{
			if(pMapItem->CreateMoney(MapManager()->SpawnMapItemID(), GetMap(), pos, dwMoney, idOwner))
			{
				MapManager()->QueryMapItemSet()->AddObj(pMapItem);
				return true;
			}
			else
				pMapItem->ReleaseByOwner();
		}
	}*/

	return false;
}

////////////////////////////////////////////////////////////////////////////////////
bool CAiNpc::DropItem(OBJID idItemType, OBJID idOwner, int nMagic2, int nMagic3, int nUserLuck,bool bIsAllowDropUnident)
{
	/*if (idItemType == ID_NONE)
		return true;

	POINT	pos;
	pos.x	= GetPosX();
	pos.y	= GetPosY();
	if(GetMap()->FindDropItemCell(MONSTERDROPITEM_RANGE, &pos))
	{
		CMapItem* pMapItem = CMapItem::CreateNew();
		if(pMapItem)
		{
			bool bUnIdent = false,bSetIdentFlag=false;
			//---判断是否进行转换为未鉴定的判断---begin
			if(bIsAllowDropUnident)
			{
				int nSort = CItem::GetItemSort(idItemType);
				int nType = CItem::GetItemType(idItemType);
				if(nSort==IETMSORT_FINERY)
				{
					if(nType==ITEMTYPE_HELMET || nType ==ITEMTYPE_NECKLACE || nType ==ITEMTYPE_ARMOR 
						||nType ==ITEMTYPE_BANGLE || nType == ITEMTYPE_SHOES)
					{
						bSetIdentFlag=true;
					}		
				}
				else if(nSort == ITEMSORT_WEAPON1 )
				{
					bSetIdentFlag=true;
				}

				//转变为未鉴定物品
				if (bSetIdentFlag)
				{
					//根据品质计算转换为鉴定的成功概率
					int  nQuality = CItem::GetQuality(idItemType);
					int  nRate=0;
					
					if(nQuality==QUALITY_ZERO)
						nRate = 5;
					else if(nQuality==QUALITY_ONE)
						nRate = 30;
					else if(nQuality==QUALITY_TWO)
						nRate = 50;
					else if(nQuality==QUALITY_THREE)
						nRate = 70;
					else if(nQuality==QUALITY_FOUR)
						nRate = 80;

					if(::RandGet(100) < nRate)
					{
						bUnIdent = true;
					}				
				}

			}
			//---判断是否进行转换为未鉴定的判断---end
			
//			bool bUnIdent = (nQuality <= NORMAL_QUALITY && ::RandGet(100) < UNIDENT_PERCENT && !CItem::IsMedicine(idItemType) && !CItem::IsArrowSort(idItemType)
//							|| nQuality > NORMAL_QUALITY || nMagic2 || nMagic3);
			if(pMapItem->Create(MapManager()->SpawnMapItemID(), GetMap(), pos, idItemType, idOwner, nMagic2, nMagic3, bUnIdent, nUserLuck))
			{
				MapManager()->QueryMapItemSet()->AddObj(pMapItem);
				return true;
			}
			else
				pMapItem->ReleaseByOwner();
		}
	}

#ifdef _DEBUG
		// temp code
		FILE* fp = fopen("item.ini", "a+");
		if (fp)
		{
			fprintf(fp, "monster: %u drop item: %u\n", 
					this->GetID(), idItemType);
		}
		fclose(fp);
#endif*/

	return false;
}

////////////////////////////////////////////////////////////////////////////////////
bool CAiNpc::DropEquipment(DWORD dwValue, OBJID idOwner, DWORD dwQuality/*=0*/)
{
	// drop money if value less than 100
	if (dwValue < 100)
		return this->DropMoney(dwValue, idOwner);
		
	// create equipment
	ItemInfoStruct info;
	if (CItem::CreateItemInfo(info, dwValue, m_pType, dwQuality))
	{
#ifdef _DEBUG
		// temp code
		/*FILE* fp = fopen("equipment.ini", "a+");
		if (fp)
		{
			fprintf(fp, "monster:%03u type:%06u amount:%05u amount_limit:%05u Gem1:%03u Gem2:%03u, Value:%06u\n", 
					this->GetID(), info.idType, info.nAmount, info.nAmountLimit, info.nGem1, info.nGem2, dwValue);
		}
		fclose(fp);*/
#endif

		// drop item
		/*POINT	pos;
		pos.x	= GetPosX();
		pos.y	= GetPosY();
		if(GetMap()->FindDropItemCell(MONSTERDROPITEM_RANGE, &pos))
		{
			CMapItem* pMapItem = CMapItem::CreateNew();
			if(pMapItem)
			{
				info.id = ID_NONE;
				if(pMapItem->Create(MapManager()->SpawnMapItemID(), GetMap(), pos, &info, idOwner))
				{
					MapManager()->QueryMapItemSet()->AddObj(pMapItem);
					return true;
				}
				else
				{
					pMapItem->ReleaseByOwner();
					return false;
				}
			}
		}

		return false;*/
	}

	return this->DropMoney(dwValue, idOwner);
}

////////////////////////////////////////////////////////////////////////////////////
bool CAiNpc::DropMedicine(OBJID idOwner)
{
	//rem by zlong 2003-11-15
	//修改了monstertype表以后已经没有drop_hp和drop_mp两个字段了

/*
	int nAmount = 0;
	int nRate = ::RandGet(100);
	if (nRate < 2)
		nAmount = 8;
	else if (nRate < 3)
		nAmount = 6;
	else if (nRate < 5)
		nAmount = 5;
	else if (nRate < 8)
		nAmount = 4;
	else if (nRate < 10)
		nAmount = 3;
	else if (nRate < 25)
		nAmount = 2;
	else
		nAmount = 1;


	for (int i=0; i<nAmount; i++)
	{
		DWORD dwType = 0;
		if (1 == ::RandGet(2))
			dwType = m_pType->GetInt(NPCTYPEDATA_DROP_HP);
		else
			dwType = m_pType->GetInt(NPCTYPEDATA_DROP_MP);

		this->DropItem(dwType, idOwner);

#ifdef _DEBUG
		// temp code
		FILE* fp = fopen("medicine.ini", "a+");
		if (fp)
		{
			fprintf(fp, "monster:%03u medicine:%06u\n", 
					this->GetID(), dwType);
		}
		fclose(fp);
#endif
	}
*/
	return true;
}

////////////////////////////////////////////////////////////////////////////////////
bool CAiNpc::ProcessAction(CUser* pUser, OBJID idAction, LPCTSTR pszAccept)
{
	if (idAction == ID_NONE)
		return false;

	try {
		// process action...
		const int _MAX_ACTIONPRC	=32;
		DWORD dwActionCount	=0;
		while (idAction != ID_NONE)
		{
			CActionData* pAction	= ActionSet()->GetObj(idAction);
			if (!pAction)
			{
				::LogSave("Error: game action %u not found.", idAction);
				break;
			}

			// process action now!
			idAction = pAction->GetInt(ACTIONDATA_IDNEXTFAIL);

			int nActionType = pAction->GetInt(ACTIONDATA_TYPE);
			switch(nActionType)
			{
			case ACTION_RAND:
				{
					// 检测随机率。"data1 data2"。"10 100"表示有1/10的机会是true。
					DWORD dwChance = 0, dwMax = 0;
					if (2 == sscanf(pAction->GetStr(ACTIONDATA_PARAM), "%u %u", &dwChance, &dwMax))
					{
						if (::RandGet(dwMax) < dwChance)
							idAction	= pAction->GetInt(ACTIONDATA_IDNEXT);
					}
					else
						LOGERROR("ACTION %u: 错误的参数数量", pAction->GetID());
				}
				break;

			case ACTION_RANDACTION:
				{
					// 检测随机率。"action0 .... action7"
					OBJID idRndAction[8];
					if (8 == sscanf(pAction->GetStr(ACTIONDATA_PARAM), "%u %u %u %u %u %u %u %u", 
						&idRndAction[0], &idRndAction[1], &idRndAction[2], &idRndAction[3],
						&idRndAction[4], &idRndAction[5], &idRndAction[6], &idRndAction[7]))
					{
						idAction	= idRndAction[::RandGet(8)];
					}
					else
						LOGERROR("ACTION %u: 错误的参数数量", pAction->GetID());
				}
				break;

			case ACTION_MST_DROPITEM:
				{
					// monster被杀死后掉物品或者钱, param "dropitem itemtype"或者"dropmoney money [LowPercent]"
					char szCmd[MAX_PARAMSIZE] = "";					
					if (1 != sscanf(pAction->GetStr(ACTIONDATA_PARAM), "%s", szCmd))
					{
						LOGERROR("ACTION %u: 错误的参数数量", pAction->GetID());
						break;
					}

					if (0 == _stricmp(szCmd, "dropitem"))
					{
						DWORD dwData = 0;
						if (2 == sscanf(pAction->GetStr(ACTIONDATA_PARAM), "%s %u", szCmd, &dwData))
						{
							if (0 == _stricmp(szCmd, "dropitem"))
							{
								OBJID idUser = ID_NONE;
								if (pUser)
									idUser = pUser->GetID();

								if (this->DropItem(dwData, idUser))
									idAction = pAction->GetInt(ACTIONDATA_IDNEXT);
							}
						}
						else
						{
							LOGERROR("ACTION %u: 错误的参数数量", pAction->GetID());
							break;
						}
					}
					else if (0 == _stricmp(szCmd, "dropmoney"))
					{
						DWORD dwData=0, dwLowPercent=0;
						int rval = sscanf(pAction->GetStr(ACTIONDATA_PARAM), "%s %u %u", szCmd, &dwData, &dwLowPercent);
						if (rval == 2)
							dwLowPercent = 100;
						else if (rval == 3)
							dwLowPercent %= 100;
						else
						{
							LOGERROR("ACTION %u: 错误的参数数量", pAction->GetID());
							break;
						}
						
						DWORD dwMoneyDrop = dwData*(dwLowPercent+::RandGet(100-dwLowPercent))/100;
						if (dwMoneyDrop <= 0)
							return true;

						OBJID idUser = ID_NONE;
						if (pUser)
							idUser = pUser->GetID();

						if (this->DropMoney(dwMoneyDrop, idUser))
							idAction	= pAction->GetInt(ACTIONDATA_IDNEXT);
					}
				}
				break;

			default:
				break;
			}

			if (dwActionCount++ >= _MAX_ACTIONPRC)
			{
				::LogSave("Error: too many game action, last action:%u.", idAction);
				break;
			}
		} // while
	}
	catch(...)
	{
		ASSERT(!"catch");
		::LogSave("Error: exception catched in CUser::ProcessAction(%u)", idAction);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::IsAtkable(IRole* pTarget, bool bSendHint)
{
	if (!pTarget)
		return false;

	if (!this->IsAlive())
	{
		if (bSendHint)
			this->SendSysMsg(STR_DIE_FORGIVE);
		return false;
	}

	if (!pTarget->IsAlive())
	{
		//if (bSendHint)
		//	this->SendSysMsg(STR_DIE_STOP_ATTACK);
		return false;
	}

	/*
	if (pTarget->IsGM())
	{
		if (bSendHint)
			this->SendSysMsg(STR_ATTACK_POLICE);
		return false;
	}
	*/

	if(GetID() == pTarget->GetID())
		return false;

	if(!pTarget->IsBeAtkable())
		return false;

	// 召唤兽不能攻击自己的主人
	if (this->QueryOwnerUser() && this->QueryOwnerUser()->GetID() == pTarget->GetID())
		return false;

	// map check
	if (!(this->GetMap() && pTarget->GetMap() && this->GetMap() == pTarget->GetMap()))
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::IsBeAtkable()
{
	return !(QueryStatus(STATUS_LOCK));
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::EnterMapGroup()
{
	CMapPtr pMap = this->GetMap();
	CHECKF(pMap);

	UpdateBroadcastSet();
	
	MapGroup(PID)->QueryIntraMsg()->SetNpcProcessID(GetID(), true);			// 同步SOCKET_KERNEL

	pMap->EnterRoom(this->QueryMapThing(), WITH_BLOCK);
//	if(IsSendBlockInfo())
//		pMap->SendBlockInfo((IRole*)this);
//	SendSelfToBlock();

	/*{
		CMsgAction	msg;
		IF_OK(msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionEmotion, _ACTION_EXCITEMENT))
			this->BroadcastRoomMsg(&msg);
	}*/

//	if(IsMapRoar())
	{
		CMsgAction	msg;
		IF_OK(msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionSoundEffect, GetType()))
			_UserManager(PID)->BroadcastMapMsg(pMap->GetID(), &msg);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::LeaveMapGroup()
{
	CMapPtr pMap = this->GetMap();
	CHECKF(pMap);


	MapGroup(PID)->QueryIntraMsg()->SetNpcProcessID(GetID(), false);			// 同步SOCKET_KERNEL

	// BeKill的时候调用了DecRole，因此这里需要判断，以免LeaveRoom的时候多减一次角色数
	bool bWithBlock = !m_bDecRole;
	
	SendLeaveFromBlock();	// NPC服务器需要这个通知来删除怪物
	ClrBroadcastSet();
	
	pMap->LeaveRoom(this->QueryMapThing(), bWithBlock);
	m_bDecRole	= true;
	return true;
}

//////////////////////////////////////////////////////////////////////
LPCTSTR	CAiNpc::GetName()
{
	return m_pType->GetStr(NPCTYPEDATA_NAME);
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetLife()
{
	int nMaxLife = this->GetMaxLife();

	if (m_nCurrLife > nMaxLife)
		m_nCurrLife = nMaxLife;

	return m_nCurrLife;
}

//////////////////////////////////////////////////////////////////////
double CAiNpc::GetMaxLife()
{
	int nLife = m_pType->GetInt(NPCTYPEDATA_LIFE);

	IStatus* pStatus = QueryStatus(STATUS_MAXLIFE);
	if (pStatus)
	{
		nLife	= ::CutTrail(0, AdjustData(nLife, pStatus->GetPower(), 100));
	}
	return nLife;
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetMinAtk()
{
	DWORD dwAtk	= m_pType->GetInt(NPCTYPEDATA_ATTACKMIN);

	return dwAtk;
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetMaxAtk()
{
	DWORD dwAtk	= m_pType->GetInt(NPCTYPEDATA_ATTACKMAX);

	// 算装备的coding here...

	dwAtk	= dwAtk;

	return dwAtk;
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetMgcMinAtk()
{
	DWORD dwAtk	= m_pType->GetInt(NPCTYPEDATA_ATTACKMIN);

	// 算装备的coding here...

	dwAtk	= dwAtk;

	return dwAtk;
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetMgcMaxAtk()
{
	DWORD dwAtk	= m_pType->GetInt(NPCTYPEDATA_ATTACKMAX);

	// 算装备的coding here...

	dwAtk	= dwAtk;

	return dwAtk;
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetDdg()
{
	DWORD dwDodge	= this->GetDodge();

//	IStatus* pStatus = QueryStatus(STATUS_DODGE);
//	if(pStatus)
//		dwDodge = AdjustData(dwDodge, pStatus->GetPower());

	// 算装备的coding here...
	
//	dwDodge	= dwDodge;

	return __max(0, dwDodge);
}

//////////////////////////////////////////////////////////////////////
double CAiNpc::GetDef()
{
	DWORD dwDef	= 0;

	// 算装备的coding here...
	
	dwDef	= dwDef + this->GetDefence();

	return dwDef; 
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetDex()
{
	float fDex = 0.0f;

	// 算装备的coding here...

	fDex = fDex + this->GetDexterity();


	// 因为需要保留2位小数点，乘100
	return __max(0, fDex*100.0f); 
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetMagicDef()
{
	int nDef	= m_pType->GetInt(NPCTYPEDATA_MAGIC_DEF);

	nDef = __min(90, nDef);
	nDef = __max(0, nDef);

	return nDef;
}

//////////////////////////////////////////////////////////////////////
DWORD CAiNpc::GetInterAtkRate()
{
	int nRate = GetIntervalAtkRate();

	IStatus* pStatus = QueryStatus(STATUS_ATKSPEED);
	if (pStatus)
		nRate	= ::CutTrail(0, AdjustData(nRate, pStatus->GetPower()));

	return nRate;
}

/////////////////////////////////////////////////////////////////////////////
void CAiNpc::SetStatus(int nStatus, bool bSynchro)
{
	I64 i64OldEffect = m_i64Effect;
	switch (nStatus)
	{
	case	STATUS_ADJUST_DODGE:
		{
			m_i64Effect	|= STATUS_ADJUST_DODGE;
		}
		break;
	case	STATUS_ADJUST_XP:
		{
			m_i64Effect	|= STATUS_ADJUST_XP;
		}
		break;
	case	STATUS_ADJUST_DROPMONEY:
		{
			m_i64Effect	|= STATUS_ADJUST_DROPMONEY;
		}
		break;
	case	STATUS_NORMAL:
		{
			m_dwStatus	= nStatus;
			m_i64Effect	= KEEPEFFECT_NORMAL;
		}
		break;
	case	STATUS_DIE:
		{
			m_dwStatus	= nStatus;
			m_i64Effect	= KEEPEFFECT_DIE;
			ClearAllStatus();
		}
		break;
	case	STATUS_CRIME:
		{
			m_i64Effect	|= KEEPEFFECT_CRIME;
		}
		break;
	case	STATUS_SYNCRIME:
		{
			m_i64Effect	|= KEEPEFFECT_SYNCRIME;
		}
		break;
	case	STATUS_POISON:
		{
			m_i64Effect	|= KEEPEFFECT_POISON;
		}
		break;
	case	STATUS_DISAPPEARING:
		{
			m_i64Effect	|= KEEPEFFECT_DISAPPEARING;
		}
		break;
	case	STATUS_DEFENCE1:
		{
			m_i64Effect	&= ~(KEEPEFFECT_DEFENCE2 | KEEPEFFECT_DEFENCE3);
			m_i64Effect	|= KEEPEFFECT_DEFENCE1;
		}
		break;
	case	STATUS_DEFENCE2:
		{
			m_i64Effect	&= ~(KEEPEFFECT_DEFENCE1 | KEEPEFFECT_DEFENCE3);
			m_i64Effect	|= KEEPEFFECT_DEFENCE2;
		}
		break;
	case	STATUS_DEFENCE3:
		{
			m_i64Effect	&= ~(KEEPEFFECT_DEFENCE1 | KEEPEFFECT_DEFENCE2);
			m_i64Effect	|= KEEPEFFECT_DEFENCE3;
		}
		break;
	case	STATUS_FREEZE:
		{
			m_i64Effect |= KEEPEFFECT_FREEZE;
		}
		break;
	case	STATUS_SMOKE:
		{
			m_i64Effect |= KEEPEFFECT_SMOKE;
		}
		break;
	case	STATUS_DARKNESS:
		{
			m_i64Effect |= KEEPEFFECT_DARKNESS;
		}
		break;
	case	STATUS_PALSY:
		{
			m_i64Effect |= KEEPEFFECT_PALSY;
		}
		break;
	case	STATUS_ATTACK:
		{
			m_i64Effect	|= KEEPEFFECT_ATTACK;
		}
		break;
	case	STATUS_MAGICDEFENCE:
		{
			m_i64Effect	|= KEEPEFFECT_MAGICDEFENCE;
		}
		break;
	case	STATUS_REFLECT:
		{
			m_i64Effect	|= KEEPEFFECT_REFLECT;
		}
		break;
	case	STATUS_REFLECTMAGIC:
		{
			m_i64Effect	|= KEEPEFFECT_REFLECTMAGIC;
		}
		break;
	case	STATUS_MAGICDAMAGE:
		{
			m_i64Effect	|= KEEPEFFECT_MAGICDAMAGE;
		}
		break;
	case	STATUS_ATKSPEED:
		{
			m_i64Effect	|= KEEPEFFECT_ATKSPEED;
		}
		break;
	case	STATUS_SLOWDOWN1:
		{
			m_i64Effect |= KEEPEFFECT_SLOWDOWN1;
		}
		break;
	case	STATUS_SLOWDOWN2:
		{
			m_i64Effect |= KEEPEFFECT_SLOWDOWN2;
		}
		break;
	case	STATUS_MAXLIFE:
		{
			m_i64Effect |= KEEPEFFECT_MAXLIFE;
		}
		break;
	case	STATUS_HIDDEN:
		{
			m_i64Effect |= KEEPEFFECT_HIDDEN;
		}
		break;
	case	STATUS_ADD_EXP:
		{
			m_i64Effect	|= KEEPEFFECT_ADD_EXP;
		}
		break;
	case	STATUS_ADJUST_EXP:
		{
			m_i64Effect |= KEEPEFFECT_ADJUST_EXP;
		}
		break;
	// 以下是结界系统相关的状态 ================
	case	STATUS_TEAMHEALTH:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_HEALTH;
		}
		break;
	case	STATUS_TEAMATTACK:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_ATTACK;
		}
		break;
	case	STATUS_TEAMDEFENCE:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_DEFENCE;
		}
		break;
	case	STATUS_TEAMSPEED:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_SPEED;
		}
		break;
	case	STATUS_TEAMEXP:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_EXP;
		}
		break;
	case	STATUS_TEAMSPIRIT:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_SPIRIT;
		}
		break;
	case	STATUS_TEAMCLEAN:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_i64Effect	|= KEEPEFFECT_TEAM_CLEAN;
		}
		break;
	// 以上是结界系统相关状态 ===============
	case	STATUS_HEAL:
		{
			m_i64Effect |= KEEPEFFECT_HEAL;
		}
		break;
	case	STATUS_FAINT:
		{
			m_i64Effect |= KEEPEFFECT_FAINT;
		}
		break;
	case	STATUS_TRUCULENCE:
		{
			m_i64Effect |= KEEPEFFECT_TRUCULENCE;
		}
		break;
	case	STATUS_DAMAGE:
		{
			m_i64Effect |= KEEPEFFECT_DAMAGE;
		}
		break;
	case	STATUS_ATKER_DAMAGE:
		{
			m_i64Effect |= KEEPEFFECT_ATKER_DAMAGE;
		}
		break;
	case	STATUS_CONFUSION:
		{
			m_i64Effect |= KEEPEFFECT_CONFUSION;
		}
		break;
	case	STATUS_FRENZY:
		{
			m_i64Effect |= KEEPEFFECT_FRENZY;
		}
		break;
	case	STATUS_EXTRA_POWER:
		{
			m_i64Effect |= KEEPEFFECT_EXTRA_POWER;
		}
		break;
	case	STATUS_SORB_REFLECT:
		{
			m_i64Effect |= KEEPEFFECT_SORB_REFLECT;

			m_tSorbReflect.Startup(SORB_REFLECT_SECS);
			m_nTotalDamage	= 0;
		}
		break;
	case	STATUS_FRENZY2:
		{
			m_i64Effect |= KEEPEFFECT_FRENZY2;
			m_nKillNum	= 0;
		}
		break;
	case	STATUS_LOCK:
		break;
	case	STATUS_SUPER_MATK:
		break;
	default:
		::LogSave("Invalid status: [%u]", nStatus);
//		ASSERT(!"switch status");
	}

	if (STATUS_FREEZE == nStatus || STATUS_FAINT == nStatus)
	{
		this->ClrAttackTarget();	// 停止自动战斗
	}

	if(bSynchro && i64OldEffect != m_i64Effect)
	{
		CMsgUserAttrib msg;
		if (msg.Create(GetID(), _USERATTRIB_KEEPEFFECT, m_i64Effect))
		{
			if (STATUS_MAXLIFE == nStatus)
			{
				msg.Append(_USERATTRIB_MAXLIFE, this->GetMaxLife());
				msg.Append(_USERATTRIB_LIFE, this->GetLife());
			}
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void CAiNpc::ClsStatus(int nStatus, bool bSynchro)
{
	I64 i64OldEffect = m_i64Effect;
	switch (nStatus)
	{
	case	STATUS_ADJUST_DODGE:
		{
			m_i64Effect	&= ~ STATUS_ADJUST_DODGE;
		}
		break;
	case	STATUS_ADJUST_XP:
		{
			m_i64Effect	&= ~ STATUS_ADJUST_XP;
		}
		break;
	case	STATUS_ADJUST_DROPMONEY:
		{
			m_i64Effect	&= ~ STATUS_ADJUST_DROPMONEY;
		}
		break;

	case	STATUS_NORMAL:
		{
			ASSERT(!"STATUS_NORMAL");
		}
		break;
	case	STATUS_DIE:
		{
			m_dwStatus	= nStatus;
			m_i64Effect	&= ~KEEPEFFECT_DIE;
		}
		break;
	case	STATUS_CRIME:
		{
			m_i64Effect	&= ~KEEPEFFECT_CRIME;
		}
		break;
	case	STATUS_SYNCRIME:
		{
			m_i64Effect	&= ~KEEPEFFECT_SYNCRIME;
		}
		break;
	case	STATUS_POISON:
		{
			m_i64Effect	&= ~KEEPEFFECT_POISON;
		}
		break;
	case	STATUS_DEFENCE1:
		{
			m_i64Effect	&= ~KEEPEFFECT_DEFENCE1;
		}
		break;
	case	STATUS_DEFENCE2:
		{
			m_i64Effect	&= ~KEEPEFFECT_DEFENCE2;
		}
		break;
	case	STATUS_DEFENCE3:
		{
			m_i64Effect	&= ~KEEPEFFECT_DEFENCE3;
		}
		break;
	case	STATUS_FREEZE:
		{
			m_i64Effect &= ~KEEPEFFECT_FREEZE;
		}
		break;
	case	STATUS_SMOKE:
		{
			m_i64Effect &= ~KEEPEFFECT_SMOKE;
		}
		break;
	case	STATUS_DARKNESS:
		{
			m_i64Effect &= ~KEEPEFFECT_DARKNESS;
		}
		break;
	case	STATUS_PALSY:
		{
			m_i64Effect &= ~KEEPEFFECT_PALSY;
		}
		break;
	case	STATUS_ATTACK:
		{
			m_i64Effect	&= ~KEEPEFFECT_ATTACK;
		}
		break;
	case	STATUS_MAGICDEFENCE:
		{
			m_i64Effect	&= ~KEEPEFFECT_MAGICDEFENCE;
		}
		break;
	case	STATUS_REFLECT:
		{
			m_i64Effect	&= ~KEEPEFFECT_REFLECT;
		}
		break;
	case	STATUS_REFLECTMAGIC:
		{
			m_i64Effect	&= ~KEEPEFFECT_REFLECTMAGIC;
		}
		break;
	case	STATUS_MAGICDAMAGE:
		{
			m_i64Effect	&= ~KEEPEFFECT_MAGICDAMAGE;
		}
		break;
	case	STATUS_ATKSPEED:
		{
			m_i64Effect	&= ~KEEPEFFECT_ATKSPEED;
		}
		break;
	case	STATUS_SLOWDOWN1:
		{
			m_i64Effect &= ~KEEPEFFECT_SLOWDOWN1;
		}
		break;
	case	STATUS_SLOWDOWN2:
		{
			m_i64Effect &= ~KEEPEFFECT_SLOWDOWN2;
		}
		break;
	case	STATUS_MAXLIFE:
		{
			m_i64Effect &= ~KEEPEFFECT_MAXLIFE;
		}
		break;
	case	STATUS_HIDDEN:
		{
			m_i64Effect &= ~KEEPEFFECT_HIDDEN;
		}
		break;
	case	STATUS_ADD_EXP:
		{
			m_i64Effect	&= ~KEEPEFFECT_ADD_EXP;
		}
		break;
	case	STATUS_ADJUST_EXP:
		{
			m_i64Effect &= ~KEEPEFFECT_ADJUST_EXP;
		}
		break;
	// 以下是结界系统相关的状态 ================
	case	STATUS_TEAMHEALTH:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_HEALTH;
		}
		break;
	case	STATUS_TEAMATTACK:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_ATTACK;
		}
		break;
	case	STATUS_TEAMDEFENCE:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_DEFENCE;
		}
		break;
	case	STATUS_TEAMSPEED:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_SPEED;
		}
		break;
	case	STATUS_TEAMEXP:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_EXP;
		}
		break;
	case	STATUS_TEAMSPIRIT:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_SPIRIT;
		}
		break;
	case	STATUS_TEAMCLEAN:
		{
			m_i64Effect	&= ~KEEPEFFECT_TEAM_CLEAN;
		}
		break;
	// 以上是结界系统相关状态 ===============
	case	STATUS_HEAL:
		{
			m_i64Effect &= ~KEEPEFFECT_HEAL;
		}
		break;
	case	STATUS_FAINT:
		{
			m_i64Effect &= ~KEEPEFFECT_FAINT;
		}
		break;
	case	STATUS_TRUCULENCE:
		{
			m_i64Effect &= ~KEEPEFFECT_TRUCULENCE;
		}
		break;
	case	STATUS_DAMAGE:
		{
			m_i64Effect &= ~KEEPEFFECT_DAMAGE;
		}
		break;
	case	STATUS_ATKER_DAMAGE:
		{
			m_i64Effect &= ~KEEPEFFECT_ATKER_DAMAGE;
		}
		break;
	case	STATUS_CONFUSION:
		{
			m_i64Effect &= ~KEEPEFFECT_CONFUSION;
		}
		break;
	case	STATUS_FRENZY:
		{
			m_i64Effect &= ~KEEPEFFECT_FRENZY;
		}
		break;
	case	STATUS_EXTRA_POWER:
		{
			m_i64Effect &= ~KEEPEFFECT_EXTRA_POWER;
		}
		break;
	case	STATUS_SORB_REFLECT:
		{
			m_i64Effect &= ~KEEPEFFECT_SORB_REFLECT;

			m_tSorbReflect.Clear();
			m_nTotalDamage	= 0;
		}
		break;
	case	STATUS_FRENZY2:
		{
			m_i64Effect &= ~KEEPEFFECT_FRENZY2;
			m_nKillNum	= 0;
		}
		break;
	case	STATUS_LOCK:
		break;
	case	STATUS_SUPER_MATK:
		break;
	default:
		::LogSave("Invalid status: [%u]", nStatus);
//		ASSERT(!"switch status");
	}

	if(bSynchro && i64OldEffect != m_i64Effect)
	{
		CMsgUserAttrib msg;
		if (msg.Create(GetID(), _USERATTRIB_KEEPEFFECT, m_i64Effect))
		{
			if (STATUS_MAXLIFE == nStatus)
			{
				msg.Append(_USERATTRIB_MAXLIFE, this->GetMaxLife());
				msg.Append(_USERATTRIB_LIFE, this->GetLife());
			}
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void CAiNpc::SaveInfo()
{
	/*if(m_pData)
	{
		m_pData->SetInt(PETDATA_LIFE, GetLife());
//		m_pData->SetInt(PETDATA_MANA, GetMana());
		m_pData->SetInt(PETDATA_RECORD_X, GetPosX());
		m_pData->SetInt(PETDATA_RECORD_Y, GetPosY());
		m_pData->Update();
	}*/
}

/////////////////////////////////////////////////////////////////////////////
bool CAiNpc::IsAlive()
{
	//if ((m_i64Effect & KEEPEFFECT_DIE) == KEEPEFFECT_DIE || this->GetLife() <= 0 || m_bLeaveMap)
	//	return false;

	if (m_bLeaveMap) return false;

	return true;
}

/*////////////////////////////////////////////////////////////////////////////
BOOL CAiNpc::CheckStatus(int nStatus)
{
	if (nStatus == STATUS_NORMAL || STATUS_DIE == nStatus)
	{
		if (m_dwStatus == nStatus)
			return true;
		else
			return false;
	}
	else
	{
		if ((m_dwStatus & nStatus) == nStatus)
			return true;
		else
			return false;
	}
}*/

/////////////////////////////////////////////////////////////////////////////
int CAiNpc::AdjustExp(IRole* pTarget, int nRawExp, bool bNewbieBonusMsg/*=false*/)
{
	CHECKF (pTarget);
	int nExp = nRawExp;

	// adjust
	nExp = 0; // CBattleSystem::AdjustExp(nExp, this->GetLev(), pTarget->GetLev());

	// 修炼界结增加组队获得的经验
	IStatus* pStatus = this->QueryStatus(STATUS_TEAMEXP);
	if (pStatus)
		nExp = ::CutTrail(0, MulDiv(nExp, 100+pStatus->GetPower(), 100));

	// 幸运 -- 增加战斗经验的状态
	pStatus = this->QueryStatus(STATUS_ADD_EXP);
	if (pStatus)
		nExp = ::CutTrail(0, MulDiv(nExp, 100+pStatus->GetPower(), 100));

	pStatus = this->QueryStatus(STATUS_ADJUST_EXP);
	if (pStatus)
		nExp = ::CutTrail(0, AdjustData(nExp, pStatus->GetPower()));

	return nExp;	
}

/////////////////////////////////////////////////////////////////////////////
void CAiNpc::AwardBattleExp		(int nExp, bool bGemEffect/*=true*/, bool bIncludeOwner/*=true*/)
{
	if(IsCallPet() && m_pOwner)
	{
		m_pOwner->AwardBattleExp(nExp, bGemEffect);
	}
}

/////////////////////////////////////////////////////////////////////////////
bool CAiNpc::IsInsteadMagic()
{
	return m_pMagicType && m_pMagicType->GetInt(MAGICTYPEDATA_SORT) == MAGICSORT_INSTEAD;
}

/////////////////////////////////////////////////////////////////////////////
OBJID CAiNpc::GetMasterID()
{
	if(IsCallPet() && m_pOwner)
		return m_pOwner->GetID();
	return ID_NONE;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::IsImmunity(IRole* pRole)
{
	CHECKF(pRole);

	if(IsCallPet() && m_pOwner)		// call pet of mine
		return m_pOwner->IsImmunity(pRole);

	const bool	ATK_IT = false;
	const bool	IMMUNITY = true;
	OBJID idRole = pRole->GetID();
	if(IsSceneID(idRole))		// is npc
	{
		if(pRole->IsBeAtkable())
			return ATK_IT;
		else
			return IMMUNITY;
	}
	else if(IsNpcID(idRole))	// is monster
	{
		if(IsEvil() && pRole->IsVirtuous() || IsVirtuous() && pRole->IsEvil())
			return ATK_IT;
		else
			return IMMUNITY;
	}
	else	// user
	{
		if(IsEvil())	// || IsGuard() && pUser->IsCrime() || IsPkKiller() && pUser->IsPker())
			return ATK_IT;
		else
			return IMMUNITY;
	}
}

//////////////////////////////////////////////////////////////////////
int  CAiNpc::AdjustAttack		(int nAtk)
{
	int	nAddAtk = 0;

	IStatus* pStatus = QueryStatus(STATUS_DEF2ATK);
	if (pStatus)
		nAddAtk += ::CutTrail(0, MulDiv(this->GetDef(), pStatus->GetPower(), 100));

	pStatus = QueryStatus(STATUS_ATTACK);
	if(pStatus)
		nAddAtk = ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower())) - nAtk;

	 pStatus = QueryStatus(STATUS_SUPER_ATK);
	if(pStatus)
		nAddAtk = ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower())) - nAtk;
	return nAtk + nAddAtk;
}

//////////////////////////////////////////////////////////////////////
int  CAiNpc::AdjustDefence		(int nDef)
{
	int	nAddDef = 0;

	IStatus* pStatus = QueryStatus(STATUS_DEF2ATK);
	if (pStatus)
		nAddDef += ::CutTrail(0, MulDiv(nDef, 100-__max(100, pStatus->GetPower()), 100)) - nDef;

	pStatus = QueryStatus(STATUS_DEFENCE3);
	if (!pStatus)
		pStatus = QueryStatus(STATUS_DEFENCE2);
	if (!pStatus)
		pStatus = QueryStatus(STATUS_DEFENCE1);
	if(pStatus)
		nAddDef = ::CutTrail(0, AdjustData(nDef, pStatus->GetPower())) - nDef;

	pStatus = QueryStatus(STATUS_SUPER_DEF);
	if(pStatus)
		nAddDef = ::CutTrail(0, AdjustData(nDef, pStatus->GetPower())) - nDef;

	return nDef + nAddDef;
}

/////////////////////////////////////////////////////////////////////////////
int CAiNpc::AdjustMagicDef(int nDef)
{
	int nAddDef = 0;

	IStatus* pStatus = QueryStatus(STATUS_SUPER_MDEF);
	if(pStatus)
		nAddDef += ::CutTrail(0, AdjustData(nDef, pStatus->GetPower()));

	pStatus = QueryStatus(STATUS_MAGICDEFENCE);
	if(pStatus)
		nAddDef += ::CutTrail(0, AdjustData(nDef, pStatus->GetPower()));

	return nDef;
}

//////////////////////////////////////////////////////////////////////
/*bool CAiNpc::DropTrap(TRAP_INFO &trapInfo, UINT ulLifePeriod)
{

	POINT	pos;
	pos.x	= GetPosX();
	pos.y	= GetPosY();

	if(GetMap()->FindDropItemCell(MONSTERDROPITEM_RANGE, &pos))
	{
		trapInfo.idOwner = 0;
		trapInfo.usPosX = pos.x;
		trapInfo.usPosY = pos.y;
		trapInfo.idMap = this->GetMap()->GetID();
		
		CMapTrap*	pTarp = CMapTrap::CreateNew(m_idProcess, &trapInfo);		
		if(pTarp)
		{			
			RoleManager()->QuerySet()->AddObj(pTarp->QueryRole());
			pTarp->SetLifePeriod(ulLifePeriod);
			return true;
		}
	}

	return false;
}*/

//////////////////////////////////////////////////////////////////////
int CAiNpc::GetNameType(int nAtkerLev, int nMonsterLev)
{
	int nDeltaLev = nAtkerLev - nMonsterLev;

	if (nDeltaLev >= 3)
		return NAME_GREEN;
	else if (nDeltaLev >= 0)
		return NAME_WHITE;
	else if (nDeltaLev >= -5)
		return NAME_RED;
	else
		return NAME_BLACK;
}

//////////////////////////////////////////////////////////////////////
bool CAiNpc::KickBack()
{
	// Monster不需要踢回，CallPet和Eudemon才需要
//	if (!((this->IsEudemon() || this->IsCallPet()) && m_pOwner))
//		return true;

	CMsgAction	msg;
	IF_OK (msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionKickBack, GetPosX(), GetPosY()))
		SendMsg(&msg);

	return true;
}

//////////////////////////////////////////////////////////////////////
int CAiNpc::AdjustWeaponDamage(int nDamage)
{
	return MulDiv(nDamage, GetDefence2(), DEFAULT_DEFENCE2);
}

//////////////////////////////////////////////////////////////////////
int CAiNpc::AdjustMagicDamage(int nDamage)
{
	IStatus* pStatus = QueryStatus(STATUS_MAGICDAMAGE);
	if(pStatus)
		nDamage = ::CutTrail(0, AdjustData(nDamage, pStatus->GetPower()));

	return nDamage;
}

//////////////////////////////////////////////////////////////////////
int CAiNpc::AdjustFrenzy2Dmg(int nDamage)
{
	IStatus* pStatus = QueryStatus(STATUS_FRENZY2);
	if (pStatus)
	{
		const int	KILLNUM_PER_DMGPERCENT	= 10;	// 每杀死10个目标增加1%伤害
		int nAddPercent = m_nKillNum / KILLNUM_PER_DMGPERCENT;
		nDamage = ::MulDiv(nDamage, __min(200, 100+nAddPercent), 100);
	}

	return nDamage;
}

//////////////////////////////////////////////////////////////////////
// 幻兽神识类型与攻击类型对潜力值的增减影响关系表
int	setAtkModePotential[EATK_MODE_LIMIT][MAX_DIVINE_ID] =
{
//	生命之神	混沌死神	公正之神	阴谋之神	智慧之神	战争之神	腐败之神	锻造之神
	{0,			0,			0,			0,			0,			0,			0,			0},		// ATK_MODE_NONE
	{-5,		5,			2,			-5,			-5,			5,			-3,			-2},	// ATK_MODE_ATK
	{-2,		-2,			5,			5,			5,			-2,			5,			5},		// ATK_MODE_ATKDEF
	{5,			-5,			-5,			-2,			2,			-5,			-3,			-2},	// ATK_MODE_DEF
};
