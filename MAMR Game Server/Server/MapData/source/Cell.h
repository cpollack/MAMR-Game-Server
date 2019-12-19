////////////////////////////////////////////
// cell.h
///////////////////////////////////////////

#ifndef _CELL_H
#define _CELL_H

//-------------------------------------------------------------
// header files ...
#include "BaseFunc.h"
#include "Layer.h"
#include "MyHeap.h"
//-------------------------------------------------------------

const int	LAYER_TOP			= -1;				// ȱʡɾ������LAYER�ı�־

////////////////////////////////////////////////////////////////////////
const int	MASK_SEARCHED		= 0x80;				// searched flag
const int	MASK_ROLECOUNT		= 0x7F;				// count of role
const int	MASK_MASK			= 0x0001;			// layer mask
const int	MASK_ALTITUDE		= 0xFFFE;			// layer alt
const int	MAX_IDXLAYER		= 0xFFFF;			// ���Ӳ�CELL����
const int	IDXLAYER_NONE		= USHORT(-1);
const int	DEFAULT_FLOORATTR	= 0;				// ȱʡ�ĵر�����
const int	ALTITUDE_LIMIT		= 32767;			// ���޸߶�(���ڷǷ��߶�)

#pragma pack(push)
#pragma pack(1)
class CCell
{
private:
//	DEQUE_LAYER m_setLayer;
//	bool        m_bSearched;
	USHORT		m_idxLayer;							// <= 65534, -1: invalid
	SHORT		m_nAlt2Mask;						// alt*2 and m_bMasked
	UCHAR		m_nCountFlag;					// rule count and m_bSearched
public:
	CCell(CLayer* pLayer);
	~CCell();
	static CCell*	CreateNew(CLayer* pLayer);
	bool	Create(int nAlt, DWORD dwMask);

	void    Destory();

public: // 
	ULONG	Release()							{ delete this; return 0; }
public:
	int		GetFloorAttr(DEQUE2_LAYER& set2Layer);
	DWORD	GetFloorMask(DEQUE2_LAYER& set2Layer);
	int		GetFloorAlt(DEQUE2_LAYER& set2Layer);
	int		GetSurfaceAlt();
	void	FullMask()							{ m_nAlt2Mask |= MASK_MASK; }
	//...
	void	IncRole(int nVal = 1)				{ if ((m_nCountFlag&MASK_ROLECOUNT)+nVal<=MASK_ROLECOUNT) m_nCountFlag = (m_nCountFlag&MASK_ROLECOUNT) + nVal; }
	void	DecRole(int nVal = 1)				{ if ((m_nCountFlag&MASK_ROLECOUNT)>=nVal) m_nCountFlag = (m_nCountFlag&MASK_ROLECOUNT) - nVal; }
	int		GetRoleAmount()						{ return (m_nCountFlag&MASK_ROLECOUNT); }

public:
	int             GetLayerAmount(DEQUE2_LAYER& set2Layer);                                    // �õ��������
	CLayer*         Getlayer(DEQUE2_LAYER& set2Layer, int nIndex);   	//�� ����ȡ��0��                             // ȡ�ò��

	void            AddLayer(DEQUE2_LAYER& set2Layer, CLayer* pLayer);                            // ��Ӳ��
	bool            DelLayer(DEQUE2_LAYER& set2Layer, int nIndex = LAYER_TOP);     //�� ����ɾ����0��                         // ɾ�����

//	BOOL            AddLogicLayer(CLayer* pLayer, CLayer* pBaseLayer);   // ����߼����
//	BOOL            DelLogicLayer(int nIndex);                           // ɾ���߼����

	BOOL            BeSearched(){return (m_nCountFlag&MASK_SEARCHED) != 0;}
	void            SetSearchFlag(bool bSearched){if(bSearched) m_nCountFlag |= MASK_SEARCHED; else m_nCountFlag &= (~MASK_SEARCHED);}

protected:
	MYHEAP_DECLARATION(s_heap)
};
#pragma pack(pop)






//-------------------------------------------------------------



#endif
