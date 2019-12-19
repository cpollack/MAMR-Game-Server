// ItemData.h: interface for the CItemData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMDATA_H__28794933_A926_4C9A_AACF_1A95340DA94B__INCLUDED_)
#define AFX_ITEMDATA_H__28794933_A926_4C9A_AACF_1A95340DA94B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameObj.h"
#include "ItemType.h"

//////////////////////////////////////////////////////////////////////
const int MAX_INTIMACY		= 255;
//////////////////////////////////////////////////////////////////////

enum // ������������ö��
{
	_SPRITE_ADDITION_PATK = 0, // ��Ԫ�ؾ���--������������
	_SPRITE_ADDITION_PDEF = 1, // ��Ԫ�ؾ���--�������������
	_SPRITE_ADDITION_MATK = 2, // ��Ԫ�ؾ���--����ħ��������
	_SPRITE_ADDITION_MDEF = 3, // ˮԪ�ؾ���--����ħ��������
	_SPRITE_ADDITION_SOUL = 4, // ��Ԫ�ؾ���--���Ӿ���
};

enum ITEMDATA{
		ITEMDATA_ID_=0,			// use for insert
		ITEMDATA_TYPE=1,
		ITEMDATA_OWNERID,
		ITEMDATA_PLAYERID,
		ITEMDATA_AMOUNT,			//ITEMDATA_EXP = ITEMDATA_AMOUNT,				// ���龭�� -- ���ñ�ʾ�������ܶ�
		ITEMDATA_AMOUNTLIMIT,		//ITEMDATA_ATTRIB = ITEMDATA_AMOUNTLIMIT,		// ���鸽������ ATTRIB100 -- ���޵ȼ�
		ITEMDATA_IDENT,
		ITEMDATA_POSITION,
		
		ITEMDATA_GEM1,				
		ITEMDATA_GEM2,              
		ITEMDATA_MAGIC1,            

		ITEMDATA_MAGIC2,			ITEMDATA_LUCK = ITEMDATA_MAGIC2,		// ����
		ITEMDATA_MAGIC3,			ITEMDATA_ADDITION = ITEMDATA_MAGIC3,	// ׷��
		ITEMDATA_DATA,				//ITEMDATA_GROWTH = ITEMDATA_DATA,			// ����ɳ��� -- ���޳ɳ���ϵ��
	
		//---jinggy---2004-11-19---ʥսħ��---����ϵͳ�������ӵ��ֶ�---begin
		ITEMDATA_WARGHOSTEXP,    //ʥս�е�ս�꾭��ֵ							// ���ñ�ʾ��������ֵ
		ITEMDATA_GEMTYPE,	     //ʥս�еļ��ܣ�ע�벻ͬ״̬�����౦ʯʵ�֣�	// ���޾���
		ITEMDATA_AVAILABLETIME,
		//---jinggy---2004-11-19---ʥսħ��---����ϵͳ�������ӵ��ֶ�---end

		/////////////////////////////////////
		ITEMDATA_INTIMACY=80,				//? for mount, NOTE: no this field

		// for sprite -- add by zlong 2003-12-05
		ITEMDATA_EXP	= 90,					// --> ���޾���
		ITEMDATA_ATTRIB	= 91,		ITEMDATA_EUDEMON_LEVEL = 91,	// --> ���޵ȼ�
		ITEMDATA_GROWTH	= 92,					// --> ���޳ɳ���ϵ��
		ITEMDATA_EUDEMON_LIFE	= 93,			// ��������
		ITEMDATA_FIDELITY		= 94,			// �������ܶ�


		ITEMTYPEDATA_OFFSET=100,		// ������������ʹ��
		ITEMDATA_NAME=101,
		ITEMDATA_REQ_PROF,			// ְҵ����
		ITEMDATA_LEVEL,
		ITEMDATA_REQ_LEVEL,			// �ȼ�����				ITEMDATA_SPRITE_LEVEL
		ITEMDATA_REQ_SEX,			// �Ա�����
		ITEMDATA_REQ_FORCE,			// ��������
		ITEMDATA_REQ_DEX,			// ��������
		ITEMDATA_REQ_HEALTH,		// ��������
		ITEMDATA_REQ_SOUL,			// ��������
		ITEMDATA_MONOPOLY,
		ITEMDATA_WEIGHT_,				// no immediacy
		ITEMDATA_PRICE,
		ITEMDATA_ACTION,
		ITEMDATA_ATTACK_MAX_,		//ITEMDATA_GROWTH_ORIGINAL
		ITEMDATA_ATTACK_MIN_,		//ITEMDATA_LEVEXP
		ITEMDATA_DEFENSE_,
		ITEMDATA_MAGICATK_MIN_,
		ITEMDATA_DODGE,					//	ITEMDATA_ADD_SOUL = ITEMDATA_DODGE,
		ITEMDATA_LIFE,
		ITEMDATA_MANA,
		ITEMDATA_AMOUNT_ORIGINAL,
		ITEMDATA_AMOUNTLIMIT_ORIGINAL,
		ITEMDATA_IDENT_ORIGINAL,
		ITEMDATA_GEM1_ORIGINAL,
		ITEMDATA_GEM2_ORIGINAL,
		ITEMDATA_MAGIC1_ORIGINAL,
		ITEMDATA_MAGIC2_ORIGINAL,
		ITEMDATA_MAGIC3_ORIGINAL,
		ITEMDATA_MAGICATK_MAX_,
		ITEMDATA_MAGICDEF_,
		ITEMDATA_ATKRANGE,
		ITEMDATA_ATKSPEED,
		ITEMDATA_HITRATE,					// ������
		ITEMDATA_MONSTERTYPE,				// ��������id
		ITEMDATA_TARGET,

		ITEMDATA_SPRITE_LEVEL = 200,		// ����ȼ� װ���������ҵĵȼ����벻�����ھ���ĵȼ���2��
		ITEMDATA_GROWTH_ORIGINAL = 201,		// ����ԭʼ�ɳ���
		ITEMDATA_LEVEXP = 202,				// ������������һ����Ҫ�ľ���ֵ
};

//////////////////////////////////////////////////////////////////////
//	ITEMDATA_MONOPOLY,
const DWORD	MONOPOLY_MASK				= 0x01;
const DWORD	STORAGE_MASK				= 0x02;
const DWORD	DROP_HINT_MASK				= 0x04;
const DWORD	SELL_HINT_MASK				= 0x08;
const DWORD	NEVER_DROP_WHEN_DEAD_MASK	= 0x10;
const DWORD	SELL_DISABLE_MASK			= 0x20;


const int	MAGIC_NONE				= 0;
const int	GEM_NONE				= 0;
const int	GEM_HOLE				= 255;

//////////////////////////////////////////////////////////////////////
// ��Ʒ��ķ���
const int	ITEMSORT_INVALID				=	-1;
const int	ITEMSORT_EXPEND					=	10;	// �׺�Ʒ
const int	IETMSORT_FINERY					=	1;	// ����
const int	ITEMSORT_WEAPON1				=	4;	// ����������������
const int	ITEMSORT_MOUNT					=	6;	// ����
const int	ITEMSORT_OTHER					=	7;	// ����, ����ֱ��ʹ��

// ���·����Ѿ���ʹ��
	const int	ITEMSORT_WEAPON2				=	-1;//5;	// ˫������
	const int	ITEMSORT_SHIELD					=	-1;//9;	// ����

//////////////////////////////////////////////////////////////////////
// ITEMSORT_FINERY �����Ʒ
const int	ITEMTYPE_HELMET				=	10000;	// ͷ��
const int	ITEMTYPE_NECKLACE			=	20000;	// ����
const int	ITEMTYPE_ARMOR				=	30000;	// ����
const int	ITEMTYPE_BANGLE				=	40000;	// ����
const int	ITEMTYPE_MANTLE				=	50000;	// ����
const int	ITEMTYPE_SHOES				=	60000;	// Ь��

// ���·����Ѿ���ʹ��
	const int	ITEMTYPE_RING				=	-1;//50000;	// ��ָ

//////////////////////////////////////////////////////////////////////
// ITEMSORT_EXPEND �����Ʒ
const int	ITEMTYPE_INVALID			=	-1;	  // �Ƿ�

const int	ITEMTYPE_PHYSIC				=	10000;//ҩƷ
const int	ITEMTYPE_MEDICINE_HP			=	10000;//��Ѫҩ
const int	ITEMTYPE_MEDICINE_MP			=	11000;//��ħ��ҩ
const int	ITEMTYPE_POISON					=	12000;//��ҩ
const int	ITEMTYPE_SCROLL				=	20000;//����
const int	ITEMTYPE_SCROLL_SPECIAL			=	20000;//������ᣬ�磺�سǾ�ף�������
const int	ITEMTYPE_SCROLL_MSKILL			=	21000;//ħ��ʦ���ܾ���
const int	ITEMTYPE_SCROLL_SSKILL			=	22000;//սʿ���ܾ���
const int	ITEMTYPE_SCROLL_BSKILL			=	23000;//�����ּ��ܾ��� <== ��Ϊ������

const int	ITEMTYPE_GHOSTGEM			=	30000;		// ħ�걦ʯ
const int	ITEMTYPE_GHOSTGEM_ACTIVE_ATK	=	31000;	// ״̬������
const int	ITEMTYPE_GHOSTGEM_PASSIVE_ATK	=	32000;	// ״̬������
const int	ITEMTYPE_GHOSTGEM_EUDEMON		=	33000;	// ������
const int	ITEMTYPE_GHOSTGEM_RELEASE		=	34000;	// �����
const int	ITEMTYPE_GHOSTGEM_TRACE			=	35000;	// ׷ɱ��
const int	ITEMTYPE_GHOSTGEM_PROTECTIVE	=	36000;	// ������
const int	ITEMTYPE_GHOSTGEM_SPECIAL		=	37000;	// ������
const int   ITEMTYPE_GHOSTGEM_EMBEDEQUIP	=	38000;	// ����Ƕ��װ���ı�ʯ---jinggy
//---jinggy 2004-11-9 --begin---ʥս����ϵͳ�õ��� 
const int   ITEMTYPE_GHOSTGEM_FORQUALITY = 1037160; //���װ��Ʒ�ʵı�ʯ ����꾧ʯ��
const int   ITEMTYPE_GHOSTGEM_FORGHOSTLEVEL = 1037150;//����װ��ħ��ȼ��ı�ʯ
const int   ITEMTYPE_GHOSTGEM_UPGRADE_EQUIPLEVEL = 1037170;//��ħ��ʯ����ħ��ʯtype��1037170��������������װ���ĵȼ���
//---jinggy 2004-11-9 --end---ʥս����ϵͳ�õ��� 


const int	ITEMTYPE_NOT_DIRECTUSE		=	40000;//������˫��ʹ�õ� -- ľ�ġ���ʯ����Դ��

//===================================
const int	ITEMTYPE_SPECIAL_USE		=	50000;	// ���ڴ˱�����ϵ�Ϊ������;����Ʒ

const int	ITEMTYPE_SPRITE				=	50000;// ����
const int	ITEMTYPE_SPRITE_PATK		=		50000;// ��Ԫ�ؾ���--������������
const int	ITEMTYPE_SPRITE_PDEF		=		51000;// ��Ԫ�ؾ���--�������������
const int	ITEMTYPE_SPRITE_MATK		=		52000;// ��Ԫ�ؾ���--����ħ��������
const int	ITEMTYPE_SPRITE_MDEF		=		53000;// ˮԪ�ؾ���--����ħ��������
const int	ITEMTYPE_SPRITE_SOUL		=		54000;// ��Ԫ�ؾ���--���Ӿ���

const int	ITEMTYPE_SPECIAL			=	60000;//������Ʒ
const int	ITEMTYPE_SPECIAL_VALUABLES		=	60000;//���������Ʒ�������Ԫ��
const int	ITEMTYPE_SPECIAL_UNREPAIRABLE	=	61000;//�����޸��Ĺ�����Ʒ

// ���� -- zlong 2004-02-03
const int	ITEMTYPE_EUDEMON			=	70000;	//����
const int	ITEMTYPE_EUDEMON_SPEED			=	71000;	// �ٶ���
const int	ITEMTYPE_EUDEMON_PATK			=	72000;	// ������
const int	ITEMTYPE_EUDEMON_DEF			=	73000;	// ������
const int	ITEMTYPE_EUDEMON_MATK			=	74000;	// ħ��������
const int	ITEMTYPE_EUDEMON_BOMB			=	75000;	// ������
const int	ITEMTYPE_EUDEMON_PROTECTIVE		=	76000;	// ������
const int	ITEMTYPE_EUDEMON_ATTACH			=	77000;	// ������
const int	ITEMTYPE_EUDEMON_VARIATIONAL	=	78000;	// ������

const int	ITEMTYPE_EUDEMON_EGG		=	80000;	// ���޵�
//===================================

/*
const int	ITEMTYPE_MEDICINE			=	00000;// ��ҩ 
const int	ITEMTYPE_POISON				=	10000;// ��ҩ
const int	ITEMTYPE_DART				=	20000;// ʸ
const int	ITEMTYPE_BOOK				=	30000;// ����
const int	ITEMTYPE_NOTUSE				=	40000;// ����
const int	ITEMTYPE_ARROW				=	50000;// ��
const int	ITEMTYPE_SPELL				=	60000;// ������
const int	ITEMTYPE_NOT_DIRECTUSE		=	70000;// ������˫��ʹ�õģ���������Ʒ����ʯ��ľ�ĵ���Դ�࣬ǧλ�������ࣩ
const int	ITEMTYPE_EX0				=	80000;// ��չ0
const int	ITEMTYPE_EX1				=	90000;// ��չ1
*/

//////////////////////////////////////////////////////////////////////
// ITEMSORT_OTHER �����Ʒ
const int	ITEMTYPE_GEM				=	00000;// ��ʯ��Ʒ
const int	ITEMTYPE_TASKITEM			=	10000;// ������Ʒ
const int	ITEMTYPE_ACTIONITEM			=	20000;// Action��Ʒ
const int	ITEMTYPE_GAMECARD			=	80000;// �㿨���¿�

/*/////////////////////////////////////////////////////////////////////
//2003-01-13 10:36:24  ���
// Necklace type define
const int	ITEMTYPE_NECKLACE			=	00000;// ���� 
const int	ITEMTYPE_SACHET				=	10000;// ���
const int	ITEMTYPE_AMULET				=	20000;// �����

//2003-01-13 10:46:37  ���
// Ring type define
const int	ITEMTYPE_RING				=	00000;// ��ָ 
const int	ITEMTYPE_THUMB_RING			=	10000;// ��ָ 
const int	ITEMTYPE_BANGLE				=	20000;// ����

//2003-01-13 11:05:03  ���
// Singlehand Weapon define
const int	SWEAPON_NONE				=	00000;// ����
const int	SWEAPON_BLADE				=	10000;// ��
const int	SWEAPON_AXE					=	20000;// ��
const int	SWEAPON_HAMMER				=	30000;// ��
const int	SWEAPON_HOOK				=	40000;// ��
const int	SWEAPON_CLUB				=	50000;// ��/��
const int	SWEAPON_SWORD				=	60000;// ��
const int	SWEAPON_CRUTCH				=	70000;// ��
const int	SWEAPON_SCOURGE				=	80000;// ��/�
const int	SWEAPON_SHORT				=	90000;// �̱���
*/
// Doublehand Weapon define
const int	DWEAPON_BOW					=	00000;// ��
const int	DWEAPON_CROSSBOW			=	 1000;// ��
const int	DWEAPON_BLADE				=	10000;// ��
const int	DWEAPON_AXE					=	20000;// ��
const int	DWEAPON_HAMMER				=	30000;// ��
const int	DWEAPON_HOOK				=	40000;// ��
const int	DWEAPON_STAFF				=	50000;// ��
const int	DWEAPON_SHOVEL				=	60000;// ��
const int	DWEAPON_HALBERD				=	70000;// �
const int	DWEAPON_FORK				=	80000;// ��
const int	DWEAPON_SPEAR				=	90000;// ǹ

//////////////////////////////////////////////////////////////////////

// add by zlong 2003-12-01
const int	MAX_SPRITE_GROWTH		= 500;	// ��������ɳ���*100
const int	MAX_SOUL_SPRITE_GROWTH	= 200;	// �Ӿ���ľ������ɳ���*100

const int	EUDEMON_DEC_FIDELITY_WHEN_DIE		= 10;			// ����������10�����ܶ�
const int	EUDEMON_DEC_FIDELITY_WHEN_DEAL		= 30;			// ����ת��Ҫ��30�����ܶ�


//////////////////////////////////////////////////////////////////////
//const int	ITEMPOSITION_BACKPACK	= 0;	// ��ͨ��Ʒ����
//const int	ITEMPOSITION_NONE		= 0;
const int	ITEMPOSITION_EQUIPBEGIN		= 1;
const int	ITEMPOSITION_HELMET		= 1;	// ͷ��
const int	ITEMPOSITION_NECKLACE	= 2;	// ����
const int	ITEMPOSITION_ARMOR		= 3;	// ����
const int	ITEMPOSITION_WEAPONR	= 4;	// ����
const int	ITEMPOSITION_WEAPONL	= 5;
const int	ITEMPOSITION_RINGR		= 6;
const int	ITEMPOSITION_RINGL		= 7;	// ����
const int	ITEMPOSITION_SHOES		= 8;	// Ь��
const int	ITEMPOSITION_MOUNT		= 9;
const int	ITEMPOSITION_SPRITE		= 10;	// ����  -- add by zlong 2003-11-27 
const int	ITEMPOSITION_MANTLE		= 11;	// ���� -- zlong 2004-02-04
const int	ITEMPOSITION_EQUIPEND		= 12;

const int	ITEMPOSITION_PACK_BEGIN				= 50;
const int	ITEMPOSITION_BACKPACK			= 50;	// ��ͨ��Ʒ����
const int	ITEMPOSITION_GHOSTGEM_PACK		= 51;	// ħ�걦ʯ����
const int	ITEMPOSITION_EUDEMONEGG_PACK	= 52;	// ���޵�����
const int	ITEMPOSITION_EUDEMON_PACK		= 53;	// ���ޱ���
const int	ITEMPOSITION_PACK_END				= 54;
const int	ITEMPOSITION_PACK_LIMIT			= 70;

const int	ITEMPOSITION_USER_LIMIT	= 199;
const int	ITEMPOSITION_STORAGE	= 201;
const int	ITEMPOSITION_TRUNK		= 202;
const int	ITEMPOSITION_CHEST		= 203;
const int	ITEMPOSITION_PLAYERTASK	= 204;			// Ӷ������Ʒ
const int	ITEMPOSITION_EUDEMON_BROODER	= 205;	// ���޷�����
const int	ITEMPOSITION_EUDEMON_STORAGE	= 206;	// ���޴洢�ֿ�
const int	ITEMPOSITION_AUCTION_STORAGE    = 207;  // Npc����ֿ⣨�����Ʒ��
const int   ITEMPOSITION_AUCTION_SYS_STORAGE= 208;  // Npc����ֿ⣨ϵͳ��Ʒ��
const int	ITEMPOSITION_GROUND		= 254;			// �������ݿ�
const int	ITEMPOSITION_NONE		= 255;			// �Ƿ�λ��

//////////////////////////////////////////////////////////////////////
char	szItemTable[];
typedef	CGameData<ITEMDATA,szItemTable, szID>		CGameItemData;

//////////////////////////////////////////////////////////////////////
enum EUDEMONDATA{
	EUDEMONDATA_ID = 0,				// ����ID
	EUDEMONDATA_OWNERID,			// ������ƷID
	EUDEMONDATA_NAME,				// ��������
	EUDEMONDATA_RELATIONSHIP,		// ���������޹�ϵ
};

char	szEudemonTable[];
typedef		CGameData<EUDEMONDATA, szEudemonTable, szID>	CEudemonData;

//////////////////////////////////////////////////////////////////////
#include "T_SingleObjSet2.h"
#include "T_SingleMap2.h"
#include "UserTable.h"
#include "ItemAddition.h"

//////////////////////////////////////////////////////////////////////
class IDatabase;
class IRecord;
class IRecordset;
class CItemData : public CGameObj  
{
protected:
	CItemData();
	virtual ~CItemData();

public:
	bool	Create			(IRecord* pDefault, const ItemInfoStruct* pInfo, IRecord* pDefaultEudemonData, bool bInsert=true, OBJID idNew=ID_NONE);			// false: �������ݿ�
	bool	Create			(IRecord* pDefault, OBJID idType, OBJID idUser, int nPosition, IRecord* pDefaultEudemonData=NULL);
	bool	Create			(OBJID idItem, IDatabase* pDb);
	bool	Create			(IRecordset* pRes, IDatabase* pDb);
	bool	DeleteRecord		();
	static bool		DeleteItemRecord	(OBJID id, IDatabase* pDb);

public: // info
	bool	GetInfo	(ItemInfoStruct* pInfo);
	bool	SaveInfo		(void);

public: // get set
	OBJID		GetID()					{ return m_pData->GetKey(); }

	int		GetInt(ITEMDATA idx);
	LPCTSTR	GetStr(ITEMDATA idx);
	void	SetInt(ITEMDATA idx, int nData, bool bUpdate = false);
	void	SetStr(ITEMDATA idx, LPCTSTR szData, int nSize, bool bUpdate = false);
protected:
	bool	IsMount()				{ return ((m_pData->GetInt(ITEMDATA_TYPE)%10000000)/100000) == ITEMSORT_MOUNT; }		// ����GEM1��INTIMACY���ദ��
	bool	IsSprite()				{ return ((m_pData->GetInt(ITEMDATA_TYPE)%10000000)/100000) == ITEMSORT_EXPEND && ((m_pData->GetInt(ITEMDATA_TYPE)%100000)/10000)*10000 == ITEMTYPE_SPRITE; }
	bool	IsEudemon()				{ return ((m_pData->GetInt(ITEMDATA_TYPE)%10000000)/100000) == ITEMSORT_EXPEND && ((m_pData->GetInt(ITEMDATA_TYPE)%100000)/10000)*10000 == ITEMTYPE_EUDEMON; }
	bool	IsEudemonEgg()			{ return ((m_pData->GetInt(ITEMDATA_TYPE)%10000000)/100000) == ITEMSORT_EXPEND && ((m_pData->GetInt(ITEMDATA_TYPE)%100000)/10000)*10000 == ITEMTYPE_EUDEMON_EGG; }

	bool	LoadEudemonData(OBJID idOwner, IDatabase* pDb);
public:
	bool	CreateEudemonData(IRecord* pDefaultData, OBJID idOwner, const char* pszName, bool bInsert=true);

protected: // data & type
	CGameItemData*		m_pData;
	CItemTypeData*		m_pType;
//	CMonsterTypeData*	m_pEudemonType;		// ���������������� -- zlong 2004-02-05

	// ׷�����ԡ�������ΪNULL
	CItemAdditionData*		m_pAddition;
	CEudemonData*		m_pEudemonData;		// ��������
};

#endif // !defined(AFX_ITEMDATA_H__28794933_A926_4C9A_AACF_1A95340DA94B__INCLUDED_)
