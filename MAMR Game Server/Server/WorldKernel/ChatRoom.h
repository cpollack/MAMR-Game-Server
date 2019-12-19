// ChatRoom.h: interface for the CChatRoom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATROOM_H__BB957C1F_A8DF_4BEB_9859_89E17BECD25F__INCLUDED_)
#define AFX_CHATROOM_H__BB957C1F_A8DF_4BEB_9859_89E17BECD25F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UserList.h"
#include <string>
#define MAX_FEE	200	//����Ա���õķ��õ����ֵ

class CChatRoom  
{
private:
	struct stPlayerInfo
	{
		int nOrder ;
		CPlayer *pPlayer;
		int      nPoint;
		CTimeOut m_tmPoint;		//���������ӵļ��ʱ��		
	};

	struct stApplyManagerEntity //�������Աʱ�������Ϣ
	{
		CPlayer * pPlayer;
		int nOrder;
		int nPoint;
	};

private:

	CTimeOut m_tmFee;			//�շ�ʱ����
	CTimeOut m_tmSetFee;		//������������շѲ�����ʱ����
	CTimeOut m_tmCancelManager; //��6��	30����֮�ڣ�����������û�дﵽ30���ˣ�ϵͳ����ȡ����ǰ����Ա�Ĺ����ʸ�
	CTimeOut m_tmManagerOffline;//����Ա���߻������ߺ�ʼ���3���Ӻ���Mû����//��ϵ������ҵĹ���ԱȨ��
	CTimeOut m_tmApplyManagerTimeLimit;
	bool m_bIsApplyManager;		//�Ƿ�����������Ա
	std::string m_sRoomName;	//����������
	DWORD  m_dwManagerID;	//����Ա	
	std::string m_sManagerName;	//����Ա������
	
	int m_nMaxContain;		//�������������		
	int m_nFee;				// �����ҹ���Ա�����õ��շѽ��	

	int m_nRoomID;			//�����ID

	std::vector<stPlayerInfo *> m_vtPlayerInfoSet;
	typedef std::vector<stPlayerInfo*>::iterator ITPLAYERINFO;
	
	std::vector<stApplyManagerEntity *> m_vtApplyManagerSet;	//1�������������Ա����Ҽ���
	typedef std::vector<stApplyManagerEntity*>::iterator ITAPPLYMANAGERSET;
	
private:	
	void CheckFee();
	void CheckPoint();

public:
	CChatRoom();
	virtual ~CChatRoom();

public:
	static CChatRoom* CreateNew();

public:
	MYHEAP_DECLARATION(s_heap)		

public:
	bool Release();
	bool DrawinFee(CPlayer * pPlayer);
	void SendMemberList(CPlayer * pPlayer);
	bool SendMsgToAllExcSelf(world_kernel::CNetMsgW*pMsg,CPlayer * pPlayer);
	const char * GetRoomName();
	void ResetManager();
	void SetFee(int nFee);
	void StartupManagerOfflineTimer();
	bool IsManager(CPlayer* pPlayer);
	CPlayer* GetManager();
	bool IsCanApplyManager();
	bool ApplyManager(CPlayer* pPlayer);
	bool IsExist(CPlayer* pPlayer);
	bool SendMsgToAllPlayer(world_kernel::CNetMsgW*pMsg);
	bool IsFull();
	bool SendSysMsg(CPlayer *pPlayer,char * szBuffer);
	int GetFee();
	int GetRoomID();
	void Init();
	void Clear();
	void OnTimer(time_t tCurr);
	void LeaveRoom(CPlayer * pPlayer);
	void EnterRoom(CPlayer* pPlayer);
	void SetName(const char * szName);
	void SetID(int nID);
};

#endif // !defined(AFX_CHATROOM_H__BB957C1F_A8DF_4BEB_9859_89E17BECD25F__INCLUDED_)
