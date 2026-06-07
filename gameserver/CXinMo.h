#ifndef __C_XIN_MO_H__
#define __C_XIN_MO_H__

#include "Shared.h"
#include "../share/DataStruct.h"
#include "CfgData.h"

class Player;

// ===== 心魔配置结构 =====

// 心魔等级配置（XinMoLevel.txt）
// INT,INT,INT,INT,INT,STRING,INT,STRING,STRING
struct XinMoCfg
{
    XinMoCfg()
        : nLevel(0), nCostMoney(0), nCostShenYaoBi(0), nCostExp(0)
        , nNeedQiQingLevel(0), nGongGaoId(0)
    {}

    int32_t     nLevel;
    int32_t     nCostMoney;
    int32_t     nCostShenYaoBi;
    int32_t     nCostExp;
    int32_t     nNeedQiQingLevel;
    AddAttrList lAttr;
    int32_t     nGongGaoId;
    AddAttrList lAddAttr;
};

// 七情激活配置（XinMoQiQing.txt）
struct QiQingCfg
{
    QiQingCfg()
        : nId(0), nGongGaoId(0)
    {}

    int32_t         nId;
    ItemDataList    lCostItems;     // parsed from NeedRes string
    AddAttrList     lAttr;          // parsed from Attr string
    int32_t         nGongGaoId;
    AddAttrList     lAddAttr;       // parsed from AddAttr string
};

// 心魔七情升级配置（无独立表，使用级别配置）
struct XinMoQiQingLevelUpCfg
{
    XinMoQiQingLevelUpCfg()
        : nType(0), nLevel(0), nNeedLastTypeLevel(0), nGongGaoId(0)
    {}

    int32_t         nType;
    int32_t         nLevel;
    int32_t         nNeedLastTypeLevel;
    ItemDataList    lCostList;
    AddAttrList     lAttr;
    int32_t         nGongGaoId;
};

// 心情奖励配置（XinQingReward.txt）
struct XinQingReward
{
    XinQingReward()
        : nFlagCount(0), nGongGaoId(0)
    {}

    int32_t         nFlagCount;     // Mount 旗数
    MemChrBagVector Items;          // Reward
    int32_t         nGongGaoId;
};

// 心情概率配置（XinQing.txt）
struct XinQingRate
{
    XinQingRate()
        : nFlagCount(0), nSpecialMount(0), nRate(0)
    {}

    int32_t nFlagCount;
    int32_t nSpecialMount;
    int32_t nRate;
};

// 装备进化配置（XinMoJingHua.txt）
struct EquipJinHua
{
    EquipJinHua()
        : nEquipId(0)
    {}

    int32_t         nEquipId;       // Id
    ItemDataList    CostItems;      // NeedRes
    int32_t         nParamRate;     // parsed from Attr field (first number)
};

// ===== XinMoTable 配置表 =====
class XinMoTable
{
public:
    XinMoTable() {}
    ~XinMoTable() {}

    void AddXinMoCfg(const XinMoCfg& cfg) { m_mXinMoCfg[cfg.nLevel] = cfg; }
    void AddQiQingCfg(const QiQingCfg& cfg) { m_mQiQingCfg[cfg.nId] = cfg; }
    void AddQiQingLevelUpCfg(const XinMoQiQingLevelUpCfg& cfg)
    {
        m_mQiQingLevelUpCfg[std::make_pair(cfg.nType, cfg.nLevel)] = cfg;
    }
    void AddXinQingReward(const XinQingReward& cfg) { m_mXinQingReward[cfg.nFlagCount] = cfg; }
    void AddXinQingRate(const XinQingRate& cfg) { m_lstXinQingRate.push_back(cfg); }
    void AddEquipJinHua(const EquipJinHua& cfg) { m_mEquipJinHua[cfg.nEquipId] = cfg; }

    const XinMoCfg* GetXingMoCfg(int32_t nLevel) const
    {
        std::map<int32_t, XinMoCfg>::const_iterator it = m_mXinMoCfg.find(nLevel);
        if (it != m_mXinMoCfg.end()) return &it->second;
        return NULL;
    }

    const QiQingCfg* GetQiQingCfg(int32_t nId) const
    {
        std::map<int32_t, QiQingCfg>::const_iterator it = m_mQiQingCfg.find(nId);
        if (it != m_mQiQingCfg.end()) return &it->second;
        return NULL;
    }

    const XinMoQiQingLevelUpCfg* GetXinMoQiQingLevelUpCfg(int32_t nType, int32_t nLevel) const
    {
        std::map<std::pair<int32_t, int32_t>, XinMoQiQingLevelUpCfg>::const_iterator it =
            m_mQiQingLevelUpCfg.find(std::make_pair(nType, nLevel));
        if (it != m_mQiQingLevelUpCfg.end()) return &it->second;
        return NULL;
    }

    const XinQingReward* GetXinQingReward(int32_t nFlagCount) const
    {
        std::map<int32_t, XinQingReward>::const_iterator it = m_mXinQingReward.find(nFlagCount);
        if (it != m_mXinQingReward.end()) return &it->second;
        return NULL;
    }

    int32_t GetAppearCount(int32_t nRemainFlagCount) const;

    const EquipJinHua* GetJinHuaCfg(int32_t nEquipId) const
    {
        std::map<int32_t, EquipJinHua>::const_iterator it = m_mEquipJinHua.find(nEquipId);
        if (it != m_mEquipJinHua.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, XinMoCfg>                     m_mXinMoCfg;
    std::map<int32_t, QiQingCfg>                    m_mQiQingCfg;
    std::map<std::pair<int32_t, int32_t>, XinMoQiQingLevelUpCfg> m_mQiQingLevelUpCfg;
    std::map<int32_t, XinQingReward>                m_mXinQingReward;
    std::list<XinQingRate>                          m_lstXinQingRate;
    std::map<int32_t, EquipJinHua>                  m_mEquipJinHua;
};

// ===== CXinMo 类 =====
// XinMoDBData 定义在 share/DataStruct.h 中
class CXinMo : public IExtSystem
{
public:
    CXinMo() : m_pPlayer(NULL) { OnCleanUp(); }
    virtual ~CXinMo() {}
    void SetPlayer(Player* p) { m_pPlayer = p; }

    // IExtSystem 接口
    virtual const char*     GetName() const { return "CXinMo"; }
    virtual void            OnCleanUp();
    virtual void            OnDaySwitch(int32_t nDiffDays);
    virtual void            OnUpdate(int64_t curTick);
    virtual void            OnLoadFromDB(const PlayerDBData& dbData);
    virtual void            OnSaveToDB(PlayerDBData& dbData);
    virtual void            GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t         DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

    // 公共方法
    void    AddCharAttr();
    void    AddExp(int32_t nValue);
    int32_t GetXinMoLevel() const { return m_XinMoLevel; }
    int32_t GetActiveXinMoLevel() const { return m_XinMoActiveLevel; }
    int32_t GetFreeSlotCount() const;

    // 七情相关
    int32_t GetQiQingLevel(int32_t nType) const;
    int32_t GetLeftYaoYiYaoTimes() const;
    int32_t GetChangeXinQingTimes() const;
    int32_t GetFlagCount() const;
    bool    IsYaoYiYao() const { return (m_QiQingInfo & (1 << 1)) != 0; }
    void    SetFlag(int32_t nId);
    void    SetYaoYiYaoFlag(int32_t nCount);
    void    GetNoFlagIdList(Int32Vector& nIdVt) const;
    void    AddYaoYiYaoTimes();
    void    AddChangeXinQingTimes();

    // 心魔背包
    bool    AddItem(MemChrBagVector* pItems);
    void    GetItem(int32_t nSlot);
    void    ResetBagSlot(int32_t nSlot, int32_t nOpway);
    void    AddXinMoBagLog(const MemChrBag& item, int32_t nFlag, int32_t nOpway);
    void    CleanXinMoBag();
    void    DieDropFromXinMoBag(MemChrBagVector* pTmpVt);

    // 数据发送
    void    SendXiMoInfo();
    void    SendXinQingInfo();
    void    SendXinMoQiQingLevel(int32_t nType);
    void    SendAllItem();
    void    SendChangeItem(const std::list<int>& itemList);

private:
    // 协议处理
    int32_t OnXinMoLevel(Answer::NetPacket* inPacket);
    int32_t OnActiveXinMo(Answer::NetPacket* inPacket);
    int32_t OnJinHua(Answer::NetPacket* inPacket);
    int32_t OnGetItem(Answer::NetPacket* inPacket);
    int32_t OnTidy(Answer::NetPacket* inPacket);
    int32_t OnDec(Answer::NetPacket* inPacket);
    int32_t OnQiQingLevelUp(Answer::NetPacket* inPacket);
    int32_t OnXinQing(Answer::NetPacket* inPacket);

    // 数据库成员
    int32_t             m_Exp;
    int32_t             m_XinMoLevel;
    int32_t             m_XinMoActiveLevel;
    std::map<int,int>   m_QiQingLevel;
    int32_t             m_QiQingInfo;       // bitmask flags 0-6
    MemChrBag           m_ItemList[56];     // 心魔背包
    Player*             m_pPlayer;
};

#endif // __C_XIN_MO_H__
