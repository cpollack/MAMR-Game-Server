// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgColor.h"

#include "../MapGroup.h"
#include "../UserManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgColor::CMsgColor()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgColor::~CMsgColor()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgColor::Create(CRole *pRole)
{
	CHECKF(pRole);

	// init
	this->Init();

	// fill info now
	m_unMsgSize	= 36;
	m_unMsgType	=_MSG_COLOR;

	m_pInfo->id = pRole->GetID();
	m_pInfo->count = 5; //can be 3 or 4

	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgColor::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgColor::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgColor::Process");
}

