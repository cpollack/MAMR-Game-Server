// ClientSocket.h
// paled, 2002.6.2

// ��������SOCKET���ӵĿͻ���һ�������������ڿͻ��˳���Ҳ��������С��Ϸ�������������ݷ�������
// ʹ�÷�������ʽʵ�֡�

#ifndef	CLIENTSOCKET_H
#define	CLIENTSOCKET_H

#include <winsock2.h>
#include "typedef.h"
#include "EncryptClient.h"

const int	RECV_BUFFER_SIZE	= 2048;			// Ӧ�ó����Լ���BUF
const int	SEND_BUFFER_SIZE	= 4048;			// Ӧ�ó����Լ���BUF

////////////////////////////////////////////////////////////////////////////////////////////
#include "common.h"				// ���ú�����


// SOCKET�ĳ�ʼ�����ս�(ע��ֻ�пͻ��˳������Ҫ�������������������ServerSocket.h�е�������������)
// ����Ѿ�ʹ����MFC��WINSOCK��ʼ�����룬��Ҫ��ʹ��������������
// ʵ�ַ�ʽΪ����ʼ�������WINSOCKET2.0���DLL��					// WINSOCK1.1
bool	ClientSocketInit();			// �൱��WSAStartup()
bool	ClientSocketFinal();		// �൱��WSACleanup()

class	CClientSocket
{
public:
	// GetPacketLen:	����ָ�룬��ȡ����Ϣ���ĳ��ȡ�
	// nSndBuf:	ϵͳ����BUFFER�ĳ��ȡ�(ע������ָӦ�ó����BUFFER)
	// nRcvBuf:	ϵͳ����BUFFER�ĳ��ȡ�(ע������ָӦ�ó����BUFFER)
	CClientSocket();		// =0 : ʹ��ϵͳ��ȱʡֵ��
public:
	// ���ӵ�CServerSocket
	// szName:		������������IP��ַ
	// nPort:		�������˿ں�
	// nBlockSecs:	�������õ�����
	// return:		���ӳɹ�ʱ����true���������������ʱ����false���ڶ������ظ������Լ���Ƿ����ӳɹ���
	bool		Open(const char* szName, int nPort, int nBlockSecs = 0, int nSndBuf = 0, int nRcvBuf = 0);
	bool		Open(int nBlockSecs = 0);		// ���������״ε���

	// ȡһ����Ϣ����������Ϣ�򷵻�NULL��pBufSize�������ݳ��ȡ�
	LPCTSTR		GetPacket(int *pBufSize, bool bFromNet = true);

	// ������Ϣ�����BUF�е����ݡ�
	bool		ClearPacket(int nPacketSize);

	// �ر�SOCKET�����ظ����á�
	void		Close();

public:
	// ��һ����Ϣ����Ӧ�ó����BUFFER(��ϵͳBUFFER)
	// return false: SOCKET�ѶϿ�, ��Flush()����δ���(bFlushΪtrueʱ)��
	bool		SendPacket(const char* pack, int nLen, bool bFlush = false);

	// ����BUFFER�е�������Ϣ��
	// Ӧ�ú���Ӧ��֤��ʱ���ô˽ӿڣ��Է���BUFFER�е����ݡ�
	bool		Flush();				// return false : no empty

public:
	// ���������Ƿ�����(�Ƿ�ɷ�������)��ͨ�����ڼ�������Ƿ���ɡ�
	bool		IsOpen();

// �ڲ����� /////////////////////////////////////////////////////////////////////
protected:
	IPSTR		m_szIP;
	int			m_nPort;
	int			m_nSndSize;
	int			m_nRcvSize;

	SOCKET		m_sock;
	char		m_bufMsg[RECV_BUFFER_SIZE];
	int			m_nLen;
	char		m_bufSendMsg[SEND_BUFFER_SIZE];
	int			m_nSendLen;

	enum { STATE_CLOSED = 0, STATE_CONNECT, STATE_OPEN, };
	int			m_nState;
//#ifdef	ENCRYPT
public:
	void	ChangeCode(DWORD dwData) { m_cSendEncrypt.ChangeCode(dwData); }
protected:
	// ���ܶ���
	typedef	CEncryptClient<0x20, 0xFD, 0x07, 0x1F, 0x7A, 0xCF, 0xE5, 0x3F>	ENCRYPTCLIENT;
	ENCRYPTCLIENT	m_cSendEncrypt, m_cRecvEncrypt;
//#endif	// ENCRYPT
};


#endif // CLIENTSOCKET_H




