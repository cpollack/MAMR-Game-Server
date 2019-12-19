// typedef.h
// �ɽ��ޣ�2002.10.23
//////////////////////////////////////////////////////////////////////

#ifndef	TYPEDEF_H
#define	TYPEDEF_H

#include "Server/Share/define.h"

#define	BETA		// �ڲ����԰汾

#define	GAME_TITLE			"MAM Server alpha 1.1"


//////////////////////////////////////////////////////////////////////
// ���Ʊ���
const int	THREADDELAY_MS			= 400;			// �ȴ��ڲ���Ϣ�����ʱ��
const int	MAPGROUP_ONTIMER_MS		= 500;			// ��ͼ���̵߳�ONTIMERƵ��
const int	SOCKETKERNEL_ONTIMER_MS	= 1000;			// �����̵߳�ONTIMERƵ��
const int	WORLDKERNEL_ONTIMER_MS	= 1000;			// �����̵߳�ONTIMERƵ��
const int	TIMER_OFFSET_LIMIT		= 10;			// TIMERʱ�������ڸ�ֵʱ���Զ�����
const int	SOCKET_PROCESS_INTERVAL	= 40;	//100;			// SOCKET��ѭ��Ƶ��
const int	CLOSETHREAD_MILLISECS	= 30000;			// �ȴ��̹߳رյĺ�����


//////////////////////////////////////////////////////////////////////
// ���泣��
const int	TEXTWINDOW_SIZE		= 8;			// ��Ϣ������

#define		LOGFILE_DIR				"syslog"
#define		LOGFILE_FILENAME		"syslog\\SZ_SERVER"
#define		ONLINE_FILENAME			"Game server online.txt"


//////////////////////////////////////////////////////////////////////
struct ST_CONFIG{
	int		MAPGROUP_SIZE;					// ��ͼ������
	int		CURRENT_PORTID;
	int		PORT_SIZE;
	char	MASTER_IP[IPSTR_SIZE];
	int		MASTER_PORT;
	char	LOGIN_KEY[256];
};

extern ST_CONFIG	CONFIG;



#endif // TYPEDEF_H