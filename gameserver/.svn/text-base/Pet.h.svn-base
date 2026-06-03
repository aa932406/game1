/*
* 宠物基本信息
*/
#ifndef __TPOC_PET_H__
#define __TPOC_PET_H__

#include "CfgData.h"
#include "DataStruct.h"
#include "Unit.h"

#define LEVEL_DIFF	5	//宠物和人物最大相差5级

enum PET_HUANHUA_TYPE
{
	PHT_START_ATTR		= 1,		// 初始属性幻化
	PHT_GROW_ATTR		= 2,		// 成长率幻化
	PHT_LUCKY			= 3			// 幸运值幻化
};

enum PET_ILLUSION_ITEM_TYPE
{
	PIIT_NONE			= 0,		// 不使用道具
	PIIT_LUCKY_GRASS	= 1,		// 幸运草
	PIIT_GOD_GRASS		= 2,		// 神仙草
};

// 与数据库对应，不能乱改
enum PET_RECORD
{
	PR_USE_EXP_GRAIN		= 0,			// 使用圣兽魔晶
	PR_USE_EXP_BALL			= 1,			// 使用经验球

	PET_RECORD_SIZE,						// 记录数量 NOTE：必须小于 128
};

enum PET_RECORD_LIMIT
{
	PRL_USE_EXP_GRAIN		= 10,			// 使用圣兽魔晶
	PRL_USE_EXP_BALL		= 10,			// 使用经验球
};

struct PetSkillInfo 
{
	SkillId_t	nId;
	int32_t		nLevel;
	int64_t		nCDTime;
};

class CPet
{
public:
	CPet();
	~CPet();

public:
	void			reset();

public:
	void			Init( CharId_t nOwner, PetId_t nPetId, int32_t nBaseId, int8_t nFromWay );
	void			Init( CharId_t nOwner, PetId_t nPetId, const CfgPetEgg& cfgEgg, int8_t nFromWay );
	void			Reborn();
	void			Reborn( const CfgPetEgg& cfgEgg );
	void			OnLoadFromDB( const MemPetDBData& pet, bool bCal = false );
	void			OnSaveToDB( MemPetDBData& pet );

public:
	PetId_t			GetPetId() const;
	int32_t			GetFlag() const;
	void			SetPetId( PetId_t nPetId );
	int32_t			GetBaseId() const;
	int32_t			GetLevel() const;
	int32_t			GetPetLevel() const;
	int64_t			GetExp() const;
	PET_PHASE		GetPhase() const;
	Job_t			GetOrderJob() const;					// 指挥需求：		幻兽对职业的需求，如果幻兽指挥需求中为0，就是任何职业都可以使用。
	Job_t			GetPetJob() const;						// 幻兽类型：		战士型、法师型等
	int32_t			GetRare() const;						// 罕见度：			幻兽稀有度
	int32_t			GetRein() const;						// 转生次数：
	int32_t			GetReinLimit() const;					// 转生次数限制：
	bool			IsRidePet() const;
	bool			IsReinLimit() const;
	int32_t			GetBaseAttr( PET_ATTR attr ) const;
	int32_t			GetBattle() const;
	int32_t			GetPoints() const;
	int32_t			GetStartPoints() const;
	int32_t			GetGrowPoints() const;
	int32_t			GetGrowTimes() const;
	int8_t			GetFromWay() const;
	int32_t			GetLucky() const;
	bool			AddExp( int64_t nExp );
	void			AppendBaseInfo( Answer::NetPacket* packet );
	PetSkillInfo*	GetSkill( SkillId_t nSkill );
	PetSkillInfo*	GetSkillByPos( int8_t nSkillPos );
	bool			LearnSkill( SkillId_t nSkill, int8_t nSkillPos );
	bool			ForgetSkill( SkillId_t nSkill );
	std::string		GetName() const;
	void			ChangeName( const std::string& strName );
	void			ChangeOwner( CharId_t nOwner, bool bSend = true );
	bool			CheckRecord( PET_RECORD record ) const;
	int32_t			AddRecord( PET_RECORD record, int32_t nAddVal = 1 );
	PET_PHASE		ChangePhase( PET_PHASE phase );
	bool			CanIllusion( CPet* pPet, int8_t nType );
	bool			Illusion( CPet* pPet, int8_t nType, int8_t nUseItem );
	void			SendPetInfo( Player* player );

	bool			NeedSyncSelf() const;
	void			SetSyncSelf( bool bSync = false );
	bool			NeedSyncStatus() const;
	void			SetSyncStatus( bool bSync = false );

	CharId_t		GetOwnerId() const;
	void			SetOwnerId( CharId_t nCharId );
	int32_t			GetRankFlag() const;
	void			ResetRankFlag();
	bool			CheckAttrChange( PET_ATTR attr ) const;
	SkillId_t		RandSkill();

	void			ResetRecord();

	bool			IsPetBorn() const;
	void			SetPetBorn();

	void			GetPetData( SocialPetData& petData );

	void			SetRankIndex( PET_RANK_TYPE nRankType, int32_t nRankIndex );
	int32_t			GetRankIndex( PET_RANK_TYPE nRankType ) const;
	bool			UseLuckyItem();
	bool			IsXOType() const;

	void			ReSetBaseAttr( CfgPetGift*	pCfgPetGift );
	void			AddBaseAttr( PET_ATTR attr, int32_t val );

	int32_t			getLevelUpExp() const;
	bool			growAttrIllusionByItem( int8_t nUseItem );
private:
	void			born();
	void			born( const CfgPetEgg& cfgEgg );
	void			calPoints();
	void			initSkill();
	void			setPhase( PET_PHASE phase );
	PET_PHASE		randPhase();

	bool			calGrowAttrIllusion( int32_t& nMainAttr, int32_t nMaxAttr, int32_t nGrowRatio, int32_t nRein, int32_t nKey );
	int32_t			calGrowAttrPoints( int32_t nVal, int32_t nMaxVal, int32_t nMaxPoints );
	int32_t			calStartAttrPoints( int32_t nVal, int32_t nMaxVal, int32_t nMaxPoints );
	
	bool			checkRecord( PET_RECORD record, int32_t nVal ) const;
	void			appendInitInfo( Answer::NetPacket* packet );
	void			appendSkillInfo( Answer::NetPacket* packet );
	void			appendRecordInfo( Answer::NetPacket* packet );
	void			appendRankInfo( Answer::NetPacket* packet );
//	bool			startAttrIllusion( CPet* pPet, int8_t nUseItem );
	bool			growAttrIllusion( CPet* pPet, int8_t nUseItem );
	bool			Illuseion( int8_t nUseItem );
//	bool			luckyIllusion( CPet* pPet, int8_t nUseItem );
	bool			calStartAttrIllusion( int32_t& nMainAttr, int32_t nViceAttr, int32_t nKey );
//	bool			checkStartAttrIllusion( CPet* pPet );
	bool			checkGrowAttrIllusion( CPet* pPet );
//	bool			checkLuckyIllusion( CPet* pPet );

	void			initBaseAttr();
	void			initBaseAttr( const CfgPetEgg& petEgg );
	void			adjustAttr( int32_t& nVal, int32_t nMaxVal );
	void			onChange();
	bool			checkLevelUp( int32_t OwnerLevel );
	void			onLevelUp();

	void			loadRecords( const std::string& str );
	void			loadSkills( const std::string& str );
	std::string		saveRecords() const;
	std::string		saveSkills() const;

	int32_t			calIllusionRein( int8_t nUseItem );
	int32_t			calIllusionKey( int8_t nUseItem );

	void			attrChange( PET_ATTR attr );
	int8_t			getSkillBarSize() const;

	void			broadcastPetGrowAttr( int32_t nPoints );
	void			broadcastPetStartAttr( int8_t nAttr, int32_t nVal );
	void			broadcastPetLucky( int16_t nVal );

private:
	CharId_t		m_nOwner;							// 所有者
	PetId_t			m_nPetId;							// 宠物ID
	int32_t			m_nFlag;							// 更新标记
	int32_t			m_nBaseId;							// 基础ID
	char			m_strName[MAX_NAME_CCH_LENGTH+1];	// 宠物名称
	int32_t			m_nLevel;							// 宠物等级
	int64_t			m_nExp;								// 宠物经验值
	int32_t			m_nPotential;						// 潜力值：			Potential 它每增加1%，敌人对幻兽的伤害就会减少1%，幻兽对敌人的伤害就会增加1%，幻兽死亡会让潜力值减少，幻兽升级会让潜力值增加。潜力值在你每次登录时都会恢复到50。（怎么增加还不知道，到时候可能会特别说明）
	int32_t			m_nRein;							// 转生次数：		Reincarnation		描述宠物转生的次数（数值范围0~9999）
	int32_t			m_nAdjustRein;						// 转生次数限制：
	int32_t			m_nNumber;							// 身份牌：			幻兽40级时可以通过雷鸣交易行的进化炉进行二次进化，二次进化完成后幻兽将获得一个幻兽身份牌，身份牌上的序号是在这个服务器中是独一无二的。
	int32_t			m_nGrowPoints;						// 成长率评分
	int32_t			m_nStartPoints;						// 初始属性评分
	int32_t			m_nPoints;							// 幻兽品质：		这里显示的为这只幻兽的品质，即成长率。品质越好，成长率就越高（通常情况下）。
	int32_t			m_nBattle;							// 战斗力：
	PET_PHASE		m_nPhase;							// 宠物相性：		风、水、火、土、雷
	int32_t			m_nLucky;							// 幸运值：			幸运值是个神奇的属性，它在冥冥中决定了幻兽许多的东西。一个幸运儿总是很讨人喜欢的。
	int32_t			m_vAttr[PET_ATTR_COUNT];			// 基础属性
	int32_t			m_vRecord[PET_RECORD_SIZE];			// 宠物记录：		一些宠物自身的记录
	PetSkillInfo	m_vSkill[PET_SKILL_BAR_SIZE];		// 宠物技能
	int8_t			m_nFromWay;							// 来源：			PET_FROM_WAY
	int32_t			m_nGrowTimes;						// 成长率幻化次数

	bool			m_bPetBorn;							// 宠物出生:
	uint32_t		m_nRankFlag;						// 排行榜更新标记
	PetRankIndex	m_RankIndex;						// 排行榜名次	// 0为榜外

	bool			m_bNeedSyncSelf;					// 基础信息更新
	bool			m_bNeedSyncStatus;					// 状态更新标记
};

#endif	// __TPOC_PET_H__
