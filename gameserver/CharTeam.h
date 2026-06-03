#ifndef __CHAR_TEAM_H__
#define __CHAR_TEAM_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharTeam : public CExtSystemBase
{
public:
	CExtCharTeam();
	virtual ~CExtCharTeam();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onQueryTeamsAround( Answer::NetPacket* inPacket );
	int32_t				onSetTeamAutoOperate( Answer::NetPacket* inPacket );
	int32_t				onUpdateTeamInfo( Answer::NetPacket* inPacket );

public:
	bool				IsFunctionOpen() const;
	bool				IsInTeam() const;
	bool				IsLeader() const;
	int32_t				GetTeamId() const;
	CharId_t			GetLeaderId() const;
	std::string			GetLeaderName() const;
	void			 	GetTeamMembers( CharIdList& members ) const;
	int32_t				GetMemberCount() const;
	void				Broadcast( Answer::NetPacket* inPacket );
	void				BroadcastBasicData();
	void				LeaveTeam();
	const TeamMemberList&	GetTeamMembers() const;
	void				UpdateTeamSetting();

private:
	int32_t				m_nTeamId;
	int64_t				m_nLastQueryTeamTick;

	CharId_t			m_nLeaderId;
	std::string			m_strLeaderName;
	TeamMemberList		m_lstMember;
};

#endif	//__CHAR_TEAM_H__
