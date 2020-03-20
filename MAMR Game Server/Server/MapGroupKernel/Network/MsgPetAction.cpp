// MsgCallPetInfo.cpp: implementation of the CMsgCallPetInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgPetAction.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgPetAction::CMsgPetAction()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgPetAction::~CMsgPetAction()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPetAction::Create(OBJID petID, OBJID useID, PETACTION action)
{
	CHECKF(petID);

	// init
	this->Init();

	// fill info now
	m_unMsgSize	=sizeof(MSG_Info);
	m_unMsgType	=_MSG_PETACTION;

	m_pInfo->petID = petID;
	m_pInfo->useID = useID;
	m_pInfo->dwAction = action;
	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPetAction::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgPetAction::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgPetAction::Process");
}

