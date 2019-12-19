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
class  ISocket;
class CMsgUserInfo : public CNetMsg
{
public:
	CMsgUserInfo();
	virtual ~CMsgUserInfo();

public:	
	BOOL			Create		(CUser* pUser);
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

		int		nTutorExp;		// ��ʦ����
		DWORD	dwMercenaryExp;	// Ӷ������

		int		nPotential;			// Ǳ��
		USHORT	usForce;				// ����
		USHORT	usConstitution;		// ����
		USHORT	usDexterity;			// ����
		USHORT	usSpeed;				// �ٶ� -- �ͻ��˵��ƶ��ٶ�
		USHORT	usHealth;			// ����
		USHORT	usSoul;				// ����
		USHORT	usAdditionalPoint;
		USHORT	usLife;
		USHORT	usMaxLife;		// �ͻ��˷���������������ˣ����ɷ������ṩ
		USHORT	usMana;

		SHORT	sPk;
		UCHAR	ucLevel;
		UCHAR	ucProfession;

		UCHAR	ucNobility;		// to be deleted
		UCHAR	ucMetempsychosis;	// to be deleted
		UCHAR	ucAutoAllot;
		UCHAR	ucTutorLevel;		// ��ʦ�ȼ�

		UCHAR	ucMercenaryRank;	// Ӷ���ȼ�
		UCHAR	ucNobilityRank;	// ��λ
		USHORT	usMaxEudemon;	// �����ٻ�������
		DWORD	dwExploit;		// ��ѫֵ
		// for str packer
		char szBuf[1];
	}MSG_Info;
	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGUSERINFO_H__DFC94B21_4F65_11D5_A212_0000E8E7F527__INCLUDED_)
