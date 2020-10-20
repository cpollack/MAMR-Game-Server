// Item.h: interface for the CItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__CA7CE885_1DCF_4B96_B308_FB7F40CCF4BA__INCLUDED_)
#define AFX_ITEM_H__CA7CE885_1DCF_4B96_B308_FB7F40CCF4BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemData.h"
#include "MyHeap.h"
#include "T_SingleObjSet2.h"
#include "T_SingleMap2.h"
#include "UserTable.h"

//////////////////////////////////////////////////////////////////////
const int	ITEMREPAIR_PERCENT		= 200;				// �����Ϊԭ�۵�200%
const int	ITEMIDENT_PERCENT		= 10;				// ������10%
const int	ERROR_WEIGHT			= 123456789;		// ���������
//---Ʒ��---begin
const int	QUALITY_ZERO		= 0;				// ��ͨƷ
const int	QUALITY_ONE			= 1;				// ��Ʒ
const int	QUALITY_TWO			= 2;				// ��Ʒ
const int	QUALITY_THREE		= 3;				// ��Ʒ
const int	QUALITY_FOUR		= 4;				// ��Ʒ
//---Ʒ��---end
const int	EUDEMON_EVOLVE_LEVEL1	= 20;				// ���޵�һ�ν����ȼ�
const int	EUDEMON_EVOLVE_LEVEL2	= 40;				// ���޵ڶ��ν����ȼ�
const int	EUDEMON_EVOLVE_MAXTYPE	= 2;				// ���޵�һ�ν�����������ͱ��

//////////////////////////////////////////////////////////////////////
//
const int	EUDEMON_GROUP_SAINT		= 1;			// ʥ��
const int	EUDEMON_GROUP_EVIL		= 2;			// ħ��

const int	MIN_DIVINE_ID	= 1;					// ��С��ʶ���
const int	MAX_DIVINE_ID	= 8;					// �����ʶ���


const int	EUDEMON_HATCH_SECS		= 24*60*60;			// ���޷�����Ҫ24Сʱ

// chest
const OBJID TYPE_CHEST_SPACE3	= 1070000;
const OBJID TYPE_CHEST_SPACE6	= 1070001;
const OBJID TYPE_CHEST_SPACE9	= 1070002;


// treasure
const OBJID TYPE_DRAGONBALL		= 1088000;
const OBJID TYPE_SHOOTINGSTAR	= 1088001;
const OBJID TYPE_DIVOICEITEM	= 1088002;

// gems
const OBJID GEM_WPNEXP_LOW	= 700051;
const OBJID GEM_WPNEXP_MID	= 700052;
const OBJID GEM_WPNEXP_HGT	= 700053;

const OBJID GEM_MGCEXP_LOW	= 700061;
const OBJID GEM_MGCEXP_MID	= 700062;
const OBJID GEM_MGCEXP_HGT	= 700063;

const OBJID GEM_EXP_LOW	= 700031;
const OBJID GEM_EXP_MID	= 700032;
const OBJID GEM_EXP_HGT	= 700033;

const OBJID GEM_DUR_LOW	= 700041;
const OBJID GEM_DUR_MID	= 700042;
const OBJID GEM_DUR_HGT	= 700043;

const OBJID GEM_DMG_LOW	= 700011;
const OBJID GEM_DMG_MID	= 700012;
const OBJID GEM_DMG_HGT	= 700013;

const OBJID GEM_HIT_LOW	= 700021;
const OBJID GEM_HIT_MID	= 700022;
const OBJID GEM_HIT_HGT	= 700023;

const OBJID GEM_MATK_LOW	= 700001;
const OBJID GEM_MATK_MID	= 700002;
const OBJID GEM_MATK_HGT	= 700003;

const OBJID GEM_EUDEMON_REBORN	= 1033020;	// ���޸����ñ�ʯ
const OBJID GEM_EUDEMON_ENHANCE	= 1033030;	// ����ǿ���ñ�ʯ

const OBJID	NORMAL_ARROW_TYPE	= 1050000;	// normal arrow itemtype
const OBJID	ARROW_SUBTYPE		= 50;		// normal arrow subtype

const OBJID	CARD_FEE_POINT		= 780000;	// game card for fee
const OBJID	CARD_FEE_POINT2		= 780001;	// game card for fee

// add by zlong 2003-12-05
const OBJID ARROW_TYPE_ID		= 170001;	// ��
const OBJID DART_TYPE_ID		= 171001;	// ���

//LW����õ������ͳ���----------------------
const int   AUCTION_CHIP                   = 720000;
//------------------------------------------

const OBJID ARROW_PILE_WEIGHT	= 100;		// ����֧��ʸ������Ϊ1. 100->100֧����Ϊ1
//---jinggy---����ϵͳ---begin
const int MAX_LEVEL_EQUIP1 = 9;
const int MAX_LEVEL_EQUIP2 = 22;
const int MAX_LEVEL_QUALITYANDADDITION = 9;
//---jinggy---����ϵͳ---end
//////////////////////////////////////////////////////////////////////
// ħ�걦ʯ
// ����4����ʯ���ռ��ʹ�õ����ȼ�����˳������
const OBJID GHOST_GEM_AVOID_DEATH	= 1033040;		// �ƻ걦ʯ�����������ָ�ȫ������
const OBJID GHOST_GEM_AMULET		= 1036000;		// ����ʯ�����������ָ�1������
const OBJID GHOST_GEM_SCAPEGOAT		= 1036030;		// ����ʯ������ɱ��������Ʒ�;���
const OBJID GHOST_GEM_REBORN		= 1036020;		// ���ʯ��������20��󸴻�
const OBJID GHOST_GEM_AVOID_STEAL	= 1034020;		// ��͵����ʯ�������ⱻ͵��

//////////////////////////////////////////////////////////////////////
enum ITEM_IDENT
{
	_ITEM_STATUS_NONE			= 0,		// ��
	_ITEM_STATUS_NOT_IDENT		= 1,		// δ����
	_ITEM_STATUS_CANNOT_REPAIR	= 2,		// �����޸�
	_ITEM_STATUS_NEVER_DAMAGE	= 4,		// ����ĥ��
};

//////////////////////////////////////////////////////////////////////
// Itemtype���target�ֶ�����
enum TARGET_MASK
{
	TARGET_NONE			= 0x0000,			// ֻ�ܶ��Լ�ʹ�� ���� ���ݾ�ϵͳ����

	// Ŀ������
	TARGET_USER			= 0x0001,			// ���Զ����ʹ��
	TARGET_MONSTER		= 0x0002,			// ���ԶԹ���ʹ��

	// ��������
	TARGET_SELF			= 0x0010,			// ����ֻ�ܶ��Լ��������Լ���Ŀ��
	TARGET_OTHERS		= 0x0020,			// ����ֻ�ܶ�������һ�����������ҵ�Ŀ��
	TARGET_BODY			= 0x0040,			// ����ֻ�ܶ�ʬ��ʹ��

	// �������ͼ��
	TARGET_CHK_PKMODE	= 0x0100,			// ��Ҫ���pkģʽ
	TARGET_FORBIDDEN	= 0x0200,			// ��ֹ���κ�Ŀ��ʹ��
};

//////////////////////////////////////////////////////////////////////

class CItem : public CItemData  
{
protected:
	CItem();
	virtual ~CItem();
public:
	static CItem* CreateNew()		{ return (new CItem); }
	UINT	ReleaseByOwner()		{ delete this; return 0; }

	static bool	CreateItemInfo(ItemInfoStruct& info, DWORD dwValue, CNpcType* pType, int nQuality=0);

public: // ����
	//bool	IsNormal()		{ return GetItemSort() == ITEMSORT_EXPEND; }
	bool	IsWeapon()		{ return GetItemSort() == ITEMSORT_WEAPON; }	
	//bool	IsWeapon1()		{ return GetItemSort() == ITEMSORT_WEAPON1; }		// single hand use
	//bool	IsWeapon2()		{ return GetItemSort() == ITEMSORT_WEAPON2; }		// two hand use
	//bool	IsWeapon()		{ return GetItemSort() == ITEMSORT_WEAPON1 || GetItemSort() == ITEMSORT_WEAPON2; }
	//bool	IsMount()		{ return CItem::IsMount(GetInt(ITEMDATA_TYPE)); }
	//bool	IsShield()		{ return CItem::IsShield(GetInt(ITEMDATA_TYPE)); }
	//bool	IsOther()		{ return GetItemSort() == ITEMSORT_OTHER; }
	//bool	IsFinery()		{ return !IsArrowSort() && GetItemSort() == IETMSORT_FINERY; }
	//bool	IsArrowSort()	{ return CItem::IsArrowSort(GetInt(ITEMDATA_TYPE)); }
	//bool	IsArrow()		{ return CItem::IsArrow(GetInt(ITEMDATA_TYPE)); } //IsNormal() && GetItemType() == ITEMTYPE_ARROW; }
	bool	IsDart()		{ return GetItemSort() == ITEMSORT_DART; } //IsNormal() && GetItemType() == ITEMTYPE_DART; }
	//bool	IsSpell()		{ return CItem::IsSpell(GetInt(ITEMDATA_TYPE)); }
	//bool	IsExpend()		{ return CItem::IsExpend(GetInt(ITEMDATA_TYPE)); }
	//bool	IsHelmet()		{ return IsFinery() && GetItemType() == ITEMTYPE_HELMET; }
	//bool	IsNecklace()	{ return GetItemSort() == ITEMTYPE_NECKLACE; }
	bool	IsArmor()		{ return GetItemSort() == ITEMSORT_ARMOR; }
	bool	IsBodyAccessory() { return GetItemSort() == ITEMSORT_BODY; }
	bool	IsHeadAccessory() { return GetItemSort() == ITEMSORT_HEAD; }
	//bool	IsRing()		{ return IsFinery() && GetItemType() == ITEMTYPE_RING; }
	//bool	IsBangle()		{ return IsFinery() && GetItemType() == ITEMTYPE_BANGLE; }	// �Ƿ����� -- zlong 2004-02-03
	bool	IsShoes()		{ return GetItemSort() == ITEMSORT_SHOES; }
	bool	IsEquipment()	{ return CItem::IsEquipment(GetInt(ITEMDATA_SORT)); }
	//bool	IsTransSpell()	{ return false; }				//? ���� GetInt(ITEMDATA_TYPE) == 107000099;
	//bool	IsBowSort()		{ return CItem::IsBowSort(GetInt(ITEMDATA_TYPE)); }
	//bool	IsBow()			{ return CItem::IsBow(GetInt(ITEMDATA_TYPE)); }
	//bool	IsCrossBow()	{ return CItem::IsCrossBow(GetInt(ITEMDATA_TYPE)); }
	//bool	IsActionItem()	{ return IsOther() && GetItemType() == ITEMTYPE_ACTIONITEM || IsSpell(); }
	bool	IsTaskItem()	{ return GetItemSort() == ITEMSORT_TASK; }
	//bool	IsGem()			{ return IsOther() && GetItemType() == ITEMTYPE_GEM; }
	//bool	IsNonsuch()		{ return GetQuality() == 9; }
	//bool	IsGameCard()	{ return CItem::IsGameCard(GetInt(ITEMDATA_TYPE)); } //IsOther() && GetItemType() == ITEMTYPE_GAMECARD; }
	bool	IsPoison()		{ return GetItemSort() == ITEMSORT_POISON; }
	bool	IsMedicine()	{ return GetItemSort() == ITEMSORT_MEDICINE; }

	//bool	IsGhostGem()	{ return CItem::IsGhostGem(GetInt(ITEMDATA_TYPE)); }
	// add by zlong 2003-11-24
	//bool	IsChestItem()	{ return (GetInt(ITEMDATA_TYPE) >= TYPE_CHEST_SPACE3) && (GetInt(ITEMDATA_TYPE) <= TYPE_CHEST_SPACE9); }
	// add by zlong 3002-12-05
	bool	IsPick()		{ return 470 == (GetInt(ITEMDATA_SORT)/1000)%1000; }		// �Ƿ��ڿ��õĳ�ͷ
	//bool	IsMantle()		{ return IsFinery() && GetItemType() == ITEMTYPE_MANTLE; }

public: // static
	//static bool	IsBowSort(int nType)	{ return CItem::IsBow(nType) || CItem::IsCrossBow(nType); }
	//static bool	IsBow(int nType)		{ return CItem::GetItemSort(nType) == ITEMSORT_WEAPON2 && CItem::GetItemType(nType) == DWEAPON_BOW; }
	//static bool	IsCrossBow(int nType)	{ return CItem::GetItemSort(nType) == ITEMSORT_WEAPON2 && CItem::GetItemType(nType) == DWEAPON_CROSSBOW; }
	//static bool	IsShield(int nType)		{ return CItem::GetItemSort(nType) == ITEMSORT_SHIELD; }
	//static bool IsGameCard(int nType)	{ return ((nType == CARD_FEE_POINT) || (nType == CARD_FEE_POINT2)); }
	//static bool IsExpend(int nType)		{ return CItem::IsArrowSort(nType) || (CItem::GetItemSort(nType) == ITEMSORT_EXPEND && CItem::GetItemType(nType)  < ITEMTYPE_SPECIAL_USE); }
	//static bool IsCountable(int nType)	{ return CItem::IsArrowSort(nType) || (CItem::GetItemSort(nType) == ITEMSORT_EXPEND); }
	// add by zlong 2003-11-20
	//static bool	IsMount(int nType)		{ return CItem::GetItemSort(nType) == ITEMSORT_MOUNT; }
	//static bool	IsEquipment(int nType)	{ return !CItem::IsArrowSort(nType) && ((GetItemSort(nType) >= IETMSORT_FINERY && GetItemSort(nType) <= ITEMSORT_MOUNT) || CItem::IsShield(nType)); }
	static bool	IsEquipment(int nType) { return (GetItemSort(nType) >= ITEMSORT_WEAPON && GetItemSort(nType) <= ITEMSORT_HEAD); }
	// add by zlong 2003-12-05
	//static bool IsArrowSort(int nType)	{ return CItem::IsArrow(nType) || CItem::IsDart(nType); }
	//static bool IsArrow(int nType)		{ return nType == ARROW_TYPE_ID; }
	static bool IsDart(int nType)		{ return nType == ITEMSORT_DART; }
	static int  GetQuality(int nType)	{ return (nType/1000000000)*10 + (nType%10); }
	static bool IsMedicine(int nType)	{ return nType == ITEMSORT_MEDICINE; }

	//static bool	IsSpell(int nType)		{ return CItem::IsExpend(nType) && CItem::GetItemType(nType)==ITEMTYPE_SCROLL; }
	//static bool	IsWPGBadge(int nType)	{ return nType/100 == 10600 && (nType/10)%10 >= 1 && (nType/10)%10 <= 5 && (nType%10) >= 1 && (nType%10) <= 5; }
	// ħ�걦ʯ�ж� -- zlong 2004-02-05
	//static bool	IsGhostGem(int nType)	{ return CItem::IsExpend(nType) && CItem::GetItemType(nType) == ITEMTYPE_GHOSTGEM; }

	//static bool	IsNeedIdent(int nIdent)	{ return (nIdent & _ITEM_STATUS_NOT_IDENT) != 0; }
	//static int	HideTypeUnident(OBJID idType)	{ if(CItem::IsEquipment(idType)) return ((idType/10)*10)%10000000; if(CItem::IsSpell(idType)) return ((idType/100)*100)%10000000; return idType; }
	//static int	HideTypeQuality(OBJID idType)	{ if(CItem::IsEquipment(idType)) return ((idType/10)*10)%10000000; return idType; }

public:

	//modified by jinggy--2004-11-11
	bool ChangeAddition(int nLevel);//�ı�װ����׷�ӵȼ�

	
	//bool	IsHoldEnable()		{ return IsWeapon1() || IsWeapon2() || IsShield() || IsArrowSort(); }
	// modified by zlong 2003-12-01 -- Sprite is equip enable
	bool	IsEquipEnable()		{ return IsEquipment(); }
	bool	IsEatEnable()		{ return IsMedicine(); }
	//bool	IsPileEnable()		{ return IsExpend() && GetInt(ITEMDATA_AMOUNTLIMIT) > 1; }
	//bool	IsRepairEnable()	{ return !IsExpend() && !IsNeedIdent() && GetInt(ITEMDATA_AMOUNTLIMIT) >= 100 && !IsCannotRepair(); }
	// modified by zlong 2003-11-24 ---- chest item can not Exchange and store
	//bool	IsExchangeEnable()	{ return (GetInt(ITEMDATA_MONOPOLY) & MONOPOLY_MASK) == 0 && !IsChestItem(); }
	//bool	IsStorageEnable()	{ return (GetInt(ITEMDATA_MONOPOLY) & STORAGE_MASK) == 0 && !IsChestItem(); }
	//bool	IsSellEnable()		{ return ((GetInt(ITEMDATA_MONOPOLY) & SELL_DISABLE_MASK) == 0 &&!IsGameCard() && !IsChestItem()); }
	//bool	IsNeverDropWhenDead()	{ return (GetInt(ITEMDATA_MONOPOLY) & NEVER_DROP_WHEN_DEAD_MASK) != 0; }
	//bool	IsNonsuchItem();	//	{ return (GetInt(ITEMDATA_TYPE)%10) >= 8; }
	//bool	IsNormalArrow()		{ return GetInt(ITEMDATA_TYPE) == NORMAL_ARROW_TYPE; }
	// modified by zlong 2003-11-24 ---- chest item is not discardable
	bool	IsDiscardable() { return true; } // return (!IsGameCard() && !IsChestItem()); }
	//bool	IsNeedIdent()		{ return IsNeedIdent(GetInt(ITEMDATA_IDENT)); }
	//bool	IsCannotRepair()	{ return (GetInt(ITEMDATA_IDENT) & _ITEM_STATUS_CANNOT_REPAIR) != 0; }
	//bool	IsNeverWear()		{ return (GetInt(ITEMDATA_IDENT) & _ITEM_STATUS_NEVER_DAMAGE) != 0; }

public:	//���� -- add by zlong 2003-11-28
	int		AwardExp(int nExp, int nLuck = 0);

	int		AdjustOriginalGrowth();
protected:
	int		GetExp()			{ return GetInt(ITEMDATA_EXP); }
	//int		GetGrowth100()		{ return GetInt(ITEMDATA_GROWTH); }

public:	// get
	//int		GetAddition(ITEMADDITIONDATA idx);
	int		GetAttack()			{ return GetInt(ITEMDATA_ATTACK); }
	//int		GetMaxAtk()			{ return GetInt(ITEMDATA_ATTACK_MAX_); }
	//int		GetMinAtk()			{ return GetInt(ITEMDATA_ATTACK_MIN_); }
	//int		GetMgcMaxAtk()		{ return GetInt(ITEMDATA_MAGICATK_MAX_); }
	//int		GetMgcMinAtk()		{ return GetInt(ITEMDATA_MAGICATK_MIN_); }
	int		GetDefence()		{ return GetInt(ITEMDATA_DEFENCE); }
	//int		GetMgcDef()			{ return GetInt(ITEMDATA_MAGICDEF_); }
	int		GetDexteriy()		{ return GetInt(ITEMDATA_DEXTERITY); }
	//int		GetDodge()			{ return GetInt(ITEMDATA_DODGE); }
	int		GetLife()			{ return GetInt(ITEMDATA_LIFE); }
	int		GetPower()			{ return GetInt(ITEMDATA_POWER); }
	//int		GetHitRate()		{ return GetInt(ITEMDATA_HITRATE); }


public: // const
	int		CalcRepairMoney();
	DWORD	GetSellPrice();
	int		GetItemCount() { return 1; } // if (IsExpend()) return GetInt(ITEMDATA_AMOUNT); return 1; }		// ��Ʒ�����������׺�Ʒ����1
	//int		GetWeight()			{ if(IsArrowSort()) return (GetInt(ITEMDATA_AMOUNT)-1)*GetInt(ITEMDATA_WEIGHT_)/ARROW_PILE_WEIGHT + 1; return GetItemCount() * GetInt(ITEMDATA_WEIGHT_); }
	//static 	int		GetWeight(OBJID idType, int nAmount=0);		// nAmount: amount �ֶ�ֵ

public: // modify attribute
	/*void	SetIdent(bool bNeedIdent, bool bUpdate)	{ 
				if(bNeedIdent) SetInt(ITEMDATA_IDENT, GetInt(ITEMDATA_IDENT)|_ITEM_STATUS_NOT_IDENT, bUpdate); 
				else SetInt(ITEMDATA_IDENT, GetInt(ITEMDATA_IDENT)&(~_ITEM_STATUS_NOT_IDENT), bUpdate); }
	void	SetStatus(DWORD dwData, bool bUpdate) { SetInt(ITEMDATA_IDENT, dwData, bUpdate); }*/

public: // gem effect
	int		GetGemDmgEffect		(void);
	int		GetGemMgcAtkEffect	(void);
	int		GetGemHitRateEffect	(void);
	int		GetGemExpEffect		(void);
	int		GetGemWpnExpEffect	(void);
	int		GetGemMgcExpEffect	(void);
	int		GetGemDurEffect		(OBJID idGemType=ID_NONE);

public: // application
	CItem*	Split(int nNum);

public:

	//����ս��ȼ�-------jinggy------2004-11-12
	//void WarGhostLevelUpgrade(CUserPtr pUser);
	//bool WarGhostLevelReset();	
	//�ж��Ƿ���״̬�����౦ʯ-----jinggy---2004-11-12
	bool IsGemActiveAtk();

	int		GetItemSubType();

	int		GetLevel	(void);
	int		GetQuality(void) { return 0; } // GetQuality(GetInt(ITEMDATA_TYPE)); }

	bool	ChangeType	(OBJID idNewType);
	bool	ChangeColor	(int nColor);
	
	bool	RecoverDur			(void);
	int		GetRecoverDurCost	(void);

//protected: // ����
	int		GetItemSort()			{ return CItem::GetItemSort(GetInt(ITEMDATA_SORT)); }
	int		GetItemType()			{ return CItem::GetItemType(GetInt(ITEMDATA_SORT)); }
public:
	static int	GetItemSort(OBJID idType)			{ return idType/100; }		// ���� + ʮ��
	static int	GetItemType(OBJID idType);									// �������أ���λ��ǧλ��*ǧ������������λ*��
	static int	GetSubType(OBJID idType)			{ return idType%100; }

protected: // 
	CItem*	Clone();		// ����Ʒ�����ݿ�

	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_ITEM_H__CA7CE885_1DCF_4B96_B308_FB7F40CCF4BA__INCLUDED_)
