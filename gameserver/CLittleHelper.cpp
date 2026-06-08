#include "stdafx.h"
#include "CLittleHelper.h"
#include "Map.h"
#include "MapManager.h"
#include "CfgData.h"
#include "DropItem.h"
#include "GameService.h"
#include "Timer.h"
#include "Player.h"

using namespace Answer;

CLittleHelper::CLittleHelper()
    : Unit( EntityType::ET_LITTLE_HELPER )
{
    reset();
}

CLittleHelper::~CLittleHelper()
{
}

EntityId_t CLittleHelper::getUnitId() const
{
    return getEntityId();
}

CharId_t CLittleHelper::getOwner() const
{
    return m_pPlayer ? m_pPlayer->getCid() : 0;
}

int32_t CLittleHelper::getLevel() const
{
    return m_pPlayer ? m_pPlayer->getLevel() : 0;
}

int32_t CLittleHelper::getBattle() const
{
    return 0;
}

void CLittleHelper::postDamage(int32_t damage, UnitHandle launcher)
{
}

void CLittleHelper::reset()
{
    m_pPlayer = NULL;
    m_LittleHelperId = 0;
    m_Clothes = 0;
    m_nStandPlace = Direction::LEFT;
    m_nState = LHS_REST;
    m_WorkState = LHWS_AWAY_FROM_MAP;
    m_TarDropId = 0;
    m_PickTick = 0;
    m_LastTick = 0;
    m_nLastWorkCheckTick = 0;
}

void CLittleHelper::refresh()
{
    if ( m_nState != LHS_WORK )
        return;
    if ( !m_pPlayer || !m_pPlayer->isAlive() )
        return;
    CheckSwitchMap();
    updateState();
}

bool CLittleHelper::appendInfo( Answer::NetPacket *packet )
{
    if ( !m_pPlayer || !packet )
        return false;
    packet->writeInt8( (int8_t)getType() );
    packet->writeInt64( getEntityId() );
    packet->writeInt64( m_pPlayer->getCid() );
    packet->writeUTF8( m_pPlayer->getName() );
    packet->writeInt32( m_LittleHelperId );
    packet->writeInt32( m_Clothes );
    packet->writeInt16( getCurrentTile().x );
    packet->writeInt16( getCurrentTile().y );
    packet->writeInt16( getTargetTile().x );
    packet->writeInt16( getTargetTile().y );
    return true;
}

void CLittleHelper::init( Player* pPlayer, int32_t nLittleHelperId, int32_t nClothes )
{
    m_pPlayer = pPlayer;
    m_LittleHelperId = nLittleHelperId;
    m_Clothes = nClothes;
    m_nStandPlace = Direction::LEFT;
    m_nState = LHS_REST;
    AddAttr();
}

void CLittleHelper::AddAttr()
{
    LittleHelperCfg* pCfg = CFG_DATA.GetLittleHelperCfg( m_LittleHelperId );
    if ( pCfg )
        SetAttrValue( CObjAttrs::ATTR_MOVE_SPEED, pCfg->nSpeed );
}

void CLittleHelper::EnterMap()
{
    if ( !m_pPlayer )
        return;
    Map* pMap = (Map*)m_pPlayer->getMap();
    if ( !pMap )
        return;
    Direction dir = m_pPlayer->getDirection();
    int32_t x = m_pPlayer->getCurrentTile().x;
    int32_t y = m_pPlayer->getCurrentTile().y;
    Position targetTile = getFollowTile( x, y, dir );
    setAtTile( pMap, targetTile.x, targetTile.y );
    pMap->AddLittleHelper( this );
    m_WorkState = LHWS_STAND;
}

void CLittleHelper::LeaveMap()
{
    if ( m_pMap )
    {
        m_WorkState = LHWS_AWAY_FROM_MAP;
        broadcastLeave();
        ((Map*)m_pMap)->removeLittleHelper( this );
        m_pMap = NULL;
    }
}

void CLittleHelper::OnLogout()
{
    if ( m_pPlayer && m_pMap )
        LeaveMap();
}

void CLittleHelper::CheckSwitchMap()
{
    if ( !m_pPlayer )
        return;
    Map* pMap = (Map*)m_pPlayer->getMap();
    if ( pMap && m_pPlayer->isAlive() && m_pMap != pMap )
    {
        LeaveMap();
        EnterMap();
    }
}

void CLittleHelper::ChangeClothe( int32_t nClotheId )
{
    m_Clothes = nClotheId;
    SynsAreaAround();
}

void CLittleHelper::ChangeLittleHelperId( int32_t nLittleHelperId, int32_t nClotheId )
{
    m_LittleHelperId = nLittleHelperId;
    m_Clothes = nClotheId;
    AddAttr();
    SynsAreaAround();
}

void CLittleHelper::SynsAreaAround()
{
    if ( !m_pPlayer || !m_pMap )
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_LITTLE_HELPER_SYNS );
    if ( packet )
    {
        packet->writeInt64( getEntityId() );
        packet->writeInt32( m_LittleHelperId );
        packet->writeInt32( m_Clothes );
        packet->setSize( packet->getWOffset() );
        ((Map*)m_pMap)->broadcastAreaAround( packet, this );
    }
}

void CLittleHelper::updateState()
{
    int64_t curTick = getTick();
    if ( curTick - m_LastTick <= 199 )
        return;
    m_LastTick = curTick;
    switch ( m_WorkState )
    {
    case LHWS_FOLLOW:
        onFollow();
        break;
    case LHWS_WALK_PICK:
        onWalkPick();
        break;
    case LHWS_PICK:
        onPick();
        break;
    case LHWS_STAND:
        onStand();
        break;
    default:
        break;
    }
    checkFarAway();
}

void CLittleHelper::checkFarAway()
{
    if ( !m_pPlayer || m_nState == 3 )
        return;
    Position pos = m_pPlayer->getCurrentTile();
    Position curTile = getCurrentTile();
    if ( curTile.tileDistance( pos ) > 15 )
    {
        Direction dir = m_pPlayer->getDirection();
        int32_t x = m_pPlayer->getCurrentTile().x;
        int32_t y = m_pPlayer->getCurrentTile().y;
        Position targetTile = getFollowTile( x, y, dir );
        instantMove( targetTile.x, targetTile.y, IMR_LITTLE_HELPER );
        m_WorkState = LHWS_STAND;
        if ( m_pPlayer->isMoving() )
        {
            ResetTargetTile(
                m_pPlayer->getTargetTile().x,
                m_pPlayer->getTargetTile().y,
                m_pPlayer->getDirection() );
        }
    }
}

void CLittleHelper::ResetTargetTile( int32_t tx, int32_t ty, Direction dir )
{
    if ( !m_pMap )
        return;
    if ( m_WorkState != LHWS_STAND && m_WorkState != LHWS_FOLLOW )
        return;
    Position targetTile = getFollowTile( tx, ty, dir );
    if ( ((Map*)m_pMap)->isWalkablePosition( targetTile.x, targetTile.y ) )
        setTargetTile( targetTile.x, targetTile.y );
    else
        setTargetTile( tx, ty );
    broadcastMove();
    m_WorkState = LHWS_FOLLOW;
}

void CLittleHelper::onStand()
{
    if ( m_pPlayer && m_pMap )
        ChangeTarget();
}void CLittleHelper::ChangeTarget()
{
	if ( !m_pMap || !m_pPlayer )
		return;
	// Scan nearby drop items and pick the nearest one
	Position dropPos;
	EntityId_t dropId = 0;
	if ( ((Map*)m_pMap)->GetNearestDropPos( this, dropPos, dropId ) )
	{
		m_TarDropId = dropId;
		setTargetTile( dropPos.x, dropPos.y );
		broadcastMove();
		m_WorkState = LHWS_WALK_PICK;
	}
	else
	{
		m_TarDropId = 0;
		m_WorkState = LHWS_STAND;
	}
}

void CLittleHelper::onFollow()
{
    if ( !m_pPlayer || !m_pMap )
        return;
    Position param = getTargetTile();
    Position curTile = getCurrentTile();
    if ( curTile.x == param.x && curTile.y == param.y )
        m_WorkState = LHWS_STAND;
}void CLittleHelper::onWalkPick()
{
	if ( !m_pPlayer || !m_pMap )
		return;
	if ( !m_TarDropId )
	{
		m_WorkState = LHWS_STAND;
		return;
	}
	Position param = getTargetTile();
	Position curTile = getCurrentTile();
	if ( curTile.x == param.x && curTile.y == param.y )
	{
		m_WorkState = LHWS_PICK;
		m_PickTick = m_pPlayer->getTick();
	}
}

void CLittleHelper::onPick()
{
	if ( !m_pPlayer || !m_pMap )
		return;
	if ( m_pPlayer->getTick() - m_PickTick <= 400 )
		return;
	// Pick up the drop item using CDropItemGroup::pick
	CDropItemGroup* pGroup = ((Map*)m_pMap)->getDropItemGroup( m_TarDropId );
	if ( pGroup != NULL )
	{
		pGroup->pick( *m_pPlayer, m_TarDropId );
	}
	m_TarDropId = 0;
	m_WorkState = LHWS_STAND;
}

Position CLittleHelper::getFollowTile( int32_t tx, int32_t ty, Direction dir )
{
    Position pos = Position(tx, ty);
    switch ( dir )
    {
    case Direction::UP:
        pos.y = ty + (int32_t)m_nStandPlace;
        break;
    case Direction::DOWN:
        pos.y = ty - (int32_t)m_nStandPlace;
        break;
    case Direction::LEFT:
        pos.x = tx - (int32_t)m_nStandPlace;
        break;
    case Direction::RIGHT:
        pos.x = tx + (int32_t)m_nStandPlace;
        break;
    default:
        pos.x = tx - 1;
        break;
    }
    return pos;
}
