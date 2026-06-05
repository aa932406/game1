#include "stdafx.h"
#include "ZongHeYunYingHD.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "CfgData.h"
#include "ItemHelper.h"
#include "Bag.h"

// ====== CZongHeYunYingHD ======

CZongHeYunYingHD::CZongHeYunYingHD()
{
    m_nDay = 0;
    m_nStartDay = 0;
    m_nEndDay = 0;
    m_nIcon = 0;
    m_nMinute = 0;
    m_nRechargeDailyValue = 0;
    m_nRechargeDailyRewardLimit = 0;
    m_nRechargeRankDailyArea = 0;
    m_nRechargeRankDailySize = 0;
    m_nRechargeTeamShopDailySize = 0;
    m_nOnceShopSize = 0;
    memset(m_vOpen, 0, sizeof(m_vOpen));
    memset(m_vStartDay, 0, sizeof(m_vStartDay));
    memset(m_vEndDay, 0, sizeof(m_vEndDay));
}

CZongHeYunYingHD::~CZongHeYunYingHD()
{
}

void CZongHeYunYingHD::Init(int32_t line)
{
    m_nDay = CFG_DATA.getServerDiffTime();
    tm nowTime = TIMER.GetLocalNow();
    m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
    initCfgData();
    loadRankData();
}

void CZongHeYunYingHD::initCfgData()
{
    memset(m_vStartDay, 0, sizeof(m_vStartDay));
    memset(m_vEndDay, 0, sizeof(m_vEndDay));

    const CfgZongHeYunYingHD* pCfg = CFG_DATA.GetZongHeYunYingHDCfg();
    if (pCfg == NULL)
        return;

    m_nStartDay = pCfg->nStartDay;
    m_nEndDay = pCfg->nEndDay;
    m_nIcon = pCfg->nIcon;
    initOpenList(pCfg->strOpen);

    if (isOpen(ZHYYHDT_RECHARGE_DAILY))
    {
        m_vStartDay[ZHYYHDT_RECHARGE_DAILY] = pCfg->nDailyRechargeStartDay;
        m_vEndDay[ZHYYHDT_RECHARGE_DAILY] = pCfg->nDailyRechargeEndDay;
        m_nRechargeDailyValue = pCfg->nDailyRechargeValue;
        m_nRechargeDailyRewardLimit = pCfg->nDailyRechargeRewardLimit;
        m_vRechargeDailyReward = pCfg->vDailyRechargeReward;
    }

    if (isOpen(ZHYYHDT_RECHARGE_RANK_DAILY))
    {
        m_vStartDay[ZHYYHDT_RECHARGE_RANK_DAILY] = pCfg->nRankDailyStartDay;
        m_vEndDay[ZHYYHDT_RECHARGE_RANK_DAILY] = pCfg->nRankDailyEndDay;
        m_nRechargeRankDailyArea = pCfg->nRankDailyArea;
        m_nRechargeRankDailySize = pCfg->nRankDailySize;
        m_vRechargeRankDailyIndex = pCfg->vRankDailyIndex;
        m_vRechargeRankDailyReward = pCfg->vRankDailyReward;
        m_vRechargeRankDailyMail = pCfg->vRankDailyMail;
    }

    if (isOpen(ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY))
    {
        m_vStartDay[ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY] = pCfg->nTeamShopDailyStartDay;
        m_vEndDay[ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY] = pCfg->nTeamShopDailyEndDay;
        m_nRechargeTeamShopDailySize = pCfg->nTeamShopDailySize;
        m_vRechargeTeamShopDailyPlayer = pCfg->vTeamShopDailyPlayer;
        m_vRechargeTeamShopDailyValue = pCfg->vTeamShopDailyValue;
        m_vRechargeTeamShopDailyReward = pCfg->vTeamShopDailyReward;
    }

    if (isOpen(ZHYYHDT_ONCE_SHOP))
    {
        m_vStartDay[ZHYYHDT_ONCE_SHOP] = pCfg->nOnceShopStartDay;
        m_vEndDay[ZHYYHDT_ONCE_SHOP] = pCfg->nOnceShopEndDay;
        m_nOnceShopSize = pCfg->nOnceShopSize;
        m_vOnceShopPrice = pCfg->vOnceShopPrice;
        m_vOnceShopItem = pCfg->vOnceShopItem;
    }
}

void CZongHeYunYingHD::initOpenList(const std::string& str)
{
    memset(m_vOpen, 0, sizeof(m_vOpen));
    StringVector vOpen = Answer::StringUtility::split(str, "|");
    for (size_t i = 0; i < vOpen.size(); ++i)
    {
        int8_t nType = (int8_t)atoi(vOpen[i].c_str());
        if (nType > 0 && nType < ZHYYHDT_MAX)
            m_vOpen[nType] = 1;
    }
}

bool CZongHeYunYingHD::isOpen(ZONG_HE_YUN_YING_HD_TYPE nType) const
{
    if (nType <= 0 || nType >= ZHYYHDT_MAX)
        return false;
    return m_vOpen[nType] != 0;
}

void CZongHeYunYingHD::loadRankData()
{
    for (int32_t i = 0; i < ZHYYHDT_MAX; ++i)
    {
        if (m_vOpen[i])
        {
            //DB_SERVICE.LoadZHYYHDRank((int8_t)i, m_nDay);
        }
    }
}

void CZongHeYunYingHD::OnDaySwitch()
{
    m_nDay = CFG_DATA.getServerDiffTime();
    if (m_nDay >= m_nEndDay)
        hideIcon(m_nIcon);

    if (isOpen(ZHYYHDT_RECHARGE_RANK_DAILY))
        sendRechargeDailyRankReward();

    if (isOpen(ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY))
    {
        Answer::MutexGuard lock(m_lock);
        m_mRechargeDailyPlayer.clear();
    }
}

void CZongHeYunYingHD::OnNewMinute(int32_t nMinute)
{
    m_nMinute = nMinute;
    IsInTime();
}

bool CZongHeYunYingHD::IsInTime()
{
    return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CZongHeYunYingHD::needShowIcon()
{
    return m_nDay >= m_nStartDay && m_nDay < m_nEndDay;
}

bool CZongHeYunYingHD::IsInTime(ZONG_HE_YUN_YING_HD_TYPE nType)
{
    return IsOpen(nType)
        && m_nDay >= m_vStartDay[nType]
        && m_nDay < m_vEndDay[nType];
}

bool CZongHeYunYingHD::IsOpen(ZONG_HE_YUN_YING_HD_TYPE nType)
{
    return IsInTime() && isOpen(nType);
}

int32_t CZongHeYunYingHD::getLeftTime()
{
    if (!IsInTime())
        return 0;
    int32_t nNowTime = TIMER.GetNow();
    return 86400 * (m_nEndDay - m_nDay) - (nNowTime - Answer::DayTime::dayzero(nNowTime));
}

void CZongHeYunYingHD::getIconState(ShowIcon& icon, Player* player)
{
    memset(&icon, 0, sizeof(icon));
    icon.nId = m_nIcon;
    icon.nState = AS_RUNNING;
    icon.nLeftTime = -1;
    icon.Effects = 1;
}

void CZongHeYunYingHD::GetIconState(Player* player, IconStateList& IconList)
{
    if (player && needShowIcon())
    {
        ShowIcon icon;
        getIconState(icon, player);
        IconList.push_back(icon);
    }
}

void CZongHeYunYingHD::SendIconState(Player* player)
{
    if (player && needShowIcon())
    {
        ShowIcon icon;
        getIconState(icon, player);
        // Send as packet
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
            GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
        }
    }
}

void CZongHeYunYingHD::hideIcon(int32_t nIconId)
{
    // hideIcon: broadcast icon removal
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
    if (packet)
    {
        packet->writeInt32(nIconId);
        packet->writeInt8(AS_TIME_OUT);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.worldBroadcast(packet);
    }
}

void CZongHeYunYingHD::SendActivityInfo(Player* player)
{
    if (!player)
        return;

    int8_t connid = player->getGateIndex();
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2EB9);
    if (!packet)
        return;

    uint32_t oldOffset = packet->getWOffset();
    int8_t nCount = 0;
    packet->writeInt8(0);

    if (IsInTime(ZHYYHDT_RECHARGE_DAILY))
    {
        packet->writeInt8(1);
        packet->writeInt32(player->GetTodayPayGold());
        packet->writeInt32(player->GetOperateLimit().GetLimitCount(1135));
        ++nCount;
    }

    if (IsInTime(ZHYYHDT_RECHARGE_RANK_DAILY))
    {
        packet->writeInt8(2);
        checkRankInvalid(connid, 2);
        packet->writeInt32(m_nRechargeRankDailySize);
        {
            Answer::MutexGuard lock(m_lock);
            FestivalRankVector& rank = m_mRechargeDailyRank[connid];
            for (int32_t i = 0; i < (int32_t)rank.size() && i < m_nRechargeRankDailySize; ++i)
            {
                packet->writeUTF8(rank[i].strName);
                packet->writeInt32(rank[i].nScore);
            }
        }
        ++nCount;
    }

    if (IsInTime(ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY))
    {
        packet->writeInt8(3);
        packet->writeInt32(player->GetTodayPayGold());
        packet->writeInt32(getRechargePlayer(connid));
        packet->writeInt32(player->GetOperateLimit().GetLimitCount(1136));
        ++nCount;
    }

    if (IsInTime(ZHYYHDT_ONCE_SHOP))
    {
        packet->writeInt8(4);
        packet->writeInt32(player->GetOperateLimit().GetLimitCount(1137));
        ++nCount;
    }

    uint32_t newOffset = packet->getWOffset();
    packet->setWOffset(oldOffset);
    packet->writeInt8(nCount);
    packet->setWOffset(newOffset);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
}

void CZongHeYunYingHD::OnRecharge(Player* player, int32_t nValue)
{
    if (!player || !IsInTime())
        return;

    bool bNeedSync = false;

    if (IsInTime(ZHYYHDT_RECHARGE_DAILY))
    {
        int32_t nGetTimes = player->GetOperateLimit().GetLimitCount(2069);
        int32_t nTodayTimes = player->GetTodayPayGold() / m_nRechargeDailyValue;
        player->GetOperateLimit().AddLimitCount(1135, nTodayTimes - nGetTimes);
        bNeedSync = true;
    }

    if (IsInTime(ZHYYHDT_RECHARGE_RANK_DAILY))
    {
        FestivalRank info;
        info.nCharId = player->getCid();
        info.strName = player->getName();
        info.nScore = player->GetTodayPayGold();
        info.nTime = player->getNow();

        if (GAME_SERVICE.getLine() == 1)
            updateRankInfo(player->getGateIndex(), 2, info);
        else
            sendLineSocialPlayerInfo(player->getGateIndex(), 2, info);
    }

    if (IsInTime(ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY))
    {
        {
            Answer::MutexGuard lock(m_lock);
            m_mRechargeDailyPlayer[player->getGateIndex()][player->getCid()] = player->GetTodayPayGold();
        }

        FestivalRank info;
        info.nCharId = player->getCid();
        info.strName = player->getName();
        info.nScore = player->GetTodayPayGold();
        info.nTime = player->getNow();

        FestivalRankVector vUpdate;
        vUpdate.push_back(info);
        //DB_SERVICE.SaveZHYYHDRank(player->getGateIndex(), 3, m_nDay, vUpdate);
    }

    if (bNeedSync)
        SendIconState(player);
}

void CZongHeYunYingHD::UpdatePlayerInfo(int8_t connid, Answer::NetPacket* inPacket)
{
    if (!inPacket)
        return;

    int8_t nType = inPacket->readInt8();
    int16_t nDay = inPacket->readInt16();
    FestivalRank info;
    info.nCharId = inPacket->readInt64();
    info.strName = inPacket->readUTF8(true);
    info.nScore = inPacket->readInt32();
    info.nTime = inPacket->readInt32();

    if (nDay == m_nDay)
        updateRankInfo(connid, nType, info);
}

void CZongHeYunYingHD::sendLineSocialPlayerInfo(int8_t connid, int8_t nType, const FestivalRank& info)
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x4EC1);
    if (!packet)
        return;

    packet->writeInt32(1);
    packet->writeInt8(nType);
    packet->writeInt16(m_nDay);
    packet->writeInt64(info.nCharId);
    packet->writeUTF8(info.strName);
    packet->writeInt32(info.nScore);
    packet->writeInt32(info.nTime);
    packet->setSize(packet->getWOffset());
    // TODO: sendPacket API not available
			//GAME_SERVICE.sendPacket(connid, packet);
}

void CZongHeYunYingHD::checkRankInvalid(int8_t connid, int8_t nType)
{
    Answer::MutexGuard lock(m_lock);

    if (nType == 2)
    {
        if (m_mRechargeDailyRank.find(connid) == m_mRechargeDailyRank.end())
        {
            FestivalRankVector vRank;
            FestivalRank emptyRank;
            vRank.resize(m_nRechargeRankDailySize, emptyRank);
            m_mRechargeDailyRank[connid] = vRank;
        }
    }
}

void CZongHeYunYingHD::updateRankInfo(int8_t connid, int8_t nType, const FestivalRank& info)
{
    checkRankInvalid(connid, nType);

    FestivalRankVector* pRank = NULL;
    int32_t nRankSize = 0;

    if (nType == 2)
    {
        Answer::MutexGuard lock(m_lock);
        pRank = &m_mRechargeDailyRank[connid];
        nRankSize = m_nRechargeRankDailySize;
    }

    if (!pRank || nRankSize <= 0)
        return;

    FestivalRankVector& vRank = *pRank;
    int32_t nRankIndex = -1;

    for (int32_t i = 0; i < nRankSize; ++i)
    {
        if (vRank[i].nScore < info.nScore)
        {
            nRankIndex = i;
            break;
        }
    }

    if (nRankIndex < 0)
        return;

    FestivalRankVector vUpdate;
    vUpdate.reserve(vRank.size());

    int32_t nOldIndex = nRankSize - 1;
    for (int32_t i = 0; i < nRankSize; ++i)
    {
        if (vRank[i].nCharId == info.nCharId)
        {
            nOldIndex = i;
            break;
        }
    }

    if (nOldIndex < nRankIndex)
        nRankIndex = nOldIndex;

    if (nOldIndex != nRankIndex)
    {
        for (int32_t i = nOldIndex; i > nRankIndex; --i)
        {
            vRank[i] = vRank[i - 1];
            vRank[i].nIndex = i;
            vUpdate.push_back(vRank[i]);
        }
    }

    vRank[nRankIndex] = info;
    vRank[nRankIndex].nIndex = nRankIndex;
    vUpdate.push_back(vRank[nRankIndex]);

    if (!vUpdate.empty())
    {
        //DB_SERVICE.SaveZHYYHDRank(connid, nType, m_nDay, vUpdate);
    }
}

void CZongHeYunYingHD::UpdateRankInfo(int8_t connid, int8_t nType, int32_t nDay, const FestivalRankVector& vUpdateRank)
{
    checkRankInvalid(connid, nType);

    FestivalRankVector* pRank = NULL;
    int32_t nRankSize = 0;

    if (nType == 2)
    {
        Answer::MutexGuard lock(m_lock);
        pRank = &m_mRechargeDailyRank[connid];
        nRankSize = m_nRechargeRankDailySize;
    }
    else if (nType == 3)
    {
        for (size_t i = 0; i < vUpdateRank.size(); ++i)
        {
            Answer::MutexGuard lock(m_lock);
            m_mRechargeDailyPlayer[connid][vUpdateRank[i].nCharId] = vUpdateRank[i].nScore;
        }
    }

    if (pRank && nRankSize > 0)
    {
        FestivalRankVector& vRank = *pRank;
        for (size_t i = 0; i < vUpdateRank.size(); ++i)
        {
            int32_t nIndex = vUpdateRank[i].nIndex;
            if (nIndex >= 0 && nIndex < nRankSize)
            {
                Answer::MutexGuard lock(m_lock);
                vRank[nIndex] = vUpdateRank[i];
            }
        }
    }
}

int32_t CZongHeYunYingHD::GetRechargeDailyReward(Player* player)
{
    if (!player) return 10002;
    if (!IsInTime(ZHYYHDT_RECHARGE_DAILY)) return 10002;

    int32_t nLeftTimes = player->GetOperateLimit().GetLimitCount(1135);
    if (nLeftTimes <= 0) return 10002;

    MemChrBagVector vItem = m_vRechargeDailyReward;
    for (size_t i = 0; i < vItem.size(); ++i)
        vItem[i].itemCount *= nLeftTimes;

    if (!player->GetBag().AddItem(vItem, IACR_ZHYYHD_RECHARGE_DAILY_REWARD))
        return 10002;

    int32_t nTodayTimes = player->GetTodayPayGold() / m_nRechargeDailyValue;
    player->GetOperateLimit().UpdateLimitCount(2069, nTodayTimes);
    player->GetOperateLimit().Reset(1135);
    SendIconState(player);
    return 0;
}

int32_t CZongHeYunYingHD::GetRechargeTeamShopDailyReward(Player* player, int32_t nIndex)
{
    if (!player) return 10002;
    if (!IsInTime(ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY)) return 10002;
    if (nIndex < 0 || nIndex >= m_nRechargeTeamShopDailySize) return 10002;

    int32_t nOldRecord = player->GetOperateLimit().GetLimitCount(1136);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord) return 10002;

    int32_t nRechargePlayer = getRechargePlayer(player->getGateIndex());
    if (nRechargePlayer < m_vRechargeTeamShopDailyPlayer[nIndex]) return 10002;
    if (player->GetTodayPayGold() < m_vRechargeTeamShopDailyValue[nIndex]) return 10002;

    if (!player->GetBag().AddItem(m_vRechargeTeamShopDailyReward[nIndex], IACR_ZHYYHD_RECHARGE_TEAM_SHOP_REWARD))
        return 10002;

    player->GetOperateLimit().UpdateLimitCount(1136, nNewRecord);
    SendIconState(player);
    return 0;
}

int32_t CZongHeYunYingHD::BuyOnceShopItem(Player* player, int32_t nIndex)
{
    if (!player) return 10002;
    if (!IsInTime(ZHYYHDT_ONCE_SHOP)) return 10002;
    if (nIndex < 0 || nIndex >= m_nOnceShopSize) return 10002;

    int32_t nOldRecord = player->GetOperateLimit().GetLimitCount(1137);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord) return 10002;

    int64_t nGold = player->GetCurrency(CURRENCY_GOLD);
    if (nGold < m_vOnceShopPrice[nIndex]) return 10002;

    if (!player->GetBag().AddItem(m_vOnceShopItem[nIndex], IACR_ZHYYHD_ONCE_SHOP_ITEM))
        return 10002;

    if (!player->DecCurrency(CURRENCY_GOLD, m_vOnceShopPrice[nIndex], GCR_ZHYYHD_BUY_ONCE_SHOP_ITEM, nIndex))
        return 10002;

    player->GetOperateLimit().UpdateLimitCount(1137, nNewRecord);
    return 0;
}

void CZongHeYunYingHD::sendRechargeDailyRankReward()
{
    if (m_mRechargeDailyRank.empty())
        return;

    if (GAME_SERVICE.getLine() != 1)
        return;

    for (int32_t i = 0; i < m_nRechargeRankDailyArea; ++i)
    {
        Answer::MutexGuard lock(m_lock);
        for (std::map<int8_t, FestivalRankVector>::iterator map_iter = m_mRechargeDailyRank.begin();
             map_iter != m_mRechargeDailyRank.end(); ++map_iter)
        {
            int8_t connid = map_iter->first;
            FestivalRankVector& vRank = map_iter->second;

            for (size_t j = 0; j < vRank.size(); ++j)
            {
                if (vRank[j].nCharId <= 0)
                    continue;

                int32_t nIndex = vRank[j].nIndex;
                if (nIndex >= m_vRechargeRankDailyIndex[i].first &&
                    nIndex <= m_vRechargeRankDailyIndex[i].second &&
                    (size_t)i < m_vRechargeRankDailyReward.size() &&
                    (size_t)i < m_vRechargeRankDailyMail.size())
                {
                                        // TODO: DBService::OnSendSysMail not available
                    /*
                    DB_SERVICE.OnSendSysMail(
                        connid,
                        vRank[j].nCharId,
                        m_vRechargeRankDailyMail[i],
                        &m_vRechargeRankDailyReward[i],
                        IACR_ZHYYHD_RECHARGE_RANK_DAILY_REWARD,
                        "",
                        0);
                    */
                }
            }
        }
    }
}

int32_t CZongHeYunYingHD::getRechargePlayer(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    return (int32_t)m_mRechargeDailyPlayer[connid].size();
}
