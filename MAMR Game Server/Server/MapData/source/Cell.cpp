///////////////////////////////////////
// cell.cpp
///////////////////////////////////////
#pragma warning(disable:4786)
#include "windows.h"
#include "typedef.h"
#include "cell.h" 

//-------------------------------------
// static 
MYHEAP_IMPLEMENTATION(CCell,s_heap);

//-------------------------------------

CCell::CCell(CLayer* pLayer)
		: m_nAlt2Mask( ( (pLayer->nAltitude*2) & MASK_ALTITUDE) | (pLayer->dwMask ? MASK_MASK : 0) )
{
/*/	m_setLayer.clear();
	CLayer* pLayer = new CLayer;
	if(pLayer)
	{
		this->AddLayer(pLayer);
	}*/
//	m_bSearched		= false;
	m_nCountFlag	= 0;
	m_idxLayer		= IDXLAYER_NONE;

	delete pLayer;
}

//-------------------------------------

CCell::~CCell()
{
	this->Destory();
	ASSERT((m_nCountFlag&MASK_ROLECOUNT) == 0);
}

//-------------------------------------

CCell* CCell::CreateNew(CLayer* pLayer)
{
	CCell* pCell = new CCell(pLayer);
//	if(pCell)
//		pCell->AddLayer(pLayer);

	return pCell;
}

//-------------------------------------

bool CCell::Create(int nAlt, DWORD dwMask)
{
	m_nAlt2Mask		= ((nAlt*2) & MASK_ALTITUDE) | (dwMask ? MASK_MASK : 0);
	m_nCountFlag	= 0;
	m_idxLayer		= IDXLAYER_NONE;
	return true;
}

//-------------------------------------

void CCell::Destory()
{
/*	int nAmount = m_setLayer.size();
	int i = 0;
	for(i = nAmount-1; i >= 0; i --)
	{
		CLayer* pLayer = m_setLayer[i];
		SAFE_DELETE(pLayer);
	}
	m_setLayer.clear();
*/
	//??? û���ͷ����LAYER
}

//-------------------------------------

int CCell::GetLayerAmount(DEQUE2_LAYER& set2Layer)
{
	if(m_idxLayer == IDXLAYER_NONE) 
		return 1; 
	else 
		return 1+set2Layer[m_idxLayer].size();
}

//-------------------------------------

CLayer* CCell::Getlayer(DEQUE2_LAYER& set2Layer, int nIndex)	//�� ����ȡ��0��
{
	CHECKF(nIndex > 0);			// ����Ϊ0
	CHECKF(m_idxLayer != IDXLAYER_NONE);
	CHECKF(m_idxLayer < set2Layer.size());

	if((nIndex < 0)||(nIndex >= set2Layer[m_idxLayer].size()))
		return NULL;

	return set2Layer[m_idxLayer][nIndex];
}

//-------------------------------------

void  CCell::AddLayer(DEQUE2_LAYER& set2Layer, CLayer* pLayer)
{
	if(!pLayer)
		return;

	if(m_idxLayer == IDXLAYER_NONE) 
	{
		for(int i = 0; i < set2Layer.size(); i++)
		{
			if(set2Layer[i].size() == 0)
			{
				m_idxLayer	= i;
				set2Layer[i].push_back(pLayer);
				return ;
			}
		}
		int nOldSize = set2Layer.size();
		set2Layer.resize(nOldSize + 1);
		m_idxLayer	= nOldSize;
		set2Layer[m_idxLayer].push_back(pLayer);
	}
	else 
		set2Layer[m_idxLayer].push_back(pLayer);
}

//-------------------------------------

bool  CCell::DelLayer(DEQUE2_LAYER& set2Layer, int nIndex /*= LAYER_TOP*/)
{
	CHECKF(nIndex == LAYER_TOP || nIndex > 0);	//�� ����ɾ����0��
	CHECKF(m_idxLayer != IDXLAYER_NONE);		// �ﲻ��ɾ����Ƥ
	CHECKF(m_idxLayer < set2Layer.size());

	if(!( nIndex == LAYER_TOP || nIndex >= 0 && nIndex < set2Layer[m_idxLayer].size() ))
		return false;

	int	idx;
	if(nIndex == LAYER_TOP)
		idx	= set2Layer[m_idxLayer].size() - 1;
	else
		idx = nIndex - 1;

	CLayer* pLayer = set2Layer[m_idxLayer][idx];
	if(pLayer)
	{
		delete pLayer;
		pLayer = NULL;
	}

	set2Layer[m_idxLayer].erase(set2Layer[m_idxLayer].begin() + idx);
	if(set2Layer[m_idxLayer].size() == 0)
		m_idxLayer = IDXLAYER_NONE;

	return true;
}

//-------------------------------------

DWORD CCell::GetFloorMask(DEQUE2_LAYER& set2Layer)
{
	if(m_idxLayer == IDXLAYER_NONE) 
		return (m_nAlt2Mask&MASK_MASK) != 0; 
	else 
	{
		int nAmount = set2Layer[m_idxLayer].size();
		if(nAmount > 0)
		{
			CLayer* pLayer = set2Layer[m_idxLayer][nAmount-1];
			if(pLayer)
			{
				return pLayer->dwMask;
			}
		}
		ASSERT(!"CCell::GetFloorMask");
		return 1;		// ���������ֹ
	}
}

//-------------------------------------

int CCell::GetFloorAttr(DEQUE2_LAYER& set2Layer)
{
	if(m_idxLayer == IDXLAYER_NONE) 
		return DEFAULT_FLOORATTR;					// �������ݲ��õر�����(��֧��LAYER��������)
	else 
	{
		int nAmount = set2Layer[m_idxLayer].size();
		if(nAmount > 0)
		{
			CLayer* pLayer = set2Layer[m_idxLayer][nAmount-1];
			if(pLayer)
			{
				return pLayer->nTerrian;
			}
		}
		ASSERT(!"CCell::GetFloorAttr");
		return DEFAULT_FLOORATTR;		// ȱʡ
	}
}

//-------------------------------------

int CCell::GetFloorAlt(DEQUE2_LAYER& set2Layer)
{
	if(m_idxLayer == IDXLAYER_NONE) 
		return short(m_nAlt2Mask&MASK_ALTITUDE) / 2; 
	else 
	{
		int nAmount = set2Layer[m_idxLayer].size();
		if(nAmount > 0)
		{
			CLayer* pLayer = set2Layer[m_idxLayer][nAmount-1];
			if(pLayer)
			{
				return pLayer->nAltitude;
			}
		}
		ASSERT(!"CCell::GetFloorAlt");
		return ALTITUDE_LIMIT;		// ���������ֹ
	}
}

//-------------------------------------

int CCell::GetSurfaceAlt()
{
	return (m_nAlt2Mask&MASK_ALTITUDE) / 2;
}

