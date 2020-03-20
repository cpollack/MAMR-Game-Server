#include "Battle.h"

#include "MapGroup.h"
#include "User.h"
#include "Pet.h"
#include "UserManager.h"

#include "Network\MsgBattle.h"
#include "Network\MsgEnemy.h"
#include "Network\MsgFighter.h"
#include "Network\MsgColor.h"
#include "Network\MsgBattleAct.h"
#include "Network\MsgNormalAct.h"
#include "Network\MsgBattleRound.h"
#include "Network\MsgBattleResult.h"

CBattle* CBattle::CreateNpcBattle(PROCESS_ID idProcess, CUser* pUser) {
	ASSERT(pUser);

	CBattle* pBattle = new CBattle;
	pBattle->m_idProcess = idProcess;
	pBattle->type = BATTLETYPE_NPC;

	int x, y;
	x = pUser->GetPosX();
	y = pUser->GetPosY();

	MONSTER_SET monsterSet;
	CGameMap* pMap = pUser->GetMap();
	pMap->CreateMonstersForBattle(monsterSet, x, y);

	pBattle->SetDefenderSet(monsterSet);

	CTeam *pTeam = pUser->GetTeam();
	if (pTeam) {
		pBattle->SetAttackerSet(pTeam);
	}
	else {
		pBattle->AddAttacker(pUser);
	}

	pBattle->SendCreateResponse();
	pBattle->SendEnemies();
	pBattle->SendFighters();
	pBattle->SendAllColors();

	return pBattle;
}

void CBattle::SetAttackerSet(CTeam *pTeam) {
	if (!pTeam) return;

	int count = pTeam->GetMemberAmount();
	for (int i = 0; i < count; i++) {
		OBJID idMember = pTeam->GetMemberByIndex(i);
		CUser *pUser = UserManager()->GetUser(idMember);
		if (pUser) attackerSet.push_back(new CFighter(pUser));
	}
}

void CBattle::AddAttacker(CUser *pUser) {
	if (pUser) {
		attackerSet.push_back(new CFighter(pUser));

		CPet* pPet = pUser->GetMarchingPet();
		if (pPet) {
			attackerSet.push_back(new CFighter(pPet));
		}
	}
}

int CBattle::GetAllyCount() {
	/*int count = 0;
	for (auto ally : allySet) {
		count++;
		CPet* pPet = ((CUser*)ally)->GetMarchingPet();
		if (pPet) count++;
	}
	return count;*/
	return attackerSet.size();
}

int CBattle::GetEnemyCount() {
	return defenderSet.size();
}

CFighter* CBattle::GetFighter(OBJID id) {
	for (auto fighter : attackerSet) {
		if (fighter->GetID() == id) return fighter;
	}
	for (auto fighter : defenderSet) {
		if (fighter->GetID() == id) return fighter;
	}
	return nullptr;
}

bool CBattle::IsAlly(CFighter* pFighter, CFighter *pCompare) {
	FIGHTER_SET allySet;
	bool isAttackerSet = false;
	for (auto fighter : attackerSet) {
		if (fighter == pFighter) {
			isAttackerSet = true;
			break;
		}
	}
	if (isAttackerSet) allySet = attackerSet;
	else allySet = defenderSet;

	for (auto ally : allySet) {
		if (ally == pCompare) return true;
	}
	return false;
}

void CBattle::AddBattleAction(BATTLEACT act, OBJID source, OBJID target, OBJID used) {
	if (!source) {
		ASSERT("no idSource");
		return;
	}
	CFighter* pFighter = GetFighter(source);
	if (!pFighter) {
		ASSERT("invalid pFighter");
		return;
	}

	pFighter->SetAction(act, source, target, used);

	CMsgBattleAct msg;
	CUser* pUser = (pFighter->GetObjType() == OBJ_USER) ? (CUser*)pFighter->GetRole() : pFighter->GetRole()->QueryOwnerUser();
	if (msg.Create(act, round, source, target, used, pUser))
		SendAllUsers(&msg);

	int count = 0;
	for (auto ally : attackerSet) {
		if (ally->IsActionSet()) count++;
	}
	if (count == GetAllyCount()) ProcessRound();
}

void CBattle::ProcessRound() {
	CreateMonsterActs();
	ReloadJoinAttackSet();
	ProcessActionGroups();

	EndRound();
	if (noTargets) EndBattle();
}

void CBattle::EndRound() {
	CMsgBattleRound msg;
	if (msg.Create(&attackerSet, &defenderSet))
		SendAllUsers(&msg);

	for (auto fighter : attackerSet) fighter->ClearAction();
	for (auto fighter : defenderSet) fighter->ClearAction();
}

void CBattle::EndBattle() {
	BATTLERESULT result;
	
	if (GetNextTarget(attackerSet[0])) result = BATTLERESULT_WIN;
	else result = BATTLERESULT_LOSE;

	for (auto fighter : attackerSet) {
		if (fighter->GetObjType() == OBJ_USER) {
			//check if ran?
			CMsgBattle msgBattle;
			if (msgBattle.Create(fighter->GetID(), BATTLESTATE_END, 0, 0))
				fighter->SendMsg(&msgBattle);


			//Total result data
			int money = 0;
			CUser *pUser = (CUser*)fighter->GetRole();
			money = fighter->GetAwardMoney();
			
			int petLife = 0;
			int petLoy = 0;
			int petExp = 0;
			CPet *pPet = pUser->GetMarchingPet();
			if (pPet) {
				CFighter *petFighter = GetFighter(pPet->GetID() | 0x80000000);
				if (petFighter) {
					petLife = pPet->GetLife();
					petLoy = pPet->GetLoyalty();
					petExp = petFighter->GetAwardExp();
					money += petFighter->GetAwardMoney();
				}
			}

			CMsgBattleResult msgResult;
			if (msgResult.Create(result, money, pUser->GetLife(), pUser->GetMana(), fighter->GetAwardRep(), fighter->GetAwardExp(), petLife, petLoy, petExp))
				fighter->SendMsg(&msgResult);
		}

		//check if victory or loss
		//apply kill rewards
		//battle award action
	}
}

void CBattle::CreateMonsterActs() {
	FIGHTER_SET targetSet;
	for (auto fighter : attackerSet) {
		if (fighter->IsAlive()) targetSet.push_back(fighter);
	}

	for (auto monster : defenderSet) {
		int nTarget = RandGet(targetSet.size());
		CFighter *pTarget = targetSet[nTarget];
		monster->SetAction(BATTLEACT_ATTACK, monster->GetID(), pTarget->GetID(), 0);
	}
}

void CBattle::ReloadJoinAttackSet(bool useExisting) {
	FIGHTER_SET fightersByDex;

	if (useExisting) {
		for (auto actSet : joinActSet) {
			for(auto fighter : actSet) fightersByDex.push_back(fighter);
		}
	}
	else {
		for (auto ally : attackerSet) fightersByDex.push_back(ally);
		for (auto enemy : defenderSet) fightersByDex.push_back(enemy);	
	}
	std::sort(fightersByDex.begin(), fightersByDex.end(), OrderFightersByDex);

	FIGHTER_SET actionSet;
	joinActSet.clear();

	//Defenders go first
	FIGHTER_SET::iterator itr;
	itr = fightersByDex.begin();
	while (itr != fightersByDex.end()) {
		CFighter *pFighter = *itr;
		if (pFighter->GetAction() == BATTLEACT_DEFEND) {
			actionSet.push_back(pFighter);
			joinActSet.push_back(actionSet);
			actionSet.clear();
			itr = fightersByDex.erase(itr);
		}
		else itr++;
	}

	while (fightersByDex.size() > 0) {
		CFighter *pFighter = fightersByDex.front();
		fightersByDex.erase(fightersByDex.begin());

		if (pFighter->GetState() == STATE_DEAD) continue;
		actionSet.push_back(pFighter);
		
		//Only attacks join, all other actions happen 'solo'
		if (pFighter->GetAction() != BATTLEACT_ATTACK || fightersByDex.size() == 0) {
			joinActSet.push_back(actionSet);
			actionSet.clear();
			continue;
		}

		FIGHTER_SET::iterator itr = fightersByDex.begin();
		while (fightersByDex.size() > 0 && itr != fightersByDex.end()) {
			CFighter *nextFighter = *itr;
			if (nextFighter->GetState() == STATE_DEAD) {
				itr = fightersByDex.erase(itr);
				continue;
			}

			//Next fighter is an ally and has the same target
			if (IsAlly(pFighter, nextFighter) && pFighter->GetTarget() == nextFighter->GetTarget()) {
				//If ally is within 20% of enemy dex, they can join the attack group
				CFighter *pTarget = GetFighter(pFighter->GetTarget());
				if (pTarget) {
					if (nextFighter->GetDexterity() > pTarget->GetDexterity() * 0.8) {
						actionSet.push_back(nextFighter);
						itr = fightersByDex.erase(itr);
						continue;
					}
					else break; //if this fighter doesn't have enough dex, neither will subsequent ones
				}
			}
			itr++;
		}

		joinActSet.push_back(actionSet);
		actionSet.clear();
	}
}

void CBattle::ProcessActionGroups() {
	//iterate attack groups and send packets as you go
	JOINACT_SET::iterator actSetItr = joinActSet.begin();
	int group = 0;
	CMsgNormalAct msg;

	while (actSetItr != joinActSet.end()) {
		bool targetSlain = false;

		for (auto fighter : *actSetItr) {
			if (fighter->IsDead()) continue;

			switch (fighter->GetAction()) {
			case BATTLEACT_NONE:
				if (msg.Create(BATTLEACT_NONE, group, fighter->GetState(), 0, fighter->GetID(), 0, 0, 0, 0, 0))
					SendAllUsers(&msg);
				break;

			case BATTLEACT_ATTACK:
				targetSlain = ProcessActionAttack(fighter, group, actSetItr->size());
				break;

			case BATTLEACT_DEFEND:
				if (msg.Create(BATTLEACT_DEFEND, group, fighter->GetState(), 0, fighter->GetID(), 0, 0, 0, 0, 0))
					SendAllUsers(&msg);
				break;

			case BATTLEACT_ITEM:
				break;
			case BATTLEACT_RUN:
				break;
			case BATTLEACT_SPECIAL:
				break;
			case BATTLEACT_CAPTURE:
				break;
			}

			if (actionsReloaded) break;
		}

		if (targetSlain) {
			CFighter *pTarget = GetFighter(actSetItr->front()->GetTarget());

			pTarget->SetState(STATE_DEAD);

			for (auto fighter : *actSetItr) DefeatEnemy(fighter, pTarget);

			//Verify if the last opponent has been defeated, trigger battle end if so
			CFighter *validTarget = GetNextTarget(pTarget);
			if (!validTarget) noTargets = true;
		}

		if (noTargets) {
			//exit loop and initiate end of battle
			break;
		}

		if (actionsReloaded) {
			actSetItr = joinActSet.begin();
			continue;
		}

		actSetItr = joinActSet.erase(actSetItr);
		group++;
	}
}

bool CBattle::ProcessActionAttack(CFighter *pFighter, int group, int groupSize) {
	if (!pFighter || !pFighter->GetTarget()) return false;

	CFighter *pTarget = GetFighter(pFighter->GetTarget());
	if (!pTarget) return false;

	if (pTarget->IsDead()) {
		pTarget = GetNextTarget(pTarget);
		if (!pTarget) {
			noTargets = true;
			return false;
		}

		//Retarget all fighters who lost their original target
		for (auto actSet : joinActSet) {
			for (auto fighter : actSet) {
				if (fighter->GetTarget() == pTarget->GetID()) {
					pFighter->SetTarget(pTarget->GetID());
				}
			}
		}
		// Reloads the remaining fighters into their new ordering
		ReloadJoinAttackSet(true);
		actionsReloaded = true;
		return false;
	}

	if (!DoesAttackHit(pFighter, pTarget, groupSize)) {
		CMsgNormalAct msg;
		if (msg.Create(BATTLEACT_ATTACK, group, pFighter->GetState(), pTarget->GetState(), pFighter->GetID(), pTarget->GetID(), 0, 0, 0, 0))
			SendAllUsers(&msg);
		return false;
	}
	
	int interaction;
	int dmg = CalculateDamage(pFighter, pTarget, interaction);
	pTarget->AddDamage(dmg);
	if (pTarget->WillDie()) {
		//Target takes more dmg then life, inform client target dies, but dont change fighter status yet
		CMsgNormalAct msg;
		if (msg.Create(BATTLEACT_ATTACK, group, pFighter->GetState(), STATE_DEAD, pFighter->GetID(), pTarget->GetID(), dmg, 0, interaction, 0))
			SendAllUsers(&msg);
		return true;
	}

	//Target didn't die yet
	CMsgNormalAct msg;
	if (msg.Create(BATTLEACT_ATTACK, group, pFighter->GetState(), pTarget->GetState(), pFighter->GetID(), pTarget->GetID(), dmg, 0, interaction, 0))
		SendAllUsers(&msg);
	return false;
}

CFighter* CBattle::GetNextTarget(CFighter *pTarget) {
	FIGHTER_SET *targetSet;
	if (IsAlly(pTarget, attackerSet[0])) targetSet = &attackerSet;
	else targetSet = &defenderSet;

	for (auto fighter : *targetSet) if (fighter->IsAlive()) return fighter;

	return nullptr;
}

///////////////////////////////// Battle Calcs
bool CBattle::DoesAttackHit(CFighter *pSource, CFighter *pTarget, int groupSize) {
	if (groupSize >= 4) return true;
	if (pTarget->GetObjType() == OBJ_MONSTER && groupSize >= 2) return true;

	int targetDex = pTarget->GetDexterity();
	int sourceDex = pSource->GetDexterity();

	if (targetDex <= 0) targetDex = 1;
	if (sourceDex <= 0) sourceDex = 1;

	int hitChance = 0;
	if (sourceDex - targetDex <= 0) {
		double dif = sourceDex - targetDex;
		hitChance = dif * 50.0 / sourceDex + 70;
	}
	else {
		double dif = sourceDex - targetDex;
		hitChance = dif * 50.0 / targetDex + 70;
	}
	hitChance *= groupSize;

	if (hitChance > 95) hitChance = 95;
	if (hitChance < 10) hitChance = 10;
	if (RandGet(100) < hitChance) return true;

	return false;
}

int CBattle::CalculateDamage(CFighter *pSource, CFighter *pTarget, int &interaction) {
	int attack = pSource->GetAttack();
	
	int defence = pTarget->GetDefence();
	if (pTarget->GetAction() == BATTLEACT_DEFEND) defence *= 2;

	int damage = 1;
	interaction = pSource->GetRole()->GetElementInteraction(pTarget->GetRole());
	switch (interaction) {
	case INTERACTION_NONE:
	case INTERACTION_GENERATE:
	case INTERACTION_GENERATED:
		if (2 * attack > defence) damage = 2 * attack - defence;
		break;
	case INTERACTION_RESTRAIN:
		if (2 * attack > defence / 2) damage = 2 * attack - defence / 2;
		break;
	case INTERACTION_RESTRAINED:
		if (2 * attack > defence * 2) damage = 2 * attack - defence * 2;
		break;
	case INTERACTION_SUPER_RESTRAIN:
		if (3 * attack > defence / 2) damage = 3 * attack - defence / 2;
		break;
	case INTERACTION_SUPER_RESTRAINED:
		if (attack > defence * 3) damage = attack - defence * 3;
		break;
	}

	return damage;
}

void CBattle::DefeatEnemy(CFighter *pSource, CFighter *pTarget) {
	if (!pSource || !pTarget || pSource->GetObjType() == OBJ_MONSTER) return;

	int srcLevel = pSource->GetLevel();
	int trgLevel = pTarget->GetLevel();
	int lvlDif = srcLevel - trgLevel;

	int exp = (pow(trgLevel, 2) * 0.012) + (5 * trgLevel);
	if (srcLevel > trgLevel) {
		if (lvlDif > 95) lvlDif = 95;
		exp = exp * (100 - lvlDif) / 100;
		if (exp <= 0) exp = 0;
	}

	pSource->AddAwardExp(exp);

	if (pSource->GetObjType() == OBJ_USER) {
		int money = sqrt(trgLevel) * 1.7;
		pSource->AddAwardMoney(money);

		int rep = lvlDif < 1 ? 1 : lvlDif;
		CUser *pUser = (CUser*)pSource->GetRole();
		if (pUser->GetRankType() > 0) {
			rep = min(rep, 50);
		}
		else {
			rep = min(rep, 150);
		}
		pSource->AddAwardRep(rep);
	}
}


/////////////////////////////////  NETWORK

// Send message to users on both sides of combat
void CBattle::SendAllUsers(CNetMsg *pMsg) {
	if (!pMsg) return;

	for (auto fighter : attackerSet) {
		if (fighter->GetObjType() == OBJ_USER) fighter->SendMsg(pMsg);
	}
	for (auto fighter : defenderSet) {
		if (fighter->GetObjType() == OBJ_USER) fighter->SendMsg(pMsg);
	}
}

void CBattle::SendCreateResponse() {
	int fighters = GetAllyCount() + GetEnemyCount();

	for (auto fighter : attackerSet) {
		if (fighter->GetObjType() == OBJ_USER) {
			CMsgBattle msg;
			msg.Create(fighter->GetID(), BATTLESTATE_CONFIRM, fighters, attackerFormation);
			fighter->SendMsg(&msg);
		}
	}
}

void CBattle::SendEnemies() {
	CMsgEnemy msg;
	if (msg.Create(defenderSet))
		SendAllUsers(&msg);
}

void CBattle::SendFighters() {
	for (auto fighter : attackerSet) {
		if (fighter->GetObjType() == OBJ_USER) {
			CMsgFighter msg;
			if (msg.Create((CUser*)fighter->GetRole()))
				SendAllUsers(&msg);
		}
	}
}

void CBattle::SendAllColors() {
	for (auto ally : attackerSet) {
		CMsgColor msg;
		if (msg.Create(ally->GetRole()))
			SendAllUsers(&msg);
	}
	for (auto enemy : defenderSet) {
		CMsgColor msg;
		if (msg.Create(enemy->GetRole()))
			SendAllUsers(&msg);
	}
}

// Vector sorting - Order Descending
bool OrderFightersByDex(CFighter* pFighter1, CFighter* pFighter2) {
	return !(pFighter1->GetDexterity() < pFighter2->GetDexterity());
}