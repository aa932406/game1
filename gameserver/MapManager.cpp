#include "stdafx.h"
#include "ActivityMap.h"
#include "CfgData.h"
#include "Dungeon.h"
#include "GameService.h"
//#include "Kingdom.h"
#include "Map.h"
#include "MapManager.h"
//#include "ActPKMap.h"
#include "PoolManager.h"

using namespace Answer; 
MapManager::MapManager()
	: m_DungenId( 1 )
{
	initRunner();
}

MapManager::~MapManager()
{

}

void MapManager::Init()
{
	initMap();
}

void MapManager::StartAll()
{
	for( int32_t i = 0; i < TPOC_MAP_RUNNER_SIZE; ++i )
	{
		m_Runner[i].Start();
	}
}

void MapManager::StopAll()
{
	for( int32_t i = 0; i < TPOC_MAP_RUNNER_SIZE; ++i )
	{
		m_Runner[i].Stop();
	}
}

void MapManager::initRunner()
{
	for( int32_t i = 0; i < TPOC_MAP_RUNNER_SIZE; ++i )
	{
		m_Runner[i].SetId( i + 1 );
	}
}

void MapManager::initMap()
{
	// �Ǹ�����ͼ
	const CfgMapTable &cfgAllMap = CFG_DATA.getMapAll();
	for ( CfgMapTable::const_iterator it = cfgAllMap.begin(); it != cfgAllMap.end(); ++it )
	{
		const CfgMap& mapInfo = it->second;
		int32_t nRunnerId = mapInfo.runnerId;
		if ( nRunnerId <= 0 || nRunnerId > TPOC_MAP_RUNNER_SIZE )
		{
			LOG_ERROR( "MapManager::initMap() runner id out of range, mapid=%d, runnerid=%d \n", mapInfo.id, nRunnerId );
			continue;
		}
		CMapRunner& runner = m_Runner[nRunnerId - 1];
		if ( mapInfo.isType( MT_ACTIVITY ) )
		{
			CActivityMap *pActivityMap = new CActivityMap();
			if ( pActivityMap != NULL )
			{
				pActivityMap->init( mapInfo );
				m_maps.insert( MapMap::value_type( pActivityMap->GetId(), pActivityMap ) );
				runner.AddMap( pActivityMap );
			}
		}
		else if ( mapInfo.isType( MT_NORMAL ) )
		{
			Map *pMap = new Map();
			if ( pMap != NULL )
			{
				pMap->init( mapInfo );
				m_maps.insert( MapMap::value_type( pMap->GetId(), pMap ) );
				runner.AddMap( pMap );
			}
		}
	}
}

Map* MapManager::GetMap( int32_t mapid )
{
	//if(actid >0)
	//{
	//	for (std::vector<Map*>::iterator it = m_maps.begin(); it != m_maps.end(); ++it)
	//	{
	//		ActivityMap *pMap = dynamic_cast<ActivityMap*>(*it);
	//		if (pMap!=NULL && pMap->getKingdomId() == kingdomid&&pMap->getActivityId() ==actid)
	//		{
	//			return pMap;
	//		}
	//	}
	//}
	//else
	//{
	//	for ( std::vector<Map*>::iterator it = m_maps.begin(); it != m_maps.end(); ++it)
	//	{
	//		Map *pMap = *it;
	//		if (pMap != NULL && pMap->GetId() == mapid)
	//		{
	//			return pMap;
	//		}
	//	}
	//}
	MapMap::iterator iter = m_maps.find( mapid );
	if ( iter != m_maps.end() )
	{
		return iter->second;
	}

	LOG_DUNGEON( "MapManager::GetMap() is faile id = %d\n",mapid );
	return NULL;
}

void MapManager::AddDungeon( Dungeon *pDungeon )
{
	if ( NULL == pDungeon )
	{
		return;
	}

	Answer::MutexGuard lock( m_mapLock );
	m_dungeons.insert( DungeonMap::value_type( pDungeon->GetId(), pDungeon ) );
}

Dungeon* MapManager::NewDungeon( int32_t nDungenId )
{
	Dungeon* pDungeon = NULL;
	CfgDungeon *pCfgDungeon = CFG_DATA.getDungeon( nDungenId );
	if ( pCfgDungeon != NULL )
	{
		CfgMap *pCfgMap = CFG_DATA.getMap( pCfgDungeon->mapid );
		if ( pCfgMap != NULL )
		{
			pDungeon = POOL_MANAGER.pop<Dungeon>();
			if ( pDungeon != NULL )
			{
				int32_t nId = newDungenId();
				pDungeon->init( *pCfgDungeon, *pCfgMap, nId );
			}
		}
	}
	return pDungeon;
}

void MapManager::DelDungeon( int32_t nId )
{
	Dungeon* pDungeon = NULL;
	{
		Answer::MutexGuard lock( m_mapLock );
		DungeonMap::iterator iter = m_dungeons.find( nId );
		if ( iter != m_dungeons.end() )
		{
			pDungeon = iter->second;
			m_dungeons.erase( iter );
		}
	}
	if ( pDungeon != NULL )
	{
		POOL_MANAGER.push<Dungeon>( pDungeon );
	}
}

void MapManager::PostMsg( int32_t nRunnerId, GameMsgCode msgcode, void *ptr1, void *ptr2, int32_t iparam1, int32_t iparam2,void *ptr3 )
{
	if ( nRunnerId <= 0 || nRunnerId > TPOC_MAP_RUNNER_SIZE )
	{
		LOG_ERROR( "MapManager::PostMessage() runner id out of range, msgcode=%d, runnerid=%d \n", msgcode, nRunnerId );
		return;
	}

	CMapRunner& runner = m_Runner[nRunnerId - 1];
	runner.PostMsg( msgcode, ptr1, ptr2, iparam1, iparam2, ptr3 );
}

int32_t MapManager::newDungenId()
{
	Answer::MutexGuard lock( m_mapLock );
	return m_DungenId++;
}

void MapManager::ResetMapMonster()
{
	Answer::MutexGuard lock( m_mapLock );
	for ( MapMap::iterator iter = m_maps.begin(); iter != m_maps.end(); ++iter )
	{
		Map* pMap = iter->second;
		if ( pMap != NULL )
		{
			pMap->ResetRefreshMonster();
		}
	}
}

