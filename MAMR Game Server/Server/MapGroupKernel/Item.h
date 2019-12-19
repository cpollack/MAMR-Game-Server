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
	TARGET_EUDEMON		= 0x0004,			// ���ԶԻ���ʹ��

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
	bool	IsNormal()		{ return GetItemSort() == ITEMSORT_EXPEND; }
	bool	IsWeapon1()		{ return GetItemSort() == ITEMSORT_WEAPON1; }		// single hand use
	bool	IsWeapon2()		{ return GetItemSort() == ITEMSORT_WEAPON2; }		// two hand use
	bool	IsWeapon()		{ return GetItemSort() == ITEMSORT_WEAPON1 || GetItemSort() == ITEMSORT_WEAPON2; }
	bool	IsMount()		{ return CItem::IsMount(GetInt(ITEMDATA_TYPE)); }
	bool	IsShield()		{ return CItem::IsShield(GetInt(ITEMDATA_TYPE)); }
	bool	IsOther()		{ return GetItemSort() == ITEMSORT_OTHER; }
	bool	IsFinery()		{ return !IsArrowSort() && GetItemSort() == IETMSORT_FINERY; }
	bool	IsArrowSort()	{ return CItem::IsArrowSort(GetInt(ITEMDATA_TYPE)); }
	bool	IsArrow()		{ return CItem::IsArrow(GetInt(ITEMDATA_TYPE)); } //IsNormal() && GetItemType() == ITEMTYPE_ARROW; }
	bool	IsDart()		{ return CItem::IsDart(GetInt(ITEMDATA_TYPE)); } //IsNormal() && GetItemType() == ITEMTYPE_DART; }
	bool	IsSpell()		{ return CItem::IsSpell(GetInt(ITEMDATA_TYPE)); }
	bool	IsExpend()		{ return CItem::IsExpend(GetInt(ITEMDATA_TYPE)); }
	bool	IsHelmet()		{ return IsFinery() && GetItemType() == ITEMTYPE_HELMET; }
	bool	IsNecklace()	{ return IsFinery() && GetItemType() == ITEMTYPE_NECKLACE; }
	bool	IsArmor()		{ return IsFinery() && GetItemType() == ITEMTYPE_ARMOR; }
	bool	IsRing()		{ return IsFinery() && GetItemType() == ITEMTYPE_RING; }
	bool	IsBangle()		{ return IsFinery() && GetItemType() == ITEMTYPE_BANGLE; }	// �Ƿ����� -- zlong 2004-02-03
	bool	IsShoes()		{ return IsFinery() && GetItemType() == ITEMTYPE_SHOES; }
	bool	IsEquipment()	{ return CItem::IsEquipment(GetInt(ITEMDATA_TYPE)); }
	bool	IsTransSpell()	{ return false; }				//? ���� GetInt(ITEMDATA_TYPE) == 107000099;
	bool	IsBowSort()		{ return CItem::IsBowSort(GetInt(ITEMDATA_TYPE)); }
	bool	IsBow()			{ return CItem::IsBow(GetInt(ITEMDATA_TYPE)); }
	bool	IsCrossBow()	{ return CItem::IsCrossBow(GetInt(ITEMDATA_TYPE)); }
	bool	IsActionItem()	{ return IsOther() && GetItemType() == ITEMTYPE_ACTIONITEM || IsSpell(); }
	bool	IsTaskItem()	{ return IsOther() && GetItemType() == ITEMTYPE_TASKITEM; }
	bool	IsGem()			{ return IsOther() && GetItemType() == ITEMTYPE_GEM; }
	bool	IsNonsuch()		{ return GetQuality() == 9; }
	bool	IsGameCard()	{ return CItem::IsGameCard(GetInt(ITEMDATA_TYPE)); } //IsOther() && GetItemType() == ITEMTYPE_GAMECARD; }
	bool	IsMedicine()	{ return CItem::IsMedicine(GetInt(ITEMDATA_TYPE)); }

	bool	IsGhostGem()	{ return CItem::IsGhostGem(GetInt(ITEMDATA_TYPE)); }
	// add by zlong 2003-11-24
	bool	IsChestItem()	{ return (GetInt(ITEMDATA_TYPE) >= TYPE_CHEST_SPACE3) && (GetInt(ITEMDATA_TYPE) <= TYPE_CHEST_SPACE9); }
	// add by zlong 3002-12-05
	bool	IsPick()		{ return 470 == (GetInt(ITEMDATA_TYPE)/1000)%1000; }		// �Ƿ��ڿ��õĳ�ͷ
	bool	IsMantle()		{ return IsFinery() && GetItemType() == ITEMTYPE_MANTLE; }

public: // static
	static bool	IsBowSort(int nType)	{ return CItem::IsBow(nType) || CItem::IsCrossBow(nType); }
	static bool	IsBow(int nType)		{ return CItem::GetItemSort(nType) == ITEMSORT_WEAPON2 && CItem::GetItemType(nType) == DWEAPON_BOW; }
	static bool	IsCrossBow(int nType)	{ return CItem::GetItemSort(nType) == ITEMSORT_WEAPON2 && CItem::GetItemType(nType) == DWEAPON_CROSSBOW; }
	static bool	IsShield(int nType)		{ return CItem::GetItemSort(nType) == ITEMSORT_SHIELD; }
	static bool IsGameCard(int nType)	{ return ((nType == CARD_FEE_POINT) || (nType == CARD_FEE_POINT2)); }
	static bool IsExpend(int nType)		{ return CItem::IsArrowSort(nType) || (CItem::GetItemSort(nType) == ITEMSORT_EXPEND && CItem::GetItemType(nType)  < ITEMTYPE_SPECIAL_USE); }
	static bool IsCountable(int nType)	{ return CItem::IsArrowSort(nType) || (CItem::GetItemSort(nType) == ITEMSORT_EXPEND && !CItem::IsEudemon(nType) && !CItem::IsEudemonEgg(nType)); }
	// add by zlong 2003-11-20
	static bool	IsMount(int nType)		{ return CItem::GetItemSort(nType) == ITEMSORT_MOUNT; }
	static bool	IsEquipment(int nType)	{ return !CItem::IsArrowSort(nType) && ((GetItemSort(nType) >= IETMSORT_FINERY && GetItemSort(nType) <= ITEMSORT_MOUNT) || CItem::IsShield(nType)); }
	// add by zlong 2003-12-05
	static bool IsArrowSort(int nType)	{ return CItem::IsArrow(nType) || CItem::IsDart(nType); }
	static bool IsArrow(int nType)		{ return nType == ARROW_TYPE_ID; }
	static bool IsDart(int nType)		{ return nType == DART_TYPE_ID; }
	static int  GetQuality(int nType)	{ return (nType/1000000000)*10 + (nType%10); }
	static bool IsMedicine(int nType)	{ return CItem::IsExpend(nType) && CItem::GetItemType(nType)==ITEMTYPE_PHYSIC; }

	static bool	IsSpell(int nType)		{ return CItem::IsExpend(nType) && CItem::GetItemType(nType)==ITEMTYPE_SCROLL; }
	static bool	IsWPGBadge(int nType)	{ return nType/100 == 10600 && (nType/10)%10 >= 1 && (nType/10)%10 <= 5 && (nType%10) >= 1 && (nType%10) <= 5; }
	// ħ�걦ʯ�ж� -- zlong 2004-02-05
	static bool	IsGhostGem(int nType)	{ return CItem::IsExpend(nType) && CItem::GetItemType(nType) == ITEMTYPE_GHOSTGEM; }

	static bool	IsNeedIdent(int nIdent)	{ return (nIdent & _ITEM_STATUS_NOT_IDENT) != 0; }
	static int	HideTypeUnident(OBJID idType)	{ if(CItem::IsEquipment(idType)) return ((idType/10)*10)%10000000; if(CItem::IsSpell(idType)) return ((idType/100)*100)%10000000; return idType; }
	static int	HideTypeQuality(OBJID idType)	{ if(CItem::IsEquipment(idType)) return ((idType/10)*10)%10000000; return idType; }

public:

	//modified by jinggy--2004-11-11
	bool ChangeAddition(int nLevel);//�ı�װ����׷�ӵȼ�

	
	bool	IsHoldEnable()		{ return IsWeapon1() || IsWeapon2() || IsShield() || IsArrowSort(); }
	// modified by zlong 2003-12-01 -- Sprite is equip enable
	bool	IsEquipEnable()		{ return IsEquipment() || IsArrowSort() || IsSprite(); }
	bool	IsEatEnable()		{ return IsMedicine(); }
	bool	IsPileEnable()		{ return IsExpend() && GetInt(ITEMDATA_AMOUNTLIMIT) > 1; }
	bool	IsRepairEnable()	{ return !IsExpend() && !IsNeedIdent() && GetInt(ITEMDATA_AMOUNTLIMIT) >= 100 && !IsCannotRepair(); }
	// modified by zlong 2003-11-24 ---- chest item can not Exchange and store
	bool	IsExchangeEnable()	{ return (GetInt(ITEMDATA_MONOPOLY) & MONOPOLY_MASK) == 0 && !IsChestItem(); }
	bool	IsStorageEnable()	{ return (GetInt(ITEMDATA_MONOPOLY) & STORAGE_MASK) == 0 && !IsChestItem(); }
	bool	IsSellEnable()		{ return ((GetInt(ITEMDATA_MONOPOLY) & SELL_DISABLE_MASK) == 0 &&!IsGameCard() && !IsChestItem()); }
	bool	IsNeverDropWhenDead()	{ return (GetInt(ITEMDATA_MONOPOLY) & NEVER_DROP_WHEN_DEAD_MASK) != 0; }
	bool	IsNonsuchItem();	//	{ return (GetInt(ITEMDATA_TYPE)%10) >= 8; }
	bool	IsNormalArrow()		{ return GetInt(ITEMDATA_TYPE) == NORMAL_ARROW_TYPE; }
	// modified by zlong 2003-11-24 ---- chest item is not discardable
	bool	IsDiscardable()		{ return (!IsGameCard() && !IsChestItem()); }
	bool	IsNeedIdent()		{ return IsNeedIdent(GetInt(ITEMDATA_IDENT)); }
	bool	IsCannotRepair()	{ return (GetInt(ITEMDATA_IDENT) & _ITEM_STATUS_CANNOT_REPAIR) != 0; }
	bool	IsNeverWear()		{ return (GetInt(ITEMDATA_IDENT) & _ITEM_STATUS_NEVER_DAMAGE) != 0; }
	
	
public:	// ���� -- zlong 2004-02-03
	static bool	IsEudemon(OBJID idType)			{ return CItem::GetItemSort(idType) == ITEMSORT_EXPEND && CItem::GetItemType(idType) == ITEMTYPE_EUDEMON; }
	static bool	IsEudemonEgg(OBJID idType)		{ return CItem::GetItemSort(idType) == ITEMSORT_EXPEND && CItem::GetItemType(idType) == ITEMTYPE_EUDEMON_EGG; }
	static int	GetEudemonType(OBJID idType)	{ return (idType/1000)%10; }
	bool	IsEudemon()			{ return CItem::IsEudemon(GetInt(ITEMDATA_TYPE)); }
	bool	IsEudemonEgg()		{ return CItem::IsEudemonEgg(GetInt(ITEMDATA_TYPE)); }
	bool	IsEvilEudemon()		{ return (IsEudemon() && (GetInt(ITEMDATA_TYPE)%10)==EUDEMON_GROUP_EVIL); }

	bool	IsEvolveEnable();
	bool	IsEvolve2Enable();
	bool	IsAliveEudemon()	{ return (IsEudemon() && GetInt(ITEMDATA_EUDEMON_LIFE) > 0); }

	int		GetEudemonType()	{ return CItem::GetEudemonType(GetInt(ITEMDATA_TYPE)); }
	int		GetEudemonLevel()	{ return GetInt(ITEMDATA_EUDEMON_LEVEL); }
//	int     GetEudemonGrowth100(){return GetInt(ITEMDATA_GROWTH)*GetInt(ITEMDATA_GROWTH_ORIGINAL)/100;}
//	bool	SendEudemonAttrib(CUser* pUser);
	int		GetEudemonMaxLife()	{ return __max(1, (GetEudemonLevel() * (GetInt(ITEMDATA_LIFE) * GetInt(ITEMDATA_GROWTH) + GetAddition(ITEMADDITIONDATA_LIFE)*100) / 10000)); }
	OBJID	GetEudemonID()		{ CHECKF (m_pEudemonData); return m_pEudemonData->GetID(); }

	OBJID	GetDivineID()		{ return (GetInt(ITEMDATA_TYPE)/10%10); }
	UCHAR	GetRelationShip(OBJID idDivine);
	bool	AddRelationShip(OBJID idDivine, int nValue);

public:	//���� -- add by zlong 2003-11-28
	static bool	IsSprite(OBJID idType)		{ return CItem::GetItemSort(idType) == ITEMSORT_EXPEND && CItem::GetItemType(idType) == ITEMTYPE_SPRITE; }
	static int	GetSpriteType(OBJID idType)	{ return (idType/1000)%10; }
	bool	IsSprite()			{ return CItem::IsSprite(GetInt(ITEMDATA_TYPE)); }
	int		GetSpriteType()		{ return CItem::GetSpriteType(GetInt(ITEMDATA_TYPE)); }
	int		GetSpriteLevel()	{ return GetInt(ITEMDATA_SPRITE_LEVEL); }

	int		AwardExp(int nExp, int nLuck = 0);
	int		AddGrowth(int nGrowth);

	int		AdjustOriginalGrowth();
protected:
	void	GrowUp(int nLuck = 0);
	int		GetExp()			{ return GetInt(ITEMDATA_EXP); }
	int		GetGrowth100()		{ return GetInt(ITEMDATA_GROWTH); }

public:	// get
	int		GetAddition(ITEMADDITIONDATA idx);
	int		GetMaxAtk()			{ return GetAddition(ITEMADDITIONDATA_ATTACK_MAX) + GetInt(ITEMDATA_ATTACK_MAX_); }
	int		GetMinAtk()			{ return GetAddition(ITEMADDITIONDATA_ATTACK_MIN) + GetInt(ITEMDATA_ATTACK_MIN_); }
	int		GetMgcMaxAtk()		{ return GetAddition(ITEMADDITIONDATA_MGCATK_MAX) + GetInt(ITEMDATA_MAGICATK_MAX_); }
	int		GetMgcMinAtk()		{ return GetAddition(ITEMADDITIONDATA_MGCATK_MIN) + GetInt(ITEMDATA_MAGICATK_MIN_); }
	int		GetDef()			{ return GetAddition(ITEMADDITIONDATA_DEFENSE) + GetInt(ITEMDATA_DEFENSE_); }
	int		GetMgcDef()			{ return GetAddition(ITEMADDITIONDATA_MAGICDEF) + GetInt(ITEMDATA_MAGICDEF_); }
	int		GetDexteriy()		{ return GetAddition(ITEMADDITIONDATA_DEXTERITY); }	// + GetInt(ITEMDATA_DEXTERITY); }
	int		GetDodge()			{ return GetAddition(ITEMADDITIONDATA_DODGE) + GetInt(ITEMDATA_DODGE); }
	int		GetLife()			{ return GetAddition(ITEMADDITIONDATA_LIFE) + GetInt(ITEMDATA_LIFE); }
	int		GetHitRate()		{ return GetInt(ITEMDATA_HITRATE); }


public: // const
	int		CalcRepairMoney();
	DWORD	GetSellPrice();
	int		GetItemCount()			{ if(IsExpend()) return GetInt(ITEMDATA_AMOUNT); return 1; }		// ��Ʒ�����������׺�Ʒ����1
	int		GetWeight()			{ if(IsArrowSort()) return (GetInt(ITEMDATA_AMOUNT)-1)*GetInt(ITEMDATA_WEIGHT_)/ARROW_PILE_WEIGHT + 1; return GetItemCount() * GetInt(ITEMDATA_WEIGHT_); }
	static 	int		GetWeight(OBJID idType, int nAmount=0);		// nAmount: amount �ֶ�ֵ

public: // modify attribute
	void	SetIdent(bool bNeedIdent, bool bUpdate)	{ 
				if(bNeedIdent) SetInt(ITEMDATA_IDENT, GetInt(ITEMDATA_IDENT)|_ITEM_STATUS_NOT_IDENT, bUpdate); 
				else SetInt(ITEMDATA_IDENT, GetInt(ITEMDATA_IDENT)&(~_ITEM_STATUS_NOT_IDENT), bUpdate); }
	void	SetStatus(DWORD dwData, bool bUpdate) { SetInt(ITEMDATA_IDENT, dwData, bUpdate); }

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
	int		GetQuality	(void)	{ return GetQuality(GetInt(ITEMDATA_TYPE)); }

	bool	ChangeType	(OBJID idNewType);
	bool	ChangeColor	(int nColor);
	
	bool	RecoverDur			(void);
	int		GetRecoverDurCost	(void);

protected: // ����
	int		GetItemSort()			{ return CItem::GetItemSort(GetInt(ITEMDATA_TYPE)); }
	int		GetItemType()			{ return CItem::GetItemType(GetInt(ITEMDATA_TYPE)); }
public:
	static int	GetItemSort(OBJID idType)			{ return (idType%10000000)/100000; }		// ���� + ʮ��
	static int	GetItemType(OBJID idType);									// �������أ���λ��ǧλ��*ǧ������������λ*��
public:

	//---jinggy---����ϵͳ---begin
	void WarGhostLevelDec(int nDec);
	int GetSuperAddition();
	int GetWarGhostLevel();

	bool DecSuperAddition();

	bool UpSuperAddition();
	bool UpQuality();
	bool UpLevel();

	bool IsGemForEmbedEquip();
	bool IsGemForUpSuperAddition();
	bool IsGemForUpQuality();
	bool IsGemForUpLevel();
	//---jinggy---����ϵͳ---end
	static int	GetSubType(OBJID idType)			{ return (idType%1000000)/1000; }

protected: // 
	CItem*	Clone();		// ����Ʒ�����ݿ�

	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_ITEM_H__CA7CE885_1DCF_4B96_B308_FB7F40CCF4BA__INCLUDED_)
