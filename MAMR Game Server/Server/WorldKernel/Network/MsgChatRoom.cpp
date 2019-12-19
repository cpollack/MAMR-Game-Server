// MsgChatRoom.cpp: implementation of the CMsgChatRoom class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#include "../UserList.h"
#include "logfile.h"
using namespace world_kernel;
#include "../WorldKernel.h"

#include "../ChatRoom.h"
#include "../ChatRoomManager.h"

#include "MsgChatRoom.h"


//extern CChatRoomManager g_objChatRoomManager;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgChatRoom::CMsgChatRoom()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_sString.SetBuf(m_pInfo->szBuf, _MAX_MSGSIZE-sizeof(MSG_Info)+1);
}

CMsgChatRoom::~CMsgChatRoom()
{

}

//////////////////////////////////////////////////////////////////////
void CMsgChatRoom::Process(void* pSocket)
{
	CPlayer* pUser = UserList()->GetPlayerBySocket(GetSocketID());
	CHECK(pUser);
	char szString[_MAX_WORDSSIZE];
	m_sString.GetString(0, szString, sizeof(szString));
	
	switch( m_pInfo->usAction )
	{
	case ACTION_ENTERROOM_APPLY:	//���������������ң��ͻ��˷��͵���������������
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoom(szString);
			CHECK(pChatRoom);
			if(pChatRoom->IsExist(pUser))
				return;
			if(pChatRoom->IsFull())
			{
				pChatRoom->SendSysMsg(pUser,STR_CHATROOM_MEMBERFULL);
				return;
			}			
			int  nMoney = pChatRoom->GetFee();//�õ��շѽ�Ǯ		
			
			CHECK(Create(ACTION_ENTERROOM_CHECKMONEY,nMoney,szString));

			GameWorld()->SendMapGroupMsgForChatRoom(pUser->idProcess,pUser->idSocket,this);
		}
		break;
	case ACTION_LEAVEROOM:	//�뿪������
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			CHECK(pChatRoom);
			if(!pChatRoom->IsExist(pUser))
				return;
			
			IF_NOT(this->Create(ACTION_LEAVEROOM,0,pUser->szName)) //֪ͨ�ͻ�������뿪����Ϣ
				return;
			
			if(pChatRoom->IsManager(pUser))
				pChatRoom->ResetManager();

			pChatRoom->SendMsgToAllPlayer(this);//֪ͨ�������������
			pChatRoom->LeaveRoom(pUser);			
			
			char szBuff[128];
			sprintf(szBuff,STR_CHATROOM_LEAVE,pUser->szName,pChatRoom->GetRoomName());
			CMsgTalkW msgTalk;
			if (msgTalk.Create(SYSTEM_NAME,ALLUSERS_NAME, szBuff, NULL, 0xff0000, _TXTATR_SYSTEM))
			{
				pChatRoom->SendMsgToAllPlayer(&msgTalk);
			}
		}
		break;
	case ACTION_ENTERROOM_CHECKMONEY: //��mapgroup���صģ��������
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoom(szString);
			CHECK(pChatRoom);
			if(pChatRoom->IsExist(pUser))
				return ;
			pChatRoom->EnterRoom(pUser);
		}
		break;
	case ACTION_APPLYMANAGER:	//���������ҹ���Ա
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			CHECK(pChatRoom);
			if(!pChatRoom->IsExist(pUser))
				return;
			if(pChatRoom->IsCanApplyManager())
				pChatRoom->ApplyManager(pUser);
		}
		break;
	case ACTION_QUITMANAGER: //���������ҹ���Ա
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			CHECK(pChatRoom);
			if(!pChatRoom->IsExist(pUser))
				return;
			if(pChatRoom->IsManager(pUser))
			{
				pChatRoom->ResetManager();				
				if(Create(ACTION_QUITMANAGER,0,pUser->szName))
				{
					pChatRoom->SendMsgToAllPlayer(this);
					pChatRoom->LeaveRoom(pUser);
				}
			}
		}
		break;
	case ACTION_OFFLINE:
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			if(pChatRoom)
			{
				ULONG ulUserID =(ULONG)pUser->GetID();
				IF_NOT(this->Create(ACTION_LEAVEROOM,0,pUser->szName)) //֪ͨ�ͻ�������뿪����Ϣ
					return;
				pChatRoom->SendMsgToAllExcSelf(this,pUser);//֪ͨ�������������
				pChatRoom->LeaveRoom(pUser);			
				
				char szBuff[128];
				sprintf(szBuff,STR_CHATROOM_LEAVE,pUser->szName,pChatRoom->GetRoomName());
				CMsgTalkW msgTalk;
				if (msgTalk.Create(SYSTEM_NAME, ALLUSERS_NAME, szBuff, NULL, 0xff0000, _TXTATR_SYSTEM))
				{
					pChatRoom->SendMsgToAllPlayer(&msgTalk);
				}				
				//���ǹ���Ա��������ʱ
				if(pChatRoom->IsManager(pUser))
					pChatRoom->StartupManagerOfflineTimer();
			}
		}		
		break;
	case ACTION_SETFEE:	//�����������
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			if(pChatRoom && pChatRoom->IsManager(pUser))
			{
				ULONG ulFee = m_pInfo->ulData;
				pChatRoom->SetFee(ulFee);
				pChatRoom->SendMsgToAllPlayer(this);//ͬ��
			}
		}
		break;
	case ACTION_SETROOMNAME://��������������
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			if(pChatRoom && pChatRoom->IsManager(pUser))
			{
				pChatRoom->SetName(szString);
				pChatRoom->SendMsgToAllPlayer(this);//ͬ��
			}
		}
		break;
	case ACTION_KICKMEMBER: //��
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			if(pChatRoom && pChatRoom->IsManager(pUser))
			{
				CPlayer * pPlayer = UserList()->GetPlayer(szString);
				if(pPlayer)
				{
					if(pChatRoom->IsExist(pPlayer))
					{
						pChatRoom->DrawinFee(pPlayer);
						IF_NOT(this->Create(ACTION_LEAVEROOM,0,szString)) //֪ͨ�ͻ���������ߵ���Ϣ
							return;
						pChatRoom->SendMsgToAllPlayer(this);//֪ͨ�������������
						pChatRoom->LeaveRoom(pUser);			
						
						char szBuff[128];
						sprintf(szBuff,STR_CHATROOM_LEAVE,pUser->szName,pChatRoom->GetRoomName());
						CMsgTalkW msgTalk;
						if (msgTalk.Create(SYSTEM_NAME,ALLUSERS_NAME, szBuff, NULL, 0xff0000, _TXTATR_SYSTEM))
						{
							pChatRoom->SendMsgToAllPlayer(&msgTalk);
						}
					}
				}
			}
		}
		break;

	case ACTION_TALK: //̸��
		{
			CChatRoom * pChatRoom = g_objChatRoomManager.GetRoomByPlayer(pUser);
			if(pChatRoom)
			{
				pChatRoom->SendMsgToAllExcSelf(this,pUser);
			}
		}
		break;

	default:
		break;
	}
}

bool CMsgChatRoom::Create(unsigned short usAction, ULONG ulData, const char *pString)
{
	// check param
	if(usAction<0) //  || idTarget == ID_NONE
	{
		ASSERT(!"CMsgSyndicate::Create()");
		return false;
	}

	// init
	this->Init();

	m_pInfo->usAction	=usAction;	
	m_pInfo->ulData	=ulData;
	if(pString)
		m_sString.AddString(pString);
	// fill info now	
	m_unMsgType	=_MSG_CHATROOM;
	if(pString)
		m_unMsgSize	=sizeof(MSG_Info)-1+m_sString.GetSize();
	else
		m_unMsgSize	=sizeof(MSG_Info)-1;


	return true;
}
