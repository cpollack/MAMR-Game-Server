// GameAutoPtr.h: declare for the CAutoPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEAUTOPTR_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
#define AFX_GAMEAUTOPTR_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_

#include "common.h"
#include "basetype.h"

//////////////////////////////////////////////////////////////////////
// ˵����������ָ�룬��֧��COPY��=����ģ����ҪRelease()����֧��
// ע�⣺�����ö����������Ǹ�����COYP��=���ࡣ

template<TYPENAME T>
class CAutoPtr
{
public:
	CAutoPtr() : m_ptr(NULL)					{}
	CAutoPtr(T* ptr) : m_ptr(ptr)				{}		// may be null
	~CAutoPtr()									{ if(m_ptr) m_ptr->Release(); }
	CAutoPtr& operator=(T* ptr)					{ ASSERT(!m_ptr && ptr); m_ptr=ptr; return *this; }
	T*	pop()									{ T* p=m_ptr; m_ptr=NULL; return p; }
private: // can't use these
	CAutoPtr& operator=(const CAutoPtr& ptr);
	CAutoPtr(const CAutoPtr&);

public:
	operator T*()									{ return m_ptr; }
	POINT_NO_RELEASE<T>*	operator->()								{ ASSERT(m_ptr); return static_cast<POINT_NO_RELEASE<T>* >(m_ptr); }
	operator const T*()	 	 const					{ return m_ptr; }
	const POINT_NO_RELEASE<T>*	operator->() const					{ ASSERT(m_ptr); return static_cast<POINT_NO_RELEASE<T>* >(m_ptr); }

protected:
	T*			m_ptr;
};


//////////////////////////////////////////////////////////////////////
// ˵��������JAVA���󣬲�֧��COPY��=����ģ����ҪCreateNew()��Release()����֧��
// ע�⣺�����ö����������Ǹ�����COYP��=���ࡣ

template<TYPENAME T>
class CJavaObj
{
public:
	CJavaObj() : m_ptr(NULL)					{}
	~CJavaObj()									{ if(m_ptr) m_ptr->Release(); }
private: // can't use these
	CJavaObj& operator=(const CJavaObj& ptr);
	CJavaObj(const CJavaObj&);

public:
	operator T*()									{ if(!m_ptr) m_ptr=T::CreateNew(); ASSERT(m_ptr); return m_ptr; }
	T*	operator->()								{ if(!m_ptr) m_ptr=T::CreateNew(); ASSERT(m_ptr); return m_ptr; }

protected:
	T*			m_ptr;
};


/*/////////////////////////////////////////////////////////////////////
// ˵����������ָ�룬����ʱ���Զ�ɾ�����󡣸�ģ����Ҫnew��delete��COPY����֧��

template<TYPENAME T>
class AutoPtr
{
public:
	AutoPtr() : m_ptr(NULL)							{}
	AutoPtr(const AutoPtr& obj)						{ m_ptr=new T; *m_ptr=*obj.m_ptr; }
	~AutoPtr()										{ delete m_ptr; }
	AutoPtr& operator=(const AutoPtr& obj)			{ if(!m_ptr) m_ptr=new T; if(this!=&obj) *m_ptr=*obj.m_ptr; return *this; }
	AutoPtr& operator=(const T& obj)				{ if(!m_ptr) m_ptr=new T; *m_ptr=obj; return *this; }

public:
	operator T*()									{ return m_ptr; }
	T*	operator->()								{ ASSERT(m_ptr); return m_ptr; }

protected:
	T*			m_ptr;
};*/



#endif // !defined(AFX_GAMEAUTOPTR_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
