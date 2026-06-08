#pragma once
//////////////////////////////////////////////////////////////////////////
//author:zxj		modify time:2012-7-7
//description:��Ϸ�нṹ�Ľṹ����
//////////////////////////////////////////////////////////////////////////

// NOTE: roundInt/RANDOM used in inline methods below.
// When this header is processed stand-alone (e.g. by tools), these stubs prevent errors.
#ifndef RANDOM
class Random { public: int generate(int,int) { return 0; } };
#define RANDOM (*(Random*)0)
#endif
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "Shared.h"
#include "../share/DataStruct.h"
#include "DataStructs.h"
#include "actStructs.h"
#include "TencentTable.h"
#include "CDaTingReward.h"
#include "XinMoTable.h"
#include "KunLingTable.h"

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

// 小助手配置
struct LittleHelperCfg
{
	LittleHelperCfg()
		: nId( 0 )
		, nSpeed( 0 )
		, nGold( 0 )
		, nReGold( 0 )
		, nTime( 0 )
		, nGongGaoId( 0 )
	{
	}

	int32_t nId;
	int32_t nSpeed;
	AddAttrList lAttr;
	int32_t nGold;
	int32_t nReGold;
	int32_t nTime;
	int32_t nGongGaoId;
};

typedef std::map<int32_t, LittleHelperCfg> LittleHelperCfgMap;


// GuardPrivilege Config
struct CfgGuardPrivilege
{
    int8_t  nIndex;
    int8_t  nType;
    int8_t  nDaily;
    int32_t nParam;
    MemChrBagVector vReward;
};
typedef std::map<int8_t, CfgGuardPrivilege> CfgGuardPrivilegeMap;

// GongMing Config
struct GongMingCfg
{
	int32_t NeedGongMingZhi;
	int32_t GongGaoId;
	int32_t nChong;
	int32_t nStar;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, GongMingCfg> GongMingCfgMap;

class ChrMount;

//����ݽṹ
struct CfgActivity 
{
	int32_t id;							// id��ʶ��
	int16_t	typeId;						// ���
	Int32Vector weekday;				// ���ʱ�䷶Χ(1234567);s
	int32_t begin_date;					// ���ʼʱ��
	int32_t end_date;					// �����ʱ��
	int32_t line;						// ����
	Int32Vector start_hour;				// ���ʱ��
	int32_t duration;					// ��ܳ���
	int32_t level;

	Int32Vector maps;					// ������ͼ
	int32_t target_mapid;				// ��ǰ�ĵ�ͼID
	Int32Vector target_regiona;			// ������1
	Int32Vector target_regionb;			// ������2
	int32_t state;						// ���״̬����
	Int32Vector gift_id;				// ��
	Int32Vector daily_reward;			// �ճ�����
	int32_t exp_add_interval;
	int32_t	iconid;						// �ͼ��ID
};
//��б�
typedef std::map<int32_t, CfgActivity> CfgActivityTable;

//�����
typedef std::list<Position> PosList;
struct CfgActivityMonster 
{
	int32_t id;
	int32_t wave;//���ﲨ��
	int32_t mid;
	int32_t x;
	int32_t y;
	int32_t count;
	int32_t side;
	PosList road;
	int32_t	delay;	// ˢ�ּ��
	int32_t	times;	// ˢ�ִ���
};
//���л�еĹ����
typedef std::map<int32_t, CfgActivityMonster> CfgActivityMonsterTable;

//�Npc
struct CfgActivityNpc 
{
	int32_t id;							//ID��ʶ��
	int32_t activity_id;				//�ID
	int32_t npc_id;						//ncp ID
	int32_t count;						//NPC����
	Int32Vector region_id;				//����IDs
};
typedef std::list<CfgActivityNpc> CfgActivityNpcList;
typedef std::map<int32_t, CfgActivityNpc> CfgActivityNpcTable;


//�ֲ��
struct CfgActivityPlant 
{
	int32_t id;							//ID��ʶ��
	int32_t activity_id;				//�ID
	int32_t plant_id;					//ֲ��ID
	int32_t count;						//ֲ�����
	int32_t wave;						//����
	int32_t region_id;					//����ID
	int32_t whoplant;					//�ɼ���
	std::vector<Position>	EnterPosVector;
};

typedef std::list<CfgActivityPlant> CfgActivityPlantList;

typedef std::map<int32_t, CfgActivityPlant> CfgActivityPlantTable;

//�������
struct CfgActivityTrap 
{
	int32_t id;
	int32_t tid;
	int32_t x;
	int32_t y;
};
typedef std::map<int32_t, CfgActivityTrap> CfgActivityTrapTable;

struct CfgActivityDrop
{
	int32_t id;
	int32_t activity_id;
	int32_t monster_min_level;
	int32_t drop_group_id;
	int32_t probability;
};
typedef std::map<int32_t, CfgActivityDrop> CfgActivityDropTable;

// 护送配置
struct CfgCarrier
{
	int32_t nId;
	std::list<int> lSkills;
};
typedef std::map<int32_t, CfgCarrier> CfgCarrierMap;

struct CfgCarrierAttr
{
	int32_t nId;
	int32_t nLevel;
	std::vector<AttrAddon> vAttr;
};
// 翅膀配置
struct WingCfg
{
	int32_t				Level;			// 翅膀等级
	ItemDataList		ConstItems;		// 升级所需材料
	int32_t				StartPoints;	// 最低幸运值
	int32_t				SuccessPoints;	// 成功幸运值（>=此值必成功）
	int32_t				MaxPoints;		// 最大幸运值
	int32_t				Rate;			// 成功率（万分比）
	int32_t				FailAddPoints;	// 失败增加的幸运值
	int32_t				SkillId;		// 技能ID
	int32_t				SkillLevel;		// 技能等级
	int32_t				IsClear;		// 是否每日清空幸运值
	int32_t				GongGaoId;		// 公告ID
	AttrAddonVector		AddonVector;	// 属性加成
};
typedef std::map<int32_t, WingCfg> WingCfgMap;

class CfgWingTable
{
public:
	CfgWingTable(){}
	~CfgWingTable(){}

	void AddWingCfg( const WingCfg& stu )
	{
		m_WingCfgMap[stu.Level] = stu;
	}

	const WingCfg* GetWingCfg( int32_t level ) const
	{
		WingCfgMap::const_iterator iter = m_WingCfgMap.find( level );
		if ( iter != m_WingCfgMap.end() )
		{
			return &iter->second;
		}
		return NULL;
	}

private:
	WingCfgMap		m_WingCfgMap;
};

// 称号配置
struct CfgTitle
{
	CfgTitle() {}

	int32_t			nId;			// 称号ID
	int32_t			nType;			// 称号类型
	Int32Vector		vParams;		// 参数
	std::string		sPlatform;		// 平台
	int32_t			nJob;			// 职业
	int32_t			nSex;			// 性别
	int32_t			nSpecial;		// 是否特殊称号
	int32_t			nPriority;		// 优先级
	AttrAddonVector	vGetAttr;		// 获得属性
	AttrAddonVector	vDressAttr;		// 穿戴属性
};
typedef std::map<int32_t, CfgTitle> CfgTitleMap;

class CfgTitleTable
{
public:
	CfgTitleTable(){}
	~CfgTitleTable(){}

	void AddTitle( const CfgTitle& stu )
	{
		m_TitleMap[stu.nId] = stu;
	}

	const CfgTitle* GetTitle( int32_t nId ) const
	{
		CfgTitleMap::const_iterator iter = m_TitleMap.find( nId );
		if ( iter != m_TitleMap.end() )
		{
			return &iter->second;
		}
		return NULL;
	}

	const CfgTitleMap* GetTitleMap() const { return &m_TitleMap; }

private:
	CfgTitleMap		m_TitleMap;
};

// 许愿配置
struct CfgWishReward
{
	int32_t			nTime;		// 所需时间
	MemChrBagVector	vReward;	// 奖励
};
typedef std::map<int32_t, std::list<CfgWishReward>> CfgWishRewardMap;

class CfgWishRewardTable
{
public:
	CfgWishRewardTable(){}
	~CfgWishRewardTable(){}

	void Add( int32_t nItemId, const CfgWishReward& stu )
	{
		m_mRewards[nItemId].push_back( stu );
	}

	const CfgWishReward* GetReward( int32_t nItemId, int32_t nTime ) const
	{
		CfgWishRewardMap::const_iterator findIter = m_mRewards.find( nItemId );
		if ( findIter == m_mRewards.end() )
			return NULL;

		const CfgWishReward* pReward = NULL;
		for ( std::list<CfgWishReward>::const_iterator iter = findIter->second.begin(); iter != findIter->second.end(); ++iter )
		{
			if ( iter->nTime > nTime )
				break;
			pReward = &(*iter);
		}
		return pReward;
	}

	int32_t GetLeftTime( int32_t nItemId, int32_t nStartTime ) const
	{
		CfgWishRewardMap::const_iterator findIter = m_mRewards.find( nItemId );
		if ( findIter == m_mRewards.end() )
			return 0;

		if ( findIter->second.empty() )
			return 0;

		int32_t nTime = nStartTime + findIter->second.back().nTime - Answer::DayTime::now();
		if ( nTime < 0 )
			return 0;
		return nTime;
	}

private:
	CfgWishRewardMap	m_mRewards;
};

typedef std::map<std::pair<int32_t,int32_t>, CfgCarrierAttr> CfgCarrierAttrMap;

class CfgCarrierTable
{
public:
	CfgCarrierTable(){}
	~CfgCarrierTable(){}

	void AddCarrier( const CfgCarrier& stu )
	{
		m_mCarrier[stu.nId] = stu;
	}

	const CfgCarrier* GetCarrier( int32_t nId ) const
	{
		CfgCarrierMap::const_iterator iter = m_mCarrier.find( nId );
		if ( iter != m_mCarrier.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

	void AddCarrierAttr( const CfgCarrierAttr& stu )
	{
		std::pair<int32_t,int32_t> key = std::make_pair( stu.nId, stu.nLevel );
		m_mCarrierAttr[key] = stu;
	}

	const CfgCarrierAttr* GetCarrierAttr( int32_t nId, int32_t nLevel ) const
	{
		std::pair<int32_t,int32_t> key = std::make_pair( nId, nLevel );
		CfgCarrierAttrMap::const_iterator iter = m_mCarrierAttr.find( key );
		if ( iter != m_mCarrierAttr.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

private:
	CfgCarrierMap		m_mCarrier;
	CfgCarrierAttrMap	m_mCarrierAttr;
};

// ��Ӫս���뽱��
struct CfgFamilyWarJoinReward 
{
	int32_t level;
	int32_t addExp;
};

typedef std::list<CfgFamilyWarJoinReward> CfgFamilyWarJoinRewardList;
struct CfgFamilyWarJoinRewardTable 
{
	void Add( int32_t nLevel, int32_t nExp )
	{
		CfgFamilyWarJoinReward reward;
		reward.level	= nLevel;
		reward.addExp	= nExp;
		m_reward.push_back( reward );
	}

	int32_t GetReward( int32_t nLevel ) const
	{
		CfgFamilyWarJoinRewardList::const_iterator iter = m_reward.begin();
		CfgFamilyWarJoinRewardList::const_iterator eiter = m_reward.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nLevel <= iter->level )
			{
				return iter->addExp;
			}
		}
		return 0;
	}
	CfgFamilyWarJoinRewardList m_reward;
};

class CfgFamilyLightExpTable 
{
public:
	void Add( int32_t nLevel, int32_t nAddExp )
	{
		vLevel.push_back( nLevel );
		vAddExp.push_back( nAddExp );
	}

	int32_t GetExp( int32_t nLevel ) const
	{
		int32_t idx = -1;
		int32_t isize = vLevel.size();
		for ( int32_t i = 0; i < isize; ++i )
		{
			if ( nLevel >= vLevel[i] )
			{
				idx = i;
			}
			else
			{
				break;
			}
		}
		if ( idx < 0 || idx >= isize )
		{
			return 0;
		}
		return vAddExp[idx];
	}



private:
	Int32Vector vLevel;
	Int32Vector vAddExp;
};

// ������Խ���
struct CfgHorseRacingReward 
{
	int32_t nIndex;
	int32_t nMaxIndex;
	int32_t	nExp;			// ����
	int32_t	nMoney;			// ��Ǯ
	MemChrBagVector			Items;
};
typedef std::list<CfgHorseRacingReward> CfgHorseRacingRewardList;
class CfgHorseRacingRewardTable
{
public:
	CfgHorseRacingRewardTable(){}
	~CfgHorseRacingRewardTable(){}

	void Add( const CfgHorseRacingReward& reward )
	{
		m_rewards.push_back( reward );
	}

	const CfgHorseRacingReward* GetReward( int32_t nIndex ) const
	{
		CfgHorseRacingRewardList::const_iterator iter = m_rewards.begin();
		CfgHorseRacingRewardList::const_iterator eiter = m_rewards.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nIndex >= iter->nIndex && nIndex <= iter->nMaxIndex )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

private:
	CfgHorseRacingRewardList m_rewards;
};


///////////////////////////////////////////////////////////////////////////////
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

struct BuffAttr //���ܹ������ԡ�����С֮���
{
	int32_t getRatio(int32_t level)
	{
		return (int)(ratio_base + ratio_ratio*level*0.1 + 0.5);
	}

	int32_t getAddon(int32_t level)
	{
		return (int)(addon_base + addon_ratio*level + 0.5);
	}

	int32_t attr;
	int32_t ratio_base;
	int32_t ratio_ratio;
	int32_t addon_base;
	int32_t addon_ratio;
};

struct CfgBuff //buff effect
{
	int32_t id;
	int32_t groupid;
	int32_t attack_type;
	int32_t level;
	int32_t beneficial;
	int32_t special;
	int32_t modify;
	int32_t hpValue;
	int32_t hpPecent;
	int32_t control;
	int32_t duration;
	int32_t interval;
	BuffAttr buffAttr[2];
	int8_t	isShow;
	int32_t shieldValue;
	int32_t shieldRatio;
	int32_t effectType;
	int32_t effectTimes;
	int8_t canRemove;
	int8_t canRecover;
	int32_t battle;
};
typedef std::map<int32_t, CfgBuff> CfgBuffTable;

struct CfgDungeon 
{
	int32_t id;				// ����ID
	std::string name;		// ��������
	int32_t mapid;			// ��ͼID
	int16_t x;				// �����X
	int16_t y;				// �����Y
	int8_t	type;			// ���� DungeonType
	int32_t group_id;		// �����飨�������������
	int32_t duration;		// ����ʱ��
	int16_t level;			// ����ȼ�
	int16_t	maxLevel;		// �ȼ�����
	int8_t	vip;			// ����VIP�ȼ�
	int32_t last_id;		// ǰһ������ID
	int32_t next_id;		// ��һ������ID
	int8_t	player_num;		// ��������
	int8_t	weekday;		// ÿ�ܿ�����
	int8_t	start_hour;		// ÿ�տ�ʼʱ��
	int8_t	end_hour;		// ÿ�ս���ʱ��
	int8_t	daily_count;	// ÿ�մ�������
	int32_t player_buff;	// ����BUFF
	int32_t star;			// ����
	int32_t	double_cost;	// ˫������
	int32_t	reward_time;	// ��ȡ����ʱ��(��)
	ItemData costItem;		// ��������
	MemChrBag rewardOnce;	// ��ͨ����
	MemChrBag rewardItem;	// ͨ�ؽ���
	int32_t	  Battle;		// ս��������֮սͨ�ؼӵ�ս����
	int32_t  costGold;		// ���ĵ�Ԫ��
	int32_t  costMoney;		// ���ĵ�ͭǮ
	int32_t  backMapId;		// ���ǵ�ͼID
	int16_t  backX;			// ���ǵ�X
	int16_t  backY;			// ���ǵ�Y
	int8_t   stayPosition;	// �Ƿ񱣳�ǰλ��
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

enum DUNGEON_DROP_TYPE
{
	DDT_ITEM	= 0,
	DDT_TRAP	= 1,
};
struct CfgDungeonDrop
{
	int32_t type;
	int32_t item_id;
	int8_t	item_class;
	int8_t	bind_type;
	int32_t count;
	int32_t weight;
	int32_t probability;
};
typedef std::list<CfgDungeonDrop> CfgDungeonDropList;

class CfgDungeonDropGroup 
{
public:
	CfgDungeonDropGroup(){ CleanUp(); }
	~CfgDungeonDropGroup(){}

	void CleanUp()
	{
		m_nMaxWight = 0;
		m_lstDropItems.clear();
	}

	void Add( CfgDungeonDrop& drop )
	{
		m_nMaxWight += drop.weight;
		drop.weight = m_nMaxWight;
		m_lstDropItems.push_back( drop );
	}

	const CfgDungeonDrop* RandDrop() const
	{
		int32_t nRand = RANDOM.generate( 0, m_nMaxWight );
		for ( CfgDungeonDropList::const_iterator iter = m_lstDropItems.begin(); iter != m_lstDropItems.end(); ++iter )
		{
			if ( nRand < iter->weight )
			{
				int32_t nRand2 = RANDOM.generate( 0, 1000 );
				if ( nRand2 < iter->probability )
				{
					return &(*iter);
				}
			}
		}
		return NULL;
	}

private:
	int32_t				m_nMaxWight;
	CfgDungeonDropList	m_lstDropItems;
};
typedef std::map<int32_t, CfgDungeonDropGroup> CfgDungeonDropGroupTable;

struct CfgDungeonMonster 
{
	int32_t id;
	int32_t wave;//���ﲨ��
	int32_t mid;
	int32_t x;
	int32_t y;
	int32_t count;
	int32_t side;
	PosList road;
	int32_t	delay;	// ˢ�ּ��
	int32_t	times;	// ˢ�ִ���
	int32_t	money;	// ������Ǯ
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
    MemChrBagVector ItemVector;
};
typedef std::map<int8_t,CfgSignReward>CfgSignRewardTable;

struct CfgAppendAttr
{
	int32_t			Id;
	int8_t			Job;
	AddAttrList		AttrList;
};
typedef std::list<CfgAppendAttr> AppendAttrTable;

struct CfgOnlineReward
{
	int8_t				Id;
	int32_t				NeedTime;
	MemChrBagVector		ItemVector;
};
typedef std::map<int8_t, CfgOnlineReward> CfgOnlineRewardTable;

struct CfgOffLineExp
{
	int32_t				Level;			//�ȼ�
	int32_t				MinuteExp;		//����ÿ���ӻ�Ľ���
	int32_t				TwoTimes;		//˫����ȡһ����λ����ĵ���
	int32_t				ThreeTimes;		//3����ȡһ����λ����ĵ���
	int32_t				BaseExp;		//һ����λ�ľ���
};
typedef std::map<int32_t,CfgOffLineExp> CfgOffLineExpTable;

struct CfgEquipItem
{
	Job_t  job;
	int32_t  id;
	int32_t  type;
	int32_t  bind;
	int32_t  count;
	int8_t	 star;
};
typedef std::vector<CfgEquipItem> MemChrEquipBagVector;

struct CfgSevenLoginRewrad
{
	int8_t					Day;
	MemChrEquipBagVector	ItemVector;
};
typedef std::map<int8_t, CfgSevenLoginRewrad> CfgSevenLoginRewradTable;

struct CfgGongGao
{
	int8_t		Job;
	int32_t		GongGaoId;
};
typedef std::list<CfgGongGao> GongGaoList;
struct NewServerFavorable
{
	int8_t					Index;
	int32_t					NeedGold;
	MemChrEquipBagVector	ItemVector;
	GongGaoList				GongGaoInfo;
};
typedef std::map<int8_t,NewServerFavorable> NewServerFavorableMap;


struct CfgWeekOnlineReward
{
	int32_t		Week;
	int32_t		Cash;
	int32_t		UpperLimit;
};
typedef std::map<int32_t,CfgWeekOnlineReward> CfgWeekOnlineRewardTable;

struct CfgLevelGift
{
	int8_t				Index;
	int32_t				Level;
	MemChrBagVector		ItemVector;
};
typedef std::map<int32_t,CfgLevelGift> CfgLevelGiftTable;

#ifndef PARAM2_DEFINED
#define PARAM2_DEFINED
struct Param2
{
	Param2() : nParam1(0), nParam2(0) {}
	int32_t nParam1;
	int32_t nParam2;
};
#endif
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

struct CfgItem : public CfgItemBase
{
	CfgItem() { RongHeReceovery.nParam1 = 0; RongHeReceovery.nParam2 = 0; }
	std::string effect;//����Ч��
	std::string use_method;
	int32_t downgrade;
	int32_t group_id;
	int32_t cd_group;
	int32_t overlay;
	int32_t can_sell;
	int32_t broadcast;
	int32_t valid_time;
	int32_t item_Grade;
	Param2	RongHeReceovery;	// 物品回收参数 (货币类型:货币数量)
};
typedef std::map<int32_t, CfgItem*> CfgItemTable;

struct CfgItemGift 
{
	int32_t id;
	int32_t item;
	int32_t type;
	int32_t count;
	int8_t  bind;
	int32_t job;
};
typedef std::vector<CfgItemGift> CfgItemGiftVector;
typedef std::map<int32_t, CfgItemGiftVector*> CfgItemGiftTable;

struct CfgFamilyLevel
{
	int32_t level;
	Int32Vector rewards;
};
typedef std::map<int32_t,CfgFamilyLevel>CfgFamilyLevelTable;

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

//��ͼ���ݽṹ
struct CfgMap 
{
	int32_t id;									//ID
	std::string name;							//����
	int32_t type;								//���
	int32_t param;								//�Id����
	int32_t width;								//��
	int32_t height;								//��
	int32_t revive;								//����
	int32_t pk_mode;							//pkģʽ
	int32_t anti_protect;						//����ģʽ
	int32_t isMount;							//�Ƿ�����
	int32_t isFly;								//�Ƿ���Է�
	int32_t isVicegeneral;						//�Ƿ�ั��
	int32_t player_level;						//��ҵȼ�
	int32_t player_level_max;					//�����ߵȼ�
	int32_t team_member;						//�Ŷӳ�Ա��
	int32_t hide_mini;							//����С��ͼ
	int32_t runnerId;							//������ͼ�߳�
	int8_t	jump;

	bool isType( const MapType& mt ) const
	{
		return (type & mt) != 0;
	}
};
typedef std::map<int32_t, CfgMap> CfgMapTable;

//�����ڵ�ͼλ�����ݽṹ
struct CfgMapMonster 
{
	int32_t id;							//����Ψһid
	int32_t mapid;						//��ͼID		
	int32_t monsterid;					//����ID
	int32_t x;							//xλ��
	int32_t y;							//yλ��
};
typedef std::map<int32_t, CfgMapMonster> CfgMonsterMap;
//һ�ŵ�ͼ�Ϲ����б�
typedef std::vector<CfgMapMonster> CfgMapMonsterVector;
//���е�ͼ�Ϲ����б�
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

//��ͼ��Χ
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
struct CfgMonster // ����
{
	int32_t mid;
	std::string name;
	int32_t level;
	int32_t quality;

	int32_t hp;						// ���Ѫ��
	int32_t phy_atk_min;			// ��С��������
	int32_t phy_atk_max;			// �����������
	int32_t mag_atk_min;			// ��Сħ������
	int32_t mag_atk_max;			// ���ħ������
	int32_t phy_def;				// ��������
	int32_t mag_def;				// ħ������
	int32_t hitrate;				// ����
	int32_t dodge;					// ����
	int32_t critrate;				// ����
	int32_t dmg_add;				// �����˺�
	int32_t dmg_rdc;				// �����˺�
	int32_t dmg_add_pec;			// �˺��ӳɣ�%��
	int32_t dmg_rdc_pec;			// �˺����⣨%��
	int32_t movespeed;				// �ƶ��ٶ�
	int32_t	battle;					// ����ֵ

	int32_t exp;
	int32_t type;//����0.���� 1.����
	int32_t kingdom_contribute;
	int32_t revive_time;
	int32_t skill_id;
	MonsterSkill unique_skill[MAX_MONSTER_SKILL];
	MonsterSkill random_skill[MAX_MONSTER_SKILL];
	int32_t angry_time;
	int32_t standby;//����
	int32_t hpPercent;//��λʱѪ������ǧ�ֱ�
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
	int32_t	BossSocre;
	int8_t  TaskShare;
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
	int8_t  job;
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
	int32_t hp;
	Int32Vector mapids;
	int32_t x;
	int32_t y;
	int32_t func;
	int32_t func_extra;
	Int32Vector params;
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

struct CfgGamble//ϡ������
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

struct CfgNpcTrade //ó��
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

struct CfgPlantEvent 
{
	int32_t EventId;
	int32_t Probability;
};
typedef std::vector<CfgPlantEvent> CfgPlantEventVector;

struct CfgPlant
{
	int32_t id;
	int32_t type;
	int32_t level;
	CfgPlantEventVector Events;
	int32_t EventMaxRate;
	int32_t item_cost;
	int32_t start_hour;
	int32_t end_hour;
	int32_t gather_time;
	int32_t revive_time;
};
typedef std::map<int32_t, CfgPlant> CfgPlantTable;

struct CfgPlantEventEffect
{
	int32_t		EventId;
	int32_t		EventType;
	string		EventEffect;
	int32_t		GongGaoId;
};
typedef std::map<int32_t,CfgPlantEventEffect> PlantEventMap;


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
		return (int)(money_base + money_ratio*(level*level+level)*0.1 + 0.5);
	}

	int32_t getMpCost(int32_t level)
	{
		 return (int)(mp_cost_base + static_cast<int32_t>(mp_cost_ratio*(level+level*(level-20)/40)) + 0.5);
	}

	int32_t getJonggongCost(int32_t level)
	{
		return jungong_base +jungong_ratio*level*level;
	}

	int32_t getAttackModify(int32_t level)
	{
		return (int)(attack_modify_base + attack_modify_ratio*(level-1) + 0.5);
	}

	int32_t getAttackAddon(int32_t level)
	{
		 return (int)(attack_addon_base + static_cast<int32_t>(attack_addon_ratio*(level+level*(level-10)/20)) + 0.5);
	}

	int32_t getBuffRate(int32_t level)
	{
		return (int)(buff_rate_base + buff_rate_ratio*level*0.1 + 0.5);
	}

	//��Ҫ���Ʋ��������ļ���
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
	int32_t beneficial;				// ������
	int32_t sp;						//�����ٶ�
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
	int32_t attack_modify_base;		// ������������ֵ
	int32_t attack_modify_ratio;	// ��������ϵ��
	int32_t attack_addon_base;		// �����ӳɻ���ֵ
	int32_t attack_addon_ratio;		// �����ӳ�ϵ��
	int32_t buff_rate_base;			// buff���ʻ���ֵ
	int32_t buff_rate_ratio;		// buff����ϵ��
	int32_t buff;
	int32_t level_base;
	int32_t maxLevel;
	ChangeJobIndexVector change_skill_id;
};
// CfgSkillTable is now a class (see below) — old map typedef renamed
typedef std::map<int32_t, CfgSkill> CfgSkillMap;

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
	int32_t dilong;
	int32_t rongyu;
	int32_t fuwen;
	int32_t shuguang;
	int32_t dungeon;
	MemChrBagVector award_item;
	MemChrJobBagVector award_optional;
	int32_t condition;
	int32_t done_count;
	TaskRequest request;
	int32_t JunTuanZiJin;
	int32_t GongXian;
};
typedef std::map<int32_t, CfgTask> CfgTaskTable;
typedef std::vector<CfgTask> CfgTaskVector;

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
	int32_t delay;			// �ӳ���Ӧ
	int32_t	event_type;		// ����Ч��
	std::string effect;		// Ч������
	int32_t item_cost;		// ��������
};
typedef std::map<int32_t, CfgTrap> CfgTrapTable;


struct cfgParam
{
	int32_t param1;
	int32_t param2;
};

typedef std::vector<cfgParam> cfgParams;
typedef std::map<int16_t, cfgParams> cfgParamsTable;


//��ͨ�����չ
struct cfgExActivity
{
	int16_t actid;
	int32_t starttime;
	int32_t endtime;
	cfgParams gifts;
	char strgifts[200];
};
typedef std::map<int16_t,cfgExActivity> cfgExActivitys;

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

//����װ�����ݽṹ
struct CfgMountEquip
{
	int32_t		id;
	std::string name;
	std::string desc;
	std::string url;
	int32_t		limit_level;
};
typedef std::map<int32_t, CfgMountEquip> CfgMountEquipTable;

////�������ݽṹ
//struct CfgKingdom
//{
//	int32_t id;								//����ID
//	std::string name;						//��������
//	int32_t task_id;						//ѡ����Һ�����ID
//	int32_t random_gift;					//������
//};
////�����б�
//typedef std::map<int32_t, CfgKingdom> CfgKingdomTable;

struct CfgYellowStone
{
	int32_t id;
	int32_t yellow_type; //1:yellow daily(level=vip level) 2:free yellow daily 3:yellow level(level=player level) 4:yellow year
	int32_t level;
	MemChrBagVector awards;
};
typedef std::map<int32_t, CfgYellowStone> CfgYellowStoneTables;


// װ����
#define MAX_EQUIP_BASE_ATTR_COUNT	4
struct CfgEquip
{
	int32_t		m_nId;										// id
	int8_t		m_nType;									// ���� EQUIP_TYPE
	int32_t		m_nLevel;									// �ȼ�
	int32_t		m_nSoulLevel;								// �����ȼ�
	int8_t		m_nJob;										// ְҵ
	int8_t		m_nQuality;									// Ʒ��
	int32_t		m_nSuitId;									// ��װID
	int32_t		m_nPrice;									// �ۼ�
	int32_t		m_nGrade;									// ����
	int32_t		m_Grade;		// alias
	int32_t		m_BackType;		// 回收类型
	int32_t		m_BackValue;	// 回收值
	int32_t		m_nRansomWorth;								// ��ؼ�ֵ
	int32_t		m_Battle;
	AttrAddon	m_vAttr[MAX_EQUIP_BASE_ATTR_COUNT];			// ��������
	AttrAddon	m_StarAttr[MAX_EQUIP_BASE_ATTR_COUNT];		// ǿ����������
	int32_t		m_nWuHunExp;								// ��꾭��
	int8_t		m_nBroadcast;								// �����Ƿ񹫸�
	int8_t		m_CanRongHe;								// �Ƿ���ں��� (0=��, >0=��)
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
	int32_t			m_nId;					// ԭװ��id					
	int32_t			m_nGiveId;				// �������װ��Id		
	int32_t			m_nFailLine;			// ��ʼ�б���������ֵ							
	int32_t			m_nSuccessLine;			// �ض��ɹ�������ֵ
	int32_t			m_nFullLucky;			// ����ֵ���ֵ
	int32_t			m_nGetLucky;			// ʧ�ܻ�õ�����ֵ
	int32_t			m_nRate;				// ��������
	int32_t			m_nTotalRate;			// ������ֵ
	ItemData		m_CostUsualItem;		// ��ͨ��Ʒ			
	ItemData		m_CostSpecialItem;		// ������Ʒ					
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
	int32_t			m_nId;					// ԭװ��id					
	int32_t			m_nGiveId;				// �������װ��Id		
	int32_t			m_nFailLine;			// ��ʼ�б���������ֵ							
	int32_t			m_nSuccessLine;			// �ض��ɹ�������ֵ
	int32_t			m_nFullLucky;			// ����ֵ���ֵ
	int32_t			m_nGetLucky;			// ʧ�ܻ�õ�����ֵ
	int32_t			m_nRate;				// ��������
	int32_t			m_nTotalRate;			// ������ֵ
	ItemData		m_CostUsualItem;		// ��ͨ��Ʒ			
	ItemData		m_CostSpecialItem;		// ������Ʒ	
	int32_t			m_OpenHoleRate;			// ������һ��ʯ�׵ĸ���
	int32_t			m_OpenSecondHoleRate;	// �����ڶ���ʯ�׵ĸ���
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
	int32_t			m_nStar;								// �Ǽ�
	int32_t			m_nFailLine;							// �ض�ʧ����
	int32_t			m_nSuccessLine;							// �ض��ɹ���
	int32_t			m_nFullLucky;							// ������ֵ
	int32_t			m_nFailAddLucky;						// ʧ�ܼӵ�����ֵ
	int32_t			m_nRate;								// �ɹ�����
	int32_t			m_nTotalRate;							// �ɹ��ܸ���
	ItemData		m_CostUsualItem;						// ������ͨ�����б�
	ItemData		m_CostSpecialItem;						// �����������
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
	int32_t			m_nLevel;								// �ȼ�
	int32_t			m_nMaxRate;								// �ܸ���
	CfgAddAttrList	m_lstAddAttr;							// ���������б�
};
typedef std::map<int32_t, CfgEquipAddAttr> CfgEquipAddAttrMap;

#define EQUIP_GOAL_STAR		1		// ǿ���Ǽ�
#define EQUIP_GOAL_GEM		2		// ��ʯ�ȼ�
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
	
	int32_t		m_nIndex;								// ����
	int8_t		m_nType;								// ����
	int32_t		m_nParam;								// ����
	AttrAddon	m_vAddAttr[MAX_EQUIP_ADD_ATTR_COUNT];	// ���������б�
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

	int32_t			m_nId;									// ����
	Int32List		m_lstEquips;							// ��װ����װ���б� 
	CfgSuitAttrList	m_lstSuitAttr;							// ���������б�
};
typedef std::map<int32_t, CfgEquipSuit> CfgEquipSuitMap;

// 装备回购配置
struct EquipBackCfg
{
	EquipBackCfg()
	{
		nId = 0;
		nType = 0;
		nLimitNum = 0;
		nDisplayDay = 0;
		nOpenDay = 0;
		nRecovType = 0;
		nRecovValues = 0;
		nBuyBackType = 0;
		nBuyBackValue = 0;
	}

	int32_t				nId;			// 配置ID
	std::list<int32_t>	nEquipList;		// 装备ID列表
	int32_t				nType;			// 类型 1=金币回购 2=开服回购
	int32_t				nLimitNum;		// 限购次数
	int32_t				nDisplayDay;	// 显示天数
	int32_t				nOpenDay;		// 开服天数
	int32_t				nRecovType;		// 回收货币类型
	int32_t				nRecovValues;	// 回收货币数量
	int32_t				nBuyBackType;	// 回购货币类型
	int32_t				nBuyBackValue;	// 回购货币数量
};
typedef std::map<int32_t, EquipBackCfg> EquipBackCfgMap;

struct EquipStrengthenCfg
{
	EquipStrengthenCfg() { CleanUp(); }
	void CleanUp()
	{
		nLevel = 0;
		nPos = 0;
		memset(&ConstItem, 0, sizeof(ConstItem));
		nAttrRate = 0;
		nDropRate = 0;
		vAttrAddon.clear();
		nNeedPos = 0;
		nGongGaoId = 0;
	}
	int32_t				nLevel;			// Level
	int32_t				nPos;			// SlotType (装备部位)
	ItemData			ConstItem;		// Item (消耗道具)
	int32_t				nAttrRate;		// BasicAttr (基础属性加成)
	int32_t				nDropRate;		// DropProbability
	AttrAddonVector		vAttrAddon;		// ActivationAttr (激活属性)
	int32_t				nNeedPos;		// ActivationType (需要部位)
	int32_t				nGongGaoId;		// GongGao (公告ID)
};
typedef std::map<std::pair<int32_t, int32_t>, EquipStrengthenCfg> EquipStrengthenMap;

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

	bool AddWuHunHoleExp( int32_t nHole, int32_t nExp )
	{
		m_mWuHunHoleExp[nHole] = nExp;
		return true;
	}

	int32_t GetWuHunHoleExp( int32_t nHole ) const
	{
		Int32Int32Map::const_iterator iter = m_mWuHunHoleExp.find( nHole );
		if ( iter != m_mWuHunHoleExp.end() )
		{
			return iter->second;
		}

		return 0;
	}

	bool AddWuHunMoHunExp( int32_t nLevel, int32_t nExp )
	{
		m_mWuHunMoHunExp[nLevel] = nExp;
		return true;
	}

	int32_t GetWuHunMoHunExp( int32_t nLevel ) const
	{
		Int32Int32Map::const_iterator iter = m_mWuHunMoHunExp.find( nLevel );
		if ( iter != m_mWuHunMoHunExp.end() )
		{
			return iter->second;
		}

		return 0;
	}
private:
	CfgEquipMap				m_mEquip;
	CfgEquipUpGradeMap		m_mEquipUpGrade;
	CfgEquipUpQualityMap	m_mEquipUpQuality;
	CfgEquipUpStarMap		m_mEquipUpStar;
	CfgEquipAddAttrMap		m_mEquipAddAttr;
	CfgEquipGoalMap			m_mEquipGoal;
	CfgEquipSuitMap			m_mEquipSuit;
	Int32Int32Map			m_mWuHunHoleExp;
	Int32Int32Map			m_mWuHunMoHunExp;
public:
	void AddEquipBack( const EquipBackCfg& stu )
	{
		m_mEquipBack[stu.nId] = stu;
	}

	const EquipBackCfg* GetEquipBackCfg( int32_t nId ) const
	{
		EquipBackCfgMap::const_iterator iter = m_mEquipBack.find( nId );
		if ( iter != m_mEquipBack.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

	void AddEequipStrengthenCfg( const EquipStrengthenCfg& stu )
	{
		std::pair<int32_t, int32_t> key = std::make_pair( stu.nLevel, stu.nPos );
		m_mEquipStrengthen[key] = stu;
	}

	const EquipStrengthenCfg* GetEequipStrengthenCfg( int32_t nLevel, int32_t nPos ) const
	{
		std::pair<int32_t, int32_t> key = std::make_pair( nLevel, nPos );
		EquipStrengthenMap::const_iterator iter = m_mEquipStrengthen.find( key );
		if ( iter != m_mEquipStrengthen.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

private:
	EquipBackCfgMap			m_mEquipBack;
	EquipStrengthenMap		m_mEquipStrengthen;
};

// ��ʯ��
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

//�±�ʯ�ṹ
struct CfgItemGem
{
	int32_t		m_nId;
	int8_t		m_nType;
	int8_t		m_nGemLevel;
	int32_t		m_nLevel;
	int32_t		m_nPrice;
	int8_t		m_nQuality;
	int32_t		m_nLayNum;
	int32_t		m_EffectType;  //��ʯЧ������
	int32_t		m_AddRate;	   //��ʯЧ������
	int32_t		m_nGrade;
	int32_t		m_Grade;		// alias
	int32_t		m_BackType;		// 回收类型
	int32_t		m_BackValue;	// 回收值
	int32_t		m_nRansomWorth;//��ؼ�ֵ
	int32_t		m_InValue;
	int32_t		m_OutValue;
//	AttrAddon	m_vAttr[MAX_GEM_BASE_ATTR_COUNT];
	int8_t		m_nBroadcast;
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

// �ϳɱ�
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
	ItemDataList CostList;//�ϳ�Ҫ�۳����б�
	int32_t m_nGiveId;				// �ϳɸ������ID
	int8_t	m_nGiveClass;			// �ϳɸ����������
	int32_t	m_nGiveCount;			// �ϳɸ����������
	int32_t	m_nMoney;				// �ϳ�����ͭǮ
	int32_t m_nRate;				// �ϳɳɹ�����
	int32_t m_nTotalRate;			// �ϳɳɹ��ܸ���
	int8_t	m_IsGongGao;			// �Ƿ񹫸�
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

// ħ�з���
struct CfgMagicBoxCombi
{
	CfgMagicBoxCombi()
	{
		m_nId		= 0;
		m_nCombiType	= 0;
		m_nCostPoint	= 0;
		m_nMoney		= 0;
		m_nRate		= 0;
		m_nTotalRate	= 0;
		m_bNeedActive	= 0;
		m_bBroadcast	= 0;
	}
	int32_t				m_nId;
	int32_t				m_nCombiType;	// 0=��ͨ, 1/2=��Ʒ, 3=װ��
	ItemDataList		m_lCostItem;	// ���Ĳ���
	int32_t				m_nCostPoint;	// ���Ļ���
	int32_t				m_nMoney;		// ���Ľ��
	MemChrBagVector		m_vGiveItem;	// ��������
	MemChrBagVector		m_vBackItem;	// ʧ�ܷ�����
	MemChrBagVector		m_vSpecialItems;	// ������Ŀ
	std::vector<Int32Vector> m_vProbability;	// ���ʾ���
	int32_t				m_nRate;		// �ɹ�����
	int32_t				m_nTotalRate;	// �ɹ��ܸ���
	int8_t				m_bNeedActive;	// �Ƿ���Ҫ����
	int8_t				m_bBroadcast;	// �Ƿ��㲥
};
typedef std::map<int32_t, CfgMagicBoxCombi> CfgMagicBoxCombiMap;

class CfgMagicBoxTable
{
public:
	CfgMagicBoxTable(){}
	~CfgMagicBoxTable(){}
	void Add( const CfgMagicBoxCombi& item ) { m_mMagicBox[item.m_nId] = item; }
	const CfgMagicBoxCombi* Get( int32_t nId ) const
	{
		CfgMagicBoxCombiMap::const_iterator it = m_mMagicBox.find( nId );
		if ( it != m_mMagicBox.end() ) return &it->second;
		return NULL;
	}
private:
	CfgMagicBoxCombiMap m_mMagicBox;
};

// V计划配置
// 国庆活动配置
struct NationalDayTaskCfg
{
	NationalDayTaskCfg() { memset(this, 0, sizeof(*this)); }
	int32_t nType;
	int32_t nId;
	int32_t nNeedValue;
	int32_t nSocre;
	int32_t nParam;
};
typedef std::map<std::pair<int,int>, NationalDayTaskCfg> NationalDayTaskCfgMap;

struct NationalDayLevelCfg
{
	NationalDayLevelCfg() { memset(this, 0, sizeof(*this)); }
	int32_t nLevel;
	int32_t nScore;
	int32_t nUnlockCost;
	int32_t nBuyCost;
	MemChrBagVector vGeneralReward;
	MemChrBag vSeniorReward;
	int32_t nGongGaoId;
};
typedef std::map<int, NationalDayLevelCfg> NationalDayLevelCfgMap;

struct CfgVplan
{
	CfgVplan()
	{
		nType = 0;
		nLevel = 0;
	}
	int32_t		nType;
	int32_t		nLevel;
	MemChrBag	EveryDayReward;
	MemChrBag	LevelReward;
};
typedef std::map<int32_t, CfgVplan> CfgVplanMap;

struct CfgYYVip
{
	CfgYYVip()
	{
		nType = 0;
		nLevel = 0;
	}
	int32_t		nType;
	int32_t		nLevel;
	MemChrBag	Gift;
};
typedef std::map<int32_t, CfgYYVip> CfgYYVipMap;

struct CfgXunLei
{
	CfgXunLei()
	{
		nLevel = 0;
	}
	int32_t		nLevel;
	MemChrBag	Reward;
};
typedef std::map<int32_t, CfgXunLei> CfgXunLeiMap;

struct CfgLuDaShi
{
	CfgLuDaShi()
	{
		nLevel = 0;
	}
	int32_t		nLevel;
	MemChrBag	Gift;
};
typedef std::map<int32_t, CfgLuDaShi> CfgLuDaShiMap;

struct CfgSwVipReward
{
	CfgSwVipReward()
	{
		nIndex = 0;
		nType = 0;
		nLevel = 0;
		nNeedLoginDays = 0;
		nCondition = 0;
		nParam = 0;
	}
	int32_t		nIndex;
	int32_t		nType;
	int32_t		nLevel;
	int32_t		nNeedLoginDays;
	int32_t		nCondition;
	int32_t		nParam;
	MemChrBag	Reward;
};
typedef std::map<int32_t, CfgSwVipReward> CfgSwVipRewardMap;

struct CfgYYGameApp
{
	CfgYYGameApp()
	{
		nIndex = 0;
		nNeedLevel = 0;
	}
	int32_t		nIndex;
	int32_t		nNeedLevel;
	MemChrBag	Reward;
};
typedef std::map<int32_t, CfgYYGameApp> CfgYYGameAppMap;

struct CfgSgGameApp
{
	CfgSgGameApp()
	{
		nIndex = 0;
		nNeedLevel = 0;
	}
	int32_t		nIndex;
	int32_t		nNeedLevel;
	MemChrBag	Reward;
};
typedef std::map<int32_t, CfgSgGameApp> CfgSgGameAppMap;
// 金币奖励任务配置
struct ShenWeiTaskCfg
{
	ShenWeiTaskCfg()
	{
		nIndex = 0;
		nTaskId = 0;
		nDoubleCost = 0;
	}
	int32_t		nIndex;
	int32_t		nTaskId;
	int32_t		nDoubleCost;
};
typedef std::map<int32_t, ShenWeiTaskCfg> ShenWeiTaskCfgMap;

struct BackEquipTask
{
	BackEquipTask()
	{
		nId = 0;
		nRandGold = 0;
		nGetCurr = 0;
		nStar = 0;
	}
	int32_t			nId;
	Int32Vector		Equips;
	MemChrBagVector	Items;
	int32_t			nRandGold;
	int32_t			nGetCurr;
	int32_t			nStar;
};
typedef std::map<int32_t, BackEquipTask> BackEquipTaskMap;

// 翻牌抽奖配置
struct FlopDrawCfg
{
	FlopDrawCfg()
	{
		m_nId		= 0;
		m_nType		= 0;
		m_nRate		= 0;
		m_GongGaoId	= 0;
	}
	int32_t				m_nId;
	int32_t				m_nType;
	MemChrBag			m_Item;
	int32_t				m_nRate;
	int32_t				m_GongGaoId;
};
typedef std::map<int32_t, FlopDrawCfg> FlopDrawCfgMap;

class CfgFlopDrawTable
{
public:
	CfgFlopDrawTable() { CleanUp(); }
	~CfgFlopDrawTable(){}

	void CleanUp() { m_mFlopDrawCfg.clear(); }

	void Add( const FlopDrawCfg& cfg ) { m_mFlopDrawCfg[cfg.m_nId] = cfg; }

	const FlopDrawCfg* GetFlopDrawCfg( int32_t nId ) const
	{
		FlopDrawCfgMap::const_iterator iter = m_mFlopDrawCfg.find( nId );
		if ( iter != m_mFlopDrawCfg.end() ) return &iter->second;
		return NULL;
	}

	const FlopDrawCfgMap& GetAll() const { return m_mFlopDrawCfg; }

private:
	FlopDrawCfgMap m_mFlopDrawCfg;
};

// ========== 时装系统配置 ==========

// 时装单品配置
struct CfgShiZhuang
{
    CfgShiZhuang()
        : nId(0), nType(0), nSuitId(0), nSort(0), nPriority(0), nQuality(0)
    {
    }

    int32_t nId;
    int32_t nType;
    int32_t nSuitId;
    int32_t nSort;
    int32_t nPriority;
    int32_t nQuality;
    std::string strName;
    std::string strIcon;
    std::string strDesc;
    std::string strMaleAvatar;
    std::string strFemaleAvatar;
    AddAttrList vAttr;
};

// 时装等级配置
struct CfgShiZhuangLevel
{
    CfgShiZhuangLevel()
        : nType(0), nLevel(0), nLevelExp(0), nNeedLevel(0), nCostItem(0),
          nGetExp(0), nSmallCritRate(0), nLargeCritRate(0), nBroadcast(0)
    {
    }

    int8_t nType;
    int32_t nLevel;
    int32_t nLevelExp;
    int32_t nNeedLevel;
    int32_t nCostItem;
    int32_t nGetExp;
    int32_t nSmallCritRate;
    int32_t nLargeCritRate;
    int32_t nBroadcast;
    AddAttrList vAttr;
};

// 时装升阶配置
struct ShiZhuLevelUp
{
    ShiZhuLevelUp()
        : nId(0), nLevel(0)
    {
    }

    int32_t nId;
    int32_t nLevel;
    ItemDataList lCostItem;
    AddAttrList lAttr;
};

// 时装套装配置
struct ShiZhuangSuitInfo
{
    int32_t nLevel;
    int32_t nSuitLevel;
};

struct ShiZhuangSuitCfg
{
    int32_t nSuidId;
    int32_t nCount;
    std::list<ShiZhuangSuitInfo> lInfo;
};

class CfgShiZhuangTable
{
public:
    CfgShiZhuangTable() { CleanUp(); }
    ~CfgShiZhuangTable() {}

    void CleanUp()
    {
        m_mShiZhuang.clear();
        m_mShiZhuangLevel.clear();
        m_ShiZhuangSuitCfgMap.clear();
    }

    void AddShiZhuang(const CfgShiZhuang& stu)
    {
        m_mShiZhuang[stu.nId] = stu;
    }

    void AddShiZhuangLevel(const CfgShiZhuangLevel& stu)
    {
        m_mShiZhuangLevel[std::make_pair(stu.nType, stu.nLevel)] = stu;
    }

    void AddShiZhuangSuitInfo(ShiZhuangSuitCfg* p_stu)
    {
        if (p_stu) m_ShiZhuangSuitCfgMap[p_stu->nSuidId] = *p_stu;
    }

    const CfgShiZhuang* GetShiZhuang(int32_t nId) const
    {
        std::map<int32_t, CfgShiZhuang>::const_iterator it = m_mShiZhuang.find(nId);
        if (it != m_mShiZhuang.end()) return &it->second;
        return NULL;
    }

    const CfgShiZhuangLevel* GetShiZhuangLevel(int8_t nType, int32_t nLevel) const
    {
        std::map<std::pair<int8_t, int32_t>, CfgShiZhuangLevel>::const_iterator it =
            m_mShiZhuangLevel.find(std::make_pair(nType, nLevel));
        if (it != m_mShiZhuangLevel.end()) return &it->second;
        return NULL;
    }

    int32_t GetShiZhuangSuitLevel(int32_t SuitId, int32_t nLevel, int32_t nCount) const;
    void GetShiZhuangSuitAttr(AddAttrList& outList, int32_t SuitId, int32_t nLevel, int32_t nCount) const;

private:
    std::map<int32_t, CfgShiZhuang> m_mShiZhuang;
    std::map<std::pair<int8_t, int32_t>, CfgShiZhuangLevel> m_mShiZhuangLevel;
    std::map<int32_t, ShiZhuangSuitCfg> m_ShiZhuangSuitCfgMap;
};


struct CfgBagSlotOpenTime 
{
	int32_t	m_nSlot;			// ������
	int32_t	m_nSeconds;			// ����������Ҫʱ��
	int32_t m_nBagAddExp;		// ����������þ���
	int32_t m_nBagAddHp;		// �����������HP
	int32_t m_nDepotNeedSeconds;// �����ֿ���Ҫ��ʱ��
	int32_t m_nDepotAddExp;		// �����ֿ��þ���
	int32_t m_nDepotAddHp;		// �����ֿ���HP
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
// ���Գ�ʼ����Ӧ�İٷֱ�
class CfgPetAttrInitRateTable
{
	friend class CfgData; 

// CfgActiveSkill - 主动技能配置 (2019完整版)
struct CfgActiveSkill
{
	CfgActiveSkill()
		: id(0), talent(0), groupid(0), cd(0), distance(0), attack_type(0),
		  range(0), target_num(0), kind(0), beneficial(0), mp(0), power(0),
		  addon_skill(0), addon_time(0), addon_trig_times(0),
		  summon_id(0), summon_limit(0), summon_delay(0),
		  shu_lian_du(0) {}
	int32_t id;
	int32_t talent;
	int32_t groupid;
	int32_t cd;
	int32_t distance;
	int32_t attack_type;
	int32_t range;				// 0=self, 1=single target, 10=team, other=AOE
	int32_t target_num;
	int32_t kind;				// 2=特殊(OperateLimit), else=normal
	int32_t beneficial;
	int32_t mp;
	int32_t power;
	int32_t addon_skill;
	int32_t addon_time;
	int32_t addon_trig_times;
	int32_t summon_id;
	int32_t summon_limit;
	int32_t summon_delay;
	int32_t shu_lian_du;		// 熟练度
	AttrAddonVector vAttrAddon;
};
typedef std::map<int32_t, CfgActiveSkill> CfgActiveSkillMap;

class CfgData;
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

#define MAX_PET_SKILL_RATE	100000	// ����������ʻ���
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
		m_Zoarium			= 0;
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
	int32_t			m_nPetId;						// ����ID
	std::string		m_strName;						// ��������
	Job_t			m_nOrderJob;					// ָ������
	Job_t			m_nPetJob;						// ��������
	int32_t			m_nRare;						// ������
	int32_t			m_nRein;						// ת����������
	PET_PHASE		m_nPhase;						// ����=0���������
	int32_t			m_nLucky;						// ����ֵ
	int32_t			m_vMaxAttr[PET_ATTR_COUNT];		// ��������
	int32_t			m_vMaxPoints[PET_ATTR_COUNT];	// �������
	SkillId_t		m_nSkillId;						// �����츳����
	SkillId_t		m_nSecondSkillId;				// �ڶ��츳����
	SkillId_t		m_vSkill[PET_SKILL_COUNT];		// ���＼��
	SkillId_t		m_vSkillRate[PET_SKILL_COUNT];	// ���＼�ܸ���
	int32_t			m_nHatchTime;					// ����ʱ��
	int32_t			m_nMutiHatchTime;				// ��������ʱ��
	int32_t			m_nRideSkin;					// ���Ƥ��
	int32_t			m_nGrowRatio;					// �ɳ�ϵ��
	int8_t			m_nXxoo;						// XO������
	int8_t			m_Zoarium;						// �Ƿ��ܺ���
	int32_t			m_WuHunExp;						// ��꾭��
};
typedef std::map<int32_t, CfgPetData>	CfgPetDataMap;

struct PetPackageCost 
{
	int32_t nPoints;
	int8_t	nCostType;
	int32_t nCostValue;
	int8_t  nXoCostType;
	int32_t nXoCostValue;
};
typedef std::list<PetPackageCost> PetPackageCostList;

typedef std::list<PetId_t>	PetIdList;

struct CWuHunExp
{
	int32_t Points;
	int32_t Exp;
};
typedef std::list<CWuHunExp> WuHunExpList;

struct PetBuyInfo
{
	int32_t ShopId;
	int32_t Points;
};
typedef map<int32_t,PetBuyInfo> PetBuyMap;

struct FamilyTaskReward
{
	int32_t		Index;
	int32_t		NeedCount;
	MemChrBagVector Rewards;
};
typedef map<int32_t,FamilyTaskReward>  FamilyTaskRewardMap;
struct CfgPetUpStar
{
	CfgPetUpStar() { CleanUp(); }
	void CleanUp()
	{
		nStar = 0;
		nCostMoney = 0;
		nCostGold = 0;
		GongGaoId = 0;
		lCostItem.clear();
		vAddPetAttr.clear();
		vAddPlayerAttr.clear();
		vSkillLevel.clear();
	}
	int32_t				nStar;
	int32_t				nCostMoney;
	int32_t				nCostGold;
	int32_t				GongGaoId;
	std::list<ItemData>	lCostItem;
	std::vector<AttrAddon>	vAddPetAttr;
	std::vector<AttrAddon>	vAddPlayerAttr;
	Int32Vector				vSkillLevel;
};
typedef std::map<int32_t, CfgPetUpStar> CfgPetUpStarMap;

class CfgPetTable
{
public:
	CfgPetTable(){}
	~CfgPetTable(){}

	void Add( const CfgPetData& pet )
	{
		m_mPetCfgData[pet.m_nPetId] = pet;
	}

	void AddPetUpStar( const CfgPetUpStar& stu )
	{
		m_mPetUpStar[stu.nStar] = stu;
	}

	const CfgPetUpStar* GetPetUpStar( int32_t nStar ) const
	{
		CfgPetUpStarMap::const_iterator iter = m_mPetUpStar.find( nStar );
		if ( iter != m_mPetUpStar.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

	void AddWuHunExp( const CWuHunExp& WuHunExp )
	{
		m_WuHunExpList.push_back( WuHunExp );
	}

	void AddPetBuy( PetBuyInfo& PetBuy )
	{
		m_PetBuyMap[PetBuy.ShopId] = PetBuy;
	}
	
	int32_t GetBuyPetPoints( int32_t ShopId ) const
	{
		PetBuyMap::const_iterator it = m_PetBuyMap.find( ShopId );
		if ( it != m_PetBuyMap.end() )
		{
			return it->second.Points;
		}
		return 0;
	}

	int32_t GetWuHunExp( int32_t Points ) const
	{
		WuHunExpList::const_iterator it = m_WuHunExpList.begin();
		for ( ; it != m_WuHunExpList.end(); ++it )
		{
			if ( Points < it->Points )
			{
				return it->Exp;
			}
		}
		return 0;
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

	void AddInitPet( Job_t job, const Int32List& pets )
	{
		m_vInitPet[job] = pets;
	}

	const Int32List& GetInitPets( Job_t job ) const
	{
		return m_vInitPet[job];
	}

	void AddPetPackageCost( const PetPackageCost& cost )
	{
		m_lstPetPackageCost.push_back( cost );
	}

	const PetPackageCost* GetPackageCost( int32_t nPoints ) const
	{
		PetPackageCostList::const_iterator iter = m_lstPetPackageCost.begin();
		PetPackageCostList::const_iterator eiter = m_lstPetPackageCost.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nPoints < iter->nPoints )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

private:
	CfgPetDataMap		m_mPetCfgData;
	CfgPetUpStarMap		m_mPetUpStar;
	Int32List			m_vInitPet[PJ_JOB_COUNT];
	PetPackageCostList	m_lstPetPackageCost;
	WuHunExpList		m_WuHunExpList;
	PetBuyMap			m_PetBuyMap;
};

struct CfgPetEgg
{
	int32_t nId;
	int32_t nPetId;
	int32_t nLevel;
	int32_t nRein;
	int32_t vAttr[PET_ATTR_COUNT];
	int32_t nHatchingTime;
	int32_t nMutiHatchingTime;
	int32_t nPrice;
	int32_t nWuHunExp;
	int8_t	broadcast;
};
typedef std::map<int32_t, CfgPetEgg> CfgPetEggMap;
class CfgPetEggTable
{
public:
	CfgPetEggTable()
	{
		CleanUp();
	}

	void CleanUp()
	{
		m_mPetEgg.clear();
	}

	bool Add( const CfgPetEgg& petEgg )
	{
		m_mPetEgg[petEgg.nId] = petEgg;
		return true;
	}

	const CfgPetEgg* GetEgg( int32_t nId ) const
	{
		CfgPetEggMap::const_iterator iter = m_mPetEgg.find( nId );
		if ( iter != m_mPetEgg.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

private:
	CfgPetEggMap	m_mPetEgg;
};

struct CfgPetIllusionGrow 
{
	int32_t nMainPointMin;
	int32_t nMainPointMax;
	int32_t nVicePoint;
	int32_t nVicePointMax;
	int32_t nViceLevel;
	Int32Vector nShopIds;
	int32_t Compensation;
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
	const CfgPetIllusionGrow* GetGrowViceGrow( int32_t VicePoint ) const
	{
		CfgPetIllusionGrowList::const_iterator iter = m_lstPetIllusionGrow.begin();
		CfgPetIllusionGrowList::const_iterator eiter = m_lstPetIllusionGrow.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( VicePoint >= iter->nVicePoint && VicePoint < iter->nVicePointMax )
			{
				return &(*iter);
			}
		}
		return NULL;
	}
	bool IsRightShopId( int32_t nMainPoint, int32_t ShopId ) const
	{
		CfgPetIllusionGrowList::const_iterator iter = m_lstPetIllusionGrow.begin();
		CfgPetIllusionGrowList::const_iterator eiter = m_lstPetIllusionGrow.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nMainPoint >= iter->nMainPointMin && nMainPoint < iter->nMainPointMax )
			{
				Int32Vector::const_iterator itShop = iter->nShopIds.begin();
				for ( ;itShop != iter->nShopIds.end(); ++itShop )
				{
					if ( *itShop == ShopId )
					{
						return true;
					}
				}
				return false;
			}
		}
		return false;
	}
private:
	CfgPetIllusionGrowList	m_lstPetIllusionGrow;
};

#define MAX_KNIGHT_QUALITY_SIZE		20
enum PET_KNIGHT_EFFECT
{
	PKE_ADD_EXP			= 1,	//������ӳ�
	PKE_REMINE_JUMP		= 2,	//��������Ծ���ĵ�����
	PKE_ADD_BATTLE		= 3,	//��ս�����ӳ�
	PKE_REMINE_DAMAGE	= 4,	//���˺�����
	PKE_ADD_DAMAGE		= 5,	//���˺��ӳ�
	PKE_ADD_MAX_HP		= 6,	//������ֵ�������
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

		if ( nMax >= 0 )
		{
			return vEffectValue[nMax];
		}
		return 0;
	}
	int32_t		nLevel;										// ����ȼ�
	int32_t		nTitle;										// �ƺţ�
	Int32List	compIdList;									// ���������ĳ����б�
	int8_t		nEffectType;								// ��������
	int32_t		vQuality[MAX_KNIGHT_QUALITY_SIZE];			// Ʒ��
	int32_t		vEffectValue[MAX_KNIGHT_QUALITY_SIZE];		// �ӳ�
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
	int32_t		nGrowTimes;
	int32_t		m_vMaxAttr[PET_ATTR_COUNT];		// ��������
};
typedef std::map<int32_t, CfgPetGift> PetGiftMap;

struct FamilyTask
{	
	int32_t TaskId;
	int32_t MinLevel;
	int32_t MaxLevel;
};
typedef std::list<FamilyTask> FamilyTaskList;
typedef std::vector<FamilyTask> FamilyTaskVector;
class CfgFamilyTask
{
public:
	CfgFamilyTask(){ CleanUp();}
	~CfgFamilyTask(){};
	void CleanUp()
	{
		m_FamilyTaskList.clear();
	}
	void AddFamilyTask( int32_t nTaskId, int32_t nMinLevel, int32_t nMaxLevel )
	{
		FamilyTask task = { nTaskId, nMinLevel, nMaxLevel };
		m_FamilyTaskList.push_back( task );
	}
	int32_t GetFamilyTask( int32_t Level ) const
	{
		Int32Vector vTask;
		vTask.reserve( m_FamilyTaskList.size() );
		FamilyTaskList::const_iterator it = m_FamilyTaskList.begin();
		for ( ; it != m_FamilyTaskList.end(); ++it )
		{
			if ( Level >= it->MinLevel && Level <= it->MaxLevel )
			{
				vTask.push_back( it->TaskId );
			}
		}
		std::random_shuffle( vTask.begin(), vTask.end() );
		return vTask.front();
	}
private:
	FamilyTaskList m_FamilyTaskList;
};


#define MAX_CYCLE_STARS			10

struct TaskCycle 
{
	int32_t nTaskId;
	int32_t nMinLevel;
	int32_t nMaxLevel;
};
typedef std::list<TaskCycle> TaskCycleList;
typedef std::vector<TaskCycle> TaskCycleVector;

struct CycleStarRate
{
	int32_t		Level;
	int32_t		Rate[MAX_CYCLE_STARS];
	int32_t		TenStarTimes;
};
typedef std::list<CycleStarRate> StarRateList;

class CfgTaskCycleTable
{
public:
	CfgTaskCycleTable(){ CleanUp(); }
	~CfgTaskCycleTable(){}

	void CleanUp()
	{
		m_StarList.clear();
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
		int32_t FirstTask = 0;
		TaskCycleList::const_iterator iter = m_lstTask.begin();
		TaskCycleList::const_iterator eiter = m_lstTask.end();
		if ( iter != eiter )
		{
			FirstTask = iter->nTaskId;
		}
		for ( ; iter != eiter; ++iter )
		{
			if ( nLevel >= iter->nMinLevel && nLevel <= iter->nMaxLevel )
			{
				vTask.push_back( iter->nTaskId );
			}
		}

		if ( vTask.empty() )
		{
			return FirstTask;
		}

		std::random_shuffle( vTask.begin(), vTask.end() );
		return vTask.front();
	}

	bool AddStarRate( CycleStarRate& StarRate)
	{
		m_StarList.push_back( StarRate );
		return true;
	}

	int32_t GetTenStarTimes( int32_t Level ) const
	{
		StarRateList::const_iterator it =	m_StarList.begin();
		for ( ; it != m_StarList.end(); ++it )
		{
			if ( Level <= it->Level )
			{
				return it->TenStarTimes;
			}
		}
		return 0;
	}

	int8_t RandStar( int32_t Level ) const
	{
		StarRateList::const_iterator it =	m_StarList.begin();
		for ( ; it != m_StarList.end(); ++it )
		{
			if ( Level <= it->Level )
			{
				int32_t nRate	= RANDOM.generate( 1, 10000 );
				for ( int8_t i = 0; i < MAX_CYCLE_STARS; i++ )
				{
					if ( nRate <= it->Rate[i] )
					{
						return i+1;
					}
					nRate -= it->Rate[i];
				}
			}
		}
		return 0;
	}

private:
	StarRateList	m_StarList;
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

	int32_t		nLevel;								// �ȼ�
	int32_t		nExp;								// �����׶�
	int32_t		nBattle;							// ����ս����
	int32_t		nMaxMembers;						// �������
	int32_t		nTotemCount;						// ���ͼ�ڸ���
	int32_t		vPosition[FAMILY_POSITION_COUNT];	// ְλ����
};

struct WarVictoryHd		//��ս�
{
	int8_t				Index;
	int8_t				Type;
	int32_t				StartTime;
	int32_t				EndTime;
	int32_t				NeedGold;
	MemChrBagVector		Rewards;
	int32_t				Times;
	GongGaoList			GongGaoId;
};
typedef std::map<int8_t,WarVictoryHd> WarVictoryHdMap;


// CfgFamilyBoss
struct CfgFamilyBoss
{
    CfgFamilyBoss() : BossMid(0), FamilyExp(0), GongGaoId(0) {}
    int32_t BossMid;
    int32_t FamilyExp;
    int32_t GongGaoId;
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
		m_mFamilyBoss.clear();
		m_mFamilyBossByMid.clear();
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

	bool AddFamilyBoss( int32_t nKey, const CfgFamilyBoss& boss )
	{
		m_mFamilyBoss[nKey] = boss;
		m_mFamilyBossByMid[boss.BossMid] = boss;
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

	const CfgFamilyBoss* GetFamilyBoss( int32_t FamilyLevel, int32_t BossId ) const;
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
	int32_t				m_vTotomActiveLevel[MAX_PET_ID+1];						// ͼ�ڼ���������ŵȼ�
	CfgFamilyPosition	m_vFamilyPosition[FAMILY_POSITION_COUNT];
	std::map<int32_t, CfgFamilyBoss>	m_mFamilyBoss;
	std::map<int32_t, CfgFamilyBoss>	m_mFamilyBossByMid;				// ����ְλ����
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

class CfgInsidePetTable
{
	typedef std::map<int32_t, AttrAddonVector>	AttrAddonMap;
public:
	void Add( int32_t nLevel, int32_t nExp, const AttrAddonVector& attrAddons1, const AttrAddonVector& attrAddons2, const AttrAddonVector& attrAddons3 )
	{
		m_mLevelExp[nLevel]		= nExp;
		m_mAttrAddon1[nLevel]	= attrAddons1;
		m_mAttrAddon2[nLevel]	= attrAddons2;
		m_mAttrAddon3[nLevel]	= attrAddons3;
	}

	const AttrAddonVector& GetAttrAddon( int32_t nLevel, Job_t job ) const
	{
		const AttrAddonMap* pMap = NULL;
		switch ( job )
		{
		case PJ_ZHANSHI:	pMap = &m_mAttrAddon1;	break;
		case PJ_FASHI:		pMap = &m_mAttrAddon2;	break;
		case PJ_LONGQI:		pMap = &m_mAttrAddon3;	break;
		default:break;
		}
		AttrAddonMap::const_iterator iter = pMap->find( nLevel );
		if ( iter != pMap->end() )
		{
			return iter->second;
		}
		return m_empty;
	}

	int32_t GetLevelExp( int32_t nLevel ) const
	{
		Int32Int32Map::const_iterator iter = m_mLevelExp.find( nLevel );
		if ( iter != m_mLevelExp.end() )
		{
			return iter->second;
		}
		return -1;
	}

	void AddExpItem( int32_t nId, int32_t nExp )
	{
		m_mExpItem[nId] = nExp;
	}

	int32_t	GetItemExp( int32_t nId ) const
	{
		Int32Int32Map::const_iterator iter = m_mExpItem.find( nId );
		if ( iter != m_mExpItem.end() )
		{
			return iter->second;
		}
		return -1;
	}

private:
	AttrAddonVector	m_empty;
	AttrAddonMap	m_mAttrAddon1;
	AttrAddonMap	m_mAttrAddon2;
	AttrAddonMap	m_mAttrAddon3;
	Int32Int32Map	m_mLevelExp;

	Int32Int32Map	m_mExpItem;
};

class CfgSoulAttrTable
{
	typedef std::map<int32_t, AttrAddonVector>	AttrAddonMap;
public:
	void Add( int32_t nLevel, int32_t nExp, const AttrAddonVector& attrAddons1, const AttrAddonVector& attrAddons2, const AttrAddonVector& attrAddons3, int32_t Battle )
	{
		m_mLevelExp[nLevel]		= nExp;
		m_mAttrAddon1[nLevel]	= attrAddons1;
		m_mAttrAddon2[nLevel]	= attrAddons2;
		m_mAttrAddon3[nLevel]	= attrAddons3;
		m_Battle[nLevel]		= Battle;
	}

	int32_t GetAddBattle( int32_t nLevel ) const
	{
		Int32Int32Map::const_iterator iter = m_Battle.find( nLevel );
		if ( iter != m_Battle.end() )
		{
			return iter->second;
		}
		return 0;
	}
	const AttrAddonVector& GetAttrAddon( int32_t nLevel, Job_t job ) const
	{
		const AttrAddonMap* pMap = NULL;
		switch ( job )
		{
		case PJ_ZHANSHI:	pMap = &m_mAttrAddon1;	break;
		case PJ_FASHI:		pMap = &m_mAttrAddon2;	break;
		case PJ_LONGQI:		pMap = &m_mAttrAddon3;	break;
		default:break;
		}
		AttrAddonMap::const_iterator iter = pMap->find( nLevel );
		if ( iter != pMap->end() )
		{
			return iter->second;
		}
		return m_empty;
	}

	int32_t GetLevelExp( int32_t nLevel ) const
	{
		Int32Int32Map::const_iterator iter = m_mLevelExp.find( nLevel );
		if ( iter != m_mLevelExp.end() )
		{
			return iter->second;
		}
		return -1;
	}

private:
	AttrAddonVector	m_empty;
	AttrAddonMap	m_mAttrAddon1;
	AttrAddonMap	m_mAttrAddon2;
	AttrAddonMap	m_mAttrAddon3;
	Int32Int32Map	m_mLevelExp;
	Int32Int32Map   m_Battle;
};


struct HallOfFameReward 
{
	int32_t nIndexMin;
	int32_t nIndexMax;
	int32_t nHonor;
	//ItemDataList items;
	MemChrBagVector items;
};
typedef std::list<HallOfFameReward> HallOfFameRewardList;

class CfgHallOfFameTable
{
public:
	CfgHallOfFameTable(){}
	~CfgHallOfFameTable(){}

public:
	void CleanUp()
	{
		m_rewards.clear();
	}

	void AddReward( const HallOfFameReward& reward )
	{
		m_rewards.push_back( reward );
	}

	const HallOfFameReward* GetReward( int32_t nIndex ) const
	{
		HallOfFameRewardList::const_iterator iter = m_rewards.begin();
		HallOfFameRewardList::const_iterator eiter = m_rewards.end();
		for ( ; iter != eiter; ++iter )
		{
			if ( nIndex >= iter->nIndexMin && nIndex <= iter->nIndexMax )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

private:
	HallOfFameRewardList	m_rewards;
};
//wmf end

struct PkDropRate
{
	int32_t		PkValues;			//pkֵ
	int32_t		EquipCount;			//����װ����
	int32_t		EquipRate;			//װ���������
	int32_t		UsualCountRate;		//��ͨ��Ʒ�����������
	int32_t		UsualDropRate;		//��ͨ��Ʒ�������
	int32_t		SpecialCountRate;	//������Ʒ�����������
	int32_t		SpecialDropRate;	//������Ʒ�������
	int32_t		OverlayRate;		//�������������
	int32_t		MoneyRate;			//ͭǮ�������
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
	FaBaoMap	m_FaBaoTable;		//��ⷨ����
};

struct FunctionOpenCfg
{
	int32_t		Type;
	int32_t		TaskId;
	int32_t		Level;
};
typedef std::map<int32_t,FunctionOpenCfg> FunctionOpenCfgMap;

struct QiFuCfg
{
	int32_t GetMoney;
	int32_t	GetExp;
	int32_t CostGold;
	int8_t  CostItemClass;
	int32_t	CostItemId;
	int32_t CostItemCount;
};

typedef map<int8_t, QiFuCfg> QiFuTimesMap;		// <��������,����>
typedef map<int32_t, QiFuTimesMap> QiFuCfgMap;	// <�ȼ�,����> 

class CQiFuTable
{
public:
	CQiFuTable();
	void		InitQiFuTable();
	QiFuCfg*	GetQiFuCfg( int8_t QiFuType,int32_t Level, int8_t QiFuTimes );
private:
	QiFuCfgMap	m_QiFuMoneyCfg;
	QiFuCfgMap	m_QiFuExpCfg;
};

struct VipCfg
{
	int8_t		VipLevel;
	int8_t		QiFuMoneyTimes;		// ����ͭǮ�Ĵ���
	int8_t		QiFuExpTimes;		// ��������Ĵ���
	int8_t		Retroactive;		// ��ǩ�Ĵ���
	int32_t		NeedVipExp;			// ��Ҫvip����
	int32_t		ExpRate;			// ��־���ӳ�
	int32_t		OpenBag;			// �������ı���
	int32_t		DailyTaskTimes;		// �ճ��������
	MemChrBagVector Item;			// vip���
	AttrAddonVector	AtttVector;		// vip����
	int32_t		PetDeport;			// ���ӳ���ֿ�ĸ���
	int32_t		FamilyLightAddRate;	// ����֮��ӳ�
	int32_t		HallOfFameBuyTimes;	// �����ù������
	int32_t		SiteRevive;			// ÿ�츴�����
	// 2019新增字段
	int32_t		Luck1;				// 普通幸运掉落次数
	int32_t		Luck2;				// 特殊幸运掉落次数
	int32_t		ClubBuyTimes;		// Club购买掉落次数
	int32_t		EquipBackRate;		// 装备找回比率
	int32_t		TreasureTimes;		// 寻宝次数
	int32_t		CycleTower;			// 循环塔次数
	int32_t		StorePage;			// 仓库页数
};
typedef map<int8_t, VipCfg> VipCfgMap;

struct VipCardCfg
{
	int8_t		VipCardId;
	int8_t		VipLevel;			// 2019: 所需VIP等级
	int32_t		AddVipExp;
	int32_t		DailyAddExp;
	int32_t		AddVipTime;
	int32_t		NeedGold;			// 首次购买价格
	int32_t		ReNeedGold;			// 2019: 续费价格
	int32_t		ExpRate;
	int32_t		AddPlayerExp;
	int32_t		AddPetExp;
	MemChrBagVector Items;
	AddAttrList AddAttr;
	int32_t		Money;				// 2019: 绑定元宝
	int32_t		TianShuJinHua;		// 2019: 天书精华
	int32_t		WeiWang;			// 2019: 威望
};

typedef map<int32_t,VipCardCfg> VipCardCfgMap;

class VipTable
{
public:
	VipTable();
	void		InitVipTable();
	VipCfg*		GetVipCfg( int8_t VipLevel );
	int8_t		GetVipLevel( int32_t VipExp );
private:
	VipCfgMap m_VipCfgMap;
};

struct MoonCardTouZiCfg
{
	int16_t		Index;
	int16_t		NeedDay;
	int8_t		CurrencyType;
	int32_t		CurrencyValues;
};
typedef std::map<int16_t,MoonCardTouZiCfg> MoonCardTouZiCfgMap;
struct LevelUpTouZiCfg
{
	int16_t  Index;
	int32_t	 NeedLevel;
	int32_t	 Rate;
};
typedef std::map<int16_t,LevelUpTouZiCfg> LevelUpTouZiCfgMap;
class CTouZiCfg
{
public:
	CTouZiCfg();
	void				InitTouZiTable();
	MoonCardTouZiCfg*	GetMoonCardTouZiCfg( int16_t Index );
	LevelUpTouZiCfg*	GetLevelUpTouZiCfg( int16_t Index );
	MoonCardTouZiCfgMap& GetMoonCardTable();
	LevelUpTouZiCfgMap&	 GetLevelUpTable();
private:
	MoonCardTouZiCfgMap	m_MoonCardCfgMap;
	LevelUpTouZiCfgMap  m_LevelUpCfgMap;
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
		m_BossId				= 0;
		m_TransferPos.x			= 0;
		m_TransferPos.y			= 0;
		m_RevivePosVector.clear();
		m_IsShow				= 0;
		m_NeedResetReviveTime	= 0;
	}
	int32_t					m_BossId;
	Position				m_TransferPos;		// ��������
	std::vector<Position>	m_RevivePosVector;	// ���������б�
	int8_t					m_NeedResetReviveTime;
	int8_t					m_IsShow;
};
typedef std::map<int32_t, BossInfo> BossInfoMap;

struct CfgQuestions
{
	int32_t QuestionId;
	int8_t AnswerId;
};
typedef std::vector<CfgQuestions> QuestionsVector;

struct ChouJiangShop
{
	int32_t		Index;
	int32_t		ItemId;
	int8_t		ItemClass;
	int32_t		ItemCount;
	int32_t		NeedScore;
	int8_t		Type;
	int32_t		Limit;
	int8_t		Bind;
};
typedef std::map<int32_t,ChouJiangShop> CJShopMap;

struct ChouJiangCost
{
	int8_t	ChouJiangType;
	int32_t	CostGold;
	int32_t CostGold2;
	int8_t	CostItemClass;
	int32_t CostItemId;
	int32_t CostItemCount;
	int32_t	AddScore;
};

typedef std::map<int32_t,ChouJiangCost> CJCostMap;

struct ChouJiangCfg
{
	bool IsEmpty()
	{
		if ( ItemId == 0 || ItemCount == 0 )
		{
			return true;
		}
		return false;
	}
	int8_t	ChouJiangType;
	int8_t	ItemClass;
	int32_t	ItemId;
	int32_t ItemCount;
	int8_t	Quality;
	int8_t	Star;
	int32_t	Probability;
	int8_t  IsRecord;
	int8_t	IsGongGao;
};
typedef std::list<ChouJiangCfg> CJCfgList;

struct CfgKaiFuHuoDongData
{
	int32_t		Index;
	int8_t		Type;
	int32_t		StartDay;
	int32_t		EndDay;
	int32_t		GetRewardDay;
	int8_t		Conditions;
	int32_t		Parm1;
	int32_t		Parm2;
	int32_t		LimitCount;
	MemChrBagVector ItemVector;
};

typedef std::map<int32_t,CfgKaiFuHuoDongData>   KaiFuHuoDongCfg;

struct LevelRefinCfg
{
	int32_t	LV;
	std::vector<int32_t>	vNeedGold;
	std::vector<int32_t>	nLevelUp;
	int32_t	nLimit;
	int32_t	nGongGaoId;
};
typedef std::map<int32_t, LevelRefinCfg>   LevelRefinCfgMap;

// ===== BossKilledReward Config =====
struct BossKilledReward
{
	int32_t			id;
	int8_t			type;
	int32_t			number;
	int32_t			start;
	int32_t			end;
	int32_t			notice;
	int32_t			index;
	std::list<int32_t>	BossList;
	MemChrBagVector		Rewars;
};
typedef std::map<int8_t, BossKilledReward> BossKilledRewardMap;

class ChouJiangConfig
{
public:
	ChouJiangConfig();
	void InitCJConfig();
	void InitShopMap();
	void InitCostMap();
	void InitCfgList();
	ChouJiangCost*  GetCJCost( int8_t ChouJiangType );
	ChouJiangShop*	GetCJShop( int8_t Index );
	ChouJiangCfg	GetCJCfg( int8_t ChouJiangType, bool IsSpecial = false );
	CJShopMap m_CJShopMap;
	CJCostMap m_CJCostMap;
	CJCfgList m_CJCfgList;
};

struct CfgBossHome
{
	int32_t		MapId;
	int32_t		Grade;
	int32_t		NeedVipLevel;
	int32_t		NeedGold;
	int32_t		IntervalTime;
	int32_t     NeedCash;
	ItemData	CostItem;
	std::vector<Position>	EnterPosVector;
};

typedef std::map<int32_t, CfgBossHome> BossHomeTable;

struct VipGuaJiMap
{
	int32_t			MapId;
	int32_t			StartTime;
	int32_t			EndTime;
	int32_t			VipLevel;
};
typedef std::map<int32_t,VipGuaJiMap> VipGuaJiMapTable;

struct CfgMoLingRuQinMapInfo
{
	int32_t			MapId;
	int32_t			NpcId;
	int32_t			NpcCount;
	std::vector<Position>	m_RevivePosVector;
};
typedef std::map<int32_t, CfgMoLingRuQinMapInfo> MoLingRuQinMap;

struct CurrencyStu
{
	int8_t		Type;
	int32_t		Values;
};
typedef std::list<CurrencyStu> CurrencyList;
struct CfgZiYuanZhaoHui
{
	int32_t				Index;				//id
	int32_t				Type;				//��Դ�һص�����
	int32_t				Times;				//�ܴ���
	int32_t				Id;					//�����ǻ ���ǻ������, �����Ǹ������� ����groupid
	int32_t				NeedMoney;			//�һ���Ҫ��ͭǮ
	int32_t				NeedGold;			//�һ���Ҫ��Ԫ��
	CurrencyList		GetCurrencyList;	//��õ���Դ
	int32_t				GetExpValues;		//��õľ���
};
typedef std::map<int32_t,CfgZiYuanZhaoHui> CfgZYZHMap;

struct CfgEquipExchange
{
	int8_t		Level;
	int8_t		CostType;
	int32_t		Money;
	int32_t		MoShi;
	int32_t		BindMoShi;
};
typedef std::map<int8_t,CfgEquipExchange> CfgEquipExchangeMap;

struct CfgEverydayChongZhi
{
	int8_t					Index;
	int32_t					NeedGold;
	MemChrEquipBagVector	ItemVector;
	GongGaoList				GongGaoInfo;
};
typedef std::map<int8_t,CfgEverydayChongZhi> EverydayChongZhiMap;

struct CfgTotalChongZhi
{
	int8_t					Index;
	int32_t					NeedGold;
	MemChrEquipBagVector	ItemVector;
	GongGaoList				GongGaoInfo;
	int32_t					NewServerday;
};
typedef std::map<int8_t,CfgTotalChongZhi> TotalChongZhiMap;

struct CfgHuoYueDu
{
	int32_t			Index;
	int8_t			Type;
	int32_t			Effect;
	int32_t			Count;
	int32_t			Gold;
	int32_t			AddHuoYueDu;
	bool			IsCanSec;					//�Ƿ������
};

typedef	std::map<int32_t,CfgHuoYueDu> HuoYueDuTable;

struct CfgHuoYueDuReward
{
	int32_t					Id;
	int32_t					NeedHuoYueDu;
	MemChrBagVector			Items;
};
typedef std::map<int8_t,CfgHuoYueDuReward> HuoYueDuRewardTable;

struct CfgGuanWei
{
	int32_t   GuanWei;
	int32_t	  NeedLevel;
	int32_t   NeedWeiWang;
	int32_t	  GetExp;
	int32_t   GetMoney;
	MemChrBagVector			Items;
	int32_t   MailId;
	int32_t	  Battle;
	AddAttrList Attrs;
};
typedef std::map<int32_t,CfgGuanWei> GuanWeiMap;

#define QI_SHI_COUNT 6					//�����ʿ�ĸ���
#define MAX_QI_SHI_QUALITY_SIZE 10		//���Ը���
struct CfgQiShi
{
	int32_t			QiShiPos;
	int32_t			NeedGuanWei;
	int32_t			AddBattle;
	int32_t			AttrType;
	int32_t			AttrType2;
	int32_t			vQuality[MAX_QI_SHI_QUALITY_SIZE];			// Ʒ��
	int32_t			vEffectValue[MAX_QI_SHI_QUALITY_SIZE];		// �ӳ�
	int32_t			vEffectValue2[MAX_QI_SHI_QUALITY_SIZE];		// �ӳ�
};
typedef std::map<int32_t,CfgQiShi> QiShiMap;

struct AchievementRequest 
{
	int32_t param1;
	int32_t param2;
	int32_t param3;
};

struct CfgAchievement
{
	int32_t				Index;
	int32_t				Socre;
	CurrencyList		ZhiYuan;
	int8_t				Group;
	AchievementRequest	Request;
};
typedef std::map<int32_t,CfgAchievement> AchievementTask;

class AchievementTable
{
public:
	AchievementTable(){ OnCleanUP(); }
	~AchievementTable(){};
	void	OnCleanUP();
	void    AddAchievementTask( CfgAchievement Stu );
	const CfgAchievement* GetAchievementTask( int32_t Index ) const;
	const AchievementTask GetAchievementTaskMap() const;
private:
	AchievementTask m_AchievementTaskMap;
};

struct CfgXunZhang
{
	int32_t		EquipId;
	int32_t		CostSocre;
	int32_t		NextEquipId;
};
typedef map<int32_t,CfgXunZhang> XunZhangMap;

struct CfgBuyAcSocre
{
	int32_t		Index;
	int8_t		CostType;
	int32_t		CostValues;
	int32_t		GetValues;
};
typedef map<int32_t, CfgBuyAcSocre> BuyAcSocerMap;

struct CfgHuanHuaNeedRoleLevel
{
	int32_t MinQualit;
	int32_t MaxQualit;
	int32_t NeedLevel;
};
typedef list<CfgHuanHuaNeedRoleLevel> HuanHuaNeedRoleLevelList;



// ZongHeYunYingHD Config
struct CfgZongHeYunYingHD
{
    int32_t nStartDay;
    int32_t nEndDay;
    int32_t nIcon;
    std::string strOpen;
    int32_t nDailyRechargeStartDay;
    int32_t nDailyRechargeEndDay;
    int32_t nDailyRechargeValue;
    int32_t nDailyRechargeRewardLimit;
    MemChrBagVector vDailyRechargeReward;
    int32_t nRankDailyStartDay;
    int32_t nRankDailyEndDay;
    int32_t nRankDailyArea;
    int32_t nRankDailySize;
    std::vector< std::pair<int32_t, int32_t> > vRankDailyIndex;
    std::vector<MemChrBagVector> vRankDailyReward;
    std::vector<int32_t> vRankDailyMail;
    int32_t nTeamShopDailyStartDay;
    int32_t nTeamShopDailyEndDay;
    int32_t nTeamShopDailySize;
    std::vector<int32_t> vTeamShopDailyPlayer;
    std::vector<int32_t> vTeamShopDailyValue;
    std::vector<MemChrBagVector> vTeamShopDailyReward;
    int32_t nOnceShopStartDay;
    int32_t nOnceShopEndDay;
    int32_t nOnceShopSize;
    std::vector<int32_t> vOnceShopPrice;
    std::vector<MemChrBagVector> vOnceShopItem;
};


// SpecialEquip Config
struct SpeciaEquipCfg
{
	int32_t	nId;
	int32_t	nTalentId;
	int32_t	nContinueLogin;		// NeedDay
	int32_t	nNeedVipLevel;		// VipLevel
	int32_t	nBuyLimitVipLevel;	// BuyVipLimit
	int32_t	nNeedGold;		// NeedGold
	int32_t	nGongGaoId;		// NoticeID
	int32_t	nDisplayID;		// DisplayID
	AddAttrList	lAttrList;		// AddAttr (parsed from string)
};
typedef std::map<int32_t, SpeciaEquipCfg> SpeciaEquipCfgMap;

// BlackMarket Config
struct CfgBlackMarketGoods
{
	int32_t	nDays;		// Days column
	int32_t	nIndex;		// Index column (1-4)
	int32_t	nOldPrice;	// OldPrice column
	int32_t	nPrice;		// Price column
	int32_t	nBroadcast;	// GongGao column
	MemChrBag	item;		// Parsed from Items column (per job)
};

// 抽卡配置
struct CfgDrawReward
{
	CfgDrawReward() { nIndex = 0; nType = 0; nRate = 0; nBroad = 0; nId = 0; }
	int32_t nIndex;
	int32_t nType;
	int32_t nRate;
	int32_t nBroad;
	int32_t nId;
	std::vector<MemChrBag> vItem;
};
typedef std::list<CfgDrawReward> CfgDrawRewardList;

struct CfgDraw
{
	CfgDraw() { m_nType = 0; m_nMaxRate = 0; }
	int8_t GetType() const { return m_nType; }
	void Add( const CfgDrawReward* reward )
	{
		m_rewards.push_back( *reward );
		m_nMaxRate += reward->nRate;
	}
	int8_t m_nType;
	int32_t m_nMaxRate;
	CfgDrawRewardList m_rewards;
};

typedef std::list<CfgDraw> CfgDrawList;

// 兑换配置
struct CfgExchange
{
	CfgExchange() { nType = 0; nIndex = 0; nLimit = 0; }
	void CleanUp() { nType = 0; nIndex = 0; nLimit = 0; vCost.clear(); vReward.clear(); }
	int8_t nType;
	int16_t nIndex;
	int32_t nLimit;
	ItemDataList vCost;
	MemChrBagVector vReward;
};

class CfgExchangeTable
{
public:
	CfgExchangeTable() {}
	~CfgExchangeTable() {}

	bool Add( const CfgExchange* stu )
	{
		m_lstExchange.push_back( *stu );
		return true;
	}

	const CfgExchange* GetExchange( int8_t nType, int16_t nIndex ) const
	{
		for ( std::list<CfgExchange>::const_iterator iter = m_lstExchange.begin(); iter != m_lstExchange.end(); ++iter )
		{
			if ( iter->nType == nType && iter->nIndex == nIndex )
			{
				return &(*iter);
			}
		}
		return NULL;
	}

private:
	std::list<CfgExchange> m_lstExchange;
};

class CfgDrawTable
{
public:
	CfgDrawTable() {}
	~CfgDrawTable() {}

	void Add( const CfgDrawReward* reward )
	{
		for ( CfgDrawList::iterator iter = m_Draws.begin(); iter != m_Draws.end(); ++iter )
		{
			if ( iter->GetType() == reward->nType )
			{
				iter->Add( reward );
				return;
			}
		}
		CfgDraw draw;
		draw.m_nType = reward->nType;
		draw.Add( reward );
		m_Draws.push_back( draw );
	}

	void RandomReward( CfgDrawReward* pReward, int8_t nType, int32_t* pGetItemList ) const
	{
		if ( NULL == pReward ) return;
		for ( CfgDrawList::const_iterator iter = m_Draws.begin(); iter != m_Draws.end(); ++iter )
		{
			if ( iter->GetType() == nType )
			{
				if ( iter->m_nMaxRate <= 0 ) return;
				int32_t nRand = RANDOM.generate( 1, iter->m_nMaxRate );
				int32_t nCur = 0;
				for ( CfgDrawRewardList::const_iterator rit = iter->m_rewards.begin(); rit != iter->m_rewards.end(); ++rit )
				{
					nCur += rit->nRate;
					if ( nRand <= nCur )
					{
						*pReward = *rit;
						return;
					}
				}
				return;
			}
		}
	}

private:
	CfgDrawList m_Draws;
};

// 神秘礼物配置
struct CfgMysteryGift
{
	CfgMysteryGift() { CleanUp(); }
	void CleanUp()
	{
		nIndex = 0;
		nType = 0;
		nCondition = 0;
		nBroadId = 0;
		vItem.clear();
	}
	int32_t nIndex;
	int32_t nType;
	int32_t nCondition;
	int32_t nBroadId;
	MemChrBagVector vItem;
};

class CfgMysteryGiftTable
{
public:
	CfgMysteryGiftTable() {}
	~CfgMysteryGiftTable() {}

	bool Add( const CfgMysteryGift* gift )
	{
		m_mMysteryGift[gift->nIndex] = *gift;
		return true;
	}

	const CfgMysteryGift* GetGiftInfo( int32_t nIndex ) const
	{
		std::map<int32_t, CfgMysteryGift>::const_iterator iter = m_mMysteryGift.find( nIndex );
		if ( iter != m_mMysteryGift.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

private:
	std::map<int32_t, CfgMysteryGift> m_mMysteryGift;
};

// 神秘商店配置
struct CfgMysteryShop
{
	CfgMysteryShop() { CleanUp(); }
	void CleanUp()
	{
		nId = 0;
		nType = 0;
		memset( &item, 0, sizeof( item ) );
		nCostType = 0;
		nPrice = 0;
		nRate = 0;
		nMinLevel = 0;
		nMaxLevel = 0;
		nBroad = 0;
		memset( &exchange, 0, sizeof( exchange ) );
	}
	int32_t		nId;
	int32_t		nType;
	MemChrBag	item;
	int32_t		nCostType;
	int32_t		nPrice;
	int32_t		nRate;
	int32_t		nMinLevel;
	int32_t		nMaxLevel;
	int32_t		nBroad;
	ItemData	exchange;
};

typedef std::list<CfgMysteryShop> CfgMysteryShopList;

class CfgMysteryShopTable
{
public:
	CfgMysteryShopTable() {}
	~CfgMysteryShopTable() {}

	void Add( const CfgMysteryShop& shop )
	{
		m_mMysteryShop[shop.nId] = shop;
	}

	const CfgMysteryShop* GetShopGood( int32_t nId ) const
	{
		std::map<int32_t, CfgMysteryShop>::const_iterator iter = m_mMysteryShop.find( nId );
		if ( iter != m_mMysteryShop.end() )
		{
			return &(iter->second);
		}
		return NULL;
	}

	void GetShopList( CfgMysteryShopList& lst, int32_t nType ) const
	{
		for ( std::map<int32_t, CfgMysteryShop>::const_iterator iter = m_mMysteryShop.begin();
			iter != m_mMysteryShop.end(); ++iter )
		{
			if ( iter->second.nType == nType )
			{
				lst.push_back( iter->second );
			}
		}
	}

private:
	std::map<int32_t, CfgMysteryShop>	m_mMysteryShop;
};

struct CfgBlacketMarketTable
{
	typedef std::map<int32_t, CfgBlackMarketGoods> GoodsMap;
	GoodsMap	m_GoodsMap;

	const CfgBlackMarketGoods* GetGoods( int32_t nDay, int32_t nIndex, int32_t nJob ) const
	{
		// Look up by combined key: day * 100 + index * 10 + job
		int32_t nKey = nDay * 10000 + nIndex * 10 + nJob;
		GoodsMap::const_iterator iter = m_GoodsMap.find( nKey );
		if ( iter != m_GoodsMap.end() )
		{
			return &iter->second;
		}
		return NULL;
	}

	void AddGoods( int32_t nDay, int32_t nIndex, int32_t nJob, const CfgBlackMarketGoods& goods )
	{
		int32_t nKey = nDay * 10000 + nIndex * 10 + nJob;
		m_GoodsMap[nKey] = goods;
	}
};


// ===== OutLinkFestival Config =====
struct CfgOutLinkFestival
{
	int32_t	nIndex;
	int32_t	nStartTime;
	int32_t	nEndTime;
	int32_t	nIcon;
	std::string	strPlatform;
};
typedef std::list<CfgOutLinkFestival> CfgOutLinkFestivalList;

class CfgOutLinkFestivalTable
{
public:
	CfgOutLinkFestivalTable(){}
	~CfgOutLinkFestivalTable(){}

	void Add( const CfgOutLinkFestival& stu )
	{
		m_lFestival.push_back( stu );
	}

	void GetShowIcons( CfgOutLinkFestivalList& lst ) const
	{
		int32_t nNowTime = Answer::DayTime::now();
		for ( CfgOutLinkFestivalList::const_iterator iter = m_lFestival.begin();
			iter != m_lFestival.end(); ++iter )
		{
			if ( iter->nStartTime <= nNowTime && iter->nEndTime >= nNowTime )
			{
				lst.push_back( *iter );
			}
		}
	}

	bool empty() const { return m_lFestival.empty(); }

	CfgOutLinkFestivalList m_lFestival;
};

// ===== SevenDayTask Config Structs =====
struct SevenTaskCfg
{
    int32_t nIndex;
    int32_t nType;
    int32_t nCondition;
    MemChrBag Item;
    int32_t nStartDay;
    int32_t nEndDay;
};

typedef std::map<int32_t, SevenTaskCfg> SevenTaskCfgMap;

struct SevenTaskSumReward
{
    int32_t nIndex;
    int32_t nFinishCount;
    MemChrBag Item;
    int32_t nGongGaoId;
};

typedef std::map<int32_t, SevenTaskSumReward> SevenTaskSumRewardMap;

// 打折券配置
struct DaZheQuan
{
	int32_t nIndex;
	int32_t nCurrencyType;
	int32_t nCurrencyValues;
	MemChrBagVector Items;
};
typedef std::map<int32_t, DaZheQuan> DaZheQuanMap;

// 神威配置 (Cachet)
struct CfgCachet
{
	CfgCachet() { CleanUp(); }
	void CleanUp()
	{
		nLevel = 0;
		nCachet = 0;
		nDeduct = 0;
		nLanguage = 0;
		lAttrList.clear();
	}
	int32_t		nLevel;		// Lv
	int32_t		nCachet;	// Cachet (minimum honor)
	AddAttrList	lAttrList;	// Attr (parsed from string)
	int32_t		nDeduct;	// Deduct (daily honor deduction)
	int32_t		nLanguage;	// Language
	int32_t		nGongGaoId; // GongGao broadcast id
};
typedef std::map<int32_t, CfgCachet> CachetCfgMap;

// 鬼谷道人配置
struct GuiGuDaoRenCfg
{
	GuiGuDaoRenCfg() { CleanUp(); }
	void CleanUp()
	{
		nNpcId = 0;
		nMaxCount = 0;
		vItemData.clear();
		vItem.clear();
		lRefreshMonster.clear();
		vMapId.clear();
	}
	int32_t					nNpcId;
	int32_t					nMaxCount;
	std::vector<ItemData>		vItemData;
	std::vector<MemChrBag>		vItem;
	std::list<int32_t>	lRefreshMonster;
	Int32Vector				vMapId;
};

typedef std::map<int32_t, GuiGuDaoRenCfg> GuiGuDaoRenCfgMap;

// 融合物品
struct RongHeItem
{
	RongHeItem() { CleanUp(); }
	void CleanUp()
	{
		memset(&item, 0, sizeof(item));
		nRate = 0;
		nRate2 = 0;
		nSuccess = 0;
		nRecord = 0;
		nGongGaoId = 0;
	}
	MemChrBag	item;		// GiveItem
	int32_t		nRate;		// Rate (weight)
	int32_t		nRate2;		// Rate2 (鬼谷道人修正权重)
	int32_t		nSuccess;	// Success (result success value)
	int32_t		nRecord;	// Record (0=no record, >0=record)
	int32_t		nGongGaoId;	// GongGaoId (broadcast if >0)
};
typedef std::list<RongHeItem> RongHeItemList;

// 融合配置
struct RongHeCfg
{
	RongHeCfg() { CleanUp(); }
	void CleanUp()
	{
		nIndex = 0;
		memset(&nCostItem, 0, sizeof(nCostItem));
		lRongHeItemList.clear();
		nMaxRate = 0;
		nMaxRate2 = 0;
	}
	int32_t			nIndex;		// Index
	ItemData		nCostItem;		// CostItem (parsed from string)
	RongHeItemList	lRongHeItemList;	// GiveItem list
	int32_t			nMaxRate;		// MaxRate
	int32_t			nMaxRate2;		// MaxRate2 (鬼谷道人)
};
typedef std::map<int32_t, RongHeCfg> RongHeCfgMap;

// 装备融合配置 (MixGem.txt)
struct EquipRongHe
{
	EquipRongHe() { nItemId = 0; nMaxEquip = 0; nAttrRate = 0; }
	int32_t nItemId;
	int32_t nMaxEquip;
	int32_t nAttrRate;
};
typedef std::map<int32_t, EquipRongHe> EquipRongHeMap;

// 物品回收参数 (nParam1 = 货币类型, nParam2 = 货币数量)

// 装备熔炼信息
struct RongLianInfo
{
	RongLianInfo()
		: nItemId(0), nCount(0), nEquipId(0) {}
	int32_t	nItemId;
	int32_t	nCount;
	int32_t	nEquipId;
};
typedef std::map<int32_t, RongLianInfo> RongLianInfoMap;

// 装备强化配置 (MieShenRongLian.txt)
class SevenTaskTable
{
public:
    SevenTaskTable() {}
    ~SevenTaskTable() {}

    void AddTaskCfg( const SevenTaskCfg& cfg )
    {
        m_TaskCfgMap[cfg.nIndex] = cfg;
    }

    void AddSumReward( const SevenTaskSumReward& cfg )
    {
        m_SumRewardMap[cfg.nIndex] = cfg;
    }

    const SevenTaskCfg* GetSevenTaskCfg( int32_t nId ) const
    {
        SevenTaskCfgMap::const_iterator it = m_TaskCfgMap.find( nId );
        if ( it != m_TaskCfgMap.end() )
        {
            return &(it->second);
        }
        return NULL;
    }

    const SevenTaskSumReward* GetSevenTaskSumReward( int32_t nId ) const
    {
        SevenTaskSumRewardMap::const_iterator it = m_SumRewardMap.find( nId );
        if ( it != m_SumRewardMap.end() )
        {
            return &(it->second);
        }
        return NULL;
    }

    const SevenTaskCfgMap& GetSevenTaskCfgMap() const
    {
        return m_TaskCfgMap;
    }

    const SevenTaskSumRewardMap& GetSevenTaskSumRewardMap() const
    {
        return m_SumRewardMap;
    }

    int32_t GetSumRewardCount() const
    {
        return (int32_t)m_SumRewardMap.size();
    }

private:
    SevenTaskCfgMap         m_TaskCfgMap;
    SevenTaskSumRewardMap   m_SumRewardMap;
};

// ===== TianLing Config Structs =====
struct TianLingCfg
{
	int32_t				CostMoney;		// Gold
	int32_t				CostCoin;		// Coin
	ItemDataList		CostItems;		// Res
	std::list<AddAttribute>	AttrList;	// Attr
	int32_t				GongGaoId;		// NoticeID
};
typedef std::map<int32_t, TianLingCfg> TianLingCfgMap;

struct ZhanHunCfg
{
	int32_t				nMoney;			// Money
	int32_t				nSyb;			// Syb
	std::list<AddAttribute>	lAddAttrs;	// Attr
	int32_t				nGongGaoId;		// NoticeID
};
typedef std::map<int32_t, ZhanHunCfg> ZhanHunCfgMap;

struct SunAndMoonCfg
{
	ItemDataList		lConstItems;	// CostItem
	std::list<AddAttribute>	lAttr;		// AttrStr
	int32_t				nGetItemTimes;	// AbsorbCount
	int32_t				nSunTelentId;	// SunTelentId
	int32_t				nSunTelentLevel;// SunSkillLevel
	int32_t				nMoonTelentId;	// MoonTelentId
	int32_t				nMoonTelentLevel;// MoonSkillLevel
	int32_t				nGongGaoId;		// Notice
};
typedef std::map<int32_t, SunAndMoonCfg> SunAndMoonCfgMap;

// ===== VIP Lucky Drop Config =====
struct SpecialItemDrop
{
	SpecialItemDrop() : Rate(0) { memset(&Item, 0, sizeof(Item)); }
	MemChrBag Item;
	int32_t	Rate;
};
typedef std::list<SpecialItemDrop> SpecialItemDropList;

struct LuckDrop
{
	LuckDrop() : Type(0), VipLevel(0), Rate(0) {}
	int32_t	Type;
	int32_t	VipLevel;
	SpecialItemDropList ItemList;
	int32_t	Rate;
};

class LuckDropTable
{
public:
	LuckDropTable();
	void		AddLuckDrop( LuckDrop* p_stu );
	int32_t		GetLuckRate( int32_t Type, int32_t VipLevel ) const;
	void		GetItem( MemChrBag* pItem, int32_t Type, int32_t VipLevel ) const;
private:
	std::map<std::pair<int,int>, LuckDrop> m_LuckDropMap;
};

struct RateItem
{
	int32_t	nItemId;
	int32_t	nItemClass;
	int32_t	nItemCount;
	int32_t	nRate;
	int8_t	nBind;
	int32_t	nGongGaoId;
};
// RefreshMonsterCfg
struct RefreshMonsterCfg
{
    RefreshMonsterCfg()
        : nStartTime(0), LastFreshTime(0), nDiffTime(0), nIndex(0), GongGaoId(0) {}
    int32_t nStartTime;     // OpenTime
    mutable int32_t LastFreshTime;  // Runtime tracking (mutable for const list)
    int32_t nDiffTime;      // Interval
    int32_t nIndex;         // Typeid
    int32_t GongGaoId;      // Language
};
typedef std::list<RefreshMonsterCfg> RefreshMonsterCfgList;

// CfgWuHunShop
struct CfgWuHunShop
{
    CfgWuHunShop() : Index(0), Rate(0), Const(0), ShowCost(0), CutPic(0) {}
    int32_t Index;
    int32_t Rate;
    int32_t Const;
    int32_t ShowCost;
    int32_t CutPic;
    MemChrBag Item;
};
typedef std::list<CfgWuHunShop> CfgWuHunShopList;

// ClbAimCfg - VIP club aim config (ClubAim.txt)
struct ClbAimCfg
{
    ClbAimCfg() : nId(0), nNeedVipLevel(0), nNeedCount(0), nAddDropTimes(0) {}
    int32_t nId;
    int32_t nNeedVipLevel;
    int32_t nNeedCount;
    int32_t nAddDropTimes;
};
typedef std::list<ClbAimCfg> ClbAimCfgList;

// TestServerReward
struct TestServerReward
{
    TestServerReward() : nType(0), nParm(0), nGongId(0) {}
    int32_t nType;
    int32_t nParm;
    MemChrBagVector vItems;
    int32_t nGongId;
};
typedef std::map<int32_t, TestServerReward> TestServerRewardMap;

// Wan360Reward
struct Wan360Reward
{
    Wan360Reward() : Index(0) {}
    int32_t Index;
    MemChrBagVector Items;
};
typedef std::map<int32_t, Wan360Reward> Wan360RewardMap;

// Speed360Reward
struct Speed360Reward
{
    Speed360Reward() : StartTime(0), EndTime(0) {}
    int32_t StartTime;
    int32_t EndTime;
    MemChrBagVector Rewards;
};

// CfgSouGouSkin
struct CfgSouGouSkin
{
    CfgSouGouSkin() : nIcon(0) {}
    std::string platform;
    MemChrBagVector vReward;
    int32_t nIcon;
};
typedef std::map<std::string, CfgSouGouSkin> CfgSouGouSkinMap;

// CfgWeiXingGift (WeiXin.txt)
struct CfgWeiXingGift
{
    CfgWeiXingGift() : nIconId(0) {}
    std::string strPlatform;
    int32_t nIconId;
    MemChrBagVector vReward;
};
typedef std::map<std::string, CfgWeiXingGift> CfgWeiXingGiftMap;

// CfgSuperMember (SuperMember.txt)
struct CfgSuperMember
{
	CfgSuperMember() : nGold(0), nQQ(0), nIcon(0) {}
	std::string	strPlatform;
	int32_t		nGold;
	int32_t		nQQ;
	int32_t		nIcon;
};
typedef std::map<std::string, CfgSuperMember> CfgSuperMemberMap;

// CfgMobilePhoneGift (MobilePhoneGift.txt)
struct CfgMobilePhoneGift
{
	CfgMobilePhoneGift() : nIcon(0) {}
	std::string		strPlatform;
	int32_t			nIcon;
	MemChrBagVector	vItem;
};
typedef std::map<std::string, CfgMobilePhoneGift> CfgMobilePhoneGiftMap;

// CfgAdultGift (ShenFenYanZheng.txt)
struct CfgAdultGift
{
	CfgAdultGift() : nIconId(0) {}
	std::string		strPlatform;
	int32_t			nIconId;
	MemChrBagVector	vReward;
};
typedef std::map<std::string, CfgAdultGift> CfgAdultGiftMap;

class CfgAdultGiftTable
{
public:
	void Add( const CfgAdultGift& stu ) { m_map[stu.strPlatform] = stu; }
	const CfgAdultGift* GetAdultGift( const std::string& platform ) const;
	const CfgAdultGiftMap& GetMap() const { return m_map; }
private:
	CfgAdultGiftMap	m_map;
	friend class CfgData;
};

// ZeroBuyPetCfg
struct ZeroBuyPetCfg
{
	ZeroBuyPetCfg() : nGold(0), nMailId(0) {}
	int32_t		nGold;
	int32_t		nMailId;
	MemChrBag	cItems;
};

typedef std::list<RateItem> RateItemList;

// XingMaiCfg
struct XingMaiCfg
{
    XingMaiCfg() : Level(0), PlayerLevel(0), GongGaoId(0), NeedBossScore(0), BossScoreLimit(0) {}
    int32_t Level;
    int32_t PlayerLevel;
    ItemDataList CostItems;
    int32_t GongGaoId;
    AddAttrList AttrList;
    int32_t NeedBossScore;
    int32_t BossScoreLimit;
};
typedef std::map<int32_t, XingMaiCfg> XingMaiCfgMap;

struct CfgXingMaiSlot
{
    CfgXingMaiSlot() : nIndex(0), nLevel(0), nScore(0) {}
    int8_t nIndex;
    int32_t nLevel;
    int32_t nScore;
};
typedef std::map<int32_t, CfgXingMaiSlot> CfgXingMaiSlotMap;

// MonthlyChouJiangCfg
struct MonthlyChouJiangCfg
{
    MonthlyChouJiangCfg() : nId(0), nRecharges(0), nAddValues(0), nGetTimes(0) {}
    int32_t nId;
    int32_t nRecharges;
    int32_t nAddValues;
    int32_t nGetTimes;
};
typedef std::map<int32_t, MonthlyChouJiangCfg> MonthlyChouJiangCfgMap;

// MonthlyChouJiangTable
class MonthlyChouJiangTable
{
public:
    MonthlyChouJiangTable();
    ~MonthlyChouJiangTable();

    void AddMonthlyChouJiangItemMap(int32_t nMonth, int32_t nId, const RateItem& item);
    void AddMonthlyChouJiangCfg(const MonthlyChouJiangCfg& cfg);
    const MonthlyChouJiangCfgMap* GetMonthlyChouJiangCfgMap() const { return &m_CfgMap; }
    bool RandRateItem(RateItem& outItem, int32_t nMonth, std::list<int32_t>& excludeList) const;

private:
    typedef std::map<int32_t, RateItem> MonthItemMap;
    std::map<int32_t, MonthItemMap> m_MonthItems;
    MonthlyChouJiangCfgMap m_CfgMap;
};

// WuHun Config
struct WuHunItem
{
	WuHunItem() { CleanUp(); }
	void CleanUp()
	{
		nId = 0;
		nLv = 0;
		nType = 0;
		nQuality1 = 0;
		nGainCondition = 0;
		nTalentId = 0;
		nTalentLevel = 0;
		nAuction = 0;
		nPrice = 0;
		nOverlay = 0;
		nGrade = 0;
		nQuality = 0;
		nDressLevel = 0;
		nNeedQuality = 0;
		lAttrList.clear();
	}

	int32_t		nId;
	int32_t		nLv;
	int32_t		nType;
	int32_t		nQuality1;
	int32_t		nGainCondition;
	AddAttrList	lAttrList;
	int32_t		nTalentId;
	int32_t		nTalentLevel;
	std::string	sName;
	int32_t		nAuction;
	int32_t		nPrice;
	int32_t		nOverlay;
	int32_t		nGrade;
	int32_t		nQuality;
	int32_t		nDressLevel;
	int32_t		nNeedQuality;
};
typedef std::map<int32_t, WuHunItem> WuHunItemMap;

struct CreateWuHun
{
	CreateWuHun() { CleanUp(); }
	void CleanUp()
	{
		nId = 0;
		nLv = 0;
		nType = 0;
		nNpcID = 0;
		nWuHunID = 0;
		GetItemRate.clear();
		GetItemRate2.clear();
		ConstItem.clear();
		SpecialCost.m_nId = 0;
		SpecialCost.m_nClass = 0;
		SpecialCost.m_nCount = 0;
	}

	int32_t		nId;
	int32_t		nLv;
	int32_t		nType;
	RateItemList	GetItemRate;
	RateItemList	GetItemRate2;
	int32_t		nNpcID;
	int32_t		nWuHunID;
	ItemData		SpecialCost;
	ItemDataList	ConstItem;
};
typedef std::map<int32_t, CreateWuHun> CreateWuHunMap;





#include "CMingGeTable.h"
#include "TreasureMap.h"
#include "CKunExt.h"
#include "CXinMo.h"
#include "CDaTingReward.h"

struct TreasureHunterCfg
{
	TreasureHunterCfg() : nId(0), nRequire(0), GongGaoId(0), nType(0) {}
	int32_t nId;
	MemChrBagVector Items;
	int32_t nRequire;
	int32_t GongGaoId;
	int32_t nType;
};
typedef std::map<int32_t, TreasureHunterCfg> TreasureHunterCfgMap;

// BuyGift (合服每日限购)
struct CfgBuyGift
{
	CfgBuyGift() : nIndex(0), nGold(0), nBroad(0) {}
	int32_t nIndex;
	int32_t nGold;
	MemChrBagVector vGift;
	int32_t nBroad;
	void CleanUp()
	{
		nIndex = 0;
		nGold = 0;
		nBroad = 0;
		vGift.clear();
	}
};
typedef std::map<int32_t, CfgBuyGift> CfgBuyGiftTable;

// SuperTeHui
struct SuperTeHuiCfg
{
    SuperTeHuiCfg() : nIndex(0), nNeedVip(0), nPrice(0), nGongGaoId(0) {}
    int32_t nIndex;
    int32_t nNeedVip;
    MemChrBagVector Items;
    int32_t nPrice;
    int32_t nGongGaoId;
};
typedef std::map<int32_t, SuperTeHuiCfg> SuperTeHuiCfgMap;

// JewelPavilion
struct JewelPavilionCfg
{
    JewelPavilionCfg() : nDay(0), nIndex(0), nPrice(0) {}
    int32_t nDay;
    int32_t nIndex;
    MemChrBag Item;
    int32_t nPrice;
};
typedef std::map<std::pair<int32_t, int32_t>, JewelPavilionCfg> JewelPavilionCfgMap;

// ShangRen
struct ShangRenCfg
{
    ShangRenCfg() : nId(0), nPrice(0) {}
    int32_t nId;
    MemChrBagVector vItem;
    int32_t nPrice;
};
typedef std::map<int32_t, ShangRenCfg> ShangRenCfgMap;

//========================================================================
struct CrossTowerCfg
{
	CrossTowerCfg()
	{
		MapId		= 0;
		NextMapId	= 0;
		LastMapId	= 0;
		MaxPlayer	= 0;
		MaxScore	= 0;
		MinScore	= 0;
		KillCount	= 0;
		Floor		= 0;
		MailId		= 0;
	}

	int32_t				MapId;
	int32_t				NextMapId;
	int32_t				LastMapId;
	int32_t				MaxPlayer;
	int32_t				MaxScore;
	int32_t				MinScore;
	int32_t				KillCount;
	int32_t				Floor;
	std::vector<MemChrBag>	RewardVt;
	std::vector<MemChrBag>	TopRewardVt;
	int32_t				MailId;
};
typedef std::map<int32_t, CrossTowerCfg> CrossTowerCfgMap;

// ===== CfgGemLevelUp Config =====
struct CfgGemLevelUp
{
    CfgGemLevelUp()
        : nNeedItemId(0), nNeedItemCount(0), nCostMoney(0), nNextGemId(0), nBroadId(0)
    {}
    int32_t nNeedItemId;
    int32_t nNeedItemCount;
    int32_t nCostMoney;
    int32_t nNextGemId;
    int32_t nBroadId;
};

class CfgGemLevelUpTable
{
public:
    CfgGemLevelUpTable() {}
    ~CfgGemLevelUpTable() {}

    void Add(int32_t nId, const CfgGemLevelUp& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgGemLevelUp* Get(int32_t nId) const
    {
        std::map<int32_t, CfgGemLevelUp>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgGemLevelUp> m_mData;
};

// ===== CfgMoFu Config =====
struct CfgMoFu
{
    CfgMoFu()
        : nId(0), nCostGold(0), nRecycleItemId(0), nRecycleItemCount(0)
    {}
    int32_t nId;
    int32_t nCostGold;
    int32_t nRecycleItemId;
    int32_t nRecycleItemCount;
};

class CfgMoFuTable
{
public:
    CfgMoFuTable() {}
    ~CfgMoFuTable() {}

    void Add(int32_t nId, const CfgMoFu& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgMoFu* Get(int32_t nId) const
    {
        std::map<int32_t, CfgMoFu>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgMoFu> m_mData;
};

// ===== CfgShenYaoEquip Config =====
struct CfgShenYaoEquip
{
    CfgShenYaoEquip()
        : nCostGold(0)
    {}
    AttrAddonVector m_vAddAttr;
    int32_t nCostGold;
};

typedef std::map<std::pair<int32_t, int32_t>, CfgShenYaoEquip> CfgShenYaoEquipMap;

class CfgShenYaoEquipTable
{
public:
    CfgShenYaoEquipTable() {}
    ~CfgShenYaoEquipTable() {}

    void Add(int32_t nPos, int32_t nLevel, const CfgShenYaoEquip& stu)
    {
        m_mData[std::make_pair(nPos, nLevel)] = stu;
    }

    const CfgShenYaoEquip* Get(int32_t nPos, int32_t nLevel) const
    {
        std::map<std::pair<int32_t, int32_t>, CfgShenYaoEquip>::const_iterator it = m_mData.find(std::make_pair(nPos, nLevel));
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    CfgShenYaoEquipMap m_mData;
};

// ===== CfgEquipStrengthen Config =====
struct CfgEquipStrengthen
{
    CfgEquipStrengthen()
        : m_nGongGaoId(0)
    {
        memset(&m_CostItem, 0, sizeof(m_CostItem));
    }
    AttrAddonVector m_vAddAttr;
    ItemData m_CostItem;
    int32_t m_nGongGaoId;
};

class CfgEquipStrengthenTable
{
public:
    CfgEquipStrengthenTable() {}
    ~CfgEquipStrengthenTable() {}

    void Add(int32_t nPos, int32_t nLevel, const CfgEquipStrengthen& stu)
    {
        m_mData[std::make_pair(nPos, nLevel)] = stu;
    }

    const CfgEquipStrengthen* Get(int32_t nPos, int32_t nLevel) const
    {
        std::map<std::pair<int32_t, int32_t>, CfgEquipStrengthen>::const_iterator it = m_mData.find(std::make_pair(nPos, nLevel));
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<std::pair<int32_t, int32_t>, CfgEquipStrengthen> m_mData;
};

// ===== CfgEquipUpPos Config =====
struct CfgEquipUpPos
{
    CfgEquipUpPos()
        : m_nNeedLevel(0), m_nTotalRate(0), m_nRate(0), m_nGongGaoId(0)
    {
        memset(&m_CostItem, 0, sizeof(m_CostItem));
    }
    AttrAddonVector m_vAddAttr;
    int32_t m_nNeedLevel;
    ItemData m_CostItem;
    int32_t m_nTotalRate;
    int32_t m_nRate;
    int32_t m_nGongGaoId;
};

class CfgEquipUpPosTable
{
public:
    CfgEquipUpPosTable() {}
    ~CfgEquipUpPosTable() {}

    void Add(int32_t nPos, int32_t nLevel, const CfgEquipUpPos& stu)
    {
        m_mData[std::make_pair(nPos, nLevel)] = stu;
    }

    const CfgEquipUpPos* Get(int32_t nPos, int32_t nLevel) const
    {
        std::map<std::pair<int32_t, int32_t>, CfgEquipUpPos>::const_iterator it = m_mData.find(std::make_pair(nPos, nLevel));
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<std::pair<int32_t, int32_t>, CfgEquipUpPos> m_mData;
};

// ===== CfgCurrencyDuiHuan Config =====
struct CfgCurrencyDuiHuan
{
    CfgCurrencyDuiHuan()
        : m_nMoShi(0), m_nShengYaoBi(0), m_nJinBi(0), m_nDailyLimit(0)
    {}
    int32_t m_nMoShi;
    int32_t m_nShengYaoBi;
    int32_t m_nJinBi;
    int32_t m_nDailyLimit;
};

class CfgCurrencyDuiHuanMap
{
public:
    CfgCurrencyDuiHuanMap() {}
    ~CfgCurrencyDuiHuanMap() {}
    void Add(int32_t nId, const CfgCurrencyDuiHuan& stu)    {
        m_mData[nId] = stu;    }
    const CfgCurrencyDuiHuan* Get(int32_t nId) const    {        std::map<int32_t, CfgCurrencyDuiHuan>::const_iterator it = m_mData.find(nId);        if (it != m_mData.end()) return &it->second;        return NULL;    }
private:    std::map<int32_t, CfgCurrencyDuiHuan> m_mData;};

// ===== CfgMoFuSuit Config =====
struct CfgMoFuSuit
{
    CfgMoFuSuit()
        : nSuitId(0), nNeedCount(0)
    {}
    int32_t nSuitId;
    int32_t nNeedCount;
    AttrAddonVector vAddAttr;
};
class CfgMoFuSuitMap
{
public:
    CfgMoFuSuitMap() {}
    ~CfgMoFuSuitMap() {}
    void Add(int32_t nSuitId, const CfgMoFuSuit& stu)    {        m_mData[nSuitId] = stu;    }
    const CfgMoFuSuit* Get(int32_t nSuitId) const    {        std::map<int32_t, CfgMoFuSuit>::const_iterator it = m_mData.find(nSuitId);        if (it != m_mData.end()) return &it->second;        return NULL;    }
private:    std::map<int32_t, CfgMoFuSuit> m_mData;};

// ===== CfgPetEquip Config =====
struct CfgPetEquip
{
    CfgPetEquip()
        : nId(0), nPetId(0), nEquipId(0), nAttrType(0), nAttrValue(0), nLevel(0)
    {}
    int32_t nId;
    int32_t nPetId;
    int32_t nEquipId;
    int32_t nAttrType;
    int32_t nAttrValue;
    int32_t nLevel;
};
typedef std::map<int32_t, CfgPetEquip> CfgPetEquipMap;

class CfgPetEquipTable
{
public:
    CfgPetEquipTable() {}
    ~CfgPetEquipTable() {}

    void Add(int32_t nId, const CfgPetEquip& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgPetEquip* Get(int32_t nId) const
    {
        std::map<int32_t, CfgPetEquip>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgPetEquip> m_mData;
};

// ===== CfgCityWar Config =====
struct CfgCityWar
{
    CfgCityWar()
        : nId(0), nMapId(0), nDuration(0), nRewardExp(0), nRewardMoney(0),
          nNeedLevel(0), nMinPlayer(0), nMaxPlayer(0)
    {}
    int32_t nId;
    int32_t nMapId;
    int32_t nDuration;
    int32_t nRewardExp;
    int32_t nRewardMoney;
    int32_t nNeedLevel;
    int32_t nMinPlayer;
    int32_t nMaxPlayer;
};
typedef std::map<int32_t, CfgCityWar> CfgCityWarMap;

class CfgCityWarTable
{
public:
    CfgCityWarTable() {}
    ~CfgCityWarTable() {}

    void Add(int32_t nId, const CfgCityWar& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgCityWar* Get(int32_t nId) const
    {
        std::map<int32_t, CfgCityWar>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgCityWar> m_mData;
};

// ===== CfgCampWar Config =====
struct CfgCampWar
{
    CfgCampWar()
        : nId(0), nMapId(0), nDuration(0), nNeedLevel(0), nRewardExp(0), nRewardMoney(0)
    {}
    int32_t nId;
    int32_t nMapId;
    int32_t nDuration;
    int32_t nNeedLevel;
    int32_t nRewardExp;
    int32_t nRewardMoney;
};
typedef std::map<int32_t, CfgCampWar> CfgCampWarMap;

class CfgCampWarTable
{
public:
    CfgCampWarTable() {}
    ~CfgCampWarTable() {}

    void Add(int32_t nId, const CfgCampWar& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgCampWar* Get(int32_t nId) const
    {
        std::map<int32_t, CfgCampWar>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgCampWar> m_mData;
};

// ===== CfgPeerlessWar Config =====
struct CfgPeerlessWar
{
    CfgPeerlessWar()
        : nId(0), nMapId(0), nDuration(0), nNeedLevel(0), nRewardExp(0), nRewardMoney(0), nMaxPlayer(0)
    {}
    int32_t nId;
    int32_t nMapId;
    int32_t nDuration;
    int32_t nNeedLevel;
    int32_t nRewardExp;
    int32_t nRewardMoney;
    int32_t nMaxPlayer;
};
typedef std::map<int32_t, CfgPeerlessWar> CfgPeerlessWarMap;

class CfgPeerlessWarTable
{
public:
    CfgPeerlessWarTable() {}
    ~CfgPeerlessWarTable() {}

    void Add(int32_t nId, const CfgPeerlessWar& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgPeerlessWar* Get(int32_t nId) const
    {
        std::map<int32_t, CfgPeerlessWar>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgPeerlessWar> m_mData;
};

// ===== CfgWorldBoss Config =====
struct CfgWorldBoss
{
    CfgWorldBoss()
        : nId(0), nBossId(0), nMapId(0), nLevel(0), nReviveTime(0),
          nRewardExp(0), nRewardMoney(0), nHp(0), nAttack(0), nDefense(0)
    {}
    int32_t nId;
    int32_t nBossId;
    int32_t nMapId;
    int32_t nLevel;
    int32_t nReviveTime;
    int32_t nRewardExp;
    int32_t nRewardMoney;
    int32_t nHp;
    int32_t nAttack;
    int32_t nDefense;
};
typedef std::map<int32_t, CfgWorldBoss> CfgWorldBossMap;

class CfgWorldBossTable
{
public:
    CfgWorldBossTable() {}
    ~CfgWorldBossTable() {}

    void Add(int32_t nId, const CfgWorldBoss& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgWorldBoss* Get(int32_t nId) const
    {
        std::map<int32_t, CfgWorldBoss>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgWorldBoss> m_mData;
};

// ===== CfgGemAdd Config =====
struct CfgGemAdd
{
    CfgGemAdd()
        : nId(0), nGemType(0), nAddRate(0), nEffectValue(0)
    {}
    int32_t nId;
    int32_t nGemType;
    int32_t nAddRate;
    int32_t nEffectValue;
};
typedef std::map<int32_t, CfgGemAdd> CfgGemAddMap;

class CfgGemAddTable
{
public:
    CfgGemAddTable() {}
    ~CfgGemAddTable() {}

    void Add(int32_t nId, const CfgGemAdd& stu)
    {
        m_mData[nId] = stu;
    }

    const CfgGemAdd* Get(int32_t nId) const
    {
        std::map<int32_t, CfgGemAdd>::const_iterator it = m_mData.find(nId);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, CfgGemAdd> m_mData;
};

// ===== BaoKuFuBen Config =====
struct BaoKuFuBen
{
    BaoKuFuBen() : nMapId(0), nLevel(0), nNeedLevel(0), nCostItemId(0), nCostItemCount(0) {}
    int32_t nMapId;
    int32_t nLevel;
    int32_t nNeedLevel;
    int32_t nCostItemId;
    int32_t nCostItemCount;
};
typedef std::map<int32_t, BaoKuFuBen> BaoKuFuBenMap;

// ===== BaoKuRandom Config =====
struct BaoKuRandom
{
    BaoKuRandom() : nId(0), nRate(0), nItemId(0), nItemCount(0) {}
    int32_t nId;
    int32_t nRate;
    int32_t nItemId;
    int32_t nItemCount;
};
typedef std::map<int, BaoKuRandom> BaoKuRandomMap;

// ===== CfgDropRecord Config =====
struct CfgDropRecord
{
    CfgDropRecord() : nId(0), nDropId(0), nProbability(0), nItemClass(0), nSpecial(0) {}
    int32_t nId;
    int32_t nDropId;
    int32_t nProbability;
    int32_t nItemClass;
    int32_t nSpecial;
};
typedef std::map<int32_t, CfgDropRecord> CfgDropRecordMap;

// ===== CfgDungeonSummon Config =====
struct CfgDungeonSummon
{
    CfgDungeonSummon() : nId(0), nMonsterId(0), nCount(0), nWave(0) {}
    int32_t nId;
    int32_t nMonsterId;
    int32_t nCount;
    int32_t nWave;
};
typedef std::map<int32_t, CfgDungeonSummon> CfgDungeonSummonMap;

// ===== ShiQuCfg Config =====
struct ShiQuCfg
{
    ShiQuCfg() : nId(0), nNeedLevel(0), nGold(0) {}
    int32_t nId;
    int32_t nNeedLevel;
    int32_t nGold;
};
typedef std::map<int32_t, ShiQuCfg> ShiQuCfgMap;

// ===== CfgMiniClient Config =====
struct CfgMiniClient
{
    CfgMiniClient() : nId(0), nPlatform(0), nUrl(""), nVersion("") {}
    int32_t nId;
    int32_t nPlatform;
    std::string nUrl;
    std::string nVersion;
};
typedef std::map<int32_t, CfgMiniClient> CfgMiniClientMap;

// ===== VipEquipPosLevelUp Config =====
struct VipEquipPosLevelUp
{
    VipEquipPosLevelUp() : nPos(0), nLevel(0), nNeedVip(0), nCostGold(0) {}
    int32_t nPos;
    int32_t nLevel;
    int32_t nNeedVip;
    int32_t nCostGold;
};
typedef std::map<std::pair<int32_t, int32_t>, VipEquipPosLevelUp> VipEquipPosLevelUpMap;

// ===== VipEQuipPosSuit Config =====
struct VipEQuipPosSuit
{
    VipEQuipPosSuit() : nSuitId(0), nCount(0), nAttrRate(0), nTalentId(0), TalentLevel(0) {}
    int32_t nSuitId;
    int32_t nCount;
    int32_t nAttrRate;
    int32_t nTalentId;
    int32_t TalentLevel;
};
typedef std::map<int32_t, VipEQuipPosSuit> VipEQuipPosSuitMap;

// ===== CVipClubLuckyDrop Config =====
struct CVipClubLuckyDrop
{
    CVipClubLuckyDrop() : nIndex(0), nRate(0), nTotalRate(0) {}
    int32_t nIndex;
    int32_t nRate;
    int32_t nTotalRate;
    MemChrBagVector vItem;
    std::list<RateItem> lRateItemList;			// 2019: Club掉落概率列表
};
typedef std::map<int32_t, CVipClubLuckyDrop> CVipClubLuckyDropMap;

// ===== CfgYYSuperBuff Config =====
struct CfgYYSuperBuff
{
    CfgYYSuperBuff() : nId(0), nBuffId(0), nBuffLevel(0) {}
    int32_t nId;
    int32_t nBuffId;
    int32_t nBuffLevel;
};
typedef std::map<int32_t, CfgYYSuperBuff> CfgYYSuperBuffMap;

// ===== ChristmasDuiHuan Config =====
struct ChristmasDuiHuan
{
    ChristmasDuiHuan() : nId(0), nNeedItemId(0), nNeedItemCount(0), nGetItemId(0), nGetItemCount(0) {}
    int32_t nId;
    int32_t nNeedItemId;
    int32_t nNeedItemCount;
    int32_t nGetItemId;
    int32_t nGetItemCount;
};
typedef std::map<int32_t, ChristmasDuiHuan> ChristmasDuiHuanMap;

// ===== ContributionCfg Config =====
struct ContributionCfg
{
    ContributionCfg() : nLevel(0), nNeedContribution(0), nAttrRate(0) {}
    int32_t nLevel;
    int32_t nNeedContribution;
    int32_t nAttrRate;
};
typedef std::map<int32_t, ContributionCfg> ContributionCfgMap;

// ===== DamnationCfg Config =====
struct DamnationCfg
{
    DamnationCfg() : nId(0), nType(0), nParam(0), nRewardExp(0), nRewardMoney(0)
        , CostMoney(0), HpPecent(0), Probability(0), GongGaoId(0) {}
    int32_t nId;
    int32_t nType;
    int32_t nParam;
    int32_t nRewardExp;
    int32_t nRewardMoney;
    // Extended fields for Curse system
    int64_t CostMoney;
    std::list<AddAttribute> AttrList;
    std::list<ItemData> CostItems;
    int32_t HpPecent;
    int32_t Probability;
    int32_t GongGaoId;
};
typedef std::map<int32_t, DamnationCfg> DamnationCfgMap;

// ===== DiligenceCfg Config =====
struct DiligenceCfg
{
    DiligenceCfg() : nDay(0), nNeedLogin(0), nRewardId(0) {}
    int32_t nDay;
    int32_t nNeedLogin;
    int32_t nRewardId;
};
typedef std::map<int32_t, DiligenceCfg> DiligenceCfgMap;

// ===== DuiHuanLimit Config =====
struct DuiHuanLimit
{
    DuiHuanLimit() : nId(0), nLimit(0) {}
    int32_t nId;
    int32_t nLimit;
};
typedef std::map<int32_t, DuiHuanLimit> DuiHuanLimitMap;

// ===== FunctionOpenMail Config =====
struct FunctionOpenMail
{
    FunctionOpenMail() : nFuncId(0), nMailId(0) {}
    int32_t nFuncId;
    int32_t nMailId;
};
typedef std::map<int32_t, FunctionOpenMail> FunctionOpenMailMap;

// ===== GoblinCfg Config =====
struct GoblinCfg
{
    GoblinCfg() : nId(0), nMonsterId(0), nRate(0), SuitId(0), ConstCurr(0), UpAttr(0), m_nAddAttrType(0) {}
    int32_t nId;
    int32_t nMonsterId;
    int32_t nRate;
    int32_t SuitId;
    int32_t ConstCurr;
    int32_t UpAttr;
    int32_t m_nAddAttrType;
};
typedef std::map<int32_t, GoblinCfg> GoblinCfgMap;

// ===== GuWuCfg Config =====
struct GuWuCfg
{
    GuWuCfg() : nId(0), nLevel(0), nCostGold(0), nAddPercent(0) {}
    int32_t nId;
    int32_t nLevel;
    int32_t nCostGold;
    int32_t nAddPercent;
};
typedef std::map<int32_t, GuWuCfg> GuWuCfgMap;

// ===== HoeCfg Config =====
struct HoeCfg
{
    HoeCfg() : nLevel(0), nNeedExp(0), nCostGold(0) {}
    int32_t nLevel;
    int32_t nNeedExp;
    int32_t nCostGold;
};
typedef std::map<int32_t, HoeCfg> HoeCfgMap;

// ===== LuDaShiVip Config =====
struct LuDaShiVip
{
    LuDaShiVip() : nLevel(0), nNeedExp(0) {}
    int32_t nLevel;
    int32_t nNeedExp;
    MemChrBag Gift;
};
typedef std::map<int32_t, LuDaShiVip> LuDaShiVipMap;

// ===== SpecialBossMapCfg Config =====
struct SpecialBossMapCfg
{
    SpecialBossMapCfg() : nMapId(0), nBossId(0), nRate(0) {}
    int32_t nMapId;
    int32_t nBossId;
    int32_t nRate;
};
typedef std::map<int32_t, SpecialBossMapCfg> SpecialBossMapCfgMap;

// ===== UltimateChallengeCfg Config =====
struct UltimateChallengeCfg
{
    UltimateChallengeCfg() : nLevel(0), nMonsterId(0), nRewardExp(0), nRewardMoney(0) {}
    int32_t nLevel;
    int32_t nMonsterId;
    int32_t nRewardExp;
    int32_t nRewardMoney;
};
typedef std::map<int32_t, UltimateChallengeCfg> UltimateChallengeCfgMap;

// ===== WingEquipPolish Config =====
struct WingEquipPolish
{
    WingEquipPolish() : nId(0), nLevel(0), nCostGold(0), nAttrType(0), nAttrValue(0) {}
    int32_t nId;
    int32_t nLevel;
    int32_t nCostGold;
    int32_t nAttrType;
    int32_t nAttrValue;
};
typedef std::map<int32_t, WingEquipPolish> WingEquipPolishMap;

// ===== WinRefiningCfg Config =====
struct WinRefiningCfg
{
    WinRefiningCfg() : nLevel(0), nCostGold(0), nRate(0) {}
    int32_t nLevel;
    int32_t nCostGold;
    int32_t nRate;
};
typedef std::map<int32_t, WinRefiningCfg> WinRefiningCfgMap;

// ===== XunLeiCfg Config =====
struct XunLeiCfg
{
    XunLeiCfg() : nLevel(0), nNeedExp(0) {}
    int32_t nLevel;
    int32_t nNeedExp;
    MemChrBag Reward;
};
typedef std::map<int32_t, XunLeiCfg> XunLeiCfgMap;

// ===== CfgTalentActive Config =====
struct CfgTalentActive
{
    CfgTalentActive() : nId(0) {}
    int32_t nId;
    std::list<ItemData> lItems;
};
typedef std::map<int32_t, CfgTalentActive> CfgTalentActiveMap;




// ===== Missing typedefs for decompiled code =====
struct ActDropItem
{
    ActDropItem() : nMinLevel(0), nMaxLevel(0), nMapType(0), nId(0), nClass(0), nCount(0), nBind(0), nRate(0), nStartTime(0), nEndTime(0), nProbability(0) {}
    int32_t nMinLevel;
    int32_t nMaxLevel;
    int32_t nMapType;
    int32_t nId;
    int32_t nClass;
    int32_t nCount;
    int32_t nBind;
    int32_t nRate;
    int32_t nStartTime;
    int32_t nEndTime;
    int32_t nProbability;
};
typedef std::list<ActDropItem> ActDropItemList;

typedef std::vector<BuffAttr> BuffAttrVector;

typedef std::vector<int32_t> Int32VtVector;

typedef std::list<Param2> Param2List;

struct GroupMonster { int32_t nGroupId; int32_t nMonsterId; int32_t nCount; };
typedef std::vector<GroupMonster> GroupMonsterVector;

typedef std::list<AddAttribute> TalentAddonList;

struct TaskDrop { int32_t nTaskId; int32_t nDropId; int32_t nProbability; };
typedef std::list<TaskDrop> TaskDropList;

// ===== Missing structs ported from decompiled =====
struct CfgJueWei
{
    CfgJueWei() : nIndex(0), nNeedHonor(0), nAttrRate(0), nGongGaoId(0) {}
    int8_t  nIndex;
    int32_t nNeedHonor;
    AddAttrList lAttr;
    int32_t nAttrRate;
    int32_t nGongGaoId;
};

class CfgJueWeiTable
{
public:
    CfgJueWeiTable() {}
    ~CfgJueWeiTable() {}

    void AddJueWei(const CfgJueWei& cfg) { m_mData[cfg.nIndex] = cfg; }

    const CfgJueWei* GetJueWei(int8_t nIndex) const
    {
        std::map<int8_t, CfgJueWei>::const_iterator it = m_mData.find(nIndex);
        if (it != m_mData.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int8_t, CfgJueWei> m_mData;
};

// CfgWuHunShopMap (shop grouped by ShopId)
typedef std::map<int32_t, std::list<CfgWuHunShop> > CfgWuHunShopMap;

struct CfgGroupIcon
{
	int32_t nId;
	int32_t bShowInCross;
	std::string platfrom;
};
struct CfgBossFirstKilled
{
	int32_t Mid; int32_t RewardType; int32_t RewardValue;
	int32_t StartDay; int32_t EndDay; int32_t GongGaoId;
};
struct ChargeDungeonCfg
{
	int32_t nId; int32_t nMinKaiFuDay; int32_t nMaxKaiFuDay;
	int32_t nChargeValue; int32_t nDungeonId;
};
struct CfgMonsterAddAttr
{
	int32_t WorldBossLevelMin;
	int32_t WorldBossLevelMax;
	std::vector<AttrAddon> AttrVector;
};
struct XiangYaoTaskCfg
{
	int32_t TaskId; int32_t Star; int32_t MinLevel;
	int32_t MaxLevel; int32_t Rate;
};
struct CfgMonsterAI
{
	int32_t id, style, target, escape_hp, view_range, move_range;
	int32_t rest_range, rest_time_min, rest_time_max, rest_ratio;
	int32_t run_distance, run_range, run_cd, pursuit_range;
};
struct CfgMonsterAdjust
{
	int32_t mid; int32_t adj_level; int32_t level; int32_t exp;
	int32_t vAttr[50];
};
class CfgBFZLEnterCostTable
{
public:
	bool AddEnterCost(int32_t nTimes, const std::list<ItemData>& vItem) {
		m_mEnterCost[nTimes] = vItem; return true;
	}
	std::map<int32_t, std::list<ItemData>> m_mEnterCost;
};


class CfgData
{
public:
	CfgData();
	~CfgData();

public:
	bool init(int32_t line, int32_t debug);
	void reload();

public:
	const int32_t getServerStartTime();
	const int32_t getServerStartDayTime();
	const int32_t getServerDiffTime();
	int32_t getServerType() const;
	bool isUniteServer() const;
	int32_t getServerDiffDay( int32_t serverType ) const;

	const CfgActivityTable&	getAllActivity();
	CfgActivity*			getActivity(int32_t id);
	const CfgMapEventList&	getActivityEvents( int32_t activity_id, MapId_t nMapId );
	
	CfgActivityMonster*		getActivityMonster( int32_t id );
	CfgActivityNpc*			getActivityNpc(int32_t id);
	CfgActivityPlant*		getActivityPlant( int32_t Id );
	CfgActivityDropTable*	getActivityDrops();
	CfgActivityTrap*		getActivityTrap( int32_t id );

	const CfgAnnoucementTimeTable& getAllAnnoucementTime() const;

	CfgBuff* getBuff(int32_t id);

	const CfgDungeonTable& getDungeonAll();
	CfgDungeon* getDungeon(int32_t id);
	const CfgMapEventList& getDungeonEvent( int32_t dungonid );
	CfgDungeonMonster* getDungeonMonster(int32_t id);
	CfgDungeonPlant* getDungeonPlant(int32_t id);
	CfgDungeonTrap* getDungeonTrap(int32_t id);

	const CfgEquip* getEquip(int32_t id) const;
	CfgChrShop* getChrShop( int32_t index );

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
	CfgMapPlantVector* getPlantOnMap(int32_t mapid);

	CfgMapRegion* getMapRegion(int32_t id);
	CfgMapRegionVector* getRegionOnMap(int32_t mapid);

	CfgMonster* getMonster(int32_t mid);
	CfgMonsterAdjust* GetMonsterAdjust(int32_t mid, int32_t nLevel, int32_t nDiff);
	int32_t GetMonsterReviveTime(int32_t Time, int32_t BossId);
	int32_t GetMapMonsterId() { return ++m_MapMonsterId; }
	bool isMonsterBroadcast(int32_t mid);
	CfgMonsterDropGroupVector* getMonsterDropGroup(int32_t group_id);
	CfgMonsterGroupDropVector* getMonsterGroupDrop(int32_t mid);
	CfgMonsterTaskDropVector* getMonsterTaskDrop(int32_t mid);
	const CfgDungeonDrop* randDungeonDrop( int32_t dungeonId );
	CfgDungeonReward* getDungeonReward(int32_t dungeonID);

	CfgBornAttr*  getBornAttr(Job_t jobindex);
	CfgChangeJobAttr* getChangeJobAttr(int32_t index);

	CfgNpc* getNpc(int32_t npcid);
	const CfgNpcTable& getNpcAll();
	CfgNpcAirport* getNpcAirport(int32_t id);
	CfgNpcKingdomShop* getNpcKingdomShop(int32_t id);

	CfgPlant* getPlant(int32_t id);

	CfgSkill* getSkill(int32_t id);
	CfgTask* getTask(int32_t id);


	CfgYellowStone* getYellowStone(int32_t id);
	PkDropRate*		GetPkDropRate( int32_t PkValues );
	int32_t getTaskDailyWindItem(int32_t tid, int32_t wind_point);


	CfgTrailer* getTrailer();
	CfgTrap* getTrap(int32_t id);
	CfgItemBase* getItemBase(int32_t id, int32_t type);
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

	int32_t getBaseJob(int32_t job);
	bool isBanChat(int32_t uid, int32_t nowTime);

	AttrAddonVector getItemEffect(int32_t id);

	void onAvgLevelUpdated(int32_t avgLevel);
	AttrAddonVector parseItemEffect(int32_t id,const std::string &str);
	MemChrBagVector parseAllItemString(int32_t id, const std::string &strItems);

	int32_t getCreateTime();
	int32_t getDebug();

	void calcAchievementCount();
	void onBanChatUpdated(int32_t action, int32_t uid, int32_t expire_time);

	const CfgEquipTable&			GetEquipTable() const;
	const CfgItemGemTable&			GetItemGemTable() const;
	const CfgItemCombiTable&		GetItemCombiTable() const;
	const CfgMagicBoxTable*		GetMagicBoxTable() const { return &m_cfgMagicBox; }
	const CfgFlopDrawTable*		GetFlopDrawTable() const { return &m_cfgFlopDraw; }
	const ShiZhuLevelUp*		GetShiZhuLevelUp( int32_t nId, int32_t nLevel ) const;
	const CfgShiZhuangTable*		GetShiZhuangTable() const { return &m_cfgShiZhuang; }
	const CfgBagSlotOpenTimeTable&	GetBagSlotOpenTimeTable() const;
	const CfgPetTable&				GetPetTable() const;
	const CfgPetEggTable&			GetPetEggTable() const;
	const CfgPetAttrInitRateTable&	GetPetAttrInitRateTable() const;
	const CfgPetIllusionTable&		GetPetIllusionTable() const;
	const CfgSkillLevelUpTable&		GetSkillLevelUpTable() const;
	const CfgTaskCycleTable&		GetTaskCycleTable() const;
	const CfgFamilyTask&			GetFamilyTaskTable() const;
	const CfgPetKnightTable&		GetPetKnightTable() const;
	const CfgFamilyPetRegistTable&	GetFamilyPetRegistTable() const;
	const TestServerReward*			GetTestServerReward( int32_t nId ) const;
	ActDropItemList				GetAcrDropList( int32_t nId ) const;

	int32_t					GetAttrBattle( int32_t nAttr ) const;	const CfgFamilyTable&			GetFamilyTable() const;
	const CfgCharPetTable&			GetCharPetTable() const;
	const CfgTeamTable&				GetTeamTable() const;
	const CfgInsidePetTable&		GetInsidePetTable() const;
	const CfgFamilyWarJoinRewardTable&	GetFamilyWarJoinRewardTable() const;
	const CfgFamilyLightExpTable&	GetFamilyLightExpTable() const;
	const CfgSoulAttrTable&			GetSoulAttrTable() const;
	const CfgHorseRacingRewardTable&	GetHorseRacingRewardTable() const;
	const CfgHallOfFameTable&		GetHallOfFameTable() const;
	const AchievementTable&			GetAchievementTable() const;
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
	CfgPetGift*					GetPetCfg( int32_t nId );
	ChouJiangConfig&			GetChouJiangCfg();
	CQiFuTable&					GetQiFuTable();
	VipTable&					GetVipTable();
	MemChrBagVector				GetSignReward( int8_t SiginCount );	
	CfgSignRewardTable&			GetSignRewardTable();
	CfgOnlineReward*			GetOnlineRewardCfg( int8_t id );
	CfgOnlineRewardTable&		 GetOnLineRewardTable();
	CfgSevenLoginRewrad*		GetSevenLoginRewardCfg( int8_t Day );
	CfgLevelGift*				GetLevelGiftCfg( int8_t Index );
	CfgLevelGiftTable&			GetLeveGiftTable();
	CfgWeekOnlineReward*		GetWeekOnlineReward( int32_t Week );
	CfgOffLineExp*				GetOfflineExpCfg( int32_t Level );
	VipCardCfg*					GetVipCardCfg( int8_t VipType );
	LuckDropTable&				GetLuckDropTableTable();
	const CVipClubLuckyDrop*	GetCVipClubLuckyDrop( int32_t nIndex ) const;
	CfgBossHome*				GetBossHomeCfg( int32_t MapId );
	bool						IsBossHomeMap( int32_t MapId );
	VipGuaJiMap*				GetVipGuaJiMapCfg( int32_t MapId);
	bool						IsVipGuaJiMap( int32_t MapId );
	FunctionOpenCfgMap&			GetOpenFunctionTable();
	FunctionOpenCfg*			GetOpenFunctionCfg( int32_t FunctionId );
	CfgMoLingRuQinMapInfo*		GetMLRQMapInfo( int32_t MapId );
	// 金币奖励任务
	void				InitMoneyRewardTask( TaskStateInfo (*pTask)[9], int32_t nLevel );
	int32_t				RandPdbfTask( int32_t nLevel );
	const BackEquipTask*		GetBackEquipTask( int32_t nId );
	int32_t				GetEquipBackTaskId( int32_t nLevel, int32_t nRandTimes );
	const ShenWeiTaskCfg*		GetShenWeiTaskCfg( int32_t nIndex );
	int32_t				RandXiangYaoTaskId( int32_t nLevel, bool bBest );
	int32_t				getXiangYaoStart( int32_t nTaskId );
	int32_t				InitXuWuTask( int32_t nLevel, int32_t nParam );
	int32_t				InitXinMoTask( int32_t nLevel, int32_t nParam );
	int32_t				RandQuality( int32_t nCurrentQuality );

	CfgItemGiftVector*			getPetGift(int32_t id);

	// V计划配置访问器

	// 国庆活动访问器
	const NationalDayTaskCfg*	GetNationalDayTaskCfg( int32_t nType, int32_t nId ) const;
	const NationalDayLevelCfg*	GetNationalDayLevelCfg( int32_t nLevel ) const;
	const NationalDayTaskCfgMap*	GetNationalDayTaskCfgMap() const;
	const NationalDayLevelCfgMap*	GetNationalDayLevelCfgMap() const;
	void				InitNationalDayTask();
	const CfgVplanMap*		GetCfgVplanMap() const;
	const CfgYYVipMap*		GetCfgYYVipMap() const;
	const CfgXunLeiMap*		GetXunLeiTable() const;
	const CfgLuDaShiMap*	GetLaDaShiHuiYuanMap() const;
	const CfgSwVipRewardMap*	GetSwVipRewardMap() const;
	const CfgSwVipRewardMap*	GetSwVipBarRewardMap() const;
	const CfgYYGameAppMap*	GetYYGameAppMap() const;
	const CfgSgGameAppMap*	GetSgGameAppMap() const;	CfgPlantEventEffect*		GetPlantEvent( int32_t EventId );
	CfgZYZHMap&					GetZYZHList();
	CfgZiYuanZhaoHui*			GetZiYuanZhaoHui( int32_t Index );
	CfgEquipExchange*			GetEquipExchange( int8_t Level );
	MemChrEquipBagVector&		GetShouChongLiBao();
	NewServerFavorable*			GetNewServerFavorable( int8_t Index );
	NewServerFavorableMap&		GetNewServerFavorableCfg();
	EverydayChongZhiMap&		GetEveryDayTable();
	CfgEverydayChongZhi*		GetEveryDayChongZhiCfg( int8_t Index );
	CTouZiCfg&					GetTouZhiCfg();
	KaiFuHuoDongCfg&			GetKaiFuHuoDongCfg();
	const CrossTowerCfg*		GetCrossTowerCfg( int32_t MapId ) const;
	void					InitCrossTowerCfgMap();
		void					fetchDungeonNpc();
		void					fetchMonsterAI();
		void					fetchMonsterAdjustTable();
		void					InitGroupIconTable();
		void					InitActiveSkillTable();
		void					InitPassiveSkillTable();
		void					InitTrigSkillTable();
		void					InitTalentTable();
	LittleHelperCfg*				GetLittleHelperCfg( int32_t nId );
	LittleHelperCfgMap&			GetLittleHelperCfgTable();
	LevelRefinCfg*				GetRefining( int32_t nLevel );
	LevelRefinCfgMap&			GetRefiningTable();
	void						InitBossKilledReward();
	const BossKilledReward*		GetBossKilledReward( int8_t nType ) const;
	const BossKilledRewardMap&	GetBossKilledRewardMap() const { return m_BossKilledRewardMap; }
	CfgHuoYueDu*				GetHuoYueDuCfg( int32_t Index );
	HuoYueDuTable&				GetHuoYueDuTable();
	CfgHuoYueDuReward*			GetHuoYueDuReward( int32_t Index );
	HuoYueDuRewardTable&		GetHuoYueDuRewardTable();
	CfgGuanWei*					GetGuanWeiCfg( int32_t index );
	CfgQiShi*					GetQiShiCfg( int32_t index );
	AddAttrList					GetQiShiAttr( int32_t index, int32_t Quality  );
	AddAttrList					GetAppendAttr( int32_t Id, int8_t Job );
	NewServerFavorable&			GetThreePetGift();
	FamilyTaskReward*			GetFamilyReward( int32_t Index );
	CfgXunZhang*				GetXunZhangCfg( int32_t EquipId );
	CfgBuyAcSocre*				GetBuyAcScoreCfg( int32_t Index );
	TotalChongZhiMap&			GetTotalChongZhiTable();
	CfgTotalChongZhi*			GetTotalChongZhiCfg( int8_t Index );
	int32_t						GetHuanHuaNeedRoleLevel( int32_t Points );
	WarVictoryHd*				GetWarVictoryHdCfg( int8_t Index );

	WuHunItem*			GetWuHunItem( int32_t nId );
	CreateWuHun*		GetCreateWuHun( int32_t nId );
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
	void fetchMap();							//��ȡ��ͼ��Ϣ��
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
	void fetchPlant();
	void fetchSkill();
	void fetchTask();
	void fetchTrailer();
	void fetchTrap();
	void fetchFormation();
	void fetchSignReward();
	void fetchYellowStone();

	ChangeJobIndexVector parseChangeJobEffect(int32_t id, const std::string &str);
	FamilyRegionVector parseFamilyRegionEffect(int32_t id, const std::string &str);
	AttrAddonVector parseEquipEffect(int32_t id, const std::string &str);
	AttrAddonVector parseEffect(int32_t id, const std::string &str);
	Int32Vector parseShejituEffect(int32_t id,const std::string &str);
	Int32Vector parseInt32VectorString(int32_t id,const std::string &str);
	MemChrEquipBagVector parseEquipItemString(int32_t id, const std::string &strItems);
	MemChrBagVector parseTaskItemString(int32_t id, const std::string &strItems);
	void parseItemStringWithJob(int32_t id,const std::string &strItems,MemChrBagVector &items,MemChrJobBagVector&jobItems);
	MemChrBagVector parseItemString(int32_t id, const std::string &strItems);
	MemChrBag parseDailyPkString(int32_t id, const std::string &strItems);
	MemChrJobBagVector parseTaskItemJobString(int32_t id, const std::string &strItems);
	GongGaoList parseGongGaoString(int32_t id, const std::string &strItems);
	void parseMonsterSkill(int32_t id, MonsterSkill (&vSkill)[MAX_MONSTER_SKILL], const std::string &strSkill);
	TaskRequest parseTaskCondition(int32_t id, int32_t condition, const std::string &strRequest);
	MemJobItemTable parseGambleEquip(int32_t id,const std::string &strItems);
	std::vector<Position> paresPosition( const std::string &strPos );
	Int32Vector parseAchievementString(int32_t id,const std::string &str);
    AcExchangeItemVector paresAcExchangeString(int32_t id,const std::string &str);
	AttrAddonVector parasePetAttrAddon( const std::string& addonAttr );
	CurrencyList	paraseCurrency( const std::string& str );
	AchievementRequest parseAchievementCondition(int32_t id, int32_t condition, const std::string &strRequest);
	void parasItemData( ItemData& data, const std::string& str );
	void parasItemData( MemChrBag& data, const std::string& str );
	void parasKaiFuHuoDongCondition( std::string& Effect, int32_t Conditions, int32_t& Param1, int32_t& Param2 );
	void fetchServerConfig(int32_t line = 0);
	void sendNewItems(const CfgItemTable &items);

	// ��ʼ��װ����
	void InitEquipTable();
	void InitEquipUpGradeTable();
	void InitEquipUpQualityTable();
	void InitEquipUpStarTable();
	void InitEquipAddAttrTable();
	void InitEquipGoalTable();
	void InitEquipSuitTable();
	void InitWuHunHoleTable();				// ��ʯ�׶�Ӧ���
	void InitWuHunMoHunTable();				// ǿ���ȼ���Ӧ���

	void InitItemGemTable();				// ��ʼ����ʯ��
	void InitItemCombiTable();				// ��ʼ���ϳɱ�
	void InitMagicBoxTable();
	void InitFlopDrawTable();				// 初始化翻牌抽奖配置表
	void InitEquipBackTable();				// 初始化装备回购配置表
	void InitLittleHelperCfg();				// 初始化小助手配置表
	void InitLevelRefiningTable();				// 初始化装备精炼配置表
	void InitShiZhuangTable();				// 初始化时装配置表
	void InitShiZhuangLevelTable();			// 初始化时装等级配置表
	void InitShiZhuLevelUp();				// 初始化时装升阶配置表				// ��ʼ��ħ�б�
	void InitBagSlotOpenTimeTable();		// ��ʼ����������ʱ���
	void InitPlayerInitPetTable();			// ��ʼ������Я�������
	void InitPetPackageTable();				// ��ʼ����������
	void InitPetTable();					// ��ʼ�����ޱ�
	void InitPetEggTable();					// ��ʼ�����޵���
	void InitPetAttrInitRateTable();		// ��ʼ���������԰ٷֱȶ�Ӧ��
	void InitPetIllusionTable();			// ��ʼ�����޻û���
	void InitPetKnightTable();				// ��ʼ��������ʿ��
	void InitSkillLevelUpTable();			// ��ʼ������������
	void InitTaskCycleStarTable();			// ��ʼ��ѭ�������
	void InitFamilyTable();					// ��ʼ�����ű�
	void InitFamilyPositionTable();			// ����ְλ��
	void InitFamilyPetRegistTable();		// ��ʼ������ǼǱ�
	void InitCharPetHatchPoolTable();		// ��ʼ��������������ñ�
	void InitPetLucyItemTable();			// ��ʼ����������ֵ�û����߱�
	void InitTeamBuffTable();				// ��ʼ�����Buff��
	void InitInsidePetTable();				// ��ʼ�����ޱ�
	void InitInsidePetExpItemTable();		// ��ʼ�����޿����ɵ��߱�
	void InitFamilyWarJoinRewardTable();	// ��ʼ������ս���뽱����
	void InitFamilyLightExpTable();			// ��ʼ������֮�⾭�齱����
	void InitSoulAttrTable();				// ��ʼ��������
	void InitHorseRacingRewardTable();		// ��ʼ��������Խ�����
	void InitHallOfFameRewardTable();		// ��������������

	void InitFriendExpTable();				//��ʼ�����Ѿ����

	void InitPkDropRateTable();				//��ʼ��pk�������
	void InitQiangHuaWorthTable();			//��ʼ��ǿ����ֵ��
	void InitSysMail();						//��ʼ��ϵͳ�ʼ�
	void InitBossInfo();					//��ʼ��boss��Ϣ
	void InitFaBaoTable();					//��ʼ��������Ϣ��
	void InitBuyFaBaoResTable();			//��ʼ�����򷨱���Դ��
	void InitDaTiHD();						//��ʼ������
	void InitShangChengTable();				//��ʼ���̳Ǳ�
	void InitPetGiftTable();				//��ʼ�����������
	void InitOnLimeReward();				//��ʼ������ʱ��
	void InitSevenLoginReward();			//��ʼ�������½����
	void InitLevelGift();					//��ʼ���ȼ����
	void InitWeekOnlineReward();			//��ʼ�����߽������
	void InitOffLineExpTable();				//��ʼ�����߾����
	void InitVipCardTable();				//��ʼ��vipcard
	void InitBossHomeTable();				//��ʼ��boss֮�ұ�
	void InitVipGuaJiMap();					//��ʼ��vip�һ���ͼ
	void InitFunctionOpenTable();			//��ʼ�����ܿ���
	void InitMoLingRuQinMap();				//��ʼ��ħ�����ֵ�ͼ
	void InitAutoPetGfit();					//��ʼ���Զ�ʹ�õĳ������
	void InitPlantEventTable();				//��ʼ���ɼ����¼���
	void InitZiYuanZhaoHuiTable();			//��ʼ����Դ�һر�
	void InitMoHuaHuanYiTable();			//��ʼ��ħ��ת�Ʊ�
	void InitShouChongLiBao();				//��ʼ���׳����
	void InitNewServerFavorable();			//�·��ػ����
	void InitEveryDayChongZhi();			//��ʼ��ÿ�ճ�ֵ
	void InitKaiFuHuoDongTable();			//��ʼ�����
	void InitHuoYueDuTable();				//��ʼ����Ծ�ȱ�
	void InitGuangWeiTable();				//��ʼ����λ��
	void InitAppendAttrTable();				//��ʼ���������Ա�
	void InitwuHunExpTable();				//��ʼ����꾭���
	void InitPetBuyTable();					//��ʼ���������û�
	void InitFamilyRewardTable();			//��ʼ�����Ž�����
	void InitAchievementTable();			//��ʼ���ɾͱ�
	void InitXunZhangTable();				//��ʼ��ѫ�±�
	void InitBuyAcSocreTable();				//��ʼ������ɾͻ���
	void InitTotalChongZhiTable();			//�����ۼƳ�ֵ
	void InitHuanHuaNeedRoleLevelTable();	//��ʼ���û��ȼ������
	void InitWarVictoryTable();				//��ʼ����սʤ��������
	void InitTianLingTable();
	void InitZhanHunTable();
	void InitSunAndMoonTable();
	void Init360RewardTable();
	void Init360RewardTypeTable();
	void InitActDropTable();
	void InitAdultGiftTable();
	void InitAttrBattleTable();
	void InitBFZLEnterCostTable();
	void InitBaoKuFuBen();
	void InitBeastShrineEnterCostTable();
	void InitBlacketMarketTable();
	void InitBlueDailyRewardTable();
	void InitBlueLevelRewardTable();
	void InitBlueRewardTable();
	void InitBossDistribution();
	void InitBossFirstKilledTable();
	void InitBuyGiftTable();
	void InitCachetCfg();
	void InitCampWarContKillTable();
	void InitCampWarRewardTable();
	void InitCarrierAttrTable();
	void InitCarrierTable();
	void InitChargeDungeon();
	void InitChristmasDuiHuanTable();
	void InitCityWarContRewardTable();
	void InitClbAimCfg();
	void InitCycleTowerTable();
	void InitDaZheQuanTable();
	void InitDamnationTable();
	DamnationCfg* GetDamnationCfg(int32_t Level);
	void InitDiligenceCfgMap();
	void InitDuiHuanLimitTable();
	void InitDungeonScoreTable();
	void InitDungeonSummon();
	void InitEquipBackTask();
	void InitEquipBlessTable();
	void InitEquipBoxTable();
	void InitEquipDecomposeTable();
	void InitEquipPosSuitTable();
	void InitEquipRongHeTable();
	void InitEquipUpPhase();
	void InitEquipUpPosTable();
	void InitExchangeTable();
	void InitFamilyDonateTable();
	void InitFamilyDungeonTable();
	void InitFamilyMedalTable();
	void InitFamilySkillTable();
	void InitFamilyWarReliveTable();
	void InitFlopTable();
	void InitFunctionOpenMailMap();
	void InitGameTable();
	void InitGemLevelUpTable();
	void InitGemOpenHoleTable();
	void InitGemSuitTable();
	void InitGoblinData();
	void InitGoblinTable();
	void InitGoldEggTable();
	void InitGongMinTable();
	void InitGroupMonster();
	void InitGuWuCfgMap();
	void InitGuardPrivilegeTable();
	void InitGuiGuDaoRenTable();
	void InitHoeTable();
	void InitJewelPavilionTable();
	void InitJueWeiTable();
	void InitKunLingTable();
	void InitLaDaShiHuiYuan();
	void InitLevelChatTimesTable();
	void InitLibraryTable();
	void InitLimitTimeTable();
	void InitLuckDropTable();
	void InitMYSJRewardTable();
	void InitMaintainCompensateTable();
	void InitMapRoadTable();
	void InitMiniClientMap();
	void InitMiniClientTable();
	void InitMoFuTable();
	void InitMobilePhoneGiftTable();
	void InitMonsterAddAttrTable();
	void InitMonsterRandTable();
	void InitMonthlyChouJiangTable();
	void InitMysteryGiftTable();
	void InitMysteryShopTable();
	void InitOutLinkFestivalTable();
	void InitPetAttrTable();
	void InitPetEquipTable();
	void InitPetUpStarTable();
	void InitPlatformDaTingMap();
	void InitPlatformReward();
	void InitPlatformVipMap();
	void InitQQGameRewardTable();
	void InitQQZoneRewardTable();
	void InitRefreshMonsterCfgListMap();
	void InitRongHeCfg();
	void InitScoreShopTable();
	void InitSevenTaskTable();
	void InitShenWeiTaskTable();
	void InitShenYaoPosSuitTable();
	void InitShenYaoPosTable();
	void InitShouHuRefining();
	void InitShunWangTable();
	void InitSouGouDaTing();
	void InitSouGouSkinTable();
	void InitSpeciaEquipCfgMap();
	void InitSpeciaSkillDistanceTable();
	void InitSpecialBossMapCfgMap();
	void InitSpecialMap();
	void InitSpecialMonster();
	void InitSpecialTreasureMapRandTable();
	void InitSpeed360Reward();
	void InitStrengthenTable();
	void InitSuperMemberTable();
	void InitSuperTeHuiTable();
	void InitSystemOpenReward();
	void InitTGPDailyRewardTable();
	void InitTGPLevelRewardTable();
	void InitTGPRewardTable();
	void InitTalentActiveTable();
	void InitTalentPageTable();
	void InitTaskCycleRewardTable();
	void InitTencentSevenDayLoginTable();
	void InitTestServerReward();
	void InitTitleTable();
	void InitTongTianChiRanTable();
	void InitTouZiTable();
	void InitTrailerTable();
	void InitTreasureMapTabale();
	void InitUltimateChallengeCfg();
	void InitVplanTable();
	void InitWeiXinTable();
	void InitWingCfgTable();
	void InitWingEquipPolish();
	void InitWishRewardTable();
	void InitWuHunCreateTable();
	void InitWuHunItemTable();
	void InitWuHunShopTable();
	void InitXianYaoTaskTable();
	void InitXinMoTable();
	void InitXingMaiSlotTable();
	void InitXingMaiTable();
	void InitXunLeiTable();
	void InitYYDaTing();
	void InitYYVip();
	void InitYellowDailyRewardTable();
	void InitYellowLevelRewardTable();
	void InitYellowRewardTable();
	void InitCampWarTable();
	void InitChouJiangTable();
	void InitCityWarTable();
	void InitCurrencyDuiHuanTable();
	void InitDropRecordTable();
	void InitEquipStrengthenTable();
	void InitGemAddTable();
	void InitMoFuSuitTable();
	void InitPeerlessWarTable();
	void InitShenYaoEquipTable();
	void InitWorldBossTable();

	void InitDrawTable();
	void InitShangRenCfgMap();
	void InitSelectItemCfgMap();
	void InitMingGeTable();
private:
	CfgMapEventList	m_emptyEvents;
	CfgActivityTable m_activities;
	CfgMapEventTable m_activityEvents;
	CfgActivityMonsterTable m_activityMonsters;
	CfgActivityNpcTable m_activityNpcs;
	CfgActivityPlantTable m_activityPlants;
	CfgActivityDropTable m_activityDrops;
	CfgActivityTrapTable m_activityTraps;

	CfgAnnoucementTimeTable m_annoucementTimes;
	CfgBuffTable m_buffs;

	CfgDungeonTable m_dungeons;
	CfgDungeonRewardTable m_dungeonReward;
	CfgDungeonDropGroupTable  m_dungeonDropGroup;
	CfgMapEventMap m_dungeonEvents;
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
	CfgPlantTable m_plants;
	CfgSkillMap m_skills;
	CfgTaskTable m_tasks;
	CfgTrailer m_tailers;
	CfgTrapTable m_traps;
	CfgLevelAttrTable m_levelAttrs;
	CfgGambleVector  m_gamble;
	CfgGambleVector  m_gamble_second;
	CfgGambleVector  m_gamble_three;
	CfgGambleEquipTable m_gambleEquip;
	CfgFamilyLevelTable  m_familyLevel;
	CfgYellowStoneTables m_yellowStone;

	CfgEquipTable			m_cfgEquip;					// װ����
	CfgItemGemTable			m_cfgItemGem;				// ��ʯ��
	CfgItemCombiTable		m_cfgItemCombi;				// �ϳɱ�
	CfgMagicBoxTable		m_cfgMagicBox;
	CfgFlopDrawTable		m_cfgFlopDraw;
	CfgShiZhuangTable		m_cfgShiZhuang;
	ShenWeiTaskCfgMap		m_cfgShenWeiTask;
	BackEquipTaskMap		m_cfgBackEquipTask;				// 翻牌抽奖配置				// ħ�з���
	CfgBagSlotOpenTimeTable	m_cfgBagSlotOpenTime;		// ��������ʱ���
	CfgPetTable				m_cfgPetTable;				// ���ޱ�
	CfgPetEggTable			m_cfgPetEggTable;			// ���޵���
	CfgPetAttrInitRateTable	m_cfgPetAttrInitRateTable;	// ���޳�ʼ�����԰ٷֱȶ�Ӧ��
	CfgPetIllusionTable		m_cfgPetIllusionTable;		// ���޻û���
	CfgPetKnightTable		m_cfgPetKnightTable;		// ������ʿ��
	CfgSkillLevelUpTable	m_cfgSkillLevelUpTable;		// ����������
	CfgTaskCycleTable		m_cfgTaskCycleTable;		// ѭ�������
	CfgFamilyTable			m_cfgFamilyTable;			// ���ű�
	CfgFamilyPetRegistTable	m_cfgFamilyPetRegistTable;	// ����ǼǱ�
	CfgCharPetTable			m_cfgCharPetTable;			// ��ҳ���ϵͳ���ñ�
	CfgTeamTable			m_cfgTeamTable;				// �����Ϣ��
	CfgInsidePetTable		m_cfgInsidePetTable;		// �������ñ�
	CfgFamilyWarJoinRewardTable	m_cfgFamilyWarJoinRewardTable;	// ����ս���뽱��
	CfgFamilyLightExpTable	m_cfgFamilyLightExpTable;	// ����֮�⾭�齱��
	CfgSoulAttrTable		m_cfgSoulAttrTable;			// �������Ա�
	CfgHorseRacingRewardTable	m_cfgHorseRacingRewardTable;	// ������Խ���
	CfgHallOfFameTable		m_cfgHallOfFameTable;		// �����ñ�

	cfgExActivitys m_cfgExActivitys;
	Answer::RwLock m_exActivityLock;

	int32_t m_avgLevel;
	int32_t m_createTime;
	int32_t m_debug;
	int32_t m_startServerTime;

	CfgFriendExpTable m_FriendExpTable;
	std::list<PkDropRate> m_PkDropRateTable;
	QiangHuaWorthMap	  m_QiangHuaWorthTable;
	CfgSysMailTable		  m_sysMail;
	BossInfoMap			  m_BossInfo;
	FaBaoTable			  m_FaBaoTable;
	FaBaoResMap			  m_FaBaoResMap;
	QuestionsVector		  m_QuestionsVct;
	GameShopMap			  m_GameShopMap;
	PetGiftMap			  m_PetGiftTable;
	ChouJiangConfig		  m_ChouJiangConfig;
	CQiFuTable			  m_QiFuTable;
	VipTable			  m_VipTable;
	CfgSignRewardTable    m_signReward;
	CfgOnlineRewardTable  m_OnLineReward;
	CfgSevenLoginRewradTable m_SevenLoginReward;
	CfgLevelGiftTable		 m_LevelGift;
	CfgWeekOnlineRewardTable m_WeekOnlineReward;
	CfgOffLineExpTable		 m_OffLineExpTable;
	VipCardCfgMap			 m_VipCardTable;
	BossHomeTable			 m_BossHomeTable;
	VipGuaJiMapTable		 m_VipGuaJiMap;
	FunctionOpenCfgMap		 m_FunctionOpenCfg;
	MoLingRuQinMap			 m_MoLingRuQinMap;
	CfgItemGiftTable		 m_PetGifts;
	PlantEventMap			 m_PlantEventMap;
	CfgZYZHMap				 m_ZiYuanZhaoHuiTable;	
	CfgEquipExchangeMap		 m_CfgEquipExchangeMap;
	MemChrEquipBagVector	 m_ShouChongLiBao;
	NewServerFavorableMap	 m_NewServerFavorable;
	NewServerFavorable		 m_ThreePetGift;
	EverydayChongZhiMap		 m_EveryDayChongZhiTable;
	CTouZiCfg				 m_TouZiCfg;
	KaiFuHuoDongCfg			 m_KaiFuHuoDongTable;
	HuoYueDuTable			 m_HuoYueDuTable;
	HuoYueDuRewardTable		 m_HuoYueDuRewardTable;
	GuanWeiMap				 m_GuanWeiCfg;
	QiShiMap				 m_QiShiCfg;
	AppendAttrTable			 m_AppendAttrTable;
	CfgFamilyTask			 m_FamilyTaskTable;
	FamilyTaskRewardMap		 m_FamilyTaskReward;
	AchievementTable		 m_AchievementTable;
	XunZhangMap				 m_XunZhangMap;
	BuyAcSocerMap			 m_BuyAcSocreMap;
	TotalChongZhiMap		 m_TotalChongZhiTable;
	HuanHuaNeedRoleLevelList m_HuanHuaNeedRoleLevelList;
	WarVictoryHdMap			 m_WarVictoryHdMap;
	GongMingCfgMap			 m_GongMingCfgMap;
	SpeciaEquipCfgMap		 m_SpeciaEquipCfgMap;
	TianLingCfgMap		m_TianLingCfgMap;
	ZhanHunCfgMap		m_ZhanHunCfgMap;
	SunAndMoonCfgMap	m_SunAndMoonCfgMap;	CfgBlacketMarketTable	m_BlacketMarketTable;
	CfgOutLinkFestivalTable	m_OutLinkFestivalTable;
	SevenTaskTable			m_SevenTaskTable;
	DaZheQuanMap			m_DaZheQuanMap;
	RongHeCfgMap			m_RongHeCfgMap;
	EquipRongHeMap			m_EquipRongHeMap;
	CachetCfgMap			m_CachetCfg;
	CfgCarrierTable			m_cfgCarrierTable;
	CfgWingTable			m_cfgWing;
	CfgWishRewardTable		m_cfgWishRewardTable;		// 护送配置表
	CfgDrawTable				m_cfgDrawTable;			// 抽卡配置表
	CfgExchangeTable			m_cfgExchangeTable;		// 兑换配置表
	CfgGuardPrivilegeMap	m_GuardPrivilegeMap;
	int32_t					m_nGuardPrivilegeStartTime;
	int32_t					m_nGuardPrivilegeEndTime;
	BossKilledRewardMap		m_BossKilledRewardMap;
	LittleHelperCfgMap		m_LittleHelperCfgMap;
	WuHunItemMap			m_WuHunItemMap;
	CreateWuHunMap			m_CreateWuHunMap;
	CfgMysteryGiftTable		m_cfgMysteryGiftTable;
	CfgMysteryShopTable			m_cfgMysteryShopTable;
public:
	// ZongHeYunYingHD
	const CfgZongHeYunYingHD*	GetZongHeYunYingHDCfg();
	
	const CfgGuardPrivilege*	GetGuardPrivilege( int8_t nIndex );
	const CfgGuardPrivilegeMap&	GetGuardPrivilegeMap();
	int32_t						GetGuardPrivilegeStartTime();
	int32_t						GetGuardPrivilegeEndTime();
const GongMingCfg*			GetGongMingCfg( int32_t nLevel );
	const GongMingCfgMap&		GetGongMingCfgMap();
	const SpeciaEquipCfg*		GetSpeciaEquipCfg( int32_t nId );
	const TianLingCfg*		GetTianLingCfg( int32_t nLevel );
	const TianLingCfgMap&		GetTianLingCfgMap();
	const ZhanHunCfg*		GetZhanHunCfg( int32_t nLevel );
	const ZhanHunCfgMap&		GetZhanHunCfgMap();
	const SunAndMoonCfg*		GetSunAndMoonCfg( int32_t nLevel );
	const SunAndMoonCfgMap&	GetSunAndMoonCfgMap();

	const CfgOutLinkFestivalTable*	GetOutLinkFestivalTable();
	const DaZheQuan*			GetDaZheQuanCfg( int32_t nIndex ) const;
	const CfgCachet*			GetCfgCachet( int32_t nLevel ) const;
	const RongHeCfg*			GetRongHeCfg( int32_t nIndex ) const;
	const EquipRongHe*		GetEquipRongHe( int32_t nItemId ) const;
	int32_t					GetCachetLevel( int64_t nHonor ) const;
	const SevenTaskTable*			GetSevenTaskTable();

	const CfgBlacketMarketTable*	GetBlacketMarketTable();
	const CfgWishRewardTable*	GetWishRewardTable() const { return &m_cfgWishRewardTable; }
	const CfgWingTable*		GetWingTable() const { return &m_cfgWing; }
	const CfgCarrierTable*		GetCarrierTable() const { return &m_cfgCarrierTable; }
	const CfgDrawTable*			GetDrawTable() const { return &m_cfgDrawTable; }
	const CfgExchangeTable*		GetExchangeTable() const { return &m_cfgExchangeTable; }
	const CfgMysteryGiftTable*	GetMysteryGiftTable() const { return &m_cfgMysteryGiftTable; }
	const CfgMysteryShopTable*		GetMysteryShopTable() const { return &m_cfgMysteryShopTable; }
	GuiGuDaoRenCfg* GetGuiGuDaoRenCfg( int32_t nNpcId );
	int32_t GetTongTianChiReward( int32_t nIndex );
	const CMingGeTable&		GetMingGeTable() const { return m_MingGeTable; }
	const TreasureMapTabale&	GetTreasureMapTabale() const { return m_TreasureMapTabale; }
	const SpecialTreasureMapRandCfgList&	GetSpecialTreasureMapRandCfgList() const { return m_SpecialTreasureMapRandCfgList; }
	XinMoTable*			GetXinMoTable() { return &m_XinMoTable; }
	const XinMoTable*	GetXinMoTable() const { return &m_XinMoTable; }
	KunLingTable*		GetKunLingTable() { return &m_KunLingTable; }
	const KunLingTable*	GetKunLingTable() const { return &m_KunLingTable; }
	// Equip accessors — return member map references
	const CfgMoFuSuitMap*	GetMoFuSuit() const { return &m_cfgMoFuSuit; }
	const CfgEquipStrengthen*	GetEquipStrengthen(int32_t nPos, int32_t nLevel) const;
	const CfgEquipUpPos*		GetEquipUpPos(int32_t nPos, int32_t nLevel) const;
	const CfgEquipStrengthenTable*	GetEquipStrengthenTable() const { return &m_cfgEquipStrengthen; }
	const CfgEquipUpPosTable*		GetEquipUpPosTable() const { return &m_cfgEquipUpPos; }
	const CfgShenYaoEquipTable*	GetShenYaoEquipTable() const { return &m_cfgShenYao; }
	const CfgGemLevelUpTable*		GetGemLevelUpTable() const { return &m_cfgGemLevelUp; }
	const CfgMoFuTable*			GetMoFuTable() const { return &m_cfgMoFu; }
	// Goblin accessors
	const GoblinCfg*		GetGoblinCfg(int32_t nType, int32_t nLevel) const;
	const VipEQuipPosSuit*	GetVipEQuipPosSuit(int32_t nSuitId) const;
	const VipEQuipPosSuitMap*	GetVipEQuipPosSuitMap() const { return &m_VipEQuipPosSuitList; }
	const PlatformDaTingMap*	GetPlatformDaTingMap() const { return &m_PlatformDaTingMap; }
	const PlatformDaTing*		GetGetPlatformDaTingCfg(const std::string& platform, int32_t nIndex) const;
	const PlatformVipMap*		GetPlatformVipMap() const { return &m_PlatformVipMap; }
	const PlatformVip*		GetGetPlatformVipCfg(const std::string& platform, int32_t nIndex) const;
	const PlatformRewardCfgMap*	GetPlatformRewardCfgMap() const { return &m_PlatformRewardCfgMap; }
	const PlatformRewardCfg*	GetGetPlatformRewardCfg(const std::string& platform, int32_t nIndex) const;
	const MiniClientCfgMap*	GetMiniClientMap() const { return &m_MiniClientMap; }
	const MiniClientCfg*		GetMiniClientCfg(const std::string& platform, int32_t nIndex) const;
	const TreasureHunterCfg*	GetTreasureHunterCfg(int32_t nId) const;
	const TreasureHunterCfgMap*	GetTreasureHunterCfgMap() const { return &m_TreasureHunterCfgMap; }
	const CfgBuyGiftTable*		GetBuyGiftTable() const { return &m_cfgBuyGiftTable; }
	const CfgBuyGift*			GetBuyGift(int32_t nIndex) const;

	const SuperTeHuiCfg*		GetSuperTeHuiCfg(int32_t nIndex) const;
	const SuperTeHuiCfgMap*		GetSuperTeHuiCfgMap() const { return &m_SuperTeHuiCfgMap; }
	const JewelPavilionCfg*		GetJewelPavilionCfg(int32_t nDay, int32_t nIndex) const;
	const JewelPavilionCfgMap*	GetJewelPavilionCfgMap() const { return &m_JewelPavilionCfgMap; }
	const ShangRenCfg*		GetShangRenCfg(int32_t nId) const;
	const ShangRenCfgMap*		GetShangRenCfgMap() const { return &m_ShangRenCfgMap; }
	const XingMaiCfg*			GetXingMaiCfg(int32_t nLevel) const;
	const CfgXingMaiSlot*		GetXingMaiSlot(int8_t nIndex) const;

	const Speed360Reward*		Get360Reward() const { return &m_Speed360Reward; }
	const Wan360Reward*		Get360RewardCfg(int32_t nIndex) const;
	int32_t			Get360RewardIcon(const std::string& platform) const;
	const CfgSouGouSkin*		GetSouGouSkin(const std::string& platform) const;
	const CfgWeiXingGift*		GetWeiXinGift(const std::string& platform) const;
	const CfgSuperMember*		GetSuperMember(const std::string& platform) const;
	const CfgMobilePhoneGift*	GetMobilePhoneGift(const std::string& platform) const;
	const CfgAdultGiftTable*	GetAdultGiftTable() const { return &m_cfgAdultGiftTable; }
	const ZeroBuyPetCfg*		GetZeroBuyPetCfg() const { return &m_ZeroBuyPetCfg; }

	const MonthlyChouJiangTable*	GetMonthlyChouJiangTable() const { return &m_MonthlyChouJiangTable; }
	const ClbAimCfgList&	GetClbAimCfgList() const { return m_ClbAimCfgList; }
	const CfgTitleTable*	GetTitleTable() const { return &m_cfgTitleTable; }
	// GetTencentTable/GetTouZiTable: need TencentTable.h/TouZi.h includes
	const void*		GetTencentTable() const { return NULL; }
	const void*		GetTouZiTable() const { return NULL; }

	// SkillTable/TalentTable accessors (2019)
	const CfgSkillTable*	GetSkillTable() const { return &m_cfgSkillTable; }
	CfgSkillTable*			GetSkillTable() { return &m_cfgSkillTable; }
	const CfgTalentTable*	GetTalentTable() const { return &m_cfgTalentTable; }
	CfgTalentTable*			GetTalentTable() { return &m_cfgTalentTable; }

	// WuHunShop accessors
	const CfgWuHunShop*		GetWuHunShopItem(int32_t nIndex) const;
	CfgWuHunShopList			GetWuHunShopItemList() const;

	// JueWei accessor
	class CfgJueWeiTable*	GetJueWeiTable();

	// UltimateChallenge accessor
	const UltimateChallengeCfg*	GetUltimateChallengeCfg(int32_t nLevel) const;

	// RefreshMonster accessor
	const RefreshMonsterCfgList&	GetRefreshMonsterCfgList() const;

	// Vplan accessor
	const CfgVplanMap*		GetVplanTable() const { return &m_CfgVplan; }

	// ShiZhuang accessor (already exists above, this resolves the int placeholder)
	// CfgShiZhuangTable already accessible via GetShiZhuangTable()

private:
	CMingGeTable				m_MingGeTable;
	TreasureMapTabale			m_TreasureMapTabale;
	SpecialTreasureMapRandCfgList		m_SpecialTreasureMapRandCfgList;
	// KunLingTable/XinMoTable — proper types via XinMoTable.h/KunLingTable.h
	XinMoTable				m_XinMoTable;
	KunLingTable			m_KunLingTable;
	PlatformDaTingMap			m_PlatformDaTingMap;
	PlatformVipMap				m_PlatformVipMap;
	PlatformRewardCfgMap		m_PlatformRewardCfgMap;
	MiniClientCfgMap			m_MiniClientMap;
	TreasureHunterCfgMap		m_TreasureHunterCfgMap;
	CfgBuyGiftTable			m_cfgBuyGiftTable;
	SuperTeHuiCfgMap		m_SuperTeHuiCfgMap;
	JewelPavilionCfgMap		m_JewelPavilionCfgMap;
	CrossTowerCfgMap		m_CrossTowerCfgMap;
	ShangRenCfgMap		m_ShangRenCfgMap;
	Wan360RewardMap			m_Wan360RewardMap;
	std::map<std::string, int32_t>	m_Wan360RewardTypeMap;
	CfgSouGouSkinMap		m_cfgSouGouSkin;
	Speed360Reward			m_Speed360Reward;
	CfgWeiXingGiftMap		m_WeiXinGiftTable;
	CfgSuperMemberMap		m_cfgSuperMember;
	CfgMobilePhoneGiftMap	m_CfgMobilePhoneGift;
	CfgAdultGiftTable		m_cfgAdultGiftTable;
	ZeroBuyPetCfg			m_ZeroBuyPetCfg;
	XingMaiCfgMap			m_XingMaiCfgTable;
	CfgXingMaiSlotMap		m_cfgXingMaiSlotTable;
	MonthlyChouJiangTable		m_MonthlyChouJiangTable;
	ClbAimCfgList		m_ClbAimCfgList;
	// ===== New table members =====
	CfgGemLevelUpTable		m_cfgGemLevelUp;
	CfgMoFuTable		m_cfgMoFu;
	CfgShenYaoEquipTable	m_cfgShenYao;
	CfgEquipStrengthenTable	m_cfgEquipStrengthen;
	CfgEquipUpPosTable		m_cfgEquipUpPos;
	CfgCurrencyDuiHuanMap	m_cfgCurrencyDuiHuan;
	CfgMoFuSuitMap		m_cfgMoFuSuit;
	CfgPetEquipTable		m_cfgPetEquip;
	CfgCityWarTable		m_cfgCityWar;
	CfgCampWarTable		m_cfgCampWar;
	CfgPeerlessWarTable		m_cfgPeerlessWar;
	CfgWorldBossTable		m_cfgWorldBoss;
	CfgGemAddTable		m_cfgGemAdd;
	BaoKuFuBenMap		m_BaoKuFuBen;
	BaoKuRandomMap		m_BaoKuRandomMap;
	TestServerRewardMap	m_TestServerRewardMap;
	std::map<int32_t, std::list<ActDropItem> >	m_ActDropItemListMap;


	CfgSkillTable				m_cfgSkillTable;
	int32_t m_cfgAttrBattle[50];
	CfgBFZLEnterCostTable		m_cfgBFZLEnterCostTable;
	// ===== Decompiled-port members (names matching CfgData.cpp usage) =====
	int32_t m_MapMonsterId;
	int32_t m_serverType;
	int32_t m_kaiFuTime;
	int32_t m_heFuTime;
	CfgTencentTable m_cfgTencentTable;
	CfgTitleTable m_cfgTitleTable;
	BossDistribution m_BossDistribution;
	CfgActivityTaskTable m_cfgActivityTaskTable;
	CfgBeastShrineTable m_CfgBeastShrineTable;
	std::map<int32_t, CfgBossFirstKilled> m_CfgBossFirstKilledMap;
	CfgDropRecordMap m_cfgDropRecordTable;
	std::map<std::pair<int32_t,int32_t>, CfgDungeonSummon> m_cfgDungeonSummon;
	CfgEquipBlessTable m_cfgEquipBlessTable;
	CfgEquipBoxTable m_cfgEquipBoxTalbe;
	cfgEquipUpPhaseTable m_cfgEquipUpPhaseTable;
	CfgFamilyDungeonTable m_cfgFamilyDungeonTable;
	cfgGoblinTableData m_cfgGoblinTableData;
	CfgGoldEggTable m_cfgGoldEggTable;
	std::map<int32_t, CfgGroupIcon> m_cfgGroupIcons;
	CfgJueWeiTable m_cfgJueWeiTable;
	std::map<int32_t, int32_t> m_cfgLevelChatTable;
	CfgLimitTimeTable m_cfgLimitTimeTable;
	CfgMaintainCompensateTable m_cfgMaintainCompensateTable;
	CfgMapRoadTable m_cfgMapRoadTable;
	CfgMonsterRandTable m_cfgMonsterRandTable;
	CfgMYSJRewardTable m_cfgMYSJRewardTable;
	CfgShiZhuangTable m_cfgShiZhuangTable_member; // note: m_cfgShiZhuang already exists above
	cfgSpecialMonsterTable m_cfgSpecialMonsterTable;
	CfgTalentTable m_cfgTalentTable;
	CfgTouZiTable m_cfgTouZiTable;
	CfgTrailerTable m_cfgTrailerTable;
	CfgVplanMap m_CfgVplan;
	CfgYYGameAppMap m_CfgYYGameAppMap;
	CfgYYSuperBuffMap m_CfgYYSuperBuffList;
	CfgYYSuperBuffMap m_Cfg37wanSuperBuffList; // same type
	CfgYYVipMap m_CfgYYVipMap;
	std::map<int32_t, ChargeDungeonCfg> m_ChargeDungeonCfgMap;
	ChristmasDuiHuanMap m_ChristmasDuiHuanMap;
	CMingGeTable m_CMingGeTable; // duplicate of m_MingGeTable for decompiled compat
	ContributionCfgMap m_ContributionCfgMap;
	CVipClubLuckyDropMap m_CVipClubLuckyDropMap;
	CycleTowerTable m_CycleTowerTable;
	DamnationCfgMap m_DamnationCfgTable;
	DiligenceCfgMap m_DiligenceCfgMap;
	DuiHuanLimitMap m_DuiHuanLimit;
	std::map<int32_t, CfgDungeonNpc> m_dungeonNpcs;
	EnergyCfg m_EnergyCfg;
	EquipBackTaskCfgMap m_EquipBackTaskCfgMap;
	std::map<int32_t, std::map<int32_t, std::list<Param2>>> m_EquipBackTaskRate;
	CfgEquipBlessMap m_EquipBlessMap;
	CfgEquipBoxTable m_EquipBoxTable;
	EquipRongHeCfgMap m_EquipRongHeCfgMap;
	EquipStrengthenCfgMap m_EquipStrengthenCfgMap;
	FunctionOpenMailMap m_FunctionOpenMailMap;
	CfgGoldEggTable m_GoldEggTable;
	CfgMiniClientMap m_GetMiniClientMap;
	std::map<std::pair<int32_t, int32_t>, GoblinCfg> m_GoblinCfgMap;
	std::map<int32_t, std::list<AddAttribute>> m_GoblinSuitMap;
	GroupMonsterVector m_GroupMonsterMap;
	GuiGuDaoRenCfgMap m_GuiGuDaoRenCfgMap;
	GuWuCfgMap m_GuWuCfgMap;
	HoeCfgMap m_HoeCfgMap;
	CfgLimitTimeTable m_LimitTimeTable;
	LuckDropTable m_LuckDropTable;
	CVipClubLuckyDropMap m_CVipClubLuckyDropMap;
	LuDaShiVipMap m_LuDaShiVipMap;
	CfgMingGeMap m_MingGeCfgMap;
	std::map<int32_t, CfgMapPlant> m_mMapPlants;
	std::map<std::pair<int,int>, CfgMonsterAdjust> m_mMonsterAdjust;
	std::map<int32_t, CfgMonsterAI> m_mMonsterAI;
	std::map<int32_t, CfgMonsterAddAttr> m_MonstAddAttrMap;
	std::map<int32_t, QuestionsVector> m_mQuestions;
	CfgDungeonTable m_mUpTowerDungeon;
	RongHeCfgMap m_RongHeCfgMap;
	std::map<int32_t, RefreshMonsterCfgList> m_RefreshMonsterCfgListMap;
	ShiQuCfgMap m_ShiQuCfgMap;
	SpecialBossMapCfgMap m_SpecialBossMapCfgMap;
	CfgTalentMap m_TalentCfgMap;
	CfgTalentActiveMap m_TalentActiveCfgMap;
	CfgTalentPageMap m_TalentPageCfgMap;
	TianLingCfgMap m_TianLingCfgTable;
	CfgTitleMap m_TitleCfgMap;
	CfgWingEquipMap m_WingEquipCfgMap;
	CfgWingPolishMap m_WingPolishCfgMap;
	CfgXingMaiMap m_XingMaiCfgMap;
	CfgXingMaiSlotMap m_XingMaiSlotCfgMap;
	std::map<int32_t, int32_t> m_TongTianChiRankReward;
	UltimateChallengeCfgMap m_UltimateChallengeCfgMap;
	VipEquipPosLevelUpMap m_VipEquipPosLevelUpMap;
	VipEQuipPosSuitMap m_VipEQuipPosSuitList;
	WingEquipPolishMap m_WingEquipPolishCfgMap;
	std::map<int32_t, AddAttrList> m_WingEquipPolishSuitMap;
	std::map<int32_t, AddAttrList> m_WingEquipRefiningSuitMap;
	WinRefiningCfgMap m_WinRefiningCfgMap;
	std::list<XiangYaoTaskCfg> m_XiangYaoTaskCfgList;
	XunLeiCfgMap m_XunLeiCfgMap;
	std::map<int32_t, CfgWuHunShop> m_CfgWuHunShopItemMap;
	CfgMiniClientMap m_CfgMiniClient;

	// ===== Additional 2019 member variables =====
	CfgXinMoMap m_XinMoCfgMap;
	CfgScoreShopMap m_ScoreShopTable;
	CfgSpeciaSkillDistanceMap m_SpeciaSkillDistanceMap;
	CfgLevelRefiningMap m_LevelRefiningMap;
	CfgSystemOpenRewardMap m_SystemOpenRewardMap;
	CfgSpecialMapTable m_SpecialMapTable;
	CfgShenWeiTaskTable m_ShenWeiTaskTable;
	CfgSuperTeHuiTable m_SuperTeHuiTable;
	CfgShouHuRefiningLevelMap m_ShouHuRefiningLevelMap;
	CfgShouHuRefiningSuitMap m_ShouHuRefiningSuitMap;
	CfgShiZhuangSuitTable m_ShiZhuangSuitTable;
	CfgMonthlyChouJiangRechargeMap m_MonthlyChouJiangRechargeMap;
	CfgSouGouDaTingTable m_SouGouDaTingTable;
	CfgPlatformRewardMap m_PlatformRewardMap;
	CfgSelectItemCfgMap m_SelectItemCfgMap;
	CfgShiZhuLevelUpMap m_ShiZhuLevelUpMap;
	CfgNationalDayTaskTable m_NationalDayTaskTable;
	CfgNationalDayPassportTable m_NationalDayPassportTable;
};

//////////////////////////////////////////////////////////////////////////
// Missing config table classes
//////////////////////////////////////////////////////////////////////////

class CfgGuardPrivilege
{
public:
	int8_t nIndex;
	int32_t nGuardId;
	int32_t nCost;
	int32_t nDiscount;

	CfgGuardPrivilege() : nIndex(0), nGuardId(0), nCost(0), nDiscount(0) {}
	CfgGuardPrivilege& operator=(const CfgGuardPrivilege& rhs) {
		nIndex = rhs.nIndex; nGuardId = rhs.nGuardId;
		nCost = rhs.nCost; nDiscount = rhs.nDiscount;
		return *this;
	}
};

class CfgGuardPrivilegeTable
{
public:
	CfgGuardPrivilegeTable() : m_nStartTime(0), m_nEndTime(0) {}
	~CfgGuardPrivilegeTable() {}

	bool Add(const CfgGuardPrivilege* stu)
	{
		if (stu) m_mGuardPrivilege[stu->nIndex] = *stu;
		return true;
	}
	void SetTime(int32_t nStartTime, int32_t nEndTime)
	{
		m_nStartTime = nStartTime;
		m_nEndTime = nEndTime;
	}

	std::map<int8_t, CfgGuardPrivilege> m_mGuardPrivilege;
	int32_t m_nStartTime;
	int32_t m_nEndTime;
};

class CfgSearchBack
{
public:
	int32_t nId;
	int32_t nMinLevel;
	int32_t nMaxLevel;
	int32_t nItemId;
	int32_t nCount;
	int8_t nIndex;

	CfgSearchBack() : nId(0), nMinLevel(0), nMaxLevel(0), nItemId(0), nCount(0), nIndex(0) {}
	CfgSearchBack& operator=(const CfgSearchBack& rhs) {
		nId = rhs.nId; nMinLevel = rhs.nMinLevel; nMaxLevel = rhs.nMaxLevel;
		nItemId = rhs.nItemId; nCount = rhs.nCount; nIndex = rhs.nIndex;
		return *this;
	}
};
typedef std::list<CfgSearchBack> CfgSearchBackList;

class CfgSearchBackTable
{
public:
	CfgSearchBackTable() {}
	~CfgSearchBackTable() {}

	void AddSearchBack(const CfgSearchBack* stu)
	{
		if (stu) m_mSearchBack[stu->nId] = *stu;
	}
	void GetSearchBackList(int32_t nLevel, CfgSearchBackList* outList) const
	{
		for (auto it = m_mSearchBack.begin(); it != m_mSearchBack.end(); ++it)
		{
			if (it->second.nMinLevel <= nLevel && it->second.nMaxLevel >= nLevel)
				outList->push_back(it->second);
		}
	}

	std::map<int32_t, CfgSearchBack> m_mSearchBack;
};

class CfgShouChong
{
public:
	int8_t nIndex;
	int32_t nItemId;
	int32_t nCount;

	CfgShouChong() : nIndex(0), nItemId(0), nCount(0) {}
	CfgShouChong& operator=(const CfgShouChong& rhs) {
		nIndex = rhs.nIndex; nItemId = rhs.nItemId; nCount = rhs.nCount;
		return *this;
	}
};

class CfgShouChongTable
{
public:
	CfgShouChongTable() {}
	~CfgShouChongTable() {}

	bool Add(const CfgShouChong* stu)
	{
		if (stu) m_mShouChong[stu->nIndex] = *stu;
		return true;
	}

	std::map<int8_t, CfgShouChong> m_mShouChong;
};

class CfgWeiXingGift
{
public:
	std::string strPlatform;
	int32_t nItemId;
	int32_t nCount;

	CfgWeiXingGift() : nItemId(0), nCount(0) {}
	CfgWeiXingGift& operator=(const CfgWeiXingGift& rhs) {
		strPlatform = rhs.strPlatform; nItemId = rhs.nItemId; nCount = rhs.nCount;
		return *this;
	}
};

class CfgWeiXinTable
{
public:
	CfgWeiXinTable() {}
	~CfgWeiXinTable() {}

	void Add(const CfgWeiXingGift* stu)
	{
		if (stu) m_mWeiXing[stu->strPlatform] = *stu;
	}

	std::map<std::string, CfgWeiXingGift> m_mWeiXing;
};

// ===== CfgFamilyWarJoinReward =====
struct CfgFamilyWarJoinReward
{
	int32_t level;
	int32_t addExp;
};

// ===== CfgFamilyWarTable =====
class CfgFamilyWarTable
{
public:
	CfgFamilyWarTable() {}
	~CfgFamilyWarTable() {}

	void AddJoinReward(int32_t nLevel, int32_t nExp);
	int32_t GetJoinReward(int32_t nLevel) const;

	std::list<CfgFamilyWarJoinReward> m_reward;

	// Relive config (used by CfgData::InitFamilyWarReliveTable)
	struct CfgFamilyWarRelive
	{
		int32_t nId;
		int32_t nLevel;
		int32_t nHpPecent;
	};
	std::vector<CfgFamilyWarRelive> m_relive;
};

// ===== DamnationCfg extended fields =====
// Note: Curse class uses CostMoney, CostItems, AttrList, HpPecent, Probability, GongGaoId
// These fields need to be added to DamnationCfg if not already present.

// ===== 2019 Version Config Tables =====

// RefreshMonster - used by GuiGuDaoRen
struct RefreshMonster
{
	RefreshMonster() : nCount(0), BossId(0), AliveTime(0), GongGaoId(0) {}
	int32_t nCount;
	int32_t BossId;
	int32_t AliveTime;
	int32_t GongGaoId;
};
typedef std::list<RefreshMonster> RefreshMonsterList;

// GuiGuDaoRenCfg - 鬼谷道人配置
struct GuiGuDaoRenCfg
{
	GuiGuDaoRenCfg() : nNpcId(0), nMaxCount(0) {}
	int32_t nNpcId;
	int32_t nMaxCount;
	RefreshMonsterList lRefreshMonster;
	std::vector<ItemData> vItemData;
	std::vector<MemChrBag> vItem;
	Int32Vector vMapId;
};
typedef std::map<int32_t, GuiGuDaoRenCfg> GuiGuDaoRenCfgMap;

// EquipBack - 装备回购配置
struct EquipBack
{
	EquipBack() : nId(0), nType(0), nRecovType(0), nRecovValues(0)
		, nBuyBackType(0), nBuyBackValue(0), nOpenDay(0), nLimitNum(0), nDisplayDay(0) {}
	int32_t nId;
	int32_t nType;
	std::list<int32_t> nEquipList;
	int32_t nRecovType;
	int32_t nRecovValues;
	int32_t nBuyBackType;
	int32_t nBuyBackValue;
	int32_t nOpenDay;
	int32_t nLimitNum;
	int32_t nDisplayDay;
};

// EquipBackTaskCfg - 装备回购任务配置
struct EquipBackTaskCfg
{
	EquipBackTaskCfg() : nId(0), nType(0), nNeedCount(0), nRewardType(0), nRewardCount(0) {}
	int32_t nId;
	int32_t nType;
	int32_t nNeedCount;
	int32_t nRewardType;
	int32_t nRewardCount;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, EquipBackTaskCfg> EquipBackTaskCfgMap;

// EquipStrengthenCfg - 装备强化配置
struct EquipStrengthenCfg
{
	EquipStrengthenCfg() : nLevel(0), nMoney(0), nRate(0) {}
	int32_t nLevel;
	int32_t nMoney;
	int32_t nRate;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, EquipStrengthenCfg> EquipStrengthenCfgMap;

// CfgEquipBox - 装备箱配置
struct CfgEquipBox
{
	CfgEquipBox() : nId(0), nBind(0) { memset(vEquipId, 0, sizeof(vEquipId)); }
	int32_t nId;
	int32_t vEquipId[5]; // per job
	int8_t  nBind;
	std::list<Param2> lstStar;
};
typedef std::map<int32_t, CfgEquipBox> CfgEquipBoxMap;

class CfgEquipBoxTable
{
public:
	CfgEquipBoxTable() {}
	~CfgEquipBoxTable() {}

	const CfgEquipBox* RandEquip(int32_t nBoxId) const
	{
		auto it = m_map.find(nBoxId);
		return it != m_map.end() ? &it->second : nullptr;
	}

	CfgEquipBoxMap m_map;
};

// CfgGoldEgg - 金蛋配置
struct CfgGoldEggItem
{
	CfgGoldEggItem() : nItemId(0), nItemClass(0), nItemCount(0), nBind(0)
		, nProbability(0), nLimitTime(0), nBroadcast(0), nJob(0), nMinLevel(0), nMaxLevel(0) {}
	int32_t nItemId;
	int32_t nItemClass;
	int32_t nItemCount;
	int8_t  nBind;
	int32_t nProbability;
	int32_t nLimitTime;
	int32_t nBroadcast;
	int8_t  nJob;
	int32_t nMinLevel;
	int32_t nMaxLevel;
};
typedef std::list<CfgGoldEggItem> CfgGoldEggItemList;

struct CfgGoldEgg
{
	CfgGoldEgg() : nId(0), nGroupId(0), nCostGold(0), nOpenTimes(0)
		, nStartDate(0), nEndDate(0) {}
	int32_t nId;
	int32_t nGroupId;
	int32_t nCostGold;
	int32_t nOpenTimes;
	int32_t nStartDate;
	int32_t nEndDate;
	CfgGoldEggItemList lstItem;
};
typedef std::map<int32_t, CfgGoldEgg> CfgGoldEggMap;

class CfgGoldEggTable
{
public:
	CfgGoldEggTable() {}
	~CfgGoldEggTable() {}

	const CfgGoldEgg* GetGoldEgg(int32_t nId) const
	{
		auto it = m_map.find(nId);
		return it != m_map.end() ? &it->second : nullptr;
	}

	CfgGoldEggMap m_map;
};

// CfgTalent - 天赋配置 (2019完整版)
struct CfgTalent
{
	CfgTalent()
		: id(0), nPageId(0), Level(0), Point(0), maxLevel(0),
		  Playerlevel(0), skillid(0), nCostType(0), nCostValue(0), GongGaoId(0) {}
	int32_t id;
	int32_t nPageId;
	int32_t Level;
	int32_t Point;				// 天赋点消耗
	int32_t maxLevel;
	int32_t Playerlevel;		// 玩家等级需求
	int32_t skillid;			// 关联技能ID
	int32_t nCostType;
	int32_t nCostValue;
	int32_t GongGaoId;			// 公告ID
	AddAttrList lAttrList;
	Int32Vector vSkill;			// 关联技能列表
};
typedef std::map<int32_t, CfgTalent> CfgTalentMap;

// CfgTalentPage - 天赋页配置 (2019版)
struct CfgTalentPage
{
	CfgTalentPage() : job(0), nId(0), nCostType(0), nCostValue(0) {}
	int8_t job;					// 职业作为key
	int32_t nId;
	int32_t nCostType;
	int32_t nCostValue;
	std::list<int32_t> talents;	// 天赋ID列表
};
typedef std::map<int8_t, CfgTalentPage> CfgTalentPageMap;

// CfgTalentActive - 天赋激活配置
struct CfgTalentActive
{
	CfgTalentActive() : nId(0), nType(0), nParam(0) {}
	int32_t nId;
	int32_t nType;
	int32_t nParam;
};
typedef std::map<int32_t, CfgTalentActive> CfgTalentActiveMap;

// SkillLevelInfo - 技能等级信息（DB持久化）
struct SkillLevelInfo
{
	SkillLevelInfo() : Level(0), Point(0) {}
	int32_t Level;
	int32_t Point;
};

// AddonSkill - 附加技能（带时效）
struct AddonSkill
{
	AddonSkill() : nEndTick(0), nTrigTimes(0), nSkillFlag(0), nSkillId(0) {}
	int64_t nEndTick;
	int32_t nTrigTimes;
	int32_t nSkillFlag;
	int32_t nSkillId;
};

// SummonSkill - 召唤技能（带延迟）
struct SummonSkill
{
	SummonSkill() : nSkillId(0), nStartTick(0) {}
	int32_t nSkillId;
	int64_t nStartTick;
	Position targetPos;
};

// MemTalent - 内存中的天赋信息
struct MemTalent
{
	MemTalent() : nId(0) { memset(vAddon, 0, sizeof(vAddon)); }
	int32_t nId;
	int32_t vAddon[9];
};

// CfgTrigSkill - 触发技能配置
struct CfgTrigSkill
{
	CfgTrigSkill()
		: id(0), trigType(0), trigRate(0), groupid(0), cdTime(0),
		  targetType(0), IsPvp(0), trigBuff(0) {}
	int32_t id;
	int32_t trigType;			// 触发类型: 1=攻击触发, 2=使用技能, 4=血量百分比, 5=阶段伤害, 6=召唤, 7=击杀
	int32_t trigRate;			// 触发概率(千分比或百分比)
	std::string trigParam;		// 触发参数(如血量阈值)
	int32_t groupid;
	int32_t cdTime;
	int32_t targetType;			// 1=自身, 0=目标
	int32_t IsPvp;				// >0 仅PVP
	int32_t trigBuff;			// 触发buff
	Int32Vector vRespondGroups;	// 响应技能组

	bool isRespond(int32_t nSkillGroup) const
	{
		if (vRespondGroups.empty()) return true;
		for (auto gid : vRespondGroups)
		{
			if (gid == nSkillGroup) return true;
		}
		return false;
	}
};
typedef std::map<int32_t, CfgTrigSkill> CfgTrigSkillMap;

// CfgTalentTable - 天赋配置表（2019版class）
class CfgTalentTable
{
public:
	void AddTalent(const CfgTalent& stu)
	{
		auto key = std::make_pair(stu.id, stu.Level);
		m_mTalent[key] = stu;
		auto it = m_mTalentMax.find(stu.id);
		if (it == m_mTalentMax.end() || stu.Level > it->second)
			m_mTalentMax[stu.id] = stu.Level;
	}

	void AddTalentPage(const CfgTalentPage& stu)
	{
		m_mTalentPage[stu.job] = stu;
	}

	const CfgTalent* GetTalent(int32_t nId, int32_t nLevel) const
	{
		auto key = std::make_pair(nId, nLevel);
		auto it = m_mTalent.find(key);
		return it != m_mTalent.end() ? &it->second : nullptr;
	}

	const CfgTalentPage* GetTalentPage(Job_t job) const
	{
		auto it = m_mTalentPage.find(job);
		return it != m_mTalentPage.end() ? &it->second : nullptr;
	}

	int32_t GetTalentMaxLevel(int32_t nId) const
	{
		auto it = m_mTalentMax.find(nId);
		return it != m_mTalentMax.end() ? it->second : 0;
	}

	bool IsTalentSkill(Job_t job, SkillId_t id) const
	{
		auto it = m_mTalentPage.find(job);
		if (it == m_mTalentPage.end()) return false;
		for (auto sid : it->second.talents)
		{
			if (sid == id) return true;
		}
		return false;
	}

	std::map<std::pair<int32_t,int32_t>, CfgTalent>	m_mTalent;
	std::map<int32_t, int32_t>	m_mTalentMax;
	CfgTalentPageMap	m_mTalentPage;
};

// Forward declaration
struct CfgFamilySkill;

// CfgSkillTable - 技能配置表（2019版class）
class CfgSkillTable
{
public:
	void AddActiveSkill(const CfgActiveSkill& skill)
	{
		m_mSkillType[skill.id] = 1;
		m_mActiveSkills[skill.id] = skill;
	}

	void AddPassiveSkill(const CfgPassiveSkill& skill)
	{
		m_mSkillType[skill.id] = 2;
		m_mPassiveSkills[skill.id] = skill;
	}

	void AddTrigSkill(const CfgTrigSkill& skill)
	{
		m_mSkillType[skill.id] = 3;
		m_mTrigSkills[skill.id] = skill;
	}

	void AddFamilySkill(int32_t nId, int32_t nLevel, const CfgFamilySkill& skill)
	{
		// CfgFamilySkill defined elsewhere - placeholder
	}

	void AddTalentActive(const CfgTalentActive& stu)
	{
		m_mTalentActive[stu.nId] = stu;
	}

	int8_t GetSkillType(int32_t id) const
	{
		auto it = m_mSkillType.find(id);
		return it != m_mSkillType.end() ? it->second : 0;
	}

	const CfgActiveSkill* GetActiveSkill(int32_t nId) const
	{
		auto it = m_mActiveSkills.find(nId);
		return it != m_mActiveSkills.end() ? &it->second : nullptr;
	}

	const CfgPassiveSkill* GetPassiveSkill(int32_t nId) const
	{
		auto it = m_mPassiveSkills.find(nId);
		return it != m_mPassiveSkills.end() ? &it->second : nullptr;
	}

	const CfgTrigSkill* GetTrigSkill(int32_t nId) const
	{
		auto it = m_mTrigSkills.find(nId);
		return it != m_mTrigSkills.end() ? &it->second : nullptr;
	}

	std::map<int32_t, int8_t>	m_mSkillType;
	CfgActiveSkillMap	m_mActiveSkills;
	std::map<int32_t, CfgPassiveSkill>	m_mPassiveSkills;
	CfgTrigSkillMap	m_mTrigSkills;
	std::map<std::pair<int32_t,int32_t>, CfgFamilySkill>	m_mFamilySkills;
	std::map<int32_t, CfgTalentActive>	m_mTalentActive;
};

// CfgTitle - 称号配置
struct CfgTitle
{
	CfgTitle() : nId(0), nType(0), nTimeType(0), nTime(0), nGongGaoId(0) {}
	int32_t nId;
	int32_t nType;
	int32_t nTimeType;
	int32_t nTime;
	AddAttrList lAttrList;
	int32_t nGongGaoId;
};
typedef std::map<int32_t, CfgTitle> CfgTitleMap;

// CfgWingEquip - 翅膀装备配置
struct CfgWingEquip
{
	CfgWingEquip() : nId(0), nLevel(0), nQuality(0), nCostMoney(0), nCostItem(0), nCostCount(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nQuality;
	int32_t nCostMoney;
	int32_t nCostItem;
	int32_t nCostCount;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, CfgWingEquip> CfgWingEquipMap;

// CfgWingPolish - 翅膀打磨配置
struct CfgWingPolish
{
	CfgWingPolish() : nId(0), nCostMoney(0), nCostItem(0), nCostCount(0) {}
	int32_t nId;
	int32_t nCostMoney;
	int32_t nCostItem;
	int32_t nCostCount;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, CfgWingPolish> CfgWingPolishMap;

// CfgEquipBless - 装备祝福配置
struct CfgEquipBless
{
	CfgEquipBless() : nId(0), nLevel(0), nRate(0), nCostMoney(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nRate;
	int32_t nCostMoney;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, CfgEquipBless> CfgEquipBlessMap;

// CfgMingGe - 命格配置
struct CfgMingGe
{
	CfgMingGe() : nId(0), nLevel(0), nType(0), nCostType(0), nCostValue(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nType;
	int32_t nCostType;
	int32_t nCostValue;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, CfgMingGe> CfgMingGeMap;

// RongHeCfg - 融合配置
struct RongHeCfg
{
	RongHeCfg() : nId(0), nType(0), nCostType(0), nCostValue(0), nRate(0) {}
	int32_t nId;
	int32_t nType;
	int32_t nCostType;
	int32_t nCostValue;
	int32_t nRate;
	MemChrBagVector vItem;
};
typedef std::map<int32_t, RongHeCfg> RongHeCfgMap;

// EquipRongHeCfg - 装备融合配置
struct EquipRongHeCfg
{
	EquipRongHeCfg() : nId(0), nDstEquipId(0), nCostMoney(0), nRate(0) {}
	int32_t nId;
	int32_t nDstEquipId;
	int32_t nCostMoney;
	int32_t nRate;
	Int32Vector vSrcEquip;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, EquipRongHeCfg> EquipRongHeCfgMap;

// CfgLimitTimeTable - 限时配置
struct CfgLimitTime
{
	CfgLimitTime() : nId(0), nTime(0) {}
	int32_t nId;
	int32_t nTime;
};
typedef std::map<int32_t, CfgLimitTime> CfgLimitTimeMap;

class CfgLimitTimeTable
{
public:
	CfgLimitTimeTable() {}
	~CfgLimitTimeTable() {}

	int32_t GetLimitTime(int32_t nId) const
	{
		auto it = m_map.find(nId);
		return it != m_map.end() ? it->second.nTime : 0;
	}

	CfgLimitTimeMap m_map;
};

// CfgDamnation - 诅咒配置
struct CfgDamnation
{
	CfgDamnation() : nId(0), nLevel(0), nCostMoney(0), nHpPecent(0), nProbability(0), nGongGaoId(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nCostMoney;
	Int32Vector CostItems;
	AddAttrList AttrList;
	int32_t nHpPecent;
	int32_t nProbability;
	int32_t nGongGaoId;
};
typedef std::map<int32_t, CfgDamnation> CfgDamnationMap;

// CfgXingMai - 星脉配置
struct CfgXingMai
{
	CfgXingMai() : nId(0), nLevel(0), nCostType(0), nCostValue(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nCostType;
	int32_t nCostValue;
	AddAttrList lAttrList;
};
typedef std::map<int32_t, CfgXingMai> CfgXingMaiMap;

// CfgXingMaiSlot - 星脉槽配置
struct CfgXingMaiSlot
{
	CfgXingMaiSlot() : nId(0), nSlotIndex(0), nNeedLevel(0), nCostType(0), nCostValue(0) {}
	int32_t nId;
	int32_t nSlotIndex;
	int32_t nNeedLevel;
	int32_t nCostType;
	int32_t nCostValue;
};
typedef std::map<int32_t, CfgXingMaiSlot> CfgXingMaiSlotMap;

// CfgItemGift - 物品礼包配置
struct CfgItemGift
{
	CfgItemGift() : item(0), type(0), count(0), bind(0), time(0), job(0) {}
	int32_t item;
	int32_t type;
	int32_t count;
	int32_t bind;
	int32_t time;
	int32_t job;
};
typedef std::vector<CfgItemGift> CfgItemGiftVector;

// CfgItemGiftRandom - 随机礼包配置
struct CfgItemGiftRandom
{
	CfgItemGiftRandom() : item(0), type(0), count(0), bind(0), time(0), job(0)
		, rate(0), MinLevel(0), MaxLevel(0), static_probability(0), sum_probability(0) {}
	int32_t item;
	int32_t type;
	int32_t count;
	int32_t bind;
	int32_t time;
	int8_t  job;
	int32_t rate;
	int32_t MinLevel;
	int32_t MaxLevel;
	int32_t static_probability;
	int32_t sum_probability;
};
typedef std::vector<CfgItemGiftRandom> CfgItemGiftRandomVector;
typedef std::map<int32_t, CfgItemGiftRandomVector*> CfgItemGiftRandomTable;

// ===== Additional 2019 Config Structs =====

// CfgXinMo (XinMo.txt)
struct CfgXinMo
{
	CfgXinMo() : nId(0), nLevel(0), nHp(0), nAttack(0), nDefence(0),
		nHit(0), nDodge(0), nCrit(0), nTough(0), nExp(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nHp;
	int32_t nAttack;
	int32_t nDefence;
	int32_t nHit;
	int32_t nDodge;
	int32_t nCrit;
	int32_t nTough;
	int32_t nExp;
};
typedef std::map<int32_t, CfgXinMo> CfgXinMoMap;

// SpecialTreasureMapRandCfg
struct SpecialTreasureMapRandCfg
{
	SpecialTreasureMapRandCfg() : nItemId(0), nType(0), nRate(0), nGongGaoId(0) {}
	int32_t nItemId;
	int32_t nType;
	MemChrBagVector vGetItems;
	int32_t nRate;
	MemChrBag vShowItem;
	int32_t nGongGaoId;
};
typedef std::list<SpecialTreasureMapRandCfg> SpecialTreasureMapRandCfgList;

// CfgQQGift (QQGameDaTing.txt)
struct CfgQQGift
{
	CfgQQGift() : nIndex(0), nType(0), nCondition(0) {}
	int32_t nIndex;
	int32_t nType;
	MemChrBagVector vReward;
	int32_t nCondition;
};

// CfgTGPGift (TGP tables)
struct CfgTGPGift
{
	CfgTGPGift() : nIndex(0), nLevel(0) {}
	int32_t nIndex;
	std::string strPF;
	int32_t nLevel;
	MemChrBagVector vReward;
};

// CfgPassiveSkill (SkillPassiveAttr.txt)
struct CfgPassiveSkill
{
	CfgPassiveSkill() : id(0), type(0) {}
	int32_t id;
	int32_t type;
	AttrAddonVector vAttrs;
	std::list<TalentAddon> lTalentAddon;
};

// CfgSwVipBuff
struct CfgSwVipBuff
{
	CfgSwVipBuff() : nIndex(0), nType(0), nLevel(0) {}
	int32_t nIndex;
	int32_t nType;
	AttrAddonVector vAttr;
	int32_t nLevel;
};

// CfgScoreShop (ScoreShop.txt)
struct CfgScoreShop
{
	CfgScoreShop() : nIndex(0), nType(0), nScore(0), nLimitCount(0) {}
	int32_t nIndex;
	int32_t nType;
	MemChrBagVector vItem;
	int32_t nScore;
	int32_t nLimitCount;
};
typedef std::map<int32_t, CfgScoreShop> CfgScoreShopMap;

// CfgSpecialEquip (SpecialEquip.txt)
struct CfgSpecialEquip
{
	CfgSpecialEquip() : nId(0), nPos(0), nLevel(0), nSuitId(0) {}
	int32_t nId;
	int32_t nPos;
	int32_t nLevel;
	AttrAddonVector vAttr;
	int32_t nSuitId;
};

// CfgSpeciaSkillDistance (SkillSpecialDamage.txt)
struct CfgSpeciaSkillDistance
{
	CfgSpeciaSkillDistance() : nId(0), nSkillId(0), nDistance(0), nDamage(0), nRate(0) {}
	int32_t nId;
	int32_t nSkillId;
	int32_t nDistance;
	int32_t nDamage;
	int32_t nRate;
};
typedef std::map<int32_t, CfgSpeciaSkillDistance> CfgSpeciaSkillDistanceMap;

// CfgLevelRefining (LvRefining.txt)
struct CfgLevelRefining
{
	CfgLevelRefining() : nLevel(0), nCostGold(0), nCostItem(0), nCostCount(0) {}
	int32_t nLevel;
	AttrAddonVector vAttr;
	int32_t nCostGold;
	int32_t nCostItem;
	int32_t nCostCount;
};
typedef std::map<int32_t, CfgLevelRefining> CfgLevelRefiningMap;

// CfgSystemOpenReward (System.txt)
struct CfgSystemOpenReward
{
	CfgSystemOpenReward() : nId(0) {}
	int32_t nId;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, CfgSystemOpenReward> CfgSystemOpenRewardMap;

// CfgSpecialMap (SpecialMap.txt)
struct CfgSpecialMap
{
	CfgSpecialMap() : nMapId(0), nType(0), nLevel(0), nEnterCount(0), nCostType(0), nCostValue(0) {}
	int32_t nMapId;
	int32_t nType;
	int32_t nLevel;
	int32_t nEnterCount;
	int32_t nCostType;
	int32_t nCostValue;
};
typedef std::map<int32_t, CfgSpecialMap> CfgSpecialMapTable;

// CfgTestServerReward (TestActivity.txt)
struct CfgTestServerReward
{
	CfgTestServerReward() : nIndex(0), nType(0), nCondition(0) {}
	int32_t nIndex;
	int32_t nType;
	MemChrBagVector vReward;
	int32_t nCondition;
};
typedef std::map<int32_t, CfgTestServerReward> CfgTestServerRewardMap;

// CfgShenWeiTask (ShenWeiTask.txt)
struct CfgShenWeiTask
{
	CfgShenWeiTask() : nTaskId(0), nType(0), nCondition(0) {}
	int32_t nTaskId;
	int32_t nType;
	int32_t nCondition;
	MemChrBagVector vReward;
};
typedef std::map<int32_t, CfgShenWeiTask> CfgShenWeiTaskTable;

// CfgSuperTeHui (SuperDiscount.txt)
struct CfgSuperTeHui
{
	CfgSuperTeHui() : nIndex(0), nType(0), nPrice(0), nRate(0), nCondition(0) {}
	int32_t nIndex;
	int32_t nType;
	MemChrBagVector vItem;
	int32_t nPrice;
	int32_t nRate;
	int32_t nCondition;
};
typedef std::map<int32_t, CfgSuperTeHui> CfgSuperTeHuiTable;

// CfgShouHuRefiningLevel (StarSpaceLevel.txt)
struct CfgShouHuRefiningLevel
{
	CfgShouHuRefiningLevel() : nLevel(0), nCostGold(0) {}
	int32_t nLevel;
	AttrAddonVector vAttr;
	int32_t nCostGold;
};
typedef std::map<int32_t, CfgShouHuRefiningLevel> CfgShouHuRefiningLevelMap;

// CfgShouHuRefiningSuit (StarSpaceSuit.txt)
struct CfgShouHuRefiningSuit
{
	CfgShouHuRefiningSuit() : nSuitId(0), nCount(0) {}
	int32_t nSuitId;
	int32_t nCount;
	AttrAddonVector vAttr;
};
typedef std::map<int32_t, CfgShouHuRefiningSuit> CfgShouHuRefiningSuitMap;

// CfgShiZhuangSuit (ShiZhuangSuit.txt)
struct CfgShiZhuangSuit
{
	CfgShiZhuangSuit() : nSuitId(0), nCount(0) {}
	int32_t nSuitId;
	int32_t nCount;
	AttrAddonVector vAttr;
};
typedef std::map<int32_t, CfgShiZhuangSuit> CfgShiZhuangSuitTable;

// CfgMonthlyChouJiang (TurntableReward.txt)
struct CfgMonthlyChouJiang
{
	CfgMonthlyChouJiang() : nIndex(0), nType(0), nRate(0) {}
	int32_t nIndex;
	int32_t nType;
	MemChrBagVector vReward;
	int32_t nRate;
};

// CfgMonthlyChouJiangRecharge (TurntableRechargePoint.txt)
struct CfgMonthlyChouJiangRecharge
{
	CfgMonthlyChouJiangRecharge() : nIndex(0), nPoint(0) {}
	int32_t nIndex;
	int32_t nPoint;
};
typedef std::map<int32_t, CfgMonthlyChouJiangRecharge> CfgMonthlyChouJiangRechargeMap;

// CfgSouGouDaTing (SouGouDaTing.txt)
struct CfgSouGouDaTing
{
	CfgSouGouDaTing() : nIndex(0), nCondition(0) {}
	int32_t nIndex;
	std::string strPlatform;
	MemChrBagVector vReward;
	int32_t nCondition;
};
typedef std::map<int32_t, CfgSouGouDaTing> CfgSouGouDaTingTable;

// CfgPlatformDaTing (DaTing.txt)
struct CfgPlatformDaTing
{
	CfgPlatformDaTing() : nIndex(0), nIconId(0) {}
	int32_t nIndex;
	std::string strPlatform;
	int32_t nIconId;
	MemChrBagVector vReward;
};

// CfgPlatformVip (OutLinkVip.txt)
struct CfgPlatformVip
{
	CfgPlatformVip() : nIndex(0), nVipLevel(0), nCondition(0) {}
	int32_t nIndex;
	std::string strPlatform;
	int32_t nVipLevel;
	MemChrBagVector vReward;
	int32_t nCondition;
};

// CfgPlatformReward (Reward.txt)
struct CfgPlatformReward
{
	CfgPlatformReward() : nIndex(0), nType(0), nCondition(0) {}
	int32_t nIndex;
	std::string strPlatform;
	int32_t nType;
	MemChrBagVector vReward;
	int32_t nCondition;
};
typedef std::map<int32_t, CfgPlatformReward> CfgPlatformRewardMap;

// CfgShangRen (MagicBusiness.txt)
struct CfgShangRen
{
	CfgShangRen() : nId(0), nType(0), nPrice(0), nRate(0) {}
	int32_t nId;
	int32_t nType;
	MemChrBagVector vItem;
	int32_t nPrice;
	int32_t nRate;
};

// CfgSelectItem (GiftChoose.txt)
struct CfgSelectItem
{
	CfgSelectItem() : nId(0), nGongGaoId(0) {}
	int32_t nId;
	MemChrBagVector vItem;
	int32_t nGongGaoId;
};
typedef std::map<int32_t, CfgSelectItem> CfgSelectItemCfgMap;

// CfgShiZhuLevelUp (ShiZhuangUpGrade.txt)
struct CfgShiZhuLevelUp
{
	CfgShiZhuLevelUp() : nId(0), nLevel(0), nCostGold(0) {}
	int32_t nId;
	int32_t nLevel;
	int32_t nCostGold;
	AttrAddonVector vAttr;
};
typedef std::map<int32_t, CfgShiZhuLevelUp> CfgShiZhuLevelUpMap;

// CfgNationalDayTask (PassportTask.txt)
struct CfgNationalDayTask
{
	CfgNationalDayTask() : nTaskId(0), nType(0), nCondition(0), nPoint(0) {}
	int32_t nTaskId;
	int32_t nType;
	int32_t nCondition;
	MemChrBagVector vReward;
	int32_t nPoint;
};
typedef std::map<int32_t, CfgNationalDayTask> CfgNationalDayTaskTable;

// CfgNationalDayPassport (Passport.txt)
struct CfgNationalDayPassport
{
	CfgNationalDayPassport() : nLevel(0), nPoint(0) {}
	int32_t nLevel;
	int32_t nPoint;
	MemChrBagVector vReward;
	MemChrBagVector vVipReward;
};
typedef std::map<int32_t, CfgNationalDayPassport> CfgNationalDayPassportTable;

// CfgBlacketMarket goods entry
struct CfgBlackMarketGoods
{
	CfgBlackMarketGoods() : nIndex(0), nType(0), nPrice(0), nRate(0), nCondition(0) {}
	int32_t nIndex;
	int32_t nType;
	MemChrBagVector vItem;
	int32_t nPrice;
	int32_t nRate;
	int32_t nCondition;
};


// ============================================================================
// Sub-type definitions for placeholder table types
// ============================================================================

struct BossLevelInfo
{
	int32_t BossLevel;
	std::list<int32_t> BossMapList;
};

struct MapBossInfo
{
	int32_t nId;
	std::list<int32_t> BossMapList;
};

struct CfgActivityTask
{
	int32_t nTaskId;
	int32_t nMinLevel;
	int32_t nMaxLevel;
	int32_t nRatio;
};

struct cfgEquipUpPhase
{
	int32_t m_CostEquip;
	std::list<ItemData> m_CostItems;
	int32_t m_CostMoney;
	int32_t m_GiveEquip;
	int32_t m_GongGaoId;
};

struct CfgFamilyDungeon
{
	int8_t  nHard;
	int32_t nDungeonId;
	int32_t nFamilyLevel;
	int32_t nCostMoney;
	int32_t nBaoKuFuBen;
	int32_t nNpcId;
	int32_t X;
	int32_t Y;
	int32_t nTime;
};

struct CurrentData
{
	int32_t nId;
	int32_t nValue;
};

struct cfgGoblinData
{
	int32_t m_nIndex;
	int32_t m_nRefreshTime;
	std::vector<CurrentData> m_RefreshMonsters;
	int32_t m_mapId;
	std::vector<Position> m_RevivePosVector;
};

struct CfgMonsterRand
{
	int32_t nId;
	std::vector<AttrAddon> vAttrValue;
	std::vector<AttrAddon> vAttrRatio;
	int32_t nSkill;
};

struct CfgMYSJReward
{
	int32_t nId;
	int32_t nClass;
	int32_t nCount;
	int32_t nBind;
	int32_t nWeight;
	int32_t nShow;
	int32_t nGroup;
	int32_t nMin;
	int32_t nMax;
	int32_t nBroad;
	int32_t nSpecial;
};

struct cfgSpecialMonster
{
	int32_t m_mid;
	int32_t Type;
	int32_t Value;
	int32_t Portal;
	int32_t Award;
	int32_t HurtDrop;
	int32_t EscapeOdds;
};

struct SevenTouZi
{
	int32_t nId;
	int32_t nType;
	int32_t nCondition;
	std::vector<MemChrBag> vItem;
};

struct MonthTouZi
{
	int32_t nDay;
	std::vector<MemChrBag> vItem;
	int32_t nGongGaoId;
};

struct CycleTowerMapCfg
{
	int32_t Floor;
	int32_t FloorType;
	int32_t MonsterId;
};

struct CycleTowerCost
{
	ItemData CostData;
	int32_t CostGold;
};

struct CfgMaintainCompensate
{
	int32_t nIndex;
	int32_t nTime;
	std::vector<MemChrBag> vItems;
	CfgMaintainCompensate() : nIndex(0), nTime(0) {}
};

struct CfgMapRoad
{
	int32_t nIndex;
	int32_t nNextIndex;
	int32_t nMapId;
	std::list<Position> road;
};

struct CfgDungeonNpc
{
	int32_t id;
	int32_t NpcId;
	int32_t x;
	int32_t y;
};

struct EnergyCfg
{
	int32_t MaxEnergy;
	int32_t EnergyTime;
	std::vector<int32_t> EnergyPrice;
	int32_t BuyAddEnergy;
	EnergyCfg() : MaxEnergy(0), EnergyTime(0), BuyAddEnergy(0) {}
};

// ============================================================================
// Table/container class definitions for placeholder types
// ============================================================================

class BossDistribution
{
public:
	std::map<int32_t, BossLevelInfo> m_BossLevelInfoMap;
	std::map<int32_t, MapBossInfo>   m_MapBossInfoMap;

	void AddBossLevelInfo(const BossLevelInfo* p_stu)
	{
		m_BossLevelInfoMap[p_stu->BossLevel] = *p_stu;
	}
	void AddMapBossInfo(const MapBossInfo* p_stu)
	{
		m_MapBossInfoMap[p_stu->nId] = *p_stu;
	}
};

class CfgActivityTaskTable
{
public:
	std::map<int32_t, CfgActivityTask> m_mTasks;
	void AddTask(int32_t nId, int32_t nMinLevel, int32_t nMaxLevel, int32_t nRatio)
	{
		CfgActivityTask stu;
		stu.nTaskId = nId;
		stu.nMinLevel = nMinLevel;
		stu.nMaxLevel = nMaxLevel;
		stu.nRatio = nRatio;
		m_mTasks[nId] = stu;
	}
};

class CfgBeastShrineTable
{
public:
	std::map<int32_t, std::list<ItemData>> m_mEnterCost;
	bool AddEnterCost(int32_t nTimes, const std::list<ItemData>& vItem)
	{
		m_mEnterCost[nTimes] = vItem;
		return true;
	}
	const std::list<ItemData>* GetEnterCost(int32_t nTimes) const
	{
		auto it = m_mEnterCost.find(nTimes);
		if (it != m_mEnterCost.end()) return &it->second;
		return nullptr;
	}
};

class CfgEquipBlessTable
{
public:
	std::list<CfgEquipBless> m_lstBless;
	bool Add(const CfgEquipBless* stu)
	{
		m_lstBless.push_back(*stu);
		return true;
	}
};

class cfgEquipUpPhaseTable
{
public:
	std::list<cfgEquipUpPhase> m_cfgEquipUpPhase;
	void AddData(const cfgEquipUpPhase* stu)
	{
		m_cfgEquipUpPhase.push_back(*stu);
	}
};

class CfgFamilyDungeonTable
{
public:
	std::map<int8_t, CfgFamilyDungeon> m_mDungeon;
	void AddDungeon(const CfgFamilyDungeon* stu)
	{
		m_mDungeon[stu->nHard] = *stu;
	}
	const CfgFamilyDungeon* GetDungeon(int8_t nHard) const
	{
		auto it = m_mDungeon.find(nHard);
		if (it != m_mDungeon.end()) return &it->second;
		return nullptr;
	}
};

class cfgGoblinTableData
{
public:
	std::map<int32_t, cfgGoblinData> m_GoblinDataMap;
	void Add(cfgGoblinData* stu)
	{
		m_GoblinDataMap[stu->m_nIndex] = *stu;
	}
};

class CfgMonsterRandTable
{
public:
	std::map<int32_t, CfgMonsterRand> m_mMonsterRand;
	std::vector<int32_t>              m_vId;
	void AddMonsterRand(const CfgMonsterRand* stu)
	{
		m_mMonsterRand[stu->nId] = *stu;
		m_vId.push_back(stu->nId);
	}
};

class CfgMYSJRewardTable
{
public:
	std::map<int32_t, std::list<CfgMYSJReward>> m_mReward;
	std::map<int32_t, std::list<CfgMYSJReward>> m_mGroupReward;
	std::map<int32_t, int32_t>                   m_mDungeonGroup;
	bool Add(int32_t nId, const CfgMYSJReward* reward)
	{
		m_mReward[nId].push_back(*reward);
		if (reward->nGroup > 0)
		{
			m_mGroupReward[reward->nGroup].push_back(*reward);
			m_mDungeonGroup[nId] = reward->nGroup;
		}
		return true;
	}
};

class cfgSpecialMonsterTable
{
public:
	std::map<int32_t, cfgSpecialMonster> m_specialMonster;
	void Add(cfgSpecialMonster* stu)
	{
		m_specialMonster[stu->m_mid] = *stu;
	}
};

class CfgTouZiTable
{
public:
	std::map<int32_t, SevenTouZi> m_SevenTouZiMap;
	std::map<int32_t, MonthTouZi> m_MonthTouZiMap;
	void AddSevenTouZi(SevenTouZi* p_stu)
	{
		m_SevenTouZiMap[p_stu->nId] = *p_stu;
	}
	void AddMonthTouZi(MonthTouZi* p_stu)
	{
		m_MonthTouZiMap[p_stu->nDay] = *p_stu;
	}
};

class CycleTowerTable
{
public:
	std::map<int32_t, CycleTowerCost>  m_CycleTowerCostMap;
	std::map<int32_t, CycleTowerMapCfg> m_CycleTowerMapCfgMap;
	std::map<int32_t, int32_t>         m_CycleTowerFloor;
	void AddCycleTowerMapCfg(int32_t MapId, const CycleTowerMapCfg& stu)
	{
		m_CycleTowerMapCfgMap[MapId] = stu;
		m_CycleTowerFloor[stu.Floor] = MapId;
	}
	void AddCycleTowerCost(int32_t Times, const CycleTowerCost& stu)
	{
		m_CycleTowerCostMap[Times] = stu;
	}
};

class CfgMaintainCompensateTable
{
public:
	std::map<int32_t, CfgMaintainCompensate> m_mMap;
	bool Add(const CfgMaintainCompensate* stu)
	{
		m_mMap[stu->nIndex] = *stu;
		return true;
	}
};

class CfgMapRoadTable
{
public:
	std::map<int32_t, CfgMapRoad> m_mMapRoad;
	void Add(const CfgMapRoad* road)
	{
		m_mMapRoad[road->nIndex] = *road;
	}
};


struct CfgCampWarContKill
{
	int32_t nLevel;
	int32_t nKillCount;
	int32_t nKillPoint;
	int32_t nBroadcast;
	int32_t nBreakBroadcast;
	int32_t nTitle;
};

struct CfgCampWarReward
{
	int32_t nIndex;
	int32_t nMaxIndex;
	int32_t nFailMailId;
	int32_t nWinMailId;
	std::vector<MemChrBag> FailItems;
	std::vector<MemChrBag> WinItems;
};

struct CfgCityWarContReward
{
	int32_t id;
	std::vector<MemChrBag> vBreakReward;
	int32_t nBreakMailId;
};

struct CfgDungeonScore
{
	int32_t nDungeonId;
	int32_t nKillCount;
	MemChrBag Item;
};

struct CfgEquipDecompose
{
	int32_t m_nClass;
	int32_t m_nId;
	std::vector<MemChrBag> m_vGiveItems;
	int32_t m_nCostMoney;
	int32_t m_nLimitType;
	int32_t m_nLimitValue;
	int32_t m_NpcId;
};

struct CfgEquipPosSuit
{
	int32_t m_nLevel;
	std::vector<AttrAddon> m_vAttrAddon;
};

struct CfgGemOpenHole
{
	int32_t m_nSlot;
	int32_t m_nCostMoney;
	std::list<ItemData> m_lCostItem;
};

struct CfgGemSuit
{
	int32_t m_nLevel;
	std::vector<AttrAddon> m_vAttrAddon;
};

struct ChouJiangLuckyCfg
{
	int32_t MaxLucky;
	int32_t MinQuality;
	int32_t MaxQuality;
};

struct ChouJiangWeekReward
{
	int32_t Index;
	int32_t Times;
	std::vector<MemChrBag> Items;
};

struct FamilyMedal
{
	int32_t nLevel;
	int32_t nNeedFamilyLevel;
	int32_t nNeedFamilyExp;
	std::list<AddAttribute> lAttrList;
	int32_t nGongGaoId;
	int32_t DefRdc;
};

#define CFG_DATA Answer::Singleton<CfgData>::instance()
