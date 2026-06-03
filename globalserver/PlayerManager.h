#ifndef __SOCIAL_PLAYER_MANAGER_H__
#define __SOCIAL_PLAYER_MANAGER_H__

#include "SocialPlayer.h"
#include <vector>
#include "DataStructs.h"

typedef Answer::ObjectPool<SocialPlayer> SocialPlayerPool;
typedef Answer::ObjectPool<PlayerInfo> PlayerInfoPool;
typedef std::map<CharId_t, SocialPlayer*> CharIdSocialPlayerMap;
typedef std::map<int16_t, SocialPlayer*> Int16SocialPlayerMap;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

public:
	bool Init();

public:
	SocialPlayer* GetPlayerByCid( CharId_t nCharId );
	SocialPlayer* GetPlayerByGateIndex( int16_t nIndex );

	PlayerInfo*	GetPlayerInfo( CharId_t nCharId );
	PlayerInfo*	GetPlayerInfo( const std::string& name );

	void AddPlayer( Answer::NetPacket* inPacket );
	void UpdatePlayer( Answer::NetPacket* inPacket );
	void DelPlayer( Answer::NetPacket *inPacket );

	void GetAllPlayerIndex( Int16Vector& indexes );
	void GetPlayerList( SocialPlayer* pPlayer, std::list<FriendInfo>& FriendList, int32_t MinLeve, int32_t MaxLevel, int32_t nLimitCount );

	void GetAllPlayerInfo( PlayerInfoVt& vPlayer );

private:
	PlayerInfo*	loadPlayerInfo( CharId_t nCharId );

private:
	PlayerInfoPool			m_PlayerInfoPool;
	CharIdPlayerInfoMap		m_mPlayerInfoByCid;
	StringPlayerInfoMap		m_mPlayerInfoByName;

	SocialPlayerPool		m_SocialPlayerPool;
	CharIdSocialPlayerMap	m_mSocialPlayerByCid;
	Int16SocialPlayerMap	m_mSocialPlayerByGateIndex;
};
#define PLAYER_MANAGER Answer::Singleton<PlayerManager>::instance()

#endif	// __SOCIAL_PLAYER_MANAGER_H__
