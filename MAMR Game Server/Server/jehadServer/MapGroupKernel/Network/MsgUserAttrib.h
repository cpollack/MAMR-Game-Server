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
		_USERATTRIB_PK					= 6,
		_USERATTRIB_PORFESSION,
		_USERATTRIB_SIZEADD				= 8,
		_USERATTRIB_ENERGY,
		_USERATTRIB_MONEYSAVED			= 10,
		_USERATTRIB_ADDPOINT,
		_USERATTRIB_LOOKFACE			= 12,
		_USERATTRIB_LEV,
		_USERATTRIB_SOUL				= 14,
		_USERATTRIB_HEALTH,
		_USERATTRIB_FORCE				= 16,
		_USERATTRIB_SPEED,						// �ٶ� -- �ͻ����õģ�������û���κι�ϵ
		_USERATTRIB_NOBILITYRANK		= 18,	// ��λ
		//_USERATTRIB_DEGREE				= 18,
		_USERATTRIB_POSE,	
		_USERATTRIB_PROFFER				= 20,
		_USERATTRIB_LENGTH,						// zlong 2004-02-03
		_USERATTRIB_SUPERMAP_ORDER		= 22,
										//23
		_USERATTRIB_EXPLOIT				= 24,	// ��ѫֵ
		_USERATTRIB_MERCENARYRANK,				// Ӷ���ȼ�
		_USERATTRIB_KEEPEFFECT			= 26,	// ��32λ��ħ��״̬
		_USERATTRIB_HAIR,
		_USERATTRIB_XP					= 28,
		_USERATTRIB_ACTIONSPEED			= 29,	// �ж��ٶ�  zlong 2004.09.18
		_USERATTRIB_MERCENARYEXP		= 30,	// Ӷ������
		_USERATTRIB_FAT					= 31,	// zlong 2004-02-03
		_USERATTRIB_TUTOR_EXP			= 32,	// ��ʦ�ȼ�
		_USERATTRIB_TUTOR_LEVEL			= 33,	// ��ʦ����
		_USERATTRIB_DEX					= 34,	// ����
		_USERATTRIB_POTENTIAL			= 35,	// Ǳ��
		_USERATTRIB_KEEPEFFECT2			= 36,	// ��32λ��ħ��״̬
		_USERATTRIB_MAXENERGY			= 37,	// �������
		_USERATTRIB_ARMORTYPE			= 38,	// ���ɳ�Աʱ���ı���ҵ��������ɫ
		_USERATTRIB_MAXEUDEMON			= 39,	// �����ٻ�������

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