// UserData.cpp: implementation of the CUserData class.
//
//////////////////////////////////////////////////////////////////////

#include "UserData.h"
#include "I_mydb.h"
#include "UserManager.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////
char	szUserTable[] = _TBL_USER;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserData::CUserData()
{
	memset(&m_Info, 0, sizeof(UserInfoStruct));
	m_pRes	= NULL;
}

CUserData::~CUserData()
{
	if(m_pRes)
		m_pRes->Release();
}

//////////////////////////////////////////////////////////////////////
bool CUserData::Create(OBJID idUser, IDatabase* pDb)
{
	CHECKF(!m_pRes);
	CHECKF(pDb);

	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s WHERE id=%u LIMIT 1", _TBL_USER, idUser);
	IRecordset* pRes = pDb->CreateNewRecordset(szSQL);	//VVVVVVVVV
	if(pRes)
	{
		m_pRes = pRes->CreateNewRecord();
		pRes->Release();		//AAAAAAAAAAAAAA

		return LoadInfo();
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUserData::LoadInfo(void)
{
	if (!m_pRes) 
		return false;

	// load again?
	if (m_Info.id != ID_NONE)
		return true;

	m_Info.sPk				= m_pRes->LoadInt("pk_enable");
	m_Info.dwCoin_money		= m_pRes->LoadDWord("coin_money");
	m_Info.dwLast_login		= m_pRes->LoadDWord("last_login");
	m_Info.dwLook			= m_pRes->LoadDWord("look");
	m_Info.dwFace			= m_pRes->LoadDWord("face");
	m_Info.dwMoney			= m_pRes->LoadDWord("money");
	m_Info.dwMoney_saved	 = m_pRes->LoadDWord("money_saved");
	m_Info.dwReputation		= m_pRes->LoadDWord("repute");
	m_Info.usRecordX		= m_pRes->LoadDWord("recordx");
	m_Info.usRecordY		= m_pRes->LoadDWord("recordy");
	m_Info.id				= m_pRes->LoadDWord("id");
	m_Info.idAccount		= m_pRes->LoadDWord("account_id");
	m_Info.idRecordmap		= m_pRes->LoadDWord("recordmap_id");
	m_Info.idSyndicate		= m_pRes->LoadDWord("syndicate_id");
	m_Info.nExp				= m_pRes->LoadUInt("exp");
	m_Info.ucLevel			= m_pRes->LoadInt("level");
	m_Info.dwCultivation	= m_pRes->LoadInt("degree_lev");
	m_Info.dwTaskMask		= m_pRes->LoadInt("task_mask");
	m_Info.idHome			= m_pRes->LoadInt("home_id");
	m_Info.dwLockKey		= m_pRes->LoadInt("lock_key");
	m_Info.dwCurrLockKey	= m_pRes->LoadInt("lock_key");

	m_pRes->LoadString(m_Info.szMate, "mate", _MAX_NAMESIZE);
	m_pRes->LoadString(m_Info.szName, "name", _MAX_NAMESIZE);
	m_pRes->LoadString(m_Info.szNickname,"monicker", _MAX_NAMESIZE);

	m_Info.usAdditional_point	= m_pRes->LoadDWord("additional_point");
	//m_Info.ucAuto_allot			= m_pRes->LoadUInt("auto_allot");

	m_Info.usLife		= m_pRes->LoadDWord("life");
	m_Info.usPower		= m_pRes->LoadDWord("power");
	m_Info.usPhysique	= m_pRes->LoadDWord("physique");
	m_Info.usStamina	= m_pRes->LoadDWord("stamina");
	m_Info.usForce		= m_pRes->LoadDWord("force");
	m_Info.usSpeed		= m_pRes->LoadDWord("speed");
	m_Info.usDegree		= m_pRes->LoadDWord("degree");

	m_Info.nSmith = m_pRes->LoadDWord("exp_smith");
	m_Info.nCreative = m_pRes->LoadDWord("exp_creative");
	m_Info.nMedicine = m_pRes->LoadDWord("exp_medicine");
	m_Info.nSteal = m_pRes->LoadDWord("exp_steal");

	m_Info.ucMetempsychosis		= m_pRes->LoadDWord("metempsychosis");

	m_Info.petCount = m_pRes->LoadInt("pet_count");
	m_Info.marchingPetId = m_pRes->LoadInt("petused_id");
	for (int i = 0; i < MAX_PETS; i++) {
		if (i < m_Info.petCount) {
			char str[8];
			sprintf(str, "pet%u_id", i);
			m_Info.petId[i] = m_pRes->LoadUInt(str);
		}
		else m_Info.petId[i] = 0;
	}

	m_Info.skillCount = m_pRes->LoadInt("skill_count");
	for (int i = 0; i < MAX_USERSKILLS; i++) {
		if (i < m_Info.skillCount) {
			char str[12];
			sprintf(str, "skill%u_id", i);
			m_Info.skillId[i] = m_pRes->LoadUInt(str);
		}
		else m_Info.skillId[i] = 0;
	}

	m_Info.idWeapon = m_pRes->LoadUInt("weapon_id");
	m_Info.idArmor = m_pRes->LoadUInt("armor_id");
	m_Info.idShoes = m_pRes->LoadUInt("shoes_id");
	m_Info.idBody = m_pRes->LoadUInt("treasure0_id");
	m_Info.idHead = m_pRes->LoadUInt("treasure1_id");

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUserData::SaveInfo(void)
{
	if (!m_pRes)
		return false;

	m_pRes->UpdateRecord();

	return true;
}

//////////////////////////////////////////////////////////////////////
char* CUserData::GetMate()
{
	return m_Info.szMate;
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetMate(LPCTSTR szMate, BOOL bUpdate)
{
	SafeCopy(m_Info.szMate, szMate, _MAX_NAMESIZE);
	if (m_pRes)
	{
		m_pRes->SetString("mate", szMate, _MAX_NAMESIZE);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetLife(int nLife, BOOL bUpdate)
{
	m_Info.usLife	= nLife;
	if (m_pRes)
	{
		m_pRes->SetDWord("life", nLife);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetPower(int nPower, BOOL bUpdate)
{
	m_Info.usPower	= nPower;
	if (m_pRes)
	{
		m_pRes->SetDWord("power", nPower);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetMoney(int nMoney, BOOL bUpdate)
{
	m_Info.dwMoney	= nMoney;
	if (m_pRes)
	{
		m_pRes->SetDWord("money", nMoney);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetMoneySaved(int nMoney, BOOL bUpdate)
{
	m_Info.dwMoney_saved	= nMoney;
	if (m_pRes)
	{
		m_pRes->SetDWord("money_saved", nMoney);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetExp(int nExp, BOOL bUpdate)
{
	m_Info.nExp	= nExp;
	if (m_pRes)
	{
		m_pRes->SetDWord("exp", nExp);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetPk(int nPk, BOOL bUpdate)
{
	m_Info.sPk	= nPk;
	if (m_pRes)
	{
		m_pRes->SetDWord("pk", nPk);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetRecordPos(OBJID idMap, DWORD dwX, DWORD dwY, BOOL bUpdate)
{
	m_Info.idRecordmap	= idMap;
	m_Info.usRecordX	= dwX;
	m_Info.usRecordY	= dwY;
	if (m_pRes)
	{
		m_pRes->SetDWord("recordmap_id", idMap);
		m_pRes->SetDWord("recordx", dwX);
		m_pRes->SetDWord("recordy", dwY);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetLastLogin()
{
	m_Info.dwLast_login	= ::DateStamp();
	if (m_pRes)
	{
		m_pRes->SetDWord("last_login", m_Info.dwLast_login);
	}
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////
void CUserData::SetName(const char* pszName)
{
	if (!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return;

	strcpy(m_Info.szName, pszName);
	if (m_pRes)
	{
		m_pRes->SetString("name", m_Info.szName, _MAX_NAMESIZE);
	}
}
#endif

//////////////////////////////////////////////////////////////////////
int CUserData::GetLev()
{
	return m_Info.ucLevel;
}

//////////////////////////////////////////////////////////////////////
int CUserData::GetCultivation()
{
	return m_Info.dwCultivation;
}

//////////////////////////////////////////////////////////////////////
int CUserData::GetAddPoint()
{
	return m_Info.usAdditional_point;
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetPotential	(int nData, BOOL fUpdate)
{
	m_Info.nPotential	= nData;
	if (m_pRes)
	{
		m_pRes->SetInt("potential", nData);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetMedalSelect	(int nData, BOOL fUpdate)
{
	m_Info.dwMedal_select	= nData;
	if (m_pRes)
	{
		m_pRes->SetUInt("medal_select", nData);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetTitleSelect	(int nData, BOOL fUpdate)
{
	m_Info.dwTitle_select	= nData;
	if (m_pRes)
	{
		m_pRes->SetUInt("title_select", nData);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
int CUserData::GetAutoAllot()
{
	return m_Info.ucAuto_allot;
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetAutoAllot(int nAutoAllot, BOOL fUpdate)
{
	m_Info.ucAuto_allot	= nAutoAllot;
	if (m_pRes)
	{
		m_pRes->SetUInt("auto_allot", nAutoAllot);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetMetempsychosis(int nMetempsychosis, BOOL fUpdate)
{
	m_Info.ucMetempsychosis	= nMetempsychosis;
	if (m_pRes)
	{
		m_pRes->SetUInt("metempsychosis", nMetempsychosis);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
int	CUserData::GetAlignment() {
	return m_Info.ucMetempsychosis % 10;
}

//////////////////////////////////////////////////////////////////////
int	CUserData::GetReborn() {
	return m_Info.ucMetempsychosis % 1000 / 10;
}

//////////////////////////////////////////////////////////////////////
int	CUserData::GetRankType() {
	return m_Info.ucMetempsychosis / 1000 % 10;
}

//////////////////////////////////////////////////////////////////////
int	CUserData::GetMasterType() {
	return m_Info.ucMetempsychosis / 10000;
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetLev(int nLev, BOOL bUpdate)
{
	m_Info.ucLevel	= nLev;
	if (m_pRes)
	{
		m_pRes->SetUInt("level", nLev);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetCultivation(int nCultivation, BOOL bUpdate)
{
	m_Info.dwCultivation = nCultivation;
	if (m_pRes)
	{
		m_pRes->SetUInt("degree_lev", nCultivation);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetForce(int nForce , BOOL bUpdate)
{
	m_Info.usForce	= nForce;
	if (m_pRes)
	{
		m_pRes->SetUInt("force", nForce);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetAddPoint(int nAddPoint, BOOL bUpdate)
{
	m_Info.usAdditional_point	= nAddPoint;
	if (m_pRes)
	{
		m_pRes->SetUInt("additional_point", nAddPoint);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetDegree(DWORD dwDex, BOOL bUpdate)
{
	m_Info.usDegree = dwDex;
	if (m_pRes)
	{
		m_pRes->SetUInt("degree", dwDex);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetSpeed(DWORD dwSpeed, BOOL bUpdate)
{
	m_Info.usSpeed	= dwSpeed;
	if (m_pRes)
	{
		m_pRes->SetUInt("speed", dwSpeed);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetStamina(DWORD dwStamina, BOOL fUpdate)
{
	m_Info.usStamina = dwStamina;
	if (m_pRes)
	{
		m_pRes->SetUInt("stamina", dwStamina);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
/*void CUserData::SetSoul(DWORD dwSoul, BOOL fUpdate)
{
	m_Info.usSoul	= dwSoul;
	if (m_pRes)
	{
		m_pRes->SetUInt("soul", dwSoul);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}*/

//////////////////////////////////////////////////////////////////////
void CUserData::SetLook(DWORD dwLook, BOOL fUpdate)
{
	m_Info.dwLook = dwLook;
	if (m_pRes)
	{
		m_pRes->SetUInt("look", dwLook);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetFace(DWORD dwFace, BOOL fUpdate)
{
	m_Info.dwFace = dwFace;
	if (m_pRes)
	{
		m_pRes->SetUInt("face", dwFace);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetHair(DWORD dwHair, BOOL fUpdate)
{
	m_Info.dwHair	= dwHair;
	if (m_pRes)
	{
		m_pRes->SetUInt("hair", dwHair);
		if (fUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetProfession (DWORD dwProfession, BOOL bUpdate)
{
	m_Info.ucProfession	= dwProfession;
	if (m_pRes)
	{
		m_pRes->SetUInt("profession", dwProfession);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetTaskMask (DWORD dwTask)
{
	m_Info.dwTaskMask	= dwTask;
	if (m_pRes)
	{
		m_pRes->SetUInt("task_mask", dwTask);
		m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetHomeID (OBJID idHome, BOOL bUpdate)
{
	m_Info.idHome	= idHome;
	if (m_pRes)
	{
		m_pRes->SetDWord("home_id", idHome);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetLockKey (DWORD dwLockKey, BOOL bUpdate)
{
	m_Info.dwLockKey		= dwLockKey;
	m_Info.dwCurrLockKey	= dwLockKey;
	if (m_pRes)
	{
		m_pRes->SetDWord("lock_key", dwLockKey);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}
//////////////////////////////////////////////////////////////////////
void CUserData::SetNobilityRank(DWORD dwNobilityRank, BOOL bUpdate)
{
	m_Info.ucNobilityRank = dwNobilityRank;
	if (m_pRes)
	{
		m_pRes->SetDWord("nobility_rank", dwNobilityRank);
		if(bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetPhysique(int nPhysique, BOOL bUpdate)
{
	m_Info.usPhysique = nPhysique;
	if (m_pRes)
	{
		m_pRes->SetUInt("physique", nPhysique);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetLength(int nLength, BOOL bUpdate)
{
	m_Info.cLength	= nLength;
	if (m_pRes)
	{
		m_pRes->SetUInt("length", nLength);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

//////////////////////////////////////////////////////////////////////
void CUserData::SetFat(int nFat, BOOL bUpdate)
{
	m_Info.cFat	= nFat;
	if (m_pRes)
	{
		m_pRes->SetUInt("fat", nFat);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

void CUserData::SetTutorExp(int nExp, BOOL bUpdate)
{
	m_Info.nTutorExp = nExp;
	if (m_pRes)
	{
		m_pRes->SetDWord("tutor_exp", nExp);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

void CUserData::SetTutorLevel(UCHAR ucLevel, BOOL bUpdate)
{
	m_Info.ucTutorLevel = ucLevel;
	if (m_pRes)
	{
		m_pRes->SetUInt("tutor_level", ucLevel);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

void CUserData::SetMaxLifePercent(DWORD dwPercent, BOOL bUpdate)
{
	if (dwPercent > 1000)		// 不超过100%
		dwPercent = 1000;
	else if (dwPercent < 125)	// 不低于1/8
		dwPercent = 125;
	m_Info.dwMaxlifePercent = dwPercent;
	if (m_pRes)
	{
		m_pRes->SetDWord("maxlife_percent", dwPercent);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

void CUserData::SetMercenaryRank(UCHAR ucRank, BOOL bUpdate)
{
	m_Info.ucMercenaryRank = ucRank;
	if (m_pRes)
	{
		m_pRes->SetUInt("mercenary_rank", ucRank);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

void CUserData::SetMercenaryExp(DWORD dwExp, BOOL bUpdate)
{
	m_Info.dwMercenaryExp	= dwExp;
	if (m_pRes)
	{
		m_pRes->SetUInt("mercenary_exp", dwExp);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

void CUserData::SetExploit(DWORD dwExploit, BOOL bUpdate)
{
	m_Info.dwExploit	= dwExploit;
	if (m_pRes)
	{
		m_pRes->SetUInt("exploit", dwExploit);
		if (bUpdate)
			m_pRes->UpdateRecord();
	}
}

DWORD CUserData::GetLastLogin()
{
	return m_Info.dwLast_login;
}
