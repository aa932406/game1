#include "WarVictory.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
enum WarVictoryType
{
	EVERY_DAY_LOGIN		= 1,	//每天登陆
	EVENY_DAY_BUY		= 2,	//每次购买
};

CWarVictory::CWarVictory()
{
	OnCleanUp();
}

CWarVictory::~CWarVictory()
{

}

void CWarVictory::OnCleanUp()
{

}

void CWarVictory::OnUpdate( int64_t curTick )
{

}

void CWarVictory::OnDaySwitch( int32_t nDiffDays )
{
	SendWarVictoryIcon();
}

void CWarVictory::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_VAR_VICTORY_INFO );
	procList.push_back( CM_GET_VAR_VICTORY_REWARD );
}

int32_t CWarVictory::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_ASK_VAR_VICTORY_INFO:
		{
			SendWarVictoryInfo();
			break;
		}
	case CM_GET_VAR_VICTORY_REWARD:
		{
			return OnGetWarVictoryReward( inPacket );
		}
	default:
		break;
	}
	return ERR_OK;
}

int32_t	CWarVictory::OnGetWarVictoryReward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t Index = inPacket->readInt8();
	WarVictoryHd* pWarVictory = CFG_DATA.GetWarVictoryHdCfg( Index );
	if ( NULL == pWarVictory )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t NowTime = m_pPlayer->getNow();
	if ( NowTime < pWarVictory->StartTime || NowTime > pWarVictory->EndTime )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pWarVictory->Type == EVERY_DAY_LOGIN )
	{
		if ( m_pPlayer->getRecord( RP_WAR_VICTORY_LOGIN ) > 0 )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->GetBag().AddItemsAndEggs( pWarVictory->Rewards,  IACR_VAR_VICTORY ) )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->updateRecord( RP_WAR_VICTORY_LOGIN, 1 );
		SendWarVictoryIcon();
	}
	else if ( pWarVictory->Type == EVENY_DAY_BUY )
	{
		if ( m_pPlayer->getRecord( RP_WAR_VICTORY_BUY_GIFT ) >= pWarVictory->Times )
		{
			return ERR_SYETEM_ERR;
		}
		if ( pWarVictory->NeedGold <= 0 )
		{
			return ERR_SYETEM_ERR;
		}

		if ( !m_pPlayer->GetBag().AddItemsAndEggs( pWarVictory->Rewards,  IACR_VAR_VICTORY ) )
		{
			return ERR_SYETEM_ERR;
		}

		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD,pWarVictory->NeedGold, GCR_BUY_WAR_VICTORY_GIFT ) )
		{
			return ERR_SYETEM_ERR;
		}

		m_pPlayer->GetOperateLimit().AddLimitCount(RP_WAR_VICTORY_BUY_GIFT, 1);
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	GongGaoList::iterator it = pWarVictory->GongGaoId.begin();
	for ( ; it != pWarVictory->GongGaoId.end(); ++it )
	{
		if ( it->Job == 0 || it->Job == m_pPlayer->getJob() )
		{
			if ( it->GongGaoId > 0 )
			{
				GongGao( it->GongGaoId );
			}
		}
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), Index );
	return ERR_OK;
}

void CWarVictory::GongGao( int32_t GongGaoId  )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( GongGaoId );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->setSize(packet->getWOffset());
	packet->setProc( SM_SEND_NOTICE_PARAM );
	GAME_SERVICE.worldBroadcast(packet);
}

void CWarVictory::GetWarVictoryIconState( IconStateList& IconList )
{
	WarVictoryHd* pWarVictory = CFG_DATA.GetWarVictoryHdCfg( 1 );
	if ( NULL == pWarVictory )
	{
		return;
	}
	int32_t NowTime = m_pPlayer->getNow();
	if ( NowTime < pWarVictory->StartTime || NowTime > pWarVictory->EndTime )
	{
		return;
	}
	IconList.push_back( GetWarVictoryIconStu() );
}

void CWarVictory::SendWarVictoryIcon()
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
	ShowIcon stu = GetWarVictoryIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8( stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

ShowIcon CWarVictory::GetWarVictoryIconStu()
{
	ShowIcon stu = {};
	if ( NULL == m_pPlayer )
	{
		return stu;
	}
	WarVictoryHd* pWarVictory = CFG_DATA.GetWarVictoryHdCfg( 1 );
	if ( NULL == pWarVictory )
	{
		return stu;
	}
	int32_t NowTime = m_pPlayer->getNow();
	if ( NowTime < pWarVictory->StartTime || NowTime > pWarVictory->EndTime )
	{
		stu.nState	= AS_TIME_OUT;
	}
	else
	{
		stu.nState	= AS_RUNNING;
	}
	stu.nId			= WAR_VICTORY_ICON;
	if ( m_pPlayer->getRecord( RP_WAR_VICTORY_LOGIN ) == 0 )
	{
		stu.IconRight = 1;
	}
	stu.nLeftTime	= -1;
	return stu;
}

void CWarVictory::SendWarVictoryInfo()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_WAR_VICTORY_INFO );
	if (NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getRecord(RP_WAR_VICTORY_LOGIN) );
	packet->writeInt32( m_pPlayer->getRecord(RP_WAR_VICTORY_BUY_GIFT) );
	packet->writeInt32( m_pPlayer->getRecord(RP_WAR_VICTORY_CHONG_ZHI_VALUES ) );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CWarVictory::AddGold( int32_t Gold )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	WarVictoryHd* pWarVictory = CFG_DATA.GetWarVictoryHdCfg( 1 );
	if ( NULL == pWarVictory )
	{
		return;
	}
	int32_t NowTime = m_pPlayer->getNow();
	if ( NowTime < pWarVictory->StartTime || NowTime > pWarVictory->EndTime )
	{
		return;
	}
	if ( Gold <= 0 )
	{
		return;
	}
	m_pPlayer->GetOperateLimit().AddLimitCount( RP_WAR_VICTORY_CHONG_ZHI_VALUES, Gold );
	m_pPlayer->AddCurrency( CURRENCY_GOLD, Gold/10,GCT_WAR_VICTORY_FAN_LI );
	SendWarVictoryInfo();
}