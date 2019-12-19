// NpcShop.cpp: implementation of the CNpcShop class.
//
//////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "define.h"
#include "NpcShop.h"
#include "MapGroup.h"
#include "npc.h"

//////////////////////////////////////////////////////////////////////
const int	SYNSHOP_REBATE_PERCENT				= 90;		// �����̵����

MYHEAP_IMPLEMENTATION(CNpcShop,s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNpcShop::CNpcShop()
{
	m_setGoods	= NULL;
}

//////////////////////////////////////////////////////////////////////
CNpcShop::~CNpcShop()
{
	if(m_setGoods)
		m_setGoods->Release();
}

//////////////////////////////////////////////////////////////////////
bool CNpcShop::Create(PROCESS_ID idProcess, CNpc* pOwner, OBJID idNpc)
{
	m_idProcess	= idProcess;
	m_pOwner	= pOwner;

	m_setGoods	= CGoodsSet::CreateNew(false);

	enum SHOPDATA { SHOPDATA_OWNERID=1, SHOPDATA_ITEMTYPE, };
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s WHERE ownerid=%u", _TBL_GOODS, idNpc);
	IRecordset* pRes = Database()->CreateNewRecordset(szSQL, false);
	if(!pRes)
		return true;		// ��SHOPû�л�

	for(int i = 0; i < pRes->RecordCount(); i++)
	{
		OBJID	idType = pRes->GetInt(SHOPDATA_ITEMTYPE);
		CItemTypeData* pType = ItemType()->QueryItemType(idType);
		if(!pType || m_setGoods->GetObj(pType->GetID()))
		{
			LOGWARNING("�̵�[%u]�з��ַǷ��Ļ��ظ���itemtypeֵ[%u]", idNpc, idType);

			pRes->MoveNext();
			continue;
		}

		m_setGoods->AddObj(pType);
		pRes->MoveNext();
	}
	pRes->Release();

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CNpcShop::IsOpen()	{ 
	//return !(//m_pOwner->IsSynNpc() && 
	//	m_pOwner->GetMap()->GetSynID() != ID_NONE); 
	return false;
}

//////////////////////////////////////////////////////////////////////
int CNpcShop::Rebate(int nPrice, OBJID idSyn, int nRankShow)
{
	OBJID idOwnerSyn = m_pOwner->GetSynID();
	if(idOwnerSyn != ID_NONE && idSyn == idOwnerSyn)
	{
		int nRebate = m_pOwner->GetInt(NPCDATA_DATA0);
		
		return MulDiv(nPrice, nRebate, 100);
	}

	return nPrice;
}









