// MsgPlayerTask.h: interface for the CMsgPlayerTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGPLAYERTASK_H__AAB8131E_45ED_4198_A946_E8716C9CF6B1__INCLUDED_)
#define AFX_MSGPLAYERTASK_H__AAB8131E_45ED_4198_A946_E8716C9CF6B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "NetStringPacker.h"

enum {
	_WANT_PK		= 0,	// ����PK
	_WANT_ITEM		= 1,	// ������Ʒ
	_WANT_EUDEMON	= 2,	// ���ͻ���
};

const int _MAX_PRIZE = 5;

struct ST_PLAYERTASK_ITEM {
	union {
		OBJID	idItem;				// ��ƷID		// to server��ʱ��
		struct {									// to client��ʱ��
			OBJID	idItemType;		// ��Ʒ����
			USHORT	usDurability;	// �;�
			UCHAR	ucAddition;		// ׷�� // ���޳ɳ�
			UCHAR	ucDegree;		// �ȼ� // ���޵ȼ�
		};
	};
};

class CMercenaryTaskData;
class CMsgPlayerTask : public CNetMsg  
{
public:
	CMsgPlayerTask();
	virtual ~CMsgPlayerTask();

	BOOL	Create(char* pbufMsg, DWORD dwMsgSize);

	BOOL	Create	(CMercenaryTaskData* pData);
	void	Process	(void *pInfo);

protected:
	typedef struct
	{
		MSGHEAD_DEFINE;

		DWORD dwMoney;			// ����
		
		OBJID idTask;
		// �������Ʒ ��Ҫ��Ʒ�ĸ�������
		DWORD dwDurability;		// �;� 
		UCHAR ucAddition;		// ׷�� // ���޳ɳ�
		UCHAR ucDegree;			// �ȼ� // ���޵ȼ�

		UCHAR ucType;			// ��������
		UCHAR ucRankReq;		// ��Ҫ��Ӷ���ȼ�
		
		ST_PLAYERTASK_ITEM	infoItem[_MAX_PRIZE];	// ��Ʒ��Ϣ -- dwItemType = ID_NONE��ʾ����û��
		
		char szBuf[1];	//to client ����title ������ϸ���� ����ɱ�˻���Ʒ����
						//to server ����title ������ϸ���� ����ɱ�˻���Ʒ����
	}MSG_Info;
	
	MSG_Info*	m_pInfo;
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGPLAYERTASK_H__AAB8131E_45ED_4198_A946_E8716C9CF6B1__INCLUDED_)
