#ifndef __C_DA_TING_REWARD_H__
#define __C_DA_TING_REWARD_H__

#include "Shared.h"
#include "../share/DataStruct.h"
#include "ExtSystemInterface.h"

// ===== 平台答题配置结构 =====

// 平台答题奖励配置（DaTing.txt）
struct PlatformDaTing
{
    PlatformDaTing() : nId(0), nType(0), nSlot(0), nParam(0), nIcon(0), nParam2(0) {}
    std::string     Platform;
    int32_t         nId;
    int32_t         nType;
    int32_t         nSlot;
    int32_t         nParam;
    MemChrBagVector vItems;
    int32_t         nIcon;
    int32_t         nParam2;
};

typedef std::map<std::pair<std::string, int32_t>, PlatformDaTing> PlatformDaTingMap;

// 平台VIP奖励配置（OutLinkVip.txt）
struct PlatformVip
{
    PlatformVip() : nId(0), nNeedVipLevel(0), nIcon(0) {}
    std::string     sPlatform;
    int32_t         nId;
    int32_t         nNeedVipLevel;
    MemChrBagVector vItem;
    int32_t         nIcon;
};

typedef std::map<std::pair<std::string, int32_t>, PlatformVip> PlatformVipMap;

// 平台奖励配置（Reward.txt）
struct PlatformRewardCfg
{
    PlatformRewardCfg() : nId(0), nIcon(0), nIsAllShow(0) {}
    int32_t         nId;
    MemChrBagVector vItem;
    int32_t         nIcon;
    std::string     sPlatform;
    int32_t         nIsAllShow;
};

typedef std::map<std::pair<std::string, int32_t>, PlatformRewardCfg> PlatformRewardCfgMap;

// 微端答题奖励配置（WeiDuanDaTing.txt）
struct MiniClientCfg
{
    MiniClientCfg() : nId(0), nType(0), nSlot(0), nParam(0), nIcon(0), nParam2(0) {}
    std::string     Platform;
    int32_t         nId;
    int32_t         nType;
    int32_t         nSlot;
    int32_t         nParam;
    MemChrBagVector vItems;
    int32_t         nIcon;
    int32_t         nParam2;
};

typedef std::map<std::pair<std::string, int32_t>, MiniClientCfg> MiniClientCfgMap;

// ===== CDaTingReward 类 =====
class CDaTingReward : public IExtSystem
{
public:
    CDaTingReward() { OnCleanUp(); }
    virtual ~CDaTingReward() {}

    // IExtSystem 接口
    virtual const char*     GetName() const { return "CDaTingReward"; }
    virtual void            OnCleanUp();
    virtual void            OnLoadFromDB(const PlayerDBData& dbData);
    virtual void            OnSaveToDB(PlayerDBData& dbData);
    virtual void            OnDaySwitch(int32_t nDiffDays);
    virtual void            OnUpdate(int64_t curTick);
    virtual void            GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t         DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

    // 平台答题
    bool    HaveDaTingReward() const;
    void    SendDaTingInfo();
    void    GetDaTingIconState(IconStateList& IconList);
    void    SendDaTingIcon();
    bool    NeedDaTing() const;
    int32_t HaveDaTingLeftGift() const;

    // 平台VIP
    void    SendPlatformVipInfo();
    void    GetPlatformVipIconState(IconStateList& IconList);
    void    SendPlatformVipIcon();
    int32_t HavePlatformVipLeftGift() const;
    bool    HavePlatformVipReward() const;
    int32_t GetPlatformVipLevel() const;

    // 平台奖励
    void    GetPlatformRewardIconState(IconStateList& IconList);
    void    SendPlatformRewardIcon(int32_t nId);

    // 微端
    void    GetMiniClientIconState(IconStateList& IconList);
    void    SendMiniClientIcon();
    void    SendMiniClientInfo();
    int32_t HaveMiniClientLeftGift() const;
    bool    HaveMiniClientReward() const;

private:
    // 协议处理
    int32_t onRequestDaTingInfo(Answer::NetPacket* inPacket);
    int32_t onGetDaTingReward(Answer::NetPacket* inPacket);
    int32_t onFromDaTing(Answer::NetPacket* inPacket);
    int32_t onRequestPlatformVipInfo(Answer::NetPacket* inPacket);
    int32_t onGetPlatformVipReward(Answer::NetPacket* inPacket);
    int32_t onGetPlatformReward(Answer::NetPacket* inPacket);
    int32_t onGetMiniClientReward(Answer::NetPacket* inPacket);
    int32_t onRequestMiniClientInfo(Answer::NetPacket* inPacket);

    int8_t  m_IsDaTingLogin;

    Player* m_pPlayer;
};

#endif // __C_DA_TING_REWARD_H__
