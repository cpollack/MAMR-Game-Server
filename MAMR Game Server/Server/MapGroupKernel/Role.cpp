// Role.cpp: implementation of the CRole class.
//
//////////////////////////////////////////////////////////////////////

#include "Role.h"
#include "StatusOnce.h"
#include "StatusMore.h"
#include "Network/MsgAction.h"
#include "User.h"
#include "MapGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRole::CRole()
	: m_setStatus(NULL)
{
	m_idProcess		= ID_NONE;
	m_pMap			= NULL;
	m_nPosX			= 0;	//DEFAULT_LOGIN_POSX;
	m_nPosY			= 0;	//DEFAULT_LOGIN_POSY;
	m_nDir			= 0;
	
}

CRole::~CRole()
{
	// �ɸ������ഴ���ģ���ô���ɸ������ฺ���ͷţ�����ֻ���ظ�����������ڴ�й©
	ASSERT(!m_setStatus);
	SAFE_RELEASE (m_setStatus);
}

//////////////////////////////////////////////////////////////////////
bool CRole::IsInFan(POINT pos, POINT posSource, int nRange, int nWidth, POINT posCenter)
{
	CHECKF(nWidth > 0 && nWidth < 360);
	
	if(posCenter.x == GetPosX() && posCenter.y == GetPosY())
		return false;
	if(pos.x == posSource.x && pos.y == posSource.y)
		return false;
	
	if(GetDistance(pos.x, pos.y) > nRange)
		return false;
	
	float PI = static_cast<float>(3.1415926535);
	float fRadianDelta	= (PI * nWidth / 180) / 2;
	float fCenterLine	= GetRadian(GetPosX(), GetPosY(), posCenter.x, posCenter.y);
	float fTargetLine	= GetRadian(posSource.x, posSource.y, pos.x, pos.y);
	float fDelta	= fabs(fCenterLine - fTargetLine);
	if(fDelta <= fRadianDelta || fDelta >= 2*PI - fRadianDelta)
		return true;
	
	return false;
}

//////////////////////////////////////////////////////////////////////
int	 CRole::AdjustDataEx(int nData, int nAdjust, int nMaxData/*=0*/)
{
	if(nAdjust>=ADJUST_PERCENT)
		return MulDiv(nData, nAdjust-ADJUST_PERCENT, 100);
	
	if(nAdjust<=ADJUST_SET)
		return -1*nAdjust + ADJUST_SET;
	
	if(nAdjust==ADJUST_FULL)
	{
		ASSERT(nMaxData != 0);
		return nMaxData;
	}
	
	return nData + nAdjust;
}


//////////////////////////////////////////////////////////////////////
bool CRole::AttachStatus(IRole* pRole, int nStatus, int nPower, int nSecs, int nTimes)
{
	CGameMap* pMap = pRole->GetMap();
	IF_NOT (pMap)
		return false;

	if (STATUS_CRIME == nStatus 
			&& (pMap->IsPkField() || pMap->IsSynMap() || pMap->IsDeadIsland()))
		return false;

	// ������� -- �Բ���״̬����
	if (pRole->QueryStatus(STATUS_TEAMCLEAN))
	{
		// Ŀǰ���ݽ������״̬��ħ����ֻ�������ֲ���״̬��������µĲ���״̬��������Ҫͬʱ�޸�����
		if (CRole::IsBadlyStatus(nStatus))
			return false;
	}

	IStatus* pStatus = pRole->QueryStatus(nStatus);
	if(pStatus)
	{
		// ħ��״̬�滻�¹��� ���� 2005-04-21
		bool bChangeData = false;
		if (pStatus->GetPower() == nPower)	// power��ͬ��ֱ���滻
		{
			bChangeData = true;
		}
		else
		{
			int nMinPower = __min(nPower, pStatus->GetPower());
			int nMaxPower = __max(nPower, pStatus->GetPower());

			if (nPower <= ADJUST_SET)
			{
				// ��power <= -30000��һ���滻
				bChangeData = true;
			}
			else
			{
				// �����power����-30000����ֻ�о�powerҲ����-30000����Ҫ�����滻
				if (pStatus->GetPower() > ADJUST_SET)
				{
					// �¾�powerͬΪ�ٷֱȻ��߾�����ֵ���ſ������滻
					if (nMinPower >= ADJUST_PERCENT || nMaxPower < ADJUST_PERCENT)
					{
						if (nMinPower >= ADJUST_PERCENT+100 || nMinPower > 0 && nMaxPower < ADJUST_PERCENT)
						{
							// ��Ϊ��Ӱ���ʱ��ȡpower���״̬
							if (nPower > pStatus->GetPower())
								bChangeData = true;
						}
						else if (nMaxPower < 0 || nMinPower > ADJUST_PERCENT && nMaxPower < ADJUST_PERCENT+100)
						{
							// ��Ϊ��Ӱ���ʱ��ȡpowerС��״̬
							if (nPower < pStatus->GetPower())
								bChangeData = true;
						}
					}
				}
			}
		}

		if (bChangeData)
			pStatus->ChangeData(nPower, nSecs, nTimes);
		return true;
	}
	else
	{
		// ���״̬���������
		if (nStatus >= STATUS_TEAM_BEGIN && nStatus <= STATUS_TEAM_END)
		{
			for (int i=STATUS_TEAM_BEGIN; i<=STATUS_TEAM_END; i++)
				pRole->QueryStatusSet()->DelObj(i);
		}

		if(nTimes)		// ��δ�����״̬
		{
			CStatusMore*	pNewStatus = CStatusMore::CreateNew();
			IF_OK(pNewStatus)
			{
				IF_OK(pNewStatus->Create(pRole, nStatus, nPower, nSecs, nTimes))
				{
					pRole->QueryStatusSet()->AddObj(pNewStatus->QueryInterface());
					pRole->SetStatus(nStatus, SYNCHRO_TRUE);
					return true;
				}
				else
					pNewStatus->ReleaseByOwner();
			}
		}
		else
		{
			CStatusOnce*	pNewStatus = CStatusOnce::CreateNew();
			IF_OK(pNewStatus)
			{
				IF_OK(pNewStatus->Create(pRole, nStatus, nPower, nSecs))
				{
					pRole->QueryStatusSet()->AddObj(pNewStatus->QueryInterface());
					pRole->SetStatus(nStatus, SYNCHRO_TRUE);
					return true;
				}
				else
					pNewStatus->ReleaseByOwner();
			}
		}

	}

	return false;
}

//////////////////////////////////////////////////////////////////////
void CRole::DetachWellStatus(IRole* pRole)
{
	CHECK(pRole);

	for(int i = pRole->QueryStatusSet()->GetAmount() - 1; i >= 0; i--)
	{
		IStatus* pStatus =  pRole->QueryStatusSet()->GetObjByIndex(i);
		if(pStatus && pStatus->GetID() != STATUS_CRIME)
		{
			if (CRole::IsWellStatus(pStatus->GetID()))
				pRole->QueryStatusSet()->DelObj(pStatus->GetID());
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CRole::DetachBadlyStatus(IRole* pRole)
{
	CHECK(pRole);

	for(int i =  pRole->QueryStatusSet()->GetAmount() - 1; i >= 0; i--)
	{
		IStatus* pStatus =  pRole->QueryStatusSet()->GetObjByIndex(i);
		if(pStatus && pStatus->GetID() != STATUS_CRIME)
		{
			if (CRole::IsBadlyStatus(pStatus->GetID()))
				pRole->QueryStatusSet()->DelObj(pStatus->GetID());
		}
	}
}

//////////////////////////////////////////////////////////////////////
bool CRole::IsWellStatus(int nStatus)
{
	switch (nStatus)
	{
	case	STATUS_DEFENCE1:
	case	STATUS_DEFENCE2:
	case	STATUS_DEFENCE3:
	case	STATUS_ATTACK:
	case	STATUS_MAGICDEFENCE:
	case	STATUS_REFLECT:
	case	STATUS_REFLECTMAGIC:
	case	STATUS_MAGICDAMAGE:
	case	STATUS_ATKSPEED:
	case	STATUS_LURKER:
		return true;
		break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CRole::IsBadlyStatus(int nStatus)
{
	switch (nStatus)
	{
	case	STATUS_POISON:
	case	STATUS_FREEZE:
	case	STATUS_SMOKE:
	case	STATUS_DARKNESS:
	case	STATUS_PALSY:
	case	STATUS_SLOWDOWN2:
	case	STATUS_SYNCRIME:
		return true;
		break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
bool CRole::DetachStatus(IRole* pRole, int nStatus)
{
	CHECKF(pRole);

	for(int i =  pRole->QueryStatusSet()->GetAmount() - 1; i >= 0; i--)
	{
		IStatus* pStatus =  pRole->QueryStatusSet()->GetObjByIndex(i);
		if(pStatus && pStatus->GetID() == nStatus)
		{
			 pRole->QueryStatusSet()->DelObj(pStatus->GetID());
			 return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
void CRole::DetachAllStatus(IRole* pRole)
{
	CHECK(pRole);

	for(int i =  pRole->QueryStatusSet()->GetAmount() - 1; i >= 0; i--)
	{
		IStatus* pStatus =  pRole->QueryStatusSet()->GetObjByIndex(i);
		if(pStatus && pStatus->GetID() != STATUS_CRIME)
			 pRole->QueryStatusSet()->DelObj(pStatus->GetID());
	}
}

//////////////////////////////////////////////////////////////////////
// ����������˲�Ƶ�����
void CRole::ActiveTransPos(int nPosX, int nPosY)
{
	if (!GetMap() || !GetMap()->IsStandEnable(nPosX, nPosY))
		return;

	this->ClrAttackTarget();
	
	CUser* pUser = NULL;
	if (this->QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		pUser->StopMine();
		pUser->DestroyBooth();
	}

	ProcessOnMove(MOVEMODE_SYNCHRO);
	TransPos(nPosX,nPosY) ;			
	CMsgAction	msg;
	if(msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionTransPos, GetPosX(), GetPosY()))
		SendMsg(&msg);

	return;
}

//////////////////////////////////////////////////////////////////////
bool CRole::MoveToward(int nDir, bool bSync)
{
	m_nDir	= nDir%8;
	int	nDirX	= _DELTA_X[m_nDir];
	int	nDirY	= _DELTA_Y[m_nDir];
	
	CMapPtr pMap = this->GetMap();
	CHECKF(pMap);

	int nNewPosX = GetPosX() + nDirX;
	int nNewPosY = GetPosY() + nDirY;
	IF_NOT(GetMap()->IsValidPoint(nNewPosX, nNewPosY))
		return false;

	CUser* pUser = NULL;
	if(GetMap() && !GetMap()->IsStandEnable(nNewPosX, nNewPosY) 
		&& this->QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		SendSysMsg(STR_INVALID_COORDINATE);
//		MSGBUF	szMsg;
//		sprintf(szMsg, "���[%s]�ߵ��Ƿ�����[%d,%d,%d]��", GetName(), GetMapID(), nNewPosX, nNewPosY);
		//		::GmLogSave(szMsg);
		pUser->KickBack();
		//UserManager()->KickOutSocket(GetSocketID(), szMsg);
		return false;
	}

	CRole::DetachStatus(this, STATUS_HIDDEN);

	pMap->MoveTo(this, nNewPosX, nNewPosY, WITH_BLOCK, WITH_BLOCK);
	if (pUser)
	{
		pUser->StandRestart();
		pMap->ChangeRegion(pUser, nNewPosX, nNewPosY);
	}
	m_nPosX = nNewPosX;
	m_nPosY = nNewPosY;

	// ����MapThing	-- !!!����Ҳ��Ҫ����
	{
/*
		int x,y,z;
		IRole*	pRole = NULL;
		FOR_9_BLOCKTHINGS(pMap, GetPosX(), GetPosY())
		{
			IMapThing* pTarget = pMap->QueryThingByIndex(x,y,z);
			if(pTarget)
			{
				int	nDistX	= (pTarget->GetPosX() - this->GetPosX()) * nDirX;			// ǰ�����Ϊ������Ϊ����
				int	nDistY	= (pTarget->GetPosY() - this->GetPosY()) * nDirY;			// ǰ�����Ϊ������Ϊ����
				if(nDirX && nDistX == CELLS_PER_VIEW || nDirY && nDistY == CELLS_PER_VIEW)
				{
					pTarget->SendShow(this);
					//				this->SendSysMsg("����");//@
					
					if(bSync && pTarget->QueryRole(IPP_OF(pRole)))		// �������ǽ�ɫ
						this->SendShow(pRole);
				}
			}
		}
*/
	}
	if (bSync)
		UpdateBroadcastSet();

	ProcessAfterMove();
	return true;
}

//////////////////////////////////////////////////////////////////////
void CRole::TransPos(int nPosX, int nPosY)
{
	if(nPosX == GetPosX() && nPosY == GetPosY())
		return;

	CMapPtr pMap = this->GetMap();
	IF_NOT(pMap && pMap->IsValidPoint(nPosX, nPosY))
		return;

	CUser* pUser = NULL;
	if(GetMap() && !GetMap()->IsStandEnable(nPosX, nPosY)
		&& this->QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		SendSysMsg(STR_INVALID_COORDINATE);
		MSGBUF	szMsg;
		sprintf(szMsg, "Player[%s] flew to illegal coordinates[%d, %d, %d].", GetName(), GetMap()->GetID(), nPosX, nPosY);
		::GmLogSave(szMsg);
		pUser->KickBack();
		//UserManager()->KickOutSocket(GetSocketID(), szMsg);
		return ;
	}

	CRole::DetachStatus(this, STATUS_HIDDEN);

	pMap->MoveTo(this, nPosX, nPosY, WITH_BLOCK, WITH_BLOCK);
	if (pUser)
	{
		pUser->StandRestart();
		pMap->ChangeRegion(pUser, nPosX, nPosY);
	}
	m_nPosX = nPosX;
	m_nPosY = nPosY;

	// �������
//	if (IsSendBlockInfo())
//		pMap->SendBlockInfo(this);
//	SendSelfToBlock();

	//Blocks don't change, so I don't think we need to clear and update BCset on move
	//ClrBroadcastSet();
	//UpdateBroadcastSet();
	
	ProcessAfterMove();
}

//////////////////////////////////////////////////////////////////////
void CRole::JumpPos(int nPosX, int nPosY)
{
	if(nPosX == GetPosX() && nPosY == GetPosY())
		return;
	
	CMapPtr pMap = this->GetMap();
	IF_NOT(pMap) return;
	//IF_NOT(pMap && pMap->IsValidPoint(nPosX, nPosY)) //Mapdata isnt loaded yet?
	//	return;

	CUser* pUser = NULL;
	if (this->QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		//We don't use blocks
		//int	nDeltaX	= abs(nPosX - m_nPosX);
		//int	nDeltaY	= abs(nPosY - m_nPosY);
		
		// ������
		//if(nDeltaX > CELLS_PER_BLOCK || nDeltaY > CELLS_PER_BLOCK)
		//{
			//		::GmLogSave("���[%s]���ľ���Ƿ�[%d][%d]��", GetName(), nDeltaX, nDeltaY);
		//	return ;
		//}
		//if(!pMap->IsStandEnable(nPosX, nPosY))
		//{
		//	SendSysMsg(STR_INVALID_COORDINATE);
//			MSGBUF	szMsg;
//			sprintf(szMsg, "���[%s]�����Ƿ�����[%d,%d,%d]��", GetName(), GetMapID(), nPosX, nPosY);
//			::GmLogSave(szMsg);
		//	pUser->KickBack();
			//UserManager()->KickOutSocket(GetSocketID(), szMsg);
			//return ;
		//}
	}

	CRole::DetachStatus(this, STATUS_HIDDEN);

	pMap->MoveTo(this, nPosX, nPosY, WITH_BLOCK, WITH_BLOCK);
	if (pUser)
	{
		pUser->StandRestart();
		pMap->ChangeRegion(pUser, nPosX, nPosY);
	}
	int	nOldX	= m_nPosX;
	int	nOldY	= m_nPosY;
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	
	// �������
/*
	int x,y,z;
	IRole*	pRole = NULL;
	FOR_9_BLOCKTHINGS(pMap, GetPosX(), GetPosY())
	{
		IMapThing* pTarget = pMap->QueryThingByIndex(x,y,z);
		CUser* pTargetUser = NULL;
		if(pTarget && 
			(pUser													// ��ң�һ��Ҫ��
			|| pTarget->QueryObj(OBJ_USER, IPP_OF(pTargetUser))))	// ����ң����ڿ�����Ҳŷ�
		{
			if(abs(pTarget->GetPosX() - nOldX) > CELLS_PER_VIEW  
				&& abs(pTarget->GetPosX() - this->GetPosX()) <= CELLS_PER_VIEW
				|| abs(pTarget->GetPosY() - nOldY) > CELLS_PER_VIEW 
				&& abs(pTarget->GetPosY() - this->GetPosY()) <= CELLS_PER_VIEW )
			{
				pTarget->SendShow(this);
				//				this->SendSysMsg("����");//@

				if(pTarget->QueryRole(IPP_OF(pRole)))
					this->SendShow(pRole);
			}
		}
	}
*/

	//Blocks don't change, so I don't think we need to clear and update BCset on move
	//ClrBroadcastSet();
	//UpdateBroadcastSet();
	
	ProcessAfterMove();
}

//////////////////////////////////////////////////////////////////////
bool CRole::SyncTrackTo(int nPosX, int nPosY, int nDir, DWORD dwAction)
{
	m_nDir	= nDir%8;
	
	if (GetPosX() != nPosX || GetPosY() != nPosY)
	{
		CMapPtr pMap = this->GetMap();
		IF_NOT(pMap && pMap->IsValidPoint(nPosX, nPosY))
			return false;
		
		if(GetMap() && !GetMap()->IsStandEnable(nPosX, nPosY))
		{
			//SendSysMsg(STR_INVALID_COORDINATE);
			//::LogSave("Invalid coordinate (%d, %d)", nPosX, nPosY);
			return false;
		}
		
		CRole::DetachStatus(this, STATUS_HIDDEN);
		
		pMap->MoveTo(this, nPosX, nPosY, WITH_BLOCK, WITH_BLOCK);
		CUser* pUser = NULL;
		if (this->QueryObj(OBJ_USER, IPP_OF(pUser)))
		{
			pUser->StandRestart();
			pMap->ChangeRegion(pUser, nPosX, nPosY);
		}

//		int	nOldX	= m_nPosX;
//		int	nOldY	= m_nPosY;
		m_nPosX	= nPosX;
		m_nPosY	= nPosY;

/*
		int x,y,z;
		IRole*	pRole = NULL;
		FOR_9_BLOCKTHINGS(pMap, GetPosX(), GetPosY())
		{
			IMapThing* pTarget = pMap->QueryThingByIndex(x,y,z);
			CUser* pTargetUser = NULL;
			if(pTarget && 
				(pUser													// ��ң�һ��Ҫ��
				|| pTarget->QueryObj(OBJ_USER, IPP_OF(pTargetUser))))	// ����ң����ڿ�����Ҳŷ�
			{
				if(abs(pTarget->GetPosX() - nOldX) > CELLS_PER_VIEW  
					&& abs(pTarget->GetPosX() - this->GetPosX()) <= CELLS_PER_VIEW
					|| abs(pTarget->GetPosY() - nOldY) > CELLS_PER_VIEW 
					&& abs(pTarget->GetPosY() - this->GetPosY()) <= CELLS_PER_VIEW )
				{
					pTarget->SendShow(this);

					if(pTarget->QueryRole(IPP_OF(pRole)))		// �������ǽ�ɫ
						this->SendShow(pRole);
				}
			}
		}
*/
	}

	UpdateBroadcastSet();

	//	ProcessAfterMove();
	
	// ͬ���켣
	CMsgAction	msg;
	IF_OK (msg.Create(GetID(), GetPosX(), GetPosY(), GetDir(), actionMagicTrack, dwAction))
		BroadcastRoomMsg(&msg, true);
	
	return true;
}

//////////////////////////////////////////////////////////////////////
ELEMENTINTERACTION CRole::GetElementInteraction(CRole* pRole) {
	if(!pRole) {
		ASSERT("Bad CRole pointer");
		return INTERACTION_NONE;
	}

	if (GetObjType() == OBJ_USER) return INTERACTION_NONE;

	int opposingElem = pRole->GetElement();

	ELEMENTINTERACTION interaction = INTERACTION_NONE;
	switch (this->GetElement()) {
	case ELEMENT_WATER:
		switch (opposingElem) {
		case ELEMENT_WATER:
			interaction = INTERACTION_NONE;
			break;
		case ELEMENT_FIRE:
			interaction = INTERACTION_RESTRAINED;
			break;
		case ELEMENT_METAL:
			interaction = INTERACTION_GENERATE;
			break;
		case ELEMENT_WOOD:
			interaction = INTERACTION_GENERATED;
			break;
		case ELEMENT_EARTH:
			interaction = INTERACTION_RESTRAIN;
			break;
		}
		break;
	case ELEMENT_FIRE:
		switch (opposingElem) {
		case ELEMENT_WATER:
			interaction = INTERACTION_RESTRAIN;
			break;
		case ELEMENT_FIRE:
			interaction = INTERACTION_NONE;
			break;
		case ELEMENT_METAL:
			interaction = INTERACTION_RESTRAINED;
			break;
		case ELEMENT_WOOD:
			interaction = INTERACTION_GENERATE;
			break;
		case ELEMENT_EARTH:
			interaction = INTERACTION_GENERATED;
			break;
		}
		break;
	case ELEMENT_METAL:
		switch (opposingElem) {
		case ELEMENT_WATER:
			interaction = INTERACTION_GENERATED;
			break;
		case ELEMENT_FIRE:
			interaction = INTERACTION_RESTRAIN;
			break;
		case ELEMENT_METAL:
			interaction = INTERACTION_NONE;
			break;
		case ELEMENT_WOOD:
			interaction = INTERACTION_RESTRAINED;
			break;
		case ELEMENT_EARTH:
			interaction = INTERACTION_GENERATE;
			break;
		}
		break;
	case ELEMENT_WOOD:
		switch (opposingElem) {
		case ELEMENT_WATER:
			interaction = INTERACTION_GENERATE;
			break;
		case ELEMENT_FIRE:
			interaction = INTERACTION_GENERATED;
			break;
		case ELEMENT_METAL:
			interaction = INTERACTION_RESTRAIN;
			break;
		case ELEMENT_WOOD:
			interaction = INTERACTION_NONE;
			break;
		case ELEMENT_EARTH:
			interaction = INTERACTION_RESTRAINED;
			break;
		}
		break;
	case ELEMENT_EARTH:
		switch (opposingElem) {
		case ELEMENT_WATER:
			interaction = INTERACTION_RESTRAINED;
			break;
		case ELEMENT_FIRE:
			interaction = INTERACTION_GENERATE;
			break;
		case ELEMENT_METAL:
			interaction = INTERACTION_GENERATED;
			break;
		case ELEMENT_WOOD:
			interaction = INTERACTION_RESTRAIN;
			break;
		case ELEMENT_EARTH:
			interaction = INTERACTION_NONE;
			break;
		}
		break;
	}

	if (interaction == INTERACTION_RESTRAIN) {
		if (IsSuper() && pRole->IsUnevo()) interaction = INTERACTION_SUPER_RESTRAIN;
	}
	if (interaction == INTERACTION_RESTRAINED) {
		if (IsUnevo() && pRole->IsSuper()) interaction = INTERACTION_SUPER_RESTRAINED;
	}

	return interaction;
}

//////////////////////////////////////////////////////////////////////
bool CRole::UpdateBroadcastSet(bool bClearSet/*=false*/)
{
	CHECKF (GetMap());
	CUser* pUser = NULL;
	QueryObj(OBJ_USER, IPP_OF(pUser));

	bool	bIsCallPet = false;
	CAiNpc* pMonster;
	//if (QueryObj(OBJ_MONSTER, IPP_OF(pMonster)))
	//{
	//	if (pMonster->IsCallPet() || pMonster->IsEudemon())
	//		bIsCallPet = true;
	//}

	// Ѱ���µ�Ŀ�꼯
	typedef std::vector<IRole*>		ROLE_SET;
	ROLE_SET		setNewRole;
	BROADCAST_SET	setNewMapItem;
	int x,y,z;
	IRole*	pRole = NULL;

	IThingSet* pSet = GetMap()->BlockByIndex(0, 0).QuerySet();
	for (int i = 0; i < pSet->GetAmount(); i++)
	{
		IMapThing* pTarget = pSet->GetObjByIndex(i);
		if(!pTarget)
			continue;
			
		//if (abs(pTarget->GetPosX() - GetPosX()) <= CELLS_PER_VIEW
		//	&& abs(pTarget->GetPosY() - GetPosY()) <= CELLS_PER_VIEW)
		//{
			if (pTarget->QueryRole(IPP_OF(pRole)))
			{
				CUser* pTargetUser = NULL;
				if (pRole->GetID() != this->GetID()
					&& (bIsCallPet || pUser || pTarget->QueryObj(OBJ_USER, IPP_OF(pTargetUser))
						|| (pTarget->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)) 
								&& pMonster->IsCallPet())))
				{
					// �Լ�����ҡ����ޣ�����Ŀ������ҡ�����
					setNewRole.push_back(pRole);
				}
			}
			else if (pUser)	// ��ͼ�ϵ���Ʒ����Ҫ����NPC������
			{
				setNewMapItem.push_back(pTarget->GetID());
			}
		//}
	}

	// ���ԭ��Ŀ�꼯 ���� ������������Ŀ��
//	if (bClearSet)
//	{
//		m_setBCRole.clear();
//		m_setBCMapItem.clear();
//	}
//	else
	{
		// ����ԭĿ�꼯��ɾ��������Ŀ�꼯�е�id��ѹ����ɾ������
		// ͬʱҲɾ����Ŀ�꼯��ԭ���Ѿ����ڵ�id
		BROADCAST_SET::iterator it = m_setBCRole.begin();
		for (; it!=m_setBCRole.end(); )
		{
			OBJID id = *it;
			bool  bMatch = false;
			ROLE_SET::iterator iter = setNewRole.begin();
			for (; iter!=setNewRole.end(); iter++)
			{
				IRole* pRole = *iter;
				if (pRole && pRole->GetID() == id)
				{
					bMatch = true;
					setNewRole.erase(iter);
					break;
				}
			}
			BROADCAST_SET::iterator itErase = it;
			++it;
			if (!bMatch)
			{
				m_setBCRole.erase(itErase);

				// ֪ͨ�Լ��Է���ʧ
				RemoveFromBCRoleSet(id);

				// ֪ͨ�Է��Լ���ʧ
				IRole* pRole = RoleManager()->QueryRole(id);
				if (pRole)
					pRole->RemoveFromBCRoleSet(this->GetID());
			}
		}
		for (it=m_setBCMapItem.begin(); it!=m_setBCMapItem.end(); )
		{
			OBJID id = *it;
			bool bMatch = false;
			BROADCAST_SET::iterator iter = setNewMapItem.begin();
			for (; iter!=setNewMapItem.end(); iter++)
			{
				if (id == *iter)
				{
					bMatch = true;
					setNewMapItem.erase(iter);
					break;
				}
			}
			BROADCAST_SET::iterator itErase = it;
			++it;
			if (!bMatch)
			{
				m_setBCMapItem.erase(itErase);

				RemoveFromBCMapItemSet(id);
			}
		}
	}

	// ���������¾�Ŀ�꼯�ϲ�
	CUser* pTargetUser = NULL;
	if (!setNewRole.empty())
	{
		ROLE_SET::iterator it=setNewRole.begin();
		for (; it!=setNewRole.end(); it++)
		{
			IRole* pRole = *it;
			if (pRole)
			{
				// ���Է������Լ���Ŀ�꼯��ͬʱҲ���Լ�����Է�Ŀ�꼯
				// �Լ�����ң������Լ���NPC�ҶԷ�����һ���޵�ʱ�����Ҫ����
				bool bSendSelf = (pUser ||
								(!bIsCallPet && (pRole->QueryObj(OBJ_USER, IPP_OF(pTargetUser)))
													|| (pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster))
															&& pMonster->IsCallPet())));
				//AddToBCRoleSet(pRole->GetID(), bSendSelf);
				AddToBCRoleSet(pRole->GetID(), false);

				// �Է����ǻ��ޣ��ң��Լ�����һ���޻��߶Է�����ҵ�ʱ�����Ҫ����
				pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster));
				bool bSendTarget = ((!pMonster || !pMonster->IsCallPet())
										&& (pUser || bIsCallPet || pRole->QueryObj(OBJ_USER, IPP_OF(pTargetUser))));
				//pRole->AddToBCRoleSet(GetID(), bSendTarget);
				pRole->AddToBCRoleSet(GetID(), false);
			}
		}
	}
	if (!setNewMapItem.empty())
	{
		BROADCAST_SET::iterator it=setNewMapItem.begin();
		for (; it!=setNewMapItem.end(); it++)
		{
			AddToBCMapItemSet(*it);
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
void CRole::ClrBroadcastSet()
{
	BROADCAST_SET::iterator it = m_setBCRole.begin();
	for (; it!=m_setBCRole.end(); it++)
	{
		OBJID id = *it;
		// ֪ͨ�Է��Լ���ʧ
		IRole* pRole = RoleManager()->QueryRole(id);
		if (pRole)
			pRole->RemoveFromBCRoleSet(this->GetID());		
	}
	m_setBCRole.clear();

	m_setBCMapItem.clear();
}

//////////////////////////////////////////////////////////////////////
void CRole::AddToBCRoleSet(OBJID idRole, bool bSendMsg)
{
	BROADCAST_SET::iterator it=m_setBCRole.begin();
	for (; it!=m_setBCRole.end(); it++)
	{
		if (idRole == *it)
			return;
	}
	m_setBCRole.push_back(idRole);
	if (bSendMsg)
	{
		IRole* pRole =  RoleManager()->QueryRole(idRole);
		if (pRole)
		{
			pRole->QueryMapThing()->SendShow((IRole*)this);
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CRole::RemoveFromBCRoleSet(OBJID idRole)
{
	//NPC������������ʱ���ģ�����ֻ��֪ͨ�ͻ������
	CUser* pUser = NULL;
	if (QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		// ֪ͨ�Լ��Է���ʧ
		CMsgAction msg;
		if (msg.Create(idRole, 0, 0, 0, actionDisappear, 0))
			SendMsg(&msg);
	}

	BROADCAST_SET::iterator it=m_setBCRole.begin();
	for (; it!=m_setBCRole.end(); it++)
	{
		if (idRole == *it)
		{
			m_setBCRole.erase(it);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CRole::AddToBCMapItemSet(OBJID idMapItem)
{
	/*BROADCAST_SET::iterator it=m_setBCMapItem.begin();
	for (; it!=m_setBCMapItem.end(); it++)
	{
		if (idMapItem == *it)
			return;
	}
	m_setBCMapItem.push_back(idMapItem);
	CMapItem* pMapItem = MapManager()->QueryMapItem(idMapItem);
	if (pMapItem)
	{
		pMapItem->QueryMapThing()->SendShow(this);
	}*/
}

//////////////////////////////////////////////////////////////////////
void CRole::RemoveFromBCMapItemSet(OBJID idMapItem)
{
	//NPC������������ʱ���ģ�����ֻ��֪ͨ�ͻ���
	CUser* pUser = NULL;
	if (QueryObj(OBJ_USER, IPP_OF(pUser)))
	{
		CMsgAction msg;
		if (msg.Create(idMapItem, 0, 0, 0, actionDisappear, 1))
			SendMsg(&msg);
	}

	BROADCAST_SET::iterator it=m_setBCMapItem.begin();
	for (; it!=m_setBCMapItem.end(); it++)
	{
		if (idMapItem == *it)
		{
			m_setBCMapItem.erase(it);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
void CRole::BroadcastRoomMsg(CNetMsg* pMsg, bool bSendSelf)
{
	CHECK(pMsg);
	CGameMap* pMap = GetMap();
	CHECK (pMap);

	CUser*	pUser		= NULL;
	IRole*	pRole		= NULL;
	CAiNpc* pMonster	= NULL;
	bool bSendToNpc	= (QueryObj(OBJ_USER, IPP_OF(pUser))
						|| (QueryObj(OBJ_MONSTER, IPP_OF(pMonster)) && pMonster->IsCallPet())
						|| bSendSelf);

	if (pMap->IsNewbieMap() && bSendSelf)
	{
		SendMsg(pMsg);
		return;
	}

	if (bSendSelf)
		m_setBCRole.push_back(this->GetID());
	DEBUG_TRY
	BROADCAST_SET::iterator it=m_setBCRole.begin();
	for (; it!=m_setBCRole.end(); it++)
	{
		OBJID idRole = *it;
		IRole* pRole = RoleManager()->QueryRole(idRole);
		if (pRole)
		{
			if (pRole->QueryObj(OBJ_MONSTER, IPP_OF(pMonster)) && bSendToNpc)
			{
				if (!pMonster->IsCallPet())
				{
					pRole->SendMsg(pMsg);
					bSendToNpc = false;
				}
			}
			if (pRole->QueryObj(OBJ_USER, IPP_OF(pUser)))
			{
				pRole->SendMsg(pMsg);
				if (pUser->IsAgent() && bSendToNpc)
					bSendToNpc = false;
			}
		}
	}
	DEBUG_CATCH("CRole::BroadcastRoomMsg")
	if (bSendSelf)
		m_setBCRole.pop_back();
}
