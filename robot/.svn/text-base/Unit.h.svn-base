#pragma once

//#include "Buff.h"
//#include "Entity.h"
//#include "Attribute.h"

class Map;

class Unit
	//: public Entity
{
public:
	Unit();
	virtual ~Unit();

	void		CleanUp();

public:
	virtual int8_t GetType() const=0;

public:
	EntityId_t	GetId() const;
	int32_t		GetMid() const;
	int32_t		GetMapId() const;
	int32_t		GetX() const;
	int32_t		GetY() const;
	bool		IsAlive() const;
	Position	GetCurTile() const;
	void		Init( EntityId_t id, int32_t mapid, int32_t x, int32_t y, int32_t hp, int32_t maxhp, int32_t mid );
	void		UpdateAttr( int32_t hp, int32_t maxhp );
	void		UpdatePosition( int32_t x, int32_t y );

protected:
	EntityId_t	m_nId;
	int32_t		m_nMid;
	int32_t		m_nHP;
	int32_t		m_nMaxHP;
	int32_t		m_nMapId;
	Position	m_curPos;
};

class Monster : public Unit
{
public:
	Monster();
	virtual ~Monster();

	virtual int8_t	GetType() const;
};
