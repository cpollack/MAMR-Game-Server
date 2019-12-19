// MsgLogin.h: interface for the CMsgLogin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGLOGIN_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_)
#define AFX_MSGLOGIN_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum {
		MSG_LOGIN_REQUEST=0,
		MSG_LOGIN_OK,
		MSG_LOGIN_ERR_VERSION,
		MSG_LOGIN_ERR_DOUBLELOGIN,
};

#include "NetMsg.h"

class CMsgLogin : public CNetMsg
{
public:
	CMsgLogin();
	virtual ~CMsgLogin();

	BOOL	Create(USHORT usVersion, const char* pszAccount, const char* pszPassword);

public:
	BOOL	Create	(char* pbufMsg, DWORD dwMsgSize);
	void	Process	(void *pInfo);

protected:
	typedef struct {
//�˴��Զ����NPC_ID		DWORD 	usVersion;
		char	szAccount[_MAX_NAMESIZE];
		char	szPassword[_MAX_NAMESIZE];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGLOGIN_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_)
