// ItemType.h: interface for the CItemType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ITEMTYPE_H)
#define ITEMTYPE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	int		nAmount;
	int		nAmountLimit;
	int		nIdent;
	int		nPosition;
	int		nData;
	int		nGem1;
	int		nGem2;
	int		nMagic1;
	int		nMagic2;
	int		nMagic3;
	//---jinggy---2004-11-19---begin
	DWORD	dwWarGhostExp; //战魂经验值
	DWORD	dwGemAtkType; //攻击类宝石的类型
	DWORD	dwAvailabeTime;//攻击类宝石可用次数
	//---jinggy---2004-11-19---end

	char	szName[_MAX_NAMESIZE];	// 由于幻兽可改名，因此掉落的物品名字有可能不是标准物品名字
};

//////////////////////////////////////////////////////////////////////
enum ITEMTYPEDATA
{
	ITEMTYPEDATA_ID_=0,
	ITEMTYPEDATA_NAME=1,
	ITEMTYPEDATA_REQ_PROF,				//ITEMTYPEDATA_SPRITE_TYPE = ITEMTYPEDATA_REQ_PROF,
	ITEMTYPEDATA_LEVEL,		// 物品等级
	ITEMTYPEDATA_REQ_LEVEL,				ITEMTYPEDATA_SPRITE_LEVEL = ITEMTYPEDATA_REQ_LEVEL,
	ITEMTYPEDATA_REQ_SEX,
	ITEMTYPEDATA_REQ_FORCE,
	ITEMTYPEDATA_REQ_DEX,
	ITEMTYPEDATA_REQ_HEALTH,
	ITEMTYPEDATA_REQ_SOUL,
	ITEMTYPEDATA_MONOPOLY,
	ITEMTYPEDATA_WEIGHT,
	ITEMTYPEDATA_PRICE,
	ITEMTYPEDATA_ACTION,
	ITEMTYPEDATA_ATTACK_MAX,			ITEMTYPEDATA_GROWTH_ORIGINAL = ITEMTYPEDATA_ATTACK_MAX,
	ITEMTYPEDATA_ATTACK_MIN,			ITEMTYPEDATA_LEVEXP = ITEMTYPEDATA_ATTACK_MIN,
	ITEMTYPEDATA_DEFENSE,
	ITEMTYPEDATA_DEXTERITY,
	ITEMTYPEDATA_LUCK,
	ITEMTYPEDATA_LIFE,
	ITEMTYPEDATA_MANA,
	ITEMTYPEDATA_AMOUNT,
	ITEMTYPEDATA_AMOUNT_LIMIT,
	ITEMTYPEDATA_IDENT,
	ITEMTYPEDATA_GEM1,
	ITEMTYPEDATA_GEM2,
	ITEMTYPEDATA_MAGIC1,
	ITEMTYPEDATA_MAGIC2,
	ITEMTYPEDATA_MAGIC3,
	ITEMTYPEDATA_MAGICATK,
	ITEMTYPEDATA_MAGICDEF,
	ITEMTYPEDATA_ATKRANGE,
	ITEMTYPEDATA_ATKSPEED,
	ITEMTYPEDATA_HITRATE,
	ITEMTYPEDATA_MONSTERTYPE,
	ITEMTYPEDATA_TARGET,
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
	IItemTypeSet*	m_setType;

	MYHEAP_DECLARATION(s_heap)
};



#endif // !defined(ITEMTYPE_H)
