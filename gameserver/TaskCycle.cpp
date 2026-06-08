#include "stdafx.h"

#include "DBService.h"
#include "GameService.h"
#include "Player.h"
#include "TaskCycle.h"
#include "MapManager.h"

#define MAX_CYCLE_FINISH_TIMES	20

int32_t vExpRatio[MAX_CYCLE_STARS]	= { 100, 110, 120, 130, 140, 160, 180, 200, 240, 300 };
int32_t vDragonRatio[MAX_CYCLE_STARS] = { 100, 110, 120, 130, 140, 150, 160, 170, 180, 200 };

using namespace Answer;

CExtChrTaskCycle::CExtChrTaskCycle()
{
	OnCleanUp();
}

CExtChrTaskCycle::~CExtChrTaskCycle()
{

}

void CExtChrTaskCycle::OnCleanUp()
{
	m_nFinishTimes	= 0;
	m_nTaskId		= 0;
	m_nStar			= 0;
	m_nKills		= 0;
	m_nState		= 0;
	m_nMonsterId	= 0;
	m_nNeedKills	= 0;
	m_nRefreshStarTimes	= 0;
}

void CExtChrTaskCycle::OnLoadFromDB( const PlayerDBData& dbData )
{
	if ( !IsFunctionOpen() || NULL == m_pPlayer )
	{
		return;
	}
	m_nFinishTimes		= dbData.taskCycleData.nFinishTimes;
	m_nTaskId			= dbData.taskCycleData.nTaskId;
	m_nStar				= dbData.taskCycleData.nStar;
	m_nState			= dbData.taskCycleData.nState;
	m_nKills			= dbData.taskCycleData.nKills;
	m_nRefreshStarTimes	= dbData.taskCycleData.nRefreshStarTimes;
	CfgTask* pTask = CFG_DATA.getTask( m_nTaskId );
	if ( pTask != NULL )
	{
		m_nMonsterId = pTask->request.param1;
		m_nNeedKills = pTask->request.param2;
	}
}

void CExtChrTaskCycle::OnSaveToDB( PlayerDBData& dbData )
{
	if ( !IsFunctionOpen() )
	{
		return;
	}
	dbData.taskCycleData.nFinishTimes		= m_nFinishTimes;
	dbData.taskCycleData.nTaskId			= m_nTaskId;
	dbData.taskCycleData.nStar				= m_nStar;
	dbData.taskCycleData.nState				= m_nState;
	dbData.taskCycleData.nKills				= m_nKills;
	dbData.taskCycleData.nRefreshStarTimes	= m_nRefreshStarTimes;
}

void CExtChrTaskCycle::OnDaySwitch( int32_t nDiffDays )
{
	if ( !IsFunctionOpen() )
	{
		return;
	}

	if ( m_nFinishTimes > 0 )
	{
		m_nFinishTimes = 0;
		m_nRefreshStarTimes	= 0;
		sendTaskInfo();
	}
}

void CExtChrTaskCycle::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_TASK_CYCLE_RECEIVE );
	procList.push_back( CM_TASK_CYCLE_SUBMIT );
	procList.push_back( CM_TASK_CYCLE_REFRESH_STAR );
	procList.push_back( CM_TASK_CYCLE_BUY_TIMES );
}

int32_t CExtChrTaskCycle::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case CM_TASK_CYCLE_RECEIVE:				return onReceiveTask( inPacket );
	case CM_TASK_CYCLE_SUBMIT:				return onSubmitTask( inPacket );
	case CM_TASK_CYCLE_REFRESH_STAR:		return onRefreshStar( inPacket );
	case CM_TASK_CYCLE_BUY_TIMES:			return OnBuyCycleTaskTime( inPacket );
	default:break;
	}
	return ERR_OK;
}

int32_t CExtChrTaskCycle::OnBuyCycleTaskTime( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t BuyTimes = m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES );
	if ( BuyTimes >= m_pPlayer->GetPlayerVip().AddDailyTaskTimes() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t NeedGold = 5;
	int64_t HaveGold = m_pPlayer->GetCurrency( CURRENCY_GOLD );
	if ( HaveGold < NeedGold )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, NeedGold, GCR_BUY_CYCLE_TASK_COUNT ) )
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->GetOperateLimit().AddLimitCount( PR_BUY_CYCLE_TIMES, 1 );
	sendTaskInfo();
	return ERR_OK;
}

int32_t CExtChrTaskCycle::onReceiveTask( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	int32_t TaskId = inPacket->readInt32();
	int32_t MapId  = inPacket->readInt32();
	int32_t Pox	   = inPacket->readInt32();
	int32_t Poy	   = inPacket->readInt32();
	if ( m_nTaskId != TaskId )
	{
		return ERR_INVALID_DATA;
	}
	int32_t BuyTimes = m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES );
	if ( m_nFinishTimes >= GetTaskCycleTimes() + BuyTimes )
	{
		return ERR_SYETEM_ERR;
	}

	if ( m_nState != TS_CAN_RECEIVE )
	{
		return ERR_INVALID_DATA;
	}

	m_nState = TS_DOING;
	sendTaskInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), m_nTaskId );
	Map *pTargetMap = MAP_MANAGER.GetMap( MapId );
	if ( pTargetMap != NULL )
	{
		if ( pTargetMap == m_pPlayer->getMap() )
		{
			m_pPlayer->instantMove(Pox, Poy, IMR_TRANSFER);
		}
		else
		{
			m_pPlayer->switchMap(pTargetMap, Pox, Poy, false);
		}
	}

	LogTask logTask = {};
	logTask.cid = m_pPlayer->getCid();
	logTask.tid = m_nTaskId;
	logTask.type = TT_CYCLE;
	logTask.time = m_pPlayer->getNow();
	DB_SERVICE.insertTaskInfo(logTask);
	return ERR_OK;
}

int32_t CExtChrTaskCycle::onSubmitTask( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_nState != TS_CAN_SUBMIT )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nRadio	= inPacket->readInt8();
	int8_t nPayType	= inPacket->readInt8();
	int32_t nNeedGold = 0;
	int32_t nNeedMoney = 0;
	int32_t nLevel = m_pPlayer->getLevel();

	switch ( nRadio )
	{
	case 1:	break;																	// ������ȡ
	case 2:	nNeedMoney = incInt( static_cast<double>( nLevel - 60 ) / 60 ) * 200000;	break;	// ˫����ȡ
	case 3:																			// ������ȡ
		{
			if ( nPayType == CURRENCY_MONEY )
			{
				nNeedMoney = incInt( static_cast<double>( nLevel - 60 ) / 60 ) * 500000;
			}
			else if ( nPayType == CURRENCY_GOLD )
			{
				nNeedGold = 100;
			}
			else
			{
				return ERR_INVALID_DATA;
			}
		}
		break;
	default: return ERR_INVALID_DATA;
	}

	if ( nNeedMoney > 0 && !m_pPlayer->GetCurrency().DecMoneyAndNoBind( nNeedMoney, GCR_TASK_CYCLE_GET_REWARD, nRadio ) )
	{
		return ERR_INVALID_DATA;
	}
	if ( nNeedGold > 0 && !m_pPlayer->DecCurrency( CURRENCY_GOLD, nNeedGold, GCR_TASK_CYCLE_GET_REWARD, nRadio ) )
	{
		return ERR_INVALID_DATA;
	}

	LogTask  logTask = {};
	logTask.cid = m_pPlayer->getCid();
	logTask.tid = m_nTaskId;
	logTask.type = TT_CYCLE;
	logTask.time = m_pPlayer->getNow();
	logTask.state = nRadio;
	DB_SERVICE.updateTaskInfo(logTask);

	addReward( nRadio );
	++m_nFinishTimes;
// 	if ( m_nFinishTimes >= GetTaskCycleTimes() )
// 	{
// 		m_nTaskId		= 0;
// 		m_nStar			= 0;
// 		m_nState		= TS_SUBMITED;	
// 		m_nKills		= 0;
// 		m_nMonsterId	= 0;
// 		m_nNeedKills	= 0;
// 		m_nRefreshStarTimes = 0;
// 	}
// 	else
	{
		m_nRefreshStarTimes = 0;
		refreshTask();
		refreshStar();
	}

	sendTaskInfo();
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_CYCLE_TASK );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), m_nTaskId );
	return ERR_OK;
}

int32_t CExtChrTaskCycle::onRefreshStar( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_nFinishTimes >= GetTaskCycleTimes() + m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES ) )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_nState != TS_CAN_RECEIVE )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nLevel = m_pPlayer->getLevel();
	int32_t nNeedMoney = nLevel < 500 ? 10000 : 0;//nLevel < 90 ? 10000 : incInt( static_cast<double>( nLevel - 80 ) / 10 ) * 10000;
	if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( nNeedMoney, GCR_TASK_CYCLE_REFRESH_STAR ) )
	{
		return ERR_INVALID_DATA;
	}

	refreshStar();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), m_nStar );
	return ERR_OK;
}

void CExtChrTaskCycle::UpdateTaskMonster(int32_t mid, int32_t level)
{
	if ( mid == m_nMonsterId && m_nState == TS_DOING )
	{
		++m_nKills;
		if ( m_nKills >= m_nNeedKills )
		{
			m_nState = TS_CAN_SUBMIT;
		}
		sendTaskInfo();
	}
}

void CExtChrTaskCycle::SendTaskCycle()
{
	sendTaskInfo();
}

bool CExtChrTaskCycle::IsFunctionOpen()
{
	// �ճ��������50����ʱ�򿪷�(���忪�ŵȼ���Ҫ������������ʱ�����)��
	return true;
}

void CExtChrTaskCycle::OpenCycleTask()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	refreshTask();
	m_nStar = 7;			//����ѭ������ʱ����
	sendTaskInfo();
}

void CExtChrTaskCycle::sendTaskInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TASK_CYCLE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_nFinishTimes );
	packet->writeInt32( m_nTaskId );
	packet->writeInt8( m_nStar );
	packet->writeInt8( m_nState );
	packet->writeInt32( m_nKills );
	if ( m_nFinishTimes >= GetTaskCycleTimes() )
	{
		packet->writeInt32( GetTaskCycleTimes() + m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES ) - m_nFinishTimes );
	}
	else
	{
		packet->writeInt32( m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES ) );
	}
	packet->writeInt32( m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES ) );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtChrTaskCycle::refreshTask()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_nTaskId = CFG_DATA.GetTaskCycleTable().RandTask( m_pPlayer->getLevel() );
	CfgTask* pTask = CFG_DATA.getTask( m_nTaskId );
	if ( NULL == pTask )
	{
		return;
	}

	m_nMonsterId = pTask->request.param1;
	m_nNeedKills = pTask->request.param2;
	m_nKills = 0;
	m_nStar = 0;
	m_nState = TS_CAN_RECEIVE;
}

void CExtChrTaskCycle::refreshStar()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( m_pPlayer->getRecord(RP_CYCLE_FLUSH) == 0 || m_nRefreshStarTimes >= CFG_DATA.GetTaskCycleTable().GetTenStarTimes( m_pPlayer->getLevel() )  )
	{
		m_nStar = MAX_CYCLE_STARS;
	}
	else
	{
		int32_t i = 0;
		int32_t OldStar = m_nStar;
		while( OldStar == m_nStar )
		{
			i++;
			m_nStar = CFG_DATA.GetTaskCycleTable().RandStar( m_pPlayer->getLevel() );
			if ( i >= 10 )
			{
				break;
			}
		}

	}
	++m_nRefreshStarTimes;
	m_pPlayer->GetOperateLimit().AddLimitCount( RP_CYCLE_FLUSH,  1);
}

void CExtChrTaskCycle::addReward( int8_t nRadio )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int8_t nIndex = m_nStar - 1;
	if ( nIndex < 0 || nIndex >= MAX_CYCLE_STARS )
	{
		return;
	}

	int32_t nExpRadio		= vExpRatio[nIndex];
	int32_t nDragonRatio	= vDragonRatio[nIndex];

	CfgTask* pTask = CFG_DATA.getTask( m_nTaskId );
	if ( NULL == pTask )
	{
		return;
	}

	int64_t texp = static_cast<int64_t>( pTask->award_exp ) * nExpRadio;
	int32_t exp = static_cast<int32_t>( texp % 100 == 0 ? texp / 100 : texp / 100 + 1 );
	int32_t nAddExp = exp * nRadio;
	m_pPlayer->addExp( nAddExp );

	int64_t tdl = static_cast<int64_t>( pTask->dilong ) * nDragonRatio;
	int32_t ndl = static_cast<int32_t>( tdl % 100 == 0 ? tdl / 100 : tdl / 100 + 1 );
	int32_t nDiLong = ndl * nRadio;
	m_pPlayer->GetPlayerFaBao().AddFaBaoRes( FA_BAO_RES_DI_LONG, nDiLong );
	m_pPlayer->GetTask().updateTaskTypeCount( pTask->type );
}

int32_t CExtChrTaskCycle::GetTaskCycleTimes()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	return MAX_CYCLE_FINISH_TIMES;
}

int32_t	CExtChrTaskCycle::GetSurplusTimes()
{
	int32_t BuyTimes = m_pPlayer->GetOperateLimit().GetLimitCount( PR_BUY_CYCLE_TIMES );
	return GetTaskCycleTimes() + m_pPlayer->GetPlayerVip().AddDailyTaskTimes() - m_nFinishTimes;
}

int32_t	CExtChrTaskCycle::GetDrawTimes()
{
	return GetSurplusTimes();
}