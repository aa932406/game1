//////////////////////////////////////////////////////////////////////////
// 时装系统
// CExtSystemBase 子类，管理时装穿戴/培养/升阶/套装效果
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_SHI_ZHUANG_H__
#define __TPOC_SHI_ZHUANG_H__

#include "stdafx.h"
#include "ExtSystemBase.h"
#include "CfgData.h"

// 时装信息结构体
struct ShiZhuangInfo
{
    ShiZhuangInfo()
    {
        CleanUp();
    }

    ShiZhuangInfo(const ShiZhuangInfo& other)
    {
        m_nWear = other.m_nWear;
        m_nLevel = other.m_nLevel;
        m_nExp = other.m_nExp;
        m_lActive = other.m_lActive;
    }

    ShiZhuangInfo& operator=(const ShiZhuangInfo& other)
    {
        if (this != &other)
        {
            m_nWear = other.m_nWear;
            m_nLevel = other.m_nLevel;
            m_nExp = other.m_nExp;
            m_lActive = other.m_lActive;
        }
        return *this;
    }

    void CleanUp()
    {
        m_nWear = 0;
        m_nLevel = 0;
        m_nExp = 0;
        m_lActive.clear();
    }

    void ParesActiveString(const std::string& strActive);
    std::string GetActiveString() const;
    void AddTime(int32_t nId, int32_t nTime);
    bool IsForever(int32_t nId) const;
    bool IsActive(int32_t nId) const;

    int32_t m_nWear;                      // 当前穿戴ID
    int32_t m_nLevel;                     // 当前等级
    int32_t m_nExp;                       // 当前经验
    std::map<int32_t, int32_t> m_lActive; // id -> expire_time (0=永久)
};

// 运行时套装信息
struct SuitInfo
{
    SuitInfo() : nCount(0), nLevel(0), nEffectLevel(0) {}
    int32_t nCount;
    int32_t nLevel;
    int32_t nEffectLevel;
};

class CExtCharShiZhuang : public CExtSystemBase
{
public:
    CExtCharShiZhuang();
    virtual ~CExtCharShiZhuang();

    // CExtSystemBase 接口
    virtual void OnCleanUp();
    virtual void OnLoadFromDB(const PlayerDBData* dbData);
    virtual void OnSaveToDB(PlayerDBData* dbData);
    virtual void OnUpdate(int64_t curTick);
    virtual void GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

    // CM 协议处理
    int32_t onRequestInfo(Answer::NetPacket* inPacket);
    int32_t onPeiYang(Answer::NetPacket* inPacket);
    int32_t onWear(Answer::NetPacket* inPacket);
    int32_t onLevelUp(Answer::NetPacket* inPacket);

    // 发送函数
    void sendShiZhuangPeiYangResult(int8_t nType, int32_t nExp, int8_t nCrit);
    void PackShiZhuangInfo(Answer::NetPacket* packet);
    void appendShiZhuangInfo(int8_t nType, Answer::NetPacket* packet);
    void sendShiZhuangInfo(int8_t nType);
    void SendShiZhuangInfo();

    // 查询函数
    int32_t GetWearId(int8_t nType) const;
    int32_t GetShiZhuangLevel(int8_t nType) const;
    int32_t GetEffectId() const { return m_EffectId; }

    // 属性计算
    void AddPlayerAttr();

    // 功能函数
    void addShiZhuangExp(int8_t nType, int32_t nAddExp);
    bool ActiveWithItem(int32_t nId, int32_t nAddTime);
    void wear(int8_t nType, int32_t nId);
    bool IsForever(int8_t nType, int32_t nId) const;
    int32_t GetNewShiZhuangLevel(int32_t nId) const;
    void CheckSuitInfo();
    void CheckSuitEffect();

private:
    ShiZhuangInfo m_vShiZhuang[3];           // 3种类型(0=武器,1=衣服,2=翅膀)
    int64_t m_LastUpdateTick;                // 最后更新tick
    std::map<int32_t, int32_t> m_ShiZhuangLevel; // id -> level
    std::map<int32_t, SuitInfo> m_SuitInfoMap;    // suitId -> SuitInfo
    int32_t m_EffectId;                      // 当前特效ID
};

#endif // __TPOC_SHI_ZHUANG_H__
