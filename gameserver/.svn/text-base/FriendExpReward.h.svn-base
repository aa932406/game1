#ifndef __FRIEND_EXP_REWARD_H__
#define __FRIEND_EXP_REWARD_H__
#include "ExtSystemBase.h"

class Player;
class CFriendExpReward:
	public CExtSystemBase
{
public:
	CFriendExpReward();
	virtual ~CFriendExpReward();
public:
	virtual void			OnCleanUp();
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t 		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
private:
	int32_t					OnAskRewardInfo( Answer::NetPacket* pData );
	int32_t					OnAskGetReward( Answer::NetPacket* pData );
	int32_t					OnUpdateRewardInfo( Answer::NetPacket* pData );

	void					SendRewardInfo();
private:
	FriendExpMap	m_RewardInfo;
};

#endif