// MsgItemInfo.h: interface for the CMsgItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_EX)
#define AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_EX

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "../Item.h"

enum {	ITEMINFOEX_NONE=0, 
		ITEMINFOEX_BOOTH,					// for booth
		ITEMINFOEX_EQUIPMENT,				// equipment update
};

class CMsgItemInfoEx : public CNetMsg   
{
public:
	CMsgItemInfoEx();
	virtual ~CMsgItemInfoEx();

	BOOL	Create		(CItem* pItem, OBJID idOwner, int nCost, int nAction = ITEMINFOEX_BOOTH);
	BOOL	Create		(char* pMsgBuf, DWORD dwSize);
	void	Process		(void* pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID		id;
		OBJID		idOwner;
		DWORD		dwPrice;
		DWORD		dwType;
		USHORT		usAmount;
		USHORT		usAmountLimit;
		UCHAR		ucAction;
		UCHAR		ucIdent;
		UCHAR		ucPosition;
		UCHAR		ucGem1;
		UCHAR		ucGem2;
		UCHAR		ucMagic1;
		UCHAR		ucMagic2;
		UCHAR		ucMagic3;
		int			nData;

		DWORD		dwWarGhostExp;	//ս�꾭��ֵ
		DWORD		dwGemAtkType;	//�����౦ʯ������
		DWORD		dwAvailabeTime;	//�����౦ʯ���ô���

		char		szBuf[1];		// ������Ʒ��Ϣ��ʱ�򣬲��������ӵ��ַ���
									// ����Ʒ�ǻ��޵�ʱ�򣬵�һ���ַ������ǻ�������
	}MSG_Info;

	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_EX)
