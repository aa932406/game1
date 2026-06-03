#pragma once

#include "Player.h"

class PlayerRobot
	: public Player
{
public:
	PlayerRobot();
	virtual ~PlayerRobot();

public:
	virtual bool isRobot();
	virtual void saveToDB(int32_t reason, int32_t param);
};

