//////////////////////////////////////////////////////////////////////////
//author :zxj			modify Time:2012 -7-7
//description:地图数据类
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_ROBOT_MAP_H__
#define __TPOC_ROBOT_MAP_H__

#include <vector>

#include "CfgData.h"
#include "Tile.h"
#include "Unit.h"

#define AREA_WIDTH			600			// 区域宽
#define AREA_HEIGHT			400			// 区域高
#define AREA_VIEW_SIZE		1			// 视野 2x+1


class Map
{
public:
	Map();
	virtual ~Map();

public:
	static Position pixelToTile(int32_t px, int32_t py);
	static Position tileToPixel(int32_t tx, int32_t ty);
	static Direction pixelDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty);
	static Direction tileDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty);
	static Position getAroundTile(int32_t tx, int32_t ty, Direction direction);

public:
	void init( const CfgMap &cfgmap );//地图数据初始化
	void update();
	
public:
	int32_t GetId() const;
	int32_t GetType() const;
	int32_t getAntiProtect() const;
	int32_t GetWidthTileCount() const;
	int32_t GetHeightTileCount() const;
	int32_t getReive() const;
	int32_t getHideMini() const;
	//*可以去除

	Tile* getTile(int32_t tx, int32_t ty);
	//void checkAreaChange( Unit *pUnit, const Position& oldPos );
	bool isWalkablePosition( int32_t tx, int32_t ty );
	bool inSafeRegion(const Position &pos);
	bool inRegion(const Position &pos, const CfgMapRegion &region);
	Position getRandomWalkablePosition();
	Position getRandomWalkablePositionInRegion(const CfgMapRegion &region);
	Position getRandomWalkableAroundPosition(int32_t tx, int32_t ty);

	bool AddMonster( Monster* pMonster );
	void getAreaMonsters( const Position& center, int32_t nArea, UnitList& outUnits );

	Monster*	GetNearestAliveMonster( const Position& pos, int32_t mid = 0 );
	Monster*	GetRandomAliveMonster();

	Position	firstLinePosition(Position src, Position dest);
	Monster*	getMonster( EntityId_t nId );
	Monster*	getMonsterByMid( int32_t nMid );

private:
	//bool		inAreas(Unit *pUnit, const PositionVector &areas);
	bool		checkPos( const Position& pos, const Position& area ) const;

	Position	getAreaByPos( const Position& pos );
	int32_t		getViewAreaCount( int32_t nSize = AREA_VIEW_SIZE ) const;
	void		getViewAreas( const Position& pos, PositionVector& outAreas, int32_t nSize = AREA_VIEW_SIZE );
	void		getNewAreas( const Position& oldPos, const Position& newPos, PositionVector& outAreas, int32_t nSize = AREA_VIEW_SIZE );
	//void		getAreaUnits( const PositionVector& areas, UnitList& outUnits );

	int32_t		xAddHalfY( int32_t x, int32_t y );
	int32_t		xSubHalfY( int32_t x, int32_t y );

protected:
	CfgMap		m_cfgmap;

	int32_t		m_widthTileCount;
	int32_t		m_heightTileCount;

	int32_t		m_widthAreaCount;
	int32_t		m_heightAreaCount;

	//PlayerList	m_players;
	MonsterList m_monsters;
	//NpcList		m_npcs;
	//DropItemGroupList m_dropItems;
	//PlantList	m_plants;
	//TrailerList m_trailers;
	//ObjPetList	m_pets;
	int32_t		m_lastUpdateTime;
};

#endif	//__TPOC_ROBOT_MAP_H__
