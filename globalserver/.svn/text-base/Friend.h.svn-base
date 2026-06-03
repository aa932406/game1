#ifndef __FRIEND_H__
#define __FRIEND_H__
#include "stdafx.h"

struct ENEMY_INFO
{
	CharId_t  EnemyCid;
	int8_t	 EnemyType;
};

typedef std::list<ENEMY_INFO> ENEMY_LIST;

class SocialPlayer;

class CFriend
{
public:
	CFriend();
	~CFriend();
	void		CleanUp();
	void		Init( SocialPlayer* pPlayer );
public:
	int32_t		OnAskFriendList( Answer::NetPacket *inPacket );				// 请求好友列表
	int32_t		OnAskAddFriend( Answer::NetPacket *inPacket );				// 请求添加好友
	int32_t		OnReplyAddFriend( Answer::NetPacket *inPacket );			// 是否同意添加好友
	int32_t		OnDeleteFriend( Answer::NetPacket *inPacket );				// 删除好友
	int32_t		OnSiftFriend( Answer::NetPacket *inPacket );				// 筛选好友
	int32_t		OnBeKilled( Answer::NetPacket *inPacket );
	int32_t		OnGetPlayerInfo( Answer::NetPacket *inPacket );				// 获取玩家信息

	int32_t		UpdateLevelUp( int32_t OldLevel,int32_t Level );			// 更新人物等级
	bool		IsInEnemy( CharId_t Cid, int8_t EnemyType );
	int32_t		GetFriendMaxCount();
	void		DeleteFriedFromMem( CharId_t TargetCid );
	void		AddFriendToMem( CharId_t TargetCid );
	bool		IsInFriendList( CharId_t TargetCid );
	void		LoadFriend();
private:
	void		SendFriendList();
	void		SendSiftedFriend();
	void		SendFriendLevelUp( int32_t OldLevel, int32_t Level );
	void		SendAddFriendRequest( SocialPlayer*  pSocialPlayer );

	void		InsertFriend( CharId_t TargetCid );
	void		DeleteFriend( CharId_t TargetCid );

	void		InsertEnemy( CharId_t TargetCid, int8_t EnemyType );
	void		DeleteEnemy( CharId_t TargetCid, int8_t EnemyType );

	int32_t		GetFriendCount();
	int32_t		GetEnemyCount( int8_t EnemyType );

	void		SetMaxFriendCount( int32_t Level );
	void		SendAddFriendAchievement( CharId_t CharId );

private:
	CharIdList		m_FriendList;		// 好友列表
	ENEMY_LIST		m_EnemyList;		// 黑名单
	int32_t			m_MaxFriendCount;	// 最大好友个数
	int32_t			m_LastSiftTime;		// 最后一次刷新好友
	SocialPlayer*	m_pPlayer;
};

#endif