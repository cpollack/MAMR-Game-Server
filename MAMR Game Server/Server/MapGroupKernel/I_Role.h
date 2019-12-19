// RoleManager.h: interface for the CRoleManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(I_ROLE_HEADER)
#define I_ROLE_HEADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "define.h"
#include "GameObjSet.h"
#include "TimeOut.h"

enum { POSE_STAND=0, };

const int	ADJUST_PERCENT			= 30000;						// ADJUSTʱ��>=30000 ��ʾ�ٷ���
const int	ADJUST_SET				= -30000;						// ADJUSTʱ��<=-30000 ��ʾ����(-1*num - 30000)
const int	ADJUST_FULL				= -32768;						// ADJUSTʱ��== -32768 ��ʾ����
const int	DEFAULT_DEFENCE2		= 10000;						// ���ݿ�ȱʡֵ

//���ɵȼ���Ҫ������������޶�
const int	SYNMEMSUM_LOWERLIMIT_TWO = 60;
const int	SYNMEMSUM_LOWERLIMIT_THREE = 150;
const int	SYNMEMSUM_LOWERLIMIT_FOUR = 380;	
//���ɼ���
const int SYNRANK_FOUR	= 4;
const int SYNRANK_THREE	= 3;
const int SYNRANK_TWO	= 2;
const int SYNRANK_ONE	= 1;

const DWORD TIME_FOOTPRINT	= 1000;

const int	TEAM_STATUS_REQ_ROLES	= 3;		// ���״̬��Ч��Ҫ�������������

const int	MAX_FRENZY_LIFE_PERCENT	= 70;		// ������������ٷֱȾͻ�ȡ����״̬


///////////////////////////////////////
// �޸�ħ��ϵͳ��Ҫ��
const int	ARROW_FLY_ALT					= 60;							// ��֧���и߶�


//---����---begin
//////////////////////////////////////////////////////////////////////
enum {
		RANK_LEADER			= 100,			//�����ų�		
		RANK_SUBLEADER		= 80,			//���ų�
		RANK_TEAMLEADER		= 60,			//�ӳ�
		RANK_NEWBIE			= 20,			//��ͨ��Ա
		RANK_RESERVED		= 10,			//Ԥ����Ա		
		RANK_NONE			= 0,

		RANK_SUB		= RANK_LEADER - RANK_SUBLEADER,
//		RANK_PRE		= -1,//RANK_SUBLEADER - RANK_PRESUBLEADER,
//		RANK_TEAM		= RANK_SUBLEADER - RANK_TEAMLEADER,
};

enum
{
	SYNMEM_LEVEL_ONE		= 1,
	SYNMEM_LEVEL_TWO		= 2,
	SYNMEM_LEVEL_THREE		= 3,
	SYNMEM_LEVEL_FOUR		= 4,
	SYNMEM_LEVEL_FIVE		= 5,		
};

//---����---end
//////////////////////////////////////////////////////////////////////
enum 
{
		DIE_NORMAL			= 1,
		DIE_CRITICALHIT		= 2,
		DIE_MAGIC			= 3,
		DIE_FLOAT			= 4,		// only for client
		DIE_ARROWSHOOT		= 5,
};

//////////////////////////////////////////////////////////////////////
enum { OWNER_NONE, OWNER_USER, OWNER_SYN, OWNER_NPC };

//////////////////////////////////////////////////////////////////////
// �ⲿ״̬����Ҫͨ��MsgPlayer֪ͨ������ҵ�״̬����ͻ���ͬ��
const I64		KEEPEFFECT_NORMAL			=0x00000000; 	// ������״̬

const I64		KEEPEFFECT_TEAMLEADER		=0x00000001;    // �ӳ�

const I64		KEEPEFFECT_DIE				=0x00000002;	// ����
const I64		KEEPEFFECT_GHOST			=0x00000004;    // ���״̬
const I64		KEEPEFFECT_DISAPPEARING		=0x00000008;    // ʬ����ʧ״̬


const I64		KEEPEFFECT_CRIME			=0x00000010;	// ���� // ����ɫ	
const I64		KEEPEFFECT_RED				=0x00000020;	// ����
const I64		KEEPEFFECT_DEEPRED			=0x00000040;	// ����
const I64		KEEPEFFECT_SYNCRIME			=0x00000080;	// ���ɷ���

const I64		KEEPEFFECT_POISON			=0x00000100;    // �ж�
const I64		KEEPEFFECT_HIDDEN			=0x00000200;    // ����
const I64		KEEPEFFECT_FREEZE			=0x00000400;    // ����
const I64		KEEPEFFECT_SUPERSOLDIER		=0x00000800;    // ��˫
const I64		KEEPEFFECT_LURKER			=0x00001000;    // Ǳ��

const I64		KEEPEFFECT_DEFENCE1			=0x00002000;    // �������1
const I64		KEEPEFFECT_DEFENCE2			=0x00004000;    // �������2
const I64		KEEPEFFECT_DEFENCE3			=0x00008000;    // �������3

const I64		KEEPEFFECT_ATTACK			=0x00010000;    // ��������
const I64		KEEPEFFECT_ATKSPEED			=0x00020000;    // �����ٶ����

const I64		KEEPEFFECT_MAGICDAMAGE		=0x00040000;    // ħ���˺����
const I64		KEEPEFFECT_MAGICDEFENCE 	=0x00080000;    // ħ���������

const I64		KEEPEFFECT_REFLECT			=0x00100000;	// ��������
const I64		KEEPEFFECT_REFLECTMAGIC		=0x00200000;    // ħ������

const I64		KEEPEFFECT_SLOWDOWN1		=0x00400000;    // ����״̬ 50%
const I64		KEEPEFFECT_SLOWDOWN2		=0x00800000;	// ����״̬ // Ѫ����һ��ʱ��ʼ���� // 50%

const I64		KEEPEFFECT_TEAM_HEALTH		=0x01000000;	// ҽ�ƽ��״̬
const I64		KEEPEFFECT_TEAM_ATTACK		=0x02000000;	// �������״̬
const I64		KEEPEFFECT_TEAM_DEFENCE		=0x04000000;	// ������״̬
const I64		KEEPEFFECT_TEAM_SPEED		=0x08000000;	// �ٶȽ��״̬
const I64		KEEPEFFECT_TEAM_EXP			=0x10000000;	// �������״̬
const I64		KEEPEFFECT_TEAM_SPIRIT		=0x20000000;	// ������״̬
const I64		KEEPEFFECT_TEAM_CLEAN		=0x40000000;	// �������״̬

const I64		KEEPEFFECT_SMOKE			=0x80000000;			// ����Ч��
const I64		KEEPEFFECT_DARKNESS			=0x0000000100000000;	// �ڰ�Ч��
const I64		KEEPEFFECT_PALSY			=0x0000000200000000;	// ���Ч��
const I64		KEEPEFFECT_MAXLIFE			=0x0000000400000000;	// �����������/����
const I64		KEEPEFFECT_MAXENERGY		=0x0000000800000000;	// �����������/����

const I64		KEEPEFFECT_ADD_EXP			=0x0000001000000000;	// ս����������
const I64		KEEPEFFECT_ATTRACT_MONSTER	=0x0000002000000000;	// ��������
const I64		KEEPEFFECT_XPFULL			=0x0000004000000000;	// XP��

const I64		KEEPEFFECT_ADJUST_DODGE			=0x0000008000000000;	// �����ܵĶ��ֵ
const I64		KEEPEFFECT_ADJUST_XP			=0x0000010000000000;	// ����ÿ������XPֵ
const I64		KEEPEFFECT_ADJUST_DROPMONEY		=0x0000020000000000;	// ���ڹ���ÿ�ε�Ǯ

const I64		KEEPEFFECT_PK_PROTECT			=0x0000040000000000;	// pk����״̬
const I64		KEEPEFFECT_PELT					=0x0000080000000000;	// ����״̬
const I64		KEEPEFFECT_ADJUST_EXP			=0x0000100000000000;	// ս����þ������

const I64		KEEPEFFECT_HEAL					=0x0000200000000000;	// ����״̬
const I64		KEEPEFFECT_FAINT				=0x0000400000000000;	// ��
const I64		KEEPEFFECT_TRUCULENCE			=0x0000800000000000;	// Ұ��
const I64		KEEPEFFECT_DAMAGE				=0x0001000000000000;	// �����ܵ����˺�
const I64		KEEPEFFECT_ATKER_DAMAGE			=0x0002000000000000;	// ������Ŀ����ɵ��˺�
const I64		KEEPEFFECT_CONFUSION			=0x0004000000000000;	// ����
const I64		KEEPEFFECT_FRENZY				=0x0008000000000000;	// ��
const I64		KEEPEFFECT_EXTRA_POWER			=0x0010000000000000;	// ����
const I64		KEEPEFFECT_TRANSFER_SHIELD		=0x0020000000000000;	// ����
const I64		KEEPEFFECT_SORB_REFLECT			=0x0040000000000000;	// ���շ���
const I64		KEEPEFFECT_FRENZY2				=0X0080000000000000;	// ��һ�ֿ�״̬

//////////////////////////////////////////////////////////////////////
// �ۺ�״̬
//enum {
const I64		KEEPEFFECT_NOT_ACTIVE		=KEEPEFFECT_DIE|KEEPEFFECT_FREEZE|KEEPEFFECT_PALSY;
const I64		KEEPEFFECT_NOT_CLEAR		=KEEPEFFECT_TEAMLEADER|KEEPEFFECT_RED|KEEPEFFECT_DEEPRED;		// ������������״̬
		// ���ϵͳ����״̬
const I64		KEEPEFFECT_TEAM_ALL			=KEEPEFFECT_TEAM_HEALTH|KEEPEFFECT_TEAM_ATTACK|KEEPEFFECT_TEAM_DEFENCE
											|KEEPEFFECT_TEAM_SPEED|KEEPEFFECT_TEAM_EXP|KEEPEFFECT_TEAM_SPIRIT|KEEPEFFECT_TEAM_CLEAN;
//};

//////////////////////////////////////////////////////////////////////
// �ڲ�״̬������Ҫͨ��MsgPlayer֪ͨ������ҵ�״̬���������ڲ�ʹ��(cq_magictypeʹ��)
enum {
		STATUS_NORMAL		=0,
		STATUS_DIE			=1,										// ����
		STATUS_CRIME		=2,										// ��������״̬
		STATUS_POISON		=3,										// �ж�
		STATUS_TEAMLEADER	=4,										// �ӳ�
		STATUS_PKVALUE		=5,										// PK״̬
		STATUS_DETACH_BADLY	=6,										// ������в���״̬
		STATUS_DETACH_ALL	=7,										// �������ħ��״̬
		STATUS_VAMPIRE		=8,										// ATKSTATUS����Ѫ
		STATUS_DISAPPEARING	=9,										// ʬ����ʧ״̬
		STATUS_MAGICDEFENCE	=10,									// ħ����������/�½�
		STATUS_SUPER_MDEF	=11,									// ����ħ��
		STATUS_ATTACK		=12,									// ��������/�½�
		STATUS_REFLECT		=13,									// ��������
		STATUS_HIDDEN		=14,									// ����
		STATUS_MAGICDAMAGE	=15,									// ħ���˺�����/�½�
		STATUS_ATKSPEED		=16,									// �����ٶ�����/�½�
		STATUS_LURKER		=17,									// user only			// Ǳ�У���״̬�²���NPC�������������Ч
		STATUS_SYNCRIME		=18,									// ���ɷ���
		STATUS_REFLECTMAGIC	=19,									// ħ������
		STATUS_SUPER_DEF	=20,									// ��������
		STATUS_SUPER_ATK	=21,									// self only	// ��������
		STATUS_SUPER_MATK	=22,		 							// self only	// ����ħ��
		STATUS_STOP			=23,
		STATUS_DEFENCE1		=24,									// �������/����1
		STATUS_DEFENCE2		=25,									// �������/����2
		STATUS_DEFENCE3		=26,									// �������/����3
		STATUS_FREEZE		=27,									// ����״̬
		STATUS_SMOKE		=28,									// ����Ч��
		STATUS_DARKNESS		=29,									// �ڰ�Ч��
		STATUS_PALSY		=30,									// ���Ч��

		STATUS_TEAM_BEGIN	=31,
		STATUS_TEAMHEALTH	=31,									// ҽ�ƽ��
		STATUS_TEAMATTACK	=32,									// �������
		STATUS_TEAMDEFENCE	=33,									// ������
		STATUS_TEAMSPEED	=34,									// �ٶȽ��
		STATUS_TEAMEXP		=35,									// �������
		STATUS_TEAMSPIRIT 	=36,									// ������
		STATUS_TEAMCLEAN	=37,									// �������
		STATUS_TEAM_END		=37,

		STATUS_SLOWDOWN1	=38,									// �ƶ��ٶ�����/�½�
		STATUS_SLOWDOWN2	=39,									// �����ٶȣ�������������һ���ʱ�򡣿ͻ��˱��֣�
		STATUS_MAXLIFE		=40,									// �����������/����
		STATUS_MAXENERGY	=41,									// �����������/����
		STATUS_DEF2ATK		=42,									// ����ת��Ϊ����(power=��ת���ķ����ٷֱ�)
		STATUS_ADD_EXP		=43,						// ս���������� -- ֻ�ܶԶӳ�ʹ�ã������������Ч��
		STATUS_DMG2LIFE		=44,									// ÿ�ι����˺�����ת��Ϊ�Լ�������(power=��ת���İٷֱ�)
		STATUS_ATTRACT_MONSTER	=45,								// ��������
		STATUS_XPFULL		=46,									// XP��
		//---jinggy---begin
		STATUS_ADJUST_DODGE	=47,			//�����ܵĶ��ֵ
		STATUS_ADJUST_XP	=48,			//����ÿ������XPֵ
		STATUS_ADJUST_DROPMONEY	=49,		//���ڹ���ÿ�ε�Ǯ
		//---jinggy---end
		STATUS_PK_PROTECT	=50,									// PK����״̬
		STATUS_PELT			=51,									// ����״̬
		STATUS_ADJUST_EXP	=52,									// ս����þ����������������κ���ʹ��

		/////////////////////////////////
		// ���޼�����Ҫ�õ���״̬
		STATUS_HEAL				=100,			// ����
		STATUS_FAINT			=101,			// ����
		STATUS_TRUCULENCE		=102,			// Ұ��
		STATUS_DAMAGE			=103,			// �����ܵ����˺�
		STATUS_ATKER_DAMAGE		=104,			// ������Ŀ����ɵ��˺�
		STATUS_CONFUSION		=105,			// ����
		STATUS_FRENZY			=106,			// ��
		STATUS_EXTRA_POWER		=107,			// ����
		STATUS_TRANSFER_SHIELD	=108,			// ����
		STATUS_SORB_REFLECT		=109,			// ���շ���
		STATUS_FRENZY2			=110,			// ����һ�ֿ�״̬

		/////////////////////////////////

		STATUS_LOCK			=251,									// ������״̬ -- only used in server

		STATUS_LIMIT		=256,						// ��ɫ״̬���ܳ������ֵ
};

//////////////////////////////////////////////////////////////////////
struct StatusInfoStruct;
class IStatus
{
public:
	virtual OBJID	GetID()							PURE_VIRTUAL_FUNCTION_0
	virtual ULONG	ReleaseByOwner()				PURE_VIRTUAL_FUNCTION_0

	virtual bool		IsValid()							PURE_VIRTUAL_FUNCTION_0
	virtual int			GetPower()							PURE_VIRTUAL_FUNCTION_0
	virtual bool		GetInfo(StatusInfoStruct* pInfo)	PURE_VIRTUAL_FUNCTION_0
	virtual void		OnTimer(DWORD tCurr)				PURE_VIRTUAL_FUNCTION
	virtual bool		ChangeData(int nPower, int nSecs, int nTimes=0)		PURE_VIRTUAL_FUNCTION_0
	virtual bool		IncTime(int nMilliSecs, int nLimit)		PURE_VIRTUAL_FUNCTION_0
	virtual bool		ToFlash()							PURE_VIRTUAL_FUNCTION_0
};

typedef	IGameObjSet<IStatus>		IStatusSet;
typedef	CGameObjSet<IStatus>		CStatusSet;

////////////////////////////////////////////////////////////////
enum {	MOVEMODE_WALK=0,					// PathMove()��ģʽ
		MOVEMODE_RUN,
		MOVEMODE_SHIFT,						// to server only
		MOVEMODE_JUMP,
		MOVEMODE_TRANS,
		MOVEMODE_CHGMAP,
		MOVEMODE_JUMPMAGICATTCK,
		MOVEMODE_COLLIDE,
		MOVEMODE_SYNCHRO,					// to server only
		MOVEMODE_TRACK,

		MOVEMODE_RUN_DIR0 = 20,

		MOVEMODE_RUN_DIR7 = 27,
};

////////////////////////////////////////////////////////////////
const int _DELTA_X[9]={ 0, -1, -1, -1, 0, 1, 1, 1, 0 };
const int _DELTA_Y[9]={ 1, 1, 0, -1, -1, -1, 0, 1, 0 };
const int MAX_DIRSIZE = 8;
inline int GetDirByPos(int nFromX, int nFromY, int nToX, int nToY)		// return MAX_DIRSIZE: error
{
	if(nFromX < nToX)
	{
		if(nFromY < nToY)
			return 7;
		else if(nFromY > nToY)
			return 5;
		else
			return 6;
	}
	else if(nFromX > nToX)
	{
		if(nFromY < nToY)
			return 1;
		else if(nFromY > nToY)
			return 3;
		else
			return 2;
	}
	else // if(nFromX == nToX)
	{
		if(nFromY < nToY)
			return 0;
		else if(nFromY > nToY)
			return 4;
	}
	return MAX_DIRSIZE;
}
inline int		MaskLook(int look)							{ return look/10; }
inline int		MaskDir(int look)							{ return look%10; }
inline DWORD	MakeLookFace(int nMaskLook, int nMaskDir)	{ return (nMaskLook*10) + (nMaskDir%10); }
inline float	GetRadian(float posSourX, float posSourY, float posTargetX, float posTargetY)
{
	CHECKF(posSourX != posTargetX || posSourY != posTargetY);

	float PI = static_cast<float>(3.1415926535);
	float fDeltaX = posTargetX - posSourX;
	float fDeltaY = posTargetY - posSourY;
	float fDistance	= sqrt(fDeltaX*fDeltaX + fDeltaY*fDeltaY);
	CHECKF(fDeltaX <= fDistance && fDistance > 0);
	float fRadian = asin(fDeltaX / fDistance);

	return fDeltaY > 0 ? (PI/2 - fRadian) : (PI + fRadian + PI/2);
}

//////////////////////////////////////////////////////////////////////
class IRole;
class IMapThing
{
public: // base
	virtual void	ReleaseByOwner()							PURE_VIRTUAL_FUNCTION
	virtual OBJID	GetID()										PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetObjType()								PURE_VIRTUAL_FUNCTION_0
	virtual int		GetPosX()									PURE_VIRTUAL_FUNCTION_0
	virtual int		GetPosY()									PURE_VIRTUAL_FUNCTION_0
	virtual void	SendShow(IRole* pRole)						PURE_VIRTUAL_FUNCTION

	// return true: ppv���ض���ָ��
	virtual bool	QueryObj(OBJID idObjType, void** ppv)				PURE_VIRTUAL_FUNCTION_0
	virtual bool	QueryRole(void** ppv)						PURE_VIRTUAL_FUNCTION_0
};

//////////////////////////////////////////////////////////////////////
class IMapThing;
class IStatus;
class CTransformation;
class CTeam;
class CItem;
class CMagic;
class IRole
{
protected:
	IRole(){}
	~IRole(){}
public:
	virtual void	ReleaseByOwner		()						PURE_VIRTUAL_FUNCTION
public: // get attrib
	virtual OBJID	GetID				()						PURE_VIRTUAL_FUNCTION_0
	virtual LPCTSTR	GetName				()						PURE_VIRTUAL_FUNCTION_0
//	virtual LPCTSTR	GetMate				()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetLookFace			()						PURE_VIRTUAL_FUNCTION_0
	//�Ժ�Ҫ�ֽ�����������ӿ�
	//virtual int	GetLook				()						PURE_VIRTUAL_FUNCTION_0
	//virtual int	GetFace				()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetHair				()						PURE_VIRTUAL_FUNCTION_0
	virtual char	GetLength			()						PURE_VIRTUAL_FUNCTION_0		// ȡ�ý�ɫ�߰� -- zlong 2004-02-03
	virtual char	GetFat				()						PURE_VIRTUAL_FUNCTION_0		// ȡ�ý�ɫ���� -- zlong 2004-02-03
	virtual int 	GetPosX				()						PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetPosY				()						PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetDir				()						PURE_VIRTUAL_FUNCTION_0
//	virtual	BOOL	CheckStatus			(int nStatus)			PURE_VIRTUAL_FUNCTION_0
	virtual I64		GetEffect			()						PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetPose				()						PURE_VIRTUAL_FUNCTION_0
//	virtual DWORD	GetMoney			()						PURE_VIRTUAL_FUNCTION_0
//	virtual DWORD	GetMoneySaved		()						PURE_VIRTUAL_FUNCTION_0
//	virtual int  	GetExp				()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetLev				()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetLife				()						PURE_VIRTUAL_FUNCTION_0
//	virtual DWORD	GetMana				()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMaxLife			()						PURE_VIRTUAL_FUNCTION_0
//	virtual DWORD	GetMaxMana			()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetMinAtk			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMaxAtk			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMgcMinAtk			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMgcMaxAtk			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetAttack			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetAtkHitRate		()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetDef				()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetDefence			()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetDegree			()						PURE_VIRTUAL_FUNCTION_0
	//virtual DWORD	GetDexterity		()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetDdg				()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetDodge			()						PURE_VIRTUAL_FUNCTION_0

//	virtual DWORD	GetMagicAtk			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMagicDef			()						PURE_VIRTUAL_FUNCTION_0

	virtual	DWORD	GetInterAtkRate		()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetIntervalAtkRate	()						PURE_VIRTUAL_FUNCTION_0

	virtual int		GetHelmetTypeID		()						PURE_VIRTUAL_FUNCTION_0
	virtual int		GetArmorTypeID		()						PURE_VIRTUAL_FUNCTION_0
	virtual int		GetWeaponRTypeID	()						PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetWeaponLTypeID	()						PURE_VIRTUAL_FUNCTION_0
//	virtual int		GetNecklaceTypeID	()						PURE_VIRTUAL_FUNCTION_0
//	virtual int 	GetRingRTypeID		()						PURE_VIRTUAL_FUNCTION_0
//	virtual int 	GetRingLTypeID		()						PURE_VIRTUAL_FUNCTION_0
//	virtual int 	GetShoesTypeID		()						PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetMountTypeID		()						PURE_VIRTUAL_FUNCTION_0
	virtual int		GetMantleTypeID		()						PURE_VIRTUAL_FUNCTION_0

//	virtual DWORD 	GetMedalSelect		()						PURE_VIRTUAL_FUNCTION_0
//	virtual DWORD	GetTitleSelect		()						PURE_VIRTUAL_FUNCTION_0

	virtual int		GetDistance			(int x, int y)			PURE_VIRTUAL_FUNCTION_0
	virtual int		GetDistance			(IMapThing* pTarget)	PURE_VIRTUAL_FUNCTION_0

	virtual CGameMap*	GetMap			()						PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetSynID			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetSynRank			()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetSynRankShow		()						PURE_VIRTUAL_FUNCTION_0

	virtual bool	IsSimpleMagicAtk	()						PURE_VIRTUAL_FUNCTION_0
	virtual int 	GetSimpleMagicHitRate()						PURE_VIRTUAL_FUNCTION_0

	virtual int		GetTutorExp			()						PURE_VIRTUAL_FUNCTION_0
	virtual UCHAR	GetTutorLevel		()						PURE_VIRTUAL_FUNCTION_0
	virtual UCHAR	GetMercenaryRank	()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMercenaryExp		()						PURE_VIRTUAL_FUNCTION_0
	virtual UCHAR	GetNobilityRank		()						PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetExploit			()						PURE_VIRTUAL_FUNCTION_0
public: // const

//	virtual int		GetSex				()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsAlive				()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsTalkEnable		()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsGM				()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsPM				()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsMonster			()						PURE_VIRTUAL_FUNCTION_0
//	virtual bool	IsScene				()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsDelThis			()						PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsVirtuous()								PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsEvil()									PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsBowman()									PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsShieldEquip()								PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsWing()									PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsSendBlockInfo		()						PURE_VIRTUAL_FUNCTION_0

	// return true: ppv���ض���ָ��
	virtual bool	QueryObj			(OBJID idObjType, void** ppv)	PURE_VIRTUAL_FUNCTION_0
	virtual IMapThing*	QueryMapThing	()						PURE_VIRTUAL_FUNCTION_0
	virtual IRole*	FindAroundRole		(OBJID id)				PURE_VIRTUAL_FUNCTION_0
	virtual CUser*	QueryOwnerUser		()						PURE_VIRTUAL_FUNCTION_0

public:	// modify attrib ------------------------------
	virtual void	SetDir				(int nDir)							PURE_VIRTUAL_FUNCTION
	virtual void	SetPose				(int nPose)							PURE_VIRTUAL_FUNCTION
//	virtual void	SetEmotion			(int nEmotion)						PURE_VIRTUAL_FUNCTION
	virtual	void	SetStatus			(int nStatus, bool bSynchro=true)						PURE_VIRTUAL_FUNCTION
	virtual	void	ClsStatus			(int nStatus, bool bSynchro=true)						PURE_VIRTUAL_FUNCTION
	virtual bool	AddAttrib			(int idxAttr, __int64 i64Data, int bSynchro)					PURE_VIRTUAL_FUNCTION_0
	virtual void	ProcessOnMove		(int nMoveMode)						PURE_VIRTUAL_FUNCTION
	virtual void	ProcessAfterMove	()									PURE_VIRTUAL_FUNCTION
	virtual void	GetFootPrint		(int& x, int& y)					PURE_VIRTUAL_FUNCTION

	virtual bool	SpendArrow			()									PURE_VIRTUAL_FUNCTION_0

	virtual	IStatus*	QueryStatus(OBJID idType)										PURE_VIRTUAL_FUNCTION_0
	virtual	IStatusSet*	QueryStatusSet()												PURE_VIRTUAL_FUNCTION_0
	virtual void	AwardBattleExp		(int nExp, bool bGemEffect=true)				PURE_VIRTUAL_FUNCTION
	virtual int 	AdjustHitRate		(int nHitRate)									PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustAttack		(int nAtk)										PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustDefence		(int nDef)										PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustMagicAtk		(int nAtk)										PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustMagicDef		(int nDef)										PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustBowDefence	(int nDef)										PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustWeaponDamage	(int nDamage)									PURE_VIRTUAL_FUNCTION_0
	virtual int 	AdjustMagicDamage	(int nDamage)									PURE_VIRTUAL_FUNCTION_0
	virtual void	SetFightPause		(int nInterval)									PURE_VIRTUAL_FUNCTION
	virtual void	SaveInfo			()												PURE_VIRTUAL_FUNCTION

public: // money --------------------------------
//	virtual bool	SpendMoney			(DWORD nMoney, bool bSynchro)			PURE_VIRTUAL_FUNCTION_0
//	virtual bool	GainMoney			(DWORD nMoney, bool bSynchro)			PURE_VIRTUAL_FUNCTION_0

public: // interactive
//	virtual bool	AddItem				(CItem* pItem)								PURE_VIRTUAL_FUNCTION_0
//	virtual bool	IsItemFull			()											PURE_VIRTUAL_FUNCTION_0

public: // system
	virtual void	BroadcastRoomMsg(CNetMsg* pMsg, bool bSendSelf = false)	PURE_VIRTUAL_FUNCTION
	virtual void	BroadcastRoomMsg(LPCTSTR szMsg, bool bSendSelf = false)	PURE_VIRTUAL_FUNCTION
//	virtual void	BroadcastMapMsg(CNetMsg* pMsg, bool bSendSelf = false)	PURE_VIRTUAL_FUNCTION
//	virtual void	BroadcastMapMsg(LPCTSTR szMsg, bool bSendSelf = false)	PURE_VIRTUAL_FUNCTION
	virtual bool	SendMsg(CNetMsg* pMsg)									PURE_VIRTUAL_FUNCTION_0
	virtual bool	SendSysMsg(const char* fmt, ...)						PURE_VIRTUAL_FUNCTION_0
	virtual void	OnTimer(time_t tCurr)									PURE_VIRTUAL_FUNCTION

public: // map
	virtual bool	MoveToward(int nDir, bool bSync = true)					PURE_VIRTUAL_FUNCTION_0
	virtual void	TransPos(int nPosX, int nPosY)							PURE_VIRTUAL_FUNCTION
	virtual void	JumpPos(int nPosX, int nPosY)							PURE_VIRTUAL_FUNCTION
	virtual bool	SyncTrackTo(int nPosX, int nPosY, int nDir, DWORD dwAction)				PURE_VIRTUAL_FUNCTION_0
	virtual void	ActiveTransPos(int nPosX, int nPosY)					PURE_VIRTUAL_FUNCTION
	virtual bool	SendSelfToBlock()										PURE_VIRTUAL_FUNCTION_0

	virtual void	AddToBCRoleSet			(OBJID idRole, bool bSendMsg)	PURE_VIRTUAL_FUNCTION
	virtual void	RemoveFromBCRoleSet		(OBJID idRole)					PURE_VIRTUAL_FUNCTION
	virtual void	AddToBCMapItemSet		(OBJID idMapItem)				PURE_VIRTUAL_FUNCTION
	virtual void	RemoveFromBCMapItemSet	(OBJID idMapItem)				PURE_VIRTUAL_FUNCTION
	
public: // fight ------------------------------
	virtual void	ClrAttackTarget		()									PURE_VIRTUAL_FUNCTION
	virtual bool	SetAttackTarget(IRole* pTarget = NULL)					PURE_VIRTUAL_FUNCTION_0
	virtual bool	AutoSkillAttack(IRole* pTarget)							PURE_VIRTUAL_FUNCTION_0
	virtual bool	AdditionMagic(int nLifeLost, int nDamage)				PURE_VIRTUAL_FUNCTION_0
	virtual int		Attack(IRole* pTarget)									PURE_VIRTUAL_FUNCTION_0
	virtual bool	BeAttack(bool bMagic, IRole* pTarget, int nPower, bool bReflectEnable=true)					PURE_VIRTUAL_FUNCTION_0
	virtual bool	MagicAttack(int nType, OBJID idTarget, int x, int y)	PURE_VIRTUAL_FUNCTION_0
	virtual void	Kill(IRole* pTarget, DWORD dwDieWay)									PURE_VIRTUAL_FUNCTION
	virtual void	BeKill(IRole* pTarget = NULL)							PURE_VIRTUAL_FUNCTION
	virtual bool	IsAtkable(IRole* pTarget, bool bSendHint=false)			PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsBeAtkable()											PURE_VIRTUAL_FUNCTION_0
	virtual int		GetAttackRange(int nTargetSizeAdd)						PURE_VIRTUAL_FUNCTION_0
	virtual int		GetSizeAdd()											PURE_VIRTUAL_FUNCTION_0
	virtual	int		GetLuck				()									PURE_VIRTUAL_FUNCTION_0
	virtual void	SendDamageMsg(OBJID idTarget, int nDamage)				PURE_VIRTUAL_FUNCTION

	virtual bool	TransferShield(bool bMagic, IRole* pAtker, int nDamage)	PURE_VIRTUAL_FUNCTION_0
	
public:	// Ϊ���޸�ħ��ϵͳ�����ӵĲ��֣���ħ��ϵͳ�޸�����������
	virtual void	AwardSynWarScore(CNpc* pNpc, int nScore)				PURE_VIRTUAL_FUNCTION
	virtual bool	IsImmunity(IRole* pRole)								PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetProfession()											PURE_VIRTUAL_FUNCTION_0
	virtual int		GetGemExpEffect()										PURE_VIRTUAL_FUNCTION_0
	virtual int		GetGemMgcExpEffect()									PURE_VIRTUAL_FUNCTION_0
	virtual bool	SpendEquipItem(int nSubType, int nNum, bool bSynchro)	PURE_VIRTUAL_FUNCTION_0
	virtual int		AdjustExp(IRole* pTarget, int nRawExp, bool bNewbieBonusMsg=false)		PURE_VIRTUAL_FUNCTION_0
	virtual bool	DecEquipmentDurability(bool bBeAttack, bool bMagic, int bDurValue=1)	PURE_VIRTUAL_FUNCTION_0
	virtual void	SendGemEffect()											PURE_VIRTUAL_FUNCTION
	virtual bool	IsEmbedGemType(int nGemType)							PURE_VIRTUAL_FUNCTION_0

	virtual DWORD	GetMana()												PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetMaxMana()											PURE_VIRTUAL_FUNCTION_0

	virtual int		GetEnergy()												PURE_VIRTUAL_FUNCTION_0
	virtual bool	CheckWeaponSubType(int nSubType, int nNum = 0)			PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetPotential()											PURE_VIRTUAL_FUNCTION_0
	virtual CTransformation* QueryTransformation()							PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsArrowPass(int x, int y, int nAlt=ARROW_FLY_ALT)		PURE_VIRTUAL_FUNCTION_0
	virtual CTeam*	GetTeam()												PURE_VIRTUAL_FUNCTION_0
	virtual CItem*	GetEquipItemByPos(int nPosition)						PURE_VIRTUAL_FUNCTION_0
	virtual bool	CheckCrime(IRole* pRole)								PURE_VIRTUAL_FUNCTION_0
	virtual void	SetDelay(int nDelay)									PURE_VIRTUAL_FUNCTION

	virtual CItem*	GetWeaponR			()									PURE_VIRTUAL_FUNCTION_0
	virtual CItem*	GetWeaponL			()									PURE_VIRTUAL_FUNCTION_0

	virtual bool	DropItem(OBJID idItem, int x, int y)					PURE_VIRTUAL_FUNCTION_0
	virtual DWORD	GetSoulSum()											PURE_VIRTUAL_FUNCTION_0
	virtual void	AddEquipmentDurability(int nPosition, int nAddValue)	PURE_VIRTUAL_FUNCTION
	virtual bool	SynPosition(int nPosX, int nPosY, int nMaxDislocation = 8)						PURE_VIRTUAL_FUNCTION_0
	virtual bool	Transform(DWORD dwType, int nKeepSecs, bool bSynchro = true)					PURE_VIRTUAL_FUNCTION_0
	virtual bool	IsInFan(POINT pos, POINT posSource, int nRange, int nWidth, POINT posCenter)	PURE_VIRTUAL_FUNCTION_0
	virtual bool	AddItem (CItem* pItem, bool bSynchro, bool bUpdate = true)						PURE_VIRTUAL_FUNCTION_0
	virtual bool	Synchro()												PURE_VIRTUAL_FUNCTION_0
	virtual int		AdjustData(int nData, int nAdjust, int nMaxData=0)		PURE_VIRTUAL_FUNCTION_0
	virtual CItem*	FindSpaceTransSpell()									PURE_VIRTUAL_FUNCTION_0

	virtual	CMagic*	QueryMagic()											PURE_VIRTUAL_FUNCTION_0
};




#endif // !defined(I_ROLE_HEADER)
