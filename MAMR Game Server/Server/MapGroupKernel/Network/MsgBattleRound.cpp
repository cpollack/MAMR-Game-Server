// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "MsgBattleRound.h"

#include "../Battle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgBattleRound::CMsgBattleRound()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgBattleRound::~CMsgBattleRound()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattleRound::Create(FIGHTER_SET* teamA, FIGHTER_SET* teamB)
{
	if (!teamA || !teamB) {
		ASSERT("CMsgBattleRound invalid team pointers");
		return false;
	}

	// init
	this->Init();

	// fill info now
	m_unMsgSize	= MSGSIZE;
	m_unMsgType	= _MSG_BATTLEROUND;

	int i = 0;
	for (int idx = 0; idx < teamA->size(); idx++) if (!(*teamA)[idx]->GetRanAway()) m_pInfo->bState[i++] = (*teamA)[idx]->GetState();
	for (int idx = 0; idx < teamB->size(); idx++) if (!(*teamB)[idx]->GetRanAway())  m_pInfo->bState[i++] = (*teamB)[idx]->GetState();
	if (i < 20) {
		for (; i < 20; i++) m_pInfo->bState[i] = 0;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgBattleRound::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgBattleRound::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgBattleRound::Process");
}

