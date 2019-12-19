// MsgTrade.h: interface for the CMsgTrade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGTRADE_H__F3900087_7C9F_4D0D_906A_10E4EB5B5E40__INCLUDED_)
#define AFX_MSGTRADE_H__F3900087_7C9F_4D0D_906A_10E4EB5B5E40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

const unsigned short _TRADE_APPLY			= 1;		// ������		to client/server
const unsigned short _TRADE_QUIT			= 2;		// ȡ������		to server
const unsigned short _TRADE_OPEN			= 3;		// �򿪽��״�	to client
const unsigned short _TRADE_SUCCESS			= 4;		// ���׳ɹ�(ͬʱ�ر�)		to client
const unsigned short _TRADE_FALSE			= 5;		// ����ʧ��(ͬʱ�ر�)		to client
const unsigned short _TRADE_ADDITEM			= 6;		// ����Ʒ		to client/server(�Է��յ�MSGITEMINFO��Ϣ)
const unsigned short _TRADE_ADDMONEY		= 7;		// ��Ǯ			to server
const unsigned short _TRADE_MONEYALL		= 8;		// �Է�Ǯ����	to client(�Է��յ���Ǯ����)
const unsigned short _TRADE_SELFMONEYALL	= 9;		// �Լ�Ǯ��Ǯ	to client(��Ǯ����)
const unsigned short _TRADE_OK				= 10;		// ͬ�⽻��		to client/server
const unsigned short _TRADE_ADDITEMFAIL		= 11;		// ����Ʒʧ��	to client

class CMsgTrade : public CNetMsg   
{
public:
	CMsgTrade();
	virtual ~CMsgTrade();

public:
	BOOL	Create		(unsigned short usAction, OBJID id);

	BOOL	Create		(char* pbufMsg, DWORD dwMsgSize);
	void	Process		(CGameSocket* pSocket);

private:
	typedef struct 
	{
		MSGHEAD_DEFINE

		union{
			OBJID			id;
			DWORD			nData;
		};
		unsigned short	usAction;
	}MSG_Info;
	
	MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGTRADE_H__F3900087_7C9F_4D0D_906A_10E4EB5B5E40__INCLUDED_)
