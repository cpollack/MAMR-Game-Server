// define.h ȫ�����ͺͳ�������
// �ɽ��ޣ�2002.10.29
//////////////////////////////////////////////////////////////////////

#ifndef	ALL_GLOBAL_DEFINE_H
#define	ALL_GLOBAL_DEFINE_H

#pragma warning(disable:4786)

#include "common.h"
#include "myDDstring.h"
#include "Myheap.h"

//////////////////////////////////////////////////////////////////////
// �汾��
const int	GAME_VERSION	= 108;		// ���汾�ţ��ͻ��˺ͷ���������ͬ���������С�
const int	SERVER_VERSION	= 107;		// �������汾�ţ�SERVERÿ�θ���ʱ���ɸ��ģ�������ʾ��
const int	NPCSERVER_VERSION	= 987654321;	// NPC������������汾��
const int	NPCSERVER_VERSION_RELOGIN	= 987654322;	// NPC������������汾��

#define MAPGROUPKERNEL_BEGIN	namespace mapgroup_kernel {
#define MAPGROUPKERNEL_END		};
MAPGROUPKERNEL_BEGIN
MAPGROUPKERNEL_END

#define		NEW_LOGOUT		// for new logout plan

//////////////////////////////////////////////////////////////////////
// NPC�������ʺ�
#define		NPCSERVER_ACCOUNT 		"NpcServer Tqdig"			// NPC��������¼��
#define		NPCSERVER_PASSWORD		"skl8934##VJICW "			// NPC����������

//////////////////////////////////////////////////////////////////////
// �ʺŷ�������س���
const int	LOGIN_FREE_LEVEL	= 16;			// �㿨�շѵĵȼ���С�ڸ�ֵ���շѡ�
#define	FLAG_ISP_TO_NORMAL	"!ISP�Ʒ�ʧ��!"		// ע�⣺���ַ�����������Ϸ��������ƥ�䡣ÿ��IP��һ���ʺš������Զ�ת��ͨ�ʺŲ���ʾ
#define	FLAG_NO_POINT		"!NO_POINT!"		// ע�⣺���ַ�����������Ϸ��������ƥ�䡣û�е���Ҳ�ɵ�¼������Ϸ�������ж���ҵȼ��Ƿ�������

//////////////////////////////////////////////////////////////////////
// ͨ�ó���
const int	IPSTR_SIZE			= 16;				// IP���ռ�
const int	_MAX_NAMESIZE		= 16;
const int	MAX_FIELDSIZE		= 256;				// �洮���ֶεĿռ��С��mysql �Ĵ������ֶ���󳤶�+1
const int	MAX_PARAMSIZE		= 256;				// action param space
const int	MAX_TENETSIZE		= 256;				// announce

#define		SYSTEM_NAME 		"SYSTEM"			// �㲥��Ϣʱ����ϵͳ�������ִ�
#define		ALLUSERS_NAME		"ALLUSERS"			// TALK�д�����ҡ������ִ�
#define		REPLAY_OK_STR		"ANSWER_OK"			// �������ʺŻ�LOGINʱ���صĳɹ���־����
#define		REPLAY_AGAIN_STR	"ANSWER_AGAIN"		// NPC_SERVER LOGINʱ���ص��ظ���¼��־����

//////////////////////////////////////////////////////////////////////
// ����
#define	CONFIG_FILENAME		"shell.ini"
const int	DBSTR_SIZE				= 16;			// ���ݿ�INI������
const int	MAX_PACKETSIZE			= 1024;			// ������Ϣ���ߴ�
const int	MAX_MESSAGESIZE			= MAX_PACKETSIZE + 24;			// �ڲ���Ϣ���ߴ�
//const int	SERVER_LISTEN_PORT = 5816;			// �����������˿�
const int	SERVER_LISTEN_PORT		= 9525;			// �����������˿�
const int	POINTFEE_SECS			= 3*60;			// �Ƶ�Ƶ��
const int	POINTFEE_DELAY_SECS		= 10;			// �״μƵ���ʱ
const int	SOCKET_SENDBUFSIZE		= 64*1024;			// SOCKET_BUF
const int	SOCKET_NPCBUFSIZE		= 128*1024;			// SOCKET_BUF
const int	SOCKET_ACCOUNTBUFSIZE	= 32*1024;			// SOCKET_BUF
const int	MAX_MAPGROUPSIZE		= 10;				// ���10����ͼ��

//////////////////////////////////////////////////////////////////////
// ����
typedef	unsigned long	OBJID;
typedef	unsigned long	PROCESS_ID;						// ͨ�����ڲ���Ϣ�ӿ�ID��ͬ
typedef	long			SOCKET_ID;						// ��Ҷ�Ӧ��SOCKET_ID��ͨ��ΪSET��������
#define	IPP_OF(x)		((void**)&(x))
typedef unsigned __int64	I64;

typedef	char			NAMESTR[_MAX_NAMESIZE];
typedef	char			SQLBUF[1024];
typedef	char			MSGBUF[1024];
typedef	char			MESSAGESTR[MAX_MESSAGESIZE];
typedef	char			PARAMBUF[MAX_PARAMSIZE];
typedef	char			TENETSTR[MAX_TENETSIZE];

//////////////////////////////////////////////////////////////////////
// �ӿڳ���
const int	GAMESERVER_INTERPORT	= 0;			// ��Ϸ����������ӿ�(���ӿ�)

enum{
		MSGPORT_SHELL			= 0,			// �Ի���ӿ�
		MSGPORT_SOCKET			= 1,			// �ײ�ͨѶ�ӿ�
		MSGPORT_WORLD			= 2,			// �ڲ����ӿ�(ȫ�ֽ���)
		MSGPORT_MAPGROUP_FIRST	= 3,			// ��һ����ͼ��ӿ�
};

//////////////////////////////////////////////////////////////////////
// ���ĳ���
const int	ID_NONE			= 0;
const int	SOCKET_NONE		= -1;				// ��Ч��SOCKET����
const int	PROCESS_NONE	= -1;				// ��Ч��PROCESS����
const int	INVALID_ROOMID	= -1;				// ��Ч��ROOM_ID
const int	BCAST_NPCID		= 0;				// ����NPC�������Ĺ㲥����NPC������ת�������NPC��
const int	INDEX_NONE		= -1;

const bool	UPDATE_TRUE				= true;
const bool	UPDATE_FALSE			= false;
const bool	DELRECORD_TRUE			= true;
const bool	DELRECORD_FALSE			= false;
const bool  INCLUDE_SELF			= true;
const bool  EXCLUDE_SELF			= false;
enum {SYNCHRO_FALSE=false, SYNCHRO_TRUE=true, SYNCHRO_BROADCAST};

//////////////////////////////////////////////////////////////////////
// �������
#define	MSGHEAD_DEFINE
			//USHORT		unMsgSize;
			//USHORT		unMsgType;

//////////////////////////////////////////////////////////////////////
// ID�ռ�
const OBJID	SCENEID_FIRST		= 000001;			// SCENE�ĵ�һ��ID
const OBJID	SYSNPCID_FIRST		= 00001;			// SYSNPC�ĵ�һ��ID			// fixed to database id
const OBJID	SYSNPCID_LAST		= 99999;			// SYSNPC�����һ��ID		// fixed to database id
const OBJID	DYNANPCID_FIRST		= 100001;			// DYNANPC�ĵ�һ��ID
const OBJID	DYNANPCID_LAST		= 199999;			// DYNANPC�����һ��ID
const OBJID	SCENEID_LAST		= 299999;			// SCENE�����һ��ID

const OBJID	NPCSERVERID_FIRST	= 400001;			// NPC�ĵ�һ��ID
const OBJID	MONSTERID_FIRST		= 400001;			// MONSTER�ĵ�һ��ID
const OBJID	MONSTERID_LAST		= 499999;			// MONSTER�����һ��ID
const OBJID	PETID_FIRST			= 500001;			// PET�ĵ�һ��ID
const OBJID	PETID_LAST			= 599999;			// PET�����һ��ID
const OBJID	NPCSERVERID_LAST	= 699999;			// NPC�����һ��ID

const OBJID	CALLPETID_FIRST		= 700001;			// CALLPET�ĵ�һ��ID
const OBJID	CALLPETID_LAST		= 799999;			// CALLPET�����һ��ID

const OBJID TRAPID_FIRST		= 900001;			// ħ������ĵ�һ��ID
const OBJID MAGICTRAPID_FIRST	= 900001;			// ���ħ���ĵ�һ��ID
const OBJID MAGICTRAPID_LAST	= 989999;			// ���ħ�������һ��ID
const OBJID SYSTRAPID_FIRST		= 990001;			// ϵͳ����ĵ�һ��ID		// fixed to database id
const OBJID SYSTRAPID_LAST		= 999999;			// ϵͳ��������һ��ID		// fixed to database id
const OBJID TRAPID_LAST			= 999999;			// ħ����������һ��ID

const OBJID PLAYER_ID_FIRST		= 1000000;			// Player�ĵ�һ��ID
const OBJID PLAYER_ID_LAST		= 1999999999;		// Player�����һ��ID

const OBJID EUDEMON_ID_FIRST	= 2000000000;		// ���޵����һ��ID
const OBJID EUDEMON_ID_LAST		= 3999999999;		// ���޵����һ��ID

const OBJID CLIENT_ID_FIRST		= 4000000000;		// Ϊ�ͻ��˱�����ID�ռ�

//////////////////////////////////////////////////////////////////////
// ��������
const int	DEFAULT_LOGIN_MAPGROUP		= 0;		// ��¼��
const int	DEFAULT_LOGIN_MAPID			= 1000001;		// ��¼��
const int	DEFAULT_LOGIN_POSX			= 61;		// ��¼��
const int	DEFAULT_LOGIN_POSY			= 49;		// ��¼��

const int	CELLS_PER_BLOCK				= 18;		// ÿROOM�ĸ�����
const int	CELLS_PER_VIEW				= 18;		// ��������ĸ�����
const int	ITEMTYPEMONEY_MIN			= 1090000;	// ��С��Ǯ
const int	ITEMTYPEMONEY_MAX			= 1091020;	// ����Ǯ
const int	SMALLHEAPMONEY_LIMIT		= 10;		// С��Ǯ
const int	SMALLHEAPMONEY_TYPE			= 1090000;		// С��ǮITEMTYPE
const int	MIDDLEHEAPMONEY_LIMIT		= 100;		// �ж�Ǯ
const int	MIDDLEHEAPMONEY_TYPE		= 1090010;		// �ж�ǮITEMTYPE
const int	BIGHEAPMONEY_LIMIT			= 1000;		// ���Ǯ
const int	BIGHEAPMONEY_TYPE			= 1090020;		// ���ǮITEMTYPE

const int	SMALLHEAPGOLD_LIMIT			= 2000;		// С�ѽ���
const int	SMALLHEAPGOLD_TYPE			= 1091000;		// С�ѽ���ITEMTYPE
const int	MIDDLEHEAPGOLD_LIMIT		= 5000;		// �жѽ���
const int	MIDDLEHEAPGOLD_TYPE			= 1091010;		// �жѽ���ITEMTYPE
const int	BIGHEAPGOLD_LIMIT			= 10000;		// ��ѽ���
const int	BIGHEAPGOLD_TYPE			= 1091020;		// ��ѽ���ITEMTYPE

enum {
	OBJ_NONE	= 0x1000,
	OBJ_USER	= 0x1001,
	OBJ_MONSTER = 0x1002,
	OBJ_PET		= 0x1003,
	OBJ_ITEM	= 0x1004,
	OBJ_MAP		= 0x1008,
	OBJ_FRIEND	= 0x1010,
	OBJ_NPCTYPE	= 0x1020, 
	OBJ_NPC		= 0x1040,
	OBJ_MAPITEM	= 0x1080,
	OBJ_SYN		= 0x1100,
	OBJ_BOOTH	= 0x1200,
	OBJ_TRAP	= 0x1400,
	OBJ_TUTOR	= 0x1800,
};
inline bool IsObjType(OBJID idObjType, OBJID idUnion) { return (idObjType & idUnion & 0x0FFF) != 0; }

//////////////////////////////////////////////////////////////////////
// safe ptr
////////////////////////////////////////////////////////////////////////
class CUser;
typedef	CUser*	CUserPtr;
//typedef	TSafePtr<class CUser, OBJ_USER>			CUserPtr;
class CMonster;
typedef	CMonster*	CMonsterPtr;
//typedef	TSafePtr<class CMonster, OBJ_MONSTER>	CMonsterPtr;
class CItem;
typedef	CItem*	CItemPtr;
//typedef	TSafePtr<class CItem, OBJ_ITEM>			CItemPtr;
class CPet;
typedef CPet* CPetPtr;
class CGameMap;
typedef	CGameMap*	CMapPtr;
//typedef	TSafePtr<class CGameMap, OBJ_MAP>		CMapPtr;
class CFriend;
typedef	CFriend*	CFriendPtr;
//typedef	TSafePtr<class CFriend, OBJ_FRIEND>		CFriendPtr;
class CNpc;
typedef	CNpc*	CNpcPtr;
//typedef	TSafePtr<class CNpc, OBJ_NPC>			CNpcPtr;
class CMapItem;
typedef	CMapItem*	CMapItemPtr;
//typedef	TSafePtr<class CMapItem, OBJ_MAPITEM>	CMapItemPtr;
class CSyndicate;
typedef	CSyndicate*	CSynPtr;
//typedef	TSafePtr<class CSyndicate, OBJ_SYN>		CSynPtr;

//////////////////////////////////////////////////////////////////////
// ͨ�ýӿ�
//////////////////////////////////////////////////////////////////////
#ifdef	WORLD_KERNEL
#else
class CNetMsg;
class ISocket
{
public:
	virtual bool SendMsg			(::CNetMsg* pNetMsg)				PURE_VIRTUAL_FUNCTION_0
	virtual bool SendMsg			(SOCKET_ID idSocket, OBJID idMsg, const char* pBuf, int nMsgLen)	PURE_VIRTUAL_FUNCTION_0
	virtual bool SendNpcMsg			(OBJID idNpc, OBJID idMsg, const char* pBuf, int nMsgLen)			PURE_VIRTUAL_FUNCTION_0
	// ����֪ͨSOCKET�ر�
	virtual bool CloseSocket		(SOCKET_ID idSocket)			PURE_VIRTUAL_FUNCTION_0
};

typedef	void			CGameSocket;		//? �����ڻ������Ϣ����
#endif

#ifdef	PALED_DEBUG_X
#define	DEBUG_CREATEMSG(x,y,a,s,n1,n2)	//{MSGBUF D_CM;sprintf(D_CM,"�� msg:%s,id:%d,action:%d,%s,%d,%d",x,y,a,s,n1,n2);CMsgTalk msg;if(msg.Create("DEBUG","DEBUG",D_CM))SendMsg(&msg);}
#define	DEBUG_SENDMSG(x,y)				{MSGBUF D_CM;sprintf(D_CM,"�� msgtype:%d,socketid:%d",x,y);CMsgTalk msg;if(msg.Create("DEBUG","DEBUG",D_CM))SendMsg(&msg);}
#define	DEBUG_PROCESSMSG(x,y,a,s,n1,n2)	{MSGBUF D_CM;sprintf(D_CM,"�� msgtype:%d,socketid:%d,msg:%s,id:%d,action:%d,%s,%d,%d",GetType(),GetSocketID(),x,y,a,s,n1,n2);CMsgTalk msg;if(msg.Create("DEBUG","DEBUG",D_CM))SendMsg(&msg);}
#else
#define	DEBUG_CREATEMSG(x,y,a,s,n1,n2)	//{MSGBUF D_CM;sprintf(D_CM,"�� msg:%s,id:%d,action:%d,%s,%d,%d",x,y,a,s,n1,n2);CMsgTalk msg;if(msg.Create("DEBUG","DEBUG",D_CM))SendMsg(&msg);}
#define	DEBUG_SENDMSG(x,y)				{}//{MSGBUF D_CM;sprintf(D_CM,"�� msgid:%d,socketid:%d",x,y);CMsgTalk msg;if(msg.Create("DEBUG","DEBUG",D_CM))SendMsg(&msg);}
#define	DEBUG_PROCESSMSG(x,y,a,s,n1,n2)	{}//{MSGBUF D_CM;sprintf(D_CM,"�� msg:%s,id:%d,action:%d,%s,%d,%d",x,y,a,s,n1,n2);CMsgTalk msg;if(msg.Create("DEBUG","DEBUG",D_CM))SendMsg(&msg);}
#endif

inline void EmptyFunction(...) {}
#ifdef MULTI_KERNEL_LOG
	#define LOGDEBUG	LOGMSG
#else
	#define LOGDEBUG	EmptyFunction
#endif


#endif // ALL_GLOBAL_DEFINE_H