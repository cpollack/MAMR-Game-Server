// MsgChatRoom.cpp: implementation of the CMsgChatRoom class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#include "mapgroup.h"
#include "transformation.h"
#include "Agent.h"

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
	CUserPtr pUser = UserManager()->GetUser(this);
	CHECK(pUser);
	
	switch( m_pInfo->usAction )
	{
	case ACTION_ENTERROOM_APPLY://����������������
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;
	case ACTION_LEAVEROOM:	//�뿪������
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);			
		}
		break;
	case ACTION_APPLYMANAGER:	//���������ҹ���Ա
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;
	case ACTION_QUITMANAGER: //���������ҹ���Ա
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;
	case ACTION_ENTERROOM_CHECKMONEY: //���Ǯ
		{
			ULONG dwMoney = m_pInfo->ulData;

			if(pUser->SpendMoney(dwMoney,true))
			{
				MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);//���Խ���������
			}
			else
			{
				pUser->SendSysMsg(STR_CHATROOM_CANNOT_INMOREROOM_FORNOMONEY);
			}
		}
		break;
	case ACTION_FEE_DEDUCT://��Ǯ--�Էǹ���Ա
		{
			ULONG dwMoney = m_pInfo->ulData;
			if(!pUser->SpendMoney(dwMoney,true))
			{
				//����û��Ǯ�ˣ����������޳�
				if(this->Create(ACTION_LEAVEROOM))
					MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
			}
		}
		break;
	case ACTION_FEE_INCOME://�չ������--�Թ���Ա
		{
			ULONG dwMoney = m_pInfo->ulData;
			pUser->AddMoney(dwMoney);
		}
		break;
	case ACTION_SETFEE:	//�����������
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;
	case ACTION_SETROOMNAME:
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;
	case ACTION_OFFLINE:
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;
	case ACTION_KICKMEMBER: //��
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);

		}
	case ACTION_TALK: //̸��
		{
			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pUser->GetSocketID(),this);
		}
		break;

	default:
		break;
	}
	
}


bool CMsgChatRoom::Create(unsigned short usAction, ULONG ulData, const char *pString)
{
	// check param
	if(usAction == ACTION_NONE) //  || idTarget == ID_NONE
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
