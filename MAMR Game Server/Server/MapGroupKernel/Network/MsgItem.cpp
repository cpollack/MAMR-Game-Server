// MsgItem.cpp: interface for the CMsgItem class.
//
//////////////////////////////////////////////////////////////////////

#include "AllMsg.h"
#include "MsgItem.h"
#include "../MapGroup.h"
#include "../ItemType.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgItem::CMsgItem()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgItem::~CMsgItem()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgItem::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_ITEM != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgItem::Create(OBJID id, int nAction)
{
	CHECKF(nAction);		// REPAIRALL 不需要 id && 

	// init
	this->Init();
	// fill info now
	m_pInfo->id = id;
	m_pInfo->usAction	= nAction;
	//m_pInfo->dwData		= nPosition;

	m_unMsgType	=_MSG_ITEM;
	m_unMsgSize	=sizeof(MSG_Info);

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgItem::Process(void *pInfo)
{
	CUserPtr pUser = UserManager()->GetUser(this);
	if(!pUser)
		return;

	if(!pUser->IsAlive())
	{
		pUser->SendSysMsg(STR_DIE);
		return ;
	}

	try {
	switch(m_pInfo->usAction)
	{
	//Cleaned
	case ITEMACT_USE:
		{
			//if (m_pInfo->idTarget == ID_NONE || m_pInfo->idTarget == pUser->GetID())
			//{
				//target is always self?
				if (!pUser->UseItem(m_pInfo->id, SYNCHRO_TRUE))
					pUser->SendSysMsg(STR_UNABLE_USE_ITEM);
			//}
			/*else
			{
				if (!pUser->UseItemTo(m_pInfo->idTarget, m_pInfo->id))
					pUser->SendSysMsg(STR_UNABLE_USE_ITEM);
			}*/
		}
		break;

	//OLD
	/*case ITEMACT_BUY:
		{
			pUser->BuyItem(m_pInfo->id, m_pInfo->dwData);
		}
		break;*/
	/*case ITEMACT_SELL:
		{
			pUser->SellItem(m_pInfo->id, m_pInfo->dwData);
		}
		break;*/
	/*case ITEMACT_DROP:
		{
			IF_NOT(pUser->GetDistance(m_pInfo->usPosX, m_pInfo->usPosY) <= USERDROPITEM_RANGE2)
				return ;

			pUser->DropItem(m_pInfo->id, m_pInfo->usPosX, m_pInfo->usPosY);
		}
		break;*/
	/*case ITEMACT_DROPMONEY:
		{
			IF_NOT(pUser->GetDistance(m_pInfo->usPosX, m_pInfo->usPosY) <= USERDROPITEM_RANGE2)
				return ;

			pUser->DropMoney(m_pInfo->id, m_pInfo->usPosX, m_pInfo->usPosY);
		}
		break;*/
	/*case ITEMACT_EQUIP:
		{
			ASSERT(!"ITEMACT_EQUIP");
		}
		break;*/
	/*case ITEMACT_UNEQUIP:
		{
			if(!pUser->UnEquipItem(m_pInfo->dwData, SYNCHRO_TRUE))
				pUser->SendSysMsg(STR_YOUR_BAG_FULL);
		}
		break;*/
	/*case ITEMACT_SPLITITEM:
		{
			if(!pUser->SplitItem(m_pInfo->id, m_pInfo->dwData))		//, true
				pUser->SendSysMsg(STR_YOUR_BAG_FULL);
		}
		break;*/
	/*case ITEMACT_COMBINEITEM:
		{
			pUser->CombineItem(m_pInfo->id, m_pInfo->dwData);		//, true
		}
		break;*/
	/*case ITEMACT_QUERYMONEYSAVED:
		{
			CNpc* pNpc; 
			if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_NPC, m_pInfo->id, IPP_OF(pNpc)))
				return ;
			if(!pNpc->IsStorageNpc())
				return;

			m_pInfo->dwData		= pUser->GetMoneySaved();
			pUser->SendMsg(this);
		}
		break;*/
	/*case ITEMACT_SAVEMONEY:
		{
			CNpc* pNpc; 
			if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_NPC, m_pInfo->id, IPP_OF(pNpc)))
				return ;
			if(!pNpc->IsStorageNpc())
				return;

			pUser->SaveMoney(m_pInfo->dwData, SYNCHRO_TRUE);
		}
		break;*/
	/*case ITEMACT_DRAWMONEY:
		{
			CNpc* pNpc; 
			if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_NPC, m_pInfo->id, IPP_OF(pNpc)))
				return ;
			if(!pNpc->IsStorageNpc())
				return;

			pUser->DrawMoney(m_pInfo->dwData, SYNCHRO_TRUE);
		}
		break;*/
	/*case ITEMACT_SPENDMONEY:
		{
			ASSERT(!"ITEMACT_SPENDMONEY");
		}
		break;*/
	/*case ITEMACT_REPAIR:
		{
			pUser->RepairItem(m_pInfo->id, SYNCHRO_TRUE);
		}
		break;*/
	/*case ITEMACT_REPAIRALL:
		{
			pUser->RepairAll(SYNCHRO_TRUE);
		}
		break;*/
	/*case ITEMACT_IDENT:
		{
			pUser->IdentItem(m_pInfo->id, SYNCHRO_TRUE);
		}
		break;*/
	/*case ITEMACT_IMPROVE:
		{
			pUser->UpEquipmentQuality(m_pInfo->id, m_pInfo->dwData);
		}
		break;*/
	/*case ITEMACT_UPLEV:
		{
			pUser->UpEquipmentLevel(m_pInfo->id, m_pInfo->dwData);
		}
		break;*/
	/*case ITEMACT_BOOTH_QUERY:
		{
			CBooth* pBooth;
			if(!pUser->FindAroundObj(OBJ_BOOTH, m_pInfo->dwData, IPP_OF(pBooth)))		// npc id
				return ;

			pBooth->SendGoods(pUser);
		}
		break;*/
	/*case ITEMACT_BOOTH_ADD:
		{
			if(pUser->QueryBooth())
			{
				if(pUser->QueryBooth()->AddItem(m_pInfo->id, m_pInfo->dwData))
					pUser->SendMsg(this);
			}
		}
		break;*/
	/*case ITEMACT_BOOTH_DEL:
		{
			if(pUser->QueryBooth())
				pUser->QueryBooth()->DelItem(m_pInfo->id);
		}
		break;*/
	/*case ITEMACT_BOOTH_BUY:
		{
			CBooth* pBooth;
			if(!pUser->FindAroundObj(OBJ_BOOTH, m_pInfo->dwData, IPP_OF(pBooth)))		// npc id
				return ;

			pBooth->BuyItem(pUser, m_pInfo->id);
		}
		break;*/
	// 完成佣兵任务 ----- CMsgAction数据不够用，这个命令借用这条消息来处理
	/*case ITEMACT_COMPLETE_TASK:
		{
			pUser->CompleteMercenaryTask(m_pInfo->id, m_pInfo->dwData);
		}
		break;*/
	}
	}catch(...)
	{
		::LogSave("switch(MSGITEM) Action [%d], id [%u]", m_pInfo->usAction, m_pInfo->id);
	}


#ifdef _MSGDEBUG
	::LogMsg("Process CMsgItem, id:%u", m_pInfo->id);
#endif
}

