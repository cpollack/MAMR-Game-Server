// MsgCallPetInfo.cpp: implementation of the CMsgCallPetInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgPetAction.h"
#include "../MapGroup.h"
#include "../Pet.h"

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
BOOL CMsgPetAction::Create(OBJID petID, DWORD dwData, PETACTION action)
{
	CHECKF(petID);

	// init
	this->Init();

	// fill info now
	m_unMsgSize	=sizeof(MSG_Info);
	m_unMsgType	=_MSG_PETACTION;

	m_pInfo->petID = petID;
	m_pInfo->dwData = dwData;
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
	CUserPtr pUser = UserManager()->GetUser(this);
	CHECK(pUser);

	try {
	switch (m_pInfo->dwAction)
	{
	case PETACTION_USEITEM:
	{
		CPet* pPet = pUser->GetPet(m_pInfo->petID);
		if (pPet) {
			pPet->UseItem(m_pInfo->dwData, SYNCHRO_TRUE);
		}
	} break;
	}
	}catch (...)
	{
		::LogSave("switch(MSGPETACTION) Action [%d], id [%u]", m_pInfo->dwAction, m_pInfo->petID);
	}

#ifdef _MSGDEBUG
	::LogMsg("Process CMsgPetAction, id:%u", m_pInfo->petID);
#endif
}

