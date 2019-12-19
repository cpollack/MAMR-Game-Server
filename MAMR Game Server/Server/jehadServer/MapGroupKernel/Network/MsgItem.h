// MsgItem.h: interface for the CMsgItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGITEM_H__9AB1BCEA_F6D1_4413_A39D_8AC35C9FF655__INCLUDED_)
#define AFX_MSGITEM_H__9AB1BCEA_F6D1_4413_A39D_8AC35C9FF655__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum {	ITEMACT_NONE			=0, 
		ITEMACT_BUY,					// to server, id: idNpc, data: idItemType
		ITEMACT_SELL,	 				// to server, id: idNpc, data: idItem
		ITEMACT_DROP,					// to server, x, y
		ITEMACT_USE,					// to server, data: position
		ITEMACT_EQUIP			=5,		// to client��֪ͨװ����Ʒ
		ITEMACT_UNEQUIP,				// to server, data: position
		ITEMACT_SPLITITEM,				// to server, data: num
		ITEMACT_COMBINEITEM,			// to server, data: id
		ITEMACT_QUERYMONEYSAVED,		// to server/client, id: idNpc, data: nMoney
		ITEMACT_SAVEMONEY		=10,	// to server, id: idNpc, data: nMoney
		ITEMACT_DRAWMONEY,				// to server, id: idNpc, data: nMoney
		ITEMACT_DROPMONEY,	 			// to server, x, y
		ITEMACT_SPENDMONEY,				// �����壬�ݱ���
		ITEMACT_REPAIR,					// to server, return MsgItemInfo
		ITEMACT_REPAIRALL		=15,	// to server, return ITEMACT_REPAIRAll, or not return if no money
		ITEMACT_IDENT,					// to server, return MsgItemInfo
		ITEMACT_DURABILITY,				// to client, update durability
		ITEMACT_DROPEQUIPMENT,			// to client, delete equipment
		ITEMACT_IMPROVE,				// to server, improve equipment
		ITEMACT_UPLEV			=20,	// to server, upleve equipment
		ITEMACT_BOOTH_QUERY,			// to server, open booth, data is npc id
		ITEMACT_BOOTH_ADD,				// to server/client(broadcast in table), id is idItem, data is money
		ITEMACT_BOOTH_DEL,				// to server/client(broadcast), id is idItem, data is npc id
		ITEMACT_BOOTH_BUY,				// to server, id is idItem, data is npc id
		ITEMACT_SYNCHRO_AMOUNT	=25,	// to client(data is amount)
		ITEMACT_FIREWORKS,				
		
		ITEMACT_COMPLETE_TASK,			// to server, ���Ӷ������, id=����ID, dwData=�ύ����Ʒ�����û����ΪID_NONE
		ITEMACT_EUDEMON_EVOLVE,			// to server, ���޽���, id=������ƷID��dwData=�����ɵ����ͣ�ȡֵ��Χ1~2
		ITEMACT_EUDEMON_REBORN,			// to server, ���޸��id=������ƷID, data=��ʯID
		ITEMACT_EUDEMON_ENHANCE	=30,	// to server, ����ǿ����id=������ƷID, data=��ʯID
		ITEMACT_CALL_EUDEMON,			// to server, �ٻ����ޣ�id=������ƷID
		ITEMACT_KILL_EUDEMON,			// to server, �ջػ��ޣ�id=������ƷID
										// to client, �ջػ��޵Ĺ�Ч���֣�id=������ƷID, dwData=����ID
		ITEMACT_EUDEMON_EVOLVE2,		// to server, ���޶��ν���, id=������ƷID��dwData=�����ɵ����ͣ�ȡֵ��Χ1~8
		ITEMACT_EUDEMON_ATKMODE,		// to server, ���û��޹���ģʽ, id=������ƷID��dwData=����ģʽ��ȡֵ��Χ1~3
		ITEMACT_ATTACH_EUDEMON	=35,	// �������˺���, id=������ƷID
		ITEMACT_DETACH_EUDEMON,			// ����������˺���״̬, id=������ƷID
};

class CMsgItem : public CNetMsg  
{
public:
	CMsgItem();
	virtual ~CMsgItem();

	BOOL	Create	(OBJID id, int nAction, int nPosition = ITEMPOSITION_NONE);
//	BOOL	Create	(DWORD dwData, int nAction);

public:	
	BOOL	Create		(char* pMsgBuf, DWORD dwSize);
	void	Process		(void* pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID		id;
		union {
			DWORD		dwData;
			struct {
				USHORT	usPosY;
				USHORT	usPosX;
			};	
		};
		USHORT		usAction;
		OBJID		idTarget;	// Ŀ�����ID��ID_NONE��ʾ�Լ�
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGITEM_H__9AB1BCEA_F6D1_4413_A39D_8AC35C9FF655__INCLUDED_)
