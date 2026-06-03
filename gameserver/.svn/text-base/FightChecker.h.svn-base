// 战斗检测
#ifndef __TPOC_FIGHT_CHECKER_H__
#define __TPOC_FIGHT_CHECKER_H__

#include "ExtSystemBase.h"
#define  SUB_PK_TIME  5*60*1000				//在线5分钟减一次pk值
#define  BLACK_KILLED_SUB_PK_VALUES 10		//黑名被杀减10点pk值
#define  KILLED_WHITE_PLAYER_PK_VALUES 20	//击杀白名增加20点pk值
#define  KILLED_RED_PLAYER_PK_VALUES 10		//击杀白名增加20点pk值
#define  PK_PROTECT_LEVEL		70
class Player;
class CExtFightChecker : public CExtSystemBase
{
public:
	CExtFightChecker();
	virtual ~CExtFightChecker();

public:
	virtual void	OnCleanUp();
	virtual void	OnUpdate( int64_t curTick );

public:
	bool			IsInFight() const;
	int8_t			GetFightState() const;
	void			SetInFight( int64_t nCurTick );
	void			CheckInFight( int64_t nCurTick );

	void			ChangeBuleName( bool bFlag );
	bool			IsBuleName();
private:
	void			OnLeaveFight();
	void			OnEnterFight();
	void			UpdateFightState();

private:
	int64_t			m_nFightTick;
	bool			m_bIsInFight;
	bool			m_IsBuleName;

	int64_t			m_nBuleNameTick;
};

#endif	//__TPOC_FIGHT_CHECKER_H__
