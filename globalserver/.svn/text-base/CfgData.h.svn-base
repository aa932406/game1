#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "DataStructs.h"

//wmf start
#define MAX_TOTOM_ADD_BATTLE		16

struct CfgTotom 
{
	int32_t	nActiveNeedPoints;
	int32_t nActiveNeedFamilyLevel;
};

class CfgFamily 
{
public:
	CfgFamily(){ CleanUp(); }
	~CfgFamily(){}
	void CleanUp()
	{
		nLevel		= 0;
		nExp		= 0;
		nBattle		= 0;
		nMaxMembers	= 0;
		nTotemCount	= 0;
		bzero( vPosition, sizeof( vPosition ) );
	}
	int32_t		nLevel;								// 等级
	int32_t		nExp;								// 需求贡献度
	int32_t		nBattle;							// 附加战斗力
	int32_t		nMaxMembers;						// 最大人数
	int32_t		nTotemCount;						// 最大图腾个数
	int32_t		vPosition[FAMILY_POSITION_COUNT];	// 职位人数
};

class CfgTotomOpen
{
public:
	CfgTotomOpen()
	{
		BaseId			= 0;	
		OpenCost		= -1;
		StarTotom		= 0;	
	}
	int32_t			BaseId;
	int32_t			OpenCost;				//无效了,配另一张表了
	int32_t			StarTotom;				//星级图腾
};
struct CfgOpenTotomCondition
{
	int32_t m_Num;
	int32_t m_OpenCost;
};
typedef std::map<int32_t, CfgOpenTotomCondition> OpenTotomConditionMap;


class CfgFamilyTable
{
public:
	CfgFamilyTable(){ CleanUp(); }
	~CfgFamilyTable(){}

	void CleanUp()
	{
		for ( int32_t i = 0; i < MAX_FAMILY_LEVEL; ++i )
		{
			m_vFamily[i].CleanUp();
		}
		bzero( m_vTotomActiveLevel, sizeof( m_vTotomActiveLevel ) );
		bzero( m_vTotomActiveCost, sizeof( m_vTotomActiveCost ) );
		bzero( m_vFamilyPosition, sizeof( m_vFamilyPosition ) );
	}

	bool Add( const CfgFamily& family )
	{
		m_vFamily[family.nLevel-1] = family;
		return true;
	}

	bool Add( int8_t nPosition, const CfgFamilyPosition& position )
	{
		if ( nPosition < 0 || nPosition >= FAMILY_POSITION_COUNT )
		{
			return false;
		}

		m_vFamilyPosition[nPosition] = position;
		return true;
	}

	bool AddTotomActiveCost( int8_t nBattle, int32_t nCost )
	{
		if ( nBattle <= 0 || nBattle >= MAX_TOTOM_ADD_BATTLE )
		{
			return false;
		}

		m_vTotomActiveCost[nBattle] = nCost;
		return true;
	}

	bool AddActiveTotom( int32_t nTotomId, int32_t nLevel )
	{
		if ( nTotomId <= 0 || nTotomId > MAX_PET_ID )
		{
			return false;
		}

		m_vTotomActiveLevel[nTotomId] = nLevel;
		return true;
	}

	const CfgFamily* GetFamilyInfo( int32_t nLevel ) const
	{
		if ( nLevel <= 0 || nLevel > MAX_FAMILY_LEVEL )
		{
			return NULL;
		}
		return &m_vFamily[nLevel-1];
	}

	int32_t GetFamilyLevel( int32_t Count ) const
	{
		int32_t i = 0;
		for ( ; i < MAX_FAMILY_LEVEL; ++i )
		{
			if ( m_vFamily[i].nExp > Count )
			{
				break;
			}
		}
		return i;
	}

	int32_t GetTotomActiveLevel( int32_t nTotomId ) const
	{
		if ( nTotomId <= 0 || nTotomId > MAX_PET_ID )
		{
			return 0;
		}
		return m_vTotomActiveLevel[nTotomId];
	}

	int32_t GetTotomActiveCost( int32_t nBattle ) const
	{
		if ( nBattle <= 0 || nBattle > MAX_TOTOM_ADD_BATTLE )
		{
			return -1;
		}
		return m_vTotomActiveCost[nBattle];
	}

	const CfgFamilyPosition* GetFamilyPosition( int8_t nPosition ) const
	{
		if ( nPosition < 0 || nPosition >= FAMILY_POSITION_COUNT )
		{
			return NULL;
		}
		return &m_vFamilyPosition[nPosition];
	}

	bool AddTotomOpenCfg( int32_t PetId, const CfgTotomOpen& stu )
	{
		m_vTotomOpen[PetId] = stu;
		return true;
	}

	const CfgTotomOpen* GetTotomOpenCfg( int32_t PetId ) const
	{
		if ( PetId <= 0 || PetId > MAX_PET_ID )
		{
			return NULL;
		}
		return &m_vTotomOpen[PetId];
	}
	
	bool IsFreeOpen( int32_t PetId ) const
	{
		if ( PetId <= 0 || PetId > MAX_PET_ID )
		{
			return false;
		}
		return m_vTotomOpen[PetId].OpenCost == 0;
	}

private:
	CfgFamily			m_vFamily[MAX_FAMILY_LEVEL];
	int32_t				m_vTotomActiveLevel[MAX_PET_ID+1];						// 图腾激活所需军团等级
	int32_t				m_vTotomActiveCost[MAX_TOTOM_ADD_BATTLE+1];				// 图腾激活战斗力所需军团资金
	CfgFamilyPosition	m_vFamilyPosition[FAMILY_POSITION_COUNT];				// 军团职位配置
	CfgTotomOpen		m_vTotomOpen[MAX_PET_ID+1];								// 图腾开启条件
};

struct HallOfFameReward 
{
	int32_t nIndexMin;
	int32_t nIndexMax;
	int32_t nHonor;
	ItemDataList items;
};
typedef std::list<HallOfFameReward> HallOfFameRewardList;

struct HallOfFameIndex
{
	int32_t nIndexMin;
	int32_t nIndexMax;
	int32_t nFrontMin;
	int32_t	nFrontMax;
	int32_t	nBackMin;
	int32_t	nBackMax;
};
typedef std::list<HallOfFameIndex> HallOfFameIndexList;

class CfgHallOfFameTable
{
public:
	CfgHallOfFameTable(){}
	~CfgHallOfFameTable(){}

public:
	void CleanUp()
	{
		m_rewards.clear();
	}
	
	void AddReward( const HallOfFameReward& reward )
	{
		m_rewards.push_back( reward );
	}

	const HallOfFameReward* GetReward( int32_t nIndex ) const
	{
		HallOfFameRewardList::const_iterator iter = m_rewards.begin();
		HallOfFameRewardList::const_iterator eiter = m_rewards.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nIndex >= iter->nIndexMin && nIndex <= iter->nIndexMax )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

	void AddIndex( const HallOfFameIndex& index )
	{
		m_indexs.push_back( index );
	}

	const HallOfFameIndex* GetIndex( int32_t nIndex ) const
	{
		HallOfFameIndexList::const_iterator iter = m_indexs.begin();
		HallOfFameIndexList::const_iterator eiter = m_indexs.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nIndex >= iter->nIndexMin && nIndex <= iter->nIndexMax )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

	void AddRobot( int32_t nIndex, int32_t nBattle )
	{
		m_mRobotsBattle[nIndex] = nBattle;
	}

	int32_t GetRobot( int32_t nIndex ) const
	{
		Int32Int32Map::const_iterator iter = m_mRobotsBattle.find( nIndex );
		if ( iter != m_mRobotsBattle.end() )
		{
			return iter->second;
		}
		return 0;
	}

private:
	HallOfFameRewardList	m_rewards;
	HallOfFameIndexList		m_indexs;
	Int32Int32Map			m_mRobotsBattle;
};
//wmf end

class CfgData
{
public:
	CfgData();
	~CfgData();

public:
	bool init();

public:
	const CfgFamilyTable&		GetFamilyTable() const;
	const CfgHallOfFameTable&	GetHallOfFameTable() const;
	const int32_t				GetOpenTotomNeedMoney( int32_t Num ) const;
	std::list<int32_t>			GetFreeOpenTotom();

private:
	void InitFamilyTable();					// 初始化军团表
	void InitFamilyPositionTable();			// 初始化军团职位表
	void InitFamilyTotomActiveCostTable();	// 初始化军图腾加持消耗表
	void InitFamilyTotomOpen();				// 初始化军团图腾激活
	void InitTotomOpen();					// 初始化图腾开启条件

	void InitHallOfFameRewardTable();		// 名人堂排名奖励
	void InitHallOfFameIndexTable();		// 名人堂挑战规则
	void InitHallOfFameRobotTable();		// 名人堂机器人属性

private:
	CfgFamilyTable				m_cfgFamilyTable;		// 军团表
	CfgHallOfFameTable			m_cfgHallOfFameTable;	// 名人堂表
	OpenTotomConditionMap		m_cfgOpenTotomMap;		// 开启军团图腾配置表
	std::list<int32_t>			m_FreeList;
};
#define CFG_DATA Answer::Singleton<CfgData>::instance()


