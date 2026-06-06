#ifndef __CKUN_EXT_H__
#define __CKUN_EXT_H__

#include "KunData.h"
#include "CfgData.h"

class Player;

// ========== Config Data Structures ==========

// 鲲升级配置
struct KunLevelUpCfg
{
    int32_t nLevel;
    int32_t nExp;
    int32_t nCostMoney;
    int32_t nCostShengYaoBi;
    int32_t nGongGaoId;
    int32_t nTalentId;
    int32_t nTalentLevel;
    AddAttrList lAttrList;
};

// 灵珠配置
struct LingZhuCfg
{
    int32_t nId;
    int32_t nType;
    int32_t nDecExp;
    int32_t nGetGongGao;
    int32_t nLevelUpGongGao;
    int32_t nKunLingLevel;
    int32_t nCostMoney;
    int32_t nCostId;
    int32_t nCostCount;
    int32_t nNextId;
    int32_t nLevel;
    int32_t nSuitId;
    AddAttrList lAttrList;
};

// 丹田配置
struct DanTianCfg
{
    int32_t nMid;
    int32_t nRate;
    int32_t nTime;
    int32_t nId;

    static int32_t RandDanTianId(const DanTianCfg* pCfg);
    static int32_t RandHighDanTianId(const DanTianCfg* pCfg);
};

// 灵珠套装属性
struct LingZhuSuit
{
    int32_t nSuitId;
    AddAttrList lAttrList;
};

// 灵珠位置初始配置
struct LingZhuPosCfg
{
    int32_t nPos;
    int32_t nFirstId;
    int32_t nCostId;
    int32_t nCostCount;
    int32_t nMoney;
};

// 灵珠全满技能配置
struct LingZhuSkill
{
    int32_t nLevel;
    int32_t TalentId;
    int32_t TalentLevel;
};

// ========== KunLingTable ==========

class KunLingTable
{
public:
    KunLingTable() {}
    ~KunLingTable() {}

    void AddKunLevelUpCfg(const KunLevelUpCfg* pCfg)
    {
        KunLevelUpCfg cfg = *pCfg;
        m_mKunLevelUpCfg[pCfg->nLevel] = cfg;
    }

    const KunLevelUpCfg* GetKunLevelUpCfg(int32_t nLevel) const
    {
        std::map<int32_t, KunLevelUpCfg>::const_iterator it = m_mKunLevelUpCfg.find(nLevel);
        if (it != m_mKunLevelUpCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuCfg(const LingZhuCfg* pCfg)
    {
        LingZhuCfg cfg = *pCfg;
        m_mLingZhuCfg[pCfg->nId] = cfg;
    }

    const LingZhuCfg* GetLingZhuCfg(int32_t nId) const
    {
        std::map<int32_t, LingZhuCfg>::const_iterator it = m_mLingZhuCfg.find(nId);
        if (it != m_mLingZhuCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddDanTianCfg(const DanTianCfg* pCfg)
    {
        DanTianCfg cfg = *pCfg;
        m_mDanTianCfg[pCfg->nMid] = cfg;
    }

    const DanTianCfg* GetDanTianCfg(int32_t nMid) const
    {
        std::map<int32_t, DanTianCfg>::const_iterator it = m_mDanTianCfg.find(nMid);
        if (it != m_mDanTianCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuSuit(const LingZhuSuit* pCfg)
    {
        LingZhuSuit cfg = *pCfg;
        m_mLingZhuSuit[pCfg->nSuitId] = cfg;
    }

    const LingZhuSuit* GetLingZhuSuit(int32_t nSuitId) const
    {
        std::map<int32_t, LingZhuSuit>::const_iterator it = m_mLingZhuSuit.find(nSuitId);
        if (it != m_mLingZhuSuit.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuPosId(const LingZhuPosCfg* pCfg)
    {
        LingZhuPosCfg cfg = *pCfg;
        m_mLingZhuPosCfg[pCfg->nPos] = cfg;
    }

    const LingZhuPosCfg* GetLingZhuPosId(int32_t nPos) const
    {
        std::map<int32_t, LingZhuPosCfg>::const_iterator it = m_mLingZhuPosCfg.find(nPos);
        if (it != m_mLingZhuPosCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuSkill(const LingZhuSkill* pCfg)
    {
        LingZhuSkill cfg = *pCfg;
        m_mLingZhuSkill[pCfg->nLevel] = cfg;
    }

    const LingZhuSkill* GetLingZhuSkill(int32_t nLevel) const
    {
        std::map<int32_t, LingZhuSkill>::const_iterator it = m_mLingZhuSkill.find(nLevel);
        if (it != m_mLingZhuSkill.end())
        {
            return &it->second;
        }
        return NULL;
    }

private:
    std::map<int32_t, KunLevelUpCfg> m_mKunLevelUpCfg;
    std::map<int32_t, LingZhuCfg>    m_mLingZhuCfg;
    std::map<int32_t, DanTianCfg>    m_mDanTianCfg;
    std::map<int32_t, LingZhuSuit>   m_mLingZhuSuit;
    std::map<int32_t, LingZhuPosCfg> m_mLingZhuPosCfg;
    std::map<int32_t, LingZhuSkill>  m_mLingZhuSkill;
};

// ========== CKunExt Class ==========

class CKunExt : public IExtSystem
{
public:
    CKunExt();
    virtual ~CKunExt();

    // IExtSystem interface
    virtual void Init(Player* pPlayer);
    virtual void OnLoadFromDB(const PlayerDBData& dbData);
    virtual void OnSaveToDB(PlayerDBData& dbData);
    virtual void OnCleanUp();
    virtual void GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);
    virtual void OnUpdate(int64_t curTick);
    virtual void OnDaySwitch(int32_t nDiffDays);

    // Public methods
    void SendKunLingInfo();
    void SendLingZhuBagAllItem();
    void SendLingZhuBagChangeItem(Int32List& changeList);
    void SendDanTianInfo(int32_t Pos);
    void SendLingZhuPosInfo(int32_t Pos);
    bool AddLingZhuBagItem(int32_t LingZhuId, int32_t Count, ITEM_CHANGE_REASON addReason);
    int32_t GetEmptyBagCount();
    void AddExp(int32_t Exp);
    bool ReMoveLingZhuItem(int32_t LingZhuId, int32_t Count, ITEM_CHANGE_REASON addReason);
    void RemoveLingZhuItem(Int32List& pPos, ITEM_CHANGE_REASON addReason);
    bool AddDanTian(int32_t Mid);
    void AddCharAttr();
    int32_t GetLeftLianHuaTimes();
    void CheckSuit();
    void CheckAddSuitSkill();

private:
    // Protocol handlers
    int32_t OnKunLingLevelUp(Answer::NetPacket* inPacket);
    int32_t OnGetLingZhu(Answer::NetPacket* inPacket);
    int32_t OnRecoveryLingZhu(Answer::NetPacket* inPacket);
    int32_t OnFastFining(Answer::NetPacket* inPacket);
    int32_t OnLingZhuLevelUp(Answer::NetPacket* inPacket);
    int32_t OnBuyLianHuaTime(Answer::NetPacket* inPacket);
    int32_t OnKunWeiYang(Answer::NetPacket* inPacket);

private:
    Player* m_pPlayer;

    // Data
    int32_t m_nKunLevel;                    // 鲲等级
    int32_t m_nExp;                         // 鲲经验
    int32_t m_nBuyTime;                     // 购买次数
    int32_t m_nLianHuaTime;                 // 炼化次数
    int64_t m_LastUpdateTick;               // 上次更新tick

    // Arrays (using KunData.h structs)
    KunLingZhuBagItem m_LingZhuBag[MAX_LING_ZHU_BAG];  // 灵珠背包
    KunDanTianItem    m_DanTian[MAX_DAN_TIAN];          // 丹田
    int32_t           m_LingZhuPos[MAX_LING_ZHU_POS];   // 灵珠位置

    std::list<int32_t> lSuitList;           // 套装列表
};

#endif // __CKUN_EXT_H__
