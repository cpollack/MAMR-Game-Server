////////////////////////////////////////////////////////////////////////////////////////////////////
// �����SOCKET�ü���ģ��
////////////////////////////////////////////////////////////////////////////////////////////////////
// �ɽ���, 2001.10.26
// �޸�Ϊģ�壺2001.12.11

#ifndef	ENCRYPTSERVER_HEAD
#define ENCRYPTSERVER_HEAD

////////////////////////////////////////////////////////////////////////////////////////////////////
// 3�������, �������ط����INI�е�SERVER KEY������
#define		aa	0x7E
#define		bb	0x33
#define		cc	0xA1

////////////////////////////////////////////////////////////////////////////////////////////////////
template <unsigned long key1, unsigned long key2>
class	CEncryptServer
{
public:
	CEncryptServer(){ Init(); }
//default	CEncryptServer(CEncryptServer & cEncrypt);
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

		/*
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
			}catch(...){ /*LOGCATCH("Encrypt init fail.");*/ }
		}
//	protected:
		unsigned char m_bufEncrypt1[256];
		unsigned char m_bufEncrypt2[256];
	}m_cGlobalEncrypt;
};

//template <unsigned long key1, unsigned long key2>
//CEncryptServer<key1, key2>::CEncryptCode	CEncryptServer<key1, key2>::m_cGlobalEncrypt;


template <unsigned long key1, unsigned long key2>
inline void CEncryptServer<key1, key2>::Encrypt(unsigned char * bufMsg, int nLen, bool bMove /*= true*/)
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
	}catch(...){ /*LOGCATCH("Encrypt fail.");*/ }
}

template <unsigned long key1, unsigned long key2>
inline void CEncryptServer<key1, key2>::ChangeCode(DWORD dwData)
{
	try{
		DWORD	dwData2 = dwData*dwData;
		for(int i = 0; i < 256; i += 4)
		{
			*(DWORD*)(&m_cGlobalEncrypt.m_bufEncrypt1[i]) ^= dwData;
			*(DWORD*)(&m_cGlobalEncrypt.m_bufEncrypt2[i]) ^= dwData2;
		}
	}catch(...){ /*LOGCATCH("ChangeCode fail.");*/ }
}


#endif	// ENCRYPTSERVER_HEAD
