#include "stdafx.h"

#include "ActivityMap.h"
#include "Map.h"
#include "PlantActivity.h"

PlantActivity::PlantActivity()
	: m_pActivityMap(NULL)
{

}

PlantActivity::~PlantActivity()
{

}

void PlantActivity::init( CActivityMap *pActivityMap, const CfgPlant &cfgPlant, const CfgMapPlant &cfgMapPlant )
{
	if ( NULL == pActivityMap )
	{
		return;
	}
	m_pActivityMap = pActivityMap;
	Plant::init( pActivityMap, cfgPlant, cfgMapPlant );
}

void PlantActivity::reset()
{
	m_pActivityMap = NULL;
}

int32_t PlantActivity::onBeginGather( Player *player )
{
	int32_t err = Plant::onBeginGather(player);
	if ( err == ERR_OK )
	{
		err = m_pActivityMap->onBeginGather(this, player );
	}
	return err;
}

int32_t PlantActivity::onEndGather( Player *player )
{
	if (NULL == player)
	{
		return ERR_INVALID_DATA;
	}
	int32_t err = Plant::onEndGather(player);

	if (err == ERR_OK)
	{
		m_pActivityMap->onPlantGather(this, player );
	}

	return err;
}
