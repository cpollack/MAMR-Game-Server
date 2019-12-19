// MercenaryTask.cpp: implementation of the CMercenaryTask class.
//
//////////////////////////////////////////////////////////////////////

#include "MercenaryTask.h"
#include "I_Role.h"
#include "MapGroup.h"
#include "User.h"
#include "AllMsg.h"

const int	CHECK_TASK_INTERVAL		= 5*60;			// ÿ5���Ӽ��һ������
const int	TASK_TIMEOUT_SECS		= 3*24*60*60;	// ����ʱʱ�䣨��λ���룩��3��

//MYHEAP_IMPLEMENTATION(CMercenaryTask, s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMercenaryTask::CMercenaryTask()
	: m_tCheckInterval(CHECK_TASK_INTERVAL)
{

}

CMercenaryTask::~CMercenaryTask()
{
	TASKDATA_SET::iterator it=m_setData.begin();
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pData = *it;
		SAFE_RELEASE (pData);
	}
}

//////////////////////////////////////////////////////////////////////
bool CMercenaryTask::Create(PROCESS_ID idProcess)
{
	m_idProcess	= idProcess;

	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s", _TBL_MERCENARYTASK);
	IRecordset* pRes = Database()->CreateNewRecordset(szSQL);
	if (pRes)
	{
		for (int i=0; i<pRes->RecordCount(); i++)
		{
			CMercenaryTaskData* pData = CMercenaryTaskData::CreateNew();
			if (pData && pData->Create(pRes, Database()))
			{
				m_setData.push_back(pData);
			}
			else
			{
				SAFE_RELEASE (pData);
				SAFE_RELEASE (pRes);
				return false;
			}

			pRes->MoveNext();
		}
		SAFE_RELEASE (pRes);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CMercenaryTask::CreateNewTask(const ST_MTASK_DATA* pInfo)
{
	CMercenaryTaskData* pData = CMercenaryTaskData::CreateNew();
	if (pData)
	{
		if (pData->CreateRecord(pInfo, Database()))
		{
			m_setData.push_back(pData);
			return true;
		}
		SAFE_RELEASE (pData);
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CMercenaryTask::DeleteTask(OBJID idTask)
{
	TASKDATA_SET::iterator it=m_setData.begin();
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pData = *it;
		if (pData && pData->GetID() == idTask)
		{
			if (!pData->DeleteRecord())
				return false;
			m_setData.erase(it);
			SAFE_RELEASE (pData);
			return true;
		}
	}
	return false;	
}

//////////////////////////////////////////////////////////////////////
CMercenaryTaskData*	CMercenaryTask::QueryTaskDataByIndex(int nIdx)
{
	if (nIdx >= m_setData.size())
		return NULL;
	return m_setData[nIdx];
}

//////////////////////////////////////////////////////////////////////
CMercenaryTaskData*	CMercenaryTask::QueryTaskDataByID(OBJID idTask)
{
	TASKDATA_SET::iterator it=m_setData.begin();
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pData = *it;
		if (pData && pData->GetID() == idTask)
			return pData;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
CMercenaryTaskData*	CMercenaryTask::QueryTaskDataByOwner(OBJID idUser)
{
	TASKDATA_SET::iterator it=m_setData.begin();
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pData = *it;
		if (pData && pData->GetInt(MTASKDATA_USER_ID) == idUser)
			return pData;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
CMercenaryTaskData*	CMercenaryTask::QueryTaskDataAccepted(OBJID idAccepter)
{
	TASKDATA_SET::iterator it=m_setData.begin();
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pData = *it;
		if (pData && pData->GetInt(MTASKDATA_STATE) == MTASKSTATE_ACCEPTED 
			&& pData->GetInt(MTASKDATA_ACCEPT_USERID) == idAccepter)
			return pData;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
bool CMercenaryTask::SendTaskList(IRole* pRole, UCHAR usType, OBJID idLast)
{
	CHECKF (pRole);

	CMsgTaskList	msg;
	if (!msg.Create(usType))
		return false;

	TASKDATA_SET::iterator it=m_setData.begin();
	if (idLast != ID_NONE)
	{
		for (; it!=m_setData.end(); it++)
		{
			CMercenaryTaskData* pData = *it;
			if (pData && pData->GetID() == idLast)
				break;
		}
	}

	int nAmount = 0;
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pData = *it;
		if (pData)
		{
			switch(usType)
			{
			case TASKLIST_ACCEPTED:		// �ѽ����� (MTASKSTATE_FINISHED��ʾ����ɵ�δ�콱�ģ�Ҳ�����ѽ�����)
				if (pData->GetInt(MTASKDATA_STATE) != MTASKSTATE_ACCEPTED 
					&& pData->GetInt(MTASKDATA_STATE) != MTASKSTATE_FINISHED)
					continue;
				break;
			case TASKLIST_UNACCEPTED:	// δ������
				if (pData->GetInt(MTASKDATA_STATE) != MTASKSTATE_NONE)
					continue;
				break;
//			case TASKLIST_COMPLETED:	// ���������
//				if (pData->GetInt(MTASKDATA_STATE) != MTASKSTATE_COMPLETED)
//					continue;
//				break;
			case TASKLIST_MYTASK:		// �ҵ�����
				if (pData->GetInt(MTASKDATA_USER_ID) != pRole->GetID())
					continue;
				break;
			default:
				::LogSave("UnKnown type in CMercenaryTask::SendTaskList [usType=%u]", usType);
				continue;
				break;
			}
			if (!msg.Append(pData->GetID(), pData->GetInt(MTASKDATA_RANK_REQ), pData->GetStr(MTASKDATA_TITLE)))
				return false;
			++nAmount;
			if (nAmount >= _MAX_TASK_PER_PAGE)
				break;
		}
	}

	return pRole->SendMsg(&msg);
}

//////////////////////////////////////////////////////////////////////
bool CMercenaryTask::SendTaskInfo(IRole* pRole, OBJID idTask)
{
	CHECKF (pRole);

	CMercenaryTaskData* pData = this->QueryTaskDataByID(idTask);
	if (!pData)
		return false;

	CMsgPlayerTask	msg;
	if (!msg.Create(pData))
		return false;

	return pRole->SendMsg(&msg);
}

//////////////////////////////////////////////////////////////////////
void CMercenaryTask::OnTimer(time_t tCurr)
{
	if (!m_tCheckInterval.ToNextTime())		// ÿ5���Ӽ��һ��
		return;

	DWORD	dwCurTime	= ::TimeGet(TIME_SECOND);
	TASKDATA_SET::iterator it=m_setData.begin();
	for (; it!=m_setData.end(); it++)
	{
		CMercenaryTaskData* pTaskData = *it;
		if (pTaskData && pTaskData->GetInt(MTASKDATA_STATE) == MTASKSTATE_ACCEPTED)	// ֻ����ѱ��ӵ���û��ɵĵ�����
		{
			DWORD dwTimeAccept = pTaskData->GetInt(MTASKDATA_ACCEPT_TIME);	// ������ʱ��ʱ��
			// ����Ƿ��Ѿ������涨ʱ��
			if (dwCurTime - dwTimeAccept < TASK_TIMEOUT_SECS)
				continue;

			// �����Զ�ȡ��
			OBJID idUser = pTaskData->GetInt(MTASKDATA_ACCEPT_USERID);
			pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_NONE);
			pTaskData->SetInt(MTASKDATA_ACCEPT_TIME, 0);
			pTaskData->SetInt(MTASKDATA_ACCEPT_USERID, ID_NONE, true);
			if (idUser != ID_NONE)
			{
				CUser* pUser = UserManager()->GetUser(idUser);
				if (pUser)
				{
					pUser->SendSysMsg(STR_TASK_TIMEOUT);
				}
//				else
//				{
//					// �����Ҫ���ԣ���cq_mercenary_task����Ҫ��¼��������ҵ�����
//					//LeaveWord()->InsertWords(SYSTEM_NAME, );
//				}
			}
		} // end of if
	}
}
