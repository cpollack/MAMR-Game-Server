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
		ITEMACT_USE,					// to server
		ITEMACT_BUY,					// to server, id: idNpc, data: idItemType
		ITEMACT_SELL,	 				// to server, id: idNpc, data: idItem
		ITEMACT_DROP,					// to server, x, y
		ITEMACT_UNEQUIP = 10,

		//Not used or not known
		ITEMACT_EQUIP,		// to client，通知装备物品
		ITEMACT_SPLITITEM,				// to server, data: num
		ITEMACT_COMBINEITEM,			// to server, data: id
		ITEMACT_QUERYMONEYSAVED,		// to server/client, id: idNpc, data: nMoney
		ITEMACT_SAVEMONEY		=10,	// to server, id: idNpc, data: nMoney
		ITEMACT_DRAWMONEY,				// to server, id: idNpc, data: nMoney
		ITEMACT_DROPMONEY,	 			// to server, x, y
		ITEMACT_SPENDMONEY,				// 无意义，暂保留
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
		
		ITEMACT_COMPLETE_TASK,			// to server, 完成佣兵任务, id=任务ID, dwData=提交的物品，如果没有则为ID_NONE
};

class CMsgItem : public CNetMsg  
{
public:
	CMsgItem();
	virtual ~CMsgItem();

//	BOOL	Create	(OBJID id, int nAction, int nPosition = ITEMPOSITION_NONE);
	BOOL	Create	(DWORD dwData, int nAction);

public:	
	BOOL	Create		(char* pMsgBuf, DWORD dwSize);
	void	Process		(void* pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID		id;
		/*union {
			DWORD		dwData;
			struct {
				USHORT	usPosY;
				USHORT	usPosX;
			};	
		};*/
		DWORD		usAction;
		//OBJID		idTarget;	// target ID，ID_NONE = self
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGITEM_H__9AB1BCEA_F6D1_4413_A39D_8AC35C9FF655__INCLUDED_)
