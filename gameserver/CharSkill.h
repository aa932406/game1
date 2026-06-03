/*
* 技能系统
* 玩家技能
* XP技能
*/
#ifndef __TPOC_CHAR_SKILL_H__
#define __TPOC_CHAR_SKILL_H__

#include "CfgData.h"
#include "ExtSystemBase.h"
#include "Skill.h"
#include "SkillBuff.h"

#define ADD_XP_TIME				30000		// XP每次增加时间间隔
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
	void				sendSocialAddXP( int32_t AddXp = 0 );				// XP值增加
private:
	void				checkXP( int64_t curTick );
	void				sendXP();

	void				startXP( SkillId_t nSkillId );
	void				endXP();

	void				sendSocialStartXP();			// 开始XP技能
	void				sendSocialEndXP();				// 结束XP技能
	void				sendSocialBreakXP();			// 跳过XP技能

private:
	bool				m_bXP;
	int32_t				m_nXP;
	SkillId_t			m_nSelectXP;
	int64_t				m_nXPAddExp;

	int64_t				m_nLastTick;
	int64_t				m_nStartTick;
};

#endif	//__TPOC_CHAR_SKILL_H__
