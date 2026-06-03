#include "stdafx.h"

#include "ExtTask.h"
#include "Robot.h"
#include "CfgData.h"
#include "ClientServer.h"

using namespace Answer;

CExtTask::CExtTask()
{
	OnCleanUp();
}

CExtTask::~CExtTask()
{
}

void CExtTask::OnCleanUp()
{
	m_nTaskId		= 0;
	m_nTaskState	= 0;
	m_nKillCount	= 0;
}

void CExtTask::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( SM_TASK_LIST );
	procList.push_back( SM_TASK_KILLED_MONSTER );
	procList.push_back( SM_TASK_RECEIVED );
}

int32_t CExtTask::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case SM_TASK_LIST:				return onTaskList( inPacket );
	case SM_TASK_KILLED_MONSTER:	return onTaskKillMonster( inPacket );
	case SM_TASK_RECEIVED:			return onTaskReceive( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtTask::onTaskList( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int32_t nId		= inPacket->readInt32();
		int8_t nState	= inPacket->readInt8();

		CfgTask* pTask = CFG_DATA.getTask( nId );
		if ( pTask != NULL && pTask->type == TT_TRUNK )
		{
			updateTask( nId, nState );
			break;
		}
	}

	return ERR_OK;
}

int32_t CExtTask::onTaskKillMonster( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int32_t nId		= inPacket->readInt32();
		int32_t nCount	= inPacket->readInt32();
		if ( nId == m_nTaskId )
		{
			m_nKillCount = nCount;
		}
	}

	if ( m_nTaskState == TS_DOING && checkCanSubmit() )
	{
		m_nTaskState = TS_CAN_SUBMIT;
	}

	return ERR_OK;
}

int32_t CExtTask::onTaskReceive( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nTask = inPacket->readInt32();
	CfgTask* pTask = CFG_DATA.getTask( nTask );
	if ( pTask != NULL && pTask->type == TT_TRUNK )
	{
		printf( "Recive task %d\n", nTask );
		updateTask( nTask, TS_DOING );
	}

	return ERR_OK;
}

void CExtTask::EndTask()
{
	CfgTask* pTask = CFG_DATA.getTask( m_nTaskId );
	if ( NULL == pTask )
	{
		printf( "ERR: task %d not find!!!\n", m_nTaskId );
		return;
	}

	switch ( pTask->condition )
	{
	case TC_RECEIVE:
	case TC_MONSTER_ID:			//指定怪物
	case TC_PLAYER_LEVEL:
		SubmitTask();
		break;
	default:
		ForceSubmit();
		break;
	}
}

void CExtTask::SubmitTask()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_nTaskId );

	packet->setType( PACK_PROC );
	packet->setProc( CM_SUBMIT_TASK );
	packet->setSize( packet->getWOffset() );

	m_pRobot->Dispatch( packet );
}

int8_t CExtTask::GetState() const
{
	return m_nTaskState;
}

const TaskDest* CExtTask::GetDest() const
{
	CfgTask* pTask = CFG_DATA.getTask( m_nTaskId );
	if ( NULL == pTask )
	{
		return NULL;
	}

	if ( m_nTaskState == TS_DOING )
	{
		return &( pTask->destCondition );
	}
	else
	{
		return &( pTask->destSubmit );
	}
}

void CExtTask::ForceSubmit()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 17 );					// 提交任务
	packet->writeInt32( m_nTaskId );

	packet->setType( PACK_PROC );
	packet->setProc( CM_DEBUG_CMD );
	packet->setSize( packet->getWOffset() );

	m_pRobot->Dispatch( packet );
}

void CExtTask::updateTask( int32_t nTaskId, int8_t nState )
{
	CfgTask* pTask = CFG_DATA.getTask( nTaskId );
	if ( NULL == pTask )
	{
		printf( "ERR: task %d not find!!!\n", nTaskId );
		return;
	}

	m_nTaskId = nTaskId;
	m_nTaskState = nState;

	if ( m_nTaskState == TS_DOING )
	{
		switch ( pTask->condition )
		{
		case TC_RECEIVE:			m_nTaskState = TS_CAN_SUBMIT;		break;
		case TC_MONSTER_ID:			//指定怪物
		case TC_PLAYER_LEVEL:
			break;
		//case TC_ITEM:
		//	//return m_player->hasItem(cfgTask.request.param1, cfgTask.request.param2, cfgTask.request.param3);
		//case TC_DUNGEON:
		//case TC_USE_ITEM:			//使用物品
		//case TC_PROTECT_BY_CLIENT:
		//case TC_DRESS_EQUIP:
		//	//return it->second.state == TS_CAN_SUBMIT;
		//	break;
		//case TC_MONSTER_LEVEL:		//指定等级怪物
		//case TC_PLANT:				//采集
		//case TC_USER_SKILL:			//使用技能
		//case TC_FINISH_TASK_TYPE:   //完成指定类型任务次数
		//	//return getMonster(tid) >= cfgTask.request.param2;
		//	break;
		//case TC_PET_ILLUSION:		//宠物幻化
		//case TC_UP_EQUIP_STAR:		//装备强化
		//case TC_UP_EQUIP_GRADE:		//装备升级
		//case TC_UP_EQUIP_QUALITY:	//装备提品
		//case TC_HALL_OF_FAME:
		//	break;
		default:
			//ForceSubmit();
			m_nTaskState = TS_CAN_SUBMIT;
			break;
		}
	}
	else if ( m_nTaskState == TS_CAN_SUBMIT )
	{
		CfgNpc* pNpc = CFG_DATA.getNpc( pTask->end_npc );
		if ( pNpc != NULL )
		{
			m_pRobot->SetTarget( pNpc->mapids[0], Position( pNpc->x, pNpc->y ) );
		}
		else
		{
			SubmitTask();
		}
	}
	//else if ( m_nTaskState == TS_DOING )
	//{
	//	switch ( pTask->destCondition.type )
	//	{
	//	case 'n':	// NPC
	//		{
	//			CfgNpc* pNpc = CFG_DATA.getNpc( pTask->destCondition.pram );
	//			if ( pNpc != NULL )
	//			{
	//				m_pRobot->SetTarget( pNpc->mapids[0], Position( pNpc->x, pNpc->y ) );
	//			}
	//			else
	//			{
	//				printf( "CExtTask::updateTask() NPC %d NOT FIND!!!", pTask->destCondition.pram );
	//			}
	//		}
	//		break;
	//	case 'g':	// 怪物
	//		{
	//			CfgMapMonster* pMonster = CFG_DATA.GetMapMonsterInfo( pTask->destCondition.pram );
	//			if ( pMonster != NULL )
	//			{
	//				m_pRobot->SetTarget( pMonster->mapid, Position( pMonster->x, pMonster->y ) );
	//			}
	//			else
	//			{
	//				printf( "CExtTask::updateTask() NPC %d NOT FIND!!!", pTask->destCondition.pram );
	//			}
	//		}
	//		break;
	//	default:
	//		{
	//			ForceSubmit();
	//		}
	//		break;
	//	}
	//}
}

bool CExtTask::checkCanSubmit()
{
	CfgTask* pTask = CFG_DATA.getTask( m_nTaskId );
	if ( pTask != NULL )
	{
		switch ( pTask->condition )
		{
		case TC_RECEIVE: 
			return true;
		case TC_MONSTER_ID:			//指定怪物
		case TC_MONSTER_LEVEL:		//指定等级怪物
		case TC_PLANT:				//采集
		case TC_USER_SKILL:			//使用技能
		case TC_FINISH_TASK_TYPE:   //完成指定类型任务次数
			return m_nKillCount >= pTask->request.param2;
		case TC_PET_ILLUSION:		//宠物幻化
		case TC_UP_EQUIP_STAR:		//装备强化
		case TC_UP_EQUIP_GRADE:		//装备升级
		case TC_UP_EQUIP_QUALITY:	//装备提品
		case TC_HALL_OF_FAME:
		case TC_KILL_BOSS_COUNT:
			return m_nKillCount >=  pTask->request.param1;
		case TC_PLAYER_LEVEL:
			return m_pRobot->getLevel() >= pTask->request.param1;
		default:
			return false;
		}
	}

	return false;
}
