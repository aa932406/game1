#ifndef __TPOC_CLITTLE_HELPER_DATA_H__
#define __TPOC_CLITTLE_HELPER_DATA_H__

#include "DataStructs.h"
#include "../share/DataStruct.h"
#include <map>
#include <string>

class CLittleHelperData
{
public:
    CLittleHelperData();
    ~CLittleHelperData();

    void CleanUp();
    void SaveToSqlString( SqlStringList *sqls, char (*szSQL)[4096], CharId_t nCid );
    bool LoadFromDB( Answer::MySqlDBGuard *db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid );
    void PackageData( Answer::NetPacket *packet );
    void UnPackageData( Answer::NetPacket *inPacket, CharId_t nCid );

    std::string getRewardState();
    void SaveRewardState( std::string *pStr );

    int32_t m_LittleHelperId;
    std::map<int32_t, ActLittleHelperInfo> m_ActLittleHelperInfoMap;
};

#endif
