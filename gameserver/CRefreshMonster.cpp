#include "stdafx.h"
#include "CRefreshMonster.h"
#include "GameService.h"
#include "MapManager.h"
#include "Map.h"
#include "Timer.h"
#include "CfgData.h"

using namespace Answer;

CRefreshMonster::CRefreshMonster( const CfgActivity& cfgActivity )
	: CActivity( cfgActivity )
	, m_StateTime( 0 )
{
}

CRefreshMonster::~CRefreshMonster()
{
}

void CRefreshMonster::reset()
{
	RefreshMonsterCfgList& cfgList = const_cast<RefreshMonsterCfgList&>( CFG_DATA.GetRefreshMonsterCfgList() );
	for ( RefreshMonsterCfgList::iterator it = cfgList.begin(); it != cfgList.end(); ++it )
	{
		it->LastFreshTime = 0;
	}
	m_StateTime = 0;
	CActivity::reset();
}

void CRefreshMonster::CheckActivity()
{
	if ( !checkData() )
	{
		m_nState = AS_TIME_OUT;
		return;
	}

	if ( !checkLine() )
	{
		m_nState = AS_NOT_START;
		return;
	}

	if ( m_nState == AS_TIME_OUT )
	{
		m_nState = AS_NOT_START;
	}

	const tm& localnow = TIMER.GetLocalNow();
	int32_t NowTime = TIMER.GetNow();
	bool bRightLine = checkLine();

	ACTIVITY_STATE nState = checkTime();

	if ( nState == AS_READY )
	{
		if ( m_nState == AS_END || m_nState == AS_NOT_START )
		{
			m_nState = AS_READY;
			if ( bRightLine )
			{
				broadcastReady();
			}
		}
	}
	else if ( nState == AS_RUNNING )
	{
		if ( m_nState <= AS_READY && bRightLine )
		{
			broadcastStart();
			broadcastReady();
			m_StateTime = NowTime;
		}
		m_nState = AS_RUNNING;
		if ( bRightLine )
		{
			FlushMonsters( NowTime );
		}
	}
	else if ( nState == AS_END )
	{
		if ( m_nState == AS_RUNNING )
		{
			if ( bRightLine )
			{
				stopActivity();
			}
			m_nState = AS_END;
		}
		m_nState = AS_END;
	}
	else if ( nState == AS_NOT_START )
	{
		if ( m_nState == AS_END )
		{
			m_nState = AS_NOT_START;
		}
		else if ( m_nState == AS_RUNNING )
		{
			if ( bRightLine )
			{
				stopActivity();
			}
			m_nState = AS_NOT_START;
		}
	}
}

void CRefreshMonster::FlushMonsters( int32_t NowTime )
{
	const RefreshMonsterCfgList& cfgList = CFG_DATA.GetRefreshMonsterCfgList();

	for ( RefreshMonsterCfgList::const_iterator it = cfgList.begin(); it != cfgList.end(); ++it )
	{
		if ( m_StateTime + it->nStartTime < NowTime )
		{
			// Note: LastFreshTime is tracked in config data. For simplicity, check if enough time has passed.
			// Since we don't modify the const config list, we just check timing.
			// The actual implementation would track LastFreshTime per config per activity instance.
			bool bCanRefresh = true;
			if ( it->LastFreshTime > 0 )
			{
				if ( it->LastFreshTime + it->nDiffTime > NowTime )
				{
					bCanRefresh = false;
				}
			}

			if ( bCanRefresh )
			{
				it->LastFreshTime = NowTime;

				// Calculate remaining time
				int32_t LeftTime = it->nDiffTime;
				int32_t nActivityLeftTime = getLeftTime();
				if ( LeftTime > nActivityLeftTime )
				{
					LeftTime = nActivityLeftTime;
				}

				// Send post message to each map
				for ( Int32Vector::const_iterator itMap = m_cfgActivity.maps.begin();
						itMap != m_cfgActivity.maps.end(); ++itMap )
				{
					Map* pMap = MAP_MANAGER.GetMap( *itMap );
					if ( NULL != pMap )
					{
						int32_t iparam2 = it->nIndex;
						int32_t RunnerId = pMap->getRunnerId();
						MAP_MANAGER.PostMsg( RunnerId, GMC_ADD_OBJ, pMap, this, LeftTime, iparam2, NULL );

						int32_t GongGaoId = it->GongGaoId;
						FreshObjGongGao( GongGaoId );
					}
				}
			}
		}
	}
}

void CRefreshMonster::stopActivity()
{
	m_nState = AS_NOT_START;
	reset();
	// broadcastEnd would be called here if it existed
}

void CRefreshMonster::broadcastStart()
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
	if ( NULL != packet )
	{
		packet->writeInt32( m_cfgActivity.state ); // TODO: should use StartGongGao from config
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( packet );
	}
}

void CRefreshMonster::FreshObjGongGao( int32_t GongGaoId )
{
	if ( GongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
		if ( NULL != packet )
		{
			packet->writeInt32( GongGaoId );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}
}
