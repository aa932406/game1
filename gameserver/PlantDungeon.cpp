#include "stdafx.h"

#include "Dungeon.h"
#include "PlantDungeon.h"

PlantDungeon::PlantDungeon()
	: m_dungeon(NULL)
{

}

PlantDungeon::~PlantDungeon()
{

}

void PlantDungeon::init(Dungeon *dungeon, const CfgPlant &cfgPlant, const CfgMapPlant &cfgMapPlant)
{
	if (NULL == dungeon)
	{
		return;
	}
	m_dungeon = dungeon;

	Plant::init(dungeon, cfgPlant, cfgMapPlant);
}

void PlantDungeon::reset()
{
	m_dungeon = NULL;
}

int32_t PlantDungeon::onEndGather(Player *player)
{
	if (NULL == player)
	{
		return ERR_INVALID_DATA;
	}
	int32_t err = Plant::onEndGather(player);

	if (err == ERR_OK)
	{
		m_dungeon->onPlantGather(this);
	}

	return err;
}

