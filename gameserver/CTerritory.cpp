#include "stdafx.h"
#include "CTerritory.h"
#include "GameService.h"
#include "FamilyManager.h"
#include "PoolManager.h"
#include "Monster.h"
#include "DropItem.h"
#include "Plant.h"
#include "Trap.h"
#include "Npc.h"
#include "CfgData.h"
#include "Player.h"

using namespace Answer;

CTerritory::CTerritory()
	: Map()
	, m_FamilyId( 0 )
	, m_Piglet( NULL )
{
}

CTerritory::~CTerritory()
{
}

void CTerritory::init( CMapRunner* pRunner, const CfgMap& cfgmap, FamilyId_t FamilyId )
{
	m_FamilyId = FamilyId;
	Map::init( cfgmap );
	AddFamilyMonster( true );
}

void CTerritory::reset()
{
	// Clear monsters
	for ( MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it )
	{
		Monster* monster = *it;
		if ( monster != NULL )
		{
			GAME_SERVICE.removeMonster( monster );
			POOL_MANAGER.push<Monster>( monster );
		}
	}
	m_monsters.clear();

	// Clear plants
	for ( PlantList::iterator it = m_plants.begin(); it != m_plants.end(); ++it )
	{
		Plant* plant = *it;
		if ( plant != NULL )
		{
			POOL_MANAGER.push<Plant>( plant );
		}
	}
	m_plants.clear();

	// Clear drop items
	for ( DropItemGroupList::iterator it = m_dropItems.begin(); it != m_dropItems.end(); ++it )
	{
		CDropItemGroup* pDrop = *it;
		if ( pDrop != NULL )
		{
			POOL_MANAGER.push<CDropItemGroup>( pDrop );
		}
	}
	m_dropItems.clear();

	// Clear traps
	for ( TrapList::iterator it = m_traps.begin(); it != m_traps.end(); ++it )
	{
		Trap* trap = *it;
		if ( trap != NULL )
		{
			POOL_MANAGER.push<Trap>( trap );
		}
	}
	m_traps.clear();

	// Clear NPCs
	for ( NpcList::iterator it = m_npcs.begin(); it != m_npcs.end(); ++it )
	{
		Npc* npc = *it;
		if ( npc != NULL )
		{
			POOL_MANAGER.push<Npc>( npc );
		}
	}
	m_npcs.clear();

	m_FamilyId = 0;
	m_Piglet = NULL;
}

void CTerritory::AddFamilyMonster( bool bInit )
{
	FamilyInfo FamilyStu = FAMILY_MANAGER.GetFamilyInfo( m_FamilyId );

	if ( ( bInit && FamilyStu.nBossState == 1 ) || ( !bInit && FamilyStu.nBossState == 3 ) )
	{
		if ( m_Piglet != NULL )
		{
			m_Piglet->leaveMap();
			m_Piglet->addRef( -m_Piglet->getRef() );  // Force release
			m_Piglet->SetReviveTime( 0 );

			const CfgFamilyBoss* pFamilyBoss = CFG_DATA.GetFamilyTable().GetFamilyBoss( FamilyStu.nLevel, 0 );
			if ( pFamilyBoss != NULL )
			{
				int32_t BossMid = pFamilyBoss->BossMid;
				const CfgMonster* pCfgMonster = CFG_DATA.getMonster( BossMid );
				if ( pCfgMonster != NULL )
				{
					Monster* monster = POOL_MANAGER.pop<Monster>();
					if ( monster != NULL )
					{
						CfgMapMonster MapMonster;
						memset( &MapMonster, 0, sizeof(MapMonster) );
						MapMonster.id = CFG_DATA.GetMapMonsterId();
						MapMonster.mapid = GetId();
						MapMonster.x = m_Piglet->getPosX();
						MapMonster.y = m_Piglet->getPosY();

						AttrAddonVector vAttrAddon;
						monster->init( pCfgMonster, &MapMonster, MS_STAND, &vAttrAddon );
						addMonster( monster, MapMonster.x, MapMonster.y );
					}
				}
			}
		}
	}
}

void CTerritory::addMonster( Monster* monster, int32_t x, int32_t y )
{
	if ( monster != NULL )
	{
		if ( monster->getMid() == 50001 )
		{
			m_Piglet = monster;
			monster->SetFamilyId( m_FamilyId, "" );
		}
		Map::addMonster( monster, x, y );
	}
}

void CTerritory::addPlayer( Player* player, int32_t x, int32_t y )
{
	if ( player != NULL )
	{
		Map::addPlayer( player, x, y );
	}
}

void CTerritory::removePlayer( Player* player, bool islogout )
{
	if ( player != NULL )
	{
		Map::removePlayer( player, islogout );
	}
}

void CTerritory::onMonsterDie( Monster* monster, Player* player )
{
	if ( monster != NULL )
	{
		int32_t Mid = monster->getMid();
		const CfgFamilyBoss* pFamilyBoss = CFG_DATA.GetFamilyTable().GetFamilyBoss( 0, Mid );
		if ( pFamilyBoss != NULL )
		{
			if ( m_Piglet != NULL )
			{
				m_Piglet->SetReviveTime( monster->getNow() + 10 );
			}
			monster->setDelFlg();
			// Add contribution
			// Map::AddContribution( 500, GCR_KILL_PIG );
			FAMILY_MANAGER.SendSocialFinishBoss( m_FamilyId, 0, 1 );

			if ( player != NULL )
			{
				Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), Answer::PACK_DISPATCH, 0x4E9B );
				if ( packet != NULL )
				{
					packet->writeInt32( player->getGateIndex() );
					packet->writeInt8( 4 );
					packet->writeInt32( pFamilyBoss->FamilyExp );
					packet->writeInt32( pFamilyBoss->GongGaoId );
					packet->setSize( packet->getWOffset() );
					GAME_SERVICE.sendPacket( player->getConnId(), packet );
				}
			}
		}
		Map::onMonsterDie( monster, player );
	}
}
