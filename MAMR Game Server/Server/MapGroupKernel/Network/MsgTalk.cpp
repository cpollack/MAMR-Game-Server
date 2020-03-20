// MsgTalk.cpp: implementation of the CMsgTalk class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#ifdef	WORLD_KERNEL
#include "userlist.h"
#else
#pragma warning(disable:4786)
#include "../mapgroup.h"
#endif

#include "../user.h"

using namespace mapgroup_kernel;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgTalk::CMsgTalk()
{
	Init();
	m_pInfo	=(MSG_Info* )m_bufMsg;

	m_StrPacker.SetBuf(m_pInfo->szBuf, _MAX_MSGSIZE-sizeof(MSG_Info)+1);
}

CMsgTalk::~CMsgTalk()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgTalk::Create(LPCTSTR pszSpeaker, LPCTSTR pszHearer, LPCTSTR pszWords, 
					  LPCTSTR pszEmotion, DWORD dwColor, unsigned short unAttribute, 
					  unsigned short unStyle)
{
	if(!pszSpeaker || strlen(pszSpeaker) >= _MAX_NAMESIZE)
		return false;

	if(!pszHearer || strlen(pszHearer) >= _MAX_NAMESIZE)
		return false;

	if(!pszWords || strlen(pszWords) >= _MAX_WORDSSIZE)
		return false;

	// can be null
	if(pszEmotion && strlen(pszEmotion) >= _MAX_NAMESIZE)	
		return false;

	// fill
	this->Init();

	// fill structure
	m_pInfo->dwWordsColor	=dwColor;
	m_pInfo->unTxtAttribute	=unAttribute;
	m_pInfo->unTxtStyle		=unStyle;
	m_pInfo->dwTime			=::SysTimeGet();


	BOOL bSucMake	=true;
	bSucMake	&=m_StrPacker.AddString(pszSpeaker);
	bSucMake	&=m_StrPacker.AddString(pszHearer);
	bSucMake	&=m_StrPacker.AddString(pszEmotion);
	bSucMake	&=m_StrPacker.AddString(pszWords);

	m_unMsgType	=_MSG_TALK;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();

	return bSucMake;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgTalk::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgTalk::Process(void *pInfo)
{

#ifdef _MSGDEBUG
	::LogMsg("Process MsgTalk, Sender:%s, Receiver:%s, Words:%s", 
						szSender, 
						szReceiver, 
						szWords);
#endif

	char szSender[_MAX_NAMESIZE];
	char szReceiver[_MAX_NAMESIZE];
	char szEmotion[_MAX_NAMESIZE];
	char szWords[_MAX_WORDSSIZE];

	m_StrPacker.GetString(0, szSender, sizeof(szSender));
	m_StrPacker.GetString(1, szReceiver, sizeof(szReceiver));
	m_StrPacker.GetString(2, szEmotion, sizeof(szEmotion));
	m_StrPacker.GetString(3, szWords, sizeof(szWords));

	CHECK(strlen(szWords) <= 255);

	IRole* pRole = RoleManager()->QueryRole(this);
	if(!pRole)
	{
		if(IsNpcMsg())
			return;

		// TransmitMsg
		switch(m_pInfo->unTxtAttribute)
		{
		case	_TXTATR_SYNDICATE:
			{
				OBJID idSyn = m_pInfo->idTransmit;
				CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
				if (pSyn)
				{
					pSyn->BroadcastSynMsg(this, NULL);
				}
			}
			break;
		}

		return;
	}
	CUser* pUser = NULL;
	pRole->QueryObj(OBJ_USER, IPP_OF(pUser));		//? pUser may be null
	if(pUser && strcmp(pUser->GetName(), szSender) != 0)
	{
		if (!pUser->IsGM())
		{
			::GmLogSave("���[%s]��ͼð����������[%s]����Talk��Ϣ�������š�", pUser->GetName(), szSender);
			return ;
		}
	}

	if(!pRole->IsTalkEnable())
	{
		pRole->SendSysMsg(STR_CAN_NOT_TALK);
		return;
	}

	if(pUser && pUser->IsGM())
	{
		::GmLogSave("-TALK %s->%s: %s", szSender, szReceiver, szWords);
	}

	if(pUser && szWords[0] == '/')
	{
		char	szCmd[_MAX_WORDSSIZE]	= "NO_CMD";
		char	szParam[_MAX_WORDSSIZE] = "";
		DEBUG_TRY	// VVVVVVVVVVVVVVVVVVVVVVVVV
		sscanf(szWords+1, "%s %s", szCmd, szParam);
		if(_stricmp(szCmd, "pro") == 0)
		{
			if(pUser->IsPM())
			{
				int	nData = atoi(szParam);
				pUser->SetAttrib(_USERATTRIB_PORFESSION, nData, SYNCHRO_TRUE);
			}
		}
		else if (_stricmp(szCmd, "���") == 0)
		{
			if(pUser->IsGM())
			{
				CMsgItem msg;
				IF_OK (msg.Create(pUser->GetID(), ITEMACT_FIREWORKS))
					pUser->BroadcastRoomMsg(&msg, true);
			}
		}
		else if (_stricmp(szCmd, "���2") == 0)
		{
			if(pUser->IsGM())
			{
				int nLen = strlen(szParam);
				if (nLen > 0 && nLen < 9)
				{
					CMsgName msg;
					IF_OK (msg.Create(NAMEACT_FIREWORKS, szParam))
						pUser->BroadcastRoomMsg(&msg, true);
				}
			}
		}
		else if (_stricmp(szCmd, "kickoutcheat") == 0)
		{
			if(pUser->IsPM())
			{
				int	nData = 0;
				if (2 == sscanf(szWords+1, "%s %d", szCmd, &nData))
				{
					extern long	g_sKickoutCheat;
					long nOld = InterlockedExchange(&g_sKickoutCheat, nData);
					pUser->SendSysMsg("set kickoutcheat OK! old value is %d", nOld);
				}
			}
		}
#ifdef _DEBUG
		else if (_stricmp(szCmd, "recover") == 0)
		{
			int	nData = 0;
			if (2 == sscanf(szWords+1, "%s %d", szCmd, &nData))
			{
				pUser->RecoverEquipmentDur(nData);
			}
		}
		/*else if (_stricmp(szCmd, "weaponexp") == 0)
		{
			int	nData = 0, nWeapon = 0;
			if (3 == sscanf(szWords+1, "%s %d %d", szCmd, &nWeapon, &nData))
			{
				pUser->AddWeaponSkillExp(nWeapon, nData);
			}
		}*/
		else if (_stricmp(szCmd, "itemquality") == 0)
		{
			int	nData = atoi(szParam);
			pUser->UpEquipmentQuality(nData);
		}
		else if (_stricmp(szCmd, "itemlev") == 0)
		{
			int	nData = atoi(szParam);
			pUser->UpEquipmentLevel(nData);
		}
		else if (_stricmp(szCmd, "divoice") == 0)
		{
			pUser->Divorce();
		}
/*
		else if (stricmp(szCmd, "resetlev") == 0)
		{
			int nForce = 5, nDex = 2, nHealth = 3, nSoul = 0;

			int nPro = pUser->GetProfessionSort();
			if (nPro == 1)
				pUser->SetAttrib(_USERATTRIB_PORFESSION, 10, SYNCHRO_TRUE);
			else if (nPro == 2)
				pUser->SetAttrib(_USERATTRIB_PORFESSION, 20, SYNCHRO_TRUE);
			else if (nPro >= 10 && nPro < 20)
			{
				pUser->SetAttrib(_USERATTRIB_PORFESSION, 100, SYNCHRO_TRUE);

				nForce	= 0;
				nDex	= 2;
				nHealth = 3;
				nSoul	= 5;
			}

			pUser->SetAttrib(_USERATTRIB_FORCE, nForce, SYNCHRO_TRUE);
			pUser->SetAttrib(_USERATTRIB_SOUL, nSoul, SYNCHRO_TRUE);
			pUser->SetAttrib(_USERATTRIB_HEALTH, nHealth, SYNCHRO_TRUE);
			pUser->SetAttrib(_USERATTRIB_DEX, nDex, SYNCHRO_TRUE);

			pUser->SetAttrib(_USERATTRIB_LEV, 1, SYNCHRO_TRUE);
		}
*/
		else if (_stricmp(szCmd, "rename") == 0)
		{
			pUser->SetName(szParam);
			pUser->SendSysMsg("�����Ѿ�����Ϊ%s��", szParam);
		}
		else if(_stricmp(szCmd, "pk") == 0)
		{
			int nData = 0;
			if (2 == sscanf(szWords+1, "%s %d", szCmd, &nData))
			{
				int nDeltaPk = nData - pUser->GetPk();
				pUser->AddPk(nDeltaPk);
			}
		}
		else if(_stricmp(szCmd, "addpoint") == 0)
		{
			int nData = 0;
			if (2 == sscanf(szWords+1, "%s %d", szCmd, &nData))
			{
				pUser->SetAttrib(_USERATTRIB_ADDPOINT, nData, SYNCHRO_TRUE);
			}
		}
		else if(_stricmp(szCmd, "testmonster") == 0)
		{
			DWORD dwType = 0, dwAmount = 0;
			if (3 == sscanf(szWords+1, "%s %u %u", szCmd, &dwType, &dwAmount))
			{
				CNpcType* pType = NpcType()->GetObj(dwType);
				if (pType)
				{
					for (int j=0; j<dwAmount; j++)
					{
						ST_CREATENEWNPC info;
						memset(&info, 0L, sizeof(info));

						info.id		= MONSTERID_FIRST+j;
						info.idMap	= 1002;
						
						CAiNpc* pMonster = CAiNpc::CreateNew();
						if (pMonster->Create(m_idProcess, pType, &info))
						{
							pMonster->BeKill(pUser->QueryRole());
						}
						
						pMonster->ReleaseByOwner();
					}
				}
			}
		}
#endif
		else if(_stricmp(szCmd, "sp") == 0)
		{
			if(pUser->IsPM())
			{
				int	nData = atoi(szParam);
				pUser->SetAttrib(_USERATTRIB_ENERGY, nData, SYNCHRO_TRUE);
			}
		}
		else if(_stricmp(szCmd, "awardmoney") == 0)
		{
			if(pUser->IsPM())
			{
				int	nMoney = atoi(szParam);
				if(pUser->GainMoney(nMoney, SYNCHRO_TRUE))
					pUser->SendSysMsg("[����Ǯ�����ˡ�]");
			}
		}
		else if(_stricmp(szCmd, "awarditem") == 0)
		{
			if(pUser->IsPM())
			{
				int	nItemType = atoi(szParam);
				if(pUser->AwardItem(nItemType, SYNCHRO_TRUE, CUser::IDENT_OK))
					pUser->SendSysMsg("[������Ʒ�����ˡ�]");
			}
		}
		else if(_stricmp(szCmd, "kickout") == 0)
		{
			if(pUser->IsGM())
			{
				CUserPtr pTarget = UserManager()->GetUser(szParam);
				if (pTarget)
				{
					UserManager()->KickOutSocket(pTarget->GetSocketID(), "GM /kickout");
				}
			}
		}
		else if(_stricmp(szCmd, "kickoutall") == 0)
		{
			if(pUser->IsGM())
			{
				LOGMSG("kickoutall process!");
				pUser->SendSysMsg(STR_KICKOUT_ALL);
				MapGroup(PID)->QueryIntraMsg()->PrintText("Server stop by GM, close server please!");
				MapGroup(PID)->QueryIntraMsg()->CloseMapGroup(GetSocketID());
			}
		}
		else if(_stricmp(szCmd, "find") == 0)
		{
			if(pUser->IsGM())
			{
				CUserPtr pTarget = UserManager()->GetUser(szParam);
				if (pTarget)
				{
					int nPosX = pTarget->GetPosX();
					int nPosY = pTarget->GetPosY();

					pUser->FlyMap(pTarget->GetMapID(), nPosX, nPosY);
				}
			}
		}
		else if(_stricmp(szCmd, "uplev") == 0)
		{
			if (pUser->IsPM())
			{
				int	nLev = atoi(szParam);
				if (nLev > 0)
				{
					pUser->IncLev(nLev);
//					pUser->AddAttrib(_USERATTRIB_ADDPOINT, nLev*_ADDITIONALPOINT_NUM, SYNCHRO_TRUE);
					pUser->AllotPoint();

					CMsgAction msg;
					if (msg.Create(pUser->GetID(), 0, 0, 0, actionUplev, 0, 0))
						pUser->BroadcastRoomMsg(&msg, INCLUDE_SELF);

					pUser->AddAttrib(_USERATTRIB_LEV, 0, SYNCHRO_TRUE);
				}
			}
		}
		else if(_stricmp(szCmd, "life") == 0)
		{
			if (pUser->IsGM())
			{
				int nData = pUser->GetMaxLife();
				int nLife = 0;
				sscanf(szWords+1, "%s %d", szCmd, &nLife);
				if(nLife)
					nData = nLife;
				pUser->SetAttrib(_USERATTRIB_LIFE, nData, SYNCHRO_TRUE);
			}
		}
		else if(_stricmp(szCmd, "mana") == 0)
		{
			if (pUser->IsGM())
			{
				int nData = pUser->GetMaxMana();
				pUser->SetAttrib(_USERATTRIB_MANA, nData, SYNCHRO_TRUE);
			}
		}
		else if(_stricmp(szCmd, "mapdata") == 0)
		{
			if (pUser->IsGM())
			{
				int x = 0, y = 0;
				if (3 == sscanf(szWords+1, "%s %d %d", szCmd, &x, &y))
				{
					int	nAttr=-1, nMask=-1, nAlt=-1, nAlt2=-1, nCount=999;
					if(pUser->GetMap()->GetDebugData(&nAttr, &nMask, &nAlt, &nAlt2, &nCount, x, y))
						pUser->SendSysMsg("ATTR: %d, MASK: %d, ALT: %d, ALT2: %d, COUNT: %d", nAttr, nMask, nAlt, nAlt2, nCount);
				}
			}
		}
		else if(_stricmp(szCmd, "showaction") == 0)
		{
			if (pUser->IsGM())
			{
				if(pUser->DebugShowAction())
					pUser->SendSysMsg("������ʾACTION�ˡ�");
				else
					pUser->SendSysMsg("����ʾACTION�ˡ�");
			}
		}
		else if(_stricmp(szCmd, "fullxp") == 0)
		{
			if (pUser->IsGM())
			{
				pUser->SetXp(100);
			}
		}
		else if(_stricmp(szCmd, "xp") == 0)
		{
			if (pUser->IsPM())
			{
				int nData = 0;
				if (2 == sscanf(szWords+1, "%s %d", szCmd, &nData))
				{
					pUser->SetXp(__min(100, nData));
				}
				else
					pUser->SetXp(100);
			}
		}
		/*else if(stricmp(szCmd, "awardwskill") == 0)
		{
			if (pUser->IsPM())
			{
				int nSkillType = 0, nLev = 0;
				if (3 == sscanf(szWords+1, "%s %d %d", szCmd, &nSkillType, &nLev))
				{
					pUser->AwardWeaponSkill(nSkillType, nLev);
				}
			}
		}*/
		else if(_stricmp(szCmd, "awardmagic") == 0)
		{
			if (pUser->IsPM())
			{
				int nSkillType = 0, nLev = 0;
				bool bSave = true;
				if (3 <= sscanf(szWords+1, "%s %d %d %d", szCmd, &nSkillType, &nLev, &bSave))
				{
					
					pUser->QueryMagic()->LearnMagic(nSkillType, nLev, bSave);
					for (int i=0; i<nLev; i++)
						pUser->QueryMagic()->UpLevelByTask(nSkillType);
				}
			}
		}
		else if(_stricmp(szCmd, "superman") == 0)
		{
			if (pUser->IsPM())
			{
				pUser->AddAttrib(_USERATTRIB_SOUL, 500, SYNCHRO_TRUE);
				//pUser->AddAttrib(_USERATTRIB_HEALTH, 500, SYNCHRO_TRUE);
				pUser->AddAttrib(_USERATTRIB_FORCE, 500, SYNCHRO_TRUE);
				//pUser->AddAttrib(_USERATTRIB_DEX, 500, SYNCHRO_TRUE);
			}
		}
		else if(_stricmp(szCmd, "pos") == 0)
		{
			pUser->SendSysMsg("(%3d, %3d)", pUser->GetPosX(), pUser->GetPosY());
		}		
		else if (_stricmp(szCmd, "player") == 0)
		{
			if (pUser->GetAccountID() <= 100)
			{
				if(_stricmp(szParam, "all") == 0)
				{
					pUser->SendSysMsg(STR_SHOW_PLAYERS_uu, UserManager()->GetUserAmount(), UserManager()->GetMaxUser());
				}
				else if(_stricmp(szParam, "map") == 0)
				{
					OBJID idMap = pUser->GetMapID();
					pUser->SendSysMsg("total %u player in this map.", UserManager()->GetMapUserAmount(idMap));
				}
			}
		}
		else if (_stricmp(szCmd, "setmaxplayer") == 0)
		{
			if (pUser && pUser->IsPM() && strlen(szParam) > 0)
			{
				int nMaxPlayers = atoi(szParam);
				extern DWORD g_dwMaxPlayer;
				InterlockedExchange((long*)&g_dwMaxPlayer, nMaxPlayers);
				{
					pUser->SendSysMsg(STR_SET_MAX_PLAYERS_u, nMaxPlayers);
				}
			}
		}
		else if (_stricmp(szCmd, "fly") == 0)
		{
			if (pUser && pUser->IsGM())
			{
				MSGBUF	szCmd	= "NO_CMD";
				int nPosX = 0, nPosY = 0;
				if (3 == sscanf(szWords+1, "%s %d %d", szCmd, &nPosX, &nPosY))
				{
					CMapPtr pMap = pUser->GetMap();
					if (pMap)
					{
						if(!pMap->IsStandEnable(nPosX, nPosY))
						{
							pUser->SendSysMsg(STR_CAN_STAND);
							return;
						}

						IMapThing* pMapThing = NULL;

						IThingSet* pSet = pMap->QueryBlock(nPosX, nPosY).QuerySet();
						for(int i = 0; i < pSet->GetAmount(); i++)
						{
							IMapThing* pTheMapThing = pSet->GetObjByIndex(i);
							if (pTheMapThing && 									
									pTheMapThing->GetObjType() == OBJ_NPC &&
										pTheMapThing->GetPosX() == nPosX && pTheMapThing->GetPosY() == nPosY)
							{
								pMapThing = pTheMapThing;
								break;		
							}
						}

						if (!pMapThing)
							pUser->FlyMap(ID_NONE, nPosX, nPosY);
						else
							pUser->SendSysMsg(STR_CAN_STAND);
					}
				}
			}
		}
		else if (_stricmp(szCmd, "chgmap") == 0)
		{
			if (pUser && pUser->IsGM())
			{
				MSGBUF	szCmd	= "NO_CMD";
				OBJID idMap = ID_NONE;
				int nPosX = 0, nPosY = 0;
				if (4 == sscanf(szWords+1, "%s %u %d %d", szCmd, &idMap, &nPosX, &nPosY))
				{
					CMapPtr pMap = MapManager()->QueryMap(idMap);
					if (pMap)
					{
#ifdef	LOCAL_DEBUG
						if(!pMap->IsValidPoint(nPosX, nPosY))
#else
						if(!pMap->IsStandEnable(nPosX, nPosY))
#endif
						{
							pUser->SendSysMsg(STR_CAN_STAND);
							return;
						}
						IMapThing* pMapThing = NULL;

						IThingSet* pSet = pMap->QueryBlock(nPosX, nPosY).QuerySet();
						CHECK(pSet);
						for(int i = 0; i < pSet->GetAmount(); i++)
						{
							IMapThing* pTheMapThing = pSet->GetObjByIndex(i);
							if (pTheMapThing && 									
									pTheMapThing->GetObjType() == OBJ_NPC &&
										pTheMapThing->GetPosX() == nPosX && pTheMapThing->GetPosY() == nPosY)
							{
								pMapThing = pTheMapThing;
								break;		
							}
						}

						if (!pMapThing)
							pUser->FlyMap(idMap, nPosX, nPosY);
						else
							pUser->SendSysMsg(STR_CAN_STAND);
					}
					else
					{
						pUser->FlyMap(idMap, nPosX, nPosY);
					}
				}
			}
		}
		else if (_stricmp(szCmd, "ǧ�ﴫ��") == 0)
		{
			if (pUser->IsGM())
			{
				char szMsg[256] = "";
				if (2 == sscanf(szWords+1, "%s %s", szCmd, szMsg))
				{
					char szBuf[300]	= "";
					sprintf(szBuf, "%s��%s", pUser->GetName(), szMsg);
					UserManager()->BroadcastMsg(szBuf, NULL, NULL, 0xffffff, _TXTATR_GM);
				}
			}
		}
		else if (_stricmp(szCmd, "reloadaction") == 0)
		{
			OBJID idAction=0;
			if (2 == sscanf(szWords+1, "%s %u", szCmd, &idAction))
			{
				if(idAction == ID_NONE)
				{
					if (pUser->IsPM())
					{
						pUser->SendSysMsg(STR_WARNING_CRASH);
						extern IActionSet* g_setAction;
						if(g_setAction)
							g_setAction->Release();
						char	szSQL[1024];
						sprintf(szSQL, "SELECT * FROM %s", _TBL_ACTION);
						g_setAction	= CActionSet::CreateNew(true);
						IF_OK_(g_setAction && g_setAction->Create(szSQL, Database()))
							pUser->SendSysMsg("[ACTION UPDATE��]");
						LOGMSG("��process command: %s��", szCmd);
					}
				}
				else
				{
					if (pUser->IsGM())
					{
						extern IActionSet* g_setAction;
						SQLBUF	szSQL;
						sprintf(szSQL, "SELECT * FROM %s WHERE id=%u LIMIT 1", _TBL_ACTION, idAction);
						CAutoPtr<IRecordset>	pRes = Database()->CreateNewRecordset(szSQL);
						CActionData* pData = CActionData::CreateNew();
						if(pData)
						{
							IF_OK(pData->Create(pRes))
							{
								DEBUG_TRY // VVVVVVVVVVVVVV
								g_setAction->DelObj(pData->GetKey());		// BUG: don't safe in multi thread
								g_setAction->AddObj(pData);
								pUser->SendSysMsg("[AN ACTION UPDATE��]");
								DEBUG_CATCH("reloadaction") // AAAAAAAAAAAAA
							}
							else
								pData->Release();
						}
						LOGMSG("%s process command: %s %d", pUser->GetName(), szCmd, idAction);
					}
				}
			}
		}
		else if (_stricmp(szCmd, "reloadmagictype") == 0)
		{
			if (pUser->IsPM())
			{
				pUser->SendSysMsg(STR_WARNING_CRASH);
				
				extern IMagicTypeSet* g_setMagicType;
				if(g_setMagicType)
					g_setMagicType->Release();
				g_setMagicType	= CMagicTypeSet::CreateNew(true);
				char szSQL[1024];
				sprintf(szSQL, "SELECT * FROM %s", _TBL_MAGIC);
				IF_NOT_(g_setMagicType && g_setMagicType->Create(szSQL, Database()))
					pUser->SendSysMsg("[ERROR: MAGICTYPE UPDATE ERROR]");

				extern IMagicTypeSet* g_setAutoMagicType;
				if(g_setAutoMagicType)
					g_setAutoMagicType->Release();
				g_setAutoMagicType	= CMagicTypeSet::CreateNew(true);
				sprintf(szSQL, "SELECT * FROM %s WHERE auto_learn!=0", _TBL_MAGIC);
				IF_NOT_(g_setAutoMagicType && g_setAutoMagicType->Create(szSQL, Database()))
					pUser->SendSysMsg("[ERROR: MAGICTYPE UPDATE ERROR]");
				CUserManager::Iterator pUser = UserManager()->NewEnum();
				while(pUser.Next())
				{
					if(pUser)
						pUser->QueryMagic()->DebugReloadAll();
				}
				LOGMSG("��process command: %s��", szCmd);
			}
		}
		else if (_stricmp(szCmd, "��ѯ") == 0)
		{
			CUserPtr pTarget = UserManager()->GetUser(szParam);
			if(pTarget)
			{
				OBJID idSyn = pUser->QuerySynAttr()->GetSynID();
				OBJID idTargetSyn = pTarget->QuerySynAttr()->GetSynID();
				if(idSyn != ID_NONE && idTargetSyn == idSyn)
				{
					//pUser->SendSysMsg("���׶ȣ�%d��", pTarget->QuerySynAttr()->GetInt(SYNATTRDATA_PROFFER));
				}
			}
		}
		else if (_stricmp(szCmd, "��Ʒ") == 0)
		{
			if (!pUser->DoBonus())
			{
				pUser->SendSysMsg(STR_NO_BONUS);
			}
		}
		else if (_stricmp(szCmd, "attach") == 0)
		{
			if (pUser->IsPM())
			{
				int nStatus, nPower, nSecs, nTimes;
				if (5 == sscanf(szWords+1, "%s %d %d %d %d", szCmd, &nStatus, &nPower, &nSecs, &nTimes))
				{
					pUser->AttachStatus(pUser->QueryRole(), nStatus, nPower, nSecs, nTimes);
				}
				else
					pUser->SendSysMsg("Invalid arguments.");
			}
		}
		else if (_stricmp(szCmd, "statuslist") == 0)
		{
			if (pUser->IsPM())
			{
				IStatusSet* pStatusSet = pUser->QueryStatusSet();
				if (pStatusSet)
				{
					pUser->SendSysMsg(_TXTATR_NORMAL, "================ Status info =================");
					for (int i=0; i<pStatusSet->GetAmount(); i++)
					{
						IStatus* pStatus = pStatusSet->GetObjByIndex(i);
						if (pStatus)
						{
							StatusInfoStruct info;
							pStatus->GetInfo(&info);
							pUser->SendSysMsg(_TXTATR_NORMAL, "Status=%d, power=%d, remain secs=%d, times=%d",
								info.nStatus, info.nPower, info.nSecs, info.nTimes);
						}
					}
					pUser->SendSysMsg(_TXTATR_NORMAL, "==============================================");
				}
			}
		}
#ifdef	_DEBUG
		/*else if (_stricmp(szCmd, "task_list") == 0)
		{
			pUser->SendSysMsg("===== mercenary task list =====");
			for (int i=0; i<MercenaryTask()->GetTaskAmount(); i++)
			{
				CMercenaryTaskData* pData = MercenaryTask()->QueryTaskDataByIndex(i);
				if (pData)
					pUser->SendSysMsg("[%u] [%s] [%s]", pData->GetID(), pData->GetStr(MTASKDATA_TITLE), pData->GetStr(MTASKDATA_USER_NAME));
			}
			pUser->SendSysMsg("===============================");
		}*/
		/*else if (_stricmp(szCmd, "task_new") == 0)
		{
			if (MercenaryTask()->QueryTaskDataByOwner(pUser->GetID()))
			{
				pUser->SendSysMsg("�����ܷ����������");
			}
			else
			{
				ST_MTASK_DATA	tTaskData;
				memset(&tTaskData, 0L, sizeof(ST_MTASK_DATA));
				if (7 == sscanf(szWords+1, "%s %u %s %s %s %u %u", szCmd,
					&tTaskData.ucType, tTaskData.szTitle, tTaskData.szDetail, tTaskData.szTargetName, &tTaskData.dwPrizeMoney, &tTaskData.ucRankReq))
				{
					tTaskData.idUser	= pUser->GetID();
					::SafeCopy(tTaskData.szUserName, pUser->GetName(), _MAX_NAMESIZE);
					if (MercenaryTask()->CreateNewTask(&tTaskData))
					{
						pUser->SendSysMsg("���񷢲��ɹ���");
					}
				}
			}
		}*/
		/*else if (_stricmp(szCmd, "task_del") == 0)
		{
			CMercenaryTaskData* pData = MercenaryTask()->QueryTaskDataByOwner(pUser->GetID());
			if (pData)
			{
				if (MercenaryTask()->DeleteTask(pData->GetID()))
					pUser->SendSysMsg("����ɾ���ɹ�");
				else
					pUser->SendSysMsg("����ɾ��ʧ��");
			}
			else
				pUser->SendSysMsg("����û�з�������");
		}*/
		else if (_stricmp(szCmd, "magicattack") == 0)
		{
			int nType = 0;
			char szName[256];
			if (3 == sscanf(szWords+1, "%s %d %s", szCmd, &nType, szName))
			{
				CUser* pTarget = UserManager()->GetUser(szName);
				if (pTarget)
				{
					pUser->SendSysMsg("Magic attack [type=%d, target=%s]", nType, szName);
					pUser->MagicAttack(nType, pTarget->GetID(), pTarget->GetPosX(), pTarget->GetPosY());
				}
			}
		}
		else if (_stricmp(szCmd, "chgpos") == 0)
		{
			int nPosX=0, nPosY = 0;
			if (3 == sscanf(szWords+1, "%s %d %d", szCmd, &nPosX, &nPosY))
			{
				if(pUser->GetMap()->IsStandEnable(nPosX, nPosY))
				{
//					pUser->ProcessOnMove(MOVEMODE_TRACK);
//					pUser->JumpPos(nPosX, nPosY);		//? may be optimize to JumpPos(,)
//					pUser->Synchro();

					pUser->SyncTrackTo(nPosX, nPosY, 0, 0);
				}
//				pUser->ProcessOnMove(MOVEMODE_TRACK);
//				pUser->JumpPos(nPosX, nPosY);
//				pUser->Synchro();
			}
		}
		else if (_stricmp(szCmd, "callpet") == 0)
		{
			OBJID	idType = ID_NONE;
			int		nSecs = 0;
			if (3 == sscanf(szWords+1, "%s %u %d", szCmd, &idType, &nSecs))
			{
				pUser->CallPet(idType, pUser->GetPosX(), pUser->GetPosY(), nSecs);
			}
		}
		else if (_stricmp(szCmd, "showid") == 0)
		{
			pUser->SendSysMsg("AccountID=%u, UserID=%u", pUser->GetAccountID(), pUser->GetID());
		}
#endif
		DEBUG_CATCH2("CMsgTalk CMD:[%s] error.", szCmd)			// AAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		return;
	}

	// ��Ƶ��
	if(pUser && pUser->IsGhost() && m_pInfo->unTxtAttribute != _TXTATR_TEAM)
	{
		m_pInfo->unTxtAttribute	= _TXTATR_GHOST;
		pUser->BroadcastRoomMsg(this, EXCLUDE_SELF);
		return ;
	}

	// ��ͨTALK
	switch(m_pInfo->unTxtAttribute)
	{
	case	_TXTATR_GLOBAL:
		{
			if(pRole->GetLev() < 30)
			{
				pRole->SendSysMsg(STR_NO_ENOUGH_LEVEL);
				break;
			}

			if(pUser && pUser->GetMana() < 200)
			{
				pRole->SendSysMsg(STR_NO_ENOUGH_POWER);
				break;
			}

			pRole->AddAttrib(_USERATTRIB_MANA, -200, SYNCHRO_TRUE);

			RoleManager()->BroadcastMsg(this);
		}
		break;
	case	_TXTATR_PRIVATE:
		{
			CUserPtr pTarget = UserManager()->GetUser(szReceiver);
			if(pTarget)
				pTarget->SendMsg(this);
			else
				MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(this, szReceiver);
		}
		break;
	case	_TXTATR_TEAM:
		{
			if (pUser)
			{
				CTeam* pTeam = pUser->GetTeam();
				if (pTeam)
					pTeam->BroadcastTeamMsg(this, pUser);
			}
		}
		break;
	case	_TXTATR_FRIEND:
		{
			if (pUser)
				pUser->BroadcastFriendsMsg(this);
		}
		break;
	case	_TXTATR_SYNDICATE:
		{
			if (pUser)
			{
				OBJID idSyn = pUser->GetSynID();
				CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
				if (pSyn)
				{
					if(pSyn->GetInt(SYNDATA_MONEY) < SYN_MONEY_BASELINE)
					{
						pUser->SendSysMsg(STR_TOO_LOWER_SYN_MONEY);
						break;
					}
					pSyn->BroadcastSynMsg(this, pUser);

					m_pInfo->idTransmit	= pSyn->GetID();
					MapGroup(PID)->QueryIntraMsg()->TransmitMsg(this, GetSocketID(), GetNpcID());
				}
			}
		}
		break;
	case	_TXTATR_LEAVEWORD:
		{
			if (pUser)
			{
				if(!::TalkStrCheck(szWords, true))		// true: enable new line character
				{
					pUser->SendSysMsg(STR_INVALID_CHARACTER);
					return ;
				}
				pUser->AddLeaveWord(szReceiver, szWords);
			}
		}
		break;
	case	_TXTATR_SYNANNOUNCE:
		{
			LPCTSTR pAnnounce = szWords;
			if(!pUser || pUser->GetSynID() == ID_NONE || pUser->GetSynRankShow() != RANK_LEADER)
				return ;
			if(!::TalkStrCheck(szWords, true))		// true: enable new line character
			{
				pUser->SendSysMsg(STR_INVALID_CHARACTER);
				return ;
			}

			CSyndicate* pSyn = SynManager()->QuerySyndicate(pUser->GetSynID());
			IF_OK(pSyn)
			{
				pSyn->QueryModify()->SetTenet(pAnnounce);
				pSyn->BroadcastSubSynMsg(GetSocketID(), GetNpcID(), pAnnounce, NULL, NULL, 0xFFFFFF, _TXTATR_SYNANNOUNCE);
			}
		}
		break;
	case	_TXTATR_CRYOUT:
		{
			if (pUser && pUser->QueryBooth())
			{
				if(!::TalkStrCheck(szWords, true))
				{
					pUser->SendSysMsg(STR_INVALID_MSG);
					return ;
				}

				pUser->QueryBooth()->SetCryOut(szWords);
				pUser->BroadcastRoomMsg(this, false);// add by arhun
			}
		}
		break;
	case	_TXTATR_MSG_TRADE:
	case	_TXTATR_MSG_FRIEND:
	case	_TXTATR_MSG_TEAM:
	case	_TXTATR_MSG_SYN:
	case	_TXTATR_MSG_OTHER:
		{
			CUser* pUser = UserManager()->GetUser(this);
			if(!pUser)
				return ;
			if(pUser->GetLev() < LOGIN_FREE_LEVEL)
			{
				pUser->SendSysMsg(STR_LOW_LEVEL);
				return ;
			}
			if(!::TalkStrCheck(szWords, true))		// true: enable new line character
			{
				pUser->SendSysMsg(STR_INVALID_CHARACTER);
				return ;
			}

				if(m_pInfo->unTxtAttribute == _TXTATR_MSG_SYN)
			{
				OBJID idSyn = pUser->GetSynID();
				if(idSyn == ID_NONE)
					return ;

				SetTransData(idSyn);
			}

			MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(this);
		}
		break;
	case	_TXTATR_MSG_SYSTEM:
		{
			ASSERT(!"_TXTATR_MSG_OTHER");
		}
		break;

	case	_TXTATR_SERVE:
		{
			CUser* pUser = UserManager()->GetUser(this);
			if (!pUser)
				return;

			if (pUser->IsGM())	// game service
			{
				CUserPtr pTarget = UserManager()->GetUser(szReceiver);
				if (pTarget)
					pTarget->SendMsg(this);
				else
					MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(this, szReceiver);
			}
			else				// client ask service
			{
				// ��������Ƶ��GM����Ϣȫ��ͨ��������Ĵ����Ա�֤Ψһ�Ժ���ȷ�� -- zlong 2004.5.18
//				CUserPtr pTarget = UserManager()->GetGM();
//				if (pTarget)
//					pTarget->SendMsg(this);
//				else
					MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(this);	//, szReceiver);
			}
		}
		break;

	case	_TXTATR_REJECT:
		{
			CUserPtr pTarget = UserManager()->GetUser(szReceiver);
			if(pTarget)
			{
				pTarget->SendMsg(this);
				// �����Ǵ������̳й����Ĵ���ʽ
				// ����һ��BUG������û�����CUser��������Ҫ�����޸ģ�

				if (strcmp(szWords, "a") == 0)	// REJECT_FRIEND
					pTarget->FetchApply(CUser::APPLY_FRIEND, pUser->GetID());
				else if (strcmp(szWords, "b") == 0)	// REJECT_TRADE
					pTarget->FetchApply(CUser::APPLY_TRADE, pUser->GetID());
				else if (strcmp(szWords, "c") == 0)	// REJECT_TEAM
					pTarget->FetchApply(CUser::APPLY_TEAMAPPLY, pUser->GetID());
				else if (strcmp(szWords, "d") == 0)	// REJECT_TEACHERAPPLY
					pTarget->FetchApply(CUser::APPLY_TEACHERAPPLY, pUser->GetID());
				else if (strcmp(szWords, "e") == 0)	// REJECT_STUDENGAPPLY
					pTarget->FetchApply(CUser::APPLY_STUDENTAPPLY, pUser->GetID());
			}
		}
		break;

	default:
		{
			pRole->BroadcastRoomMsg(this, EXCLUDE_SELF);
		}
		break;
	}
}
