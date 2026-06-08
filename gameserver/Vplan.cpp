#include "Vplan.h"
#include "Player.h"
#include "CfgData.h"
#include "GameService.h"
#include "PDUDefine.h"
#include "Bag.h"
#include "Currency.h"
#include "DataStructs.h"
#include "OperateLimit.h"
#include "FunctionOpen.h"

using namespace Answer;

CVplan::CVplan()
{
	m_pPlayer = NULL;
	OnCleanUp();
}

CVplan::~CVplan()
{
}

void CVplan::OnCleanUp()
{
	m_VplanType = 0;
	m_VplanLevel = 0;
	m_nSwVipLevel = 0;
	m_bSwVipBar = 0;
	m_YyLevel = 0;
	m_YyVipLevel = 0;
	m_YySuperLevel = 0;
	m_fromLYGameApp = 0;
	m_SgHallLevel = 0;
	m_strSGPf.clear();
	m_XlNxLevel = 0;
	m_PlatformVip = 0;
	m_PlatformSuperVip = 0;
}

void CVplan::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_VplanType = dbData.m_VplanData.m_VplanType;
	m_VplanLevel = dbData.m_VplanData.m_VplanLevel;
	m_nSwVipLevel = dbData.m_VplanData.m_SwVipLevel;
	m_YyLevel = dbData.m_VplanData.m_YYLevel;
	m_YyVipLevel = dbData.m_VplanData.m_YYVipLevel;
	m_YySuperLevel = dbData.m_VplanData.m_YySuperLevel;
	m_fromLYGameApp = dbData.m_VplanData.m_fromLYGameApp;
	m_SgHallLevel = dbData.m_VplanData.m_SgHallLevel;
	m_strSGPf = dbData.m_VplanData.m_strSGPf;
	m_XlNxLevel = dbData.m_VplanData.m_XlNxLevel;
	m_PlatformVip = dbData.m_VplanData.m_PlatformVip;
	m_PlatformSuperVip = dbData.m_VplanData.m_PlatformSuperVip;
}

void CVplan::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_VplanData.m_VplanType = m_VplanType;
	dbData.m_VplanData.m_VplanLevel = m_VplanLevel;
	dbData.m_VplanData.m_SwVipLevel = m_nSwVipLevel;
	dbData.m_VplanData.m_YYLevel = m_YyLevel;
	dbData.m_VplanData.m_YYVipLevel = m_YyVipLevel;
	dbData.m_VplanData.m_YySuperLevel = m_YySuperLevel;
	dbData.m_VplanData.m_fromLYGameApp = m_fromLYGameApp;
	dbData.m_VplanData.m_SgHallLevel = m_SgHallLevel;
	dbData.m_VplanData.m_strSGPf = m_strSGPf;
	dbData.m_VplanData.m_XlNxLevel = m_XlNxLevel;
	dbData.m_VplanData.m_PlatformVip = m_PlatformVip;
	dbData.m_VplanData.m_PlatformSuperVip = m_PlatformSuperVip;
}

void CVplan::OnDaySwitch( int32_t nDiffDays )
{
	if ( m_pPlayer )
	{
		// Platform-specific day switch logic
		SendVplanInfo();
		SendVplanIcon();
	}
}

void CVplan::OnWeekSwitch( int32_t nDiffWeeks )
{
}

void CVplan::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_VPLAN_INFO );
	procList.push_back( CM_GET_VPLAN_GIFT );
	procList.push_back( CM_GET_YY_LEVEL_REWARD );
	procList.push_back( CM_ASK_YY_INFO );
	procList.push_back( CM_LOGIN_FROM_YY_GAME_APP );
	procList.push_back( CM_GET_SW_VIP_REWARD );
	procList.push_back( CM_ASK_SW_VIP_INFO );
	procList.push_back( CM_GET_YY_VIP_GIFT );
	procList.push_back( CM_ASK_YY_VIP_INFO );
	procList.push_back( CM_GET_SW_VIP_BAR_REWARD );
	procList.push_back( CM_ASK_SG_GAME_APP_INFO );
	procList.push_back( CM_GET_SG_GAME_APP );
	procList.push_back( CM_GET_XUN_LEI_REWARD );
	procList.push_back( CM_ASK_XUN_LEI_INFO );
	procList.push_back( CM_ASK_LU_DA_SHI_INFO );
	procList.push_back( CM_GET_LU_DA_SHI_GIFT );
}

int32_t CVplan::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( !inPacket ) return ERR_INVALID_DATA;
	switch ( nProcId )
	{
	case CM_ASK_VPLAN_INFO:         SendVplanInfo(); break;
	case CM_GET_VPLAN_GIFT:          return OnGetReward( inPacket );
	case CM_ASK_YY_VIP_INFO:          return OnGetSWVipReward( inPacket );
	case CM_GET_YY_VIP_GIFT:          SendSwVipReward(); break;
	case CM_GET_YY_LEVEL_REWARD:      return OnGetYYLevelReward( inPacket );
	case CM_ASK_YY_INFO:              SendYYInfo(); break;
	case CM_LOGIN_FROM_YY_GAME_APP:   return OnGetYYVipGift( inPacket );
	case CM_GET_SW_VIP_REWARD:        SendYYVipInfo(); break;
	case CM_ASK_SW_VIP_INFO:          return OnLoginFromYYgameApp( inPacket );
	case CM_GET_SW_VIP_BAR_REWARD:    return OnGetSWVipBarReward( inPacket );
	case CM_ASK_SG_GAME_APP_INFO:     SendSgGameAppInfo(); break;
	case CM_GET_SG_GAME_APP:          return OnGetSgGameApp( inPacket );
	case CM_GET_XUN_LEI_REWARD:       return OnGetXunLeiReward( inPacket );
	case CM_ASK_XUN_LEI_INFO:         SendXunLieInfo(); break;
	case CM_ASK_LU_DA_SHI_INFO:       SendLuDaShiVipInfo(); break;
	case CM_GET_LU_DA_SHI_GIFT:       return OnGetLuDaShiVipGift( inPacket );
	default: return ERR_INVALID_DATA;
	}
	return 0;
}

void CVplan::AddAttr()
{
	if ( !m_pPlayer ) return;
	// Apply Vplan attribute bonuses based on platform VIP levels
}

int32_t CVplan::GetExpRatio()
{
	int32_t nRatio = 0;
	if ( m_bSwVipBar ) nRatio += 50; // SwBar exp bonus
	return nRatio;
}

void CVplan::SendVplanInfo()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_VPLAN_INFO );
	if ( packet )
	{
		packet->writeInt32( m_VplanLevel );
		packet->writeInt8( m_VplanType );
		packet->writeInt32( m_pPlayer->getRecord( 2046 ) );
		packet->writeInt32( m_pPlayer->getRecord( 2047 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1096 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1097 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1098 ) );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}

void CVplan::SendVplanIcon()
{
	if ( !m_pPlayer ) return;
	VplanIconStu stu;
	GetVplanIconStu( stu );
	ShowIcon icon;
	memset( &icon, 0, sizeof(icon) );
	icon.nId = stu.nId;
	icon.nState = stu.nState;
	icon.nLeftTime = 0;
	m_pPlayer->SendIconState( &icon );
}

bool CVplan::HaveVplanGift()
{
	if ( !m_pPlayer ) return false;
	if ( (m_VplanType == 1 || m_VplanType == 2) && m_pPlayer->getRecord( 1097 ) <= 0 ) return true;
	return ( m_VplanType == 2 && m_pPlayer->getRecord( 1098 ) <= 0 );
}

int32_t CVplan::OnGetReward( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int8_t GiftType = inPacket->readInt8();
	int8_t VplanGiftType = inPacket->readInt8();
	int32_t Index = inPacket->readInt32();
	const CfgVplanMap* pMap = CFG_DATA.GetCfgVplanMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgVplanMap::const_iterator it = pMap->find( Index );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	switch ( GiftType )
	{
	case 1: // 每日奖励
	{
		int32_t nOldRecord = m_pPlayer->getRecord( 2046 );
		if ( nOldRecord > 0 ) return ERR_INVALID_DATA;
		if ( m_VplanLevel != it->second.nLevel ) return ERR_INVALID_DATA;
		if ( !m_pPlayer->GetBag().AddItem( it->second.EveryDayReward, IACR_VPALN_GIFT ) ) return ERR_INVALID_DATA;
		m_pPlayer->updateRecord( 2046, Index );
		break;
	}
	case 2: // 等级奖励
	{
		int32_t nOldRecord = m_pPlayer->getRecord( 1096 );
		int32_t nNewRecord = nOldRecord | (1 << (Index - 1));
		if ( nOldRecord == nNewRecord ) return ERR_INVALID_DATA;
		if ( it->second.nLevel > m_pPlayer->getLevel() ) return ERR_INVALID_DATA;
		if ( !m_pPlayer->GetBag().AddItem( it->second.LevelReward, IACR_VPALN_GIFT ) ) return ERR_INVALID_DATA;
		m_pPlayer->updateRecord( 1096, nNewRecord );
		break;
	}
	case 3: // V计划礼包
	{
		int32_t nOldRecord = m_pPlayer->getRecord( 1097 );
		if ( nOldRecord > 0 ) return ERR_INVALID_DATA;
		if ( !m_pPlayer->GetBag().AddItem( it->second.LevelReward, IACR_VPALN_GIFT ) ) return ERR_INVALID_DATA;
		m_pPlayer->updateRecord( 1097, Index );
		break;
	}
	default:
		return ERR_INVALID_DATA;
	}
	SendVplanInfo();
	SendVplanIcon();
	return 0;
}

void CVplan::GetVplanIconStu( VplanIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
	stu.nId = VPLAN_ICON;
	if ( HaveVplanGift() || HaveEveryDayGift() || HaveLevelGift() )
		stu.nState = 1;
}

int8_t CVplan::GetVplanIconState()
{
	return 0;
}

bool CVplan::HaveXunLeiVipReward()
{
	return false;
}
bool CVplan::IsGetAllXunLeiReward()
{
	return true;
}
void CVplan::SendXunLieInfo()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_XUN_LEI_INFO );
	if ( packet )
	{
		packet->writeInt32( m_XlNxLevel );
		packet->writeInt32( m_pPlayer->getRecord( 1156 ) );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
void CVplan::SendXunLeiIcon()
{
}
void CVplan::GetXunLeiIconState( int8_t& nState )
{
	nState = 0;
}
void CVplan::GetXunLeiIconStu( XunLeiIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
}
int32_t CVplan::OnGetXunLeiReward( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int32_t Index = inPacket->readInt32();
	int32_t nOldRecord = m_pPlayer->getRecord( 1156 );
	int32_t nNewRecord = nOldRecord | (1 << (Index - 1));
	if ( nOldRecord == nNewRecord ) return ERR_INVALID_DATA;
	const CfgXunLeiMap* pMap = CFG_DATA.GetXunLeiTable();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgXunLeiMap::const_iterator it = pMap->find( Index );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	if ( m_XlNxLevel < it->second.nLevel ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Reward, IACR_XUN_LEI ) ) return ERR_INVALID_DATA;
	m_pPlayer->updateRecord( 1156, nNewRecord );
	SendXunLeiIcon();
	SendXunLieInfo();
	return 0;
}
int32_t CVplan::GetXunLeiDownlondIcon()
{
	return 0;
}
int32_t CVplan::GetXunLeiVipIcon()
{
	return 0;
}
int32_t CVplan::GetXunLeiDaTingIcon()
{
	return 0;
}

void CVplan::SendYYInfo()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_YY_INFO );
	if ( packet )
	{
		packet->writeInt32( m_YyLevel );
		packet->writeInt32( m_pPlayer->getRecord( 1100 ) );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
void CVplan::SendYYVipInfo()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_YY_VIP_INFO );
	if ( packet )
	{
		packet->writeInt32( m_YyVipLevel );
		const CfgYYVipMap* pMap = CFG_DATA.GetCfgYYVipMap();
		if ( pMap )
		{
			packet->writeInt8( (int8_t)pMap->size() );
			for ( CfgYYVipMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
			{
				packet->writeInt8( (int8_t)m_pPlayer->getRecord( it->first + 1500 ) );
			}
		}
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
void CVplan::SendYYVipIcon()
{
}
bool CVplan::HaveYYVipLeftGift()
{
	return false;
}
bool CVplan::HaveYYLevelReward()
{
	return false;
}
void CVplan::GetYYVipIconState( int8_t& nState )
{
	nState = 0;
}
void CVplan::GetYYVipIconStu( YYVipIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
}
void CVplan::AppendYYInfo( Answer::NetPacket* packet )
{
	if ( packet )
	{
		packet->writeInt8( (int8_t)m_YyVipLevel );
		packet->writeInt8( (int8_t)m_YySuperLevel );
	}
}
int32_t CVplan::OnGetYYLevelReward( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int32_t Index = inPacket->readInt8();
	const CfgYYGameAppMap* pMap = CFG_DATA.GetYYGameAppMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgYYGameAppMap::const_iterator it = pMap->find( Index );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	int32_t nOldRecord = m_pPlayer->getRecord( 1100 );
	int32_t nNewRecord = nOldRecord | (1 << (Index - 1));
	if ( nOldRecord == nNewRecord ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Reward, IACR_YY_DA_TING ) ) return ERR_INVALID_DATA;
	m_pPlayer->updateRecord( 1100, nNewRecord );
	SendYYInfo();
	return 0;
}
int32_t CVplan::OnGetYYVipGift( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int32_t nIndex = inPacket->readInt8();
	const CfgYYVipMap* pMap = CFG_DATA.GetCfgYYVipMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgYYVipMap::const_iterator it = pMap->find( nIndex );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	if ( m_YyVipLevel < it->second.nLevel ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetOperateLimit().GetLimitCount( nIndex + 1500 ) >= 1 ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Gift, IACR_YY_VIP ) ) return ERR_INVALID_DATA;
	m_pPlayer->GetOperateLimit().AddLimitCount( nIndex + 1500, 1 );
	SendYYVipInfo();
	SendYYVipIcon();
	return 0;
}
int32_t CVplan::OnLoginFromYYgameApp( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	m_fromLYGameApp = inPacket->readInt8();
	return 0;
}

void CVplan::SendLuDaShiVipInfo()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_VPLAN_ICON );
	if ( packet )
	{
		packet->writeInt32( m_PlatformVip );
		packet->writeInt32( m_PlatformSuperVip );
		const CfgLuDaShiMap* pMap = CFG_DATA.GetLaDaShiHuiYuanMap();
		if ( pMap )
		{
			packet->writeInt8( (int8_t)pMap->size() );
			for ( CfgLuDaShiMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
			{
				packet->writeInt8( (int8_t)m_pPlayer->getRecord( it->first + 1551 ) );
			}
		}
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
void CVplan::SendLuDaShiIcon()
{
}
bool CVplan::HaveLuDaShiVipLeftGift()
{
	return false;
}
void CVplan::GetLuDaShiIconState( int8_t& nState )
{
	nState = 0;
}
void CVplan::GetLuDaShiStu( LuDaShiIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
}
int32_t CVplan::OnGetLuDaShiVipGift( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int32_t nIndex = inPacket->readInt8();
	const CfgLuDaShiMap* pMap = CFG_DATA.GetLaDaShiHuiYuanMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgLuDaShiMap::const_iterator it = pMap->find( nIndex );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	if ( m_pPlayer->GetOperateLimit().GetLimitCount( nIndex + 1551 ) > 0 ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Gift, IACR_YY_VIP ) ) return ERR_INVALID_DATA;
	m_pPlayer->GetOperateLimit().AddLimitCount( nIndex + 1551, 1 );
	SendLuDaShiVipInfo();
	SendLuDaShiIcon();
	return 0;
}

void CVplan::SendSgGameAppInfo()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SG_GAME_APP_INFO );
	if ( packet )
	{
		packet->writeInt32( m_SgHallLevel );
		packet->writeInt32( m_pPlayer->getRecord( 1091 ) );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
void CVplan::SendSgDownLoadIcon()
{
}
bool CVplan::HaveSgDownLoadGift()
{
	return false;
}
bool CVplan::HaveSgGameAppReward()
{
	return false;
}
void CVplan::GetSgDownLoadIconStu( SgDownLoadIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
}
int32_t CVplan::GetSgDownLoadIocnState()
{
	return 0;
}
int32_t CVplan::OnGetSgGameApp( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int32_t Index = inPacket->readInt8();
	const CfgSgGameAppMap* pMap = CFG_DATA.GetSgGameAppMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgSgGameAppMap::const_iterator it = pMap->find( Index );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	int32_t nOldRecord = m_pPlayer->getRecord( 1091 );
	int32_t nNewRecord = nOldRecord | (1 << (Index - 1));
	if ( nOldRecord == nNewRecord ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Reward, IACR_SG_GAME_APP ) ) return ERR_INVALID_DATA;
	m_pPlayer->updateRecord( 1091, nNewRecord );
	SendSgGameAppInfo();
	return 0;
}

void CVplan::SendSwVipReward()
{
	if ( !m_pPlayer ) return;
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SW_VIP_REWARD_INFO );
	if ( packet )
	{
		packet->writeInt8( (int8_t)m_nSwVipLevel );
		packet->writeInt32( m_pPlayer->getRecord( 1099 ) );
		packet->writeInt8( m_bSwVipBar );
		packet->writeInt32( m_pPlayer->getRecord( 1092 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1094 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1095 ) );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
void CVplan::SendSwVipIcon()
{
}
void CVplan::SendSwVipBarIcon()
{
}
bool CVplan::HaveEveryDayGift()
{
	if ( !m_pPlayer ) return false;
	if ( (m_VplanType == 1 || m_VplanType == 2) && m_pPlayer->getRecord( 2046 ) <= 0 ) return true;
	return ( m_VplanType == 2 && m_pPlayer->getRecord( 2047 ) <= 0 );
}
bool CVplan::HaveLevelGift()
{
	if ( !m_pPlayer ) return false;
	if ( m_VplanType == 1 || m_VplanType == 2 )
	{
		int32_t nRecord = m_pPlayer->getRecord( 1096 );
		int32_t nLevel = m_pPlayer->getLevel();
		const CfgVplanMap* pMap = CFG_DATA.GetCfgVplanMap();
		if ( pMap )
		{
			for ( CfgVplanMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
			{
				if ( it->second.nLevel <= nLevel && ((nRecord >> (it->first - 1)) & 1) == 0 )
					return true;
			}
		}
	}
	return false;
}
bool CVplan::checkSwVipRewardCondition()
{
	return true;
}
bool CVplan::isGetAllSwVipReward()
{
	int32_t nRecord = m_pPlayer->getRecord( 1099 );
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipRewardMap();
	if ( !pMap ) return true;
	for ( CfgSwVipRewardMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
	{
		if ( ((nRecord >> (it->first - 1)) & 1) == 0 ) return false;
	}
	return true;
}
bool CVplan::checkSwBarRewardCondition()
{
	return m_bSwVipBar != 0;
}
bool CVplan::isGetAllSwVipBarReward()
{
	int32_t nRecord = m_pPlayer->getRecord( 1095 );
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipBarRewardMap();
	if ( !pMap ) return true;
	for ( CfgSwVipRewardMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
	{
		if ( ((nRecord >> (it->first - 1)) & 1) == 0 ) return false;
	}
	return true;
}

void CVplan::CheckSwBarLoginCount()
{
}
void CVplan::resetSwVipDailyReward()
{
	if ( !m_pPlayer ) return;
	int32_t nRecord = m_pPlayer->getRecord( 1099 );
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipRewardMap();
	if ( !pMap ) return;
	for ( CfgSwVipRewardMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
	{
		if ( it->second.nType == 2 ) nRecord ^= (1 << (it->first - 1));
	}
	m_pPlayer->updateRecord( 1099, nRecord );
}
void CVplan::resetSwBarDailyReward()
{
	if ( !m_pPlayer ) return;
	int32_t nRecord = m_pPlayer->getRecord( 1095 );
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipBarRewardMap();
	if ( !pMap ) return;
	for ( CfgSwVipRewardMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
	{
		if ( it->second.nType == 2 ) nRecord ^= (1 << (it->first - 1));
	}
	m_pPlayer->updateRecord( 1095, nRecord );
}
void CVplan::getSwVipIconStu( SwVipIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
}
int32_t CVplan::GetSwVipIconState()
{
	return 0;
}
void CVplan::getSwVipBarIconStu( SwVipBarIconStu& stu )
{
	memset( &stu, 0, sizeof(stu) );
}
int32_t CVplan::GetSwVipBarIconState()
{
	return 0;
}
int32_t CVplan::getSwVipRewardCount()
{
	if ( !m_pPlayer ) return 0;
	int32_t nCount = 0;
	int32_t nRecord = m_pPlayer->getRecord( 1099 );
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipRewardMap();
	if ( !pMap ) return 0;
	for ( CfgSwVipRewardMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
	{
		if ( ((nRecord >> (it->first - 1)) & 1) == 0 ) ++nCount;
	}
	return nCount;
}
int32_t CVplan::getSwVipBarRewardCount()
{
	if ( !m_pPlayer ) return 0;
	int32_t nCount = 0;
	int32_t nRecord = m_pPlayer->getRecord( 1095 );
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipBarRewardMap();
	if ( !pMap ) return 0;
	for ( CfgSwVipRewardMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it )
	{
		if ( ((nRecord >> (it->first - 1)) & 1) == 0 ) ++nCount;
	}
	return nCount;
}
void CVplan::AppendSwVipInfo( Answer::NetPacket* packet )
{
	if ( packet ) packet->writeInt8( (int8_t)m_nSwVipLevel );
}
int32_t CVplan::OnGetSWVipReward( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int8_t nIndex = inPacket->readInt8();
	int32_t nOldRecord = m_pPlayer->getRecord( 1099 );
	int32_t nNewRecord = nOldRecord | (1 << (nIndex - 1));
	if ( nOldRecord == nNewRecord ) return ERR_INVALID_DATA;
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipRewardMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgSwVipRewardMap::const_iterator it = pMap->find( nIndex );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Reward, IACR_VPALN_GIFT ) ) return ERR_INVALID_DATA;
	m_pPlayer->updateRecord( 1099, nNewRecord );
	SendSwVipIcon();
	return 0;
}
int32_t CVplan::OnGetSWVipBarReward( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer ) return ERR_INVALID_DATA;
	int8_t nIndex = inPacket->readInt8();
	int32_t nOldRecord = m_pPlayer->getRecord( 1095 );
	int32_t nNewRecord = nOldRecord | (1 << (nIndex - 1));
	if ( nOldRecord == nNewRecord ) return ERR_INVALID_DATA;
	const CfgSwVipRewardMap* pMap = CFG_DATA.GetSwVipBarRewardMap();
	if ( !pMap ) return ERR_INVALID_DATA;
	CfgSwVipRewardMap::const_iterator it = pMap->find( nIndex );
	if ( it == pMap->end() ) return ERR_INVALID_DATA;
	if ( !m_pPlayer->GetBag().AddItem( it->second.Reward, IACR_VPALN_GIFT ) ) return ERR_INVALID_DATA;
	m_pPlayer->updateRecord( 1095, nNewRecord );
	SendSwVipBarIcon();
	return 0;
}

int32_t CVplan::GetPlatformVipLevel() const
{
	return m_PlatformVip;
}
