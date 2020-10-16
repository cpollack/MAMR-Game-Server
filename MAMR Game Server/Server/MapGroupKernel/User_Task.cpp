// User.cpp: implementation of the CUser class.
//
//////////////////////////////////////////////////////////////////////

#include "Network/AllMsg.h"
#include "User.h"
#include "MapGroup.h"
#include "Network/netmsg.h"
#include "ItemType.h"
//#include "MapItem.h"
#include "Package.h"
#include "ActionDefine.h"
#include "Syndicate.h"
#include "npc.h"
//#include "WantedList.h"
//#include "MercenaryTask.h"

#include "Network/MsgDialog.h"

const int	VAL_SKIPTEST	=999;
const int	PRESENTMONEY_LIMIT		= 10000;			// ���𻮲�������10000

//////////////////////////////////////////////////////////////////////
// task
////////////////////////////////////////////////////////////////////////////////////
bool CUser::TestTask(CTaskData* pTask)
{
	CHECKF(pTask);

	try
	{
		if(!CheckItem(pTask))
			return false;	// û��������Ʒ

		if (this->GetMoney() < pTask->GetInt(TASKDATA_MINMONEY))
			return false;

		//if (pTask->GetInt(TASKDATA_PROFESSION) && this->GetProfession() != pTask->GetInt(TASKDATA_PROFESSION))
		//	return false;

//		if (pTask->GetInt(TASKDATA_SEX) && ((1 << this->GetSex()) & pTask->GetInt(TASKDATA_SEX)) != 0)
//			return false;

		if (this->GetPk() < pTask->GetInt(TASKDATA_MINPK) || this->GetPk() > pTask->GetInt(TASKDATA_MAXPK))
			return false;

		if (pTask->GetInt(TASKDATA_TEAM) != VAL_SKIPTEST)
		{
/*			switch(pTask->GetInt(TASKDATA_TEAM))
			{
			case 0:
			case 1:
				{
					int nMembers	=this->GetTeamMembers();
					if (nMembers != 0 && nMembers != 1)
						return false;
				}
				break;

			case 2:
			case 3:
			case 4:
			case 5:
				{
					if (this->GetTeamMembers() != m_Info.nTeam)
						return false;
				}
				break;

			case 6:		// no team members check
				break;

			case 7:		// couple
				{
					CTeam* pTeam	=this->GetTeam();
					if (!pTeam || !pTeam->IsCoupleTeam())
						return false;
				}
				break;

			case 8:		// brother
				{
					CTeam* pTeam	=this->GetTeam();
					if (!pTeam || !pTeam->IsBrotherTeam())
						return false;
				}
				break;

			default:
				return false;
			} // switch
*/		}

		if (pTask->GetInt(TASKDATA_SEX) != VAL_SKIPTEST)
		{
			if (this->GetSex() != pTask->GetInt(TASKDATA_SEX))
				return false;
		}
/*
		if(pTask->GetInt(TASKDATA_METEMPSYCHOSIS) && this->GetMetempsychosis() < pTask->GetInt(TASKDATA_METEMPSYCHOSIS))
		{
			if (g_cSyndicate.GetLevel(this->GetSyndicateID()) != m_Info.nSyndicate)
				return false;
		}
*/
		int nMarriageChk = pTask->GetInt(TASKDATA_MARRIAGE);
		if (-1 != nMarriageChk)
		{
			if (0 == nMarriageChk && this->IsMarried())
				return false;

			if (1 == nMarriageChk && !this->IsMarried())
				return false;
		}

		return true;
	}
	catch(...)
	{
		ASSERT(!"catch");
		::LogSave("exception catched In CGameTask::TestUser.");
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////
bool CUser::CheckItem(CTaskData* pTask)
{
	if(strlen(pTask->GetStr(TASKDATA_ITEMNAME1)) > 0)
	{
		if(!this->GetTaskItem(pTask->GetStr(TASKDATA_ITEMNAME1)))
			return false;

		if(strlen(pTask->GetStr(TASKDATA_ITEMNAME2)) > 0)
		{
			if(!this->GetTaskItem(pTask->GetStr(TASKDATA_ITEMNAME2)))
				return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::ProcessClientTask(OBJID idTask, LPCTSTR pszAccept)
{
	CTaskData* pTask = TaskSet()->GetObj(idTask);
	CHECKF(pTask && pTask->GetInt(TASKDATA_IDNEXT1));

	CNpc* pNpc = NULL;
	GetMap()->QueryObj(GetPosX(), GetPosY(), OBJ_NPC, m_idTaskNpc, IPP_OF(pNpc));	// pNpc may be null

	if (!this->TestTask(pTask))
	{
		OBJID idNext	= pTask->GetInt(TASKDATA_IDNEXT2);
		if (idNext != ID_NONE)
		{
			GameAction()->ProcessAction(idNext, this, pNpc->QueryRole(), NULL, pszAccept);
			return true;
		}

		this->SendSysMsg(STR_UNQUALIFIED);
		return false;
	}

	OBJID idNext	= pTask->GetInt(TASKDATA_IDNEXT0);
	if (idNext != ID_NONE)
		GameAction()->ProcessAction(idNext, this, pNpc->QueryRole(), NULL, pszAccept);

	return true;
}

//////////////////////////////////////////////////////////////////////
int CUser::PushTaskID(OBJID idTask, OBJID idIter)
{
	if(idTask != ID_NONE && m_setTaskID.size() < MAX_MENUTASKSIZE)
	{
		m_setTaskID.push_back(idTask);
		m_setIterID.push_back(idIter);
		return m_setTaskID.size()-1;
	}
	return INDEX_NONE;
}

//////////////////////////////////////////////////////////////////////
bool CUser::ProcessTask(int idx, LPCTSTR pszAccept)
{
	// check npc
	if(m_idTaskNpc == ID_NONE)
		return false;
	CNpc* pNpc = NULL;
	if(!GetMap()->QueryObj(GetPosX(), GetPosY(), OBJ_NPC, m_idTaskNpc, IPP_OF(pNpc)))
	{
//		LOGERROR("����ϵͳ����������NPC[%u]�Ҳ���!", m_idTaskNpc);
		return false;
	}
	CHECKF(pNpc);

	//What does this do? User specific tasks? It does not currently work
	//OBJID	idTask = GetTaskID(idx);
	//if (idTask == ID_NONE)
	//	return false;
	//SetIterID(idx);
	//ClearTaskID();

	OBJID idTask = idx;
	if (idTask == ID_NONE)
		return false;

	CTaskData* pTask = TaskSet()->GetObj(idTask);
	IF_NOT(pTask)
	{
		LOGERROR("Don't find ACTION ID in menu: %d", idTask);
		return false;
	}

	if (!this->TestTask(pTask))
	{
		OBJID idNext	= pTask->GetInt(TASKDATA_IDNEXT2);
		if (idNext != ID_NONE)
		{
			GameAction()->ProcessAction(idNext, this, pNpc->QueryRole(), NULL, pszAccept);
			return true;
		}

		this->SendSysMsg(STR_UNQUALIFIED);
		return false;
	}

	OBJID idNext	= pTask->GetInt(TASKDATA_IDNEXT0);
	if (idNext != ID_NONE)
		GameAction()->ProcessAction(idNext, this, pNpc->QueryRole(), NULL, pszAccept);

	return true;
}

bool CUser::ProcessDialogueTask(int idx) {
	if (idx < 0 || idx > 4) {
		LOGERROR("CUser::ProcessDialogueTask(): Invalid dialogue response index %d", idx);
		return false;
	}
	int nTask = m_dialogueTasks[idx];
	ProcessTask(nTask, "");
}

bool CUser::PushDialogueMessage(string strMessage) {
	if (m_dialogueMessages.size() >= 16) return false;
	m_dialogueMessages.push_back(strMessage);
}

bool CUser::PushDialogueResponse(string strResponse, int runTask) {
	if (m_dialogueResponses.size() >= 4) return false;
	m_dialogueResponses.push_back(strResponse);
	m_dialogueTasks[m_dialogueResponses.size()] = runTask;
}

void CUser::ClearDialogue() {
	m_dialogueMessages.clear();
	m_dialogueResponses.clear();
}

bool CUser::SendDialogue(int nFace, int nCloseTask) {
	m_dialogueTasks[0] = nCloseTask;
	CMsgDialog msg;
	if (msg.Create(MSGDIALOG_CREATE, nFace, m_dialogueMessages, m_dialogueResponses)) {
		SendMsg(&msg);
		ClearDialogue();
		return true;
	}

	ClearDialogue();
	return false;
}

//////////////////////////////////////////////////////////////////////
void CUser::AddTaskMask		(int idx)
{
	IF_NOT (idx >= 0 && idx < 32)
		return;

	DWORD dwMask = m_data.GetTaskMask()|(1<<idx);
	m_data.SetTaskMask(dwMask);
}

//////////////////////////////////////////////////////////////////////
void CUser::ClrTaskMask		(int idx)
{
	IF_NOT (idx >= 0 && idx < 32)
		return;

	DWORD dwMask = m_data.GetTaskMask();
	dwMask	&= ~(1<<idx);
	m_data.SetTaskMask(dwMask);
}

//////////////////////////////////////////////////////////////////////
bool CUser::ChkTaskMask		(int idx)
{
	IF_NOT (idx >= 0 && idx < 32)
		return false;

	return (m_data.GetTaskMask() & (1<<idx)) != 0;
}

//////////////////////////////////////////////////////////////////////
bool CUser::CompleteMercenaryTask(OBJID idTask, OBJID idItem)
{
	// �ύ��ɵ�Ӷ������
	// �������Ϸ���
	/*CMercenaryTaskData* pTaskData = MercenaryTask()->QueryTaskDataByID(idTask);
	if (!pTaskData)
	{
		SendSysMsg(STR_INVALID_MERCENARYTASK);
		return false;
	}
	if (pTaskData->GetInt(MTASKDATA_USER_ID) == GetID())
	{
		// �ر��Լ�������
		if (pTaskData->GetInt(MTASKDATA_STATE) != MTASKSTATE_COMPLETED)
		{
			// ����û������
			SendSysMsg(STR_TASK_NOT_FINISHED_YET);
			return false;
		}

		// ȡ��������Ʒ
		if (pTaskData->GetInt(MTASKDATA_TYPE) == _WANT_ITEM
			|| pTaskData->GetInt(MTASKDATA_TYPE) == _WANT_EUDEMON)
		{
			{	// �ȼ�鱳���ռ�
				CItem* pItem = pTaskData->GetResultItem();
				if (pItem && QueryPackage()->IsPackFull(1, &pItem))
				{
					SendSysMsg(STR_BAG_FULL);
					return false;
				}
			}
			CItem* pItem = pTaskData->PopResultItem();
			ASSERT(pItem);
			AddItem(pItem, true, true);
		}
		else if (pTaskData->GetInt(MTASKDATA_TYPE) ==_WANT_PK)
		{
			// ɱ�����񣬲���Ҫȡ���κ���Ʒ
		}
		else
		{
			::LogSave("Invalid mercenary task type [ID=%u, type=%u]", 
				pTaskData->GetID(), pTaskData->GetInt(MTASKDATA_TYPE));
			return false;
		}
		// �ر����� ���� ֱ��ɾ������
		MercenaryTask()->DeleteTask(idTask);

		// return a message
		SendSysMsg(STR_CLOSE_TASK_OK);
	}
	else
	{
		// ����Լ��ӵ�����
		if (pTaskData->GetInt(MTASKDATA_ACCEPT_USERID) != GetID()
			|| (pTaskData->GetInt(MTASKDATA_STATE) != MTASKSTATE_ACCEPTED
				&& pTaskData->GetInt(MTASKDATA_STATE) != MTASKSTATE_FINISHED))
		{
			// �����Լ��ӵ����񣬻��߲��Ǵ����ѽ�δ���״̬���Ƿ�
			SendSysMsg(STR_INVALID_MERCENARYTASK);
			return false;
		}
		// �������������������ɱ�˻���������Ʒ
		if (pTaskData->GetInt(MTASKDATA_TYPE) == _WANT_ITEM
			|| pTaskData->GetInt(MTASKDATA_TYPE) == _WANT_EUDEMON)
		{
			// ������Ʒ
			// ���idItem��������Ʒ�Ƿ���������
			// coding here...
			CItem* pResultItem = GetItem(idItem);	// �Ȳ�ͬ�����ͻ���
			if (pResultItem && pResultItem->IsEudemon())
			{
				CallBackEudemon(pResultItem->GetID());
				DetachEudemon(pResultItem);
			}

			IF_NOT (pResultItem = PopItem(idItem, false, true))
				return false;

			if (pTaskData->AddResultItem(pResultItem))
			{
				CMsgItem msg;
				if(msg.Create(idItem, ITEMACT_DROP))	// �ɹ����ͬ��
					this->SendMsg(&msg);

				// set task finished.
				pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_FINISHED, true);		// Ϊ�˱�֤��Ҫ������������д��
			}
			else
			{
				// ʧ�ܣ����·��ظ����
				AddItem(pResultItem, false);		// ��Ϊǰ��û��ͬ��֪ͨ�ͻ���ɾ��������Ҳ��û��Ҫ֪ͨ�ͻ������
				SendSysMsg(STR_ILLEGAL_TASK_ITEM);
				return false;
			}
		}
		else if (pTaskData->GetInt(MTASKDATA_TYPE) == _WANT_PK)
		{
			// ����ɱ�ˣ���ɱ��Ŀ���ʱ����Զ�����������ΪFinished״̬�ˣ�����Ͳ���Ҫ���κ�������
		}
		else
		{
			::LogSave("Invalid mercenary task type [ID=%u, type=%u]", 
				pTaskData->GetID(), pTaskData->GetInt(MTASKDATA_TYPE));
			return false;
		}

		// ��������һ�����������ɹ�ִ�У����Ѿ�����������Ϊfinished״̬��

		if (pTaskData->GetInt(MTASKDATA_STATE) == MTASKSTATE_FINISHED)
		{
			// �����Ѿ���ɣ���ȡ��Ʒ
			// �ȼ�鱳���ռ�
			{
				CItem* setItems[_MAX_PRIZE];
				int nAmount = 0;
				for (int i=0; i<_MAX_PRIZE; i++)
				{
					OBJID idItem = pTaskData->GetInt((MTASKDATA)(MTASKDATA_PRIZE_ITEMID0+i));
					if (idItem != ID_NONE)
					{
						CItem* pItem = pTaskData->GetItem(idItem);
						IF_NOT (pItem)
							return false;
						setItems[nAmount]	= pItem;
						++nAmount;
					}
				}
				if (nAmount > 0 && QueryPackage()->IsPackFull(nAmount, setItems))
				{
					SendSysMsg(STR_BAG_FULL);
					return false;
				}
			}

			// �Ƚ�������
			pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_COMPLETED);
			
			// ���콱
			// ��Ʒ
			for (int i=0; i<_MAX_PRIZE; i++)
			{
				OBJID idItem = pTaskData->GetInt((MTASKDATA)(MTASKDATA_PRIZE_ITEMID0+i));
				if (idItem != ID_NONE)
				{
					CItem* pItem = pTaskData->PopItem(idItem);
					if (pItem)
						AddItem(pItem, true, true);
					pTaskData->SetInt((MTASKDATA)(MTASKDATA_PRIZE_ITEMID0+i), ID_NONE);
				}
			}
			// ����
			GainMoney(pTaskData->GetInt(MTASKDATA_PRIZE_MONEY), true);
			pTaskData->SetInt(MTASKDATA_PRIZE_MONEY, 0, true);

			// send a message to client
			SendSysMsg(STR_TAKE_PRIZE_OK);
		}
		else
		{
			// ����û�����
			// send task unfinished msg to client
			SendSysMsg(STR_TASK_NOT_FINISHED_YET);
			return false;
		}
	}*/
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::AcceptMercenaryTask(OBJID idTask)
{
	// ����Ƿ��Ѿ��ӹ�����
	/*{
		CMercenaryTaskData* pTaskData = MercenaryTask()->QueryTaskDataAccepted(GetID());
		if (pTaskData)
		{
			SendSysMsg(STR_DUPLICATE_TASK);
			return false;
		}
	}

	// ��鱻���������Ч��
	CMercenaryTaskData* pTaskData = MercenaryTask()->QueryTaskDataByID(idTask);
	if (!pTaskData)
	{
		SendSysMsg(STR_INVALID_MERCENARYTASK);
		return false;
	}

	if (pTaskData->GetInt(MTASKDATA_USER_ID) == this->GetID())
	{
		SendSysMsg(STR_CANNOT_ACCEPT_MYTASK);
		return false;
	}

	if (pTaskData->GetInt(MTASKDATA_STATE) != MTASKSTATE_NONE)
	{
		SendSysMsg(STR_INVALID_MERCENARYTASK);
		return false;
	}

	if (GetMercenaryRank() < pTaskData->GetInt(MTASKDATA_RANK_REQ))
	{
		SendSysMsg(STR_LOW_MERCENARY_RANK);
		return false;
	}

	// ��Ѻ��
	int nMoney = pTaskData->GetInt(MTASKDATA_PRIZE_MONEY);
	for (int i=0; i<_MAX_PRIZE; i++)
	{
		CItem* pItem = pTaskData->GetItemByIndex(i);
		if (pItem)
			nMoney += pItem->GetInt(ITEMDATA_PRICE);
	}
	nMoney = __max(500, nMoney/100);	// ������ֻ������Ʒ�۸�+�����1%���������Ϊ500
	if (!SpendMoney(nMoney, true))
	{
		SendSysMsg(STR_NOT_ENOUGH_MONEY, nMoney);
		return false;
	}

	// ������
	pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_ACCEPTED);
	pTaskData->SetInt(MTASKDATA_ACCEPT_TIME, ::TimeGet(TIME_SECOND));	// ��¼ʱ��
	pTaskData->SetInt(MTASKDATA_ACCEPT_USERID, GetID(), true);

	// retuen a message
	SendSysMsg(STR_ACCEPT_TASK_OK);*/
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::CancelMercenaryTask(OBJID idTask)
{
	// �������Ϸ���
	/*CMercenaryTaskData* pTaskData = MercenaryTask()->QueryTaskDataByID(idTask);
	if (!pTaskData)
	{
		SendSysMsg(STR_INVALID_MERCENARYTASK);
		return false;
	}
	if (pTaskData->GetInt(MTASKDATA_USER_ID) == GetID())
	{
		// ��ֹ�Լ�������
		if (pTaskData->GetInt(MTASKDATA_STATE) != MTASKSTATE_NONE)
		{
			// �����Ǵ���δ��״̬��������ֹ
			SendSysMsg(STR_CANNOT_CANCEL_TASK);
			return false;
		}
		// �ȼ�鱳���ռ�
		{
			CItem* setItems[_MAX_PRIZE];
			int nAmount = 0;
			for (int i=0; i<_MAX_PRIZE; i++)
			{
				OBJID idItem = pTaskData->GetInt((MTASKDATA)(MTASKDATA_PRIZE_ITEMID0+i));
				if (idItem != ID_NONE)
				{
					CItem* pItem = pTaskData->GetItem(idItem);
					IF_NOT (pItem)
						return false;
					setItems[nAmount]	= pItem;
					++nAmount;
				}
			}
			if (nAmount > 0 && QueryPackage()->IsPackFull(nAmount, setItems))
			{
				SendSysMsg(STR_BAG_FULL);
				return false;
			}
		}
		// ������Ʒ�ͽ���
		// ��Ʒ
		DEBUG_TRY
		for (int i=0; i<_MAX_PRIZE; i++)
		{
			OBJID idItem = pTaskData->GetInt((MTASKDATA)(MTASKDATA_PRIZE_ITEMID0+i));
			if (idItem != ID_NONE)
			{
				CItem* pItem = pTaskData->PopItem(idItem);
				if (pItem)
					AddItem(pItem, true, true);
				pTaskData->SetInt((MTASKDATA)(MTASKDATA_PRIZE_ITEMID0+i), ID_NONE);
			}
		}
		DEBUG_CATCH("CUser::CancelMercenaryTask crash when return prize items")
		// ����
		GainMoney(pTaskData->GetInt(MTASKDATA_PRIZE_MONEY), true);

		//pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_CANCELED, true);
		// ��ֹ����ֻҪֱ��ɾ������ͺ���
		MercenaryTask()->DeleteTask(idTask);
	}
	else
	{
		// ��ֹ�Լ��ӵ�����
		if (pTaskData->GetInt(MTASKDATA_ACCEPT_USERID) != GetID()
			|| pTaskData->GetInt(MTASKDATA_STATE) != MTASKSTATE_ACCEPTED)
		{
			// �����Լ��ӵ����񣬻��߲��Ǵ����ѽ�δ���״̬���Ƿ�
			SendSysMsg(STR_INVALID_MERCENARYTASK);
			return false;
		}

		// ��������ִ�е�Ӷ������
		pTaskData->SetInt(MTASKDATA_ACCEPT_USERID, ID_NONE);
		pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_NONE, true);

	}
	// return a message
	SendSysMsg(STR_CANCEL_TASK_OK);*/
	return true;
}
