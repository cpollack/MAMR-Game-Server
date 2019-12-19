// TimeOut.h: interface for the CTimeOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEOUT_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_)
#define AFX_TIMEOUT_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>
#include "BaseFunc.h"

//////////////////////////////////////////////////////////////////////
// ��ʱ�࣬�ԡ��롱Ϊ��λ
template<int I>
class CTimeOut_
{
public:
	CTimeOut_(int nIntervalSecs = I) { m_nInterval = nIntervalSecs; m_tUpdateTime = 0; }		// =0 : ���������ʼ��
//	virtual ~CTimeOut_() {}

public:
	// ����ʱ���ǩ
	void	Update		()						{ m_tUpdateTime = (clock()/1000); }
	// ����Ƿ�ʱ
	bool	IsTimeOut	()						{ return (clock()/1000) >= m_tUpdateTime+m_nInterval; }
	// ���ڶ�ʱ����������ʱ�ӡ�ÿ�δ���ʱΪtrue��
	bool	ToNextTime	()						{ if(IsTimeOut()) return Update(),true; else return false; }
	// ��ʼ��ʱ��Ƭ��(��������)
	void	SetInterval	(int nSecs)				{ m_nInterval = nSecs; }

	// ��ʼ����ʱ��(ͬSetInterval)
	void	Startup		(int nSecs)				{ m_nInterval = nSecs; Update(); }
	// ʱ���Ƿ񴥷�(ֻ����һ��)����Startup���ʹ�ã���ʵ��ֻ����һ�ε�ʱ�ӡ�
	bool	TimeOver	()						{ if(IsActive() && IsTimeOut()) return Clear(),true; return false; }
	void	Clear		()						{ m_nInterval = m_tUpdateTime = 0; }
	bool	IsActive	()						{ return m_tUpdateTime != 0; }
	void	IncInterval	(int nSecs, int nLimit)	{ m_nInterval = ::CutOverflow(m_nInterval+nSecs, nLimit); }
	void	DecInterval	(int nSecs)				{ m_nInterval = ::CutTrail(m_nInterval-nSecs, 0); }

	// ����Ƿ�ʱ��ָ��ʱ��Ƭ������ͬһʱ���ǩ�������ͬ��ʱ�¼���(��ʵ��һ��������ƶ��ʱ��)
	bool	IsTimeOut	(int nSecs)				{ return (clock()/1000) >= m_tUpdateTime+nSecs; }
	// ���ڱ䳤�ĳ�ʱ�¼���
	bool	ToNextTime	(int nSecs)				{ if(IsTimeOut(nSecs)) return Update(),true; else return false; }
	// ʱ���Ƿ񴥷�(ֻ����һ��)����Startup���ʹ�ã���ʵ��ֻ����һ�ε�ʱ�ӡ�
	bool	TimeOver	(int nSecs)					{ if(IsActive() && IsTimeOut(nSecs)) return Clear(),true; return false; }
	// ʱ�ӻ���ۣ�������ֵ���������ֵ������ͬToNextTime(...)
	bool	ToNextTick	(int nSecs);
//	void	AppendInterval	(int nSecs)			{ if(ToNextTime()) m_nInterval=nSecs; else m_nInterval+=nSecs; }	// ToNextTime(): ��֤������nSecs��

public: // get
	int		GetRemain()							{ return m_tUpdateTime ? ::CutRange<int>(m_nInterval - ((clock()/1000)-(int)m_tUpdateTime), 0, m_nInterval) : 0; }
	int		GetInterval()						{ return m_nInterval; }

protected:
	int		m_nInterval;
	time_t	m_tUpdateTime;
};
typedef	CTimeOut_<0>	CTimeOut;

//////////////////////////////////////////////////////////////////////
// ��ʱ�࣬�ԡ����롱Ϊ��λ
template<int I>
class CTimeOutMS_
{
public:
	CTimeOutMS_(int nIntervalSecs = I) { m_nInterval = nIntervalSecs; m_tUpdateTime = 0; }		// =0 : ���������ʼ��
//	virtual ~CTimeOutMS_() {}

public:
	void	Update		()						{ m_tUpdateTime = clock(); }
	bool	IsTimeOut	()						{ return clock() >= m_tUpdateTime+m_nInterval; }
	bool	ToNextTime	()						{ if(IsTimeOut()) return Update(),true; else return false; }
	void	SetInterval	(int nMilliSecs)		{ m_nInterval = nMilliSecs; }

	void	Startup		(int nMilliSecs)		{ m_nInterval = nMilliSecs; Update(); }
	bool	TimeOver	()						{ if(IsActive() && IsTimeOut()) return Clear(),true; return false; }
	void	Clear		()						{ m_nInterval = m_tUpdateTime = 0; }
	bool	IsActive	()						{ return m_tUpdateTime != 0; }
	void	IncInterval	(int nMilliSecs, int nLimit)		{ m_nInterval = ::CutOverflow(m_nInterval+nMilliSecs, nLimit); }
	void	DecInterval	(int nMilliSecs)		{ m_nInterval = ::CutTrail(m_nInterval-nMilliSecs, 0); }

	bool	IsTimeOut	(int nMilliSecs)		{ return clock() >= m_tUpdateTime+nMilliSecs; }
	bool	ToNextTime	(int nMilliSecs)		{ if(IsTimeOut(nMilliSecs)) return Update(),true; else return false; }
	bool	TimeOver	(int nMilliSecs)		{ if(IsActive() && IsTimeOut(nMilliSecs)) return Clear(),true; return false; }
	bool	ToNextTick	(int nMilliSecs);
//	void	AppendInterval	(int nMilliSecs)	{ if(ToNextTime()) m_nInterval=nMilliSecs; else m_nInterval+=nMilliSecs; }	// ToNextTime(): ��֤������nSecs��

public: // get
	int		GetRemain()							{ return m_tUpdateTime ? ::CutRange(m_nInterval - (int)(clock()-(int)m_tUpdateTime), 0, m_nInterval) : 0; }
	int		GetInterval()						{ return m_nInterval; }

protected:
	int		m_nInterval;
	clock_t	m_tUpdateTime;
};
typedef	CTimeOutMS_<0>	CTimeOutMS;

#endif // !defined(AFX_TIMEOUT_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_)
