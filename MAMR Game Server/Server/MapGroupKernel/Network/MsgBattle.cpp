// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgBattle.h"

#include "../MapGroup.h"
#include "../UserManager.h"
#include "../Battle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgBattle::CMsgBattle()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgBattle::~CMsgBattle()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattle::Create(OBJID userID, BATTLESTATE state, int actors, int formation)
{
	CHECKF(userID);

	// init
	this->Init();

	// fill info now
	m_unMsgSize	= MSGSIZE;
	m_unMsgType	=_MSG_BATTLE;

	m_pInfo->bState = state;
	m_pInfo->bActors = actors;
	m_pInfo->idUser = userID;
	m_pInfo->dwFormation = formation;
	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattle::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgBattle::Process(CGameSocket* pSocket)
{
	CUser* pUser = UserManager()->GetUser(m_pInfo->idUser);
	if (!pUser) return;

	//only handling new battle requests to start
	if (m_pInfo->bState == BATTLESTATE_START) {
		//verify if user is in a battle
		//team?
		//create new NPC battle
		//have battle send init data to team

		CBattle *pBattle = CBattle::CreateNpcBattle(m_idProcess, pUser);
		pUser->SetBattle(pBattle);
	}

	ASSERT(!"CMsgBattle::Process");
}

