// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgFighter.h"

#include "../User.h"
#include "../Pet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgFighter::CMsgFighter()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgFighter::~CMsgFighter()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgFighter::Create(CUser *pUser)
{
	CHECKF(pUser);

	// init
	this->Init();

	m_unMsgType	= _MSG_FIGHTER;

	m_pInfo->dwType = FIGHTERINFO_PLAYER;
	m_unMsgSize = sizeof(MSG_Info) - 32;

	m_pInfo->idPlayer = pUser->GetID();
	m_pInfo->wLook = pUser->GetLook();
	m_pInfo->wLevel = pUser->GetLev();
	m_pInfo->wLifeCurrent = pUser->GetLife();
	m_pInfo->wLifeMax = pUser->GetMaxLife();
	m_pInfo->wManaCurrent = pUser->GetMana();
	m_pInfo->wManaMax = pUser->GetMaxMana();
	//memcpy(m_pInfo->strName, pUser->GetName(), sizeof(NAMESTR));
	strcpy(m_pInfo->strName, pUser->GetName());

	CPet *pPet = pUser->GetMarchingPet();
	if (pPet) {
		m_pInfo->dwType = FIGHTERINFO_PLAYERPET;
		m_unMsgSize = sizeof(MSG_Info);
		m_unMsgSize = 72;

		m_pInfo->idPet = pPet->GetID() | 0x80000000;
		m_pInfo->wPetLook = pPet->GetLook();
		m_pInfo->wPetLevel = pPet->GetLev();
		m_pInfo->wPetLifeCurrent = pPet->GetLife();
		m_pInfo->wPetLifeMax = pPet->GetMaxLife();
		//memcpy(m_pInfo->strPetName, pPet->GetName(), sizeof(NAMESTR));
		strcpy(m_pInfo->strPetName, pPet->GetName());
	}

	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgFighter::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgFighter::Process(CGameSocket* pSocket)
{
	ASSERT(!"CMsgEnemy::Process");
}

