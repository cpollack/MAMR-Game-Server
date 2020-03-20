// MsgItemInfo.cpp: interface for the CMsgItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "AllMsg.h"
#include "../MapGroup.h"
#include "../ItemType.h"
#pragma	warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgItemInfo::CMsgItemInfo()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgItemInfo::~CMsgItemInfo()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgItemInfo::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_ITEMINFO != this->GetType())
		return false;

	return true;
}

/*BOOL CMsgItemInfo::Create(CGameAuctionSystemData* pData, int nAction)
{	
	// init
	CHECKF(pData);
	CItemTypeData* pItemInfo = NULL;
	pItemInfo = ItemType()->QueryItemType(pData->GetInt(AUCTION_SYSTEMITEM_TYPE));				
	CHECKF(pItemInfo);
	this->Init();
	
	// fill info now
	m_pInfo->ucAction			= nAction;	
	m_pInfo->id					= pData->GetID();	
	m_pInfo->dwType				= pData->GetInt(AUCTION_SYSTEMITEM_TYPE);
	m_pInfo->ucIdent			= _ITEM_STATUS_NOT_IDENT;
	m_pInfo->usAmount			= pData->GetInt(AUCTION_SYSTEMITEM_AMOUNT);
	m_pInfo->usAmountLimit		= pData->GetInt(AUCTION_SYSTEMITEM_AMOUNTLIMIT);
	m_pInfo->ucIdent			= pData->GetInt(AUCTION_SYSTEMITEM_IDENT);
	m_pInfo->ucGem1				= pData->GetInt(AUCTION_SYSTEMITEM_GEM1);
	m_pInfo->ucGem2				= pData->GetInt(AUCTION_SYSTEMITEM_GEM2);
	m_pInfo->ucMagic1			= pData->GetInt(AUCTION_SYSTEMITEM_MAGIC1);
	m_pInfo->ucMagic2			= pData->GetInt(AUCTION_SYSTEMITEM_MAGIC2);
	m_pInfo->ucMagic3			= pData->GetInt(AUCTION_SYSTEMITEM_MAGIC3);
	m_pInfo->nData				= pData->GetInt(AUCTION_SYSTEMITEM_DATA);
	m_pInfo->dwWarGhostExp      = pData->GetInt(AUCTION_SYSTEMITEM_WARGHOSTEXP);
	m_pInfo->dwGemAtkType       = pData->GetInt(AUCTION_SYSTEMITEM_GEMTYPE);
	m_pInfo->dwAvailabeTime     = pData->GetInt(AUCTION_SYSTEMITEM_AVAILABLETIME);		
	m_StrPacker.AddString(pItemInfo->GetStr(ITEMTYPEDATA_NAME));
	m_unMsgType	=_MSG_ITEMINFO;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();
	return true;
}*/

//////////////////////////////////////////////////////////////////////
BOOL CMsgItemInfo::Create(CItem* pItem, int nAction /*= ITEMINFO_ADDITEM*/, OBJID idUser/*=ID_NONE*/)
{
	CHECKF(pItem);
	ItemInfoStruct info;
	CHECKF(pItem->GetInfo(&info));

	// init
	this->Init();

	// fill info now
	m_pInfo->dwAction = nAction;
	m_pInfo->idPlayer = idUser;
	strcpy(m_pInfo->szName, info.szName);
	strcpy(m_pInfo->szInventor, info.szInventor);

	m_pInfo->id	= info.id;
	if(idUser != ID_NONE)
		m_pInfo->id	= idUser;
	m_pInfo->dwCost = info.cost;
	m_pInfo->wLook = info.look;
	m_pInfo->wSort = info.sort;
	
	m_pInfo->dwLevelReq = info.levelReq;
	m_pInfo->wLife = info.life;
	m_pInfo->wPower = info.power;
	m_pInfo->wAttack = info.attack;
	m_pInfo->wDefence = info.defence;
	m_pInfo->wDexterity = info.dexterity;

	m_unMsgType	=_MSG_ITEMINFO;
	m_unMsgSize	=sizeof(MSG_Info);

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgItemInfo::Process(void *pInfo)
{
	ASSERT(!"CMsgItemInfo::Process()");
	return;

#ifdef _MSGDEBUG
	::LogMsg("Process CMsgItemInfo, id:%u", m_info.id);
#endif
}
