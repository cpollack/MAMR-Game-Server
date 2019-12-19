// NPC���������̰߳�
// �ɽ��ޣ�2002.12.2



#ifndef	TYPEDEF_HEADFILE_H
#define	TYPEDEF_HEADFILE_H

#include <limits.h>

/////////////////////////////////////////////////////////////////////////////////////
#define	NPCSERVER_TITLE				"JehadNpcServer beta 1.17"

#define	LOGFILE_DIRECTION			"syslog"
#define	LOGFILE_FILENAME			"syslog\\NpcServer"

/////////////////////////////////////////////////////////////////////////////////////
// DIALOG���Ƴ���
const int	MAX_TEXTLINESIZE		= 500;
const DWORD	END_OF_TEXT				= INT_MAX;
const int	SAVESTATEWIN_SECS		= 5*60;				// ÿ5���Ӹ���һ�ν���
const int	UPDATESTATEWIN_SECS		= 10;				// ÿ5���Ӹ���һ�ν���



const int	CONNECT_DELAY_MS		= 900;
const int	SYSTEM_ONTIMER_MS		= 500;		// ONTIMER���
const int	TIMER_OFFSET_LIMIT		= 10;		// 



/////////////////////////////////////////////////////////////////////////////////////
// ���Ķ���
/////////////////////////////////////////////////////////////////////////////////////
typedef		unsigned long			OBJID;
const OBJID	ID_NONE					= 0;

const int	IPSTR_SIZE				= 16;
typedef		char					IPSTR[IPSTR_SIZE];

const int	MAX_PACKETSIZE			= 1024;			// ������Ϣ���ߴ�



#endif // TYPEDEF_HEADFILE_H