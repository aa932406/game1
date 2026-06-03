#include "stdafx.h"
#include "CfgData.h"
#include "Map.h"
#include "MapManager.h"

using namespace Answer; 
MapManager::MapManager()
{
}

MapManager::~MapManager()
{

}

void MapManager::Init()
{
	initMap();
}

void MapManager::initMap()
{
	const CfgMapTable &cfgAllMap = CFG_DATA.getMapAll();
	for ( CfgMapTable::const_iterator it = cfgAllMap.begin(); it != cfgAllMap.end(); ++it )
	{
		const CfgMap& mapInfo = it->second;
		if ( ( mapInfo.type & MT_NORMAL ) != 0 )
		{
			Map *pMap = new Map();
			if ( pMap != NULL )
			{
				pMap->init( mapInfo );
				m_maps.insert( MapMap::value_type( pMap->GetId(), pMap ) );
			}
		};
	}
}

Map* MapManager::GetMap( int32_t mapid )
{
	MapMap::iterator iter = m_maps.find( mapid );
	if ( iter != m_maps.end() )
	{
		return iter->second;
	}

	LOG_DUNGEON( "MapManager::GetMap() is faile id = %d\n",mapid );
	return NULL;
}
