// AiCenter.cpp: implementation of the CAiCenter class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>

const int	FACT_ID_FIRST				= 1000000;			// ����ǰ���ΪTEMP_FACT��ID������FactQueue��
//////////////////////////////////////////////////////////////////////
inline char*	SystemFunction(int idx)
{
	static char*	g_setSysFunc[]={
		// debug or operator
		"dump",					// for debug, dump this rule
		"keep",					// (int), only for change mode, keep(0) for keep fact forever
		// function
		"now",					// (int), ��ǰʱ��
		"less",					// (left,right), �����left < right������ȷ
		"less_equ",				// (left,right), �����left <= right������ȷ
		"strstr",				// (str,substr), ���str�а������Ӵ�substr����ȷ
		"percent",				// (int), 0 ~ 100, ��n%�Ļ���ΪTRUE��

		NULL
	};

	CHECKF(idx < sizeof(g_setSysFunc));
	return g_setSysFunc[idx];
}

enum {
		SYS_FUNC_DUMP,			// "dump",					// for debug, dump this rule
		SYS_FUNC_KEEP,			// "keep",					// (int), only for change mode, keep(0) for keep fact forever

		SYS_FUNC_NOW,			// "now",					// (int), ��ǰʱ��
		SYS_FUNC_LESS,			// "less",					// (left,right), �����left < right������ȷ
		SYS_FUNC_LESS_EQU,		// "less_equ",				// (left,right), �����left <= right������ȷ
		SYS_FUNC_STRSTR,		// "strstr",				// (str,substr), ���str�а������Ӵ�substr����ȷ
		SYS_FUNC_PERCENT,		// "percent",				// (int), 0 ~ 100, ��n%�Ļ���ΪTRUE��
};