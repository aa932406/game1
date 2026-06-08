#include "stdafx.h"

#include "GameService.h"
//#include "Kingdom.h"
#include "Map.h"
#include "PersistBuff.h"
#include "Skill.h"
#include "Unit.h"
#include "PoolManager.h"
#include "Timer.h"
#include <limits>

using namespace Answer;

Unit::Unit(EntityType entitytype)
	: Entity(entitytype)
{
	bzero(m_buffs, sizeof(m_buffs));
	reset();
}

Unit::~Unit()
{

}

UnitHandle Unit::getHandle()
{
	return UnitHandle(getUnitId(), getType());
}

void Unit::reset()
{
	m_pMap = NULL;

	m_baseAttr.CleanUp();
	m_buffAttrValue.CleanUp();
	m_buffAttrRatio.CleanUp();
	m_buffStates.CleanUp();

	//bzero(&m_secondAttr, sizeof(m_secondAttr));
	//bzero(&m_secondAttrAddon, sizeof(m_secondAttrAddon));
	//bzero(&m_secondAttrBuff, sizeof(m_secondAttrBuff));
	//bzero(&m_secondFormation,sizeof(m_secondFormation));
	bzero(&m_unitAttr, sizeof(m_unitAttr));
	m_bDie=false;
	m_needSync = false;
	GameMsg *msg = NULL;
	while ((msg = m_delayMsgQueue.pop()) != NULL)
	{
		POOL_MANAGER.push<GameMsg>( msg );
	}
	m_currentTile = m_targetTile = Position();
	m_currentPos = m_targetPos = Position();
	m_xOffset = m_yOffset = 0.0;
	m_direction = DOWN;
	m_posUpdateTick = getTick();
	m_throwedTick = -1;
	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		delete m_buffs[i];
	}
	bzero(m_buffs, sizeof(m_buffs));
	//bzero(m_buffStates, sizeof(m_buffStates));
	m_nSkillFlag = 0;
}

void Unit::update()
{
	updatePosition();

	//checkDelayGameMsg();

	checkBuffList();
	refresh();

	syncBasicData();
}

//void Unit::addDelayMsg(GameMsgCode msgcode, void *ptr1, void *ptr2, int32_t iparam1, int32_t iparam2, int64_t delay)
//{
//	GameMsg *msg = POOL_MANAGER.pop<GameMsg>();
//	if (msg != NULL)
//	{
//		msg->msgcode = msgcode;
//		msg->ptr1 = ptr1;
//		msg->ptr2 = ptr2;
//		msg->iparam1 = iparam1;
//		msg->iparam2 = iparam2;
//		msg->effecttick = getTick()+delay;
//
//		m_delayMsgQueue.push(msg);
//	}
//}

Map* Unit::getMap()
{
	return m_pMap;
}

int32_t Unit::getMapId()
{
	if (m_pMap != NULL)
	{
		return m_pMap->GetId();
	}
	else
	{
		return 0;
	}
}

int32_t Unit::getMapType()
{
	if (m_pMap != NULL)
	{
		return m_pMap->GetType();
	}
	else
	{
		return 0;
	}
}

bool Unit::InDungeon() const
{
	if ( NULL == m_pMap )
	{
		return false;
	}
	return m_pMap->IsDungeonMap();
}

bool Unit::InActivity() const
{
	if ( NULL == m_pMap )
	{
		return false;
	}
	return m_pMap->IsActivityMap();
}

int32_t Unit::GetRunnerId() const
{
	if ( m_pMap != NULL )
	{
		return m_pMap->GetRunnerId();
	}
	return 0;
}

Position Unit::getCurrentTile()
{
	return m_currentTile;
}

int32_t Unit::GetPosX() const
{
	return m_currentTile.x;
}

int32_t Unit::GetPosY() const
{
	return m_currentTile.y;
}

Position Unit::getCurrentPixel()
{
	return m_currentPos;
}

Position Unit::getTargetTile()
{
	return m_targetTile;
}

void Unit::onArriveTarget()
{
	// 到达目标
}

bool Unit::isBoss() const
{
	return false;
}

int32_t Unit::GetCalLevel() const
{
	return getLevel();
}

int32_t Unit::GetHurtIncreace() const
{
	return 1;
}

Direction Unit::getDirection()
{
	return m_direction;
}

void Unit::leaveTile()
{
	Position( 0, 0 );
	m_pMap = NULL;
	m_currentTile = Position( 0, 0 );
	m_targetTile = m_currentTile;
}

void Unit::setAtTile(Map *pMap, int32_t tx, int32_t ty)
{
	Map *pOldMap = m_pMap;
	Position oldPos = m_currentPos;

	m_pMap = pMap;
	m_currentTile = m_targetTile = Position(tx, ty);
	m_currentPos = m_targetPos = Map::tileToPixel(tx, ty);
	m_posUpdateTick = getTick();

	if (pOldMap == m_pMap && m_pMap != NULL)
	{
		m_pMap->checkAreaChange(this, oldPos);
	}
}

void Unit::setTargetTile(int32_t tx, int32_t ty)
{
	if (m_pMap == NULL)
	{
		return;
	}

	if( !m_pMap->isWalkablePosition(tx, ty) )
	{
		return;
	}
	
	if ( !resetDirection( tx, ty ) )
	{
		return;
	}

	m_targetTile.x = tx;
	m_targetTile.y = ty;
	m_targetPos = Map::tileToPixel(tx, ty);

	m_posUpdateTick = getTick();
}

bool Unit::resetDirection( int32_t tx, int32_t ty )
{
	Direction direction = m_direction;
	if (getCurrentTile() != Position(tx, ty))
	{
		direction = Map::tileDirection(m_currentTile.x, m_currentTile.y, tx, ty);
		if (direction == INVALID_DIRECTION)
		{
			Position targetPos = Map::tileToPixel(tx, ty);
			direction = Map::pixelDirection(m_currentPos.x, m_currentPos.y, targetPos.x, targetPos.y);
			if (direction == INVALID_DIRECTION)
			{
				return false;
			}
		}
	}
	m_direction = direction;
	return true;
}

void Unit::instantMove(int32_t tx, int32_t ty, InstanceMoveReason reason)
{
	broadcastInstantMove(static_cast<int16_t>(tx), static_cast<int16_t>(ty), reason);
	
	Position oldPos = m_currentPos;
	m_currentTile = m_targetTile = Position(tx, ty);
	m_currentPos = m_targetPos = Map::tileToPixel(tx, ty);
	
	m_posUpdateTick = getTick();
	if (m_pMap != NULL)
	{
		m_pMap->checkAreaChange(this, oldPos);
	}
}

void Unit::setStand()
{
	if (m_targetPos != m_currentPos)
	{
		m_targetTile = m_currentTile;
		m_targetPos = m_currentPos;
		m_posUpdateTick = getTick();
		broadcastMove();
	}
}

bool Unit::isInRectangle(Position pst1,Position pst2) const
{
	if (m_currentTile.x >= pst1.x && m_currentTile.x <= pst2.x && m_currentTile.y >= pst1.y && m_currentTile.y <= pst2.y)
	{
		return true;
	}
	return false;
}

bool Unit::updatePosition()
{
	if (!isMoving())
	{
		return false;
	}

	if ( HasBuffState( CObjState::OBS_BINGDONG ) || HasBuffState( CObjState::OBS_YUNXUAN ) )
	{
		return false;
	}

	int64_t ticks = getTick() - m_posUpdateTick;
	if (ticks <= 100)
	{
		return false;
	}

	double distance = sqrt(static_cast<double>((m_targetPos.x-m_currentPos.x)*(m_targetPos.x-m_currentPos.x) + (m_targetPos.y-m_currentPos.y)*(m_targetPos.y-m_currentPos.y)));
	double moved = getDirectionSpeed()*0.001*ticks;

	Position oldPos = m_currentPos;

	//bool barrive = false;
	if (moved > distance)
	{
		m_currentPos.x = m_targetPos.x;
		m_currentPos.y = m_targetPos.y;
		m_currentTile = m_targetTile;
		//barrive = true;
	}
	else if (moved > 0)
	{
		double ratio = moved/distance;

		double xMoved = m_currentPos.x + ratio*(m_targetPos.x-m_currentPos.x) + m_xOffset;
		double yMoved = m_currentPos.y + ratio*(m_targetPos.y-m_currentPos.y) + m_yOffset;

		int32_t ixMoved = static_cast<int32_t>(xMoved);
		int32_t iyMoved = static_cast<int32_t>(yMoved);

		m_xOffset = xMoved - ixMoved;
		m_yOffset = yMoved - iyMoved;

		m_currentPos.x = ixMoved;
		m_currentPos.y = iyMoved;
		m_currentTile = m_pMap->pixelToTile(m_currentPos.x, m_currentPos.y);
	}

	m_posUpdateTick = getTick();

	if (m_pMap != NULL)
	{
		m_pMap->checkAreaChange(this, oldPos);
	}

	if ( m_currentPos == m_targetPos )
	{
		onArriveTarget();
	}
	return true;
}
 
bool Unit::isMoving()
{
	return !(m_currentPos == m_targetPos);
}

int64_t Unit::getTick() const
{
	return TIMER.GetTick();
}

int32_t Unit::getNow() const
{
	return TIMER.GetNow();
}

tm Unit::getLocalNow() const
{
	return TIMER.GetLocalNow();
}

double Unit::pixelDistance(Unit *unit)
{
	if (unit == NULL || unit->getMap() != m_pMap)
	{
		return std::numeric_limits<int32_t>::max();
	}
	
	return m_currentPos.distance(unit->m_currentPos);
}

int32_t Unit::tileDistance(Unit *unit)
{
	if (unit == NULL || unit->getMap() != m_pMap)
	{
		return std::numeric_limits<int32_t>::max();
	}

	return (std::max)(abs(getCurrentTile().x-unit->getCurrentTile().x), abs(getCurrentTile().y-unit->getCurrentTile().y));
}

bool Unit::isAlive() const
{
	return GetHP() > 0;
}

//int32_t Unit::getHP()
//{
//	return m_unitAttr.hp;
//}
//
//void Unit::addHP(int32_t addon)
//{
//	if (addon != 0)
//	{
//		m_unitAttr.hp += addon;
//		m_needSync = true;
//	}
//}

//void Unit::addMP(int32_t addon)
//{
//	if (addon != 0)
//	{
//		m_unitAttr.mp += addon;
//		m_needSync = true;
//	}
//}

int32_t Unit::struckDamage(int32_t damge, int32_t attackType, UnitHandle launcher)
{
	if (!isAlive() || damge <= 0)
	{
		return 0;
	}

	int32_t real = damge;

	if ( HasBuffState( CObjState::OBS_WUDI ) )
	{
		real = 0;
	}
	else
	{
		//if (attackType == 1)
		//{
		//	real = static_cast<int32_t>(real * (1 - getAttr(ATTR_PREDUCE)*0.001));
		//}
		//else if (attackType == 2)
		//{
		//	real = static_cast<int32_t>(real * (1 - getAttr(ATTR_MREDUCE)*0.001));
		//}

		//if (real <= 0)
		//{
		//	real = 1;
		//}

		//if (getType() == ET_MONSTER && getAttr(ATTR_PDEF) >= 1000000 && real > 1)
		//{
		//	real = 1;
		//}

		AddHP(-1*real);
	}

	postDamage(real, launcher);

	return real;
}

int32_t Unit::GetBaseAttr( CObjAttrs::Index_T const nIdx ) const
{
	int32_t nValue = m_baseAttr.GetAttr( nIdx );
	if ( nValue < 0 )
	{
		nValue = 0;
	}
	return nValue;
}

int32_t	Unit::GetAttrValue( CObjAttrs::Index_T const nIdx ) const
{
	int64_t  nValue = static_cast<int64_t>( m_baseAttr.GetAttr( nIdx ) )* ( 100 + m_buffAttrRatio.GetAttr( nIdx ) ) / 100 + m_buffAttrValue.GetAttr( nIdx );
	if ( nValue < 0 )
	{
		nValue = 0;
	}
	int32_t Value = static_cast<int32_t>( nValue );
	return Value;
}

int32_t Unit::AddAttrValue( CObjAttrs::Index_T const nIdx, int32_t nAddVal )
{
	if ( nIdx < 0 || nIdx >= CObjAttrs::MAX_INDEX )
	{
		return 0;
	}

	int32_t	nRealValue = m_baseAttr.GetAttr( nIdx ) + nAddVal;
	m_baseAttr.SetAttr( nIdx, nRealValue );
	setNeedSync();
	return nRealValue;
}

void Unit::SetAttrValue( CObjAttrs::Index_T const nIdx, int32_t nVal )
{
	setNeedSync();
	m_baseAttr.SetAttr( nIdx, nVal );
}

void Unit::ResetAttrs()
{
	m_baseAttr.CleanUp();
}

int32_t Unit::AddBuffAttrRatio( CObjAttrs::Index_T const nIdx, int32_t nRate )
{
	if ( nRate == 0 )
	{
		return 0;
	}
	
	m_buffAttrRatio.SetAttr( nIdx, m_buffAttrRatio.GetAttr( nIdx ) + nRate );
	setNeedSync();
	return nRate;
}

int32_t Unit::AddBuffAttrValue( CObjAttrs::Index_T const nIdx, int32_t nAddVal )
{
	if ( nAddVal == 0)
	{
		return 0;
	}

	m_buffAttrValue.SetAttr( nIdx, m_buffAttrValue.GetAttr( nIdx ) + nAddVal );
	setNeedSync();
	return nAddVal;
}

bool Unit::HasBuffState( CObjState::Index_T const nIdx ) const
{
	return m_buffStates.GetState( nIdx );
}

void Unit::AddBuffState( CObjState::Index_T const nIdx )
{
	if ( nIdx == CObjState::OBS_YUNXUAN || nIdx == CObjState::OBS_BINGDONG  )
	{
		if ( isMoving() )
		{
			setAtTile( m_pMap, getCurrentTile().x, getCurrentTile().y );
		}
	}
	
	m_buffStates.AddState( nIdx );
}

void Unit::RemoveBuffState( CObjState::Index_T const nIdx )
{
	m_buffStates.RemoveState( nIdx );
}

int32_t Unit::GetHP() const
{
	return m_unitAttr.hp;
}

int32_t Unit::GetMP() const
{
	return m_unitAttr.mp;
}

int32_t Unit::GetPP() const
{
	return m_unitAttr.pp;
}

int32_t Unit::GetXP() const
{
	return m_unitAttr.xp;
}

int32_t Unit::GetMaxHP() const
{
	return GetAttrValue( CObjAttrs::ATTR_HP );
}

int32_t Unit::GetMaxMP() const
{
	return GetAttrValue( CObjAttrs::ATTR_MP );
}

int32_t Unit::GetMaxPP() const
{
	return GetAttrValue( CObjAttrs::ATTR_PP );
}

int32_t Unit::GetMaxXP() const
{
	return GetAttrValue( CObjAttrs::ATTR_XP );
}

int32_t Unit::GetMoveSpeed() const
{
	int32_t MoveSpeed = GetAttrValue( CObjAttrs::ATTR_MOVE_SPEED );

	if ( !isAlive() && getType() == ET_PLAYER )  
	{
		MoveSpeed = 30;
	}
	return MoveSpeed;
}

void Unit::AddHP( int32_t nAddValue )
{
	if ( nAddValue >= 0 )
	{
		if ( m_unitAttr.hp == GetMaxHP() )
		{
			return;
		}
	}

	int32_t nRealValue = m_unitAttr.hp + nAddValue;
	adjustAttr( nRealValue, GetMaxHP() );
	setHP( nRealValue );
	setNeedSync();
	setNeedSyncSelf();
}

void Unit::AddMP( int32_t nAddValue )
{
	if ( nAddValue >= 0 )
	{
		if ( m_unitAttr.mp == GetMaxMP() )
		{
			return;
		}
	}

	int32_t nRealValue = m_unitAttr.mp + nAddValue;
	adjustAttr( nRealValue, GetMaxMP() );
	setMP( nRealValue );
	setNeedSync();
	setNeedSyncSelf();
}

void Unit::AddPP( int32_t nAddValue )
{
	if ( nAddValue >= 0 )
	{
		if ( m_unitAttr.pp == GetMaxPP() )
		{
			return;
		}
	}
	int32_t nRealValue = m_unitAttr.pp + nAddValue;
	adjustAttr( nRealValue, GetMaxPP() );
	setPP( nRealValue );
	setNeedSync();
	setNeedSyncSelf();
}

void Unit::AddXP( int32_t nAddValue )
{
	if ( nAddValue >= 0 )
	{
		if ( m_unitAttr.xp == GetMaxPP() )
		{
			return;
		}
	}
	int32_t nRealValue = m_unitAttr.xp + nAddValue;
	adjustAttr( nRealValue, GetMaxXP() );
	setXP( nRealValue );
	setNeedSyncSelf();
}

void Unit::FillHP( int32_t nPercent )
{
	int64_t nMaxHP = GetAttrValue( CObjAttrs::ATTR_HP );
	int32_t nRealValue = static_cast<int32_t>( nMaxHP * nPercent / 100 );
	adjustAttr( nRealValue, static_cast<int32_t>(nMaxHP) );
	setHP( nRealValue );
	m_bDie = false;
	setNeedSync();
	setNeedSyncSelf();
}

void Unit::FillMP( int32_t nPercent )
{
	int32_t nMaxMP = GetAttrValue( CObjAttrs::ATTR_MP );
	int32_t nRealValue = nMaxMP * nPercent / 100;
	adjustAttr( nRealValue, nMaxMP );
	setMP( nRealValue );
	setNeedSync();
	setNeedSyncSelf();
}

int32_t	Unit::GetDefValue() const
{
	return GetAttrValue( CObjAttrs::ATTR_PHY_DEF ) + GetAttrValue( CObjAttrs::ATTR_MAG_DEF );
}

int32_t Unit::GetSkillFlag( bool bIncrease )
{
	if ( bIncrease && getType() != ET_PLAYER )
	{
		++m_nSkillFlag;
	}
	return m_nSkillFlag;
}

void Unit::SetSkillFlag( int32_t SkillFlag )
{
	m_nSkillFlag = SkillFlag;
}

void Unit::resetUnitAttr()
{
	bzero( &m_unitAttr, sizeof( m_unitAttr ) );
}

void Unit::adjustUnitAttr()
{
	adjustAttr( m_unitAttr.hp, GetMaxHP() );
	adjustAttr( m_unitAttr.mp, GetMaxMP() );
	adjustAttr( m_unitAttr.pp, GetMaxPP() );
	adjustAttr( m_unitAttr.xp, GetMaxXP() );
}

void Unit::adjustAttr( int32_t& nAttr, int32_t nMaxValue, int32_t nMinValue )
{
	nAttr = nAttr > nMinValue ? nAttr : nMinValue;
	nAttr = nAttr < nMaxValue ? nAttr : nMaxValue;
}

void Unit::setHP( int32_t nValue )
{
	m_unitAttr.hp = nValue;
}

void Unit::setMP( int32_t nValue )
{
	m_unitAttr.mp = nValue;
}

void Unit::setPP( int32_t nValue )
{
	m_unitAttr.pp = nValue;
}

void Unit::setXP( int32_t nValue )
{
	m_unitAttr.xp = nValue;
}

bool Unit::HasBuffById(int32_t buffId)
{
	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && buff->getId() == buffId)
		{
			return true;
		}
	}
	return false;
}

int32_t Unit::getBuffCount()
{
	int32_t count = 0;

	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		if (m_buffs[i] != NULL && m_buffs[i]->NeedShow() )
		{
			++count;
		}
	}
	return count;
}

int32_t Unit::addBuff(Buff *buff)
{
	if (buff == NULL)
	{
		return ERR_INVALID_DATA;
	}
	if (buff->remainTick() <= 0)
	{
		delete buff;
		return ERR_INVALID_DATA;
	}

	int32_t freeSlot = -1;

	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		if (m_buffs[i] != NULL)
		{
			if (m_buffs[i]->getType() == BT_PERSIST && buff->getType() == BT_PERSIST)
			{
				if (m_buffs[i]->getGroupId() == buff->getGroupId())
				{
					if (m_buffs[i]->getId() == buff->getId())
					{
						PersistBuff *persistBuff = dynamic_cast<PersistBuff*>(m_buffs[i]);
						if (persistBuff != NULL)
						{
							persistBuff->extend(buff);
						}
						delete buff;
						broadcastBuffList();
						return ERR_OK;
					}
					else
					{
						m_buffs[i]->restore();
						delete m_buffs[i];
						buff->effect();
						m_buffs[i] = buff;
						broadcastBuffList();
						return ERR_OK;
					}
				}
			}
			else if (m_buffs[i]->getType() == buff->getType() && m_buffs[i]->getGroupId() == buff->getGroupId())
			{
				if (m_buffs[i]->getLevel() > buff->getLevel())
				{
					delete buff;
					return ERR_INVALID_DATA;
				}
				else
				{
					m_buffs[i]->restore();
					delete m_buffs[i];
					buff->effect();
					m_buffs[i] = buff;
					broadcastBuffList();
					return ERR_OK;
				}
			}
		}
		else
		{
			freeSlot = i;
		}
	}

	if (freeSlot < 0)
	{
		delete buff;
		return ERR_INVALID_DATA;
	}

	buff->effect();
	m_buffs[freeSlot] = buff;
	broadcastBuffList();
	return ERR_OK;
}

void Unit::removeBuff(int32_t buffId)
{
	Int32Vector buffids;
	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && buff->getId() == buffId)
		{
			if ( buff->NeedShow() )
			{
				buffids.push_back(buff->getId());
			}
			buff->restore();
			delete buff;
			m_buffs[i] = NULL;
		}
	}
	adjustUnitAttr();
	broadcastBuffList();
	broadcastBuffEnd(buffids);
}

void Unit::clearDebuff()
{
	Int32Vector buffids;

	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && !buff->beneficial())
		{
			if ( buff->NeedShow() )
			{
				buffids.push_back(buff->getId());
			}
			buff->restore();
			delete buff;
			m_buffs[i] = NULL;
		}
	}

	broadcastBuffList();
	broadcastBuffEnd(buffids);
}

Buff* Unit::findBuffBySpecail(int32_t special)
{
	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && buff->getSpecial() == special)
		{
			return buff;
		}
	}

	return NULL;
}

bool Unit::checkBuffBySpecail(int32_t special)
{
	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && buff->getSpecial() == special)
		{
			return true;
		}
	}

	return false;
}


MemChrBuffVector Unit::getPersistBuffs()
{
	MemChrBuffVector buffs;

	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && buff->getType() == BT_PERSIST)
		{
			PersistBuff *persistBuff = dynamic_cast<PersistBuff*>(buff);
			if (persistBuff != NULL)
			{
				MemChrBuff chrbuff = {};
				chrbuff.id = persistBuff->getItemId();
				chrbuff.time = persistBuff->getEndTime();
				buffs.push_back(chrbuff);
			}
		}
	}

	return buffs;
}

//void Unit::addBuffState(BuffState buffState)
//{
//	if (buffState > 0 && buffState < BS_BUFF_STATE_MAX)
//	{
//		m_buffStates[buffState]++;
//	}
//}
//
//void Unit::removeBuffState(BuffState buffState)
//{
//	if (buffState > 0 && buffState < BS_BUFF_STATE_MAX && m_buffStates[buffState] > 0)
//	{
//		m_buffStates[buffState]--;
//	}
//}
//
//bool Unit::hasBuffState(BuffState buffState)
//{
//	if (buffState > 0 && buffState < BS_BUFF_STATE_MAX)
//	{
//		return m_buffStates[buffState] > 0;
//	}
//	return false;
//}

void Unit::addFans(int16_t cgindex)
{
	MutexGuard lock(m_fansLock);
	m_fans.push_back(cgindex);

	//sendBuffList(cgindex);
}

void Unit::removeFans(int16_t cgindex)
{
	MutexGuard lock(m_fansLock);
	m_fans.remove(cgindex);
}

void Unit::clearFans()
{
	MutexGuard lock(m_fansLock);
	m_fans.clear();
}

int32_t Unit::getDeadTime() const
{
	return 0;
}

//int32_t Unit::getAttr(int32_t index) const
//{
//	int32_t attr = 0;
//
//	switch (index)
//	{
//	case ATTR_ATTACK: attr = m_secondAttr.attack + m_secondAttrAddon.attack + m_secondAttrBuff.attack; break;
//	case ATTR_PDEF: attr = m_secondAttr.pdef + m_secondAttrAddon.pdef + m_secondAttrBuff.pdef; break;
//	case ATTR_MDEF: attr = m_secondAttr.mdef + m_secondAttrAddon.mdef + m_secondAttrBuff.mdef; break;
//	case ATTR_MAXHP: attr = m_secondAttr.maxhp + m_secondAttrAddon.maxhp + m_secondAttrBuff.maxhp; break;
//	case ATTR_MAXMP: attr = m_secondAttr.maxmp + m_secondAttrAddon.maxmp + m_secondAttrBuff.maxmp;break;
//	case ATTR_VP: attr = m_secondAttr.vp + m_secondAttrAddon.vp + m_secondAttrBuff.vp; break;
//	case ATTR_DP: attr = m_secondAttr.dp + m_secondAttrAddon.dp + m_secondAttrBuff.dp; break;
//	case ATTR_HTIP: attr = m_secondAttr.hitp + m_secondAttrAddon.hitp + m_secondAttrBuff.hitp; break;
//	case ATTR_SP: attr = m_secondAttr.sp + m_secondAttrAddon.sp + m_secondAttrBuff.sp; break;
//	case ATTR_PREVP: attr = m_secondAttr.prevp+ m_secondAttrAddon.prevp + m_secondAttrBuff.prevp; break;
//	case ATTR_PREFROST: attr = m_secondAttr.preforst + m_secondAttrAddon.preforst + m_secondAttrBuff.preforst; break;
//	case ATTR_PREBK: attr = m_secondAttr.prebk + m_secondAttrAddon.prebk + m_secondAttrBuff.prebk; break;
//	case ATTR_PREDUCE: attr = m_secondAttr.preduce + m_secondAttrAddon.preduce + m_secondAttrBuff.preduce; break;
//	case ATTR_MREDUCE: attr = m_secondAttr.mreduce + m_secondAttrAddon.mreduce + m_secondAttrBuff.mreduce; break;
//	case ATTR_VPP: attr = m_secondAttr.vpp + m_secondAttrAddon.vpp + m_secondAttrBuff.vpp; break;
//	case ATTR_HP: attr = m_unitAttr.hp; break;
//	case ATTR_MP: attr = m_unitAttr.mp;break;
//	default: break;;
//	}
//
//	if (attr < 0)
//	{
//		attr = 0;
//	}
//
//	return attr;
//}

bool Unit::isFriendSide(Unit *pUnit)
{
	return false;
}

bool Unit::checkSkillTarget(CfgSkill *pCfg, Unit *pUnit)
{
	return false;
}

bool Unit::needMapBroadcast()
{
	return false;
}

//void Unit::onDelayGameMsg(GameMsg *msg)
//{
//	if (msg != NULL)
//	{
//		switch (msg->msgcode)
//		{
//		case GMC_UNIT_SKILL_DELAY_RESULT: onSkillDelayResult(static_cast<CfgSkill*>(msg->ptr1), msg->iparam1, msg->iparam2); break;
//		default: break;
//		}
//	}
//}

//void Unit::addSecondAttrAddon(int32_t index, int32_t addon)
//{
//	switch (index)
//	{
//	case ATTR_ATTACK: m_secondAttrAddon.attack += addon; break;
//	case ATTR_PDEF: m_secondAttrAddon.pdef += addon; break;
//	case ATTR_MDEF: m_secondAttrAddon.mdef += addon; break;
//	case ATTR_MAXHP: m_secondAttrAddon.maxhp += addon; break;
//	case ATTR_MAXMP: m_secondAttrAddon.maxmp += addon; break;
//	case ATTR_VP: m_secondAttrAddon.vp += addon; break;
//	case ATTR_DP: m_secondAttrAddon.dp += addon; break;
//	case ATTR_HTIP: m_secondAttrAddon.hitp += addon; break;
//	case ATTR_SP: m_secondAttrAddon.sp += addon; break;
//	case ATTR_PREVP: m_secondAttrAddon.prevp += addon ; break;
//	case ATTR_PREFROST: m_secondAttrAddon.preforst += addon;  break;
//	case ATTR_PREBK: m_secondAttrAddon.prebk += addon;  break;
//	case ATTR_PREDUCE: m_secondAttrAddon.preduce += addon; break;
//	case ATTR_MREDUCE: m_secondAttrAddon.mreduce += addon; break;
//	case ATTR_VPP: m_secondAttrAddon.vpp += addon; break;
//	default: break;
//	}
//}

//void Unit::checkDelayGameMsg()
//{
//	int size = m_delayMsgQueue.size();
//	for (int i = 0; i < size; ++i)
//	{
//		GameMsg *msg = m_delayMsgQueue.pop();
//		if (msg != NULL)
//		{
//			if (getTick() < msg->effecttick)
//			{
//				m_delayMsgQueue.push(msg);
//			}
//			else
//			{
//				onDelayGameMsg(msg);
//				POOL_MANAGER.push<GameMsg>( msg );
//			}
//		}
//	}
//}

void Unit::checkBuffList()
{
	if (!isAlive())
	{
		deathClearBuff();
		return;
	}

	bool change = false;

	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL)
		{
			if (buff->expire())
			{
				buff->restore();
				m_buffs[i] = NULL;
				delete buff;
				change = true;
			}
			else
			{
				buff->interval();
			}
		}
	}

	if (change)
	{
		broadcastBuffList();
	}

	if (!isAlive())
	{
		deathClearBuff();
	}
}

void Unit::syncBasicData()
{
	if ( m_needSync )
	{
		broadcastBasicData();
		m_needSync = false;
	}
}

void Unit::setNeedSync()
{
	m_needSync = true;
}

void Unit::setNeedSyncSelf()
{
	m_needSyncSelf = true;
}

void Unit::broadcastMove()
{
	if (m_pMap != NULL)
	{
		int16_t x=static_cast<int16_t>(m_targetTile.x);
		int16_t y=static_cast<int16_t>(m_targetTile.y);

		if ( !m_pMap->isWalkablePosition(x,y) )
		{
			return;
		}
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_MOVE);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getUnitId());
		packet->writeInt8(getType());
		packet->writeInt16(x);
		packet->writeInt16(y);
		packet->setSize(packet->getWOffset());
		m_pMap->broadcastAreaAround(packet, this);
	}
}

void Unit::broadcastInstantMove(int16_t finalX, int16_t finalY, InstanceMoveReason reason)
{
	if (m_pMap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_INSTANT_MOVE);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getUnitId());
		packet->writeInt8(getType());
		packet->writeInt16(finalX);
		packet->writeInt16(finalY);
		packet->writeInt32(reason);
		packet->setSize(packet->getWOffset());
		m_pMap->broadcastAreaAround(packet, this);
	}
}

int32_t Unit::onKickOutMove(int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t finalX, int16_t finalY, Direction direction)
{
	if (m_pMap == NULL)
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

	setAtTile(m_pMap,targetX,targetY);
	broadcastKickOutedMove();

	return ERR_OK;
}

void Unit::broadcastKickOutedMove()
{
	if (m_pMap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_KICK_OUT_MOVE);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getUnitId());
		packet->writeInt8(getType());
		packet->writeInt16(static_cast<int16_t>(m_currentTile.x));
		packet->writeInt16(static_cast<int16_t>(m_currentTile.y));
		packet->setSize(packet->getWOffset());
		m_pMap->broadcastAreaAround(packet, this);
	}
}
void Unit::onThrowed()
{
	m_throwedTick = getTick() + 800;
	broadcastThrowed();
}
void Unit::broadcastThrowed()
{
	if (m_pMap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_UNIT_THROWED);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getUnitId());
		packet->writeInt8(getType());
		packet->setSize(packet->getWOffset());
		m_pMap->broadcastAreaAround(packet, this);
	}
}

void Unit::broadcastLeave()
{
	if (m_pMap != NULL)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_LEAVE_MAP);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getUnitId());
		packet->writeInt8(getType());
		packet->setSize(packet->getWOffset());
		m_pMap->broadcast(packet);
	}
}

void Unit::broadcastBasicData()
{
	if (m_pMap != NULL)
	{
		int8_t nflag = m_bDie ? 1 : 0;
		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_UNIT_BASIC_DATA);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64(getUnitId());
		packet->writeInt8(getType());
		packet->writeInt32( GetHP() );
		packet->writeInt32( GetMaxHP() );
		if ( getType() == ET_PLAYER )
		{
			packet->writeInt32( GetMP() );										//  当前法力值
			packet->writeInt32( GetMaxMP() );									// 最大法力值
			packet->writeInt32( GetPP() );										// 当前体力值
			packet->writeInt32( GetMaxPP() );									// 最大体力值
		}
		packet->writeInt16( GetMoveSpeed() );
		packet->writeInt8( nflag );
		packet->writeInt32(getDeadTime());
		packet->setSize(packet->getWOffset());
		m_pMap->broadcastAreaAround(packet, this);
	}
}

void Unit::sendBuffList(int16_t cgindex)
{
// 	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_UNIT_BUFF_LIST);
// 	if (NULL == packet)
// 	{
// 		return;
// 	}
// 	packet->writeInt64(getUnitId());
// 	packet->writeInt32(getType());
// 	packet->writeInt32(getBuffCount());
// 	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
// 	{
// 		Buff *pBuff = m_buffs[i];
// 		if (pBuff != NULL)
// 		{
// 			packet->writeInt32(pBuff->getId());
// 			packet->writeInt32(pBuff->getLevel());
// 			packet->writeInt32(pBuff->remainTick());
// 		}
// 	}
// 	packet->setSize(packet->getWOffset());
// 	GAME_SERVICE.sendPacketTo(cgindex, packet);
}

void Unit::broadcastBuffList()
{
	if ( m_pMap == NULL )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_UNIT_BUFF_LIST);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(1);
	PacketBuffList( packet );
	packet->setSize(packet->getWOffset());
	m_pMap->broadcastAreaAround( packet,this );
	//fansBroadcast(packet);
}

void Unit::PacketBuffList( Answer::NetPacket *Packet )
{
	Packet->writeInt64(getUnitId());
	Packet->writeInt32(getType());
	int32_t Count = 0;
	int32_t OldOffset = Packet->getWOffset();
	Packet->writeInt32( Count );
	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *pBuff = m_buffs[i];
		if (pBuff != NULL && m_buffs[i]->NeedShow() )
		{
			Packet->writeInt32(pBuff->getId());
			Packet->writeInt32(pBuff->getLevel());
			Packet->writeInt32(pBuff->remainTick());
			Count++;
		}
	}
	int32_t NewOffset = Packet->getWOffset();
	Packet->setWOffset( OldOffset );
	Packet->writeInt32( Count );
	Packet->setWOffset( NewOffset );
}

void Unit::broadcastBuffEnd(Int32Vector buffids)
{
	if (m_pMap == NULL || buffids.empty())
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_UNIT_BUFF_END);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64(getUnitId());
	packet->writeInt32(getType());
	packet->writeInt32(static_cast<int32_t>(buffids.size()));
	for (Int32Vector::iterator it = buffids.begin(); it != buffids.end(); ++it)
	{
		packet->writeInt32(*it);
	}
	packet->setSize(packet->getWOffset());
	m_pMap->broadcast(packet);
}

void Unit::fansBroadcast(Answer::NetPacket *inPacket)
{
	if (inPacket == NULL)
	{
		return;
	}

	MutexGuard lock(m_fansLock);

	if (m_fans.empty())
	{
		inPacket->destroy();
		return;
	}

	uint32_t oldSize = inPacket->getSize();
	uint32_t addonSize = (m_fans.size()+1)*(sizeof(int16_t));
	if (inPacket->rightShift(addonSize))
	{
		inPacket->writeInt16(static_cast<int16_t>(m_fans.size()));
		for (Int16List::iterator it = m_fans.begin(); it != m_fans.end(); ++it)
		{
			inPacket->writeInt16(*it);
		}
		inPacket->setSize(oldSize+addonSize);
		GAME_SERVICE.sendPacket(inPacket);
	}
	else
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(inPacket->getType(), inPacket->getProc(), (m_fans.size()+1)*sizeof(int16_t) + inPacket->getSize());
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(static_cast<int16_t>(m_fans.size()));
		for (Int16List::iterator it = m_fans.begin(); it != m_fans.end(); ++it)
		{
			packet->writeInt16(*it);
		}
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacket(packet);
		inPacket->destroy();
	}
}

//void Unit::onSkillDelayResult(CfgSkill *cfg, int32_t param1, int32_t param2)
//{
//	if (cfg != NULL)
//	{
//		Skill skill(cfg->skill_id, 1);
//		skill.unitResult(*this, UnitHandle(param1, param2));
//	}
//}

//void Unit::adjustUnitAttr()
//{
//	if (m_unitAttr.hp < 0)
//	{
//		m_unitAttr.hp = 0;
//	}
//	
//	if (m_unitAttr.hp > getAttr(ATTR_MAXHP))
//	{
//		m_unitAttr.hp = getAttr(ATTR_MAXHP);
//	}
//
//	if (m_unitAttr.mp < 0)
//	{
//		m_unitAttr.mp = 0;
//	}
//
//	if (m_unitAttr.mp > getAttr(ATTR_MAXMP))
//	{
//		m_unitAttr.mp = getAttr(ATTR_MAXMP);
//	}
//}

void Unit::deathClearBuff()
{
	bool change = false;

	for (int32_t i = 0; i < MAX_UNIT_BUFF_NUM; ++i)
	{
		Buff *buff = m_buffs[i];
		if (buff != NULL && buff->deathClear())
		{
			buff->restore();
			m_buffs[i] = NULL;
			delete buff;
			change = true;
		}
	}

	if (change)
	{
		broadcastBuffList();
	}
}

double Unit::getDirectionSpeed()
{
	double baseSpeed = GetAttrValue( CObjAttrs::ATTR_MOVE_SPEED );

	double directionSpeed = baseSpeed;

	switch (m_direction)
	{
	case DOWN:
	case UP:
		directionSpeed = baseSpeed;
		break;
	case LEFT:
	case RIGHT:
		directionSpeed = baseSpeed*1.2;
		break;
	case DOWN_LEFT:
	case UP_LEFT:
	case UP_RIGHT:
	case DOWN_RIGHT:
		directionSpeed = baseSpeed*1.5;
		break;
	default:
		LOG_ERROR("Unit::setTargetPosition with m_direction = %d\n", m_direction);
		break;
	}

	return directionSpeed;
}
