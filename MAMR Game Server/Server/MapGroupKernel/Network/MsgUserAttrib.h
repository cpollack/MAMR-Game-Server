///////////////////////////////////////////////////////////
//
//		CMsgUserAttrib.h
//

#ifndef		_MSGUSERSTATUS_H_
#define		_MSGUSERSTATUS_H_

#include "NetMsg.h"


// ȡ��32λ����������
//const _MAX_MSGATRRIB	=32;			// �����ȡ��ֵ����ʱʹ��32λ������ΪDIRTY���룬�ʸ�ֵ���ܳ���32��

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
		_USERATTRIB_EXPLOIT,	// ��ѫֵ
		_USERATTRIB_MERCENARYRANK,				// Ӷ���ȼ�
		_USERATTRIB_KEEPEFFECT,	// ��32λ��ħ��״̬
		_USERATTRIB_HAIR,
		//_USERATTRIB_XP					= 28,
		_USERATTRIB_ACTIONSPEED,	// �ж��ٶ�  zlong 2004.09.18
		_USERATTRIB_MERCENARYEXP,	// Ӷ������
		_USERATTRIB_FAT,	// zlong 2004-02-03
		_USERATTRIB_TUTOR_EXP,	// ��ʦ�ȼ�
		_USERATTRIB_TUTOR_LEVEL,	// ��ʦ����
		_USERATTRIB_POTENTIAL,	// Ǳ��
		_USERATTRIB_KEEPEFFECT2,	// ��32λ��ħ��״̬
		_USERATTRIB_MAXENERGY,	// �������
		_USERATTRIB_ARMORTYPE,	// ���ɳ�Աʱ���ı���ҵ��������ɫ
		_USERATTRIB_MAXEUDEMON,	// �����ٻ�������

		_USERATTRIB_NONE	= -1,			// �Ƿ�ֵ
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

public:		//�ӿں���
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
		UserAttribStruct	setUserAttrib[1];			// �䳤
	}MSG_Info;
	
	MSG_Info*	m_pInfo;
};

#endif