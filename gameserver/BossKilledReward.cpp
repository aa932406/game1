#include "BossKilledReward.h"
#include "CfgData.h"
#include "Player.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "FunctionOpen.h"
#include "GameService.h"
#include "DataStructs.h"
#include <sstream>

using namespace Answer;

#define FT_BOSS_KILLED_REWARD		190

// ========== 清理 - 从配置初始化 ==========
void CBossKilledReward::OnCleanUp()
{
	m_BossKilledRewardMap.clear();

	const BossKilledRewardMap& cfgMap = CFG_DATA.GetBossKilledRewardMap();
	for ( BossKilledRewardMap::const_iterator it = cfgMap.begin(); it != cfgMap.end(); ++it )
	{
		BossKilledRewardInfo info;
		info.IsGetReward = 0;

		for ( std::list<int32_t>::const_iterator itBoss = it->second.BossList.begin(); itBoss != it->second.BossList.end(); ++itBoss )
		{
			BossKilledInfo stu;
			stu.BossId = *itBoss;
			stu.IsKilled = 0;
			info.BossKeilled.push_back( stu );
		}

		m_BossKilledRewardMap[it->first] = info;
	}
}

// ========== 从DB加载 ==========
void CBossKilledReward::OnLoadFromDB( const PlayerDBData& dbData )
{
	const std::string& strReward = dbData.m_BossKilledReward.RewardString;
	if ( strReward.empty() )
	{
		return;
	}

	StringVector mineString = StringUtility::split( strReward, "|" );
	for ( StringVector::iterator it = mineString.begin(); it != mineString.end(); ++it )
	{
		StringVector StringVt = StringUtility::split( *it, ":" );
		if ( StringVt.size() == 3 )
		{
			int8_t Type = (int8_t)atoi( StringVt[0].c_str() );
			int8_t IsGetReward = (int8_t)atoi( StringVt[1].c_str() );

			std::map<int8_t, BossKilledRewardInfo>::iterator itBoss = m_BossKilledRewardMap.find( Type );
			if ( itBoss != m_BossKilledRewardMap.end() )
			{
				itBoss->second.IsGetReward = IsGetReward;

				StringVector BossIdVt = StringUtility::split( StringVt[2], "," );
				for ( StringVector::iterator iter = BossIdVt.begin(); iter != BossIdVt.end(); ++iter )
				{
					int32_t BossId = atoi( iter->c_str() );
					itBoss->second.SetBossKilled( BossId );
				}
			}
		}
	}
}

// ========== 保存到DB ==========
void CBossKilledReward::OnSaveToDB( PlayerDBData& dbData )
{
	std::stringstream ss;
	for ( std::map<int8_t, BossKilledRewardInfo>::iterator it = m_BossKilledRewardMap.begin(); it != m_BossKilledRewardMap.end(); ++it )
	{
		ss << (int32_t)it->first << ":" << (int32_t)it->second.IsGetReward << ":";

		for ( std::list<BossKilledInfo>::iterator itBoss = it->second.BossKeilled.begin(); itBoss != it->second.BossKeilled.end(); ++itBoss )
		{
			if ( itBoss->IsKilled > 0 )
			{
				ss << itBoss->BossId << ",";
			}
		}

		ss << ":" << "|";
	}

	dbData.m_BossKilledReward.RewardString = ss.str();
}

// ========== 协议注册 ==========
void CBossKilledReward::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_GET_BOSS_KILLED_REWARD );
}

// ========== 协议分发 ==========
int32_t CBossKilledReward::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( nProcId == CM_GET_BOSS_KILLED_REWARD )
	{
		return OnGetBossKilledReward( inPacket );
	}

	return 0;
}

// ========== 领取奖励 ==========
int32_t CBossKilledReward::OnGetBossKilledReward( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int8_t type = (int8_t)inPacket->readInt32();

	std::map<int8_t, BossKilledRewardInfo>::iterator it = m_BossKilledRewardMap.find( type );
	if ( it == m_BossKilledRewardMap.end() )
	{
		return ERR_INVALID_DATA;
	}

	if ( !it->second.CanGetReward() )
	{
		return ERR_INVALID_DATA;
	}

	const BossKilledReward* pCfg = CFG_DATA.GetBossKilledReward( type );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddItem( pCfg->Rewars, (ITEM_ADD_REASON)IACR_GET_BOSS_KILLED_REWARD ) )
	{
		return ERR_INVALID_DATA;
	}

	it->second.IsGetReward = 1;

	SendBossKilledInfo();
	SendBossKilledIcon();

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( packet != NULL )
	{
		packet->writeInt32( 450 );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeInt8( type );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
	}

	return 0;
}

// ========== 添加Boss击杀记录 ==========
void CBossKilledReward::AddBossKilled( int32_t nBossId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	CFunctionOpen* pFuncOpen = &m_pPlayer->GetPlayerFunctionOpen();
	if ( NULL == pFuncOpen || !pFuncOpen->IsOpened( FT_BOSS_KILLED_REWARD ) )
	{
		return;
	}

	bool bUpdated = false;
	for ( std::map<int8_t, BossKilledRewardInfo>::iterator it = m_BossKilledRewardMap.begin(); it != m_BossKilledRewardMap.end(); ++it )
	{
		if ( it->second.SetBossKilled( nBossId ) )
		{
			bUpdated = true;
		}
	}

	if ( bUpdated )
	{
		SendBossKilledInfo();
		SendBossKilledIcon();
	}
}

// ========== 发送Boss击杀信息给客户端 ==========
void CBossKilledReward::SendBossKilledInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_BOSS_KILLED_REWARD_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( (int32_t)m_BossKilledRewardMap.size() );

	for ( std::map<int8_t, BossKilledRewardInfo>::iterator it = m_BossKilledRewardMap.begin(); it != m_BossKilledRewardMap.end(); ++it )
	{
		packet->writeInt8( it->first );
		packet->writeInt8( it->second.IsGetReward );

		int32_t OldWoffset = packet->getWOffset();
		int32_t Count = 0;
		packet->writeInt32( 0 );

		for ( std::list<BossKilledInfo>::iterator iter = it->second.BossKeilled.begin(); iter != it->second.BossKeilled.end(); ++iter )
		{
			if ( iter->IsKilled > 0 )
			{
				packet->writeInt32( iter->BossId );
				++Count;
			}
		}

		int32_t NewWoffset = packet->getWOffset();
		packet->setWOffset( OldWoffset );
		packet->writeInt32( Count );
		packet->setWOffset( NewWoffset );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

// ========== 获取图标状态 ==========
void CBossKilledReward::GetBossKilledIcon( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	CFunctionOpen* pFuncOpen = &m_pPlayer->GetPlayerFunctionOpen();
	if ( NULL == pFuncOpen || !pFuncOpen->IsOpened( FT_BOSS_KILLED_REWARD ) )
	{
		return;
	}

	ShowIcon icon;
	memset( &icon, 0, sizeof( icon ) );
	icon.nId = BOSS_KILLED_REWARD_ICON;
	icon.nState = AS_RUNNING;
	IconList.push_back( icon );
}

// ========== 推送图标 ==========
void CBossKilledReward::SendBossKilledIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	CFunctionOpen* pFuncOpen = &m_pPlayer->GetPlayerFunctionOpen();
	if ( NULL == pFuncOpen || !pFuncOpen->IsOpened( FT_BOSS_KILLED_REWARD ) )
	{
		return;
	}

	ShowIcon icon;
	memset( &icon, 0, sizeof( icon ) );
	icon.nId = BOSS_KILLED_REWARD_ICON;
	icon.nState = AS_RUNNING;
	m_pPlayer->SendIconState( &icon );
}

// ========== 是否所有奖励都已领取 ==========
bool CBossKilledReward::IsAllRewardGet()
{
	for ( std::map<int8_t, BossKilledRewardInfo>::iterator it = m_BossKilledRewardMap.begin(); it != m_BossKilledRewardMap.end(); ++it )
	{
		if ( it->second.IsGetReward <= 0 )
		{
			return false;
		}
	}
	return true;
}

// ========== 可领取奖励数量 ==========
int32_t CBossKilledReward::CanGetRewardCount()
{
	int32_t Count = 0;
	for ( std::map<int8_t, BossKilledRewardInfo>::iterator it = m_BossKilledRewardMap.begin(); it != m_BossKilledRewardMap.end(); ++it )
	{
		if ( it->second.CanGetReward() )
		{
			++Count;
		}
	}
	return Count;
}
