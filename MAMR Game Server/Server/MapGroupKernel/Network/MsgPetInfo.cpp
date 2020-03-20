// MsgCallPetInfo.cpp: implementation of the CMsgCallPetInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "MsgPetInfo.h"
#include "../GameMap.h"
#include "../MapGroup.h"

#include "../Pet.h"
#include "../PetData.h"
#include "../MonsterData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgPetInfo::CMsgPetInfo()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgPetInfo::~CMsgPetInfo()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPetInfo::Create(CPet *pPet, PETINFO_ACTION action)
{
	CHECKF(pPet->GetID());

	// init
	this->Init();

	// fill info now
	m_unMsgSize	=sizeof(MSG_Info);
	m_unMsgType	=_MSG_PETINFO;

	m_pInfo->dwAction = action;
	m_pInfo->idPet = pPet->GetID();
	strcpy(m_pInfo->szName, pPet->GetName());

	CPetData *pData = pPet->GetData();
	m_pInfo->dwClass = pData->GetClass();
	m_pInfo->wLook = pData->GetLook();
	m_pInfo->wAttack = pData->GetAttack();
	m_pInfo->wDefence = pData->GetDefence();
	m_pInfo->wDexterity = pData->GetDexterity();
	m_pInfo->dwLevel = pData->GetLevel();
	m_pInfo->dwExperience = pData->GetExperience();
	m_pInfo->wLifeCurrent = pData->GetMaxLife();
	m_pInfo->wLifeMax = pData->GetLife();
	m_pInfo->bGeneration = pData->GetGeneration();
	
	m_pInfo->bSkillCount = pData->GetSkillCount();
	m_pInfo->idSkill0 = pData->GetSkill(0);
	m_pInfo->idSkill1 = pData->GetSkill(1);
	m_pInfo->idSkill2 = pData->GetSkill(2);
	m_pInfo->idSkill3 = pData->GetSkill(3);
	m_pInfo->idSkill4 = pData->GetSkill(4);

	m_pInfo->bVal1 = 0; //Hardcoded to 0 until we know what they do
	m_pInfo->bVal2 = 0;
	m_pInfo->bVal3 = 0;
	m_pInfo->bVal4 = 0;

	m_pInfo->bMedalAttack = pData->GetMedalAttack();
	m_pInfo->bMedalDefence = pData->GetMedalDefence();
	m_pInfo->bMedalDexterity = pData->GetMedalDexterity();
	m_pInfo->bLoyalty = pData->GetLoyalty();

	m_pInfo->idOwner = pPet->GetOwnerID();

	for (int i = 0; i < 3; i++) { // 96, 128, 0
		HSB hsb = pData->GetHSB(i);
		m_pInfo->colors[(i * 5) + 0] = hsb.hue;
		m_pInfo->colors[(i * 5) + 1] = 8;
		m_pInfo->colors[(i * 5) + 2] = hsb.sat;
		m_pInfo->colors[(i * 5) + 3] = hsb.bright;
		if (i == 0) m_pInfo->colors[(i * 5) + 4] = 96;
		if (i == 1) m_pInfo->colors[(i * 5) + 4] = 128;
		if (i == 2) m_pInfo->colors[(i * 5) + 4] = 0;
	}

	
	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPetInfo::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgPetInfo::Process(CGameSocket* pSocket)
{
#ifdef _MYDEBUG
	::LogSave("Process CMsgCallPetInfo: ID:0x:%x, Type:%d, LookType:%d, CellX:%d, CellY:%d, Name:%s",
				m_pInfo->id	, m_pInfo->ucType,
				m_pInfo->usLook, m_pInfo->usCellX, 
				m_pInfo->usCellY, m_pInfo->szName);

#endif
	ASSERT(!"CMsgCallPetInfo::Process");
}

