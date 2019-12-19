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
CMsgRole::CMsgRole()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgRole::~CMsgRole() {
	//
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgRole::Create(const char* pszNickname, const char* pszName,
	USHORT usPointLife, USHORT usPointDefence, USHORT usPointAttack, USHORT usPointDexterity, USHORT usPointMana,
	UCHAR ucRole, UCHAR ucFace, DWORD dwRecordMap, const BYTE* pbColorSet)
{
	// check param
	if(!pszNickname || strlen(pszNickname) >= _MAX_NAMESIZE)
		return false;

	if(!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return false;

	// init
	this->Init();
	
	// fill structure
	m_unMsgType	=_MSG_ROLE;
	m_unMsgSize	=sizeof(MSG_Info);

	strcpy(m_pInfo->szNickname, pszNickname);
	strcpy(m_pInfo->szName, pszName);

	m_pInfo->usPointLife = usPointLife;
	m_pInfo->usPointDefence = usPointDefence;
	m_pInfo->usPointAttack = usPointAttack;
	m_pInfo->usPointDexterity = usPointDexterity;
	m_pInfo->usPointMana = usPointMana;

	m_pInfo->ucRole = ucRole;
	m_pInfo->ucFace = ucFace;
	m_pInfo->dwRecordMap = dwRecordMap;

	if (pbColorSet) memcpy(m_pInfo->bColorSet, pbColorSet, 25);

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgRole::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsgW::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_LOGIN != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgRole::Process(void *pInfo) {
	//receving a role means the user is attempting to create a character
}









