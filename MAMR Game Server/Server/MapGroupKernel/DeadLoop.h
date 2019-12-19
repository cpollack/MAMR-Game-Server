// ջ
// �ɽ��ޣ�2003.10.24
//////////////////////////////////////////////////////////////////////
// ˵����pop���ɹ�ʱ���󣬲�����0��
//////////////////////////////////////////////////////////////////////


#ifndef	DEADLOOP_H
#define DEADLOOP_H

#include "common.h"
#include "MyStack.h"
#include "Array.h"

template	< TYPENAME T, TYPENAME S >
class CAutoPop
{
public:
	CAutoPop(T& set, const S& obj)		{ m_pSet = &set; m_pSet->push(obj); }
	~CAutoPop()							{ if(m_pSet->size()) m_pSet->pop(); }
protected:
	T*		m_pSet;
};

typedef	CMyStack<const char*>	DEADLOOP;
typedef	Array<DEADLOOP>		DEADLOOP_SET;
extern DEADLOOP_SET	g_setDeadLoop;
inline DEADLOOP_SET&	DeadLoopSet() { return g_setDeadLoop; }

typedef	CAutoPop<DEADLOOP,const char*>		AUTO_POP;

#define	DEADLOOP_CHECK(p,s)	AUTO_POP	xAutoPop(DeadLoopSet()[(p)], (s));
//#define	DEADLOOP_CHECK(p,s)


#endif // DEADLOOP_H
