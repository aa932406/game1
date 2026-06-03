#pragma once

#include "Plant.h"

class Dungeon;

class PlantDungeon
	: public Plant
{
public:
	PlantDungeon();
	virtual ~PlantDungeon();

public:
	void init(Dungeon *dungeon, const CfgPlant &cfgPlant, const CfgMapPlant &cfgMapPlant);
	void reset();

	virtual int32_t onEndGather(Player *player);

private:
	Dungeon *m_dungeon;
};


