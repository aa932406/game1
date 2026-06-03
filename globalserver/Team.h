#ifndef __TPOC_TEAM_H__
#define __TPOC_TEAM_H__


class SocialPlayer;
class Team
{
public:
	Team( int32_t nTeamId, SocialPlayer* player );
	~Team();

public:
	bool			IsFull() const;
	bool			IsInTeam( CharId_t nCharId ) const;
	int32_t			GetId() const;
	int8_t			GetMemberCount() const;
	void			GetMembers( TeamMemberList& members ) const;
	SocialPlayer*	GetLeader() const;
	bool			SetLeader( CharId_t nCid );
	int32_t			MemberJoin( SocialPlayer* player );
	bool			MemberLeave( CharId_t nCid, LEAVE_TEAM_REASON nReason = LTR_NORMAL );
	void			Destroy();
	void			Broadcast( Answer::NetPacket *inPacket );
	void			BroadcastMembers();
	void			AddApplyer( SocialPlayer* pApplyer );
	void			RemoveApplyer( CharId_t nCid );
	SocialPlayer*	CheckInApplyList( CharId_t nCid ) const;
	//void			AddXP();
	bool			IsInXP();
	void			CheckEndXP();
	bool			AllMembersXpStateStop();
	void			resetXP( int32_t nValue );

private:
	void			cleanUp();
	void			sendLeaveTeam( CharId_t nCid, LEAVE_TEAM_REASON nReason );
	void			avrageXP();
	void			broadcastXPRecord();
	float			getXPExpKey();
	void			updateGameAllMemberInfo();

private:
	int32_t			m_nTeamId;									// 队伍ID
	SocialPlayer*	m_arrMembers[MAX_TEAM_MEMBER_COUNT];		// 队员列表
	SocialPlayer*	m_pLeader;									// 队长
	int8_t			m_nMemberCount;

	typedef std::list<SocialPlayer*> ApplyList;
	ApplyList		m_lstApply;									// 申请列表
};

#endif // __TPOC_TEAM_H__
