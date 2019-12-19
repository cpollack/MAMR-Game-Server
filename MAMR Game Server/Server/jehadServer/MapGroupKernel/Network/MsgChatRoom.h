// MsgChatRoom.h: interface for the CMsgChatRoom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGCHATROOM_H__1B68DBCB_769A_43F8_9FC3_1A3E09873759__INCLUDED_)
#define AFX_MSGCHATROOM_H__1B68DBCB_769A_43F8_9FC3_1A3E09873759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	//---jinggy---������ϵͳ---begin
	//�涨��5�������ҵ�ID: 1 ,2,3,4,5

	ACTION_POINT	=0,			   //��ͻ��˸�����ҵ�����ֵ,�ͻ����յ������Ϣ�󣬽��д���
		
	ACTION_FEE_DEDUCT =1,		   //���������۳�������ã�����Ƿ������䴦�����Ϣ��
	ACTION_FEE_INCOME =2,		   //֪ͨ�����ҹ���Ա��ȡ����
		
	ACTION_ENTERROOM_APPLY =3,	   //���������������ң��ͻ��˷��͵���������������ucAmount(Ϊ1),usShort
	ACTION_ENTERROOM_CHECKMONEY =4,//������ҽ��������ң������������ͻ���
	ACTION_ENTERROOM	 =5,    //֪ͨ�ͻ�����ҽ���������
	ACTION_LEAVEROOM	 =6,    //֪ͨ�ͻ�����ҽ���������
		
	ACTION_APPLYMANAGER =7,     //���������ҹ���Ա
	ACTION_SETMANAGER   =8,		//	���������ҹ���Ա
	ACTION_QUITMANAGER =10,         //���������ҹ���Ա

	ACTION_KICKMEMBER =11,         //�������ҳ�Ա

	ACTION_SETFEE =12,			   //���������ҷ���

	ACTION_SETROOMNAME =13,		  //��������������

	ACTION_OFFLINE =14,			   //�������
		
	ACTION_TALK =15,			   //���̸��

	ACTION_MEMBERINFO =16,		//��Ա��Ϣ
	ACTION_UPDATEPOINT =17,		//�����������ֵ
	
	//---jinggy---������ϵͳ---end

};
#include "NetMsg.h"
class CMsgChatRoom  : public CNetMsg
{

private:
	typedef struct 
	{
		MSGHEAD_DEFINE		
		unsigned short	usAction;
		ULONG ulData;	
		char	szBuf[1];
	}MSG_Info;
	
	CNetStringPacker m_sString;

	MSG_Info*	m_pInfo;
public:
	CMsgChatRoom();
	virtual ~CMsgChatRoom();
public:
	void			Process		(void* pSocket);
	bool Create(unsigned short usAction, ULONG ulData=0, const char *  pString=NULL);

};

#endif // !defined(AFX_MSGCHATROOM_H__1B68DBCB_769A_43F8_9FC3_1A3E09873759__INCLUDED_)





















