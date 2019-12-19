// MsgAuction.h: interface for the CMsgAuction class.
// ����ϵͳ��Ϣ�����    ��LW-   2004-11-26
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGAUCTION_H__1F99F42A_5E1E_4147_93DF_221F682C9E26__INCLUDED_)
#define AFX_MSGAUCTION_H__1F99F42A_5E1E_4147_93DF_221F682C9E26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "NetStringPacker.h"
enum{
	AUCTION_ADD = 0,//to server//����������Ʒ ������idItem
	AUCTION_BID ,//to server//��Ҿ������ ������idItem  dwValue
	AUCTION_NEW ,//to client//��ʼ�µ����� ������idUser idItem  dwValue
	AUCTION_HINT_USER,//to client �㲥��Ҿ���м� ������idUser dwValue
//	AUCTION_HINT, //to client���㲥���ֽм�dwDataΪ�ڼ��νУ�ǰ���Σ�������dwData idItem dwValue
    AUCTION_HAMMER,//to client���㲥���ֽм�dwDataΪ�ڼ��νУ����γɽ�������idUser,idItem,dwValue��
	AUCTION_ITEM_INFO,//to server idItem����ʱͨ��CMsgItemInfo��Ϣ����
//	AUCTION_SYS,      //to client �㲥������ϵͳ���򣬲���������ٷ���������Ʒ
};
class CMsgAuction  : public CNetMsg
{
public:
	CMsgAuction();
	virtual ~CMsgAuction();
	BOOL	Create	(/*OBJID idUser*/char* szName ,OBJID idItem,DWORD dwValue,int nAction);
	BOOL	Create	(OBJID dwData,int dwValue,int nAction);
public:	
	BOOL	Create		(char* pbufMsg, DWORD dwMsgSize);
	void	Process		(void* pInfo);

//protected:
	typedef struct {
		MSGHEAD_DEFINE
		OBJID       idNpc;       //����NPC��id
		OBJID		idItem;
		int         nAuction;
		int         dwValue;
			union{
			char        szName[1]; //�䳤
			OBJID       dwData;
		};
	}MSG_Info;
    CNetStringPacker m_StrPacker;
	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGAUCTION_H__1F99F42A_5E1E_4147_93DF_221F682C9E26__INCLUDED_)
