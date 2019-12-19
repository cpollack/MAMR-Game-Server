// MsgUserInfo.cpp: interface for the CMsgUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "AllMsg.h"
#include "../UserData.h"
#include "../User.h"
#pragma	warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgUserInfo::CMsgUserInfo()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;

	m_StrPacker.SetBuf(m_pInfo->szBuf, _MAX_MSGSIZE-sizeof(MSG_Info)+1);
}

CMsgUserInfo::~CMsgUserInfo()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgUserInfo::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsg::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_USERINFO != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgUserInfo::Create(CUser* pUser)
{
	CHECKF(pUser);
	const UserInfoStruct* pInfo = pUser->GetInfo();

	// init
	this->Init();
	// fill info now
	m_pInfo->id			= pInfo->id;
	m_pInfo->bLook		= pInfo->dwLook;
	m_pInfo->bFace		= pInfo->dwFace;

	m_pInfo->wLevel		= pInfo->ucLevel;
	m_pInfo->wLife		= pInfo->usLife;
	m_pInfo->wLifeMax	= pUser->GetMaxLife();
	m_pInfo->wMana		= pInfo->usPower;
	m_pInfo->wManaMax	= pUser->GetMaxPower();

	m_pInfo->bRank = pUser->GetRankType();
	m_pInfo->bReborn = pUser->GetReborn();
	m_pInfo->bRankDetails = (pUser->GetMasterType() << 4) | pUser->GetAlignment();

	m_pInfo->dwMoney = pInfo->dwMoney;
	m_pInfo->dwReputation = pInfo->dwReputation;
	m_pInfo->dwCultivation = pInfo->dwCultivation;
	m_pInfo->dwPK = pInfo->sPk;
	m_pInfo->dwExperience = pInfo->nExp;
	m_pInfo->dwWuxing = pInfo->nSmith;
	m_pInfo->dwKungfu = pInfo->nCreative;
	m_pInfo->dwPetRaising = pInfo->nMedicine;
	m_pInfo->dwThievery = pInfo->nSteal;

	m_pInfo->wAdditionalPoint = pInfo->usAdditional_point;
	m_pInfo->wPhysique = pInfo->usPhysique;
	m_pInfo->wStamina = pInfo->usStamina;
	m_pInfo->wForce = pInfo->usForce;
	m_pInfo->wSpeed = pInfo->usSpeed;
	m_pInfo->wDegree = pInfo->usDegree;

	m_pInfo->wRecordX = pInfo->usRecordX;
	m_pInfo->wRecordY = pInfo->usRecordY;
	m_pInfo->dwRecordMap = pInfo->idRecordmap;

	m_pInfo->dwSyndicateID = pInfo->idSyndicate;
	m_pInfo->dwSubgroupID = pInfo->idSubgroup;
	m_pInfo->wSyndicateRank = pInfo->wSynRank;

	BOOL bSucMake	=true;
	bSucMake	&= m_StrPacker.AddString((char*)pInfo->szName);
	bSucMake	&= m_StrPacker.AddString((char*)pInfo->szNickname);
	bSucMake	&= m_StrPacker.AddString((char*)pInfo->szMate);

	//if (m_pInfo->dwSyndicateID > 0) bSucMake &= m_StrPacker.AddString((char*)pInfo->szSyndicate);
	//if (m_pInfo->dwSubgroupID > 0) bSucMake &= m_StrPacker.AddString((char*)pInfo->szBranch);
	//if (m_pInfo->wSyndicateRank > 0) bSucMake &= m_StrPacker.AddString((char*)pInfo->szSynidcateRank);

	m_unMsgType	=_MSG_USERINFO;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgUserInfo::Process(void *pInfo)
{
	ASSERT(!"CMsgUserInfo::Process()");
	return;

#ifdef _MSGDEBUG
	::LogMsg("Process CMsgUserInfo, id:%u", m_pInfo->id);
#endif

	char szName[_MAX_NAMESIZE]		= "";
	char szNickname[_MAX_NAMESIZE]	="";
	char szMate[_MAX_NAMESIZE]		="";
	char szSyndicate[_MAX_NAMESIZE] ="";
	char szSubgroup[_MAX_NAMESIZE]	="";
	char szTitle[_MAX_NAMESIZE]		="";

	m_StrPacker.GetString(0, szName, _MAX_NAMESIZE);
	m_StrPacker.GetString(1, szNickname, _MAX_NAMESIZE);
	m_StrPacker.GetString(2, szMate, _MAX_NAMESIZE);
}
