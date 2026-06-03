#pragma once

#include <list>
#include <map>
#include <vector>

typedef std::list<int32_t> Int32List;
typedef std::list<CharId_t> CharIdList;
typedef std::list<PetId_t> PetIdList;
typedef std::vector<int16_t> Int16Vector;

enum PlayerTitleType
{
	PTT_BAWANG = 1,//霸王
	PTT_GUOJUN = 2,//国君
	PTT_WUSHEN = 3,//武神
	PTT_ZHUHOU = 4,//诸侯
	PTT_WUZUN = 5,//武尊
	PTT_DIYIGAOSHOU = 6,//第一高手
	PTT_DAFUWENG = 7,//大富翁
};

//enum ActivityNewId
//{
//	AI_KINGDOMWAR	=1,				//楚汉争霸
//	AI_DIGUOWAR		,				//敌国攻城
//	AI_GUOJIAWAR	,				//国家战场
//	AI_KIHNGDOMPK	,				//武神大赛
//	AI_MATCHWAR		,				//比武大赛
//	AI_KINGFAMILYWAR,				//国君继位塞
//	AI_BANQUET,						//宴会对酒
//	AI_ZHUGONGZHENGDUOZHAN1,		//主公争夺战
//	AI_ZHUGONGZHENGDUOZHAN2,		//主公争夺战
//	AI_OTHER		=100,			//其他
//};

//enum ActivityWeal
//{
//	WEAL_JIANGXING =1,
//	WEAL_WUHUN,
//	WEAL_JUNGONG,
//	WEAL_GUOJIA,//国家贡献 
//};

enum signActionType
{
	SAT_REFRESH = 1,
	SAT_INSERT = 2,
	SAT_SIGN_BENGIN = 3,
	SAT_SIGN_END = 4,
	SAT_GET_BENGIN = 5,
	SAT_GET_MID = 6,
	SAT_GET_END = 7,
};

struct ActivityRank
{
	int32_t acId;
	int32_t rank;
	char name[MAX_NAME_CCH_LENGTH];
	int32_t date;
	int32_t jifen;
	int32_t count;
	int32_t kingdom;
};
typedef std::vector<ActivityRank> ActivityRankVector;
typedef std::vector<ActivityRank *> ActivityRankPtrVector;

struct CfgActivity
{
	int32_t id;
	Int32Vector weekday;
	int32_t  startTime;
};
typedef std::map<int32_t,CfgActivity>CfgActivityTable;

struct FriendInfo
{
	CharId_t	Cid;
	int32_t		Level;
	Sex_t		Sex;
	Job_t		Job;
	std::string	Name;
	int32_t		LogOutTime;
	int8_t		FriendType;
};

enum RelationType
{
	RLT_FRIEND			= 1,	// 好友
	RLT_ENEMY			= 2,	// 仇人
	RLT_BLACKLIST		= 3,	// 黑名单
	RLT_IN_BLACKLIST	= 4,	// 把我加黑名的玩家
};

enum FamilyPostType
{
	FPR_NOTICE = 1,
	FPR_INTRO = 2,
};

enum FamilyPartsType
{
	FPT_BASE = 0,
	FPT_FARM = 1,
	FPT_POOL = 2,
	FPT_TREE = 3,
};

enum FamilyEventType
{
	FET_APPOINT			= 1,		// 任命帮派职位
	FET_APPROVE			= 2,		// 批准加入帮派
	FET_KICK			= 3,		// 踢出帮派
	FET_LEAVE			= 4,		// 离开帮派
	FET_ACTIVE_TOTOM	= 5,		// 激活图腾
	FET_DESTROY			= 6,		// 解散帮派
	FET_LEVEL_CHANGE	= 7,		// 帮派等级变化
	FET_REGIST_PET		= 8,		// 登记幻兽
	FET_POSITION_UP		= 9,		// 职位晋升
	FET_UN_HONOR_POS	= 10,		// 罢免
};

enum AuctionAction
{
	AA_BUY,
	AA_SELL,
	AA_CANCEL,
	AA_GETMONEY,
};

typedef std::list<int16_t> Int16List;
typedef std::vector<int32_t> Int32Vector;
typedef std::map<int32_t, int32_t> Int32Int32Map;
typedef std::map<int32_t, Int32Vector> Int32Int32VectorMap;

struct FamilyDBData
{
	FamilyDBData()
		:nFamilyId(0),nLevel(0),nMoney(0),AutoAgree(0),FamilyTaskCount(0),LastFamilyTaskTime(0)
	{	
	}
	FamilyId_t	nFamilyId;
	std::string	strName;
	int32_t		nLevel;
	int32_t		nMoney;
	std::string	strNotice;
	int8_t		AutoAgree;
	int32_t     FamilyTaskCount;
	int32_t     LastFamilyTaskTime;
};

#define FAMILY_LOG_SIZE			50	// 帮派日志保留大小
enum FAMILY_LOG_TYPE
{
	FLT_MEMBER_LEAVE	= 1,		// 玩家离开军团
	FLT_MEMBER_JOIN		= 2,		// 玩家加入军团
	FLT_LEVEL_UP		= 3,		// 军团等级提升
	FLT_GOLD			= 4,		// 捐献魔石
	FLT_MONEY			= 5,		// 捐献金币
	FLT_APPOINT			= 6,		// 任命职位
	FLT_KICK			= 7,		// 踢人
	FLT_UN_APPOINT		= 8,		// 解除职位
	FLT_POSITION_UP		= 9,		// 职位提升
	FLT_ACTIVE_TOTOM	= 10,		// 激活图腾
	FLT_LEVEL_DOWN		= 11,		// 军团等级下降
	FLT_REGIST_PET		= 12,		// 登记幻兽
	FLT_POSITION_DOWN	= 13,		// 职位降低
	FLT_UNREGIST_PET	= 14,		// 解除幻兽
	FLT_FAMILY_TASK		= 15,		// 军团任务
};
struct FamilyLog 
{
	int8_t	nType;
	int64_t	vParam[5];
	int32_t	nTime;
};
typedef std::list<FamilyLog> FamilyLogList;

class PlayerInfo 
{
public:
	void reset()
	{
		nCharId					= 0;
		strName					= "";
		nSex					= 0;
		nJob					= 0;
		nLevel					= 0;
		nLastLogoutTime			= 0;
		nBattle					= 0;
		bLearnedXP				= false;
		nVip					= 0;
		nTitle					= 0;
		nJueWei					= 0;
		nWeapon					= 0;
		nCloth					= 0;
		nWorshipRecord			= 0;

		nFamilyId				= 0;
		nFamilyPosition			= 0;
		nFamilyContribution		= 0;
		nFamilyPetContribution	= 0;
		nFamilyApplyCount		= 0;
		nGuanWei				= 0;
	}

	int32_t GetFamilyContribution() const
	{
		return nFamilyContribution + nFamilyPetContribution;
	}
	CharId_t		nCharId;
	std::string		strName;
	Sex_t			nSex;
	Job_t			nJob;
	int32_t			nLevel;
	int32_t			nLastLogoutTime;
	int32_t			nBattle;
	bool			bLearnedXP;
	int8_t			nVip;
	int8_t			nVipLevel;
	int32_t			nVipEndTime;
	int32_t			nTitle;
	int8_t			nJueWei;
	int32_t			nWeapon;
	int32_t			nCloth;
	int32_t			nWorshipRecord;
	int32_t			nGuanWei;

	// 军团信息
	FamilyId_t		nFamilyId;									// 军团ID
	int8_t			nFamilyPosition;							// 军团职务 FAMILY_POSITION
	int32_t			nFamilyContribution;						// 贡献度
	int32_t			nFamilyPetContribution;						// 军团宠物总贡献度
	int8_t			nFamilyApplyCount;							// 申请个数
};
typedef std::map<CharId_t, PlayerInfo*> CharIdPlayerInfoMap;
typedef std::map<std::string, PlayerInfo*> StringPlayerInfoMap;
typedef std::vector<PlayerInfo*> PlayerInfoVector;
typedef std::vector<PlayerInfo> PlayerInfoVt;
struct PetRankData 
{
	PetRankData()
	{
	}
	PetRankData( int32_t baseId, int32_t points, const std::string& name, CharId_t ownerId, const std::string& ownerName, PetId_t PetId )
		:nBaseId( baseId ), nPoints( points ), strName( name ), nOwnerId( ownerId ), strOwnerName( ownerName ), nPetId( PetId )
	{
	}

	PetId_t		nPetId;
	int32_t		nBaseId;
	int32_t		nPoints;
	std::string	strName;
	CharId_t	nOwnerId;
	std::string	strOwnerName;
};
typedef std::vector<PetRankData> PetRankDataVector;

struct PlayerAttr 
{
	int32_t attack;
	int32_t pdef;
	int32_t mdef;
	int32_t maxhp;
	int32_t maxmp;
	int32_t vp;
	int32_t dp;
	int32_t hitp;
	int32_t prevp;
	int32_t prebk;
	int32_t prerost;
	int32_t preduce;
	int32_t mreduce;
	int32_t vpp;
};

//struct GambleRecord
//{
//	int32_t cid;
//	char name[MAX_NAME_CCH_LENGTH];
//	int32_t type;
//	int32_t item;
//	int32_t item_type;
//	int32_t count;
//};
//typedef std::vector<GambleRecord>GambleRecordVector;

struct CfgMysteriousShop//神秘商店
{
	int32_t id;
	int32_t group;
	int32_t item;
	int32_t count;
};
typedef std::vector<CfgMysteriousShop>CfgMysteriousShopVector;
typedef std::map<int32_t,CfgMysteriousShopVector>CfgMysteriousShopTable;

struct CfgMysteriousShopTime
{
	int32_t week;
	int32_t start_time;
	int32_t end_time;
	int32_t refresh_time;
};
typedef std::map<int32_t,CfgMysteriousShopTime>CfgMysteriousShopTimeTable;



struct BagSlot 
{
	int32_t bag;
	int32_t slot;
};
typedef std::vector<BagSlot> BagSlotVector;

#define  MAX_FAMILY_NAME  12

typedef std::map<int32_t, GmtBanChat> GmtBanChatTable;
typedef std::vector<MemChrBag> MemChrBagVector;


enum LEAVE_TEAM_REASON
{
	LTR_NORMAL	= 0,		// 自己退队
	LTR_KICKED	= 1,		// 被队长踢出
	LTR_DESTROY	= 2,		// 队长解散队伍
};

// 拍卖数据
struct AuctionItem 
{
	int32_t		nId;
	int32_t		nClass;
	int32_t		nCount;
	int64_t		nSrcId;
	int32_t		nPrice;
	CharId_t	nSeller;
	CharId_t	nBuyer;
	int32_t		nTime;
	int32_t		nEquipStar;
};
typedef std::map<int32_t, AuctionItem> AuctionItemMap;
typedef std::list<AuctionItem> AuctionItemList;
