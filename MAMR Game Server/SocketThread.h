// SocketThread.h: interface for the CSocketThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETTHREAD_H__FB24259F_D321_441C_A6C7_33970E96B6C3__INCLUDED_)
#define AFX_SOCKETTHREAD_H__FB24259F_D321_441C_A6C7_33970E96B6C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Common/ThreadBase.h"
#include "Common/TimeOut.h"

class IMessagePort;
class CSocketThread : public CThreadBase  
{
public:
	CSocketThread(IMessagePort* pPort);
	virtual ~CSocketThread();

public: // overload
	virtual	bool	CreateThread(bool bRun = true);		// false: �ݲ����У��� ResumeThread() ����

/////////////////////////////////////////////////////////////////////
protected:	// ������
	//overrideable
	virtual	void	OnInit();
	virtual bool	OnProcess();		// ����Ҫ����DWORD
	virtual void	OnDestroy();

protected: // ���Ķ��󼰽ӿ�
	CTimeOutMS		m_tProcessSocket;
	clock_t m_tNextClock;
	ISocketKernel*	m_pServerSocket;
	IMessagePort*	m_pMsgPort;

protected: // ctrl
	HANDLE	m_hMutexThread;
};

#endif // !defined(AFX_SOCKETTHREAD_H__FB24259F_D321_441C_A6C7_33970E96B6C3__INCLUDED_)
