// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgNormalAct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgNormalAct::CMsgNormalAct()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgNormalAct::~CMsgNormalAct()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNormalAct::Create(int act, int group, BYTE srcState, BYTE trgState, OBJID source, OBJID target, WORD dmg, WORD heal, BYTE interact, BYTE unk)
{
	// init
	this->Init();

	// fill info now
	m_unMsgSize	= MSGSIZE;
	m_unMsgType	= _MSG_NORMALACT;

	m_pInfo->bAct = act;
	m_pInfo->bGroup = group;
	m_pInfo->bStateSource = srcState;
	m_pInfo->bStateTarget = trgState;
	m_pInfo->idSource = source;
	m_pInfo->idTarget = target;
	m_pInfo->wDamage = dmg;
	m_pInfo->wHeal = heal;
	m_pInfo->bInteraction = interact;
	m_pInfo->bUnknown = unk;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNormalAct::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgNormalAct::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgNormalAct::Process");
}

