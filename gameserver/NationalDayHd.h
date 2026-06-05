//////////////////////////////////////////////////////////////////////////
// 国庆活动系统 (CNationalDayHd)
// 任务进度追踪、等级系统、奖励系统
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_NATIONAL_DAY_HD_H__
#define __TPOC_NATIONAL_DAY_HD_H__

#include "ExtSystemBase.h"
#include "DataStruct.h"

class CfgData;
struct NationalDayTaskCfg;
struct NationalDayLevelCfg;
class PlayerDBData;
#include "PDUDefine.h"
#include "ExtSystemBase.h"

class Player;

// 国庆活动任务类型
enum NATIONAL_HD_TYPE
{
    HHT_LOGIN       = 0,
    HHT_CBT         = 1,
    HHT_CHOU_JIANG  = 2,
    HHT_LUN_HUI_TA  = 3,
    HHT_COST_GOLD   = 4,
    HHT_RECHARGE    = 5,
    HHT_YJSK        = 6,
    HHT_KILL_BOSS   = 7,
};

// 参数对结构
struct Param2
{
    Param2() : nParam1(0), nParam2(0) {}
    Param2(int32_t p1, int32_t p2) : nParam1(p1), nParam2(p2) {}
    int32_t nParam1;
    int32_t nParam2;
};

class CNationalDayHd
{
friend class Player;
friend class CExtSystemMgr;
public:
    CNationalDayHd();
    ~CNationalDayHd();

    // 数据生命周期
    void OnCleanUp();
    void OnLoadFromDB( const PlayerDBData* dbData );
    void OnSaveToDB( PlayerDBData* dbData );

    // 协议处理
    void GetInterestsProtocol( ProcIdList& procList );
    int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

    // 核心接口
    void AddNationalValue( int32_t nType, int32_t ParamValue1, int32_t ParamValue2 );
    bool GetNationalExp( int32_t nType, int32_t nId );
    bool UnLockHighReward();
    bool GetSeniorReward( int32_t nLevel );
    bool GetOrdinaryReward( int32_t nLevel );
    bool BuyLevel( int32_t BuyLv );
    int32_t CanGetCount();

    // 内部接口
    void AddExp( int32_t AddExp );
    void CheckLevelUp();
    void SendLevelInfo();
    void PackHdInfo( Answer::NetPacket* packet );

    // 辅助
    void paraseNational( const std::string& pNationalInfo );
    std::string SaveNationalInfo();
    void SetPlayer( Player* pPlayer ) { m_pPlayer = pPlayer; }

private:
    Player*             m_pPlayer;
    int32_t             m_Level;
    int32_t             m_Exp;
    int32_t             m_UnLockReward;
    int32_t             m_OrdinaryReward;
    int32_t             m_SeniorReward;
    std::map<int32_t, Param2> m_NationalInfo;

    // 协议处理
    int32_t onAskNationalDayInfo( Answer::NetPacket* inPacket );
    int32_t onAskNationalDayExp( Answer::NetPacket* inPacket );
    int32_t onAskNationalDayReward( Answer::NetPacket* inPacket );
    int32_t onAskNationalDayBuyLevel( Answer::NetPacket* inPacket );
};

#endif // __TPOC_NATIONAL_DAY_HD_H__
