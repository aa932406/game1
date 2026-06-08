#include "ShiZhuang.h"
#include "GameService.h"
#include "Bag.h"
#include "Currency.h"
#include "Timer.h"

using namespace Answer;

CExtCharShiZhuang::CExtCharShiZhuang()
    : m_LastUpdateTick(0)
    , m_EffectId(0)
{
}

CExtCharShiZhuang::~CExtCharShiZhuang()
{
}

void CExtCharShiZhuang::OnCleanUp()
{
    for (int8_t i = 0; i <= 2; ++i)
    {
        m_vShiZhuang[i].CleanUp();
    }
    m_LastUpdateTick = 0;
    m_ShiZhuangLevel.clear();
    m_SuitInfoMap.clear();
    m_EffectId = 0;
}

void CExtCharShiZhuang::OnLoadFromDB(const PlayerDBData* dbData)
{
    if (NULL == dbData)
    {
        return;
    }

    for (int8_t i = 0; i <= 2; ++i)
    {
        m_vShiZhuang[i].m_nWear = dbData->m_ShiZhuangData.m_vShiZhuang[i].m_nWear; m_vShiZhuang[i].m_nLevel = dbData->m_ShiZhuangData.m_vShiZhuang[i].m_nLevel; m_vShiZhuang[i].m_nExp = dbData->m_ShiZhuangData.m_vShiZhuang[i].m_nExp; m_vShiZhuang[i].m_lActive = dbData->m_ShiZhuangData.m_vShiZhuang[i].m_lActive;
    }
    m_ShiZhuangLevel.clear(); for (size_t si = 0; si < dbData->m_ShiZhuangData.m_ShiZhuangLevel.size(); si+=2) { m_ShiZhuangLevel[dbData->m_ShiZhuangData.m_ShiZhuangLevel[si]] = dbData->m_ShiZhuangData.m_ShiZhuangLevel[si+1]; };
    m_EffectId = dbData->m_ShiZhuangData.m_EffectId;

    CheckSuitInfo();
    CheckSuitEffect();
}

void CExtCharShiZhuang::OnSaveToDB(PlayerDBData* dbData)
{
    if (NULL == dbData)
    {
        return;
    }

    for (int8_t i = 0; i <= 2; ++i)
    {
        dbData->m_ShiZhuangData.m_vShiZhuang[i].m_nWear = m_vShiZhuang[i].m_nWear; dbData->m_ShiZhuangData.m_vShiZhuang[i].m_nLevel = m_vShiZhuang[i].m_nLevel; dbData->m_ShiZhuangData.m_vShiZhuang[i].m_nExp = m_vShiZhuang[i].m_nExp; dbData->m_ShiZhuangData.m_vShiZhuang[i].m_lActive = m_vShiZhuang[i].m_lActive;
    }
    dbData->m_ShiZhuangData.m_ShiZhuangLevel.clear(); for (std::map<int32_t,int32_t>::const_iterator si = m_ShiZhuangLevel.begin(); si != m_ShiZhuangLevel.end(); ++si) { dbData->m_ShiZhuangData.m_ShiZhuangLevel.push_back(si->first); dbData->m_ShiZhuangData.m_ShiZhuangLevel.push_back(si->second); };
    dbData->m_ShiZhuangData.m_EffectId = m_EffectId;
}

void CExtCharShiZhuang::OnUpdate(int64_t curTick)
{
    if (NULL == m_pPlayer || curTick - m_LastUpdateTick <= 59999)
    {
        return;
    }

    m_LastUpdateTick = curTick;
    int32_t Now = m_pPlayer->getNow();

    for (int8_t i = 0; i <= 2; ++i)
    {
        std::map<int32_t, int32_t>::iterator it = m_vShiZhuang[i].m_lActive.begin();
        while (it != m_vShiZhuang[i].m_lActive.end())
        {
            if (it->second > 0 && it->second < Now)
            {
                // 时装到期
                if (it->first == m_vShiZhuang[i].m_nWear)
                {
                    wear(i, 0);
                    sendShiZhuangInfo(i);
                }

                // 发送邮件续费通知
                std::stringstream ss;
                ss << it->first << "," << (int32_t)i;
                DB_SERVICE.OnSendSysMail(m_pPlayer->getConnId(), m_pPlayer->getCid(), 6396, ss.str(), 0);

                std::map<int32_t, int32_t>::iterator toErase = it;
                ++it;
                m_vShiZhuang[i].m_lActive.erase(toErase);
            }
            else
            {
                ++it;
            }
        }
    }
}

void CExtCharShiZhuang::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(CM_SHI_ZHUANG_REQUEST_INFO);
    procList.push_back(CM_SHI_ZHUANG_PEI_YANG);
    procList.push_back(CM_SHI_ZHUANG_WEAR);
    procList.push_back(CM_SHI_ZHUANG_LEVEL_UP);
}

int32_t CExtCharShiZhuang::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return ERR_INVALID_DATA;
    }

    switch (nProcId)
    {
    case CM_SHI_ZHUANG_REQUEST_INFO: return onRequestInfo(inPacket);
    case CM_SHI_ZHUANG_PEI_YANG:     return onPeiYang(inPacket);
    case CM_SHI_ZHUANG_WEAR:         return onWear(inPacket);
    case CM_SHI_ZHUANG_LEVEL_UP:     return onLevelUp(inPacket);
    default: return 0;
    }
}

int32_t CExtCharShiZhuang::onRequestInfo(Answer::NetPacket* inPacket)
{
    if (NULL == inPacket)
    {
        return ERR_INVALID_DATA;
    }

    int8_t nType = inPacket->readInt8();
    if (nType < 0 || nType > 2)
    {
        return ERR_INVALID_DATA;
    }

    sendShiZhuangInfo(nType);
    return 0;
}

int32_t CExtCharShiZhuang::onPeiYang(Answer::NetPacket* inPacket)
{
    if (NULL == inPacket || NULL == m_pPlayer)
    {
        return ERR_INVALID_DATA;
    }

    int8_t nType = inPacket->readInt8();
    int8_t nAutoBuy = inPacket->readInt8();
    int32_t nCount = inPacket->readInt32();

    Int32Vector vSlot;
    m_pPlayer->queryBagInfo(inPacket, vSlot);

    if (nType < 0 || nType > 2)
    {
        return ERR_INVALID_DATA;
    }

    if (m_vShiZhuang[nType].m_lActive.empty())
    {
        return ERR_INVALID_DATA;
    }

    if (nCount <= 0)
    {
        return ERR_INVALID_DATA;
    }

    // 多次培养需要VIP
    if (nCount > 1 && m_pPlayer->GetPlayerVip().GetVipLevel() <= 0)
    {
        return ERR_INVALID_DATA;
    }

    int32_t nLevel = m_vShiZhuang[nType].m_nLevel;
    const CfgShiZhuangLevel* pCfgLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangLevel(nType, nLevel);
    const CfgShiZhuangLevel* pCfgNextLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangLevel(nType, nLevel + 1);

    if (NULL == pCfgLevel || NULL == pCfgNextLevel)
    {
        return ERR_INVALID_DATA;
    }

    if (pCfgLevel->nLevelExp <= 0)
    {
        return ERR_INVALID_DATA;
    }

    // 检查等级需求
    if (m_pPlayer->getLevel() < pCfgLevel->nNeedLevel)
    {
        return ERR_INVALID_DATA;
    }

    // 扣除消耗物品
    ItemData costItem;
    costItem.m_nClass = 1;
    costItem.m_nId = pCfgLevel->nCostItem;
    costItem.m_nCount = nCount;

    if (nAutoBuy <= 0)
    {
        // 直接扣除背包
        if (!m_pPlayer->GetBag().RemoveItem(vSlot, costItem, IDCR_SHI_ZHUANG_PEI_YANG))
        {
            return ERR_INVALID_DATA;
        }
        m_pPlayer->GetBag().ForceSendDirty();
    }
    else
    {
        // 自动购买模式
        int32_t nBuyCount = 0;
        int32_t nItemCount = m_pPlayer->GetBag().GetItemCount(vSlot, costItem.m_nClass, costItem.m_nId);
        if (costItem.m_nCount > nItemCount)
        {
            nBuyCount = costItem.m_nCount - nItemCount;
            costItem.m_nCount = nItemCount;
        }

        int32_t nCostGold = 0;
        int32_t nShopId = 0;
        if (nBuyCount > 0)
        {
            const CfgGameShop* pCfgGameShop = CFG_DATA.GetGameShopItem(costItem.m_nClass, costItem.m_nId);
            if (NULL == pCfgGameShop)
            {
                return ERR_INVALID_DATA;
            }
            nShopId = pCfgGameShop->ShopId;
            nCostGold = nBuyCount * pCfgGameShop->Price;
            if (nCostGold <= 0)
            {
                return ERR_INVALID_DATA;
            }
            if (m_pPlayer->GetCurrency(CURRENCY_GOLD) < nCostGold)
            {
                return ERR_INVALID_DATA;
            }
        }

        if (costItem.m_nCount > 0)
        {
            if (!m_pPlayer->GetBag().RemoveItem(vSlot, costItem, IDCR_SHI_ZHUANG_PEI_YANG))
            {
                return ERR_INVALID_DATA;
            }
        }

        if (nCostGold > 0)
        {
            if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, nCostGold, GCR_SHI_ZHUANG_PEI_YANG, nShopId))
            {
                return ERR_INVALID_DATA;
            }
            m_pPlayer->GetCurrency().SynCurrency();
        }
    }

    // 计算暴击
    int8_t nCrit = 0;
    int32_t nTimes = 0;
    for (int32_t i = 0; i < nCount; ++i)
    {
        int32_t nRand = RANDOM.generate(0, 10000);
        if (nRand <= pCfgLevel->nLargeCritRate)
        {
            nTimes += 10;
            nCrit = 2;
        }
        else if (nRand <= pCfgLevel->nSmallCritRate)
        {
            nTimes += 2;
            if (nCrit == 0) nCrit = 1;
        }
        else
        {
            ++nTimes;
        }
    }

    int32_t nAddExp = nTimes * pCfgLevel->nGetExp;
    addShiZhuangExp(nType, nAddExp);
    sendShiZhuangPeiYangResult(nType, nAddExp, nCrit);
    return 0;
}

int32_t CExtCharShiZhuang::onWear(Answer::NetPacket* inPacket)
{
    if (NULL == inPacket || NULL == m_pPlayer)
    {
        return ERR_INVALID_DATA;
    }

    int8_t nType = inPacket->readInt8();
    int32_t nId = inPacket->readInt32();

    if (nType < 0 || nType > 2)
    {
        return ERR_INVALID_DATA;
    }

    if (nId < 0)
    {
        return ERR_INVALID_DATA;
    }

    if (nId > 0)
    {
        if (!m_vShiZhuang[nType].IsActive(nId))
        {
            return ERR_INVALID_DATA;
        }
    }
    else if (m_vShiZhuang[nType].m_nWear == 0)
    {
        return ERR_INVALID_DATA;
    }

    wear(nType, nId);
    if (nType == 1)
    {
        CheckSuitEffect();
    }
    sendShiZhuangInfo(nType);
    return 0;
}

int32_t CExtCharShiZhuang::onLevelUp(Answer::NetPacket* inPacket)
{
    if (NULL == inPacket || NULL == m_pPlayer)
    {
        return ERR_INVALID_DATA;
    }

    int8_t nType = inPacket->readInt8();
    int32_t nId = inPacket->readInt32();

    if (!IsForever(nType, nId))
    {
        return ERR_INVALID_DATA;
    }

    int32_t NewLevel = GetNewShiZhuangLevel(nId);
    const ShiZhuLevelUp* pCfgLevel = CFG_DATA.GetShiZhuLevelUp(nId, NewLevel);
    const ShiZhuLevelUp* pCfgNextLevel = CFG_DATA.GetShiZhuLevelUp(nId, NewLevel + 1);

    if (NULL == pCfgLevel || NULL == pCfgNextLevel)
    {
        return ERR_INVALID_DATA;
    }

    if (pCfgLevel->lCostItem.empty())
    {
        return ERR_INVALID_DATA;
    }

    if (!m_pPlayer->GetBag().RemoveItem(pCfgLevel->lCostItem, IDCR_SHI_ZHUANG_LEVEL_UP))
    {
        return ERR_INVALID_DATA;
    }

    ++m_ShiZhuangLevel[nId];

    CheckSuitInfo();
    sendShiZhuangInfo(nType);
    CheckSuitEffect();

    m_pPlayer->RecalcAttr();

    GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

void CExtCharShiZhuang::sendShiZhuangPeiYangResult(int8_t nType, int32_t nExp, int8_t nCrit)
{
    if (NULL == m_pPlayer || nType < 0 || nType > 2)
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SHI_ZHUANG_PEI_YANG_RESULT);
    if (packet)
    {
        packet->writeInt8(nType);
        packet->writeInt32(nExp);
        packet->writeInt8(nCrit);
        packet->writeInt32(m_vShiZhuang[nType].m_nLevel);
        packet->writeInt32(m_vShiZhuang[nType].m_nExp);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
    }
}

void CExtCharShiZhuang::PackShiZhuangInfo(Answer::NetPacket* packet)
{
    if (packet)
    {
        packet->writeInt32(GetWearId(0));
        packet->writeInt32(GetWearId(1));
        packet->writeInt32(m_EffectId);
        packet->writeInt32(GetWearId(2));
    }
}

void CExtCharShiZhuang::appendShiZhuangInfo(int8_t nType, Answer::NetPacket* packet)
{
    if (NULL == m_pPlayer || NULL == packet || nType < 0 || nType > 2)
    {
        return;
    }

    packet->writeInt8(nType);
    packet->writeInt32(GetWearId(nType));
    packet->writeInt32(m_vShiZhuang[nType].m_nLevel);
    packet->writeInt32(m_vShiZhuang[nType].m_nExp);

    // 写入激活列表
    int32_t nCount = 0;
    uint32_t nOldOffset = packet->getWOffset();
    packet->writeInt32(0);

    for (std::map<int32_t, int32_t>::iterator iter = m_vShiZhuang[nType].m_lActive.begin();
         iter != m_vShiZhuang[nType].m_lActive.end(); ++iter)
    {
        // 跳过已过期的限时时装
        if (iter->second > 0 && iter->second < m_pPlayer->getNow())
        {
            continue;
        }

        packet->writeInt32(iter->first);
        packet->writeInt32(iter->second);

        // 写入升阶等级
        std::map<int32_t, int32_t>::iterator itLevel = m_ShiZhuangLevel.find(iter->first);
        if (itLevel != m_ShiZhuangLevel.end())
        {
            packet->writeInt32(itLevel->second);
        }
        else
        {
            packet->writeInt32(0);
        }

        ++nCount;
    }

    uint32_t nOffset = packet->getWOffset();
    packet->setWOffset(nOldOffset);
    packet->writeInt32(nCount);
    packet->setWOffset(nOffset);
}

void CExtCharShiZhuang::sendShiZhuangInfo(int8_t nType)
{
    if (NULL == m_pPlayer || nType < 0 || nType > 2)
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SHI_ZHUANG_INFO);
    if (packet)
    {
        appendShiZhuangInfo(nType, packet);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
    }
}

void CExtCharShiZhuang::SendShiZhuangInfo()
{
    for (int8_t i = 0; i <= 2; ++i)
    {
        sendShiZhuangInfo(i);
    }
}

int32_t CExtCharShiZhuang::GetWearId(int8_t nType) const
{
    if (nType < 0 || nType > 2)
    {
        return 0;
    }

    if (m_vShiZhuang[nType].IsActive(m_vShiZhuang[nType].m_nWear))
    {
        return m_vShiZhuang[nType].m_nWear;
    }
    return 0;
}

int32_t CExtCharShiZhuang::GetShiZhuangLevel(int8_t nType) const
{
    if (nType >= 0 && nType <= 2)
    {
        return m_vShiZhuang[nType].m_nLevel;
    }
    return 0;
}

void CExtCharShiZhuang::AddPlayerAttr()
{
    if (NULL == m_pPlayer)
    {
        return;
    }

    // 1. 等级属性
    for (int32_t i = 0; i <= 2; ++i)
    {
        int32_t nLevel = m_vShiZhuang[i].m_nLevel;
        const CfgShiZhuangLevel* pCfgLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangLevel((int8_t)i, nLevel);
        if (pCfgLevel)
        {
            for (AddAttrList::const_iterator it = pCfgLevel->vAttr.begin(); it != pCfgLevel->vAttr.end(); ++it)
            {
                m_pPlayer->AddAttrValue((CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue);
            }
        }

        // 2. 已激活时装属性
        for (std::map<int32_t, int32_t>::iterator iter = m_vShiZhuang[i].m_lActive.begin();
             iter != m_vShiZhuang[i].m_lActive.end(); ++iter)
        {
            if (iter->second > 0 && iter->second < m_pPlayer->getNow())
            {
                continue;
            }

            const CfgShiZhuang* pCfg = CFG_DATA.GetShiZhuangTable()->GetShiZhuang(iter->first);
            if (pCfg)
            {
                for (AddAttrList::const_iterator it = pCfg->vAttr.begin(); it != pCfg->vAttr.end(); ++it)
                {
                    m_pPlayer->AddAttrValue((CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue);
                }
            }
        }
    }

    // 3. 升阶等级属性
    for (std::map<int32_t, int32_t>::iterator it = m_ShiZhuangLevel.begin(); it != m_ShiZhuangLevel.end(); ++it)
    {
        const ShiZhuLevelUp* pCfgLevel = CFG_DATA.GetShiZhuLevelUp(it->first, it->second);
        if (pCfgLevel && !pCfgLevel->lAttr.empty())
        {
            for (AddAttrList::const_iterator itAttr = pCfgLevel->lAttr.begin(); itAttr != pCfgLevel->lAttr.end(); ++itAttr)
            {
                m_pPlayer->AddAttrValue((CObjAttrs::Index_T)itAttr->m_nAddAttrType, itAttr->m_nAddAttrValue);
            }
        }
    }

    // 4. 套装属性
    for (std::map<int32_t, SuitInfo>::iterator it = m_SuitInfoMap.begin(); it != m_SuitInfoMap.end(); ++it)
    {
        AddAttrList suitAttr;
        CFG_DATA.GetShiZhuangTable()->GetShiZhuangSuitAttr(suitAttr, it->first, it->second.nLevel, it->second.nCount);
        for (AddAttrList::const_iterator itAttr = suitAttr.begin(); itAttr != suitAttr.end(); ++itAttr)
        {
            m_pPlayer->AddAttrValue((CObjAttrs::Index_T)itAttr->m_nAddAttrType, itAttr->m_nAddAttrValue);
        }
    }
}

void CExtCharShiZhuang::addShiZhuangExp(int8_t nType, int32_t nAddExp)
{
    if (NULL == m_pPlayer || nType < 0 || nType > 2 || nAddExp <= 0)
    {
        return;
    }

    int32_t nLevel = m_vShiZhuang[nType].m_nLevel;
    const CfgShiZhuangLevel* pCfgLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangLevel(nType, nLevel);
    const CfgShiZhuangLevel* pCfgNextLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangLevel(nType, nLevel + 1);

    if (NULL == pCfgLevel)
    {
        return;
    }

    m_vShiZhuang[nType].m_nExp += nAddExp;

    while (pCfgNextLevel && m_vShiZhuang[nType].m_nExp >= pCfgLevel->nLevelExp)
    {
        ++m_vShiZhuang[nType].m_nLevel;
        m_vShiZhuang[nType].m_nExp -= pCfgLevel->nLevelExp;

        m_pPlayer->recalcAttr();

        pCfgLevel = pCfgNextLevel;
        pCfgNextLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangLevel(nType, m_vShiZhuang[nType].m_nLevel + 1);
    }
}

bool CExtCharShiZhuang::ActiveWithItem(int32_t nId, int32_t nAddTime)
{
    if (NULL == m_pPlayer)
    {
        return false;
    }

    const CfgShiZhuang* pCfg = CFG_DATA.GetShiZhuangTable()->GetShiZhuang(nId);
    if (NULL == pCfg)
    {
        return false;
    }

    int8_t nType = (int8_t)pCfg->nType;

    if (m_vShiZhuang[nType].IsActive(nId))
    {
        m_vShiZhuang[nType].AddTime(nId, nAddTime);
    }

    if (!m_vShiZhuang[nType].IsActive(nId))
    {
        m_vShiZhuang[nType].AddTime(nId, nAddTime);
        m_pPlayer->recalcAttr();
        wear(nType, nId);
    }

    sendShiZhuangInfo(nType);
    return true;
}

void CExtCharShiZhuang::wear(int8_t nType, int32_t nId)
{
    if (NULL == m_pPlayer || nType < 0 || nType > 2)
    {
        return;
    }

    m_vShiZhuang[nType].m_nWear = nId;
    m_pPlayer->setNeedSyncSelf();
    m_pPlayer->setSyncToTeamFlag();

    if (nType == 0)
    {
        m_pPlayer->sendUpdateSocialPlayerInfo(PII_SHI_ZHUANG_WEAPON, nId);
    }
    else if (nType == 1)
    {
        m_pPlayer->sendUpdateSocialPlayerInfo(PII_SHI_ZHUANG_CLOTHES, nId);
    }
}

bool CExtCharShiZhuang::IsForever(int8_t nType, int32_t nId) const
{
    if (nType < 0 || nType > 2)
    {
        return false;
    }
    return m_vShiZhuang[nType].IsForever(nId);
}

int32_t CExtCharShiZhuang::GetNewShiZhuangLevel(int32_t nId) const
{
    std::map<int32_t, int32_t>::const_iterator it = m_ShiZhuangLevel.find(nId);
    if (it != m_ShiZhuangLevel.end())
    {
        return it->second;
    }
    return 0;
}

void CExtCharShiZhuang::CheckSuitInfo()
{
    m_SuitInfoMap.clear();

    for (std::map<int32_t, int32_t>::iterator it = m_ShiZhuangLevel.begin(); it != m_ShiZhuangLevel.end(); ++it)
    {
        const CfgShiZhuang* pCfg = CFG_DATA.GetShiZhuangTable()->GetShiZhuang(it->first);
        if (pCfg && pCfg->nSuitId > 0)
        {
            SuitInfo& info = m_SuitInfoMap[pCfg->nSuitId];
            ++info.nCount;
            if (info.nLevel <= 0 || it->second < info.nLevel)
            {
                info.nLevel = it->second;
            }
        }
    }

    // 计算套装效果等级
    for (std::map<int32_t, SuitInfo>::iterator it = m_SuitInfoMap.begin(); it != m_SuitInfoMap.end(); ++it)
    {
        it->second.nEffectLevel = CFG_DATA.GetShiZhuangTable()->GetShiZhuangSuitLevel(
            it->first, it->second.nLevel, it->second.nCount);
    }
}

void CExtCharShiZhuang::CheckSuitEffect()
{
    int32_t OldId = m_EffectId;
    int32_t WearId = GetWearId(1); // 衣服类型

    const CfgShiZhuang* pCfg = CFG_DATA.GetShiZhuangTable()->GetShiZhuang(WearId);
    if (pCfg && pCfg->nSuitId > 0)
    {
        std::map<int32_t, SuitInfo>::iterator it = m_SuitInfoMap.find(pCfg->nSuitId);
        if (it != m_SuitInfoMap.end())
        {
            m_EffectId = it->second.nEffectLevel;
        }
        else
        {
            m_EffectId = 0;
        }
    }
    else
    {
        m_EffectId = 0;
    }

    if (m_EffectId != OldId)
    {
        m_pPlayer->setNeedSyncSelf();
        m_pPlayer->setSyncToTeamFlag();
        m_pPlayer->sendUpdateSocialPlayerInfo(PII_SHI_ZHUANG_EFFECT, m_EffectId);
    }
}

// ==================== ShiZhuangInfo 方法实现 ====================

void ShiZhuangInfo::ParesActiveString(const std::string& strActive)
{
    int32_t Now = DayTime::now();
    m_lActive.clear();

    if (strActive.empty())
    {
        return;
    }

    StringVector vt = Answer::StringUtility::split(strActive, "|");

    for (StringVector::iterator iter = vt.begin(); iter != vt.end(); ++iter)
    {
        StringVector ShiZhuangVt = Answer::StringUtility::split(*iter, ":");

        if (ShiZhuangVt.size() == 2)
        {
            int32_t nId = atoi(ShiZhuangVt[0].c_str());
            int32_t nTime = atoi(ShiZhuangVt[1].c_str());
            m_lActive[nId] = nTime;
        }
    }
}

std::string ShiZhuangInfo::GetActiveString() const
{
    int32_t Now = DayTime::now();
    std::stringstream ss;

    for (std::map<int32_t, int32_t>::const_iterator iter = m_lActive.begin();
         iter != m_lActive.end(); ++iter)
    {
        ss << iter->first << ":" << iter->second << "|";
    }

    return ss.str();
}

void ShiZhuangInfo::AddTime(int32_t nId, int32_t nTime)
{
    if (nTime > 0)
    {
        int32_t Now = DayTime::now();
        if (!IsActive(nId))
        {
            m_lActive[nId] = Now + nTime;
        }
        else if (m_lActive[nId] > 0)
        {
            m_lActive[nId] += nTime;
        }
    }
    else
    {
        m_lActive[nId] = 0; // 永久
    }
}

bool ShiZhuangInfo::IsForever(int32_t nId) const
{
    std::map<int32_t, int32_t>::const_iterator it = m_lActive.find(nId);
    if (it != m_lActive.end() && it->second == 0)
    {
        return true;
    }
    return false;
}

bool ShiZhuangInfo::IsActive(int32_t nId) const
{
    int32_t Now = DayTime::now();
    std::map<int32_t, int32_t>::const_iterator it = m_lActive.find(nId);

    if (it == m_lActive.end())
    {
        return false;
    }

    if (it->second > 0 && it->second <= Now)
    {
        return false;
    }

    return true;
}
