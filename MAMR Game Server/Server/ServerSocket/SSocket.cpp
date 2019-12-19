// ServerSocket.cpp
// paled, 2002.6.3

#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */

#define FD_SETSIZE      2048				// �������2000���ͻ��˵�¼
#include <winsock2.h>
#include <windows.h>
#include <assert.h>
#include "EncryptServer.h"
#include "SSocket.h"
#include "define.h"

#define ENCRYPT

/////////////////////////////////////////////////////////////////////////////////////////
// ȫ�ֺ���
/////////////////////////////////////////////////////////////////////////////////////////
bool	ServerSocketInit()
{
	// ��ʼ������
	WSADATA		wsaData;
	int ret = WSAStartup(0x0002, &wsaData);
	if(ret!=0)
	{
		LOGERROR("ERROR: Init WSAStartup() failed.");
		return false;
	}

	// ���汾
	if(LOBYTE(wsaData.wVersion) != 0x02 || HIBYTE(wsaData.wVersion) != 0x00)
	{
		LOGERROR("ERROR: WSAStartup Version not match 2.0");
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool	ServerSocketFinal()
{
	WSACleanup();
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////
// class	CListenSocket
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
// nSndBuf��nRcvBufָSOCKETϵͳ�Ļ�����
CListenSocket::CListenSocket()
{
	m_sock = INVALID_SOCKET;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool		CListenSocket::Listen(int nPort, int nSndBuf /*= 0*/, int nRcvBuf /*= 0*/)		// 0Ϊȱʡֵ
{
	if(m_sock != INVALID_SOCKET)
	{
		Close();
		m_sock = INVALID_SOCKET;
	}

	// �������׽���
	SOCKADDR_IN		sin;
	m_sock=socket(AF_INET, SOCK_STREAM, 0);
	if(m_sock==INVALID_SOCKET)
	{
		LOGERROR("ERROR: Init socket() failed.");
		return false;
	}

	// ����SOCKETΪKEEPALIVE
	int		optval=1;
	if(setsockopt(m_sock, SOL_SOCKET, SO_KEEPALIVE, (char *) &optval, sizeof(optval)))
	{
		closesocket(m_sock);
		LOGERROR("setsockopt() set SO_KEEPALIVE failed.");
		return false;
	}

	// ����SENDBUG
			optval = nSndBuf;
	if(nSndBuf && setsockopt(m_sock, SOL_SOCKET, SO_SNDBUF, (char *) &optval, sizeof(optval)))
	{
		int err = WSAGetLastError();
		LOGERROR("setsockopt() set SO_SNDBUF failed[%d].", err);
		Close();
		return false;
	}

	// ����RECVBUG
			optval = nRcvBuf;
	if(nRcvBuf && setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (char *) &optval, sizeof(optval)))
	{
		int err = WSAGetLastError();
		LOGERROR("setsockopt() set SO_RCVBUF failed[%d].", err);
		Close();
		return false;
	}

	// ����SOCKETΪ���ظ�ʹ��
	if(setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval)))
	{
		closesocket(m_sock);
		LOGERROR("ERROR: Init setsockopt() failed.");
		return false;
	}

	// ��
	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=0;
	sin.sin_port=htons(nPort);
	if(bind(m_sock, (LPSOCKADDR) &sin, sizeof(sin)))
	{
		closesocket(m_sock);
		LOGERROR("ERROR: Init bind() failed.");
		return false;
	}

	// ����Ϊ��������ʽ
	unsigned long	i = 1;
	if(ioctlsocket(m_sock, FIONBIO, &i))
	{
		closesocket(m_sock);
		LOGERROR("ERROR: Init ioctlsocket() failed.");
		return false;
	}

	// keep_alive

	// �����˿�
	if(listen(m_sock, 5))//SOMAXCONN))
	{
		closesocket(m_sock);
		LOGERROR("ERROR: Init listen() failed.");
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
SOCKET		CListenSocket::Accept()
{
	fd_set	readmask;
	FD_ZERO(&readmask);
	FD_SET(m_sock, &readmask);

	struct timeval	timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	if(select(FD_SETSIZE, &readmask, (fd_set *) 0, (fd_set *) 0, &timeout) > 0)
	{
		if(FD_ISSET(m_sock, &readmask))
		{
			struct sockaddr_in	addr;
			int	   len = sizeof(addr);
			SOCKET newsock = accept(m_sock, (sockaddr *) &addr, (int *) &len);

			if(newsock == INVALID_SOCKET)
				LOGERROR("ERROR: accept() failed.");
			else
				return newsock;
		}
	}
	return INVALID_SOCKET;
}

/////////////////////////////////////////////////////////////////////////////////////////
void		CListenSocket::Close()
{
	if(m_sock != INVALID_SOCKET)
	{
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
// class	CServerSocket
/////////////////////////////////////////////////////////////////////////////////////////
const char* CServerSocket::GetPacket(int* pLen, BOOL bFromNet /*= true*/)
{
	CHECKF(pLen);

	*pLen = 0;

	if(bFromNet && m_sock != INVALID_SOCKET && m_nLen < RECV_BUFFER_SIZE)
	{
		int ret = recv(m_sock, m_bufMsg + m_nLen, RECV_BUFFER_SIZE - m_nLen, 0);
		if(ret > 0)
		{
#ifdef	ENCRYPT
				// ���ܹ���
				m_cEncryptRecv.Encrypt((unsigned char *)m_bufMsg + m_nLen, ret);
#endif
			m_nLen += ret;
		}
		else if(ret == 0)
		{
			LOGDEBUG("DEBUG���ͻ��������ر�SOCKET��");
			Close();
		}
		else if(ret < 0)
		{
			int err = WSAGetLastError();
			if(err != WSAEWOULDBLOCK)
			{
				LOGDEBUG("DEBUG�������쳣��SOCKET����");
				Close(true);
			}
		}
	}

	*pLen	= m_nLen;
	return m_bufMsg;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool CServerSocket::ClearPacket	(int nLen)
{
	ASSERT(nLen <= m_nLen);

	if(m_nLen - nLen > 0)
		memcpy(m_bufMsg, m_bufMsg + nLen, m_nLen - nLen);

	m_nLen	-= nLen;
	if(m_nLen < 0)
	{
		m_nLen = 0;
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool CServerSocket::IsOpen()
{
	if(m_sock == INVALID_SOCKET)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CServerSocket::Close(BOOL bNoLinger /*= false*/)
{
	if(m_sock != INVALID_SOCKET)
	{
		LOGDEBUG("DEBUG��SOCKET�ر��С�");
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
		LOGDEBUG("DEBUG��SOCKET�ر��ˡ�");
		//? bNoLinger��δʹ��
	}
//	m_nLen = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
DWORD	CServerSocket::GetPeerIP()
{
	// ȡ�Է�IP
	sockaddr_in	inAddr;
	memset(&inAddr, 0, sizeof(inAddr));
	int		nLen = sizeof(inAddr);
	if(getpeername(m_sock, (sockaddr *)&inAddr, &nLen))
	{
		int err = WSAGetLastError();
		LOGERROR("ERROR: getpeername()����.");
		Close(true);
		return NULL;
	}

	return	inAddr.sin_addr.S_un.S_addr;
}

/////////////////////////////////////////////////////////////////////////////////////////
int	CServerSocket::SetBufSize(int nSndBuf, int nRcvBuf)
{
	// ����SENDBUG
	int		optval = nSndBuf;
	if(nSndBuf && setsockopt(m_sock, SOL_SOCKET, SO_SNDBUF, (char *) &optval, sizeof(optval)))
	{
		int err = WSAGetLastError();
		LOGERROR("setsockopt() set SO_SNDBUF failed[%d].", err);
		Close();
		return false;
	}

	// ����RECVBUG
			optval = nRcvBuf;
	if(nRcvBuf && setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (char *) &optval, sizeof(optval)))
	{
		int err = WSAGetLastError();
		LOGERROR("setsockopt() set SO_RCVBUF failed[%d].", err);
		Close();
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
// static 
CServerSocket* CServerSocket::CreateNew(SOCKET sock)
{
	CServerSocket* pSocket = ::new CServerSocket(sock);

#ifdef	ENCRYPT
		pSocket->m_cEncryptSend.Init();
		pSocket->m_cEncryptRecv.Init();
#endif
	return	pSocket;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CServerSocket::Destroy(CServerSocket* pSocket)
{
	::delete	pSocket;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool CServerSocket::SendPacket(const char* pack, int nLen)
{
	OBJID idPack = *((unsigned short*)pack+1);
#ifdef	ENCRYPT		
		// ���ܹ���
		char	buf[MAX_PACKETSIZE];
		memcpy(buf, pack, nLen);
		pack = buf;		//? �滻��������ֵ
		m_cEncryptSend.Encrypt((unsigned char *)pack, nLen);
#endif
	int ret = send(m_sock, pack, nLen, 0);
	if(ret == nLen)
	{
		return true;
	}
	else
	{
//		LOGMSG("SNDBUF�����SOCKET�ر�![%d]", idPack);
		Close(true);
		return false;
	}
}




