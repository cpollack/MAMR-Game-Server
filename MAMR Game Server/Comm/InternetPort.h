// �ӿ��ࡣ�ӿڣ�������ϢͨѶ���Ƶ������ͨѶ�ӿڡ�
// �ɽ��ޣ�2002.9.6

#ifndef	INTERNETPORT_H
#define INTERNETPORT_H

#pragma warning(disable:4786)

#define	_WINSOCKAPI_
#include <afxmt.h>
#ifndef FD_SETSIZE
#define	FD_SETSIZE					110	//? ���޸������ӽڵ���
#endif
#include "winsock2.h"
#include "I_MessagePort.h"
#include <list>
#include <vector>
using namespace std;

#include "MessagePort.h"		// ������ͨ�ö��塱


/////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿ����
MSGPORT_BEGIN
#define	CONNECT_OVERTIMESECS		10					// �ͻ���OPEN�ȴ���ʱ����
#define	SOCKET_VERSION				0x0002				// ʹ�õ�WIN SOCKET�汾�š�0x0101��0x0002
#define	SNDBUF_SIZE					(32*1024)			// SOCKETϵͳ�ڲ�SENDBUF�ߴ�

#define	IPSTR_SIZE	16
#define	MAX_KEYSIZE	256

#define	MASTER_PORT_ID				0					// ���ڵ��
#define	MAX_PORT_SIZE				FD_SETSIZE-2			// �����ٽڵ�

enum {	SYS_PACKET_BASE		= MAX_PACKET_ID+1,	// ϵͳ��Ϣ��
		SYS_PACKET_PORTID	= SYS_PACKET_BASE+1,	// �����ڵ㷢���Լ���ID��(����ΪINT)
		SYS_PACKET_PORTSIZE	= SYS_PACKET_BASE+2,	// ���ӽڵ㷢��SIZE(����ΪINT)���ӽڵ�SIZE��ͬʱ�������Լ���SIZE
		SYS_PACKET_LOGINKEY	= SYS_PACKET_BASE+3,	// �����ڵ㷢���Լ���LOGIN_KEY(����ΪSTRING)
};
MSGPORT_END
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
// �ڲ��ṹ
MSGPORT_BEGIN
const int	MSG_HEAD_SIZE		= 6;					// ��Ϣͷ�ĳߴ�
const int	RECV_BUFFER_SIZE	= 16*1024;				// Ӧ�ó����ڲ�BUFFER�ߴ硣
struct	CMessageHead							// ע�⣺�ṹ�ߴ������MSG_HEAD_SIZE��ͬ
{
	unsigned short		m_nPort;				// ��->����TARGET_PORT����->�ӣ�SOURCE_PORT
	unsigned short		m_nPacket;
	unsigned short		m_nVarType;
	char				m_bufData[1];
};
MSGPORT_END
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
class	CInternetPort : private IMessagePort
{
private: // �ڲ�����
	// ����BUFFER
	struct	CRecvBuffer{
	public:
		CRecvBuffer()	{ Reset(); }
		void Reset()	{ m_nMsgLen = 0; }
		bool DelMsg(int nLen){
						if(nLen <= m_nMsgLen){
							if(nLen < m_nMsgLen)
								memcpy(m_bufMsg, m_bufMsg + nLen, m_nMsgLen - nLen);
							m_nMsgLen -= nLen;
							return true;
						}
						m_nMsgLen	= 0;
						return false;
		}
		message_port::CMessageHead* GetHead()	{ return (message_port::CMessageHead*)m_bufMsg; }
		char* GetTail()	{ return m_bufMsg + m_nMsgLen; }
		int	  GetLen()	{ return m_nMsgLen; }
		void  AddLen(int nLen)	{ m_nMsgLen += nLen; }
	protected:
		char		m_bufMsg[message_port::RECV_BUFFER_SIZE];
		int			m_nMsgLen;
	};
public:
	CInternetPort			(int nPort);
	virtual ~CInternetPort	() { ClearPortSet(); }

	IMessagePort*	GetInterface() { return (IMessagePort*)this; }

protected: // Interface
	// ȡ���ӿڵ�ID��
	virtual int		GetSize	() { return m_nPortSize; }
	virtual int		GetID	() { return m_id; }

	// ��ʼ�������ýӿ�ID�ţ���ʼ������Ϣ�����ظ�����(PORT_ID���ܸı�)��
	virtual bool	Open	();
	// �رսӿڣ����ٽ�����Ϣ�����ظ����á��ͻ��˻�ȴ�CONNECT_OVERTIMESECS��
	virtual bool	Close	();

	// ������Ϣ��ָ���ӿڡ�������ϢID���������͡����ݡ�return false: ���Ͳ��ɹ������Ѿ��ر�
	virtual bool	Send	(int nPort, int nPacket, VAR_TYPE nVarType, const void* buf);
	// ����ָ���ӿ�(�����нӿ�)��������Ϣ����ָ����ϢID��Ҳ�ɲ�ָ����VARTYPE�����塣return false: û���յ�����
	virtual bool	Recv	(int nPort, int nPacket, VAR_TYPE nVarType, void* buf, CMessageStatus *pStatus = NULL);

	// �����Ϣջ����û����Ϣ����û����Ϣ��ȴ���return false: ��ʱ�����
	virtual bool	WaitMsg	(int nMilliSec);						// �����ӽӿںźͰ����Ͳ������Եȴ�ĳһ��Ϣ��
//	virtual bool	Broadcast	(int nGroup, int nPacket, int nVarType, DWORD nData);
	virtual bool	IsOpen	() { return m_nState == STATE_OK; }

protected:
	bool	PushMsg		(int nPort, int nPacket, VAR_TYPE nVarType, const void* buf);
	bool	PopMsg		(int *nPort, int *nPacket, VAR_TYPE *nVarType, void* buf);
	bool	SendFrom	(int nPortFrom, int nPort, int nPacket, VAR_TYPE nVarType, const void* buf);
	bool	RecvMsg		(int nMilliSec);
	bool	RecvToBuf	(CRecvBuffer* pBuf, SOCKET sock);					// return false: error
	bool	BufferToList	(int idx);								// return false: ����Ϣ
	static int	SIZE_OF_TYPE		(int type);
	SOCKET	CreateServerSocket		();
	SOCKET	CreateClientSocket		();

	// ��SET�ĺ�������
	bool	Init();			// WSAStartup
	void	Clear();		// WSACleanup

protected:
	int			m_id;
	enum { STATE_OK, STATE_CLOSED, STATE_OPENING };
	int			m_nState;
	typedef	list<message_port::CMessagePacket*>	MSG_SET;
	MSG_SET		m_setMsg;

////////////////////////////////////////////////////////////////////////////////////////
// ���þ�̬����
// ���нӿڵ���ӱ������״�ͨѶǰ��ɡ�ͨѶ�ڼ�ӿڼ������б仯���������ͨѶ�󣬲�����սӿڡ�
// ע�⣺Ŀǰֻ֧�֡���̬���ӿڼ���
public: //static
	bool	InitPortSet(int nPortSize, LPCTSTR pszMasterIP, int nMasterPort);
	void	ClearPortSet();
	/*/ �� 1 ~ N �㲥һ����Ϣ��
	void	BROADCAST1(int nPortFrom, int nPacket, int nVarType, const void* buf)
	{
		for(int i = 1; i < m_nPortSize i++)
		{
			if(i != nPortFrom)
				m_setSocket[i].Send(nPort, nPacket, nVarType, buf);
		}
	}//*/

////////////////////////////////////////////////////////////////////////////////////////
// �½ӿ�
public:
	// release by: delete pMessagePort;
	// (szKey==""): need not key
	static IMessagePort* CreateNew(int nPortID, int nPortSize, LPCTSTR szMasterIP, int nMasterPort, LPCTSTR szKey);

////////////////////////////////////////////////////////////////////////////////////////
protected:
	// �����(���ڵ�)��IP��ַ�Ͷ˿ں�
	int				m_nPortSize;
	char			m_szMasterIP[IPSTR_SIZE];
	int				m_nMasterPort;
	char			m_szKey[MAX_KEYSIZE];

	typedef	vector<SOCKET> PORT_SET;
	PORT_SET		m_setSocket;				// 0~(size-1)Ϊ����SOCKET���Լ�ΪINVALID_SOCKET������ˣ������Ϊ��accept()��SOCKET������֪��ID�Ľӿڡ�(���ڷ����)
	SOCKET			m_sockMain;					// listend()��SOCKET������connect()��SOCKET��

	typedef	vector<CRecvBuffer> BUFFER_SET;
	BUFFER_SET		m_setRecvBuf;				// �����ÿ���ӽڵ�һ��BUF���ͻ���ֻ��1����

	// �����ڿ���windows Startup & Cleanup
	bool			m_bWinStartup;
};



#endif // INTERNETPORT_H














