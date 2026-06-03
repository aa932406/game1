// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef LIANSWER_WINDOWS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#endif

// TODO: reference additional headers your program requires here
#include "libanswer.h"
#include "Shared.h"
#include "DataStructs.h"

#define DBPOOL Answer::Singleton<Answer::DBPool>::instance()
#define RANDOM Answer::Singleton<Answer::Random>::instance()


inline int roundInt(double d)
{
	if (d > 0)
	{
		d += 0.5;
	}
	else if (d < 0)
	{
		d -= 0.5;
	}

	return static_cast<int>(d);
}

template<typename T>
void adjust(T &value, T lower_bound, T up_bound)
{
	if (value < lower_bound)
	{
		value = lower_bound;
	}

	if (value > up_bound)
	{
		value = up_bound;
	}
}

enum EntityType
{
	ET_NONE			= 0,
	ET_PLAYER		= 1,	// 玩家
	ET_MONSTER		= 2,	// 怪物
	ET_NPC			= 3,	// NPC
	ET_PET			= 4,	// 副将
	ET_DROPITEM		= 5,	// 掉落包
	ET_PLANT		= 6,	// 采集物
	ET_TRAP			= 7,	// 触发器
	ET_TRAILER		= 8,	// 镖车
	ET_LACKEY		= 9,	// 随从
};
