#pragma once
//////////////////////////////////////////////////////////////////////////
// 宝藏图系统 (CTreasureMap)
// 包含普通宝藏图（使用后获得奖励/召唤BOSS/进入副本/扣血）
// 和特殊宝藏图（6x6 翻牌格子）
//////////////////////////////////////////////////////////////////////////

#include "Shared.h"
#include "ExtSystemBase.h"

class Player;
class CfgMonster;

// ========== 数据结构 ==========

// 宝藏图坐标（MapId + XY）
struct MapPos
{
    int32_t MapId;
    int32_t PosX;
    int32_t PosY;
};

// 宝藏图数据（运行时）
struct TreasureMapData
{
    int32_t ItemId;         // 道具ID
    int32_t MapId;          // 地图ID
    int32_t PosX;           // 位置X
    int32_t PosY;           // 位置Y
    int8_t  IsGetReward;    // 是否已领奖
};

// 宝藏图事件配置
struct TreasureMapEventCfg
{
    TreasureMapEventCfg()
        : m_EventId(0), m_EventType(0), m_GongGaoId(0)
    {
    }

    int32_t     m_EventId;
    int32_t     m_EventType;    // 1=道具 2=召唤BOSS 3=进入副本 4=扣血
    std::string m_EventParam;   // 事件参数
    int32_t     m_GongGaoId;    // 公告ID
};

// 宝藏图配置表
struct TreasureMapCfg
{
    TreasureMapCfg()
        : m_ItemId(0), m_MapId(0), m_PosX(0), m_PosY(0)
    {
    }

    int32_t m_ItemId;
    int32_t m_MapId;
    int32_t m_PosX;
    int32_t m_PosY;
};

// 特殊宝藏图随机配置
struct SpecialTreasureMapRandCfg
{
    SpecialTreasureMapRandCfg()
        : nItemId(0), nType(0), nRate(0), nGongGaoId(0), IsGet(0)
    {
        vShowItem = MemChrBag();
    }

    int32_t             nItemId;        // 道具ID
    int32_t             nType;          // 0=普通 1=特殊
    MemChrBagVector     vGetItems;      // 获得的道具
    int32_t             nRate;          // 权重
    MemChrBag           vShowItem;      // 显示的展示道具
    int32_t             nGongGaoId;     // 公告ID
    int8_t              IsGet;          // 是否已获取
};

typedef std::list<SpecialTreasureMapRandCfg> SpecialTreasureMapRandCfgList;

// 宝藏图表类
class TreasureMapTabale
{
public:
    TreasureMapTabale() {}
    ~TreasureMapTabale() {}

    void AddTreasureMapCfg(TreasureMapCfg* p_stu);
    void AddTreasureMapEventCfg(TreasureMapEventCfg* p_stu);

    const TreasureMapEventCfg* GetEvent(int32_t itemId) const;
    const MapPos* GetMapPos(int32_t itemId) const;

    void Clear()
    {
        m_TreasureMapCfgMap.clear();
        m_TreasureMapEventCfgMap.clear();
    }

private:
    std::map<int32_t, TreasureMapCfg>       m_TreasureMapCfgMap;
    std::map<int32_t, TreasureMapEventCfg>  m_TreasureMapEventCfgMap;
};

// ========== 宝藏图系统类 ==========

class CTreasureMap : public CExtSystemBase
{
public:
    CTreasureMap();
    virtual ~CTreasureMap();

    // CExtSystemBase 虚函数
    virtual void    OnCleanUp();
    virtual void    GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

    // 协议处理函数
    int32_t OnGetTreasureMapReward(Answer::NetPacket* inPacket);
    int32_t OnAskTreasureMapInfo(Answer::NetPacket* inPacket);
    int32_t OnAskSpecialTreasureMapInfo(Answer::NetPacket* inPacket);
    int32_t OnGetSpecialTreasureMapReward(Answer::NetPacket* inPacket);

    // 业务逻辑
    void    SendTreasureInfo(int32_t Id);
    int32_t GetUseMaxTime();
    void    SendSpecialTreasureInfo(int32_t nSlot, int32_t ItemId);
    void    SendGetItemInfo(int32_t X, int32_t Y);
    int32_t GetDidff(int32_t X, int32_t Y);
    void    SendEndInfo();

    // 辅助函数
    void    GetSpecialTreasureMapRandCfgList(SpecialTreasureMapRandCfgList& outList, int32_t nItemId, int32_t nType);

private:
    void InitItems();

    std::map<int32_t, TreasureMapData>  m_TreasureMapDataMap;   // 已打开的宝藏图数据 map<itemId, data>
    int32_t                             m_LeftTimes;            // 剩余领取次数
    int32_t                             m_SpecialX;             // 特殊道具X
    int32_t                             m_SpecialY;             // 特殊道具Y
    SpecialTreasureMapRandCfg           m_Items[6][6];          // 6x6 特殊宝藏格
};
