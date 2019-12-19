// ��ȫָ��ģ��
// �ɽ��ޣ�2001.12.15


#ifndef	T_SAFEPTR
#define T_SAFEPTR

#pragma warning(disable:4786)
#include "common.h"

/*
#define	LogSave	printf		//sys	
#define LF	"\n"					// 
#define SHOWINC	printf("[+%d+]", m_nCount)		// 
#define SHOWDEC printf("[-%d-]", m_nCount)		// 
//*/
//*else
//#define	LogSave	printf		//sys	
#define LF	// "\n"					
#define SHOWINC	// printf("[+%d+]", m_nCount)		
#define SHOWDEC // printf("[-%d-]", m_nCount)		
//*/


//////////////////////////////////////////////////////////////////////////////////////////////////
template < class T, unsigned long MYID >
class	TSafePtr
{
public:
	TSafePtr() { m_ptr = NULL; m_nCount++; SHOWINC; }
	TSafePtr(T * ptr) { 
		if(ptr != m_pDefault)	m_ptr = ptr; else m_ptr = NULL;		//? �����塣����Ϊm_pDefault
		m_nCount++; SHOWINC; 
	}		//? δ�������Ƿ���Ч
	TSafePtr(T & ref) {
		if(ref.m_ptr != m_pDefault)	m_ptr = ref.m_ptr; else m_ptr = NULL;		//? �����塣����Ϊm_pDefault
		m_nCount++; SHOWINC; 
	}
	~TSafePtr() { 
		m_nCount--; SHOWDEC; 
		if(!m_nCount && m_pDefault){ 
#ifdef	SAFEPTR_COMSTYLE
			m_pDefault->ReleaseByOwner();
#else
			delete m_pDefault; 
#endif
			m_pDefault = NULL; } 
	}
public:
//	T & operator =(T * ptr) { m_ptr = ptr; }		//? δ�������Ƿ���Ч
	operator T * () { Valid(); return m_ptr; }		//? Ϊ��֤NULLָ��������ȷ����ת��Ϊȱʡ����
	operator == (T * ptr) { Valid(); return (m_ptr == ptr); }
	T * operator ->() { if(Valid(false)) return m_ptr; else return Default(); }
private:
	bool	Valid(bool bEnableNull = true);		// ͨ�������ָ��
	T *		Default();
protected:
	T *	m_ptr;
	static T *	m_pDefault;
	static int	m_nCount;		// TSafePtr����ĸ���
};

/////////////////////////////////////////////////////////////////////////////////
template < class T, unsigned long MYID >
T * TSafePtr<T, MYID>::m_pDefault = NULL;

template < class T, unsigned long MYID >
int	TSafePtr<T, MYID>::m_nCount = 0;

/////////////////////////////////////////////////////////////////////////////////
// ���ָ������Ч�ԣ�������Чָ��(β������)��ΪNULL��
template < class T, unsigned long MYID >
bool	TSafePtr<T, MYID>::Valid(bool bEnableNull /*= true*/)
{
	if(bEnableNull && !m_ptr)
		return true;

	if(m_ptr)
	{
		try{
			unsigned long nID = m_ptr->GetObjType();			//??? ֱ��ʹ�ú��������Ǵ�ģ������д��ݡ�
			if(nID == MYID)
				return true;		// ��������
			else
			{
				LOGERROR("ERROR: TSafePointer<%d>::operator->() type dismatch to %d." LF, MYID, nID);
				ASSERT(!"TSafePtr");
			}
		}catch(...){
			m_ptr = NULL;
			LOGERROR("CATCH ERROR: TSafePointer<%d>::operator->() can't access object. follow access." LF, MYID);
			ASSERT(!"TSafePtr");
		}
	}
	else
	{
		LOGERROR("ERROR: TSafePointer<%d>::operator->() null pointer access.uninitial pointer." LF, MYID);
		ASSERT(!"TSafePtr");
	}

	return false;
}

template < class T, unsigned long MYID >
T *		TSafePtr<T, MYID>::Default()
{
	// ������
	try
	{
#ifdef	SAFEPTR_COMSTYLE
			m_pDefault->ReleaseByOwner();
#else
		delete m_pDefault;			//??? ֱ��ʹ�ú��������Ǵ�ģ������д��ݡ�
#endif
	}catch(...){
		LOGERROR("CATCH ERROR: TSafePointer<%d>::operator->() can't access default object." LF, MYID);
		ASSERT(!"TSafePtr");
//?????			m_nCount = 0;
	}

#ifdef	SAFEPTR_COMSTYLE
			m_pDefault = T::CreateNew();
#else
	m_pDefault = new T;
#endif

	return m_pDefault;
}


#endif	// T_SAFEPTR
