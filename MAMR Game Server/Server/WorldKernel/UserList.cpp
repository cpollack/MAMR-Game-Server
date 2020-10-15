// UserList.cpp: implementation of the CUserList class.
//
//////////////////////////////////////////////////////////////////////
#include "MessagePort.h"
#include "common.h"
#include "Network/NetMsgW.h"
#include "I_mydb.h"
#include "protocol.h"
#include "inifile.h"
#include "Network/MsgFee_A.h"
using namespace world_kernel;
#include "Network/AllMsg.h"
//#include "supermanlist.h"
#include "UserList.h"
#include "MessageBoard.h"
#include "WorldKernel.h"
#include "../MapGroupKernel/Role.h"

const int	SECS_PER_GAMEHOUR		= 300;			// send CMsgTime to all user
const int	NEWBIE_ATTR_POINT		= 10;			// 新建角色属性点总和
//////////////////////////////////////////////////////////////////////
void CPlayer::OnTimer(time_t tCurr)
{
	if(IsAgent())
		return;

	if(m_nLevel < LOGIN_FREE_LEVEL)
	{
		m_tPoint	= time(NULL);
		if (m_tTick.ToNextTime(POINTFEE_SECS))
			GameWorld()->SendFee(m_idAccount, CMsgFee_A::FEE_TICK);
		return;
	}

	// account server
	if(GameWorld()->IsAccountLoginOK() && time(NULL) > m_tPoint + POINTFEE_DELAY_SECS)
	{
		m_tPoint += POINTFEE_SECS;

		GameWorld()->SendFee(m_idAccount, CMsgFee_A::FEE_POINT);
	}
}

bool CPlayer::SendMsg(world_kernel::CNetMsgW* pMsg)
{
	if(IsAgent())
		return GameWorld()->SendNpcMsg(GetID(), pMsg);
	else
		return GameWorld()->SendClientMsg(idSocket, pMsg);
}


MYHEAP_IMPLEMENTATION(CUserList,s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUserList::CUserList()
{
	m_nPlayerAmount		= 0;
	m_nMaxPlayerAmount	= 0;
	m_nHour				= 6;		// start server in 8 am.
	m_setAgent			= AGENT_SET::CreateNew(true);
}

//////////////////////////////////////////////////////////////////////
CUserList::~CUserList()
{

}

//////////////////////////////////////////////////////////////////////
bool CUserList::Create(world_kernel::ISocket* pSocket, IDatabase* pDb)
{
	CHECKF(pSocket);
	m_pSocket	= pSocket;

	//m_pSupermanSet = CSupermanList::CreateNew();
	//CHECKF(m_pSupermanSet && m_pSupermanSet->Create(pDb));

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUserList::LoginUser(LPCTSTR szAccount, LPCTSTR szPassword, SOCKET_ID idSocket)	// 仅用于非帐号服务器启动
{
#ifdef	ACCOUNT_ENABLE
	return false;
#endif
	bool	bRet = false;
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT id, name, account_id, recordmap_id FROM %s WHERE account='%s' && password='%s'", _TBL_USER, szAccount, szPassword);
	IRecordset*	pRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);		//VVVVVVVVVVVVVVVVVVVVVVVV
	if(pRes)
	{
		OBJID	idUser	= pRes->LoadDWord("id");
		NAMESTR	szName = "None";
		pRes->LoadString(szName, "name", _MAX_NAMESIZE);
		OBJID	idAccount	= pRes->LoadDWord("account_id");
		OBJID	idMap	= pRes->LoadDWord("recordmap_id");
		PROCESS_ID	idProcess	= MapList()->GetMapProcessID(idMap);
		ASSERT (idProcess != PROCESS_NONE);
		int		nLevel	= 0;		// 未帐号服务器登录，不需要等级
		CreateUser(idProcess, idUser, szName, idAccount, idSocket, nLevel, szAccount);

		bRet = true;
		pRes->Release();;		//AAAAAAAAAAAAAAAAAAAAAAAAAA

		GameWorld()->SendFee(idAccount, CMsgFee_A::FEE_BEGIN);
	}

	{
		m_nPlayerAmount++;
		if(m_nMaxPlayerAmount < m_nPlayerAmount)
			m_nMaxPlayerAmount = m_nPlayerAmount;
		extern struct STAT_STRUCT	g_stat;
		InterlockedExchange(&g_stat.nAllPlayers, m_nPlayerAmount);
		InterlockedExchange(&g_stat.nMaxPlayers, m_nMaxPlayerAmount);
		InterlockedIncrement(&g_stat.nLoginPlayers);
	}
	return bRet;
}

//////////////////////////////////////////////////////////////////////
// enum { LOGIN_OK, LOGIN_NEW, LOGIN_BAN };
int CUserList::LoginUser(OBJID idAccount, SOCKET_ID idSocket, LPCTSTR szInfo)
{
	int	nRet = LOGIN_NEW;
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT id, name, account_id, recordmap_id, level FROM %s WHERE account_id='%u'", _TBL_USER, idAccount);
	IRecordset*	pRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);		//VVVVVVVVVVVVVVVVVVVVVVVV
	if(pRes)
	{
		OBJID	idUser	= pRes->LoadDWord("id");
		NAMESTR	szName = "无";
		pRes->LoadString(szName, "name", _MAX_NAMESIZE);
		OBJID	idAccount	= pRes->LoadDWord("account_id");
		OBJID	idMap	= pRes->LoadDWord("recordmap_id");
		PROCESS_ID	idProcess	= MapList()->GetMapProcessID(idMap);
		int		nLevel	= pRes->LoadInt("level");

		if(!(strcmp(szInfo, FLAG_NO_POINT) == 0 && nLevel >= LOGIN_FREE_LEVEL)
				&& CreateUser(idProcess, idUser, szName, idAccount, idSocket, nLevel, szInfo))
		{
			nRet = LOGIN_OK;
			GameWorld()->SendFee(idAccount, CMsgFee_A::FEE_BEGIN);

			GameWorld()->SendRole(idSocket, idAccount);
		}
		else
		{
			nRet = LOGIN_BAN;
			GameWorld()->SendFee(idAccount, CMsgFee_A::FEE_OFFLINE);
		}
		pRes->Release();		//AAAAAAAAAAAAAAAAAAAAAAAAAA

	}
	else {
		//character creation, still do a 'fake' login
		CreateUser(-1, 0, "", idAccount, idSocket, 0, szInfo);
	}

	return nRet;
}

//////////////////////////////////////////////////////////////////////
bool CUserList::LoginAgent(OBJID idAgent)
{
	int	nRet = LOGIN_NEW;
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT id, name, recordmap_id, level FROM %s WHERE id=%u && account_id=0", _TBL_USER, idAgent);
	IRecordset*	pRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);		//VVVVVVVVVVVVVVVVVVVVVVVV
	if(pRes)
	{
		OBJID	idUser	= pRes->LoadDWord("id");
		NAMESTR	szName = "None";
		pRes->LoadString(szName, "name", _MAX_NAMESIZE);
		OBJID	idAccount	= ID_NONE;
		SOCKET_ID	idSocket	= SOCKET_NONE;
		OBJID	idMap	= pRes->LoadDWord("recordmap_id");
		PROCESS_ID	idProcess	= MapList()->GetMapProcessID(idMap);
		int		nLevel	= pRes->LoadInt("level");

		pRes->Release();		//AAAAAAAAAAAAAAAAAAAAAAAAAA

		if(CreateAgent(idProcess, idAgent, szName))
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUserList::LogoutUser(SOCKET_ID idSocket)		// return false: no this user
{
	if(!( idSocket != SOCKET_NONE && idSocket < m_setUser.size() && m_setUser[idSocket] ))
		return false;

	// account server
	CPlayer* pPlayer = m_setUser[idSocket];
	CHECKF(pPlayer);
	GameWorld()->SendFee(pPlayer->m_idAccount, CMsgFee_A::FEE_END);
	int	tCurr = time(NULL);
	if(tCurr > pPlayer->m_tPoint + POINTFEE_SECS)
	{
		LOGWARNING("Player [% s] [% u] failed to upload [% d] points when they exited!", 
				pPlayer->szName, pPlayer->GetID(), (tCurr - pPlayer->m_tPoint) / POINTFEE_SECS);
	}

	// gm ?
	if (pPlayer->IsGM())
	{
		vector<OBJID>::iterator iter;
		for (iter = m_setGm.begin(); iter != m_setGm.end(); iter++)
		{
			if (pPlayer->GetID() == *iter)
			{
				m_setGm.erase(iter);
				break;
			}
		}
	}

	{ // stat
		m_nPlayerAmount--;
		extern struct STAT_STRUCT	g_stat;
		InterlockedExchange(&g_stat.nAllPlayers, m_nPlayerAmount);
		InterlockedIncrement(&g_stat.nLogoutPlayers);
	}
	{
		SAFE_DELETE(m_setUser[idSocket]);
		m_setUser[idSocket] = NULL;
		return true;
	}
}

//////////////////////////////////////////////////////////////////////
bool CUserList::KickOutAccount(OBJID idAccount, LPCTSTR szText)		// return false: 不在线
{
	CHECKF(szText);

	CPlayer* pPlayer = GetPlayerByAccountID(idAccount);
	if(!pPlayer)
		return false;
	LOGDEBUG("DEBUG：Kick Out Account [% u]，SOCKET_ID[%d]", idAccount, pPlayer->idSocket);

	{
		CMsgTalkW	msg;
		if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, (char*)szText, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			pPlayer->SendMsg(&msg);
	}
	return GameWorld()->GetSocketInterface()->CloseSocket(pPlayer->idSocket);
}

//////////////////////////////////////////////////////////////////////
bool CUserList::KickOutSocket(SOCKET_ID idSocket)		// return false: 不在线
{
	LOGDEBUG("DEBUG：World core kicks out SOCKET_ID [% d]", idSocket);
	return GameWorld()->GetSocketInterface()->CloseSocket(idSocket);
}

//////////////////////////////////////////////////////////////////////
void CUserList::OnTimer(time_t tCurr)
{
	for(int i = 0; i < m_setUser.size(); i++)
	{
		if(m_setUser[i])
			m_setUser[i]->OnTimer(tCurr);
	}

	if(m_tHour.ToNextTick(SECS_PER_GAMEHOUR))
	{
		m_nHour = (++m_nHour) % 24;
/*
		CMsgTime	msg;
		IF_OK(msg.Create(m_nHour))
		{
			for(int i = 0; i < m_setUser.size(); i++)
			{
				if(m_setUser[i])
					GameWorld()->SendClientMsg(i, &msg);
			}
		}
*/
	}
}

//////////////////////////////////////////////////////////////////////
void CUserList::SendTimeToSocket(SOCKET_ID idSocket)
{
/*	CMsgTime	msg;
	IF_OK(msg.Create(m_nHour))
		GameWorld()->SendClientMsg(idSocket, &msg);
*/
}

//////////////////////////////////////////////////////////////////////
void CUserList::LogoutAllUser()
{
}

//////////////////////////////////////////////////////////////////////
bool CUserList::CreateUser(PROCESS_ID idProcess, OBJID idUser, LPCTSTR szName, OBJID idAccount, SOCKET_ID idSocket, int nLevel, LPCTSTR szNotify)
{
	if(idSocket >= m_setUser.size())
		m_setUser.resize(idSocket + 1, NULL);		// +1 : 保证有m_setUser[idSocket]这个成员

	IF_NOT(!m_setUser[idSocket])
	{
		LOGERROR("Players log in with the same SOCKET, new players [% s] [% u], SOCKET [% d], old players [% s] [% d]",
					szName, idUser, idSocket, m_setUser[idSocket]->szName, m_setUser[idSocket]->idUser);
		// gm ?
		if (m_setUser[idSocket]->IsGM())
		{
			vector<OBJID>::iterator iter;
			for (iter = m_setGm.begin(); iter != m_setGm.end(); iter++)
			{
				if (m_setUser[idSocket]->GetID() == *iter)
				{
					m_setGm.erase(iter);
					break;
				}
			}
		}
		KickOutSocket(idSocket);
		return false;
	}

	m_setUser[idSocket] = new CPlayer;
	if(!m_setUser[idSocket])
		return false;

	m_setUser[idSocket]->idUser		= idUser;
	SafeCopy(m_setUser[idSocket]->szName, szName, _MAX_NAMESIZE);
	m_setUser[idSocket]->idProcess	= idProcess;
	SafeCopy(m_setUser[idSocket]->szAccount, szNotify, _MAX_NAMESIZE);
	m_setUser[idSocket]->idSocket	= idSocket;
	m_setUser[idSocket]->m_idAccount	= idAccount;
	m_setUser[idSocket]->m_nLevel		= nLevel;
	SafeCopy(m_setUser[idSocket]->szNotify, szNotify, _MAX_NAMESIZE);

	m_setUser[idSocket]->m_tPoint	= time(NULL);

	// gm ?
	if (m_setUser[idSocket]->IsGM())
		m_setGm.push_back(m_setUser[idSocket]->GetID());

	{ // stat
		m_nPlayerAmount++;
		if(m_nMaxPlayerAmount < m_nPlayerAmount)
			m_nMaxPlayerAmount = m_nPlayerAmount;
		extern struct STAT_STRUCT	g_stat;
		InterlockedExchange(&g_stat.nAllPlayers, m_nPlayerAmount);
		InterlockedExchange(&g_stat.nMaxPlayers, m_nMaxPlayerAmount);
		InterlockedIncrement(&g_stat.nLoginPlayers);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUserList::CreateAgent(PROCESS_ID idProcess, OBJID idAgent, LPCTSTR szName)
{
	CPlayer* pAgent = new CPlayer;
	if(!pAgent)
		return false;

	pAgent->idUser			= idAgent;
	SafeCopy(pAgent->szName, szName, _MAX_NAMESIZE);
	pAgent->idProcess		= idProcess;
	pAgent->szAccount[0]	= 0;
	pAgent->idSocket		= SOCKET_NONE;
	pAgent->m_idAccount		= ID_NONE;
	pAgent->m_nLevel		= 0;
	pAgent->szNotify[0]		= 0;

	m_setAgent->AddObj(pAgent);

	return true;
}

//////////////////////////////////////////////////////////////////////
CPlayer* CUserList::GetPlayer(LPCTSTR szName)
{
	for(int i = 0; i < m_setUser.size(); i++)
	{
		if(m_setUser[i])
		{
			if(strcmp(m_setUser[i]->szName, szName) == 0)
				return m_setUser[i];
		}
	}

	AGENT_SET::Iterator pAgent = m_setAgent->NewEnum();
	while(pAgent.Next())
	{
		if(strcmp(pAgent->szName, szName) == 0)
			return pAgent;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
CPlayer* CUserList::GetPlayer(OBJID idUser)
{
	for(int i = 0; i < m_setUser.size(); i++)
	{
		if(m_setUser[i])
		{
			if(m_setUser[i]->idUser == idUser)
				return m_setUser[i];
		}
	}

	AGENT_SET::Iterator pAgent = m_setAgent->NewEnum();
	while(pAgent.Next())
	{
		if(pAgent->GetID() == idUser)
			return pAgent;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
CPlayer* CUserList::GetPlayerByAccount(LPCTSTR szAccount)
{
	for(int i = 0; i < m_setUser.size(); i++)
	{
		if(m_setUser[i])
		{
			if(strcmp(m_setUser[i]->szAccount, szAccount) == 0)
				return m_setUser[i];
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
CPlayer* CUserList::GetPlayerByAccountID(OBJID idAccount)
{
	for(int i = 0; i < m_setUser.size(); i++)
	{
		if(m_setUser[i])
		{
			if(m_setUser[i]->m_idAccount == idAccount)
				return m_setUser[i];
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
bool CUserList::CreateNewPlayer(OBJID idAccount, LPCTSTR szName, LPCSTR szNickName,
						int unLook, UCHAR ucFace, int nPhysique, int nStamina, int nForce, int nSpeed, int nDegree, HSB* hsb)
{
	CPlayer* pPlayer = GetPlayerByAccountID(idAccount);
	if (!pPlayer) return false;

	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s WHERE name=%s", _TBL_USER, szName);
	IRecordset* pUserRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);
	if (pUserRes) 	{
		pUserRes->Release();
		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_ERROR_DUPLICATE_NAME, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			pPlayer->SendMsg(&msg);
		return false;
	}

	int idMap	= DEFAULT_LOGIN_MAPID;					// Default logon point map
	CMapSt* pMap = MapList()->GetMap(idMap);
	if(!pMap)
		return false;

	//Attributes
	nPhysique++;
	nStamina++;
	nForce++;
	nSpeed++;
	nDegree++;

	int nMaxLife = (nPhysique * 3) + 30;		
	nMaxLife += (nStamina + nForce + nSpeed) / 4;
	nMaxLife += 5 * nStamina / 100;
	nMaxLife += 5 * nForce / 100;
	nMaxLife += 5 * nSpeed / 100;
	int nMaxMana = (nDegree * 3) + 20;			
	int nDefaultMoney = 100;
	int nDefaultLevel = 1;
	const int DEFAULT_ALLOT_POINT = 0;
	char szMate[_MAX_NAMESIZE] = "无";

	//check for duplicate name

	sprintf(szSQL, "INSERT %s SET account_id=%u,name='%s',mate='%s',monicker='%s',look=%d,face=%d, life=%d,power=%d,money=%u,level=%d, recordmap_id=%u,recordx=%u,recordy=%u, physique=%d,stamina=%d,force=%d,speed=%d,degree=%d,additional_point=%d, \
					money_saved=0,repute=0,exp=0,exp_smith=0,exp_creative=0,exp_medicine=0,exp_steal=0,metempsychosis=0,deed=0,task_mask=0,pk_enable=0,home_id=0,syndicate_id=0,degree_lev=0,lockkey=0,intellect=0,quiz_point=0,coin_money=0,last_login=0, \
					pet_count=0,pet0_id=0,pet1_id=0,pet2_id=0,pet3_id=0,pet4_id=0, skill_count=0,skill0_id=0,skill1_id=0,skill2_id=0,skill3_id=0,skill4_id=0,skill5_id=0,skill6_id=0,skill7_id=0,skill8_id=0,skill9_id=0, \
					weapon_id=0,armor_id=0,shoes_id=0,treasure0_id=0,treasure1_id=0",
					_TBL_USER,
					idAccount, szName, szMate, szNickName, unLook, ucFace,
					nMaxLife, nMaxMana, nDefaultMoney, nDefaultLevel,
					idMap, DEFAULT_LOGIN_POSX, DEFAULT_LOGIN_POSY,
					nPhysique, nStamina, nForce, nSpeed, nDegree, DEFAULT_ALLOT_POINT);
	GameWorld()->GetDatabase()->ExecuteSQL(szSQL);

	int userId = 0;
	sprintf(szSQL, "SELECT id FROM %s WHERE account_id=%d", _TBL_USER, idAccount);
	pUserRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);
	if (pUserRes) {
		userId = pUserRes->GetInt(0);
		pUserRes->Release();
	}
	if (!userId) return false;

	sprintf(szSQL, "INSERT %s SET id_user=%d, hue0=%d,saturation0=%d,bright0=%d,hue1=%d,saturation1=%d,bright1=%d,hue2=%d,saturation2=%d,bright2=%d,hue3=%d,saturation3=%d,bright3=%d,hue4=%d,saturation4=%d,bright4=%d ",
		_TBL_USERCOLOR, userId,		
		hsb[0].hue, hsb[0].sat, hsb[0].bright, hsb[1].hue, hsb[1].sat, hsb[1].bright, hsb[2].hue, hsb[2].sat, hsb[2].bright, hsb[3].hue, hsb[3].sat, hsb[3].bright, hsb[4].hue, hsb[4].sat, hsb[4].bright);
	GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);

	return true;
}

//////////////////////////////////////////////////////////////////////
void CUserList::ChangeProcessID(SOCKET_ID idSocket, PROCESS_ID idProcess)
{
	CHECK(idProcess >= MSGPORT_MAPGROUP_FIRST && idProcess < GameWorld()->GetMsgPort()->GetSize());
	CHECK(idSocket >= 0 && idSocket < m_setUser.size());

	m_setUser[idSocket]->idProcess = idProcess;
}

//////////////////////////////////////////////////////////////////////
void CUserList::LoginToMapGroup(CPlayer* pPlayer)
{
	CHECK(pPlayer);

	// 转到地图组中进行登录。
	IMessagePort* pPort = GameWorld()->GetMsgPort();
	ST_LOGIN	cLogin;
	cLogin.idSocket	= pPlayer->idSocket;
	cLogin.idUser	= pPlayer->GetID();
	PROCESS_ID	idMapGroupProcess = pPlayer->GetProcessID();
	pPort->Send(idMapGroupProcess, MAPGROUP_LOGIN, STRUCT_TYPE(ST_LOGIN), &cLogin);
	// 转换PROCESS_ID，标志玩家进入了MAPGROUP。(@帐号服务器是在MsgConnect中)
	pPlayer->idProcess	= idMapGroupProcess;	// 已设置，无意义		// readme.txt(2-9)

	if(!pPlayer->IsAgent())
	{
		CMsgTalkW	msg;
		if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, REPLAY_OK_STR, NULL, _COLOR_WHITE, _TXTATR_ENTRANCE))
			pPlayer->SendMsg(&msg);
	}
}

//////////////////////////////////////////////////////////////////////
void CUserList::BroadcastMsg(world_kernel::CNetMsgW* pMsg, CPlayer* pExcludeSender/*=NULL*/)
{
	CHECK(pMsg);

	for(int i = 0; i < m_setUser.size(); i++)
	{
		CPlayer* pPlayer = m_setUser[i];
		if(pPlayer && (!pExcludeSender || pExcludeSender->GetID() != pPlayer->GetID()))
			pPlayer->SendMsg(pMsg);
	}

	AGENT_SET::Iterator pAgent = m_setAgent->NewEnum();
	while(pAgent.Next())
	{
		if(pAgent && (!pExcludeSender || pExcludeSender->GetID() != pAgent->GetID()))
		{
			pAgent->SendMsg(pMsg);
			return;		// only one msg
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CUserList::BroadcastMsg(LPCTSTR szMsg, CPlayer* pExcludeSender/*=NULL*/, LPCTSTR pszEmotion, DWORD dwColor, int nAttribute)
{
	CHECK(szMsg);

	CMsgTalkW	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, (char*)szMsg, (char*)pszEmotion, dwColor, nAttribute))
		BroadcastMsg(&msg, pExcludeSender);
}

//////////////////////////////////////////////////////////////////////
void CUserList::DelAllAgent()
{
	AGENT_SET::Iterator pAgent	= m_setAgent->NewEnum();
	while(pAgent.Next())
		m_setAgent->DelObj(pAgent);
}
