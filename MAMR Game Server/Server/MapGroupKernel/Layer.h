////////////////////////////////////////////
// Layer.h
///////////////////////////////////////////

#ifndef _LAYER_H
#define _LAYER_H

//-------------------------------------------------------------
// header files ...
#pragma	warning(disable:4786)
#include "BaseFunc.h"
#include "MyHeap.h"
#include <vector>
using namespace std;
//-------------------------------------------------------------

//-------------------------------------------------------------
// ���ڵر����� layer �ĸ߶�Ϊ 0
//-------------------------------------------------------------
class CLayer
{
public:
	unsigned short		nTerrian;       // ����(����)
	short				nAltitude;      // �߶ȣ����ػ�����ڵر�ĸ߶�
//	int					nHeight;        // layer�ĸ߶ȣ���ȣ�
	unsigned short		dwMask;         // �赲����

public:
	CLayer();
	virtual ~CLayer();
	static CLayer*	CreateNew() { return new CLayer; }

	MYHEAP_DECLARATION(s_heap)
};

#include <vector>
using namespace std;
typedef vector<CLayer* >  DEQUE_LAYER;
typedef vector<DEQUE_LAYER>  DEQUE2_LAYER;

//-------------------------------------------------------------
#endif
