#ifndef __ULTIMATE_CHALLENGE_H__
#define __ULTIMATE_CHALLENGE_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"
#include "CfgData.h"

class CUltimateChallenge
    : public CActivity
{
public:
    CUltimateChallenge( const CfgActivity& cfgActivity );
    virtual ~CUltimateChallenge();

    virtual void Init();
    virtual void OnUpdate( CActivityMap* pMap );

    virtual int8_t GetState();
    virtual int32_t GetIconLeftTime();
    virtual void GetIconState( IconStateList& iconList );

    virtual Answer::NetPacket* packetActivityScore();

protected:
    virtual void reset();
    virtual int32_t canEnter( Player* player, CActivityMap* pTargetMap ) const;
    virtual void addPlayer( Player* player );
    virtual void removePlayer( Player* player, bool islogout );
    virtual bool OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t Param );
    virtual void onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
    virtual void onPlayerKilled( Player* pDier, Player* pKiller );
    virtual void onPlayerRevive( Player* player, bool bSafe );

    virtual void BroadcastActivityState();
    virtual void broadcastReady();
    virtual void broadcastStart();

private:
    int8_t  m_ActState;
    int64_t m_lastUpdateTime;
    int32_t m_nRand;
    int32_t m_MonsterScore;
};

#endif
