#pragma once
#include <string>
#include "Team.h"
#include "TeamDungeon.h"
#include "Friend.h"

class SocialPlayer
{
public:
	SocialPlayer();
	~SocialPlayer();

public:
	int32_t handleNetPacket(Answer::NetPacket *inPacket);

public:
	void init( int32_t cgindex, CharId_t cid, int32_t uid, int32_t sid, PlayerInfo* pInfo );
	void reset();
	int16_t getGateIndex() const;
	CharId_t getCid() const;
	int32_t getuid() const;
	int32_t getsid() const;

	int8_t GetVip() const;
	int8_t GetVipLevel() const;
	Job_t getJob() const;
	Sex_t getSex() const;
	int32_t getLevel() const;
	std::string getName() const;
	int8_t GetJueWei() const;
	bool inActivity() const;

	int32_t		GetCloth() const;
	int32_t		GetWeapon() const;

	int32_t		GetBattle() const;
	int32_t		GetLastLogOutTime() const;

	PlayerInfo*	GetPlayerInfo();

	// 帮派
	FamilyId_t	GetFamilyId() const;				// 帮派ID
	int8_t		GetFamilyPosition() const;			// 帮派职务
	std::string	GetFamilyName() const;				// 帮派名称
	int32_t		GetFamilyContribution() const;		// 帮派贡献度
	int32_t		GetFamilyApplyCount() const;
	void		SendGameUpdateFamilyInfo();
	int32_t		getLevelFamilyTime() const;
	//void		AppendFamilyRegistPetInfo( Answer::NetPacket* packet, int16_t& nCount );

	//int32_t getFamilyId();
	//int32_t getFamilyPos();
	//std::string getFamilyName();
	//void setFamilyId(int32_t value);
	//void setFamilyApplyCount(int32_t flag);
	//void setFamilyPos(int32_t value);
	//void updateFamilyContribue(int32_t addon);
	//void clearFamilyApply();
	//void clearFamilyInfo();
	//void sendFamilyStateData();
	//void sendGameSynFamily(updateFamilyInfoReason reason);
	//void sendGameSynFamilyLevel(int32_t cgindex,int32_t uid,int32_t sid,int32_t level);


	// 组队系统
	void	SendGameUpdateTeamInfo();	// 同步组队信息
	bool	IsInTeam() const;
	bool	IsAutoAcceptInvite() const;
	bool	IsAutoAcceptApply() const;
	bool	CanAcceptInvite() const;
	bool	CanAddFriend()  const;
	void	AddInvite( Team* pTeam );
	void	SetTeam( Team* pTeam );
	Team*	GetTeam();

	// XP
	void	AddXP( int32_t AddXp );
	int32_t GetXP() const;
	int8_t	GetXPState() const;
	int64_t	GetXPAddExp() const;
	bool	IsLearnedXP() const;
	void	ResetXP( int32_t nValue = 0 );
	void	SendGameUpdateXP();			// 同步XP信息
	void	SendGameAddExp( int64_t nExp );
	void	SetJoinWithXP();

	// 组队副本
	TeamDungeon* GetTeamDungeon();
	void	SetTeamDungeon( TeamDungeon* pTeamDungeon );
	bool	IsTeamDungeonReady();
	void	SendGameTeamDungeonStart( int32_t nLine );
	void	SendGameTeamDungeonUpdateInfo();

	// 摆摊标记
	bool	IsInStall() const;

	// 名人堂
	void	SendGameFightResult( bool bWin );
	void	SendGameGetHallOfFameRankReward( int32_t nIndex );
	void	SendGameHallOfFameRankRewardInfo( int32_t nIndex, int8_t nReward );

	// 发送游戏服添加货币
	void	SendGameAddCurrency( int8_t nCurrency, int32_t nCount );

	Int32Vector getYellowVipLevel(CharId_t tcid);
	//AttrAddonInfoVector parseEffect(int32_t id, const std::string &str);
	//AttrAddonInfoVector getEquipSecondAttrAddon(const ViceGeneralEquipInfo &memEquip,int32_t position);
	//AttrAddonInfo getGemRatioAddon(int32_t id);

private:
	//void updateActivityData(int8_t activityId, int8_t kindom, int8_t count);
	//int32_t onSelectKingdom(Answer::NetPacket *inPacket);
	int32_t onQueryActivityInfo(Answer::NetPacket *inPacket);

	// 帮派
	int32_t onFamilyRequestList(Answer::NetPacket *inPacket);			// 请求帮派列表
	int32_t onFamilyRequestInfo(Answer::NetPacket *inPacket);			// 请求帮派信息
	int32_t onFamilyRequestMemberList(Answer::NetPacket *inPacket);		// 查看帮派成员列表
	int32_t onFamilyRequestTotomList(Answer::NetPacket *inPacket);		// 查看图腾信息
	int32_t onFamilyRequestAppliers(Answer::NetPacket *inPacket);		// 查看帮派申请列表
	int32_t onFamilyRequestRegistPets(Answer::NetPacket *inPacket);		// 查看帮派注册宠物
	int32_t onFamilyRequestPlayerPets(Answer::NetPacket *inPacket);		// 查看自身注册宠物
	int32_t onFamilyRequestLogs(Answer::NetPacket *inPacket);			// 查看帮派日志
	//int32_t onQueryFamilyNotice(Answer::NetPacket *inPacket);
	int32_t onFamilyChangeNotice(Answer::NetPacket *inPacket);			// 编辑帮派公告
	//int32_t onQuerySelfFamilyInfo(Answer::NetPacket *inPacket);
	//int32_t onUpgradeFamilyLevel(Answer::NetPacket *inPacket);
	int32_t onFamilyCreate(Answer::NetPacket *inPacket);				// 创建帮派
	int32_t onFamilyDestroy(Answer::NetPacket *inPacket);				// 解散帮派
	int32_t onFamilyApply(Answer::NetPacket *inPacket);					// 帮派申请
	int32_t onFamilyCancelApply(Answer::NetPacket *inPacket);			// 取消申请
	int32_t onFamilyOpenTotom( Answer::NetPacket *inPacket );			// 激活帮派图腾

	//int32_t onFamilyInvite(Answer::NetPacket *inPacket);
	//int32_t onFamilyAppointInvite(Answer::NetPacket *inPacket);
	int32_t onFamilyApprove(Answer::NetPacket *inPacket);				// 回复申请
	int32_t onFamilyAppoint(Answer::NetPacket *inPacket);				// 任命帮派职务
	int32_t onFamilyKick(Answer::NetPacket *inPacket);					// 帮派踢人
	int32_t onSetAutoAgree( Answer::NetPacket* inPacket );				// 设置自动入帮
	//int32_t onFamilyLeaderDown(Answer::NetPacket *inPacket);
	int32_t onFamilyLeave(Answer::NetPacket *inPacket);					// 离开帮派
	int32_t onFamilyActiveTotom(Answer::NetPacket *inPacket);			// 激活图腾
	void	UpdatePlayerLeaveFamily();
	int32_t onGameCreateFamily(Answer::NetPacket *inPacket);
	//int32_t onGameChangeFamilyName(Answer::NetPacket *inPacket);
	//int32_t onGameBreakFamily(Answer::NetPacket *inPacket);
	//int32_t onGameUpdateFamilyMoney(Answer::NetPacket *inPacket);
	int32_t onGameUpdatePetContribute(Answer::NetPacket *inPacket);
	int32_t onGameAddFamilyContribute(Answer::NetPacket *inPacket);
	int32_t onGameFamilyRegistPet(Answer::NetPacket *inPacket);
	int32_t onGameFamilyUnRegistPet(Answer::NetPacket *inPacket);
	int32_t onGameFamilyAddTaskCount(Answer::NetPacket *inPacket);
	int32_t onFamilyRequestTaskCount(Answer::NetPacket *inPacket);
	int32_t onGameFamilyAddContribute( Answer::NetPacket *inPacket );
	//int32_t onRankRequestInfo(Answer::NetPacket *inPacket);
	int32_t onQueryRealTimeRank(Answer::NetPacket *inPacket);
	int32_t onUseExchangeCode(Answer::NetPacket *inPacket);
	int32_t onSocialPublicChat(Answer::NetPacket *inPacket);
	int32_t onSocialPrivateChat(Answer::NetPacket *inPacket);
	//int32_t onQueryKillerRank(Answer::NetPacket *inPacket);
	//int32_t onQueryGambleRecord(Answer::NetPacket *inPacket);
	int32_t onChangeName(Answer::NetPacket *inPacket);
	int32_t onGameUpdateActivityState(Answer::NetPacket *inPacket);
	int32_t onGameUpdateLimitShop(Answer::NetPacket *inPacket);
	//int32_t onGameUpdateKingdomContribute(Answer::NetPacket *inPacket);
	//int32_t onGameAddContribution(Answer::NetPacket *inPacket);
	int32_t onGameUseExchangeCode(Answer::NetPacket *inPacket);
	int32_t onGameChangeName(Answer::NetPacket *inPacket);
	int32_t onGameQueryPlayerInfo(Answer::NetPacket *inPacket);
	
	// 组队系统
	int32_t	onCreateTeam( Answer::NetPacket* inPacket );
	int32_t	onInviteIntoTeam( Answer::NetPacket* inPacket );
	int32_t	onSetTeamLeader( Answer::NetPacket* inPacket );
	int32_t	onKickOutTeamMember( Answer::NetPacket* inPacket );
	int32_t	onLeaveTeam( Answer::NetPacket* inPacket );
	int32_t	onApplyIntoTeam( Answer::NetPacket* inPacket );
	int32_t	onReplyTeamInvite( Answer::NetPacket* inPacket );
	int32_t	onReplyTeamApply( Answer::NetPacket* inPacket );
	int32_t	onSetTeamAutoOperate( Answer::NetPacket* inPacket );
	int32_t	onTeamDestroy( Answer::NetPacket* inPacket );
	
	// XP
	int32_t	onGameAddXP( Answer::NetPacket* inPacket );
	int32_t	onGameStartXP( Answer::NetPacket* inPacket );
	int32_t	onGameEndXP( Answer::NetPacket* inPacket );
	int32_t	onGameBreakXP( Answer::NetPacket* inPacket );
	int32_t	OnDieResetXp( Answer::NetPacket* inPacket );

	// 排行榜
	int32_t	onAskPetRankInfo( Answer::NetPacket* inPacket );
	int32_t	onAskPetRankList( Answer::NetPacket* inPacket );
	int32_t	onAskGameRank( Answer::NetPacket* inPacket );

	// 组队副本
	int32_t onTeamDungonRequestList(Answer::NetPacket *inPacket);
	int32_t onTeamDungeonLeave(Answer::NetPacket *inPacket);
	int32_t onTeamDungeonKick(Answer::NetPacket *inPacket);
	int32_t onTeamDungeonReady(Answer::NetPacket *inPacket);
	int32_t onTeamDungeonSetAutoStart(Answer::NetPacket *inPacket);

	int32_t onGameTeamDungonCreate(Answer::NetPacket *inPacket);
	int32_t onGameTeamDungonJoin(Answer::NetPacket *inPacket);
	int32_t onGameTeamDungeonStart(Answer::NetPacket *inPacket);
	int32_t onGameTeamDungeonLeave(Answer::NetPacket *inPacket);

	// 崇拜
	int32_t	onWorship( Answer::NetPacket *inPacket );
	int32_t	onRequestWorshipInfo( Answer::NetPacket *inPacket );
	int32_t	onGameWorship( Answer::NetPacket *inPacket );
	void	sendGameWorship( CharId_t nCharId );
	void	notifyWorshipInfo( CharId_t nCharId );
	void	savePlayerWorshipRecord( CharId_t nCharId, int32_t nWorshipRecord );

	// 拍卖
	int32_t	onAuctionSell( Answer::NetPacket *inPacket );
	int32_t onAuctionBuy( Answer::NetPacket *inPacket );
	int32_t onAuctionCancel( Answer::NetPacket *inPacket );
	int32_t onAuctionItemList( Answer::NetPacket *inPacket );
	int32_t onAuctionSelfItems( Answer::NetPacket *inPacket );
	int32_t onAuctionRecords( Answer::NetPacket *inPacket );
	int32_t	onGameAuctionSell( Answer::NetPacket *inPacket );
	int32_t	onGameAuctionBuy( Answer::NetPacket *inPacket );
	int32_t	onGameStall( Answer::NetPacket *inPacket );
	void	sendGameAuctionSell( int8_t nType, int32_t nBagSlot, int32_t nCount, int32_t nPrice );
	void	sendGameAuctionBuy( int32_t nId, int8_t nPayType, int32_t nPrice );
	void	sendClientSellItem( int32_t nId, const AuctionItem& item );

	// 活动
	int32_t	onGameActivityNotifyFamilyWarInfo( Answer::NetPacket *inPacket );
	int32_t	onGameActivityFamilyWarAddPillarMoney( Answer::NetPacket *inPacket );

	// 名人堂
	int32_t	onHallOfFameRankInfo( Answer::NetPacket *inPacket );
	int32_t	onHallOfFameGetReward( Answer::NetPacket *inPacket );
	int32_t	onGameHallOfFameFight( Answer::NetPacket *inPacket );
	int32_t	onGameHallOfFameRequestInfo( Answer::NetPacket *inPacket );
	int32_t	onGameHallOfFameRewardResult( Answer::NetPacket *inPacket );

private:
	// 帮派
	void loadFamilyInfo();
	void loadApplyFamilyInfo();
	//void sendFamilyInfo();
	//void sendFamilyNotice(int32_t fid,const std::string &notice);
	//void sendSelfFamilyInfo();
	//void sendFamilyResource(int32_t contribute);
	//void sendInviteFamily(std::string familyname,int32_t tcgindex);
	//void sendFamilyAppliers();
	//int32_t createFamily(std::string name,std::string &notice,const Int32Vector &slot);
	//int32_t approveForFamily(int32_t cid, int32_t result);
	//int32_t appointFamily(int32_t tcid, int32_t pos);
	//int32_t reorderStoreFamily(int32_t slot_id, int32_t slot_id2);
	//void sendFamilyShopInfo();
	//void sendFamilyApplyNote();
	//void sendGameFamilyPosChange(const std::string &name,int32_t position);
	//void sendGameChangeFamilyName(const std::string &name, int32_t bag, int32_t slot);
	void sendGameCreateFamily( const std::string &name, const std::string &notice );
	//void sendGameUpdateFamilyContribute(int32_t addon);

	//void sendGameLeaderDown(int32_t tcid);
	//void sendGameLeaderCid(int32_t cid,int32_t uid,int32_t sid,int32_t cgindex);
	//void sendGotoEnemy(int32_t cid,int32_t type,const BagSlotVector & item);
	void sendGameUseExchangeCode(int32_t item_id,const std::string &code);
	//void sendActivityData();
//全服限制物品购买
	int32_t	OnAskItemLimitInfo( Answer::NetPacket *inPacket );
	int32_t	OnBuyLimitItem( Answer::NetPacket *inPacket );
	int32_t OnReceiveBuySucceed( Answer::NetPacket *inPacket );
	void	SendBuyItemCount( int32_t ShopId, int32_t AddCount );
	void    SendLimitItemCountChange( int32_t ShopId );
	void	InitFaBaoInfo( std::string  FaBaoLevelString, std::string FaBaoDressString, Answer::NetPacket *inPacket );

private:
	void	resetXP( int32_t nValue = 0 );

private:
	PlayerInfo*	m_pInfo;
	//int16_t m_job;
	//int32_t m_sex;
	
	int16_t m_cgindex;

	CharId_t m_cid;
	int32_t m_uid;
	int32_t m_sid;
	//int32_t m_level;
	//VipType	m_vip;
	int32_t m_activityState;

	int32_t m_get_exchange_code; //是否兑换码中


	int32_t m_blessing;//is blessing
	int32_t m_receiveBless;//is receiving bless
	//int32_t m_gettingAwardZhiyuanqianxian;
	ActivityRankPtrVector m_activityRanks;

	//int64_t m_last_change_name_tick;
	int64_t m_last_auction_tick;

	//std::string m_name;

	int32_t m_limitShopBuying;

	typedef std::list<Team*> TeamList;
	// 组队
	Team*			m_pTeam;
	TeamList		m_lstInvite;
	bool			m_bAutoApply;
	bool			m_bAutoInvite;
	bool			m_bCanInvite;
	bool			m_bCanAddFriend;

	//bool			m_bIsLearnedXP;	// 是否已经学习XP技能
	bool			m_bJoinWithXP;		// 在XP中加入队伍
	int32_t			m_nXP;				// XP值
	int8_t			m_nXPState;			// XP状态
	int64_t			m_nXPAddExp;		// XP期间获得的经验值

	// 组队副本
	TeamDungeon*	m_pTeamDungeon;
	bool			m_bTeamDungeonReady;

	// 摆摊
	bool			m_bStall;
	int32_t			m_LeaveFamilyTime;
public:
	CFriend&		GetFrined(){ return m_Friend; }
private:
	CFriend			m_Friend;

};

