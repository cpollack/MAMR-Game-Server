// MsgPlayer.h: interface for the CMsgPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGPLAYER_H__298DE32A_21B9_41E0_8728_CD895F36A959__INCLUDED_)
#define AFX_MSGPLAYER_H__298DE32A_21B9_41E0_8728_CD895F36A959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "NetStringPacker.h"
#include "../AiNpc.h"


//////////////////////////////////////////////////////////////////////
// ����dwSynID_Rank
const DWORD	MASK_SYNID			= 0x00FFFFFF;
const DWORD	MASK_RANK_SHIFT		= 24;

class CUser;
class CMsgPlayer : public CNetMsg  
{
public:
	CMsgPlayer();
	virtual ~CMsgPlayer();

public:	
//	BOOL			Create		(CBooth* pBooth);
	BOOL			Create		(IRole* pRole);

	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void *pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID id;
		DWORD dwLookFace;
		union
		{
			//I64 i64Status;
			DWORD	dwStatus[2];
			struct
			{
				USHORT usStatuaryLife; // ��������
				USHORT usStatuaryFrame;// ����֡��
			};
		};

		union
		{
			DWORD	dwSynID_Rank;		// �ǻ�����Ч
			OBJID	idOwner;			// ������Ч
		};
		
		DWORD dwArmorType;
		DWORD dwWeaponRType;
		
		union
		{
			DWORD	dwMantleType;
			struct {
				USHORT	usMaxLife;				// ��PlayerΪMonster��ʱ�򣬱�ʾ�������
				USHORT	usMonsterLife;			// ��PlayerΪMonster��ʱ�򣬱�ʾ��ǰ����
			};
		};

		union
		{
			DWORD dwMountType;
			struct
			{
				USHORT usLife;		//	������Ч
				USHORT usLevel;		//  ����ȼ�
			};
		};

		//unsigned short usMantleType;
		
		USHORT usPosX, usPosY;
		USHORT usHair;

		// zlong 2004-02-03
		char cLength;
		char cFat;
		
		UCHAR ucDir;
		UCHAR ucPose;

		union {
			struct {
				UCHAR ucActionSpeed;		// �ж��ٶ�
				UCHAR ucTutorLevel;			// ��ʦ�ȼ�
				UCHAR ucMercenaryRank;		// Ӷ���ȼ�
				UCHAR ucNobilityRank;		// ��λ
			};
			OBJID	idMonsterType;			// ����ͻ�����Ч
		};
		// for str packer
		char szBuf[1];
	}MSG_Info;
	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;

};

#endif // !defined(AFX_MSGPLAYER_H__298DE32A_21B9_41E0_8728_CD895F36A959__INCLUDED_)
