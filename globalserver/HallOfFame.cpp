#include "stdafx.h"

#include "HallOfFame.h"
#include "SocialService.h"
#include "CfgData.h"
#include "PlayerManager.h"

using namespace Answer;


#define	FRONT_SIZE				7			// 挑战界面前7人
#define BACK_SIZE				2			// 挑战界面后2人
#define BROADCAST_INDEX			10			// 挑战前10成功发公告


/*
总生命力 = 战斗力*500
伤害 = 战斗力*100
攻击伤害浮动 ±百分之50
攻擂和守擂都有5%的闪避率
战斗力比值(X) = (攻击方战斗力 - 防御方战斗力) / 攻击方战斗力
攻擂方最终伤害 = 伤害 * (战斗力比值  + 105%) * rand(-50% , 50%)
守擂方最终伤害 = 伤害 * (战斗力比值  + 100%) * rand(-50% , 50%)
*/

FameFighter::FameFighter( int32_t battle, int32_t tarBattle, bool bAtker )
:nBattle( battle )
{
	nHP = nBattle * 500;
	nHPMax = nHP;

	float rate = static_cast<float>( battle - tarBattle ) / battle;
	if ( rate < -0.9f )
	{
		rate = -0.9f;
	}
	float atk = nBattle * 100 * ( rate + ( bAtker ? 1.05f : 1.00f ) );
	nAtkMin = static_cast<int32_t>( atk * 0.5f );
	nAtkMax = static_cast<int32_t>( atk * 1.5f );
}

FameFighter::~FameFighter()
{

}

bool FameFighter::Hurt( int32_t nDamage )
{
	nHP -= nDamage;
	if ( nHP <= 0 )
	{
		return true;
	}
	return false;
}

int32_t FameFighter::Attack()
{
	return RANDOM.generate( nAtkMin, nAtkMax );
}

int32_t FameFighter::GetHP()
{
	return nHP;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FameBattle::FameBattle( int32_t battle, int32_t tarBattle )
:m_atker( battle, tarBattle, true ), m_defer( tarBattle, battle, false )
{

}

FameBattle::~FameBattle()
{

}

bool FameBattle::isMiss()
{
	return RANDOM.generate( 0, 100 ) < 5;
}

bool FameBattle::Fight( Answer::NetPacket* packet, int8_t bForce )
{
	bool bWin = false;
	int32_t nCount = 0;
	uint32_t oldOffset = packet->getWOffset();

	packet->writeInt8( 0 );
	packet->writeInt32( nCount );
	while( 1 )
	{
		if ( bForce != FBF_WIN && isMiss() )
		{
			packet->writeInt8( SAS_PARRY );
			packet->writeInt32( 0 );
			++nCount;
		}
		else
		{
			int32_t nDmg = m_atker.Attack();
			if ( bForce == FBF_FAIL &&  m_defer.GetHP() <= nDmg )
			{
				packet->writeInt8( SAS_PARRY );
				packet->writeInt32( 0 );
				++nCount;
			}
			else
			{
				packet->writeInt8( SAS_NORMAL );
				packet->writeInt32( -1*nDmg );
				++nCount;
				if ( m_defer.Hurt( nDmg ) )
				{
					bWin = true;
					break;
				}
			}
		}

		if ( bForce != FBF_FAIL && isMiss() )
		{
			packet->writeInt8( SAS_PARRY );
			packet->writeInt32( 0 );
			++nCount;
		}
		else
		{
			int32_t nDmg = m_defer.Attack();
			if ( bForce == FBF_WIN &&  m_atker.GetHP() <= nDmg )
			{
				packet->writeInt8( SAS_PARRY );
				packet->writeInt32( 0 );
				++nCount;
			}
			else
			{
				packet->writeInt8( SAS_NORMAL );
				packet->writeInt32( -1*nDmg );
				++nCount;
				if ( m_atker.Hurt( nDmg ) )
				{
					bWin = false;
					break;
				}
			}
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt8( bWin ? 1 : 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( newOffset );

	return bWin;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CFamePlayer::CFamePlayer()
:nCharId(0),nIndex(0),nLastIndex(0),nReward(0)
{
}

CFamePlayer::~CFamePlayer()
{
}

void CFamePlayer::ResetFighters()
{
	vFighters.clear();
	if ( nIndex == 0 )
	{
		vFighters.push_back( 2001 );
		vFighters.push_back( 2050 );
		vFighters.push_back( 2089 );
		vFighters.push_back( 2134 );
		vFighters.push_back( 2179 );
		vFighters.push_back( 2224 );
		vFighters.push_back( 2269 );
		vFighters.push_back( 2314 );
		vFighters.push_back( 2359 );
		vFighters.push_back( 2404 );
	}
	else if ( nIndex > HALL_OF_FAME_RANK_SIZE )
	{
		vFighters.push_back( RANDOM.generate( 1400, 1460 ) );
		vFighters.push_back( RANDOM.generate( 1461, 1520 ) );
		vFighters.push_back( RANDOM.generate( 1521, 1580 ) );
		vFighters.push_back( RANDOM.generate( 1581, 1640 ) );
		vFighters.push_back( RANDOM.generate( 1641, 1700 ) );
		vFighters.push_back( RANDOM.generate( 1701, 1760 ) );
		vFighters.push_back( RANDOM.generate( 1761, 1820 ) );
		vFighters.push_back( RANDOM.generate( 1820, 1880 ) );
		vFighters.push_back( RANDOM.generate( 1881, 1940 ) );
		vFighters.push_back( RANDOM.generate( 1941, 2000 ) );
	}
	else
	{
		const HallOfFameIndex* pIndex = CFG_DATA.GetHallOfFameTable().GetIndex( nIndex );
		if ( pIndex != NULL )
		{
			int32_t nFrontSize = FRONT_SIZE;
			int32_t nBackSize = BACK_SIZE;
			if ( nIndex <= FRONT_SIZE )
			{
				nFrontSize = nIndex-1;
				nBackSize = FRONT_SIZE + BACK_SIZE - nFrontSize;
			}
			else if ( nIndex > HALL_OF_FAME_RANK_SIZE - BACK_SIZE )
			{
				nBackSize = HALL_OF_FAME_RANK_SIZE - nIndex;
				nFrontSize = FRONT_SIZE + BACK_SIZE - nBackSize;
			}

			{
				int32_t frontIndex = nIndex;
				for ( int32_t i = 0; i < nFrontSize; ++i )
				{
					frontIndex -= RANDOM.generate( pIndex->nFrontMin, pIndex->nFrontMax );
					vFighters.push_front( frontIndex );
				}
			}

			if ( nIndex + nBackSize*pIndex->nBackMax > HALL_OF_FAME_RANK_SIZE )
			{
				int32_t dis = 1;
				if ( nBackSize > 0 )
				{
					dis = ( HALL_OF_FAME_RANK_SIZE - nIndex ) / nBackSize;
				}
				for ( int32_t i = 0; i < nBackSize; ++i )
				{
					vFighters.push_back( RANDOM.generate( nIndex + 1 + dis*i, nIndex + dis*(i+1) ) );
				}
			}
			else
			{
				int32_t backIndex = nIndex;
				for ( int32_t j = 0; j < nBackSize; ++j )
				{
					backIndex += RANDOM.generate( pIndex->nBackMin, pIndex->nBackMax );
					vFighters.push_back( backIndex );
				}
			}
		}
	}
}

bool CFamePlayer::CanFight( int32_t nIndex ) const
{
	Int32List::const_iterator iter = vFighters.begin();
	Int32List::const_iterator eiter = vFighters.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == nIndex )
		{
			return true;
		}
	}
	return false;
}

void CFamePlayer::ResetLastIndex()
{
	nLastIndex = nIndex;
	nReward = 0;
}

void CFamePlayer::SignReward( bool bSign )
{
	nReward = bSign ? 1 : 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CHallOfFameManager::CHallOfFameManager()
{

}

CHallOfFameManager::~CHallOfFameManager()
{

}

void CHallOfFameManager::Init()
{
	loadRank();
	loadChars();
}

void CHallOfFameManager::loadRank()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_hall_of_fame` WHERE `cid`>0 OR `last_cid`>0" );
	MySqlQuery result = db.query(szSQL);

	while ( !result.eof() )
	{
		int32_t index		= result.getIntValue("fame_index");;
		CharId_t cid		= result.getInt64Value("cid");
		CharId_t lastcid	= result.getInt64Value( "last_cid" );
		int8_t reward		= result.getIntValue("reward");
		if ( cid > 0 )
		{
			FamePlayerMap::iterator findIter = m_mPlayer.find( cid );
			if ( findIter != m_mPlayer.end() )
			{
				findIter->second.nIndex = index;
				findIter->second.ResetFighters();
				m_vPlayer[index] = &( findIter->second );
			}
			else
			{
				CFamePlayer player;
				player.nCharId	= cid;
				player.nIndex	= index;
				player.ResetFighters();

				FamePlayerMap::iterator iter = m_mPlayer.insert( FamePlayerMap::value_type( player.nCharId, player ) ).first;
				if ( iter != m_mPlayer.end() )
				{
					m_vPlayer[index] = &( iter->second );
				}
			}
		}

		if ( lastcid > 0 )
		{
			FamePlayerMap::iterator findIter = m_mPlayer.find( lastcid );
			if ( findIter != m_mPlayer.end() )
			{
				findIter->second.nLastIndex = index;
				findIter->second.nReward	= reward;
			}
			else
			{
				CFamePlayer player;
				player.nCharId		= lastcid;
				player.nLastIndex	= index;
				player.nReward		= reward;
				player.ResetFighters();

				m_mPlayer.insert( FamePlayerMap::value_type( player.nCharId, player ) );
			}
		}

		result.nextRow();
	}
}

void CHallOfFameManager::loadChars()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_char_operate_limit` WHERE `LimitId`=2015" );
	MySqlQuery result = db.query(szSQL);

	while ( !result.eof() )
	{
		CharId_t nCharId = result.getInt64Value("cid");
		FamePlayerMap::iterator iter = m_mPlayer.find( nCharId );
		if ( iter == m_mPlayer.end() )
		{
			CFamePlayer player;
			player.nCharId	= nCharId;
			player.nIndex	= HALL_OF_FAME_RANK_SIZE + 1;
			player.ResetFighters();

			m_mPlayer.insert( FamePlayerMap::value_type( player.nCharId, player ) );
		}

		result.nextRow();
	}
}

void CHallOfFameManager::OnNewMinuteCome( int32_t minute )
{
	if ( minute == HALL_OF_FAME_REWARD_TIME )
	{
		broadcastTops();
		sendRankReward();
		saveLastIndex();
	}
}

void CHallOfFameManager::SendIconState( SocialPlayer* player )
{
	if ( NULL == player )
	{
		return;
	}

	FamePlayerMap::iterator iter = m_mPlayer.find( player->getCid() );
	if ( iter == m_mPlayer.end() )
	{
		return;
	}

	if ( iter->second.nLastIndex > 0 && iter->second.nLastIndex <= HALL_OF_FAME_RANK_SIZE && iter->second.nReward == 0 )
	{
		player->SendGameHallOfFameRankRewardInfo( iter->second.nLastIndex, iter->second.nReward );
	}
}

int32_t	CHallOfFameManager::OnRequestInfo( SocialPlayer* player, Answer::NetPacket* inPacket )
{
	if ( NULL == player || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t	nFightTimes = inPacket->readInt32();
	int32_t	nBuyTimes	= inPacket->readInt32();
	int32_t	nCDTime		= inPacket->readInt32();

	FamePlayerMap::iterator findIter = m_mPlayer.find( player->getCid() );
	if ( findIter == m_mPlayer.end() )
	{
		CFamePlayer newPlayer;
		newPlayer.nCharId = player->getCid();
		newPlayer.nIndex = 0;
		newPlayer.ResetFighters();
		findIter = m_mPlayer.insert( FamePlayerMap::value_type( player->getCid(), newPlayer ) ).first;
	}

	if ( findIter == m_mPlayer.end() )
	{
		return ERR_INVALID_DATA;
	}

	CFamePlayer& famePlayer = findIter->second;

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( NULL == packet )
	{
		return ERR_INVALID_DATA;
	}

	packet->writeInt32( famePlayer.nIndex );
	packet->writeInt32( nFightTimes );
	packet->writeInt32( nBuyTimes );
	packet->writeInt32( nCDTime );
	packet->writeInt32( famePlayer.nLastIndex );
	packet->writeInt8( famePlayer.nReward );
	packet->writeInt32( famePlayer.vFighters.size() );
	for ( Int32List::iterator iter = famePlayer.vFighters.begin(); iter != famePlayer.vFighters.end(); ++iter )
	{
		int32_t nIndex = *iter;
		packet->writeInt32( nIndex );
		if ( nIndex > 0 && nIndex <= HALL_OF_FAME_RANK_SIZE && m_vPlayer[nIndex] != NULL )
		{
			PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_vPlayer[nIndex]->nCharId );
			if ( pInfo != NULL )
			{
				packet->writeInt8( 1 );
				packet->writeInt64( pInfo->nCharId );
				packet->writeUTF8( pInfo->strName );
				packet->writeInt32( pInfo->nBattle );
				packet->writeInt8( pInfo->nJob );
				packet->writeInt8( pInfo->nSex );
				packet->writeInt32( pInfo->nCloth );
				packet->writeInt32( pInfo->nWeapon );
			}
			else
			{
				packet->writeInt8( 0 );
			}
		}
		else
		{
			packet->writeInt8( 0 );
		}
	}
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_HALL_OF_FAME_INFO );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( player->getGateIndex(), packet );
	return ERR_OK;
}

int32_t CHallOfFameManager::OnFight( SocialPlayer* player, Answer::NetPacket* inPacket )
{
	if ( NULL == player || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nIndex = inPacket->readInt32();
	if ( nIndex <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	FamePlayerMap::iterator findIter = m_mPlayer.find( player->getCid() );
	if ( findIter == m_mPlayer.end() )
	{
		return ERR_INVALID_DATA;
	}

	CFamePlayer& famePlayer = findIter->second;
	if ( !famePlayer.CanFight( nIndex ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( nIndex > HALL_OF_FAME_RANK_SIZE )
	{
		if ( famePlayer.nIndex == 0 )
		{
			return firstFight( player, famePlayer, nIndex );
		}
		else
		{
			return ERR_INVALID_DATA;
		}
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( NULL == packet )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBattle = 0;
	if ( m_vPlayer[nIndex] != NULL )
	{
		PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_vPlayer[nIndex]->nCharId );
		if ( pInfo != NULL )
		{
			packet->writeInt8( 1 );
			packet->writeInt64( pInfo->nCharId );
			packet->writeUTF8( pInfo->strName );
			packet->writeInt32( pInfo->nBattle );
			packet->writeInt8( pInfo->nJob );
			packet->writeInt8( pInfo->nSex );
			packet->writeInt32( pInfo->nCloth );
			packet->writeInt32( pInfo->nWeapon );
			packet->writeInt32( pInfo->nLevel );
			nBattle = pInfo->nBattle;
		}
		else
		{
			packet->writeInt8( 0 );
			packet->writeInt32( nIndex );
			nBattle = CFG_DATA.GetHallOfFameTable().GetRobot( nIndex );
		}
	}
	else
	{
		packet->writeInt8( 0 );
		packet->writeInt32( nIndex );
		nBattle = CFG_DATA.GetHallOfFameTable().GetRobot( nIndex );
	}

	bool bWin = false;
	FameBattle battle( player->GetBattle(), nBattle );
	if ( battle.Fight( packet ) )
	{
		int32_t nCurIndex = famePlayer.nIndex;
		if ( nCurIndex == 0 || nIndex < nCurIndex )
		{
			CharId_t tarCid = 0;
			CFamePlayer* pFamePlayer = m_vPlayer[nIndex];
			if ( m_vPlayer[nIndex] != NULL )
			{
				tarCid = pFamePlayer->nCharId;
				pFamePlayer->nIndex = nCurIndex;
				pFamePlayer->ResetFighters();
			}

			famePlayer.nIndex = nIndex;
			famePlayer.ResetFighters();
			m_vPlayer[nIndex] = &famePlayer;
			saveIndex( nIndex );

			if ( nCurIndex > 0 && nCurIndex <= HALL_OF_FAME_RANK_SIZE )
			{
				m_vPlayer[nCurIndex] = pFamePlayer;
				saveIndex( nCurIndex );
			}

			if ( nIndex <= BROADCAST_INDEX )
			{
				std::string defer = "";
				if ( tarCid > 0 )
				{
					PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( tarCid );
					if ( pInfo != NULL )
					{
						defer = pInfo->strName;
						
					}
				}
				broadcastFight( player->getCid(), player->getName(), defer, nCurIndex, nIndex );
			}
		}
		
		bWin = true;
	}
	else
	{
		bWin = false;
	}

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_HALL_OF_FAME_BATTLE );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( player->getGateIndex(), packet );

	player->SendGameFightResult( bWin );
	return ERR_OK;
}


int32_t CHallOfFameManager::firstFight( SocialPlayer* player, CFamePlayer& famePlayer,int32_t nIndex )
{
	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( NULL == packet )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBattle = 0;
	packet->writeInt8( 0 );
	packet->writeInt32( nIndex );
	nBattle = CFG_DATA.GetHallOfFameTable().GetRobot( nIndex );

	FameBattle battle( player->GetBattle(), nBattle );
	battle.Fight( packet, FBF_WIN );

	famePlayer.nIndex = nIndex;
	famePlayer.ResetFighters();

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_HALL_OF_FAME_BATTLE );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( player->getGateIndex(), packet );

	player->SendGameFightResult( true );
	return ERR_OK;
}

int32_t	CHallOfFameManager::OnRequestRankInfo( SocialPlayer* player, Answer::NetPacket* inPacket )
{
	if ( NULL == player || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCurIndex = 0;
	FamePlayerMap::iterator findIter = m_mPlayer.find( player->getCid() );
	if ( findIter != m_mPlayer.end() )
	{
		nCurIndex = findIter->second.nIndex;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( NULL == packet )
	{
		return ERR_INVALID_DATA;
	}

	packet->writeInt32( nCurIndex );
	int32_t nCount = 0;
	uint32_t oldOffset = packet->getWOffset();
	packet->writeInt32( nCount );
	for ( int32_t i = 1; i <= HALL_OF_FAME_RANK_SIZE; ++i )
	{
		if ( m_vPlayer[i] != NULL )
		{
			PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_vPlayer[i]->nCharId );
			if ( pInfo != NULL )
			{
				packet->writeInt32( i );
				packet->writeInt64( pInfo->nCharId );
				packet->writeUTF8( pInfo->strName );
				packet->writeInt32( pInfo->nBattle );
				packet->writeInt8( pInfo->nJob );
				packet->writeInt8( pInfo->nSex );
				packet->writeInt32( pInfo->nCloth );
				packet->writeInt32( pInfo->nWeapon );
				++nCount;
			}
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt32( nCount );
	packet->setWOffset( newOffset);

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_HALL_OF_FAME_RANK_INFO );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( player->getGateIndex(), packet );
	return ERR_OK;
}

int32_t	CHallOfFameManager::OnGetReward( SocialPlayer* player, Answer::NetPacket* inPacket )
{
	if ( NULL == player || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	FamePlayerMap::iterator findIter = m_mPlayer.find( player->getCid() );
	if ( findIter == m_mPlayer.end() )
	{
		return ERR_INVALID_DATA;
	}

	CFamePlayer& famePlayer = findIter->second;
	if ( famePlayer.nReward != 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( 0 == famePlayer.nLastIndex || famePlayer.nLastIndex > HALL_OF_FAME_RANK_SIZE )
	{
		return ERR_INVALID_DATA;
	}

	famePlayer.SignReward();

	player->SendGameGetHallOfFameRankReward( famePlayer.nLastIndex );
	return ERR_OK;
}

int32_t	CHallOfFameManager::OnRewardResult( SocialPlayer* player, Answer::NetPacket* inPacket )
{
	if ( NULL == player || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nLastIndex = inPacket->readInt32();
	int8_t nResult = inPacket->readInt8();
	if ( nResult == 0 )
	{
		FamePlayerMap::iterator findIter = m_mPlayer.find( player->getCid() );
		if ( findIter == m_mPlayer.end() )
		{
			return ERR_INVALID_DATA;
		}

		CFamePlayer& famePlayer = findIter->second;
		famePlayer.SignReward( false );
		return ERR_OK;
	}

	updateReward( nLastIndex );
	return ERR_OK;

}

void CHallOfFameManager::broadcastFight( CharId_t cid, const std::string& atker, const std::string& defer, int32_t nOldIndex, int32_t nNewIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_HALL_OF_FAME_FIGHT );
	packet->writeUTF8( atker );
	packet->writeInt64( cid );
	packet->writeUTF8( defer );
	packet->writeInt32( nOldIndex );
	packet->writeInt32( nNewIndex );

	packet->setSize(packet->getWOffset());
	packet->setProc( SM_SEND_NOTICE_PARAM );
	SOCIAL_SERVICE.worldBroadcast(packet);
}

void CHallOfFameManager::broadcastTops()
{
	if ( m_vPlayer[1] != NULL )
	{
		PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_vPlayer[1]->nCharId );
		if ( pInfo != NULL )
		{
			NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
			if (NULL == packet)
			{
				return;
			}
			packet->writeInt32( BCI_HALL_OF_FAME_RANK_1 );
			packet->writeUTF8( pInfo->strName );
			packet->writeInt64( pInfo->nCharId );
			packet->setSize(packet->getWOffset());
			packet->setProc( SM_SEND_NOTICE_PARAM );
			SOCIAL_SERVICE.worldBroadcast(packet);
		}
	}
	if ( m_vPlayer[2] != NULL )
	{
		PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_vPlayer[2]->nCharId );
		if ( pInfo != NULL )
		{
			NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
			if (NULL == packet)
			{
				return;
			}
			packet->writeInt32( BCI_HALL_OF_FAME_RANK_2 );
			packet->writeUTF8( pInfo->strName );
			packet->writeInt64( pInfo->nCharId );
			packet->setSize(packet->getWOffset());
			packet->setProc( SM_SEND_NOTICE_PARAM );
			SOCIAL_SERVICE.worldBroadcast(packet);
		}
	}
	if ( m_vPlayer[3] != NULL )
	{
		PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_vPlayer[3]->nCharId );
		if ( pInfo != NULL )
		{
			NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
			if (NULL == packet)
			{
				return;
			}
			packet->writeInt32( BCI_HALL_OF_FAME_RANK_3 );
			packet->writeUTF8( pInfo->strName );
			packet->writeInt64( pInfo->nCharId );
			packet->setSize(packet->getWOffset());
			packet->setProc( SM_SEND_NOTICE_PARAM );
			SOCIAL_SERVICE.worldBroadcast(packet);
		}
	}
}

void CHallOfFameManager::sendRankReward()
{
	for ( FamePlayerMap::iterator iter = m_mPlayer.begin(); iter != m_mPlayer.end(); ++iter )
	{
		iter->second.ResetLastIndex();
		if ( iter->second.nLastIndex > 0 && iter->second.nLastIndex <= HALL_OF_FAME_RANK_SIZE )
		{
			SocialPlayer* player = PLAYER_MANAGER.GetPlayerByCid( iter->second.nCharId );
			if ( player != NULL )
			{
				player->SendGameHallOfFameRankRewardInfo( iter->second.nLastIndex, iter->second.nReward );
			}
		}
	}
}

void CHallOfFameManager::saveIndex( int32_t nIndex )
{
	CharId_t cid = 0;
	if ( m_vPlayer[nIndex] != NULL )
	{
		cid = m_vPlayer[nIndex]->nCharId;
	}
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_hall_of_fame` (`fame_index`, `cid`) VALUES (%d, %lld) ON DUPLICATE KEY UPDATE `cid`=%lld", nIndex, cid, cid );
	db.excute(szSQL);
}

void CHallOfFameManager::saveLastIndex()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "UPDATE `mem_hall_of_fame` SET `last_cid`=`cid`, `reward`=0";
	db.excute(szSQL);
}

void CHallOfFameManager::updateReward( int32_t nIndex )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_hall_of_fame` SET `reward`=1 WHERE `fame_index`=%d", nIndex );
	db.excute(szSQL);
}
