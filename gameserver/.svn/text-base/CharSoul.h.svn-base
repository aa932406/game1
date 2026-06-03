/*
* 魂力系统
* 玩家等级上限
*/

#ifndef __TPOC_CHAR_SOUL_H__
#define __TPOC_CHAR_SOUL_H__

#include "CfgData.h"
#include "ExtSystemBase.h"
#include "Skill.h"
#include "SkillBuff.h"

class Player;
class CExtCharSoul : public CExtSystemBase
{
public:
	CExtCharSoul();
	virtual ~CExtCharSoul();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onAddSoul( Answer::NetPacket* inPacket );
	int32_t				onUpgradeSoulLevel( Answer::NetPacket* inPacket );

public:
	bool				IsFunctionOpen() const;
	void				SendSoulInfo();
	void				AddCharAttr();
	int32_t				GetLevel() const;
	int32_t				GetPlayerMaxLevel() const;

	int32_t				AddLevel( int32_t Level );

private:
	void				broadcastLevelUp();

private:
	int32_t				m_nLevel;
	int64_t				m_nExp;
};

#endif	//__TPOC_CHAR_SOUL_H__
