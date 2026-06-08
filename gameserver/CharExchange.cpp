#include "stdafx.h"
#include "CharExchange.h"
#include "Player.h"
#include "GameService.h"
#include "CfgData.h"

using namespace Answer;

// 协议号
#define CM_EXCHANGE_INFO		890
#define CM_EXCHANGE				891
#define SM_EXCHANGE_INFO		0x2EAE

CExtCharExchange::CExtCharExchange()
{
	OnCleanUp();
}

CExtCharExchange::~CExtCharExchange()
{
}

void CExtCharExchange::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_lstExchangeRecords = dbData.m_ExchangeDBData.lstExchange;
}

void CExtCharExchange::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_ExchangeDBData.lstExchange = m_lstExchangeRecords;
}

void CExtCharExchange::OnDaySwitch( int32_t nDiffDays )
{
	if ( !m_lstExchangeRecords.empty() )
	{
		m_lstExchangeRecords.clear();
		for ( int8_t nType = 0; nType <= 4; ++nType )
		{
			sendExchangeInfo( nType );
		}
	}
}

void CExtCharExchange::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_EXCHANGE_INFO );
	procList.push_back( CM_EXCHANGE );
}

int32_t CExtCharExchange::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	// Check function open via record
	if ( !m_pPlayer || m_pPlayer->getRecord( 1169 ) <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( nProcId == CM_EXCHANGE_INFO )
	{
		return onAskExchangeInfo( inPacket );
	}
	if ( nProcId == CM_EXCHANGE )
	{
		return onExchange( inPacket );
	}

	return ERR_OK;
}

int32_t CExtCharExchange::onAskExchangeInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType = inPacket->readInt8();
	if ( (uint8_t)nType > 4 )
	{
		return ERR_INVALID_DATA;
	}

	sendExchangeInfo( nType );
	return ERR_OK;
}

int32_t CExtCharExchange::onExchange( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType = inPacket->readInt8();
	int16_t nIndex = inPacket->readInt16();
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	if ( (uint8_t)nType > 4 )
	{
		return ERR_INVALID_DATA;
	}

	const CfgExchangeTable* pExchangeTable = CFG_DATA.GetExchangeTable();
	const CfgExchange* pCfg = pExchangeTable->GetExchange( nType, nIndex );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nExchangeRecord = getExchangeRecord( nType, nIndex );
	if ( nExchangeRecord >= pCfg->nLimit )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddAndRemoveItem( pCfg->vReward, IACR_ACTIVITY, vSlot, pCfg->vCost, IDCR_BAG_USE ) )
	{
		return ERR_INVALID_DATA;
	}

	addExchangeRecord( nType, nIndex, 1 );
	sendExchangeInfo( nType );

	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nIndex );
	return ERR_OK;
}

void CExtCharExchange::sendExchangeInfo( int8_t nType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_EXCHANGE_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( nType );

	int16_t nCount = 0;
	uint32_t oldOffset = packet->getWOffset();
	packet->writeInt16( 0 ); // placeholder for count

	for ( std::list<ExchangeRecord>::const_iterator iter = m_lstExchangeRecords.begin();
		iter != m_lstExchangeRecords.end(); ++iter )
	{
		if ( iter->nType == nType )
		{
			packet->writeInt16( iter->nIndex );
			packet->writeInt32( iter->nCount );
			++nCount;
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( newOffset );
	packet->setSize( packet->getWOffset() );

	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CExtCharExchange::getExchangeRecord( int8_t nType, int16_t nIndex )
{
	for ( std::list<ExchangeRecord>::const_iterator iter = m_lstExchangeRecords.begin();
		iter != m_lstExchangeRecords.end(); ++iter )
	{
		if ( iter->nType == nType && iter->nIndex == nIndex )
		{
			return iter->nCount;
		}
	}
	return 0;
}

void CExtCharExchange::addExchangeRecord( int8_t nType, int16_t nIndex, int32_t nCount )
{
	for ( std::list<ExchangeRecord>::iterator iter = m_lstExchangeRecords.begin();
		iter != m_lstExchangeRecords.end(); ++iter )
	{
		if ( iter->nType == nType && iter->nIndex == nIndex )
		{
			iter->nCount += nCount;
			return;
		}
	}

	ExchangeRecord record;
	record.nType = nType;
	record.nIndex = nIndex;
	record.nCount = nCount;
	m_lstExchangeRecords.push_back( record );
}
