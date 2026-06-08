#include "stdafx.h"
#include "CDaTingReward.h"
#include "GameService.h"
#include "ItemHelper.h"
#include "Player.h"
#include "Bag.h"
#include "Currency.h"
#include "Vplan.h"
#include "DBService.h"

using namespace Answer;

// ===== 构造/析构 =====

void CDaTingReward::OnUpdate(int64_t curTick)
{
}

void CDaTingReward::OnCleanUp()
{
    m_IsDaTingLogin = 0;
}

void CDaTingReward::OnLoadFromDB(const PlayerDBData& dbData)
{
    // No DB data to load
}

void CDaTingReward::OnSaveToDB(PlayerDBData& dbData)
{
    // No DB data to save
}

void CDaTingReward::OnDaySwitch(int32_t nDiffDays)
{
    if (!m_pPlayer)
        return;

    // 每天重置平台答题奖励标记
    std::string platform = m_pPlayer->GetPlatform();
    const PlatformDaTingMap* pDaTingMap = CFG_DATA.GetPlatformDaTingMap();
    if (pDaTingMap)
    {
        int32_t nOldRecord = m_pPlayer->getRecord(1106);
        int32_t nNewRecord = 0;
        for (PlatformDaTingMap::const_iterator it = pDaTingMap->begin();
             it != pDaTingMap->end(); ++it)
        {
            if (it->first.first == platform && it->second.nType != 7)
            {
                if ((nOldRecord >> it->second.nSlot) & 1)
                    nNewRecord |= (1 << it->second.nSlot);
            }
        }
        m_pPlayer->updateRecord(1106, nNewRecord);

        // pdsso 特殊处理
        if (platform == "pdsso")
        {
            nOldRecord = m_pPlayer->getRecord(1106);
            nNewRecord = 0;
            for (PlatformDaTingMap::const_iterator it = pDaTingMap->begin();
                 it != pDaTingMap->end(); ++it)
            {
                if (it->first.first == platform && it->second.nType != 2)
                {
                    if ((nOldRecord >> it->second.nSlot) & 1)
                        nNewRecord |= (1 << it->second.nSlot);
                }
            }
            m_pPlayer->updateRecord(1106, nNewRecord);
        }
    }

    SendDaTingInfo();
    SendDaTingIcon();
    SendMiniClientIcon();
    SendMiniClientInfo();
}

void CDaTingReward::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(CM_REQUEST_DA_TING_INFO);
    procList.push_back(CM_GET_DA_TING_REWARD);
    procList.push_back(CM_FROM_DA_TING);
    procList.push_back(CM_REQUEST_PLATFORM_VIP_INFO);
    procList.push_back(CM_GET_PLATFORM_VIP_REWARD);
    procList.push_back(CM_GET_PLATFORM_REWARD);
    procList.push_back(CM_GET_MINI_CLIENT_REWARD);
    procList.push_back(CM_REQUEST_MINI_CLIENT_INFO);
}

int32_t CDaTingReward::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (!inPacket)
        return 2;

    switch (nProcId)
    {
    case CM_REQUEST_DA_TING_INFO:       return onRequestDaTingInfo(inPacket);
    case CM_GET_DA_TING_REWARD:         return onGetDaTingReward(inPacket);
    case CM_FROM_DA_TING:               return onFromDaTing(inPacket);
    case CM_REQUEST_PLATFORM_VIP_INFO:  return onRequestPlatformVipInfo(inPacket);
    case CM_GET_PLATFORM_VIP_REWARD:    return onGetPlatformVipReward(inPacket);
    case CM_GET_PLATFORM_REWARD:        return onGetPlatformReward(inPacket);
    case CM_GET_MINI_CLIENT_REWARD:     return onGetMiniClientReward(inPacket);
    case CM_REQUEST_MINI_CLIENT_INFO:   return onRequestMiniClientInfo(inPacket);
    default:                            return 2;
    }
}

// ===== 平台答题 =====

bool CDaTingReward::HaveDaTingReward() const
{
    if (!m_pPlayer)
        return false;

    std::string platform = m_pPlayer->GetPlatform();
    return CFG_DATA.GetGetPlatformDaTingCfg(platform, 1) != NULL;
}

void CDaTingReward::SendDaTingInfo()
{
    if (!m_pPlayer || !HaveDaTingReward())
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D17);
    if (packet)
    {
        packet->writeInt32(m_pPlayer->GetContinueLoginCount());
        packet->writeInt32(GetPlatformVipLevel());
        packet->writeInt32(m_pPlayer->getRecord(1106));
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

void CDaTingReward::GetDaTingIconState(IconStateList& IconList)
{
    if (HaveDaTingReward() && m_pPlayer)
    {
        ShowIcon icon;
        // Build icon state
        icon.nId = 0;
        icon.nState = 1;
        IconList.push_back(icon);
    }
}

void CDaTingReward::SendDaTingIcon()
{
    if (!m_pPlayer || !HaveDaTingReward())
        return;

    ShowIcon icon;
    icon.nId = 0;
    icon.nState = 1;
    m_pPlayer->SendIconState(&icon);
}

bool CDaTingReward::NeedDaTing() const
{
    if (!m_pPlayer)
        return true;

    std::string platform = m_pPlayer->GetPlatform();
    // 这些平台不需要答题
    if (platform == "yilewan" || platform == "wan_993h" ||
        platform == "liebao_993h" || platform == "douyu_993h")
        return false;

    return true;
}

int32_t CDaTingReward::HaveDaTingLeftGift() const
{
    if (NeedDaTing() && !m_IsDaTingLogin)
        return 0;

    int32_t nCount = 0;
    int32_t nRecord = m_pPlayer->getRecord(1106);
    std::string platform = m_pPlayer->GetPlatform();

    const PlatformDaTingMap* pDaTingMap = CFG_DATA.GetPlatformDaTingMap();
    if (!pDaTingMap)
        return 0;

    for (PlatformDaTingMap::const_iterator it = pDaTingMap->begin();
         it != pDaTingMap->end(); ++it)
    {
        if (it->first.first != platform)
            continue;

        if ((nRecord >> it->second.nSlot) & 1)
            continue;

        switch (it->second.nType)
        {
        case 1:
            ++nCount;
            break;
        case 2:
            if (m_pPlayer->GetContinueLoginCount() >= it->second.nParam)
                ++nCount;
            break;
        case 3:
            if (m_pPlayer->getLevel() >= it->second.nParam)
                ++nCount;
            break;
        case 6:
            if (GetPlatformVipLevel() >= it->second.nParam)
                ++nCount;
            break;
        case 7:
            if (GetPlatformVipLevel() >= it->second.nParam &&
                GetPlatformVipLevel() <= it->second.nParam2)
                ++nCount;
            break;
        default:
            break;
        }
    }
    return nCount;
}

// ===== 协议处理：平台答题 =====

int32_t CDaTingReward::onRequestDaTingInfo(Answer::NetPacket* inPacket)
{
    SendDaTingInfo();
    return 0;
}

int32_t CDaTingReward::onGetDaTingReward(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    if (NeedDaTing() && !m_IsDaTingLogin)
        return 2;

    int8_t nIndex = inPacket->readInt8();
    std::string platform = m_pPlayer->GetPlatform();
    const PlatformDaTing* pDaTing = CFG_DATA.GetGetPlatformDaTingCfg(platform, nIndex);
    if (!pDaTing)
        return 2;

    // 检查条件
    switch (pDaTing->nType)
    {
    case 1:
    case 9:
        break;
    case 2:
        if (m_pPlayer->GetContinueLoginCount() < pDaTing->nParam)
            return 2;
        break;
    case 3:
        if (m_pPlayer->getLevel() < pDaTing->nParam)
            return 2;
        break;
    case 6:
        if (GetPlatformVipLevel() < pDaTing->nParam)
            return 2;
        break;
    case 7:
        if (GetPlatformVipLevel() < pDaTing->nParam || GetPlatformVipLevel() > pDaTing->nParam2)
            return 2;
        break;
    default:
        return 2;
    }

    int32_t nOldRecord = m_pPlayer->getRecord(1106);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord)
        return 2;

    CExtCharBag& pBag = m_pPlayer->GetBag();
    if (!pBag.AddItem(pDaTing->vItems, IACR_PALTFORM_DA_TING))
        return 2;

    m_pPlayer->updateRecord(1106, nNewRecord);
    SendDaTingInfo();
    SendDaTingIcon();
    return 0;
}

int32_t CDaTingReward::onFromDaTing(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer)
        return 10002;

    m_IsDaTingLogin = 1;
    SendDaTingIcon();
    m_pPlayer->RecalcAttr();
    return 0;
}

// ===== 平台VIP =====

void CDaTingReward::SendPlatformVipInfo()
{
    if (!m_pPlayer || !HavePlatformVipReward())
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D18);
    if (packet)
    {
        packet->writeInt32(GetPlatformVipLevel());
        packet->writeInt32(m_pPlayer->getRecord(1107));
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

void CDaTingReward::GetPlatformVipIconState(IconStateList& IconList)
{
    if (HavePlatformVipReward() && m_pPlayer)
    {
        ShowIcon icon;
        icon.nId = 0;
        icon.nState = 1;
        IconList.push_back(icon);
    }
}

void CDaTingReward::SendPlatformVipIcon()
{
    if (!m_pPlayer || !HavePlatformVipReward())
        return;

    ShowIcon icon;
    icon.nId = 0;
    icon.nState = 1;
    m_pPlayer->SendIconState(&icon);
}

int32_t CDaTingReward::HavePlatformVipLeftGift() const
{
    if (!m_IsDaTingLogin)
        return 0;

    int32_t nCount = 0;
    int32_t nRecord = m_pPlayer->getRecord(1107);
    std::string platform = m_pPlayer->GetPlatform();

    const PlatformVipMap* pVipMap = CFG_DATA.GetPlatformVipMap();
    if (!pVipMap)
        return 0;

    for (PlatformVipMap::const_iterator it = pVipMap->begin();
         it != pVipMap->end(); ++it)
    {
        if (it->first.first != platform)
            continue;

        if ((nRecord >> it->second.nId) & 1)
            continue;

        if (GetPlatformVipLevel() >= it->second.nNeedVipLevel)
            ++nCount;
    }
    return nCount;
}

bool CDaTingReward::HavePlatformVipReward() const
{
    if (!m_pPlayer)
        return false;

    std::string platform = m_pPlayer->GetPlatform();
    return CFG_DATA.GetGetPlatformVipCfg(platform, 1) != NULL;
}

int32_t CDaTingReward::GetPlatformVipLevel() const
{
    if (!m_pPlayer)
        return 0;

    return m_pPlayer->GetVplan().GetPlatformVipLevel();
}

// ===== 协议处理：平台VIP =====

int32_t CDaTingReward::onRequestPlatformVipInfo(Answer::NetPacket* inPacket)
{
    SendPlatformVipInfo();
    return 0;
}

int32_t CDaTingReward::onGetPlatformVipReward(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    int8_t nIndex = inPacket->readInt8();
    std::string platform = m_pPlayer->GetPlatform();
    const PlatformVip* pVip = CFG_DATA.GetGetPlatformVipCfg(platform, nIndex);
    if (!pVip)
        return 2;

    if (GetPlatformVipLevel() < pVip->nNeedVipLevel)
        return 2;

    int32_t nOldRecord = m_pPlayer->getRecord(1107);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord)
        return 2;

    CExtCharBag& pBag = m_pPlayer->GetBag();
    if (!pBag.AddItem(pVip->vItem, IACR_PALTFORM_VIP))
        return 2;

    m_pPlayer->updateRecord(1107, nNewRecord);
    SendPlatformVipInfo();
    SendPlatformVipIcon();
    return 0;
}

// ===== 平台奖励 =====

void CDaTingReward::GetPlatformRewardIconState(IconStateList& IconList)
{
    if (!m_pPlayer)
        return;

    int32_t nOldRecord = m_pPlayer->getRecord(1904);
    const PlatformRewardCfgMap* pRewardMap = CFG_DATA.GetPlatformRewardCfgMap();
    if (!pRewardMap)
        return;

    std::string platform = m_pPlayer->GetPlatform();

    for (PlatformRewardCfgMap::const_iterator it = pRewardMap->begin();
         it != pRewardMap->end(); ++it)
    {
        if (it->first.first != platform)
            continue;

        if (it->second.nIsAllShow > 0 || ((nOldRecord >> (it->second.nId - 1)) & 1) != 1)
        {
            ShowIcon icon;
            icon.nId = it->second.nIcon;
            icon.nState = 1;
            IconList.push_back(icon);
        }
    }
}

void CDaTingReward::SendPlatformRewardIcon(int32_t nId)
{
    if (!m_pPlayer)
        return;

    ShowIcon icon;
    icon.nId = nId;
    icon.nState = 0;
    m_pPlayer->SendIconState(&icon);
}

int32_t CDaTingReward::onGetPlatformReward(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    int32_t nIndex = inPacket->readInt32();
    std::string platform = m_pPlayer->GetPlatform();
    const PlatformRewardCfg* pReward = CFG_DATA.GetGetPlatformRewardCfg(platform, nIndex);
    if (!pReward)
        return 2;

    int32_t nOldRecord = m_pPlayer->getRecord(1904);
    int32_t nNewRecord = nOldRecord | (1 << (nIndex - 1));
    if (nOldRecord == nNewRecord)
        return 2;

    CExtCharBag& pBag = m_pPlayer->GetBag();
    if (!pBag.AddItem(pReward->vItem, IACR_PLATFORM_REWARD))
        return 2;

    m_pPlayer->updateRecord(1904, nNewRecord);

    if (pReward->nIsAllShow <= 0)
        SendPlatformRewardIcon(pReward->nIcon);

    return 0;
}

// ===== 微端 =====

void CDaTingReward::GetMiniClientIconState(IconStateList& IconList)
{
    if (HaveMiniClientReward() && m_pPlayer)
    {
        ShowIcon icon;
        icon.nId = 0;
        icon.nState = 1;
        IconList.push_back(icon);
    }
}

void CDaTingReward::SendMiniClientIcon()
{
    if (!m_pPlayer || !HaveMiniClientReward())
        return;

    ShowIcon icon;
    icon.nId = 0;
    icon.nState = 1;
    m_pPlayer->SendIconState(&icon);
}

void CDaTingReward::SendMiniClientInfo()
{
    if (!m_pPlayer || !HaveMiniClientReward())
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D19);
    if (packet)
    {
        packet->writeInt32(m_pPlayer->GetContinueLoginCount());
        packet->writeInt32(GetPlatformVipLevel());
        packet->writeInt32(m_pPlayer->getRecord(1108));
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

int32_t CDaTingReward::HaveMiniClientLeftGift() const
{
    if (!m_pPlayer || !m_pPlayer->IsMiniClient())
        return 0;

    int32_t nCount = 0;
    int32_t nRecord = m_pPlayer->getRecord(1108);
    std::string platform = m_pPlayer->GetPlatform();

    const MiniClientCfgMap* pMiniMap = CFG_DATA.GetMiniClientMap();
    if (!pMiniMap)
        return 0;

    for (MiniClientCfgMap::const_iterator it = pMiniMap->begin();
         it != pMiniMap->end(); ++it)
    {
        if (it->first.first != platform)
            continue;

        if ((nRecord >> it->second.nId) & 1)
            continue;

        switch (it->second.nType)
        {
        case 1:
            ++nCount;
            break;
        case 2:
            if (m_pPlayer->GetContinueLoginCount() < it->second.nParam)
                ++nCount;
            break;
        case 3:
            if (m_pPlayer->getLevel() < it->second.nParam)
                ++nCount;
            break;
        case 6:
            if (GetPlatformVipLevel() < it->second.nParam)
                ++nCount;
            break;
        case 7:
            if (GetPlatformVipLevel() < it->second.nParam || GetPlatformVipLevel() > it->second.nParam2)
                ++nCount;
            break;
        case 8:
            if (GetPlatformVipLevel() < it->second.nParam || GetPlatformVipLevel() > it->second.nParam2)
                ++nCount;
            break;
        default:
            break;
        }
    }
    return nCount;
}

bool CDaTingReward::HaveMiniClientReward() const
{
    if (!m_pPlayer)
        return false;

    std::string platform = m_pPlayer->GetPlatform();
    return CFG_DATA.GetMiniClientCfg(platform, 1) != NULL;
}

int32_t CDaTingReward::onRequestMiniClientInfo(Answer::NetPacket* inPacket)
{
    SendMiniClientInfo();
    return 0;
}

int32_t CDaTingReward::onGetMiniClientReward(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    if (!m_pPlayer->IsMiniClient())
        return 2;

    int8_t nIndex = inPacket->readInt8();
    std::string platform = m_pPlayer->GetPlatform();
    const MiniClientCfg* pMiniCfg = CFG_DATA.GetMiniClientCfg(platform, nIndex);
    if (!pMiniCfg)
        return 2;

    // 检查条件
    switch (pMiniCfg->nType)
    {
    case 1:
        break;
    case 2:
        if (m_pPlayer->GetContinueLoginCount() < pMiniCfg->nParam)
            return 2;
        break;
    case 3:
        if (m_pPlayer->getLevel() < pMiniCfg->nParam)
            return 2;
        break;
    case 6:
        if (GetPlatformVipLevel() < pMiniCfg->nParam)
            return 2;
        break;
    case 7:
        if (GetPlatformVipLevel() < pMiniCfg->nParam || GetPlatformVipLevel() > pMiniCfg->nParam2)
            return 2;
        break;
    default:
        return 2;
    }

    int32_t nOldRecord = m_pPlayer->getRecord(1108);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord)
        return 2;

    CExtCharBag& pBag = m_pPlayer->GetBag();
    if (!pBag.AddItem(pMiniCfg->vItems, IACR_PALTFORM_DA_TING))
        return 2;

    m_pPlayer->updateRecord(1108, nNewRecord);
    SendMiniClientInfo();
    SendMiniClientIcon();
    return 0;
}
