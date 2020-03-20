// Item.cpp: implementation of the CItem class.
//
//////////////////////////////////////////////////////////////////////

#include "Item.h"
#include "ItemType.h"
#include "MapGroup.h"
#include "I_mydb.h"
#include "User.h"
//#include "MsgEudemonAttrib.h"
//---jinggy---2004-11-12---Begin
#include "Network/netmsg.h"
#include "Network/AllMsg.h"

#define WARGHOSTVALUE_LIMIT  1024	//战魂经验值的界限
//---jinggy---2004-11-12---End

MYHEAP_IMPLEMENTATION(CItem,s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CItem::CItem()
{
	SetObjType(OBJ_ITEM);
}

//////////////////////////////////////////////////////////////////////
CItem::~CItem()
{
}

//////////////////////////////////////////////////////////////////////
bool CItem::CreateItemInfo(ItemInfoStruct& info, DWORD dwValue, CNpcType* pType, int nQuality/*=0*/)
{ //This appears to generate random item drops?
	if (!pType)
		return false;

	// item quality
	DWORD dwItemQuality = 0;

	if (nQuality == 0)	
	{	// auto create this param
		int nRand = ::RandGet(100);
		if (nRand >= 0 && nRand < 30)
			dwItemQuality = 5;
		else if (nRand >= 30 && nRand <70)
			dwItemQuality = 4;
		else
			dwItemQuality = 3;
	}
	else
		dwItemQuality = nQuality;

	// item sort & item color
	DWORD dwItemSort	= 0;
	DWORD dwItemColor	= 0;
	DWORD dwItemLev		= 0;

	int nRand = ::RandGet(1200);
	if (nRand >= 0 && nRand < 20)
	{	// shoes
		dwItemSort	= 160;

		dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_SHOES);
	}
	else if (nRand >= 20 && nRand < 50)
	{	// necklace
		DWORD dwSort[2] = {120, 121};
		dwItemSort = dwSort[::RandGet(2)];

		dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_NECKLACE);
	}
	else if (nRand >= 50 && nRand < 100)
	{	// ring
		DWORD dwSort[3] = {150, 151, 152};
		dwItemSort = dwSort[::RandGet(3)];

		dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_RING);
	}
	else if (nRand >= 100 && nRand < 400)
	{	// armet
		DWORD dwSort[6] = {111, 112, 113, 114, 117, 118};
		dwItemSort = dwSort[::RandGet(6)];

		if (dwItemSort <= 118)	// have color
			dwItemColor = ::RandGet(7)+3;

		dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_ARMET);
	}
	else if (nRand >= 400 && nRand < 700)
	{	// armor
		DWORD dwSort[5] = {130, 131, 132, 133, 134};
		dwItemSort	= dwSort[::RandGet(5)];
		dwItemColor = ::RandGet(7)+3;
		dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_ARMOR);
	}
	else 
	{	// weapon & shield
		int nRate = ::RandGet(100);
		if (nRate >= 0 && nRate < 20)		// 20% for sword of Taoist
		{
			dwItemSort = 421;
		}
		else if (nRate >= 20 && nRate < 40)	// 20% for archer
		{
			// dwItemSort = 500;
			return false;
		}
		else if (nRate >= 40 && nRate < 80)	// 40% for single hand weapon
		{
			DWORD dwSort[11] = {410, 420, 421, 430, 440, 450, 460, 480, 481, 490, 500};
			dwItemSort = dwSort[::RandGet(11)];
		}
		else	// 20% for two hand weapon
		{
			DWORD dwSort[6] = {510, 530, 560, 561, 580, 900};
			dwItemSort = dwSort[::RandGet(6)];

			if (900 == dwItemSort)	// shield
				dwItemColor = ::RandGet(7)+3;
		}

		if (900 == dwItemSort)	// shield
		{
			dwItemColor = ::RandGet(7)+3;
			dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_SHIELD);
		}
		else // weapon
		{
			dwItemLev	= pType->GetInt(NPCTYPEDATA_DROP_WEAPON);
		}
	}


	// item lev
	if (dwItemLev == 99)
		return false;
		
	{
		int nRate = ::RandGet(100);
		if (nRate < 50)		// 50% down one lev
		{
			DWORD dwLev = dwItemLev;
			dwItemLev = ::RandGet(dwLev/2)+dwLev/3;

			if (dwItemLev >= 1)
				dwItemLev--;
		}
		else if (nRate >= 80)	// 20% up one lev
		{
			if ((dwItemSort >= 110 && dwItemSort <= 114) ||
					(dwItemSort >= 130 && dwItemSort <= 134) ||
						(dwItemSort >= 900 && dwItemSort <= 999))
			{	// item with color
				dwItemLev = __min(dwItemLev+1, 9);
			}
			else
			{
				dwItemLev = __min(dwItemLev+1, 23);
			}
		}

		// 50% do nothing
	}


	// item type
	OBJID idItemType = dwItemSort*1000+dwItemColor*100+dwItemLev*10+dwItemQuality;

	CItemTypeData* pItemType = ItemType()->QueryItemType(idItemType);
	if (!pItemType)
		return false;

	// fill item info
	memset(&info, 0L, sizeof(info));

	info.id			= ID_NONE;
	info.idOwner	= ID_NONE;
	info.idPlayer	= ID_NONE;
	info.idType		= idItemType;

	/*info.nAmountLimit	= pItemType->GetInt(ITEMTYPEDATA_AMOUNT_LIMIT)*::RandomRateGet(0.3);
	if (info.nAmountLimit < 1)
		info.nAmountLimit = 1;

	if (dwItemQuality > 5)
		info.nAmount = info.nAmountLimit*(50+::RandGet(50))/100;
	else
	{
		DWORD dwPrice = pItemType->GetInt(ITEMTYPEDATA_PRICE);
		if (dwPrice <= 0)
			dwPrice = 1;

		info.nAmount = 3*info.nAmountLimit*dwValue/dwPrice;
		if (info.nAmount >= info.nAmountLimit)
			info.nAmount = info.nAmountLimit;

		if (info.nAmount < 1)
		{
			info.nAmount = 1;
			//return false;
		}
	}*/

	// gem hole
	/*if (idItemType >= 400000 && idItemType < 599999)	
	{	// is weapon
		int nRate = ::RandGet(100);
		if (nRate < 5)			// 5% got 2 holes
		{
			info.nGem1 = 0xff;
			info.nGem2 = 0xff;
		}
		else if (nRate < 20)	// 15% got 1 hole
		{
			info.nGem1 = 0xff;
		}

		// 80% do nothing
	}*/

	// magic
	// to do...

	return true;
}

//////////////////////////////////////////////////////////////////////
int	CItem::CalcRepairMoney()
{
	// the highest price is about million.
	//int nRecoverDurability =  __max(0, GetInt(ITEMDATA_AMOUNTLIMIT) - GetInt(ITEMDATA_AMOUNT));
	
	//if (nRecoverDurability == 0)
	//	return 0;

	// 修理价格=(持久上限-当前持久)/持久上限*商店出售价格*50%
	// 案子中没有说明当amount_limit==0的时候怎么处理，这里只好当作修理价格为0处理了
	int nRepairCost	= 0;
	//if (GetInt(ITEMDATA_AMOUNTLIMIT) > 0)
	//	nRepairCost	= GetInt(ITEMDATA_PRICE) * nRecoverDurability / GetInt(ITEMDATA_AMOUNTLIMIT) / 2;
	
	return __max(1, nRepairCost);	// 最低修理价格为1
}

//////////////////////////////////////////////////////////////////////
DWORD CItem::GetSellPrice()
{
	//if(GetInt(ITEMDATA_AMOUNTLIMIT) == 0)
	//	return 0;

	int nAmount = 1; // this->GetInt(ITEMDATA_AMOUNT);
	//if (nAmount > this->GetInt(ITEMDATA_AMOUNTLIMIT))
	//	nAmount = this->GetInt(ITEMDATA_AMOUNTLIMIT);

	DWORD dwPrice = GetInt(ITEMDATA_COST);
	//dwPrice	= dwPrice + MulDiv(dwPrice, GetQuality()*5, 100) /* + MulDiv(dwPrice, (GetInt(ITEMDATA_ADDITION)/10)*5, 100)*/ + MulDiv(dwPrice, GetInt(ITEMDATA_LUCK)*5, 100);
	//dwPrice = MulDiv(dwPrice/3, nAmount, GetInt(ITEMDATA_AMOUNT_ORIGINAL));
	dwPrice /= 2;

	// ident
	//if(IsNeedIdent())
	//	dwPrice = UNIDENT_SALE_FEE;

	//if(IsArrowSort())
	//	dwPrice = 0;

	return dwPrice;
}

//////////////////////////////////////////////////////////////////////
CItem*	CItem::Split(int nNum)
{
	/*CHECKF(IsPileEnable());

	int nCurrNum = GetInt(ITEMDATA_AMOUNT);
	CHECKF(nNum > 0 && nNum < nCurrNum);

	DEBUG_TRY ////////
	CItemPtr pItem = Clone();
	CHECKF(pItem);

	pItem->SetInt(ITEMDATA_AMOUNT, nNum, UPDATE_TRUE);
	this->SetInt(ITEMDATA_AMOUNT, nCurrNum - nNum, UPDATE_TRUE);

	return pItem;
	DEBUG_CATCH("item split") ////////// */

	return NULL;
}

//////////////////////////////////////////////////////////////////////
CItem*	CItem::Clone()		// 新物品存数据库
{
	/*CItemPtr pItem = CreateNew();
	IF_NOT(pItem)
		return NULL;

	ItemInfoStruct	info;
	GetInfo(&info);
	info.id		= ID_NONE;		// new record
	if(pItem->Create(m_pData->GetRecord(), &info))		// true: insert
		return pItem;

	pItem->ReleaseByOwner();*/
	return NULL;
}

/*/////////////////////////////////////////////////////////////////////
int	CItem::GetItemSort()
{
	//取百万+十万位
	int nType = ITEMSORT_INVALID;
	switch((GetInt(ITEMDATA_TYPE)%10000000)/100000)
	{
	case 10:
		nType = ITEMSORT_EXPEND;
		break;

	case 1:
		{
			////取十万位+万位
			switch((GetInt(ITEMDATA_TYPE)%1000000)/10000)
			{
			case 11:
				nType = ITEMSORT_HELMET;
				break;
			case 12:
				nType = ITEMSORT_NECKLACE;
				break;
			case 13:
				nType = ITEMSORT_ARMOR;
				break;
			case 15:
				nType = ITEMSORT_RING;
				break;
			case 16:
				nType = ITEMSORT_SHOES;
				break;
			}
		}
		break;

	case 4:
		nType = ITEMSORT_WEAPON1;
		break;

	case 5:
		nType = ITEMSORT_WEAPON2;
		break;

	case 6:
		nType = ITEMSORT_MOUNT;
		break;

	case 7:
		nType = ITEMSORT_OTHER;
		break;

	case 9:
		nType = ITEMSORT_SHIELD;
		break;
	}

	return nType;
}
//*/
/*/////////////////////////////////////////////////////////////////////
int	CItem::GetItemType()
{
	int nType = ITEMTYPE_INVALID;
	//取百万+十万位
	switch((GetInt(ITEMDATA_TYPE)%10000000)/100000)
	{
	case 7:
	case 10:
		nType = ((GetInt(ITEMDATA_TYPE)%100000)/10000)*10000;	// 返回万位*万
		break;

	case 4:
	case 5:
		nType = ((GetInt(ITEMDATA_TYPE)%100000)/1000)*1000;		// 返回（万位，千位）*千
		break;

	default:
		break;
	}

	return nType;
}
//*/
//////////////////////////////////////////////////////////////////////
int	CItem::GetItemType(OBJID idType)
{
	return idType % 100;
	/*if(GetItemSort(idType) == ITEMSORT_WEAPON1 || GetItemSort(idType) == ITEMSORT_WEAPON2) // || GetItemSort(idType) == ITEMSORT_EXPEND)
		return  ((idType%100000)/1000)*1000;		// 返回（万位，千位）*千
	else
		return  ((idType%100000)/10000)*10000;	// 返回万位*万*/
}
//////////////////////////////////////////////////////////////////////
int	CItem::GetItemSubType()
{
	// 取十万，万，千位
	return (GetInt(ITEMDATA_SORT)%1000000)/1000;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetLevel(void)
{
	//if (this->IsShield() || this->IsArmor() || this->IsHelmet())
	//	return (GetInt(ITEMDATA_TYPE)%100)/10;
	//else
		return GetInt(ITEMDATA_LEVELREQ);
}

//////////////////////////////////////////////////////////////////////
/*
 对表 cq_item 中的 type, 改变 type 的末尾就是改变装备的品质 ;
 通过 type 和 magic3 就可定位到  表 cq_itemaddition (不同品质及追加属性的装备对应的其他属性)
*/
bool CItem::ChangeType	(OBJID idNewType) //
{
	// type
	CItemTypeData *pType = ItemType()->QueryItemType(idNewType);
	if(!pType)
	{
		LOGERROR("ChangeType类型[%d]错误!", idNewType);

		return false;
	}
	
	m_pType = pType;
	//this->SetInt(ITEMDATA_TYPE, idNewType);

	// TODO:这里暂时不考虑从非幻兽物品到幻兽物品的type变换
	// 否则需要读入或创建eudemon表数据
	// zlong 2005-03-02
	
	
	//m_pAddition = ItemAddition()->QueryItemAddition(idNewType, GetInt(ITEMDATA_ADDITION));

	return true;
}
//////////////////////////////////////////////////////////////////////
/*
对表 cq_item 中的 magic3, 改变 type 的末尾就是改变装备的追加等级属性
*/
bool CItem::ChangeAddition(int nLevel)
{
	/*CItemAdditionData* pAddition = NULL;
	if (nLevel > 0)
	{
		//pAddition = ItemAddition()->QueryItemAddition(this->GetInt(ITEMDATA_TYPE), nLevel);
		if (!pAddition)
			return false;
	}
	//m_pAddition	= pAddition;
	this->SetInt(ITEMDATA_ADDITION, nLevel, true);*/
	return true;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetGemDmgEffect()
{
	int nEffect = 0;
	/*int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

	for (int i=0; i<2; i++)
	{
		if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
		{
			OBJID idGemType = 700000 + nGem[i];
			switch(idGemType)
			{
			case GEM_DMG_LOW:
				nEffect += 5;
				break;
				
			case GEM_DMG_MID:
				nEffect += 10;
				break;
				
			case GEM_DMG_HGT:
				nEffect += 15;
				break;
			}
		}
	}*/
	
	return nEffect;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetGemMgcAtkEffect()
{
	int nEffect = 0;
	/*int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

	for (int i=0; i<2; i++)
	{
		if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
		{
			OBJID idGemType = 700000 + nGem[i];
			switch(idGemType)
			{
			case GEM_MATK_LOW:
				nEffect += 5;
				break;
				
			case GEM_MATK_MID:
				nEffect += 10;
				break;
				
			case GEM_MATK_HGT:
				nEffect += 15;
				break;
			}
		}
	}*/
	
	return nEffect;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetGemHitRateEffect()
{
	int nEffect = 0;
	/*int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

	for (int i=0; i<2; i++)
	{
		if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
		{
			OBJID idGemType = 700000 + nGem[i];
			switch(idGemType)
			{
			case GEM_HIT_LOW:
				nEffect += 5;
				break;
				
			case GEM_HIT_MID:
				nEffect += 10;
				break;
				
			case GEM_HIT_HGT:
				nEffect += 15;
				break;
			}
		}
	}*/
	
	return nEffect;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetGemExpEffect()
{
	int nEffect = 0;
	/*int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

	for (int i=0; i<2; i++)
	{
		if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
		{
			OBJID idGemType = 700000 + nGem[i];
			switch(idGemType)
			{
			case GEM_EXP_LOW:
				nEffect += 10;
				break;
				
			case GEM_EXP_MID:
				nEffect += 15;
				break;
				
			case GEM_EXP_HGT:
				nEffect += 25;
				break;
			}
		}
	}*/

	return nEffect;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetGemWpnExpEffect()
{
	int nEffect = 0;
	/*int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

	for (int i=0; i<2; i++)
	{
		if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
		{
			OBJID idGemType = 700000 + nGem[i];
			switch(idGemType)
			{
			case GEM_WPNEXP_LOW:
				nEffect += 30;
				break;
				
			case GEM_WPNEXP_MID:
				nEffect += 50;
				break;
				
			case GEM_WPNEXP_HGT:
				nEffect += 100;
				break;
			}
		}
	}*/

	return nEffect;
}

//////////////////////////////////////////////////////////////////////
int	CItem::GetGemMgcExpEffect()
{
	int nEffect = 0;
	/*int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

	for (int i=0; i<2; i++)
	{
		if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
		{
			OBJID idGemType = 700000 + nGem[i];
			switch(idGemType)
			{
			case GEM_MGCEXP_LOW:
				nEffect += 15;
				break;
				
			case GEM_MGCEXP_MID:
				nEffect += 30;
				break;
				
			case GEM_MGCEXP_HGT:
				nEffect += 50;
				break;
			}
		}
	}*/

	return nEffect;
}

//////////////////////////////////////////////////////////////////////
int CItem::GetGemDurEffect(OBJID idGemType)
{
	int nEffect = 0;

	// default...
	/*if (ID_NONE == idGemType)
	{
		int nGem[2] = { this->GetInt(ITEMDATA_GEM1), this->GetInt(ITEMDATA_GEM2) };

		for (int i=0; i<2; i++)
		{
			if (nGem[i] != GEM_NONE && nGem[i] != GEM_HOLE)
			{
				OBJID idGemType = 700000 + nGem[i];
				switch(idGemType)
				{
				case GEM_DUR_LOW:
					nEffect += 50;
					break;
					
				case GEM_DUR_MID:
					nEffect += 100;
					break;
					
				case GEM_DUR_HGT:
					nEffect += 200;
					break;
				}
			}
		}
	}
	else 
	{
		switch(idGemType)
		{
		case GEM_DUR_LOW:
			nEffect += 50;
			break;
			
		case GEM_DUR_MID:
			nEffect += 100;
			break;
			
		case GEM_DUR_HGT:
			nEffect += 200;
			break;
		}
	}*/

	return nEffect;
}

//////////////////////////////////////////////////////////////////////
/*bool CItem::IsNonsuchItem(void)
{
	// treasure
	DWORD dwType = this->GetInt(ITEMDATA_TYPE);
	switch(dwType)
	{
	case TYPE_DRAGONBALL:
	case TYPE_SHOOTINGSTAR:
	case TYPE_DIVOICEITEM:
		return true;
		break;

	default:
		break;
	}

	// precious gem
	if (this->IsGem() && (dwType%10) >= 2)
		return true;

	// game card
	if (this->IsGameCard())
		return true;

	// chest item
	if (this->IsChestItem())
		return true;

	// other type
	if (CItem::GetItemSort(dwType) == ITEMSORT_OTHER || CItem::GetItemSort(dwType) >= ITEMSORT_EXPEND)
		return false;

	// high quality
	if (this->GetQuality() >= 8)
		return true;

	// ....
	int nGem1 = this->GetInt(ITEMDATA_GEM1)%10;
	int nGem2 = this->GetInt(ITEMDATA_GEM2)%10;

	bool bIsNonsuch = false;
	if(IsWeapon())
	{
		if ((nGem1 != GEM_HOLE && nGem1 >= 2)
				|| (nGem2 != GEM_HOLE && nGem2 >= 2))
			bIsNonsuch = true;
	}
	else if(IsFinery() || IsShield())
	{
		if (nGem1 != GEM_NONE || nGem2 != GEM_NONE)
			bIsNonsuch = true;
	}

	return bIsNonsuch;
}*/

//////////////////////////////////////////////////////////////////////
bool CItem::ChangeColor(int nColor)
{
	/*if (!(nColor >=3 && nColor <= 9))
		return false;

	if(IsHelmet() || IsArmor() || IsShield())
	{
		DWORD idType = this->GetInt(ITEMDATA_TYPE);
		DWORD idNewType = idType-((idType/100)%10)*100+nColor*100;
		return this->ChangeType(idNewType);
	}*/

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CItem::RecoverDur	(void)
{
	/*int nMaxDur = this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL);
	nMaxDur += nMaxDur*this->GetGemDurEffect()/100;

	this->SetInt(ITEMDATA_AMOUNTLIMIT, nMaxDur, true);*/
	return true;
}

//////////////////////////////////////////////////////////////////////
int CItem::GetRecoverDurCost	(void)
{
	/*int nRealMaxDur = this->GetInt(ITEMDATA_AMOUNTLIMIT)*100/(100+this->GetGemDurEffect());
	if (nRealMaxDur >= this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL))
		return 0;

	int nRepairDur = this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL)-nRealMaxDur;
	int nCost = 0;
	CHECKF(this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL));
	switch(this->GetQuality())
	{
	case 9:
		nCost = ::MulDiv(5000000, nRepairDur, this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL));
		nCost = __max(nCost, 500000);
		break;

	case 8:
		nCost = ::MulDiv(3500000, nRepairDur, this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL));
		nCost = __max(nCost, 350000);
		break;

	default:
		nCost = ::MulDiv(1500000, nRepairDur, this->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL));
		nCost = __max(nCost, 150000);
		break;
	}

	return __max(1, nCost);*/
	return 0;
}

//////////////////////////////////////////////////////////////////////
/*int CItem::GetWeight(OBJID idType, int nAmount)		// nAmount: amount 字段值
{
	CItemTypeData* pType = ItemType()->QueryItemType(idType);
	IF_NOT(pType)
		return ERROR_WEIGHT;

	if(!nAmount)
		nAmount	= pType->GetInt(ITEMTYPEDATA_AMOUNT);

	if(IsArrowSort(idType))
		return (pType->GetInt(ITEMTYPEDATA_AMOUNT)-1)*pType->GetInt(ITEMTYPEDATA_WEIGHT)/ARROW_PILE_WEIGHT + 1;

	if(CItem::IsExpend(idType))
		return pType->GetInt(ITEMTYPEDATA_WEIGHT) * nAmount;
	else
		return pType->GetInt(ITEMTYPEDATA_WEIGHT);
}*/

//////////////////////////////////////////////////////////////////////
int	CItem::AwardExp(int nExp, int nLuck /* = 0*/)
{
	if (nExp <= 0)
		return nExp;

	return nExp;
}


//////////////////////////////////////////////////////////////////////
int CItem::AdjustOriginalGrowth()
{
	int nGrowth = 0;
	/*int nRate = ::RandGet(100);
	if (nRate < 15)
		nGrowth = ::RandGet(50);
	else if (nRate < 35)
		nGrowth = ::RandGet(50) + 50;
	else if (nRate < 75)
		nGrowth = 100;
	else if (nRate < 95)
		nGrowth = ::RandGet(49) + 101;
	else
		nGrowth = ::RandGet(50) + 150;

	this->SetInt(ITEMDATA_GROWTH, nGrowth, true);*/

	return nGrowth;
}

//////////////////////////////////////////////////////////////////////
/*int CItem::GetAddition(ITEMADDITIONDATA idx)
{
	if (!m_pAddition)
		return 0;

	return m_pAddition->GetInt(idx);
}*/

//判断是否是状态攻击类宝石
bool CItem::IsGemActiveAtk()
{
	//DWORD dwType = GetInt(ITEMDATA_TYPE)%100000/1000*1000;

	//return (this->IsGhostGem() && (dwType == ITEMTYPE_GHOSTGEM_ACTIVE_ATK));
	return false;
}
