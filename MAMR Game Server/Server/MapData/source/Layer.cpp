///////////////////////////////////////
// Layer.cpp
///////////////////////////////////////
#pragma warning(disable:4786)
#include "windows.h"
#include "layer.h"

MYHEAP_IMPLEMENTATION(CLayer,s_heap);

//--------------------------------------------------------------
CLayer::CLayer()
{
	nTerrian = 0;
	nAltitude = 0;
	dwMask = 0;
//	nHeight = 0;
}

//-------------------------------------

CLayer::~CLayer()
{}

//-------------------------------------

