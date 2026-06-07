#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include "DataStructs.h"

//////////////////////////////////////////////////////////////////////////
// DB Data Classes - data persistence layer
//////////////////////////////////////////////////////////////////////////

class BossKilledRewardData
{
public:
	BossKilledRewardData();
	~BossKilledRewardData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string RewardString;
};

class CFaBaoData
{
public:
	CFaBaoData();
	~CFaBaoData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t m_FaBao[4];
	int32_t m_FaBaoRes[4];
};

class CGoblinData
{
public:
	CGoblinData();
	~CGoblinData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strData;
};

class CHuoYueDuData
{
public:
	CHuoYueDuData();
	~CHuoYueDuData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nHuoYueDu;
	int32_t nTodayHuoYueDu;
	int32_t nLastTime;
	std::string strRewards;
};

class CJueWeiData
{
public:
	CJueWeiData();
	~CJueWeiData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nJueWeiLevel;
	int32_t nJueWeiExp;
	std::string strRewards;
};

class CMonthlyChouJiangData
{
public:
	CMonthlyChouJiangData();
	~CMonthlyChouJiangData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nFreeCount;
	int32_t nTotalCount;
	int32_t nLastFreeTime;
	std::string strRewards;
};

class CSevenDayData
{
public:
	CSevenDayData();
	~CSevenDayData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nDayIndex;
	std::string strRewards;
};

class CShiZhuangData
{
public:
	CShiZhuangData();
	~CShiZhuangData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nShiZhuangId;
	int32_t nLevel;
	std::string strData;
};

class CVplanData
{
public:
	CVplanData();
	~CVplanData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nVplanId;
	int32_t nLevel;
	int32_t nExp;
	std::string strRewards;
};

class CharFamilyDBData
{
public:
	CharFamilyDBData();
	~CharFamilyDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nContribution;
	int32_t nTotalContribution;
	std::string strData;
};

class CharWingDBData
{
public:
	CharWingDBData();
	~CharWingDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nWingId;
	int32_t nLevel;
	std::string strData;
};

class CharWishDBData
{
public:
	CharWishDBData();
	~CharWishDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strWishes;
};

class ChouJiangData
{
public:
	ChouJiangData();
	~ChouJiangData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nFreeCount;
	int32_t nLastFreeTime;
	std::string strRewards;
};

class CurrencyDBData
{
public:
	CurrencyDBData();
	~CurrencyDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int64_t vCurrency[12];
};

class DailyActivityData
{
public:
	DailyActivityData();
	~DailyActivityData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nTodayActive;
	int32_t nTotalActive;
	std::string strRewards;
};

class EquipRongHeData
{
public:
	EquipRongHeData();
	~EquipRongHeData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strData;
};

class ExchangeDBData
{
public:
	ExchangeDBData();
	~ExchangeDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nCount;
	std::string strData;
};

class MagicBoxDBData
{
public:
	MagicBoxDBData();
	~MagicBoxDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nCombiPoints;
	int32_t nLastReviveTime;
	std::string strActiveScrolls;
	std::string strSuccessIds;
};

class MailDBData
{
public:
	MailDBData();
	~MailDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nMailId;
	int32_t nType;
	int32_t nTime;
	std::string strSender;
	std::string strTitle;
	std::string strContent;
	std::string strItems;
};

class MemAttrData
{
public:
	MemAttrData();
	~MemAttrData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nAttr[32];
};

class MemCharacterData
{
public:
	MemCharacterData();
	~MemCharacterData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nLevel;
	int32_t nExp;
	int32_t nJob;
};

class MemChrActionData
{
public:
	MemChrActionData();
	~MemChrActionData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nActionId;
	int32_t nCount;
	int32_t nLastTime;
};

class MemChrAutoFightData
{
public:
	MemChrAutoFightData();
	~MemChrAutoFightData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nEnabled;
	int32_t nEndTime;
};

class MemChrBagData
{
public:
	MemChrBagData();
	~MemChrBagData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::vector<MemChrBag> items;
};

class MemChrBuffData
{
public:
	MemChrBuffData();
	~MemChrBuffData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strBuffs;
};

class MemChrDepotData
{
public:
	MemChrDepotData();
	~MemChrDepotData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strDepot;
};

class MemChrEquipData
{
public:
	MemChrEquipData();
	~MemChrEquipData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strEquips;
};

class MemChrGemData
{
public:
	MemChrGemData();
	~MemChrGemData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strGems;
};

class MemChrSkillData
{
public:
	MemChrSkillData();
	~MemChrSkillData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strSkills;
};

class MemChrSystemSettingData
{
public:
	MemChrSystemSettingData();
	~MemChrSystemSettingData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strSettings;
};

class MemChrTaskCycleData
{
public:
	MemChrTaskCycleData();
	~MemChrTaskCycleData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nCycle;
	std::string strTasks;
};

class MemChrTaskData
{
public:
	MemChrTaskData();
	~MemChrTaskData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strTasks;
};

class MoneyRewardTaskData
{
public:
	MoneyRewardTaskData();
	~MoneyRewardTaskData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nTaskId;
	int32_t nStatus;
	int32_t nCount;
};

class MysteryShopDBData
{
public:
	MysteryShopDBData();
	~MysteryShopDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nShopId;
	std::string strData;
};

class NationalDayData
{
public:
	NationalDayData();
	~NationalDayData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strData;
};

class OperateLimitDBData
{
public:
	OperateLimitDBData();
	~OperateLimitDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nType;
	int32_t nCount;
	int32_t nLastTime;
};

class PetDBData
{
public:
	PetDBData();
	~PetDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nPetId;
	int32_t nLevel;
	int32_t nExp;
	std::string strData;
};

class PortalDBData
{
public:
	PortalDBData();
	~PortalDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nPortalId;
	std::string strData;
};

class ScoreShopData
{
public:
	ScoreShopData();
	~ScoreShopData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nShopId;
	std::string strData;
};

class ShangChengData
{
public:
	ShangChengData();
	~ShangChengData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::string strData;
};

class SysUserData
{
public:
	SysUserData();
	~SysUserData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int64_t nUid;
	int32_t nSid;
	std::string strData;
};

class SysUserPreventWallowData
{
public:
	SysUserPreventWallowData();
	~SysUserPreventWallowData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	struct WallowData {
		int64_t uid;
		int32_t sid;
		char name[64];
		char identitycard[32];
		int32_t isGrowUp;
	} data;
};

class TouZiData
{
public:
	TouZiData();
	~TouZiData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nTouZiId;
	int32_t nLevel;
	std::string strData;
};

class VipData
{
public:
	VipData();
	~VipData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nVipLevel;
	int32_t nVipExp;
	int32_t nVipTime;
	std::string strData;
};

class WorshipDBData
{
public:
	WorshipDBData();
	~WorshipDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nCount;
	int32_t nLastTime;
	std::string strData;
};

class WuHunShopDBData
{
public:
	WuHunShopDBData();
	~WuHunShopDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nShopId;
	std::string strData;
};

class XinMoDBData
{
public:
	XinMoDBData();
	~XinMoDBData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	bool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t nXinMoId;
	int32_t nLevel;
	int32_t nExp;
	std::string strData;
};

//////////////////////////////////////////////////////////////////////////
// MemChrSignInfo - sign-in info
//////////////////////////////////////////////////////////////////////////
struct MemChrSignInfo
{
	MemChrSignInfo() : sign_record(0), refresh_time(0) {}

	void CleanUp();

	int32_t sign_record;
	int32_t refresh_time;
	std::vector<int8_t> sign_reward;
};

//////////////////////////////////////////////////////////////////////////
// MemEquip - in-memory equipment data
//////////////////////////////////////////////////////////////////////////
class MemEquip
{
public:
	MemEquip();
	~MemEquip();

	void CleanUp();
	void PackageData(Answer::NetPacket* packet);
	void UnPackageData(Answer::NetPacket* inPacket);
	void PackageClientData(Answer::NetPacket* packet);

public:
	int64_t id;
	int32_t base;
	int64_t owner;
	int8_t  star;
	std::string name;
	int32_t time;
	int32_t MapId;
	int32_t Mid;
	int32_t Lucky;
};

//////////////////////////////////////////////////////////////////////////
// MemPetDBData - in-memory pet DB data
//////////////////////////////////////////////////////////////////////////
struct MemPetDBData
{
	MemPetDBData() : nOwner(0), nPetId(0), nBaseId(0) {}

	void CleanUp();

	int64_t nOwner;
	int32_t nPetId;
	int32_t nBaseId;
	std::string strName;
	std::string skills;
	std::string equips;
};

//////////////////////////////////////////////////////////////////////////
// PlayerDBData - aggregate player DB data
//////////////////////////////////////////////////////////////////////////
class PlayerDBData
{
public:
	PlayerDBData();
	~PlayerDBData();

	void CleanUp();
	void PackageData(Answer::NetPacket* packet, CharId_t nCid);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	int32_t connid;
	int32_t cgindex;
	int32_t loadTime;
	int32_t saveRefCount;

	MemCharacterData chr;
	MemAttrData attrData;
	SysUserData sysUser;
	DailyActivityData signInfo;
	MemChrEquipData equipData;
	MemChrGemData gemData;
	MemChrBagData bagData;
	MemChrSkillData skillData;
	MemChrTaskData taskData;
	MemChrTaskCycleData taskCycleData;
	MemChrActionData actionData;
	MemChrAutoFightData autoFight;
	MemChrSystemSettingData systemSetting;
	MemChrBuffData buffData;
	MemChrDepotData gambleDepot;
	SysUserPreventWallowData sysUserPreventWallow;
	CurrencyDBData m_CurrencyData;
	OperateLimitDBData m_OperateLimit;
	PetDBData m_CharPets;
	FriendExpReward m_FriendExpReward;
	MailDBData m_MailDBData;
	ShangChengData m_ShangChengData;
	BossKilledRewardData m_BossKilledReward;
	CFaBaoData m_FaBaoData;
	CGoblinData m_CGoblinData;
	CharFamilyDBData m_FamilyData;
	WorshipDBData m_WorshipData;
	CJueWeiData m_JueWeiData;
	ScoreShopData m_ScoreShopData;
	TouZiData m_TouZiData;
	CHuoYueDuData m_HuoYueDuData;
	MysteryShopDBData m_MysteryShopDBData;
	ExchangeDBData m_ExchangeDBData;
	CharWishDBData m_WishDBData;
	CVplanData m_VplanData;
	CharWingDBData m_CharWingDBData;
	MagicBoxDBData m_MagicBoxDBData;
	VipData m_vipData;
	CShiZhuangData m_ShiZhuangData;
	CMonthlyChouJiangData m_CMonthlyChouJiangData;
	ChouJiangData m_ChouJinagData;
	MoneyRewardTaskData m_MoneyRewardTaskData;
	WuHunShopDBData m_WuHunShopDBData;
	CMingGeData m_CMingGeData;
	CKunData m_CKunData;
	CFlopDraw m_CFlopDraw;
	CSevenDayData m_CSevenDayData;
	PortalDBData m_PortalDBData;
	XinMoDBData m_XinMoDBData;
	CLittleHelperData m_CLittleHelper;
	NationalDayData m_NationalDayData;
	EquipRongHeData m_EquipRongHeData;
};

//////////////////////////////////////////////////////////////////////////
// ItemData - item data struct
//////////////////////////////////////////////////////////////////////////
struct ItemData
{
	int32_t m_nId;
	int32_t m_nClass;
	int32_t m_nCount;

	bool IsEmpty() const;
};

//////////////////////////////////////////////////////////////////////////
// CKunData - Kun system DB data
//////////////////////////////////////////////////////////////////////////
class CKunData
{
public:
	CKunData();
	~CKunData();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	void PackageData(Answer::NetPacket* packet, CharId_t nCid);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

	std::string getLingZhuPosString();
	void parseLingZhuPos(const std::string& p_PosString);
	std::string getDanTianString();
	void parseDanTian(const std::string& p_DanTianString);

public:
	int32_t m_nBuyTime;
	int32_t m_nLianHuaTime;
	int32_t m_nKunLevel;
	int32_t m_nExp;
	struct LingZhuPosData { int32_t nId; int32_t nLevel; } m_LingZhuPos[10];
	struct LingZhuBagSlot { int32_t nId; int32_t nCount; } m_LingZhuBag[100];
	struct DanTianSlot { int32_t nMid; int32_t nId; int32_t nEndTime; } m_DanTian[6];
};

//////////////////////////////////////////////////////////////////////////
// CFlopDraw - Flop draw DB data
//////////////////////////////////////////////////////////////////////////
class CFlopDraw
{
public:
	CFlopDraw();
	~CFlopDraw();

	void CleanUp();
	void SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);
	void PackageData(Answer::NetPacket* packet, CharId_t nCid);
	void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

public:
	std::map<int32_t, std::map<int32_t, int32_t> > m_FlopDrawRecordMap;
};

//////////////////////////////////////////////////////////////////////////
// RandHelper - random utility
//////////////////////////////////////////////////////////////////////////
class RandHelper
{
public:
	static int32_t CalRandTimes(int32_t nTotalTimes, int32_t nRate, int32_t nTotalRate);
};
