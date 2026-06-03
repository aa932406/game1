#ifndef __TPOC_TEAM_DUNGEON_H__
#define __TPOC_TEAM_DUNGEON_H__

class SocialPlayer;
class TeamDungeon
{
public:
	TeamDungeon( int32_t nId, SocialPlayer* player, int32_t nDungeonId, int32_t battle, int32_t nLine );
	~TeamDungeon();

public:
	int32_t	GetId() const;
	int32_t GetDungeonId() const;
	int32_t GetLimitBattle() const;
	SocialPlayer*	GetLeader();

	bool	StartDungeon( SocialPlayer* player );
	bool	MemberLeave( SocialPlayer* player );
	bool	MemberJoin( SocialPlayer* player );
	bool	SetAutoStart( SocialPlayer* player, int8_t bAuto );
	bool	KickMember( SocialPlayer* player, CharId_t memberId );
	void	AppendInfo( Answer::NetPacket* packet );

	void	BroadcastMemberInfo();
	void	Broadcast( Answer::NetPacket* packet );
	bool	CheckAutoStart();

private:
	void	setNewLeader();
	void	broadcastMemberLeave( CharId_t cid, int8_t reason );
	void	sendGameCreateDungeon();
	void	sendGameStartDungeon();
	void	broadcastStartDungeon();

private:
	int32_t			m_nId;
	int32_t			m_nDungeonId;								// 副本ID
	SocialPlayer*	m_arrMembers[MAX_TEAM_MEMBER_COUNT];		// 成员列表
	SocialPlayer*	m_pLeader;									// 队长
	int8_t			m_nMemberCount;								// 成员数量
	int32_t			m_nLimitBattle;								// 需求战斗力
	int32_t			m_nCreaterLine;								// 创建线路
	int8_t			m_bAutoStart;								// 自动开启
};
typedef std::list<TeamDungeon*> TeamDungeonList;

class TeamDungeonManager
{
public:
	TeamDungeonManager();
	~TeamDungeonManager();

public:
	bool RemoveDungeon( TeamDungeon* pDungeon );
	void SendDungeonList( SocialPlayer* pPlayer, int32_t nDungeonId );

	TeamDungeon*	CreateTeamDungeon( SocialPlayer* pPlayer, int32_t nDungeonId, int32_t battle, int32_t nLine );
	TeamDungeon*	GetTeamDungeon( int32_t nId );

private:
	TeamDungeonList	m_lstTeamDungon;
	int32_t			m_nNextId;
};

#define TEAM_DUNGEON_MANAGER Answer::Singleton<TeamDungeonManager>::instance()

#endif // __TPOC_TEAM_DUNGEON_H__
