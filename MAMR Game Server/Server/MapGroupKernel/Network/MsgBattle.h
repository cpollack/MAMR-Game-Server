#pragma once

#include "NetMsg.h"

enum BATTLESTATE {
	BATTLESTATE_START = 0,
	BATTLESTATE_CONFIRM = 2,
	BATTLESTATE_END = 3,
};

class CMsgBattle : public CNetMsg
{
public:
	CMsgBattle();
	virtual ~CMsgBattle();

	BOOL	Create(OBJID userID, BATTLESTATE state, int actors, int formation);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		BYTE bState;
		BYTE bActors;
		WORD empty; //2 empty bytes
		OBJID idUser;
		DWORD dwFormation;
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
