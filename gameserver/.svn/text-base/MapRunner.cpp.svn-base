#include "stdafx.h"
#include "GameService.h"
#include "Map.h"
#include "MapRunner.h"
#include "MapManager.h"
#include "MapRunner.h"
#include "PoolManager.h"
#include "Activity.h"
#include "ActivityMap.h"
#include "Monster.h"

using namespace Answer;

void CMapRunner::run()
{
	m_bRunning = true;

	while (m_bRunning)
	{
		update();
		checkMessage();
		DayTime::sleep(10);
	}
}

void CMapRunner::SetId( int32_t nId )
{
	m_nId = nId;
}

int32_t CMapRunner::GetId() const
{
	return m_nId;
}

void CMapRunner::Start()
{
	start(); //启动线程
}

void CMapRunner::Stop()
{
	m_bRunning = false;
	join();
}


void CMapRunner::AddMap( Map* pMap )
{
	m_maps.push_back( pMap );
}

void CMapRunner::DelMap( MapId_t nMapId )
{
	//m_maps.erase( nMapId );
	MapList::iterator iter = m_maps.begin();
	for ( ; iter != m_maps.end(); ++iter ) 
	{
		m_maps.erase( iter );
	}
}

void CMapRunner::PostMsg( GameMsgCode msgcode, void *ptr1, void *ptr2, int32_t iparam1, int32_t iparam2,void *ptr3 )
{
	GameMsg *msg = POOL_MANAGER.pop<GameMsg>();
	if ( msg != NULL )
	{
		msg->msgcode = msgcode;
		msg->ptr1 = ptr1;
		msg->ptr2 = ptr2;
		msg->ptr3 = ptr3;
		msg->iparam1 = iparam1;
		msg->iparam2 = iparam2;
		msg->effecttick = 0;
		m_msgQueue.push(msg);
	}
}

void CMapRunner::update()
{
	for ( MapList::iterator it = m_maps.begin(); it != m_maps.end(); ++it)
	{
		if((*it)!=NULL)
		{
			(*it)->update();
		}
	}
}

void CMapRunner::checkMessage()
{
	GameMsg *msg = NULL;
	while ( ( msg = m_msgQueue.pop() ) != NULL )
	{
		dealMessage( msg );
		POOL_MANAGER.push<GameMsg>( msg );
	}
}

void CMapRunner::dealMessage(GameMsg *msg)
{
	if (msg != NULL)
	{
		switch (msg->msgcode)
		{
		case GMC_PLAYER_ENTER_MAP:	onPlayerEnterMap( static_cast<Player*>(msg->ptr1), static_cast<Map*>(msg->ptr2), msg->iparam1, msg->iparam2 );	break;
		case GMC_PLAYER_LEAVE_MAP:	onPlayerLeaveMap( static_cast<Player*>(msg->ptr1), static_cast<Map*>(msg->ptr2), msg->iparam1, msg->iparam2 );	break;
		case GMC_ADD_DUNGEON:		onAddDungeon( static_cast<Dungeon*>(msg->ptr1) );																break;
		case GMC_DEL_DUNGEON:		onDelDungeon( static_cast<Dungeon*>(msg->ptr1) );																break;
		case GMC_PLAYER_LOGOUT:		onPlayerLogout( static_cast<Player*>(msg->ptr1), static_cast<int16_t>(msg->iparam1) );							break;
		case GMC_ACTIVITY_START:	onActivityStart( static_cast<CActivityMap*>( msg->ptr1), static_cast<CActivity*>( msg->ptr2 ) );				break;
		case GMC_ACTIVITY_STOP:		onActivityStop( static_cast<CActivityMap*>( msg->ptr1), static_cast<CActivity*>( msg->ptr2 ) );					break;
		case GMC_MO_LING_RU_QIN_START: onStartMoLingRuQin(static_cast<Map*>(msg->ptr1), msg->iparam1);												break;			
		case GMC_KILL_MONST:		onKillMonster( static_cast<Map*>(msg->ptr1), static_cast<Monster*>(msg->ptr2) );
		default: LOG_ERROR("Kingdom::checkMessage with unknown msg code %d\n", (int)(msg->msgcode)); break;
		}
	}
}

void CMapRunner::onPlayerEnterMap( Player *pPlayer, Map *pMap, int32_t x, int32_t y )
{
	if ( NULL == pPlayer || NULL == pMap || pMap->GetRunnerId() != this->GetId() )
	{
		return;
	}

	LOG_DEBUG( "CMapRunner::onPlayerEnterMap with player = %p, cid = %lld, cgindex = %d\n", pPlayer, pPlayer->getCid(), pPlayer->getGateIndex() );
	pMap->addPlayer( pPlayer, x, y );
}

void CMapRunner::onPlayerLeaveMap( Player *pPlayer, Map *pMap, int32_t x, int32_t y )
{
	if ( NULL == pPlayer || NULL == pMap )
	{
		return;
	}

	// 切换地图消息由此处中转一下是为了使当前线程完成一次完整的更新循环，下次循环才将人物投递到另一条线程
	LOG_DEBUG( "CMapRunner::onPlayerLeaveMap with player = %p, cid = %lld, cgindex = %d\n", pPlayer, pPlayer->getCid(), pPlayer->getGateIndex() );
	MAP_MANAGER.PostMsg( pMap->GetRunnerId(), GMC_PLAYER_ENTER_MAP, pPlayer, pMap, x, y );
}

void CMapRunner::onAddDungeon( Dungeon* pDungeon )
{
	if ( NULL == pDungeon )
	{
		return;
	}

	m_maps.push_back( pDungeon );
	MAP_MANAGER.AddDungeon( pDungeon );
}

void CMapRunner::onDelDungeon( Dungeon* pDungeon )
{
	if ( NULL == pDungeon )
	{
		return;
	}

	for ( MapList::iterator iter = m_maps.begin(); iter != m_maps.end(); ++iter )
	{
		if ( *iter == pDungeon )
		{
			m_maps.erase( iter );
			break;
		}
	}
	//m_maps.push_back( pDungeon );
	MAP_MANAGER.DelDungeon( pDungeon->GetId() );
}

void CMapRunner::onPlayerLogout( Player *pPlayer, int16_t nGateIndex )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	LOG_DEBUG("Kingdom::onPlayerLogout with player = %p cid = %lld, cgindex = %d\n", pPlayer, pPlayer->getCid(), nGateIndex );
	GAME_SERVICE.onPlayerLogout( pPlayer, nGateIndex );
}

void CMapRunner::onActivityStart( CActivityMap* pMap, CActivity* pActivity )
{
	if ( NULL == pMap || NULL == pActivity )
	{
		return;
	}

	pMap->onActivityStart( pActivity );
}

void CMapRunner::onActivityStop( CActivityMap* pMap, CActivity* pActivity )
{
	if ( NULL == pMap || NULL == pActivity )
	{
		return;
	}

	pMap->onActivityStop( pActivity );
}

void CMapRunner::onStartMoLingRuQin( Map* pMap, int32_t EndTime )
{
	if( NULL == pMap )
	{
		return;
	}
	pMap->OnStartMoLingRuQin( EndTime );
}

void CMapRunner::onKillMonster( Map* pMap, Monster* pMonster )
{
	if( NULL == pMap || NULL == pMonster )
	{
		return;
	}
	pMap->OnKillMonster( pMonster->getEntityId() );
}
