// UserData.h: interface for the CUserData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERDATA_H__6C3EB549_7325_4A50_82DF_FD07A49E1300__INCLUDED_)
#define AFX_USERDATA_H__6C3EB549_7325_4A50_82DF_FD07A49E1300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include "define.h"
#include "GameObj.h"
#include "windows.h"
#include "GameData.h"

const int		MEDAL_BUFSIZE		= 64+1;
const int		TITLE_BUFSIZE		= 64+1;

//////////////////////////////////////////////////////////////////////
enum USERDATA{
	USERDATA_NAME=1,
};

char	szUserTable[];
const int MAX_PETS = 5;
const int MAX_USERSKILLS = 10;

//////////////////////////////////////////////////////////////////////
//Point auto allocation
enum {_NOT_AUTOALLOT = 0, _AUTOALLOT = 1};

struct WantedInfoStruct{
		char	szName[_MAX_NAMESIZE];
		int		nBonuty;
		OBJID	idModifyWanted;
		OBJID	idWanted;
};

struct	UserInfoStruct
{
	OBJID			id;

	NAMESTR			szName;			// 名字
	NAMESTR			szNickname;			// 名字
	NAMESTR			szMate;			// 配偶名字

	DWORD			dwLook;		//int(4) unsigned
	DWORD			dwFace;		//int(4) unsigned
	DWORD			dwHair;
	char			cLength;		// 高度 -- zlong 2004-02-03
	char			cFat;			// 胖瘦 -- zlong 2004-02-03

	DWORD			dwMoney;			//int(4) unsigned	身上的金钱
	DWORD			dwMoney_saved;	//int(4) unsigned		存储的金钱
	DWORD			dwCoin_money;	//mediumint(3) unsigned 
	DWORD			dwReputation;

	UCHAR			ucLevel;			//tinyint(1) unsigned	等级
	DWORD			dwCultivation;
	int				nExp;			//int(4) ?? 为什么不用unsigned?	当前经验

	USHORT			usLife;
	USHORT			usPower;			//smallint(2) unsigned
	USHORT			usPhysique;		//smallint(2) unsigned			力量
	USHORT			usStamina;	//smallint(2) unsigned			体质 -- add by zlong 2004-1-30
	USHORT			usForce;	//smallint(2) unsigned			敏捷
	USHORT			usSpeed;		//smallint(2) unsigned			耐力
	USHORT			usDegree;			//smallint(2) unsigned			精神

	DWORD			nSmith;
	DWORD			nCreative;
	DWORD			nMedicine;
	DWORD			nSteal;

	DWORD			marchingPetId;
	BYTE			petCount;
	DWORD			petId[MAX_PETS];

	BYTE			skillCount;
	OBJID			skillId[MAX_USERSKILLS];

	OBJID			idWeapon;
	OBJID			idArmor;
	OBJID			idShoes;
	OBJID			idBody;
	OBJID			idHead;

	USHORT			usAdditional_point; //smallint(2) unsigned		可分配点数
	UCHAR			ucAuto_allot;		//tinyint(1) unsigned		是否自动分配
	UCHAR			ucProfession;	//tinyint(2) unsigned			职业
	int				nPotential;		//int(4)						潜能
	SHORT			sPk;			//smallint(2) 
	UCHAR			ucNobility;		//tinyint(1) unsigned
	char			setMedal[MEDAL_BUFSIZE];			//int(4) unsigned	勋章
	DWORD			dwMedal_select;	//int(4) unsigned
	char			setTitle[TITLE_BUFSIZE];			//int(4) unsigned	称号
	DWORD			dwTitle_select;	//int(4) unsigned
	DWORD			ucMetempsychosis;	//tinyint(1) unsigned		转世轮回
	OBJID			idSyndicate;	//int(4) unsigned				所属帮派
	OBJID			idSubgroup;	//int(4) unsigned				所属帮派
	WORD			wSynRank;	//int(4) unsigned				所属帮派
	OBJID			idRecordmap;	//int(4)
	USHORT			usRecordX;
	USHORT			usRecordY;		//int(4) unsigned
	OBJID			idAccount;	//int(4) unsigned
	DWORD			dwLast_login;	 //int(8) unsigned
	DWORD			dwTaskMask;
//	DWORD			dwVirtue;
	OBJID			idHome;	//int(4) unsigned
	DWORD			dwLockKey;
	int				nTutorExp;
	UCHAR			ucTutorLevel;
	DWORD			dwMaxlifePercent;	// 当前最大血量千分比

	UCHAR			ucMercenaryRank;	// 佣兵等级
	DWORD			dwMercenaryExp;		// 佣兵经验

	UCHAR			ucNobilityRank;		// 爵位
	DWORD			dwExploit;			// 功勋值

	// 玩家临时状态
	I64				i64Effect;
	DWORD			dwStatus;
	UCHAR			ucPkMode;			// PK模式
	USHORT			usEnergy;			// 当前体力
	USHORT			usMaxEnergy;		// 最大体力
	DWORD			dwCurrLockKey;

	DWORD			dwMonsterType;		//? only use for just change mapgroup
	DWORD			dwMonsterSecs;		//? only use for just change mapgroup
	
	// wanted
	struct WantedInfoStruct infoWanted;
	OBJID	idPoliceWanted;
};


class IRecord;
class IDatabase;
class CUserData
{
public:
	CUserData();
	virtual ~CUserData();

#ifdef _DEBUG
	void			SetName			(const char* pszName);
#endif

protected:
	bool	Create					(OBJID idUser, IDatabase* pDb);
	bool	LoadInfo				(void);
	bool	SaveInfo				(void);

public: // set to info, use by CUser
	DWORD GetLastLogin();
	void			SetMate			(LPCTSTR szMate, BOOL bUpdate = TRUE);	// 很少使用，默认直接修改数据库
	char*			GetMate			();

	void			SetLife			(int nLife, BOOL bUpdate = false);
	USHORT			GetLife			()	{return m_Info.usLife;}

	int				GetPower		()	{return m_Info.usPower;}
	void			SetPower		(int nPower, BOOL bUpdate = false);
	
	void			SetExp			(int nExp, BOOL bUpdate = false);
	int				GetExp			()	{return m_Info.nExp;}

	void			SetPk			(int nPk, BOOL bUpdate = TRUE);	// 很少使用，默认直接修改数据库
	int				GetPk			()	{return m_Info.sPk;}

	void			SetLev			(int nLev, BOOL bUpdate = TRUE);
	int				GetLev			();

	void			SetCultivation	(int nCultivation, BOOL bUpdate = TRUE);
	int				GetCultivation	();

	void			SetAddPoint		(int nAddPoint, BOOL bUpdate = TRUE);
	int				GetAddPoint		();

	void			SetPotential	(int nData, BOOL fUpdate = TRUE);	// 设置潜能值
	void			SetMedalSelect	(int nData, BOOL fUpdate = TRUE);
	void			SetTitleSelect	(int nData, BOOL fUpdate = TRUE);

	void			SetAutoAllot	(int nAutoAllot, BOOL fUpdate = TRUE);
	int				GetAutoAllot	();

	void			SetMetempsychosis	(int nMetempsychosis, BOOL fUpdate = TRUE);
	int				GetMetempsychosis() { return m_Info.ucMetempsychosis; };
	int				GetAlignment();
	int				GetReborn();
	int				GetRankType();
	int				GetMasterType();

	void			SetMoney		(int nMoney, BOOL bUpdate = false);	// 很常使用，默认不直接修改数据库
	void			SetMoneySaved	(int nMoney, BOOL bUpdate = false);	// 很常使用，默认不直接修改数据库

	void			SetRecordPos	(OBJID idMap, DWORD dwX, DWORD dwY, BOOL bUpdate = false);
	OBJID			GetRecordMap	()	{return m_Info.idRecordmap;}
	DWORD			GetRecordX		()	{return m_Info.usRecordX;}
	DWORD			GetRecordY		()	{return m_Info.usRecordY;}

	void			SetProfession	(DWORD dwProfession, BOOL bUpdate = TRUE);	// 很少使用，默认直接修改数据库
	DWORD			GetProfession	()	{return m_Info.ucProfession;}

	void			SetForce		(int nForce, BOOL bUpdate = false);
	DWORD			GetForce		() { return m_Info.usForce; }

	void			SetPhysique		(int nPhysique, BOOL bUpdate = false);
	DWORD			GetPhysique		() { return m_Info.usPhysique; }

	void			SetDegree		(DWORD dwDex, BOOL bUpdate = false);
	DWORD			GetDegree		()	{return m_Info.usDegree;}

	void			SetSpeed		(DWORD dwSpeed, BOOL bUpdate = false);
	DWORD			GetSpeed		()	{return m_Info.usSpeed;}

	void			SetStamina		(DWORD dwStamina, BOOL fUpdate = false);
	DWORD			GetStamina		()	{return m_Info.usStamina;}

	void			SetPetRaising	(int nPetRaise, BOOL bUpdate = false);
	DWORD			GetPetRaising	() { return GetMedicine(); }
	DWORD			GetMedicine		() { return m_Info.nMedicine; }

	//void			SetSoul			(DWORD dwSoul, BOOL fUpdate = TRUE);
	//DWORD			GetSoul			()	{return m_Info.usSoul;}

	void			SetLook			(DWORD dwLookFace, BOOL fUpdate = TRUE);
	DWORD			GetLook			()	{return m_Info.dwLook;}

	void			SetFace			(DWORD dwFace, BOOL fUpdate = TRUE);
	DWORD			GetFace			() { return m_Info.dwFace; }

	void			SetHair			(DWORD dwHair, BOOL fUpdate = TRUE);
	DWORD			GetHair			()	{return m_Info.dwHair;}

	void			SetLastLogin	();

	void			SetTaskMask		(DWORD dwMask);	
	DWORD			GetTaskMask		()	{ return m_Info.dwTaskMask; }

//	void			SetVirtue		(DWORD dwVirtue, BOOL bUpdate = TRUE);	
//	DWORD			GetVirtue		()	{ return m_Info.dwVirtue; }

	void			SetHomeID		(OBJID idHome, BOOL bUpdate = TRUE);	
	DWORD			GetHomeID		()	{ return m_Info.idHome; }

	void			SetLockKey		(DWORD dwLockKey, BOOL bUpdate = TRUE);	
	void			SetCurrLockKey	(DWORD dwLockKey, BOOL bUpdate = TRUE)		{ m_Info.dwCurrLockKey = dwLockKey; }
	DWORD			GetRealLockKey	()	{ return m_Info.dwLockKey; }
	DWORD			GetCurrLockKey	()	{ return m_Info.dwCurrLockKey; }
	
	int				GetNobilityRank		()	{ return m_Info.ucNobilityRank; }
	void			SetNobilityRank		(DWORD dwNobilityRank, BOOL bUpdate = TRUE);

	void			SetLength		(int nLength, BOOL bUpdate = TRUE);
	int				GetLength		()	{ return m_Info.cLength; }

	void			SetFat			(int nFat, BOOL bUpdate = TRUE);
	int				GetFat			()	{ return m_Info.cFat; }

	void			SetTutorExp		(int nExp, BOOL bUpdate = TRUE);
	void			SetTutorLevel	(UCHAR ucLevel, BOOL bUpdate = TRUE);

	void			SetMaxLifePercent(DWORD dwPercent, BOOL bUpdate = TRUE);
	DWORD			GetMaxLifePercent()	{ return m_Info.dwMaxlifePercent; }

	void			SetMercenaryRank(UCHAR ucRank, BOOL bUpdate = TRUE);
	void			SetMercenaryExp	(DWORD dwExp, BOOL bUpdate = TRUE);
	
	DWORD			GetExploit		()	{ return m_Info.dwExploit; }
	void			SetExploit		(DWORD dwExploit, BOOL bUpdate = TRUE);

	//Equipment

	void SetWeapon	(OBJID itemID, BOOL bUpdate = true);
	void SetArmor	(OBJID itemID, BOOL bUpdate = true);
	void SetShoes	(OBJID itemID, BOOL bUpdate = true);
	void SetBodyAcc	(OBJID itemID, BOOL bUpdate = true);
	void SetHeadAcc	(OBJID itemID, BOOL bUpdate = true);

	UserInfoStruct&		GetInfo()	{ return m_Info; }
protected:
	UserInfoStruct		m_Info;
	IRecord*			m_pRes;

	friend class CUser;		// 所有内容由CUser操作
};

#endif // !defined(AFX_USERDATA_H__6C3EB549_7325_4A50_82DF_FD07A49E1300__INCLUDED_)
