// MsgBetOutside.h: interface for the CMsgAtk class.
// �ɽ��ޣ�2002.1.8
//////////////////////////////////////////////////////////////////////

#ifndef	MSGBETOUTSIDE_H
#define MSGBETOUTSIDE_H

#include "NetMsg.h"

enum
{
	_ACTION_CHIPIN				= 0,		//��ע  to server, to client
											//������עͨ�����Action�㲥ͬ��
											//�¼���ľֵ���Ҳͨ�����Actionȡ��Ͷע�б�
											//dwDataΪͶ�˶���Ǯ��ucTypeΪͶ����ע
											// exclude self, �Լ�ͨ��_ACTION_CHIPIN_CONFIRM ����
	_ACTION_CHIPIN_CONFIRM		= 1,		//��עȷ��// only to client
	_ACTION_CANCELCHIP			= 2,		//ȡ����עto server, to client
											//dwMoneyΪͶ�˶���Ǯ��ucTypeΪͶ����ע
											// exclude self, �Լ�ͨ��_ACTION_CANCELCHIP_CONFIRM ����
	_ACTION_CANCELCHIP_CONFIRM	= 3,		//�˳���עȷ��// only to client
	_ACTION_BEGINCHIP			= 4,		//��ʼ��ע // to client ����ʱ	// ucTime is leave secs
	_ACTION_ENDCHIP				= 5,		//������ // to client ����ʱ5S
	_ACTION_DICE				= 6,		//������Ϣ // to client ����ʱ5S // MsgName�㲥ӮǮ��Ϣ
};

class CMsgBODice : public CNetMsg
{
public:
	CMsgBODice();
	virtual ~CMsgBODice();

	BOOL	Create (int nAction, OBJID idNpc, int nTime=0);
	BOOL	Append (int nType, DWORD dwData);
	BOOL	Create (int nAction, OBJID idNpc, char aDice[4]);

public:	
	BOOL			Create		(char* pMsgBuf, DWORD dwSize);
	void			Process		(CGameSocket* pSocket);

protected:
	typedef struct {
		MSGHEAD_DEFINE

		unsigned char	ucAction;
		union
		{
			unsigned char	ucTime;		// ������ע��ʼ�˶�� // use for _ACTION_BEGINCHIP
			unsigned char	ucAmount;
		};
		OBJID			idDiceNpc;
		struct
		{
			unsigned char	ucType;
			union
			{
				DWORD			dwData;
				unsigned char	ucDice[4];
			};
		}Data[1];
	}MSG_Info;

	MSG_Info*	m_pInfo;
};






#endif // MSGBETOUTSIDE_H
