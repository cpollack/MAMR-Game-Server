// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"

#include "../Pet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgPetLevelUp::CMsgPetLevelUp()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgPetLevelUp::~CMsgPetLevelUp()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPetLevelUp::Create(CPet* pPet)
{
	CHECKF(pPet);

	// init
	this->Init();

	// fill info now
	m_unMsgSize	= MSGSIZE;
	m_unMsgType	= _MSG_PETLEVELUP;

	m_pInfo->petID = pPet->GetID();
	m_pInfo->level = pPet->GetLev();
	m_pInfo->attack = pPet->GetAttack();
	m_pInfo->defence = pPet->GetDefence();
	m_pInfo->dexterity = pPet->GetDexterity();
	m_pInfo->life = pPet->GetMaxLife();
	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPetLevelUp::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgPetLevelUp::Process(CGameSocket* pSocket)
{
	//No action

	ASSERT(!"CMsgPetLevelUp::Process");
}

