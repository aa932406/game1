#pragma once

#include "CfgData.h"
#include "Entity.h"

class Map;
/*
* 采集物
*/

enum PlantEventType
{
	PET_GAIN_ITEM		= 1,	//获得物品
	PET_FLUSH_NPC		= 2,	//放出npc
	PET_FLUSH_MONSTER	= 3,	//放出怪物
	PET_DROP_ITEM		= 4,	//物品掉落在地上
};

class Plant
	: public Entity
{
public:
	Plant();
	virtual ~Plant();

public:
	void init(Map *pMap, const CfgPlant &cfgPlant, const CfgMapPlant &cfgMapPlant);

	virtual int32_t			onBeginGather(Player *player);
	virtual int32_t			onEndGather(Player *player);
	virtual bool			isLifeEnd();
	virtual void			revive();

	void					BreakGather();
	int32_t					onBreakGather(Player *player);
	bool					isCorpse();
	int32_t					getPlantId();
	bool					checkRevive();
	void					appendInfo(Answer::NetPacket *inPacket);
	void					broadcastRemove();
	int32_t					GetPlantType();
	int32_t					getNow();
	tm						getLocalNow();
	CharId_t				getOwner() const;
	int32_t					PlantEvent( Player *pPlayer, int32_t EventId );
	void					SendGainItem( Player* pPlayer, const MemChrBagVector &vItem );
	void					BroadCastCheange();
protected:
	Map*			m_pMap;
	CfgPlant		m_cfgPlant;
	CfgMapPlant		m_cfgMapPlant;

	CharId_t		m_gather;
	int64_t			m_gatherTick;

	bool			m_isCorpse;
	int64_t			m_corpseTick;
	int32_t			m_whoCanPlant;
};

