#ifndef __CHAR_TEAM_DUNGEON_H__
#define __CHAR_TEAM_DUNGEON_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharTeamDungeon : public CExtSystemBase
{
public:
	CExtCharTeamDungeon();
	virtual ~CExtCharTeamDungeon();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onTeamDungeonCreate( Answer::NetPacket* inPacket );
	int32_t				onTeamDungeonJoin( Answer::NetPacket* inPacket );
	int32_t				onTeamDungeonStart( Answer::NetPacket* inPacket );

	int32_t				onSocialTeamDungeonStart( Answer::NetPacket* inPacket );
	int32_t				onSocialTeamDungeonUpdateInfo( Answer::NetPacket* inPacket );

public:
	bool				IsFunctionOpen() const;
	bool				IsInTeamDungeon() const;
	bool				IsTeamDungeonLeader() const;
	void				LeaveTeamDungeon();

private:
	bool				checkTeamDungeon( const CfgDungeon& cfgDungeon ) const;
	int32_t				onSocialTeamDungeonCost( Answer::NetPacket* inPacket );

private:
	int32_t				m_nId;
	int32_t				m_nDungeonId;
	CharId_t			m_nLeader;
};

#endif	//__CHAR_TEAM_DUNGEON_H__
