// User.cpp: implementation of the CUser class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include "Network/AllMsg.h"
#include "Network/MsgDataArray.h"
#include "Package.h"
#include "User.h"
#include "MapGroup.h"
#include "Network/netmsg.h"
#include "ItemType.h"
#include "team.h"
#include "StatusOnce.h"
#include "Transformation.h" //What is this?
//#include "WantedList.h"
//#include "PoliceWanted.h"
//#include "MapTrap.h"
#include "I_MessagePort.h"
#include "DeadLoop.h"
#include "AutoPtr.h"
#include "I_Shell.h"
//#include "MercenaryTaskData.h"
//#include "MercenaryTask.h"
#include "math.h"
#include "TaskDetail.h"
#include "Pet.h"



//extern long	g_sKickoutCheat;
long	g_sKickoutCheat = 0;
//////////////////////////////////////////////////////////////////////
const int	ADD_ENERGY_STAND_SECS			= 5;			// ÿ����������һ��
const int	ADD_ENERGY_STAND				= 50;			// վ����������
const int	DEL_ENERGY_PELT_SECS			= 3;			// ����״̬ÿ3���һ��
const int	DEL_ENERGY_PELT					= 2;			// ÿ�ο�2��
const int	KEEP_STAND_MS					= 1500;			// վ����Ҫ��ʱ�䣬վ�Ⱥ��ܵ�ס��ҡ�
const int	CRUSH_ENERGY_NEED				= 100;			// ������Ҫ���ٵ�
const int	CRUSH_ENERGY_EXPEND				= 100;			// �������Ķ��ٵ�
const int	SYNWAR_PROFFER_PERCENT			= 1;			// �����ӵþ���ֵ�İٷֱ�
const int	SYNWAR_MONEY_PERCENT			= 2;			// �����ӵ�Ǯ�İٷֱ�
const int	MIN_SUPERMAP_KILLS				= 25;			// ��˫�б����
//const int	NEWBIE_LEVEL					= 70;			// ���ֵĵȼ�
const int	VETERAN_DIFF_LEVEL				= 20;			// ���ֵĵȼ���
//const int	_MIN_TUTOR_LEVEL				= 50;							// ��ʦ��͵ȼ�
const int	HIGHEST_WATER_WIZARD_PROF		= 135;			// ˮ����
const int	MOUNT_ADD_INTIMACY_SECS			= 3600;			// 
const int	INTIMACY_DEAD_DEC				= 20;			// 
const int	SLOWHEALLIFE_MS					= 1000;							// ��ҩ��Ѫ��������ȥ�ĺ�������
const int	AUTOHEALLIFE_TIME				= 10;							// ÿ��10���Զ���Ѫ1�Ρ�
const int	AUTOHEALLIFE_EACHPERIOD			= 6;							// ÿ�β�Ѫ6��
const int	AUTOHEAL_MAXLIFE_TIME			= 60;							// ÿ��60���Զ��ָ�maxlife
const int	AUTOHEAL_MAXLIFE_FLESH_WOUND	= 16;							// ����״̬��ÿ�λָ�maxlife��ǧ�ֱ�
const int	AUTOHEAL_MAXLIFE_GBH			= 4;							// ����״̬��ÿ�λָ�maxlife��ǧ�ֱ�
const int	TICK_SECS						= 10;
const int	MAX_PKLIMIT						= 10000;						// PKֵ�������С����(���ؾ�)  //change huang 2004.1.11
const int	PILEMONEY_CHANGE				= 5000;							// �����ֽ�䶯(��Ҫ��ʱ����)
const int	_ADDITIONALPOINT_NUM			= 3;							// ��1���Ӷ������Ե�
const int	PK_DEC_TIME						= 60;							// ÿ���60�뽵��pkֵ     //change huang 2004.1.11   
const int   PKVALUE_DEC_ONCE                = 1;                            // ��ʱ�����PKֵ��        
const int	PKVALUE_DEC_ONCE_IN_PRISON		= 3;							// ��ʱ�����PKֵ�����ڼ����е����
const int	PKVALUE_DEC_PERDEATH			= 10;							// ��PK��һ�μ��ٵ�PKֵ
const int	TIME_TEAMPRC					= 5;							// ������Ϣ�����ʱ��
const int	DURABILITY_DEC_TIME				= 12;							// ÿ12�뽵��һ�ΰ�ʱ�����ĵ�װ���;ö�
const int	USER_ATTACK_SPEED				= 800;							// ���ͽ�ֹ���Ƶ��
const int	POISONDAMAGE_INTERVAL			= 2;							// �ж�ÿ2����Ѫһ��
const int	WARGHOST_CHECK_INTERVAL			= 10;							// ÿ��10����һ��ս��ȼ�(��������)
const int	AUTO_REBORN_SECS				= 30;							// ���ʯ30����Զ�ʹ��
const int	INC_POTENTIAL_SECS				= 6*60;							// ÿ��6��������һ��Ǳ��
const int	INC_POTENTIAL_NUM				= 1;							// ÿ������1��Ǳ��
const int	ADD_POTENTIAL_RELATIONSHIP		= 6;							// ��ϵֵ֮��ÿ�ﵽ6����1��Ǳ��ֵ

// add by zlong 2003-11-28
const int	SPRITE_ADD_EXP_SECS				= 60;			//Ԫ�ؾ���ÿ��������һ�ξ���
const int	SPRITE_ADD_EXP					= 1;			//������������

const int	EUDEMON_ADD_FIDELITY_SECS		= 60*6;			// ����ÿ6��������һ�����ܶ�
const int	EUDEMON_ADD_FIDELITY			= 1;			// ÿ�����ӵ����ܶ�
const int	MAX_EUDEMON_FIDELITY			= 1000;			// ������ܶ�1000
const int	MAX_RETURN_BORN_POS_LEV			= 4;			// �����󷵻س�ʼ����������ȼ�
//////////////////////////////////////////////////////////////////////
MYHEAP_IMPLEMENTATION(CUser,s_heap)
char	szActionTable[]			= _TBL_ACTION;
char	szTaskTable[]			= _TBL_TASK;
//char	szMagicTypeTable[]		= _TBL_MAGICTYPE;
char	szTrackTable[]			= _TBL_TRACK;
char	szBonusTable[]			= _TBL_BONUS;
char	szAddPointTable[]		= _TBL_POINTALLOT;
char	szTrapTypeTable[]		= _TBL_TRAPTYPE;
char	szMonsterTypeTable[]	= _TBL_MONSTERTYPE;
char	szRebirthTable[]		= _TBL_REBIRTH;	

//////////////////////////////////////////////////////////////////////
// Construction/Destruction CHEAT
//////////////////////////////////////////////////////////////////////
bool CUser::SetCheatLevel(int nLevel)
{
#if	!defined(_DEBUG)
	if(IsGM() || GetLev() < LOGIN_FREE_LEVEL)
		return false;
#endif

	// init count 
	if(m_nCheatLevel == 0)
		m_nCheatCount = UserManager()->GetCheatCount(GetID());


	// is max?
	if(nLevel <= m_nCheatLevel)
		return false;

	if(!IsCheater(_TYPE_MAGIC))
	{
		m_nCheatLevel	= nLevel;
		if(m_nCheatLevel + m_nCheatCount*10 >= 30)
		{
			SetCheatMark(_TYPE_MAGIC, 0);

			// add to manager
			int nAmount, nTimes;
			UserManager()->AddCheat(GetID(), &nAmount, &nTimes);
			LOGCHEAT("magic: user[%s], account[%u], type[zffy], level[%d], amount[%d], times[%d]", GetName(), GetAccountID(), nLevel, nAmount, nTimes);
			return true;
		}
	}
	else
	{
		m_nCheatLevel	= nLevel;
		LOGCHEAT("magic: user[%s], account[%u], type[zffy], level[%d]", GetName(), GetAccountID(), nLevel);
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsCheater(OBJID idKind)
{
	CHECKF(idKind < 32);

	return (m_maskCheat & (1<<idKind)) != 0;
}

char* g_setName[] = { "_TYPE_MAGIC", "_TYPE_WS", "_TYPE_FY", "_TYPE_USE_LIFE", "_TYPE_USE_MANA", 
		"null", "null", "null", "null", "null", "null", "null", "null", "null", "null", 
		"null", "null", "null", "null", "null", "null", "null", "null", "null", "null", 
		"null", "null", "null", "null", "null", "null", "null", "null", "null", "null",  };
//////////////////////////////////////////////////////////////////////
void CUser::SetCheatMark(OBJID idCheatKind, DWORD dwCheatMark)
{
	CHECK(idCheatKind < 32);

	LOGCHEAT("client: user[%s], account[%u], type[%s], mark[%d]", GetName(), GetAccountID(), g_setName[idCheatKind], dwCheatMark);

	m_maskCheat = m_maskCheat | (1<<idCheatKind);
}

//////////////////////////////////////////////////////////////////////
void CUser::KickoutCheat(OBJID idKind)
{
	CHECK(idKind < 32);
	CHECK(IsCheater(idKind));

#if	!defined(_DEBUG)
//	if(UserManager()->GetCheatAmount() < 5)
//		return ;
#endif

	// kickout
	if(GetLev() >= LOGIN_FREE_LEVEL && (g_sKickoutCheat&(1<<idKind)) != 0 )
	{
#if	defined(_DEBUG)
		SendSysMsg("��CHEAT��");
#endif
		UserManager()->KickOutSocket(m_idSocket, "cheat");
	}
	else
	{
		LOGCHEAT("need kick: user[%s], account[%u], type[%s]", GetName(), GetAccountID(), g_setName[idKind]);
	}
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsMagicAtkCheat (OBJID idTarget, int nTargetX, int nTargetY, DWORD dwTimeStamp)
{
	IRole* pRole = RoleManager()->QueryRole(idTarget);
	if (!pRole)
		return false;

	// action mode test
	{
		if (dwTimeStamp-m_dwLastJump < 100)
		{
			//::MyLogSave("gmlog/test", "---------suspect action found!");
			return true;
		}
	}

	// interval test
	CONST int TEST_SIZE = 8;
	m_setActionTime.push_back(dwTimeStamp);

	if (m_setActionTime.size() > TEST_SIZE)
		m_setActionTime.pop_front();

	if (m_setActionTime.size() != TEST_SIZE)
		return false;

	{
		deque<int> setDeltaTime;
		for (int i=1; i<TEST_SIZE; i++)
			setDeltaTime.push_back(m_setActionTime[i]-m_setActionTime[i-1]);		

		CONST int SUSPECT_TIME = 20;

		int nSuspectCount = 0;
		for (int i=1; i<TEST_SIZE-1; i++)
		{
			if (abs(setDeltaTime[0] - setDeltaTime[i]) <= SUSPECT_TIME)
				nSuspectCount++;
		}

		if (nSuspectCount >= TEST_SIZE-2)
		{
			//::MyLogSave("gmlog/test", "---------repeat action found!");
			return true;
		}
	}

	// target pos test
	if (nTargetX == 0 && nTargetY == 0)
		return true;

	// dislocation test
	// ....
	return false;	
}

//////////////////////////////////////////////////////////////////////
void CUser::DoCheaterPunish	(int nData/* = 0*/)
{
	CONST OBJID idMapCheaterPrison = 6010;
	CONST int nPosX = 34, nPosY = 74;

	if (this->GetMapID() == idMapCheaterPrison)
		return;

	this->SetRecordPos(idMapCheaterPrison, nPosX, nPosY, true);
	this->FlyMap(idMapCheaterPrison, nPosX, nPosY);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUser::CUser()
{
	SetObjType(OBJ_USER);

	m_link.Init(this);
	m_nStep			= STEP_LOGIN;		// ��ͼ�������ǽ����ͼ

	// item ----------------------
	m_pWeapon		= NULL;
	m_pArmor		= NULL;
	m_pShoes		= NULL;
	m_pBodyAccessory = NULL;
	m_pHeadAccessory = NULL;

	m_bUpdateWeight	= true;			// true: ��Ҫ���¼���

	m_nPose			= 0;	//DEFAULT_LOGIN_POSE;
	m_nEmotin		= 0;	//DEFAULT_LOGIN_EMOTION;

	m_dwXP			= 0;
	m_pTeam			= NULL;

	// tick -----------
	m_dwFirstServerTick	= 0;
	m_dwLastServerTick	= 0;

	m_dwLastClientTick	= 0;
	m_dwFirstClientTick	= 0;
	m_dwLastCoolShow	= 0;

	m_dwLastRcvClientTick = 0;

	// interface
	m_ifaceSquareDeal.m_pParent	= this;

	//m_pBattleSystem	= NULL;
	m_pStorage		= NULL;
	m_idTaskNpc		= ID_NONE;
	m_idTaskItem	= ID_NONE;
	m_idTaskItemAction	= ID_NONE;
	m_bDebugAction	= false;
	m_pPackage		= CUserPackage::CreateNew();

	//m_pUserWeaponSkillSet	= CUserWeaponSkillSet::CreateNew(true);
	m_pMagic		= NULL;
	m_pSyn			= NULL;
	m_bGhost		= false;

	m_bHaveLeaveWord	= true;
	m_pTransformation	= NULL;

//	m_bSynchro		= true;
	m_pBooth		= NULL;
	m_idxLastArrow	= -1;		// error

	// foot print
	m_tFootPrint	= 0;
	m_posFootPrint.x	= 0;
	m_posFootPrint.y	= 0;

	// superman list
	m_nCurrSupermanKills	= 0;
	m_nTopSupermanKills		= 0;
	m_nSupermanOrder		= 0;

	// cheat test
	m_dwLastJump = 0;
	m_dwMsgCount = 0;

	// tutor
	m_pTutor	= NULL;
	m_dwExpToTutor	= 0;
	
	// mine
	m_pMineTarget	= NULL;

	//���ɷ�װ��armor type;
	m_nSynDressArmorType = 0;
	m_pTaskDetail	= NULL;
	m_bIsEnableWarGhostExp = false;

	m_nLinkValue		= 0;
}

//////////////////////////////////////////////////////////////////////
CUser::~CUser()
{
	LeaveMapGroup();
	//if (m_pBattleSystem)
	//{
	//	delete m_pBattleSystem;
	//	m_pBattleSystem	= NULL;
	//}
	if(m_pStorage)
		m_pStorage->Release();

	if (m_pPackage)
		m_pPackage->Release();

	//if (m_pUserWeaponSkillSet)
	//	m_pUserWeaponSkillSet->Release();

	if (m_pMagic)
		m_pMagic->ReleaseByOwner();
	if (m_pSyn)
		m_pSyn->ReleaseByOwner();

	SAFE_RELEASE (m_setStatus);
	
	if (m_pTeam)
		m_pTeam->ReleaseByOwner();
	if (m_pTransformation)
		m_pTransformation->Release();

	if(m_pTaskDetail)
		m_pTaskDetail->Release();

	DEBUG_TRY
	Announce()->DeleteAnnounceByUserID(this->GetID(),false);
    DEBUG_CATCH("Announce()->DeleteAnnounceByUserID(this->GetID()) ERROR!");

	this->DestroyBooth();
}

//////////////////////////////////////////////////////////////////////
CUser* CUser::CreateNewUser(PROCESS_ID idProcess, SOCKET_ID idSocket, UserInfoStruct* pInfo)	// join from other map_group
{
	CHECKF(CMapGroup::IsValidMapGroupProcessID(idProcess));
	CHECKF(pInfo);

	CUserPtr pUser = CUser::CreateNew();
	CHECKF(pUser);
	if(pUser)
	{
		pUser->m_idProcess	= idProcess;
		pUser->m_idSocket	= idSocket;
		memcpy(&pUser->m_data.m_Info, pInfo, sizeof(UserInfoStruct));
		pUser->m_data.m_pRes = MapGroup(idProcess)->QueryDataDefault()->GetUserData()->CreateNewRecord(pInfo->id);
		if(!pUser->m_data.m_pRes)
		{
			pUser->ReleaseByOwner();
			return NULL;
		}
	}

	pUser->Init();
	pUser->QueryEnemy()->Create(idProcess, pUser);
	pUser->m_pMap	= NULL;			//? ��֤Ϊ�գ����ڿ�������������

	// transformation
	if(pUser->m_data.m_Info.dwMonsterType && pUser->m_data.m_Info.dwMonsterSecs)
	{
		ASSERT(pUser->Transform(pUser->m_data.m_Info.dwMonsterType, pUser->m_data.m_Info.dwMonsterSecs));
	}

	return pUser;
}

//////////////////////////////////////////////////////////////////////
// login, return false: logout_user
bool CUser::EnterMap()
{
	if(m_nStep != STEP_LOGIN)
		return false;

	SendLight();

	CMapPtr pMap = GetMap();
	if(pMap)
	{
		pMap->EnterRoom(this->QueryMapThing(), WITH_BLOCK);
	
		//pMap->SendRegionInfo(this);

		pMap->SendMapInfo(this);
		pMap->SendBlockInfo((IRole*)this); //Send after changing maps, not before

		UpdateBroadcastSet();

		SendSelfToBlock();
	}

//	if(!GetMap()->IsWingEnable())
//		QueryStatusSet()->DelObj(STATUS_WING);

	// �����г���ͼ���XPFULL״̬
	if (pMap && pMap->IsBoothEnable())
		DetachStatus((IRole*)this, STATUS_XPFULL);

	CRole::AttachStatus(this->QueryRole(), STATUS_PK_PROTECT, 0, CHGMAP_LOCK_SECS);
//	m_tLock.Startup(CHGMAP_LOCK_SECS);
	m_nStep = STEP_ENTERMAP;
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::SendSelfToBlock()
{
	// brocast my info
	CMsgPlayer msg;
	if (msg.Create((IRole*)this))
		this->BroadcastRoomMsg(&msg, EXCLUDE_SELF);

	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::SetMaxLifePercent(int nPercent, BOOL bUpdate /*= TRUE*/)
{
	bool bAboveHalfLife = this->GetLife()*2 >= this->GetMaxLife();
	m_data.SetMaxLifePercent(nPercent);		// ��SetMaxLifePercent��֤������1/8
	bool bBelowHalfLife = this->GetLife()*2 < this->GetMaxLife();
	bool bSpeedChanged = (bAboveHalfLife && bBelowHalfLife) || (!bAboveHalfLife && !bBelowHalfLife);

	// ֪ͨ�ͻ���
	CMsgUserAttrib	msg;
	if (msg.Create(GetID(), _USERATTRIB_MAXLIFE, GetMaxLife()))
	{
		// �Ƿ�Ӱ�쵽�ٶȣ�
		IStatus* pStatus = this->QueryStatus(STATUS_SLOWDOWN2);
		if (pStatus && bSpeedChanged)
			msg.Append(_USERATTRIB_SPEED, AdjustSpeed(GetSpeed()));

		SendMsg(&msg);
	}
	const bool bMaxLife = true;
	this->BroadcastTeamLife(bMaxLife);	
}

//////////////////////////////////////////////////////////////////////
// modify attrib
//////////////////////////////////////////////////////////////////////
bool CUser::AddAttrib(int idxAttr, __int64 i64Data, int nSynchro)
{
	CMsgUserAttrib	msg;
	IF_NOT (msg.Create(GetID(), _USERATTRIB_NONE, 0))			// _USERATTRIB_NONE : �����
		return false;

	if(i64Data)
	{
		switch(idxAttr)
		{
		case	_USERATTRIB_LEV:
			{
				IF_NOT (i64Data >= 0)
					return false;

				int nOldLev = this->GetLev();
				int nNewLev = __min(MAX_USERLEV, nOldLev+i64Data);
				m_data.SetLev(nNewLev, true);
				IF_NOT (msg.Append(_USERATTRIB_LEV, this->GetLev()))
					return false;

				// �ȼ���70�����·����仯����Ҫ��������ֵ�洢��ʽ
				if (nNewLev > ADJUST_EXPFORMAT_LEVEL && nOldLev <= ADJUST_EXPFORMAT_LEVEL)
					this->SetAttrib(_USERATTRIB_EXP, this->GetExp()/10, nSynchro);
				else if (nNewLev <= ADJUST_EXPFORMAT_LEVEL && nOldLev > ADJUST_EXPFORMAT_LEVEL)
					this->SetAttrib(_USERATTRIB_EXP, this->GetExp()*10, nSynchro);
			}
			break;

		case	_USERATTRIB_LIFE:
			{
				if ((int)this->GetLife() + i64Data <= 0)
				{
					//this->SetStatus(STATUS_DIE);
					SetLife(0);
				}
				else
				{
					SetLife(__min(this->GetMaxLife(), this->GetLife() + i64Data));
				}

				// Ѫ����70%��ʱ������״̬
				if (GetLife()*100/GetMaxLife() > MAX_FRENZY_LIFE_PERCENT)
				{
					CRole::DetachStatus(this->QueryRole(), STATUS_FRENZY);
				}
				
				IF_NOT (msg.Append(_USERATTRIB_LIFE, this->GetLife()))
					return false;
			}
			break;
		case	_USERATTRIB_MANA:
			{
				if ((int)this->GetMana() + i64Data <= 0)
					m_data.SetPower(0);
				else
					m_data.SetPower(__min(this->GetMaxMana(), this->GetMana() + i64Data));

				IF_NOT (msg.Append(_USERATTRIB_MANA, this->GetMana()))
					return false;
			}
			break;
		case	_USERATTRIB_EXP:
			{
				// exp allow negative
				m_data.SetExp(this->GetExp() + i64Data);
				IF_NOT (msg.Append(_USERATTRIB_EXP, this->GetExp()))
					return false;
			}
			break;
		case	_USERATTRIB_PK:
			{
				// pk allow negative
				m_data.SetPk(this->GetPk() + i64Data);
				IF_NOT (msg.Append(_USERATTRIB_PK, this->GetPk()))
					return false;
			}
			break;			
		case	_USERATTRIB_MONEY:
			{
				if (i64Data < 0 && (int)this->GetMoney() + i64Data < 0)
				{
					// if not enough money, return false only
					return false;
				}
				else
					m_data.SetMoney(GetMoney() + i64Data);

				IF_NOT (msg.Append(_USERATTRIB_MONEY, this->GetMoney()))
					return false;
			}
			break;
		case _USERATTRIB_ADDPOINT:
			{
				if (i64Data < 0)
				{
					return false;	// ���Դ�
				}
				m_data.SetAddPoint(m_data.GetAddPoint()+i64Data);
				IF_NOT (msg.Append(_USERATTRIB_ADDPOINT, this->GetAddPoint()))
					return false;
			}
			break;
		/*case _USERATTRIB_SOUL:
			{
				m_data.SetSoul(__max(0, m_data.GetSoul()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_SOUL, this->GetSoul()))
					return false;
			}
			break;*/
		case _USERATTRIB_PHYSIQUE:
			{
				m_data.SetPhysique(__max(0, m_data.GetPhysique()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_PHYSIQUE, this->GetPhysique()))
					return false;
			}
			break;
		case _USERATTRIB_FORCE:
			{
				m_data.SetForce(__max(0, m_data.GetForce()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_FORCE, this->GetForce()))
					return false;
			}
			break;
		case _USERATTRIB_SPEED:
			{
				m_data.SetSpeed(__max(0, m_data.GetSpeed()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_SPEED, AdjustSpeed(this->GetSpeed())))
					return false;
			}
			break;
		case _USERATTRIB_DEGREE:
			{
				m_data.SetDegree(__max(0, (int)m_data.GetDegree()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_DEGREE, this->GetDegree()))
					return false;
			}
			break;
		case _USERATTRIB_POTENTIAL:
			{
				m_data.SetPotential(__max(0, (int)this->GetPotential()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_POTENTIAL, this->GetPotential()))
					return false;
			}
			break;
		case _USERATTRIB_XP:
			{
				if((int)i64Data != 0)
				{
					m_dwXP = ::CutRange(m_dwXP+(int)i64Data, 0, MAX_USER_XP);
					if(m_dwXP == MAX_USER_XP)
					{
						if(m_pMagic && m_pMagic->HaveXpMagic())
						{
							CMsgAction msgAction;
							const int XPFULLSOUNDEFFECT=1000000;
							if(msgAction.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionSoundEffect, 1000000))
							{
								this->BroadcastRoomMsg(&msgAction, INCLUDE_SELF);
							}
						}
					}
					IF_NOT (msg.Append(_USERATTRIB_XP, m_dwXP))
						return false;
				}
			}
			break;
		case _USERATTRIB_ENERGY:
			{
				AddEnergy(i64Data);
				IF_NOT (msg.Append(_USERATTRIB_ENERGY, this->GetEnergy()))
					return false;
#ifdef	PALED_DEBUG
				SendSysMsg("ENERGY: [%d]", GetEnergy());
#endif
			}
			break;
		case _USERATTRIB_MAXENERGY:
			{
				// no operation
				IF_NOT (msg.Append(_USERATTRIB_MAXENERGY, this->GetMaxEnergy()))
					return false;
			}
			break;
		case _USERATTRIB_MERCENARYEXP:
			{
				m_data.SetMercenaryExp(__max(0, (int)m_data.m_Info.dwMercenaryExp+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_MERCENARYEXP, this->GetMercenaryExp()))
					return false;
			}
			break;
		case _USERATTRIB_MERCENARYRANK:
			{
				m_data.SetMercenaryRank(__max(0, (int)m_data.m_Info.ucMercenaryRank + i64Data));
				IF_NOT (msg.Append(_USERATTRIB_MERCENARYRANK, this->GetMercenaryRank()))
					return false;
			}
			break;
		case _USERATTRIB_NOBILITYRANK:
			{
				m_data.SetNobilityRank(__max(0, (int)m_data.GetNobilityRank() + i64Data));
				IF_NOT (msg.Append(_USERATTRIB_NOBILITYRANK, this->GetNobilityRank()))
					return false;
			}
			break;
		case _USERATTRIB_EXPLOIT:
			{
				m_data.SetExploit(__max(0, (int)m_data.GetExploit()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_EXPLOIT, this->GetExploit()))
					return false;
			}
			break;
		case _USERATTRIB_TUTOR_EXP:
			{
				m_data.SetTutorExp(this->GetTutorExp()+i64Data);
				IF_NOT (msg.Append(_USERATTRIB_TUTOR_EXP, this->GetTutorExp()))
					return false;
			}
			break;
		case _USERATTRIB_TUTOR_LEVEL:
			{
				m_data.SetTutorLevel(__max(0, (int)this->GetTutorLevel()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_TUTOR_LEVEL, this->GetTutorLevel()))
					return false;
			}
			break;
		case _USERATTRIB_MAXEUDEMON:
			{
				m_data.SetMedalSelect(__max(0, (int)this->GetMedalSelect()+i64Data));
				IF_NOT (msg.Append(_USERATTRIB_MAXEUDEMON, this->GetMedalSelect()))
					return false;
			}
			break;
		default:
			return false;
		}
	}

	if(nSynchro != SYNCHRO_FALSE)
	{
		switch(nSynchro)
		{
		case SYNCHRO_TRUE:
			this->SendMsg(&msg);
			break;

		case SYNCHRO_BROADCAST:
			this->BroadcastRoomMsg(&msg, INCLUDE_SELF);
			break;

		default:
			break;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::SetAttrib(int idxAttr, __int64 i64Data, int nSynchro)
{
	CMsgUserAttrib	msg;
	if(!msg.Create(GetID(), _USERATTRIB_NONE, 0))			// _USERATTRIB_NONE : �����
		return;
	
	switch(idxAttr)
	{
	case	_USERATTRIB_LIFE:
	{
		i64Data = __max(0, __min(this->GetMaxLife(), i64Data));

		SetLife(i64Data);

		// Ѫ����70%��ʱ������״̬
		/*if (GetLife() * 100 / GetMaxLife() > MAX_FRENZY_LIFE_PERCENT)
		{
			CRole::DetachStatus(this->QueryRole(), STATUS_FRENZY);
		}*/

		if (!msg.Append(_USERATTRIB_LIFE, GetLife()))
			return;
	} break;
	
	//Not cleaned
	case	_USERATTRIB_ENERGY:
		{
			this->SetEnergy(i64Data);
			if(!msg.Append(_USERATTRIB_ENERGY, this->GetEnergy()))
				return;
		}
		break;
	case	_USERATTRIB_MAXENERGY:
		{
			// no operation
			if (!msg.Append(_USERATTRIB_MAXENERGY, this->GetMaxEnergy()))
				return;
		}
		break;

	case	_USERATTRIB_PK:
		{
			m_data.SetPk(i64Data, true);
			if(!msg.Append(_USERATTRIB_PK, this->GetPk()))
				return;
		}
		break;
	case _USERATTRIB_LEV:
		{
			int nOldLev = this->GetLev();
			int nNewLev = __max(0, __min(MAX_USERLEV, i64Data));

			m_data.SetLev(nNewLev);
			if(!msg.Append(_USERATTRIB_LEV, GetLev()))
				return;

			// �ȼ���70�����·����仯����Ҫ��������ֵ�洢��ʽ
			if (nNewLev > ADJUST_EXPFORMAT_LEVEL && nOldLev <= ADJUST_EXPFORMAT_LEVEL)
				this->SetAttrib(_USERATTRIB_EXP, this->GetExp()/10, nSynchro);
			else if (nNewLev <= ADJUST_EXPFORMAT_LEVEL && nOldLev > ADJUST_EXPFORMAT_LEVEL)
				this->SetAttrib(_USERATTRIB_EXP, this->GetExp()*10, nSynchro);
		}
		break;
	case _USERATTRIB_ADDPOINT:
		{
			i64Data = __max(0, i64Data);

			m_data.SetAddPoint(i64Data);
			if(!msg.Append(_USERATTRIB_ADDPOINT, GetAddPoint()))
				return;
		}
		break;
	case	_USERATTRIB_MANA:
		{
			i64Data = __max(0, __min(this->GetMaxMana(), i64Data));

			m_data.SetPower(i64Data);
			if(!msg.Append(_USERATTRIB_MANA, GetMana()))
				return;
		}
		break;
	case _USERATTRIB_FORCE:
		{
			m_data.SetForce(__max(0, i64Data));
			if(!msg.Append(_USERATTRIB_FORCE, GetForce()))
				return;
		}
		break;
	/*case _USERATTRIB_SOUL:
		{
			m_data.SetSoul(__max(0, i64Data));
			if(!msg.Append(_USERATTRIB_SOUL, GetSoul()))
				return;
		}
		break;*/
	case _USERATTRIB_PHYSIQUE:
		{
			m_data.SetPhysique(__max(0, i64Data));
			if(!msg.Append(_USERATTRIB_PHYSIQUE, GetPhysique()))
				return;
		}
		break;
	case _USERATTRIB_SPEED:
		{
			m_data.SetSpeed(__max(0, i64Data));
			if(!msg.Append(_USERATTRIB_SPEED, AdjustSpeed(GetSpeed())))
				return;
		}
		break;
	case _USERATTRIB_DEGREE:
		{
			m_data.SetDegree(__max(0, i64Data));
			if(!msg.Append(_USERATTRIB_DEGREE, GetDegree()))
				return;
		}
		break;
	case _USERATTRIB_POTENTIAL:
		{
			m_data.SetPotential(__max(0, i64Data));
			if (!msg.Append(_USERATTRIB_POTENTIAL, GetPotential()))
				return;
		}
		break;
	case _USERATTRIB_XP:
		{
			m_dwXP = ::CutRange((int)i64Data, 0, MAX_USER_XP);
			IF_NOT (msg.Append(_USERATTRIB_XP, m_dwXP))
				return;
		}
		break;
	case	_USERATTRIB_EXP:
		{
			// exp allow negative
			m_data.SetExp(i64Data);
			if(!msg.Append(_USERATTRIB_EXP, GetExp()))
				return;
		}
		break;
	case	_USERATTRIB_MONEY:
		{
			m_data.SetMoney(__max(0, i64Data));
			if(!msg.Append(_USERATTRIB_MONEY, GetMoney()))
				return;
		}
		break;
	case	_USERATTRIB_KEEPEFFECT:
		{
			ResetEffect();		// reset all
			this->SetEffect(i64Data);
			if(!msg.Append(idxAttr, this->GetEffect()))
				return;
		}
		break;
	case	_USERATTRIB_HAIR:
		{
			m_data.SetHair(__max(0, i64Data));

			if(!msg.Append(idxAttr, m_data.GetHair()))			
				return;

			// brocast any way
			if (nSynchro != SYNCHRO_FALSE)
				nSynchro = SYNCHRO_BROADCAST;
		}
		break;
	case	_USERATTRIB_PORFESSION:
		{
			m_data.SetProfession(i64Data, true);
			if(!msg.Append(idxAttr, m_data.GetProfession()))
				return;
		}
		break;
	case	_USERATTRIB_LOOKFACE:
		{
			// ��֧���޸�LOOKFACE����
			if(!msg.Append(idxAttr, i64Data))
				return;
		}
		break;
	case	_USERATTRIB_SIZEADD:
		{
			// ��֧���޸�SIZEADD����
			if(!msg.Append(idxAttr, i64Data))
				return;
		}
		break;
	case	_USERATTRIB_SUPERMAP_ORDER:
		{
			// ��֧���޸�SIZEADD����
			if(!msg.Append(idxAttr, i64Data))
				return;
		}
		break;
	case	_USERATTRIB_MERCENARYEXP:
		{
			m_data.SetMercenaryExp(i64Data, true);
			if(!msg.Append(idxAttr, m_data.m_Info.dwMercenaryExp))
				return;
		}
		break;
	case	_USERATTRIB_MERCENARYRANK:
		{
			m_data.SetMercenaryRank(i64Data, true);
			if (!msg.Append(idxAttr, m_data.m_Info.ucMercenaryRank))
				return;
		}
		break;
	case _USERATTRIB_NOBILITYRANK:
		{
			m_data.SetNobilityRank(__max(0, i64Data));
			if (!msg.Append(idxAttr, m_data.GetNobilityRank()))
				return;
		}
		break;
	case	_USERATTRIB_EXPLOIT:
		{
			m_data.SetExploit(__max(0, i64Data), true);
			if (!msg.Append(idxAttr, m_data.GetExploit()))
				return;
		}
		break;
	case	_USERATTRIB_ACTIONSPEED:
		{
			// TODO: 
		}
		break;
	case	_USERATTRIB_TUTOR_EXP:
		{
			m_data.SetTutorExp(i64Data);
			IF_NOT (msg.Append(_USERATTRIB_TUTOR_EXP, this->GetTutorExp()))
				return ;
		}
		break;
	case	_USERATTRIB_TUTOR_LEVEL:
		{
			m_data.SetTutorLevel(__max(0, i64Data));
			IF_NOT (msg.Append(_USERATTRIB_TUTOR_LEVEL, this->GetTutorLevel()))
				return ;
		}
		break;
	case _USERATTRIB_MAXEUDEMON:
		{
			m_data.SetMedalSelect(__max(0, i64Data));
			IF_NOT (msg.Append(_USERATTRIB_MAXEUDEMON, this->GetMedalSelect()))
				return ;
		}
		break;
		
	default:
		return;
	}

	switch(nSynchro)
	{
	case SYNCHRO_TRUE:
		this->SendMsg(&msg);
		break;

	case SYNCHRO_BROADCAST:
		this->BroadcastRoomMsg(&msg, INCLUDE_SELF);
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////
// return false mean fatal syn error.
bool CUser::SynPosition(int nPosX, int nPosY, int nMaxDislocation/* = 8*/)
{
	if (nMaxDislocation <= 0 || (nPosX == 0 && nPosY == 0))	// ignore in this condition
		return true;

	int nDislocation = this->GetDistance(nPosX, nPosY);
	if (nDislocation >= nMaxDislocation)
		return false;

	if (nDislocation <= 0)
		return true;


	if (this->IsGM())
		this->SendSysMsg("syn move: (%u, %u)->(%u, %u)",
									this->GetPosX(), this->GetPosY(),
									nPosX, nPosY);

	CMapPtr pMap = this->GetMap();
	IF_NOT(pMap && pMap->IsValidPoint(nPosX, nPosY))
		return false;
	
	// correct pos
	CMsgAction msg;
	if (msg.Create(this->GetID(), nPosX, nPosY, this->GetDir(), actionSynchro, nPosX, nPosY))
		this->BroadcastRoomMsg(&msg, EXCLUDE_SELF);

	// process move
	this->ProcessOnMove(MOVEMODE_SYNCHRO);
	this->JumpPos(nPosX, nPosY);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessAfterMove()
{
	/*IThingSet* pSet = GetMap()->QueryBlock(GetPosX(), GetPosY()).QuerySet();
	for(int i = 0; i < pSet->GetAmount(); i++)
	{
		IMapThing* pTarget = pSet->GetObjByIndex(i);
		CMapTrap* pTrap;
		if(pTarget && pTarget->QueryObj(OBJ_TRAP, IPP_OF(pTrap))
				&& pTrap->IsTrapSort() && pTarget->GetPosX() == GetPosX() && pTarget->GetPosY() == GetPosY())
		{
			pTrap->TrapAttack(QueryRole());
		}
	}*/
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessOnMove(int nMoveMode)
{
	//if(QueryBooth()) //Mam uses pet booths, which stay?
	//	QueryBooth()->LeaveMap();

	//if (nMoveMode != MOVEMODE_TRACK)
	//	SetPose(_ACTION_STANDBY);

	// stop fight
	/*if(nMoveMode != MOVEMODE_TRACK && nMoveMode != MOVEMODE_JUMPMAGICATTCK 
		&& nMoveMode != MOVEMODE_COLLIDE && nMoveMode != MOVEMODE_SYNCHRO)
	{
		ClrAttackTarget();
	}*/
	
	if(nMoveMode == MOVEMODE_RUN || nMoveMode == MOVEMODE_JUMP || nMoveMode == MOVEMODE_WALK
		|| (nMoveMode >= MOVEMODE_RUN_DIR0 && nMoveMode <= MOVEMODE_RUN_DIR7))		// && QueryMagic()->IsKeepBow()
	{
		if (QueryMagic())
			QueryMagic()->AbortMagic(true);

		// run
		if(nMoveMode == MOVEMODE_RUN || (nMoveMode >= MOVEMODE_RUN_DIR0 && nMoveMode <= MOVEMODE_RUN_DIR7))
		{
	#ifdef	PALED_DEBUG
			if(!m_bRun)
				SendSysMsg("RUN");
	#endif
			m_bRun	= true;
		}
		else
			ResetEnergyInc();
	}

//	if(nMoveMode != MOVEMODE_SHIFT && nMoveMode != MOVEMODE_SYNCHRO)
//		QueryStatusSet()->DelObj(STATUS_WEAPONDAMAGE);

//	if(nMoveMode != MOVEMODE_SHIFT && nMoveMode != MOVEMODE_SYNCHRO)
//		QueryStatusSet()->DelObj(STATUS_KEEPBOW);

	// stop mine
	this->StopMine();

	// foot print
	m_tFootPrint = ::TimeGet();
	m_posFootPrint.x = this->GetPosX();
	m_posFootPrint.y = this->GetPosY();

	// unlock
	CRole::DetachStatus(this->QueryRole(), STATUS_PK_PROTECT);
	//m_tLock.Clear();
}


//////////////////////////////////////////////////////////////////////
void CUser::ProcessOnAttack()
{
	CRole::DetachStatus(this->QueryRole(), STATUS_PK_PROTECT);
	//m_tLock.Clear();
}
//////////////////////////////////////////////////////////////////////
void CUser::GetFootPrint	(int& nPosX, int& nPosY)
{
	if (::TimeGet()-m_tFootPrint >= TIME_FOOTPRINT)
	{	// time out
		nPosX = this->GetPosX();
		nPosY = this->GetPosY();
	}
	else
	{
		nPosX = m_posFootPrint.x;
		nPosY = m_posFootPrint.y;
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::SetLife(int nLife, BOOL bUpdate)
{
	int nOldLife = this->GetLife();
	if(QueryTransformation())
	{
		if(nLife > 0)
		{
			QueryTransformation()->SetLife(nLife);

			// recalc user life
			nLife = ::CutTrail(1, MulDiv(nLife, GetMaxLife(), QueryTransformation()->GetMaxLife()));
		}
		else
		{
			SAFE_RELEASE(m_pTransformation);
			SynchroTransform();
		}
	}

	m_data.SetLife(nLife, bUpdate);

	// �����ƶ��ٶ�
	/*IStatus* pStatus = this->QueryStatus(STATUS_SLOWDOWN2);
	if (pStatus)
	{
		if ((nOldLife*2 < this->GetMaxLife() && this->GetLife()*2 >= this->GetMaxLife())
			|| (nOldLife*2 >= this->GetMaxLife() && this->GetLife()*2 < this->GetMaxLife()))
		{
			CMsgUserAttrib msg;
			if (msg.Create(this->GetID(), _USERATTRIB_SPEED, AdjustSpeed(this->GetSpeed())))
				this->BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}*/
}

//////////////////////////////////////////////////////////////////////
// get attrib
//////////////////////////////////////////////////////////////////////
DWORD CUser::GetLife()
{
	if(QueryTransformation())
		return QueryTransformation()->GetLife();

	int nMaxLife = this->GetMaxLife();
	if (m_data.GetLife() > nMaxLife)
		m_data.SetLife(nMaxLife);

	return m_data.GetLife();
}

//////////////////////////////////////////////////////////////////////
double CUser::GetMaxLife()
{
	if(QueryTransformation())
		return QueryTransformation()->GetMaxLife();

	//int nMaxLife = (this->GetLev()-1) * 3 + 30;	// û�еȼ���ְҵ�ӳ�
	/*switch(this->GetProfessionSort())
	{
	case PROFSORT_SOLDIER:
		nMaxLife += m_data.GetHealth() * 5;
		break;
	case PROFSORT_ARCHER:
		nMaxLife += m_data.GetHealth() * 7;
		break;
	case PROFSORT_MAGICIAN:
		nMaxLife += m_data.GetHealth() * 6;
		break;
	}*/
	int nMaxLife = (3 * GetPhysique()) + 30;	// �������� = ���� * 10;	// ���ʾ�������
	nMaxLife += (m_data.GetStamina() + m_data.GetForce() + m_data.GetSpeed()) / 4;
	nMaxLife += 5 * m_data.GetStamina() / 100;
	nMaxLife += 5 * m_data.GetForce() / 100;
	nMaxLife += 5 * m_data.GetSpeed() / 100;

	/*for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
			nMaxLife += pEquip->GetInt(ITEMDATA_LIFE);
	}

	nMaxLife	= nMaxLife * m_data.GetMaxLifePercent() / 1000;		// ��Ϊ�и����˶ȵ����⣬������Ҫ�������Ѫ��

	IStatus* pStatus = QueryStatus(STATUS_MAXLIFE);
	if (pStatus)
	{
		nMaxLife	= ::CutTrail(0, AdjustData(nMaxLife, pStatus->GetPower(), 100));
	}

	// �����ͻ��޺��������������
	if (m_idLinkEudemonType == ITEMTYPE_EUDEMON_DEF)
		nMaxLife += m_nLinkValue;*/

	return __max(0, nMaxLife);
}

//////////////////////////////////////////////////////////////////////
void CUser::SetMana(int nMana, BOOL bUpdate)
{
	m_data.SetLife(nMana, bUpdate);
}

DWORD CUser::GetPower() {
	int nMaxPower = this->GetMaxPower();
	if (m_data.GetPower() > nMaxPower)
		m_data.SetPower(nMaxPower);

	return m_data.GetPower();
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMaxPower()
{
	/*int nMaxMana = 0;
	switch(this->GetProfessionSort())
	{
	case PROFSORT_SOLDIER:
		nMaxMana += GetSoulSum()*5 + (GetLev()-1)*3;
		break;

	case PROFSORT_ARCHER:
		nMaxMana += GetSoulSum()*5 + (GetLev()-1)*3;
		break;

	case PROFSORT_MAGICIAN:
		nMaxMana += GetSoulSum()*5 + (GetLev()-1)*3;
		break;

	}*/
	int nMaxMana = (3 * GetDegree()) + 20;

	/*for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
			nMaxMana += pEquip->GetInt(ITEMDATA_MANA);
	}	*/

	return __max(0, nMaxMana);
}

//////////////////////////////////////////////////////////////////////
double CUser::GetAttack()
{
	if(QueryTransformation())
		return QueryTransformation()->GetAttack();

	/*float fAtk = 0.0f;
	switch(this->GetProfessionSort())
	{
	case PROFSORT_SOLDIER:
		fAtk += m_data.GetForce()*1.0f;
		break;

	case PROFSORT_ARCHER:
		fAtk += m_data.GetSpeed()*0.5f;
		break;

	case PROFSORT_MAGICIAN:
		fAtk += m_data.GetForce()*0.5f;
		break;
	}

	return (fAtk+0.5f);*/
	return m_data.GetForce();
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMagicAttack()
{
	if(QueryTransformation())
		return QueryTransformation()->GetAttack();

	/*float fAtk = 0.0f;
	switch(this->GetProfessionSort())
	{
	case PROFSORT_MAGICIAN:
		fAtk += GetSoulSum()*0.5f;
		break;
	}

	return (fAtk+0.5f);*/
	return GetSoulSum();
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetAtkHitRate()
{
	if (QueryTransformation())
		return QueryTransformation()->GetHitRate();

	int nAtkHitRate = 0;

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if (pEquip)
		{
			//nAtkHitRate += pEquip->GetHitRate();
		}
	}

	return nAtkHitRate;
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMinAtk()
{
	if(QueryTransformation())
		return QueryTransformation()->GetMinAtk();

	int nMinAtk	= this->GetAttack();

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if (pEquip)
		{
			//int nEquipAtk = pEquip->GetMinAtk();


			//if (ITEMPOSITION_WEAPONL == i && !pEquip->IsShield())
			//	nEquipAtk = nEquipAtk/2;
			//else if (ITEMPOSITION_SPRITE == i)	// ����洢�ĸ���������*100�Ժ��ֵ
			//	nEquipAtk = nEquipAtk/100;

			//nMinAtk += nEquipAtk;
		}
	}

	return __max(0, nMinAtk);
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMaxAtk()
{
	if(QueryTransformation())
		return QueryTransformation()->GetMaxAtk();

	int nMaxAtk	= this->GetAttack();

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
		{
			//int nEquipAtk = pEquip->GetMaxAtk();


			//if (ITEMPOSITION_WEAPONL == i && !pEquip->IsShield())
			//	nEquipAtk = nEquipAtk/2;
			//else if (ITEMPOSITION_SPRITE == i)	// ����洢�ĸ���������*100�Ժ��ֵ
			//	nEquipAtk = nEquipAtk/100;

			//nMaxAtk += nEquipAtk;
		}
	}

	return __max(0, nMaxAtk);
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMgcMinAtk()
{
	if(QueryTransformation())
		return QueryTransformation()->GetMgcMinAtk();

	int nMinAtk	= this->GetMagicAttack();

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if (pEquip)
		{
			//int nEquipAtk = pEquip->GetMgcMinAtk();


			//if (ITEMPOSITION_WEAPONL == i && !pEquip->IsShield())
			//	nEquipAtk = nEquipAtk/2;
			//else if (ITEMPOSITION_SPRITE == i)	// ����洢�ĸ���������*100�Ժ��ֵ
			//	nEquipAtk = nEquipAtk/100;

			//nMinAtk += nEquipAtk;
		}
	}

	return __max(0, nMinAtk);
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMgcMaxAtk()
{
	if(QueryTransformation())
		return QueryTransformation()->GetMaxAtk();

	int nMaxAtk	= this->GetMagicAttack();

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
		{
			//int nEquipAtk = pEquip->GetMgcMaxAtk();


			//if (ITEMPOSITION_WEAPONL == i && !pEquip->IsShield())
			//	nEquipAtk = nEquipAtk/2;
			//else if (ITEMPOSITION_SPRITE == i)	// ����洢�ĸ���������*100�Ժ��ֵ
			//	nEquipAtk = nEquipAtk/100;

			//nMaxAtk += nEquipAtk;
		}
	}

	return __max(0, nMaxAtk);
}

//////////////////////////////////////////////////////////////////////
double CUser::GetDefence()
{
	if(QueryTransformation())
		return QueryTransformation()->GetDefence();

	/*float fDef = 0.0f;
	switch(this->GetProfessionSort())
	{
	case PROFSORT_SOLDIER:
		fDef += m_data.GetHealth()*0.5f;
		break;

	case PROFSORT_ARCHER:
		fDef += m_data.GetHealth()*0.5f;
		break;

	case PROFSORT_WIZARD:
		fDef += m_data.GetHealth()*1.5f;
		break;

	case PROFSORT_MAGICIAN:
		fDef += m_data.GetHealth()*0.5f;
		break;
	}

	return (fDef+0.5f);*/
	return 0;
}

//////////////////////////////////////////////////////////////////////
double CUser::GetDef()
{
	if(QueryTransformation())
		return QueryTransformation()->GetDef();

	int nDef = this->GetDefence();

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
		{
			int nEquipDef = pEquip->GetDefence();

			//if (ITEMPOSITION_SPRITE == i)
			//	nEquipDef = nEquipDef / 100;	// ����洢�ĸ���������*100�Ժ��ֵ

			nDef += nEquipDef;
		}
	}
	
	return __max(0, nDef);
}

//////////////////////////////////////////////////////////////////////
/*DWORD CUser::GetSoulSum()
{
	int nData = this->GetSoul();


	//for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	//{
	//	CItem* pEquip = this->GetEquipItemByPos(i);
	//	if(pEquip)
	//		nData += pEquip->GetInt(ITEMDATA_ADD_SOUL);
	//}


	return __max(0, nData);
}*/

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetDefence2()
{
	if(QueryTransformation())
		return QueryTransformation()->GetDefence2();

	return (GetMetempsychosis() && this->GetProfessionLevel() >= 3) ? 7000 : DEFAULT_DEFENCE2;		// 3: 70��
}

//////////////////////////////////////////////////////////////////////
double CUser::GetDexterity()
{
	if(QueryTransformation())
		return QueryTransformation()->GetDexterity();

	return m_data.GetSpeed();
}

//////////////////////////////////////////////////////////////////////
/*DWORD CUser::GetDegree()
{
	//if(QueryTransformation())
	//	return QueryTransformation()->GetDegree();

	int nDegree = m_data.GetDegree();

	//for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	//{
	//	CItem* pEquip = this->GetEquipItemByPos(i);
	//	if(pEquip)
	//		nDex += pEquip->GetDexteriy();
	//}

	return nDegree;
}*/

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetDodge()
{
	if(QueryTransformation())
		return QueryTransformation()->GetDodge();

	//return 0;
	int nDex = GetSpeed();

	for (int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if (pEquip)
		{
			int nEquipDex = pEquip->GetDexteriy();

			//if (ITEMPOSITION_SPRITE == i)
			//	nEquipDef = nEquipDef / 100;	// ����洢�ĸ���������*100�Ժ��ֵ

			nDex += nEquipDex;
		}
	}

	return __max(0, nDex);
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetDdg()
{
	if(QueryTransformation())
		return QueryTransformation()->GetDdg();

	int nDge = this->GetDodge();

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		//if(pEquip)
		//	nDge +=	pEquip->GetDodge();		//pEquip->GetInt(ITEMDATA_DODGE);
	}

	//---jinggy---begin
	//�������״̬���� dodge ֵ
	IStatus * pStatus = QueryStatus(STATUS_ADJUST_DODGE);
	if (pStatus)
	{
		nDge = ::CutTrail(0, AdjustData(nDge, pStatus->GetPower()));			
	}		
	//---jinggy---end

	return __max(0, nDge);
}

//////////////////////////////////////////////////////////////////////
int	 CUser::GetLuck()
{
//	if(QueryTransformation())
//		return QueryTransformation()->GetDdg();

	int nLuck = 0;

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		//if(pEquip)
		//	nLuck += pEquip->GetInt(ITEMDATA_LUCK);
	}

	ASSERT(nLuck <= 35);
	return __max(0, nLuck);
}

//////////////////////////////////////////////////////////////////////
/*DWORD CUser::GetMagicAtk()		//? ���Ż�
{
	if(QueryTransformation())
		return QueryTransformation()->GetMagicAtk();

	float fAtk = 0.0f;
	switch(this->GetProfessionSort())
	{
	case PROFSORT_SOLDIER:
		break;

	case PROFSORT_ARCHER:
		break;

	case PROFSORT_WIZARD:
		fAtk += m_data.GetSoul()*0.5f;
		break;

	case PROFSORT_MAGICIAN:
		fAtk += m_data.GetSoul()*0.5f;
		break;
	}

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
		{
			fAtk += pEquip->GetInt(ITEMDATA_MAGICATK);
		}
	}

	return __max(0, fAtk+0.5);
}*/

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetMagicDef()		//? ���Ż�
{
	if(QueryTransformation())
		return QueryTransformation()->GetMagicDef();

	float fDef = 0.0f;
	/*switch(this->GetProfessionSort())
	{
	case PROFSORT_SOLDIER:
		fDef += m_data.GetHealth()*0.5f;
		break;

	case PROFSORT_ARCHER:
		fDef += GetSoulSum()*0.5f;
		break;

	case PROFSORT_MAGICIAN:
		fDef += GetSoulSum()*0.5f;
		break;
	}*/

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr* ppEquip = GetEquipItemPtr(i);
		CHECKF(ppEquip);
		CItemPtr& pEquip = *ppEquip;
		if(pEquip)
		{
			//int nEquipDef = pEquip->GetMgcDef();

			//if (ITEMPOSITION_SPRITE == i)
			//	nEquipDef = nEquipDef / 100;	// ����洢�ĸ���������*100�Ժ��ֵ

			//fDef += nEquipDef;
		}
	}

	fDef += 0.5f;

//	fDef = __min(90.0f, fDef);
//	fDef = __max(0.0f, fDef);

	return fDef;
}

//////////////////////////////////////////////////////////////////////
int CUser::GetAddPoint()
{
	return m_data.GetAddPoint();
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetLev()
{
	return m_data.GetLev();
}

//////////////////////////////////////////////////////////////////////
void CUser::IncLev(int nLev)
{
	int nOldLev = this->GetLev();
	int nNewLev	= nOldLev + nLev;
	this->SetAttrib(_USERATTRIB_LEV, nNewLev, SYNCHRO_TRUE);

	// start pay point fee?
	if(nOldLev < LOGIN_FREE_LEVEL && nNewLev >= LOGIN_FREE_LEVEL)
		MapGroup(PID)->QueryIntraMsg()->LevelUp(GetID(), nNewLev);

	if (QueryMagic())
		QueryMagic()->OwnerUpLevel(nNewLev);
	if(GetSynID() != ID_NONE)
	{
		QuerySynAttr()->UpLevel(nNewLev);
		if (QuerySynAttr()->GetSynRank() == RANK_RESERVED && GetLev() >= SYN_CONDITION_NEWBIE)
			QuerySynAttr()->SetRank(RANK_NEWBIE);
	}

	// tutor exp record
	/*if (this->GetLev() >= _MIN_TUTOR_LEVEL)
	{
		CTutorexpData*	pExpData;
		pExpData = CTutorexpData::CreateNew();
		if (pExpData && pExpData->Create(GetID(), Database()))
		{
			if (pExpData->GetID() == ID_NONE)
			{
				pExpData->SetInt(TUTOREXPDATA_ID, this->GetID());
				pExpData->SetInt(TUTOREXPDATA_TUTOR_LEV, this->GetLev());
				pExpData->InsertRecord();
			}
			else
			{
				if (pExpData->GetInt(TUTOREXPDATA_TUTOR_LEV) != this->GetLev())
				{
					pExpData->SetInt(TUTOREXPDATA_TUTOR_LEV, this->GetLev());
					pExpData->Update();
				}
			}
		}
		SAFE_RELEASE (pExpData);
	}*/
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetCultivation()
{
	return m_data.GetCultivation();
}

//////////////////////////////////////////////////////////////////////
void CUser::AllotPoint()
{
	int nProf = this->GetProfessionSort();
	if (nProf > 10)
		nProf = (nProf/10)*10;

	int nAmount = AddPointSet()->GetAmount();
	for(int i = 0; i < nAmount; i++)
	{
		CAddPointData* pData = AddPointSet()->GetObjByIndex(i);
		if(pData 
				&& pData->GetInt(ADDPOINTDATA_PROF) == nProf
				&& pData->GetInt(ADDPOINTDATA_LEVEL) == this->GetLev())
		{
			m_data.SetForce(pData->GetInt(ADDPOINTDATA_FORCE));
			//m_data.SetHealth(pData->GetInt(ADDPOINTDATA_HEALTH));
			//m_data.SetSoul(pData->GetInt(ADDPOINTDATA_SOUL));
			//m_data.SetDexterity(pData->GetInt(ADDPOINTDATA_DEX), UPDATE_TRUE);

			{
				CMsgUserAttrib	msg;
				if(msg.Create(GetID(), _USERATTRIB_FORCE, GetForce())
						&& msg.Append(_USERATTRIB_DEGREE, GetDegree())
						&& msg.Append(_USERATTRIB_PHYSIQUE, GetPhysique())
						//&& msg.Append(_USERATTRIB_SOUL, GetSoul())	
					)
					SendMsg(&msg);
			}
			return ;
		}
	}

	// lev data not found
	this->AddAttrib(_USERATTRIB_ADDPOINT, _ADDITIONALPOINT_NUM, SYNCHRO_TRUE);
	return;
}

//////////////////////////////////////////////////////////////////////
int CUser::GetPose()
{
	return m_nPose;
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsAllNonsuchEquip (void)
{
	/*CItemPtr pWeaponR = NULL;
	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		if (i == ITEMPOSITION_RINGL)
			continue;

		CItem* pEquip = GetEquipItemByPos(i);

		if (i == ITEMPOSITION_WEAPONR)
			pWeaponR = pEquip;

		if (!pEquip)
		{
			if (i == ITEMPOSITION_WEAPONL)
			{
				switch(this->GetProfessionSort())
				{
				case PROFSORT_SOLDIER:
					{
						if (this->GetLev() >= 40)
						{
							if (pWeaponR && !pWeaponR->IsWeapon2())
								return false;
						}
					}
					break;

				default:
					break;
				}
				
				continue;
			}
			else
				return false;
		}
		
		if (!pEquip->IsNonsuch())
			return false;
	}*/

	return true;
}

//////////////////////////////////////////////////////////////////////
I64 CUser::GetEffect()
{
	return m_data.m_Info.i64Effect;
}

//////////////////////////////////////////////////////////////////////
int CUser::GetDir()
{
	return m_nDir;
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetLook()
{
	/*enum {LOOK_MALEGHOST=98, LOOK_FEMALEGHOST};

	if (IsGhost())
	{
		if (SEX_MAN == this->GetSex())
			return m_data.GetLook() + MASK_CHANGELOOK*LOOK_MALEGHOST;
		else
			return m_data.GetLook() + MASK_CHANGELOOK*LOOK_FEMALEGHOST;
	}
	else if(QueryTransformation())
	{
		return m_data.GetLookFace()
				+ MASK_CHANGELOOK * QueryTransformation()->GetLook();
	}
	else*/
		return m_data.GetLook();
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::GetWeightLimit()
{
	if(this->GetProfessionSort() == PROFSORT_SOLDIER)
		return 30 - 3 + 3*GetLev();
	else
		return 20 - 2 + 2*GetLev();
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
bool CUser::LeaveMap()
{
	if(m_nStep != STEP_ENTERMAP)
		return false;

	StopMine();
	DestroyBooth();
	KillCallPet();
	//CallBackAllEudemon(); recall walking pet?

	CMapPtr pMap = GetMap();
	if(pMap)
	{
		// BeKill��ʱ�������DecRole�����������Ҫ�ж��Ƿ�Ϊ����״̬������LeaveRoom��ʱ����һ�ν�ɫ��
		//pMap->LeaveRoom(QueryMapThing(), this->IsAlive());	//WITH_BLOCK);
		pMap->LeaveRoom(QueryMapThing(), false);	// Turn off block?
		StandTurnoff();
		pMap->ClearRegionInfo(this);

		// brocast my info
		CMsgAction msg;
		if (msg.Create(GetID(), 0,0,0, actionLeaveMap))
			this->BroadcastRoomMsg(&msg, EXCLUDE_SELF);

		ClrBroadcastSet();
	}

	m_nStep = STEP_LOGIN;
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::SendItemSet()
{
	SendAllItemInfo();
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::SendGoodFriend()
{
	SendFriendInfo();
	return true;
}

//////////////////////////////////////////////////////////////////////
// fight
//////////////////////////////////////////////////////////////////////
bool CUser::SetAttackTarget(IRole* pTarget /*= NULL*/)
{
	//if (!m_pBattleSystem)
		return false;

	/*if(pTarget == NULL)
	{
		m_pBattleSystem->ResetBattle();
		return true;
	}

	if(pTarget->QueryOwnerUser() && GetMap()->IsInRegionType(REGION_PK_PROTECTED, GetPosX(), GetPosY()))
		return false;

	if (!this->IsAtkable(pTarget, true))
		return false;

	if(pTarget->IsWing() && !this->IsWing() && !(this->IsBowman() || this->IsSimpleMagicAtk()))
		return false;

	// goal
	CNpc* pNpc;
	pTarget->QueryObj(OBJ_NPC, IPP_OF(pNpc));
	if(pNpc && pNpc->IsGoal() && (GetLev() < pNpc->GetLev() || pNpc->GetType()!=_WEAPONGOAL_NPC))
		return false;

	if(this->GetDistance(pTarget->QueryMapThing()) > GetAttackRange(pTarget->GetSizeAdd()))
	{
		m_pBattleSystem->ResetBattle();
		return false;
	}

	CheckCrime(pTarget);

	if(IsBowman() && !IsArrowPass(pTarget->GetPosX(), pTarget->GetPosY()))
		return false;

	m_pBattleSystem->CreateBattle(pTarget->GetID());
	CalcFightRate();

	if (QueryMagic())
		QueryMagic()->AbortMagic(true);

	// unequip magic arrow, hard code@@@
	CItem* pEquipL = GetEquipItemByPos(ITEMPOSITION_WEAPONL);
	if(!pEquipL || pEquipL->GetInt(ITEMDATA_MAGIC1) == MAGIC_NONE)
		UnequipMagicItem(ITEMPOSITION_WEAPONL);

	return true;*/
}

//////////////////////////////////////////////////////////////////////
int CUser::GetGemMgcExpEffect()
{
	int nAddPercent = 0;
	for (int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if (pEquip)
			nAddPercent += pEquip->GetGemMgcExpEffect();
	}

	return nAddPercent;
}

//////////////////////////////////////////////////////////////////////
int CUser::GetGemWpnExpEffect()
{
	int nAddPercent = 0;
	for (int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if (pEquip)
			nAddPercent += pEquip->GetGemWpnExpEffect();
	}

	return nAddPercent;
}

//////////////////////////////////////////////////////////////////////
int CUser::GetGemExpEffect()
{
	int nAddPercent = 0;
	for (int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if (pEquip)
			nAddPercent += pEquip->GetGemExpEffect();
	}

	return nAddPercent;
}
//////////////////////////////////////////////////////////////////////
int	CUser::GetGemAtkEffect		(void)
{
	int nAddEffect = 0;
	for (int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if (pEquip)
			nAddEffect += pEquip->GetGemDmgEffect();
	}

	return nAddEffect;
}

//////////////////////////////////////////////////////////////////////
int CUser::GetGemMgcAtkEffect	(void)
{
	int nAddEffect = 0;
	for (int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if (pEquip)
			nAddEffect += pEquip->GetGemMgcAtkEffect();
	}

	return nAddEffect;
}

//////////////////////////////////////////////////////////////////////
void CUser::SendGemEffect(void)
{
	vector<int> setGem;

	int nGem = 0;
	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if (pEquip)
		{
			/*nGem = pEquip->GetInt(ITEMDATA_GEM1);
			if (nGem != GEM_NONE && nGem != GEM_HOLE)
				setGem.push_back(nGem);

			nGem = pEquip->GetInt(ITEMDATA_GEM2);
			if (nGem != GEM_NONE && nGem != GEM_HOLE)
				setGem.push_back(nGem);*/
		}
	}	

	int nGems = setGem.size();
	if (nGems <= 0)
		return;

	string strEffect;
	switch(setGem[::RandGet(nGems)])
	{
	case 3:
		strEffect = "phoenix";
		break;
	case 13:
		strEffect = "goldendragon";
		break;
	case 23:
		strEffect = "fastflash";
		break;
	case 33:
		strEffect = "rainbow";
		break;
	case 43:
		strEffect = "goldenkylin";
		break;
	case 53:
		strEffect = "purpleray";
		break;
	case 63:
		strEffect = "moon";
		break;
	default:
		return;
	}

	CMsgName msg;
	IF_OK (msg.Create(NAMEACT_ROLEEFFECT, strEffect.c_str(), this->GetID()))
		this->BroadcastRoomMsg(&msg, true);
}

//////////////////////////////////////////////////////////////////////
// precondition is dodge failed
int CUser::Attack(IRole* pTarget)		// return : lose life
{
 	CHECKF(pTarget);

	CNpc* pNpc;
	pTarget->QueryObj(OBJ_NPC, IPP_OF(pNpc));

	int nAtk=0;
	int nDamage = 0;// CBattleSystem::CalcPower(IsSimpleMagicAtk(), QueryRole(), pTarget, &nAtk, true);

	// Ŀ�껤��״̬ת���˺�
	if (nDamage>0 && pTarget->TransferShield(IsSimpleMagicAtk(), QueryRole(), nDamage))
	{
	}
	else
	{
		int nLoseLife = ::CutOverflow(nDamage, (int)pTarget->GetLife());
		if (nLoseLife > 0)
			pTarget->AddAttrib(_USERATTRIB_LIFE, -1*nLoseLife, SYNCHRO_TRUE);

		// adjust synflag damage
		if(pNpc && pNpc->IsSynFlag() && pNpc->IsSynMoneyEmpty())
		{
			nDamage	*= SYNWAR_NOMONEY_DAMAGETIMES;
		} 

		if (nDamage > 0)
		{
			if (::RandGet(10) == 7)
				this->SendGemEffect();
		}
		
		pTarget->BeAttack(IsSimpleMagicAtk(), QueryRole(), nDamage);
	}		

	CGameMap* pMap = this->GetMap();
	if (pMap)
	{
		// crime
		if (!pTarget->IsEvil()				// ֻ��pk����������
				&& !pMap->IsDeadIsland())	// ������ɱ�˲�����
		{
			if (!QueryStatus(STATUS_CRIME))
				this->SetCrimeStatus();
		}

		// equipment durability cost
		if (!pMap->IsTrainMap())
			this->DecEquipmentDurability(ATTACK_TIME, IsSimpleMagicAtk(), (nDamage < nAtk/10) ? 10 : 1);
	}

	IStatus* pStatus = QueryStatus(STATUS_DMG2LIFE);
	if (pStatus)
	{
		int nLifeGot = ::CutTrail(0, MulDiv(nDamage, pStatus->GetPower(), 100));
		if (nLifeGot > 0)
			this->AddAttrib(_USERATTRIB_LIFE, nLifeGot, SYNCHRO_TRUE);
	}

	return nDamage;
}

//////////////////////////////////////////////////////////////////////
bool CUser::BeAttack(bool bMagic, IRole* pTarget, int nPower, bool bReflectEnable/*=true*/)
{
	CHECKF(pTarget);

	QueryStatusSet()->DelObj(STATUS_LURKER);
	CRole::DetachStatus(this->QueryRole(), STATUS_FREEZE);
	StopMine();

	// reflect, only use for weapon attack!!!
	IStatus* pStatus = QueryStatus(bMagic?STATUS_REFLECTMAGIC:STATUS_REFLECT);
	if(nPower>0 && pStatus && bReflectEnable)
	{
		int nPower2 = AdjustData(nPower, pStatus->GetPower());
		if(nPower2 > 0)
		{
			int nLoseLife = ::CutOverflow((int)pTarget->GetLife(), nPower2);
			pTarget->AddAttrib(_USERATTRIB_LIFE, -1*nLoseLife, SYNCHRO_TRUE);
			pTarget->BeAttack(bMagic, this, nPower2, false);

			// ���ͽ����Ϣ
			CMsgInteract msg;
			if (msg.Create(bMagic?INTERACT_REFLECTMAGIC:INTERACT_REFLECTWEAPON, GetID(), pTarget->GetID(), GetPosX(), GetPosY(), nPower2))
				BroadcastRoomMsg(&msg, INCLUDE_SELF);

			// kill?
			if (!pTarget->IsAlive())
				pTarget->BeKill();
		}
	}

	// equipment durability cost
	if (!this->GetMap()->IsTrainMap())
	{
		this->DecEquipmentDurability(BEATTACK_TIME, bMagic, (nPower > this->GetMaxLife()/4) ? 10 : 1);
	}

	// self_defence     // add huang 2004.1.14
//	if(QueryStatus(STATUS_SELFDEFENCE))
//		this->SetSelfDefStatus();
	
	if(nPower > 0)
		BroadcastTeamLife();

	// abort magic
	if (QueryMagic() && QueryMagic()->IsIntone())
		QueryMagic()->AbortMagic(true);

	/*/ stamina lost
	if (_ACTION_SITDOWN ==  this->GetPose())
	{
		this->SetPose(_ACTION_STANDBY);
		this->SetAttrib(_USERATTRIB_ENERGY, this->GetEnergy()/2, SYNCHRO_TRUE);
	}*/

	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::SendDamageMsg(OBJID idTarget, int nDamage)
{
	OBJID idMagicType = ID_NONE;
	if(QueryTransformation())
		idMagicType = QueryTransformation()->GetMagicType();

	if(idMagicType != ID_NONE)
	{
		CMsgMagicEffect	msg;
		IF_OK(msg.Create(GetID(), idMagicType, 0, idTarget, nDamage, GetDir()))
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}
	else if(IsBowman())
	{
		CMsgInteract msg;
		IF_OK(msg.Create(INTERACT_SHOOT, GetID(), idTarget, GetPosX(), GetPosY(), nDamage))
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}
	else
	{
		CMsgInteract msg;
		IF_OK(msg.Create(INTERACT_ATTACK, GetID(), idTarget, GetPosX(), GetPosY(), nDamage))
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
	}
}

//////////////////////////////////////////////////////////////////////
bool CUser::TransferShield(bool bMagic, IRole* pAtker, int nDamage)
{
	IStatus* pStatus = QueryStatus(STATUS_TRANSFER_SHIELD);
	if (!pStatus)
		return false;

	int nMagicType = pStatus->GetPower();

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::BroadcastTeamLife(bool bMaxLife)
{
	// 2003.2.13 ����Է�����Ҷ�������ˡ����������ȥѪֵҪ�ڶ��ڹ㲥��
	CTeam* pTeam	= GetTeam();
	if (pTeam && pTeam->GetMemberAmount() > 1)
	{
		pTeam->BroadcastMemberLife(this, bMaxLife);
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::DecEquipmentDurability(bool bBeAttack, bool bMagic, int bDurValue/*=1*/)
{
	int nInc = -1 * bDurValue;
	/*for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		if (!bMagic)
		{
			if (i == ITEMPOSITION_RINGR || 
					i == ITEMPOSITION_RINGL ||
						i == ITEMPOSITION_SHOES ||
							i == ITEMPOSITION_WEAPONR ||
								i == ITEMPOSITION_WEAPONL)
			{
				if(!bBeAttack)
					AddEquipmentDurability(i, nInc);
			}
			else
			{
				if(bBeAttack)
					AddEquipmentDurability(i, nInc);
			}
		}
		else
		{
			if (i == ITEMPOSITION_RINGR || 
					i == ITEMPOSITION_RINGL ||
						i == ITEMPOSITION_SHOES ||
							i == ITEMPOSITION_WEAPONR ||
								i == ITEMPOSITION_WEAPONL)
			{
				if(!bBeAttack)
					AddEquipmentDurability(i, -5);
			}
			else
			{
				if(bBeAttack)
					AddEquipmentDurability(i, nInc);
			}
		}
	}*/
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::MagicAttack(int nType, OBJID idTarget, int x, int y)
{
	if (QueryMagic())
		return QueryMagic()->MagicAttack(nType, idTarget, x, y);
	return false;
}

//////////////////////////////////////////////////////////////////////
int	CUser::CalcExpLostOfDeath (IRole* pKiller)
{
	CUser* pUserKiller = NULL;
	if (!pKiller->QueryObj(OBJ_USER, IPP_OF(pUserKiller)))
		return 0;

	// normal condition
	int nParam = 50;
	if (this->GetEffect()&KEEPEFFECT_RED)
		nParam = 10;
	else if (this->GetEffect()&KEEPEFFECT_DEEPRED)
		nParam = 5;
	else
		nParam = 50;

	int nExpLost = __max(0, this->GetExp()/nParam);

	//if (true)
	//	return nExpLost;

	// syndicate member && not the killer wanted guy
	if (this->GetSynID() != ID_NONE && !pUserKiller->IsMyWantedTarget(this))
	{
		int nDecPercent = 0;
		CSyndicate* pSyn = this->GetSyndicate();
		IF_OK (pSyn)
		{
			int nExpPayBySyn = 0;
			int nProffer = this->QuerySynProffer();
			if (nProffer > 0)
			{			
				int nRank = this->QuerySynRank();
//				switch(nRank)
//				{
//				case RANK_LEADER:
//					nDecPercent = 80;
//					break;
//
//				case RANK_SUBLEADER:
//					nDecPercent = 60;
//					break;
//				case RANK_TEAMLEADER:
//					nDecPercent = 40;
//					break;
//				default:
//					nDecPercent = 25;
//					break;
//				}
	

				CONST int MONEYCOST_PEREXP = 100;
				int nFundSyn  = pSyn->GetInt(SYNDATA_MONEY);
				int nFundLost = ::MulDiv(nExpLost, nDecPercent, 100*MONEYCOST_PEREXP);	// 100�㾭��1��
				if (nFundLost > nFundSyn)
					nFundLost = nFundSyn;

				pSyn->QueryModify()->AddData(SYNDATA_MONEY, -1*nFundLost, true);

				if (nRank != RANK_LEADER)
					this->SetSynProffer(nProffer-nFundLost);

				nExpPayBySyn = nFundLost*MONEYCOST_PEREXP;
				nExpLost -= nExpPayBySyn;//nFundLost*MONEYCOST_PEREXP;
			}
			else
			{
				if (pSyn->IsWhiteSynMapOwner() || pSyn->IsBlackSynMapOwner())
				{
					nDecPercent = 20;
				}
				else
				{
					nDecPercent = 10;
				}

				CONST int MONEYCOST_PEREXP = 100;
				int nFundSyn  = pSyn->GetInt(SYNDATA_MONEY);
				int nFundLost = ::MulDiv(nExpLost, nDecPercent, 100*MONEYCOST_PEREXP);	// 100�㾭��1��
				if (nFundLost > nFundSyn)
					nFundLost = nFundSyn;

				pSyn->QueryModify()->AddData(SYNDATA_MONEY, -1*nFundLost, true);

				if (this->QuerySynRank() != RANK_LEADER)
					this->SetSynProffer(nProffer-nFundLost);

				nExpPayBySyn = nFundLost*MONEYCOST_PEREXP;
				nExpLost -= nExpPayBySyn;//nFundLost*MONEYCOST_PEREXP;
			}

			this->SendSysMsg(_TXTATR_NORMAL, EXPLOST_PAYBY_SYNFUND, nExpPayBySyn);
		}
	}

	return __max(0, nExpLost);
}

//////////////////////////////////////////////////////////////////////
void CUser::Kill(IRole* pTarget, DWORD dwDieWay)
{
	CHECK(pTarget);

	// inc xp
	USHORT usRemainTime = 0;
//	IStatus* pStatus = QueryStatus(STATUS_XPFULL);
//	if (pStatus && pTarget->IsMonster())
//	{
//		pStatus->IncTime(ADD_XPFULL_SECS_KILLMONSTER*1000, MAX_XPFULL_SECS*1000);
//		m_nCurrSupermanKills++;
//		StatusInfoStruct	info;
//		if (pStatus->GetInfo(&info))
//			usRemainTime = info.nSecs;
//	}

	CMsgInteract msg;
	if(msg.Create(INTERACT_KILL, this->GetID(), pTarget->GetID(), pTarget->GetPosX(), pTarget->GetPosY(), dwDieWay, usRemainTime))
		pTarget->BroadcastRoomMsg(&msg, true);

	// earth magic
	//???

	if (QueryMagic())
		QueryMagic()->UserKillTarget(pTarget);

	CUser* pTargetUser	= NULL;
	if(!pTarget->QueryObj(OBJ_USER, IPP_OF(pTargetUser)))
	{
		pTarget->BeKill((IRole*)this);		// NPC return
		return;
	}

	ProcessPk(pTargetUser);

	// target...
	pTarget->BeKill((IRole*)this);
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessPk (CUser* pTargetUser)
{
	ASSERT(pTargetUser);

	// map...
	CGameMap* pMap = MapManager()->QueryMap(this->GetMapID());
	IF_OK (pMap) 
	{
		if (pMap->IsPkField())
		{
		}
		else if (pMap->IsPkGameMap())
		{
			pTargetUser->DelAllBadge();
			AddBadge();
		}
		else if (pMap->IsSynMap())
		{
		}
		else if (pMap->IsPrisonMap())
		{
		}
		else
		{
			// innocent kill      //change huang 2004.1.11
			if (!(pTargetUser->GetEffect()&KEEPEFFECT_RED) 
					&& !(pTargetUser->GetEffect()&KEEPEFFECT_DEEPRED))
			{
				//if (this->GetEffect()&(KEEPEFFECT_DEEPRED | KEEPEFFECT_RED))   
				//	PoliceWanted().AddWanted(this);
			}

/*			// �°���û�м��������ʧ --- zlong 2004.10.28
			int nManaLost = pTargetUser->GetMana()/2;
			pTargetUser->AddAttrib(_USERATTRIB_MANA, -1*nManaLost, SYNCHRO_TRUE);		// , &dwDirty
*/

			// pk increase    // tudo 2004.1.11   // û��
//			if (!pTargetUser->IsEvil() 
//					&& pTargetUser->GetPk() < PKVALUE_REDNAME
//						&& !pMap->IsDeadIsland())	// ������ɱ�˲�����������PKֵ
						// && pTargetUser->GetExp() >= 0)	// ʥս��ȡ������趨

			// pk increase	���� PK����������Ҫ��PKֵ -- zlong 2005-04-28
			if (!pMap->IsDeadIsland()
				&& !pTargetUser->QueryStatus(STATUS_CRIME)
				&& pTargetUser->GetPk() < PKVALUE_BLACKNAME)
			{
				int nPkValue = PKVALUE_ONEKILL;
				if (pTargetUser->GetPk() >= PKVALUE_REDNAME)	// PK�����ӵ�PKֵ����
					nPkValue /= 2;
				switch (pTargetUser->GetNobilityRank())
				{
				case NOBILITY_RANK_VISCOUNT:		// ɱ�Ӿ�+10%PKֵ
					nPkValue += nPkValue*10/100;
					break;
				case NOBILITY_RANK_EARL:			// ɱ����+20%PKֵ
					nPkValue += nPkValue*20/100;
					break;
				case NOBILITY_RANK_MARQUESS:		// ɱ���+40%PKֵ
					nPkValue += nPkValue*40/100;
					break;
				case NOBILITY_RANK_DUKE:			// ɱ����+50%PKֵ
					nPkValue += nPkValue*50/100;
					break;
				}
				// syn effect
				if (this->IsHostileSynMember(pTargetUser))
					nPkValue /= 2;

				this->AddPk(nPkValue);

				// crime
				//if (!QueryStatus(STATUS_CRIME))
				//{
				//	CONST CRIME_TIME_PERMURDER = 30;	//2*60;		// ����ʱ���Ϊ30��
				//	this->SetCrimeStatus(STATUS_CRIME, CRIME_TIME_PERMURDER);
				//}

				// ��ʾ ���� zlong 2005-04-28
				/*if (this->GetPk() < PKVALUE_REDNAME)
					this->SendSysMsg(STR_INCPK_REDNAME_PUNISH);
				else if (this->GetPk() < PKVALUE_BLACKNAME)
					this->SendSysMsg(STR_INCPK_BLACKNAME_PUNISH);
				else
					this->SendSysMsg(STR_INCPK_BLACKNAME_PUNISH2);*/
			}

			// ��������
			/*{
				// ����2004.10.28�İ������� ---- zlong
				__int64	nLevExp = 0;	// �������辭��
				int		nStuExp	= 0;	// ������߾���
				CLevupexpData* pLevupexp	= LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + pTargetUser->GetLev());
				if (!pLevupexp)
					pLevupexp = LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + __max(0, pTargetUser->GetLev()-1));

				if (pLevupexp)
				{
					nLevExp = pLevupexp->GetInt(LEVUPEXPDATA_EXP);
					nStuExp	= pLevupexp->GetInt(LEVUPEXPDATA_STU_EXP);	//nStuExp������Ϊ��ĸ������Ϊ0
				}
				pLevupexp	= LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + this->GetLev());
				if (!pLevupexp)
					pLevupexp = LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + __max(0, this->GetLev()-1));

				int nKillerStuExp	= 0;
				if (pLevupexp)
					nKillerStuExp	= pLevupexp->GetInt(LEVUPEXPDATA_STU_EXP);

				int nLossExpPercent = 0;
				if (pTargetUser->GetPk() < PKVALUE_REDNAME)					// ����
					nLossExpPercent	= 1;									// ��ʧ��������1%����
				else if (pTargetUser->GetPk() < PKVALUE_BLACKNAME)			// ����
					nLossExpPercent	= 2;									// ��ʧ��������2%����
				else														// ����
					nLossExpPercent	= 3;									// ��ʧ��������3%����

				__int64 nExpGet = (nLevExp) * nLossExpPercent * 70 / 10000;			// ɱ�˵õ��Է���ʧ�����70%
				// ����Ĺ�ʽ�޸���, 
				// ɱ�˵��˵õ�����=����ɱ����ʧ����/��ɱ�˱���1�οɵ���߾��飩*ɱ�˵��˱���1�οɵ���߾���*70%
				if (nStuExp == 0)
					nExpGet	= 0;
				else
					nExpGet	= nExpGet * nKillerStuExp / nStuExp;
				
				if (nExpGet > 0)
					this->AwardBattleExp(nExpGet);

				// ����ɱ����Ҫ�۹�ѫֵ
				if (!pTargetUser->IsEvil() 
						&& pTargetUser->GetPk() < PKVALUE_REDNAME
							&& !pMap->IsDeadIsland()	// ������ɱ�˲�����������PKֵ
								&& this->GetNobilityRank() > NOBILITY_RANK_NONE)
				{
					int nExploitLost = 0;
					switch (this->GetNobilityRank())
					{
					case NOBILITY_RANK_VISCOUNT:		// �Ӿ�ɱ�˹�ѫֵ�۶Է���ʧ�����1/80
						nExploitLost = (nLevExp * nLossExpPercent)/100 / 80;
						break;
					case NOBILITY_RANK_EARL:			// ����ɱ�˹�ѫֵ�۶Է���ʧ�����1/60
						nExploitLost = (nLevExp * nLossExpPercent)/100 / 60;
						break;
					case NOBILITY_RANK_MARQUESS:		// ���ɱ�˹�ѫֵ�۶Է���ʧ�����1/40
						nExploitLost = (nLevExp * nLossExpPercent)/100 / 40;
						break;
					case NOBILITY_RANK_DUKE:			// ����ɱ�˹�ѫֵ�۶Է���ʧ�����1/20
						nExploitLost = (nLevExp * nLossExpPercent)/100 / 20;
						break;
					}
					if (nExploitLost > 0)
					{
						this->AddAttrib(_USERATTRIB_EXPLOIT, -1*nExploitLost, SYNCHRO_TRUE);
					}
				}

				// ����ɱ�����������ѫֵ
				if (pTargetUser->GetPk() >= PKVALUE_REDNAME
						&& !pMap->IsDeadIsland()
							&& this->GetNobilityRank() > NOBILITY_RANK_NONE)
				{
					int nExploitGet = (nLevExp * nLossExpPercent)/100/100;
					if (nExploitGet > 0)
						this->AddAttrib(_USERATTRIB_EXPLOIT, nExploitGet, SYNCHRO_TRUE);
				}
			}*/

			// wanted kill
			/*if (this->IsMyWantedTarget(pTargetUser))
			{
				OBJID idWanted = this->WantedInfo().idWanted;
				CWantedData* pData = CWantedList::s_WantedList.GetWanted(idWanted);

				// award bonuty!
				int nBonuty = 0;
				if (pData)
					nBonuty = pData->GetInt(DATA_BOUNTY);

				this->AddAttrib(_USERATTRIB_MONEY, nBonuty*(100-_BONUTY_TAX)/100, SYNCHRO_TRUE);
				
				// del wanted from list
				CWantedList::s_WantedList.DelWanted(idWanted);
				
				// reset my wanted info
				this->ResetWantedInfo();
				
				// inform client
				CMsgName msg;
				IF_OK_ (msg.Create(NAMEACT_WANTED, ""))
					this->SendMsg(&msg);
				
				// lost of wanted target
				int nLevExp = 0;
				CLevupexpData* pLevupexp	= LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + this->GetLev());
				if (pLevupexp)
					nLevExp = pLevupexp->GetInt(LEVUPEXPDATA_EXP);
				
				int nCurExp = pTargetUser->GetExp();
				int nExpLost = __min(nBonuty, nLevExp);
				
				if (nCurExp >= 0)				
				{
					if (nCurExp - nExpLost <= 0)
						nExpLost = nCurExp + (nExpLost-nCurExp)/2;
				}
				else
				{
					int nFactor = (-1*nCurExp/nLevExp + 1)*2;
					nExpLost = nExpLost/nFactor;
				}
				
				pTargetUser->AddAttrib(_USERATTRIB_EXP, -1*nExpLost, SYNCHRO_TRUE);
			}*/

			// Ӷ��ϵͳ�е�ɱ������ -- �Ժ��������Ż�������Ҫÿ�ζ�ȥ��ѯ�Լ��ӵ�����
			/*CMercenaryTaskData* pTaskData = MercenaryTask()->QueryTaskDataAccepted(GetID());
			if (pTaskData && pTaskData->GetInt(MTASKDATA_TYPE) == _WANT_PK 
				&& pTaskData->GetInt(MTASKDATA_STATE) == MTASKSTATE_ACCEPTED)
			{
				if (strcmp(pTaskData->GetStr(MTASKDATA_TARGET_NAME), pTargetUser->GetName()) == 0)
				{
					pTaskData->SetInt(MTASKDATA_STATE, MTASKSTATE_FINISHED, true);
					// task finished.
					this->SendSysMsg(STR_TASK_FINISHED);
				}
			}*/

			// police wanted kill
			if (pTargetUser->GetID() == this->PoliceWantedID())
			{
				this->PoliceWantedID() = ID_NONE;

				int nKillAward = __min(-1, -1*(int(pTargetUser->GetLev())-40)/10);
				this->AddAttrib(_USERATTRIB_PK, nKillAward, SYNCHRO_TRUE);
			}
			else
			{
				// team hunter
				CTeam* pTeam = this->GetTeam();
				if (pTeam)
				{
					CUser* pLeader = UserManager()->GetUser(pTeam->GetLeader());
					if (pLeader)
					{
						if (pLeader->PoliceWantedID() == pTargetUser->GetID())
							pLeader->TeamHuntKill(pTargetUser->GetID(), pTargetUser->GetLev(), pTargetUser->GetName());
					}
					else	// in other thread?
					{
						char buf[1024] = {0};
						REMOTE_CALL0* pInfo = (REMOTE_CALL0*)&buf;
						pInfo->ucFuncType	= REMOTE_CALL_TEAM_HUNTKILL;
						pInfo->idUser		= pTeam->GetLeader();
						pInfo->IntParam[0]	= pTargetUser->GetID();
						pInfo->IntParam[1]	= pTargetUser->GetLev();
						strcpy((char*)(pInfo->IntParam[2]), pTargetUser->GetName());
						pInfo->nSize		= sizeof(REMOTE_CALL0) + 2*sizeof(int)+strlen(pTargetUser->GetName())+1;
						MapGroup(PID)->QueryIntraMsg()->RemoteCall(pInfo);
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::TeamHuntKill (OBJID idTarget, int nTargetLev, const char* pszTargetName)
{
	if (idTarget != this->PoliceWantedID())
		return;

	CTeam* pTeam = this->GetTeam();
	IF_NOT (pTeam)
		return;

	IF_NOT (pTeam->GetLeader() == this->GetID())
		return;

	// ok now
	this->PoliceWantedID() = ID_NONE;
		
	int nKillAward = __min(-1, -1*(nTargetLev-40)/10);
	this->AddAttrib(_USERATTRIB_PK, nKillAward, SYNCHRO_TRUE);

	// broadcast msg
	MSGBUF szMsg = "";
	std::sprintf(szMsg, STR_TEAM_HUNT, pszTargetName, this->GetName());
	this->BroadcastMapMsg(szMsg, true);
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsMyWantedTarget (CUser* pTarget)
{
	IF_NOT (pTarget)
		return false;

	OBJID idWanted = this->WantedInfo().idWanted;
	if (ID_NONE == idWanted)
		return false;

	//CWantedData* pData = CWantedList::s_WantedList.GetWanted(idWanted);
	return false; // (pData && 0 == strcmp(pData->GetStr(DATA_TARGET_NAME), pTarget->GetName()));
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsPoliceWantedTarget(CUser* pTarget)
{
	IF_NOT (pTarget)
		return false;

	// police wanted kill
	if (pTarget->GetID() == this->PoliceWantedID())
		return true;

	// team hunter, leader get the police wanted for this target
	CTeam* pTeam = this->GetTeam();
	if (pTeam)
	{
		CUser* pLeader = UserManager()->GetUser(pTeam->GetLeader());
		if (pLeader && pLeader->PoliceWantedID() == pTarget->GetID())
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
void CUser::BeKill(IRole* pRole /*= NULL*/)
{
	bool bDropItem	= true;
	bool bDropExp	= true;
	/*CItem* pItem = this->GetItemByType(GHOST_GEM_AVOID_DEATH);
	if (pItem)
	{
		this->SendSysMsg(STR_AVOID_DEATH, pItem->GetStr(ITEMDATA_NAME));
		this->EraseItem(pItem->GetID(), true);
		this->SetAttrib(_USERATTRIB_LIFE, this->GetMaxLife(), SYNCHRO_TRUE);
		return;
	}
	else if (pItem = this->GetItemByType(GHOST_GEM_AMULET))
	{
		this->SendSysMsg(STR_AVOID_DEATH, pItem->GetStr(ITEMDATA_NAME));
		this->EraseItem(pItem->GetID(), true);
		this->SetAttrib(_USERATTRIB_LIFE, 1, SYNCHRO_TRUE);
		return;
	}
	else if (pItem = this->GetItemByType(GHOST_GEM_SCAPEGOAT))
	{
		this->SendSysMsg(STR_AUTO_USE_SCAPEGOAT, pItem->GetStr(ITEMDATA_NAME));
		this->EraseItem(pItem->GetID(), true);
		bDropExp = bDropItem = false;
	}
	else if (pItem = this->GetItemByType(GHOST_GEM_REBORN))
	{
		m_tAutoReborn.Startup(AUTO_REBORN_SECS);
	}*/
	
	// ����״̬����������е�״̬��

	ClrAttackTarget();
	if (QueryMagic())
		QueryMagic()->AbortMagic(true);
//	CRole::DetachStatus(this->QueryRole(), STATUS_LOCK);
//	CRole::DetachStatus(this->QueryRole(), STATUS_FREEZE);

	this->SetStatus(STATUS_DIE);
	StandTurnoff();

	m_bGhost	= false;
	OBJID	idRebornMap = ID_NONE;
	POINT	pos;
	if (this->GetLev() <= MAX_RETURN_BORN_POS_LEV)
	{
		CGameMap* pMap = MapManager()->GetGameMap(DEFAULT_LOGIN_MAPID);
		IF_OK (pMap)
			this->SetRecordPos(pMap->GetID(), DEFAULT_LOGIN_POSX, DEFAULT_LOGIN_POSY);
	}
	else
	{
		IF_OK(GetMap()->GetRebornMap(&idRebornMap, &pos))
			this->SetRecordPos(idRebornMap, pos.x, pos.y);
	}
	KillCallPet();
	/*if(m_pMount)
	{
		m_pMount->SetInt(ITEMDATA_INTIMACY, ::CutTrail(0, m_pMount->GetInt(ITEMDATA_INTIMACY) - INTIMACY_DEAD_DEC), UPDATE_TRUE);
		this->SendSysMsg(STR_DEC_MOUNT_INTIMACY);

		// synchro
		CMsgItemInfo	msg;
		IF_OK(msg.Create(m_pMount, ITEMINFO_UPDATE))
			SendMsg(&msg);
	}*/

	// no pk pulishment in pk field
	CGameMap* pMap = MapManager()->QueryMap(this->GetMapID());
	IF_OK (pMap)
	{
		// ��Ϊ����WITH_BLOCK���أ�Ϊ����������ʬ������͸����Ҫ����ͼ�ϵĽ�ɫ��
		pMap->DecRole(this->GetPosX(), this->GetPosY());
		
		if(!pMap->IsNeverWoundMap())
		{
			// ����
			SetMaxLifePercent(m_data.GetMaxLifePercent()/2);		// ��SetMaxLifePercent��֤������1/8
		}
		// ����Ʒ ����������
		if (pMap->IsPkField() || pMap->IsSynMap())
		{
			// drop item
			{
				int nChance = 30;
				if(!pMap->IsDeadIsland() && bDropItem) // ������������Ʒ
					m_pPackage->RandDropItem(_MAP_PKFIELD, nChance);
			
			}
			
			// fly out
			/*if (pMap->IsPkField())
			{
				if (idRebornMap != ID_NONE)
					this->FlyMap(idRebornMap, pos.x, pos.y);
			}
			*/

			// set reborn pos to DoubleDragon city if not in syn war but in syn map
			if (pMap->IsSynMap() && !pMap->IsWarTime())
			{
				CONST OBJID ID_DDCITY	= 1002;
				CONST POINT POS_REBORN	= { 438, 398 };
				this->SetRecordPos(ID_DDCITY, POS_REBORN.x, POS_REBORN.y);
			}

			return;
		}
		else if (pMap->IsPrisonMap())
		{
			// drop item
			{
				if(!pMap->IsDeadIsland() && bDropItem) // ������������Ʒ
				{
					int nChance = __min(90, 20+this->GetPk()/2);
					m_pPackage->RandDropItem(_MAP_PRISON, nChance);
				}
			
			}

			return;
		}
	}
	else
		return;
	
	if(!pRole)		// no killer
		return ;
	
	// pk pulishment      
	CUser* pUserKiller = NULL; 
	pRole->QueryObj(OBJ_USER, IPP_OF(pUserKiller));

	if (pUserKiller && !pMap->IsDeadIsland())// ������ ���ɹ��� ��Ǯ ����Ʒ ��װ����Ч
	{	// kill by other player
		CSyndicate* pSyn = this->GetSyndicate();
		CSyndicate* pSynKiller = pUserKiller->GetSyndicate();
		if (pSyn && pSynKiller && (pSyn->IsHostile(pSynKiller->GetID()) || pSynKiller->IsHostile(pSyn->GetID())))
		{
			// �Է����ڵж԰���
		//	this->QuerySynAttr()->DecProffer(PROFFER_BEKILL);
			pSyn->QueryModify()->AddData(SYNDATA_REPUTE, -1*SYNREPUTE_BEKILL);
			//pSynKiller->QueryModify()->AddData(SYNDATA_REPUTE, SYNREPUTE_BEKILL);
			//�����������
			//pUserKiller->QuerySynAttr()->AddReputeInc(SYNREPUTE_BEKILL);
		}

		// �Լ����Ǵ�������״̬�żӳ���
		if (!QueryStatus(STATUS_CRIME))
			QueryEnemy()->Add(pUserKiller->GetID(), pUserKiller->GetName(), SYNCHRO_TRUE, UPDATE_TRUE);

		// drop money
		{
			// ����2004.10.28�İ����޸�	---- zlong
			DWORD dwMoneyDroped = 0;
			if (GetPk() < PKVALUE_REDNAME)								// ����
				dwMoneyDroped = this->GetMoney()*(RandGet(40)+10)/100;	// ��Ǯ 10% ~ 50%
			else if (GetPk() < PKVALUE_BLACKNAME)						// ����
				dwMoneyDroped = this->GetMoney()*(RandGet(50)+50)/100;	// ��Ǯ 50% ~ 100%
			else														// ����
				dwMoneyDroped = this->GetMoney();						// ��Ǯ 100%

			if (dwMoneyDroped > 0)
				this->DropMoney(dwMoneyDroped, this->GetPosX(), this->GetPosY());
		}

		// drop item    //change huang 2004.1.12   //todo 
		if (bDropItem)
		{
			// ����2004.10.28�İ����޸�	---- zlong
			bool bDropItem = false;
			int nChance = 0;
			if (GetPk() < PKVALUE_REDNAME)								// ����
				nChance = 10 + RandGet(40);								// ����Ʒ 10% ~ 50%
			else if (GetPk() < PKVALUE_BLACKNAME)						// ����
				nChance = 50 + RandGet(50);								// ����Ʒ 50% ~ 100%
			else														// ����
				nChance	= 100;											// ����Ʒ 100%

			//int nItems	  = m_setItem.size();
			int nItems		= m_pPackage->GetAmount();
			int nDropItem = (nItems * nChance) / 100;

			m_pPackage->RandDropItem(nDropItem);

		}

		// drop equipment                 //change huang 2004.1.12
		if (bDropItem)
		{
			// ����2004.10.28�İ����޸�	---- zlong
			BOOL bDropEquipment = false;
			int nEquipDropNum = 0;                  //must lost equip item num.
			if(this->GetPk() >= PKVALUE_BLACKNAME)
				nEquipDropNum = 1;					// ������PK������װ�������һ��

			std::vector<OBJID>	setPosition;

			for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
			{
				CItemPtr pEquip = GetEquipItemByPos(i);
				
				//if(pEquip && !pEquip->IsNeverDropWhenDead())
				//	setPosition.push_back(i);
			}
			if (setPosition.size() > 0)
			{
				for (int i=0; i<__min(nEquipDropNum, setPosition.size()); i++)
				{
					int nIndex = ::RandGet(setPosition.size());
					OBJID idPosition = setPosition[nIndex];

					CItemPtr pEquip = GetEquipItemByPos(idPosition);
					
					if(pEquip)
					{
						/*if (ITEMPOSITION_WEAPONR == idPosition)
						{
							CItem* pWeaponL = this->GetEquipItemByPos(ITEMPOSITION_WEAPONL);
							if (pWeaponL)
								pEquip = pWeaponL;
						}*/
						POINT	pos;
						pos.x	= GetPosX();
						pos.y	= GetPosY();
						if (GetMap()->FindDropItemCell(USERDROPITEM_RANGE, &pos))
						{
							this->DropItem(pEquip->GetID(), pos.x, pos.y);
							bDropEquipment = true;
						}
					}
					else
						::LogSave("GetEquipItemByPos failed item does not exists in position [ %u ].", idPosition);
				}
				setPosition.clear();
				
				if (bDropEquipment)
				{
					CMsgPlayer msg;
					if (msg.Create(this->QueryRole()))
						this->BroadcastRoomMsg(&msg, EXCLUDE_SELF);
				}
			}
		}

		// loss exp
		/*if (bDropExp)
		{
			// ����2004.10.28�İ������ӵ�	---- zlong
			int nLossExpPercent = 0;
			if (GetPk() < PKVALUE_REDNAME)								// ����
				nLossExpPercent	= 1;									// ��ʧ��������1%����
			else if (GetPk() < PKVALUE_BLACKNAME)						// ����
				nLossExpPercent	= 2;									// ��ʧ��������2%����
			else														// ����
				nLossExpPercent	= 3;									// ��ʧ��������3%����

			int nLevExp = 0;
			CLevupexpData* pLevupexp	= LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + this->GetLev());
			if (!pLevupexp)
				pLevupexp = LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + __max(0, this->GetLev()-1));
			if (pLevupexp)
				nLevExp = pLevupexp->GetInt(LEVUPEXPDATA_EXP);
			
			__int64 nExpLost = ((__int64)nLevExp) * nLossExpPercent / 100;
			
			if (nExpLost > 0)				
				AddAttrib(_USERATTRIB_EXP, -1*nExpLost, SYNCHRO_TRUE);
		}*/

		// bad guy in police wanted
		/*if (PoliceWanted().GetWanted(this->GetID()))
		{
			this->GotoJail();
			PoliceWanted().DelWanted(this->GetID());
		}*/

		// dec pk value ---- ����2004.10.28�������� -- zlong
		if (this->GetPk() > 0)
			this->AddPk(-1*PKVALUE_DEC_PERDEATH);
	}
	else if(pUserKiller && pMap->IsDeadIsland())
	{
		// �Լ����Ǵ�������״̬�żӳ���
		if (!QueryStatus(STATUS_CRIME))
			QueryEnemy()->Add(pUserKiller->GetID(), pUserKiller->GetName(), SYNCHRO_TRUE, UPDATE_TRUE);
	}
	else	// kill by monster
	{
		CAiNpc* pMonster = NULL;
		if (pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)))
		{
			CUser* pUser = pMonster->QueryOwnerUser();
			// �Լ����Ǵ�������״̬�żӳ���
			if (pUser && !QueryStatus(STATUS_CRIME))
				QueryEnemy()->Add(pUser->GetID(), pUser->GetName(), SYNCHRO_TRUE, UPDATE_TRUE);
		}

		if (!pMap->IsDeadIsland())
		{
			// money
			DWORD dwMoneyLost = ::RandGet(this->GetMoney()/3);
			if (dwMoneyLost > 0)
				this->DropMoney(dwMoneyLost, this->GetPosX(), this->GetPosY());
			
			// item
			if (bDropItem)
			{
				int nChance = 33;
				if (this->GetLev() < 10)
					nChance = 5;

				m_pPackage->RandDropItem(_MAP_NONE, nChance);
			}

			// guard
			if (pMonster && (pMonster->IsGuard() || pMonster->IsPkKiller()))
			{
				if (this->GetPk() >= PKVALUE_BLACKNAME)
					this->GotoJail();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void CUser::AwardBattleExp(int nExp, bool bGemEffect/*=true*/)
{// ����������ս���еõ����߿۳�����ֵ��
	return; //temp before cleaned
	if (GetLev() > ADJUST_EXPFORMAT_LEVEL)
		nExp /= 10;

	if (nExp == 0)
		return;

	if (nExp < 0)
	{// �۾���
		this->AddAttrib(_USERATTRIB_EXP, nExp, SYNCHRO_TRUE);
		return;
	}

	// gem effect
	if (bGemEffect)
	{
		int nAddPercent = this->GetGemExpEffect();
		nExp += nExp*nAddPercent/100;

#ifdef _DEBUG
		if (nAddPercent != 0)
			this->SendSysMsg(_TXTATR_NORMAL, "got gem exp add percent: %d", nAddPercent);
#endif
	}

	if (this->GetLev() >= MAX_USERLEV)
		return;

	if (this->GetLev() >= MASTER_USERLEV)
		nExp /= 2;

#ifdef _DEBUG
	this->SendSysMsg(_TXTATR_NORMAL, "got battle exp: %d", nExp);
#endif

	// ���Ӿ���
	//CLevupexpData* pLevupexp	= LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + this->GetLev());
	//if (!pLevupexp)
		return;

	int nLevupExp = 0; // pLevupexp->GetInt(LEVUPEXPDATA_EXP);
	int nOrgProgress = ::MulDiv(this->GetExp(), 1000, nLevupExp);

	int nNewExp = nExp + this->GetExp();
	if (nNewExp >= nLevupExp)
	{
		this->SetAttrib(_USERATTRIB_EXP, 0, SYNCHRO_TRUE);
		this->IncLev(1);
		if(IsAutoAllot())
			this->AllotPoint();		//? add and allot
		else
			this->AddAttrib(_USERATTRIB_ADDPOINT, _ADDITIONALPOINT_NUM, SYNCHRO_TRUE);

		// �������Ѫ��
		CMsgUserAttrib	msg;
		if (msg.Create(GetID(), _USERATTRIB_MAXLIFE, GetMaxLife()))
			SendMsg(&msg);
		// 2003.2.9 �����Զ�����Ѫ��
		this->SetAttrib(_USERATTRIB_LIFE, this->GetMaxLife(), SYNCHRO_TRUE);
		this->SetAttrib(_USERATTRIB_MANA, this->GetMaxMana(), SYNCHRO_TRUE);

		CMsgAction msgAction;
		if (msgAction.Create(this->GetID(), 0, 0, 0, actionUplev, 0, 0))
			this->BroadcastRoomMsg(&msgAction, INCLUDE_SELF);

		// team life broacast
		if (this->GetTeam())
			this->BroadcastTeamLife(true);

		// save info
		m_data.SaveInfo();
	}
	else
	{
		this->SetAttrib(_USERATTRIB_EXP, nNewExp, SYNCHRO_TRUE);

		int nCurProgress = ::MulDiv(this->GetExp(), 1000, nLevupExp);

		bool bSave = false;
		int nLev = this->GetLev();
		if (nLev >= 110)
		{
			if (nOrgProgress/5 != nCurProgress/5)
				bSave = true;				
		}
		else if (nLev >= 100)
		{
			if (nOrgProgress/10 != nCurProgress/10)
				bSave = true;				
		}
		else if (nLev >= 80)
		{
			if (nOrgProgress/20 != nCurProgress/20)
				bSave = true;				
		}
		else if (nLev >= 60)
		{
			if (nOrgProgress/50 != nCurProgress/50)
				bSave = true;				
		}
		else
		{
			if (nOrgProgress/100 != nCurProgress/100)
				bSave = true;				
		}

		if (bSave)
			m_data.SaveInfo();
	}

	// ������ʦ����
	if (GetTutor() && GetLev() >= _MIN_GIVEEXP_LEV)
		m_dwExpToTutor += nExp * TUTOREXP_PERCENT / 100;
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsAtkable(IRole* pTarget, bool bSendHint)
{
	if (!pTarget)
		return false;

	if (!this->IsAlive())
	{
		if (bSendHint)
			this->SendSysMsg(STR_DIE_FORGIVE);
		return false;
	}

	if (!pTarget->IsAlive())
	{
	//	if (bSendHint)
	//		this->SendSysMsg("����Ϊ�󣬽�ֹ��ʬ��");
		return false;
	}

	if (!this->IsPkEnable(pTarget))
	{
		if (bSendHint)
			this->SendSysMsg(STR_NOT_PK_MODE);
		return false;
	}
	
	if(GetID() == pTarget->GetID())
		return false;

	if(!pTarget->IsBeAtkable())
		return false;	

	CNpc* pNpc;
	if(pTarget->QueryObj(OBJ_NPC, IPP_OF(pNpc)))
	{
		if(pNpc->IsSynFlag() && GetSynID() != ID_NONE && pNpc->GetSynID() != ID_NONE)
		{
			//---jinggy---���ǹ�����ɣ����������빥��İ��ɳ�Ա�ſ��Դ�---begin
		/*	CGameMap * pMapSyn = this->GetMap();
			if(pMapSyn->IsSynMap())
			{
				if(pMapSyn->IsWarTime())
				{
					//�������빥��İ��ɣ��Ͳ��ܴ�
					CNpc * pWarLetterNpc = pMapSyn->GetNpcSynWarLetter();
					if(!pWarLetterNpc)
						return false;

					if(this->GetSynID() != (pWarLetterNpc->GetApplyAttackerSynID()))
						return false;
					
				}
				else //��ս��ʱ�䲻������
					return false;
			}*/
			//---jinggy---���ǹ�����ɣ����������빥��İ��ɳ�Ա�ſ��Դ�---end
			CSyndicate* pSyn = SynManager()->QuerySyndicate(GetSynID());
			if(pSyn && pSyn->IsNearSyn(pNpc->GetSynID()))
				return false;
		}
	}

	CUser* pUserTarget = NULL;
	pTarget->QueryObj(OBJ_USER, IPP_OF(pUserTarget));

	// ʥս�޸�Ϊ����ֵΪ����Ȼ����PK
//	if (pUserTarget && this->GetExp() < 0)
//	{
//		if (bSendHint)
//			this->SendSysMsg(STR_NOT_PK_EXP);
//		return false;
//	}

	// map check
	if (!(this->GetMap() && pTarget->GetMap() && this->GetMap() == pTarget->GetMap()))
		return false;

	if (GetMap()->IsNewbieMap() || (GetMap()->IsPkDisable() && pUserTarget))
	{
		if (bSendHint)
			this->SendSysMsg(STR_PK_FORBIDDEN);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
bool CUser::Create(PROCESS_ID idProcess, SOCKET_ID idSocket, OBJID idUser)
{
	CHECKF(CMapGroup::IsValidMapGroupProcessID(idProcess));
	m_idProcess	= idProcess;
	m_idSocket	= idSocket;

	m_nDir		= 0;	//DEFAULT_LOGIN_DIR;
	m_nPose		= 0;	//DEFAULT_LOGIN_POSE;
	m_nEmotin	= 0;	//DEFAULT_LOGIN_EMOTION;

	// װ��DATA
	if(!m_data.Create(idUser, Database()))
		return false;

	// temp attrib
	m_data.m_Info.usMaxEnergy	= 100;
	m_data.m_Info.usEnergy		= m_data.m_Info.usMaxEnergy;

	// �����ͼ
	m_nPosX		= this->m_data.m_Info.usRecordX;
	m_nPosY		= this->m_data.m_Info.usRecordY;
	OBJID idMap	= this->m_data.m_Info.idRecordmap;
	m_pMap		= MapManager()->GetGameMap(idMap);
	if(!m_pMap)		//? ���ͼ
	{
		m_nPosX		= DEFAULT_LOGIN_POSX;
		m_nPosY		= DEFAULT_LOGIN_POSY;
		OBJID idMap	= DEFAULT_LOGIN_MAPID;
		m_pMap		= MapManager()->GetGameMap(idMap);
		CHECKF(m_pMap);
	}

	Init();
	CreateAllPet();

	// װ��USER�������
	IDatabase* pDb = Database();
	if(!CreateAllFriend(pDb))
		return false;
	if(!CreateAllTutor(pDb))
		return false;
	if(!QueryEnemy()->Create(idProcess, this, pDb))
		return false;
	if(!CreateAllItem(pDb))
		return false;
	//if (!CreateWeaponSkill(pDb))
	//	return false;
	//if(!m_pBattleSystem)
	//	return false;
	//if (!m_pMagic || !m_pMagic->CreateAll())
	//	return false;
	if (!m_pSyn || !m_pSyn->Create())
		return false;
	if (!m_setStatus)
		return false;

	//---jinggy---2004-11-19---��ʼ��װ������ֵ������---begin
	UpdateEquipmentExp_Init();
	//---jinggy---2004-11-19---��ʼ��װ������ֵ������---end

	//---����ϵͳ---begin
	/*m_pTaskDetail = CTaskDetail::CreateNew();
	IF_NOT(m_pTaskDetail && m_pTaskDetail->Create(m_idProcess, this))
		return false;*/
	//---����ϵͳ---end

	// divoice
/*	if (this->GetTaskItemByType(TYPE_DIVOICEITEM))
	{
		m_data.SetMate(NOMATE_NAME, false);
	}
*/

	// status
	SetStatus(STATUS_NORMAL);
	m_data.SetLastLogin();

	// life?...
	if (this->GetLife() <= 0)
		this->AddAttrib(_USERATTRIB_LIFE, 1, SYNCHRO_TRUE);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::Init			()		// login �� change map_group��Ҫִ�еĲ���
{
	m_tFight.SetInterval(this->GetIntervalAtkRate());		// ͽ�ֹ�Ƶ��
	m_tFight.Update();

	m_tXp.SetInterval(ADD_XP_SECS);
	m_tXp.Update();

	m_tSlowHealLife.SetInterval(SLOWHEALLIFE_MS);
	m_tSlowHealLife.Update();

	m_tSlowHealMana.SetInterval(SLOWHEALLIFE_MS);
	m_tSlowHealMana.Update();

	m_tAutoHealLife.SetInterval(AUTOHEALLIFE_TIME);
	m_tAutoHealLife.Update();

	m_tEquipmentDurability.SetInterval(DURABILITY_DEC_TIME);		// every 12s change durability
	m_tEquipmentDurability.Update();

	m_tPK.SetInterval(PK_DEC_TIME);		// every 1 minutes reduce 2 pk value //change huang 2004.1.11
	m_tPK.Update();

	m_tTeam.SetInterval(TIME_TEAMPRC);
	m_tTeam.Update();

	//m_pBattleSystem	= new CBattleSystem(this->m_idProcess, this);
	//ASSERT(m_pBattleSystem);
	m_pMagic = CMagic::CreateNew(m_idProcess, this->QueryRole());
	ASSERT(m_pMagic);
	m_pSyn	= CSynAttr::CreateNew(m_idProcess, this);
	ASSERT(m_pSyn);
	m_setStatus	= CStatusSet::CreateNew(true);
	ASSERT(m_setStatus);
	DEBUG_TRY
	if(m_nStep == STEP_LOGIN)
		if(this->IsStudentFull())
			Announce()->DeleteAnnounceByUserID(this->GetID(),true);
		else
            Announce()->Create(Database(),this->GetID());
	DEBUG_CATCH("Announce()->Create(Database(),this->GetID()) ERROR!");

	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::SaveInfo			()
{
	m_data.SaveInfo();
	//save all pet
	SaveItemInfo();
	//SaveAllWeaponSkillInfo();
	m_pMagic->SaveInfo();
	m_pSyn->SaveInfo();
	//@ ������Ҫ���̵Ķ���
	//...

	// �湱�׸���ʦ�ľ���
	if (GetTutor() && GetLev() >= _MIN_GIVEEXP_LEV)
	{
		if (m_dwExpToTutor > 0)
		{
			int nTutorExp2	= m_dwExpToTutor * TUTOREXP2_PERCENT / TUTOREXP_PERCENT;
			SQLBUF szSQL;
			std::sprintf(szSQL, "UPDATE %s SET exp=exp+%u, tutor_exp=tutor_exp+%u WHERE tutor_id=%u AND tutor_lev>%u LIMIT 1",
				_TBL_TUTOREXP, m_dwExpToTutor, nTutorExp2, m_pTutor->GetTutorID(), GetLev());
			Database()->ExecuteSQL(szSQL);

			m_dwExpToTutor	= 0;	// ������0
		}
	}

}

//////////////////////////////////////////////////////////////////////
/*bool CUser::SaveAllWeaponSkillInfo()
{
	for(int i = 0; i < m_pUserWeaponSkillSet->GetAmount(); i++)
	{
		CUserWeaponSkill* pData = m_pUserWeaponSkillSet->GetObjByIndex(i);
		if(pData)
			pData->SaveInfo();
	}
	return true;
}*/

//////////////////////////////////////////////////////////////////////
bool CUser::AddLeaveWord(LPCTSTR szRecv, LPCTSTR szWords)
{
	for(int i = 0; i < m_setFriend.size(); i++)
	{
		CFriend* pFriend = m_setFriend[i];
		if(pFriend && strcmp(pFriend->GetFriendName(), szRecv) == 0)
		{
			ASSERT(UserManager()->GetUser(pFriend->GetFriendID()) == NULL);
			if(pFriend->IsLeaveWordEnable())
			{
				LeaveWord()->InsertWords(GetName(), szRecv, szWords);
				SendSysMsg(STR_MSG_SENT);
				return true;
			}
			else
			{
				SendSysMsg(STR_MSG_FAILED, LEAVEWORD_INTERVAL_MINS);
			}
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
// application
//////////////////////////////////////////////////////////////////////
/*
int	 CUser::AdjustData(int nData, int nAdjust, int nMaxData/ *=0* /)
{
	if(nAdjust>=ADJUST_PERCENT)
		return MulDiv(nData, nAdjust-ADJUST_PERCENT, 100);

	if(nAdjust<=ADJUST_SET)
		return -1*nAdjust + ADJUST_SET;

	if(nAdjust==ADJUST_FULL)
	{
		ASSERT(nMaxData != 0);
		return nMaxData;
	}

	return nData + nAdjust;
}
*/

//////////////////////////////////////////////////////////////////////
bool CUser::SendMsg(CNetMsg* pMsg)
{
	if(false
//		||pMsg->GetType() == _MSG_ACTION 
		||pMsg->GetType() == _MSG_INTERACT
//		||pMsg->GetType() == _MSG_PLAYER
//		||pMsg->GetType() == _MSG_TRADE
		)
	{
		DEBUG_SENDMSG(pMsg->GetType(), m_idSocket)
	}

	return MapGroup(PID)->QueryIntraMsg()->SendClientMsg(m_idSocket, pMsg);
}

//////////////////////////////////////////////////////////////////////
void CUser::BroadcastRoomMsg(CNetMsg* pMsg, bool bSendSelf /*= false*/)		
{ 
	CRole::BroadcastRoomMsg(pMsg, bSendSelf);
}

//////////////////////////////////////////////////////////////////////
void CUser::BroadcastRoomMsg(LPCTSTR szMsg, bool bSendSelf /*= false*/)		
{
	mapgroup_kernel::CMsgTalk	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		this->BroadcastRoomMsg(&msg, bSendSelf);
}

//////////////////////////////////////////////////////////////////////
void CUser::BroadcastMapMsg(CNetMsg* pMsg, bool bSendSelf /*= false*/)		
{ 
	//CMapPtr pMap = MapManager()->GetGameMap(GetMapID());
	CMapPtr pMap = this->GetMap();
	if(pMap)
		UserManager()->BroadcastMapMsg(pMap->GetID(), pMsg, bSendSelf?NULL:this);
}

//////////////////////////////////////////////////////////////////////
void CUser::BroadcastMapMsg(LPCTSTR szMsg, bool bSendSelf /*= false*/)		
{
	mapgroup_kernel::CMsgTalk	msg;
	if(msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		this->BroadcastMapMsg(&msg, bSendSelf);
}

//////////////////////////////////////////////////////////////////////

bool CUser::SendSysMsg(const char* fmt, ...)
{ 
	MSGBUF	szMsg;
    vsprintf( szMsg, fmt, (char*) ((&fmt)+1) );
	
	mapgroup_kernel::CMsgTalk msg;
	if (msg.Create(SYSTEM_NAME, GetName(), szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
		return this->SendMsg(&msg);

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::SendSysMsg(int nChannel, const char* fmt, ...)
{ 
	MSGBUF	szMsg;
    vsprintf( szMsg, fmt, (char*) ((&fmt)+1) );
	
	mapgroup_kernel::CMsgTalk msg;
	if (msg.Create(SYSTEM_NAME, GetName(), szMsg, NULL, 0x00ffff00, nChannel))
		return this->SendMsg(&msg);

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::ChangeMap()
{
	POINT	pos;
	pos.x	= GetPosX();
	pos.y	= GetPosY();

	int nX[9]={0,1,-1,1,0,1,-1,-1,0};
	int nY[9]={0,1,-1,0,1,-1,1,0,-1};
	for (int i=0; i<9; i++)
	{
		POINT posTest = pos;
		posTest.x += nX[i];
		posTest.y += nY[i];

		OBJID	idMap = ID_NONE;
		POINT	posTarget = {0, 0};
		if (GetMap()->GetPassageMap(&idMap, &posTarget, posTest))
		{
			if(FlyMap(idMap, posTarget.x, posTarget.y) != FLYMAP_ERROR)
				return true;
			else
				break;
		}
	}

	FlyMap(DEFAULT_LOGIN_MAPID, DEFAULT_LOGIN_POSX, DEFAULT_LOGIN_POSY);
	UserManager()->KickOutSocket(m_idSocket, "�������㣡");
	return false;
}

//////////////////////////////////////////////////////////////////////
OBJID CUser::GetMapID()
{
	if(m_pMap)
		return m_pMap->GetID();
	return ID_NONE;
}

//////////////////////////////////////////////////////////////////////
OBJID CUser::GetRecordMapID()
{
	return m_data.GetRecordMap();
}

//////////////////////////////////////////////////////////////////////
void CUser::GotoJail(void)
{
	CGameMap* pMap = MapManager()->QueryMap(MAP_PRISON);
	IF_OK (pMap)
	{
		char szMsg[1024] = "";
		std::sprintf(szMsg, STR_GOTO_JAIL, this->GetName());
		UserManager()->BroadcastMsg(szMsg);
		
		this->QuitTeam();
		
		POINT pos = pMap->GetPortal();
		this->FlyMap(MAP_PRISON, pos.x, pos.y);
		
		// reset reborn pos
		{
			OBJID	idRebornMap = ID_NONE;
			POINT	pos;
			IF_OK(GetMap()->GetRebornMap(&idRebornMap, &pos))
				this->SetRecordPos(idRebornMap, pos.x, pos.y);
		}
	}				
}

//////////////////////////////////////////////////////////////////////
// return false: can't fly
int CUser::FlyMap(OBJID idMap, int nPosX, int nPosY, int idxPassage)				// call - may be delete this;
{
	if(m_pMap == NULL)			// not in map
	{
		LOGWARNING("The player cuts the screen continuously.");
		return FLYMAP_ERROR;
	}

	POINT	posNew;
	posNew.x = nPosY;
	posNew.y = nPosY;
	if (idxPassage >= 0) {
		m_pMap->GetPassageMap(&idMap, &posNew, idxPassage);
	}

	if (idMap == ID_NONE)
		idMap = this->GetMapID();

	PROCESS_ID idProcess = MapManager()->GetProcessID(idMap);
	if(!CMapGroup::IsValidMapGroupProcessID(idProcess) || idProcess == m_idProcess)
	{
		CGameMap* pNewMap = MapManager()->GetGameMap(idMap);
		//if(!pNewMap || !pNewMap->IsValidPoint(nPosX, nPosY))
		//{
		//	LOGMSG("FLY The coordinates of the map [%u] [%u] [%u] are illegal!", idMap, nPosX, nPosY);
		//	return FLYMAP_ERROR;
		//}

		DEBUG_TRY	// VVVVVVVVVVVVVV
		LeaveMap();
		m_pMap		= pNewMap;
		m_nPosX		= posNew.x;
		m_nPosY		= posNew.y;

		// ���ͻ�Ӧ��Ϣ
		CMsgAction	msg;
		if(msg.Create(GetID(), nPosX, nPosY, GetDir(), actionFlyMap, pNewMap->GetDocID()))
			SendMsg(&msg);

		EnterMap();
		DEBUG_CATCH("FlyMap")		// AAAAAAAAAAA

		return FLYMAP_NORMAL;
	}
	else
	{
		ChangeMapGroup(idProcess, idMap, nPosX, nPosY);					// call - delete this;
		return FLYMAP_MAPGROUP;
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::OnTimer(time_t tCurr)
{
	if(m_pMap == NULL)		// not join map ok.
		return;

	// tick ------------------------------------
#ifndef _DEBUG
	DEBUG_TRY
	DEADLOOP_CHECK(PID, "m_dequeServerTick")
	if(!IsAgent())
	{
		DWORD dwTimeNow = ::TimeGet();

		if (m_dwFirstServerTick == 0)
		{	// this code will run only once with each user
			m_dwFirstServerTick = dwTimeNow;
			m_dwLastServerTick	= dwTimeNow;

			m_dwLastRcvClientTick = dwTimeNow;	// pre set this

			//CMsgTick msg;
			//if(msg.Create(GetID()))
			//	this->SendMsg(&msg);

			m_dequeServerTick.push_back(dwTimeNow);
		}
		else
		{
			if (dwTimeNow >= m_dwLastServerTick+TICK_SECS*1000)
			{
				m_dwLastServerTick	= dwTimeNow;
				m_dequeServerTick.push_back(dwTimeNow);

				//CMsgTick msg;
				//if(msg.Create(GetID()))
				//	this->SendMsg(&msg);
			}
		}

		if (m_dwLastRcvClientTick != 0)
		{
			//if (dwTimeNow-m_dwLastRcvClientTick >= TICK_SECS*1000*2.5)
			//	UserManager()->KickOutSocket(m_idSocket);		// 	, "tick not feedback"			
		}
	}
	DEBUG_CATCH("@m_dwServerTickCount@")
#endif

	//---jinggy---2004-11-12--Begin---������ϸ���װ���Ƿ�����ս�꾭���ʱ��
	DEBUG_TRY
	DEADLOOP_CHECK(PID, "UpdateEquipmentExp")
	UpdateEquipmentExp();
	DEBUG_CATCH("CUser UpdateEquipmentExp crash");
	//---jinggy---2004-11-12--End---������ϸ���װ���Ƿ�����ս�꾭���ʱ��

	//---jinggy---����Ҽ�����ɣ�������������---begin
	DEBUG_TRY	
	if(this->GetSyndicate())
	{
		if(!m_tTimeOnline.IsActive())
			m_tTimeOnline.Startup(SYNMEM_TIMEONLINE_INTERVAL);

		if(this->m_tTimeOnline.ToNextTime(SYNMEM_TIMEONLINE_INTERVAL))
		{
			this->QuerySynAttr()->IncTimeOnline(SYNMEM_TIMEONLINE_INTERVAL/60); 
		}
	}
	DEBUG_CATCH("this->QuerySynAttr()->IncTimeOnline(TIMEONLINE_INTERVAL_DETECT/60); //����10���ӵ�����ʱ��");
	//---jinggy---����Ҽ�����ɣ�������������---end


	DEBUG_TRY
	DEADLOOP_CHECK(PID, "ProcessAutoAttack")
	ProcessAutoAttack();
	DEBUG_CATCH("CUser ProcAttack_Hand2Hand carsh")

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "ProcXpVal")
	if (m_tXp.ToNextTime())
		this->ProcXpVal();
	DEBUG_CATCH("CUser ProcXpVal crash")

	DEBUG_TRY
	// 2003.2.8����Ժ�������ҩʱ������Ѫ����coding here
	if (m_tSlowHealLife.ToNextTime() && m_setSlowHealUp2Life.Size() > 0)
		this->ProcSlowHealLifeUp();
	DEBUG_CATCH("CUser ProcSlowHealLifeUp crash")

	DEBUG_TRY
	if (m_tSlowHealMana.ToNextTime() && m_setSlowHealUp2Mana.Size() > 0)
		this->ProcSlowHealManaUp();
	DEBUG_CATCH("CUser ProcSlowHealManaUp crash")

//	DEBUG_TRY	//����Ҫ�����Ӫ����
//	DEADLOOP_CHECK(PID, "ProcAutoHealLife")
//	if (m_tAutoHealLife.ToNextTime())
//		this->ProcAutoHealLife();
//	DEBUG_CATCH("CUser autoheallife timer crash.")

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "ENERGY timer")
	if(IsAlive())		// && !this->QueryTransformation()
	{
//		if (!this->IsWing())
		{
			if(QueryStatus(STATUS_PELT))
			{
				if (m_tEnergy.ToNextTime(DEL_ENERGY_PELT_SECS))
				{
					if (this->GetEnergy() < DEL_ENERGY_PELT)
						CRole::DetachStatus(this->QueryRole(), STATUS_PELT);
					else
						AddAttrib(_USERATTRIB_ENERGY, -1*DEL_ENERGY_PELT, SYNCHRO_TRUE);
				}
			}
			else if(GetEnergy() < GetMaxEnergy())
			{
#ifdef	PALED_DEBUG
					SendSysMsg("WALK --------------");
#endif
				if (m_tEnergy.ToNextTime(ADD_ENERGY_STAND_SECS))
					AddAttrib(_USERATTRIB_ENERGY, ADD_ENERGY_STAND, SYNCHRO_TRUE);
			}
		}
	}
	DEBUG_CATCH("CUser ENERGY timer crash.")

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "QueryMagic()->OnTimer")
	if (QueryMagic())
		QueryMagic()->OnTimer(tCurr);
	DEBUG_CATCH("CUser magic timer crash.")

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "status")
	// �������Ӳ��ִ��������ж��Ƿ������ϵͳ״̬
	// bDetachTeamStatus = true ��ʾ��Ҫ�������������ص�״̬
	bool	bDetachTeamStatus = false;
	bool	bDetachAddExpStatus = false;	// �Ƿ���STATUS_ADD_EXP
	CTeam* pTeam = GetTeam();
	if (IsAlive() && pTeam)
	{
		if (pTeam->GetMemberAmount() < TEAM_STATUS_REQ_ROLES)
			bDetachTeamStatus = true;
		
		OBJID idLeader = pTeam->GetLeader();
		if (idLeader != this->GetID())
		{
			CUser* pLeader = UserManager()->GetUser(idLeader);
			if (!pLeader || !pLeader->IsAlive()
				|| this->GetMapID() != pLeader->GetMapID()
				|| this->GetDistance(pLeader->QueryMapThing()) > _RANGE_TEAM_STATUS)
			{
				bDetachTeamStatus = true;
			}
			if (!pLeader || !pLeader->QueryStatus(STATUS_ADD_EXP))
				bDetachAddExpStatus = true;
		}
	}
	else
	{
		bDetachTeamStatus = true;
		bDetachAddExpStatus = true;
	}

	for(int i = QueryStatusSet()->GetAmount()-1; i >= 0; i--)
	{
		IStatus* pStatus = QueryStatusSet()->GetObjByIndex(i);
		if(pStatus)
		{
			pStatus->OnTimer(tCurr);
			if (!pStatus->IsValid()
				|| (bDetachTeamStatus && pStatus->GetID() >= STATUS_TEAM_BEGIN && pStatus->GetID() <= STATUS_TEAM_END)
				|| (bDetachAddExpStatus && pStatus->GetID() == STATUS_ADD_EXP))
			{
				OBJID idStatus = pStatus->GetID();
				QueryStatusSet()->DelObj(idStatus);

				// superman list
				if (idStatus == STATUS_XPFULL)
				{
					CalcSupermanKills();
					CalcFightRate();
				}
			}
		}
	}
	DEBUG_CATCH("CUser status timer crash.")

	/*
	DEBUG_TRY
	DEADLOOP_CHECK(PID, "UpdateEquipmentDurability")
	if (m_tEquipmentDurability.ToNextTime())
		this->UpdateEquipmentDurability();
	DEBUG_CATCH("UpdateEquipmentDurability crashed.")
	*/

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "ProcessPkTimer")
	if (m_tPK.ToNextTime())
		this->ProcessPkTimer();
	DEBUG_CATCH("CUser pk timer crash.")


	DEBUG_TRY
	DEADLOOP_CHECK(PID, "ProcessMineTimer")
	if (m_tMine.IsActive() && m_tMine.ToNextTime())
	{
		this->ProcessMineTimer();
		ResetEnergyInc();
	}
	DEBUG_CATCH("CUser mine timer crash.")


	DEBUG_TRY
	DEADLOOP_CHECK(PID, "ProcessTeamTimer")
	if (this->GetTeam() && m_tTeam.ToNextTime())
		this->ProcessTeamTimer();
	DEBUG_CATCH("CUser team timer crash.")

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "AbortTransform")
	if (m_pTransformation && m_tTransformation.TimeOver())
	{
		AbortTransform();
	}
	DEBUG_CATCH("CUser Transformation crash.")

	DEBUG_TRY
	DEADLOOP_CHECK(PID, "KillCallPet")
	if(m_tCallPet.IsActive() && m_tCallPet.TimeOver())
	{
		KillCallPet();
	}
	DEBUG_CATCH("CUser CallPet crash.")

	/*DEBUG_TRY
	if(m_pMount)
	{
		DEADLOOP_CHECK(PID, "m_pMount")
		if(!m_tMount.IsActive())
			m_tMount.Startup(MOUNT_ADD_INTIMACY_SECS);
		else if(m_tMount.ToNextTime())
		{
			if(m_pMount->GetInt(ITEMDATA_INTIMACY) < MAX_INTIMACY)
			{
				m_pMount->SetInt(ITEMDATA_INTIMACY, m_pMount->GetInt(ITEMDATA_INTIMACY) + 1, UPDATE_TRUE);
				this->SendSysMsg(STR_INC_MOUNT_INTIMACY);

				// synchro
				CMsgItemInfo	msg;
				if (msg.Create(m_pMount, ITEMINFO_UPDATE))
					SendMsg(&msg);
			}
		}
	}
	DEBUG_CATCH("CUser CallPet crash.")*/

/*
	DEBUG_TRY
	DEADLOOP_CHECK(PID, "LeaveWord()->ShowWords")
	if (IsMoreLeaveWord() && m_tLeaveWord.ToNextTime(5))
	{
		LeaveWord()->ShowWords(this);
	}
	DEBUG_CATCH("CUser LeaveWord crash.")
*/

	DEBUG_TRY
	if(!m_bStand && m_tStand.TimeOver(KEEP_STAND_MS) && IsAlive())
	{
		StandTurnon();
	}
	DEBUG_CATCH("Stand crash.")

	// ������ʽ��Ա����6���ӣ�������������10��
	DEBUG_TRY
	if (this->GetSynID() != ID_NONE)
	{
		if (!m_tIncRepute.IsActive())
			m_tIncRepute.Startup(SYNREPUTE_SECS);
		else if (m_tIncRepute.ToNextTime())
		{
			CSyndicate* pSyn = this->GetSyndicate();
			if (pSyn)
			{
				if(this->GetSynRank()>RANK_RESERVED)
				{
					//�Ӱ�������
					pSyn->QueryModify()->AddData(SYNDATA_REPUTE, SYNREPUTE_VAL_PEREACH, false);
					//�Ӱ��ɹ��׶�
					this->QuerySynAttr()->AddProffer(SYNREPUTE_VAL_PROFFER);
				}
			}
		}
	}
	DEBUG_CATCH("Auto inc syndicate repute crash.");

	// Ǳ��ֵÿ6��������1��
	DEBUG_TRY
	if (!m_tIncPotential.IsActive())
		m_tIncPotential.Startup(INC_POTENTIAL_SECS);
	else if (m_tIncPotential.ToNextTime())
	{
		this->AddAttrib(_USERATTRIB_POTENTIAL, INC_POTENTIAL_NUM, SYNCHRO_TRUE);
	}
	DEBUG_CATCH("Inc potential crash.");

	// 
	DEBUG_TRY
	if (IsAlive() && m_data.GetMaxLifePercent() < 1000)
	{
		if (!m_tAutoHealMaxLife.IsActive())
			m_tAutoHealMaxLife.Startup(AUTOHEAL_MAXLIFE_TIME);
		else if (m_tAutoHealMaxLife.ToNextTime())
		{
			int nMaxLifePercent = m_data.GetMaxLifePercent();
			if (nMaxLifePercent >= 500)
				nMaxLifePercent += AUTOHEAL_MAXLIFE_FLESH_WOUND;		// ���˻ָ�
			else
				nMaxLifePercent += AUTOHEAL_MAXLIFE_GBH;				// ���˻ָ�
			SetMaxLifePercent(nMaxLifePercent);

			if (nMaxLifePercent >= 1000)
				m_tAutoHealMaxLife.Clear();
		}
	}
	DEBUG_CATCH("Auto heal max life crash.");

	/*DEBUG_TRY
	if (m_tAutoReborn.IsActive() && m_tAutoReborn.IsTimeOut())
	{
		m_tAutoReborn.Clear();
		if (!IsAlive())
		{
			CItem* pItem = this->GetItemByType(GHOST_GEM_REBORN);
			if (pItem)
			{
				this->SendSysMsg(STR_AUTO_USE_REBORN, pItem->GetStr(ITEMDATA_NAME));
				this->EraseItem(pItem->GetID(), true);
				this->Reborn(false);	// ԭ�ظ���
			}
		}
	}
	DEBUG_CATCH("Auto use reborn gem crash");*/

}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessAutoAttack		()
{
	// �ٶ��ͻ��޺�����߹����ٶ�
	int nFightPause = m_nFightRate + m_nFightPause;

	/*if (m_pBattleSystem && m_pBattleSystem->IsActived() 
		&& m_tFight.ToNextTick(nFightPause)
		&& (!QueryMagic() || !QueryMagic()->IsActive()))
	{
		m_pBattleSystem->ProcAttack_Hand2Hand();
		m_nFightPause	= 0;
		if(m_pBattleSystem->GetTargetID() != ID_NONE)
			ResetEnergyInc();
	}*/
}

//////////////////////////////////////////////////////////////////////
void CUser::ClearAllStatus		()
{
	ClsXpVal();
	for(int i = QueryStatusSet()->GetAmount() - 1; i >= 0; i--)
	{
		IStatus* pStatus = QueryStatusSet()->GetObjByIndex(i);
		if(pStatus)
			QueryStatusSet()->DelObj(pStatus->GetID());
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessPkTimer()
{
	if (this->GetPk() > 0)
	{
		CGameMap* pMap = MapManager()->QueryMap(this->GetMapID());
		IF_OK (pMap) 
		{
			if (pMap->IsPrisonMap())
			{
				this->AddPk(-1*PKVALUE_DEC_ONCE_IN_PRISON);
				return;
			}
		}
		this->AddPk(-1*PKVALUE_DEC_ONCE);
	}
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsPkEnable(IRole* pRole)
{
	if (!pRole || this->GetID() == pRole->GetID())
		return false;
	
	if (pRole->IsMonster())
		return true;

	CNpc* pNpc = NULL;
	pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc));
	
	if (pNpc)
		return true;

	bool bCanPk = false;
	switch(this->GetPkMode())
	{
	case	PKMODE_FREE:
		bCanPk = true;
		break;

	case	PKMODE_TEAM:               //change huang 2004.1.15
		{
			bCanPk = true;

			CTeam* pTeam = this->GetTeam();
			if(pTeam && pTeam->IsTeamMember(pRole->GetID()))
				bCanPk = false;
			
			if (this->GetFriend(pRole->GetID()))
				bCanPk = false;
			
			CUser* pUser = NULL; 
			if(pRole->QueryObj(OBJ_USER, IPP_OF(pUser)))
			{
				if(this->IsMate(pUser))
					bCanPk = false;
			}	
			return bCanPk;
		}
		break;
		
	case    PKMODE_SYNDICATE:     //add huang 2004.1.15
		{
			bool bCanPk = true;

			CUser* pUser = NULL;
			if (pRole->QueryObj(OBJ_USER, IPP_OF(pUser)) && this->GetSynID() != ID_NONE)
			{
				if (this->GetMasterSynID() == pUser->GetMasterSynID() || this->IsMate(pUser))
					bCanPk = false;
				else
				{				
					CSyndicate* pSyn = SynManager()->QuerySyndicate(this->GetMasterSynID());
					if (pSyn)
					{
						if ( pSyn->IsFriendly(pUser->GetSynID()))
							bCanPk = false;
					}
				}
			}
			return bCanPk;
		}
		break;

	case	PKMODE_ARRESTMENT:
		{
			if(pRole->IsEvil())
				bCanPk = true;
		}
		break;

	case	PKMODE_SAFE:
		bCanPk = false;
		break;

	default:
		ASSERT(!"switch pk mode");
		bCanPk = false;
		break;
	}

	return bCanPk;
}

//////////////////////////////////////////////////////////////////////
void CUser::Reborn(bool bChgPos/*=true*/)
{
	if (this->IsAlive())
		return;

	SetStatus(STATUS_NORMAL);
	m_bGhost	= false;
	ClsXpVal();					//? �ͻ������¿�ʼ��ʱ
	m_tAutoHealMaxLife.Clear();

	SetAttrib(_USERATTRIB_LIFE, GetMaxLife(), SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_MANA, GetMaxMana(), SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_KEEPEFFECT, GetEffect(), SYNCHRO_BROADCAST);
	SetAttrib(_USERATTRIB_LOOKFACE, GetLookFace(), SYNCHRO_BROADCAST);
	AddAttrib(_USERATTRIB_ENERGY, 100, SYNCHRO_TRUE);
	AddAttrib(_USERATTRIB_MAXENERGY, 0, SYNCHRO_TRUE);	// ���������Ϊ��ͬ��

	const bool bMaxLife = true;
	this->BroadcastTeamLife(bMaxLife);

	if (bChgPos)
	{
		if (ID_NONE != m_data.GetRecordMap())
			this->FlyMap(m_data.GetRecordMap(), m_data.GetRecordX(), m_data.GetRecordY());
	}

	// lock
	CRole::AttachStatus(this->QueryRole(), STATUS_PK_PROTECT, 0, CHGMAP_LOCK_SECS);
//	m_tLock.Startup(CHGMAP_LOCK_SECS);
}

//////////////////////////////////////////////////////////////////////
void CUser::TransformGhost()
{
	m_bGhost = true;

	SetAttrib(_USERATTRIB_KEEPEFFECT, SetEffect(KEEPEFFECT_GHOST), SYNCHRO_BROADCAST);
	SetAttrib(_USERATTRIB_LOOKFACE, GetLookFace(), SYNCHRO_BROADCAST);
}

//////////////////////////////////////////////////////////////////////
// ��������ϵͳ
//////////////////////////////////////////////////////////////////////
int CUser::AddPk(int nAdd)			// auto synchro
{
	ASSERT(nAdd != 0);

	if(abs(m_data.GetPk() + nAdd) < MAX_PKLIMIT)
		m_data.SetPk(__max(0, m_data.GetPk() + nAdd));
	else
		m_data.SetPk(MAX_PKLIMIT);

	if(nAdd > 0)
		SetStatus(STATUS_PKVALUE, SYNCHRO_TRUE);
	else
		ClsStatus(STATUS_PKVALUE, SYNCHRO_TRUE);

	this->SetAttrib(_USERATTRIB_PK, this->GetPk(), SYNCHRO_TRUE);
	return m_data.GetPk();
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcXpVal()
{// ÿ30��+15�����ˣ�30�����

	if(!IsAlive())
	{
		ClsXpVal();
		return;
	}
	
	IStatus* pStatus = QueryStatus(STATUS_XPFULL);	//XPFULL�ڼ䲻�ӣ�Ҳ�����
	if (pStatus)
		return;

	if (m_dwXP == MAX_USER_XP)	// full already
	{
		SetXp(0);
		m_tXp.Update();
	}
	else
	{
		/*if (GetMap() && GetMap()->IsBoothEnable())		// �����̯��ͼ�Ͳ���XP��
			return;

		//---jinggy---begin
		//�������״̬����XPֵ
		IStatus * pStatus = QueryStatus(STATUS_ADJUST_XP);
		int nAddXpValue = ADD_XP_VALUE;
		if (pStatus)
		{
			nAddXpValue = ::CutTrail(0, AdjustData(nAddXpValue, pStatus->GetPower()));						
		}		
		//---jinggy---end
		AddXp(nAddXpValue);*/
	}		

#ifdef _DEBUG
	this->SendSysMsg("[Debug]��һ�����%u��Xp��Xp=%d������", m_dwXP, MAX_USER_XP);
#endif
}

//////////////////////////////////////////////////////////////////////
void CUser::ClsXpVal(bool bSynchro)
{
	SetXp(0);
	m_tXp.Update();

	if (bSynchro)
		CRole::DetachStatus(this->QueryRole(), STATUS_XPFULL);
}

//////////////////////////////////////////////////////////////////////
bool CUser::BurstXp()
{
	if(m_dwXP < MAX_USER_XP)
		return false;

	IStatus* pStatus = QueryStatus(STATUS_XPFULL);
	if (pStatus)
		return true;

	CRole::AttachStatus(this->QueryRole(), STATUS_XPFULL, 0, MAX_XPFULL_SECS);
	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::SetXp(int nXp)
{
	if (nXp < 0 || nXp > MAX_USER_XP)
		return;

	this->SetAttrib(_USERATTRIB_XP, nXp, SYNCHRO_TRUE);

}

//////////////////////////////////////////////////////////////////////
void CUser::AddXp(int nXp)
{
	if (nXp < 0 || nXp > MAX_USER_XP)
		return;

	this->AddAttrib(_USERATTRIB_XP, nXp, SYNCHRO_TRUE);

}

//////////////////////////////////////////////////////////////////////
void CUser::ProcSlowHealLifeUp()
{
	CHECK(m_setSlowHealUp2Life.Size());

	if(!IsAlive() || GetLife() >= GetMaxLife())
	{
		m_setSlowHealUp2Life.Clear();
		return ;
	}

	int nAddLife = m_setSlowHealUp2Life.At(0);
	m_setSlowHealUp2Life.DelObj(0);


	AddAttrib(_USERATTRIB_LIFE, nAddLife, SYNCHRO_TRUE);
	BroadcastTeamLife();
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcSlowHealManaUp()
{
	CHECK(m_setSlowHealUp2Mana.Size());
	
	if(!IsAlive() || GetMana() >= GetMaxMana())
	{
		m_setSlowHealUp2Mana.Clear();
		return ;
	}

	int nAddMana = m_setSlowHealUp2Mana.At(0);
	m_setSlowHealUp2Mana.DelObj(0);
	
	
	AddAttrib(_USERATTRIB_MANA, nAddMana, SYNCHRO_TRUE);
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcAutoHealLife()
{
	if (this->GetPose() != _ACTION_SITDOWN ||
			this->GetLife() >= this->GetMaxLife() ||
				!this->IsAlive())
		return;

	this->AddAttrib(_USERATTRIB_LIFE, AUTOHEALLIFE_EACHPERIOD, SYNCHRO_TRUE);
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessTick(DWORD dwClientTime)
{
#ifdef _DEBUG
	return;
#endif

	if (m_dwFirstClientTick == 0)
		m_dwFirstClientTick = dwClientTime;

	if (dwClientTime < m_dwLastClientTick)
	{	// ridiculous time stamp
		this->SendSysMsg(STR_CONNECTION_OFF);
		UserManager()->KickOutSocket(m_idSocket, "ProcessTick");
		return;
	}

	const int CRITICAL_TICK_PERCENT = 5;

	int nServerTicks = m_dequeServerTick.size();
	if (m_dwLastClientTick != 0 && 
			nServerTicks >= 2 &&
				dwClientTime > m_dwLastClientTick+TICK_SECS*(100+CRITICAL_TICK_PERCENT)*10)	// *10 means 1000ms/100percent
	{	// suspicious time stamp		
		DWORD dwTimeServer = ::TimeGet();
		DWORD dwTimeServerTickInterval = m_dequeServerTick[1]-m_dequeServerTick[0];

		int nEchoTime = dwTimeServer-m_dequeServerTick[1];
		if (nEchoTime < (int)dwClientTime-(int)m_dwLastClientTick-(int)dwTimeServerTickInterval)
		{
			::GmLogSave("������ң�%s��ʹ�ü�������", this->GetName());

			this->SendSysMsg(STR_CONNECTION_OFF);
			UserManager()->KickOutSocket(m_idSocket, "������");
			return;
		}
	}

	m_dwLastClientTick = dwClientTime;

	if (m_dequeServerTick.size() >= 2)
		m_dequeServerTick.pop_front();

	m_dwLastRcvClientTick = ::TimeGet();
}

//////////////////////////////////////////////////////////////////////
// friend
//////////////////////////////////////////////////////////////////////
CFriend* CUser::GetFriend(OBJID idFriend)
{
	for(int i = 0; i < m_setFriend.size(); i++)
	{
		CFriend* pFriend = m_setFriend[i];
		if(pFriend && pFriend->GetFriendID() == idFriend)
			return m_setFriend[i];
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
bool CUser::AddFriend(OBJID idFriend, LPCTSTR szFriendName)		// δ����ظ����
{
	CFriend* pFriend = CFriend::CreateNew();
	if(pFriend && pFriend->CreateRecord(GetID(), idFriend, szFriendName, Database()))
	{
		m_setFriend.push_back(pFriend);
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::DelFriend(OBJID idFriend)
{
	for(int i = 0; i < m_setFriend.size(); i++)
	{
		CFriend* pFriend = m_setFriend[i];
		if(pFriend && pFriend->GetFriendID() == idFriend)
		{
			pFriend->DeleteRecord(Database());
			delete pFriend;
			m_setFriend.erase(m_setFriend.begin() + i);
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
/*BOOL CUser::CreateWeaponSkill(IDatabase* pDb)
{
	CHECKF(pDb);

	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s WHERE owner_id=%u && unlearn=0", _TBL_WEAPONSKILL, this->GetID());
	IRecordset* pRes = pDb->CreateNewRecordset(szSQL);	//VVVVVVVVV
	if(pRes)
	{
		for (int i=0; i<pRes->RecordCount(); i++)
		{
			CUserWeaponSkill*	pSkill	= CUserWeaponSkill::CreateNew(pRes);
			if (pSkill)
				m_pUserWeaponSkillSet->AddObj(pSkill);

			pRes->MoveNext();
		}
		pRes->Release();		//AAAAAAAAAAAAAA
	}
	return true;
}*/

//////////////////////////////////////////////////////////////////////
/*bool CUser::CheckWeaponSubType(int nSubType, int nNum)
{
	CHECKF(nSubType);


	//if(nSubType == 900)		// shield
	//{
	//	if(m_pWeaponL && m_pWeaponL->IsShield() && m_pWeaponL->GetInt(ITEMDATA_AMOUNT) >= nNum)
	//		return true;

	//	return false;
	//}

	if (m_pWeaponR && m_pWeaponR->GetItemSubType() == nSubType && m_pWeaponR->GetInt(ITEMDATA_AMOUNT) >= nNum)
		return true;
	if (m_pWeaponL && m_pWeaponL->GetItemSubType() == nSubType && m_pWeaponL->GetInt(ITEMDATA_AMOUNT) >= nNum)
		return true;

	if (nSubType == 400)
	{
		int setTypes[2]	= {410, 420};

		if (m_pWeaponR && (m_pWeaponR->GetItemSubType() == setTypes[0] || m_pWeaponR->GetItemSubType() == setTypes[1])
			&& m_pWeaponR->GetInt(ITEMDATA_AMOUNT) >= nNum)
		{
			return true;
		}
		if (m_pWeaponL && (m_pWeaponL->GetItemSubType() == setTypes[0] || m_pWeaponL->GetItemSubType() == setTypes[1])
			&& m_pWeaponL->GetInt(ITEMDATA_AMOUNT) >= nNum)
		{
			return true;
		}
	}

	// 500�����������н��ķ��࣬ħ�����Ѿ�û��������࣬����������δ�����Ч -- zlong 2005-03-03
	//if(nSubType == 500)
	//{
	//	nSubType	= 501;	//? ����������ȫ���潣
	//	if (m_pWeaponR && m_pWeaponR->GetItemSubType() == nSubType && m_pWeaponR->GetInt(ITEMDATA_AMOUNT) >= nNum)
	//		return true;
	//	if (m_pWeaponL && m_pWeaponL->GetItemSubType() == nSubType && m_pWeaponL->GetInt(ITEMDATA_AMOUNT) >= nNum)
	//		return true;
	//}
	return false;
}*/

//////////////////////////////////////////////////////////////////////
/*void CUser::AddWeaponSkillExp(int nSkillType, int nExp)
{
	//int nSkillType = GetWeaponSkillType();
	if(nSkillType == ARROW_SUBTYPE)
		return ;

	for (int i=0; i<m_pUserWeaponSkillSet->GetAmount(); i++)
	{
		CUserWeaponSkill* pSkill	= m_pUserWeaponSkillSet->GetObjByIndex(i);
		if (pSkill && pSkill->GetType() == nSkillType)
		{
			int nIncreaseLev	= 0;

			// exp adjusted by lev effect
			if (pSkill->GetLevel() > MASTER_WEAPONSKILLLEVEL)
			{
				int nRatio = 100-(pSkill->GetLevel()-MASTER_WEAPONSKILLLEVEL)*20;
				if (nRatio < 10)
					nRatio = 10;

				nExp = ::MulDiv(nExp, nRatio, 100)/2;
			}

			// new exp
			int nNewExp	= __max(nExp+pSkill->GetExp(), pSkill->GetExp());

#ifdef _DEBUG
			this->SendSysMsg(_TXTATR_NORMAL, "Add Weapon Skill exp: %u, CurExp: %u", nExp, nNewExp);
#endif


			int nLevel = pSkill->GetLevel();
			if (nLevel >= 1 && nLevel < MAX_WEAPONSKILLLEVEL)
			{
				if (nNewExp > nWeaponSkillLeveUpNeedExp[nLevel] || nLevel >= pSkill->GetOldLev()/2 && nLevel < pSkill->GetOldLev())
				{
					nNewExp			= 0;
					nIncreaseLev	= 1;
				}
			}
			else
				return;


			if (pSkill->GetLevel() < this->GetLev()/10+1		// base level is 1
					|| pSkill->GetLevel() >= MASTER_WEAPONSKILLLEVEL)
			{
				// every 10 percent save exp once.
				bool bSave = false;

				CHECK(nWeaponSkillLeveUpNeedExp[nLevel]);
				int nOldExpPercent = ::MulDiv(pSkill->GetExp(), 100, nWeaponSkillLeveUpNeedExp[nLevel]);
				int nNewExpPercent = ::MulDiv(nNewExp, 100, nWeaponSkillLeveUpNeedExp[nLevel]);

				if ((nOldExpPercent%10) != 0 && (nNewExpPercent%10) == 0)
					bSave = true;

				// inc lev save exp too
				if (nIncreaseLev > 0)
					bSave = true;

				// set new exp
				pSkill->SetExp(nNewExp, bSave);

				if (nIncreaseLev > 0)
				{
					pSkill->SetLevel(pSkill->GetLevel() + nIncreaseLev, true);

					CMsgWeaponSkill msg;
					if (msg.Create(pSkill->GetType(), pSkill->GetLevel(), pSkill->GetExp()))
						this->SendMsg(&msg);

					this->SendSysMsg(STR_WEAPON_SKILL_UP);

					if (QueryMagic())
						QueryMagic()->UserWeaponSkillUpLevel(nSkillType, pSkill->GetLevel());
				}
				else
				{
					CMsgFlushExp msg;
					if (msg.Create(MSGFLUSHEXP_WEAPONSKILL, pSkill->GetType(), nNewExp))
						this->SendMsg(&msg);

					if(nExp && QueryMagic())
						QueryMagic()->AutoLearnWeaponSkill(nSkillType, pSkill->GetLevel(), nExp);
				}
			}

			return;
		}
		else if (!pSkill)
			LOGERROR("���ִ�������������ȼ������ݡ�");
	}

	// ���û��nSkillType�������������ȣ������¼�¼��
	UserWeaponSkillInfoStruct info;
	info.id			= ID_NONE;
	info.idowner	= this->GetID();
	info.nExp		= __max(0, nExp);
	info.nType		= nSkillType;
	info.ucLevel	= 1;
	info.ucOldLev	= 1;

	// check unlearn magic
	OBJID idNew = ID_NONE;
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT id FROM %s WHERE owner_id=%u && type=%d", _TBL_WEAPONSKILL, GetID(), nSkillType);
	CAutoPtr<IRecordset> pRes = _Database(PID)->CreateNewRecordset(szSQL);
	if(pRes)
		idNew = pRes->GetInt(0);

	CUserWeaponSkill* pSkill	= CUserWeaponSkill::InsertNewRecord(&info, GameDataDefault()->GetUserWeaponSkill(), idNew);
	IF_OK(pSkill)
	{
		m_pUserWeaponSkillSet->AddObj(pSkill);
		CMsgWeaponSkill msg;
		if (msg.Create(pSkill->GetType(), pSkill->GetLevel(), pSkill->GetExp()))
			this->SendMsg(&msg);
	}
}*/

//////////////////////////////////////////////////////////////////////
/*DWORD CUser::GetWeaponSkillLev (OBJID idWeaponType)
{
	int nSkillType = (idWeaponType%1000000)/1000;
	int nWeaponSkills = m_pUserWeaponSkillSet->GetAmount();
	for (int i=0; i<nWeaponSkills; i++)
	{
		CUserWeaponSkill* pSkill	= m_pUserWeaponSkillSet->GetObjByIndex(i);
		if (pSkill && pSkill->GetType() == nSkillType)
			return pSkill->GetLevel();
	}

	return 1;
}*/

//////////////////////////////////////////////////////////////////////
/*CUserWeaponSkill* CUser::GetWeaponSkill (int nSkillType)
{
	IF_NOT (m_pUserWeaponSkillSet)
		return NULL;

	int nWeaponSkills = m_pUserWeaponSkillSet->GetAmount();
	for (int i=0; i<nWeaponSkills; i++)
	{
		CUserWeaponSkill* pSkill	= m_pUserWeaponSkillSet->GetObjByIndex(i);
		if (pSkill && pSkill->GetType() == nSkillType)
			return pSkill;
	}

	return NULL;
}*/

//////////////////////////////////////////////////////////////////////
/*BOOL CUser::AwardWeaponSkill (int nSkillType, int nLev)
{
	CUserWeaponSkill* pSkill = this->GetWeaponSkill(nSkillType);
	if (pSkill)
	{
		pSkill->SetLevel(nLev, true);

		// update to client
		CMsgWeaponSkill msg;
		IF_OK (msg.Create(pSkill->GetType(), pSkill->GetLevel(), pSkill->GetExp()))
			this->SendMsg(&msg);

		SendSysMsg(STR_WEAPON_SKILL_UPLEV);
		return true;
	}
	else
	{
		// ���û��nSkillType�������������ȣ������¼�¼��
		UserWeaponSkillInfoStruct info;
		info.id			= ID_NONE;
		info.idowner	= this->GetID();
		info.nExp		= 0;
		info.nType		= nSkillType;
		info.ucLevel	= nLev;
		info.ucOldLev	= 1;

		// check unlearn magic
		OBJID idNew = ID_NONE;
		SQLBUF	szSQL;
		sprintf(szSQL, "SELECT id FROM %s WHERE owner_id=%u && type=%d", _TBL_WEAPONSKILL, GetID(), nSkillType);
		CAutoPtr<IRecordset> pRes = _Database(PID)->CreateNewRecordset(szSQL);
		if(pRes)
			idNew = pRes->GetInt(0);

		CUserWeaponSkill* pSkill = CUserWeaponSkill::InsertNewRecord(&info, GameDataDefault()->GetUserWeaponSkill(), idNew);
		IF_OK (pSkill)
		{
			m_pUserWeaponSkillSet->AddObj(pSkill);

			// update to client
			CMsgWeaponSkill msg;
			IF_OK (msg.Create(pSkill->GetType(), pSkill->GetLevel(), pSkill->GetExp()))
				this->SendMsg(&msg);
		}

		return true;
	}
}*/

//////////////////////////////////////////////////////////////////////
/*void CUser::SendAllWeaponSkillInfo()
{
	for (int i=0; i<m_pUserWeaponSkillSet->GetAmount(); i++)
	{
		CUserWeaponSkill* pSkill	= m_pUserWeaponSkillSet->GetObjByIndex(i);
		if (pSkill)
		{
			CMsgWeaponSkill msg;
			if (msg.Create(pSkill->GetType(), pSkill->GetLevel(), pSkill->GetExp()))
				this->SendMsg(&msg);
		}
	}
}*/


//////////////////////////////////////////////////////////////////////
/*bool CUser::UnlearnAllSkill()
{
	CHECKF(m_pUserWeaponSkillSet);

	int nWeaponSkills = m_pUserWeaponSkillSet->GetAmount();
	for (int i = nWeaponSkills-1; i >= 0; i--)		// del obj
	{
		CUserWeaponSkill* pSkill	= m_pUserWeaponSkillSet->GetObjByIndex(i);
		if(pSkill)
		{
			pSkill->SetOldLev(pSkill->GetLevel(), UPDATE_FALSE);
			pSkill->SetUnlearn(true, UPDATE_TRUE);
			//pSkill->Update());

			//if(m_pMagic && m_pMagic->GetID() == pData->GetID())
			//	m_pMagic = NULL;
			int nType = pSkill->GetType();
			m_pUserWeaponSkillSet->DelObj(pSkill->GetID());

			// synchro
			CMsgAction	msg;
			IF_OK(msg.Create(this->GetID(), this->GetPosX(), this->GetPosY(), this->GetDir(), actionDropSkill, nType))
				this->SendMsg(&msg);
		}
	}

	return true;
}*/
//////////////////////////////////////////////////////////////////////
bool CUser::CreateAllFriend(IDatabase* pDb)
{
	SQLBUF		szSQL;
	std::sprintf(szSQL, "SELECT * FROM %s WHERE userid = %u LIMIT %d", _TBL_FRIEND, GetID(), _MAX_USERFRIENDSIZE);
	IRecordset*	pRes = pDb->CreateNewRecordset(szSQL);
	if(pRes)
	{
		for(int i = 0; i < pRes->RecordCount(); i++)
		{
			CFriendPtr	pFriend = CFriend::CreateNew();
			if(pFriend)
			{
				if(pFriend->Create(pRes))
					m_setFriend.push_back(pFriend);
				else
					delete pFriend;
			}
			pRes->MoveNext();
		}
		pRes->Release();
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::DeleteAllFriend()
{
	for(int i = 0; i < m_setFriend.size(); i++)
	{
		SAFE_DELETE(m_setFriend[i]);
	}
	m_setFriend.clear();
}

//////////////////////////////////////////////////////////////////////
void CUser::SendFriendInfo()
{
	int	nAmount = m_setFriend.size();
	CHECK(nAmount <= _MAX_USERFRIENDSIZE);

	for(int i = 0; i < nAmount; i++)
	{
		CFriend* pFriend = m_setFriend[i];
		if(pFriend)
		{
			OBJID	idFriend	= pFriend->GetFriendID();
			CUser* pFriendUser	= UserManager()->GetUser(idFriend);
			bool	bOnline		= pFriendUser!=0;
			DWORD	dwLookFace	= pFriendUser ? pFriendUser->GetLookFace() : 0;
			int		nLevel		= pFriendUser ? pFriendUser->GetLev() : 0;

			CMsgFriend	msg;
			if(msg.Create(_FRIEND_GETINFO, idFriend, pFriend->GetFriendName(), bOnline, dwLookFace, nLevel))
				SendMsg(&msg);

			if(!bOnline)
				MapGroup(PID)->QueryIntraMsg()->TransmitMsg(&msg, GetSocketID(), GetID());		// ֪ͨ������ͼ�飬�´����Һ������ߵ���Ϣ
		}
	}

	// ͨ��WORLD����ת���������������
	for(int i = 0; i < nAmount; i++)
	{
		CFriend* pFriend = m_setFriend[i];
		if(pFriend)
		{
			OBJID	idFriend	= pFriend->GetFriendID();
			CMsgFriend	msg;
			IF_OK(msg.Create(_FRIEND_ONLINE, GetID(), GetName(), CMsgFriend::ONLINE_STATUS, GetLookFace(), GetLev()))
				MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(&msg, idFriend);
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////
void CUser::BroadcastFriendsMsg	(CNetMsg* pMsg)
{
	if (!pMsg)
		return;

	int	nAmount = m_setFriend.size();
	CHECK(nAmount <= _MAX_USERFRIENDSIZE);

	for(int i = 0; i < nAmount; i++)
	{
		CFriend* pFriend = m_setFriend[i];
		if(pFriend)
		{
			OBJID	idFriend	= pFriend->GetFriendID();
			CUser* pUserFriend = UserManager()->GetUser(idFriend);
			if (pUserFriend)
				pUserFriend->SendMsg(pMsg);
			else
			{
				MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(pMsg, pFriend->GetFriendID());
			}
		}
	}

	// ͨ��WORLD���Ĳ������������

	return;
}

//////////////////////////////////////////////////////////////////////
// mapgroup
//////////////////////////////////////////////////////////////////////
bool CUser::ChangeMapGroup(PROCESS_ID idProcess, OBJID idMap, int nPosX, int nPosY)					// call - delete this;
{
	SaveInfo();		// SaveAllInfo
#ifdef	PALED_DEBUG
	SendSysMsg("�ӵ�ͼ[%s][%d][%d]������[%d][%d]...", GetMap()->GetName(), GetMapID(), m_idProcess-3, idMap, idProcess-3);
#endif
	// transformation
	m_data.m_Info.dwMonsterType	= 0;
	m_data.m_Info.dwMonsterSecs = m_tTransformation.GetRemain();
	if(QueryTransformation() && m_data.m_Info.dwMonsterSecs > 0)
	{
		m_data.m_Info.dwMonsterType	= QueryTransformation()->GetMonsterType();
	}

	MapGroup(PID)->QueryIntraMsg()->SendSocketUserInfo(idProcess, m_idSocket, GetInfo());

	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = GetEquipItemByPos(i);
		if(pEquip)
		{
			ItemInfoStruct info;
			pEquip->GetInfo(&info);
			MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_ITEM, &info, sizeof(info));
		}
	}

	m_pPackage->SendAllObjInfo(MapGroup(PID), idProcess);
	/*for( i = 0; i < m_setItem.size(); i++)
	{
		CItemPtr pItem = m_setItem[i];
		if(pItem)
		{
			ItemInfoStruct info;
			pItem->GetInfo(&info);
			MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_ITEM, &info, sizeof(info));
		}
	}*/

	for(int i = 0; i < m_setFriend.size(); i++)
	{
		CFriendPtr pFriend = m_setFriend[i];
		if(pFriend)
			MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_FRIEND, pFriend->GetInfo(), sizeof(FriendInfoStruct));
	}

	{
		CEnemyInfoStruct	info;
		if(QueryEnemy()->GetInfo(&info))
			MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_ENEMY, &info, sizeof(CEnemyInfoStruct));
	}

	/*for( i = 0; i < QueryWeapenSkill()->GetAmount(); i++)
	{
		CUserWeaponSkill* pSkill = QueryWeapenSkill()->GetObjByIndex(i);
		if(pSkill)
			MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_WEAPONSKILL, pSkill->GetInfo(), sizeof(UserWeaponSkillInfoStruct));
	}*/

	if (QueryMagic())
	{
		for(int i = 0; i < QueryMagic()->QuerySet()->GetAmount(); i++)
		{
			MagicInfoStruct	info;
			if(QueryMagic()->GetInfoByIndex(&info, i))
				MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_MAGIC, &info, sizeof(info));
		}
	}
	{
		SynAttrInfoStruct info;
		QuerySynAttr()->GetInfo(&info);
		MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_SYNATTR, &info, sizeof(info));
	}

	// status info
	for(int i = 0; i < QueryStatusSet()->GetAmount(); i++)
	{
		IStatus* pStatus = QueryStatusSet()->GetObjByIndex(i);
		if(pStatus)
		{
			StatusInfoStruct	info;
			if(pStatus->GetInfo(&info))					//? ��ЧINFO������
				MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_STATUS, &info, sizeof(info));
		}
	}

	if(GetTeam())
	{
		TeamInfoStruct info;
		GetTeam()->GetInfo(&info);
		MapGroup(PID)->QueryIntraMsg()->SendObjInfo(idProcess, GetID(), INFO_TEAM, &info, sizeof(info));

		ClrTeam();			//? LeaveMapGroup()ʱ���˳�����
	}

	MapGroup(PID)->QueryIntraMsg()->ChangeMapGroup(idProcess, GetID(), idMap, nPosX, nPosY);

//����ʱ����	LeaveMapGroup();
	UserManager()->LogoutUser(GetSocketID(), false);	// ɾ�����󣬽�����һ��ͼ��, false: not offline

	{
		// stat
		extern struct STAT_STRUCT	g_stat;
		InterlockedIncrement(&g_stat.setDebug[3]);		// debug
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::LeaveMapGroup()
{
//	ASSERT(m_nStep == STEP_ENTERMAP);

	// leave map first(�����뿪��ͼ��������ظ����ʹ���Ϣ)
	CMsgAction msg;
	if (msg.Create(GetID(), 0,0,0, actionLeaveMap))
		this->BroadcastRoomMsg(&msg, EXCLUDE_SELF);

	DestroyBooth();

	if (m_pTeam)
		this->QuitTeam();
/*
	if(IsAlive())
	{
		if(GetMap()->IsStandEnable(GetPosX(), GetPosY()) && !GetMap()->IsRecordDisable())
			this->SetRecordPos(GetMap()->GetID(), GetPosX(), GetPosY());
	}
*/
	SaveInfo();		// SaveAllInfo

	// ������DeleteAllItem֮ǰ�ջػ��޲���
	//CallBackAllEudemon();
	// �л���ͼ����Ҫ����޽���
	

	DeleteAllTutor();
	DeleteAllFriend();
	DeleteAllItem();

	LeaveMap();

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::JoinMap(OBJID idMap, int nPosX, int nPosY)
{
	m_pMap		= MapManager()->GetGameMap(idMap);
	m_nPosX		= nPosX;
	m_nPosY		= nPosY;

	// ���ͻ�Ӧ��Ϣ
	CMsgAction	msg;
	//if(msg.Create(GetID(), nPosX, nPosY, GetDir(), actionFlyMap, m_pMap->GetDocID()))
	//	SendMsg(&msg);

	EnterMap();

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::AppendObjInfo(INFO_ID nType, void* pInfo)
{
	switch(nType)
	{
	case	INFO_ITEM:
		AppendItem((ItemInfoStruct*)pInfo);
		break;
	case	INFO_FRIEND:
		AppendFriend((FriendInfoStruct*)pInfo);
		break;
	case	INFO_ENEMY:
		QueryEnemy()->AppendInfo((CEnemyInfoStruct*)pInfo);
		break;
	//case	INFO_WEAPONSKILL:
	//	AppendWeaponSkill((UserWeaponSkillInfoStruct*)pInfo);
	//	break;
	case	INFO_MAGIC:
		if (QueryMagic())
			QueryMagic()->AppendMagic((MagicInfoStruct*)pInfo);
		break;
	case	INFO_SYNATTR:
		QuerySynAttr()->AppendSynAttr((SynAttrInfoStruct*)pInfo);
		break;
	case	INFO_STATUS:
		AppendStatus((StatusInfoStruct*)pInfo);
		break;
	case	INFO_TEAM:
		AppendTeam((TeamInfoStruct*)pInfo);
		break;
	default:
		ASSERT(!"switch INFO_TYPE");
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::AppendItem(ItemInfoStruct* pInfo)
{
	CHECKF(pInfo->idOwner == GetID());

	CItemPtr pItem = CItem::CreateNew();
	IF_NOT(pItem)
		return false;

	IF_NOT(pItem->Create(GameDataDefault()->GetGameItemData(), pInfo, false))
	{
		pItem->ReleaseByOwner();
		return false;
	}

	if(pInfo->nPosition >= ITEMPOSITION_EQUIPBEGIN && pInfo->nPosition < ITEMPOSITION_EQUIPEND)
	{
		CItemPtr& refpEquip = this->GetEquipItemRef(pInfo->nPosition);
		IF_OK(!refpEquip)
		{
			refpEquip = pItem;
			pItem = NULL;		// �����뱳��
		}
	}

	if(pItem)
		m_pPackage->AddItem(pItem);
	//	m_setItem.push_back(pItem);

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::AppendFriend(FriendInfoStruct* pInfo)
{
	CHECKF(pInfo->idUser == GetID());

	CFriendPtr pFriend;
	pFriend = CFriend::CreateNewFriend(pInfo);
	if(!pFriend)
		return false;

	m_setFriend.push_back(pFriend);

	return true;
}

//////////////////////////////////////////////////////////////////////
/*bool CUser::AppendWeaponSkill(UserWeaponSkillInfoStruct* pInfo)
{
	CHECKF(pInfo->idowner == GetID());

	CUserWeaponSkill*	pSkill	= CUserWeaponSkill::CreateNew(pInfo, GameDataDefault()->GetUserWeaponSkill());
	if (!pSkill)
		return false;

	m_pUserWeaponSkillSet->AddObj(pSkill);

	return true;
}*/

//////////////////////////////////////////////////////////////////////
bool CUser::AppendStatus(StatusInfoStruct* pInfo)
{
	if(pInfo->nTimes > 0)		// more status
	{
		CStatusMore* pStatus = CStatusMore::CreateNew();
		if(pStatus)
		{
			if(pStatus->Create(QueryRole(), pInfo->nStatus, pInfo->nPower, pInfo->nSecs, pInfo->nTimes))
				QueryStatusSet()->AddObj(pStatus->QueryInterface());
			else
				pStatus->ReleaseByOwner();
		}
	}
	else
	{
		CStatusOnce* pStatus = CStatusOnce::CreateNew();
		if(pStatus)
		{
			if(pStatus->Create(QueryRole(), pInfo->nStatus, pInfo->nPower, pInfo->nSecs))
				QueryStatusSet()->AddObj(pStatus->QueryInterface());
			else
				pStatus->ReleaseByOwner();
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// money
//////////////////////////////////////////////////////////////////////
bool CUser::SpendMoney(DWORD dwMoney, bool bSynchro)
{
	if(dwMoney == 0)
		return true;

	if (this->GetMoney() < dwMoney)
		return false;

	DWORD dwNewMoney = this->GetMoney() - dwMoney;
	m_data.SetMoney(dwNewMoney);

	// update to client...
	if(bSynchro)
	{
		CMsgUserAttrib	msg;
		if(msg.Create(this->GetID(), _USERATTRIB_MONEY, dwNewMoney))
			SendMsg(&msg);
	}

	return true;
}

bool CUser::GainMoney(DWORD dwMoney, bool bSynchro /*= true*/)
{
	if(dwMoney == 0)
		return true;

	if(dwMoney < 0)
	{
		LOGWARNING("GainMoney: dwMoney < 0");
	}

	DWORD dwNewMoney = this->GetMoney() + dwMoney;
	if (dwNewMoney > _MAX_MONEYLIMIT)
		return false;

	m_data.SetMoney(dwNewMoney);

	// update to client...
	if(bSynchro)
	{
		CMsgUserAttrib	msg;
		if(msg.Create(this->GetID(), _USERATTRIB_MONEY, dwNewMoney))
			SendMsg(&msg);
	}

	return true;
}

bool CUser::SaveMoney(DWORD dwMoney, bool bSynchro /*= true*/)
{
	if (this->GetMoney() < dwMoney)
	{
		this->SendSysMsg(STR_NOT_ENOUGH_MONEY);
		return false;
	}

	DWORD dwNewMoney = this->GetMoney() - dwMoney;
	DWORD dwNewMoneySaved = this->GetMoneySaved() + dwMoney;
	if (dwNewMoneySaved > _MAX_MONEYLIMIT)
	{
		this->SendSysMsg(STR_TOOMUCH_MONEY_SAVED);
		return false;
	}

	m_data.SetMoney(dwNewMoney);
	m_data.SetMoneySaved(dwNewMoneySaved);

	// update to client...
	if(bSynchro)
	{
		CMsgUserAttrib	msg;
		if(msg.Create(this->GetID(), _USERATTRIB_MONEY, dwNewMoney))
		{
			msg.Append(_USERATTRIB_MONEYSAVED, this->GetMoneySaved());
			SendMsg(&msg);
		}
	}

	return true;
}

bool CUser::DrawMoney(DWORD dwMoney, bool bSynchro /*= true*/)
{
	if (this->GetMoneySaved() < dwMoney)
	{
		SendSysMsg(STR_NOT_ENOUGH_MONEY);
		return false;
	}

	DWORD dwNewMoney = this->GetMoney() + dwMoney;
	DWORD dwNewMoneySaved = this->GetMoneySaved() - dwMoney;
	if (dwNewMoney > _MAX_MONEYLIMIT)
	{
		SendSysMsg(STR_TOOMUCH_MONEY_TO_DRAW);
		return false;
	}

	m_data.SetMoney(dwNewMoney);
	m_data.SetMoneySaved(dwNewMoneySaved);

	// update to client...
	if(bSynchro)
	{
		CMsgUserAttrib	msg;
		if(msg.Create(this->GetID(), _USERATTRIB_MONEY, dwNewMoney))
		{
			msg.Append(_USERATTRIB_MONEYSAVED, this->GetMoneySaved());
			SendMsg(&msg);
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// role
/////////////////////////////////////////////////////////////////////////////
void CUser::SendShow(IRole* pRole)
{
	CMsgPlayer	msg;
	if(msg.Create((IRole*)this))
		pRole->SendMsg(&msg);
}

/////////////////////////////////////////////////////////////////////////////
void CUser::SetStatus(int nStatus, bool bSynchro)
{
	I64 i64OldEffect = GetEffect();
	switch (nStatus)
	{
	case STATUS_ADJUST_DODGE:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_ADJUST_DODGE;
		}
		break;
	case STATUS_ADJUST_XP:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_ADJUST_XP;
		}
		break;
	case STATUS_ADJUST_DROPMONEY:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_ADJUST_DROPMONEY;
		}
		break;
	case	STATUS_NORMAL:           //change huang 2004.1.11
		{
			m_data.m_Info.dwStatus	= nStatus;
			m_data.m_Info.i64Effect	= KEEPEFFECT_NORMAL;

			if (m_data.GetPk() >= PKVALUE_BLACKNAME)
				m_data.m_Info.i64Effect	|= KEEPEFFECT_DEEPRED;
			else if (m_data.GetPk() >= PKVALUE_REDNAME)
				m_data.m_Info.i64Effect	|= KEEPEFFECT_RED;

			CTeam* pTeam = GetTeam();
			if(pTeam && pTeam->GetLeader() == GetID())
				m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAMLEADER;
		}
		break;
	case	STATUS_DIE:
		{
			m_data.m_Info.dwStatus	= nStatus;
			m_data.m_Info.i64Effect	&= KEEPEFFECT_NOT_CLEAR;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_DIE;

			ClearAllStatus();
		}
		break;
	case	STATUS_TEAMLEADER:
		{
		     m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAMLEADER;
		}
		break;
	case	STATUS_CRIME:       
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_CRIME;
		}
		break;
	case	STATUS_SYNCRIME:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_SYNCRIME;
		}
		break;
	case	STATUS_POISON:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_POISON;
		}
		break;
	case	STATUS_PKVALUE:         //change huang 2004.1.11
		{
			// ȡ������״̬����������������
			if (m_data.GetPk() >= PKVALUE_BLACKNAME)
				m_data.m_Info.i64Effect	|= KEEPEFFECT_DEEPRED;
			else if (m_data.GetPk() >= PKVALUE_REDNAME)
				m_data.m_Info.i64Effect	|= KEEPEFFECT_RED;
		}
		break;
	case	STATUS_DEFENCE1:
		{
			m_data.m_Info.i64Effect	&= ~(KEEPEFFECT_DEFENCE2 | KEEPEFFECT_DEFENCE3);
			m_data.m_Info.i64Effect	|= KEEPEFFECT_DEFENCE1;
		}
		break;
	case	STATUS_DEFENCE2:
		{
			m_data.m_Info.i64Effect	&= ~(KEEPEFFECT_DEFENCE1 | KEEPEFFECT_DEFENCE3);
			m_data.m_Info.i64Effect	|= KEEPEFFECT_DEFENCE2;
		}
		break;
	case	STATUS_DEFENCE3:
		{
			m_data.m_Info.i64Effect	&= ~(KEEPEFFECT_DEFENCE1 | KEEPEFFECT_DEFENCE2);
			m_data.m_Info.i64Effect	|= KEEPEFFECT_DEFENCE3;
		}
		break;
	case	STATUS_FREEZE:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_FREEZE;
		}
		break;
	case	STATUS_SMOKE:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_SMOKE;
		}
		break;
	case	STATUS_DARKNESS:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_DARKNESS;
		}
		break;
	case	STATUS_PALSY:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_PALSY;
		}
		break;
	case	STATUS_ATTACK:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_ATTACK;
		}
		break;
	case	STATUS_MAGICDEFENCE:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_MAGICDEFENCE;
		}
		break;
	case	STATUS_REFLECT:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_REFLECT;
		}
		break;
	case	STATUS_REFLECTMAGIC:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_REFLECTMAGIC;
		}
		break;
	case	STATUS_MAGICDAMAGE:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_MAGICDAMAGE;
		}
		break;
	case	STATUS_ATKSPEED:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_ATKSPEED;
		}
		break;
	case	STATUS_LURKER:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_LURKER;
		}
		break;
	case	STATUS_SLOWDOWN1:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_SLOWDOWN1;
		}
		break;
	case	STATUS_SLOWDOWN2:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_SLOWDOWN2;
		}
		break;
	case	STATUS_MAXLIFE:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_MAXLIFE;
		}
		break;
	case	STATUS_MAXENERGY:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_MAXENERGY;
		}
		break;
	case	STATUS_HIDDEN:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_HIDDEN;
		}
		break;
	case	STATUS_ADD_EXP:
		{
			m_data.m_Info.i64Effect	|= KEEPEFFECT_ADD_EXP;
		}
		break;
	case	STATUS_ATTRACT_MONSTER:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_ATTRACT_MONSTER;
		}
		break;
	case	STATUS_XPFULL:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_XPFULL;
		}
		break;
	case	STATUS_PK_PROTECT:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_PK_PROTECT;
		}
		break;
	case	STATUS_PELT:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_PELT;
		}
		break;
	case	STATUS_ADJUST_EXP:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_ADJUST_EXP;
		}
		break;
	// �����ǽ��ϵͳ��ص�״̬ ================
	case	STATUS_TEAMHEALTH:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_HEALTH;
		}
		break;
	case	STATUS_TEAMATTACK:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_ATTACK;
		}
		break;
	case	STATUS_TEAMDEFENCE:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_DEFENCE;
		}
		break;
	case	STATUS_TEAMSPEED:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_SPEED;
		}
		break;
	case	STATUS_TEAMEXP:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_EXP;
		}
		break;
	case	STATUS_TEAMSPIRIT:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_SPIRIT;
		}
		break;
	case	STATUS_TEAMCLEAN:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ALL;
			m_data.m_Info.i64Effect	|= KEEPEFFECT_TEAM_CLEAN;
		}
		break;
	// �����ǽ��ϵͳ���״̬ ===============
	case	STATUS_HEAL:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_HEAL;
		}
		break;
	case	STATUS_FAINT:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_FAINT;
		}
		break;
	case	STATUS_TRUCULENCE:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_TRUCULENCE;
		}
		break;
	case	STATUS_DAMAGE:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_DAMAGE;
		}
		break;
	case	STATUS_ATKER_DAMAGE:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_ATKER_DAMAGE;
		}
		break;
	case	STATUS_FRENZY:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_FRENZY;
		}
		break;
	case	STATUS_TRANSFER_SHIELD:
		{
			m_data.m_Info.i64Effect |= KEEPEFFECT_TRANSFER_SHIELD;
		}
		break;
	case	STATUS_LOCK:
	case	STATUS_SUPER_MATK:
		break;
	default:
		::LogSave("Invalid status: [%u]", nStatus);
//		ASSERT(!"switch status");
	}

	if (STATUS_FREEZE == nStatus || STATUS_FAINT == nStatus)
	{
		this->ClrAttackTarget();	// ֹͣ�Զ�ս��
	}

	/*if(bSynchro && i64OldEffect != GetEffect())
	{
		CMsgUserAttrib msg;
		if (msg.Create(GetID(), _USERATTRIB_KEEPEFFECT, GetEffect()))
		{
			// �ٶȽ�磬�����ƶ��ٶ�
			// �����ƶ��ٶ�
			if (STATUS_TEAMSPEED == nStatus || STATUS_SLOWDOWN1 == nStatus || STATUS_SLOWDOWN2 == nStatus
				|| STATUS_PELT == nStatus)
			{
				// ֻ��֪ͨ�ͻ����޸��ƶ��ٶȣ�������ĸı��ƶ��ٶ�
				msg.Append(_USERATTRIB_SPEED, AdjustSpeed(this->GetSpeed()));
			}
			else if (STATUS_MAXLIFE == nStatus)
			{
				msg.Append(_USERATTRIB_MAXLIFE, this->GetMaxLife());
				msg.Append(_USERATTRIB_LIFE, this->GetLife());
			}
			else if (STATUS_MAXENERGY == nStatus)
			{
				msg.Append(_USERATTRIB_MAXENERGY, this->GetMaxEnergy());
				msg.Append(_USERATTRIB_ENERGY, this->GetEnergy());
			}
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}*/
}

/////////////////////////////////////////////////////////////////////////////
void CUser::ClsStatus(int nStatus, bool bSynchro)
{
	I64 i64OldEffect = GetEffect();
	switch (nStatus)
	{		
	case STATUS_ADJUST_DODGE:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_ADJUST_DODGE;
		}
		break;
	case STATUS_ADJUST_XP:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_ADJUST_XP;
		}
		break;
	case STATUS_ADJUST_DROPMONEY:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_ADJUST_DROPMONEY;
		}
		break;
	case	STATUS_NORMAL:
		{
			ASSERT(!"STATUS_NORMAL");
		}
		break;
	case	STATUS_DIE:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_DIE;
		}
		break;
	case	STATUS_TEAMLEADER:
		{
		     m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAMLEADER;
		}
		break;
	case	STATUS_CRIME:           
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_CRIME;
		}
		break;
	case	STATUS_SYNCRIME:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_SYNCRIME;
		}
		break;
	case	STATUS_POISON:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_POISON;
		}
		break;
	case	STATUS_PKVALUE:        // change huang 2004.1.11  todo
		{
			// ȡ������״̬����������������
			if (m_data.GetPk() < PKVALUE_REDNAME)
				m_data.m_Info.i64Effect	&= ~(KEEPEFFECT_RED|KEEPEFFECT_DEEPRED);
			else if (m_data.GetPk() < PKVALUE_BLACKNAME)
			{
				m_data.m_Info.i64Effect	&= ~KEEPEFFECT_DEEPRED;
				m_data.m_Info.i64Effect	|= KEEPEFFECT_RED;
			}
		}
		break;
	case	STATUS_DEFENCE1:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_DEFENCE1;
		}
		break;
	case	STATUS_DEFENCE2:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_DEFENCE2;
		}
		break;
	case	STATUS_DEFENCE3:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_DEFENCE3;
		}
		break;
	case	STATUS_FREEZE:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_FREEZE;
		}
		break;
	case	STATUS_SMOKE:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_SMOKE;
		}
		break;
	case	STATUS_DARKNESS:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_DARKNESS;
		}
		break;
	case	STATUS_PALSY:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_PALSY;
		}
		break;
	case	STATUS_ATTACK:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_ATTACK;
		}
		break;
	case	STATUS_MAGICDEFENCE:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_MAGICDEFENCE;
		}
		break;
	case	STATUS_REFLECT:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_REFLECT;
		}
		break;
	case	STATUS_REFLECTMAGIC:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_REFLECTMAGIC;
		}
		break;
	case	STATUS_MAGICDAMAGE:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_MAGICDAMAGE;
		}
		break;
	case	STATUS_ATKSPEED:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_ATKSPEED;
		}
		break;
	case	STATUS_LURKER:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_LURKER;
		}
		break;
	case	STATUS_SLOWDOWN1:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_SLOWDOWN1;
		}
		break;
	case	STATUS_SLOWDOWN2:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_SLOWDOWN2;
		}
		break;
	case	STATUS_MAXLIFE:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_MAXLIFE;
		}
		break;
	case	STATUS_MAXENERGY:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_MAXENERGY;
		}
		break;
	case	STATUS_HIDDEN:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_HIDDEN;
		}
		break;
	case	STATUS_ADD_EXP:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_ADD_EXP;
		}
		break;
	case	STATUS_ATTRACT_MONSTER:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_ATTRACT_MONSTER;
		}
		break;
	case	STATUS_XPFULL:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_XPFULL;
			ClsXpVal(SYNCHRO_FALSE);
		}
		break;
	case	STATUS_PK_PROTECT:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_PK_PROTECT;
		}
		break;
	case	STATUS_PELT:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_PELT;
		}
		break;
	case	STATUS_ADJUST_EXP:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_ADJUST_EXP;
		}
		break;
	// �����ǽ��ϵͳ��ص�״̬ ================
	case	STATUS_TEAMHEALTH:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_HEALTH;
		}
		break;
	case	STATUS_TEAMATTACK:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_ATTACK;
		}
		break;
	case	STATUS_TEAMDEFENCE:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_DEFENCE;
		}
		break;
	case	STATUS_TEAMSPEED:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_SPEED;
		}
		break;
	case	STATUS_TEAMEXP:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_EXP;
		}
		break;
	case	STATUS_TEAMSPIRIT:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_SPIRIT;
		}
		break;
	case	STATUS_TEAMCLEAN:
		{
			m_data.m_Info.i64Effect	&= ~KEEPEFFECT_TEAM_CLEAN;
		}
		break;
	// �����ǽ��ϵͳ���״̬ ===============
	case	STATUS_HEAL:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_HEAL;
		}
		break;
	case	STATUS_FAINT:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_FAINT;
		}
		break;
	case	STATUS_TRUCULENCE:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_TRUCULENCE;
		}
		break;
	case	STATUS_DAMAGE:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_DAMAGE;
		}
		break;
	case	STATUS_ATKER_DAMAGE:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_ATKER_DAMAGE;
		}
		break;
	case	STATUS_FRENZY:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_FRENZY;
		}
		break;
	case	STATUS_TRANSFER_SHIELD:
		{
			m_data.m_Info.i64Effect &= ~KEEPEFFECT_TRANSFER_SHIELD;
		}
		break;
	case	STATUS_LOCK:
	case	STATUS_SUPER_MATK:
		break;
	default:
		::LogSave("Invalid status: [%u]", nStatus);
		//		ASSERT(!"switch status");
	}

	if (nStatus == STATUS_LOCK)
	{
		CMsgAction	msg;
		if (msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionUnlockUser))
		{
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}
	/*if(bSynchro && i64OldEffect != GetEffect())
	{
		CMsgUserAttrib msg;
		if (msg.Create(GetID(), _USERATTRIB_KEEPEFFECT, GetEffect()))
		{
			// �����ٶȽ�磬�ָ�ԭ�����ƶ��ٶ�
			if (STATUS_TEAMSPEED == nStatus || STATUS_SLOWDOWN1 == nStatus || STATUS_SLOWDOWN2 == nStatus
				|| STATUS_PELT == nStatus)
			{
				msg.Append(_USERATTRIB_SPEED, AdjustSpeed(this->GetSpeed()));
			}
			else if (STATUS_MAXLIFE == nStatus)
			{
				msg.Append(_USERATTRIB_MAXLIFE, this->GetMaxLife());
				msg.Append(_USERATTRIB_LIFE, this->GetLife());
			}
			else if (STATUS_MAXENERGY == nStatus)
			{
				msg.Append(_USERATTRIB_MAXENERGY, this->GetMaxEnergy());
				msg.Append(_USERATTRIB_ENERGY, this->GetEnergy());
			}
			BroadcastRoomMsg(&msg, INCLUDE_SELF);
		}
	}*/
}

/////////////////////////////////////////////////////////////////////////////
void CUser::IncAddPoint(int nAddPoint)
{
	int nNewPoint	= nAddPoint + m_data.GetAddPoint();

	if (nNewPoint < 0)
		nNewPoint	= 0;

	m_data.SetAddPoint(nNewPoint);
}

/////////////////////////////////////////////////////////////////////////////
bool CUser::IsAlive()
{
	if ((GetStatus() & STATUS_DIE) == STATUS_DIE || this->GetLife() <= 0)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void CUser::SetForce(DWORD dwForce)
{
	m_data.SetForce(dwForce);
}

/////////////////////////////////////////////////////////////////////////////
void CUser::SetDegree(DWORD dwDegree)
{
	m_data.SetDegree(dwDegree);
}

/////////////////////////////////////////////////////////////////////////////
void CUser::SetSpeed(DWORD dwSpeed)
{
	m_data.SetSpeed(dwSpeed);
}

/////////////////////////////////////////////////////////////////////////////
/*void CUser::SetSoul(DWORD dwSoul)
{
	//m_data.SetSoul(dwSoul);
}*/

/////////////////////////////////////////////////////////////////////////////
void CUser::SetPhysique(DWORD dwPhysique)
{
	m_data.SetPhysique(dwPhysique);
}

/////////////////////////////////////////////////////////////////////////////
void CUser::SetFace(DWORD dwFace)
{
	
	//DWORD dwLookFace = m_data.GetLookFace();
	//dwLookFace = (dwLookFace-this->GetFace()*10000)+(dwFace%1000)*10000;

	m_data.SetFace(dwFace, true);
}

/////////////////////////////////////////////////////////////////////////////
void CUser::SetLook(DWORD dwLook)
{
	//DWORD dwLookFace = m_data.GetLook();
	//dwLookFace = (dwLookFace/1000)*1000 + (dwLook%1000);

	m_data.SetLook(dwLook, true);
}

/*////////////////////////////////////////////////////////////////////////////
BOOL CUser::CheckStatus(int nStatus)
{
	if (nStatus == STATUS_NORMAL || STATUS_DIE == nStatus)
	{
		if (m_infoStatus.dwStatus == nStatus)
			return true;
		else
			return false;
	}
	else
	{
		if ((m_infoStatus.dwStatus & nStatus) == nStatus)
			return true;
		else
			return false;
	}
}*/

/////////////////////////////////////////////////////////////////////////////
bool CUser::IsJumpPass(int x, int y, int nAlt)
{
	vector<POINT>	setLine;
	DDALineEx(GetPosX(), GetPosY(), x, y, setLine);

	int nSize = setLine.size();
	if(nSize <= 2)
		return true;
	ASSERT(x == setLine[nSize-1].x);
	ASSERT(y == setLine[nSize-1].y);
	float	fAlt	= (float)(GetMap()->GetFloorAlt(GetPosX(), GetPosY()) + nAlt) + 0.5;
	float	fDelta	= (float)(GetMap()->GetFloorAlt(x, y) - fAlt) / nSize;
	for(int i = 0; i < nSize; i++)
	{
		if(GetMap()->IsAltOver(setLine[i], (int)fAlt))
			return false;
//		fAlt	+= fDelta;
	}

	return true;
}
/////////////////////////////////////////////////////////////////////////////
bool CUser::IsArrowPass(int x, int y, int nAlt/*=ARROW_FLY_ALT*/)
{
	return true;		//? �ݲ���� /////////////////////////////////////////////////////////////

	vector<POINT>	setLine;
	DDALineEx(GetPosX(), GetPosY(), x, y, setLine);

	int nSize = setLine.size();
	if(nSize <= 2)
		return true;
	ASSERT(x == setLine[nSize-1].x);
	ASSERT(y == setLine[nSize-1].y);
	float	fAlt	= (float)(GetMap()->GetFloorAlt(GetPosX(), GetPosY()) + nAlt) + 0.5;
	float	fDelta	= (float)(GetMap()->GetFloorAlt(x, y) - fAlt) / nSize;
	for(int i = 0; i < nSize; i++)
	{
		if(GetMap()->IsAltOver(setLine[i], (int)fAlt))
			return false;
		fAlt	+= fDelta;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// posCenter: ����Լ�(����posSource!!!)��posSource������Ϊ������
// posSource���������ĵ�
// nWidth: 1 - 359
/*
bool CUser::IsInFan(POINT pos, POINT posSource, int nRange, int nWidth, POINT posCenter)
{
	CHECKF(nWidth > 0 && nWidth < 360);

	if(posCenter.x == GetPosX() && posCenter.y == GetPosY())
		return false;
	if(pos.x == posSource.x && pos.y == posSource.y)
		return false;

	if(GetDistance(pos.x, pos.y) > nRange)
		return false;

	float PI = static_cast<float>(3.1415926535);
	float fRadianDelta	= (PI * nWidth / 180) / 2;
	float fCenterLine	= GetRadian(GetPosX(), GetPosY(), posCenter.x, posCenter.y);
	float fTargetLine	= GetRadian(posSource.x, posSource.y, pos.x, pos.y);
	float fDelta	= fabs(fCenterLine - fTargetLine);
	if(fDelta <= fRadianDelta || fDelta >= 2*PI - fRadianDelta)
		return true;

	return false;
}
*/

/////////////////////////////////////////////////////////////////////////////
bool	CUser::EquipMagicItem(CItem* pItem, int nPosition)
{
	/*int idxMagic = pItem->GetInt(ITEMDATA_MAGIC1);
	if(idxMagic != MAGIC_NONE && QueryMagic())
		ASSERT(QueryMagic()->EquipWeaponMagic(POSITION2MAGIC_ID(nPosition), MagicType(idxMagic), WEAPONMAGIC_LEVEL));*/

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool	CUser::UnequipMagicItem(int nPosition)
{
	OBJID idMagic = POSITION2MAGIC_ID(nPosition);

	if (QueryMagic())
		QueryMagic()->UnequipWeaponMagic(idMagic);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void	CUser::SynchroSupermanOrder(int nOrder)
{
	m_nSupermanOrder	= nOrder;

	// synchro
	SetAttrib(_USERATTRIB_SUPERMAP_ORDER, nOrder, SYNCHRO_TRUE);
}

/////////////////////////////////////////////////////////////////////////////
void	CUser::CalcSupermanKills()
{
	if(IsGM() || m_nCurrSupermanKills < MIN_SUPERMAP_KILLS || m_nCurrSupermanKills <= m_nTopSupermanKills)
	{
		m_nCurrSupermanKills	= 0;
		return ;
	}

	m_nTopSupermanKills		= m_nCurrSupermanKills;
	m_nCurrSupermanKills	= 0;

	char	buf[sizeof(long)*2];
	VARIANT_SET0* pInfo = (VARIANT_SET0*)buf;
	pInfo->IntParam(0)	= GetID();
	pInfo->IntParam(1)	= m_nTopSupermanKills;
	MapGroup(PID)->QueryMsgPort()->Send(MSGPORT_WORLD, KERNEL_SUPERMANLIST, STRUCT_TYPE(buf), buf);
}

/////////////////////////////////////////////////////////////////////////////
void	CUser::QuerySupermanSecs()
{
	char	buf[sizeof(long)*2];
	VARIANT_SET0* pInfo = (VARIANT_SET0*)buf;
	pInfo->IntParam(0)	= GetID();
	pInfo->IntParam(1)	= 0;			// 0: for query
	MapGroup(PID)->QueryMsgPort()->Send(MSGPORT_WORLD, KERNEL_SUPERMANLIST, STRUCT_TYPE(buf), buf);
}

/////////////////////////////////////////////////////////////////////////////
void	CUser::QuerySupermanList(int nIndex, OBJID idAction, int nNumber)
{
	char	buf[sizeof(long)*4];
	VARIANT_SET0* pInfo = (VARIANT_SET0*)buf;
	pInfo->IntParam(0)	= GetID();
	pInfo->IntParam(1)	= nIndex;
	pInfo->IntParam(2)	= idAction;
	pInfo->IntParam(3)	= nNumber;
	MapGroup(PID)->QueryMsgPort()->Send(MSGPORT_WORLD, KERNEL_QUERYSUPERMANLIST, STRUCT_TYPE(buf), buf);
}

/////////////////////////////////////////////////////////////////////////////
CUser*	CUser::FindAroundUser(OBJID id)
{
	IRole* pRole = FindAroundRole(id);
	CUser* pUser = NULL;
	if(pRole)
		pRole->QueryObj(OBJ_USER, IPP_OF(pUser));

	return pUser;
}

/////////////////////////////////////////////////////////////////////////////
DWORD	CUser::GetInterAtkRate()			
{
	if(QueryTransformation())
		return QueryTransformation()->GetInterAtkRate();

	int nRate = GetIntervalAtkRate();
	int nRateR = 0, nRateL = 0;
	//if (m_pWeaponR && m_pWeaponR->IsWeapon())		// not arrow
	//	nRateR = m_pWeaponR->GetInt(ITEMDATA_ATKSPEED);
	//if (m_pWeaponL && m_pWeaponL->IsWeapon())		// not shield
	//	nRateL = m_pWeaponL->GetInt(ITEMDATA_ATKSPEED);

	if(nRateR && nRateL)
		nRate = (nRateR + nRateL) / 2;
	else if(nRateR)
		nRate = nRateR;
	else if(nRateL)
		nRate = nRateL;

	IStatus* pStatus = QueryStatus(STATUS_ATKSPEED);
	if (pStatus)
	{
		nRate	= ::CutTrail(0, AdjustData(nRate, pStatus->GetPower()));
		if (this->IsPM())
			this->SendSysMsg(_TXTATR_NORMAL, "atack speed+: %d", pStatus->GetPower());
	}

//	pStatus = QueryStatus(STATUS_SUPERMAN);
//	if (pStatus)
//	{
//		nRate	= nRate/2;
//		if (this->IsPM())
//			this->SendSysMsg(_TXTATR_NORMAL, "superman +: %d", pStatus->GetPower());
//	}
	
//	pStatus = QueryStatus(STATUS_TORNADO);
//	if (pStatus)
//	{
//		nRate	= ::CutTrail(0, AdjustData(nRate, pStatus->GetPower()));
//		if (this->IsPM())
//			this->SendSysMsg(_TXTATR_NORMAL, "tornado +: %d", pStatus->GetPower());
//	}

	return nRate;
}

/////////////////////////////////////////////////////////////////////////////
DWORD	CUser::GetIntervalAtkRate()			
{
	if(QueryTransformation())
		return QueryTransformation()->GetIntervalAtkRate();

	return USER_ATTACK_SPEED;
}

/////////////////////////////////////////////////////////////////////////////
int	CUser::GetAttackRange(int nTargetSizeAdd)			
{
	if(QueryTransformation())
		return QueryTransformation()->GetAttackRange(nTargetSizeAdd);

	int nRange = 1;
	int nRangeR = 0, nRangeL = 0;
	//if (m_pWeaponR && m_pWeaponR->IsWeapon())		// not arrow
	//	nRangeR = m_pWeaponR->GetInt(ITEMDATA_ATKRANGE);
	//if (m_pWeaponL && m_pWeaponL->IsWeapon())		// not shield
	//	nRangeL = m_pWeaponL->GetInt(ITEMDATA_ATKRANGE);

	if(nRangeR && nRangeL)
		nRange = (nRangeR + nRangeL) / 2;
	else if(nRangeR)
		nRange = nRangeR;
	else if(nRangeL)
		nRange = nRangeL;

	nRange += (GetSizeAdd()+nTargetSizeAdd+1)/2;

//	IStatus* pStatus = QueryStatus(STATUS_ATKRANGE);
//	if (pStatus)
//		nRange	= ::CutTrail(1, AdjustData(nRange, pStatus->GetPower()));


	//if (QueryMagic())
	//	nRange += QueryMagic()->GetExtendAtkRange(m_pWeaponR, m_pWeaponL);
	return nRange;
}

/////////////////////////////////////////////////////////////////////////////
int	CUser::GetSizeAdd()			
{
	if(QueryTransformation())
		return QueryTransformation()->GetSizeAdd();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// adjust
/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustHitRate(int nHitRate)
{
//	IStatus* pStatus = QueryStatus(STATUS_HITRATE);
//	if(pStatus)
//	{
//		nHitRate = ::CutTrail(0, AdjustData(nHitRate, pStatus->GetPower()));
//#ifdef _DEBUG
//		this->SendSysMsg(_TXTATR_NORMAL, "hit rate adjust+: %d", pStatus->GetPower());
//#endif
//	}

	return nHitRate;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustAttack(int nAtk)
{
	int nAddAtk = 0;
	IStatus* pStatus = QueryStatus(STATUS_DEF2ATK);
	if (pStatus)
	{
		nAddAtk += ::CutTrail(0, MulDiv(this->GetDef(), pStatus->GetPower(), 100));
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "attack adjust STATUS_DEF2ATK+: %d%% of def", pStatus->GetPower());
#endif
	}

	pStatus = QueryStatus(STATUS_ATTACK);
	if(pStatus)
	{
		nAddAtk += ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower())) - nAtk;
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "atack adjust STATUS_ATTACK+: %d", pStatus->GetPower());
#endif
	}
	
	pStatus = QueryStatus(STATUS_SUPER_ATK);
	if(pStatus)
	{
		nAddAtk += ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower())) - nAtk;
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "atack adjust STATUS_SUPER_ATK+: %d", pStatus->GetPower());
#endif
	}

/*
	pStatus	= QueryStatus(STATUS_TEAMATTACK);
	if (pStatus)
	{
		nAddAtk += ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower())) - nAtk;
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "atack adjust STATUS_TEAMATTACK+: %d", pStatus->GetPower());
#endif
	}
*/

	return nAtk + nAddAtk;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustDefence(int nDef)
{
	int nAddDef = 0;
	
	IStatus* pStatus = QueryStatus(STATUS_DEF2ATK);
	if (pStatus)
	{
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "def adjust STATUS_DEF2ATK-: %d%%", pStatus->GetPower());
#endif
		nAddDef += ::CutTrail(0, MulDiv(nDef, 100-__max(100, pStatus->GetPower()), 100)) - nDef;
	}

	pStatus = QueryStatus(STATUS_DEFENCE3);
	if (!pStatus)
		pStatus = QueryStatus(STATUS_DEFENCE2);
	if (!pStatus)
		pStatus = QueryStatus(STATUS_DEFENCE1);
	if(pStatus)
	{
		nAddDef += ::CutTrail(0, AdjustData(nDef, pStatus->GetPower())) - nDef;
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "def adjust STATUS_DEFENCE+: %d", pStatus->GetPower());
#endif
	}

	pStatus = QueryStatus(STATUS_SUPER_DEF);
	if(pStatus)
	{
		nAddDef += ::CutTrail(0, AdjustData(nDef, pStatus->GetPower())) - nDef;
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "def adjust STATUS_SUPER_DEF+: %d", pStatus->GetPower());
#endif
	}

	pStatus = QueryStatus(STATUS_DEF2ATK);
	if (pStatus)
	{
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "def adjust STATUS_DEF2ATK-: %d%%", pStatus->GetPower());
#endif
		return (::CutTrail(0, MulDiv(nDef+nAddDef, 100-__max(100, pStatus->GetPower()), 100)));
	}

	return nDef + nAddDef;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustMagicAtk(int nAtk)
{
	IStatus* pStatus = QueryStatus(STATUS_SUPER_MATK);
	if(pStatus)
		return ::CutTrail(0, AdjustData(nAtk, pStatus->GetPower()));

	return nAtk;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustMagicDef(int nDef)
{
	int nAddDef = 0;
	IStatus* pStatus = QueryStatus(STATUS_SUPER_MDEF);
	if(pStatus)
		nAddDef += ::CutTrail(0, AdjustData(nDef, pStatus->GetPower()));

	pStatus = QueryStatus(STATUS_MAGICDEFENCE);
	if (pStatus)
		nAddDef += ::CutTrail(0, AdjustData(nDef, pStatus->GetPower()));

	return nDef + nAddDef;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustBowDefence(int nDef)
{
//	IStatus* pStatus = QueryStatus(STATUS_BOWDEFENCE);
//	if(pStatus)
//	{
//		nDef = ::CutTrail(0, AdjustData(nDef, pStatus->GetPower()));
//#ifdef _DEBUG
//		this->SendSysMsg(_TXTATR_NORMAL, "def adjust STATUS_BOWDEFENCE+: %d", pStatus->GetPower());
//#endif
//	}
	return nDef;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustWeaponDamage(int nDamage)
{
//	IStatus* pStatus = QueryStatus(STATUS_WEAPONDAMAGE);
//	if(pStatus)
//	{
//		nDamage = ::CutTrail(0, AdjustData(nDamage, pStatus->GetPower()));
//#ifdef _DEBUG
//		this->SendSysMsg(_TXTATR_NORMAL, "adjust STATUS_WEAPONDAMAGE+: %d", pStatus->GetPower());
//#endif
//	}

	nDamage=MulDiv(nDamage, GetDefence2(), DEFAULT_DEFENCE2);
	return nDamage;
}

/////////////////////////////////////////////////////////////////////////////
int CUser::AdjustMagicDamage(int nDamage)
{
	IStatus* pStatus = QueryStatus(STATUS_MAGICDAMAGE);
	if(pStatus)
	{
		nDamage = ::CutTrail(0, AdjustData(nDamage, pStatus->GetPower()));
#ifdef _DEBUG
		this->SendSysMsg(_TXTATR_NORMAL, "adjust STATUS_MAGICDAMAGE+: %d", pStatus->GetPower());
#endif
	}

	int nMagicDefence2 = (GetMetempsychosis() && this->GetProfessionLevel() >= 3) ? 7000 : DEFAULT_DEFENCE2;		// 3: 70��
	nDamage=MulDiv(nDamage, nMagicDefence2, DEFAULT_DEFENCE2);
	return nDamage;
}

//////////////////////////////////////////////////////////////////////
DWORD CUser::AdjustSpeed(int nSpeed)
{
	if (!m_setStatus)
		return nSpeed;

	int nAddSpeed = 0;
	IStatus* pStatus = QueryStatus(STATUS_TEAMSPEED);
	if (pStatus)
		nAddSpeed += nSpeed * pStatus->GetPower()/100;

	pStatus = QueryStatus(STATUS_PELT);
	if (pStatus)
		nAddSpeed += ::CutTrail(0, AdjustData(nSpeed, pStatus->GetPower())) - nSpeed;
	

	pStatus = QueryStatus(STATUS_SLOWDOWN1);
	if (pStatus)
		nAddSpeed += ::CutTrail(0, AdjustData(nSpeed, pStatus->GetPower())) - nSpeed;

	pStatus = QueryStatus(STATUS_SLOWDOWN2);
	if (pStatus && (this->GetLife()*2 < this->GetMaxLife()))
	{
		nAddSpeed += ::CutTrail(0, AdjustData(nSpeed, pStatus->GetPower())) - nSpeed;
	}

	nSpeed = __min(255, __max(1, nSpeed + nAddSpeed));
	return nSpeed;
}

//////////////////////////////////////////////////////////////////////
void CUser::SendBonusInfo(void)
{
	// read record from db
	char szSQL[256] = "";
	sprintf(szSQL, "SELECT * FROM %s WHERE id_account=%u", _TBL_BONUS, this->GetAccountID());

	IRecordset* pRes = Database()->CreateNewRecordset(szSQL);
	if (!pRes)
		return;

	int nBonus = pRes->RecordCount();
	if (nBonus > 0)
	{
		this->SendSysMsg(_TXTATR_GM, STR_BONUS, nBonus);
	}

	pRes->Release();
}

//////////////////////////////////////////////////////////////////////
bool CUser::DoBonus(void)
{
	// condition check
	for (int i=ITEMPOSITION_BACKPACK; i<ITEMPOSITION_PACK_END; i++)
	{
		if (this->IsItemFull(0, 0, i))
		{
			this->SendSysMsg(STR_BAG_FULL);
			return false;
		}
	}
/*
	if (this->IsItemFull(0))
	{
		this->SendSysMsg(STR_BAG_FULL);
		return false;
	}
*/

	// read record from db
	enum{
		BONUSDATA_ACTION = 0,
		BONUSDATA_ID,
		BONUSDATA_ACCOUNT,
	};

	char szSQL[256] = "";
	sprintf(szSQL, "SELECT * FROM %s WHERE id_account=%u LIMIT 1", _TBL_BONUS, this->GetAccountID());

	CAutoPtr<IRecordset> pRes = Database()->CreateNewRecordset(szSQL);
	if (!pRes || pRes->RecordCount() <= 0)
		return false;

	OBJID idRecord	=pRes->GetInt(BONUSDATA_ID);
	OBJID idAction	=pRes->GetInt(BONUSDATA_ACTION);

	// del recordset obj
//	pRes->Release();

	DEBUG_TRY
	{
		if(!GameAction()->ProcessAction(idAction, this))		//? �˴��������������������������һ�����롣
		{
			this->SendSysMsg(STR_BAG_FULL);		// ��ACTION�м��������
			return false;
		}

		// record info
		::MyLogSave("gmlog/bonus", "###Bonus: AccountID(%u), Player(%u) take bonus(%u).", this->GetAccountID(), this->GetID(), idAction);

		// delete
		char szSQL[256] = "";
		sprintf(szSQL, "DELETE from %s WHERE id=%u LIMIT 1", _TBL_BONUS, idRecord);

		ASSERT(g_db.ExecuteSQL(szSQL));

		return true;
	}
	DEBUG_CATCH("DoBonus(void)")

	return false;
}

//////////////////////////////////////////////////////////////////////
void CUser::RemoteCall(REMOTE_CALL0* pInfo)
{
	switch(pInfo->ucFuncType)
	{
	case	REMOTE_CALL_TEAM_HUNTKILL:
		{
			this->TeamHuntKill((OBJID)pInfo->IntParam[0], pInfo->IntParam[1], (const char*)pInfo->IntParam[2]);
		}
		break;
	case	REMOTE_CALL_DROP_LEADER:
		{
			CHECK(GetSynRank() == RANK_LEADER);

			// update new leader
			QuerySynAttr()->SetIdRank(pInfo->IntParam[0], pInfo->IntParam[1]);
		}
		break;
	case	REMOTE_CALL_LEAVE_SYN:
		{
			if(GetSynID() == pInfo->IntParam[0])
			{
				QuerySynAttr()->LeaveSyn(true, DELRECORD_FALSE, SYNCHRO_TRUE);		// false: need not delete recorder again
				SendSysMsg(STR_KICKOUT_ME_s, (char*)&pInfo->IntParam[1]);				
			}
		}
		break;
	case	REMOTE_CALL_TEAM_CLOSE_MONEY:
		{
			CTeam* pTeam = GetTeam();
			if(pTeam)
			{
				if(pInfo->IntParam[0])
					pTeam->SetCloseMoney(true);
				else
					pTeam->SetCloseMoney(false);
				this->SendSysMsg(_TXTATR_TEAM, STR_TEAM_MONEY_s, pInfo->IntParam[0] ? STR_CLOSE : STR_OPEN);
			}
		}
		break;
	case	REMOTE_CALL_TEAM_CLOSE_ITEM:
		{
			CTeam* pTeam = GetTeam();
			if(pTeam)
			{
				if(pInfo->IntParam[0])
					pTeam->SetCloseItem(true);
				else
					pTeam->SetCloseItem(false);
				this->SendSysMsg(_TXTATR_TEAM, STR_TEAM_ITEM_s, pInfo->IntParam[0] ? STR_CLOSE : STR_OPEN);
			}
		}
		break;
	/*case	REMOTE_CALL_TEAM_CLOSE_GEM_ACCESS:
		{
			CTeam* pTeam = GetTeam();
			if(pTeam)
			{
				if(pInfo->IntParam[0])
					pTeam->SetCloseGemAccess(true);
				else
					pTeam->SetCloseGemAccess(false);
				this->SendSysMsg(_TXTATR_TEAM, STR_TEAM_GEM_s, pInfo->IntParam[0] ? STR_CLOSE : STR_OPEN);
			}
		}
		break;*/
	}
}

//////////////////////////////////////////////////////////////////////
bool CUser::Transform(DWORD dwType, int nKeepSecs, bool bSynchro/*=true*/)
{
	bool bBack = false;

	if(m_pTransformation)
	{
		m_pTransformation->Release();
		m_pTransformation = NULL;
		bBack = true;
	}

	CNpcType* pType = NpcType()->GetObj(dwType);
	CHECKF(pType);

	CTransformation* pTransform = CTransformation::CreateNew();		// VVVVVVVVVVVVVVVVVVVVVVVVvv
	IF_OK(pTransform)
	{
		IF_OK(pTransform->Create(this, pType))
		{
			m_pTransformation = pTransform;
			m_tTransformation.Startup(nKeepSecs);
			if(bSynchro)
				SynchroTransform();

			this->StopMine();
			return true;
		}
		else
			pTransform->Release();		// AAAAAAAAAAAAAAAAAAAAAAAA
	}

	if(bBack)
		SynchroTransform();

	return false;
}

//////////////////////////////////////////////////////////////////////
void CUser::AbortTransform()
				{ SAFE_RELEASE(m_pTransformation); SynchroTransform(); }

//////////////////////////////////////////////////////////////////////
bool CUser::SynchroTransform()
{
	CMsgUserAttrib	msg;
	IF_OK( msg.Create(GetID(), _USERATTRIB_LOOKFACE, GetLookFace())
			&& msg.Append(_USERATTRIB_MAXLIFE, GetMaxLife())
			&& msg.Append(_USERATTRIB_LIFE, GetLife())
			&& msg.Append(_USERATTRIB_SIZEADD, GetSizeAdd()) )
		BroadcastRoomMsg(&msg, INCLUDE_SELF);

	this->BroadcastTeamLife(true);		// true: with max life

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::CallPet(OBJID idMonsterType, int x, int y, int nKeepSecs/*=0*/)
{
	KillCallPet();

	CAiNpc* pMonster = NpcManager()->CreateCallPet(this, idMonsterType, x, y);
	CHECKF(pMonster);
	m_pCallPet = pMonster->QueryLink();

	if(nKeepSecs)
		m_tCallPet.Startup(nKeepSecs);
	else
		m_tCallPet.Clear();

	return true;
}

//////////////////////////////////////////////////////////////////////
void CUser::KillCallPet(bool bNow/*=false*/)
{
	if(!m_pCallPet)
		return ;

	if(!m_pCallPet->IsDeleted())
		m_pCallPet->DelMonster(bNow);
}

//////////////////////////////////////////////////////////////////////
OBJID CUser::GetCallPetID()			{ if(m_pCallPet) return QueryCallPet()->GetID(); return ID_NONE; }

//////////////////////////////////////////////////////////////////////
bool CUser::IsSimpleMagicAtk	()
{ return QueryTransformation() && QueryTransformation()->GetMagicType() != ID_NONE; }

//////////////////////////////////////////////////////////////////////
int CUser::GetSimpleMagicHitRate()
{ IF_OK(QueryTransformation()) return QueryTransformation()->GetMagicHitRate(); else return 100; }

//////////////////////////////////////////////////////////////////////
bool CUser::SetWeather(int nType, int nIntensity, int nDir, DWORD nColor, DWORD nKeepSecs, DWORD nSpeedSecs)
{
	if(m_idWeather != ID_NONE)
	{
		CWeatherRegion* pRegion = GetMap()->QueryWeatherRegion(m_idWeather);
		IF_OK(pRegion)
			return pRegion->QueryWeather()->SetNewWeather(nType, nIntensity, nDir, nColor, nKeepSecs, nSpeedSecs);
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
void CUser::SetLight(int dwRGB, int nSecs/*=0*/)
{
	if(nSecs == 0)		// keep light
		GetMap()->SetLight(dwRGB);

	CMsgAction	msg;
	IF_OK(msg.Create(GetID(), GetPosX(), GetPosY(), nSecs, actionMapARGB, dwRGB))
		UserManager()->BroadcastMapMsg(GetMapID(), &msg, NULL);
}

//////////////////////////////////////////////////////////////////////
void CUser::SendLight()
{
	//int	nKeepSecs = 0;		// keep light

	//CMsgAction	msg;
	//IF_OK(msg.Create(GetID(), GetPosX(), GetPosY(), nKeepSecs, actionMapARGB, GetMap()->GetLight()))
	//	SendMsg(&msg);
}

//////////////////////////////////////////////////////////////////////
void CUser::AwardSynWarScore(CNpc* pNpc, int nScore)
{
	CHECK(pNpc);
	CHECK(nScore > 0);

	if(GetSynID() == ID_NONE || GetSynID() == pNpc->GetSynID())
		return ;

	int nAddProffer = MulDiv(nScore, SYNWAR_PROFFER_PERCENT, 100);
	if(nAddProffer)
		QuerySynAttr()->AddProffer(nAddProffer);

	int nAddMoney	= MulDiv(nScore, SYNWAR_MONEY_PERCENT, 100);
	if(nAddMoney > 0)
	{
		CSyndicate* pSyn = SynManager()->QuerySyndicate(pNpc->GetSynID());
		if(pSyn)
		{
			nAddMoney	= ::CutOverflow(nAddMoney, pSyn->GetInt(SYNDATA_MONEY));
			pSyn->QueryModify()->AddData(SYNDATA_MONEY, -1*nAddMoney, true);
			this->GainMoney(nAddMoney, SYNCHRO_TRUE);
			//
		}
	}

	CSyndicate* pSyn = SynManager()->QuerySyndicate(GetSynID());
	if(pSyn)
	{
		pSyn = pSyn->GetMasterSyn();
		pSyn->AddSynWarScore(pNpc->GetID(), nScore);
		
	}
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsHostileSynMember	(CUser* pTarget)
{
	IF_NOT (pTarget)
		return false;

	OBJID idSynTarget	= pTarget->GetSynID();
	OBJID idSyn			= this->GetSynID();
	if (ID_NONE != idSynTarget && ID_NONE != idSyn)
	{
		CSyndicate* pSyn = SynManager()->QuerySyndicate(idSyn);
		if (pSyn && pSyn->IsHostile(idSynTarget))
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
CSyndicate* CUser::GetSyndicate(void)
{
	if(this->GetSynID() != ID_NONE)
		return SynManager()->QuerySyndicate(this->GetSynID());

	return NULL;
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsMemberOfSyn(OBJID idSyn)
{
	if (idSyn == ID_NONE)
		return false;
	CSyndicate* pSyn = this->GetSyndicate();
	while (pSyn)
	{
		if (pSyn->GetID() == idSyn)
			return true;

		OBJID idFealty	= pSyn->GetInt(SYNDATA_FEALTY);
		if (idFealty == ID_NONE)
			return false;

		pSyn = SynManager()->QuerySyndicate(idFealty);
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
OBJID CUser::GetMateHomeID()
{
	LPCTSTR szMateName = GetMate();
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT home_id FROM %s WHERE name='%s' LIMIT 1", _TBL_USER, szMateName);
	CAutoPtr<IRecordset> pRes = _Database(PID)->CreateNewRecordset(szSQL);
	if(pRes)
		return pRes->GetInt(0);

	return ID_NONE;
}

//////////////////////////////////////////////////////////////////////
void CUser::SetRecordPos(OBJID idMap, DWORD dwX, DWORD dwY, BOOL bUpdate/* = false*/)
{
	PROCESS_ID idProcess = MapManager()->GetProcessID(idMap);
	CHECK(idProcess != PROCESS_NONE);
	if(idProcess == m_idProcess)
	{
		CGameMap* pMap = MapManager()->GetGameMap(idMap);
		IF_NOT (pMap)
			return;

		IF_NOT(pMap->IsStandEnable(dwX, dwY))
			return;
	}

	m_data.SetRecordPos(idMap, dwX, dwY, bUpdate);
}

//////////////////////////////////////////////////////////////////////
bool CUser::KickBack()
{
	if(!this->IsSynchro())
		return false;

	CMsgAction	msg;
	IF_OK(msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionKickBack, GetPosX(), GetPosY()))
		SendMsg(&msg);

	this->SetSynchro(false);
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::Synchro()
{
	CMsgAction	msg;
	IF_OK(msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionSynchro, GetPosX(), GetPosY()))
		SendMsg(&msg);

	this->SetSynchro(false);
	return true;
}

//////////////////////////////////////////////////////////////////////
OBJID CUser::GetMateID()
{
	if(!IsMarried())
		return ID_NONE;

	CUser* pMate = UserManager()->GetUser(this->GetMate());
	if(pMate)
		return pMate->GetID();

	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT id FROM %s where name='%s' LIMIT 1", _TBL_USER, GetMate());
	CAutoPtr<IRecordset> pRes = _Database(PID)->CreateNewRecordset(szSQL);
	if(pRes)
		return pRes->GetInt(0);

	return ID_NONE;
}

//////////////////////////////////////////////////////////////////////
int CUser::AdjustExp(IRole* pTarget, int nRawExp, bool bNewbieBonusMsg)
{
	CHECKF(pTarget);

	int nExp = nRawExp;

	// kill bonus
//	if (this && !pTarget->IsAlive())
//	{
//		CNpc* pNpc = NULL;
//		pTarget->QueryObj(OBJ_NPC, IPP_OF(pNpc));
//
//		if (pTarget->IsMonster() || pNpc && pNpc->IsGoal())
//		{
//			// team bonus
//			CTeam* pTeam = this->GetTeam();
//			if (pTeam && pTeam->IsTeamWithNewbie(this->GetID(), pTarget))
//			{
//				nExp *= 2;
//				
//				if (bNewbieBonusMsg)
//					this->SendSysMsg(STR_KILLING_EXPEX, nExp);
//			}
//		}
//	}

	// adjust
	nExp = 0; //CBattleSystem::AdjustExp(nExp, this->GetLev(), pTarget->GetLev());
	CNpc* pNpc = NULL;
	pTarget->QueryObj(OBJ_NPC, IPP_OF(pNpc));
	if (pTarget->IsMonster() || (pNpc && pNpc->IsGoal()))
	{
		if (this->GetTutor())
		{
			CTeam* pTeam	= this->GetTeam();
			if (pTeam && pTeam->IsTeamWithTutor(this->GetID(), pTarget))
				nExp += nExp*WITHTUTORBONUS_PERCENT/100;	// �͵�ʦһ����������20%����
			else
				nExp += nExp*HAVETUTORBONUS_PERCENT/100;	// û�͵�ʦһ����������10%����
		}
	}
	
	// �������������ӻ�õľ���
	IStatus* pStatus = this->QueryStatus(STATUS_TEAMEXP);
	if (pStatus)
		nExp = ::CutTrail(0, MulDiv(nExp, 100+pStatus->GetPower(), 100));
	
	// ���� -- ����ս�������״̬
	pStatus = this->QueryStatus(STATUS_ADD_EXP);
	if (pStatus)
		nExp = ::CutTrail(0, MulDiv(nExp, 100+pStatus->GetPower(), 100));

	pStatus = this->QueryStatus(STATUS_ADJUST_EXP);
	if (pStatus)
		nExp = ::CutTrail(0, AdjustData(nExp, pStatus->GetPower()));

	return nExp;
}

//////////////////////////////////////////////////////////////////////
bool CUser::CheckCrime(IRole* pRole)
{
	CHECKF(pRole);
	if(!pRole->IsEvil())
	{
		if (!GetMap() || !GetMap()->IsDeadIsland())
			SetCrimeStatus();
		return true;
	}

	/*OBJID idSyn = GetMap()->GetSynID();
	if(idSyn != ID_NONE && pRole->GetSynID() == idSyn)
	{
		CNpc* pNpc;
		if(pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc)) && pNpc->IsGoal())		// ����
			return false;

		if (!GetMap() || !GetMap()->IsDeadIsland())
			SetCrimeStatus(STATUS_SYNCRIME);
		return true;
	}*/

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsImmunity(IRole* pRole)
{
	CHECKF(pRole);

	const bool	ATK_IT = false;
	const bool	IMMUNITY = true;
	OBJID idRole = pRole->GetID();
	if(IsSceneID(idRole))		// is npc
	{
		CNpc* pNpc;
		pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc));
		if(pNpc && !pNpc->IsBeAtkable())
			return true;
		return false;
	}
	else if(IsNpcID(idRole))	// is monster
	{
		CAiNpc* pMonster = NULL;
		CHECKF(pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)));
		if(pMonster->GetMasterID() == GetID())		// call pet of mine
			return true;
		switch(this->GetPkMode())
		{
		case PKMODE_FREE:
			return ATK_IT;
			break;
		case PKMODE_TEAM:
			if (pMonster->IsCallPet())
			{
				CTeam* pTeam = GetTeam();
				if(pTeam && pTeam->IsTeamMember(pMonster->GetMasterID()))
					return IMMUNITY;

				CUser* pUser = this->QueryOwnerUser();
				if(this->IsMate(pUser))
					return IMMUNITY;
			}
			else
				return ATK_IT;
			break;
		case PKMODE_SYNDICATE:          //add huang 2004.1.15  todo.
			if(pMonster->IsCallPet())
			{
				CUser* pOwnerUser = pRole->QueryOwnerUser();
				if (this->GetSynID() == pOwnerUser->GetSynID() || this->IsMate(pOwnerUser))
					return IMMUNITY;
				else
				{				
					CSyndicate* pSyn = SynManager()->QuerySyndicate(this->GetSynID());
					if (pSyn)
					{
						if ( pSyn->IsFriendly(pOwnerUser->GetSynID())
							    || pSyn->IsNearSyn(pOwnerUser->GetSynID()))

							return IMMUNITY;
					}
				}
			}
			else if(pMonster->IsSynPet())
			{
				CSyndicate* pSyn = SynManager()->QuerySyndicate(this->GetSynID());
				if (pSyn)
				{
					if ( pSyn->IsFriendly(pMonster->GetSynID())
							|| pSyn->IsNearSyn(pMonster->GetSynID()))
						
						return IMMUNITY;
				}	
			}
			
			return ATK_IT;
			break;

		case PKMODE_ARRESTMENT:
			if(pMonster->IsMonster() || pMonster->IsSynMonster() || pMonster->IsEvil())
				return ATK_IT;
			else
				return IMMUNITY;
			break;
			
		case PKMODE_SAFE:
			if(pMonster->IsMonster() || pMonster->IsSynMonster())
				return ATK_IT;
			else
				return IMMUNITY;
			break;
		}
		return false;
	}
	else	// user
	{
		switch(this->GetPkMode())
		{
		case	PKMODE_FREE:
			return false;
			break;
			
		case	PKMODE_TEAM:    //change huang 2004.1.11 (�����ʿ��ģʽ) 
			{
				bool bImmunity = false;
				
				CTeam* pTeam = this->GetTeam();
				if(pTeam && pTeam->IsTeamMember(idRole))
					bImmunity = true;
				
				if (this->GetFriend(pRole->GetID()))
					bImmunity = true;
				
				CUser* pUser = NULL;
				if (pRole->QueryObj(OBJ_USER, IPP_OF(pUser)))
				{
					if(this->IsMate(pUser))
						bImmunity = true;
				}
				
				return bImmunity;
			}
			break;
		case	PKMODE_SYNDICATE:     //add huang 2004.1.15
			{
				bool bImmunity = false;
				CUser* pUser = NULL;
				if (pRole->QueryObj(OBJ_USER, IPP_OF(pUser)) && this->GetSynID() != ID_NONE)
				{
					if (this->GetSynID() == pUser->GetSynID())
						bImmunity = true;
					else
					{
						CSyndicate* pSyn = SynManager()->QuerySyndicate(this->GetSynID());
						if (pSyn)
						{
							if (pSyn->IsNearSyn(pUser->GetSynID()) 
								|| pSyn->IsFriendly(pUser->GetSynID()))
								
								bImmunity = true;
						}
					}
					if (this->IsMate(pUser))
						bImmunity = true;
				}
				return bImmunity;
			}
			break;

		case	PKMODE_ARRESTMENT:
			{
				if(pRole->IsEvil())
					return false;
				return true;
			}
			break;

		case	PKMODE_SAFE:
			return true;
			break;

		default:
			ASSERT(!"switch pk mode");
			break;
		}

		return false;
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::SetCrimeStatus(int nStatus/*=STATUS_CRIME*/, int nTime/*=CRIME_KEEP_SECS*/)
{
	ASSERT(nStatus == STATUS_CRIME || nStatus == STATUS_SYNCRIME);

	int nPower = 1;		// 0: decrement secs
	CRole::AttachStatus(QueryRole(), nStatus, nPower, nTime);
	if(QueryCallPet())
		CRole::AttachStatus(QueryCallPet()->QueryRole(), nStatus, nPower, nTime);
}
//////////////////////////////////////////////////////////////////////
void CUser::SetSelfDefStatus(int nTime)      //add huang 2004.1.14
{
//	int nPower = 1;
//	CRole::AttachStatus(QueryRole(),STATUS_SELFDEFENCE,nPower,nTime);
}
//////////////////////////////////////////////////////////////////////
bool CUser::IsBeAtkable			()
{
	return !(QueryStatus(STATUS_PK_PROTECT)	//m_tLock.IsActive() && !m_tLock.IsTimeOut() 
		|| m_pCallPet&&m_pCallPet->IsInsteadMagic() 
		|| QueryStatus(STATUS_HIDDEN)
		|| QueryStatus(STATUS_LOCK));
}

//////////////////////////////////////////////////////////////////////
// rebirth
//////////////////////////////////////////////////////////////////////
bool CUser::CheckRebirth(int nProf, CRebirthData* pData)
{
	if(this->GetMetempsychosis())
		return false;
	if(GetLev() < pData->GetInt(REBIRTHDATA_NEED_LEVEL))
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::Rebirth(int nProf, int nLook)
{
	for(int i = 0; i < RebirthSet()->GetAmount(); i++)
	{
		CRebirthData* pData = RebirthSet()->GetObjByIndex(i);
		if(pData && GetProfession() == pData->GetInt(REBIRTHDATA_NEED_PROF) && nProf == pData->GetInt(REBIRTHDATA_NEW_PROF))
		{
			if(CheckRebirth(nProf, pData))
			{
				int nOldProf	= GetProfession();
				int nOldLevel	= GetLev();
				ResetEquipLevel(pData->GetInt(REBIRTHDATA_NEW_LEVEL));
				ResetUserAttrib(nOldProf, nOldLevel, pData->GetInt(REBIRTHDATA_NEW_PROF), pData->GetInt(REBIRTHDATA_NEW_LEVEL), nLook);
				return true;
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
void CUser::ResetEquipLevel(int nNewLevel)
{
	for(int i = ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItem* pEquip = this->GetEquipItemByPos(i);
		if(pEquip)
		{
			ASSERT(DownEquipmentLevel(i, nNewLevel));
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::ResetUserAttrib(int nOldProf, int nOldLevel, int nNewProf, int nNewLevel, int nNewLook)
{
	// default attribute
	int nProfession = nNewProf;
	if (nProfession == 0)
		nProfession = 20;

	int nForce = 6, nPhysique = 3, nDegree = 1, nSoul = 0;
	if (nProfession == 100)
	{
		nForce	= 0;
		nDegree = 2;
		nPhysique = 3;
		nSoul	= 5;
	}
	else if (nProfession == 40)
	{
		nForce	= 2;
		nDegree = 7;
		nPhysique = 1;
		nSoul	= 0;
	}

	int nMaxLife = nPhysique * 3 + 30;
	int nMaxMana = nSoul*20;
	int nDefaultMoney = 100;
	int nDefaultHair = 310+::RandGet(7)*100;
	int nAddPoint	= GetRebirthAddPoint(nOldProf, nOldLevel);

	// modify
	this->SetAutoAllot(true);
	this->SetMetempsychosis(1);
	this->SetLook(nNewLook);
	SetAttrib(_USERATTRIB_LOOKFACE, GetLookFace(), SYNCHRO_BROADCAST);		// no database
	SetAttrib(_USERATTRIB_PORFESSION, nNewProf, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_LEV, nNewLevel, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_EXP, 0, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_FORCE, nForce, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_DEGREE, nDegree, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_PHYSIQUE, nPhysique, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_SOUL, nSoul, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_LIFE, nMaxLife, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_MANA, nMaxMana, SYNCHRO_TRUE);
	SetAttrib(_USERATTRIB_ADDPOINT, nAddPoint, SYNCHRO_TRUE);

	SaveInfo();
}

//////////////////////////////////////////////////////////////////////
int CUser::GetRebirthAddPoint(int nOldProf, int nOldLevel)
{
	if(nOldProf == HIGHEST_WATER_WIZARD_PROF)
	{
		return 30 + (1 + (nOldLevel-110)/2 ) * ((nOldLevel-110)/2) / 2;
	}
	else
	{
		return 30 + (1 + (nOldLevel-120) ) * (nOldLevel-120) / 2;
	}
}

//////////////////////////////////////////////////////////////////////
void CUser::SendSystemBBS(LPCTSTR szText)
{
	OBJID idUser = this->GetID();

	mapgroup_kernel::CMsgTalk	msg;
	IF_OK(msg.Create(this->GetName(), ALLUSERS_NAME, szText, NULL, 0xffffff, _TXTATR_MSG_SYSTEM))
		MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(&msg, idUser);
}

//////////////////////////////////////////////////////////////////////
void CUser::ProcessMsgAction(int nAction, int nData, OBJID id)
{
	switch(nAction)
	{
	case actionQueryMedal:
		{
			CMsgDataArray	msg;
			IF_OK(msg.Create(_DATAARRAY_ACTION_MEDAL, strlen(this->GetMedal()), this->GetMedal()))
				SendMsg(&msg);
		}
		break;
	case actionDelMedal:
		{
			char* ptr = strchr(this->GetMedal(), nData);
			if(ptr)
			{
				memcpy(ptr, ptr+1, (ptr - this->GetMedal()));
			}
		}
		break;
/*
	case actionSelectMedal:
		{
			if(strchr(this->GetMedal(), nData))
			{
				this->SetAttrib(_USERATTRIB_MEDALSELECTED, nData, SYNCHRO_BROADCAST);
			}
		}
		break;
*/
	case actionQueryHonorTitle:
		{
			CMsgDataArray	msg;
			IF_OK(msg.Create(_DATAARRAY_ACTION_HONORTITLE, strlen(this->GetTitle()), this->GetTitle()))
				SendMsg(&msg);
		}
		break;
	case actionDelHonorTitle:
		{
			char* ptr = strchr(this->GetTitle(), nData);
			if(ptr)
			{
				memcpy(ptr, ptr+1, (ptr - this->GetTitle()));
			}
		}
		break;
	case actionSelectHonorTitle:
		{
/*
			if(strchr(this->GetTitle(), nData))
			{
				this->SetAttrib(_USERATTRIB_HONORTITLESELECTED, nData, SYNCHRO_BROADCAST);
			}
*/
		}
		break;
	default:
		ASSERT(!"CUser::ProcessMsgAction");
	}
}

//////////////////////////////////////////////////////////////////////
// lock key
//////////////////////////////////////////////////////////////////////
bool CUser::SetLock(DWORD dwKey)
{
	// check key
	if(m_data.GetRealLockKey())
		return false;
	if(dwKey <= 99999)		// || dwKey >= 1000000000
		return false;
	if(dwKey == 123456 || dwKey == 654321)
		return false;
	if(dwKey == 111111 || dwKey == 222222 || dwKey == 333333 || dwKey == 666666 || dwKey == 888888 || dwKey == 999999)
		return false;

	m_data.SetLockKey(dwKey);
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::OpenLock(DWORD dwKey)
{
	if(!m_data.GetRealLockKey() || m_data.GetRealLockKey() != dwKey)
		return false;

	m_data.SetCurrLockKey(0, UPDATE_FALSE);
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::ClearLock(DWORD dwKey)
{
	if(m_data.GetRealLockKey() && m_data.GetRealLockKey() != dwKey)
		return false;

	m_data.SetLockKey(0, UPDATE_FALSE);
	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::CheckLock(bool bSynchro/*=true*/)
{
	if(m_data.GetCurrLockKey())
	{
		if(bSynchro)
			SendSysMsg(STR_LOCKKEY_DENY);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// week pk game badge
//////////////////////////////////////////////////////////////////////
bool CUser::AddBadge()
{
	CItem* pBadge = NULL;
	// TODO: ��CUserPackage��������������
	pBadge	= QueryPackage()->GetWPGBadge();

	/*for(int i = m_setItem.size()-1; i >= 0; i--)
	{
		CItem* pItem = m_setItem[i];
		if(pItem && CItem::IsWPGBadge(pItem->GetInt(ITEMDATA_TYPE)))
		{
			pBadge	= pItem;
			break;
		}
	}*/

	/*if(pBadge && pBadge->GetInt(ITEMDATA_AMOUNT) == 1)
	{
		pBadge->SetInt(ITEMDATA_AMOUNT, 2);

		CMsgItem	msg;
		IF_OK(msg.Create(pBadge->GetID(), ITEMACT_SYNCHRO_AMOUNT, pBadge->GetInt(ITEMDATA_AMOUNT)))
			SendMsg(&msg);

		return true;
	}*/

	return false;
}

//////////////////////////////////////////////////////////////////////
bool CUser::DelAllBadge()
{
	CItem* pBadge = NULL;

	while (pBadge = QueryPackage()->GetWPGBadge())		// ��whileѭ����̫�ã��Ժ���øĵ� -- zlong 2004.11.22
	{
		EraseItem(pBadge->GetID(), SYNCHRO_TRUE);
	}
	/*for(int i = m_setItem.size()-1; i >= 0; i--)
	{
		CItem* pItem = m_setItem[i];
		if(pItem && CItem::IsWPGBadge(pItem->GetInt(ITEMDATA_TYPE)))
			EraseItem(pItem->GetID(), SYNCHRO_TRUE);
	}*/

	return true;
}

//////////////////////////////////////////////////////////////////////
bool CUser::CheckBadge(int nItemType/*=0*/)
{
	return QueryPackage()->CheckWPGBadge(nItemType);
/*
	CItem* pBadge = NULL;
	for(int i = m_setItem.size()-1; i >= 0; i--)
	{
		CItem* pItem = m_setItem[i];
		if(pItem && CItem::IsWPGBadge(pItem->GetInt(ITEMDATA_TYPE)))
		{
			if(nItemType && pItem->GetInt(ITEMDATA_TYPE) == nItemType && pItem->GetInt(ITEMDATA_AMOUNT) == 1)
			{
				nItemType = 0;		// no ignore again
				continue;
			}

			return false;
		}
	}

	return true;
*/
}

//////////////////////////////////////////////////////////////////////
bool CUser::CreateAllPet()
{
	if (m_data.m_Info.petCount == 0) return true;

	for (int i = 0; i < m_data.m_Info.petCount; i++) {
		if (m_data.m_Info.petId[i] > 0) {
			CPetPtr pPet = CPet::CreateNew();
			if (pPet) {
				if (pPet->Create(m_idProcess, m_data.m_Info.petId[i])) {
					pPet->SetOwner(this);
					setPet.push_back(pPet);
					if (m_data.m_Info.petId[i] == m_data.m_Info.marchingPetId) marchingPet = pPet;
				}
				else
					pPet->ReleaseByOwner();
			}
		}
	}
	return true;
}

void CUser::SendAllPet() {
	for (auto pet : setPet) {
		CMsgPetInfo	msg;
		if (msg.Create(pet, PETINFO_ACTIONADD))
			SendMsg(&msg);
	}
}

void CUser::SendActivePet() {
	if (!marchingPet) return;

	CMsgPetAction msg;
	if (msg.Create(marchingPet->GetID(), 0, PETACTION_ACTIVE))
		SendMsg(&msg);
}

//////////////////////////////////////////////////////////////////////
bool CUser::IsItemFull(int nWeight, OBJID idItemType, DWORD dwData)
{
	// �����Ǹ���

	return m_pPackage->IsPackFull(idItemType, nWeight, dwData);
}


//////////////////////////////////////////////////////////////////////
// tutor 

bool CUser::AddTutor(OBJID idTutor, LPCTSTR szName)
{
	CHECKF(szName);
	m_pTutor	= CTutor::CreateNew();
	if (m_pTutor)
	{
		if (m_pTutor->CreateRecord(this->GetID(), idTutor, this->GetName(), szName, Database()))
		{
			// ���ﻹ��Ҫ֪ͨ�Է�
			CUser* pTarget = UserManager()->GetUser(idTutor);
			if (pTarget)
			{
				/*CMsgSchoolMember msg;
				if (msg.Create(MESSAGEBOARD_ADDMEMBER, NULL, 0))
				{
					msg.Append(RELATION_TEACHER, MEMBERSTATUS_ONLINE, pTarget);
					SendMsg(&msg);
				}
				pTarget->AwardTutorExp(-1 * ADDSTUDENT_TUTOREXP);
				pTarget->AddStudentRef(m_pTutor->GetInfo());*/
			}
			else
			{
				// TODO: ͨ���������������MapGroup��Ѱ�Ҳ�֪ͨ
				/*CMsgSchoolMember msg;
				if (msg.Create(MESSAGEBOARD_ADDMEMBER, NULL, 0))
				{
					if (msg.Append(RELATION_TEACHER, MEMBERSTATUS_OFFLINE, idTutor, szName))
					{
						SendMsg(&msg);
						MapGroup(PID)->QueryIntraMsg()->TransmitMsg(&msg, this->GetSocketID(), this->GetID());
					}
				}*/
			}
			return true;
		}
		else
			SAFE_DELETE (m_pTutor);
	}
	return false;
}

bool CUser::DelTutor()
{
	if (!m_pTutor)
		return false;

	//this->SendSysMsg(STR_LEAVE_TEACHER, m_pTutor->GetTutorName());

	OBJID idTutor = m_pTutor->GetTutorID();
	m_pTutor->DeleteRecord(Database());
	SAFE_DELETE (m_pTutor);

	/*if (this->GetLev() >= LEAVETUTOR_LEVEL)
	{
		// ����10���������ʦ����ǰ3����������
		int nExpPunish	= 0;
		for (int i=1; i<=3; i++)
		{
			CLevupexpData* pLevupexp	= LevupexpSet()->GetObj(EXP_TYPE_USER * _EXP_TYPE + this->GetLev()-i);
			if (pLevupexp)
				nExpPunish	+= pLevupexp->GetInt(LEVUPEXPDATA_EXP);
		}
		this->AwardBattleExp(-1*nExpPunish);
	}

	CMsgSchoolMember	msg;
	if (msg.Create(MESSAGEBOARD_DELMEMBER, NULL, 0))
	{
		if (msg.Append(RELATION_TEACHER, MEMBERSTATUS_OFFLINE, idTutor))
			SendMsg(&msg);
	}*/

	// ����ֻ��ɾ����ʦ�������ݿ��¼����Ӧ��֪ͨʦ��ɾ���ڴ����ݡ������ʦ�����ߵĻ�
	CUser* pUser = UserManager()->GetUser(idTutor);
	if (pUser)
	{
		pUser->DelStudentRef(GetID());
	}
	else
	{
		// ֪ͨ����MapGroupѰ��ʦ����ɾ��ͽ��
	}

	return true;
}

bool CUser::DelTutorRef()
{
	/*if (!m_pTutor)
		return false;

	SendSysMsg(STR_LEAVE_TEACHER4, m_pTutor->GetTutorName());

	OBJID idTutor = m_pTutor->GetTutorID();
	SAFE_DELETE (m_pTutor);

	CMsgSchoolMember	msg;
	if (msg.Create(MESSAGEBOARD_DELMEMBER, NULL, 0))
	{
		if (msg.Append(RELATION_TEACHER, MEMBERSTATUS_OFFLINE, idTutor))
			SendMsg(&msg);
	}*/

	return true;
}

CTutor* CUser::GetStudent(OBJID idStudent)
{
	TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		if (pTutor->GetUserID() == idStudent)
			return pTutor;
	}
	return NULL;
}

bool CUser::AddStudentRef(const TutorInfoStruct* pInfo)
{
	CHECKF (pInfo);

	TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		if (pTutor->GetUserID() == pInfo->idUser && pTutor->GetTutorID() == this->GetID())
			return false;
	}

	/*CTutor* pTutor = CTutor::CreateNewTutor(pInfo);
	if (pTutor)
	{
		m_setStudent.push_back(pTutor);
		CMsgSchoolMember	msg;
		if (msg.Create(MESSAGEBOARD_ADDMEMBER, NULL, 0))
		{
			CUser* pUser = UserManager()->GetUser(pTutor->GetUserID());
			if (pUser)
			{
				if (msg.Append(RELATION_STUDENT, MEMBERSTATUS_ONLINE, pUser))
					SendMsg(&msg);
			}
			else
			{
				if (msg.Append(RELATION_STUDENT, MEMBERSTATUS_OFFLINE, pTutor->GetUserID(), pTutor->GetUserName()))
				{
					SendMsg(&msg);
					MapGroup(PID)->QueryIntraMsg()->TransmitMsg(&msg, this->GetSocketID(), this->GetID());
				}
			}
		}
		return true;
	}*/
	return false;
}
DWORD   CUser::GetAllTutorLevel()
{//Ϊ�������ֹ��������򹫸����������ѧԱ�ĵȼ��͡�LW
/*	DWORD dLevel = 0;
	TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		OBJID idStudent = pTutor->GetUserID(); 
		dLevel += UserManager()->GetUser(idStudent)->GetLev();
	}*/
	return 0; 
	
}
bool CUser::DelStudent(OBJID idStudent)
{
	/*TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		if (pTutor->GetUserID() == idStudent && pTutor->GetTutorID() == GetID())
		{
			this->SendSysMsg(STR_LEAVE_TEACHER, pTutor->GetUserName());

			OBJID idStudent = pTutor->GetUserID();
			pTutor->DeleteRecord(Database());
			SAFE_DELETE (pTutor);
			m_setStudent.erase(it);

			// ����ѧԱҪ�۵�ʦ������Ϊ�ͷ�
			m_data.SetTutorExp(GetTutorExp() - DELSTUDENT_TUTOREXP);

			CMsgSchoolMember	msg;
			if (msg.Create(MESSAGEBOARD_DELMEMBER, NULL, 0))
			{
				if (msg.Append(RELATION_STUDENT, MEMBERSTATUS_OFFLINE, idStudent))
					SendMsg(&msg);
			}

			CUser* pUser = UserManager()->GetUser(idStudent);
			if (pUser)
				pUser->DelTutorRef();
			else
			{
				// ֪ͨ����MapGroupѰ��Student��ɾ����ʦ
			}

			return true;
		}
	}*/
	return false;
}

bool CUser::DelStudentRef(OBJID idStudent)
{
	/*TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		if (pTutor->GetUserID() == idStudent && pTutor->GetTutorID() == GetID())
		{
			this->SendSysMsg(STR_LEAVE_TEACHER3, pTutor->GetUserName());
			SAFE_DELETE (pTutor);
			m_setStudent.erase(it);

			CMsgSchoolMember	msg;
			if (msg.Create(MESSAGEBOARD_DELMEMBER, NULL, 0))
			{
				if (msg.Append(RELATION_STUDENT, MEMBERSTATUS_OFFLINE, idStudent))
					SendMsg(&msg);
			}

			return true;
		}
	}*/
	return false;
}

bool CUser::CreateAllTutor(IDatabase* pDb)
{
	// create tutor
	SQLBUF		szSQL;
	sprintf(szSQL, "SELECT * FROM %s WHERE user_id=%u LIMIT 1", _TBL_TUTOR, GetID());
	IRecordset*	pRes = pDb->CreateNewRecordset(szSQL);
	if(pRes)
	{
		m_pTutor = CTutor::CreateNew();
		if(m_pTutor)
		{
			if(!m_pTutor->Create(pRes))
				SAFE_DELETE (m_pTutor);
		}
		SAFE_RELEASE (pRes);
	}

	// create student
	sprintf(szSQL, "SELECT * FROM %s WHERE tutor_id=%u LIMIT %d", _TBL_TUTOR, GetID(), _MAX_TUTORSIZE);
	pRes = pDb->CreateNewRecordset(szSQL);
	if(pRes)
	{
		for(int i = 0; i < pRes->RecordCount(); i++)
		{
			CTutor*	pTutor = CTutor::CreateNew();
			if(pTutor)
			{
				if(pTutor->Create(pRes))
					m_setStudent.push_back(pTutor);
				else
					SAFE_DELETE (pTutor);
			}
			pRes->MoveNext();
		}
		SAFE_RELEASE (pRes);
	}
	return true;

}

void CUser::DeleteAllTutor()
{
	SAFE_DELETE (m_pTutor);

	TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		SAFE_DELETE (pTutor);
	}
	m_setStudent.clear();
}

void CUser::SendTutorInfo()
{
	if (!m_pTutor && GetStudentAmount() == 0)
		return;

	/*CMsgSchoolMember	msg;
	msg.Create(MESSAGEBOARD_ADDMEMBER, NULL, 0);
	if (m_pTutor)
	{
		// ����ͼ���Ҳ����Ķ���Ϊ���ߴ�����ͷ�����������鸺�𷵻�������Ϣ
		CUser* pUser = UserManager()->GetUser(m_pTutor->GetTutorID());
		if (pUser)
			msg.Append(RELATION_TEACHER, MEMBERSTATUS_ONLINE, pUser);
		else
			msg.Append(RELATION_TEACHER, MEMBERSTATUS_OFFLINE, m_pTutor->GetTutorID(), m_pTutor->GetTutorName());
	}
	*/
	/*TUTOR_SET::iterator it = m_setStudent.begin();
	for (; it != m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		if (pTutor)
		{
			CUser* pUser = UserManager()->GetUser(pTutor->GetUserID());
			if (pUser)
				msg.Append(RELATION_STUDENT, MEMBERSTATUS_ONLINE, pUser);
			else
				msg.Append(RELATION_STUDENT, MEMBERSTATUS_OFFLINE, pTutor->GetUserID(), pTutor->GetUserName());
		}
	}
	this->SendMsg(&msg);
	MapGroup(PID)->QueryIntraMsg()->TransmitMsg(&msg, this->GetSocketID(), this->GetID());*/		// ֪ͨ������ͼ�飬�´�����ʦͽ������Ϣ
}

void CUser::AwardTutorExp(int nTutorExp)
{
	int nExp = GetTutorExp() + nTutorExp;
	
	m_data.SetTutorExp(nExp);
}

bool CUser::TakeExpFromStudent(int nExpTake)
{
	if (GetLev() < _MIN_TUTOR_LEVEL)
		return false;

	/*CTutorexpData*	pExpData;
	pExpData = CTutorexpData::CreateNew();
	if (!pExpData)
		return false;

	if (pExpData->Create(GetID(), Database()))
	{
		// ���ͽ�ܹ��׵ľ���
		int nExp = pExpData->GetInt(TUTOREXPDATA_EXP);
		if (nExpTake > nExp)
			return false;

		// ���ݵ�ʦ�ȼ��Լ���ȡ�õĹ��׾���������ĵĵ�ʦ����
		int nGetExpPerTutorexp = GETEXP_PER_TUTOREXP0;
		if (this->GetTutorLevel() == 1)
			nGetExpPerTutorexp = GETEXP_PER_TUTOREXP1;
		else if (this->GetTutorLevel() == 2)
			nGetExpPerTutorexp = GETEXP_PER_TUTOREXP2;
		int nCostTutorExp = nExpTake/nGetExpPerTutorexp + ((nExpTake%nGetExpPerTutorexp > 0)?1:0);
		if (this->GetTutorExp() < nCostTutorExp)
		{
			this->SendSysMsg(STR_NOT_ENOUGH_TUTOREXP);
			return false;
		}
		this->AwardTutorExp(-1*nCostTutorExp);		// �ȿ۳���ʦ����
		pExpData->SetInt(TUTOREXPDATA_EXP, nExp - nExpTake);
		this->AwardBattleExp(nExpTake);			// �õ����׾���

		// ��ʦ���ݾ���
		int nTutorExp = pExpData->GetInt(TUTOREXPDATA_TUTOREXP);
		pExpData->SetInt(TUTOREXPDATA_TUTOREXP, 0);
		pExpData->Update();
		if (GetTutor() && nTutorExp>0)
		{
			SQLBUF szSQL;
			sprintf(szSQL, "UPDATE %s SET exp=exp+%u WHERE tutor_id=%u AND tutor_lev>%u LIMIT 1",
				_TBL_TUTOREXP, nTutorExp, m_pTutor->GetTutorID(), GetLev());
			Database()->ExecuteSQL(szSQL);
		}
	}
	SAFE_RELEASE (pExpData);*/
	return true;
}

void CUser::NotifyTutorStatus(int nStatus)
{
	/*if (!m_pTutor && m_setStudent.size() <= 0)
		return;

	// ֪ͨ�Լ����е�ʦͽ�Լ�Ŀǰ״̬
	CMsgSchoolMember	msg;
	if (m_pTutor)
	{
		msg.Create(MESSAGEBOARD_UPDATEMEMBER, NULL, 0);
		msg.Append(RELATION_STUDENT, nStatus, this);
		MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(&msg, m_pTutor->GetTutorID());
	}


	char szMsg[_MAX_WORDSSIZE];
	if (nStatus == MEMBERSTATUS_ONLINE)
		sprintf(szMsg, STR_TUTOR_LOGIN, this->GetName());
	else
		sprintf(szMsg, STR_TUTOR_LOGOUT, this->GetName());
	
	msg.Create(MESSAGEBOARD_UPDATEMEMBER, NULL, 0);
	msg.Append(RELATION_TEACHER, nStatus, this);
	TUTOR_SET::iterator it=m_setStudent.begin();
	for (; it!=m_setStudent.end(); it++)
	{
		CTutor* pTutor = *it;
		if (pTutor)
		{
			CUser* pUser = UserManager()->GetUser(pTutor->GetUserID());
			if (pUser)
				pUser->SendMsg(&msg);
			else
				MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(&msg, pTutor->GetUserID());

			CMsgTalk	msgNotify;
			if (msgNotify.Create(SYSTEM_NAME, pTutor->GetUserName(), szMsg, NULL, 0xff0000, _TXTATR_SYSTEM))
			{
				if (pUser)
					pUser->SendMsg(&msgNotify);
				else
					MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(&msgNotify, pTutor->GetUserID());
			}
		}
	}*/
}

//---jinggy---2004-11-12---��������Ƕ��Ĺ����౦ʯ�����Է�
bool CUser::UseSkillAtk(OBJID idDes)
{ /*
	
	for(int i=ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr pEquipItem = GetEquipItemByPos(i);

		if(!pEquipItem)
			continue;
		
		//�õ���ʯ�����ж��ǲ�����Ч����
		DWORD dwGemType = pEquipItem->GetInt(ITEMDATA_GEMTYPE);		
		CItemTypeData * pItemTypeData = ItemType()->QueryItemType(dwGemType);
		if(!pItemTypeData)
			return false ;
		
		//�����ͱ�ʯ��ʹ�õĴ���
//		DWORD dwGemAvailableTime = pEquipItem->GetInt(ITEMDATA_AVAILABLETIME);

		if(dwGemAvailableTime<=0)
			return false ;

		if (RandGet(100)<=1) {

			//�øñ�ʯ����
			UserItemToByType(idDes,dwGemType);

			//װ�������ı�ʯ����������һ��
//			pEquipItem->SetInt(ITEMDATA_AVAILABLETIME, -- dwGemAvailableTime);
			pEquipItem->SaveInfo();

			CMsgItemInfo msg;					
			IF_OK(msg.Create(pEquipItem,ITEMINFO_UPDATE)) //֪ͨ�ͻ��˸��� װ��
				SendMsg(&msg);		
			
			return true ;
		}
	}
*/
	return false ;
}
//���´������ϵ�װ���ľ���ֵ
/*
  ֻ�д������� 10 ���Ӻ�Ÿ�װ�� ��һ��ľ���ֵ
*/
//---jinggy---2004-11-17--
void CUser::UpdateEquipmentExp()
{
	if(!m_bIsEnableWarGhostExp)
		return;

	if(m_tEquipWarGhostExp.ToNextTime())
	{
		for(int i=ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)

		{
			if(m_arrTimeOutForEquipExp[i-ITEMPOSITION_EQUIPBEGIN].IsActive()
				&& m_arrTimeOutForEquipExp[i-ITEMPOSITION_EQUIPBEGIN].ToNextTime())
			{
				CItemPtr pItem = GetEquipItemByPos(i);
				if(pItem)
				{
					//pItem->WarGhostLevelUpgrade(this);

#ifdef _DEBUG				
				//	char szInfo[255];
					//sprintf(szInfo,"��Ʒ %s ��ս�꾭��ֵ %d",pItem->GetStr(ITEMDATA_NAME),pItem->GetInt(ITEMDATA_WARGHOSTEXP));
					//this->SendSysMsg(_TXTATR_NORMAL,szInfo);
#endif
				}	
			}
		}
	}	
}

//ָֹͣ���豸�ļ�����
void CUser::UpdateEquipmentExp_Stop(DWORD dwPos)
{
	DEBUG_TRY

	IF_NOT(dwPos>=ITEMPOSITION_EQUIPBEGIN && dwPos<ITEMPOSITION_EQUIPEND)
		return;

	m_arrTimeOutForEquipExp[dwPos-ITEMPOSITION_EQUIPBEGIN].Clear();
	m_arrEquipIncExp[dwPos-ITEMPOSITION_EQUIPBEGIN] = 0;

	DEBUG_CATCH("void CUser::UpdateEquipmentExp_Stop(DWORD dwPos)")
}
//����ָ���豸�ļ�����
void CUser::UpdateEquipmentExp_Startup(DWORD dwPos,int nSecs)
{
	DEBUG_TRY

	IF_NOT(dwPos>=ITEMPOSITION_EQUIPBEGIN && dwPos<ITEMPOSITION_EQUIPEND)
		return;

	m_arrTimeOutForEquipExp[dwPos-ITEMPOSITION_EQUIPBEGIN].Startup(nSecs);

	DEBUG_CATCH("void CUser::UpdateEquipmentExp_Startup(DWORD dwPos)")
}
//��ʼ�������豸�ļ�����
void CUser::UpdateEquipmentExp_Init()
{
	DEBUG_TRY

	if(DateStamp()!= this->GetLastLogin())
		m_bIsEnableWarGhostExp = true;

	//---��ʼ��������
	for(int i=ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; ++i)
	{
		m_arrTimeOutForEquipExp[i-ITEMPOSITION_EQUIPBEGIN].Clear();		
		m_arrEquipIncExp[i-ITEMPOSITION_EQUIPBEGIN] = 0;
	}

	if(DateStamp()!=this->GetLastLogin())
	{
		time_t	tCurr = time(NULL);

		tm	tmComp;
		memset(&tmComp, 0, sizeof(tm));
		tmComp.tm_year	= DateStamp()/10000 - 1900;
		tmComp.tm_mon	= (DateStamp()/100)%100 - 1;
		tmComp.tm_mday	= DateStamp()%100;

		time_t	tCur = mktime(&tmComp);
		
		memset(&tmComp, 0, sizeof(tm));
		tmComp.tm_year	= GetLastLogin()/10000 - 1900;
		tmComp.tm_mon	= (GetLastLogin()/100)%100 - 1;
		tmComp.tm_mday	= GetLastLogin()%100;

		time_t	tLast = mktime(&tmComp);

		time_t tResult = tCur - tLast;
		int nDays = tResult/86400 - 1;
	}

	DEBUG_CATCH("void CUser::UpdateEquipmentExp_Init()S")
}

//�Ƿ��ǰ��ɰ���
bool CUser::IsSynLeader()
{
	return GetSynRank() == RANK_LEADER;

}

void CUser::AddMoney(DWORD dwMoney)
{
	AddAttrib(_USERATTRIB_MONEY,dwMoney,true);
}
//�õ�����½ʱ��
DWORD CUser::GetLastLogin()
{
	return this->m_data.GetLastLogin();
}
//�Ƿ���Ƕ��װ���ı�ʯ������
bool CUser::IsEmbedGemType(int nGemType)
{
	for(int i=ITEMPOSITION_EQUIPBEGIN; i < ITEMPOSITION_EQUIPEND; i++)
	{
		CItemPtr pItem = GetEquipItemByPos(i);
		if(pItem)
		{
			//if(pItem->GetInt(ITEMDATA_GEMTYPE)==nGemType)
			//	return true;
		}
	}
	return false;
}

bool CUser::FlyToMainMap()
{
	if (QueryMagic())
	{
		if (QueryMagic()->IsInLaunch())	// ħ��ʩչ������
			return false;
		QueryMagic()->AbortMagic();
	}

	OBJID idMap = this->GetMapID();
	idMap = (idMap/1000)*1000; //����ͼID

	CGameMap * pMap=MapManager()->QueryMap(idMap);
	
	if(pMap)
	{
		OBJID idRebornMap ;
		POINT pt;
		pMap->GetRebornMap(&idRebornMap,&pt);

		ProcessOnMove(MOVEMODE_CHGMAP);

		if(this->FlyMap(idRebornMap,pt.x,pt.y) == FLYMAP_NORMAL)
		{
			ProcessAfterMove();
			return true;
		}
		else
			return false;
	}
	else
	{
		SendSysMsg(STR_ACTION_USER_FLYTOMAINMAP_ERROR);
		return false;
	}
	
}
//�õ������õİ��ɻ���
int CUser::GetAvailableSynFund()
{
	CSyndicate * pSyn = this->GetSyndicate();
	if (pSyn)
	{
		return MulDiv(pSyn->GetMoney(),1,2);
	}
	return 0;
}

bool CUser::ApplyAttackSyn(CNpc * pNpc)
{
	if(!IsSynLeader())
		return false;
	if (!pNpc->IsSynWarLetter())
	{
		return false;
	}	
	
	{		
		CGameMap* pSynMap = MapManager()->GetGameMap(pNpc->GetMapID());
		if(!pSynMap->IsSynMap())
			return false;
		//�жϾ��ŵȼ�
		int nRank = GetSynRank();
		if (nRank==SYNRANK_ONE || nRank==SYNRANK_TWO)
		{
			return false;
		}
		//����Ƿ��Ѿ���������ս��
		if(pNpc->GetData(SYNWARLETTER_ISATTACK)>0)
		{
			SendSysMsg(STR_SYN_APPLYATTACKSYN_HASBEENAPPLIED);
			return false;
		}

		if(pNpc->GetData(SYNWARLETTER_OCCUPYTIME)==0)	//û�б�ռ��
		{
			//��¼ռ���ʱ��---begin
			pNpc->GetMap()->SetSynOccupyTime();
			//��¼ռ���ʱ��---end
			CNpc* pSynFlagNpc = pSynMap->GetNpcSynFlag();

			IF_NOT(pSynFlagNpc)
				return false;
								
			pSynFlagNpc->SetSynOwnerID(GetSyndicate()->GetID(), false);		// true: with link map
			pSynFlagNpc->GetMap()->SetSynID(GetSyndicate()->GetID(), true);		// with all map npc
			
//			pSynFlagNpc->SendSelfToBlock();
			
			MSGBUF	szMsg;
			sprintf(szMsg, STR_GOT_WIN_s, GetSyndicate()->GetStr(SYNDATA_NAME));				
			mapgroup_kernel::CMsgTalk msg;
			IF_OK (msg.Create(SYSTEM_NAME, ALLUSERS_NAME, szMsg, NULL, _COLOR_WHITE, _TXTATR_GM))
				UserManager()->BroadcastMsg(&msg);
			
			// owner flag
			CGameMap* pMap = pNpc->GetMap();
			if(pMap->GetID() == WHITE_SYN_MAP_ID)
			{
				CMsgSyndicate	msg;
				IF_OK(msg.Create(SET_WHITE_SYN, pMap->GetOwnerID()))
					UserManager()->BroadcastMsg(&msg);
			}
			else if(pMap->GetID() == BLACK_SYN_MAP_ID)
			{
				CMsgSyndicate	msg;
				IF_OK(msg.Create(SET_BLACK_SYN, pMap->GetOwnerID()))
					UserManager()->BroadcastMsg(&msg);
			}
			return false;
		}

		
		//����˵�ͼ�ļ�ֵ
		int nSynMapValue = pSynMap->GetSynMapValue();

		CSyndicate * pOwnerSyn = nullptr;// SynManager()->QuerySyndicate(pSynMap->GetSynID());
		
		//�ж��������Ƿ����Ҫ��
		CSyndicate * pSyn = GetSyndicate();
		if(pSyn->GetMoney() < nSynMapValue)//�ʽ𲻹�
		{
			SendSysMsg(STR_SYN_APPLYATTACKSYN_FAIL);
			return false;
		}
		//д��ս�����Ϣ
		pNpc->SetData(SYNWARLETTER_ISATTACK,1,true);
		pNpc->SetData(SYNWARLETTER_ATTACK_SYNID,pSyn->GetID(),true);
		pNpc->SetData(SYNWARLETTER_DEPOSIT,nSynMapValue,true);
		//�۳�����Ѻ��
		pSyn->QueryModify()->AddData(SYNDATA_MONEY,-nSynMapValue);

		//����ս��ʱ��
		CNpc * pNpcSynFlag=pSynMap->GetNpcSynFlag();
		char szAnnounce[255],szAnnounce2[255];
		if(pNpcSynFlag)
		{
			time_t	tCur;
			tCur = time(NULL);
			tm * pTm = localtime(&tCur);
			
			tm	tmS;	
			memset(&tmS, 0, sizeof(tm));
			
			tmS =*pTm;
			tmS.tm_mday	+= 3;			
			tmS.tm_hour = 20;
			tmS.tm_min = 0;			
			tmS.tm_sec = 0;
			time_t	tS	= mktime(&tmS);
			sprintf(szAnnounce, STR_SYNWAR_ANNOUNCE, tmS.tm_year+1900, tmS.tm_mon+1, tmS.tm_mday,pOwnerSyn->GetStr(SYNDATA_NAME));
			sprintf(szAnnounce2, STR_SYNWAR_ANNOUNCE2, tmS.tm_year+1900, tmS.tm_mon+1, tmS.tm_mday,pSyn->GetStr(SYNDATA_NAME));
			
			tmS.tm_hour = 23;
			time_t	tE	= mktime(&tmS);
			
			pNpcSynFlag->SetData(SYNFLAGNPC_FIGHTBEGIN,(int)tS,true);
			pNpcSynFlag->SetData(SYNFLAGNPC_FIGHTEND,(int)tE,true);
			
		}
		
		GetSyndicate()->QueryModify()->SetTenet(szAnnounce);
		GetSyndicate()->BroadcastSubSynMsg(GetSocketID(), ID_NONE, szAnnounce, NULL, NULL, 0xFFFFFF, _TXTATR_SYNANNOUNCE);

		pOwnerSyn->QueryModify()->SetTenet(szAnnounce2);
		pOwnerSyn->BroadcastSubSynMsg(GetSocketID(), ID_NONE, szAnnounce2, NULL, NULL, 0xFFFFFF, _TXTATR_SYNANNOUNCE);		
	}
	//	SendSysMsg(_TXTATR_MSG_SYN,STR_SYN_APPLYATTACKSYN_SUCCESS);
	return true;	
}

//��WorldKernel�������������Ϣ
//void CUser::NotifyChatRoomOffline()
//{
//	CMsgChatRoom	msg;
//	if(msg.Create(ACTION_OFFLINE))
//	{
//		MapGroup(PID)->QueryIntraMsg()->TransmitWorldMsg(this->GetSocketID(),&msg);
//	}
//
//}

void CUser::SetSynDressArmorType(int nArmorType)
{
	if(nArmorType<=0)
		return ;
	m_nSynDressArmorType = nArmorType;
}


bool CUser::FlyToRandomPos()
{
	if (QueryMagic())
	{
		if (QueryMagic()->IsInLaunch())	// ħ��ʩչ������
			return false;
		QueryMagic()->AbortMagic();
	}
	int nPosX = 0;
	int nPosY = 0;

	if (GetMap()->GetRandomPos(nPosX,nPosY))
	{
		ActiveTransPos(nPosX, nPosY);
		return true;
	}
	return false;
}

CTaskDetail* CUser::GetTaskDetail()
{
	return m_pTaskDetail;
}
