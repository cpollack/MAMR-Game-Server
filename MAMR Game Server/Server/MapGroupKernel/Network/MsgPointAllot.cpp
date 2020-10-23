// MsgBattle.cpp: implementation of the CMsgBattle class.
//
//////////////////////////////////////////////////////////////////////

#include "allmsg.h"

#include "../MapGroup.h"
#include "../User.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgPointAllot::CMsgPointAllot()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
}

CMsgPointAllot::~CMsgPointAllot()
{

}

//////////////////////////////////////////////////////////////////////
BOOL CMsgPointAllot::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!pbufMsg)
		return false;

	memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgPointAllot::Process(CGameSocket* pSocket)
{
	CUser* pUser = UserManager()->GetUserBySocketID(this->GetSocketID());
	CHECK(pUser);

	int points = m_pInfo->physique + m_pInfo->stamina + m_pInfo->force + m_pInfo->speed + m_pInfo->degree;
	if (points > pUser->GetAddPoint()) {
		pUser->SendSysMsg(_TXTATR_NORMAL, "Failed to allocate attributes. You attempted to spend more points then you had.");
		return;
	}

	pUser->SetPhysique(pUser->GetPhysique() + m_pInfo->physique);
	pUser->SetStamina(pUser->GetStamina() + m_pInfo->stamina);
	pUser->SetForce(pUser->GetForce() + m_pInfo->force);
	pUser->SetSpeed(pUser->GetSpeed() + m_pInfo->speed);
	pUser->SetDegree(pUser->GetDegree() + m_pInfo->degree);
	pUser->SetAddPoint(pUser->GetAddPoint() - points);
	pUser->SaveInfo();

	//ASSERT(!"CMsgUserLevelUp::Process");
}

