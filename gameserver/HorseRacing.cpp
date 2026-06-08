
#include "HorseRacing.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include "FamilyManager.h"
#include "ActivityManager.h"

#define HORSE_RACING_END_MAP_ID					10003		// 终点地图
#define HORSE_RACING_END_POS_X					20			// 终点坐标X
#define HORSE_RACING_END_POS_Y					57			// 终点坐标Y
#define HORSE_RACING_END_SIZE					6			// 终点区域大小
#define HORSE_RACING_ACTIVITY_SCORE_RANK_SIZE	3			// 排行榜大小
#define HORSE_RACING_BOOS_MAP_ID				90017		// BOSS地图

using namespace Answer;

CHorseRacing::CHorseRacing( const CfgActivity& cfgActivity )
:CActivity( cfgActivity ), m_nIndex( 0 )
{

}

CHorseRacing::~CHorseRacing()
{

}



void CHorseRacing::reset()
{
	CActivity::reset();
	m_rankList.clear();
	m_racing.clear();
	m_winner.clear();
	m_nIndex = 0;
}

void CHorseRacing::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
	if ( NULL == pMap )
	{
		return;
	}

	if ( pMap->GetId() != HORSE_RACING_END_MAP_ID )
	{
		return;
	}

	for ( PlayerList::iterator iter = m_racing.begin(); iter != m_racing.end(); )
	{
		Player* player = *iter;
		if ( NULL == player )
		{
			m_racing.erase( iter++ );
			continue;
		}

		if ( player->getMapId() == pMap->GetId() )
		{
			// 终点检测
			if ( player->getCurrentTile().tileDistance( Position( HORSE_RACING_END_POS_X, HORSE_RACING_END_POS_Y ) ) <= HORSE_RACING_END_SIZE )
			{
				m_racing.erase( iter++ );
				m_winner.push_back( player );
				win( player );
				continue;
			}
		}
		++iter;
	}
}

void CHorseRacing::SendPlayerActivityInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( getNextStartTime() );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}


void CHorseRacing::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = packetActivityScore();
	if ( NULL == packet )
	{
		return;
	}

	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CHorseRacing::removePlayer( Player* player, bool islogout )
{
	CActivity::removePlayer( player, islogout );
	{
		for ( PlayerList::iterator iter = m_racing.begin(); iter != m_racing.end(); ++iter )
		{
			if ( player == *iter )
			{
				m_racing.erase( iter );
				break;
			}
		}
	}
	{
		for ( PlayerList::iterator iter = m_winner.begin(); iter != m_winner.end(); ++iter )
		{
			if ( player == *iter )
			{
				m_winner.erase( iter );
				break;
			}
		}
	}
	player->removeBuff( ACTIVITY_HORSE_RACING_BUFF_ID );
}

void CHorseRacing::addPlayer( Player* player )
{
	CActivity::addPlayer( player );
	m_racing.push_back( player );
	CfgBuff *cfgBuff = CFG_DATA.getBuff( ACTIVITY_HORSE_RACING_BUFF_ID );
	if ( cfgBuff != NULL )
	{
		SkillBuff *buff = new SkillBuff( *player, *cfgBuff );
		if (NULL == buff)
		{
			return;
		}
		buff->init( cfgBuff->id, 1, player->getHandle(), player->getHandle() );
		player->addBuff( buff );
	}
}

int32_t	CHorseRacing::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	if ( NULL == player || NULL == pTargetMap )
	{
		return ERR_INVALID_DATA;
	}

	if ( pTargetMap->GetId() == HORSE_RACING_BOOS_MAP_ID )
	{
		if ( !bArrived( player->getCid() ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	else
	{
		if ( bArrived( player->getCid() ) )
		{
			player->TiShiInfo( FINISH_FEI_TIAN_SHENG_JV );
			return ERR_INVALID_DATA;
		}
	}

	return CActivity::canEnter( player, pTargetMap );
}

bool CHorseRacing::bArrived( CharId_t cid ) const
{
	PlayerRankList::const_iterator iter = m_rankList.begin();
	PlayerRankList::const_iterator eiter = m_rankList.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( iter->nCharId == cid )
		{
			return true;
		}
	}
	return false;
}

void CHorseRacing::win( Player* player )
{
	if ( NULL == player )
	{
		return;
	}
	++m_nIndex;
	addReward( player );
	sendActivityResult( player );
	broadcastWin( player );
	PlayerRank Rank = {};
	Rank.nCharId	= player->getCid();
	Rank.strName	= player->getName();
	m_rankList.push_back( Rank );
	if ( m_nIndex <= HORSE_RACING_ACTIVITY_SCORE_RANK_SIZE )
	{
		setNeedBroadcastActivityScore();
	}

	LogActivity logActivity = {};
	logActivity.cid = player->getCid();
	logActivity.actid = 0;
	logActivity.acttype = GetType();
	logActivity.time = player->getNow();
	DB_SERVICE.InsertActivityLog( logActivity );
}

void CHorseRacing::addReward( Player* player )
{
	const CfgHorseRacingReward* pReward = CFG_DATA.GetHorseRacingRewardTable().GetReward( m_nIndex );
	if ( NULL == pReward || NULL == player )
	{
		return;
	}
	if ( pReward->nExp > 0 )
	{
		player->addExp( pReward->nExp );
	}
	if ( pReward->nMoney > 0 )
	{
		player->AddCurrency( CURRENCY_MONEY, pReward->nMoney, MCR_HORSE_RACING_REWARD );
	}
	if ( pReward->Items.size() > 0 )
	{
		int32_t nMailIndex = 0;
		if ( m_nIndex == 1 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD1;
		}
		else if ( m_nIndex == 2 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD2;
		}
		else if ( m_nIndex == 3 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD3;
		}
		else if ( m_nIndex == 4 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD4;
		}
		else if ( m_nIndex == 5 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD5;
		}
		else if ( m_nIndex == 6 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD6;
		}
		else if ( m_nIndex == 7 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD7;
		}
		else if ( m_nIndex == 8 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD8;
		}
		else if ( m_nIndex == 9 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD9;
		}
		else if ( m_nIndex == 10 )
		{
			nMailIndex = MI_HORSE_RACING_REWARD0;
		}
		else
		{
			nMailIndex = MI_HORSE_RACING_REWARD;
		}
		if ( nMailIndex > 0 )
		{
			DB_SERVICE.OnSendSysMail( player->getCid(), nMailIndex,  pReward->Items );
		}
	}
}

void CHorseRacing::sendActivityResult( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( m_nIndex );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CHorseRacing::onTimeEnd()
{
	m_nState = AS_NOT_START;
	delayKickAll( 0 );	// 立即全部踢出
}

bool CHorseRacing::CanUseXP() const
{
	return false;
}

bool CHorseRacing::CanUsePet( MapId_t mid ) const
{
	if ( mid == HORSE_RACING_BOOS_MAP_ID )
	{
		return true;
	}
	return false;
}

Answer::NetPacket* CHorseRacing::packetActivityScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( getLeftTime() );
	int16_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt16( nCount );
	PlayerRankList::iterator iter = m_rankList.begin();
	PlayerRankList::iterator eiter = m_rankList.end();
	for ( ; iter != eiter; ++iter )
	{
		packet->writeUTF8( iter->strName );
		++nCount;
		if ( nCount >= HORSE_RACING_ACTIVITY_SCORE_RANK_SIZE )
		{
			break;
		}
	}
	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	return packet;
}

void CHorseRacing::broadcastReady()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_HORSE_RACING_READY );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CHorseRacing::broadcastStart()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_HORSE_RACING_START );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CHorseRacing::broadcastWin( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	int32_t nBroadCastId = 0;
	if ( m_nIndex == 1 )
	{
		nBroadCastId = BCI_HORSE_RACING_WIN_1;
	}
	else if ( m_nIndex == 2 )
	{
		nBroadCastId = BCI_HORSE_RACING_WIN_2;
	}
	else if ( m_nIndex == 3 )
	{
		nBroadCastId = BCI_HORSE_RACING_WIN_3;
	}

	if ( nBroadCastId > 0 )
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( nBroadCastId );
		packet->writeUTF8( player->getName() );
		packet->writeInt64( player->getCid() );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(packet);
	}
}
