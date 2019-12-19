// 索引类，用于建立数据表之间的快速查询。加入的KEY不能重复
// 仙剑修，2001.12.18
//////////////////////////////////////////////////////////////////////

#ifndef	TSINGLEMAP2_H
#define TSINGLEMAP2_H

#include "Define.h"
#include "basefunc.h"
#include "logfile.h"
#include "I_mydb.h"
#include "Myheap.h"

#pragma warning(disable:4786)
#include <map>
using namespace std;

template<class T>
class ISingleMap2
{
protected:
	virtual ~ISingleMap2() {}
public:
	typedef	map<OBJID, T*> MAPINDEX;	typedef	typename MAPINDEX::iterator	Iter;
	virtual bool		Create(LPCTSTR szSQL, IDatabase* pDb)	PURE_VIRTUAL_FUNCTION_0
	virtual ULONG		Release()							PURE_VIRTUAL_FUNCTION_0
	virtual Iter		Begin() = 0; //							PURE_VIRTUAL_FUNCTION_0
	virtual Iter		End() = 0; //								PURE_VIRTUAL_FUNCTION_0
	virtual T*			GetObjByIter(Iter i)				PURE_VIRTUAL_FUNCTION_0
	virtual bool		AddObj(T* pObj)						PURE_VIRTUAL_FUNCTION_0
	virtual bool		DelObj(OBJID key)						PURE_VIRTUAL_FUNCTION_0
	virtual T*			GetObj(OBJID key)						PURE_VIRTUAL_FUNCTION_0
//	virtual int			GetAmount()							PURE_VIRTUAL_FUNCTION_0
//	virtual OBJID			Key(iterator Iter)					PURE_VIRTUAL_FUNCTION_0
//	virtual T*			PopObj(OBJID idObj, int idType)		PURE_VIRTUAL_FUNCTION_0		// 用于从OWNER_SET中取出对象，不删除。

//	MYHEAP_DECLARATION(s_heap)
};

template	< class T >
class CSingleMap2 : ISingleMap2<T>
{
protected:
	CSingleMap2(bool bOwner) { m_bOwner = bOwner; }
	virtual ~CSingleMap2();
public:
	static ISingleMap2<T>*	CreateNew(bool bOwner) { return new CSingleMap2<T>(bOwner); }
public:
//	typedef	map<OBJID, T*> MAPINDEX;	typedef	MAPINDEX::iterator	Iter;
	bool		Create(LPCTSTR szSQL, IDatabase* pDb);
	ULONG	Release() { delete this; return 0; }
	Iter	Begin() 										{ return m_map.begin(); }
	Iter	End()											{ return m_map.end(); }
	T*		GetObjByIter(Iter i)							{ return i->second; }
	bool	AddObj(T* pObj);
	bool	DelObj(OBJID key);
	T*		GetObj(OBJID key);
//	int		GetAmount()										{ return m_map.size(); }
///	OBJID		Key(iterator Iter)								{ return Iter->first; }
//	bool	IsIn(OBJID key);
protected:
	bool		m_bOwner;
	MAPINDEX	m_map;
};

template	< class T >
CSingleMap2<T>::~CSingleMap2()
{
	if(m_bOwner && m_map.size())
	{
		for(Iter i = Begin(); i != End(); i++)
			GetObjByIter(i)->ReleaseByOwner();
	}
}

//////////////////////////////////////////////////////////////////////
// 此函数需要数据库支持
template<class T>
bool CSingleMap2<T>::Create(LPCTSTR szSQL, IDatabase* pDb)
{
	CHECKF(szSQL);
	CHECKF(pDb);
	IRecordset* pRes = pDb->CreateNewRecordset(szSQL, false);
	if(!pRes)
		return false;

	for(int i = 0; i < pRes->RecordCount(); i++)
	{
		T* pData = T::CreateNew();
		if(!pData)
		{
			pRes->Release();
			return false;
		}

		if(!pData->Create(pRes))
		{
			pData->ReleaseByOwner();
			pRes->Release();
			return false;
		}

		this->AddObj(pData);

		pRes->MoveNext();
	}

	pRes->Release();
	return true;
}

template	< class T >
bool	CSingleMap2<T>::AddObj(T* pObj)
{
	CHECKF(pObj);
	if(m_bOwner)
	{
		ASSERT(!DelObj(pObj->GetID()));
	}
	m_map[pObj->GetID()] = pObj;
	return true;
}

template	< class T >
bool	CSingleMap2<T>::DelObj(OBJID key)
{
	if(m_bOwner)
	{
		Iter i = m_map.find(key);
		if(i != m_map.end())
		{
			GetObjByIter(i)->ReleaseByOwner();
			m_map.erase(i);
			return true;
		}
		return false;
	}
	else
		return m_map.erase(key) != 0;
}

template	< class T >
T*		CSingleMap2<T>::GetObj(OBJID key)
{
	Iter i;
	if((i=m_map.find(key)) != m_map.end())
		return i->second;

	return NULL;
}

/*template	< class T >
bool	CSingleMap2<T>::IsIn(OBJID key)
{
	return (m_map.find(key) != m_map.end());
}*/


#endif // TSINGLEMAP2_H
