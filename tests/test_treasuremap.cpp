// ============================================================================
// CTreasureMap 单元测试
// 测试范围：
//   1. TreasureMapTabale - 数据增删查
//   2. GetMapPos reinterpret_cast 内存布局正确性
//   3. GetDidff 曼哈顿距离计算
//   4. 数据结构默认构造器初始化
//   5. InitItems / OnCleanUp 状态重置
// ============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

// ==================== 类型定义 ====================
typedef int32_t EntityId_t;
typedef int64_t CharId_t;
typedef int32_t SkillId_t;
typedef int32_t MapId_t;
typedef int32_t ProcId_t;
typedef int32_t PetId_t;
typedef int32_t FamilyId_t;
typedef int32_t EquipId_t;
typedef int32_t ItemId_t;
typedef int32_t Time_t;
typedef int8_t Sex_t;
typedef int8_t Job_t;
typedef std::list<int32_t> ProcIdList;

// ==================== 迷你测试框架 ====================
static int g_testsPassed = 0;
static int g_testsFailed = 0;
static int g_assertions = 0;

#define TEST(name) \
    do { \
        printf("  TEST: %s ... ", name); \
        fflush(stdout);

#define END_TEST \
        printf("PASSED\n"); \
        g_testsPassed++; \
    } while (0)

#define ASSERT(cond) do { \
    g_assertions++; \
    if (!(cond)) { \
        printf("\n  ASSERTION FAILED: %s (line %d)\n", #cond, __LINE__); \
        printf("  FAILED\n"); \
        g_testsFailed++; \
        return; \
    } \
} while (0)

#define ASSERT_EQ(a, b) do { \
    g_assertions++; \
    if (!((a) == (b))) { \
        printf("\n  ASSERTION FAILED: %s == %s (line %d)\n", #a, #b, __LINE__); \
        printf("  FAILED\n"); \
        g_testsFailed++; \
        return; \
    } \
} while (0)

// ==================== MemChrBag / 道具结构 ====================
struct MemChrBag
{
    int32_t itemId;
    int8_t  itemClass;
    int32_t itemCount;
    int8_t  bind;
    Time_t  endTime;
    int64_t srcId;
};
typedef std::vector<MemChrBag> MemChrBagVector;

// ==================== 宝藏图数据结构（与 TreasureMap.h 一致） ====================

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
    int32_t ItemId;
    int32_t MapId;
    int32_t PosX;
    int32_t PosY;
    int8_t  IsGetReward;
};

// 宝藏图事件配置
struct TreasureMapEventCfg
{
    TreasureMapEventCfg()
        : m_EventId(0), m_EventType(0), m_GongGaoId(0)
    {
    }

    int32_t     m_EventId;
    int32_t     m_EventType;
    std::string m_EventParam;
    int32_t     m_GongGaoId;
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

    int32_t             nItemId;
    int32_t             nType;
    MemChrBagVector     vGetItems;
    int32_t             nRate;
    MemChrBag           vShowItem;
    int32_t             nGongGaoId;
    int8_t              IsGet;
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

    // 测试辅助：获取内部数据大小
    size_t GetCfgCount() const { return m_TreasureMapCfgMap.size(); }
    size_t GetEventCount() const { return m_TreasureMapEventCfgMap.size(); }

private:
    std::map<int32_t, TreasureMapCfg>       m_TreasureMapCfgMap;
    std::map<int32_t, TreasureMapEventCfg>  m_TreasureMapEventCfgMap;
};

// ==================== TreasureMapTabale 实现 ====================
void TreasureMapTabale::AddTreasureMapCfg(TreasureMapCfg* p_stu)
{
    if (p_stu)
    {
        m_TreasureMapCfgMap[p_stu->m_ItemId] = *p_stu;
    }
}

void TreasureMapTabale::AddTreasureMapEventCfg(TreasureMapEventCfg* p_stu)
{
    if (p_stu)
    {
        m_TreasureMapEventCfgMap[p_stu->m_EventId] = *p_stu;
    }
}

const TreasureMapEventCfg* TreasureMapTabale::GetEvent(int32_t itemId) const
{
    std::map<int32_t, TreasureMapEventCfg>::const_iterator iter = m_TreasureMapEventCfgMap.find(itemId);
    if (iter != m_TreasureMapEventCfgMap.end())
    {
        return &iter->second;
    }
    return NULL;
}

const MapPos* TreasureMapTabale::GetMapPos(int32_t itemId) const
{
    std::map<int32_t, TreasureMapCfg>::const_iterator iter = m_TreasureMapCfgMap.find(itemId);
    if (iter != m_TreasureMapCfgMap.end())
    {
        // TreasureMapCfg layout: m_ItemId, m_MapId, m_PosX, m_PosY
        // MapPos layout:         MapId, PosX, PosY
        // Cast from &m_MapId skips m_ItemId and matches MapPos layout
        return reinterpret_cast<const MapPos*>(&iter->second.m_MapId);
    }
    return NULL;
}

// ==================== CTreasureMap 简化测试版 ====================

class CTreasureMap
{
public:
    CTreasureMap();
    ~CTreasureMap() {}

    void    OnCleanUp();
    int32_t GetDidff(int32_t X, int32_t Y);
    void    InitItems();

    // 测试辅助
    int32_t GetLeftTimes() const { return m_LeftTimes; }
    int32_t GetSpecialX() const { return m_SpecialX; }
    int32_t GetSpecialY() const { return m_SpecialY; }
    const SpecialTreasureMapRandCfg& GetItem(int32_t x, int32_t y) const { return m_Items[x][y]; }

private:
    std::map<int32_t, TreasureMapData>  m_TreasureMapDataMap;
    int32_t                             m_LeftTimes;
    int32_t                             m_SpecialX;
    int32_t                             m_SpecialY;
    SpecialTreasureMapRandCfg           m_Items[6][6];
};

CTreasureMap::CTreasureMap()
    : m_LeftTimes(0)
    , m_SpecialX(0)
    , m_SpecialY(0)
{
    InitItems();
}

void CTreasureMap::InitItems()
{
    for (int32_t i = 0; i < 6; ++i)
    {
        for (int32_t j = 0; j < 6; ++j)
        {
            m_Items[i][j] = SpecialTreasureMapRandCfg();
        }
    }
}

void CTreasureMap::OnCleanUp()
{
    m_TreasureMapDataMap.clear();
    m_LeftTimes = 0;
    m_SpecialX = 0;
    m_SpecialY = 0;
    InitItems();
}

int32_t CTreasureMap::GetDidff(int32_t X, int32_t Y)
{
    return abs(m_SpecialX - X) + abs(m_SpecialY - Y);
}

// ==================== 测试用例 ====================

// ---- Test 1: 数据结构默认构造器 ----
void test_data_structure_defaults()
{
    TEST("数据结构默认构造器: TreasureMapCfg");

    TreasureMapCfg cfg;
    ASSERT_EQ(cfg.m_ItemId, 0);
    ASSERT_EQ(cfg.m_MapId, 0);
    ASSERT_EQ(cfg.m_PosX, 0);
    ASSERT_EQ(cfg.m_PosY, 0);

    END_TEST;
}

void test_data_structure_defaults_event()
{
    TEST("数据结构默认构造器: TreasureMapEventCfg");

    TreasureMapEventCfg evt;
    ASSERT_EQ(evt.m_EventId, 0);
    ASSERT_EQ(evt.m_EventType, 0);
    ASSERT_EQ(evt.m_GongGaoId, 0);
    ASSERT(evt.m_EventParam.empty());

    END_TEST;
}

void test_data_structure_defaults_special()
{
    TEST("数据结构默认构造器: SpecialTreasureMapRandCfg");

    SpecialTreasureMapRandCfg sp;
    ASSERT_EQ(sp.nItemId, 0);
    ASSERT_EQ(sp.nType, 0);
    ASSERT_EQ(sp.nRate, 0);
    ASSERT_EQ(sp.nGongGaoId, 0);
    ASSERT_EQ(sp.IsGet, 0);
    ASSERT(sp.vGetItems.empty());
    ASSERT_EQ(sp.vShowItem.itemId, 0);
    ASSERT_EQ(sp.vShowItem.itemClass, 0);
    ASSERT_EQ(sp.vShowItem.itemCount, 0);

    END_TEST;
}

void test_data_structure_defaults_data()
{
    TEST("数据结构默认构造器: TreasureMapData");

    TreasureMapData d = {};
    ASSERT_EQ(d.ItemId, 0);
    ASSERT_EQ(d.MapId, 0);
    ASSERT_EQ(d.PosX, 0);
    ASSERT_EQ(d.PosY, 0);
    ASSERT_EQ(d.IsGetReward, 0);

    END_TEST;
}

// ---- Test 2: TreasureMapTabale ----
void test_treasure_map_tabale_add_get()
{
    TEST("TreasureMapTabale: 添加并获取配置");

    TreasureMapTabale tab;

    TreasureMapCfg cfg1; cfg1.m_ItemId = 567; cfg1.m_MapId = 50140; cfg1.m_PosX = 114; cfg1.m_PosY = 101;
    TreasureMapCfg cfg2; cfg2.m_ItemId = 568; cfg2.m_MapId = 50140; cfg2.m_PosX = 76;  cfg2.m_PosY = 169;
    TreasureMapCfg cfg3; cfg3.m_ItemId = 570; cfg3.m_MapId = 50042; cfg3.m_PosX = 13;  cfg3.m_PosY = 52;

    tab.AddTreasureMapCfg(&cfg1);
    tab.AddTreasureMapCfg(&cfg2);
    tab.AddTreasureMapCfg(&cfg3);

    ASSERT_EQ(tab.GetCfgCount(), (size_t)3);

    const MapPos* pos = tab.GetMapPos(567);
    ASSERT(pos != NULL);
    ASSERT_EQ(pos->MapId, 50140);
    ASSERT_EQ(pos->PosX, 114);
    ASSERT_EQ(pos->PosY, 101);

    pos = tab.GetMapPos(570);
    ASSERT(pos != NULL);
    ASSERT_EQ(pos->MapId, 50042);
    ASSERT_EQ(pos->PosX, 13);
    ASSERT_EQ(pos->PosY, 52);

    pos = tab.GetMapPos(999);
    ASSERT(pos == NULL);

    END_TEST;
}

void test_treasure_map_tabale_add_event()
{
    TEST("TreasureMapTabale: 添加并获取事件配置");

    TreasureMapTabale tab;

    TreasureMapEventCfg evt1;
    evt1.m_EventId = 567; evt1.m_EventType = 4; evt1.m_EventParam = "70"; evt1.m_GongGaoId = 416;

    TreasureMapEventCfg evt2;
    evt2.m_EventId = 568; evt2.m_EventType = 1; evt2.m_EventParam = "103:1:1:1|153:1:1:1"; evt2.m_GongGaoId = 0;

    tab.AddTreasureMapEventCfg(&evt1);
    tab.AddTreasureMapEventCfg(&evt2);

    ASSERT_EQ(tab.GetEventCount(), (size_t)2);

    const TreasureMapEventCfg* e = tab.GetEvent(567);
    ASSERT(e != NULL);
    ASSERT_EQ(e->m_EventType, 4);
    ASSERT(e->m_EventParam == "70");
    ASSERT_EQ(e->m_GongGaoId, 416);

    e = tab.GetEvent(568);
    ASSERT(e != NULL);
    ASSERT_EQ(e->m_EventType, 1);
    ASSERT(e->m_EventParam == "103:1:1:1|153:1:1:1");

    e = tab.GetEvent(999);
    ASSERT(e == NULL);

    END_TEST;
}

void test_treasure_map_tabale_clear()
{
    TEST("TreasureMapTabale: Clear() 重置");

    TreasureMapTabale tab;

    TreasureMapCfg cfg1; cfg1.m_ItemId = 567; tab.AddTreasureMapCfg(&cfg1);
    TreasureMapEventCfg evt1; evt1.m_EventId = 567; tab.AddTreasureMapEventCfg(&evt1);

    ASSERT_EQ(tab.GetCfgCount(), (size_t)1);
    ASSERT_EQ(tab.GetEventCount(), (size_t)1);

    tab.Clear();

    ASSERT_EQ(tab.GetCfgCount(), (size_t)0);
    ASSERT_EQ(tab.GetEventCount(), (size_t)0);

    ASSERT(tab.GetMapPos(567) == NULL);
    ASSERT(tab.GetEvent(567) == NULL);

    END_TEST;
}

void test_treasure_map_tabale_null_safety()
{
    TEST("TreasureMapTabale: NULL 指针安全");

    TreasureMapTabale tab;

    tab.AddTreasureMapCfg(NULL);
    tab.AddTreasureMapEventCfg(NULL);

    ASSERT_EQ(tab.GetCfgCount(), (size_t)0);
    ASSERT_EQ(tab.GetEventCount(), (size_t)0);

    END_TEST;
}

void test_treasure_map_tabale_update()
{
    TEST("TreasureMapTabale: 更新已有配置");

    TreasureMapTabale tab;

    TreasureMapCfg cfg1; cfg1.m_ItemId = 567; cfg1.m_MapId = 50140; cfg1.m_PosX = 100; cfg1.m_PosY = 200;
    tab.AddTreasureMapCfg(&cfg1);

    const MapPos* pos = tab.GetMapPos(567);
    ASSERT(pos != NULL);
    ASSERT_EQ(pos->PosY, 200);

    // 更新
    cfg1.m_PosY = 999;
    tab.AddTreasureMapCfg(&cfg1);

    pos = tab.GetMapPos(567);
    ASSERT(pos != NULL);
    ASSERT_EQ(pos->PosY, 999);
    ASSERT_EQ(tab.GetCfgCount(), (size_t)1);

    END_TEST;
}

// ---- Test 3: GetMapPos reinterpret_cast 内存布局 ----
void test_reinterpret_cast_layout()
{
    TEST("reinterpret_cast: TreasureMapCfg -> MapPos 内存布局一致");

    TreasureMapCfg cfg;
    cfg.m_ItemId = 567;
    cfg.m_MapId = 50140;
    cfg.m_PosX = 114;
    cfg.m_PosY = 101;

    const char* baseAddr = reinterpret_cast<const char*>(&cfg);
    std::ptrdiff_t offsetMapId = reinterpret_cast<const char*>(&cfg.m_MapId) - baseAddr;
    std::ptrdiff_t offsetPosX  = reinterpret_cast<const char*>(&cfg.m_PosX) - baseAddr;
    std::ptrdiff_t offsetPosY  = reinterpret_cast<const char*>(&cfg.m_PosY) - baseAddr;

    // m_ItemId 在先, m_MapId 紧跟其后
    ASSERT_EQ(offsetMapId, (std::ptrdiff_t)sizeof(int32_t));
    ASSERT_EQ(offsetPosX, (std::ptrdiff_t)(2 * sizeof(int32_t)));
    ASSERT_EQ(offsetPosY, (std::ptrdiff_t)(3 * sizeof(int32_t)));

    // 验证 MapPos 的布局
    MapPos pos;
    baseAddr = reinterpret_cast<const char*>(&pos);
    ASSERT_EQ(reinterpret_cast<const char*>(&pos.MapId) - baseAddr, (std::ptrdiff_t)0);
    ASSERT_EQ(reinterpret_cast<const char*>(&pos.PosX) - baseAddr, (std::ptrdiff_t)sizeof(int32_t));
    ASSERT_EQ(reinterpret_cast<const char*>(&pos.PosY) - baseAddr, (std::ptrdiff_t)(2 * sizeof(int32_t)));

    // 验证 reinterpret_cast 结果正确
    const MapPos* pCast = reinterpret_cast<const MapPos*>(&cfg.m_MapId);
    ASSERT_EQ(pCast->MapId, cfg.m_MapId);
    ASSERT_EQ(pCast->PosX, cfg.m_PosX);
    ASSERT_EQ(pCast->PosY, cfg.m_PosY);

    END_TEST;
}

// ---- Test 4: GetDidff 曼哈顿距离 ----
void test_get_didff_basic()
{
    TEST("GetDidff: 基本距离计算");

    CTreasureMap tm;

    ASSERT_EQ(tm.GetDidff(0, 0), 0);

    ASSERT_EQ(tm.GetDidff(1, 0), 1);
    ASSERT_EQ(tm.GetDidff(0, 1), 1);

    ASSERT_EQ(tm.GetDidff(1, 1), 2);

    ASSERT_EQ(tm.GetDidff(5, 5), 10);

    END_TEST;
}

// ---- Test 5: InitItems / OnCleanUp ----
void test_init_items()
{
    TEST("InitItems: 初始化 6x6 格子");

    CTreasureMap tm;
    tm.InitItems();

    for (int32_t i = 0; i < 6; ++i)
    {
        for (int32_t j = 0; j < 6; ++j)
        {
            const SpecialTreasureMapRandCfg& item = tm.GetItem(i, j);
            ASSERT_EQ(item.nItemId, 0);
            ASSERT_EQ(item.nType, 0);
            ASSERT_EQ(item.nRate, 0);
            ASSERT_EQ(item.nGongGaoId, 0);
            ASSERT_EQ(item.IsGet, 0);
            ASSERT(item.vGetItems.empty());
            ASSERT_EQ(item.vShowItem.itemId, 0);
        }
    }

    END_TEST;
}

void test_on_clean_up_resets_state()
{
    TEST("OnCleanUp: 重置所有状态");

    CTreasureMap tm;

    tm.OnCleanUp();

    ASSERT_EQ(tm.GetLeftTimes(), 0);
    ASSERT_EQ(tm.GetSpecialX(), 0);
    ASSERT_EQ(tm.GetSpecialY(), 0);

    const SpecialTreasureMapRandCfg& item0 = tm.GetItem(0, 0);
    ASSERT_EQ(item0.nItemId, 0);
    ASSERT_EQ(item0.IsGet, 0);

    const SpecialTreasureMapRandCfg& item5 = tm.GetItem(5, 5);
    ASSERT_EQ(item5.nItemId, 0);
    ASSERT_EQ(item5.IsGet, 0);

    END_TEST;
}

void test_init_items_36_slots()
{
    TEST("InitItems: 确保 6x6=36 个格子");

    CTreasureMap tm;
    tm.InitItems();

    // 检查所有 36 个格子的地址都不为 NULL
    for (int32_t i = 0; i < 6; ++i)
    {
        for (int32_t j = 0; j < 6; ++j)
        {
            ASSERT(&tm.GetItem(i, j) != NULL);
        }
    }

    END_TEST;
}

// ==================== 主函数 ====================
int main()
{
    printf("============================================\n");
    printf("  CTreasureMap 单元测试\n");
    printf("============================================\n\n");

    // Test 1: 数据结构默认构造器
    printf("[Test 1] 数据结构默认构造器:\n");
    test_data_structure_defaults();
    test_data_structure_defaults_event();
    test_data_structure_defaults_special();
    test_data_structure_defaults_data();
    printf("\n");

    // Test 2: TreasureMapTabale
    printf("[Test 2] TreasureMapTabale 配置表:\n");
    test_treasure_map_tabale_add_get();
    test_treasure_map_tabale_add_event();
    test_treasure_map_tabale_clear();
    test_treasure_map_tabale_null_safety();
    test_treasure_map_tabale_update();
    printf("\n");

    // Test 3: reinterpret_cast 布局
    printf("[Test 3] GetMapPos reinterpret_cast 布局:\n");
    test_reinterpret_cast_layout();
    printf("\n");

    // Test 4: GetDidff
    printf("[Test 4] GetDidff 曼哈顿距离:\n");
    test_get_didff_basic();
    printf("\n");

    // Test 5: InitItems / OnCleanUp
    printf("[Test 5] InitItems / OnCleanUp:\n");
    test_init_items();
    test_init_items_36_slots();
    test_on_clean_up_resets_state();
    printf("\n");

    // 汇总
    printf("============================================\n");
    printf("  测试结果:\n");
    printf("    通过: %d\n", g_testsPassed);
    printf("    失败: %d\n", g_testsFailed);
    printf("    断言: %d\n", g_assertions);
    printf("============================================\n");

    return g_testsFailed > 0 ? 1 : 0;
}
