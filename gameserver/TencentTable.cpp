#include "stdafx.h"
#include "TencentTable.h"
#include "ItemHelper.h"

using namespace std;

CfgTencentTable::CfgTencentTable()
{
}

CfgTencentTable::~CfgTencentTable()
{
}

MemChrBagVector CfgTencentTable::parseRewardString(const std::string& str)
{
	return CItemHelper::parseItemVectorString(str);
}

// ===== YellowReward.txt (newer gift) =====
void CfgTencentTable::InitYellowRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/YellowReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		// INT, STRING: Index, Reward
		m_YellowNewerGift.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
	}
}

// ===== YellowDailyReward.txt =====
void CfgTencentTable::InitYellowDailyRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowDailyReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/YellowDailyReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgYellowDailyGift stu;
		stu.nLevel = TabFile.Search_Posistion(i, 0)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
		stu.vVipReward = parseRewardString(TabFile.Search_Posistion(i, 2)->pString);
		m_YellowDailyGiftMap[stu.nLevel] = stu;
	}
}

// ===== YellowLevelReward.txt =====
void CfgTencentTable::InitYellowLevelRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowLevelReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/YellowLevelReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgYellowLevelGift stu;
		stu.nIndex = TabFile.Search_Posistion(i, 0)->iValue;
		stu.nMinLevel = TabFile.Search_Posistion(i, 1)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 2)->pString);
		stu.vVipReward = parseRewardString(TabFile.Search_Posistion(i, 3)->pString);
		m_YellowLevelGiftMap[stu.nIndex] = stu;
	}
}

// ===== BlueReward.txt (newer gift) =====
void CfgTencentTable::InitBlueRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/BlueReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		m_BlueNewerGift.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
	}
}

// ===== BlueDailyReward.txt =====
void CfgTencentTable::InitBlueDailyRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueDailyReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/BlueDailyReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgBlueDailyGift stu;
		stu.nLevel = TabFile.Search_Posistion(i, 0)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
		m_BlueDailyGiftMap[stu.nLevel] = stu;
	}
}

// ===== BlueLevelReward.txt =====
void CfgTencentTable::InitBlueLevelRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueLevelReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/BlueLevelReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgBlueLevelGift stu;
		stu.nIndex = TabFile.Search_Posistion(i, 0)->iValue;
		stu.nMinLevel = TabFile.Search_Posistion(i, 1)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 2)->pString);
		m_BlueLevelGiftMap[stu.nIndex] = stu;
	}
}

// ===== QQZone.txt =====
void CfgTencentTable::InitQQZoneRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QQZone.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/QQZone.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgQQZoneGift stu;
		stu.nIndex = TabFile.Search_Posistion(i, 0)->iValue;
		stu.nType = TabFile.Search_Posistion(i, 1)->iValue;
		stu.nSlot = TabFile.Search_Posistion(i, 2)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 3)->pString);
		stu.nCondition = TabFile.Search_Posistion(i, 4)->iValue;
		stu.sDesc = TabFile.Search_Posistion(i, 5)->pString;
		stu.nPic = TabFile.Search_Posistion(i, 6)->iValue;
		m_QQZoneGiftMap[stu.nIndex] = stu;
	}
}

// ===== QQGameDaTing.txt =====
void CfgTencentTable::InitQQGameRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QQGameDaTing.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/QQGameDaTing.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgQQGameGift stu;
		stu.nIndex = TabFile.Search_Posistion(i, 0)->iValue;
		stu.nType = TabFile.Search_Posistion(i, 1)->iValue;
		stu.nSlot = TabFile.Search_Posistion(i, 2)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 3)->pString);
		stu.nCondition = TabFile.Search_Posistion(i, 4)->iValue;
		m_QQGameGiftMap[stu.nIndex] = stu;
	}
}

// ===== TGPReward.txt (newer + daily by platform) =====
void CfgTencentTable::InitTGPRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/TGPReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgTGPGift stu;
		stu.sPf = TabFile.Search_Posistion(i, 0)->pString;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
		m_TGPGiftMap[stu.sPf] = stu;
	}
}

// ===== TGPDailyReward.txt =====
void CfgTencentTable::InitTGPDailyRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPDailyReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/TGPDailyReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgTGPGift stu;
		stu.sPf = TabFile.Search_Posistion(i, 0)->pString;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
		m_TGPGiftMap[stu.sPf] = stu;
	}
}

// ===== TGPLevelReward.txt =====
void CfgTencentTable::InitTGPLevelRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPLevelReward.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/TGPLevelReward.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgTGPLevelGift stu;
		stu.nIndex = TabFile.Search_Posistion(i, 0)->iValue;
		stu.nMinLevel = TabFile.Search_Posistion(i, 1)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 2)->pString);
		m_TGPLevelGiftMap[stu.nIndex] = stu;
	}
}

// ===== TencentSevenDayLogin.txt =====
void CfgTencentTable::InitTencentSevenDayLoginTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TencentSevenDayLogin.txt");
	if (!ret)
	{
		LOG_ERROR("open ./ServerConfig/Tables/TencentSevenDayLogin.txt failed");
		return;
	}
	int32_t nCount = TabFile.GetRecordsNum();
	int32_t nCol = TabFile.GetFieldsNum();
	if (nCol <= 0) return;
	for (int32_t i = 0; i < nCount; ++i)
	{
		CfgSevenDayLoginGift stu;
		stu.nDay = TabFile.Search_Posistion(i, 0)->iValue;
		stu.vReward = parseRewardString(TabFile.Search_Posistion(i, 1)->pString);
		m_SevenDayLoginGiftMap[stu.nDay] = stu;
	}
}

// ===== Getter implementations =====
const CfgYellowNewerGift* CfgTencentTable::GetYellowNewerGift() const
{
	if (m_YellowNewerGift.vReward.empty())
		return NULL;
	return &m_YellowNewerGift;
}

const CfgYellowDailyGift* CfgTencentTable::GetYellowDailyGift(int32_t nLevel) const
{
	CfgYellowDailyGiftMap::const_iterator it = m_YellowDailyGiftMap.find(nLevel);
	if (it != m_YellowDailyGiftMap.end())
		return &it->second;
	// fallback: find the highest level <= requested
	for (CfgYellowDailyGiftMap::const_reverse_iterator rit = m_YellowDailyGiftMap.rbegin();
		rit != m_YellowDailyGiftMap.rend(); ++rit)
	{
		if (rit->first <= nLevel)
			return &rit->second;
	}
	return NULL;
}

const CfgYellowLevelGift* CfgTencentTable::GetYellowLevelGift(int32_t nIndex) const
{
	CfgYellowLevelGiftMap::const_iterator it = m_YellowLevelGiftMap.find(nIndex);
	if (it != m_YellowLevelGiftMap.end())
		return &it->second;
	return NULL;
}

const CfgBlueNewerGift* CfgTencentTable::GetBlueNewerGift() const
{
	if (m_BlueNewerGift.vReward.empty())
		return NULL;
	return &m_BlueNewerGift;
}

const CfgBlueDailyGift* CfgTencentTable::GetBlueDailyGift(int32_t nLevel) const
{
	CfgBlueDailyGiftMap::const_iterator it = m_BlueDailyGiftMap.find(nLevel);
	if (it != m_BlueDailyGiftMap.end())
		return &it->second;
	// fallback
	for (CfgBlueDailyGiftMap::const_reverse_iterator rit = m_BlueDailyGiftMap.rbegin();
		rit != m_BlueDailyGiftMap.rend(); ++rit)
	{
		if (rit->first <= nLevel)
			return &rit->second;
	}
	return NULL;
}

const CfgBlueYearGift* CfgTencentTable::GetBlueYearGift() const
{
	if (m_BlueYearGift.vReward.empty())
		return NULL;
	return &m_BlueYearGift;
}

const CfgBlueHighGift* CfgTencentTable::GetBlueHighGift() const
{
	if (m_BlueHighGift.vReward.empty())
		return NULL;
	return &m_BlueHighGift;
}

const CfgBlueLevelGift* CfgTencentTable::GetBlueLevelGift(int32_t nIndex) const
{
	CfgBlueLevelGiftMap::const_iterator it = m_BlueLevelGiftMap.find(nIndex);
	if (it != m_BlueLevelGiftMap.end())
		return &it->second;
	return NULL;
}

const CfgQQZoneGift* CfgTencentTable::GetQQZoneGift(int32_t nIndex) const
{
	CfgQQZoneGiftMap::const_iterator it = m_QQZoneGiftMap.find(nIndex);
	if (it != m_QQZoneGiftMap.end())
		return &it->second;
	return NULL;
}

const CfgQQGameGift* CfgTencentTable::GetQQGameGift(int32_t nIndex) const
{
	CfgQQGameGiftMap::const_iterator it = m_QQGameGiftMap.find(nIndex);
	if (it != m_QQGameGiftMap.end())
		return &it->second;
	return NULL;
}

const CfgTGPGift* CfgTencentTable::GetTGPGift(const std::string& sPf) const
{
	CfgTGPGiftMap::const_iterator it = m_TGPGiftMap.find(sPf);
	if (it != m_TGPGiftMap.end())
		return &it->second;
	return NULL;
}

const CfgTGPLevelGift* CfgTencentTable::GetTGPLevelGift(int32_t nIndex) const
{
	CfgTGPLevelGiftMap::const_iterator it = m_TGPLevelGiftMap.find(nIndex);
	if (it != m_TGPLevelGiftMap.end())
		return &it->second;
	return NULL;
}

const CfgSevenDayLoginGift* CfgTencentTable::GetSevenDayLoginGift(int32_t nDay) const
{
	CfgSevenDayLoginGiftMap::const_iterator it = m_SevenDayLoginGiftMap.find(nDay);
	if (it != m_SevenDayLoginGiftMap.end())
		return &it->second;
	return NULL;
}
