
#include "stdafx.h"
#include "Currency.h"
#include "GameService.h"
#include "DBService.h"
#include <sstream>

using namespace Answer;

CExtCurrency::CExtCurrency()
{
	OnCleanUp();
}

CExtCurrency::~CExtCurrency()
{

}

void CExtCurrency::OnCleanUp()
{
	m_bNeedSync = false;
	bzero( m_aCurrency, sizeof( m_aCurrency ) );
	bzero( m_aUpdateSign, sizeof( m_aUpdateSign ) );
}

void CExtCurrency::OnUpdate( int64_t curTick )
{
	SynCurrency();
}

void CExtCurrency::SynCurrency()
{
	if ( m_bNeedSync )
	{
		m_bNeedSync = false;
		SendCurrencyInfo( false );
	}
}

void CExtCurrency::OnLoadFromDB( const PlayerDBData& dbData )
{
	StringVector vStr = StringUtility::split( dbData.m_CurrencyData.m_str, "|" );
	int32_t isize = vStr.size();
	for ( int32_t i = 0; i < isize; ++i )
	{
		StringVector tv = StringUtility::split( vStr[i], ":" );
		if ( tv.size() != 2 )
		{
			continue;
		}
		int32_t nType = atoi( tv[0].c_str() );
		if ( !checkCurrencyType( static_cast<CURRENCY_TYPE>(nType) ) )
		{
			continue;
		}
		m_aCurrency[nType] = atoi( tv[1].c_str() );
	}
}

void CExtCurrency::OnSaveToDB( PlayerDBData& dbData )
{
	std::stringstream ss;
	for ( int32_t i = 0; i < CURRENCY_TYPE_COUNT; ++i )
	{
		if ( m_aCurrency[i] > 0 )
		{
			ss << "|" << i << ":" << m_aCurrency[i];
		}
	}
	dbData.m_CurrencyData.m_str = ss.str();
}

void CExtCurrency::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( IM_SOCIAL_GAME_ADD_CURRENCY );
	procList.push_back( CM_SYNC_GOLD );
	procList.push_back( CM_CURRENCY_DUIHUAN );
}

int32_t CExtCurrency::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case IM_SOCIAL_GAME_ADD_CURRENCY:	return onSocialAddCurrency( inPacket );
	case CM_SYNC_GOLD:					return syncGold( inPacket );
	case CM_CURRENCY_DUIHUAN:			return OnCurrencyDuiHuan( inPacket );
	default:	break;
	}
	return ERR_OK;
}

int32_t CExtCurrency::onSocialAddCurrency( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	int8_t nCurrency = inPacket->readInt8();
	int32_t nCount = inPacket->readInt32();
	if ( nCount >= 0 )
	{
		AddCurrency( static_cast<CURRENCY_TYPE>( nCurrency ), nCount );
	}
	else
	{
		DecCurrency( static_cast<CURRENCY_TYPE>( nCurrency ), -1*nCount );
	}
	return ERR_OK;
}

int64_t CExtCurrency::GetMoneyBindAndNoBind()
{
	int64_t Money		= GetCurrency( CURRENCY_MONEY );
	int64_t BindMoney	= GetCurrency( CURRENCY_BIND_MONEY );
	return Money + BindMoney;
}

bool CExtCurrency::DecMoneyAndNoBind( int64_t nVal, int32_t opWay, int64_t nParam )
{
	int64_t BindMoney	= GetCurrency( CURRENCY_BIND_MONEY );
	if ( BindMoney >= nVal )
	{
		return DecCurrency( CURRENCY_BIND_MONEY, nVal, opWay, nParam);
	}
	
	if ( BindMoney > 0 )
	{
		if ( !DecCurrency( CURRENCY_BIND_MONEY, BindMoney, opWay, nParam) )
		{
			return false;
		}
		if ( !DecCurrency( CURRENCY_MONEY, nVal - BindMoney, opWay, nParam)  )
		{
			return false;
		}
		return true;
	}

	if ( BindMoney <= 0 )
	{
		if ( !DecCurrency( CURRENCY_MONEY, nVal, opWay, nParam)  )
		{
			return false;
		}
		return true;
	}
	return false;
}

int64_t CExtCurrency::GetCurrency( CURRENCY_TYPE const nType ) const
{
	if ( !checkCurrencyType( nType ) )
	{
		return 0;
	}

	return m_aCurrency[nType];
}

bool CExtCurrency::AddCurrency( CURRENCY_TYPE const nType, int64_t nVal, int32_t opWay, int64_t nParam )
{
	if ( nVal <= 0 )
	{
		LOG_ERROR( "CExtCurrency::AddCurrency() wrong value!!! nType=%d, nVal=%d, opWay=%d, nParam=%lld\n", nType, nVal, opWay, nParam );
		return false;
	}

	int64_t nMaxAddVal = getMaxVal( nType ) - GetCurrency( nType );
	if ( nVal > nMaxAddVal )
	{
		nVal = nMaxAddVal;
	}

	if ( nVal <= 0 )
	{
		return true;
	}
	switch( nType )
	{
	case CURRENCY_MONEY:
		{
			double  bnfRatio = 1.0;
			if ( nParam != 9527 )	//gm����
			{
				bnfRatio = m_pPlayer->benefitRatio();	
			}
			nVal = static_cast<int32_t>( nVal * bnfRatio );
			m_pPlayer->sendGainInfo( GT_MONEY, nVal, m_pPlayer->benefitType() );
			if ( nVal <= 0 )
			{
				return true;
			}
			break;
		}
	case CURRENCY_GOLD:
		{
			m_pPlayer->sendGainInfo( GT_GOLD, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_CASH:
		{
			m_pPlayer->sendGainInfo( GT_CASH, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_CHOUJINAG:
		{
			m_pPlayer->sendGainInfo( GT_CHOU_JINAG, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_BOSS:
		{
			m_pPlayer->sendGainInfo( GT_BOSS_SCORE, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_BIND_MONEY:
		{
			m_pPlayer->sendGainInfo( GT_BIND_MONEY, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_HONOR:
		{
			m_pPlayer->sendGainInfo( GT_HONOR, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_AC_SOCRE:
		{
			m_pPlayer->sendGainInfo( GT_AC_SOCRE, nVal, m_pPlayer->benefitType() );
			break;
		}
	default:
		break;
	}
	return changeCurrency( nType, nVal, opWay, nParam );
}

bool CExtCurrency::DecCurrency( CURRENCY_TYPE const nType, int64_t nVal, int32_t opWay, int64_t nParam )
{
	if (  NULL == m_pPlayer )
	{
		return false;
	}
	if ( nVal <= 0 )
	{
		LOG_ERROR( "CExtCurrency::AddCurrency() wrong value!!! nType=%d, nVal=%d, opWay=%d, nParam=%lld\n", nType, nVal, opWay, nParam );
		return false;
	}

	if (  GetCurrency( nType ) < nVal )
	{
		return false;
	}
	nVal *= -1;
	switch( nType )
	{
	case CURRENCY_MONEY:
		{
			m_pPlayer->sendGainInfo( GT_MONEY, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_GOLD:
		{
			m_pPlayer->sendGainInfo( GT_GOLD, nVal, m_pPlayer->benefitType() );
			m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_COST_GOLD,  -1 * static_cast<int32_t>(nVal) );
			break;
		}
	case CURRENCY_CASH:
		{
			m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_COST_CASH, -1 *  static_cast<int32_t>( nVal ) );
			m_pPlayer->sendGainInfo( GT_CASH, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_CHOUJINAG:
		{
			m_pPlayer->sendGainInfo( GT_CHOU_JINAG, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_BOSS:
		{
			m_pPlayer->sendGainInfo( GT_BOSS_SCORE, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_BIND_MONEY:
		{
			m_pPlayer->sendGainInfo( GT_BIND_MONEY, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_HONOR:
		{
			m_pPlayer->sendGainInfo( GT_HONOR, nVal, m_pPlayer->benefitType() );
			break;
		}
	case CURRENCY_AC_SOCRE:
		{
			m_pPlayer->sendGainInfo( GT_AC_SOCRE, nVal, m_pPlayer->benefitType() );
			break;
		}
	default:
		break;
	}
	
	if ( nType == CURRENCY_GOLD && opWay != GCR_TRADE_CONST_GOLD && opWay != GCR_AUCTION_BUY && opWay != GCR_AUCTION_SELL )
	{																	
		m_pPlayer->GetPlayerVip().AddVipExp( -1* static_cast<int32_t>(nVal) );
	}
	return changeCurrency( nType, nVal, opWay, nParam );
}

bool CExtCurrency::changeCurrency( CURRENCY_TYPE const nType, int64_t nVal, int32_t opWay, int64_t nParam )
{
	if( NULL == m_pPlayer || 0 == nVal )
	{
		return false;
	}
	
	if ( !checkCurrencyType( nType ) )
	{
		return false;
	}
	m_aCurrency[nType] += nVal;
	m_aUpdateSign[nType] = true;
	m_bNeedSync = true;

	DB_SERVICE.logCurrency( m_pPlayer->getCid(), m_pPlayer->getName(), nType, opWay, static_cast<int32_t>(nVal), nParam, m_pPlayer->getNow() );
	return true;
}

void CExtCurrency::SendCurrencyInfo( bool bAll )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_CURRENCY_INFO );
	if ( NULL == packet )
	{
		return;
	}

	uint32_t oldOffset = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( nCount );
	for ( int8_t i = 0; i < CURRENCY_TYPE_COUNT; ++i )
	{
		if ( bAll || m_aUpdateSign[i] )
		{
			m_aUpdateSign[i] = false;
			packet->writeInt8( i );
			packet->writeInt64( m_aCurrency[i] );	
			++nCount;
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( newOffset );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

bool CExtCurrency::checkCurrencyType( CURRENCY_TYPE const nType ) const
{
	if ( nType < 0 || nType >= CURRENCY_TYPE_COUNT )
	{
		return false;
	}
	return true;
}

int32_t CExtCurrency::syncGold( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return 2;
	}
	int32_t Gold = inPacket->readInt32();
	// syncGold removed: m_pPlayer->syncGold( Gold );
	return 0;
}

int32_t CExtCurrency::OnCurrencyDuiHuan( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nDouble = 0;
	if ( inPacket->getSize() > 0 )
	{
		nDouble = inPacket->readInt32();
	}

	const CfgCurrencyDuiHuan* pCfg = CFG_DATA.GetCurrencyDuiHuan( m_pPlayer->getLevel() );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCfg->m_nMoShi <= 0 || pCfg->m_nShengYaoBi <= 0 || pCfg->m_nJinBi <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = m_pPlayer->getRecord( PR_CURRENCY_DUIHUAN_COUNT );
	if ( nCount >= pCfg->m_nDailyLimit )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nRate = 1;
	if ( nDouble > 0 )
	{
		int32_t nGoldCost = 0;
		if ( nGoldCost <= 0 || m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nGoldCost )
		{
			return ERR_INVALID_DATA;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nGoldCost, GCR_CURRENCY_DUIHUAN ) )
		{
			return ERR_INVALID_DATA;
		}
		nRate = 2;
	}

	if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfg->m_nMoShi, MCR_CURRENCY_DUIHUAN ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->AddCurrency( CURRENCY_VIGOUR, nRate * pCfg->m_nShengYaoBi, GCR_CURRENCY_DUIHUAN ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( PR_CURRENCY_DUIHUAN_COUNT, nCount + 1 );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_CURRENCY_DUIHUAN );
	return 0;
}

int64_t CExtCurrency::getMaxVal( CURRENCY_TYPE const nType ) const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	switch ( nType )
	{
	case CURRENCY_VIGOUR:
		{
			int32_t nLevel = m_pPlayer->getLevel();
			if ( nLevel < 90 )
			{
				return 18000;
			}
			else if ( nLevel < 120 )
			{
				return 24000;
			}
			else if ( nLevel < 133 )
			{
				return 30000;
			}
			else if ( nLevel < 136 )
			{
				return 36000;
			}
			else if ( nLevel < 139 )
			{
				return 42000;
			}
			else
			{
				return 50000;
			}
		}
		break;
	default:
		break;
	}
	return 9999999999999;
}
