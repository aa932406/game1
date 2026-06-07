#include "stdafx.h"
#include "CXinMaiMap.h"
#include "GameService.h"
#include "Player.h"
#include "Monster.h"
#include "Plant.h"
#include "Timer.h"
#include "CfgData.h"

using namespace Answer;

CXinMaiMap::CXinMaiMap( const CfgActivity& cfgActivity )
	: CActivity( cfgActivity )
	, m_pLastBoss( NULL )
	, m_LeftTime( 0 )
{
}

CXinMaiMap::~CXinMaiMap()
{
}

void CXinMaiMap::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
}

void CXinMaiMap::onPlayerKilled( Player* pDier, Player* pKiller )
{
	// empty override
}

bool CXinMaiMap::OnSitRevive( Player* player )
{
	if ( NULL == player )
	{
		return false;
	}

	int32_t& Time = m_ReviveTimes[player->getCid()];
	if ( Time < 0 )
	{
		return false;
	}

	if ( !player->DecCurrency( CURRENCY_GOLD, 100 * ( Time + 1 ), GCR_XIN_MAI_MAP_REVIVE, 0 ) )
	{
		return false;
	}

	++Time;
	CActivity::OnSitRevive( player );
	return true;
}

int32_t CXinMaiMap::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	if ( NULL != player && NULL != pTargetMap )
	{
		return CActivity::canEnter( player, pTargetMap );
	}
	return ERR_INVALID_DATA;
}

void CXinMaiMap::reset()
{
	m_MonsterActivityMap.clear();
	m_pLastBoss = NULL;
	m_LeftTime = 0;
	m_ReviveTimes.clear();
	CActivity::reset();
}

void CXinMaiMap::addPlayer( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	if ( player->getFamilyId() <= 0 )
	{
		player->setPkMode( 6, 0 );
	}
	else
	{
		player->setPkMode( 3, 0 );
	}

	CActivity::addPlayer( player );
}

void CXinMaiMap::removePlayer( Player* player, bool islogout )
{
	CActivity::removePlayer( player, islogout );
}

void CXinMaiMap::sendPlayerScore( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	int32_t Count = 0;
	std::map<int64_t, int32_t>::iterator iter = m_ReviveTimes.find( player->getCid() );
	if ( iter != m_ReviveTimes.end() )
	{
		Count = iter->second;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), Answer::Answer::PACK_DISPATCH, 0x2E24 );

	if ( NULL != packet )
	{
		packet->writeInt32( m_cfgActivity.id );
		packet->writeInt32( Count );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
	}
}

void CXinMaiMap::onTimeEnd()
{
	m_nState = AS_END;
	CActivity::delayKickAll( 0 );
}

void CXinMaiMap::broadcastReady()
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::Answer::PACK_DISPATCH, 0x2CD6 );
	if ( NULL != packet )
	{
		packet->writeInt32( 491 );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( packet );
	}
}

void CXinMaiMap::broadcastStart()
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::Answer::PACK_DISPATCH, 0x2CD6 );
	if ( NULL != packet )
	{
		packet->writeInt32( 492 );
		packet->writeInt32( GetId() );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( packet );
	}
}

void CXinMaiMap::onMonsterAdd( MonsterActivity* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}

	if ( pMonster->isAlive() && pMonster->getBossSign() == 14 )
	{
		m_pLastBoss = pMonster;
		m_LeftTime = 0;
		setNeedBroadcastActivityScore();
	}
	else
	{
		m_MonsterActivityMap[pMonster->getId()] = pMonster;
	}
}

int32_t CXinMaiMap::onBeginGather( Plant* plant, Player* player )
{
	if ( NULL == plant || NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	if ( player->getRecord( 2101 ) > 10 )
	{
		return ERR_NO;
	}

	return ERR_OK;
}

void CXinMaiMap::onPlantGather( Plant* pPlant, Player* player )
{
	if ( NULL != pPlant && NULL != player )
	{
		player->GetOperateLimit().AddLimitCount( 2101, 1 );
	}
}

bool CXinMaiMap::alwaysShowIcon()
{
	int32_t ServerDiffDay = CFG_DATA.getServerDiffDay( 0 ); // SVT_NORMAL = 0
	return ServerDiffDay >= 0 && ServerDiffDay < 30;

}

void CXinMaiMap::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
	if ( NULL == pMonster || NULL == pKiller )
	{
		return;
	}

	if ( pMonster->getBossSign() != 14 )
	{
		bool IsAllDie = true;

		for ( std::map<int64_t, MonsterActivity*>::iterator it = m_MonsterActivityMap.begin();
				it != m_MonsterActivityMap.end(); ++it )
		{
			MonsterActivity* pActivityMonster = it->second;
			if ( NULL != pActivityMonster && pActivityMonster->isAlive() )
			{
				IsAllDie = false;
				break;
			}
		}

		if ( IsAllDie )
		{
			m_LeftTime = pKiller->getNow() + 180;
		}
	}

	setNeedBroadcastActivityScore();
}
