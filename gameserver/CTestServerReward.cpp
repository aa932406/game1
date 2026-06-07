#include "stdafx.h"
#include "CTestServerReward.h"
#include "GameService.h"
#include "Player.h"
#include "Bag.h"
#include "FunctionOpen.h"
#include "CfgData.h"

using namespace Answer;

CTestServerReward::CTestServerReward()
	: CExtSystemBase()
{
}

CTestServerReward::~CTestServerReward()
{
}

void CTestServerReward::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 469 );
}

int32_t CTestServerReward::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( nProcId == 469 )
	{
		return OnGetTestServerReward( inPacket );
	}

	return ERR_INVALID_DATA;
}

int32_t CTestServerReward::OnGetTestServerReward( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 192 ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();
	const TestServerReward* pCfg = CFG_DATA.GetTestServerReward( nId );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	int32_t OldRecord = m_pPlayer->getRecord( 1915 );
	int32_t NewRecord = OldRecord | ( 1 << ( nId - 1 ) );
	if ( NewRecord == OldRecord )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCfg->nType == 1 )
	{
		if ( m_pPlayer->getRecord( 1011 ) < pCfg->nParm )
		{
			return ERR_INVALID_DATA;
		}
	}
	else if ( pCfg->nType == 2 )
	{
		if ( m_pPlayer->getLevel() < pCfg->nParm )
		{
			return ERR_INVALID_DATA;
		}
	}
	else
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddItem( &pCfg->vItems, ICR_TEST_SERVER ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 1915, NewRecord );

	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nId );

	if ( pCfg->nGongId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( 0, Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet != NULL )
		{
			packet->writeInt32( pCfg->nGongId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( nId );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( 0, packet );
		}
	}

	SendTestServerIcon();
	return 0;
}

void CTestServerReward::GetTestServerIcon( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 192 ) )
	{
		return;
	}

	ShowIcon stu;
	memset(&stu, 0, sizeof(stu));
	stu.nId = TEST_SERVER_REWARD_ICON;
	stu.nState = AS_RUNNING;
	stu.nLeftTime = -1;
	IconList.push_back( stu );
}

void CTestServerReward::SendTestServerIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 192 ) )
	{
		return;
	}

	ShowIcon stu;
	memset(&stu, 0, sizeof(stu));
	stu.nId = TEST_SERVER_REWARD_ICON;
	stu.nState = AS_RUNNING;
	stu.nLeftTime = -1;
	m_pPlayer->SendIconState( &stu );
}

int32_t CTestServerReward::CanActivationCount()
{
	int32_t Count = 0;
	if ( NULL == m_pPlayer )
	{
		return Count;
	}

	const TestServerRewardMap& RewardMap = CFG_DATA.GetTestServerRewardMap();
	int32_t OldRecord = m_pPlayer->getRecord( 1915 );

	for ( TestServerRewardMap::const_iterator it = RewardMap.begin(); it != RewardMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( NewRecord != OldRecord )
		{
			if ( it->second.nType == 1 )
			{
				if ( m_pPlayer->getRecord( 1011 ) >= it->second.nParm )
				{
					++Count;
				}
			}
			else if ( it->second.nType == 2 )
			{
				if ( m_pPlayer->getLevel() >= it->second.nParm )
				{
					++Count;
				}
			}
		}
	}

	return Count;
}

bool CTestServerReward::IsAllGetReward()
{
	if ( NULL == m_pPlayer )
	{
		return true;
	}

	int32_t OldRecord = m_pPlayer->getRecord( 1915 );
	const TestServerRewardMap& RewardMap = CFG_DATA.GetTestServerRewardMap();

	for ( TestServerRewardMap::const_iterator it = RewardMap.begin(); it != RewardMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( NewRecord != OldRecord )
		{
			return false;
		}
	}

	return true;
}
