// MsgAction.cpp: implementation of the CMsgAction class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#include "../mapgroup.h"
#include "../transformation.h"
#include "../Agent.h"
//#include "MercenaryTask.h"
#include "../User.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgDirection::CMsgDirection()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgDirection::~CMsgDirection()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgDirection::Create(OBJID idPlayer, int nPosX, int nPosY, USHORT usDir)
{
	// param check
	if (idPlayer == ID_NONE)
		return false;

	// init
	this->Init();

	// fill info now
	m_unMsgSize	=sizeof(MSG_Info);
	m_unMsgType	=_MSG_DIRECTION;

	m_pInfo->idUser		=idPlayer;
	m_pInfo->unPosX		=(USHORT)nPosX;
	m_pInfo->unPosY		=(USHORT)nPosY;
	m_pInfo->dwDir		=usDir;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgDirection::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_DIRECTION != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgDirection::Process(void *pInfo)
{
#ifdef _MSGDEBUG
	::LogMsg("Process CMsgDirection, idUser:%u",
					m_pInfo->idUser);
#endif

	// get obj
	IRole* pRole	= RoleManager()->QueryRole(this, m_pInfo->idUser);
	if (!pRole)
	{
		return;
	}

	pRole->SetDir(m_pInfo->dwDir);
	pRole->BroadcastRoomMsg(this, EXCLUDE_SELF);
}
