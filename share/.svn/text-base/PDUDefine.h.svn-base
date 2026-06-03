#pragma once


/*
* MSG_CM_CODE	客户端发送给服务端的协议	0~10000
* MSG_SM_CODE	服务端发送给客户端的协议	10000~20000
* MSG_IM_CODE	服务端各服务器之间的协议	>20000
*/

/*
* 朱开		CM_ZK	400~699		SM_ZK	11400~11699
* 汪敏锋	CM_WMF	700~899		SM_WMF	11700~11899
* 王鑫剑	CM_WXJ	900~999		SM_WXJ	11900~11999
*/

/*
* CM_CHARACTER_MIN					= 0,
* CM_GAME_MIN						= 5,
* CM_GATE_MIN						= 1000,
* CM_LOGIN_MIN						= 2000,
* CM_SOCIAL_MIN						= 3000,
* CM_KINDOM_MIN						= 4000,
* CM_GM_MIN							= 9000,
*/
enum MSG_CM_CODE
{
	CM_CHARACTER_MIN		=0,
	CM_GET_CHARACTER		=1,		//获取玩家
	CM_NEW_CHARACTER		=2,		//新玩家
	CM_DEL_CHARACTER		=3,		// 废弃 删除玩家信息
	CM_CHARACTER_MAX		=4,

	CM_GAME_MIN				=5,
	CM_ENTER_GAME			=6,		//进入游戏
	CM_ENTER_GAME_ROBOT		=7,		//客服端未使用
	CM_LOGOUT				=8,		
	CM_SYNC_TIME			=9,		//同步时间
	CM_MOVE					=10,	//移动
	CM_JUMP					=11,	//跳跃
	CM_TRAILER_MOVE			=12,	//追踪移动
	CM_HIT					=13,	//技能冲锋
	CM_UNIT_THROWED			=14,
	CM_ARRIVE				=15,	//到达
	CM_SWITCH_MAP			=16,	//选择地图
	//CM_GETMATCHINFO			=17,

	CM_ENTER_DUNGEON					=18,	//进入副本
	CM_ENTER_ACHIEVEMENT_DUNGEON		=19,	//进入成就副本
	CM_BUY_DULTI_DUNGEON				=20,
	CM_LEAVE_DUNGEON					=21,	//离开副本
	CM_LEAVE_ACTDUNGEON					=22,
	CM_DUNGEON_ENTRUST					=23,	// 废弃//开始委托副本
	CM_ENTRUST_STOP						=24,	// 废弃//停止委托
	CM_ENTRUST_COLLING					=25,	// 废弃//委托冷却
	CM_ENTRUST_COLLECT					=26,	// 废弃//委托收集
	CM_ENTRUST_QUERY					=27,	// 废弃//进入委托副本查询
	CM_DUNGEON_SELECT_REWARD			=28,	//选择副本奖励
	CM_ENTER_ACTIVIY					=29,	//进入活动
	CM_LEAVE_ACTIVIY					=30,	//离开活动
	CM_GETAWARD_ACTIVIY					=31,	//领取奖品

	CM_ENTER_FAMILY_ACTIVITY			=32,	// 废弃
	CM_LEAVE_FAMILY_ACTIVITY			=33,	// 废弃
	CM_GET_EXACTIVITY_GIFT				=34,	// 废弃

	CM_ENTER_FAMILY_POT_ACTIVITY		=35,	// 废弃//进入帮派火锅
	CM_QUERY_FAMILY_POT_INFO			=36,	// 废弃//查询帮派火锅

	CM_ENTER_FAMILY_MAP					=37,	// 废弃//进入帮派地图
	CM_LEAVE_FAMILY_MAP					=38,	// 废弃//离开帮派地图
	CM_SELECT_UNIT						=39,	//选择英雄or武将
	CM_DO_UNIT_SKILL					=40,	//使用技能
	CM_PICK_DROPITEM					=41,	//采摘终止
	CM_BEGIN_GATHER						=42,	//开始采集
	CM_END_GATHER						=43,	//结束采集
	CM_USE_TRAP							=44,	//使用触发器
	CM_SWITCH_PK_MODE					=45,	//PK模式

	// 组队协议
	CM_QUERY_TEAMS_AROUND				=46,	// 搜寻附近队伍
	//CM_CREATE_TEAM						=47,	// 创建队伍
	//CM_INVITE_INTO_TEAM					=48,	// 邀请玩家入队
	//CM_CHANGE_TEAM_NAME					=49,	// 废弃
	//CM_SET_TEAM_LEADER					=50,	// 队长转让
	//CM_KICKOUT_TEAM_MEMBER				=51,	// 踢人
	//CM_LEAVE_TEAM						=52,	// 离开队伍
	//CM_APPLY_INTO_TEAM					=53,	// 申请入队
	//CM_REPLY_TEAM_INVITE				=54,	// 回复组队邀请
	//CM_REPLY_TEAM_APPLY					=55,	// 回复组队申请

	CM_SAFE_REVIVE						=56,	//回城复活
	CM_ON_SITE_REVIVE					=57,	//立即复活
	CM_STRONG_REVIVE					=58,	//
	CM_QUERY_CHR_INFO					=59,	//查看将领
	CM_UPGRADE_LEVEL					=60,
	CM_KINGDOM_SELECT					=61,	// 废弃//选择叛国管理员
	CM_CHANGE_KINGDOM					=62,	// 废弃//叛国
	CM_SELECT_KINGDOM					=63,	// 废弃//选择国家
	CM_EXCHANGE_EQUIP					=64,	// 废弃//装备改变
	CM_SWITCH_MOUNT						=65,
	CM_EXCHANGE_ARTIFACT				=66,	//null
	CM_ADD_ARTIFACT_EXP					=67,	//null
	CM_ADD_ARTIFACT_MAX_LEVEL			=68,	//null
	CM_ADD_ARTIFACT_QUALITY				=69,	//null
	CM_MOUNT_XISUI_UPGRADE				=70,	// 废弃//坐骑洗髓 
	CM_MOUNT_USER_XIUWEIDAN				=71,	// 废弃//使用资质丹训练(玄铁)
	CM_QUERY_BAG_ITEMS					=72,	// 废弃//查询包裹

	CM_QUERY_SIGN_INFO					=73,	//签到信息
	CM_SIGN								=74,	//每日签到
	CM_GET_SIGN_REWARD					=75,	//领取签到奖励
	/*神将传说（转身）*/
	CM_QUERY_AC_EXCHANGE				=76,	//查询成就
	CM_QUERY_AC_OUTDOOR					=77,	//传说野外
	CM_QUERY_AC_CAVE					=78,	//洞穴
	CM_QUERY_AC_GROW_UP					=79,	//成长（成就）
	CM_QUERY_AC_CHALLENGE				=80,	//挑战（转身）
	CM_QUERY_AC_SPECIAL					=81,	//特殊成就
	CM_QUERY_AC_DAILY					=82,
	CM_QUERY_AC_TASK					=83,	//成就任务  
	CM_GET_ACHIEVEMENT_REWARD			=84,	//领取成就奖励
	CM_GET_AC_EXCHANGE_REWARD			=85,	//领取挑战成就奖励
	CM_QUICK_AC_DAILY					=86,	//快速完成日常成就
	CM_QUICK_AC_OUTDOORCAVE				=87,	//龙魂石快速完成

	CM_ADD_BAGSLOT						=88,	//增加包裹位置
	CM_USE_ITEM							=89,	//使用包裹物品
	CM_PATCH_USE_ITEM					=90,	//批量使用道具
	CM_MOVE_ITEM						=91,	//移动装备 
	CM_SPLIT_ITEM						=92,
	CM_DESTROY_ITEM						=93,
	CM_SORT_BAG							=94,	//整理包裹
	CM_SELL_ITEM						=95,	//卖出背包物品
	CM_ITEM_COMBINE						=96,	// 废弃//合成
	CM_EQUIP_ENHANCE					=97,	// 废弃//强化装备
	CM_QUERY_EQUIP_ENHANCE_TIME			=98,	// 废弃//查看强化装备
	CM_RESET_ENHANCE_TIME				=99,	// 废弃
	CM_EQUIP_SMITTHING					=100,	// 废弃//装备锻造升级
	CM_EQUIP_MAGIC_SMITH				=101,	// 废弃//神铸打造装备
	CM_EQUIP_DISMANTLE					=102,	// 废弃//分解装备
	CM_UNDRESS_SHIZHUANG				=103,	// 废弃//脱掉时装
	CM_MOUNT_XISUI						=104,	// 废弃//坐骑洗髓
	CM_EQUIP_ADDGEM						=105,	// 废弃//镶嵌宝石装备
	CM_EQUIP_REMOVEGEM					=106,	// 废弃//取消镶嵌宝石
	CM_STRATEGICS_READ					=107,	// 废弃//阅读兵法
	CM_STRATEGICS_EXERCISE				=108,	// 废弃//Strategic 兵法训练
	CM_STRATEGICS_QUERY					=109,	// 废弃//查询兵法
	CM_QUERY_SKILL_LIST					=110,	//查询技能LIST
	CM_UPGRADE_SKILL_LEVEL				=111,	//升级SKILL LEVEL
	CM_QUERY_ZHENFA_LIST				=112,	// 废弃//查询心法LIST
	CM_UPGRADE_ZHENGFA_LEVEL			=113,	// 废弃//更新阵法等级
	CM_QUERY_TASK_LIST					=114,
	CM_RECEIVE_TASK						=115,	//接受任务
	CM_SUBMIT_TASK						=116,	//提交任务
	CM_GIVEUP_TASK						=117,	//放弃任务
	CM_SET_TASK_CAN_SUBMIT				=118,	//设置任务提交 
	CM_RECEIVE_TASK_CYCLE				=119,	// 废弃 接受循环任务
	CM_SUBMIT_TASK_CYCLE				=120,	// 废弃 提交循环任务
	CM_RECEIVE_TASK_FAMILY				=121,	//接受帮派任务
	CM_SUBMIT_TASK_FAMILY				=122,	//提交帮派任务
	CM_RECEIVE_TASK_KINGDOM				=123,	//接受国家任务
	CM_SUBMIT_TASK_KINGDOM				=124,	//提交国家任务
	CM_TALK_WITH_NPC					=125,	//和NPC交谈
	CM_QUICK_DONE						=126,	//快速完成
	CM_TELEPORT							=127,	//传送 
	CM_TELEPORT_ACTIVITY				=128,	//活动传送
	CM_QUERY_VICE_GENERAL_LIST			=129,	// 废弃//查询副将列表
	CM_QUERY_LAKEY						=130,	// 废弃//查询随从
	CM_MONSTER_MOVE						=131,
	CM_KICK_OUT_MOVE					=132,	//反冲移动
	CM_VICE_GENERAL_MOVE				=133,	// 废弃//副将移动
	CM_VICEGENERAL_FREE					=134,	// 废弃
	CM_VICEGENERAL_MAIN_SETTING			=135,	// 废弃
	CM_VICEGENERAL_MODE_SETTING			=136,	// 废弃
	CM_VICEGENERAL_GENGU_UPGRADE		=137,	// 废弃//副将强化资质
	CM_VICEGENERAL_WUYI_UPGRADE			=138,	// 废弃//副将武艺升级
	CM_MOUNT_UPGRADE					=139,	//坐骑进阶
	CM_SHIZHUANG_CHANGE_FORM			=140,	//换装 -- 废弃
	CM_VICE_GENERAL_DO_SKILL			=141,	// 废弃//副将使用技能
	CM_ADD_ACTION						=142,
	CM_REMOVE_ACTION					=143,
	CM_EXCHANGE_ACTION					=144,	//交换技能位置
	CM_SET_AUTOFIGHT					=145,	//设置自动战斗
	CM_SET_SYSTEM_SETTING				=146,	//系统设置
	CM_QUERY_GAME_SHOP					=147,	//客户端未使用
	CM_BUY_GAME_SHOP_ITEM				=148,	//购买商城物品
	CM_BUY_GAME_CHR_ITEM				=149,	//购买个人商城
	CM_BUY_TOP_SHOP_ITEM				=150,	//购买商城热卖商品
	CM_BUY_BACK_CHR_ITEM				=151,	//购回个人商城物品
	CM_BUY_RESOURCE						=152,	//兑换心法
	CM_BUY_TASK_COUNT					=153,	//购买任务次数
	CM_GET_ONLINE_REWARD				=154,	//领取在线奖励
	CM_ASK_ONLINE_TEME_INFO				=155,	//请求在线时间信息
	CM_GET_WEEK_ONLINE_REWARD			=156,	//获取周在线奖励
	CM_QUERY_MONSTER_BROADCAST			=157,
//	CM_GET_OFFLINE_EXP					=158,	//废弃//获取离线经验
	CM_TELEPORT_BY_ITEM					=159,	//传送
	CM_BUY_TELEPORT_COUNT				=160,	//购买传送次数
	CM_CLICK_PAY_BUTTON					=161,	//充值
	CM_MAP_ENTERED						=162,
	CM_DEBUG_CMD						=163,	//命令行输入

	CM_GET_BLESS_EXP					=164,	//null
	CM_QUERY_PLAYER_INFO				=165,	//查询玩家信息
	CM_MOUNT_PUTUP						=166,	//背包使用坐骑 （无实现）
	CM_PILL_USE							=167,	//废弃//丹药使用
	CM_LACKEY_UPGRADE					=168,	//废弃//升级奴仆
	CM_QUERY_DAILY_ITEM					=169,	//查询活跃度项目
	CM_GET_DAILY_REWARD					=170,	// 废弃 领取活跃奖励
	CM_DAILY_SEARCHBACK_REWARD			=171,	// 废弃 领取日常奖励
	CM_DAILY_FAMILY_REWARD				=172,	// 废弃 帮派俸禄
	CM_DAILY_KINGDOM_REWARD				=173,	// 废弃 国家俸禄
	CM_DAILY_WUSHEN_REWARD				=174,	// 废弃 武神俸禄a
	CM_DAILY_LEVEL_REWARD				=175,	// 废弃 等级俸禄
	CM_GET_FAV_REWARD					=176,	//收藏和保存快捷方式后的奖励
	CM_QUERY_LAN_AND_VAL_GIFT_INFO		=177,	//查询元宵情人双节活动领奖情况
	CM_GET_LAN_AND_VAL_GIFT				=178,	//获取元宵情人节双节活动奖励
	CM_DAILY_CLOSE_TABLE				=179,	//关闭日常活跃度面板
	CM_QUERY_CHARGE_REWARDS_INFO		=180,
	CM_GET_CHARGE_REWARD				=181,	//领取首冲礼包
	CM_SECOND_DAY_LOGIN					=182,	//第二天登陆奖励
	CM_BUY_READ_COUNT					=183,	// 废弃//购买 阅读次数
	CM_OPEN_LEVEL						=184,	// 废弃//转生
	CM_GAMBLE							=185,	//废弃 //摇奖（稀世宝阁）
	CM_BUY_PVP_STATE					=186,	//购买 相关状态
	CM_QUERY_DAILY_PK_INFO				=187,	//查询 每日PK 信息
	
	CM_GOTO_ENEMY_KILLER_RANK			=188,	//传送到敌人 位置	// 废弃
	CM_GET_DAILY_PK_REWARD				=189,	//获取 每日PK 奖励
	CM_QUERY_KILLER_RANK_SELF			=190,
	CM_BUY_LEVEL_EQUIP					=191,	// 废弃
	CM_QUERY_EVERY_GOLD					=192,
	CM_GET_EVERY_GOLD					=193,
	CM_FAMILY_BREAK						=194,	// 废弃 解算帮派
	CM_GET_LEVEL_GIFT					=195,	//领取 等级礼包
	CM_QUERY_LEVEL_GIFT					=196,	//查询 等级礼包 
	CM_GAME_PUBLIC_CHAT					=197,	//聊天
	CM_QUERY_GAMBLE_DEPOT_ITEM			=198,	
	CM_GET_GAMBLE_DEPOT_ITEM			=199,
	CM_GET_LEVEL_GOLD					=200,	//领取  等级元宝
	CM_QUERY_LEVEL_GOLD					=201,	//查询 等级元宝

	CM_GET_SEVEN_LOGIN					=202,	//七日礼包领取

	CM_QUERY_SEVEN_LOGIN				=203,
	
	CM_QUERY_NEW_SERVER_ACTIVITY_INFO	=204,
	CM_GET_NEW_SERVER_ACTIVITY_REWARD	=205,

	CM_GET_NEW_SERVER_ACTIVITY_GOLD		=206,

	CM_GET_MAGIC_WEAPON					=207,	// 废弃//装备神器
	CM_GET_MAGIC_WEAPON_INFO			=208,	// 废弃//获取神器信息
	CM_MAGIC_WEAPON_UPGRADE				=209,	// 废弃//神兵
	CM_USER_JOIN						=210,
	//CM_TEAM_DUNGEON_START				=211,	// 废弃//组队副本开始
	//CM_TEAM_DUNGEON_KICK_OUT			=212,	// 废弃//踢出队伍
	CM_USE_JIANSHELING					=213,	// 废弃//使用建设令
	CM_VICEGENERAL_UPGRADE				=214,	// 废弃//副将进阶
	CM_EXCHANGE_GAMBLE_GOLD_EQUIP		=215,	// 废弃

	//CM_BUY_VIP							=216,
	CM_YELLOW_STONE						=217,	//QQ黄钻特权	
	CM_GET_YELLOW_AWARD					=218,	//领取QQ黄钻礼包

	CM_GET_STRATEGICS_PAGE					= 219,			// 废弃//兵法书页领取
	CM_FLUSH_STRATEGICS_PAGE				= 220,			// 废弃//刷新书页
	//CM_LEAVE_DUNGEON_TEAM					= 221,			// 废弃//离开副本组队 队伍
	CM_ADVANCED_TRIALS_QUERY				= 222,			// 废弃//进阶试炼初始				
	CM_ADVANCED_TRIALS_RESET				= 223,			// 废弃//进阶重置
	CM_ADVANCED_TRIALS_RAIDS_START			= 224,			// 废弃//进阶副本扫荡开始
	CM_ADVANCED_TRIALS_RAIDS_QUERY			= 225,			// 废弃//进阶扫荡信息
	CM_ADVANCED_TRIALS_RAIDS_STOP			= 226,			// 废弃//扫荡停止
	CM_ADVANCED_TRIALS_RAIDS_REWARD			= 227,			// 废弃//扫荡时间到,领取奖励
	CM_ADVANCED_TRIALS_RAIDS_COOLING		= 228,			// 废弃//冷却扫荡
	CM_SHOP_MYSTERIOUS_QUERY				= 229,			//初始化神秘商店(改版的)
	CM_SHOP_MYSTERIOUS_FLUSH				= 230,			//刷新神秘商店
	CM_SHOP_MYSTERIOUS_BUY					= 231,			//神秘商店 购买

	CM_VICE_GENERAL_TIME_QUERY				= 232,			// 废弃//武将招募时间信息
	CM_VICE_GENERAL_RECRUIT					= 233,			// 废弃//武将招募
	CM_VICE_GENERAL_SHOW					= 234,			// 废弃//预览武将
	CM_VICE_GENERAL_FORWARD					= 235,			// 废弃//武将继承
	CM_VICEGENERAL_GENGU_REPLACE			= 236,			// 废弃//武将资质替换
	CM_VICEGENERAL_GENGU_CANCLE				= 237,			// 废弃//武将资质取消


	CM_PB_THY_RELIEF_RESIDENT				= 250,			// 废弃//升级门生
	CM_PB_THY_RELIEF_SERVANT				= 251,			// 废弃//升级名士
	CM_PB_THY_HIGH_RECRUIT					= 252,			// 废弃//高级招募
	CM_PB_THY_RECRUIT_EXP					= 253,			// 废弃//升级经验仓库
	CM_PB_THY_RECRUIT_MONEY					= 254,			// 废弃//升级铜钱仓库
	CM_MOUNT_CHANGESHAPE					= 255,			//坐骑化形

	CM_VICEGENERAL_USEREXP					= 256,			// 废弃//副将使用经验丹
	CM_VICEGENERAL_FIGHTMODE				= 257,			// 废弃//副将更改战斗模式 上阵 下阵
	CM_VICEGENERAL_FIRE						= 258,			// 废弃//副将解雇

	CM_BUY_THREE_LIMIT_SHOP					= 259,			// 废弃//购买开服3天商城物品

//===============================
//这里还有40条协议可以用
//===============================

	CM_PREVENT_WALLOW						= 299,			//防沉迷
	CM_PB_THY_QUERY							= 300,			// 废弃
	CM_PB_THY_GET_EXP						= 301,			// 废弃
	CM_PB_THY_GET_MONEY						= 302,			// 废弃
	CM_PB_THY_RELIEF						= 303,			// 废弃//升级
	CM_PB_THY_RECRUIT						= 304,			// 废弃//招贤
	CM_PB_THY_RELIEF_COOLING				= 305,			// 废弃
	CM_PB_THY_RECRUIT_COOLING				= 306,			// 废弃

	CM_PB_YWC_ACTIVATION					= 307,			// 废弃//练兵场升级
	CM_PB_YWC_CULTIVATION					= 308,			// 废弃//开始练兵场训练
	CM_PB_YWC_GET_EXP						= 309,			// 废弃//领取练兵场经验
	CM_PB_YWC_COOLING						= 310,			// 废弃//冷去练兵场
	CM_PB_YWC_QUERY							= 311,			// 废弃//练兵场
	CM_PB_YWC_BUY_EXERCISE_COUNT			= 312,			// 废弃//购买演武场修炼次数

	CM_PB_FYB_QUERY							= 313,			// 废弃//副本查询	
	CM_PB_FYB_GET_WUHUEN					= 314,			// 废弃
	CM_PB_FYB_AGAINSEAL						= 315,			// 废弃

	CM_GB_SLD_REFINING_PILL					= 316,			// 废弃
	CM_GB_SLD_ACTIVE						= 317,			// 废弃
	CM_GB_SLD_QUERY							= 318,			// 废弃

	CM_GB_SJT_PRODUCTION					= 319,  		// 废弃//？收取物品（百草园）
	CM_GB_SJT_SHEJITU_QUERY					= 320,			// 废弃

	CM_GB_LTFD_CULTIVATION					= 321,			// 废弃//喂养
	CM_GB_LTFD_GET_XIUWEI					= 322,			// 废弃//获取成长值
	CM_GB_LTFD_COOLING						= 323,			// 废弃//喂养立即冷却
	CM_GB_LTFD_QUERY						= 324,			// 废弃

	CM_SB_KLJ_QUERY							= 325,			// 废弃//查询乾坤镜
	CM_SB_KLJ_AGAINCHALLENGE				= 326,			// 废弃

	CM_SB_JTT_QUERY							= 327,			// 废弃//查询机枢九宫
	CM_SB_JTT_GET_ITEM						= 328,			// 废弃
	CM_SB_JTT_AGAINCHALLENGE				= 329,			// 废弃
	CM_SB_LHT_CHANGEJOB						= 330,			// 废弃

	CM_SB_FM_QUERY							= 331,			// 废弃
	CM_SB_DTT_QUERY							= 332,			// 废弃//查询破龙门
		
	CM_UPDATE_FLY_ICON_INT					= 333,			//开启锁定功能弹窗
//============================================
// 这里还有好多协议可以用
//============================================
	CM_ACTIVITY_BANQUET_TOAST				= 400,

	/*
	* CM_ZK	401~699
	*/
	//背包仓库
	CM_GET_DEPOT_ITEM							= 401,			//取回仓库物品
	CM_SAVE_DEPOT_ITEM							= 402,			//存物品到仓库
	CM_GET_DEPOT_CURRENCY						= 403,			//取出仓库货币
	CM_SAVE_DEPOT_CURRENCY						= 404,			//存货币到仓库
	CM_SORT_DEPOT								= 405,			//整理仓库
	CM_OPEN_DEPOT_SLOT							= 406,			//开启仓库格子
	//宝石镶嵌
	CM_NEW_ADD_GEM								= 407,			//镶嵌宝石
	CM_NEW_REMOVE_GEM							= 408,			//摘取宝石
	CM_OPQN_GEM_HOLE							= 409,			//装备开孔
	//装备赎回
	CM_ASK_RANSOM_INFO							= 410,			//请求装备赎回信息
	CM_ASK_SPOILS_INFO							= 411,			//请求战利品信息
	CM_ASK_RANSOM_ITEM							= 412,			//请求赎回物品							
	//坐骑
	CM_REQUEST_ASK_MOUNT_TRAIN_INFO				= 413,			//请求坐骑信息
	CM_REQUEST_TRAIN_MOUNT						= 414,			//坐骑培养
	CM_REQUEST_REQEST_EAT_MOUNT_HEART			= 415,			//吃坐骑之心
	CM_REQUEST_ACTIVE_MOUNT_USE_DEFAULT_MOUNT	= 416,			//乘骑
	CM_REQUEST_STUDY_AND_UP_MOUNT_SKILL			= 417,			//学习和升级坐骑技能
	CM_REQUEST_ASK_MOUNT_SKILL_INFO				= 418,			//请求坐骑技能信息
	//交易
	CM_REQUEST_TRADE							= 419,			//请求交易
	CM_AGREE_TRADE								= 420,			//同意交易
	CM_ADD_TRADE_ITEM							= 421,			//往交易背包中加物品
	CM_REMOVE_TRADE_ITEM						= 422,			//移除交易背包中的物品
//	CM_REQUSET_SHUI_JI							= 423,			//测试随机
	CM_SUB_TRADE_MONEY							= 424,			//减少背包中的资源
	CM_LOCK_TRADE								= 425,			//锁定交易背包
	CM_SURED_TRADE								= 426,			//确定交易
	CM_CANCEL_TRADE								= 427,			//取消交易
	CM_ADD_TRADE_MONEY							= 428,			//添加交易背包中的资源
	//邮件
	CM_READ_MAIL								= 429,			//读邮件
	CM_ASK_MAIL_LIST							= 430,			//请求邮件列表
	CM_GET_FU_JIAN								= 431,			//获取附件
	CM_DEL_MAIL									= 432,			//删除邮件
	//商城
	CM_ASK_SHANG_CHENG_LIMIT_INFO				= 433,			//请求商城限制信息
	CM_BUY_SHANG_CHENG_ITEM						= 434,			//购买商城物品

	//好友
	CM_ASK_FRIEND_REWARD_INFO					= 436,			//请求好友奖励信息
	CM_ASK_GET_FRIEND_REWARD					= 437,			//请求获取奖励
	//请求boss信息
	CM_ASK_BOSS_INFO							= 438,			//请求boss信息

	//法宝系统
	CM_BUY_FA_BAO_RES							= 439,			//购买法宝资源
	CM_ASK_FA_BAO_INFO							= 440,			//请求法宝信息
	CM_UP_FA_BAO_LEVEL							= 441,			//法宝升级

	//请求战斗力信息
	CM_ASK_BATTLE_INFO							= 442,			//请求战斗力信息
	//法宝
	CM_DRESS_FA_BAO								= 443,			//佩戴或卸下
	//爵位
	CM_JUE_WEI_DONATE_MONEY						= 444,			//爵位捐献
	CM_ASK_JUE_WEI_INFO							= 445,			//请求爵位信息
	//抽奖
	CM_TIDY_CHOU_JIANG_BAG						= 448,			//整理抽奖背包
	CM_GET_CHOU_JIANG_ITEM						= 449,			//取出抽奖物品
	CM_ASK_CHOU_JIANG_RECORD					= 450,			//请求抽奖记录 
	CM_BUY_SCORE_SHOP_ITEM						= 451,			//购买积分商店物品
	CM_ASK_CHOU_JIANG							= 452,			//请求抽奖
	CM_ASK_SCORE_SHOP_INFO						= 453,			//请求积分商城限制信息
	//祈福
	CM_ASK_QI_FU_INFO							= 454,			//请求祈福信息
	CM_ASK_QI_FU								= 455,			//请求祈福
	//大胃王
	CM_ASK_DWW_INFO								= 456,			//请求大胃王信息
	CM_ASK_DWW_REWARD							= 457,			//请求大胃王奖励
	//离线经验
	CM_ASK_OFFLINE_INFO							= 459,			//请求离线经验信息
	CM_GET_OFFLINE_EXP							= 460,			//获取离线经验
	//请求活动大厅数据
	CM_ASK_HUO_DONG_DA_TING_INFO				= 462,			//请求活动大厅数据
	//vip
	CM_BUY_VIP									= 463,			//购买vip卡
	CM_GET_VIP_GIFT								= 464,			//VIP礼包
	CM_GET_VIP_CARD_GIFT						= 465,			//vip卡礼包
	//进入boss之家
	CM_BUY_ENTER_BOSS_HOME						= 467,			//进入boss之家
	CM_LEAVE_BOSS_HOME							= 468,			//离开boss之家
	//进入vip挂机地图
	CM_ENTER_VIP_GUA_JI_MAP						= 469,			//进入vip挂机地图
	//进入魔灵入侵
	CM_ENTER_MO_LING_RU_QIN						= 472,			//进入魔灵入侵
	//资源找回
	CM_ASK_SEARCHBACK_INFO						= 475,			//请求资源找回信息
	CM_ASK_GET_SEARCHBACK_REWARD				= 476,			//找回资源
	//经验球
	CM_PUT_IN_EXP_BALL							= 477,			//装上经验球
	CM_ASK_EXP_BALL_INFO						= 478,			//请求经验球信息
	//点击开始游戏
	CM_CLICK_GAME								= 480,			//点击开始游戏
	//使用多个物品
	CM_USE_MMULTI_ITEM							= 481,			//使用多个物品
	//运营活动
	CM_GET_SHOU_CHONG_REWARD					= 482,			//领首冲礼包
	CM_ASK_SHOU_CHONG_INFO						= 483,			//请求首冲信息
	CM_ASK_SHOU_TE_HUI_INFO						= 484,			//请求新服特惠
	CM_BUY_TEI_HUI_GIFT							= 485,			//购买特惠礼包
	CM_ASK_EVERYDAY_CHONG_ZHI_INFO				= 486,			//请求每日充值信息
	CM_GET_EVERYDAY_CHONG_ZHI_LI_BAO			= 487,			//获取每日充值礼包
	CM_GET_THREE_PET_GIFT						= 488,			//获取3宠礼包			
	CM_GET_TOTAL_CHONG_ZHI_GIFT					= 489,			//开服充值礼包
	//投资
	CM_ASK_TOU_ZI_INFO							= 490,			//请求投资信息
	CM_GET_TOU_ZI_REWARD						= 491,			//领取投资
	CM_TOU_ZI									= 492,			//投资
	
	//开服活动
	CM_ASK_KAI_FU_HUO_DAO_INFO					= 495,			//请求开服活动信息
	CM_GET_KAI_FU_HUO_DAO_WARD					= 496,			//获取开服活动礼包
	CM_ASK_KAI_FU_HUO_DONG_STATE				= 497,			//请求开服活动状态

	//活跃度
	CM_ASK_HUO_YUE_DU_INFO						= 500,			//请求活跃度信息
	CM_GET_HUO_YUE_DU_REWARD					= 501,			//获取活跃度奖励
	CM_ASK_MIAO_HUO_YUE_DU						= 502,			//秒活跃度
	//官位
	CM_ASK_GUAN_WEI_INFO						= 505,			//亲求官位信息
	CM_ASK_GUAN_WEI_REWARD						= 506,			//获取官位奖励
	CM_UP_GUAN_WEI								= 507,			//升级官位
	CM_WEAR_QI_SHI								= 508,			//佩戴骑士
	//成就
	CM_ACHIEVEMENT_GET_REWARD					= 510,			//领取成就奖励
	CM_ACHIEVEMENT_UP_XUN_ZHANG					= 511,			//升级勋章
	CM_ACHIEVEMENT_BUY_XUN_ZHANG_SOCER			= 512,			//购买勋章积分

	//请求开服累计充值信息
	CM_ASK_TOTAL_CHONG_ZHI_INFO					= 515,			//请求开服累计充值信息
	//抗战70
	CM_ASK_VAR_VICTORY_INFO						= 516,			//请求抗战胜利活动信息
	CM_GET_VAR_VICTORY_REWARD					= 517,			//请求抗战胜利奖励
	//杀怪统计
	CM_ASK_KILL_MONSTER_COUNT					= 600,			//请求杀怪信息
	/*
	* CM_WMF	700~899
	*/

	// 装备玩法
	CM_EQUIP_REQUEST_INFO						= 710,			// 请求装备信息
	CM_EQUIP_DRESS								= 711,			// 穿装备
	CM_EQUIP_UNDRESS							= 712,			// 脱装备
	CM_EQUIP_UP_GRADE							= 713,			// 装备升阶
	CM_EQUIP_UP_STAR							= 714,			// 装备升星
	CM_EQUIP_UP_QUALITY							= 715,			// 装备升品（橙装锻造）
	CM_EQUIP_ADD_GEM							= 716,			// 宝石镶嵌
	CM_EQUIP_REMOVE_GEM							= 717,			// 宝石摘取
	CM_EQUIP_ITEM_COMBI							= 718,			// 道具合成
	CM_EQUIP_EXCHANGE_STAR						= 719,			// 强化转移

	// 组队补充
	CM_TEAM_SET_AUTO_OPERATE					= 720,			// 组队默认设置
	//CM_TEAM_DESTROY_TEAM						= 721,			// 队长解散队伍

	// 幻兽系统
	CM_PET_REQUEST_INFO							= 730,			// 请求宠物信息
	CM_PET_FIGHTING								= 731,			// 出战
	CM_PET_REST									= 732,			// 休息
	CM_PET_ZOARIUM								= 733,			// 合体
	CM_PET_ZOARIUM_OFF							= 734,			// 解除合体
	CM_PET_RIDE									= 735,			// 骑乘
	CM_PET_CHANGE_NAME							= 736,			// 宠物改名
	CM_PET_RELEASE								= 737,			// 放生宠物
	CM_PET_HATCHING								= 738,			// 孵化
	CM_PET_MUTI_HATCHING						= 739,			// 批量孵化
	CM_PET_REHATCHING							= 740,			// 重新孵化
	CM_PET_OPEN_EGG								= 741,			// 打开宠物蛋
	CM_PET_DROP_EGG								= 742,			// 丢弃蛋
	CM_PET_USE_EXP_ITEM							= 743,			// 使用经验道具：圣兽魔晶、经验球、特级经验球
	CM_PET_USE_PHASE_ITEM						= 744,			// 使用改变相性道具：电浆药水、奇异果
	CM_PET_STOP_HATCHING						= 745,			// 停止孵化
	CM_PET_QUICK_HATCHING						= 746,			// 快速孵化
	CM_PET_EGG_MOVE								= 747,			// 宠物蛋移动
	CM_PET_LEARN_SKILL							= 748,			// 宠物学习技能（技能书学习）
	CM_PET_FORGET_SKILL							= 749,			// 宠物遗忘技能
	CM_PET_ILLUSION								= 750,			// 幻化
	CM_PET_DEPORT								= 751,			// 仓库存取操作
	CM_PET_SET_KNIGHT							= 752,			// 任命骑士
	CM_PET_USE_LUCKY_ITEM						= 753,			// 使用幸运值道具
	CM_PET_MOVE_TO_BAG							= 754,			// 打包到背包
	CM_PET_GET_FROM_BAG							= 755,			// 从背包移动到幻兽栏
	CM_PET_ILLUSION_BY_LI_BAO					= 756,			// 礼包幻化
	// XP
	CM_START_XP									= 760,			// 开始XP

	// 循环任务
	CM_TASK_CYCLE_RECEIVE						= 770,			// 接受循环任务
	CM_TASK_CYCLE_SUBMIT						= 771,			// 提交循环任务
	CM_TASK_CYCLE_REFRESH_STAR					= 772,			// 刷新循环任务星级
	CM_TASK_CYCLE_BUY_TIMES						= 773,			// 购买循环任务次数

	// 军团
	CM_FAMILY_CONTRIBUTION						= 780,			// 军团捐献
	CM_FAMILY_REGIST_PET						= 781,			// 注册宠物
	CM_FAMILY_UNREGIST_PET						= 782,			// 取消注册宠物
	CM_FAMILY_RECEIVE_TASK						= 783,			// 接军团任务
	CM_FAMILY_GET_TASK_REWARD					= 784,			// 领取帮派
	// 副本
	CM_DUNGEON_BUILD_TOWER						= 790,			// 副本种塔
	CM_DUNGEON_START							= 791,			// 副本开始（跳过等待阶段）
	CM_DUNGOEN_BUY_TOWER						= 792,			// 购买塔

	// 组队副本
	CM_TEAM_DUNGEON_CREATE						= 800,			// 请求创建组队副本
	CM_TEAM_DUNGEON_JOIN						= 801,			// 请求加入组队副本
	CM_TEAM_DUNGEON_START						= 802,			// 组队副本开始

	// 灵兽系统
	CM_INSIDE_PET_REQUEST_INFO					= 810,			// 请求灵兽信息
	CM_INSIDE_PET_BASE_ILLUSION					= 811,			// 初灵
	CM_INSIDE_PET_GROW_ILLUSION					= 812,			// 幻灵
	CM_INSIDE_PET_LUCKY_ILLUSION				= 813,			// 幸运
	CM_INSIDE_PET_EXP_ILLUSION					= 814,			// 武灵
	CM_INSIDE_PET_USE_LUCKY_ITEM				= 815,			// 使用幸运值道具
	CM_INSIDE_PET_USE_PHASE_ITEM				= 816,			// 使用相性道具
	CM_INSIDE_PET_BUY_EXP						= 817,			// 购买经验值
	CM_INSIDE_PET_REQUEST_BASE_ILLUSION			= 818,			// 请求初灵信息
	CM_INSIDE_PET_ITEM_ILLUSION					= 819,			// 物品幻化

	// 摆摊
	CM_OPEN_STALL								= 820,			// 出摊
	CM_CLOSE_STALL								= 821,			// 收摊

	// 活动
	CM_REQUEST_ACTIVITY_INFO					= 830,			// 请求活动信息
	CM_REQUEST_ACTIVITY_FAMILY_WAR_PILLAR_INFO	= 831,			// 请求战神之柱信息
	CM_ACTIVITY_FAMILYWAR_ADD_PILLAR_MONEY		= 832,			// 战神之柱注入军团资金
	CM_ACTIVITY_GET_DAILY_REWARD				= 833,			// 每日活动奖励
	CM_ACTIVITY_REQUEST_TERRITORY_INFO			= 834,			// 请求领地战信息

	// 魂力
	CM_ADD_SOUL									= 840,			// 兑换魂力
	CM_UPGRADE_SOUL_LEVEL						= 841,			// 升级魂力

	// 名人堂
	CM_HALL_OF_FAME_FIGHT						= 850,			// 挑战
	CM_HALL_OF_FAME_BUY_TIMES					= 851,			// 购买次数
	CM_HALL_OF_FAME_CLEAR_CD					= 852,			// 秒CD
	CM_HALL_OF_FAME_INFO						= 853,			// 请求界面信息

	/*
	* CM_WXJ	900~998
	*/

	CM_GAME_MAX,
	

	CM_GATE_MIN					= 1000,
	CM_GATE_LOGIN				= 1001,
	CM_GATE_LOGIN_ROBOT			= 1002,
	CM_GATE_SWITCH_LINE			= 1003,
	CM_GATE_QUERY_LINE			= 1004,
	CM_GATE_LOAD_UI				= 1005,			//创角界面加载完成
	CM_GATE_MAX,

	CM_LOGIN_MIN				= 2000,
	CM_USER_LOGIN				= 2001,
	CM_LOGIN_MAX,


	//社会
	CM_SOCIAL_MIN				= 3000,

	CM_QUERY_MAIL_LIST			= 3001,
	CM_GET_MAIL_INFO			= 3002,
	CM_GET_MAIL_POST			= 3003,
	CM_SEND_MAIL				= 3004,
	CM_DELETE_MAIL				= 3005,
//	CM_READ_MAIL				= 3006,
	CM_SEND_SYS_MAIL			= 3007,

	CM_RELATION_REQUEST_LIST	= 3008,			//关系列表（黑名单等等）
	CM_ADD_RELATION				= 3009,			//添加好友
	CM_DELETE_RELATION			= 3010,			//删除好友
	CM_REMOVE_BAD_RELATION		= 3011,

	CM_FAMILY_REQUEST_LIST				= 3012,			// 帮派列表
	CM_FAMILY_REQUEST_LOGS				= 3013,			// 查看帮派日志
	CM_FAMILY_REQUEST_INFO				= 3014,			// 帮派信息
	CM_FAMILY_REQUEST_MEMBER_LIST		= 3015,			// 查看帮派成员列表
	CM_FAMILY_REQUEST_TOTOM_LIST		= 3016,			// 查看帮派图腾
	CM_FAMILY_REQUEST_APPLIERS			= 3017,			// 帮派申请信息
	CM_FAMILY_REQUEST_PLAYER_PETS		= 3018,			// 查看注册宠物
	CM_FAMILY_EDIT_NOTICE				= 3019,			// 编辑帮派公告
	CM_FAMILY_CREATE					= 3020,			// 创建帮派
	CM_FAMILY_APPLY						= 3021,			// 加入帮派
	CM_FAMILY_CANCLE_APPLY				= 3022,			// 取消加入
	CM_FAMILY_DESTROY					= 3023,			// 解散军团
	CM_FAMILY_REQUEST_REGIST_PETS		= 3024,			// 帮派宠物列表
	CM_FAMILY_APPOINT					= 3025,			// 帮派任命
	CM_FAMILY_APPROVE					= 3026,			// 批准加入
	CM_FAMILY_KICK						= 3027,			// 帮派T人
	CM_FAMILY_LEAVE						= 3028,			// 离开帮派
	CM_FAMILY_ACTIVE_TOTOM				= 3029,			// 激活帮派图腾
	CM_FAMILY_TASK_COUNT				= 3030,			// 请求帮派任务数量

	//CM_TEAM_DUNGEON_ADD					= 3031,			// 废弃//加入
	//CM_TEAM_DUNGEON_QUERY				= 3032,			// 废弃
	//CM_TEAM_DUNGEON_INVITE				= 3033,			// 废弃//世界窗口副本邀请

	CM_KILLER_RANK_QUERY				= 3034,			//查询
	CM_QUERY_ALL_ENEMY_INFO				= 3035,			//查询 所有 敌人 信息
	CM_GOTO_ENEMY						= 3036,			//追杀敌人

	CM_RANK_REQUEST_INFO				= 3037,			// 废弃 //排行榜信息
	CM_QUERY_REAL_TIME_RANK				= 3038,			// 废弃
	CM_QUERY_TITLE_POSITION				= 3039,			// 废弃//查看官爵
	CM_QUERY_KINGDOM_TOP				= 3040,
	CM_SET_KINGDOM_POSTION				= 3041,			// 废弃
	CM_QUERY_GAMBLE_RECORD				= 3042,			// 废弃
	CM_ASK_KINGDOM_POST					= 3043,			// 废弃
    CM_REFUSE_KINGDOM_REQUIRE			= 3044,			// 废弃
	CM_QUERY_LIMIT_SHOP					= 3045,
	CM_BUY_LIMIT_SHOP_ITEM				= 3046,
	CM_QUERY_MYSTERIOUS_SHOP			= 3047,			//查询神秘商店
	CM_EXCHANGE_MYSTERIOUS_SHOP_ITEM	= 3048,
	
	CM_SET_OFFICE						= 3049,
	CM_USE_EXCHANGE_CODE				= 3050,

	CM_SOCIAL_PUBLIC_CHAT				= 3051,			//公共聊天
	CM_SOCIAL_PRIVATE_CHAT				= 3052,			//私聊

	CM_CHANGE_NAME						= 3053,
	CM_CHANGE_FAMILY_NAME				= 3054,
	CM_QUERY_ACTIVITY_INFO				= 3055,			// 废弃
	CM_GET_AWARD_ZHIYUANQIANXIAN		= 3056,			// 废弃
	CM_GET_JUANXIANWUZI_INFO			= 3057,			// 废弃

	// 组队系统
	//CM_QUERY_TEAMS_AROUND				= 3058,			// 搜寻附近队伍
	CM_CREATE_TEAM						= 3059,			// 创建队伍
	CM_INVITE_INTO_TEAM					= 3060,			// 邀请玩家入队
	CM_SET_TEAM_LEADER					= 3061,			// 队长转让
	CM_KICKOUT_TEAM_MEMBER				= 3062,			// 踢人
	CM_LEAVE_TEAM						= 3063,			// 离开队伍
	CM_APPLY_INTO_TEAM					= 3064,			// 申请入队
	CM_REPLY_TEAM_INVITE				= 3065,			// 回复组队邀请
	CM_REPLY_TEAM_APPLY					= 3066,			// 回复组队申请
	CM_TEAM_DESTROY_TEAM				= 3067,			// 队长解散队伍
	//CM_TEAM_SET_AUTO_OPERATE			= 3068,			// 组队默认设置
	//军团
	CM_FAMILY_AUTO_AGREE				= 3069,			// 设置自动
	//好友系统
	CM_ASK_FRIEND_LIST					= 3071,			// 请求好友列表
	CM_ASK_ADD_FRIEND					= 3072,			// 请求添加好友
	CM_REPLAY_ADD_FRIEND				= 3073,			// 答复请求好友
	CM_DELETE_FRIEND					= 3074,			// 删除好友
	CM_SIFT_FRIEND						= 3075,			// 筛选好友
	CM_FIND_PLAYER						= 3076,			// 查找好友
	CM_GET_PLAYER_INFO					= 3077,			// 获取玩家信息

	CM_ASK_JUE_WEI_RANK					= 3078,			// 请求爵位排行榜
	CM_ANSWER_QUESTIONS					= 3079,			// 回答问题

	// 排行榜
	CM_ASK_PET_RANK_INFO				= 3080,			// 请求宠物排行榜信息
	CM_ASK_PET_RANK_LIST				= 3081,			// 请求宠物排行榜（列表）
	CM_ASK_GAME_RANK					= 3082,			// 请求游戏排行榜信息
	CM_REQUEST_WORSHIP_INFO				= 3083,			// 请求崇拜信息
	CM_WORSHIP							= 3084,			// 崇拜

	// 组队副本
	CM_TEAM_DUNGEON_REQUEST_LIST		= 3090,			// 请求组队副本列表
	CM_TEAM_DUNGEON_LEAVE				= 3091,			// 离开组队副本
	CM_TEAM_DUNGEON_KICK				= 3092,			// 组队副本踢人
	CM_TEAM_DUNGEON_READY				= 3093,			// 组队副本开始
	CM_TEAM_DUNGEON_SET_AUTO_START		= 3094,			// 设置满员自动开启
	// 爬塔副本
	CM_ASK_UP_TOWER_DUNGEON_RANK		= 3100,			// 请求副本排行榜
	//答题活动
	CM_ASK_DA_TI_INFO					= 3101,			// 请求答题活动信息

	CM_ASK_ONE_TOU_ZI_RECORD			= 3102,			// 请求一条投资信息
	CM_ASK_ALL_TOU_ZI_RECORD			= 3103,			// 请求所有投资信息

	// 拍卖
	CM_AUCTION_SELL						= 3110,			// 上架
	CM_AUCTION_BUY						= 3111,			// 购买
	CM_AUCTION_CANCEL					= 3112,			// 下架
	CM_AUCTION_REQUEST_ITEM_LIST		= 3113,			// 请求拍卖信息
	CM_AUCTION_REQUEST_SELF_ITEMS		= 3114,			// 请求自己的拍卖列表
	CM_AUCTION_REQUEST_RECORD			= 3115,			// 请求交易记录

	// 名人堂
	CM_HALL_OF_FAME_RANK				= 3120,			// 请求名人堂排行榜
	CM_FAMILY_OPEN_TOTOM				= 3121,			// 激活帮派图腾
	CM_HALL_OF_FAME_GET_REWARD			= 3122,			// 请求名人堂奖励

	CM_SOCIAL_MAX,
	//社会结束 

	CM_KINGDOM_MIN						= 4000,
	
	CM_KINGDOM_MAX,

	CM_GM_MIN							= 9000,
	CM_GM_LOGIN							= 9001,
	CM_GM_BAN_LOGIN						= 9002,
	CM_GM_BAN_CHAT						= 9003,
	CM_GM_KICK_USER						= 9004,
	CM_GM_ANNOUNCEMENT					= 9005,
	CM_GM_SENDMAIL						= 9006,
	CM_GM_BAN_IP						= 9007,
	CM_GM_RELOAD_INFO					= 9008,
	CM_GM_EXACTIVITY					= 9009,
	CM_GM_CLOSE_LINE					= 9900,
	CM_GM_RELOAD_ITEM					= 9901,
	CM_GM_MAX,
};

/*
*SM_GAME_MIN						= 10000,
*SM_GM_MIN							= 19000,
*SM_PHP_MIN							= 19500,	·
*/
enum MSG_SM_CODE
{
	SM_MIN						= 10000,
	SM_LINE_LIST				= 10001,
	SM_LINE_CLOSED				= 10002,
	SM_KICK_OUT					= 10003,
	SM_USER_TOKEN				= 10004,
	SM_CHARACTER_LIST			= 10005,
	SM_OPEN_PANEL				= 10006,
	SM_SYNC_TIME				= 10007,
	SM_LOGIN_INFO				= 10008,
	SM_MOVE						= 10009,
	SM_KICK_OUT_MOVE			= 10010,
	SM_UNIT_THROWED				= 10011,
	SM_INSTANT_MOVE				= 10012,
	SM_SELF_ENTER_AREA			= 10013,
	SM_UNIT_ENTER_AREA			= 10014,
	SM_ENTER_MAP				= 10015,
	SM_LEAVE_MAP				= 10016,
	SM_PLYAER_INTO_MAP			= 10017,
	SM_MONSTER_INTO_MAP			= 10018,
	SM_NPC_INTO_MAP				= 10019,
	SM_PET_INTO_MAP				= 10020,
	SM_LACKEY_INTO_MAP			= 10022,
	// 废弃一条
	SM_TRAILER_INTO_MAP			= 10023,
	SM_DUNGEON_EVENT			= 10024,
	SM_DUNGEON_MOVIE			= 10025,
	SM_STACKS_ADD_INTO_MAP		= 10026,		// 添加地图碰撞
	SM_STACKS_REMOVE_FROM_MAP	= 10027,		// 移除地图碰撞
	SM_FAMILY_ACTIVITY_NAME		= 10028,		// 废弃
	SM_FAMILY_ACTIVITY_FAIL		= 10029,		// 废弃
	SM_FAMILY_POT_ACTIVITY_END	= 10030,		// 废弃
	SM_FAMILY_POST_INFO			= 10031,		// 废弃
	SM_FAMILY_POST_UPDATE_PLANT	= 10032,		// 废弃
	SM_FAMILY_CHR_POST_INFO		= 10033,		// 废弃
	SM_MONSTER_PLAYER_DAMAGE_INFO	= 10034,
	SM_WORLD_BOSS_ACTIVITY_RESULT	= 10035,
	SM_FINISH_DUNGEON			= 10036,		// 副本结算界面
	SM_DUNGEON_RESULT			= 10037,
	SM_SKILL_CHANT				= 10038,
	SM_SKILL_ACTION				= 10039,
	SM_SKILL_RESULT				= 10040,
	SM_UNIT_BASIC_DATA			= 10041,
	SM_UNIT_BUFF_LIST			= 10042,
	SM_UNIT_BUFF_END			= 10043,
	SM_PLAYER_STATUS			= 10044,
	SM_ADD_DROP_ITEM			= 10045,
	SM_REMOVE_DROP_ITEM			= 10046,
	SM_ADD_TRAP					= 10047,
	SM_REMOVE_TRAP				= 10048,
	SM_TRAP_STATE				= 10049,
	SM_FIGHT_EXP_MONEY			= 10050,
	SM_ADD_PLANT				= 10051,
	SM_REMOVE_PLANT				= 10052,
	SM_END_GATHER				= 10053,
	SM_END_SIT					= 10054,		// 废弃

	// 组队下行协议
	SM_TEAMS_AROUND				= 10055,		// 下发附近队伍
	SM_TEAM_MEMBERS				= 10056,		// 下发队伍信息
	SM_TEAM_MEMBER_BASIC_DATA	= 10057,		// 更新玩家信息到队伍
	SM_TEAM_INVITE				= 10058,		// 转发邀请信息
	SM_TEAM_APPLY				= 10059,		// 转发申请信息
	SM_TEAM_LEAVED				= 10060,		// 玩家离开队伍

	SM_EQUIP_INFO				= 10061,
	SM_EQUIP_ENHANCE_TIME		= 10062,		// 废弃
	SM_EQUIP_DISMANTLE_RESULT	= 10063,		// 废弃
	SM_EQUIP_MAGIC_SMITH		= 10064,		// 废弃
	SM_ITEM_INFO				= 10065,		// 废弃
	SM_NEW_ITEM					= 10066,		// 废弃
	SM_ITEM_EFFECT				= 10067,
	SM_STORE_INFO				= 10068,
	SM_CHR_INFO					= 10069,
	SM_CHR_INFO_TYPE			= 10070,
	SM_CHR_KINGDOM_INFO			= 10071,		// 废弃
	SM_VIEW_STAR_FINISHED		= 10072,
	SM_BAG_ITEMS				= 10073,
	SM_BAG_ITEMS_CHANGE			= 10074,
	SM_MAGIC_WEAPON_INFO		= 10075,
	SM_GOLD_CASH_CHANGE			= 10076,
	SM_JUNGONG_CHANGE			= 10077,
	SM_WUHUEN_CHANGE			= 10078,
	SM_JIANGCING_CHANGE			= 10079,
	SM_ZHIYUANQIANXIAN_WUZI_CHANGE	= 10080,		// 废弃
	SM_KINGDOM_CONTRIBUTE_CHANGE	= 10081,
	SM_MONEY_CHANGE					= 10082,
	SM_GAIN_INFO					= 10083,
	SM_REWARD_INFO					= 10084,		// 废弃
	SM_EXPIRE_INFO					= 10085,
	SM_BUY_ITEM_INFO				= 10086,
	SM_SELL_ITEM_INFO				= 10087,
	SM_CONSUME_ITEM_INFO			= 10088,
	SM_ZHENFA_LIST					= 10089,		// 废弃
	SM_SKILL_LIST					= 10090,
	SM_STRATEGICS_LIST				= 10091,		// 废弃
	SM_NEW_SKILL					= 10092,
	SM_REFUGEE_KILL_MONSTER			= 10093,
	SM_TASK_LIST					= 10094,
	SM_TASK_CYCLE					= 10095,
	SM_TASK_KINGDOM					= 10096,
	SM_TASK_FAMILY					= 10097,
	SM_TASK_KILLED_MONSTER			= 10098,
	SM_TASK_RECEIVED				= 10099,
	SM_TASK_CAN_SUBMIT				= 10100,
	SM_TASK_SUBMITTED				= 10101,
	SM_TASK_GIVEUPED				= 10102,
	SM_TASK_CYCLE_RECEIVED			= 10103,
	SM_TASK_CYCLE_SUBMITTED			= 10104,
	SM_TASK_FAMILY_RECEIVED			= 10105,
	SM_TASK_FAMILY_SUBMITTED		= 10106,
	SM_TASK_KINGDOM_RECEIVED		= 10107,
	SM_TASK_KINGDOM_SUBMITTED		= 10108,
	SM_ENTERUST_INFO				= 10109,
	SM_DAILY_ITEM_INFO				= 10110,
	SM_DAILY_ITEM_CHANGE			= 10111,
	SM_DAILY_MARK_CHANGE			= 10112,
	SM_SHIZHUANG_FORM_INFO			= 10113,		// 废弃
	SM_ENTRUST_GROUP_REWARD			= 10114,		// 废弃
	SM_CHARGE_REWARD_INFO			= 10115,
	SM_DAILY_REWARD					= 10116,
	SM_ACTVIVTY_JIFEN				= 10117,
	SM_ACTIVITY_SOUTHINVADE			= 10118,
	SM_ACTIVITY_KILLERIST_BOARDCAST	= 10119,
	SM_ACTVIVTY_DATA				= 10120,		// 废弃
	SM_ACTVITY_PLANTS				= 10121,
	SM_ACTVIVTY_KING_MSG			= 10122,
	SM_SECOND_DAY_LOGIN				= 10123,
	SM_SEARCH_BACK_INFO				= 10124,
	SM_VICE_GENERAL_DIE				= 10125,
	SM_AC_EXCHANGE					= 10126,
	SM_AC_OUTDOOR					= 10127,
	SM_AC_CAVE						= 10128,
	SM_AC_GROW_UP					= 10129,
	SM_AC_CHALLENGE					= 10130,
	SM_AC_SPECIAL					= 10131,
	SM_AC_DAILY						= 10132,
	SM_AC_TASK						= 10133,

	SM_WIND_POINT					= 10134,
	SM_FIND_EXP						= 10135,
    SM_VICEGENERAL_INFO				= 10136,
	SM_VICEGENERAL_SUITE_QUITE		= 10137,
	SM_VICEGENERAL_HP_INFO			= 10138,
	SM_MOUNT_NEW_LEVEL				= 10139,
	SM_VICE_GENERAL_LIST			= 10140,
	SM_NEW_VICE_GENERAL				= 10141,
	SM_VICE_GENERAL_NEW_LEVEL		= 10142,
	SM_LACKEY_INFO					= 10143,		// 废弃
	SM_LACKEY_ADD_MPHP				= 10144,		// 废弃
	SM_MOUNT_LIST					= 10145,
	SM_FLY_COUNT					= 10146,
	SM_PILL_LIST					= 10147,		//废弃
	SM_ACTION_LIST					= 10148,
	SM_AUTO_FIGHT					= 10149,
	SM_SYSTEM_SETTING				= 10150,
	SM_GAME_SHOP					= 10151,
	SM_GAME_SHOP_LIMIT				= 10152,
	SM_GAME_MYSTERIOUS_SHOP			= 10153,
	SM_UPDATE_MYSTERIOUS_SHOP		= 10154, 
	SM_ONLINE_REWARD_STATE			= 10155,		//发送在线时间信息
	SM_LAN_AND_VAL_GIFT_INFO		= 10156,
	SM_CHR_RECORD					= 10157,
	SM_ANNOUCEMENT					= 10158,
	SM_GAME_EVENT					= 10159,
	SM_KILLED_BY_PLAYER				= 10160,

	SM_MONSTER_BROADCAST			= 10161,
	SM_GM_ANNOUNCEMENT				= 10162,
	SM_GAMBLE_BORADCAST				= 10163,		// 废弃

	SM_TEAM_DUNGEON_BORADCAST		= 10164,		// 废弃
	SM_TEAM_DUNGEON_INFO			= 10165,		// 废弃
	SM_INVITE_TEAM_DUNGEON			= 10166,		// 废弃

	SM_ACTIVITY_PKSORCE				= 10167,		//pk比赛后的输赢
	SM_ACTIVITY_MATCH_DATA			= 10168,		//比武数据更新
	SM_ACTIVITY_MSG					= 10169,
	SM_ACTIVITY_RESLUT				= 10170,		//发送比赛结果
	SM_ACTIVITY_QUIZ				= 10171,
	SM_ACTIVITY_STARTFRONT			= 10172,		//活动开始前
	SM_ACTIVITY_STATE				= 10173,
	SM_ACTIVITY_MAP_STATE			= 10174,
	SM_ACTIVITY_EVENT				= 10175,
	SM_CHR_ACTIVITY					= 10176,
	SM_CHR_ACTIVITY_GAIN			= 10177,
	SM_DRINK_EVENT					= 10178,
	SM_GOLD_EVENT					= 10179,
	SM_OFFLINE_EXP_DATA				= 10180,
	SM_KINGDOM_RANK					= 10181,
	SM_PRIVATE_CHAT					= 10182,
	SM_FAMILY_STATE_DATA			= 10183,
	SM_MAIL_LIST					= 10184,
	SM_MAIL_INFO					= 10185,
	SM_GUESS_INFO					= 10186,
	SM_NEW_MAIL						= 10187,
	SM_HAVE_NO_READ_MAIL			= 10188,
	SM_FRIEND_INFO					= 10189,
	SM_RELATION_MESSAGE				= 10190,
	SM_FAMILY_LIST					= 10191,				// 下发帮派列表
	SM_FAMILY_NOTICE				= 10192,				// 下发帮派公告
	SM_FAMILY_INFO					= 10193,				// 下发帮派信息
	SM_FAMILY_MEMBER_INFO			= 10194,				// 下发帮派成员信息
	SM_FAMILY_TOTOM_INFO			= 10195,				// 下发图腾信息
	SM_FAMILY_APPLIERS				= 10196,				// 下发帮派申请信息
	SM_FAMILY_PETS					= 10197,				// 下发帮派登记宠物
	SM_FAMILY_EVENT					= 10198,				// 下发帮派通知
	SM_FAMILY_PLAYER_PETS			= 10199,				// 下发自身登记幻兽
	SM_FAMILY_APPLY_RESULT			= 10200,				// 下发申请结果
	SM_FAMILY_LOGS					= 10201,				// 下发帮派日志
	SM_FAMILY_JOINED				= 10202,				// 成功加入军团
	SM_FAMILY_TASK_COUNT			= 10203,				// 下发帮派任务数量
	SM_REAL_TIME_RANK_RESULT		= 10204,
	SM_REAL_TIME_RANK_TIME			= 10205,
	SM_TITLE_POSITION				= 10206,				// 废弃
	SM_FAMILY_WAR_EVENT				= 10207,
	SM_FAMILY_WAR_WINNER			= 10208,				// 废弃
	SM_PEOPLEBOOK_TAOYUAN			= 10209,				// 废弃
	SM_PEOPLEBOOK_YANWUCHANG		= 10210,				// 废弃
	SM_PEOPLEBOOK_FENGYINBANG		= 10211,				// 废弃
	SM_GLEBEBOOK_SHENLONGDING		= 10212,				// 废弃
	SM_GLEBEBOOK_SHEJITU			= 10213,				// 废弃
	SM_GLEBEBOOK_LINGTAIFUDI		= 10214,				// 废弃
	SM_SKYBOOK_KUNLUNJING			= 10215,				// 废弃
	SM_SKYBOOK_JIUTIANTA			= 10216,				// 废弃
	SM_SKYBOOK_FUMO					= 10217,				// 废弃
	SM_SKYBOOK_DENGTIANTI			= 10218,				// 废弃
	SM_BANQUET_TOAST				= 10219,
	SM_PVP_INFO						= 10220,
	SM_DAILY_PK_INFO				= 10221,
	SM_ENEMY_INFO					= 10222,
	SM_ENEMY_INFO_SINGLE			= 10223,
	SM_TRYOUT_VIP_INFO				= 10224,
	SM_KILLER_RANK_INFO				= 10225,				// 废弃
	SM_KILLER_RANK_SELF				= 10226,
	SM_EVERY_DAY_GET_GOLD			= 10227,
	SM_LEVEL_GIFT					= 10228,
	SM_LEVEL_GOLD					= 10229,
	SM_GAMBLE_SINGLE_INFO			= 10230,
	SM_PUBLIC_CHAT					= 10231,
	SM_GAMBLE_DEPOT					= 10232,				//稀世宝阁珍宝仓库
	SM_SIGN_INFO					= 10233,				//发送签到信息
	SM_JUANXIANWUZI_INFO			= 10234,				// 废弃
	SM_SEVEN_LOGIN					= 10235,

	SM_NEW_SERVER_ACTIVITY_INFO		= 10236,
	SM_NSA_JIUTIANTA				= 10237,
	SM_NSA_EQUIP					= 10238,
	SM_NSA_GEM						= 10239,
	SM_NAS_LATER					= 10240,
	SM_SHOP_LIMIT_NOTE				= 10241,
	SM_CHR_LOGIN_IN_INFO			= 10242,

	SM_GAIN_VICEGENERAL_BROADCAST	= 10243,
	SM_VICEGENERAL_UPGRADE_BROADCAST	= 10244,
	SM_MOUNT_UPGRADE_BROADCAST			= 10245,
	SM_VICEGENERAL_GENGU_BROADCAST		= 10246,
	SM_VICEGENERAL_WUYI_BROADCAST		= 10247,
	SM_OPEN_LEVEL_BROADCAST				= 10248,				// 废弃
	SM_CHANGE_JOB_BROADCAST				= 10249,				// 废弃
	SM_LACKEY_UPGRADE_BROADCAST			= 10250,				// 废弃
	SM_ITEM_COMBINE_BROADCAST			= 10251,				// 废弃
	SM_SUBMIT_GOLD_EQUIP_BROADCAST		= 10252,				// 废弃
	SM_READ_BROADCAST					= 10253,				// 废弃
	SM_VIP_BROADCAST					= 10254,
	SM_RECHARGE_REWARD_BROADCAST		= 10255,
	SM_GET_DIAMOND_RING					= 10256,

	SM_CHANGE_POSITION					= 10257,				// 废弃

	SM_KINGDOM_MIN						= 10258,
	SM_KINGDOM_POSTION					= 10259,
	SM_KINGDOM_FENG						= 10260,
	SM_KINGDOM_CREAT					= 10261,			//创建国家
	SM_KINGDOM_GUANJUE					= 10262,			//官爵架构
	SM_KINGDOM_TWEAL_CONFIG				= 10263,			//奖励加成配置信息
	SM_KINGDOM_TOP						= 10264,			//
	SM_KINGDOM_MAX						= 10265,

	SM_BANQUET_INFO						= 10266,
	SM_GAMBLE							= 10267,				// 废弃
	SM_QUERY_PLAYER_INFO				= 10268,
	SM_QUERY_ACTIVITY_INFO				= 10269,
	SM_EXACTIVITY_INFO					= 10270,				//废弃
	SM_EXACTIVITY_CFG					= 10271,				//废弃

	SM_CHARGE_SUCCESS					= 10272,
	SM_FLY_ICON_INT						= 10273,

	SM_YELLOW_STONE						= 10274,
	SM_PREVENT_WALLOW					= 10275,				//防沉迷
	SM_SKYBOOK_ADVANCEDTRIALSQUERY		= 10276,				// 废弃//进阶试炼初始化
	SM_ADVANCEDTRIALS_RAIDS_INFO		= 10277,				// 废弃//进阶试炼扫荡信息
	SM_ADVANCEDTRIALS_BOSS_RESULT		= 10278,				// 废弃//进阶试炼BOSS怪掉 通知
	SM_MYSTERIOUS_SHOP_QUERY			= 10279,				//神秘商店初始化
	
	SM_VICE_GENERAL_TIME_QUERY			= 10280,				//武将招募时间信息
	SM_VICE_GENERAL_RECRUIT				= 10281,				//招募的武将
	SM_VICE_GENERAL_SHOW				= 10282,				//预览武将
	SM_VICE_GENERAL_WORLD_BROADCAST		= 10283,				//世界广播获得武将

	SM_ACTIVITY_STARTFIVEFRONT			= 10299,				//提前5分钟提醒

	SM_HIGH_TAOYUAN_ERROR				= 10300,				// 废弃//高级招贤失败
	SM_THREE_SHOP						= 10301,				// 废弃//3天商城购买信息



	/*
	* SM_ZK	11400~11699
	*/
	SM_NOTIFY_MOUNT_INFO				= 11407,		//通知坐骑信息
	SM_NOTIFY_MOUNT_TRAIN_RESULT		= 11408,		//通知坐骑培养结果
	SM_NOTIFY_MOUNT_SKILL_INFO			= 11409,		//通知坐骑技能信息

	SM_NOTIFY_TI_SHI_INFO				= 11415,		//提示信息
	SM_NOTIFY_MOUNT_UPDATE				= 11416,		//坐骑升阶公告

	SM_NOTIFY_KILL_MONSTER_COUNT		= 11417,		//下发杀怪统计信息
	SM_NOTIFY_KILL_MONSTER_CHANGE		= 11418,		//下发杀怪数变化信息

	SM_NOTIFY_DEPOT_CURRENCY_INFO		= 11419,		//下发仓库货币信息
	SM_NOTIFY_DEPOT_INFO				= 11420,		//下发仓库信息
	SM_NOTIFY_DEPOT_ITEM				= 11421,		//下发仓库物品
	//好友系统
	SM_SEND_FRIEND_LIST					= 11422,		//下发好友列表
	SM_SEND_SIFT_FRIEND					= 11423,		//下发筛选好友
	SM_SEND_FRIEND_REQUEST				= 11424,		//下发好友请求
	SM_SEND_FRIEND_REWARD				= 11425,		//下发好友奖励
	
	SM_NOTIFY_EQUIP_UP_STAR				= 11426,		//装备强化公告
	//交易
	SM_SEND_ASK_TRADE					= 11427,		//发送交易请求
	SM_TRADE_ITEM_CHANGE				= 11428,		//下发交易栏物品变化
	SM_TARGET_TRADE_ITEM_CHANGE			= 11429,		//通知对方交易栏物品变化
	SM_TRADE_MONEY_CHANGE				= 11430,		//下发交易栏金钱变化
	SM_TARGET_MONEY_CHANGE				= 11431,		//通知对方交易栏金钱变化
	SM_SEND_TRADE_SUCCEED				= 11432,		//通知交易成功
	SM_SEND_OPERATE_TO_TARGET			= 11433,		//把操作通知对方

	//装备赎回
	SM_SEND_RANSOM_INFO					= 11434,		//发送装备赎回信息
	SM_SEND_SPOILS_INFO					= 11435,		//发送战利品信息
	//邮件					
	SM_SEND_MAIL_LIST					= 11436,		//发送邮件列表
	SM_SEND_MAIL_CONTENT				= 11437,		//发送邮件内容
	SM_SEND_NEW_MAIL					= 11438,		//发送新邮件
	//商城
	SM_SEND_ITEM_LIMIT_COUNT			= 11439,		//发送商城限制个数
	//法宝
	SM_SEND_FA_BAO_INFO					= 11440,		//发送法宝信息
	SM_SEND_FA_BAO_GONG_GAO				= 11441,		//法宝公告
	//发送boss信息
	SM_SEND_BOSS_INFO					= 11442,		//发送boos信息
	SM_SEND_BOSS_GONG_GAO				= 11443,		//BOSS死亡复活公告
	//发送战斗力信息
	SM_SEND_BATTLE_INFO					= 11444,		//发送战斗信息
	//爵位
	SM_SEND_JUE_WEI_DONATE_MONEY		= 11445,		//发送爵位捐献的铜钱
	SM_SEND_JUE_WEI_RANK				= 11446,		//发送爵位个人排行
	SM_SEND_JUE_TOTAL_RANK				= 11447,		//发送爵位总排行榜
	SM_SEND_JUE_WEI_GONG_GAO			= 11448,		//公告

	//答题活动
	SM_SEND_DA_TI_READY_START			= 11450,		//准备开始
	SM_SEND_DA_TI_RANK					= 11451,		//发送排行榜
	SM_SEND_QUESTIONS_TO_CLIENT			= 11452,		//发送问题给客户端
	SM_SEND_CHAR_DA_TI_INFO				= 11453,		//发送个人信息
	SM_SEND_DA_TI_HUO_DONG_ID			= 11454,		//发送答题活动id

	//爬塔副本
	SM_SEND_ZSZZ_DUNGEON_RANK			= 11456,		//发送诸神之战副本信息
	SM_ZSZZ_DUNGEON_GONG_GAO			= 11457,		//通关公告
	//通知活动图标
	SM_SEND_ALL_ICON					= 11458,		//登陆下发所有活动图标
	SM_SEND_ONE_ICON					= 11459,		//下发单个活动图标
	//抽奖系统
	SM_SEND_CHOU_JIANG_RECORD			= 11465,		//发送个人抽奖记录
	SM_SEND_ADD_CHOU_JIANG_RECORD		= 11466,		//增加一条个人抽奖记录
	SM_SEND_GLOBAL_CHOU_JIANG_RECORD	= 11467,		//发送全服抽奖记录
	SM_SEND_ADD_GLOBAL_CHOU_JIANG_RECORD= 11468,		//增加一条全服抽奖记录
	SM_SEND_SCORE_SHOP_LIMIT_INFO		= 11469,		//商城限制信息
	SM_SEND_ALL_CHOU_JIANG_ITEM			= 11470,		//发送抽奖背包信息
	SM_SEND_CHOU_JIANG_ITEM_CHANGE		= 11471,		//发送抽奖背包物品改变
	SM_SEND_CHOU_JIANG_GONG_GAO			= 11472,		//发送抽奖公告
	SM_SEND_GET_ITEM					= 11473,		//抽奖抽到的物品
	//祈福系统
	SM_SEND_QI_FU_INFO					= 11475,		//发送祈福信息
	SM_SEND_QI_FU_SUCCESS				= 11476,		//发送祈福成功
	//提示信息
	SM_GM_BROADCAST						= 11477,		// GM后台发送公告
	SM_SEND_NOTICE_PARAM				= 11478,		//发送提示信息参数
	//大胃王
	SM_SEND_DWW_INFO					= 11479,		//发送大胃王信息
	//活动大厅数据
	SM_SEND_HD_DA_TING_INFO				= 11480,		//发送活动大厅数据
	//VIP
	SM_SEND_VIP_INFO					= 11481,		//发送vip信息
	// boss之间
	SM_SEND_BOSS_HOME_INFO				= 11485,		//发送boss之家信息
	SM_SEND_BOSS_CHANGE					= 11486,		//boss信息改变
	// 采集
	SM_PLANT_GAIN_ITEM					= 11489,		//发送采集获取物品
	//资源找回
	SM_SEND_SEARCH_BACK_INFO			= 11490,		//发送资源找回信息
	//经验球
	SM_SEND_EXP_BALL_INFO				= 11491,		//发送经验球信息
	//运营活动
	SM_SEND_SHOU_CHONG_INFO				= 11492,		//发送首冲信息
	SM_SEND_NEW_SERVER_FAVORABLE		= 11493,		//发送新服特惠信息
	SM_SEND_EVERYDAY_CHONG_ZHI			= 11494,		//发送每日充值信息
	SM_SEND_TOTAL_CHONG_ZHI				= 11495,		//累计充值信息

	//投资
	SM_SEND_TOU_ZI_INFO					= 11496,		//发送投资信息
	SM_SEND_GET_RESULT					= 11497,		//领取成功
	SM_SEND_TOU_ZI_RECORD				= 11498,		//发送投资记录
	// 开服活动
	SM_SEND_KAI_FU_HUO_DONG_INFO		= 11500,		//发送开服活动信息
	SM_SEND_KAI_FU_HUO_DONG_STATE		= 11501,		//发送活动状态
	// 活跃度
	SM_SEND_HUO_YUE_DU_INFO				= 11502,		//发送活跃度信息
	//官位
	SM_SEND_GUAN_WEI_INFO				= 11504,		//发送官位信息
	SM_SEND_QI_SHI_INFO					= 11505,		//发送骑士信息
	//成就
	SM_SEND_ACHIEVEMENT_INFO			= 11510,		//发送成就系统信息
	//发送抗战胜利活动奖励
	SM_SEND_WAR_VICTORY_INFO			= 11515,		//发送抗战胜利活动信息
	/*
	* SM_WMF	11700~11899
	*/

	SM_UPDATE_FIGHT_STATE				= 11700,	// 更新战斗状态

	//背包
	SM_SEND_BAG_DIRTY					= 11703,	// 下发背包脏数据
	SM_SEND_BAG_INFO					= 11704,	// 下发背包数据
	SM_SEND_BAG_SELL_ITEMS				= 11705,	// 下发回购信息
	SM_SEND_CHAR_SHOP_LINIT				= 11706,	// 个人商店限购信息

	// 装备栏
	SM_SEND_EQUIP_INFO					= 11710,	// 发送装备信息
	SM_SEND_GEM_INFO					= 11711,	// 发送宝石镶嵌信息
	SM_SEND_OPEN_GEM_HOLE				= 11712,	// 发送宝石开孔信息
	// 货币
	SM_SEND_CURRENCY_INFO				= 11720,	// 发送货币信息

	// 幻兽
	SM_SEND_PET_INFO					= 11730,	// 发送幻兽信息
	SM_SEND_PET_EGG_INFO				= 11731,	// 发送宠物蛋信息
	SM_SEND_PET_LIST					= 11732,	// 发送玩家幻兽列表
	SM_SEND_PET_LEARN_NEW_SKILL			= 11733,	// 发送幻兽学习到新技能
	SM_PET_BROADCASE					= 11734,	// 幻兽公告
	SM_SEND_PET_STATUS					= 11735,	// 幻兽状态更新包（区域发送）

	// XP技能
	SM_XP_INFO							= 11740,	// XP信息
	SM_SEND_XP_EXP_BOARD				= 11741,	// 组队XP结算面板

	// 宠物排行榜
	SM_PET_RANK_INFO					= 11750,	// 宠物排行榜信息
	SM_PET_RANK_LIST					= 11751,	// 宠物排行榜
	SM_PET_SET_FIGHT					= 11752,	// 宠物出战屏幕内特效

	// 副本
	SM_DUNGEON_INFO_BOARD				= 11760,	// 下发副本信息面板

	// 组队副本
	SM_TEAM_DUNGEON_SEND_LIST			= 11770,	// 下发组队副本列表
	SM_TEAM_DUNGEON_MEMBER_INFO			= 11771,	// 下发组队副本成员信息
	SM_TEAM_DUNGEON_MEMBER_LEAVE		= 11772,	// 下发玩家离开组队副本信息
	SM_TEAM_DUNGEON_START				= 11773,	// 下发组队副本开启（倒计时开始）
	SM_TEAM_DUNGEON_DAMAGE_LIST			= 11774,	// 下发组队副本伤害统计

	// 灵兽
	SM_INSIDE_PET_SEND_BASE_INFO		= 11780,	// 下发灵兽信息
	SM_INSIDE_PET_SEND_BASE_ILLUSION	= 11781,	// 下发灵兽初灵信息

	// 游戏排行榜
	SM_GAME_RANK_DATA					= 11790,	// 下发游戏排行榜
	SM_SELF_WORSHIP_INFO				= 11791,	// 下发玩家自身崇拜信息
	SM_NOTIFY_WORSHIP_INFO				= 11792,	// 下发玩家崇拜信息

	// 拍卖
	SM_AUCTION_ITEM_LIST				= 11800,	// 下发拍卖数据
	SM_AUCTION_SELF_ITEMS				= 11801,	// 下发自身数据
	SM_AUCTION_RECORD					= 11802,	// 下发交易记录
	SM_AUCTION_SELL_ITEM				= 11803,	// 下发上架成功信息

	// 活动
	SM_NOTIFY_ACTIVITY_INFO				= 11810,	// 下发活动信息
	SM_NOTIFY_ACTIVITY_FAMILY_SCORE		= 11811,	// 下发活动面板
	SM_NOTIFY_ACTIVITY_PLAYER_SCORE		= 11812,	// 下发活动面板
	SM_NOTIFY_FAMILY_WAR_PILLAR_INFP	= 11813,	// 下发战神之柱信息
	SM_NOTIFY_ACTIVITY_SCORE			= 11814,	// 下发活动面板信息
	SM_NOTIFY_ACTIVITY_RESULT			= 11815,	// 下发活动结果
	SM_NOTIFY_ACTIVITY_TERRITORY_INFO	= 11816,	// 下发领地战信息
	SM_NOTIFY_FAMILY_WAR_WIN_FAMILY		= 11817,	// 军团战胜利军团
	// 魂力
	SM_SOUL_INFO						= 11900,	// 下发魂力信息

	// 名人堂
	SM_HALL_OF_FAME_INFO				= 11910,	// 名人堂界面信息
	SM_HALL_OF_FAME_BATTLE				= 11911,	// 名人堂战斗结果
	SM_HALL_OF_FAME_RANK_INFO			= 11912,	// 名人堂排行榜

	/*
	* SM_WXJ	11900~11999
	*/

	SM_MAX,

	SM_GM_MIN				= 19000,
	SM_GM_CHAT				= 19001,

	SM_PHP_MIN				= 19500,
	SM_PHP_BUY				= 19501,
	SM_PHP_MAX,
};

/*
* IM_MIN							= 20000,
* IM_SOCIAL_GLOBAL_MIN,
* IM_SOCIAL_GAME_MIN,
* IM_SOCIAL_SPECIFIC_GAME_MIN,
* IM_SOCIAL_ALL_GAME_MIN,
* IM_GAME_SOCIAL_MIN,
* IM_DB_GAME_SERVICE_CONNECT,
* IM_DB_LOG_ARTIFACT_ADD_EXP,
* IM_PHP_MIN						= 25000,
*/
enum MSG_IM_CODE
{
	IM_MIN = 20000,
	IM_CHARACTER_SERVICE_CONNECT,
	IM_GAME_SERVICE_CONNECT,
	IM_LOGIN_SERVICE_CONNECT,
	IM_SOCIAL_SERVICE_CONNECT,
	IM_GAME_GATE_USER_SAVED,
	IM_GATE_ADD_USER,
	IM_GATE_REMOVE_USER,
	IM_GATE_UPDATE_BAN_CHAT,
	IM_GATE_RELOAD_ITEM,
	IM_GAME_GATE_KICK_USER,
//================================================================
	IM_SOCIAL_GLOBAL_MIN,
	IM_SOCIAL_ADD_PLAYER_INFO,		//废弃
	IM_SOCIAL_UPDATE_PLAYER_INFO,
	IM_SOCIAL_ADD_PLAYER,
	IM_SOCIAL_REMOVE_PLAYER,
	IM_SOCIAL_REMOVE_FAMILY_APPLIER,		// 废弃
	IM_SOCIAL_DELETE_CHARACTER,				// 废弃
	IM_SOCIAL_NEW_MINUTE_COME,
	IM_SOCIAL_SEND_MAIL,
	IM_SOCIAL_FAMILY_WAR,
	IM_SOCIAL_ACTIVITY_CLEAR,
	IM_SOCIAL_ADD_KILLER,					// 废弃
	IM_SOCIAL_UPDATE_GAMBLE,				// 废弃
	IM_SOCIAL_FAMILY_ACTIVITY_PLAYER,		// 废弃
	IM_SOCIAL_WORLD_BOSS_ACTIVITY_RESULT,	// 废弃
	IM_SOCIAL_REAL_TIME_RANK_RESET,			// 废弃

	IM_SOCIAL_UPDATE_PET_DATA,		// 更新宠物排行榜信息
	IM_SOCIAL_DELETE_PET_DATA,		// 更新宠物排行榜信息

	IM_SOCIAL_REQUEST_PET_RANK_DATA,	// 游戏服请求宠物排行榜信息

	IM_SOCIAL_DA_TI_START_READY,		// 准备开始答题
	IM_SOCIAL_DA_TI_START,				// 答题活动开始
	IM_SOCIAL_DA_TI_END,				// 答题活动结束
	IM_SOCIAL_QUESTIONS,				// 发送题目信息
	IM_SOCIAL_RAND_ANSWER,				// 随机答案
	IM_SOCIAL_UPDATE_ZSZZ,				// 更新诸神之战副本信息
	IM_SOCIAL_SYN_SERVER_DAY,			// 开服第几天
	IM_SOCIAL_REQUEST_FAMILY_INFO,		// 请求一下军团信息
	IM_SOCIAL_GLOBAL_MAX,

//===================================================
	IM_SOCIAL_GAME_MIN,
	//IM_SOCIAL_GAME_SYN_FAMILY_LEVEL,
	//IM_SOCIAL_GAME_CHANGE_FAMILY_INFO,
	IM_SOCIAL_GAME_SEND_MAIL,
	IM_SOCIAL_GAME_SEND_MAIL_INFO,
	IM_SOCIAL_GAME_GET_MAIL_POST,
	IM_SOCIAL_GAME_USE_EXCHANGE_CODE,
	//IM_SOCIAL_GAME_CHANGE_FAMILY_NAME,
	IM_SOCIAL_GAME_GOTO_ENEMY,							// 废弃
	//IM_SOCIAL_GAME_LEADER_DOWN,
	//IM_SOCIAL_GAME_UPDATE_LEADER_CID,
	//IM_SOCIAL_GAME_UPDATE_FAMILY_CONTRIBUTE,

	// 帮派
	IM_SOCIAL_GAME_CREATE_FAMILY,						// 创建帮派
	IM_SOCIAL_GAME_UPDATE_FAMILY,						// 更新玩家帮派信息
	IM_SOCIAL_GAME_NEED_UPDATE_FAMILY,					// 帮派信息更新

	// 组队
	IM_SOCIAL_GAME_UPDATE_TEAM_INFO,

	// 崇拜
	IM_SOCIAL_GAME_WORSHIP,								// 崇拜

	// XP
	IM_SOCIAL_GAME_UPDATE_XP,							// 同步XP信息
	IM_SOCIAL_GAME_ADD_XP,								// 组队XP经验结算信息

	// 组队副本
	IM_SOCIAL_GAME_TEAM_DUNGEON_START,					// 组队副本开始
	IM_SOCIAL_GAME_TEAM_DUNGEON_UPDATE_INFO,			// 组队副本信息更新

	// 拍卖
	IM_SOCIAL_GAME_AUCTION_SELL,						// 物品上架
	IM_SOCIAL_GAME_AUCTION_BUY,							// 购买物品
	IM_SOCIAL_GAME_ADD_CURRENCY,						// 添加货币

	// 活动
	IM_SOCIAL_GAME_FAMILYWAR_PILLAR_ADD_MONEY,			// 战神之柱注入军团资金

	// 名人堂
	IM_SOCIAL_GAME_HALL_OF_FAME_FIGHT_RESULT,			// 名人堂挑战结果
	IM_SOCIAL_GAME_HALL_OF_FAME_GET_REWARD,				// 名人堂领取奖励
	IM_SOCIAL_GAME_HALL_OF_FAME_RANK_REWARD_INFO,		// 名人堂排行榜奖励信息

	// 好友
	IM_SOCIAL_GAME_UPDATE_FRIEND_LEVEL_UP,				//好友升级
	IM_SOCIAL_GAME_SEND_JUE_WEI_RANK,					//发送爵位排行榜
	IM_SOCIAL_GAME_ALREADY,								//答题记录
	IM_SOCIAL_GAME_ADD_FRIEND,							//成就里的统计
	//抽奖
	IM_SOCIAL_GAME_ASK_CHOU_JIANG,						//请求抽奖
	// 购买全服限制物品
	IM_SOCIAL_GAME_BUY_LIMIT_ITEM,						// 购买全服限制物品			
	IM_SOCIAL_GAME_MAX,
//=======================================================
	IM_SOCIAL_SPECIFIC_GAME_MIN,
	IM_SOCIAL_GAME_ADD_APPLIER,							// 废弃
	IM_SOCIAL_GAME_REAL_TIME_RANK_BASE,					// 废弃
	IM_SOCIAL_SPECIFIC_GAME_MAX,

	IM_SOCIAL_ALL_GAME_MIN,
	IM_SOCIAL_ALL_GAME_UPDATE_PET_RANK,					// 更新宠物排行榜
	IM_SOCIAL_ALL_GAME_UPDATE_FAMILY,					// 更新帮派信息
	IM_SOCIAL_ALL_GAME_CHANGE_OWNER,					// 宠物、装备变更所有者
	IM_SOCIAL_ALL_GAME_KAI_FU_HUO_DAO_RANK,				// 同步开服活动排行榜
	IM_SOCIAL_ALL_GAME_MAX,

	IM_SOCIAL_SINGLE_GAME_MIN,
	IM_SOCIAL_SINGLE_GAME_INIT_PET_RANK,				// 初始化宠物排行榜
	IM_SOCIAL_SINGLE_GAME_TEAM_DUNGEON_CREATE,			// 创建组队副本
	IM_SOCIAL_SINGLE_GAME_DA_TI_RANK,					// 发送答题排行榜到游戏服
	IM_SOCIAL_SINGLE_GAME_SEND_SYSTEM_MAIL,				// 发送系统邮件
	IM_SOCIAL_SINGLE_GAME_SEND_SYSTEM_MAIL2,			// 发送系统邮件
	IM_SOCIAL_SINGLE_GAME_MAX,

	//社会内部
	IM_GAME_SOCIAL_MIN,
	IM_GAME_SOCIAL_CREATE_FAMILY,
	IM_GAME_SOCIAL_SEND_MAIL,
	IM_GAME_SOCIAL_GET_MAIL_POST,
	IM_GAME_SOCIAL_ADD_CONTRIBUTION,
	IM_GAME_SOCIAL_USE_EXCHANGE_CODE,
	IM_GAME_SOCIAL_CHANGE_NAME,
	IM_GAME_SOCIAL_CHANGE_FAMILY_NAME,
	IM_GAME_SOCIAL_GOTO_ENEMY,
	IM_GAME_SOCIAL_BREAK_FAMILY,
	IM_GAME_SOCIAL_UPDATE_ZHENLONGZHIQI,

	IM_GAME_SOCIAL_ADD_FAMILY_CONTRIBUTE,		// 军团捐献
	IM_GAME_SOCIAL_UPDATE_PET_CONTRIBUTE,		// 同步玩家军团贡献度
	IM_GAME_SOCIAL_FAMILY_REGIST_PET,			// 军团幻兽登记
	IM_GAME_SOCIAL_FAMILY_UNREGIST_PET,			// 军团幻兽取消登记
	IM_GAME_SOCIAL_FAMILY_TASK_COUTN,			// 增加军团任务完成次数
	IM_GAME_SOCIAL_FAMILY_ADD_CONTRIBUTION,		// 增加军团贡献
	IM_GAME_SOCIAL_SET_TEAM_AUTO_OPERATE,		// 组队默认设置
	IM_GAME_SOCIAL_LEAVE_TEAM,					// 强制离开队伍

	IM_GAME_SOCIAL_WORSHIP,						// 添加崇拜记录
	IM_GAME_SOCIAL_AUCTION_SELL,				// 拍卖行售卖
	IM_GAME_SOCIAL_AUCTION_BUY,					// 拍卖行购买
	IM_GAME_SOCIAL_STALL,						// 摆摊

	IM_GAME_SOCIAL_ADD_XP,						// XP值增加
	IM_GAME_SOCIAL_START_XP,					// 开始XP技能
	IM_GAME_SOCIAL_END_XP,						// 结束XP技能
	IM_GAME_SOCIAL_BREAK_XP,					// 跳过XP技能
	IM_GAME_SOCIAL_RESET_XP,					// 死亡重置xp

	IM_GAME_SOCIAL_TEAM_DUNGEON_CREATE,			// 创建组队副本
	IM_GAME_SOCIAL_TEAM_DUNGEON_JOIN,			// 加入组队副本
	IM_GAME_SOCIAL_TEAM_DUNGEON_START,			// 开启组队副本
	IM_GAME_SOCIAL_TEAM_DUNGEON_LEAVE,			// 离开组队副本

	IM_GAME_SOCIAL_NOTIFY_FAMILYWAR_INFO,		// 下发军团战信息
	IM_GAME_SOCIAL_FAMILYWAR_ADD_PILLAR_MONEY,	// 战神之柱注入资金

	IM_GAME_SOCIAL_HALL_OF_FAME_FIGHT,			// 名人堂挑战
	IM_GAME_SOCIAL_HALL_OF_FAME_REQUEST_INFO,	// 名人堂请求界面信息
	IM_GAME_SOCIAL_HALL_OF_FAME_REWARD_RESULT,	// 名人堂领取奖励返回

	IM_GAME_SOCIAL_ADD_ENEMY,					// 被杀添加仇人
	IM_GAME_SOCIAL_JUE_WEI_DONATE_MONEY,		// 同步爵位捐献
	IM_GAME_SOCIAL_ASK_JUE_WEI_RANK,			// 请求爵位排行榜
	IM_GAME_SOCIAL_ASK_LIMIT_SHOP_INFO,			// 请求全服限制物品信息
	IM_GAME_SOCIAL_BUY_LIMIT_SHOP_ITEM,			// 购买全服限制物品
	IM_GAME_SOCIAL_BUY_LIMIT_SHOP_SUCCEED,		// 购买全服限制物品成功
	IM_GAME_SOCIAL_ADD_CHOU_JIANG_RECORD,		// 增加全服抽奖记录
	IM_GAME_SOCIAL_CLEAN_GLOBAL_POINT,			// 清除抽奖全服幸运值
	IM_GAME_SOCIAL_CHECK_GLOBAL_POINT,			// 检测全服幸运值
	IM_GAME_SOCIAL_ASK_CHOU_JIANG_RECORD,		// 请求发送抽奖记录给客户端
	IM_GAME_SOCIAL_ADD_TOU_ZI_RECORD,			// 增加投资记录

	IM_GAME_SOCIAL_QUERY_PLAYER_INFO,
	IM_GAME_SOCIAL_UPDATE_ACTIVITY_STATE,
	IM_GAME_SYN_DAY_SWITCH,			//同步跨天
	IM_GAME_SOCIAL_MAX,
	//社会结束
	

	IM_DB_GAME_SERVICE_CONNECT,
	IM_DB_LOAD_PLAYER,
	IM_DB_PLAYER_LOADED,
	IM_DB_SAVE_PLAYER,
	IM_DB_SAVE_COLTH,
	IM_DB_PLAYER_SAVED,
	IM_DB_INSERT_EQUIP,
	IM_DB_UPDATE_EQUIP,
	IM_DB_DELETE_EQUIP,
	IM_DB_EQUIP_UPDATED,
	IM_DB_UPDATE_FAMILY_WAR,		// 废弃
	IM_DB_FAMILY_WAR_UPDATED,		// 废弃
	IM_DB_INSERT_LACKEY,			// 废弃
	IM_DB_INSERT_ITEM,
	IM_DB_UPDATE_ITEM,
	IM_DB_DELETE_ITEM,
	IM_DB_ITEM_UPDATED,

	IM_DB_INSERT_PET,
	IM_DB_UPDATE_PET,
	IM_DB_DELETE_PET,
	IM_DB_PET_UPDATED,
	IM_DB_PET_DELETED,

	IM_DB_LOG_ARTIFACT_ADD_EXP,
	IM_DB_LOG_ARTIFACT_ADD_MAX_LEVEL,
	IM_DB_LOG_ARTIFACT_ADD_QUALITY,
	IM_DB_LOG_EQUIP_ADD_GEM,
	IM_DB_LOG_EQUIP_ADD_GEM_SLOT,
	IM_DB_LOG_EQUIP_APPEND_STAR,
	IM_DB_LOG_EQUIP_COMBINE,
	IM_DB_LOG_EQUIP_FORGE,
	IM_DB_LOG_EQUIP_LIFE,
	IM_DB_LOG_EQUIP_REFRESH_BIND,
	IM_DB_LOG_EQUIP_REFRESH_ELEMENT,
	IM_DB_LOG_EQUIP_REFRESH_FLOAT_ATTR,
	IM_DB_LOG_EQUIP_REMOVE_GEM,
	IM_DB_LOG_EQUIP_REMOVE_STAR,
	IM_DB_LOG_EQUIP_STRENGTHEN,
	IM_DB_LOG_EQUIP_UPGRADE,

	IM_DB_LOG_PLAYER_LOGIN,
	IM_DB_LOG_PLAYER_DEAL,
	IM_DB_USER_PAYED,
	IM_DB_LOG_TASK_RECEIVE,
	IM_DB_LOG_TASK_SUBMIT,
	IM_DB_LOG_EQUIP_ENHANCE,
	IM_DB_LOG_ITEM_COMBINE,
	IM_DB_LOG_EQUIP_SMITHING,// 合成装备.宝石
	IM_DB_LOG_EQUIP_MAGIC_SMITH,//打造装备
	IM_DB_LOG_EQUIP_DISMANTLE,
	IM_DB_LOG_IN_DUNGEON,
	IM_DB_LOG_OUT_DUNGEON,
	IM_DB_LOG_CREATE_FAMILY,
	IM_DB_LOG_JOIN_FAMILY,
	IM_DB_LOG_OUT_FAMILY,
	IM_DB_LOG_ACHIEVEMENT,
	IM_DB_LOG_PK,
	IM_DB_LOG_ACTIVITY_DATA,			// 活动日志
	IM_DB_LOG_ITEM_CHANGE,
	IM_DB_LOG_KILL_BOSS,				// BOSS击杀日志
	IM_DB_LOG_DAILY_GIFT,				// 每日礼包领取日志
	IM_GATE_QQ_TO_PLAYER,				// 从QQ平台传过来的传到player中
	IM_DB_INSERT_MEMYELLOWSTONE,		// 记录黄钻领取记录
	IM_DB_LOG_VICEGENERAL_CHANGE,		// 副将招募解雇log
	IM_DB_LOG_CURRENCY,					// 货币日志
	IM_DB_ADD_RANSOM_INFO,				// 增加赎回物品
	IM_DB_DLE_RANSOM_INFO,				// 删除赎回物品
	IM_DB_UPDATE_RANSOM,				// 更新赎回信息
	IM_DB_SEND_MAIL_TO_DB,				// 发送邮件到dbserver
	IM_DB_UPDATE_NEW_MAIL,				// 更新新邮件到gameserver
	IM_DB_NEW_MINUTE,
	IM_DB_SAVE_FAMILY_WAR_RESULT,		// 存储军团战结果
	IM_DB_UPDATE_FAMILY_WAR_RESULT,		// 更新军团战结果到各条线路
	IM_DB_SAVE_TERRITORY_WAR_RESULT,	// 存储领地战结果
	IM_DB_UPDATE_TERRITORY_WAR_RESULT,	// 更新领地战结果到各条线路
	IM_DB_UPDATE_LOGIN_TIME,			// 更新标记进入时间			
	IM_DB_UPDATE_GM_BROADCAST,			// 更新公告		
	IM_DB_UPDATE_GM_BAN_CHAT,			// 更新禁言	
	IM_DB_UPDATE_GM_SEAL,				// 更新封号

	IM_PHP_MIN = 25000,
	IM_DB_USER_PAY = 25001,
	CM_GATE_PHP_PROP,

	IM_MAX,
};
