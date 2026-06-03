#ifndef __TPOC_ROBOT_MAP_MANAGER_H__
#define __TPOC_ROBOT_MAP_MANAGER_H__

#include "Map.h"

class MapManager
{
typedef std::map<int32_t, Map*>	MapMap;		
public:
	MapManager();
	~MapManager();

public:
	void		Init();
	Map*		GetMap( int32_t mapid );

private:
	void		initMap();

private:
	MapMap		m_maps;
};
#define MAP_MANAGER Answer::Singleton<MapManager>::instance()

#endif	//__TPOC_ROBOT_MAP_MANAGER_H__
