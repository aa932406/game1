#ifndef __TPOC_CROSS_TOWER_H__
#define __TPOC_CROSS_TOWER_H__

#include "stdafx.h"
#include "Activity.h"

// 跨服塔配置
// CrossTowerCfg is defined as CfgCrossTower in CfgData.h
// This typedef provides the old name for compatibility
typedef CfgCrossTower CrossTowerCfg;

class CCrossTower : public CActivity
{
public:
    CCrossTower( const CfgActivity& cfgActivity );
    virtual ~CCrossTower();

    virtual void Init();
    virtual void OnUpdate( CActivityMap* pMap );

    virtual void        SendPlayerActivityInfo( Player* player );
    virtual void        SendPlayerActivityScore( Player* player, int32_t nLeftTime );
    virtual Position    GetRandBornPos( Player* player );
    virtual int32_t     GetRevive( Player* player );

    void    SetWinnerInfo( CharId_t nWinnerId, const std::string& sName );
    void    SetBattle( int32_t nBattle ) { m_nBattle = nBattle; }
    int32_t GetBattle() const { return m_nBattle; }

protected:
    virtual void    reset();
    virtual void    addPlayer( Player* player );
    virtual void    removePlayer( Player* player, bool islogout );
    virtual int32_t canEnter( Player* player, CActivityMap* pTargetMap ) const;
    virtual void    onTimeEnd();

private:
    struct PlayerScore
    {
        PlayerScore()
        {
            nCharId     = 0;
            nConnId     = 0;
            nScore      = 0;
            nScoreTime  = 0;
            nCurMapId   = 0;
            bInActivity = 0;
        }
        CharId_t    nCharId;
        int8_t      nConnId;
        int32_t     nScore;
        int32_t     nScoreTime;
        int32_t     nCurMapId;
        int32_t     bInActivity;
    };

    void    addRewards();
    void    addPlayerScore( Player* player, int32_t nScore );
    int32_t callAddScore( int32_t nMaxPlayer, int32_t nMaxScore, int32_t nMinScore, int32_t nCurPlayer, int32_t nFloor );
    void    checkWin( bool bForce );
    Answer::NetPacket* packetActivityMapInfo( CActivityMap* pMap );
    Answer::NetPacket* packetActivityScore();

    typedef std::map<CharId_t, PlayerScore> PlayerScoreMap;
    typedef std::set<int32_t>               NeedSysMapSet;

    PlayerScoreMap  m_mPlayerScore;
    NeedSysMapSet   m_NeedSysMap;

    // 胜者信息
    CharId_t        m_nWinerId;
    std::string     m_sWinerName;
    CharId_t        m_nNewWinerId;
    std::string     m_sNewWinerName;

    int32_t         m_nBattle;
    int8_t          m_nConnId;

    // 怪物指针（用于设置胜者家族名）
    Monster*        m_pMonster;

    // 状态标志
    int32_t         m_nNeedChangeMap;
    int32_t         m_nNeedAddScore;
    int32_t         m_nLastAddScoreTime;
    int32_t         m_nLastUpdateTime;
    int32_t         m_nStateTime;
};

#endif // __TPOC_CROSS_TOWER_H__
