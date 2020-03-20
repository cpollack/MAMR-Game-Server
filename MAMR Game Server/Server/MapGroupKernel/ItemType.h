#pragma once

#pragma warning(disable:4786)
#include "define.h"
#include "ConstGameData.h"
#include "GameData.h"
#include "GameObj.h"
#include "Myheap.h"
#include "T_SingleMap2.h"
#include <vector>
using namespace std;


//////////////////////////////////////////////////////////////////////
struct ItemInfoStruct
{
	OBJID	id;
	OBJID	idType;
	OBJID	idOwner;
	OBJID	idPlayer;
	int		nPosition;

	int cost;
	int look;
	int sort;
	int levelReq;

	int life;
	int power;
	int attack;
	int defence;
	int dexterity;

	int antiPoison;
	int antiFreeze;
	int antiSleep;
	int antiChaos;

	OBJID idAction;
	int exp;
	int iClass;
	int sacrifice;

	char	szName[_MAX_NAMESIZE];
	char	szInventor[_MAX_NAMESIZE];
};

//////////////////////////////////////////////////////////////////////
enum ITEMTYPEDATA
{
	ITEMTYPEDATA_NAME = 0,
	ITEMTYPEDATA_ID_=1,
	ITEMTYPEDATA_COST,
	ITEMTYPEDATA_LOOK,
	ITEMTYPEDATA_SORT,
	ITEMTYPEDATA_LEVELREQ,
	ITEMTYPEDATA_LIFE,
	ITEMTYPEDATA_POWER,
	ITEMTYPEDATA_ATTACK,		
	ITEMTYPEDATA_DEFENCE,
	ITEMTYPEDATA_DEXTERITY,
	ITEMTYPEDATA_ANTIPOISON,
	ITEMTYPEDATA_ANTIFREEZE,
	ITEMTYPEDATA_ANTISLEEP,
	ITEMTYPEDATA_ANTICHAOS,
	ITEMTYPEDATA_INVENTOR,
	ITEMTYPEDATA_ACTION,
	ITEMTYPEDATA_EXP,
	ITEMTYPEDATA_CLASS,
	ITEMTYPEDATA_SACRIFICE
};

char	szItemTypeTable[];
#if	defined(PALED_DEBUG)
typedef	CConstGameData<ITEMTYPEDATA,szItemTypeTable,ITEMTYPEDATA_ID_>	CItemTypeData;
#else
typedef	CGameData<ITEMTYPEDATA,szItemTypeTable, szID>	CItemTypeData;
#endif
typedef	ISingleMap2<CItemTypeData>	IItemTypeSet;
typedef	CSingleMap2<CItemTypeData>	CItemTypeSet;

class IDatabase;
class CItemType
{
protected:
	CItemType();
	virtual ~CItemType();
public:
	static CItemType*	CreateNew	()		{ return new CItemType; }
	ULONG	Release			()				{ delete this; return 0; }
	bool	Create			(IDatabase* pDb);
	CItemTypeData*	QueryItemType(OBJID idType);
	bool	GetInfo(OBJID idType, ItemInfoStruct* pInfo);

protected:
	IItemTypeSet*	pTypeSet;

	MYHEAP_DECLARATION(s_heap)
};
