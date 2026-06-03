#pragma once

//class Kingdom;
class CActivityMap;
class Dungeon;
class Map;
//class ActDungeonMap;
//class ActMatchkingDom;
//class ActPKMap;
//class actMatchBase;
//typedef std::vector<ActDungeonMap*> actDungeonVector;
//typedef std::vector<ActPKMap*> pkMapVector;

#include "MapRunner.h"
#define TPOC_MAP_RUNNER_SIZE	5

class MapManager
{
typedef std::map<int32_t, Map*>	MapMap;		
typedef std::map<int32_t, Dungeon*> DungeonMap;
typedef std::map<int32_t, CActivityMap*> ActivityMapMap;

public:
	MapManager();
	~MapManager();

public:
	void		Init();
	void		StartAll();
	void		StopAll();

	Map*		GetMap( int32_t mapid );
	void		AddDungeon( Dungeon *pDungeon );
	Dungeon*	NewDungeon( int32_t nDungeonId );
	void		DelDungeon( int32_t nId );
	void		PostMsg( int32_t nRunnerId, GameMsgCode msgcode, void *ptr1=NULL, void *ptr2=NULL, int32_t iparam1=0, int32_t iparam2=0,void *ptr3=NULL );

private:
	void		initRunner();
	void		initMap();
	int32_t		newDungenId();

private:
	MapMap			m_maps;
	DungeonMap		m_dungeons;
	ActivityMapMap	m_activitys;
	int32_t			m_DungenId;

	CMapRunner		m_Runner[TPOC_MAP_RUNNER_SIZE];
	Answer::Mutex   m_mapLock;
};
#define MAP_MANAGER Answer::Singleton<MapManager>::instance()
