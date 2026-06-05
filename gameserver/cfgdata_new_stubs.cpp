// Auto-generated stub implementations for missing CfgData Init* methods
#include "stdafx.h"
#include "CfgData.h"


void CfgData::Init360RewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GameLobby.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GameLobby.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GameLobby.txt
    }
}

void CfgData::Init360RewardTypeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GameLobbyType.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GameLobbyType.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GameLobbyType.txt
    }
}

void CfgData::InitActDropTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/shoujihuodong.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/shoujihuodong.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/shoujihuodong.txt
    }
}

void CfgData::InitActiveSkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_skill_info.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/cfg_skill_info.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/cfg_skill_info.txt
    }
}

void CfgData::InitAdultGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShenFenYanZheng.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShenFenYanZheng.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShenFenYanZheng.txt
    }
}

void CfgData::InitAttrBattleTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AttrBattle.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AttrBattle.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AttrBattle.txt
    }
}

void CfgData::InitBFZLEnterCostTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BingFengZouLang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BingFengZouLang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BingFengZouLang.txt
    }
}

void CfgData::InitBaoKuFuBen()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BaoKuFuBen.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BaoKuFuBen.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BaoKuFuBen.txt
    }
}

void CfgData::InitBeastShrineEnterCostTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AnimalMapCost.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AnimalMapCost.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AnimalMapCost.txt
    }
}

void CfgData::InitBlacketMarketTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlackMarket.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlackMarket.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlackMarket.txt
    }
}

void CfgData::InitBlueDailyRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueEverydayReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlueEverydayReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlueEverydayReward.txt
    }
}

void CfgData::InitBlueLevelRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueLevelReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlueLevelReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlueLevelReward.txt
    }
}

void CfgData::InitBlueRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlueReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlueReward.txt
    }
}

void CfgData::InitBossDistribution()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MonsterRefreshInMaps.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MonsterRefreshInMaps.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MonsterRefreshInMaps.txt
    }
}

void CfgData::InitBossFirstKilledTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BossKill.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BossKill.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BossKill.txt
    }
}

void CfgData::InitBossKilledReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GoldReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GoldReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GoldReward.txt
    }
}

void CfgData::InitBuyGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TimeLimit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TimeLimit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TimeLimit.txt
    }
}

void CfgData::InitCachetCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Cachet.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Cachet.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Cachet.txt
    }
}

void CfgData::InitCampWarContKillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/CampWarContKill.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/CampWarContKill.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/CampWarContKill.txt
    }
}

void CfgData::InitCampWarRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/CampWarReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/CampWarReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/CampWarReward.txt
    }
}

void CfgData::InitCarrierAttrTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Carrier_attr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Carrier_attr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Carrier_attr.txt
    }
}

void CfgData::InitCarrierTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Carrier.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Carrier.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Carrier.txt
    }
}

void CfgData::InitChargeDungeon()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/charge_dungeon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/charge_dungeon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/charge_dungeon.txt
    }
}

void CfgData::InitChouJiangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TreasureBase.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TreasureBase.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TreasureBase.txt
    }
}

void CfgData::InitChristmasDuiHuanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Christmas.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Christmas.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Christmas.txt
    }
}

void CfgData::InitCityWarContRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GongChengZhanJiangLi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GongChengZhanJiangLi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GongChengZhanJiangLi.txt
    }
}

void CfgData::InitCrossTowerCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/KuaFuMap.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/KuaFuMap.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/KuaFuMap.txt
    }
}

void CfgData::InitCycleTowerTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LunHuiEvent.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LunHuiEvent.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LunHuiEvent.txt
    }
}

void CfgData::InitDaZheQuanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ItemDiscount.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ItemDiscount.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ItemDiscount.txt
    }
}

void CfgData::InitDamnationTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Curse.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Curse.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Curse.txt
    }
}

void CfgData::InitDiligenceCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QinFen.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QinFen.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QinFen.txt
    }
}

void CfgData::InitDrawTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Draw.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Draw.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Draw.txt
    }
}

void CfgData::InitDropRecordTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/DropRecord.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/DropRecord.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/DropRecord.txt
    }
}

void CfgData::InitDuiHuanLimitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ExchangeShengYaoBi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ExchangeShengYaoBi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ExchangeShengYaoBi.txt
    }
}

void CfgData::InitDungeonScoreTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/DungeonScore.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/DungeonScore.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/DungeonScore.txt
    }
}

void CfgData::InitDungeonSummon()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_summon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/cfg_dungeon_summon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/cfg_dungeon_summon.txt
    }
}

void CfgData::InitEquipBackTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipRecovery.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipRecovery.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipRecovery.txt
    }
}

void CfgData::InitEquipBackTask()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TaskRecovery.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TaskRecovery.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TaskRecovery.txt
    }
}

void CfgData::InitEquipBlessTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LuckyValue.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LuckyValue.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LuckyValue.txt
    }
}

void CfgData::InitEquipBoxTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_item_gift_equip.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/cfg_item_gift_equip.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/cfg_item_gift_equip.txt
    }
}

void CfgData::InitEquipDecomposeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipDecompose.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipDecompose.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipDecompose.txt
    }
}

void CfgData::InitEquipPosSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipPosSuit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipPosSuit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipPosSuit.txt
    }
}

void CfgData::InitEquipUpPhase()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipUpPhase.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipUpPhase.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipUpPhase.txt
    }
}

void CfgData::InitExchangeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/JiZiDuiJiang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/JiZiDuiJiang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/JiZiDuiJiang.txt
    }
}

void CfgData::InitFamilyDonateTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilyDonate.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilyDonate.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilyDonate.txt
    }
}

void CfgData::InitFamilyDungeonTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilyDungeon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilyDungeon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilyDungeon.txt
    }
}

void CfgData::InitFamilyMedalTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilyBadge.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilyBadge.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilyBadge.txt
    }
}

void CfgData::InitFamilySkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilySkill.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilySkill.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilySkill.txt
    }
}

void CfgData::InitFlopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FlopActivity.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FlopActivity.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FlopActivity.txt
    }
}

void CfgData::InitFunctionOpenMailMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MailGuide.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MailGuide.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MailGuide.txt
    }
}

void CfgData::InitGemOpenHoleTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GemOpenHole.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GemOpenHole.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GemOpenHole.txt
    }
}

void CfgData::InitGemSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GemSuit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GemSuit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GemSuit.txt
    }
}

void CfgData::InitGoblinData()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Goblin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Goblin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Goblin.txt
    }
}

void CfgData::InitGoblinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GoblinUp.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GoblinUp.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GoblinUp.txt
    }
}

void CfgData::InitGoldEggTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ItemGoldEggOpen.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ItemGoldEggOpen.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ItemGoldEggOpen.txt
    }
}

void CfgData::InitGongMinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GongMing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GongMing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GongMing.txt
    }
}

void CfgData::InitGroupIconTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GroupIcon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GroupIcon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GroupIcon.txt
    }
}

void CfgData::InitGroupMonster()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/RegionRefresh.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/RegionRefresh.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/RegionRefresh.txt
    }
}

void CfgData::InitGuWuCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GuWu.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GuWu.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GuWu.txt
    }
}

void CfgData::InitGuardPrivilegeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GuardPrivilegeReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GuardPrivilegeReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GuardPrivilegeReward.txt
    }
}

void CfgData::InitGuiGuDaoRenTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TaoistTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TaoistTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TaoistTask.txt
    }
}

void CfgData::InitHoeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Hoe.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Hoe.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Hoe.txt
    }
}

void CfgData::InitJewelPavilionTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TreasureShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TreasureShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TreasureShop.txt
    }
}

void CfgData::InitJueWeiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/JueWei.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/JueWei.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/JueWei.txt
    }
}

void CfgData::InitLaDaShiHuiYuan()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LuDaShiHuiYuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LuDaShiHuiYuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LuDaShiHuiYuan.txt
    }
}

void CfgData::InitLevelChatTimesTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PublicChatTimes.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PublicChatTimes.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PublicChatTimes.txt
    }
}

void CfgData::InitLevelRefiningTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LvRefining.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LvRefining.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LvRefining.txt
    }
}

void CfgData::InitLibraryTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ChestItemRandom.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ChestItemRandom.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ChestItemRandom.txt
    }
}

void CfgData::InitLimitTimeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LimitTime.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LimitTime.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LimitTime.txt
    }
}

void CfgData::InitLittleHelperCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LittleHelper.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LittleHelper.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LittleHelper.txt
    }
}

void CfgData::InitLuckDropTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LuckyRate.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LuckyRate.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LuckyRate.txt
    }
}

void CfgData::InitMYSJRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MoYuShiJieReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MoYuShiJieReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MoYuShiJieReward.txt
    }
}

void CfgData::InitMaintainCompensateTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MaintainCompensate.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MaintainCompensate.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MaintainCompensate.txt
    }
}

void CfgData::InitMapRoadTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MapRoad.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MapRoad.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MapRoad.txt
    }
}

void CfgData::InitMingGeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MingGe.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MingGe.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MingGe.txt
    }
}

void CfgData::InitMiniClientMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WeiDuanDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WeiDuanDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WeiDuanDaTing.txt
    }
}

void CfgData::InitMiniClientTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WeiDuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WeiDuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WeiDuan.txt
    }
}

void CfgData::InitMobilePhoneGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShouJi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShouJi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShouJi.txt
    }
}

void CfgData::InitMonsterAddAttrTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MonstAddAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MonstAddAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MonstAddAttr.txt
    }
}

void CfgData::InitMonsterRandTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MonsterRand.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MonsterRand.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MonsterRand.txt
    }
}

void CfgData::InitMonthlyChouJiangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TurntableReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TurntableReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TurntableReward.txt
    }
}

void CfgData::InitMysteryGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MysteriousGift.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MysteriousGift.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MysteriousGift.txt
    }
}

void CfgData::InitMysteryShopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MysteriousShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MysteriousShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MysteriousShop.txt
    }
}

void CfgData::InitNationalDayTask()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PassportTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PassportTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PassportTask.txt
    }
}

void CfgData::InitOutLinkFestivalTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/OutLinkFestival.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/OutLinkFestival.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/OutLinkFestival.txt
    }
}

void CfgData::InitPassiveSkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillPassiveAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillPassiveAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillPassiveAttr.txt
    }
}

void CfgData::InitPetAttrTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PetAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PetAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PetAttr.txt
    }
}

void CfgData::InitPetUpStarTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PetUpStar.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PetUpStar.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PetUpStar.txt
    }
}

void CfgData::InitPlatformDaTingMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/DaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/DaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/DaTing.txt
    }
}

void CfgData::InitPlatformReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Reward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Reward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Reward.txt
    }
}

void CfgData::InitPlatformVipMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/OutLinkVip.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/OutLinkVip.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/OutLinkVip.txt
    }
}

void CfgData::InitQQGameRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QQGameDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QQGameDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QQGameDaTing.txt
    }
}

void CfgData::InitQQZoneRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QQZone.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QQZone.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QQZone.txt
    }
}

void CfgData::InitRefreshMonsterCfgListMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ActivityServer.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ActivityServer.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ActivityServer.txt
    }
}

void CfgData::InitRongHeCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ItemMix.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ItemMix.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ItemMix.txt
    }
}

void CfgData::InitScoreShopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ScoreShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ScoreShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ScoreShop.txt
    }
}

void CfgData::InitSelectItemCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GiftChoose.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GiftChoose.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GiftChoose.txt
    }
}

void CfgData::InitShangRenCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MagicBusiness.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MagicBusiness.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MagicBusiness.txt
    }
}

void CfgData::InitShenWeiTaskTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShenWeiTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShenWeiTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShenWeiTask.txt
    }
}

void CfgData::InitShenYaoPosSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShengZhuangSuit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShengZhuangSuit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShengZhuangSuit.txt
    }
}

void CfgData::InitShenYaoPosTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShengZhuangAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShengZhuangAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShengZhuangAttr.txt
    }
}

void CfgData::InitShiZhuLevelUp()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuangUpGrade.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShiZhuangUpGrade.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShiZhuangUpGrade.txt
    }
}

void CfgData::InitShiZhuangLevelTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuangLevel.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShiZhuangLevel.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShiZhuangLevel.txt
    }
}

void CfgData::InitShiZhuangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShiZhuang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShiZhuang.txt
    }
}

void CfgData::InitShouHuRefining()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/StarSpaceLevel.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/StarSpaceLevel.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/StarSpaceLevel.txt
    }
}

void CfgData::InitShunWangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShunWangHuiYuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShunWangHuiYuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShunWangHuiYuan.txt
    }
}

void CfgData::InitSouGouDaTing()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SouGouDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SouGouDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SouGouDaTing.txt
    }
}

void CfgData::InitSouGouSkinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SogouSkin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SogouSkin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SogouSkin.txt
    }
}

void CfgData::InitSpeciaEquipCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialEquip.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialEquip.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialEquip.txt
    }
}

void CfgData::InitSpeciaSkillDistanceTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillSpecialDamage.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillSpecialDamage.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillSpecialDamage.txt
    }
}

void CfgData::InitSpecialBossMapCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MapConsume.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MapConsume.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MapConsume.txt
    }
}

void CfgData::InitSpecialMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialMap.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialMap.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialMap.txt
    }
}

void CfgData::InitSpecialMonster()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialMonster.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialMonster.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialMonster.txt
    }
}

void CfgData::InitSpecialTreasureMapRandTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialTreasureMap.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialTreasureMap.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialTreasureMap.txt
    }
}

void CfgData::InitSpeed360Reward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Speed360Reward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Speed360Reward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Speed360Reward.txt
    }
}

void CfgData::InitStrengthenTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MieShenRongLian.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MieShenRongLian.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MieShenRongLian.txt
    }
}

void CfgData::InitSuperMemberTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SuperMember.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SuperMember.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SuperMember.txt
    }
}

void CfgData::InitSuperTeHuiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SuperDiscount.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SuperDiscount.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SuperDiscount.txt
    }
}

void CfgData::InitSystemOpenReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/System.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/System.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/System.txt
    }
}

void CfgData::InitTGPDailyRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPEverydayReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TGPEverydayReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TGPEverydayReward.txt
    }
}

void CfgData::InitTGPLevelRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPLevelReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TGPLevelReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TGPLevelReward.txt
    }
}

void CfgData::InitTGPRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TGPReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TGPReward.txt
    }
}

void CfgData::InitTalentActiveTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillActive.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillActive.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillActive.txt
    }
}

void CfgData::InitTalentPageTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillTree.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillTree.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillTree.txt
    }
}

void CfgData::InitTalentTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillTalent.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillTalent.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillTalent.txt
    }
}

void CfgData::InitTaskCycleRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TaskCycleReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TaskCycleReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TaskCycleReward.txt
    }
}

void CfgData::InitTencentSevenDayLoginTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TencentSevenDayLogin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TencentSevenDayLogin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TencentSevenDayLogin.txt
    }
}

void CfgData::InitTestServerReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TestActivity.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TestActivity.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TestActivity.txt
    }
}

void CfgData::InitTianLingTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TianLing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TianLing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TianLing.txt
    }
}

void CfgData::InitTitleTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Title.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Title.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Title.txt
    }
}

void CfgData::InitTongTianChiRanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/tongtianpaihang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/tongtianpaihang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/tongtianpaihang.txt
    }
}

void CfgData::InitTouZiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QiRiTouZi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QiRiTouZi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QiRiTouZi.txt
    }
}

void CfgData::InitTreasureMapTabale()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TreasureMapBase.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TreasureMapBase.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TreasureMapBase.txt
    }
}

void CfgData::InitTrigSkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillTrig.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillTrig.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillTrig.txt
    }
}

void CfgData::InitUltimateChallengeCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/limitChallenge.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/limitChallenge.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/limitChallenge.txt
    }
}

void CfgData::InitVplanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/VplanReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/VplanReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/VplanReward.txt
    }
}

void CfgData::InitWeiXinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WeiXin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WeiXin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WeiXin.txt
    }
}

void CfgData::InitWingCfgTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AttributeWing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AttributeWing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AttributeWing.txt
    }
}

void CfgData::InitWingEquipPolish()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WingEquipPolish.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WingEquipPolish.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WingEquipPolish.txt
    }
}

void CfgData::InitWishRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WishReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WishReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WishReward.txt
    }
}

void CfgData::InitWuHunCreateTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WuHunMake.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WuHunMake.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WuHunMake.txt
    }
}

void CfgData::InitWuHunItemTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WuHun.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WuHun.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WuHun.txt
    }
}

void CfgData::InitWuHunShopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MysterShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MysterShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MysterShop.txt
    }
}

void CfgData::InitXianYaoTaskTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XiangYaoTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XiangYaoTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XiangYaoTask.txt
    }
}

void CfgData::InitXinMoTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XinMoLevel.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XinMoLevel.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XinMoLevel.txt
    }
}

void CfgData::InitXinMoTask(int32_t Level, int32_t Times)
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_INITXINMOTASK);
    if (ret == false)
    {
        LOG_ERROR("open FILE_INITXINMOTASK failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // no file
    }
}

void CfgData::InitXingMaiSlotTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XingMaiSlot.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XingMaiSlot.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XingMaiSlot.txt
    }
}

void CfgData::InitXingMaiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AttributeXingMai.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AttributeXingMai.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AttributeXingMai.txt
    }
}

void CfgData::InitXuWuTask(int32_t Level, int32_t Times)
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_INITXUWUTASK);
    if (ret == false)
    {
        LOG_ERROR("open FILE_INITXUWUTASK failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // no file
    }
}

void CfgData::InitXunLeiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XunLeiBox.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XunLeiBox.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XunLeiBox.txt
    }
}

void CfgData::InitYYDaTing()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YYDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YYDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YYDaTing.txt
    }
}

void CfgData::InitYYVip()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YYHuiYuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YYHuiYuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YYHuiYuan.txt
    }
}

void CfgData::InitYellowDailyRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowEverydayReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YellowEverydayReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YellowEverydayReward.txt
    }
}

void CfgData::InitYellowLevelRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowLevelReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YellowLevelReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YellowLevelReward.txt
    }
}

void CfgData::InitYellowRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YellowReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YellowReward.txt
    }
}
