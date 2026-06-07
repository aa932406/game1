#pragma once

#include <string>
#include "DataStructs.h"

//////////////////////////////////////////////////////////////////////////
// Log Classes - for recording game events
//////////////////////////////////////////////////////////////////////////

class platform_log_base
{
public:
	platform_log_base();
	virtual ~platform_log_base();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	int32_t nTime;
	int32_t nSid;
};

class boss_log
	: public platform_log_base
{
public:
	boss_log();
	virtual ~boss_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t kill_time;
	int32_t mid;
	int32_t boss_id;
};

class bossjoin_log
	: public platform_log_base
{
public:
	bossjoin_log();
	virtual ~bossjoin_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t join_time;
	int32_t mid;
	int32_t boss_id;
	int32_t mapId;
	int32_t killed;
};

class currency_log
	: public platform_log_base
{
public:
	currency_log();
	virtual ~currency_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t time;
	int8_t type;
	int32_t opway;
	int64_t value;
	std::string ids;
	std::string couts;
	int32_t level;
};

class death_log
	: public platform_log_base
{
public:
	death_log();
	virtual ~death_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t level;
	int32_t mapId;
	int32_t killerType;
	int64_t killerId;
	std::string killerName;
};

class item_log
	: public platform_log_base
{
public:
	item_log();
	virtual ~item_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t time;
	int32_t itemId;
	int32_t opway;
	int32_t count;
	int32_t level;
};

class level_up_log
	: public platform_log_base
{
public:
	level_up_log();
	virtual ~level_up_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t oldLevel;
	int32_t newLevel;
};

class logout_log
	: public platform_log_base
{
public:
	logout_log();
	virtual ~logout_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t level;
	int32_t onlineTime;
};

class main_task_log
	: public platform_log_base
{
public:
	main_task_log();
	virtual ~main_task_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t taskId;
	int32_t taskState;
};

class online_user_24th_log
	: public platform_log_base
{
public:
	online_user_24th_log();
	virtual ~online_user_24th_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	int32_t nOnlineCount;
	int32_t nTime;
};

class proc_log
	: public platform_log_base
{
public:
	proc_log();
	virtual ~proc_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	int32_t nProcId;
	int32_t nOnlineCount;
	int32_t nCpuUsage;
	int32_t nMemUsage;
};

class skill_log
	: public platform_log_base
{
public:
	skill_log();
	virtual ~skill_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t skillId;
	int32_t skillLevel;
	int32_t targetId;
};

class log_abnormal
{
public:
	log_abnormal();
	~log_abnormal();

	void PackageData(Answer::NetPacket* packet);

public:
	int64_t nCid;
	std::string sName;
	int8_t nType;
	int32_t nValue;
	int32_t nOpway;
};

class important_system_log
	: public platform_log_base
{
public:
	important_system_log();
	virtual ~important_system_log();

	virtual void CleanUp();
	virtual void PackageData(Answer::NetPacket* packet);
	virtual void UnPackageData(Answer::NetPacket* inPacket);

public:
	std::string passport;
	int64_t cid;
	std::string name;
	int32_t up_time;
	int32_t sys_name;
	int32_t oper_id;
	int32_t level;
};

//////////////////////////////////////////////////////////////////////////
// Other missing classes
//////////////////////////////////////////////////////////////////////////

struct BlackMarketIndex
{
	int32_t nDays;
	int32_t nIndex;
	int32_t nJob;

	bool operator<(const BlackMarketIndex& right) const;
};

class NpcDungeon
	: public Npc
{
public:
	NpcDungeon();
	virtual ~NpcDungeon();

	void init(Dungeon* dungeon, const CfgNpc* cfgNpc);
	virtual int32_t onEndNpc(Player* player, int8_t choice);

private:
	Dungeon* m_dungeon;
};

class StaticObj
{
public:
	StaticObj();
	virtual ~StaticObj();

	void reset();
	int32_t getMapId();
	int32_t getMapType();
	bool InDungeon();
	bool InActivity();
	bool InPrison();
	int32_t GetRunnerId();
	bool IsSpecialBossMap();
	bool IsCycleTower();
	bool IsKuangDong();
	bool IsTerritory();

protected:
	Map* m_pMap;
	Position m_currentTile;
	Position m_currentPos;
};
