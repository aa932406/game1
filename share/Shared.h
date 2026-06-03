#pragma once

#include "Attribute.h"
#include "PDUDefine.h"
#include "Type.h"
#include "stdafx.h"
#include <vector>
#include <sstream>
#include <set>
#define MAX_CONNECTION 10000
#define MAX_SQL_LENGTH 4096

/*
* 一个服务器100w个角色
* 32位字段可以开2100个服
* 超过这个数把CharId改成UInt或扩成64位
*/
#define MAX_SERVER_CHAR_ID	1000000

#define GAME_SERVICE_LINE_SOCIAL 1

enum ErrorCode
{
	ERR_OK = 0,
	ERR_LEAVE_KINGDOM,
	ERR_SYETEM_ERR,
	ERR_FOR_GAME_CLIENT_BASE = 10001,
	ERR_INVALID_DATA,
	ERR_WRONG_PASSWORD,
	ERR_NAME_EXIST,
	ERR_GENERAL_CD,
	ERR_ALREADY_IN_CHANT,
	ERR_TARGET_NOT_EXIST,
	ERR_NOT_ENOUGH_HP,
	ERR_NOT_ENOUGH_MP,
	ERR_NOT_ENOUGH_MONEY,
	ERR_NOT_ENOUGH_JUNGONG,
	ERR_NOT_ENOUGH_WUHUEN,
	ERR_LEVEL_TOO_LOW,
	ERR_LEVEL_TOO_HIGH,
	ERR_DISTANCE_TOO_LONG,
	ERR_BAG_IS_FULL,
	ERR_BAD_LUCK,
	ERR_IN_DEAL,
	ERR_ALREADY_IN_GATHER,
	ERR_BREAK,
	ERR_NOT_ENOUGH_LEFT_AMOUNT,
	ERR_DUNGEON_PLAYER_LEVEL,
	ERR_DUNGEON_DAILY_COUNT,
	ERR_PLAYER_NOT_EXIST,
	ERR_SKILL_CD,
	ERR_NOT_ENOUGH_ANGRY,
	ERR_SWITCH_MAP_WITH_TRAILER,
	ERR_NPC_ACQUIRE_LIMIT,
	ERR_NPC_DONATE_LIMIT,
	ERR_ITEM_CD,
	ERR_LACK_OF_FAMILY_MONEY,
	ERR_FAMILY_LEVEL_LIMIT,
	ERR_FAMILY_TREE_LIMIT,
	ERR_FAMILY_LEVEL_LOW,
	ERR_FAMILY_ALREADY_APPLIED,
	ERR_FAMILY_POSITION_LIMIT,
	ERR_FAMILY_ACTIVITY_LIMIT,
	ERR_DELETE_CHR_AS_FAMILY_LEADER,
	ERR_GM_BAN_LOGIN,
	ERR_GM_BAN_CHAT,
	ERR_WRONG_VERSION,
	ERR_EXCHANGE_CODE_USED,
	ERR_EXCHANGE_CODE_NOT,
	ERR_EXCHANGE_CODE_SAME,
	ERR_TREASURE_STORE_IS_FULL,
	ERR_EXP_GAIN_LIMIT,
	ERR_AUCTION_ITEM_DELETED,
	ERR_AUCTION_ITEM_EXPIRED,
	ERR_AUCTION_ITEM_SELLED,
	ERR_AUCTION_ITEM_IN_SELL,
	ERR_PLAYER_OFF_LINE,
	ERR_EXCHANGE_CODE_GOLD_LIMIT,
	ERR_TOAST_COUNT_LIMIT,
	ERR_DELAY_EXCHANGE_SLOT_NEED,
	ERR_DUNGEON_TRAILER,
	ERR_MAP_PLAYER_LEVEL,
	ERR_MAP_TEAM_MEMBER_COUNT,
	ERR_MAP_ACTIVITY_NOT_STARTED,
	ERR_MAP_ACTIVITY_ENTRY_CLOSED,
	ERR_MAP_ACTIVITY_ENTRY_KING,
	ERR_MAP_CANNOT_REVIVE,
	ERR_MAP_ACTIVITY_OTHER_LINE,
	ERR_MAP_CHALLENGE_TIME_END,
	ERR_MAP_FAMILY_NEED,
	ERR_MAP_FAMILY_ATTACK,
	ERR_MAP_CONNOT_GO,
	ERR_FLAG_CANNOT_ATTACK,
	ERR_STRATEGICE_READ_NOT,
	ERR_NOT_ENOUGH_STUFF,
	ERR_TASK_FAIL,
	ERR_APPLY_COUNT_FULL,
	ERR_CHANGE_JOB_FAIL,
	ERR_MOUNT_INHERITANCE_FAIL,
	ERR_MOUNT_FORM_EXIST,
	ERR_MOUNT_FORM_GRADE,
	ERR_MOUNT_FORM_EXCHANGE,
	ERR_NOT_ENOUGH_GOLD,
	ERR_MAP_ACTIVITY_NOTADD_FAMILY,
	ERR_MAP_ACTIVITY_PKIN,
	ERR_MAP_ACTIVITY_NOTADD_KINGDOM,
	ERR_MAP_ACTIVITY_INPLAY,
	ERR_MAP_ACTIVITY_INDUM,
	ERR_MAP_ACTIVITY_NOTMAP,
	ERR_MAP_ACTIVITY_NOTREG,
	ERR_MAP_ACTIVITY_LEVEL,
	ERR_SKILL_MAXLEVEL,
	ERR_MAIL_FULL,
	ERR_RELATION_BAD,
	ERR_IS_BEING_ACTIVE,
	ERR_ZHAOXIAN_FAIL,
	ERR_FIRST_COST_Q,
	ERR_TREASON_KINGDOM,
	ERR_TEAM_DUNGEON_FAIL,
	ERR_VICEGENERAL_UPGRADE,
	ERR_MOUNT_UPGRADE,
	ERR_POST_UP,
	ERR_ACTIVITY_DATA_EMPTY,
	ERR_DUNGEON_TIME_OUT,
	ERR_EXACTVITY_HSAGET,
	ERR_FAMILY_ACTIVITY_SUCCESS,
	ERR_FAMILY_NOT_LEVEL,
	ERR_FAMILY_NOT,
	ERR_MOUNT_XISUI,
	ERR_VICEGENERAL_GENGU,
	ERR_GET_SEVEN_LOGIN,
	ERR_DUNGEON_COMMON = 10106,//未通关普通副本，对应魔化副本不能进入
	ERR_READ_STRATEGICS_FAIL = 10107,//兵法阅读失败
};

enum ExActivityCode
{
	EXACTIVITY_MIN =0,
	EXACTIVITY_CHARGE,//充值活动
	EXACTIVITY_YUANBAOUSE, //消费元宝
	EXACTIVITY_IET_XINGYUNQUAN,//七王秘匙
	EXACTIVITY_IET_SUPER_XINGYUNQUAN, //阿房遗宝
	EXACTIVITY_IET_MOJIAYAOSHI, //墨家宝库
	EXACTIVITY_VIP,//名将等级活动
	EXACTIVITY_SAVEDB_REALTIME = 25,
	EXACTIVITY_XISUIDAN,//下次加入新的活动的时候如果是需要及时写入数据库的则放到XISUIDAN之前
	EXACTIVITY_GENGUDAN,
	EXACTIVITY_XIUWEIDAN,
	EXACTIVITY_VICEGERNERALJINJIEDAN,
	EXACTIVITY_ZUOJIJINJIEDAN,
	EXACTIVITY_BINGFA,
	EXACTIVITY_END,
	EXACTIVITY_MAX =50,
	MOUNT_UPGRADE,
	VICEGERNERAL_UPGRADE,
	EQUIP_ENHENCE,
};

enum FamilyWarEvent
{
	FWE_ATTACK = 1,
	FWE_DEFENSE = 2,
};

enum MoneyCostType
{
	MCT_EQUIP_ENHANCE = 1,//装备强化
};

enum LogoutReason
{
	LR_DISCONNECT = 1,
	LR_KICK_SELF = 2,
	LR_SWITCH_LINE = 3,
	LR_KICK_BY_GM = 4,
	LR_SAVE_INTERVAL = 5,
};

enum updateFamilyInfoReason
{
	UFIR_NONE,
	UFIR_CREATE,
	UFIR_LEAVE,
	UFIR_JOIN,
};

enum ChatChannel
{
	CC_WORLD = 1,
	CC_KINGDOM = 2,
	CC_FAMILY = 3,
	CC_TEAM = 4,
	CC_AREA = 5,
	CC_COLOR_WORLD = 6,
};

enum TaskType /*10开始为支线任务*/
{
	TT_TRUNK	= 1,	// 主线任务
	TT_CYCLE	= 3,	// 循环任务
	TT_FAMILY	= 37,	// 军团任务
};

enum TaskCondition
{
	TC_RECEIVE				= 1,		//对话
	TC_ITEM					= 2,		//需要物品
	TC_USE_ITEM				= 3,		//使用物品
	TC_MONSTER_ID			= 4,		//杀死指定怪物
	TC_MONSTER_LEVEL		= 5,		//杀死指定等级怪物					
	TC_PLAYER_LEVEL			= 6,		//等级达到

	TC_PET_ILLUSION			= 7,		//宠物幻化
	TC_UP_EQUIP_STAR		= 8,		//装备强化
	TC_UP_EQUIP_GRADE		= 9,		//装备升级
	TC_UP_EQUIP_QUALITY		= 10,		//装备提品
	TC_FINISH_TASK_TYPE		= 11,		//完成指定类型任务
	TC_PROTECT_BY_CLIENT	= 12,		//客户端任务
	TC_PLANT				= 13,		//采集次数	
	TC_DUNGEON				= 14,		//完成副本
	TC_USER_SKILL			= 16,		//使用指定技能
	TC_HALL_OF_FAME			= 17,		//完成指定次数的名人堂
	TC_DRESS_EQUIP			= 18,		//穿戴几件几级的装备
	TC_EQUIP_STAR_COUNT		= 19,		//强化xx级xx件
	TC_PET_POINTS_COUNT		= 20,		//拥有几个几星的宠物
	TC_KILL_BOSS_COUNT		= 21,		//杀死boss
};

enum AchievementType
{
	AT_TEAM						= 1,	//组队
	AT_FRIEND					= 2,	//好友
	AT_FAMILY					= 3,	//军团
	AT_EQUIP_UP_STAR			= 4,	//强化装备
	AT_PET_ILLUSION				= 5,	//宠物幻化
	AT_LOGIN					= 6,	//登陆
	AT_LEVEL					= 7,	//等级
	AT_THREE_PET				= 8,	//三宠
	AT_PET_POINTS_COUNT			= 9,	//拥有几个几星宠物
	AT_PET_KNIGHT				= 10,	//宠物任命
	AT_DRESS_EQUIP				= 11,	//穿戴几件几级的装备
	AT_KILL_MONSTER_BY_MID		= 12,	//杀指定怪
	AT_KILL_BOSS				= 13,	//杀boss
	AT_KILL_MONSSTER			= 14,	//杀怪
	AT_DUNGEON					= 15,	//完成副本
	AT_GUAN_WEI					= 16,	//阶
	AT_FA_BAO					= 17,	//法宝
	AT_INSID_PET_POINTS			= 18,	//内置宠物总评分
	AT_WU_LING_POINTS			= 19,	//武灵评分
	AT_HUAN_LING_POINTS			= 20,	//幻灵评分
	AT_LUCK_POINTS				= 21,	//幸运值
	AT_ACTIVITY					= 22,	//参加活动
	AT_QI_FU_EXP				= 23,	//祈福经验
	AT_QI_FU_MONEY				= 24,	//祈福金币
	AT_CHOU_JIANG				= 25,	//抽奖
	AT_JUE_WEI					= 26,	//爵位
	AT_HALL_FAME				= 27,	//挑战次数			
};

#define WU_LING_RATE	100

// 任务状态
enum TaskState
{
	TS_UNKNOWN		= 0,
	TS_UNRECEIVABLE	= 1,		// 不可接
	TS_CAN_RECEIVE	= 2,		// 可接
	TS_DOING		= 3,		// 进行中
	TS_CAN_SUBMIT	= 4,		// 可完成
	TS_SUBMITED		= 5,		// 已提交
};

enum DungeonType
{
	DT_TASK			= 1,		// 主线副本
	DT_ACHIEVEMENT	= 5,		// 成就副本
	DT_EQUIP		= 11,		// 装备副本
	DT_TEAM			= 12,		// 组队副本
	DT_BOSS			= 13,		// boss副本
	DT_VIP			= 14,		// VIP副本 守护
	DT_TD			= 15,		// 经验副本 塔防
	DT_UP_TOWER		= 16,		// 爬塔副本
	DT_MY_WORLD		= 17,		// 魔域世界副本
	DT_MLRQ			= 18,		// 魔灵入侵
	DT_MONEY		= 19,		// 金钱副本 满XP
	DT_PET			= 20,		// 幻兽副本
};

enum ITEM_CLASS
{
	IC_NORMAL	= 1,		// 普通道具
	IC_EQUIP	= 2,		// 装备
	IC_GEM		= 3,		// 宝石
	IC_CURRENCY = 4,		// 货币
	IC_PET_EGG	= 5,		// 幻兽蛋
	IC_PET		= 6,		// 宠物			
};

enum CURRENCY_ITEM_ID
{
	CURRENCY_MONEY_ID			= 1,		// 铜钱
	CURRENCY_GOLD_ID			= 2,		// 元宝
	CURRENCY_CASH_ID			= 3,		// 绑元
	CURRENCY_VIGOUR_ID			= 4,		// 元气
	CURRENCY_HORNOR_ID			= 5,		// 荣誉
};

enum ItemQuality
{
	IQ_WHITE	= 1,	// 普通
	IQ_GREEN	= 2,	// 良品
	IQ_BLUE		= 3,	// 上品
	IQ_PURPLE	= 4,	// 精品
	IQ_GOLD		= 5,	// 极品
};

// 技能
enum SKILL_ATTACK_TYPE
{
	SAT_PATTACK = 1,
	SAT_MATTACK = 2,
};

enum SKILL_TYPE
{
	SK_ACTIVE	= 1,
	SK_PASSIVE	= 2,
};

enum SKILL_KIND
{
	SK_NORMAL		= 1,	// 普通技能
	SK_XP			= 2,	// XP技能
	SK_PUSH			= 3,	// 推人技能
	SK_HORSERACING	= 4,	// 赛马技能
};

enum SKILL_RANGE
{
	SR_SELF			= 0,	// 自身
	SR_SOLO			= 1,	// 单体
	SR_LINE			= 2,	// 直线
	SR_AROUND		= 3,	// 圆形
	SR_HALF_ROUND	= 4,	// 半圆

	SR_TEAM			= 10,	// 小队
};

enum SKILL_TARGET_POS
{
	STP_TARGET	= 0,	// 目标单位
	STP_SELF	= 1,	// 自己
	STP_POS		= 2,	// 目标位置
};


enum KingdomId
{
	KI_SHU	=1,
	KI_WU =2,
	KI_NEUTRAL = 3,			//中立
	KI_HOME = 99,
};

enum RankType
{
	RT_MIN = 0,
	RT_LEVEL = 1,
	RT_FIGHT_POWER = 2,
	RT_WEALTH = 3,
	RT_SHENGWANG = 4,
	//5原来是坐骑
	RT_SINGLE_CONTEST = 6,
	RT_FAMILY_CONTEST = 7,
	RT_LACKEY_LEVEL = 8,
	RT_ENHANCE_LEVEL = 9,
	RT_TOTAL_FIGHT_POWER = 10,
	RT_VICEGENERAL_FIGHT = 11,
	RT_MAX,
};

enum RealTimeRankType
{
	RTRT_LEVEL = 1,
	RTRT_FIGHT_POWER = 2,
};

enum GameMailType
{
	GMT_PLAYER = 1,
	GMT_FAMILY = 2,
};

enum AcOutdoorCaveType
{
	AOCT_RECORD =1,
	AOCT_ITEM =2,
};

enum YellowType
{
	YELLOW_DAILY = 1,//黄钻每日礼包
	YELLOW_YEAR = 2,//年费黄钻额外每日礼包
	YELLOW_GROW_UP = 3,//黄钻成长礼包
	YELLOW_NEW = 4,//黄钻新手礼包
};


#define N_MAX_IN_RECEIVE_BLESS 30//the max number in receive list
#define GOLD_COST_SUPER_BLESS 5//the gold cost for super bless

#define MAX_GM_ANNOUNCEMENT 606
// GM公告
struct GmtAnnouncement 
{
	int32_t id;
	int32_t type;
	char content[MAX_GM_ANNOUNCEMENT];
	int32_t begin_time;
	int32_t end_time;
	int32_t interval;
	int32_t enable;

	int32_t last_action_time;
};
typedef std::map<int32_t, GmtAnnouncement> GmtAnnouncementTable;
struct GmtBanChat 
{
	int32_t uid;
	int32_t expire_time;
};
typedef std::map<int32_t, GmtBanChat> GmtBanChatTable;

#define MAX_NAME_LENGTH 8
#define MAX_NAME_CCH_LENGTH 30
#define MAX_EQUIP_NAME_LENGTH 60
#define MAX_ENTRUST_LENGTH  128
#define MAX_FAMILT_POST 100
#define MAX_CODE_LENGTH 20
#define MAX_OPEN_ID_LENGTH 36
#define MAX_PF_LENGTH  20
#define MAX_IP_LENGTH  16
#define MAX_IDENTITYCARD_LENGTH 18
#define MAX_ADVANCEDTRIALS_LENGTH  1000

#define SEX_MALE 1
#define SEX_FEMALE 2

#define MIN_STYLE_ID 1
#define MAX_STYLE_ID 2

#define MIN_HEAD_ID 1
#define MAX_HEAD_ID 10

#define MAX_CHARACTER_NUM 1

struct LogArtifactAddExp
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t itemid;
	int32_t baseid;
	int32_t old_exp;
	int32_t old_level;
	int32_t new_exp;
	int32_t new_level;
	int32_t stone_id;
	int32_t stone_count;
	int32_t time;
};

struct LogArtifactAddMaxLevel
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t itemid;
	int32_t baseid;
	int32_t old_max_level;
	int32_t new_max_level;
	int32_t stone_id;
	int32_t stone_count;
	int32_t time;
};

struct LogTask
{
	CharId_t cid;
	int32_t tid;
	int32_t type;
	int32_t state;
	int32_t time;
};

struct LogEquipEnhance
{
	CharId_t cid;
    char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t equip_id;
	int32_t base_id;
	int32_t equip_quality;
	int32_t old_level;
	int32_t new_level;
	int32_t money_cost;
	int32_t sys_gold_cost;
	int32_t gold_cost;
	int32_t time;    
};

struct LogEquipAddGem
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	char equip_name[MAX_EQUIP_NAME_LENGTH+1];
	int32_t equip_quality;
	char gem_name[MAX_NAME_CCH_LENGTH+1];
	int32_t gem_level;
	int32_t time;
};

struct LogItemCombine
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t old_item_id;
	int32_t old_item_num;
	int32_t new_item_id;
	int32_t new_item_num;
	int32_t money_cost;
	int32_t sys_gold_cost;
	int32_t gold_cost;
	int32_t time;
};

struct LogEquipSmithing
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	CharId_t equip_id;
	int32_t old_base_id;
	int32_t new_base_id;
	int32_t equip_quality;
	int32_t blueprint_id;
	int32_t blueprint_quality;
	int32_t time;
};

struct LogEquipDismantle//装备拆除
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH + 1];
	CharId_t equip_id;
	int32_t base;
	int32_t enhance;
	int32_t item1_id;
	int32_t item1_count;
	int32_t item2_id;
	int32_t item2_count;
	int32_t item3_id;
	int32_t item3_count;
	int32_t item4_id;
	int32_t item4_count;
	int32_t time;
};

struct LogDungeon
{
	CharId_t cid;			// 玩家ID
	int32_t	did;			// 副本ID
	int32_t type;			// 副本类型
	int32_t level;			// 玩家等级
	int32_t state;			// 状态 0 未完成 1 完成 2 中途退出
	int32_t start_time;		// 开启时间
	int32_t	finish_time;	// 完成时间
};

struct LogBoss
{
	int32_t	mid;			// 怪物ID
	int32_t	type;			// boss类型
	CharId_t killer;		// 击杀者
	int32_t	time;			// 击杀时间
};

struct LogActivity
{
	CharId_t cid;			// 玩家ID
	int32_t	actid;			// 活动ID
	int32_t	acttype;		// 活动类型
	int32_t	time;			// 进入时间
	int64_t param;			// 参数
};

enum DAILY_GIFT_TYPE
{
	DGT_SHOU_CHONG	= 1,	// 每日首冲
};

struct LogDailyGift
{
	CharId_t cid;			// 玩家ID
	int32_t	type;			// 礼包类型
	int32_t	giftid;			// 礼包id
	int32_t	time;			// 进入时间
};

struct LogFamily
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	char family_name[MAX_NAME_CCH_LENGTH+1];
	int32_t time;
};

struct LogOnlineReward
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t  num;
	int32_t  time;
	int32_t  type;
};

struct LogAchievement
{
	CharId_t  cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t  id;
	int32_t  index;
	int32_t  type;
	int32_t  time;
};

struct LogLevelGift
{
	CharId_t  cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t type;
	int32_t time;
};

#define ITEM_CHANGE_LOG_ADD			1
#define ITEM_CHANGE_LOG_REMOVE		2
#define ITEM_CHANGE_LOG_UPDATE		3
struct LogItemChange
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int8_t	flag;
	int32_t reason;
	int32_t id;
	int8_t	itemClass;
	int32_t count;
	int32_t time;
	int64_t srcId;
};
typedef std::list<LogItemChange> LogItemChangeList;

struct LogArtifactAddQuality 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	int32_t itemid;
	int32_t baseid;
	int32_t old_quality;
	int32_t new_quality;
	int32_t stone_id;
	int32_t time;
};


struct LogEquipAddGemSlot 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t old_gem_slot_num;
	int32_t new_gem_slot_num;
	int32_t stone_id;
	int32_t time;
};

struct LogEquipAppendStar 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t level;
	int32_t fuxing_stone_id;
	int32_t time;
};

struct LogEquipCombine 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t new_baseid;
	int32_t side_equip_1;
	int32_t side_equip_2;
	int32_t side_equip_3;
	int32_t side_equip_4;
	int32_t shouhu_stone_id;
	int32_t money;
	int32_t time;
};

struct LogEquipForge 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t item_id;
	int32_t money;
	int32_t time;
};

struct LogEquipLife
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t type;
	int32_t reason;
	int32_t time;
};


struct LogEquipRemoveGem
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t slot_index;
	int32_t stone_id;
	int32_t time;
};

struct LogEquipRemoveStar 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t level;
	int32_t fuxing_stone_id;
	int32_t shouhu_stone_id;
	int32_t time;
};

struct LogEquipRefreshBind
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t old_bind;
	int32_t new_bind;
	int32_t stone_id;
	int32_t time;
};

struct LogEquipRefreshElement
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t old_element;
	int32_t new_element;
	int32_t stone_id;
	int32_t time;
};

struct LogEquipRefreshFloatAttr 
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t old_float_attr;
	int32_t new_float_attr;
	int32_t stone_id;
	int32_t time;
};

struct LogEquipStrengthen //强化装备
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t old_strength;
	int32_t new_strength;
	int32_t stone_id;
	int32_t stone_count;
	int32_t time;
};

struct LogEquipUpgrade
{
	CharId_t cid;
	char name[MAX_NAME_CCH_LENGTH+1];
	EquipId_t eid;
	int32_t baseid;
	int32_t new_baseid;
	int32_t upgrade_stone_id;
	int32_t upgrade_stone_count;
	int32_t crystal_stone_id;
	int32_t zhenxing_stone_id;
	int32_t money;
	int32_t time;
};

enum AuctionState
{
	AS_IN_SELL,
	AS_SELLED,
	AS_SYS_LOCK,
};

struct MemCharacter 
{
	CharId_t cid;									// 角色ID
	char	name[MAX_NAME_CCH_LENGTH+1];			// 角色名称
	char	familyName[MAX_NAME_CCH_LENGTH+1];		// 帮派名称
	Sex_t	sex;									// 性别
	Job_t	job;									// 职业
	int32_t level;									// 等级
	int32_t battle;									// 战斗力
	int64_t exp;									// 经验值
	int64_t exp_minus;
	int32_t	vip;									// vip使用过的卡
	int32_t vip_end_time;							// vip到期时间
	int32_t mapid;									// 所在地图ID
	int32_t x;										// 所在地图坐标X
	int32_t y;										// 所在地图坐标Y
	int32_t hp;										// 当前血量
	int32_t mp;										// 当前法力值
	int32_t pp;										// 当前体力值
	int32_t xp;										// 当前XP值
	int32_t level_gift;								// 等级礼包
	int32_t level_gold;
	int32_t seven_login;							// 七日登陆
	int32_t head;
	int32_t pk_mode;								// pk模式
	int32_t pk_value;								// pk值
	int32_t pk_killed_count;
	int32_t pk_time;
	int32_t kill_count;

	int32_t bag_open_time;							// 背包开启时间
	int32_t bag_open_slot;							// 背包当前开启的格数
	int32_t bag_can_open;							// 当前等够开启的最大格数
	int32_t last_task_id;							// 上一个主线任务ID
	int32_t logout_count;							// 登出时间
	int32_t pay_click_count;
	int32_t level_stay_time;
	int32_t last_login_time;
	int32_t last_logout_time;
	int32_t create_time;
	int32_t leader;
};

#define ACTION_NUMBER 13 //action 0 for invalid check, max 12 actions

struct MemPvp
{
	int32_t time;
	int32_t count;
	int32_t mode;
};

struct MemAchievement
{
	  int32_t kill_player_count;
};

struct MemAttr
{
	int32_t hp;						// 最大血量
	int32_t mp;						// 最大血量
	int32_t pp;						// 最大血量
	int32_t xp;						// 最大血量
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
	int32_t battle;					// 战斗力
	int32_t lucky;					// 幸运值
};

struct MemChrAction 
{
	int32_t id;
	int32_t type;
};

#define MAX_GOLD_FIND_CCH_LENGTH 100

#define MAX_AUTO_FIGHT_CCH_LENGTH 300
#define MAX_AUTO_PICK_CCH_LENGTH 600

struct MemChrAutoFight 
{
	char fight[MAX_AUTO_FIGHT_CCH_LENGTH+1];
	char pick[MAX_AUTO_PICK_CCH_LENGTH+1];
};

enum CHAR_BAG_TYPE
{
	CBT_EQUIP	= 0,	// 装备栏
	CBT_BAG		= 1,	// 背包
	CBT_DEPORT	= 2,	// 仓库
	CBT_CHOUJIANG = 3,	// 抽奖背包
};
#define MAX_BAG_SLOT_NUM	150			//背包最大数
#define FREE_BAG_SLOT_NUM	40			//背包初始化大小

#define FREE_DEPOT_SLOT 40				//仓库初始化大小
#define MAX_DEPOT_SLOT 150				//仓库最大数

#define MAX_SELL_ITEM_COUNT 15
#define STONE_COMBINE_NUM 10
#define MAX_EQUIP_LEVEL 120
#define EQUIP_NAMESUITE_NUM 6
#define MAX_GEM_LEVEL  9

struct ChrBagInfo 
{
	int32_t	m_nLastOpenTime;
	int32_t m_nLeftSeconds;
	int32_t m_nCanOpenSlots;
	int32_t m_nOpenedSlots;
};

struct MemChrBag 
{
	int32_t itemId;		// 道具ID（配置表中的ID）
	int8_t	itemClass;	// 道具类型
	int32_t itemCount;	// 道具数量
	int8_t	bind;		// 绑定类型
	Time_t	endTime;	// 过期时间
	int64_t	srcId;		// 关联ID（装备ID...）
};
typedef std::vector<MemChrBag> MemChrBagVector;
typedef std::map<int32_t,MemChrBagVector> MemChrBagVectorTable;
typedef std::map<int32_t,MemChrBag> MemBagTable;

struct MemChrClothesBag
{
	int32_t id;				//时装id
	int32_t type;			//类别
	int32_t job;			//职业
	int32_t base;			//基础id
};
typedef std::vector<MemChrClothesBag> MemChrClothesBagVector;
typedef std::map<int32_t,MemChrClothesBag>MemChrClothesBagTable;

struct MemDungeonGift
{
	int32_t index;
	MemChrBagVector  items;
};

struct MemChrJobBag
{
	Job_t  job;
	int32_t  id;
	int32_t  type;
	int32_t  bind;
	int32_t  count;
};
typedef std::vector<MemChrJobBag> MemChrJobBagVector;

struct MemChrBuff 
{
	int32_t id;
	int32_t time;
};
typedef std::vector<MemChrBuff> MemChrBuffVector;

// 签到
class MemChrSignInfo
{
public:
	MemChrSignInfo()
	{
		CleanUp();
	}
	void CleanUp()
	{
		sign_record		= 0;
		refresh_time	= 0;
		sign_reward.clear();
	}
	int32_t				sign_record;
	std::vector<int8_t>	sign_reward;
	int32_t				refresh_time;		//上一次签到
};

enum PlayerBornAttr
{
	PBA_STR = 0,
	PBA_WIS = 0,
	PDA_MAG = 0,
	PBA_VIT = 0,
	PBA_MEN = 0,
	PBA_AGI = 0,
	PBA_PATTACK = 11,
	PBA_MATTACK = 11,
	PBA_PDEF = 1,
	PBA_MDEF = 1,
	PBA_MAXHP = 560,
	PBA_MAXMP = 200,
	PBA_VP = 0,
	PBA_DP = 0,
	PBA_HTIP = 300,
	PBA_SP = 150,
	PBA_PREVP = 0,
	PBA_PREFORST = 0,
	PBA_PREBK = 0,
	PBA_MAXANGRY = 1000,
	PBA_REGION = 10002,
	PBA_BENGIN_REGION = 10004,
	PBA_CENTER_CITY = 20002,
	PBA_FAMILY_MAP = 20026,
};

enum PlayerJob
{
	PJ_ZHANSHI		= 1,		// 战士
	PJ_FASHI		= 2,		// 法师
	PJ_LONGQI		= 3,		// 龙骑
	PJ_JOB_COUNT,
};

enum PetJob
{
	PET_JOB_ZHANSHI		= 1,		// 战士
	PET_JOB_FASHI		= 2,		// 法师
};

enum SkillJob
{
	SJ_ZHANSHI = 1,
	SJ_GONGSHOU = 2,
	SJ_MOUSHI = 3,
	SJ_MOKE = 4,
	SJ_NUQI = 10,
};

enum EQUIP_TYPE
{
	ET_WEAPON			= 0,		// 武器
	ET_NECK				= 1,		// 项链
	ET_HAND				= 2,		// 手镯
	ET_CLOSE			= 3,		// 衣服
	ET_HEAD				= 4,		// 头盔
	ET_SHOES			= 5,		// 靴子
	ET_BELT				= 6,		// 腰带
	ET_RING				= 7,		// 戒指
	ET_XUNZHANG			= 8,		// 勋章
};


enum EquipSlot
{
	EQUIP_SLOT_WEAPON			= 0,		// 武器
	EQUIP_SLOT_NECK				= 1,		// 项链
	EQUIP_SLOT_HAND				= 2,		// 手镯
	EQUIP_SLOT_CLOTH			= 3,		// 衣服
	EQUIP_SLOT_HEAD				= 4,		// 头盔
	EQUIP_SLOT_SHOES			= 5,		// 靴子
	EQUIP_SLOT_BELT				= 6,		// 腰带
	EQUIP_SLOT_RING				= 7,		// 戒指
	EQUIP_SLOT_XUNZHANG			= 8,		// 勋章
	EQUIP_SLOT_TOTAL_NUM,					// 装备总栏大小
};

enum NEW_GEM_TYPE
{
	GEM_TYPE_BATTLE 	= 1,	//战斗力宝石
	GEM_TYPE_DAMMAGE    = 2,	//减伤宝石
	GEM_TYPE_EXP		= 3,	//经验宝石
	GEM_TYPE_ATTACK		= 4,	//伤害宝石
};

enum GEM_TYPE
{
	GEM_TYPE_RED	= 1,	// 红宝石
	GEM_TYPE_GREEN	= 2,	// 绿宝石
	GEM_TYPE_BLUE	= 3,	// 蓝宝石
};

enum GEM_SLOT
{
	GEM_SLOT_RED	= 0,	// 红宝石插槽
	GEM_SLOT_GREEN,			// 绿宝石插槽
	GEM_SLOT_BLUE,			// 蓝宝石插槽
	GEM_SLOT_NUM,
};

enum CHRINFO
{
	CHR_HONORID,
	CHR_HONORIDKINGDOM,
};
enum PlayerInfoIndex
{
	PII_JOB,
	PII_LEVEL,
	PII_LAST_LOGOUT_TIME,
	PII_VIP,
	PII_VIP_LEVEL,
	PII_LEARN_XP_SKILL,
	PII_BATTLE,
	PII_JUE_WEI,
	PII_WEAPON,
	PII_CLOTH,
	PII_GUAN_WEI,
};

struct MemChrEquip // 废弃
{
	int32_t eid;
	int32_t bind;
	int32_t expire;
};

struct MemJobItem
{
	int32_t job;
	int32_t item;
};
typedef std::map<int32_t,MemJobItem>MemJobItemTable;

struct MemChrRelation 
{
	int32_t tcid;
	int32_t type;
};
typedef std::vector<MemChrRelation> MemChrRelationVector;

struct MemChrSkill 
{
	int32_t id;
	int32_t level;
	int64_t last_action_tick;
};
typedef std::vector<MemChrSkill> MemChrSkillVector;

#define MAX_SYSTEM_SETTING_CCH_LENGTH 300

struct MemChrSystemSetting 
{
	char setting[MAX_SYSTEM_SETTING_CCH_LENGTH+1];
};

struct MemChrTask 
{
	int32_t id;
	int32_t state;
	int32_t monster;
};
typedef std::vector<MemChrTask> MemChrTaskVector;

#define EQUIP_GEM_COUNT 3
class MemEquip 
{
public:
	MemEquip() { CleanUp(); }
	~MemEquip(){}
	void CleanUp()
	{
		id				= 0;
		nFlag			= 0;
		base			= 0;
		owner			= 0;
		star			= 0;			
		starLucky		= 0;		
		UpGradeLucky	= 0;	
		UpQuality		= 0;		
		addAttr			= 0;
		memset( GemHole, -1, sizeof( GemHole ) );
	}
	void ParesEquipString( std::string EquipGemString )
	{
		if ( EquipGemString.empty() )
		{
			return;
		}
		StringVector ItemVector = Answer::StringUtility::split( EquipGemString, ":");
		if ( ItemVector.size() == EQUIP_GEM_COUNT )
		{
			for ( int32_t i = 0; i < EQUIP_GEM_COUNT; ++i )
			{
				GemHole[i]	= atoi(ItemVector[i].c_str());
			}
		}
	}
	std::string GetEquipGemString() const
	{
		std::stringstream ss;
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; ++i )
		{
			ss << static_cast<int32_t>( GemHole[i]);
			ss << ":";
		}
		return ss.str();
	}
	int32_t GetGemSlotCount() const
	{
		int32_t nCount = 0;
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; ++i )
		{
			if ( 0 == GemHole[i] )
			{
				++nCount;
			}
		}
		return nCount;
	}

	EquipId_t	id;
	int32_t		nFlag;			// 更新标记
	ItemId_t	base;
	CharId_t	owner;
	int32_t		star;			// 星级
	int32_t		starLucky;		// 升星幸运值
	int32_t		UpGradeLucky;	// 升级幸运值
	int32_t		UpQuality;		// 升品幸运值
	int32_t		GemHole[EQUIP_GEM_COUNT];	// 宝石孔
	int32_t		addAttr;		// 附加属性类型
};
typedef std::vector<MemEquip> MemEquipVector;
typedef std::map<EquipId_t, MemEquip> MemEquipTable;

struct MemYellowStone
{
	CharId_t cid;
	int32_t id; //cfg_yellow_stone  id
	int32_t get_time;
};
typedef std::vector<MemYellowStone> MemYellowStoneVector;

struct MemItemArtifact 
{
	int32_t id;
	int32_t base;
	int32_t owner;
	int32_t bind;
	int32_t expire;
	int32_t level;
	int32_t max_level;
	int32_t exp;
	int32_t quality;
};

struct SysUser 
{
	int32_t uid;
	int32_t sid;
	int32_t gold;
	int32_t sys_gold;
	int32_t gold_pay_total;
	int32_t prepay_gold;
	int32_t gold_cost_total;
	int32_t cash;
	int32_t map_enter_time;
	int32_t last_login_time;
	int32_t adult;
	int32_t type;
	int32_t total_login_count;
	int32_t continue_login_count;
	int32_t last_logout_time;
	int32_t total_online_time;
	int32_t total_offline_time;
	char IP[MAX_IP_LENGTH+1];
};

//防沉迷验证
struct SysUserPreventWallow
{
	int32_t uid;
	int32_t sid;
	char    name[MAX_NAME_CCH_LENGTH+1]; //姓名
	char    identitycard[MAX_IDENTITYCARD_LENGTH + 1]; //身份证号码
	int32_t isGrowUp; //是否成年人
};

#define  MAX_IDENTITYCARD_LENGTH 18

enum NewServerActivityType
{
	NSAT_VIP = 1,
	NSAT_FIGHT_POWER_RANK = 2,
	NSAT_LEVEL_RANK = 3,
	NSAT_JISHUJIUGONG = 4,
	NSAT_MOUNT_FIGHT_POWER_RANK = 5,
	NSAT_EQUIP = 6,
	NSAT_GEM = 7,
	NSAT_LEVEL_UP_TO = 8,
	NSAT_FIGHT_POWER_UP_TO = 9,
	NSAT_POINT = 10,
	NSAT_VICEGENERAL = 11,
	NSAT_GOLD_COST = 12,
};

struct OperateLimit
{
	int32_t	LimitId;
	int32_t	LimitCount;
	bool	IsChaned;
};
typedef map<int32_t, OperateLimit> OperateLimitMap;

// 绑定状态
enum ITEM_BIND_STATE
{
	IBS_UNBIND	= 0,
	IBS_BIND	= 1,
};

struct ItemData
{
	int32_t	m_nId;
	int8_t	m_nClass;
	int32_t	m_nCount;
};
typedef std::list<ItemData> ItemDataList;

struct CfgAddAttr
{
	int32_t	m_nAttr;
	int32_t	m_nValue;
	int32_t	m_nRate;
};
typedef std::list<CfgAddAttr> CfgAddAttrList;

struct CfgSuitAttr
{
	int32_t	m_nCount;
	int32_t	m_nAttr;
	int32_t m_nValue;
};
typedef std::list<CfgSuitAttr> CfgSuitAttrList;

// 货币
enum CURRENCY_TYPE
{
	CURRENCY_INVALID		= -1,
	CURRENCY_MONEY			= 0,		// 铜钱
	CURRENCY_GOLD			= 1,		// 元宝
	CURRENCY_CASH			= 2,		// 绑元
	CURRENCY_VIGOUR			= 3,		// 元气
	CURRENCY_CHOUJINAG		= 4,		// 抽奖积分
	CURRENCY_BOSS			= 5,		// BOSS积分
	CURRENCY_BIND_MONEY		= 6,		// 绑定金币
	CURRENCY_HONOR			= 7,		// 荣誉
	CURRENCY_AC_SOCRE		= 8,		// 积分
	CURRENCY_TYPE_COUNT,
};

inline CURRENCY_TYPE TranseCurrency( CURRENCY_ITEM_ID id )
{
	switch( id )
	{
	case CURRENCY_MONEY_ID:		return CURRENCY_MONEY;
	case CURRENCY_GOLD_ID:		return CURRENCY_GOLD;
	case CURRENCY_CASH_ID:		return CURRENCY_CASH;
	case CURRENCY_VIGOUR_ID:	return CURRENCY_VIGOUR;
	default:	break;
	}
	return CURRENCY_INVALID;
}

struct KillMonsterInfo
{
	int32_t		m_MonsterMid;		
	int32_t		m_KillCount;		
	int8_t		m_BossSign;		
};
typedef std::map<int32_t,KillMonsterInfo> KillMonsterMap;

class ExpReward
{
public:
	ExpReward()
	{
		FriendId	= 0;
		GetExp		= 0;
		Name		= "";
		Level		= 0;
	}
	CharId_t	FriendId;
	int32_t		GetExp;
	std::string Name;
	int32_t		Level;
};
typedef std::map<CharId_t,ExpReward> FriendExpMap;


 class DropEquipInfo
{
public:
	DropEquipInfo()
	{
		CharId				= 0;
		CharName			= "";
		KillerId			= 0;	
		KillerName			= "";
		CanGetLastTime		= 0; 
		itemId				= 0;			
		itemClass			= 0;		
		itemCount			= 0;		
		bind				= 0;			
		endTime				= 0;		
		srcId				= 0;
		Mid					= 0;
	}
	CharId_t			CharId;
	std::string			CharName;
	CharId_t			KillerId;	
	std::string			KillerName;
	Time_t				CanGetLastTime; // 可赎回的最后时间				
	int32_t				itemId;			// 道具ID（配置表中的ID）
	int8_t				itemClass;		// 道具类型
	int32_t				itemCount;		// 道具数量
	int8_t				bind;			// 绑定类型
	Time_t				endTime;		// 过期时间
	int64_t				srcId;			// 关联ID（装备ID...）
	int32_t				Mid;			// 如果是被怪物杀死
};
 typedef std::list<DropEquipInfo> RANSOM_ITEM_LIST;

 enum UPDATE_TYPE
 {
	 ADD_RANSOM		= 1,
	 SUB_RANSOM		= 2,
 };

#define EQUIP_RANSOM_TIME 7*24*60*60	//装备赎回时间
#define EQUIP_MAX_STAT  12 //装备最大星数

#define PET_RANK_OPEN_LEVEL	60		// 宠物进入排行榜需求等级
#define MAX_PET_ID			100		// 最大幻兽ID
#define PET_SKILL_COUNT		10		// 宠物技能数
#define PET_SKILL_BAR_SIZE	6		// 宠物技能栏大小 
enum PET_ATTR
{
	PET_ATTR_START_HP					= 0,			// 初始生命：		初始生命为幻兽1级时的生命值。（数值范围1~9999999）
	PET_ATTR_START_PHY_ATK_MIN			= 1,			// 初始最小攻击：	初始攻击为幻兽1级时的物理攻击值。（数值范围1~9999999）
	PET_ATTR_START_PHY_ATK_MAX			= 2,			// 初始最大攻击：	初始攻击为幻兽1级时的物理攻击值。（数值范围1~9999999）
	PET_ATTR_START_PHY_DEF				= 3,			// 初始防御：		初始防御为幻兽1级时的物理防御值。（数值范围1~9999999）
	PET_ATTR_START_MAG_ATK_MIN			= 4,			// 初始最小魔攻：	初始魔攻为幻兽1级时的魔法攻击值。（数值范围1~9999999）
	PET_ATTR_START_MAG_ATK_MAX			= 5,			// 初始最大魔攻：	初始魔攻为幻兽1级时的魔法攻击值。（数值范围1~9999999）
	PET_ATTR_START_MAG_DEF				= 6,			// 初始魔防：		初始魔防为幻兽1级时的魔法防御值。（数值范围1~9999999）
	PET_ATTR_START_DODGE				= 7,			// 初始闪避：		幻兽1级时的闪避值。（数值范围1~9999999）
	PET_ATTR_START_HITRATE				= 8,			// 初始命中：		幻兽1级时的命中值。（数值范围1~9999999）
	PET_ATTR_START_CRITRATE				= 9,			// 初始暴击：		幻兽1级时的暴击值。（数值范围1~9999999）
	PET_ATTR_START_TENACITY				= 10,			// 初始韧性：
	PET_ATTR_GROW_HP					= 11,			// 生命成长：		影响幻兽的最终生命值。（数值范围1~9999，有小数点，到后面4位）		（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_PHY_ATK_MIN			= 12,			// 最小攻击成长：	影响幻兽的最终最小攻击值。（数值范围1~9999，有小数点，到后面4位）	（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_PHY_ATK_MAX			= 13,			// 最大攻击成长：	影响幻兽的最终最大攻击值。（数值范围1~9999，有小数点，到后面4位）	（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_PHY_DEF				= 14,			// 防御成长：		影响幻兽的最终防御值。（数值范围1~9999，有小数点，到后面4位）		（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_MAG_ATK_MIN			= 15,			// 最小魔攻成长：	影响幻兽的最终最小魔攻值。（数值范围1~9999，有小数点，到后面4位）	（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_MAG_ATK_MAX			= 16,			// 最大魔攻成长：	影响幻兽的最终最大魔攻值。（数值范围1~9999，有小数点，到后面4位）	（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_MAG_DEF				= 17,			// 魔防成长：		影响幻兽的最终魔防值。（数值范围1~9999，有小数点，到后面4位）		（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_DODGE					= 18,			// 闪避成长：		影响幻兽的最终闪避值。（数值范围1~9999，有小数点，到后面4位）		（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_HITRATE				= 19,			// 命中成长：		影响幻兽的最终命中值。（数值范围1~9999，有小数点，到后面4位）		（1~99990000, 除以10000为显示值）
	PET_ATTR_GROW_CRITRATE				= 20,			// 暴击成长：		幻兽1级时的暴击值。（数值范围1~9999999）
	PET_ATTR_GROW_TENACITY				= 21,			// 初始韧性：
	PET_ATTR_COUNT,
};

enum INSIDE_PET_ID
{
	IPI_ZHANSHI	= 21,	// 战士灵兽ID
	IPI_FASHI	= 22,	// 法师灵兽
	IPI_LONGQI	= 23,	// 龙骑灵兽
};

inline int32_t GetInsidePetId( Job_t nJob )
{
	switch( nJob )
	{
	case PJ_ZHANSHI:	return IPI_ZHANSHI;		// 战士
	case PJ_FASHI:		return IPI_FASHI;		// 法师
	case PJ_LONGQI:		return IPI_LONGQI;		// 龙骑
	default:break;
	}
	return -1;
}

inline bool IsInsidePet( int32_t nPetId )
{
	return ( nPetId == IPI_ZHANSHI || nPetId == IPI_FASHI || nPetId == IPI_LONGQI );
}


// 幻兽相性
enum PET_PHASE
{
	PP_INVALID	= 0,
	PP_WIND		= 1,	// 风
	PP_WATER	= 2,	// 水
	PP_FIRE		= 3,	// 火
	PP_EARTH	= 4,	// 土
	PP_ELECTRIC	= 5,	// 雷
	PP_GOLD		= 6,	// 金

	PP_DEFAULT	= 0xFF
};

enum PET_PLACE
{
	PBT_BAG		= 0,
	PBT_DEPORT	= 1,

	PET_BAG_TYPE_SIZE,
};

enum PET_EGG_STATE
{
	PES_NORMAL		= 0,		// 正常状态
	PES_HATCHING	= 1,		// 孵化中
	PES_CAN_OPEN	= 2,		// 孵化完成
};

enum PET_FROM_WAY
{
	PFW_NORMAL		= 0,		// 一般来源
	PFW_BORN		= 1,		// 出生自带
	PFW_GIFT		= 2,		// 礼包获得
};

#define PET_BAG_SIZE					20								// 幻兽栏大小
#define PET_DEPORT_SIZE					15								// 幻兽仓库大小
#define PET_VIP_ADD_DEPORT_SIZE			30								// vip增加幻兽仓库最多的个数				
#define PET_LIST_SIZE					(PET_BAG_SIZE+PET_DEPORT_SIZE + PET_VIP_ADD_DEPORT_SIZE )	// 总大小
#define PET_EGG_BAG_SIZE				14								// 幻兽背包大小
#define PET_HATCH_POOL_SIZE				32								// 幻兽孵化池大小
#define	PET_MUTI_HATCH_POOL_SIZE		40								// 幻兽批量孵化池大小
#define PET_EGG_REHATCH_COST			3								// 幻兽重新孵化消耗元宝
#define PET_EGG_QUICK_HATCH_COST		(30*60)							// 幻兽快速孵化每30分钟消耗1元宝
#define PET_EGG_HATCH_TIME				(20*60)							// 宠物蛋孵化时间		20分钟
#define PET_EGG_MUTI_HATCH_TIME			(6*60*60)						// 宠物蛋批量孵化时间	6小时
#define PET_REIN_RATE					10								// 宠物转生次数存储值比率

// 幻兽骑士
enum PET_KNIGHT
{
	PK_NONE			= 0,		// 无
	PK_ZHIHUI		= 1,		// 智慧骑士
	PK_LEITING		= 2,		// 雷霆骑士
	PK_DOUHUN		= 3,		// 斗魂骑士
	PK_SHENGZHAN	= 4,		// 圣战骑士
	PK_GUANGHUI		= 5,		// 光辉骑士
	PK_SHOUHU		= 6,		// 守护骑士
	PK_CAIJUE		= 7,		// 裁决骑士
	PK_SHENGGUANG	= 8,		// 圣光骑士

	PET_KNIGHT_SIZE
};

enum PET_EGG_BAG_TYPE
{
	PEBT_BAG				= 1,	// 宠物蛋背包
	PEBT_HATCH_POOL			= 2,	// 宠物孵化池
	PEBT_MUTI_HATCH_POOL	= 3,	// 批量孵化池
};

enum PET_RANK_TYPE
{
	PRT_POINTS					= 0,	// 评分（总排行）
// 	PRT_START_HP				= 1,	// 初始生命：	
// 	PRT_START_PHY_ATK_MIN		= 2,	// 初始最小攻击：
// 	PRT_START_PHY_ATK_MAX		= 3,	// 初始最大攻击：
// 	PRT_START_PHY_DEF			= 4,	// 初始防御：	
// 	PRT_START_MAG_ATK_MIN		= 5,	// 初始最小魔攻：
// 	PRT_START_MAG_ATK_MAX		= 6,	// 初始最大魔攻：
// 	PRT_START_MAG_DEF			= 7,	// 初始魔防：	
	PRT_GROW_HP					= 8,	// 生命成长：	
	PRT_GROW_PHY_ATK_MIN		= 9,	// 最小攻击成长：
	PRT_GROW_PHY_ATK_MAX		= 10,	// 最大攻击成长：
	PRT_GROW_PHY_DEF			= 11,	// 防御成长：	
	PRT_GROW_MAG_ATK_MIN		= 12,	// 最小魔攻成长：
	PRT_GROW_MAG_ATK_MAX		= 13,	// 最大魔攻成长：
	PRT_GROW_MAG_DEF			= 14,	// 魔防成长：	
};

struct SocialPetData
{
	int32_t		nBaseId;
	uint32_t	nRankFlag;
	PetId_t		nPetId;
	CharId_t	nOwner;
	int32_t		nPoints;
	char		strName[MAX_NAME_CCH_LENGTH+1];
	int32_t		vAttr[PET_ATTR_COUNT];
};

struct PetRankIndex 
{
	int32_t	nPointsIndex;
	int32_t vAttrIndex[PET_ATTR_COUNT];
};

struct DBPet
{
	PetId_t		nPetId;
	int32_t		nHP;
	int8_t		bAlive;
	int32_t		nSoul;
	int8_t		nState;
	int8_t		nBag;
	int8_t		nKnight;
	int8_t		nQiShi;
	FamilyId_t	nFamilyId;
};

struct DBPetEgg 
{
	int8_t	nBag;
	int32_t	nSlot;
	int32_t	nBaseId;
	int8_t	nState;
	int32_t	nStartTime;
	PetId_t	nPetId;
};

#define MAX_TEAM_MEMBER_COUNT	4		// 组队最大人数
struct TeamMember 
{
	TeamMember( CharId_t cid, const std::string& name, int16_t idx )
		:nCharId( cid ), strName( name ), nIndex( idx )
	{

	}
	CharId_t	nCharId;
	std::string	strName;
	int16_t		nIndex;
};
typedef std::list<TeamMember> TeamMemberList;

#define MAX_XP_POINTS			210		// XP最大值
#define ADD_XP_POINTS			30		// XP每次增加值

enum XP_STATE
{
	XS_INCREACE		= 0,	// XP增长中
	XS_DO_SKILL		= 1,	// XP释放中
	XS_END			= 2,	// XP结束等待结算
	XS_BREAK		= 3,	// 未选择XP直接跳过了
	XS_OTHER_END	= 4,	// XP中途进入队伍的玩家结束XP了
	XS_STOP			= 5,	// 在队伍中死亡,这一轮停止增长xp
};

#define CREATE_FAMILY_COST_GOLD		100	// 创建帮派需要100元宝
#define FAMILY_APPLY_COUNT			50

struct FamilyInfo 
{
	FamilyInfo(){ CleanUp(); }
	~FamilyInfo(){}
	void CleanUp()
	{
		nId			= 0;
		nLevel		= 0;
		strName		= "";
		nAddBattle	= 0;
		FamilyTaskCount	= 0;
	}

	bool IsEmpty() const
	{
		return 0 == nId;
	}

	bool TotomIsOpened( int32_t PetBaseId )
	{
		std::set<int32_t>::iterator it = OpenedTotom.find( PetBaseId );
		if ( it != OpenedTotom.end() )
		{
			return true;
		}
		return false;
	}

	FamilyId_t			nId;
	int8_t				nLevel;
	std::string			strName;
	int32_t				nAddBattle;
	std::set<int32_t>	OpenedTotom;
	int32_t				FamilyTaskCount;
};

#define MAX_FAMILY_LEVEL			10
#define FAMILY_OPEN_LEVEL			30			// 军团开启等级
#define MAX_FAMILY_CONTRIBUTE_GOLD	100000		// 单笔捐献最大魔石 10w
#define MAX_FAMILY_CONTRIBUTE_MONEY	1000000000	// 单笔捐献最大金钱 10y
#define MAX_FAMILY_CONTRIBUTE		100000000	// 人物通过捐献能获得的最大贡献度 1
#define MAX_FAMILY_MONEY			1000000000	// 帮派最大资金 10y
#define FAMILY_TOTOM_ACTIVE_TIME	259200		// 军团加持时间 3天	3*24*60*60

struct CfgFamilyPosition 
{
	int32_t	nNeedContribution;		// 需求贡献度
	int32_t	nShareBattleRatio;		// 战斗力分享
};

enum FAMILY_UPDATE_REASON
{
	FUR_CREATE	= 1,
	FUR_UPDATE	= 2,
	FUR_DELETE	= 3,
};

// 军团职务
enum FAMILY_POSITION
{
	FP_NONE			= 0,	// 帮众
	FP_SENIOR		= 1,	// 资深
	FP_ELIT			= 2,	// 精英
	FP_SENETE		= 3,	// 议员
	FP_ELDER		= 4,	// 元老
	FP_VICE			= 5,	// 副团长
	FP_LEADER		= 6,	// 军团长
	FP_HONOR_VICE	= 7,	// 荣誉副团长
	FP_HONOR_ELDER	= 8,	// 荣誉元老
	FP_HONOR_SENETE	= 9,	// 荣誉议员

	FAMILY_POSITION_COUNT,
};

enum FAMILY_POSITION_LEVEL
{
	FPL_NONE	= 0,
	FPL_SENIOR	= 1,
	FPL_ELIT	= 2,
	FPL_SENETE	= 3,
	FPL_ELDER	= 4,
	FPL_VICE	= 5,
	FPL_LEADER	= 6,

	FAMILY_POSITION_LEVEL_COUNT,
};

inline bool IsSortPosition( int8_t nPosition )
{
	switch ( nPosition )
	{
	case FP_SENIOR:
	case FP_ELIT:
	case FP_SENETE:
	case FP_ELDER:
	case FP_VICE:
		return true;
	}
	return false;
}

inline bool IsHonorPosition( int8_t nPosition )
{
	switch ( nPosition )
	{
	case FP_HONOR_VICE:
	case FP_HONOR_ELDER:
	case FP_HONOR_SENETE:
		return true;
	}
	return false;
}

inline int8_t GetPositionLevel( int8_t nPosition )
{
	switch ( nPosition )
	{
	case FP_NONE:			return FPL_NONE;
	case FP_SENIOR:			return FPL_SENIOR;		// 资深会员
	case FP_ELIT:			return FPL_ELIT;		// 精英
	case FP_HONOR_SENETE:
	case FP_SENETE:			return FPL_SENETE;		// 议员、荣誉议员
	case FP_HONOR_ELDER:
	case FP_ELDER:			return FPL_ELDER;		// 元老、荣誉元老
	case FP_HONOR_VICE:
	case FP_VICE:			return FPL_VICE;		// 副团长、荣誉副团长
	case FP_LEADER:			return FPL_LEADER;		// 军团长
	}
	return 0;
}

inline int32_t CalPetRegistAddContribute( int32_t nPoints )
{
	return nPoints;
}

inline int32_t CalFamilyContribute( int32_t nMoney, int32_t nGold )
{
	return nMoney / 1000 + nGold * 200;
}

enum BossType
{
	BOSS_TYPE_LING_TU		= 1,	//领土boss
	BOSS_TYPE_SPIDER_QUEEN  = 2,	//蜘蛛女王
	BOSS_TYPE_WORLD_BOSS	= 3,	//世界boss
	BOSS_TYPE_BOSS_HOME		= 4,	//boss之家
};

#define MAIL_MAX_FU_JIAN_COUNT	6			//附件个数
#define MAIL_TITLE_MAX_LENGTH 30			//邮件标题长度
#define MAIL_CONTENT_MAX_LENGTH 150			//邮件内容长度
#define MAIL_MAX_KEEP_TIME	14*24*60*60		//邮件保留的时间		
struct MailInfo
{
	int32_t			MailId;
	int32_t			SysMailId;
	CharId_t		SenderId;
	char			SenderName[MAX_NAME_CCH_LENGTH];
	CharId_t		ReceiveId;
	char			ReceiveName[MAX_NAME_CCH_LENGTH];
	int32_t			SendTime;
	int8_t			HasRead;
	int8_t			Extract;		//附件是否提取
	char			MailTitle[MAIL_TITLE_MAX_LENGTH];
	char			MailContent[MAIL_CONTENT_MAX_LENGTH];
	MemChrBag		Item[MAIL_MAX_FU_JIAN_COUNT];
	std::string		Param;
};

typedef std::map<int32_t,MailInfo> MailInfoMap;

enum TI_SHI_VALUES
{
	PET_BAG_NOT_ENOUGH		= 2,	//幻兽背包已满
	PET_EGG_BAG_NOT_ENOUGH	= 3,	//宠物蛋背包格子不足
	FINISH_FEI_TIAN_SHENG_JV= 4,	//已经完成过飞天神驹活动
	NO_TRADE				= 5,	//禁止交易
	NO_ENTER_ACTIVITY		= 6,	//不能传送进入活动,副本等特殊地图
	BAG_SLOT_NOT_ENOUGH		= 2048,	//提示背包空格不足
};

enum FaBaoType
{
	FA_BAO_TYPE_SHU_GUANG	= 0,	//曙光法宝
	FA_BAO_TYPE_DI_LONG		= 1,	//帝龙法宝
	FA_BAO_TYPE_FU_WEN		= 2,	//符文法宝
	FA_BAO_TYPE_COUNT,
};

enum FaBaoResourceType
{	
	FA_BAO_RES_SHU_GUANG	= 0,	//曙光碎片
	FA_BAO_RES_DI_LONG		= 1,	//帝龙碎片
	FA_BAO_RES_FU_WEN		= 2,	//符文碎片
	FA_BAO_RES_COUNT,		
};

#define  DA_TIME_MAX_TIME		30		//答题时间30秒
#define  RAND_ANSWER_TIME		25		//随机答案25秒

//活动状态
enum ACTIVITY_STATE
{
	AS_NOT_START	= 0,	// 未开启
	AS_READY		= 1,	// 准备
	AS_RUNNING		= 2,	// 进行中
	AS_END			= 3,	// 结束
	AS_TIME_OUT		= 4		// 过期
};

//邮件内容id
enum EamilId	
{
	RansomItemId	= 6,			//装备赎回邮件内容
	DaTiHDFirst		= 6203,			//答题活动第一名
	DaTiHDSecond	= 6204,			//答题活动第二名
	DaTiHDThird		= 6205,			//答题活动第三名
	DaTiHDChanYu	= 6206,			//答题活动参与奖
	DaWeiWangHD		= 6210,			//大胃王活动奖励
	PlantAddItem    = 6216,			//采集物获取的物品
	ExpBallId		= 6217,			//经验球id
	DungeonRewards	= 1000,			//副本奖励

	MI_AUCTION_SELL			= 6207,			// 拍卖行售卖成功
	MI_AUCTION_BUY			= 6208,			// 拍卖行购买成功
	MI_AUCTION_DOWNLOAD		= 6209,			// 拍卖行下架成功
	MI_FAMILYWAR_REWARD		= 6211,			// 军团战奖励
	MI_HORSE_RACING_REWARD1	= 6212,			// 飞天神驹第一名奖励
	MI_HORSE_RACING_REWARD2	= 6213,			// 飞天神驹第二名奖励
	MI_HORSE_RACING_REWARD3	= 6214,			// 飞天神驹第三名奖励

	MI_TERRITORY_WAR_REWARD	= 6218,			// 领地战奖励
	MI_HALL_OF_FAME_REWARD	= 6239,			// 名人堂奖励

	MI_HORSE_RACING_REWARD4	= 6240,			// 飞天神驹第四名奖励
	MI_HORSE_RACING_REWARD5	= 6241,			// 飞天神驹第五名奖励
	MI_HORSE_RACING_REWARD6	= 6242,			// 飞天神驹第六名奖励
	MI_HORSE_RACING_REWARD7	= 6243,			// 飞天神驹第七名奖励
	MI_HORSE_RACING_REWARD8	= 6244,			// 飞天神驹第八名奖励
	MI_HORSE_RACING_REWARD9	= 6245,			// 飞天神驹第九名奖励
	MI_HORSE_RACING_REWARD0	= 6246,			// 飞天神驹第十名奖励
	MI_HORSE_RACING_REWARD	= 6247,			// 飞天神驹第十名之后奖励
};

// 公告ID
enum BROADCAST_ID
{
	MO_YU_WORLD_DUNGEON_GONG_GAO	= 1,
	BCI_WORLD_FAMILYWAR_READY		= 2,
	BCI_WORLD_FAMILYWAR_START		= 3,
	BCI_WORLD_FAMILYWAR_PILLAR_KILLED_BY_FAMILY		= 6,
	BCI_WORLD_FAMILYWAR_PILLAR_KILLED_BY_FREE		= 7,
	BCI_WORLD_FAMILYWAR_STONE_KILLED				= 8,
	BCI_WORLD_FAMILYWAR_WIN							= 9,
	BCI_WORLD_FAMILYWAR_FAIL						= 10,
	BCI_MOUNT_DIE_DROP_GONG_GAO		= 11,	// 怪物死亡掉落
	BCI_SOUL_LEVEL_UP				= 12,	// 魂力升级
	BCI_HORSE_RACING_WIN_1			= 13,	// 跑马第一名
	BCI_HORSE_RACING_WIN_2			= 14,	// 跑马第二名
	BCI_HORSE_RACING_WIN_3			= 15,	// 跑马第三名

	BCI_HORSE_RACING_READY			= 19,	// 飞天神驹准备公告
	BCI_HORSE_RACING_START			= 20,	// 飞天神驹开始公告
	BCI_GRADE_BAO_XIANG				= 21,	//  高级宝箱刷新公告
	BCI_VIP_GONG_GAO_1				= 22,	//  vip公告
	BCI_VIP_GONG_GAO_2				= 23,	//  vip公告
	BCI_VIP_GONG_GAO_3				= 24,	//  vip公告
	BCI_TOU_ZI_MOON_CARD			= 26,	//  月卡投资公告
	BCI_TOU_ZI_LEVEL_UP				= 27,	//  登记投资
	BCI_DA_TI_FIRST					= 28,	//  答题公告
	BCI_XIAO_JV_HUA_GONG_GAO		= 30,	//  掉落菊花

	BCI_TERRITORY_ACTIVITY_START	= 31,	// 领地战开始
	BCI_TERRITORY_BATTLE_READY		= 32,	// 领地战开始5分钟后
	BCI_TERRITORY_WIN_SINGLE		= 33,	// 领地战单人获胜
	BCI_TERRITORY_WIN_TEAM			= 34,	// 领地战组队获胜
	BCI_SQ_ACTIVITY_START			= 35,	// 蜘蛛女王活动开始
	BCI_SQ_ACTIVITY_END_BY_SQ_DIE	= 36,	// 蜘蛛女王死亡活动结束
	BCI_SQ_ACTIVITY_END_BY_TIME		= 37,	// 蜘蛛女王活动时间到结束

	BCI_HALL_OF_FAME_FIGHT			= 38,	// 名人堂挑战公告
	BCI_HALL_OF_FAME_RANK_1			= 39,	// 名人堂第一名公告
	BCI_HALL_OF_FAME_RANK_2			= 40,	// 名人堂第二名公告
	BCI_HALL_OF_FAME_RANK_3			= 41,	// 名人堂第三名公告
	BCI_GUAN_WEI_UP					= 42,	// 升级官位公告
	BCI_SHOU_CHONG_LI_BAO			= 43,	// 领取首冲礼包

	BCI_DROP_EQUIP					= 83,	// 玩家装备掉落公告
	BCI_DROP_EQUIP_2				= 84,	// 玩家装备掉落公告
	BCI_RANSOM_EQUIP				= 85,	// 赎回装备
	BCI_RANSOM_EQUIP_2				= 86,	// 赎回装备
	BCI_WAR_VICTORY_BOSS_REVIVE		= 95,	// 抗战boss复活
	BCI_WAR_VICTORY_BOSS_LEAVE		= 96,   // 抗战boss离开
	BCI_WAR_VICTORY_BOSS_KILLED		= 97,	// 抗战boss被杀
};

// GM公告
class GMBroadcast 
{
public:
	GMBroadcast()
		:nId(0),nStartTime(0),nInterval(0),nTimes(0), nLastTime(0), nCount(0)
	{
	}
	GMBroadcast( int32_t id, const std::string& text, int8_t type, int32_t start_time, int32_t interval, int32_t times )
		:nId(id), strText(text), nType(type), nStartTime(start_time), nInterval(interval), nTimes(times), nLastTime(0), nCount(0)
	{
	}

	int32_t nId;
	std::string strText;
	int8_t nType;
	int32_t nStartTime;	
	int32_t nInterval;	
	int32_t nTimes;
	int32_t nLastTime;
	int32_t nCount;
};
typedef std::list<GMBroadcast> GMBroadcastList;
typedef std::map<int32_t, GMBroadcast> GMBroadcastMap;

// 禁言
struct GMBanChat 
{
	CharId_t nCharId;
	int32_t	nExpireTime;
};
typedef std::list<GMBanChat> GMBanChatList;
typedef std::map<CharId_t,GMBanChat> GMBanChatMap;

// 封号
struct GMSeal 
{
	CharId_t nCharId;
	int32_t	nExpireTime;
};
typedef std::list<GMSeal> GMSealList;
typedef std::map<CharId_t,GMSeal> GMSealMap;

// 名人堂
#define HALL_OF_FAME_RANK_SIZE		2000	// 排行榜大小
#define HALL_OF_FAME_CD_TIME		180		// CD时间 10分钟
#define HALL_OF_FAME_FREE_TIMES		10		// 每天可挑战10次
#define HALL_OF_FAME_BUY_COST		10		// 购买消耗魔石
#define HALL_OF_FAME_CLEAR_CD_COST	2		// 清CD消耗魔石
#define HALL_OF_FAME_REWARD_TIME	1320	// 每天22:00发奖励


#define JUE_WEI_RANK_MIN_DONATE	30000000		//3千万才开始排名

typedef std::map<int32_t,MailInfo> MailInfoMap;

#define BANG_SHI_SHANG_CHENG_TYPE	4 //绑石商城的商城类型

enum ShangChengLimitType
{
	LIMIT_TYPE_INVALID		= 0,		 //	不限购
	LIMIT_TYPE_CHAR			= 1,		 // 个人限购(每天的购买次数)
	LIMIT_TYPE_SERVER		= 2,		 //	全服限购(每天的购买次数)
	LIMIT_TYPE_TIME			= 3,		 //	时间限购
};

enum ShopType
{
	ST_GAME_SHOP  = 1,	//商城
	ST_CHAR_SHOP  = 2,	//个人商店
	ST_SCORE_SHOP = 3,	//积分商城
};

typedef std::map<int32_t,int32_t> ItemLimitMap;		// <商城id,购买次数>

struct CfgGameShop
{
	int32_t		ShopId;
	int32_t		ItemId;
	int32_t		ItemClass;
	int32_t		ItemBind;
	int32_t		LimitType;	
	int32_t		LimitCount;
	int32_t		LimitStartTime;
	int32_t		LimitEndTime;
	int32_t		OriginalPrice;		//原价
	int32_t		Price;
	int32_t		ShopType;
	int8_t		VipLevelLimit;		//等级
};
typedef std::map<int32_t,CfgGameShop> GameShopMap;

// 0~6 转化成 1~7
inline int8_t GetWeekDay( int8_t tm_wday )
{
	return ( tm_wday + 6 ) % 7 + 1;
}

enum AUCTION_ITEM_TYPE
{
	AIC_ITEM	= 0,		// 道具拍卖
	AIC_MONEY	= 1,		// 铜钱拍卖
	AIC_GOLD	= 2,		// 魔石拍卖
};

#define MAX_ITEM_LIST	105 //最大背包空间

struct ChouJiangRecord
{
	MemChrBag	  CJItem;
	int32_t		  Time;		//抽奖时间
};
typedef std::list<ChouJiangRecord> CJRecordList;

enum VipCardType
{
	VT_TI_YAN_CARD		= 1,	//vip体验
	VT_STAR_CARD		= 2,	//星之祝福卡
	VT_MOON_CARD		= 3,	//月之祝福卡
	VT_GOD_CARD			= 4,	//神之祝福卡
};
#define  VIP_CARD_TYPE_COUNT	 4		//vip种类
#define  MAX_VIP_LEVEL			12		//最大vip等级
#define  SPECIAL_FLAG			1000    //今天进副本和昨天进副本记录id相差1000

typedef std::set<int32_t> JoinedActivityId;		//参加过的活动
struct JoinedActivityInfo
{
	JoinedActivityId	YesterdayRecord;
	JoinedActivityId	JoinedIdSet;
};
typedef std::map<int32_t,JoinedActivityInfo> JoinedActivityRecord;

enum ACTIVITY_TYPE_ID
{
	ATI_FAMILY_WAR		= 1,	// 军团战
	ATI_HORSE_RACING	= 2,	// 赛马
	ATI_FAMILY_LIGHT	= 3,	// 军团之光
	ATI_MO_LING_RU_QIN	= 4,	// 魔灵入侵
	ATI_DA_TI_HUO_DONG	= 5,	// 答题活动
	ATI_BAO_XIANG		= 6,	// 开宝箱
	ATI_SAFE_GUAJI		= 7,	// 安全挂机
	ATI_TERRITORY_WAR	= 8,	// 领地战
	ATI_SPIDER_QUEEN	= 9,	// 蜘蛛女王
};
#define RACING_HD_SKILL_ID	130		//赛马活动恢复技能

enum TouZiType
{
	TT_MOON_CARD		= 1,	//月卡投资
	TT_LEVEL_UP			= 2,	//升级投资
};

typedef map<int16_t,int32_t>	RecordMap; 

enum KaiFuHuoDongCondition
{
	KFHDC_LEVEL_UP			= 1,		//升级
	KFHDC_PET_RANK			= 2,		//宠物星级排行榜
	KFHDC_PET_POINT			= 3,		//宠物积分
	KFHDC_JUN_TUAN_LEADER	= 4,		//军团战军团长
	KFHDC_JUN_TUAN_WIN		= 5,		//军团战获胜方成员
	KFHDC_FAMILY_WAR_JOIN	= 6,		//军团战参与奖
	KFHDC_BATTLE_RANK		= 7,		//战斗力排行榜
	KFHDC_BATTLE_POINT		= 8,		//战斗力值
};


struct RankInfo
{
	CharId_t			CharId;
	std::string			CharName;
	int8_t				CharJob;
	int8_t				CharSex;
	int32_t				Param;
};
typedef std::map<int32_t,RankInfo> KaiFuHuoDongRank;

struct HuoYueDuRecord
{
	int32_t			FinishTimes;			//完成次数
	int8_t			IsSec;					//是否是秒
};
typedef std::map<int32_t, HuoYueDuRecord> HuoYueDuRecordMap;

enum SkillAttackState
{
	SAS_NORMAL = 0,
	SAS_MISS = 1,//miss
	SAS_IGNORE = 2,//忽视
	SAS_VIOLENT = 3,//暴击
	SAS_PARRY = 4,//闪避
};

struct AchievementState
{
	int32_t Index;
	int32_t FinishCount;
	int8_t  AcState;
	int32_t Time;
};
typedef std::map<int32_t,AchievementState> AchievementMap;

#define FAMILY_LIGHT_MAP_PARA	4	//军团之光地图参数
