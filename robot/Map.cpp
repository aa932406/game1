#include "stdafx.h"
#include "Map.h"
#include "CfgData.h"
#include "PathFinder.h"

using namespace Answer;
using namespace std;

Map::Map()
{

}

Map::~Map()
{

}

Position Map::pixelToTile(int32_t px, int32_t py)
{
	int32_t tx = -1;
	int32_t ty = -1;

	int32_t rx = ((px>>6)<<6) + 32;
	int32_t ry = ((py>>5)<<5) + 16;

	if ( (abs(px-rx)<<4) + (abs(py-ry)<<5) < 32 * 16 ) //in the diamond..
	{
		tx = px >> 6;
		ty = ((py>>5)<<1);
	}
	else
	{
		tx = ((px-32)>>6) + 1;
		ty = (((py-16)>>5)<<1) + 1;
	}

	return Position(tx-(ty&1), ty);
}

Position Map::tileToPixel(int32_t tx, int32_t ty)
{
	int32_t px = (tx<<6)+32+((ty&1)<<5);
	int32_t py = (ty+1)<<4;
	return Position(px, py);
}

Direction Map::pixelDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty)
{
	double radians = atan2(static_cast<double>(ty-cy), static_cast<double>(tx-cx));
	double degrees = radians*180/PI;
	int direction = roundInt(degrees/45); //right as 0, down as 2, left as 4, up as 6...
	if (direction < 0)
	{
		direction += 8;
	}
	direction -= 2;
	if (direction < 0)
	{
		direction += 8;
	}

	Direction dir = static_cast<Direction>(direction);
	if (dir == INVALID_DIRECTION)
	{
		LOG_ERROR("Map::pixelDirection return INVALID_DIRECTION with cx = %d, cy = %d, tx = %d, ty = %d\n", cx, cy, tx, ty);
	}

	return dir;
}

Direction Map::tileDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty)
{
	if (cx < 0 || cy < 0 || tx < 0 || ty < 0)
	{
		return INVALID_DIRECTION;
	}

	if (cx == tx && cy == ty)
	{
		return INVALID_DIRECTION;
	}

	if (cx==tx && cy-ty>1)
	{
		return UP;
	}
	if (cx==tx && ty-cy>1)
	{
		return DOWN;
	}
	if (cy==ty && tx>cx)
	{
		return RIGHT;
	}
	if (cy==ty && tx<cx)
	{
		return LEFT;
	}

	if (ty > cy)
	{
		if (tx>=cx && (tx-cx)==((ty-cy+(cy&1))>>1))
		{
			return DOWN_RIGHT;
		}
		if (tx<=cx && (cx-tx)==((ty-cy+((cy+1)&1))>>1))
		{
			return DOWN_LEFT;
		}
	}
	else
	{
		if (tx>=cx && (tx-cx)==((cy-ty+(cy&1))>>1))
		{
			return UP_RIGHT;
		}
		if (tx<=cx && (cx-tx)==((cy-ty+((cy+1)&1))>>1))
		{
			return UP_LEFT;
		}
	}

	return INVALID_DIRECTION;
}

Position Map::getAroundTile(int32_t tx, int32_t ty, Direction direction)
{
	switch (direction)
	{
	case DOWN: return Position(tx, ty+2);
	case DOWN_LEFT: return Position(tx-1+(ty&1), ty+1);
	case LEFT: return Position(tx-1, ty);
	case UP_LEFT: return Position(tx-1+(ty&1), ty-1);
	case UP: return Position(tx, ty-2);
	case UP_RIGHT: return Position(tx+(ty&1), ty-1);
	case RIGHT: return Position(tx+1, ty);
	case DOWN_RIGHT: return Position(tx+(ty&1), ty+1);
	default: return Position(tx, ty);
	}
}

void Map::init( const CfgMap &cfgmap )
{
	m_cfgmap = cfgmap;
	m_widthTileCount = m_cfgmap.width/64;
	m_heightTileCount = roundInt(m_cfgmap.height/16.0);
	m_widthAreaCount = m_cfgmap.width/AREA_WIDTH+1;
	m_heightAreaCount = m_cfgmap.height/AREA_HEIGHT+1;
	m_lastUpdateTime = 0;

	//CfgMapMonsterVector *pMonsters = CFG_DATA.getMonstersOnMap(GetId());
	//if (pMonsters != NULL)
	//{
	//	for (CfgMapMonsterVector::iterator it = pMonsters->begin(); it != pMonsters->end(); ++it)
	//	{
	//		CfgMonster *pCfgMonster = CFG_DATA.getMonster(it->monsterid);
	//		if (pCfgMonster != NULL)
	//		{
	//			Monster *monster = new Monster;
	//			if (NULL == monster)
	//			{
	//				continue;
	//			}
	//			monster->init(*pCfgMonster, *it, NULL);
	//			if ( pCfgMonster->boss_sign == BOSS_TYPE_SPIDER_QUEEN || pCfgMonster->boss_sign == BOSS_TYPE_WORLD_BOSS )
	//			{
	//				if ( GAME_SERVICE.getLine() == 1 )
	//				{
	//					addMonster(monster, it->x, it->y);
	//				}
	//			}
	//			else
	//			{
	//				addMonster(monster, it->x, it->y);
	//			}
	//		}
	//	}
	//}

	//const CfgNpcTable &allNpc = CFG_DATA.getNpcAll();
	//for (CfgNpcTable::const_iterator it = allNpc.begin(); it != allNpc.end(); ++it)
	//{
	//	if (it->second.findMapId(GetId()) && it->second.x > 0 && it->second.y > 0)
	//	{
	//		Npc *npc = new Npc;
	//		if (NULL == npc)
	//		{
	//			continue;
	//		}
	//		npc->init(it->second);
	//		addNpc(npc, it->second.x, it->second.y);		
	//	}
	//}

	//CfgMapPlantVector *pPlants = CFG_DATA.getPlantOnMap(GetId());
	//if (pPlants != NULL)
	//{
	//	for (CfgMapPlantVector::iterator it = pPlants->begin(); it != pPlants->end(); ++it)
	//	{
	//		CfgPlant *pCfgPlant = CFG_DATA.getPlant(it->plantid);
	//		if (pCfgPlant != NULL && pCfgPlant->type == PT_NORMAL)
	//		{
	//			Plant *plant = new Plant;
	//			if (NULL == plant)
	//			{
	//				continue;
	//			}
	//			plant->init(this, *pCfgPlant, *it);
	//			addPlant(plant);
	//		}
	//	}
	//}
}

void Map::update()
{
	//if (!m_players.empty() || getNow() - m_lastUpdateTime >= 60)
	//{

	//	updatePlayers();

	//	updateMonsters();

	//	updateNpcs();

	//	updatePlants();

	//	updateDropItems();

	//	m_lastUpdateTime = getNow();
	//}
}

int32_t Map::GetId() const
{
	return m_cfgmap.id;
}

int32_t Map::GetType() const
{
	return m_cfgmap.type;
}

int32_t Map::getAntiProtect() const
{
	return m_cfgmap.anti_protect;
}

int32_t Map::getReive() const
{
	return m_cfgmap.revive;
}

int32_t Map::getHideMini() const
{
	return m_cfgmap.hide_mini;
}

int32_t Map::GetWidthTileCount() const
{
	return m_widthTileCount;
}

int32_t Map::GetHeightTileCount() const
{
	return m_heightTileCount;
}

Tile* Map::getTile(int32_t tx, int32_t ty)
{
	if (tx >= 0 && tx < m_widthTileCount && ty >= 0 && ty < m_heightTileCount)
	{
		Tile *pTile = TILE_MANAGER.getTiles(m_cfgmap.id);
		if (pTile != NULL)
		{
			return &(pTile[tx + ty*m_widthTileCount]);
		}
	}

	return NULL;
}

bool  Map::isWalkablePosition(int32_t tx, int32_t ty)
{
	if (tx >= 0 && tx < m_widthTileCount && ty >= 0 && ty < m_heightTileCount)
	{
		return  TILE_MANAGER.isWalkblePosition(m_cfgmap.id,tx,ty,m_cfgmap.width/64);
	}
	return false;
}

Position Map::getAreaByPos( const Position& pos )
{
	Position area;
	area.x = pos.x / AREA_WIDTH;
	area.y = pos.y / AREA_HEIGHT;

	return area;
}

int32_t Map::getViewAreaCount( int32_t nSize ) const
{
	return (2*nSize+1)*(2*nSize+1);
}

void Map::getViewAreas( const Position& pos, PositionVector& outAreas, int32_t nSize )
{
	Position area = getAreaByPos( pos );

	outAreas.reserve( getViewAreaCount( nSize ) );
	for (int32_t x = area.x-nSize; x <= area.x+nSize; ++x)
	{
		for (int32_t y = area.y-nSize; y <= area.y+nSize; ++y)
		{
			if ( x >= 0 && x < m_widthAreaCount && y >= 0 && y < m_heightAreaCount )
			{
				outAreas.push_back( Position( x, y ) );
			}
		}
	}
}

void Map::getNewAreas( const Position& oldPos, const Position& newPos, PositionVector& outAreas, int32_t nSize )
{
	Position oldArea = getAreaByPos( oldPos );
	Position newArea = getAreaByPos( newPos );
	if ( oldArea == newArea )
	{
		return;
	}

	PositionVector oldAreas;
	PositionVector newAreas;
	getViewAreas( oldPos, oldAreas, nSize );
	getViewAreas( newPos, newAreas, nSize );

	outAreas.reserve( getViewAreaCount( nSize ) );
	for ( PositionVector::iterator iter = newAreas.begin(); iter != newAreas.end(); ++iter )
	{
		Position& tmpArea = *iter;
		if ( std::find( oldAreas.begin(), oldAreas.end(), tmpArea ) == oldAreas.end() )
		{
			outAreas.push_back( tmpArea );
		}
	}
}

//void Map::getAreaUnits( const PositionVector& areas, UnitList& outUnits )
//{
//	// 检测玩家
//	for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
//	{
//		Player *player = *it;
//		if (player != NULL)
//		{
//			if ( !inAreas( player, areas ) )
//			{
//				continue;
//			}
//
//			// player
//			outUnits.push_back(player);
//			// 加上玩家的宠物
//		}
//	}
//
//	// 检测怪物
//	for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
//	{
//		Monster *monster = *it;
//		if (monster != NULL && inAreas(monster, areas))
//		{
//			outUnits.push_back(monster);
//		}
//	}
//
//	// 检测陷阱
//	for (TrailerList::iterator it = m_trailers.begin(); it != m_trailers.end(); ++it)
//	{
//		Trailer *trailer = *it;
//		if (trailer != NULL && inAreas(trailer, areas))
//		{
//			outUnits.push_back(trailer);
//		}
//	}
//}

bool Map::inRegion(const Position &pos, const CfgMapRegion &region)
{
	if (GetId() != region.mapid)
	{
		return false;
	}

	if (xAddHalfY(pos.x, pos.y) >= xAddHalfY(region.min_x, region.min_y) && 
		xAddHalfY(pos.x, pos.y) <= xAddHalfY(region.max_x, region.max_y) && 
		xSubHalfY(pos.x, pos.y) >= xSubHalfY(region.min_x, region.min_y) && 
		xSubHalfY(pos.x, pos.y) <= xSubHalfY(region.max_x, region.max_y))
	{
		return true;
	}

	return false;
}

Position Map::getRandomWalkablePosition()
{
	return TILE_MANAGER.getRandomWalkablePosition( GetId() );
}

Position Map::getRandomWalkablePositionInRegion(const CfgMapRegion &region)
{
	Position pos(-1, -1);

	//y轴的值是否合理
	if(region.min_y <0)return pos;
	if(region.max_y <region.min_y) return pos; 
	if(region.min_x <0)return pos;
	if(region.max_x <region.min_x) return pos;

	for (int32_t i = 0; i < 10; ++i) //max try 10 times
	{
		int32_t x = RANDOM.generate(region.min_x, region.max_x);
		int32_t y = RANDOM.generate(region.min_y, region.max_y);
		Tile *pTile = getTile(x, y);
		if (pTile != NULL && pTile->isWalkable())
		{
			pos.x = x;
			pos.y = y;
			break;
		}
	}

	return pos;
}

Position Map::getRandomWalkableAroundPosition(int32_t tx, int32_t ty)
{
	Position poses[25];
	int32_t count = 0;

	for (int32_t x = -2; x <= 2; ++x)
	{
		for (int32_t y = -4; y <= 4; ++y)
		{
			Position pos(tx+x, ty+y);
			if (pos.tileDistance(Position(tx, ty)) > 1)
			{
				Tile *pTile = getTile(tx+x, ty+y);
				if (pTile != NULL && pTile->isWalkable() && count < 25)
				{
					poses[count++] = pos;
				}
			}
		}
	}

	if (count <= 0)
	{
		return Position(tx, ty);
	}
	else
	{
		return poses[RANDOM.generate(0, count-1)];
	}
}

int32_t Map::xAddHalfY(int32_t x, int32_t y)
{
	return x + y/2;
}

int32_t Map::xSubHalfY(int32_t x, int32_t y)
{
	return x - y/2;
}

//bool Map::inAreas(Unit *pUnit, const PositionVector &areas)
//{
//	if (pUnit == NULL || pUnit->getMap() != this)
//	{
//		return false;
//	}
//
//	Position pos = pUnit->getCurrentPixel();
//	for ( PositionVector::const_iterator it = areas.begin(); it != areas.end(); ++it )
//	{
//		if ( checkPos ( pos, *it ) )
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

bool Map::checkPos( const Position& pos, const Position& area ) const
{
	int32_t nLeft = area.x * AREA_WIDTH;
	int32_t nRight = nLeft + AREA_WIDTH;
	int32_t nBottom = area.y * AREA_HEIGHT;
	int32_t nTop = nBottom + AREA_HEIGHT;
	if ( pos.x < nLeft || pos.x >= nRight || pos.y < nBottom || pos.y >= nTop )
	{
		return false;
	}

	return true;
}

bool Map::AddMonster( Monster* pMonster )
{
	if ( NULL == pMonster )
	{
		return false;
	}
	if ( getMonster( pMonster->GetId() ) != NULL )
	{
		return false;
	}

	m_monsters.push_back( pMonster );
	return true;
}

void Map::getAreaMonsters( const Position& center, int32_t nArea, UnitList& outUnits )
{
	for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		Monster *monster = *it;
		if ( monster != NULL && center.tileDistance( monster->GetCurTile() ) <= nArea )
		{
			outUnits.push_back( monster );
		}
	}
}

Monster* Map::getMonster( EntityId_t nId )
{
	MonsterList::iterator iter = m_monsters.begin();
	MonsterList::iterator eiter = m_monsters.end();
	for ( ; iter != eiter; ++iter )
	{
		Monster* pMonster = *iter;
		if ( NULL == pMonster )
		{
			continue;
		}

		if ( pMonster->GetId() == nId )
		{
			return pMonster;
		}
	}
	return NULL;
}

Monster* Map::getMonsterByMid( int32_t nMid )
{
	Monster* pTarget = NULL;
	int32_t distance = 0;
	MonsterList::iterator iter = m_monsters.begin();
	MonsterList::iterator eiter = m_monsters.end();
	for ( ; iter != eiter; ++iter )
	{
		Monster* pMonster = *iter;
		if ( NULL == pMonster )
		{
			continue;
		}

		if ( pMonster->GetMid() == nMid && pMonster->IsAlive() )
		{
			return pMonster;
		}
	}
	return NULL;
}

Monster* Map::GetNearestAliveMonster( const Position& pos, int32_t mid )
{
	Monster* pRet = NULL;
	MonsterList::iterator iter = m_monsters.begin();
	MonsterList::iterator eiter = m_monsters.end();
	for ( ; iter != eiter; ++iter )
	{
		Monster* pMonster = *iter;
		if ( NULL == pMonster )
		{
			continue;
		}

		if ( !pMonster->IsAlive() )
		{
			continue;
		}

		if ( mid > 0 && mid != pMonster->GetMid() )
		{
			continue;
		}

		Tile* pTile = getTile( pMonster->GetX(), pMonster->GetY() );
		if ( pTile != NULL && pTile->isWalkable() )
		{
			if ( NULL == pRet )
			{
				pRet = pMonster;
				continue;
			}

			if ( pMonster->GetCurTile().tileDistance( pos ) < pRet->GetCurTile().tileDistance( pos ) )
			{
				pRet = pMonster;
			}
		}
	}
	return pRet;
}

Monster* Map::GetRandomAliveMonster()
{
	std::vector<Monster*> vMonster;
	vMonster.reserve( m_monsters.size() );

	MonsterList::iterator iter = m_monsters.begin();
	MonsterList::iterator eiter = m_monsters.end();
	for ( ; iter != eiter; ++iter )
	{
		Monster* pMonster = *iter;
		if ( NULL == pMonster )
		{
			continue;
		}

		if ( !pMonster->IsAlive() )
		{
			continue;
		}

		Tile* pTile = getTile( pMonster->GetX(), pMonster->GetY() );
		if ( pTile != NULL && pTile->isWalkable() )
		{
			vMonster.push_back( pMonster );
		}
	}

	if ( vMonster.empty() )
	{
		return NULL;
	}

	int32_t rand = RANDOM.generate( 0, vMonster.size()-1 );
	return vMonster[rand];
}

Position Map::firstLinePosition(Position src, Position dest)
{
	Position pos(-1, -1);

	PathFinder pathFinder(*this);
	PositionVector path = pathFinder.findPath(src, dest);

	if (path.size() >= 2)
	{
		int32_t direction = tileDirection(src.x, src.y, path[1].x, path[1].y);
		pos = path[1];

		for (size_t i = 2; i < path.size(); ++i)
		{
			if (tileDirection(path[i-1].x, path[i-1].y, path[i].x, path[i].y) != direction)
			{
				break;
			}

			pos = path[i];
		}
	}

	return pos;
}
