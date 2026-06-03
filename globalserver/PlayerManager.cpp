
#include "stdafx.h"
#include "PetRank.h"
#include "PetManager.h"
#include "PlayerManager.h"
#include "SocialService.h"

using namespace Answer;

PlayerManager::PlayerManager()
:m_PlayerInfoPool( 500, 2000 ), m_SocialPlayerPool( 100, 1000 )
{

}

PlayerManager::~PlayerManager()
{

}

bool PlayerManager::Init()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid,a.name, a.sex, a.job,a.vip,a.vip_end_time,a.level,a.sid,a.uid,a.last_logout_time,a.battle,a.weapon,a.cloth,b.family_id,c.LimitCount,d.record FROM `mem_character` As a LEFT JOIN `mem_chr_family` As b ON a.cid = b.cid LEFT JOIN `mem_char_operate_limit` As c ON a.cid = c.cid and c.LimitId=37204 LEFT JOIN `mem_char_worship` AS d ON a.cid=d.cid WHERE a.last_login_time>0");
	MySqlQuery result = db.query(szSQL);

	while ( !result.eof() )
	{
		PlayerInfo *pInfo = m_PlayerInfoPool.pop();
		if ( NULL == pInfo )
		{
			LOG_ERROR( "PlayerManager::Init() PlayerInfoPool Full!!!" );
			return false;
		}

		pInfo->nCharId			= result.getInt64Value("cid");;
		pInfo->strName			= result.getStringValue("name");
		pInfo->nSex				= result.getIntValue("sex");
		pInfo->nJob				= result.getIntValue("job");
		pInfo->nLevel			= result.getIntValue("level");
		pInfo->nLastLogoutTime	= result.getIntValue("last_logout_time");
		pInfo->nBattle			= result.getIntValue("battle");
		pInfo->bLearnedXP		= result.getIntValue("LimitCount") > 0;
		pInfo->nVip				= result.getIntValue("vip");
		pInfo->nWorshipRecord	= result.getIntValue("record");
		pInfo->nWeapon			= result.getIntValue("weapon");
		pInfo->nCloth			= result.getIntValue("cloth");
		pInfo->nVipEndTime 		= result.getIntValue("vip_end_time");
		if ( pInfo->nVipEndTime <= DayTime::now() )
		{
			pInfo->nVip = 0;
		}
		else
		{
			int8_t VipType = 0;
			int8_t i = 0;
			while( i < VIP_CARD_TYPE_COUNT )
			{
				if ( ( ( pInfo->nVipEndTime >> i ) & 1 )> 0 )
				{
					VipType = i + 1;
				}
				i++;
			}
			pInfo->nVip = VipType;
		}
		bzero( szSQL,sizeof(szSQL) );
		snprintf(szSQL, sizeof(szSQL)-1, "SELECT LimitCount FROM `mem_char_operate_limit` WHERE `cid`=%lld and LimitId=1034", pInfo->nCharId,1034 );//RP_CUR_GUAN_WEI
		MySqlQuery result_1 = db.query(szSQL);
		if ( !result_1.eof() )
		{
			pInfo->nGuanWei = result_1.getIntValue("LimitCount");
		}

		m_mPlayerInfoByCid[pInfo->nCharId] = pInfo;
		m_mPlayerInfoByName[pInfo->strName] = pInfo;

		result.nextRow();
	}

	return true;
}

SocialPlayer* PlayerManager::GetPlayerByCid( CharId_t nCharId )
{
	CharIdSocialPlayerMap::iterator iter = m_mSocialPlayerByCid.find( nCharId );
	if ( iter != m_mSocialPlayerByCid.end() )
	{
		return iter->second;
	}
	return NULL;
}

SocialPlayer* PlayerManager::GetPlayerByGateIndex( int16_t nIndex )
{
	Int16SocialPlayerMap::iterator iter = m_mSocialPlayerByGateIndex.find( nIndex );
	if ( iter != m_mSocialPlayerByGateIndex.end() )
	{
		return iter->second;
	}
	return NULL;
}

PlayerInfo* PlayerManager::GetPlayerInfo( CharId_t nCharId )
{
	CharIdPlayerInfoMap::iterator iter = m_mPlayerInfoByCid.find( nCharId );
	if ( iter != m_mPlayerInfoByCid.end() )
	{
		return iter->second;
	}
	return loadPlayerInfo( nCharId );
}

PlayerInfo* PlayerManager::GetPlayerInfo( const std::string& name )
{
	StringPlayerInfoMap::iterator iter = m_mPlayerInfoByName.find( name );
	if ( iter != m_mPlayerInfoByName.end() )
	{
		return iter->second;
	}
	return NULL;
}

void PlayerManager::AddPlayer( NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	int32_t cgindex = inPacket->readInt32();
	CharId_t cid = inPacket->readInt64();
	int32_t uid = inPacket->readInt32();
	int32_t sid = inPacket->readInt32();

	PlayerInfo* pInfo = GetPlayerInfo( cid );
	if ( NULL == pInfo )
	{
		LOG_ERROR( "PlayerManager::AddPlayer() PlayerInfo not find cid=%lld!!!", cid );
		return;
	}

	SocialPlayer *pPlayer = m_SocialPlayerPool.pop();
	if ( NULL == pPlayer )
	{
		LOG_ERROR( "PlayerManager::AddPlayer() SocialPlayerPool Full!!!" );
		return;
	}
#ifdef _DEBUG
	printf( "PlayerManager::AddPlayer() index=%d,\tname=%s\n", cgindex, pInfo->strName.c_str() );
#endif

	pPlayer->init( cgindex, cid, uid, sid, pInfo );
	m_mSocialPlayerByCid[cid] = pPlayer;
	m_mSocialPlayerByGateIndex[cgindex] = pPlayer; 
}

void PlayerManager::UpdatePlayer( NetPacket* inPacket )
{
	if (NULL == inPacket)
	{
		return;
	}

	CharId_t cid = inPacket->readInt64();
	int32_t key = inPacket->readInt32();
	int32_t value = inPacket->readInt32();

	PlayerInfo* pInfo = GetPlayerInfo( cid );
	if ( NULL == pInfo )
	{
		return;
	}

	switch ( key )
	{
	case PII_JOB:
		{
			pInfo->nJob = value; 
		}
		break;
	case PII_LEVEL:
		{
			SocialPlayer *player = GetPlayerByCid( cid );
			if (player != NULL)
			{
				player->GetFrined().UpdateLevelUp( pInfo->nLevel, value);
			}
			pInfo->nLevel = value;
			break;
		}
	case PII_LAST_LOGOUT_TIME:
		{
			pInfo->nLastLogoutTime = value;
		}
		break;
	case PII_VIP:
		{
			pInfo->nVip = static_cast<int8_t>(value); 
		}
		break;
	case PII_VIP_LEVEL:
		{
			pInfo->nVipLevel = static_cast<int8_t>(value); 
			break;
		}
	case PII_LEARN_XP_SKILL:
		{
			pInfo->bLearnedXP = value > 0;
		}
		break;
	case PII_BATTLE:
		{
			pInfo->nBattle = value;
		}
		break;
	case PII_JUE_WEI:
		{	
			pInfo->nJueWei	= value;
		}
		break;
	case PII_WEAPON:
		{	
			pInfo->nWeapon	= value;
		}
		break;
	case PII_CLOTH:
		{	
			pInfo->nCloth	= value;
		}
		break;
	case PII_GUAN_WEI:
		{
			pInfo->nGuanWei = value;
		}
		break;
	default: return;
	}
}

void PlayerManager::DelPlayer( NetPacket *inPacket )
{
	if (NULL == inPacket)
	{
		return;
	}

	CharId_t cid = inPacket->readInt64();

	SocialPlayer *pPlayer = GetPlayerByCid( cid );
	if ( pPlayer != NULL )
	{
		int32_t cgindex = pPlayer->getGateIndex();

		m_mSocialPlayerByCid.erase( cid );
		m_mSocialPlayerByGateIndex.erase( cgindex );
		m_SocialPlayerPool.push( pPlayer );
	}
}

void PlayerManager::GetAllPlayerIndex( Int16Vector& indexes )
{
	indexes.reserve( m_mSocialPlayerByCid.size() );
	CharIdSocialPlayerMap::iterator iter = m_mSocialPlayerByCid.begin();
	CharIdSocialPlayerMap::iterator eiter = m_mSocialPlayerByCid.end();
	for ( ; iter != eiter; ++iter )
	{
		SocialPlayer* pPlayer = iter->second;
		if ( pPlayer != NULL )
		{
			indexes.push_back( pPlayer->getGateIndex() );
		}
	}
}

void PlayerManager::GetPlayerList( SocialPlayer* pPlayer, std::list<FriendInfo>& FriendList, int32_t MinLeve, int32_t MaxLevel, int32_t nLimitCount )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t nCount = 0;
	if ( MinLeve <= 0 )
	{
		MinLeve = 1;
	}
	if ( MaxLevel < MinLeve )
	{
		return;
	}

	CharIdSocialPlayerMap::iterator iter = m_mSocialPlayerByCid.begin();
	CharIdSocialPlayerMap::iterator eiter = m_mSocialPlayerByCid.end();
	for (; iter != eiter; ++iter )
	{
		SocialPlayer* pTemp = iter->second;
		if ( NULL == pTemp )
		{
			continue;
		}
		if ( pTemp->getLevel() >= MinLeve && pTemp->getLevel() <= MaxLevel )
		{
			FriendInfo Friend = {};
			Friend.Cid		= pTemp->getCid();
			Friend.Job		= pTemp->getJob();
			Friend.Level	= pTemp->getLevel();
			Friend.Name		= pTemp->getName();
			Friend.Sex		= pTemp->getSex();
			if ( pPlayer->getCid() == Friend.Cid || 
				pPlayer->GetFrined().IsInFriendList( Friend.Cid ) || 
				pPlayer->GetFrined().IsInEnemy( Friend.Cid, RLT_BLACKLIST ) ||
				pPlayer->GetFrined().IsInEnemy( Friend.Cid, RLT_IN_BLACKLIST ) )
			{
				continue;
			}
			FriendList.push_back( Friend );
			++nCount;
			if ( nCount >= nLimitCount )
			{
				break;
			}
		}
	}
}

void PlayerManager::GetAllPlayerInfo( PlayerInfoVt& vPlayer )
{
	vPlayer.reserve( m_mPlayerInfoByCid.size() );
	CharIdPlayerInfoMap::iterator iter = m_mPlayerInfoByCid.begin();
	CharIdPlayerInfoMap::iterator eiter = m_mPlayerInfoByCid.end();
	for ( ; iter != eiter; ++iter )
	{
		vPlayer.push_back( *(iter->second) );
	}
}

PlayerInfo* PlayerManager::loadPlayerInfo( CharId_t nCharId )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid,a.name, a.sex, a.job,a.vip,a.vip_end_time,a.level,a.sid,a.uid,a.last_logout_time,a.battle,a.weapon,a.cloth,b.family_id,c.LimitCount,d.record FROM `mem_character` As a LEFT JOIN `mem_chr_family` As b ON a.cid = b.cid LEFT JOIN `mem_char_operate_limit` As c ON a.cid = c.cid and c.LimitId=37204 LEFT JOIN `mem_char_worship` AS d ON a.cid=d.cid WHERE a.cid=%lld", nCharId );
	MySqlQuery result = db.query(szSQL);

	if ( result.eof() )
	{
		LOG_ERROR( "PlayerManager::loadPlayerInfo() Player not find cid=%lld!!!", nCharId );
		return NULL;
	}
	
	PlayerInfo *pInfo = m_PlayerInfoPool.pop();
	if ( NULL == pInfo )
	{
		LOG_ERROR( "PlayerManager::loadPlayerInfo() PlayerInfoPool Full!!!" );
		return NULL;
	}

	pInfo->nCharId			= nCharId;
	pInfo->strName			= result.getStringValue("name");
	pInfo->nSex				= result.getIntValue("sex");
	pInfo->nJob				= result.getIntValue("job");
	pInfo->nLevel			= result.getIntValue("level");
	pInfo->nLastLogoutTime =  result.getIntValue("last_logout_time");
	pInfo->nBattle			= result.getIntValue("battle");
	pInfo->bLearnedXP		= result.getIntValue("LimitCount") > 0;
	pInfo->nVip				= result.getIntValue("vip");
	pInfo->nWorshipRecord	= result.getIntValue("record");
	pInfo->nWeapon			= result.getIntValue("weapon");
	pInfo->nCloth			= result.getIntValue("cloth");
	pInfo->nVipEndTime		= result.getIntValue("vip_end_time");
	if ( pInfo->nVipEndTime <= DayTime::now() )
	{
		pInfo->nVip = 0;
	}
	else
	{
		int8_t VipType = 0;
		int8_t i = 0;
		while( i < VIP_CARD_TYPE_COUNT )
		{
			if ( ( ( pInfo->nVipEndTime >> i ) & 1 )> 0 )
			{
				VipType = i + 1;
			}
			i++;
		}
		pInfo->nVip = VipType;
	}

	m_mPlayerInfoByCid[pInfo->nCharId] = pInfo;
	m_mPlayerInfoByName[pInfo->strName] = pInfo;
	return pInfo;
}
