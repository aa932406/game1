#include "stdafx.h"
#include "CWan360.h"
#include "GameService.h"
#include "Player.h"
#include "ItemHelper.h"
#include "Timer.h"

using namespace Answer;

CWan360::CWan360()
	: m_LastUpdateTiem( 0 )
	, m_IsSpeed360Start( false )
	, m_IsGameAppLogin( false )
	, m_bSouGouSkinLogin( false )
{
}

CWan360::~CWan360()
{
}

void CWan360::OnDaySwitch( int32_t nDiffDays )
{
	SendSpeed360Icon();
	SendGameAppIcon();
}

void CWan360::OnUpdate( int64_t curTick )
{
	if ( NULL == m_pPlayer || curTick - m_LastUpdateTiem <= 999 )
	{
		return;
	}

	m_LastUpdateTiem = curTick;
	int32_t Now = m_pPlayer->getNow();
	const Speed360Reward* pReward = CFG_DATA.Get360Reward();

	if ( pReward != NULL )
	{
		if ( pReward->StartTime > Now || pReward->EndTime < Now )
		{
			if ( m_IsSpeed360Start )
			{
				m_IsSpeed360Start = false;
				SendSpeed360Icon();
			}
		}
		else if ( !m_IsSpeed360Start )
		{
			m_IsSpeed360Start = true;
			SendSpeed360Icon();
		}
	}
}

void CWan360::OnCleanUp()
{
	m_IsGameAppLogin = false;
	m_IsSpeed360Start = false;
	m_bSouGouSkinLogin = false;
	m_LastUpdateTiem = 0;
}

void CWan360::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 530 );
	procList.push_back( 531 );
	procList.push_back( 532 );
	procList.push_back( 533 );
	procList.push_back( 534 );
}

int32_t CWan360::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case 530:	return OnGetJiaSuQiuReward( inPacket );
	case 531:	return OnGetGameAppReward( inPacket );
	case 532:	return OnLoginFromGameApp( inPacket );
	case 533:	return OnGetSpeed360Reward( inPacket );
	case 534:	return OnLoginFromSouGouSkin( inPacket );
	default:	return ERR_OK;
	}
}

int32_t CWan360::OnGetJiaSuQiuReward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->GetPlatform() != "w360" )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getRecord( 1050 ) > 0 )
	{
		return ERR_INVALID_DATA;
	}

	const Wan360Reward* pReward = CFG_DATA.Get360RewardCfg( 100 );
	if ( NULL == pReward )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddItem( (MemChrBagVector*)&pReward->Items, ICR_360_JIA_SU_QIU ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 1050, 1 );
	SendJiaShuQiuIcon();

	return GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
}

int32_t CWan360::OnGetGameAppReward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	if ( CFG_DATA.Get360RewardIcon( m_pPlayer->GetPlatform() ) == 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_IsGameAppLogin )
	{
		return ERR_INVALID_DATA;
	}

	int32_t GetRewardTimes = m_pPlayer->getRecord( 1051 );
	if ( GetRewardTimes > 6 )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getRecord( 2028 ) > 0 )
	{
		return ERR_INVALID_DATA;
	}

	const Wan360Reward* pReward = CFG_DATA.Get360RewardCfg( GetRewardTimes + 1 );
	if ( NULL == pReward )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddItem( (MemChrBagVector*)&pReward->Items, ICR_360_GAME_APP ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 2028, 1 );
	m_pPlayer->updateRecord( 1051, GetRewardTimes + 1 );

	SendGameAppIcon();
	return GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
}

int32_t CWan360::OnLoginFromGameApp( Answer::NetPacket *inPacket )
{
	if ( CFG_DATA.Get360RewardIcon( m_pPlayer->GetPlatform() ) == 0 )
	{
		return ERR_INVALID_DATA;
	}

	m_IsGameAppLogin = true;
	return ERR_OK;
}

int32_t CWan360::OnLoginFromSouGouSkin( Answer::NetPacket *inPacket )
{
	const CfgSouGouSkin* pSkin = CFG_DATA.GetSouGouSkin( m_pPlayer->GetPlatform() );
	if ( NULL == pSkin )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getRecord( 1118 ) > 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddItem( (MemChrBagVector*)&pSkin->vReward, ICR_SOU_GOU_SKIN_LOGIN ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 1118, 1 );

	SendSouGouSkinIcon();
	return GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
}

int32_t CWan360::OnGetSpeed360Reward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return 2;
	}

	if ( !InSpeed360Time() )
	{
		return 2;
	}

	if ( m_pPlayer->getRecord( 2048 ) > 0 )
	{
		return 2;
	}

	const Speed360Reward* pReward = CFG_DATA.Get360Reward();
	if ( NULL == pReward )
	{
		return 2;
	}

	if ( m_pPlayer->GetBag().GetFreeSlotCount() < (int32_t)pReward->Rewards.size() )
	{
		return 2;
	}

	if ( !m_pPlayer->GetBag().AddItem( (MemChrBagVector*)&pReward->Rewards, ICR_SPEED_360_REWARD ) )
	{
		return 2;
	}

	m_pPlayer->updateRecord( 2048, 1 );
	SendSpeed360Icon();
	return 0;
}

bool CWan360::InSpeed360Time()
{
	int32_t Now = m_pPlayer->getNow();
	const Speed360Reward* pReward = CFG_DATA.Get360Reward();

	if ( NULL == pReward )
	{
		return false;
	}

	return pReward->StartTime <= Now && pReward->EndTime >= Now;
}

void CWan360::SendSouGouSkinIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	const CfgSouGouSkin* pSkin = CFG_DATA.GetSouGouSkin( m_pPlayer->GetPlatform() );
	if ( NULL == pSkin )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = pSkin->nIcon;
	m_pPlayer->SendIconState( &stu );
}

void CWan360::GetSouGouSkinIconState( IconStateList& IconList )
{
	const CfgSouGouSkin* pSkin = CFG_DATA.GetSouGouSkin( m_pPlayer->GetPlatform() );
	if ( NULL == pSkin || NULL == m_pPlayer )
	{
		return;
	}

	if ( m_pPlayer->getRecord( 1118 ) > 0 )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = pSkin->nIcon;
	IconList.push_back( stu );
}

void CWan360::SendGameAppIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( CFG_DATA.Get360RewardIcon( m_pPlayer->GetPlatform() ) == 0 )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = CFG_DATA.Get360RewardIcon( m_pPlayer->GetPlatform() );
	m_pPlayer->SendIconState( &stu );
}

void CWan360::GetGameAppIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( CFG_DATA.Get360RewardIcon( m_pPlayer->GetPlatform() ) == 0 )
	{
		return;
	}

	if ( m_pPlayer->getRecord( 2028 ) > 6 )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = CFG_DATA.Get360RewardIcon( m_pPlayer->GetPlatform() );
	IconList.push_back( stu );
}

void CWan360::SendJiaShuQiuIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( m_pPlayer->GetPlatform() != "w360" )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = 1006; // JiaSuQiu icon id
	m_pPlayer->SendIconState( &stu );
}

void CWan360::GetJiaShuQiuIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( m_pPlayer->GetPlatform() != "w360" )
	{
		return;
	}

	if ( m_pPlayer->getRecord( 1050 ) > 0 )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = 1006; // JiaSuQiu icon id
	IconList.push_back( stu );
}

void CWan360::SendWeiXinIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	const CfgWeiXingGift* pGift = CFG_DATA.GetWeiXinGift( m_pPlayer->GetPlatform() );
	if ( NULL == pGift )
	{
		return;
	}

	if ( m_pPlayer->GetPlatform() == "duowanclouds" )
	{
		if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 211 ) )
		{
			return;
		}
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = pGift->nIconId;
	m_pPlayer->SendIconState( &stu );
}

void CWan360::GetWeiXinIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	const CfgWeiXingGift* pGift = CFG_DATA.GetWeiXinGift( m_pPlayer->GetPlatform() );
	if ( NULL == pGift )
	{
		return;
	}

	if ( m_pPlayer->GetPlatform() == "duowanclouds" )
	{
		if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 211 ) )
		{
			return;
		}
	}

	if ( m_pPlayer->getRecord( 1052 ) > 0 )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = pGift->nIconId;
	IconList.push_back( stu );
}

void CWan360::SendSpeed360Icon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( m_pPlayer->GetPlatform() != "w360" )
	{
		return;
	}

	if ( !m_IsSpeed360Start )
	{
		return;
	}

	ShowIcon stu;
	memset( &stu, 0, sizeof(stu) );
	stu.nId = 1010; // Speed360 icon id, adjust as needed
	m_pPlayer->SendIconState( &stu );
}

void CWan360::GetSpeed360State( IconStateList& IconList )
{
	if ( InSpeed360Time() )
	{
		ShowIcon stu;
		memset( &stu, 0, sizeof(stu) );
		stu.nId = 1010; // Speed360 icon id
		IconList.push_back( stu );
	}
}
