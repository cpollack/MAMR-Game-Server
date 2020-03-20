#pragma once

#include "NetMsg.h"

class CMsgNormalAct : public CNetMsg
{
public:
	CMsgNormalAct();
	virtual ~CMsgNormalAct();

	BOOL	Create(int act, int group, BYTE srcState, BYTE trgState, OBJID source, OBJID target, WORD dmg, WORD heal, BYTE interact, BYTE unk);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		BYTE bAct;
		BYTE bGroup;
		BYTE bStateSource;
		BYTE bStateTarget;
		OBJID idSource;
		OBJID idTarget;
		WORD wDamage;
		WORD wHeal;
		BYTE bInteraction;
		BYTE bUnknown; //not yet deciphered from old server binary, maybe state or state rounds
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
