///////////////////////////////////////////////////////////
//
//		CMsgDataArray.h
//

#ifndef		_MSGDATAARRAY_H_
#define		_MSGDATAARRAY_H_

#include "NetMsg.h"

enum
{
	_DATAARRAY_ACTION_MEDAL				=	0,	//	unsigned char	// ѫ��
	_DATAARRAY_ACTION_HONORTITLE		=	1,	//	unsigned char	// �ƺ�
	//---jinggy---2004-11-9---����ϵͳ---begin
	_DATAARRAY_ACTION_UPGRADE_QUALITY		=2,//����װ��Ʒ��	
	_DATAARRAY_ACTION_UPGRADE_SUPERADDITION	=3,//����װ��׷��	
	_DATAARRAY_ACTION_UPGRADE_EQUIPLEVEL	=4,//����װ���ȼ�
	_DATAARRAY_ACTION_EMBEDGEM				=5,//��װ��Ƕ�뱦ʯ
	//---jinggy---2004-11-9---����ϵͳ---end

	//---jinggy---����ϵͳ---begin
	_DATAARRAY_ACTION_SETSYN_DRESS	=50,	//���ð��ɷ�װ��һ���ĸ��ȼ��ķ�װ
	//---jinggy---����ϵͳ---end

	_DATAARRAY_SETITEMREBATE	=60,	//������Ʒ���ۿ�

	
};
#define MAX_LEVEL_SUPERADDITION	9	//ָ׷�����Ե���߼���

class CMsgDataArray : public CNetMsg
{
public:
	CMsgDataArray();
	virtual ~CMsgDataArray();

public:		//�ӿں���
	BOOL	Create(int nAction, int nAmount, char setChar[]);
	BOOL	Create(int nAction, int nAmount, short setShort[]);
	BOOL	Create(int nAction, int nAmount, long setLong[]);

protected:
	int RateSuccForQuality(CItemPtr pEquipItem);
	int RateSuccForGhostLevel(CItemPtr pEquipItem);
	//void SetSynDress(CUserPtr pUser);
public:
	bool Create(int nAction, int nAmount, unsigned long setULong[]);
	bool EmbedGemToEquip(CUserPtr pUser);
	bool UpEquipSuperAddition(CUserPtr pUser);
	bool UpEquipQuality(CUserPtr pUser);
	int RateSuccForEquipLevel(CItemPtr pEquipItem);
	bool UpEquipLevel(CUserPtr pUser);
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

private:
	typedef struct {
		MSGHEAD_DEFINE

		unsigned char ucAction;
		unsigned char ucAmount;
		union
		{
			unsigned char ucChar[1];			// �䳤
			char cChar[1];
			unsigned short usShort[1];
			short sShort[1];
			unsigned long dwLong[1];
			long nLong[1];
		};
	}MSG_Info;
	
	MSG_Info*	m_pInfo;
};

#endif