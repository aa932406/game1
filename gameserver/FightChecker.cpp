
#include "stdafx.h"
#include "FightChecker.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"

using namespace Answer;

#define TPOC_FIGHT_LEAVE_TIME		5000

CExtFightChecker::CExtFightChecker()
{
	OnCleanUp();
}

CExtFightChecker::~CExtFightChecker()
{
}

void CExtFightChecker::OnCleanUp()
{
	m_bIsInFight	= false;
	m_IsBuleName	= false;
	m_nFightTick	= 0;
	m_nBuleNameTick	= 0;
}


void CExtFightChecker::OnUpdate( int64_t curTick )
{
	CheckInFight( curTick );
}

bool CExtFightChecker::IsInFight() const
{
	return m_bIsInFight;
}

int8_t CExtFightChecker::GetFightState() const
{
	return m_bIsInFight ? 1 : 0;
}

void CExtFightChecker::SetInFight( int64_t nCurTick )
{
	m_nFightTick	= nCurTick;
}

void CExtFightChecker::CheckInFight( int64_t nCurTick )
{
	if ( nCurTick - m_nFightTick > 5000 )
	{
		if ( m_bIsInFight )
		{
			OnLeaveFight();
		}
	}
	else
	{
		if ( !m_bIsInFight )
		{
			OnEnterFight();
		}
	}
	
	if ( nCurTick - m_nBuleNameTick > 5000 )
	{
		if ( IsBuleName() )
		{
			ChangeBuleName( false );
		}
	}
}

void CExtFightChecker::OnLeaveFight()
{
#ifdef _DEBUG
	printf( "CExtFightChecker::OnLeaveFight()\n" );
#endif // _DEBUG
	m_bIsInFight = false;
	UpdateFightState();
	if ( NULL != m_pPlayer )
	{
		m_pPlayer->SetPPTick( m_pPlayer->getTick() );
	}
}

void CExtFightChecker::OnEnterFight()
{
#ifdef _DEBUG
	printf( "CExtFightChecker::OnEnterFight()\n" );
#endif // _DEBUG
	m_bIsInFight = true;
	UpdateFightState();
}

void CExtFightChecker::UpdateFightState()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int8_t connid = m_pPlayer->getConnId();
	NetPacket* inPacket = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, SM_UPDATE_FIGHT_STATE );
	if ( NULL == inPacket )
	{
		return;
	}

	inPacket->writeInt64( m_pPlayer->getCid() );
	inPacket->writeInt8( GetFightState() );
	inPacket->setSize( inPacket->getWOffset() );
	
	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap )
	{
		GAME_SERVICE.sendPacketTo( connid, m_pPlayer->getGateIndex(), inPacket );
	}
	else
	{
		pMap->broadcast( inPacket );
	}
}

void CExtFightChecker::ChangeBuleName( bool bFlag )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( bFlag != m_IsBuleName )
	{
		m_nBuleNameTick = m_pPlayer->getTick(); 
		m_IsBuleName = bFlag;
		m_pPlayer->setNeedSyncSelf();
		m_pPlayer->setSyncStatusFlag();
	}
}

bool CExtFightChecker::IsBuleName()
{
	return m_IsBuleName;
}

