// ���ݿ��¼�ļ���ͨ������CGameData����
// �ɽ��ޣ�2004.1.7
//////////////////////////////////////////////////////////////////////

#ifndef	T_GAMEDATAMAP_H
#define T_GAMEDATAMAP_H

#include "Define.h"
#include "basefunc.h"
#include "logfile.h"
#include "I_mydb.h"
#include "Myheap.h"
#include "T_SingleMap.h"

template	< class T >
class CGameDataMap : public CSingleMap<T>
{
public:
	static CGameDataMap<T>*	CreateNew(bool bOwner=true) { return new CGameDataMap<T>(bOwner); }
	bool		Create(LPCTSTR szSQL, IDatabase* pDb);
private:
	CGameDataMap(bool bOwner) : CSingleMap<T>(bOwner)		{}
};

//////////////////////////////////////////////////////////////////////
// �˺�����Ҫ���ݿ�֧��
template<class T>
bool CGameDataMap<T>::Create(LPCTSTR szSQL, IDatabase* pDb)
{
	IRecordset* pRes = pDb->CreateNewRecordset(szSQL, false);
	if(!pRes)
		return false;

	for(int i = 0; i < pRes->RecordCount(); i++)
	{
		T* pData = T::CreateNew();
		if(!pData)
		{
			pRes->Release();
			return false;
		}

		if(!pData->Create(pRes))
		{
			pData->ReleaseByOwner();
			pRes->Release();
			return false;
		}

		this->AddObj(pData);

		pRes->MoveNext();
	}

	pRes->Release();
	return true;
}


#endif // T_GAMEDATAMAP_H
