#pragma once

#include "NetMsg.h"

#include "../Battle.h"

struct ENEMYINFO {
	OBJID id;
	WORD look;
	WORD level;
	NAMESTR name;
};

class CMsgEnemy : public CNetMsg
{
public:
	CMsgEnemy();
	virtual ~CMsgEnemy();

	BOOL	Create(CBattle::FIGHTER_SET enemies);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		DWORD dwCount;
		ENEMYINFO enemy[10];
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
