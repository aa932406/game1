#ifndef __SOCIAL_FAMILY_H__
#define __SOCIAL_FAMILY_H__

#include "SocialPet.h"
#include "SocialPlayer.h"
#include <vector>
#include <map>
#include <set>
#include "DataStructs.h"

class Totom 
{
public:
	Totom()
	{
		nValue			= -1;		
		nTotalPoints	= 0;
		nStartTime		= 0;	
	}
	int8_t		nValue;			// 图腾战斗力 = -1 时为开启
	int32_t		nTotalPoints;	// 总评分
	int32_t		nStartTime;
};
typedef std::map<int32_t, Totom> TotomMap;
typedef std::map<CharId_t, PlayerInfo*> MemberMap;
struct FamilyMemberContributionGreater {	bool operator()( PlayerInfo* pLeft, PlayerInfo* pRight ) const;	};
typedef std::multiset< PlayerInfo*, FamilyMemberContributionGreater > MemberSet;
typedef std::list<PlayerInfo*>	MemberList;
typedef std::list<CSocialPet*>	RegPetList;

class Family
{
public:
	Family();
	~Family();

public:
	void			reset();
	void			LoadFromDB( const FamilyDBData& dbData );
	void			Init( FamilyId_t nFamilyId, const std::string& name, SocialPlayer& creater );
	FamilyId_t		GetId() const;
	std::string		GetName() const;
	bool			OnApply( PlayerInfo* pApplyer );															// 申请
	bool			OnApplyReply( SocialPlayer& player, PlayerInfo* pApplyer, bool bAccept );					// 回复申请
	void			OnApplyOperator( SocialPlayer& player, bool bAccept );										// 一键回复
	void			AddContribution( SocialPlayer& player, int32_t nMoney, int32_t nGold, int32_t nAddValue );	// 捐献
	void			AddContribution( SocialPlayer& player, int32_t Contribution, int32_t Money );
	bool			RegistPet( const SocialPlayer& player, CSocialPet* pPet );									// 登记宠物
	bool			UnRegistPet( const SocialPlayer& player, CSocialPet* pPet );															// 宠物取消登记
	bool			ActiveTotom( SocialPlayer& player, int32_t nTotomId, int32_t nAddBattle );					// 激活图腾
	bool			SetHonorPosition( SocialPlayer& player, PlayerInfo* pMember, int8_t nPosition );			// 任命荣誉职位
	bool			UnSetHonorPosition( SocialPlayer& player, PlayerInfo* pMember );							// 解除荣誉职位
	bool			AppendListInfo( Answer::NetPacket* packet, const SocialPlayer& player );
	void			SendFamilyInfo( const SocialPlayer& player );
	void			SendMemberInfo( const SocialPlayer& player );
	void			SendTotomInfo( const SocialPlayer& player );
	void			SendRegistPetInfo( const SocialPlayer& player );
	void			SendPlayerPetInfo( const SocialPlayer& player );
	void			SendApplyInfo( const SocialPlayer& player );
	void			SendLogInfo( const SocialPlayer& player );
	void			SendNotice( const SocialPlayer& player );
	void			ChangeNotice( const std::string& notice, bool IsCreate = false );
	void			Broadcase( Answer::NetPacket* packet );
	bool			RemoveApply( CharId_t nCharId );
	bool			KickMember( SocialPlayer& player, PlayerInfo* pMember );
	bool			LeaveMember( PlayerInfo* pMember );
	void			OnDestroy();
	void			OnUpdateContribution( SocialPlayer& player );
	void			CheckTotomTime( int32_t nNowTime );
	void			AppendFamilyWarInfo( Answer::NetPacket* packet );
	bool			DecFamilyMoney( int32_t nMoney );
	bool			IsAuto() ;
	bool			AutoAddMember( SocialPlayer* pPlayer, PlayerInfo* pInfo );
	void			onSetAutoAgree( int8_t nFlag );
	void			onOpenTotom( SocialPlayer* pPlayer, int32_t PetBaseId );
	bool			OpenTotom( int32_t PetBaseId );
	void			sendGameUpdateFamilyInfo( int8_t nReason );
	void			AddFamilyTaskCount();
	void			ResetFamilyCount();
	void			SendFamilyTaskCount( SocialPlayer* player = NULL );
private:
	void			loadMembers();
	void			loadPets();
	void			loadTotom();
	void			loadLog();
	void			resetPosition();
	void			setPosition( PlayerInfo* pMember );
	PlayerInfo*		getLeader();
	//SocialPlayer*	getMember( CharId_t nCharId );
	bool			addMember( SocialPlayer& player, PlayerInfo* pPlayerInfo );								// 添加成员
	bool			removeMember( PlayerInfo* pMember );													// 删除成员
	void			removeAllPlayerRegPet( CharId_t nCharId );
	bool			isApplied( CharId_t nCharId ) const;
	int32_t			calBattle() const;
	int32_t			calContribution() const;
	void			recalContribution();
	int32_t			calTotomBattle() const;
	int32_t			calTotomPoints( int32_t nTotomId ) const;
	void			recalTotomPoints( int32_t nBaseId );
	int32_t			RecalStatTotomCount();
	void			broadcastNotice();
	void			sendGameUpdatePlayerInfo( PlayerInfo* pMember );

	void			broadcastGameNeedUpdatePlayerInfo();			// 广播图腾加战斗力给全军团

	void			broadcastLevelChange( int32_t nLevel, int8_t nFlg );
	void			broadcastSetPosition( const std::string& opName, CharId_t CharId,const std::string& tarName, CharId_t tarId, int8_t nPosition );
	void			broadcastEnterFamily( const std::string& opName, CharId_t opId,const std::string& tarName,  CharId_t tarId );
	void			broadcastLeaveFamily( const std::string& memberName,CharId_t CharId );
	void			broadcastKickMember( const std::string& opName, CharId_t opId,const std::string& tarName, CharId_t tarId );
	void			broadcastActiveTotom( const std::string& opName, CharId_t opId, int32_t nTotomId, int8_t nAddBattle );
	void			broadcastRegistPet( const std::string& opName,CharId_t opId, int32_t nBaseId, int32_t nAddContribute );
	void			broadcastPositionUp( const std::string& opName,CharId_t opId, int8_t nPosition );
	void			broadcastFamilyDestroy();
	void			broadcastUnSetHonorPosition( const std::string& opName,CharId_t CharId, const std::string& tarName, CharId_t tarId );

	void			saveFamilyInfo();
	void			savePlayerInfo( PlayerInfo* pMember );
	void			saveTotomInfo( int32_t nTotomId, const Totom& totom );
	void			addFamilyLog( const FamilyLog& log );

	void			sendFamilyApplyResult( const std::string& opName, PlayerInfo* pApplyer, bool bAccept );

	void			appendFamilyLogInfo( Answer::NetPacket* packet, const FamilyLog& log );
private:
	FamilyId_t		m_nId;									// 军团Id
	std::string		m_strName;								// 军团名称
	int32_t			m_nLevel;								// 军团等级
	int32_t			m_nContribution;						// 军团贡献（经验值）
	int32_t			m_nMoney;								// 军团资金
	int32_t			m_nMemberCount;							// 军团人数
	int8_t			m_AutoAgree;							// 是否自动同意
	std::string		m_strNotice;							// 军团公告
	int32_t			m_FamilyTaskCount;						// 军团任务次数
	int32_t			m_LastFamilyTaskTime;					// 最后任务时间
	MemberList		m_vPosition[FAMILY_POSITION_COUNT];		// 职位表
	//MemberMap		m_mMember;								// 成员列表
	//MemberSet		m_setMember;							// 成员列表（按贡献值排序 ）

	PlayerInfo*		m_vApplyer[FAMILY_APPLY_COUNT];			// 申请列表
	Totom			m_vTotom[MAX_PET_ID+1];					// 军团图腾
	RegPetList		m_lstRegistPet;							// 军团登记幻兽列表

	FamilyLogList	m_lstFamilyLog;
	int32_t			m_OpenTotomCount;
};

#endif	//__SOCIAL_FAMILY_H__
