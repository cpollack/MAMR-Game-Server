// MsgSynMemberInfo.h: interface for the CMsgSynMemberInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGSYNMEMBERINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_)
#define AFX_MSGSYNMEMBERINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"


class CMsgSynMemberInfo : public CNetMsg  
{
public:
	CMsgSynMemberInfo();
	virtual ~CMsgSynMemberInfo();

	BOOL	Create		(class CUser* pUser);
	BOOL	Create		(char* pMsgBuf, DWORD dwSize);
	void	Process		(void* pInfo);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		int 	nProffer;					// ���׶�
		UCHAR	ucRank;						// ְλ
		UCHAR	ucProfession;				// ְҵ
		UCHAR	ucNobilityRank;				// ��λ
		UCHAR	ucLevel;					// �ȼ�
		SHORT	sPk;						// PKֵ
		DWORD	dwLookFace;					// 
		char	szName[_MAX_NAMESIZE];		// ����
		char	szMate[_MAX_NAMESIZE];		// ��ż����
	}MSG_Info;

	MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGSYNMEMBERINFO_H__683B9A1E_9C3D_41E1_B90D_8DF5ABE79632__INCLUDED_)
