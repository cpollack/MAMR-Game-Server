// Auction.cpp: implementation of the CAuction class.
// ����ϵͳ    ��LW-   2004-11-26
//////////////////////////////////////////////////////////////////////

#include "Auction.h"
#include "MapGroup.h"
#include "MsgAuction.h"
#include "UserManager.h"
#include "MsgItemInfo.h"
#include "MsgTalk.h"
//#include <stdio.h>

MYHEAP_IMPLEMENTATION(CAuction, s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAuction::CAuction(PROCESS_ID idProcess)
{
	m_nCountUp = 0 ; 
	m_pProprietor = NULL;
	m_nState = auction_none;
	m_nSysState = auction_none;
	m_idProcess = idProcess;
	m_isSysBid = false;
	strcpy(m_szInfo ,"NULL");
	m_nCue = 0;
	m_tDay = 0;
}

CAuction::~CAuction()
{
	DEBUG_TRY
    if(m_pAuctionInfo)
        SAFE_DELETE(m_pAuctionInfo);
	if(m_SystemItem)
		SAFE_DELETE(m_SystemItem);
	if(m_pPackage)
		m_pPackage->Release();
	DEBUG_CATCH("CAuction::~CAuction() ERROR");
}
bool CAuction::Create(PROCESS_ID idProcess, OBJID idNpc)
{
	ASSERT(idNpc > 0);
	m_idProcess	= idProcess;
	m_idAuction = idNpc;
	DEBUG_TRY
		m_pAuctionInfo = new CAuctionStorage;
	    CHECKF(m_pAuctionInfo);
		m_SystemItem = CAuctionSystemItemData::CreateNew();
		CHECKF(m_SystemItem);
	    m_pPackage = CPackage::CreateNew();
		CHECKF(m_pPackage);
	    m_pAuctionInfo->Create(idNpc,PLAYER_ITEM,Database());
	    m_pPackage->Create(ITEMPOSITION_AUCTION_STORAGE,idNpc,0,Database());
	DEBUG_CATCH("CAuctionStorage Create Error!")
	return true;
}
void CAuction::OnTimer(DWORD nCurr)
{ 
	DEBUG_TRY
	if(!m_tClock.ToNextTime(1))
		return ;
    CMsgAuction nMsg;
	switch(m_nState)
	{		
	case	auction_none://��ʼ�µ�����׼��
		{			
	    if(m_nCue)//���������ϵͳ����ǰ����ʾ���򷵻�
			return;
		ASSERT(m_pAuctionInfo);
		if(!m_pAuctionInfo->m_SetAuctionQueue.size() && !m_pAuctionInfo->m_SetSysAuction.size())
			return;
		if(m_pAuctionInfo->m_SetSysAuction.size())
		{
			if(!m_isSysBid)
				m_isSysBid = true;
			m_pProprietor = m_pAuctionInfo->m_SetSysAuction.pop();
			if(strcmp(m_szInfo,"NULL"))
			{
				BroadcastSysMsg(m_szInfo);
				strcpy(m_szInfo,"NULL");
			}
		}
		else
		{
			if(m_isSysBid)
				m_isSysBid = false;
			m_pProprietor = m_pAuctionInfo->m_SetAuctionQueue.pop();	
		}
		if(m_pProprietor == NULL)
			return ;
		CItemPtr pItem = NULL;		
		if(!m_isSysBid)
		{
			pItem = QueryPackage()->GetItemByID(m_pProprietor->idItem);
			if(!pItem)
			{
				m_pAuctionInfo->DeleteRecord(m_pProprietor->id,Database());
				return;
			}
			m_pProprietor->idPlayer = pItem->GetInt(ITEMDATA_PLAYERID);
		}
 		m_Current.idAuction = m_pProprietor->idAuction;
		strcpy(m_Current.szPlayer,m_pProprietor->szPlayer);
        m_Current.idItem = m_pProprietor->idItem;
		m_Current.idPlayer = m_pProprietor->idPlayer;
		m_Current.dwValue = m_pProprietor->dwValue ;
		if(nMsg.Create(m_pProprietor->szPlayer,m_pProprietor->idItem,m_pProprietor->dwValue,AUCTION_NEW))
		{
			this->BroadcastListMsg(&nMsg,NULL);
			SQLBUF szMsg;
			if(!m_isSysBid)
			   sprintf(szMsg,STR_AUCTION_NEW,m_Current.szPlayer,pItem->GetStr(ITEMDATA_NAME),m_Current.dwValue);
			else
			{
				CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByID(m_Current.idItem);
				CHECK(pData);
				CItemTypeData* pItemInfo = NULL;
				pItemInfo = ItemType()->QueryItemType(pData->GetInt(AUCTION_SYSTEMITEM_TYPE));				
				CHECK(pItemInfo);
				sprintf(szMsg,STR_AUCTION_NEW,m_Current.szPlayer,pItemInfo->GetStr(ITEMTYPEDATA_NAME),m_Current.dwValue);				
			}
			this->BroadcastSysMsg(szMsg,NULL);
		}
		m_nState = auction_bating;
		m_tHammer	= clock() + AUCTION_INTERVAL*CLOCKS_PER_SEC;
		m_tBroadcast = clock() + AUCTION_BROADCAST_BID*CLOCKS_PER_SEC;
		}
		break;
	case	auction_bating:
		{
			if(m_tBroadcast < clock())
			{
				if(nMsg.Create(m_pProprietor->szPlayer,m_pProprietor->idItem,m_pProprietor->dwValue,AUCTION_HINT_USER))
					this->BroadcastListMsg(&nMsg,NULL);
				m_tBroadcast = clock() + AUCTION_BROADCAST_BID*CLOCKS_PER_SEC;
/*
				SQLBUF szMsg;
				sprintf(szMsg,"��ǰ����Ϊ��%d,�����ˣ�%s",m_pProprietor->dwValue,m_pProprietor->szPlayer);
				UserManager()->BroadcastMsg(szMsg);
*/
			}
			if(m_tHammer < clock())
			{
				m_nCountUp++;
				//			ProcessRun(m_nCountUp);//��ʾ
				if(m_nCountUp <= AUCTION_DEGREE_MAX)
				{
					char szName[16];
					if(!m_isSysBid)
					{	
						CItemPtr pItem = QueryPackage()->GetItemByID(m_Current.idItem);
						CHECK(pItem);
						strcpy(szName,pItem->GetStr(ITEMDATA_NAME));
					}
					else
					{
						CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByID(m_Current.idItem);
						CHECK(pData);
						CItemTypeData* pItemInfo = NULL;
						pItemInfo = ItemType()->QueryItemType(pData->GetInt(AUCTION_SYSTEMITEM_TYPE));				
						CHECK(pItemInfo);
						strcpy(szName,pItemInfo->GetStr(ITEMTYPEDATA_NAME));
					}				
					SQLBUF szMsg;
					sprintf(szMsg,STR_AUCTION_BID,szName,m_pProprietor->szPlayer,m_pProprietor->dwValue,m_nCountUp);
					this->BroadcastSysMsg(szMsg);
				if(m_nCountUp == AUCTION_DEGREE_MAX)
					m_nState = auction_bated;
				}
				m_tHammer	= clock() + AUCTION_INTERVAL*CLOCKS_PER_SEC;
			}
		}
		break;
	case	auction_bated:
		//�㲥����Ľ������ĳ����ĳ�۸��ĵ�ĳ��Ʒ��
		if(m_isSysBid&&!m_pAuctionInfo->m_SetSysAuction.size())
            m_nSysState = auction_bated;
		if(nMsg.Create(0,0,AUCTION_HAMMER))
			this->BroadcastListMsg(&nMsg,NULL);
		if(!m_pProprietor)
		{
			LOGERROR("m_pProprietor NULL");
			return ;
		}
		//----------------------------------------------------------------------
		DEBUG_TRY
		if(m_pProprietor->iState == SYSTEM_ITEM)//ϵͳ��Ʒ
		{
			CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByID(m_pProprietor->idItem);
			CHECK(pData);
			if(m_pProprietor->dwValue != m_Current.dwValue)//����ɹ�
			{
				CItemPtr pItem = NULL;
				pItem = CItem::CreateNew();
				pItem->Create(GameDataDefault()->GetGameItemData(), pData->GetInt(AUCTION_SYSTEMITEM_TYPE),
						               m_pProprietor->idPlayer, ITEMPOSITION_AUCTION_STORAGE);
				CHECK(pItem);
				pItem->SetInt(ITEMDATA_OWNERID, m_pProprietor->idPlayer, UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_PLAYERID, m_pProprietor->idPlayer, UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_POSITION, ITEMPOSITION_AUCTION_STORAGE, UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_AMOUNT,pData->GetInt(AUCTION_SYSTEMITEM_AMOUNT), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_AMOUNTLIMIT,pData->GetInt(AUCTION_SYSTEMITEM_AMOUNTLIMIT), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_IDENT,pData->GetInt(AUCTION_SYSTEMITEM_IDENT), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_GEM1,pData->GetInt(AUCTION_SYSTEMITEM_GEM1), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_GEM2,pData->GetInt(AUCTION_SYSTEMITEM_GEM2), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_MAGIC1,pData->GetInt(AUCTION_SYSTEMITEM_MAGIC1), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_MAGIC2,pData->GetInt(AUCTION_SYSTEMITEM_MAGIC2), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_MAGIC3, pData->GetInt(AUCTION_SYSTEMITEM_MAGIC3), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_DATA, pData->GetInt(AUCTION_SYSTEMITEM_DATA), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_WARGHOSTEXP,pData->GetInt(AUCTION_SYSTEMITEM_WARGHOSTEXP), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_GEMTYPE,pData->GetInt(AUCTION_SYSTEMITEM_GEMTYPE), UPDATE_FALSE);
				pItem->SetInt(ITEMDATA_AVAILABLETIME,pData->GetInt(AUCTION_SYSTEMITEM_AVAILABLETIME), UPDATE_TRUE);
				CUser* pUser = UserManager()->GetUser(m_pProprietor->idPlayer);
				//���������ߣ�ͬʱ������ҵ�����ֿ�
				IF_OK(pUser)	
				{
					pUser->AuctionGoodsBackOff(pItem,ITEMPOSITION_AUCTION_STORAGE);
				}
				SQLBUF szMsg;
				char nGoods[32];
				strcpy(nGoods,pItem->GetStr(ITEMDATA_NAME));
				sprintf(szMsg,STR_AUCTION_HAMMER,m_pProprietor->szPlayer,m_pProprietor->dwValue,nGoods);
				this->BroadcastSysMsg(szMsg);
			}
			else//ʧ��
			{
/*				CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByID(m_pProprietor->idItem);
				if(pData)
				    m_SystemItem->DeleteRecord(m_pProprietor->idItem);
*/			}
		}
		else//�����Ʒ
		{
			if(m_pProprietor->dwValue != m_Current.dwValue)//����ɹ�
			{
				CItemPtr pItem = QueryPackage()->GetItemByID(m_pProprietor->idItem);
				if(!pItem)
				{
					LOGERROR("AUCTION QUERY ITEM ERROR");
					return;
				}
				SQLBUF szMsg;
				char nGoods[32];
				strcpy(nGoods,pItem->GetStr(ITEMDATA_NAME));
				sprintf(szMsg,STR_AUCTION_HAMMER,m_pProprietor->szPlayer,m_pProprietor->dwValue,nGoods);
				this->BroadcastSysMsg(szMsg);
				//������Ʒ����
				QueryPackage()->AuctionGoodsBackOff(m_pProprietor->idPlayer,m_pProprietor->idItem,true);
				CUser* pProprietor = UserManager()->GetUser(m_pProprietor->idPlayer);
				if(pProprietor && pItem)
					pProprietor->AuctionGoodsBackOff(pItem,ITEMPOSITION_AUCTION_STORAGE);
				//��Ǯ
				DWORD dMoney = (m_pProprietor->dwValue*(100-AUCTION_REVENUE)+ m_Current.dwValue*AUCTION_REVENUE)/100;
				ASSERT(dMoney > 0);
                CUser* pCurUser = UserManager()->GetUser(m_Current.idPlayer);
				if(pCurUser)
				{
					pCurUser->GainMoney(dMoney, SYNCHRO_TRUE);
					SQLBUF nMsg;
					sprintf(nMsg,STR_AUCTION_BID_SUCCESS,dMoney);
					pCurUser->SendSysMsg(nMsg);
				}
				else
				{
					m_pPackage->CAuctionChip(m_Current.idPlayer,dMoney,GameDataDefault()->GetGameItemData(),Database());		
				}
			}
			else//ʧ��
			{
				CItemPtr pItem = QueryPackage()->GetItemByID(m_pProprietor->idItem);
				if(!pItem)
				{
					LOGERROR("AUCTION QUERY ITEM ERROR");
					return;
				}
				QueryPackage()->AuctionGoodsBackOff(m_Current.idPlayer,m_Current.idItem,true);
				CUser* pUser = UserManager()->GetUser(m_Current.idPlayer);
				//���������ߣ�ͬʱ������ҵ�����ֿ�
				if(pUser && pItem)	
				{
					pUser->SendSysMsg(STR_AUCTION_BID_FAIL);
					pUser->AuctionGoodsBackOff(pItem,ITEMPOSITION_AUCTION_STORAGE);
				}
			}
		}
		DEBUG_CATCH("auction_bated Error!")
		DEBUG_TRY
		m_pAuctionInfo->DeleteRecord(m_pProprietor->id,Database());
		DEBUG_CATCH("m_pAuctionInfo->UpdateRecord ERROR!")
		// ���³�ʼ��
		m_nCountUp	= 0;
		SAFE_DELETE(m_pProprietor);
		m_nState	= auction_none;
		break;
	default:
		LOGERROR("CAuction::OnTimer() �ڲ��쳣");
	}
	DEBUG_CATCH("CAuction::OnTimer(DWORD nCurr)  ERROR");
}
void CAuction::BroadcastListMsg(CNetMsg* pMsg, CUser* pExcludeUser)  //�㲥��Ϣ
{
	UserManager()->BroadcastMapGroupMsg(pMsg,pExcludeUser);
}
/*----------------------------------------
*bool  CAuction::CheckAuctionState(int nType)
*�鿴��ǰ������״̬
*nType:0.��ʾ�鿴ϵͳ������Ʒ��1.��ʾ�鿴�����Ʒ
*������ڽ��У��򷵻�TRUE
*----------------------------------------*/
bool  CAuction::CheckAuctionState(int nType)
{
	switch(nType)
	{
	case SYSTEM_ITEM:
		if(m_nSysState == auction_bating||m_nSysState == auction_none)
            return true;
		if(m_nSysState == auction_bated)
			m_nSysState = auction_none;
/*		if(m_tDay)//����Ѿ����й�ϵͳ�����������ϵͳ���������㲥
		{
			const UCHAR SYS_AUCTION_END = 0;
			m_nCue = SYS_AUCTION_END;
		}*/
		return false;
		break;
	case PLAYER_ITEM:
		{	
			const UCHAR SYS_AUCTION_READY = 3;
			m_nCue = SYS_AUCTION_READY;				
			if(!m_isSysBid&&(m_nState == auction_bating||m_nState == auction_bated))
				return true;	
			return false;
		}
		break;
	default:
		LOGERROR("CheckAuctionState(int nType) Enable Type");
		return false;
		break;
	}
}
/*LW----------------------------------------------------------------------
*bool  CAuction::SysAuctionStart()
*����true��ʾ�ɹ���false��ʾʧ�ܻ�û��ϵͳ������Ʒ
*----------------------------------------------------------------------*/
bool  CAuction::SysAuctionStart(char* szInfo)
{
	DEBUG_TRY
		//��Ϊ�п��ܷ���������ʱ������ϵͳ��Ʒû�������꣬�����ȼ��
		const UCHAR SYS_AUCTION_END = 0;
		if(m_pProprietor&&m_pProprietor->iState == SYSTEM_ITEM)
		{
			m_nCue = SYS_AUCTION_END;
			m_nSysState = auction_bating;
			LOGWARNING(STR_AUCTION_SYS_JOIN_MORETIMES);
			return false;
		}
		//------->ÿ��ֻ�ܽ���һ��ϵͳ����
		time_t ltime;
	    time( &ltime );
	    struct tm *pTime;
	    pTime = localtime( &ltime );
		int nDayTemp = (pTime->tm_year+1900)*10000+(pTime->tm_mon+1)*100+pTime->tm_mday;
		if(nDayTemp == m_tDay)
		{
			LOGWARNING("ϵͳ�����Ѿ����й�ϵͳ������Ҫ�ٽ���ϵͳ�����������������");
			return false;
		}
		//<-------------------------------		
		//����ϵͳ������Ʒ
		strcpy(m_szInfo,szInfo);
		if(m_pAuctionInfo->m_SetSysAuction.size())
			m_pAuctionInfo->m_SetSysAuction.clear();
		const int MAX_DATE_TYPE = 5;
        m_SystemItem->Create(Database(),m_idAuction,AUCTION_SYSTEM_MAX,MAX_DATE_TYPE);
		int nAmount = m_SystemItem->GetAmount();
		if(!nAmount)
		{
			LOGWARNING("û���κ�ϵͳ��Ʒ�������������������Ƿ���ȷ");
		}
		for(int i=0;i<nAmount&&i<AUCTION_SYSTEM_MAX;i++)
		{
			CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByIndex(i);
			CHECKF(pData);
			IF_OK(m_pAuctionInfo->CreateRecord(m_idAuction,"SYSTEM",pData->GetID(),pData->GetInt(AUCTION_SYSTEMITEM_VALUE),SYSTEM_ITEM,Database()))
			{
				m_pAuctionInfo->m_SetSysAuction.push(m_pAuctionInfo->m_pInfo);
			}
		}
		m_tDay = nDayTemp;
		m_nCue = SYS_AUCTION_END;
		m_nSysState = auction_bating;
		LOGWARNING("ϵͳ������ʼ�ɹ�");
		return true;
    DEBUG_CATCH(STR_AUCTION_BID_ERROR)
	return false;
}
//��ҽм�
bool CAuction::ShoutPrice(OBJID idItem,OBJID idUser, int nMoney)
{
	try{
	CUser* pUser = UserManager()->GetUser(idUser);
	ASSERT(pUser);
	if(m_pProprietor->dwValue >= nMoney)
	{
		pUser->SendSysMsg(STR_AUCTION_SHOUTPRICE_LOW);
		return false;
	}
	if(m_pProprietor->idItem != idItem)
	{
		pUser->SendSysMsg(STR_AUCTION_BIDED);
		return false;
	}
	if(m_Current.idPlayer==idUser)
	{
		pUser->SendSysMsg(STR_SHOUT_PRICE_SELF_ERR);
		return false;
	}
	//�˻���һ����ҵ�Ӷ�𡣡�
	if(m_pProprietor->dwValue > m_Current.dwValue)
	{
		CUser* pLastUser = UserManager()->GetUser(m_pProprietor->idPlayer);
		if(pLastUser)
			pLastUser->GainMoney(m_pProprietor->dwValue,true);
		else//����Ҳ�����ң���Ǯ�ŷŲֿ⡣��
		{
		    m_pPackage->CAuctionChip(m_pProprietor->idPlayer,m_pProprietor->dwValue,GameDataDefault()->GetGameItemData(),Database());		
		}
	}
	m_pProprietor->dwValue = nMoney;
	strcpy(m_pProprietor->szPlayer,pUser->GetName());
	m_pProprietor->idPlayer = idUser;
	//��ȡ��ҵĳ���Ǯ��
	pUser->SpendMoney(nMoney,true);
	m_tHammer	= clock() + AUCTION_INTERVAL*CLOCKS_PER_SEC;
	m_nCountUp = 0;
	if(!m_isSysBid)
	{	
		CItemPtr pItem = QueryPackage()->GetItemByID(idItem);
		CHECKF(pItem);
		pUser->SendSysMsg(STR_SHOUT,nMoney,pItem->GetStr(ITEMDATA_NAME));
	}
	else
	{
		CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByID(m_Current.idItem);
		CHECKF(pData);
		CItemTypeData* pItemInfo = NULL;
		pItemInfo = ItemType()->QueryItemType(pData->GetInt(AUCTION_SYSTEMITEM_TYPE));				
		CHECKF(pItemInfo);
		pUser->SendSysMsg(STR_SHOUT,nMoney,pItemInfo->GetStr(ITEMTYPEDATA_NAME));
	}
	return true;
	}
	catch (...) {
		LOGERROR("CAuction::ShoutPrice");
		return false;
	}
}
bool CAuction::SendAuctionItemInfo(OBJID idUser,OBJID idItem)
{
    DEBUG_TRY
	CUserPtr pUser = UserManager()->GetUser(idUser);
	CMsgItemInfo msg;
	CHECKF(pUser);
	if(m_isSysBid)
	{
		CGameAuctionSystemData* pData = m_SystemItem->GetItemDataByID(m_Current.idItem);
        CHECKF(pData);
        if(msg.Create(pData,ITEMINFO_AUCTION))
			pUser->SendMsg(&msg);
	}
	else
	{	
	CItemPtr pItem = QueryPackage()->GetItemByID(idItem);	
	if(pItem && msg.Create(pItem,ITEMINFO_AUCTION))
		pUser->SendMsg(&msg);
	else
		pUser->SendSysMsg(STR_AUCTION_NOT_ITEM);
	}	
	DEBUG_CATCH("CAuction SendAuctionItemInfo Error!");
	return false;
}
const int MIN_VALUE = 100;
bool CAuction::JoinAuction(/*CUser* pUser*/OBJID idUser,  OBJID idItem, DWORD dwValue,IDatabase* pDb)
{
	CUser* pUser = UserManager()->GetUser(idUser);
	ASSERT(pUser);
	if(dwValue < MIN_VALUE)
	{
		pUser->SendSysMsg(STR_AUCTION_MIN_VALUE,MIN_VALUE);
		return false;
	}
	CItem* pItem = pUser->GetItem(idItem);
	if (!pItem)
		return false;
    if(pItem->GetInt(ITEMDATA_MONOPOLY))
	{
		pUser->SendSysMsg(STR_SPECIAL_GOODS_JOIN_ERR);//"������Ʒ��������"
	 	return false;
	}
	// ���������������Ʒ���Ѿ������Ļ��ޣ��������ٻ�
	if (pItem->IsEudemon())
	{
		pUser->CallBackEudemon(pItem->GetID());
		pUser->DetachEudemon(pItem);
	}

/*	if(m_isSysBid)
	{
		pUser->SendSysMsg(STR_AUCTION_SYS_BID);
		return false;
	}*/
	if(m_pAuctionInfo->m_SetAuctionQueue.size() >= AUCTION_PACKAGE_MAX)
	{
		pUser->SendSysMsg(STR_AUCTION_BID_PACKAGE_FULL);
		return false;
	}
	if(pUser->GetMoney() < dwValue*AUCTION_REVENUE/100)
	{
		pUser->SendSysMsg(STR_AUCTION_LESS_MONEY);
		return false;
	}
	if(m_pAuctionInfo->CreateRecord(m_idAuction,pUser->GetName(),idItem,dwValue,PLAYER_ITEM,pDb))
	{
		m_pAuctionInfo->m_SetAuctionQueue.push(m_pAuctionInfo->m_pInfo);
		pUser->SendSysMsg(STR_AUCTION_JOIN_SUCCESS,m_pAuctionInfo->m_SetAuctionQueue.size());
	}
	else
	{
		pUser->SendSysMsg(STR_AUCTION_JOIN_ERROR);
		return false;
	}
	DEBUG_TRY
	pUser->SpendMoney(DWORD(dwValue*3/100), SYNCHRO_TRUE);
	CItem* pTemp = pUser->PopItem(idItem, SYNCHRO_TRUE, UPDATE_FALSE);
	CHECKF(pTemp);
	QueryPackage()->CheckIn(pUser,pTemp,true);
	DEBUG_CATCH("CAuction::JoinAuction ERROR!")
	return true;
}
void CAuction::BroadcastSysMsg(LPCTSTR szMsg, CUser* pSendSelf)
{
	CMsgTalk	msg;	
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		UserManager()->BroadcastMapGroupMsg(&msg, pSendSelf);
}