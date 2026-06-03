#include "stdafx.h"

#include "GameService.h"
#include "Map.h"
#include "Plant.h"
#include "Timer.h"
#include "ItemHelper.h"
#include "ActivityMap.h"
#include "Dungeon.h"
#include "DBService.h"
#include "PoolManager.h"
using namespace Answer;

Plant::Plant()
	: Entity(ET_PLANT), m_pMap(NULL), m_gather(0), m_gatherTick(0), m_isCorpse(false), m_corpseTick(0),m_whoCanPlant(0)
{

}

Plant::~Plant()
{

}

void Plant::init(Map *pMap, const CfgPlant &cfgPlant, const CfgMapPlant &cfgMapPlant)
{
	if (NULL == pMap)
	{
		return;
	}
	m_pMap = pMap;
	m_cfgPlant = cfgPlant;
	m_cfgMapPlant = cfgMapPlant;

	m_gather = 0;
	m_gatherTick = 0;

	m_isCorpse = false;
	m_corpseTick = 0;
}

int32_t Plant::getPlantId()
{
	return m_cfgPlant.id;
}

int32_t Plant::onBeginGather(Player *player)
{
	if (m_pMap == NULL || player == NULL || isCorpse() )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_gather != 0 && m_gather != player->getCid() )
	{
		player->sendEndGather(ERR_ALREADY_IN_GATHER);
		return ERR_ALREADY_IN_GATHER;
	}

	if (m_cfgPlant.item_cost != 0 && !player->hasItem(m_cfgPlant.item_cost, IC_NORMAL, 1))
	{
		return ERR_INVALID_DATA;
	}
	if ( m_cfgPlant.revive_time > 0 )
	{
		m_gather = player->getCid();
		m_gatherTick = m_pMap->getTick();
		BroadCastCheange();
	}
	else if ( m_cfgPlant.revive_time == 0 )
	{
		player->SetStartGather(m_pMap->getTick());
	}
	return ERR_OK;
}

int32_t Plant::GetPlantType()
{
	return m_cfgPlant.type;
}

int32_t Plant::onEndGather(Player *player)
{
	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_cfgPlant.revive_time > 0 )
	{
		if ( m_pMap->getTick() - m_gatherTick < m_cfgPlant.gather_time )
		{
			BreakGather();
			//player->sendEndGather(ERR_INVALID_DATA);
			return ERR_INVALID_DATA;
		}
	}
	else if ( m_cfgPlant.revive_time ==  0 )
	{
		if ( m_pMap->getTick() - player->GetStartGather() < m_cfgPlant.gather_time )
		{
			//player->sendEndGather(ERR_INVALID_DATA);
			return ERR_INVALID_DATA;
		}
	}
	
	if ( m_cfgPlant.item_cost != 0 && !player->hasItem( m_cfgPlant.item_cost, IC_NORMAL, 1))
	{
		BreakGather();
		//player->sendEndGather(ERR_INVALID_DATA);
		return ERR_INVALID_DATA;
	}

	int32_t roll = RANDOM.generate(1, m_cfgPlant.EventMaxRate);

	for (CfgPlantEventVector::iterator it = m_cfgPlant.Events.begin(); it != m_cfgPlant.Events.end(); ++it)
	{
		if ( roll <= it->Probability )
		{
			if ( ERR_OK != PlantEvent( player, it->EventId ) )
			{
				BreakGather();
				//player->sendEndGather(ERR_INVALID_DATA);
				return ERR_INVALID_DATA;
			}
			break;
		}
		else
		{
			roll -= it->Probability;
		}
	}
	if( m_cfgPlant.revive_time > 0 )
	{
		m_gather = 0;
		m_gatherTick = 0;
		m_isCorpse = true;
		m_corpseTick = m_pMap->getTick();
		broadcastRemove();
	}
	player->GetTask().updateTaskMonster( m_cfgPlant.id, 0 );
	return ERR_OK;
}

int32_t Plant::PlantEvent( Player* pPlayer,int32_t EventId )
{
	if ( NULL == m_pMap || NULL == pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	CfgPlantEventEffect* pPlantEvent = CFG_DATA.GetPlantEvent( EventId );
	if ( NULL == pPlantEvent )
	{
		return ERR_SYETEM_ERR;
	}
	switch( pPlantEvent->EventType )
	{
	case PET_GAIN_ITEM:
		{
			const MemChrBagVector ItemVector = CItemHelper::parseItemString( EventId, pPlantEvent->EventEffect );
			if ( ItemVector.size() > 0 )
			{
				if ( pPlayer->GetBag().AddItemsAndEggs( ItemVector, IACR_PALNT_GET ) )
				{
					if ( m_pMap->IsActivityMap() )
					{
						SendGainItem( pPlayer, ItemVector );
					}
				}
				else
				{
					if ( m_pMap->IsActivityMap() )
					{
						DB_SERVICE.OnSendSysMail( pPlayer->getCid(), PlantAddItem, ItemVector );
					}
				}
			}
			break;
		}
	case PET_FLUSH_NPC:
		{
			if ( m_pMap->IsActivityMap() )
			{
				CActivityMap* pAactivityMap = dynamic_cast<CActivityMap*>( m_pMap );
				if ( pAactivityMap != NULL )
				{
					pAactivityMap->AddActivityNpc( pPlantEvent->EventEffect );
				}
			}
			break;
		}
	case PET_FLUSH_MONSTER:
		{
			if ( m_pMap->IsActivityMap() )
			{
				CActivityMap* pAactivityMap = dynamic_cast<CActivityMap*>( m_pMap );
				if ( pAactivityMap != NULL )
				{
					pAactivityMap->generateMonster(  pPlantEvent->EventEffect );
				}
			}
			else if ( m_pMap->IsDungeonMap() )
			{
				Dungeon* pDungeon = dynamic_cast<Dungeon*>( m_pMap );
				if ( pDungeon != NULL )
				{
					pDungeon->generateMonster(  pPlantEvent->EventEffect );
				}
			}
			break;
		}
	case PET_DROP_ITEM:
		{
			MemChrBagVector ItemVector = CItemHelper::parseItemString( EventId, pPlantEvent->EventEffect );
			if ( ItemVector.size() <= 0 )
			{
				return ERR_SYETEM_ERR;
			}
			DropItem dropItems[MAX_DROPITEM_SIZE] = {};

			int32_t i = 0;
			MemChrBagVector::iterator it = ItemVector.begin();
			for ( ; it != ItemVector.end(); it++ )
			{
				dropItems[i].itemId		= it->itemId;
				dropItems[i].itemClass	= it->itemClass;
				dropItems[i].bindType	= it->bind;
				dropItems[i].costType	= CCT_NONE;
				dropItems[i].costValue	= 0;
				dropItems[i].itemCount	= it->itemCount;
				dropItems[i].endTime	= 0;
				dropItems[i].srcId		= 0;
				++i;
				if ( i >= MAX_DROPITEM_SIZE )
				{
					break;
				}
			}
			CDropItemGroup *pDropItemGroup = NULL;
			pDropItemGroup = POOL_MANAGER.pop<CDropItemGroup>();
			if ( pDropItemGroup != NULL )
			{
				Position pos( m_cfgMapPlant.x, m_cfgMapPlant.y );
				pDropItemGroup->init(m_pMap,pos, pPlayer, ET_MONSTER, 0, dropItems,pPlayer->getName(), 0, 0);
				m_pMap->addDropItemGroup(pDropItemGroup);
			}
			break;
		}
	default:
		break;
	}
	if ( pPlantEvent->GongGaoId > 0 )
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet != NULL )
		{
			packet->writeInt32( pPlantEvent->GongGaoId );
			packet->writeUTF8( pPlayer->getName() );
			packet->writeInt64( pPlayer->getCid() );
			packet->setSize(packet->getWOffset());
			GAME_SERVICE.broadcast( packet );
		}
	}
	return ERR_OK;
}

void Plant::SendGainItem( Player* pPlayer, const MemChrBagVector &vItem )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_PLANT_GAIN_ITEM);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( getEntityId() );
	int32_t nSize = vItem.size();
	packet->writeInt32(nSize);
	MemChrBagVector::const_iterator it = vItem.begin();
	for ( ; it != vItem.end(); ++it )
	{
		packet->writeInt8( it->itemClass );
		packet->writeInt32( it->itemId );
		packet->writeInt32( it->itemCount );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);
}

int32_t Plant::onBreakGather(Player *player)
{
	if (m_pMap == NULL || player == NULL)
	{
		return ERR_INVALID_DATA;
	}
	BreakGather();
	return ERR_OK;
}

void Plant::BreakGather()
{
	m_gather = 0;
	m_gatherTick = 0;
	BroadCastCheange();
}

bool Plant::isCorpse()
{
	return m_isCorpse;
}

bool Plant::checkRevive()
{
	tm localNow = getLocalNow();

	if(m_pMap != NULL && m_cfgPlant.revive_time==0)
		return true;

	if (m_pMap != NULL && isCorpse() && m_pMap->getTick()-m_corpseTick >= m_cfgPlant.revive_time && localNow.tm_hour >= m_cfgPlant.start_hour && localNow.tm_hour <= m_cfgPlant.end_hour)
	{
		return true;
	}

	return false;
}

void Plant::appendInfo(Answer::NetPacket *inPacket)
{
	if (inPacket != NULL)
	{
		inPacket->writeInt64(getEntityId());
		inPacket->writeInt32(m_cfgPlant.id);
		inPacket->writeInt64(m_gather);
		inPacket->writeInt16(static_cast<int16_t>(m_cfgMapPlant.x));
		inPacket->writeInt16(static_cast<int16_t>(m_cfgMapPlant.y));
	}
}

void Plant::BroadCastCheange()
{
	if (m_pMap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTVITY_PLANTS);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getEntityId());
		packet->writeInt64( m_gather );
		packet->setSize(packet->getWOffset());
		m_pMap->broadcast(packet);
	}
};

void Plant::broadcastRemove()
{
	if (m_pMap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_REMOVE_PLANT);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(1);
		packet->writeInt64(getEntityId());
		packet->setSize(packet->getWOffset());
		m_pMap->broadcast(packet);
	}
}

int32_t Plant::getNow()
{
	return TIMER.GetNow();
}

tm Plant::getLocalNow()
{
	return TIMER.GetLocalNow();
}

bool Plant::isLifeEnd()
{
	return false;
}

void Plant::revive()
{
	m_gather = 0;
	m_gatherTick = 0;

	m_isCorpse = false;
	m_corpseTick = 0;
	m_pMap->broadcastPlantIntoMap(this);
}
