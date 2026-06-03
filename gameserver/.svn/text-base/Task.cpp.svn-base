#include "stdafx.h"
#include "CfgData.h"
#include "DBService.h"
#include "GameService.h"
#include "Map.h"
#include "MapManager.h"
#include "Player.h"
#include "Task.h"

using namespace Answer;

ChrTask::ChrTask()
	: m_player(NULL), m_trunkTaskId(0)
{

}

ChrTask::~ChrTask()
{

}

void ChrTask::init(Player *player, const MemChrTaskVector &tasks)
{
	if (NULL == player)
	{
		return;
	}
	m_player = player;

	for (MemChrTaskVector::const_iterator it = tasks.begin(); it != tasks.end(); ++it)
	{
		CfgTask *cfgTask = CFG_DATA.getTask(it->id);
		if (cfgTask != NULL)
		{
			if (cfgTask->type == TT_TRUNK)
			{
				CfgTask *pCfgLastTrunk = CFG_DATA.getTask(m_trunkTaskId);
				if (pCfgLastTrunk != NULL)
				{
					if (pCfgLastTrunk->main_order > cfgTask->main_order)
					{
						continue;
					}
					else
					{
						m_tasks.erase(m_trunkTaskId);
						m_trunkTaskId = it->id;
					}
				}
				else
				{
					m_trunkTaskId = cfgTask->id;
				}
			}

			m_tasks[it->id] = *it;

			if (it->state == TS_DOING)
			{
				if ( CheckTaskCondition( cfgTask->condition ) )
				{
					TaskMonster taskMonster = {};
					taskMonster.tid = it->id;
					taskMonster.condition = cfgTask->condition;
					taskMonster.request.param1 = cfgTask->request.param1;
					taskMonster.request.param2 = it->monster;
					m_taskMonsters.push_back(taskMonster);
				}
			}
		}
	}
	m_player->GetPlayerFunctionOpen().InitFunctionOpen( m_trunkTaskId, 0 );
}

bool ChrTask::CheckTaskCondition( int32_t taskCondition )
{
	switch( taskCondition )
	{
	case TC_MONSTER_ID:		
	case TC_MONSTER_LEVEL: 
	case TC_PLANT:			
	case TC_USER_SKILL:    
	case TC_PET_ILLUSION:	
	case TC_UP_EQUIP_STAR:	
	case TC_UP_EQUIP_GRADE:	
	case TC_UP_EQUIP_QUALITY:
	case TC_FINISH_TASK_TYPE:
	case TC_HALL_OF_FAME:
	case TC_DRESS_EQUIP:		
	case TC_EQUIP_STAR_COUNT:
	case TC_PET_POINTS_COUNT:
	case TC_KILL_BOSS_COUNT:
		{
			return true;
		}
	default:
		return false;
	}
}

void ChrTask::reset()
{
	m_player = NULL;
	m_tasks.clear();
	m_trunkTaskId = 0;
	m_taskMonsters.clear();
}

int32_t ChrTask::receive( int32_t tid,  int8_t TaskType )
{
	if (m_player == NULL)
	{
		return ERR_INVALID_DATA;
	}

	CfgTask *cfgTask = CFG_DATA.getTask(tid);
	if (cfgTask == NULL)
	{
		return ERR_INVALID_DATA;
	}

	//现在的要接收的id
	if (!receivePreCheck(tid, *cfgTask))
	{
		return ERR_INVALID_DATA;
	}

	if (!m_player->GetBag().AddItemsAndEggs( cfgTask->items_receive, IACR_NONE ))
	{
		return ERR_INVALID_DATA;
	}
// 	if ( cfgTask->type != TaskType )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
	if (cfgTask->type == TT_TRUNK )
	{
		m_tasks.erase( m_trunkTaskId );
	}
	else if ( cfgTask->type == TT_FAMILY )
	{
		int32_t TaskId = GetTypeTask( cfgTask->type );
		if ( TaskId > 0 )
		{
			m_tasks.erase( TaskId );
		}
	}
	else
	{
		if ( cfgTask->pretask != 0 && cfgTask->type == GetTaskType( cfgTask->pretask ) )
		{
			m_tasks.erase( cfgTask->pretask );
		}
	}

	m_tasks[tid].id = tid;
	m_tasks[tid].state = TS_DOING;

	sendTaskReceived(tid);

	TaskMonster taskMonster = {};
	taskMonster.tid = tid;
	taskMonster.condition = cfgTask->condition;
	taskMonster.request.param1 = cfgTask->request.param1;
	
	m_taskMonsters.push_back(taskMonster);
	sendTaskKilledMonster();

	m_player->updateLastTaskId(tid);

	if (cfgTask->type == TT_TRUNK)
	{
		m_trunkTaskId = tid;
	}
	updateTaskCount( TC_DRESS_EQUIP );
	updateTaskCount( TC_EQUIP_STAR_COUNT );
	updateTaskCount( TC_PET_POINTS_COUNT );

	LogTask logTask = {};
	logTask.cid = m_player->getCid();
	logTask.tid = tid;
	logTask.type = cfgTask->type;
	logTask.time = m_player->getNow();
	DB_SERVICE.insertTaskInfo(logTask);

	return ERR_OK;
}

bool ChrTask::ForceSubmit( int32_t tid )
{
	CfgTask *cfgTask = CFG_DATA.getTask(tid);
	if ( cfgTask == NULL )
	{
		return false;
	}

	Int32MemChrTaskMap::iterator it = m_tasks.find(tid);
	if ( it == m_tasks.end() )
	{
		return false;
	}

	if ( it->second.state != TS_DOING && it->second.state != TS_CAN_SUBMIT )
	{
		return false;
	}

	MemChrBagVector add = cfgTask->award_item;
	if (!cfgTask->award_optional.empty())
	{
		for (MemChrJobBagVector::iterator it =cfgTask->award_optional.begin();it !=  cfgTask->award_optional.end();++it)
		{
			if (m_player->getJob() == it->job)
			{
				MemChrBag  chrbag = {};
				chrbag.itemId = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				add.push_back(chrbag);
			}
		}
	}

	m_player->autoUseItem(add);
	if ( !m_player->GetBag().AddItemsAndEggs( add, IACR_TASK ) )
	{
		return false;
	}
	m_player->GetCharPet().ForceSendDirty();

	if ( cfgTask->award_money > 0 )
	{
		m_player->AddCurrency( CURRENCY_BIND_MONEY, static_cast<int32_t>(cfgTask->award_money ), MCR_TASK, cfgTask->id );
	}
	if ( cfgTask->award_exp > 0 )
	{
		m_player->addExp(static_cast<int64_t>(cfgTask->award_exp));
	}
	if ( cfgTask->dilong > 0 )
	{
		m_player->GetPlayerFaBao().AddFaBaoRes( FA_BAO_RES_DI_LONG, static_cast<int32_t>(cfgTask->dilong) );
	}
	if ( cfgTask->rongyu > 0 )
	{
		m_player->AddCurrency( CURRENCY_HONOR, cfgTask->rongyu,MCR_TASK, cfgTask->id );
	}

	if ( cfgTask->type == TT_TRUNK )
	{
		m_player->GetCharPet().OnAddExp( static_cast<int64_t>( cfgTask->award_exp * 0.3f ) );	// 出战宠物获得30%主线任务经验
	}

	m_tasks[tid].id = tid;
	m_tasks[tid].state = TS_SUBMITED;
	m_tasks[tid].monster = 0;
	
	double bnfRatio = m_player->benefitRatio();
	sendTaskSubmitted(tid, static_cast<int32_t>(cfgTask->award_exp * bnfRatio));//防沉迷时间，玩家不能接任务，故无需下发防沉迷状态

	for (TaskMonsterVector::iterator itTaskMonster = m_taskMonsters.begin(); itTaskMonster != m_taskMonsters.end(); ++itTaskMonster)
	{
		if (itTaskMonster->tid == tid)
		{
			m_taskMonsters.erase(itTaskMonster);
			sendTaskKilledMonster();
			break;
		}
	}

	m_player->updateLastTaskId( tid );

	LogTask  logTask = {};
	logTask.cid = m_player->getCid();
	logTask.tid = tid;
	logTask.type = cfgTask->type;
	logTask.time = m_player->getNow();
	logTask.state = 1;
	DB_SERVICE.updateTaskInfo(logTask);

	m_player->GetPlayerFunctionOpen().CheckFunctionOpne( tid, 0 );
	//主线任务自动接收
	if ( cfgTask->type == TT_TRUNK )
	{
		if ( cfgTask->posttask > 0 )
		{
			//receive( cfgTask->posttask );
			int32_t postTaskId = cfgTask->posttask;
			CfgTask *cfgPostTask = CFG_DATA.getTask( postTaskId );
			if ( cfgPostTask == NULL )
			{
				return false;
			}

			m_player->GetBag().AddItemsAndEggs( cfgPostTask->items_receive, IACR_NONE );
			m_tasks.erase( tid );

			m_tasks[postTaskId].id = postTaskId;
			m_tasks[postTaskId].state = TS_DOING;

			sendTaskReceived( postTaskId );

			TaskMonster taskMonster = {};
			taskMonster.tid = postTaskId;
			taskMonster.condition = cfgPostTask->condition;
			taskMonster.request.param1 = cfgPostTask->request.param1;

			m_taskMonsters.push_back( taskMonster );
			sendTaskKilledMonster();

			m_player->updateLastTaskId( postTaskId );
			m_trunkTaskId = postTaskId;

			updateTaskCount( TC_DRESS_EQUIP );
			updateTaskCount( TC_EQUIP_STAR_COUNT );
			updateTaskCount( TC_PET_POINTS_COUNT );

			LogTask logTask = {};
			logTask.cid = m_player->getCid();
			logTask.tid = postTaskId;
			logTask.type = cfgPostTask->type;
			logTask.time = m_player->getNow();
			DB_SERVICE.insertTaskInfo( logTask );
		}
	}
	return true;
}

int32_t ChrTask::submit(int32_t tid)
{
	CfgTask *cfgTask = CFG_DATA.getTask(tid);
	if (cfgTask == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if ( !submitPreCheck(tid, *cfgTask) )
	{
		return ERR_INVALID_DATA;
	}

	ItemDataList itemSubmit;
	if ( cfgTask->condition == TC_ITEM )
	{
		ItemData item = {};
		item.m_nId		= cfgTask->request.param1;
		item.m_nClass	= cfgTask->request.param2;
		item.m_nCount	= cfgTask->request.param3;
		itemSubmit.push_back(item);
	}

	MemChrBagVector add = cfgTask->award_item;
	if (!cfgTask->award_optional.empty())
	{
		for (MemChrJobBagVector::iterator it =cfgTask->award_optional.begin();it !=  cfgTask->award_optional.end();++it)
		{
			if (m_player->getJob() == it->job)
			{
				MemChrBag  chrbag = {};
				chrbag.itemId = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				add.push_back(chrbag);
			}
		}
	}

	
	if ( !m_player->GetBag().RemoveItem(itemSubmit,IDCR_NONE))
	{
		return ERR_INVALID_DATA;
	}
	m_player->autoUseItem(add);
	if ( !m_player->GetBag().AddItemsAndEggs( add, IACR_TASK ) )
	{
		return ERR_INVALID_DATA;
	}
	m_player->GetCharPet().ForceSendDirty();

	if ( cfgTask->award_money > 0 )
	{
		m_player->AddCurrency( CURRENCY_BIND_MONEY, static_cast<int32_t>(cfgTask->award_money ), MCR_TASK, cfgTask->id );
	}
	if ( cfgTask->award_exp > 0 )
	{
		m_player->addExp(static_cast<int64_t>(cfgTask->award_exp));
	}
	if ( cfgTask->dilong > 0 )
	{
		m_player->GetPlayerFaBao().AddFaBaoRes( FA_BAO_RES_DI_LONG, static_cast<int32_t>(cfgTask->dilong) );
	}
	if ( cfgTask->fuwen > 0 )
	{
		m_player->GetPlayerFaBao().AddFaBaoRes( FA_BAO_RES_FU_WEN, static_cast<int32_t>(cfgTask->fuwen) );
	}
	if ( cfgTask->shuguang > 0 )
	{
		m_player->GetPlayerFaBao().AddFaBaoRes( FA_BAO_RES_SHU_GUANG, static_cast<int32_t>(cfgTask->shuguang) );
	}
	if ( cfgTask->rongyu > 0 )
	{
		m_player->AddCurrency( CURRENCY_HONOR, cfgTask->rongyu,MCR_TASK, cfgTask->id );
	}

	if ( cfgTask->gold > 0 )
	{
		m_player->AddCurrency( CURRENCY_CASH, cfgTask->gold,MCR_TASK, cfgTask->id );
	}
	if ( cfgTask->type == TT_TRUNK )
	{
		m_player->GetCharPet().OnAddExp( static_cast<int64_t>( cfgTask->award_exp * 0.3f ) );	// 出战宠物获得30%主线任务经验
	}
	if ( cfgTask->type == TT_FAMILY )
	{
		m_tasks.erase( tid );
		m_player->GetOperateLimit().AddLimitCount( RP_FAMILY_TASK_COUNT, 1 );
		m_player->GetCharFamily().SendAddFamilyTaskCount();
		m_player->GetCharFamily().AddContribution( cfgTask->GongXian, cfgTask->JunTuanZiJin );
	}
	else
	{
		m_tasks[tid].id = tid;
		m_tasks[tid].state = TS_SUBMITED;
		m_tasks[tid].monster = 0;
	}

	
	double bnfRatio = m_player->benefitRatio();
	sendTaskSubmitted(tid, static_cast<int32_t>(cfgTask->award_exp * bnfRatio));//防沉迷时间，玩家不能接任务，故无需下发防沉迷状态

	for (TaskMonsterVector::iterator itTaskMonster = m_taskMonsters.begin(); itTaskMonster != m_taskMonsters.end(); ++itTaskMonster)
	{
		if (itTaskMonster->tid == tid)
		{
			m_taskMonsters.erase(itTaskMonster);
			sendTaskKilledMonster();
			break;
		}
	}

	m_player->updateLastTaskId(tid);

	LogTask  logTask = {};
	logTask.cid = m_player->getCid();
	logTask.tid = tid;
	logTask.type = cfgTask->type;
	logTask.time = m_player->getNow();
	logTask.state = 1;
	DB_SERVICE.updateTaskInfo( logTask );

	m_player->GetPlayerFunctionOpen().CheckFunctionOpne( tid, 0 );
	//主线任务自动接收
	if ( cfgTask->type == TT_TRUNK )
	{
		if ( cfgTask->posttask > 0 )
		{
			receive( cfgTask->posttask, TT_TRUNK );
		}
	}
	return ERR_OK;
}

int32_t ChrTask::giveUp(int32_t tid)
{
	CfgTask *cfgTask = CFG_DATA.getTask(tid);
	if (cfgTask == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if (cfgTask->can_giveup == 0)
	{
		return ERR_INVALID_DATA;
	}

	Int32MemChrTaskMap::iterator it = m_tasks.find(tid);
	if (it == m_tasks.end() || it->second.state != TS_DOING)
	{
		return ERR_INVALID_DATA;
	}

	ItemDataList dataLst;
	for ( MemChrBagVector::iterator iter = cfgTask->items_receive.begin(); iter != cfgTask->items_receive.end(); ++iter )
	{
		ItemData data = {};
		data.m_nId		= iter->itemId;
		data.m_nCount	= iter->itemCount;
		data.m_nClass	= IC_NORMAL;
		dataLst.push_back( data );
	}
	if ( !m_player->GetBag().RemoveItem( dataLst, IDCR_NONE ) )
	{
		return ERR_INVALID_DATA;
	}

	m_tasks.erase(tid);

	sendTaskGiveUped(tid);

	for (TaskMonsterVector::iterator itTaskMonster = m_taskMonsters.begin(); itTaskMonster != m_taskMonsters.end(); ++itTaskMonster)
	{
		if (itTaskMonster->tid == tid)
		{
			m_taskMonsters.erase(itTaskMonster);
			sendTaskKilledMonster();
			break;
		}
	}
	return ERR_OK;
}

void ChrTask::checkTaskCanSubmit(int32_t dungenID)
{
	   //不会 去做 两个 任务 都是通关 同一个FB的情况
   for (Int32MemChrTaskMap::iterator it = m_tasks.begin();it != m_tasks.end();++it)
   {
	   CfgTask* pTask = CFG_DATA.getTask(it->second.id);
	   if (pTask != NULL && pTask->condition  == TC_DUNGEON && pTask->request.param1 == dungenID && it->second.state != TS_SUBMITED)
	   {
		   it->second.state =  TS_CAN_SUBMIT;

		   sendTaskList();

		   NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_CAN_SUBMIT);
		   if (NULL == packet)
		   {
			   continue;
		   }
		   packet->writeInt32(it->second.id);
		   packet->setSize(packet->getWOffset());
		   GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);

		   break;
	   }
   }
}

int32_t ChrTask::quickDone(int32_t tid)
{
	CfgTask *cfgTask = CFG_DATA.getTask(tid);
	if (cfgTask == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if ( m_player->GetCurrency( CURRENCY_GOLD ) < 5 )
	{
		return ERR_INVALID_DATA;
	}

	Int32MemChrTaskMap::iterator it = m_tasks.find(tid);
	if (it == m_tasks.end() || it->second.state != TS_DOING)
	{
		return ERR_INVALID_DATA;
	}

	MemChrBagVector add = cfgTask->award_item;
	if (!cfgTask->award_optional.empty())
	{
		for (MemChrJobBagVector::iterator it =cfgTask->award_optional.begin();it !=  cfgTask->award_optional.end();++it)
		{
			if (m_player->getJob() == it->job)
			{
				MemChrBag  chrbag = {};
				chrbag.itemId = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				add.push_back(chrbag);
			}
		}
	}

	m_player->autoUseItem(add);
	if (!m_player->GetBag().AddItemsAndEggs( add, IACR_TASK ))
	{
		return ERR_INVALID_DATA;
	}

	m_player->AddCurrency( CURRENCY_MONEY, static_cast<int32_t>(cfgTask->award_money), MCR_TASK, cfgTask->id );
	m_player->addExp(static_cast<int64_t>(cfgTask->award_exp));
	m_player->GetPlayerFaBao().AddFaBaoRes( FA_BAO_RES_DI_LONG, static_cast<int32_t>(cfgTask->dilong) );

	m_tasks[tid].id = tid;
	m_tasks[tid].state = TS_SUBMITED;
	m_tasks[tid].monster = 0;

	double bnfRatio = m_player->benefitRatio();
	sendTaskSubmitted(tid, static_cast<int32_t>( cfgTask->award_exp * bnfRatio ) );

	for (TaskMonsterVector::iterator itTaskMonster = m_taskMonsters.begin(); itTaskMonster != m_taskMonsters.end(); ++itTaskMonster)
	{
		if (itTaskMonster->tid == tid)
		{
			m_taskMonsters.erase(itTaskMonster);
			sendTaskKilledMonster();
			break;
		}
	}
	BenefitType bnfType = m_player->benefitType();
	m_player->updateLastTaskId(tid);
	m_player->DecCurrency( CURRENCY_GOLD, 5, GCR_QUICK_TASK, tid );
	//m_player->sendBagItems();

//	DB_SERVICE.logGoldCashCost(m_player, GCC_QUICK_DONE, -5, cfgTask->id, 1, m_player->getNow());

	LogTask  logTask = {};
	logTask.cid = m_player->getCid();
	logTask.tid = tid;
	logTask.type = cfgTask->type;
	logTask.time = m_player->getNow();
	logTask.state = 2;
	DB_SERVICE.updateTaskInfo( logTask );

	return ERR_OK;
}

bool ChrTask::receivePreCheck(int32_t tid, const CfgTask &cfgTask)
{
	if (m_player == NULL)
	{
		return false;
	}

	Int32MemChrTaskMap::iterator itTask = m_tasks.find(tid);
	if (itTask != m_tasks.end())
	{
		return false;
	}

	if (cfgTask.type == TT_CYCLE )//|| cfgTask.type == TT_KINGDOM || cfgTask.type == TT_FACTION)
	{
		return false;
	}

	if (cfgTask.start_npc != 0)
	{
		CfgNpc *cfgNpc = CFG_DATA.getNpc(cfgTask.start_npc);
		if (cfgNpc == NULL)
		{
			return false;
		}

		if (!cfgNpc->findMapId(m_player->getMapId()))
		{
			return false;
		}
	}

	if (cfgTask.pretask != 0)
	{
		CfgTask *pCfgPreTask = CFG_DATA.getTask(cfgTask.pretask);
		if (pCfgPreTask == NULL)
		{
			return false;
		}

		if ( cfgTask.type == TT_TRUNK)
		{
			CfgTask *pCfgTrunkTask = CFG_DATA.getTask(m_trunkTaskId);
			if (pCfgTrunkTask == NULL)
			{
				return false;
			}

			Int32MemChrTaskMap::iterator itTrunk = m_tasks.find(m_trunkTaskId);
			if (itTrunk == m_tasks.end())
			{
				return false;
			}

			if (itTrunk->second.id == tid)
			{
				return false;
			}

			if ( pCfgPreTask->id == pCfgTrunkTask->id )
			{
				if (itTrunk->second.state != TS_SUBMITED)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			CfgTask *pCfg = CFG_DATA.getTask(cfgTask.pretask);
			if (pCfg == NULL)
			{
				return false;
			}
			if ( pCfg->type != cfgTask.type )
			{
				if ( GetTypeTask( cfgTask.type ) > 0 )
				{
					return false;
				}
				int32_t TaskId = GetTypeTask( pCfg->type );
				CfgTask *pHasCfg = CFG_DATA.getTask(TaskId);
				if ( pHasCfg == NULL )
				{
					return false;
				}
				if ( pHasCfg->main_order < pCfg->main_order )
				{
					return false;
				}
			}
			else
			{
				Int32MemChrTaskMap::iterator itPreTask = m_tasks.find(cfgTask.pretask);
				if (itPreTask == m_tasks.end() || itPreTask->second.state != TS_SUBMITED)
				{
					return false;
				}
			}
		}
	}
	else
	{
		 if ( cfgTask.type != TT_TRUNK || cfgTask.type == TT_FAMILY )
		{
			if ( GetTypeTask( cfgTask.type ) > 0 )
			{
				return false;
			}
		}

	}

	if (cfgTask.job != 0)
	{
		if (cfgTask.job == 100)
		{
			if (m_player->getJob() == 0)
			{
				return false;
			}
		}
		else
		{
			if (m_player->getJob() != cfgTask.job)
			{
				return false;
			}
		}
	}

	if ( m_player->getLevel() < cfgTask.level || m_player->getLevel() > cfgTask.max_level)
	{
		return false;
	}

	return true;
}

bool ChrTask::submitPreCheck(int32_t tid,  const CfgTask &cfgTask)
{
	if (m_player == NULL)
	{
		return false;
	}

	if (cfgTask.end_npc != 0)
	{
		CfgNpc *cfgNpc = CFG_DATA.getNpc(cfgTask.end_npc);
		if (cfgNpc == NULL)
		{
			return false;
		}

		if (!cfgNpc->findMapId(m_player->getMapId()))
		{
			return false;
		}
	}

	Int32MemChrTaskMap::iterator it = m_tasks.find(tid);
	if (it == m_tasks.end())
	{
		return false;
	}

	if (it->second.state != TS_DOING && it->second.state != TS_CAN_SUBMIT)
	{
		return false;
	}
	if ( cfgTask.type == TT_FAMILY )
	{
		if ( m_player->getFamilyId() <= 0 )
		{
			return false;
		}
	}
	switch (cfgTask.condition)
	{
	case TC_RECEIVE: 
		return true;
	case TC_ITEM:
		return m_player->hasItem(cfgTask.request.param1, cfgTask.request.param2, cfgTask.request.param3);
	case TC_DUNGEON:
	case TC_USE_ITEM:			//使用物品
	case TC_PROTECT_BY_CLIENT:
	case TC_DRESS_EQUIP:
	case TC_EQUIP_STAR_COUNT:
	case TC_PET_POINTS_COUNT:
		return it->second.state == TS_CAN_SUBMIT;
	case TC_MONSTER_ID:			//指定怪物
	case TC_MONSTER_LEVEL:		//指定等级怪物
	case TC_PLANT:				//采集
	case TC_USER_SKILL:			//使用技能
	case TC_FINISH_TASK_TYPE:   //完成指定类型任务次数
		return getMonster(tid) >= cfgTask.request.param2;
	case TC_PET_ILLUSION:		//宠物幻化
	case TC_UP_EQUIP_STAR:		//装备强化
	case TC_UP_EQUIP_GRADE:		//装备升级
	case TC_UP_EQUIP_QUALITY:	//装备提品
	case TC_HALL_OF_FAME:
	case TC_KILL_BOSS_COUNT:
		return getMonster(tid) >=  cfgTask.request.param1;
	case TC_PLAYER_LEVEL:
		return m_player->getLevel() >= cfgTask.request.param1;
	default:
		return false;
	}
}

void ChrTask::updateTaskUseItem( int32_t id ,int32_t Count )
{
	bool update = false;

	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		switch (it->condition)
		{
		case TC_USE_ITEM:
			if ( id == it->request.param1 )
			{
				TaskRequest Request = GetTaskCfgRequest( it->tid );
				if ( Request.param2 > it->request.param2 )
				{
					update = true;
				}
				it->request.param2 += Count;
			}
			break;
		default:
			break;
		}
	}

	if (update)
	{
		sendTaskKilledMonster();
	}
}

void ChrTask::updateTaskTypeCount( int32_t taskType )
{
	bool update = false;

	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		switch (it->condition)
		{
		case TC_FINISH_TASK_TYPE:
			if ( taskType == it->request.param1 )
			{
				TaskRequest Request = GetTaskCfgRequest( it->tid );
				if ( Request.param2 > it->request.param2 )
				{
					update = true;
				}
				it->request.param2++;
			}
			break;
		default:
			break;
		}
	}

	if (update)
	{
		sendTaskKilledMonster();
	}
}

void ChrTask::updateTaskMonster(int32_t mid, int32_t level)
{
	bool update = false;

	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		switch (it->condition)
		{
		case TC_PLANT:
		case TC_MONSTER_ID:
			if (mid == it->request.param1)
			{
				TaskRequest Request = GetTaskCfgRequest( it->tid );
				if ( Request.param2 > it->request.param2 )
				{
					update = true;
				}
				it->request.param2++;
			}
			break;
		case TC_MONSTER_LEVEL:
			if (level >= it->request.param1)
			{
				TaskRequest Request = GetTaskCfgRequest( it->tid );
				if ( Request.param2 > it->request.param2 )
				{
					update = true;
				}
				it->request.param2++;
			}
			break;
		default:
			break;
		}
	}

	if (update)
	{
		sendTaskKilledMonster();
	}
}

void ChrTask::updateTaskSkill(int32_t skillID)
{
	bool update = false;

	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		switch (it->condition)
		{
		case TC_USER_SKILL:
			if (it->request.param1 ==  skillID)
			{
				TaskRequest Request = GetTaskCfgRequest( it->tid );
				if ( Request.param2 > it->request.param2 )
				{
					update = true;
				}
				it->request.param2++;
			}
			break;
		default:
			break;
		}
	}

	if (update)
	{
		sendTaskKilledMonster();
	}
}

void ChrTask::updateTaskCount( int32_t Condition )
{
	bool update = false;

	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		if ( it->condition != Condition )
		{
			continue;
		}

		switch ( it->condition )
		{
		case TC_PET_ILLUSION:		
		case TC_UP_EQUIP_STAR:	
		case TC_UP_EQUIP_GRADE:	
		case TC_UP_EQUIP_QUALITY:
		case TC_HALL_OF_FAME:
		case TC_KILL_BOSS_COUNT:
			if ( it->request.param1 > it->request.param2 )
			{
				TaskRequest Request = GetTaskCfgRequest( it->tid );
				if ( Request.param1 > it->request.param2 )
				{
					update = true;
				}
				it->request.param2++;
			}
			break;
		case TC_DRESS_EQUIP:
			{
				Int32MemChrTaskMap::iterator itTask = m_tasks.find(it->tid);
				if ( itTask == m_tasks.end() )
				{
					continue;
				}
				if ( itTask->second.state != TS_DOING )
				{
					continue;
				}
				int32_t Count = m_player->GetEquip().HaveLevelEquipCount( it->request.param1 );
				if ( Count != it->request.param2 )
				{
					it->request.param2 = Count;

					CfgTask *pCfgTask = CFG_DATA.getTask(it->tid);
					if ( NULL == pCfgTask )
					{
						continue;
					}
					if ( it->request.param2 >= pCfgTask->request.param2 )
					{
						setTaskCanSubmit( it->tid );
					}
					update = true;
				}
			}
			break;
		case TC_EQUIP_STAR_COUNT:
			{
				Int32MemChrTaskMap::iterator itTask = m_tasks.find(it->tid);
				if ( itTask == m_tasks.end() )
				{
					continue;
				}
				if ( itTask->second.state != TS_DOING )
				{
					continue;
				}
				int32_t Count = m_player->GetEquip().HaveStarEquipCount( it->request.param1 );
				if ( Count != it->request.param2 )
				{
					it->request.param2 = Count;

					CfgTask *pCfgTask = CFG_DATA.getTask(it->tid);
					if ( NULL == pCfgTask )
					{
						continue;
					}
					if ( it->request.param2 >= pCfgTask->request.param2 )
					{
						setTaskCanSubmit( it->tid );
					}
					update = true;
				}
			}
			break;
		case TC_PET_POINTS_COUNT:
			{
				Int32MemChrTaskMap::iterator itTask = m_tasks.find(it->tid);
				if ( itTask == m_tasks.end() )
				{
					continue;
				}
				if ( itTask->second.state != TS_DOING )
				{
					continue;
				}
				int32_t Count = m_player->GetCharPet().HavePetCountByPoints( it->request.param1 );
				if ( Count != it->request.param2 )
				{
					it->request.param2 = Count;

					CfgTask *pCfgTask = CFG_DATA.getTask(it->tid);
					if ( NULL == pCfgTask )
					{
						continue;
					}
					if ( it->request.param2 >= pCfgTask->request.param2 )
					{
						setTaskCanSubmit( it->tid );
					}
					update = true;
				}
			}
			break;
		default:
			break;
		}
	}

	if (update)
	{
		sendTaskKilledMonster();
	}
}

void ChrTask::updateTaskDrop(int32_t tid, int32_t itemid)
{
	if (m_player == NULL)
	{
		return;
	}

	Int32MemChrTaskMap::iterator itTask = m_tasks.find(tid);
	if (itTask != m_tasks.end() && itTask->second.state == TS_DOING)
	{
		CfgTask *pCfgTask = CFG_DATA.getTask(tid);
		if (pCfgTask != NULL && pCfgTask->condition == TC_ITEM && pCfgTask->request.param1 == itemid && !m_player->hasItem(pCfgTask->request.param1, pCfgTask->request.param2, pCfgTask->request.param3))
		{
			MemChrBag item = {};
			item.itemId = itemid;
			item.itemClass = IC_NORMAL;
			item.itemCount = 1;
			m_player->GetBag().AddItem( item, IACR_NONE );
		}
	}
}

void ChrTask::cmdResetTrunkTask(int32_t trunkTaskId)
{
	CfgTask *pCfgTask = CFG_DATA.getTask(trunkTaskId);
	if (pCfgTask != NULL && pCfgTask->type == TT_TRUNK)
	{
		for (TaskMonsterVector::iterator itTaskMonster = m_taskMonsters.begin(); itTaskMonster != m_taskMonsters.end(); ++itTaskMonster)
		{
			if (itTaskMonster->tid == m_trunkTaskId)
			{
				m_taskMonsters.erase(itTaskMonster);
				sendTaskKilledMonster();
				break;
			}
		}
		m_tasks.erase(m_trunkTaskId);
		m_tasks[trunkTaskId].id = trunkTaskId;
		m_tasks[trunkTaskId].monster = 0;
		m_tasks[trunkTaskId].state = TS_DOING;
		m_trunkTaskId = trunkTaskId;

		TaskMonster taskMonster = {};
		taskMonster.tid = trunkTaskId;
		taskMonster.condition = pCfgTask->condition;
		taskMonster.request.param1 = pCfgTask->request.param1;
		m_taskMonsters.push_back(taskMonster);
		sendTaskList();
	}
}

bool ChrTask::isDoingTaskType(int32_t type)
{
	for (Int32MemChrTaskMap::iterator it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		if (it->second.state == TS_DOING)
		{
			CfgTask *pCfg = CFG_DATA.getTask(it->second.id);
			if (pCfg != NULL && pCfg->type == type)
			{
				return true;
			}
		}
	}

	return false;
}

void ChrTask::setTaskCanSubmit(int32_t tid)
{
	Int32MemChrTaskMap::iterator it = m_tasks.find(tid);
	if (it != m_tasks.end() && it->second.state == TS_DOING)
	{
		it->second.state = TS_CAN_SUBMIT;

		sendTaskList();

		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_CAN_SUBMIT);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(tid);
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);
	}
}

void ChrTask::sendTaskList()
{
	if (m_player == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_LIST);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(static_cast<int32_t>(m_tasks.size()));
	for (Int32MemChrTaskMap::iterator it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		packet->writeInt32(it->second.id);
		packet->writeInt8(static_cast<int8_t>(it->second.state));
	}
	packet->setSize(packet->getWOffset());

	GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);

	sendTaskKilledMonster();
}

void ChrTask::sendTaskKilledMonster()
{
	if (m_player == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_KILLED_MONSTER);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(m_taskMonsters.size());
	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		packet->writeInt32(it->tid);
		packet->writeInt32(it->request.param2);
	}
	packet->setSize(packet->getWOffset());

	GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);
}

void ChrTask::saveToDB(Answer::NetPacket *packet)
{
	if (NULL == packet)
	{
		return;
	}
	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		Int32MemChrTaskMap::iterator itTask = m_tasks.find(it->tid);
		if (itTask != m_tasks.end())
		{
			itTask->second.monster = it->request.param2;
		}
	}

	packet->writeInt32(static_cast<int32_t>(m_tasks.size()));
	for (Int32MemChrTaskMap::iterator it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		packet->writeInt32(it->second.id);
		packet->writeInt32(it->second.state);
		packet->writeInt32(it->second.monster);

	}
}

void ChrTask::SaveDBData( PlayerDBData& dbData )
{
	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		Int32MemChrTaskMap::iterator itTask = m_tasks.find(it->tid);
		if (itTask != m_tasks.end())
		{
			itTask->second.monster = it->request.param2;
		}
	}

	dbData.taskData.taskVt.reserve( m_tasks.size() );
	for (Int32MemChrTaskMap::iterator it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		MemChrTask task = {};
		task.id			= it->second.id;
		task.state		= it->second.state;
		task.monster	= it->second.monster;
		dbData.taskData.taskVt.push_back(task);
	}
}

int32_t ChrTask::getMonster(int32_t tid)
{
	for (TaskMonsterVector::iterator it = m_taskMonsters.begin(); it != m_taskMonsters.end(); ++it)
	{
		if (it->tid == tid) 
		{
			return it->request.param2;
		}
	}

	return 0;
}

void ChrTask::sendTaskReceived(int32_t tid)
{
	if (m_player == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_RECEIVED);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(tid);
	packet->setSize(packet->getWOffset());

	GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);
}

void ChrTask::sendTaskSubmitted(int32_t tid, int32_t exp)
{
	if (m_player == NULL)
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_SUBMITTED); //任务提交显示国家选择界面10100
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(tid);
	packet->writeInt32(exp);
	packet->setSize(packet->getWOffset());

	GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);

	//sendSelectKingdom();
}

void ChrTask::sendTaskGiveUped(int32_t tid)
{
	if (m_player == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_TASK_GIVEUPED);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(tid);
	packet->setSize(packet->getWOffset());

	GAME_SERVICE.sendPacketTo(m_player->getGateIndex(), packet);
}

int32_t ChrTask::GetTypeTask( int8_t Type )
{
	
	Int32MemChrTaskMap::iterator it = m_tasks.begin();
	for ( ; it != m_tasks.end(); ++it )
	{
		CfgTask *cfgTask = CFG_DATA.getTask( it->second.id );
		if ( NULL == cfgTask )
		{
			continue;
		}
		if ( cfgTask->type == Type )
		{
			return it->second.id;
		}
	}
	return 0;
}

int8_t ChrTask::GetTaskType( int32_t TaskId )
{
	Int32MemChrTaskMap::iterator it = m_tasks.find( TaskId );
	if ( it != m_tasks.end() )
	{
		CfgTask *cfgTask = CFG_DATA.getTask( it->second.id );
		if ( NULL != cfgTask )
		{
			return cfgTask->type;
		}
	}
	return 0;
}

TaskRequest ChrTask::GetTaskCfgRequest( int32_t Tid )
{
	TaskRequest stu = {};
	CfgTask *cfgTask = CFG_DATA.getTask( Tid );
	if ( NULL == cfgTask )
	{
		return stu;
	}
	return cfgTask->request;
}