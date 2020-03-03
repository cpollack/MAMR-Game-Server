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

	float Attack;
	float Defence;
	float Dexterity;
	float Life;

	float baseAttack;
	float baseDefence;
	float baseDexterity;
	float baseLife;

	float Growth;
	float LifeRise;
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
	void			SetId(OBJID oId) { info.id = oId; }
	OBJID			GetID() { return info.id; }

	void			SetName(const char* pszName);
	char*			GetName() { return info.szName; }

	void			SetAttack(float fAttack) { info.Attack = fAttack; }
	float			GetAttack() { return info.Attack; }

	void			SetDefence(float fDef) { info.Defence = fDef; }
	float			GetDefence() { return info.Defence; }

	void			SetDexterity(float fDex) { info.Dexterity = fDex; }
	float			GetDexterity() { return info.Dexterity; }

	void			SetLife(float fLife) { info.Life = fLife; }
	float			GetLife() { return info.Life; }

	void			SetGrowth(float fGrow) { info.Growth = fGrow; }
	float			GetGrowth() { return info.Growth; }

	void			SetLifeRise(float fRise) { info.LifeRise = fRise; }
	float			GetLifeRise() { return info.LifeRise; }

	void			SetLevel(int nLev) { info.Level = nLev; }
	int				GetLevel() { return info.Level; }

	void			SetLook(int nLook) { info.Look = nLook; }
	DWORD			GetLook() { return info.Look; }

	void			SetBaseAttack(float fAttack) { info.baseAttack = fAttack; }
	float			GetBaseAttack() { return info.baseAttack; }

	void			SetBaseDefence(float fDef) { info.baseDefence = fDef; }
	float			GetBaseDefence() { return info.baseDefence; }

	void			SetBaseDexterity(float fDex) { info.baseDexterity = fDex; }
	float			GetBaseDexterity() { return info.baseDexterity; }

	void			SetBaseLife(float fLife) { info.baseLife = fLife; }
	float			GetBaseLife() { return info.baseLife; }

	void			SetRateAttack(int iRate) { info.rateAttack = iRate; }
	float			GetRateAttack() { return info.rateAttack; }

	void			SetRateDefence(int iRate) { info.rateDefence = iRate; }
	float			GetRateDefence() { return info.rateDefence; }

	void			SetRateDexterity(int iRate) { info.rateDexterity = iRate; }
	float			GetRateDexterity() { return info.rateDexterity; }


	MonsterInfoStruct&		GetInfo()	{ return info; }
protected:
	MonsterInfoStruct		info;
	IRecord*				pRes;

	friend class CMonster;
};
