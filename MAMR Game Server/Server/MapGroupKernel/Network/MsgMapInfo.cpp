// MsgMapInfo.cpp: implementation of the CMsgMapInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "AllMsg.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgMapInfo::CMsgMapInfo()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
}

CMsgMapInfo::~CMsgMapInfo()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgMapInfo::Create(CGameMap* pMap, int nMode, CUser* pUser)
{
	IF_NOT (pMap)
		return false;

	// init
	this->Init();

	// fill info now
	m_pInfo->wMode	= nMode;
	m_pInfo->idUser = pUser->GetID();
	m_pInfo->idMap	= pMap->GetID();
	m_pInfo->idDoc	= pMap->GetDocID();

	m_pInfo->wX = pUser->GetPosX();
	m_pInfo->wY = pUser->GetPosY();
	m_pInfo->wWeather = pMap->GetWeather();
	m_pInfo->wBGMusic = pMap->GetBGMusic();
	m_pInfo->wBGMusic_show = pMap->GetBGMusicShow();
	m_pInfo->wFightMusic = pMap->GetFightMusic();

	strcpy(m_pInfo->szMapName, pMap->GetName());

	m_pInfo->dwType		= pMap->GetType();

	m_unMsgType	= _MSG_MAPINFO;
	m_unMsgSize	= sizeof(MSG_Info);

	return true;

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgMapInfo::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_MAPINFO != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgMapInfo::Process(void* pInfo)
{
}

//////////////////////////////////////////////////////////////////////
