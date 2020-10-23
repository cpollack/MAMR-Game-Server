// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"

#include "../User.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgUserLevelUp::CMsgUserLevelUp()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
}

CMsgUserLevelUp::~CMsgUserLevelUp()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgUserLevelUp::Create(CUser* pUser)
{
	CHECKF(pUser);

	// init
	this->Init();

	// fill info now
	m_unMsgSize = MSGSIZE;
	m_unMsgType = _MSG_USERLEVELUP;

	m_pInfo->userID = pUser->GetID();
	m_pInfo->exp = pUser->GetExp();
	m_pInfo->level = pUser->GetLev();
	m_pInfo->attributes = pUser->GetAddPoint();

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgUserLevelUp::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgUserLevelUp::Process(CGameSocket* pSocket)
{
	//No action

	ASSERT(!"CMsgUserLevelUp::Process");
}

