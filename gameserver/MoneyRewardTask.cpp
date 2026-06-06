#include "MoneyRewardTask.h"
#include "Player.h"
#include "Bag.h"
#include "CfgData.h"
#include "Task.h"
#include "Currency.h"
#include "Vip.h"
#include "HuoYueDu.h"
#include "DailyActivity.h"
#include "GameService.h"
#include "PDUDefine.h"
#include "FunctionOpen.h"
#include "FaBao.h"
#include "DBService.h"
#include "Trailer.h"
#include "PoolManager.h"
#include "ActivityManager.h"
#include <sstream>

using namespace Answer;

CMoneyRewardTask::CMoneyRewardTask()
{
	m_pPlayer = NULL;
	OnCleanUp();
}

CMoneyRewardTask::~CMoneyRewardTask()
{
}

void CMoneyRewardTask::OnCleanUp()
{
	for ( int32_t i = 0; i <= 8; ++i )
	{
		m_MoneyRewardTask[i].TaskId = 0;
		m_MoneyRewardTask[i].TaskState = 0;
	}
	m_IsGetReward = 0;
	m_FinishTimes = 0;
	m_TaskId = 0;
	m_Star = 0;
	m_RandStarTimes = 0;
	m_PdbfFinishTimes = 0;
	m_EquipBackTaskId = 0;
	m_EquipBackTaskFinishTimes = 0;
	m_RandEquipBackTaskStarTimes = 0;
	for ( int32_t j = 0; j <= 3; ++j )
	{
		m_XiangYaoTask[j].TaskId = 0;
		m_XiangYaoTask[j].TaskState = 0;
	}
	m_XiangYaoFinishTimes = 0;
	m_RefreshTimes = 0;
	for ( int32_t k = 0; k <= 4; ++k )
		m_ShenWeiTaskState[k] = 0;
}

void CMoneyRewardTask::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_FinishTimes = dbData.m_MoneyRewardTaskData.m_FinishTimes;
	m_IsGetReward = dbData.m_MoneyRewardTaskData.m_IsGetReward;
	m_TaskId = dbData.m_MoneyRewardTaskData.m_TaskId;
	m_Star = dbData.m_MoneyRewardTaskData.m_Star;
	m_RandStarTimes = dbData.m_MoneyRewardTaskData.m_RandStarTimes;
	m_PdbfFinishTimes = dbData.m_MoneyRewardTaskData.m_PdbfFinishTimes;
	m_EquipBackTaskId = dbData.m_MoneyRewardTaskData.m_EquipBackTaskId;
	m_EquipBackTaskFinishTimes = dbData.m_MoneyRewardTaskData.m_EquipBackTaskFinishTimes;
	m_RandEquipBackTaskStarTimes = dbData.m_MoneyRewardTaskData.m_RandEquipBackTaskStarTimes;
	m_JieBiaoTimes = dbData.m_MoneyRewardTaskData.m_JieBiaoTimes;
	m_YaBiaoTimes = dbData.m_MoneyRewardTaskData.m_YaBiaoTimes;
	m_TrailerQuality = dbData.m_MoneyRewardTaskData.m_TrailerQuality;
	m_EndTime = dbData.m_MoneyRewardTaskData.m_EndTime;
	m_XiangYaoFinishTimes = dbData.m_MoneyRewardTaskData.m_XiangYaoFinishTimes;
	m_RefreshTimes = dbData.m_MoneyRewardTaskData.m_RefreshTimes;
	parseXiangYaoTask( dbData.m_MoneyRewardTaskData.m_XiangYaoTask );
	parseMoneyRewardTaskInfo( dbData.m_MoneyRewardTaskData.m_MoneyRewardTaskInfo );
	parseShenWeiTask( dbData.m_MoneyRewardTaskData.m_ShenWeiTask );
	if ( IsPdbfFunctionOpen() && !m_TaskId && !m_Star && !m_RandStarTimes && !m_PdbfFinishTimes )
		InitPdbfTask();
	if ( IsBackEquipFunctionOpen() && !m_EquipBackTaskId && !m_EquipBackTaskFinishTimes && !m_RandEquipBackTaskStarTimes )
		InitEquipBackTask();
	if ( m_EndTime > 0 && m_pPlayer && m_pPlayer->getNow() > m_EndTime )
	{
		ResetTrailer();
		m_EndTime = 0;
	}
	if ( !m_TrailerQuality )
		ResetTrailer();
	LoginInitXiangYaoTask();
	LoginInitShenWeiTask();
}

void CMoneyRewardTask::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_MoneyRewardTaskData.m_FinishTimes = m_FinishTimes;
	dbData.m_MoneyRewardTaskData.m_IsGetReward = m_IsGetReward;
	dbData.m_MoneyRewardTaskData.m_MoneyRewardTaskInfo = GetMoneyRewardTaskInfo();
	dbData.m_MoneyRewardTaskData.m_TaskId = m_TaskId;
	dbData.m_MoneyRewardTaskData.m_Star = m_Star;
	dbData.m_MoneyRewardTaskData.m_RandStarTimes = m_RandStarTimes;
	dbData.m_MoneyRewardTaskData.m_PdbfFinishTimes = m_PdbfFinishTimes;
	dbData.m_MoneyRewardTaskData.m_EquipBackTaskId = m_EquipBackTaskId;
	dbData.m_MoneyRewardTaskData.m_EquipBackTaskFinishTimes = m_EquipBackTaskFinishTimes;
	dbData.m_MoneyRewardTaskData.m_RandEquipBackTaskStarTimes = m_RandEquipBackTaskStarTimes;
	dbData.m_MoneyRewardTaskData.m_JieBiaoTimes = m_JieBiaoTimes;
	dbData.m_MoneyRewardTaskData.m_YaBiaoTimes = m_YaBiaoTimes;
	dbData.m_MoneyRewardTaskData.m_TrailerQuality = m_TrailerQuality;
	dbData.m_MoneyRewardTaskData.m_EndTime = m_EndTime;
	dbData.m_MoneyRewardTaskData.m_XiangYaoFinishTimes = m_XiangYaoFinishTimes;
	dbData.m_MoneyRewardTaskData.m_RefreshTimes = m_RefreshTimes;
	dbData.m_MoneyRewardTaskData.m_XiangYaoTask = saveXiangYaoTaskString();
	dbData.m_MoneyRewardTaskData.m_ShenWeiTask = saveShenWeiTaskString();
}

void CMoneyRewardTask::OnDaySwitch( int32_t nDiffDays )
{
	if ( IsFunctionOpen() ) InitMoneyRewardTask();
	if ( IsPdbfFunctionOpen() ) InitPdbfTask();
	if ( IsBackEquipFunctionOpen() ) InitEquipBackTask();
	if ( IsXiangYaoFunctionOpen() ) InitXiangYaoTask();
	if ( IsShenWeiFunctionOPen() ) InitShenWeiTask();
	if ( m_pPlayer && m_pPlayer->getRecord(1001) )
	{
		InitXuWuTask();
		InitXinMoTask();
	}
	m_JieBiaoTimes = 0;
	m_YaBiaoTimes = 0;
	SendTrailerInfo();
}

void CMoneyRewardTask::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_SUBMIT_MONEY_REWARD_TASK );
	procList.push_back( CM_GET_MONEY_REWARD );
	procList.push_back( CM_SUBMIT_PDBF_TASK );
	procList.push_back( CM_PDBF_RAND_STAR );
	procList.push_back( CM_SUBMIT_EQUIP_BACK_TASK );
	procList.push_back( CM_EQUIP_BACK_TASK_RAND_STAR );
	procList.push_back( CM_RECEIVE_PDBF_TASK );
	procList.push_back( CM_ASK_TRAILER_POS );
	procList.push_back( CM_RAND_TRAILER );
	procList.push_back( CM_START_TRAILER );
	procList.push_back( CM_SUB_TRAILER );
	procList.push_back( CM_REQUEST_SUPPORT );
	procList.push_back( CM_RECEIVE_MONEY_REWARD_TASK );
	procList.push_back( CM_RECEIVE_EQUIP_BACK_TASK );
	procList.push_back( CM_ONE_KEY_COMPLETION );
	procList.push_back( CM_ASK_XIANG_YAO_TASK );
	procList.push_back( CM_OPERATOR_TASK );
	procList.push_back( CM_REFRESH_TASK );
	procList.push_back( CM_OPERATOR_SHEN_WEI_TASK );
}

int32_t CMoneyRewardTask::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( !inPacket ) return ERR_INVALID_DATA;
	switch ( nProcId )
	{
	case CM_SUBMIT_MONEY_REWARD_TASK: return OnSubmitMoneyRewardTask( inPacket );
	case CM_GET_MONEY_REWARD: return OnGetReward( inPacket );
	case CM_SUBMIT_PDBF_TASK: return OnSubmitPdbfTask( inPacket );
	case CM_PDBF_RAND_STAR: return OnPdbfRandStar( inPacket );
	case CM_SUBMIT_EQUIP_BACK_TASK: return OnSubmitEquipBackTask( inPacket );
	case CM_EQUIP_BACK_TASK_RAND_STAR: return OnEquipBackTaskRandStar( inPacket );
	case CM_RECEIVE_PDBF_TASK: return OnReceivePdbfTask( inPacket );
	case CM_ASK_TRAILER_POS: return OnAskTrailerPos( inPacket );
	case CM_RAND_TRAILER: return OnRandTrailer( inPacket );
	case CM_START_TRAILER: return OnStartTrailer( inPacket );
	case CM_SUB_TRAILER: return OnSubTrailer( inPacket );
	case CM_REQUEST_SUPPORT: return OnRequestSupport( inPacket );
	case CM_RECEIVE_MONEY_REWARD_TASK: return OnReceiveMoneyRewardTask( inPacket );
	case CM_RECEIVE_EQUIP_BACK_TASK: return OnReceiveEquipBackTask( inPacket );
	case CM_ONE_KEY_COMPLETION: return OneKeyCompletion( inPacket );
	case CM_ASK_XIANG_YAO_TASK: return OnAskXiangYaoTask( inPacket );
	case CM_OPERATOR_TASK: return OnOperatorTask( inPacket );
	case CM_REFRESH_TASK: return OnRefreshTask( inPacket );
	case CM_OPERATOR_SHEN_WEI_TASK: return OnOperatorShenWeiTask( inPacket );
	}
	return 0;
}

bool CMoneyRewardTask::IsFunctionOpen()
{
	if ( !m_pPlayer ) return false;
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 178 );
}

void CMoneyRewardTask::InitMoneyRewardTask()
{
	if ( !m_pPlayer ) return;
	m_pPlayer->GetTask().CleanTaskType( 2 );
	CFG_DATA.InitMoneyRewardTask( &m_MoneyRewardTask, m_pPlayer->getLevel() );
	m_MoneyRewardTask[0].TaskState = 2;
	m_IsGetReward = 0;
	m_FinishTimes = 0;
	sendTaskInfo();
}

int32_t CMoneyRewardTask::OnReceiveMoneyRewardTask( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	if ( m_FinishTimes > 8 ) return ERR_INVALID_DATA;
	int32_t TaskId = m_MoneyRewardTask[m_FinishTimes].TaskId;
	if ( m_pPlayer->GetTask().receive( TaskId, TT_TRUNK ) ) return ERR_INVALID_DATA;
	m_MoneyRewardTask[m_FinishTimes].TaskState = 3;
	sendTaskInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnGetReward( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	if ( m_FinishTimes <= 8 ) return ERR_INVALID_DATA;
	if ( m_IsGetReward ) return ERR_INVALID_DATA;
	MemChrBag stu;
	memset( &stu, 0, sizeof(stu) );
	stu.itemId = 7000;
	stu.itemCount = 1;
	stu.itemClass = 1;
	if ( !m_pPlayer->GetBag().AddItem( stu, IACR_TASK ) ) return ERR_INVALID_DATA;
	m_IsGetReward = 1;
	sendTaskInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnSubmitMoneyRewardTask( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	int32_t TaskId = inPacket->readInt32();
	int8_t nTimes = inPacket->readInt8();
	if ( nTimes <= 0 || nTimes > 2 ) return ERR_INVALID_DATA;
	const CfgTask* cfgTask = CFG_DATA.getTask( TaskId );
	if ( !cfgTask ) return ERR_INVALID_DATA;
	if ( nTimes == 2 )
	{
		if ( cfgTask->gold <= 0 ) return ERR_INVALID_DATA;
		float Rate = 1.0f;
		CVip& vip = m_pPlayer->GetPlayerVip();
		//if ( vip.GetVipFlg( 2 ) ) Rate = 0.8f;
		int32_t nCost = (int32_t)((float)cfgTask->gold * Rate);
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCost, MCR_TASK ) ) return ERR_INVALID_DATA;
	}
	if ( m_FinishTimes > 8 ) return ERR_INVALID_DATA;
	if ( m_MoneyRewardTask[m_FinishTimes].TaskId != TaskId ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().submit( TaskId ) ) return ERR_INVALID_DATA;
	m_MoneyRewardTask[m_FinishTimes++].TaskState = 5;
	if ( m_FinishTimes > 0 && m_FinishTimes <= 8 )
		m_MoneyRewardTask[m_FinishTimes].TaskState = 2;
	sendTaskInfo();
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 13 );
	return 0;
}

int32_t CMoneyRewardTask::OneKeyCompletion( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int32_t Times = inPacket->readInt32();
	if ( Times <= 0 || Times > 2 ) return ERR_INVALID_DATA;
	//if ( !m_pPlayer->GetPlayerVip().GetVipFlg( 3 ) ) return ERR_INVALID_DATA;
	if ( m_FinishTimes > 8 ) return ERR_INVALID_DATA;
	if ( m_FinishTimes < 0 ) m_FinishTimes = 0;
	int32_t Money = 0;
	int32_t FuWen = 0;
	MemChrBagVector Items;
	int32_t NeedGold = 0;
	for ( int32_t i = m_FinishTimes; i <= 8; ++i )
	{
		int32_t TaskId = m_MoneyRewardTask[i].TaskId;
		const CfgTask* cfgTask = CFG_DATA.getTask( TaskId );
		if ( cfgTask )
		{
			if ( cfgTask->award_money > 0 ) Money += Times * cfgTask->award_money;
			if ( cfgTask->fuwen > 0 ) FuWen += Times * cfgTask->fuwen;
			for ( size_t j = 0; j < cfgTask->award_item.size(); ++j )
			{
				MemChrBag stu = cfgTask->award_item[j];
				stu.itemCount *= Times;
				Items.push_back( stu );
			}
			if ( cfgTask->gold > 0 ) NeedGold += cfgTask->gold;
		}
	}
	if ( (int32_t)Items.size() > m_pPlayer->GetBag().GetFreeSlotCount() ) return ERR_INVALID_DATA;
	if ( Times == 2 )
	{
		float Rate = 1.0f;
		//if ( m_pPlayer->GetPlayerVip().GetVipFlg( 2 ) ) Rate = 0.8f;
		int32_t nCost = (int32_t)((float)NeedGold * Rate);
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCost, MCR_TASK ) ) return ERR_INVALID_DATA;
	}
	if ( !Items.empty() )
	{
		if ( !m_pPlayer->GetBag().AddItem( Items, IACR_TASK ) ) return ERR_INVALID_DATA;
	}
	if ( FuWen > 0 )
		m_pPlayer->GetPlayerFaBao().AddFaBaoRes( (FaBaoResourceType)7, FuWen );
	if ( Money > 0 )
		m_pPlayer->AddCurrency( CURRENCY_BIND_MONEY, Money, MCR_TASK );
	for ( int32_t i = m_FinishTimes; i <= 8; ++i )
	{
		m_MoneyRewardTask[m_FinishTimes++].TaskState = 5;
		m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 13 );
	}
	m_pPlayer->GetTask().CleanTaskType( 2 );
	sendTaskInfo();
	m_pPlayer->GetTask().updateTaskTypeCount( 2 );
	return 0;
}

void CMoneyRewardTask::sendTaskInfo()
{
	if ( !m_pPlayer || !IsFunctionOpen() ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_MONEY_REWARD_TASK_INFO );
	if ( !packet ) return;
	packet->writeInt32( m_FinishTimes );
	packet->writeInt8( m_IsGetReward );
	packet->writeInt32( 9 );
	for ( int32_t i = 0; i <= 8; ++i )
	{
		packet->writeInt32( m_MoneyRewardTask[i].TaskId );
		packet->writeInt8( m_MoneyRewardTask[i].TaskState );
	}
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CMoneyRewardTask::parseMoneyRewardTaskInfo( const std::string& infoString )
{
	if ( infoString.empty() )
	{
		if ( IsFunctionOpen() ) InitMoneyRewardTask();
		return;
	}
	// Parse format: "i|TaskId|TaskState:|"
	// Split by "|:" to get individual entries, then each entry by "|"
	StringVector entries = Answer::StringUtility::split( infoString, "|:" );
	for ( size_t i = 0; i < entries.size(); ++i )
	{
		StringVector fields = Answer::StringUtility::split( entries[i], "|" );
		if ( fields.size() == 3 )
		{
			int32_t nIndex = atoi( fields[0].c_str() );
			if ( nIndex >= 0 && nIndex <= 8 )
			{
				m_MoneyRewardTask[nIndex].TaskId = atoi( fields[1].c_str() );
				m_MoneyRewardTask[nIndex].TaskState = (int8_t)atoi( fields[2].c_str() );
			}
		}
	}
}

std::string CMoneyRewardTask::GetMoneyRewardTaskInfo()
{
	std::ostringstream oss;
	for ( int32_t i = 0; i <= 8; ++i )
	{
		oss << i << "|" << m_MoneyRewardTask[i].TaskId << "|" << (int32_t)m_MoneyRewardTask[i].TaskState << ":|";
	}
	return oss.str();
}

bool CMoneyRewardTask::IsPdbfFunctionOpen()
{
	if ( !m_pPlayer ) return false;
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 179 );
}

void CMoneyRewardTask::InitPdbfTask()
{
	if ( !m_pPlayer ) return;
	m_pPlayer->GetTask().CleanTaskType( 4 );
	m_TaskId = RandTaskId();
	m_Star = RandStar();
	m_RandStarTimes = 1;
	m_PdbfFinishTimes = 0;
	SendPdbfTaskInfo();
}

int32_t CMoneyRewardTask::OnReceivePdbfTask( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().isDoingTaskType( 4 ) ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().receive( m_TaskId, TT_TRUNK ) ) return ERR_INVALID_DATA;
	return 0;
}

int32_t CMoneyRewardTask::OnSubmitPdbfTask( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	int32_t TaskId = inPacket->readInt32();
	int32_t Times = inPacket->readInt32();
	if ( Times != 1 && Times != 2 ) return ERR_INVALID_DATA;
	if ( m_TaskId != TaskId ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().submit( m_TaskId ) ) return ERR_INVALID_DATA;
	if ( ++m_PdbfFinishTimes <= 0 || m_PdbfFinishTimes > 2 )
	{
		m_TaskId = 0;
		m_Star = 0;
		m_RandStarTimes = 0;
	}
	else
	{
		m_TaskId = RandTaskId();
		m_Star = RandStar();
		m_RandStarTimes = 1;
	}
	SendPdbfTaskInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnPdbfRandStar( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	if ( m_Star == 10 ) return ERR_INVALID_DATA;
	if ( m_TaskId <= 0 ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().isDoingTaskType( 4 ) ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, 10, GCR_QUICK_TASK ) ) return ERR_INVALID_DATA;
	if ( m_RandStarTimes == 15 )
		m_Star = 10;
	else
		m_Star = RandStar();
	SendPdbfTaskInfo();
	return 0;
}

void CMoneyRewardTask::SendPdbfTaskInfo()
{
	if ( !m_pPlayer || !IsPdbfFunctionOpen() ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PDBF_TASK_INFO );
	if ( !packet ) return;
	packet->writeInt32( m_TaskId );
	packet->writeInt32( m_Star );
	packet->writeInt32( m_PdbfFinishTimes );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CMoneyRewardTask::RandTaskId()
{
	if ( !m_pPlayer ) return 0;
	return CFG_DATA.RandPdbfTask( m_pPlayer->getLevel() );
}

int32_t CMoneyRewardTask::RandStar()
{
	return RANDOM.generate( 1, 10 );
}

float CMoneyRewardTask::GetPdbfRewardRate()
{
	return (float)(m_Star + 10) / 10.0f;
}

bool CMoneyRewardTask::IsBackEquipFunctionOpen()
{
	if ( !m_pPlayer ) return false;
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 180 );
}

void CMoneyRewardTask::InitEquipBackTask()
{
	if ( !m_pPlayer ) return;
	m_EquipBackTaskId = RandTaskIndex( 1 );
	m_EquipBackTaskFinishTimes = 0;
	m_RandEquipBackTaskStarTimes = 1;
	SendBackEquipTaskInfo();
}

int32_t CMoneyRewardTask::OnReceiveEquipBackTask( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().isDoingTaskType( 6 ) ) return ERR_INVALID_DATA;
	if ( m_EquipBackTaskFinishTimes >= GetEquipBackTaskLimit() ) return ERR_INVALID_DATA;
	if ( !m_EquipBackTaskId ) InitEquipBackTask();
	m_pPlayer->GetTask().receive( m_EquipBackTaskId, TT_TRUNK );
	return 0;
}

int32_t CMoneyRewardTask::OnSubmitEquipBackTask( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;

	int32_t Bagslot = inPacket->readInt32();
	int32_t times = inPacket->readInt32();
	if ( times <= 0 || times > 2 ) return ERR_INVALID_DATA;

	if ( !m_pPlayer->GetTask().isDoingTaskType( 6 ) ) return ERR_INVALID_DATA;

	MemChrBag BagItem = m_pPlayer->GetBag().GetSlotData( Bagslot );
	if ( BagItem.itemClass != 2 ) return ERR_INVALID_DATA;

	if ( m_EquipBackTaskFinishTimes >= GetEquipBackTaskLimit() ) return ERR_INVALID_DATA;

	const CfgTask* pCfg = CFG_DATA.getTask( m_EquipBackTaskId );
	if ( !pCfg ) return ERR_INVALID_DATA;

	const BackEquipTask* pTask = CFG_DATA.GetBackEquipTask( m_EquipBackTaskId );
	if ( !pTask ) return ERR_INVALID_DATA;

	const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( BagItem.itemId );
	if ( !pCfgEquip ) return ERR_INVALID_DATA;

	// Check if the equip id is in the task's allowed equip list
	bool bFind = false;
	for ( Int32Vector::const_iterator iter = pTask->Equips.begin(); iter != pTask->Equips.end(); ++iter )
	{
		if ( *iter == BagItem.itemId )
		{
			bFind = true;
			break;
		}
	}
	if ( !bFind ) return ERR_INVALID_DATA;

	// Check free slots for reward items
	if ( (int32_t)pTask->Items.size() > m_pPlayer->GetBag().GetFreeSlotCount() ) return ERR_INVALID_DATA;

	// If double submission, deduct gold
	if ( times == 2 )
	{
		float Rate = 1.0f;
		//if ( m_pPlayer->GetPlayerVip().GetVipFlg( 2 ) ) Rate = 0.8f;
		int32_t nCost = (int32_t)((float)pCfg->gold * Rate);
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCost, GCR_DOUBLE_BACK_EQUIP, 0 ) )
			return ERR_INVALID_DATA;
	}

	// Remove the equipped item from bag
	m_pPlayer->GetBag().CleanSlot( Bagslot, IDCR_EQUIP_BACK_TASK );

	// Build reward items (scaled by times)
	MemChrBagVector ItemTmp;
	for ( size_t i = 0; i < pTask->Items.size(); ++i )
	{
		MemChrBag stu = pTask->Items[i];
		stu.itemCount *= times;
		ItemTmp.push_back( stu );
	}

	// Add reward items to bag
	if ( !ItemTmp.empty() )
	{
		if ( !m_pPlayer->GetBag().AddItem( ItemTmp, IACR_EQUIP_BACK_TASK_GET ) )
			return ERR_INVALID_DATA;
	}

	// Add vigor reward
	if ( pTask->nGetCurr > 0 )
	{
		m_pPlayer->AddCurrency( CURRENCY_VIGOUR, times * pTask->nGetCurr, VCR_EQUIP_BACK_TASK );
	}

	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 14 );

	// Log task completion to DB
	LogTask logTask = {};
	logTask.cid = m_pPlayer->getCid();
	logTask.tid = m_EquipBackTaskId;
	logTask.type = 6;
	logTask.time = m_pPlayer->getNow();
	logTask.state = 1;
	DB_SERVICE.insertTaskInfo( logTask );

	++m_EquipBackTaskFinishTimes;
	m_EquipBackTaskId = RandTaskIndex( 1 );
	m_RandEquipBackTaskStarTimes = 1;
	SendBackEquipTaskInfo();

	return 0;
}

int32_t CMoneyRewardTask::OnEquipBackTaskRandStar( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	const BackEquipTask* pTask = CFG_DATA.GetBackEquipTask( m_EquipBackTaskId );
	if ( !pTask ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().isDoingTaskType( 6 ) ) return ERR_INVALID_DATA;
	if ( pTask->nStar > 9 ) return ERR_INVALID_DATA;
	if ( pTask->nRandGold <= 0 ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pTask->nRandGold, MCR_TASK ) ) return ERR_INVALID_DATA;
	m_EquipBackTaskId = RandTaskIndex( m_RandEquipBackTaskStarTimes );
	++m_RandEquipBackTaskStarTimes;
	SendBackEquipTaskInfo();
	return 0;
}

int32_t CMoneyRewardTask::GetEquipBackTaskLimit()
{
	return 3;
}

int32_t CMoneyRewardTask::RandTaskIndex( int32_t nRandTimes )
{
	if ( !m_pPlayer ) return 0;
	m_pPlayer->GetTask().CleanTaskType( 6 );
	if ( m_pPlayer->getRecord( 1910 ) <= 0 )
	{
		m_pPlayer->updateRecord( 1910, 1 );
		nRandTimes = 15;
	}
	return CFG_DATA.GetEquipBackTaskId( m_pPlayer->getLevel(), nRandTimes );
}

void CMoneyRewardTask::SendBackEquipTaskInfo()
{
	if ( !m_pPlayer || !IsBackEquipFunctionOpen() ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_BACK_EQUIP_TASK_INFO );
	if ( !packet ) return;
	packet->writeInt32( m_EquipBackTaskId );
	packet->writeInt32( m_EquipBackTaskFinishTimes );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CMoneyRewardTask::OnAskTrailerPos( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	Trailer* pTrailer = m_pPlayer->getTrailer();
	if ( pTrailer )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TRAILER_INFO );
		if ( packet )
			pTrailer->appendInfo( packet );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
	}
	return 0;
}

int32_t CMoneyRewardTask::OnRandTrailer( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	int8_t AutoBuy = inPacket->readInt8();
	if ( m_EndTime > 0 ) return ERR_INVALID_DATA;
	if ( m_TrailerQuality <= 0 ) ResetTrailer();
	int32_t nNewQuality = m_TrailerQuality + 1;
	// Simplified: no quality-based cost for this codebase version
	RandTrailer();
	SendTrailerInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnStartTrailer( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	if ( m_YaBiaoTimes >= GetYaBiaoLimit() ) return ERR_INVALID_DATA;
	const CfgNpc* cfgNpc = CFG_DATA.getNpc( 1060 );
	if ( !cfgNpc || !cfgNpc->findMapId( m_pPlayer->getMapId() ) ) return ERR_INVALID_DATA;
	if ( m_EndTime > 0 ) return ERR_INVALID_DATA;
	if ( m_TrailerQuality <= 0 ) ResetTrailer();
	const CfgTrailer* pCfgTrailer = CFG_DATA.getTrailer();
	if ( !pCfgTrailer ) return ERR_INVALID_DATA;
	Trailer* pTrailer = POOL_MANAGER.pop<Trailer>();
	if ( !pTrailer ) return ERR_INVALID_DATA;
	++m_YaBiaoTimes;
	m_EndTime = m_pPlayer->getNow() + 1800;
	pTrailer->init( *pCfgTrailer, m_pPlayer, 0, m_pPlayer->getMapId(), cfgNpc->x, cfgNpc->y, m_EndTime, 100 );
	GAME_SERVICE.addTrailer( pTrailer );
	m_pPlayer->setTrailer( pTrailer );
	SendTrailerInfo();
	// Broadcast announcement for high quality
	int32_t GongGaoId = 0;
	if ( m_TrailerQuality == 3 ) GongGaoId = 427;
	else if ( m_TrailerQuality == 4 ) GongGaoId = 428;
	if ( GongGaoId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet )
		{
			packet->writeInt32( GongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}
	return 0;
}

int32_t CMoneyRewardTask::OnSubTrailer( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	const CfgNpc* cfgNpc = CFG_DATA.getNpc( 1061 );
	if ( !cfgNpc || !cfgNpc->findMapId( m_pPlayer->getMapId() ) ) return ERR_INVALID_DATA;
	if ( !cfgNpc->findMapId( m_pPlayer->getMapId() ) ) return ERR_INVALID_DATA;
	if ( m_EndTime <= 0 ) return ERR_INVALID_DATA;
	if ( m_TrailerQuality <= 0 ) ResetTrailer();
	Trailer* pTrailer = m_pPlayer->getTrailer();
	if ( !pTrailer ) return ERR_INVALID_DATA;
	pTrailer->leaveMap();
	// Simplified reward: basic delivery reward
	m_pPlayer->AddCurrency( CURRENCY_BIND_MONEY, 1000 * m_TrailerQuality, MCR_TASK );
	m_pPlayer->AddCurrency( CURRENCY_HONOR, 10 * m_TrailerQuality, MCR_TASK );
	m_pPlayer->GetPlayerFaBao().AddFaBaoRes( (FaBaoResourceType)7, 5 * m_TrailerQuality );
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 12 );
	GAME_SERVICE.removeTrailer( pTrailer );
	POOL_MANAGER.push<Trailer>( pTrailer );
	m_pPlayer->setTrailer( NULL );
	ResetTrailer();
	m_EndTime = 0;
	SendTRailerEnd();
	SendTrailerInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnRequestSupport( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	if ( m_pPlayer->getFamilyId() <= 0 ) return ERR_INVALID_DATA;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_PROC, SM_REQUEST_SUPPORT );
	if ( !packet ) return ERR_INVALID_DATA;
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt32( m_pPlayer->getMapId() );
	packet->writeInt16( m_pPlayer->GetPosX() );
	packet->writeInt16( m_pPlayer->GetPosY() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
	return 0;
}

void CMoneyRewardTask::AddJieBiaoTimes()
{
	++m_JieBiaoTimes;
	SendTrailerInfo();
}

int32_t CMoneyRewardTask::GetYaBiaoLimit()
{
	int32_t nLimit = 3;
	//if ( m_pPlayer->GetPlayerVip().GetVipFlg( 3 ) ) nLimit = 4;
	return nLimit;
}

void CMoneyRewardTask::RandTrailer()
{
	if ( m_TrailerQuality <= 0 ) ResetTrailer();
	m_TrailerQuality = CFG_DATA.RandQuality( m_TrailerQuality );
}

void CMoneyRewardTask::ResetTrailer()
{
	// Implementation depends on config
	m_TrailerQuality = 1;
}

void CMoneyRewardTask::SendTrailerInfo()
{
	if ( !m_pPlayer ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TRAILER_INFO );
	if ( !packet ) return;
	packet->writeInt32( m_JieBiaoTimes );
	packet->writeInt32( m_YaBiaoTimes );
	packet->writeInt8( m_TrailerQuality );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CMoneyRewardTask::SendTRailerEnd()
{
	if ( !m_pPlayer ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TRAILER_END );
	if ( !packet ) return;
	packet->writeInt8( 0 );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

bool CMoneyRewardTask::IsXiangYaoFunctionOpen()
{
	if ( !m_pPlayer ) return false;
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 193 );
}

void CMoneyRewardTask::InitXiangYaoTask()
{
	if ( !m_pPlayer ) return;
	m_pPlayer->GetTask().CleanTaskType( 7 );
	m_XiangYaoFinishTimes = 0;
	m_RefreshTimes = 0;
	RandXiangYaoTask( false, false );
	SendXiangYaoTaskInfo();
}

void CMoneyRewardTask::OnXiangYaoFunctionOpen()
{
	RandXiangYaoTask( false, false );
	SendXiangYaoTaskInfo();
}

int32_t CMoneyRewardTask::OnAskXiangYaoTask( Answer::NetPacket* inPacket )
{
	SendXiangYaoTaskInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnOperatorTask( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	int8_t nId = inPacket->readInt8();
	int8_t nOper = inPacket->readInt8();
	if ( nId <= 0 || nId > 4 ) return ERR_INVALID_DATA;
	int32_t nIndex = nId - 1;
	if ( nOper == 1 )
	{
		// Receive task
		if ( m_XiangYaoFinishTimes > 9 ) return ERR_INVALID_DATA;
		if ( m_pPlayer->GetTask().isDoingTaskType( 7 ) ) return ERR_INVALID_DATA;
		if ( m_XiangYaoTask[nIndex].TaskState != 1 ) return ERR_INVALID_DATA;
		if ( CFG_DATA.getTask( m_XiangYaoTask[nIndex].TaskId )->type != 7 ) return ERR_INVALID_DATA;
		if ( m_pPlayer->GetTask().receive( m_XiangYaoTask[nIndex].TaskId, TT_TRUNK ) ) return ERR_INVALID_DATA;
		m_XiangYaoTask[nIndex].TaskState = 2;
		++m_XiangYaoFinishTimes;
	}
	else if ( nOper == 2 )
	{
		// Submit task
		int32_t TaskId = m_XiangYaoTask[nIndex].TaskId;
		if ( !m_pPlayer->GetTask().isDoingTaskType( CFG_DATA.getTask(TaskId)->type ) ) return ERR_INVALID_DATA;
		if ( m_XiangYaoTask[nIndex].TaskState != 2 ) return ERR_INVALID_DATA;
		if ( m_pPlayer->GetTask().submit( TaskId ) ) return ERR_INVALID_DATA;
		m_pPlayer->GetTask().CleanTaskType( 7 );
		m_XiangYaoTask[nIndex].TaskState = 3;
		if ( NeedRefreshTask() ) RandXiangYaoTask( false, true );
	}
	else if ( nOper == 3 )
	{
		// Drop task
		if ( m_XiangYaoTask[nIndex].TaskState != 2 ) return ERR_INVALID_DATA;
		int32_t TaskId = m_XiangYaoTask[nIndex].TaskId;
		if ( !m_pPlayer->GetTask().isDoingTaskType( CFG_DATA.getTask(TaskId)->type ) ) return ERR_INVALID_DATA;
		m_pPlayer->GetTask().CleanTaskType( 7 );
		m_XiangYaoTask[nIndex].TaskState = 4;
		if ( NeedRefreshTask() ) RandXiangYaoTask( false, true );
	}
	else if ( nOper == 4 )
	{
		// Quick done
		if ( m_XiangYaoTask[nIndex].TaskState != 2 ) return ERR_INVALID_DATA;
		int32_t TaskId = m_XiangYaoTask[nIndex].TaskId;
		if ( m_pPlayer->GetTask().quickDone( TaskId ) ) return ERR_INVALID_DATA;
		m_pPlayer->GetTask().CleanTaskType( 7 );
		m_XiangYaoTask[nIndex].TaskState = 3;
		if ( NeedRefreshTask() ) RandXiangYaoTask( false, true );
	}
	else
		return ERR_INVALID_DATA;
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 15 );
	SendXiangYaoTaskInfo();
	return 0;
}

int32_t CMoneyRewardTask::OnRefreshTask( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket ) return ERR_INVALID_DATA;
	if ( m_XiangYaoFinishTimes > 9 ) return ERR_INVALID_DATA;
	if ( !IsXiangYaoFunctionOpen() ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetTask().isDoingTaskType( 7 ) ) return ERR_INVALID_DATA;
	int8_t IsBest = inPacket->readInt8();
	int32_t NeedCost = 0;
	if ( IsBest <= 0 )
	{
		if ( m_RefreshTimes > 2 ) NeedCost = 50;
	}
	else
	{
		NeedCost = 200;
	}
	if ( NeedCost > 0 && !m_pPlayer->DecCurrency( CURRENCY_GOLD, NeedCost, GCR_QUICK_TASK ) )
		return ERR_INVALID_DATA;
	RandXiangYaoTask( IsBest > 0, true );
	++m_RefreshTimes;
	SendXiangYaoTaskInfo();
	return 0;
}

bool CMoneyRewardTask::NeedRefreshTask()
{
	for ( int32_t j = 0; j <= 3; ++j )
	{
		if ( m_XiangYaoTask[j].TaskState == 1 || m_XiangYaoTask[j].TaskState == 2 )
			return false;
	}
	return true;
}

void CMoneyRewardTask::RandXiangYaoTask( bool bBest, bool bNeedGongGao )
{
	if ( !m_pPlayer ) return;
	for ( int32_t i = 0; i <= 3; ++i )
	{
		m_XiangYaoTask[i].TaskId = CFG_DATA.RandXiangYaoTaskId( m_pPlayer->getLevel(), bBest );
		m_XiangYaoTask[i].TaskState = 1;
		if ( !bBest && bNeedGongGao )
		{
			int32_t nStart = CFG_DATA.getXiangYaoStart( m_XiangYaoTask[i].TaskId );
			if ( nStart == 4 )
			{
				NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
				if ( packet )
				{
					packet->writeInt32( 458 );
					packet->writeInt64( m_pPlayer->getCid() );
					packet->writeUTF8( m_pPlayer->getName() );
					GAME_SERVICE.worldBroadcast( packet );
				}
			}
		}
	}
	if ( bBest )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet )
		{
			packet->writeInt32( 459 );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}
}

void CMoneyRewardTask::LoginInitXiangYaoTask()
{
	if ( !IsXiangYaoFunctionOpen() ) return;
	bool bNeedInit = false;
	for ( int32_t i = 0; i <= 3; ++i )
	{
		if ( m_XiangYaoTask[i].TaskId <= 0 || m_XiangYaoTask[i].TaskState <= 0 )
		{
			bNeedInit = true;
			break;
		}
	}
	if ( bNeedInit ) InitXiangYaoTask();
}

void CMoneyRewardTask::SendXiangYaoTaskInfo()
{
	if ( !m_pPlayer || !IsXiangYaoFunctionOpen() ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_XIANG_YAO_TASK_INFO );
	if ( !packet ) return;
	packet->writeInt32( m_RefreshTimes );
	packet->writeInt32( m_XiangYaoFinishTimes );
	packet->writeInt8( 4 );
	for ( int32_t i = 0; i <= 3; ++i )
	{
		packet->writeInt8( i + 1 );
		packet->writeInt32( m_XiangYaoTask[i].TaskId );
		packet->writeInt8( m_XiangYaoTask[i].TaskState );
	}
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CMoneyRewardTask::parseXiangYaoTask( const std::string& infoString )
{
	if ( infoString.empty() ) return;
	// Parse format: "i|TaskId|TaskState:|" for up to 4 entries
	StringVector entries = Answer::StringUtility::split( infoString, "|:" );
	for ( size_t i = 0; i < entries.size(); ++i )
	{
		StringVector fields = Answer::StringUtility::split( entries[i], "|" );
		if ( fields.size() == 3 )
		{
			int32_t nIndex = atoi( fields[0].c_str() );
			if ( nIndex >= 0 && nIndex < 4 )
			{
				m_XiangYaoTask[nIndex].TaskId = atoi( fields[1].c_str() );
				m_XiangYaoTask[nIndex].TaskState = (int8_t)atoi( fields[2].c_str() );
			}
		}
	}
}

std::string CMoneyRewardTask::saveXiangYaoTaskString()
{
	std::ostringstream oss;
	for ( int32_t i = 0; i <= 3; ++i )
	{
		oss << i << "|" << m_XiangYaoTask[i].TaskId << "|" << (int32_t)m_XiangYaoTask[i].TaskState << ":|";
	}
	return oss.str();
}

bool CMoneyRewardTask::IsShenWeiFunctionOPen()
{
	if ( !m_pPlayer ) return false;
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 194 );
}

void CMoneyRewardTask::InitShenWeiTask()
{
	for ( int32_t k = 0; k <= 4; ++k )
		m_ShenWeiTaskState[k] = 2;
	if ( m_pPlayer )
		m_pPlayer->GetTask().CleanTaskType( 8 );
	SendShenWeiTaskInfo();
}

int32_t CMoneyRewardTask::OnOperatorShenWeiTask( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int8_t nIndex = inPacket->readInt8();
	int8_t nOper = inPacket->readInt8();
	const ShenWeiTaskCfg* pCfg = CFG_DATA.GetShenWeiTaskCfg( nIndex );
	if ( !pCfg ) return ERR_INVALID_DATA;
	int32_t nIdx = nIndex - 1;
	if ( nIdx < 0 || nIdx > 4 ) return ERR_INVALID_DATA;
	int32_t TaskId = pCfg->nTaskId;
	switch ( nOper )
	{
	case 1:
		// Receive
		if ( m_pPlayer->GetTask().isDoingTaskType( 8 ) ) return ERR_INVALID_DATA;
		if ( m_ShenWeiTaskState[nIdx] != 2 ) return ERR_INVALID_DATA;
		if ( m_pPlayer->GetTask().receive( TaskId, TT_TRUNK ) ) return ERR_INVALID_DATA;
		m_ShenWeiTaskState[nIdx] = 3;
		break;
	case 2:
	case 3:
	{
		if ( m_ShenWeiTaskState[nIdx] != 3 ) return ERR_INVALID_DATA;
		if ( !m_pPlayer->GetTask().isDoingTaskType( CFG_DATA.getTask(TaskId)->type ) ) return ERR_INVALID_DATA;
		int32_t nTimes = 1;
		if ( nOper == 3 )
		{
			if ( pCfg->nDoubleCost <= 0 ) return ERR_INVALID_DATA;
			nTimes = 2;
			if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nDoubleCost, GCR_QUICK_TASK ) )
				return ERR_INVALID_DATA;
		}
		if ( m_pPlayer->GetTask().submit( TaskId ) ) return ERR_INVALID_DATA;
		m_pPlayer->GetTask().CleanTaskType( 8 );
		m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 16 );
		m_ShenWeiTaskState[nIdx] = 5;
		break;
	}
	case 4:
		// Quick done
		if ( m_ShenWeiTaskState[nIdx] != 3 ) return ERR_INVALID_DATA;
		if ( m_pPlayer->GetTask().quickDone( TaskId ) ) return ERR_INVALID_DATA;
		m_pPlayer->GetTask().CleanTaskType( 8 );
		m_ShenWeiTaskState[nIdx] = 5;
		m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 16 );
		break;
	case 5:
		// Give up
		if ( m_ShenWeiTaskState[nIdx] != 3 ) return ERR_INVALID_DATA;
		if ( !m_pPlayer->GetTask().isDoingTaskType( CFG_DATA.getTask(TaskId)->type ) ) return ERR_INVALID_DATA;
		m_pPlayer->GetTask().CleanTaskType( 8 );
		m_ShenWeiTaskState[nIdx] = 2;
		break;
	default:
		return ERR_INVALID_DATA;
	}
	SendShenWeiTaskInfo();
	return 0;
}

void CMoneyRewardTask::LoginInitShenWeiTask()
{
	if ( !IsShenWeiFunctionOPen() ) return;
	bool bNeedInit = false;
	for ( int32_t i = 0; i <= 4; ++i )
	{
		if ( !m_ShenWeiTaskState[i] )
		{
			bNeedInit = true;
			break;
		}
	}
	if ( bNeedInit ) InitShenWeiTask();
}

void CMoneyRewardTask::SendShenWeiTaskInfo()
{
	if ( !m_pPlayer || !IsShenWeiFunctionOPen() ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_XIANG_YAO_TASK_INFO );
	if ( !packet ) return;
	packet->writeInt8( 5 );
	for ( int32_t i = 0; i <= 4; ++i )
	{
		packet->writeInt8( i + 1 );
		packet->writeInt8( m_ShenWeiTaskState[i] );
	}
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CMoneyRewardTask::parseShenWeiTask( const std::string& infoString )
{
	if ( infoString.empty() ) return;
	// Parse format: "i|TaskState:|" for up to 5 entries
	StringVector entries = Answer::StringUtility::split( infoString, "|:" );
	for ( size_t i = 0; i < entries.size(); ++i )
	{
		StringVector fields = Answer::StringUtility::split( entries[i], "|" );
		if ( fields.size() == 2 )
		{
			int32_t nIndex = atoi( fields[0].c_str() );
			if ( nIndex >= 0 && nIndex <= 4 )
			{
				m_ShenWeiTaskState[nIndex] = (int8_t)atoi( fields[1].c_str() );
			}
		}
	}
}

std::string CMoneyRewardTask::saveShenWeiTaskString()
{
	std::ostringstream oss;
	for ( int32_t i = 0; i <= 4; ++i )
	{
		oss << i << "|" << (int32_t)m_ShenWeiTaskState[i] << ":|";
	}
	return oss.str();
}

void CMoneyRewardTask::InitXuWuTask()
{
	if ( !m_pPlayer ) return;
	int32_t TaskId = CFG_DATA.InitXuWuTask( m_pPlayer->getLevel(), 1 );
	if ( TaskId > 0 )
	{
		m_pPlayer->GetTask().CleanTaskType( 9 );
		m_pPlayer->GetTask().receive( TaskId, TT_TRUNK );
	}
}

void CMoneyRewardTask::InitXinMoTask()
{
	if ( !m_pPlayer ) return;
	int32_t TaskId = CFG_DATA.InitXinMoTask( m_pPlayer->getLevel(), 1 );
	if ( TaskId > 0 )
	{
		m_pPlayer->GetTask().CleanTaskType( 42 );
		m_pPlayer->GetTask().receive( TaskId, TT_TRUNK );
	}
}
