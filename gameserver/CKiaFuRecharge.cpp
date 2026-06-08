#include "stdafx.h"
#include "CKiaFuRecharge.h"
#include "GameService.h"
#include "ItemHelper.h"
#include "Player.h"
#include "Bag.h"
#include "Currency.h"
#include "Timer.h"

using namespace Answer;

CKiaFuRecharge::CKiaFuRecharge()
{
    bzero(m_vStartDay, sizeof(m_vStartDay));
    bzero(m_vEndDay, sizeof(m_vEndDay));
    m_nDay = 0;
    m_nMinute = 0;
    m_nEndDay = 0;
    m_nIcon = 0;
    m_nSize = 0;
    m_nXiaoFeiSize = 0;
    m_ChouJiangIcon = 0;
}

CKiaFuRecharge::~CKiaFuRecharge()
{
}

void CKiaFuRecharge::Init()
{
    m_nDay = CFG_DATA.getServerDiffDay(0);
    const tm& nowTime = TIMER.GetLocalNow();
    m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
    initCfgData();
}

void CKiaFuRecharge::OnDaySwitch()
{
    m_nDay = CFG_DATA.getServerDiffDay(0);
    if (m_nDay == m_nEndDay)
        hideIcon(m_nIcon);
    if (m_nDay == m_vEndDay[3])
        hideIcon(m_ChouJiangIcon);
}

// ===== 配置加载 =====

void CKiaFuRecharge::initCfgData()
{
    Inifile ini;
    ini.parse("./ServerConfig/Tables/KaiFuRecharge.cfg");

    m_nEndDay = ini.getIntValue("CONFIG", "end_day");
    m_nIcon = ini.getIntValue("CONFIG", "icon");

    // RECHARGE_SUM
    m_vStartDay[1] = ini.getIntValue("RECHARGE_SUM", "start_day");
    m_vEndDay[1] = ini.getIntValue("RECHARGE_SUM", "end_day");
    m_nSize = ini.getIntValue("RECHARGE_SUM", "size");
    m_vSumGolds.clear();
    m_vSumGift.clear();
    for (int32_t i = 0; i < m_nSize; ++i)
    {
        char szCol[64] = {0};
        snprintf(szCol, sizeof(szCol) - 1, "gold%d", i);
        int32_t nGold = ini.getIntValue("RECHARGE_SUM", szCol);
        m_vSumGolds.push_back(nGold);

        bzero(szCol, sizeof(szCol));
        snprintf(szCol, sizeof(szCol) - 1, "gift%d", i);
        std::string strGift = ini.getStrValue("RECHARGE_SUM", szCol);
        MemChrBagVector items = CItemHelper::parseItemVectorString(strGift);
        m_vSumGift.push_back(items);
    }

    // LIAN_RECHARGE
    m_vStartDay[2] = ini.getIntValue("LIAN_RECHARGE", "start_day");
    m_vEndDay[2] = ini.getIntValue("LIAN_RECHARGE", "end_day");
    m_LianRechargeCfgVt.clear();
    for (int32_t i = 0; i <= 1; ++i)
    {
        LianRechargeCfg stu;
        char szCol[64] = {0};
        snprintf(szCol, sizeof(szCol) - 1, "type%d", i);
        stu.nValues = ini.getIntValue("LIAN_RECHARGE", szCol);

        for (int32_t j = 0; j <= 6; ++j)
        {
            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol) - 1, "gift%d_%d", i, j);
            std::string strGift = ini.getStrValue("LIAN_RECHARGE", szCol);
            if (!strGift.empty())
            {
                MemChrBagVector items = CItemHelper::parseItemVectorString(strGift);
                stu.vGiftVector.push_back(items);
            }
        }
        m_LianRechargeCfgVt.push_back(stu);
    }

    // CHOU_JIANG
    m_vStartDay[3] = ini.getIntValue("CHOU_JIANG", "start_day");
    m_vEndDay[3] = ini.getIntValue("CHOU_JIANG", "end_day");
    m_ChouJiangIcon = ini.getIntValue("CHOU_JIANG", "icon");

    // XIAO_FEI_SUM (note: the cfg uses LIAO_FEI_SUM typo)
    m_vStartDay[4] = ini.getIntValue("LIAO_FEI_SUM", "start_day");
    m_vEndDay[4] = ini.getIntValue("LIAO_FEI_SUM", "end_day");
    m_nXiaoFeiSize = ini.getIntValue("LIAO_FEI_SUM", "size");
    m_nValues.clear();
    m_vXiaoFeiSumGift.clear();
    m_vXiaoFeiGongGaoId.clear();
    for (int32_t i = 1; i <= m_nXiaoFeiSize; ++i)
    {
        char szCol[64] = {0};
        snprintf(szCol, sizeof(szCol) - 1, "value%d", i);
        int32_t nValue = ini.getIntValue("LIAO_FEI_SUM", szCol);
        m_nValues.push_back(nValue);

        bzero(szCol, sizeof(szCol));
        snprintf(szCol, sizeof(szCol) - 1, "gift%d", i);
        std::string strGift = ini.getStrValue("LIAO_FEI_SUM", szCol);
        MemChrBagVector items = CItemHelper::parseItemVectorString(strGift);
        m_vXiaoFeiSumGift.push_back(items);

        bzero(szCol, sizeof(szCol));
        snprintf(szCol, sizeof(szCol) - 1, "gonggao%d", i);
        int32_t nGongGao = ini.getIntValue("LIAO_FEI_SUM", szCol);
        m_vXiaoFeiGongGaoId.push_back(nGongGao);
    }
}

// ===== 时间检测 =====

bool CKiaFuRecharge::IsInTime() const
{
    if (CFG_DATA.getServerStartDayZeroTime() <= 1565107199)
        return false;
    return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CKiaFuRecharge::IsInTime(KAI_FU_RECHARGE_TYPE nType) const
{
    if (nType == KFRT_XIAO_FEI_SUM)
    {
        if (CFG_DATA.getServerStartTime() <= 1566316799)
            return false;
    }
    return m_nDay >= m_vStartDay[nType] && m_nDay < m_vEndDay[nType];
}

bool CKiaFuRecharge::needShowIcon() const
{
    if (CFG_DATA.getServerStartDayZeroTime() <= 1565107199)
        return false;
    return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CKiaFuRecharge::needShowShouJinagIcon() const
{
    if (CFG_DATA.getServerStartDayZeroTime() <= 1565107199)
        return false;
    return m_nDay >= m_vStartDay[3] && m_nDay < m_vEndDay[3];
}

int32_t CKiaFuRecharge::getLeftTime()
{
    if (!IsInTime())
        return 0;
    int32_t nNowTime = TIMER.GetNow();
    return 86400 * (m_nEndDay - m_nDay) - (nNowTime - DayTime::dayzero(nNowTime));
}

int32_t CKiaFuRecharge::GetChouJiangLeftTime()
{
    if (!IsInTime(KFRT_CHOU_JIANG))
        return 0;
    int32_t nNowTime = TIMER.GetNow();
    return 86400 * (m_vEndDay[3] - m_nDay) - (nNowTime - DayTime::dayzero(nNowTime));
}

// ===== 驱动事件 =====

void CKiaFuRecharge::OnRecharge(Player* player, int32_t OldValue, int32_t AddValue)
{
    if (!player)
        return;

    bool NeedSendIcon = false;

    if (IsInTime(KFRT_RECHARGE_SUM))
    {
        player->GetOperateLimit().AddLimitCount(1041, AddValue);
        NeedSendIcon = true;
    }

    if (IsInTime(KFRT_LIAN_RECHARGE))
    {
        if (m_LianRechargeCfgVt.size() > 0)
        {
            if (m_LianRechargeCfgVt[0].nValues > OldValue &&
                OldValue + AddValue >= m_LianRechargeCfgVt[0].nValues)
            {
                player->GetOperateLimit().AddLimitCount(1043, 1);
                NeedSendIcon = true;
            }
        }
        if (m_LianRechargeCfgVt.size() > 1)
        {
            if (m_LianRechargeCfgVt[1].nValues > OldValue &&
                OldValue + AddValue >= m_LianRechargeCfgVt[1].nValues)
            {
                player->GetOperateLimit().AddLimitCount(1045, 1);
                NeedSendIcon = true;
            }
        }
    }

    if (NeedSendIcon)
        SendIconState(player);
}

void CKiaFuRecharge::OnXiaoFeiSum(Player* player, int32_t AddTimes)
{
    if (!player)
        return;

    bool NeedSendIcon = false;

    if (IsInTime(KFRT_XIAO_FEI_SUM))
    {
        player->GetOperateLimit().AddLimitCount(1075, AddTimes);
        NeedSendIcon = true;
    }

    if (NeedSendIcon)
        SendIconState(player);
}

void CKiaFuRecharge::OnAddChouJiangTimes(Player* player, int32_t AddTimes)
{
    bool NeedSendIcon = false;

    if (IsInTime(KFRT_CHOU_JIANG))
    {
        player->GetOperateLimit().AddLimitCount(1047, AddTimes);
        NeedSendIcon = true;
    }

    if (NeedSendIcon)
        SendChouJiangIconState(player);
}

// ===== 奖励领取 =====

void CKiaFuRecharge::OnGetRechargeSumReward(Player* player, int32_t nIndex)
{
    if (!player)
        return;

    if (!IsInTime(KFRT_RECHARGE_SUM))
        return;

    if (nIndex < 0 || nIndex >= m_nSize)
        return;

    int32_t nRecord = player->getRecord(1042);
    int32_t nNewRecord = nRecord | (1 << nIndex);
    if (nNewRecord == nRecord)
        return;

    int32_t nRechargeSum = player->getRecord(1041);
    if (m_vSumGolds[nIndex] > nRechargeSum)
        return;

    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vSumGift[nIndex], IDCR_KAI_FU_RECHARGE_SUM))
        return;

    player->updateRecord(1042, nNewRecord);
    GongGao(3012, player);
    SendIconState(player);
}

void CKiaFuRecharge::OnGetXiaoFeiReward(Player* player, int32_t nIndex)
{
    if (!player)
        return;

    if (!IsInTime(KFRT_XIAO_FEI_SUM))
        return;

    if (nIndex < 0 || nIndex >= m_nXiaoFeiSize)
        return;

    int32_t nXiaoFeiSum = player->getRecord(1075);
    if (nXiaoFeiSum < m_nValues[nIndex])
        return;

    int32_t nRecord = player->getRecord(1076);
    int32_t nNewRecord = nRecord | (1 << nIndex);
    if (nNewRecord == nRecord)
        return;

    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vXiaoFeiSumGift[nIndex], IDCR_KAI_FU_XIAO_FEI_SUM))
        return;

    player->updateRecord(1076, nNewRecord);

    if (nIndex < (int32_t)m_vXiaoFeiGongGaoId.size() && m_vXiaoFeiGongGaoId[nIndex] > 0)
        GongGao(m_vXiaoFeiGongGaoId[nIndex], player);

    SendIconState(player);
}

void CKiaFuRecharge::OnGetChouJiangReward(Player* player, int32_t nIndex)
{
    if (!player)
        return;

    if (!IsInTime(KFRT_CHOU_JIANG))
        return;

    const TreasureHunterCfg* pCurCfg = CFG_DATA.GetTreasureHunterCfg(nIndex);
    if (!pCurCfg)
        return;

    if (pCurCfg->nType != 1)
        return;

    if (player->getRecord(1047) < pCurCfg->nRequire)
        return;

    int32_t nRecord = player->getRecord(1048);
    int32_t nNewRecord = nRecord | (1 << (nIndex - 1));
    if (nNewRecord == nRecord)
        return;

    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(&pCurCfg->Items, IDCR_KAI_FU_CHOU_JIANG))
        return;

    player->updateRecord(1048, nNewRecord);
    GongGao(3013, player);
    SendChouJiangIconState(player);
}

void CKiaFuRecharge::GetLianRechargeReward(Player* player, int32_t nType, int32_t nIndex)
{
    if (!player)
        return;

    if (!IsInTime(KFRT_LIAN_RECHARGE))
        return;

    if (nType < 0 || nType >= (int32_t)m_LianRechargeCfgVt.size())
        return;

    int32_t nLianChongRecord = (nType == 1) ? 1045 : 1043;
    int32_t nRewardRecord = (nType == 1) ? 1046 : 1044;

    if (nIndex + 1 > player->getRecord(nLianChongRecord))
        return;

    int32_t nRecord = player->getRecord(nRewardRecord);
    int32_t nNewRecord = nRecord | (1 << nIndex);
    if (nNewRecord == nRecord)
        return;

    if (nIndex >= (int32_t)m_LianRechargeCfgVt[nType].vGiftVector.size())
        return;

    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_LianRechargeCfgVt[nType].vGiftVector[nIndex], IDCR_KAI_FU_RECHARGE_SUM))
        return;

    player->updateRecord(nRewardRecord, nNewRecord);
    GongGao(3012, player);
    SendIconState(player);
}

// ===== 查询 =====

int32_t CKiaFuRecharge::HaveRechargeRewardCount(Player* player)
{
    if (!player)
        return 0;

    int32_t nCount = 0;

    if (IsInTime(KFRT_RECHARGE_SUM))
    {
        int32_t nRechargeSum = player->getRecord(1041);
        int32_t nRewardRecord = player->getRecord(1042);
        for (size_t i = 0; i < m_vSumGolds.size(); ++i)
        {
            if (m_vSumGolds[i] <= nRechargeSum)
            {
                int32_t nNewRecord = nRewardRecord | (1 << i);
                if (nNewRecord != nRewardRecord)
                    ++nCount;
            }
        }
    }

    if (IsInTime(KFRT_XIAO_FEI_SUM))
    {
        int32_t nXiaoFeiSum = player->getRecord(1075);
        int32_t nRewardRecord = player->getRecord(1076);
        for (size_t i = 0; i < m_nValues.size(); ++i)
        {
            if (m_nValues[i] <= nXiaoFeiSum)
            {
                int32_t nNewRecord = nRewardRecord | (1 << i);
                if (nNewRecord != nRewardRecord)
                    ++nCount;
            }
        }
    }

    if (IsInTime(KFRT_LIAN_RECHARGE))
    {
        int32_t nActCount0 = player->getRecord(1043);
        int32_t nOldRecord0 = player->getRecord(1044);
        for (int32_t i = 0; i < nActCount0; ++i)
        {
            int32_t nNewRecord = nOldRecord0 | (1 << i);
            if (nNewRecord != nOldRecord0)
                ++nCount;
        }

        int32_t nActCount1 = player->getRecord(1045);
        int32_t nOldRecord1 = player->getRecord(1046);
        for (int32_t i = 0; i < nActCount1; ++i)
        {
            int32_t nNewRecord = nOldRecord1 | (1 << i);
            if (nNewRecord != nOldRecord1)
                ++nCount;
        }
    }

    return nCount;
}

int32_t CKiaFuRecharge::HaveChouJiangCount(Player* player)
{
    if (!player)
        return 0;

    int32_t nCount = 0;

    if (IsInTime(KFRT_CHOU_JIANG))
    {
        int32_t nChouJiangTimes = player->getRecord(1047);
        int32_t nRewardRecord = player->getRecord(1048);

        const TreasureHunterCfgMap* pMap = CFG_DATA.GetTreasureHunterCfgMap();
        if (pMap)
        {
            for (TreasureHunterCfgMap::const_iterator it = pMap->begin();
                 it != pMap->end(); ++it)
            {
                if (it->second.nType == 1 && it->second.nRequire <= nChouJiangTimes)
                {
                    int32_t nNewRecord = nRewardRecord | (1 << (it->first - 1));
                    if (nNewRecord != nRewardRecord)
                        ++nCount;
                }
            }
        }
    }

    return nCount;
}

// ===== 图标状态 =====

void CKiaFuRecharge::getIconState(ShowIcon& icon, Player* player)
{
    icon.nId = m_nIcon;
    icon.nState = 1;
}

void CKiaFuRecharge::GetIconState(Player* player, IconStateList& IconList)
{
    if (player && needShowIcon())
    {
        ShowIcon icon;
        getIconState(icon, player);
        IconList.push_back(icon);
    }
}

void CKiaFuRecharge::SendIconState(Player* player)
{
    if (player && needShowIcon())
    {
        ShowIcon icon;
        getIconState(icon, player);
        Answer::NetPacket* pPacket = GAME_SERVICE.popNetpacket(player->getConnId(), Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
        if (pPacket)
        {
            pPacket->writeInt32(icon.nId);
            pPacket->writeInt8(icon.nState);
            pPacket->writeInt32(icon.nLeftTime);
            pPacket->writeInt8(icon.IconLeft);
            pPacket->writeInt32(icon.IconRight);
            pPacket->writeInt8(icon.Effects);
            pPacket->setSize(pPacket->getWOffset());
            GAME_SERVICE.sendPacketTo(player->getConnId(), player->getGateIndex(), pPacket);
        }
    }
}

void CKiaFuRecharge::getChouJiangIconState(ShowIcon& icon, Player* player)
{
    icon.nId = m_ChouJiangIcon;
    icon.nState = 1;
}

void CKiaFuRecharge::GetChouJiangIconState(Player* player, IconStateList& IconList)
{
    if (player && needShowShouJinagIcon())
    {
        ShowIcon icon;
        getChouJiangIconState(icon, player);
        IconList.push_back(icon);
    }
}

void CKiaFuRecharge::SendChouJiangIconState(Player* player)
{
    if (player && needShowShouJinagIcon())
    {
        ShowIcon icon;
        getChouJiangIconState(icon, player);
        Answer::NetPacket* pPacket = GAME_SERVICE.popNetpacket(player->getConnId(), Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
        if (pPacket)
        {
            pPacket->writeInt32(icon.nId);
            pPacket->writeInt8(icon.nState);
            pPacket->writeInt32(icon.nLeftTime);
            pPacket->writeInt8(icon.IconLeft);
            pPacket->writeInt32(icon.IconRight);
            pPacket->writeInt8(icon.Effects);
            pPacket->setSize(packet->getWOffset());
            GAME_SERVICE.sendPacketTo(player->getConnId(), player->getGateIndex(), pPacket);
        }
    }
}

void CKiaFuRecharge::hideIcon(int32_t nIconId)
{
    if (GAME_SERVICE.getLine() != 1)
        return;

    ShowIcon icon;
    icon.nId = nIconId;
    icon.nState = 4;
    icon.nLeftTime = 0;
    icon.IconRight = 0;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PACK_DISPATCH, 0x2CC3);
    if (packet)
    {
        packet->writeInt32(icon.nId);
        packet->writeInt8(icon.nState);
        packet->writeInt32(icon.nLeftTime);
        packet->writeInt8(icon.IconLeft);
        packet->writeInt32(icon.IconRight);
        packet->writeInt8(icon.Effects);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.worldBroadcast(0, packet);
    }
}

void CKiaFuRecharge::GongGao(int32_t GongGaoId, Player* player)
{
    if (!player)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PACK_DISPATCH, 0x2CD6);
    if (packet)
    {
        packet->writeInt32(GongGaoId);
        packet->writeUTF8(player->getName());
        packet->writeInt64(player->getCid());
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.worldBroadcast(0, packet);
    }
}
