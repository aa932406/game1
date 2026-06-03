#include "stdafx.h"

//#include "GameService.h"
//#include "Kingdom.h"
#include "Map.h"
//#include "PersistBuff.h"
//#include "Skill.h"
#include "Unit.h"
//#include "PoolManager.h"
//#include "Timer.h"
//#include <limits>

using namespace Answer;

Unit::Unit()
{

}

Unit::~Unit()
{

}

void Unit::CleanUp()
{
	m_nId		= 0;
	m_nMapId	= 0;
	m_curPos.x	= 0;
	m_curPos.y	= 0;
	m_nHP		= 0;
	m_nMaxHP	= 0;
	m_nMid		= 0;
}

EntityId_t	Unit::GetId() const
{
	return m_nId;
}

int32_t Unit::GetMid() const
{
	return m_nMid;
}

bool Unit::IsAlive() const
{
	return m_nHP > 0;
}

int32_t	Unit::GetMapId() const
{
	return m_nMapId;
}

int32_t	Unit::GetX() const
{
	return m_curPos.x;
}

int32_t	Unit::GetY() const
{
	return m_curPos.y;
}

Position Unit::GetCurTile() const
{
	return m_curPos;
}

void Unit::Init( EntityId_t id, int32_t mapid, int32_t x, int32_t y, int32_t hp, int32_t maxhp, int32_t mid )
{
	m_nId		= id;
	m_nMapId	= mapid;
	m_curPos.x	= x;
	m_curPos.y	= y;
	m_nHP		= hp;
	m_nMaxHP	= maxhp;
	m_nMid		= mid;
}

void Unit::UpdateAttr( int32_t hp, int32_t maxhp )
{
	m_nHP		= hp;
	m_nMaxHP	= maxhp;
}

void Unit::UpdatePosition( int32_t x, int32_t y )
{
	m_curPos.x	= x;
	m_curPos.y	= y;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Monster::Monster()
{

}

Monster::~Monster()
{

}

int8_t Monster::GetType() const
{
	return ET_MONSTER;
}

