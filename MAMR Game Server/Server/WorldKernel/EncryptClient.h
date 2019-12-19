////////////////////////////////////////////////////////////////////////////////////////////////////
// �ͻ���SOCKET�ü���ģ��
////////////////////////////////////////////////////////////////////////////////////////////////////
// �ɽ���, 2001.10.26
// �޸�Ϊģ�壺2001.12.11

#ifndef	ENCRYPTCLIENT_H
#define ENCRYPTCLIENT_H

#include <stdlib.h>
#include "logfile.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1, 
					unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
class	CEncryptClient
{
public:
	CEncryptClient(){ Init(); }
//default	CEncryptClient(CEncryptClient & cEncrypt);
public:
	void Init() { m_nPos1 = m_nPos2 = 0; m_cGlobalEncrypt.Init(); }
	void Encrypt(unsigned char * bufMsg, int nLen, bool bMove = true);
	void ChangeCode(DWORD dwData);
protected:
	int		m_nPos1;
	int		m_nPos2;
protected:
	class	CEncryptCode
	{
	public:
		CEncryptCode() { Init(); }
		void Init()
		{
			try{
		/*
				// ���� ABC
				int	a1, b1, c1, fst1;
				a1		= ((key1 >> 0) & 0xFF) ^ aa;
				b1		= ((key1 >> 8) & 0xFF) ^ bb;
				c1		= ((key1 >> 24) & 0xFF) ^ cc;
				fst1	= (key1 >> 16) & 0xFF;

				int	a2, b2, c2, fst2;
				a2		= ((key2 >> 0) & 0xFF) ^ aa;
				b2		= ((key2 >> 8) & 0xFF) ^ bb;
				c2		= ((key2 >> 24) & 0xFF) ^ cc;
				fst2	= (key2 >> 16) & 0xFF;

				unsigned char	nCode = fst1;
				for(int i = 0; i < 256; i++)
				{
					m_cGlobalEncrypt.m_bufEncrypt1[i] = nCode;
					int	nTemp = a1*512;
					nCode = (nTemp*128 + c1 + b1*256) % 256;
				}
				assert(nCode == fst1);

					nCode = fst2;
				for( i = 0; i < 256; i++)
				{
					m_cGlobalEncrypt.m_bufEncrypt2[i] = nCode;
					int	nTemp = a2*1024;
					nCode = ((b2<<8) + nTemp*64 + c2) & 0xFF;
				}
				assert(nCode == fst2);
		//*/
		//*else
				unsigned char	nCode = fst1;
				for(int i = 0; i < 256; i++)
				{
					m_bufEncrypt1[i] = nCode;
		//			printf("%02X ", nCode);		//???
					nCode = (a1*nCode*nCode + b1*nCode + c1) % 256;
				}
		//		printf("[%02X]\n", nCode);		//???
				assert(nCode == fst1);

					nCode = fst2;
				for(int i = 0; i < 256; i++)
				{
					m_bufEncrypt2[i] = nCode;
					nCode = (a2*nCode*nCode + b2*nCode + c2) % 256;
				}
				assert(nCode == fst2);
		//*/
			}catch(...){ LOGCATCH("Encrypt init fail."); }
		}
//	protected:
		unsigned char m_bufEncrypt1[256];
		unsigned char m_bufEncrypt2[256];
	}m_cGlobalEncrypt;		//??? Ӧ�ĳɾ�̬����ĳ�Ա�����Խ�Լ��Դ
};

//template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1, 
//					unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
//CEncryptClient<a1, b1, c1, fst1, a2, b2, c2, fst2>::CEncryptCode	CEncryptClient<a1, b1, c1, fst1, a2, b2, c2, fst2>::m_cGlobalEncrypt;


template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1, 
					unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
inline void CEncryptClient<a1, b1, c1, fst1, a2, b2, c2, fst2>::Encrypt(unsigned char * bufMsg, int nLen, bool bMove /*= true*/)
{
	try{
		int		nOldPos1 = m_nPos1;
		int		nOldPos2 = m_nPos2;
		for(int i = 0; i < nLen; i++)
		{
			bufMsg[i] ^= m_cGlobalEncrypt.m_bufEncrypt1[m_nPos1];
			bufMsg[i] ^= m_cGlobalEncrypt.m_bufEncrypt2[m_nPos2];
			if(++m_nPos1 >= 256)
			{
				m_nPos1 = 0;
				if(++m_nPos2 >= 256)
					m_nPos2 = 0;
			}
			assert(m_nPos1 >=0 && m_nPos1 < 256);
			assert(m_nPos2 >=0 && m_nPos2 < 256);
		}

		if(!bMove)
		{
			// �ָ�ָ��
			m_nPos1 = nOldPos1;
			m_nPos2 = nOldPos2;
		}
	}catch(...){ LOGCATCH("Encrypt fail."); }
}

template <unsigned char a1, unsigned char b1, unsigned char c1, unsigned char fst1, 
					unsigned char a2, unsigned char b2, unsigned char c2, unsigned char fst2>
inline void CEncryptClient<a1, b1, c1, fst1, a2, b2, c2, fst2>::ChangeCode(DWORD dwData)
{
	try{
		DWORD	dwData2 = dwData*dwData;
		for(int i = 0; i < 256; i += 4)
		{
			*(DWORD*)(&m_cGlobalEncrypt.m_bufEncrypt1[i]) ^= dwData;
			*(DWORD*)(&m_cGlobalEncrypt.m_bufEncrypt2[i]) ^= dwData2;
		}
	}catch(...){ LOGCATCH("ChangeCode fail."); }
}



#endif	// ENCRYPTCLIENT_H
