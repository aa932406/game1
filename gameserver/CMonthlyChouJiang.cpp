#include "stdafx.h"
#include "CMonthlyChouJiang.h"
#include "GameService.h"
#include "ItemHelper.h"
#include "Player.h"
#include "Bag.h"
#include "Timer.h"
#include "FunctionOpen.h"

using namespace Answer;

CMonthlyChouJiang::CMonthlyChouJiang()
    : m_Score(0), m_AllScore(0)
{
}

CMonthlyChouJiang::~CMonthlyChouJiang()
{
}

void CMonthlyChouJiang::OnLoadFromDB(const PlayerDBData& dbData)
{
    m_Score = dbData.m_CMonthlyChouJiangData.m_Score;
    m_AllScore = dbData.m_CMonthlyChouJiangData.m_AllScore;
    m_GetItemList = dbData.m_CMonthlyChouJiangData.m_GetItemList;
    m_GetTimes = dbData.m_CMonthlyChouJiangData.m_GetTimes;
}

void CMonthlyChouJiang::OnSaveToDB(PlayerDBData& dbData)
{
    dbData.m_CMonthlyChouJiangData.m_Score = m_Score;
    dbData.m_CMonthlyChouJiangData.m_AllScore = m_AllScore;
    dbData.m_CMonthlyChouJiangData.m_GetItemList = m_GetItemList;
    dbData.m_CMonthlyChouJiangData.m_GetTimes = m_GetTimes;
}

void CMonthlyChouJiang::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(522);
    procList.push_back(523);
}

int32_t CMonthlyChouJiang::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    if (nProcId == 522)
        return OnAskMonthlyChouJiangInfo(inPacket);
    if (nProcId == 523)
        return OnMonthlyChouJiang(inPacket);
    return 2;
}

void CMonthlyChouJiang::OnCleanUp()
{
    m_Score = 0;
    m_AllScore = 0;
    m_GetItemList.clear();
    m_GetTimes.clear();
}

void CMonthlyChouJiang::OnDaySwitch(int32_t nDiffDays)
{
    SendIcon();
    SendMonthlyChouJiangInfo();
}

void CMonthlyChouJiang::OnMonthlySwitch()
{
    // On monthly switch - clear list and scores
    OnCleanUp();
    SendMonthlyChouJiangInfo();
    SendIcon();
}

void CMonthlyChouJiang::OnChongZhi(int32_t NewValues, int32_t OldValues)
{
    if (!m_pPlayer)
        return;

    if (CFG_DATA.getServerDiffDay(0) < 0)
        return;

    const MonthlyChouJiangTable* pTable = CFG_DATA.GetMonthlyChouJiangTable();
    if (!pTable)
        return;

    const MonthlyChouJiangCfgMap* pCfgMap = pTable->GetMonthlyChouJiangCfgMap();
    if (!pCfgMap)
        return;

    for (MonthlyChouJiangCfgMap::const_iterator it = pCfgMap->begin(); it != pCfgMap->end(); ++it)
    {
        if (it->second.nRecharges > OldValues && it->second.nRecharges <= NewValues)
        {
            int32_t SocreTimes = GetSocreTimes(it->first);
            if (SocreTimes < it->second.nGetTimes)
            {
                m_GetTimes[it->first]++;
                m_Score += it->second.nAddValues;
                m_AllScore += it->second.nAddValues;
            }
        }
    }
}

int32_t CMonthlyChouJiang::GetKaiFuMonth()
{
    if (!m_pPlayer)
        return 0;

    int32_t nKaiFuTime = CFG_DATA.getServerStartTime();
    tm Time;
    DayTime::localnow(&Time, nKaiFuTime);
    int32_t nNowTime = m_pPlayer->getNow();
    int32_t DiffMonth = DayTime::monthdiff(nKaiFuTime) + 1;

    if (nNowTime <= 1567267199)
        return 0;
    if (Time.tm_mday > 16)
        --DiffMonth;
    if (DiffMonth <= 0)
        DiffMonth = 1;
    if (DiffMonth > 12)
        return 12;
    return DiffMonth;
}

int32_t CMonthlyChouJiang::OnMonthlyChouJiang(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;

    if (m_Score <= 99)
        return 2;

    if (m_pPlayer->GetBag().GetFreeSlotCount() <= 0)
        return 2;

    int32_t KaiFuMonth = GetKaiFuMonth();
    const MonthlyChouJiangTable* pTable = CFG_DATA.GetMonthlyChouJiangTable();
    if (!pTable)
        return 2;

    RateItem Item;
    if (!pTable->RandRateItem(Item, KaiFuMonth, m_GetItemList))
        return 2;

    if (Item.nItemClass <= 0 || Item.nItemCount <= 0 || Item.nItemId <= 0)
        return 2;

    MemChrBag stu;
    memset(&stu, 0, sizeof(stu));
    stu.itemClass = (int8_t)Item.nItemClass;
    stu.itemCount = Item.nItemCount;
    stu.itemId = Item.nItemId;
    stu.bind = (int8_t)Item.nBind;

    m_pPlayer->GetBag().AddItem(&stu, IDR_MONTHLY_CHOU_JIANG);
    m_Score -= 100;

    int32_t LastId = m_GetItemList.back();
    SendMonthlyChouJiangResult(LastId);

    if (Item.nGongGaoId > 0)
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(Item.nGongGaoId);
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt32(stu.itemId);
            packet->writeInt8(stu.itemClass);
            packet->writeInt32(stu.itemCount);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(packet);
        }
    }

    SendIcon();
    return 0;
}

int32_t CMonthlyChouJiang::OnAskMonthlyChouJiangInfo(Answer::NetPacket* inPacket)
{
    SendMonthlyChouJiangInfo();
    return 0;
}

void CMonthlyChouJiang::SendMonthlyChouJiangInfo()
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CDB);
    if (!packet)
        return;

    packet->writeInt32(m_pPlayer->GetTodayPayGold());
    packet->writeInt32(m_Score);
    packet->writeInt32(m_AllScore);
    packet->writeInt32((int32_t)m_GetItemList.size());
    for (std::list<int32_t>::iterator it = m_GetItemList.begin(); it != m_GetItemList.end(); ++it)
        packet->writeInt32(*it);

    packet->writeInt32((int32_t)m_GetTimes.size());
    for (std::map<int32_t, int32_t>::iterator it = m_GetTimes.begin(); it != m_GetTimes.end(); ++it)
    {
        packet->writeInt32(it->first);
        packet->writeInt32(it->second);
    }

    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CMonthlyChouJiang::SendMonthlyChouJiangResult(int32_t nId)
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CDC);
    if (!packet)
        return;

    packet->writeInt32(nId);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CMonthlyChouJiang::GetIcon(ShowIcon& icon)
{
    memset(&icon, 0, sizeof(icon));
    icon.nId = 210;
    icon.nState = 1;
}

void CMonthlyChouJiang::GetIcon(IconStateList& IconList)
{
    if (!m_pPlayer)
        return;

    if (!m_pPlayer->GetPlayerFunctionOpen().IsOpened(210))
        return;

    if (CFG_DATA.getServerDiffDay(0) < 0)
        return;

    ShowIcon icon;
    GetIcon(icon);
    IconList.push_back(icon);
}

void CMonthlyChouJiang::SendIcon()
{
    if (!m_pPlayer)
        return;

    if (!m_pPlayer->GetPlayerFunctionOpen().IsOpened(210))
        return;

    if (CFG_DATA.getServerDiffDay(0) < 0)
        return;

    ShowIcon icon;
    GetIcon(icon);
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
    if (packet)
    {
        packet->writeInt32(icon.nId);
        packet->writeInt8(icon.nState);
        packet->writeInt32(icon.nLeftTime);
        packet->writeInt8(icon.IconLeft);
        packet->writeInt32(icon.IconRight);
        packet->writeInt8(icon.Effects);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
    }
}

int32_t CMonthlyChouJiang::GetSocreTimes(int32_t nId)
{
    std::map<int32_t, int32_t>::iterator it = m_GetTimes.find(nId);
    if (it != m_GetTimes.end())
        return it->second;
    return 0;
}

bool CMonthlyChouJiang::TodaySocreIsAllGet()
{
    if (!m_pPlayer)
        return true;

    int32_t TodayPay = m_pPlayer->GetTodayPayGold();
    const MonthlyChouJiangTable* pTable = CFG_DATA.GetMonthlyChouJiangTable();
    if (!pTable)
        return true;

    const MonthlyChouJiangCfgMap* pCfgMap = pTable->GetMonthlyChouJiangCfgMap();
    if (!pCfgMap)
        return true;

    for (MonthlyChouJiangCfgMap::const_iterator it = pCfgMap->begin(); it != pCfgMap->end(); ++it)
    {
        if (it->second.nRecharges > TodayPay)
        {
            int32_t SocreTimes = GetSocreTimes(it->first);
            if (SocreTimes < it->second.nGetTimes)
                return false;
        }
    }
    return true;
}
