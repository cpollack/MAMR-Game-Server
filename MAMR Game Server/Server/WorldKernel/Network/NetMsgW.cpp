// NetMsg.cpp: implementation of the CNetMsgW class.
//
//////////////////////////////////////////////////////////////////////
#define _WINSOCKAPI_
#include "AllMsg.h"
#include "basefunc.h"
#include "common.h"
#include "../WorldKernel.h"
using namespace world_kernel;
#include "../UserList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
world_kernel::CNetMsgW::CNetMsgW()
{
	Init();
}

world_kernel::CNetMsgW::~CNetMsgW()
{

}

//////////////////////////////////////////////////////////////////////
void world_kernel::CNetMsgW::Init()
{
	memset(m_bufMsg, 0L, sizeof(m_bufMsg));
	m_unMsgSize	=0;
	m_unMsgType	=_MSG_NONE;
}

//////////////////////////////////////////////////////////////////////
BOOL world_kernel::CNetMsgW::IsValid(void)
{
	if(_MSG_NONE == this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL world_kernel::CNetMsgW::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void world_kernel::CNetMsgW::Process(void *pInfo)
{
	//--------------------
	char szMsg[1024];
	sprintf(szMsg, "Process Msg:%d, Size:%d", m_unMsgType, m_unMsgSize);
	::LogSave(szMsg);	
}

//////////////////////////////////////////////////////////////////////
bool world_kernel::CNetMsgW::SendMsg(CNetMsgW* pMsg)
{
#ifdef _MYDEBUG
	::LogMsg("SendMsg:%d, size:%d", m_unMsgType, m_unMsgSize);

#endif
	if(!IsNpcMsg())
		return GameWorld()->SendClientMsg(m_idSocket, pMsg);
	else
		return GameWorld()->SendNpcMsg(m_idNpc, pMsg);
}

//////////////////////////////////////////////////////////////////////
// static functions;
//////////////////////////////////////////////////////////////////////
world_kernel::CNetMsgW* world_kernel::CNetMsgW::CreateClientMsg(PROCESS_ID idProcess, SOCKET_ID idSocket, OBJID idMsg,
										const char* pbufMsg, DWORD dwMsgSize, int nTrans)
{
	// check it...
	if(idMsg == _MSG_NONE || !pbufMsg || (int)dwMsgSize > GetMaxSize())
		return NULL;

	CNetMsgW* pMsg = CreateMsg(idMsg, pbufMsg, dwMsgSize);
	if(!pMsg)
		return NULL;

	pMsg->m_idProcess	= idProcess;
	pMsg->m_idSocket	= idSocket;
	pMsg->m_idNpc		= ID_NONE;
	pMsg->m_unMsgType	= idMsg;
	pMsg->m_unMsgSize	= dwMsgSize;
	pMsg->m_nTransData	= nTrans;

	if(!pMsg->CNetMsgW::Create((char*)pbufMsg, dwMsgSize))
	{
		SAFE_DELETE(pMsg);
		return NULL;
	}
	else
	{
	#ifdef _MYDEBUG
		::LogMsg("\n--Receive Msg:%u, Size:%u", pMsg->GetType(), pMsg->GetSize());
	#endif
		return pMsg;
	}
}

//////////////////////////////////////////////////////////////////////
world_kernel::CNetMsgW* world_kernel::CNetMsgW::CreateNpcMsg(PROCESS_ID idProcess, OBJID idNpc, OBJID idMsg,
										const char* pbufMsg, DWORD dwMsgSize, int nTrans)
{
	// check it...
	if(idMsg == _MSG_NONE || !pbufMsg || (int)dwMsgSize > GetMaxSize())
		return NULL;

	CNetMsgW* pMsg = CreateMsg(idMsg, pbufMsg, dwMsgSize);
	if(!pMsg)
		return NULL;

	pMsg->m_idProcess	= idProcess;
	pMsg->m_idSocket	= SOCKET_NONE;
	pMsg->m_idNpc		= idNpc;
	pMsg->m_unMsgType	= idMsg;
	pMsg->m_unMsgSize	= dwMsgSize;
	pMsg->m_nTransData	= nTrans;

	if(!pMsg->CNetMsgW::Create((char*)pbufMsg, dwMsgSize))
	{
		SAFE_DELETE(pMsg);
		return NULL;
	}
	else
	{
	#ifdef _MYDEBUG
		::LogMsg("\n--Receive Msg:%u, Size:%u", pMsg->GetType(), pMsg->GetSize());
	#endif
		return pMsg;
	}
}

world_kernel::CNetMsgW* world_kernel::CNetMsgW::CreateMsg(OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize)
{
	// make it...
	CNetMsgW* pMsg	=NULL;
	switch(idMsg)
	{
	case _MSG_TALK:
		pMsg	=new CMsgTalkW;
		break;
	case _MSG_MESSAGEBOARD:
		pMsg	=new CMsgMessageBoard;
		break;
	case _MSG_REGISTER:
		pMsg	=new CMsgRegister;
		break;
	case _MSG_LOGIN:
		pMsg	=new CMsgLogin;
		break;
	/*case _MSG_AINPCINFO:
		pMsg	=new CMsgAiNpcInfo;
		break;*/
	case _MSG_CONNECT:
		pMsg	=new CMsgConnect;
		break;
	case _MSG_TIME:
		pMsg	=new CMsgTime;
		break;
	case _MSG_NAME:
		pMsg	=new CMsgNameW;
		break;
	case _MSG_FRIEND:
		pMsg	=new CMsgFriendW;
		break;
	case _MSG_DIALOG:
		pMsg	=new CMsgDialogW;
		break;
//	case _MSG_CHATROOM:
//		pMsg	=new CMsgChatRoom;
//		break;
	default:
		break;
	}
	return pMsg;
}
