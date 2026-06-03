#include "stdafx.h"

#include "Map.h"
#include "PathFinder.h"
#include "Tile.h"
#include "MapManager.h"

#include <algorithm>
#include <stack>

#define COST_HORIZONTAL	10
#define COST_VERTICAL	10
#define COST_DIAGONAL	14
#define MAP_MAX_NOD		1000

#define ASTAR_DISTANCE	15
#define ASTAR_DEAPTH	20

using namespace std;

struct FindNode 
{
	Position	parent;
	int32_t		deapth;
	bool		checked;
};

FindNode	mapnods[MAP_MAX_NOD][MAP_MAX_NOD];

bool GreaterNode(Node *left, Node *right)
{
	return left->f > right->f;
}

PathFinder::PathFinder(Map &map)
	: m_map(map)
{

}

PathFinder::~PathFinder()
{

}
PositionVector PathFinder::findPath(Position src, Position dest)
{
	PositionVector path;

	Tile *pSrc = m_map.getTile(src.x, src.y);
	Tile *pDest = m_map.getTile(dest.x, dest.y);

	if (pSrc != NULL && pDest != NULL && pDest->isWalkable())
	{
		//path = findPathAStar(src, dest);
		if (m_map.getHideMini() != 0 || src.tileDistance(dest) <= ASTAR_DISTANCE)
		{
			//path = findPathOctree(src, dest);
			//path = findPathAStar(src, dest);
			path = findPathAStar2(src, dest, ASTAR_DEAPTH);
			if ( path.empty() )
			{
				path = findPathOctree(src, dest);
			}
		}
		else
		{
			path = findPathOctree(src, dest);
		}
	}

	return path;
}

PositionVector PathFinder::findPathAStar(Position src, Position dest)
{
	PositionVector path;

	NodeVector openList;
	NodeVector closeList;

	Tile *pSrc = m_map.getTile(src.x, src.y);
	Tile *pDest = m_map.getTile(dest.x, dest.y);

	if (pSrc != NULL && pDest != NULL && pDest->isWalkable())
	{
		Node *pCurrentNode = new Node(src);
		if (NULL == pCurrentNode)
		{
			return path;
		}
		Node endNode(dest);

		openList.push_back(pCurrentNode);

		while (!openList.empty())
		{
			pCurrentNode = openList.back();
			openList.pop_back();

			pCurrentNode->inOpen = false;
			pCurrentNode->inClose = true;
			closeList.push_back(pCurrentNode);

			if (pCurrentNode->pos == endNode.pos)
			{
				break;
			}

			PositionVector arounds = getAroundTiles(pCurrentNode->pos, closeList);

			for (PositionVector::iterator it = arounds.begin(); it != arounds.end(); ++it)
			{
				int32_t g = gValue(pCurrentNode, *it);
				int32_t h = hValue(*it, endNode.pos);

				int32_t openIndex = -1;
				for (size_t i = 0; i < openList.size(); ++i)
				{
					if (openList[i]->pos == *it)
					{
						openIndex = i;
						break;
					}
				}

				if (openIndex >= 0)
				{
					if (g < openList[openIndex]->g)
					{
						openList[openIndex]->g = g;
						openList[openIndex]->h = h;
						openList[openIndex]->f = g + h;
						openList[openIndex]->parent = pCurrentNode;
						sort(openList.begin(), openList.end(), GreaterNode);
					}
				}
				else
				{
					Node *pNode = new Node(*it);
					if (NULL == pNode)
					{
						continue;
					}
					pNode->inOpen = true;
					pNode->g = g;
					pNode->h = h;
					pNode->f = g+h;
					pNode->parent = pCurrentNode;

					openList.push_back(pNode);
					sort(openList.begin(), openList.end(), GreaterNode);
				}
			}
		}

		if (!closeList.empty())
		{
			Node *pNode = closeList.back();
			if (NULL == pNode)
			{
			}
			while (pNode->pos != src)
			{
				path.push_back(pNode->pos);
				pNode = pNode->parent;
			}

			reverse(path.begin(), path.end());
		}
	}

	for (NodeVector::iterator it = openList.begin(); it != openList.end(); ++it)
	{
		delete *it;
	}

	for (NodeVector::iterator it = closeList.begin(); it != closeList.end(); ++it)
	{
		delete *it;
	}

	return path;
}

PositionVector PathFinder::findPathAStar2(Position src, Position dest, int32_t deapth)
{
	bool bFind = false;
	PositionVector path;
	bzero( mapnods, sizeof( FindNode )* MAP_MAX_NOD * MAP_MAX_NOD );


	std::list<Position> openList;
	Tile *pSrc = m_map.getTile(src.x, src.y);
	Tile *pDest = m_map.getTile(dest.x, dest.y);

	if (pSrc != NULL && pDest != NULL && pDest->isWalkable())
	{
		openList.push_back( src );
		mapnods[src.x][src.y].parent = src;
		mapnods[src.x][src.y].checked = true;

		while (!openList.empty())
		{
			Position curPos = openList.front();
			openList.pop_front();

			if ( curPos == dest )
			{
				bFind = true;
				break;
			}

			if ( mapnods[curPos.x][curPos.y].deapth >= deapth )
			{
				continue;
			}

			for (int32_t i = DOWN; i < DIRECTION_NUM; ++i)
			{
				Position pos = Map::getAroundTile( curPos.x, curPos.y, static_cast<Direction>(i) );
				Tile *pTile = m_map.getTile(pos.x, pos.y);
				if ( NULL == pTile )
				{
					continue;
				}
				if ( !pTile->isWalkable() )
				{
					continue;
				}

				if ( mapnods[pos.x][pos.y].checked )
				{
					continue;
				}

				mapnods[pos.x][pos.y].checked = true;
				mapnods[pos.x][pos.y].parent = curPos;
				mapnods[pos.x][pos.y].deapth = mapnods[curPos.x][curPos.y].deapth+1;
				openList.push_back( pos );
			}
		}

		if ( bFind )
		{
			Position curPos = dest;
			FindNode* pNode = &mapnods[curPos.x][curPos.y];
			while ( pNode->parent != src )
			{
				path.push_back( curPos );
				curPos = pNode->parent;
				pNode = &mapnods[curPos.x][curPos.y];
			}

			path.push_back( curPos );
			path.push_back( src );
			reverse(path.begin(), path.end());
		}
	}

	return path;
}

PositionVector PathFinder::findPathOctree(Position src, Position dest)
{
	PositionVector path;

	Tile *pTiles = TILE_MANAGER.getTiles(m_map.GetId());
	Tile *pSrc = m_map.getTile(src.x, src.y);
	Tile *pDest = m_map.getTile(dest.x, dest.y);

	if (pTiles != NULL && pSrc != NULL && pDest != NULL && pDest->isWalkable())
	{
		PositionVector begins;
		stack<Position> ends;

		Position start = src;
		Position end = dest;

		while (start.x != end.x || start.y != end.y)
		{
			Tile *pStart = m_map.getTile(start.x, start.y);
			Tile *pEnd = m_map.getTile(end.x, end.y);

			if (pStart == NULL || !pStart->isWalkable() || pEnd == NULL || !pEnd->isWalkable())
			{
				break;
			}

			if (pStart->getDepth() >= pEnd->getDepth())
			{
				begins.push_back(start);
				start = pTiles[pStart->getParent()].getPosition();
			}

			if (pStart->getDepth() <= pEnd->getDepth())
			{
				ends.push(end);
				end = pTiles[pEnd->getParent()].getPosition();
			}
		}

		begins.push_back(start);

		while (!ends.empty())
		{
			begins.push_back(ends.top());
			ends.pop();
		}

		path = begins;
	}

	return path;
}

PositionVector PathFinder::getAroundTiles(Position center, const NodeVector &closelist)
{
	PositionVector arounds;

	for (int32_t i = DOWN; i < DIRECTION_NUM; ++i)
	{
		Position pos = Map::getAroundTile(center.x, center.y, static_cast<Direction>(i));
		Tile *pTile = m_map.getTile(pos.x, pos.y);
		if (pTile != NULL && pTile->isWalkable())
		{
			bool inclose = false;
			for (NodeVector::const_iterator it = closelist.begin(); it != closelist.end(); ++it)
			{
				if (pos == (*it)->pos)
				{
					inclose = true;
					break;
				}
			}

			if (!inclose)
			{
				arounds.push_back(pos);
			}
		}
	}

	return arounds;
}

int32_t PathFinder::gValue(Node *pSrc, Position dest)
{
	int32_t g = 0;

	if (pSrc->pos.y == dest.y)
	{
		g = pSrc->g + COST_HORIZONTAL;
	}
	else if (pSrc->pos.y+2 == dest.y || pSrc->pos.y-2==dest.y)
	{
		g = pSrc->g + COST_VERTICAL*2;
	}
	else
	{
		g = pSrc->g + COST_DIAGONAL;
	}

	return g;
}

int32_t PathFinder::hValue(Position src, Position dest)
{
	int32_t dxSrcToZero = src.x*COST_HORIZONTAL + (src.y&1)*COST_HORIZONTAL/2;
	int32_t dxDestToZero = dest.x*COST_HORIZONTAL + (dest.y&1)*COST_HORIZONTAL/2;

	int32_t dx = abs(dxSrcToZero-dxDestToZero);
	int32_t dy = abs(src.y-dest.y)*COST_VERTICAL;

	return dx + dy;
}

