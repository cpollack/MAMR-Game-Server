#pragma once

#include "NetMsg.h"

class CFighter;
typedef std::vector<CFighter*> FIGHTER_SET;

class CMsgBattleRound : public CNetMsg
{
public:
	CMsgBattleRound();
	virtual ~CMsgBattleRound();

	BOOL	Create(FIGHTER_SET* teamA, FIGHTER_SET* teamB);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		BYTE bState[20];
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
