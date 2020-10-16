// Npc.h: interface for the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKNPC_H__D7A2DFC3_2C2C_4F67_BB52_8F55409E76BC__INCLUDED_)
#define AFX_TASKNPC_H__D7A2DFC3_2C2C_4F67_BB52_8F55409E76BC__INCLUDED_

#include "MyHeap.h"
#include "GameData.h"
#include "NpcShop.h"
#include "NpcStorage.h"
#include "NpcTable.h"
#include "Myheap.h"
#include "Role.h"
#include "AutoPtr.h"
//#include "Auction.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUser;
class CGameMap;

/////////////////////////////////////////////////////////////////////////////////////
//define constant ..
const	int	ADD_NEW_NPC				= 0;
const	int LAY_NEW_NPC				= 10;
const	int PRE_CHANGE_POSITION		= 11;
const	int CHANGE_POSITION			= 12;
const	int DYNANPCDIEDELAY_SECS	= 3;		// DYNA_NPC�����������ɾ��
const	int	GOAL_EXP_PERCENT		= 10;		// ����ӵľ���ֵ�ٷֱ�(���εľ���ֵ��5%�Ļ���)
const	int	SYNFLAG_SIZEADD			= 5;		// �������ӵĸ��ӳߴ�
const	int	SYNWAR_GAINMONEY_PERCENT			= 10;		// ����ս�õ��Է�����ı���
const	int	DEFAULT_NPC_SIZEADD			= 4;		// ÿ�����������
const	int SYNWARLETTERNPC_CHECKINTERVAL = 60*20;//ÿ���20���Ӽ��ռ������Ƿ���7��
/////////////////////////////////////////////////////////////////////////////////////
const	int	_MAX_NPCTASK			=8;
const	int	MAX_NPCDATA				=4;		// ����С��_MAX_NPCTASK

/////////////////////////////////////////////////////////////////////////////////////
// ����ʹ�õ�DATA���
enum {
		SYNFLAGNPC_FIXFUND=0,SYNFLAGNPC_FIGHTBEGIN,SYNFLAGNPC_FIGHTEND,SYNFLAGNPC_MOREMAPID,					// ���ɱ�־(time:WWHHMMSS, sun day = 7)
		SYNWARLETTER_ISATTACK=0,SYNWARLETTER_ATTACK_SYNID=1,SYNWARLETTER_OCCUPYTIME=2,SYNWARLETTER_DEPOSIT=3,
		SYNDRESS_SORT=0,SYNDRESS_SETTING=1,
		GOALNPC_LEVEL=3,
		TIMERNPC_TIME=3,
		TRUNKNPC_SIZE=3,
		EUDEMON_BROODER_NPC_SIZE=2, EUDEMON_STORAGE_NPC_SIZE=3,
		STORAGENPC_SIZE=3,
		NEIGHBORNPC_X=1,NEIGHBORNPC_Y=2,NEIGHBORNPC_SERIAL=3,
};			//? Ŀǰһ�����֧��4������

/////////////////////////////////////////////////////////////////////////////////////
enum NPCTYPE{
		_NPC_NONE				= 0,			// ͨ��NPC
		_SHOPKEEPER_NPC			= 1,			// �̵�NPC
		_TASK_NPC				= 2,			// ����NPC(�����ϣ������ڼ��ݾ�����)
		_STORAGE_NPC			= 3,			// �Ĵ洦NPC
		_TRUNCK_NPC				= 4,			// ����NPC
		_FACE_NPC				= 5,			// ��ͷ��NPC
		_FORGE_NPC				= 6,			// ����NPC		(only use for client)
		_EMBED_NPC				= 7,			// ��ǶNPC
		_STATUARY_NPC			= 9,			// ����NPC
		_SYNFLAG_NPC			= 10,			// ���ɱ��NPC
		_ROLE_PLAYER			= 11,			// �������		(only use for client)
		_ROLE_HERO				= 12,			// �Լ�			(only use for client)
		_ROLE_MONSTER			= 13,			// ����			(only use for client)
		_BOOTH_NPC				= 14,			// ��̯NPC		(CBooth class)
		_SYNTRANS_NPC			= 15,			// ���ɴ���NPC, �̶��Ǹ���Ҫ�ô�����! (����00:00�շ�)(LINKIDΪ�̶�NPC��ID��������ʹ��LINKID�Ļ���)
		_ROLE_BOOTH_FLAG_NPC	= 16,			// ̯λ��־NPC	(only use for client)
		_ROLE_MOUSE_NPC			= 17,			// ����ϵ�NPC	(only use for client)
		_ROLE_MAGICITEM			= 18,			// �����ǽ		(only use for client)
		_ROLE_DICE_NPC			= 19,			// ����NPC
		_ROLE_SHELF_NPC			= 20,			// ��Ʒ��
		_WEAPONGOAL_NPC			= 21,			// ��������NPC
		_MAGICGOAL_NPC			= 22,			// ħ������NPC
		_BOWGOAL_NPC			= 23,			// ��������NPC
		_ROLE_TARGET_NPC		= 24,			// ���򣬲���������	(only use for client)
		_ROLE_FURNITURE_NPC		= 25,			// �Ҿ�NPC	(only use for client)
		_ROLE_CITY_GATE_NPC		= 26,			// ����NPC	(only use for client)
		_ROLE_NEIGHBOR_DOOR		= 27,			// �ھӵ���
		_ROLE_CALL_PET			= 28,			// �ٻ���	(only use for client)
		_EUDEMON_TRAINPLACE_NPC	= 29,			// ����ѱ����
		 _AUCTION_NPC			= 30,			// ����NPC	��Ʒ��ȡNPC  LW
		 _ROLE_MINE_NPC			= 31,			// ��ʯNPC		 
		 
		 _ROLE_3DFURNITURE_NPC	= 101,			// 3D�Ҿ�NPC 
		 
		 _SYN_NPC_WARLETTER     = 110,			//�����µģΣУ����͡�ר����������ս��ġ����ɣΣУ�
};

/////////////////////////////////////////////////////////////////////////////////////
enum NPCSORT{
		NPCSORT_NONE		= 0,
		NPCSORT_TASK		= 1,			// ������
		NPCSORT_RECYCLE		= 2,			// �ɻ�����
		NPCSORT_SCENE		= 4,			// ������(����ͼ���)
		NPCSORT_LINKMAP		= 8,			// �ҵ�ͼ��(LINKIDΪ��ͼID��������ʹ��LINKID�Ļ���)
		NPCSORT_DIEACTION	= 16,			// ����������(LINKIDΪACTION_ID��������ʹ��LINKID�Ļ���)
		NPCSORT_DELENABLE	= 32,			// �����ֶ�ɾ��(����ָͨ������)
		NPCSORT_EVENT		= 64,			// ����ʱ����, ʱ����data3�У���ʽΪMMWWHHMMSS��(LINKIDΪACTION_ID��������ʹ��LINKID�Ļ���)
		NPCSORT_TABLE		= 128,			// �����ݱ�����

//		NPCSORT_SHOP		= ,			// �̵���
//		NPCSORT_DICE		= ,			// ����NPC

		NPCSORT_USELINKID	= NPCSORT_LINKMAP | NPCSORT_DIEACTION | NPCSORT_EVENT,
};

/////////////////////////////////////////////////////////////////////////////////////
struct NPCINFO_ST{
	OBJID	idOwner;
	int		nOwnerType;
	OBJID	idMap;
	int		nPosX;
	int		nPosY;
	int		nType;
	int		nLookFace;
	int		setTask[_MAX_NPCTASK];
	int		setData[MAX_NPCDATA];
	NAMESTR	szData;
	OBJID	idLink;
	int		nLife;
	OBJID	idBase;
	int		nSort;
	char	cLength;
	char	cFat;
};

/////////////////////////////////////////////////////////////////////////////////////
enum NPCDATA{
		//NPCDATA_OWNERID=1,
		NPCDATA_ID,
		//NPCDATA_OWNERTYPE,
		NPCDATA_NAME,
		NPCDATA_TYPE,
		NPCDATA_LOOK,		//STATUARYDATA_DIR=NPCDATA_LOOKFACE,
		//NPCDATA_LENGTH,		// �߰� -- zlong 2004-02-03
		//NPCDATA_FAT,		// ����
		NPCDATA_MAPID,
		NPCDATA_POSX_,		// �ⲿ��Ҫֱ��ʹ�ã�ע����m_nPosX��ͬ��
		NPCDATA_POSY_,		// �ⲿ��Ҫֱ��ʹ�ã�ע����m_nPosY��ͬ��
		NPCDATA_TASKCOUNT,
		NPCDATA_TASK0,		STATUARYDATA_HELMET=NPCDATA_TASK0,
		NPCDATA_TASK1,		STATUARYDATA_ARMOR=NPCDATA_TASK1,
		NPCDATA_TASK2,		STATUARYDATA_WEAPONR=NPCDATA_TASK2,
		NPCDATA_TASK3,		STATUARYDATA_WEAPONL=NPCDATA_TASK3,
		NPCDATA_TASK4,		STATUARYDATA_FRAME=NPCDATA_TASK4,
		NPCDATA_TASK5,		STATUARYDATA_POSE=NPCDATA_TASK5,
		NPCDATA_TASK6,		STATUARYDATA_LOOKFACE=NPCDATA_TASK6,
		NPCDATA_TASK7,		STATUARYDATA_RANKSHOW_HAIR=NPCDATA_TASK7,
		NPCDATA_FACE,
		NPCDATA_IDXSERVER,
		NPCDATA_OWNERID,
		NPCDATA_DATA0,
		NPCDATA_DATA1,
		NPCDATA_DATA2,
		NPCDATA_DATA3,
		//NPCDATA_DATASTR,
		//NPCDATA_LINKID,		// �ҵ�ͼ��ĵ�ͼID����������ID
		//NPCDATA_LIFE,
		//NPCDATA_MAXLIFE,
		//NPCDATA_BASE,
		//NPCDATA_SORT,
		//NPCDATA_ITEMTYPE,

		//NPCDATA_SIZE_FRONT,
		//NPCDATA_SIZE_BACK,
		//NPCDATA_SIZE_LEFT,
		//NPCDATA_SIZE_RIGHT,

		//HSB0-2?
		NPCDATA_HUE0,
		NPCDATA_SATURATION0,
		NPCDATA_BRIGHT0,
};

typedef	IGameData<NPCDATA>	INpcData;
char	szNpcTable[];
typedef	CGameData<NPCDATA,szNpcTable, szID>	CNpcData;
char	szDynTable[];
typedef	CGameData<NPCDATA,szDynTable, szID>	CDynaNpcData;

/////////////////////////////////////////////////////////////////////////////////////
//class CNpcTrunk;
class CNpcTask;
class CNpcScene;
class CNpcLink;
class CNpcBet;
class CAuction;
class CNpc : public CGameObj, public CRole
{
protected:
	CNpc();
	virtual ~CNpc();
public:
	static CNpc* CreateNew()								{ return new CNpc; }
	bool	Create(PROCESS_ID idProcess, NPCINFO_ST* pInfo, OBJID idItemType, LPCTSTR szName);
	bool	Create(PROCESS_ID idProcess, IRecordset* pRecordset, bool bDynaNpc);
//����	bool	Create(OBJID id);
//����	bool	Create(TaskNpcInfo* pInfo);		// INSERT DB
//	virtual ULONG	ReleaseByOwner()							{ delete this; return 0; }

	IRole*			QueryRole()									{ return (IRole*)this; }
	virtual		bool		FindAroundObj	(OBJID idObjType, OBJID idObj, void** pp)		{ return GetMap()->QueryObj(GetPosX(), GetPosY(), idObjType, idObj, pp); }
public: // IRole ================================================================================
	virtual void	ReleaseByOwner()							{ delete this; }
	virtual OBJID	GetID()										{ return m_id; }
	virtual int 	GetObjType()								{ return CGameObj::GetObjType(); }
	virtual int		GetPosX()									{ return m_nPosX; }//m_pData->GetInt(NPCDATA_POSX); }
	virtual int		GetPosY()									{ return m_nPosY; }//m_pData->GetInt(NPCDATA_POSY); }
	virtual void	SendShow(IRole* pRole);							// ����ҷ��������������

public: // get attrib
	virtual LPCTSTR	GetName				();
//	virtual LPCTSTR	GetMate				()						{ return NOMATE_NAME; }

	virtual DWORD	GetLook				()						{ return m_pData->GetInt(NPCDATA_LOOK); }
	//virtual DWORD	GetLookFace			()						{ if(GetType()==_STATUARY_NPC) return m_pData->GetInt(STATUARYDATA_LOOKFACE); return m_pData->GetInt(NPCDATA_LOOK); }
	//virtual char	GetLength			()						{ return m_pData->GetInt(NPCDATA_LENGTH); }
	//virtual char	GetFat				()						{ return m_pData->GetInt(NPCDATA_FAT); }
	virtual DWORD	GetHair				()						{ return m_pData->GetInt(STATUARYDATA_RANKSHOW_HAIR)&0xFFFF; }
	virtual int 	GetDir				()						{ return MaskDir(m_pData->GetInt(NPCDATA_LOOK))%MAX_DIRSIZE; }
//	virtual	BOOL	CheckStatus			(int nStatus)			{ return 0; }
	virtual I64		GetEffect			()						{ return m_i64Effect; }
	virtual int 	GetPose				()						{ return m_pData->GetInt(STATUARYDATA_POSE); }
	virtual DWORD	GetLev				()						{ if(IsGoal()) return GetData(GOALNPC_LEVEL); return 0; }
	virtual std::vector<HSB> GetHSBSets();

	//virtual DWORD	GetLife				()						{ return m_pData->GetInt(NPCDATA_LIFE); }
	//virtual DWORD	GetMaxLife			()						{ return m_pData->GetInt(NPCDATA_MAXLIFE); }

	virtual DWORD	GetAtkHitRate		()						{ ASSERT(!"GetAtkHitRate"); return 0; }

	virtual int		GetArmorTypeID		();
	virtual int		GetWeaponRTypeID	();
	virtual int 	GetWeaponLTypeID	();
	virtual int 	GetMountTypeID		();



//	virtual CGameMap*	GetMap			()						{ CHECKF(m_pMap); return m_pMap; }

	//virtual DWORD	GetSynID			()						{ return m_pData->GetInt(NPCDATA_OWNERTYPE)==OWNER_SYN ? m_pData->GetInt(NPCDATA_OWNERID) : ID_NONE; }
	//virtual DWORD	GetSynRankShow		()						{ return m_pData->GetInt(STATUARYDATA_RANKSHOW_HAIR)>>16; }

public: // const
	//virtual bool	IsAlive				()						{ return !(IsDynaNpc() && m_pData->GetInt(NPCDATA_MAXLIFE)>0 && m_pData->GetInt(NPCDATA_LIFE)<=0 || IsDeleted()); }		// NPCDATA_LIFE is a flag
	//virtual bool	IsDelThis			()						{ return IsDeleted() && m_tDie.IsTimeOut(); }		// ASSERT(!IsAlive()); 

	// return true: ppv���ض���ָ��
	virtual bool	QueryObj(OBJID idObjType, void** ppv)		{ if(idObjType==OBJ_NPC) return *ppv=this,true; return *ppv=NULL,false; }
	virtual bool	QueryRole(void** ppv)						{ return *ppv=QueryRole(),true; }
	virtual CUser*	QueryOwnerUser		()						{ return NULL; }		//@@@ ��

public:	// modify attrib ------------------------------
	virtual	void	SetStatus			(int nStatus, bool bSynchro=true);
	virtual	void	ClsStatus			(int nStatus, bool bSynchro=true);
	virtual bool	AddAttrib			(int idxAttr, __int64 i64Data, int bSynchro);
	virtual void	ProcessOnMove		(int nMoveMode)						{}

	virtual	IStatus*	QueryStatus(OBJID idType)							{ ASSERT(IsDynaNpc()); return CRole::QueryStatus(idType); }
	virtual	IStatusSet*	QueryStatusSet()									{ ASSERT(IsDynaNpc()); return CRole::QueryStatusSet(); }

public: // money --------------------------------
//	virtual bool	SpendMoney			(DWORD nMoney, bool bSynchro)		{ return 0; }
//	virtual bool	GainMoney			(DWORD nMoney, bool bSynchro)		{ return 0; }

public: // system
	virtual void	BroadcastRoomMsg(CNetMsg* pMsg, bool bSendSelf = false);
	virtual void	BroadcastRoomMsg(LPCTSTR szMsg, bool bSendSelf = false);
	virtual void	OnTimer(time_t tCurr);

public: // map
	virtual bool	MoveToward(int nDir)									{ return 0; }
	virtual void	TransPos(int nPosX, int nPosY);
	virtual void	JumpPos(int nPosX, int nPosY)							{}
	virtual bool	SyncTrackTo(int nPosX, int nPosY, int nDir, DWORD dwAction)		{ return 0; }
	virtual void	GetFootPrint	(int& nPosX, int& nPosY)				{ nPosX = GetPosX(); nPosY = GetPosY(); }

public: // fight ------------------------------
	virtual void	ClrAttackTarget		()									{ SetAttackTarget(NULL); }
	virtual bool	SetAttackTarget(IRole* pTarget)							{ return true; }
	virtual bool	AutoSkillAttack(IRole* pTarget)							{ return false; }
	virtual bool	AdditionMagic(int nLifeLost, int nDamage)				{ return false; }
	virtual int		Attack(IRole* pTarget)									{ ASSERT(!"Attack"); return 0; }
	virtual bool	BeAttack(bool bMagic, IRole* pTarget, int nPower, bool bReflectEnable=true);
	virtual bool	MagicAttack(int nType, OBJID idTarget, int x, int y)	{ ASSERT(!"MagicAttack"); return 0; }
	virtual void	Kill(IRole* pTarget, DWORD dwDieWay)					{ ASSERT(!"Kill"); }
	virtual void	BeKill(IRole* pTarget = NULL);
	virtual bool	IsAtkable(IRole* pTarget, bool bSendHint=false)			{ return false; }
	virtual bool	IsBeAtkable();
	virtual int		GetAttackRange(int nTargetSizeAdd)						{ ASSERT(!"GetAttackRange"); return 0; }
	virtual int		GetSizeAdd()											{ if(IsSynFlag()) return SYNFLAG_SIZEADD; return DEFAULT_NPC_SIZEADD; }
	virtual	int		GetLuck()												{ return 0; }
	virtual void	SendDamageMsg(OBJID idTarget, int nDamage)				{ ASSERT(!"SendDamageMsg"); }
private: // IRole ================================================================================
//	int			m_nPosX, m_nPosY;

public: // const
	//int 			GetSort()									{ return m_pData->GetInt(NPCDATA_SORT); }
	int 			GetType()									{ return m_pData->GetInt(NPCDATA_TYPE); }
	void			ChangeDir(int nLook)						{ m_pData->SetInt(NPCDATA_LOOK, MakeLookFace(MaskLook(GetLookFace()), MaskDir(nLook))); }
	//bool			IsRecycleEnable()							{ return (GetSort() & NPCSORT_RECYCLE) != 0; }
	enum { MATE_ENABLE=true };
	bool			IsOwnerOf(CUser* pUser, bool bMateEnable=false);
	//bool			IsDieAction()								{ return (GetSort() & NPCSORT_DIEACTION) != 0; }
	bool			IsStatuary()								{ return GetType() == _STATUARY_NPC; }		// �Զ�����CGameMap::m_idSyn
	bool			IsGoal()									{ return GetType()==_WEAPONGOAL_NPC || GetType()==_MAGICGOAL_NPC || GetType()==_BOWGOAL_NPC; }
	bool			IsSynFlag()									{ return GetType() == _SYNFLAG_NPC; }
	bool			IsAwardScore()								{ return GetType() == _SYNFLAG_NPC; }
	bool			IsDelEnable();
	//bool			IsSynNpc()									{ return GetInt(NPCDATA_OWNERTYPE)==OWNER_SYN && GetInt(NPCDATA_OWNERID)!=ID_NONE; }
	//bool			IsUserNpc()									{ return GetInt(NPCDATA_OWNERTYPE)==OWNER_USER && GetInt(NPCDATA_OWNERID)!=ID_NONE; }
	int 			GetStorageSize()							{ return GetData(STORAGENPC_SIZE); }
	bool			IsSynMoneyEmpty();
	bool			IsShelfNpc()								{ return m_pData->GetInt(NPCDATA_TYPE) == _ROLE_SHELF_NPC; }
	bool			IsSynWarLetter()							{ return GetType() == _SYN_NPC_WARLETTER; }//�Ƿ�����ս��ģΣУ�
	
public: // application
	bool			SendSelfToBlock();
	bool			SendLeaveFromBlock();
	bool			ActivateNpc(IRole* pRole, int nAction);			// ��������в���
	CItem*			Recycle(OBJID idUser);			//??? need call DelNpc() follow
	bool			DelNpc();						// call this mast !IsDeleted()
protected:
	bool			DeleteRecord()								{ CHECKF(IsDynaNpc()); return m_pData->DeleteRecord(); }
	void			CheckFightTime();
	void			RecruitLife();
	void			BroadcastScore();

public:
	//---------- NPC ���Դ�ȡ���� --------------------------
	int				GetInt		(NPCDATA idx)					{ CHECKF(m_pData); return m_pData->GetInt(idx); }
	LPCTSTR			GetStr		(NPCDATA idx)					{ CHECKF(m_pData); return m_pData->GetStr(idx); }
	int				GetData		(int idx)						{ CHECKF(m_pData); CHECKF(idx>=0 && idx<MAX_NPCDATA); return m_pData->GetInt(NPCDATA(NPCDATA_DATA0 + idx)); }
	OBJID			GetMapID	();

	//---------- �޸�NPC���� ------------------
	void			SetInt		(NPCDATA idx, int nData, bool bUpdate = false)	{ CHECK(m_pData && IsDynaNpc()); m_pData->SetInt(idx, nData); if(bUpdate) m_pData->Update(); }
	void			SetStr		(NPCDATA idx, LPCTSTR szData, int nSize, bool bUpdate = false)	{ CHECK(m_pData && IsDynaNpc()); m_pData->SetStr(idx, szData, nSize); if(bUpdate) m_pData->Update(); }
	void			SetData		(int idx, int nData, BOOL bUpdate)	{ 
										CHECK(m_pData && IsDynaNpc()); 
										CHECK(idx < MAX_NPCDATA); 
										m_pData->SetInt(NPCDATA(NPCDATA_DATA0 + idx), nData); 
										if(bUpdate) m_pData->Update(); }
	void			SaveInfo	();
	BOOL			ChangePos		(OBJID idMap, int nPosX, int nPosY);
	bool			SetSynOwnerID(OBJID idSyn, BOOL bWithLinkMap);		// true: with link map
	bool			SetUserOwnerID(OBJID idUser, BOOL bWithLinkMap);		// true: with link map

public: // ����ӿ� ------------------------------------------------------------------
	void SetOccupyTime();
	int GetLostFixMoney();
	int GetMaxFixMoney();
	void OnFightEnd();
	OBJID GetApplyAttackerSynID();
	
	virtual bool		IsShopNpc()							{ return m_pData->GetInt(NPCDATA_TYPE) == _SHOPKEEPER_NPC; }		// || (m_pData->GetInt(NPCDATA_SORT)&NPCSORT_SHOP)!=0
	virtual CNpcShop*	QueryShop()							{ CHECKF(m_pShop); return m_pShop; }

	//virtual bool		IsTaskNpc()							{ return m_pData->GetInt(NPCDATA_TYPE)==_TASK_NPC || (m_pData->GetInt(NPCDATA_SORT)&NPCSORT_TASK)!=0; }
	virtual CNpcTask*	QueryTask()							{ CHECKF(m_pTask); return m_pTask; }

	virtual	bool		IsStorageNpc()						{ return m_pData->GetInt(NPCDATA_TYPE) == _STORAGE_NPC; }
//	virtual	bool		IsAuctionStorageNpc()				{ return m_pData->GetInt(NPCDATA_TYPE) == _AUCTION_NPC/*_AUCTION_STORAGE_NPC*/; }
	virtual	bool		IsAuctionNpc()				        { return m_pData->GetInt(NPCDATA_TYPE) == _AUCTION_NPC; }
//    virtual IAuction*   QueryAuction()                      {CHECKF(m_pAuction);return m_pAuction/*->QueryInterface()*/;}
//����Ҫ	virtual CNpcStorage*	QueryStorage()						{ CHECKF(m_pStorage); return m_pStorage; }

	virtual	bool		IsTrunkNpc()						{ return m_pData->GetInt(NPCDATA_TYPE) == _TRUNCK_NPC || m_pData->GetInt(NPCDATA_TYPE) == _ROLE_SHELF_NPC; }
	virtual CNpcTrunk*	QueryTrunk()						{ if(!m_pTrunk) CreateFuncTrunk(m_idProcess); CHECKF(m_pTrunk); return m_pTrunk; }

	// ���޷�����NPC -- ����Trunk��ʵ��
	virtual bool		IsEudemonBrooderNpc()				{ return m_pData->GetInt(NPCDATA_TYPE) == _EUDEMON_TRAINPLACE_NPC; }
	virtual CNpcTrunk*	QueryEudemonBrooder()				{ if (!m_pEudemonBrooder) CreateFuncEudemonBrooder(m_idProcess); CHECKF (m_pEudemonBrooder); return m_pEudemonBrooder; }

	// ���޲ֿ�NPC -- ����Trunk��ʵ��
	virtual bool		IsEudemonStorageNpc()				{ return m_pData->GetInt(NPCDATA_TYPE) == _EUDEMON_TRAINPLACE_NPC; }
	virtual CNpcTrunk*	QueryEudemonStorage()				{ if (!m_pEudemonStorage) CreateFuncEudemonStorage(m_idProcess); CHECKF (m_pEudemonStorage); return m_pEudemonStorage; }
															//?? ��ʱ����
	//virtual bool		IsSceneNpc()						{ return (m_pData->GetInt(NPCDATA_SORT) & NPCSORT_SCENE) != 0; }
	virtual CNpcScene*	QueryScene()						{ CHECKF(m_pScene); return m_pScene; }

	//virtual bool		IsLinkNpc()							{ return (m_pData->GetInt(NPCDATA_SORT) & NPCSORT_LINKMAP) != 0; }
	virtual CNpcLink*	QueryLinkMap()						{ CHECKF(m_pLinkMap); return m_pLinkMap; }

	virtual CNpcTable*	QueryTable()						{ return m_pTable; }

	virtual bool		IsBetNpc()							{ return m_pData->GetInt(NPCDATA_TYPE) == _ROLE_DICE_NPC; }		// || (m_pData->GetInt(NPCDATA_SORT)&NPCSORT_BET)!=0
	virtual CNpcBet*	QueryBet()							{ CHECKF(m_pBet); return m_pBet; }

	OBJID				GetRecordID()						{ CHECKF(m_pData); return m_pData->GetID(); } 
	bool				IsDeleted()							{ return m_tDie.IsActive(); }

	bool				IsDynaNpc()							{ return m_bDynaNpc; }
private:
	bool				CreateFuncObj(PROCESS_ID idProcess);
	bool				CreateFuncTrunk(PROCESS_ID idProcess);
	bool				CreateFuncEudemonBrooder(PROCESS_ID idProcess);
	bool				CreateFuncEudemonStorage(PROCESS_ID idProcess);
	bool				CheckSortMutex();
	void				UpdateHoldFloor(bool bEnter);

protected:
	CNpcShop*			m_pShop;
//	IAuction*           m_pAuction;
	CNpcTask*			m_pTask;
//	CNpcStorage*		m_pStorage;
//	CNpcTrunk*          m_pUserAuctionStorage;
	CNpcTrunk*			m_pTrunk;
	CNpcScene*			m_pScene;
	CNpcLink*			m_pLinkMap;
	CNpcBet*			m_pBet;
	CAutoPtr<CNpcTable>	m_pTable;

	CNpcTrunk*			m_pEudemonBrooder;
	CNpcTrunk*			m_pEudemonStorage;

protected: // data
	OBJID			m_id;
	INpcData*		m_pData;
	bool			m_bDynaNpc;
//	CGameMap*		m_pMap;				// fast reference
//	IStatusSet*		m_setStatus;
	I64				m_i64Effect;

protected: // ctrl
	CTimeOut		m_tSynEvent;
	CTimeOut		m_tBroadcastScore;
	CTimeOut		m_tDie;
	CTimeOut		m_tSynWarLetter;//ÿ���20���Ӽ��ռ������Ƿ���7��
	bool			m_bFeeOK;
//	PROCESS_ID		m_idProcess;

	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_TASKNPC_H__D7A2DFC3_2C2C_4F67_BB52_8F55409E76BC__INCLUDED_)
