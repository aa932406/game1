#pragma once

#include "Plant.h"

class CActivityMap;
class PlantActivity
	: public Plant
{
public:
	PlantActivity();
	virtual ~PlantActivity();

public:
	void init( CActivityMap *pActivityMap, const CfgPlant &cfgPlant, const CfgMapPlant &cfgMapPlant );
	void reset();

	virtual int32_t onEndGather(Player *player);
	virtual int32_t onBeginGather(Player *player);
private:
	CActivityMap *m_pActivityMap;
};

