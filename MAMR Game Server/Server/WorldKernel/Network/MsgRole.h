// MsgRole.h: interface for the CMsgRole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGROLE_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_)
#define AFX_MSGROLE_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsgW.h"

class CMsgRole : public world_kernel::CNetMsgW
{
public:
	CMsgRole();
	virtual ~CMsgRole();

	BOOL	Create(const char* pszNickname, const char* pszName, 
		USHORT usPointLife, USHORT usPointDefence, USHORT usPointAttack, USHORT usPointDexterity, USHORT usPointMana,
		UCHAR ucRole, UCHAR ucFace, DWORD dwRecordMap, const BYTE* pbColorSet);

public:
	BOOL	Create	(char* pbufMsg, DWORD dwMsgSize);
	void	Process	(void *pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		char	szNickname[_MAX_NAMESIZE];
		char	szName[_MAX_NAMESIZE];

		USHORT usPointLife;
		USHORT usPointDefence;
		USHORT usPointAttack;
		USHORT usPointDexterity;
		USHORT usPointMana;

		UCHAR ucRole;
		UCHAR ucFace;

		DWORD dwRecordMap;

		BYTE bColorSet[25];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGROLE_H__63122645_0BCE_11D5_8D37_0010B13A12DB__INCLUDED_)
