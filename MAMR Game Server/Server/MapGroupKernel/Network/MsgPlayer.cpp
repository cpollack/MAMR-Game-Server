// MsgPlayer.cpp: implementation of the CMsgPlayer class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#include "../mapgroup.h"
//#include "UserData.h"
#include "../User.h"
#include "../AiNpc.h"
//#include "Booth.h"
#include "../Npc.h"

const int	STATUARY_LIFE_SCALE					= 100;			//? 补丁：雕像下传LIFE的比例
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgPlayer::CMsgPlayer()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;

	m_StrPacker.SetBuf(m_pInfo->szBuf, _MAX_MSGSIZE-sizeof(MSG_Info)+1);
}

CMsgPlayer::~CMsgPlayer()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPlayer::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_PLAYER != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPlayer::Create(IRole* pRole)
{
	DEBUG_CREATEMSG("CMsgPlayer",pRole->GetID(),pRole->IsUser(),"",pRole->GetPosX(),pRole->GetPosY())
	// param check
	if (!pRole)
		return false;

	// init
	this->Init();

	CUser* pUser = NULL;
	pRole->QueryObj(OBJ_USER, IPP_OF(pUser));
	const UserInfoStruct* pInfo = pUser->GetInfo();

	// fill info now
	m_pInfo->id			= pRole->GetID();
	m_pInfo->wPosX = pRole->GetPosX();
	m_pInfo->wPosY = pRole->GetPosY();

	m_pInfo->bLook = pInfo->dwLook;
	m_pInfo->bFace = pInfo->dwFace;
	m_pInfo->bState = 0;// pInfo->dwStatus ?
	m_pInfo->bDirection = pRole->GetDir();
	m_pInfo->bEmotion = 0; // emotion handling?

	m_pInfo->bRank = pUser->GetRankType();
	m_pInfo->bReborn = pUser->GetReborn();
	m_pInfo->bRankDetails = (pUser->GetMasterType() << 4) | pUser->GetAlignment();

	m_pInfo->wLevel = pInfo->ucLevel;
	m_pInfo->dwPK = pInfo->sPk;

	m_pInfo->dwSyndicateID = pInfo->idSyndicate;
	m_pInfo->dwSubgroupID = pInfo->idSubgroup;
	m_pInfo->wSyndicateRank = pInfo->wSynRank;

	BOOL bSucMake	=true;
	bSucMake &= m_StrPacker.AddString((char*)pRole->GetName());
	bSucMake &= m_StrPacker.AddString((char*)pInfo->szNickname);
	bSucMake &= m_StrPacker.AddString((char*)pInfo->szMate);

	for (int i = 0; i < 25; i++) m_pInfo->bColorSets[i] = 0;

	//if (m_pInfo->dwSyndicateID > 0) bSucMake &= m_StrPacker.AddString((char*)pInfo->szSyndicate);
	//if (m_pInfo->dwSubgroupID > 0) bSucMake &= m_StrPacker.AddString((char*)pInfo->szBranch);
	//if (m_pInfo->wSyndicateRank > 0) bSucMake &= m_StrPacker.AddString((char*)pInfo->szSynidcateRank);

	m_unMsgType	=_MSG_PLAYER;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();

	return true;
}

/*//////////////////////////////////////////////////////////////////////
BOOL CMsgPlayer::Create((CBooth* pBooth))
{
	// param check
	if (idPlayer == ID_NONE)
		return false;

	// init
	this->Init();

	// fill info now
	m_pInfo->id					= pBooth->GetID();
	m_pInfo->dwLookFace			= pBooty->GetLook();
	m_pInfo->dwEffect			= 0;
	m_pInfo->dwSynID_Rank		= 0;

	m_pInfo->dwHelmetType		= pInfo->ucFace;
	m_pInfo->dwArmorType		= pInfo->dwExp;
	m_pInfo->dwWeaponRType		= pInfo->nRepute;
	m_pInfo->dwWeaponLType		= pInfo->nRepute;
	m_pInfo->dwMountType		= pInfo->ucRank;

	m_pInfo->dwMedalSelect		= 0;

	m_pInfo->usPosX				= pBooth->GetPosX();
	m_pInfo->usPosY				= pBooth->GetPosY();
	m_pInfo->usHair				= 0;
	m_pInfo->ucDir				= pBooth->GetDir();
	m_pInfo->ucPose				= 0;

	if(!m_StrPacker.AddString(pBooth->GetOwnerName())
		return false;

	m_unMsgType	=_MSG_PLAYER;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();

	return true;
}*/

//////////////////////////////////////////////////////////////////////
void CMsgPlayer::Process(void *pInfo)
{
	return;
	CUser* pUser = g_UserManager.GetUser(this);
	pUser->BroadcastRoomMsg(this, EXCLUDE_SELF);

#ifdef _MSGDEBUG
	::LogMsg("Process CMsgPlayer, id:%u", m_pInfo->id);
#endif

	char szName[_MAX_NAMESIZE]		="";
	char szMate[_MAX_NAMESIZE]		="";
	char szSyndicate[_MAX_NAMESIZE]	="";
	char szTitle[_MAX_NAMESIZE]		="";

	m_StrPacker.GetString(0, szName, _MAX_NAMESIZE);
	m_StrPacker.GetString(1, szMate, _MAX_NAMESIZE);
	m_StrPacker.GetString(2, szSyndicate, _MAX_NAMESIZE);
	m_StrPacker.GetString(3, szTitle, _MAX_NAMESIZE);
}
