#ifndef __TEAM_MANAGER_H__
#define __TEAM_MANAGER_H__

#include "Team.h"
#include "SocialPlayer.h"

typedef std::map<int32_t, Team*> TeamMap;
class TeamManager
{
public:
	TeamManager();
	~TeamManager();

	Team*	CreateTeam( SocialPlayer* pLeader );
	Team*	GetTeam( int32_t nTeamId );
	void	DeleteTeam( int32_t nTeamId );

private:
	int32_t	getNewTeamId();

private:
	TeamMap	m_teamPool;
	int32_t	m_nextTeamId;
};

#define TEAM_MANAGER Answer::Singleton<TeamManager>::instance()


#endif	//__TEAM_MANAGER_H__
