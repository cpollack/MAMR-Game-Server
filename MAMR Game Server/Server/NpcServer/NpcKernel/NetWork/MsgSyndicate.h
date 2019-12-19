// MsgBetOutside.h: interface for the CMsgAtk class.
// �ɽ��ޣ�2002.1.8
//////////////////////////////////////////////////////////////////////

#ifndef	MSGSYNDICATE_H
#define MSGSYNDICATE_H

#include "NetMsg.h"

enum{
		// ��ʵ��
		APPLY_JOIN			= 1,			// �����������, id
		INVITE_JOIN			= 2,			// �����������, id
		LEAVE_SYN			= 3,			// ��������
		KICKOUT_MEMBER		= 4,			// ����������Ա,id	(ע�⣺�ĳ�ID��)
		QUERY_SYN_NAME		= 6,			// ��ѯ��������
		SET_ALLY			= 7,			// ����				// to client, npc(npc_id is syn_id, same follow)
		CLEAR_ALLY			= 8,			// �������			// to client, npc
		SET_ANTAGONIZE		= 9,			// ����				// to client, npc
		CLEAR_ANTAGONIZE	= 10,			// �������			// to client, npc
		DONATE_MONEY		= 11,			// ���ھ�Ǯ
		QUERY_SYNATTR		= 12,			// ��ѯ������Ϣ		// to server
		SET_MAINSYN			= 13,			// ��������ɵ�ID	// to client
		SET_SUBSYN			= 14,			// ����Ӱ��ɵ�ID	// to client
		//UNITE_SUBSYN		= 15,			// �ϲ��ÿ� // to client // dwData���ϲ�, target������
		//UNITE_SYN			= 16,			// �ϲ����� // to client // dwData���ϲ�, target������
		SET_WHITE_SYN		= 17,			// �װ����ID // δ��ռ���뷢ID_NONE
		SET_BLACK_SYN		= 18,			// �ڰ����ID // δ��ռ���뷢ID_NONE
		DESTROY_SYN			= 19,			// ����㲥��ɾ�����ɡ�

		NPCMSG_CREATE_SYN	= 101,			// ֪ͨNPC��������Ӱ���	// to npc
		NPCMSG_DESTROY_SYN	= 102,			// ֪ͨNPC������ɾ������	// to npc
};


class CMsgSyndicate : public CNetMsg
{
public:
	CMsgSyndicate();
	virtual ~CMsgSyndicate();

	BOOL	Create (unsigned short usAction, OBJID idTarget);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct {
		MSGHEAD_DEFINE
		
		unsigned short	usAction;
		OBJID			idTarget;
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // MSGSYNDICATE_H
