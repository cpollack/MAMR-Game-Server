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

	info.Life = pRes->LoadDWord("life");
	info.LifeMax = pRes->LoadDWord("max_life");
	info.baseLife = pRes->LoadDWord("base_life");

	info.Attack = pRes->LoadDWord("attack");
	info.baseAttack = pRes->LoadDWord("base_attack");
	info.rateAttack = pRes->LoadInt("attack_rate");

	info.Defence = pRes->LoadDWord("defence");
	info.baseDefence = pRes->LoadDWord("base_defence");
	info.rateDefence = pRes->LoadInt("defence_rate");

	info.Dexterity = pRes->LoadDWord("dexterity");
	info.baseDexterity = pRes->LoadDWord("base_dexterity");
	info.rateDexterity = pRes->LoadInt("dexterity_rate");
	
	info.Growth = pRes->LoadDWord("grow_rate");
	info.baseGrowth = pRes->LoadDWord("org_growrate");
	info.LifeRise = pRes->LoadDWord("life_rise");

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