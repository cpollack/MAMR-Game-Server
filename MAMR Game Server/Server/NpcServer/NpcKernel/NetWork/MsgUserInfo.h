// MsgUserInfo.h: interface for the CMsgUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGUSERINFO_H__DFC94B21_4F65_11D5_A212_0000E8E7F527__INCLUDED_)
#define AFX_MSGUSERINFO_H__DFC94B21_4F65_11D5_A212_0000E8E7F527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

struct UserInfoStruct;
class CMsgUserInfo : public CNetMsg
{
public:
	CMsgUserInfo();
	virtual ~CMsgUserInfo();

public:	
	BOOL			Create		(OBJID idUser, const UserInfoStruct* pInfo);
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void *pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		OBJID id;
		DWORD dwLookFace;		// ��ò
		USHORT usHair;			// ͷ��
		char cLength;			// �߶� -- zlong 2004-02-03
		char cFat;				// ���� -- zlong 2004-02-03
		DWORD dwMoney;			// ��Ǯ
		LONG nExp;				// ����

		int		nTutorExp;			// ��ʦ����
		DWORD	dwMercenaryExp;		// Ӷ������

		int    nPotential;			// Ǳ��
		USHORT usForce;				// ����
		USHORT usConstitution;		// ����
		USHORT usDexterity;			// ����
		USHORT usSpeed;				// �ٶ� -- �ͻ����õ��ƶ��ٶ�
		USHORT usHealth;			// ����
		USHORT usSoul;				// ����

		USHORT usAdditionalPoint;

		USHORT usLife;
		USHORT usMaxLife;
		USHORT usMana;
		SHORT sPk;

		UCHAR ucLevel;
		UCHAR ucProfession;
		UCHAR ucNobility;
		UCHAR ucMetempsychosis;
		UCHAR ucAutoAllot;

		UCHAR ucTutorLevel;		// ��ʦ�ȼ�
		UCHAR ucMercenaryRank;	// Ӷ���ȼ�

		UCHAR ucNobilityRank;	// ��λ
		DWORD dwExploit;		// ��ѫֵ
		
		// for str packer
		char			szBuf[1];
		//	name[16]
		//	mate[16]
	}MSG_Info;
	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGUSERINFO_H__DFC94B21_4F65_11D5_A212_0000E8E7F527__INCLUDED_)
