#pragma once

#include <cmath>
#include <list>
#include <map>
#include <string>
#include <vector>

//enum SkillResultType
//{
//	SRT_NONE = 0,
//
//	SRT_CD = 1,
//	SRT_DISTANCE = 2,
//	SRT_JOB = 3,
//	SRT_NUMBER = 4,
//	SRT_RANGE = 5,
//	SRT_EFFECT = 6,
//	SRT_CONTINUE = 7,
//
//	SRT_DEF_REDUCE_SELF = 20,
//	SRT_HP_REDUCE_SELF = 21,
//	SRT_ATTACK_ADD = 22,
//	SRT_DP_ADD = 23,//增加闪避；
//	SRT_VP_ADD = 24,//增加暴击；
//	SRT_WUDI = 25,
//	SRT_PDEF_ADD = 26,
//	SRT_MAXHP_INCREASE = 27,
//	SRT_HP_ADD_SELF = 28,
//	SRT_HP_ADD = 29,
//	SRT_MDEF_ADD = 30,
//	SRT_SP_REDUCE_SELF = 31,
//	SRT_COLLIDE = 32,
//	SRT_REBOUND = 33,//反弹；
//
//	SRT_ATTCK = 50,
//	SRT_PDEF_REDUCE = 51,
//	SRT_ATTCK_REDUCE = 52,
//	SRT_SP_REDUCE = 53,
//	SRT_DP_REDUCE = 54,
//	SRT_HITP_REDUCE = 55,
//	SRT_WEAK_TARGET = 56,//make target weak
//	SRT_WEAK_ATTACK_ADDON = 57,
//	SRT_HP_REDUCE_DURABLE = 58,
//	SRT_IGNORE_DEF = 59,
//	SRT_MDEF_REDUCE = 60,
//	SRT_DIZZY_TARGET = 61,//眩晕；
//	SRT_FORCE_ATTACK_SELF = 62,//强制攻击；
//	SRT_BINGDONG_TARGET = 63,//冰冻;
//	SRT_IMBIBE_HP = 64,//吸取目标生命值;
//	SRT_BURN_TARGET = 65,//灼伤目标;
//	SRT_BURN_ADDON = 66,//灼伤目标伤害增加
//	SRT_CONFUSION_TARGET = 67,//使目标进入混乱状态
//	SRT_VP_REDUCE_TARGET = 68,
//
//	SRT_VICEGENERAL_PDEF_ADD = 90,
//	SRT_VICEGENERAL_MDEF_ADD = 91,
//	SRT_VICEGENERAL_ATTACK_ADD = 92,
//	SRT_VICEGENERAL_HP_ADD = 93,
//};
//
//enum SkillResultModify
//{
//	SRM_CD = 101,
//	SRM_DISTANCE = 102,
//	SRM_JOB = 103,
//	SRM_NUMBER = 104,
//	SRM_RANGE = 105,
//	SRM_EFFECT = 106,
//	SRM_CONTINUE = 107,
//
//	SRM_DEF_REDUCE_SELF = 120,
//	SRM_HP_REDUCE_SELF = 121,
//	SRM_ATTACK_ADD = 122,
//	SRM_DP_ADD = 123,//增加闪避；
//	SRM_VP_ADD = 124,//增加暴击；
//	SRM_WUDI = 125,
//	SRM_PDEF_ADD = 126,
//	SRM_MAXHP_INCREASE = 127,
//	SRM_HP_ADD_SELF = 128,
//	SRM_HP_ADD = 129,
//	SRM_MDEF_ADD = 130,
//	SRM_SP_REDUCE_SELF = 131,
//	SRM_COLLIDE = 132,
//	SRM_REBOUND = 133,//反弹；
//
//	SRM_ATTCK = 150,
//	SRM_PDEF_REDUCE = 151,
//	SRM_ATTCK_REDUCE = 152,
//	SRM_SP_REDUCE = 153,
//	SRM_DP_REDUCE = 154,
//	SRM_HITP_REDUCE = 155,
//	SRM_WEAK_TARGET = 156,//make target weak
//	SRM_WEAK_ATTACK_ADDON = 157,
//	SRM_HP_REDUCE_DURABLE = 158,
//	SRM_IGNORE_DEF = 159,
//	SRM_MDEF_REDUCE = 160,
//	SRM_DIZZY_TARGET = 161,//眩晕；
//	SRM_FORCE_ATTACK_SELF = 162,//强制攻击；
//	SRM_BINGDONG_TARGET = 163,//冰冻;
//	SRM_IMBIBE_HP = 164,//吸取目标生命值;
//	SRM_BURN_TARGET = 165,//灼伤目标;
//	SRM_BURN_ADDON = 166,//灼伤目标伤害增加
//	SRM_CONFUSION_TARGET = 167,//使目标进入混乱状态
//	SRM_VP_REDUCE_TARGET = 168,
//
//	SRM_VICEGENERAL_PDEF_ADD = 190,
//	SRM_VICEGENERAL_MDEF_ADD = 191,
//	SRM_VICEGENERAL_ATTACK_ADD = 192,
//	SRM_VICEGENERAL_HP_ADD = 193,
//};

//enum FormationEffect
//{
//	FE_NONE                       =0,
//	FE_PDEF_ADD               = 1, //提高物理防御力
//	FE_MDEF_ADD              =2,//提高法术防御力
//	FE_ATTACK_ADD           =3,//提高攻击力
//	FE_SKILL_EFFECT_ADD  =4,//提高技能效果
//
//};
//enum EquipElement
//{
//	EE_NONE = 0,
//	EE_METAL = 1,
//	EE_WOOD = 2,
//	EE_WATER = 3,
//	EE_FIRE = 4,
//	EE_EARTH = 5,
//	EE_NUM = 6,
//};
//
//enum EquipItemLifeReason
//{
//	EILR_NPC_SHOP,
//	EILR_DROP_ITEM,
//};

enum AcSpecialType
{
	AST_FAMILY_LEADER = 1,
	AST_FEUDAL_PRINCES,
	AST_KING,
	AST_TOP_KING,
	AST_FAMILY_NUMBER,
	AST_KILL_PLAYER,
	AST_OPEN_BAG_SLOT,
	AST_MOUNT_COUNT,
	AST_SPECIAL_MOUNT,
	AST_KILL_ONE_PLAYER,
};

enum CurrencyChangeReason
{

	GM_NONE								= 0,
	GM_DEBUG_CMD						= 1,

// 铜钱使用
 	MCR_CHR_SHOP_COST					= 2,		//个人商店
 	MCR_MONEY_GAIN_ITEM					= 3,
 	MCR_TASK							= 4,		//主线任务
 	MCR_BUY_BACK_ITEM					= 5,		//购回
 	MCR_DUNGEON_REWARD					= 6,		//副本 奖励
 	MCR_SUPER_EXCHANGE					= 7,		//超级兑换 
 	MCR_ACHIEVEMENT_EXCHANGE			= 8,		//成就兑换
 	MCR_PK_DROP							= 9,		//PK时爆出的钱币
 	MCR_GET_DROP_ITEM					= 10,		//掉落拾取
	MCR_NPC_SELL						= 11,
	MCR_COMBI_ITEM						= 12,		// 物品合成

	MCR_EQUIP_EXCHANGE_STAR				= 37,		// 装备强化转移
	MCR_PLAYER_ZHUAN_SHENG_COST_MONEY	= 38,		// 主角转生消耗铜钱
	MCR_TRADE_GET_MONEY					= 39,		// 交易获得
	MCR_TRADE_CONST_MONEY				= 40,		// 交易失去
	MCR_PICK_CURRENCY_ITEM				= 41,		// 拾取资源道具获取
	MCR_MAIL_CURRENCY_ITEM				= 42,		// 邮件资源道具获取
	MCR_DONATION_JUE_WEI				= 43,		// 爵位捐款
	MCR_CYCLY_TASK_GET					= 44,		// 循环任务获得
	MCR_AUCTION_SELL					= 45,		// 拍卖金币
	MCR_PET_TO_BAG						= 46,		// 打包幻兽
	MCR_QI_FU							= 47,		// 祈福
	MCR_ENTER_DUNGEON					= 48,		// 进入副本
	MCR_ATTACK_FAMIWAR_PILLAR			= 49,		// 军团战攻击战神之柱
	MCR_AUCTION_BUY						= 50,		// 拍卖行购买元宝
	MCR_HORSE_RACING_REWARD				= 51,		// 赛马奖励
	MCR_ENTER_ACTIVITY					= 52,		// 进入开宝箱宝箱活动
	MCR_SEARCH_BACK						= 53,		// 资源找回
	MCR_GUAN_WEI_GET					= 54,		// 官位获得
	MCR_ACHIEVEMENT_FINISHED			= 55,		// 完成成就
	MCR_TIAN_LING_LEVEL_UP				= 56,
//=======================================================================================
//绑定魔石开始	
 	GCC_PICK_CURRENCY_ITEM				= 1000,
 	GCC_MAIL_CURRENCY_ITEM				= 1001,
 	GCC_BUY_SHANG_CHENG_ITEM			= 1002,
	GCC_WEEK_ONLINE_REWARD				= 1003,		//周在线奖励
	GCC_ENTER_BOSS_HOME					= 1004,		//进入boss之间
	GCC_EQUIP_EXCHANGE_STAR				= 1005,		//魔化转移

//=========================================================================================
//魔石
	GCR_START							= 2000,
	GCR_QUICK_TASK						= 2001,		//快速任务
	GCR_ACHIEVEMENT_EXCHANGE			= 2002,		//成就兑换
	GCR_QUICK_ACHIEVEMENT				= 2003,		//快速成就
	GCR_DUNGEON_REWARD					= 2004,		//副本奖励
	GCR_BUY_CYCLE_TASK_COUNT			= 2005,		//购买循环任务
	GCR_RECHARGE						= 2006,		//充值
	GCR_CREATE_FAMILY					= 2007,
	GCR_ACT_SPECIAL_EQUIP					= 2008,

	GCR_BLACK_MARCKET_ENTER_TICKET			= 2009,
	GCR_BLACK_MARCKET_BUY_GOODS				= 2010,
	GCR_USE_LIQUAN						= 2008,		//使用礼券
	GCR_SUPER_EXCHANGE					= 2009,		//超级兑换
	GCR_GET_DROP_ITEM					= 2010,		//掉落拾取
	GCR_AUTOBUYBAG						= 2011,		//自动购买物品
	GCR_MOUNT_QUALITY_UP				= 2012,		// 升级坐骑
	GCR_EQUIP_UPGRADE_AUTOBUY			= 2013,		// 装备升阶自动购买
	GCR_EQUIP_UPQUALITY_AUTOBUY			= 2014,		// 装备升品自动购买
	GCR_EQUIP_UPSTAR_AUTOBUY			= 2015,		// 装备升星自动购买
	GCR_BAG_SLOT_OPEN					= 2016,		// 开启背包
	GCR_DEPOT_GET						= 2017,		// 从仓库里取得
	GCR_DEPOT_SLOT_OPEN					= 2018,		// 开起仓库格子
	GCR_TRADE_GET_GOLD					= 2019,		// 交易获得
	GCR_TRADE_CONST_GOLD				= 2020,		// 交易失去
	GCR_RANSOM_ITEM						= 2021,		// 赎回
	GCR_PICK_CURRENCY_ITEM				= 2022,		// 拾取资源道具
	GCR_MAIL_CURRENCY_ITEM				= 2023,		// 邮件资源道具
	GCR_PET_EGG_REHATCH					= 2024,		// 宠物重新孵化
	GCR_PET_EGG_QUICK_HATCH				= 2025,		// 宠物快速孵化
	GCR_REVIVE							= 2026,		// 原地复活
	GCR_TASK_CYCLE_REFRESH_STAR			= 2027,		// 日常任务刷新星级
	GCR_TASK_CYCLE_GET_REWARD			= 2028,		// 日常任务多倍领取奖励
	GCR_DONATION_JUE_WEI				= 2029,		// 爵位捐献
	GCR_FAMILY_CONTRIBUTE				= 2030,		// 帮派捐献
	GCR_BUY_FA_BAO_RES					= 2031,		// 购买法宝资源
	GCR_BUY_SHANG_CHENG_ITEM			= 2032,		// 购买商城物品
	GCR_DUNGEON_DOUBLE_REWARD			= 2033,		// 副本双倍领取
	GCR_DUNGEON_BUILD_TOWER				= 2034,		// 副本造塔
	GCR_INSIDE_PET_EXP_ILLUSION_DOUBLE	= 2035,		// 双倍修炼
	GCR_INSIDE_PET_EXP_ILLUSION_GOLD	= 2036,		// 魔石修炼
	GCR_AUCTION_BUY						= 2037,		// 拍卖行购买道具
	GCR_AUCTION_SELL					= 2038,		// 拍卖行出售魔石
	GCR_CHOU_JIANG						= 2039,		// 抽奖
	GCR_PET_TO_BAG						= 2040,		// 宠物打包到背包栏
	GCR_QI_FU							= 2041,		// 祈福
	GCR_ENTER_DUNGEON					= 2042,		// 进入副本
	GCR_GET_OFFLINE_EXP					= 2043,		// 获取离线多倍
	GCR_BUY_VIP_CARD					= 2044,		// 购买vip卡
	GCR_ENTER_BOSS_HOME					= 2045,		// 进入boss之家
	GCR_EQUIP_EXCHANGE_STAR				= 2046,		// 魔化转移
	GCR_BUY_TE_HUI_LI_BAO				= 2047,		// 购买新服特惠礼包
	GCR_TOU_ZHI_HUO_DE					= 2048,		// 投资获得
	GCR_TOU_ZHI_SHI_QU					= 2049,		// 投资失去
	GCR_HUO_YUE_DU						= 2050,		// 活跃度
	GCR_HALL_OF_FAME_BUY_TIMES			= 2051,		// 名人堂购买次数
	GCR_HALL_OF_FAME_CLEAR_CD			= 2052,		// 名人堂清CD
	GCR_ITEM_COMBI_AUTO_BUY				= 2053,		// 物品合成自动购买
	GCR_BUY_THREE_PET_LI_BAO			= 2054,		// 购买三宠礼包
	GCR_BUY_AC_SOCRE					= 2055,		// 购买勋章积分
	GCR_BUY_WAR_VICTORY_GIFT			= 2056,		// 购买抗战胜利礼包
	GCT_WAR_VICTORY_FAN_LI				= 2057,		// 战胜利充值返利
	GCR_SUN_AND_MOON_LEVEL_UP			= 2058,

//==================================================================================
//元气
	VCR_STRART							= 3000,
	VCR_KILL_MONSTER					= 3001,		// 打怪增加
	VCR_BASE_ILLUSION					= 3002,		// 内置宠初灵
	VCR_GROW_ILLUSION					= 3003,		// 内置宠幻灵
	VCR_LUCKY_ILLUSION					= 3004,		// 内置宠幸运
	VCR_EXP_ILLUSION					= 3005,		// 内置宠武灵


//=======================================================================================
//boss积分和抽奖积分
	SCR_ON_CHOU_JIANG					= 4000,		//抽奖
	SCR_KILL_BOSS						= 4001,		//杀怪
	SCR_BUY_ITEM						= 4002,		//购买物品

//=======================================================================================
// 荣誉
	HCR_HALL_OF_FAME_FIGHT				= 5000,		// 挑战
	HCR_BUY_GUAN_WEI					= 5001,		// 购买官位
	HCR_HALL_OF_FAME_RANK_REWARD		= 5002,		// 排名奖励

//成就积分
	ACHIEVEMNET_SOCRE_GET				= 6001,		// 成就	
	ACHIEVEMNET_UP_XUN_ZHANG			= 6002,		// 升级勋章
	ACHIEVEMENT_BUY_SOCRE				= 6003,		// 购买积分
};

enum ITEM_ADD_REASON
{
 	IACR_NONE					= 0,
 	IACR_DUNGEON_REWARD			= 1,	//副本 奖励
 	IACR_MAIL					= 2,	//邮件获取
 	IACR_EXCHANGE_CODE			= 3,	//交换 码
 	IACR_ACHIEVEMENT_EXCHANGE	= 3,	//成就 兑换
 	IACR_ACTIVITY				= 4,	//活动 奖励
 	IACR_PICK					= 5,	//拾取
 	IACR_LIBAO					= 6,	//礼包
 	IACR_TASK					= 7,	//主线 任务
 	IACR_ONLINE_REWAR			= 8,	//在 线 奖励
 	IACR_COMBINE				= 9,	//合并
 	IACR_CHR_SHOP				= 10,	//个人 商店 购买
 	IACR_SIGN					= 11,	//签到奖励
 	IACR_SEVEN_LOGIN			= 12,	//七天登陆
 	IACR_REMOVE_GEM				= 13,	//撤除宝石
 	IACR_SUIJILIBAO				= 14,	//随机礼包
 	IACR_YELLOW_STONE_REWARD	= 15,	//黄钻每日礼包
 	IACR_YEAR_YELLOW_STONE_REWARD	= 16,	//年费黄钻额外每日礼包
 	IACR_YELLOW_STONE_GROW_UP		= 17,	//黄钻成长礼包
	IACR_DEPOT_GET				= 18,	//仓库获取
	IACR_DEPOT_SAVE				= 19,	//存入仓库
	IACR_GEM_TO_BAG				= 20,	//摘取宝石
	IACR_RANSOM_ITEM			= 21,	//赎回
	IACR_TRADE					= 22,	//交易
	IACR_BUY_SHANG_CHENG_ITEM	= 23,	//商城购买
	IACR_CHOU_JIANG				= 24,	//抽奖
	IACR_BUY_CHOU_JIANG_SHOP	= 25,	//抽奖商店购买
	IACR_FROM_PET				= 26,	//从幻兽栏来
	IACR_DWW_HD					= 27,	//大胃王活动
	IACR_GET_VIP_GIFT			= 28,	//领取vip礼包
	IACR_PALNT_GET				= 29,   //采集物里获得
	IACR_EXP_BALL				= 30,	//经验球获得
	IACR_SHOU_CHONG				= 31,	//首冲
	IACR_NEW_SERVER_TE_HUI		= 32,	//新服特惠
	IACR_EVERYDAY_CHONG_ZHI		= 33,	//每日充值
	IACR_KAI_FU_HUO_DONG		= 34,	//开服活动
	IACR_HUO_YUE_DU				= 35,	//活跃度
	IACR_HALL_OF_FAME_REWARD	= 36,	//名人堂奖励
	IACR_VIP_CARD_GIFT			= 37,	//VIP卡礼包
	IACR_FAMILY_TASK_REWARD		= 38,	//军团任务
	IACR_TOTAL_CHONG_ZHI		= 39,	//开服累计充值
	IACR_VAR_VICTORY			= 40,	//抗战70周年

	IACR_BLACK_MARKET_ENTER_TICKET		= 70,
	IACR_BLACK_MARKET_BUY_GOODS			= 71,
};

enum ITEM_DEL_REASON
{
 	IDCR_NONE						= 0,
 	IDCR_ACHIEVEMENT_QUICK			= 1,	// 成就 快速完成
 	IDCR_BAG_USE					= 2,	// 背包  使用
 	IDCR_ADD_GEM					= 3,	// 镶嵌
 	IDCR_FLY						= 4,	// 传送
 	IDCR_DUNGEON					= 5,	// 副本  次数
 	IDCR_COMBINE					= 6,	// 合并
	IDCR_VICEGENERAL_USE_EXP_PILL	= 7,	// 武将使用经验
	IDCR_EQUIP_UPSTAR				= 8,	// 装备升星
	IDCR_EQUIP_UPGRADE				= 9,	// 装备升阶
	IDCR_EQUIP_UPQUALITY			= 10,	// 装备升品
	IDCR_MOUNT_HEART				= 11,	// 服用坐骑之心
	IDCR_MOUNT_LEAR_SKILL			= 12,	// 学习坐骑技能
	IDCR_MOUNT_SKILL_UP				= 13,	// 升级坐骑技能
	IDCR_MOUNT_LEVEL_UP				= 14,	// 坐骑升阶
	IDCR_EQUIP_OPEN_GEM_HOLE		= 15,	// 宝石开孔
	IDCR_GEM_TO_EQUIP				= 16,	// 宝石镶嵌
	IDCR_TRADE						= 17,	// 交易 
	IDCR_DIE_DROP					= 18,	// 死亡掉落
	IDCR_PET_USE_ITEM				= 19,	// 宠物使用道具
	IDCR_SKILL_LEVEL_UP				= 20,	// 技能升级
	IDCR_BACK_CITY					= 21,	// 使用回城卷
	IDCR_SUI_JI						= 22,	// 使用随机卷
	IDCR_INSIDE_PET_EXP_ILLUSION	= 23,	// 内置宠武灵
	IDCR_INSIDE_PET_USE_LUCKY_ITEM	= 24,	// 内置宠使用幸运值道具
	IDCR_INSIDE_PET_CHANGE_PHASE	= 25,	// 内置宠改变相性
	IDCR_AUCTION_SELL				= 26,	// 拍卖
	IDCR_CHOU_JIANG					= 27,	// 抽奖
	IDCR_TO_PET						= 28,	// 到幻兽栏
	IDCR_QI_FU						= 29,	// 祈福消耗
	IDCR_FAMILY_WAR_SIT_REVIVE		= 30,	// 军团战原地复活
	IDCR_FAMILY_WAR_PET_REVIVE		= 31,	// 军团战复活宠物
	IDCR_PUT_IN_EXP_BALL			= 32,	// 装备经验球
	IDCR_USE_MULTI_ITEM				= 33,	// 使用多个
	IDCR_ENTER_BOSS_HOME			= 34,	// 进入boss之家
	IDCR_SITE_REVIVE				= 35,	// 复活丹
	IDCR_SUN_AND_MOON_LEVEL_UP			= 36,
	IDCR_MOON_SKILL_GET			= 37,
};

enum ItemEffectType
{
	IET_NONE						= 0,
	IET_MONEY_GAIN					= 1,	// 金币
	IET_CHIXUHUIXUE					= 2,	// 持续回血
	IET_SHUNJIANHUIXUE				= 3,	// 瞬间回血
	IET_CHONGHUIXUE					= 4,	// 宠物回血
	IET_CHIXUHUIMO					= 5,	// 持续回魔
	IET_SHUJIANHUIMO				= 6,	// 瞬间回魔 -- 废弃

	IET_JINGYANDAN					= 24,	// 经验丹

	IET_GIFT						= 29,	// 礼包
	IET_AUTO_PET_GIFT				= 30,	// 自动使用的宠物礼包

	IET_EXPERIENCECARD				= 33,	// VIP 体验卡

 	IET_LIQUAN						= 55,	// 礼券

 	IET_YUANBAO						= 70,	// 元宝

 	IET_SUIJILIBAO					= 72,	// 随机礼包

 	IET_SUPER_EXCHANGE				= 75,	// 超级兑换
 	IET_MAXHP_DAOJU					= 76,	// 最大血量buff道具
 	IET_ATTACK_DAOJU				= 77,	// 攻击力buff道具
 	IET_VP_DAOJU					= 78,	// 增加暴击buff道具
 	IET_MUTI_EXP					= 79,	// 多倍经验丹

	IET_CURRENCY_RES				= 82,	// 资源物品

	IET_SHU_GUANG_SUI_PIAN			= 98,	// 曙光碎片
	IET_DI_LONG_SUI_PIAN			= 99,	// 帝龙碎片
	IET_FU_WEN_SUI_PIAN				= 100,	// 符文碎片
	IET_PET_ADD_THIRD				= 101,	// 开三宠

	IET_ENTER_DUNGEON				= 103,	// 进入副本道具
	IET_FAMOLY_WAR_PET_REVIVE		= 104,	// 军团战复活宠物
	IET_FAMOLY_LIGHT_WINE			= 105,	// 军团烈酒
	IET_LEVEL_UP					= 106,	// 升级丹
	IET_JIU_SHU_CARD				= 135,	// 救赎卡
	IET_HUN_LI_UP				    = 136,	// 魂力升级单
};


// 特殊道具
enum ITEM_SPECIAL_ID
{
	ISI_OPEN_THIRD_GEM_HOLE			= 7002,		// 装备开第三个孔
	ISI_OPEN_FIRST_GEM_HOLE			= 7003,		// 装备开第一个孔
	ISI_OPEN_SECOND_GEM_HOLE		= 7004,		// 装备开第二个孔
	ISI_RELIVE						= 33,		// 复活道具
	ISI_TELEPORT					= 34,		// 传送道具
	ISI_PET_KIWI_FRUIT				= 7036,		// 奇异果
	ISI_PET_ELECTRIC_POTION			= 7037,		// 电浆药水
	ISI_PET_EXP_GRAIN				= 7038,		// 圣兽魔晶
	ISI_EXP_BALL					= 7039,		// 普通经验球
	ISI_SPECIAL_EXP_BALL			= 7040,		// 特级经验球
	ISI_PET_LUCKY_GRASS				= 7041,		// 幸运草
	ISI_PET_GOD_GRASS				= 7042,		// 神仙草
	ISI_BACK_CITY_JUAN				= 7078,		// 回城卷
	ISI_SUI_JI_JUAN					= 7079,		// 随机卷
	ISI_ZHI_ZUN_PI_SA				= 7188,		// 至尊披萨
	ISI_FAMILY_WAR_SIT_REVIVE		= 7227,		// 军团战原地复活
	ISI_EMPTY_EXP_BALL				= 7278,		// 空经验球
	ISI_XIAO_JV_HUA					= 7289,		// 小菊花
	ISI_XIAO_LA_BA					= 7290,		// 小喇叭
	ISI_FU_HUO_DAN					= 7308,		// 复活丹
};

enum  AcDailyType
{
	 ADT_MOUNT_COUNT = 1,
	 ADT_FENGYINBANG = 2,
	 ADT_KUNLUNJING = 3,
	 ADT_JIUTIANTA = 4,
	 ADT_CYCLE_TASK = 5,
	 ADT_VICEGENERAL = 6,
	 ADT_FAMILY_TASK = 7,
	 ADT_KINGDOM_TASK =8,
	 ADT_DAILY_ITEM =9,
};

enum  AchievementWorkType
{
	AWT_MUST = 1,
	AWT_NOT_BE = 2,
};

enum AcGrowUpType
{
	AGUT_PLAYER_LEVEL = 1,
	AGUT_ENHANCE =2,
	AGUT_STAATEGICS = 3,
	AGUT_USER_PILL_COUNT = 4,
	AGUT_MOUNT_LEVEL = 5,
	AGUT_MOUNT_XISUI = 6, 
	AGUT_LACKEY_LEVEL = 7,
	AGUT_SKILL_LEVEL = 8,
	AGUT_VICEGENERAL_WUYI_LEVEL= 9,
	AGUT_VICEGENERAL_GENGU_LEVEL = 10,
	AGUT_ZHENFA = 11,
	AGUT_SHENGWANG = 12,
	AGUT_GEM =13,
};

enum ItemBroadcast
{
	IB_PICK = 1,
	IB_TREASURE = 2,
};


enum GainType
{
	GT_EXP			= 1,
	GT_MONEY		= 2,
	GT_GOLD			= 3,
	GT_CASH			= 4,
	GT_SHU_GUANG	= 5,		// 曙光碎片
	GT_DI_LONG		= 6,		// 帝龙碎片
	GT_FU_WEN		= 7,		// 符文碎片
	GT_CHOU_JINAG	= 8,		// 抽将积分
	GT_BOSS_SCORE	= 9,		// BOSS积分
	GT_BIND_MONEY	= 10,		// 绑定金币
	GT_HONOR		= 11,		// 威望
	GT_AC_SOCRE		= 12,		// 成就积分
};

enum NpcFunc
{
	NF_NORMAL	= 0,	// NpcFuncExtra
	NF_TASK		= 1,	// 任务
};

enum NpcFuncExtra
{
	NFE_INTRODUC		= 1034,		// 介绍
	NFE_EQUIPSET		= 1036,		// 装备强化
	NFE_ROLE			= 1037,		// 角色
	NFE_GEMMY			= 1038,		// 宝石镶嵌
	NFE_GANGINFO		= 1039,		// 帮派信息
	NFE_EQUIPBUILD		= 1040,		// 装备打造
	NFE_PETWARE			= 1041,		// 伙伴仓库
	NFE_SINGLEFUBEN		= 1042,		// 单人副本
	NFE_VIPFUBEN		= 1043,		// vip副本
	NFE_MULTIFUBEN		= 1044,		// 多人副本
	NFE_EXPFUBEN		= 1045,		// 经验副本
	NFE_ZHUSHEN			= 1046,		// 诸神副本
	NFE_STALL			= 1047,		// 摊位
	NPE_MLRQ			= 1048,		// 魔灵入侵
};

enum ActionType
{
	AT_NONE = 0,
	AT_ITEM = 1,
	AT_SKILL = 2,
};

enum PlayerTeamStatus
{
	PTS_FREE = 0,
	PTS_TEAM_LEADER = 1,
	PTS_TEAM_MEMBER = 2,
};

#define  ONLINE_REWARD_BEGIN_ID  8
enum PlayerRecord
{
	//临时的记录开始-----
	PR_MIN_TEMP_VALUE						= 0,	
	PR_IN_BOSS_HOME							= 1,		//在boss之家标记
	PR_MAX_TEMP_VALUE						= 1000,
	//临时的记录结束-----

	PR_DAILY_CHECK_LAST_UPDATE				= 1001,		// 跨天的刷新时间
	PR_MINUTE_CHECK_TIME					= 1002,
	PR_TRAILER_KINGDOM						= 1003,
	PR_TRAILER_MAPID						= 1004,
	PR_TRAILER_X							= 1005,
	PR_TRAILER_Y							= 1006,
	PR_TRAILER_HP							= 1007,
	PR_TRAILER_END_TIME						= 1008,
	PR_WORLD_CHAT_LAST_TIME					= 1009,		//最后聊天时间
	
	RP_PK_RANK_COUNT						= 1010,		// 每日 杀人记录
	RP_LOGIN_COUNT							= 1011,		// 登陆次数 
	PR_DEAD_TIME							= 1012,		// 死亡次数
	PR_FLY_ICON_INT							= 1013,		// 用于保存图标飞行的标记
	RP_DAILY_SEVEN_LOGIN_REWARD				= 1014,		// 七天登陆奖励领取信息
	RP_LEVEL_GIFT_REWARD					= 1015,		// 等级礼包领取情况
	RP_WEEK_ONLINE_TIME						= 1016,		// 周在线时间
	RP_LAST_WEEK_ONLINE_TIME				= 1017,		// 上周在线时间
	PR_WEEK_CHECK_LAST_UPDATE				= 1018,		// 跨周刷新时间
	PR_ACCUMULATIVE_OFFLINE_TIME			= 1019,		// 累计离线时间
	PR_VIP_EXP								= 1020,		// vip经验
	PR_VIP_GIFT_RECORD						= 1021,		// vip礼包记录
	RP_VIP_LAST_ADD_EXP_TIME				= 1022,		// 最后增加vip经验的时间
	PR_MAX_VIP_LEVEL						= 1023,		// 最大vip等级
	RP_IN_BOSS_HOME_ENT_TIME				= 1024,		// 在boss之家的最后时间
	RP_CYCLE_FLUSH							= 1025,		// 循环任务刷新总次数
	RP_SHOU_CHONG_LI_BAO					= 1026,		// 首冲状态
	RP_BUY_TE_HUI_RECORD					= 1027,		// 购买开服特惠记录
	RP_KAI_FU_HUO_DONG_LEVEL				= 1028,		// 开服活动期间达到的等级
	RP_KAI_FU_HUO_DONG_PET_POINT			= 1029,		// 开服活动宠物最大星级
	RP_FIRST_JUN_TUAN_ZHAN_STATE			= 1030,		// 第一次军团战情况
	RP_KAI_FU_HUO_DONG_BATTLE				= 1031,		// 开服活动期间最大战斗力
	RP_KAI_FU_HUO_DONG_REWARD				= 1032,		// 开服活动奖励领取情况
	PR_FALL_OF_FAME_CD_TIME					= 1033,		// 名人堂CD时间
	RP_CUR_GUAN_WEI							= 1034,		// 当前官位
	RP_THREE_PET_GIFT						= 1035,		// 三宠礼包是否领取
	RP_TOTAL_CHI_ZHI_VALUES					= 1036,		// 开服累计充值活动
	RP_TOTAL_CHI_ZHI_REWARD					= 1037,		// 开服累计充值领取记录
	RP_WAR_VICTORY_CHONG_ZHI_VALUES			= 1038,		// 抗战胜利活动充值

	// 每日清理的记录开始----------------------------------
	PR_DAILY_CLEAR_BEGIN					= 2000,
	RP_DAILY_PK_MARK						= 2001,		// 每日PK分数
//	RP_EVERY_DAY_GET_GOLD					= 2002,		// 封测 每日领取元宝
	RP_DAILY_ONLIN_TIME						= 2003,		// 每日在线时间
	RP_DAILY_ONLIE_REWARD_INFO				= 2004,		// 每日在线时间奖励
	RP_DAILY_DWW_TIMES						= 2005,		// 大胃王奖励次数
	RP_DAILY_DWW_LAST_TIME					= 2006,		// 今天参加大胃王
	RP_IS_USED_VIP_TI_YAN_CARD				= 2007,		// 是否正在使用vip体验卡
	RP_IN_BOSS_HOME_TIME					= 2008,		// 在boss之家的时间
	PR_KILL_TRAILER_COUNT					= 2009,
	PR_SEARCH_BACK_REWARD_INFO				= 2010,		// 资源找回记录
	PR_EVERY_DAY_CHONG_ZHI_GIFT_RECORD		= 2011,		// 每日充值礼包领取情况
	PR_HUO_YUE_DU_REWARD_INFO				= 2012,		// 活跃度领取情况
	PR_XIAO_JV_HUA_SHI_YONG					= 2013,		// 小菊花使用限制
	PR_TERRITORY_WAR_REVIVE_TIMES			= 2014,		// 领地战复活记录
	PR_FALL_OF_FAME_FIGHT_TIMES				= 2015,		// 挑战次数
	PR_FALL_OF_FAME_BUY_TIMES				= 2016,		// 购买次数
	RP_CUR_GUAN_WEI_DAILY_REWARD			= 2017,		// 官位日常奖励信息
	RP_GET_VIP_CARD_GIFT					= 2018,		// 获取vip卡礼包
	RP_FAMILY_TASK_COUNT					= 2019,		// 军团任务次数
	RP_FAMILY_TASK_REWARD					= 2020,		// 军团任务奖励
	RP_VIP_SITEREVIVE_TIMES					= 2021,		// vip每日原地复活次数
	RP_WAR_VICTORY_LOGIN					= 2022,		// 每日抗战胜利每日登陆礼包领取情况
	RP_WAR_VICTORY_BUY_GIFT					= 2023,		// 抗战胜利每日特惠购买情况

	RP_DUNGEON_DAILY_START					= 3000,		// 副本每日领奖记录开始
	RP_DUNGEON_DAILY_END					= 3999,		// 副本每日领奖记录结束
	RP_YESTERDAY_DUNGEON_RECORD_START		= 4000,		// 昨日副本次数开始
	RP_YESTERDAY_DUNGEON_RECORD_END			= 4999,		// 昨日副本次数结束

	PR_YEllOW_DAILY							= 7000,		// 黄钻每日礼包
	PR_YEAR_YEllOW_DAILY					= 7001,		// 年费黄钻额外每日礼包

	PR_BUY_CYCLE_TIMES						= 8003,		// 购买循环任务次数
	PR_QI_FU_MONEY							= 8004,		// 祈福铜钱
	PR_QI_FU_EXP							= 8005,		// 祈福经验

	PR_ACTIVITY_DAILY_REAWRD_START			= 9000,		// 活动每日奖励开始
	RP_ACTIVITY_DAILY_REAWRD_END			= 9999,		// 活动每日奖励结束

	PR_DAILY_CLEAR_END						= 19999,
	// 每日清理的记录结束----------------------------------

	PR_DUNGEON_COMPLETED_BEING				= 20000,	// 副本通关记录开始
	PR_DUNGEON_COMPLETED_END				= 29999,	// 副本通关记录结束

	PR_GEM_SLOT_RECORD						= 37200,	// 宝石镶嵌孔开启状态
	PR_TEAM_AUTO_ACCEPT_INVITE				= 37201,
	PR_TEAM_AUTO_ACCEPT_APPLY				= 37202,
	PR_FIRST_ENTER_GAME						= 37203,
	PR_LEARNED_XP_SKILL						= 37204,
	PR_OPEN_THIRED_FIGHT_PET				= 37205,	// 开三宠
	PR_LAST_FINISH_UP_TOWER_DUNGEON			= 37206,	// 最后完成的爬塔副本
	PR_RETROACTIVE_TIMES					= 37207,	// 补签次数
};

enum PlayerAction
{
	PA_STAND = 1,
	PA_SIT = 17,
	PA_COLLECT = 16,
};


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

enum QiFuType
{
	QT_MONEY = 1,			//祈福铜钱
	QT_EXP	 = 2,			//祈福经验
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
	PT_NORMAL			= 0,
	PT_GRADE_BAO_XIANG	= 1,	//活动中的高级宝箱
};

enum RegionType
{
	RNT_SAFE = 1,
	RNT_TRADE = 2,
	RNT_TASK = 3,
};

enum InstanceMoveReason
{
	IMR_PULL_BACK	= 1,		// 拉回
	IMR_TRANSFER	= 2,		// 传送
	IMR_SKILL		= 3,		// 技能
	IMR_ACTIVITY	= 4,
	IMR_JUMP		= 5,
	IMR_SPOUSE_MOVE = 6,
	IMR_HIT			= 7,
	IMR_OPEN_STALL	= 8,		// 摆摊
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

#define MAX_DROPITEM_SIZE 60

#define PLAYER_GENERAL_CD_MS 1250
#define ITEM_CD_GROUP_COUNT 7

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
typedef std::map<EntityId_t, int32_t> EntityIdInt32Map;

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
 
struct  DungeonGroupReward
{
	  int32_t dungeonID;
	  MemChrBagVector items;
};
typedef std::vector<DungeonGroupReward>DungeonGroupRewardVector;

struct HPEvent
{
	int32_t id;
	int32_t minhp;
	int32_t maxhp;
};
typedef std::list<HPEvent> HPEventList;

struct EquipPatchEnhanceInfo
{
	 int32_t money;
	 int32_t time;
};


struct UnitAttr 
{
	int32_t hp;			// 生命值
	int32_t mp;			// 法力值
	int32_t pp;			// 体力值
	int32_t xp;			// 必杀值
};

struct UnitHandle 
{
	explicit UnitHandle( EntityId_t id_ = 0, int32_t type_ = 0 )
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

	EntityId_t id;
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
	explicit SkillResult(EntityId_t unitid_ = 0, int32_t unittype_ = 0, int32_t hpchange_ = 0, int32_t state_ = 0, int32_t buffid_ = 0, int32_t buffDuration_ = 0)
		: unitid(unitid_), unittype(unittype_), hpchange(hpchange_), attackState(state_), buffid(buffid_), buffDuration(buffDuration_)
	{

	}

	EntityId_t unitid;
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
	bool	rewardWave;
};
typedef std::map<int32_t, MonsterWave> Int32MonsterWaveMap;

struct MonsterWait 
{
	int32_t id;
	int32_t times;
	int64_t	lastTick;
	bool	rewardWave;
};
typedef std::list<MonsterWait> MonsterWaitList;

//#define  MAX_GAMBLE_RECORD 10
//struct GambleRecord
//{
//	int32_t cid;
//	std::string name;
//	int32_t type;
//	int32_t item;
//	int32_t item_type;
//	int32_t count;
//};
//typedef std::vector<GambleRecord>GambleRecordVector;

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

#define MAX_PLAYER_LEVEL 130
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
//typedef std::map<int32_t, Monster*> Int32MonsterMap;
typedef std::map<EntityId_t, Monster*> EntityIdMonsterMap;

class Npc;
typedef std::list<Npc*> NpcList;

class Player;
typedef std::list<Player*> PlayerList;
typedef std::vector<Player*> PlayerVector;
typedef std::map<CharId_t, Player*> CharIdPlayerMap;

class CObjPet;
typedef std::list<CObjPet*> ObjPetList;
typedef std::map<PetId_t,CObjPet*> PetIdObjPetMap;

class Trailer;
typedef std::list<Trailer*> TrailerList;
typedef std::map<EntityId_t, Trailer*> EntityIdTrailerMap;

//class CDropItemGroup;
//typedef std::list<CDropItemGroup*> DropItemGroupList;

class Plant;
typedef std::list<Plant*> PlantList;

class Trap;
typedef std::list<Trap*> TrapList;

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
	GMC_ACTIVITY_START,
	GMC_MO_LING_RU_QIN_START,	// 魔灵入侵开始
	GMC_KILL_MONST,				// 杀死怪物
	GMC_ACTIVITY_STOP,
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

enum SpecialBuffId
{
	JUN_TUAN_LIE_JIU_BUFFI	= 135,		//军团烈酒buffid
};
enum TD_DUNGEON_SKILL_ID
{
	DUNGEON_SKILL_ID_1	= 150,
	DUNGEON_SKILL_ID_2  = 151,
	DUNGEON_SKILL_ID_3  = 152,
};
enum DungeonDropGroupType
{
	DDGT_ORDINARY = 1,
	DDGT_HERO	  = 2,
};

enum AddXiuweiType
{
	AXT_XIUWEIDAN = 1,
	AXT_LINGTAIFUDI = 2,
};

#define DAILY_READ_MAX 10

#define PRISON_MAP_ID 70003		// 监狱地图id
#define PRISON_X    50			// 监狱坐标x
#define PRISON_Y	50			// 监狱坐标y

#define ADD_PP_VALUES1	5
#define ADD_PP_VALUES2	10
#define ADD_PP_VALUES3  15

typedef std::list<UnitHandle> UnitHandlerList;
struct UseSkill
{
	UseSkill()
	{
		CleanUp();
	}

	void CleanUp()
	{
		skillId	= 0;
		srcPos.x = 0;
		srcPos.y = 0;
		tarPos.x = 0;
		tarPos.y = 0;
		targets.clear();
	}

	int32_t			skillId;
	Position		srcPos;
	Position		tarPos;
	UnitHandlerList	targets;
};

struct ShowIcon
{
	int32_t nId;
	int8_t  nState;
	int32_t nLeftTime;
	int8_t	IconLeft;
	int32_t IconRight;
	int8_t Effects;
};
typedef std::list<ShowIcon> IconStateList;

#define MAX_FAMILY_TASK_COUNT 10				//军团任务最大次数

enum HD_ID
{
	HUODONG_DA_TING	    = 1,		// 活动大厅
	JIANG_LI_DA_TING	= 2,		// 奖励大厅
	DA_WEI_WANG_HD_ID	= 6,		// 大胃王活动
	JI_ZHAN_BOSS		= 9,		// 激战boss
	VIP_GUA_JI			= 14,		// vip挂机
	CHOU_CHONG			= 15,		// 首次充值
	NEW_SERVER_TE_HUI	= 16,		// 新服特惠
	EVERYDAY_CHOU_ZHI	= 17,		// 每日充值
	TOU_ZI				= 18,		// 投资
	KAI_FU_HUO_DONG_ID	= 19,		// 开服活动
	TERRITORY_WAR_ICON	= 24,		// 领地战
	HALL_OF_FAME_ICON	= 25,		// 名人堂
	SCORE_SHOP			= 26,		// 积分商城
	THREE_PET_ICON		= 27,		// 三宠礼包图标
	VIP_CARD_ICON		= 28,		// vip开礼包
	CHOU_JIANG_ICON		= 29,		// 抽奖
	QI_FU_ICON			= 30,		// 祈福
	TOTAL_CHONG_ZHI		= 31,		// 开服累计充值
	WAR_VICTORY_ICON	= 32,		// 抗战胜利图标
};

enum SysSetting
{
	SS_PETEGG			= 1,	//自动孵化幻兽蛋
	SS_TEAM				= 2,	//禁止他人邀请我加入队伍
	SS_FRIEND			= 3,	//禁止他人将我加为好友
	SS_TRADE			= 4,	//禁止他人向我发起交易
};

enum APPEND_ATTR_TYPE
{
	FAMILY_WAR_WIN		= 1,	//军团战胜利军团长属性
};

#define WAR_VICTORY_BOSS_ID  477115		//抗战胜利bossid
