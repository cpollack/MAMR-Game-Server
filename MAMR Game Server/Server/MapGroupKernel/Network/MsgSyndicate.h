// MsgBetOutside.h: interface for the CMsgAtk class.
// �ɽ��ޣ�2002.1.8
//////////////////////////////////////////////////////////////////////

#ifndef	MSGSYNDICATE_H
#define MSGSYNDICATE_H

#include "NetMsg.h"
#include "NetStringPacker.h"

enum{
	ACTION_NONE = 0,				// ����ֵ

	APPLY_JOIN			= 1,			// �����������, id
	INVITE_JOIN			= 2,			// �����������, id
	LEAVE_SYN			= 3,			// ��������
	KICKOUT_MEMBER		= 4,			// ����������Ա, name
	QUERY_SYN_NAME		= 6,			// ��ѯ��������
	SET_ALLY			= 7,			// ����				// to client, npc(npc_id is syn_id, same follow)
	CLEAR_ALLY			= 8,			// �������			// to client, npc
	SET_ANTAGONIZE		= 9,			// ����				// to client, npc
	CLEAR_ANTAGONIZE	= 10,			// �������			// to client, npc
	DONATE_MONEY		= 11,			// ���ھ�Ǯ
	QUERY_SYNATTR		= 12,			// ��ѯ������Ϣ		// to server

	SET_SYN				= 14,			// ��Ӱ���ID		// to client
	//UNITE_SUBSYN		= 15,			// �ϲ��ÿ� // to client // dwData���ϲ�, target������
	//UNITE_SYN			= 16,			// �ϲ����� // to client // dwData���ϲ�, target������
	SET_WHITE_SYN		= 17,			// �װ����ID // δ��ռ���뷢ID_NONE
	SET_BLACK_SYN		= 18,			// �ڰ����ID // δ��ռ���뷢ID_NONE
	DESTROY_SYN			= 19,			// ����㲥��ɾ�����ɡ�
	SET_MANTLE          = 20,            // ����㲥������ // add huang 2004.1.1       

	_APPLY_ALLY			= 21,			// �������			// to server&client, idTarget=SynLeaderID
	_CLEAR_ALLY			= 22,			// �������			// to server

	_SET_ANTAGONIZE		= 23,			//���� client to server
	_CLEAR_ANTAGONIZE   = 24,			//������� client to server

	NPCMSG_CREATE_SYN	= 101,			// ֪ͨNPC��������Ӱ���	// to npc
	NPCMSG_DESTROY_SYN	= 102,			// ֪ͨNPC������ɾ������	// to npc

	KICKOUT_MEMBER_INFO_QUERY	= 110,	//������ѯ���뿪���ĳ�Ա
	KICKOUT_MEMBER_AGREE		= 111,	//����ͬ�⿪����Ա
	KICKOUT_MEMBER_NOAGREE		= 112,	//������ͬ�⿪����Ա

	SYNMEMBER_ASSIGN	= 113,			//���ɳ�Ա����	

	SYN_CHANGE_NAME		= 114,			// ���ɸ���




	SYN_CHANGE_SUBNAME		=114,		//���Ÿ���
	SYN_CHANGE_SUBSUBNAME	=115,		//�ֶӸ���

	SYN_DEMISE				=116,		//����
	SYN_SET_ASSISTANT		=117,		//���ø�����
	SYN_SET_TEAMLEADER		=118,		//���ð��ɶӳ�
	SYN_SET_PUBLISHTIME		=119,		//���ù���ʱ��

};

#define SYN_CONDITION_NEWBIE 20 //20������ΪԤ����Ա



class CMsgSyndicate : public CNetMsg
{
public:
	CMsgSyndicate();
	virtual ~CMsgSyndicate();

	BOOL	Create(unsigned short usAction, OBJID idTarget, OBJID idFealty=ID_NONE);

public:	

	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct {
		MSGHEAD_DEFINE
		
		unsigned short	usAction;
		union
		{
			OBJID	idTarget;
			DWORD	dwData;
		};
		union {
			OBJID	idFealty;				// �ϼ�����ID
			OBJID	idUser;					// �������޸İ��ɱ���ʱ
		};
		char	szBuf[1];
	}MSG_Info;
	
	MSG_Info*	m_pInfo;

	CNetStringPacker m_StrPacker;
	
};

#endif // MSGSYNDICATE_H
