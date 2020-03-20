#pragma once

#include "NetMsg.h"

class CMsgBattleAct : public CNetMsg
{
public:
	CMsgBattleAct();
	virtual ~CMsgBattleAct();

	BOOL	Create(int act, int round, OBJID source, OBJID target, OBJID use, CUser* pUser);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		BYTE bAct;
		BYTE bRound;
		WORD emtpy; //2 byte buffer space
		OBJID idSource;
		OBJID idTarget;
		OBJID idUsing;

		DWORD dwVerify;
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
