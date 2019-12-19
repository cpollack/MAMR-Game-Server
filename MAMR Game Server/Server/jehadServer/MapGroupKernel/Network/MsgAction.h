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
		actionChgMap			=7,			// �������
		actionFlyMap			=8,
		actionChgWeather		=9,
		actionFireworks			= 10,
		actionDie				=11,
		actionQuitSyn			=12,
		actionWalk				=13,
		actionEnterMap			=14,		// ��¼��1����֪ͨ�ͻ��˵�¼�ɹ�������Ѿ������ͼ�������! (to client: idUser is Map)
		actionGetItemSet		= 15,		// ��¼��2��
		actionGetGoodFriend		=16,		// ��¼��3��
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
		actionGetWeaponSkillSet	=27,		// ��¼��4��
		actionGetMagicSet		=28,		// ��¼��5��
		actionSetPkMode			=29,
		actionGetSynAttr		= 30,
		actionGhost				=31,		// ���
		actionSynchro			=32,		// ����ͬ����send to client self, request client broadcast self coord if no synchro; broadcast to other client, set coord of this player
		actionQueryFriendInfo	=33,		// idTarget = friend id
		actionQueryLeaveWord	=34,
		actionChangeFace		= 35,
//		actionMine				=36,		// �ڿ󣬸���CMsgInteract
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
//		actionTakeOff			=52,		// to server, wing user take off
		actionGetMoney			=53,		// to client only // ��500�Լ�500����Ǯ��ֻ�����Լ���dwDataΪ�񵽵�Ǯ
//		actionCancelKeepBow		=54,		// to server, cancel keep_bow status
		actionQueryEnemyInfo	= 55,		// idTarget = enemy id	// to server
		actionMoveStop			=56,		// to target client, data=milli secs.
		actionKickBack			=57,		// to client	idUser is Player ID, unPosX unPosY is Player pos
		actionDropMagic			=58,		// to client only, data is magic type
		actionDropSkill			=59,		// to client only, data is weapon skill type
		actionSoundEffect		= 60,		// to client only, client play sound effect, dwData is monster type
		actionQueryMedal		=61,		// to server idUser is Player ID, dwData is medal
		actionDelMedal			=62,		// to server idUser is Player ID, dwData is medal
		actionAddMedal			=63,		// to client idUser is Player ID, dwData is medal
		actionSelectMedal		=64,		// to server idUser is Player ID, dwData is medal
		actionQueryHonorTitle	= 65,		// to server idUser is Player ID, dwData is title
		actionDelHonorTitle		=66,		// to server idUser is Player ID, dwData is title
		actionAddHonorTitle		=67,		// to client idUser is Player ID, dwData is title
		actionSelectHonorTitle	=68,		// to server idUser is Player ID, dwData is title
		actionOpenDialog		=69,		// to client only, open a dialog, dwData is id of dialog
		actionFlashStatus		= 70,		// broadcast to client only, team member only. dwData is dwStatus
		actionQuerySynInfo		=71,		// to server, return CMsgSynInfo. dwData is target syn id.

		///////////////
		actionStudentApply		=72,		// ʦ����������ͽ�� // to server/client idUserΪʦ��ID dwDataΪͽ��ID
		actionTeacherApply		=73,		// ͽ�������ʦ // to server/client idUserΪͽ��ID dwDataΪʦ��ID
		actionAgreeStudentApply	=74,		// ͬ���ʦ // to server idUserΪʦ��ID dwDataΪͽ��ID
		actionAgreeTeacherApply	= 75,		// ͬ������ѧ�� // to server idUserΪͽ��ID dwDataΪʦ��ID
		actionDismissStudent	=76,		// ����ѧ��// to server idUserΪʦ��ID dwDataΪͽ��ID
		actionLeaveTeacher		=77,		// ����ʦ�� // to server idUserΪͽ��ID dwDataΪʦ��ID
		actionQuerySchoolMember	=78,		// ��ѯʦͽ�б� //to server //
		actionTeacherRequest    =79,        // �����ֹ����з���ʦ����
 
		////////////////
		// Ӷ���������
		actionQueryPlayerTaskAcceptedList		=80, // ��ѯ������͵��ѽ������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
		actionQueryPlayerTaskUnacceptedList		=81, // ��ѯ������͵�δ�������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
//		actionQueryPlayerTaskCompletedList		=82, // ��ѯ������͵�����������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
		actionQueryPlayerMyTaskList				=83, // ��ѯ������͵��ҵ������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
		actionQueryPlayerTaskDetail				=84, // ��ѯ�������������ϸ���� // to server // dwDataΪ��ѯ����ID

		actionAcceptPlayerTask					=88, // �������� // to server // dwDataΪ����ID
//		actionCompletePlayerTask				=89, // ������� // to server // dwDataΪ����ID	// <== ����CMsgItem
		actionCancelPlayerTask					=90, // �������� // to server // dwDataΪ����ID

		actionLockUser							=91, // �����ͻ��˲�ͬ�����귽��
		actionUnlockUser						=92, // �����ͻ��˲�ͬ�����귽��
		actionMagicTrack						=93, // ͬ�����귽��
		
		actionQueryStudentsOfStudent			=94, // ��ѯͽ���б�idTarget = ��Ҫ��ѯͽ���б��ͽ��ID
		
		actionBurstXp			=95,		// XP����������ʹ��XP����
		actionTransPos			=96,		// ֪ͨ�ͻ��˽�����ƶ��������λ��
		actionDisappear			=97,		// ֪ͨ�ͻ���Ŀ�곬�����߷�Χ��ʧ, idUserΪĿ��ID��dwData=0��ʾ��ɫ��dwData=1��ʾ����MapItem

		// for ai server
		actionSuperChgMap		= 200,		// to game server, data=idMap
		actionFullItem			= 201,		// to game server, data=itemtype
		actionChangeMapDoc		= 202,//no use		// to ai server, idPlayer=idMap, data=idDoc
		actionAddTerrainObj		= 203,		// to ai server, idUser=idMap, data=idOwner, npc_id=idTerrainObj
		actionDelTerrainObj		= 204,		// to ai server, idUser=idMap, data=idOwner
};

enum { PKMODE_FREE=0, PKMODE_SAFE, PKMODE_TEAM, PKMODE_ARRESTMENT, PKMODE_SYNDICATE };    //change huang 2004.1.15
const int _ACTION_DANCE1		=001;
const int _ACTION_STANDBY		=100;
const int _ACTION_LAUGH			=150;
const int _ACTION_GUFFAW		=151;
const int _ACTION_FURY          =160;
const int _ACTION_SAD	        =170;
const int _ACTION_EXCITEMENT	=180;
const int _ACTION_SAYHELLO		=190;
const int _ACTION_SALUTE		=200;
const int _ACTION_GENUFLECT     =210;
const int _ACTION_KNEEL			=220;
const int _ACTION_COOL			=230;
const int _ACTION_SWIM			=240;
const int _ACTION_SITDOWN       =250;
const int _ACTION_ZAZEN			=260;
const int _ACTION_FAINT	        =270;
const int _ACTION_LIE	        =271;
//const int _ACTION_WALK			= 272;

 
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
