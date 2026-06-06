#include "stdafx.h"
#include "CSuperTeHui.h"
#include "GameService.h"
#include "ItemHelper.h"
#include "Player.h"
#include "Bag.h"
#include "Currency.h"
#include "Timer.h"
#include "FunctionOpen.h"

using namespace Answer;

CSuperTeHui::CSuperTeHui()
{
}

CSuperTeHui::~CSuperTeHui()
{
}

void CSuperTeHui::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(645);
    procList.push_back(646);
    procList.push_back(647);
    procList.push_back(648);
}

int32_t CSuperTeHui::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;

    switch (nProcId)
    {
    case 645: return OnBuySuperTeHui(inPacket);
    case 646: return OnGetJewelPavilionItem(inPacket);
    case 647: return OnBuyShengRenItem(inPacket);
    case 648: SendLeftTime(); return 0;
    }
    return 0;
}

void CSuperTeHui::OnDaySwitch(int32_t nDiffDays)
{
    SendJewelPavilionIcon();
    SendShangRenIcon();
}

// ===== SuperTeHui (超级特惠) =====

int32_t CSuperTeHui::OnBuySuperTeHui(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 10002;

    int32_t nIndex = inPacket->readInt32();
    const SuperTeHuiCfg* pCfg = CFG_DATA.GetSuperTeHuiCfg(nIndex);
    if (!pCfg)
        return 10002;

    int32_t OldRecord = m_pPlayer->getRecord(1028);
    int32_t NewRecord = OldRecord | (1 << (nIndex - 1));
    if (OldRecord == NewRecord)
        return 2;

    if (m_pPlayer->GetPlayerVip().GetVipLevel() < pCfg->nNeedVip)
        return 2;

    if (pCfg->Items.empty())
        return 2;

    if (m_pPlayer->GetBag().GetFreeSlotCount() < (int32_t)pCfg->Items.size())
        return 2;

    if (pCfg->nPrice <= 0)
        return 2;

    if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, pCfg->nPrice, GCR_BUY_SUPER_TE_HUI, nIndex))
        return 2;

    m_pPlayer->GetBag().AddItem((MemChrBagVector*)&pCfg->Items, ICR_SUPER_TE_HUI);
    m_pPlayer->updateRecord(1028, NewRecord);
    SendSuperTeHuiIcon();

    if (pCfg->nGongGaoId > 0)
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pCfg->nGongGaoId);
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeInt32(nIndex);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(packet);
        }
    }
    return 0;
}

void CSuperTeHui::GetSuperTeHuiIcon(IconStateList& IconList)
{
    if (!m_pPlayer)
        return;

    if (m_pPlayer->GetPlayerFunctionOpen().IsOpened(201))
    {
        ShowIcon icon;
        GetSuperTeHuiIcon(icon);
        IconList.push_back(icon);
    }
}

void CSuperTeHui::SendSuperTeHuiIcon()
{
    if (!m_pPlayer)
        return;

    if (m_pPlayer->GetPlayerFunctionOpen().IsOpened(201))
    {
        ShowIcon icon;
        GetSuperTeHuiIcon(icon);
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SEND_ONE_ICON);
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
}

bool CSuperTeHui::IsAllGetTeHui()
{
    if (!m_pPlayer)
        return true;

    int32_t OldRecord = m_pPlayer->getRecord(1028);
    const SuperTeHuiCfgMap* pMap = CFG_DATA.GetSuperTeHuiCfgMap();
    if (!pMap)
        return true;

    for (SuperTeHuiCfgMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it)
    {
        int32_t NewRecord = OldRecord | (1 << (it->first - 1));
        if (OldRecord != NewRecord)
            return false;
    }
    return true;
}

void CSuperTeHui::GetSuperTeHuiIcon(ShowIcon& icon)
{
    memset(&icon, 0, sizeof(icon));
    // Default icon - specific icon ID should come from config
    icon.nId = 200;
    icon.nState = IsAllGetTeHui() ? 4 : 1;
}

// ===== JewelPavilion (宝石阁) =====

int32_t CSuperTeHui::OnGetJewelPavilionItem(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 10002;

    if (!IsOpenedJewelPavilion())
        return 10002;

    int32_t nDay = GetJewelPavilionDay();
    int32_t nIndex = inPacket->readInt32();
    const JewelPavilionCfg* pCfg = CFG_DATA.GetJewelPavilionCfg(nDay, nIndex);
    if (!pCfg)
        return 10002;

    int32_t OldRecord = m_pPlayer->getRecord(2085);
    int32_t NewRecord = OldRecord | (1 << (nIndex - 1));
    if (OldRecord == NewRecord)
        return 2;

    if (m_pPlayer->GetBag().GetFreeSlotCount() <= 0)
        return 10002;

    if (pCfg->nPrice > 0 && !m_pPlayer->DecCurrency(CURRENCY_GOLD, pCfg->nPrice, GCR_JEWEL_PAVILION, 0))
        return 10002;

    m_pPlayer->GetBag().AddItem((MemChrBag*)&pCfg->Item, ICR_JEWEL_PAVILION);
    m_pPlayer->updateRecord(2085, NewRecord);
    SendJewelPavilionIcon();
    return 0;
}

void CSuperTeHui::GetJewelPavilionIcon(IconStateList& IconList)
{
    if (!m_pPlayer)
        return;

    if (IsOpenedJewelPavilion())
    {
        ShowIcon icon;
        GetJewelPavilionIcon(icon);
        IconList.push_back(icon);
    }
}

void CSuperTeHui::SendJewelPavilionIcon()
{
    if (!m_pPlayer)
        return;

    if (IsOpenedJewelPavilion())
    {
        ShowIcon icon;
        GetJewelPavilionIcon(icon);
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SEND_ONE_ICON);
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
}

int32_t CSuperTeHui::HaveFreeCount()
{
    int32_t Count = 0;
    int32_t nDay = GetJewelPavilionDay();
    int32_t OldRecord = m_pPlayer->getRecord(2085);

    const JewelPavilionCfgMap* pMap = CFG_DATA.GetJewelPavilionCfgMap();
    if (!pMap)
        return 0;

    for (JewelPavilionCfgMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it)
    {
        if (it->first.first == nDay && it->second.nPrice <= 0)
        {
            int32_t NewRecord = OldRecord | (1 << (it->second.nIndex - 1));
            if (OldRecord != NewRecord)
                ++Count;
        }
    }
    return Count;
}

bool CSuperTeHui::IsOpenedJewelPavilion()
{
    return m_pPlayer && m_pPlayer->getRecord(1034) > 0;
}

bool CSuperTeHui::IsAllGetPavilion()
{
    if (!m_pPlayer)
        return true;

    int32_t nDay = GetJewelPavilionDay();
    int32_t OldRecord = m_pPlayer->getRecord(2085);

    const JewelPavilionCfgMap* pMap = CFG_DATA.GetJewelPavilionCfgMap();
    if (!pMap)
        return true;

    for (JewelPavilionCfgMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it)
    {
        if (it->first.first == nDay)
        {
            int32_t NewRecord = OldRecord | (1 << (it->second.nIndex - 1));
            if (OldRecord != NewRecord)
                return false;
        }
    }
    return true;
}

bool CSuperTeHui::IsTimeEnd()
{
    if (!m_pPlayer)
        return true;

    int32_t StartTime = m_pPlayer->getRecord(1034);
    int32_t EndTime = DayTime::dayzero(StartTime) + 604800;
    return m_pPlayer->getNow() > EndTime;
}

void CSuperTeHui::SetJewelPavilionOpen()
{
    if (!m_pPlayer)
        return;

    int32_t Now = m_pPlayer->getNow();
    m_pPlayer->updateRecord(1034, Now);
    SendJewelPavilionIcon();
}

int32_t CSuperTeHui::GetJewelPavilionDay()
{
    if (!m_pPlayer)
        return 0;

    int32_t StartTime = m_pPlayer->getRecord(1034);
    return DayTime::daydiff(DayTime::dayzero(StartTime)) + 1;
}

void CSuperTeHui::GetJewelPavilionIcon(ShowIcon& icon)
{
    memset(&icon, 0, sizeof(icon));
    icon.nId = 201;
    icon.nState = 1;
}

// ===== ShangRen (商人) =====

int32_t CSuperTeHui::OnBuyShengRenItem(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 10002;

    int32_t Day = CFG_DATA.getServerDiffDay(0) + 1;
    if (Day <= 9 || Day > 12)
        return 10002;

    int32_t nId = inPacket->readInt32();
    const ShangRenCfg* pCfg = CFG_DATA.GetShangRenCfg(nId);
    if (!pCfg)
        return 10002;

    int32_t OldRecord = m_pPlayer->getRecord(2100);
    int32_t NewRecord = OldRecord | (1 << (nId - 1));
    if (OldRecord == NewRecord)
        return 2;

    if (pCfg->vItem.empty())
        return 2;

    if (m_pPlayer->GetBag().GetFreeSlotCount() < (int32_t)pCfg->vItem.size())
        return 2;

    if (pCfg->nPrice <= 0)
        return 2;

    if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, pCfg->nPrice, GCR_SHANG_REN, nId))
        return 2;

    m_pPlayer->GetBag().AddItem((MemChrBagVector*)&pCfg->vItem, IDCR_SHANG_REN);
    m_pPlayer->updateRecord(2100, NewRecord);
    SendShangRenIcon();
    return 0;
}

void CSuperTeHui::GetShangRenIcon(IconStateList& IconList)
{
    int32_t Day = CFG_DATA.getServerDiffDay(0) + 1;
    if (Day > 9 && Day <= 12)
    {
        ShowIcon icon;
        GetShangRenIcon(icon);
        IconList.push_back(icon);
    }
}

void CSuperTeHui::SendShangRenIcon()
{
    if (!m_pPlayer)
        return;

    ShowIcon icon;
    GetShangRenIcon(icon);
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SEND_ONE_ICON);
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

int32_t CSuperTeHui::GetShangRenLeftTime()
{
    if (!m_pPlayer)
        return 0;

    int32_t Day = CFG_DATA.getServerDiffDay(0) + 1;
    if (Day <= 9 || Day > 12)
        return 0;

    int32_t EndTime = CFG_DATA.getServerStartDayZeroTime() + 1036800;
    return EndTime - m_pPlayer->getNow();
}

void CSuperTeHui::SendLeftTime()
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CC6);
    if (packet)
    {
        int32_t nLeftTime = GetShangRenLeftTime();
        packet->writeInt32(nLeftTime);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
    }
}

void CSuperTeHui::GetShangRenIcon(ShowIcon& icon)
{
    memset(&icon, 0, sizeof(icon));
    icon.nId = 202;
    icon.nState = 1;
}
