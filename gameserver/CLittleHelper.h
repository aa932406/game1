#ifndef __TPOC_CLITTLE_HELPER_H__
#define __TPOC_CLITTLE_HELPER_H__

#include "Unit.h"
#include "Entity.h"
class Player;

// 小助手状态
enum LITTLE_HELPER_STATE
{
    LHS_REST     = 0,
    LHS_WORK     = 1,
};

// 小助手工作状态
enum LITTLE_HELPER_WORK_STATE
{
    LHWS_AWAY_FROM_MAP   = 0,
    LHWS_STAND           = 1,
    LHWS_FOLLOW          = 2,
    LHWS_WALK_PICK       = 3,
    LHWS_PICK            = 4,
};

class CLittleHelper : public Unit
{
public:
    CLittleHelper();
    virtual ~CLittleHelper();

    void reset();
    virtual void refresh();
    bool appendInfo( Answer::NetPacket *packet );

    void init( Player* pPlayer, int32_t nLittleHelperId, int32_t nClothes );
    void AddAttr();
    void EnterMap();
    void LeaveMap();
    void OnLogout();
    void CheckSwitchMap();
    void ChangeClothe( int32_t nClotheId );
    void ChangeLittleHelperId( int32_t nLittleHelperId, int32_t nClotheId );
    void SynsAreaAround();

    void updateState();
    void checkFarAway();
    void ResetTargetTile( int32_t tx, int32_t ty, Direction dir );
    void onStand();
    void ChangeTarget();
    void onFollow();
    void onWalkPick();
    void onPick();

    int32_t OnGetLittleHelperId() const { return m_LittleHelperId; }
    bool IsWork() const { return m_nState == LHS_WORK; }
    void OnWork() { m_nState = LHS_WORK; }
    void OnRest() { m_nState = LHS_REST; m_WorkState = LHWS_AWAY_FROM_MAP; }

    Position getFollowTile( int32_t tx, int32_t ty, Direction dir );

    // Unit pure virtual implementations
    virtual EntityId_t getUnitId() const;
    virtual CharId_t getOwner() const;
    virtual int32_t getLevel() const;
    virtual int32_t getBattle() const;
    virtual void postDamage(int32_t damage, UnitHandle launcher);

public:
    Player*         m_pPlayer;
    int32_t         m_LittleHelperId;
    int32_t         m_Clothes;
    Direction       m_nStandPlace;
    int8_t          m_nState;
    int8_t          m_WorkState;
    EntityId_t      m_TarDropId;
    int64_t         m_PickTick;
    int64_t         m_LastTick;
    int64_t         m_nLastWorkCheckTick;
};

#endif
