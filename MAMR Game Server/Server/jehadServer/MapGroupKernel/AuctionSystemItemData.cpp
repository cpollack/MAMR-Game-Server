// AuctionSystemItemData.cpp: implementation of the CAuctionSystemItemData class.
//
//////////////////////////////////////////////////////////////////////

#include "AuctionSystemItemData.h"
#include "MapGroup.h"
#include "ItemType.h"

char szAuctionsystemTable[]	= _TBL_AUCTION_SYSTEM;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MYHEAP_IMPLEMENTATION(CAuctionSystemItemData, s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAuctionSystemItemData::CAuctionSystemItemData()
{
	m_SystemData_set.empty();
}
CAuctionSystemItemData::~CAuctionSystemItemData()
{
    this->CleanDataSet();
}
void CAuctionSystemItemData::CleanDataSet()
{
	AUCTION_DATA_SET::iterator it=m_SystemData_set.begin();
	for (; it!=m_SystemData_set.end(); it++)
	{
		CGameAuctionSystemData* pData = *it;
		SAFE_RELEASE (pData);
	}
	m_SystemData_set.clear();
}
CGameAuctionSystemData* CAuctionSystemItemData::GetItemDataByID(int id)
{
	AUCTION_DATA_SET::iterator it=m_SystemData_set.begin();
	for (; it!=m_SystemData_set.end(); it++)
	{
		CGameAuctionSystemData* pData = *it;
		if (pData && pData->GetID() == id)
			return pData;
	}
	return NULL;
}
CGameAuctionSystemData* CAuctionSystemItemData::GetItemDataByIndex(int nIndex)
{
	DEBUG_TRY
	AUCTION_DATA_SET::iterator it=m_SystemData_set.begin();
	for(int i=0;it!=m_SystemData_set.end()&&i<nIndex;it++,i++);
	CGameAuctionSystemData* pData = *it;
	if (pData)
		return pData;	
	return NULL;
	DEBUG_CATCH("CAuctionSystemItemData::GetItemDataByIndex(int nIndex) ERROR!")
		return NULL;
}
//����Ҫ��������Ʒ���������Ͳ����������Ʒ
void CAuctionSystemItemData::GetItemDataByDateType(AUCTION_DATA_SET& Data_set,int nType,int nAmount)
{
	DEBUG_TRY
	AUCTION_DATA_SET::iterator it=m_SystemData_set.begin();
	for (int i = 0; i<nAmount&&it!=m_SystemData_set.end(); it++,i++)
	{
		CGameAuctionSystemData* pData = *it;
		if (pData && pData->GetInt(AUCTION_SYSTEMITEM_DATE_TYPE) == nType)
			Data_set.push_back(pData);
	}
	DEBUG_CATCH("CAuctionSystemItemData::GetItemDataByDateType ERRORF")
}

/*--------------------------------------------------------------------
*����������Ʒ�����ͺ����ڲ�������ϵͳ������Ʒ
*idNpc��Ϊ����NPC��ID,nDateType��Ϊɸѡ���������� szDate��Ϊָ��������
*nAmount:Ϊ��ǰϵͳ��������Ʒ���������nMaxType��ϵͳ����������������
*��Ʒ���б������¿�ʼһ���µ�ϵͳ����ʱҪ�����
*-------------------------------------------------------------------*/
bool CAuctionSystemItemData::Create(IDatabase* pDb,OBJID idNpc,int nAmount,int nMaxType)
{
	DEBUG_TRY
	IF_NOT (pDb)
		return false;
	time_t ltime;
	time( &ltime );
	
	struct tm *pTime;
	pTime = localtime( &ltime ); /* Convert to local time. */
	
	int nCurYear, nCurMonth, nCurDay, nCurWeekDay;//, nCurYearDay;
	nCurYear	=pTime->tm_year+1900;
	nCurMonth	=pTime->tm_mon+1;
	nCurDay		=pTime->tm_mday;
	nCurWeekDay	=pTime->tm_wday;
//	nCurYearDay	=pTime->tm_yday;
	int nCount = 0,nDateTypeTemp = 1;
//	if(isClean)
	this->CleanDataSet();
	char szSQL[1024],szDateTemp[64];
	IRecordset*	pRes = NULL;
	while(nCount < nAmount && nDateTypeTemp <= nMaxType)
	{
		ZeroMemory(szDateTemp,sizeof(szDateTemp));
		switch(nDateTypeTemp)
		{
		case 1://ɸѡ����Ϊĳ��ĳ��ĳ�յ���Ʒ
			sprintf(szDateTemp,"%d-%d-%d",nCurYear,nCurMonth,nCurDay);
			break;
		case 2://ɸѡ����Ϊĳ��ĳ�յ���Ʒ
			sprintf(szDateTemp,"%d-%d",nCurMonth,nCurDay);
			break;
		case 3://ɸѡ����Ϊĳ�յ���Ʒ
			sprintf(szDateTemp,"%d",nCurDay);
			break;
		case 4://ɸѡ����Ϊĳ�ܼ�����Ʒ
			sprintf(szDateTemp,"%d",nCurWeekDay);
			break;
		case 5://������Ʒ
			strcpy(szDateTemp,"0");
            break;
		}
		sprintf(szSQL, "SELECT * FROM %s WHERE auction_id=%d and date_type = %d and date_param = '%s' LIMIT %d", _TBL_AUCTION_SYSTEM, idNpc,nDateTypeTemp,szDateTemp,nAmount);
		pRes = pDb->CreateNewRecordset(szSQL);
		if (pRes)
		{
			nCount += pRes->RecordCount();
			for(int i = 0; i < pRes->RecordCount(); i++)
			{
				OBJID idItemType = pRes->GetInt(AUCTION_SYSTEMITEM_TYPE);
				CItemTypeData* pTypeData = ItemType()->QueryItemType(idItemType);
				IF_NOT (pTypeData)
				{
					LOGWARNING(STR_AUCTION_SYS_ITEM_INVALID, idNpc, idItemType);
					pRes->MoveNext();
					continue;
				}
				
				CGameAuctionSystemData* pData = CGameAuctionSystemData::CreateNew();
				IF_NOT (pData)
				{
					pRes->Release();
					return false;
				}
				
				IF_NOT (pData->Create(pRes))
				{
					pData->Release();
					pRes->Release();
					return false;
				}	
				m_SystemData_set.push_back(pData);
				pRes->MoveNext();
			}
		}
		nDateTypeTemp++;
	}
	pRes->Release();
	return true;
	DEBUG_CATCH("CAuctionSystemItemData::Create")
		return false;
}
//////////////////////////////////////////////////////////////////////
bool CAuctionSystemItemData::DeleteRecord(int id)
{
	DEBUG_TRY
	AUCTION_DATA_SET::iterator it=m_SystemData_set.begin();
	for (; it!=m_SystemData_set.end(); it++)
	{
		CGameAuctionSystemData* pData = *it;
		if (pData->GetID() == id)
		{
			if (!pData->DeleteRecord())
				return false;
			m_SystemData_set.erase(it);
			SAFE_RELEASE (pData);
			return true;
		}
	}
	return false;
	DEBUG_CATCH("CAuctionSystemItemData::DeleteRecord ERROR")
		return false;
}
