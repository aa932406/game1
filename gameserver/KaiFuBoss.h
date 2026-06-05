#ifndef __TPOC_KAI_FU_BOSS_H__
#define __TPOC_KAI_FU_BOSS_H__

#include "stdafx.h"
#include "Activity.h"

class MonsterActivity;

// 开服Boss广播ID
#define BCI_KF_BOSS_READY      470     // 活动准备
#define BCI_KF_BOSS_START      471     // 活动开始
#define BCI_KF_BOSS_END_NORMAL 472     // 活动结束 (正常)
#define BCI_KF_BOSS_END_KILLED 473     // 活动结束 (Boss被击杀)

class CKaiFuBoss : public CActivity
{
public:
    CKaiFuBoss( const CfgActivity& cfgActivity );
    virtual ~CKaiFuBoss();

    virtual void    reset();
    virtual bool    checkData();
    virtual bool    checkWeek();
    virtual int32_t getNextStartTime();

    virtual void    broadcastReady();
    virtual void    broadcastStart();
    virtual void    broadcastTimeEnd();

    virtual void    sendPlayerScore( Player* player );

    virtual void    onMonsterAdd( MonsterActivity* pMonster );

protected:
    virtual void    onTimeEnd();

private:
    bool    isSpecialDay( int32_t nStartDays ) const;

    MonsterActivity*    m_Boss;
};

#endif // __TPOC_KAI_FU_BOSS_H__
