// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERTABLE_H__BF5C20F1_5DBE_4E65_9099_E96EFAD7ECBA__INCLUDED_1)
#define AFX_USERTABLE_H__BF5C20F1_5DBE_4E65_9099_E96EFAD7ECBA__INCLUDED_1

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MagicType.h"

////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
enum TASKDATA{
		TASKDATA_ID_		=0,
		TASKDATA_IDNEXT		=1,
		TASKDATA_IDNEXTFAIL,
		TASKDATA_ITEMNAME1,
		TASKDATA_ITEMNAME2,
		TASKDATA_MONEY,
		TASKDATA_PROFESSION,
		TASKDATA_SEX,
		TASKDATA_MINPK,
		TASKDATA_MAXPK,
		TASKDATA_TEAM,
		TASKDATA_METEMPSYCHOSIS,
		TASKDATA_QUERY,
		TASKDATA_MARRIAGE,
		TASKDATA_CLIENTACT,
};
char	szTaskTable[];
typedef	CConstGameData<TASKDATA,szTaskTable,TASKDATA_ID_>		CTaskData;
typedef	ISingleObjSet2<CTaskData>	ITaskSet;
typedef	CSingleObjSet2<CTaskData>	CTaskSet;

//////////////////////////////////////////////////////////////////////
enum ACTIONDATA{
		ACTIONDATA_ID_			=0,
		ACTIONDATA_IDNEXT		=1,
		ACTIONDATA_IDNEXTFAIL,
		ACTIONDATA_TYPE,
		ACTIONDATA_DATA,
		ACTIONDATA_PARAM,
};
char	szActionTable[];
typedef	CConstGameData<ACTIONDATA,szActionTable,ACTIONDATA_ID_>	CActionData;
typedef	ISingleMap2<CActionData>	IActionSet;
typedef	CSingleMap2<CActionData>	CActionSet;

//////////////////////////////////////////////////////////////////////
enum ADDPOINTDATA{
		ADDPOINTDATA_PROF		=1,
		ADDPOINTDATA_LEVEL,
		ADDPOINTDATA_FORCE,
		ADDPOINTDATA_DEX,
		ADDPOINTDATA_HEALTH,
		ADDPOINTDATA_SOUL,
};
char	szAddPointTable[];
typedef	CGameData<ADDPOINTDATA,szAddPointTable, szID>	CAddPointData;
typedef	ISingleObjSet2<CAddPointData>	IAddPointSet;
typedef	CSingleObjSet2<CAddPointData>	CAddPointSet;

//////////////////////////////////////////////////////////////////////
/*
enum MAGICTYPEDATA{
		MAGICTYPEDATA_TYPE=1,
		MAGICTYPEDATA_SORT,
		MAGICTYPEDATA_NAME,
		MAGICTYPEDATA_CRIME,
		MAGICTYPEDATA_GROUND,
		MAGICTYPEDATA_MULTI,
		MAGICTYPEDATA_TARGET,
		MAGICTYPEDATA_LEVEL,
		MAGICTYPEDATA_USE_MP,
		MAGICTYPEDATA_POWER,
		MAGICTYPEDATA_INTONE,
		MAGICTYPEDATA_PERCENT,
		MAGICTYPEDATA_STEP,
		MAGICTYPEDATA_RANGE,
		MAGICTYPEDATA_DISTANCE,
		MAGICTYPEDATA_STATUS,
		MAGICTYPEDATA_NEED_PROFMASK,
		MAGICTYPEDATA_NEED_EXP,
		MAGICTYPEDATA_NEED_LEVEL,
		MAGICTYPEDATA_USE_XP,				// == TYPE_XPSKILL: use xp
		MAGICTYPEDATA_WEAPON_SUBTYPE,
		MAGICTYPEDATA_TIMES,				// =0 : once status
		MAGICTYPEDATA_AUTO_ACTIVE,			// 0x01: active when kill target
		MAGICTYPEDATA_FLOOR_ATTR,			// 0: need not match.
		MAGICTYPEDATA_AUTO_LEARN,			// bool
		MAGICTYPEDATA_LEARN_LEVEL,			// auto learn need level, nn: equ level, nnmm: between mm - nn level.
		MAGICTYPEDATA_DROPWEAPON,			// 1: throw weapon_r to target
		MAGICTYPEDATA_USE_EP,				// use energy
		MAGICTYPEDATA_WEAPON_HIT,			// 1: hit by weapon
		MAGICTYPEDATA_USE_ITEM,				// use equip item
		MAGICTYPEDATA_NEXT_MAGIC,			// launch this magic when filished current magic, use same target and pos
		MAGICTYPEDATA_DELAY,				// milli-secs
		MAGICTYPEDATA_ITEM_NUM,				// use equip item number
		MAGICTYPEDATA_WIDTH,
		MAGICTYPEDATA_DURABILITY,
		MAGICTYPEDATA_APPLY_MS,
		MAGICTYPEDATA_OFFSET_X,
		MAGICTYPEDATA_OFFSET_Y,
		MAGICTYPEDATA_TRACK_ID,
};
char	szMagicTypeTable[];

typedef	CGameData<MAGICTYPEDATA, szMagicTypeTable, szID>	CMagicTypeData;
typedef	ISingleObjSet2<CMagicTypeData>		IMagicTypeSet;
typedef	CSingleObjSet2<CMagicTypeData>		CMagicTypeSet;
*/

//////////////////////////////////////////////////////////////////////

enum MAGICTRACKDATA{
	MAGICTRACKDATA_ID_	=0,				// ħ���켣ID
	MAGICTRACKDATA_ID_NEXT,				// ��һ���켣ID
	MAGICTRACKDATA_DIR,					// �ƶ�����
	MAGICTRACKDATA_STEP,				// �ƶ�����
	MAGICTRACKDATA_ALT,					// ��ͨ���߶�
	MAGICTRACKDATA_ACTION,				// �������
	MAGICTRACKDATA_POWER,				// �������������power
	MAGICTRACKDATA_APPLY_MS,			// �������������ʱ��
};

char	szTrackTable[];
typedef CGameData<MAGICTRACKDATA, szTrackTable, szID>		CMagicTrackData;
typedef ISingleMap2<CMagicTrackData>	IMagicTrackSet;
typedef CSingleMap2<CMagicTrackData>	CMagicTrackSet;


//////////////////////////////////////////////////////////////////////
enum TRAPTYPEDATA
{
	TRAPTYPEDATA_SORT=1,
	TRAPTYPEDATA_LOOK,
	TRAPTYPEDATA_ACTION,
	TRAPTYPEDATA_LEVEL,
	TRAPTYPEDATA_ATK_MAX,
	TRAPTYPEDATA_ATK_MIN,
	TRAPTYPEDATA_DEX,
	TRAPTYPEDATA_SPEED,
	TRAPTYPEDATA_TIMES,
	TRAPTYPEDATA_MAGICTYPE,
	TRAPTYPEDATA_MAGICHITRATE,
	TRAPTYPEDATA_SIZE,
	TRAPTYPEDATA_ATKMODE,
};
char	szTrapTypeTable[];
typedef	CGameData<TRAPTYPEDATA, szTrapTypeTable, szID>	CTrapTypeData;
typedef	ISingleObjSet2<CTrapTypeData>		ITrapTypeSet;
typedef	CSingleObjSet2<CTrapTypeData>		CTrapTypeSet;

//////////////////////////////////////////////////////////////////////
enum NPCTYPEDATA
{
		NPCTYPEDATA_NAME = 1,
		NPCTYPEDATA_TYPE,
		NPCTYPEDATA_LOOKFACE,
		NPCTYPEDATA_LENGTH,
		NPCTYPEDATA_FAT,

		NPCTYPEDATA_LIFE,
		NPCTYPEDATA_MANA,
		NPCTYPEDATA_ATTACKMAX,
		NPCTYPEDATA_ATTACKMIN,
		NPCTYPEDATA_DEFENCE,
		NPCTYPEDATA_DEXTERITY,
		NPCTYPEDATA_DODGE,

		NPCTYPEDATA_HELMET_TYPE,
		NPCTYPEDATA_ARMOR_TYPE,
		NPCTYPEDATA_WEAPONR_TYPE,
		NPCTYPEDATA_WEAPONL_TYPE,

		NPCTYPEDATA_ATKRANGE,
		NPCTYPEDATA_VIEWRANGE,
		NPCTYPEDATA_ESCAPELIFE,
		NPCTYPEDATA_ATKSPEED,				// ����
		NPCTYPEDATA_MOVESPEED,				// ����

		NPCTYPEDATA_LEVEL,
		NPCTYPEDATA_ATKUSER,

//		NPCTYPEDATA_DROPMONEY,
//		NPCTYPEDATA_DROPITEMTYPE,
		//���������Ϊ��
		NPCTYPEDATA_DROPMONEY_MIN,			//����Ǯ������ֵ
		NPCTYPEDATA_DROPMONEY_MAX,			//����Ǯ������ֵ

		NPCTYPEDATA_SIZEADD,				// 1: ����һ��CELL�Ĺ�������
		NPCTYPEDATA_ACTION,					// action for kill award

		NPCTYPEDATA_RUNSPEED,				// ����

		NPCTYPEDATA_DROP_ARMET,				// 
		NPCTYPEDATA_DROP_NECKLACE,			// 
		NPCTYPEDATA_DROP_ARMOR,				// 
		NPCTYPEDATA_DROP_RING,				// 
		NPCTYPEDATA_DROP_WEAPON,			// 
		NPCTYPEDATA_DROP_SHIELD,			// 
		NPCTYPEDATA_DROP_SHOES,				// 

//		NPCTYPEDATA_DROP_HP,				// 
//		NPCTYPEDATA_DROP_MP,				// 
		//���������Ϊ��
		NPCTYPEDATA_DROP_MONEY_CHANCE,		//��Ǯ�ļ���
		NPCTYPEDATA_DROP_ITEM_CHANCE,		//����Ʒ�ļ���

		NPCTYPEDATA_MAGIC_TYPE,	
		NPCTYPEDATA_MAGIC_DEF,
		NPCTYPEDATA_MAGIC_HITRATE,
		NPCTYPEDATA_ATK_HITRATE,

		NPCTYPEDATA_AITYPE,					// for client
		NPCTYPEDATA_DEFENCE2,				// defalut 1

		//���������ӵ�
		NPCTYPEDATA_EXPLODE_ITEM_CHANCE1,	//С���ļ���
		NPCTYPEDATA_EXPLODE_ITEM_CHANCE2,	//�б��ļ���
		NPCTYPEDATA_EXPLODE_ITEM_CHANCE3,	//�󱬵ļ���
		NPCTYPEDATA_DROP_ITEM_RULE,			//����Ʒ�Ĺ�����ID

		NPCTYPEDATA_PROFESSION,				// ְҵ���
};
char	szNpcTypeTable[];
typedef	CGameData<NPCTYPEDATA, szNpcTypeTable, szID>	CNpcTypeData;
typedef	ISingleMap2<CNpcTypeData>		INpcTypeSet;
typedef	CSingleMap2<CNpcTypeData>		CNpcTypeSet;
#define	CNpcType	CNpcTypeData

enum MONSTERDATA {
	MONSTERDATA_ID = 0,
	MONSTERDATA_NAME,
	MONSTERDATA_BASE_ATTACK,
	MONSTERDATA_BASE_DEFENCE,
	MONSTERDATA_BASE_DEXTERITY,
	MONSTERDATA_BASE_LIFE,
	MONSTERDATA_GROWPOINT,
	MONSTERDATA_LIFERISE,
	MONSTERDATA_RATE_ATTACK,
	MONSTERDATA_RATE_DEFENCE,
	MONSTERDATA_RATE_DEXTERITY,
	MONSTERDATA_LOOK,
	MONSTERDATA_CLASS,
	MONSTERDATA_INDEXNUM,
	MONSTERDATA_HUE0,
	MONSTERDATA_SAT0,
	MONSTERDATA_BRIGHT0, //x3
};
char	szMonsterTypeTable[];
typedef	CGameData<MONSTERDATA, szMonsterTypeTable, szID>	CMonsterTypeData;
typedef	ISingleMap2<CMonsterTypeData>		IMonsterTypeSet;
typedef	CSingleMap2<CMonsterTypeData>		CMonsterTypeSet;
#define	CMonsterType	CMonsterTypeData

//////////////////////////////////////////////////////////////////////
enum REBIRTHDATA
{
	REBIRTHDATA_NEED_PROF=1,
	REBIRTHDATA_NEW_PROF,
	REBIRTHDATA_NEED_LEVEL,
	REBIRTHDATA_NEW_LEVEL,
};
char	szRebirthTable[];
typedef	CGameData<REBIRTHDATA, szRebirthTable, szID>	CRebirthData;
typedef	ISingleObjSet2<CRebirthData>		IRebirthSet;
typedef	CSingleObjSet2<CRebirthData>		CRebirthSet;



#endif // !defined(AFX_USERTABLE_H__BF5C20F1_5DBE_4E65_9099_E96EFAD7ECBA__INCLUDED_1)
