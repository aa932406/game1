#ifndef __EXT_SKILL_H__
#define __EXT_SKILL_H__

#include "ExtSystemBase.h"

struct Skill 
{
	int32_t nSkillId;
	int32_t nSkillLevel;
	int64_t	nLastUseTick;
};
typedef std::list<Skill> SkillList;

class CRobot;
class CExtSkill : public CExtSystemBase
{
public:
	CExtSkill();
	virtual ~CExtSkill();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onSkillList( Answer::NetPacket* inPacket );

public:
	void				CheckLearnSkill( int32_t nBookId, int32_t nSlot );
	int32_t				GetSkillId( int64_t curTick );
	int32_t				GetSkillFlag();
	Skill*				GetSkill( int32_t nId );

private:
	void				updateSkill( const Skill& skill );
	void				sendLearnSkill();

private:
	SkillList			m_skills;
	int32_t				m_nSkillFlag;

};

#endif	//__EXT_BAG_H__
