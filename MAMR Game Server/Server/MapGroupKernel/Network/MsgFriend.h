// MsgFriend.h: interface for the CMsgGoodFriend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGFRIEND_H__DC85CF8B_3B54_4C8D_94EA_F68172C0A179__INCLUDED_)
#define AFX_MSGFRIEND_H__DC85CF8B_3B54_4C8D_94EA_F68172C0A179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// include head file(s) hrere...
#include "NetMsg.h"

// define constant(s) here...
const int _FRIEND_APPLY			= 10;
const int _FRIEND_ACCEPT		= 11;
const int _FRIEND_ONLINE		= 12;
const int _FRIEND_OFFLINE		= 13;
const int _FRIEND_BREAK			= 14;
const int _FRIEND_GETINFO		= 15;
const int _ENEMY_ONLINE			= 16;			// to client // ���µ�����״̬ 
const int _ENEMY_OFFLINE		= 17;			// to client // ���µ�����״̬ 
const int _ENEMY_DEL			= 18;			// to server // to client // ɾ��һ������ 
const int _ENEMY_ADD			= 19;			// to client // ���һ������ 

MAPGROUPKERNEL_BEGIN
class CMsgFriend : public CNetMsg
{
public:
	CMsgFriend();
	virtual ~CMsgFriend();

	enum { OFFLINE_STATUS, ONLINE_STATUS };
	BOOL	Create	(int nAction, OBJID idFriend, LPCTSTR szName, bool bOnline = false, DWORD nLookFace=0, int nLevel=0);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void* pInfo);

private:
	typedef struct
	{
		MSGHEAD_DEFINE

		OBJID			idFriend;	
		DWORD			dwLookFace;
		unsigned char	ucAction;
		unsigned char	ucOnlineFlag;
		unsigned char	ucLevel;
		union{
			char			szName[_MAX_NAMESIZE];				//@ ���Ż���ֻ�޸�����״̬ʱ�����������ݡ�
			OBJID			idTransmit;				// use for transmit
		};
	}MSG_Info;

	MSG_Info*	m_pInfo;
};
MAPGROUPKERNEL_END

#endif // !defined(AFX_MSGFRIEND_H__DC85CF8B_3B54_4C8D_94EA_F68172C0A179__INCLUDED_)
