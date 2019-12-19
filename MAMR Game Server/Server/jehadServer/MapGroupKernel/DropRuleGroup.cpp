// DropRuleGroup.cpp: implementation of the CDropRuleGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "common.h"
#include "basefunc.h"

#include "DropRuleGroup.h"


MYHEAP_IMPLEMENTATION(CDropRuleGroup,s_heap)

const int _DROP_CHANCE_PRECISION	= 10000000;		//����Ʒ���ʵľ���Ϊǧ���֮һ

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDropRuleGroup::CDropRuleGroup()
{
	m_idRuleGroup	= ID_NONE;
}

CDropRuleGroup::~CDropRuleGroup()
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////

bool	CDropRuleGroup::Create(OBJID	idRuleGroup, IDatabase*	pDb)
{
	CHECKF(pDb);

//	if (m_idRuleGroup != ID_NONE)
//		return true;

	//ѡ�������򣬲����ո��ʴӵ͵�������
	SQLBUF	szSQL;
	sprintf(szSQL, "SELECT * FROM %s where id=%u order by Chance", _TBL_DROPITEMRULE, idRuleGroup);
	IRecordset* pRes = pDb->CreateNewRecordset(szSQL);
	if(pRes)
	{
		bool ret = LoadInfo(pRes);
		pRes->Release();
		return ret;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////

void	CDropRuleGroup::Destroy()
{
	DEBUG_TRY
	for (int i=0; i<m_setRule.size(); i++)
	{
		CDropRule*	pRule	= m_setRule[i];
		if (pRule)
			pRule->Release();
	}
//	m_setRule.clear();
	DEBUG_CATCH("CDropRuleGroup::Destroy()")
}
//////////////////////////////////////////////////////////////////////

bool	CDropRuleGroup::LoadInfo(IRecordset*	pRes)
{
	CHECKF(pRes);

	//�������Ʒ����
	//���������ݸ��ʺϲ���ͬ�ļ�¼Ϊһ��(��������Ӧ�ð��մӵ͵��ߵ�˳������)

	DEBUG_TRY
	for (int i=0; i<pRes->RecordCount(); i++)
	{
		CDropRule*	pRule = NULL;
		bool bSameChance = false;
		int nChance = pRes->GetInt(DROPRULEDATA_CHANCE);
		for (RULE_SET::iterator it=m_setRule.begin(); it!=m_setRule.end(); it++)
		{
			pRule = *it;
			if (pRule->GetChance() == nChance)
			{
				bSameChance = true;
				break;
			}
			pRule = NULL;
		}

		if (!pRule)
		{
			pRule = CDropRule::CreateNew();
		}

		if (!pRule)
		{
			return false;
		}
		if (!pRule->Create(pRes))
		{
			pRule->Release();
			return false;
		}
		if (!bSameChance)
			m_setRule.push_back(pRule);

		pRes->MoveNext();
	}
	DEBUG_CATCH("CDropRuleGroup::LoadInfo()")
	return true;
}
//////////////////////////////////////////////////////////////////////

OBJID	CDropRuleGroup::GetDropItem()
{
	// ���ݵ������ʼ��������ƷID
	OBJID idType = ID_NONE;

	//������������ֱ�Ϊ��λ
	int	nRand = ::RandGet(_DROP_CHANCE_PRECISION);
	int nTotalChance = 0;
	
	DEBUG_TRY
	for (int i=0; i<m_setRule.size(); i++)
	{
		CDropRule*	pRule	= m_setRule[i];
		IF_NOT (pRule)
			continue;
		if (ID_NONE != (idType = pRule->GetDropItem(nTotalChance, nRand)))
			return idType;

		nTotalChance += pRule->GetChance();
	}
	DEBUG_CATCH("CDropRuleGroup::GetDropItem()");
	return idType;

}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
