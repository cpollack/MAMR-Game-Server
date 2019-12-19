// myrecords.h ���ڷֽ��myrecordset.h�еĵ�����¼��
// �ɽ��ޣ�2002.9.12
// �ɽ��� �޸��� 2003.8.26
//////////////////////////////////////////////////////////////////////

#ifndef	MY_CONST_RECORD_H
#define	MY_CONST_RECORD_H

#include "../Common/Array.h"
#include "../Common/VarType.h"

class CCriticalSection;

class CMyConstRecord : public IRecord
{
protected: // interface
	virtual IRecord*	CreateNewRecord(DWORD idNewKey = NEWKEY_NONE);
	virtual	void	Release() { delete this; }

	virtual DWORD	InsertRecord();
	virtual bool	UpdateRecord();
	virtual bool	DeleteRecord();

	virtual int		LoadInt		(LPCTSTR szField);
	virtual void	SetInt		(LPCTSTR szField, int nData);
	virtual UINT	LoadUInt	(LPCTSTR szField)					{ return (UINT)LoadInt(szField); }
	virtual void	SetUInt		(LPCTSTR szField, UINT nData)		{ SetInt(szField, nData); }
	virtual void	LoadString	(char* szData, LPCTSTR szField, int nSize);
	virtual void	SetString	(LPCTSTR szField, LPCTSTR szData, int nSize);

	// ��ģʽ�Ľӿڣ����ڴ���Ӧ�ó����DATA�㡣
	virtual int		GetInt		(int idx);
	virtual LPCTSTR	GetStr		(int idx);
	virtual void	SetInt		(int idx, int nData);
	virtual void	SetStr		(int idx, LPCTSTR szData, int nSize);
	virtual void	ClearUpdateFlags	()							{ ASSERT(!"const"); }

	// ����д�⡣���޹����ͻ���ɲ��ṩ�ýӿ�
	virtual bool	AddInt		(LPCTSTR szField, int nData)		{ ASSERT(!"const"); return false; }

public: // Constructor
	CMyConstRecord(CMyDatabase  * pMyDatabase);
	virtual ~CMyConstRecord();
	bool	Open(CMyRecordset  *pMyRecordset, DWORD idNewKey = NEWKEY_NONE);

public:
#ifdef	MULTITHREAD_SAFE
	static CCriticalSection	m_xCtrl;
#endif
#ifdef	USE_NEW
	static CMyHeap	s_heapString;
#endif
	static CMyConstRecord* CreateNew(CMyDatabase  *pMyDatabase);

public:
	MYHEAP_DECLARATION(s_heap)

protected:
//	Array<String>	m_setName;
	VarTypeSet	m_setField;
};

#endif // MY_CONST_RECORD_H