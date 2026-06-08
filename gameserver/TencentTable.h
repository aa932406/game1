#pragma once

#include "Shared.h"
#include "DataStructs.h"

// ===== Yellow Gift Types =====
struct CfgYellowNewerGift
{
	MemChrBagVector vReward;
};

struct CfgYellowDailyGift
{
	int32_t nLevel;
	MemChrBagVector vReward;
	MemChrBagVector vVipReward;
};
typedef std::map<int32_t, CfgYellowDailyGift> CfgYellowDailyGiftMap;

struct CfgYellowLevelGift
{
	int32_t nIndex;
	int32_t nMinLevel;
	MemChrBagVector vReward;
	MemChrBagVector vVipReward;
};
typedef std::map<int32_t, CfgYellowLevelGift> CfgYellowLevelGiftMap;

// ===== Blue Gift Types =====
struct CfgBlueNewerGift
{
	MemChrBagVector vReward;
};

struct CfgBlueDailyGift
{
	int32_t nLevel;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, CfgBlueDailyGift> CfgBlueDailyGiftMap;

struct CfgBlueYearGift
{
	MemChrBagVector vReward;
};

struct CfgBlueHighGift
{
	MemChrBagVector vReward;
};

struct CfgBlueLevelGift
{
	int32_t nIndex;
	int32_t nMinLevel;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, CfgBlueLevelGift> CfgBlueLevelGiftMap;

// ===== QQ Gift Types =====
struct CfgQQZoneGift
{
	int32_t nIndex;
	int32_t nType;
	int32_t nSlot;
	MemChrBagVector vReward;
	int32_t nCondition;
	std::string sDesc;
	int32_t nPic;
};
typedef std::map<int32_t, CfgQQZoneGift> CfgQQZoneGiftMap;

struct CfgQQGameGift
{
	int32_t nIndex;
	int32_t nType;
	int32_t nSlot;
	MemChrBagVector vReward;
	int32_t nCondition;
};
typedef std::map<int32_t, CfgQQGameGift> CfgQQGameGiftMap;

// ===== TGP Gift Types =====
struct CfgTGPGift
{
	std::string sPf;
	MemChrBagVector vReward;
};
typedef std::map<std::string, CfgTGPGift> CfgTGPGiftMap;

struct CfgTGPLevelGift
{
	int32_t nIndex;
	int32_t nMinLevel;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, CfgTGPLevelGift> CfgTGPLevelGiftMap;

// ===== SevenDayLogin Gift =====
struct CfgSevenDayLoginGift
{
	int32_t nDay;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, CfgSevenDayLoginGift> CfgSevenDayLoginGiftMap;

// ===== Unified Config Table =====
class CfgTencentTable
{
public:
	CfgTencentTable();
	~CfgTencentTable();

	// Init methods
	void InitYellowRewardTable();
	void InitYellowDailyRewardTable();
	void InitYellowLevelRewardTable();
	void InitBlueRewardTable();
	void InitBlueDailyRewardTable();
	void InitBlueLevelRewardTable();
	void InitQQZoneRewardTable();
	void InitQQGameRewardTable();
	void InitTGPRewardTable();
	void InitTGPDailyRewardTable();
	void InitTGPLevelRewardTable();
	void InitTencentSevenDayLoginTable();

	// Get methods
	const CfgYellowNewerGift*	GetYellowNewerGift() const;
	const CfgYellowDailyGift*	GetYellowDailyGift(int32_t nLevel) const;
	const CfgYellowLevelGift*	GetYellowLevelGift(int32_t nIndex) const;
	const CfgBlueNewerGift*		GetBlueNewerGift() const;
	const CfgBlueDailyGift*		GetBlueDailyGift(int32_t nLevel) const;
	const CfgBlueYearGift*		GetBlueYearGift() const;
	const CfgBlueHighGift*		GetBlueHighGift() const;
	const CfgBlueLevelGift*		GetBlueLevelGift(int32_t nIndex) const;
	const CfgQQZoneGift*		GetQQZoneGift(int32_t nIndex) const;
	const CfgQQGameGift*		GetQQGameGift(int32_t nIndex) const;
	const CfgTGPGift*			GetTGPGift(const std::string& sPf) const;
	const CfgTGPLevelGift*		GetTGPLevelGift(int32_t nIndex) const;
	const CfgSevenDayLoginGift*	GetSevenDayLoginGift(int32_t nDay) const;
	const CfgQQZoneGiftMap&		GetQQZoneGiftMap() const { return m_QQZoneGiftMap; }
	const CfgQQGameGiftMap&		GetQQGameGiftMap() const { return m_QQGameGiftMap; }

private:
	MemChrBagVector parseRewardString(const std::string& str);

	CfgYellowNewerGift		m_YellowNewerGift;
	CfgYellowDailyGiftMap	m_YellowDailyGiftMap;
	CfgYellowLevelGiftMap	m_YellowLevelGiftMap;

	CfgBlueNewerGift		m_BlueNewerGift;
	CfgBlueDailyGiftMap		m_BlueDailyGiftMap;
	CfgBlueYearGift			m_BlueYearGift;
	CfgBlueHighGift			m_BlueHighGift;
	CfgBlueLevelGiftMap		m_BlueLevelGiftMap;

	CfgQQZoneGiftMap		m_QQZoneGiftMap;
	CfgQQGameGiftMap		m_QQGameGiftMap;
	CfgTGPGiftMap			m_TGPGiftMap;
	CfgTGPLevelGiftMap		m_TGPLevelGiftMap;
	CfgSevenDayLoginGiftMap	m_SevenDayLoginGiftMap;
};
