// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgBattleAct.h"

#include "../MapGroup.h"
#include "../UserManager.h"
#include "../Battle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgBattleAct::CMsgBattleAct()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgBattleAct::~CMsgBattleAct()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattleAct::Create(int act, int round, OBJID source, OBJID target, OBJID use, CUser* pUser)
{
	CHECKF(source);

	// init
	this->Init();

	// fill info now
	m_unMsgSize	= MSGSIZE;
	m_unMsgType	=_MSG_BATTLEACT;

	m_pInfo->bAct = act;
	m_pInfo->bRound = round;
	m_pInfo->idSource = source;
	m_pInfo->idTarget = target;
	m_pInfo->idUsing = use;
	
	m_pInfo->dwVerify = (pUser->GetAccountID() ^ pUser->GetID()) + pUser->GetID() * (act + 8210 - round);

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattleAct::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgBattleAct::Process(CGameSocket* pSocket)
{
	CUser *pUser = UserManager()->GetUser(this);
	if (!pUser) {
		ASSERT("Invalid pUser");
		return;
	}

	CBattle *pBattle = pUser->GetBattle();
	if (!pBattle) {
		ASSERT("Invalid pBattle");
		return;
	}

	pBattle->AddBattleAction((BATTLEACT)m_pInfo->bAct, m_pInfo->idSource, m_pInfo->idTarget, m_pInfo->idUsing);

	ASSERT(!"CMsgBattleAct::Process");
}

