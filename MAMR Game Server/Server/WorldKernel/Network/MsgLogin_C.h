// MsgLogin.h: interface for the CMsgLogin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGLOGIN_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_C)
#define AFX_MSGLOGIN_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_C

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsgW.h"

class CMsgLogin_C : public world_kernel::CNetMsgW
{
public:
	CMsgLogin_C();
	virtual ~CMsgLogin_C();

	BOOL	Create(OBJID idAccount, DWORD dwCheckData, char* pszName, USHORT usVersion);

public:
	virtual BOOL			Create(char* pbufMsg, DWORD dwMsgSize);
	virtual void			Process		(void *pInfo);

	virtual unsigned short	GetStdSize	(void){return sizeof(MSG_Info);}

//private:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID			idAccount;
		DWORD			dwCheckData;
		unsigned short 	usVersion;
		char			szUserName[_MAX_NAMESIZE];
	}MSG_Info;
	
	MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGLOGIN_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_C)
