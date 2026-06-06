#include "stdafx.h"
#include "CXinMo.h"
#include "GameService.h"
#include "ItemHelper.h"
#include "Player.h"
#include "Bag.h"
#include "Currency.h"
#include "EquipManager.h"
#include "StringUtility.h"
#include "Map.h"
#include "DBService.h"

using namespace Answer;

// ===== XinMoTable 方法 =====

int32_t XinMoTable::GetAppearCount(int32_t nRemainFlagCount) const
{
    // 从 XinQing.txt 表中查找指定 flagCount 下的随机结果
    for (std::list<XinQingRate>::const_iterator iter = m_lstXinQingRate.begin();
         iter != m_lstXinQingRate.end(); ++iter)
    {
        if (iter->nFlagCount == nRemainFlagCount)
            return iter->nSpecialMount;
    }
    return 0;
}

// ===== CXinMo 构造/析构 =====

void CXinMo::OnDaySwitch(int32_t nDiffDays)
{
}

void CXinMo::OnUpdate(int64_t curTick)
{
}

void CXinMo::OnCleanUp()
{
    m_Exp = 0;
    m_XinMoLevel = 0;
    m_XinMoActiveLevel = 0;
    m_QiQingLevel.clear();
    m_QiQingInfo = 0;
    bzero(m_ItemList, sizeof(m_ItemList));
}

void CXinMo::OnLoadFromDB(const PlayerDBData& dbData)
{
    m_Exp = dbData.m_XinMoDBData.m_Exp;
    m_XinMoLevel = dbData.m_XinMoDBData.m_XinMoLevel;
    m_XinMoActiveLevel = dbData.m_XinMoDBData.m_XinMoActiveLevel;
    m_QiQingLevel = dbData.m_XinMoDBData.m_QiQingLevel;
    m_QiQingInfo = dbData.m_XinMoDBData.m_QiQingInfo;
    memcpy(m_ItemList, dbData.m_XinMoDBData.m_ItemList, sizeof(m_ItemList));
}

void CXinMo::OnSaveToDB(PlayerDBData& dbData)
{
    dbData.m_XinMoDBData.m_Exp = m_Exp;
    dbData.m_XinMoDBData.m_XinMoLevel = m_XinMoLevel;
    dbData.m_XinMoDBData.m_XinMoActiveLevel = m_XinMoActiveLevel;
    dbData.m_XinMoDBData.m_QiQingLevel = m_QiQingLevel;
    dbData.m_XinMoDBData.m_QiQingInfo = m_QiQingInfo;
    memcpy(dbData.m_XinMoDBData.m_ItemList, m_ItemList, sizeof(dbData.m_XinMoDBData.m_ItemList));
}

void CXinMo::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(CM_XIN_MO_LEVEL);
    procList.push_back(CM_ACTIVE_XIN_MO);
    procList.push_back(CM_XIN_MO_JIN_HUA);
    procList.push_back(CM_XIN_MO_GET_ITEM);
    procList.push_back(CM_XIN_MO_TIDY);
    procList.push_back(CM_XIN_MO_DEC);
    procList.push_back(CM_QI_QING_LEVEL_UP);
    procList.push_back(CM_XIN_QING);
}

int32_t CXinMo::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return ERR_INVALID_DATA;

    // 检查开服天数（原版要求 >= 29天）
    if (CFG_DATA.getServerDiffDay(SVT_NORMAL) + 1 <= 29)
        return ERR_INVALID_DATA;

    switch (nProcId)
    {
    case CM_XIN_MO_LEVEL:       return OnXinMoLevel(inPacket);
    case CM_ACTIVE_XIN_MO:      return OnActiveXinMo(inPacket);
    case CM_XIN_MO_JIN_HUA:     return OnJinHua(inPacket);
    case CM_XIN_MO_GET_ITEM:    return OnGetItem(inPacket);
    case CM_XIN_MO_TIDY:        return OnTidy(inPacket);
    case CM_XIN_MO_DEC:         return OnDec(inPacket);
    case CM_QI_QING_LEVEL_UP:   return OnQiQingLevelUp(inPacket);
    case CM_XIN_QING:           return OnXinQing(inPacket);
    default:                    return ERR_INVALID_DATA;
    }
}

// ===== 属性加成 =====

void CXinMo::AddCharAttr()
{
    // 心魔等级属性
    const XinMoCfg* pCurCfg = CFG_DATA.GetXinMoTable().GetXingMoCfg(m_XinMoLevel);
    if (pCurCfg)
    {
        for (AddAttrList::const_iterator it = pCurCfg->lAttr.begin();
             it != pCurCfg->lAttr.end(); ++it)
        {
            Unit::AddAttrValue(m_pPlayer, (CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue);
        }
    }

    // 心魔觉醒等级属性
    const QiQingCfg* pQiQingCfg = CFG_DATA.GetXinMoTable().GetQiQingCfg(m_XinMoActiveLevel);
    if (pQiQingCfg)
    {
        for (AddAttrList::const_iterator it = pQiQingCfg->lAttr.begin();
             it != pQiQingCfg->lAttr.end(); ++it)
        {
            Unit::AddAttrValue(m_pPlayer, (CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue);
        }
    }

    // 七情等级属性
    for (std::map<int,int>::const_iterator it = m_QiQingLevel.begin();
         it != m_QiQingLevel.end(); ++it)
    {
        const XinMoQiQingLevelUpCfg* pLevelCfg =
            CFG_DATA.GetXinMoTable().GetXinMoQiQingLevelUpCfg(it->first, it->second);
        if (pLevelCfg)
        {
            for (AddAttrList::const_iterator ait = pLevelCfg->lAttr.begin();
                 ait != pLevelCfg->lAttr.end(); ++ait)
            {
                Unit::AddAttrValue(m_pPlayer, (CObjAttrs::Index_T)ait->m_nAddAttrType, ait->m_nAddAttrValue);
            }
        }
    }
}

// ===== 心魔升级 =====

int32_t CXinMo::OnXinMoLevel(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return ERR_INVALID_DATA;

    const XinMoCfg* pCurCfg = CFG_DATA.GetXinMoTable().GetXingMoCfg(m_XinMoLevel);
    const XinMoCfg* pNextCfg = CFG_DATA.GetXinMoTable().GetXingMoCfg(m_XinMoLevel + 1);
    if (!pCurCfg || !pNextCfg)
        return ERR_INVALID_DATA;

    // 检查七情等级需求
    if (GetActiveXinMoLevel() < pNextCfg->nNeedQiQingLevel)
        return ERR_INVALID_DATA;

    // 检查金钱
    if (pCurCfg->nCostMoney > 0)
    {
        CExtCurrency* pCurrency = m_pPlayer->GetCurrency();
        if (!pCurrency || pCurrency->GetMoneyBindAndNoBind() < pCurCfg->nCostMoney)
            return ERR_INVALID_DATA;
    }

    // 检查神识
    if (pCurCfg->nCostShenYaoBi > 0)
    {
        if (m_pPlayer->GetCurrency(CURRENCY_VIGOUR) < pCurCfg->nCostShenYaoBi)
            return ERR_INVALID_DATA;
    }

    // 检查经验
    if (pCurCfg->nCostExp > 0 && m_Exp < pCurCfg->nCostExp)
        return ERR_INVALID_DATA;

    // 扣除消耗
    if (pCurCfg->nCostMoney > 0)
    {
        if (!m_pPlayer->GetCurrency()->DecMoneyAndNoBind(pCurCfg->nCostMoney, GCR_XIN_MO_LEVEL_UP, 0))
            return ERR_INVALID_DATA;
    }

    if (pCurCfg->nCostShenYaoBi > 0)
    {
        if (!m_pPlayer->DecCurrency(CURRENCY_VIGOUR, pCurCfg->nCostShenYaoBi, GCR_XIN_MO_LEVEL_UP, 0))
            return ERR_INVALID_DATA;
    }

    if (pCurCfg->nCostExp > 0)
        m_Exp -= pCurCfg->nCostExp;

    ++m_XinMoLevel;
    SendXiMoInfo();

    // 公告
    if (pNextCfg->nGongGaoId > 0)
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pNextCfg->nGongGaoId);
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeInt32(m_XinMoLevel);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(m_pPlayer->getConnId(), packet);
        }
    }

    m_pPlayer->RecalcAttr();
    return GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(),
                                     inPacket->getProc(), (int64_t)m_XinMoLevel);
}

// ===== 心魔觉醒 =====

int32_t CXinMo::OnActiveXinMo(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return ERR_INVALID_DATA;

    Int32Vector vSlot;
    m_pPlayer->queryBagInfo(inPacket, vSlot);

    const QiQingCfg* pCurCfg = CFG_DATA.GetXinMoTable().GetQiQingCfg(m_XinMoActiveLevel + 1);
    if (!pCurCfg)
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    CExtCharBag* pBag = m_pPlayer->GetBag();
    if (!pBag->RemoveItem(vSlot, &pCurCfg->lCostItems, IDCR_JI_HUO_XIN_MO))
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    ++m_XinMoActiveLevel;
    pBag->ForceSendDirty();
    SendXiMoInfo();

    // 公告
    if (pCurCfg->nGongGaoId > 0)
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pCurCfg->nGongGaoId);
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeInt32(m_XinMoActiveLevel);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(m_pPlayer->getConnId(), packet);
        }
    }

    m_pPlayer->RecalcAttr();
    int32_t nResult = GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(),
                                                 inPacket->getProc(), (int64_t)m_XinMoActiveLevel);
    vSlot.clear();
    return nResult;
}

// ===== 装备进化 =====

int32_t CXinMo::OnJinHua(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return ERR_INVALID_DATA;

    int32_t nPos = inPacket->readInt32();
    Int32Vector vSlot;
    m_pPlayer->queryBagInfo(inPacket, vSlot);

    MemChrBag bagItem;
    m_pPlayer->getBagSlotData(bagItem, nPos);
    if (bagItem.itemClass != IC_EQUIP)
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    const EquipJinHua* pJinHua = CFG_DATA.GetXinMoTable().GetJinHuaCfg(bagItem.itemId);
    if (!pJinHua)
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    int32_t nEquipId = pJinHua->GetParamRate();
    if (nEquipId <= 0)
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    MemEquip equip;
    CEquipManager::instance().GetMemEquip(equip, bagItem.srcId);
    if (equip.base <= 0)
    {
        equip.~MemEquip();
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    CExtCharBag* pBag = m_pPlayer->GetBag();
    if (!pBag->RemoveItem(vSlot, &pJinHua->CostItems, IDCR_XIN_MO_EQUIP_JIN_HUA))
    {
        equip.~MemEquip();
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    equip.base = nEquipId;
    bagItem.itemId = nEquipId;
    pBag->SetSlotData(nPos, &bagItem, IDCR_XIN_MO_EQUIP_JIN_HUA, 0);

    CEquipManager::instance().UpdateMemEquip(m_pPlayer->getConnId(), &equip, 1467);
    CEquipManager::instance().SendPlayerEquipInfo(m_pPlayer, &equip);

    // 高级装备公告
    const CfgEquip* pCfgEquip = CFG_DATA.getEquip(nEquipId);
    if (pCfgEquip && pCfgEquip->m_nGrade > 7)
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(548);
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeInt32(nEquipId);
            packet->writeInt32(pCfgEquip->m_nGrade);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(m_pPlayer->getConnId(), packet);
        }
    }

    int32_t nResult = GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(),
                                                 inPacket->getProc(), (int64_t)bagItem.itemId);
    equip.~MemEquip();
    vSlot.clear();
    return nResult;
}

// ===== 七情升级 =====

int32_t CXinMo::OnQiQingLevelUp(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return ERR_INVALID_DATA;

    int32_t nType = inPacket->readInt32();
    Int32Vector vSlot;
    m_pPlayer->queryBagInfo(inPacket, vSlot);

    if (m_XinMoActiveLevel < nType)
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    int32_t nLevel = GetQiQingLevel(nType);
    const XinMoQiQingLevelUpCfg* pCurCfg =
        CFG_DATA.GetXinMoTable().GetXinMoQiQingLevelUpCfg(nType, nLevel);
    const XinMoQiQingLevelUpCfg* pNextCfg =
        CFG_DATA.GetXinMoTable().GetXinMoQiQingLevelUpCfg(nType, nLevel + 1);

    if (!pCurCfg || !pNextCfg)
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    // 检查前置七情等级
    if (nType - 1 > 0)
    {
        int32_t nNeedLevel = pCurCfg->nNeedLastTypeLevel;
        if (nNeedLevel > GetQiQingLevel(nType - 1))
        {
            vSlot.clear();
            return ERR_INVALID_DATA;
        }
    }

    CExtCharBag* pBag = m_pPlayer->GetBag();
    if (!pBag->RemoveItem(vSlot, &pCurCfg->lCostList, IDCR_XIN_MO_QI_QING_LEVEL_UP))
    {
        vSlot.clear();
        return ERR_INVALID_DATA;
    }

    m_QiQingLevel[nType] = nLevel + 1;
    pBag->ForceSendDirty();
    SendXinMoQiQingLevel(nType);

    // 公告
    if (pNextCfg->nGongGaoId > 0)
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pNextCfg->nGongGaoId);
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeInt32(nType);
            packet->writeInt32(m_QiQingLevel[nType]);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(m_pPlayer->getConnId(), packet);
        }
    }

    m_pPlayer->RecalcAttr();
    vSlot.clear();
    return 0;
}

// ===== 心情系统 =====

int32_t CXinMo::OnXinQing(Answer::NetPacket* inPacket)
{
    if (!m_pPlayer || !inPacket)
        return ERR_INVALID_DATA;

    if (m_XinMoLevel <= 9)
        return ERR_INVALID_DATA;

    int32_t nType = inPacket->readInt32();
    switch (nType)
    {
    case 0: // 摇一摇
    {
        if (IsYaoYiYao())
            return ERR_INVALID_DATA;
        if (GetLeftYaoYiYaoTimes() <= 0)
            return ERR_INVALID_DATA;

        m_pPlayer->updateRecord(37304, 1);
        m_QiQingInfo = 0;
        int32_t nAppearCount = CFG_DATA.GetXinMoTable().GetAppearCount(7);
        SetFlag(7);
        SetYaoYiYaoFlag(nAppearCount);
        AddYaoYiYaoTimes();
        break;
    }
    case 1: // 换心情
    {
        if (!IsYaoYiYao())
            return ERR_INVALID_DATA;

        int32_t nFlagCount = GetFlagCount();
        if (nFlagCount > 6)
            return ERR_INVALID_DATA;

        bool bAddTimes = true;
        if (GetChangeXinQingTimes() <= 0)
        {
            bAddTimes = false;
            if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, 100, GCR_CHANGE_XIN_QING, 0))
                return ERR_INVALID_DATA;
        }

        int32_t nAppearCount;
        if (m_pPlayer->getRecord(37304) <= 19)
        {
            nAppearCount = CFG_DATA.GetXinMoTable().GetAppearCount(7 - nFlagCount);
        }
        else
        {
            nAppearCount = 7 - nFlagCount;
        }
        SetYaoYiYaoFlag(nAppearCount);

        m_pPlayer->updateRecord(37304, m_pPlayer->getRecord(37304) + 1);
        if (bAddTimes)
            AddChangeXinQingTimes();
        break;
    }
    case 2: // 领取奖励
    {
        if (!IsYaoYiYao())
            return ERR_INVALID_DATA;

        int32_t nFlagCount = GetFlagCount();
        const XinQingReward* pReward = CFG_DATA.GetXinMoTable().GetXinQingReward(nFlagCount);
        if (!pReward)
            return ERR_INVALID_DATA;

        CExtCharBag* pBag = m_pPlayer->GetBag();
        if (!pBag->AddItem(&pReward->Items, IACR_XIN_MO_XIN_QING_REWARD))
            return ERR_INVALID_DATA;

        if (pReward->nGongGaoId > 0)
        {
            Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2CD6);
            if (packet)
            {
                packet->writeInt32(pReward->nGongGaoId);
                packet->writeUTF8(m_pPlayer->getName());
                packet->writeInt64(m_pPlayer->getCid());
                packet->writeInt32(GetFlagCount());
                packet->setSize(packet->getWOffset());
                GAME_SERVICE.worldBroadcast(m_pPlayer->getConnId(), packet);
            }
        }

        m_QiQingInfo = 0;
        break;
    }
    default:
        return ERR_INVALID_DATA;
    }

    SendXinQingInfo();
    return GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(),
                                     inPacket->getProc(), (int64_t)nType);
}

// ===== 心魔背包 =====

int32_t CXinMo::OnGetItem(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    const Map* pMap = StaticObj::getMap(m_pPlayer);
    if (!pMap || !pMap->IsXinMoCun())
        return 2;

    int32_t nSlot = inPacket->readInt32();
    if (nSlot < -1 || nSlot > 55)
        return 2;

    CExtCharBag* pBag = m_pPlayer->GetBag();
    if (pBag->GetFreeSlotCount() <= 0)
        return 2;

    if (nSlot == -1)
    {
        // 全部领取
        for (int32_t i = 0; i <= 55; ++i)
        {
            if (m_ItemList[i].itemCount > 0 && m_ItemList[i].itemId > 0)
            {
                if (pBag->GetFreeSlotCount() <= 0)
                {
                    m_pPlayer->TiShiInfo(2048, 0);
                    return 2;
                }
                GetItem(i);
            }
        }
    }
    else
    {
        GetItem(nSlot);
    }

    return 0;
}

int32_t CXinMo::OnDec(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    int32_t nSlot = inPacket->readInt32();
    if (nSlot >= 56)
        return 2;

    if (m_ItemList[nSlot].itemCount <= 0 || m_ItemList[nSlot].itemId <= 0)
        return 2;

    ResetBagSlot(nSlot, 1);
    std::list<int> tmpList;
    tmpList.push_back(nSlot);
    SendChangeItem(tmpList);
    return 0;
}

int32_t CXinMo::OnTidy(Answer::NetPacket* inPacket)
{
    if (!inPacket || !m_pPlayer)
        return 2;

    MemChrBagVector items;
    int32_t nBagSize = 56;

    // 整理合并相同物品
    for (int32_t i = 0; i < nBagSize; ++i)
    {
        if (m_ItemList[i].itemCount > 0 && m_ItemList[i].itemId > 0)
        {
            bool bFind = false;
            for (MemChrBagVector::iterator it = items.begin(); it != items.end(); ++it)
            {
                if (it->itemClass == m_ItemList[i].itemClass &&
                    it->itemId == m_ItemList[i].itemId &&
                    it->bind == m_ItemList[i].bind &&
                    it->srcId == m_ItemList[i].srcId)
                {
                    it->itemCount += m_ItemList[i].itemCount;
                    bFind = true;
                    break;
                }
            }
            if (!bFind)
                items.push_back(m_ItemList[i]);
        }
    }

    // 排序（按物品优先级）
    std::sort(items.begin(), items.end(), GreaterBagItem);

    // 重新填充
    int32_t slot = 0;
    for (MemChrBagVector::iterator iter = items.begin(); iter != items.end() && slot < nBagSize; ++iter)
    {
        int32_t nOverlay = CFG_DATA.getOverlay(iter->itemId, iter->itemClass);
        if (nOverlay > 0)
        {
            while (iter->itemCount > nOverlay && slot < nBagSize)
            {
                MemChrBag nullobj = *iter;
                nullobj.itemCount = nOverlay;
                iter->itemCount -= nOverlay;
                m_ItemList[slot++] = nullobj;
            }
            if (iter->itemCount > 0 && slot < nBagSize)
                m_ItemList[slot++] = *iter;
        }
    }

    // 清空剩余格子
    while (slot < nBagSize)
    {
        bzero(&m_ItemList[slot], sizeof(MemChrBag));
        ++slot;
    }

    SendAllItem();
    return 0;
}

bool CXinMo::AddItem(MemChrBagVector* pItems)
{
    if (!m_pPlayer || !pItems)
        return false;

    int32_t nTime = m_pPlayer->getNow();
    std::list<int> itemList;
    itemList.clear();

    for (MemChrBagVector::iterator it = pItems->begin(); it != pItems->end(); ++it)
    {
        for (int32_t i = 0; i <= 55; ++i)
        {
            if (m_ItemList[i].itemCount <= 0 || m_ItemList[i].itemId <= 0)
            {
                m_ItemList[i] = *it;
                AddXinMoBagLog(m_ItemList[i], 1, 5);
                itemList.push_back(i);
                break;
            }
        }
    }

    SendChangeItem(itemList);
    return true;
}

void CXinMo::GetItem(int32_t nSlot)
{
    if (!m_pPlayer)
        return;

    if (nSlot < 0 || nSlot >= 56)
        return;

    if (m_ItemList[nSlot].itemCount <= 0 || m_ItemList[nSlot].itemId <= 0)
        return;

    CExtCharBag* pBag = m_pPlayer->GetBag();
    if (pBag->GetFreeSlotCount() <= 0)
        return;

    MemChrBag bagItem = m_ItemList[nSlot];
    MemChrBagVector item;
    item.push_back(bagItem);

    if (pBag->AddItem(&item, IDCR_XIN_MO_BAG_GET))
    {
        ResetBagSlot(nSlot, 2);
        std::list<int> tmpList;
        tmpList.push_back(nSlot);
        SendChangeItem(tmpList);
    }
}

void CXinMo::ResetBagSlot(int32_t nSlot, int32_t nOpway)
{
    AddXinMoBagLog(m_ItemList[nSlot], 2, nOpway);
    bzero(&m_ItemList[nSlot], sizeof(MemChrBag));
}

void CXinMo::AddXinMoBagLog(const MemChrBag& item, int32_t nFlag, int32_t nOpway)
{
    if (m_pPlayer)
    {
        DBService::instance().LogXinMoBag(m_pPlayer->getCid(), item, nFlag, nOpway);
    }
}

void CXinMo::CleanXinMoBag()
{
    std::list<int> tmpList;
    for (int32_t i = 0; i <= 55; ++i)
    {
        if (m_ItemList[i].itemCount > 0 && m_ItemList[i].itemId > 0)
        {
            ResetBagSlot(i, 3);
            tmpList.push_back(i);
        }
    }
    SendChangeItem(tmpList);
}

void CXinMo::DieDropFromXinMoBag(MemChrBagVector* pTmpVt)
{
    if (!m_pPlayer || !pTmpVt)
        return;

    Map* pMap = StaticObj::getMap(m_pPlayer);
    if (!pMap || !pMap->IsXinMoMap())
        return;

    std::list<int> tmpList;
    for (int32_t i = 0; i <= 55; ++i)
    {
        if (m_ItemList[i].itemCount > 0 && m_ItemList[i].itemId > 0)
        {
            int32_t nRand = RANDOM.generate(1, 100);
            if (nRand <= 20)
                pTmpVt->push_back(m_ItemList[i]);

            ResetBagSlot(i, 4);
            tmpList.push_back(i);
        }
    }
    SendChangeItem(tmpList);
}

int32_t CXinMo::GetFreeSlotCount() const
{
    int32_t nCount = 0;
    for (int32_t i = 0; i <= 55; ++i)
    {
        if (!m_ItemList[i].itemCount || !m_ItemList[i].itemId)
            ++nCount;
    }
    return nCount;
}

// ===== 七情工具方法 =====

int32_t CXinMo::GetQiQingLevel(int32_t nType) const
{
    std::map<int,int>::const_iterator it = m_QiQingLevel.find(nType);
    if (it != m_QiQingLevel.end())
        return it->second;
    return 0;
}

int32_t CXinMo::GetLeftYaoYiYaoTimes() const
{
    if (m_pPlayer)
        return 10 - m_pPlayer->getRecord(2122);
    return 0;
}

int32_t CXinMo::GetChangeXinQingTimes() const
{
    if (m_pPlayer)
        return 10 - m_pPlayer->getRecord(2123);
    return 0;
}

int32_t CXinMo::GetFlagCount() const
{
    int32_t nCount = 0;
    for (int32_t i = 0; i <= 6; ++i)
    {
        if ((m_QiQingInfo & (1 << i)) != 0)
            ++nCount;
    }
    return nCount;
}

void CXinMo::SetFlag(int32_t nId)
{
    if (nId >= 0 && nId < 8)
        m_QiQingInfo |= (1 << nId);
}

void CXinMo::SetYaoYiYaoFlag(int32_t nCount)
{
    Int32Vector nIdVt;
    GetNoFlagIdList(nIdVt);

    int32_t nNoFlagCount = (int32_t)nIdVt.size();
    int32_t nSetCount = (nNoFlagCount <= nCount) ? nNoFlagCount : nCount;

    if (nSetCount > 0)
    {
        std::random_shuffle(nIdVt.begin(), nIdVt.end());
        for (int32_t i = 0; i < nSetCount; ++i)
        {
            SetFlag(nIdVt[i]);
        }
    }
}

void CXinMo::GetNoFlagIdList(Int32Vector& nIdVt) const
{
    nIdVt.clear();
    for (int32_t i = 0; i <= 6; ++i)
    {
        if ((m_QiQingInfo & (1 << i)) == 0)
            nIdVt.push_back(i);
    }
}

void CXinMo::AddYaoYiYaoTimes()
{
    if (m_pPlayer)
    {
        int32_t nRecord = m_pPlayer->getRecord(2122);
        m_pPlayer->updateRecord(2122, nRecord + 1);
    }
}

void CXinMo::AddChangeXinQingTimes()
{
    if (m_pPlayer)
    {
        int32_t nRecord = m_pPlayer->getRecord(2123);
        m_pPlayer->updateRecord(2123, nRecord + 1);
    }
}

void CXinMo::AddExp(int32_t nValue)
{
    m_Exp += nValue;
    SendXiMoInfo();
}

// ===== 数据发送 =====

void CXinMo::SendXiMoInfo()
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D3E);
    if (packet)
    {
        packet->writeInt32(m_Exp);
        packet->writeInt32(m_XinMoLevel);
        packet->writeInt32(m_XinMoActiveLevel);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

void CXinMo::SendXinQingInfo()
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D43);
    if (packet)
    {
        packet->writeInt32(GetLeftYaoYiYaoTimes());
        packet->writeInt32(GetChangeXinQingTimes());
        packet->writeInt32(m_QiQingInfo);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

void CXinMo::SendXinMoQiQingLevel(int32_t nType)
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D42);
    if (packet)
    {
        if (nType)
        {
            packet->writeInt32(1);
            packet->writeInt32(nType);
            packet->writeInt32(m_QiQingLevel[nType]);
        }
        else
        {
            int32_t nSize = (int32_t)m_QiQingLevel.size();
            packet->writeInt32(nSize);
            for (std::map<int,int>::const_iterator it = m_QiQingLevel.begin();
                 it != m_QiQingLevel.end(); ++it)
            {
                packet->writeInt32(it->first);
                packet->writeInt32(it->second);
            }
        }
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

void CXinMo::SendAllItem()
{
    if (!m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D3F);
    if (packet)
    {
        int32_t nCount = 0;
        int32_t nOldOffset = packet->getWOffset();
        packet->writeInt32(0);  // placeholder for count

        for (int32_t i = 0; i <= 55; ++i)
        {
            if (m_ItemList[i].itemCount > 0 && m_ItemList[i].itemId > 0)
            {
                ++nCount;
                packet->writeInt32(i);
                packet->writeInt32(m_ItemList[i].itemId);
                packet->writeInt8(m_ItemList[i].itemClass);
                packet->writeInt32(m_ItemList[i].itemCount);
                packet->writeInt8(m_ItemList[i].bind);
                packet->writeInt32(m_ItemList[i].endTime);
                packet->writeInt64(m_ItemList[i].srcId);
            }
        }

        int32_t nNewOffset = packet->getWOffset();
        packet->setWOffset(nOldOffset);
        packet->writeInt32(nCount);
        packet->setWOffset(nNewOffset);
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}

void CXinMo::SendChangeItem(const std::list<int>& itemList)
{
    int32_t nCount = (int32_t)itemList.size();
    if (nCount <= 0 || !m_pPlayer)
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2D40);
    if (packet)
    {
        packet->writeInt32(nCount);
        for (std::list<int>::const_iterator it = itemList.begin(); it != itemList.end(); ++it)
        {
            packet->writeInt32(*it);
            packet->writeInt32(m_ItemList[*it].itemId);
            packet->writeInt8(m_ItemList[*it].itemClass);
            packet->writeInt32(m_ItemList[*it].itemCount);
            packet->writeInt8(m_ItemList[*it].bind);
            packet->writeInt32(m_ItemList[*it].endTime);
            packet->writeInt64(m_ItemList[*it].srcId);
        }
        packet->setSize(packet->getWOffset());
        GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
    }
}
