#pragma once

#include "NetMsg.h"

class CMsgPointAllot : public CNetMsg
{
public:
	CMsgPointAllot();
	virtual ~CMsgPointAllot();

	//BOOL	Create(CUser* pUser);
public:
	BOOL			Create(char* pMsgBuf, DWORD dwSize);
	void			Process(CGameSocket* pSocket);

protected:
	typedef struct
	{
		MSGHEAD_DEFINE

		WORD physique;
		WORD stamina;
		WORD force;
		WORD speed;
		WORD degree;
	}MSG_Info;
	MSG_Info* m_pInfo;
};
