// AgentData.h: agent system config file
// paled, 2003.8.18
//////////////////////////////////////////////////////////////////////

#ifndef	AGENT_DATA_H
#define	AGENT_DATA_H

#include "common.h"
#include "BaseFunc.h"

const int		TICKS_PER_SEC			= 2;

//////////////////////////////////////////////////////////////////////
inline const char* const * GetActionStringSet()
{
	static char* setAction[]={
			// attr
			"ChangeMode",//XXXXXXXXXXX				// �޸�Mode(_,_)����action��ʵ��д��������ʵ��
			"Reborn",
			"TalkToName",				// (name,str)
			"TalkToID",					// (id,str)

			// move
			"MoveCloseTarget",//XXXXXXXXXXX			// (id)���ߵ��ܹ����Է��ľ��롣
			"JumpClose",				// (x,y,dist)���ߵ���Է�һ���ľ��롣
			"JumpToSafePos",			// ������ȫ�ĵط�����ֹ���ְ�Χ
			"ChangeMapTo",				// (id,x,y)��SUPER����ص�ָ���ص�(���ƻسǾ�)
			"RandomWalk",				// ����
			"KeepOutEnemy",				// (dist)������˱��־��룬����

			// fight
			"AttackRole",				// (id)

			// item_pack
			"UseItem",					// (type)��һ��ҩ
			"FullMedicine",				// (type)��SHOP��װ��ҩ, SUPER����

			// team
			"AcceptTeamInvite",			// (id)
			"SendTeamApply",			// (id)
			"LeaveTeam",

			NULL
	};

	return setAction;
}

enum {
											// // attr
		ACTION_CHANGE_MODE,					// "ChangeMode",				// �޸�Mode(_,_)����action��ʵ��д��������ʵ��
		ACTION_REBORN,						// "Reborn",
		ACTION_TALK_TO_NAME,				// "TalkToName",				// (name,str)
		ACTION_TALK_TO_ID,					// "TalkToID",					// (id,str)
											// 
											// // move
		ACTION_MOVE_CLOSE,					// "MoveCloseTarget",			// (id)���ߵ��ܹ����Է��ľ��롣XXXXXXXXXXX
		ACTION_JUMP_CLOSE,					// "JumpClose":					// (x,y,dist)���ߵ���Է�һ���ľ��롣
		ACTION_JUMP_TO_SAFE,				// "JumpToSafePos",				// ������ȫ�ĵط�����ֹ���ְ�Χ
		ACTION_CHGMAP,						// "ChangeMapTo",				// (id,x,y)�ó�������ص�SHOP����(���ƻسǾ�)
		ACTION_RANDOM_WALK,					// "RandomWalk",				// ����
		ACTION_LEAVE_EVIL,					// "KeepOutEnemy",				// (dist)������˱��־��룬����
											// 
											// // fight
		ACTION_ATTACK,						// "AttackRole",				// (id)
											// 
											// // item_pack
		ACTION_USE_ITEM,					// "UseItem":					// (type)��һ��ҩ
		ACTION_FULL_MEDICINE,				// "FullMedicine",				// (type)��SHOP��װ��ҩ
											// 
											// // team
		ACTION_ACCEPT_INVITE,				// "AcceptTeamInvite",			// (id)
		ACTION_SEND_APPLY,					// "SendTeamApply",				// (id)
		ACTION_LEAVE_TEAM,					// "LeaveTeam",
};

//////////////////////////////////////////////////////////////////////
inline const char* const * GetFactFuncStringSet()
{
	static char*	setFactFunc[]={
			// attr
			"IsAlive",					// (id)������ɫ�Ƿ����
			"IsWing",					// (id)������ɫ�Ƿ��ڷ�����
			"IsUser",					// (id)
			"IsMonster",				// (id)
			"EvilValue",				// (id, int)��ȡ��ɫ��а��ֵ�����������������Ϊ100������Ϊ50����������ͨ���Ϊ0
			"CoolValue",				// (id, int)��100 ~ 0�������ּ�Ʒ����Ϊ50
			"Level",					// (id, int)��ȡ��ɫ�ȼ�(����װ������ߵȼ�)
			"MyLife",					// (int)

			// move
			"RolePos",					// (id,x,y)��ȡ��ɫ������
			"MyDistance",				// (x,y,int)����Ŀ���ľ���

			// fight
			"AttackDistance",			// (id,int)���ܹ����Է��ľ���
			"DangerValue",				// (int)��+�� ~ 0��ͨ��80��Σ�գ���������Ϊ50���޵���Ϊ0

			// item pack
			"ItemCount",				// (int)��40 ~ 0����������Ʒ����(ҩƷ����)

			// team
			"MyLeader",					// (id)���ӳ�ID
			"IsLeader",					// (id)������Ƿ�ӳ�

			NULL
	};

	return setFactFunc;
}

enum{
											// // attr
		FACTFUNC_IS_ALIVE,					// "IsAlive",					// (id)������ɫ�Ƿ����
		FACTFUNC_IS_WING,					// "IsWing",					// (id)������ɫ�Ƿ��ڷ�����
		FACTFUNC_IS_USER,					// "IsUser",					// (id)
		FACTFUNC_IS_MONSTER,				// "IsMonster",				// (id)
		FACTFUNC_EVIL_VALUE,				// "EvilValue",				// (id, int)��ȡ��ɫ��а��ֵ�����������������Ϊ100������Ϊ50����������ͨ���Ϊ0
		FACTFUNC_COOL_VALUE,				// "CoolValue",				// (id, int)��100 ~ 0�������ּ�Ʒ����Ϊ50
		FACTFUNC_LEVEL,						// "Level",					// (id, int)��ȡ��ɫ�ȼ�(����װ������ߵȼ�)
		FACTFUNC_MY_LIFE,					// "MyLife",					// (int)

											// // move
		FACTFUNC_ROLE_POS,					// "RolePos",					// (id,x,y)��ȡ��ɫ������
		FACTFUNC_MYDISTANCE,				// "MyDistance",				// (x,y,int)����Ŀ���ľ���

											// // fight
		FACTFUNC_ATTACK_DISTNACE,			// "AttackDistance",			// (id,int)���ܹ����Է��ľ���
		FACTFUNC_DANGER_VALUE,				// "DangerValue",				// (int)��+�� ~ 0��ͨ��80��Σ�գ���������Ϊ50���޵���Ϊ0

											// // item pack
		FACTFUNC_ITEM_COUNT,				// "ItemCount"					// (int)��40 ~ 0����������Ʒ����(ҩƷ����)

											// // team
		FACTFUNC_MY_LEADER,					// "MyLeader",					// (id)���ӳ�ID
		FACTFUNC_IS_LEADER,					// "IsLeader",					// (id)������Ƿ�ӳ�
};

//////////////////////////////////////////////////////////////////////
//* push fact set, add and del
//#define FACT_MODE				"Mode"					// (e,e)			// 0
#define FACT_LOOK_TARGET		"LookTarget"			// <id>				// 80
#define FACT_TALK_TO_ME			"TalkToMe"				// <name>(str)		// 50
#define FACT_TEAM_INVITE		"TeamInvite"			// (id)				// 50
//#define FACT_LOOK_ATTACK		"LookAttack"			// (id,id)			// 80
//#define FACT_LISTEN_TALK		"ListenTalk"			// (name,name,str)		// 50
//*/

//////////////////////////////////////////////////////////////////////
inline int	 Priority2Durable(int nPriority)
{
	static int	setPriority2Durable[]={ INT_MAX/TICKS_PER_SEC,				// 0

		// random
		1200, 1200, 1200, 1200, 1200,  1200, 1200, 1200, 1200, 1200,		// 1 - 10
		300, 300, 300, 300, 300,  300, 300, 300, 300, 300,		// 11 - 20

		// idle
		8, 8, 8, 8, 8,  8, 8, 8, 8, 8,		// 21 - 30
		8, 8, 8, 8, 8,  8, 8, 8, 8, 8,		// 31 - 40
		8, 8, 8, 8, 8,  8, 8, 8, 8, 8,		// 41 - 50

		// fight
		3, 3, 3, 3, 3,  3, 3, 3, 3, 3,		// 51 - 60
		3, 3, 3, 3, 3,  3, 3, 3, 3, 3,		// 61 - 70
		3, 3, 3, 3, 3,  3, 3, 3, 3, 3,		// 71 - 80

		// attack
		1, 1, 1, 1, 1,  1, 1, 1, 1, 1,		// 81 - 90
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,		// 91 - 100
	};

	return setPriority2Durable[nPriority];
}



#endif// AGENT_DATA_H

