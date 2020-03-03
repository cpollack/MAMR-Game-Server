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
	//m_pRes	= NULL;
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
	strcpy(info.szName, pRes->GetStr(MONSTERDATA_NAME));
	info.Look			= pRes->GetInt(MONSTERDATA_LOOK);
	info.Level		= 1;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMonsterData::SetName(const char* pszName) {
	if (!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return;

	strcpy(info.szName, pszName);
}
