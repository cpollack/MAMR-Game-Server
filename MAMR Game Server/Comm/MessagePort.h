// �ӿ��ࡣ�ӿڣ�������ϢͨѶ���Ƶ��̼߳�ͨѶ�ӿڡ�
// �ɽ��ޣ�2002.8.28

#ifndef	MESSAGEPORT_H
#define MESSAGEPORT_H

#pragma warning(disable:4786)

#include <afxmt.h>
#include "winsock2.h"
#include "I_MessagePort.h"
#include "../Common/T_MyQueue.h"
#include <list>
#include <vector>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
// ͨ�ö���
/////////////////////////////////////////////////////////////////////////////////////////////////
MSGPORT_BEGIN
const int	MAX_MSGPACKSIZE = 2048;			// ��Ϣ�����ݵ����ߴ�
struct	CMessagePacket
{
	unsigned int		m_nPortFrom;
	unsigned int		m_nPacket;
	unsigned int		m_nVarType;
	char	m_bufData[MAX_MSGPACKSIZE];
};

#define	CRITSECT	CCriticalSection
#define LOCKOBJ		CSingleLock xLock(&m_xCtrl, true)
#define UNLOCKOBJ	xLock.Unlock()
MSGPORT_END
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
class	CMessagePort : private IMessagePort
{
protected:
	CMessagePort			(int nPort) { LOCKOBJ; m_id = nPort; m_nState = STATE_CLOSED; m_hHaveMsg = NULL; }
	virtual ~CMessagePort	() { Clear(); }

	IMessagePort*	GetInterface() { LOCKOBJ; return (IMessagePort*)this; }

protected: // Interface
	virtual bool	IsOpen	() { LOCKOBJ; return m_nState == STATE_OK; }

	// ȡ���ӿڵ�ID��
	virtual int		GetID	() { LOCKOBJ; return m_id; }
	virtual int		GetSize	() { return m_setPort.size(); }

	// ��ʼ�������ýӿ�ID�ţ���ʼ������Ϣ�����ظ�����(PORT_ID���ܸı�)��
	virtual bool	Open	();
	// �رսӿڣ����ٽ�����Ϣ�����ظ����á�
	virtual bool	Close	();

	// ������Ϣ��ָ���ӿڡ�������ϢID���������͡����ݡ�return false: ���Ͳ��ɹ������Ѿ��ر�
	virtual bool	Send	(int nPort, int nPacket, VAR_TYPE nVarType, const void* buf);
	// ����ָ���ӿ�(�����нӿ�)��������Ϣ����ָ����ϢID��Ҳ�ɲ�ָ����VARTYPE�����塣return false: û���յ�����
	virtual bool	Recv	(int nPort, int nPacket, VAR_TYPE nVarType, void* buf, CMessageStatus *pStatus = NULL);

	// �����Ϣջ����û����Ϣ����û����Ϣ��ȴ���return false: ��ʱ�����
	virtual bool	WaitMsg	(int nMilliSec);						// �����ӽӿںźͰ����Ͳ������Եȴ�ĳһ��Ϣ��
//	virtual bool	Broadcast	(int nGroup, int nPacket, int nVarType, DWORD nData);


protected:	// ������ú�������Ҫ����
	bool		PushMsg		(int nPort, int nPacket, VAR_TYPE nVarType, const void* buf);
private:	// �ڲ�����������Ҫ����
	bool		PopMsg		(int *nPort, int *nPacket, VAR_TYPE *nVarType, void* buf);
	static int	SIZE_OF_TYPE		(int type);

	// ��SET�ĺ�������
	bool		Init();
	void		Clear();

protected:
	int			m_id;
	enum { STATE_OK, STATE_CLOSED };
	int			m_nState;
	typedef	list<message_port::CMessagePacket*>	MSG_SET;			//?? �ɽ��л���
	MSG_SET		m_setMsg;
	CRITSECT	m_xCtrl;								// ����m_setMsg����
	HANDLE		m_hHaveMsg;								// ���¼�ʱΪ��֪ͨ
	int			m_debugPackets;
	CMyQueue<message_port::CMessagePacket*>		m_setRecycle;

////////////////////////////////////////////////////////////////////////////////////////
// ���þ�̬����
// ���нӿڵ���ӱ������״�ͨѶǰ��ɡ�ͨѶ�ڼ�ӿڼ������б仯���������ͨѶ�󣬲�����սӿڡ�
// ע�⣺Ŀǰֻ֧�֡���̬���ӿڼ���(��ò��ֲ�֧���̰߳�ȫ��)
public:
	static bool	InitPortSet(int nPortNum);
	static void	ClearPortSet();
	static IMessagePort*	GetInterface(int nPort) {
					if(nPort>=0&&nPort<m_setPort.size()) return m_setPort[nPort]->GetInterface(); else return NULL;
				}
	static int	GetQueueSize(int nPort)				{
					if(nPort>=0&&nPort<m_setPort.size()) return m_setPort[nPort]->m_setMsg.size(); else return -1;
				}
	/*/ �� 1 ~ N �㲥һ����Ϣ��
	void	BROADCAST1(int nPortFrom, int nPacket, int nVarType, const void* buf)
	{
		for(int i = 1; i < m_setPort.size(); i++)
		{
			if(i != nPortFrom)
				m_setPort[i].Send(nPort, nPacket, nVarType, buf);
		}
	}//*/

protected: //static
	typedef	vector<CMessagePort*> PORT_SET;			// ����̬���������ڼ䲻�޸ġ�
	static PORT_SET		m_setPort;
	static CRITSECT		m_xSetCtrl;					// ����m_setPort����
};


#endif // MESSAGEPORT_H














