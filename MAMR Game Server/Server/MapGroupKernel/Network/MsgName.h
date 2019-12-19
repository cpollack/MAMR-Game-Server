// MsgName.h: interface for the CMsgName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGNAME_H__62DB03E2_7185_4BDF_B9B0_5AE64B03DFDB__INCLUDED_)
#define AFX_MSGNAME_H__62DB03E2_7185_4BDF_B9B0_5AE64B03DFDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
MAPGROUPKERNEL_BEGIN
enum {	NAMEACT_NONE				= 0, 
		NAMEACT_FIREWORKS			= 1,
		NAMEACT_CREATE_SYN			= 2, 				// �ĵ�TALK��
		NAMEACT_SYNDICATE			= 3, 				// �޷�ʵ���޸İ����������´�
		NAMEACT_CHANGE_TITLE		= 4, 
		NAMEACT_DELROLE				= 5,				// ������
		NAMEACT_MATE				= 6,
		NAMEACT_QUERY_NPC			= 7,				// to server��to client
		NAMEACT_WANTED				= 8,				// to client
		NAMEACT_MAPEFFECT			= 9,				// to client
		NAMEACT_ROLEEFFECT			= 10,
		NAMEACT_MEMBERLIST			= 11,				// to server/client, dwData is index
		MANEACT_KICKOUT_SYNMEM		= 12,
		NAMEACT_QUERY_WANTED		= 13,
		NAMEACT_QUERY_POLICEWANTED	= 14,
		NAMEACT_POLICEWANTED		= 15,
		NAMEACT_QUERY_MATE			= 16,
		NAMEACT_ADDDICE_PLAYER		= 17,			//BcastClient(INCLUDE_SELF) �����������// dwDataΪ����̯ID // To Server ���� ��Ҫԭ��Ϣ����
		NAMEACT_DELDICE_PLAYER		= 18,			//BcastClient(INCLUDE_SELF) ɾ���������// dwDataΪ����̯ID // To Server �뿪 ��Ҫԭ��Ϣ����
		NAMEACT_DICE_BONUS			= 19,			//BcastClient �����ӽ��� ���// dwDataΪMoney
		NAMEACT_PLAYER_WAVE			= 20,			// ����Ч // ���usPosX = usPosY = 0; �ǵ�ͼ��Ч // ѹ����ַ���Ϊ��Ч�����·�� 
		NAMEACT_MEMBERLIST_SPECIFYSYN = 21,			//��ѯָ�����ɵĳ�Ա�б�
		NAMEACT_PLAYERTASKLIST		= 23,			// Ӷ�������ѯ����
		NAMEACT_CHANGE_EUDEMON_NAME	= 24,			// ���޸�����idTarget=������ƷID����һ���ַ���Ϊ����������
};

class CMsgName : public CNetMsg   
{
public:
	CMsgName();
	virtual ~CMsgName();

	BOOL	Create(int nType, const char* pszName, DWORD dwData=0);
	BOOL	Create(int nType, const char* pszName, USHORT usPosX, USHORT usPosY);
	BOOL	AppendStr(const char* pszName);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void* pInfo);
	
private:
	typedef struct{
		MSGHEAD_DEFINE

		union {
			OBJID	idTarget;
			DWORD	dwData;
			struct{
				USHORT  usPosX, usPosY;
			};
		};
		UCHAR	ucType;
		char	szBuf[1];
	}MSG_Info;
	
	MSG_Info*	m_pInfo;

private:
	CNetStringPacker	m_StrPacker;
};
MAPGROUPKERNEL_END

#endif // !defined(AFX_MSGNAME_H__62DB03E2_7185_4BDF_B9B0_5AE64B03DFDB__INCLUDED_)
