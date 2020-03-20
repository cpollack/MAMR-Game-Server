// ItemType.cpp: implementation of the CItemType class.
//
//////////////////////////////////////////////////////////////////////

#include "winsock2.h"
#include "ItemType.h"
#include "I_mydb.h"
#include "ItemData.h"

MYHEAP_IMPLEMENTATION(CItemType,s_heap)
char	szItemTypeTable[] = _TBL_ITEMTYPE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CItemType::CItemType()
{
	pTypeSet = NULL;
}

//////////////////////////////////////////////////////////////////////
CItemType::~CItemType()
{
	if(pTypeSet)
		pTypeSet->Release();
}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
bool CItemType::Create(IDatabase* pDb)
{
	pTypeSet = CItemTypeSet::CreateNew(true);
	CHECKF(pTypeSet);

	char szSQL[1024];
	sprintf(szSQL, "SELECT * FROM %s", _TBL_ITEMTYPE);
	IF_NOT_(pTypeSet->Create(szSQL, pDb))
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
CItemTypeData* CItemType::QueryItemType(OBJID idType)
{
	return pTypeSet->GetObj(idType);
}

//////////////////////////////////////////////////////////////////////
bool CItemType::GetInfo(OBJID idType, ItemInfoStruct* pInfo)
{
	memset(pInfo, 0, sizeof(ItemInfoStruct));

	CItemTypeData* pType = pTypeSet->GetObj(idType);
	CHECKF(pType);

	pInfo->id		= ID_NONE;
	pInfo->idType = pType->GetID();
	pInfo->idOwner	= ID_NONE;
	pInfo->idPlayer	= ID_NONE;
	pInfo->nPosition	= ITEMPOSITION_NONE;

	pInfo->cost = pType->GetInt(ITEMTYPEDATA_COST);
	pInfo->look = pType->GetInt(ITEMTYPEDATA_LOOK);
	pInfo->sort = pType->GetInt(ITEMTYPEDATA_SORT);
	pInfo->levelReq = pType->GetInt(ITEMTYPEDATA_LEVELREQ);

	pInfo->life = pType->GetInt(ITEMTYPEDATA_LIFE);
	pInfo->power = pType->GetInt(ITEMTYPEDATA_POWER);
	pInfo->attack = pType->GetInt(ITEMTYPEDATA_ATTACK);
	pInfo->defence = pType->GetInt(ITEMTYPEDATA_DEFENCE);
	pInfo->dexterity = pType->GetInt(ITEMTYPEDATA_DEXTERITY);

	pInfo->antiPoison = pType->GetInt(ITEMTYPEDATA_ANTIPOISON);
	pInfo->antiFreeze = pType->GetInt(ITEMTYPEDATA_ANTIFREEZE);
	pInfo->antiSleep = pType->GetInt(ITEMTYPEDATA_ANTISLEEP);
	pInfo->antiChaos = pType->GetInt(ITEMTYPEDATA_ANTICHAOS);

	pInfo->idAction = pType->GetInt(ITEMTYPEDATA_ACTION);
	pInfo->exp = pType->GetInt(ITEMTYPEDATA_EXP);
	pInfo->iClass = pType->GetInt(ITEMTYPEDATA_CLASS);
	pInfo->sacrifice = pType->GetInt(ITEMTYPEDATA_SACRIFICE);

	strcpy(pInfo->szName, pType->GetStr(ITEMTYPEDATA_NAME));
	strcpy(pInfo->szInventor, pType->GetStr(ITEMTYPEDATA_INVENTOR));

	return true;
}




