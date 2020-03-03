// protocol.h
// �ɽ��ޣ�2002.10.23
//////////////////////////////////////////////////////////////////////

#ifndef	PROTOCOL_H
#define	PROTOCOL_H

#include <string.h>
#include "define.h"
#ifdef MAPGROUP_KERNEL
#include "UserData.h"
#endif

enum{
		//////////////////////////////////////////////////////////////////////
		// ��ͼ������紦�����Ϣ
		KERNEL_BASE					= 1000,
		KERNEL_CLIENTMSG			= KERNEL_BASE + 1,				// CLIENTMSG_PACKET0(size:1024+12), �ͻ����ϴ�����Ϣ��
		KERNEL_NPCMSG				= KERNEL_BASE + 2,				// NPCMSG_PACKET0(size:1024+12), NPC�������ϴ�����Ϣ��
		KERNEL_CLOSEKERNEL			= KERNEL_BASE + 3,				// INT, SOCKET_ID��֪ͨ���Ĺر�(���ı����ٴ�֪ͨSOCKET��!!!)
		KERNEL_CREATESYNDICATE		= KERNEL_BASE + 10,				// CreateSyndicateInfo
		KERNEL_DESTROYSYNDICATE		= KERNEL_BASE + 11,				// OBJID
		KERNEL_CHANGESYNDICATE		= KERNEL_BASE + 12,				// SynFuncInfo0
		KERNEL_COMBINESYNDICATE		= KERNEL_BASE + 13,				// OBJID+OBJID
		KERNEL_SUPERMANLIST			= KERNEL_BASE + 14,				// OBJID+int, to world: ��ӻ��ѯĳ�˵�������to mapgroup: ����ĳ�˵�����
		KERNEL_QUERYSUPERMANLIST	= KERNEL_BASE + 15,				// OBJID+int, �´�����������


		//////////////////////////////////////////////////////////////////////
		// �ɵ�ͼ����Ĵ������Ϣ
		MAPGROUP_BASE				= 10000,
		MAPGROUP_LOGIN				= MAPGROUP_BASE + 1,			// ST_LOGIN, ��ҵ�¼��
		MAPGROUP_BROADCASTMSG		= MAPGROUP_BASE + 2,			// CLIENTMSG_PACKET0(size:1024+12), ת���㲥��Ϣ��
		MAPGROUP_SOCKETUSERINFO		= MAPGROUP_BASE + 3,			// ST_USERCHANGEMAPGORUP��STRUCT(SOCKET_ID,UserInfoStruct)����һ���ͼ�顣
		MAPGROUP_SENDOBJINFO		= MAPGROUP_BASE + 4,			// CHANGEMAPGORUP_INFO0{id,type,info}
		MAPGROUP_TRANSMITMSG		= MAPGROUP_BASE + 5,			// TRANSMSG_PACKET0(size:1024+16), ת���㲥��Ϣ��
		MAPGROUP_CHANGEMAPGROUP		= MAPGROUP_BASE + 10,			// ST_CHANGEMAPGROUP����һ���ͼ�顣
		MAPGROUP_CREATENEWNPC		= MAPGROUP_BASE + 11,			// ST_CREATENEWNPC������һ����NPC��
		MAPGROUP_CHANGETEAM			= MAPGROUP_BASE + 12,			// ST_CHANGETEAM, ת��TEAM�޸�OPERATION��
		MAPGROUP_REMOTECALL			= MAPGROUP_BASE + 13,			// REMOTE_CALL0, ת����USER��
		MAPGROUP_CHANGENPC			= MAPGROUP_BASE + 14,			// int+str+str, ת��NPC�޸�OPERATION��
		MAPGROUP_DELTRANSNPC		= MAPGROUP_BASE + 15,			// int, ת��ɾ��TRANS_NPC
		MAPGROUP_DELALLMONSTER		= MAPGROUP_BASE + 16,			// int, ɾ�����й���Ա�����¹��ͬʱ����SOCKET_KERNRL
		MAPGROUP_SETMAPSYNID		= MAPGROUP_BASE + 17,			// idMap+idSyn, �޸�ĳ��ͼ��ռ�����
		MAPGROUP_LOADALLPET			= MAPGROUP_BASE + 18,			// int, ����װ�����а����ػ���
		MAPGROUP_RPC				= MAPGROUP_BASE + 19,			// CEventPack, ת����ָ������
		MAPGROUP_TRANSMITMSG_FORCHATROOM = MAPGROUP_BASE + 20,		// ��������Ϣ


		//////////////////////////////////////////////////////////////////////
		// ��������Ĵ������Ϣ
		WORLD_BASE					= 20000,
		WORLD_SHELLTALK				= WORLD_BASE + 1,				// STRING, ��Ƿ���TALK��Ϣ��
		WORLD_SETPROCESSID			= WORLD_BASE + 2,				// CHANGE_USERDATA, �����µ�PROCESS_ID
		WORLD_CLOSESOCKET			= WORLD_BASE + 3,				// INT, SOCKET_ID������֪ͨSOCKET�ر�(SOCKET����֪ͨ����)
		WORLD_USERNAMEMSG			= WORLD_BASE + 4,				// USERNAMEMSG_PACKET0(size:1024+16+12), ������ת������ҡ�
		WORLD_USERIDMSG				= WORLD_BASE + 5,				// USERIDMSG_PACKET0(size:1024+4+12), ��IDת������ҡ�
		WORLD_LEVELUP				= WORLD_BASE + 6,				// OBJID, �������10����
		WORLD_QUERYFEE				= WORLD_BASE + 7,				// OBJID, ACCOUNT ID��
		WORLD_SENDTIME				= WORLD_BASE + 8,				// INT, SOCKET_ID
		WORLD_TRANSMITMSG			= WORLD_BASE + 9,				// TRANSMSG_PACKET0(size:1024+16), ת����Ϣ��


		//////////////////////////////////////////////////////////////////////
		// ��SOCKET���Ĵ������Ϣ
		SOCKET_BASE					= 30000,
		SOCKET_CLOSESOCKET			= SOCKET_BASE + 1,				// INT, SOCKET_ID������֪ͨSOCKET�ر�(SOCKET����֪ͨ����)
		SOCKET_SETPROCESSID			= SOCKET_BASE + 2,				// CHANGE_USERDATA, �����µ�PROCESS_ID
			//!!! ���ķ��͸���Ϣʱ��Ҫͬʱ����CUSER�е�PROCESS_ID��־�������ڴ���KERNEL_CLIENTMSGʱ��һ��Ҫ���PROCESS_ID�Ƿ�ƥ��!!!
		SOCKET_SENDCLIENTMSG		= SOCKET_BASE + 3,				// SENDCLIENTMSG_PACKET0(size:1024+12), ����ͻ��˺�NPC����������Ϣ��
		SOCKET_SENDNPCMSG			= SOCKET_BASE + 4,				// SENDNPCMSG_PACKET0(size:1024+12), ����ͻ��˺�NPC����������Ϣ��
		SOCKET_SETNPCSOCKETID		= SOCKET_BASE + 5,				// INT, SOCKET_ID, ������Ľ��յ�NPC�������ĵ�¼��Ϣʱ��֪ͨSOCKET���ġ�(����ΪSOCKET_NONE)
		SOCKET_SETNPCPROCESSID		= SOCKET_BASE + 6,				// CHANGE_NPCPROCESSID, �����µ�PROCESS_ID
		SOCKET_CHANGECODE			= SOCKET_BASE + 7,				// CHANGE_USERDATA���޸Ķ�̬���롣
		SOCKET_BREAKCONNECT			= SOCKET_BASE + 8,				// INT, SOCKET_ID, �����ʱ���ȶϿ�SOCKET���ӡ�
		SOCKET_BREAKALLCONNECT		= SOCKET_BASE + 11,				// INT, GM_SOCKET_ID, ��������ң���ֹ�������ӡ�


		//////////////////////////////////////////////////////////////////////
		// ����Ǵ������Ϣ
		SHELL_BASE					= 40000,
		SHELL_PRINTTEXT				= SHELL_BASE + 1,				// STRING, ���ķ��͵�TEXT��Ϣ
		SHELL_KERNELSTATE			= SHELL_BASE + 2,				// STRING, ���ķ��͵�STATE��������
		

		//////////////////////////////////////////////////////////////////////
		// �����ݿ���Ĵ������Ϣ
		DB_BASE						= 50000,
		DB_QUERY_USERINFO			= DB_BASE + 1,

		DB_MSG_BASEINFO				= DB_BASE + 101,
		DB_MSG_FRIENDS				= DB_BASE + 102,
		DB_MSG_ENEMYS				= DB_BASE + 103,
		DB_MSG_ITEMS				= DB_BASE + 104,
		DB_MSG_WEAPON_SKILL			= DB_BASE + 105,
		DB_MSG_MAGICS				= DB_BASE + 106,
		DB_MSG_SYNATTR				= DB_BASE + 107,
};

struct CLIENTMSG_PACKET0			// ���յ�CLIENT��Ϣ
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID	idPacket;
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct NPCMSG_PACKET0			// ���յ�NPC��Ϣ
{
	OBJID	idNpc;
	OBJID	idPacket;
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct SENDCLIENTMSG_PACKET0
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID	idPacket;
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct SENDNPCMSG_PACKET0
{
	OBJID	idNpc;				// �㲥��Ϣ��BCAST_NPCID
	OBJID	idPacket;
	int		nSize;
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct TRANSMSG_PACKET0			// ת�����������̴������Ϣ
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID			idNpc;				// ͬʱ֧��NPC����Ϣ
	OBJID	idPacket;
	int		nSize;
	int		nTrans;				// ��������
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct USERNAMEMSG_PACKET0			// ��WORLDת������Ϣ��������ת��
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID	idPacket;
	int		nSize;
	char	szName[_MAX_NAMESIZE];		// ת���������
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};

struct USERIDMSG_PACKET0			// ��WORLDת������Ϣ����IDת��
{
	SOCKET_ID		idSocket;			// SOCKET_ID
	OBJID	idPacket;
	int		nSize;
	OBJID	idUser;				// ת���������
	char	buf[1];				// ���ڽṹָ�룬����Ҫ�ռ�
};


struct CHANGE_USERDATA
{
	SOCKET_ID	idSocket;
	int			nData;
};

struct CHANGE_NPCPROCESSID
{
	SOCKET_ID	idNpc;
	PROCESS_ID	idProcess;		// ΪSOCKET_NONEʱΪɾ��
};

struct ST_LOGIN
{
	SOCKET_ID	idSocket;
	OBJID		idUser;
};

#ifdef MAPGROUP_KERNEL
struct ST_USERCHANGEMAPGORUP
{
	SOCKET_ID	idSocket;
	UserInfoStruct		info;
};
#endif

struct CHANGEMAPGORUP_INFO0
{
	OBJID		idUser;
	int			nInfoType;
	char		info[1];
};

struct CHANGE_MAPGROUP
{
	OBJID		idUser;
	PROCESS_ID	idProcess;
};

struct ST_CHANGEMAPGROUP
{
	OBJID		idUser;
	OBJID		idMap;
	int			nPosX;
	int			nPosY;
};

struct ST_CREATENEWNPC
{
	OBJID			id;
	OBJID			idMap;
	OBJID			idData;
	OBJID			idOwner;
	int				nData;
	unsigned short	usPosX;
	unsigned short	usPosY;
	unsigned short	usAction;
	unsigned short	usType;
	unsigned char	ucOwnerType;
};

struct ST_CREATENEWMONSTER { //Is this really needed?
	OBJID id;
	int iLevel;
};

struct CreateSyndicateInfo
{
	OBJID		idSyn;
	NAMESTR		szName;
	TENETSTR	szTenet;
	NAMESTR		szLeaderTitle;
	NAMESTR		szMemberTitle;
	OBJID		idLeader;
	NAMESTR		szLeader;
	int			nMoney;
	OBJID		idFealty;
	int			nMantle;
	int 		nSynFlag;//0:���ţ�1�����ţ�2���ֶ�
};

struct	SynFuncInfo0
{
	OBJID			idSyn;
	union {
		struct {
			int		nRank;				//���ɳ�Ա�ľ���
			int		nSynMemberLevel;	//���ɳ�Ա����
		};
		struct {
			DWORD	dwData[2];	
		};
	};
	unsigned short	nSize;
	unsigned char	ucFuncType;
	unsigned char	ucSaveFlag;
	union{
		long		IntParam[1];
		char		StrParam[1];
	};
};

struct ST_CHANGETEAM
{
	int				nAction;
	OBJID			idTeam;
	OBJID			idUser;
	int				nData;		// idSocket or (x,y)
};

struct	REMOTE_CALL0
{
	OBJID			idUser;
	unsigned short	nSize;
	unsigned char	ucFuncType;
	union{
		long		IntParam[1];
		char		StrParam[1];
	};
};

struct	VARIANT_SET0
{
	long		m_setLong[1];
	long&		IntParam(int idx)			{ return m_setLong[idx]; }
	char*		StrParam(int idx)			{ return (char*)&m_setLong[idx]; }
};


/////////////////////////////////////////
// DBService��	-- zlong 2004.09.06

struct	ST_QUERY_USERINFO
{
	OBJID	idUser;
};

const int		_MEDAL_BUFSIZE		= 64+1;
const int		_TITLE_BUFSIZE		= 64+1;

struct	ST_DB_USERINFO
{
	OBJID	idUser;

	// ����Ϊ��4�ֽڶ��룬û�а���ԭ����˳��
	DWORD	dwCoin_money;
	DWORD	dwLast_login;
	DWORD	dwLookface;
	DWORD	dwHair;
	char	setMedal[_MEDAL_BUFSIZE];
	UCHAR	ucLevel;
	UCHAR	ucMetempsychosis;
	UCHAR	ucNobility;
	DWORD	dwMedal_select;

	char	setTitle[_TITLE_BUFSIZE];
	UCHAR	ucProfession;
	UCHAR	ucAdditional_point;
	UCHAR	ucAuto_allot;
	DWORD	dwTitle_select;

	DWORD	dwMoney;
	DWORD	dwMoney_saved;
	USHORT	usRecordX;
	USHORT	usRecordY;
	//OBJID	id;
	OBJID	idAccount;
	OBJID	idRecordmap;
	OBJID	idSyndicate;
	int		nDeed;
	int		nExp;

	DWORD	dwTaskMask;
	DWORD	dwVirtue;
	OBJID	idHome;
	DWORD	dwLockKey;
	//DWORD	dwCurrLockKey;
	char	szMate[_MAX_NAMESIZE];
	char	szName[_MAX_NAMESIZE];
	USHORT	usForce;
	USHORT	usConstitution;
	USHORT	usHealth;
	USHORT	usLife;
	USHORT	usMana;
	USHORT	usSoul;
	USHORT	usSpeed;
	SHORT	sPk;
};

struct	ST_DB_FRIEND_INFO
{
		OBJID	id;
		OBJID	idUser;
		OBJID	idFriend;
		char	szFriendName[_MAX_NAMESIZE];
};

struct	ST_DB_FRIEND
{
	OBJID	idUser;

	int		nAmount;
	ST_DB_FRIEND_INFO	setFriends[1];
};

struct	ST_DB_ENEMY
{
	OBJID	idUser;
};

struct	ST_DB_ITEMINFO
{
	OBJID	id;

};
struct	ST_DB_ITEM
{
	OBJID	idUser;

	int		nAmount;
	ST_DB_ITEMINFO	setItems[1];
};

struct	ST_DB_WEAPON_SKILL
{
	OBJID	idUser;
};

struct	ST_DB_MAGIC
{
	OBJID	idUser;
};

struct	ST_DB_SYNATTR
{
	OBJID	idUser;
};



//////////////////////////////////////////////////////////////////////
// C/S Э��Ŀͻ��˲���	

// �ò��ֳ������������������������ʹ��
const int	PROTOCOL_MSG_HEADSIZE		= 4;
struct CProtocolMsgStruct{
	unsigned short	nMsgSize;
	unsigned short	idPacket;
	char			pMsg[1];
};

// �ֽ���Ϣ��
// return: netpacket size
inline int	SplitPacket(const char* pBuf, int nBufLen, OBJID* pidPacket, char** ppMsg, int* pMsgSize)
{
	if(nBufLen > PROTOCOL_MSG_HEADSIZE)
	{
		CProtocolMsgStruct*	pMsgPtr = (CProtocolMsgStruct*)pBuf;
		if(pMsgPtr->nMsgSize <= nBufLen)
		{
			if(pMsgPtr->nMsgSize < 4 || pMsgPtr->nMsgSize > MAX_PACKETSIZE)
				return 0;

			*pidPacket	= pMsgPtr->idPacket;
			*pMsgSize	= pMsgPtr->nMsgSize - PROTOCOL_MSG_HEADSIZE;
			*ppMsg		= pMsgPtr->pMsg;
			return pMsgPtr->nMsgSize;
		}
	}
	return 0;
}

// �ϳ���Ϣ��
// return: netpacket size
inline int	UnitePacket(char* pBuf, int nBufLen, OBJID idPacket, const char* pMsg, int nMsgSize)
{
	if(nBufLen >= nMsgSize + PROTOCOL_MSG_HEADSIZE)
	{
		CProtocolMsgStruct*	pMsgPtr = (CProtocolMsgStruct*)pBuf;
		pMsgPtr->idPacket		= (unsigned short)idPacket;
		pMsgPtr->nMsgSize		= nMsgSize + PROTOCOL_MSG_HEADSIZE;
		memcpy(pMsgPtr->pMsg,	pMsg, (size_t)nMsgSize);
		return pMsgPtr->nMsgSize;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// C/S Э���NPC����	

// �ò��ֳ������������������������ʹ��
const int	PROTOCOL_NPCMSG_HEADSIZE		= 8;
struct CProtocolNpcMsgStruct{
	unsigned short	nMsgSize;
	unsigned short	idPacket;
	unsigned long	idNpc;
	char			pMsg[1];
};

// �ֽ���Ϣ��
// return: netpacket size
inline int	SplitNpcPacket(const char* pBuf, int nBufLen, OBJID* pidPacket, char** ppMsg, int* pMsgSize, OBJID* pidNpc)
{
	if(nBufLen > PROTOCOL_NPCMSG_HEADSIZE)
	{
		CProtocolNpcMsgStruct*	pMsgPtr = (CProtocolNpcMsgStruct*)pBuf;
		if(pMsgPtr->nMsgSize <= nBufLen)
		{
			if(pMsgPtr->nMsgSize < 4 || pMsgPtr->nMsgSize > MAX_PACKETSIZE)
				return 0;

			*pidPacket	= pMsgPtr->idPacket;
			*pMsgSize	= pMsgPtr->nMsgSize - PROTOCOL_NPCMSG_HEADSIZE;
			*pidNpc		= pMsgPtr->idNpc;
			*ppMsg		= pMsgPtr->pMsg;
			return pMsgPtr->nMsgSize;
		}
	}
	return 0;
}

// �ϳ���Ϣ��
// return: netpacket size
inline int	UniteNpcPacket(char* pBuf, int nBufLen, OBJID idPacket, const char* pMsg, int nMsgSize, OBJID idNpc)
{
	if(nBufLen >= nMsgSize + PROTOCOL_NPCMSG_HEADSIZE)
	{
		CProtocolNpcMsgStruct*	pMsgPtr = (CProtocolNpcMsgStruct*)pBuf;
		pMsgPtr->idPacket		= (unsigned short)idPacket;
		pMsgPtr->nMsgSize		= nMsgSize + PROTOCOL_NPCMSG_HEADSIZE;
		pMsgPtr->idNpc			= idNpc;
		memcpy(pMsgPtr->pMsg,	pMsg, (size_t)nMsgSize);

		return pMsgPtr->nMsgSize;
	}
	return 0;
}


#endif // PROTOCOL_H