// ջ
// �ɽ��ޣ�2003.10.24
//////////////////////////////////////////////////////////////////////
// ˵����pop���ɹ�ʱ����
//////////////////////////////////////////////////////////////////////


#ifndef	MYSTACK_H
#define MYSTACK_H

#include "common.h"

#pragma warning(disable:4786)
#include <vector>
using namespace std;

template	< TYPENAME T >
class CMyStack
{
public:
	void	push(T obj)					{ m_set.push_back(obj); }
	T		pop()						{ IF_OK(size()) { T obj = m_set.back(); m_set.pop_back(); return obj; } return T(); }
	int		size()						{ return m_set.size(); }
	void	clear()						{ m_set.clear(); }
protected:
	typedef	vector<T>	STACK_SET;
	STACK_SET			m_set;
};



#endif // MYSTACK_H
