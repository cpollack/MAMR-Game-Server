// Package.h: interface for the CPackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKAGE_H__DBC395BA_5C4A_40B5_944A_329D547BFBE5__INCLUDED_)
#define AFX_PACKAGE_H__DBC395BA_5C4A_40B5_944A_329D547BFBE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Item.h"
#include "GameObjSet.h"
#include "Myheap.h"
#include <vector>
//////////////////////////////////////////////////////////////////////
enum {
		_STORE_NONE				=0, 
		_STORE_NPCITEM			=ITEMPOSITION_STORAGE,
		_STORE_TRUNKITEM		=ITEMPOSITION_TRUNK,
		_STORE_USERPACK_ITEM	=ITEMPOSITION_CHEST,				//	_ITEM_PACKAGE �ٱ��ң�����Ʒ��
		_STORE_EUDEMONBROODER	=ITEMPOSITION_EUDEMON_BROODER,
		_STORE_EUDEMONITEM		=ITEMPOSITION_EUDEMON_STORAGE,
		_STORE_AUCTION          =ITEMPOSITION_AUCTION_STORAGE,
};
enum{
	GOODS,
	MONEY,
};
const int	PACKAGE_LIMIT			= 50;			// һ��package����ܷŶ��ٸ���Ʒ��ע�⣺̫��ʱCMsgPacket���ܳ���1024��
const int   PACKAGE_AUCTION_LIMIT   = 5;          //���򵽵���Ʒ�ֿ����������LW
//////////////////////////////////////////////////////////////////////
typedef	IGameObjSet<CItem>	IItemSet;
typedef	CGameObjSet<CItem>	CItemSet;

class CPackage  
{
protected:
	CPackage();
	virtual ~CPackage();
public:
	static CPackage* CreateNew()							{ return new CPackage; }
	ULONG	Release()										{ delete this; return 0; }

public:
	int GetItemType(int index);
    bool	Create(int nType, OBJID idOwner, OBJID idPlayer, IDatabase* pDb);// ���ظ�����
    CItem*	AuctionGoodsBackOff(OBJID idPlayer,OBJID idItem, bool bUpdate = true);
	virtual bool	CheckIn(CUser* pUser, CItem* pItem, bool bUpdate = true);// �Զ�ͬ���ͻ���
	virtual bool    CheckIn(CItem* pItem){CHECKF(pItem);if(m_setItem->AddObj(pItem)) return true;else return false;}
	virtual CItem*	CheckOut(OBJID idItem);
	virtual CItem*	CheckOut(CUser* pUser, OBJID idItem, bool bUpdate);					// �Զ�ͬ���ͻ���
	bool	SendInfo(CUser* pUser);									// �Զ�ͬ���ͻ���
	bool	IsPlayerPackage()								{ return m_nType == ITEMPOSITION_STORAGE || m_nType == ITEMPOSITION_CHEST 
																	|| m_nType == ITEMPOSITION_EUDEMON_BROODER || m_nType == ITEMPOSITION_EUDEMON_STORAGE
		                                                     /*LW*/ ||m_nType == ITEMPOSITION_AUCTION_STORAGE; }
	int		GetAmount()										{ return m_setItem->GetAmount(); }
	int		GetWeight(OBJID idItem);
	OBJID	GetItemTypeByID(OBJID idItem);
	DWORD	GetItemAmountLimitByID(OBJID idItem);
	//LW�������----------------------------------------
	CItem*	GetItemByIndex(int index){CHECKF(index >= 0 && index < GetAmount());return(m_setItem->GetObjByIndex(index));}
	CItem*  GetItemByID(OBJID idItem){CHECKF(idItem > 0);CHECKF(m_nType != _STORE_NONE);return(m_setItem->GetObj(idItem));}
	bool    CAuctionChip(/*OBJID idNpc,*/OBJID idUser,DWORD value,IRecordset* pRecordset,IDatabase* pDb);//����һ����Ʒ�̣�
	//LW------------------------------------------------
protected:
	IItemSet*	m_setItem;
	int			m_nType;
	OBJID		m_idOwner;
	OBJID		m_idPlayer;
	UCHAR		m_ucType;
protected:
	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_PACKAGE_H__DBC395BA_5C4A_40B5_944A_329D547BFBE5__INCLUDED_)
