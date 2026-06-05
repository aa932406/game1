#include <cstring>
#include <cstdint>
#include <sstream>

#include "NationalDayHd.h"
#include "Player.h"
#include "GameService.h"
#include "Bag.h"
#include "Currency.h"
#include "KaiFuHuoDong.h"
#include "DataStruct.h"
// StringUtility from libanswer

using namespace Answer;

CNationalDayHd::CNationalDayHd()
{
	m_pPlayer = NULL;
	OnCleanUp();
}

CNationalDayHd::~CNationalDayHd()
{
}

void CNationalDayHd::OnCleanUp()
{
	m_Level = 0;
	m_Exp = 0;
	m_UnLockReward = 0;
	m_OrdinaryReward = 0;
	m_SeniorReward = 0;
	m_NationalInfo.clear();
}

void CNationalDayHd::OnLoadFromDB( const PlayerDBData* dbData )
{
	if ( NULL == dbData ) return;
	m_Level = dbData->m_NationalDayData.m_Level;
	m_Exp = dbData->m_NationalDayData.m_Exp;
	m_UnLockReward = dbData->m_NationalDayData.m_UnLockReward;
	m_OrdinaryReward = dbData->m_NationalDayData.m_OrdinaryReward;
	m_SeniorReward = dbData->m_NationalDayData.m_SeniorReward;
	paraseNational( dbData->m_NationalDayData.m_NationalInfo );
}

void CNationalDayHd::OnSaveToDB( PlayerDBData* dbData )
{
	if ( NULL == dbData ) return;
	dbData->m_NationalDayData.m_Level = m_Level;
	dbData->m_NationalDayData.m_Exp = m_Exp;
	dbData->m_NationalDayData.m_UnLockReward = m_UnLockReward;
	dbData->m_NationalDayData.m_OrdinaryReward = m_OrdinaryReward;
	dbData->m_NationalDayData.m_SeniorReward = m_SeniorReward;
	dbData->m_NationalDayData.m_NationalInfo = SaveNationalInfo();
}

void CNationalDayHd::paraseNational( const std::string& pNationalInfo )
{
	if ( pNationalInfo.empty() ) return;
	m_NationalInfo.clear();

	// Parse format: "type:param1:param2|type:param1:param2|..."
	std::stringstream ss( pNationalInfo );
	std::string segment;
	while ( std::getline( ss, segment, '|' ) )
	{
		std::stringstream segStream( segment );
		std::string part;
		StringVector parts;
		while ( std::getline( segStream, part, ':' ) )
		{
			parts.push_back( part );
		}
		if ( parts.size() == 3 )
		{
			int32_t nType = atoi( parts[0].c_str() );
			Param2 stu( atoi( parts[1].c_str() ), atoi( parts[2].c_str() ) );
			m_NationalInfo[nType] = stu;
		}
	}
}

std::string CNationalDayHd::SaveNationalInfo()
{
	std::stringstream ss;
	for ( std::map<int32_t, Param2>::iterator it = m_NationalInfo.begin(); it != m_NationalInfo.end(); ++it )
	{
		ss << it->first << ":" << it->second.nParam1 << ":" << it->second.nParam2 << "|";
	}
	return ss.str();
}

bool CNationalDayHd::GetNationalExp( int32_t nType, int32_t nId )
{
	if ( NULL == m_pPlayer ) return false;

	std::map<int32_t, Param2>::iterator it = m_NationalInfo.find( nType );
	if ( it == m_NationalInfo.end() ) return false;

	const NationalDayTaskCfg* pCfg = CFG_DATA.GetNationalDayTaskCfg( nType, nId );
	if ( NULL == pCfg ) return false;

	if ( it->second.nParam1 < pCfg->nNeedValue ) return false;
	if ( it->second.nParam2 >= nId ) return false;

	++it->second.nParam2;
	AddExp( pCfg->nSocre );
	return true;
}

bool CNationalDayHd::UnLockHighReward()
{
	if ( NULL == m_pPlayer ) return false;
	if ( m_UnLockReward > 0 ) return false;

	const NationalDayLevelCfg* pCfg = CFG_DATA.GetNationalDayLevelCfg( 0 );
	if ( NULL == pCfg || pCfg->nUnlockCost <= 0 ) return false;

	if ( !m_pPlayer->DecCurrency( CURRENCY_TYPE::CURRENCY_GOLD, pCfg->nUnlockCost, GCR_NATIONAL_UNLOCK_REWARD, 0 ) )
		return false;

	m_UnLockReward = 1;

	// Broadcast unlock announcement
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
	if ( packet )
	{
		packet->writeInt32( 3023 );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( packet );
	}
	return true;
}

bool CNationalDayHd::GetSeniorReward( int32_t nLevel )
{
	if ( NULL == m_pPlayer ) return false;
	if ( m_Level < nLevel ) return false;

	const NationalDayLevelCfg* pCfg = CFG_DATA.GetNationalDayLevelCfg( nLevel );
	if ( NULL == pCfg ) return false;
	if ( pCfg->vSeniorReward.itemId <= 0 || pCfg->vSeniorReward.itemClass <= 0 ) return false;

	int32_t nNewRecord = m_SeniorReward | (1 << nLevel);
	if ( m_SeniorReward == nNewRecord ) return false;

	if ( !m_pPlayer->GetBag().AddItem( pCfg->vSeniorReward, IACR_ACTIVITY ) )
		return false;

	m_SeniorReward = nNewRecord;

	// Broadcast if configured
	if ( pCfg->nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet )
		{
			packet->writeInt32( pCfg->nGongGaoId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( pCfg->vSeniorReward.itemId );
			packet->writeInt8( pCfg->vSeniorReward.itemClass );
			packet->writeInt32( pCfg->vSeniorReward.itemCount );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}
	return true;
}

bool CNationalDayHd::GetOrdinaryReward( int32_t nLevel )
{
	if ( NULL == m_pPlayer ) return false;
	if ( m_Level < nLevel ) return false;

	const NationalDayLevelCfg* pCfg = CFG_DATA.GetNationalDayLevelCfg( nLevel );
	if ( NULL == pCfg ) return false;
	if ( pCfg->vGeneralReward.empty() ) return false;

	int32_t nNewRecord = m_OrdinaryReward | (1 << nLevel);
	if ( m_OrdinaryReward == nNewRecord ) return false;

	if ( !m_pPlayer->GetBag().AddItem( pCfg->vGeneralReward, IACR_ACTIVITY ) )
		return false;

	m_OrdinaryReward = nNewRecord;
	return true;
}

bool CNationalDayHd::BuyLevel( int32_t BuyLv )
{
	if ( NULL == m_pPlayer ) return false;
	if ( m_Level >= BuyLv ) return false;

	const NationalDayLevelCfg* pCfg = CFG_DATA.GetNationalDayLevelCfg( m_Level );
	const NationalDayLevelCfg* pBuyCfg = CFG_DATA.GetNationalDayLevelCfg( BuyLv );
	if ( NULL == pCfg || NULL == pBuyCfg ) return false;
	if ( pBuyCfg->nBuyCost <= pCfg->nBuyCost || pBuyCfg->nBuyCost <= 0 ) return false;

	int32_t diffCost = pBuyCfg->nBuyCost - pCfg->nBuyCost;
	if ( diffCost <= 0 ) return false;

	if ( !m_pPlayer->DecCurrency( CURRENCY_TYPE::CURRENCY_GOLD, diffCost, GCR_NATIONAL_BUY_LEVEL, 0 ) )
		return false;

	m_Level = BuyLv;
	return true;
}

void CNationalDayHd::AddNationalValue( int32_t nType, int32_t ParamValue1, int32_t ParamValue2 )
{
	if ( NULL == m_pPlayer ) return;

	// Check if activity is active via KaiFuHuoDong (type 16)
	CKaiFuHuoDong& kf = Answer::Singleton<CKaiFuHuoDong>::instance();
	if ( !kf.IsInTime( 16 ) ) return;

	int32_t OldCount = CanGetCount();

	switch ( nType )
	{
	case HHT_LOGIN:
	case HHT_CBT:
	case HHT_CHOU_JIANG:
	case HHT_LUN_HUI_TA:
	case HHT_COST_GOLD:
		m_NationalInfo[nType].nParam1 += ParamValue1;
		break;
	case HHT_RECHARGE:
		{
			const NationalDayTaskCfg* pCfg = CFG_DATA.GetNationalDayTaskCfg( nType, 1 );
			if ( pCfg && pCfg->nParam > ParamValue1 && pCfg->nParam <= ParamValue2 )
			{
				++m_NationalInfo[nType].nParam1;
			}
			break;
		}
	case HHT_KILL_BOSS:
		{
			const NationalDayTaskCfg* pCfg = CFG_DATA.GetNationalDayTaskCfg( nType, 1 );
			if ( pCfg && pCfg->nParam <= ParamValue2 )
			{
				++m_NationalInfo[nType].nParam1;
			}
			break;
		}
	case HHT_YJSK:
		{
			const NationalDayTaskCfg* pCfg = CFG_DATA.GetNationalDayTaskCfg( nType, 1 );
			if ( pCfg && pCfg->nParam == ParamValue2 )
			{
				m_NationalInfo[nType].nParam1 += ParamValue1;
			}
			break;
		}
	default:
		break;
	}

	int32_t NewCount = CanGetCount();
	if ( NewCount != OldCount )
	{
		kf.SendIconState( m_pPlayer );
	}
}

void CNationalDayHd::AddExp( int32_t AddExp )
{
	m_Exp += AddExp;
	CheckLevelUp();
	SendLevelInfo();
}

void CNationalDayHd::CheckLevelUp()
{
	while ( true )
	{
		const NationalDayLevelCfg* pCfg = CFG_DATA.GetNationalDayLevelCfg( m_Level );
		if ( !pCfg || pCfg->nScore <= 0 || m_Exp < pCfg->nScore )
			break;
		++m_Level;
		m_Exp -= pCfg->nScore;
	}
}

void CNationalDayHd::SendLevelInfo()
{
	if ( NULL == m_pPlayer ) return;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2844 );
	if ( packet )
	{
		packet->writeInt32( m_Level );
		packet->writeInt32( m_Exp );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( packet );
	}
}

void CNationalDayHd::PackHdInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet ) return;
	packet->writeInt32( m_Level );
	packet->writeInt32( m_Exp );
	packet->writeInt32( m_UnLockReward );
	packet->writeInt32( m_OrdinaryReward );
	packet->writeInt32( m_SeniorReward );
	packet->writeInt32( (int32_t)m_NationalInfo.size() );
	for ( std::map<int32_t, Param2>::iterator it = m_NationalInfo.begin(); it != m_NationalInfo.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.nParam1 );
		packet->writeInt32( it->second.nParam2 );
	}
}

int32_t CNationalDayHd::CanGetCount()
{
	int32_t nCount = 0;

	// Count task rewards available
	const NationalDayTaskCfgMap* pTaskMap = CFG_DATA.GetNationalDayTaskCfgMap();
	if ( pTaskMap )
	{
		for ( NationalDayTaskCfgMap::const_iterator it = pTaskMap->begin(); it != pTaskMap->end(); ++it )
		{
			const std::pair<int,int>& key = it->first;
			const NationalDayTaskCfg& cfg = it->second;
			std::map<int32_t, Param2>::iterator infoIt = m_NationalInfo.find( key.first );
			if ( infoIt != m_NationalInfo.end() )
			{
				if ( infoIt->second.nParam2 < cfg.nId && infoIt->second.nParam1 >= cfg.nNeedValue )
				{
					++nCount;
				}
			}
		}
	}

	// Count level rewards available
	const NationalDayLevelCfgMap* pLevelMap = CFG_DATA.GetNationalDayLevelCfgMap();
	if ( pLevelMap )
	{
		for ( NationalDayLevelCfgMap::const_iterator it = pLevelMap->begin(); it != pLevelMap->end(); ++it )
		{
			const NationalDayLevelCfg& cfg = it->second;
			if ( cfg.nLevel <= m_Level )
			{
				// Ordinary reward
				int32_t nOrdNew = m_OrdinaryReward | (1 << cfg.nLevel);
				if ( m_OrdinaryReward != nOrdNew && !cfg.vGeneralReward.empty() )
				{
					++nCount;
				}
				// Senior reward
				if ( m_UnLockReward > 0 )
				{
					int32_t nSenNew = m_SeniorReward | (1 << cfg.nLevel);
					if ( m_SeniorReward != nSenNew && cfg.vSeniorReward.itemId > 0 )
					{
						++nCount;
					}
				}
			}
		}
	}

	return nCount;
}

void CNationalDayHd::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_NATIONAL_DAY_INFO );
	procList.push_back( CM_ASK_NATIONAL_DAY_EXP );
	procList.push_back( CM_ASK_NATIONAL_DAY_REWARD );
	procList.push_back( CM_ASK_NATIONAL_DAY_BUY_LEVEL );
}

int32_t CNationalDayHd::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	switch ( nProcId )
	{
	case CM_ASK_NATIONAL_DAY_INFO:	return onAskNationalDayInfo( inPacket );
	case CM_ASK_NATIONAL_DAY_EXP:		return onAskNationalDayExp( inPacket );
	case CM_ASK_NATIONAL_DAY_REWARD:	return onAskNationalDayReward( inPacket );
	case CM_ASK_NATIONAL_DAY_BUY_LEVEL:	return onAskNationalDayBuyLevel( inPacket );
	default: return ERR_INVALID_DATA;
	}
}

int32_t CNationalDayHd::onAskNationalDayInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket ) return ERR_INVALID_DATA;
	// Send full HD info
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NATIONAL_DAY_HD_INFO );
	if ( packet )
	{
		PackHdInfo( packet );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( packet );
	}
	return 0;
}

int32_t CNationalDayHd::onAskNationalDayExp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket ) return ERR_INVALID_DATA;
	int32_t nType = inPacket->readInt32();
	int32_t nId = inPacket->readInt32();
	GetNationalExp( nType, nId );
	return 0;
}

int32_t CNationalDayHd::onAskNationalDayReward( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket ) return ERR_INVALID_DATA;
	int32_t nType = inPacket->readInt32();
	int32_t nLevel = inPacket->readInt32();
	switch ( nType )
	{
	case 1: // Ordinary reward
		GetOrdinaryReward( nLevel ); break;
	case 2: // Senior reward
		GetSeniorReward( nLevel ); break;
	case 3: // Unlock senior reward
		UnLockHighReward(); break;
	default: break;
	}
	return 0;
}

int32_t CNationalDayHd::onAskNationalDayBuyLevel( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket ) return ERR_INVALID_DATA;
	int32_t nLevel = inPacket->readInt32();
	BuyLevel( nLevel );
	return 0;
}
