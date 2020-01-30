// MsgAction.h: interface for the CMsgAction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
#define AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

 
class CMsgDirection : public CNetMsg  
{
public:
	CMsgDirection();
	virtual ~CMsgDirection();

	BOOL	Create	(OBJID idPlayer, int nPosX, int nPosY, USHORT usDir);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void *pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID		idUser;
		USHORT		unPosX, unPosY;
		DWORD		dwDir;
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
