#include "stdafx.h"

#include "CfgData.h"
#include "Tile.h"

#include <fstream>

using namespace Answer;
using namespace std;

Tile::Tile()
	: m_parent(0), m_x(0), m_y(0), m_depth(0), m_mask(TM_BLOCK)
{

}

Tile::~Tile()
{

}

int32_t Tile::getParent()
{
	return m_parent;
}

Position Tile::getPosition()
{
	return Position(m_x, m_y);
}

int32_t Tile::getDepth()
{
	return m_depth;
}

bool Tile::isWalkable()
{
	return m_mask == TM_NORMAL || m_mask == TM_SHADOW;
}

void Tile::init(int32_t parent, int32_t x, int32_t y, int32_t depth, int32_t mask)
{
	m_parent = parent;
	m_x = x;
	m_y = y;
	m_depth = depth;
	m_mask = mask;
}

void Tile::setMask(int32_t mask)
{
	m_mask = mask;
}

TileManager::TileManager()
{

}

TileManager::~TileManager()
{

}

void TileManager::Init()
{
	//读取地图信息
	const CfgMapTable &allMaps = CFG_DATA.getMapAll();
	for (CfgMapTable::const_iterator it = allMaps.begin(); it != allMaps.end(); ++it)
	{
		addMap(it->second.id, it->second.width/64, roundInt(it->second.height/16.0));//菱形;
	}
}

void TileManager::addMap(int32_t mapid, int32_t width, int32_t height)
{
	if (mapid <= 0 || width <= 0 || height <= 0)
	{
		return;
	}

	CfgMap *pCfg = CFG_DATA.getMap(mapid);
	if (pCfg == NULL)
	{
		return;
	}

	Tile *pTile = new Tile[width*height];
	//parseRd(mapid, width, height, pTile);
	//bool bAstart=false;
	if (pCfg->hide_mini)
	{
		//bAstart=true;
		parseRd(mapid, width, height, pTile);
	}
	else
	{
		parseRdx(mapid, width, height, pTile);
	}
	m_allTiles[mapid] = pTile;
	/*
	if(!bAstart)
	{
		Tile *pTileAstart = new Tile[width*height];
		parseRd(mapid, width, height, pTileAstart);
		m_AllAStarTiles[mapid] =pTileAstart;
	}
	else
	{
		m_AllAStarTiles[mapid] =pTile;
	}
	*/
	for (int32_t x = 0; x < width; ++x)
	{
		for (int32_t y = 0; y < height; ++y)
		{
			if (pTile[x + y*width].isWalkable())
			{
				m_walkablePositions[mapid].push_back(Position(x, y));
			}
		}
	}
}
/*
Tile* TileManager::getTilesAstart(int32_t mapid)
{
	Int32TileMap::iterator it = m_AllAStarTiles.find(mapid);
	if (it != m_AllAStarTiles.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}*/
Tile* TileManager::getTiles(int32_t mapid)
{
	Int32TileMap::iterator it = m_allTiles.find(mapid);
	if (it != m_allTiles.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

bool TileManager::isWalkblePosition(int32_t mapid,int32_t x,int32_t y,int32_t wigth)
{
	Int32TileMap::iterator it = m_allTiles.find(mapid);
	if (it != m_allTiles.end())
	{
		return it->second[x + wigth*y].isWalkable();
	}
	else
	{
		return false;
	}  
}

Position TileManager::getRandomWalkablePosition(int32_t mapid)
{
	Position pos(-1, -1);

	Int32PositionVectorMap::iterator it = m_walkablePositions.find(mapid);
	if (it != m_walkablePositions.end())
	{
		if (!it->second.empty())
		{
			pos = it->second[RANDOM.generate(0, it->second.size()-1)];
		}
	}

	return pos;
}

void TileManager::parseRd(int32_t mapid, int32_t width, int32_t height, Tile *pTile)
{
	char filename[MAX_PATH] = "";
	snprintf(filename, sizeof(filename)-1, "map/%d.rd", mapid);

	uint32_t destLen = width*height/4 + 1;
	uint8_t *pDest = (uint8_t*)calloc(destLen, sizeof(uint8_t));

	int err = Zip::uncompressFile(filename, pDest, &destLen);
	if (err != ERR_ANSWER_OK)
	{
		LOG_ERROR("Map::parseRd uncompressFile return %d\n", err);
		free(pDest);
		return;
	}

	int32_t tileIndex = 0;
	for (int32_t i = 0; i < (int32_t)destLen && i < width*height/4; ++i)
	{
		pTile[tileIndex++].setMask(pDest[i]&3);
		pTile[tileIndex++].setMask((pDest[i]&12)>>2);
		pTile[tileIndex++].setMask((pDest[i]&48)>>4);
		pTile[tileIndex++].setMask((pDest[i]&192)>>6);
	}

	free(pDest);
}

void TileManager::parseRdx(int32_t mapid, int32_t width, int32_t height, Tile *pTile)
{
	char filename[MAX_PATH] = {};
	snprintf(filename, sizeof(filename)-1, "map/%d.rdx", mapid);

	ifstream rdx(filename);
	if (!rdx.is_open())
	{
		LOG_ERROR("Map::parseRdx failed to open rdx file with mapid = %d\n", mapid);
		return;
	}

	try
	{
		while (!rdx.eof())
		{
			int32_t id = 0;
			rdx >> id;
			int32_t parent = 0;
			rdx >> parent;
			int32_t x = 0;
			rdx >> x;
			int32_t y = 0;
			rdx >> y;
			int32_t depth = 0;
			rdx >> depth;
			int32_t mask = 0;
			rdx >> mask;

			if (id >= 0 && id < width*height)
			{
				if (parent >= -1 && id < width*height)
				{
					pTile[id].init(parent, x, y, depth, mask);
				}
			}
		}
	}
	catch (...)
	{
		LOG_ERROR("Map::parseRdx parse error with mapid = %d\n", mapid);
	}
}


