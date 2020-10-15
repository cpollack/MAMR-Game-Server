// Pet.h: interface for the CMonster class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "define.h"
#include "gameobj.h"
#include "Timeout.h"
#include "Item.h"
#include "Myheap.h"
#include "GameMap.h"
#include "StatusMore.h"
#include "protocol.h"
#include "autolink.h"
#include "Role.h"
#include "PetData.h"
#include "UserTable.h"

//////////////////////////////////////////////////////////////////////
const DWORD _IDMSK_PET = 0x80000000;

extern DWORD NEXT_PETID;
extern DWORD GetNext_PetID(IDatabase *pDb);


//////////////////////////////////////////////////////////////////////
class CPet : public CGameObj, public CRole
{
protected:
	CPet();
	virtual ~CPet();
public:
	static CPet* CreateNew() { return new CPet; }

	//static	CPet*	CreateNewPet(PROCESS_ID idProcess, PetInfoStruct* pInfo);
	static	CPet*	CreateNewPet(PROCESS_ID idProcess, OBJID ownerId, CMonster* pMonster);
	bool	Create(PROCESS_ID idProcess, OBJID idPet);
	void	ReleaseByOwner() { delete this; }

protected: // Query Data
	virtual bool		QueryRole(void** ppv) { return *ppv = (IRole*)this, true; }
	virtual bool		QueryObj(OBJID idObjType, void** ppv) { if (idObjType == OBJ_MONSTER) return *ppv = this, true; return *ppv = NULL, false; }
public:
	virtual IMapThing*	QueryMapThing() { return (IMapThing*)this; }
	IRole*				QueryRole() { return (IRole*)this; }

public: // IRole
		//	virtual OBJID	GetID();
	virtual LPCTSTR	GetName() { return data.GetName(); }							
								//	virtual LPCTSTR	GetMate()							{ return NOMATE_NAME; }
	virtual LPCTSTR	GetTitle() { return TITILE_NONE; }

	virtual DWORD 	GetHair() { return 0; }
	virtual int 	GetPosX() { return m_nPosX; }
	virtual int 	GetPosY() { return m_nPosY; }
	virtual int 	GetDir() { return m_nDir; }
	//	virtual	BOOL	CheckStatus			(int nStatus);
	virtual I64		GetEffect() { return m_i64Effect; }
	// 幻兽不使用monstertype表中的等级属性字段 -- zlong 2004-02-24
	virtual DWORD	GetLev() { return data.GetLevel(); }

	virtual	DWORD	GetLife() { return data.GetLife(); } 	//			{ return m_nCurrLife; }
	virtual double	GetMaxLife() { return data.GetMaxLife(); }	//				{ return (m_AddInfo.nMaxLifeAdd + m_pType->GetInt(NPCTYPEDATA_LIFE)); }
									//	virtual DWORD	GetMana				()				{ return m_nCurrMana; }
									//	virtual DWORD	GetMaxMana			()				{ return m_pType->GetInt(NPCTYPEDATA_MANA); }
	//virtual DWORD	GetMinAtk();
	//virtual DWORD	GetMaxAtk();
	//virtual DWORD	GetMgcMinAtk();
	//virtual DWORD	GetMgcMaxAtk();
	virtual double	GetAttack() { return data.GetAttack(); } //{ return (GetMaxAtk() + GetMinAtk()) / 2; }	//{ return (m_pType->GetInt(NPCTYPEDATA_ATTACKMIN)+m_pType->GetInt(NPCTYPEDATA_ATTACKMAX))/2; }
	//virtual DWORD	GetDef();
	virtual double	GetDefence() { return data.GetDefence(); }
	//virtual DWORD	GetDefence2() { return m_pType->GetInt(NPCTYPEDATA_DEFENCE2); }
	//virtual DWORD	GetDex();
	virtual double	GetDexterity() { return data.GetDexterity(); } //{ return m_pType->GetInt(NPCTYPEDATA_DEXTERITY); }
	//virtual DWORD	GetDdg();
	//virtual DWORD	GetDodge(); //{ return m_pType->GetInt(NPCTYPEDATA_DODGE); }
	//	virtual DWORD	GetMagicAtk			()				{ return 0; }
	//virtual DWORD	GetMagicDef();
	//virtual	DWORD	GetInterAtkRate();
	//virtual	DWORD	GetIntervalAtkRate() { return m_pType->GetInt(NPCTYPEDATA_ATKSPEED); }

	//virtual int		AdjustExp(IRole* pTarget, int nRawExp, bool bNewbieBonusMsg = false);
	//virtual void	AwardBattleExp(int nExp, bool bGemEffect = true, bool bIncludeOwner = true);
	//virtual int 	AdjustHitRate(int nHitRate) { /*IStatus* pStatus = QueryStatus(STATUS_HITRATE); if(pStatus) return ::CutTrail(0, AdjustData(nHitRate, pStatus->GetPower()));*/ return nHitRate; }
	//virtual int 	AdjustAttack(int nAtk);
	//virtual int 	AdjustDefence(int nDef);
	//virtual int 	AdjustMagicAtk(int nAtk) { IStatus* pStatus = QueryStatus(STATUS_SUPER_MATK); if (pStatus) return ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower())); return nAtk; }
	//virtual int 	AdjustMagicDef(int nDef);
	//virtual int 	AdjustBowDefence(int nDef) { /*IStatus* pStatus = QueryStatus(STATUS_BOWDEFENCE); if(pStatus) return ::CutTrail(0, AdjustData(nDef, pStatus->GetPower()));*/ return nDef; }
	//virtual int 	AdjustWeaponDamage(int nDamage);
	//virtual int 	AdjustMagicDamage(int nDamage);
	//virtual void	SetFightPause(int nInterval) { m_nFightPause = nInterval; }

	virtual CUser*	QueryOwnerUser() { return m_pOwner; }

	virtual DWORD	GetLook() { return data.GetLook(); }
	virtual ELEMENT GetElement() { return element; }

	//virtual void	BroadcastRoomMsg(CNetMsg* pMsg, bool bSendSelf = false);
	//virtual void	BroadcastRoomMsg(LPCTSTR szMsg, bool bSendSelf = false);
	//virtual void	BroadcastMapMsg(CNetMsg* pMsg, bool bSendSelf = false);
	//virtual void	BroadcastMapMsg(LPCTSTR szMsg, bool bSendSelf = false);
	//virtual bool	SendMsg(CNetMsg* pMsg);
	//virtual bool	SendSysMsg(const char* fmt, ...);
	//virtual void	OnTimer(time_t tCurr);

public: // map
	//bool	EnterMapGroup();
	//bool	LeaveMapGroup();
	//	virtual bool	MoveToward(int nDir);
	//	virtual void	TransPos(int nPosX, int nPosY);		// 传送，完全的新坐标
	//	virtual void	JumpPos(int nPosX, int nPosY);		// 跳，半屏以内
	//	virtual bool	SyncTrackTo(int nPosX, int nPosY, int nDir, DWORD dwAction);	// 魔法轨迹同步
	//virtual bool	SendSelfToBlock();
	//bool	SendLeaveFromBlock();

	//bool	KickBack();

public: // foot print
	//void	GetFootPrint(int& nPosX, int& nPosY);

protected:
	DWORD	m_tFootPrint;
	POINT	m_posFootPrint;

public: // get
	virtual OBJID	GetID() { return ID; }
	virtual int		GetObjType() { return CGameObj::GetObjType(); }
	//virtual OBJID	GetMapID()		{ return m_idMap; }
	//virtual void	SendShow(IRole* pRole);

public: // get attrib  ------------------------------------
	void	SetOwner(CUser* pOwner) { m_pOwner = pOwner; SetOwnerID(((CRole*)pOwner)->GetID()); }
	void	SetOwnerID(OBJID id) { data.SetOwnerID(id);  }
	OBJID	GetOwnerID() { return data.GetOwnerID(); }

	int		GetLoyalty() { return data.GetLoyalty(); }

	//virtual int		GetType() { return pData->; }
	//	virtual int		GetSex			()		{ return 0; }
	//virtual bool	IsAlive();
	//virtual bool	IsTalkEnable() { return m_dwStatus == STATUS_NORMAL; }
	//virtual bool	IsMonster() { return IsMonsterID(GetID()) && !IsGuard() && !IsPkKiller(); }
	//virtual bool	IsDelThis() { return IsDeleted() && m_tDie.IsTimeOut(); }		// ASSERT(!IsAlive()); 
	//virtual bool	IsVirtuous() { return IsGuard() || IsPkKiller(); }
	//virtual bool	IsEvil() { return ((m_pType->GetInt(NPCTYPEDATA_ATKUSER)&ATKUSER_RIGHTEOUS) == 0 || QueryStatus(STATUS_CRIME)); }
	//virtual bool	IsBowman() { return CItem::IsBowSort(GetWeaponRTypeID()); }
	//virtual bool	IsShieldEquip() { return CItem::IsShield(GetWeaponLTypeID()); }
	//virtual bool	IsWing() { return (m_pType->GetInt(NPCTYPEDATA_ATKUSER)&ATKUSER_WING) != 0; }
	//virtual bool	IsSendBlockInfo() { return (!IsCallPet() && !IsEudemon()); }

	//static	bool	IsMonsterID(OBJID id) { return id >= MONSTERID_FIRST && id <= MONSTERID_LAST; }
	//bool		IsGuard() { return (m_pType->GetInt(NPCTYPEDATA_ATKUSER)&ATKUSER_GUARD) != 0; }
	//bool		IsPkKiller() { return (m_pType->GetInt(NPCTYPEDATA_ATKUSER)&ATKUSER_PPKER) != 0; }
	//bool		IsDeleted() { return m_tDie.IsActive(); }
	//void		DelMonster(bool bNow = false);			//? call this mast !IsDeleted()
	//bool		IsSynPet() { return m_idNpc >= PETID_FIRST && m_idNpc <= PETID_LAST; }
	//bool		IsSynMonster() { return (m_idNpc >= PETID_FIRST && m_idNpc <= PETID_LAST) && !m_pData; }
	//bool		IsCallPet() { return m_idNpc >= CALLPETID_FIRST && m_idNpc <= CALLPETID_LAST; }
	//OBJID		GetMasterID();
	CPetData*			GetData() { return &data; }
	//OBJID		GetGenID() { return m_idGen; }
	//bool		IsTaskMonster() { return this->GetType() >= TYPE_TASK_MONSTER; }
	//bool		IsMagicAtk() { return m_pType->GetInt(NPCTYPEDATA_MAGIC_TYPE) != ID_NONE && m_pType->GetInt(NPCTYPEDATA_MAGIC_HITRATE) == 0; }
	//OBJID		GetMagicType() { return m_pType->GetInt(NPCTYPEDATA_MAGIC_TYPE); }
	//bool		IsMapRoar() { return (m_pType->GetInt(NPCTYPEDATA_ATKUSER)&ATKUSER_ROAR) != 0; }
	//bool		IsEquality() { return (m_pType->GetInt(NPCTYPEDATA_ATKUSER)&ATKUSER_EQUALITY) != 0; }
	//bool		IsEudemon() { return (m_idNpc >= EUDEMON_ID_FIRST && m_idNpc <= EUDEMON_ID_LAST); }
	//static int	GetNameType(int nAtkerLev, int nMonsterLev);

	virtual bool IsSuper() { return (data.GetClass() / 10000) == 1; }
	virtual bool IsUnevo() { return (data.GetClass() / 10000) == 7; }

public:	// modify attrib ------------------------------
	//virtual void	SetDir(int nDir) { m_nDir = nDir % 8; }
	//virtual void	SetPose(int nPose) { m_nPose = nPose; }
	//	virtual void	SetEmotion(int nEmotion)	{ }//m_nEmotin = nEmotion; }

	//virtual	void	SetStatus(int nStatus, bool bSynchro = true);
	//virtual	void	ClsStatus(int nStatus, bool bSynchro = true);

	//virtual bool	AddAttrib(int idxAttr, __int64 i64Data, int nSynchro);
	//virtual	void	ProcessOnMove(int nMoveMode);
	//virtual void	ProcessAfterMove();
public: // money --------------------------------
		//	virtual bool	SpendMoney(DWORD nMoney, bool bSynchro)		{ return true; }
		//	virtual bool	GainMoney(DWORD nMoney, bool bSynchro)		{ return true; }

public: // fight ------------------------------
	//virtual void	ClrAttackTarget() { SetAttackTarget(NULL); }
	//virtual bool	SetAttackTarget(IRole* pTarget);
	//virtual bool	AutoSkillAttack(IRole* pTarget);
	//virtual bool	AdditionMagic(int nLifeLost, int nDamage);
	//virtual int		Attack(IRole* pTarget);		// return : lose life
	//virtual bool	BeAttack(bool bMagic, IRole* pTarget, int nPower, bool bReflectEnable = true);
	//virtual bool	MagicAttack(int nType, OBJID idTarget, int x, int y) { if (m_pMagic) return m_pMagic->MagicAttack(nType, idTarget, x, y); return false; }
	//virtual void	Kill(IRole* pTarget, DWORD dwDieWay);
	//virtual void	BeKill(IRole* pRole = NULL);	//pTarget = NULL);						// 可能删除NPC对象
	//virtual bool	IsAtkable(IRole* pTarget, bool bSendHint = false);
	//virtual bool	IsBeAtkable();
	//virtual void	SendDamageMsg(OBJID idTarget, int nDamage);
	//int 	GetDieMode();
	//bool	IsInsteadMagic();
	//bool	IsImmunity(IRole* pRole);

public: // interactive
		//	virtual bool	AddItem		(CItem* pItem)				{ CHECKF(pItem); pItem->ReleaseByOwner(); return true; }
		//	virtual bool	IsItemFull	()							{ return false; }
	//virtual bool	Freeze(int nSecs);							// return false: 解穴不成功

																//	virtual CGameMap*		GetMap			()			{ ASSERT(m_pMap); return m_pMap; }

public: // action
	//bool	ProcessAction(CUser* pUser, OBJID idAction, LPCTSTR pszAccept = NULL);

public: // status
public: // user status --------------------------------------------------------------------------------
		//	IStatus*	QueryStatus(OBJID idType)		{ CHECKF(m_setStatus); return m_setStatus->GetObj(idType); }
		//	IStatusSet*	QueryStatusSet()				{ CHECKF(m_setStatus); return m_setStatus; }
	//void		ClearAllStatus();
protected: // data
		   //	IStatusSet*	m_setStatus;

public: // common -------------------------------------
		//	static int	AdjustData			(int nData, int nAdjust, int nMaxData=0);

public: // pet ----------------------------------------------------
	//bool	Create(PROCESS_ID idProcess, IRecordset* pRes);
	//void	SaveInfo();			//??? save all when close server!!!

public: // call pet ---------------------------------
	//CAutoLink<CPet>&	QueryLink() { return m_link; }
protected:
	CUser* m_pOwner;
	//CAutoLink<CPet>	m_link;
	//CMagicTypeData*		m_pMagicType;			// may be null
	//CTimeOut			m_tMagic;

	//CMagic*				m_pMagic;				// may be null 

public:
	//DWORD	GetDropMoneyAvg();
	//bool	DropMoney(DWORD dwMoney, OBJID idOwner);
	// modifyed by zlong 2003-11-19
	// 增加设置magic2,magic3的默认参数
	//bool	DropItem(OBJID idItemType, OBJID idOwner, int nMagic2 = 0, int nMagic3 = 0, int nUserLuck = 0, bool bIsAllowDropUnident = false);

protected:
	CPetData	data;	

protected:
	//bool	DropMedicine(OBJID idOwner);
	//bool	DropEquipment(DWORD dwValue, OBJID idOwner, DWORD dwQuality = 0);

protected: // attrib
	OBJID		ID;
	//OBJID		ownerID;
	//	int			m_nPosX;
	//	int			m_nPosY;
	//	int			m_nDir;
	DWORD		m_dwStatus;
	I64			m_i64Effect;
	//int			m_nPose;
	//	CGameMap*	m_pMap;

	ELEMENT element;
	//int		LifeCurrent;
	//int			m_nCurrMana;

	//int			m_nPotential;		
	//DWORD		m_dwMaskData;
public:
	//DWORD	GetMaskData() { return m_dwMaskData; }
	//void	SetMaskData(DWORD dwMask) { m_dwMaskData = dwMask; }
	//void	AddMaskData(DWORD dwMask) { m_dwMaskData |= dwMask; }
	//void	ClsMaskData(DWORD dwMask) { m_dwMaskData &= ~dwMask; }

public:	// eudemon -------------------------------
		//bool DropTrap(TRAP_INFO &trapInfo, UINT ulLifePeriod);
		// 此函数只需要在创建幻兽的时候调用一次即可，由于功能已经改变，以后最好换个函数名
	//void	SetEudemonAddi(CItem*	pEudemon);
	//DWORD	GetFidelity() { IF_NOT(IsEudemon() && m_pEudemonItem) return 0; return m_pEudemonItem->GetInt(ITEMDATA_FIDELITY); }

	//OBJID	GetDivineID() { IF_NOT(IsEudemon() && m_pEudemonItem) return 0; return m_pEudemonItem->GetDivineID(); }
	//UCHAR	GetRelationShip(OBJID idDivine) { IF_NOT(IsEudemon() && m_pEudemonItem) return 0; return m_pEudemonItem->GetRelationShip(idDivine); }
	//bool	AddRelationShip(OBJID idDivine, int nValue) { IF_NOT(IsEudemon() && m_pEudemonItem) return 0; return m_pEudemonItem->AddRelationShip(idDivine, nValue); }

	//int		GetAtkMode() { ASSERT(IsEudemon()); return m_nAtkMode; }
	//bool	ChgAtkMode(int nAtkMode);

protected:
	//DWORD	GetEudemonLev() { IF_NOT(IsEudemon() && m_pEudemonItem) return 0; return m_pEudemonItem->GetEudemonLevel(); }

protected:
	// 幻兽各属性根据等级、成长计算出来的差值，需要加成到属性中的
	/*
	struct {
	int			nMaxAtkAdd;			// 物理攻击
	int			nMinAtkAdd;
	int			nMaxMAtkAdd;		// 魔法攻击
	int			nMinMAtkAdd;
	int			nDefAdd;			// 物理防御
	int			nMDefAdd;			// 魔法防御
	int			nMaxLifeAdd;		// 最大生命

	int			nAtkSpeedAdd;		// 攻击速度
	int			nHitRateAdd;		// 命中率
	int			nDodgeAdd;			// 躲避率

	//		int			nEudemonLev;		// 等级
	} m_AddInfo;
	*/

	//CItem*		m_pEudemonItem;		// refrence

protected: // fight
		   //CBattleSystem*		m_pBattleSystem;
	CTimeOutMS			m_tFight;
	int					m_nFightPause;						// 僵硬状态时，一次性增加的间隔毫秒数

	CTimeOut			m_tSorbReflect;
	int					m_nTotalDamage;

	int					m_nKillNum;							// 杀死的目标数
	int					m_nKillNum4Potential;				// 杀死目标数量——为了增加潜力值而做的统计
	int					m_nKillNum4RelationShip;			// 杀死目标数量——为了增加关系值而做的统计

	int					m_nAtkMode;		// 攻击类型

protected: // Monster Type
	CMonsterType*	pType;		// reference

protected: // application
	CTimeOut	m_tDie;
	auto_long	m_bLeaveMap;
	bool		m_bDecRole;

protected: // ctrl
	CTimeOut	m_tAddLife;
	CTimeOut	m_tIncLife;
	OBJID		m_idGen;
	//	PROCESS_ID	m_idProcess;

	MYHEAP_DECLARATION(s_heap)
};
