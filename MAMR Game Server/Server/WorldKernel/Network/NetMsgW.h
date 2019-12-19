// NetMsg.h: interface for the CNetMsg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _NETMSG_H
#define _NETMSG_H

/////////////////////////////////////////////////////////////////////////////////////////////////
// ���������ڲ����ռ�
#define WORLDKERNEL_BEGIN	namespace world_kernel {
#define WORLDKERNEL_END		};

/////////////////////////////////////////////////////////////////////////////////////////////////
#pragma	warning(disable:4786)
#include "basefunc.h"
#include "NetworkDef.h"
#include "define.h"

//////////////////////////////////////////////////////////////////////
WORLDKERNEL_BEGIN
class CNetMsgW;
class ISocket
{
public:
	virtual bool SendMsg			(CNetMsgW* pNetMsg)				PURE_VIRTUAL_FUNCTION_0
	virtual bool SendMsg			(SOCKET_ID idSocket, OBJID idMsg, const char* pBuf, int nMsgLen)	PURE_VIRTUAL_FUNCTION_0
	virtual bool SendNpcMsg			(OBJID idNpc, OBJID idMsg, const char* pBuf, int nMsgLen)			PURE_VIRTUAL_FUNCTION_0
	// ����֪ͨSOCKET�ر�
	virtual bool CloseSocket		(SOCKET_ID idSocket)			PURE_VIRTUAL_FUNCTION_0
};

class CNetMsgW
{
public:
	CNetMsgW();
	virtual ~CNetMsgW();

	void	Init(void);
	void	Reset(void)	{Init();}

	bool	IsNpcMsg()			{return m_idSocket == SOCKET_NONE;}
	SOCKET_ID	GetSocketID()	{return m_idSocket;}
	OBJID		GetNpcID()		{return m_idNpc;}
	OBJID	GetType	(void)		{return m_unMsgType;}
	int		GetSize	(void)		{return m_unMsgSize;}

	char*	GetBuf(void)	{return m_bufMsg;}

public:	
	virtual BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	virtual BOOL			IsValid		(void);
//	virtual void			Send		(ISocket* pSocket);
	virtual void			Process		(void *pInfo);
	virtual bool			SendMsg		(CNetMsgW* pMsg);

public:
	static int	GetMaxSize	(void)		{return _MAX_MSGSIZE;}

	static CNetMsgW*	CreateClientMsg	(PROCESS_ID idProcess, SOCKET_ID idSocket, OBJID idMsg, 
										const char* pbufMsg, DWORD dwMsgSize, int nTrans);
	static CNetMsgW*	CreateNpcMsg	(PROCESS_ID idProcess, OBJID idNpc, OBJID idMsg, 
										const char* pbufMsg, DWORD dwMsgSize, int nTrans);
	static CNetMsgW*	CreateMsg	(OBJID idMsg, const char* pbufMsg, DWORD dwMsgSize);

public:
	void	AppendInfo(PROCESS_ID idProcess, SOCKET_ID idSocket, OBJID idNpc)	// ����CUser,CUserManager�е�SendMsg����
			{ m_idProcess = idProcess; m_idSocket = idSocket; m_idNpc = idNpc; }

protected:
	OBJID		m_unMsgType;
	int			m_unMsgSize;
	char		m_bufMsg[_MAX_MSGSIZE];

	PROCESS_ID	m_idProcess;
	SOCKET_ID	m_idSocket;
	OBJID		m_idNpc;

public: // trans intra message
	void		SetTransData(int nData)				{ m_nTransData = nData; }
	int			GetTransData()						{ return m_nTransData; }
protected:
	int			m_nTransData;
};
WORLDKERNEL_END

#endif 
