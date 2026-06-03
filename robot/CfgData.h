#pragma once
//////////////////////////////////////////////////////////////////////////
//author:zxj		modify time:2012-7-7
//description:游戏中结构的结构定义
//////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "Shared.h"
struct AddAttribute
{
	AddAttribute()
		: m_nAddAttrType( 0 )
		, m_nAddAttrValue( 0 )
	{
	}
	uint8_t	m_nAddAttrType;
	int32_t	m_nAddAttrValue;
};
typedef std::list<AddAttribute> AddAttrList;

class ChrMount;

//活动数据结构
struct CfgActivity 
{
	int32_t id;							//id标识符
	int16_t	typeId;						//类别
	Int32Vector weekday;				//活动的时间范围(1234567);s
	int32_t begin_date;					//活动开始时间
	int32_t end_date;					//活动结束时间
	int32_t line;						//分线
	int16_t kingdom;					//国家
	int32_t start_hour;					//起初时间
	int32_t duration;					//活动总长度
	int32_t level;
	int32_t target_mapid;				//当前的地图ID
	Int32Vector target_regiona;				//地图上所在的X坐标
	Int32Vector target_regionb;				//地图上所在的Y坐标
	int32_t state;						//活动的状态类型
	Int32Vector gift_id;				//奖
	int32_t exp_add_interval;
};
//活动列表
typedef std::map<int32_t, CfgActivity> CfgActivityTable;

//活动事件
struct CfgActivityEvent
{
	int32_t activity_id;				//活动Id
	int32_t trigger_id;					//触发事件ID
	int32_t trigger_type;				//触发类型
	Int32Vector trigger_param;			//触发参数s
	int32_t event_type;					//事件类型
	Int32Vector event_effect;			//事件效果s
	std::string dialog;					//弹出的信息
										
	bool done;							//是否完成
};
//一个活动的事件列表
typedef std::vector<CfgActivityEvent> CfgActivityEventVector;
//所有活动的事件表
typedef std::map<int32_t, CfgActivityEventVector> CfgActivityEventTable;

struct CfgActivityBanquet
{
	  int32_t activity_id;
	  FamilyRegionVector han_region;
	  FamilyRegionVector chu_region;
	  int32_t  x;
	  int32_t  y;
};
typedef std::vector<CfgActivityBanquet> CfgActivityBanquetVector;

//活动怪物
struct CfgActivityMonster 
{
	int32_t id;							//ID标识符
	int32_t activity_id;				//活动ID
	int32_t monster_id;					//怪物ID
	int32_t count;						//怪物个数
	int32_t wave;						//一波
	int32_t kingdom;					//国家
	Int32Vector region_id;				//区域IDs
	int8_t side;
};
//一个活动中的怪物表
typedef std::vector<CfgActivityMonster> CfgActivityMonsterVector;
//所有活动中的怪物表
typedef std::map<int32_t, CfgActivityMonsterVector> CfgActivityMonsterTable;

//活动Npc
struct CfgActivityNpc 
{
	int32_t id;							//ID标识符
	int32_t activity_id;				//活动ID
	int32_t npc_id;						//ncp ID
	int32_t count;						//NPC个数
	Int32Vector region_id;				//区域IDs
};
//一个活动中的NPC表
typedef std::vector<CfgActivityNpc> CfgActivityNpcVector;
//所有活动中的NPC表
typedef std::map<int32_t, CfgActivityNpcVector> CfgActivityNpcTable;


//活动植物
struct CfgActivityPlant 
{
	int32_t id;							//ID标识符
	int32_t activity_id;				//活动ID
	int32_t plant_id;					//植物ID
	int32_t count;						//植物个数
	int32_t wave;						//发动
	int32_t region_id;					//区域ID
	int32_t whoplant;					//采集者
};
//一个活动中的植物表
typedef std::vector<CfgActivityPlant> CfgActivityPlantVector;
//所有活动中的植所有活动
typedef std::map<int32_t, CfgActivityPlantVector> CfgActivityPlantTable;

struct CfgActivityDrop
{
	int32_t id;
	int32_t activity_id;
	int32_t monster_min_level;
	int32_t drop_group_id;
	int32_t probability;
};
typedef std::map<int32_t, CfgActivityDrop> CfgActivityDropTable;


struct CfgAnnoucementTime
{
	int32_t id;
	Int32Vector weekday;
	int32_t begin_date;
	int32_t end_date;
	int32_t hour;
	int32_t minute;
	int32_t annoucement_id;
};
typedef std::vector<CfgAnnoucementTime> CfgAnnoucementTimeTable;

struct BuffAttr //技能攻击属性。。大小之类的
{
	int32_t getRatio(int32_t level)
	{
		return roundInt(ratio_base + ratio_ratio*level*0.1);
	}

	int32_t getAddon(int32_t level)
	{
		return roundInt(addon_base + addon_ratio*level);
	}

	int32_t attr;
	int32_t ratio_base;
	int32_t ratio_ratio;
	int32_t addon_base;
	int32_t addon_ratio;
};

struct CfgBuff //技能效果
{
	int32_t id;
	int32_t beneficial;
	int32_t special;
	int32_t duration;//长短
	int32_t interval;//间隔
	BuffAttr buffAttr[2];
};
typedef std::map<int32_t, CfgBuff> CfgBuffTable;

#define  DAILY_ITEM_COUNT  16
struct CfgDailyItem //每日任务种类名称
{
	int32_t  id;
	int32_t  type;
	int32_t  mark;
	int32_t  count;
	int32_t  level;
	int32_t  isBack;
};

typedef std::map<int32_t,CfgDailyItem>CfgDailyItemTable;

struct CfgDailySearchBack
{
	   int32_t id;
	   int32_t level;
	   int32_t exp;
	   int32_t money;
	   int32_t jungong;
	   int32_t wuhuen;
	   int32_t luck;
	   int32_t jiangxing;
	   MemChrBagVector items; 
};
typedef std::vector<CfgDailySearchBack>CfgDailySearchBackVector;
typedef std::map<int32_t,CfgDailySearchBackVector>CfgDailySearchBackTable;

struct CfgDailyMark
{
	int32_t mark;
	int32_t gift_id;
};
typedef std::map<int32_t,CfgDailyMark>CfgDailyMarkTable;

struct CfgDailyReward
{
	int32_t id;
	int32_t level;
	int32_t value;
};
typedef std::vector<CfgDailyReward>CfgDailyRewardVector;
typedef std::map<int32_t,CfgDailyRewardVector>CfgDailyRewardTable;

struct CfgDungeon 
{
	int32_t id;				// 副本ID
	std::string name;		// 副本名称
	int32_t mapid;			// 地图ID
	int16_t x;				// 进入点X
	int16_t y;				// 进入点Y
	int8_t	type;			// 类型 DungeonType
	int32_t group_id;		// 所在组（共享进入次数）
	int32_t duration;		// 持续时间
	int16_t level;			// 需求等级
	int8_t	vip;			// 需求VIP等级
	int32_t last_id;		// 前一个副本ID
	int32_t next_id;		// 后一个副本ID
	int8_t	player_num;		// 人数限制
	int8_t	weekday;		// 每周开放日
	int8_t	start_hour;		// 每日开始时间
	int8_t	end_hour;		// 每日结束时间
	int8_t	daily_count;	// 每日次数限制
	int32_t player_buff;	// 人物BUFF
	int32_t	double_cost;	// 双倍消耗
	int32_t	reward_time;	// 领取奖励时间(秒)
	ItemData costItem;		// 进入消耗
	MemChrBag rewardOnce;	// 首通奖励
	MemChrBag rewardItem;	// 通关奖励
};
typedef std::vector<CfgDungeon> CfgDungeonVector;
typedef std::map<int32_t, CfgDungeon> CfgDungeonTable;

struct CfgDungeonReward
{
	int32_t dungeonID;
	int32_t exp;
	int32_t money;
	int32_t cash;
	int32_t groupID;
};
typedef std::vector<CfgDungeonReward> CfgDungeonRewardVector;
typedef std::map<int32_t, CfgDungeonReward> CfgDungeonRewardTable;

struct CfgDungeonDropGroup
{
	int32_t id;
	int32_t type;
	int32_t item_id;
	int8_t	item_class;
	int8_t	bind_type;
	int32_t count;
	int32_t weight;
	int32_t probability;
};
typedef std::vector<CfgDungeonDropGroup> CfgDungeonDropGroupVector;
typedef std::map<int32_t, CfgDungeonDropGroupVector> CfgDungeonDropGroupTable;

struct CfgDungeonEvent 
{
	int32_t dungeon_id;
	int32_t trigger_id;
	int32_t type;
	int32_t trigger_type;
	Int32Vector trigger_param;
	int32_t event_type;
	std::string effect;
	std::string dialog;

	bool m_done;
};
typedef std::list<CfgDungeonEvent> CfgDungeonEventList;
typedef std::map<int32_t, CfgDungeonEventList> CfgDungeonEventTable;

typedef std::list<Position> PosList;
struct CfgDungeonMonster 
{
	int32_t id;
	int32_t wave;//怪物波次
	int32_t mid;
	int32_t x;
	int32_t y;
	int32_t count;
	int32_t side;
	PosList road;
	int32_t	delay;	// 刷怪间隔
	int32_t	times;	// 刷怪次数
};
typedef std::map<int32_t, CfgDungeonMonster> CfgDungeonMonsterTable;

struct CfgDungeonPlant 
{
	int32_t id;
	int32_t pid;
	int32_t x;
	int32_t y;
};
typedef std::map<int32_t, CfgDungeonPlant> CfgDungeonPlantTable;

struct CfgDungeonTrap 
{
	int32_t id;
	int32_t tid;
	int32_t x;
	int32_t y;
};
typedef std::map<int32_t, CfgDungeonTrap> CfgDungeonTrapTable;

struct CfgSignReward
{
	int32_t count;
    SignVipRewardVector vip;
};
typedef std::vector<CfgSignReward>CfgSignRewardVector;
typedef std::map<int32_t,CfgSignReward>CfgSignRewardTable;

struct CfgSevenLogin
{
	int32_t days;
	int32_t level;
	int32_t fight_power;
	int32_t point;
	int32_t strategics;
	int32_t enhance;
	int32_t zizhi;
	int32_t kingdom_contribute;
	int32_t mount;
	MemChrBagVector item;
	MemChrJobBagVector job_item;
	int32_t vip;
};
typedef std::map<int32_t,CfgSevenLogin>CfgSevenLoginTable;


struct CfgItemBase 
{
	int32_t id;
	std::string name;
	std::string desc;
	int32_t type;
	int32_t level;
	int32_t grade;
	Job_t job;
	int32_t in_value;
	int32_t out_value;
	int32_t bind;
	int32_t combine;
	int32_t quality;
	std::string url;
	std::string drop_url;
};


struct CfgLevelGift
{
	int32_t level;
	MemChrJobBagVector jobItem;
	MemChrBagVector item;
	int32_t index;
};
typedef std::map<int32_t,CfgLevelGift> CfgLevelGiftTable;

struct CfgItem : public CfgItemBase
{
	std::string effect;//作用效果
	std::string use_method;
	int32_t downgrade;
	int32_t group_id;
	int32_t cd_group;
	int32_t overlay;
	int32_t can_sell;
	int32_t broadcast;
	int32_t valid_time;
	int32_t item_Grade;
};
typedef std::map<int32_t, CfgItem*> CfgItemTable;

struct CfgItemGift 
{
	int32_t id;
	int32_t item;
	int32_t type;
	int32_t count;
	int32_t job;
};
typedef std::vector<CfgItemGift> CfgItemGiftVector;
typedef std::map<int32_t, CfgItemGiftVector*> CfgItemGiftTable;

struct CfgAchievement
{
	int32_t  id;
	Int32Vector outdoor;
	Int32Vector cave;
	Int32Vector daily;
	Int32Vector grow_up;
	int32_t challenge;
	int32_t exchange;
	Int32Vector special;
	int32_t last;
	int32_t next;
};
typedef std::map<int32_t,CfgAchievement>CfgAchievementTable;

struct CfgFamilyLevel
{
	int32_t level;
	Int32Vector rewards;
};
typedef std::map<int32_t,CfgFamilyLevel>CfgFamilyLevelTable;

struct CfgAcOutdoorCave
{
	int32_t id;
	int32_t point;
	int32_t flag;
	int32_t type;
	int32_t target_id;
	int32_t target_count;
	int32_t gold;
	int32_t hufu;
};
typedef std::vector<CfgAcOutdoorCave>CfgAcOutdoorCaveVector;
typedef std::vector<CfgAcOutdoorCave*>CfgAcOutdoorCavePVector;
typedef std::map<int32_t,CfgAcOutdoorCavePVector>CfgAcOutdoorCavePTable;
typedef std::map<int32_t,CfgAcOutdoorCave>CfgAcOutdoorCaveTable;

struct CfgAcDaily
{
	int32_t id;
	int32_t type;
	int32_t flag;
	int32_t target_id;
	Int32Vector point;
	Int32Vector target_count;
	Int32Vector gold;
	Int32Vector hufu;
};
typedef std::vector<CfgAcDaily>CfgAcDailyVector;
typedef std::map<int32_t,CfgAcDaily>CfgAcDailyTable;
//挑战
struct CfgAcChallenge
{
	 int32_t id;
	 AcChallengeFBInfoVector  fb;
	 int32_t point;
	 int32_t change_count;
	 int32_t flag;
};
typedef std::map<int32_t,CfgAcChallenge>CfgAcChallengeTable;

struct CfgAcExchange
{
	 int32_t id;
	 int32_t index;
	 int32_t group;
	 int32_t point;
	 int32_t group_first;
	 int32_t money;
	 int32_t exp;
	 int32_t gold;
	 int32_t jiangxing;
	 int32_t jungong;
	 int32_t wuhuen;
	 int32_t last;
	 int32_t next;
	 AcExchangeItemVector item;
};
typedef std::vector<CfgAcExchange>CfgAcExchangeVector;
typedef std::map<int32_t,CfgAcExchangeVector>CfgAcExchangeTable;

struct CfgAcGrowUp 
{
	 int32_t id;
	 int32_t type;
	 Int32Vector target_value;
	 int32_t point;
	 int32_t flag;
};
typedef std::map<int32_t,CfgAcGrowUp>CfgAcGrowUpTable;

struct CfgAcSpecial
{
	int32_t id;
	int32_t type;
	int32_t point;
	int32_t target;
	int32_t gold;
	int32_t hufu;
};
typedef std::map<int32_t,CfgAcSpecial>CfgAcSpecialTable;

struct CfgAcTask
{
	int32_t id;
	int32_t taskID;
	int32_t point;
};
typedef std::map<int32_t,CfgAcTask>CfgAcTaskTable;

struct CfgItemGiftRandom 
{
	int32_t id;
	int32_t item;
	int32_t type;
	int32_t count;
	int32_t static_probability;
	int32_t sum_probability;
};
typedef std::vector<CfgItemGiftRandom> CfgItemGiftRandomVector;
typedef std::map<int32_t, CfgItemGiftRandomVector*> CfgItemGiftRandomTable;

struct CfgJob 
{
	int32_t id;
	int32_t job_task;
	int32_t attack_attr;
	int32_t base_skill;
};
typedef std::map<int32_t, CfgJob> CfgJobTable;

struct CfgMovie
{
	int32_t id;
};
typedef std::map<int32_t,CfgMovie> CfgMovieTable;

struct CfgLevelExp 
{
	int32_t level;
	int64_t upgrade_exp;
	int64_t max_exp;
	int32_t pet_exp;
	int32_t mount_exp;
	int32_t vicegeneral_id;
};
typedef std::map<int32_t, CfgLevelExp> CfgLevelExpTable;

//地图数据结构
struct CfgMap 
{
	int32_t id;									//ID
	std::string name;							//名称
	int32_t type;								//类别
	int32_t param;								//活动Id差数
	int32_t width;								//宽
	int32_t height;								//高
	int32_t revive;								//复活
	int32_t pk_mode;							//pk模式
	int32_t anti_protect;						//保护模式
	int32_t isMount;							//是否可骑乘
	int32_t isFly;								//是否可以飞
	int32_t isVicegeneral;						//是否多副将
	int32_t player_level;						//玩家等级
	int32_t player_level_max;					//玩家最高等级
	int32_t team_member;						//团队成员数
	int32_t hide_mini;							//隐藏小地图
	int32_t runnerId;							//所属地图线程
};
typedef std::map<int32_t, CfgMap> CfgMapTable;


struct CfgLevelGold
{
	int32_t level;
	int32_t gold;
	int32_t index;
};
typedef std::vector<CfgLevelGold>CfgLevelGoldVector;
typedef std::map<int32_t,CfgLevelGold>CfgLevelGoldTable;

//怪物在地图位置数据结构
struct CfgMapMonster 
{
	int32_t id;							//怪物唯一id
	int32_t mapid;						//地图ID		
	int32_t monsterid;					//怪物ID
	int32_t x;							//x位置
	int32_t y;							//y位置
};
typedef std::map<int32_t, CfgMapMonster> CfgMonsterMap;
//一张地图上怪物列表
typedef std::vector<CfgMapMonster> CfgMapMonsterVector;
//所有地图上怪物列表
typedef std::map<int32_t, CfgMapMonsterVector> CfgMapMonsterTable;

struct CfgMapPlant 
{
	int32_t mapid;
	int32_t plantid;
	int32_t x;
	int32_t y;
};
typedef std::vector<CfgMapPlant> CfgMapPlantVector;
typedef std::map<int32_t, CfgMapPlantVector> CfgMapPlantTable;

struct CfgMapRect 
{
	int32_t id;
	int32_t from_map;
	int32_t from_x;
	int32_t from_y;
	int32_t to_map;
	int32_t to_x;
	int32_t to_y;
};
typedef std::vector<CfgMapRect> CfgMapRectVector;
typedef std::map<int32_t, CfgMapRectVector> CfgMapRectTable;

//地图范围
struct CfgMapRegion 
{
	int32_t id;
	int32_t mapid;
	int32_t min_x;
	int32_t min_y;
	int32_t max_x;
	int32_t max_y;
	int32_t type;
};
typedef std::vector<CfgMapRegion> CfgMapRegionVector;
typedef std::map<int32_t, CfgMapRegionVector> Int32CfgMapRegionVectorMap;
typedef std::map<int32_t, CfgMapRegion> CfgMapRegionTable;

#define MAX_MONSTER_SKILL	10
struct CfgMonster // 怪物
{
	int32_t mid;
	std::string name;
	int32_t level;
	int32_t quality;

	int32_t hp;						// 最大血量
	int32_t phy_atk_min;			// 最小物理攻击
	int32_t phy_atk_max;			// 最大物理攻击
	int32_t mag_atk_min;			// 最小魔法攻击
	int32_t mag_atk_max;			// 最大魔法攻击
	int32_t phy_def;				// 物理防御
	int32_t mag_def;				// 魔法防御
	int32_t hitrate;				// 命中
	int32_t dodge;					// 闪避
	int32_t critrate;				// 暴击
	int32_t dmg_add;				// 额外伤害
	int32_t dmg_rdc;				// 忽视伤害
	int32_t dmg_add_pec;			// 伤害加成（%）
	int32_t dmg_rdc_pec;			// 伤害减免（%）
	int32_t movespeed;				// 移动速度
	int32_t	battle;					// 幸运值

	int32_t exp;
	int32_t type;//类型0.怪物 1.陷阱
	int32_t kingdom_contribute;
	int32_t revive_time;
	int32_t skill_id;
	MonsterSkill unique_skill[MAX_MONSTER_SKILL];
	MonsterSkill random_skill[MAX_MONSTER_SKILL];
	int32_t angry_time;
	int32_t standby;//待命
	int32_t hpPercent;//归位时血量增加千分比
	int32_t ai_style;
	int32_t ai_target;
	int32_t has_kingdom;
	int32_t view_range;
	int32_t move_range;
	int32_t broadcast;
	int32_t drop_free;
	int32_t corpse_time;
	int32_t	group_id;
	int8_t	boss_sign;
};
typedef std::map<int32_t, CfgMonster> CfgMonsterTable;

struct CfgMonsterDropGroup 
{
	int32_t group_id;
	int32_t item_id;
	int8_t	item_class;
	int8_t	bind_type;
	int32_t probability;
	int32_t cost_type;
	int32_t cost_value;
};
typedef std::vector<CfgMonsterDropGroup> CfgMonsterDropGroupVector;
typedef std::map<int32_t, CfgMonsterDropGroupVector> CfgMonsterDropGroupTable;

struct CfgMonsterGroupDrop 
{
	int32_t mid;
	int32_t group_id;
	int32_t probability;
	int32_t begin_time;
	int32_t end_time;
	int32_t repeat;
};
typedef std::vector<CfgMonsterGroupDrop> CfgMonsterGroupDropVector;
typedef std::map<int32_t, CfgMonsterGroupDropVector> CfgMonsterGroupDropTable;

struct CfgMonsterTaskDrop 
{
	int32_t mid;
	int32_t tid;
	int32_t item;
	int32_t probability;
};
typedef std::vector<CfgMonsterTaskDrop> CfgMonsterTaskDropVector;
typedef std::map<int32_t, CfgMonsterTaskDropVector> CfgMonsterTaskDropTable;

struct CfgBornAttr
{
	Job_t job;
	AttrAddonVector bornAttr;
};
typedef std::vector<CfgBornAttr> CfgBornAttrVector;
typedef std::map<Job_t, CfgBornAttr> CfgBornAttrTable;

struct CfgChangeJobAttr
{
	int32_t index;
	AttrAddonVector changeAttr;
};
typedef std::vector<CfgChangeJobAttr> CfgChangeJobAttrVector;
typedef std::map<int32_t, CfgChangeJobAttr> CfgChangeJobAttrTable;

struct CfgNpc 
{
	bool findMapId(int32_t mapid) const
	{
		return std::find(mapids.begin(), mapids.end(), mapid) != mapids.end();
	}

	int32_t id;
	int32_t level;
	Int32Vector mapids;
	int32_t x;
	int32_t y;
	int32_t func;
	int32_t func_extra;
};
typedef std::map<int32_t, CfgNpc> CfgNpcTable;

struct CfgNpcAirport
{
	int32_t id;
	int32_t npcid;
	int32_t player_kingdom;
	int32_t kingdom_id;
	int32_t map_id;
	int32_t map_x;
	int32_t map_y;
	int32_t cost;
};
typedef std::map<int32_t, CfgNpcAirport> CfgNpcAirportTable;

struct CfgGamble//稀世宝阁
{
	  int32_t id;
	  int32_t ratio;
	  int32_t item;
	  int32_t item_type;
	  int32_t count;
	  int32_t isBroadcast;
};
typedef std::vector<CfgGamble>CfgGambleVector;

struct CfgGambleEquip
{
	int32_t id;
	int32_t type;
	MemJobItemTable equip;
};
typedef std::map<int32_t,CfgGambleEquip>CfgGambleEquipTable;

struct CfgFriendExp
{
	int32_t Level;
	int32_t Exp;
};
typedef std::map<int32_t,CfgFriendExp> CfgFriendExpTable;

struct CfgChrShop 
{
	int32_t		Index;
	int32_t		ItemId;
	int8_t		ItemClass;
	int32_t		IsBind;
	int32_t		LimitCount;
	int32_t		Price;
};
typedef std::map<int32_t, CfgChrShop> CfgChrShopTable;


struct CfgNpcKingdomShop
{
	int32_t id;
	int32_t npcid;
	int32_t item_id;
	int32_t item_type;
	int32_t cost;
	int32_t level_required;
	int32_t weight;
};
typedef std::map<int32_t, CfgNpcKingdomShop> CfgNpcKingdomShopTable;

struct CfgNpcTrade //贸易
{
	int32_t id;
	int32_t npcid;
	int32_t item_id;
	int32_t item_type;
	int32_t item_cost;
	int32_t cost_value;
	int32_t weight;
};
typedef std::map<int32_t, CfgNpcTrade> CfgNpcTradeTable;

struct CfgOnlineReward
{
	int32_t id;
	int32_t type;
	int32_t time;
	int32_t gold;
	MemChrBagVector items;
};
typedef std::vector<CfgOnlineReward> CfgOnlineRewardVector;
typedef std::map<int32_t,CfgOnlineReward>CfgOnlineRewardTable;

struct CfgPlantItem 
{
	int32_t item;
	int32_t probability;
};
typedef std::vector<CfgPlantItem> CfgPlantItemVector;

struct CfgPlant
{
	int32_t id;
	int32_t type;
	int32_t level;
	CfgPlantItemVector item;
	int32_t item_count;
	int32_t item_cost;
	int32_t start_hour;
	int32_t end_hour;
	int32_t gather_time;
	int32_t revive_time;
};
typedef std::map<int32_t, CfgPlant> CfgPlantTable;

struct CfgLevelAttr
{
	int32_t job;
	int32_t level;
	AttrAddonVector addonattr;
};
typedef std::map<int32_t, CfgLevelAttr> CfgLevelAttrTable;

struct CfgPractice
{
	int32_t dungeon_id;
	int32_t first_award_exp;
	int32_t next_award_exp;
	Int32Vector award_item;
};
typedef std::map<int32_t, CfgPractice> CfgPracticeTable;


struct CfgSkill 
{
	int32_t getMoney(int32_t level)
	{
		return roundInt(money_base + money_ratio*(level*level+level)*0.1);
	}

	int32_t getMpCost(int32_t level)
	{
		 return roundInt(mp_cost_base + static_cast<int32_t>(mp_cost_ratio*(level+level*(level-20)/40)));
	}

	int32_t getJonggongCost(int32_t level)
	{
		return jungong_base +jungong_ratio*level*level;
	}

	int32_t getAttackModify(int32_t level)
	{
		return roundInt(attack_modify_base + attack_modify_ratio*level*0.1);
	}

	int32_t getAttackAddon(int32_t level)
	{
		 return roundInt(attack_addon_base + static_cast<int32_t>(attack_addon_ratio*(level+level*(level-10)/20)));
	}

	int32_t getBuffRate(int32_t level)
	{
		return roundInt(buff_rate_base + buff_rate_ratio*level*0.1);
	}

	//主要限制不可升级的技能
	int32_t getLevelLimit(int32_t level)
	{
		return level + level_base;
	}

	SkillId_t id;
	Job_t job;
	int32_t type;					// SKILL_TYPE
	int32_t	kind;					// SKILL_KIND
	int32_t distance;
	int32_t range;					// SKILL_RANGE
	int32_t area;					// RangeArea
	int32_t	self;					// SKILL_TARGET_POS
	int32_t target_num;
	int32_t beneficial;				// 增益标记
	int32_t sp;						//飞行速度
	int32_t study_level;
	int32_t money_base;
	int32_t money_ratio;
	int32_t jungong_base;
	int32_t jungong_ratio;
	int32_t cd;
	int32_t mp_cost_base;
	int32_t mp_cost_ratio;
	int32_t angry_cost;
	int32_t special;				// SkillSpecial
	int32_t attack_type;			// SKILL_ATTACK_TYPE
	int32_t attack_modify_base;		// 攻击修正基础值
	int32_t attack_modify_ratio;	// 攻击修正系数
	int32_t attack_addon_base;		// 攻击加成基础值
	int32_t attack_addon_ratio;		// 攻击加成系数
	int32_t buff_rate_base;			// buff概率基础值
	int32_t buff_rate_ratio;		// buff概率系数
	int32_t buff;
	int32_t level_base;
	int32_t maxLevel;
	ChangeJobIndexVector change_skill_id;
};
typedef std::map<int32_t, CfgSkill> CfgSkillTable;

#define MAX_SKILL_LEVEL		5
struct CfgSkillLevelUp 
{
	SkillId_t	nSkillId;
	int32_t		nBookId[MAX_SKILL_LEVEL];
};
typedef std::map<SkillId_t, CfgSkillLevelUp> CfgSkillLevelUpMap;

class CfgSkillLevelUpTable
{
public:
	CfgSkillLevelUpTable(){}
	~CfgSkillLevelUpTable(){}

	bool Add( const CfgSkillLevelUp& skill )
	{
		m_mSkillLevelUpMap[skill.nSkillId] = skill;
		return true;
	}

	int32_t GetBook( int32_t nSkillId, int32_t nLevel ) const
	{
		if ( nLevel < 0 || nLevel >= MAX_SKILL_LEVEL )
		{
			return 0;
		}
		CfgSkillLevelUpMap::const_iterator iter = m_mSkillLevelUpMap.find( nSkillId );
		if ( iter == m_mSkillLevelUpMap.end() )
		{
			return 0;
		}
		const CfgSkillLevelUp& cfgSkill = iter->second;
		return cfgSkill.nBookId[nLevel];
	}
private:
	CfgSkillLevelUpMap	m_mSkillLevelUpMap;
};

struct TaskDest 
{
	char	type;
	int32_t	pram;
};

struct CfgTask 
{
	int32_t id;
	char  name[MAX_NAME_CCH_LENGTH+1];
	int32_t type;
	int32_t group;
	int32_t can_giveup;
	int32_t pretask;
	int32_t	posttask;
	int32_t main_order;
	Job_t job;
	int32_t level;
	int32_t max_level;
	int32_t kingdom;
	int32_t start_npc;
	int32_t end_npc;
	MemChrBagVector items_receive;
	int32_t award_exp;
	int32_t award_money;
	int32_t gold;
	int32_t jiangxing;
	int32_t wuhuen;
	int32_t jungong;
	int32_t dungeon;
	MemChrBagVector award_item;
	MemChrJobBagVector award_optional;
	int32_t condition;
	int32_t done_count;
	TaskRequest request;
	TaskDest destCondition;
	TaskDest destSubmit;
};
typedef std::map<int32_t, CfgTask> CfgTaskTable;
typedef std::vector<CfgTask> CfgTaskVector;

struct CfgTaskGroup
{
	int32_t min_level;
	int32_t max_level;
	int32_t cycle_group;
	int32_t family_group;
};
typedef std::vector<CfgTaskGroup> CfgTaskGroupTable;

struct CfgTrailer 
{
	int32_t id;
	std::string name;
	int32_t level;
	int32_t pdef;
	int32_t mdef;
	int32_t maxhp;
	int32_t sp;
	int32_t time;

	void reset()
	{
		id =0;
		level=0;
		pdef =0;
		mdef =0;
		maxhp=0;
		maxhp=0;
		sp=0;
		time=0;
		name="";
	}
	CfgTrailer()
	{
		reset();
	}
};
typedef std::map<int32_t, CfgTrailer> CfgTrailerTable;

struct CfgTrap 
{
	int32_t id;
	int32_t cd;
	int32_t effect_delay;
	int32_t type;
	std::string effect;
	int32_t item_cost;
};
typedef std::map<int32_t, CfgTrap> CfgTrapTable;


struct cfgParam
{
	int32_t param1;
	int32_t param2;
};

typedef std::vector<cfgParam> cfgParams;
typedef std::map<int16_t, cfgParams> cfgParamsTable;


//普通活动的扩展
struct cfgExActivity
{
	int16_t actid;
	int32_t starttime;
	int32_t endtime;
	cfgParams gifts;
	char strgifts[200];
};
typedef std::map<int16_t,cfgExActivity> cfgExActivitys;

struct CfgNewServerActivity
{
	int32_t id;
	int32_t time;
	int32_t type;
	int32_t value;
	int32_t param;
	int32_t order;
	MemChrBagVector item;
};
typedef std::vector<CfgNewServerActivity>CfgNewServerActivityVector;
typedef std::map<int32_t,CfgNewServerActivityVector>CfgNewServerActivityTable;

struct CfgNewServerLater
{
	int32_t id;
	int32_t type;
	int32_t index;
	int32_t value;
	MemChrBagVector items;
};
typedef std::map<int32_t,CfgNewServerLater>CfgNewServerLaterTable;

struct CfgNewServerGold
{
	int32_t id;
	int32_t type;
	int32_t cost;
	int32_t give;
};
typedef std::map<int32_t,CfgNewServerGold>CfgNewServerGoldTable;

//struct CfgVip
//{
//	int32_t id;
//	int32_t type;
//	int32_t gold_cost;
//	int32_t remain;//持续时间
//	int32_t exp_addon_ratio;//打怪经验加成
//	int32_t fly_free;
//	int32_t daily_gift;
//	int32_t no_cd_enhance;//无冷却强化0:需要cd，1:无需cd
//	int32_t yumajian;
//	int32_t yanwuchang_middle;
//	int32_t yanwuchang_advance;
//	int32_t entrust_cd_reduce;//副本委托时间减少
//	int32_t bagua_time_addon;//八卦阵次数增加
//	int32_t relief_addon;//流民增加次数
//	int32_t order;
//	AttrAddonVector attr_addon;//属性加成
//	int32_t buy_num;
//};
//typedef std::map<int32_t, CfgVip> CfgVipTable;

struct CfgChargeRewards
{
	int32_t id;
	int32_t type;
	int32_t charge;
	int32_t money;
	int32_t sys_gold;
	MemChrBagVector real_rewards;
	MemChrJobBagVector real_job_rewards;
};
typedef std::vector<CfgChargeRewards> CfgChargeRewardsVector;

typedef std::map<int32_t, GmtBanChat> GmtBanChatTable;

struct MemFamily 
{
	int32_t id;
	int32_t leaderID;
	int32_t level;
};
typedef std::vector<MemFamily> MemFamilyVector;

struct SysServerRatio 
{
	int32_t sid;
	int32_t begin_date;
	int32_t end_date;
	int32_t exp_ratio;
};
typedef std::map<int32_t, SysServerRatio> SysServerRatioTable;

//坐骑装备数据结构
struct CfgMountEquip
{
	int32_t		id;
	std::string name;
	std::string desc;
	std::string url;
	int32_t		limit_level;
};
typedef std::map<int32_t, CfgMountEquip> CfgMountEquipTable;

////国家数据结构
//struct CfgKingdom
//{
//	int32_t id;								//国家ID
//	std::string name;						//国家名称
//	int32_t task_id;						//选择国家后任务ID
//	int32_t random_gift;					//随机礼包
//};
////国家列表
//typedef std::map<int32_t, CfgKingdom> CfgKingdomTable;

struct CfgYellowStone
{
	int32_t id;
	int32_t yellow_type; //1:黄钻每日礼包(等级为黄钻等级) 2:年费黄钻额外每日礼包 3:黄钻成长礼包(等级为人物等级) 4:黄钻新手礼包
	int32_t level; //等级
	MemChrBagVector awards;
};
typedef std::map<int32_t, CfgYellowStone> CfgYellowStoneTables;


// 装备表
#define MAX_EQUIP_BASE_ATTR_COUNT	3
struct CfgEquip
{
	int32_t		m_nId;										// id
	int8_t		m_nType;									// 类型 EQUIP_TYPE
	int32_t		m_nLevel;									// 等级
	int8_t		m_nJob;										// 职业
	int8_t		m_nQuality;									// 品质
	int32_t		m_nSuitId;									// 套装ID
	int32_t		m_nPrice;									// 售价
	int32_t		m_nGrade;									// 档次
	int32_t		m_nRansomWorth;								// 赎回价值
	AttrAddon	m_vAttr[MAX_EQUIP_BASE_ATTR_COUNT];			// 基础属性
	AttrAddon	m_StarAttr[MAX_EQUIP_BASE_ATTR_COUNT];		// 强化基础属性
};
typedef std::map<int32_t, CfgEquip> CfgEquipMap;

class CfgEquipUpGrade
{
public:
	CfgEquipUpGrade(){ CleanUp(); }
	void CleanUp()
	{
		m_nId				= 0;
		m_nGiveId			= 0;
		m_nFailLine			= 0;
		m_nSuccessLine		= 0;
		m_nFullLucky		= 0;
		m_nGetLucky			= 0;
		m_nRate				= 0;
		m_nTotalRate		= 0;
		bzero( &m_CostUsualItem, sizeof( m_CostUsualItem ) );
		bzero( &m_CostSpecialItem, sizeof( m_CostSpecialItem ) );
	}
	int32_t			m_nId;					// 原装备id					
	int32_t			m_nGiveId;				// 升级后的装备Id		
	int32_t			m_nFailLine;			// 开始有暴击的幸运值							
	int32_t			m_nSuccessLine;			// 必定成功的幸运值
	int32_t			m_nFullLucky;			// 幸运值最大值
	int32_t			m_nGetLucky;			// 失败获得的幸运值
	int32_t			m_nRate;				// 暴击概率
	int32_t			m_nTotalRate;			// 最大随机值
	ItemData		m_CostUsualItem;		// 普通物品			
	ItemData		m_CostSpecialItem;		// 特殊物品					
};
typedef std::map<int32_t, CfgEquipUpGrade> CfgEquipUpGradeMap;

class CfgEquipUpQuality
{
public:
	CfgEquipUpQuality(){ CleanUp(); }
	void CleanUp()
	{
		m_nId				= 0;
		m_nGiveId			= 0;
		m_nFailLine			= 0;
		m_nSuccessLine		= 0;
		m_nFullLucky		= 0;
		m_nGetLucky			= 0;
		m_nRate				= 0;
		m_nTotalRate		= 0;
		m_OpenHoleRate		= 0;
		m_OpenSecondHoleRate	= 0;
		bzero( &m_CostUsualItem, sizeof( m_CostUsualItem ) );
		bzero( &m_CostSpecialItem, sizeof( m_CostSpecialItem ) );
	}
	int32_t			m_nId;					// 原装备id					
	int32_t			m_nGiveId;				// 升级后的装备Id		
	int32_t			m_nFailLine;			// 开始有暴击的幸运值							
	int32_t			m_nSuccessLine;			// 必定成功的幸运值
	int32_t			m_nFullLucky;			// 幸运值最大值
	int32_t			m_nGetLucky;			// 失败获得的幸运值
	int32_t			m_nRate;				// 暴击概率
	int32_t			m_nTotalRate;			// 最大随机值
	ItemData		m_CostUsualItem;		// 普通物品			
	ItemData		m_CostSpecialItem;		// 特殊物品	
	int32_t			m_OpenHoleRate;			// 开启第一宝石孔的概率
	int32_t			m_OpenSecondHoleRate;	// 开启第二宝石孔的概率
};
typedef std::map<int32_t, CfgEquipUpQuality> CfgEquipUpQualityMap;

class CfgEquipUpStar
{
public:
	CfgEquipUpStar(){ CleanUp(); }
	void CleanUp()
	{
		m_nStar			= 0;
		m_nFailLine		= 0;
		m_nSuccessLine	= 0;
		m_nFullLucky	= 0;
		m_nFailAddLucky	= 0;
		m_nRate			= 0;
		m_nTotalRate	= 0;
		bzero( &m_CostUsualItem, sizeof( m_CostUsualItem ) );
		bzero( &m_CostSpecialItem,sizeof( m_CostSpecialItem ));
	}
	int32_t			m_nStar;								// 星级
	int32_t			m_nFailLine;							// 必定失败线
	int32_t			m_nSuccessLine;							// 必定成功线
	int32_t			m_nFullLucky;							// 总幸运值
	int32_t			m_nFailAddLucky;						// 失败加的幸运值
	int32_t			m_nRate;								// 成功概率
	int32_t			m_nTotalRate;							// 成功总概率
	ItemData		m_CostUsualItem;						// 消耗普通道具列表
	ItemData		m_CostSpecialItem;						// 消耗特殊道具
};
typedef std::map<int32_t, CfgEquipUpStar> CfgEquipUpStarMap;

#define MAX_EQUIP_ADD_ATTR_COUNT	10
class CfgEquipAddAttr
{
public:
	CfgEquipAddAttr(){ CleanUp(); }
	void CleanUp()
	{
		m_nLevel		= 0;
		m_nMaxRate		= 0;
		m_lstAddAttr.clear();
	}
	int32_t GetAttrValue( int32_t nAttr ) const
	{
		CfgAddAttrList::const_iterator iter = m_lstAddAttr.begin();
		CfgAddAttrList::const_iterator eiter = m_lstAddAttr.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( iter->m_nAttr == nAttr )
			{
				return iter->m_nValue;
			}
		}
		return 0;
	}
	int32_t GetRandAttr() const
	{
		if ( m_nMaxRate <= 0 )
		{
			return 0;
		}
		int32_t nRand = RANDOM.generate( 0, m_nMaxRate );
		CfgAddAttrList::const_iterator iter = m_lstAddAttr.begin();
		CfgAddAttrList::const_iterator eiter = m_lstAddAttr.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nRand < iter->m_nRate )
			{
				return iter->m_nAttr;
			}
		}
		return 0;
	}
	int32_t			m_nLevel;								// 等级
	int32_t			m_nMaxRate;								// 总概率
	CfgAddAttrList	m_lstAddAttr;							// 附加属性列表
};
typedef std::map<int32_t, CfgEquipAddAttr> CfgEquipAddAttrMap;

#define EQUIP_GOAL_STAR		1		// 强化星级
#define EQUIP_GOAL_GEM		2		// 宝石等级
class CfgEquipGoal
{
public:
	CfgEquipGoal(){ CleanUp(); }
	void CleanUp()
	{
		m_nIndex	= 0;
		m_nType		= 0;
		m_nParam	= 0;
		bzero( m_vAddAttr, sizeof( m_vAddAttr ) );
	}
	
	int32_t		m_nIndex;								// 序列
	int8_t		m_nType;								// 类型
	int32_t		m_nParam;								// 参数
	AttrAddon	m_vAddAttr[MAX_EQUIP_ADD_ATTR_COUNT];	// 附加属性列表
};
typedef std::map<int32_t, CfgEquipGoal> CfgEquipGoalMap;

class CfgEquipSuit
{
public:
	CfgEquipSuit(){ CleanUp(); }
	void CleanUp()
	{
		m_nId	= 0;
		m_lstEquips.clear();
		m_lstSuitAttr.clear();
	}

	AttrAddonList GetAddAttr( int32_t nCount ) const
	{
		AttrAddonList attrList;
		CfgSuitAttrList::const_iterator iter = m_lstSuitAttr.begin();
		CfgSuitAttrList::const_iterator eiter = m_lstSuitAttr.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( iter->m_nCount > nCount )
			{
				continue;
			}
			AttrAddon attr = {};
			attr.index = iter->m_nAttr;
			attr.addon = iter->m_nValue;
			attrList.push_back( attr );
		}
		return attrList;
	}

	int32_t			m_nId;									// 序列
	Int32List		m_lstEquips;							// 套装包含装备列表 
	CfgSuitAttrList	m_lstSuitAttr;							// 附加属性列表
};
typedef std::map<int32_t, CfgEquipSuit> CfgEquipSuitMap;

class CfgEquipTable
{
public:
	void AddEquip( const CfgEquip& equip )
	{
		m_mEquip[equip.m_nId] = equip;
	}

	const CfgEquip*	GetEquip( int32_t id ) const
	{
		CfgEquipMap::const_iterator iter = m_mEquip.find( id );
		if ( iter != m_mEquip.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}

	void AddEquipUpGrade( const CfgEquipUpGrade& equip )
	{
		m_mEquipUpGrade[equip.m_nId] = equip;
	}

	const CfgEquipUpGrade* GetEquipUpGrade( int32_t id ) const
	{
		CfgEquipUpGradeMap::const_iterator iter = m_mEquipUpGrade.find( id );
		if ( iter != m_mEquipUpGrade.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}

	void AddEquipUpQuality( const CfgEquipUpQuality& equip )
	{
		m_mEquipUpQuality[equip.m_nId] = equip;
	}

	const CfgEquipUpQuality* GetEquipUpQuality( int32_t id ) const
	{
		CfgEquipUpQualityMap::const_iterator iter = m_mEquipUpQuality.find( id );
		if ( iter != m_mEquipUpQuality.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}

	void AddEquipUpStar( const CfgEquipUpStar& equip )
	{
		m_mEquipUpStar[equip.m_nStar] = equip;
	}

	const CfgEquipUpStar* GetEquipUpStar( int32_t nStar ) const
	{
		CfgEquipUpStarMap::const_iterator iter = m_mEquipUpStar.find( nStar );
		if ( iter != m_mEquipUpStar.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}

	void AddEquipAddAttr( const CfgEquipAddAttr& equip )
	{
		m_mEquipAddAttr[equip.m_nLevel] = equip;
	}

	const CfgEquipAddAttr* GetEquipAddAttr( int32_t nLevel ) const
	{
		CfgEquipAddAttrMap::const_iterator iter = m_mEquipAddAttr.find( nLevel );
		if ( iter != m_mEquipAddAttr.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}

	void AddEquipGoal( const CfgEquipGoal& equip )
	{
		m_mEquipGoal[equip.m_nIndex] = equip;
	}

	const CfgEquipGoal* GetEquipGoal( int8_t nType, int32_t nParam ) const
	{
		int32_t	nMaxParam = 0;
		CfgEquipGoalMap::const_iterator findIter = m_mEquipGoal.end();
		CfgEquipGoalMap::const_iterator iter = m_mEquipGoal.begin();
		CfgEquipGoalMap::const_iterator eiter = m_mEquipGoal.end();
		for ( ; iter != eiter; ++iter )
		{
			const CfgEquipGoal& stu = iter->second;
			if ( stu.m_nType == nType && stu.m_nParam <= nParam )
			{
				if ( stu.m_nParam > nMaxParam )
				{
					findIter = iter;
					nMaxParam = stu.m_nParam;
				}
			}
		}
		if ( findIter != eiter )
		{
			return &( findIter->second );
		}
		return NULL;
	}

	void AddEquipSuit( const CfgEquipSuit& equip )
	{
		m_mEquipSuit[equip.m_nId] = equip;
	}

	const CfgEquipSuit* GetEquipSuit( int32_t nId ) const
	{
		CfgEquipSuitMap::const_iterator iter = m_mEquipSuit.find( nId );
		if ( iter != m_mEquipSuit.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}
private:
	CfgEquipMap				m_mEquip;
	CfgEquipUpGradeMap		m_mEquipUpGrade;
	CfgEquipUpQualityMap	m_mEquipUpQuality;
	CfgEquipUpStarMap		m_mEquipUpStar;
	CfgEquipAddAttrMap		m_mEquipAddAttr;
	CfgEquipGoalMap			m_mEquipGoal;
	CfgEquipSuitMap			m_mEquipSuit;
};

// 宝石表
#define MAX_GEM_BASE_ATTR_COUNT		5
// struct CfgItemGem
// {
// 	int32_t		m_nId;
// 	int8_t		m_nType;
// 	int8_t		m_nGemLevel;
// 	int32_t		m_nLevel;
// 	int32_t		m_nPrice;
// 	int8_t		m_nQuality;
// 	int32_t		m_nLayNum;
// };

//新宝石结构
struct CfgItemGem
{
	int32_t		m_nId;
	int8_t		m_nType;
	int8_t		m_nGemLevel;
	int32_t		m_nLevel;
	int32_t		m_nPrice;
	int8_t		m_nQuality;
	int32_t		m_nLayNum;
	int32_t		m_EffectType;  //宝石效果类型
	int32_t		m_AddRate;	   //宝石效果比例
	int32_t		m_nGrade;
	int32_t		m_nRansomWorth;//赎回价值
	AttrAddon	m_vAttr[MAX_GEM_BASE_ATTR_COUNT];
};
typedef std::map<int32_t, CfgItemGem> CfgGemMap;

class CfgItemGemTable
{
public:
	void	Add( const CfgItemGem& gem )
	{
		m_mGemMap[gem.m_nId] = gem;
	}

	const CfgItemGem*	GetItemGem( int32_t id ) const
	{
		CfgGemMap::const_iterator iter = m_mGemMap.find( id );
		if ( iter != m_mGemMap.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}
private:
	CfgGemMap	m_mGemMap;
};

// 合成表
class CfgItemCombi
{
public:
	CfgItemCombi()
	{
		m_nId			= 0;
		CostList.clear();
		m_nGiveId		= 0;		
		m_nGiveClass	= 0;	
		m_nGiveCount	= 0;	
		m_nMoney		= 0;		
		m_nRate			= 0;		
		m_nTotalRate	= 0;	
	}
	int32_t	m_nId;
	ItemDataList CostList;//合成要扣除的列表
	int32_t m_nGiveId;				// 合成给予道具ID
	int8_t	m_nGiveClass;			// 合成给予道具类型
	int32_t	m_nGiveCount;			// 合成给予道具数量
	int32_t	m_nMoney;				// 合成消耗铜钱
	int32_t m_nRate;				// 合成成功概率
	int32_t m_nTotalRate;			// 合成成功总概率
};
typedef std::map<int32_t, CfgItemCombi> CfgItemCombiMap;

class CfgItemCombiTable
{
public:
	void	Add( const CfgItemCombi& itemCombi )
	{
		m_mItemCombi[itemCombi.m_nId]	= itemCombi;
	}

	const CfgItemCombi*	GetItemCombi( int32_t key ) const
	{
		CfgItemCombiMap::const_iterator iter = m_mItemCombi.find( key );
		if ( iter != m_mItemCombi.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}
private:
	CfgItemCombiMap	m_mItemCombi;
};

struct CfgBagSlotOpenTime 
{
	int32_t	m_nSlot;			// 背包格
	int32_t	m_nSeconds;			// 开启背包需要时间
	int32_t m_nBagAddExp;		// 开启背包获得经验
	int32_t m_nBagAddHp;		// 开启背包获得HP
	int32_t m_nDepotNeedSeconds;// 开启仓库需要的时间
	int32_t m_nDepotAddExp;		// 开启仓库获得经验
	int32_t m_nDepotAddHp;		// 开启仓库获得HP
};
typedef std::map<int32_t, CfgBagSlotOpenTime> CfgBagSlotOpenTimeMap;
class CfgBagSlotOpenTimeTable
{
public:
	void	Add( const CfgBagSlotOpenTime& stu )
	{
		m_mBagSlotOpenTime[stu.m_nSlot] = stu;
	}

	const CfgBagSlotOpenTime*	Get( int32_t nOpenSlot ) const
	{
		CfgBagSlotOpenTimeMap::const_iterator iter = m_mBagSlotOpenTime.find( nOpenSlot );
		if ( iter != m_mBagSlotOpenTime.end() )
		{
			return &( iter->second );
		}
		return NULL;
	}

	int32_t GetNeedSeconds( int32_t nOpenSlot, int8_t Type ) const
	{
		CfgBagSlotOpenTimeMap::const_iterator iter = m_mBagSlotOpenTime.find( nOpenSlot );
		if ( iter != m_mBagSlotOpenTime.end() )
		{
			if ( Type = CBT_BAG )
			{
				return iter->second.m_nSeconds;
			}
			else
			{
				return iter->second.m_nDepotNeedSeconds;
			}
		}
		return 0;
	}

	int32_t GetNeedSeconds( int32_t nFromSlot, int32_t nToSlot, int8_t Type ) const
	{
		int32_t nSeconds = 0;
		for ( int32_t i = nFromSlot; i <= nToSlot; ++i )
		{
			CfgBagSlotOpenTimeMap::const_iterator iter = m_mBagSlotOpenTime.find( i );
			if ( iter != m_mBagSlotOpenTime.end() )
			{
				if ( Type == CBT_BAG )
				{
					nSeconds += iter->second.m_nSeconds;
				}
				else
				{
					nSeconds += iter->second.m_nDepotNeedSeconds;
				}
			}
		}
		return nSeconds;
	}
private:
	CfgBagSlotOpenTimeMap	m_mBagSlotOpenTime;
};

#define MAX_PET_ATTR_RATE	100
// 属性初始化对应的百分比
class CfgPetAttrInitRateTable
{
	friend class CfgData;
public:
	CfgPetAttrInitRateTable()
	{
		bzero( m_vStartRate, sizeof( m_vStartRate ) );
	}

	int32_t	GetStartRate() const
	{
		if ( m_nMaxStartRate < 1 )
		{
			return 0;
		}

		int32_t nRate	= RANDOM.generate( 1, m_nMaxStartRate );
		for ( int32_t i = 0; i < MAX_PET_ATTR_RATE; ++i )
		{
			if ( nRate <= m_vStartRate[i] )
			{
				return i+1;
			}
		}
		return 0;
	}

	int32_t	GetLuckyRate() const
	{
		if ( m_nMaxLuckyRate < 1 )
		{
			return 0;
		}

		int32_t nRate	= RANDOM.generate( 1, m_nMaxLuckyRate );
		for ( int32_t i = 0; i < MAX_PET_ATTR_RATE; ++i )
		{
			if ( nRate <= m_vLuckyRate[i] )
			{
				return i+1;
			}
		}
		return 0;
	}

	int32_t	GetGrowRate() const
	{
		if ( m_nMaxGrowRate < 1 )
		{
			return 0;
		}

		int32_t nRate	= RANDOM.generate( 1, m_nMaxGrowRate );
		for ( int32_t i = 0; i < MAX_PET_ATTR_RATE; ++i )
		{
			if ( nRate <= m_vGrowRate[i] )
			{
				return i+1;
			}
		}
		return 0;
	}

private:
	bool add( int32_t nPercent, int32_t nStartRate, int32_t nLuckyRate, int32_t nGrowRate )
	{
		if ( nPercent <= 0 || nPercent > MAX_PET_ATTR_RATE )
		{
			return false;
		}
		m_nMaxStartRate += nStartRate;
		m_vStartRate[nPercent-1] = m_nMaxStartRate;

		m_nMaxLuckyRate += nLuckyRate;
		m_vLuckyRate[nPercent-1] = m_nMaxLuckyRate;
		
		m_nMaxGrowRate += nGrowRate;
		m_vGrowRate[nPercent-1] = m_nMaxGrowRate;
		return true;
	}

private:
	int32_t m_nMaxStartRate;
	int32_t	m_vStartRate[MAX_PET_ATTR_RATE];
	int32_t m_nMaxLuckyRate;
	int32_t	m_vLuckyRate[MAX_PET_ATTR_RATE];
	int32_t m_nMaxGrowRate;
	int32_t	m_vGrowRate[MAX_PET_ATTR_RATE];
};

#define MAX_PET_SKILL_RATE	100000	// 技能随机概率基数
class CfgPetData 
{
public:
	CfgPetData(){ CleanUp(); }
	~CfgPetData(){}

	void CleanUp()
	{
		m_nPetId			= 0;
		m_strName			= "";
		m_nLucky			= 0;
		m_nRein				= 0;
		m_nOrderJob			= 0;
		m_nPetJob			= 0;
		m_nRare				= 0;
		m_nPhase			= PP_INVALID;
		m_nHatchTime		= 0;
		m_nMutiHatchTime	= 0;
		m_nGrowRatio		= 0;
		m_nXxoo				= 0;
		m_nSkillId			= 0;
		m_nSecondSkillId	= 0;
		bzero( m_vMaxAttr, sizeof( m_vMaxAttr ) );
		bzero( m_vMaxPoints, sizeof( m_vMaxPoints ) );
		bzero( m_vSkill, sizeof( m_vSkill ) );
		bzero( m_vSkillRate, sizeof( m_vSkillRate ) );
	}

	SkillId_t RandSkill() const
	{
		int32_t nRand = RANDOM.generate( 0, MAX_PET_SKILL_RATE );
		for ( int32_t i = 0; i < PET_SKILL_COUNT; ++i )
		{
			if ( nRand < m_vSkillRate[i] )
			{
				return m_vSkill[i];
			}
		}
		return 0;
	}

public:
	int32_t			m_nPetId;						// 基础ID
	std::string		m_strName;						// 宠物名称
	Job_t			m_nOrderJob;					// 指挥需求
	Job_t			m_nPetJob;						// 幻兽类型
	int32_t			m_nRare;						// 罕见度
	int32_t			m_nRein;						// 转生次数限制
	PET_PHASE		m_nPhase;						// 相性=0则随机生成
	int32_t			m_nLucky;						// 幸运值
	int32_t			m_vMaxAttr[PET_ATTR_COUNT];		// 基础属性
	int32_t			m_vMaxPoints[PET_ATTR_COUNT];	// 最大评分
	SkillId_t		m_nSkillId;						// 宠物天赋技能
	SkillId_t		m_nSecondSkillId;				// 第二天赋技能
	SkillId_t		m_vSkill[PET_SKILL_COUNT];		// 宠物技能
	SkillId_t		m_vSkillRate[PET_SKILL_COUNT];	// 宠物技能概率
	int32_t			m_nHatchTime;					// 孵化时间
	int32_t			m_nMutiHatchTime;				// 批量孵化时间
	int32_t			m_nRideSkin;					// 骑乘皮肤
	int32_t			m_nGrowRatio;					// 成长系数
	int8_t			m_nXxoo;						// XO兽类型
};
typedef std::map<int32_t, CfgPetData>	CfgPetDataMap;
class CfgPetTable
{
public:
	CfgPetTable(){}
	~CfgPetTable(){}

	void Add( const CfgPetData& pet )
	{
		m_mPetCfgData[pet.m_nPetId] = pet;
	}

	const CfgPetData* GetPet( int32_t nPetId ) const
	{
		CfgPetDataMap::const_iterator findIter = m_mPetCfgData.find( nPetId );
		if ( findIter != m_mPetCfgData.end() )
		{
			return &( findIter->second );
		}
		return NULL;
	}

private:
	CfgPetDataMap	m_mPetCfgData;
};

struct CfgPetIllusionGrow 
{
	int32_t nMainPointMin;
	int32_t nMainPointMax;
	int32_t nVicePoint;
	int32_t nViceLevel;
};

typedef std::list<CfgPetIllusionGrow> CfgPetIllusionGrowList;
class CfgPetIllusionTable
{
public:
	CfgPetIllusionTable(){}
	~CfgPetIllusionTable(){}
	bool AddGrow( const CfgPetIllusionGrow& grow )
	{
		m_lstPetIllusionGrow.push_back( grow );
		return true;
	}

	const CfgPetIllusionGrow*	GetGrow( int32_t nMainPoint ) const
	{
		CfgPetIllusionGrowList::const_iterator iter = m_lstPetIllusionGrow.begin();
		CfgPetIllusionGrowList::const_iterator eiter = m_lstPetIllusionGrow.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nMainPoint >= iter->nMainPointMin && nMainPoint < iter->nMainPointMax )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

private:
	CfgPetIllusionGrowList	m_lstPetIllusionGrow;
};

#define MAX_KNIGHT_QUALITY_SIZE		20
enum PET_KNIGHT_EFFECT
{
	PKE_ADD_EXP			= 1,	//：经验加成
	PKE_REMINE_JUMP		= 2,	//：减少跳跃消耗的体力
	PKE_ADD_BATTLE		= 3,	//：战斗力加成
	PKE_REMINE_DAMAGE	= 4,	//：伤害减免
	PKE_ADD_DAMAGE		= 5,	//：伤害加成
	PKE_ADD_MAX_HP		= 6,	//：生命值上限提高
};

class CfgPetKnight 
{
public:
	CfgPetKnight(){ CleanUp(); }
	~CfgPetKnight(){}
	void CleanUp()
	{
		nLevel		= 0;
		nTitle		= 0;
		nEffectType	= 0;
		compIdList.clear();
		vQuality[MAX_KNIGHT_QUALITY_SIZE];
		vEffectValue[MAX_KNIGHT_QUALITY_SIZE];
	}

	bool IsInCompList( int32_t nPetId ) const
	{
		if ( compIdList.empty() )
		{
			return true;
		}
		Int32List::const_iterator iter =  compIdList.begin();
		Int32List::const_iterator eiter =  compIdList.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( *iter == nPetId )
			{
				return true;
			}
		}
		return false;
	}
	bool IsNeedCal() const
	{
		switch( nEffectType )
		{
		case PKE_ADD_BATTLE:
		case PKE_REMINE_DAMAGE:
		case PKE_ADD_DAMAGE:
		case PKE_ADD_MAX_HP:
			return true;
		default: break;
		}
		return false;
	}
	int32_t GetEffectValue( int32_t nPoints ) const
	{
		int32_t nMax = -1;
		for ( int32_t i = 0; i < MAX_KNIGHT_QUALITY_SIZE; ++i )
		{
			if ( vQuality[i] < 0 )
			{
				break;
			}
			if ( nPoints < vQuality[i] )
			{
				break;
			}

			nMax = i;
		}

		if ( nMax > 0 )
		{
			return vEffectValue[nMax];
		}
		return 0;
	}
	int32_t		nLevel;										// 需求等级
	int32_t		nTitle;										// 称号？
	Int32List	compIdList;									// 可以任命的宠物列表
	int8_t		nEffectType;								// 作用类型
	int32_t		vQuality[MAX_KNIGHT_QUALITY_SIZE];			// 品质
	int32_t		vEffectValue[MAX_KNIGHT_QUALITY_SIZE];		// 加成
};

class CfgPetKnightTable
{
	friend class CfgData;
public:
	CfgPetKnightTable(){ CleanUp(); }
	~CfgPetKnightTable(){}
	void CleanUp()
	{
		for ( int32_t i = 0; i < PET_KNIGHT_SIZE; ++i )
		{
			m_vKnight[i].CleanUp();
		}
	}

	const CfgPetKnight* GetKnight( int8_t nKnight ) const
	{
		if ( nKnight <= PK_NONE || nKnight >= PET_KNIGHT_SIZE )
		{
			return NULL;
		}
		return &m_vKnight[nKnight];
	}
private:
	CfgPetKnight	m_vKnight[PET_KNIGHT_SIZE];
};

struct PetHatchPoolOpenLevel 
{
	int32_t	nLevel;
	int32_t nVipLevel;
};

struct CfgPetLuckyItem
{
	int32_t nLucky;
	int8_t	nClass;
	int32_t	nId;
	int32_t	nCount;
	int32_t nRate;
};
typedef std::map<int32_t,CfgPetLuckyItem> CfgPetLuckyItemMap;

class CfgCharPetTable
{
friend class CfgData;
public:
	CfgCharPetTable(){CleanUp();}
	~CfgCharPetTable(){}
	void CleanUp()
	{
		bzero( m_vHatchPool, sizeof( m_vHatchPool ) );
		bzero( m_vMutiHatchPool, sizeof( m_vMutiHatchPool ) );
	}
	
	int32_t	GetHatchPoolSize( int32_t nLevel, int32_t nVipLevel ) const
	{
		for ( int32_t i = 0; i < PET_HATCH_POOL_SIZE; ++i )
		{
			if ( m_vHatchPool[i].nLevel > nLevel && m_vHatchPool[i].nVipLevel > nVipLevel )
			{
				return i;
			}
		}
		return PET_HATCH_POOL_SIZE;
	}

	int32_t GetMutiHatchPoolSize( int32_t nLevel, int32_t nVipLevel ) const
	{
		for ( int32_t i = 0; i < PET_MUTI_HATCH_POOL_SIZE; ++i )
		{
			if ( m_vMutiHatchPool[i].nLevel > nLevel && m_vMutiHatchPool[i].nVipLevel > nVipLevel )
			{
				return i;
			}
		}
		return PET_MUTI_HATCH_POOL_SIZE;
	}

	const CfgPetLuckyItem*	GetPetLuckyItem( int32_t nLucky ) const
	{
		CfgPetLuckyItemMap::const_iterator iter = m_mPetLucyItem.find( nLucky );
		if ( iter != m_mPetLucyItem.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

private:
	void addPetLuckyUseItem( const CfgPetLuckyItem& stu )
	{
		m_mPetLucyItem[stu.nLucky] = stu;
	}

private:
	PetHatchPoolOpenLevel	m_vHatchPool[PET_HATCH_POOL_SIZE];
	PetHatchPoolOpenLevel	m_vMutiHatchPool[PET_MUTI_HATCH_POOL_SIZE];
	CfgPetLuckyItemMap		m_mPetLucyItem;
};

struct CfgPetGift
{
	int32_t		nId;
	int32_t		nPetBaseId;
	int32_t		nLevel;
	int32_t		m_vMaxAttr[PET_ATTR_COUNT];		// 基础属性
};
typedef std::map<int32_t, CfgPetGift> PetGiftMap;

#define MAX_CYCLE_STARS			10

struct TaskCycle 
{
	int32_t nTaskId;
	int32_t nMinLevel;
	int32_t nMaxLevel;
};
typedef std::list<TaskCycle> TaskCycleList;
typedef std::vector<TaskCycle> TaskCycleVector;

class CfgTaskCycleTable
{
public:
	CfgTaskCycleTable(){ CleanUp(); }
	~CfgTaskCycleTable(){}

	void CleanUp()
	{
		bzero( m_vMaxRate, sizeof( m_vMaxRate ) );
		bzero( m_vRate, sizeof( m_vRate ) );
		m_lstTask.clear();
	}

	bool AddTask( int32_t nTaskId, int32_t nMinLevel, int32_t nMaxLevel )
	{
		TaskCycle task = { nTaskId, nMinLevel, nMaxLevel };
		m_lstTask.push_back( task );
		return true;
	}

	int32_t RandTask( int32_t nLevel ) const
	{
		Int32Vector vTask;
		vTask.reserve( m_lstTask.size() );
		TaskCycleList::const_iterator iter = m_lstTask.begin();
		TaskCycleList::const_iterator eiter = m_lstTask.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nLevel >= iter->nMinLevel && nLevel <= iter->nMaxLevel )
			{
				vTask.push_back( iter->nTaskId );
			}
		}

		if ( vTask.empty() )
		{
			return 0;
		}

		std::random_shuffle( vTask.begin(), vTask.end() );
		return vTask.front();
	}

	bool AddStarRate( int8_t nStar, int32_t vRate[MAX_CYCLE_STARS], int32_t nMaxRate )
	{
		if ( nStar < 0 || nStar > MAX_CYCLE_STARS )
		{
			return false;
		}

		m_vMaxRate[nStar] = nMaxRate;
		memcpy( m_vRate[nStar], vRate, sizeof( int32_t ) * MAX_CYCLE_STARS );
		return true;
	}

	int8_t RandStar( int8_t nStar ) const
	{
		if ( nStar < 0 || nStar > MAX_CYCLE_STARS )
		{
			return 0;
		}

		int32_t nRand = RANDOM.generate( 1, m_vMaxRate[nStar] );
		for ( int32_t i = 0; i < MAX_CYCLE_STARS; ++i )
		{
			if ( nRand <= m_vRate[nStar][i] )
			{
				return i+1;
			}
		}
		return 0;
	}

private:
	int32_t			m_vMaxRate[MAX_CYCLE_STARS+1];
	int32_t			m_vRate[MAX_CYCLE_STARS+1][MAX_CYCLE_STARS];
	TaskCycleList	m_lstTask;
};

class CfgFamilyPetRegistTable 
{
public:
	bool Add( int32_t nLevel, int32_t nCount )
	{
		m_mLevelPet[nLevel] = nCount;
		return true;
	}

	int32_t GetLevelCount( int32_t nLevel ) const
	{
		std::map<int32_t, int32_t>::const_iterator iter = m_mLevelPet.find( nLevel );
		if ( iter != m_mLevelPet.end() )
		{
			return iter->second;
		}
		return 0;
	}
private:
	std::map<int32_t, int32_t>	m_mLevelPet;
};

class CfgFamily 
{
public:
	CfgFamily(){ CleanUp(); }
	~CfgFamily(){}
	void CleanUp()
	{
		nLevel		= 0;
		nExp		= 0;
		nBattle		= 0;
		nMaxMembers	= 0;
		nTotemCount	= 0;
		bzero( vPosition, sizeof( vPosition ) );
	}

	int32_t		nLevel;								// 等级
	int32_t		nExp;								// 需求贡献度
	int32_t		nBattle;							// 附加战斗力
	int32_t		nMaxMembers;						// 最大人数
	int32_t		nTotemCount;						// 最大图腾个数
	int32_t		vPosition[FAMILY_POSITION_COUNT];	// 职位人数
};

class CfgFamilyTable
{
public:
	CfgFamilyTable(){ CleanUp(); }
	~CfgFamilyTable(){}

	void CleanUp()
	{
		for ( int32_t i = 0; i < MAX_FAMILY_LEVEL; ++i )
		{
			m_vFamily[i].CleanUp();
		}
		bzero( m_vTotomActiveLevel, sizeof( m_vTotomActiveLevel ) );
		bzero( m_vFamilyPosition, sizeof( m_vFamilyPosition ) );
	}

	bool Add( const CfgFamily& family )
	{
		m_vFamily[family.nLevel-1] = family;
		return true;
	}

	bool Add( int8_t nPosition, const CfgFamilyPosition& position )
	{
		if ( nPosition < 0 || nPosition >= FAMILY_POSITION_COUNT )
		{
			return false;
		}

		m_vFamilyPosition[nPosition] = position;
		return true;
	}

	bool AddActiveTotom( int32_t nTotomId, int32_t nLevel )
	{
		if ( nTotomId <= 0 || nTotomId > MAX_PET_ID )
		{
			return false;
		}

		m_vTotomActiveLevel[nTotomId] = nLevel;
		return true;
	}

	const CfgFamily* GetFamilyInfo( int32_t nLevel ) const
	{
		if ( nLevel <= 0 || nLevel > MAX_FAMILY_LEVEL )
		{
			return NULL;
		}
		return &m_vFamily[nLevel-1];
	}

	int32_t GetTotomActiveLevel( int32_t nTotomId ) const
	{
		if ( nTotomId <= 0 || nTotomId > MAX_PET_ID )
		{
			return NULL;
		}
		return m_vTotomActiveLevel[nTotomId];
	}

	const CfgFamilyPosition* GetFamilyPosition( int8_t nPosition ) const
	{
		if ( nPosition < 0 || nPosition >= FAMILY_POSITION_COUNT )
		{
			return NULL;
		}
		return &m_vFamilyPosition[nPosition];
	}


private:
	CfgFamily			m_vFamily[MAX_FAMILY_LEVEL];
	int32_t				m_vTotomActiveLevel[MAX_PET_ID+1];						// 图腾激活所需军团等级
	CfgFamilyPosition	m_vFamilyPosition[FAMILY_POSITION_COUNT];				// 军团职位配置
};

struct TeamBuff 
{
	int32_t nExpRatio;
	int32_t nHPRatio;
};

class CfgTeamTable
{
public:
	CfgTeamTable(){ CleanUp(); }
	~CfgTeamTable(){}

	void CleanUp()
	{
		bzero( m_vBuff, sizeof( m_vBuff ) );
	}

	bool Add( int32_t nNum, int32_t nExpRatio, int32_t nHPRatio )
	{
		int32_t nIndex = nNum - 1;
		if ( nIndex < 0 || nIndex >= MAX_TEAM_MEMBER_COUNT )
		{
			return false;
		}
		if ( nExpRatio > 0 )
		{
			m_vBuff[nIndex].nExpRatio = nExpRatio;
		}
		if ( nHPRatio > 0 )
		{
			m_vBuff[nIndex].nHPRatio = nHPRatio;
		}
		return true;
	}

	int32_t GetTeamExpRatio( int32_t nNum ) const
	{
		int32_t nIndex = nNum - 1;
		if ( nIndex < 0 || nIndex >= MAX_TEAM_MEMBER_COUNT )
		{
			return 0;
		}
		return m_vBuff[nIndex].nExpRatio;
	}

	int32_t GetTeamHPRatio( int32_t nNum ) const
	{
		int32_t nIndex = nNum - 1;
		if ( nIndex < 0 || nIndex >= MAX_TEAM_MEMBER_COUNT )
		{
			return 0;
		}
		return m_vBuff[nIndex].nHPRatio;
	}

private:
	TeamBuff m_vBuff[MAX_TEAM_MEMBER_COUNT];
};
//wmf end


//坐骑培养系统相关
struct  GameMountTrain
{
	GameMountTrain()
	{
		m_MountLevel		= 0;
		m_MountName			= "";
		m_MountSkinID		= 0;
		m_MinLucky			= 0;
		m_MaxLucky			= 0;
		m_Rate				= 0;
		m_GetLucky			= 0;
		m_NeedZiYuanType	= 0;
		m_NeedZiyuanCount	= 0;
		m_NeedItemId		= 0;
		m_NeedItemCount		= 0;
		m_IsActiveSkill		= 0;
		m_IsCleanLuck		= 0;
		m_CanEatMountHeart	= 0;
		m_AddSpeed			= 0;
		m_AddAttrList.clear();
	}
	uint8_t			m_MountLevel;
	std::string		m_MountName;
	int32_t			m_MountSkinID;
	int32_t			m_MinLucky;
	int32_t			m_MaxLucky;
	int32_t			m_Rate;
	int32_t			m_GetLucky;
	uint8_t			m_NeedZiYuanType;
	int32_t			m_NeedZiyuanCount;
	uint8_t			m_NeedItemId;
	int32_t			m_NeedItemCount;
	uint8_t			m_IsActiveSkill;
	uint8_t			m_IsCleanLuck;
	int32_t			m_CanEatMountHeart;
	int32_t			m_AddSpeed;
	AddAttrList m_AddAttrList;
};

struct GameMountTrainTBL
{
	GameMountTrainTBL()
	{
		m_MountTrainMap.clear();
	}
	const GameMountTrain*  GetMountTrainData( uint8_t MountTrainLevel )
	{
		map<uint8_t,GameMountTrain>::iterator it = m_MountTrainMap.find(MountTrainLevel);
		if ( it != m_MountTrainMap.end() )
		{
			return &(it->second);
		}
		return NULL;
	}
	uint8_t GetMaxLevel()
	{
		return m_MountTrainMap.size();
	}
	map<uint8_t,GameMountTrain>   m_MountTrainMap;
};

struct CMountHeart //坐骑之星属性表
{
	CMountHeart()
	{
		m_NeedItemBingID	= 0;
		m_NeedItemUnBingID	= 0;
		m_NeedItemClass		= 0;
		m_NeedItemId		= 0;
		m_Type				= 0;
		m_NeedMountQuaLity	= 0;
		m_AddAttrList.clear();
	}
	AddAttrList GetAddAttrList()
	{
		return m_AddAttrList;
	}
	uint8_t m_Type;
	uint8_t m_NeedMountQuaLity;
	int32_t m_NeedItemBingID;
	int32_t m_NeedItemUnBingID;
	uint8_t m_NeedItemClass;
	uint8_t m_NeedItemId;
	AddAttrList m_AddAttrList;
};
typedef std::map<uint8_t,CMountHeart> CMountHeartMap;

struct CLearnMountSkillTBL
{
	CLearnMountSkillTBL()
	{
		m_SkillType			= 0;
		m_SkillName			= "";
		m_NeedMountLevel	= 0;
		m_StudyItemId		= 0;
		m_StudyItemCount	= 0;
		m_SkillEsc			= "";
	}
	uint8_t m_SkillType;
	std::string m_SkillName;
	uint8_t m_NeedMountLevel;
	uint8_t m_StudyItemId;
	int32_t m_StudyItemCount;
	std::string m_SkillEsc;
};
typedef std::map<uint8_t,CLearnMountSkillTBL> LearnMountSkillMap;
struct MountSKillLevelUp
{
	MountSKillLevelUp()
	{
		m_Index			= 0;
		m_SkillType		= 0;
		m_SkillLevel		= 0;
		m_UpItemId		= 0;
		m_UpItemCount		= 0;
		m_AttrType			= 0;
		m_AttrRate			= 0;
	}
	uint8_t m_Index;
	uint8_t m_SkillType;
	uint8_t m_SkillLevel;
	uint8_t m_UpItemId;
	int32_t m_UpItemCount;
	uint8_t m_AttrType;
	int32_t m_AttrRate;
};
struct MountSKillLevelUpTabl
{
	MountSKillLevelUpTabl()
	{
		m_MountSkillLevelUpVct.clear();
	}
	MountSKillLevelUp* GetMountLevelUpdata(uint8_t SkillType,uint8_t SkilLevel )
	{
		std::vector<MountSKillLevelUp>::iterator it = m_MountSkillLevelUpVct.begin();
		for ( ; it != m_MountSkillLevelUpVct.end(); ++it )
		{
			if ( it->m_SkillType == SkillType && it->m_SkillLevel == SkilLevel )
			{
				return &(*it);
			}
		}
		return NULL;
	}
	uint8_t GetSkillMaxLevel(uint8_t SkillType )
	{
		uint8_t SkillLevel = 0;
		std::vector<MountSKillLevelUp>::iterator it = m_MountSkillLevelUpVct.begin();
		for ( ; it != m_MountSkillLevelUpVct.end(); ++it )
		{
			if ( it->m_SkillType == SkillType ) //最大等级没有升级物品
			{
				if ( SkillLevel < it->m_SkillLevel )
				{
					SkillLevel = it->m_SkillLevel;
				}
			}
		}
		return SkillLevel;
	}
	void Add(MountSKillLevelUp& stu)
	{
		m_MountSkillLevelUpVct.push_back(stu);
	}
	std::vector<MountSKillLevelUp> m_MountSkillLevelUpVct;
};

struct PkDropRate
{
	int32_t		PkValues;			//pk值
	int32_t		EquipCount;			//掉落装备数
	int32_t		EquipRate;			//装备掉落比例
	int32_t		UsualCountRate;		//普通物品掉落个数比例
	int32_t		UsualDropRate;		//普通物品掉落比例
	int32_t		SpecialCountRate;	//特殊物品掉落个数比例
	int32_t		SpecialDropRate;	//特殊物品掉落比例
	int32_t		OverlayRate;		//叠加数掉落比例
	int32_t		MoneyRate;			//铜钱掉落比例
};


struct QiangHuaWorthTable
{
	int32_t Worth[EQUIP_MAX_STAT];
};
typedef std::map<int8_t,QiangHuaWorthTable> QiangHuaWorthMap;

class CfgFaBao
{
public:
	CfgFaBao()
	{
		FaBaoLevel		= 0;
		NeedRes			= 0;
		m_AttrList.clear();
	}
	int32_t			FaBaoId;
	int32_t			NextFaBaoId;
	int32_t			FaBaoType;
	int32_t			FaBaoLevel;		
	int32_t			NeedRes;
	AddAttrList		m_AttrList;
};
typedef std::map<int32_t, CfgFaBao> FaBaoMap;

class FaBaoTable
{
public:
	FaBaoTable();
CfgFaBao*		GetFaBaoCfg( int32_t FaBaoId );
void			AddFaBao( CfgFaBao& Stu );
private:
	FaBaoMap	m_FaBaoTable;		//曙光法宝表
};

class CfgSysMail
{
public:
	CfgSysMail()
	{
		sender_name		= "";
		title			= "";
		content			= "";
		item.clear();
	}
	int32_t id;
	std::string sender_name;
	std::string title;
	std::string content;
	MemChrBagVector  item;
};
typedef std::map<int32_t,CfgSysMail>CfgSysMailTable;

struct BuyFaBaoResCfg
{
	int32_t	id;
	int8_t	FaBaoResType;
	int32_t	NeedGold;
	int32_t GetResValues;
};
typedef std::map<int32_t, BuyFaBaoResCfg> FaBaoResMap;

class BossInfo
{
public:
	BossInfo()
	{
		m_BossId			= 0;
		m_TransferPos.x		= 0;
		m_TransferPos.y		= 0;
		m_RevivePosVector.clear();
	}
	int32_t					m_BossId;
	Position				m_TransferPos;		// 传送坐标
	std::vector<Position>	m_RevivePosVector;	// 复活坐标列表
};
typedef std::map<int32_t, BossInfo> BossInfoMap;

struct CfgQuestions
{
	int32_t QuestionId;
	int8_t AnswerId;
};
typedef std::vector<CfgQuestions> QuestionsVector;

struct CfgDaTiHD
{
	int32_t StartSeconds;
	int32_t HDTime;
};

class CfgData
{
public:
	CfgData();
	~CfgData();

public:
	bool init();

public:
	const int32_t getServerStartTime();
	const int32_t getServerStartDayTime();
	const int32_t getServerDiffTime();

	const CfgActivityTable& getAllActivity();
	//const CfgKingdomTable& getKingdomAll();
	CfgActivity* getActivity(int32_t id);
	CfgActivityEventVector* getActivityEvents(int32_t activity_id);
	
	CfgActivityMonster* getActivityMonsterById(int32_t id,int32_t actid);
	CfgActivityMonsterVector* getActivityMonster(int32_t activity_id, int32_t wave);
	CfgActivityNpcVector* getActivityNpc(int32_t activity_id);
	CfgActivityPlantVector* getActivityPlant(int32_t activity_id, int32_t wave);
	CfgActivityDropTable* getActivityDrops();

	const CfgAnnoucementTimeTable& getAllAnnoucementTime() const;

	CfgBuff* getBuff(int32_t id);

	const CfgDungeonTable& getDungeonAll();
	CfgDungeon* getDungeon(int32_t id);
	//CfgDungeon* getDengTianTiFirstDungeon();

	void getDungeonEvent(int32_t dungonid,int32_t type,CfgDungeonEventList &events);
	CfgDungeonEvent*  getDungeonEvent(int32_t dungeonID,int32_t type);

	CfgDungeonMonster* getDungeonMonster(int32_t id);
	CfgDungeonPlant* getDungeonPlant(int32_t id);
	CfgDungeonTrap* getDungeonTrap(int32_t id);

	const CfgEquip* getEquip(int32_t id) const;
	CfgChrShop* getChrShop( int32_t Index );
	CfgChrShop* getChrShopTop( int8_t type, int32_t nLevel );

	CfgGamble* getGamble(int32_t ratio,int32_t type);
	CfgGambleEquip* getGambleEquip(int32_t id);

	CfgItemTable getAllItem();
	CfgItem* getItem(int32_t id);
	CfgItemGiftVector* getItemGift(int32_t id);
	CfgItemGiftRandomVector* getItemGiftRandom(int32_t id);

	CfgJob* getJob(int32_t id);
	bool getMovie(int32_t id);

	const CfgMapTable& getMapAll();
	CfgMap* getMap(int32_t id);
	Int32Vector* getFamilyBossActivityReward(int32_t level);

	CfgMapMonsterVector* getMonstersOnMap(int32_t mapid);
	CfgMapMonster* GetMapMonsterInfo( int32_t id );
	CfgMapMonster* GetMapMonsterInfoByMid( int32_t mid, MapId_t mapid );
	CfgMapPlantVector* getPlantOnMap(int32_t mapid);

	CfgMapRegion* getMapRegion(int32_t id);
	CfgMapRegion getOfflineExpRegion();
	CfgMapRegionVector* getRegionOnMap(int32_t mapid);

	CfgMonster* getMonster(int32_t mid);
	bool isMonsterBroadcast(int32_t mid);
	CfgMonsterDropGroupVector* getMonsterDropGroup(int32_t group_id);
	CfgMonsterGroupDropVector* getMonsterGroupDrop(int32_t mid);
	CfgMonsterTaskDropVector* getMonsterTaskDrop(int32_t mid);
	CfgDungeonDropGroupVector* getDungeonDropGroup(int32_t groupID);
	CfgDungeonReward* getDungeonReward(int32_t dungeonID);

	CfgBornAttr*  getBornAttr(Job_t jobindex);
	CfgChangeJobAttr* getChangeJobAttr(int32_t index);

	CfgNpc* getNpc(int32_t npcid);
	const CfgNpcTable& getNpcAll();
	CfgNpcAirport* getNpcAirport(int32_t id);
	CfgNpcKingdomShop* getNpcKingdomShop(int32_t id);
	
	CfgOnlineReward* getOnlineReward(int32_t id);
	CfgOnlineRewardVector getOnlineRewardByType(int32_t type);
	int32_t getOnlineTime(int32_t id);

	CfgPlant* getPlant(int32_t id);

	CfgSkill* getSkill(int32_t id);
	CfgTask* getTask(int32_t id);

	CfgAcSpecial* getAcSpecial(int32_t id);
	CfgAcSpecial* getAcSpecialByID(int32_t id);
	CfgAcOutdoorCave* getAcOutdoorCave(int32_t id);
	CfgAcDaily*getAcDaily(int32_t id);
	CfgAcExchange*getAcExchange(int32_t id,int32_t index);
	CfgAcGrowUp* getAcGrowUp(int32_t id);
	CfgAcChallenge* getAcChallenge(int32_t id);
	void  initAcOutdoorCave(CfgAcOutdoorCavePTable &outdoorCave,int32_t level);
	CfgAchievement*getAchievement(int32_t id);
	int32_t getFirstAchievement();
	int32_t getAchievementCount(int32_t level);
	CfgAcTask* getAcTask(int32_t taskID);
	CfgAcTask* getAcTaskByID(int32_t id);
	CfgYellowStone* getYellowStone(int32_t id);
	PkDropRate*		GetPkDropRate( int32_t PkValues );
	//int32_t generateCycleTasks(int32_t level);
	//int32_t generateFamilyTask(int32_t level);
	int32_t generateKingdomTask(int32_t level);
	int32_t getTaskDailyWindItem(int32_t tid, int32_t wind_point);

	CfgTask getTaskKingdomGather();
	CfgTask getTaskKingdomMonster(int32_t level);
	CfgTask getTaskKingdomTalk();
	CfgTask getTaskKingdomHome();

	CfgTrailer* getTrailer();
	CfgTrap* getTrap(int32_t id);
	//CfgVip getVip(VipType type);
	CfgItemBase* getItemBase(int32_t id, int32_t type);
	MemChrBagVector getSignReward(int32_t count, int32_t minOrder, int32_t maxOrder);
	int32_t getSignRewardIndex(int32_t count);
	CfgSevenLogin* getSevenReward(int32_t days);
	std::string getItemName(int32_t id, int32_t type);
	int32_t getOverlay(int32_t id, int32_t itemClass);
	int32_t getInValue(int32_t id, int32_t type);
	int32_t getOutValue(int32_t id, int32_t type);
	bool canSell(int32_t id, int32_t itemClass);
	CfgLevelExp* getUpgradeExp(int32_t level);
	int64_t getNeedLevelExp(int32_t level);
	int64_t getMaxExp(int32_t level);
	int32_t	GetPetExp( int32_t level );
	CfgLevelAttr getLevelAttr(int32_t job,int32_t level);
	CfgLevelGift* getLevelGift(int32_t level);
	CfgLevelGold* getLevelGold(int32_t level);

	int32_t getBaseJob(int32_t job);
	bool isBanChat(int32_t uid, int32_t nowTime);

	int32_t getMemFamilyWarFamilyId();
	std::string getMemFamilyWarFamilyName();
	void updateMemFamilyWar(const MemFamilyWar &familyWar);
	void onMemFamilyWarUpdated(const MemFamilyWar &familyWar);

	AttrAddonVector getItemEffect(int32_t id);

	void onAvgLevelUpdated(int32_t avgLevel);
	AttrAddonVector parseItemEffect(int32_t id,const std::string &str);
	MemChrBagVector parseAllItemString(int32_t id, const std::string &strItems);

	int32_t getCreateTime();
	int32_t getDebug();

	CfgDailyItem* getDailyItemMark(int32_t type,int32_t id = 0);
	int32_t getDailyReward(int32_t id,int32_t level);
	int32_t  getDailyItemID(int32_t type);
	int32_t  getDailyMarkGiftID(int32_t mark);

	CfgNewServerActivity* getNewServerActivityByID(int32_t type,int32_t value,int32_t &index);
	CfgNewServerActivity* getNewServerActivity(int32_t type, int32_t value, int32_t param);
	CfgNewServerGold* getNewServerGold(int32_t id);
	CfgNewServerLater* getNewServerLater(int32_t id);

	CfgDailySearchBack* getDailySearchBack(int32_t id,int32_t level);
	void calcAchievementCount();
	void onBanChatUpdated(int32_t action, int32_t uid, int32_t expire_time);

	void setRealTimeRankLevelBase(int32_t base);
	void setRealTimeRankFightPowerBase(int32_t base);
	int32_t getRealTimeRankLevelBase();
	int32_t getRealTimeRankFightPowerBase();

	const CfgEquipTable&			GetEquipTable() const;
	const CfgItemGemTable&			GetItemGemTable() const;
	const CfgItemCombiTable&		GetItemCombiTable() const;
	const CfgBagSlotOpenTimeTable&	GetBagSlotOpenTimeTable() const;
	const CfgPetTable&				GetPetTable() const;
	const CfgPetAttrInitRateTable&	GetPetAttrInitRateTable() const;
	const CfgPetIllusionTable&		GetPetIllusionTable() const;
	const CfgSkillLevelUpTable&		GetSkillLevelUpTable() const;
	const CfgTaskCycleTable&		GetTaskCycleTable() const;
	const CfgPetKnightTable&		GetPetKnightTable() const;
	const CfgFamilyPetRegistTable&	GetFamilyPetRegistTable() const;
	const CfgFamilyTable&			GetFamilyTable() const;
	const CfgCharPetTable&			GetCharPetTable() const;
	const CfgTeamTable&				GetTeamTable() const;

	GameMountTrainTBL&			GetMountTrainTab();
	CMountHeartMap&				GetMountHeart();			
	LearnMountSkillMap&			GetMountSkillTable();
	MountSKillLevelUpTabl&		GetMountSkillLevelTable();
	int32_t						GetFriendExpByLevel( int32_t Level );
	int32_t						GetQiangHuaWorth( int8_t Quality, int8_t Star );
	CfgSysMail*					GetSysMail( int32_t Id );

	BossInfo*					GetBossInfo( int32_t BossId );
	BossInfoMap&				GetBossInfoMap();
	FaBaoTable&					GetFaBaoTable();
	CfgGameShop*				GetGameShop(int32_t nShopId );
	CfgGameShop*				GetGameShopItem( int8_t Class, int32_t Id );

	
	BuyFaBaoResCfg*				GetBuyFaBaoResCfg( int32_t Id );
	QuestionsVector				GetAllQuestions();
	CfgDaTiHD&					GetDaTiCfg();	
	CfgPetGift*					GetPetCfg( int32_t nId );			

private:
	void getExParams(cfgParams& params,const std::string& str);

	void fetchcfExActivity();
	//void fetchKingdom();
	void fetchActivity();
	void fetchGmtBanChat();
	void fetchAnnoucementTime();
	void fetchBuff();
	void fetchDungeon();
	void fetchDungeonEvent();
	void fetchDungeonMonster();
	void fetchDungeonPlant();
	void fetchDungeonTrap();
	void fetchFamily();
	void fetchChrShop();
	void fetchItem(bool bSend);
	void fetchJob();
	void fetchMovie();
	void fetchLevelExp();
	void fetchLevelAttr();
	void fetchBuleprint();
	void fetchMap();							//获取地图信息表
	void fetchMapMonster();			
	void fetchMapPlant();						
	void fetchMapRegion();						
	void fetchMonster();
	void fetchMonsterDropGroup();
	void fetchMonsterGroupDrop();
	void fetchMonsterTaskDrop();
	void fetchNpc();
	void fetchGamble();
	void fetchBornAttr();
	void fetchChargeRewards();
	void fetchOnlineReward();
	void fetchPlant();
	void fetchSkill();
	void fetchTask();
	void fetchDaily();
	void fetchTaskCycleGroup();
	void fetchTrailer();
	void fetchTrap();
	//void fetchVip();
	void fetchFormation();
	void fetchAchievement();
	void fetchLevelGift();
	void fetchLevelGold();
	void fetchSignReward();
	void fetchSevenLogin();
	void fetchNewServerActivity();
	void fetchYellowStone();

	ChangeJobIndexVector parseChangeJobEffect(int32_t id, const std::string &str);
	FamilyRegionVector parseFamilyRegionEffect(int32_t id, const std::string &str);
	AttrAddonVector parseEquipEffect(int32_t id, const std::string &str);
	AttrAddonVector parseEffect(int32_t id, const std::string &str);
	Int32Vector parseShejituEffect(int32_t id,const std::string &str);
	Int32Vector parseInt32VectorString(int32_t id,const std::string &str);

	MemChrBagVector parseTaskItemString(int32_t id, const std::string &strItems);
	void parseItemStringWithJob(int32_t id,const std::string &strItems,MemChrBagVector &items,MemChrJobBagVector&jobItems);
	MemChrBagVector parseItemString(int32_t id, const std::string &strItems);
	MemChrBag parseDailyPkString(int32_t id, const std::string &strItems);
	MemChrJobBagVector parseTaskItemJobString(int32_t id, const std::string &strItems);
	TaskDest parseTaskDestString( int32_t id, const std::string &strItems );
	void parseMonsterSkill(int32_t id, MonsterSkill (&vSkill)[MAX_MONSTER_SKILL], const std::string &strSkill);
	TaskRequest parseTaskCondition(int32_t id, int32_t condition, const std::string &strRequest);
	MemJobItemTable parseGambleEquip(int32_t id,const std::string &strItems);
	std::vector<Position> paresPosition( const std::string &strPos );
	Int32Vector parseAchievementString(int32_t id,const std::string &str);
    AcExchangeItemVector paresAcExchangeString(int32_t id,const std::string &str);

	void parasItemData( ItemData& data, const std::string& str );
	void parasItemData( MemChrBag& data, const std::string& str );

	void fetchGMAnnouncement();
	void fetchMemFamilyWar();
	void fetchServerConfig();
	void sendNewItems(const CfgItemTable &items);

	// 初始化装备表
	void InitEquipTable();
	void InitEquipUpGradeTable();
	void InitEquipUpQualityTable();
	void InitEquipUpStarTable();
	void InitEquipAddAttrTable();
	void InitEquipGoalTable();
	void InitEquipSuitTable();

	void InitItemGemTable();				// 初始化宝石表
	void InitItemCombiTable();				// 初始化合成表
	void InitBagSlotOpenTimeTable();		// 初始化背包开启时间表
	void InitPetTable();					// 初始化幻兽表
	void InitPetAttrInitRateTable();		// 初始化幻兽属性百分比对应表
	void InitPetIllusionTable();			// 初始化幻兽幻化表
	void InitPetKnightTable();				// 初始化幻兽骑士表
	void InitSkillLevelUpTable();			// 初始化技能升级表
	void InitTaskCycleStarTable();			// 初始化循环任务表
	void InitFamilyTable();					// 初始化军团表
	void InitFamilyPositionTable();			// 军团职位表
	void InitFamilyPetRegistTable();		// 初始化宠物登记表
	void InitCharPetHatchPoolTable();		// 初始化宠物孵化池配置表
	void InitPetLucyItemTable();			// 初始化宠物幸运值幻化道具表
	void InitTeamBuffTable();				// 初始化组队Buff表


	void InitMountHearAttrTable();			//初始化坐骑之心属性表
	void InitMountSkillTable();				//初始化坐骑技能表
	void InitMountSkillLevelUp();			//初始化坐骑技能升级表
	void InitMountTrainTable();				//初始化坐骑升阶表

	void InitFriendExpTable();				//初始化好友经验表

	void InitPkDropRateTable();				//初始化pk掉落概率
	void InitQiangHuaWorthTable();			//初始化强化价值表
	void InitSysMail();						//初始化系统邮件
	void InitBossInfo();					//初始化boss信息
	void InitFaBaoTable();					//初始化法宝信息表
	void InitBuyFaBaoResTable();			//初始化购买法宝资源表
	void InitDaTiHD();						//初始化答题活动
	void InitShangChengTable();				//初始化商城表
	void InitPetGiftTable();				//初始化幻兽礼包表

private:
	CfgActivityTable m_activities;
	CfgActivityBanquetVector m_BanquetRegion;
	CfgActivityEventTable m_activityEvents;
	CfgActivityMonsterTable m_activityMonsters;
	CfgActivityNpcTable m_activityNpcs;
	CfgActivityPlantTable m_activityPlants;
	CfgActivityDropTable m_activityDrops;
	CfgAnnoucementTimeTable m_annoucementTimes;
	CfgBuffTable m_buffs;
	CfgDungeonTable m_dungeons;
	CfgDungeonRewardTable m_dungeonReward;
	CfgDungeonDropGroupTable  m_dungeonDropGroup;
	CfgDungeonEventTable m_dungeonEvents;
	CfgDungeonMonsterTable m_dungeonMonsters;
	CfgDungeonPlantTable m_dungeonPlants;
	CfgDungeonTrapTable m_dungeonTraps;

	GmtBanChatTable m_banChats;
	Answer::Mutex m_banChatsLock;

	CfgItemTable m_items;
	Answer::RwLock m_itemsLock;

	CfgItemGiftTable m_itemGifts;
	Answer::RwLock m_itemGiftsLock;

	CfgItemGiftRandomTable m_itemGiftRandoms;
	Answer::RwLock m_itemGiftRandomsLock;

	CfgMountEquipTable m_mountEquip;
	//CfgKingdomTable m_kingdoms;
	CfgJobTable m_jobs;
	CfgMovieTable m_movie;
	CfgLevelExpTable m_levelExps;
	CfgMapTable m_maps;
	CfgMapMonsterTable m_mapMonsters;
	CfgMonsterMap	   m_CfgMapMonsters;

	CfgMapPlantTable m_mapPlants;
	CfgMapRegionTable m_mapRegions;
	CfgMapRegion m_offlineExpRegion;
	Int32CfgMapRegionVectorMap m_mapRegionsByMapId;
	CfgMonsterTable m_monsters;
	Int32Vector m_monsterBroadcasts;
	CfgMonsterDropGroupTable m_monsterDropGroups;
	CfgMonsterGroupDropTable m_monsterGroupDrops;
	CfgMonsterTaskDropTable m_monsterTaskDrops;
	CfgNpcTable m_npcs;
	CfgBornAttrTable m_bornAttr;
	CfgChangeJobAttrTable m_changeAttr;
	CfgNpcAirportTable m_npcAirports;
	CfgChrShopTable m_chrShops;
	CfgChargeRewardsVector m_chargeRewards;
	CfgOnlineRewardTable m_onlineRewards;
	CfgPlantTable m_plants;
	CfgSkillTable m_skills;
	CfgTaskTable m_tasks;
	//Int32Int32VectorMap m_taskCycles;
	Int32Int32VectorMap  m_kingdomTask;
	CfgTaskGroupTable m_taskGroups;
	CfgTask m_taskKingdomGather;
	CfgTaskVector m_taskKingdomMonster;
	CfgTask m_taskKingdomTalk;
	CfgTask m_taskKingdomHome;
	CfgTrailer m_tailers;
	CfgTrapTable m_traps;
	//CfgVipTable m_vips;
	CfgLevelAttrTable m_levelAttrs;
	CfgDailyItemTable m_dailyItems;
	CfgDailyMarkTable m_dailyMark;
	CfgDailySearchBackTable m_dailySearchBack;
	CfgDailyRewardTable m_dailyReward;
	GmtAnnouncementTable m_gmAnnouncements;
	CfgAchievementTable m_achievement;
	CfgAcOutdoorCaveTable  m_acOutdoorCave; 
	CfgAcDailyTable  m_acDaily;
	CfgAcChallengeTable m_acChallenge;
	CfgAcExchangeTable m_acExchange;
	CfgAcGrowUpTable   m_acGrowUp;
	CfgAcSpecialTable  m_acSpecial;
	CfgAcTaskTable     m_acTask;
	AchievementCountTable m_acCount;
	CfgGambleVector  m_gamble;
	CfgGambleVector  m_gamble_second;
	CfgGambleVector  m_gamble_three;
	CfgGambleEquipTable m_gambleEquip;
	CfgLevelGiftTable   m_levelGift;
	CfgLevelGoldTable   m_levelGold;
	CfgSignRewardTable  m_signReward;
	CfgSevenLoginTable  m_sevenReward;
	CfgNewServerActivityTable m_newServerActivity;
	CfgNewServerGoldTable m_newServerGold;
	CfgNewServerLaterTable m_newServerLater;
	CfgFamilyLevelTable  m_familyLevel;
	CfgYellowStoneTables m_yellowStone;

	CfgEquipTable			m_cfgEquip;					// 装备表
	CfgItemGemTable			m_cfgItemGem;				// 宝石表
	CfgItemCombiTable		m_cfgItemCombi;				// 合成表
	CfgBagSlotOpenTimeTable	m_cfgBagSlotOpenTime;		// 背包开启时间表
	CfgPetTable				m_cfgPetTable;				// 幻兽表
	CfgPetAttrInitRateTable	m_cfgPetAttrInitRateTable;	// 幻兽初始化属性百分比对应表
	CfgPetIllusionTable		m_cfgPetIllusionTable;		// 幻兽幻化表
	CfgPetKnightTable		m_cfgPetKnightTable;		// 幻兽骑士表
	CfgSkillLevelUpTable	m_cfgSkillLevelUpTable;		// 技能升级表
	CfgTaskCycleTable		m_cfgTaskCycleTable;		// 循环任务表
	CfgFamilyTable			m_cfgFamilyTable;			// 军团表
	CfgFamilyPetRegistTable	m_cfgFamilyPetRegistTable;	// 宠物登记表
	CfgCharPetTable			m_cfgCharPetTable;			// 玩家宠物系统配置表
	CfgTeamTable			m_cfgTeamTable;				// 组队信息表

	GameMountTrainTBL			m_MountTrainTBL;	//坐骑升阶表
	CMountHeartMap				CMountHeartTBL;
	LearnMountSkillMap			m_LearMountSkillTabl;
	MountSKillLevelUpTabl		m_MountSkillLevelUpTable;

	MemFamilyWar m_memFamilyWar;

	cfgExActivitys m_cfgExActivitys;
	Answer::RwLock m_exActivityLock;

	int32_t m_avgLevel;
	int32_t m_createTime;
	int32_t m_debug;
	int32_t m_startServerTime;

	int32_t m_realTimeRankLevelBase;
	int32_t m_realTimeRankFightPowerBase;

	CfgFriendExpTable m_FriendExpTable;
	std::list<PkDropRate> m_PkDropRateTable;
	QiangHuaWorthMap	  m_QiangHuaWorthTable;
	CfgSysMailTable		  m_sysMail;
	BossInfoMap			  m_BossInfo;
	FaBaoTable			  m_FaBaoTable;
	FaBaoResMap			  m_FaBaoResMap;
	QuestionsVector		  m_QuestionsVct;
	CfgDaTiHD			  m_DaTiHDCfg;
	GameShopMap			  m_GameShopMap;
	PetGiftMap			  m_PetGiftTable;
};
#define CFG_DATA Answer::Singleton<CfgData>::instance()


