#include "RankMirror.h"
#include "GameService.h"

using namespace Answer;

CRankMirror::CRankMirror()
{
	m_nLastRefreshTime = 0;
	memset( m_vBattleRank, 0, sizeof(m_vBattleRank) );
	memset( m_vLevelRank, 0, sizeof(m_vLevelRank) );
	memset( m_vWeiWangRank, 0, sizeof(m_vWeiWangRank) );
}

CRankMirror::~CRankMirror()
{
}

int32_t CRankMirror::GetBattleIndex( CharId_t nCharId )
{
	MutexGuard lock( m_lock );
	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		return iter->second.nBattleIndex;
	}
	return 0;
}

int32_t CRankMirror::GetLevelIndex( CharId_t nCharId )
{
	MutexGuard lock( m_lock );
	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		return iter->second.nLevelIndex;
	}
	return 0;
}

bool CRankMirror::IsJobBattleFirst( CharId_t nCharId )
{
	MutexGuard lock( m_lock );
	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		return iter->second.nJobBattleFirst > 0;
	}
	return false;
}

int32_t CRankMirror::GetWeiWangIndex( CharId_t nCharId )
{
	MutexGuard lock( m_lock );
	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		return iter->second.nWeiWangIndex;
	}
	return 0;
}

void CRankMirror::OnSocialUpdateRank( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	int8_t nType = inPacket->readInt8();
	if ( nType == 2 )
	{
		// 等级排名更新
		resetLevelRank();
		int16_t nSize = inPacket->readInt16();
		for ( int16_t i = 0; i < nSize; ++i )
		{
			CharId_t nCharId = inPacket->readInt64();
			int32_t nIndex = inPacket->readInt8();
			setLevelRank( nCharId, nIndex );
		}
	}
	else if ( nType == 4 )
	{
		// 威望排名更新
		resetWeiWangRank();
		int16_t nSize = inPacket->readInt16();
		for ( int16_t i = 0; i < nSize; ++i )
		{
			CharId_t nCharId = inPacket->readInt64();
			int32_t nIndex = inPacket->readInt8();
			setWeiWangRank( nCharId, nIndex );
		}
	}
	else if ( nType == 1 )
	{
		// 战力排名更新
		m_nLastRefreshTime = inPacket->readInt32();
		resetBattleRank();
		int16_t nSize = inPacket->readInt16();
		for ( int16_t i = 0; i < nSize; ++i )
		{
			CharId_t nCharId = inPacket->readInt64();
			int32_t nIndex = inPacket->readInt8();
			int8_t nJobFrist = inPacket->readInt8();
			setBattleRank( nCharId, nIndex, nJobFrist );
		}
	}
}

void CRankMirror::resetBattleRank()
{
	MutexGuard lock( m_lock );

	memset( m_vBattleRank, 0, sizeof(m_vBattleRank) );

	for ( PlayerRankMap::iterator iter = m_mPlayerRank.begin(); iter != m_mPlayerRank.end(); ++iter )
	{
		PlayerRankData& data = iter->second;
		data.nBattleIndex = 0;
		if ( data.nJobBattleFirst > 0 )
		{
			onRemoveTitle( data.nCharId, 3 );
			data.nJobBattleFirst = 0;
		}
	}
}

void CRankMirror::resetLevelRank()
{
	MutexGuard lock( m_lock );

	memset( m_vLevelRank, 0, sizeof(m_vLevelRank) );

	for ( PlayerRankMap::iterator iter = m_mPlayerRank.begin(); iter != m_mPlayerRank.end(); ++iter )
	{
		iter->second.nLevelIndex = 0;
	}
}

void CRankMirror::resetWeiWangRank()
{
	MutexGuard lock( m_lock );

	memset( m_vWeiWangRank, 0, sizeof(m_vWeiWangRank) );

	for ( PlayerRankMap::iterator iter = m_mPlayerRank.begin(); iter != m_mPlayerRank.end(); ++iter )
	{
		iter->second.nWeiWangIndex = 0;
	}
}

void CRankMirror::setBattleRank( CharId_t nCharId, int32_t nIndex, int8_t nJobFrist )
{
	MutexGuard lock( m_lock );

	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		iter->second.nBattleIndex = nIndex;
		iter->second.nJobBattleFirst = nJobFrist;
	}
	else
	{
		PlayerRankData data;
		data.nCharId = nCharId;
		data.nBattleIndex = nIndex;
		data.nJobBattleFirst = nJobFrist;
		m_mPlayerRank.insert( std::make_pair( nCharId, data ) );
	}

	if ( nJobFrist > 0 )
	{
		onCheckTitle( nCharId, 3, nJobFrist );
	}

	if ( nIndex > 0 && nIndex <= 100 )
	{
		m_vBattleRank[nIndex] = nCharId;
	}
}

void CRankMirror::setLevelRank( CharId_t nCharId, int32_t nIndex )
{
	MutexGuard lock( m_lock );

	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		iter->second.nLevelIndex = nIndex;
	}
	else
	{
		PlayerRankData data;
		data.nCharId = nCharId;
		data.nLevelIndex = nIndex;
		m_mPlayerRank.insert( std::make_pair( nCharId, data ) );
	}

	if ( nIndex > 0 && nIndex <= 100 )
	{
		m_vLevelRank[nIndex] = nCharId;
	}
}

void CRankMirror::setWeiWangRank( CharId_t nCharId, int32_t nIndex )
{
	MutexGuard lock( m_lock );

	PlayerRankMap::iterator iter = m_mPlayerRank.find( nCharId );
	if ( iter != m_mPlayerRank.end() )
	{
		iter->second.nWeiWangIndex = nIndex;
	}
	else
	{
		PlayerRankData data;
		data.nCharId = nCharId;
		data.nWeiWangIndex = nIndex;
		m_mPlayerRank.insert( std::make_pair( nCharId, data ) );
	}

	if ( nIndex > 0 && nIndex <= 100 )
	{
		m_vWeiWangRank[nIndex] = nCharId;
	}
}

// ========== 标题/称号 ==========
// 通过 GameService 查找在线玩家并授予/移除称号
void CRankMirror::onCheckTitle( CharId_t nCharId, int32_t nTitleId, int8_t nParam )
{
	GAME_SERVICE.onCheckTitle( nCharId, (int8_t)nTitleId, nParam );
}

void CRankMirror::onRemoveTitle( CharId_t nCharId, int32_t nTitleId )
{
	GAME_SERVICE.onRemoveTitle( nCharId, (int8_t)nTitleId );
}
