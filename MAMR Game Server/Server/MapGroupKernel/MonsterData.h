#pragma once

#pragma warning(disable:4786)
#include "define.h"
#include "windows.h"
#include "GameData.h"
#include "Role.h"

//////////////////////////////////////////////////////////////////////
struct	MonsterInfoStruct
{
	OBJID id;

	NAMESTR	szName;		

	int Look;
	int MonsterID;
	int Class;

	WORD Level;

	double Attack;
	double Defence;
	double Dexterity;
	int Life; //Life is 'current life', and is always a whole number

	double baseAttack;
	double baseDefence;
	double baseDexterity;
	double baseLife;

	double Growth;
	double LifeRise;
	BYTE rateAttack;
	BYTE rateDefence;
	BYTE rateDexterity;

	HSB hsb[3];
};

class CMonsterData
{
public:
	CMonsterData();
	virtual ~CMonsterData();
	void Release() { delete this; }

	static CMonsterData* CreateNew() { return new CMonsterData; }

protected:
	bool	Create					(OBJID idMonster);
	bool	LoadInfo				();

public: // set to info, use by CMonster
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

	void			SetLife(int fLife) { info.Life = fLife; }
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

	MonsterInfoStruct&		GetInfo()	{ return info; }
protected:
	MonsterInfoStruct		info;
	IRecord*				pRes;

	friend class CMonster;
};
