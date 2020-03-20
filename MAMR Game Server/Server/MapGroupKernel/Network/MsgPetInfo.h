#pragma once

#include "NetMsg.h"

enum PETINFO_ACTION {
	PETINFO_ACTIONADD = 0,
	PETINFO_ACTIONUPDATE = 1,
};

class CPet;
class CMsgPetInfo  : public CNetMsg
{
public:
	CMsgPetInfo();
	virtual ~CMsgPetInfo();

	BOOL	Create(CPet *pPet, PETINFO_ACTION action);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct 
	{
		MSGHEAD_DEFINE

		DWORD		dwAction;
		OBJID		idPet;
		NAMESTR		szName;
		DWORD		dwClass;
		WORD		wLook;

		WORD		wAttack;
		WORD		wDefence;
		WORD		wDexterity;
		DWORD		dwLevel;
		DWORD		dwExperience;
		WORD		wLifeCurrent;
		WORD		wLifeMax;
		BYTE		bGeneration;

		BYTE		bSkillCount;
		OBJID		idSkill0;
		OBJID		idSkill1;
		OBJID		idSkill2;
		OBJID		idSkill3;
		OBJID		idSkill4;

		BYTE		bVal1; //These four values are unknown
		BYTE		bVal2;
		BYTE		bVal3;
		BYTE		bVal4;

		BYTE		bMedalAttack;
		BYTE		bMedalDefence;
		BYTE		bMedalDexterity;
		BYTE		bLoyalty;

		OBJID		idOwner;

		BYTE		colors[15];
	}MSG_Info;
	MSG_Info*	m_pInfo;
};
