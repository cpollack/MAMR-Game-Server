// MonsterData.cpp: implementation of the CMonsterData class.
//
//////////////////////////////////////////////////////////////////////

#include "MonsterData.h"
//#include "I_mydb.h"
#include "string.h"
#include "MapGroup.h"
#include "Monster.h"
#include "UserData.h"

//////////////////////////////////////////////////////////////////////
char	szMonsterTable[] = _TBL_MONSTER;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonsterData::CMonsterData()
{
	memset(&info, 0, sizeof(MonsterInfoStruct));
	pRes = NULL;
}

CMonsterData::~CMonsterData()
{
	//if(m_pRes)
	//	m_pRes->Release();
}

//////////////////////////////////////////////////////////////////////
bool CMonsterData::Create(OBJID idMonster)
{
	CHECKF(!pRes);
	
	pRes = MonsterType()->GetObj(idMonster)->GetRecord();
	if(pRes)
	{
		return LoadInfo();
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CMonsterData::LoadInfo()
{
	if (!pRes) 
		return false;

	// load again?
	if (info.id != ID_NONE)
		return true;

	info.MonsterID	= pRes->GetInt(MONSTERDATA_ID);
	info.Class = pRes->GetInt(MONSTERDATA_CLASS);
	strcpy(info.szName, pRes->GetStr(MONSTERDATA_NAME));
	info.Look = pRes->GetInt(MONSTERDATA_LOOK);
	
	//load the rest of the monster data
	info.baseAttack = pRes->GetDouble(MONSTERDATA_BASE_ATTACK);
	info.baseDefence = pRes->GetDouble(MONSTERDATA_BASE_DEFENCE);
	info.baseDexterity = pRes->GetDouble(MONSTERDATA_BASE_DEXTERITY);
	info.baseLife = pRes->GetDouble(MONSTERDATA_BASE_LIFE);

	info.rateAttack = pRes->GetInt(MONSTERDATA_RATE_ATTACK);
	info.rateDefence = pRes->GetInt(MONSTERDATA_RATE_DEFENCE);
	info.rateDexterity = pRes->GetInt(MONSTERDATA_RATE_DEXTERITY);

	info.Growth = pRes->GetDouble(MONSTERDATA_GROWPOINT);
	info.LifeRise = pRes->GetDouble(MONSTERDATA_LIFERISE);

	info.Level = 1;
	info.Attack = info.baseAttack;
	info.Defence = info.baseDefence;
	info.Dexterity = info.baseDexterity;
	info.Life = info.baseLife;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMonsterData::SetName(const char* pszName) {
	if (!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return;

	strcpy(info.szName, pszName);
}
