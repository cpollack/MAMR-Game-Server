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
		actionChgMap			=97,			// 无需参数
		actionChgWeather		=99,
		actionFireworks			=910,
		actionDie				=911,
		actionQuitSyn			=912,
		actionWalk				=913,
		actionEnterMap			=914,		// 登录第1步，通知客户端登录成功，玩家已经进入地图。仅玩家! (to client: idUser is Map)
		actionGetItemSet		=915,		// 登录第2步
		actionGetGoodFriend		=916,		// 登录第3步
		actionForward			=917,
		actionLeaveMap			=918,		// 服务器->客户端,idPlayer。与CMsgPlayer对应，表示玩家离开地图，要求删除对象。
		actionJump				=919,
		actionRun				=920,
		actionEquip				=921,
		actionUnequip			=922,
		actionUplev				=923,		// 玩家升级(只显示动画)
		actionXpCLear			=924,
		actionReborn			=925,
		actionDelRole			=926,
		actionGetWeaponSkillSet	=927,		// 登录第4步
		actionGetMagicSet		=928,		// 登录第5步
		actionSetPkMode			=929,
		actionGetSynAttr		=930,
		actionGhost				=931,		// 变鬼
		actionSynchro			=932,		// 坐标同步。send to client self, request client broadcast self coord if no synchro; broadcast to other client, set coord of this player
		actionQueryFriendInfo	=933,		// idTarget = friend id
		actionQueryLeaveWord	=934,
		actionChangeFace		=935,
//		actionMine				=936,		// 挖矿，改用CMsgInteract
		actionTeamMemeberPos	=937,
		actionQueryPlayer		=938,
		actionAbordMagic		=939,
		actionMapARGB			=940,		// to client only
		actionMapStatus			=941,		// to npc server only, idTarget = map id.
		actionQueryTeamMember	=942,
		actionCreateBooth		=943,		// 开始摆摊 to server - unPosX,unPosY: playerpos; unDir:dirofbooth; to client - idTarget:idnpc; 
		actionSuspendBooth		=944,		// 收起摆摊
		actionResumeBooth		=945,		// 继续摆摊 to server - unPosX,unPosY: playerpos; unDir:dirofbooth; to client - idTarget:idnpc; 
		actionDestroyBooth		=946,		// 停止摆摊
		actionQueryCryOut		=947,		// 查询摆摊吆喝
		actionPostCmd			=948,		// to client only
		actionQueryEquipment	=949,		// to server //idTarget为需要query的PlayerID
		actionAbortTransform	=950,		// to server
		actionCombineSubSyn		=951,		// to client, idUser-> idSubSyn, idTarget-> idTargetSyn
//		actionTakeOff			=952,		// to server, wing user take off
		actionGetMoney			=953,		// to client only // 捡到500以及500以上钱，只传给自己，dwData为捡到的钱
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
		actionStudentApply		=972,		// 师父申请招收徒弟 // to server/client idUser为师父ID dwData为徒弟ID
		actionTeacherApply		=973,		// 徒弟申请拜师 // to server/client idUser为徒弟ID dwData为师父ID
		actionAgreeStudentApply	=974,		// 同意拜师 // to server idUser为师父ID dwData为徒弟ID
		actionAgreeTeacherApply	= 975,		// 同意招收学生 // to server idUser为徒弟ID dwData为师父ID
		actionDismissStudent	=976,		// 开除学生// to server idUser为师父ID dwData为徒弟ID
		actionLeaveTeacher		=977,		// 背叛师门 // to server idUser为徒弟ID dwData为师父ID
		actionQuerySchoolMember	=978,		// 查询师徒列表 //to server //
		actionTeacherRequest    =979,        // 在新手工会中发拜师申请
 
		////////////////
		// 佣兵任务相关
		actionQueryPlayerTaskAcceptedList		=980, // 查询玩家悬赏的已接任务列表 // to server // dwData为上一次查询的最后一个ID
		actionQueryPlayerTaskUnacceptedList		=981, // 查询玩家悬赏的未接任务列表 // to server // dwData为上一次查询的最后一个ID
//		actionQueryPlayerTaskCompletedList		=82, // 查询玩家悬赏的已完成任务列表 // to server // dwData为上一次查询的最后一个ID
		actionQueryPlayerMyTaskList				=983, // 查询玩家悬赏的我的任务列表 // to server // dwData为上一次查询的最后一个ID
		actionQueryPlayerTaskDetail				=984, // 查询玩家悬赏任务详细内容 // to server // dwData为查询任务ID

		actionAcceptPlayerTask					=988, // 接受任务 // to server // dwData为任务ID
//		actionCompletePlayerTask				=89, // 完成任务 // to server // dwData为任务ID	// <== 改用CMsgItem
		actionCancelPlayerTask					=990, // 撤销任务 // to server // dwData为任务ID

		actionLockUser							=991, // 锁定客户端并同步坐标方向
		actionUnlockUser						=992, // 解锁客户端并同步坐标方向
		actionMagicTrack						=993, // 同步坐标方向
		
		actionQueryStudentsOfStudent			=994, // 查询徒孙列表，idTarget = 需要查询徒孙列表的徒弟ID
		
		actionBurstXp			=995,		// XP爆发，允许使用XP技能
		actionTransPos			=996,		// 通知客户端将玩家移动到随机的位置
		actionDisappear			=997,		// 通知客户端目标超出视线范围消失, idUser为目标ID，dwData=0表示角色，dwData=1表示其他MapItem

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
