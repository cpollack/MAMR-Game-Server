#pragma once

#include "NetMsg.h"



enum FIGHTERINFO {
	FIGHTERINFO_PLAYER = 200,
	FIGHTERINFO_PLAYERPET = 201,
};

class CUser;
class CMsgFighter : public CNetMsg
{
public:
	CMsgFighter();
	virtual ~CMsgFighter();

	BOOL	Create(CUser *pUser);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		DWORD dwType;

		OBJID idPlayer;
		WORD wLook;
		WORD wLevel;
		WORD wLifeCurrent;
		WORD wLifeMax;
		WORD wManaCurrent;
		WORD wManaMax;
		NAMESTR strName;

		OBJID idPet;
		WORD wPetLook;
		WORD wPetLevel;
		WORD wPetLifeCurrent;
		WORD wPetLifeMax;
		DWORD empty; //four empty bytes, client looks for 2 WORDs
		NAMESTR strPetName;
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
