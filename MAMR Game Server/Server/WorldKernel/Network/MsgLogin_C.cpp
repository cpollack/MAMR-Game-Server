// MsgLogin.cpp: implementation of the CMsgLogin class.
//
//////////////////////////////////////////////////////////////////////

#include "MessagePort.h"
#include "protocol.h"
#include "define.h"
#include "AllMsg.h"
#include "../WorldKernel.h"
using namespace world_kernel;
#include "../UserList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgLogin_C::CMsgLogin_C()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
}

CMsgLogin_C::~CMsgLogin_C()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgLogin_C::Create(OBJID idAccount, DWORD dwCheckData, char* pszName, USHORT usVersion)
{
	// check param
	if (!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return false;

	// init
	this->Init();

	// fill structure
	m_unMsgType = _MSG_LOGIN;
	m_unMsgSize = sizeof(MSG_Info);

	m_pInfo->idAccount = idAccount;
	m_pInfo->dwCheckData = dwCheckData;
	m_pInfo->usVersion = usVersion;
	strcpy(m_pInfo->szUserName, pszName);
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgLogin_C::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsgW::Create(pbufMsg, dwMsgSize))
		return false;

	if (_MSG_LOGIN != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgLogin_C::Process(void *pInfo)
{

#ifdef _MSGDEBUG
	::LogMsg("Process CMsgLogin, Account:%d, Name:%s",
		m_pInfo->idAccount,
		m_pInfo->szUserName);
#endif
	/* ÎÞÕÊºÅ·þÎñÆ÷Ê±£¬Íæ¼ÒµÇÂ¼´úÂë
	#ifdef	ACCOUNT_ENABLE
	return ;				// ´ÓÕÊºÅ·þÎñÆ÷µÇÂ¼£¬¸ÃÏûÏ¢²»´¦Àí!
	#endif
	if(m_pInfo->dwVersion < GAME_VERSION)
	{
	CMsgTalk	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, "´íÎó£º°æ±¾ºÅ´íÎó!", NULL, _COLOR_WHITE, _TXTATR_ENTRANCE))
	SendMsg(&msg);
	return;
	}

	CPlayer*	pPlayer;
	if(pPlayer = g_UserList.GetPlayerByAccount(m_pInfo->szAccount))
	{
	GameWorld()->GetSocketInterface()->CloseSocket(pPlayer->idSocket);

	CMsgTalk	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, "´íÎó£º¿¨ºÅ£¬ÇëÖØÐÂµÇÂ¼!", NULL, _COLOR_WHITE, _TXTATR_ENTRANCE))
	SendMsg(&msg);
	GameWorld()->GetSocketInterface()->CloseSocket(GetSocketID());		// ¹Ø±Õ×Ô¼º
	return;
	}

	if(!g_UserList.LoginUser(m_pInfo->szAccount, m_pInfo->szPassword, m_idSocket))
	{
	CMsgTalk	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, "´íÎó£ºÕÊºÅ»òÃÜÂë´íÎó!", NULL, _COLOR_WHITE, _TXTATR_ENTRANCE))
	SendMsg(&msg);
	return;
	}

	pPlayer	= g_UserList.GetPlayerByAccount(m_pInfo->szAccount);
	if(!pPlayer)
	return;

	UserList()->LoginToMapGroup(pPlayer);
	*/
}










