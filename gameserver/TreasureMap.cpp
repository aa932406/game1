#include "stdafx.h"
#include "TreasureMap.h"
#include "Player.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "GameService.h"
#include "CfgData.h"
#include "Monster.h"
#include "Map.h"
#include "MapManager.h"
#include "PoolManager.h"
#include "Vip.h"
#include "HuoYueDu.h"
#include "NationalDayHd.h"
#include "DBService.h"

using namespace Answer;

// ========== TreasureMapTabale 实现 ==========

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

// ========== CTreasureMap 实现 ==========

CTreasureMap::CTreasureMap()
    : m_LeftTimes(0)
    , m_SpecialX(0)
    , m_SpecialY(0)
{
    InitItems();
}

CTreasureMap::~CTreasureMap()
{
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

void CTreasureMap::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(CM_ASK_TREASURE_MAP_INFO);
    procList.push_back(CM_GET_TREASURE_MAP_REWARD);
    procList.push_back(CM_ASK_SPECIAL_TREASURE_MAP_INFO);
    procList.push_back(CM_GET_SPECIAL_TREASURE_MAP_REWARD);
}

int32_t CTreasureMap::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (!inPacket)
    {
        return 10002;
    }

    switch (nProcId)
    {
    case CM_ASK_TREASURE_MAP_INFO:
        return OnAskTreasureMapInfo(inPacket);
    case CM_GET_TREASURE_MAP_REWARD:
        return OnGetTreasureMapReward(inPacket);
    case CM_ASK_SPECIAL_TREASURE_MAP_INFO:
        return OnAskSpecialTreasureMapInfo(inPacket);
    case CM_GET_SPECIAL_TREASURE_MAP_REWARD:
        return OnGetSpecialTreasureMapReward(inPacket);
    default:
        return 0;
    }
}

int32_t CTreasureMap::OnGetTreasureMapReward(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    Player* player = m_pPlayer;

    int32_t nRecord = player->getRecord(7006);
    if (nRecord > GetUseMaxTime())
        return 2;

    int32_t nSlot = inPacket->readInt32();
    CExtCharBag& pBag = player->GetBag();
    MemChrBag bagSlot = pBag.GetSlotData(nSlot);

    CfgItem* pItem = CFG_DATA.getItem(bagSlot.itemId);
    if (!pItem)
        return 2;

    std::map<int32_t, TreasureMapData>::iterator it = m_TreasureMapDataMap.find(bagSlot.itemId);
    if (it == m_TreasureMapDataMap.end())
        return 2;

    if (it->second.IsGetReward == 1)
        return 2;

    int32_t nMapId = it->second.MapId;
    if (nMapId != player->getMapId())
        return 2;

    int32_t itemId = bagSlot.itemId;
    const TreasureMapEventCfg* pEvent = CFG_DATA.GetTreasureMapTabale().GetEvent(itemId);
    if (!pEvent)
        return 2;

    int32_t eventType = pEvent->m_EventType;

    if (eventType == 1)
    {
        // 道具奖励
        MemChrBagVector ItemVt = CItemHelper::parseItemVectorString(pEvent->m_EventParam);
        if (!ItemVt.empty())
        {
            CExtCharBag& bag = player->GetBag();
            if (!bag.AddItem(ItemVt, (ITEM_ADD_REASON)IACR_CANG_BAO_TU_GET))
            {
                return 2;
            }
        }
    }
    else if (eventType == 2)
    {
        // 召唤BOSS - 消耗道具后在玩家位置召唤怪物
        int32_t nMonsterId = atoi(pEvent->m_EventParam.c_str());
        if (nMonsterId > 0)
        {
            const CfgMonster* pCfgMon = CFG_DATA.getMonster(nMonsterId);
            if (pCfgMon)
            {
                Monster* pMonster = POOL_MANAGER.pop<Monster>();
                if (pMonster)
                {
                    CfgMapMonster MapMonster = {};
                    MapMonster.mapid = player->getMapId();
                    MapMonster.monsterid = nMonsterId;
                    MapMonster.x = player->getCurrentTile().x;
                    MapMonster.y = player->getCurrentTile().y;
                    pMonster->init(*pCfgMon, MapMonster, NULL);
                    Map* pMap = MAP_MANAGER.GetMap(player->getMapId());
                    if (pMap)
                        pMap->addMonster(pMonster, MapMonster.x, MapMonster.y);
                }
            }
        }
    }
    else if (eventType == 3)
    {
        // 进入副本
        int32_t nDungeonId = atoi(pEvent->m_EventParam.c_str());
        if (Player::enterDungeon(player, nDungeonId, 0, 0, 0, 0, 0, 0) != 0)
            return 2;
    }
    else if (eventType == 4)
    {
        // 扣血
        int32_t nSubHpRate = atoi(pEvent->m_EventParam.c_str());
        int32_t nMaxHp = player->GetMaxHP();
        int32_t nSubHpValue = nSubHpRate * nMaxHp / 100;
        player->AddHP(-nSubHpValue);
    }
    else
    {
        return 2;
    }

    // 消耗道具
    --bagSlot.itemCount;
    pBag.SetSlotData(nSlot, bagSlot, ICR_CANG_BAO_TU, 0);

    // 标记已领取
    it->second.IsGetReward = 1;

    // 公告
    if (pEvent->m_GongGaoId > 0)
    {
        NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pEvent->m_GongGaoId);
            packet->writeInt64(player->getCid());
            packet->writeUTF8(player->getName());
            packet->writeInt32(player->getMapId());
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(packet);
        }
    }

    // 国庆活动计数
    player->m_CNationalDayHd.AddNationalValue(HHT_CBT, 1, 0);

    // 记录使用次数
    int32_t record = player->getRecord(7006);
    player->updateRecord(7006, record + 1);

    // 活跃度
    player->GetPlayerHuoYueDu().AddHuoYueDuRecord(9);

    return 0;
}

int32_t CTreasureMap::OnAskTreasureMapInfo(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    int32_t nSlot = inPacket->readInt32();
    CExtCharBag& pBag = m_pPlayer->GetBag();
    MemChrBag bagSlot = pBag.GetSlotData(nSlot);

    std::map<int32_t, TreasureMapData>::iterator it = m_TreasureMapDataMap.find(bagSlot.itemId);
    std::map<int32_t, TreasureMapData>::iterator endIt = m_TreasureMapDataMap.end();

    if (it == endIt || it->second.IsGetReward)
    {
        // 首次打开该宝藏图，生成数据
        int32_t itemId = bagSlot.itemId;
        const MapPos* pCfg = CFG_DATA.GetTreasureMapTabale().GetMapPos(itemId);
        if (!pCfg)
            return 2;

        TreasureMapData stu = {};
        stu.ItemId = bagSlot.itemId;
        stu.MapId = pCfg->MapId;
        stu.PosX = pCfg->PosX;
        stu.PosY = pCfg->PosY;
        stu.IsGetReward = 0;

        m_TreasureMapDataMap[bagSlot.itemId] = stu;
    }

    SendTreasureInfo(bagSlot.itemId);
    return 0;
}

void CTreasureMap::SendTreasureInfo(int32_t Id)
{
    if (!m_pPlayer)
        return;

    std::map<int32_t, TreasureMapData>::iterator it = m_TreasureMapDataMap.find(Id);
    if (it == m_TreasureMapDataMap.end())
        return;

    NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2F52);
    if (!packet)
        return;

    packet->writeInt32(it->second.ItemId);
    packet->writeInt32(it->second.MapId);
    packet->writeInt32(it->second.PosX);
    packet->writeInt32(it->second.PosY);
    packet->setSize(packet->getWOffset());

    GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CTreasureMap::GetUseMaxTime()
{
    if (!m_pPlayer)
        return 0;

    // 基础次数 + VIP额外次数
    int32_t nVipLevel = m_pPlayer->GetPlayerVip().GetVipLevel();
    return 10 + nVipLevel;
}

int32_t CTreasureMap::OnAskSpecialTreasureMapInfo(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    int32_t nSlot = inPacket->readInt32();
    int32_t nItemId = inPacket->readInt32();

    CExtCharBag& pBag = m_pPlayer->GetBag();
    MemChrBag bagSlot = pBag.GetSlotData(nSlot);

    if (nItemId <= 0 || bagSlot.itemId != nItemId || bagSlot.itemClass != 1)
        return 2;

    // 如果次数=3 且道具ID匹配，说明已经生成过了，直接重发信息
    if (m_LeftTimes == 3 && m_Items[0][0].nItemId == nItemId)
    {
        SendSpecialTreasureInfo(nSlot, nItemId);
        return 0;
    }

    // 重置所有格子
    InitItems();

    // 生成普通格（6x6 = 36格）
    // 配置表解析完成后可通过 GetSpecialTreasureMapRandCfgList 启用随机逻辑
    m_SpecialX = RANDOM.generate(0, 5);
    m_SpecialY = RANDOM.generate(0, 5);

    m_LeftTimes = 3;
    SendSpecialTreasureInfo(nSlot, nItemId);
    return 0;
}

void CTreasureMap::SendSpecialTreasureInfo(int32_t nSlot, int32_t ItemId)
{
    if (!m_pPlayer)
        return;

    NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CEF);
    if (!packet)
        return;

    packet->writeInt32(m_LeftTimes);
    packet->writeInt32(nSlot);
    packet->writeInt32(ItemId);
    packet->setSize(packet->getWOffset());

    GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CTreasureMap::OnGetSpecialTreasureMapReward(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    int32_t nSlot = inPacket->readInt32();
    int32_t nItemId = inPacket->readInt32();
    int32_t X = inPacket->readInt32();
    int32_t Y = inPacket->readInt32();

    CExtCharBag& pBag = m_pPlayer->GetBag();
    MemChrBag bagSlot = pBag.GetSlotData(nSlot);

    // 验证次数
    if (m_LeftTimes == 3 && (bagSlot.itemId != nItemId || bagSlot.itemClass != 1))
        return 2;

    // 验证坐标
    if ((uint32_t)X > 5 || (uint32_t)Y >= 6)
        return 2;

    // 验证是否已领取
    if (m_Items[X][Y].IsGet > 0)
        return 2;

    // 验证道具ID
    if (m_Items[X][Y].nItemId != nItemId)
        return 2;

    // 验证剩余次数
    if (m_LeftTimes <= 0)
        return 2;

    Player* player = m_pPlayer;

    // 首次点击扣除宝藏图道具
    if (m_LeftTimes == 3)
    {
        --bagSlot.itemCount;
        pBag.SetSlotData(nSlot, bagSlot, IDCR_SPECIAL_TREASURE_MAP, 0);
    }

    // 发放奖励
    if (!pBag.AddItem(m_Items[X][Y].vGetItems, (ITEM_ADD_REASON)IACR_CANG_BAO_TU_GET))
    {
        // 背包满时发邮件
        DB_SERVICE.OnSendSysMail(player->getCid(), 1, m_Items[X][Y].vGetItems, "");
    }

    // 扣减次数
    --m_LeftTimes;
    m_Items[X][Y].IsGet = 1;

    if (m_LeftTimes <= 0)
    {
        SendEndInfo();
    }

    SendGetItemInfo(X, Y);

    // 公告
    if (m_Items[X][Y].nGongGaoId > 0)
    {
        NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(m_Items[X][Y].nGongGaoId);
            packet->writeInt64(player->getCid());
            packet->writeUTF8(player->getName());
            packet->writeInt32(m_Items[X][Y].vShowItem.itemId);
            packet->writeInt8(m_Items[X][Y].vShowItem.itemClass);
            packet->writeInt32(m_Items[X][Y].vShowItem.itemCount);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(packet);
        }
    }

    return 0;
}

void CTreasureMap::SendGetItemInfo(int32_t X, int32_t Y)
{
    if (!m_pPlayer)
        return;

    if ((uint32_t)X > 5 || (uint32_t)Y > 5)
        return;

    NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CF0);
    if (!packet)
        return;

    packet->writeInt32(m_LeftTimes);
    if (m_SpecialX == X && m_SpecialY == Y)
        packet->writeInt32(1);
    else
        packet->writeInt32(0);

    packet->writeInt32(X);
    packet->writeInt32(Y);

    packet->writeInt32(m_Items[X][Y].vShowItem.itemId);
    packet->writeInt8(m_Items[X][Y].vShowItem.itemClass);
    packet->writeInt32(m_Items[X][Y].vShowItem.itemCount);

    // 已领取奖励列表
    int32_t nSize = m_Items[X][Y].vGetItems.size();
    packet->writeInt32(nSize);
    for (MemChrBagVector::iterator it = m_Items[X][Y].vGetItems.begin();
        it != m_Items[X][Y].vGetItems.end(); ++it)
    {
        packet->writeInt32(it->itemId);
        packet->writeInt8(it->itemClass);
        packet->writeInt32(it->itemCount);
    }

    // 距离
    int32_t didff = GetDidff(X, Y);
    packet->writeInt32(didff);
    packet->setSize(packet->getWOffset());

    GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CTreasureMap::GetDidff(int32_t X, int32_t Y)
{
    return abs(m_SpecialX - X) + abs(m_SpecialY - Y);
}

void CTreasureMap::SendEndInfo()
{
    if (!m_pPlayer)
        return;

    NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CF2);
    if (!packet)
        return;

    packet->writeInt32(m_SpecialX);
    packet->writeInt32(m_SpecialY);

    packet->writeInt32(m_Items[m_SpecialX][m_SpecialY].vShowItem.itemId);
    packet->writeInt8(m_Items[m_SpecialX][m_SpecialY].vShowItem.itemClass);
    packet->writeInt32(m_Items[m_SpecialX][m_SpecialY].vShowItem.itemCount);

    int32_t nSize = m_Items[m_SpecialX][m_SpecialY].vGetItems.size();
    packet->writeInt32(nSize);
    for (MemChrBagVector::iterator it = m_Items[m_SpecialX][m_SpecialY].vGetItems.begin();
        it != m_Items[m_SpecialX][m_SpecialY].vGetItems.end(); ++it)
    {
        packet->writeInt32(it->itemId);
        packet->writeInt8(it->itemClass);
        packet->writeInt32(it->itemCount);
    }
    packet->setSize(packet->getWOffset());

    GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

// ========== 辅助函数：获取特殊宝藏图随机配置列表 ==========

void CTreasureMap::GetSpecialTreasureMapRandCfgList(SpecialTreasureMapRandCfgList& outList, int32_t nItemId, int32_t nType)
{
    // 配置表解析完成后从 CFG_DATA.GetSpecialTreasureMapRandCfgList() 读取
    // const SpecialTreasureMapRandCfgList& allList = CFG_DATA.GetSpecialTreasureMapRandCfgList();
    // 按类型过滤
    // for (SpecialTreasureMapRandCfgList::const_iterator it = allList.begin(); it != allList.end(); ++it)
    // {
    //     if (it->nType == nType && it->nItemId > 0)
    //     {
    //         outList.push_back(*it);
    //     }
    // }
}
