#pragma once

#include "ExtSystemBase.h"
#include "DataStructs.h"
#include "TencentTable.h"

struct TencentInfo
{
	std::string m_pf;				// platform
	int8_t m_bYellowVip;
	int8_t m_bYellowYearVip;
	int8_t m_bYellowHighVip;
	int8_t m_nYellowVipLevel;
	int8_t m_bBlueVip;
	int8_t m_bBlueYearVip;
	int8_t m_bBlueHighVip;
	int8_t m_nBlueVipLevel;
	int32_t m_nEndTime;

	TencentInfo()
		: m_bYellowVip(0), m_bYellowYearVip(0), m_bYellowHighVip(0), m_nYellowVipLevel(0)
		, m_bBlueVip(0), m_bBlueYearVip(0), m_bBlueHighVip(0), m_nBlueVipLevel(0)
		, m_nEndTime(0)
	{
	}

	int32_t GetEndTime() const { return m_nEndTime; }
};

class CTencent : public CExtSystemBase
{
public:
	CTencent();
	virtual ~CTencent();

	// CExtSystemBase overrides
	virtual void OnDaySwitch(int32_t nDiffDays);
	virtual void GetInterestsProtocol(ProcIdList& procList);
	virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

	// Public interface
	void InitTencentInfo(const TencentInfo* info);
	void UpdateTencentInfo(const TencentInfo* info);

	void OnReloadTencentInfo();
	bool IsYellowVip() const;
	bool IsYellowYearVip() const;
	bool IsYellowHighVip() const;
	int32_t GetYellowVipLevel() const;
	bool IsBlueVip() const;
	bool IsBlueYearVip() const;
	bool IsBlueHighVip() const;
	int32_t GetBlueVipLevel() const;
	bool isYellowEnter() const;
	bool isBlueEnter() const;
	bool isTGPEnter() const;

	void AppendInfo(Answer::NetPacket* packet);
	std::string GetPf() const;
	int32_t getLoginDay();
	bool isInSevenDay();
	bool needShowSevenDayIcon();
	bool IsSevenDayLoginExchangeDay();
	bool canGetYellowReward();
	bool canGetBlueReward();
	bool needShowBluePayIcon();

	// Icon methods
	void getYellowStoneIcon(ShowIcon& stu);
	void getYellowNewerIcon(ShowIcon& stu);
	void getBlueStoneIcon(ShowIcon& stu);
	void getBluePayIcon(ShowIcon& stu);
	void getSevenDayLoginIcon(ShowIcon& stu);
	void getTGPIcon(ShowIcon& stu);
	void getQZoneIcon(ShowIcon& stu);
	void getQQGameIcon(ShowIcon& stu);

	void GetYellowStoneIcon(IconStateList& IconList);
	void GetYellowNewerIcon(IconStateList& IconList);
	void GetBlueStoneIcon(IconStateList& IconList);
	void GetBluePayIcon(IconStateList& IconList);
	void GetSevenDayLoginIcon(IconStateList& IconList);
	void GetTGPIcon(IconStateList& IconList);
	void GetFriendIcon(IconStateList& IconList);
	void GetQZoneIcon(IconStateList& IconList);
	void GetQQGameIcon(IconStateList& IconList);

	void SendYellowStoneIcon();
	void SendYellowNewerIcon();
	void SendBlueStoneIcon();
	void SendBluePayIcon();
	void SendSevenDayLoginIcon();
	void SendTGPIcon();
	void SendQZoneIcon();
	void SendQQGameIcon();

	bool checkQQGiftCondition(int8_t nType, int32_t nCondition);

	// Request handlers
	int32_t onRequestYellowStoneInfo(Answer::NetPacket* inPacket);
	int32_t onRequestBlueStoneInfo(Answer::NetPacket* inPacket);
	int32_t onGetYellowNewerAward(Answer::NetPacket* inPacket);
	int32_t onGetYellowDailyAward(Answer::NetPacket* inPacket);
	int32_t onGetYellowYearAward(Answer::NetPacket* inPacket);
	int32_t onGetYellowLevelAward(Answer::NetPacket* inPacket);
	int32_t onGetBlueAward(Answer::NetPacket* inPacket);
	int32_t onGetBlueDailyAward(Answer::NetPacket* inPacket);
	int32_t onGetBlueYearAward(Answer::NetPacket* inPacket);
	int32_t onGetBlueLevelAward(Answer::NetPacket* inPacket);
	int32_t onGetBlueHighAward(Answer::NetPacket* inPacket);
	int32_t onGetQZoneGift(Answer::NetPacket* inPacket);
	int32_t onGetQQGameGift(Answer::NetPacket* inPacket);
	int32_t onGetTGPAward(Answer::NetPacket* inPacket);
	int32_t onGetTGPDailyAward(Answer::NetPacket* inPacket);
	int32_t onGetTGPLevelAward(Answer::NetPacket* inPacket);
	int32_t onRequestTGPInfo(Answer::NetPacket* inPacket);
	int32_t onRequestSevenDayLoginInfo(Answer::NetPacket* inPacket);
	int32_t onGetSevenDayLoginReward(Answer::NetPacket* inPacket);

private:
	void resetQZoneDailyReward();
	void resetQQGameDailyReward();

protected:
	void sendPlayerIcon(const ShowIcon& stu);

private:
	TencentInfo m_info;
	Player* m_pPlayer;
	CfgTencentTable m_tables;
	void InitTables();
};
