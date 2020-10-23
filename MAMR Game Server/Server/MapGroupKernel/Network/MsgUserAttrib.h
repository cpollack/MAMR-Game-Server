///////////////////////////////////////////////////////////
//
//		CMsgUserAttrib.h
//

#ifndef		_MSGUSERSTATUS_H_
#define		_MSGUSERSTATUS_H_

#include "NetMsg.h"


// 取消32位的掩码限制
//const _MAX_MSGATRRIB	=32;			// ★：由于取数值属性时使用32位整数作为DIRTY掩码，故该值不能超过32。

enum {  _USERATTRIB_LIFE				= 0,
		_USERATTRIB_MAXLIFE,
		_USERATTRIB_MANA				= 2,
		_USERATTRIB_MAXMANA,
		_USERATTRIB_MONEY				= 4,
		_USERATTRIB_EXP,
		_USERATTRIB_REP,
		_USERATTRIB_THIEF,
		_USERATTRIB_KUNGFU,
		_USERATTRIB_PETRAISE,
		_USERATTRIB_WUXING,
		_USERATTRIB_MONEYSAVED,
		_USERATTRIB_ADDPOINT,
		_USERATTRIB_LOOK,
		_USERATTRIB_LEV,
		_USERATTRIB_PHYSIQUE,
		_USERATTRIB_STAMINA,
		_USERATTRIB_FORCE,
		_USERATTRIB_SPEED,
		_USERATTRIB_DEGREE,
		_USERATTRIB_PK,
		_USERATTRIB_POSE,	
		_USERATTRIB_CULT,
		_USERATTRIB_LOCKKEY,
		_USERATTRIB_ALIGNMENT,
		_USERATTRIB_RANK,
		_USERATTRIB_VIRTUE,
		_USERATTRIB_REBORN,


		_USERATTRIB_PROFFER,
		_USERATTRIB_LENGTH,						// zlong 2004-02-03
		_USERATTRIB_SUPERMAP_ORDER,
										//23
		_USERATTRIB_EXPLOIT,	// 功勋值
		_USERATTRIB_MERCENARYRANK,				// 佣兵等级
		_USERATTRIB_KEEPEFFECT,	// 低32位的魔法状态
		_USERATTRIB_HAIR,
		//_USERATTRIB_XP					= 28,
		_USERATTRIB_ACTIONSPEED,	// 行动速度  zlong 2004.09.18
		_USERATTRIB_MERCENARYEXP,	// 佣兵经验
		_USERATTRIB_FAT,	// zlong 2004-02-03
		_USERATTRIB_TUTOR_EXP,	// 导师等级
		_USERATTRIB_TUTOR_LEVEL,	// 导师经验
		_USERATTRIB_POTENTIAL,	// 潜能
		_USERATTRIB_KEEPEFFECT2,	// 高32位的魔法状态
		_USERATTRIB_MAXENERGY,	// 最大体力
		_USERATTRIB_ARMORTYPE,	// 帮派成员时，改变玩家的身体的颜色
		_USERATTRIB_MAXEUDEMON,	// 最大可召唤幻兽数

		_USERATTRIB_NONE	= -1,			// 非法值
};

typedef struct 
{
	DWORD	ucAttributeType;
	DWORD	dwAttributeData;
}UserAttribStruct;

class CMsgUserAttrib : public CNetMsg
{
public:
	CMsgUserAttrib();
	virtual ~CMsgUserAttrib();

public:		//接口函数
//	BOOL	Create(OBJID idUser, int nType, DWORD dwData);
	BOOL	Create(OBJID idUser, int nType, I64 i64Data);

//	BOOL	Append(int nType, DWORD dwData);
	BOOL	Append(int nType, I64 i64Data);

public:
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

private:
	typedef struct
	{
		MSGHEAD_DEFINE

		OBJID				idUser;
		DWORD				dwAttributeNum;
		UserAttribStruct	setUserAttrib[1];			// 变长
	}MSG_Info;
	
	MSG_Info*	m_pInfo;
};

#endif