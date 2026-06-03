#include "stdafx.h"

#include "SocialService.h"
#include "SocialPlayer.h"
#include "TeamManager.h"

using namespace Answer;

TeamManager::TeamManager()
:m_nextTeamId( 0 )
{

}

TeamManager::~TeamManager()
{

}

Team* TeamManager::CreateTeam( SocialPlayer* leader )
{
	int32_t nNewId = getNewTeamId();
	Team* newTeam = new Team( nNewId, leader );
	m_teamPool[nNewId] = newTeam;
	return m_teamPool[nNewId];
}

Team* TeamManager::GetTeam( int32_t nTeamId )
{
	TeamMap::iterator iter = m_teamPool.find( nTeamId );
	if ( iter != m_teamPool.end() )
	{
		return iter->second;
	}

	return NULL;
}

void TeamManager::DeleteTeam( int32_t nTeamId )
{
	TeamMap::iterator iter = m_teamPool.find( nTeamId );
	if ( iter != m_teamPool.end() )
	{
		Team* pTeam = iter->second;
		if ( pTeam != NULL )
		{
			delete pTeam;
		}
		m_teamPool.erase( iter );
	}
}

int32_t TeamManager::getNewTeamId()
{
	return ++m_nextTeamId;
}
