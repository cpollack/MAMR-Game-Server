// ���ݿ��¼�ļ���ͨ������CGameData����
// �ɽ��ޣ�2004.1.19
//////////////////////////////////////////////////////////////////////

#ifndef	T_GAMEDATASET_H
#define T_GAMEDATASET_H

#include "../Server/share/Define.h"
#include "../Common/BaseFunc.h"
#include "../Common/logfile.h"
#include "I_mydb.h"
#include "../Common/Myheap.h"
#include "../Common/T_SingleMap.h"

template	< class T >
class CGameDataSet : public CGameObjSet<T>
{
public:
	static CGameDataSet<T>*	CreateNew(bool bOwner=true) { return new CGameDataSet<T>(bOwner); }
	bool		Create(LPCTSTR szSQL, IDatabase* pDb);
private:
	CGameDataSet(bool bOwner) : CGameObjSet<T>(bOwner)		{}
};

//////////////////////////////////////////////////////////////////////
// �˺�����Ҫ���ݿ�֧��
template<class T>
bool CGameDataSet<T>::Create(LPCTSTR szSQL, IDatabase* pDb)
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


#endif // T_GAMEDATASET_H
