#ifndef __TPOC_BOSS_KILLED_REWARD_H__
#define __TPOC_BOSS_KILLED_REWARD_H__

#include "stdafx.h"
#include "ExtSystemBase.h"
#include "CfgData.h"
#include "DataStructs.h"

// ========== 协议定义 (参见 share/PDUDefine.h) ==========
// CM_GET_BOSS_KILLED_REWARD = 545, SM_BOSS_KILLED_REWARD_INFO = 0x283E

// ========== 结构体定义 ==========
struct BossKilledInfo
{
	int32_t	BossId;
	int8_t	IsKilled;
};

struct BossKilledRewardInfo
{
	int8_t						IsGetReward;
	std::list<BossKilledInfo>	BossKeilled;

	bool SetBossKilled( int32_t nBossId )
	{
		for ( std::list<BossKilledInfo>::iterator iter = BossKeilled.begin(); iter != BossKeilled.end(); ++iter )
		{
			if ( iter->BossId == nBossId && iter->IsKilled == 0 )
			{
				iter->IsKilled = 1;
				return true;
			}
		}
		return false;
	}

	bool CanGetReward()
	{
		if ( IsGetReward != 0 )
		{
			return false;
		}
		for ( std::list<BossKilledInfo>::const_iterator iter = BossKeilled.begin(); iter != BossKeilled.end(); ++iter )
		{
			if ( iter->IsKilled == 0 )
			{
				return false;
			}
		}
		return !BossKeilled.empty();
	}
};

// ========== 模块类 ==========
class CBossKilledReward : public CExtSystemBase
{
public:
	CBossKilledReward(){}
	virtual ~CBossKilledReward(){}

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );

	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	int32_t		OnGetBossKilledReward( Answer::NetPacket* inPacket );
	void		AddBossKilled( int32_t nBossId );
	void		SendBossKilledInfo();
	void		GetBossKilledIcon( ShowIcon& icon );
	void		SendBossKilledIcon();
	bool		IsAllRewardGet();
	int32_t		CanGetRewardCount();

private:
	std::map<int8_t, BossKilledRewardInfo>	m_BossKilledRewardMap;
};

#endif //__TPOC_BOSS_KILLED_REWARD_H__
