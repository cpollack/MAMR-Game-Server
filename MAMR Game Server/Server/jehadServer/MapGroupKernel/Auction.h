// Auction.h: interface for the CAuction class.
// ����ϵͳ    ��LW-   2004-11-26
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUCTION_H__983FD325_E569_4AC7_BB51_2C11F613DDBF__INCLUDED_)
#define AFX_AUCTION_H__983FD325_E569_4AC7_BB51_2C11F613DDBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AuctionStorage.h" 
#include "AuctionSystemItemData.h"
#include "TimeOut.h"

//#include "T_MyQueue.h"
class	CUser;
class   IDatabase;
class   IAuction
{
public:
	virtual bool    JoinAuction(OBJID idUser,  OBJID idItem, DWORD dwValue,IDatabase* pDb) PURE_VIRTUAL_FUNCTION_0 //����typeΪ���Ժ�����������ⶫ����ʹ��
	virtual bool	ShoutPrice(OBJID idItem,OBJID idUser, int nMoney)                      PURE_VIRTUAL_FUNCTION_0//�м�
	virtual bool    SendAuctionItemInfo(OBJID idUser,OBJID idItem)                         PURE_VIRTUAL_FUNCTION_0
	virtual void	OnTimer(DWORD nCurr)                                                   PURE_VIRTUAL_FUNCTION
	virtual bool    Create(PROCESS_ID idProcess, OBJID idNpc)                              PURE_VIRTUAL_FUNCTION_0
	virtual void	Release()								                               PURE_VIRTUAL_FUNCTION
	virtual CPackage* QueryPackage()                                                       PURE_VIRTUAL_FUNCTION_0
	virtual bool    SysAuctionStart(char* szInfo)                                          PURE_VIRTUAL_FUNCTION_0
	virtual bool    CheckAuctionState(int nType)                                           PURE_VIRTUAL_FUNCTION_0
};
class   CPackage;
class   CAuctionStorage;
class CAuction:public IAuction //: public CAuctionStorage 
{ 
public: 
	CAuction(PROCESS_ID idProcess);	
	virtual ~CAuction();
public:
	static IAuction*	CreateNew(PROCESS_ID idProcess)		{ return new CAuction(idProcess); }
public:
	//����Ʒ�ŵ����򴦵ȴ�����
	virtual bool    JoinAuction(OBJID idUser,  OBJID idItem, DWORD dwValue,IDatabase* pDb);
	virtual bool	ShoutPrice(OBJID idItem,OBJID idUser, int nMoney);//�м�
	virtual bool    SendAuctionItemInfo(OBJID idUser,OBJID idItem);
	virtual void	OnTimer(DWORD nCurr);  
    virtual bool    Create(PROCESS_ID idProcess, OBJID idNpc);
	virtual void	Release()	{ delete this; }
	virtual bool    SysAuctionStart(char* szInfo);
	virtual bool    CheckAuctionState(int nType);
protected:
	enum	{ 	auction_none=0,auction_bating ,auction_bated, }	m_nState,m_nSysState;//��¼����ĵ�ǰ״̬	
	CPackage* QueryPackage() { ASSERT(m_pPackage); return m_pPackage; }

	int		m_nCountUp;                           //��ǰϵͳ�м۴�����ÿ��ʮ��һ�Σ�
	bool    m_isSysBid;                           //��¼�Ƿ�Ϊϵͳ����
	OBJID   m_idAuction;                          //����Σ��ģɣ�
	UCHAR   m_nCue;                               //�ж��Ƿ�ʼϵͳ����ǰ��ʾ
	int     m_tDay;                               //��¼����ʱ��
	char    m_szInfo[1024];                       //��¼��ʾ����
private:
	void BroadcastListMsg(CNetMsg* pMsg, CUser* pExcludeUser = NULL);  //�㲥��Ϣ
	void BroadcastSysMsg(LPCTSTR szMsg, CUser* pSendSelf= NULL);
protected: // ctrl
	CAuctionSystemItemData* m_SystemItem;
    CAuctionStorage* m_pAuctionInfo;              //���ں����ݿ������
	CPackage*  m_pPackage;                        //����������Ʒ�Ĳֿ�
    pAUCTION_STORAGE_INFO m_pProprietor;	      // ���ڱ��浱ǰ��߼�
    AUCTION_STORAGE_INFO m_Current;               // ���ڱ��浱ǰ������Ʒ��ԭʼ��Ϣ
///////////////////////////////////////////
private:
	time_t	m_tHammer;                            //ÿ��ʮ����һ�¡�
	time_t  m_tBroadcast;                         //ÿ����ͳ��һ�ε�ǰ��߳��ۣ����㲥
	CTimeOut	m_tClock;                         //���ڿ���OnTime()ÿ��ѭ��һ��
protected:
	PROCESS_ID	m_idProcess;
	MYHEAP_DECLARATION(s_heap)
};

#endif // !defined(AFX_AUCTION_H__983FD325_E569_4AC7_BB51_2C11F613DDBF__INCLUDED_)
