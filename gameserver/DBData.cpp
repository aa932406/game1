#include "stdafx.h"
#include "DBData.h"
#include "DBService.h"

using namespace Answer;


BossKilledRewardData::BossKilledRewardData()
{
	CleanUp();
}

BossKilledRewardData::~BossKilledRewardData()
{
}

void BossKilledRewardData::CleanUp()
{
	RewardString.clear();
}

void BossKilledRewardData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_boss_killed` (`cid`,`reward_info`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `reward_info`='%s'",
		(long long)nCid, RewardString.c_str(), RewardString.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool BossKilledRewardData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_boss_killed` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		RewardString = result.getStringValue("reward_info", "");
	}
	return true;
}

void BossKilledRewardData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(RewardString);
}

void BossKilledRewardData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); RewardString = tmp; }
}

CFaBaoData::CFaBaoData()
{
	CleanUp();
}

CFaBaoData::~CFaBaoData()
{
}

void CFaBaoData::CleanUp()
{
	m_FaBao = 0;
	m_FaBaoRes = 0;
}

void CFaBaoData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_fabao` (`cid`,`FaBaoLevel`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `FaBaoLevel`='%s'",
		(long long)nCid, RewardString.c_str(), RewardString.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CFaBaoData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_fabao` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		RewardString = result.getStringValue("FaBaoLevel", "");
	}
	return true;
}

void CFaBaoData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	for (int i = 0; i < 4; i++) packet->writeInt32(m_FaBao[i]);
	for (int i = 0; i < 4; i++) packet->writeInt32(m_FaBaoRes[i]);
}

void CFaBaoData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	for (int i = 0; i < 4; i++) m_FaBao[i] = inPacket->readInt32();
	for (int i = 0; i < 4; i++) m_FaBaoRes[i] = inPacket->readInt32();
}

CGoblinData::CGoblinData()
{
	CleanUp();
}

CGoblinData::~CGoblinData()
{
}

void CGoblinData::CleanUp()
{
	strData.clear();
}

void CGoblinData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_goblin` (`cid`,`data`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `data`='%s'",
		(long long)nCid, strData.c_str(), strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CGoblinData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_goblin` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strData = result.getStringValue("data", "");
	}
	return true;
}

void CGoblinData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strData);
}

void CGoblinData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

CHuoYueDuData::CHuoYueDuData()
{
	CleanUp();
}

CHuoYueDuData::~CHuoYueDuData()
{
}

void CHuoYueDuData::CleanUp()
{
	nHuoYueDu = 0;
	nTodayHuoYueDu = 0;
	nLastTime = 0;
	strRewards.clear();
}

void CHuoYueDuData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_huoyuedu` (`cid`,`huoyuedu`,`today_huoyuedu`,`last_time`,`rewards`) VALUES (%lld,%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `huoyuedu`=%lld,`today_huoyuedu`=%lld,`last_time`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nHuoYueDu,(long long)nTodayHuoYueDu,(long long)nLastTime,strRewards.c_str(), (long long)nHuoYueDu,(long long)nTodayHuoYueDu,(long long)nLastTime,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CHuoYueDuData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_huoyuedu` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nHuoYueDu = result.getIntValue("huoyuedu", 0);
		nTodayHuoYueDu = result.getIntValue("today_huoyuedu", 0);
		nLastTime = result.getIntValue("last_time", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void CHuoYueDuData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nHuoYueDu);
	packet->writeInt32(nTodayHuoYueDu);
	packet->writeInt32(nLastTime);
	packet->writeUTF8(strRewards);
}

void CHuoYueDuData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nHuoYueDu = inPacket->readInt32();
	nTodayHuoYueDu = inPacket->readInt32();
	nLastTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

CJueWeiData::CJueWeiData()
{
	CleanUp();
}

CJueWeiData::~CJueWeiData()
{
}

void CJueWeiData::CleanUp()
{
	nJueWeiLevel = 0;
	nJueWeiExp = 0;
	strRewards.clear();
}

void CJueWeiData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_juewei` (`cid`,`level`,`exp`,`rewards`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `level`=%lld,`exp`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nJueWeiLevel,(long long)nJueWeiExp,strRewards.c_str(), (long long)nJueWeiLevel,(long long)nJueWeiExp,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CJueWeiData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_juewei` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nJueWeiLevel = result.getIntValue("level", 0);
		nJueWeiExp = result.getIntValue("exp", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void CJueWeiData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nJueWeiLevel);
	packet->writeInt32(nJueWeiExp);
	packet->writeUTF8(strRewards);
}

void CJueWeiData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nJueWeiLevel = inPacket->readInt32();
	nJueWeiExp = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

CMonthlyChouJiangData::CMonthlyChouJiangData()
{
	CleanUp();
}

CMonthlyChouJiangData::~CMonthlyChouJiangData()
{
}

void CMonthlyChouJiangData::CleanUp()
{
	nFreeCount = 0;
	nTotalCount = 0;
	nLastFreeTime = 0;
	strRewards.clear();
}

void CMonthlyChouJiangData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_monthly_choujiang` (`cid`,`free_count`,`total_count`,`last_free_time`,`rewards`) VALUES (%lld,%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `free_count`=%lld,`total_count`=%lld,`last_free_time`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nFreeCount,(long long)nTotalCount,(long long)nLastFreeTime,strRewards.c_str(), (long long)nFreeCount,(long long)nTotalCount,(long long)nLastFreeTime,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CMonthlyChouJiangData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_monthly_choujiang` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nFreeCount = result.getIntValue("free_count", 0);
		nTotalCount = result.getIntValue("total_count", 0);
		nLastFreeTime = result.getIntValue("last_free_time", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void CMonthlyChouJiangData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nFreeCount);
	packet->writeInt32(nTotalCount);
	packet->writeInt32(nLastFreeTime);
	packet->writeUTF8(strRewards);
}

void CMonthlyChouJiangData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nFreeCount = inPacket->readInt32();
	nTotalCount = inPacket->readInt32();
	nLastFreeTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

CSevenDayData::CSevenDayData()
{
	CleanUp();
}

CSevenDayData::~CSevenDayData()
{
}

void CSevenDayData::CleanUp()
{
	nDayIndex = 0;
	strRewards.clear();
}

void CSevenDayData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_seven_day` (`cid`,`day_index`,`rewards`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `day_index`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nDayIndex,strRewards.c_str(), (long long)nDayIndex,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CSevenDayData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_seven_day` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nDayIndex = result.getIntValue("day_index", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void CSevenDayData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nDayIndex);
	packet->writeUTF8(strRewards);
}

void CSevenDayData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nDayIndex = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

CShiZhuangData::CShiZhuangData()
{
	CleanUp();
}

CShiZhuangData::~CShiZhuangData()
{
}

void CShiZhuangData::CleanUp()
{
	nShiZhuangId = 0;
	nLevel = 0;
	strData.clear();
}

void CShiZhuangData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_shizhuang` (`cid`,`shizhuang_id`,`level`,`data`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `shizhuang_id`=%lld,`level`=%lld,`data`='%s'",
		(long long)nCid, (long long)nShiZhuangId,(long long)nLevel,strData.c_str(), (long long)nShiZhuangId,(long long)nLevel,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CShiZhuangData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_shizhuang` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nShiZhuangId = result.getIntValue("shizhuang_id", 0);
		nLevel = result.getIntValue("level", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void CShiZhuangData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nShiZhuangId);
	packet->writeInt32(nLevel);
	packet->writeUTF8(strData);
}

void CShiZhuangData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nShiZhuangId = inPacket->readInt32();
	nLevel = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

CVplanData::CVplanData()
{
	CleanUp();
}

CVplanData::~CVplanData()
{
}

void CVplanData::CleanUp()
{
	nVplanId = 0;
	nLevel = 0;
	nExp = 0;
	strRewards.clear();
}

void CVplanData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_vplan` (`cid`,`vplan_id`,`level`,`exp`,`rewards`) VALUES (%lld,%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `vplan_id`=%lld,`level`=%lld,`exp`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nVplanId,(long long)nLevel,(long long)nExp,strRewards.c_str(), (long long)nVplanId,(long long)nLevel,(long long)nExp,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CVplanData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_vplan` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nVplanId = result.getIntValue("vplan_id", 0);
		nLevel = result.getIntValue("level", 0);
		nExp = result.getIntValue("exp", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void CVplanData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nVplanId);
	packet->writeInt32(nLevel);
	packet->writeInt32(nExp);
	packet->writeUTF8(strRewards);
}

void CVplanData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nVplanId = inPacket->readInt32();
	nLevel = inPacket->readInt32();
	nExp = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

CharFamilyDBData::CharFamilyDBData()
{
	CleanUp();
}

CharFamilyDBData::~CharFamilyDBData()
{
}

void CharFamilyDBData::CleanUp()
{
	nContribution = 0;
	nTotalContribution = 0;
	strData.clear();
}

void CharFamilyDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_family` (`cid`,`contribution`,`total_contribution`,`data`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `contribution`=%lld,`total_contribution`=%lld,`data`='%s'",
		(long long)nCid, (long long)nContribution,(long long)nTotalContribution,strData.c_str(), (long long)nContribution,(long long)nTotalContribution,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CharFamilyDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_family` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nContribution = result.getIntValue("contribution", 0);
		nTotalContribution = result.getIntValue("total_contribution", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void CharFamilyDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nContribution);
	packet->writeInt32(nTotalContribution);
	packet->writeUTF8(strData);
}

void CharFamilyDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nContribution = inPacket->readInt32();
	nTotalContribution = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

CharWingDBData::CharWingDBData()
{
	CleanUp();
}

CharWingDBData::~CharWingDBData()
{
}

void CharWingDBData::CleanUp()
{
	nWingId = 0;
	nLevel = 0;
	strData.clear();
}

void CharWingDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_wing` (`cid`,`wing_id`,`level`,`data`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `wing_id`=%lld,`level`=%lld,`data`='%s'",
		(long long)nCid, (long long)nWingId,(long long)nLevel,strData.c_str(), (long long)nWingId,(long long)nLevel,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CharWingDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_wing` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nWingId = result.getIntValue("wing_id", 0);
		nLevel = result.getIntValue("level", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void CharWingDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nWingId);
	packet->writeInt32(nLevel);
	packet->writeUTF8(strData);
}

void CharWingDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nWingId = inPacket->readInt32();
	nLevel = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

CharWishDBData::CharWishDBData()
{
	CleanUp();
}

CharWishDBData::~CharWishDBData()
{
}

void CharWishDBData::CleanUp()
{
	strWishes.clear();
}

void CharWishDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_wish` (`cid`,`wishes`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `wishes`='%s'",
		(long long)nCid, strWishes.c_str(), strWishes.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool CharWishDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_wish` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strWishes = result.getStringValue("wishes", "");
	}
	return true;
}

void CharWishDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strWishes);
}

void CharWishDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strWishes = tmp; }
}

ChouJiangData::ChouJiangData()
{
	CleanUp();
}

ChouJiangData::~ChouJiangData()
{
}

void ChouJiangData::CleanUp()
{
	nFreeCount = 0;
	nLastFreeTime = 0;
	strRewards.clear();
}

void ChouJiangData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_choujiang` (`cid`,`free_count`,`last_free_time`,`rewards`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `free_count`=%lld,`last_free_time`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nFreeCount,(long long)nLastFreeTime,strRewards.c_str(), (long long)nFreeCount,(long long)nLastFreeTime,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool ChouJiangData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_choujiang` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nFreeCount = result.getIntValue("free_count", 0);
		nLastFreeTime = result.getIntValue("last_free_time", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void ChouJiangData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nFreeCount);
	packet->writeInt32(nLastFreeTime);
	packet->writeUTF8(strRewards);
}

void ChouJiangData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nFreeCount = inPacket->readInt32();
	nLastFreeTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

CurrencyDBData::CurrencyDBData()
{
	CleanUp();
}

CurrencyDBData::~CurrencyDBData()
{
}

void CurrencyDBData::CleanUp()
{
	vCurrency = 0;
}

void CurrencyDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_char_currency` (`cid`) VALUES (%lld) ON DUPLICATE KEY UPDATE `cid`=%lld",
		(long long)nCid, (long long)nCid);
	sqls->push_back(std::string((char*)szSQL));
}

bool CurrencyDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_char_currency` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
	}
	return true;
}

void CurrencyDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	for (int i = 0; i < 12; i++) packet->writeInt64(vCurrency[i]);
}

void CurrencyDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	for (int i = 0; i < 12; i++) vCurrency[i] = inPacket->readInt64();
}

DailyActivityData::DailyActivityData()
{
	CleanUp();
}

DailyActivityData::~DailyActivityData()
{
}

void DailyActivityData::CleanUp()
{
	nTodayActive = 0;
	nTotalActive = 0;
	strRewards.clear();
}

void DailyActivityData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_daily_activity` (`cid`,`today_active`,`total_active`,`rewards`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `today_active`=%lld,`total_active`=%lld,`rewards`='%s'",
		(long long)nCid, (long long)nTodayActive,(long long)nTotalActive,strRewards.c_str(), (long long)nTodayActive,(long long)nTotalActive,strRewards.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool DailyActivityData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_daily_activity` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nTodayActive = result.getIntValue("today_active", 0);
		nTotalActive = result.getIntValue("total_active", 0);
		strRewards = result.getStringValue("rewards", "");
	}
	return true;
}

void DailyActivityData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nTodayActive);
	packet->writeInt32(nTotalActive);
	packet->writeUTF8(strRewards);
}

void DailyActivityData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nTodayActive = inPacket->readInt32();
	nTotalActive = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strRewards = tmp; }
}

EquipRongHeData::EquipRongHeData()
{
	CleanUp();
}

EquipRongHeData::~EquipRongHeData()
{
}

void EquipRongHeData::CleanUp()
{
	strData.clear();
}

void EquipRongHeData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_equip_ronghe` (`cid`,`data`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `data`='%s'",
		(long long)nCid, strData.c_str(), strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool EquipRongHeData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_equip_ronghe` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strData = result.getStringValue("data", "");
	}
	return true;
}

void EquipRongHeData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strData);
}

void EquipRongHeData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

ExchangeDBData::ExchangeDBData()
{
	CleanUp();
}

ExchangeDBData::~ExchangeDBData()
{
}

void ExchangeDBData::CleanUp()
{
	nCount = 0;
	strData.clear();
}

void ExchangeDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_exchange` (`cid`,`count`,`data`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `count`=%lld,`data`='%s'",
		(long long)nCid, (long long)nCount,strData.c_str(), (long long)nCount,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool ExchangeDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_exchange` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nCount = result.getIntValue("count", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void ExchangeDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nCount);
	packet->writeUTF8(strData);
}

void ExchangeDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nCount = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

MagicBoxDBData::MagicBoxDBData()
{
	CleanUp();
}

MagicBoxDBData::~MagicBoxDBData()
{
}

void MagicBoxDBData::CleanUp()
{
	nCombiPoints = 0;
	nLastReviveTime = 0;
	strActiveScrolls.clear();
	strSuccessIds.clear();
}

void MagicBoxDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_char_magic_box` (`cid`,`combi_points`,`revive_time`,`active_scrolls`,`success_ids`) VALUES (%lld,%lld,%lld,'%s','%s') ON DUPLICATE KEY UPDATE `combi_points`=%lld,`revive_time`=%lld,`active_scrolls`='%s',`success_ids`='%s'",
		(long long)nCid, (long long)nCombiPoints,(long long)nLastReviveTime,strActiveScrolls.c_str(),strSuccessIds.c_str(), (long long)nCombiPoints,(long long)nLastReviveTime,strActiveScrolls.c_str(),strSuccessIds.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MagicBoxDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_char_magic_box` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nCombiPoints = result.getIntValue("combi_points", 0);
		nLastReviveTime = result.getIntValue("revive_time", 0);
		strActiveScrolls = result.getStringValue("active_scrolls", "");
		strSuccessIds = result.getStringValue("success_ids", "");
	}
	return true;
}

void MagicBoxDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nCombiPoints);
	packet->writeInt32(nLastReviveTime);
	packet->writeUTF8(strActiveScrolls);
	packet->writeUTF8(strSuccessIds);
}

void MagicBoxDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nCombiPoints = inPacket->readInt32();
	nLastReviveTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strActiveScrolls = tmp; }
	{ std::string tmp; inPacket->readUTF8(tmp); strSuccessIds = tmp; }
}

MailDBData::MailDBData()
{
	CleanUp();
}

MailDBData::~MailDBData()
{
}

void MailDBData::CleanUp()
{
	nMailId = 0;
	nType = 0;
	nTime = 0;
	strSender.clear();
	strTitle.clear();
	strContent.clear();
	strItems.clear();
}

void MailDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_mail` (`cid`,`mail_id`,`type`,`time`,`sender`,`title`,`content`,`items`) VALUES (%lld,%lld,%lld,%lld,'%s','%s','%s','%s') ON DUPLICATE KEY UPDATE `mail_id`=%lld,`type`=%lld,`time`=%lld,`sender`='%s',`title`='%s',`content`='%s',`items`='%s'",
		(long long)nCid, (long long)nMailId,(long long)nType,(long long)nTime,strSender.c_str(),strTitle.c_str(),strContent.c_str(),strItems.c_str(), (long long)nMailId,(long long)nType,(long long)nTime,strSender.c_str(),strTitle.c_str(),strContent.c_str(),strItems.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MailDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_mail` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nMailId = result.getIntValue("mail_id", 0);
		nType = result.getIntValue("type", 0);
		nTime = result.getIntValue("time", 0);
		strSender = result.getStringValue("sender", "");
		strTitle = result.getStringValue("title", "");
		strContent = result.getStringValue("content", "");
		strItems = result.getStringValue("items", "");
	}
	return true;
}

void MailDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nMailId);
	packet->writeInt32(nType);
	packet->writeInt32(nTime);
	packet->writeUTF8(strSender);
	packet->writeUTF8(strTitle);
	packet->writeUTF8(strContent);
	packet->writeUTF8(strItems);
}

void MailDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nMailId = inPacket->readInt32();
	nType = inPacket->readInt32();
	nTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strSender = tmp; }
	{ std::string tmp; inPacket->readUTF8(tmp); strTitle = tmp; }
	{ std::string tmp; inPacket->readUTF8(tmp); strContent = tmp; }
	{ std::string tmp; inPacket->readUTF8(tmp); strItems = tmp; }
}

MemAttrData::MemAttrData()
{
	CleanUp();
}

MemAttrData::~MemAttrData()
{
}

void MemAttrData::CleanUp()
{
	nAttr = 0;
}

void MemAttrData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_attr` (`cid`) VALUES (%lld) ON DUPLICATE KEY UPDATE `cid`=%lld",
		(long long)nCid, (long long)nCid);
	sqls->push_back(std::string((char*)szSQL));
}

bool MemAttrData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_attr` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
	}
	return true;
}

void MemAttrData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	for (int i = 0; i < 32; i++) packet->writeInt32(nAttr[i]);
}

void MemAttrData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	for (int i = 0; i < 32; i++) nAttr[i] = inPacket->readInt32();
}

MemCharacterData::MemCharacterData()
{
	CleanUp();
}

MemCharacterData::~MemCharacterData()
{
}

void MemCharacterData::CleanUp()
{
	nLevel = 0;
	nExp = 0;
	nJob = 0;
}

void MemCharacterData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_character` (`cid`,`level`,`exp`,`job`) VALUES (%lld,%lld,%lld,%lld) ON DUPLICATE KEY UPDATE `level`=%lld,`exp`=%lld,`job`=%lld",
		(long long)nCid, (long long)nLevel,(long long)nExp,(long long)nJob, (long long)nLevel,(long long)nExp,(long long)nJob);
	sqls->push_back(std::string((char*)szSQL));
}

bool MemCharacterData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_character` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nLevel = result.getIntValue("level", 0);
		nExp = result.getIntValue("exp", 0);
		nJob = result.getIntValue("job", 0);
	}
	return true;
}

void MemCharacterData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nLevel);
	packet->writeInt32(nExp);
	packet->writeInt32(nJob);
}

void MemCharacterData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nLevel = inPacket->readInt32();
	nExp = inPacket->readInt32();
	nJob = inPacket->readInt32();
}

MemChrActionData::MemChrActionData()
{
	CleanUp();
}

MemChrActionData::~MemChrActionData()
{
}

void MemChrActionData::CleanUp()
{
	nActionId = 0;
	nCount = 0;
	nLastTime = 0;
}

void MemChrActionData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_action` (`cid`,`action_id`,`count`,`last_time`) VALUES (%lld,%lld,%lld,%lld) ON DUPLICATE KEY UPDATE `action_id`=%lld,`count`=%lld,`last_time`=%lld",
		(long long)nCid, (long long)nActionId,(long long)nCount,(long long)nLastTime, (long long)nActionId,(long long)nCount,(long long)nLastTime);
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrActionData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_action` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nActionId = result.getIntValue("action_id", 0);
		nCount = result.getIntValue("count", 0);
		nLastTime = result.getIntValue("last_time", 0);
	}
	return true;
}

void MemChrActionData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nActionId);
	packet->writeInt32(nCount);
	packet->writeInt32(nLastTime);
}

void MemChrActionData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nActionId = inPacket->readInt32();
	nCount = inPacket->readInt32();
	nLastTime = inPacket->readInt32();
}

MemChrAutoFightData::MemChrAutoFightData()
{
	CleanUp();
}

MemChrAutoFightData::~MemChrAutoFightData()
{
}

void MemChrAutoFightData::CleanUp()
{
	nEnabled = 0;
	nEndTime = 0;
}

void MemChrAutoFightData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_auto_fight` (`cid`,`enabled`,`end_time`) VALUES (%lld,%lld,%lld) ON DUPLICATE KEY UPDATE `enabled`=%lld,`end_time`=%lld",
		(long long)nCid, (long long)nEnabled,(long long)nEndTime, (long long)nEnabled,(long long)nEndTime);
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrAutoFightData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_auto_fight` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nEnabled = result.getIntValue("enabled", 0);
		nEndTime = result.getIntValue("end_time", 0);
	}
	return true;
}

void MemChrAutoFightData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nEnabled);
	packet->writeInt32(nEndTime);
}

void MemChrAutoFightData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nEnabled = inPacket->readInt32();
	nEndTime = inPacket->readInt32();
}

MemChrBagData::MemChrBagData()
{
	CleanUp();
}

MemChrBagData::~MemChrBagData()
{
}

void MemChrBagData::CleanUp()
{
}

void MemChrBagData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_bag` (`cid`) VALUES (%lld) ON DUPLICATE KEY UPDATE `cid`=%lld",
		(long long)nCid, (long long)nCid);
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrBagData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_bag` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
	}
	return true;
}

void MemChrBagData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
}

void MemChrBagData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
}

MemChrBuffData::MemChrBuffData()
{
	CleanUp();
}

MemChrBuffData::~MemChrBuffData()
{
}

void MemChrBuffData::CleanUp()
{
	strBuffs.clear();
}

void MemChrBuffData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_buff` (`cid`,`buffs`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `buffs`='%s'",
		(long long)nCid, strBuffs.c_str(), strBuffs.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrBuffData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_buff` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strBuffs = result.getStringValue("buffs", "");
	}
	return true;
}

void MemChrBuffData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strBuffs);
}

void MemChrBuffData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strBuffs = tmp; }
}

MemChrDepotData::MemChrDepotData()
{
	CleanUp();
}

MemChrDepotData::~MemChrDepotData()
{
}

void MemChrDepotData::CleanUp()
{
	strDepot.clear();
}

void MemChrDepotData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_depot` (`cid`,`depot`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `depot`='%s'",
		(long long)nCid, strDepot.c_str(), strDepot.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrDepotData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_depot` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strDepot = result.getStringValue("depot", "");
	}
	return true;
}

void MemChrDepotData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strDepot);
}

void MemChrDepotData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strDepot = tmp; }
}

MemChrEquipData::MemChrEquipData()
{
	CleanUp();
}

MemChrEquipData::~MemChrEquipData()
{
}

void MemChrEquipData::CleanUp()
{
	strEquips.clear();
}

void MemChrEquipData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_equip` (`cid`,`equips`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `equips`='%s'",
		(long long)nCid, strEquips.c_str(), strEquips.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrEquipData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_equip` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strEquips = result.getStringValue("equips", "");
	}
	return true;
}

void MemChrEquipData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strEquips);
}

void MemChrEquipData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strEquips = tmp; }
}

MemChrGemData::MemChrGemData()
{
	CleanUp();
}

MemChrGemData::~MemChrGemData()
{
}

void MemChrGemData::CleanUp()
{
	strGems.clear();
}

void MemChrGemData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_gem` (`cid`,`gems`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `gems`='%s'",
		(long long)nCid, strGems.c_str(), strGems.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrGemData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_gem` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strGems = result.getStringValue("gems", "");
	}
	return true;
}

void MemChrGemData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strGems);
}

void MemChrGemData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strGems = tmp; }
}

MemChrSkillData::MemChrSkillData()
{
	CleanUp();
}

MemChrSkillData::~MemChrSkillData()
{
}

void MemChrSkillData::CleanUp()
{
	strSkills.clear();
}

void MemChrSkillData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_skill` (`cid`,`skills`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `skills`='%s'",
		(long long)nCid, strSkills.c_str(), strSkills.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrSkillData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_skill` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strSkills = result.getStringValue("skills", "");
	}
	return true;
}

void MemChrSkillData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strSkills);
}

void MemChrSkillData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strSkills = tmp; }
}

MemChrSystemSettingData::MemChrSystemSettingData()
{
	CleanUp();
}

MemChrSystemSettingData::~MemChrSystemSettingData()
{
}

void MemChrSystemSettingData::CleanUp()
{
	strSettings.clear();
}

void MemChrSystemSettingData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_system_setting` (`cid`,`settings`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `settings`='%s'",
		(long long)nCid, strSettings.c_str(), strSettings.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrSystemSettingData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_system_setting` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strSettings = result.getStringValue("settings", "");
	}
	return true;
}

void MemChrSystemSettingData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strSettings);
}

void MemChrSystemSettingData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strSettings = tmp; }
}

MemChrTaskCycleData::MemChrTaskCycleData()
{
	CleanUp();
}

MemChrTaskCycleData::~MemChrTaskCycleData()
{
}

void MemChrTaskCycleData::CleanUp()
{
	nCycle = 0;
	strTasks.clear();
}

void MemChrTaskCycleData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_task_cycle` (`cid`,`cycle`,`tasks`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `cycle`=%lld,`tasks`='%s'",
		(long long)nCid, (long long)nCycle,strTasks.c_str(), (long long)nCycle,strTasks.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrTaskCycleData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_task_cycle` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nCycle = result.getIntValue("cycle", 0);
		strTasks = result.getStringValue("tasks", "");
	}
	return true;
}

void MemChrTaskCycleData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nCycle);
	packet->writeUTF8(strTasks);
}

void MemChrTaskCycleData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nCycle = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strTasks = tmp; }
}

MemChrTaskData::MemChrTaskData()
{
	CleanUp();
}

MemChrTaskData::~MemChrTaskData()
{
}

void MemChrTaskData::CleanUp()
{
	strTasks.clear();
}

void MemChrTaskData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_task` (`cid`,`tasks`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `tasks`='%s'",
		(long long)nCid, strTasks.c_str(), strTasks.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MemChrTaskData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_task` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strTasks = result.getStringValue("tasks", "");
	}
	return true;
}

void MemChrTaskData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strTasks);
}

void MemChrTaskData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strTasks = tmp; }
}

MoneyRewardTaskData::MoneyRewardTaskData()
{
	CleanUp();
}

MoneyRewardTaskData::~MoneyRewardTaskData()
{
}

void MoneyRewardTaskData::CleanUp()
{
	nTaskId = 0;
	nStatus = 0;
	nCount = 0;
}

void MoneyRewardTaskData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_money_reward_task` (`cid`,`task_id`,`status`,`count`) VALUES (%lld,%lld,%lld,%lld) ON DUPLICATE KEY UPDATE `task_id`=%lld,`status`=%lld,`count`=%lld",
		(long long)nCid, (long long)nTaskId,(long long)nStatus,(long long)nCount, (long long)nTaskId,(long long)nStatus,(long long)nCount);
	sqls->push_back(std::string((char*)szSQL));
}

bool MoneyRewardTaskData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_money_reward_task` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nTaskId = result.getIntValue("task_id", 0);
		nStatus = result.getIntValue("status", 0);
		nCount = result.getIntValue("count", 0);
	}
	return true;
}

void MoneyRewardTaskData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nTaskId);
	packet->writeInt32(nStatus);
	packet->writeInt32(nCount);
}

void MoneyRewardTaskData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nTaskId = inPacket->readInt32();
	nStatus = inPacket->readInt32();
	nCount = inPacket->readInt32();
}

MysteryShopDBData::MysteryShopDBData()
{
	CleanUp();
}

MysteryShopDBData::~MysteryShopDBData()
{
}

void MysteryShopDBData::CleanUp()
{
	nShopId = 0;
	strData.clear();
}

void MysteryShopDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_mystery_shop` (`cid`,`shop_id`,`data`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `shop_id`=%lld,`data`='%s'",
		(long long)nCid, (long long)nShopId,strData.c_str(), (long long)nShopId,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool MysteryShopDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_mystery_shop` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nShopId = result.getIntValue("shop_id", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void MysteryShopDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nShopId);
	packet->writeUTF8(strData);
}

void MysteryShopDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nShopId = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

NationalDayData::NationalDayData()
{
	CleanUp();
}

NationalDayData::~NationalDayData()
{
}

void NationalDayData::CleanUp()
{
	strData.clear();
}

void NationalDayData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_national_day` (`cid`,`data`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `data`='%s'",
		(long long)nCid, strData.c_str(), strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool NationalDayData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_national_day` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strData = result.getStringValue("data", "");
	}
	return true;
}

void NationalDayData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strData);
}

void NationalDayData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

OperateLimitDBData::OperateLimitDBData()
{
	CleanUp();
}

OperateLimitDBData::~OperateLimitDBData()
{
}

void OperateLimitDBData::CleanUp()
{
	nType = 0;
	nCount = 0;
	nLastTime = 0;
}

void OperateLimitDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_operate_limit` (`cid`,`type`,`count`,`last_time`) VALUES (%lld,%lld,%lld,%lld) ON DUPLICATE KEY UPDATE `type`=%lld,`count`=%lld,`last_time`=%lld",
		(long long)nCid, (long long)nType,(long long)nCount,(long long)nLastTime, (long long)nType,(long long)nCount,(long long)nLastTime);
	sqls->push_back(std::string((char*)szSQL));
}

bool OperateLimitDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_operate_limit` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nType = result.getIntValue("type", 0);
		nCount = result.getIntValue("count", 0);
		nLastTime = result.getIntValue("last_time", 0);
	}
	return true;
}

void OperateLimitDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nType);
	packet->writeInt32(nCount);
	packet->writeInt32(nLastTime);
}

void OperateLimitDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nType = inPacket->readInt32();
	nCount = inPacket->readInt32();
	nLastTime = inPacket->readInt32();
}

PetDBData::PetDBData()
{
	CleanUp();
}

PetDBData::~PetDBData()
{
}

void PetDBData::CleanUp()
{
	nPetId = 0;
	nLevel = 0;
	nExp = 0;
	strData.clear();
}

void PetDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_pet` (`cid`,`pet_id`,`level`,`exp`,`data`) VALUES (%lld,%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `pet_id`=%lld,`level`=%lld,`exp`=%lld,`data`='%s'",
		(long long)nCid, (long long)nPetId,(long long)nLevel,(long long)nExp,strData.c_str(), (long long)nPetId,(long long)nLevel,(long long)nExp,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool PetDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_pet` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nPetId = result.getIntValue("pet_id", 0);
		nLevel = result.getIntValue("level", 0);
		nExp = result.getIntValue("exp", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void PetDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nPetId);
	packet->writeInt32(nLevel);
	packet->writeInt32(nExp);
	packet->writeUTF8(strData);
}

void PetDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nPetId = inPacket->readInt32();
	nLevel = inPacket->readInt32();
	nExp = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

PortalDBData::PortalDBData()
{
	CleanUp();
}

PortalDBData::~PortalDBData()
{
}

void PortalDBData::CleanUp()
{
	nPortalId = 0;
	strData.clear();
}

void PortalDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_portal` (`cid`,`portal_id`,`data`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `portal_id`=%lld,`data`='%s'",
		(long long)nCid, (long long)nPortalId,strData.c_str(), (long long)nPortalId,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool PortalDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_portal` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nPortalId = result.getIntValue("portal_id", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void PortalDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nPortalId);
	packet->writeUTF8(strData);
}

void PortalDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nPortalId = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

ScoreShopData::ScoreShopData()
{
	CleanUp();
}

ScoreShopData::~ScoreShopData()
{
}

void ScoreShopData::CleanUp()
{
	nShopId = 0;
	strData.clear();
}

void ScoreShopData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_score_shop` (`cid`,`shop_id`,`data`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `shop_id`=%lld,`data`='%s'",
		(long long)nCid, (long long)nShopId,strData.c_str(), (long long)nShopId,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool ScoreShopData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_score_shop` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nShopId = result.getIntValue("shop_id", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void ScoreShopData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nShopId);
	packet->writeUTF8(strData);
}

void ScoreShopData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nShopId = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

ShangChengData::ShangChengData()
{
	CleanUp();
}

ShangChengData::~ShangChengData()
{
}

void ShangChengData::CleanUp()
{
	strData.clear();
}

void ShangChengData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_shangcheng` (`cid`,`data`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `data`='%s'",
		(long long)nCid, strData.c_str(), strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool ShangChengData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_shangcheng` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		strData = result.getStringValue("data", "");
	}
	return true;
}

void ShangChengData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeUTF8(strData);
}

void ShangChengData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

SysUserData::SysUserData()
{
	CleanUp();
}

SysUserData::~SysUserData()
{
}

void SysUserData::CleanUp()
{
	nUid = 0;
	nSid = 0;
	strData.clear();
}

void SysUserData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `sys_user` (`cid`,`uid`,`sid`,`data`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `uid`=%lld,`sid`=%lld,`data`='%s'",
		(long long)nCid, (long long)nUid,(long long)nSid,strData.c_str(), (long long)nUid,(long long)nSid,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool SysUserData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `sys_user` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nUid = result.getInt64Value("uid", 0);
		nSid = result.getIntValue("sid", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void SysUserData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt64(nUid);
	packet->writeInt32(nSid);
	packet->writeUTF8(strData);
}

void SysUserData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nUid = inPacket->readInt64();
	nSid = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

SysUserPreventWallowData::SysUserPreventWallowData()
{
	CleanUp();
}

SysUserPreventWallowData::~SysUserPreventWallowData()
{
}

void SysUserPreventWallowData::CleanUp()
{
}

void SysUserPreventWallowData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `sys_user_prevent_wallow` (`cid`) VALUES (%lld) ON DUPLICATE KEY UPDATE `cid`=%lld",
		(long long)nCid, (long long)nCid);
	sqls->push_back(std::string((char*)szSQL));
}

bool SysUserPreventWallowData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `sys_user_prevent_wallow` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
	}
	return true;
}

void SysUserPreventWallowData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
}

void SysUserPreventWallowData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
}

TouZiData::TouZiData()
{
	CleanUp();
}

TouZiData::~TouZiData()
{
}

void TouZiData::CleanUp()
{
	nTouZiId = 0;
	nLevel = 0;
	strData.clear();
}

void TouZiData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_touzi` (`cid`,`touzi_id`,`level`,`data`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `touzi_id`=%lld,`level`=%lld,`data`='%s'",
		(long long)nCid, (long long)nTouZiId,(long long)nLevel,strData.c_str(), (long long)nTouZiId,(long long)nLevel,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool TouZiData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_touzi` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nTouZiId = result.getIntValue("touzi_id", 0);
		nLevel = result.getIntValue("level", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void TouZiData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nTouZiId);
	packet->writeInt32(nLevel);
	packet->writeUTF8(strData);
}

void TouZiData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nTouZiId = inPacket->readInt32();
	nLevel = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

VipData::VipData()
{
	CleanUp();
}

VipData::~VipData()
{
}

void VipData::CleanUp()
{
	nVipLevel = 0;
	nVipExp = 0;
	nVipTime = 0;
	strData.clear();
}

void VipData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_vip` (`cid`,`vip_level`,`vip_exp`,`vip_time`,`data`) VALUES (%lld,%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `vip_level`=%lld,`vip_exp`=%lld,`vip_time`=%lld,`data`='%s'",
		(long long)nCid, (long long)nVipLevel,(long long)nVipExp,(long long)nVipTime,strData.c_str(), (long long)nVipLevel,(long long)nVipExp,(long long)nVipTime,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool VipData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_vip` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nVipLevel = result.getIntValue("vip_level", 0);
		nVipExp = result.getIntValue("vip_exp", 0);
		nVipTime = result.getIntValue("vip_time", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void VipData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nVipLevel);
	packet->writeInt32(nVipExp);
	packet->writeInt32(nVipTime);
	packet->writeUTF8(strData);
}

void VipData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nVipLevel = inPacket->readInt32();
	nVipExp = inPacket->readInt32();
	nVipTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

WorshipDBData::WorshipDBData()
{
	CleanUp();
}

WorshipDBData::~WorshipDBData()
{
}

void WorshipDBData::CleanUp()
{
	nCount = 0;
	nLastTime = 0;
	strData.clear();
}

void WorshipDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_worship` (`cid`,`count`,`last_time`,`data`) VALUES (%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `count`=%lld,`last_time`=%lld,`data`='%s'",
		(long long)nCid, (long long)nCount,(long long)nLastTime,strData.c_str(), (long long)nCount,(long long)nLastTime,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool WorshipDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_worship` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nCount = result.getIntValue("count", 0);
		nLastTime = result.getIntValue("last_time", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void WorshipDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nCount);
	packet->writeInt32(nLastTime);
	packet->writeUTF8(strData);
}

void WorshipDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nCount = inPacket->readInt32();
	nLastTime = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

WuHunShopDBData::WuHunShopDBData()
{
	CleanUp();
}

WuHunShopDBData::~WuHunShopDBData()
{
}

void WuHunShopDBData::CleanUp()
{
	nShopId = 0;
	strData.clear();
}

void WuHunShopDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_wuhun_shop` (`cid`,`shop_id`,`data`) VALUES (%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `shop_id`=%lld,`data`='%s'",
		(long long)nCid, (long long)nShopId,strData.c_str(), (long long)nShopId,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool WuHunShopDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_wuhun_shop` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nShopId = result.getIntValue("shop_id", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void WuHunShopDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nShopId);
	packet->writeUTF8(strData);
}

void WuHunShopDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nShopId = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

XinMoDBData::XinMoDBData()
{
	CleanUp();
}

XinMoDBData::~XinMoDBData()
{
}

void XinMoDBData::CleanUp()
{
	nXinMoId = 0;
	nLevel = 0;
	nExp = 0;
	strData.clear();
}

void XinMoDBData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "INSERT INTO `mem_chr_xinmo` (`cid`,`xinmo_id`,`level`,`exp`,`data`) VALUES (%lld,%lld,%lld,%lld,'%s') ON DUPLICATE KEY UPDATE `xinmo_id`=%lld,`level`=%lld,`exp`=%lld,`data`='%s'",
		(long long)nCid, (long long)nXinMoId,(long long)nLevel,(long long)nExp,strData.c_str(), (long long)nXinMoId,(long long)nLevel,(long long)nExp,strData.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

bool XinMoDBData::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
	bzero(szSQL, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "SELECT * FROM `mem_chr_xinmo` WHERE `cid`=%lld", (long long)nCid);
	Answer::MySqlQuery result(db->query((const char*)szSQL));
	if (!result.eof())
	{
		nXinMoId = result.getIntValue("xinmo_id", 0);
		nLevel = result.getIntValue("level", 0);
		nExp = result.getIntValue("exp", 0);
		strData = result.getStringValue("data", "");
	}
	return true;
}

void XinMoDBData::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nXinMoId);
	packet->writeInt32(nLevel);
	packet->writeInt32(nExp);
	packet->writeUTF8(strData);
}

void XinMoDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	nXinMoId = inPacket->readInt32();
	nLevel = inPacket->readInt32();
	nExp = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); strData = tmp; }
}

//////////////////////////////////////////////////////////////////////////
// MemChrSignInfo
//////////////////////////////////////////////////////////////////////////
void MemChrSignInfo::CleanUp()
{
	sign_record = 0;
	refresh_time = 0;
	sign_reward.clear();
}

//////////////////////////////////////////////////////////////////////////
// MemEquip
//////////////////////////////////////////////////////////////////////////
MemEquip::MemEquip()
	: id(0), base(0), owner(0), star(0), time(0), MapId(0), Mid(0), Lucky(0)
{
}

MemEquip::~MemEquip()
{
}

void MemEquip::CleanUp()
{
	id = 0;
	base = 0;
	owner = 0;
	star = 0;
	name.clear();
	time = 0;
	MapId = 0;
	Mid = 0;
	Lucky = 0;
}

void MemEquip::PackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt64(id);
	packet->writeInt32(base);
	packet->writeInt64(owner);
	packet->writeInt8(star);
	packet->writeInt32(MapId);
	packet->writeInt32(Mid);
	packet->writeInt32(time);
	packet->writeUTF8(name);
	packet->writeInt32(Lucky);
}

void MemEquip::UnPackageData(Answer::NetPacket* inPacket)
{
	if (!inPacket) return;
	id = inPacket->readInt64();
	base = inPacket->readInt32();
	owner = inPacket->readInt64();
	star = inPacket->readInt8();
	MapId = inPacket->readInt32();
	Mid = inPacket->readInt32();
	time = inPacket->readInt32();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	Lucky = inPacket->readInt32();
}

void MemEquip::PackageClientData(Answer::NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt64(id);
	packet->writeInt32(base);
	packet->writeInt8(star);
	packet->writeInt32(MapId);
	packet->writeInt32(Mid);
	packet->writeInt32(time);
	packet->writeUTF8(name);
	packet->writeInt32(Lucky);
}

//////////////////////////////////////////////////////////////////////////
// MemPetDBData
//////////////////////////////////////////////////////////////////////////
void MemPetDBData::CleanUp()
{
	nOwner = 0;
	nPetId = 0;
	nBaseId = 0;
	strName.clear();
	skills.clear();
	equips.clear();
}

//////////////////////////////////////////////////////////////////////////
// PlayerDBData
//////////////////////////////////////////////////////////////////////////
PlayerDBData::PlayerDBData()
{
	CleanUp();
}

PlayerDBData::~PlayerDBData()
{
}

void PlayerDBData::CleanUp()
{
	connid = 0;
	cgindex = 0;
	loadTime = 0;
	saveRefCount = 0;
	chr.CleanUp();
	attrData.CleanUp();
	sysUser.CleanUp();
	signInfo.CleanUp();
	equipData.CleanUp();
	gemData.CleanUp();
	bagData.CleanUp();
	skillData.CleanUp();
	taskData.CleanUp();
	taskCycleData.CleanUp();
	actionData.CleanUp();
	autoFight.CleanUp();
	systemSetting.CleanUp();
	buffData.CleanUp();
	gambleDepot.CleanUp();
	sysUserPreventWallow.CleanUp();
	m_CurrencyData.CleanUp();
	m_OperateLimit.CleanUp();
	m_CharPets.CleanUp();
	m_FriendExpReward.CleanUp();
	m_MailDBData.CleanUp();
	m_ShangChengData.CleanUp();
	m_BossKilledReward.CleanUp();
	m_FaBaoData.CleanUp();
	m_CGoblinData.CleanUp();
	m_FamilyData.CleanUp();
	m_WorshipData.CleanUp();
	m_JueWeiData.CleanUp();
	m_ScoreShopData.CleanUp();
	m_TouZiData.CleanUp();
	m_HuoYueDuData.CleanUp();
	m_MysteryShopDBData.CleanUp();
	m_ExchangeDBData.CleanUp();
	m_WishDBData.CleanUp();
	m_VplanData.CleanUp();
	m_CharWingDBData.CleanUp();
	m_MagicBoxDBData.CleanUp();
	m_vipData.CleanUp();
	m_ShiZhuangData.CleanUp();
	m_CMonthlyChouJiangData.CleanUp();
	m_ChouJinagData.CleanUp();
	m_MoneyRewardTaskData.CleanUp();
	m_WuHunShopDBData.CleanUp();
	m_CMingGeData.CleanUp();
	m_CKunData.CleanUp();
	m_CFlopDraw.CleanUp();
	m_CSevenDayData.CleanUp();
	m_PortalDBData.CleanUp();
	m_XinMoDBData.CleanUp();
	m_CLittleHelper.CleanUp();
	m_NationalDayData.CleanUp();
	m_EquipRongHeData.CleanUp();
}

void PlayerDBData::PackageData(Answer::NetPacket* packet, CharId_t nCid)
{
	if (!packet) return;
	chr.PackageData(packet);
	attrData.PackageData(packet);
	sysUser.PackageData(packet, nCid);
	signInfo.PackageData(packet);
	equipData.PackageData(packet);
	gemData.PackageData(packet);
	bagData.PackageData(packet);
	skillData.PackageData(packet);
	taskData.PackageData(packet);
	taskCycleData.PackageData(packet);
	actionData.PackageData(packet);
	autoFight.PackageData(packet);
	systemSetting.PackageData(packet);
	buffData.PackageData(packet);
	gambleDepot.PackageData(packet);
	sysUserPreventWallow.PackageData(packet, nCid);
	m_CurrencyData.PackageData(packet, nCid);
	m_OperateLimit.PackageData(packet, nCid);
	m_CharPets.PackageData(packet, nCid);
	m_FriendExpReward.PackageData(packet, nCid);
	m_MailDBData.PackageData(packet, nCid);
	m_ShangChengData.PackageData(packet, nCid);
	m_BossKilledReward.PackageData(packet, nCid);
	m_FaBaoData.PackageData(packet, nCid);
	m_CGoblinData.PackageData(packet, nCid);
	m_FamilyData.PackageData(packet, nCid);
	m_WorshipData.PackageData(packet, nCid);
	m_JueWeiData.PackageData(packet, nCid);
	m_ScoreShopData.PackageData(packet, nCid);
	m_TouZiData.PackageData(packet, nCid);
	m_HuoYueDuData.PackageData(packet, nCid);
	m_MysteryShopDBData.PackageData(packet, nCid);
	m_ExchangeDBData.PackageData(packet, nCid);
	m_WishDBData.PackageData(packet, nCid);
	m_VplanData.PackageData(packet, nCid);
	m_CharWingDBData.PackageData(packet, nCid);
	m_MagicBoxDBData.PackageData(packet, nCid);
	m_vipData.PackageData(packet, nCid);
	m_ShiZhuangData.PackageData(packet, nCid);
	m_CMonthlyChouJiangData.PackageData(packet, nCid);
	m_ChouJinagData.PackageData(packet, nCid);
	m_MoneyRewardTaskData.PackageData(packet, nCid);
	m_WuHunShopDBData.PackageData(packet, nCid);
	m_CMingGeData.PackageData(packet, nCid);
	m_CKunData.PackageData(packet, nCid);
	m_CFlopDraw.PackageData(packet, nCid);
	m_CSevenDayData.PackageData(packet, nCid);
	m_PortalDBData.PackageData(packet, nCid);
	m_XinMoDBData.PackageData(packet, nCid);
	m_CLittleHelper.PackageData(packet, nCid);
	m_NationalDayData.PackageData(packet, nCid);
	m_EquipRongHeData.PackageData(packet, nCid);
}

void PlayerDBData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	chr.UnPackageData(inPacket);
	attrData.UnPackageData(inPacket);
	sysUser.UnPackageData(inPacket, nCid);
	signInfo.UnPackageData(inPacket);
	equipData.UnPackageData(inPacket);
	gemData.UnPackageData(inPacket);
	bagData.UnPackageData(inPacket);
	skillData.UnPackageData(inPacket);
	taskData.UnPackageData(inPacket);
	taskCycleData.UnPackageData(inPacket);
	actionData.UnPackageData(inPacket);
	autoFight.UnPackageData(inPacket);
	systemSetting.UnPackageData(inPacket);
	buffData.UnPackageData(inPacket);
	gambleDepot.UnPackageData(inPacket);
	sysUserPreventWallow.UnPackageData(inPacket, nCid);
	m_CurrencyData.UnPackageData(inPacket, nCid);
	m_OperateLimit.UnPackageData(inPacket, nCid);
	m_CharPets.UnPackageData(inPacket, nCid);
	m_FriendExpReward.UnPackageData(inPacket, nCid);
	m_MailDBData.UnPackageData(inPacket, nCid);
	m_ShangChengData.UnPackageData(inPacket, nCid);
	m_BossKilledReward.UnPackageData(inPacket, nCid);
	m_FaBaoData.UnPackageData(inPacket, nCid);
	m_CGoblinData.UnPackageData(inPacket, nCid);
	m_FamilyData.UnPackageData(inPacket, nCid);
	m_WorshipData.UnPackageData(inPacket, nCid);
	m_JueWeiData.UnPackageData(inPacket, nCid);
	m_ScoreShopData.UnPackageData(inPacket, nCid);
	m_TouZiData.UnPackageData(inPacket, nCid);
	m_HuoYueDuData.UnPackageData(inPacket, nCid);
	m_MysteryShopDBData.UnPackageData(inPacket, nCid);
	m_ExchangeDBData.UnPackageData(inPacket, nCid);
	m_WishDBData.UnPackageData(inPacket, nCid);
	m_VplanData.UnPackageData(inPacket, nCid);
	m_CharWingDBData.UnPackageData(inPacket, nCid);
	m_MagicBoxDBData.UnPackageData(inPacket, nCid);
	m_vipData.UnPackageData(inPacket, nCid);
	m_ShiZhuangData.UnPackageData(inPacket, nCid);
	m_CMonthlyChouJiangData.UnPackageData(inPacket, nCid);
	m_ChouJinagData.UnPackageData(inPacket, nCid);
	m_MoneyRewardTaskData.UnPackageData(inPacket, nCid);
	m_WuHunShopDBData.UnPackageData(inPacket, nCid);
	m_CMingGeData.UnPackageData(inPacket, nCid);
	m_CKunData.UnPackageData(inPacket, nCid);
	m_CFlopDraw.UnPackageData(inPacket, nCid);
	m_CSevenDayData.UnPackageData(inPacket, nCid);
	m_PortalDBData.UnPackageData(inPacket, nCid);
	m_XinMoDBData.UnPackageData(inPacket, nCid);
	m_CLittleHelper.UnPackageData(inPacket, nCid);
	m_NationalDayData.UnPackageData(inPacket, nCid);
	m_EquipRongHeData.UnPackageData(inPacket, nCid);
}

//////////////////////////////////////////////////////////////////////////
// ItemData
//////////////////////////////////////////////////////////////////////////
bool ItemData::IsEmpty() const
{
	return m_nId <= 0 || m_nClass <= 0 || m_nCount <= 0;
}

//////////////////////////////////////////////////////////////////////////
// RandHelper
//////////////////////////////////////////////////////////////////////////
int32_t RandHelper::CalRandTimes(int32_t nTotalTimes, int32_t nRate, int32_t nTotalRate)
{
	int32_t times = 0;
	for (int32_t i = 0; i < nTotalTimes; ++i)
	{
		if (Answer::Singleton<Answer::Random>::instance()->generate(0, nTotalRate - 1) < nRate)
			++times;
	}
	return times;
}

//////////////////////////////////////////////////////////////////////////
// CKunData
//////////////////////////////////////////////////////////////////////////
CKunData::CKunData()
{
	CleanUp();
}

CKunData::~CKunData()
{
}

void CKunData::CleanUp()
{
	m_nBuyTime = 0;
	m_nLianHuaTime = 0;
	m_nKunLevel = 0;
	m_nExp = 0;
	memset(m_LingZhuPos, 0, sizeof(m_LingZhuPos));
	memset(m_LingZhuBag, 0, sizeof(m_LingZhuBag));
	memset(m_DanTian, 0, sizeof(m_DanTian));
}

std::string CKunData::getLingZhuPosString()
{
	std::string result;
	for (int i = 0; i < 10; ++i)
	{
		char buf[64];
		snprintf(buf, sizeof(buf), "%d:%d", m_LingZhuPos[i].nId, m_LingZhuPos[i].nLevel);
		if (i > 0) result += "|";
		result += buf;
	}
	return result;
}

void CKunData::parseLingZhuPos(const std::string& p_PosString)
{
	if (p_PosString.empty()) return;
	StringVector vt;
	std::string delims("|");
	Answer::StringUtility::split(vt, p_PosString, delims, false);
	for (size_t i = 0; i < vt.size() && i < 10; ++i)
	{
		StringVector sv;
		std::string d(":");
		Answer::StringUtility::split(sv, vt[i], d, false);
		if (sv.size() == 2)
		{
			m_LingZhuPos[i].nId = atoi(sv[0].c_str());
			m_LingZhuPos[i].nLevel = atoi(sv[1].c_str());
		}
	}
}

std::string CKunData::getDanTianString()
{
	std::string result;
	for (int i = 0; i < 6; ++i)
	{
		char buf[64];
		snprintf(buf, sizeof(buf), "%d:%d:%d:%d", i, m_DanTian[i].nMid, m_DanTian[i].nId, m_DanTian[i].nEndTime);
		if (i > 0) result += "|";
		result += buf;
	}
	return result;
}

void CKunData::parseDanTian(const std::string& p_DanTianString)
{
	if (p_DanTianString.empty()) return;
	StringVector vt;
	std::string delims("|");
	Answer::StringUtility::split(vt, p_DanTianString, delims, false);
	for (size_t i = 0; i < vt.size(); ++i)
	{
		StringVector sv;
		std::string d(":");
		Answer::StringUtility::split(sv, vt[i], d, false);
		if (sv.size() == 4)
		{
			int32_t nId = atoi(sv[0].c_str());
			if (nId >= 0 && nId < 6)
			{
				m_DanTian[nId].nMid = atoi(sv[1].c_str());
				m_DanTian[nId].nId = atoi(sv[2].c_str());
				m_DanTian[nId].nEndTime = atoi(sv[3].c_str());
			}
		}
	}
}

void CKunData::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	if (!sqls || !szSQL) return;

	// Save LingZhuBag
	for (int32_t i = 0; i <= 99; ++i)
	{
		memset(szSQL, 0, 0x1000);
		snprintf((char*)szSQL, 0xFFF,
			"INSERT INTO `mem_chr_kun_bag` (`cid`, `slot`, `nId`, `nCount`) VALUES (%lld, %d,%d,%d) "
			"ON DUPLICATE KEY UPDATE `nId`=%d, `nCount`=%d",
			(int64_t)nCid, i, m_LingZhuBag[i].nId, m_LingZhuBag[i].nCount,
			m_LingZhuBag[i].nId, m_LingZhuBag[i].nCount);
		sqls->push_back(std::string((char*)szSQL));
	}

	// Save main record
	std::string posStr = getLingZhuPosString();
	std::string dtStr = getDanTianString();
	memset(szSQL, 0, 0x1000);
	snprintf((char*)szSQL, 0xFFF,
		"INSERT INTO `mem_chr_kun` (`cid`,`buyTime`,`lianhuaTime`,`kunLevel`,`exp`,`lingZhuPos`,`danTian`) "
		"VALUES (%lld,%d,%d,%d,%d,'%s','%s') "
		"ON DUPLICATE KEY UPDATE `buyTime`=%d,`lianhuaTime`=%d,`kunLevel`=%d,`exp`=%d,`lingZhuPos`='%s',`danTian`='%s'",
		(int64_t)nCid, m_nBuyTime, m_nLianHuaTime, m_nKunLevel, m_nExp, posStr.c_str(), dtStr.c_str(),
		m_nBuyTime, m_nLianHuaTime, m_nKunLevel, m_nExp, posStr.c_str(), dtStr.c_str());
	sqls->push_back(std::string((char*)szSQL));
}

void CKunData::PackageData(Answer::NetPacket* packet, CharId_t nCid)
{
	if (!packet) return;
	packet->writeInt32(m_nBuyTime);
	packet->writeInt32(m_nLianHuaTime);
	packet->writeInt32(m_nKunLevel);
	packet->writeInt32(m_nExp);
	for (int i = 0; i < 10; ++i)
	{
		packet->writeInt32(m_LingZhuPos[i].nId);
		packet->writeInt32(m_LingZhuPos[i].nLevel);
	}
	for (int i = 0; i < 100; ++i)
	{
		packet->writeInt32(m_LingZhuBag[i].nId);
		packet->writeInt32(m_LingZhuBag[i].nCount);
	}
	for (int i = 0; i < 6; ++i)
	{
		packet->writeInt32(m_DanTian[i].nMid);
		packet->writeInt32(m_DanTian[i].nId);
		packet->writeInt32(m_DanTian[i].nEndTime);
	}
}

void CKunData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	m_nBuyTime = inPacket->readInt32();
	m_nLianHuaTime = inPacket->readInt32();
	m_nKunLevel = inPacket->readInt32();
	m_nExp = inPacket->readInt32();
	for (int i = 0; i < 10; ++i)
	{
		m_LingZhuPos[i].nId = inPacket->readInt32();
		m_LingZhuPos[i].nLevel = inPacket->readInt32();
	}
	for (int i = 0; i < 100; ++i)
	{
		m_LingZhuBag[i].nId = inPacket->readInt32();
		m_LingZhuBag[i].nCount = inPacket->readInt32();
	}
	for (int i = 0; i < 6; ++i)
	{
		m_DanTian[i].nMid = inPacket->readInt32();
		m_DanTian[i].nId = inPacket->readInt32();
		m_DanTian[i].nEndTime = inPacket->readInt32();
	}
}

//////////////////////////////////////////////////////////////////////////
// CFlopDraw
//////////////////////////////////////////////////////////////////////////
CFlopDraw::CFlopDraw()
{
	CleanUp();
}

CFlopDraw::~CFlopDraw()
{
}

void CFlopDraw::CleanUp()
{
	m_FlopDrawRecordMap.clear();
}

void CFlopDraw::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)
{
	if (!sqls || !szSQL) return;

	// Delete old records
	memset(szSQL, 0, 0x1000);
	snprintf((char*)szSQL, 0xFFF, "DELETE FROM `mem_flop_draw` WHERE `cid` = %lld ", (int64_t)nCid);
	sqls->push_back(std::string((char*)szSQL));

	// Insert new records
	for (auto it = m_FlopDrawRecordMap.begin(); it != m_FlopDrawRecordMap.end(); ++it)
	{
		for (auto itFlop = it->second.begin(); itFlop != it->second.end(); ++itFlop)
		{
			memset(szSQL, 0, 0x1000);
			snprintf((char*)szSQL, 0xFFF,
				"INSERT INTO `mem_flop_draw` (`cid`,`nType`,`nFlopId`,`nId`) VALUES (%lld,%d,%d,%d)",
				(int64_t)nCid, it->first, itFlop->first, itFlop->second);
			sqls->push_back(std::string((char*)szSQL));
		}
	}
}

void CFlopDraw::PackageData(Answer::NetPacket* packet, CharId_t nCid)
{
	if (!packet) return;
	packet->writeInt32((int32_t)m_FlopDrawRecordMap.size());
	for (auto it = m_FlopDrawRecordMap.begin(); it != m_FlopDrawRecordMap.end(); ++it)
	{
		packet->writeInt32(it->first);
		packet->writeInt32((int32_t)it->second.size());
		for (auto itFlop = it->second.begin(); itFlop != it->second.end(); ++itFlop)
		{
			packet->writeInt32(itFlop->first);
			packet->writeInt32(itFlop->second);
		}
	}
}

void CFlopDraw::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
	if (!inPacket) return;
	int32_t nTypeSize = inPacket->readInt32();
	for (int32_t i = 0; i < nTypeSize; ++i)
	{
		int32_t nType = inPacket->readInt32();
		int32_t FlopSize = inPacket->readInt32();
		std::map<int32_t, int32_t> TmpMap;
		for (int32_t j = 0; j < FlopSize; ++j)
		{
			int32_t FlopId = inPacket->readInt32();
			int32_t nId = inPacket->readInt32();
			TmpMap[FlopId] = nId;
		}
		m_FlopDrawRecordMap[nType] = TmpMap;
	}
}