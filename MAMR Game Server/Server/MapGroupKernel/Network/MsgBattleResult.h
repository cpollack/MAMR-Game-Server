#pragma once

#include "NetMsg.h"

enum BATTLERESULT {
	BATTLERESULT_RUN = 0, 
	BATTLERESULT_WIN = 1,
	BATTLERESULT_TEAMWIN = 2, //best guess
	BATTLERESULT_LOSE = 3, 
	BATTLERESULT_TEAMLOSE = 4 //best guess again
};

class CMsgBattleResult : public CNetMsg
{
public:
	CMsgBattleResult();
	virtual ~CMsgBattleResult();

	BOOL	Create(BATTLERESULT mode, int money, int life, int mana, int rep, int exp, int petLife, int petLoyalty, int petExp);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		WORD wMode;
		WORD wMoney;
		WORD wUserLife;
		WORD wUserMana;
		DWORD dwReputation;
		DWORD dwUserExp;
		WORD wPetLife;
		WORD wPetLoyalty;
		DWORD dwPetExp;
		DWORD empty; //empty 4 bytes on old server
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
