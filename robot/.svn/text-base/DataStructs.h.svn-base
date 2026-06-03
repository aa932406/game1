#pragma once

#include <cmath>
#include <list>
#include <map>
#include <string>
#include <vector>


#define  PK_PROTECT_TIME 3600
enum PkMode
{
	PK_MODE_FREE		= 0,	//无效
	PK_MODE_PEACE		= 1,	//和平模式
	PK_MODE_TEAM		= 2,	//组队模式
	PK_MODE_LEGION		= 3,	//军团模式
	PK_MODE_GOOD_EVIL	= 4,	//善恶模式
	PK_MODE_SERVER		= 5,	//本盟模式
	PK_MODE_ALL			= 6,	//全体模式	
	PK_MODE_COUNT,
};

enum NameColour
{
	NAME_COLOUR_WHITE	= 1,	//白名
	NAME_COLOUR_RED		= 2,	//红名
	NAME_COLOUR_BLACK	= 3,	//黑名
};

enum PkValue
{
	PK_VALUE_WHITE		= 20,	//白名pk值
	PK_VALUE_RED		= 100,	//红名pk值
};

enum MonsterType
{
	MT_MONSTER = 0,
	MT_TRAP = 1,
};

enum ExchangeGetType
{
	EGT_ITEM = 1,
	EGT_EQUIP = 2,
	EGT_MONEY = 3,
	EGT_EXP = 4,
	EGT_RAND_ITEM = 11,
};

//地图类别
enum MapType
{
	MT_NORMAL		= 1,		// 普通地图
	MT_DUNGEON		= 2,		// 副本地图
	MT_ACTIVITY		= 4,		// 活动地图
};

enum PlantType
{
	PT_NORMAL = 0,
	PT_FAMILY_FRUIT = 1,
	PT_FAMILY_FISH = 2,
};

enum RegionId
{
	RI_KINGDOM_WAR_BASE = 42000,
	RI_FAMILY_WAR_ATTACK = 55001,
	RI_FAMILY_WAR_DEFENSE = 55002,
	RI_OFFLINE_EXP = 90000,
	RI_ZHUCHENG =20001,
};

enum RegionType
{
	RNT_SAFE = 1,
	RNT_TRADE = 2,
	RNT_TASK = 3,
};

enum GameEventType
{
	GET_BOSS_DIE = 1,
	GET_BOSS_REVIVE = 2,
	GET_COMPLETE_DUNGEON = 3,
	GET_ARRIVE_LEVEL = 4,
	GET_ARTIFACT_LEVEL = 5,
	GET_ENHANCE_EQUIP = 6,
	GET_GET_EGG = 7,
	GET_CREATE_FAMILY = 8,
	GET_KILL_PLAYER_REPUTATION = 9,
	GET_TREASURE = 10,
	GET_TRAILER = 11,
	GET_KILL_PLAYER_PKVALUE = 12,
	GET_PICK_DROP_ITEM = 13,
	GET_TRAILER_KILLER = 14,
	GET_ONLINE = 15,
};

enum InstanceMoveReason
{
	IMR_PULL_BACK = 1,
	IMR_TRANSFER = 2,
	IMR_SKILL = 3,
	IMR_ACTIVITY = 4,
	IMR_JUMP = 5,
	IMR_SPOUSE_MOVE = 6,
	IMR_HIT = 7,
};

enum SuperExchangeType
{
	SET_EXP = 1,
	SET_MONEY = 2,
	SET_JUNGONG = 3,
	SET_JIANGXING = 4,
	SET_WUHUN = 5,
	SET_CASH = 6,
	SET_GOLD = 7,
};

enum BenefitType
{
	BT_NORMAL = 1,
	BT_TIRED = 2,
	BT_HURT = 3,
};

enum ConsumeCostType
{
	CCT_NONE = 0,
	CCT_MONEY = 1,
	CCT_SYS_GOLD = 2,
	CCT_GOLD = 3,
};

struct SuperExchangeToItem
{
	int32_t type;
	int32_t value;
};

typedef std::vector<SuperExchangeToItem> SuperExchangeToItemVector;

#define PULL_BACK_DISTANCE 6
#define TRANSFER_DISTANCE 18

#define MAX_DROPITEM_SIZE 24

#define PLAYER_GENERAL_CD_MS 750
#define ITEM_CD_GROUP_COUNT 5

#define MAX_UNIT_BUFF_NUM 14

typedef std::list<int8_t> Int8List;
typedef std::vector<int8_t> Int8Vector;
typedef std::list<int16_t> Int16List;
typedef std::vector<int16_t> Int16Vector;
typedef std::list<int32_t> Int32List;
typedef std::vector<int32_t> Int32Vector;
typedef std::map<int32_t, int32_t> Int32Int32Map;
typedef std::map<int32_t, Int32Vector> Int32Int32VectorMap;
typedef std::list<CharId_t> CharIdList;

struct DropItem 
{
	int32_t itemId;
	int8_t	itemClass;
	int8_t	bindType;
	int32_t itemCount;
	Time_t	endTime;	
	int64_t	srcId;
	int32_t costType;
	int32_t costValue;
};

struct DungeonNumReward
{
	int32_t exp;
	int32_t money;
	int32_t gold;
	int32_t jungong;
	int32_t wuhuen;
	int32_t jiangxing;
};



struct AchievementCount
{
	 int32_t  level;
	 int32_t  count;
};
typedef std::map<int32_t,AchievementCount>AchievementCountTable;
 
struct  DungeonGroupReward
{
	  int32_t dungeonID;
	  MemChrBagVector items;
};
typedef std::vector<DungeonGroupReward>DungeonGroupRewardVector;

struct DungeonHPEvent
{
	int32_t minhp;
	int32_t maxhp;
};
typedef std::vector<DungeonHPEvent>DungeonHPEventVector;

//struct PlayerEntrustState
//{
//	int32_t time;
//	Int32Vector dungeons;
//};

//struct PlayerAdvancedTrialsState
//{
//	int32_t time;
//	Int32Vector dungeons;
//};


struct EquipPatchEnhanceInfo
{
	 int32_t money;
	 int32_t time;
};

//struct  MountFormInfo
//{
//	  int32_t id;
//	  int32_t quality;
//	  int32_t type;
//	  int32_t value;
//};
//typedef std::vector<MountFormInfo>MountFormInfoVector;


//struct FirstAttr 
//{
//	int32_t str;
//	int32_t wis;
//	int32_t mag;
//	int32_t vit;
//	int32_t men;
//};

struct UnitAttr 
{
	int32_t hp;			// 生命值
	int32_t mp;			// 法力值
	int32_t pp;			// 体力值
	int32_t xp;			// 必杀值
};

//struct PlayerAttr 
//{
//	int32_t exp_rate;
//	int32_t money_rate;
//};

struct UnitHandle 
{
	explicit UnitHandle(int32_t id_ = 0, int32_t type_ = 0)
		: id(id_), type(type_)
	{

	}

	bool operator==(const UnitHandle &param) const
	{
		return id == param.id && type == param.type;
	}

	bool operator!=(const UnitHandle &param) const
	{
		return id != param.id || type != param.type;
	}

	bool isEmpty() const
	{
		return id == 0 || type == 0;
	}

	void clear()
	{
		id = 0;
		type = 0;
	}

	int32_t id;
	int32_t type;
};

struct AttrAddon
{
	int32_t index;
	int32_t addon;
};
typedef std::list<AttrAddon> AttrAddonList;
typedef std::vector<AttrAddon> AttrAddonVector;
typedef std::map<int32_t,AttrAddon>AttrAddonTable;

struct AttrAddonArtifact
{
	int32_t index;
	int32_t addon;
	int32_t ratio;
};
typedef std::vector<AttrAddonArtifact> AttrAddonArtifactVector;

struct SkillResult 
{
	explicit SkillResult(int32_t unitid_ = 0, int32_t unittype_ = 0, int32_t hpchange_ = 0, int32_t state_ = 0, int32_t buffid_ = 0, int32_t buffDuration_ = 0)
		: unitid(unitid_), unittype(unittype_), hpchange(hpchange_), attackState(state_), buffid(buffid_), buffDuration(buffDuration_)
	{

	}

	int32_t unitid;
	int32_t unittype;
	int32_t hpchange;
	int32_t attackState;
	int32_t buffid;
	int32_t buffDuration;
};
typedef std::vector<SkillResult> SkillResultVector;

struct Position 
{
	explicit Position(int32_t x_ = 0, int32_t y_ = 0)
		: x(x_), y(y_)
	{

	}

	bool operator==(const Position &param) const
	{
		return x == param.x && y == param.y;
	}

	bool operator!=(const Position &param) const
	{
		return x != param.x || y != param.y;
	}

	double distance(const Position &pos) const
	{
		return sqrt(static_cast<double>((pos.x-x)*(pos.x-x) + (pos.y - y)*(pos.y - y)));
	}

	int32_t tileDistance(const Position &pos) const
	{
		return (std::max)(std::abs(x-pos.x), std::abs(y-pos.y)/2);
	}

	int32_t x;
	int32_t y;
};
typedef std::vector<Position> PositionVector;

struct TaskRequest 
{
	int32_t param1;
	int32_t param2;
	int32_t param3;
};

struct activityRankData
{
	int32_t rank;
	int32_t id;//帮派ID或人物ID或国家ID
	int32_t count; //比赛场次（比武时用）
	int32_t jifen;
	int32_t aid;
	int32_t kingDomId;

	activityRankData()
	{
		reset();
	}

	void reset()
	{
		rank=0;
		id=0;
		count =0;
		jifen=0;
		aid=0;
		kingDomId = 0;
	}
};
typedef std::vector<activityRankData> ActivityRankVector;

struct FormationLocationType
{
	int32_t        isplayer;
	int32_t        roleID;
    
	bool operator==(const FormationLocationType&LocationType)
	{
		return (isplayer == LocationType.isplayer && roleID == LocationType.roleID);
	}

	void operator = (const FormationLocationType&LocationType)
	{
		   isplayer = LocationType.isplayer;
		   roleID   = LocationType.roleID;
	}
};

struct FormationRoleLocation
{
	FormationLocationType  frontRoleID;
	FormationLocationType  leftMidRoleID;
	FormationLocationType  mainMidRoleID;
	FormationLocationType  rightMidRoleID;
	FormationLocationType  leftBacktRoleID;
	FormationLocationType  mainBacktRoleID;
	FormationLocationType  rightBackRoleID;

	bool operator==(const FormationRoleLocation &roleLocation)
	{
		return  (frontRoleID == roleLocation.frontRoleID        && leftMidRoleID ==roleLocation.leftMidRoleID   && leftMidRoleID ==roleLocation.leftMidRoleID           && 
			rightMidRoleID == roleLocation.rightMidRoleID   && leftBacktRoleID == roleLocation.leftBacktRoleID  && mainBacktRoleID ==roleLocation.mainBacktRoleID   && 
			rightBackRoleID ==roleLocation.rightBackRoleID  );
	}

	void operator = (const FormationRoleLocation &roleLocation)
	{
		frontRoleID = roleLocation.frontRoleID   ;        
		leftMidRoleID  = roleLocation.leftMidRoleID ;    
		leftMidRoleID  = roleLocation.leftMidRoleID ;
		rightMidRoleID  = roleLocation.rightMidRoleID ;
		leftBacktRoleID  = roleLocation.leftBacktRoleID ;
		mainBacktRoleID  = roleLocation.mainBacktRoleID ;
		rightBackRoleID = roleLocation.rightBackRoleID ;
	}
};

struct AcChallengeFBInfo
{
	  int32_t   id;
	  int32_t   point;
};
typedef std::vector<AcChallengeFBInfo>AcChallengeFBInfoVector;

struct AcExchangeItem
{
       int32_t id;
	   int32_t count;
	   Job_t job;
};
typedef std::vector<AcExchangeItem>AcExchangeItemVector;

struct AcExchange
{
	int32_t group;
	int32_t point;
	int32_t group_first;
	int32_t money;
	int32_t exp;
	int32_t gold;
	int32_t jiangxing;
	int32_t wuhuen;
	AcExchangeItemVector item;
};

struct SignVipReward
{
	int32_t vip_order;
	MemChrBagVector item;
};
typedef std::vector<SignVipReward>SignVipRewardVector;


struct TaskMonster 
{
	int32_t tid;
	int32_t condition;
	TaskRequest request;
};

struct DailyRecord
{
     int32_t id;
	 int32_t mark;
	 int32_t need_count;
	 int32_t count;
	 int32_t type;
};
typedef std::vector<DailyRecord>DailyRecordVector;
typedef std::map<int32_t,DailyRecord>DailyRecordTable;

struct FamilyRegion
{
	int32_t family_index;
	int32_t x;
	int32_t y;
};
typedef std::vector<FamilyRegion>FamilyRegionVector;
typedef std::map<int32_t,FamilyRegion>FamilyRegionTable;


#define TASK_CYCLE_GROUP_COUNT 10

enum MonsterBroadcastState
{
	MBS_INACTIVE,
	MBS_ALIVE,
	MBS_DEAD,
};

struct MountAttr
{
	int32_t attr;
	int32_t pdef;
	int32_t mdef;
	int32_t hp;
	int32_t vp;
	int32_t bp;
	int32_t htip;
};
typedef std::vector<MountAttr> mountAttrVector;

struct MonsterBroadcast 
{
	int32_t mid;
	int32_t state;
	std::string last_killer;
	int32_t next_revive;
	int32_t kingdom;
};
typedef std::vector<MonsterBroadcast> MonsterBroadcastVector;


struct MonsterSkill 
{
	int32_t maxHp;
	int32_t minHp;
	int32_t skillid;
	bool	done;
};
//typedef std::vector<MonsterSkill> MonsterSkillVector;

struct MonsterWave 
{
	bool alive()
	{
		return count > killed+escaped;
	}
	int32_t count;
	int32_t	killed;
	int32_t	escaped;
	int64_t startTime;
};
typedef std::map<int32_t, MonsterWave> Int32MonsterWaveMap;

enum Direction
{
	INVALID_DIRECTION = -1,
	DOWN = 0,
	DOWN_RIGHT = 1,
	RIGHT = 2,
	UP_RIGHT = 3,
	UP = 4,
	UP_LEFT = 5,
	LEFT = 6,
	DOWN_LEFT = 7,	
	DIRECTION_NUM = 8,
};

enum LogSignInfoFlag
{
	LSIF_NEW_MONTH = 1,
	LSIF_SIGN = 2,
	LSIF_GET_REWARD = 3,
};

#define PI 3.14159265

#define MAX_PLAYER_LEVEL 190
#define MAX_AUTO_UPGRADE_PLAYER_LEVEL 190
#define MAX_NO_POTENTIAL_PLAYER_LEVEL 10
#define MAX_FIRST_PLAYER_LEVEL 190
#define MAX_SECOND_PLAYER_LEVEL 250
#define MAX_THREE_PLAYER_LEVEL 300

#define DEAL_SLOT_NUM 11 //0 is valid, 10 slot for items, last slot for money
#define STALL_SLOT_NUM 25 //slot 0 for invalid check, max 24 slot

enum DealResult
{
	DR_SUCCESS = 0,
	DR_CANCELED = 1,
	DR_FAILED = 2,
};

struct BagSlot 
{
	int32_t bag;
	int32_t slot;
};
typedef std::vector<BagSlot> BagSlotVector;
typedef std::vector<BagSlotVector> BagSlotVectorVector;

class Unit;
typedef std::list<Unit*> UnitList;
typedef std::vector<Unit*> UnitVector;

class Monster;
typedef std::list<Monster*> MonsterList;
typedef std::map<int32_t, Monster*> Int32MonsterMap;

class Npc;
typedef std::list<Npc*> NpcList;

class Player;
typedef std::list<Player*> PlayerList;
typedef std::vector<Player*> PlayerVector;
typedef std::map<int32_t, Player*> Int32PlayerMap;

class CObjPet;
typedef std::list<CObjPet*> ObjPetList;
typedef std::map<PetId_t,CObjPet*> ObjPetMap;

class Trailer;
typedef std::list<Trailer*> TrailerList;
typedef std::map<int32_t, Trailer*> Int32TrailerMap;

//class CDropItemGroup;
//typedef std::list<CDropItemGroup*> DropItemGroupList;

class Plant;
typedef std::list<Plant*> PlantList;

class Trap;
typedef std::list<Trap*> TrapList;

struct MemFamilyWar 
{
	int32_t family_id;
	std::string family_name;
};

struct ChangeJobIndex
{
	int32_t  job;
	int32_t  replace_id;
};
typedef std::vector<ChangeJobIndex> ChangeJobIndexVector;

enum GameMsgCode
{
	GMC_UNKNOWN,

	GMC_PLAYER_ENTER_MAP,
	GMC_PLAYER_LEAVE_MAP,
	GMC_ADD_DUNGEON,			// 创建副本
	GMC_DEL_DUNGEON,			// 回收副本
	GMC_PLAYER_LOGOUT,			// 玩家登出


	//GMC_UNIT_SKILL_DELAY_RESULT,

	GMC_ACTIVITY_START,
	GMC_ACTIVITY_STOP,

	//GMC_OPEN_ACTIVITY_MAP,		// 废弃
	//CMC_ACTIVITY_DUNGEONEND,	// 废弃//删除活动副本地图
	//CMC_ACTIVITY_DUNGERUN,
	//CMC_ACTIVITY_DUNGSTOP,
	//CMC_FAMILY_ACTIVITY_LEAVE,
	//GMC_FAMILY_OPEN_MAP,		// 废弃
	//GMC_FAMILY_CLOSE_MAP,		// 废弃
	//GMC_FAMILY_ADD_APPLIER,
	//GMC_BUY_GAME_SHOP,
};

class GameMsg 
{
public:
	GameMsg()
	{

	}

	void reset()
	{
		msgcode = GMC_UNKNOWN;
		ptr1 = NULL;
		ptr2 = NULL;
		ptr3 =NULL;
		iparam1 = 0;
		iparam2 = 0;
		effecttick = 0;
	}

	GameMsgCode msgcode;
	void *ptr1;
	void *ptr2;
	void *ptr3;
	int32_t iparam1;
	int32_t iparam2;
	int64_t effecttick;
};
typedef Answer::SafeQueue<GameMsg*> GameMsgQueue;


#define EX_ACTIVITY_NUM 3   //不计算充值活动
#define BI_HERO_BUFF 9002//英雄副本英雄状态


enum DungeonDropGroupType
{
	DDGT_ORDINARY = 1,
	DDGT_HERO = 2,
};

enum AddXiuweiType
{
	AXT_XIUWEIDAN = 1,
	AXT_LINGTAIFUDI = 2,
};

#define DAILY_READ_MAX 10

#define LAN_AND_VAL_START_TIME 1392307200
#define LAN_AND_VAL_END_TIME 1392911999
#define LAN_AND_VAL_GIFT_ITEM 518
#define DIAMOND_RING_ITEM 605

#define MAX_PK_VALUE 999
#define PK_DROP_COIN_ITEM 100100
#define PK_DROP_COIN_VALUE 50000
#define CLEAR_PK_VALUE_PER_ITEM 300


#define PRISON_MAP_ID 70003		// 监狱地图id
#define PRISON_X    50			// 监狱坐标x
#define PRISON_Y	50			// 监狱坐标y
