// Body.cpp: implementation of the CBody class.
//
//////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "Body.h"
#include "Array.h"
#include "Vartype.h"
#include "AGent.h"
#include "AGentData.h"
#include "AllMsg.h"
#include "NpcWorld.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBody::CBody()
{

}

CBody::~CBody()
{

}

bool CBody::Create(CAgent* pOwner)
{
	m_pOwner	= pOwner;

	return true;
}

void CBody::OnTimer()
{
	IAiCenter* pAi = Cast<IAiCenter>(m_pOwner);
	CHECK(pAi);
	int idxAction;
	VarTypeSet setParam;
	if(pAi->FetchAction(&idxAction, &setParam))
	{
		DEBUG_TRY
		ProcessAction(idxAction, setParam);
		DEBUG_CATCH2("CBody::OnTimer(): %d", idxAction)
	}
}

bool CBody::ProcessAction(int idxAction, VarTypeSetRef setParam)
{
	CHECKF(idxAction >= 0);

	switch(idxAction)
	{
	case	ACTION_REBORN:						// "Reborn":
		{
			CMsgAction	msg;
			IF_OK(msg.Create(m_pOwner->GetID(), m_pOwner->GetPosX(), m_pOwner->GetPosY(), m_pOwner->GetDir(), actionReborn))
				m_pOwner->SendMsg(&msg);
		}
		break;
	case	ACTION_TALK_TO_NAME:				// "TalkToName",				// (name,str)
		{
			StringRef	szName	= setParam[0];
			StringRef	szMsg	= setParam[1];
			CUser* pRole = UserManager()->QueryUser(szName);
			if(pRole)
			{
				CMsgTalk	msg;
				IF_OK(msg.Create(m_pOwner->GetName(), szName, szMsg))
					m_pOwner->SendMsg(&msg);
			}
		}
		break;
	case	ACTION_TALK_TO_ID:					// "TalkToID",					// (id,str)
		{
			OBJID		idRole	= setParam[0];
			StringRef	szMsg	= setParam[1];
			CUser* pRole = UserManager()->QueryUser(idRole);
			if(pRole)
			{
				CMsgTalk	msg;
				IF_OK(msg.Create(m_pOwner->GetName(), pRole->GetName(), szMsg))
					m_pOwner->SendMsg(&msg);
			}
		}
		break;
	case	ACTION_MOVE_CLOSE:					// "MoveCloseTarget":			// (id)���ߵ��ܹ����Է��ľ��롣
		{
			OBJID	idRole = setParam[0];
			IRole* pRole = UserManager()->QueryRole(idRole);
			CRoleMove* pMove;
			if(pRole && Cast(&pMove, m_pOwner))
			{
				if(::RandGet(3) == 0)
					pMove->JumpTo(pRole->GetPosX(), pRole->GetPosY(), m_pOwner->GetAttackRange(pRole->GetSizeAdd()));
				else
					pMove->RunTo(pRole->GetPosX(), pRole->GetPosY(), m_pOwner->GetAttackRange(pRole->GetSizeAdd()));
			}
		}
		break;
	case	ACTION_JUMP_CLOSE:					// "JumpClose":			// (x,y,dist)���ߵ���Է�һ���ľ��롣
		{
			int		nPosX = setParam[0];
			int		nPosY = setParam[1];
			int		nDist = setParam[2];
			CRoleMove* pMove = Cast<CRoleMove>(m_pOwner);
			if(pMove)
			{
				pMove->JumpTo(nPosX, nPosY, nDist);
			}
		}
		break;
	case	ACTION_JUMP_TO_SAFE:				// "JumpToSafePos":			// ������ȫ�ĵط�����ֹ���ְ�Χ
		{
			CRoleMove* pMove;
			if(Cast(&pMove, m_pOwner))
			{
				pMove->JumpSafePos();
			}
		}
		break;
	case	ACTION_CHGMAP:						// "ChangeMapTo",				// (id,x,y)�ó�������ص�SHOP����(���ƻسǾ�)
		{
			OBJID	idMap = setParam[0];
			int		nPosX = setParam[1];
			int		nPosY = setParam[2];
			CMsgAction	msg;
			IF_OK(msg.Create(m_pOwner->GetID(), nPosX, nPosY, m_pOwner->GetDir(), actionSuperChgMap, idMap))
				m_pOwner->SendMsg(&msg);
		}
		break;
	case	ACTION_RANDOM_WALK:					// "RandomWalk":				// ����
		{
			CRoleMove* pMove;
			if(Cast(&pMove, m_pOwner))
			{
				POINT	pos = pMove->FindRandomPos();
				if(m_pOwner->GetMap()->IsJumpEnable(pos.x, pos.y))
					pMove->WalkTo(pos.x, pos.y);
			}
		}
		break;
	case	ACTION_CHANGE_MODE:					// "ChangeMode",				// �޸�Mode(_,_)����action��ʵ��д��������ʵ��
		{
			int	nMode1 = setParam[0];
			int	nMode2 = setParam[1];

			int		nPriority	= 0;
			String	strFact = "Mode";					// (e,e)			// 0
			strFact	+= '(';
			strFact	+= String().FormatLong(nMode1);
			strFact	+= ',';
			strFact	+= String().FormatLong(nMode2);
			strFact	+= ')';

			IAiCenter* pAi = Cast<IAiCenter>(m_pOwner);
			pAi->AddFact(strFact, nPriority);

			LOGDUMP("ChangeMode to [%d,%d] OK! ===============================================", nMode1, nMode2);
		}
		break;
	case	ACTION_LEAVE_EVIL:					// "KeepOutEnemy":				// (dist)������˱��־��룬����
		{
			int	nDist = setParam[0];
			CRoleMove* pMove;
			if(Cast(&pMove, m_pOwner))			// && m_pOwner->GetMapID() == SHOP_MAP_ID
			{
				if(pMove->JumpSafePos(nDist))
					return true;

				POINT pos = pMove->FindRandomPos();
				if(m_pOwner->GetMap()->IsJumpEnable(pos.x, pos.y))
				{
					pMove->JumpTo(pos.x, pos.y);
					return true;
				}
			}
		}
		break;
	case	ACTION_ATTACK:						// "AttackRole":				// (id)
		{
			OBJID	idRole = setParam[0];
			IRole* pRole = UserManager()->QueryRole(idRole);
			CRoleFight* pFight;
			if(pRole && Cast(&pFight, m_pOwner))
			{
				pFight->Attack(pRole);
			}
		}
		break;
	case	ACTION_USE_ITEM:					// "UseItem":					// (type)��һ��ҩ
		{
			OBJID	idType = setParam[0];
			CItemPack* pPack = Cast<CItemPack>(m_pOwner);
			CItem* pItem = pPack->FindItemByType(idType);
			if(pItem)
			{
				CMsgItem	msg;
				IF_OK(msg.Create(pItem->GetID(), ITEMACT_USE))
					m_pOwner->SendMsg(&msg);
			}
		}
		break;
	case	ACTION_FULL_MEDICINE:				// "FullMedicine":				// (type)��SHOP��װ��ҩ
		{
			OBJID	idItem = setParam[0];
			CMsgAction	msg;
			IF_OK(msg.Create(m_pOwner->GetID(), m_pOwner->GetPosX(), m_pOwner->GetPosY(), m_pOwner->GetDir(), actionFullItem, idItem))
				m_pOwner->SendMsg(&msg);
			LOGDUMP("ACTION_FULL_MEDICINE");
		}
		break;
	case	ACTION_ACCEPT_INVITE:				// "AcceptTeamInvite":			// (id)
		{
			OBJID	idRole = setParam[0];
			CMsgTeam	msg;
			IF_OK(msg.Create(idRole, _MSGTEAM_ACCEPTINVEIT))
				m_pOwner->SendMsg(&msg);
		}
		break;
	case	ACTION_SEND_APPLY:					// "SendTeamApply":				// (id)
		{
			OBJID	idRole = setParam[0];
			CMsgTeam	msg;
			IF_OK(msg.Create(idRole, _MSGTEAM_APPLYJOIN))
				m_pOwner->SendMsg(&msg);
		}
		break;
	case	ACTION_LEAVE_TEAM:					// "LeaveTeam":
		{
			CMsgTeam	msg;
			IF_OK(msg.Create(m_pOwner->GetID(), _MSGTEAM_LEAVE))
				m_pOwner->SendMsg(&msg);
		}
		break;
	default:
		ASSERT(!"switch(idxAction)");
	}

	return false;
}
