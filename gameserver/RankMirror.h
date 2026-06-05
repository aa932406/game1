//////////////////////////////////////////////////////////////////////////
// 排行榜镜像 - 维护战力/等级/威望三个榜单的玩家排名数据
// 单例模式，通过 IM_SOCIAL_ALL_GAME_UPDATE_RANK 从 globalserver 接收更新
//////////////////////////////////////////////////////////////////////////

#ifndef __RANK_MIRROR_H__
#define __RANK_MIRROR_H__

#include "stdafx.h"
#include "DataStructs.h"

class CRankMirror
{
public:
	struct PlayerRankData
	{
		PlayerRankData()
		{
			nCharId			= 0;
			nBattleIndex	= 0;
			nLevelIndex		= 0;
			nWeiWangIndex	= 0;
			nJobBattleFirst = 0;
			nGuanWeiIndex	= 0;
		}

		CharId_t	nCharId;
		int32_t		nBattleIndex;
		int32_t		nLevelIndex;
		int32_t		nWeiWangIndex;
		int8_t		nJobBattleFirst;
		int32_t		nGuanWeiIndex;
	};

public:
	CRankMirror();
	~CRankMirror();

	// 查询接口
	int32_t	GetBattleIndex( CharId_t nCharId );
	int32_t	GetLevelIndex( CharId_t nCharId );
	bool	IsJobBattleFirst( CharId_t nCharId );
	int32_t	GetWeiWangIndex( CharId_t nCharId );

	// 从 globalserver 接收排行榜更新
	void	OnSocialUpdateRank( Answer::NetPacket* inPacket );

private:
	void	resetBattleRank();
	void	resetLevelRank();
	void	resetWeiWangRank();
	void	setBattleRank( CharId_t nCharId, int32_t nIndex, int8_t nJobFrist );
	void	setLevelRank( CharId_t nCharId, int32_t nIndex );
	void	setWeiWangRank( CharId_t nCharId, int32_t nIndex );

	// 标题/称号辅助（存根 - 待与 Title 系统集成）
	void	onCheckTitle( CharId_t nCharId, int32_t nTitleId, int8_t nParam );
	void	onRemoveTitle( CharId_t nCharId, int32_t nTitleId );

private:
	typedef std::map<CharId_t, PlayerRankData> PlayerRankMap;
	PlayerRankMap	m_mPlayerRank;			// 角色ID -> 排名数据

	CharId_t		m_vBattleRank[101];		// 战力排名 (1-100)
	CharId_t		m_vLevelRank[101];		// 等级排名 (1-100)
	CharId_t		m_vWeiWangRank[101];	// 威望排名 (1-100)

	int32_t			m_nLastRefreshTime;		// 上次刷新时间

	Answer::Mutex	m_lock;
};

#define RANK_MIRROR Answer::Singleton<CRankMirror>::instance()

#endif // __RANK_MIRROR_H__
