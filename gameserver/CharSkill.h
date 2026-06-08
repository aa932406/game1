/*
* 技能系统
* 天赋加点
* XP技能
* 2019完整版
*/
#ifndef __TPOC_CHAR_SKILL_H__
#define __TPOC_CHAR_SKILL_H__

#include "CfgData.h"
#include "ExtSystemBase.h"
#include "Skill.h"
#include "SkillBuff.h"
#include <map>
#include <list>

#define ADD_XP_TIME				30000		// XP每增加时间间隔
#define XP_WAIT_SELECT_TIME		30000		// XP选择时间
#define XP_TIME					60000		// XP持续时间

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
	void				sendSocialAddXP( int32_t AddXp = 0 );

public:
	// ========== 2019版本方法 ==========
	void				InitSystem();
	void				initSkills( int32_t TalentId, int32_t TalentLevel );
	void				AddCharAttr();
	int32_t				CallSkillBattle();
	int32_t				GetPower();
	int32_t				AddPower( int32_t nValue );
	int32_t				GetDropMoneyRate();
	void				recalDropMoneyRate();
	bool				CanUseSkillAndMove( int64_t nCurTick, bool ResetTick );
	void				addSkillBuffTo( SkillId_t nSkillId, int32_t nGroupId, Unit* pTarget );
	void				broadcastIntervalEffect( int32_t nSkillId );
	int32_t				calActiveSkillCD( int32_t nSkillId );
	void				checkActiveList();
	void				recalAcviveSkill();
	int32_t				doSkill( Answer::NetPacket* inPacket, const CfgActiveSkill* pCfgSkill,
								SkillResultVector* results, Position srcPos,
								int32_t nSkillId, int32_t nSkillFlag, bool bAction );
	void				doSkillActive( const CfgTrigSkill* pCfgSkill, Unit* pTarget );
	int32_t				activeSkill( int32_t nId, const UnitHandle* handler );
	const CfgActiveSkill*	getActiveSkill( int32_t nSkillId );
	bool				addActiveSkill( const CfgActiveSkill* pCfgSkill );
	AddonSkill*			getAddonSkill( int32_t nSkillFlag );
	bool				addAddonSkill( const AddonSkill* addonSkill );
	bool				removeAddonSkill( int32_t nSkillFlag );
	void				checkAddonSkills( int64_t nCurTick );
	void				checkSummonSkills( int64_t nCurTick );
	void				CheckSummonBuff();
	void				CheckSelfTrigBuff( int8_t nTrigType );
	void				CheckHPPecentTrigBuff( int32_t nLastPecent, int32_t nNowPecent );
	void				CheckPhaseDamageTrigBuff( int8_t nPhase );
	void				checkSkillTrigBuff( const CfgActiveSkill* pCfgSkill, const SkillResultVector* results );
	void				CheckSkillTrigBuff( int32_t nSkillGroup, Unit* target, int8_t nTrigType );
	void				AddSuitSkillEnergy( int32_t nAddValue );
	void				checkSuitSkillEnergy( int64_t nCurTick );
	void				AddOtherSkill( int32_t nSkillId, int32_t nLevel );
	void				addTalentAddon( const AddAttribute& stu );
	void				getTalentAddon( TalentAddonList* addonList );
	void				recalTalentAddon();
	std::string			saveTalentPoints();
	void				loadTalentPoints( const std::string& str );
	void				SendTalentInfo();
	void				SendTalentAddon();
	void				SendlearedSkill( int32_t nTalentId );
	int32_t				AddSkillPoint( int32_t Id, int32_t Points );
	bool				UseSkillBook( int32_t Id );
	bool				AddSkillBookPoint( int32_t Id, int32_t Points );
	void				removeSkillByTalent( int32_t TalentId, int32_t TalentLevel );

private:
	int32_t				onDoUnitSkill( Answer::NetPacket* inPacket );
	int32_t				onDoAddonSkill( Answer::NetPacket* inPacket );
	int32_t				onAddTalentPoint( Answer::NetPacket* inPacket );

private:
	// XP系统
	bool				m_bXP;
	int32_t				m_nXP;
	SkillId_t			m_nSelectXP;
	int64_t				m_nXPAddExp;
	int64_t				m_nLastTick;
	int64_t				m_nStartTick;

	// ========== 2019版本成员 ==========
	std::map<int32_t, SkillLevelInfo>	m_SkillLevelMap;		// 天赋等级映射
	std::list<AddonSkill>				m_lAddonSkills;		// 附加技能列表
	std::list<SummonSkill>				m_lSummonSkills;		// 召唤技能列表
	std::list<MemTalent>				m_lActiveTalent;		// 激活天赋列表
	std::list<int32_t>					m_lActiveSkills;		// 主动技能ID列表
	std::list<int32_t>					m_lPassiveSkills;		// 被动技能ID列表
	std::list<int32_t>					m_lTrigSkills;			// 触发技能ID列表
	std::map<int32_t, CfgActiveSkill>	m_mActiveSkills;		// 主动技能配置映射
	std::map<int32_t, int32_t>			m_OthreSkillLevelMap;	// 其他技能等级
	std::map<int32_t, int64_t>			m_mSkillCD;				// 技能CD时间映射

	int32_t				m_nPower;
	int32_t				m_nDropMoneyRate;
	int32_t				m_SkillBattle;
	int64_t				m_SkillPublicCD;
	int64_t				m_nLastAddonTick;
	int64_t				m_PowerLastTick;
	int64_t				m_lastActionTick;
	int64_t				m_nLastEnergyTick;
	int32_t				m_nSuitSkillEnergy;
};

#endif	//__TPOC_CHAR_SKILL_H__
