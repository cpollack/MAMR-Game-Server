#pragma once

#include "MonsterData.h"

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

	double LifeMax;
	SHORT MedalAttack;
	SHORT MedalDefence;
	SHORT MedalDexterity;

	int SkillCount;
	int SkillID[MAX_PETSKILL];

	double baseGrowth; //org_growrate ?
	int State; //?
};


class IRecord;
class IDatabase;
class CPetData : public CMonsterData {
public:
	CPetData();
	virtual ~CPetData();

protected:
	bool	Create(OBJID idPet, IDatabase* pDb);
	bool	LoadInfo(void);
	bool	SaveInfo(void);

public: //From Monster
	void			SetID(OBJID oId) { info.id = oId; }
	OBJID			GetID() { return info.id; }

	void			SetName(const char* pszName);
	char*			GetName() { return info.szName; }

	void			SetAttack(double fAttack) { info.Attack = fAttack; }
	double			GetAttack() { return info.Attack; }

	void			SetDefence(double fDef) { info.Defence = fDef; }
	double			GetDefence() { return info.Defence; }

	void			SetDexterity(double fDex) { info.Dexterity = fDex; }
	double			GetDexterity() { return info.Dexterity; }

	void			SetLife(int fLife, BOOL bUpdate = false);
	int				GetLife() { return info.Life; }

	void			SetGrowth(double fGrow) { info.Growth = fGrow; }
	double			GetGrowth() { return info.Growth; }

	void			SetLifeRise(double fRise) { info.LifeRise = fRise; }
	double			GetLifeRise() { return info.LifeRise; }

	void			SetLevel(int nLev) { info.Level = nLev; }
	int				GetLevel() { return info.Level; }

	void			SetLook(int nLook) { info.Look = nLook; }
	int				GetLook() { return info.Look; }

	void			SetClass(int nClass) { info.Class = nClass; }
	int				GetClass() { return info.Class; }

	void			SetBaseAttack(double fAttack) { info.baseAttack = fAttack; }
	double			GetBaseAttack() { return info.baseAttack; }

	void			SetBaseDefence(double fDef) { info.baseDefence = fDef; }
	double			GetBaseDefence() { return info.baseDefence; }

	void			SetBaseDexterity(double fDex) { info.baseDexterity = fDex; }
	double			GetBaseDexterity() { return info.baseDexterity; }

	void			SetBaseLife(double fLife) { info.baseLife = fLife; }
	double			GetBaseLife() { return info.baseLife; }

	void			SetRateAttack(int iRate) { info.rateAttack = iRate; }
	int				GetRateAttack() { return info.rateAttack; }

	void			SetRateDefence(int iRate) { info.rateDefence = iRate; }
	int				GetRateDefence() { return info.rateDefence; }

	void			SetRateDexterity(int iRate) { info.rateDexterity = iRate; }
	int				GetRateDexterity() { return info.rateDexterity; }

	HSB				GetHSB(int idx) { return info.hsb[idx]; }

public: //Specific to pet
	void SetExperience(int iExp) { info.Experience = iExp; }
	DWORD GetExperience() { return info.Experience; }

	void SetLoyalty(int iLoy) { info.Loyalty = iLoy; }
	DWORD GetLoyalty() { return info.Loyalty; }

	void SetGeneration(int iGen) { info.Generation = iGen; }
	DWORD GetGeneration() { return info.Generation; }

	void SetInjury(int iInj) { info.Injury = iInj; }
	DWORD GetInjury() { return info.Injury; }

	void SetMaxLife(double fLife) { info.LifeMax = fLife; }
	double GetMaxLife() { return info.LifeMax; }

	void SetSkillCount(int iCount) { info.SkillCount = iCount; }
	DWORD GetSkillCount() { return info.SkillCount; }

	void SetSkill(int idx, OBJID idSkill) { info.SkillID[idx] = idSkill; }
	DWORD GetSkill(int idx) { return info.SkillID[idx]; }

	void SetMedalAttack(int iMedal) { info.MedalAttack = iMedal; }
	DWORD GetMedalAttack() { return info.MedalAttack; }

	void SetMedalDefence(int iMedal) { info.MedalDefence = iMedal; }
	DWORD GetMedalDefence() { return info.MedalDefence; }

	void SetMedalDexterity(int iMedal) { info.MedalDexterity = iMedal; }
	DWORD GetMedalDexterity() { return info.MedalDexterity; }

	void SetOwnerID(OBJID id) { info.OwnerID = id; }
	OBJID GetOwnerID() { return info.OwnerID; }

	PetInfoStruct&		GetInfo() { return info; }
protected:
	PetInfoStruct		info;
	IRecord*			pRes;

	friend class CPet;
};