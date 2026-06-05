#include "stdafx.h"

#include "DBService.h"
#include "GameService.h"
#include "Player.h"
#include "FlopDraw.h"
#include "KaiFuHuoDong.h"

using namespace Answer;

CExtFlopDraw::CExtFlopDraw()
{
	OnCleanUp();
}

CExtFlopDraw::~CExtFlopDraw()
{

}

void CExtFlopDraw::OnCleanUp()
{
	m_FlopDrawRecordMap.clear();
}

void CExtFlopDraw::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_FlopDrawRecordMap = dbData.m_CFlopDraw.m_FlopDrawRecordMap;
}

void CExtFlopDraw::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_CFlopDraw.m_FlopDrawRecordMap = m_FlopDrawRecordMap;
}

bool CExtFlopDraw::OnFlopDraw( int32_t nType, int32_t nFlopId )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		return false;
	}

	int32_t FlopType = GetFlopType( nType, nFlopId );
	const FlopDrawCfgMap& allCfg = CFG_DATA.GetFlopDrawTable()->GetAll();

	FlopDrawCfgList validList;
	int32_t MaxRate = 0;
	for ( FlopDrawCfgMap::const_iterator iter = allCfg.begin(); iter != allCfg.end(); ++iter )
	{
		if ( iter->second.m_nType != FlopType )
		{
			continue;
		}
		if ( IsGet( nType, iter->first ) )
		{
			continue;
		}
		validList.push_back( iter->second );
		MaxRate += iter->second.m_nRate;
	}

	if ( MaxRate <= 0 )
	{
		return false;
	}

	int32_t nRand = RANDOM.generate( 1, MaxRate );
	FlopDrawCfg resultItem;
	memset( &resultItem, 0, sizeof( resultItem ) );

	for ( FlopDrawCfgList::iterator iter = validList.begin(); iter != validList.end(); ++iter )
	{
		if ( iter->m_nRate >= nRand )
		{
			resultItem = *iter;
			break;
		}
		nRand -= iter->m_nRate;
	}

	if ( resultItem.m_nId <= 0 )
	{
		return false;
	}

	if ( !DrawAndCost( nType, nFlopId ) )
	{
		return false;
	}

	m_pPlayer->GetBag().AddItem( resultItem.m_Item, IACR_NONE );
	addDrawTimes( nType, nFlopId, resultItem.m_nId );
	SendFlopOneRecord( m_pPlayer, nType, nFlopId, resultItem.m_nId );

	if ( resultItem.m_GongGaoId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_CHOU_JIANG_GONG_GAO );
		if ( packet != NULL )
		{
			packet->writeInt32( resultItem.m_GongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( resultItem.m_nId );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	return true;
}

int32_t CExtFlopDraw::GetFlopType( int32_t nType, int32_t nFlopId )
{
	if ( nType == 1 )
	{
		// COpenBeta - now integrated into CKaiFuHuoDong
		return KAI_FU_HUO_DONG.GetFlopType( nFlopId );
	}
	else if ( nType == 2 )
	{
		return KAI_FU_HUO_DONG.GetFlopType( nFlopId );
	}
	return 0;
}

bool CExtFlopDraw::DrawAndCost( int32_t nType, int32_t nFlopId )
{
	if ( IsFloped( nType, nFlopId ) )
	{
		return false;
	}

	if ( nType == 1 || nType == 2 )
	{
		return KAI_FU_HUO_DONG.CanFlopDraw( m_pPlayer, nFlopId );
	}

	return false;
}

bool CExtFlopDraw::IsGet( int32_t nType, int32_t nId )
{
	std::map<int, std::map<int,int>>::iterator it = m_FlopDrawRecordMap.find( nType );
	if ( it == m_FlopDrawRecordMap.end() )
	{
		return false;
	}

	for ( std::map<int,int>::iterator itFlop = it->second.begin(); itFlop != it->second.end(); ++itFlop )
	{
		if ( itFlop->second == nId )
		{
			return true;
		}
	}

	return false;
}

bool CExtFlopDraw::IsFloped( int32_t nType, int32_t nFlopId )
{
	std::map<int, std::map<int,int>>::iterator it = m_FlopDrawRecordMap.find( nType );
	if ( it == m_FlopDrawRecordMap.end() )
	{
		return false;
	}

	std::map<int,int>::iterator itFlop = it->second.find( nFlopId );
	if ( itFlop == it->second.end() )
	{
		return false;
	}

	return itFlop->second > 0;
}

void CExtFlopDraw::addDrawTimes( int32_t nType, int32_t nFlopId, int32_t FlopResult )
{
	std::map<int, std::map<int,int>>::iterator it = m_FlopDrawRecordMap.find( nType );
	if ( it != m_FlopDrawRecordMap.end() )
	{
		std::map<int,int>::iterator itFlop = it->second.find( nFlopId );
		if ( itFlop != it->second.end() )
		{
			itFlop->second = FlopResult;
		}
		else
		{
			it->second.insert( std::make_pair( nFlopId, FlopResult ) );
		}
	}
	else
	{
		std::map<int,int> TmpMap;
		TmpMap[nFlopId] = FlopResult;
		m_FlopDrawRecordMap[nType] = TmpMap;
	}
}

void CExtFlopDraw::SendFlopRecord( Player* player, int32_t nType )
{
	if ( NULL == player )
	{
		return;
	}

	std::map<int, std::map<int,int>>::iterator it = m_FlopDrawRecordMap.find( nType );
	if ( it == m_FlopDrawRecordMap.end() )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_FLOP_RECORD );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nType );
	packet->writeInt32( (int32_t)it->second.size() );
	for ( std::map<int,int>::iterator itFlop = it->second.begin(); itFlop != it->second.end(); ++itFlop )
	{
		packet->writeInt32( itFlop->first );
		packet->writeInt32( itFlop->second );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CExtFlopDraw::SendFlopOneRecord( Player* player, int32_t nType, int32_t FlopId, int32_t FlopResult )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_FLOP_ONE_RECORD );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nType );
	packet->writeInt32( FlopId );
	packet->writeInt32( FlopResult );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}
