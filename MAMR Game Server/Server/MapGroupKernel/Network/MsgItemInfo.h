// MsgItemInfo.h: interface for the CMsgItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_)
#define AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
//#include "AuctionSystemItemData.h"


enum {	ITEMINFO_NONE=0, 
		ITEMINFO_ADDITEM,				// �����Ʒ
		ITEMINFO_TRADE,					// ��ƽ���׶Է���ӵ���Ʒ
		ITEMINFO_UPDATE,				// update item info
		ITEMINFO_OTHERPLAYER_EQUIPMENT, // �����������װ��// id is user id
		ITEMINFO_AUCTION,               // ����鿴��Ʒ
};

class CItem;
class CMsgItemInfo : public CNetMsg  
{
public:
	CMsgItemInfo();
	virtual ~CMsgItemInfo();

	BOOL	Create		(CItem* pItem, int nAction = ITEMINFO_ADDITEM, OBJID idUser=ID_NONE);
	//BOOL	Create		(CGameAuctionSystemData* pData, int nAction);	
	BOOL	Create		(char* pMsgBuf, DWORD dwSize);
	void	Process		(void* pInfo);
 
protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID		id;
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
		//---jinggy---2004-11-19---begin
		DWORD		dwWarGhostExp; //ս�꾭��ֵ
		DWORD		dwGemAtkType; //�����౦ʯ������
		DWORD		dwAvailabeTime; //�����౦ʯ���ô���
		//---jinggy---2004-11-19---end
		
		char		szBuf[1];		// ������Ʒ��Ϣ��ʱ�򣬲��������ӵ��ַ���
									// ����Ʒ�ǻ��޵�ʱ�򣬵�һ���ַ������ǻ�������
	}MSG_Info;

	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_)
