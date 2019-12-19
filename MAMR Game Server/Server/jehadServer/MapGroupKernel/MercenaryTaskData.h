// MercenaryTaskData.h: interface for the CMercenaryTaskData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERCENARYTASKDATA_H__10522F05_A91D_4979_9240_BE2EDE9DFEBB__INCLUDED_)
#define AFX_MERCENARYTASKDATA_H__10522F05_A91D_4979_9240_BE2EDE9DFEBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include "define.h"
#include "GameData.h"
#include "GameObj.h"
#include "MyHeap.h"
#include "MsgPlayerTask.h"
#include <vector>

// Ӷ����������

enum MTASKDATA {
	MTASKDATA_ID_	= 0,				// ����ID
	MTASKDATA_TYPE,						// ��������
	MTASKDATA_USER_ID,					// ����������ID
	MTASKDATA_USER_NAME,				// ��������������
	MTASKDATA_TITLE,					// �������
	MTASKDATA_DETAIL,					// ������ϸ˵��
	MTASKDATA_TARGET_NAME,				// Ŀ�����֣�Ŀ����Ʒ���֡���������(��ʵҲ����Ʒ)��Ŀ����������
	MTASKDATA_DURA,						// ��Ҫ�;ö�
	MTASKDATA_ADDITION,					// ��Ҫ׷�� / ���޳ɳ�
	MTASKDATA_DEGREE,					// ��Ҫ�ȼ� / ���޵ȼ�
	MTASKDATA_PRIZE_MONEY,				// ����
	MTASKDATA_PRIZE_ITEMID0,			// ��Ʒ0 ~ 4
	MTASKDATA_PRIZE_ITEMID1,
	MTASKDATA_PRIZE_ITEMID2,
	MTASKDATA_PRIZE_ITEMID3,
	MTASKDATA_PRIZE_ITEMID4,
	MTASKDATA_RANK_REQ,					// ������Ҫ��Ӷ���ȼ�
	MTASKDATA_ACCEPT_USERID,			// ��������ID
	MTASKDATA_ACCEPT_TIME,				// ������ʱ��
	MTASKDATA_RESULT_ITEMID,			// ���������Ʒ
	MTASKDATA_STATE,					// ����״̬
};

enum MTASKSTATE {
	MTASKSTATE_NONE	= 0,				//
	MTASKSTATE_ACCEPTED,				// �����Ѿ�����
	MTASKSTATE_FINISHED,				// ��������ɣ�����û��ȡ��Ʒ������Ҫ������ɱ�˵�����
	MTASKSTATE_COMPLETED,				// �����Ѿ���ȫ����
	MTASKSTATE_CANCELED,				// �����Ѿ���ȡ��
	MTASKSTATE_CLOSED,					// �����Ѿ��رա�����������ɲ��ҷ���������Ҳȡ����Ҫ����Ʒ��
};

struct ST_MTASK_DATA {
	OBJID		idTask;					// ����ID
	OBJID		idUser;					// ����������ID
	NAMESTR		szUserName;				// ��������������
	char		szTitle[32];			// �������
	char		szDetail[128];			// ������ϸ����
	NAMESTR		szTargetName;			// ����Ŀ������(�����������Ʒ����������)

	UCHAR		ucType;					// ��������

	UCHAR		ucAddition;				// ��Ҫ׷�� / ���޳ɳ�
	UCHAR		ucDegree;				// ��Ҫ�ȼ� / ���޵ȼ�
	UCHAR		ucRankReq;				// ��ҪӶ���ȼ�
	DWORD		dwDura;					// ��Ҫ�;ö�

	OBJID		idAcceptUser;			// ��������ID
	DWORD		dwAcceptTime;			// ������ʱ��
	OBJID		idResultItem;			// ���������ƷID
	UCHAR		ucTaskState;			// ����״̬
	
	DWORD		dwPrizeMoney;				// ����
	OBJID		idPrizeItems[_MAX_PRIZE];	// ��Ʒ
};
//////////////////////////////////////////////////////////////////////
char	szMercenaryTaskTable[];
typedef CGameData<MTASKDATA, szMercenaryTaskTable, szID>		CGameMTaskData;

//////////////////////////////////////////////////////////////////////
class IDatabase;
class CItem;
class CMercenaryTaskData  : public CGameObj
{
public:
	CMercenaryTaskData();
	virtual ~CMercenaryTaskData();

	static CMercenaryTaskData* CreateNew()		{ return new CMercenaryTaskData; }
	ULONG	Release()				{ delete this; return 0; }
	ULONG	ReleaseByOwner()		{ delete this; return 0; }

public:
	bool	Create		(OBJID idTask, IDatabase* pDb);
	bool	Create		(IRecordset* pRes, IDatabase* pDb);

	bool	CreateRecord(const ST_MTASK_DATA* pInfo, IDatabase* pDb);
	bool	DeleteRecord();
	
public:
//	bool	IsFinished	()				{ return (GetInt(MTASKDATA_RESULT_ITEMID) != ID_NONE); }
//	bool	IsAccepted	()				{ return (GetInt(MTASKDATA_ACCEPT_USERID) != ID_NONE); }

public:	// get&set
	OBJID	GetID()			{ return m_pData->GetKey(); }

	int		GetInt(MTASKDATA idx)		{ return m_pData->GetInt(idx); }
	LPCTSTR	GetStr(MTASKDATA idx)		{ return m_pData->GetStr(idx); }
	void	SetInt(MTASKDATA idx, int nData, bool bUpdate = false)					{ m_pData->SetInt(idx, nData); if (bUpdate) m_pData->Update(); }
	void	SetStr(MTASKDATA idx, LPCTSTR szData, int nSize, bool bUpdate = false)	{ m_pData->SetStr(idx, szData, nSize); if (bUpdate) m_pData->Update(); }
	
	CItem*	GetItem(OBJID idItem);
	CItem*	PopItem(OBJID idItem);
	CItem*	GetItemByIndex(int nIndex);

	bool	AddResultItem(CItem* pItem, bool bUpdate = true);
	CItem*	GetResultItem()		{ return m_pResultItem; }
	CItem*	PopResultItem()		{ CItem* pItem = m_pResultItem; m_pResultItem = NULL; return pItem; }

protected:
	bool	LoadItems(IDatabase* pDb);

protected:
	CGameMTaskData*	m_pData;

	CItem*		m_pResultItem;
	typedef std::vector<CItem*>		ITEM_SET;
	ITEM_SET	m_setPrizeItem;

	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_MERCENARYTASKDATA_H__10522F05_A91D_4979_9240_BE2EDE9DFEBB__INCLUDED_)
