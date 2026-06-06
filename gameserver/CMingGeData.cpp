#include "stdafx.h"
#include "CMingGeData.h"
#include "GameService.h"
#include "Timer.h"
#include <sstream>

using namespace Answer;

bool IsInvalidSlot(int32_t nBagType, int32_t nSlot)
{
    switch (nBagType)
    {
    case 1: return nSlot < 0 || nSlot >= 100;
    case 2: return nSlot < 0 || nSlot >= 30;
    case 3: return nSlot < 0 || nSlot >= 8;
    default: return true;
    }
}

CMingGeData::CMingGeData()
{
    CleanUp();
}

CMingGeData::~CMingGeData()
{
}

void CMingGeData::CleanUp()
{
    m_MingGeExp = 0;
    m_MingChip = 0;
    bzero(m_MingGeBag, sizeof(m_MingGeBag));
    bzero(m_LieMingBag, sizeof(m_LieMingBag));
    bzero(m_MingGeEquip, sizeof(m_MingGeEquip));
    bzero(m_MingGeNpc, sizeof(m_MingGeNpc));
}

void CMingGeData::SaveToSqlString(SqlStringList& sqls, char (&szSQL)[4096], CharId_t nCid)
{
    bzero(szSQL, sizeof(szSQL));
    snprintf(szSQL, sizeof(szSQL) - 1, "DELETE FROM mem_chr_ming_ge_bag WHERE Cid = %lld", nCid);
    sqls.push_back(std::string(szSQL));

    for (int32_t slot = 0; slot < 100; ++slot)
    {
        if (m_MingGeBag[slot].nId > 0)
        {
            bzero(szSQL, sizeof(szSQL));
            snprintf(szSQL, sizeof(szSQL) - 1,
                "INSERT INTO `mem_chr_ming_ge_bag` (`cid`, `bag`, `slot`, `id`, `lock`) VALUES (%lld, %d, %d, %d, %d)",
                nCid, 1, slot, m_MingGeBag[slot].nId, m_MingGeBag[slot].IsLock);
            sqls.push_back(std::string(szSQL));
        }
    }

    for (int32_t slot = 0; slot < 30; ++slot)
    {
        if (m_LieMingBag[slot].nId > 0)
        {
            bzero(szSQL, sizeof(szSQL));
            snprintf(szSQL, sizeof(szSQL) - 1,
                "INSERT INTO `mem_chr_ming_ge_bag` (`cid`, `bag`, `slot`, `id`, `lock`) VALUES (%lld, %d, %d, %d, %d)",
                nCid, 2, slot, m_LieMingBag[slot].nId, m_LieMingBag[slot].IsLock);
            sqls.push_back(std::string(szSQL));
        }
    }

    for (int32_t slot = 0; slot < 8; ++slot)
    {
        if (m_MingGeEquip[slot].nId > 0)
        {
            bzero(szSQL, sizeof(szSQL));
            snprintf(szSQL, sizeof(szSQL) - 1,
                "INSERT INTO `mem_chr_ming_ge_bag` (`cid`, `bag`, `slot`, `id`, `lock`) VALUES (%lld, %d, %d, %d, %d)",
                nCid, 3, slot, m_MingGeEquip[slot].nId, m_MingGeEquip[slot].IsLock);
            sqls.push_back(std::string(szSQL));
        }
    }

    bzero(szSQL, sizeof(szSQL));
    std::string npcStr = GetNpcString();
    snprintf(szSQL, sizeof(szSQL) - 1,
        "INSERT INTO `mem_chr_ming_ge_info` (`cid`,`ming_ge_exp`,`ming_ge_chip`,`ming_ge_npc`) VALUES (%lld,%d,%d,'%s')"
        " ON DUPLICATE KEY UPDATE `ming_ge_exp`=%d,`ming_ge_chip`=%d,`ming_ge_npc`='%s'",
        nCid, m_MingGeExp, m_MingChip, npcStr.c_str(),
        m_MingGeExp, m_MingChip, npcStr.c_str());
    sqls.push_back(std::string(szSQL));
}

bool CMingGeData::LoadFromDB(Answer::MySqlDBGuard& db, char (&szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)
{
    bzero(szSQL, sizeof(szSQL));
    snprintf(szSQL, sizeof(szSQL) - 1, "SELECT * FROM `mem_chr_ming_ge_bag` WHERE `cid`=%lld", nCid);
    Answer::MySqlQuery result = db.query(szSQL);
    while (!result.eof())
    {
        int32_t bag = result.getIntValue("bag", 0);
        int32_t slot = result.getIntValue("slot", 0);
        MingGe stu;
        stu.nId = result.getIntValue("id", 0);
        stu.IsLock = result.getIntValue("lock", 0);
        if (!IsInvalidSlot(bag, slot))
        {
            switch (bag)
            {
            case 1: m_MingGeBag[slot] = stu; break;
            case 2: m_LieMingBag[slot] = stu; break;
            case 3: m_MingGeEquip[slot] = stu; break;
            }
        }
        result.nextRow();
    }

    bzero(szSQL, sizeof(szSQL));
    snprintf(szSQL, sizeof(szSQL) - 1, "SELECT * FROM `mem_chr_ming_ge_info` WHERE `Cid`=%lld", nCid);
    Answer::MySqlQuery resultInfo = db.query(szSQL);
    if (!resultInfo.eof())
    {
        m_MingGeExp = resultInfo.getIntValue("ming_ge_exp", 0);
        m_MingChip = resultInfo.getIntValue("ming_ge_chip", 0);
        std::string npcStr = resultInfo.getStringValue("ming_ge_npc", "");
        parseMingGeNpc(&npcStr);
    }
    return true;
}

std::string CMingGeData::GetNpcString()
{
    std::ostringstream ss;
    for (int32_t i = 0; i < 5; ++i)
    {
        ss << i << ":" << m_MingGeNpc[i] << "|";
    }
    return ss.str();
}

void CMingGeData::parseMingGeNpc(std::string* pStr)
{
    if (pStr == NULL || pStr->empty())
        return;

    StringVector vStr = Answer::StringUtility::split(*pStr, "|");
    for (size_t i = 0; i < vStr.size(); ++i)
    {
        StringVector tv = Answer::StringUtility::split(vStr[i], ":");
        if (tv.size() == 2)
        {
            int32_t nId = atoi(tv[0].c_str());
            if (nId >= 0 && nId < 5)
                m_MingGeNpc[nId] = atoi(tv[1].c_str());
        }
    }
}

void CMingGeData::PackageData(Answer::NetPacket* packet)
{
    uint32_t nCount = packet->getWOffset();
    int32_t slotCount = 0;
    packet->writeInt32(0);
    for (int32_t slot = 0; slot < 100; ++slot)
    {
        if (m_MingGeBag[slot].nId > 0)
        {
            packet->writeInt32(slot);
            packet->writeInt32(m_MingGeBag[slot].nId);
            packet->writeInt32(m_MingGeBag[slot].IsLock);
            ++slotCount;
        }
    }
    *(int32_t*)&packet->getBuffer()[nCount] = slotCount;

    nCount = packet->getWOffset();
    slotCount = 0;
    packet->writeInt32(0);
    for (int32_t slot = 0; slot < 30; ++slot)
    {
        if (m_LieMingBag[slot].nId > 0)
        {
            packet->writeInt32(slot);
            packet->writeInt32(m_LieMingBag[slot].nId);
            packet->writeInt32(m_LieMingBag[slot].IsLock);
            ++slotCount;
        }
    }
    *(int32_t*)&packet->getBuffer()[nCount] = slotCount;

    nCount = packet->getWOffset();
    slotCount = 0;
    packet->writeInt32(0);
    for (int32_t slot = 0; slot < 8; ++slot)
    {
        if (m_MingGeEquip[slot].nId > 0)
        {
            packet->writeInt32(slot);
            packet->writeInt32(m_MingGeEquip[slot].nId);
            packet->writeInt32(m_MingGeEquip[slot].IsLock);
            ++slotCount;
        }
    }
    *(int32_t*)&packet->getBuffer()[nCount] = slotCount;

    packet->writeInt32(m_MingGeExp);
    packet->writeInt32(m_MingChip);
    for (int32_t i = 0; i < 5; ++i)
        packet->writeInt32(m_MingGeNpc[i]);
}

void CMingGeData::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)
{
    int32_t slotCount = inPacket->readInt32();
    for (int32_t i = 0; i < slotCount; ++i)
    {
        int32_t slot = inPacket->readInt32();
        MingGe stu;
        stu.nId = inPacket->readInt32();
        stu.IsLock = inPacket->readInt32();
        if (!IsInvalidSlot(1, slot))
            m_MingGeBag[slot] = stu;
    }

    slotCount = inPacket->readInt32();
    for (int32_t i = 0; i < slotCount; ++i)
    {
        int32_t slot = inPacket->readInt32();
        MingGe stu;
        stu.nId = inPacket->readInt32();
        stu.IsLock = inPacket->readInt32();
        if (!IsInvalidSlot(2, slot))
            m_LieMingBag[slot] = stu;
    }

    slotCount = inPacket->readInt32();
    for (int32_t i = 0; i < slotCount; ++i)
    {
        int32_t slot = inPacket->readInt32();
        MingGe stu;
        stu.nId = inPacket->readInt32();
        stu.IsLock = inPacket->readInt32();
        if (!IsInvalidSlot(3, slot))
            m_MingGeEquip[slot] = stu;
    }

    m_MingGeExp = inPacket->readInt32();
    m_MingChip = inPacket->readInt32();
    for (int32_t i = 0; i < 5; ++i)
        m_MingGeNpc[i] = inPacket->readInt32();
}
