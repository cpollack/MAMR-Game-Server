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
		ITEMINFO_ADDITEM = 3003,			
		ITEMINFO_EQUIPITEM = 3004,
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

		DWORD dwAction;
		OBJID idPlayer;
		NAMESTR szName;
		NAMESTR szInventor;

		OBJID id;
		DWORD dwCost;
		WORD wLook;
		WORD wSort;

		DWORD dwLevelReq;
		WORD wLife;
		WORD wPower;
		WORD wAttack;
		WORD wDefence;
		WORD wDexterity;

		WORD w1;
		WORD w2;
		WORD w3;
		WORD w4;

		WORD zero; //spacer

		DWORD d1;
		DWORD d2;
		DWORD d3;
		DWORD d4;
	}MSG_Info;

	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGITEMINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_)
