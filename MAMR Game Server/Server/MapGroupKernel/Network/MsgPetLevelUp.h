#pragma once

#include "NetMsg.h"

class CMsgPetLevelUp : public CNetMsg
{
public:
	CMsgPetLevelUp();
	virtual ~CMsgPetLevelUp();

	BOOL	Create(CPet *pPet);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		DWORD petID;
		WORD level;
		WORD attack;
		WORD defence;
		WORD dexterity;
		WORD life;
		WORD loyalty;
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
