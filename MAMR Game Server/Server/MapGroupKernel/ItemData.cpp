// ItemData.cpp: implementation of the CItemData class.
//
//////////////////////////////////////////////////////////////////////

#include "ItemData.h"
#include "I_mydb.h"
#include "MapGroup.h"
#include "UserTable.h"
#include "ItemAddition.h"

char	szItemTable[] = _TBL_ITEM;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CItemData::CItemData()
{
	m_pData		= NULL;
	m_pType		= NULL;
    //_pEudemonType	= NULL;
	//m_pAddition	= NULL;
}

//////////////////////////////////////////////////////////////////////
CItemData::~CItemData()
{
	if(m_pData)
		m_pData->Release();
}

//////////////////////////////////////////////////////////////////////
bool CItemData::Create(IRecord* pDefault, const ItemInfoStruct* pInfo, bool bInsert, OBJID idNew)			// false: ²»´æÊý¾Ý¿â
{
	CHECKF(!m_pData);
	CHECKF(!m_pType);
//	CHECKF(!m_pEudemonType);
	CHECKF(pInfo);
	CHECKF(pDefault);

	OBJID idItem = pInfo->id;
	if(idNew)
		idItem = idNew;

	// data
	m_pData = CGameItemData::CreateNew();
	CHECKF(m_pData);
	IF_NOT(m_pData->Create(pDefault, idItem))
		return false;

	if(idNew)
		SetInt(ITEMDATA_ID,		idNew);
	
	m_pData->SetInt(ITEMDATA_COST, pInfo->cost);
	m_pData->SetInt(ITEMDATA_LOOK, pInfo->look);
	m_pData->SetInt(ITEMDATA_SORT, pInfo->sort);
	m_pData->SetInt(ITEMDATA_LEVELREQ, pInfo->levelReq);

	m_pData->SetInt(ITEMDATA_LIFE, pInfo->life);
	m_pData->SetInt(ITEMDATA_POWER, pInfo->power);
	m_pData->SetInt(ITEMDATA_ATTACK, pInfo->attack);
	m_pData->SetInt(ITEMDATA_DEFENCE, pInfo->defence);
	m_pData->SetInt(ITEMDATA_DEXTERITY, pInfo->dexterity);

	m_pData->SetInt(ITEMDATA_ACTION, pInfo->idAction);
	
	m_pData->SetStr(ITEMDATA_NAME, pInfo->szName, _MAX_NAMESIZE);
	m_pData->SetStr(ITEMDATA_INVENTOR, pInfo->szInventor, _MAX_NAMESIZE);

	// db
	if(bInsert)
	{
		IF_NOT(m_pData->InsertRecord())
			return false;
	}
	else
	{
		m_pData->ClearUpdateFlags();
	}

	// item type
	if (pInfo->idType) {
		m_pType = ItemType()->QueryItemType(pInfo->idType);
		//IF_NOT(m_pType)
		//	return false;
	}

	//m_pAddition = ItemAddition()->QueryItemAddition(pInfo->idType, pInfo->nMagic3);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CItemData::Create (IRecord* pDefault, OBJID idType, OBJID idUser, int nPosition)
{
	CHECKF(!m_pData);
	CHECKF(!m_pType);
	CHECKF(idType != ID_NONE);
	CHECKF(pDefault);

	// type
	m_pType	= ItemType()->QueryItemType(idType);
	IF_NOT(m_pType)
		return false;

	//Item id is a combo of user and position
	OBJID idItem = 100000000 + (idUser * 100) + nPosition;

	// data
	m_pData = CGameItemData::CreateNew();
	CHECKF(m_pData);
	IF_NOT(m_pData->Create(pDefault, idItem))
		return false;


	m_pData->SetInt(ITEMDATA_ID, idItem);
	m_pData->SetInt(ITEMDATA_COST, m_pType->GetInt(ITEMTYPEDATA_COST));
	m_pData->SetInt(ITEMDATA_LOOK, m_pType->GetInt(ITEMTYPEDATA_LOOK));
	m_pData->SetInt(ITEMDATA_SORT, m_pType->GetInt(ITEMTYPEDATA_SORT));
	m_pData->SetInt(ITEMDATA_LEVELREQ, m_pType->GetInt(ITEMTYPEDATA_LEVELREQ));

	m_pData->SetInt(ITEMDATA_LIFE, m_pType->GetInt(ITEMTYPEDATA_LIFE));
	m_pData->SetInt(ITEMDATA_POWER, m_pType->GetInt(ITEMTYPEDATA_POWER));
	m_pData->SetInt(ITEMDATA_ATTACK, m_pType->GetInt(ITEMTYPEDATA_ATTACK));
	m_pData->SetInt(ITEMDATA_DEFENCE, m_pType->GetInt(ITEMTYPEDATA_DEFENCE));
	m_pData->SetInt(ITEMDATA_DEXTERITY, m_pType->GetInt(ITEMTYPEDATA_DEXTERITY));

	m_pData->SetInt(ITEMDATA_ACTION, m_pType->GetInt(ITEMTYPEDATA_ACTION));

	m_pData->SetStr(ITEMDATA_NAME, m_pType->GetStr(ITEMTYPEDATA_COST), _MAX_NAMESIZE);
	m_pData->SetStr(ITEMDATA_INVENTOR, m_pType->GetStr(ITEMTYPEDATA_COST), _MAX_NAMESIZE);

	// db
	IF_NOT(m_pData->InsertRecord())
		return false;

	//m_pAddition = ItemAddition()->QueryItemAddition(idType, GetInt(ITEMDATA_ADDITION));

	return true;
}

//////////////////////////////////////////////////////////////////////
/*bool CItemData::Create(OBJID idItem, IDatabase* pDb)
{
	CHECKF(!m_pData);
	CHECKF(!m_pType);
	CHECKF(pDb);

	// data
	m_pData = CGameItemData::CreateNew();
	IF_NOT(m_pData)
		return false;
	IF_NOT(m_pData->Create(idItem, pDb))
		return false;

	// type
	m_pType	= ItemType()->QueryItemType(GetInt(ITEMDATA_TYPE));
	IF_NOT(m_pType)
		return false;

	//m_pAddition = ItemAddition()->QueryItemAddition(GetInt(ITEMDATA_TYPE), GetInt(ITEMDATA_ADDITION));

	return true;
}*/

//////////////////////////////////////////////////////////////////////
bool CItemData::Create(IRecordset* pRes, IDatabase* pDb)
{
	CHECKF(!m_pData);
	CHECKF(!m_pType);
	CHECKF(pRes);
	CHECKF(pDb);

	// data
	m_pData = CGameItemData::CreateNew();
	IF_NOT(m_pData)
		return false;

	IF_NOT(m_pData->Create(pRes))
		return false;

	// type
	/*m_pType	= ItemType()->QueryItemType(type);
	if(!m_pType)
	{
		LOGERROR("Unknown item type in database [%d]", type);
		return false;
	}*/

	//m_pAddition = ItemAddition()->QueryItemAddition(GetInt(ITEMDATA_TYPE), GetInt(ITEMDATA_ADDITION));
	
	return true;
}

//////////////////////////////////////////////////////////////////////
// info
//////////////////////////////////////////////////////////////////////
bool CItemData::GetInfo	(ItemInfoStruct* pInfo)
{
	CHECKF(pInfo);
	CHECKF(GetID() != ID_NONE);

	pInfo->id			= GetID();
	pInfo->cost = m_pData->GetInt(ITEMDATA_COST);
	pInfo->sort = m_pData->GetInt(ITEMDATA_SORT);
	pInfo->look = m_pData->GetInt(ITEMDATA_LOOK);
	pInfo->levelReq = m_pData->GetInt(ITEMDATA_LEVELREQ);

	pInfo->life = m_pData->GetInt(ITEMDATA_LIFE);
	pInfo->power = m_pData->GetInt(ITEMDATA_POWER);
	pInfo->attack = m_pData->GetInt(ITEMDATA_ATTACK);
	pInfo->defence = m_pData->GetInt(ITEMDATA_DEFENCE);
	pInfo->dexterity = m_pData->GetInt(ITEMDATA_DEXTERITY);

	pInfo->idAction = m_pData->GetInt(ITEMDATA_ACTION);

	strcpy(pInfo->szName, m_pData->GetStr(ITEMDATA_NAME));
	strcpy(pInfo->szInventor, m_pData->GetStr(ITEMDATA_INVENTOR));
	
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CItemData::SaveInfo(void)
{
	CHECKF(m_pData);
	CHECKF(m_pType);

	m_pData->Update();

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CItemData::DeleteRecord()
{
	return m_pData->DeleteRecord();
}

//////////////////////////////////////////////////////////////////////
///////////////////////      STATIC      /////////////////////////////
bool CItemData::DeleteItemRecord(OBJID id, IDatabase* pDb)
{
	if (id == ID_NONE || !pDb)
		return false;

	SQLBUF	szSQL;
	sprintf(szSQL, "DELETE FROM %s WHERE id=%u LIMIT 1", _TBL_ITEM, id);
	return pDb->ExecuteSQL(szSQL);
}

//////////////////////////////////////////////////////////////////////
int CItemData::GetInt(ITEMDATA idx)
{
	/*if(IsMount())
	{
		if(idx == ITEMDATA_GEM1)
			return GEM_NONE;
		else if(idx == ITEMDATA_INTIMACY)
			idx = ITEMDATA_GEM1;
	}*/

	//if(idx < ITEMTYPEDATA_OFFSET)
		return m_pData->GetInt(idx);
	
	//return m_pType->GetInt((ITEMTYPEDATA)(idx-ITEMTYPEDATA_OFFSET));
}

//////////////////////////////////////////////////////////////////////
void CItemData::SetInt(ITEMDATA idx, int nData, bool bUpdate/*=false*/)
{
	/*if(IsMount())
	{
		CHECK(idx != ITEMDATA_GEM1);
		if(idx == ITEMDATA_INTIMACY)
			idx = ITEMDATA_GEM1;
	}*/

	//CHECK(idx < ITEMTYPEDATA_OFFSET);
	m_pData->SetInt(idx, nData);
	if(bUpdate)
		m_pData->Update();
}

//////////////////////////////////////////////////////////////////////
LPCTSTR CItemData::GetStr(ITEMDATA idx)
{
	//if(idx < ITEMTYPEDATA_OFFSET)
		return m_pData->GetStr(idx);
	
	//return m_pType->GetStr((ITEMTYPEDATA)(idx-ITEMTYPEDATA_OFFSET));
}

//////////////////////////////////////////////////////////////////////
void CItemData::SetStr(ITEMDATA idx, LPCTSTR szData, int nSize, bool bUpdate /*= false*/)
{
	//CHECK(idx < ITEMTYPEDATA_OFFSET);
	m_pData->SetStr(idx, szData, nSize);
	if(bUpdate)
		m_pData->Update();
}
