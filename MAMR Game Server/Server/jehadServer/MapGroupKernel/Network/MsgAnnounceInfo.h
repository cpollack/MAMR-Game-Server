// MsgAnnounceInfo.h: interface for the CMsgAnnounceInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGANNOUNCEINFO_H__A8C4D920_B8F1_4651_A8F2_7E915AFC7F9F__INCLUDED_)
#define AFX_MSGANNOUNCEINFO_H__A8C4D920_B8F1_4651_A8F2_7E915AFC7F9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NetMsg.h"
#include "AnnounceData.h"

enum{_ANNOUNCE_ISSUE = 0,        //��������to server
     _ANNOUNCE_CHECK,            //�鿴����to client
	 _ANNOUNCE_SLEF_CHECK,       //�鿴�Լ��Ĺ���to client
	 _ANNOUNCE_USER_INFO,        //to server/client�ڷ���ʱ���ͻ���Ҫ�õ�����Ϣ�� ���ؿͻ��˵�:�ȼ���
	                             //����ʦ�ȼ�   ��Ϣ�ṹ��char	szBuf[1]������Ϊ��������ְҵ
	 _ANNOUNCE_CANCEL,           //ȡ������
};
  
class CMsgAnnounceInfo :public CNetMsg 
{
public:
	CMsgAnnounceInfo();
	virtual ~CMsgAnnounceInfo();
	BOOL            Create      (CAnnounceData *pData,int type);
	BOOL            Create      (int level,int teacher_level,const char* name,int profession,int type);
public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(void* pInfo);
protected:
	typedef struct {
		MSGHEAD_DEFINE
        int usType;
		OBJID	idAnnounce;
		OBJID   user_id;
		int     level;
		int     teacher_level;
		int     profession;        //��ʦ�ȼ�
	    char	szBuf[1];
	}MSG_Info;

	MSG_Info*	m_pInfo;
private:
	CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGANNOUNCEINFO_H__A8C4D920_B8F1_4651_A8F2_7E915AFC7F9F__INCLUDED_)
