#include "Friend.h"
#include "SocialPlayer.h"
#include "SocialService.h"
#include "PlayerManager.h"
#include "FamilyManager.h"
using namespace Answer;
const static int32_t FriendCount[3] = { 30, 50, 70 };  	
#define BLACK_LIST_MAX_COUNT 30		//黑名单个数
#define SIFT_FRIEND_CD		10		//筛选好友的cd

enum ReplyValues
{
	ERR_PLAYER_NOT_ONLINE			= 1,		//玩家不在线
	ERR_IN_BLACKLIST				= 2,		//在黑名单中
	ERR_IN_TARGET_BLACKLIST 		= 3,		//在对方黑名单中
	ERR_IS_IN_FRIEND_LIST			= 4,		//已经是你的好友了
	ERR_FRIEND_UPPER_LIMIT			= 5,		//好有个数达到上限
	ERR_TARGET_FRIEND_UPPER_LIMIT	= 6,		//对方好友数达到上限
	ERR_TARGET_SET_NOT_ADD			= 7,		//对方设置了不能加
};

CFriend::CFriend()
{
	CleanUp();
}

CFriend::~CFriend()
{

}

void CFriend::CleanUp()
{
	m_FriendList.clear();
	m_EnemyList.clear();
	m_MaxFriendCount = 0;
	m_LastSiftTime	 = 0;
}

void CFriend::Init( SocialPlayer* pPlayer )
{
	m_pPlayer = pPlayer;
}

int32_t CFriend::OnAskFriendList( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer  )
	{
		return ERR_SYETEM_ERR;
	}
	SendFriendList();
	return ERR_OK;
}

int32_t CFriend::OnAskAddFriend( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer  )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t		FriendType	= inPacket->readInt8();
	CharId_t	TargetCid	= inPacket->readInt64();
	std::string TargetName	= inPacket->readUTF8(true);
	if (!TargetName.empty() && StringUtility::utf8Strlen(TargetName.c_str()) > MAX_NAME_CCH_LENGTH)
	{
		return ERR_SYETEM_ERR;
	}
	if( FriendType != RLT_FRIEND &&  FriendType != RLT_ENEMY && FriendType != RLT_BLACKLIST)
	{
		return ERR_SYETEM_ERR;
	}

	PlayerInfo* targetPlayer = NULL;
	if (TargetCid > 0)
	{
		targetPlayer = PLAYER_MANAGER.GetPlayerInfo( TargetCid );
	}
	else if ( !TargetName.empty() )
	{
		targetPlayer = PLAYER_MANAGER.GetPlayerInfo( TargetName );
	}

	if( targetPlayer == NULL )
	{
		return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_PLAYER_NOT_ONLINE);
	}

	TargetCid = targetPlayer->nCharId;

	SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( TargetCid );
	if ( NULL == pSocialPlayer )
	{
		return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_PLAYER_NOT_ONLINE);
	}
	if ( !pSocialPlayer->CanAddFriend() )
	{
		return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_TARGET_SET_NOT_ADD);
	}

	if ( RLT_FRIEND == FriendType )		// 添加好友
	{
		if ( IsInEnemy( TargetCid, static_cast<int8_t>( RLT_BLACKLIST ) ) )
		{
			return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_IN_BLACKLIST );
		}
		if ( pSocialPlayer->GetFrined().IsInEnemy( m_pPlayer->getCid(), static_cast<int8_t>( RLT_BLACKLIST ) ) )
		{
			return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_IN_TARGET_BLACKLIST );
		}
		if ( IsInFriendList( TargetCid ) )
		{
			return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_IN_TARGET_BLACKLIST );
		}
	}
	else if ( RLT_BLACKLIST == FriendType )
	{
		if ( IsInFriendList( TargetCid ) )
		{
			DeleteFriend( TargetCid );
		}
		InsertEnemy( TargetCid, static_cast<int8_t>( RLT_BLACKLIST ) );
		return ERR_OK;
	}
	else 
	{
		InsertEnemy( TargetCid, static_cast<int8_t>( RLT_ENEMY ) );
		return ERR_OK;
	}

	SendAddFriendRequest( pSocialPlayer );	
	SOCIAL_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CFriend::OnReplyAddFriend( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer  )
	{
		return ERR_SYETEM_ERR;
	}

	CharId_t TargetCid	= inPacket->readInt64();
	int8_t	ReplyResult	= inPacket->readInt8();

	SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( TargetCid );
	if ( NULL == pSocialPlayer )
	{
		return ERR_SYETEM_ERR;
	}

	if (  1 != ReplyResult )		// 不同意添加
	{
		return ERR_SYETEM_ERR;
	}
	
	if ( GetFriendCount() >= m_MaxFriendCount )
	{
		return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_FRIEND_UPPER_LIMIT );
	}

	if ( pSocialPlayer->GetFrined().GetFriendCount() >= pSocialPlayer->GetFrined().GetFriendMaxCount() )
	{
		return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_TARGET_FRIEND_UPPER_LIMIT );
	}
	InsertFriend( TargetCid );
	SendAddFriendAchievement( TargetCid );
	SendAddFriendAchievement( m_pPlayer->getCid() );
	return ERR_OK;
}

int32_t CFriend::OnDeleteFriend( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer  )
	{
		return ERR_SYETEM_ERR;
	}

	CharId_t TargetCid	= inPacket->readInt64();
	int8_t	FriendType	= inPacket->readInt8();

	if ( RLT_FRIEND == FriendType )
	{
		if ( IsInFriendList( TargetCid ) )
		{
			DeleteFriend( TargetCid );
		}
	}
	else if ( RLT_BLACKLIST == FriendType )
	{
		if ( IsInEnemy( TargetCid, static_cast<int8_t>( RLT_BLACKLIST ) ) )
		{
			DeleteEnemy( TargetCid, static_cast<int8_t>( RLT_BLACKLIST ) );
		}
	}
	else if ( RLT_ENEMY == FriendType )
	{
		DeleteEnemy( TargetCid, static_cast<int8_t>( RLT_ENEMY ) );
	}
	return ERR_OK;
}

int32_t CFriend::OnSiftFriend( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendSiftedFriend();
	return ERR_OK;
}

int32_t CFriend::UpdateLevelUp( int32_t OldLevel, int32_t Level )
{
	SendFriendLevelUp( OldLevel, Level );
	SetMaxFriendCount( Level );
	return ERR_OK;
}

int32_t	CFriend::OnBeKilled( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	CharId_t TargetId  = inPacket->readInt64();
	if ( TargetId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !IsInEnemy( TargetId, RLT_ENEMY ))
	{
		InsertEnemy( TargetId, RLT_ENEMY );
	}
	return ERR_OK;
}

int32_t	CFriend::OnGetPlayerInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	std::string TargetName	= inPacket->readUTF8(true);

	PlayerInfo* targetPlayer = NULL;

	if ( !TargetName.empty() )
	{
		targetPlayer = PLAYER_MANAGER.GetPlayerInfo( TargetName );
	}

	if( targetPlayer == NULL )
	{
		return SOCIAL_SERVICE.replyfailure(m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_PLAYER_NOT_ONLINE);
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt64( targetPlayer->nCharId );
	packet->writeInt32( targetPlayer->nLevel );
	packet->writeInt8( targetPlayer->nSex );
	packet->writeInt8( targetPlayer->nJob );
	packet->writeUTF8( targetPlayer->strName );
	packet->setProc(SM_FRIEND_INFO);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
	return ERR_OK;
}

void CFriend::SendFriendList()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	int32_t CurTime = DayTime::now();
	int32_t nSize = 0;
	int32_t Offset = packet->getWOffset();
	packet->writeInt32( nSize );
	CharIdList::iterator it = m_FriendList.begin();
	for ( ; it != m_FriendList.end(); ++it )
	{
		PlayerInfo* targetPlayer = PLAYER_MANAGER.GetPlayerInfo(*it);
		if(targetPlayer != NULL)
		{
			packet->writeInt64( targetPlayer->nCharId );
			packet->writeInt32( targetPlayer->nLevel );
			packet->writeInt8( targetPlayer->nSex );
			packet->writeInt8( targetPlayer->nJob );
			packet->writeUTF8( targetPlayer->strName );
			packet->writeInt32( targetPlayer->nLastLogoutTime == 0 ? 0 : CurTime - targetPlayer->nLastLogoutTime );
			packet->writeInt32( targetPlayer->nBattle );
			packet->writeInt8( targetPlayer->nJueWei );
			Family*	pFamily = FAMILY_MANAGER.GetFamily( targetPlayer->nFamilyId );
			if ( NULL != pFamily )
			{
				packet->writeUTF8( pFamily->GetName() );
			}
			else
			{
				packet->writeUTF8("");
			}
			nSize++;
		}
	}
	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( Offset );
	packet->writeInt32( nSize );
	packet->setWOffset( endOffSet );
	
 	ENEMY_LIST::iterator bIt = m_EnemyList.begin();
	int32_t bSize = 0;
	Offset	= packet->getWOffset();
 	packet->writeInt32( bSize );
 	
 	for ( ; bIt != m_EnemyList.end(); ++bIt )
 	{
		PlayerInfo* targetPlayer = PLAYER_MANAGER.GetPlayerInfo( bIt->EnemyCid );
		if(targetPlayer != NULL)
		{
			packet->writeInt8( bIt->EnemyType );
			packet->writeInt64( targetPlayer->nCharId );
			packet->writeInt32( targetPlayer->nLevel );
			packet->writeInt8( targetPlayer->nSex );
			packet->writeInt8( targetPlayer->nJob );
			packet->writeUTF8( targetPlayer->strName );
			packet->writeInt32( targetPlayer->nLastLogoutTime == 0 ? 0 : CurTime - targetPlayer->nLastLogoutTime );
			packet->writeInt32( targetPlayer->nBattle );
			packet->writeInt8( targetPlayer->nJueWei );
			Family*	pFamily = FAMILY_MANAGER.GetFamily( targetPlayer->nFamilyId );
			if ( NULL != pFamily )
			{
				packet->writeUTF8( pFamily->GetName() );
			}
			else
			{
				packet->writeUTF8("");
			}
			bSize++;
		}
	}
 	endOffSet = packet->getWOffset();
 	packet->setWOffset( Offset );
 	packet->writeInt32( bSize );
 
 	packet->setWOffset( endOffSet );
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_FRIEND_LIST);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CFriend::SendSiftedFriend()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t CurTime = DayTime::now();
	if ( CurTime - m_LastSiftTime < SIFT_FRIEND_CD )
	{
		return;
	}
	m_LastSiftTime = CurTime;
	std::list<FriendInfo> FriendList;
	FriendList.clear();
	int32_t Level = m_pPlayer->getLevel();
	PLAYER_MANAGER.GetPlayerList( m_pPlayer, FriendList, Level-3, Level + 3, 8 );
	std::list<FriendInfo>::iterator it = FriendList.begin();
	NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == Packet)
	{
		return;
	}
	int8_t nSize = static_cast<int8_t>(FriendList.size());
	Packet->writeInt8( nSize );
	for ( ; it != FriendList.end(); ++it )
	{
		Packet->writeInt64( it->Cid );
		Packet->writeInt32( it->Level );
		Packet->writeInt8( it->Job );
		Packet->writeInt8( it->Sex );
		Packet->writeUTF8( it->Name );
	}
	Packet->setType(PACK_DISPATCH);
	Packet->setProc(SM_SEND_SIFT_FRIEND);
	Packet->setSize(Packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), Packet);
}

void CFriend::SendFriendLevelUp( int32_t OldLevel, int32_t Level )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	CharIdList::iterator it = m_FriendList.begin();
	for ( ; it != m_FriendList.end(); ++it )
	{
		SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( *it );
		if ( NULL != pSocialPlayer )
		{
			NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
			if (NULL == Packet)
			{
				return;
			}
			Packet->writeInt32( pSocialPlayer->getuid() );
			Packet->writeInt32( pSocialPlayer->getsid() );
			Packet->writeInt32( pSocialPlayer->getGateIndex() );
			Packet->writeInt64( m_pPlayer->getCid() );
			Packet->writeInt32( OldLevel );
			Packet->writeInt32( Level );
			Packet->writeUTF8( m_pPlayer->getName() );
			Packet->setType(PACK_DISPATCH);
			Packet->setProc( IM_SOCIAL_GAME_UPDATE_FRIEND_LEVEL_UP );
			Packet->setSize(Packet->getWOffset());
			SOCIAL_SERVICE.sendPacket(Packet);
		}
	}
}

void CFriend::SendAddFriendAchievement( CharId_t CharId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( CharId );
	if ( NULL != pSocialPlayer )
	{
		NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == Packet)
		{
			return;
		}
		Packet->writeInt32( pSocialPlayer->getuid() );
		Packet->writeInt32( pSocialPlayer->getsid() );
		Packet->writeInt32( pSocialPlayer->getGateIndex() );
		Packet->writeInt8( 0 );
		Packet->setType(PACK_DISPATCH);
		Packet->setProc( IM_SOCIAL_GAME_ADD_FRIEND );
		Packet->setSize(Packet->getWOffset());
		SOCIAL_SERVICE.sendPacket(Packet);
	}
}

void CFriend::SendAddFriendRequest( SocialPlayer*  pSocialPlayer )
{
	if ( NULL == pSocialPlayer || NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == Packet)
	{
		return;
	}
	Packet->writeInt64( m_pPlayer->getCid() );
	Packet->writeInt32( m_pPlayer->getLevel() );
	Packet->writeUTF8( m_pPlayer->getName() );
	Packet->setType(PACK_DISPATCH);
	Packet->setProc(SM_SEND_FRIEND_REQUEST);
	Packet->setSize(Packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(pSocialPlayer->getGateIndex(), Packet);
}

bool CFriend::IsInEnemy( CharId_t Cid, int8_t EnemyType )
{
	ENEMY_LIST::iterator it = m_EnemyList.begin();
	for ( ; it != m_EnemyList.end(); ++it )
	{
		if ( it->EnemyCid == Cid && it->EnemyType == EnemyType  )
		{
			return true;
		}
	}
	return false;
}

void CFriend::LoadFriend()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_chr_friend` WHERE `cid`=%lld", m_pPlayer->getCid() );
	MySqlQuery result = db.query(szSQL);
	while (!result.eof())
	{
		CharId_t FriendId	= result.getInt64Value("tcid");
		m_FriendList.push_back( FriendId );
		result.nextRow();
	}
	bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_chr_friend` WHERE `tcid`=%lld", m_pPlayer->getCid() );
	MySqlQuery result_2 = db.query(szSQL);
	while (!result_2.eof())
	{
		CharId_t FriendId	= result_2.getInt64Value("cid");
		m_FriendList.push_back( FriendId );
		result_2.nextRow();
	}
	bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_enemy` WHERE `cid`=%lld", m_pPlayer->getCid() );
	MySqlQuery result_3 = db.query(szSQL);
	while (!result_3.eof())
	{
		ENEMY_INFO Enemy = {};
		Enemy.EnemyCid		= result_3.getInt64Value("ecid");
		Enemy.EnemyType		= result_3.getIntValue("friend_type");	
		m_EnemyList.push_back( Enemy );
		result_3.nextRow();
	}
	bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_enemy` WHERE `ecid`=%lld AND friend_type=%d", m_pPlayer->getCid(),RLT_BLACKLIST );
	MySqlQuery result_4 = db.query(szSQL);
	while (!result_4.eof())
	{
		ENEMY_INFO Enemy = {};
		Enemy.EnemyCid		= result_4.getInt64Value("cid");
		Enemy.EnemyType		= result_4.getIntValue("friend_type");	
		m_EnemyList.push_back( Enemy );
		result_4.nextRow();
	}
	SetMaxFriendCount( m_pPlayer->getLevel() );
}

void CFriend::InsertFriend( CharId_t TargetCid )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result;
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO  `mem_chr_friend` ( cid, tcid, time) VALUES ( %lld,%lld,%d )", m_pPlayer->getCid(), TargetCid, DayTime::now() );
	db.excute(szSQL);
	PlayerInfo* TargetInfo = PLAYER_MANAGER.GetPlayerInfo( TargetCid );
	if ( NULL != TargetInfo )
	{
		AddFriendToMem( TargetCid );
	}
	SocialPlayer* pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( TargetCid );
	if ( NULL == pSocialPlayer )
	{
		return;
	}	
	pSocialPlayer->GetFrined().AddFriendToMem( m_pPlayer->getCid() );
}

void CFriend::DeleteFriend( CharId_t TargetCid )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result;
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_chr_friend` WHERE ( cid=%lld and tcid=%lld ) or ( cid=%lld and tcid=%lld )", m_pPlayer->getCid(), TargetCid, TargetCid, m_pPlayer->getCid() );
	db.excute(szSQL);
	CharIdList::iterator it = m_FriendList.begin();
	for ( ; it != m_FriendList.end(); ++it )
	{
		if ( *it == TargetCid )
		{
			DeleteFriedFromMem( *it );
			break;
		}
	}
	SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( TargetCid );
	if ( NULL == pSocialPlayer )
	{
		return;
	}
	pSocialPlayer->GetFrined().DeleteFriedFromMem( m_pPlayer->getCid() );
}

void CFriend::InsertEnemy( CharId_t TargetCid, int8_t EnemyType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( GetEnemyCount( EnemyType ) > BLACK_LIST_MAX_COUNT )
	{
		ENEMY_LIST::iterator it = m_EnemyList.begin();
		for ( ; it != m_EnemyList.end(); ++it )
		{
			if ( it->EnemyCid == TargetCid && it->EnemyType == EnemyType )
			{
				DeleteEnemy( it->EnemyCid, it->EnemyType );
				break;
			}
		}
	}
	ENEMY_INFO Enemy = {};
	Enemy.EnemyCid		= TargetCid;
	Enemy.EnemyType		= EnemyType;
	m_EnemyList.push_back( Enemy );
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result;
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_enemy` (cid,ecid,friend_type) VALUES ( %lld, %lld, %d )", m_pPlayer->getCid(), TargetCid, EnemyType);
	db.excute(szSQL);
	SendFriendList();
}

void CFriend::DeleteEnemy( CharId_t TargetCid, int8_t EnemyType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result;
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_enemy` WHERE cid=%lld and ecid=%lld and friend_type=%d", m_pPlayer->getCid(), TargetCid, EnemyType);
	db.excute(szSQL);

	ENEMY_LIST::iterator it = m_EnemyList.begin();
	for ( ; it != m_EnemyList.end(); ++it )
	{
		if ( it->EnemyCid == TargetCid && it->EnemyType == EnemyType )
		{
			m_EnemyList.erase( it );
			break;
		}
	}
	SendFriendList();
}

int32_t CFriend::GetFriendCount()
{
	return m_FriendList.size();
}

int32_t	CFriend::GetEnemyCount( int8_t EnemyType )
{
	int32_t Count = 0;
	ENEMY_LIST::iterator it =  m_EnemyList.begin();
	for ( ; it != m_EnemyList.end(); ++it )
	{
		if ( it->EnemyType == EnemyType )
		{
			Count++;
		}
	}
	return Count;
}

void CFriend::DeleteFriedFromMem( CharId_t TargetCid )
{
	CharIdList::iterator it = m_FriendList.begin();
	for ( ; it != m_FriendList.end(); ++it )
	{
		if ( *it == TargetCid )
		{
			m_FriendList.erase( it );
			break;
		}
	}
	SendFriendList();
}

void CFriend::AddFriendToMem( CharId_t TargetCid )
{

	if ( TargetCid <= 0 )
	{
		return;
	}
	m_FriendList.push_back( TargetCid );
	SendFriendList();
}

int32_t	CFriend::GetFriendMaxCount()
{
	return m_MaxFriendCount;
}

bool CFriend::IsInFriendList( CharId_t TargetCid )
{
	CharIdList::iterator it = m_FriendList.begin();
	for ( ; it != m_FriendList.end(); ++it )
	{
		if ( *it ==TargetCid )
		{
			return true;
		}
	}
	return false;
}

void CFriend::SetMaxFriendCount( int32_t Level )
{
	if ( Level <= 30 )
	{
		m_MaxFriendCount = FriendCount[0];
	}
	else if ( Level <= 50 )
	{
		m_MaxFriendCount = FriendCount[1];
	}
	else
	{
		m_MaxFriendCount = FriendCount[2];
	}
}