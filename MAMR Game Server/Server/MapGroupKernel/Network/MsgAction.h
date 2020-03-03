// MsgAction.h: interface for the CMsgAction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGACT_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
#define AFX_MSGACT_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum {	//Verified
		actionNone				= 0, 
		actionChgDir			= 1, 
		actionPosition			= 2, 
		actionFlyMap			= 8, //Leave map

	//OLD
		actionEmotion			=93,
		actionBroadcastPos		=94,
		actionDivorce			=95,
		actionSelfUnfreeze		=96,
		actionChgMap			=97,			// �������
		actionChgWeather		=99,
		actionFireworks			=910,
		actionDie				=911,
		actionQuitSyn			=912,
		actionWalk				=913,
		actionEnterMap			=914,		// ��¼��1����֪ͨ�ͻ��˵�¼�ɹ�������Ѿ������ͼ�������! (to client: idUser is Map)
		actionGetItemSet		=915,		// ��¼��2��
		actionGetGoodFriend		=916,		// ��¼��3��
		actionForward			=917,
		actionLeaveMap			=918,		// ������->�ͻ���,idPlayer����CMsgPlayer��Ӧ����ʾ����뿪��ͼ��Ҫ��ɾ������
		actionJump				=919,
		actionRun				=920,
		actionEquip				=921,
		actionUnequip			=922,
		actionUplev				=923,		// �������(ֻ��ʾ����)
		actionXpCLear			=924,
		actionReborn			=925,
		actionDelRole			=926,
		actionGetWeaponSkillSet	=927,		// ��¼��4��
		actionGetMagicSet		=928,		// ��¼��5��
		actionSetPkMode			=929,
		actionGetSynAttr		=930,
		actionGhost				=931,		// ���
		actionSynchro			=932,		// ����ͬ����send to client self, request client broadcast self coord if no synchro; broadcast to other client, set coord of this player
		actionQueryFriendInfo	=933,		// idTarget = friend id
		actionQueryLeaveWord	=934,
		actionChangeFace		=935,
//		actionMine				=936,		// �ڿ󣬸���CMsgInteract
		actionTeamMemeberPos	=937,
		actionQueryPlayer		=938,
		actionAbordMagic		=939,
		actionMapARGB			=940,		// to client only
		actionMapStatus			=941,		// to npc server only, idTarget = map id.
		actionQueryTeamMember	=942,
		actionCreateBooth		=943,		// ��ʼ��̯ to server - unPosX,unPosY: playerpos; unDir:dirofbooth; to client - idTarget:idnpc; 
		actionSuspendBooth		=944,		// �����̯
		actionResumeBooth		=945,		// ������̯ to server - unPosX,unPosY: playerpos; unDir:dirofbooth; to client - idTarget:idnpc; 
		actionDestroyBooth		=946,		// ֹͣ��̯
		actionQueryCryOut		=947,		// ��ѯ��̯ߺ��
		actionPostCmd			=948,		// to client only
		actionQueryEquipment	=949,		// to server //idTargetΪ��Ҫquery��PlayerID
		actionAbortTransform	=950,		// to server
		actionCombineSubSyn		=951,		// to client, idUser-> idSubSyn, idTarget-> idTargetSyn
//		actionTakeOff			=952,		// to server, wing user take off
		actionGetMoney			=953,		// to client only // ��500�Լ�500����Ǯ��ֻ�����Լ���dwDataΪ�񵽵�Ǯ
//		actionCancelKeepBow		=954,		// to server, cancel keep_bow status
		actionQueryEnemyInfo	=955,		// idTarget = enemy id	// to server
		actionMoveStop			=956,		// to target client, data=milli secs.
		actionKickBack			=957,		// to client	idUser is Player ID, unPosX unPosY is Player pos
		actionDropMagic			=958,		// to client only, data is magic type
		actionDropSkill			=959,		// to client only, data is weapon skill type
		actionSoundEffect		=960,		// to client only, client play sound effect, dwData is monster type
		actionQueryMedal		=961,		// to server idUser is Player ID, dwData is medal
		actionDelMedal			=962,		// to server idUser is Player ID, dwData is medal
		actionAddMedal			=963,		// to client idUser is Player ID, dwData is medal
		actionSelectMedal		=964,		// to server idUser is Player ID, dwData is medal
		actionQueryHonorTitle	=965,		// to server idUser is Player ID, dwData is title
		actionDelHonorTitle		=966,		// to server idUser is Player ID, dwData is title
		actionAddHonorTitle		=967,		// to client idUser is Player ID, dwData is title
		actionSelectHonorTitle	=968,		// to server idUser is Player ID, dwData is title
		actionOpenDialog		=969,		// to client only, open a dialog, dwData is id of dialog
		actionFlashStatus		=970,		// broadcast to client only, team member only. dwData is dwStatus
		actionQuerySynInfo		=971,		// to server, return CMsgSynInfo. dwData is target syn id.

		///////////////
		actionStudentApply		=972,		// ʦ����������ͽ�� // to server/client idUserΪʦ��ID dwDataΪͽ��ID
		actionTeacherApply		=973,		// ͽ�������ʦ // to server/client idUserΪͽ��ID dwDataΪʦ��ID
		actionAgreeStudentApply	=974,		// ͬ���ʦ // to server idUserΪʦ��ID dwDataΪͽ��ID
		actionAgreeTeacherApply	= 975,		// ͬ������ѧ�� // to server idUserΪͽ��ID dwDataΪʦ��ID
		actionDismissStudent	=976,		// ����ѧ��// to server idUserΪʦ��ID dwDataΪͽ��ID
		actionLeaveTeacher		=977,		// ����ʦ�� // to server idUserΪͽ��ID dwDataΪʦ��ID
		actionQuerySchoolMember	=978,		// ��ѯʦͽ�б� //to server //
		actionTeacherRequest    =979,        // �����ֹ����з���ʦ����
 
		////////////////
		// Ӷ���������
		actionQueryPlayerTaskAcceptedList		=980, // ��ѯ������͵��ѽ������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
		actionQueryPlayerTaskUnacceptedList		=981, // ��ѯ������͵�δ�������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
//		actionQueryPlayerTaskCompletedList		=82, // ��ѯ������͵�����������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
		actionQueryPlayerMyTaskList				=983, // ��ѯ������͵��ҵ������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
		actionQueryPlayerTaskDetail				=984, // ��ѯ�������������ϸ���� // to server // dwDataΪ��ѯ����ID

		actionAcceptPlayerTask					=988, // �������� // to server // dwDataΪ����ID
//		actionCompletePlayerTask				=89, // ������� // to server // dwDataΪ����ID	// <== ����CMsgItem
		actionCancelPlayerTask					=990, // �������� // to server // dwDataΪ����ID

		actionLockUser							=991, // �����ͻ��˲�ͬ�����귽��
		actionUnlockUser						=992, // �����ͻ��˲�ͬ�����귽��
		actionMagicTrack						=993, // ͬ�����귽��
		
		actionQueryStudentsOfStudent			=994, // ��ѯͽ���б�idTarget = ��Ҫ��ѯͽ���б��ͽ��ID
		
		actionBurstXp			=995,		// XP����������ʹ��XP����
		actionTransPos			=996,		// ֪ͨ�ͻ��˽�����ƶ��������λ��
		actionDisappear			=997,		// ֪ͨ�ͻ���Ŀ�곬�����߷�Χ��ʧ, idUserΪĿ��ID��dwData=0��ʾ��ɫ��dwData=1��ʾ����MapItem

		// for ai server
		actionSuperChgMap		= 9200,		// to game server, data=idMap
		actionFullItem			= 9201,		// to game server, data=itemtype
		actionChangeMapDoc		= 9202,//no use		// to ai server, idPlayer=idMap, data=idDoc
		actionAddTerrainObj		= 9203,		// to ai server, idUser=idMap, data=idOwner, npc_id=idTerrainObj
		actionDelTerrainObj		= 9204,		// to ai server, idUser=idMap, data=idOwner
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

		OBJID		idUser;
		USHORT		unPosX, unPosY;
		union {
			DWORD	dwDir;
			DWORD	dwPassage;
		};
		DWORD	dwAction;

		DWORD		dwTimeStamp;
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGACT_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
