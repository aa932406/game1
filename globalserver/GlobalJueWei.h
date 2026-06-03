#ifndef  __GLOBAL_JUE_WEI_H__
#define  __GLOBAL_JUE_WEI_H__
#include "stdafx.h"
#include "SocialPlayer.h"
#define JUE_WEI_RANK_MAX_COUNT	20	//爵位排名20个
class CJueWeiInfo
{
public:
	CJueWeiInfo()
	{
		m_Charid		= 0;
		m_CharName		= "";	
		m_DonateMoney	= 0;	
		m_Rank			= 0;
		m_Sex			= 0;
	}
	bool operator > ( const CJueWeiInfo& stu ) const
	{
		return m_DonateMoney > stu.m_DonateMoney;
	}
	bool operator < ( const CJueWeiInfo & stu ) const
	{
		return m_DonateMoney < stu.m_DonateMoney;
	}
public:
	CharId_t			m_Charid;
	std::string			m_CharName;
	int8_t				m_Sex;
	int64_t				m_DonateMoney;			//铜钱
	int32_t				m_Rank;					//排名
};

typedef std::vector<CJueWeiInfo> JueWeiInfoVector;

class CGlobalJueWei
{
public:
	CGlobalJueWei();
	~CGlobalJueWei();
	void				Init();
	int32_t				OnUpdateDonateMoney( Answer::NetPacket* packet );
	int32_t				SendRankToGs( Answer::NetPacket* packet );
	int32_t				SendDonateRank( SocialPlayer* pPlayer );
	void				RefreshRank();
	void				SortVector(std::vector<CJueWeiInfo>& RankVct);
	void				SendRankToGs( CharId_t CharID, int32_t Rank, bool IsLogin= false );
private:
	JueWeiInfoVector	m_DonateVector;
};
#define GLOBAL_JUE_WEI Answer::Singleton<CGlobalJueWei>::instance()
#endif