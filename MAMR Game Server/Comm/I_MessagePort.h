// �ӿ�����࣬���������ӿ��ࡣ�ӿڣ�������ϢͨѶ���Ƶ��̼߳�ͨѶ�ӿڡ�
// �ɽ��ޣ�2002.8.28

#ifndef	I_MESSAGEPORT_H
#define I_MESSAGEPORT_H

#include <windows.h>
#include "common.h"
#include "LogFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿ����
//#define	LOGERROR	LogError
//void	LogError(const char* szFormat, ...);
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
// ���������ڲ����ռ�
#define MSGPORT_BEGIN	namespace message_port {
#define MSGPORT_END		};


/////////////////////////////////////////////////////////////////////////////////////////////////
#define	MAX_PORT_ID			59999
#define	MAX_PACKET_ID		59999
#define	MAX_MSG_TYPE		59999

/////////////////////////////////////////////////////////////////////////////////////////////////
enum VAR_TYPE {	
		VARTYPE_NONE = MAX_MSG_TYPE+1,			// û��һ���ṹ�ߴ��������ֵ��С�ڸ�ֵ��ʾ�ṹ
		VARTYPE_CHAR, VARTYPE_UCHAR, VARTYPE_SHORT, VARTYPE_USHORT, 
		VARTYPE_LONG, VARTYPE_ULONG, VARTYPE_INT, VARTYPE_UINT, 
		VARTYPE_FLOAT, VARTYPE_DOUBLE };
#define	STRUCT_TYPE(x)							((VAR_TYPE)sizeof(x))
#define	STRING_TYPE(x)							((VAR_TYPE)(strlen(x)+1))
#define	BUFFER_TYPE(x)							((VAR_TYPE)(x))

/////////////////////////////////////////////////////////////////////////////////////////////////
const int	PORT_ANY		= -1;				// ����PORT��Χ��0 - XXX
const int	INVALID_PORT	= MAX_PORT_ID+1;	// ����PORT�����ᷢ��
const int	PACKET_ANY		= -1;				// ����PACKET��Χ��1 - XXX

enum {	STATUS_FLAG_OK			= 0,				// û�д���
		STATUS_FLAG_CLOSE,							// ���������Ͽ����Է����󲻽�����Ϣ��
		STATUS_FLAG_ERROR,							// ���ӷ������������
		STATUS_FLAG_FATAL,							// ��������
};

/////////////////////////////////////////////////////////////////////////////////////////////////
struct	CMessageStatus
{
	int		m_nPortFrom;
	int		m_nPacket;
	VAR_TYPE		m_nVarType;
	int 	m_nError;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
class	IMessagePort
{
public:
	IMessagePort			() {}
	virtual ~IMessagePort	() {}

	virtual bool	IsOpen	() PURE_VIRTUAL_FUNCTION_0;

public:
	// ȡ���ӿڵ�ID��
	virtual int		GetID	() PURE_VIRTUAL_FUNCTION_0;
	// ȡ�ӿ�����
	virtual int		GetSize	() PURE_VIRTUAL_FUNCTION_0;

	// ��ʼ�������ýӿ�ID�ţ���ʼ������Ϣ�����ظ�����(PORT_ID���ܸı�)��
	virtual bool	Open	() PURE_VIRTUAL_FUNCTION_0;
	// �رսӿڣ����ٽ�����Ϣ�����ظ����á�
	virtual bool	Close	() PURE_VIRTUAL_FUNCTION_0;

	// ������Ϣ��ָ���ӿڡ�������ϢID���������͡����ݡ�return false: ���Ͳ��ɹ������Ѿ��ر�
	virtual bool	Send	(int nPort, int nPacket, VAR_TYPE nVarType, const void* buf) PURE_VIRTUAL_FUNCTION_0;
	// ����ָ���ӿ�(�����нӿ�)��������Ϣ����ָ����ϢID��Ҳ�ɲ�ָ����return false: û���յ�����
	virtual bool	Recv	(int nPort, int nPacket, VAR_TYPE nVarType, void* buf, CMessageStatus* pStatus) PURE_VIRTUAL_FUNCTION_0;

	// �����Ϣջ����û����Ϣ����û����Ϣ��ȴ���return false: ��ʱ�����
	virtual bool	WaitMsg	(int nMilliSec = INFINITE) PURE_VIRTUAL_FUNCTION_0;
};


#endif // I_MESSAGEPORT_H

/////////////////////////////////////////////////////////////////////////////////////////////////
// ���ƣ�
//		port		0-59999
//		packet		1-59999
//		msg_len		0-59999












