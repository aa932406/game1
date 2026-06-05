//////////////////////////////////////////////////////////////////////////
// V计划系统 - 跨平台奖励系统
// 包含：V计划、迅雷、YY语音、鲁大师、SG游戏、神武VIP等
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_VPLAN_H__
#define __TPOC_VPLAN_H__

#include "ExtSystemBase.h"
#include "DataStruct.h"

namespace Answer { class NetPacket; }
class Player;
struct CfgVplan;
struct CfgYYVip;
struct CfgXunLei;
struct CfgLuDaShi;
struct CfgSwVipReward;
struct CfgYYGameApp;
struct CfgSgGameApp;

class CVplan : public CExtSystemBase
{
friend class Player;
public:
	CVplan();
	virtual ~CVplan();

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	OnWeekSwitch( int32_t nDiffWeeks );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	// V计划核心
	void		AddAttr();
	int32_t		GetExpRatio();
	void		SendVplanInfo();
	void		SendVplanIcon();
	bool		HaveVplanGift();
	int32_t		OnGetReward( Answer::NetPacket* inPacket );
	void		GetVplanIconStu( VplanIconStu& stu );
	int8_t		GetVplanIconState();

	// 迅雷
	bool		HaveXunLeiVipReward();
	bool		IsGetAllXunLeiReward();
	void		SendXunLieInfo();
	void		SendXunLeiIcon();
	void		GetXunLeiIconState( int8_t& nState );
	void		GetXunLeiIconStu( XunLeiIconStu& stu );
	int32_t		OnGetXunLeiReward( Answer::NetPacket* inPacket );
	int32_t		GetXunLeiDownlondIcon();
	int32_t		GetXunLeiVipIcon();
	int32_t		GetXunLeiDaTingIcon();

	// YY语音
	void		SendYYInfo();
	void		SendYYVipInfo();
	void		SendYYVipIcon();
	bool		HaveYYVipLeftGift();
	bool		HaveYYLevelReward();
	void		GetYYVipIconState( int8_t& nState );
	void		GetYYVipIconStu( YYVipIconStu& stu );
	void		AppendYYInfo( Answer::NetPacket* packet );
	int32_t		OnGetYYLevelReward( Answer::NetPacket* inPacket );
	int32_t		OnGetYYVipGift( Answer::NetPacket* inPacket );
	int32_t		OnLoginFromYYgameApp( Answer::NetPacket* inPacket );

	// 鲁大师
	void		SendLuDaShiVipInfo();
	void		SendLuDaShiIcon();
	bool		HaveLuDaShiVipLeftGift();
	void		GetLuDaShiIconState( int8_t& nState );
	void		GetLuDaShiStu( LuDaShiIconStu& stu );
	int32_t		OnGetLuDaShiVipGift( Answer::NetPacket* inPacket );

	// SG游戏
	void		SendSgGameAppInfo();
	void		SendSgDownLoadIcon();
	bool		HaveSgDownLoadGift();
	bool		HaveSgGameAppReward();
	void		GetSgDownLoadIconStu( SgDownLoadIconStu& stu );
	int32_t		GetSgDownLoadIocnState();
	int32_t		OnGetSgGameApp( Answer::NetPacket* inPacket );

	// 神武VIP
	void		SendSwVipReward();
	void		SendSwVipIcon();
	void		SendSwVipBarIcon();
	bool		HaveEveryDayGift();
	bool		HaveLevelGift();
	bool		checkSwVipRewardCondition();
	bool		isGetAllSwVipReward();
	bool		checkSwBarRewardCondition();
	bool		isGetAllSwVipBarReward();
	void		CheckSwBarLoginCount();
	void		resetSwVipDailyReward();
	void		resetSwBarDailyReward();
	void		getSwVipIconStu( SwVipIconStu& stu );
	int32_t		GetSwVipIconState();
	void		getSwVipBarIconStu( SwVipBarIconStu& stu );
	int32_t		GetSwVipBarIconState();
	int32_t		getSwVipRewardCount();
	int32_t		getSwVipBarRewardCount();
	void		AppendSwVipInfo( Answer::NetPacket* packet );
	int32_t		OnGetSWVipReward( Answer::NetPacket* inPacket );
	int32_t		OnGetSWVipBarReward( Answer::NetPacket* inPacket );

private:
	Player*		m_pPlayer;

	// V计划数据
	int32_t		m_VplanType;
	int32_t		m_VplanLevel;

	// 神武VIP
	int32_t		m_nSwVipLevel;
	int8_t		m_bSwVipBar;

	// YY语音
	int32_t		m_YyLevel;
	int32_t		m_YyVipLevel;
	int32_t		m_YySuperLevel;
	int8_t		m_fromLYGameApp;

	// SG游戏
	int32_t		m_SgHallLevel;
	std::string	m_strSGPf;

	// 迅雷
	int32_t		m_XlNxLevel;

	// 平台
	int32_t		m_PlatformVip;
	int32_t		m_PlatformSuperVip;
};

#endif	//__TPOC_VPLAN_H__
