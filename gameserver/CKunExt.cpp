#include "stdafx.h"
#include "CKunExt.h"
#include "GameService.h"
#include "ItemHelper.h"
#include "ExtSystemMgr.h"
#include "Bag.h"
#include "Currency.h"
#include "CharSkill.h"
#include <algorithm>

using namespace Answer;

// ========== Static utility methods for DanTianCfg ==========

int32_t DanTianCfg::RandDanTianId(const DanTianCfg* pCfg)
{
    // 根据pCfg配置随机选择丹田ID
    // nMid、nRate、nTime等字段可用于加权随机
    return (pCfg && pCfg->nMid > 0) ? pCfg->nMid : 1;
}

int32_t DanTianCfg::RandHighDanTianId(const DanTianCfg* pCfg)
{
    // 随机选择高级丹田ID
    return (pCfg && pCfg->nId > 0) ? pCfg->nId : 2;
}

// ========== Helper: check if LingZhuBag slot is empty ==========

static bool LingZhuBagIsEmpty(const KunLingZhuBagItem* pItem)
{
    return pItem->nId <= 0;
}

static bool DanTianIsEmpty(const KunDanTianItem* pItem)
{
    return pItem->nMid <= 0;
}

// ========== CKunExt ==========

CKunExt::CKunExt()
    : m_pPlayer(NULL)
    , m_nKunLevel(0)
    , m_nExp(0)
    , m_nBuyTime(0)
    , m_nLianHuaTime(0)
    , m_LastUpdateTick(0)
{
    memset(m_LingZhuBag, 0, sizeof(m_LingZhuBag));
    memset(m_DanTian, 0, sizeof(m_DanTian));
    memset(m_LingZhuPos, 0, sizeof(m_LingZhuPos));
}

CKunExt::~CKunExt()
{
}

void CKunExt::Init(Player* pPlayer)
{
    m_pPlayer = pPlayer;
}

void CKunExt::OnLoadFromDB(const PlayerDBData& dbData)
{
    memcpy(m_DanTian, dbData.m_KunData.m_DanTian, sizeof(m_DanTian));
    memcpy(m_LingZhuBag, dbData.m_KunData.m_LingZhuBag, sizeof(m_LingZhuBag));
    memcpy(m_LingZhuPos, dbData.m_KunData.m_LingZhuPos, sizeof(m_LingZhuPos));
    m_nBuyTime = dbData.m_KunData.m_nBuyTime;
    m_nLianHuaTime = dbData.m_KunData.m_nLianHuaTime;
    m_nKunLevel = dbData.m_KunData.m_nKunLevel;
    m_nExp = dbData.m_KunData.m_nExp;

    CheckSuit();

    // Apply talent skill from current level config
    const KunLevelUpCfg* pKunLevelUpCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetKunLevelUpCfg(m_nKunLevel);
    if (pKunLevelUpCfg && pKunLevelUpCfg->nTalentId > 0 && pKunLevelUpCfg->nTalentLevel > 0)
    {
        m_pPlayer->GetCharSkill().AddOtherSkill(pKunLevelUpCfg->nTalentId, pKunLevelUpCfg->nTalentLevel);
    }
}

void CKunExt::OnSaveToDB(PlayerDBData& dbData)
{
    memcpy(dbData.m_KunData.m_DanTian, m_DanTian, sizeof(m_DanTian));
    memcpy(dbData.m_KunData.m_LingZhuBag, m_LingZhuBag, sizeof(m_LingZhuBag));
    memcpy(dbData.m_KunData.m_LingZhuPos, m_LingZhuPos, sizeof(m_LingZhuPos));
    dbData.m_KunData.m_nBuyTime = m_nBuyTime;
    dbData.m_KunData.m_nLianHuaTime = m_nLianHuaTime;
    dbData.m_KunData.m_nKunLevel = m_nKunLevel;
    dbData.m_KunData.m_nExp = m_nExp;
}

void CKunExt::OnCleanUp()
{
    lSuitList.clear();
    m_nKunLevel = 0;
    m_nExp = 0;
    m_nBuyTime = 0;
    m_nLianHuaTime = 0;
    memset(m_DanTian, 0, sizeof(m_DanTian));
    memset(m_LingZhuBag, 0, sizeof(m_LingZhuBag));
    memset(m_LingZhuPos, 0, sizeof(m_LingZhuPos));
    m_LastUpdateTick = 0;
}

void CKunExt::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(CM_KUN_LING_LEVEL_UP);
    procList.push_back(CM_KUN_GET_LING_ZHU);
    procList.push_back(CM_KUN_RECOVERY_LING_ZHU);
    procList.push_back(CM_KUN_FAST_FINING);
    procList.push_back(CM_KUN_LING_ZHU_LEVEL_UP);
    procList.push_back(CM_KUN_BUY_LIAN_HUA_TIME);
    procList.push_back(CM_KUN_WEI_YANG);
}

int32_t CKunExt::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
    if (NULL == inPacket)
    {
        return 2;
    }

    switch (nProcId)
    {
    case CM_KUN_LING_LEVEL_UP:  return OnKunLingLevelUp(inPacket);
    case CM_KUN_GET_LING_ZHU:  return OnGetLingZhu(inPacket);
    case CM_KUN_RECOVERY_LING_ZHU:  return OnRecoveryLingZhu(inPacket);
    case CM_KUN_FAST_FINING:  return OnFastFining(inPacket);
    case CM_KUN_LING_ZHU_LEVEL_UP:  return OnLingZhuLevelUp(inPacket);
    case CM_KUN_BUY_LIAN_HUA_TIME:  return OnBuyLianHuaTime(inPacket);
    case CM_KUN_WEI_YANG:  return OnKunWeiYang(inPacket);
    default:   return 2;
    }
}

void CKunExt::OnUpdate(int64_t curTick)
{
    if (curTick - m_LastUpdateTick <= 999)
    {
        return;
    }
    m_LastUpdateTick = curTick;

    for (int32_t i = 0; i < MAX_DAN_TIAN; ++i)
    {
        if (!DanTianIsEmpty(&m_DanTian[i]) && m_DanTian[i].nEndTime > 0)
        {
            if (m_DanTian[i].nEndTime <= m_pPlayer->getNow())
            {
                int32_t nMid = m_DanTian[i].nMid;
                const DanTianCfg* pDanTian = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetDanTianCfg(nMid);
                if (pDanTian)
                {
                    m_DanTian[i].nEndTime = 0;
                    if (m_nKunLevel <= 10)
                    {
                        m_DanTian[i].nId = DanTianCfg::RandDanTianId(pDanTian);
                    }
                    else
                    {
                        m_DanTian[i].nId = DanTianCfg::RandHighDanTianId(pDanTian);
                    }
                    SendDanTianInfo(i);
                }
            }
        }
    }
}

void CKunExt::OnDaySwitch(int32_t nDiffDays)
{
    m_nBuyTime = 0;
    m_nLianHuaTime = 0;
    SendKunLingInfo();
}

// ========== Attribute ==========

void CKunExt::AddCharAttr()
{
    // Kun level attributes
    const KunLevelUpCfg* pKunLevelUpCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetKunLevelUpCfg(m_nKunLevel);
    if (pKunLevelUpCfg)
    {
        for (AddAttrList::const_iterator it = pKunLevelUpCfg->lAttrList.begin();
             it != pKunLevelUpCfg->lAttrList.end(); ++it)
        {
            m_pPlayer->AddAttrValue(static_cast<CObjAttrs::Index_T>(it->m_nAddAttrType), it->m_nAddAttrValue);
        }
    }

    // LingZhu position attributes
    for (int32_t i = 0; i < MAX_LING_ZHU_POS; ++i)
    {
        if (m_LingZhuPos[i] > 0)
        {
            const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(m_LingZhuPos[i]);
            if (pLingZhuCfg)
            {
                for (AddAttrList::const_iterator it = pLingZhuCfg->lAttrList.begin();
                     it != pLingZhuCfg->lAttrList.end(); ++it)
                {
                    m_pPlayer->AddAttrValue(static_cast<CObjAttrs::Index_T>(it->m_nAddAttrType), it->m_nAddAttrValue);
                }
            }
        }
    }

    // Suit attributes
    for (std::list<int32_t>::iterator it = lSuitList.begin(); it != lSuitList.end(); ++it)
    {
        const LingZhuSuit* pLingZhuSuit = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuSuit(*it);
        if (pLingZhuSuit)
        {
            for (AddAttrList::const_iterator ait = pLingZhuSuit->lAttrList.begin();
                 ait != pLingZhuSuit->lAttrList.end(); ++ait)
            {
                m_pPlayer->AddAttrValue(static_cast<CObjAttrs::Index_T>(ait->m_nAddAttrType), ait->m_nAddAttrValue);
            }
        }
    }
}

// ========== Send Methods ==========

void CKunExt::SendKunLingInfo()
{
    if (NULL == m_pPlayer)
    {
        return;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2DDD);
    if (NULL == packet)
    {
        return;
    }

    packet->writeInt32(m_nKunLevel);
    packet->writeInt32(m_nExp);
    packet->writeInt32(m_nBuyTime);
    packet->writeInt32(GetLeftLianHuaTimes());
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CKunExt::SendLingZhuBagAllItem()
{
    if (NULL == m_pPlayer)
    {
        return;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2DDE);
    if (NULL == packet)
    {
        return;
    }

    int32_t Count = 0;
    int32_t OldOffset = packet->getWOffset();
    packet->writeInt32(0);

    for (int32_t i = 0; i < MAX_LING_ZHU_BAG; ++i)
    {
        if (!LingZhuBagIsEmpty(&m_LingZhuBag[i]))
        {
            ++Count;
            packet->writeInt32(i);
            packet->writeInt32(m_LingZhuBag[i].nId);
            packet->writeInt32(m_LingZhuBag[i].nCount);
        }
    }

    int32_t NewOffset = packet->getWOffset();
    packet->setWOffset(OldOffset);
    packet->writeInt32(Count);
    packet->setWOffset(NewOffset);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CKunExt::SendLingZhuBagChangeItem(Int32List& changeList)
{
    if (NULL == m_pPlayer)
    {
        return;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2DDF);
    if (NULL == packet)
    {
        return;
    }

    int32_t Count = 0;
    int32_t OldOffset = packet->getWOffset();
    packet->writeInt32(0);

    for (Int32List::iterator it = changeList.begin(); it != changeList.end(); ++it)
    {
        int32_t idx = *it;
        if (idx >= 0 && idx < MAX_LING_ZHU_BAG)
        {
            ++Count;
            packet->writeInt32(idx);
            packet->writeInt32(m_LingZhuBag[idx].nId);
            packet->writeInt32(m_LingZhuBag[idx].nCount);
        }
    }

    int32_t NewOffset = packet->getWOffset();
    packet->setWOffset(OldOffset);
    packet->writeInt32(Count);
    packet->setWOffset(NewOffset);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CKunExt::SendDanTianInfo(int32_t Pos)
{
    if (NULL == m_pPlayer)
    {
        return;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2DE0);
    if (NULL == packet)
    {
        return;
    }

    if (Pos == -1)
    {
        packet->writeInt32(MAX_DAN_TIAN);
        for (int32_t i = 0; i < MAX_DAN_TIAN; ++i)
        {
            packet->writeInt32(i);
            packet->writeInt32(m_DanTian[i].nMid);
            packet->writeInt32(m_DanTian[i].nEndTime);
            packet->writeInt32(m_DanTian[i].nId);
        }
    }
    else if (Pos >= MAX_DAN_TIAN)
    {
        packet->writeInt32(0);
    }
    else
    {
        packet->writeInt32(1);
        packet->writeInt32(Pos);
        packet->writeInt32(m_DanTian[Pos].nMid);
        packet->writeInt32(m_DanTian[Pos].nEndTime);
        packet->writeInt32(m_DanTian[Pos].nId);
    }

    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CKunExt::SendLingZhuPosInfo(int32_t Pos)
{
    if (NULL == m_pPlayer)
    {
        return;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket(m_pPlayer->getConnId(), PACK_DISPATCH, 0x2DE1);
    if (NULL == packet)
    {
        return;
    }

    if (Pos == -1)
    {
        packet->writeInt32(MAX_LING_ZHU_POS);
        for (int32_t i = 0; i < MAX_LING_ZHU_POS; ++i)
        {
            packet->writeInt32(i);
            packet->writeInt32(m_LingZhuPos[i]);
        }
    }
    else if (Pos >= MAX_LING_ZHU_POS)
    {
        packet->writeInt32(0);
    }
    else
    {
        packet->writeInt32(1);
        packet->writeInt32(Pos);
        packet->writeInt32(m_LingZhuPos[Pos]);
    }

    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

// ========== LingZhuBag Operations ==========

bool CKunExt::AddLingZhuBagItem(int32_t LingZhuId, int32_t Count, ITEM_CHANGE_REASON addReason)
{
    if (LingZhuId <= 0 || Count <= 0 || NULL == m_pPlayer)
    {
        return false;
    }

    const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(LingZhuId);
    if (NULL == pLingZhuCfg)
    {
        return false;
    }

    // Type 100 = exp item
    if (pLingZhuCfg->nType == 100)
    {
        m_nExp += Count * pLingZhuCfg->nDecExp;
        m_pPlayer->GetBag().addItemChangeLog(addReason, LingZhuId, 11, 0, 2, Count, 0);
        SendKunLingInfo();
        return true;
    }

    // Try to stack existing item
    for (int32_t i = 0; i < MAX_LING_ZHU_BAG; ++i)
    {
        if (m_LingZhuBag[i].nId == LingZhuId)
        {
            m_LingZhuBag[i].nCount += Count;
            Int32List changeList;
            changeList.push_back(i);
            SendLingZhuBagChangeItem(changeList);
            m_pPlayer->GetBag().addItemChangeLog(addReason, m_LingZhuBag[i].nId, 11, 0, Count, 1, m_LingZhuBag[i].nCount);
            return true;
        }
    }

    // Find empty slot
    for (int32_t i = 0; i < MAX_LING_ZHU_BAG; ++i)
    {
        if (LingZhuBagIsEmpty(&m_LingZhuBag[i]))
        {
            m_LingZhuBag[i].nId = LingZhuId;
            m_LingZhuBag[i].nCount = Count;
            Int32List changeList;
            changeList.push_back(i);
            SendLingZhuBagChangeItem(changeList);
            m_pPlayer->GetBag().addItemChangeLog(addReason, m_LingZhuBag[i].nId, 11, 0, Count, 1, Count);
            return true;
        }
    }

    return false;
}

int32_t CKunExt::GetEmptyBagCount()
{
    int32_t Count = 0;
    for (int32_t i = 0; i < MAX_LING_ZHU_BAG; ++i)
    {
        if (LingZhuBagIsEmpty(&m_LingZhuBag[i]))
        {
            ++Count;
        }
    }
    return Count;
}

void CKunExt::AddExp(int32_t Exp)
{
    m_nExp += Exp;
    SendKunLingInfo();
}

bool CKunExt::ReMoveLingZhuItem(int32_t LingZhuId, int32_t Count, ITEM_CHANGE_REASON addReason)
{
    // Count total available
    int32_t HaveCount = 0;
    for (int32_t i = 0; i < MAX_LING_ZHU_BAG; ++i)
    {
        if (m_LingZhuBag[i].nId == LingZhuId)
        {
            HaveCount += m_LingZhuBag[i].nCount;
            if (HaveCount >= Count)
            {
                break;
            }
        }
    }

    if (HaveCount < Count)
    {
        return false;
    }

    int32_t NeedCount = Count;
    Int32List Pos;

    for (int32_t i = 0; i < MAX_LING_ZHU_BAG && NeedCount > 0; ++i)
    {
        if (m_LingZhuBag[i].nId == LingZhuId)
        {
            if (m_LingZhuBag[i].nCount > NeedCount)
            {
                m_LingZhuBag[i].nCount -= NeedCount;
                m_pPlayer->GetBag().addItemChangeLog(addReason, m_LingZhuBag[i].nId, 11, 0, Count, 2, m_LingZhuBag[i].nCount);
                Pos.push_back(i);
                break;
            }
            NeedCount -= m_LingZhuBag[i].nCount;
            m_pPlayer->GetBag().addItemChangeLog(addReason, m_LingZhuBag[i].nId, 11, 0, Count, 2, 0);
            memset(&m_LingZhuBag[i], 0, sizeof(KunLingZhuBagItem));
            Pos.push_back(i);
        }
    }

    SendLingZhuBagChangeItem(Pos);
    return true;
}

void CKunExt::RemoveLingZhuItem(Int32List& pPos, ITEM_CHANGE_REASON addReason)
{
    for (Int32List::iterator it = pPos.begin(); it != pPos.end(); ++it)
    {
        int32_t idx = *it;
        if (idx >= 0 && idx < MAX_LING_ZHU_BAG)
        {
            m_pPlayer->GetBag().addItemChangeLog(addReason, m_LingZhuBag[idx].nId, 11, 0, m_LingZhuBag[idx].nCount, 2, 0);
            memset(&m_LingZhuBag[idx], 0, sizeof(KunLingZhuBagItem));
        }
    }

    SendLingZhuBagChangeItem(pPos);
}

// ========== DanTian Operations ==========

bool CKunExt::AddDanTian(int32_t Mid)
{
    const DanTianCfg* pDanTian = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetDanTianCfg(Mid);
    if (NULL == pDanTian)
    {
        return false;
    }

    if (pDanTian->nRate < RANDOM.generate(1, 10000))
    {
        return false;
    }

    for (int32_t i = 0; i < MAX_DAN_TIAN; ++i)
    {
        if (DanTianIsEmpty(&m_DanTian[i]))
        {
            m_DanTian[i].nMid = Mid;
            m_DanTian[i].nId = 0;
            m_DanTian[i].nEndTime = m_pPlayer->getNow() + pDanTian->nTime;
            SendDanTianInfo(i);
            return true;
        }
    }

    return false;
}

// ========== Protocol Handlers ==========

int32_t CKunExt::OnKunLingLevelUp(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    const KunLevelUpCfg* pKunLevelUpCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetKunLevelUpCfg(m_nKunLevel);
    const KunLevelUpCfg* pNextCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetKunLevelUpCfg(m_nKunLevel + 1);

    if (NULL == pNextCfg || NULL == pKunLevelUpCfg)
    {
        return 2;
    }

    if (pKunLevelUpCfg->nExp > 0 && m_nExp < pKunLevelUpCfg->nExp)
    {
        return 2;
    }

    if (pKunLevelUpCfg->nCostMoney > 0)
    {
        if (m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < pKunLevelUpCfg->nCostMoney)
        {
            return 2;
        }
    }

    if (pKunLevelUpCfg->nCostShengYaoBi > 0)
    {
        if (m_pPlayer->GetCurrency(CURRENCY_VIGOUR) < pKunLevelUpCfg->nCostShengYaoBi)
        {
            return 2;
        }
    }

    // Consume costs
    if (pKunLevelUpCfg->nCostMoney > 0)
    {
        if (!m_pPlayer->GetCurrency().DecMoneyAndNoBind(pKunLevelUpCfg->nCostMoney, GCR_KUN_LEVEL_UP, 0))
        {
            return 2;
        }
    }

    if (pKunLevelUpCfg->nCostShengYaoBi > 0)
    {
        if (!m_pPlayer->DecCurrency(CURRENCY_VIGOUR, pKunLevelUpCfg->nCostShengYaoBi, GCR_KUN_LEVEL_UP, 0))
        {
            return 2;
        }
    }

    if (pKunLevelUpCfg->nExp > 0)
    {
        m_nExp -= pKunLevelUpCfg->nExp;
    }

    // Apply talent skill for next level
    if (pNextCfg->nTalentId > 0 && pNextCfg->nTalentLevel > 0)
    {
        m_pPlayer->GetCharSkill().AddOtherSkill(pNextCfg->nTalentId, pNextCfg->nTalentLevel);
    }

    ++m_nKunLevel;
    SendKunLingInfo();
    m_pPlayer->RecalcAttr();

    // Broadcast announcement
    if (pNextCfg->nGongGaoId > 0)
    {
        NetPacket* packet = GAME_SERVICE.popNetpacket(0, PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pNextCfg->nGongGaoId);
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt32(m_nKunLevel);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(0, packet);
        }
    }

    GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), inPacket->getProc(), pKunLevelUpCfg->nExp);
    return 0;
}

int32_t CKunExt::OnGetLingZhu(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    int32_t Pos = inPacket->readInt32();
    if (Pos >= MAX_DAN_TIAN)
    {
        return 2;
    }

    if (GetLeftLianHuaTimes() <= 0)
    {
        return 0;
    }

    if (DanTianIsEmpty(&m_DanTian[Pos]))
    {
        return 2;
    }

    if (m_DanTian[Pos].nEndTime > 0)
    {
        return 2;
    }

    int32_t nId = m_DanTian[Pos].nId;
    const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(nId);
    if (NULL == pLingZhuCfg)
    {
        return 2;
    }

    if (!AddLingZhuBagItem(m_DanTian[Pos].nId, 1, IDCR_DAN_TIAN_GET))
    {
        return 2;
    }

    if (pLingZhuCfg->nGetGongGao > 0)
    {
        NetPacket* packet = GAME_SERVICE.popNetpacket(0, PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pLingZhuCfg->nGetGongGao);
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt32(m_DanTian[Pos].nMid);
            packet->writeInt32(m_DanTian[Pos].nId);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(0, packet);
        }
    }

    ++m_nLianHuaTime;
    memset(&m_DanTian[Pos], 0, sizeof(KunDanTianItem));
    SendDanTianInfo(Pos);
    SendKunLingInfo();
    return 0;
}

int32_t CKunExt::OnRecoveryLingZhu(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    int32_t NeedAddExp = 0;
    Int32List changeList;

    for (int32_t i = 0; i < MAX_LING_ZHU_BAG; ++i)
    {
        if (!LingZhuBagIsEmpty(&m_LingZhuBag[i]))
        {
            int32_t nId = m_LingZhuBag[i].nId;
            const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(nId);
            if (pLingZhuCfg && pLingZhuCfg->nDecExp > 0)
            {
                // Only recover if slot is empty or no upgrade available
                if (pLingZhuCfg->nType >= 20)
                {
                    NeedAddExp += pLingZhuCfg->nDecExp * m_LingZhuBag[i].nCount;
                    changeList.push_back(i);
                }
                else
                {
                    int32_t posId = m_LingZhuPos[pLingZhuCfg->nType];
                    const LingZhuCfg* pPosCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(posId);
                    if (pPosCfg && pPosCfg->nNextId <= 0)
                    {
                        NeedAddExp += pLingZhuCfg->nDecExp * m_LingZhuBag[i].nCount;
                        changeList.push_back(i);
                    }
                }
            }
        }
    }

    if (NeedAddExp <= 0)
    {
        return 2;
    }

    RemoveLingZhuItem(changeList, IDCR_BAO_ZHU_HUI_SHOU);
    m_nExp += NeedAddExp;
    SendKunLingInfo();
    GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), inPacket->getProc(), NeedAddExp);
    return 0;
}

int32_t CKunExt::OnFastFining(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    int32_t Slot = inPacket->readInt32();
    if (Slot >= MAX_DAN_TIAN)
    {
        return 2;
    }

    if (DanTianIsEmpty(&m_DanTian[Slot]))
    {
        return 2;
    }

    if (m_DanTian[Slot].nEndTime <= 0)
    {
        return 2;
    }

    int32_t nMid = m_DanTian[Slot].nMid;
    const DanTianCfg* pDanTian = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetDanTianCfg(nMid);
    if (NULL == pDanTian)
    {
        return 2;
    }

    int32_t DiffTime = m_DanTian[Slot].nEndTime - m_pPlayer->getNow();
    if (DiffTime <= 0)
    {
        return 2;
    }

    int32_t Count = DiffTime / 600;
    if (DiffTime % 600)
    {
        ++Count;
    }

    if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, 10 * Count, GCR_KUN_KAST_FINING_COST, 0))
    {
        return 2;
    }

    m_DanTian[Slot].nEndTime = 0;
    if (m_nKunLevel <= 10)
    {
        m_DanTian[Slot].nId = DanTianCfg::RandDanTianId(pDanTian);
    }
    else
    {
        m_DanTian[Slot].nId = DanTianCfg::RandHighDanTianId(pDanTian);
    }

    SendDanTianInfo(Slot);
    return 0;
}

int32_t CKunExt::OnLingZhuLevelUp(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    int32_t Pos = inPacket->readInt32();
    if (Pos >= MAX_LING_ZHU_POS)
    {
        return 2;
    }

    int32_t nId = m_LingZhuPos[Pos];
    int32_t NeedMoney = 0;
    KunLingZhuBagItem NeedItem;
    memset(&NeedItem, 0, sizeof(NeedItem));

    if (nId > 0)
    {
        const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(nId);
        if (NULL == pLingZhuCfg)
        {
            return 2;
        }
        if (pLingZhuCfg->nKunLingLevel > m_nKunLevel)
        {
            return 2;
        }
        if (pLingZhuCfg->nCostMoney > 0)
        {
            if (m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < pLingZhuCfg->nCostMoney)
            {
                return 2;
            }
            NeedMoney = pLingZhuCfg->nCostMoney;
        }
        NeedItem.nId = pLingZhuCfg->nCostId;
        NeedItem.nCount = pLingZhuCfg->nCostCount;
        nId = pLingZhuCfg->nNextId;
    }
    else
    {
        const LingZhuPosCfg* pFirstCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuPosId(Pos);
        if (pFirstCfg)
        {
            nId = pFirstCfg->nFirstId;
            NeedItem.nId = pFirstCfg->nCostId;
            NeedItem.nCount = pFirstCfg->nCostCount;
            if (pFirstCfg->nMoney > 0)
            {
                if (m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < pFirstCfg->nMoney)
                {
                    return 2;
                }
                NeedMoney = pFirstCfg->nMoney;
            }
        }
    }

    if (nId <= 0)
    {
        return 2;
    }

    if (NeedItem.nId <= 0 || NeedItem.nCount <= 0)
    {
        return 2;
    }

    if (!ReMoveLingZhuItem(NeedItem.nId, NeedItem.nCount, IDCR_LING_ZHU_LEVEL_UP))
    {
        return 2;
    }

    if (NeedMoney > 0)
    {
        if (!m_pPlayer->GetCurrency().DecMoneyAndNoBind(NeedMoney, GCR_LING_ZHU_JI_HUO, 0))
        {
            return 2;
        }
    }

    int32_t OldId = m_LingZhuPos[Pos];
    m_LingZhuPos[Pos] = nId;
    SendLingZhuPosInfo(Pos);
    CheckSuit();
    m_pPlayer->RecalcAttr();

    GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), inPacket->getProc(), 0);

    // Broadcast level up announcement
    const LingZhuCfg* pNewLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(nId);
    if (pNewLingZhuCfg && pNewLingZhuCfg->nLevelUpGongGao > 0)
    {
        NetPacket* packet = GAME_SERVICE.popNetpacket(0, PACK_DISPATCH, 0x2CD6);
        if (packet)
        {
            packet->writeInt32(pNewLingZhuCfg->nLevelUpGongGao);
            packet->writeInt64(m_pPlayer->getCid());
            packet->writeUTF8(m_pPlayer->getName());
            packet->writeInt32(OldId);
            packet->writeInt32(nId);
            packet->setSize(packet->getWOffset());
            GAME_SERVICE.worldBroadcast(0, packet);
        }
    }

    return 0;
}

int32_t CKunExt::OnBuyLianHuaTime(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    if (m_nBuyTime > 1)
    {
        return 2;
    }

    if (m_nBuyTime == 0)
    {
        if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, 500, GCR_BUY_LIAN_HUA_TIME, 0))
        {
            return 2;
        }
    }
    else if (m_nBuyTime == 1)
    {
        if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, 2000, GCR_BUY_LIAN_HUA_TIME, 0))
        {
            return 2;
        }
    }

    ++m_nBuyTime;
    SendKunLingInfo();
    return 0;
}

int32_t CKunExt::OnKunWeiYang(Answer::NetPacket* inPacket)
{
    if (NULL == m_pPlayer || NULL == inPacket)
    {
        return 2;
    }

    int32_t nSize = inPacket->readInt32();
    int32_t AddValues = 0;
    Int32List bagSlotList;

    for (int32_t i = 0; i < nSize; ++i)
    {
        int32_t BagSlot = inPacket->readInt32();
        const MemChrBag* slotData = m_pPlayer->GetBag().GetSlotData(BagSlot);

        if (slotData->itemClass != 1)
        {
            return 2;
        }

        int32_t itemId = slotData->itemId;
        CfgItem* cfgItem = CFG_DATA.getItem(itemId);
        if (NULL == cfgItem || cfgItem->KunLingJingHua <= 0)
        {
            return 2;
        }

        AddValues += cfgItem->KunLingJingHua * slotData->itemCount;
        bagSlotList.push_back(BagSlot);
    }

    if (AddValues <= 0 || bagSlotList.empty())
    {
        return 2;
    }

    for (Int32List::iterator it = bagSlotList.begin(); it != bagSlotList.end(); ++it)
    {
        m_pPlayer->GetBag().CleanSlot(*it, IDCR_KUN_WEI_YANG);
    }

    m_pPlayer->GetBag().ForceSendDirty();
    m_nExp += AddValues;
    SendKunLingInfo();

    GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

// ========== Suit/Skill ==========

void CKunExt::CheckSuit()
{
    lSuitList.clear();

    for (int32_t i = 0; i < 4; ++i)
    {
        int32_t SuitId = 0;
        for (int32_t j = 5 * i; j < 5 * (i + 1); ++j)
        {
            if (m_LingZhuPos[j] <= 0)
            {
                SuitId = 0;
                break;
            }

            int32_t posId = m_LingZhuPos[j];
            const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(posId);
            if (NULL == pLingZhuCfg || pLingZhuCfg->nSuitId <= 0)
            {
                SuitId = 0;
                break;
            }

            if (SuitId == 0)
            {
                SuitId = pLingZhuCfg->nSuitId;
            }
            else
            {
                SuitId = std::min(SuitId, pLingZhuCfg->nSuitId);
            }
        }

        if (SuitId > 0)
        {
            lSuitList.push_back(SuitId);
        }
    }

    CheckAddSuitSkill();
}

void CKunExt::CheckAddSuitSkill()
{
    int32_t nSuitLevel = 0;

    for (int32_t i = 0; i < MAX_LING_ZHU_POS; ++i)
    {
        if (m_LingZhuPos[i] <= 0)
        {
            return;
        }

        const LingZhuCfg* pLingZhuCfg = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuCfg(m_LingZhuPos[i]);
        if (NULL == pLingZhuCfg || pLingZhuCfg->nLevel <= 0)
        {
            return;
        }

        if (nSuitLevel == 0)
        {
            nSuitLevel = pLingZhuCfg->nLevel;
        }
        else
        {
            nSuitLevel = std::min(nSuitLevel, pLingZhuCfg->nLevel);
        }
    }

    if (nSuitLevel > 0)
    {
        const LingZhuSkill* pLingZhuSkill = ((KunLingTable*)CFG_DATA.GetKunLingTable())->GetLingZhuSkill(nSuitLevel);
        if (pLingZhuSkill && pLingZhuSkill->TalentId > 0 && pLingZhuSkill->TalentLevel > 0)
        {
            m_pPlayer->GetCharSkill().AddOtherSkill(pLingZhuSkill->TalentId, pLingZhuSkill->TalentLevel);
        }
    }
}

int32_t CKunExt::GetLeftLianHuaTimes()
{
    int32_t AddTime = 0;
    if (m_nBuyTime == 1)
    {
        AddTime = 5;
    }
    else if (m_nBuyTime == 2)
    {
        AddTime = 15;
    }
    return AddTime + 10 - m_nLianHuaTime;
}
