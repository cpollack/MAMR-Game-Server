// Magic.h: interface for the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGIC_H__B2689767_419D_487F_B0F9_FBB04C4619AA__INCLUDED_)
#define AFX_MAGIC_H__B2689767_419D_487F_B0F9_FBB04C4619AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "GameObj.h"
#include "GameData.h"
#include "UserTable.h"
#include "MagicType.h"
#include "T_SingleObjSet2.h"
#include "Myheap.h"
#include "MagicData.h"

#pragma warning(disable:4786)
#include <vector>



char	szMagicTable[];

//////////////////////////////////////////////////////////////////////
enum {
		MAGICSORT_ATTACK			= 1,
		MAGICSORT_RECRUIT			= 2,			// support auto active.
		MAGICSORT_CROSS				= 3,
		MAGICSORT_FAN				= 4,			// support auto active(random).
		MAGICSORT_BOMB				= 5,
		MAGICSORT_ATTACHSTATUS		= 6,
		MAGICSORT_DETACHSTATUS		= 7,
		MAGICSORT_SQUARE			= 8,
		MAGICSORT_JUMPATTACK		= 9,			// move, a-lock
		MAGICSORT_RANDOMTRANS		= 10,			// move, a-lock
		MAGICSORT_DISPATCHXP		= 11,
		MAGICSORT_COLLIDE			= 12,			// move, a-lock & b-synchro
		MAGICSORT_SERIALCUT			= 13,			// auto active only.
		MAGICSORT_LINE				= 14,			// support auto active(random).
		MAGICSORT_ATKRANGE			= 15,			// auto active only, forever active.
		MAGICSORT_ATKSTATUS			= 16,			// support auto active, random active.
		MAGICSORT_CALLTEAMMEMBER	= 17,
		MAGICSORT_RECORDTRANSSPELL	= 18,
		MAGICSORT_TRANSFORM			= 19,
		MAGICSORT_ADDMANA			= 20,			// support self target only.
		MAGICSORT_LAYTRAP			= 21,
		MAGICSORT_DANCE				= 22,			// ����(only use for client)
		MAGICSORT_CALLPET			= 23,			// �ٻ���
		MAGICSORT_VAMPIRE			= 24,			// ��Ѫ��power is percent award. use for call pet
		MAGICSORT_INSTEAD			= 25,			// ����. use for call pet
		MAGICSORT_DECLIFE			= 26,			// ��Ѫ(��ǰѪ�ı���)
		MAGICSORT_GROUNDSTING		= 27,			// �ش�
		MAGICSORT_REBORN			= 28,			// ���� -- zlong 2004.5.14
		MAGICSORT_TEAM_MAGIC		= 29,			// ���ħ������ ��MAGICSORT_ATTACHSTATUS��ͬ����
													//				�����������ֻ��Ϊ�˷���ͻ���ʶ��
		MAGICSORT_BOMB_LOCKALL		= 30,			// ��MAGICSORT_BOMB������ͬ��ֻ������ȫ��Ŀ��
		MAGICSORT_SORB_SOUL			= 31,			// ����ħ��
		MAGICSORT_STEAL				= 32,			// ͵���������Ŀ������͵ȡpower����Ʒ
		MAGICSORT_LINE_PENETRABLE	= 33,			// �����߹켣���Դ��˵����Թ���

		//////////////////////////////////////////////
		// ��������ħ������
		MAGICSORT_BLAST_THUNDER			= 34,			// ħ��
		MAGICSORT_MULTI_ATTACHSTATUS	= 35,			// Ⱥ��ʩ��״̬
		MAGICSORT_MULTI_DETACHSTATUS	= 36,			// Ⱥ����״̬
		MAGICSORT_MULTI_CURE			= 37,			// Ⱥ�岹Ѫ
		MAGICSORT_STEAL_MONEY			= 38,			// ͵Ǯ
		MAGICSORT_KO					= 39,			// ��ɱ����Ŀ��ѪС��15%�Զ�����
		MAGICSORT_ESCAPE				= 40,			// ����/����
//		MAGICSORT_FLASH_ATTACK			= 41,			// ���λ�λ		
};

//////////////////////////////////////////////////////////////////////
const int	WEAPONMAGIC_OFFSET				= 10000;	// �����ϴ���ħ�������IDֵ��ͬʱ��ITEMTYPE��MAGICx�ֶμӴ�ƫ�Ƶ���MAGICTYPE��ID
const int	WEAPONMAGIC_MIN					= WEAPONMAGIC_OFFSET;
const int	WEAPONMAGIC_MAX					= WEAPONMAGIC_OFFSET+256;
const int	WEAPONMAGIC_LEVEL	= 0;					// ȱʡ������ħ���ȼ�
const int	WEAPONR_MAGICID		= 4200000001;			// ����������ħ��ID
const int	WEAPONL_MAGICID		= 4200000002;			// ����������ħ��ID

//////////////////////////////////////////////////////////////////////
const int	MAGICDAMAGE_ALT					= 26;		// ����Ч���ĸ߲�����
const int	AUTOLEVELUP_EXP					= -1;		// �Զ������ı�־
const int	DISABLELEVELUP_EXP				= 0;		// �������ı�־
const int	AUTOMAGICLEVEL_PER_USERLEVEL	= 10;		// ÿ10���������ȼ���һ��
const int	USERLEVELS_PER_MAGICLEVEL		= 10;		// ��ҵȼ������Ƿ����ȼ���10��

const int	KILLBONUS_PERCENT				= 5;		// ɱ������Ķ���EXP����
const int	HAVETUTORBONUS_PERCENT			= 10;		// �е�ʦ������¶���EXP����
const int	WITHTUTORBONUS_PERCENT			= 20;		// �͵�ʦһ�����������EXP����

const int	MAGIC_DELAY						= 1000;		// ħ��DELAY
const int	MAGIC_DECDELAY_PER_LEVEL		= 100;		// ÿ���������ȼ������ٵ�ħ��DELAY
const int	RANDOMTRANS_TRY_TIMES			= 10;		// ���˲�Ƶĳ��Դ���
const int	DISPATCHXP_NUMBER				= 20;		// ��XP������
const int	COLLIDE_POWER_PERCENT			= 80;		// ��ײ���ӹ������İٷֱ�
const int	COLLIDE_SHIELD_DURABILITY		= 3;		// ��ײҪ���ٵĶ�������
const int	LINE_WEAPON_DURABILITY			= 2;		// ֱ�߹���Ҫ���ٵ���������
const int	MAX_SERIALCUTSIZE				= 10;		// ˳��ն������
const int	AWARDEXP_BY_TIMES				= 1;		// �������Ӿ���ֵ
const int	AUTO_MAGIC_DELAY_PERCENT		= 150;		// ����ħ������ʱ���ӵ�DELAY
const int	BOW_SUBTYPE						= 500;		// ����SUBTYPE
const int	POISON_MAGIC_TYPE				= 1501;		// use for more status
const int	DEFAULT_MAGIC_FAN				= 120;		// 
//const int	STUDENTBONUS_PERCENT			= 5;		// ��ʦɱ��һֻ����ͽ�ܵõ��ľ���ٷֱ�

const int	MAGIC_KO_LIFE_PERCENT			= 15;		// ��ɱ����ȥѪ����
const int	MAGIC_ESCAPE_LIFE_PERCENT		= 15;		// ���ܼ�����Ч����������

//////////////////////////////////////////////////////////////////////
typedef	CGameData<MAGICDATA, szMagicTable, szID>	CMagicDataBase;
class	CMagicData : public IMagicData
{
protected:
	CMagicData()			{ m_pData = NULL; }
	virtual ~CMagicData();
public: // overload
	static IMagicData* CreateNew()		{ return new CMagicData; }
	virtual void	ReleaseByOwner()	{ delete this; }
	virtual bool	Create(IRecordset* pRecordset);
	virtual bool	Create(IRecordset* pDefaultRecord, OBJID idNewKey);
	virtual bool	Create(ST_MAGIC_DATA* pMagicData);
	virtual int		GetInt(MAGICDATA nDataName);
	virtual void	SetInt(MAGICDATA idx, int nData);
	virtual bool	FindType();		//? ��������Ҫ���ô˺����ֹ�ͬ��

	virtual OBJID	GetID()				{ CHECKF(m_pData); return m_pData->GetID(); }
	virtual bool	Update()			{ CHECKF(m_pData); return m_pData->Update(); }
	virtual void	ClearUpdateFlags()	{ CHECK(m_pData); m_pData->ClearUpdateFlags(); }
	virtual OBJID	InsertRecord()		{ CHECKF(m_pData); return m_pData->InsertRecord(); }
	virtual bool	DeleteRecord()		{ CHECKF(m_pData); return m_pData->DeleteRecord(); }
		
protected:
	CMagicDataBase*	m_pData;

protected: // ctrl
	MYHEAP_DECLARATION(s_heap)
};

//////////////////////////////////////////////////////////////////////
typedef	ISingleObjSet2<IMagicData>		IMagicSet;
typedef	CSingleObjSet2<IMagicData>		CMagicSet;

//////////////////////////////////////////////////////////////////////
struct MagicInfoStruct
{
	OBJID	id;
	OBJID	idOwner;
	int		nType;
	int		nLevel;
	DWORD	dwExp;
};

////////////////////////////////////////////////////////////////
enum
{
	TYPE_MAGIC		= 0, // ħ��
	TYPE_XPSKILL	= 1, // xp��
	TYPE_KONGFU		= 2, // �书��ʽ
};

//////////////////////////////////////////////////////////////////////
enum
{
	MAGICSTATE_NONE		= 0,		// ��״̬
	MAGICSTATE_INTONE	= 1,		// ����״̬
	MAGICSTATE_LAUNCH	= 2,		// ʩչ״̬
	MAGICSTATE_DELAY	= 3,		// �ӳ�״̬
};

//////////////////////////////////////////////////////////////////////
enum AUTO_ACTIVE{
	AUTOACTIVE_KILL			= 0x01,
	AUTOACTIVE_FOREVER		= 0x02,
	AUTOACTIVE_RANDOM		= 0x04,
	AUTOACTIVE_HIDDEN		= 0x08,		// �����������ħ������ʾ�ڿͻ���
	AUTOACTIVE_EXPDISABLE	= 0x10,		// �����������ħ��ʹ�ù����в��ܵõ�����
};

//////////////////////////////////////////////////////////////////////
enum THROW_WEAPON{
	THROW_WERPONR_TARGET			= 1,
};

//////////////////////////////////////////////////////////////////////
inline bool		IsWeaponMagic(int nType)			{ return nType >= WEAPONMAGIC_MIN && nType < WEAPONMAGIC_MAX; }
inline int		MagicType(int idx)					{ int nType = idx + WEAPONMAGIC_OFFSET; CHECKF(IsWeaponMagic(nType)); return nType; }
inline OBJID	POSITION2MAGIC_ID(int nPosition)	{ if(nPosition == ITEMPOSITION_WEAPON) return WEAPONR_MAGICID; else return WEAPONL_MAGICID; }
void	DDALine(int x0, int y0, int x1, int y1, int nRange, vector<POINT>& vctPoint);

//////////////////////////////////////////////////////////////////////
class CMagic  
{
protected:
	CMagic(PROCESS_ID idProcess, IRole* pRole);
	virtual ~CMagic();

private:
	CMagic() { m_bAutoAttack = false;}

public:
	static CMagic* CreateNew(PROCESS_ID idProcess, IRole* pRole);
	ULONG	ReleaseByOwner()	{ delete this; return 0; }
	void	OnTimer(DWORD tCurr);

public: // login
	bool	CreateAll();
	bool	SendInfoToClient();

public: // MapGroup
	bool	SaveInfo();
	bool	GetInfoByIndex(MagicInfoStruct* pInfo, int idx);
	bool	AppendMagic(const MagicInfoStruct* pInfo);

public: // application
	IMagicSet*	QuerySet()		{ CHECKF(m_setData); return m_setData; }
	bool		MagicAttack(int nType, OBJID idTarget, int x, int y, UCHAR ucAutoActive = 0);		// return false: NO BROADCAST
	bool		AbortMagic(bool bSynchro=false);
	void		OwnerUpLevel(int nOwnerLev);

	bool		AutoLearnMagic();
	
	void		UserWeaponSkillUpLevel(int nWeaponSkillType, int nWeaponSkillLevel);
	bool		AutoLearnWeaponSkill(int nWeaponSkillType, int nWeaponSkillLevel, int nWeaponSkillExp=0);
	bool		UserKillTarget(IRole* pTarget);
	bool		AutoAttackTarget(IRole* pTarget);
	IMagicData*	FindMagic(int nType);
	int			GetExtendAtkRange	(CItem* pWeaponR, CItem* pWeaponL);
	bool		AwardExp(int nType, int nBattleExp, int nExp);
	bool		AwardExp(int nBattleExp, int nExp = AWARDEXP_BY_TIMES, bool bIgnoreFlag=false);		// ͬʱ֧������ã���bAddBattleExpӦ��Ϊ0�����ڱ�����
	void		BreakAutoAttack();
	void		DebugReloadAll(){
					for(int i = 0; i < m_setData->GetAmount(); i++)
						m_setData->GetObjByIndex(i)->FindType();
				}

	bool		IsIntone()		{ return m_nMagicState == MAGICSTATE_INTONE; }	//return (m_tIntone.IsActive() && !m_tIntone.IsTimeOut()); }
	bool		IsInLaunch()	{ return m_nMagicState == MAGICSTATE_LAUNCH; }	//return (m_tApply.IsActive() && !m_tApply.IsTimeOut()); }
	bool		IsActive()		{ return (m_nMagicState != MAGICSTATE_NONE); }

public: // static
	static CMagicTypeData*	FindMagicType(int nType, int nLevel);
	static int 	CalcMagicPower(IRole* pAtker, IRole* pTarget, int* pAdjustAtk=0);

protected:
	bool		AwardExpOfLife(IRole* pRole, int nLoseLife, BOOL bMagicRecruit=false);
	void		ShowMiss();
	int			Attack(int nType, IRole* pRole);		// return lose life
	int			Attack(int nType, int x, int y);		// return lose life
	int			Launch();
	bool		UpLevel(bool bSynchro = true);
	bool		CheckCondition(IMagicData* pData, OBJID idTarget, int x, int y);
	bool		CheckCrime(const vector<IRole*>* pSet);
	bool		CheckCrime(IRole* pRole);

	bool		LockTarget(bool bLock);
//	bool		AdjustUserPos();
//	bool		AdjustTargetPos();
	bool		AdjustPosByTrack(int nStepIndex, bool bAtkerPenetrable=false, bool bTargetPenetrable=false);

	bool		CheckProfession(DWORD dwProf, DWORD dwNeedProf);

protected: // calc magic fight
	bool		CheckAwardExpEnable(DWORD dwProf);
	void		OtherMemberAwardExp(IRole* pTarget, int nRawExp);

public: // const
	enum { HIT_BY_MAGIC, HIT_BY_WEAPON, HIT_BY_ITEM };
	bool		IsImmunity(IRole* pRole);
	int			HitByMagic();
	bool		HitByWeapon();
	int			GetDieMode();
	bool		IsKeepBow()						{ return false; }	//m_pMagic && m_pMagic->GetInt(MAGICDATA_SORT) == MAGICSORT_ATTACHSTATUS && m_pMagic->GetInt(MAGICDATA_STATUS) == STATUS_KEEPBOW; }
	int			GetPower(int nStepIndex = -1);
//	int			GetApplyMS(int nStepIndex = -1);
	
public: // task
	bool		CheckType(int nType);
	bool		CheckLevel(int nType, int nLevel);
	bool		UpLevelByTask(int nType);

public: // create
	void		ResetDelay();
	OBJID		LearnMagic(int nType, int nLevel=0, bool bSaveMagic=true);
	bool		UnlearnMagic(int nType, bool bDrop);
	bool		EquipWeaponMagic(OBJID idMagic, int nType, int nLevel);
	bool		UnequipWeaponMagic(OBJID idMagic);

protected: // process
	bool		ProcessAttack();
	bool		ProcessAtkStatus();
	bool		ProcessRecruit();
	bool		ProcessCross();
	bool		ProcessLine();
	bool		ProcessFan();
	bool		ProcessBomb();
	bool		ProcessBombLockAll();
	bool		ProcessSquare();
	bool		ProcessAttach();
	bool		ProcessDetach();
	bool		ProcessJumpAttackFaild(int x, int y);
	bool		ProcessJumpAtk();
	bool		ProcessRandomTrans();
	bool		ProcessDispatchXP();
	bool		ProcessCollideFail(int x, int y, int nDir);
	bool		ProcessCollide();
	bool		ProcessSerialCut();
	bool		ProcessCallTeamMember();
	bool		ProcessRecordTransSpell();
	bool		ProcessTransform();
	bool		ProcessAddMana();
	bool		ProcessLayTrap();
	bool		ProcessCallPet();
	bool		ProcessDecLife();
	bool		ProcessGroundSting();
	bool		ProcessReborn();
	bool		ProcessSorbSoul();
	bool		ProcessSteal();

	////////////////////////////////////////////////////////
	// ��������ħ������
	bool		ProcessBlastThunder();
	bool		ProcessMultiAttach();
	bool		ProcessMultiDetach();
	bool		ProcessMultiCure();
	bool		ProcessStealMoney();
	bool		ProcessKO();
	bool		ProcessEscape();
//	bool		ProcessFlashAttack();


	typedef std::vector<IRole*>	ROLE_SET;
	enum { LOCK_NONE, LOCK_ONE, LOCK_ALL };
	bool		CollectTargetSet_Bomb(ROLE_SET& setRole, POINT& pos, int nLockType=LOCK_NONE);
	bool		CollectTargetSet_Team(ROLE_SET& setRole);

protected: // spawn id
	static OBJID	SpawnMagicID()						{ return InterlockedIncrement(&m_lockNextID); }

protected: // data
	IMagicSet*		m_setData;

protected: // intone
	IMagicData*		m_pMagic;
	OBJID			m_idTarget;
	POINT			m_pos;
	int				m_nData;
	bool			m_bAutoAttack;
	int				m_nRawDelay;		// fast delay for trans map
	int				m_nDelay;			// normal delay

	int				m_nMagicState;		// ħ��״̬	-- zlong 2004-11-30

	CTimeOutMS		m_tIntone;			// ������ʱ
	CTimeOutMS		m_tApply;			// ÿ��Ч����ʱ
	int				m_nApplyTimes;		// ����Ч������
	CTimeOutMS		m_tDelay;			// ʩչ������ʱ

	vector<OBJID>	m_setTargetLocked;	// ħ���������й켣��Ŀ�꼯
	bool			m_bTargetLocked;

private: // cheat --------
	OBJID			m_cheatTargetID;
	int				m_cheatCount;

// XP add by arhun
public:
	BOOL HaveXpMagic();	// �Ƿ�ѧ��XP����

protected: // ctrl
	PROCESS_ID		m_idProcess;
	IRole*			m_pOwner;
	static long		m_lockNextID;
	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_MAGIC_H__B2689767_419D_487F_B0F9_FBB04C4619AA__INCLUDED_)
