#ifndef __TPOC_CMING_GE_DATA_H__
#define __TPOC_CMING_GE_DATA_H__

#include "DataStructs.h"
#include "../share/DataStruct.h"
#include <string>
#include <vector>
#include <list>

struct MingGe
{
    MingGe() : nId(0), IsLock(0) {}
    int32_t nId;
    int32_t IsLock;

    static bool IsEmpty(const MingGe* pMG) { return pMG == NULL || pMG->nId == 0; }
};

struct MGLog
{
    MGLog() : Cid(0), Time(0), Reason(ITEM_CHANGE_REASON(0)), BagType(0), MingGeId(0), Flag(0) {}
    CharId_t Cid;
    int32_t Time;
    ITEM_CHANGE_REASON Reason;
    int32_t BagType;
    int32_t MingGeId;
    int32_t Flag;
};

class CMingGeData
{
public:
    CMingGeData();
    ~CMingGeData();

    void CleanUp();
    void SaveToSqlString(SqlStringList& sqls, char (&szSQL)[4096], CharId_t nCid);
    bool LoadFromDB(Answer::MySqlDBGuard& db, char (&szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);
    void PackageData(Answer::NetPacket* packet);
    void UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);

    std::string GetNpcString();
    void parseMingGeNpc(std::string* pStr);

    // Data members
    MingGe m_MingGeBag[100];
    MingGe m_LieMingBag[30];
    MingGe m_MingGeEquip[8];
    int32_t m_MingGeNpc[5];
    int32_t m_MingGeExp;
    int32_t m_MingChip;
};

bool IsInvalidSlot(int32_t nBagType, int32_t nSlot);

#endif
