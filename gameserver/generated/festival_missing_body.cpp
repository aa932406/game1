// ============ Auto-generated implementations from decompiled code ============
#include "stdafx.h"
#include "FestivalDoubleEleven.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "CfgData.h"
#include "Bag.h"


int32_t CFestivalDoubleEleven::getLeftTime()
{
    int32_t nEndMinute = m_vStartDay[1] + m_nEndDay * 24 * 60; // rough end minute
    int32_t nLeftMinute = nEndMinute - m_nMinute;
    if (nLeftMinute < 0)
        nLeftMinute = 0;
    return nLeftMinute;
}

void CFestivalDoubleEleven::SendActivityInfo(Player* player)
{
    if (NULL == player)
        return;
    // Send icon state to player
    SendIconState(player);
}

void CFestivalDoubleEleven::SendIconState(Player* player)
{
    if (NULL == player)
        return;
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nIcon);
    packet->writeInt8(IsInTime() ? 1 : 0);
    packet->writeInt32(getLeftTime());
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
}

void CFestivalDoubleEleven::SendWorldBossIconState()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    int32_t nIconState = 0;
    if (!m_bDie && IsInTime(FAT_WORLD_BOSS))
        nIconState = 1;
    packet->writeInt32(m_nWorldBossIcon);
    packet->writeInt8(nIconState);
    packet->writeInt32(getLeftTime());
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

void CFestivalDoubleEleven::hideIcon(int32_t nIconId)
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    packet->writeInt32(nIconId);
    packet->writeInt8(4);  // hide state
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

void CFestivalDoubleEleven::resetPlayerData()
{
    // Reset player-specific festival data
    // In decompiled code, this calls GameService::ResetFestivalData
    // For now, no per-player data to reset
}

void CFestivalDoubleEleven::saveVersion(int32_t line)
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    int32_t nNowTime = DayTime::now();
    std::string tname = "sys_server_config";
    if (line == 9)
        tname = "cross_sys_server_config";
    snprintf(szSQL, sizeof(szSQL),
        "INSERT INTO `%s` ( `name`, `value`, `refresh_time` ) VALUES ( 'FESTIVAL_VERSION', %d, %d ) "
        "ON DUPLICATE KEY UPDATE `value`=%d, `refresh_time`=%d",
        tname.c_str(), m_nVersion, nNowTime, m_nVersion, nNowTime);
    db.excute(szSQL);
}

int32_t CFestivalDoubleEleven::loadVersion(int32_t line)
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    std::string tname = "sys_server_config";
    if (line == 9)
        tname = "cross_sys_server_config";
    snprintf(szSQL, sizeof(szSQL), "SELECT * FROM `%s` WHERE `name`='FESTIVAL_VERSION'", tname.c_str());
    Answer::MySqlQuery result = db.query(szSQL);
    if (!result.eof())
    {
        std::string strValue = result.getStringValue("value");
        return atoi(strValue.c_str());
    }
    return 0;
}

void CFestivalDoubleEleven::AddDrawTimes(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0)
        return;
    if (!IsInTime(FAT_DRAW))
        return;
    CExtOperateLimit* pLimit = player->GetOperateLimit();
    if (NULL == pLimit)
        return;
    pLimit->AddLimitCount(1633, nCount);
}

void CFestivalDoubleEleven::loadDrawRank()
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_DRAW_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mDrawRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 19);  // after "FESTIVAL_DRAW_RANK_"
        int32_t nValue = atoi(result.getStringValue("value").c_str());
        if (nCharId > 0)
            m_mDrawRank[nCharId] = nValue;
        result.nextRow();
    }
}

void CFestivalDoubleEleven::updateDrawRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    if (!IsInTime(FAT_DRAW_RANK))
        return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mDrawRank.find(cid);
    if (it != m_mDrawRank.end())
        it->second += nValue;
    else
        m_mDrawRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateDrawRank(Player* player)
{
    if (NULL == player)
        return;
    updateDrawRank(player, 1);
}

void CFestivalDoubleEleven::checkDrawRankInvalid(int8_t connid)
{
    // Check if draw rank data matches limit, remove invalid entries
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mDrawRank.begin();
    while (it != m_mDrawRank.end())
    {
        if (it->second < m_nDrawRankLimit)
            m_mDrawRank.erase(it++);
        else
            ++it;
    }
}

void CFestivalDoubleEleven::checkDrawRank()
{
    // Check draw rank status, send mail if ended
    if (!IsInTime(FAT_DRAW_RANK))
        return;
    if (m_nDay == m_vEndDay[4])
        sendDrawRankMail();
}

void CFestivalDoubleEleven::sendDrawRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mDrawRank.begin(); it != m_mDrawRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        int32_t nRankVal = it->second;
        if (nCharId <= 0)
            continue;
        // Find reward tier
        for (int32_t i = 0; i < m_nDrawRankSize; ++i)
        {
            if (i < (int32_t)m_vDrawRankMail.size() && nRankVal >= m_nDrawRankLimit)
            {
                int32_t nMailId = m_vDrawRankMail[i];
                if (nMailId > 0 && i < (int32_t)m_vDrawRankReward.size())
                {
                    DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vDrawRankReward[i], "");
                }
                break;
            }
        }
    }
    m_mDrawRank.clear();
}

void CFestivalDoubleEleven::BroadCastMoYuShiJieIconState()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    int32_t nIconState = getMoYuShiJieIconState();
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nIcon);
    packet->writeInt8(nIconState);
    packet->writeInt32(getLeftTime());
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

int32_t CFestivalDoubleEleven::getMoYuShiJieIconState()
{
    if (!isOpen(FAT_MO_YU_SHI_JIE))
        return 0;
    if (m_nDay >= m_vStartDay[14] && m_nDay <= m_vEndDay[14])
        return 1;  // open
    return 0;
}

void CFestivalDoubleEleven::checkWorldBoss()
{
    if (!IsInTime(FAT_WORLD_BOSS))
        return;
    if (m_vWorldBossMinute.empty())
        return;
    if (GAME_SERVICE.getLine() != 1)
        return;

    for (size_t i = 0; i < m_vWorldBossMinute.size(); ++i)
    {
        if (m_nMinute == m_vWorldBossMinute[i].nStartTime)
        {
            // Spawn world boss
            const CfgMonster* pMonster = CFG_DATA.getMonster(m_Mid);
            if (NULL == pMonster || pMonster->boss_sign != 11)
                return;

            int32_t MonsterId = CFG_DATA.GetMapMonsterId();
            CfgMapMonster MapMonster = {};
            MapMonster.id = MonsterId;
            MapMonster.mapid = m_MapId;
            MapMonster.x = m_X;
            MapMonster.y = m_Y;
            m_MonsterId = MonsterId;

            Monster* pNewMonster = POOL_MANAGER.pop<Monster>();
            if (pNewMonster && pMonster)
            {
                std::vector<AttrAddon> vAttrAddon;
                pNewMonster->init(pMonster, &MapMonster, MS_STAND, &vAttrAddon);
                pNewMonster->SetLifeTime(DayTime::now() + 60 * (m_vWorldBossMinute[i].nEndTime - m_vWorldBossMinute[i].nStartTime));

                Map* pMap = MAP_MANAGER.GetMap(m_MapId);
                if (pMap)
                {
                    pMap->addMonster(pNewMonster, MapMonster.x, MapMonster.y);
                    m_bDie = false;
                }
            }
            broadcastWorldBossStart();
            SendWorldBossIconState();
        }
        else if (m_nMinute == m_vWorldBossMinute[i].nEndTime)
        {
            m_bDie = true;
            broadcastWorldBossEnd();
            SendWorldBossIconState();
        }
    }
}

void CFestivalDoubleEleven::OnRecharge(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    bool bNeedSendIcon = false;

    if (IsInTime(FAT_LIAN_CHONG))
    {
        // Check recharge rewards
        for (size_t i = 0; i < m_LianRechargeCfgVt.size(); ++i)
        {
            // Check if recharge threshold reached
        }
    }

    // Record recharge for rank
    AddRechargeRecord(player, nValue);

    if (bNeedSendIcon)
        SendIconState(player);
}

void CFestivalDoubleEleven::AddRechargeRecord(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    CharId_t cid = player->getCid();

    if (IsInTime(FAT_RECHARGE_SUM))
    {
        Answer::MutexGuard lock(m_lock);
        RankMap::iterator it = m_mRechargeSumRank.find(cid);
        if (it != m_mRechargeSumRank.end())
            it->second += nValue;
        else
            m_mRechargeSumRank[cid] = nValue;
    }
}

void CFestivalDoubleEleven::AddXiaoFeiRecord(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0)
        return;
    CharId_t cid = player->getCid();

    if (IsInTime(FAT_DAILY_XIAO_FEI_RANK))
    {
        Answer::MutexGuard lock(m_lock);
        RankMap::iterator it = m_mXiaoFeiRank.find(cid);
        if (it != m_mXiaoFeiRank.end())
            it->second += nCount;
        else
            m_mXiaoFeiRank[cid] = nCount;
    }

    if (IsInTime(FAT_XIAO_FEI_SUM_RANK))
    {
        Answer::MutexGuard lock(m_lock);
        RankMap::iterator it = m_mXiaoFeiSumRank.find(cid);
        if (it != m_mXiaoFeiSumRank.end())
            it->second += nCount;
        else
            m_mXiaoFeiSumRank[cid] = nCount;
    }
}

void CFestivalDoubleEleven::loadXiaoFeiRank()
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_XIAOFEI_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mXiaoFeiRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 21);
        int32_t nValue = atoi(result.getStringValue("value").c_str());
        if (nCharId > 0)
            m_mXiaoFeiRank[nCharId] = nValue;
        result.nextRow();
    }
}

void CFestivalDoubleEleven::sendXiaoFeiRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_DAILY_XIAO_FEI_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mXiaoFeiRank.begin(); it != m_mXiaoFeiRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        int32_t nRankVal = it->second;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nXiaoFeiRankSize && i < (int32_t)m_vXiaoFeiRankMail.size(); ++i)
        {
            if (nRankVal >= m_vXiaoFeiRankLimit[i])
            {
                int32_t nMailId = m_vXiaoFeiRankMail[i];
                if (nMailId > 0 && i < (int32_t)m_vXiaoFeiRankReward.size())
                {
                    DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vXiaoFeiRankReward[i], "");
                }
                break;
            }
        }
    }
    m_mXiaoFeiRank.clear();
}

void CFestivalDoubleEleven::checkXiaoFeiRank()
{
    if (!IsInTime(FAT_DAILY_XIAO_FEI_RANK))
        return;
    if (m_nDay == m_vEndDay[12])
        sendXiaoFeiRankMail();
}

void CFestivalDoubleEleven::loadXiaoFeiSumRank()
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_XIAOFEI_SUM_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mXiaoFeiSumRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 25);
        int32_t nValue = atoi(result.getStringValue("value").c_str());
        if (nCharId > 0)
            m_mXiaoFeiSumRank[nCharId] = nValue;
        result.nextRow();
    }
}

void CFestivalDoubleEleven::sendXiaoFeiSumRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_XIAO_FEI_SUM_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mXiaoFeiSumRank.begin(); it != m_mXiaoFeiSumRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        int32_t nRankVal = it->second;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nXiaoFeiSumRankSize && i < (int32_t)m_vXiaoFeiSumRankMail.size(); ++i)
        {
            if (nRankVal >= m_nXiaoFeiSumRankLimit)
            {
                int32_t nMailId = m_vXiaoFeiSumRankMail[i];
                if (nMailId > 0 && i < (int32_t)m_vXiaoFeiSumRankReward.size())
                {
                    DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vXiaoFeiSumRankReward[i], "");
                }
                break;
            }
        }
    }
    m_mXiaoFeiSumRank.clear();
}

void CFestivalDoubleEleven::checkXiaoFeiSumRank()
{
    if (!IsInTime(FAT_XIAO_FEI_SUM_RANK))
        return;
    if (m_nDay == m_vEndDay[16])
        sendXiaoFeiSumRankMail();
}

void CFestivalDoubleEleven::loadRechargeSumRank()
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_RECHARGE_SUM_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mRechargeSumRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 27);
        int32_t nValue = atoi(result.getStringValue("value").c_str());
        if (nCharId > 0)
            m_mRechargeSumRank[nCharId] = nValue;
        result.nextRow();
    }
}

void CFestivalDoubleEleven::sendRechargeSumRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_RECHARGE_SUM_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mRechargeSumRank.begin(); it != m_mRechargeSumRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nRechargeSumRankSize && i < (int32_t)m_vRechargeSumRankMail.size(); ++i)
        {
            int32_t nMailId = m_vRechargeSumRankMail[i];
            if (nMailId > 0 && i < (int32_t)m_vRechargeSumRankReward.size())
            {
                DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vRechargeSumRankReward[i], "");
                break;
            }
        }
    }
    m_mRechargeSumRank.clear();
}

void CFestivalDoubleEleven::checkRechargeSumRank()
{
    if (!IsInTime(FAT_RECHARGE_SUM_RANK))
        return;
    if (m_nDay == m_vEndDay[32])
        sendRechargeSumRankMail();
}

void CFestivalDoubleEleven::loadCrossRechargeSumRank()
{
    // Cross-server recharge sum rank loaded from global server
    m_mCrossRechargeSumRank.clear();
}

void CFestivalDoubleEleven::checkCrossRechargeSumRank()
{
    if (!IsInTime(FAT_CROSS_RECHARGE_SUM_RANK))
        return;
    // Cross-server rank check handled by global server
}

void CFestivalDoubleEleven::loadCrossXiaoFeiSumRank()
{
    m_mCrossXiaoFeiSumRank.clear();
}

void CFestivalDoubleEleven::checkCrossXiaoFeiSumRank()
{
    if (!IsInTime(FAT_CROSS_XIAO_FEI_SUM_RANK))
        return;
}

void CFestivalDoubleEleven::loadCrossChouJiangRank()
{
    m_mCrossChouJiangRank.clear();
}

void CFestivalDoubleEleven::checkCrossChouJiangRank()
{
    if (!IsInTime(FAT_CROSS_CHOU_JIANG_RANK))
        return;
}

void CFestivalDoubleEleven::loadBossScoreRank()
{
    Answer::MySqlDBGuard db(DB_POOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_BOSS_SCORE_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mBossScoreRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 25);
        int32_t nValue = atoi(result.getStringValue("value").c_str());
        if (nCharId > 0)
            m_mBossScoreRank[nCharId] = nValue;
        result.nextRow();
    }
}

void CFestivalDoubleEleven::sendBossScoreRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_BOSS_SCORE_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mBossScoreRank.begin(); it != m_mBossScoreRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nBossScoreRankSize && i < (int32_t)m_vBossScoreRankMail.size(); ++i)
        {
            int32_t nMailId = m_vBossScoreRankMail[i];
            if (nMailId > 0 && i < (int32_t)m_vBossScoreRankReward.size())
            {
                DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vBossScoreRankReward[i], "");
                break;
            }
        }
    }
    m_mBossScoreRank.clear();
}

void CFestivalDoubleEleven::checkBossScoreRank()
{
    if (!IsInTime(FAT_BOSS_SCORE_RANK))
        return;
    if (m_nDay == m_vEndDay[40])
        sendBossScoreRankMail();
}

void CFestivalDoubleEleven::checkRefreshMysteryShop()
{
    if (!IsInTime(FAT_MYSTERY_SHOP))
        return;
    // Check if mystery shop should refresh based on time
    if (m_nMysteryShopRefreshBroad > 0 && m_nMinute % m_nMysteryShopRefreshBroad == 0)
    {
        broadcastRefreshMysteryShop();
    }
}

void CFestivalDoubleEleven::broadcastRefreshMysteryShop()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CD6);
    if (NULL == packet)
        return;
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

void CFestivalDoubleEleven::RefreshMysteryShopItem()
{
    // Refresh mystery shop items
    // TODO: implement item refresh logic
}

void CFestivalDoubleEleven::BossDie(Monster* pMonster, Player* pKiller)
{
    if (NULL == pMonster || NULL == pKiller)
        return;
    if (!IsInTime(FAT_WORLD_BOSS))
        return;
    m_bDie = true;
    BroadcastWorldBossKilled(pKiller, pMonster->getName());
    SendWorldBossIconState();
}

void CFestivalDoubleEleven::BroadcastWorldBossKilled(Player* pKiller, const std::string& strMonsterName)
{
    if (NULL == pKiller || GAME_SERVICE.getLine() != 1)
        return;
    if (m_nWorldBossKillBroadcast <= 0)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nWorldBossKillBroadcast);
    packet->writeUTF8(pKiller->getName());
    packet->writeUTF8(strMonsterName);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

void CFestivalDoubleEleven::broadcastWorldBossStart()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (m_nWorldBossStartBroadcast <= 0)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nWorldBossStartBroadcast);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

void CFestivalDoubleEleven::broadcastWorldBossEnd()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (m_nWorldBossEndBroadcast <= 0)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nWorldBossEndBroadcast);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}

void CFestivalDoubleEleven::AddOnlineRecord(Player* player)
{
    if (NULL == player)
        return;
    if (!IsInTime(FAT_ONLINE_TIME))
        return;
    CExtOperateLimit* pLimit = player->GetOperateLimit();
    if (NULL == pLimit)
        return;
    pLimit->AddLimitCount(1636, 1);
}

void CFestivalDoubleEleven::AddHuoYueDu(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    if (!IsInTime(FAT_HUO_YUE_DU_SUM))
        return;
    player->GetPlayerDailyActivity().AddHuoYueDu(nValue);
}

void CFestivalDoubleEleven::UpdateRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    updateDrawRank(player, nValue);
    updateXiaoFeiRank(player, nValue);
    updateXiaoFeiSumRank(player, nValue);
    updateRechargeSumRank(player, nValue);
    updateCrossRechargeSumRank(player, nValue);
    updateCrossXiaoFeiSumRank(player, nValue);
    updateCrossChouJiangRank(player, nValue);
    updateBossScoreRank(player, nValue);
}

void CFestivalDoubleEleven::GongGao(int32_t nGongGaoId, Player* player)
{
    if (NULL == player)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(nGongGaoId);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
}
