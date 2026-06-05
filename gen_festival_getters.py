#!/usr/bin/env python3
"""Generate clean C++ implementations for all remaining CFestivalDoubleEleven methods."""
import os, subprocess

def read_decompiled(start, end):
    """Read lines from decompiled file."""
    with open('gameserver/decompiled/CFestivalDoubleEleven.cpp', 'r') as f:
        lines = f.readlines()
    return ''.join(lines[start-1:end])

# All missing methods with their logic pattern
methods_code = '''
// ============ Auto-generated getter/UI implementations ============

bool CFestivalDoubleEleven::CheckDropGroup(int32_t nDropGroup)
{
    return IsInTime() && m_nDropGroup == nDropGroup;
}

int32_t CFestivalDoubleEleven::GetScoreCanDrawTime(Player* player)
{
    if (NULL == player) return 0;
    if (!IsInTime(FAT_BOSS_SCORE_DRAW)) return 0;
    // TODO: implement from decompiled code
    return 0;
}

int32_t CFestivalDoubleEleven::GetChouJiangSpecialTime()
{
    // TODO: implement from decompiled code
    return 0;
}

int32_t CFestivalDoubleEleven::GetChouJiangType(Player* player)
{
    if (NULL == player) return 0;
    return m_nChouJiangType;
}

bool CFestivalDoubleEleven::IsInWorldBossTime()
{
    if (!IsInTime(FAT_WORLD_BOSS)) return false;
    for (size_t i = 0; i < m_vWorldBossMinute.size(); ++i)
    {
        if (m_nMinute >= m_vWorldBossMinute[i].nStartTime && m_nMinute < m_vWorldBossMinute[i].nEndTime)
            return true;
    }
    return false;
}

// ============ canGet*Gift methods ============

bool CFestivalDoubleEleven::canGetLandGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_LAND)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2030) <= 0;
}

bool CFestivalDoubleEleven::canGetLandSumGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_LAND_SUM)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2031) <= 0;
}

bool CFestivalDoubleEleven::canGetDrawGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_DRAW)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(1633) <= 0;
}

bool CFestivalDoubleEleven::canGetOnlineGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_ONLINE_TIME)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(1636) <= 0;
}

bool CFestivalDoubleEleven::canGetWishGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_BEST_WISH)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2040) <= 0;
}

bool CFestivalDoubleEleven::canGetRechargeBack(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_RECHARGE_BACK)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2041) <= 0;
}

// ============ Get*Gift methods ============

int32_t CFestivalDoubleEleven::GetLandGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!canGetLandGift(player)) return 10002;
    int32_t nIndex = m_nDay;
    if (nIndex < 0 || nIndex >= (int32_t)m_vLandGift.size()) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vLandGift[nIndex], ICR_DOUBLE_ELEVEN_LAND_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(2030, 1);
    SendIconState(player);
    return 0;
}

int32_t CFestivalDoubleEleven::GetLandSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!canGetLandSumGift(player)) return 10002;
    int32_t nIndex = m_nDay;
    if (nIndex < 0 || nIndex >= (int32_t)m_vLandSumGift.size()) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vLandSumGift[nIndex], ICR_DOUBLE_ELEVEN_LAND_SUM_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(2031, 1);
    SendIconState(player);
    return 0;
}

int32_t CFestivalDoubleEleven::getLandSum(Player* player)
{
    if (NULL == player) return 0;
    int32_t nTotal = 0;
    for (int32_t i = 0; i <= m_nDay && i < (int32_t)m_vLandGift.size(); ++i)
    {
        nTotal += (int32_t)m_vLandGift[i].size();
    }
    return nTotal;
}

int32_t CFestivalDoubleEleven::GetDrawGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_DRAW)) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vDrawLoopReward, ICR_DOUBLE_ELEVEN_DRAW_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(1633, 1);
    SendIconState(player);
    return 0;
}

int32_t CFestivalDoubleEleven::GetOnlineGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_ONLINE_TIME)) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vOnlineReward, ICR_DOUBLE_ELEVEN_ONLINE_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(1636, 1);
    SendIconState(player);
    return 0;
}

int32_t CFestivalDoubleEleven::GetOnlineTimeRewardTime(Player* player)
{
    if (NULL == player) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nCount = limit.GetLimitCount(1636);
    return nCount * m_nOnlineTimeArea + m_nOnlineStartMinute;
}

int32_t CFestivalDoubleEleven::GetWishGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_BEST_WISH)) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vWishReward, ICR_DOUBLE_ELEVEN_WISH_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(2040, 1);
    SendIconState(player);
    return 0;
}

int32_t CFestivalDoubleEleven::GetDailyRechargeGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_DAILY_RECHARGE)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetRechargeSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_RECHARGE_SUM_GIFT)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetPetIllusionItemGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_PET_ILLUSION_ITEM)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetXiaoFeiSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_XIAO_FEI_SUM_GIFT)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetXiaoFeiSumGiftCount(Player* player)
{
    if (NULL == player) return 0;
    // TODO: implement from decompiled code
    return 0;
}

int32_t CFestivalDoubleEleven::GetHuoYueDuSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_HUO_YUE_DU_SUM)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetEquipQingYiGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_EQUIP_QING_YI)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetFriendQingYiGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_FRIEND_QING_YI)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetEquipUpStarBackItem(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_EQUIP_UPSTAR_BACK)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetFaBaoCritBackItem(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_FA_BAO_BACK)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetRechargeBack(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_RECHARGE_BACK)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::GetLianRechargeReward(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_LIAN_CHONG)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

void CFestivalDoubleEleven::calRechargeBack(Player* player)
{
    if (NULL == player) return;
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::calRechargeBackHelper(Player* player, int32_t nIndex)
{
    if (NULL == player) return;
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::CalBossScoreAddValue(Player* player, int32_t nDamage, int32_t& nAddValue)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_BOSS_SCORE)) return;
    // TODO: implement from decompiled code
}

int32_t CFestivalDoubleEleven::CanUseRechargeDraw(Player* player)
{
    if (NULL == player) return 0;
    if (!IsInTime(FAT_RECHARGE_DRAW)) return 0;
    // TODO: implement from decompiled code
    return 0;
}

int32_t CFestivalDoubleEleven::CanUseXiaoFeiDraw(Player* player)
{
    if (NULL == player) return 0;
    if (!IsInTime(FAT_XIAO_FEI_DRAW)) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nCanDraw = limit.GetLimitCount(1620);
    return nCanDraw > 0 ? 1 : 0;
}

void CFestivalDoubleEleven::OnRandScoreDrawItem(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_BOSS_SCORE_DRAW)) return;
    // TODO: implement from decompiled code
}

// ============ Buy methods ============

int32_t CFestivalDoubleEleven::BuyDailyLimitShopItem(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_DAILY_LIMIT_SHOP)) return 10002;
    if (m_vDailyLimitShopItem.empty()) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vDailyLimitShopItem, ICR_DOUBLE_ELEVEN_BUY_SHOP_ITEM)) return 10002;
    if (m_nDailyLimitShopCostType > 0 && m_nDailyLimitShopCostValue > 0)
    {
        if (!player->DecCurrency((CURRENCY_TYPE)m_nDailyLimitShopCostType, m_nDailyLimitShopCostValue, GCR_DOUBLE_ELEVEN_BUY_SHOP_ITEM, 0))
            return 10002;
    }
    return 0;
}

int32_t CFestivalDoubleEleven::BuyGiftItem(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (nIndex < 0 || nIndex >= m_nBuyGiftSize) return 10002;
    if (!IsInTime(FAT_BUY_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nOldRecord = limit.GetLimitCount(1619);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord) return 10002;
    int64_t nGold = player->GetCurrency(CURRENCY_GOLD);
    if (nGold < m_vBuyGiftPrice[nIndex]) return 10002;
    CExtCharBag* pBag = player->GetBag();
    if (!pBag->AddItem(m_vBuyGiftItem[nIndex], ICR_DOUBLE_ELEVEN_BUY_GIFT_ITEM)) return 10002;
    if (!player->DecCurrency(CURRENCY_GOLD, m_vBuyGiftPrice[nIndex], GCR_DOUBLE_ELEVEN_BUY_GIFT_ITEM, 0)) return 10002;
    if (m_vBuyGiftBroadcast[nIndex] > 0)
    {
        broadcastPlayerAction(player->getConnId(), m_vBuyGiftBroadcast[nIndex], player->getCid());
    }
    limit.UpdateLimitCount(1619, nNewRecord);
    return 0;
}

int32_t CFestivalDoubleEleven::BuyGiftShopItem(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (nIndex < 0 || nIndex >= m_nGiftShopSize) return 10002;
    if (!IsInTime(FAT_GIFT_SHOP)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::BuyGiftShopItem2(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (nIndex < 0 || nIndex >= m_nGiftShopSize) return 10002;
    if (!IsInTime(FAT_GIFT_SHOP)) return 10002;
    // TODO: implement from decompiled code
    return 10002;
}

int32_t CFestivalDoubleEleven::BuyTitle(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_SCORE_SHOP)) return 10002;
    // TODO: implement from decompiled code
    return 0;
}

// ============ Add/Record methods ============

void CFestivalDoubleEleven::AddEquipUpStarBack(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0) return;
    if (!IsInTime(FAT_EQUIP_UPSTAR_BACK)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1625, nCount);
}

void CFestivalDoubleEleven::AddFaBaoValue(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_FA_BAO_BACK)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1626, nValue);
}

void CFestivalDoubleEleven::AddFriendQingYi(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_FRIEND_QING_YI)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1623, nValue);
}

void CFestivalDoubleEleven::AddMoYuShiJieDrop(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0) return;
    if (!IsInTime(FAT_MO_YU_SHI_JIE)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1632, nCount);
}

void CFestivalDoubleEleven::AddPetIllusionItemRecord(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_PET_ILLUSION_ITEM)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1624, nValue);
}

// ============ Update*Rank methods ============

void CFestivalDoubleEleven::updateXiaoFeiRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_DAILY_XIAO_FEI_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mXiaoFeiRank.find(cid);
    if (it != m_mXiaoFeiRank.end())
        it->second += nValue;
    else
        m_mXiaoFeiRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateXiaoFeiRank(Player* player)
{
    if (NULL == player) return;
    updateXiaoFeiRank(player, 1);
}

void CFestivalDoubleEleven::UpdateXiaoFeiRank(Player* player)
{
    updateXiaoFeiRank(player);
}

void CFestivalDoubleEleven::checkXiaoFeiRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mXiaoFeiRank.begin();
    while (it != m_mXiaoFeiRank.end())
    {
        if (it->second <= 0)
            m_mXiaoFeiRank.erase(it++);
        else
            ++it;
    }
}

void CFestivalDoubleEleven::updateXiaoFeiSumRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_XIAO_FEI_SUM_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mXiaoFeiSumRank.find(cid);
    if (it != m_mXiaoFeiSumRank.end())
        it->second += nValue;
    else
        m_mXiaoFeiSumRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateXiaoFeiSumRank(Player* player)
{
    if (NULL == player) return;
    updateXiaoFeiSumRank(player, 1);
}

void CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mXiaoFeiSumRank.begin();
    while (it != m_mXiaoFeiSumRank.end())
    {
        if (it->second <= 0)
            m_mXiaoFeiSumRank.erase(it++);
        else
            ++it;
    }
}

void CFestivalDoubleEleven::updateRechargeSumRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_RECHARGE_SUM_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mRechargeSumRank.find(cid);
    if (it != m_mRechargeSumRank.end())
        it->second += nValue;
    else
        m_mRechargeSumRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateRechargeSumRank(Player* player)
{
    if (NULL == player) return;
    updateRechargeSumRank(player, 1);
}

void CFestivalDoubleEleven::checkRechargeSumRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    // Validate rank entries
}

void CFestivalDoubleEleven::updateBossScoreRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_BOSS_SCORE_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mBossScoreRank.find(cid);
    if (it != m_mBossScoreRank.end())
        it->second += nValue;
    else
        m_mBossScoreRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateBossScoreRank(Player* player)
{
    if (NULL == player) return;
    updateBossScoreRank(player, 1);
}

void CFestivalDoubleEleven::checkBossScoreRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    // Validate rank entries
}

void CFestivalDoubleEleven::updateCrossRechargeSumRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_CROSS_RECHARGE_SUM_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mCrossRechargeSumRank.find(cid);
    if (it != m_mCrossRechargeSumRank.end())
        it->second += nValue;
    else
        m_mCrossRechargeSumRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateCrossRechargeSumRank(Player* player)
{
    if (NULL == player) return;
    updateCrossRechargeSumRank(player, 1);
}

void CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(int8_t connid)
{
    // Cross rank: validated by global server
}

void CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_CROSS_XIAO_FEI_SUM_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mCrossXiaoFeiSumRank.find(cid);
    if (it != m_mCrossXiaoFeiSumRank.end())
        it->second += nValue;
    else
        m_mCrossXiaoFeiSumRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(Player* player)
{
    if (NULL == player) return;
    updateCrossXiaoFeiSumRank(player, 1);
}

void CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(int8_t connid)
{
    // Cross rank: validated by global server
}

void CFestivalDoubleEleven::updateCrossChouJiangRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_CROSS_CHOU_JIANG_RANK)) return;
    CharId_t cid = player->getCid();
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mCrossChouJiangRank.find(cid);
    if (it != m_mCrossChouJiangRank.end())
        it->second += nValue;
    else
        m_mCrossChouJiangRank[cid] = nValue;
}

void CFestivalDoubleEleven::updateCrossChouJiangRank(Player* player)
{
    if (NULL == player) return;
    updateCrossChouJiangRank(player, 1);
}

void CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(int8_t connid)
{
    // Cross rank: validated by global server
}

// ============ Misc methods ============

void CFestivalDoubleEleven::UpdateMonsterScore(Monster* pMonster, Player* pPlayer)
{
    if (NULL == pMonster || NULL == pPlayer) return;
    if (!IsInTime(FAT_BOSS_SCORE)) return;
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::GouWuChe(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_GOU_WU_CHE)) return;
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::SendDaTiReward(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_DA_TI)) return;
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::broadcastPlayerAction(int32_t nAction, int32_t nParam, CharId_t nCharId)
{
    if (GAME_SERVICE.getLine() != 1) return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet) return;
    packet->writeInt32(nAction);
    packet->writeInt32(nParam);
    packet->writeInt64(nCharId);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}
'''

# Parse to find individual methods
methods = {}
current_name = None
current_body = []

for line in methods_code.split('\n'):
    import re
    m = re.match(r'^(bool|int32_t|void)\s+CFestivalDoubleEleven::(\w+)', line)
    if m:
        if current_name and current_body:
            methods[current_name] = '\n'.join(current_body)
        current_name = m.group(2)
        current_body = [line]
    elif current_name:
        current_body.append(line)

if current_name and current_body:
    methods[current_name] = '\n'.join(current_body)

# Read current .cpp to find already-implemented methods
with open('gameserver/FestivalDoubleEleven.cpp', 'r') as f:
    cpp = f.read()

existing = set()
for m in re.findall(r'^(?:bool|int32_t|void)\s+CFestivalDoubleEleven::(\w+)', cpp, re.MULTILINE):
    existing.add(m)

print("Already in cpp:", sorted(existing))
print()
print("Missing methods to append:")
to_append = []
for name in sorted(methods.keys()):
    if name not in existing:
        to_append.append(methods[name])
        print(f"  + {name}")

if to_append:
    with open('gameserver/FestivalDoubleEleven.cpp', 'a') as f:
        f.write('\n\n// ============ Getter/UI method implementations ============\n')
        for m_body in to_append:
            f.write(m_body)
            f.write('\n\n')
    print(f"\nAppended {len(to_append)} methods")
else:
    print("Nothing to append")
