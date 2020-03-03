#pragma once

#include "MonsterData.h"

const DWORD	_IDMSK_PET = 0x80000000;
const int MAX_PETSKILL = 5;

//////////////////////////////////////////////////////////////////////
enum PETDATA {
	PETDATA_NAME = 1,
};

//////////////////////////////////////////////////////////////////////
char		szPetTable[];

//////////////////////////////////////////////////////////////////////
struct PetInfoStruct : MonsterInfoStruct {
	DWORD Experience;
	SHORT Loyalty;
	BYTE Generation;
	WORD Injury;

	OBJID OwnerID;
	OBJID ItemID;

	float LifeMax;
	SHORT MedalAttack;
	SHORT MedalDefence;
	SHORT MedalDexterity;

	int SkillCount;
	int SkillID[MAX_PETSKILL];

	float baseGrowth; //org_growrate ?
	int State; //?
};


class IRecord;
class IDatabase;
class CPetData : CMonsterData {
public:
	CPetData();
	virtual ~CPetData();

protected:
	bool	Create(OBJID idPet, IDatabase* pDb);
	bool	LoadInfo(void);
	bool	SaveInfo(void);

public:
	void SetExperience(int iExp) { info.Experience = iExp; }
	DWORD GetExperience() { return info.Experience; }

	void SetLoyalty(int iLoy) { info.Loyalty = iLoy; }
	DWORD getLoyalty() { return info.Loyalty; }

	void SetGeneration(int iGen) { info.Generation = iGen; }
	DWORD GetGeneration() { return info.Generation; }

	void SetInjury(int iInj) { info.Injury = iInj; }
	DWORD GetInjury() { return info.Injury; }

	void SetMaxLife(float fLife) { info.LifeMax = fLife; }
	float GetMaxLife() { return info.LifeMax; }

	PetInfoStruct&		GetInfo() { return info; }
protected:
	PetInfoStruct		info;
	IRecord*			pRes;

	friend class CPet;
};