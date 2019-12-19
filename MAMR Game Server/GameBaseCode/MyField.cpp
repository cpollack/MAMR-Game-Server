
#ifdef	MULTITHREAD_SAFE
	#include <afxmt.h>
	#define	LOCKOBJ		CSingleLock xLock(&m_xCtrl, true)
	#include <winsock2.h>
#else
	#define	LOCKOBJ		
#endif

#include <windows.h>
#include <stdio.h>
#include <assert.h>

#include "mydb.h"
#include "../Common/BaseFunc.h"

// static init
#ifdef	MULTITHREAD_SAFE
	CCriticalSection	CMyField::m_xCtrl;
#endif

MYHEAP_IMPLEMENTATION(CMyField,s_heap)
//////////////////////////////////////////////////////////////////////////////
// Implementation of CMyField

CMyField::CMyField()
{
	// Initialize type and value
	m_ulType = FIELD_TYPE_NULL;
	m_szVal = NULL;
}		//�� δ��ʼ�� m_Field,m_nIndex,m_pMyRecordset,m_nNumAllocsInHeap
		//paled - m_pMyRecordsetΪ��ָָ�룬��OWNER�����ʼ����m_Field��m_nIndexҲ�ǡ�m_szVal�Ŀռ�Ҳ��OWNER����.��

void CMyField::Clear()
{

}

CMyField::~CMyField()
{
	//Clear();
}

//////////////////////////////////////////////////////////////////
//	Operator 

void CMyField::operator = (unsigned char chOp)
{
	if (m_pMyField->m_ulType == FIELD_TYPE_TINY)
		m_pMyField->m_ucVal = chOp;
}

void CMyField::operator = (char chOp)
{
	if (m_pMyField->m_ulType == FIELD_TYPE_TINY)
		m_pMyField->m_cVal = chOp;
}

void CMyField::operator = ( int nOp)
{	
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
			|| m_pMyField->m_ulType == FIELD_TYPE_TINY
			|| m_pMyField->m_ulType == FIELD_TYPE_SHORT
			)
		m_pMyField->m_iVal = nOp;
}

void CMyField::operator = ( long lOp)
{	
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
			|| m_pMyField->m_ulType == FIELD_TYPE_TINY
			|| m_pMyField->m_ulType == FIELD_TYPE_SHORT )
		m_pMyField->m_lVal = lOp;
}

void CMyField::operator = ( float fltOp )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_FLOAT)
		m_pMyField->m_fVal = fltOp;
}

void CMyField::operator = ( double dbOp )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_DOUBLE) 
		m_pMyField->m_dVal = dbOp;
}

void CMyField::operator = ( unsigned long lOp )
{
	if (m_pMyField->m_ulType == FIELD_TYPE_LONG
			|| m_pMyField->m_ulType == FIELD_TYPE_TINY
			|| m_pMyField->m_ulType == FIELD_TYPE_SHORT )
		m_pMyField->m_lVal = lOp;
}


void CMyField::FieldName(char * szFileName)
{	strcpy(szFileName, m_Field.name);
}

unsigned int CMyField::FieldLen() const
{	return m_Field.length;
}

unsigned int CMyField::FieldAttr() const
{	return m_Field.flags;
}


void CMyField::CopyFrom(const char * szField, int nLen)			//�� ��Ӧ�ò������ر���(������ַ���ָ���ѻ�ָ��CMyRecordset)
{	
	try{
		assert(szField != NULL);
		memset(m_szVal,0,nLen);
		strncpy(m_szVal, szField, nLen-1);		//��� û��鳤�ȳ�������ʧ��β0����δ���
	}catch(...){ LogSave("*DATABASE* ERROR: CMyField::CopyFrom() illegal access."); }	//paled debug
}

void CMyField::CopyTo(char * szField, int nLen)			//�� ��Ӧ�ò������ر���(������ַ���ָ���ѻ�ָ��CMyRecordset)
{	
	try{
		assert(szField != NULL);
		memset(szField,0,nLen);
		strncpy(szField, m_szVal, nLen-1);		//��� û��鳤�ȳ�������ʧ��β0����δ���
	}catch(...){ LogSave("*DATABASE* ERROR: CMyField::CopyTo() illegal access."); }	//paled debug
}


#ifdef	EXTERN_C_DEFINE
	void CMyField::operator = (LPCTSTR szVal)
	{	
		try{
			if (m_pMyField->m_ulType == FIELD_TYPE_STRING)		//paled debug
				strcpy(m_pMyField->m_szVal ,szVal);		//��� BUG: ���ȿ����������δ���
		}catch(...){				//paled debug
			LogSave("*DATABASE* ERROR: CMyField::operator char*() illegal access."); 
		}
	}
#else
	void CMyField::operator = (CString strOp)
	{	
		strcpy(m_pMyField->m_szVal, strOp);
	}
#endif

