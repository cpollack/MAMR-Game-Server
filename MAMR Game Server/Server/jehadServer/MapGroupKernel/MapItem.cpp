// MapItem.cpp: implementation of the CMapItem class.
//
//////////////////////////////////////////////////////////////////////

#include "AllMsg.h"
#include "MapItem.h"
#include "MapGroup.h"
#include "ItemData.h"

MYHEAP_IMPLEMENTATION(CMapItem,s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapItem::CMapItem()
{
	SetObjType(OBJ_MAPITEM);
	memset(&m_Info, 0, sizeof(m_Info));

	m_pMap = NULL;
}

//////////////////////////////////////////////////////////////////////
CMapItem::~CMapItem()
{
	if (m_pMap)
	{
		m_pMap->LeaveRoom(QueryMapThing());

//		CMsgMapItem	msg;
//		if(msg.Create(MSGMAPITEM_DELETE, this))
//			m_pMap->BroadcastBlockMsg(QueryMapThing(), &msg);
		BroadcastSet(false);
	}
}

//////////////////////////////////////////////////////////////////////
// modifyed by zlong 2003-11-19
// ��������magic2,magic3��Ĭ�ϲ���
bool CMapItem::Create(OBJID idNewMapItem, CGameMap* pMap, POINT pos, OBJID idType, OBJID idOwner, int nMagic2, int nMagic3, bool bUnIdent, int nUserLuck)		// �����
{
	CHECKF(pMap);
	CHECKF(idType != ID_NONE);

	CItemTypeData* pType = ItemType()->QueryItemType(idType);
	if(!pType)
	{
		LOGWARNING("�������Ʒ���󣺴����item_type[%u]!", idType);
		return false;
	}

	m_tAlive.SetInterval(MAPITEM_MONSTER_ALIVESECS);
	m_tAlive.Update();
	m_pMap		= pMap;
	m_nPosX		= pos.x;
	m_nPosY		= pos.y;

	memset(&m_Info, 0, sizeof(m_Info));
	m_id			= idNewMapItem;
	m_Info.id			= ID_NONE;
	m_Info.idType		= pType->GetKey();
	m_Info.idOwner		= ID_NONE;
	m_Info.idPlayer		= idOwner;
	m_Info.nAmount		= pType->GetInt(ITEMTYPEDATA_AMOUNT);
	m_Info.nAmountLimit		= pType->GetInt(ITEMTYPEDATA_AMOUNT_LIMIT);

	if(m_Info.nAmount > 1)
	{
		int nRate = 50 - nUserLuck;
		if (::RandGet(100) < nRate)
			m_Info.nAmount = m_Info.nAmount * (::RandGet(15) + 20) / 100;
		else
			m_Info.nAmount = m_Info.nAmount * (::RandGet(15) + 35) / 100;
		m_Info.nAmount = ::CutTrail(1, m_Info.nAmount);
	}

	m_Info.nIdent		= pType->GetInt(ITEMTYPEDATA_IDENT);
	m_Info.nPosition	= ITEMPOSITION_GROUND;
	if (CItem::IsSprite(idType))
	{
		// ��Ծ��� -- �����ɳ��� -- add by zlong 2003-12-01
		// �ɳ����� -0.2 ~ +0.2 ��Χ֮���������
		int nGrowth			= pType->GetInt(ITEMTYPEDATA_GROWTH_ORIGINAL) + ::RandGet(41) - 20;
		if (CItem::GetSpriteType(idType) == _SPRITE_ADDITION_SOUL)
			nGrowth			= __min(MAX_SOUL_SPRITE_GROWTH, nGrowth);
		else
			nGrowth			= __min(MAX_SPRITE_GROWTH, nGrowth);
		nGrowth			= __max(0, nGrowth);
		m_Info.nData	= nGrowth;
	}
	else if (CItem::IsEudemon(idType) || CItem::IsEudemonEgg(idType))
	{
		// TODO: ��Ի��ޣ������ɳ���ϵ�� 0.5 ~ 1.5֮�両��
		int nGrowth = 50 + ::RandGet(11)*10;
		m_Info.nData	= nGrowth;

		// ���ܶ�
		int nFidelity	= 450 + ::RandGet(100);
		m_Info.nAmount	= nFidelity;

		// ���Լ��������Ѫ�Ƕ��٣���ʱ��������ϴ�ֵ
		// �������ٻ�����������GetLife�ӿڵ�ʱ���������MaxLife���Զ�CutOverflow��
		m_Info.dwWarGhostExp	= 0x7FFFFFFF;
	}
	else
		m_Info.nData	= 0;

	m_Info.nGem1		= pType->GetInt(ITEMTYPEDATA_GEM1);
	m_Info.nGem2		= pType->GetInt(ITEMTYPEDATA_GEM2);
	m_Info.nMagic1		= pType->GetInt(ITEMTYPEDATA_MAGIC1);

	if (nMagic2)
		m_Info.nMagic2	= nMagic2;
	else
		m_Info.nMagic2	= pType->GetInt(ITEMTYPEDATA_MAGIC2);

	if (nMagic3)
		m_Info.nMagic3	= nMagic3;
	else
		m_Info.nMagic3	= pType->GetInt(ITEMTYPEDATA_MAGIC3);

	if (bUnIdent)
		m_Info.nIdent	|= _ITEM_STATUS_NOT_IDENT;

	if(idOwner != ID_NONE)
	{
		m_tPriv.SetInterval(MAPITEM_PRIV_SECS);
		m_tPriv.Update();
	}

	// �����ͼ
	m_pMap->EnterRoom(QueryMapThing());

	// �ͻ���ͬ�� ���� �������BroadcastShow()����Ϊ��ʱ��δ����MapItem��������Լ��޷���ѯ��
	BroadcastShow();
	BroadcastSet(true);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CMapItem::Create(OBJID idNewMapItem, CGameMap* pMap, POINT pos, ItemInfoStruct* pInfo, OBJID idOwner)			// ��ҵ�
{
	CHECKF(pMap);
	CHECKF(pInfo);

	// ������ʱ��
	CItemTypeData* pType = ItemType()->QueryItemType(pInfo->idType);
	int nAliveSecs = MAPITEM_USERMAX_ALIVESECS;
	if(pType)
		nAliveSecs = pType->GetInt(ITEMTYPEDATA_PRICE)/MAPITEM_ALIVESECS_PERPRICE + MAPITEM_USERMIN_ALIVESECS;
	if(nAliveSecs > MAPITEM_USERMAX_ALIVESECS)
		nAliveSecs = MAPITEM_USERMAX_ALIVESECS;

	m_tAlive.SetInterval(nAliveSecs);
	m_tAlive.Update();
	m_pMap		= pMap;
	m_nPosX		= pos.x;
	m_nPosY		= pos.y;

	memcpy(&m_Info, pInfo, sizeof(m_Info));
	m_id			= idNewMapItem;
	m_Info.idOwner		= ID_NONE;
	m_Info.idPlayer		= idOwner;
	m_Info.nPosition	= ITEMPOSITION_GROUND;
	::SafeCopy(m_Info.szName, pInfo->szName, _MAX_NAMESIZE);

	if(idOwner != ID_NONE)
	{
		m_tPriv.SetInterval(MAPITEM_PRIV_SECS);
		m_tPriv.Update();
	}

	// �����ͼ
	m_pMap->EnterRoom(QueryMapThing());

	// �ͻ���ͬ�� ���� �������BroadcastShow()����Ϊ��ʱ��δ����MapItem��������Լ��޷���ѯ��
	BroadcastShow();
	BroadcastSet(true);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CMapItem::CreateMoney(OBJID idNewMapItem, CGameMap* pMap, POINT pos, DWORD dwMoney, OBJID idOwner /*= ID_NONE*/)			// idOwner��ID_NONE����ҵ�
{
	CHECKF(pMap);
	CHECKF(idNewMapItem);
//	if(dwMoney <= 0)	// || nMoney > DROPMONEY_LIMIT)	-- ʥսȡ����Ǯ��������
//		return false;

	// ������ʱ��
	int nAliveSecs = MAPITEM_MONSTER_ALIVESECS;
	if(idOwner == ID_NONE)
	{
		nAliveSecs = dwMoney/MAPITEM_ALIVESECS_PERPRICE + MAPITEM_USERMIN_ALIVESECS;
		if(nAliveSecs > MAPITEM_USERMAX_ALIVESECS)
			nAliveSecs = MAPITEM_USERMAX_ALIVESECS;
	}

	m_tAlive.SetInterval(nAliveSecs);
	m_tAlive.Update();
	m_pMap		= pMap;
	m_nPosX		= pos.x;
	m_nPosY		= pos.y;

	OBJID idType = ID_NONE;
	if(dwMoney <= SMALLHEAPMONEY_LIMIT)
		idType	= SMALLHEAPMONEY_TYPE;
	else if(dwMoney <= MIDDLEHEAPMONEY_LIMIT)
		idType	= MIDDLEHEAPMONEY_TYPE;
	else if(dwMoney <= BIGHEAPMONEY_LIMIT)
		idType	= BIGHEAPMONEY_TYPE;
	else if(dwMoney <= SMALLHEAPGOLD_LIMIT)
		idType	= SMALLHEAPGOLD_TYPE;
	else if(dwMoney <= MIDDLEHEAPGOLD_LIMIT)
		idType	= MIDDLEHEAPGOLD_TYPE;
	else
		idType	= BIGHEAPGOLD_TYPE;

	memset(&m_Info, 0, sizeof(m_Info));
	m_id			= idNewMapItem;
	m_Info.id			= ID_NONE;
	m_Info.idType		= idType;
	m_Info.idOwner		= ID_NONE;
	m_Info.idPlayer		= idOwner;
	m_Info.nAmount		= dwMoney;
	m_Info.nAmountLimit		= 0xFFFFFFFF;	// DROPMONEY_LIMIT; -- ʥսȡ����Ǯ���ޣ������Ϊ���ֵ
	m_Info.nIdent		= 0;
	m_Info.nPosition	= ITEMPOSITION_GROUND;
	m_Info.nData		= 0;
	m_Info.nGem1		= 0;
	m_Info.nGem2		= 0;
	m_Info.nMagic1		= 0;
	m_Info.nMagic2		= 0;
	m_Info.nMagic3		= 0;

	if(idOwner != ID_NONE)
	{
		m_tPriv.SetInterval(MAPITEM_PRIV_SECS);
		m_tPriv.Update();
	}

	// �����ͼ
	m_pMap->EnterRoom(QueryMapThing());

	// �ͻ���ͬ�� ���� �������BroadcastShow()����Ϊ��ʱ��δ����MapItem��������Լ��޷���ѯ��
	BroadcastShow();
	BroadcastSet(true);

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMapItem::SendShow(IRole* pRole)
{
	CHECK(m_pMap);

	CMsgMapItem	msg;
	if(msg.Create(MSGMAPITEM_CREATE, this))
		pRole->SendMsg(&msg);
}

//////////////////////////////////////////////////////////////////////
void CMapItem::BroadcastShow()
{
	CHECK(m_pMap);

	CMsgMapItem	msg;
	if(msg.Create(MSGMAPITEM_CREATE, this))
		m_pMap->BroadcastBlockMsg(QueryMapThing(), &msg);
}
//////////////////////////////////////////////////////////////////////
void CMapItem::BroadcastSet(bool bEnter)
{
	CHECK (m_pMap);

	int x,y,z;
	IRole*	pRole = NULL;
	CUser* pTargetUser = NULL;
	FOR_9_BLOCKTHINGS(m_pMap, GetPosX(), GetPosY())
	{
		IMapThing* pTarget = m_pMap->QueryThingByIndex(x,y,z);
		if(pTarget && pTarget->QueryObj(OBJ_USER, IPP_OF(pTargetUser)))
		{
			if(abs(pTarget->GetPosX() - GetPosX()) <= CELLS_PER_VIEW
				&& abs(pTarget->GetPosY() - GetPosY()) <= CELLS_PER_VIEW )
			{
				if (bEnter)
					pTargetUser->AddToBCMapItemSet(GetID());
				else
					pTargetUser->RemoveFromBCMapItemSet(GetID());
			}
		}
	}
}