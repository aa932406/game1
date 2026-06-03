#pragma once

struct Node	 
{
	Node(Position &position)
	{
		pos = position;
		inOpen = false;
		inClose = false;
		g = 0;
		h = 0;
		f = 0;
		parent = NULL;
	}

	Position pos;
	bool inOpen;
	bool inClose;
	int32_t g;
	int32_t h;
	int32_t f;
	Node *parent;
};
typedef std::vector<Node*> NodeVector;

class Map;

class PathFinder
{
public:
	PathFinder(Map &map);
	~PathFinder();

public:
	PositionVector findPath(Position src, Position dest);

private:
	PositionVector findPathOctree(Position src, Position dest);
	PositionVector findPathAStar(Position src, Position dest);
	PositionVector findPathAStar2(Position src, Position dest, int32_t deapth);

	PositionVector getAroundTiles(Position center, const NodeVector &closelist);

	int32_t gValue(Node *pSrc, Position dest);
	int32_t hValue(Position src, Position dest);

private:
	Map &m_map;
};

