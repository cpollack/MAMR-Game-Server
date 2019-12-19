// MsgConnect.h: interface for the CMsgConnect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGCONNECT_H__F6692EA5_5D32_4E87_AA3C_4B37A6BE6695__INCLUDED_)
#define AFX_MSGCONNECT_H__F6692EA5_5D32_4E87_AA3C_4B37A6BE6695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsgW.h"

class CMsgConnect : public world_kernel::CNetMsgW  
{
public:
	CMsgConnect();
	virtual ~CMsgConnect();

	BOOL	Create	(OBJID idAccount, DWORD dwData, char* pszInfo);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void* pSocket);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID			idAccount;
		DWORD			dwData;
		char			szInfo[_MAX_NAMESIZE];
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGCONNECT_H__F6692EA5_5D32_4E87_AA3C_4B37A6BE6695__INCLUDED_)
