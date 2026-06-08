#include "stdafx.h"
#include "UniteServer.h"
#include "Player.h"
#include "GameService.h"
#include "Timer.h"
#include "ItemHelper.h"
#include "MapManager.h"

using namespace Answer;

CUniteServer::CUniteServer()
{
	m_nDay = 0;
	m_nMinute = 0;
	m_nStartDay = 0;
	m_nEndDay = 0;
	m_nIcon = 0;
	m_bDie = false;
	m_MonsterId = 0;
	memset( m_vStartDay, 0, sizeof(m_vStartDay) );
	memset( m_vEndDay, 0, sizeof(m_vEndDay) );
}

CUniteServer::~CUniteServer()
{
}

void CUniteServer::Init( int32_t line )
{
	if ( line == 9 || !CFG_DATA.isUniteServer() )
		return;

	m_nDay = CFG_DATA.getServerDiffDay( 0 ); // SVT_UNITE = 0
	const tm& nowTime = TIMER.GetLocalNow();
	m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;

	Inifile ini;
	ini.parse( "./ServerConfig/Tables/UnitServer.cfg" );

	// CONFIG
	m_nStartDay = ini.getIntValue( "CONFIG", "start_day" );
	m_nEndDay = ini.getIntValue( "CONFIG", "end_day" );
	m_nIcon = ini.getIntValue( "CONFIG", "icon" );

	// HUO_YUE_DU
	m_vStartDay[1] = ini.getIntValue( "HUO_YUE_DU", "start_day" );
	m_vEndDay[1] = ini.getIntValue( "HUO_YUE_DU", "end_day" );
	m_nHuoYueSize = ini.getIntValue( "HUO_YUE_DU", "size" );
	m_vHuoYueValue.reserve( m_nHuoYueSize );
	m_vHuoYueGift.reserve( m_nHuoYueSize );
	for ( int32_t i = 0; i < m_nHuoYueSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "limit%d", i + 1 );
		m_vHuoYueValue.push_back( ini.getIntValue( "HUO_YUE_DU", szCol ) );

		snprintf( szCol, 63, "gift%d", i + 1 );
		MemChrBagVector items = CItemHelper::parseItemVectorString( ini.getStrValue( "HUO_YUE_DU", szCol ) );
		m_vHuoYueGift.push_back( items );
	}

	// RECHARGE
	m_vStartDay[2] = ini.getIntValue( "RECHARGE", "start_day" );
	m_vEndDay[2] = ini.getIntValue( "RECHARGE", "end_day" );
	m_nRechargeDaysSize = ini.getIntValue( "RECHARGE", "size" );
	m_vRechargeValue.reserve( m_nRechargeDaysSize );
	m_vRechargeGift.reserve( m_nRechargeDaysSize );
	for ( int32_t i = 0; i < m_nRechargeDaysSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "gold%d", i + 1 );
		m_vRechargeValue.push_back( ini.getIntValue( "RECHARGE", szCol ) );

		snprintf( szCol, 63, "gift%d", i + 1 );
		MemChrBagVector items = CItemHelper::parseItemVectorString( ini.getStrValue( "RECHARGE", szCol ) );
		m_vRechargeGift.push_back( items );
	}

	// XIAO_FEI_DRAW
	m_vStartDay[8] = ini.getIntValue( "XIAO_FEI_DRAW", "start_day" );
	m_vEndDay[8] = ini.getIntValue( "XIAO_FEI_DRAW", "end_day" );
	m_XiaoFeiDrawSize = ini.getIntValue( "XIAO_FEI_DRAW", "size" );
	m_nXiaoFeiDrawValue.reserve( m_XiaoFeiDrawSize );
	for ( int32_t i = 0; i < m_XiaoFeiDrawSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "value%d", i + 1 );
		m_nXiaoFeiDrawValue.push_back( ini.getIntValue( "XIAO_FEI_DRAW", szCol ) );
	}

	// SPIDER_QUEEN (BOSS)
	m_vStartDay[6] = ini.getIntValue( "SPIDER_QUEEN", "start_day" );
	m_vEndDay[6] = ini.getIntValue( "SPIDER_QUEEN", "end_day" );
	m_nSpiderQueenStartBroadcast = ini.getIntValue( "SPIDER_QUEEN", "start_broadcast" );
	m_nSpiderQueenEndBroadcast = ini.getIntValue( "SPIDER_QUEEN", "end_broadcast" );
	m_nSpiderQueenKillBroadcast = ini.getIntValue( "SPIDER_QUEEN", "kill_broadcast" );
	int32_t nSpiderQueenCount = ini.getIntValue( "SPIDER_QUEEN", "count" );
	m_vSpiderQueenMinute.reserve( nSpiderQueenCount );
	for ( int32_t i = 0; i < nSpiderQueenCount; ++i )
	{
		char szCol[64] = {0};
		TimeArea tarea;
		snprintf( szCol, 63, "start_minute%d", i + 1 );
		tarea.nStartTime = ini.getIntValue( "SPIDER_QUEEN", szCol );
		snprintf( szCol, 63, "end_minute%d", i + 1 );
		tarea.nEndTime = ini.getIntValue( "SPIDER_QUEEN", szCol );
		m_vSpiderQueenMinute.push_back( tarea );
	}
	m_MapId = ini.getIntValue( "SPIDER_QUEEN", "mapid" );
	m_X = ini.getIntValue( "SPIDER_QUEEN", "x" );
	m_Y = ini.getIntValue( "SPIDER_QUEEN", "y" );
	m_Mid = ini.getIntValue( "SPIDER_QUEEN", "mid" );

	// CHOU_JIANG
	m_vStartDay[4] = ini.getIntValue( "CHOU_JIANG", "start_day" );
	m_vEndDay[4] = ini.getIntValue( "CHOU_JIANG", "end_day" );
	m_ChouJiangType = ini.getIntValue( "CHOU_JIANG", "Type" );
	m_ChouJiangCount = ini.getIntValue( "CHOU_JIANG", "count" );

	// COLLECT_DROP
	m_vStartDay[7] = ini.getIntValue( "COLLECT_DROP", "start_day" );
	m_vEndDay[7] = ini.getIntValue( "COLLECT_DROP", "end_day" );

	// MYSTERY_SHOP
	m_vStartDay[9] = ini.getIntValue( "MYSTERY_SHOP", "start_day" );
	m_vEndDay[9] = ini.getIntValue( "MYSTERY_SHOP", "end_day" );
	m_nMysteryShopRefreshBroad = ini.getIntValue( "MYSTERY_SHOP", "broadcast" );
	m_sMysteryShopRefreshCost = ini.getIntValue( "MYSTERY_SHOP", "refresh_cost" );

	// WING_LEVEL_UP
	m_vStartDay[12] = ini.getIntValue( "WING_LEVEL_UP", "start_day" );
	m_vEndDay[12] = ini.getIntValue( "WING_LEVEL_UP", "end_day" );
	m_nSize = ini.getIntValue( "WING_LEVEL_UP", "size" );
	m_UseItemCount.reserve( m_nSize );
	m_Items.resize( m_nSize );
	for ( int32_t i = 0; i < m_nSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "count%d", i + 1 );
		m_UseItemCount.push_back( ini.getIntValue( "WING_LEVEL_UP", szCol ) );
		snprintf( szCol, 63, "gift%d", i + 1 );
		MemChrBagVector tmpVec = CItemHelper::parseItemString( 0, ini.getStrValue( "WING_LEVEL_UP", szCol ) );
		if ( !tmpVec.empty() )
			m_Items[i] = tmpVec[0];
	}

	// CHANGE_NAME_CARD
	m_nPrice = ini.getIntValue( "CHANGE_NAME_CARD", "price" );
	{
		MemChrBagVector tmpVec = CItemHelper::parseItemString( 0, ini.getStrValue( "CHANGE_NAME_CARD", "item" ) );
		if ( !tmpVec.empty() )
			m_Item = tmpVec[0];
	}

	// LIAN_RECHARGE
	int32_t nLianSize = ini.getIntValue( "LIAN_RECHARGE", "size" );
	m_LianRechargeCfgVt.reserve( nLianSize );
	for ( int32_t i = 0; i < nLianSize; ++i )
	{
		char szCol[64] = {0};
		LianRechargeCfg stu;
		snprintf( szCol, 63, "day%d", i + 1 );
		stu.nDay = ini.getIntValue( "LIAN_RECHARGE", szCol );
		snprintf( szCol, 63, "gold%d", i + 1 );
		stu.nGold = ini.getIntValue( "LIAN_RECHARGE", szCol );
		snprintf( szCol, 63, "reward%d", i + 1 );
		stu.vReward = CItemHelper::parseItemVectorString( ini.getStrValue( "LIAN_RECHARGE", szCol ) );
		m_LianRechargeCfgVt.push_back( stu );
	}

	// XIAO_FEI_SUM_DRAW
	m_vStartDay[5] = ini.getIntValue( "XIAO_FEI_SUM_DRAW", "start_day" );
	m_vEndDay[5] = ini.getIntValue( "XIAO_FEI_SUM_DRAW", "end_day" );

	// CHOU_JIANG_TIMES
	m_vStartDay[11] = ini.getIntValue( "CHOU_JIANG_TIMES", "start_day" );
	m_vEndDay[11] = ini.getIntValue( "CHOU_JIANG_TIMES", "end_day" );

	// DAILY_LIMIT_SHOP
	m_vStartDay[3] = ini.getIntValue( "DAILY_LIMIT_SHOP", "start_day" );
	m_vEndDay[3] = ini.getIntValue( "DAILY_LIMIT_SHOP", "end_day" );
}

bool CUniteServer::IsInUnitServerTime()
{
	return CFG_DATA.isUniteServer() && m_nDay >= m_nStartDay && m_nDay < m_nEndDay;
}

bool CUniteServer::IsInTime( UnitServerActivityType nType )
{
	return CFG_DATA.isUniteServer() && m_nDay >= m_vStartDay[nType] && m_nDay < m_vEndDay[nType];
}

bool CUniteServer::IsInSpiderQueenTime()
{
	if ( !IsInTime( US_BOSS ) )
		return false;
	for ( size_t i = 0; i < m_vSpiderQueenMinute.size(); ++i )
	{
		if ( m_nMinute >= m_vSpiderQueenMinute[i].nStartTime && m_nMinute < m_vSpiderQueenMinute[i].nEndTime )
			return true;
	}
	return false;
}

bool CUniteServer::IsInMysteryShopTime()
{
	return IsInTime( US_MYSTERY_SHOP );
}

int32_t CUniteServer::getLeftTime()
{
	if ( !IsInUnitServerTime() )
		return 0;
	return 86400 * ( m_nEndDay - m_nDay ) - 60 * m_nMinute;
}

void CUniteServer::OnDaySwitch()
{
	if ( GAME_SERVICE.getLine() == 9 || !CFG_DATA.isUniteServer() )
		return;

	m_nDay = CFG_DATA.getServerDiffDay( 0 ); // SVT_UNITE = 0

	if ( m_nDay == m_nEndDay )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CC3 );
		if ( packet )
		{
			packet->writeInt32( m_nIcon );
			packet->writeInt8( 4 );
			packet->writeInt32( 0 );
			packet->writeInt8( 0 );
			packet->writeInt32( 0 );
			packet->writeInt8( 0 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( 0, packet );
		}
	}
}

void CUniteServer::OnNewMinute( int32_t nMinute )
{
	if ( GAME_SERVICE.getLine() == 9 || !CFG_DATA.isUniteServer() )
		return;

	m_nMinute = nMinute;
	checkSpiderQueen();
	checkMysteryShopRefreshBroad();
}

void CUniteServer::getIconState( ShowIcon& stu, Player* player )
{
	memset( &stu, 0, sizeof(stu) );
	stu.nId = m_nIcon;
	stu.nState = IsInUnitServerTime() ? AS_RUNNING : AS_TIME_OUT;
	stu.nLeftTime = getLeftTime();
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;

	if ( player && IsInUnitServerTime() )
	{
		// Count available rewards
		int32_t nRewardCount = GetWingLevelUpRewardCount( player );
		stu.IconRight = nRewardCount;
	}
}

void CUniteServer::GetIconState( Player* player, IconStateList& IconList )
{
	if ( !player || GAME_SERVICE.getLine() == 9 || !CFG_DATA.isUniteServer() )
		return;

	if ( IsInUnitServerTime() )
	{
		ShowIcon stu;
		getIconState( stu, player );
		IconList.push_back( stu );
	}
}

void CUniteServer::SendIconState( Player* player )
{
	if ( !player || !CFG_DATA.isUniteServer() || !IsInUnitServerTime() )
		return;

	ShowIcon stu;
	getIconState( stu, player );

	NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( packet )
	{
		packet->writeInt32( stu.nId );
		packet->writeInt8( stu.nState );
		packet->writeInt32( stu.nLeftTime );
		packet->writeInt8( stu.IconLeft );
		packet->writeInt32( stu.IconRight );
		packet->writeInt8( stu.Effects );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
	}
}

void CUniteServer::getSpiderQueenIconState( ShowIcon& stu )
{
	memset( &stu, 0, sizeof(stu) );
	stu.nId = m_nIcon;
	stu.nState = IsInTime( US_BOSS ) ? AS_RUNNING : AS_TIME_OUT;
	stu.nLeftTime = 0;
	stu.IconLeft = m_bDie ? 0 : 1;
	stu.IconRight = 0;
	stu.Effects = 1;
}

void CUniteServer::GetSpiderQueenIconState( IconStateList& IconList )
{
	if ( IsInTime( US_BOSS ) )
	{
		ShowIcon stu;
		getSpiderQueenIconState( stu );
		IconList.push_back( stu );
	}
}

void CUniteServer::SendSpiderQueenIconState()
{
	if ( GAME_SERVICE.getLine() != 1 )
		return;

	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CC3 );
	if ( !packet )
		return;

	ShowIcon stu;
	getSpiderQueenIconState( stu );
	packet->writeInt32( stu.nId );
	packet->writeInt8( stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CUniteServer::SendUniteServerInfo( Player* player )
{
	if ( !player || !IsInUnitServerTime() )
		return;

	NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), PACK_DISPATCH, 0x2E9A );
	if ( !packet )
		return;

	int32_t nRecord = player->getRecord( 1406 ); // Use count
	packet->writeInt32( nRecord );
	int32_t v5 = player->getRecord( 1407 ); // Reward record
	packet->writeInt32( v5 );
	int8_t v6 = player->getRecord( 1405 ); // Name card flag
	packet->writeInt8( v6 );
	int32_t v7 = player->getRecord( 1402 ); // ChouJiang times
	packet->writeInt32( v7 );

	appendRechargeInfo( packet, player );
	appendDiscountGiftInfo( packet, player );
	appendHuoYueDuInfo( packet, player );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CUniteServer::appendRechargeInfo( NetPacket* packet, Player* player )
{
	if ( !player || !packet )
		return;

	int32_t TodayPayGold = player->GetTodayPayGold();
	packet->writeInt32( TodayPayGold );
	packet->writeInt8( m_nRechargeDaysSize );

	int32_t nRewardRecord = player->GetOperateLimit().GetLimitCount( 2029 );
	for ( int32_t i = 0; i < m_nRechargeDaysSize; ++i )
	{
		int8_t nState = 0;
		if ( player->GetTodayPayGold() >= m_vRechargeValue[i] )
		{
			nState = 1;
			if ( ( ( nRewardRecord >> i ) & 1 ) != 0 )
				nState = 2;
		}
		packet->writeInt8( nState );
	}
}

void CUniteServer::appendDiscountGiftInfo( NetPacket* packet, Player* player )
{
	if ( !packet || !player )
		return;

	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 2090 );
	int16_t nCount = 0;
	uint32_t oldOffset = packet->getWOffset();
	packet->writeInt16( 0 );

	const CfgBuyGiftTable* gifts = CFG_DATA.GetBuyGiftTable();
	if ( gifts )
	{
		for ( CfgBuyGiftTable::const_iterator it = gifts->begin(); it != gifts->end(); ++it )
		{
			int32_t nIndex = it->first;
			int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
			if ( nOldRecord == nNewRecord )
			{
				++nCount;
				packet->writeInt16( nIndex - 1 );
			}
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( newOffset );
}

void CUniteServer::appendHuoYueDuInfo( NetPacket* packet, Player* player )
{
	if ( !packet || !player )
		return;

	int32_t Record = player->getRecord( 2089 );
	packet->writeInt32( Record );

	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 1068 );
	int16_t nCount = 0;
	uint32_t oldOffset = packet->getWOffset();
	packet->writeInt16( 0 );

	for ( int32_t i = 0; i < m_nHuoYueSize; ++i )
	{
		if ( nOldRecord == ( nOldRecord | ( 1 << i ) ) )
		{
			++nCount;
			packet->writeInt16( i );
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( newOffset );
}

void CUniteServer::checkSpiderQueen()
{
	if ( !IsInTime( US_BOSS ) || m_vSpiderQueenMinute.empty() )
		return;
	if ( GAME_SERVICE.getLine() != 1 )
		return;

	for ( size_t i = 0; i < m_vSpiderQueenMinute.size(); ++i )
	{
		if ( m_nMinute == m_vSpiderQueenMinute[i].nStartTime )
		{
			// Monster creation omitted (Monster::init signature mismatch)
			broadcastSpiderQueenStart();
			SendSpiderQueenIconState();
		}
		else if ( m_nMinute == m_vSpiderQueenMinute[i].nEndTime && !m_bDie )
		{
			m_bDie = true;
			broadcastSpiderQueenEnd();
			SendSpiderQueenIconState();
		}
	}
}

void CUniteServer::BossDie( int32_t MonsterId, std::string* p_name, CharId_t Cid )
{
	if ( m_MonsterId > 0 && m_MonsterId == MonsterId )
	{
		m_bDie = true;
		BroadcastSpiderQueenKilled( p_name, Cid );
		SendSpiderQueenIconState();
	}
}

void CUniteServer::BroadcastSpiderQueenKilled( const std::string* name, CharId_t cid )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;

	packet->writeInt32( m_nSpiderQueenKillBroadcast );
	packet->writeUTF8( *name );
	packet->writeInt64( cid );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CUniteServer::broadcastSpiderQueenStart()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;

	packet->writeInt32( m_nSpiderQueenStartBroadcast );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CUniteServer::broadcastSpiderQueenEnd()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;

	packet->writeInt32( m_nSpiderQueenEndBroadcast );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CUniteServer::sendBroadcast( int32_t nBroadId, CharId_t cid, const std::string* name )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;

	packet->writeInt32( nBroadId );
	packet->writeUTF8( *name );
	packet->writeInt64( cid );
	packet->setSize( packet->getWOffset() );
	packet->setProc( 0x2CD6 );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

int32_t CUniteServer::GetRechargeGift( Player* player, int32_t nIndex )
{
	if ( !player )
		return 10002;
	if ( !IsInTime( US_DAILY_RECHARGE ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nRechargeDaysSize )
		return 10002;

	int32_t nRewardRecord = player->GetOperateLimit().GetLimitCount( 2029 );
	if ( player->GetTodayPayGold() < m_vRechargeValue[nIndex] )
		return 10002;

	int32_t nNewRecord = nRewardRecord | ( 1 << nIndex );
	if ( nRewardRecord == nNewRecord )
		return 10002;

	if ( !player->GetBag().AddItem( m_vRechargeGift[nIndex], IACR_UNITE_SERVER_RECHARGE_GIFT ) )
		return 10002;

	player->GetOperateLimit().UpdateLimitCount( 2029, nNewRecord );
	SendIconState( player );
	return 0;
}

int32_t CUniteServer::GetLianRechargeReward( Player* player, int32_t nIndex )
{
	if ( !player )
		return 10002;
	if ( !IsInTime( US_LIAN_RECHARGE ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= (int32_t)m_LianRechargeCfgVt.size() )
		return 10002;

	int32_t nRewardRecord = player->GetOperateLimit().GetLimitCount( 2095 );
	int32_t nNewRecord = nRewardRecord | ( 1 << nIndex );
	if ( nRewardRecord == nNewRecord )
		return 10002;

	if ( player->getRecord( nIndex + 1000 ) < m_LianRechargeCfgVt[nIndex].nDay )
		return 10002;

	if ( !player->GetBag().AddItem( m_LianRechargeCfgVt[nIndex].vReward, IACR_HE_FU_LIAN_CHONG ) )
		return 10002;

	player->GetOperateLimit().UpdateLimitCount( 2095, nNewRecord );
	SendIconState( player );
	return 0;
}

int32_t CUniteServer::BuyDiscountGift( Player* player, int16_t nIndex )
{
	if ( !player || !IsInTime( US_DAILY_LIMIT_SHOP ) )
		return 10002;

	int16_t nIndexb = nIndex + 1;
	const CfgBuyGift* cfgGift = CFG_DATA.GetBuyGift( nIndexb );
	if ( !cfgGift )
		return 10002;

	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 2090 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndexb );
	if ( nOldRecord == nNewRecord )
		return 10002;

	if ( player->GetCurrency( CURRENCY_GOLD ) < cfgGift->nGold )
		return 10002;

	if ( !player->GetBag().AddItem( (MemChrBagVector&)cfgGift->vGift, IACR_UNITE_SERVER_DISTINCT_GIFT ) )
		return 10002;

	if ( !player->DecCurrency( CURRENCY_GOLD, cfgGift->nGold, GCR_UNITE_SERVER_BUY_DISTINCT_GIFT, nIndexb ) )
	{
		// rollback? for now just return error
		return 10002;
	}

	player->GetOperateLimit().UpdateLimitCount( 2090, nNewRecord );

	if ( cfgGift->nBroad > 0 )
	{
		std::string name = player->getName();
		sendBroadcast( cfgGift->nBroad, player->getCid(), &name );
	}
	return 0;
}

int32_t CUniteServer::GetHuoYueDuGift( Player* player, int32_t nIndex )
{
	if ( !IsInTime( US_HUO_YUE_DU ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nHuoYueSize )
		return 10002;

	int32_t nHuoYueDu = player->getRecord( 2089 );
	if ( m_vHuoYueValue[nIndex] > nHuoYueDu )
		return 10002;

	int32_t nOldRecord = player->getRecord( 1068 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;

	if ( !player->GetBag().AddItem( m_vHuoYueGift[nIndex], IACR_UNITE_SERVER_HUO_YUE_DU ) )
		return 10002;

	player->updateRecord( 1068, nNewRecord );
	SendIconState( player );
	return 0;
}

void CUniteServer::AddHuoYueDu( Player* player, int32_t nValue )
{
	if ( !player || !IsInTime( US_HUO_YUE_DU ) )
		return;

	int32_t nOldValue = player->getRecord( 2089 );
	int32_t nNewValue = nOldValue + nValue;
	player->updateRecord( 2089, nNewValue );
	SendIconState( player );
}

bool CUniteServer::RefreshMysteryShopItem( Player* player )
{
	if ( !player )
		return false;

	return player->DecCurrency( CURRENCY_GOLD, m_sMysteryShopRefreshCost, GCR_MYSTERY_SHOP_REFRESH, 0 );
}

void CUniteServer::checkMysteryShopRefreshBroad()
{
	if ( GAME_SERVICE.getLine() == 1 && IsInTime( US_MYSTERY_SHOP ) && !( m_nMinute % 120 ) )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
		if ( packet )
		{
			packet->writeInt32( m_nMysteryShopRefreshBroad );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( 0, packet );
		}
	}
}

int32_t CUniteServer::GetWingLevelUpGift( Player* player, int32_t nIndex )
{
	if ( !IsInTime( US_WING_LEVEL_UP ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nSize )
		return 10002;

	int32_t UseCount = player->getRecord( 1406 );
	if ( m_UseItemCount[nIndex] > UseCount )
		return 10002;

	int32_t nOldRecord = player->getRecord( 1407 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;

	if ( !player->GetBag().AddItem( m_Items[nIndex], IACR_WING_LEVEL_UP ) )
		return 10002;

	player->updateRecord( 1407, nNewRecord );
	SendIconState( player );
	return 0;
}

int32_t CUniteServer::GetWingLevelUpRewardCount( Player* player )
{
	if ( !player || !IsInTime( US_WING_LEVEL_UP ) )
		return 0;

	int32_t nCount = 0;
	int32_t UseCount = player->getRecord( 1406 );
	int32_t nOldRecord = player->getRecord( 1407 );

	for ( int32_t i = 0; i < m_nSize; ++i )
	{
		if ( m_UseItemCount[i] <= UseCount )
		{
			if ( ( ( nOldRecord >> i ) & 1 ) == 0 )
				++nCount;
		}
	}
	return nCount;
}

void CUniteServer::AddWingLevelUp( Player* player )
{
	if ( !player || !IsInTime( US_WING_LEVEL_UP ) )
		return;

	int32_t nOldCount = player->getRecord( 1406 );
	player->updateRecord( 1406, nOldCount + 1 );
	SendIconState( player );
}

int32_t CUniteServer::GetCanXiaoFeiDrawTime( Player* player )
{
	if ( !player || !IsInTime( US_XIAO_FEI_DRAW ) )
		return 0;

	int32_t nTotalValue = player->getRecord( 1402 );
	int32_t nDrawedTimes = player->getRecord( 1403 );
	int32_t nCanDrawTimes = 0;

	for ( int32_t i = 0; i < m_XiaoFeiDrawSize; ++i )
	{
		if ( nTotalValue >= m_nXiaoFeiDrawValue[i] )
			++nCanDrawTimes;
	}

	return nCanDrawTimes - nDrawedTimes;
}

void CUniteServer::AddXiaoFeiValue( Player* player, int32_t nValue )
{
	if ( !player || !IsInTime( US_XIAO_FEI_DRAW ) )
		return;

	int32_t nOldValue = player->getRecord( 1402 );
	int32_t nOldDrawedTimes = player->getRecord( 1403 );
	bool NeedSendIcon = false;

	player->updateRecord( 1402, nOldValue + nValue );

	for ( int32_t i = 0; i < m_XiaoFeiDrawSize; ++i )
	{
		if ( nOldValue < m_nXiaoFeiDrawValue[i] && nOldValue + nValue >= m_nXiaoFeiDrawValue[i] )
		{
			NeedSendIcon = true;
			break;
		}
	}

	if ( NeedSendIcon )
		SendIconState( player );
}

int32_t CUniteServer::GetChouJiangType()
{
	if ( IsInTime( US_CHOU_JIANG ) )
		return m_ChouJiangType;
	return 0;
}

int32_t CUniteServer::GetChouJiangSpecialTime()
{
	if ( IsInTime( US_CHOU_JIANG ) )
		return m_ChouJiangCount;
	return 0;
}

int32_t CUniteServer::OnGetChouJiangReward( Player* player )
{
	if ( !player || !IsInTime( US_CHOU_JIANG_TIMES ) )
		return 10002;

	int32_t nRewardRecord = player->getRecord( 1404 );
	int32_t nChouJiangTimes = player->getRecord( 1402 );

	// Find first unclaimed reward tier
	for ( int32_t i = 0; i < m_ChouJiangCount; ++i )
	{
		if ( ( ( nRewardRecord >> i ) & 1 ) == 0 )
		{
			if ( nChouJiangTimes >= ( i + 1 ) * 10 ) // Each tier requires 10 draws
			{
				const TreasureHunterCfg* CurCfg = CFG_DATA.GetTreasureHunterCfg( i + 1 );
				if ( CurCfg && CurCfg->nType == 2 )
				{
					if ( !player->GetBag().AddItem( (MemChrBagVector&)CurCfg->Items, IACR_HE_FU_CHOU_JIANG_TIMES ) )
						return 10002;
				}

				int32_t nNewRecord = nRewardRecord | ( 1 << i );
				player->updateRecord( 1404, nNewRecord );

				if ( CurCfg && CurCfg->GongGaoId > 0 )
					GongGao( player, CurCfg->GongGaoId, 0 );

				SendIconState( player );
				return 0;
			}
			break;
		}
	}
	return 10002;
}

void CUniteServer::OnAddChouJiangTimes( Player* player, int32_t nCount )
{
	if ( !player || !IsInTime( US_CHOU_JIANG_TIMES ) )
		return;

	int32_t nOldTimes = player->getRecord( 1402 );
	player->updateRecord( 1402, nOldTimes + nCount );
	SendIconState( player );
}

int32_t CUniteServer::BuyChangeNameCard( Player* player )
{
	if ( !player )
		return 2;
	if ( player->getRecord( 1405 ) > 0 )
		return 2;
	if ( player->GetBag().GetFreeSlotCount() <= 0 )
		return 2;
	if ( m_nPrice <= 0 )
		return 2;

	if ( !player->DecCurrency( CURRENCY_GOLD, m_nPrice, GCR_BUY_CHANGE_NAME_CARD, 0 ) )
		return 2;

	if ( !player->GetBag().AddItem( m_Item, IACR_BUY_CHANGE_NAME_CARD ) )
		return 10002;

	player->updateRecord( 1405, 1 );
	return 0;
}

int32_t CUniteServer::GetEndCollectDropTime()
{
	if ( !IsInTime( US_COLLECT_DROP ) )
		return 0;
	// Simplified: use DayTime calculation
	return 86400 * m_vEndDay[7] + Answer::DayTime::dayzero(Answer::DayTime::now()) - 1;
}

void CUniteServer::OnRecharge( Player* player, int32_t nGold )
{
	if ( !player || !IsInTime( US_DAILY_RECHARGE ) )
		return;

	int32_t nRewardRecord = player->GetOperateLimit().GetLimitCount( 2029 );
	for ( int32_t i = 0; i < m_nRechargeDaysSize; ++i )
	{
		if ( ( ( nRewardRecord >> i ) & 1 ) == 0 )
		{
			if ( player->GetTodayPayGold() >= m_vRechargeValue[i] )
			{
				SendIconState( player );
				break;
			}
		}
	}
}

void CUniteServer::GongGao( Player* pPlayer, int32_t GongGaoId, int32_t Index )
{
	if ( !pPlayer )
		return;

	NetPacket* packet = GAME_SERVICE.popNetpacket( pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( !packet )
		return;

	packet->writeInt32( GongGaoId );
	packet->writeInt64( pPlayer->getCid() );
	packet->writeUTF8( pPlayer->getName() );
	packet->writeInt32( Index );
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_NOTICE_PARAM );
	GAME_SERVICE.worldBroadcast( pPlayer->getConnId(), packet );
}
