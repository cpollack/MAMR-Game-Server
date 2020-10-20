#pragma once

#include "NetMsg.h"

enum PETACTION {
	PETACTION_ACTIVE = 0,
	PETACTION_DROP = 3,
	PETACTION_LEARNSKILL = 4,
	PETACTION_FORGETSKILL = 5,
	PETACTION_USEITEM = 7,
	PETACTION_FULLHEAL = 18,
	PETACTION_EXP = 19,
	PETACTION_LOYALTY = 20,
};

class CPet;
class CMsgPetAction  : public CNetMsg
{
public:
	CMsgPetAction();
	virtual ~CMsgPetAction();

	BOOL	Create(OBJID petID, DWORD dwData, PETACTION action);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		OBJID petID;
		DWORD dwData; //Can also be an item id
		DWORD dwAction;
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
