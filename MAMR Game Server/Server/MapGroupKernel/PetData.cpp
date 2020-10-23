#include "PetData.h"

//////////////////////////////////////////////////////////////////////
char	szPetTable[] = _TBL_PET;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPetData::CPetData()
{
	memset(&info, 0, sizeof(PetInfoStruct));
	pRes = NULL;
}

CPetData::~CPetData()
{
	if (pRes)
		pRes->Release();
}

//////////////////////////////////////////////////////////////////////
bool CPetData::Create(OBJID idPet, IDatabase* pDb)
{
	CHECKF(!pRes);
	CHECKF(pDb);

	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s WHERE id=%u LIMIT 1", _TBL_PET, idPet);
	IRecordset* pRecs = pDb->CreateNewRecordset(szSQL);	//VVVVVVVVV
	if (pRecs)
	{
		pRes = pRecs->CreateNewRecord();
		pRecs->Release();		//AAAAAAAAAAAAAA

		return LoadInfo();
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CPetData::LoadInfo(void)
{
	if (!pRes)
		return false;

	// load again?
	if (info.id != ID_NONE)
		return true;

	info.id = pRes->LoadUInt("id");
	
	info.Level = pRes->LoadInt("level");
	info.Experience = pRes->LoadInt("exp");
	info.Loyalty = pRes->LoadInt("fidelity");
	info.Injury = pRes->LoadInt("cap_lev");

	info.Look = pRes->LoadInt("look");
	info.Class = pRes->LoadInt("class");

	info.Life = pRes->LoadInt("life");
	info.LifeMax = pRes->LoadDouble("max_life");
	info.baseLife = pRes->LoadDouble("base_life");

	info.Attack = pRes->LoadDouble("attack");
	info.baseAttack = pRes->LoadDouble("base_attack");
	info.rateAttack = pRes->LoadInt("attack_rate");

	info.Defence = pRes->LoadDouble("defence");
	info.baseDefence = pRes->LoadDouble("base_defence");
	info.rateDefence = pRes->LoadInt("defence_rate");

	info.Dexterity = pRes->LoadDouble("dexterity");
	info.baseDexterity = pRes->LoadDouble("base_dexterity");
	info.rateDexterity = pRes->LoadInt("dexterity_rate");
	
	info.Growth = pRes->LoadDouble("grow_rate");
	info.baseGrowth = pRes->LoadDouble("org_growrate");
	info.LifeRise = pRes->LoadDouble("life_rise");

	info.MedalAttack = pRes->LoadInt("medal_attack");
	info.MedalDefence = pRes->LoadInt("medal_defence");
	info.MedalDexterity = pRes->LoadInt("medal_dexterity");

	info.OwnerID = pRes->LoadUInt("owner_id");
	info.ItemID = pRes->LoadUInt("treasure_id");

	info.SkillCount = pRes->LoadInt("sp_atk_cnt");
	for (int i = 0; i < MAX_PETSKILL; i++) {
		if (i + 1 < info.SkillCount) {
			char str[32];
			sprintf(str, "sp_atk%u", i);
			info.SkillID[i] = pRes->LoadInt(str);
		}
		else info.SkillID[i] = 0;
	}

	for (int i = 0; i < 3; i++) {
		char str1[8], str2[8], str3[8];
		sprintf(str1, "hue%u", i);
		sprintf(str2, "sat%u", i);
		sprintf(str3, "bright%u", i);
		info.hsb[i].hue = pRes->LoadInt(str1);
		info.hsb[i].sat = pRes->LoadInt(str2);
		info.hsb[i].bright = pRes->LoadInt(str3);
	}

	pRes->LoadStringA(info.szName, "name", _MAX_NAMESIZE);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CPetData::SaveInfo(void)
{
	if (!pRes)
		return false;

	pRes->UpdateRecord(); //Only updates data set via pRes->Set...

	return true;
}

//////////////////////////////////////////////////////////////////////
void CPetData::SetName(const char* pszName) {
	if (!pszName || strlen(pszName) >= _MAX_NAMESIZE)
		return;

	strcpy(info.szName, pszName);
}

void CPetData::SetLife(int nLife, BOOL bUpdate) {
	if (nLife < 0) nLife = 0;
	info.Life = nLife;
	if (pRes)
	{
		pRes->SetDWord("life", nLife);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetMaxLife(double dLife, BOOL bUpdate) {
	if (dLife < 0) dLife = 0;
	info.LifeMax = dLife;
	if (pRes)
	{
		pRes->SetDouble("max_life", dLife);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetAttack(double dAttack, BOOL bUpdate) {
	if (dAttack < 0) dAttack = 0;
	info.Attack = dAttack;
	if (pRes)
	{
		pRes->SetDouble("attack", dAttack);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetDefence(double dDef, BOOL bUpdate) {
	if (dDef < 0) dDef = 0;
	info.Defence = dDef;
	if (pRes)
	{
		pRes->SetDouble("defence", dDef);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetDexterity(double dDex, BOOL bUpdate) {
	if (dDex < 0) dDex = 0;
	info.Dexterity = dDex;
	if (pRes)
	{
		pRes->SetDouble("dexterity", dDex);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetLevel(int nLev, BOOL bUpdate) {
	if (nLev < 1) nLev = 1;
	info.Level = nLev;
	if (pRes)
	{
		pRes->SetDWord("level", nLev);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetExperience(int nExp, BOOL bUpdate) {
	if (nExp < 0) nExp = 0;
	info.Experience = nExp;
	if (pRes)
	{
		pRes->SetDWord("exp", nExp);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}

void CPetData::SetLoyalty(int nLoy, BOOL bUpdate) {
	if (nLoy < 0) nLoy = 0;
	if (nLoy > 150) nLoy = 150;
	info.Loyalty = nLoy;
	if (pRes)
	{
		pRes->SetDWord("fidelity", nLoy);
		if (bUpdate)
			pRes->UpdateRecord();
	}
}