// DropRule.cpp: implementation of the CDropRule class.
//
//////////////////////////////////////////////////////////////////////

#include "DropRule.h"
#include "basefunc.h"


MYHEAP_IMPLEMENTATION(CDropRule,s_heap)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDropRule::CDropRule()
{
	m_idRule	= ID_NONE;
}

CDropRule::~CDropRule()
{
	m_setItemType.clear();
}

//////////////////////////////////////////////////////////////////////
// �����ظ�Create�����ظ�Create����Ϊ��ͬһ�����ʵ���Ʒ
bool	CDropRule::Create(IRecordset*	pRes)
{
	if (!pRes)
		return false;

	IRecord* pRecord = pRes->CreateNewRecord();

	bool ret = LoadInfo(pRecord);
	SAFE_RELEASE (pRecord);
	return ret;
}
//////////////////////////////////////////////////////////////////////

bool	CDropRule::LoadInfo(IRecord*	pRes)
{
	if (!pRes)
		return false;

	if (m_idRule == ID_NONE)
	{
		m_idRule	= pRes->LoadDWord("ruleid");
		m_nChance	= pRes->LoadDWord("Chance");
	}

	DEBUG_TRY
	for (int i=DROPRULEDATA_ITEM0; i<=DROPRULEDATA_ITEM14; i++)
	{
		OBJID	idType	= (OBJID)pRes->GetInt(i);
		if (idType != ID_NONE)
			m_setItemType.push_back(idType);
	}
	DEBUG_CATCH("CDropRule::LoadInfo()")
	return true;
}
//////////////////////////////////////////////////////////////////////

OBJID	CDropRule::GetDropItem(int nTotalChance, int nRand)
{
	OBJID	idType = ID_NONE;
	// TODO: ���ݵ������ʼ��������ƷID������������������Ʒ�򷵻�ID_NONE
	DEBUG_TRY
	if (m_nChance > 0)
	{
		if (nRand < nTotalChance+m_nChance)
		{
			//������������ֱ�Ϊ��λ
			int nIndex = ::RandGet(m_setItemType.size());
			idType = m_setItemType[nIndex];
		}
	}
	DEBUG_CATCH("CDropRule::GetDropItem()")
	return idType;
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
