#pragma once

#include "CfgData.h"
#include "Unit.h"

/*
* 镖车
* 护送对象
*/
class Trailer
	: public Unit
{
public:
	Trailer();
	virtual ~Trailer();

public:
	virtual void reset();
	virtual void refresh();
	virtual EntityId_t getUnitId() const;
	virtual CharId_t getOwner() const;
	virtual int32_t getLevel() const;
	virtual int32_t	getBattle() const;
	virtual void postDamage(int32_t damge, UnitHandle launcher);

public:
	void init(const CfgTrailer &cfgTrailer, Player *player, int32_t tid, int32_t endMapId, int32_t endX, int32_t endY, int32_t timeOut, int32_t hp);

	void appendInfo(Answer::NetPacket *packet);

	Player* getPlayer();

	int32_t move(int32_t mapID,int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t finalX, int16_t finalY, Direction direction);

	void leaveMap();
	void onLogout();
	void checkSwitchMap();
	void quickTask();

private:
	void checkEnd();

private:
	CfgTrailer m_cfgTrailer;

	Player *m_player;
	int32_t m_tid;
	int32_t m_endMapId;
	int32_t m_endX;
	int32_t m_endY;
	int32_t m_endTime;
};
