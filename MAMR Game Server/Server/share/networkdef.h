#ifndef _NETWORKDEF_H
#define _NETWORKDEF_H

#include "define.h"

// max size define
const int _MAX_MSGSIZE		=1024;
const int _MAX_WORDSSIZE	=256;
const int _MAX_IDLETIME		=600;	// 600s idle time

typedef	char	WORDSSTR[_MAX_WORDSSIZE];

// msg type define
const unsigned short _MSG_NONE			=0;
const unsigned short _MSG_GENERAL		=1000;

//Cleaned
const unsigned short _MSG_WALK		= _MSG_GENERAL + 5;
const unsigned short _MSG_ACTION	= _MSG_GENERAL + 7;
const unsigned short _MSG_USERINFO	= _MSG_GENERAL + 8;
const unsigned short _MSG_ITEMINFO  = _MSG_GENERAL + 16;
const unsigned short _MSG_DIRECTION = _MSG_GENERAL + 18;
const unsigned short _MSG_MAPINFO	= _MSG_GENERAL + 31;
const unsigned short _MSG_PLAYER	= _MSG_GENERAL + 32;
const unsigned short _MSG_PETACTION = _MSG_GENERAL + 33;
const unsigned short _MSG_PETINFO   = _MSG_GENERAL + 34;
const unsigned short _MSG_COLOR	    = _MSG_GENERAL + 43;

const unsigned short _MSG_ROLE		= _MSG_GENERAL + 50;
const unsigned short _MSG_CONNECT	= _MSG_GENERAL + 52;

const unsigned short _MSG_BATTLEACT		= _MSG_GENERAL + 1000;
const unsigned short _MSG_NORMALACT		= _MSG_GENERAL + 1001;
const unsigned short _MSG_BATTLE		= _MSG_GENERAL + 1005;
const unsigned short _MSG_ENEMY			= _MSG_GENERAL + 1007;
const unsigned short _MSG_FIGHTER		= _MSG_GENERAL + 1008;
const unsigned short _MSG_BATTLERESULT	= _MSG_GENERAL + 1009;
const unsigned short _MSG_BATTLEROUND	= _MSG_GENERAL + 1012;
const unsigned short _MSG_NPCINFO		= _MSG_GENERAL + 1030;

//Uncleaned

const unsigned short _MSG_REGISTER		=_MSG_GENERAL+1;
const unsigned short _MSG_LOGIN			=_MSG_GENERAL+2;
const unsigned short _MSG_LOGIN_c		=_MSG_GENERAL+2; //special login override, original used for npc server?
const unsigned short _MSG_LOGOUT		=_MSG_GENERAL+3;
const unsigned short _MSG_TALK			=_MSG_GENERAL+4;
const unsigned short _MSG_ITEM			=_MSG_GENERAL+9;
const unsigned short _MSG_ATTACK		=_MSG_GENERAL + 10;
const unsigned short _MSG_ACCIDENT		=_MSG_GENERAL+11;
const unsigned short _MSG_TICK			=_MSG_GENERAL+12;
const unsigned short _MSG_ROOM			=_MSG_GENERAL+13;
const unsigned short _MSG_NAME			=_MSG_GENERAL+15;
const unsigned short _MSG_WEATHER		=_MSG_GENERAL+16 + 100;
const unsigned short _MSG_USERATTRIB	=_MSG_GENERAL+17;
const unsigned short _MSG_FRIEND		=_MSG_GENERAL+19;
const unsigned short _MSG_EFFECT		=_MSG_GENERAL+20;
const unsigned short _MSG_QUIZGAME		=_MSG_GENERAL+21;
const unsigned short _MSG_INTERACT		=_MSG_GENERAL+22;
const unsigned short _MSG_TEAM			=_MSG_GENERAL+23;
const unsigned short _MSG_ALLOT			= _MSG_GENERAL+24;
const unsigned short _MSG_WEAPONSKILL	= _MSG_GENERAL+25;
const unsigned short _MSG_TEAMMEMBER	= _MSG_GENERAL+26;
const unsigned short _MSG_GEMEMBED		=_MSG_GENERAL+27;

const unsigned short _MSG_TRADE			=_MSG_GENERAL+56;
const unsigned short _MSG_BATTLESYSTEM	=_MSG_GENERAL+57;

// new info in cq
const unsigned short _MSG_MAPITEM		=_MSG_GENERAL+101;
const unsigned short _MSG_PACKAGE		=_MSG_GENERAL+102;
const unsigned short _MSG_MAGICINFO		=_MSG_GENERAL+103;
const unsigned short _MSG_FLUSHEXP		=_MSG_GENERAL+104;
const unsigned short _MSG_MAGICEFFECT	=_MSG_GENERAL+105;
const unsigned short _MSG_SYNATTRINFO	=_MSG_GENERAL+106;
const unsigned short _MSG_SYNDICATE		=_MSG_GENERAL+107;
const unsigned short _MSG_ITEMINFOEX	=_MSG_GENERAL+108;
const unsigned short _MSG_NPCINFOEX		=_MSG_GENERAL+109;
const unsigned short _MSG_MESSAGEBOARD	=_MSG_GENERAL+111;
const unsigned short _MSG_SYNMEMBERINFO	=_MSG_GENERAL+112;
const unsigned short _MSG_DICE			=_MSG_GENERAL+113;
const unsigned short _MSG_SYNINFO		=_MSG_GENERAL+114;

const unsigned short _MSG_NPC			=_MSG_GENERAL+1031;
const unsigned short _MSG_DIALOG		=_MSG_GENERAL+1032;
const unsigned short _MSG_FRIENDINFO	=_MSG_GENERAL+1033;
const unsigned short _MSG_TIME			=_MSG_GENERAL+1034; 
const unsigned short _MSG_CALLPETINFO	=_MSG_GENERAL+1035;
const unsigned short _MSG_DATAARRAY		=_MSG_GENERAL+1036;
const unsigned short _MSG_EUDEMONATTRIB	=_MSG_GENERAL+1037;
const unsigned short _MSG_SCHOOLMEMBER	=_MSG_GENERAL+1038;
const unsigned short _MSG_PLAYERTASK	=_MSG_GENERAL+1039;
const unsigned short _MSG_TASK_LIST		=_MSG_GENERAL+1040;
const unsigned short _MSG_ANNOUNCE_LIST =_MSG_GENERAL+1041;
const unsigned short _MSG_ANNOUNCE_INFO =_MSG_GENERAL+1042;
const unsigned short _MSG_AUCTION       =_MSG_GENERAL+1043;
const unsigned short _MSG_CHATROOM      =_MSG_GENERAL+1044;	//ʥս��������ϵͳ��Ϣ
const unsigned short _MSG_ITEMATTRIB	=_MSG_GENERAL+1045;


// new msg in qq
const unsigned short _MSG_WALKEX		=_MSG_GENERAL+2005;

// msg npc server
const unsigned short _MSG_NPCSERVER		=20000;
const unsigned short _MSG_AINPCINFO		=_MSG_NPCSERVER+1;

// msg account server
const unsigned short _MSG_ACCOUNTSERVER	=1000;
const unsigned short _MSG_LOGIN_A	=_MSG_ACCOUNTSERVER+2;
const unsigned short _MSG_ACCOUNT_A	=_MSG_ACCOUNTSERVER+51;
//const unsigned short _MSG_CONNECT	=_MSG_ACCOUNTSERVER+52;
const unsigned short _MSG_FEE_A		=_MSG_ACCOUNTSERVER+200;		// paled
const unsigned short _MSG_QUERYFEE_A=_MSG_ACCOUNTSERVER+201;		// paled

// color define
const unsigned long	_COLOR_WHITE	=0x00ffffff;

// msg style define
const unsigned short _TXT_NORMAL	=0;
const unsigned short _TXT_SCROLL	=0x0001;
const unsigned short _TXT_FLASH		=0x0002;
const unsigned short _TXT_BLAST		=0x0008;

// msg attribute define
const unsigned short _TXTATR_NORMAL		=2000;
const unsigned short _TXTATR_PRIVATE	=_TXTATR_NORMAL+1;	// ˽��
const unsigned short _TXTATR_ACTION		=_TXTATR_NORMAL+2;	// ����
const unsigned short _TXTATR_TEAM		=_TXTATR_NORMAL+3;	// ����
const unsigned short _TXTATR_SYNDICATE	=_TXTATR_NORMAL+4;	// ����
const unsigned short _TXTATR_SYSTEM		=_TXTATR_NORMAL+5;	// ϵͳ
const unsigned short _TXTATR_FAMILY		=_TXTATR_NORMAL+6;	// ��ͥ
const unsigned short _TXTATR_TALK		=_TXTATR_NORMAL+7;	// ��̸
const unsigned short _TXTATR_YELP 		=_TXTATR_NORMAL+8;	// �к�
const unsigned short _TXTATR_FRIEND 	=_TXTATR_NORMAL+9;	// ����
const unsigned short _TXTATR_GLOBAL 	=_TXTATR_NORMAL+10;	// ǧ�ﴫ��
const unsigned short _TXTATR_GM 		=_TXTATR_NORMAL+11;	// GMƵ��
const unsigned short _TXTATR_WHISPER 	=_TXTATR_NORMAL+12;	// ����
const unsigned short _TXTATR_GHOST	 	=_TXTATR_NORMAL+13;	// ����
const unsigned short _TXTATR_SERVE		=_TXTATR_NORMAL+14; // ����

const unsigned short _TXTATR_REGISTER	=_TXTATR_NORMAL+100;
const unsigned short _TXTATR_ENTRANCE	=_TXTATR_NORMAL+101;
const unsigned short _TXTATR_SHOP		=_TXTATR_NORMAL+102;
const unsigned short _TXTATR_PETTALK	=_TXTATR_NORMAL+103;
const unsigned short _TXTATR_CRYOUT		=_TXTATR_NORMAL+104;
const unsigned short _TXTATR_WEBPAGE	=_TXTATR_NORMAL+105;

const unsigned short _TXTATR_NEWMESSAGE	=_TXTATR_NORMAL+106;
const unsigned short _TXTATR_TASK		=_TXTATR_NORMAL+107;
const unsigned short _TXTATR_SYNWAR_FIRST	=_TXTATR_NORMAL+108;	// ����ս��
const unsigned short _TXTATR_SYNWAR_NEXT	=_TXTATR_NORMAL+109;	// ����ս��

const unsigned short _TXTATR_LEAVEWORD		=_TXTATR_NORMAL+110;	// ����ϵͳ
const unsigned short _TXTATR_SYNANNOUNCE	=_TXTATR_NORMAL+111;	// ���ɹ���
const unsigned short _TXTATR_MESSAGEBOX		=_TXTATR_NORMAL+112;	// �Ի���
const unsigned short _TXTATR_REJECT			=_TXTATR_NORMAL+113;	// ����
const unsigned short _TXTATR_SYNTENET		=_TXTATR_NORMAL+114;	// ������ּ

const unsigned short _TXTATR_MSG_TRADE	=_TXTATR_NORMAL+201;	// �������԰�
const unsigned short _TXTATR_MSG_FRIEND	=_TXTATR_NORMAL+202;	// �������԰�
const unsigned short _TXTATR_MSG_TEAM	=_TXTATR_NORMAL+203;	// ������԰�
const unsigned short _TXTATR_MSG_SYN	=_TXTATR_NORMAL+204;	// �������԰�
const unsigned short _TXTATR_MSG_OTHER	=_TXTATR_NORMAL+205;	// �������԰�
const unsigned short _TXTATR_MSG_SYSTEM	=_TXTATR_NORMAL+206;	// �������԰�
// ....... �뱣������ID


const unsigned short _TXTATR_DIALOG_BEGIN	=_TXTATR_NORMAL+500;	// �Ի����һ��
// ... �м�ı�������֪ͨ�ͻ��˴򿪽���
const unsigned short _TXTATR_DIALOG_END		=_TXTATR_NORMAL+600;	// �Ի������һ�� + 1
#endif