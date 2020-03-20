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
		BYTE bLook;
		BYTE bFace;

		WORD wLevel;
		WORD wLife;
		WORD wLifeMax;
		WORD wMana;
		WORD wManaMax;

		BYTE bRank;
		BYTE bReborn;
		BYTE bRankDetails;

		DWORD dwMoney;
		DWORD dwReputation;
		DWORD dwPK;
		DWORD dwCultivation;
		DWORD dwExperience;
		DWORD dwWuxing;
		DWORD dwKungfu;
		DWORD dwPetRaising;
		DWORD dwThievery;

		WORD wAdditionalPoint;
		WORD wPhysique;
		WORD wStamina;
		WORD wForce;
		WORD wSpeed;
		WORD wDegree;

		WORD wRecordX;
		WORD wRecordY;
		DWORD dwRecordMap;

		DWORD dwSyndicateID;
		DWORD dwSubgroupID;
		WORD wSyndicateRank;

		// for str packer
		char szBuf[1];
	}MSG_Info;
	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGUSERINFO_H__DFC94B21_4F65_11D5_A212_0000E8E7F527__INCLUDED_)
