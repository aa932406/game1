#include "stdafx.h"

#include "Activity.h"
#include "CfgData.h"
#include "DropItem.h"
#include "GameService.h"
#include "Map.h"
#include "Monster.h"
#include "MonsterActivity.h"
#include "Npc.h"
#include "NpcActivity.h"
#include "PathFinder.h"
#include "Plant.h"
#include "PlantActivity.h"
#include "Player.h"
#include "Skill.h"
#include "Trailer.h"
#include "Trap.h"
#include "PoolManager.h"
#include "Timer.h"
#include "CLittleHelper.h"
#include "WorldBoss.h"
#include <vector>
#include <algorithm>
#include <limits>
using namespace Answer;
using namespace std;

#define NETPACKET_PLAYER_INTO_MAP_LIMIT		50
#define NETPACKET_PET_INTO_MAP_LIMIT		50
#define NETPACKET_MONSTER_INTO_MAP_LIMIT	200
#define NETPACKET_NPC_INTO_MAP_LIMIT		200
#define NETPACKET_DROPITEM_INTO_MAP_LIMIT	50
#define NETPACKET_PLANT_INTO_MAP_LIMIT		600
#define NETPACKET_TRAILER_INTO_MAP_LIMIT	150
#define NETPACKET_TRAP_INTO_MAP_LIMIT		600

int32_t DELTA_X[] = { 0, 1, 1, 1, 0, -1, -1,  -1 };
int32_t DELTA_Y[] = { 1, 1, 0, -1, -1, -1, 0,  1 };

Map::Map()
{
	bzero(&m_lastLocalNow, sizeof(m_lastLocalNow));
}

//Map::Map(const CfgMap &cfgmap, Kingdom *kingdom)
//	: m_cfgmap(cfgmap), m_kingdom(kingdom), 
//	m_widthTileCount(m_cfgmap.width/64), m_heightTileCount(roundInt(m_cfgmap.height/16.0)), m_widthAreaCount(m_cfgmap.width/AREA_WIDTH+1), m_heightAreaCount(m_cfgmap.height/AREA_HEIGHT+1), m_lastUpdateTime(0)
//{
//	//m_cfgActKingDom=m_kingdom->getId();
//}

Map::~Map()
{

}

Position Map::pixelToTile(int32_t px, int32_t py)
{
	int32_t tx = -1;
	int32_t ty = -1;

	//the center pixel of the rect with width 64, height 32 which px and py in
	int32_t rx = ((px>>6)<<6) + 32;
	int32_t ry = ((py>>5)<<5) + 16;

	if ( (abs(px-rx)<<4) + (abs(py-ry)<<5) < 32 * 16 ) //in the diamond..
	{
		tx = px >> 6;
		ty = ((py>>5)<<1);
	}
	else
	{
		tx = ((px-32)>>6) + 1;
		ty = (((py-16)>>5)<<1) + 1;
	}

	return Position(tx-(ty&1), ty);
}

Position Map::tileToPixel(int32_t tx, int32_t ty)
{
	//diamond
	int32_t px = (tx<<6)+32+((ty&1)<<5);
	int32_t py = (ty+1)<<4;
	return Position(px, py);

	//rectangle
// 	int32_t px = (tx<<5)+16;
// 	int32_t py = (ty<<5)+16;
// 
// 	return Position(px, py);
}

Direction Map::pixelDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty)
{
	double radians = atan2(static_cast<double>(ty-cy), static_cast<double>(tx-cx));
	double degrees = radians*180/PI;
	int direction = roundInt(degrees/45); //right as 0, down as 2, left as 4, up as 6...
	if (direction < 0)
	{
		direction += 8;
	}
	//direction -= 2;
	//if (direction < 0)
	//{
	//	direction += 8;
	//}
	switch( direction )
	{
	case 0:	return RIGHT;
	case 1: return DOWN_RIGHT;
	case 2: return DOWN;
	case 3: return DOWN_LEFT;
	case 4:	return LEFT;
	case 5: return UP_LEFT;
	case 6: return UP;
	case 7: return UP_RIGHT;
	default: break;
	}

	Direction dir = static_cast<Direction>(direction);
	if (dir == INVALID_DIRECTION)
	{
		LOG_ERROR("Map::pixelDirection return INVALID_DIRECTION with cx = %d, cy = %d, tx = %d, ty = %d\n", cx, cy, tx, ty);
	}

	return dir;
}

Direction Map::tileDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty)
{
	if (cx < 0 || cy < 0 || tx < 0 || ty < 0)
	{
		return INVALID_DIRECTION;
	}

	if (cx == tx && cy == ty)
	{
		return INVALID_DIRECTION;
	}

	if (cx==tx && cy-ty>1)
	{
		return UP;
	}
	if (cx==tx && ty-cy>1)
	{
		return DOWN;
	}
	if (cy==ty && tx>cx)
	{
		return RIGHT;
	}
	if (cy==ty && tx<cx)
	{
		return LEFT;
	}

	if (ty > cy)
	{
		if (tx>=cx && (tx-cx)==((ty-cy+(cy&1))>>1))
		{
			return DOWN_RIGHT;
		}
		if (tx<=cx && (cx-tx)==((ty-cy+((cy+1)&1))>>1))
		{
			return DOWN_LEFT;
		}
	}
	else
	{
		if (tx>=cx && (tx-cx)==((cy-ty+(cy&1))>>1))
		{
			return UP_RIGHT;
		}
		if (tx<=cx && (cx-tx)==((cy-ty+((cy+1)&1))>>1))
		{
			return UP_LEFT;
		}
	}

	return INVALID_DIRECTION;
}

Direction Map::UnitDirection( const Position& src, const Position& tar )
{
	Direction direction = Map::tileDirection( src.x, src.y, tar.x, tar.y);
	if ( direction == INVALID_DIRECTION )
	{
		Position srcPixel = Map::tileToPixel( src.x, src.y );
		Position tarPixel = Map::tileToPixel( tar.x, tar.y );
		direction = Map::pixelDirection( srcPixel.x,  srcPixel.y, tarPixel.x, tarPixel.y );
	}
	return direction;
}

Position Map::getAroundTile(int32_t tx, int32_t ty, Direction direction)
{
	switch (direction)
	{
	case DOWN: return Position(tx, ty+2);
	case DOWN_LEFT: return Position(tx-1+(ty&1), ty+1);
	case LEFT: return Position(tx-1, ty);
	case UP_LEFT: return Position(tx-1+(ty&1), ty-1);
	case UP: return Position(tx, ty-2);
	case UP_RIGHT: return Position(tx+(ty&1), ty-1);
	case RIGHT: return Position(tx+1, ty);
	case DOWN_RIGHT: return Position(tx+(ty&1), ty+1);
	default: return Position(tx, ty);
	}
}

void Map::init( const CfgMap &cfgmap )
{
	m_cfgmap = cfgmap;
	m_widthTileCount = m_cfgmap.width/64;
	m_heightTileCount = roundInt(m_cfgmap.height/16.0);
	m_widthAreaCount = m_cfgmap.width/AREA_WIDTH+1;
	m_heightAreaCount = m_cfgmap.height/AREA_HEIGHT+1;
	m_lastUpdateTime = 0;
	m_IsVipGuaJiMap = CFG_DATA.IsVipGuaJiMap( m_cfgmap.id );
	CfgMapMonsterVector *pMonsters = CFG_DATA.getMonstersOnMap(GetId());
	if (pMonsters != NULL)
	{
		for (CfgMapMonsterVector::iterator it = pMonsters->begin(); it != pMonsters->end(); ++it)
		{
			CfgMonster *pCfgMonster = CFG_DATA.getMonster(it->monsterid);
			if (pCfgMonster != NULL)
			{
				Monster *monster = new Monster;
				if (NULL == monster)
				{
					continue;
				}
				monster->init(*pCfgMonster, *it, NULL);
				if ( pCfgMonster->boss_sign == BOSS_TYPE_SPIDER_QUEEN || pCfgMonster->boss_sign == BOSS_TYPE_WORLD_BOSS )
				{
					if ( GAME_SERVICE.getLine() == 1 )
					{
						addMonster(monster, it->x, it->y);
						if ( pCfgMonster->boss_sign == BOSS_TYPE_SPIDER_QUEEN )
						{
							if ( !WORLDBOSS.IsInHuoDongTiem() )
							{
								monster->SetDieType( 1 );
								monster->AddHP( -1 * monster->GetHP() );
								WORLDBOSS.UpdateBossInfo( it->id, getNow(), 0, "", WORLDBOSS.GetSpiderQueenReviveTime() );
							}
							WORLDBOSS.AddMonst( monster );
						}
					}
				}
				else if ( pCfgMonster->mid == WAR_VICTORY_BOSS_ID )
				{
					addMonster(monster, it->x, it->y);
					if ( !WORLDBOSS.IsWarVictoryBossTime() )
					{
						monster->SetDieType( 1 );
						monster->AddHP( -1 * monster->GetHP() );
					}
					WORLDBOSS.AddWarVictoryBoss( monster );
				}
				else
				{
					addMonster(monster, it->x, it->y);
				}
			}
		}
	}

	const CfgNpcTable &allNpc = CFG_DATA.getNpcAll();
	for (CfgNpcTable::const_iterator it = allNpc.begin(); it != allNpc.end(); ++it)
	{
		if (it->second.findMapId(GetId()) && it->second.x > 0 && it->second.y > 0)
		{
			Npc *npc = new Npc;
			if (NULL == npc)
			{
				continue;
			}
			npc->init(it->second);
			addNpc(npc, it->second.x, it->second.y);		
		}
	}

	CfgMapPlantVector *pPlants = CFG_DATA.getPlantOnMap(GetId());
	if (pPlants != NULL)
	{
		for (CfgMapPlantVector::iterator it = pPlants->begin(); it != pPlants->end(); ++it)
		{
			CfgPlant *pCfgPlant = CFG_DATA.getPlant(it->plantid);
			if (pCfgPlant != NULL && pCfgPlant->type == PT_NORMAL)
			{
				Plant *plant = new Plant;
				if (NULL == plant)
				{
					continue;
				}
				plant->init(this, *pCfgPlant, *it);
				addPlant(plant);
			}
		}
	}
}

void Map::update()
{
	if ( !m_players.empty() || getLocalNow().tm_min != m_lastLocalNow.tm_min )
	{

		updatePlayers();

		updateMonsters();

		updateNpcs();

		updatePlants();

		updateDropItems();

		updateTraps();

		CheckVipGuaJiEnd();
		m_lastUpdateTime = getNow();
		m_lastLocalNow	 = getLocalNow();
	}
}

void Map::CheckVipGuaJiEnd()
{
	if ( !IsVipGuaJiMap() )
	{
		return;
	}
	tm localNow = getLocalNow();
	if ( localNow.tm_min != m_lastLocalNow.tm_min )
	{	
		VipGuaJiMap* pVipGuaJi = CFG_DATA.GetVipGuaJiMapCfg( GetId() );
		if ( NULL == pVipGuaJi )
		{
			return; 
		}
		int32_t NowSeconds	= localNow.tm_hour * 60 * 60 + localNow.tm_min * 60 + localNow.tm_sec;
		if ( NowSeconds <= pVipGuaJi->StartTime * 60 && NowSeconds >= pVipGuaJi->EndTime * 60 )
		{
			PlayerList players = m_players;
			for (PlayerList::iterator it = players.begin(); it != players.end(); ++it)
			{
				Player *player = *it;
				if (player != NULL)
				{
					player->LeaveVipGuaJiMap();
				}
			}
		}
	}
}

int32_t Map::canEnter(Player *player)
{
	if (player == NULL)
	{
		return ERR_INVALID_DATA;
	}
	//�жϵȼ�����
	if (player->getLevel() < m_cfgmap.player_level || player->getLevel() > m_cfgmap.player_level_max)
	{
		return ERR_MAP_PLAYER_LEVEL;
	}
	if ( IsVipGuaJiMap() )
	{
		VipGuaJiMap* pVipGuaJi = CFG_DATA.GetVipGuaJiMapCfg( GetId() );
		if ( NULL == pVipGuaJi )
		{
			return ERR_SYETEM_ERR; 
		}
		if ( player->GetPlayerVip().GetVipLevel() < pVipGuaJi->VipLevel )
		{
			return ERR_SYETEM_ERR;
		}
		if ( player->getPkValue() > PK_VALUE_WHITE )
		{
			return ERR_SYETEM_ERR;
		}
		tm localnow = getLocalNow();
		int32_t NowSeconds	= localnow.tm_hour * 60 * 60 + localnow.tm_min * 60 + localnow.tm_sec;
		if ( NowSeconds < pVipGuaJi->StartTime * 60 && NowSeconds > pVipGuaJi->EndTime * 60 )
		{
			return ERR_SYETEM_ERR;
		}
	}
	return ERR_OK;
}

int32_t Map::getPkMode() const
{
	return m_cfgmap.pk_mode;
}

bool Map::randomTransfer()
{
	return false;
}

bool Map::canRevive()
{
	return true;
}

void Map::onPlayerKilled( Player* pDier, Player *pKiller )
{

}

void Map::onPlayerDie(Player* dier)
{

}
void Map::onMonsterDie(Monster *monster, Player *player)
{
	//checkWorldBossActivityResult(monster,player);
}

int32_t Map::GetId() const
{
	return m_cfgmap.id;
}

int32_t Map::GetRunnerId() const
{
	return m_cfgmap.runnerId;
}

int32_t Map::GetType() const
{
	return m_cfgmap.type;
}

int32_t Map::getAntiProtect() const
{
	return m_cfgmap.anti_protect;
}

int32_t Map::getReive( Player* player )
{
	return m_cfgmap.revive;
}

int32_t Map::getHideMini()
{
	return m_cfgmap.hide_mini;
}

bool Map::IsActivityMap() const
{
	return false;
}

bool Map::IsDungeonMap() const
{
	return false;
}

bool Map::OnSitRevive( Player* player )
{
	return false;
}

bool Map::OnSafeRevive( Player* player )
{
	return false;
}

bool Map::CanUseXP() const
{
	return true;
}

bool Map::CanUsePet() const
{
	return true;
}

bool Map::IsFullXP() const
{
	return false;
}

bool Map::CanJump() const
{
	return m_cfgmap.jump >= 1;
}

//Kingdom* Map::getKingdom() const
//{
//	return m_kingdom;
//}

int64_t Map::getTick()
{
	return TIMER.GetTick();
}

int32_t Map::getNow()
{
	return TIMER.GetNow();
}

tm Map::getLocalNow()
{
	return TIMER.GetLocalNow();
}

Tile* Map::getTile(int32_t tx, int32_t ty)
{
	if (tx >= 0 && tx < m_widthTileCount && ty >= 0 && ty < m_heightTileCount)
	{
		Tile *pTile = TILE_MANAGER.getTiles(m_cfgmap.id);
		if (pTile != NULL)
		{
			return &(pTile[tx + ty*m_widthTileCount]);
		}
	}

	return NULL;
}

bool  Map::isWalkablePosition(int32_t tx, int32_t ty)
{
	if ( inStack( tx, ty ) )
	{
		return false;
	}
	if (tx >= 0 && tx < m_widthTileCount && ty >= 0 && ty < m_heightTileCount)
	{
		return  TILE_MANAGER.isWalkblePosition(m_cfgmap.id,tx,ty,m_cfgmap.width/64);
	}
	return false;
}

bool Map::inStack( int32_t tx, int32_t ty ) const
{
	if ( m_lstStack.empty() )
	{
		return false;
	}
	for ( PosList::const_iterator iter = m_lstStack.begin(); iter != m_lstStack.end(); ++iter )
	{
		if ( iter->x == tx && iter->y == ty )
		{
			return true;
		}
	}
	return false;
}

Position Map::getAreaByPos( const Position& pos )
{
	Position area;
	area.x = pos.x / AREA_WIDTH;
	area.y = pos.y / AREA_HEIGHT;

	return area;
}

int32_t Map::getViewAreaCount( int32_t nSize ) const
{
	return (2*nSize+1)*(2*nSize+1);
}

void Map::getViewAreas( const Position& pos, PositionVector& outAreas, int32_t nSize )
{
	Position area = getAreaByPos( pos );

	outAreas.reserve( getViewAreaCount( nSize ) );
	for (int32_t x = area.x-nSize; x <= area.x+nSize; ++x)
	{
		for (int32_t y = area.y-nSize; y <= area.y+nSize; ++y)
		{
			if ( x >= 0 && x < m_widthAreaCount && y >= 0 && y < m_heightAreaCount )
			{
				outAreas.push_back( Position( x, y ) );
			}
		}
	}
}

void Map::getNewAreas( const Position& oldPos, const Position& newPos, PositionVector& outAreas, int32_t nSize )
{
	Position oldArea = getAreaByPos( oldPos );
	Position newArea = getAreaByPos( newPos );
	if ( oldArea == newArea )
	{
		return;
	}

	PositionVector oldAreas;
	PositionVector newAreas;
	getViewAreas( oldPos, oldAreas, nSize );
	getViewAreas( newPos, newAreas, nSize );

	outAreas.reserve( getViewAreaCount( nSize ) );
	for ( PositionVector::iterator iter = newAreas.begin(); iter != newAreas.end(); ++iter )
	{
		Position& tmpArea = *iter;
		if ( std::find( oldAreas.begin(), oldAreas.end(), tmpArea ) == oldAreas.end() )
		{
			outAreas.push_back( tmpArea );
		}
	}
}

void Map::broadcastToAreas( NetPacket *packet, const PositionVector& areas )
{
	if ( NULL == packet || m_players.empty() )
	{
		packet->destroy();
		return;
	}

	Int16Vector indexes;
	for ( PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it )
	{
		Player *player = *it;
		if ( NULL == player )
		{
			continue;
		}

		if ( !inAreas( player, areas ) )
		{
			continue;
		}

		indexes.push_back( player->getGateIndex() );
	}

	if ( indexes.empty() )
	{
		packet->destroy();
		return;
	}

	broadcastToList( packet, indexes );
}

void Map::sendSelfEnterArea( Player* player, const Position& oldPos )
{
	if ( NULL == player )
	{
		return;
	}

	Position oldArea = getAreaByPos( oldPos );
	Position newArea = getAreaByPos( player->getCurrentPixel() );

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SELF_ENTER_AREA );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( oldArea.x );
	packet->writeInt32( oldArea.y );
	packet->writeInt32( newArea.x );
	packet->writeInt32( newArea.y );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void Map::getAreaUnits( const PositionVector& areas, UnitList& outUnits )
{
	// ������
	for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		Player *player = *it;
		if (player != NULL)
		{
			if ( !inAreas( player, areas ) )
			{
				continue;
			}

			// player
			outUnits.push_back(player);

			// ������ҵĳ���
			//player->GetCharPet().GetFightPet( outUnits );
		}
	}

	// ������
	for ( ObjPetList::iterator it = m_pets.begin(); it != m_pets.end(); ++it )
	{
		CObjPet * pPet = *it;
		if ( pPet != NULL )
		{
			if ( !inAreas( pPet, areas ) )
			{
				continue;
			}

			// player
			outUnits.push_back(pPet);
		}
	}

	// ������
	for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		Monster *monster = *it;
		if (monster != NULL && inAreas(monster, areas))
		{
			outUnits.push_back(monster);
		}
	}

	// ����ڳ�
	for (TrailerList::iterator it = m_trailers.begin(); it != m_trailers.end(); ++it)
	{
		Trailer *trailer = *it;
		if (trailer != NULL && inAreas(trailer, areas))
		{
			outUnits.push_back(trailer);
		}
	}
}

void Map::getAreaTargets( Unit &launcher, Position pos, CfgSkill *pCfg, UnitList& outUnits )
{
	if ( NULL == pCfg )
	{
		return;
	}
	int32_t nArea = pCfg->area;
	// ������
	for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		Monster *monster = *it;
		if ( monster != NULL && pos.tileDistance( monster->getCurrentTile() ) <= nArea && launcher.checkSkillTarget( pCfg, monster ) )
		{
			outUnits.push_back( monster );
		}
	}

	// ������
	for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		Player *player = *it;
		if ( player != NULL && pos.tileDistance( player->getCurrentTile() ) <= nArea && launcher.checkSkillTarget( pCfg, player ) )
		{
			outUnits.push_back( player );
		}
	}

	// ������
	for ( ObjPetList::iterator it = m_pets.begin(); it != m_pets.end(); ++it )
	{
		CObjPet* pPet = *it;
		if ( pPet != NULL && pos.tileDistance( pPet->getCurrentTile() ) <= nArea && launcher.checkSkillTarget( pCfg, pPet ) )
		{
			outUnits.push_back( pPet );
		}
	}

	// ����ڳ�
	for (TrailerList::iterator it = m_trailers.begin(); it != m_trailers.end(); ++it)
	{
		Trailer *trailer = *it;
		if ( trailer != NULL && pos.tileDistance( trailer->getCurrentTile() ) <= nArea && launcher.checkSkillTarget( pCfg, trailer ) )
		{
			outUnits.push_back( trailer );
		}
	}
}

NetPacket* Map::packageUnitEnterAreaBuff( const UnitList& inList )
{
	if ( inList.empty() )
	{
		return NULL;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_UNIT_BUFF_LIST );
	if ( NULL == packet )
	{
		return NULL;
	}

	int32_t nCount = 0;
	packet->writeInt32( static_cast<int32_t>( inList.size() ) );
	for ( UnitList::const_iterator it = inList.begin(); it != inList.end(); ++it )
	{
		Unit *pUnit = *it;
		if ( NULL == pUnit )
		{
			continue;
		}
		pUnit->PacketBuffList( packet );
		++nCount;
	}

	if ( 0 == nCount )
	{
		packet->destroy();
		return NULL;
	}

	uint32_t oldOffSet = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( oldOffSet );
	packet->setSize( packet->getWOffset() );

	return packet;
}

NetPacket* Map::packageUnitEnterArea( const UnitList& inList )
{
	if ( inList.empty() )
	{
		return NULL;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_UNIT_ENTER_AREA );
	if ( NULL == packet )
	{
		return NULL;
	}

	int32_t nCount = 0;
	packet->writeInt32( static_cast<int32_t>( inList.size() ) );
	for ( UnitList::const_iterator it = inList.begin(); it != inList.end(); ++it )
	{
		Unit *pUnit = *it;
		if ( NULL == pUnit )
		{
			continue;
		}

		packet->writeInt64( pUnit->getUnitId() );
		packet->writeInt8( pUnit->getType() );
		packet->writeInt32( pUnit->getCurrentPixel().x );
		packet->writeInt32( pUnit->getCurrentPixel().y );
		packet->writeInt16( static_cast<int16_t>( pUnit->getTargetTile().x ) );
		packet->writeInt16( static_cast<int16_t>( pUnit->getTargetTile().y ) );
		packet->writeInt32( pUnit->GetHP() );
		packet->writeInt32( pUnit->GetMaxHP() );
		packet->writeInt32( pUnit->GetMoveSpeed() );
		++nCount;
	}

	if ( 0 == nCount )
	{
		packet->destroy();
		return NULL;
	}

	uint32_t oldOffSet = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( oldOffSet );
	packet->setSize( packet->getWOffset() );

	return packet;
}

void Map::checkAreaChange( Unit *pUnit, const Position& oldPos )
{
	if ( pUnit == NULL || m_players.empty() )
	{
		return;
	}

	PositionVector newAreas;
	getNewAreas( oldPos, pUnit->getCurrentPixel(), newAreas );
	if ( newAreas.empty() )
	{
		return;
	}


	{// �������ڵ���ҷ��ͽ�����Ϣ
		UnitList self;
		self.push_back( pUnit );
		NetPacket *packet = packageUnitEnterArea( self );
		if ( packet != NULL )
		{
			broadcastToAreas( packet, newAreas );
		}
		NetPacket* packetBuff = packageUnitEnterAreaBuff( self );
		if ( NULL != packetBuff )
		{
			broadcastToAreas( packetBuff, newAreas );
		}
	}

	// ������������ң����������ڵĶ�����Ϣ�����
	Player *player = dynamic_cast<Player*>(pUnit);
	if ( player != NULL )
	{
		sendSelfEnterArea( player, oldPos );

		UnitList newUnits;
		getAreaUnits( newAreas, newUnits );

		NetPacket *packet = packageUnitEnterArea( newUnits );
		if ( packet != NULL )
		{
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
		}
		NetPacket* packetBuff = packageUnitEnterAreaBuff( newUnits );
		if ( NULL != packetBuff )
		{
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packetBuff );
		}
		player->setSyncToTeamFlag();
	}
}

void Map::addPlayer(Player *player, int32_t x, int32_t y)
{
	if (player != NULL && player->getGateIndex() > 0)
	{
		if (randomTransfer())
		{
			Position pos = getRandomWalkablePosition();
			if (pos.x > 0 && pos.y > 0)
			{
				x = pos.x;
				y = pos.y;
			}
		}
		else
		{
			int32_t specialRegion = 0;
			//���ֵ�λ��
			if (specialRegion != 0)
			{
				CfgMapRegion *pCfgRegion = CFG_DATA.getMapRegion(specialRegion);
				if (pCfgRegion != NULL)
				{
					Position pos = getRandomWalkablePositionInRegion(*pCfgRegion);
					if (pos.x > 0 && pos.y > 0)
					{
						x = pos.x;
						y = pos.y;
					}
				}
			}
		}

		player->setAtTile(this, x, y);

		sendEnterMap(player, x, y);

		for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			if (*it == player)
			{
				LOG_ERROR("Map::addPlayer player = %p, cid = %lld, cgindex = %d\n", player, player->getCid(), static_cast<int32_t>(player->getGateIndex()));
				return;
			}
		}

		m_players.push_front(player);

		sendPlayersInMap(player);
		sendPetsInMap( player );
		//sendActivityMapState(player);
		sendMonstersInMap(player);
		//sendActivityMonsterDamageInfoInMap(player);
		sendNpcsInMap(player);
		sendDropItemsInMap(player);
		sendPlantsInMap(player);
		sendTrailersInMap(player);
		sendTrapsInMap(player);
		SendStacksInMap( player );
		
		SendBuffList( player );
		
		player->broadcastBuffList();
		broadcastPlayerIntoMap(player);

		player->resetPkModeOnEnterMap(this);
		if ( !CanUseXP() )
		{
			player->GetCharSkill().ClearXP();
		}
		if ( !CanUsePet() )
		{
			player->GetCharPet().FreeAllFightPet( true );
		}
		else
		{
			player->GetCharPet().FightLastFightPet();
		}
		player->setSyncToTeamFlag();
		if ( CFG_DATA.IsBossHomeMap( GetId() ) )
		{
			player->SendBossHomeInfo( GetId() );
		}
	}
}

void Map::removePlayer(Player *player, bool islogout)
{
	if (player != NULL)
	{
		player->setAtTile( NULL, 0, 0 );	// ʹ����뿪��ǰ�߳�

		PlayerList::iterator it = m_players.begin();
		while (it != m_players.end())
		{
			if (*it == player)
			{
				if (islogout)
				{
					LOG_DEBUG("Map::removePlayer remove player = %p, cid = %lld from m_players\n", player, player->getCid());
				}
				it = m_players.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

Player* Map::getEnemySidePlayer(Monster *monster)
{
	if (monster == NULL || m_players.empty())
	{
		return NULL;
	}

	PlayerList players;
	for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		int32_t ndis=monster->getCurrentTile().tileDistance((*it)->getCurrentTile());
		int32_t mdis =monster->getViewRange();
		//int8_t nkingdom=(*it)->getKingdom();
		if ( (*it)->isAlive() && ndis<= mdis /*&&  nkingdom != monster->getKingdom()*/)
		{
			players.push_back(*it);
		}
	}

	if (players.empty())
	{
		return NULL;
	}

	int32_t index = RANDOM.generate(0, players.size()-1);

	PlayerList::iterator it = players.begin();
	for (int32_t i = 0; i < index && it != players.end(); ++i)
	{
		it++;
	}

	if (it == players.end())
	{
		return NULL;
	}

	return *it;
}

Unit* Map::GetNearestAliveEnemySideUnit( Monster *monster )
{
	Unit* pUnit = NULL;
	int32_t mdis = monster->getViewRange();
	if ( monster->getSide() == 0  )
	{
		if ( ( monster->getAITarget() & ( 1 << ET_PLAYER ) ) != 0 )
		{
			for ( PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it )
			{
				Player* pPlayer = *it;
				if ( NULL == pPlayer )
				{
					continue;
				}

				if ( !pPlayer->isAlive() )
				{
					continue;
				}

				int32_t ndis = monster->getCurrentTile().tileDistance( pPlayer->getCurrentTile() );
				if ( ndis <= mdis )
				{
					pUnit = pPlayer;
					mdis = ndis;
				}
			}
		}

		if ( ( monster->getAITarget() & ( 1 << ET_PET ) ) != 0 )
		{
			for ( ObjPetList::iterator it = m_pets.begin(); it != m_pets.end(); ++it )
			{
				CObjPet* pPet = *it;
				if ( NULL == pPet )
				{
					continue;
				}

				if ( !pPet->isAlive() )
				{
					continue;
				}

				int32_t ndis = monster->getCurrentTile().tileDistance( pPet->getCurrentTile() );
				if ( ndis <= mdis )
				{
					pUnit = pPet;
					mdis = ndis;
				}
			}
		}
	}

	if ( ( monster->getAITarget() & ( 1 << ET_MONSTER ) ) != 0 )
	{
		for ( MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it )
		{
			Monster* pMonster = *it;
			if ( NULL == pMonster )
			{
				continue;
			}

			if ( pMonster->getSide() == monster->getSide() )
			{
				continue;
			}

			if ( !pMonster->isAlive() )
			{
				continue;
			}

			int32_t ndis = monster->getCurrentTile().tileDistance( pMonster->getCurrentTile() );
			if ( ndis <= mdis )
			{
				pUnit = pMonster;
				mdis = ndis;
			}
		}
	}

	return pUnit;
}

void Map::addMonster(Monster *monster, int32_t x, int32_t y)
{
	if (monster != NULL)
	{
		monster->setAtTile(this, x, y);
		m_monsters.push_back(monster);
		broadcastMonsterIntoMap(monster);
		GAME_SERVICE.addMonster(monster);
	}
}

Monster* Map::getEnemySideMonster(Monster *monster)
{
	if (monster == NULL)
	{
		return NULL;
	}

	Monster *neareastMonster = NULL;
	int32_t nearestDistance = numeric_limits<int32_t>::max();

	for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		int32_t distance = monster->getCurrentTile().tileDistance((*it)->getCurrentTile());

		if ((*it)->isAlive() && (*it)->getSide() != monster->getSide() && distance <= monster->getViewRange() && distance < nearestDistance)
		{
			neareastMonster = *it;
			nearestDistance = distance;
		}
	}

	return neareastMonster;
}

void Map::addNpc(Npc *npc, int32_t x, int32_t y)
{
	if (npc != NULL)
	{
		npc->setAtTile(this, x, y);
		m_npcs.push_back(npc);
		broadcastNpcIntoMap(npc);
	}
}

Npc* Map::getNpc(EntityId_t id)
{
	for (NpcList::iterator it = m_npcs.begin(); it != m_npcs.end(); ++it)
	{
		if ((*it)->getUnitId() == id)
		{
			return *it;
		}
	}

	return NULL;
}

void Map::addDropItemGroup(CDropItemGroup *dropItemGroup)
{
	if (dropItemGroup != NULL)
	{
		m_dropItems.push_back(dropItemGroup);
		broadcastDropItemIntoMap(dropItemGroup);
	}
}

CDropItemGroup* Map::getDropItemGroup(EntityId_t dropid)
{
	for (DropItemGroupList::iterator it = m_dropItems.begin(); it != m_dropItems.end(); ++it)
	{
		if ((*it)->hasDropItem(dropid))
		{
			return *it;
		}
	}

	return NULL;
}

void Map::addPlant(Plant *plant)
{
	if (plant != NULL)
	{
		m_plants.push_back(plant);
		broadcastPlantIntoMap(plant);
	}
}

Plant* Map::getPlant(EntityId_t id)
{
	for (PlantList::iterator it = m_plants.begin(); it != m_plants.end(); ++it)
	{
		if ((*it)->getEntityId() == id)
		{
			return *it;
		}
	}

	return NULL;
}

void Map::removePlant(EntityId_t id)
{
	for (PlantList::iterator it = m_plants.begin(); it != m_plants.end(); ++it)
	{
		if ((*it)->getEntityId() == id)
		{
			m_plants.erase(it);
			break;
		}
	}
}

void Map::addTrailer(Trailer *trailer)
{
	if (trailer != NULL)
	{
		m_trailers.push_back(trailer);

		broadcastTrailerIntoMap(trailer);
	}
}

void Map::removeTrailer(Trailer *trailer)
{
	if (trailer != NULL)
	{
		m_trailers.remove(trailer);
	}
}

void Map::AddLittleHelper(CLittleHelper *pLittleHelper)
{
	if (pLittleHelper != NULL)
	{
		m_CLittleHelperList.push_back(pLittleHelper);
	}
}

void Map::removeLittleHelper(CLittleHelper *pLittleHelper)
{
	if (pLittleHelper != NULL)
	{
		m_CLittleHelperList.remove(pLittleHelper);
	}
}

CDropItem* Map::GetNearestDropItem(Unit *pUnit)
{
	// TODO: CDropItem doesn't expose position info directly.
	// This requires adding a position getter to CDropItemGroup.
	return NULL;
}

void Map::addPet( CObjPet* pet )
{
	if ( pet != NULL )
	{
		m_pets.push_back( pet );
		broadcastPetIntoMap( pet );
	}
}

void Map::removePet( CObjPet* pet )
{
	if ( pet != NULL )
	{
		m_pets.remove( pet );
	}
}

void Map::addTrap( Trap* trap )
{
	if ( trap != NULL )
	{
		m_traps.push_back( trap );
		broadcastTrapIntoMap( trap );
	}
}

void Map::removeTrap( Trap* trap )
{
	if ( trap != NULL )
	{
		m_traps.remove( trap );
	}
}

Trap* Map::getTrap( EntityId_t id )
{
	for ( TrapList::iterator iter = m_traps.begin(); iter != m_traps.end(); ++iter )
	{
		Trap* trap = *iter;
		if ( trap != NULL && trap->getEntityId() == id )
		{
			return trap;
		}
	}
	return NULL;
}

bool Map::inSafeRegion(const Position &pos)
{
	CfgMapRegionVector *pMapRegion = CFG_DATA.getRegionOnMap(GetId());
	if (pMapRegion == NULL)
	{
		return false;
	}

	for (CfgMapRegionVector::iterator it = pMapRegion->begin(); it != pMapRegion->end(); ++it)
	{
		if (it->type != RNT_SAFE && it->type != RNT_TRADE)
		{
			continue;
		}

		if ( pos.x >= it->min_x && pos.x <= it->max_x && pos.y >= it->min_y && pos.y <= it->max_y )
		{
			return true;
		}
	}

	return false;
}

UnitVector Map::getSkillTargets(Unit &launcher, Position pos, CfgSkill *pCfg)
{
	UnitVector targets;

	if ( NULL == pCfg )
	{
		return targets;
	}

	if (pCfg->range == SR_TEAM)
	{
		if ( launcher.getType() != ET_PLAYER )
		{
			return targets;
		}
		Player &player = dynamic_cast<Player&>(launcher);
		targets.push_back(&player);

		CharIdList members;
		player.GetCharTeam().GetTeamMembers( members );
		CharIdList::const_iterator iter = members.begin();
		CharIdList::const_iterator eiter = members.end();
		for ( ; iter != eiter; ++iter )
		{
			CharId_t nCid = *iter;
			if ( nCid == player.getCid() )
			{
				continue;
			}

			Player *pMember = GAME_SERVICE.getPlayer( nCid, GetRunnerId() );
			if ( pMember != NULL && pMember->getMap() == player.getMap() && pMember->getCurrentTile().tileDistance(player.getCurrentTile()) < 20 )
			{
				targets.push_back( pMember );
			}
		}
	}
	else
	{
		Position center = launcher.getCurrentTile();
		if ( pCfg->range == SR_AROUND && pCfg->self != STP_SELF && pCfg->self != STP_POS )
		{
			center = pos;
		}
		UnitList areaUnits;
		getAreaTargets( launcher, center, pCfg, areaUnits );
		Direction dir = launcher.getDirection();
		switch (pCfg->range)
		{
		case SR_LINE:
			{
				for ( UnitList::iterator it = areaUnits.begin(); it != areaUnits.end(); ++it)
				{
					Unit* pTarget = *it;
					if ( pTarget != NULL )
					{
						Direction tdir = Map::UnitDirection( center, pTarget->getCurrentTile() );
						if ( tdir != dir )
						{
							continue;
						}
						targets.push_back( pTarget );
					}
				}
			}
			break;
		case SR_AROUND:
			{
				for ( UnitList::iterator it = areaUnits.begin(); it != areaUnits.end(); ++it)
				{
					Unit* pTarget = *it;
					if ( pTarget != NULL )
					{
						targets.push_back( pTarget );
					}
				}
			}
			break;
		case SR_HALF_ROUND:
			{
				int32_t tx = DELTA_X[dir];
				int32_t ty = DELTA_Y[dir];

				for ( UnitList::iterator it = areaUnits.begin(); it != areaUnits.end(); ++it)
				{
					Unit* pTarget = *it;
					if ( pTarget != NULL )
					{
						Position tpos = pTarget->getCurrentTile();
						if ( ty == 0 )					// ����
						{
							if ( ( tpos.x - center.x ) * tx < 0 )
							{
								continue;
							}
						}
						else if ( tx == 0 )				// ����
						{
							if ( ( tpos.y - center.y ) * ty < 0 )
							{
								continue;
							}
						}
						else if ( tx > 0  )	
						{
							if ( ty > 0 )				// ����
							{
								if ( ( tpos.y - center.y ) + ( tpos.x - center.x ) * 2 < 0 )
								{
									continue;
								}
							}
							else if ( ty < 0 )			// ����
							{
								if ( ( tpos.y - center.y ) > ( tpos.x - center.x ) * 2 )
								{
									continue;
								}
							}
						}
						else if ( tx < 0  )
						{
							if ( ty < 0 )				// ����
							{
								if ( ( tpos.y - center.y ) + ( tpos.x - center.x ) * 2 > 0 )
								{
									continue;
								}
							}
							else if ( ty > 0 )			// ����
							{
								if ( ( tpos.y - center.y ) < ( tpos.x - center.x ) * 2 )
								{
									continue;
								}
							}
						}

						targets.push_back( pTarget );
					}
				}

			}
			break;
		default:
			break;
		}
	}

	if (static_cast<int32_t>(targets.size()) > pCfg->target_num)
	{
		random_shuffle(targets.begin(), targets.end());
		targets.resize(pCfg->target_num);
	}

	return targets;
}

bool Map::checkSkillTarget(Unit &launcher, Position pos, Unit &target, CfgSkill *pCfg)
{
	if (pCfg == NULL)
	{
		return false;
	}

	//if (pCfg->job == 12 && target.getType() == ET_PLAYER)
	//{
	//	return false;
	//}

	if (!launcher.checkSkillTarget(pCfg, &target))
	{
		return false;
	}

	bool bSuccess = false;

	if (launcher.getType() == ET_PLAYER && launcher.InDungeon() )
	{
		bSuccess = true;
	}
	else
	{
		int32_t distance = pos.tileDistance(target.getCurrentTile());
		switch (pCfg->range)
		{
		case SR_LINE:
		case SR_AROUND:
		case SR_HALF_ROUND:
		case SR_TEAM: 
			bSuccess = ( distance <= pCfg->area );
			break;
		default:
			break;
		}
	}
	return bSuccess;
}

bool Map::inRegion(const Position &pos, const CfgMapRegion &region)
{
	if (GetId() != region.mapid)
	{
		return false;
	}
	if ( pos.x >= region.min_x && pos.x <= region.max_x && pos.y >= region.min_y && pos.y <= region.max_y )
	{
		return true;
	}
	return false;
}

Position Map::getRandomWalkablePosition()
{
	return TILE_MANAGER.getRandomWalkablePosition(GetId());
}

Position Map::getRandomWalkablePositionInRegion(const CfgMapRegion &region)
{
	Position pos(-1, -1);

	//y���ֵ�Ƿ����
	if(region.min_y <0)return pos;
	if(region.max_y <region.min_y) return pos; 
	if(region.min_x <0)return pos;
	if(region.max_x <region.min_x) return pos;

	for (int32_t i = 0; i < 10; ++i) //max try 10 times
	{
		int32_t x = RANDOM.generate(region.min_x, region.max_x);
		int32_t y = RANDOM.generate(region.min_y, region.max_y);
		if ( isWalkablePosition( x, y ) )
		{
			pos.x = x;
			pos.y = y;
			break;
		}
	}

	return pos;
}

Position Map::getRandomWalkableAroundPosition(int32_t tx, int32_t ty)
{
	Position poses[25];
	int32_t count = 0;

	for (int32_t x = -2; x <= 2; ++x)
	{
		for (int32_t y = -4; y <= 4; ++y)
		{
			Position pos(tx+x, ty+y);
			if (pos.tileDistance(Position(tx, ty)) > 1)
			{
				if ( isWalkablePosition(tx+x, ty+y)&& count < 25)
				{
					poses[count++] = pos;
				}
			}
		}
	}

	if (count <= 0)
	{
		return Position(tx, ty);
	}
	else
	{
		return poses[RANDOM.generate(0, count-1)];
	}
}

void Map::sendEnterMap(Player *player, int32_t x, int32_t y)
{
	if (player != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ENTER_MAP);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(player->getCid());
		packet->writeInt32(GetRunnerId());
		packet->writeInt32(m_cfgmap.id);
		packet->writeInt32(x);
		packet->writeInt32(y);
		packet->writeInt32(GAME_SERVICE.getLine());
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
	}
}

void Map::sendPlayersInMap(Player *player)
{
	if ( NULL == player || m_players.empty() )
	{
		return;
	}

	PlayerList::iterator iter = m_players.begin();
	PlayerList::iterator eiter = m_players.end();
	while ( iter != eiter )
	{
		NetPacket *playerPacket = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_PLYAER_INTO_MAP);
		if ( NULL == playerPacket )
		{
			return;
		}

		int32_t playerCount = 0;
		playerPacket->writeInt32( playerCount );
		for ( ; iter != eiter; ++iter )
		{
			Player *mapPlayer = *iter;
			if ( NULL == mapPlayer )
			{
				continue;
			}

			mapPlayer->appendInfo(playerPacket);
			++playerCount;
			if ( playerCount >= NETPACKET_PLAYER_INTO_MAP_LIMIT )
			{
				++iter;
				break;
			}
		}

		if ( playerCount > 0 )
		{
			uint32_t oldwoffset = playerPacket->getWOffset();
			playerPacket->setWOffset( 0 );
			playerPacket->writeInt32( playerCount );
			playerPacket->setWOffset( oldwoffset );
			playerPacket->setSize( oldwoffset );
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), playerPacket );
		}
		else
		{
			playerPacket->destroy();
		}
	}
}

void Map::sendPetsInMap( Player* player )
{
	if ( NULL == player || m_pets.empty() )
	{
		return;
	}

	ObjPetList::iterator iter = m_pets.begin();
	ObjPetList::iterator eiter = m_pets.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_PET_INTO_MAP);
		if ( NULL == packet )
		{
			return;
		}

		int16_t nCount = 0;
		packet->writeInt16( nCount );
		for (; iter != eiter; ++iter )
		{
			CObjPet* pPet = *iter;
			if ( pPet != NULL )
			{
				if ( pPet->AppendInfo(packet) )
				{
					++nCount;
					if ( nCount >= NETPACKET_PET_INTO_MAP_LIMIT )
					{
						++iter;
						break;
					}
				}
			}
		}

		if ( nCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt16( nCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
		}
		else
		{
			packet->destroy();
		}
	}
}

void Map::sendMonstersInMap( Player *player )
{
	if ( NULL == player || m_monsters.empty() )
	{
		return;
	}

	MonsterList::iterator iter = m_monsters.begin();
	MonsterList::iterator eiter = m_monsters.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_MONSTER_INTO_MAP);
		if (NULL == packet)
		{
			return;
		}

		int32_t monsterCount = 0;
		packet->writeInt32(monsterCount);
		for ( ; iter != eiter; ++iter )
		{
			Monster *monster = *iter;
			if ( monster != NULL && monster->getState() != MS_GHOST )
			{
				monster->appendInfo( packet );
				++monsterCount;
				if ( monsterCount >= NETPACKET_MONSTER_INTO_MAP_LIMIT )
				{
					++iter;
					break;
				}
			}
		}

		if ( monsterCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt32( monsterCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( oldwoffset );
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
		}
		else
		{
			packet->destroy();
		}
	}
}

//void Map::sendActivityMonsterDamageInfoInMap(Player *player)
//{
//	if ( NULL == player || m_monsters.empty() )
//	{
//		return;
//	}
//
//	MonsterList::iterator iter = m_monsters.begin();
//	MonsterList::iterator eiter = m_monsters.end();
//	for ( ; iter != eiter; ++iter )
//	{
//		Monster* pMonster = *iter;
//		if ( pMonster != NULL && pMonster->isActivityMonster() )
//		{
//			MonsterActivity *pActivityMonster = static_cast<MonsterActivity*>( pMonster );
//			if ( pActivityMonster != NULL )
//			{
//				pActivityMonster->sendPlayerDamageInfo(player);
//			}
//		}
//	}
//}

void Map::sendNpcsInMap(Player *player)
{
	if ( NULL == player || m_npcs.empty() )
	{
		return;
	}

	NpcList::iterator iter = m_npcs.begin();
	NpcList::iterator eiter = m_npcs.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_NPC_INTO_MAP);
		if (NULL == packet)
		{
			return;
		}

		int32_t npcCount = 0;
		packet->writeInt32( npcCount );
		for ( ; iter != eiter; ++iter )
		{
			Npc *npc = *iter;
			if ( npc != NULL )
			{
				npc->appendInfo(packet);
				++npcCount;
				if ( npcCount >= NETPACKET_NPC_INTO_MAP_LIMIT )
				{
					++iter;
					break;
				}
			}
		}

		if ( npcCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt32( npcCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( oldwoffset );
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
		}
		else
		{
			packet->destroy();
		}
	}
}

void Map::sendDropItemsInMap(Player *player)
{
	if ( NULL == player || m_dropItems.empty() )
	{
		return;
	}

	DropItemGroupList::iterator iter = m_dropItems.begin();
	DropItemGroupList::iterator eiter = m_dropItems.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ADD_DROP_ITEM);
		if ( NULL == packet )
		{
			return;
		}

		int16_t nCount = 0;
		packet->writeInt16( nCount );
		for ( ; iter != eiter; ++iter )
		{
			CDropItemGroup *dropItemGroup = *iter;
			if ( dropItemGroup != NULL )
			{
				dropItemGroup->appendInfo( packet );
				++nCount;
				if ( nCount >= NETPACKET_DROPITEM_INTO_MAP_LIMIT )
				{
					++iter;
					break;
				}
			}
		}

		if ( nCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt16( nCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( oldwoffset );
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
		}
		else
		{
			packet->destroy();
		}
	}
}

void Map::sendPlantsInMap(Player *player)
{
	if ( NULL == player || m_plants.empty() )
	{
		return;
	}

	PlantList::iterator iter = m_plants.begin();
	PlantList::iterator eiter = m_plants.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ADD_PLANT);
		if (NULL == packet)
		{
			return;
		}

		int16_t plantCount = 0;
		packet->writeInt16(plantCount);
		for ( ; iter != eiter; ++iter )
		{
			Plant *plant = *iter;
			if ( plant != NULL && !plant->isCorpse() )
			{
				plant->appendInfo(packet);
				++plantCount;
				if ( plantCount >= NETPACKET_PLANT_INTO_MAP_LIMIT )
				{
					++iter;
					break;
				}
			}
		}

		if ( plantCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt16( plantCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
		}
		else
		{
			packet->destroy();
		}
	}
}

void Map::sendTrailersInMap( Player *player )
{
	if ( NULL == player || m_trailers.empty() )
	{
		return;
	}

	TrailerList::iterator iter = m_trailers.begin();
	TrailerList::iterator eiter = m_trailers.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TRAILER_INTO_MAP);
		if ( NULL == packet )
		{
			return;
		}

		int16_t trailerCount = 0;
		packet->writeInt16( trailerCount );
		for (; iter != eiter; ++iter )
		{
			Trailer* pTrailer = *iter;
			if ( pTrailer != NULL )
			{
				pTrailer->appendInfo(packet);
				++trailerCount;
				if ( trailerCount >= NETPACKET_TRAILER_INTO_MAP_LIMIT )
				{
					++iter;
					break;
				}
			}
		}

		if ( trailerCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt16( trailerCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
		}
		else
		{
			packet->destroy();
		}
	}
}

void Map::sendTrapsInMap( Player *player )
{
	if ( NULL == player || m_traps.empty() )
	{
		return;
	}

	TrapList::iterator iter = m_traps.begin();
	TrapList::iterator eiter = m_traps.end();
	while ( iter != eiter )
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_ADD_TRAP );
		if ( NULL == packet )
		{
			return;
		}

		int16_t trapCount = 0;
		packet->writeInt16( trapCount );
		for (; iter != eiter; ++iter )
		{
			Trap* pTrap = *iter;
			if ( pTrap != NULL )
			{
				pTrap->appendInfo(packet);
				++trapCount;
				if ( trapCount >= NETPACKET_TRAP_INTO_MAP_LIMIT )
				{
					++iter;
					break;
				}
			}
		}

		if ( trapCount > 0 )
		{
			uint32_t oldwoffset = packet->getWOffset();
			packet->setWOffset( 0 );
			packet->writeInt16( trapCount );
			packet->setWOffset( oldwoffset );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
		}
		else
		{
			packet->destroy();
		}
	}
}

void Map::sendTeamsInMap( Player *player )
{
	if ( NULL == player || m_players.empty() )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TEAMS_AROUND);
	if (NULL == packet)
	{
		return;
	}

	int32_t count = 0;
	packet->writeInt32( count );

	PlayerList::iterator iter = m_players.begin();
	PlayerList::iterator eiter = m_players.end();
	for ( ; iter != eiter; ++iter )
	{
		Player *player = *iter;
		if ( player != NULL && player->IsTeamLeader() )
		{
			packet->writeInt32( player->GetTeamId() );
			packet->writeInt64( player->getCid() );
			packet->writeInt8( player->GetCharTeam().GetMemberCount() );
			++count;
		}
	}

	int oldwoffset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( count );
	packet->setWOffset( oldwoffset );
	packet->setSize( oldwoffset );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void Map::broadcastPlayerIntoMap(Player *player)
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PLYAER_INTO_MAP );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(1);
	player->appendInfo(packet);
	packet->setSize(packet->getWOffset());
	broadcast(packet);
}

void Map::broadcastMonsterIntoMap(Monster *monster)
{
	if (monster != NULL)
	{
		monster->broadcastIntoMap();
	}
}

void Map::broadcastNpcIntoMap(Npc *npc)
{
	if ( NULL == npc )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_NPC_INTO_MAP);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(1);
	npc->appendInfo(packet);
	packet->setSize(packet->getWOffset());
	broadcast(packet);
}

void Map::broadcastDropItemIntoMap(CDropItemGroup *dropItemGroup)
{
	if ( NULL == dropItemGroup )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ADD_DROP_ITEM);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt16(1);
	dropItemGroup->appendInfo(packet);
	packet->setSize(packet->getWOffset());
	broadcast(packet);
}

void Map::broadcastPlantIntoMap(Plant *plant)
{
	if ( NULL == plant )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ADD_PLANT);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt16(1);
	plant->appendInfo(packet);
	packet->setSize(packet->getWOffset());
	broadcast(packet);
}

void Map::broadcastTrailerIntoMap(Trailer *trailer)
{
	if ( NULL == trailer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TRAILER_INTO_MAP);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt16(1);
	trailer->appendInfo(packet);
	packet->setSize(packet->getWOffset());
	broadcast(packet);
}

void Map::broadcastPetIntoMap( CObjPet *pet )
{
	if ( NULL == pet )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_PET_INTO_MAP);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt16(1);
	if ( pet->AppendInfo( packet ) )
	{
		packet->setSize(packet->getWOffset());
		broadcast(packet);
	}
	else
	{
		packet->destroy();
	}
}

void Map::broadcastTrapIntoMap( Trap *trap )
{
	if (trap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_ADD_TRAP );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(1);
		trap->appendInfo( packet );
		packet->setSize( packet->getWOffset() );
		broadcast( packet );
	}
}

//void Map::broadcastActivityEventDialog(int32_t evtId,int32_t actid)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_DIALOG);
//	packet->writeInt32(actid);
//	packet->writeInt32(evtId);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastPhenixAppear(int32_t x, int32_t y)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_PHENIX);
//	packet->writeInt32(APE_PHENIX_APPEAR);
//	packet->writeInt32(x);
//	packet->writeInt32(y);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastFengYuDroped(int32_t x, int32_t y)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_PHENIX);
//	packet->writeInt32(APE_FENGYU_DROPED);
//	packet->writeInt32(x);
//	packet->writeInt32(y);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastFengYuPicked(const std::string &name, int32_t x, int32_t y)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_PHENIX);
//	packet->writeInt32(APE_FENGYU_PICKED);
//	packet->writeUTF8(name);
//	packet->writeInt32(x);
//	packet->writeInt32(y);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastFengYuChangeOwner(const std::string &dier, const std::string &killer, int32_t x, int32_t y)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_PHENIX);
//	packet->writeInt32(APE_FENGYU_CHANGEOWNER);
//	packet->writeUTF8(dier);
//	packet->writeUTF8(killer);
//	packet->writeInt32(x);
//	packet->writeInt32(y);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastFengYuProtect(const std::string &name, int32_t killCount)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_PHENIX);
//	packet->writeInt32(APE_FENGYU_PROTECT);
//	packet->writeUTF8(name);
//	packet->writeInt32(killCount);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastSurvivalFirstKill(const std::string &name)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_SURVIVAL);
//	packet->writeInt32(ASE_FIRST_KILL);
//	packet->writeUTF8(name);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastSurvivalContinuousKill(const std::string &name, int32_t count)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_SURVIVAL);
//	packet->writeInt32(ASE_CONTINUOUS_KILL);
//	packet->writeUTF8(name);
//	packet->writeInt32(count);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastKingdomWarContinuousKill(const std::string &name, int32_t kingdom, int32_t count)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_KINGDOMWAR);
//	packet->writeInt32(AKWE_CONTINUOUS_KILL);
//	packet->writeUTF8(name);
//	packet->writeInt32(kingdom);
//	packet->writeInt32(count);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastKingdomWarKillFlag(const std::string &name, int32_t kingdom, int32_t loseKingdom)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_KINGDOMWAR);
//	packet->writeInt32(AKWE_KILL_FLAG);
//	packet->writeUTF8(name);
//	packet->writeInt32(kingdom);
//	packet->writeInt32(loseKingdom);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}
//
//void Map::broadcastKingdomWarKillMonster(const std::string &name, int32_t kingdom, const std::string &monster, int32_t loseKingdom)
//{
//	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ACTIVITY_EVENT);
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(AE_KINGDOMWAR);
//	packet->writeInt32(AKWE_KILL_MONSTER);
//	packet->writeUTF8(name);
//	packet->writeInt32(kingdom);
//	packet->writeUTF8(monster);
//	packet->writeInt32(loseKingdom);
//	packet->setSize(packet->getWOffset());
//	broadcast(packet);
//}

void Map::broadcast(Answer::NetPacket *inPacket)
{
	if (inPacket == NULL)
	{
		return;
	}

	if (m_players.empty())
	{
		inPacket->destroy();
		return;
	}

	uint32_t oldSize = inPacket->getSize();
	uint32_t addonSize = (m_players.size()+1)*(sizeof(int16_t));
	if (inPacket->rightShift(addonSize))
	{
		inPacket->writeInt16(static_cast<int16_t>(m_players.size()));
		for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			inPacket->writeInt16((*it)->getGateIndex());
		}
		inPacket->setSize(oldSize+addonSize);
		GAME_SERVICE.sendPacket(inPacket);
	}
	else
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(inPacket->getType(), inPacket->getProc(), (m_players.size()+1)*sizeof(int16_t) + inPacket->getSize());
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(static_cast<int16_t>(m_players.size()));
		for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			packet->writeInt16((*it)->getGateIndex());
		}
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacket(packet);
		inPacket->destroy();
	}
}

void Map::broadcastAreaAround(Answer::NetPacket *inPacket, Unit *pUnit)
{
	if (inPacket == NULL)
	{
		return;
	}

	if (m_players.empty() || pUnit == NULL)
	{
		inPacket->destroy();
		return;
	}

	if ( IsDungeonMap() || pUnit->needMapBroadcast())
	{
		broadcast(inPacket);
	}
	else
	{
		Position currentPos = pUnit->getCurrentPixel();
		if (currentPos.x <= 0 || currentPos.x > m_cfgmap.width || currentPos.y <= 0 || currentPos.y > m_cfgmap.height)
		{
			inPacket->destroy();
			return;
		}

		int32_t areaX = currentPos.x/AREA_WIDTH;
		int32_t areaY = currentPos.y/AREA_HEIGHT;

		int32_t minX = (areaX - 1) * AREA_WIDTH;
		int32_t maxX = (areaX + 2) * AREA_WIDTH;
		int32_t minY = (areaY - 1) * AREA_HEIGHT;
		int32_t maxY = (areaY + 2) * AREA_HEIGHT;

		Player *unitPlayer = dynamic_cast<Player*>(pUnit);

		Int16Vector indexes;
		for (PlayerList::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			Player *player = *it;
			if (player != NULL)
			{
				Position playerPos = player->getCurrentPixel();
				if (playerPos.x >= minX && playerPos.x < maxX && playerPos.y >= minY && playerPos.y < maxY)
				{
					indexes.push_back(player->getGateIndex());
				}
				else if (pUnit->getOwner() == player->getCid())
				{
					indexes.push_back(player->getGateIndex());
				}
				//else if (unitPlayer != NULL && unitPlayer->getTeam() != NULL && unitPlayer->getTeam() == player->getTeam())
				//{
				//	indexes.push_back(player->getGateIndex());
				//}
			}
		}

		broadcastToList(inPacket, indexes);
	}
}

void Map::broadcastToList(Answer::NetPacket *inPacket, const Int16Vector &indexes)
{
	if (inPacket == NULL)
	{
		return;
	}

	if (indexes.empty())
	{
		inPacket->destroy();
		return;
	}

	uint32_t oldSize = inPacket->getSize();
	uint32_t addonSize = (indexes.size()+1)*(sizeof(int16_t));
	if (inPacket->rightShift(addonSize))
	{
		inPacket->writeInt16(static_cast<int16_t>(indexes.size()));
		for (Int16Vector::const_iterator it = indexes.begin(); it != indexes.end(); ++it)
		{
			inPacket->writeInt16(*it);
		}
		inPacket->setSize(oldSize+addonSize);
		GAME_SERVICE.sendPacket(inPacket);
	}
	else
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(inPacket->getType(), inPacket->getProc(), (indexes.size()+1)*sizeof(int16_t) + inPacket->getSize());
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(static_cast<int16_t>(indexes.size()));
		for (Int16Vector::const_iterator it = indexes.begin(); it != indexes.end(); ++it)
		{
			packet->writeInt16(*it);
		}
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacket(packet);
		inPacket->destroy();
	}
}

int32_t Map::xAddHalfY(int32_t x, int32_t y)
{
	return x + y/2;
}

int32_t Map::xSubHalfY(int32_t x, int32_t y)
{
	return x - y/2;
}

//bool Map::isMultiVicegeneral()
//{
//	return m_cfgmap.isVicegeneral > 0;
//}
bool Map::isRunning()
{
	return false;
}

void Map::onPlantGather(int wava)
{
}

Position Map::firstLinePosition(Position src, Position dest)
{
	Position pos(-1, -1);

	PathFinder pathFinder(*this);
	PositionVector path = pathFinder.findPath(src, dest);

	if (path.size() >= 2)
	{
		int32_t direction = tileDirection(src.x, src.y, path[1].x, path[1].y);
		pos = path[1];

		for (size_t i = 2; i < path.size(); ++i)
		{
			if (tileDirection(path[i-1].x, path[i-1].y, path[i].x, path[i].y) != direction)
			{
				break;
			}

			pos = path[i];
		}
	}

	return pos;
}

bool Map::inAreas(Unit *pUnit, const PositionVector &areas)
{
	if (pUnit == NULL || pUnit->getMap() != this)
	{
		return false;
	}

	Position pos = pUnit->getCurrentPixel();
	for ( PositionVector::const_iterator it = areas.begin(); it != areas.end(); ++it )
	{
		if ( checkPos ( pos, *it ) )
		{
			return true;
		}
	}

	return false;
}

bool Map::checkPos( const Position& pos, const Position& area ) const
{
	int32_t nLeft = area.x * AREA_WIDTH;
	int32_t nRight = nLeft + AREA_WIDTH;
	int32_t nBottom = area.y * AREA_HEIGHT;
	int32_t nTop = nBottom + AREA_HEIGHT;
	if ( pos.x < nLeft || pos.x >= nRight || pos.y < nBottom || pos.y >= nTop )
	{
		return false;
	}

	return true;
}

void Map::updatePlayers()
{
	PlayerList players = m_players;
	for (PlayerList::iterator it = players.begin(); it != players.end(); ++it)
	{
		Player *player = *it;

		if (player != NULL)
		{
			if (player->getGateIndex() > 0)
			{
				player->update();
			}
			else
			{
				LOG_ERROR("Map::updatePlayers with player->getGateIndex() == %d\n", static_cast<int32_t>(player->getGateIndex()));
				removePlayer(player, true);
				GAME_SERVICE.removePlayer(player);
			}
		}
		else
		{
			LOG_ERROR("Map::updatePlayers with player == NULL\n");
		}
	}
}

int32_t Map::GetMapParam()
{
	return m_cfgmap.param;
}

void Map::updateMonsters()
{
	//for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end();)
	//{
	//	Monster *monster = *it;
	//	if (monster != NULL && monster->isLifeEnd())
	//	{
	//		if (monster->getBroadcast() != 0)
	//		{
	//			MonsterBroadcast monsterBroadcast;
	//			monsterBroadcast.mid = monster->getMid();
	//			monsterBroadcast.state = MBS_INACTIVE;
	//			monsterBroadcast.last_killer = "";
	//			monsterBroadcast.next_revive = 0;
	//			monsterBroadcast.kingdom = GetRunnerId();
	//			GAME_SERVICE.updateMonsterBroadcast(monsterBroadcast);
	//		}
	//		if (monster->isAlive())
	//		{
	//			checkWorldBossActivityResult(monster,NULL);
	//		}
	//		monster->leaveMap();
	//		m_monsters.erase(it++);
	//		GAME_SERVICE.removeMonster(monster);
	//		POOL_MANAGER.push<MonsterActivity>( dynamic_cast<MonsterActivity*>( monster ) );
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}

	for (MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); )
	{
		Monster *monster = *it;
		if ( NULL == monster )
		{
			m_monsters.erase( it++ );
			continue;
		}

		monster->update();
		if ( monster->needDel() )
		{
			monster->destroy();
			m_monsters.erase( it++ );
			continue;
		}
		++it;
	}
}

void Map::updateNpcs()
{
	for (NpcList::iterator it = m_npcs.begin(); it != m_npcs.end();)
	{
		Npc *npc = *it;
		if (npc != NULL && npc->isLifeEnd())
		{
			npc->leaveMap();
			m_npcs.erase(it++);
			POOL_MANAGER.push<NpcActivity>( dynamic_cast<NpcActivity*>( npc ) );
		}
		else
		{
			++it;
		}
	}
}

void Map::updatePlants()
{
	//for (PlantList::iterator it = m_plants.begin(); it != m_plants.end();)
	//{
	//	Plant *plant = *it;
	//	if (plant != NULL && plant->isLifeEnd())
	//	{
	//		plant->broadcastRemove();
	//		m_plants.erase(it++);
	//		POOL_MANAGER.push<PlantActivity>( dynamic_cast<PlantActivity*>( plant ) );
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}

	for (PlantList::iterator it = m_plants.begin(); it != m_plants.end(); ++it)
	{
		Plant *plant = *it;
		if (plant != NULL && plant->isCorpse() && plant->checkRevive())
		{
			plant->revive();
		}
	}
}

void Map::updateDropItems()
{
	for (DropItemGroupList::iterator it = m_dropItems.begin(); it != m_dropItems.end();)
	{
		CDropItemGroup *dropItemGroup = *it;
		if (dropItemGroup != NULL && dropItemGroup->checkEnd())
		{
			dropItemGroup->leaveMap();
			m_dropItems.erase(it++);
			POOL_MANAGER.push<CDropItemGroup>( dropItemGroup );
		}
		else
		{
			++it;
		}
	}
}

void Map::updateTraps()
{
	for ( TrapList::iterator it = m_traps.begin(); it != m_traps.end(); ++it )
	{
		(*it)->checkState();
	}
}

int32_t Map::GetWidthTileCount()
{
	return m_widthTileCount;
}

int32_t Map::GetHeightTileCount()
{
	return m_heightTileCount;
}

void Map::SendStacksInMap( Player *player )
{
	if ( NULL == player || m_lstStack.empty() )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_STACKS_ADD_INTO_MAP );
	if ( NULL == packet )
	{
		return;
	}

	appendStack( packet, m_lstStack );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
}

void Map::SendBuffList( Player* player )
{
	if ( NULL == player )
	{
		return;
	}
	PositionVector OutAreas;
	UnitList outUnits;
	getViewAreas( player->getCurrentPixel(), OutAreas );
	getAreaUnits( OutAreas, outUnits );
	if ( outUnits.size() > 0 )
	{
		UnitList::iterator it = outUnits.begin();
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_UNIT_BUFF_LIST);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( outUnits.size() );
		for ( ; it != outUnits.end(); ++it )
		{
			(*it)->PacketBuffList( packet );
		}
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
	}
}

void Map::appendStack( Answer::NetPacket *packet, const PosList& posList )
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt16( posList.size() );
	PosList::const_iterator iter = posList.begin();
	PosList::const_iterator eiter = posList.end();
	for (; iter != eiter; ++iter )
	{
		packet->writeInt16( iter->x );
		packet->writeInt16( iter->y );
	}
}

void Map::AddStack( const PosList& posList )
{
	for ( PosList::const_iterator iter = posList.begin(); iter != posList.end(); ++iter )
	{
		m_lstStack.push_back( *iter );
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_STACKS_ADD_INTO_MAP );
	if ( NULL == packet )
	{
		return;
	}

	appendStack( packet, posList );
	packet->setSize( packet->getWOffset() );
	broadcast( packet );
}

void Map::RemoveStack( const PosList& posList )
{
	for ( PosList::const_iterator iter = posList.begin(); iter != posList.end(); ++iter )
	{
		removeStack( *iter );
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_STACKS_REMOVE_FROM_MAP );
	if ( NULL == packet )
	{
		return;
	}

	appendStack( packet, posList );
	packet->setSize( packet->getWOffset() );
	broadcast( packet );
}

void Map::removeStack( const Position& pos )
{
	for ( PosList::iterator iter = m_lstStack.begin(); iter != m_lstStack.end(); ++iter )
	{
		if ( *iter == pos )
		{
			m_lstStack.erase( iter );
			break;
		}
	}
}

bool Map::IsVipGuaJiMap()
{
	return m_IsVipGuaJiMap;
}

void Map::OnStartMoLingRuQin( int32_t EndTime )
{
	CfgMoLingRuQinMapInfo* pMoLingRuQin = CFG_DATA.GetMLRQMapInfo(  GetId() );
	if ( NULL == pMoLingRuQin )
	{
		return;
	}

	const CfgNpc* pNpc = CFG_DATA.getNpc( pMoLingRuQin->NpcId );
	if( NULL == pNpc )
	{
		return;
	}
	srand( TIMER.GetNow());
	std::vector<Position> PosVector = pMoLingRuQin->m_RevivePosVector;
	std::random_shuffle(PosVector.begin(),PosVector.end());
	int32_t nSize	= PosVector.size();
	int32_t nFlush	= 0;
	for ( int32_t i = 0; i < pMoLingRuQin->NpcCount; i++ )
	{
		if ( nFlush >= nSize )
		{
			return;
		}
		Npc *npc = new Npc;
		if (NULL == npc)
		{
			continue;
		}
		npc->init(*pNpc,EndTime);
		addNpc(npc, PosVector[nFlush].x, PosVector[nFlush].y);	
		nFlush++;
	}
}

void Map::removeNpc( EntityId_t npcid )
{
	for (NpcList::iterator it = m_npcs.begin(); it != m_npcs.end(); ++it)
	{
		if ( (*it)->getEntityId() == npcid )
		{
			(*it)->leaveMap();
			m_npcs.erase(it);
			break;
		}
	}
}

void Map::OnKillMonster( EntityId_t MonsterId )
{
	for ( MonsterList::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it )
	{
		if ( (*it)->getEntityId() == MonsterId )
		{
			(*it)->leaveMap();
			(*it)->SetDieType( 1 );
			(*it)->AddHP( -1 * ( *it )->GetHP() );
			break;
		}
	}
}