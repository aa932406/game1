#pragma once

#include "CfgData.h"
#include "Entity.h"

enum TrapState
{
	TS_STANDBY,
	TS_EFFECT,
	TS_COOLDOWN,
	TS_DIE,
};

enum TrapType
{
	TT_BUFF				= 1,	// BUFF
	TT_MONSTER			= 2,	// 刷怪
	TT_TRANSFER			= 3,	// 传送
	TT_TRANSFER_TEAM	= 4,	// 队伍传送
	TT_DELAY_MONSTER	= 5,	// 延时刷怪
	TT_CHANGE_DUNGEON	= 6,	// 切换副本
	TT_ADD_DUNGEON_TIME	= 7,	// 延长副本时间
};

class Map;
class Dungeon;
class CActivityMap;
/*
* 陷阱
*/
class Trap
	: public Entity
{
public:
	Trap();
	virtual ~Trap();

public:
	void init( Map *pMap, Position pos, const CfgTrap &cfgTrap);
	void reset();

	void checkState();

	int32_t onUse(Player *player);

	void appendInfo(Answer::NetPacket *inPacket);
	void leaveMap();

private:
	void broadcastState();
	void broadcastLeaveMap();

	void setState(TrapState state);
	void effect();

private:
	Map*		m_pMap;
	CfgTrap		m_cfgTrap;
	Position	m_pos;
	CharId_t	m_user;
	TrapState	m_state;
	int64_t		m_stateTick;
};


