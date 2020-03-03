// MsgAction.cpp: implementation of the CMsgWalk class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#include "../mapgroup.h"
#include "../transformation.h"
#include "../I_Role.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgWalk::CMsgWalk()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgWalk::~CMsgWalk()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgWalk::Create(OBJID idPlayer, int nDir, int nMode /*= MOVEMODE_WALK*/)
{
	// param check
	if (idPlayer == ID_NONE)
		return false;

	// init
	this->Init();

	// fill info now
	m_unMsgSize	=sizeof(MSG_Info);
	m_unMsgType	=_MSG_WALK;

	m_pInfo->idUser		=idPlayer;
	//m_pInfo->ucDir		=nDir;
	//m_pInfo->ucMode		=nMode;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgWalk::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_WALK != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgWalk::Process(void *pInfo)
{
	DEBUG_TRY
#ifdef _MSGDEBUG
	::LogMsg("Process CMsgWalk, idUser:%u, data:%u",
					m_pInfo->idUser,
					m_pInfo->dwData);
#endif

	// get obj
	IRole* pRole	= RoleManager()->QueryRole(this, m_pInfo->idUser);
	if(!pRole)
	{
		if(!this->IsNpcMsg())
			LOGERROR("CMsgWalk��Ϣû���ҵ���ң�SOCKET_ID[%u],NPC_ID[%u]", GetSocketID(), GetNpcID());
		return ;
	}
	//xxxCHECK(pRole->GetID() == m_pInfo->idUser);

	pRole->BroadcastRoomMsg(this);

	/*int nDir = m_pInfo->ucDir%8;
	int nNewX = pRole->GetPosX()+_DELTA_X[nDir];
	int nNewY = pRole->GetPosY()+_DELTA_Y[nDir];

	CUser* pUser = NULL;
	if(pRole->QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		if(!pRole->IsAlive() && !pUser->IsGhost())
		{
			pRole->SendSysMsg(STR_DIE);
			return ;
		}
		if (pUser->QueryTransformation() && !pUser->QueryTransformation()->IsMoveEnable())		// BUG: �ձ�ʱ���ͻ��˻�û����
		{
			pUser->SendSysMsg(STR_YOUR_CANNOT_WALK);
			pUser->KickBack();
			//UserManager()->KickOutSocket(m_idSocket, "�����ߣ�");
			return;
		}
		if (pUser->QueryStatus(STATUS_LOCK) || pUser->QueryStatus(STATUS_FREEZE)
			|| pRole->QueryStatus(STATUS_FAINT))
		{
			pUser->KickBack();
#ifdef ZLONG_DEBUG
			pUser->SendSysMsg("Debug: �����ƶ���");
#endif
			return;
		}
		if (pUser->QueryMagic() && pUser->QueryMagic()->IsInLaunch())
		{
			pUser->KickBack();
#ifdef	ZLONG_DEBUG
			pUser->SendSysMsg("Debug: ħ��ʩչ�У��߻ء�");
#endif
			return;
		}
		if (pUser->QueryMagic() && pUser->QueryMagic()->IsIntone())
		{
			pUser->QueryMagic()->AbortMagic();
		}
		if(pUser->IsAlive() && !pUser->GetMap()->IsMoveEnable(nNewX, nNewY))
		{
			pUser->KickBack();
#ifdef	LOCAL_DEBUG
			pUser->SendSysMsg("�赲��(%d,%d)", nNewX, nNewY);
#endif
			return;
		}
		// �ܲ�ģʽ���赲�ж�
		if (m_pInfo->ucMode >= MOVEMODE_RUN_DIR0 && m_pInfo->ucMode <= MOVEMODE_RUN_DIR7)
		{
			nNewX += _DELTA_X[m_pInfo->ucMode - MOVEMODE_RUN_DIR0];
			nNewY += _DELTA_Y[m_pInfo->ucMode - MOVEMODE_RUN_DIR0];

			if(pUser->IsAlive() && !pUser->GetMap()->IsMoveEnable(nNewX, nNewY))
			{
				pUser->KickBack();
#ifdef	LOCAL_DEBUG
				pUser->SendSysMsg("�赲��(%d,%d)", nNewX, nNewY);
#endif
				return;
			}
		}
	}
	else
	{
		if(!pRole->IsAlive())
			return ;
		CMonster* pMonster = NULL;
		if (pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)))
		{
			if (!pRole->GetMap())
				return ;
			if (!pRole->GetMap()->IsMoveEnable(nNewX, nNewY))
			{
				pMonster->KickBack();
#ifdef LOCAL_DEBUG
				::LogSave("Kick back monster from (%d, %d) [ID=%u].", nNewX, nNewY, pMonster->GetID());
#endif
				return;
			}
			if (m_pInfo->ucMode >= MOVEMODE_RUN_DIR0 && m_pInfo->ucMode <= MOVEMODE_RUN_DIR7)
			{
				nNewX += _DELTA_X[m_pInfo->ucMode - MOVEMODE_RUN_DIR0];
				nNewY += _DELTA_Y[m_pInfo->ucMode - MOVEMODE_RUN_DIR0];

				if (!pRole->GetMap()->IsMoveEnable(nNewX, nNewY))
				{
					pMonster->KickBack();
#ifdef LOCAL_DEBUG
					::LogSave("Kick back monster from (%d, %d) [ID=%u].", nNewX, nNewY, pMonster->GetID());
#endif
					return;
				}
			}
		}
	}*/

	/*DEBUG_TRY
	// stop fight
	if(m_pInfo->ucMode != MOVEMODE_SHIFT)
		pRole->ProcessOnMove(m_pInfo->ucMode);
	DEBUG_CATCH("ProcessOnMove")*/

	// fill id
	//DEBUG_TRY
//*
//	pRole->BroadcastRoomMsg(this, EXCLUDE_SELF);

	/*{
		CMsgWalkEx msg;
		IF_OK(msg.Create(m_pInfo->idUser, m_pInfo->ucDir, m_pInfo->ucMode, nNewX, nNewY))
		{
//			pRole->SendMsg(&msg);
			pRole->BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}*/
//*/
/*else
	pRole->SendMsg(this);
//*/
	/*bool bRunMode = (m_pInfo->ucMode >= MOVEMODE_RUN_DIR0 && m_pInfo->ucMode <= MOVEMODE_RUN_DIR7);
	pRole->MoveToward(nDir, !bRunMode);		// return true: ��n��ģ��
	// ����ǣ��ܲ�ģʽ���ƶ��ڶ���
	if (bRunMode)
		pRole->MoveToward(m_pInfo->ucMode - MOVEMODE_RUN_DIR0);

	DEBUG_CATCH("MoveToward")

#ifdef	PALED_DEBUG_X
	MSGBUF	szMsg;
	if(IsNpcID(pRole->GetID()))
		sprintf(szMsg, "%s%06dWALK: (%d,%d)", pRole->GetName(), pRole->GetID(), pRole->GetPosX(), pRole->GetPosY());
	else
		sprintf(szMsg, "%sWALK: (%d,%d)", pRole->GetName(), pRole->GetPosX(), pRole->GetPosY());
	//LOGWARNING(szMsg);
	DebugSave(szMsg);
#endif*/
	DEBUG_CATCH("CMsgWalk::Process")
}
