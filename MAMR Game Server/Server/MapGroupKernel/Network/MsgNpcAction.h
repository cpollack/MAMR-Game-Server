// MsgNpc.h: interface for the CMsgNpc class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "NetMsg.h"

//define constant ..
enum {
		NPC_ACT_DIALOGUERESPONSE = 100
};

class CMsgNpcAction : public CNetMsg  
{
public:
	CMsgNpcAction();
	virtual ~CMsgNpcAction();
	BOOL	Create	(int nOption, int nAction);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		int nOption;
		int nAction;
	}MSG_Info;

	MSG_Info*	m_pInfo;

};