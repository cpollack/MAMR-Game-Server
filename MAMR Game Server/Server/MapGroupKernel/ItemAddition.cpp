// ItemAddition.cpp: implementation of the CItemAddition class.
//
//////////////////////////////////////////////////////////////////////

#include "ItemAddition.h"
#include "i_mydb.h"
#include "Item.h"

MYHEAP_IMPLEMENTATION(CItemAddition,s_heap)
char szItemAdditionTable[] = _TBL_ITEMADDITION;		//"cq_itemaddition";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemAddition::CItemAddition()
{
	m_setAddition = NULL;
}

CItemAddition::~CItemAddition()
{
	if (m_setAddition)
		m_setAddition->Release();
}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
bool CItemAddition::Create(IDatabase* pDb)
{
	IF_NOT (pDb)
		return false;

	m_setAddition	= CItemAdditionSet64::CreateNew(true);
	IF_NOT (m_setAddition)
		return false;

	char szSQL[1024];
	sprintf(szSQL, "SELECT * FROM %s", _TBL_ITEMADDITION);
	IF_NOT_(m_setAddition->Create(szSQL, pDb))
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
CItemAdditionData* CItemAddition::QueryItemAddition(OBJID idType, int nLevel)
{
	OBJID idKey = idType;
	
/*
	if (CItem::IsMSword(idType) || CItem::IsBow(idType))
	{
		// �����͹������޸ģ�ֱ��ʹ��type
	}
	else if (CItem::IsWeapon1(idType))
	{
		idKey = (idType/100000)*100000 + idType % 1000 + 44000;	// �̱���ͳһ��444***����
	}
	else if (CItem::IsWeapon2(idType))
	{
		idKey = (idType/100000)*100000 + idType % 1000 + 55000;	// ������ͳһ��555***����
	}
	else if (CItem::IsHelmet(idType) || CItem::IsArmor(idType) || CItem::IsShield(idType))
	{
		idKey = (idType/1000)*1000 + idType % 100;				// ͷ�����·�������ͳһ�ѱ�ʾ��ɫ�İ�λ��0
	}
*/

	_int64	key = (idKey / 10) * 10;	// ��������ƷƷ�ʣ����һλȫ����0 -- zlong 2004-02-08
	key = (key << 32) + nLevel;
	return m_setAddition->GetObj(key);
}