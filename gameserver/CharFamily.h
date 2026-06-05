#ifndef __CHAR_FAMILY_H__
#define __CHAR_FAMILY_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharFamily : public CExtSystemBase
{
public:
	CExtCharFamily();
	virtual ~CExtCharFamily();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual void		OnDaySwitch( int32_t nDiffDays );
	int32_t			OnDaySwitch();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onContribution( Answer::NetPacket* inPacket );
	int32_t				onRegistPet( Answer::NetPacket* inPacket );
	int32_t				onUnRegistPet( Answer::NetPacket* inPacket );

	int32_t				onSocialCreateFamily( Answer::NetPacket* inPacket );
	int32_t				onSocialUpdateFamilyInfo( Answer::NetPacket* inPacket );

	// Missing declarations added for compatibility
	int32_t				onAskFamilyInfo( Answer::NetPacket* inPacket );
	int32_t				onAskFamilyMemberList( Answer::NetPacket* inPacket );
	int32_t				onAskFamilyLogs( Answer::NetPacket* inPacket );
	int32_t				onAskFamilyTotem( Answer::NetPacket* inPacket );
	int32_t				onActiveTotem( Answer::NetPacket* inPacket );
	int32_t				onOpenTotem( Answer::NetPacket* inPacket );

	int32_t				onRequestFamilyWarPillarInfo( Answer::NetPacket* inPacket );
	int32_t				onFamilyWarAddPillarMoney( Answer::NetPacket* inPacket );
	int32_t				onSocialFamilyWarPillarAddMoney( Answer::NetPacket* inPacket );

	int32_t				onReceiveFamilyTask( Answer::NetPacket* inPacket );
	int32_t				onGetFamilyTaskReward( Answer::NetPacket* inPacket );

	// Missing declarations added for compatibility
	int32_t				onSocialRequestFamilyWarPillarInfo( Answer::NetPacket* inPacket );
	int32_t				onSocialFamilyWarAddPillarMoney( Answer::NetPacket* inPacket );
	int32_t				onSocialGetDailyReward( Answer::NetPacket* inPacket );
	int32_t				onReceiveTask( Answer::NetPacket* inPacket );
	int32_t				onGetTaskReward( Answer::NetPacket* inPacket );
	// 新版本添加方法 - 家族功能扩展
	int32_t				onUpgradeTotem( Answer::NetPacket* inPacket );
	int32_t				onPray( Answer::NetPacket* inPacket );
	int32_t				onAskPrayRank( Answer::NetPacket* inPacket );
	int32_t				onAskTotemRank( Answer::NetPacket* inPacket );
	int32_t				onActiveFamilyLight( Answer::NetPacket* inPacket );
	int32_t				onAskFamilyWarInfo( Answer::NetPacket* inPacket );
	int32_t				onStartFamilyWar( Answer::NetPacket* inPacket );
	int32_t				onDonateItem( Answer::NetPacket* inPacket );
	int32_t				onAskFamilyDonateLog( Answer::NetPacket* inPacket );

public:
	FamilyId_t			GetFamilyId() const;
	std::string			GetFamilyName() const;
	int32_t				GetFamilyLevel() const;
	int8_t				GetPosition() const;
	int32_t				GetContribution() const;
	int32_t				GetFamilyAddBattle() const;
	int32_t				GetFamilyTotomAddBattle() const;
	bool				TotomIsOpened( int32_t PetBaseId );
	void				OnSynPetContribution();
	void				SendAddFamilyTaskCount();
	void				AddContribution( int32_t GongXian, int32_t JunTuanZiJin );
public:
	// ========== 新版本添加方法 ==========
	void				FamilySay( const char* pMsg );
	void				AddMedRes( int32_t nAddVal );
	void				AddSkillAttr();
	int32_t				GetDefRdc();
	bool				IsDeclareWarFamily();
	void				EndMining();
	int32_t				GetHoeId();
	void				refreshWeekTime();
	void				loadSkillString( const PlayerDBData& dbData );
	void				saveSkillString( PlayerDBData& dbData );
	int32_t				getSkillLevel( int32_t nSkillId );
	int32_t				addSkillLevel( int32_t nSkillId, int32_t nAddLevel );
	void				sendSkillInfo();
	void				sendSocialSendRedPacket( int64_t nGold, int32_t nRedPacketCount );
	void				sendSocialImpeach( int64_t nBeImpeachCid );
	void				SendHoe();
	void				SendFamilyDungeonInfo();

private:
	int32_t				onSocialApplyFamily( Answer::NetPacket* inPacket );
	int32_t				onSocialApprove( Answer::NetPacket* inPacket );
	int32_t				onSocialKick( Answer::NetPacket* inPacket );
	int32_t				onSocialLeave( Answer::NetPacket* inPacket );
	int32_t				onSocialDestroy( Answer::NetPacket* inPacket );
	int32_t				onSocialAppoint( Answer::NetPacket* inPacket );
	int32_t				onSocialEditNotice( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestFamilyInfo( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestMemberList( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestLogs( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestTotemList( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestApplicants( Answer::NetPacket* inPacket );
	int32_t				onSocialCancelApply( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestRegistPets( Answer::NetPacket* inPacket );
	int32_t				onSocialAddContribution( Answer::NetPacket* inPacket );
	int32_t				onSocialFamilyTaskCount( Answer::NetPacket* inPacket );
	int32_t				onSocialRequestPlayerPets( Answer::NetPacket* inPacket );
	int32_t				onSocialChangeFamilyName( Answer::NetPacket* inPacket );
	int32_t				onSocialInviteAll( Answer::NetPacket* inPacket );
	int32_t				onSocialStartBoss( Answer::NetPacket* inPacket );
	int32_t				onSocialImpeachResult( Answer::NetPacket* inPacket );
	int32_t				onBindRedPacketTake( Answer::NetPacket* inPacket );
	int32_t				onSendRedPacket( Answer::NetPacket* inPacket );
	int32_t				onSetTalkTask( Answer::NetPacket* inPacket );
	int32_t				onImpeach( Answer::NetPacket* inPacket );
	int32_t				onLearnSkill( Answer::NetPacket* inPacket );
	int32_t				onRequestSkillInfo( Answer::NetPacket* inPacket );
	int32_t				onGetTalkTaskReward( Answer::NetPacket* inPacket );
	int32_t				onGetFamilyDungeonInfo( Answer::NetPacket* inPacket );
	int32_t				onEnterTerritory( Answer::NetPacket* inPacket );
	int32_t				onStartFamlyDungeon( Answer::NetPacket* inPacket );
	int32_t				onEnterFamilyDungeon( Answer::NetPacket* inPacket );
	int32_t				onOpenTerritory( Answer::NetPacket* inPacket );
	int32_t				onAddBossPoint( Answer::NetPacket* inPacket );
	int32_t				onFamilyBuyHoe( Answer::NetPacket* inPacket );
	int32_t				onWearHoe( Answer::NetPacket* inPacket );
	int32_t				onFamilyLevelUpMedal( Answer::NetPacket* inPacket );
	int32_t				onQuickSubmitFamilyTask( Answer::NetPacket* inPacket );
	void				StartFamilyAct();
	void				EnterFamilyDungeon();

private:
	bool				isFunctionOpen() const;
	int32_t				getMaxRegistPetNum( int32_t nLevel );
	void				sendSocialAddContribution( int32_t nMoney, int32_t nGold );
	void				sendSocialRegistPet( PetId_t nPetId );
	void				sendSocialUnRegistPet( PetId_t nPetId );
	void				sendSocialUpdatePetContribution();
	void				sendSocialAddTaskContribution( int32_t GongXian, int32_t JunTuanZiJin );
	void				recalPetAddContribute();
	int32_t				calPetAddContribute();

private:
	FamilyId_t			m_nFamilyId;
	int8_t				m_nPosition;
	int32_t				m_nContribution;
	int32_t				m_nRegistPetCount;
	int32_t				m_nPetContribution;
	bool				m_IsLogin;

	CObjPet*			m_vRegistPetList[MAX_PET_ID+1];			// ע�����
	int8_t				m_vPetRegistTime[MAX_PET_ID+1];			// ����ע��ʱ��
};

#endif	//__CHAR_FAMILY_H__
