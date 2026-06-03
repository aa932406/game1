#pragma once

enum TileMask
{
	TM_NORMAL = 0,
	TM_BLOCK = 1,
	TM_SHADOW = 2,
	TM_TOP = 3,
};

/*
* 地图块
* 地图上的基本运算单元格
*/
class Tile
{
public:
	Tile();
	~Tile();

public:
	int32_t getParent();
	Position getPosition();
	int32_t getDepth();
	bool isWalkable();

	void init(int32_t parent, int32_t x, int32_t y, int32_t depth, int32_t mask);

	void setMask(int32_t mask);

private:
	int32_t m_parent;
	int16_t m_x;
	int16_t m_y;
	int16_t m_depth;
	int16_t m_mask;
};

class TileManager
{
public:
	TileManager();
	~TileManager();

public:
	void Init();
	//Tile* getTilesAstart(int32_t mapid);
	Tile* getTiles(int32_t mapid);
	bool isWalkblePosition(int32_t mapid,int32_t x,int32_t y,int32_t wigth);
	Position getRandomWalkablePosition(int32_t mapid);

private:
	void addMap(int32_t mapid, int32_t width, int32_t height);
	void parseRd(int32_t mapid, int32_t width, int32_t height, Tile *pTile);
	void parseRdx(int32_t mapid, int32_t width, int32_t height, Tile *pTile);

private:
	typedef std::map<int32_t, Tile*> Int32TileMap;
	Int32TileMap m_allTiles;
	//Int32TileMap m_AllAStarTiles;

	typedef std::map<int32_t, PositionVector> Int32PositionVectorMap;
	Int32PositionVectorMap m_walkablePositions;
};
#define TILE_MANAGER Answer::Singleton<TileManager>::instance()
