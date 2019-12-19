// SynAttr.h: interface for the CSynAttr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNATTR_H__7205A42E_F451_4A87_9BBD_37397D6578E2__INCLUDED_)
#define AFX_SYNATTR_H__7205A42E_F451_4A87_9BBD_37397D6578E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "GameData.h"
#include "GameObj.h"
#include "Myheap.h"
#include "AutoLink.h"
#include "Syndicate.h"

#define	DEFAULT_TENET				""
#define	DEFAULT_LEADERTITLE			STR_SYNDICATE_LEADER
#define	DEFAULT_MEMBERTITLE			STR_SYNDICATE_MEMBER
//---jinggy---2004-12-7---define---begin
#define TIMEONLINE_FIRSTJOIN		10*60	//�״μ��������ʱ������10*60����
//---jinggy---2004-12-7---define---end
//////////////////////////////////////////////////////////////////////
const int	DEFAULT_PROFFER			= 0;				// ���˵Ĺ���
const int	CHANGELEADER_DAYS		= 30;				// ����30�첻���ߣ����ܱ��滻
const int	CHANGELEADER_MONEY		= 100000;			// �滻����Ҫ�����Ǯ��
const int	SYNMONEY_LIMIT			= 2000000000;		// ��������ƶ�
const int	SYNPROFFER_LIMIT		= 1000000000;		// ���׵����ƶ�
const int	MAX_ASSISTANTSIZE		= 5;				// ����ж��ٸ����������ݶ�
const int	SYN_MEMBER_LIMIT		= 800;				// ����������ն��ٸ�����

//---jinggy---2004-12-7---����---begin
const int	MONEY_PER_MEMBER		= 10000;			// �������ӵĻ���
const int	MONEY_PER_MEMBER_OUT	= 30000;		// ���������ŶӼ��ٵĻ���
const int	MONEY_KICKOUT			= 20000;			// ������Ա�۳��Ļ���
//---jinggy---2004-12-7---����---end

//---jinggy---2004-12-7---����---begin
const int	REPUTE_PER_MEMBER		= 1000;			// �������ӵ�����1000
const int	REPUTE_PER_MEMBER_OUT	= 3000;			// �����˳����پ�������3000
const int	REPUTE_KICKOUT			= 1000;			// ������Ա�۳�������1000
//---jinggy---2004-12-7---����---end
//---jinggy---���׶�---begin

//---jinggy---���׶�---end

//////////////////////////////////////////////////////////////////////
struct SynAttrInfoStruct
{
	OBJID		id;
	OBJID		idSyn;
	USHORT		usMantle;
	UCHAR		ucRank;
	UCHAR		ucRankShow;
	int 		nProffer;
	int			nProfferInc;
	int			nTitle;
	UCHAR		ucLevel;
};

//////////////////////////////////////////////////////////////////////
enum SYNATTRDATA
{
	SYNATTRDATA_ID=0,		     // ����INSERT
	SYNATTRDATA_NAME,
	SYNATTRDATA_RANK,
	SYNATTRDATA_TITLE=4,
	SYNATTRDATA_SYNID=1,
	//SYNATTRDATA_PROFFER,
	//---jinggy---2004-12-7---begin
//	SYNATTRDATA_TIMEONLINE,		//��Ա������ʱ�䣬��2����û�дﵽ10��Сʱ��Ϊ���Ѱ���
//	SYNATTRDATA_TIMEDETECTED,	//�����͵�ǰʱ����бȽϣ����Ƿ���2���µ�ʱ����
//	SYNATTRDATA_PROFFERINC,		//��¼��Ա���ϴΰ��ɷ��Ž����õ���Proffer�ۼ�ֵ
//	SYNATTRDATA_MEMBERLEVEL,	//��Ա����
	//---jinggy---2004-12-7---end
//	SYNATTRDATA_TITLE,				// ����
};
char	szSynAttrTable[];
typedef	CGameData<SYNATTRDATA, szSynAttrTable, szID>		CSynAttrData;

//////////////////////////////////////////////////////////////////////
class CSynAttr  
{
protected:
	CSynAttr();
	virtual ~CSynAttr();

public:
	static CSynAttr* CreateNew(PROCESS_ID idProcess, CUser* pUser);
	ULONG	ReleaseByOwner()						{ delete this; return 0; }
//	void	OnTimer(DWORD tCurr);

public: // login
	bool	Create();
	bool	SendInfoToClient();

public: // MapGroup
	bool	SaveInfo();
	bool	GetInfo(SynAttrInfoStruct* pInfo);
	bool	AppendSynAttr(SynAttrInfoStruct* pInfo);

public: // const
	OBJID	GetSynID()								{ if(m_pData) return m_pData->GetInt(SYNATTRDATA_SYNID); return ID_NONE; }
	int		GetInt(SYNATTRDATA idx)					{ CHECKF(m_pData); ASSERT(idx!=SYNATTRDATA_SYNID); return m_pData->GetInt(idx); }
	int		GetAssistantCount();
	DWORD	GetSynRankShow		();
	LPCTSTR	GetRankTitle();
//	int		SumSynMember();
	//int		GetProffer(void)	const				{ if(m_pData) return m_pData->GetInt(SYNATTRDATA_PROFFER); return 0; }
	//---jinggy---�õ�����ֵ������
	//int		GetProfferInc(void)	const				{ if(m_pData) return m_pData->GetInt(SYNATTRDATA_PROFFERINC); return 0; }
	
public: // modify
	bool	CreateSyndicate(LPCTSTR szName, int nLevel, int nMoney, int nMoneyLeave);
//	bool	CreateSubSyn(LPCTSTR szName, int nLevel,int nProffer, int nMoney, int nMoneyLeave);
	OBJID	CreateSubSyn(OBJID idFealty,const char* pszName);
	bool	DestroySyndicate();
	bool	JoinSyn(OBJID idSyn, int nRank=RANK_NEWBIE, int nProffer=0);
	bool	AddMemberList(OBJID idSyn, LPCTSTR szName, int nLevel);
	bool	LeaveSyn(bool bKickout=false, bool bDeleteRecord=true, bool bSynchro=true);
	bool	DelMemberList(OBJID idOldSyn, LPCTSTR szName);
	bool	DonateMoney(int nMoney);
	bool	SetRank(int nRank, bool bLeader = false);
	bool	ChangeLeader(LPCTSTR szSyn, int nLevel);
	bool	SetIdRank(OBJID idSyn, int nRank, bool bSynchro=true);
	bool	AddProffer(int nData);
	bool	DecProffer(int nData);
	void	UpLevel(int nLevel);			// synchro world kernel member list
	void	SetProffer(int nProffer);


public:
	void	SynchroInfo(BOOL bAnnounce=false);				// �޸ĺ󣬹㲥�Լ�������
protected:
	bool	ChangeLeader();				// ����Ƿ񻻰���
	void	AddProfferToLeader(int nProffer);

public: // static
	int		GetSynRank();
	OBJID	CreateSubSubSyn(OBJID idFealty,const char  szName[]);
	bool	CreateSubSubSyn(LPCTSTR szName, int nLevel,int nProffer, int nMoney, int nMoneyLeave);
	int		GetSynMemberLevel();
	bool	SetSynMemberLevel(int nLevel);
	void	ResetSynProfferInc();
	void	Betray();
	bool	DetectIsBetrySyn();
	void	IncTimeOnline(unsigned short usTimeInc);

	//---jinggy---2004-12-7---��ð��ɳ�Ա����������ʱ��
	unsigned int GetTimeOnline();

	CSyndicate* QuerySyndicate();
	bool	ChangeSyn(CSyndicate* pSyn, CSyndicate* pTarget);
	bool	KickoutMember(LPCTSTR szTarget);

protected: // data
	CSynAttrData*	m_pData;			//? ����Ϊ0
	int m_nProfferInc;
protected: // ctrl
	PROCESS_ID		m_idProcess;
	CUser*			m_pUser;
	CAutoLink<CSyndicate>	m_linkSyn;

protected: // ctrl
	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_SYNATTR_H__7205A42E_F451_4A87_9BBD_37397D6578E2__INCLUDED_)
