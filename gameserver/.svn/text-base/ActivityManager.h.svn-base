//////////////////////////////////////////////////////////////////////////
// 活动管理器
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_ACTIVITY_MANAGER_H__
#define __TPOC_ACTIVITY_MANAGER_H__

#include "Activity.h"


enum ActivityId
{
	JUN_TUAN_ZHAN_ID		= 1,		//军团战
	FEI_TIAN_SHENG_JV_ID    = 2,		//飞天神驹
	JUN_TUAN_ZHI_GUANG_ID	= 3,		//军团之光
	JUN_TUAN_ZHI_GUANG_ID2  = 4,		//军团之光2
	MO_LING_RU_QING_ID		= 5,		//魔灵入侵
	MO_LING_RU_QING_ID2		= 6,		//魔灵入侵2
	DA_TI_HUONG_DONG_ID		= 7,		//答题活动
	DA_TI_HUONG_DONG_ID2	= 8,		//答题活动2
	TIAN_JIANG_BAO_XIANG	= 9,		//天降宝箱
	CTERRITORYWAR_1			= 11,		//领地战
	CTERRITORYWAR_2			= 12,		//领地战
	CTERRITORYWAR_3			= 13,		//领地战
	CTERRITORYWAR_4			= 14,		//领地战
	CTERRITORYWAR_5			= 15,		//领地战
	SQIDER_QUEEN_ID_1		= 16,		//蜘蛛女王1
	SQIDER_QUEEN_ID_2		= 17,		//蜘蛛女王2
	SQIDER_QUEEN_ID_3		= 18,		//蜘蛛女王3
	SQIDER_QUEEN_ID_4		= 19,		//蜘蛛女王4
};

class CActivityManager
{
	typedef std::map<int32_t,CActivity*> ActivityMap;
public:
	CActivityManager();
	virtual ~CActivityManager();

public:
	void Init();
	void OnUpdate();

	void	SendActivityInfo( Player* player, int32_t nId );
	int32_t	GiveDailyReward( Player* player, int32_t nId );
	int32_t	HaveRewardCount( Player* Player, int32_t nId );
	void    NotifyActivityInfo( Player* player );
public:
	bool		IsActivityRunning(int32_t id);										
	void		AppendActivityState(Answer::NetPacket *packet);
	CActivity*	GetActivity( int32_t id );


	FamilyId_t	GetFamilyWarWinner();
	std::string GetFamilyWarLeaderName();
	std::string GetFamilyWarWinnerName();
	void		OnFamilyWarResult( int32_t nActId, FamilyId_t nFamilyId, int16_t nWinTimes , string FamilyName, string LeadyerName );
	void		OnTerritoryWarResult( int32_t nActId, std::string winners );
	void		GetActicityIconState( IconStateList& iconList );
	void		OnTerritoryWarInfo( Player* player );
	int8_t		GetTerritoryWarState();

	void		StopSqiderQueen();
private:
	Answer::Mutex	m_mutex;

	int32_t			m_nNowDay;
	ActivityMap		m_mActivity;

	FamilyId_t		m_nFamilyWarWinner;
	int32_t			m_nFamilyWarWinTimes;
};
#define ACTIVITY_MANAGER Answer::Singleton<CActivityManager>::instance()

#endif	//__TPOC_ACTIVITY_MANAGER_H__
