// ����
// �ɽ��ޣ�2003.5.24
//////////////////////////////////////////////////////////////////////
// ˵����pop���ɹ�ʱ����0��
//////////////////////////////////////////////////////////////////////


#ifndef	MYQUEUE_H
#define MYQUEUE_H

#pragma warning(disable:4786)
#include <deque>
using namespace std;

template	< TYPENAME T >
class CMyQueue
{
public:
	void	push(T obj)					{ m_set.push_back(obj); }
	T		pop()						{ if(size()) { T obj = *m_set.begin(); m_set.pop_front(); return obj; } return 0; }
	int		size()						{ return m_set.size(); }
	void	clear()						{ m_set.clear(); }
//	deque<T>&	QueryList()				{ return m_set; }
protected:
	typedef	deque<T>		QUEUE_SET;
	QUEUE_SET		m_set;
};



#endif // MYQUEUE_H
