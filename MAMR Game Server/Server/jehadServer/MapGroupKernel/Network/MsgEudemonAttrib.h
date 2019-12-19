// MsgEudemonAttrib.h: interface for the CMsgEudemonAttrib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGEUDEMONATTRIB_H__8564AAFC_105E_49B7_9B62_12E1D65F5019__INCLUDED_)
#define AFX_MSGEUDEMONATTRIB_H__8564AAFC_105E_49B7_9B62_12E1D65F5019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"


enum {
	_EA_ACTION_NONE = 0,
	_EA_ACTION_QUERY,			// ��ѯ����
	_EA_ACTION_ATTRIB,			// ��������
};

const int _MAX_EUDEMON_ATTRIB	= 8;
enum {
	_EUDEMONATTRIB_ATK_MAX,			// ������
	_EUDEMONATTRIB_ATK_MIN,
	_EUDEMONATTRIB_MAGICATK_MAX,	// ħ������
	_EUDEMONATTRIB_MAGICATK_MIN,
	_EUDEMONATTRIB_DEF,				// �������
	_EUDEMONATTRIB_MAGICDEF,		// ħ������
	_EUDEMONATTRIB_LIFE,			// ����
	_EUDEMONATTRIB_MAXLIFE,			// �������
//	_EUDEMONATTRIB_FIDELITY,		// ���ܶ�
};

typedef struct {
	DWORD	dwAttributeType;
	DWORD	dwAttributeData;
} ST_EUDEMON_ATTRIB;

class CMsgEudemonAttrib : public CNetMsg  
{
public:
	CMsgEudemonAttrib();
	virtual ~CMsgEudemonAttrib();

public:		//�ӿں���
	BOOL	Create(USHORT usAction, OBJID idEudemon, int nType, DWORD dwData);
	BOOL	Append(int nType, DWORD dwData);

	BOOL	Create(USHORT usAction, OBJID idEudemon, int nAttribNum, ST_EUDEMON_ATTRIB setEudemonAttrib[]);

public:
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

private:
	typedef struct
	{
		MSGHEAD_DEFINE

		USHORT				usAction;
		OBJID				idEudemon;
		DWORD				dwAttributeNum;
		ST_EUDEMON_ATTRIB	setEudemonAttrib[1];			// �䳤
	}MSG_Info;
	
	MSG_Info*	m_pInfo;

};

#endif // !defined(AFX_MSGEUDEMONATTRIB_H__8564AAFC_105E_49B7_9B62_12E1D65F5019__INCLUDED_)
