// MsgSchoolMember.h: interface for the CMsgSchoolMember class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGSCHOOLMEMBER_H__82E6220E_E387_4CA2_A66E_51466E54A627__INCLUDED_)
#define AFX_MSGSCHOOLMEMBER_H__82E6220E_E387_4CA2_A66E_51466E54A627__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum {
	MESSAGEBOARD_DELMEMBER		= 1, //ɾ��
	MESSAGEBOARD_ADDMEMBER		= 2, //���
	MESSAGEBOARD_UPDATEMEMBER	= 3, //����
};

enum {
	RELATION_TEACHER = 1,		// ��ʦ
	RELATION_STUDENT,			// ͽ��
	RELATION_STUDENTOFSTUDENT,	// ͽ�ܵ�ͽ��(ͽ��)
};

enum {
	MEMBERSTATUS_OFFLINE = 0,	// ����״̬
	MEMBERSTATUS_ONLINE,		// ����״̬
};

typedef struct
{
	OBJID	idMember;				// ��ԱID
	char	szName[_MAX_NAMESIZE];	// ��Ա����
	char	szMate[_MAX_NAMESIZE];	// ��ż����
	UCHAR	ucLevel;				// �ȼ�
	UCHAR	ucProfession;			// ְҵ���
	USHORT	usPkValue;				// PKֵ
	UCHAR	ucNobilityRank;			// ��ݣ���λ��
	UCHAR	ucRelation;				// ����ҹ�ϵ
	UCHAR	ucStatus;				// ״̬ ���� �����ߡ�����
	DWORD	dwSynID_Rank;			// ����ID & ְλ (��MsgPlayerһ������8λΪְλ��ţ���24λΪ����ID)
} ST_MEMBERINFO;

class CMsgSchoolMember : public CNetMsg  
{
public:
	CMsgSchoolMember();
	virtual ~CMsgSchoolMember();

public:	
	BOOL	Create	(UCHAR ucAction, ST_MEMBERINFO* pMember, UCHAR ucAmount);
	BOOL	Append	(UCHAR ucRelation, UCHAR ucStatus, OBJID idMember, const char* pszName = NULL);
	BOOL	Append	(UCHAR ucRelation, UCHAR ucStatus, CUser* pUser);
	BOOL	Create	(char* pMsgBuf, DWORD dwSize);
	void	Process	(CGameSocket* pSocket);

protected:
	typedef struct
	{
		MSGHEAD_DEFINE

		UCHAR		ucAction;			// ��Ϊģʽ
		UCHAR		ucAmount;			// ����
		ST_MEMBERINFO	setMember[1];	// ��Ա�б�
	}MSG_Info;
	MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGSCHOOLMEMBER_H__82E6220E_E387_4CA2_A66E_51466E54A627__INCLUDED_)
