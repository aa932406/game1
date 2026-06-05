#ifndef __TPOC_SEVEN_DAY_TASK_H__
#define __TPOC_SEVEN_DAY_TASK_H__

#include "ExtSystemBase.h"
#include "CfgData.h"

class CSevenDayTask : public CExtSystemBase
{
public:
    CSevenDayTask( Player* pPlayer ) { m_pPlayer = pPlayer; }
    virtual ~CSevenDayTask() {}

    // CExtSystemBase interface
    virtual void    OnLoadFromDB( const PlayerDBData* dbData );
    virtual void    OnSaveToDB( PlayerDBData* dbData );
    virtual void    GetInterestsProtocol( ProcIdList& procList );
    virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );
    virtual void    OnCleanUp();
    virtual void    OnUpdate( int64_t curTick );

    // SevenDayTask specific
    void    OpenSevenDayTask();
    void    UpdateTaskState( int32_t nType, int32_t Values, bool NeedSend );
    int32_t OnAskReward( Answer::NetPacket* inPacket );
    int32_t OnAskSumReward( Answer::NetPacket* inPacket );
    void    SendTaskSTate();
    void    GetIcon( IconStateList& IconList );
    void    SendIcon();
    int32_t HaveRewardCount();

protected:
    int32_t     m_OpenTime;
    std::map<int32_t, int32_t>  m_RewardState;
    int64_t     m_LastUpdateTick;
    int32_t     m_SumRewardState;
    bool        m_bShowIcon;
    int32_t     m_DiffDay;
};

#endif  //__TPOC_SEVEN_DAY_TASK_H__
