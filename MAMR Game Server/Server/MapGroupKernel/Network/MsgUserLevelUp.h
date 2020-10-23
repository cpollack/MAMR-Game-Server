#pragma once

#include "NetMsg.h"

class CMsgUserLevelUp : public CNetMsg
{
public:
	CMsgUserLevelUp();
	virtual ~CMsgUserLevelUp();

	BOOL	Create(CUser* pUser);
public:
	BOOL			Create(char* pMsgBuf, DWORD dwSize);
	void			Process(CGameSocket* pSocket);

protected:
	typedef struct
	{
		MSGHEAD_DEFINE

		OBJID userID;
		DWORD exp;
		WORD level;
		WORD attributes;
	}MSG_Info;
	MSG_Info* m_pInfo;
};
