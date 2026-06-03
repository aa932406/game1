#include "stdafx.h"

#include "GameService.h"
#include "Map.h"
#include "Player.h"
#include "Trailer.h"
#include "PoolManager.h"

Trailer::Trailer()
	: Unit(ET_TRAILER),  m_player(NULL), m_tid(0),  m_endMapId(0), m_endX(0), m_endY(0), m_endTime(0)
{

}

Trailer::~Trailer()
{

}

void Trailer::refresh()
{
	checkEnd();
}

EntityId_t Trailer::getUnitId() const
{
	return getEntityId();
}

CharId_t Trailer::getOwner() const
{
	if (m_player != NULL)
	{
		return m_player->getCid();
	}
	else
	{
		return 0;
	}
}

int32_t Trailer::getLevel() const
{
	return m_cfgTrailer.level;
}

int32_t	Trailer::getBattle() const
{
	return 0;
}

void Trailer::postDamage(int32_t damge, UnitHandle launcher)
{
	if (!isAlive())
	{
		if (launcher.type == ET_PLAYER)
		{
			Player *killer = GAME_SERVICE.getPlayer( launcher.id, GetRunnerId() );
			if (killer != NULL)
			{
				if (killer->getRecord(PR_KILL_TRAILER_COUNT) < 3)
				{
					int32_t exp = 0;/*m_player->getTrailerKilledLostExp();*/
					if (exp > 0)
					{
						killer->addExp(static_cast<int64_t>(exp));
						killer->updateRecord(PR_KILL_TRAILER_COUNT, killer->getRecord(PR_KILL_TRAILER_COUNT)+1);
						//killer->sendChrRecord();
					}
				}
			}
		}
	}
}

void Trailer::init(const CfgTrailer &cfgTrailer, Player *player, int32_t tid, int32_t endMapId, int32_t endX, int32_t endY, int32_t timeOut, int32_t hp)
{

	m_cfgTrailer = cfgTrailer;
	m_player = player;
	m_tid = tid;

	m_endMapId = endMapId;
	m_endX = endX;
	m_endY = endY;
	m_endTime = timeOut;

	//m_secondAttr.pdef = cfgTrailer.pdef;
	//m_secondAttr.mdef = cfgTrailer.mdef;
	//m_secondAttr.maxhp = cfgTrailer.maxhp;
	//m_secondAttr.sp = cfgTrailer.sp;

	//m_unitAttr.hp = cfgTrailer.maxhp;

	SetAttrValue( CObjAttrs::ATTR_PHY_DEF,		cfgTrailer.pdef );
	SetAttrValue( CObjAttrs::ATTR_MAG_DEF,		cfgTrailer.pdef );
	SetAttrValue( CObjAttrs::ATTR_HP,		cfgTrailer.maxhp );
	SetAttrValue( CObjAttrs::ATTR_MOVE_SPEED,	cfgTrailer.sp );

	FillHP();
}

void Trailer::reset()
{
	Unit::reset();

	m_player = NULL;
	m_tid = 0;
	m_endMapId = 0;
	m_endX = 0;
	m_endY = 0;
	m_endTime = 0;
}

void Trailer::appendInfo(Answer::NetPacket *packet)
{
	if (m_player == NULL || packet == NULL)
	{
		return;
	}

	packet->writeInt64(getUnitId());
	packet->writeInt64(m_player->getCid());
	packet->writeUTF8(m_player->getName());
	packet->writeInt32(m_cfgTrailer.id);
	packet->writeInt16(getCurrentTile().x);
	packet->writeInt16(getCurrentTile().y);
	packet->writeInt16(getTargetTile().x);
	packet->writeInt16(getTargetTile().y);
	packet->writeInt32( GetHP() );
	packet->writeInt32( GetMaxHP() );
	packet->writeInt32( GetMoveSpeed() );
}

Player* Trailer::getPlayer()
{
	return m_player;
}

int32_t Trailer::move(int32_t mapID,int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t finalX, int16_t finalY, Direction direction)
{
	if (m_player == NULL || m_pMap == NULL || m_pMap != m_player->getMap() || m_pMap->GetId() != mapID)
	{
		return ERR_INVALID_DATA;
	}

	Tile *pCurrentTile = m_pMap->getTile(currentX, currentY);
	Tile *pTargetTile = m_pMap->getTile(targetX, targetY);
	Tile *pFinalTile = m_pMap->getTile(finalX, finalY);

	if (pCurrentTile == NULL || pTargetTile == NULL || pFinalTile == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if (Position(currentX, currentY).tileDistance(Position(finalX, finalY)) > 20)
	{
		return ERR_INVALID_DATA;
	}

	setAtTile(m_pMap, currentX, currentY);
	
	setTargetTile(targetX, targetY);
	
	broadcastMove();

	return ERR_OK;
}

void Trailer::leaveMap()
{
	if (m_pMap != NULL)
	{
		m_pMap->removeTrailer(this);
		broadcastLeave();
	}
}

void Trailer::onLogout()
{
	if (m_player == NULL)
	{
		return;
	}

	m_player->updateRecord(PR_TRAILER_KINGDOM, GetRunnerId());
	m_player->updateRecord(PR_TRAILER_MAPID, getMapId());
	m_player->updateRecord(PR_TRAILER_X, getCurrentTile().x);
	m_player->updateRecord(PR_TRAILER_Y, getCurrentTile().y);
	m_player->updateRecord(PR_TRAILER_HP, GetHP() );
	m_player->updateRecord(PR_TRAILER_END_TIME, m_endTime);

	leaveMap();
	GAME_SERVICE.removeTrailer(this);
	POOL_MANAGER.push<Trailer>( this );
}

void Trailer::quickTask()
{
	leaveMap();
	m_player->setTrailer(NULL);
	GAME_SERVICE.removeTrailer(this);
	POOL_MANAGER.push<Trailer>( this );
}

void Trailer::checkSwitchMap()
{
	if (m_player == NULL || m_pMap == NULL)
	{
		return;
	}

	Map *pMap = m_player->getMap();
	if (pMap == NULL)
	{
		return;
	}

	if (pMap != m_pMap)
	{
		leaveMap();
		Position targetTile = Map::getAroundTile(m_player->getCurrentTile().x, m_player->getCurrentTile().y, UP_LEFT);
		setAtTile(pMap, targetTile.x, targetTile.y);
		pMap->addTrailer(this);

		clearFans();
		addFans(m_player->getGateIndex());
	}
}

void Trailer::checkEnd()
{
	if (getNow() > m_endTime)
	{
	   m_player->kingdomTaskFaile();
	}
	else if (m_pMap != NULL && m_pMap->GetId() == m_endMapId && getCurrentTile().tileDistance(Position(m_endX, m_endY)) <= 10)
	{
		m_player->updateRecord( PR_TRAILER_HP, GetHP() );
		m_player->setKingdomTaskState(m_tid,TS_CAN_SUBMIT);
	}
	else
	{
		return;
	}
	leaveMap();
	m_player->setTrailer(NULL);
	GAME_SERVICE.removeTrailer(this);
	POOL_MANAGER.push<Trailer>( this );
}

