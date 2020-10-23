#pragma once

#include "Monster.h"
#include <vector>

enum BATTLETYPE {
	BATTLETYPE_NPC,
	BATTLETYPE_PVP,
};

enum BATTLEACT {
	BATTLEACT_ATTACK = 0,
	BATTLEACT_SPECIAL = 1,
	BATTLEACT_DEFEND = 2,
	BATTLEACT_NONE = 3,
	//4, change pet?
	BATTLEACT_RUN = 5,
	BATTLEACT_CAPTURE = 6,
	BATTLEACT_CAPTUREFAIL = 7,
	BATTLEACT_CAPTURESUCCEED = 8,
	BATTLEACT_ITEM = 9,
	BATTLEACT_RUNSUCCEED = 11,
};

enum FIGHTERSTATE {
	STATE_ALIVE = 100,
	STATE_DEAD = 101,
	//Further states to be added: sleep/poison/chaos
};

class CFighter {
public:
	CFighter(CRole *pRole) { this->pRole = pRole; }
	~CFighter() {}

public: // Actions
	void SetAction(BATTLEACT act, OBJID src, OBJID trg, OBJID u) { action = act; source = src; target = trg; use = u; }
	void ClearAction() { action = BATTLEACT_NONE; source = 0; target = 0; use = 0; }
	BATTLEACT GetAction() { return action; }
	OBJID GetTarget() { return target; }
	void SetTarget(OBJID id) { target = id; }
	bool IsActionSet() { return source != 0; }
protected:
	BATTLEACT action = BATTLEACT_NONE;
	OBJID source = 0;
	OBJID target = 0;
	OBJID use = 0;

public: //Awards
	void AddAwardExp(int e) { awardExp += e; if (awardExp < 0) awardExp = 0; }
	void AddAwardMoney(int m) { awardMoney += m; if (awardMoney < 0) awardMoney = 0; }
	void AddAwardRep(int r) { awardRep += r; if (awardRep < 0) awardRep = 0; }
	int GetAwardExp() { return awardExp; }
	int GetAwardMoney() { return awardMoney; }
	int GetAwardRep() { return awardRep; }
protected:
	int awardExp = 0;
	int awardMoney = 0;
	int awardRep = 0;

public: //IRole
	CRole* GetRole() { return pRole; }
	OBJID GetID() { return (GetObjType() == OBJ_PET) ? pRole->GetID() | 0x80000000 : pRole->GetID(); }
	int	GetObjType() { return pRole->GetObjType(); }
	int GetLevel() { return pRole->GetLev(); }

	void SetLife(int nLife) { pRole->SetLife(nLife); }
	int GetLife() { return pRole->GetLife(); }
	int GetMaxLife() { return pRole->GetMaxLife(); }
	void SetMana(int nMana) { pRole->SetMana(nMana); }
	int GetMana() { return pRole->GetMana(); }
	int GetMaxMana() { return pRole->GetMaxMana(); }

	int GetAttack() { return pRole->GetAttack(); }
	int GetDefence() { return pRole->GetDefence(); }
	int GetDexterity() { return pRole->GetDexterity(); }

protected:
	CRole *pRole;

public: //State
	FIGHTERSTATE GetState() { return state; }
	void SetState(FIGHTERSTATE s) { state = s; }

	void AddDamage(int dmg) { takeDamage += dmg; }
	int GetDamage() { return takeDamage; }
	bool WillDie() { return pRole->GetLife() <= takeDamage; }
	
	bool GetRanAway() { return bRanAway; }
	void SetRanAway(bool bRan) { bRanAway = bRan; }

	bool CanAct() { return IsAlive() && !bRanAway; }
	bool IsValidTarget() { return IsAlive() && !bRanAway; }
	bool IsAlive() { return !IsDead(); }
	bool IsDead() { return state == STATE_DEAD; }
protected:
	FIGHTERSTATE state = STATE_ALIVE;
	int doDamage = 0;
	int takeDamage = 0;
	bool bRanAway = false;

public: //Network
	bool SendMsg(CNetMsg* pMsg) { return pRole->SendMsg(pMsg); }
};

class CGameMap;
class CRole;
class CUser;
class CTeam;
class CMonster;

class CBattle {
protected:
	CBattle() {}
	~CBattle() {}
public:
	static		CBattle* CreateNpcBattle(PROCESS_ID idProcess, CUser* pUser);
	void		ReleaseByOwner() { delete this; }

public: //Teams
	typedef std::vector<CFighter*> FIGHTER_SET;

	void SetAttackerSet(CTeam *team);
	void AddAttacker(CUser *pUser);
	void SetDefenderSet(FIGHTER_SET enemies) { defenderSet = enemies; }
	void SetDefenderSet(MONSTER_SET enemies) { for (auto enemy : enemies) defenderSet.push_back(new CFighter(enemy)); }

	CFighter* GetFighter(OBJID id);
	bool IsAlly(CFighter* pFighter, CFighter *pCompare);
	bool IsEnemy(CFighter* pFighter, CFighter *pCompare) { return !IsAlly(pFighter, pCompare); }
public:
	typedef std::vector<FIGHTER_SET> JOINACT_SET;
	void AddBattleAction(BATTLEACT act, OBJID source, OBJID target, OBJID used);

	void ProcessRound();
	void EndRound();
	void EndBattle();
	void HandleBattleReward();

	void ProcessActionGroups();
	bool ProcessActionAttack(CFighter *pFighter, int group, int groupSize);
	CFighter* GetNextTarget(CFighter *pTarget);
	void CreateMonsterActs();
	void ReloadJoinAttackSet(bool useExisting = false);

	bool DoesAttackHit(CFighter *pTarget, CFighter *pSource, int groupSize);
	int CalculateDamage(CFighter *pSource, CFighter *pTarget, int &interaction);
	void DefeatEnemy(CFighter *pSource, CFighter *pTarget);

private:
	int GetAllyCount();
	int GetEnemyCount();

	JOINACT_SET joinActSet;

public: //Network
	void SendAllUsers(CNetMsg *pMsg);
	void SendCreateResponse();
	void SendEnemies();
	void SendFighters();
	void SendAllColors();

	void SendBattleAct_None(CFighter *pFighter);
	void SendBattleAct_Defend(CFighter *pFighter);
	void SendBattleAct_Run(CFighter *pFighter);

private:
	BATTLETYPE type;
	bool battleComplete = false;
	int round = 0;
	int group = 0;
	bool noTargets = false;
	bool allyKO = false;
	bool actionsReloaded = false;

	CGameMap* pMap;
	int battleX, battleY;

	FIGHTER_SET attackerSet;
	int attackerFormation = 0;
	FIGHTER_SET defenderSet;
	int defenderFormation = 0;

	PROCESS_ID m_idProcess;
};

bool OrderFightersByDex(CFighter* pFighter1, CFighter* pFighter2);