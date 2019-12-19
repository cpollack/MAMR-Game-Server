// define.h ȫ�����ͺͳ�������
// �ɽ��ޣ�2002.10.29
//////////////////////////////////////////////////////////////////////

#pragma	warning(disable:4786)

#ifndef	ALL_GLOBAL_DEFINE_H
#define	ALL_GLOBAL_DEFINE_H

#include "common.h"
#include "mycom.h"

// #define ENG_RC
#ifdef ENG_RC
#include "eng_rc.h"
#else
#include "chn_rc.h"
#endif

//////////////////////////////////////////////////////////////////////
// �汾��
const int	GAME_VERSION	= 100;		// ���汾�ţ��ͻ��˺ͷ���������ͬ���������С�
const int	SERVER_VERSION	= 100;		// �������汾�ţ�SERVERÿ�θ���ʱ���ɸ��ģ�������ʾ��
const int	NPCSERVER_VERSION	= 987654321;	// NPC������������汾��
const int	NPCSERVER_VERSION_RELOGIN	= 987654322;	// NPC������������汾��

//////////////////////////////////////////////////////////////////////
// NPC�������ʺ�
#define		NPCSERVER_ACCOUNT 		"NpcServer Tqdig"			// NPC��������¼��
#define		NPCSERVER_PASSWORD		"skl8934##VJICW "			// NPC����������

//////////////////////////////////////////////////////////////////////
// ͨ�ó���
const int	IPSTR_SIZE			= 16;				// IP���ռ�
const int	_MAX_NAMESIZE		= 16;
const int	MAX_FIELDSIZE		= 1024;				// ���ݿ��д���ĳ���

#define		SYSTEM_NAME 		"SYSTEM"				// �㲥��Ϣʱ����ϵͳ�������ִ�
#define		ALLUSERS_NAME		"ALLUSERS"				// TALK�д�����ҡ������ִ�
#define		REPLAY_OK_STR		"ANSWER_OK"			// �������ʺŻ�LOGINʱ���صĳɹ���־����
#define		REPLAY_AGAIN_STR	"ANSWER_AGAIN"		// NPC_SERVER LOGINʱ���ص��ظ���¼��־����

//////////////////////////////////////////////////////////////////////
// ����
#define	CONFIG_FILENAME		"shell.ini"
const int	DBSTR_SIZE				= 16;			// ���ݿ�INI������
const int	_MAX_MSGSIZE			= 1024;			// ��Ϣ���ߴ�
const int	MAX_PACKETSIZE			= 1024;			// ������Ϣ���ߴ�
const int	MAX_MESSAGESIZE			= MAX_PACKETSIZE + 24;			// �ڲ���Ϣ���ߴ�
const int	SERVER_LISTEN_PORT		= 5816;			// �����������˿�

//////////////////////////////////////////////////////////////////////
// ���п���
const int	RESEND_MSGLOGIN_SECS		= 5;			// ��¼����Ϸ���������ٶ�

//////////////////////////////////////////////////////////////////////
// ����
typedef	unsigned long	OBJID;
typedef	unsigned long	PROCESS_ID;						// ͨ�����ڲ���Ϣ�ӿ�ID��ͬ
typedef	long			SOCKET_ID;						// ��Ҷ�Ӧ��SOCKET_ID��ͨ��ΪSET��������
typedef unsigned __int64	I64;

typedef	char			IPSTR[IPSTR_SIZE];
typedef	char			NAMESTR[_MAX_NAMESIZE];
typedef	char			SQLBUF[1024];
typedef	char			MSGBUF[1024];
typedef	char			NETMSGBUF[1024];				// �������BUF
typedef	char			MESSAGESTR[MAX_MESSAGESIZE];
typedef	char			FIELDBUF[MAX_FIELDSIZE];

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
const int	INVALID_ID		= -1;				// ��Ч��SOCKET����
const int	INVALID_ROOMID	= -1;				// ��Ч��ROOM_ID
const int	BCAST_NPCID		= 0;				// ����NPC�������Ĺ㲥����NPC������ת�������NPC��

const bool	UPDATE_TRUE				= true;
const bool	UPDATE_FALSE			= false;
const bool	DELRECORD_TRUE			= true;
const bool	DELRECORD_FALSE			= false;
const bool	SYNCHRO_TRUE			= true;
const bool	SYNCHRO_FALSE			= false;

//////////////////////////////////////////////////////////////////////
// ID�ռ�
const OBJID	SCENEID_FIRST		= 000001;			// SCENE�ĵ�һ��ID
const OBJID	SYSNPCID_FIRST		= 00001;			// SYSNPC�ĵ�һ��ID		// fixed to database id
const OBJID	SYSNPCID_LAST		= 99999;			// SYSNPC�����һ��ID	// fixed to database id
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
const OBJID SYSTRAPID_FIRST		= 990001;			// ϵͳ����ĵ�һ��ID
const OBJID SYSTRAPID_LAST		= 999999;			// ϵͳ��������һ��ID
const OBJID TRAPID_LAST			= 999999;			// ħ����������һ��ID

const OBJID PLAYER_ID_FIRST		= 1000000;			// Player�ĵ�һ��ID
const OBJID PLAYER_ID_LAST		= 3999999999;		// Player�����һ��ID

const OBJID CLIENT_ID_FIRST		= 4000000000;		// Ϊ�ͻ��˱�����ID�ռ�

//////////////////////////////////////////////////////////////////////
// �������
#define	MSGHEAD_DEFINE
			//USHORT		unMsgSize;
			//USHORT		unMsgType;

//////////////////////////////////////////////////////////////////////
// �ʽ�����
const int	DEFAULT_LOGIN_MAPGROUP		= 0;		// ��¼��
const int	DEFAULT_LOGIN_MAPID			= 1000;		// ��¼��
const int	DEFAULT_LOGIN_POSX			= 44;		// ��¼��
const int	DEFAULT_LOGIN_POSY			= 44;		// ��¼��
const int	DEFAULT_LOGIN_DIR			= 0;
const int	DEFAULT_LOGIN_STATUS		= 0;		// STATUS_NORMAL
const int	DEFAULT_LOGIN_POSE			= 0;
const int	DEFAULT_LOGIN_EMOTION		= 0;

const int	CELLS_PER_BLOCK				= 18;		// ÿROOM�ĸ�����
const int	CELLS_PER_VIEW				= 18;		// ��������ĸ�����
const int	BLOCKWIDTH_PER_MAP			= 100;		// ��ͼX����ROOM���������˹��󣬿պ��ڴ�

const int	DEFAULT_MAP_WIDTH			= 50;		// ÿ�ŵ�ͼ��ROOM��
const int	DEFAULT_MAP_HEIGHT			= 50;

const int	MAPS_PER_MAPGROUP			= 1;

enum {
	OBJ_NONE	= 1234,
	OBJ_USER,
	OBJ_ITEM,
	OBJ_MAP,
	OBJ_FRIEND,
	OBJ_NPC,
	OBJ_NPCGEN,
	OBJ_NPCTYPE,
	OBJ_AGENT,
};

class CUser;
class CNpc;
class CAgent;
GUID_DECLARE(CUser,OBJ_USER)
GUID_DECLARE(CNpc,OBJ_NPC)
GUID_DECLARE(CAgent,OBJ_AGENT)

#define NOMATE_NAME		"��"						// ����ż����ż��

#define	SYNNAME_NONE	"��"						// �ް�����ҵİ�����
#define	SYNLEADER_TITLE	"����"						// ������TITLE
#define	SYNMEMBER_TITLE	"��ͨ����"						// �������ҵ�TITLE
#define	NOSYN_TITLE		"��"						// �ް�����ҵ�TITLE

//////////////////////////////////////////////////////////////////////
// ��������
const int	STATESTR_SIZE		= 2048;


//////////////////////////////////////////////////////////////////////
// safe ptr
////////////////////////////////////////////////////////////////////////
class CUser;
typedef	CUser*	CUserPtr;
//typedef	TSafePtr<class CUser, OBJ_USER>		CUserPtr;
class CItem;
typedef	CItem*	CItemPtr;
//typedef	TSafePtr<class CItem, OBJ_ITEM>		CItemPtr;
class CGameMap;
typedef	CGameMap*	CMapPtr;
//typedef	TSafePtr<class CGameMap, OBJ_MAP>	CMapPtr;
class CFriend;
typedef	CFriend*	CFriendPtr;
//typedef	TSafePtr<class CFriend, OBJ_FRIEND>	CFriendPtr;
#define	CNpcPtr			INpc*
//typedef	TSafePtr<class CNpc, OBJ_NPC>		CNpcPtr;
class CNpcGenerator;
typedef	CNpcGenerator*	CGenPtr;
//typedef	TSafePtr<class CNpcGenerator, OBJ_NPCGEN>		CGenPtr;
class CNpcType;
typedef	CNpcType*	CNpcTypePtr;
//typedef	TSafePtr<class CNpcType, OBJ_NPCTYPE>		CNpcTypePtr;

//////////////////////////////////////////////////////////////////////
/*class CNetMsg;
class ISocket
{
public:
	virtual bool SendMsg			(CNetMsg* pNetMsg)				PURE_VIRTUAL_FUNCTION_0
	virtual bool SendMsg			(SOCKET_ID idSocket, OBJID idMsg, const char* pBuf, int nMsgLen)	PURE_VIRTUAL_FUNCTION_0
	virtual bool SendNpcMsg			(OBJID idNpc, OBJID idMsg, const char* pBuf, int nMsgLen)			PURE_VIRTUAL_FUNCTION_0
	// ����֪ͨSOCKET�ر�
	virtual bool CloseSocket		(SOCKET_ID idSocket)			PURE_VIRTUAL_FUNCTION_0
};
*/
typedef	void			CGameSocket;		// �����ڻ������Ϣ����

///////////////////////////////////////////////////////////////////////
// ���߷���
const int _DELTA_X[9]={ 0,-1,-1,-1, 0, 1, 1, 1, 0 };
const int _DELTA_Y[9]={ 1, 1, 0,-1,-1,-1, 0, 1, 0 };
const int MAX_DIRSIZE = 8;
inline int GetDirByPos(int nFromX, int nFromY, int nToX, int nToY)		// return MAX_DIRSIZE: error
{
	if(nFromX < nToX)
	{
		if(nFromY < nToY)
			return 7;
		else if(nFromY > nToY)
			return 5;
		else
			return 6;
	}
	else if(nFromX > nToX)
	{
		if(nFromY < nToY)
			return 1;
		else if(nFromY > nToY)
			return 3;
		else
			return 2;
	}
	else // if(nFromX == nToX)
	{
		if(nFromY < nToY)
			return 0;
		else if(nFromY > nToY)
			return 4;
	}
	return MAX_DIRSIZE;
}


#endif // ALL_GLOBAL_DEFINE_H