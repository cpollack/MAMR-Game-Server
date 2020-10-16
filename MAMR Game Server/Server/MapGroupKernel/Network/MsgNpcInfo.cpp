// MsgNpcInfo.cpp: implementation of the CMsgNpcInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"
#include "../Npc.h"
#include "../NpcManager.h"
#include "../GameMap.h"
#include "../MapGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgNpcInfo::CMsgNpcInfo()
{
	Init();
	m_pInfo	= (MSG_Info *)m_bufMsg;

	//m_StrPacker.SetBuf(m_pInfo->szBuf, _MAX_MSGSIZE-sizeof(MSG_Info)+1);
}

CMsgNpcInfo::~CMsgNpcInfo()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNpcInfo::Create(CNpc* pNpc, int nMode)
{
	// init
	this->Init();

	// fill info now

	m_pInfo->id			= pNpc->GetID();
	m_pInfo->wMode		= nMode;
	m_pInfo->wType		= pNpc->GetType();
	m_pInfo->wLook		= pNpc->GetLook();
	m_pInfo->wCellX		= pNpc->GetPosX();
	m_pInfo->wCellY		= pNpc->GetPosY();

	strcpy(m_pInfo->szName, pNpc->GetName());

	std::vector<HSB> hsbSets = pNpc->GetHSBSets();
	for (int i = 0; i < 3; i++) {
		m_pInfo->bColorSets[(i * 5)] = i == 0 ? 32 : i == 1 ? 96 : 127;
		m_pInfo->bColorSets[(i * 5) + 2] = 8;
		if (i < hsbSets.size()) {
			HSB hsb = hsbSets[i];
			m_pInfo->bColorSets[(i * 5) + 1] = hsb.hue;
			m_pInfo->bColorSets[(i * 5) + 3] = hsb.sat;
			m_pInfo->bColorSets[(i * 5) + 4] = hsb.bright;
		}
		else {
			m_pInfo->bColorSets[(i * 5) + 1] = 0;
			m_pInfo->bColorSets[(i * 5) + 3] = 0;
			m_pInfo->bColorSets[(i * 5) + 4] = 0;
		}
	}

	m_unMsgType	=_MSG_NPCINFO;
	m_unMsgSize	=sizeof(MSG_Info);

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNpcInfo::Create(OBJID id, int nType, int nSort, int nLookFace, int nCellX, int nCellY, int nLength, int nFat, const char* pszName/*=NULL*/)
{
	// init
	this->Init();

	// fill info now

	m_pInfo->id			= id;
	/*m_pInfo->usType		= (unsigned short)nType;
	m_pInfo->usSort		= (unsigned short)nSort;
	m_pInfo->usLook		= (unsigned short)nLookFace;
	m_pInfo->usCellX	= (unsigned short)nCellX;	
	m_pInfo->usCellY	= (unsigned short)nCellY;
	m_pInfo->cLength	= (char)nLength;
	m_pInfo->cFat		= (char)nFat;*/

	// with name
	//if(pszName)
	//{
	//	m_StrPacker.AddString(pszName);
	//}

	m_unMsgType	=_MSG_NPCINFO;
	m_unMsgSize	=sizeof(MSG_Info);

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgNpcInfo::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if(!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgNpcInfo::Process(CGameSocket* pSocket)
{
#ifdef _MYDEBUG
	::LogSave("Process CMsgNpcInfo: ID:0x:%x, Type:%d, LookType:%d, CellX:%d, CellY:%d, Name:%s",
				m_pInfo->id	, m_pInfo->ucType,
				m_pInfo->usLook, m_pInfo->usCellX, 
				m_pInfo->usCellY, m_pInfo->szName);

#endif
	// create new npc
	CUserPtr pUser = UserManager()->GetUser(this);
	if(!pUser)
		return;

	MSGBUF	szMsg;
	//sprintf(szMsg, "%d %d %d %d %d", 
	//		m_pInfo->wCellX, m_pInfo->usCellY, 
	//		m_pInfo->wLook, m_pInfo->usType, m_pInfo->usSort);		// 转换成串，提供给任务系统
			// dir,			 frame,			, pose

	OBJID	idTaskItem = pUser->GetTaskItemID();
	if(idTaskItem == ID_NONE)
		return ;
	CItem* pItem = pUser->GetItem(idTaskItem);
	if(!pItem)
		return ;

	OBJID idAction = pUser->GetTaskItemActionID();
	if(idAction == ID_NONE)
		return ;

	GameAction()->ProcessAction(idAction, pUser, NULL, pItem, szMsg);
}


