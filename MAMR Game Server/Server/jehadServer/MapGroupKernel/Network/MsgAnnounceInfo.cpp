// MsgAnnounceInfo.cpp: implementation of the CMsgAnnounceInfo class.
//
//////////////////////////////////////////////////////////////////////
#include "AllMsg.h"
#include "MsgAnnounceInfo.h"
#include "mapgroup.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgAnnounceInfo::CMsgAnnounceInfo()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;

	m_StrPacker.SetBuf(m_pInfo->szBuf, _MAX_MSGSIZE-sizeof(MSG_Info)+1);
}

CMsgAnnounceInfo::~CMsgAnnounceInfo()
{

}
BOOL CMsgAnnounceInfo::Create(char* pMsgBuf, DWORD dwSize)
{
	if (!CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_ANNOUNCE_INFO != this->GetType())
		return false;

	return true;
}
BOOL   CMsgAnnounceInfo::Create(CAnnounceData *pData,int type)
{
	m_pInfo->idAnnounce = pData->GetInt(ANNOUNCEDATA_ID);
	m_pInfo->user_id = pData->GetInt(ANNOUNCEDATA_USER_ID);
	m_pInfo->level = pData->GetInt(ANNOUNCEDATA_LEVEL);        // ���������˵ĵȼ�
	m_pInfo->teacher_level = pData->GetInt(ANNOUNCEDATA_TEACHER_LEVEL);	 // ��ʦ�ȼ�
	m_pInfo->profession = pData->GetInt(ANNOUNCEDATA_PROFESSION);
	m_pInfo->usType = type;
	BOOL bSucMake	=true;  	
	bSucMake    &=m_StrPacker.AddString((char*)pData->GetStr(ANNOUNCEDATA_USER_NAME)); // ��������������
	//bSucMake	&=m_StrPacker.AddString((char*)pData->GetStr(ANNOUNCEDATA_PROFESSION));// ��ʦְҵ
	bSucMake	&=m_StrPacker.AddString((char*)pData->GetStr(ANNOUNCEDATA_TITLE));     // �������
	bSucMake	&=m_StrPacker.AddString((char*)pData->GetStr(ANNOUNCEDATA_CONTENT));   // ��������
	m_unMsgType	=_MSG_ANNOUNCE_INFO;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();

	return true;
}
BOOL CMsgAnnounceInfo::Create(int level,int teacher_level,const char* name,int profession,int type)
{
	m_pInfo->level = level;
	m_pInfo->teacher_level = teacher_level;
	m_pInfo->usType = type;
	m_pInfo->profession = profession;
	BOOL bSucMake = true;
	bSucMake    &=m_StrPacker.AddString((char*)name);
	//bSucMake    &=m_StrPacker.AddString(profession);
	m_unMsgType = _MSG_ANNOUNCE_INFO;
	m_unMsgSize	=sizeof(MSG_Info)-1+m_StrPacker.GetSize();
	return true;
}
void CMsgAnnounceInfo::Process(void* pInfo)
{
	CUserPtr pUser = UserManager()->GetUser(this);
	//CUser* pUser = g_UserManager.GetUser(m_pInfo->user_id);
	switch(m_pInfo->usType)
	{
	case _ANNOUNCE_ISSUE:
		if(Announce()->QueryAnnounceDataByOwner(pUser->GetID()))
		{
			pUser->SendSysMsg(STR_DUPLICATE_ANNOUNCE);
			return ;
		}
		ST_ANNOUNCE_DATA	tAnnounceData;		
		tAnnounceData.level = pUser->GetLev();
		tAnnounceData.user_id = pUser->GetID();
		tAnnounceData.teacherlevel = pUser->GetTutorLevel();
		if(tAnnounceData.teacherlevel < 1)
		{
			pUser->SendSysMsg(STR_LOW_GRADE);
			return ;
		}
/*		switch(pUser->GetProfession())
		{
		case 10:
            strcpy(tAnnounceData.profession,"ħ��ʦ");// ħ��ʦ  11,			// ħ��ʦתְ
			break;
		case 20:
            strcpy(tAnnounceData.profession,"սʿ");// սʿ  21,			// սʿתְ
			break;
		case 30:
			strcpy(tAnnounceData.profession,"������");	// ������  31,			// ������תְ	
			break;
		}*/
		tAnnounceData.profession = pUser->GetProfession();
		sprintf(tAnnounceData.name,"%s",pUser->GetName());

		m_StrPacker.GetString(0, tAnnounceData.title, 32);
		m_StrPacker.GetString(1, tAnnounceData.content, 128);
	/*	if(strlen(tAnnounceData.title) > 32)
		{
			pUser->SendSysMsg("�������");
		    return;
		}
		if(strlen(tAnnounceData.content) > 128 )
		{
			pUser->SendSysMsg("�������");
			return ;
		}*/
		if(Announce()->CreateNewAnnounce(&tAnnounceData,Database()))
			pUser->SendSysMsg(STR_ANNOUNCE_SUCCEED);
		break;
	case _ANNOUNCE_SLEF_CHECK:
		Announce()->SendAnnounceSelf(RoleManager()->QueryRole(m_pInfo->user_id));
		break;
	case _ANNOUNCE_CHECK:
		Announce()->SendAnnounceInfo(RoleManager()->QueryRole(pUser->GetID()/*m_pInfo->user_id*/),m_pInfo->idAnnounce);
		break;
	case _ANNOUNCE_USER_INFO:
	/*	char nProfession[16];
		switch(pUser->GetProfession())
		{
		case 10:
            strcpy(nProfession,"ħ��ʦ");// ħ��ʦ 
			break;
		case 20:
            strcpy(nProfession,"սʿ");// սʿ 
			break;
		case 30:
			strcpy(nProfession,"������");	// ������
			break;
		}*/
        if(Announce()->QueryAnnounceDataByOwner(pUser->GetID()))
		{
			IF_OK(Create(pUser->GetLev(),pUser->GetTutorLevel(), pUser->GetName(), pUser->GetProfession(),_ANNOUNCE_USER_INFO))
				SendMsg(this);
		}
		else 
			pUser->SendSysMsg(STR_NO_ANNOUNCE);
		break;
	case _ANNOUNCE_CANCEL:
        if(Announce()->DeleteAnnounceByObjID(m_pInfo->idAnnounce))
			pUser->SendSysMsg(STR_DELETE_ANNOUNCE);
		else
			pUser->SendSysMsg(STR_NO_ANNOUNCE);
		break;
	}
}