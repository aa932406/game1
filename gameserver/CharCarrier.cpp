#include "stdafx.h"

#include "CharCarrier.h"
#include "ObjCarrier.h"
#include "Player.h"
#include "CfgData.h"
#include "PoolManager.h"

using namespace Answer;

CExtCharCarrier::CExtCharCarrier()
: CExtSystemBase()
{
	m_pCarrier = NULL;
}

CExtCharCarrier::~CExtCharCarrier()
{
}

void CExtCharCarrier::OnCleanUp()
{
	if ( m_pCarrier )
	{
		POOL_MANAGER.push( m_pCarrier );
		m_pCarrier = NULL;
	}
}

void CExtCharCarrier::OnUpdate( int64_t curTick )
{
	if ( m_pCarrier )
	{
		m_pCarrier->Unit::update();
	}
}

void CExtCharCarrier::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_LEAVE_CARRIER );
}

int32_t CExtCharCarrier::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( !inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( nProcId == CM_LEAVE_CARRIER )
	{
		return onLeaveCarrier( inPacket );
	}
	return 0;
}

int32_t CExtCharCarrier::onLeaveCarrier( Answer::NetPacket *inPacket )
{
	if ( !m_pPlayer || !inPacket || !m_pCarrier )
	{
		return ERR_INVALID_DATA;
	}
	LeaveCarrier();
	return ERR_OK;
}

void CExtCharCarrier::EnterCarrier( int32_t nId )
{
	if ( !m_pPlayer )
		return;

	const CfgCarrierTable* pCarrierTable = CFG_DATA.GetCarrierTable();
	const CfgCarrier* pCfgCarrier = pCarrierTable->GetCarrier( nId );
	if ( !pCfgCarrier )
		return;

	if ( m_pCarrier )
	{
		LeaveCarrier();
	}

	m_pCarrier = POOL_MANAGER.pop<CObjCarrier>();
	if ( m_pCarrier )
	{
		m_pCarrier->Init( m_pPlayer, nId );
		m_pPlayer->clearDebuff( 0 );
		m_pPlayer->setNeedSyncSelf();
		m_pPlayer->SetNeedSyncAround();
	}
}

void CExtCharCarrier::LeaveCarrier()
{
	if ( !m_pPlayer )
		return;

	if ( m_pCarrier )
	{
		POOL_MANAGER.push( m_pCarrier );
		m_pCarrier = NULL;
		m_pPlayer->setNeedSyncSelf();
		m_pPlayer->SetNeedSyncAround();
	}
}

int32_t CExtCharCarrier::GetCarrierId() const
{
	if ( m_pCarrier )
		return m_pCarrier->GetCarrierId();
	return 0;
}

bool CExtCharCarrier::HaveSkill( int32_t nSkillId ) const
{
	return m_pPlayer && m_pCarrier && m_pCarrier->HaveSkill( nSkillId );
}
