#ifndef __C_SUPER_TE_HUI_H__
#define __C_SUPER_TE_HUI_H__

#include "Shared.h"
#include "../share/DataStruct.h"
#include "ExtSystemBase.h"

// 超级特惠配置
struct SuperTeHuiCfg
{
    int32_t nIndex;
    int32_t nNeedVip;
    MemChrBagVector Items;
    int32_t nPrice;
    int32_t nGongGaoId;
};
typedef std::map<int32_t, SuperTeHuiCfg> SuperTeHuiCfgMap;

// 宝石阁配置（key: pair<day, index>）
struct JewelPavilionCfg
{
    int32_t nDay;
    int32_t nIndex;
    MemChrBag Item;
    int32_t nPrice;
};
typedef std::map<std::pair<int32_t, int32_t>, JewelPavilionCfg> JewelPavilionCfgMap;

// 商人配置
struct ShangRenCfg
{
    int32_t nId;
    MemChrBagVector vItem;
    int32_t nPrice;
};
typedef std::map<int32_t, ShangRenCfg> ShangRenCfgMap;

class CSuperTeHui
    : public CExtSystemBase
{
public:
    CSuperTeHui();
    ~CSuperTeHui();

    virtual void GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

    void OnDaySwitch(int32_t nDiffDays);

    // SuperTeHui (超级特惠)
    int32_t OnBuySuperTeHui(Answer::NetPacket* inPacket);
    void GetSuperTeHuiIcon(IconStateList& IconList);
    void SendSuperTeHuiIcon();
    bool IsAllGetTeHui();

    // JewelPavilion (宝石阁)
    int32_t OnGetJewelPavilionItem(Answer::NetPacket* inPacket);
    void GetJewelPavilionIcon(IconStateList& IconList);
    void SendJewelPavilionIcon();
    int32_t HaveFreeCount();
    bool IsOpenedJewelPavilion();
    bool IsAllGetPavilion();
    bool IsTimeEnd();
    void SetJewelPavilionOpen();
    int32_t GetJewelPavilionDay();

    // ShangRen (商人)
    int32_t OnBuyShengRenItem(Answer::NetPacket* inPacket);
    void GetShangRenIcon(IconStateList& IconList);
    void SendShangRenIcon();
    int32_t GetShangRenLeftTime();
    void SendLeftTime();

private:
    void GetSuperTeHuiIcon(ShowIcon& icon);
    void GetJewelPavilionIcon(ShowIcon& icon);
    void GetShangRenIcon(ShowIcon& icon);
};

#endif // __C_SUPER_TE_HUI_H__
