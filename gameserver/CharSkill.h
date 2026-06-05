/*
* ����ϵͳ
* ��Ҽ���
* XP����
*/
#ifndef __TPOC_CHAR_SKILL_H__
#define __TPOC_CHAR_SKILL_H__

#include "CfgData.h"
#include "ExtSystemBase.h"
#include "Skill.h"
#include "SkillBuff.h"
#include <map>

#define ADD_XP_TIME				30000		// XPÿ������ʱ����
#define XP_WAIT_SELECT_TIME		30000		// XPѡ��ʱ��
#define XP_TIME					60000		// XP����ʱ��

class Player;
class CExtCharSkill : public CExtSystemBase
{
public:
	CExtCharSkill();
	virtual ~CExtCharSkill();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual	void		OnUpdate( int64_t curTick );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onStartXP( Answer::NetPacket* inPacket );
	int32_t				onSocialUpdateXP( Answer::NetPacket* inPacket );
	int32_t				onSocialAddExp( Answer::NetPacket* inPacket );
	void				SendXpRecord();
	void				AddPlayerExp( int32_t AddExp );

public:
	bool				IsInXP() const;
	void				SetInXP( bool bFlg );
	SkillId_t			GetSelectedXP() const;
	void				AddMonsterExp( int64_t nAddExp );
	void				FillXP();
	void				LearnXPSkill();
	bool				IsLearnedXPSkill() const;
	void				DieResetXp();
	void				ClearXP();
	void				sendSocialAddXP( int32_t AddXp = 0 );				// XPֵ����
private:
	void				checkXP( int64_t curTick );
	void				sendXP();

	void				startXP( SkillId_t nSkillId );
	void				endXP();

	void				sendSocialStartXP();			// ��ʼXP����
	void				sendSocialEndXP();				// ����XP����
	void				sendSocialBreakXP();			// ����XP����

public:
	// ========== 新版本添加方法 ==========
	void				InitSystem();
	void				initSkills();
	void				AddCharAttr();
	int32_t				CallSkillBattle();
	int32_t				GetPower();
	int32_t				AddPower( int32_t nAddPower );
	int32_t				AddSkillPoint( int32_t nAddPoint );
	int32_t				AddSkillBookPoint( int32_t nAddPoint );
	int32_t				GetDropMoneyRate();
	void				recalDropMoneyRate();
	bool				CanUseSkillAndMove();
	void				addSkillBuffTo( UnitHandle launcher, SkillId_t nSkillId );
	void				broadcastIntervalEffect( int32_t nSkillId );
	void				calActiveSkillCD( int32_t nSkillId );
	void				checkActiveList();
	void				recalAcviveSkill();
	void				doSkill( SkillId_t nSkillId );
	void				doSkillActive();
	int32_t				activeSkill( SkillId_t nSkill );
	int32_t				getActiveSkill( int32_t nSkillId );
	int32_t				addActiveSkill( int32_t nSkillId );
	int32_t				getAddonSkill( int32_t nSkillId );
	int32_t				addAddonSkill( int32_t nSkillId );
	void				removeAddonSkill( int32_t nSkillId );
	void				checkAddonSkills();
	void				checkSummonSkills();
	void				CheckSummonBuff();
	void				CheckSelfTrigBuff();
	void				CheckHPPecentTrigBuff();
	void				CheckPhaseDamageTrigBuff();
	void				checkSkillTrigBuff( SkillId_t nSkillId );
	void				CheckSkillTrigBuff( SkillId_t nSkillId );
	void				AddSuitSkillEnergy( int32_t nAddValue );
	void				checkSuitSkillEnergy();
	void				AddOtherSkill( int32_t nSkillId, int32_t nLevel );
	void				addTalentAddon( int32_t nAddonId );
	int32_t				getTalentAddon( int32_t nAddonId );
	void				recalTalentAddon();
	void				loadTalentPoints( const PlayerDBData& dbData );
	void				saveTalentPoints( PlayerDBData& dbData );
	void				SendTalentInfo();
	void				SendTalentAddon();
	void				SendlearedSkill();
	void				UseSkillBook( int32_t nSkillId );
	void				removeSkillByTalent( int32_t nSkillId );

private:
	int32_t				onDoUnitSkill( Answer::NetPacket* inPacket );
	int32_t				onDoAddonSkill( Answer::NetPacket* inPacket );
	int32_t				onAddTalentPoint( Answer::NetPacket* inPacket );

private:
	bool				m_bXP;
	int32_t				m_nXP;
	SkillId_t			m_nSelectXP;
	int64_t				m_nXPAddExp;

	int64_t				m_nLastTick;
	int64_t				m_nStartTick;

	// ========== 新版本成员 ==========
	int32_t				m_nPower;
	int32_t				m_nSkillPoint;
	int32_t				m_nSkillBookPoint;
	int32_t				m_nDropMoneyRate;
	bool				m_bCanUseSkillAndMove;
	std::map<int32_t, int32_t>	m_mActiveSkills;
	std::map<int32_t, int32_t>	m_mAddonSkills;
	std::map<int32_t, int32_t>	m_mTalentAddons;
	int32_t				m_nSuitSkillEnergy;
};

#endif	//__TPOC_CHAR_SKILL_H__
