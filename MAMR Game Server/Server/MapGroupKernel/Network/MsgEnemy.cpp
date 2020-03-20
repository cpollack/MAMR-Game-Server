// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgEnemy.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgEnemy::CMsgEnemy()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgEnemy::~CMsgEnemy()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgEnemy::Create(CBattle::FIGHTER_SET enemies)
{
	// init
	this->Init();

	m_unMsgType	= _MSG_ENEMY;

	m_pInfo->dwCount = enemies.size();

	for (int i = 0; i < m_pInfo->dwCount; i++) {
		m_pInfo->enemy[i].id = enemies[i]->GetID();
		m_pInfo->enemy[i].look = enemies[i]->GetRole()->GetLook();
		m_pInfo->enemy[i].level = enemies[i]->GetRole()->GetLev();
		//memcpy(m_pInfo->enemy[i].name, enemies[i]->GetName(), sizeof(NAMESTR));
		strcpy(m_pInfo->enemy[i].name, enemies[i]->GetRole()->GetName());
	}

	m_unMsgSize = MSGSIZE - (sizeof(ENEMYINFO) * (10 - m_pInfo->dwCount));
	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgEnemy::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgEnemy::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgEnemy::Process");
}

