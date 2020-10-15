// MsgLogin.cpp: implementation of the CMsgLogin class.
//
//////////////////////////////////////////////////////////////////////

#include "MessagePort.h"
#include "protocol.h"
#include "define.h"
#include "AllMsg.h"
#include "../WorldKernel.h"
using namespace world_kernel;
#include "../UserList.h"

#include "../MapGroupKernel/Network/MsgTalk.h"
#include "../MapGroupKernel/Monster.h"
#include "../MapGroupKernel/Pet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgRole::CMsgRole()
{
	Init();
	m_pInfo	= (MSG_Info*)m_bufMsg;
}

CMsgRole::~CMsgRole() {
	//
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgRole::Create(const char* pszNickname, const char* pszName,
	USHORT usPointLife, USHORT usPointDefence, USHORT usPointAttack, USHORT usPointDexterity, USHORT usPointMana,
	UCHAR ucRole, UCHAR ucFace, DWORD dwRecordMap, const BYTE* pbColorSet)
{
	// check param
	if(!pszNickname || strlen(pszNickname) >= _MAX_NAMESIZE)
		return false;

	if(!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return false;

	// init
	this->Init();
	
	// fill structure
	m_unMsgType	=_MSG_ROLE;
	m_unMsgSize	=sizeof(MSG_Info);

	strcpy(m_pInfo->szNickname, pszNickname);
	strcpy(m_pInfo->szName, pszName);

	m_pInfo->usPointLife = usPointLife;
	m_pInfo->usPointDefence = usPointDefence;
	m_pInfo->usPointAttack = usPointAttack;
	m_pInfo->usPointDexterity = usPointDexterity;
	m_pInfo->usPointMana = usPointMana;

	m_pInfo->ucRole = ucRole;
	m_pInfo->ucFace = ucFace;
	m_pInfo->dwRecordMap = dwRecordMap;

	if (pbColorSet) memcpy(m_pInfo->bColorSet, pbColorSet, 25);

	return true;
}

//////////////////////////////////////////////////////////////////////
BOOL CMsgRole::Create(char* pbufMsg, DWORD dwMsgSize)
{
	if (!CNetMsgW::Create(pbufMsg, dwMsgSize))
		return false;

	if(_MSG_ROLE != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
void CMsgRole::Process(void *pInfo) {
	if (!pInfo) return;


	if (!NameStrCheck(m_pInfo->szName))
	{
		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_ERROR_ILLEGAL_NAME, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			SendMsg(&msg);
		return;
	}

	if (!NameStrCheck(m_pInfo->szNickname))
	{
		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_ERROR_ILLEGAL_NICKNAME, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			SendMsg(&msg);
		return;
	}

	bool bRoleOk = false;
	if (m_pInfo->ucRole < 36) bRoleOk = true;
	if (m_pInfo->ucRole >= 190 && m_pInfo->ucRole <= 193) bRoleOk = true;
	if (!bRoleOk) {
		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_ERROR_ILLEGAL_TYPE, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			SendMsg(&msg);
		return;
	}

	int statTotal = 0;
	statTotal = m_pInfo->usPointLife;
	statTotal += m_pInfo->usPointDefence;
	statTotal += m_pInfo->usPointAttack;
	statTotal += m_pInfo->usPointDexterity;
	statTotal += m_pInfo->usPointMana;
	if (statTotal != 20) {
		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_ERROR_ILLEGAL_STAT, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			SendMsg(&msg);
		return;
	}

	HSB hsb[5];
	for (int i = 0; i < 5; i++) {
		hsb[i].hue = m_pInfo->bColorSet[(i * 3)];
		hsb[i].sat = m_pInfo->bColorSet[(i * 3) + 1];
		hsb[i].bright = m_pInfo->bColorSet[(i * 3) + 2];
	}

	CPlayer* pPlayer = UserList()->GetPlayerBySocket(GetSocketID());
	if (!pPlayer) return;

	SQLBUF	szSQL;
	if (g_UserList.CreateNewPlayer(pPlayer->m_idAccount, m_pInfo->szName, m_pInfo->szNickname, m_pInfo->ucRole, m_pInfo->ucFace,
		m_pInfo->usPointLife, m_pInfo->usPointDefence, m_pInfo->usPointAttack, m_pInfo->usPointDexterity, m_pInfo->usPointMana, hsb))
	{
		PROCESS_ID pId = MapList()->GetMapProcessID(100001);
		ST_CREATENEWMONSTER stMonster = { 72013, 1 };
		CMonster* pMonster = CMonster::CreateNew();
		if (pMonster->Create(pId, &stMonster)) {
			int userId = 0;
			sprintf(szSQL, "SELECT id FROM %s WHERE account_id=%d", _TBL_USER, pPlayer->m_idAccount);
			IRecordset* pUserRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);
			if (pUserRes) {
				userId = pUserRes->GetInt(0);
				pUserRes->Release();
			}
			else return;

			CPet* pPet = CPet::CreateNewPet(pId, userId, pMonster);
			if (pPet) {
				DWORD petId = 0;
				sprintf(szSQL, "SELECT id FROM %s WHERE owner_id=%d ORDER BY id DESC LIMIT 1", _TBL_PET, pPlayer->m_idAccount);
				IRecordset* pPetRes = GameWorld()->GetDatabase()->CreateNewRecordset(szSQL);
				if (pPetRes) {
					petId = pPetRes->GetInt(0);
					pPetRes->Release();

					sprintf(szSQL, "UPDATE %s SET pet_count=%d, petused_id=%u, pet0_id=%u WHERE id=%d LIMIT 1",
						_TBL_USER, 1, petId, petId, userId);
					GameWorld()->GetDatabase()->ExecuteSQL(szSQL);
				}
			}
		}

		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_CHARACTER_CREATED, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			SendMsg(&msg);
	}
	/*else
	{
		CMsgTalkW	msg;
		if (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, STR_ERROR_DUPLICATE_NAME, NULL, _COLOR_WHITE, _TXTATR_REGISTER))
			SendMsg(&msg);
	}*/
}










