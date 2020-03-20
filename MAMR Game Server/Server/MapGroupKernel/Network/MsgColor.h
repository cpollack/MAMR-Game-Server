#pragma once

#include "NetMsg.h"
#include "../Role.h"

class CMsgColor : public CNetMsg
{
public:
	CMsgColor();
	virtual ~CMsgColor();

	BOOL	Create(CRole *pRole);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	
	typedef struct 
	{
		MSGHEAD_DEFINE

		OBJID id;
		WORD count;
		ColorSet sets[5];
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
