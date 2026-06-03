#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharHallOfFame.h"
#include "Timer.h"

using namespace Answer;

#define CLEAR_CD_VIP_LEVEL	3		// VIP3以上消除冷却

CExtCharHallOfFame::CExtCharHallOfFame()
{
	OnCleanUp();
}

CExtCharHallOfFame::~CExtCharHallOfFame()
{
}

void CExtCharHallOfFame::OnCleanUp()
{
	//m_nCDTime		= 0;
}

void CExtCharHallOfFame::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_HALL_OF_FAME_FIGHT );						// 挑战
	procList.push_back( CM_HALL_OF_FAME_BUY_TIMES );					// 购买次数
	procList.push_back( CM_HALL_OF_FAME_CLEAR_CD );						// 秒CD
	procList.push_back( CM_HALL_OF_FAME_INFO );							// 请求界面信息

	procList.push_back( IM_SOCIAL_GAME_HALL_OF_FAME_FIGHT_RESULT );		// 挑战结果
	procList.push_back( IM_SOCIAL_GAME_HALL_OF_FAME_GET_REWARD );		// 领取奖励
	procList.push_back( IM_SOCIAL_GAME_HALL_OF_FAME_RANK_REWARD_INFO );	// 奖励信息
}

int32_t CExtCharHallOfFame::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !IsFunctionOpen() )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case CM_HALL_OF_FAME_FIGHT:								return onFight( inPacket );
	case CM_HALL_OF_FAME_BUY_TIMES:							return onBuyTimes( inPacket );
	case CM_HALL_OF_FAME_CLEAR_CD:							return onClearCD( inPacket );
	case CM_HALL_OF_FAME_INFO:								return onRequestInfo( inPacket );
	case IM_SOCIAL_GAME_HALL_OF_FAME_FIGHT_RESULT:			return onSocialFightResult( inPacket );
	case IM_SOCIAL_GAME_HALL_OF_FAME_GET_REWARD:			return onSocialGetReward( inPacket );
	case IM_SOCIAL_GAME_HALL_OF_FAME_RANK_REWARD_INFO:		return onSocialRankRewardInfo( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onFight( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nIndex = inPacket->readInt32();
	if ( getFightTimes() >= getLimitFightTimes() )
	{
		return ERR_INVALID_DATA;
	}

	if ( getCDTime() > 0 )
	{
		return ERR_INVALID_DATA;
	}

	sendSocialFight( nIndex );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_HALL_FAME );
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onBuyTimes( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( getBuyTimes() >= getLimitBuyTimes() )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, HALL_OF_FAME_BUY_COST, GCR_HALL_OF_FAME_BUY_TIMES ) )
	{
		return ERR_INVALID_DATA;
	}

	addBuyTimes();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), getBuyTimes() );
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onClearCD( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	if ( getCDTime() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, HALL_OF_FAME_CLEAR_CD_COST, GCR_HALL_OF_FAME_CLEAR_CD ) )
	{
		return ERR_INVALID_DATA;
	}

	clearCDTime();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onRequestInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	sendSocialRequestInfo();
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onSocialFightResult( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int8_t bWin = inPacket->readInt8();

	if ( bWin > 0 )
	{
		m_pPlayer->addExp( 1000000 );
		m_pPlayer->AddCurrency( CURRENCY_HONOR, 10000, HCR_HALL_OF_FAME_FIGHT );
	}
	else
	{
		addCDTime();
		m_pPlayer->addExp( 500000 );
		m_pPlayer->AddCurrency( CURRENCY_HONOR, 5000, HCR_HALL_OF_FAME_FIGHT );
	}
	m_pPlayer->GetTask().updateTaskCount( TC_HALL_OF_FAME );
	addFightTimes();
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onSocialGetReward( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nLastIndex = inPacket->readInt32();

	const HallOfFameReward* pReward = CFG_DATA.GetHallOfFameTable().GetReward( nLastIndex );
	if ( NULL == pReward )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pReward->items.empty() )
	{
		if ( !m_pPlayer->GetBag().AddItem( pReward->items, IACR_HALL_OF_FAME_REWARD ) )
		{
			sendSocialRewardResult( nLastIndex, false );
			return ERR_INVALID_DATA;
		}
	}

	sendSocialRewardResult( nLastIndex, true );
	m_pPlayer->AddCurrency( CURRENCY_HONOR, pReward->nHonor, HCR_HALL_OF_FAME_RANK_REWARD );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_HALL_OF_FAME_GET_REWARD );
	SendIconState();
	return ERR_OK;
}

int32_t CExtCharHallOfFame::onSocialRankRewardInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nLastIndex = inPacket->readInt32();
	int8_t nReward = inPacket->readInt8();

	if ( IsFunctionOpen() )
	{
		if ( nReward == 0 )
		{
			SendIconState( 1 );
		}
	}
	return ERR_OK;
}

bool CExtCharHallOfFame::IsFunctionOpen() const
{
	return m_pPlayer != NULL && m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_HALL_OF_FAME );
}

void CExtCharHallOfFame::sendSocialFight( int32_t nIndex )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_HALL_OF_FAME_FIGHT );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nIndex );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharHallOfFame::sendSocialRequestInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_HALL_OF_FAME_REQUEST_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( getLimitFightTimes() - getFightTimes() );
	packet->writeInt32( getLimitBuyTimes() - getBuyTimes() );
	packet->writeInt32( getCDTime() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharHallOfFame::sendSocialRewardResult( int32_t nLastIndex, bool bSuccess )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_HALL_OF_FAME_REWARD_RESULT );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nLastIndex );
	packet->writeInt8( bSuccess ? 1 : 0 );

	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}


int32_t	CExtCharHallOfFame::getFightTimes() const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	return m_pPlayer->GetOperateLimit().GetLimitCount( PR_FALL_OF_FAME_FIGHT_TIMES );
}

int32_t	CExtCharHallOfFame::getLimitFightTimes() const
{
	return HALL_OF_FAME_FREE_TIMES + getBuyTimes();
}

int32_t CExtCharHallOfFame::getBuyTimes() const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	return m_pPlayer->GetOperateLimit().GetLimitCount( PR_FALL_OF_FAME_BUY_TIMES );
}

int32_t CExtCharHallOfFame::getLimitBuyTimes() const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	return m_pPlayer->GetPlayerVip().GetHallOfFameBuyTimes();
}

int32_t CExtCharHallOfFame::getCDTime() const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	if ( m_pPlayer->GetPlayerVip().GetMaxVipLevel() >= CLEAR_CD_VIP_LEVEL )
	{
		return 0;
	}

	int32_t nCDTime = m_pPlayer->GetOperateLimit().GetLimitCount( PR_FALL_OF_FAME_CD_TIME );
	int32_t nNowTime = TIMER.GetNow();
	if ( nCDTime > nNowTime  )
	{
		return nCDTime - nNowTime;
	}
	else
	{
		return 0;
	}
}

void CExtCharHallOfFame::addFightTimes()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_pPlayer->GetOperateLimit().AddLimitCount( PR_FALL_OF_FAME_FIGHT_TIMES, 1 );
}

void CExtCharHallOfFame::addBuyTimes()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_pPlayer->GetOperateLimit().AddLimitCount( PR_FALL_OF_FAME_BUY_TIMES, 1 );
}

void CExtCharHallOfFame::addCDTime()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( m_pPlayer->GetPlayerVip().GetMaxVipLevel() >= CLEAR_CD_VIP_LEVEL )
	{
		return;
	}

	int32_t nCDTime = m_pPlayer->GetOperateLimit().GetLimitCount( PR_FALL_OF_FAME_CD_TIME );
	int32_t nNowTime = TIMER.GetNow();
	if ( nCDTime > nNowTime  )
	{
		nCDTime += HALL_OF_FAME_CD_TIME;
	}
	else
	{
		nCDTime = nNowTime + HALL_OF_FAME_CD_TIME;
	}
	m_pPlayer->GetOperateLimit().UpdateLimitCount( PR_FALL_OF_FAME_CD_TIME, nCDTime );
}

void CExtCharHallOfFame::clearCDTime()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	m_pPlayer->GetOperateLimit().Reset( PR_FALL_OF_FAME_CD_TIME );
}

void CExtCharHallOfFame::GetIconState( IconStateList& iconList )
{
	if ( !IsFunctionOpen() )
	{
		return;
	}

	ShowIcon icon = {};
	icon.nId		= HALL_OF_FAME_ICON;
	icon.nState		= AS_RUNNING;
	icon.nLeftTime	= -1;

	iconList.push_back( icon );
}

void CExtCharHallOfFame::SendIconState( int32_t nReward )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}

	ShowIcon stu = {};
	stu.nId			= HALL_OF_FAME_ICON;
	stu.nState		= AS_RUNNING;
	stu.nLeftTime	= -1;
	stu.IconRight	= nReward;

	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);		
}
