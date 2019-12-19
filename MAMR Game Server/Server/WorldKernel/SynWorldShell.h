// SynShell.h: interface for the CSyndicateWorld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNSHELL_H__8147FFBF_85B9_43E4_9D3A_B847BF31F088__INCLUDED_2)
#define AFX_SYNSHELL_H__8147FFBF_85B9_43E4_9D3A_B847BF31F088__INCLUDED_2

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "GameData.h"
#include "protocol.h"
#include "AutoPtr.h"
#include <vector>
#include <string>
using namespace std;

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
	extern char	szID[256];
	extern char	szSynTable[256];
}
typedef	CGameData<SYNDATA, world_kernel::szSynTable, world_kernel::szID>	CSynWorldBase;

//////////////////////////////////////////////////////////////////////
class ISynModify
{
public:
	virtual bool	Demise(OBJID idOldLeader,int nOldSynMemberLevel,OBJID idNewLeader, LPCTSTR szNewLeader, int nNewSynMemberLevel, OBJID idBackSyn, bool bSave)		PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetTenet(LPCTSTR szTenet, bool bSave)													PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetLeaderTitle(LPCTSTR szLeaderTitle, bool bSave)										PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetMemberTitle(LPCTSTR szMemberTitle, bool bSave)										PURE_VIRTUAL_FUNCTION_0
	virtual bool	AddData(SYNDATA idx, int nData, bool bSave)												PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetData(SYNDATA idx, int nData, bool bSave)												PURE_VIRTUAL_FUNCTION_0
	virtual bool	PresentMoney(OBJID idSyn, int nMoney, bool bSave)										PURE_VIRTUAL_FUNCTION_0
	virtual bool	SetSynName(LPCTSTR szSynName, bool bSave=true)											PURE_VIRTUAL_FUNCTION_0
};

//////////////////////////////////////////////////////////////////////
class CMessageBoard;

// ���г�Ա����Ϊԭ�Ӳ�����
struct CPlayer;
class CSyndicateWorld : ISynModify
{
protected:
	CSyndicateWorld();
	virtual ~CSyndicateWorld();
public:
	static CSyndicateWorld* CreateNew()	{ return new CSyndicateWorld; }
	virtual ULONG	ReleaseByOwner()				{ delete this; return 0; }
	bool	Create(IRecordset* pRes);
	bool	Create(IRecordset* pRes, const CreateSyndicateInfo* pInfo, bool bSave);
	ISynModify*		QueryModify()					{ return (ISynModify*)this; }
	CMessageBoard*	QueryMessageBoard()				{ ASSERT(m_ptrMsgBd); return m_ptrMsgBd; }
	bool			ChangeSyndicate(const SynFuncInfo0* pFuncInfo);

public:
	OBJID	GetID()									{ return m_pData->GetKey(); }
	int		GetInt(SYNDATA idx)						{ return m_pData->GetInt(idx); }
	LPCTSTR	GetStr(SYNDATA idx)						{ return m_pData->GetStr(idx); }

protected: // syn member list --------------------------
	struct	MemberInfo{
		MemberInfo(LPCTSTR str, int nUserRank) 
		{
			szName	= str;
			nRank	= nUserRank;
		}
		string	szName;	
		int		nRank;	//��Ҿ���
	};
	typedef	vector<MemberInfo>	MEMBER_SET;
public:
	int		GetSynRankShow(int nRank);
//	void	SendMemberListSpecifySyn(CPlayer* pUser, int idxLast);
	CSyndicateWorld* GetMasterSyn();
	bool	AddMember(LPCTSTR szName, int nUserRank);
	bool	DelMember(LPCTSTR szName);
	int		GetMemberAmount()				{ return m_setMember.size(); }
	void	SendMemberList(CPlayer* pUser, int idx);
	void	CombineMemberList(const MEMBER_SET& setMember);
	MEMBER_SET&	QueryMemberList()						{ return m_setMember; }
protected:
	int		AppendMember(class CMsgNameW& msg, int idx, int idxFirst, int& nCount);
//	int		AppendOnlineMember(class CMsgName& msg, int idxFirst);
//	int		AppendOnlineMemberForAllMember(class CMsgName& msg, int idxFirst);
//	int		AppendOfflineMember(class CMsgName& msg, int idxFirst, int nCurrCount=0);
//	int		AppendOfflineMemberForAllMember(class CMsgName& msg, int idx, int nCount=0);
protected:
	MEMBER_SET	m_setMember;
//	MEMBER_SET	m_setMemberTmp;

protected: // modify, mast be atom operator. test & set
	// bSave ����Ϊtrue�����򲻻����
	virtual bool	Demise(OBJID idOldLeader,int nOldSynMemberLevel,OBJID idNewLeader, LPCTSTR szNewLeader, int nNewSynMemberLevel, OBJID idBackSyn, bool bSave);
	virtual bool	SetTenet(LPCTSTR szTenet, bool bSave);
	virtual bool	SetLeaderTitle(LPCTSTR szLeaderTitle, bool bSave);
	virtual bool	SetMemberTitle(LPCTSTR szMemberTitle, bool bSave);
	virtual bool	AddData(SYNDATA idx, int nData, bool bSave);
	virtual bool	SetData(SYNDATA idx, int nData, bool bSave);
	virtual bool	PresentMoney(OBJID idSyn, int nMoney, bool bSave);
	virtual bool	SetSynName(LPCTSTR szSynName, bool bSave);

private:
	CSynWorldBase*	m_pData;

protected: // msgbd
	typedef	CAutoPtr<CMessageBoard>	MSGBD_PTR;
	MSGBD_PTR		m_ptrMsgBd;

protected: // ctrl
	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_SYNSHELL_H__8147FFBF_85B9_43E4_9D3A_B847BF31F088__INCLUDED_2)
