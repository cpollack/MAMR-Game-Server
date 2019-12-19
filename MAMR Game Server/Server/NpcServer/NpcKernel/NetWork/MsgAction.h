  // MsgAction.h: interface for the CMsgAction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
#define AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum {	actionNone				=0, 
		actionChgDir			=1, 
		actionPosition			=2, 
		actionEmotion			=3,
		actionBroadcastPos		=4,
		actionDivorce			= 5,
		actionSelfUnfreeze		=6,
		actionChgMap			=7,
		actionFlyMap			=8,
		actionChgWeather		=9,
		actionFireworks			= 10,
		actionDie				=11,
		actionQuitSyn			=12,
		actionWalk				=13,
		actionEnterMap			=14,		// ��¼��1����֪ͨ�ͻ��˵�¼�ɹ�������Ѿ������ͼ�������! (to client: idUser is Map)
		actionGetItemSet		= 15,
		actionGetGoodFriend		=16,
		actionForward			=17,
		actionLeaveMap			=18,		// ������->�ͻ���,idPlayer����CMsgPlayer��Ӧ����ʾ����뿪��ͼ��Ҫ��ɾ������
		actionJump				=19,
		actionRun				= 20,
		actionEquip				=21,
		actionUnequip			=22,
		actionUplev				=23,		// �������(ֻ��ʾ����)
		actionXpCLear			=24,
		actionReborn			= 25,
		actionDelRole			=26,
		actionGetWeaponSkillSet	=27,
		actionGetMagicSet		=28,
		actionSetPkMode			=29,
		actionGetSynAttr		= 30,
		actionGhost				=31,		// ���
		actionSynchro			=32,		// ����ͬ��
		actionQueryFriendInfo	=33,		// idTarget = friend id
		actionQueryLeaveWord	=34,
		actionChangeFace		= 35,
		actionMine				=36,
		actionTeamMemeberPos	=37,
		actionQueryPlayer		=38,
		actionAbordMagic		=39,
		actionMapARGB			= 40,		// to client only
		actionMapStatus			=41,		// to npc server only, idTarget = map id.
		actionQueryTeamMember	=42,
		actionCreateBooth		=43,		// ��ʼ��̯ to server - unPosX,unPosY: playerpos; unDir:dirofbooth; to client - idTarget:idnpc; 
		actionSuspendBooth		=44,		// �����̯
		actionResumeBooth		= 45,		// ������̯ to server - unPosX,unPosY: playerpos; unDir:dirofbooth; to client - idTarget:idnpc; 
		actionDestroyBooth		=46,		// ֹͣ��̯
		actionQueryCryOut		=47,		// ��ѯ��̯ߺ��
		actionPostCmd			=48,		// to client only
		actionQueryEquipment	=49,		// to server //idTargetΪ��Ҫquery��PlayerID
		actionAbortTransform	= 50,		// to server
		actionCombineSubSyn		=51,		// to client, idUser-> idSubSyn, idTarget-> idTargetSyn
		actionTakeOff			=52,		// to server, wing user take off
		actionGetMoney			=53,		// to client only // ��500�Լ�500����Ǯ��ֻ�����Լ���dwDataΪ�񵽵�Ǯ
		actionCancelKeepBow		=54,		// to server, cancel keep_bow status
		actionQueryEnemyInfo	= 55,		// idTarget = enemy id	// to server
		actionMoveStop			=56,		// to target client, data=milli secs.
		actionKickBack			=57,		// to client	idUser is Player ID, unPosX unPosY is Player pos, client answer actionSynchro


		actionLockUser			=91, // �����ͻ��˲�ͬ�����귽��
		actionUnlockUser		=92, // �����ͻ��˲�ͬ�����귽��
		actionMagicTrack		=93, // ͬ�����귽��


		// for ai server
		actionSuperChgMap		= 200,		// to game server, data=idMap
		actionFullItem			= 201,		// to game server, data=itemtype
		actionChangeMapDoc		= 202,//no use		// to ai server, idUser=idMap, data=idDoc
		actionAddTerrainObj		= 203,		// to ai server, idUser=idMap, data=idOwner, ncp_id=idTerrainObj
		actionDelTerrainObj		= 204,		// to ai server, idUser=idMap, data=idOwner
		
};


class CMsgAction : public CNetMsg  
{
public:
	CMsgAction();
	virtual ~CMsgAction();

	BOOL	Create	(OBJID idPlayer, int nPosX, int nPosY, USHORT usDir, USHORT usAction, DWORD dwData=0);
	BOOL	Create	(OBJID idPlayer, int nPosX, int nPosY, USHORT usDir, USHORT usAction, USHORT usTargetPosX, USHORT usTargetPosY);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void *pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		DWORD		dwTimeStamp;

		OBJID		idUser;
		USHORT		unPosX, unPosY;
		USHORT		unDir;
		union {
			OBJID		idTarget;
			DWORD		dwData;
			INT			iData;
			BOOL		bSucDone;
			struct {
				USHORT usTargetPosX;
				USHORT usTargetPosY;
			};
		};

		USHORT		usAction;
	}MSG_Info;

	MSG_Info*	m_pInfo;

};

#endif // !defined(AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
