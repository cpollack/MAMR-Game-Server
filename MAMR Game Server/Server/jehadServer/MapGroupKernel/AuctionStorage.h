// AuctionStorage.h: interface for the CAuctionStorage class.
// ����ϵͳ�ֿ⣬ֻ��Auction ����   ��LW-   2004-11-26
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUCTIONSTORAGE_H__FE6ABBEB_EFF7_4E89_9782_E1D93D9E95D8__INCLUDED_)
#define AFX_AUCTIONSTORAGE_H__FE6ABBEB_EFF7_4E89_9782_E1D93D9E95D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "I_mydb.h"
#include "T_MyQueue.h"
#include "Package.h"
typedef struct /*AuctionStorageInfo*/{
	int id;              //������Ʒ���id
	int idAuction;       //����Σ���id
	NAMESTR szPlayer;    //������Ʒ����������
	int idPlayer;        //������Ʒ������id
	int idItem;          //������Ʒ��id
	DWORD dwValue;       //������Ʒ�ļ۸�
	int iState;          //���������״̬0��ʾ��ϵͳ��Ʒ��1��ʾ�������Ʒ
//	int itype;
}AUCTION_STORAGE_INFO,*pAUCTION_STORAGE_INFO;
enum{
	SYSTEM_ITEM,  //ϵͳ�������Ʒ
	PLAYER_ITEM,  //��Ҽ������Ʒ
	COMPLETE_ITEM,//���
};
const int   AUCTION_PACKAGE_MAX     = 50 ;    //�����ֿ�ɷŵ��������
const int   AUCTION_INTERVAL= 30 ;            //ÿ�νм۵ļ��
const int   AUCTION_DEGREE_MAX  = 3  ;        //�м۶��ٴγɽ�
const int   AUCTION_SYSTEM_MAX  = 10 ;        //ϵͳÿ�η����������Ʒ����
const int   AUCTION_REVENUE =  3;             //˰��
const int   AUCTION_BROADCAST_BID = 3;        //����೤ʱ��㲥��߳�����Ϣ(������)
class CAuctionStorage  
{
public:
	CAuctionStorage();
	virtual ~CAuctionStorage();
	// interface
public:
	virtual bool	Create			(IRecordset* pRes);
	virtual bool	Create			(OBJID idNpc,int iType,IDatabase* pDb);
	bool	LoadInfo		(IRecord* pRes,pAUCTION_STORAGE_INFO pInfo);
public:	// add del
	OBJID	CreateRecord(OBJID idAuction,const char* szPlayer,OBJID idItem, DWORD dwValue,UCHAR nType, IDatabase* pDb);
	bool	DeleteRecord(OBJID id,IDatabase* pDb);

public:
    pAUCTION_STORAGE_INFO m_pInfo;
    CMyQueue<pAUCTION_STORAGE_INFO> m_SetAuctionQueue;//������Ҽ����������Ʒ
	CMyQueue<pAUCTION_STORAGE_INFO> m_SetSysAuction;  //����ϵͳ�����������Ʒ
};

#endif // !defined(AFX_AUCTIONSTORAGE_H__FE6ABBEB_EFF7_4E89_9782_E1D93D9E95D8__INCLUDED_)
