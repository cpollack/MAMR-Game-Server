// Syndicate.h: interface for the CSyndicate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNDICATE_H__78C1D98F_7DA8_482D_9819_22AD24402CB6__INCLUDED_)
#define AFX_SYNDICATE_H__78C1D98F_7DA8_482D_9819_22AD24402CB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "NetWorkDef.h"
#include "protocol.h"
#include "GameData.h"
#include "GameObj.h"
#include <vector>
using namespace std;

const int	SYN_MONEY_BASELINE		= 0;					// ���ɻ������ڸ�ֵ�������ư��ɹ���

//////////////////////////////////////////////////////////////////////
enum {
		SYNFUNC_DEMISE=1,
		SYNFUNC_SETTENET,
		SYNFUNC_SETLEADERTITLE,
		SYNFUNC_SETMEMBERTITLE,
		SYNFUNC_ADDDATA,
		SYNFUNC_SETDATA,
		SYNFUNC_PRESENT,
		SYNFUNC_ADD_MEMBER,
		SYNFUNC_DEL_MEMBER,
		SYNFUNC_UP_LEVEL,
		SYNFUNC_SETSYNNAME,
};

//////////////////////////////////////////////////////////////////////
const int	MAX_SYNENEMYSIZE		= 5;		// һ��5���ж԰��ɿռ�
const int	MAX_SYNALLYSIZE			= 5;		// һ��5�����˰��ɿռ�
enum SYNDATA{
		SYNDATA_ID=0,			// ������INSERT

		SYNDATA_NAME=1,			// ������
		SYNDATA_TENET,			// ������ּ
		SYNDATA_ANNOUNCE,		// ���ɹ���
		SYNDATA_MEMBERTITLE,	// ���ɳ�Ա�ƺ�
		SYNDATA_LEADERID,		// ����ID
		SYNDATA_LEADERNAME,		// ��������
		SYNDATA_MONEY,			// ���ɻ���
		SYNDATA_FEALTY,			// Master ID
		SYNDATA_DEL_FLAG,
		SYNDATA_AMOUNT,			// ��������
		SYNDATA_ENEMY0,			// �ж԰���
		SYNDATA_ENEMY1,
		SYNDATA_ENEMY2,
		SYNDATA_ENEMY3,
		SYNDATA_ENEMY4,
		SYNDATA_ALLY0,			// ͬ�˰���
		SYNDATA_ALLY1,
		SYNDATA_ALLY2,
		SYNDATA_ALLY3,
		SYNDATA_ALLY4,
		SYNDATA_RANK,			// ��ʿ�ŵȼ�  1 ~ 5
		SYNDATA_SAINT,			// ʥ��ʿ��    (0: NULL��1��ʥ)
		SYNDATA_MANTLE_FALG,	// �����־    add huang 2004.1.1
		SYNDATA_DISMISS_TIME,	// �Զ���ɢ��ʼʱ��   //add huang 2004.1.5
		SYNDATA_REPUTE,			// ��������
		SYNDATA_PUBLISHTIME,	// ���淢��ʱ�䣬��ʽ��yyyymmdd
};
namespace world_kernel {
	char	szSynTable[];
}
typedef	CGameData<SYNDATA, world_kernel::szSynTable, szID>	CSynBase;

const int   DISMISSSYN_MONEY_LIMIT  = 100000;           // ��Ǯ���ڴ������Զ���ɢ��//add huang 2004.1.5
const int	DISMISSSYN_AMOUNT_LIMIT	= 20;				// �������ڴ������Զ���ɢ  
const int   DISMISSSYN_TIME_LIMIT   = 24*60*60;         // �Զ���ɢ����ʱ�� 24Сʱ


//////////////////////////////////////////////////////////////////////
class ISynModify
{
public:
	virtual bool	Demise(OBJID idOldLeader,int nOldSynMemberLevel,OBJID idNewLeader, LPCTSTR szNewLeader, int nNewSynMemberLevel, OBJID idBackSyn, bool bSave=true)		PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetTenet(LPCTSTR szTenet, bool bSave=true)													PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetLeaderTitle(LPCTSTR szLeaderTitle, bool bSave=true)										PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetMemberTitle(LPCTSTR szMemberTitle, bool bSave=true)										PURE_VIRTUAL_FUNCTION_0
	virtual bool	AddData(SYNDATA idx, int nData, bool bSave=true)											PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetData(SYNDATA idx, int nData, bool bSave=true)											PURE_VIRTUAL_FUNCTION_0
	virtual bool	PresentMoney(OBJID idSyn, int nMoney, bool bSave=true)										PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetSynName(LPCTSTR szSynName, bool bSave=true)												PURE_VIRTUAL_FUNCTION_0
};

//////////////////////////////////////////////////////////////////////
// ���г�Ա����Ϊԭ�Ӳ�����
class CSyndicate : public CGameObj, ISynModify
{
protected:
	CSyndicate();
	virtual ~CSyndicate();
public:
	static CSyndicate* CreateNew() { ASSERT(!"CSyndicate::CreateNew()"); return NULL; }				// ����CSynPtr
	static CSyndicate* CreateNew(PROCESS_ID idProcess)	{ CSyndicate* ptr=new CSyndicate; if(ptr) ptr->m_idProcess=idProcess; return ptr; }
	virtual ULONG	ReleaseByOwner()				{ delete this; return 0; }
	bool	Create(IRecordset* pRes);
	bool	Create(const CreateSyndicateInfo* pInfo, bool bSave);
	ISynModify*		QueryModify()	{ return (ISynModify*)&m_obj; }
	bool			ChangeSyndicate(const SynFuncInfo0* pFuncInfo);
	bool			ReloadData();

public: // const
	OBJID	GetID()							{ return m_pData->GetKey(); }
	int		GetInt(SYNDATA idx);
	LPCTSTR	GetStr(SYNDATA idx)				{ return m_pData->GetStr(idx); }
	void	BroadcastSynMsg(CNetMsg* pMsg, CUser* pExcludeSender=NULL);
	void	BroadcastSubSynMsg(SOCKET_ID idSocket, OBJID idNpc, LPCTSTR szMsg, CUser* pExcludeSender=NULL, LPCTSTR pszEmotion=NULL, DWORD dwColor=0xffffff, int nAttribute=_TXTATR_SYNDICATE);
	LPCTSTR	GetFealtyName();
	bool	IsNearSyn(OBJID idSyn);
//	OBJID	GetMasterSynID()				{ if(GetInt(SYNDATA_FEALTY) != ID_NONE) return GetInt(SYNDATA_FEALTY); return GetID(); }
	CSyndicate*		GetMasterSyn();
	bool	IsFriendly(OBJID idSyn, BOOL bNest=true);		// mast be true
	bool	IsHostile(OBJID idSyn, BOOL bNest=true);		// mast be true
	bool	IsNeutral(OBJID idSyn);
	bool	IsWhiteSynMapOwner();
	bool	IsBlackSynMapOwner();
	int		GetMemberAmount(bool bIncludeSub = true);
	int		GetSynAmount();
	bool    AutoDismissSyn();
protected:
	bool    CheckDismissTime();    // add huang 2004.1.7
	bool    CheckDismissSyn();     
	void	BroadcastLocalSynMsg(CNetMsg* pMsg, CUser* pExcludeSender=NULL);

public: // application
	void	SendInfoToClient(CUser* pUser);
	void	SetNewSubName(LPCTSTR szName);		// ��ʱ����
	
	bool	ClearAllySyn(CSyndicate* pTargetSyn);
	bool	ClearEnemySyn(CSyndicate* pTargetSyn);

public: // link -------------------------------------
	CAutoLink<CSyndicate>&	QueryLink	()					{ return m_link; }
protected:
	CAutoLink<CSyndicate>	m_link;

public: // syn war -------------------------------------
	void	AddSynWarScore(OBJID idNpc, int nScore);
	int		GetSynWarScore(OBJID idNpc);
	void	ClearSynWarScore(OBJID idNpc);
protected:
	struct	SynWarInfo{
		OBJID	idNpc;
		int		nScore;
	};
	typedef	vector<SynWarInfo>	SYNWAR_SET;
	SYNWAR_SET		m_setSynWarScore;
protected: // modify, mast be atom operator. test & set
	// bSave ����Ϊtrue�����򲻻����
	virtual bool	AddData(SYNDATA idx, int nData, bool bSave);
	virtual bool	Demise(OBJID idOldLeader,int nOldSynMemberLevel,OBJID idNewLeader, LPCTSTR szNewLeader, int nNewSynMemberLevel, OBJID idBackSyn, bool bSave);
	virtual bool	SetTenet(LPCTSTR szTenet, bool bSave);
	virtual bool	SetLeaderTitle(LPCTSTR szLeaderTitle, bool bSave);
	virtual bool	SetMemberTitle(LPCTSTR szMemberTitle, bool bSave);
	virtual bool	SetData(SYNDATA idx, int nData, bool bSave);
	virtual bool	PresentMoney(OBJID idSyn, int nMoney, bool bSave);
	virtual bool	SetSynName(LPCTSTR szSynName, bool bSave);
public:
	int GetMoney();

private:
	CSynBase*	m_pData;

protected: // ctrl
	PROCESS_ID		m_idProcess;
	MYHEAP_DECLARATION(s_heap)
protected:
	class	XSynModify : public ISynModify
	{
	public:
		virtual bool	Demise(OBJID idOldLeader,int nOldSynMemberLevel,OBJID idNewLeader, LPCTSTR szNewLeader, int nNewSynMemberLevel, OBJID idBackSyn, bool bSave);
		virtual bool	SetTenet(LPCTSTR szTenet, bool bSave);
		virtual bool	SetLeaderTitle(LPCTSTR szLeaderTitle, bool bSave);
		virtual bool	SetMemberTitle(LPCTSTR szMemberTitle, bool bSave);
		virtual bool	AddData(SYNDATA idx, int nData, bool bSave);
		virtual bool	SetData(SYNDATA idx, int nData, bool bSave);
		virtual bool	PresentMoney(OBJID idSyn, int nMoney, bool bSave);
		virtual bool	SetSynName(LPCTSTR szSynName, bool bSave);
	protected:
		CSyndicate*		This()		{ return m_pOwner; }
		CSyndicate*		m_pOwner;
		friend class CSyndicate;
	} m_obj;
public:
	void	SynchroInfo();

	OBJID	GetMasterSynID();
	bool	FallLevel();
	bool	IsFallLevel();
	bool	IsSubSubSyn();
	bool	IsSubSyn();
	int		GetSubSubSynNum();
	bool	IfCanCreateSubSubSyn();
	bool	IsMasterSyn()				{ return (GetInt(SYNDATA_FEALTY) == ID_NONE); }
	//����ÿ�ܻ���ͳһ�ĵط����ű��ܾ��������һ������Ϊ��Ա����
	bool	AllotBonusForMember(CUserPtr pUser,DWORD dwBonus);
	bool	ApplyKickoutMember(CUserPtr pLeader,CUserPtr pTarget);
	int		GetSubSynNum();
	friend class CSyndicate::XSynModify;
};

#endif // !defined(AFX_SYNDICATE_H__78C1D98F_7DA8_482D_9819_22AD24402CB6__INCLUDED_)
