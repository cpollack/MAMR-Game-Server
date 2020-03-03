// MapGroupThread.cpp: implementation of the CMapGroupThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comm/MessagePort.h"
#include "MsgServer.h"
#include "Server/Share/I_Shell.h"
#include "MapGroupThread.h"
#include "Server/Share/protocol.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapGroupThread::CMapGroupThread(IMessagePort* pPort)
{
	ASSERT(pPort);
	m_pMsgPort		= pPort;
	m_pMapGroup		= NULL;
	m_tNextClock	= 0;

	m_hMutexThread	= NULL;
}

CMapGroupThread::~CMapGroupThread()
{
}

//////////////////////////////////////////////////////////////////////
// overload
//////////////////////////////////////////////////////////////////////
bool CMapGroupThread::CreateThread(bool bRun /*= true*/)
{
#ifdef	DEBUG_MULTITHREAD
	m_hMutexThread    =::CreateMutex(NULL, false, "FW_DEBUG_MULTITHREAD");
	if(!m_hMutexThread)
	{
		LOGERROR("Create mutex handle failed!");
		return false;
	}
#endif
	if(!CThreadBase::CreateThread(bRun))
		return false;

	m_pMapGroup	= IMapGroup::CreateNew();
	return m_pMapGroup->Create(m_pMsgPort);
}

//////////////////////////////////////////////////////////////////////
void CMapGroupThread::OnDestroy()
{ 
	if(m_pMapGroup)
		m_pMapGroup->Release();
	m_pMapGroup = NULL;

#ifdef	DEBUG_MULTITHREAD
	if(m_hMutexThread)
	{
		::CloseHandle(m_hMutexThread);
		m_hMutexThread = NULL;
	}
#endif
}

//////////////////////////////////////////////////////////////////////
void CMapGroupThread::OnInit()	
{ 
	m_pMapGroup->Init();

	m_tNextClock = clock() + CLOCKS_PER_SEC; 

	char	szText[1024];
	sprintf(szText, "#%u: map group kernel thread running��", m_pMsgPort->GetID());
	m_pMsgPort->Send(MSGPORT_SHELL, SHELL_PRINTTEXT, STRING_TYPE(szText), szText);


	m_pMapGroup->SynchroData();
}

//////////////////////////////////////////////////////////////////////
bool CMapGroupThread::OnProcess()
{
#ifdef	DEBUG_MULTITHREAD
	if(::WaitForSingleObject(m_hMutexThread, INFINITE) == WAIT_ABANDONED)
		return false;
#endif
	char	buf[MAX_MESSAGESIZE];
	CMessageStatus	cStatus;
	clock_t	clkStart = clock();

	DEBUG_TRY	// VVVVVVVVVVVVVV
	if(m_pMsgPort->Recv(PORT_ANY, PACKET_ANY, STRUCT_TYPE(buf), buf, &cStatus))
	{
		if(!m_pMapGroup->ProcessMsg(cStatus.m_nPacket, buf, cStatus.m_nVarType, cStatus.m_nPortFrom))
		{
			LOGERROR("m_pMapGroup->ProcessMsg�ڲ���Ϣ����");
//			return false;
		}
	}
	DEBUG_CATCH("CMapGroupThread::OnProcess()")	// AAAAAAAAAAA

	clock_t	tCurr = clock();
	clock_t clkTimerUsed = 0;
	if(tCurr >= m_tNextClock)
	{
		m_tNextClock	+= MAPGROUP_ONTIMER_MS;

		// �Զ�����
		{
			int nOffset	= (tCurr - m_tNextClock) / CLOCKS_PER_SEC;
			if(abs(nOffset) > TIMER_OFFSET_LIMIT)
			{
				m_tNextClock = tCurr + MAPGROUP_ONTIMER_MS;
				LOGWARNING("CMapGroupThread::OnProcess() ʱ��ƫ��%d�룬���Զ�������", nOffset);
			}
		}

		clock_t clkTimerStart = clock();
		DEBUG_TRY
		m_pMapGroup->OnTimer(tCurr);
		DEBUG_CATCH("m_pMapGroup->OnTimer()")
		clkTimerUsed = clock() - clkTimerStart;
	}

#ifdef	DEBUG_MULTITHREAD
	::ReleaseMutex(m_hMutexThread);
#endif
//	Sleep(0);
	{
		// stat
		clock_t	 clkUsed	= clock() - clkStart;
		extern struct STAT_STRUCT	g_stat;
		int idx = m_pMsgPort->GetID() - MSGPORT_MAPGROUP_FIRST;
		if(idx >= 0 && idx < STAT_MAX_MAPGROUP)
		{
			InterlockedExchangeAdd(&g_stat.setMapGroupTimerMS[idx], clkTimerUsed);
			InterlockedExchangeAdd(&g_stat.setAllMapGroupMS[idx], clkUsed);
			InterlockedIncrement(&g_stat.setMapGroupTimes[idx]);
			if(g_stat.setMaxMapGroupMS[idx] < clkUsed)
			{
				g_stat.setMaxMapGroupMS[idx] = clkUsed;
				if(cStatus.m_nPacket == KERNEL_CLIENTMSG || cStatus.m_nPacket == KERNEL_NPCMSG)
					g_stat.nPacketID	= *((long*)buf + 1);
				else
					g_stat.nPacketID	= -1*cStatus.m_nPacket;
			}
		}
	}
	DEBUG_TRY	// VVVVVVVVVVVVVV
	m_pMsgPort->WaitMsg(__min(THREADDELAY_MS, MAPGROUP_ONTIMER_MS));		// ��Ӧ���ر��߳���Ϣ����Ƶ��
	DEBUG_CATCH("CMapGroupThread::OnProcess(2)")	// AAAAAAAAAAA

	return true;
}



