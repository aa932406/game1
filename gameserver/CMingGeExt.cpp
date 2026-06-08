#include "stdafx.h"
#include "CMingGeExt.h"
#include "CMingGeTable.h"
#include "GameService.h"
#include "Player.h"
#include "Timer.h"

using namespace Answer;

CMingGeExt::CMingGeExt()
    : CExtSystemBase()
    , m_MingGeExp(0)
    , m_MingChip(0)
{
    bzero(m_MingGeBag, sizeof(m_MingGeBag));
    bzero(m_LieMingBag, sizeof(m_LieMingBag));
    bzero(m_MingGeEquip, sizeof(m_MingGeEquip));
    bzero(m_MingGeNpc, sizeof(m_MingGeNpc));
}

CMingGeExt::~CMingGeExt()
{
}

void CMingGeExt::GetInterestsProtocol(ProcIdList& procList)
{
    procList.push_back(CM_MING_GE_LEVEL_UP);
    procList.push_back(CM_MING_GE_PICKUP);
    procList.push_back(CM_MING_GE_LOCK);
    procList.push_back(CM_MING_GE_DEC);
    procList.push_back(CM_MING_GE_DUI_HUAN);
    procList.push_back(CM_MING_GE_LIE_MING);
    procList.push_back(CM_MING_GE_DRESS);
    procList.push_back(CM_MING_GE_UNDRESS);
    procList.push_back(CM_MING_GE_BUY_NPC);
}

int32_t CMingGeExt::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket *inPacket)
{
    if (!inPacket)
        return 2;
    switch (nProcId)
    {
    case CM_MING_GE_LEVEL_UP:   return OnMingGeLevelUp(inPacket);
    case CM_MING_GE_PICKUP:     return OnPickupMingGe(inPacket);
    case CM_MING_GE_LOCK:       return OnLock(inPacket);
    case CM_MING_GE_DEC:        return OnDecMingGe(inPacket);
    case CM_MING_GE_DUI_HUAN:   return OnDuiHuan(inPacket);
    case CM_MING_GE_LIE_MING:   return OnLieMing(inPacket);
    case CM_MING_GE_DRESS:      return OnDress(inPacket);
    case CM_MING_GE_UNDRESS:    return OnUnDress(inPacket);
    case CM_MING_GE_BUY_NPC:    return OnBuyNpc(inPacket);
    default: return 2;
    }
}

// CMingGeData handles its own DB persistence (SaveToSqlString/LoadFromDB)
// via CMingGeExt::OnSaveToDB is not needed because CMingGeData is saved
// directly through the database service, independent of PlayerDBData.
void CMingGeExt::OnLoadFromDB(const PlayerDBData *const dbData)
{
    // CMingGeData manages persistence independently via LoadFromDB()
    if (!dbData)
        return;
}

void CMingGeExt::OnSaveToDB(PlayerDBData *const dbData)
{
    // CMingGeData manages persistence independently via SaveToSqlString()
    if (!dbData)
        return;
}

void CMingGeExt::OnCleanUp()
{
    bzero(m_MingGeBag, sizeof(m_MingGeBag));
    bzero(m_LieMingBag, sizeof(m_LieMingBag));
    bzero(m_MingGeEquip, sizeof(m_MingGeEquip));
    bzero(m_MingGeNpc, sizeof(m_MingGeNpc));
    m_MingGeExp = 0;
    m_MingChip = 0;
}

// ========== Send ==========

void CMingGeExt::SendMingGeInfo()
{
    if (!m_pPlayer)
        return;
    Answer::NetPacket* packet =     popNetpacket(m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_MING_GE_INFO);
    if (!packet)
        return;
    packet->writeInt32(m_MingGeExp);
    packet->writeInt32(m_MingChip);
    for (int32_t i = 0; i < 5; ++i)
    {
        if (i)
            packet->writeInt32(m_MingGeNpc[i]);
        else
            packet->writeInt32(1);
    }
    packet->setSize(packet->getWOffset());
    sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CMingGeExt::SendMingGeBagInfo(int32_t nType)
{
    if (!m_pPlayer || nType <= 0 || nType > 3)
        return;
    Answer::NetPacket* packet = popNetpacket(m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_MING_GE_BAG_INFO);
    if (!packet)
        return;
    if (nType == 1)
        PackMingGeBagInfo(packet);
    else if (nType == 2)
        PackLeiMingBagInfo(packet);
    else
        PackMingGeEquipBagInfo(packet);
    packet->setSize(packet->getWOffset());
    sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CMingGeExt::SendMingGeBagInfo(int32_t nType, int32_t nSlot)
{
    if (!m_pPlayer)
        return;
    Answer::NetPacket* packet = popNetpacket(m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_MING_GE_SLOT_INFO);
    if (!packet)
        return;
    packet->writeInt32(nType);
    packet->writeInt32(nSlot);
    MingGe stu = GetSlotItem(nType, nSlot);
    packet->writeInt32(stu.nId);
    packet->writeInt32(stu.IsLock);
    packet->setSize(packet->getWOffset());
    sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

// ========== Pack ==========

void CMingGeExt::PackMingGeBagInfo(Answer::NetPacket *packet)
{
    packet->writeInt32(1);
    int32_t oldOffet = packet->getWOffset();
    int32_t count = 0;
    packet->writeInt32(0);
    for (int32_t i = 0; i < 100; ++i)
    {
        if (!MingGe::IsEmpty(&m_MingGeBag[i]))
        {
            ++count;
            packet->writeInt32(i);
            packet->writeInt32(m_MingGeBag[i].nId);
            packet->writeInt32(m_MingGeBag[i].IsLock);
        }
    }
    int32_t newOffet = packet->getWOffset();
    packet->setWOffset(oldOffet);
    packet->writeInt32(count);
    packet->setWOffset(newOffet);
}

void CMingGeExt::PackLeiMingBagInfo(Answer::NetPacket *packet)
{
    packet->writeInt32(3);
    int32_t oldOffet = packet->getWOffset();
    int32_t count = 0;
    packet->writeInt32(0);
    for (int32_t i = 0; i < 8; ++i)
    {
        if (!MingGe::IsEmpty(&m_MingGeEquip[i]))
        {
            ++count;
            packet->writeInt32(i);
            packet->writeInt32(m_MingGeEquip[i].nId);
            packet->writeInt32(m_MingGeEquip[i].IsLock);
        }
    }
    int32_t newOffet = packet->getWOffset();
    packet->setWOffset(oldOffet);
    packet->writeInt32(count);
    packet->setWOffset(newOffet);
}

void CMingGeExt::PackMingGeEquipBagInfo(Answer::NetPacket *packet)
{
    packet->writeInt32(2);
    int32_t oldOffet = packet->getWOffset();
    int32_t count = 0;
    packet->writeInt32(0);
    for (int32_t i = 0; i < 30; ++i)
    {
        if (!MingGe::IsEmpty(&m_LieMingBag[i]))
        {
            ++count;
            packet->writeInt32(i);
            packet->writeInt32(m_LieMingBag[i].nId);
            packet->writeInt32(m_LieMingBag[i].IsLock);
        }
    }
    int32_t newOffet = packet->getWOffset();
    packet->setWOffset(oldOffet);
    packet->writeInt32(count);
    packet->setWOffset(newOffet);
}

// ========== Protocol Handlers ==========

int32_t CMingGeExt::OnMingGeLevelUp(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nSlot = inPacket->readInt32();
    if (IsInvalidSlot(3, nSlot))
        return 2;
    MingGe MG = GetSlotItem(3, nSlot);
    if (MingGe::IsEmpty(&MG))
        return 2;
    int32_t nId = MG.nId;
    const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(nId);
    if (!pCfg || pCfg->nNextId <= 0 || pCfg->nUpExp <= 0)
        return 2;
    if (m_MingGeExp < pCfg->nUpExp)
        return 2;
    m_MingGeExp -= pCfg->nUpExp;
    MG.nId = pCfg->nNextId;
    SetSlot(3, nSlot, MG, ICR_MING_GE_LEVEL_UP);
    SendMingGeInfo();
    m_pPlayer->RecalcAttr();
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

int32_t CMingGeExt::OnPickupMingGe(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nSlot = inPacket->readInt32();
    int8_t IsAuto = inPacket->readInt8();
    if (IsInvalidSlot(2, nSlot))
        return 2;
    MingGe MG = GetSlotItem(2, nSlot);
    if (MingGe::IsEmpty(&MG))
        return 2;
    int32_t nId = MG.nId;
    const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(nId);
    if (!pCfg || pCfg->nCanPickup)
        return 2;
    int32_t FreeSlot = GetBagFreeSlot(1);
    if (FreeSlot < 0)
        return 2;
    if (RemoveItem(2, nSlot, ICR_SHI_QU_MING_GE))
        AddBagItem(1, FreeSlot, MG, ICR_SHI_QU_MING_GE);
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), IsAuto);
    return 0;
}

int32_t CMingGeExt::OnLock(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nSlot = inPacket->readInt32();
    int8_t State = inPacket->readInt8();
    if (IsInvalidSlot(1, nSlot))
        return 2;
    MingGe MG = GetSlotItem(1, nSlot);
    if (MingGe::IsEmpty(&MG))
        return 2;
    MG.IsLock = (State == 1) ? 1 : 0;
    SetSlot(1, nSlot, MG, ICR_MING_GE_LOCK);
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

int32_t CMingGeExt::OnDecMingGe(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nBagType = inPacket->readInt32();
    int32_t nSlot = inPacket->readInt32();
    if (nBagType == 3 || IsInvalidSlot(nBagType, nSlot))
        return 2;
    MingGe MG = GetSlotItem(nBagType, nSlot);
    if (MingGe::IsEmpty(&MG) || MG.IsLock > 0)
        return 2;
    const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(MG.nId);
    if (!pCfg)
        return 2;
    if (!RemoveItem(nBagType, nSlot, ICR_MING_GE_DEC))
        return 2;
    if (pCfg->nDecExp > 0)
        m_MingGeExp += pCfg->nDecExp;
    if (pCfg->nDecMoney > 0)
        m_pPlayer->AddCurrency(CURRENCY_BIND_MONEY, pCfg->nDecMoney, GCR_DEC_MING_GE, 0);
    SendMingGeInfo();
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nBagType);
    return 0;
}

int32_t CMingGeExt::OnDuiHuan(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nId = inPacket->readInt32();
    const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(nId);
    if (!pCfg || pCfg->nCostChip <= 0)
        return 2;
    int32_t nFreeSlot = GetBagFreeSlot(1);
    if (nFreeSlot < 0)
        return 2;
    if (m_MingChip < pCfg->nCostChip)
        return 2;
    m_MingChip -= pCfg->nCostChip;
    MingGe MG;
    MG.nId = nId;
    AddBagItem(1, nFreeSlot, MG, ICR_MING_GE_DUI_HUAN);
    SendMingGeInfo();
    GongGao(510, nId);
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

int32_t CMingGeExt::OnLieMing(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nType = inPacket->readInt32();
    int8_t IsAuto = inPacket->readInt8();
    if (nType != 1)
    {
        if (nType <= 1 || nType > 5)
            return 2;
        if (*(&m_MingChip + nType) <= 0)
            return 2;
    }

    const MingGeDrawCost* pCost = CFG_DATA.GetMingGeTable().GetMingGeDrawCost(nType);
    if (!pCost)
        return 2;

    int32_t MingGeId = CFG_DATA.GetMingGeTable().RandMingGe(nType);
    if (MingGeId <= 0)
        return 2;

    const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(MingGeId);
    if (!pCfg)
        return 2;

    int32_t nFreeSlot = GetBagFreeSlot(2);
    if (nFreeSlot < 0)
        return 2;

    if (pCost->nConstMoney > 0)
    {
        int32_t LieMingTimes = m_pPlayer->getRecord(2108);
        if (LieMingTimes > 1000) LieMingTimes = 1000;
        float rate = GetRate(LieMingTimes);
        int32_t ConstMoney = (int32_t)(rate * (float)(pCost->nConstMoney * (LieMingTimes / 20))) + pCost->nConstMoney;
        if (!m_pPlayer->DecCurrency(CURRENCY_BIND_MONEY, ConstMoney, GCR_LIE_MING, LieMingTimes))
            return 2;
        m_pPlayer->updateRecord(2109, ConstMoney);
        m_pPlayer->GetCurrency().SendCurrencyInfo(false);
    }

    MingGe MG;
    MG.nId = MingGeId;
    AddBagItem(2, nFreeSlot, MG, ICR_MING_GE_LIE_MING);
    *(&m_MingChip + nType) = 0;

    if (pCost->nRate > 0 && pCost->nRate >= RANDOM.generate(1, 10000))
    {
        int32_t nTypea = nType + 1;
        if (nTypea > 0 && nTypea <= 5)
            *(&m_MingChip + nTypea) = 1;
    }

    m_pPlayer->updateRecord(2108, 1);
    SendMingGeInfo();

    if (pCfg->nQuality > 4 && !pCfg->nCanPickup)
        GongGao(509, MingGeId);

    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), IsAuto);
    return 0;
}

int32_t CMingGeExt::OnDress(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nBagSlot = inPacket->readInt32();
    int32_t nEquipSlot = inPacket->readInt32();
    if (IsInvalidSlot(1, nBagSlot) || IsInvalidSlot(3, nEquipSlot))
        return 2;
    MingGe BagMingGe = GetSlotItem(1, nBagSlot);
    int32_t SameMingGeSlot = GetSameTypeMingGe(BagMingGe.nId);
    if (SameMingGeSlot >= 0 && SameMingGeSlot != nEquipSlot)
        return 2;
    MingGe SlotItem = GetSlotItem(3, nEquipSlot);
    SetSlot(1, nBagSlot, SlotItem, ICR_MING_GE_DRESS);
    SetSlot(3, nEquipSlot, BagMingGe, ICR_MING_GE_DRESS);
    m_pPlayer->RecalcAttr();
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

int32_t CMingGeExt::OnUnDress(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nEquipSlot = inPacket->readInt32();
    if (IsInvalidSlot(3, nEquipSlot))
        return 2;
    int32_t nFreeSlot = GetBagFreeSlot(1);
    if (nFreeSlot < 0)
        return 2;
    MingGe Stu = GetSlotItem(3, nEquipSlot);
    SetSlot(3, nEquipSlot, MingGe(), ICR_MING_GE_UNDRESS);
    AddBagItem(1, nFreeSlot, Stu, ICR_MING_GE_UNDRESS);
    m_pPlayer->RecalcAttr();
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

int32_t CMingGeExt::OnBuyNpc(Answer::NetPacket *inPacket)
{
    if (!m_pPlayer || !inPacket)
        return 2;
    int32_t nType = inPacket->readInt32();
    if (nType <= 1 || nType > 5)
        return 2;
    if (*(&m_MingChip + nType) > 0)
        return 2;
    const MingGeDrawCost* pCost = CFG_DATA.GetMingGeTable().GetMingGeDrawCost(nType);
    if (!pCost || pCost->nConstGold <= 0)
        return 2;
    if (!m_pPlayer->DecCurrency(CURRENCY_GOLD, pCost->nConstGold, GCR_BUY_NPC, 0))
        return 2;
    *(&m_MingChip + nType) = 1;
    SendMingGeInfo();
    replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
    return 0;
}

// ========== Bag Operations ==========

int32_t CMingGeExt::GetBagFreeSlot(int32_t nType)
{
    switch (nType)
    {
    case 1:
        for (int32_t i = 0; i < 100; ++i)
            if (MingGe::IsEmpty(&m_MingGeBag[i])) return i;
        break;
    case 2:
        for (int32_t i = 0; i < 30; ++i)
            if (MingGe::IsEmpty(&m_LieMingBag[i])) return i;
        break;
    case 3:
        for (int32_t i = 0; i < 8; ++i)
            if (MingGe::IsEmpty(&m_MingGeEquip[i])) return i;
        break;
    }
    return -1;
}

int32_t CMingGeExt::GetBagFreeSlotCount(int32_t nType)
{
    int32_t Count = 0;
    switch (nType)
    {
    case 1:
        for (int32_t i = 0; i < 100; ++i)
            if (MingGe::IsEmpty(&m_MingGeBag[i])) ++Count;
        break;
    case 2:
        for (int32_t i = 0; i < 30; ++i)
            if (MingGe::IsEmpty(&m_LieMingBag[i])) ++Count;
        break;
    case 3:
        for (int32_t i = 0; i < 8; ++i)
            if (MingGe::IsEmpty(&m_MingGeEquip[i])) ++Count;
        break;
    }
    return Count;
}

int32_t CMingGeExt::GetSameTypeMingGe(int32_t MingGeId)
{
    const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(MingGeId);
    if (!pCfg)
        return -1;
    for (int32_t i = 0; i < 8; ++i)
    {
        if (!MingGe::IsEmpty(&m_MingGeEquip[i]))
        {
            const CMingGeCfg* pEquipCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(m_MingGeEquip[i].nId);
            if (pEquipCfg && pCfg->nType == pEquipCfg->nType)
                return i;
        }
    }
    return -1;
}

bool CMingGeExt::AddBagItem(int32_t nType, int32_t Slot, MingGe stu, ITEM_CHANGE_REASON Reason)
{
    MingGe SlotItem = GetSlotItem(nType, Slot);
    if (!MingGe::IsEmpty(&SlotItem))
        return false;
    return SetSlot(nType, Slot, stu, Reason);
}

bool CMingGeExt::RemoveItem(int32_t nType, int32_t Slot, ITEM_CHANGE_REASON Reason)
{
    if (IsInvalidSlot(nType, Slot))
        return false;
    return SetSlot(nType, Slot, MingGe(), Reason);
}

bool CMingGeExt::SetSlot(int32_t nType, int32_t Slot, MingGe stu, ITEM_CHANGE_REASON Reason)
{
    if (IsInvalidSlot(nType, Slot) || !m_pPlayer)
        return false;

    MGLog LogStu;
    memset(&LogStu, 0, sizeof(LogStu));
    LogStu.Cid = m_pPlayer->getCid();
    LogStu.Time = TIMER.GetNow();
    LogStu.Reason = Reason;
    LogStu.BagType = nType;

    switch (nType)
    {
    case 1:
    {
        if (MingGe::IsEmpty(&m_MingGeBag[Slot]) && !MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = stu.nId; LogStu.Flag = 1; AddMingGeLog(LogStu); }
        else if (!MingGe::IsEmpty(&m_MingGeBag[Slot]) && !MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = stu.nId; LogStu.Flag = 1; AddMingGeLog(LogStu);
          LogStu.MingGeId = m_MingGeBag[Slot].nId; LogStu.Flag = 2; AddMingGeLog(LogStu); }
        else if (!MingGe::IsEmpty(&m_MingGeBag[Slot]) && MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = m_MingGeBag[Slot].nId; LogStu.Flag = 2; AddMingGeLog(LogStu); }
        m_MingGeBag[Slot] = stu;
        break;
    }
    case 2:
    {
        if (MingGe::IsEmpty(&m_LieMingBag[Slot]) && !MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = stu.nId; LogStu.Flag = 1; AddMingGeLog(LogStu); }
        else if (!MingGe::IsEmpty(&m_LieMingBag[Slot]) && !MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = stu.nId; LogStu.Flag = 1; AddMingGeLog(LogStu);
          LogStu.MingGeId = m_LieMingBag[Slot].nId; LogStu.Flag = 2; AddMingGeLog(LogStu); }
        else if (!MingGe::IsEmpty(&m_LieMingBag[Slot]) && MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = m_LieMingBag[Slot].nId; LogStu.Flag = 2; AddMingGeLog(LogStu); }
        m_LieMingBag[Slot] = stu;
        break;
    }
    case 3:
    {
        if (MingGe::IsEmpty(&m_MingGeEquip[Slot]) && !MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = stu.nId; LogStu.Flag = 1; AddMingGeLog(LogStu); }
        else if (!MingGe::IsEmpty(&m_MingGeEquip[Slot]) && !MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = stu.nId; LogStu.Flag = 1; AddMingGeLog(LogStu);
          LogStu.MingGeId = m_MingGeEquip[Slot].nId; LogStu.Flag = 2; AddMingGeLog(LogStu); }
        else if (!MingGe::IsEmpty(&m_MingGeEquip[Slot]) && MingGe::IsEmpty(&stu))
        { LogStu.MingGeId = m_MingGeEquip[Slot].nId; LogStu.Flag = 2; AddMingGeLog(LogStu); }
        m_MingGeEquip[Slot] = stu;
        break;
    }
    default:
        return false;
    }
    SendMingGeBagInfo(nType, Slot);
    return true;
}

MingGe CMingGeExt::GetSlotItem(int32_t nType, int32_t Slot)
{
    switch (nType)
    {
    case 1:
        if (!IsInvalidSlot(1, Slot)) return m_MingGeBag[Slot];
        break;
    case 2:
        if (!IsInvalidSlot(2, Slot)) return m_LieMingBag[Slot];
        break;
    case 3:
        if (!IsInvalidSlot(3, Slot)) return m_MingGeEquip[Slot];
        break;
    }
    return MingGe();
}

// ========== Logic ==========

void CMingGeExt::AddAttr()
{
    if (!m_pPlayer)
        return;
    for (int32_t i = 0; i < 8; ++i)
    {
        if (!MingGe::IsEmpty(&m_MingGeEquip[i]))
        {
            const CMingGeCfg* pCfg = CFG_DATA.GetMingGeTable().GetCMingGeCfg(m_MingGeEquip[i].nId);
            if (pCfg)
            {
                for (std::list<MingGeAddAttr>::const_iterator it = pCfg->lAttrList.begin();
                     it != pCfg->lAttrList.end(); ++it)
                {
                    m_pPlayer->AddAttrValue((CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue);
                }
            }
        }
    }
}

bool CMingGeExt::AddMingGeChip(int32_t Count)
{
    if (!m_pPlayer || Count <= 0)
        return false;
    m_MingChip += Count;
    SendMingGeInfo();
    return true;
}

bool CMingGeExt::AddItem(int32_t nId, ITEM_CHANGE_REASON Reason)
{
    if (!CFG_DATA.GetMingGeTable().GetCMingGeCfg(nId))
        return false;
    int32_t FreeSlot = GetBagFreeSlot(1);
    if (FreeSlot < 0)
        return false;
    MingGe MG;
    MG.nId = nId;
    return AddBagItem(1, FreeSlot, MG, Reason);
}

bool CMingGeExt::AddExp(int32_t Exp)
{
    if (Exp <= 0)
        return false;
    m_MingGeExp += Exp;
    SendMingGeInfo();
    return true;
}

void CMingGeExt::GongGao(int32_t GongGaoId, int32_t MingGeId)
{
    if (!m_pPlayer)
        return;
    Answer::NetPacket* packet = popNetpacket(m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM);
    if (!packet)
        return;
    packet->writeInt32(GongGaoId);
    packet->writeInt64(m_pPlayer->getCid());
    packet->writeUTF8(m_pPlayer->getName());
    packet->writeInt32(MingGeId);
    packet->setSize(packet->getWOffset());
    worldBroadcast(m_pPlayer->getConnId(), packet);
}

void CMingGeExt::AddMingGeLog(MGLog Stu)
{
    // DB日志记录 — 写入 ming_ge_log 表
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    snprintf( szSQL, sizeof(szSQL),
        "INSERT INTO `ming_ge_log` (char_id, time, reason, bag_type, ming_ge_id, flag) VALUES (%lld,%d,%d,%d,%d,%d)",
        Stu.Cid, Stu.Time, (int32_t)Stu.Reason, Stu.BagType, Stu.MingGeId, Stu.Flag );
    db.excute( szSQL );
}

float CMingGeExt::GetRate(int32_t Times)
{
    if (Times > 100)
        return 0.2f;
    return 0.0f;
}
