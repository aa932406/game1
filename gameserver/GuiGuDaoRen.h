//////////////////////////////////////////////////////////////////////////
// 鬼谷道人系统 - 物品回收/装备传承/融合记录管理
// 单例模式，负责管理 NPC 交互的回收、BOSS 刷新和排行榜
//////////////////////////////////////////////////////////////////////////

#ifndef __GUI_GU_DAO_REN_H__
#define __GUI_GU_DAO_REN_H__

#include "stdafx.h"
#include "CfgData.h"

// 融合记录
struct RongHeRecord
{
	RongHeRecord()
		: nCid(0), nCostId(0), nGiveId(0), nSuccess(0), nTime(0)
	{
	}

	RongHeRecord(const RongHeRecord& other)
		: strName(other.strName), nCid(other.nCid), nCostId(other.nCostId),
		  nGiveId(other.nGiveId), nSuccess(other.nSuccess), nTime(other.nTime)
	{
	}

	~RongHeRecord() {}

	RongHeRecord& operator=(const RongHeRecord& other)
	{
		if (this != &other)
		{
			strName = other.strName;
			nCid = other.nCid;
			nCostId = other.nCostId;
			nGiveId = other.nGiveId;
			nSuccess = other.nSuccess;
			nTime = other.nTime;
		}
		return *this;
	}

	std::string	strName;
	CharId_t	nCid;
	int32_t		nCostId;
	int32_t		nGiveId;
	int32_t		nSuccess;
	int32_t		nTime;
};

// 刷新怪物配置（用于 GuiGuDaoRenCfg 内的 BOSS 刷新信息）
struct RefreshMonster
{
	int32_t BossId;
	int32_t nCount;
	int32_t AliveTime;
	int32_t GongGaoId;
};

// 装备回收排行榜
struct EquipBackRankCfg
{
	EquipBackRankCfg()
		: Cid(0), Count(0), Time(0)
	{
	}

	EquipBackRankCfg(const EquipBackRankCfg& other)
		: nName(other.nName), Cid(other.Cid), Count(other.Count), Time(other.Time)
	{
	}

	~EquipBackRankCfg() {}

	EquipBackRankCfg& operator=(const EquipBackRankCfg& other)
	{
		if (this != &other)
		{
			nName = other.nName;
			Cid = other.Cid;
			Count = other.Count;
			Time = other.Time;
		}
		return *this;
	}

	void PackageData(Answer::NetPacket* packet) const
	{
		packet->writeInt64(Cid);
		packet->writeUTF8(nName);
		packet->writeInt32(Count);
		packet->writeInt32(Time);
	}

	std::string	nName;
	CharId_t	Cid;
	int32_t		Count;
	int32_t		Time;
};

inline bool GreaterEquipBackRank(const EquipBackRankCfg& a, const EquipBackRankCfg& b)
{
	if (a.Count != b.Count) return a.Count > b.Count;
	return a.Time < b.Time;
}

class CGuiGuDaoRen
{
public:
	static CGuiGuDaoRen* instance()
	{
		static CGuiGuDaoRen s_instance;
		return &s_instance;
	}

public:
	CGuiGuDaoRen();
	~CGuiGuDaoRen();

	// === 物品回收（OnBackItem） ===
	int32_t	OnAskBackItemCount( Player* pPlayer, Answer::NetPacket* packet );
	int32_t	OnBackItem( Player* pPlayer, Answer::NetPacket* packet );
	void	SendBackItemCount( Player* pPlayer, int32_t NpcId );
	void	UpdateBackItemCount( int32_t NpcId );

	// === 装备回收（OnBackEquipCount） ===
	int32_t	OnAskBackEquipCount( Player* pPlayer, Answer::NetPacket* packet );
	int32_t	OnBackEquipCount( Player* pPlayer, Answer::NetPacket* packet );
	void	SendBackEquipCount( Player* pPlayer );
	void	UpdateEquipCount();

	int32_t	GetMaxCount();		// 根据开服天数计算最大回收次数

	// === 装备回收排行榜 ===
	int32_t	OnAskEquipBackRank( Player* pPlayer, Answer::NetPacket* packet );
	void	SendBackEquipRank( Player* pPlayer );
	void	UpdateRankDate( EquipBackRankCfg* pStu );

	// === 每日重置（OnNewMinute） ===
	void	OnNewMinute( int32_t nMinute );

	// === 融合记录（供 CRongHe 调用） ===
	int32_t	GetRongHeRate();						// 获取当前融合概率修正
	void	AddRongHeRecord( RongHeRecord* pRecord );	// 添加融合记录
	void	AddRongHeCount( int32_t nCostValue, int32_t nGetValue );	// 添加融合统计

	void	SendAllRongHeRecord( Player* pPlayer );			// 发送所有融合记录
	void	SendOneRongHeRecord( RongHeRecord* pRecord );	// 广播单条融合记录
	void	UpdateRongHeCount();							// 保存融合统计到DB
	void	SaveRecordToDB();								// 保存融合记录到DB

private:
	int32_t		m_CostCount;			// 累计消耗
	int32_t		m_GetCount;				// 累计获得
	int32_t		m_Rate;					// 当前概率修正(0/1)
	int32_t		EquipCount;				// 当前装备回收次数
	Answer::Mutex	m_RankLock;

	std::map<int32_t, int32_t>			BackItemCount;		// NpcId -> 回收计数
	std::list<RongHeRecord>				m_RongHeRecordList;	// 融合记录列表（最多20条）
	std::vector<EquipBackRankCfg>		m_EquipBackRank;	// 装备回收排行榜
};

#define GUI_GU_DAO_REN Answer::Singleton<CGuiGuDaoRen>::instance()

#endif // __GUI_GU_DAO_REN_H__
