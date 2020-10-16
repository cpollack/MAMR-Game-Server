// MsgNpc.cpp: implementation of the CMsgNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "../Npc.h"
#include "../NpcManager.h"
#include "../GameMap.h"
#include "../MapGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgNpcAction::CMsgNpcAction()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgNpcAction::~CMsgNpcAction()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNpcAction::Create(int nOption, int nAction)
{
	// init
	this->Init();

	// fill info now
	m_unMsgSize	=sizeof(MSG_Info);
	m_unMsgType	=_MSG_NPCACTION;

	m_pInfo->nOption = nOption;
	m_pInfo->nAction	= (unsigned short)nAction;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNpcAction::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgNpcAction::Process(CGameSocket* pSocket)
{
#ifdef _MYDEBUG
	::LogSave("Process CMsgName, id:%u, usAction:%u", 
		m_pInfo->id,
		m_pInfo->usAction);

#endif

	if (!pSocket)
		return;

	CUserPtr pUser	= UserManager()->GetUser(this);
	if (!pUser)
		return ;

	if(!pUser->IsAlive())
	{
		pUser->SendSysMsg(STR_DIE);
		return ;
	}

	switch(m_pInfo->nAction)
	{
	case NPC_ACT_DIALOGUERESPONSE:
		{
			pUser->ProcessDialogueTask(m_pInfo->nOption);
		}
		break;

	default:
		::LogSave("ERROR: CMsgNpcAction::Process() Action[%u]", m_pInfo->nAction);
	}
}

