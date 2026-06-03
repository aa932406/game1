#include "stdafx.h"
#include "PoolManager.h"
#include "Dungeon.h"
#include "MonsterDungeon.h"
#include "DropItem.h"
#include "Trap.h"
#include "PlantDungeon.h"
#include "User.h"
#include "Player.h"
#include "MonsterActivity.h"
#include "NpcActivity.h"
#include "PlantActivity.h"
#include "Trailer.h"
#include "DataStructs.h"
#include "Pet.h"
#include "ObjPet.h"

using namespace Answer; 

CPoolManager::CPoolManager()
{

}

CPoolManager::~CPoolManager()
{

}

void CPoolManager::Init()
{
	regPool<Dungeon>( 50, 500 );				// 副本
	regPool<MonsterDungeon>( 500, 5000 );		// 副本怪物
	regPool<CDropItemGroup>( 500, 5000 );		// 掉落包
	regPool<Trap>( 100, 1000 );					// 陷阱
	regPool<PlantDungeon>( 100, 1000 );			// 副本采集物
	regPool<User>( 200, 2000 );					// 用户
	regPool<Player>( 200, 2000 );				// 玩家
	regPool<MonsterActivity>( 100, 1000 );		// 活动怪物
	regPool<NpcActivity>( 0, 500 );				// 活动NPC
	regPool<PlantActivity>( 0, 500 );			// 活动采集物
	regPool<Trailer>( 0, 500 );					// 镖车
	regPool<GameMsg>( 0, 2000 );				// 消息
	regPool<CPet>( 500, 5000 );					// 宠物
	regPool<CObjPet>( 500, 5000 );				// 宠物对象
}
