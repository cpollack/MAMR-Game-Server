// GameAction.cpp: implementation of the CGameAction class.
//
//////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <sstream>
#include "define.h"
#include "windows.h"
#include "I_Role.h"
#include "User.h"
#include "Item.h"
#include "GameAction.h"
#include "MapGroup.h"
#include "Npc.h"
#include "Network/AllMsg.h"
#include "ActionDefine.h"
//#include "WantedList.h"
//#include "PoliceWanted.h"
#include "NpcLink.h"
//#include "MapTrap.h"
#include "DeadLoop.h"
#include "string.h"
#include "EventPack.h"
#include "NpcTable.h"
#include "TaskDetailData.h"
#include "TaskDetail.h"

//////////////////////////////////////////////////////////////////////
const int	PRESENTMONEY_LIMIT				= 10000;			// ���𻮲�������10000
const int	ENTER_HOME_TEAM_DISTANCE		= 5;				// ��ӽ����ͥ�ľ���
const int	MAX_UNLEARN_NUMBER				= 20;				// ��ȴMAGIC���֧������
const int	SUBSYN_NAMESIZE					= 16;				// �Ӱ������ֳ���
const int	MAX_ACCEPTSTR					= 4;				// ����4���Ӵ�

MYHEAP_IMPLEMENTATION(CGameAction,s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////////////////////
void CGameAction::ReplaceAttrStr(char* pszTarget, const char* pszSource, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept/*=NULL*/)
{
	if(!pszTarget || !pszSource)
	{
		ASSERT(!"CJobNpc::ReplaceAttrStr");
		return;
	}

	if(strchr(pszSource, '%') == NULL)
	{
		SafeCopy(pszTarget, pszSource);
		return;
	}

	CNpc* pNpc = NULL;
	if(pRole)
		pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc));

	const char*	ptr = pszSource; 
	char*	ptr2 = pszTarget;
	while(*ptr)
	{
		if(*ptr == '%')
		{
			ptr++;

			// width
			int nWidth	= 0;
			if(isdigit(*ptr))
				nWidth	= nWidth*10 + (*(ptr++))-'0';
			if(isdigit(*ptr))
				nWidth	= nWidth*10 + (*(ptr++))-'0';		// ��֧��2λ��
			const char* pNext = ptr2 + nWidth;

			if(*(ptr) == '%')
			{
				*ptr2	= '%';

				ptr	+= 2;
				ptr2++;
				// continue;
			}
			if (_strnicmp(ptr, PARAM_DATE_STAMP, sizeof(PARAM_DATE_STAMP)-1) == 0)
			{
				char szString[256] = "(err)";
				sprintf(szString, "%d", ::DateStamp());

				strcpy(ptr2, szString);

				ptr += sizeof(PARAM_DATE_STAMP)-1;
				ptr2 += strlen(szString);
				// continue;
			}
			else if (_strnicmp(ptr, PARAM_TIME, sizeof(PARAM_TIME)-1) == 0)
			{
				char szString[256] = "(err)";
				sprintf(szString, "%d", time(NULL));

				strcpy(ptr2, szString);

				ptr += sizeof(PARAM_TIME)-1;
				ptr2 += strlen(szString);
				// continue;
			}
			else if(_strnicmp(ptr, ACCEPT_STR_, sizeof(ACCEPT_STR_)-1) == 0 
						&& *(ptr+sizeof(ACCEPT_STR_)-1) >= '0' && *(ptr+sizeof(ACCEPT_STR_)-1) < '0'+ MAX_ACCEPTSTR)
			{
				char	szNum[256] = "(err)";
				int		nSize = strlen(szNum);
				int		idx = *(ptr+sizeof(ACCEPT_STR_)-1) - '0';
				if(pszAccept && idx >= 0 && idx < MAX_ACCEPTSTR)
				{
					char	szStr[4][256] = {0};
					sscanf(pszAccept, "%s %s %s %s", szStr[0], szStr[1], szStr[2], szStr[3]);
					strcpy(szNum, szStr[idx]);
				}
				strcpy(ptr2, szNum);

				ptr	+= sizeof(ACCEPT_STR_)-1 + 1;		//+1 : index
				ptr2		+= strlen(szNum);
				// continue;
			}
			if(pUser)
			{
				if (_strnicmp(ptr, PARA_ITER_GAME_CARD2, sizeof(PARA_ITER_GAME_CARD2)-1) == 0)
				{
					char szString[256] = "--";
					sprintf(szString, "%d", pUser->CountCard2());

					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_GAME_CARD2)-1;
					ptr2 += strlen(szString);
					// continue;
				}
				else if (_strnicmp(ptr, PARA_AVAILABLE_FUND, sizeof(PARA_AVAILABLE_FUND)-1) == 0)
				{
					//���ɻ���
					char szString[256] = "--";
					sprintf(szString, "%d", pUser->GetAvailableSynFund());
					
					strcpy(ptr2, szString);
					
					ptr += sizeof(PARA_AVAILABLE_FUND)-1;
					ptr2 += strlen(szString);

				}								
				else if (_strnicmp(ptr, PARA_ITER_GAME_CARD, sizeof(PARA_ITER_GAME_CARD)-1) == 0)
				{
					char szString[256] = "--";
					sprintf(szString, "%d", pUser->CountCard());

					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_GAME_CARD)-1;
					ptr2 += strlen(szString);
					// continue;
				}
				else if (_strnicmp(ptr, PARA_ITER_COST_DURRECOVER, sizeof(PARA_ITER_COST_DURRECOVER)-1) == 0)
				{
					char szString[256] = "--";
					if (pUser->TaskIterator() != 0)
					{
						CItem* pItem = pUser->GetEquipItemByPos(pUser->TaskIterator());
						if (pItem)
							sprintf(szString, "%d", pItem->GetRecoverDurCost());
					}
					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_COST_DURRECOVER)-1;
					ptr2 += strlen(szString);
					// continue;
				}
				else if (_strnicmp(ptr, PARA_ITER_GEMSUPQUALITY, sizeof(PARA_ITER_GEMSUPQUALITY)-1) == 0)
				{
					char szString[256] = "--";
					if (pUser->TaskIterator() != 0)
					{
						int nChance = pUser->GetChanceUpEpQuality(pUser->TaskIterator());

						int nGemCost = 0;
						if (nChance >= 0)
							nGemCost = 100/__max(1, nChance) + 1;

						sprintf(szString, "%d", nGemCost);
					}
					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_GEMSUPQUALITY)-1;
					ptr2 += strlen(szString);
					// continue;
				}
				else if (_strnicmp(ptr, PARA_ITER_GEMSUPLEVEL, sizeof(PARA_ITER_GEMSUPLEVEL)-1) == 0)
				{
					char szString[256] = "--";
					if (pUser->TaskIterator() != 0)
					{
						int nChance = pUser->GetChanceUpEpLevel(pUser->TaskIterator());

						int nGemCost = 0;
						if (nChance >= 0)
							nGemCost = (100/__max(1, nChance) + 1)*12/10;

						sprintf(szString, "%d", nGemCost);
					}
					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_GEMSUPLEVEL)-1;
					ptr2 += strlen(szString);
					// continue;
				}
				else if (_strnicmp(ptr, PARA_ITER_POLICEWANTED, sizeof(PARA_ITER_POLICEWANTED)-1) == 0)
				{
					/*char szString[256] = "--";
					//if (pUser->TaskIterator() != 0)
					{
						PoliceWantedStruct* pWanted = PoliceWanted().GetWantedByIndex(pUser->TaskIterator());
						if (pWanted)
						{
							sprintf(szString, "%03u %-15s %-15s %03d %d", 
									pUser->TaskIterator(), 
									pWanted->strName.c_str(), 
									pWanted->strSynName.c_str(), 
									pWanted->nLev,
									pWanted->nPk);
						}
					}
					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_POLICEWANTED)-1;
					ptr2 += strlen(szString);*/
					// continue;
				}
				else if (_strnicmp(ptr, PARA_ITER_WANTED, sizeof(PARA_ITER_WANTED)-1) == 0)
				{
					/*char szString[256] = "--";
					//if (pUser->TaskIterator() != 0)
					{
						CWantedData* pWanted = CWantedList::s_WantedList.GetWantedByIndex(pUser->TaskIterator());
						if (pWanted)
						{
							sprintf(szString, "%06u %-15s %u", pWanted->GetInt(DATA_ID), pWanted->GetStr(DATA_TARGET_NAME), pWanted->GetInt(DATA_BOUNTY));
						}
					}
					strcpy(ptr2, szString);

					ptr += sizeof(PARA_ITER_WANTED)-1;
					ptr2 += strlen(szString);*/
					// continue;
				}
				else if (_strnicmp(ptr, PARA_TUTOREXP_, sizeof(PARA_TUTOREXP_)-1) == 0)
				{
					char	szNum[256] = "0";
					sprintf(szNum, "%d", pUser->GetTutorExp());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_TUTOREXP_)-1;
					ptr2		+= strlen(szNum);
					// continue;					
				}
				else if (_strnicmp(ptr, PARA_STUDENT_EXP_, sizeof(PARA_STUDENT_EXP_)-1) == 0)
				{
					/*char	szNum[256]	= "0";
					CTutorexpData*	pExpData;
					pExpData = CTutorexpData::CreateNew();
					if (pExpData)
					{
						if (pExpData->Create(pUser->GetID(), Database()))
						{
							sprintf(szNum, "%u", pExpData->GetInt(TUTOREXPDATA_EXP));
						}
						SAFE_RELEASE (pExpData);
					}
					strcpy(ptr2, szNum);

					ptr		+= sizeof(PARA_STUDENT_EXP_)-1;
					ptr2	+= strlen(szNum);*/
					// continue;
				}
				else if (_strnicmp(ptr, PARA_EXPLOIT_, sizeof(PARA_EXPLOIT_)-1) == 0)
				{
					char	szNum[256]	= "0";
					sprintf(szNum, "%u", pUser->GetExploit());

					strcpy(ptr2, szNum);

					ptr		+= sizeof(PARA_EXPLOIT_)-1;
					ptr2	+= strlen(szNum);
				}
				else if(_strnicmp(ptr, PARA_ENEMY_SYN_, sizeof(PARA_ENEMY_SYN_)-1) == 0 
							&& *(ptr+sizeof(PARA_ENEMY_SYN_)-1) >= '0' && *(ptr+sizeof(PARA_ENEMY_SYN_)-1) < '0'+ MAX_SYNENEMYSIZE)
				{
					char	szNum[256] = "--";
					int		idx = *(ptr+sizeof(PARA_ENEMY_SYN_)-1) - '0';
					if(idx >= 0 && idx < MAX_SYNENEMYSIZE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
						if(pSyn)
						{
							CSynPtr pTarget = SynManager()->QuerySyndicate(pSyn->GetInt((SYNDATA)(SYNDATA_ENEMY0+idx)));
							if(pTarget)
								sprintf(szNum, "%s", pTarget->GetStr(SYNDATA_NAME));
						}
					}
					strcpy(ptr2, szNum);

					ptr	+= sizeof(PARA_ENEMY_SYN_)-1 + 1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ALLY_SYN_, sizeof(PARA_ALLY_SYN_)-1) == 0 
							&& *(ptr+sizeof(PARA_ALLY_SYN_)-1) >= '0' && *(ptr+sizeof(PARA_ALLY_SYN_)-1) < '0'+ MAX_SYNALLYSIZE)
				{
					char	szNum[256] = "--";
					int		idx = *(ptr+sizeof(PARA_ALLY_SYN_)-1) - '0';
					if(idx >= 0 && idx < MAX_SYNALLYSIZE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
						if(pSyn)
						{
							CSynPtr pTarget = SynManager()->QuerySyndicate(pSyn->GetInt((SYNDATA)(SYNDATA_ALLY0+idx)));
							if(pTarget)
								sprintf(szNum, "%s", pTarget->GetStr(SYNDATA_NAME));
						}
					}
					strcpy(ptr2, szNum);

					ptr	+= sizeof(PARA_ALLY_SYN_)-1 + 1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_USER_ID, sizeof(PARA_USER_ID)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pUser->GetID());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_USER_ID)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_USER_MAPID, sizeof(PARA_USER_MAPID)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pUser->GetMapID());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_USER_MAPID)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_USER_MAPX, sizeof(PARA_USER_MAPX)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pUser->GetPosX());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_USER_MAPX)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_USER_MAPY, sizeof(PARA_USER_MAPY)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pUser->GetPosY());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_USER_MAPY)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_USER_HOME, sizeof(PARA_USER_HOME)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pUser->GetHomeID());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_USER_HOME)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_SYN_ID, sizeof(PARA_SYN_ID)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pUser->GetMasterSynID());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_SYN_ID)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_SYN_NAME, sizeof(PARA_SYN_NAME)-1) == 0)
				{
					const char*	pName = SYNNAME_NONE;
					if(pUser->GetSynID() != ID_NONE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
						if(pSyn)
							pName = pSyn->GetStr(SYNDATA_NAME);
					}
					strcpy(ptr2, pName);

					ptr += sizeof(PARA_SYN_NAME)-1;
					ptr2		+= strlen(pName);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_USER_NAME, sizeof(PARA_USER_NAME)-1) == 0)
				{
					strcpy(ptr2, pUser->GetName());

					ptr += sizeof(PARA_USER_NAME)-1;
					ptr2		+= strlen(pUser->GetName());
					// continue;
				}
				else if(_strnicmp(ptr, PARA_MATE_NAME, sizeof(PARA_MATE_NAME)-1) == 0)
				{
					strcpy(ptr2, pUser->GetMate());

					ptr += sizeof(PARA_MATE_NAME)-1;
					ptr2		+= strlen(pUser->GetMate());
					// continue;
				}
				else if(_strnicmp(ptr, PARA_MAP_OWNER_ID, sizeof(PARA_MAP_OWNER_ID)-1) == 0)
				{
					char	szNum[256] = "0";	// ȱʡOWNERIDΪ0
					sprintf(szNum, "%u", pUser->GetMap()->GetOwnerID());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_MAP_OWNER_ID)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				/*else if(_strnicmp(ptr, PARA_MAP_OWNER_TYPE, sizeof(PARA_MAP_OWNER_TYPE)-1) == 0)
				{
					char	szNum[256] = "0";	// ȱʡOWNERIDΪ0
					sprintf(szNum, "%u", pUser->GetMap()->GetOwnerType());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_MAP_OWNER_TYPE)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}*/
				else if(_strnicmp(ptr, PARA_ITER_VALUE, sizeof(PARA_ITER_VALUE)-1) == 0)
				{
					char	szNum[256] = "0";	// ȱʡOWNERIDΪ0
					sprintf(szNum, "%u", pUser->TaskIterator());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITER_VALUE)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_SYN_NAME, sizeof(PARA_ITER_SYN_NAME)-1) == 0)
				{
					const char*	pName = "--";
					if(pUser->TaskIterator() != ID_NONE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate((OBJID)pUser->TaskIterator());
						if(pSyn)
							pName = pSyn->GetStr(SYNDATA_NAME);
					}
					strcpy(ptr2, pName);

					ptr += sizeof(PARA_ITER_SYN_NAME)-1;
					ptr2		+= strlen(pName);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_SYN_LEADER, sizeof(PARA_ITER_SYN_LEADER)-1) == 0)
				{
					const char*	pName = "--";
					if(pUser->TaskIterator() != ID_NONE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate((OBJID)pUser->TaskIterator());
						if(pSyn)
							pName = pSyn->GetStr(SYNDATA_LEADERNAME);
					}
					strcpy(ptr2, pName);

					ptr += sizeof(PARA_ITER_SYN_LEADER)-1;
					ptr2		+= strlen(pName);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_SYN_MONEY, sizeof(PARA_ITER_SYN_MONEY)-1) == 0)
				{
					char	szNum[256] = "--";	// ȱʡOWNERIDΪ0
					if(pUser->TaskIterator() != ID_NONE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate((OBJID)pUser->TaskIterator());
						if(pSyn)
							sprintf(szNum, "%d", pSyn->GetInt(SYNDATA_MONEY));
					}
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITER_SYN_MONEY)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_SYN_AMOUNT, sizeof(PARA_ITER_SYN_AMOUNT)-1) == 0)
				{
					char	szNum[256] = "--";	// ȱʡOWNERIDΪ0
					if(pUser->TaskIterator() != ID_NONE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate((OBJID)pUser->TaskIterator());
						if(pSyn)
							sprintf(szNum, "%u", pSyn->GetSynAmount());
					}
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITER_SYN_AMOUNT)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_SYN_FEALTY, sizeof(PARA_ITER_SYN_FEALTY)-1) == 0)
				{
					char	szNum[256] = "--";	// ȱʡOWNERIDΪ0
					if(pUser->TaskIterator() != ID_NONE)
					{
						CSynPtr pSyn = SynManager()->QuerySyndicate((OBJID)pUser->TaskIterator());
						if(pSyn)
							sprintf(szNum, "%u", pSyn->GetFealtyName());
					}
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITER_SYN_FEALTY)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_MEMBER_RANK, sizeof(PARA_ITER_MEMBER_RANK)-1) == 0)
				{
					const char*	pName = "--";
					if(pUser->TaskIterator() != ID_NONE)
					{
						CUser* pTheUser = UserManager()->GetUser((OBJID)pUser->TaskIterator());
						if(pTheUser && pTheUser->GetSynID())
							pName = pTheUser->QuerySynAttr()->GetRankTitle();
					}
					strcpy(ptr2, pName);

					ptr += sizeof(PARA_ITER_MEMBER_RANK)-1;
					ptr2		+= strlen(pName);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_MEMBER_NAME, sizeof(PARA_ITER_MEMBER_NAME)-1) == 0)
				{
					const char*	pName = "--";
					if(pUser->TaskIterator() != ID_NONE)
					{
						CUser* pTheUser = UserManager()->GetUser((OBJID)pUser->TaskIterator());
						if(pTheUser)
							pName = pTheUser->GetName();
					}
					strcpy(ptr2, pName);

					ptr += sizeof(PARA_ITER_MEMBER_NAME)-1;
					ptr2		+= strlen(pName);
					// continue;
				}
				/*else if(_strnicmp(ptr, PARA_ITER_MEMBER_PROFFER, sizeof(PARA_ITER_MEMBER_PROFFER)-1) == 0)
				{
					char	szNum[256] = "--";	// ȱʡOWNERIDΪ0
					if(pUser->TaskIterator() != ID_NONE)
					{
						CUser* pTheUser = UserManager()->GetUser((OBJID)pUser->TaskIterator());
						if(pTheUser && pTheUser->GetSynID() != ID_NONE)
							sprintf(szNum, "%d", pTheUser->QuerySynAttr()->GetInt(SYNATTRDATA_PROFFER));
					}
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITER_MEMBER_PROFFER)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}*/
				else if (_strnicmp(ptr, PARA_ITER_TABLE_DATASTR, sizeof(PARA_ITER_TABLE_DATASTR)-1) == 0)
				{
					CHECK(pNpc && pNpc->QueryTable());
					CTableData* pData = pNpc->QueryTable()->QuerySet()->GetObj(pUser->TaskIterator());
					CHECK(pData);

					strcpy(ptr2, pData->GetStr(TABLEDATA_DATASTR));

					ptr += sizeof(PARA_ITER_TABLE_DATASTR)-1;
					ptr2		+= strlen(pData->GetStr(TABLEDATA_DATASTR));
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_TABLE_DATA_, sizeof(PARA_ITER_TABLE_DATA_)-1) == 0 
							&& *(ptr+sizeof(PARA_ITER_TABLE_DATA_)-1) >= '0' && *(ptr+sizeof(PARA_ITER_TABLE_DATA_)-1) < '0'+ TABLEDATA_SIZE)
				{
					CHECK(pNpc && pNpc->QueryTable());
					CTableData* pData = pNpc->QueryTable()->QuerySet()->GetObj(pUser->TaskIterator());
					CHECK(pData);

					char	szNum[256] = "--";
					int		idx = *(ptr+sizeof(PARA_ITER_TABLE_DATA_)-1) - '0';
					if(idx >= 0 && idx < TABLEDATA_SIZE)
						sprintf(szNum, "%d", pData->GetInt(TABLEDATA(TABLEDATA_DATA0 + idx)));
					strcpy(ptr2, szNum);

					ptr	+= sizeof(PARA_ITER_TABLE_DATA_)-1 + 1;		//+1 : index
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITER_ITEM_DATA, sizeof(PARA_ITER_ITEM_DATA)-1) == 0)
				{
					char	szNum[256] = "(err)";
					CItem* pItem = pUser->GetItem(pUser->TaskIterator());
					IF_OK(pItem)
					//	sprintf(szNum, "%u", pItem->GetInt(ITEMDATA_DATA));
					//strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITER_ITEM_DATA)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				//---����ϵͳ---begin
				else if(_strnicmp(ptr, PARA_ITER_TASK_USERNAME, sizeof(PARA_ITER_TASK_USERNAME)-1) == 0)
				{
					//�������Ӧ���û���
					char szName[128];
					CTaskDetail * pTask = pUser->GetTaskDetail();
					CHECK(pTask);
					CTaskDetailData * pTaskData = pTask->QueryData(pUser->TaskIterator());
					CHECK(pTaskData);
					OBJID idUser = pTaskData->GetInt(TASKDETAILDATA_USERID);
					CUser * pUser = UserManager()->GetUser(idUser);
					CHECK(pUser);
					
					sprintf(szName,"%s",pUser->GetName());
					
					strcpy(ptr2, szName);

					ptr += sizeof(PARA_ITER_TASK_USERNAME)-1;
					ptr2		+= strlen(szName);
					// continue;
				}  
				else if(_strnicmp(ptr, PARA_ITER_TASK_COMPLETENUM, sizeof(PARA_ITER_TASK_COMPLETENUM)-1) == 0)
				{
					//������ɴ���
					char szBuff[128];

					CTaskDetail * pTask = pUser->GetTaskDetail();
					CHECK(pTask);
					CTaskDetailData * pTaskData = pTask->QueryData(pUser->TaskIterator());
					CHECK(pTaskData);

					sprintf(szBuff,"%d",pTaskData->GetInt(TASKDETAILDATA_TASKCOMPLETENUM));

					strcpy(ptr2, szBuff);

					ptr += sizeof(PARA_ITER_TASK_COMPLETENUM)-1;
					ptr2		+= strlen(szBuff);

				}
				else if(_strnicmp(ptr, PARA_ITER_TASK_BEGINTIME, sizeof(PARA_ITER_TASK_BEGINTIME)-1) == 0)
				{
					//����Ŀ�ʼʱ��
					char szBuff[128];

					CTaskDetail * pTask =pUser->GetTaskDetail();
					CHECK(pTask);
					CTaskDetailData * pTaskData = pTask->QueryData(pUser->TaskIterator());
					CHECK(pTaskData);

					time_t ltime = pTaskData->GetInt(TASKDETAILDATA_TASKBEGINTIME);
					struct tm *pTime;
					pTime = localtime( &ltime );
					CHECK(pTime);
					
					int nYear, nMonth, nDay, nHour, nMinute, nSec;
					nYear	=pTime->tm_year+1900;
					nMonth	=pTime->tm_mon+1;
					nDay	=pTime->tm_mday;					
					nHour	=pTime->tm_hour;
					nMinute	=pTime->tm_min;
					nSec    = pTime->tm_sec;

					sprintf(szBuff,"%d-%02d-%02d %02d:%02d:%02d",nYear,nMonth,nDay,nHour,nMinute,nSec);

					strcpy(ptr2, szBuff);

					ptr += sizeof(TASKDETAILDATA_TASKBEGINTIME)-1;
					ptr2		+= strlen(szBuff);

				}
				//---����ϵͳ---end

			}
			if(pNpc)
			{
				/*if (_strnicmp(ptr, PARA_DATASTR, sizeof(PARA_DATASTR)-1) == 0)
				{
					strcpy(ptr2, pNpc->GetStr(NPCDATA_DATASTR));

					ptr += sizeof(PARA_DATASTR)-1;
					ptr2		+= strlen(pNpc->GetStr(NPCDATA_DATASTR));
					// continue;
				}
				else */
				if(_strnicmp(ptr, PARA_DATA_, sizeof(PARA_DATA_)-1) == 0 
							&& *(ptr+sizeof(PARA_DATA_)-1) >= '0' && *(ptr+sizeof(PARA_DATA_)-1) < '0'+ MAX_NPCDATA)
				{
					char	szNum[256] = "";
					int		idx = *(ptr+sizeof(PARA_DATA_)-1) - '0';
					if(idx >= 0 && idx < MAX_NPCDATA)
						sprintf(szNum, "%d", pNpc->GetData(idx));
					strcpy(ptr2, szNum);

					ptr	+= sizeof(PARA_DATA_)-1 + 1;		//+1 : index
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_NAME, sizeof(PARA_NAME)-1) == 0)
				{
					strcpy(ptr2, pNpc->GetName());

					ptr += sizeof(PARA_NAME)-1;
					ptr2		+= strlen(pNpc->GetStr(NPCDATA_NAME));
					// continue;
				}
				else if(_strnicmp(ptr, PARA_NPC_ID, sizeof(PARA_NPC_ID)-1) == 0)
				{
					char	szNum[256] = "0";
					sprintf(szNum, "%u", pNpc->GetRecordID());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_NPC_ID)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_NPC_X, sizeof(PARA_NPC_X)-1) == 0)
				{
					char	szNum[256] = "0";
					sprintf(szNum, "%u", pNpc->GetPosX());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_NPC_X)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_NPC_Y, sizeof(PARA_NPC_Y)-1) == 0)
				{
					char	szNum[256] = "0";
					sprintf(szNum, "%u", pNpc->GetPosY());
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_NPC_Y)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_NPC_OWNERID, sizeof(PARA_NPC_OWNERID)-1) == 0)
				{
					char	szNum[256] = "0";
					sprintf(szNum, "%u", pNpc->GetInt(NPCDATA_OWNERID));
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_NPC_OWNERID)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
			}
			if(pItem)
			{
				if(_strnicmp(ptr, PARA_ITEM_TYPE, sizeof(PARA_ITEM_TYPE)-1) == 0)
				{
					char	szNum[256] = "";
					sprintf(szNum, "%u", pItem->GetInt(ITEMDATA_SORT));
					strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITEM_TYPE)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
				else if(_strnicmp(ptr, PARA_ITEM_DATA, sizeof(PARA_ITEM_DATA)-1) == 0)
				{
					char	szNum[256] = "";
					//sprintf(szNum, "%u", pItem->GetInt(ITEMDATA_DATA));
					//strcpy(ptr2, szNum);

					ptr += sizeof(PARA_ITEM_DATA)-1;
					ptr2		+= strlen(szNum);
					// continue;
				}
			}
			
			// fill space
			if(nWidth)
			{
				while(ptr2 < pNext)
					*(ptr2++)	= ' ';
			}
		} // %
		else
		{
			*ptr2	= *ptr;

			ptr++;
			ptr2++;
		}
	} // while
	*ptr2	= 0;
}

////////////////////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessAction(OBJID idAction, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	if (idAction == ID_NONE)
		return false;

	m_pUser	= pUser;
	m_pRole	= pRole;
	m_pItem	= pItem;

	try
	{
		// process action...
		const int _MAX_ACTIONPRC	=32;
		DWORD dwActionCount	=0;
		while (idAction != ID_NONE)
		{
			DEADLOOP_CHECK(PID, "idAction: ")

			CActionData* pAction = ActionSet()->GetObj(idAction);
			if (!pAction)
			{
				::LogSave("Error: game action %u not found.", idAction);
				break;
			}

			char	szParam[1024];
			ReplaceAttrStr(szParam, pAction->GetStr(ACTIONDATA_PARAM), m_pUser, m_pRole, m_pItem, pszAccept);
			szParam[255]	= 0;			// �ض�

			//? FOR DEBUG
			if(m_pUser && m_pUser->IsPM())
			{
				char	szMsg[1024];
				sprintf(szMsg, "%d: [%d,%d]. type[%d], data[%d], param:[%s].", 
						pAction->GetID(),
						pAction->GetInt(ACTIONDATA_IDNEXT),
						pAction->GetInt(ACTIONDATA_IDNEXTFAIL),
						pAction->GetInt(ACTIONDATA_TYPE), 
						pAction->GetInt(ACTIONDATA_DATA),
						szParam);
// '%' in szMsg				this->SendSysMsg(_TXTATR_NORMAL, "ACTION: %s", szMsg);
				szMsg[255]	= 0;
				CMsgTalk msg;
				if (msg.Create(SYSTEM_NAME, m_pUser->GetName(), szMsg, NULL, 0x00ffff00, _TXTATR_NORMAL))
					m_pUser->SendMsg(&msg);
			}

			// process action now!
			bool	bRet = false;
			int nActionType = pAction->GetInt(ACTIONDATA_TYPE);
			if (nActionType > ACTION_MAM_FIRST && nActionType < ACTION_MAM_LIMIT)
				bRet	= ProcessActionMAM(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_SYS_FIRST && nActionType < ACTION_SYS_LIMIT)
				bRet	= ProcessActionSys	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_NPC_FIRST && nActionType < ACTION_NPC_LIMIT)
				bRet	= ProcessActionNpc	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_MAP_FIRST && nActionType < ACTION_MAP_LIMIT)
				bRet	= ProcessActionMap	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_ITEMONLY_FIRST && nActionType < ACTION_ITEMONLY_LIMIT)
				bRet	= ProcessActionItemOnly	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_ITEM_FIRST && nActionType < ACTION_ITEM_LIMIT)
				bRet	= ProcessActionItem	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_NPCONLY_FIRST && nActionType < ACTION_NPCONLY_LIMIT)
				bRet	= ProcessActionNpcOnly	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_SYN_FIRST && nActionType < ACTION_SYN_LIMIT)
				bRet	= ProcessActionSyn	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_USER_FIRST && nActionType < ACTION_USER_LIMIT)
				bRet	= ProcessActionUser	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_EVENT_FIRST && nActionType < ACTION_EVENT_LIMIT)
				bRet	= ProcessActionEvent	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_TRAP_FIRST && nActionType < ACTION_TRAP_LIMIT)
				bRet	= ProcessActionEvent	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_WANTED_FIRST && nActionType < ACTION_WANTED_LIMIT)
				bRet	= ProcessActionWanted	(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_MST_FIRST && nActionType < ACTION_MST_LIMIT)
				bRet	= ProcessActionMonster (pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else if(nActionType > ACTION_MAP_FIRST && nActionType < ACTION_MAGIC_LIMIT)
				bRet	= ProcessActionMagic(pAction, szParam, m_pUser, m_pRole, m_pItem, pszAccept);
			else
			{
				ASSERT(!"Error action type!");
			}

			if (bRet)
				idAction	= pAction->GetInt(ACTIONDATA_IDNEXT);
			else
				idAction	= pAction->GetInt(ACTIONDATA_IDNEXTFAIL);

			if (dwActionCount++ >= _MAX_ACTIONPRC)
			{
				::LogSave("Error: too many game action, last action:%u.", idAction);
				break;
			}
		} // while
	}
	catch(...)
	{
		ASSERT(!"catch");
		::LogSave("Error: exception caught in CGameAction::ProcessAction(%u)", idAction);
	}

	return true;
}

bool CGameAction::ProcessActionMAM(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction);

	switch (pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_ITEM_ADD:
	{
		CItem* pItem = pUser->AwardItem(pAction->GetInt(ACTIONDATA_DATA), SYNCHRO_FALSE, false, CUser::NO_COMBINE);
		if (pItem)
		{
			std::string strParam(szParam);
			std::istringstream iss(strParam);
			std::string token;
			//Modify item values by Param
			while (std::getline(iss, token, ' '))
			{
				std::string strUpdate;
				char* cTest;
				int nUpdate;
				if (token.find("name:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					pItem->SetStr(ITEMDATA_NAME, strUpdate.c_str(), strUpdate.length());
				}
				if (token.find("inventor:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					pItem->SetStr(ITEMDATA_INVENTOR, strUpdate.c_str(), strUpdate.length());
				}

				if (token.find("cost:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_COST, nUpdate);
				}

				if (token.find("action:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_ACTION, nUpdate);
				}

				if (token.find("exp:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_EXP, nUpdate);
				}

				if (token.find("life:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_LIFE, nUpdate);
				}

				if (token.find("mana:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_POWER, nUpdate);
				}

				if (token.find("attack:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_ATTACK, nUpdate);
				}

				if (token.find("defence:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_DEFENCE, nUpdate);
				}

				if (token.find("dexterity:") != std::string::npos) {
					strUpdate = token.substr(token.find(':') + 1, std::string::npos);
					nUpdate = std::strtoul(strUpdate.c_str(), &cTest, 10);
					if (cTest) pItem->SetInt(ITEMDATA_DEXTERITY, nUpdate);
				}

				pItem->SaveInfo();
			}

			// synchro
			CMsgItemInfo msg;
			if (msg.Create(pItem, ITEMINFO_ADDITEM))
				pUser->SendMsg(&msg);
			return true;
		}
	} break;
	case ACTION_NPC_DIALOGUE:
	{
		char szMessage[MAX_PARAMSIZE];
		int nTriggerTask = 0;
		int nRes = sscanf(szParam, "%s %d", szMessage, &nTriggerTask);
		if (nRes == 1) {
			pUser->PushDialogueMessage(szMessage);
		}
		else if (nRes == 2)
		{
			pUser->PushDialogueResponse(szMessage, nTriggerTask);
		}
		else {
			LOGERROR("ACTION %u: TYPE %u - No param", pAction->GetID(), pAction->GetInt(ACTIONDATA_TYPE));
			break;
		}

		return true;
	} break;
	case ACTION_NPC_DIALOGUE_SEND: 
	{
		int nFace = 0;
		int nCancelTask = 0;
		int nRes = sscanf(szParam, "%u %u", &nFace, &nCancelTask);
		if (nRes > 0) pUser->SendDialogue(nFace, nCancelTask);
		else {
			LOGERROR("ACTION %u: TYPE %u - No param", pAction->GetID(), pAction->GetInt(ACTIONDATA_TYPE));
			break;
		}

		return true;
	} break;
	default:
		LOGERROR("Unsupported ACTION[%u] TYPE[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	} // switch

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionMonster(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	IF_NOT (pAction)
		return false;

	CAiNpc* pMonster = NULL;
	IF_NOT (pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)))
		return false;

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_MST_DROPITEM:
		{
			// monster��ɱ�������Ʒ����Ǯ, param "dropitem itemtype"����"dropmoney money [LowPercent]"
			
			char szCmd[MAX_PARAMSIZE] = "";
			if (1 != sscanf(szParam, "%s", szCmd))
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			
			if (0 == _stricmp(szCmd, "dropitem"))
			{
				DWORD dwData = 0;
				if (2 == sscanf(szParam, "%s %u", szCmd, &dwData))
				{
					if (0 == _stricmp(szCmd, "dropitem"))
					{
						OBJID idUser = ID_NONE;
						if (pUser)
							idUser = pUser->GetID();
						
						if (pMonster->DropItem(dwData, idUser))
							return true;
					}
				}
				else
				{
					LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
					break;
				}
			}
			else if (0 == _stricmp(szCmd, "dropmoney"))
			{
				DWORD dwData=0, dwLowPercent=0;
				int rval = sscanf(szParam, "%s %u %u", szCmd, &dwData, &dwLowPercent);
				if (rval == 2)
					dwLowPercent = 100;
				else if (rval == 3)
					dwLowPercent %= 100;
				else
				{
					LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
					break;
				}
				
				DWORD dwMoneyDrop = dwData*(dwLowPercent+::RandGet(100-dwLowPercent))/100;
				if (dwMoneyDrop <= 0)
					return false;
				
				OBJID idUser = ID_NONE;
				if (pUser)
					idUser = pUser->GetID();
				
				if (pMonster->DropMoney(dwMoneyDrop, idUser))
					return true;
			}
			else if (0 == _stricmp(szCmd, "droptrap"))//monster��ɱ���������, param "droptrap traptype lifeperiod"��
			{
				/*OBJID idTrapId=NULL;				

				UINT uiLifePeriod=0;

				if (3 == sscanf(szParam, "%s %u %u", szCmd, &idTrapId,&uiLifePeriod))
				{
					if (0 == _stricmp(szCmd, "droptrap"))
					{
						TRAP_INFO	info;
						memset(&info, 0, sizeof(TRAP_INFO));
						info.usType = idTrapId;
						


						if (pMonster->DropTrap(info,uiLifePeriod))
							return true;
					}
				}*/
			}
		}
		break;
	case	ACTION_MST_MAGIC:
		{
			if (!pRole->QueryMagic())
				return false;

			PARAMBUF	szCmd;
			int			nType;
			int			nLevel=0;
			bool		bSave=true;
			int	nNum = 0;
			if((nNum=sscanf(szParam, "%s %u %u %u", szCmd, &nType, &nLevel, &bSave)) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			
			if(_stricmp(szCmd, "check") == 0)
			{
				if(nNum == 3)
					return pRole->QueryMagic()->CheckLevel(nType, nLevel);
				else
					return pRole->QueryMagic()->CheckType(nType);
			}
			else if(_stricmp(szCmd, "learn") == 0)
			{
				return pRole->QueryMagic()->LearnMagic(nType, nLevel, bSave) != ID_NONE;
			}
			else if(_stricmp(szCmd, "uplevel") == 0)
			{
				return pRole->QueryMagic()->UpLevelByTask(nType);
			}
			else
			{
				ASSERT(!"ACTION_USER_MAGIC ����Ĳ�������!");
			}
			return true;
		}
		break;
		
	default:
		LOGERROR("�����Action Type", pAction->GetInt(ACTIONDATA_TYPE));
		break;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionSys(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_BROCASTMSG:
		{
			CMsgTalk msg;
			if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szParam, NULL, _COLOR_WHITE, pAction->GetInt(ACTIONDATA_DATA)))
				RoleManager()->BroadcastMsg(&msg);
		}
		break;

	case	ACTION_POSTCMD:
		{
			if (pUser)
			{
				CMsgAction msg;
				IF_OK (msg.Create(	pUser->GetID(), 
									pUser->GetPosX(), 
									pUser->GetPosY(), 
									pUser->GetDir(), 
									actionPostCmd,
									pAction->GetInt(ACTIONDATA_DATA) ))
					pUser->SendMsg(&msg);

				return true;
			}
		}
		break;

	case	ACTION_CHKTIME:
		{
			if (CMapGroup::CheckTime(pAction->GetInt(ACTIONDATA_DATA), szParam))
				return true;
		}
		break;

	case	ACTION_MENUTEXT:
		{
			if(!pUser)
			{
				LOGERROR("Can't find user object when action[%d].", pAction->GetID());
				return false;
			}

			//CMsgDialog	msg;
			//CHECKF(msg.Create(MSGDIALOG_TEXT, szParam, INDEX_NONE, pAction->GetInt(ACTIONDATA_DATA)));
			//pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_MENULINK:
		{
			CHECKF(pUser);

			PARAMBUF	szText;
			OBJID		idTask;
			int			nAlign = 0;
			if(sscanf(szParam, "%s %u %d", szText, &idTask, &nAlign) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			//CMsgDialog	msg;
			//CHECKF(msg.Create(MSGDIALOG_LINK, szText, pUser->PushTaskID(idTask), nAlign));
			//pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_MENUEDIT:
		{
			CHECKF(pUser);

			int			nAcceptLen;
			OBJID		idTask;
			PARAMBUF	szText = "";
			if(sscanf(szParam, "%d %u %s", &nAcceptLen, &idTask, szText) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			//CMsgDialog	msg;
			//CHECKF(msg.Create(MSGDIALOG_EDIT, szText, pUser->PushTaskID(idTask), nAcceptLen));
			//pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_MENUPIC:
		{
			CHECKF(pUser);

			int			x;
			int			y;
			OBJID		idPic;
			OBJID		idTask = ID_NONE;
			if(sscanf(szParam, "%d %d %u %u", &x, &y, &idPic, &idTask) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			//CMsgDialog	msg;
			//CHECKF(msg.Create(MSGDIALOG_PIC, x, y, idPic, pUser->PushTaskID(idTask)));
			//pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_MENUBUTTON:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
		break;
	case	ACTION_MENULISTPART:
		{
			CHECKF(pUser);

			OBJID		idTask;
			OBJID		idIter;
			if(sscanf(szParam, "%u %u ", &idTask, &idIter) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			char* pszText = (char*)strchr(szParam, ' ');
			CHECKF(pszText);
			pszText = strchr(pszText+1, ' ');
			CHECKF(pszText);
			pszText++;
			CHECKF(*pszText);

			//CMsgDialog	msg;
			//CHECKF(msg.Create(MSGDIALOG_LISTLINE, pszText, pUser->PushTaskID(idTask, idIter), idIter));
			//pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_MENUCREATE:
		{
			CHECKF(pUser);

			OBJID		idTask = ID_NONE;
			sscanf(szParam, "%u", &idTask);

			//CMsgDialog	msg;
			//CHECKF(msg.Create(MSGDIALOG_CREATE, pUser->PushTaskID(idTask)));
			//pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_RAND:
		{
			int		nData1, nData2;
			if(sscanf(szParam, "%u %u", &nData1, &nData2) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(::RandGet(nData2) < nData1)
				return true;
			else
				return false;
		}
		break;

	case ACTION_RANDACTION:
		{
			// �������ʡ�"action0 .... action7"
			OBJID idAction[8];
			if (8 == sscanf(szParam, "%u %u %u %u %u %u %u %u", 
				&idAction[0], &idAction[1], &idAction[2], &idAction[3],
				&idAction[4], &idAction[5], &idAction[6], &idAction[7]))
			{
				ProcessAction(idAction[::RandGet(8)], pUser, pRole, pItem, pszAccept);
				return true;
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case ACTION_MESSAGEBOX:
		{
			if(pUser)
			{
				int nChannel = _TXTATR_MESSAGEBOX;
				if(pAction->GetInt(ACTIONDATA_DATA) > 0 && pAction->GetInt(ACTIONDATA_DATA) < _TXTATR_DIALOG_END - _TXTATR_DIALOG_BEGIN)
					nChannel = pAction->GetInt(ACTIONDATA_DATA) + _TXTATR_DIALOG_BEGIN;

				CMsgTalk	msg;
				IF_OK(msg.Create(nChannel, szParam))
					pUser->SendMsg(&msg);

				return true;
			}
		}
		break;

	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	} // switch

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionNpc(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction);
		
	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case ACTION_NPC_DRESS_SYNCLOTHING://�����ɷ�װ
		{
			CNpc* pNpc=NULL;
			CHECKF(pRole);

			if(!pUser->GetMap()->IsSynMap())
				return false;
			
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			if(pNpc->GetSynID() != pUser->GetSynID())
			{
				return false;
			}

			int nData0 = pNpc->GetData(SYNDRESS_SORT);
			if(!(nData0>=0&&nData0<5))//5����ɷ�װ
				return false;
			int nData1 = pNpc->GetData(SYNDRESS_SETTING);
						
			char szData1[16];
			sprintf(szData1,"%d",nData1);
			
			OBJID idMap = pUser->GetMapID();
			DWORD dwSynID = pUser->GetSynID();
			int nLevel=0, nRank=0;
			
			int nIndex=0; //���ɷ�װ���������
			nLevel = pUser->QuerySynAttr()->GetSynMemberLevel();						
			nRank= pUser->GetSyndicate()->GetInt(SYNDATA_RANK);
			
			if(nRank==RANK_TEAMLEADER||nLevel==SYNMEM_LEVEL_THREE||nLevel==SYNMEM_LEVEL_FOUR)
				nIndex = 1;
			else if(nRank==RANK_SUBLEADER||nLevel==SYNMEM_LEVEL_FIVE)							
				nIndex = 2;
			else if(nRank==RANK_LEADER)
				nIndex = 3;
			else //��ͨ
				nIndex =0;
			
			if(nData1!=0)
			{
				char cColor= szData1[nIndex]-1;
				nData1 = atoi(&cColor);
			}
			char szFlag[7];
			sprintf(szFlag,"137%d%d0",nData1,nData0);
			
			pUser->SetSynDressArmorType(atoi(szFlag));

//			pUser->SendSelfToBlock();
		
			CMsgUserAttrib msgAtt;
			if (msgAtt.Create(pUser->GetID(), _USERATTRIB_ARMORTYPE, pUser->GetArmorTypeID()))
			{
				pUser->SendMsg(&msgAtt);
			}
			return true;
		}		
		break;
	case ACTION_NPC_TAKEOFF_SYNCLOTHING://�Ѱ��ɷ�װ
		{	
			CNpc* pNpc=NULL;
			CHECKF(pRole);
			
			if(!pUser->GetMap()->IsSynMap())
				return false;	
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			
			pUser->SetSynDressArmorType(0);
			
//			pUser->SendSelfToBlock();		

			CMsgUserAttrib msgAtt;
			if (msgAtt.Create(pUser->GetID(), _USERATTRIB_ARMORTYPE, pUser->GetArmorTypeID()))
			{
				pUser->SendMsg(&msgAtt);
			}

			return true;
		}
		break;
	case	ACTION_NPC_ATTR:
		{
			PARAMBUF	szAttr;
			PARAMBUF	szOpt;
			PARAMBUF	szData;
			OBJID		idTargetNpc = ID_NONE;
			if(sscanf(szParam, "%s %s %s %u", szAttr, szOpt, szData, &idTargetNpc) < 4)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			int		nData = atoi(szData);
			bool	bUpdate = UPDATE_FALSE;

			CNpc* pNpc=NULL;
			if(idTargetNpc != ID_NONE)
			{
				pNpc = RoleManager()->QueryDynNpcByRecordID(idTargetNpc);
			}
			else
			{
				CHECKF(pRole);
				pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc));
			}
			IF_NOT(pNpc)
			{
				LOGERROR("Can't find npc_id[%u] in action[%u].", idTargetNpc, pAction->GetID());
				return false;
			}

			if(_stricmp(szAttr, "ownerid") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetInt(NPCDATA_OWNERID, nData, bUpdate);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if(pNpc->GetInt(NPCDATA_OWNERID) == nData)
						return true;
				}
			}
			/*else if(_stricmp(szAttr, "ownertype") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetInt(NPCDATA_OWNERTYPE, nData, bUpdate);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if(pNpc->GetInt(NPCDATA_OWNERTYPE) == nData)
						return true;
				}
			}*/
			else if(_stricmp(szAttr, "look") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetInt(NPCDATA_LOOK, nData, bUpdate);

					CMsgUserAttrib	msg;
					IF_OK(msg.Create(pNpc->GetID(), _USERATTRIB_LOOKFACE, nData))
						pNpc->BroadcastRoomMsg(&msg);

					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if(pNpc->GetInt(NPCDATA_LOOK) == nData)
						return true;
				}
			}
			/*else if(_stricmp(szAttr, "datastr") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetInt(NPCDATA_DATASTR, nData, bUpdate);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if(pNpc->GetInt(NPCDATA_DATASTR) == nData)
						return true;
				}
			}*/
			else if(_strnicmp(szAttr, "data", 4) == 0)
			{
				if(_stricmp(szData, "accept") == 0)
				{
					nData	= atol(pszAccept);
				}

				int idx = (*(szAttr+4) - '0');
				if(idx < 0 || idx >= MAX_NPCDATA)
					return false;
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetData(idx, nData, bUpdate);
					return true;
				}
				else if(strcmp(szOpt, "+=") == 0)
				{
					pNpc->SetData(idx, pNpc->GetData(idx) + nData, bUpdate);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if(pNpc->GetData(idx) == nData)
						return true;
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					if(pNpc->GetData(idx) < nData)
						return true;
				}
				else if(strcmp(szOpt, "<=") == 0)
				{
					if(pNpc->GetData(idx) <= nData)
						return true;
				}
				else if(strcmp(szOpt, ">") == 0)
				{
					if(pNpc->GetData(idx) > nData)
						return true;
				}
				else if(strcmp(szOpt, ">=") == 0)
				{
					if(pNpc->GetData(idx) >= nData)
						return true;
				}
				else if(strcmp(szOpt, "pass") == 0)
				{
					pNpc->SetData(idx, ::DateStampPass(pNpc->GetData(idx), nData), bUpdate);
					return true;
				}
			}
			/*else if(_stricmp(szAttr, "life") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetInt(NPCDATA_LIFE, nData, bUpdate);

					CMsgUserAttrib	msg;
					IF_OK(msg.Create(pNpc->GetID(), _USERATTRIB_LIFE, nData))
						pNpc->BroadcastRoomMsg(&msg);

					return true;
				}
			}*/
			/*else if(_stricmp(szAttr, "maxlife") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pNpc->SetInt(NPCDATA_MAXLIFE, nData, bUpdate);

					CMsgUserAttrib	msg;
					IF_OK(msg.Create(pNpc->GetID(), _USERATTRIB_MAXLIFE, nData))
						pNpc->BroadcastRoomMsg(&msg);

					return true;
				}
			}*/
			else
			{
				LOGERROR("��֧�ֵ�ACTION[%u]����[%s]", pAction->GetKey(), szAttr);
			}

			return false;
		}
		break;
	case	ACTION_NPC_MODIFY:
		{
			OBJID		idTarget;
			PARAMBUF	szAttr;
			PARAMBUF	szOpt;
			PARAMBUF	szData;
			if(sscanf(szParam, "%u %s %s %s", &idTarget, szAttr, szOpt, szData) < 4)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			int		nData = atoi(szData);
			bool	bUpdate = UPDATE_FALSE;

			CNpc*	pTarget = RoleManager()->QueryDynNpcByRecordID(idTarget);
			if(!pTarget)
			{
				MapGroup(PID)->QueryIntraMsg()->ModifyNpc(idTarget, szAttr, szData);
				return true;
			}

			if(_stricmp(szAttr, "lookface") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pTarget->SetInt(NPCDATA_LOOK, nData, bUpdate);

					CMsgUserAttrib	msg;
					IF_OK(msg.Create(pTarget->GetID(), _USERATTRIB_LOOKFACE, nData))
						pTarget->BroadcastRoomMsg(&msg);

					return true;
				}
			}
			/*else if(_stricmp(szAttr, "datastr") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pTarget->SetStr(NPCDATA_DATASTR, szData, _MAX_NAMESIZE, bUpdate);
					return true;
				}
			}*/
			else if(_strnicmp(szAttr, "data", 4) == 0)
			{
				int idx = (*(szAttr+4) - '0');
				if(idx < 0 || idx >= MAX_NPCDATA)
					return false;
				if(strcmp(szOpt, "=") == 0)
				{
					pTarget->SetData(idx, nData, bUpdate);
					return true;
				}
			}
			else
			{
				LOGERROR("��֧�ֵ�ACTION[%u]����[%s]", pAction->GetKey(), szAttr);
			}

			return false;
		}
		break;
/*	case	ACTION_NPC_REQUESTSHIFT:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;

			OBJID	idNextTask;
			if(sscanf(szParam, "%u", &idNextTask) < 1)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			CHECKF(idNextTask != ID_NONE);
			ClearTaskID();
			PushTaskID(idNextTask);

			CMsgNpc		msg;
			IF_OK(msg.Create(EVENT_CHANGEPOS, pNpc->GetID()))
				SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_NPC_SHIFT:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;

			CHECKF(pszAccept && strlen(pszAccept) > 0)

			int x, y, nLook;
			IF_NOT_(sscanf(pszAccept, "%d %d %d", &x, &y, &nLook) == 3)	XXX	// MsgNpcInfoת���ɴ����ṩ������ϵͳ
				return false;

			if(::MaskLook(pNpc->GetLookFace()) == ::MaskLook(nLook))
				pNpc->SetInt(NPCDATA_LOOKFACE, nLook);
			pNpc->TransPos(x, y);		// synchro true
			return true;
		}
		break;
*/
	case	ACTION_NPC_ERASE:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;

			if(pNpc->IsDeleted())
				return false;

			int	nType = pAction->GetInt(ACTIONDATA_DATA);
			if(nType == 0)
			{
				m_pRole	= NULL;			// �������NPC
				return pNpc->DelNpc();
			}
			else
			{
				for(IRoleSet::Iter i = RoleManager()->QuerySet()->Begin(); i != RoleManager()->QuerySet()->End(); )
				{
					IRole* pRole = RoleManager()->QuerySet()->GetObjByIter(i);
					i++;		// Ҫɾ������ǰ�ƶ�

					CNpc* pNpc;
					if(pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)) && pNpc->GetType() == nType)
					{
						if(!pNpc->DelNpc())
							return false;
					}
				}
				return true;
			}
		}
		break;
	case	ACTION_NPC_RESETSYNOWNER://�µİ���ռ����ɵ�ͼ
		{
			CHECKF(pAction && pRole);
			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			CHECKF(pNpc->IsSynFlag());
			/*
			int		nMaxScore	= 0;
			CSynPtr pMaxSyn		= NULL;
			for(int i = 0; i < SynManager()->QuerySynSet()->GetAmount(); i++)
			{
				CSyndicate* pSyn = SynManager()->QuerySynSet()->GetObjByIndex(i);
				if(pSyn)
				{
					int nScore = pSyn->GetSynWarScore(pNpc->GetID());
					pSyn->ClearSynWarScore(pNpc->GetID());
					if(nMaxScore < nScore)
					{
						nMaxScore	= nScore;
						pMaxSyn		= pSyn;
					}
				}
			}

			if(pMaxSyn && pMaxSyn->GetID() != ID_NONE)
			{
				// gain syn money
				if(pNpc->GetSynID() != ID_NONE)
				{
					CSyndicate* pOldSyn = SynManager()->QuerySyndicate(pNpc->GetSynID());
					if(pOldSyn && pOldSyn->GetInt(SYNDATA_MONEY) > 0)
					{
						int nMoney = MulDiv(pOldSyn->GetInt(SYNDATA_MONEY), SYNWAR_GAINMONEY_PERCENT, 100);
						if(nMoney > 0)
						{
							pOldSyn->QueryModify()->AddData(SYNDATA_MONEY, -1*nMoney);
							pMaxSyn->QueryModify()->AddData(SYNDATA_MONEY, nMoney);
						}
					}
				}  
				}
*/
			CGameMap * pSynMap = pNpc->GetMap();
			IF_NOT(pSynMap->IsSynMap())
				return false;
			
			CNpc * pSynWarLetterNpc = pSynMap->GetNpcSynWarLetter();

			OBJID idSynAtt = pSynWarLetterNpc->GetApplyAttackerSynID();
			CSyndicate * pSynAtt = SynManager()->QuerySyndicate(idSynAtt);
			IF_NOT(pSynAtt)
				return false;

			if(pSynWarLetterNpc)
			{
				int nMoney = pSynWarLetterNpc->GetData(SYNWARLETTER_DEPOSIT);
				pSynAtt->QueryModify()->AddData(SYNDATA_MONEY,nMoney);//��������
			}
			
			pNpc->SetSynOwnerID(pSynAtt->GetID(), false);		// true: with link map
			pNpc->GetMap()->SetSynID(pSynAtt->GetID(), true);		// with all map npc
			pNpc->GetMap()->SetStatus(CGameMap::STATUS_WAR, false);
//			pNpc->SendSelfToBlock();

			//��¼ռ���ʱ��---begin
			pNpc->GetMap()->SetSynOccupyTime();
			//��¼ռ���ʱ��---end			

			MSGBUF	szMsg;
			sprintf(szMsg, STR_GOT_WIN_s, pSynAtt->GetStr(SYNDATA_NAME));

			CMsgTalk msg;
			IF_OK (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szMsg, NULL, _COLOR_WHITE, _TXTATR_GM))
				UserManager()->BroadcastMsg(&msg);

			// stop all auto battal
			CRoleSet::Iterator pRole = RoleManager()->QuerySet()->NewEnum();
			while(pRole.Next())
			{
				if(pRole && pRole->GetMap()->GetID() == pNpc->GetMapID())
					pRole->ClrAttackTarget();
			}
			
			// owner flag
			CGameMap* pMap = pNpc->GetMap();
			if(pMap->GetID() == WHITE_SYN_MAP_ID)
			{
				CMsgSyndicate	msg;
				IF_OK(msg.Create(SET_WHITE_SYN, pMap->GetOwnerID()))
					UserManager()->BroadcastMsg(&msg);
			}
			else if(pMap->GetID() == BLACK_SYN_MAP_ID)
			{
				CMsgSyndicate	msg;
				IF_OK(msg.Create(SET_BLACK_SYN, pMap->GetOwnerID()))
					UserManager()->BroadcastMsg(&msg);
			}
			return true;
		}
		break;
	case	ACTION_NPC_FIND_NEXT_TABLE:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			CHECKF(pNpc->QueryTable());

			int nType = atoi(szParam);
			return pNpc->QueryTable()->FindNext(nType, pUser->TaskIterator());
		}
		break;
	case	ACTION_NPC_ADD_TABLE:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			CHECKF(pNpc->QueryTable());

			int			nType;
			OBJID		idKey;
			int			setData[TABLEDATA_SIZE]	= {0};
			PARAMBUF	szData	= "";
			CHECKF(TABLEDATA_SIZE == 4);
			if(sscanf(szParam, "%d %u %d %d %d %d %s", &nType, &idKey, &setData[0], &setData[1], &setData[2], &setData[3], szData) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			return pNpc->QueryTable()->AddRecord(nType, idKey, setData, szData);
		}
		break;
	case	ACTION_NPC_DEL_TABLE:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			CHECKF(pNpc->QueryTable());

			if(strlen(szParam))
			{
				int			nType;
				OBJID		idKey;
				int			setData[TABLEDATA_SIZE]	= {0};
				PARAMBUF	szData	= "";
				CHECKF(TABLEDATA_SIZE == 4);
				if(sscanf(szParam, "%d %u %d %d %d %d %s", &nType, &idKey, &setData[0], &setData[1], &setData[2], &setData[3], szData) < 2)
				{
					LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
					break;
				}

				return pNpc->QueryTable()->DelRecord(nType, idKey, setData, szData);
			}
			else
			{
				CHECKF(pUser->TaskIterator());
				return pNpc->QueryTable()->DelRecord(pUser->TaskIterator());
			}
		}
		break;
	case	ACTION_NPC_DEL_INVALID:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			CHECKF(pNpc->QueryTable());

			int			nType;
			int			nIndex;
			if(sscanf(szParam, "%d %u", &nType, &nIndex) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			return pNpc->QueryTable()->DelInvalid(nType, nIndex);
		}
		break;
	/*case ACTION_NPC_AUCTIONING:
		{
			CNpc* pNpc;
			IRole* pRole = RoleManager()->QuerySet()->GetObj(pAction->GetInt(ACTIONDATA_DATA));
			if (pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
			{
				CHECKF(pNpc);
				if(pNpc->IsAuctionNpc())
				{
					int nType = 0; 
					if(sscanf(szParam, "%d", &nType))
						return(pNpc->QueryAuction()->CheckAuctionState(nType));
				}
			}
		}
		break;*/
	/*case ACTION_NPC_SYS_AUCTION:
		{
			CNpc* pNpc;
			IRole* pRole = RoleManager()->QuerySet()->GetObj(pAction->GetInt(ACTIONDATA_DATA));
			if (pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
			{
				CHECKF(pNpc);
				if(pNpc->IsAuctionNpc())
				{
					char szInfo[1024] = "NULL";
					if(sscanf(szParam, "%s", szInfo) < 1 )
					{
						LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
					}
					return(pNpc->QueryAuction()->SysAuctionStart(szInfo));
				}
			}  
			return false;
		}
		break;*/
	case	ACTION_NPC_TABLE_AMOUNT:
		{
			CHECKF(pAction && pRole);

			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;
			CHECKF(pNpc->QueryTable());

			return pNpc->QueryTable()->QuerySet()->Size() < pAction->GetInt(ACTIONDATA_DATA);
		}
		break;
	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionMap(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem_no_use, LPCTSTR pszAccept)
{
	CHECKF(pAction);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
/*	case ACTION_MAP_NPC_BROCASTMSG:
		{
			CNpc* pNpc;
			IRole* pRole = RoleManager()->QuerySet()->GetObj(pAction->GetInt(ACTIONDATA_DATA));
			if (pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
			{
				CHECKF(pNpc);
				CMsgTalk msg;
				IF_OK (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szParam, NULL, 0x0ffffff, _TXTATR_SYSTEM))
					UserManager()->BroadcastMapMsg(pNpc->GetMapID(), &msg);
				return true;
			}
		}
		break;*/
	case ACTION_MAP_FIREWORKS:
		{
			IF_OK (pUser)
			{
				CMsgItem msg;
				IF_OK (msg.Create(pUser->GetID(), ITEMACT_FIREWORKS))
					pUser->BroadcastRoomMsg(&msg, true);

				return true;
			}
		}
		break;

	case ACTION_MAP_SETSTATUS:
		{
			OBJID	idMap;
			int		nStatus;
			int		nFlag;
			if (3 == sscanf(szParam, "%u %d %d", &idMap, &nStatus, &nFlag))
			{
				CGameMap* pMap = MapManager()->QueryMap(idMap);
				if (pMap)
				{
					pMap->SetStatus(nStatus, nFlag != 0);
					return true;					
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;
		
	/*case ACTION_MAP_DROPITEM:
		{
			OBJID idItemType = ID_NONE, idMap = ID_NONE;
			POINT pos;
			if (4 == sscanf(szParam, "%u %u %d %d", &idItemType, &idMap, &pos.x, &pos.y))
			{
				CGameMap* pMap = MapManager()->QueryMap(idMap);
				if (pMap && pMap->IsLayItemEnable(pos.x, pos.y))
				{
					CMapItem* pMapItem = CMapItem::CreateNew();
					if (pMapItem)
					{
						if(pMapItem->Create(MapManager()->SpawnMapItemID(), pMap, pos, idItemType, ID_NONE))
						{
							MapManager()->QueryMapItemSet()->AddObj(pMapItem);
							return true;
						}
						else
							pMapItem->ReleaseByOwner();
					}
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;*/

	case	ACTION_MAP_MAPEFFECT:
		{
			OBJID idMap = ID_NONE;
			int nPosX = 0, nPosY = 0;
			char szEffect[256] = "";

			if (4 == sscanf(szParam, "%u %d %d %s", &idMap, &nPosX, &nPosY, szEffect))
			{
				CGameMap* pMap = MapManager()->QueryMap(idMap);
				if (pMap)
				{
					CMsgName msg;
					IF_OK (msg.Create(NAMEACT_MAPEFFECT, szEffect, nPosX, nPosY))
						pMap->BroadcastBlockMsg(nPosX, nPosY, &msg);

					return true;
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_MAP_MOVENPC:
		{
			CNpc* pNpc;
			IRole* pRole = RoleManager()->QuerySet()->GetObj(pAction->GetInt(ACTIONDATA_DATA));
			if (pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
			{
				IF_NOT(!pNpc->IsDynaNpc())
				{
					LOGERROR("ACTION_MAP_MOVENPC �����ڹ̶�NPC[%d]", pNpc->GetID());
					return false;
				}

				OBJID idMap = ID_NONE;
				int nPosX = 0, nPosY = 0;

				if (3 == sscanf(szParam, "%u %d %d", &idMap, &nPosX, &nPosY))
				{
					if (pNpc->ChangePos(idMap, nPosX, nPosY))
						return true;
				}
				else
					LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
			}
		}
		break;

	case	ACTION_MAP_MAPUSER:
		{
			char szCmd[256] = "", szOpt[256] = "";
			int nData = 0;
			if (3 == sscanf(szParam, "%s %s %d", szCmd, szOpt, &nData))
			{
				OBJID idMap = pAction->GetInt(ACTIONDATA_DATA);
				vector<CUser*> setUser;

				if (0 == _stricmp("map_user", szCmd))
				{
					CUserManager::Iterator pUser = UserManager()->NewEnum();
					while(pUser.Next())
					{
						if (pUser && pUser->GetMapID() == idMap)
							setUser.push_back(pUser);
					}
				}
				else if (0 == _stricmp("alive_user", szCmd))
				{
					CUserManager::Iterator pUser = UserManager()->NewEnum();
					while(pUser.Next())
					{
						if (pUser && pUser->GetMapID() == idMap && pUser->IsAlive())
							setUser.push_back(pUser);
					}
				}
				else
				{
					LOGERROR("ACTION %u: �����param����", pAction->GetID());
					return false;
				}


				if (0 == _stricmp(szOpt, "=="))
				{
					if (setUser.size() == nData)
						return true;
				}
				else if (0 == _stricmp(szOpt, "<="))
				{
					if (setUser.size() <= nData)
						return true;
				}
				else if (0 == _stricmp(szOpt, ">="))
				{
					if (setUser.size() >= nData)
						return true;
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_MAP_BROCASTMSG:
		{
			CMsgTalk msg;
			IF_OK (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szParam, NULL, 0x0ffffff, _TXTATR_SYSTEM))
				UserManager()->BroadcastMapMsg(pAction->GetInt(ACTIONDATA_DATA), &msg);

			return true;
		}
		break;

	case	ACTION_MAP_CHANGEWEATHER:
		{
			CHECKF(pUser);

			int nType, nIntensity, nDir, nColor, nKeepSecs;
			if (5 == sscanf(szParam, "%d %d %d %d %d", &nType, &nIntensity, &nDir, &nColor, &nKeepSecs))
			{
				pUser->SetWeather(nType, nIntensity, nDir, nColor, nKeepSecs, 10);
				return true;
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_MAP_CHANGELIGHT:
		{
			DWORD	dwRGB;
			OBJID	idMap = ID_NONE;
			int		nSecs = 0;
			if (3 == sscanf(szParam, "%u %u %d", &idMap, &dwRGB, &nSecs))
			{
				CGameMap* pMap = MapManager()->QueryMap(idMap);
				if (pMap)
				{
					if(nSecs == 0)		// keep light
						pMap->SetLight(dwRGB);
					
					CMsgAction	msg;
					IF_OK(msg.Create(1, 0, 0, nSecs, actionMapARGB, dwRGB))
						UserManager()->BroadcastMapMsg(pMap->GetID(), &msg, NULL);

					return true;
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_MAP_ATTRIB:
		{
			PARAMBUF	szField;
			PARAMBUF	szOpt;
			int			nData;
			OBJID		idMap = ID_NONE;
			if (sscanf(szParam, "%s %s %d %u", szField, szOpt, &nData, &idMap) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			CGameMap*	pTaskMap = NULL;
			if(idMap != ID_NONE)
			{
				pTaskMap = MapManager()->QueryMap(idMap);
			}
			else
			{
				CNpc* pNpc = NULL;
				if(pUser)
					pTaskMap = pUser->GetMap();
				else if(pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
					pTaskMap = pNpc->GetMap();
			}
			CHECKF(pTaskMap);

			/*if(_stricmp(szField, "synid") == 0)
			{
				if(strcmp(szOpt, "==") == 0)
				{
					if(pTaskMap->GetSynID() == nData)
						return true;
				}
				else if(strcmp(szOpt, "=") == 0)
				{
					pTaskMap->SetSynID(nData, true);		// with all map npc
					return true;
				}
			}*/
			//else 
			if(_stricmp(szField, "status") == 0)
			{
				if(strcmp(szOpt, "test") == 0)
				{
					if((pTaskMap->GetStatus() & nData) != 0)
						return true;
				}
				else if(strcmp(szOpt, "set") == 0)
				{
					pTaskMap->SetStatus(nData, true);
					return true;
				}
				else if(strcmp(szOpt, "reset") == 0)
				{
					pTaskMap->SetStatus(nData, false);
					return true;
				}
			}
			else if(_stricmp(szField, "type") == 0)
			{
				if(strcmp(szOpt, "test") == 0)
				{
					if((pTaskMap->GetType() & nData) != 0)
						return true;
				}
			}
			/*else if(_stricmp(szField, "res_lev") == 0)
			{
				if(strcmp(szOpt, "==") == 0)
				{
					if(pTaskMap->GetResLev() == nData)
						return true;
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					if(pTaskMap->GetResLev() < nData)
						return true;
				}
				else if(strcmp(szOpt, "=") == 0)
				{
					pTaskMap->SetResLev(nData, true);
					return true;
				}
			}*/
			else if(_stricmp(szField, "mapdoc") == 0)
			{
				if(strcmp(szOpt, "==") == 0)
				{
					if(pTaskMap->GetDocID() == nData)
						return true;
				}
				else if(strcmp(szOpt, "=") == 0)
				{
					pTaskMap->ChangeMapDoc(nData);
					return true;
				}
			}
			else if(_stricmp(szField, "portal0_x") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pTaskMap->SetPortal0X(nData, UPDATE_TRUE);
					return true;
				}
			}
			else if(_stricmp(szField, "portal0_y") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pTaskMap->SetPortal0Y(nData, UPDATE_TRUE);
					return true;
				}
			}
			else if(_stricmp(szField,"castle") == 0)                  //add huang 2003.12.30
			{
				if(_stricmp(szOpt, "==") == 0)
				{
					if(pTaskMap->GetID() == nData)
						return true;
				}
			}
		}
		break;
	case	ACTION_MAP_REGION_MONSTER:
		{
			PARAMBUF	szOpt;
			OBJID		idMap, idType;
			int			nRegionX, nRegionY, nRegionCX, nRegionCY, nData;
			if(sscanf(szParam, "%u %d %d %d %d %u %s %d", 
					&idMap, &nRegionX, &nRegionY, &nRegionCX, &nRegionCY, &idType, szOpt, &nData) < 8)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(idMap == ID_NONE)
			{
				if(pUser)
				{
					idMap = pUser->GetMapID();
				}
				else
				{
					CNpc* pNpc = NULL;
					if(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
						idMap = pNpc->GetMapID();
				}
			}
			if(idMap == ID_NONE)
			{
				LOGERROR("ACTION %u: û���ҵ���ͼ", pAction->GetID());
				break;
			}

			int nCount = 0;
			CRoleSet::Iterator pRole = RoleManager()->QuerySet()->NewEnum();
			while(pRole.Next())
			{
				CAiNpc* pMonster;
				if(pRole && pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster))
					&& pMonster->GetMap()->GetID() == idMap
					&& pRole->GetPosX() >= nRegionX && pRole->GetPosX() < nRegionX + nRegionCX
					&& pRole->GetPosY() >= nRegionY && pRole->GetPosY() < nRegionY + nRegionCY
					&& (idType == ID_NONE || pMonster->GetType() == idType) )
				{
					nCount++;
				}
			}

			if(strcmp(szOpt, "==") == 0)
			{
				if(nCount == nData)
					return true;
			}
			else if(strcmp(szOpt, "<") == 0)
			{
				if(nCount < nData)
					return true;
			}
		}
		break;
	case	ACTION_MAP_CREATEMAP:
		{
			CHECKF(pUser && pRole);
			CNpc* pNpc;
			IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				return false;

			//CHECKF(pNpc->IsLinkNpc());

			PARAMBUF	szName;
			OBJID		idOwner, idRebornMap;
			int			nOwnerType, nMapDoc, nType, nPortalX, nPortalY, nRebornPortal, nResLev;
			if(sscanf(szParam, "%s %d %u %d %d %d %d %u %d %d", 
					szName, &nOwnerType, &idOwner, &nMapDoc, &nType, &nPortalX, &nPortalY, &idRebornMap, &nRebornPortal, &nResLev) < 10)
			{
				LOGERROR("ACTION %u: Wrong number of parameters", pAction->GetID());
				break;
			}

			NewMapInfo	info;
			memset(&info, 0, sizeof(NewMapInfo));
			SafeCopy(info.szName, szName, _MAX_NAMESIZE);
			info.nMapDoc		= nMapDoc; 
			info.nType			= nType;
			info.nOwnerType		= nOwnerType;
			info.idOwner		= idOwner;
			info.nMapGroup		= MapGroup(PID)->GetMapGroup();
			info.idLikeMap		= pUser->GetMapID();
			info.nLinkX			= pUser->GetPosX();
			info.nLinkY			= pUser->GetPosY();
			info.nPortalX		= nPortalX;
			info.nPortalY		= nPortalY;
			info.idRebornMap	= idRebornMap;
			info.nRebornPortal	= nRebornPortal;
			info.nResLev		= nResLev;

			OBJID idMap = MapManager()->CreateDynaMap(&info);
			if(idMap == ID_NONE)
				return false;

			//pNpc->QueryLinkMap()->SetLinkMap(idMap);

			return true;
		}
		break;
	default:
		LOGERROR("Unsupported ACTION [%u] type [%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionItemOnly(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction && pUser && pItem);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_ITEM_REQUESTLAYNPC:
		{
			OBJID	idNextTask;
			int		nType, nSort, nLookFace, nRegion=0;
			if(sscanf(szParam, "%u %d %d %d %d %d", &idNextTask, &nType, &nSort, &nLookFace, &nRegion) < 4)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			CHECKF(idNextTask != ID_NONE);
			pUser->SetTaskItemActionID(idNextTask);

			CMsgNpc		msg;
			IF_OK(msg.Create(EVENT_LAYNPC, nRegion, nType, nLookFace))
				pUser->SendMsg(&msg);
			return true;
		}
		break;
	case	ACTION_ITEM_COUNTNPC:
		{
			PARAMBUF	szField;
			PARAMBUF	szData;
			PARAMBUF	szOpt;
			int			nNum;
			IF_NOT_(sscanf(szParam, "%s %s %s %d", szField, szData, szOpt, &nNum) == 4)
				return false;

			int nCount = 0;
			if(_stricmp(szField, "all") == 0)
			{
				nCount = RoleManager()->CountAllNpc(pUser->GetMapID());
			}
			else if(_stricmp(szField, "furniture") == 0)
			{
				nCount = RoleManager()->CountFurnitureNpc(pUser->GetMapID());
			}
			else if(_stricmp(szField, "name") == 0)
			{
				nCount = RoleManager()->CountNpcByName(pUser->GetMapID(), szData);
			}
			else if(_stricmp(szField, "type") == 0)
			{
				int nType = atol(szData);
				nCount = RoleManager()->CountNpcByType(pUser->GetMapID(), nType);
			}
			else
				return false;

			if(_stricmp(szOpt, "<") == 0 && nCount < nNum)
				return true;
			else if(_stricmp(szOpt, "==") == 0 && nCount == nNum)
				return true;
			else
				return false;

			return false;
		}
		break;
	case	ACTION_ITEM_LAYNPC:
		{
			CHECKF(pszAccept && strlen(pszAccept) > 0);

			NPCINFO_ST	info;
			memset(&info, 0, sizeof(NPCINFO_ST));

			int nPose=0, nFrame=0, nDir = 0;
			IF_NOT_(sscanf(pszAccept, "%d %d %d %d %d", &info.nPosX, &info.nPosY, &nDir, &nFrame, &nPose) >= 3)		// MsgNpcInfoת���ɴ����ṩ������ϵͳ
				return false;

			// check overlap npc
			void* pTemp;
			if(pUser->GetMap()->QueryObjInPos(info.nPosX, info.nPosY, OBJ_NPC, IPP_OF(pTemp)))
				return false;

			NAMESTR	szName;
			const char* pName = szName;
			int		nRegionType = 0;
			ASSERT(_MAX_NPCTASK == 8);
			ASSERT(MAX_NPCDATA == 4);
			IF_NOT_(sscanf(szParam, "%s %d %d %d %d ""%d %d %d %d ""%d %d %d %d %d %d %d %d ""%d %d %d %d %s", 
							szName, &info.nType, &info.nSort, &info.nLookFace, &info.nOwnerType, 
							&info.nLife, &nRegionType, &info.idBase, &info.idLink, 
							&info.setTask[0], &info.setTask[1], &info.setTask[2], &info.setTask[3], 
							&info.setTask[4], &info.setTask[5], &info.setTask[6], &info.setTask[7], 
							&info.setData[0], &info.setData[1], &info.setData[2], &info.setData[3], info.szData) >= 5)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			if(info.nType == _STATUARY_NPC)
			{
				pName				= pUser->GetName();
				info.nLookFace		= ::MaskDir(nDir);				// dir
				info.setTask[0]		= pUser->GetMountTypeID();
				info.setTask[1]		= pUser->GetArmorTypeID();
				info.setTask[2]		= pUser->GetWeaponRTypeID();
				info.setTask[3]		= pUser->GetWeaponLTypeID();
				info.setTask[4]		= nFrame;
				info.setTask[5]		= nPose;
				info.setTask[6]		= pUser->GetLookFace();
				info.setTask[7]		= (pUser->GetSynRankShow()<<16) + pUser->GetHair();
			}
			else
			{
				info.nLookFace	= ::MakeLookFace(::MaskLook(info.nLookFace), ::MaskDir(nDir));
			}

			// check syn trans npc
			if(pUser->GetMap()->IsTeleportDisable() && info.nType == _SYNTRANS_NPC)
			{
				pUser->SendSysMsg(STR_DISABLE_LAY_SYNTRANS);
				return false;
			}

			if(nRegionType && !pUser->GetMap()->IsInRegionType(nRegionType, info.nPosX, info.nPosY))
				return false;

			info.idMap	= pUser->GetMapID();
			switch(info.nOwnerType)
			{
			case	OWNER_NONE:
				{
					info.idOwner	= ID_NONE;
				}
				break;
			case	OWNER_USER:
				{
					info.idOwner	= pUser->GetID();
				}
				break;
			case	OWNER_SYN:
				{
					if(pUser->GetSynID() == ID_NONE)
						return false;
					CSyndicate* pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
					CHECKF(pSyn);
					info.idOwner	= pSyn->GetMasterSynID();
				}
				break;
			case	OWNER_NPC:
				{
					ASSERT(!"OWNER_NPC");
				}
				break;
			}

			CNpc* pNpc = CNpc::CreateNew();
			IF_OK(pNpc)
			{
				IF_OK(pNpc->Create(m_idProcess, &info, pItem->GetInt(ITEMDATA_SORT), pName))
				{
					RoleManager()->QuerySet()->AddObj(pNpc->QueryRole());
					//pNpc->EnterMap();

					pUser->SetTaskNpcID(pNpc->GetID());		// fill idLink when create new map
					m_pRole		= pNpc->QueryRole();
					return true;
				}
				else
					pNpc->ReleaseByOwner();
			}

			return false;
		}
		break;
	case	ACTION_ITEM_DELTHIS:
		{
			pUser->SetTaskItemID(ID_NONE);
			pUser->EraseItem(pItem->GetID(), SYNCHRO_TRUE);
			pUser->SendSysMsg(STR_USE_ITEM);

			m_pItem	= NULL;			// ���������Ʒ

			return true;
		}
		break;
	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionItem(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction && pUser);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_ITEM_EQUIPCOLOR:
		{
			int nData = 0, nEquipType = 0;

			IF_OK_ (2 == sscanf(szParam, "%d %d", &nEquipType, &nData))
			{
				CItem* pItem = pUser->GetEquipItemByPos(nEquipType);
				if (!pItem)
					return false;

				if (pItem->ChangeColor(nData))
				{
					CMsgItemInfoEx msg;
					IF_OK(msg.Create(pItem, pUser->GetID(), 0, ITEMINFOEX_EQUIPMENT))
						pUser->BroadcastRoomMsg(&msg, true);
				}
			}
		}
		break;

	case	ACTION_ITEM_EQUIPEXIST:
		{
			CItem* pEquip = pUser->GetEquipItemByPos(pAction->GetInt(ACTIONDATA_DATA));
			if (pEquip)
				return true;
		}
		break;

	case	ACTION_ITEM_EQUIPTEST:
		{
			char szCmd[256] = "";
			char szOpt[256] = "";
			int nData = 0, nEquipType = 0;
	
			IF_OK_ (4 == sscanf(szParam, "%d %s %s %d", &nEquipType, szCmd, szOpt, &nData))
			{
				CItem* pItem = pUser->GetEquipItemByPos(nEquipType);
				if (pItem)
				{
					int nTestData = 0;
					if (0 == _stricmp("level", szCmd))
					{	
						nTestData = pItem->GetLevel();
					}
					else if (0 == _stricmp("quality", szCmd))
					{
						nTestData = pItem->GetQuality();
					}
					/*else if (0 == _stricmp("durability", szCmd))
					{
						if (-1 == nData)
							nData = pItem->GetInt(ITEMDATA_AMOUNTLIMIT)/100;

						nTestData = pItem->GetInt(ITEMDATA_AMOUNT)/100;
					}*/
					/*else if (0 == _stricmp("max_dur", szCmd))
					{
						if (-1 == nData)
							nData = pItem->GetInt(ITEMDATA_AMOUNTLIMIT_ORIGINAL)/100;

						nTestData = (pItem->GetInt(ITEMDATA_AMOUNTLIMIT)*100/(100+pItem->GetGemDurEffect()))/100;
					}*/
					else
					{
						LOGERROR("ACTION %u: ����Ĳ���", pAction->GetID());
						return false;
					}

					if (0 == _stricmp(szOpt, "=="))
					{
						return (nTestData == nData);
					}
					else if (0 == _stricmp(szOpt, "<="))
					{
						return (nTestData <= nData);
					}
					else if (0 == _stricmp(szOpt, ">="))
					{
						return (nTestData >= nData);
					}
					else
					{
						LOGERROR("ACTION %u: ����Ĳ���", pAction->GetID());
					}
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_ITEM_UPEQUIPMENT://
		{
			char szCmd[256] = "";
			int nPos = 0;
			
			IF_OK_ (2 == sscanf(szParam, "%s %d", szCmd, &nPos))
			{
				if (0 == _stricmp("up_lev", szCmd))
				{
					if (pUser->UpEquipmentLevel(nPos))
						return true;
				}
				else if (0 == _stricmp("up_quality", szCmd))
				{
					if (pUser->UpEquipmentQuality(nPos))
						return true;
				}
				else if (0 == _stricmp("recover_dur", szCmd))
				{
					if (pUser->RecoverEquipmentDur(nPos))
						return true;
				}
				else
					LOGERROR("ACTION %u: ����Ĳ���", pAction->GetID());
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_ITEM_MULTIDEL:
		{
			OBJID idType0 = ID_NONE, idType1 = ID_NONE;
			int nNum = 0;
			IF_OK_ (3 == sscanf(szParam, "%u %u %d", &idType0, &idType1, &nNum))
			{
				return pUser->MultiDelItem(idType0, idType1, nNum);
			}
		}
		break;

	case ACTION_ITEM_MULTICHK:
		{
			OBJID idType0 = ID_NONE, idType1 = ID_NONE;
			int nNum = 0;
			IF_OK_ (3 == sscanf(szParam, "%u %u %d", &idType0, &idType1, &nNum))
			{
				return pUser->MultiCheckItem(idType0, idType1, nNum);
			}
		}
		break;

	case	ACTION_ITEM_REPAIR:
		{
			CItem* pEquip = pUser->GetEquipItemByPos(pAction->GetInt(ACTIONDATA_DATA));
			if (pEquip)
			{
				//pEquip->SetInt(ITEMDATA_AMOUNT, pEquip->GetInt(ITEMDATA_AMOUNTLIMIT), true);
				return true;
			}
		}
		break;

	case	ACTION_ITEM_HOLE:
		{
			char szCmd[256] = "";
			int nData = 0;
			if (2 == sscanf(szParam, "%s %u", szCmd, &nData))
			{
				if (0 == _stricmp(szCmd, "ChkHole"))
				{
					CItem* pItem = pUser->GetWeaponR();
					if (pItem)
					{
						//if (1 == nData && GEM_NONE != pItem->GetInt(ITEMDATA_GEM1))
						//	return true;
						//else if (2 == nData && GEM_NONE != pItem->GetInt(ITEMDATA_GEM2))
							return true;
					}
				}
				else if (0 == _stricmp(szCmd, "MakeHole"))
				{
					CItem* pItem = pUser->GetWeaponR();
					if (pItem)
					{
						/*if (1 == nData && GEM_NONE == pItem->GetInt(ITEMDATA_GEM1))
						{
							pItem->SetInt(ITEMDATA_GEM1, GEM_HOLE, true);

							// inform client
							CMsgItemInfo msg;
							IF_OK (msg.Create(pItem, ITEMINFO_UPDATE))
								pUser->SendMsg(&msg);

							return true;
						}

						if (2 == nData 
							&& GEM_NONE != pItem->GetInt(ITEMDATA_GEM1)
							&& GEM_NONE == pItem->GetInt(ITEMDATA_GEM2))
						{
							pItem->SetInt(ITEMDATA_GEM2, GEM_HOLE, true);

							// inform client
							CMsgItemInfo msg;
							IF_OK (msg.Create(pItem, ITEMINFO_UPDATE))
								pUser->SendMsg(&msg);

							return true;
						}*/
						return true;
					}
				}
			}
		}
		break;	

	case	ACTION_ITEM_ADD:
		{
			CItem* pItem = pUser->AwardItem(pAction->GetInt(ACTIONDATA_DATA), SYNCHRO_FALSE, false, CUser::NO_COMBINE);
			if(pItem)
			{
				int	nAmount, nAmountLimit, nIdent, nGem1, nGem2, nMagic1, nMagic2, nMagic3, nData, nWarGhostExp, nGemType, nAvailableTime;
				nAmount = nAmountLimit = nIdent = nGem1 = nGem2 = nMagic1 = nMagic2 = nMagic3 = nData = nWarGhostExp = nGemType = nAvailableTime = 0;
				if(sscanf(szParam, "%u %u %u %u %u %u %u %u %d %u %u %u", 
					&nAmount, &nAmountLimit, &nIdent, &nGem1, &nGem2, &nMagic1, &nMagic2, &nMagic3, &nData, &nWarGhostExp, &nGemType, &nAvailableTime) > 0)
				{
					/*if(nAmount)
						pItem->SetInt(ITEMDATA_AMOUNT, nAmount);
					if(nAmountLimit)
						pItem->SetInt(ITEMDATA_AMOUNTLIMIT, nAmountLimit);
					if(nGem1)
						pItem->SetInt(ITEMDATA_GEM1, nGem1);
					if(nGem2)
						pItem->SetInt(ITEMDATA_GEM2, nGem2);
					if(nMagic1)
						pItem->SetInt(ITEMDATA_MAGIC1, nMagic1);
					if(nMagic2)
						pItem->SetInt(ITEMDATA_MAGIC2, nMagic2);
					if(nMagic3)
						pItem->SetInt(ITEMDATA_MAGIC3, nMagic3);
					if(nData)
						pItem->SetInt(ITEMDATA_DATA, nData);
					if(nWarGhostExp)
						pItem->SetInt(ITEMDATA_WARGHOSTEXP, nWarGhostExp);
					if(nGemType)
						pItem->SetInt(ITEMDATA_GEMTYPE, nGemType);
					if(nAvailableTime)
						pItem->SetInt(ITEMDATA_AVAILABLETIME, nAvailableTime);

					pItem->SetStatus(nIdent, UPDATE_TRUE);*/
				}

				// ����������ܶ�
				/*if(pItem->IsMount())
				{
					int nIntimacy	= pItem->GetInt(ITEMDATA_INTIMACY);
					int nAdjust		= nIntimacy*25/100;
					nIntimacy	+= ::RandGet(nAdjust * 2) - nAdjust;
					pItem->SetInt(ITEMDATA_INTIMACY, nIntimacy);
				}*/

				// synchro
				CMsgItemInfo msg;
				if(msg.Create(pItem, ITEMINFO_ADDITEM))
					pUser->SendMsg(&msg);
				return true;
			}
		}
		break;
	case	ACTION_ITEM_DEL:
		{
			CItemPtr pItem = NULL;
			int nNum = 1;
			if(pAction->GetInt(ACTIONDATA_DATA))
			{
				nNum = ::CutTrail(1, atoi(szParam));
				pItem = pUser->GetTaskItemByType(pAction->GetInt(ACTIONDATA_DATA), nNum);
			}
			else if(strlen(szParam) > 0)
				pItem = pUser->GetTaskItem(szParam);
			IUserPackage* pPackage = pUser->QueryPackage();
			if(pPackage	&& pItem && pUser->SpendItem(pItem, nNum, pPackage->GetItemPosition(pItem)))
				return true;
		}
		break;
	case	ACTION_ITEM_CHECK:
		{
			CItemPtr pItem = NULL;
			if(pAction->GetInt(ACTIONDATA_DATA))
			{
				int nNum = atoi(szParam);
				pItem = pUser->GetTaskItemByType(pAction->GetInt(ACTIONDATA_DATA), nNum);
			}
			else if(strlen(szParam) > 0)
				pItem = pUser->GetTaskItem(szParam);
			if(pItem)
				return true;
		}
		break;
	case	ACTION_ITEM_LEAVESPACE:
		{
			int		nSpace, nWeight, nPackType;
			if(sscanf(szParam, "%d %d %d", &nSpace, &nWeight, &nPackType) == 3)
			{
				if(pUser->IsBackPackSpare(nSpace, nWeight, ID_NONE, nPackType))
					return true;
			}
			else
			{
				ASSERT(!"ACTION_ITEM_LEAVESPACE no param");
				//if(pUser->IsBackPackSpare(pAction->GetInt(ACTIONDATA_DATA), 0))
				//	return true;
			}
		}
		break;
	case ACTION_ENCASH_CHIP:
		{
			CHECKF(pItem);
			DEBUG_TRY
			//int nMoney = pItem->GetInt(ITEMDATA_DATA);
			//pUser->GainMoney(nMoney, SYNCHRO_TRUE);
			IF_NOT(pUser->SpendItem(pItem))
		    	return false;
			DEBUG_CATCH("Encash Chip Error!")
		}
		break;
	case	ACTION_ITEM_FIND:
		{
			CItemPtr pItem = NULL;
			if(pAction->GetInt(ACTIONDATA_DATA))
				pItem = pUser->GetTaskItemByType(pAction->GetInt(ACTIONDATA_DATA));
			else if(strlen(szParam) > 0)
				pItem = pUser->GetTaskItem(szParam);
			if(pItem && pUser)
			{
				pUser->TaskIterator() = pItem->GetID();
				return true;
			}
		}
		break;
	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionNpcOnly(CActionData* pAction, LPCTSTR szParam, CUser* pUser_NoUse, IRole* pRole, CItem* pItem_NoUse, LPCTSTR pszAccept)
{
	CHECKF(pAction);

	CNpc* pNpc;
	IF_NOT(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
		return false;

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_NPCONLY_CREATENEW_PET:
		{
			OBJID	idGen, idType;
			int		nPosX, nPosY, nData=0;
			PARAMBUF	szName = "";
			if(sscanf(szParam, "%d %d %u %u %d %s", &nPosX, &nPosY, &idGen, &idType, &nData, szName) < 4)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(!::NameStrCheck(szName))
			{
				return false;
			}

			ST_CREATENEWNPC	info;
			memset(&info, 0, sizeof(ST_CREATENEWNPC));
//not in this			info.id				= MapManager()->SpawnNewPetID();
			info.idMap			= pNpc->GetMapID();
			info.idData			= idGen;
			info.idOwner		= pNpc->GetInt(NPCDATA_OWNERID);		// �ܰ�
			info.usPosX			= nPosX;
			info.usPosY			= nPosY;
//			info.usAction		= MSGAINPCINFO_CREATENEW;
			info.usType			= idType;
			//info.ucOwnerType	= pNpc->GetInt(NPCDATA_OWNERTYPE);
			info.nData			= nData;

			if(strlen(szName) > 0 && strcmp(szName, ACTIONSTR_NONE) != 0)
				return NpcManager()->CreateSynPet(&info, szName);
			else
				return NpcManager()->CreateSynPet(&info);
		}
		break;
	case	ACTION_NPCONLY_DELETE_PET:
		{
			OBJID	idType;
			int		nData=0;
			PARAMBUF	szName = "";
			if(sscanf(szParam, "%u %d %s", &idType, &nData, szName) < 1)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			bool	ret = false;
			OBJID idMap = pNpc->GetMapID();
			for(IRoleSet::Iter i = RoleManager()->QuerySet()->Begin(); i != RoleManager()->QuerySet()->End(); )		// ɾ��
			{
				IRole* pRole = RoleManager()->QuerySet()->GetObjByIter(i);
				i++;		//??? ��ǰ�ƶ���������ܻ�ɾ����ǰ��ɫ
				CAiNpc* pPet;
				if(pRole && pRole->QueryObj(OBJ_MONSTER, IPP_OF(pPet))
							&& pPet->GetMap()->GetID() == idMap && pPet->GetType() == idType)		// pPet->IsPet() && 
				{
					if(!( nData && pPet->GetData() != nData || strlen(szName) && strcmp(szName, pPet->GetName()) != 0 ))
					{
						if(!pPet->IsDeleted())
						{
							pPet->DelMonster(DEL_NOW);
							ret = true;
						}
					}
				}
			}
			return ret;
		}
		break;
	case	ACTION_NPCONLY_MAGICEFFECT:
		{
			OBJID	idSource, idTarget;
			int		nType, nLevel, nData;
			if(sscanf(szParam, "%u %d %d %u %d", &idSource, &nType, &nLevel, &idTarget, &nData) < 5)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			// effect
			CMsgMagicEffect	msg;
			IF_OK(msg.Create(idSource, nType, nLevel, idTarget, nData, pNpc->GetDir()))
				pNpc->BroadcastRoomMsg(&msg);

			return true;
		}
		break;
	case	ACTION_NPCONLY_MAGICEFFECT2:
		{
			OBJID	idSource, idTarget=0;
			int		nType, nLevel, x, y, nData=0;
			if(sscanf(szParam, "%u %d %d %d %d %u %d", &idSource, &nType, &nLevel, &x, &y, &idTarget, &nData) < 5)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			
			// effect
			CMsgMagicEffect	msg;
			IF_OK(msg.CreateByPos(idSource, nType, nLevel, x, y, idTarget, nData, pNpc->GetDir()))
				pNpc->BroadcastRoomMsg(&msg);

			return true;
		}
		break;
	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionSyn(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction && pUser);

	int nActionType = pAction->GetInt(ACTIONDATA_TYPE);
	switch(nActionType)
	{
	case ACTION_SYN_APPLLY_ATTACKSYN: //�������ս���NPC���빥�����
		{
			CNpc* pNpc;						
			if (pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)) && pUser->GetMapID() == pNpc->GetMapID()&&pNpc->IsSynWarLetter())
			{
				if(pUser->ApplyAttackSyn(pNpc))
					return true;				
			}
			return false;				
		}
		break;
	case ACTION_SYN_ALLOCATE_SYNFUND: //������������
	{
		if (!pszAccept || strlen(pszAccept) <= 0)
			break;

		int nExpTake = 0;
		try {
			nExpTake = atoi(pszAccept);
		} catch (...) {
			break;
		}
		if (nExpTake > 0)
		{
			CSyndicate* pSyn = pUser->GetSyndicate();				
			if (!pSyn)
				break;

			if (pSyn->GetInt(SYNDATA_FEALTY) != ID_NONE || pUser->GetSynRank() != RANK_LEADER)
				break;

			if (pSyn->AllotBonusForMember(pUser, nExpTake))
				return true;
		}
	}
	break;
	case ACTION_SYN_UPMEMBERLEVEL:	///����,��,�� ���ɳ�Ա�ȼ�
	{
		PARAMBUF	szOpt;
		int 		nData;

		CSyndicate* pSyn = pUser->GetSyndicate();
		
		CHECKF(pSyn);

		if(sscanf(szParam, "%s %d",szOpt,&nData) < 2)
		{
			LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
			break;
		}

		if(_stricmp(szOpt, "=")==0)//���ü���
		{
			if(nData >= SYNMEM_LEVEL_ONE && nData <= SYNMEM_LEVEL_FIVE)
			{
				pUser->QuerySynAttr()->SetSynMemberLevel(nData);
			}
		}
		else if(_stricmp(szOpt, "+=")==0)//�Ӽ���
		{
			int nLevel = pUser->QuerySynAttr()->GetSynMemberLevel();
			nLevel += nData;
			if(nLevel >= SYNMEM_LEVEL_ONE && nLevel <= SYNMEM_LEVEL_FIVE)
			{
				pUser->QuerySynAttr()->SetSynMemberLevel(nLevel);
				return true;
			}		
		}	
		return false;
	}
	break;
	
	case	ACTION_SYN_CREATE:	// ��������
		{
			int		nLevel, nMoney, nMoneyLeave;
			if(sscanf(szParam, "%u %u %u %d", &nLevel, &nMoney, &nMoneyLeave) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(pUser->GetSynID() != ID_NONE)
				return false;

			// check syndicate name
			if(!pszAccept)
				return false;

			if (strlen(pszAccept) < 2 || 
					strlen(pszAccept) >= _MAX_NAMESIZE ||
						!::NameStrCheck((char*)pszAccept))
			{
				pUser->SendSysMsg(STR_INVALID_GUILD_NAME);
				return false;
			}

			OBJID idSyn = pUser->QuerySynAttr()->CreateSyndicate(pszAccept, nLevel, nMoney, nMoneyLeave);
			if(idSyn == ID_NONE)
				return false;
			{
				// synchro npc server
				CMsgSyndicate	msg;
				OBJID idFealty = ID_NONE;
				IF_OK(msg.Create(NPCMSG_CREATE_SYN, idFealty))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(idSyn, &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_CREATE_SUB:	// �����Ӱ���(���ų�ִ���򴴽����ţ����ų�ִ���򴴽��ֶ�)
		{
			/*
			int		nLevel, nProffer, nMoney, nMoneyLeave;
			if(sscanf(szParam, "%u %u %u %u", &nLevel, &nProffer, &nMoney, &nMoneyLeave) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}*/

			// check syndicate name
			if(!pszAccept)
				return false;
			
			if(pUser->GetSynID() == ID_NONE || pUser->GetSynRank() != RANK_LEADER)
				return false;

			CSyndicate* pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
			if (!pSyn)
				return false;

			if (pSyn->IsMasterSyn())
			{
				// �������ţ��ж�����
				const int setRank2Num[]	= { 0, 2, 3, 4 };	// ���ŵȼ������������ϵ
				int nRank = pSyn->GetInt(SYNDATA_RANK);
				if (pSyn->GetSubSynNum() >= setRank2Num[nRank-SYNRANK_ONE])
					return false;
			}
			else
			{
				CSyndicate* pMasterSyn = SynManager()->QuerySyndicate(pSyn->GetInt(SYNDATA_FEALTY));
				if (!pMasterSyn || !pMasterSyn->IsMasterSyn())
					return false;

				// �����ֶӣ��ж�����
				const int setRank2Num[] = { 0, 2, 2, 3 };	// ���ŵȼ���ÿ�������еķֶ�������ϵ
				int nRank = pMasterSyn->GetInt(SYNDATA_RANK);
				if (pSyn->GetSubSynNum() >= setRank2Num[nRank-SYNRANK_ONE])
					return false;
			}
			
			if (strlen(pszAccept) < 2 || strlen(pszAccept) > SUBSYN_NAMESIZE || !::NameStrCheck((char*)pszAccept))
			{
				pUser->SendSysMsg(STR_INVALID_GUILD_NAME);
				return false;
			}

			OBJID idSubSyn = pUser->QuerySynAttr()->CreateSubSyn(pSyn->GetID(), pszAccept);
			if(idSubSyn == ID_NONE)
				return false;

			{
				// synchro npc server
				CMsgSyndicate	msg;
				OBJID idFealty = pSyn->GetID();
				IF_OK(msg.Create(NPCMSG_CREATE_SYN, idFealty))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(idSubSyn, &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_CHANGE_LEADER:
		{
			int		nNeedLevel;
			int		nNobilityRank;
			if(sscanf(szParam, "%u %u", &nNeedLevel, &nNobilityRank) != 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(pUser->GetSynID() == ID_NONE || pUser->GetSynRankShow() != RANK_LEADER)
				return false;
			CSyndicate* pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
			IF_NOT(pSyn)
				return false;

			// check syndicate name
			OBJID idNewLeader = ID_NONE;
			MSGBUF	szSubSynName;
			if(!pszAccept || sscanf(pszAccept, "%u %s", &idNewLeader, szSubSynName) != 2)
			{
				LOGERROR("ACTION %u: �����accept����", pAction->GetID());
				return false;
			}

			// target
			CUser* pTarget = UserManager()->GetUser(idNewLeader);
			if(!pTarget || pTarget->GetSynID() != pSyn->GetID() || pTarget->GetNobilityRank() < nNobilityRank)
				return false;

			if(pTarget->QuerySynAttr()->ChangeLeader(szSubSynName, nNeedLevel))
				return true;
			else
				return false;
		}
		break;
	case	ACTION_SYN_DESTROY:
		{
			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;

			// ���Ȩ��
			if(pUser->GetSynRank() != RANK_LEADER)
			{
				pUser->SendSysMsg(STR_NOT_AUTHORIZED);
				return false;
			}

			OBJID idFealty = ID_NONE;
			CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
			if (pSyn)
				idFealty = pSyn->GetInt(SYNDATA_FEALTY);

			if(!SynManager()->QueryModify()->DestroySyndicate(idSyn, idFealty))
				return false;
			{
				// synchro npc server
				CMsgSyndicate	msg;
				IF_OK(msg.Create(NPCMSG_DESTROY_SYN, (OBJID)ID_NONE))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(idSyn, &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_COMBINE_SUB:
		{
			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;

			if (pUser->GetSynRank() != RANK_LEADER)
			{
				pUser->SendSysMsg(STR_NOT_AUTHORIZED);
				return false;
			}

			if(!SynManager()->QueryModify()->CombineSyndicate(idSyn, pUser->GetMasterSynID()))
				return false;

			{
				// synchro npc server
				CMsgSyndicate	msg;
				IF_OK(msg.Create(NPCMSG_DESTROY_SYN, (OBJID)ID_NONE))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(idSyn, &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_ALLY:
		{
			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn || !pSyn->ReloadData())
				return false;
			// ���Ȩ��
			if(pUser->GetSynRankShow() != RANK_LEADER)
			{
//				sprintf(szMsg, "��û�����Ȩ��!");
//				this->SendSysMsg(szMsg);
				return false;
			}

			// target syn
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam)
				return false;
			CUser* pTarget = NULL;
			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				OBJID idUser = pTeam->GetMemberByIndex(i);
				if(idUser != ID_NONE && idUser != pUser->GetID())
				{
					pTarget = UserManager()->GetUser(idUser);
					break;
				}
			}
			if(!pTarget)
				return false;
			OBJID	idTargetSyn = pTarget->GetSynID();
			if(idTargetSyn == ID_NONE || idTargetSyn == pUser->GetSynID())
				return false;
			if(pTarget->GetSynRankShow() != RANK_LEADER)
				return false;
			CSyndicate* pTargetSyn = SynManager()->QuerySyndicate(idTargetSyn);
			if(!pTargetSyn || !pTargetSyn->ReloadData())
				return false;
			pTargetSyn = pTargetSyn->GetMasterSyn();

			int nIdx = -1;
			for(int i = 0; i < MAX_SYNALLYSIZE; i++)
			{
				OBJID idTarget = pSyn->GetInt((SYNDATA)(SYNDATA_ALLY0+i));
				if(idTarget == ID_NONE || SynManager()->QuerySyndicate(idTarget) == NULL || idTarget == pTargetSyn->GetID())
					nIdx = i;
			}
			if(nIdx == -1)
			{
				pUser->SendSysMsg(STR_ALLY_FULL);
				return false;
			}
			int nIdx2 = -1;
			for(int i = 0; i < MAX_SYNALLYSIZE; i++)
			{
				OBJID idTarget = pTargetSyn->GetInt((SYNDATA)(SYNDATA_ALLY0+i));
				if(idTarget == ID_NONE || SynManager()->QuerySyndicate(idTarget) == NULL || idTarget == pSyn->GetID())
					nIdx2 = i;
			}
			if(nIdx2 == -1)
			{
				pUser->SendSysMsg(STR_HIS_ALLY_FULL);
				return false;
			}
			pSyn->QueryModify()->SetData((SYNDATA)(SYNDATA_ALLY0+nIdx), pTargetSyn->GetID(), true);		// true: ����save
			pTargetSyn->QueryModify()->SetData((SYNDATA)(SYNDATA_ALLY0+nIdx2), pSyn->GetID(), true);		// true: ����save
			{
				// synchro npc server
				CMsgSyndicate	msg;
				IF_OK(msg.Create(SET_ALLY, pTargetSyn->GetID()))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(pSyn->GetID(), &msg);
			}

			return true;
		}
		break;
	case	ACTION_SYN_CLEAR_ALLY:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->QuerySynAttr()->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			if(pUser->GetSynRankShow() != RANK_LEADER)
			{
				return false;
			}

			// ������
			CSyndicate* pTargetSyn = SynManager()->QuerySynByName(pszAccept);
			if(!pTargetSyn)
				return false;
			pTargetSyn = pTargetSyn->GetMasterSyn();

			for(int i = 0; i < MAX_SYNALLYSIZE; i++)
			{
				OBJID idTarget = pSyn->GetInt((SYNDATA)(SYNDATA_ALLY0+i));
				if(idTarget == pTargetSyn->GetID())
					pSyn->QueryModify()->SetData((SYNDATA)(SYNDATA_ALLY0+i), ID_NONE, true);		// true: ����save
			}
			for(int i = 0; i < MAX_SYNALLYSIZE; i++)
			{
				OBJID idTarget = pTargetSyn->GetInt((SYNDATA)(SYNDATA_ALLY0+i));
				if(idTarget == pSyn->GetID())
					pTargetSyn->QueryModify()->SetData((SYNDATA)(SYNDATA_ALLY0+i), ID_NONE, true);		// true: ����save
			}
			{
				// synchro npc server
				CMsgSyndicate	msg;
				IF_OK(msg.Create(CLEAR_ALLY, pTargetSyn->GetID()))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(pSyn->GetID(), &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_ANTAGONIZE:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->QuerySynAttr()->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			if(pUser->GetSynRankShow() != RANK_LEADER)
			{
//				sprintf(szMsg, "��û�����Ȩ��!");
//				this->SendSysMsg(szMsg);
				return false;
			}

			// ������
			CSyndicate* pTargetSyn = SynManager()->QuerySynByName(pszAccept);
			if(!pTargetSyn || pTargetSyn->GetID() == idSyn)
				return false;
			pTargetSyn = pTargetSyn->GetMasterSyn();

			for(int i = 0; i < MAX_SYNENEMYSIZE; i++)
			{
				OBJID idTarget = pSyn->GetInt((SYNDATA)(SYNDATA_ENEMY0+i));
				if(idTarget != ID_NONE && idTarget == pTargetSyn->GetID())
					return false;
			}
			for(int i = 0; i < MAX_SYNENEMYSIZE; i++)
			{
				OBJID idTarget = pSyn->GetInt((SYNDATA)(SYNDATA_ENEMY0+i));
				if(idTarget == ID_NONE || SynManager()->QuerySyndicate(idTarget) == NULL)
				{
					pSyn->QueryModify()->SetData((SYNDATA)(SYNDATA_ENEMY0+i), pTargetSyn->GetID(), true);		// true: ����save
					break;
				}
			}
			{
				// synchro npc server
				CMsgSyndicate	msg;
				IF_OK(msg.Create(SET_ANTAGONIZE, pTargetSyn->GetID()))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(pSyn->GetID(), &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_CLEAR_ANTAGONIZE:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->QuerySynAttr()->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			if(pUser->GetSynRankShow() != RANK_LEADER)
			{
//				sprintf(szMsg, "��û�����Ȩ��!");
//				this->SendSysMsg(szMsg);
				return false;
			}

			// ������
			CSyndicate* pTargetSyn = SynManager()->QuerySynByName(pszAccept);
			if(!pTargetSyn)
				return false;
			pTargetSyn = pTargetSyn->GetMasterSyn();

			for(int i = 0; i < MAX_SYNENEMYSIZE; i++)
			{
				OBJID idTarget = pSyn->GetInt((SYNDATA)(SYNDATA_ENEMY0+i));
				if(idTarget == pTargetSyn->GetID())
				{
					pSyn->QueryModify()->SetData((SYNDATA)(SYNDATA_ENEMY0+i), ID_NONE, true);		// true: ����save
					break;
				}
			}
			{
				// synchro npc server
				CMsgSyndicate	msg;
				IF_OK(msg.Create(CLEAR_ANTAGONIZE, pTargetSyn->GetID()))
					MapGroup(PID)->QueryIntraMsg()->SendNpcMsg(pSyn->GetID(), &msg);
			}
			return true;
		}
		break;
	case	ACTION_SYN_DONATE:
		{
			if(!pszAccept)
				return false;

			char* pTemp;
			int nMoney = strtol(pszAccept, &pTemp, 10);
			if(nMoney <= 0 || pUser->GetMoney() < nMoney)
				return false;

			pUser->QuerySynAttr()->DonateMoney(nMoney);
			return true;
		}
		break;
	case	ACTION_SYN_DEMISE:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;

			// ֻ������ų����ã����ų��ͷֶӳ���������
			if (pSyn->GetInt(SYNDATA_FEALTY)!=ID_NONE)
				return false;

			// ���Ȩ��
			if(pUser->GetSynRank() != RANK_LEADER)
				return false;

			// target syn
			CUser* pTarget = UserManager()->GetUser(pszAccept);
			if(!pTarget)
			{
				pUser->SendSysMsg(STR_NOT_HERE);
				return false;
			}
			if(pTarget->GetID() == pUser->GetID() || pTarget->GetSynID() != pUser->GetSynID())
				return false;

			int nNeedLevel = atol(szParam);
			if(nNeedLevel && pTarget->GetLev() < nNeedLevel)
			{
				pUser->SendSysMsg(STR_LEVEL_NOT_ENOUGH);
				return false;
			}
			OBJID	idTargetSyn = pTarget->GetSynID();
			if(idTargetSyn == ID_NONE || idTargetSyn != idSyn)
				return false;

			pSyn->QueryModify()->Demise(pUser->GetID(), pUser->QuerySynAttr()->GetSynMemberLevel(),pTarget->GetID(), pTarget->GetName(),pTarget->QuerySynAttr()->GetSynMemberLevel(), pSyn->GetID());
			return true;
		}
		break;
	case	ACTION_SYN_SET_ASSISTANT:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			int nRank = pUser->GetSynRank();
			if(nRank != RANK_LEADER)
				return false;

			// check amount, temporary code.
			if(pUser->QuerySynAttr()->GetAssistantCount() >= MAX_ASSISTANTSIZE)
			{
				pUser->SendSysMsg(STR_SYN_PLACE_FULL);
				return false;
			}

			// target syn
			CUser* pTarget = UserManager()->GetUser(pszAccept);
			if(!pTarget)
			{
				pUser->SendSysMsg(STR_NOT_HERE);
				return false;
			}
			if(pUser->GetID() == pTarget->GetID())
				return false;
			OBJID	idTargetSyn = pTarget->GetSynID();
			if(idTargetSyn == ID_NONE || idTargetSyn == idSyn)
				return false;

			pTarget->QuerySynAttr()->SetRank(RANK_SUBLEADER);
			return true;
		}
		break;
	case	ACTION_SYN_CLEAR_RANK:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			int nRank = pUser->GetSynRank();
			if(nRank != RANK_LEADER)
				return false;

			// target syn
			CUser* pTarget = UserManager()->GetUser(pszAccept);
			if(!pTarget)
			{
				pUser->SendSysMsg(STR_NOT_HERE);
				return false;
			}
			if(pUser->GetID() == pTarget->GetID())
				return false;
			OBJID	idTargetSyn = pTarget->GetSynID();
			if(idTargetSyn == ID_NONE || idTargetSyn != idSyn)
				return false;

			pTarget->QuerySynAttr()->SetRank(RANK_NEWBIE);
			return true;
		}
		break;
	case	ACTION_SYN_PRESENT_MONEY:
		{
			if(!pszAccept)
				return false;

			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			int nRank = pUser->GetSynRank();
			if(nRank != RANK_LEADER)
			{
//				sprintf(szMsg, "��û�����Ȩ��!");
//				this->SendSysMsg(szMsg);
				return false;
			}

			// check money
			int nMoney = atol(pszAccept);
			if(nMoney <= 0 || pSyn->GetInt(SYNDATA_MONEY) < nMoney)
				return false;
			if(nMoney < PRESENTMONEY_LIMIT)
			{
//				pUser->SendSysMsg("��������%d��!", PRESENTMONEY_LIMIT);
				return false;
			}

			// target syn
			OBJID	idTargetSyn = pUser->TaskIterator();
			if(idTargetSyn == ID_NONE || idTargetSyn == pUser->GetSynID())
				return false;

			pSyn->QueryModify()->PresentMoney(idTargetSyn, nMoney);
			return true;
		}
		break;
	case	ACTION_SYN_CHANGESYN:
		{
			if(pUser->GetSynID() == ID_NONE || pUser->GetSynRank() != RANK_LEADER)
				return false;
			CSyndicate* pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
			IF_NOT(pSyn)
				return false;

			// check syndicate name
			OBJID idMember = ID_NONE;
			MSGBUF	szSynName;
			if(!pszAccept || sscanf(pszAccept, "%u %s", &idMember, szSynName) != 2)
			{
				LOGERROR("ACTION %u: �����accept����", pAction->GetID());
				return false;
			}

			// target
			CUser* pTarget = UserManager()->GetUser(idMember);
			if(!pTarget || pTarget->GetSynID() != pSyn->GetID())
				return false;

			CSyndicate* pTargetSyn = SynManager()->QuerySynByName(szSynName);
			if(!pTargetSyn)
				return false;

			if(pTarget->QuerySynAttr()->ChangeSyn(pSyn, pTargetSyn))
				return true;
			else
				return false;
		}
		break;
	case	ACTION_SYN_FIND_NEXT_SYN:
		{
			return SynManager()->FindNextSyn(pUser->TaskIterator());
		}
		break;
	case	ACTION_SYN_FIND_BY_NAME:
		{
			if(!pszAccept || strlen(pszAccept) >= _MAX_NAMESIZE)
				return false;

			CSynPtr pSyn = SynManager()->QuerySynByName(pszAccept);
			if(pSyn)
				pUser->TaskIterator()	= pSyn->GetID();
			else
				pUser->TaskIterator()	= ID_NONE;
			return pUser->TaskIterator() != ID_NONE;
		}
		break;
	case	ACTION_SYN_FIND_NEXT_SYNMEMBER:
		{
			OBJID idSyn = pUser->GetSynID();
			if(idSyn != ID_NONE)
				return UserManager()->FindNextSynMember(idSyn, pUser->TaskIterator());
		}
		break;
/*
	case    ACTION_SYN_LEVEL:           //����,��,�� ���ɵȼ�
		{			
			int nData;			
			PARAMBUF szOpt;
			
			CSyndicate* pSyn = pUser->GetSyndicate();
			if (!pSyn || pSyn->GetInt(SYNDATA_FEALTY)!=ID_NONE)			// ������������
				return false;
			if(pSyn->GetInt(SYNDATA_LEADERID) != pUser->GetID())		// �����ǰ���
				return false;

			if(sscanf(szParam, "%s %d",szOpt,&nData) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			
			if(_stricmp(szOpt, "=")==0)			//���ü���
			{
				IF_NOT (nData >= SYNRANK_ONE && nData <= SYNRANK_FOUR)
					return false;

				pSyn->QueryModify()->SetData(SYNDATA_RANK,nData,true);
			}
			else if(_stricmp(szOpt, "+=")==0)	//�޸ļ���
			{
				int nRank = pSyn->GetInt(SYNDATA_RANK);
				nRank += nData;

				IF_NOT (nRank >=SYNRANK_ONE && nRank <= SYNRANK_FOUR)
					return false;

				pSyn->QueryModify()->AddData(SYNDATA_RANK, nData, true);		// mast true				
			}
			return true;
		}
		break;
*/

	case    ACTION_SYN_SAINT:
		{
			PARAMBUF	szOpt;
			int	        nData;
			if(sscanf(szParam, "%s %d", szOpt, &nData) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}	
			CSyndicate* pSyn = pUser->GetSyndicate();
			CHECKF(pSyn);
				return false;
			if ( _stricmp(szOpt, "=") == 0 )
			{
				pSyn->QueryModify()->SetData(SYNDATA_SAINT,nData,true);
				return true;
			}
			else if (_stricmp(szOpt, ">="))
			{
				return (pSyn->GetInt(SYNDATA_SAINT)>= nData);
			}
		}
		break;
	case	ACTION_SYN_KICKOUT_MEMBER:  //������Ա������������ʱ��ϵͳ��Ҫ�õ�������ͬ��
		{
			if(!pszAccept || strlen(pszAccept) >= _MAX_NAMESIZE)
				return false;

			OBJID idSyn = pUser->GetSynID();
			int	  nRank = pUser->GetSynRank();
			if(idSyn == ID_NONE || nRank != RANK_LEADER|| nRank != RANK_SUBLEADER)
				return false;
			if(strcmp(pszAccept, pUser->GetName()) == 0)
				return false;

			// no money ?
			CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
			if(pSyn && pSyn->GetInt(SYNDATA_MONEY) < SYN_MONEY_BASELINE)
			{
				pUser->SendSysMsg(STR_TOO_LOWER_SYN_MONEY);
				return false;
			}

			CUser* pTarget = UserManager()->GetUser(pszAccept);
			if(!pTarget) return false;
			//---jinggy---2004-12-20---begin
			if(nRank==RANK_SUBLEADER)//������������������Ϳ����������͵�����
			{
				if(pSyn->ApplyKickoutMember(pUser,pTarget)) return true;
				return false;
			}
			//---jinggy---2004-12-20---end

			MSGBUF	szMsg;
			sprintf(szMsg, STR_KICKOUT_MEMBER_s, pszAccept, pSyn->GetStr(SYNDATA_NAME));
			IF_OK(pSyn)
				pSyn->BroadcastSubSynMsg(pUser->GetSocketID(), pUser->GetID(), szMsg);

		
			if(pTarget)
			{
				pTarget->SendSysMsg(STR_KICKOUT_ME_s, pUser->GetName());
				if(pTarget->GetSynID() == idSyn)
					return pTarget->QuerySynAttr()->LeaveSyn();
			}
			else
			{
				return pUser->QuerySynAttr()->KickoutMember(pszAccept);
			}
		}
		break;
	case	ACTION_SYN_CHANGE_SUBNAME:
		{
			if(!pszAccept)
				return false;
			if (strlen(pszAccept) < 2 || strlen(pszAccept) > SUBSYN_NAMESIZE || !::NameStrCheck((char*)pszAccept))
			{
				pUser->SendSysMsg(STR_INVALID_GUILD_NAME);
				return false;
			}

			OBJID idSyn = pUser->GetSynID();
			int	  nRank = pUser->GetSynRankShow();
			if(idSyn == ID_NONE || !(nRank == RANK_SUBLEADER /* ||nRank == RANK_PRESUBLEADER*/) )
				return false;
			CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn || strlen(pSyn->GetStr(SYNDATA_NAME)) <= 6)
				return false;

			pSyn->SetNewSubName(pszAccept);
			return true;
		}
		break;
	case	ACTION_SYN_RENAME:
		{
			if(!pszAccept)
				return false;
			if (strlen(pszAccept) < 2 || strlen(pszAccept) > SUBSYN_NAMESIZE || !::NameStrCheck((char*)pszAccept))
			{
				pUser->SendSysMsg(STR_INVALID_GUILD_NAME);
				return false;
			}
			OBJID idSyn = pUser->GetSynID();
			if (idSyn == ID_NONE)
				return false;

			if (pUser->GetSynRank() != RANK_LEADER)		// ֻ�б���������������
			{
				pUser->SendSysMsg(STR_NOT_AUTHORIZED);
				return false;
			}

			CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
			if (!pSyn || pSyn->GetInt(SYNDATA_FEALTY)==ID_NONE)		// �����ɲ��������
				return false;

			pSyn->SetNewSubName(pszAccept);
			return true;
		}
		break;
	case	ACTION_SYN_CREATENEW_PET:
		{
			OBJID	idGen, idType, nData=0;
			if(sscanf(szParam, "%u %u %d", &idGen, &idType, &nData) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(pUser->GetSynID() == ID_NONE || pUser->GetSynRank() != RANK_LEADER)		// ����Ҳ�ɷ�
				return false;
			if(!::NameStrCheck((char*)pszAccept))
			{
				pUser->SendSysMsg(STR_INVALID_NAME);
				return false;
			}

			CSyndicate* pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
			CHECKF(pSyn);

			ST_CREATENEWNPC	info;
			memset(&info, 0, sizeof(ST_CREATENEWNPC));
//not in this			info.id				= MapManager()->SpawnNewPetID();
			info.idMap			= pUser->GetMapID();
			info.idData			= idGen;
			info.idOwner		= pSyn->GetMasterSynID();		// �ܰ�
			info.usPosX			= pUser->GetPosX();
			info.usPosY			= pUser->GetPosY();
//			info.usAction		= MSGAINPCINFO_CREATENEW;
			info.usType			= idType;
			info.ucOwnerType	= OWNER_SYN;
			info.nData			= nData;

			if(pszAccept && strlen(pszAccept) > 0)
				return NpcManager()->CreateSynPet(&info, pszAccept);
			else
				return NpcManager()->CreateSynPet(&info);
		}
		break;
	case	ACTION_SYN_ATTR:
		{
			PARAMBUF	szField;
			PARAMBUF	szOpt;
			int 		nData;
			OBJID		idSyn=ID_NONE;
			if(sscanf(szParam, "%s %s %d %u", szField, szOpt, &nData, &idSyn) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			
			if(idSyn == ID_NONE)
				idSyn = pUser->GetSynID();
			CHECKF(idSyn);
			
			CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
			CHECKF(pSyn);
			
			if (_stricmp(szField, "money") == 0)//����
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pSyn->QueryModify()->AddData(SYNDATA_MONEY, nData, true);		// mast true
					return true;
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					if(pSyn->GetInt(SYNDATA_MONEY) < nData)
						return true;
				}
			}
			else if (_stricmp(szField, "repute") ==0)//����
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pSyn->QueryModify()->AddData(SYNDATA_REPUTE, nData, true);		// mast true
					return true;
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					if(pSyn->GetInt(SYNDATA_REPUTE) < nData)
						return true;
				}
				
			}
			else if (_stricmp(szField, "membernum") ==0)//��Ա����
			{
				if(strcmp(szOpt, "<") == 0)
				{
					if(pSyn->GetSynAmount()< nData)
						return true;					
				}		
				
			}
			else if (_stricmp(szField, "fealty") == 0)
			{
				if(strcmp(szOpt, "==") == 0)
				{
					if(pSyn->GetInt(SYNDATA_FEALTY) == nData)
						return true;
				}
			}
			else if (_stricmp(szField, "level") == 0)
			{
				if (pSyn->GetInt(SYNDATA_FEALTY)!=ID_NONE)			// ������������
					return false;
				if(pSyn->GetInt(SYNDATA_LEADERID) != pUser->GetID())		// �����ǰ���
					return false;

				if (strcmp(szOpt, "=") == 0)
				{
					IF_NOT (nData >= SYNRANK_ONE && nData <= SYNRANK_FOUR)
						return false;
					
					pSyn->QueryModify()->SetData(SYNDATA_RANK, nData, true);
					return true;
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					int nRank = pSyn->GetInt(SYNDATA_RANK);
					nRank += nData;
					nRank = __min(SYNRANK_FOUR, __max(SYNRANK_ONE, nRank));
					
					pSyn->QueryModify()->SetData(SYNDATA_RANK, nRank, true);		// mast true				
					return true;
				}
				else if (strcmp(szOpt, "<") == 0)
				{
					if (pSyn->GetInt(SYNDATA_RANK) < nData)
						return true;
				}
				else if (strcmp(szOpt, "==") == 0)
				{
					if (pSyn->GetInt(SYNDATA_RANK) == nData)
						return true;
				}
			}
			return false;
		}
		break;
	case	ACTION_SYN_RANK:
		{

			int		nNewRank;
			NAMESTR	szTarget;
			if(!pszAccept || sscanf(pszAccept, "%d %s", &nNewRank, szTarget) != 2)
			{
				LOGERROR("ACTION %u: �����ACCEPT����", pAction->GetID());
				return false;
			}
//			CHECKF(nNewRank <= RANK_SAN);

/*			int	setLevel[5]={0};
			sscanf(szParam, "%d %d %d %d %d", &setLevel[0], &setLevel[1], &setLevel[2], &setLevel[3], &setLevel[4]);
			int	nNeedLevel = setLevel[::CutRange(5 - (nNewRank/10), 0, 4)];
*/
			// ������
			OBJID idSyn = pUser->GetSynID();
			if(idSyn == ID_NONE)
				return false;
			CSynPtr pSyn = SynManager()->QuerySyndicate(idSyn);
			if(!pSyn)
				return false;
			// ���Ȩ��
			int nRank = pUser->GetSynRank();
			if(nRank != RANK_LEADER)
				return false;

				
			CUser* pTarget = UserManager()->GetUser(szTarget);
			if(!pTarget)
			{
				pUser->SendSysMsg(STR_NOT_HERE);
				return false;
			}
			
			if(pUser->GetID() == pTarget->GetID())
				return false;

			OBJID	idTargetSyn = pTarget->GetSynID();
			if(idTargetSyn == ID_NONE || idTargetSyn != idSyn)
				return false;

			pTarget->QuerySynAttr()->SetRank(nNewRank);
			
			return true;


			/* check amount, temporary code.
			if(pUser->QuerySynAttr()->GetAssistantCount() >= MAX_ASSISTANTSIZE)
			{
				pUser->SendSysMsg(STR_SYN_PLACE_FULL);
				return false;
			}

			// target syn
			CUser* pTarget = UserManager()->GetUser(szTarget);
			if(!pTarget)
			{
				pUser->SendSysMsg(STR_NOT_HERE);
				return false;
			}
			if(pTarget->GetSynRank() > RANK_SAN || pTarget->GetLev() < nNeedLevel)
			{
				pUser->SendSysMsg(STR_CANNOT_RANK);
				return false;
			}
			if(pUser->GetID() == pTarget->GetID())
				return false;
			OBJID	idTargetSyn = pTarget->GetSynID();
			if(idTargetSyn == ID_NONE || idTargetSyn != idSyn)
				return false;

			pTarget->QuerySynAttr()->SetRank(nNewRank);
			
			return true;*/
		}
		break;
	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionUser(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction && pUser);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case ACTION_USER_TASK_MANAGER:	//����������
		{
			int nData = pAction->GetInt(ACTIONDATA_DATA);
			IF_NOT(nData>0)
				return false;
			
			char szOpt[128] = "";

			CTaskDetail * pTask = pUser->GetTaskDetail();
			IF_NOT(pTask)
				return false;

			if (1 == sscanf(szParam, "%s", szOpt))
			{
				if(0 == _stricmp(szOpt,"new"))
				{
					// ����Ѿ����ڣ���������
					if (pTask->QueryData(pUser->GetID(), nData))
						return false;

					ST_TASKDETAILDATA stData;
					stData.idTask = nData;
					stData.idUser = pUser->GetID();
					stData.nCompleteNum = 0;
					stData.nTaskPhase = 0;
					return pTask->CreateNewTaskDetailData(&stData);
				}
				else if(0 == _stricmp(szOpt,"delete"))
				{
					return pTask->DeleteData(pUser->GetID(), nData);
				}
				else if(0 == _stricmp(szOpt,"isexit"))
				{
					return (pTask->QueryData(pUser->GetID(), nData) != NULL);
				}
			}		
		}
		break;
	case ACTION_USER_TASK_OPE:
		{
			char szCurOpt[128], szOpe[128];
			int  nCurData = 0;
			
			if (3 == sscanf(szParam, "%s %s %d",szOpe, szCurOpt, &nCurData))
			{
				int nData = pAction->GetInt(ACTIONDATA_DATA);							
				CTaskDetail * pTask = pUser->GetTaskDetail();
				IF_NOT(pTask)
					return false;
				
				CTaskDetailData * pTaskData = NULL;
				if(nData > 0)
				{
					pTaskData = pTask->QueryData(pUser->GetID(),nData);
				}
				else if(nData == -1)
				{
					pTaskData = pTask->QueryData(pUser->TaskIterator());
				}
				if (!pTaskData)
					return false;

				if(0 == strcmp(szOpe,"phase")) //�׶�
				{
					int nPhaseLimit = 255;
					if(0 == strcmp(szCurOpt,">="))
					{
						return pTaskData->GetInt(TASKDETAILDATA_TASKPHASE) >= nCurData;
					}
					else if(0 == strcmp(szCurOpt,"=="))
					{
						return pTaskData->GetInt(TASKDETAILDATA_TASKPHASE) == nCurData;
					}
					else if(0 == strcmp(szCurOpt,"+="))
					{							
						int nPhase = AddToTop(pTaskData->GetInt(TASKDETAILDATA_TASKPHASE),nCurData,PHASE_LIMIT);
						pTaskData->SetInt(TASKDETAILDATA_TASKPHASE,nPhase,true);
						return true;
					}
					else if(0 == strcmp(szCurOpt,"="))
					{
						CHECKF(nCurData<=PHASE_LIMIT);
						pTaskData->SetInt(TASKDETAILDATA_TASKPHASE,nCurData,true);
						return true;
					}				
				}
				else if(0 == strcmp(szOpe,"completenum")) //��ɴ���
				{
					if(0 == strcmp(szCurOpt,">="))
					{
						return pTaskData->GetInt(TASKDETAILDATA_TASKCOMPLETENUM) >= nCurData;
					}
					else if(0 == strcmp(szCurOpt,"=="))
					{
						return pTaskData->GetInt(TASKDETAILDATA_TASKCOMPLETENUM) == nCurData;
					}
					else if(0 == strcmp(szCurOpt,"+="))
					{							
						int nNum = AddToTop(pTaskData->GetInt(TASKDETAILDATA_TASKCOMPLETENUM),nCurData,COMPLETENUM_LIMIT);
						pTaskData->SetInt(TASKDETAILDATA_TASKCOMPLETENUM,nNum,true);
						return true;
					}
					else if(0 == strcmp(szCurOpt,"="))
					{
						CHECKF(nCurData<=COMPLETENUM_LIMIT);
						pTaskData->SetInt(TASKDETAILDATA_TASKCOMPLETENUM,nCurData,true);
						return true;
					}					
				}
			}
			//������ʼʱ����в���---begin
			if (1 == sscanf(szParam, "%s",szOpe))
			{
				if(0 == strcmp(szOpe,"begintime")) //��ʼʱ��
				{
					if(2 == sscanf(szParam, "%s %s",szOpe,szCurOpt))
					{
						if(0 == strcmp(szCurOpt,"+=")) //
						{
							if(3 == sscanf(szParam, "%s %s %d",szOpe,szCurOpt,&nCurData))
							{
								int nData = pAction->GetInt(ACTIONDATA_DATA);							
								CTaskDetail * pTask = pUser->GetTaskDetail();
								IF_NOT(pTask)
									return false;
								
								CTaskDetailData * pTaskData = NULL;
								if(nData > 0)
								{
									 pTaskData = pTask->QueryData(pUser->GetID(),nData);
								}
								else if(nData == -1)
								{
									 pTaskData = pTask->QueryData(pUser->TaskIterator());
								}
								if (!pTaskData)
									return false;

								int nTimeData = nCurData; //����Ϊ��λ������
								CHECKF(nTimeData > 0);
								time_t ltime = (time_t)pTaskData->GetInt(TASKDETAILDATA_TASKCOMPLETENUM);
								struct tm *pTime;
								pTime = localtime( &ltime ); 
								CHECKF(pTime);
								pTime->tm_sec = pTime->tm_sec + nTimeData;
								CHECKF(pTime);
								time_t t1 = mktime(pTime);							
								pTaskData->SetInt(TASKDETAILDATA_TASKBEGINTIME,(int)t1,true);
								return true;
							}
						}
						else if(0 == strcmp(szCurOpt,">=")) //
						{
							int nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMinute = 0, nSec = 0;
							if(8 == sscanf(szParam, "%s %s %d-%d-%d %d:%d:%d",szOpe,szCurOpt,&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSec))
							{
								int nData = pAction->GetInt(ACTIONDATA_DATA);							
								CTaskDetail * pTask = pUser->GetTaskDetail();
								IF_NOT(pTask)
									return false;
								
								CTaskDetailData * pTaskData = NULL;
								if(nData > 0)
								{
									pTaskData = pTask->QueryData(pUser->GetID(),nData);
								}
								else if(nData == -1)
								{
									pTaskData = pTask->QueryData(pUser->TaskIterator());
								}
								if (!pTaskData)
									return false;

								struct tm time0;
								memset(&time0, 0L, sizeof(tm));
								time0.tm_year	=nYear-1900;
								time0.tm_mon	=nMonth-1;	
								time0.tm_mday	=nDay;
								time0.tm_hour	=nHour;
								time0.tm_min	=nMinute;
								time0.tm_sec	=nSec;
								time_t t0	=mktime(&time0);
								return pTaskData->GetInt(TASKDETAILDATA_TASKBEGINTIME) >= (int)t0;
							}
						}
						else if(0 == strcmp(szCurOpt,"==")) //
						{
							int nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMinute = 0, nSec = 0;
							if(8 == sscanf(szParam, "%s %s %d-%d-%d %d:%d:%d",szOpe,szCurOpt,&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSec))
							{
								int nData = pAction->GetInt(ACTIONDATA_DATA);							
								CTaskDetail * pTask = pUser->GetTaskDetail();
								IF_NOT(pTask)
									return false;
								
								CTaskDetailData * pTaskData = NULL;
								if(nData > 0)
								{
									pTaskData = pTask->QueryData(pUser->GetID(),nData);
								}
								else if(nData == -1)
								{
									pTaskData = pTask->QueryData(pUser->TaskIterator());
								}
								if (!pTaskData)
									return false;

								struct tm time0;
								memset(&time0, 0L, sizeof(tm));
								time0.tm_year	=nYear-1900;
								time0.tm_mon	=nMonth-1;	
								time0.tm_mday	=nDay;
								time0.tm_hour	=nHour;
								time0.tm_min	=nMinute;
								time0.tm_sec	=nSec;
								time_t t0	=mktime(&time0);
								return pTaskData->GetInt(TASKDETAILDATA_TASKBEGINTIME) == (int)t0;
							}
						}
						else if(0 == strcmp(szCurOpt,"=")) //
						{
							int nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMinute = 0, nSec = 0;
							if(8 == sscanf(szParam, "%s %s %d-%d-%d %d:%d:%d",szOpe,szCurOpt,&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSec))
							{
								int nData = pAction->GetInt(ACTIONDATA_DATA);							
								CTaskDetail * pTask = pUser->GetTaskDetail();
								IF_NOT(pTask)
									return false;
								
								CTaskDetailData * pTaskData = NULL;
								if(nData > 0)
								{
									pTaskData = pTask->QueryData(pUser->GetID(),nData);
								}
								else if(nData == -1)
								{
									pTaskData = pTask->QueryData(pUser->TaskIterator());
								}
								if (!pTaskData)
									return false;
									
								struct tm time0;
								memset(&time0, 0L, sizeof(tm));
								time0.tm_year	=nYear-1900;
								time0.tm_mon	=nMonth-1;	
								time0.tm_mday	=nDay;
								time0.tm_hour	=nHour;
								time0.tm_min	=nMinute;
								time0.tm_sec	=nSec;
								time_t t0	=mktime(&time0);
								pTaskData->SetInt(TASKDETAILDATA_TASKBEGINTIME, (int)t0,true);
								return true;
							}

						}
						else if(0 == strcmp(szCurOpt,"reset")) //������ʼʱ������Ϊ��ǰʱ��
						{
							int nData = pAction->GetInt(ACTIONDATA_DATA);							
							CTaskDetail * pTask = pUser->GetTaskDetail();
							IF_NOT(pTask)
								return false;
							
							CTaskDetailData * pTaskData = NULL;
							if(nData > 0)
							{
								pTaskData = pTask->QueryData(pUser->GetID(),nData);
							}
							else if(nData == -1)
							{
								pTaskData = pTask->QueryData(pUser->TaskIterator());
							}
							if (!pTaskData)
								return false;
							time_t tCur=time(NULL); 
							pTaskData->SetInt(TASKDETAILDATA_TASKBEGINTIME, (int)tCur,true);
							return true;
						}
					}
				}
			}
			//������ʼʱ����в���---end
			return false;
		}
		break;		
	case ACTION_USER_TASK_LOCALTIME: //��ǰʱ��������ʼʱ��Ƚϵ�action��
		{
			int nData = pAction->GetInt(ACTIONDATA_DATA);
			IF_NOT(nData>0)		
				return false;

			CTaskDetail * pTask = pUser->GetTaskDetail();
			IF_NOT(pTask)
				return false;

			int  nCurData =0; //����Ϊ��λ������					
			
			if (1 == sscanf(szParam, "%d",&nCurData))
			{
				time_t ltime;
				time( &ltime);
				struct tm *pTime;
				pTime = localtime( &ltime ); 
				CHECKF(pTime);
				pTime->tm_sec = pTime->tm_sec - nCurData;
				CHECKF(pTime);
				time_t tCmp = mktime(pTime);	
				
				CTaskDetailData * pTaskData = pTask->QueryData(pUser->GetID(),nData);
				if(pTaskData && tCmp > pTaskData->GetInt(TASKDETAILDATA_TASKBEGINTIME) ) //��ʱ
					return true;
			}
			return false;
		}
		break;
	case ACTION_USER_TASK_FIND:  //����ҵ�����//param: 'find taskid phase completenum ';��������ID���׶Σ���ɴ�����ѯ�����¼		   //		 'findnext'	;��ѯ��һ����¼
		{
			char szOpt[128];
			if (1 == sscanf(szParam, "%s", szOpt))
			{
				if(0 == _stricmp(szParam,"find"))
				{
					int nTaskID=0,nPhase=0, nCompleteNum=0;
					if (4 == sscanf(szParam, "%s %d %d %d",szOpt, &nTaskID, &nPhase, &nCompleteNum))
					{							
						CTaskDetail * pTask = pUser->GetTaskDetail();	
						IF_NOT(pTask)
							return false;						
						return pTask->FindData(nTaskID,nPhase,nCompleteNum,pUser->TaskIterator());						
					}
				}
				else if(0 == _stricmp(szParam,"findnext"))
				{
					CTaskDetail * pTask = pUser->GetTaskDetail();	
					IF_NOT(pTask)
						return false;
					return pTask->FindNextData(pUser->TaskIterator());
				}
			}
			return false;
		}
		break;
	case	ACTION_USER_CHKIN_CARD2:
		{
			if (pUser->CheckInCard2())
				return true;
		}
		break;

	case ACTION_USER_CHKOUT_CARD2:
		{
			if (pUser->CheckOutCard2())
				return true;
		}
		break;

	case	ACTION_USER_CHKIN_CARD:
		{
			if (pUser->CheckInCard())
				return true;
		}
		break;

	case ACTION_USER_CHKOUT_CARD:
		{
			if (pUser->CheckOutCard())
				return true;
		}
		break;

	case	ACTION_USER_MEDIAPLAY:
		{
			char szOpt[256]		= "";
			char szMedia[256]	= "";
			if (2 == sscanf(szParam, "%s %s", szOpt, szMedia))
			{
				if (0 == _stricmp(szOpt, "play"))
				{
					CMsgName msg;
					IF_OK(msg.Create(NAMEACT_PLAYER_WAVE, szMedia))
						pUser->SendMsg(&msg);

				}
				else if (0 == _stricmp(szOpt, "broacast"))
				{
					CMsgName msg;
					IF_OK(msg.Create(NAMEACT_PLAYER_WAVE, szMedia))
						pUser->BroadcastRoomMsg(&msg, true);
				}
			}
		}
		break;

	case	ACTION_USER_TASKMASK:
		{
			char szOpt[256] = "";
			int idx = 0;

			if (2 == sscanf(szParam, "%s %d", szOpt, &idx))
			{
				if (0 == _stricmp(szOpt, "chk"))
				{
					if (pUser->ChkTaskMask(idx))
						return true;
				}
				else if (0 == _stricmp(szOpt, "add"))
				{
					pUser->AddTaskMask(idx);
					return true;
				}
				else if (0 == _stricmp(szOpt, "clr"))
				{
					pUser->ClrTaskMask(idx);
					return true;
				}
				else
					LOGERROR("ACTION %u: ����Ĳ���", pAction->GetID());
			}
		}
		break;

	case	ACTION_USER_EFFECT:
		{
			char szOpt[256] = "";
			char szEffect[256] = "";

			if (2 == sscanf(szParam, "%s %s", szOpt, szEffect))
			{
				if (0 == _stricmp(szOpt, "self"))
				{
					CMsgName msg;
					IF_OK (msg.Create(NAMEACT_ROLEEFFECT, szEffect, pUser->GetID()))
						pUser->BroadcastRoomMsg(&msg, true);

					return true;
				}
				else if (0 == _stricmp(szOpt, "couple"))
				{
					CMsgName msg;
					IF_OK (msg.Create(NAMEACT_ROLEEFFECT, szEffect, pUser->GetID()))
						pUser->BroadcastRoomMsg(&msg, true);

					if (pUser->IsMarried())
					{
						CUser* pMate = UserManager()->GetUser(pUser->GetMate());
						if (pMate)	// online
						{
							IF_OK (msg.Create(NAMEACT_ROLEEFFECT, szEffect, pMate->GetID()))
								pMate->BroadcastRoomMsg(&msg, true);
						}
					}

					return true;
				}
				else if (0 == _stricmp(szOpt, "team"))
				{
					CMsgName msg;
					IF_OK (msg.Create(NAMEACT_ROLEEFFECT, szEffect, pUser->GetID()))
						pUser->BroadcastRoomMsg(&msg, true);

					CTeam* pTeam = pUser->GetTeam();
					if (pTeam)
					{
						int nTeamMembers = pTeam->GetMemberAmount();
						for (int i=0; i<nTeamMembers; i++)
						{
							OBJID idMember = pTeam->GetMemberByIndex(i);
							CUser* pMember = UserManager()->GetUser(idMember);
							if (pMember && pMember != pUser)
							{
								CMsgName msg;
								IF_OK (msg.Create(NAMEACT_ROLEEFFECT, szEffect, pMember->GetID()))
									pMember->BroadcastRoomMsg(&msg, true);
							}
						}
					}
					
					return true;
				}
				else if (0 == _stricmp(szOpt, "target"))
				{
					if (pRole)
					{
						CMsgName msg;
						IF_OK (msg.Create(NAMEACT_ROLEEFFECT, szEffect, pRole->GetID()))
							pRole->BroadcastRoomMsg(&msg, true);
						
						return true;
					}
				}
				else
					LOGERROR("ACTION %u: ����Ĳ���", pAction->GetID());
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case	ACTION_USER_SEX:
		{
			return (pUser->GetSex() == 1);
		}
		break;

	case	ACTION_USER_MARRIAGE:
		{
			return pUser->IsMarried();
		}
		break;

	case	ACTION_USER_DIVORCE:
		{
			return pUser->Divorce();
		}
		break;

	case	ACTION_USER_BONUS:
		{
			return pUser->DoBonus();
		}
		break;

	case	ACTION_USER_LOG:
		{
			::GmLogSave(szParam);
			return true;
		}
		break;

	case	ACTION_USER_ATTR:
		{
			PARAMBUF	szAttr;
			PARAMBUF	szOpt;
			PARAMBUF	szData;
			if(sscanf(szParam, "%s %s %s", szAttr, szOpt, szData) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}
			int		nData = atoi(szData);
			bool	bUpdate = UPDATE_FALSE;

			if(_stricmp(szAttr, "life") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					return pUser->AddAttrib(_USERATTRIB_LIFE, nData, SYNCHRO_TRUE);
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetLife() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetLife() < nData);
				}
			}
			else if(_stricmp(szAttr, "mana") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					return pUser->AddAttrib(_USERATTRIB_MANA, nData, SYNCHRO_TRUE);
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetMana() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetMana() < nData);
				}
			}
			else if(_stricmp(szAttr, "money") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					return pUser->AddAttrib(_USERATTRIB_MONEY, nData, SYNCHRO_TRUE);
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetMoney() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetMoney() < nData);
				}
			}
			else if(_stricmp(szAttr, "exp") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					return pUser->AddAttrib(_USERATTRIB_EXP, nData, SYNCHRO_TRUE);
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetExp() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetExp() < nData);
				}
			}
			else if(_stricmp(szAttr, "pk") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddPk(nData);
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if(pUser->GetPk() == nData)
						return true;
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					if(pUser->GetPk() < nData)
						return true;
				}
			}
			else if(_stricmp(szAttr, "profession") == 0)
			{
				if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetProfession() == nData);
				}
				else if(strcmp(szOpt, ">=") == 0)
				{
					return (pUser->GetProfession() >= nData);
				}
				else if(strcmp(szOpt, "<=") == 0)
				{
					return (pUser->GetProfession() <= nData);
				}
				else if(strcmp(szOpt, "set") == 0)
				{
					pUser->QueryDataForAction()->SetProfession(nData, true);
					pUser->SetAttrib(_USERATTRIB_PORFESSION, nData, SYNCHRO_BROADCAST);
					return true;
				}
			}
			else if(_stricmp(szAttr, "level") == 0)
			{
				/*if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddPk(nData);
				}
				else */
				if(strcmp(szOpt, "==") == 0)
				{
					if(pUser->GetLev() == nData)
						return true;
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					if(pUser->GetLev() < nData)
						return true;
				}
			}
			else if(_stricmp(szAttr, "force") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_FORCE, nData, SYNCHRO_TRUE);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return ((int)pUser->GetForce() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return ((int)pUser->GetForce() < nData);				
				}
			}
			else if(_stricmp(szAttr, "speed") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_SPEED, nData, SYNCHRO_TRUE);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return ((int)pUser->GetSpeed() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return ((int)pUser->GetSpeed() < nData);				
				}
			}
			else if(_stricmp(szAttr, "dexterity") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_DEGREE, nData, SYNCHRO_TRUE);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return ((int)pUser->GetDegree() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return ((int)pUser->GetDegree() < nData);				
				}
			}
			else if(_stricmp(szAttr, "physique") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_PHYSIQUE, nData, SYNCHRO_TRUE);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return ((int)pUser->GetPhysique() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return ((int)pUser->GetPhysique() < nData);
				}
			}
			/*else if(_stricmp(szAttr, "soul") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_SOUL, nData, SYNCHRO_TRUE);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return ((int)pUser->GetSoul() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return ((int)pUser->GetSoul() < nData);				
				}
			}*/
			else if(_stricmp(szAttr, "rank") == 0)
			{
				if(pUser->GetSynID() == ID_NONE)
					return false;

				if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetSynRank() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetSynRank() < nData);				
				}
			}
			else if(_stricmp(szAttr, "rankshow") == 0)
			{
				if(pUser->GetSynID() == ID_NONE)
					return false;

				if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetSynRankShow() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetSynRankShow() < nData);				
				}
			}
			else if(_stricmp(szAttr, "iterator") == 0)
			{
				if(strcmp(szOpt, "=") == 0)
				{
					pUser->TaskIterator() = nData;
					return true;
				}
				else if(strcmp(szOpt, "<=") == 0)
				{
					if (pUser->TaskIterator() <= nData)
						return true;
				}
				else if(strcmp(szOpt, "+=") == 0)
				{
					pUser->TaskIterator() += nData;
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					if (pUser->TaskIterator() == nData)
						return true;
				}
			}
			else if(_stricmp(szAttr, "crime") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					if (nData == 0)
						return (pUser->QueryStatus(STATUS_CRIME) == NULL);
					else
						return (pUser->QueryStatus(STATUS_CRIME) != NULL);
				}
				else if (strcmp(szOpt, "set") == 0)
				{
					if (nData == 0)
					{
						CRole::DetachStatus(pUser->QueryRole(), STATUS_CRIME);
						return true;
					}
					else
					{
						pUser->SetCrimeStatus();
						return true;
					}
				}
			}
			else if(_stricmp(szAttr, "gamecard") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->CountCard() == nData);
				}
				else if(strcmp(szOpt, ">=") == 0)
				{
					return (pUser->CountCard() >= nData);
				}
				else if(strcmp(szOpt, "<=") == 0)
				{
					return (pUser->CountCard() <= nData);
				}
			}
			else if(_stricmp(szAttr, "gamecard2") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->CountCard2() == nData);
				}
				else if(strcmp(szOpt, ">=") == 0)
				{
					return (pUser->CountCard2() >= nData);
				}
				else if(strcmp(szOpt, "<=") == 0)
				{
					return (pUser->CountCard2() <= nData);
				}
			}
			else if(_stricmp(szAttr, "xp") == 0)
			{
				if (strcmp(szOpt, "+=") == 0)
				{
					pUser->AddXp(nData);
					return true;
				}
			}
			else if(_stricmp(szAttr, "metempsychosis") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetMetempsychosis() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetMetempsychosis() < nData);
				}
			}
			else  if(_stricmp(szAttr, "nobility_rank") == 0)     //add huang 2003.12.29
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetNobilityRank() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetNobilityRank() < nData);
				}
				else if(strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_NOBILITYRANK, nData, SYNCHRO_TRUE);
					return true;
				}
				else if(strcmp(szOpt, "=") == 0)
				{
					pUser->SetAttrib(_USERATTRIB_NOBILITYRANK, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else if (strcmp(szAttr, "mercenary_rank") == 0)		// Ӷ���ȼ�
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetMercenaryRank() == nData);
				}
				else if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetMercenaryRank() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_MERCENARYRANK, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else if (strcmp(szAttr, "mercenary_exp") == 0)		// Ӷ������
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetMercenaryExp() == nData);
				}
				else if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetMercenaryExp() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_MERCENARYEXP, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else if (strcmp(szAttr, "exploit") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetExploit() == nData);
				}
				else if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetExploit() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_EXPLOIT, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else if(_stricmp(szAttr, "maxlifepercent") == 0)
			{
				if(strcmp(szOpt, "+=") == 0)
				{
					int nMyData = pUser->QueryDataForAction()->GetMaxLifePercent() + nData;
					pUser->SetMaxLifePercent(nMyData, true);
					return true;
				}
				else if(strcmp(szOpt, "==") == 0)
				{
					return (pUser->QueryDataForAction()->GetMaxLifePercent() == nData);
				}
				else if(strcmp(szOpt, "<") == 0)
				{
					return (pUser->QueryDataForAction()->GetMaxLifePercent() < nData);
				}
			}
			else if (_stricmp(szAttr, "tutor_exp") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetTutorExp() == nData);
				}
				else if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetTutorExp() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_TUTOR_EXP, nData, SYNCHRO_TRUE);
					return true;
				}
				else if (strcmp(szOpt, "=") == 0)
				{
					pUser->SetAttrib(_USERATTRIB_TUTOR_EXP, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else if (_stricmp(szAttr, "tutor_level") == 0)
			{
				if (strcmp(szOpt, "==") == 0)
				{
					return (pUser->GetTutorLevel() == nData);
				}
				else if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetTutorLevel() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					pUser->AddAttrib(_USERATTRIB_TUTOR_LEVEL, nData, SYNCHRO_TRUE);
					return true;
				}
				else if (strcmp(szOpt, "=") == 0)
				{
					pUser->SetAttrib(_USERATTRIB_TUTOR_LEVEL, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else if (_stricmp(szAttr, "syn_proffer") == 0) 
			{
				//---jinggy---���ɹ��׶�---begin			
				if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->QuerySynProffer() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{
					pUser->QuerySynAttr()->AddProffer(nData);
					return true;
				}		
				else if (strcmp(szOpt, "=") == 0)
				{
					pUser->QuerySynAttr()->SetProffer(nData);
					return true;
				}
				//---jinggy---���ɹ��׶�---end
			}
			else if (_stricmp(szAttr, "maxeudemon") == 0)
			{
				if (strcmp(szOpt, "<") == 0)
				{
					return (pUser->GetMedalSelect() < nData);
				}
				else if (strcmp(szOpt, "+=") == 0)
				{	
					pUser->AddAttrib(_USERATTRIB_MAXEUDEMON, nData, SYNCHRO_TRUE);
					return true;
				}		
				else if (strcmp(szOpt, "=") == 0)
				{
					pUser->SetAttrib(_USERATTRIB_MAXEUDEMON, nData, SYNCHRO_TRUE);
					return true;
				}
			}
			else
			{
				ASSERT(!"ACTION_USER_ATTR");
			}
		}
		break;
	case	ACTION_USER_FULL:
		{
			if (0 == _stricmp(szParam, "life"))
			{
				return pUser->AddAttrib(_USERATTRIB_LIFE, pUser->GetMaxLife(), SYNCHRO_TRUE);
			}
			else if (0 == _stricmp(szParam, "mana"))
			{
				return pUser->AddAttrib(_USERATTRIB_MANA, pUser->GetMaxMana(), SYNCHRO_TRUE);
			}
		}
		break;
	case	ACTION_USER_CHGMAP:
		{
			OBJID idMap = ID_NONE;
			int nMapX=0, nMapY=0;
			BOOL bImmediacy = false;

			if (sscanf(szParam, "%u %d %d %d", &idMap, &nMapX, &nMapY, &bImmediacy) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if (!pUser->GetMap()->IsTeleportDisable() || bImmediacy)
			{
				int ret = pUser->FlyMap(idMap, nMapX, nMapY);
				if(ret == FLYMAP_NORMAL)
					return true;
				else if(ret == FLYMAP_MAPGROUP)
				{
					m_pUser	= NULL;					// ����������
					return true;
				}
				else if(ret == FLYMAP_ERROR)
				{
					pUser->FlyMap(DEFAULT_LOGIN_MAPID, DEFAULT_LOGIN_POSX, DEFAULT_LOGIN_POSY);
					UserManager()->KickOutSocket(pUser->GetSocketID(), "�������������");
				}
			}
		}
		break;
	case	ACTION_USER_CHGMAPRECORD:
		{
			int ret = pUser->FlyMap(pUser->QueryDataForAction()->GetRecordMap(), 
									pUser->QueryDataForAction()->GetRecordX(), 
									pUser->QueryDataForAction()->GetRecordY());
			if(ret == FLYMAP_NORMAL)
				return true;
			else if(ret == FLYMAP_MAPGROUP)
			{
				m_pUser	= NULL;					// ����������
				return true;
			}
		}
		break;
	case ACTION_USER_CHGTO_MAINMAP: //������ͼ�ĸ���㸴��
		{
			return pUser->FlyToMainMap();
		}
		break;		
	case ACTION_USER_CHGTO_RANDOMPOS:
		{
			return pUser->FlyToRandomPos();
		}
		break;
	case	ACTION_USER_CHGLINKMAP:
		{
			CHECKF(pRole);
			CNpc* pNpc;
			CHECKF(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)));
			//CHECKF(pNpc->IsLinkNpc());

			CGameMap* pMap	= pNpc->QueryLinkMap()->GetLinkMap();
			CHECKF(pMap);

			POINT pos = pMap->GetPortal();
			int ret = pUser->FlyMap(pMap->GetID(), pos.x, pos.y);
			if(ret == FLYMAP_NORMAL)
				return true;
			else if(ret == FLYMAP_MAPGROUP)
			{
				ASSERT(!"ACTION_USER_CHGLINKMAP");
				m_pUser	= NULL;					// ����������
				return true;
			}
		}
		break;
	case	ACTION_USER_RECORDPOINT:
		{
			OBJID idMap = ID_NONE;
			int nMapX=0, nMapY=0;
			if (3 == sscanf(szParam, "%u %d %d", &idMap, &nMapX, &nMapY))
			{
				pUser->SetRecordPos(idMap, nMapX, nMapY, true);
				return true;
			}
		}
		break;
	case	ACTION_USER_HAIR:
		{
			PARAMBUF szCmd = "";
			DWORD dwData = 0;
			if (2 == sscanf(szParam, "%s %u", szCmd, &dwData))
			{
				int nHair = pUser->GetHair();

				if (0 == _stricmp("color", szCmd))
				{
					dwData %= 10;
					nHair = nHair-((nHair%1000)/100)*100+dwData*100;
					pUser->SetAttrib(_USERATTRIB_HAIR, nHair, SYNCHRO_TRUE);

					return true;
				}
				else if (0 == _stricmp("style", szCmd))
				{
					dwData %= 100;
					
					nHair = nHair-(nHair%100)+dwData;
					if (nHair < 100)	// no color
					{
						const int DEFAULT_COLOR = 3;
						nHair += DEFAULT_COLOR*100;
					}

					pUser->SetAttrib(_USERATTRIB_HAIR, nHair, SYNCHRO_TRUE);

					return true;
				}
			}
		}
		break;
	case	ACTION_USER_TALK:
		{
			int nChannel = pAction->GetInt(ACTIONDATA_DATA);
			if (nChannel == 0)
				nChannel = _TXTATR_NORMAL;
			pUser->SendSysMsg(nChannel, "%s", szParam);
			return true;
		}
		break;
	case	ACTION_USER_MAGIC:
		{
			if (!pUser->QueryMagic())
				return false;

			PARAMBUF	szCmd;
			int			nType;
			int			nData=0;
			bool		bSave=true;
			int	nNum = 0;
			if((nNum=sscanf(szParam, "%s %u %u %u", szCmd, &nType, &nData, &bSave)) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			if(_stricmp(szCmd, "check") == 0)
			{
				if(nNum == 3)
					return pUser->QueryMagic()->CheckLevel(nType, nData);
				else
					return pUser->QueryMagic()->CheckType(nType);
			}
			else if(_stricmp(szCmd, "learn") == 0)
			{
				return pUser->QueryMagic()->LearnMagic(nType, nData, bSave) != ID_NONE;
			}
			else if(_stricmp(szCmd, "uplevel") == 0)
			{
				return pUser->QueryMagic()->UpLevelByTask(nType);
			}
			else if(_stricmp(szCmd, "addexp") == 0)
			{
				return pUser->QueryMagic()->AwardExp(nType, 0, nData);
			}
			else
			{
				ASSERT(!"ACTION_USER_MAGIC ����Ĳ�������!");
			}
			return true;
		}
		break;
	/*case ACTION_USER_WEAPONSKILL:
		{
			PARAMBUF szCmd = "";
			int nSkillType = 0, nLev = 0;
			if (3 == sscanf(szParam, "%s %d %d", szCmd, &nSkillType, &nLev))
			{
				if (0 == _stricmp("check", szCmd))
				{
					CUserWeaponSkill* pSkill = pUser->GetWeaponSkill(nSkillType);
					if (pSkill)
					{
						if (pSkill->GetLevel() >= nLev)
							return true;
					}

				}
				else if (0 == _stricmp("learn", szCmd))
				{
					if (pUser->AwardWeaponSkill(nSkillType, nLev))
						return true;
				}				
			}
		}
		break;*/

	case ACTION_USER_SUPERMANLIST:
		{
			OBJID idTask;
			int nNumber;
			if (2 == sscanf(szParam, "%u %d", &idTask, &nNumber))
			{
				int	idx = pUser->TaskIterator();
				pUser->TaskIterator()	+= nNumber;
				int idxTask = pUser->PushTaskID(idTask);		// next page
				pUser->QuerySupermanList(idx, idxTask, nNumber);

				// no next		return true;
			}
		}
		break;
	case ACTION_USER_CREATEMAP:
		{
			PARAMBUF	szName;
			OBJID		idOwner, idRebornMap;
			int			nOwnerType, nMapDoc, nType, nPortalX, nPortalY, nRebornPortal, nResLev;
			if(sscanf(szParam, "%s %d %u %d %d %d %d %u %d %d", 
					szName, &nOwnerType, &idOwner, &nMapDoc, &nType, &nPortalX, &nPortalY, &idRebornMap, &nRebornPortal, &nResLev) < 10)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			NewMapInfo	info;
			memset(&info, 0, sizeof(NewMapInfo));
			SafeCopy(info.szName, szName, _MAX_NAMESIZE);
			info.nMapDoc		= nMapDoc; 
			info.nType			= nType;
			info.nOwnerType		= nOwnerType;
			info.idOwner		= idOwner;
			info.nMapGroup		= MapGroup(PID)->GetMapGroup();
			info.idLikeMap		= pUser->GetMapID();
			info.nLinkX			= pUser->GetPosX();
			info.nLinkY			= pUser->GetPosY();
			info.nPortalX		= nPortalX;
			info.nPortalY		= nPortalY;
			info.idRebornMap	= idRebornMap;
			info.nRebornPortal	= nRebornPortal;
			info.nResLev		= nResLev;

			OBJID idMap = MapManager()->CreateDynaMap(&info);
			if(idMap == ID_NONE)
				return false;

			pUser->QueryDataForAction()->SetHomeID(idMap);

			return true;
		}
		break;
	case ACTION_USER_ENTER_HOME:
		{
			OBJID idHome = pUser->GetHomeID();
			if(idHome == ID_NONE)
				return false;
			CGameMap* pMap = MapManager()->QueryMap(idHome);
			CHECKF(pMap);
			POINT	pos = pMap->GetPortal();
			OBJID idOldMap = pUser->GetMapID();
			int	nOldX = pUser->GetPosX();
			int	nOldY = pUser->GetPosY();
			if (pUser->FlyMap(pMap->GetID(), pos.x, pos.y) == FLYMAP_NORMAL)	// no FLYMAP_MAPGROUP
			{
				CTeam* pTeam = pUser->GetTeam();
				if(pTeam && pTeam->GetLeader() == pUser->GetID())
				{
					for(int i = pTeam->GetMemberAmount()-1; i >= 0; i--)
					{
						OBJID idTarget = pTeam->GetMemberByIndex(i);
						CUser* pTarget = UserManager()->GetUser(idTarget);
						if(pTarget && pTarget->GetMapID() == idOldMap && pTarget->GetDistance(nOldX, nOldY) <= ENTER_HOME_TEAM_DISTANCE)
						{
							pTarget->FlyMap(pMap->GetID(), pos.x, pos.y);
							pTarget->Synchro();
						}
					}
				}
				return true;
			}
		}
		break;
	case ACTION_USER_ENTER_MATE_HOME:
		{
			OBJID idHome = pUser->GetMateHomeID();
			if(idHome == ID_NONE)
				return false;
			CGameMap* pMap = MapManager()->QueryMap(idHome);
			CHECKF(pMap);
			POINT	pos = pMap->GetPortal();
			return (pUser->FlyMap(pMap->GetID(), pos.x, pos.y) != FLYMAP_ERROR);
		}
		break;
	case	ACTION_USER_FLY_NEIGHBOR:
		{
			int		nData;
			if (sscanf(szParam, "%d", &nData) < 1)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			CRoleSet::Iterator pRole = _RoleManager(PID)->QuerySet()->NewEnum();
			while(pRole.Next())
			{
				CNpc* pNpc;
				if(pRole && pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
				{
					if(pNpc->GetType() == _ROLE_NEIGHBOR_DOOR && pNpc->GetData(NEIGHBORNPC_SERIAL) == nData)
					{
						pUser->FlyMap(pNpc->GetMapID(), pNpc->GetData(NEIGHBORNPC_X), pNpc->GetData(NEIGHBORNPC_Y));
						return true;
					}
				}
			}
		}
		break;
	case	ACTION_USER_UNLEARN_MAGIC:
		{
			if (!pUser->QueryMagic())
				return false;

			int		nData[MAX_UNLEARN_NUMBER+1] = { 0 };		//? +1: more one
			ASSERT(MAX_UNLEARN_NUMBER == 20);
			int nNum = sscanf(szParam, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
						&nData[0], &nData[1], &nData[2], &nData[3], &nData[4], 
						&nData[5], &nData[6], &nData[7], &nData[8], &nData[9], 
						&nData[10], &nData[11], &nData[12], &nData[13], &nData[14], 
						&nData[15], &nData[16], &nData[17], &nData[18], &nData[19], 
						&nData[20] );
			if(nNum < 1 || nNum > MAX_UNLEARN_NUMBER)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			bool bDrop = false;
			for(int i = 0; i < nNum; i++)
			{
				int nType = nData[i];
				pUser->QueryMagic()->UnlearnMagic(nType, bDrop);
			}

			return true;
		}
		break;
	case	ACTION_USER_DROP_MAGIC:
		{
			if (!pUser->QueryMagic())
				return false;
			
			int		nData[MAX_UNLEARN_NUMBER+1] = { 0 };		//? +1: more one
			ASSERT(MAX_UNLEARN_NUMBER == 20);
			int nNum = sscanf(szParam, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
						&nData[0], &nData[1], &nData[2], &nData[3], &nData[4], 
						&nData[5], &nData[6], &nData[7], &nData[8], &nData[9], 
						&nData[10], &nData[11], &nData[12], &nData[13], &nData[14], 
						&nData[15], &nData[16], &nData[17], &nData[18], &nData[19], 
						&nData[20] );
			if(nNum < 1 || nNum > MAX_UNLEARN_NUMBER)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			bool bDrop = true;
			for(int i = 0; i < nNum; i++)
			{
				int nType = nData[i];
				pUser->QueryMagic()->UnlearnMagic(nType, bDrop);
			}

			return true;
		}
		break;
	/*case	ACTION_USER_UNLEARN_SKILL:
		{
			return pUser->UnlearnAllSkill();
		}
		break;*/

	case	ACTION_USER_REBIRTH:
		{
			int		nProf, nLook;
			if (sscanf(szParam, "%d %d", &nProf, &nLook) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			if(pUser->Rebirth(nProf, nLook))
			{
				::MyLogSave("sys\\rebirth.log", "User[%s][%d], prof[%d], level[%d] rebirth to prof[%d], look[%d]", 
					pUser->GetName(), pUser->GetID(), pUser->GetProfession(), pUser->GetLev(), nProf, nLook);
				return true;
			}
		}
		break;
	case ACTION_USER_WEBPAGE:
		{
			pUser->SendSysMsg(_TXTATR_WEBPAGE, szParam);
			return true;
		}
		break;
	case ACTION_USER_BBS:
		{
			pUser->SendSystemBBS(szParam);
			return true;
		}
		break;
	case ACTION_USER_OPEN_DIALOG:
		{
			CMsgAction	msg;
			IF_OK(msg.Create(pUser->GetID(), pUser->GetPosX(), pUser->GetPosY(), pUser->GetDir(), actionOpenDialog, pAction->GetInt(ACTIONDATA_DATA)))
				pUser->SendMsg(&msg);

			char szOpt[16];
			int nRebate=0;
			if(sscanf(szParam, "%s %d",szOpt,&nRebate) == 2)
			{
				if(_stricmp(szOpt,"setrebate")==0)
				{
					CNpc * pNpc;
					if(!pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
						return false;

					pNpc->SetInt(NPCDATA_DATA0,nRebate);
					//��ͻ��˷��ʹ�����Ϣ
					CMsgDataArray msg;
					DWORD dwArray[2];
					dwArray[0] =pRole->GetID();
					dwArray[1] = nRebate;
					if(msg.Create(_DATAARRAY_SETITEMREBATE,2,(unsigned long*)dwArray))
						pUser->SendMsg(&msg);
				}
			}

			const char* pWord	= szParam;
			for(int i = 0; i < MAX_MENUTASKSIZE; i++)
			{
				OBJID	idTask = strtoul(pWord, (char**)&pWord, 10);
				if(idTask != ID_NONE)
					pUser->PushTaskID(idTask);
				else
					break;
			}

			return true;
		}
		break;
	case ACTION_USER_CHGMAP_REBORN:
		{
			OBJID	idRebornMap = ID_NONE;
			POINT	pos;
			IF_OK(pUser->GetMap()->GetRebornMap(&idRebornMap, &pos))
				pUser->FlyMap(idRebornMap, pos.x, pos.y);
			return true;
		}
		break;
	case ACTION_USER_DEL_WPG_BADGE:
		{
			return pUser->DelAllBadge();
		}
		break;
	case ACTION_USER_CHK_WPG_BADGE:
		{
			int nItemType = 0;
			if(strlen(szParam))
				nItemType = atoi(szParam);
			return pUser->CheckBadge(nItemType);
		}
		break;
	case ACTION_USER_TAKESTUDENTEXP:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				int nExpTake = atoi(pszAccept);
				if (nExpTake > 0)
					return pUser->TakeExpFromStudent(nExpTake);
				else
					return false;
			}
		}
		break;
	// team part. �� û�ж���ʱ���᷵�� false������ACTION�������ӳ� �� ---------------------------------------------------------------
	case ACTION_TEAM_BROADCAST:
		{
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(pMember && pMember->GetID() != pUser->GetID())
				{
					pMember->SendSysMsg(_TXTATR_TEAM, szParam);
				}
			}
			return true;
		}
		break;
	case	ACTION_TEAM_ATTR:
		{
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			PARAMBUF	szField, szOpt="(none)";
			int		nData=0;
			if (sscanf(szParam, "%s %s %d", szField, szOpt, &nData) < 1)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			if(strcmp(szField, "count")==0)
			{
				if(strcmp(szOpt, "<")==0)
				{
					if(!( pTeam->GetMemberAmount() < nData ))
						return false;
				}
				else if(strcmp(szOpt, "==")==0)
				{
					if(!( pTeam->GetMemberAmount() == nData ))
						return false;
				}
				else
				{
					return false;
				}
				return true;
			}

			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(!pMember)
					return false;		//? ���߳�
				if(pMember && pMember->GetID() != pUser->GetID())
				{
					if(strcmp(szField, "money")==0)
					{
						if(strcmp(szOpt, "+=")==0)
						{
							pMember->GainMoney(nData, SYNCHRO_TRUE);
						}
						else if(strcmp(szOpt, "<")==0)
						{
							if(!( pMember->GetMoney() < nData ))
								return false;
						}
						else if(strcmp(szOpt, ">")==0)
						{
							if(!( pMember->GetMoney() > nData ))
								return false;
						}
						else if(strcmp(szOpt, "==")==0)
						{
							if(!( pMember->GetMoney() == nData ))
								return false;
						}
						else
							return false;
					}
					else if(strcmp(szField, "level")==0)
					{
						if(strcmp(szOpt, "<")==0)
						{
							if(!( pMember->GetLev() < nData ))
								return false;
						}
						else if(strcmp(szOpt, ">")==0)
						{
							if(!( pMember->GetLev() > nData ))
								return false;
						}
						else if(strcmp(szOpt, "==")==0)
						{
							if(!( pMember->GetLev() == nData ))
								return false;
						}
						else
							return false;
					}
					else if(strcmp(szField, "mate")==0)
					{
						if(!( pMember->IsMate(pUser) && pMember->IsAlive() ))
							return false;
					}
					else if(strcmp(szField, "friend")==0)
					{
						if(!( pMember->GetFriend(pUser->GetID()) && pMember->IsAlive() ))
							return false;
					}
					else if(strcmp(szField, "count_near")==0)
					{
						if(!( pMember->GetMapID() == pUser->GetMapID() && pMember->IsAlive() ))
							return false;
					}
					else
						return false;
				}
			}
			return true;
		}
		break;
	case ACTION_TEAM_LEAVESPACE:
		{
			int		nSpace, nWeight;
			int		nPackType = ITEMPOSITION_BACKPACK;
			if(sscanf(szParam, "%d %d %d", &nSpace, &nWeight, &nPackType) != 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(pMember && pMember->GetID() != pUser->GetID())
				{
					if(!( pMember->IsBackPackSpare(nSpace, nWeight, ID_NONE, nPackType)))
						return false;
				}
			}
			return true;
		}
		break;
	case ACTION_TEAM_ITEM_ADD:
		{
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(pMember && pMember->GetID() != pUser->GetID())
				{
//					CItem* pItem = pMember->GetTaskItemByType(pAction->GetInt(ACTIONDATA_DATA));
//					if(pItem && pItem->GetInt(ITEMDATA_WEIGHT_) + pMember->GetWeight() <= pMember->GetWeightLimit())
					pMember->AwardItem(pAction->GetInt(ACTIONDATA_DATA), SYNCHRO_TRUE);
				}
			}
			return true;
		}
		break;
	case ACTION_TEAM_ITEM_DEL:
		{
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(pMember && pMember->GetID() != pUser->GetID())
				{
					CItem* pItem = pMember->GetTaskItemByType(pAction->GetInt(ACTIONDATA_DATA));
					if(pItem)
					{
						pMember->EraseItem(pItem->GetID(), SYNCHRO_TRUE);
					}
					else
					{
						LOGWARNING("ACITON %d: �޷�ɾ��ָ��������Ʒ[%d]", pAction->GetID(), pAction->GetInt(ACTIONDATA_DATA));
					}
				}
			}
			return true;
		}
		break;
	case ACTION_TEAM_ITEM_CHECK:
		{
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			for(int i = 0; i < pTeam->GetMemberAmount(); i++)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(pMember && pMember->GetID() != pUser->GetID())
				{
					if(!( pMember->GetItemByType(pAction->GetInt(ACTIONDATA_DATA)) ))
						return false;
				}
			}
			return true;
		}
		break;
	case ACTION_TEAM_CHGMAP:
		{
			CTeam* pTeam = pUser->GetTeam();
			if(!pTeam || pUser->GetID() != pTeam->GetLeader() || pTeam->GetMemberAmount() <= 1)
				return false;

			OBJID	idMap;
			int		nPosX, nPosY;
			if (sscanf(szParam, "%u %d %d", &idMap, &nPosX, &nPosY) < 3)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}

			for(int i = pTeam->GetMemberAmount()-1; i >= 0; i--)
			{
				CUser* pMember = pUser->FindAroundUser(pTeam->GetMemberByIndex(i));
				if(pMember && pMember->GetID() != pUser->GetID() && pMember->IsAlive())
				{
					pMember->FlyMap(idMap, nPosX, nPosY);
					pMember->Synchro();
				}
			}

			ASSERT(pUser->FlyMap(idMap, nPosX, nPosY) == FLYMAP_NORMAL);	// no FLYMAP_MAPGROUP
			return true;
		}
		break;
	case ACTION_TEAM_CHK_ISLEADER:	
		{
			CTeam* pTeam = pUser->GetTeam();
			if (pTeam && pTeam->GetLeader() == pUser->GetID())
				return true;
		}
		break;

	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionEvent(CActionData* pAction, LPCTSTR szParam, CUser* pUser_NoUse, IRole* pRole_NoUse, CItem* pItem_NoUse, LPCTSTR pszAccept)
{
	CHECKF(pAction);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case ACTION_EVENT_DELNPC_GENID:
		{
			OBJID	idGen = pAction->GetInt(ACTIONDATA_DATA);
			for(IRoleSet::Iter i = RoleManager()->QuerySet()->Begin(); i != RoleManager()->QuerySet()->End(); )		// ɾ��
			{
				IRole* pRole = RoleManager()->QuerySet()->GetObjByIter(i);
				i++;		//??? ��ǰ�ƶ���������ܻ�ɾ����ǰ��ɫ
				CAiNpc* pMonster;
				if(pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)) && pMonster->GetGenID() == idGen)
				{
					if(!pMonster->IsDeleted())
						pMonster->DelMonster(DEL_NOW);
				}
			}
			
			return true;
		}
		break;
		
	case	ACTION_EVENT_SETSTATUS:
		{
			OBJID	idMap;
			int		nStatus;
			int		nFlag;
			if (3 == sscanf(szParam, "%u %d %d", &idMap, &nStatus, &nFlag))
			{
				CGameMap* pMap = MapManager()->QueryMap(idMap);
				if (pMap)
				{
					pMap->SetStatus(nStatus, nFlag != 0);					
					return true;
				}
			}
			else
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;

	case ACTION_EVENT_COMPARE:
		{
			int			data1, data2;
			PARAMBUF	opt;
			if (3 != sscanf(szParam, "%d %s %d", &data1, opt, &data2))
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				return false;
			}
			
			if (strcmp(opt, "==") == 0)
			{
				if(data1 == data2)
					return true;
			}
			else if (strcmp(opt, "<") == 0)
			{
				if(data1 < data2)
					return true;
			}

			if (strcmp(opt, "<=") == 0)
			{
				if(data1 <= data2)
					return true;
			}
		}
		break;
	case ACTION_EVENT_COMPARE_UNSIGNED:
		{
				DWORD		data1, data2;
				PARAMBUF	opt;
				if (3 != sscanf(szParam, "%u %s %u", &data1, opt, &data2))
				{
					LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
					return false;
				}

				if (strcmp(opt, "==") == 0)
				{
					if(data1 == data2)
						return true;
				}
				else if (strcmp(opt, "<") == 0)
				{
					if(data1 < data2)
						return true;
				}
				if (strcmp(opt, "<=") == 0)
				{
					if(data1 <= data2)
						return true;
				}
		}
		break;
	case ACTION_EVENT_CHANGEWEATHER:
		{
				OBJID	idMap, idRegion;
				int		nType, nIntensity, nDir, nColor, nKeepSecs;
				if (7 == sscanf(szParam, "%u %u %d %d %d %d %d", &idMap, &idRegion, &nType, &nIntensity, &nDir, &nColor, &nKeepSecs))
				{
					CGameMap* pMap = MapManager()->QueryMap(idMap);
					if(pMap)
					{
						CWeatherRegion* pRegion = pMap->QueryWeatherRegion(idRegion);
						IF_OK(pRegion)
						{
							return pRegion->QueryWeather()->SetNewWeather(nType, nIntensity, nDir, nColor, nKeepSecs, 10);
						}
					}
				}
				else
					LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
		}
		break;
	case	ACTION_EVENT_CREATEPET:
		{
			OBJID	idOwner, idMap, idGen, idType;
			int		nOwnerType, nPosX, nPosY, nData=0;
			PARAMBUF	szName = "";
			if(sscanf(szParam, "%d %u %u %d %d %u %u %d %s", &nOwnerType, &idOwner, &idMap, &nPosX, &nPosY, &idGen, &idType, &nData, szName) < 7)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			// check syndicate name
			const char* pszName = szName;
			if(pszAccept && strlen(pszAccept) > 0)
			{
				if(strlen(pszAccept) >= _MAX_NAMESIZE || !::NameStrCheck((char*)pszAccept))
				{
					//pUser->SendSysMsg(STR_INVALID_PET_NAME);
					return false;
				}
				pszName = pszAccept;
			}

			ST_CREATENEWNPC	info;
			memset(&info, 0, sizeof(ST_CREATENEWNPC));
//not in this			info.id				= MapManager()->SpawnNewPetID();
			info.idMap			= idMap;
			info.idData			= idGen;
			info.idOwner		= idOwner;
			info.usPosX			= nPosX;
			info.usPosY			= nPosY;
//			info.usAction		= MSGAINPCINFO_CREATENEW;
			info.usType			= idType;
			info.ucOwnerType	= nOwnerType;
			info.nData			= nData;

			if(strlen(pszName) > 0 && strcmp(pszName, ACTIONSTR_NONE) != 0)
				return NpcManager()->CreateSynPet(&info, pszName);
			else
				return NpcManager()->CreateSynPet(&info);
		}
		break;
	case	ACTION_EVENT_CREATENEW_NPC:
		{
			NPCINFO_ST	info;
			memset(&info, 0, sizeof(NPCINFO_ST));

			// check overlap npc
//			void* pTemp;
//			if(pUser->GetMap()->QueryObjInPos(info.nPosX, info.nPosY, OBJ_NPC, IPP_OF(pTemp)))
//				return false;

			NAMESTR	szName;
			ASSERT(_MAX_NPCTASK == 8);
			ASSERT(MAX_NPCDATA == 4);
			IF_NOT_(sscanf(szParam, "%s %d %d %d %d %d ""%d %d %d ""%d %d %d ""%d %d %d %d %d %d %d %d ""%d %d %d %d %s", 
							szName, &info.nType, &info.nSort, &info.nLookFace, &info.nOwnerType, &info.idOwner,
							&info.idMap, &info.nPosX, &info.nPosY,
							&info.nLife, &info.idBase, &info.idLink, 
							&info.setTask[0], &info.setTask[1], &info.setTask[2], &info.setTask[3], 
							&info.setTask[4], &info.setTask[5], &info.setTask[6], &info.setTask[7], 
							&info.setData[0], &info.setData[1], &info.setData[2], &info.setData[3], info.szData) >= 9)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			CNpc* pNpc = CNpc::CreateNew();
			IF_OK(pNpc)
			{
				IF_OK(pNpc->Create(m_idProcess, &info, ID_NONE, szName))
				{
					RoleManager()->QuerySet()->AddObj(pNpc->QueryRole());
					//pNpc->EnterMap();
					return true;
				}
				else
					pNpc->ReleaseByOwner();
			}

			return false;
		}
		break;
	case	ACTION_EVENT_COUNTMONSTER:
		{
			OBJID		idMap;
			PARAMBUF	szField;
			PARAMBUF	szData;
			PARAMBUF	szOpt;
			int			nNum;
			IF_NOT_(sscanf(szParam, "%u %s %s %s %d", &idMap, szField, szData, szOpt, &nNum) == 5)
				return false;

			int nCount = 0;
			if(_stricmp(szField, "name") == 0)
			{
				nCount = RoleManager()->CountMonsterByName(idMap, szData);
			}
			else if(_stricmp(szField, "gen_id") == 0)
			{
				OBJID idGen = atol(szData);
				nCount = RoleManager()->CountMonsterByGenID(idMap, idGen);
			}
			else
				return false;

			if(_stricmp(szOpt, "<") == 0 && nCount < nNum)
				return true;
			else if(_stricmp(szOpt, "==") == 0 && nCount == nNum)
				return true;
			else
				return false;

			return false;
		}
		break;
	case	ACTION_EVENT_DELETEMONSTER:
		{
			OBJID	idMap;
			OBJID	idType;
			int		nData=0;
			PARAMBUF	szName = "";
			if(sscanf(szParam, "%u %u %d %s", &idMap, &idType, &nData, szName) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			bool	ret = false;
			for(IRoleSet::Iter i = RoleManager()->QuerySet()->Begin(); i != RoleManager()->QuerySet()->End(); )		// ɾ��
			{
				IRole* pRole = RoleManager()->QuerySet()->GetObjByIter(i);
				i++;		//??? ��ǰ�ƶ���������ܻ�ɾ����ǰ��ɫ
				CAiNpc* pPet;
				if(pRole && pRole->QueryObj(OBJ_MONSTER, IPP_OF(pPet))
							&& pPet->GetMap()->GetID() == idMap && pPet->GetType() == idType)		// pPet->IsPet() && 
				{
					if(!( nData && pPet->GetData() != nData || strlen(szName) && strcmp(szName, pPet->GetName()) != 0 ))
					{
						if(!pPet->IsDeleted())
						{
							pPet->DelMonster(DEL_NOW);
							ret = true;
						}
					}
				}
			}
			return ret;
		}
		break;
	case ACTION_EVENT_BBS:
		{
			OBJID idUser = ID_NONE;

			CMsgTalk	msg;
			IF_OK(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szParam, NULL, 0xffffff, _TXTATR_MSG_SYSTEM))
				MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(&msg, idUser);
			return true;
		}
		break;
	case	ACTION_EVENT_ERASE:
		{
			OBJID	idMap;
			int		nType;
			PARAMBUF	szName = "";
			if(sscanf(szParam, "%u %d", &idMap, &nType) < 2)
			{
				LOGERROR("ACTION %u: ����Ĳ�������", pAction->GetID());
				break;
			}

			CGameMap* pMap = MapManager()->QueryMap(idMap);
			if(pMap)
			{
				pMap->DelNpcByType(nType);
				return true;
			}
			else
			{
				PROCESS_ID idProcess = MapManager()->GetProcessID(idMap);
				if(idProcess != PROCESS_NONE)
				{
					// rpc
					CEventPack	evt(OBJ_MAP, idMap, RPC_MAP_DELNPC);
					evt << nType;
					MapGroup(PID)->QueryIntraMsg()->SendRpc(evt);
					return true;
				}
			}
		}
		break;
	// TRAP //////////////////////////////////////////////////////////////////////
	/*case	ACTION_TRAP_CREATE:
		{
			TRAP_INFO	info;
			memset(&info, 0, sizeof(TRAP_INFO));
			int			nData;
			IF_NOT_(sscanf(szParam, "%d %d %u %u %d %d %d", &info.usType, &info.usLook, &info.idOwner, &info.idMap, &info.usPosX, &info.usPosY, &nData) == 7)
				return false;

			CMapTrap*	pTarp = CMapTrap::CreateNew(m_idProcess, &info);
			if(pTarp)
			{
				RoleManager()->QuerySet()->AddObj(pTarp->QueryRole());
				return true;
			}
		}
		break;*/

	/*case	ACTION_TRAP_ERASE:
		{
			IRole* pRole = pRole_NoUse;
			CHECKF(pRole);
			CMapTrap* pTrap;
			if(pRole->QueryObj(OBJ_TRAP, IPP_OF(pTrap)))
			{
				pTrap->DelTrap();
				return true;
			}
		}
		break;*/

	/*case	ACTION_TRAP_COUNT:
		{
			OBJID		idMap;
			int			nCount, nType, nPosX, nPosY, nCX, nCY;
			IF_NOT_(sscanf(szParam, "%u %d %d %d %d %d %d ", &idMap, &nPosX, &nPosY, &nCX, &nCY, &nCount, &nType) == 7)
				return false;

			int nNum = 0;
			IRoleSet::Iterator	pRole = RoleManager()->QuerySet()->NewEnum();
			while(pRole.Next())
			{
				CMapTrap* pTrap;
				if(pRole && pRole->QueryObj(OBJ_TRAP, IPP_OF(pTrap)) && pTrap->GetType() == nType)
					nNum++;
			}

			return nNum < nCount;
		}
		break;*/

	/*case	ACTION_TRAP_ATTR:
		{
			OBJID		id;
			PARAMBUF	szField;
			PARAMBUF	szOpt;
			int			nData;
			IF_NOT_(sscanf(szParam, "%d %s %s %d ", &id, szField, &szOpt, &nData) == 4)
				return false;

			IRole* pRole = RoleManager()->QueryRole(id);
			CMapTrap* pTrap;
			CHECKF(pRole && pRole->QueryObj(OBJ_TRAP, IPP_OF(pTrap)));

			if(strcmp(szField, "type") == 0 && strcmp(szOpt, "=") == 0)
			{
				pTrap->ChangeType(nData);
				return true;
			}
			else if(strcmp(szField, "look") == 0 && strcmp(szOpt, "=") == 0)
			{
				pTrap->ChangeLook(nData);
				return true;
			}
		}
		break;*/

	default:
		LOGERROR("��֧�ֵ�ACTION[%u]����[%u]", pAction->GetKey(), pAction->GetInt(ACTIONDATA_TYPE));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionWanted(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pszAccept)
{
	CHECKF(pAction && pUser);

	/*switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_POLICEWANTED_CHECK:
		{
			if (PoliceWanted().GetWanted(pUser->GetID()) != NULL)
				return true;
		}
		break;

	case	ACTION_POLICEWANTED_NEXT:
		{
			++pUser->TaskIterator();

			if (PoliceWanted().GetWantedByIndex(pUser->TaskIterator()) != NULL)
				return true;
		}
		break;

	case	ACTION_POLICEWANTED_ORDER:
		{
			if (pszAccept)
			{
				int idx = atoi(pszAccept);
				PoliceWantedStruct* pInfo = PoliceWanted().GetWantedByIndex(idx);
				if (pInfo)
				{
					{	// inform client
						CMsgName msg;
						IF_OK (msg.Create(NAMEACT_POLICEWANTED, pInfo->strName.c_str()))
							pUser->SendMsg(&msg);
					}

					CUser* pTarget = UserManager()->GetUser(pInfo->idUser);
					if (pTarget)
					{
						pUser->PoliceWantedID() = pInfo->idUser;
						pUser->SendSysMsg(_TXTATR_NORMAL, STR_POLICE_WANTED_ORDER, pInfo->strName.c_str(), pUser->GetMap()->GetName());
						return true;
					}
				}
				else
					pUser->SendSysMsg(STR_INVALID_WANTED);
			}
		}
		break;

	case	ACTION_WANTED_MODIFYID:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				OBJID id = atoi(pszAccept);
				if (id != ID_NONE)
				{
					if (CWantedList::s_WantedList.GetWanted(id))
					{
						pUser->WantedInfo().idModifyWanted = id;
						return true;
					}
					else
						pUser->SendSysMsg(STR_INVALID_WANTED);
				}
			}
		}
		break;

	case	ACTION_WANTED_SUPERADD:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				CWantedData* pData = CWantedList::s_WantedList.GetWanted(pUser->WantedInfo().idModifyWanted);
				if (pData)
				{
					int nAddBonuty = atoi(pszAccept);
					if (nAddBonuty >= _MIN_ADDBONUTY)
					{
						if (pData->GetInt(DATA_BOUNTY)+nAddBonuty > _MAX_BONUTY)
						{
							pUser->SendSysMsg(STR_MAX_BONUTY, _MAX_BONUTY);
							return false;
						}
						else
						{
							if (pUser->SpendMoney(nAddBonuty, true))
							{
								int nNewBonuty = pData->GetInt(DATA_BOUNTY)+nAddBonuty;
								pData->SetInt(DATA_BOUNTY, nNewBonuty);
								pData->Update();

								pUser->SendSysMsg(STR_SUPERADD_BONUTY, pUser->WantedInfo().idModifyWanted, nNewBonuty);
								return true;
							}
							else
								pUser->SendSysMsg(STR_NOT_ENOUGH_MONEY, nAddBonuty);
						}
					}
					else
						pUser->SendSysMsg(STR_LOWEST_SUPERADD_BONUTY, _MIN_ADDBONUTY);
				}
				else
					pUser->SendSysMsg(STR_INVALID_WANTED);
			}
		}
		break;

	case	ACTION_WANTED_CANCEL:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				OBJID id = atoi(pszAccept);
				if (id != ID_NONE)
				{
					CWantedData* pData = CWantedList::s_WantedList.GetWanted(id);
					if (pData)
					{
						if (pUser->SpendMoney(pData->GetInt(DATA_BOUNTY)*2, true))
						{
							CWantedList::s_WantedList.DelWanted(id);

							pUser->SendSysMsg(STR_CANCEL_WANTED, id);
							return true;
						}
						else
							pUser->SendSysMsg(STR_NOT_ENOUGH_MONEY, pData->GetInt(DATA_BOUNTY)*2);
					}
					else
						pUser->SendSysMsg(STR_INVALID_WANTED);
				}
			}
		}
		break;

	case	ACTION_WANTED_ORDER:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				OBJID id = atoi(pszAccept);
				if (id != ID_NONE)
				{
					CWantedData* pData = CWantedList::s_WantedList.GetWanted(id);
					if (pData)
					{
						if (pUser->SpendMoney(_WANTED_ORDERCOST, true))
						{
							pUser->WantedInfo().idWanted = id;
							
							{	// inform client
								CMsgName msg;
								IF_OK (msg.Create(NAMEACT_WANTED, pData->GetStr(DATA_TARGET_NAME)))
									pUser->SendMsg(&msg);
							}

							{
								char szMsg[1024] = "";
								sprintf(szMsg, STR_WANTED_ORDER, _WANTED_ORDERCOST, id, pData->GetStr(DATA_TARGET_NAME), pData->GetInt(DATA_BOUNTY));

								CMsgTalk msg;
								if (msg.Create(SYSTEM_NAME, pUser->GetName(), szMsg, NULL, 0x00ff0000, _TXTATR_NORMAL))
									pUser->SendMsg(&msg);
							}

							CUser* pTarget = UserManager()->GetUser(pData->GetStr(DATA_TARGET_NAME));
							if (pTarget)
							{
								CGameMap* pMap = pTarget->GetMap();
								if (pMap)
								{
									char szMsg[1024] = "";
									sprintf(szMsg, STR_WANTED_INFO, pMap->GetName());

									CMsgTalk msg;
									if (msg.Create(SYSTEM_NAME, pUser->GetName(), szMsg, NULL, 0x00ff0000, _TXTATR_NORMAL))
										pUser->SendMsg(&msg);
								}
							}

							return true;
						}
						else
							pUser->SendSysMsg(STR_NOT_ENOUGH_MONEY, _WANTED_ORDERCOST);
					}
					else
						pUser->SendSysMsg(STR_INVALID_WANTED);
				}
			}
		}
		break;

	case	ACTION_WANTED_NEXT:
		{
			++pUser->TaskIterator();

			if (CWantedList::s_WantedList.GetWantedByIndex(pUser->TaskIterator()) != NULL)
				return true;
		}
		break;

	case	ACTION_WANTED_NAME:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				::SafeCopy(pUser->WantedInfo().szName, pszAccept, _MAX_NAMESIZE);
				return true;
			}
		}
		break;
	
	case	ACTION_WANTED_BONUTY:
		{
			if (pszAccept && strlen(pszAccept) > 0 && pUser)
			{
				int nBonuty = atoi(pszAccept);
				if (nBonuty > _MAX_BONUTY)
				{
					pUser->SendSysMsg(STR_MAX_BONUTY, _MAX_BONUTY);
					return false;
				}
				else
				{
					pUser->WantedInfo().nBonuty = nBonuty;
					return true;
				}
			}
		}
		break;

	case	ACTION_WANTED_NEW:
		{
			if (pUser->WantedInfo().nBonuty >= _MIN_BONUTY)
			{
				if (pUser->SpendMoney(pUser->WantedInfo().nBonuty, SYNCHRO_TRUE))
				{
					if (CWantedList::s_WantedList.AddWanted(pUser->WantedInfo().szName, pUser->GetName(), pUser->WantedInfo().nBonuty))
						return true;
				}
				else
					pUser->SendSysMsg(STR_NOT_ENOUGH_MONEY, pUser->WantedInfo().nBonuty);
			}
			else
				pUser->SendSysMsg(STR_MIN_BONUTY, _MIN_BONUTY);
		}
		break;

	default:
		break;
	}*/

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CGameAction::ProcessActionMagic(CActionData* pAction, LPCTSTR szParam, CUser* pUser, IRole* pRole, CItem* pItem, LPCTSTR pazAccept)
{
	CHECKF(pAction && pUser);

	switch(pAction->GetInt(ACTIONDATA_TYPE))
	{
	case	ACTION_MAGIC_ATTACHSTATUS:
		{
			if (!pRole)
				pRole	= pUser->QueryRole();
//			if (pRole)
			{
				int nStatus, nPower, nSecs, nTimes = 0;
				if (4 != sscanf(szParam, "%d %d %d %d", &nStatus, &nPower, &nSecs, &nTimes))
					return false;

				if (CRole::AttachStatus(pRole, nStatus, nPower, nSecs, nTimes))
					return true;
			}
		}
		break;
	case	ACTION_MAGIC_ATTACK:
		{
			if (!pRole)
				pRole	= pUser->QueryRole();

			int nType = pAction->GetInt(ACTIONDATA_DATA);
			int nLevel = 0;
			sscanf(szParam, "%u", &nLevel);
			// magic attack
			CMagicTypeData* pMagicData = CMagic::FindMagicType(nType, nLevel);
			if (pMagicData)
			{
				switch (pMagicData->GetInt(MAGICTYPEDATA_SORT))
				{
				case MAGICSORT_DETACHSTATUS:
					{
						int nPower	= 0;		//��״̬ GetPower();
						int nSecs	= pMagicData->GetInt(MAGICTYPEDATA_STEP);
						int	nTimes	= pMagicData->GetInt(MAGICTYPEDATA_TIMES);
						int nStatus	= pMagicData->GetInt(MAGICTYPEDATA_STATUS);
						ASSERT(nPower == 0);

						if (!pRole->IsAlive())
						{
							if (STATUS_DIE != nStatus)
								return false;
							void* pTemp;
							if (!pRole->QueryObj(OBJ_USER, IPP_OF(pTemp)))
								return false;
						}
						// pk field will disable reborn magic
						if (STATUS_DIE == nStatus)
						{
							CGameMap* pMap = pUser->GetMap();
							if (pMap && pMap->IsPkField())
								return false;		
						}

						if(nStatus == STATUS_DETACH_ALL)
						{
							CRole::DetachAllStatus(pRole);
						}
						else if(nStatus == STATUS_DETACH_BADLY)
						{
							CRole::DetachBadlyStatus(pRole);
						}
						else
						{
							IStatus* pStatus = pRole->QueryStatus(nStatus);
							if(pStatus)
								pStatus->ChangeData(nPower, nSecs, nTimes);
						}

						// �㲥����Ч��
						CMsgMagicEffect	msg;
						IF_OK(msg.Create(pUser->GetID(), pMagicData->GetInt(MAGICTYPEDATA_TYPE), pMagicData->GetInt(MAGICTYPEDATA_LEVEL), pRole->GetID(), nStatus, pUser->GetDir()))
							pUser->BroadcastRoomMsg(&msg, INCLUDE_SELF);

						if (pMagicData->GetInt(MAGICTYPEDATA_CRIME))
							pUser->CheckCrime(pRole);

						pRole->ClsStatus(nStatus, SYNCHRO_TRUE);

						if (STATUS_DIE == nStatus)
						{	// reborn
							CUser* pTarget = NULL;
							pRole->QueryObj(OBJ_USER, IPP_OF(pTarget));
							if (pTarget)
							{
								bool bChgPos = false;
								pTarget->Reborn(bChgPos);
							}
						}
						return true;
					}
					break;
				case MAGICSORT_STEAL:
					{
						if(!pRole || !pRole->IsAlive())
							return false;

						CUser* pTargetUser = NULL;
						if (!pRole->QueryObj(OBJ_USER, IPP_OF(pTargetUser)))
							return false;

						int	nPower = pMagicData->GetInt(MAGICTYPEDATA_POWER);

						// �㲥����Ч��
						CMsgMagicEffect	msg;
						IF_OK(msg.Create(pUser->GetID(), pMagicData->GetInt(MAGICTYPEDATA_TYPE), pMagicData->GetInt(MAGICTYPEDATA_LEVEL), pRole->GetID(), nPower, pUser->GetDir()))
							pUser->BroadcastRoomMsg(&msg, INCLUDE_SELF);

						if (pMagicData->GetInt(MAGICTYPEDATA_CRIME))
							pUser->CheckCrime(pRole);
						
						if (nPower)
						{
							CItem* pItem = nullptr; // pTargetUser->GetItemByType(GHOST_GEM_AVOID_STEAL);
							if (pItem)
							{
								//pTargetUser->SendSysMsg(STR_AUTO_USE_ANTISTEAL, pItem->GetStr(ITEMDATA_NAME));
								//pTargetUser->SendSysMsg(STR_AVOID_STEAL, m_pUser->GetName());
								//pTargetUser->EraseItem(pItem->GetID(), true);
							}
							else
							{
								IUserPackage* pPackage = pTargetUser->QueryPackage();
								if (pPackage)
								{
									int nStealNum = __min(nPower, pPackage->GetAmount());
									for (int i=0; i<nStealNum; i++)
									{
										OBJID idItem = pPackage->RandGetItem();
										CItem* pItem = pTargetUser->PopItem(idItem, true, true);
										if (pItem)
										{
											pTargetUser->SendSysMsg(STR_STOLEN, m_pUser->GetName(), pItem->GetStr(ITEMDATA_NAME));
											if (!pUser->AddItem(pItem, true))
											{
												pItem->DeleteRecord();
												pItem->ReleaseByOwner();
											}
										}
									}
								}
							}
						}
						return true;
					}
					break;
				default:
					{
						::LogSave("Unsupported item magic type [%d]", nType);
					}
					break;
				}
			}
			else
			{
				::LogSave("Invalid action param: Can not find magic type [%d]", nType);
			}
		}
		break;
	default:
		break;
	}

	return false;
}
