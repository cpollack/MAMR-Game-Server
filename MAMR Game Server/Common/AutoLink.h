// �Զ�������
// �ɽ���, 2003.7.7
////////////////////////////////////////////////////////////////
// ˵��:����AutoLink������Ҫ�ø������ָ���ʼ���Լ���Init()������Ϊ�ա�
//		����AutoLink����ʹ�ø�ֵ�ķ�ʽ��������LINK��(ע�⣺��ò�Ҫ����̫�����ʱ���󣬷������һ������)
//		����AutoLink���ڲ���ָ�������ʱ������AutoLink����գ�����ÿ��ʹ�á���AutoLink��ʱ�����ȼ���Ƿ�Ϊ�ա�(!)
//		��AutoLink��������Clear()��ն��󡣡���AutoLink����ͬʱ���������������AutoLink��ֻ�������ɾ���Լ���
////////////////////////////////////////////////////////////////
//		���������ʵ��һ��������CAutoLink<T>& QueryLink(const CAutoLink<T>&)�����ء���AutoLink�������á�(����ֻ�����ͣ�������)


#ifndef	AUTO_LINK_H
#define	AUTO_LINK_H

#include "common.h"
#include "basetype.h"

////////////////////////////////////////////////////////////////
template<TYPENAME T>
class	CAutoLink;
template<TYPENAME T>
class	CAutoLink
{
public:
	CAutoLink()										{ Init(); }
	~CAutoLink()									{ Break(); }
	CAutoLink(const CAutoLink<T>& link)				{ Init(); Insert(&const_cast<CAutoLink<T>&>(link)); }
	CAutoLink(T* ptr)						{ Init(); Insert(&ptr->QueryLink(CAutoLink<T>())); }
	CAutoLink&	operator=(const CAutoLink<T>& link)	{ Break(); Insert(&const_cast<CAutoLink<T>&>(link)); return *this; }
	CAutoLink&	operator=(T* ptr)					{ Break(); Insert(&ptr->QueryLink(CAutoLink<T>())); return *this; }
	void	Init(T* pOwner)							{ ASSERT(!IsValid() && pOwner); m_pOwner=pOwner; }
	void	Clear()									{ Break(); }

public: // const
	operator T*()			const					{ return m_pOwner; }
	POINT_NO_RELEASE<T>*		operator->()	const					{ ASSERT(IsValid()); return static_cast<POINT_NO_RELEASE<T>* >(m_pOwner); }

public: // modify

protected:
	void	Init();
	void	Insert(CAutoLink<T>* pPrev);		// insert to next, only for !IsMaster
	void	Erase();							// erase from list, only for !IsMaster
	void	Break();
	bool	IsValid()		const					{ return m_pOwner != NULL; }
	bool	IsMaster()		const					{ return IsValid() && m_pPrev == NULL; }

protected:
	T*				m_pOwner;
	CAutoLink<T>*	m_pPrev;
	CAutoLink<T>*	m_pNext;
};

////////////////////////////////////////////////////////////////
template<TYPENAME T>
inline void CAutoLink<T>::Init()						// Init all
{
	m_pOwner	= NULL;
	m_pPrev		= NULL;
	m_pNext		= NULL;
}

////////////////////////////////////////////////////////////////
template<TYPENAME T>
void CAutoLink<T>::Break()
{
	if(IsMaster())		// master
	{
		CAutoLink<T>* pNext = m_pNext;
		int	nCount=0;
		while(pNext)
		{
			CAutoLink<T>* pCurr = pNext;
			pNext	= pNext->m_pNext;			// ++

			ASSERT(pCurr->IsValid());
			pCurr->Init();

			DEAD_LOOP_BREAK(nCount, 100)
		}

		Init();
	}
	else
	{
		Erase();
	}
}

////////////////////////////////////////////////////////////////
template<TYPENAME T>
void CAutoLink<T>::Insert(CAutoLink<T>* pPrev)		// insert to next
{
	CHECK(pPrev);
	CHECK(pPrev != this);
	CHECK(!IsMaster());
	Erase();

	this->m_pOwner			= pPrev->m_pOwner;
	if(IsValid())
	{
		this->m_pPrev			= pPrev;
		this->m_pNext			= pPrev->m_pNext;
		if(pPrev->m_pNext)
			pPrev->m_pNext->m_pPrev	= this;
		pPrev->m_pNext			= this;
	}
}

////////////////////////////////////////////////////////////////
template<TYPENAME T>
void CAutoLink<T>::Erase()						// erase from list
{
	if(IsValid())
	{
		CHECK(!IsMaster());

		m_pPrev->m_pNext	= this->m_pNext;
		if(m_pNext)
			m_pNext->m_pPrev	= this->m_pPrev;

		Init();
	}
}


#endif // AUTO_LINK_H
