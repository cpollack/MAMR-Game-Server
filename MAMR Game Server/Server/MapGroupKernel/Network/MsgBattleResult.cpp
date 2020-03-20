// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "MsgBattleResult.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgBattleResult::CMsgBattleResult()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgBattleResult::~CMsgBattleResult()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattleResult::Create(BATTLERESULT mode, int money, int life, int mana, int rep, int exp, int petLife, int petLoyalty, int petExp)
{
	// init
	this->Init();

	// fill info now
	m_unMsgSize	= MSGSIZE;
	m_unMsgType	= _MSG_BATTLERESULT;

	m_pInfo->wMode = mode;

	m_pInfo->wMoney = money;
	m_pInfo->wUserLife = life;
	m_pInfo->wUserMana = mana;
	m_pInfo->dwReputation = rep;
	m_pInfo->dwUserExp = exp;

	m_pInfo->wPetLife = petLife;
	m_pInfo->wPetLoyalty = petLoyalty;
	m_pInfo->dwPetExp = petExp;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattleResult::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgBattleResult::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgBattleResult::Process");
}

