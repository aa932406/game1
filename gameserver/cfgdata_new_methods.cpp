// Auto-extracted from decompiled CfgData.cpp
// These are approximating the original source code.
// Compile errors expected - fix each method as needed.

#include "stdafx.h"
#include "CfgData.h"


void CfgData::Init360RewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/GameLobby.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_360_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::Init360RewardTypeTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string platform; // [rsp+A0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/GameLobbyType.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_360_REWARD_TYPE_TABLE failed,please check!!!\n");
  }

void CfgData::InitActDropTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ActDropItem> *v3; // rax
  std::string p_StringTime; // [rsp+D0h] [rbp-40h] BYREF
  std::string v9; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/shoujihuodong.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ACTDROP_TABLE failed, please check!!!\n");
  }

void CfgData::InitActiveSkillTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+170h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+180h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/cfg_skill_info.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_ACTIVE_SKILL_TABLE fail, please check!!!\n");
  }

void CfgData::InitAdultGiftTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ShenFenYanZheng.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ADULT_GIFT_TABLE failed,please check!!!\n");
  }

void CfgData::InitAttrBattleTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/AttrBattle.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ATTR_BATTLE_TABLE failed,please check!!!\n");
  }

void CfgData::InitBFZLEnterCostTable()
{
  const CDBCFile::FIELD *v1; // rax
  bool bCombi[10]; // [rsp+B0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/BingFengZouLang.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_BFZL_ENTER_COST_TABLE failed,please check!!!\n");
  }

void CfgData::InitBaoKuFuBen()
{
  unsigned int v11; // r8d

  CDBCFile::CDBCFile((CDBCFile *const)&stu_0, 0);
  if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_0, "./ServerConfig/Tables/BaoKuFuBen.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileBaoKuF);
    v1 = 0;
  }

void CfgData::InitBeastShrineEnterCostTable()
{
  const CDBCFile::FIELD *v1; // rax
  bool bCombi[10]; // [rsp+B0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/AnimalMapCost.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileBfzlEn_0);
  }

void CfgData::InitBlacketMarketTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string strItem; // [rsp+110h] [rbp-60h] BYREF
  std::string v10; // [rsp+120h] [rbp-50h] BYREF
  std::string v12; // [rsp+130h] [rbp-40h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/BlackMarket.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_BLACK_MARKET_TABLE failed,please check!!!\n");
  }

void CfgData::InitBlueDailyRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string strItems; // [rsp+180h] [rbp-A0h] BYREF
  std::string v12; // [rsp+1B0h] [rbp-70h] BYREF
  std::string v15; // [rsp+1E0h] [rbp-40h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/BlueEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BLUE_DAILY_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitBlueLevelRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/BlueLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BLUE_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitBlueRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+C0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/BlueReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_BLUE_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitBossDistribution()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string BossMapListString_0; // [rsp+A0h] [rbp-F0h] BYREF
  std::string BossMapListString; // [rsp+D0h] [rbp-C0h] BYREF
  std::list<int> __x; // [rsp+100h] [rbp-90h] BYREF
  std::list<int> v13; // [rsp+130h] [rbp-60h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/MonsterRefreshInMaps.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_LEVEL_IFNO_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitBossFirstKilledTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/BossKill.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BOSS_FIRST_KILLED_TABLE.txt failed,please check!!");
  }

void CfgData::InitBossKilledReward()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GoldReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BOSS_KILLED_REWARD_TABLE.txt failed,please check!!");
  }

void CfgData::InitBuyGiftTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string items; // [rsp+D0h] [rbp-50h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TimeLimit.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_BUY_GIFT_TABLE failed,please check!!!\n");
  }

void CfgData::InitCachetCfg()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+E0h] [rbp-40h] BYREF
  int32_t v8[3]; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Cachet.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CACHET_CFG_TABLE.txt failed,please check!!");
  }

void CfgData::InitCampWarContKillTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/CampWarContKill.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CAMP_WAR_CONT_KILL_TABLE failed,please check!!");
  }

void CfgData::InitCampWarRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string failItem; // [rsp+E0h] [rbp-80h] BYREF
  std::string winItem; // [rsp+F0h] [rbp-70h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/CampWarReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CAMP_WAR_REWARD_TABLE failed,please check!!");
  }

void CfgData::InitCarrierAttrTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Carrier_attr.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_ATTR_TABLE failed,please check!!!\n");
  }

void CfgData::InitCarrierTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Carrier.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_TABLE failed,please check!!!\n");
  }

void CfgData::InitChargeDungeon()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/charge_dungeon.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileCharge);
  }

void CfgData::InitChouJiangTable()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  std::string strItem; // [rsp+170h] [rbp-E0h] BYREF
  std::string strItems; // [rsp+1A0h] [rbp-B0h] BYREF
  std::string v20; // [rsp+1D0h] [rbp-80h] BYREF
  std::string v22; // [rsp+1E0h] [rbp-70h] BYREF

  thisa = this;
  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TreasureBase.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CHOU_JIANG_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitChristmasDuiHuanTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string strItems; // [rsp+100h] [rbp-70h] BYREF
  std::list<ItemData> v11; // [rsp+110h] [rbp-60h] BYREF
  bool bCombi[15]; // [rsp+120h] [rbp-50h] BYREF
  std::string p_StringTime; // [rsp+130h] [rbp-40h] BYREF
  std::string v16; // [rsp+140h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Christmas.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileLingZh_2);
  }

void CfgData::InitCityWarContRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GongChengZhanJiangLi.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_CITY_WAR_CONT_REWARD_TABLE failed,please check!!");
  }

void CfgData::InitCrossTowerCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+120h] [rbp-60h] BYREF
  std::string v10; // [rsp+150h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/KuaFuMap.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }

void CfgData::InitCycleTowerTable()
{
  const CDBCFile::FIELD *v2; // rax
  std::string strItem; // [rsp+C0h] [rbp-50h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/LunHuiEvent.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C95A0);
    v1 = 0;
  }

void CfgData::InitDaZheQuanTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/ItemDiscount.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_DA_ZHE_QUAN_TABLE failed,please check!!!\n");
  }

void CfgData::InitDamnationTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ItemData> strItems; // [rsp+E0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+F0h] [rbp-60h] BYREF
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+110h] [rbp-40h] BYREF
  int32_t v12[3]; // [rsp+120h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Curse.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileDamnat);
  }

void CfgData::InitDiligenceCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<RateItem> strItems; // [rsp+C0h] [rbp-40h] BYREF
  _BYTE v6[14]; // [rsp+D0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/QinFen.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C9450);
  }

void CfgData::InitDrawTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Draw.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_DRAW_TABLE failed,please check!!!\n");
  }

void CfgData::InitDropRecordTable()
{

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/DropRecord.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_DROP_RECORD_TABLE failed,please check!!!\n");
  }

void CfgData::InitDuiHuanLimitTable()
{

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/ExchangeShengYaoBi.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
  }

void CfgData::InitDungeonScoreTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItem; // [rsp+F0h] [rbp-30h] BYREF

  thisa = this;
  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/DungeonScore.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_DUNGEON_SCORE_TABLE failed,please check!!!\n");
  }

void CfgData::InitDungeonSummon()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<int> __x; // [rsp+D0h] [rbp-70h] BYREF
  int32_t size[3]; // [rsp+E0h] [rbp-60h] BYREF
  std::string path; // [rsp+F0h] [rbp-50h] BYREF
  std::string strItem; // [rsp+100h] [rbp-40h] BYREF
  std::pair<int,int> __k; // [rsp+110h] [rbp-30h] BYREF

  CDBCFile &DungeonTrapFile(0);
  if ( !DungeonTrapFile.OpenFromTXT(, "./ServerConfig/Tables/cfg_dungeon_summon.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_DUNGEON_SUMMON_TABLE.txt failed,please check!!");
  }

void CfgData::InitEquipBackTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  const char *v3; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-C0h] BYREF
  std::string EquipList; // [rsp+110h] [rbp-90h] BYREF
  std::string delims; // [rsp+120h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+130h] [rbp-70h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/EquipRecovery.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BACK failed,please check!!!\n");
  }

void CfgData::InitEquipBackTask()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  const CDBCFile::FIELD *v7; // rax
  std::string *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  std::map<int,std::list<Param2>> *v13; // rax
  std::list<Param2> *v14; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+120h] [rbp-140h] BYREF
  std::string TaskRate; // [rsp+160h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+170h] [rbp-F0h] BYREF
  std::string NeedEquipString; // [rsp+1A0h] [rbp-C0h] BYREF
  std::string strItems; // [rsp+1D0h] [rbp-90h] BYREF
  std::string delims; // [rsp+1E0h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1F0h] [rbp-70h] BYREF
  std::string v37; // [rsp+200h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v39; // [rsp+210h] [rbp-50h] BYREF
  std::string v40; // [rsp+220h] [rbp-40h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TaskRecovery.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_EQUIP_BACK_TASK failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitEquipBlessTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/LuckyValue.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }

void CfgData::InitEquipBoxTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<Param2> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v5[15]; // [rsp+F0h] [rbp-40h] BYREF
  int32_t v7[3]; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/cfg_item_gift_equip.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BOX_TABLE failed,please check!!!\n");
  }

void CfgData::InitEquipDecomposeTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/EquipDecompose.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_DECOMPOSE_TABLE failed,please check!!!\n");
  }

void CfgData::InitEquipPosSuitTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/EquipPosSuit.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_POS_SUIT_TABLE failed,please check!!!\n");
  }

void CfgData::InitEquipUpPhase()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-40h] BYREF
  bool bCombi[18]; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/EquipUpPhase.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C7918);
  }

void CfgData::InitExchangeTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string rewards; // [rsp+D0h] [rbp-70h] BYREF
  std::string items; // [rsp+E0h] [rbp-60h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-50h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/JiZiDuiJiang.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_EXCHANGE_TABLE failed,please check!!!\n");
  }

void CfgData::InitFamilyDonateTable()
{

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/FamilyDonate.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C94A0);
  }

void CfgData::InitFamilyDungeonTable()
{

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/FamilyDungeon.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_DUNGEON_TABLE failed,please check!!!\n");
  }

void CfgData::InitFamilyMedalTable()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-90h] BYREF
  _BYTE v7[15]; // [rsp+E0h] [rbp-80h] BYREF
  int32_t v9[3]; // [rsp+F0h] [rbp-70h] BYREF
  std::list<AddAttribute> v11; // [rsp+100h] [rbp-60h] BYREF
  _BYTE v12[15]; // [rsp+110h] [rbp-50h] BYREF
  int32_t v14[2]; // [rsp+120h] [rbp-40h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/FamilyBadge.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_MEDAL_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitFamilySkillTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/FamilySkill.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_FAMILY_SKILL_TABLE fail, please check!!!\n");
  }

void CfgData::InitFlopTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItem; // [rsp+F0h] [rbp-30h] BYREF

  thisa = this;
  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/FlopActivity.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_FLOP_TABLE failed,please check!!!\n");
  }

void CfgData::InitFunctionOpenMailMap()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MailGuide.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }

void CfgData::InitGemOpenHoleTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<ItemData> strItems; // [rsp+C0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+D0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GemOpenHole.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GEM_OPEN_HOLE_TABLE failed,please check!!!\n");
  }

void CfgData::InitGemSuitTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GemSuit.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GEM_SUIT_TABLE failed,please check!!!\n");
  }

void CfgData::InitGoblinData()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string path; // [rsp+E0h] [rbp-70h] BYREF
  std::string str; // [rsp+F0h] [rbp-60h] BYREF
  std::vector<Position> __x; // [rsp+100h] [rbp-50h] BYREF
  std::string strPos; // [rsp+120h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/Goblin.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C7820);
  }

void CfgData::InitGoblinTable()
{
  const CDBCFile::FIELD *v2; // rax
  std::list<AddAttribute> *v3; // rax
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,GoblinCfg> >,bool> v8; // [rsp+E0h] [rbp-A0h]
  _BYTE v9[32]; // [rsp+F0h] [rbp-90h] BYREF
  std::pair<int,int> __a; // [rsp+110h] [rbp-70h] BYREF
  _BYTE v11[15]; // [rsp+120h] [rbp-60h] BYREF
  int32_t v13[4]; // [rsp+130h] [rbp-50h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/GoblinUp.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitGoldEggTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ItemGoldEggOpen.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOLD_EGG_OPEN_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitGongMinTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+E0h] [rbp-40h] BYREF
  int32_t v8[3]; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GongMing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileGongMi);
  }

void CfgData::InitGroupIconTable()
{
  const CDBCFile::FIELD *v1; // rax

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GroupIcon.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_GROUP_ICON_TABLE fail, please check!!!\n");
  }

void CfgData::InitGroupMonster()
{
  const CDBCFile::FIELD *v1; // rax
  std::vector<GroupMonster> *v2; // rax
  std::vector<Position> __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &InitBossFile(0);
  if ( !InitBossFile.OpenFromTXT(, "./ServerConfig/Tables/RegionRefresh.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_INFO_TABLE failed,please check!!");
  }

void CfgData::InitGuWuCfgMap()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GuWu.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }

void CfgData::InitGuardPrivilegeTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string strItems; // [rsp+E0h] [rbp-60h] BYREF
  std::string p_StringTime; // [rsp+F0h] [rbp-50h] BYREF
  std::string v11; // [rsp+100h] [rbp-40h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/GuardPrivilegeReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileGuardP);
  }

void CfgData::InitGuiGuDaoRenTable()
{
  const CDBCFile::FIELD *v1; // rax
  const std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  const CDBCFile::FIELD *v11; // rax
  const CDBCFile::FIELD *v12; // rax
  const CDBCFile::FIELD *v13; // rax
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+140h] [rbp-130h] BYREF
  std::string RefreshMonsterString; // [rsp+170h] [rbp-100h] BYREF
  std::string delims; // [rsp+180h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+190h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1A0h] [rbp-D0h] BYREF
  std::string v28; // [rsp+1B0h] [rbp-C0h] BYREF
  std::string strItem; // [rsp+1D0h] [rbp-A0h] BYREF
  std::string v34; // [rsp+200h] [rbp-70h] BYREF
  std::string path; // [rsp+230h] [rbp-40h] BYREF
  std::string str; // [rsp+240h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TaoistTask.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GUI_GU_DAO_REN_TABLE failed,please check!!!\n");
  }

void CfgData::InitHoeTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Hoe.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_HOE_TABLE failed,please check!!!\n");
  }

void CfgData::InitJewelPavilionTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,JewelPavilionCfg> >,bool> v2; // rax
  std::string strItem; // [rsp+F0h] [rbp-90h] BYREF
  std::_Rb_tree_node_base::_Base_ptr M_node; // [rsp+100h] [rbp-80h]
  _BYTE v11[64]; // [rsp+110h] [rbp-70h] BYREF
  std::pair<int,int> __a; // [rsp+150h] [rbp-30h] BYREF

  thisa = this;
  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TreasureShop.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_TREASURE_SHOP_TABLE failed,please check!!!\n");
  }

void CfgData::InitJueWeiTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/JueWei.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_TABLE failed,please check!!!\n");
  }

void CfgData::InitLaDaShiHuiYuan()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/LuDaShiHuiYuan.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C9220);
  }

void CfgData::InitLevelChatTimesTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/PublicChatTimes.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_LEVEL_CHAT_TIMES_TABLE failed,please check!!!\n");
  }

void CfgData::InitLevelRefiningTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string sLevelUp; // [rsp+120h] [rbp-70h] BYREF
  std::string vNeedGoldString; // [rsp+130h] [rbp-60h] BYREF
  std::string delims; // [rsp+140h] [rbp-50h] BYREF
  std::string v21; // [rsp+150h] [rbp-40h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/LvRefining.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_LEVEL_REFIN_TABLE.txt failed,please check!!");
  }

void CfgData::InitLibraryTable()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string strItem; // [rsp+150h] [rbp-70h] BYREF
  std::string v14; // [rsp+160h] [rbp-60h] BYREF

  thisa = this;
  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ChestItemRandom.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_LIBRARY_ITEM_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitLimitTimeTable()
{
  const CDBCFile::FIELD *v1; // rax
  const char *v2; // rax
  std::string strTime; // [rsp+A0h] [rbp-50h] BYREF
  std::string p_StringTime; // [rsp+C0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/LimitTime.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_LIMIT_TIME_TABLE failed,please check!!!\n");
  }

void CfgData::InitLittleHelperCfg()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v6; // rax
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-B0h] BYREF
  _BYTE v11[15]; // [rsp+100h] [rbp-A0h] BYREF
  int32_t v13[3]; // [rsp+110h] [rbp-90h] BYREF
  std::string strItems; // [rsp+140h] [rbp-60h] BYREF

  CDBCFile &FileTable(0);
  if ( !FileTable.OpenFromTXT(, "./ServerConfig/Tables/LittleHelper.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_LITTLE_HELPER_CFG_TABLE.txt failed,please check!!");
    v1 = 0;
  }

void CfgData::InitLuckDropTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+110h] [rbp-C0h] BYREF
  std::string ItemString; // [rsp+140h] [rbp-90h] BYREF
  std::string delims; // [rsp+150h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+160h] [rbp-70h] BYREF
  std::string v24; // [rsp+170h] [rbp-60h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/LuckyRate.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_LUCK_DROP_TABLE.txt failed,please check!!");
  }

void CfgData::InitMYSJRewardTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MoYuShiJieReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSJ_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitMaintainCompensateTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string p_StringTime; // [rsp+C0h] [rbp-60h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MaintainCompensate.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MAINTAIN_COMPENSATE_TABLE failed,please check!!!\n");
  }

void CfgData::InitMapRoadTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-B0h] BYREF
  std::string strRoad; // [rsp+110h] [rbp-80h] BYREF
  std::string delims; // [rsp+120h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+130h] [rbp-60h] BYREF
  std::string v17; // [rsp+140h] [rbp-50h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MapRoad.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_ROAD_TABLE failed,please check!!!\n");
  }

void CfgData::InitMingGeTable()
{
  const CDBCFile::FIELD *v2; // rax
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-C0h] BYREF
  _BYTE v9[15]; // [rsp+110h] [rbp-B0h] BYREF
  int32_t v11[3]; // [rsp+120h] [rbp-A0h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MingGe.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe);
    v1 = 0;
  }

void CfgData::InitMiniClientMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/WeiDuanDaTing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C9320);
  }

void CfgData::InitMiniClientTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/WeiDuan.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MINI_CLIENT_TABLE failed,please check!!!\n");
  }

void CfgData::InitMobilePhoneGiftTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/ShouJi.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MOBILE_PHONE_GIFT_TABLE failed,please check!!!\n");
  }

void CfgData::InitMonsterAddAttrTable()
{
  std::list<CfgMonsterAddAttr> *v1; // rax

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/MonstAddAttr.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_ADD_ATTR failed,please check!!!\n");
  }

void CfgData::InitMonsterRandTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string path; // [rsp+100h] [rbp-80h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-70h] BYREF
  std::string v11; // [rsp+140h] [rbp-40h] BYREF
  std::string v13; // [rsp+150h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MonsterRand.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_RAND_TABLE failed,please check!!!\n");
  }

void CfgData::InitMonthlyChouJiangTable()
{
  const CDBCFile::FIELD *v2; // rax
  std::string strItem; // [rsp+F0h] [rbp-50h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TurntableReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TURNTABLE_REWARD_TABLE failed, please check!!!\n");
    v1 = 0;
  }

void CfgData::InitMysteryGiftTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MysteriousGift.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSTERY_GIFT_TABLE failed,please check!!!\n");
  }

void CfgData::InitMysteryShopTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItem; // [rsp+110h] [rbp-40h] BYREF
  std::string v10; // [rsp+120h] [rbp-30h] BYREF

  thisa = this;
  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MysteriousShop.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSTERY_SHOP_TABLE failed,please check!!!\n");
  }

void CfgData::InitNationalDayTask()
{
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,NationalDayTaskCfg> >,bool> v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::_Rb_tree_node_base::_Base_ptr M_node; // [rsp+20h] [rbp-210h]
  std::_Rb_tree_node_base::_Base_ptr v13; // [rsp+180h] [rbp-B0h]
  _BYTE v15[32]; // [rsp+190h] [rbp-A0h] BYREF
  std::pair<int,int> __a; // [rsp+1B0h] [rbp-80h] BYREF
  std::string strItems; // [rsp+1E0h] [rbp-50h] BYREF
  std::string strItem; // [rsp+1F0h] [rbp-40h] BYREF

  thisa = this;
  CDBCFile::CDBCFile((CDBCFile *const)&stu_0, 0);
  if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_0, "./ServerConfig/Tables/PassportTask.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MO_SHEN_JIANG_LING_TABLE.txt failed,please check!!");
    v1 = 0;
  }

void CfgData::InitOutLinkFestivalTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string p_StringTime; // [rsp+C0h] [rbp-40h] BYREF
  std::string v8; // [rsp+D0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/OutLinkFestival.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_OUT_LINK_FESTIVAL_TABLE failed, please check!!!\n");
  }

void CfgData::InitPassiveSkillTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string path; // [rsp+100h] [rbp-70h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-60h] BYREF
  std::list<TalentAddon> v10; // [rsp+120h] [rbp-50h] BYREF
  _BYTE v11[15]; // [rsp+130h] [rbp-40h] BYREF
  int32_t v13[3]; // [rsp+140h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SkillPassiveAttr.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_PASSIVE_SKILL_TABLE fail, please check!!!\n");
  }

void CfgData::InitPetAttrTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+130h] [rbp-40h] BYREF
  std::string addonAttr; // [rsp+140h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/PetAttr.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_PET_ATTR_TABLE failed,please check!!!\n");
  }

void CfgData::InitPetUpStarTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::list<ItemData> strItems; // [rsp+110h] [rbp-100h] BYREF
  bool bCombi[15]; // [rsp+120h] [rbp-F0h] BYREF
  std::string path; // [rsp+150h] [rbp-C0h] BYREF
  std::string addonAttr; // [rsp+160h] [rbp-B0h] BYREF
  std::string v16; // [rsp+190h] [rbp-80h] BYREF
  std::string v18; // [rsp+1A0h] [rbp-70h] BYREF
  std::string v21; // [rsp+1D0h] [rbp-40h] BYREF
  std::string str; // [rsp+1E0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/PetUpStar.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_PET_UP_STAR_TABLE failed,please check!!!\n");
  }

void CfgData::InitPlatformDaTingMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/DaTing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C9320);
  }

void CfgData::InitPlatformReward()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformRewardCfg> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/Reward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C93F8);
  }

void CfgData::InitPlatformVipMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+100h] [rbp-A0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformVip> >,bool> v8; // [rsp+110h] [rbp-90h]
  _BYTE v9[64]; // [rsp+120h] [rbp-80h] BYREF
  std::pair<std::string,int> p___x; // [rsp+160h] [rbp-40h] BYREF
  std::string __y; // [rsp+170h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/OutLinkVip.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C93A0);
  }

void CfgData::InitQQGameRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/QQGameDaTing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_QQGAME_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitQQZoneRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/QQZone.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_QQZONE_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitRefreshMonsterCfgListMap()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<RefreshMonsterCfg> *v2; // rax
  std::vector<Position> __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ActivityServer.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ACT_SHUA_GUAI_TABLE failed,please check!!");
  }

void CfgData::InitRongHeCfg()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  std::string *v13; // rax
  const char *v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  std::string *v17; // rax
  const char *v18; // rax
  std::string *v19; // rax
  const char *v20; // rax
  std::string *v21; // rax
  const char *v22; // rax
  std::string RongHeString; // [rsp+160h] [rbp-80h] BYREF
  std::string strItem; // [rsp+170h] [rbp-70h] BYREF
  std::string delims; // [rsp+180h] [rbp-60h] BYREF
  std::string v38; // [rsp+190h] [rbp-50h] BYREF

  CDBCFile &FileTable(0);
  if ( !FileTable.OpenFromTXT(, "./ServerConfig/Tables/ItemMix.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_RONG_HE_TABLE.txt failed,please check!!");
    v1 = 0;
  }

void CfgData::InitScoreShopTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ScoreShop.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SCORE_SHOP_TABLE failed,please check!!!\n");
  }

void CfgData::InitSelectItemCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/GiftChoose.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C9548);
  }

void CfgData::InitShangRenCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/MagicBusiness.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C94F8);
  }

void CfgData::InitShenWeiTaskTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ShenWeiTask.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileXiangY);
  }

void CfgData::InitShenYaoPosSuitTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string path; // [rsp+E0h] [rbp-70h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-60h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ShengZhuangSuit.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_POS_SUIT_TABLE failed,please check!!!\n");
  }

void CfgData::InitShenYaoPosTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string path; // [rsp+100h] [rbp-A0h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-90h] BYREF
  std::list<ItemData> strItems; // [rsp+120h] [rbp-80h] BYREF
  bool bCombi[15]; // [rsp+130h] [rbp-70h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ShengZhuangAttr.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_UP_POS_TABLE failed,please check!!!\n");
  }

void CfgData::InitShiZhuLevelUp()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-80h] BYREF
  bool bCombi[15]; // [rsp+E0h] [rbp-70h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-60h] BYREF
  _BYTE v10[15]; // [rsp+100h] [rbp-50h] BYREF
  int32_t v12[3]; // [rsp+110h] [rbp-40h] BYREF
  std::pair<int,int> __k; // [rsp+120h] [rbp-30h] BYREF

  CDBCFile &FileTable(0);
  if ( !FileTable.OpenFromTXT(, "./ServerConfig/Tables/ShiZhuangUpGrade.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_SHI_ZHUANG_LEVEL_UP_TABLE.txt failed,please check!!");
  }

void CfgData::InitShiZhuangLevelTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ShiZhuangLevel.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileShiZhu_2);
  }

void CfgData::InitShiZhuangTable()
{
  const CDBCFile::FIELD *v2; // rax
  std::list<AddAttribute> __x; // [rsp+110h] [rbp-90h] BYREF
  _BYTE v9[15]; // [rsp+120h] [rbp-80h] BYREF
  int32_t v11[3]; // [rsp+130h] [rbp-70h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/ShiZhuang.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileShiZhu_0);
    v1 = 0;
  }

void CfgData::InitShouHuRefining()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::list<AddAttribute> *v5; // rax
  std::list<ItemData> strItems; // [rsp+100h] [rbp-100h] BYREF
  bool bCombi[15]; // [rsp+110h] [rbp-F0h] BYREF
  std::list<AddAttribute> __x; // [rsp+120h] [rbp-E0h] BYREF
  _BYTE v14[15]; // [rsp+130h] [rbp-D0h] BYREF
  int32_t v16[3]; // [rsp+140h] [rbp-C0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,ShouHuRefinishingCfg> >,bool> v18; // [rsp+150h] [rbp-B0h]
  _BYTE v19[48]; // [rsp+160h] [rbp-A0h] BYREF
  std::pair<int,int> __a; // [rsp+190h] [rbp-70h] BYREF
  _BYTE v21[15]; // [rsp+1A0h] [rbp-60h] BYREF
  int32_t v23[4]; // [rsp+1B0h] [rbp-50h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/StarSpaceLevel.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitShunWangTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+220h] [rbp-80h] BYREF
  std::string v12; // [rsp+250h] [rbp-50h] BYREF

  CDBCFile &SwVip(0);
  ret = SwVip.OpenFromTXT(, "./ServerConfig/Tables/ShunWangHuiYuan.txt");
  if ( !ret )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SW_VIP_REWARD failed,please check!!\n");
  }

void CfgData::InitSouGouDaTing()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/SouGouDaTing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }

void CfgData::InitSouGouSkinTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string platform; // [rsp+C0h] [rbp-60h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SogouSkin.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SOU_GOU_SKIN_TABLE failed,please check!!!\n");
  }

void CfgData::InitSpeciaEquipCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-80h] BYREF
  _BYTE v7[15]; // [rsp+100h] [rbp-70h] BYREF
  int32_t v9[3]; // [rsp+110h] [rbp-60h] BYREF
  std::list<AddAttribute> v11; // [rsp+120h] [rbp-50h] BYREF
  _BYTE v12[15]; // [rsp+130h] [rbp-40h] BYREF
  int32_t v14[3]; // [rsp+140h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SpecialEquip.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileBuyFaB);
  }

void CfgData::InitSpeciaSkillDistanceTable()
{
  std::pair<int,int> __k; // [rsp+B0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SkillSpecialDamage.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SPECIAL_DAMAGE_TABLE.txt failed,please check!!");
  }

void CfgData::InitSpecialBossMapCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItem; // [rsp+C0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/MapConsume.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
  }

void CfgData::InitSpecialMap()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SpecialMap.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SPECIAL_MAP_TABLE.txt failed,please check!!");
  }

void CfgData::InitSpecialMonster()
{

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/SpecialMonster.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C78C8);
  }

void CfgData::InitSpecialTreasureMapRandTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+130h] [rbp-40h] BYREF
  std::string strItem; // [rsp+140h] [rbp-30h] BYREF

  thisa = this;
  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/SpecialTreasureMap.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_SPECIAL_TREASURE_MAP_TABLE failed,please check!!!\n");
  }

void CfgData::InitSpeed360Reward()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string p_StringTime; // [rsp+A0h] [rbp-70h] BYREF
  std::string v7; // [rsp+B0h] [rbp-60h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile &Speed360Revard(0);
  if ( !Speed360Revard.OpenFromTXT(, "./ServerConfig/Tables/Speed360Reward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_REWARD failed,please check!!");
  }

void CfgData::InitStrengthenTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItem; // [rsp+E0h] [rbp-C0h] BYREF
  std::string path; // [rsp+110h] [rbp-90h] BYREF
  std::string addonAttr; // [rsp+120h] [rbp-80h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/MieShenRongLian.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BACK failed,please check!!!\n");
  }

void CfgData::InitSuperMemberTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string platform; // [rsp+A0h] [rbp-40h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SuperMember.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SUPER_MEMBER_TABLE failed,please check!!!\n");
  }

void CfgData::InitSuperTeHuiTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/SuperDiscount.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SUPER_DISCOUNT_TABLE failed,please check!!!\n");
  }

void CfgData::InitSystemOpenReward()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/System.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SYSTEM_OPEN_TABLE.txt failed,please check!!");
  }

void CfgData::InitTGPDailyRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TGPEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TGP_DAILY_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitTGPLevelRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TGPLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TGP_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitTGPRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TGPReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_TGP_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitTalentActiveTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<ItemData> strItems; // [rsp+C0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+D0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SkillActive.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_ACTIVE_TALENT_TABLE fail, please check!!!\n");
  }

void CfgData::InitTalentPageTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SkillTree.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_PAGE_TABLE fail, please check!!!\n");
  }

void CfgData::InitTalentTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-60h] BYREF
  std::list<int> __x; // [rsp+110h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+120h] [rbp-40h] BYREF
  std::string path; // [rsp+130h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SkillTalent.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_TABLE fail, please check!!!\n");
  }

void CfgData::InitTaskCycleRewardTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TaskCycleReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TASK_CYCLE_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitTencentSevenDayLoginTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/TencentSevenDayLogin.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TENCENT_SEVEN_DAY_LOGIN_TABLE failed,please check!!!\n");
  }

void CfgData::InitTestServerReward()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TestActivity.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TEST_SERVER_REWARD_TABLE.txt failed,please check!!");
  }

void CfgData::InitTianLingTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+E0h] [rbp-60h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+100h] [rbp-40h] BYREF
  int32_t v12[3]; // [rsp+110h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TianLing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileAttrib);
  }

void CfgData::InitTitleTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+100h] [rbp-100h] BYREF
  std::string dressattr; // [rsp+130h] [rbp-D0h] BYREF
  std::string getttr; // [rsp+140h] [rbp-C0h] BYREF
  std::string params; // [rsp+150h] [rbp-B0h] BYREF
  std::string delims; // [rsp+160h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+170h] [rbp-90h] BYREF
  std::string path; // [rsp+1A0h] [rbp-60h] BYREF
  std::string v25; // [rsp+1D0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/Title.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_TITLE_TABLE failed,please check!!");
  }

void CfgData::InitTongTianChiRanTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/tongtianpaihang.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileTongTi);
  }

void CfgData::InitTouZiTable()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string strItems; // [rsp+F0h] [rbp-D0h] BYREF
  std::string v11; // [rsp+150h] [rbp-70h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/QiRiTouZi.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_SEVEN_DAY_TOU_ZI_TABEL failed,please check!!");
    v1 = 0;
  }

void CfgData::InitTreasureMapTabale()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  const std::string *v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  std::string *v17; // rax
  const char *v18; // rax
  std::string *v19; // rax
  const char *v20; // rax
  const CDBCFile::FIELD *v21; // rax
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin_0; // [rsp+150h] [rbp-1E0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+1A0h] [rbp-190h] BYREF
  std::string MapPosString; // [rsp+1D0h] [rbp-160h] BYREF
  std::string RateString; // [rsp+1E0h] [rbp-150h] BYREF
  std::string delims; // [rsp+1F0h] [rbp-140h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+200h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+210h] [rbp-120h] BYREF
  std::string v40; // [rsp+220h] [rbp-110h] BYREF
  std::string v43; // [rsp+230h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v45; // [rsp+240h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v46; // [rsp+250h] [rbp-E0h] BYREF
  std::string v47; // [rsp+260h] [rbp-D0h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/TreasureMapBase.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TREASURE_MAP_CFG_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitTrigSkillTable()
{
  const CDBCFile::FIELD *v1; // rax

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/SkillTrig.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TRIG_SKILL_TABLE fail, please check!!!\n");
  }

void CfgData::InitUltimateChallengeCfg()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string strItem; // [rsp+F0h] [rbp-90h] BYREF
  std::string strItems; // [rsp+120h] [rbp-60h] BYREF
  std::list<Param2> v13; // [rsp+130h] [rbp-50h] BYREF
  _BYTE v14[15]; // [rsp+140h] [rbp-40h] BYREF
  int32_t v16[3]; // [rsp+150h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/limitChallenge.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ULTIMATE_CHALLENGE_TABLE.txt failed,please check!!");
  }

void CfgData::InitVplanTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  std::string strItems; // [rsp+220h] [rbp-1A0h] BYREF
  std::string v14; // [rsp+250h] [rbp-170h] BYREF
  std::string v18; // [rsp+2C0h] [rbp-100h] BYREF
  std::string v22; // [rsp+310h] [rbp-B0h] BYREF
  std::string v25; // [rsp+340h] [rbp-80h] BYREF

  CDBCFile &VplanRevard(0);
  ret = VplanRevard.OpenFromTXT(, "./ServerConfig/Tables/VplanReward.txt");
  if ( !ret )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_REWARD failed,please check!!\n");
  }

void CfgData::InitWeiXinTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/WeiXin.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_WEI_XIN_TABLE failed,please check!!!\n");
  }

void CfgData::InitWingCfgTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ItemData> strItems; // [rsp+100h] [rbp-E0h] BYREF
  bool bCombi[15]; // [rsp+110h] [rbp-D0h] BYREF
  std::string path; // [rsp+140h] [rbp-A0h] BYREF
  std::string addonAttr; // [rsp+150h] [rbp-90h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/AttributeWing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_WING_CFG_TABEL failed,please check!!!\n");
  }

void CfgData::InitWingEquipPolish()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v5; // rax
  std::list<AddAttribute> *v6; // rax
  const CDBCFile::FIELD *v8; // rax
  const CDBCFile::FIELD *v9; // rax
  std::list<AddAttribute> *v10; // rax
  std::list<AddAttribute> __x; // [rsp+130h] [rbp-1E0h] BYREF
  _BYTE v18[15]; // [rsp+140h] [rbp-1D0h] BYREF
  int32_t v20[3]; // [rsp+150h] [rbp-1C0h] BYREF
  std::list<ItemData> strItems; // [rsp+160h] [rbp-1B0h] BYREF
  bool bCombi[15]; // [rsp+170h] [rbp-1A0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WingEquipPolish> >,bool> v25; // [rsp+180h] [rbp-190h]
  _BYTE v26[64]; // [rsp+190h] [rbp-180h] BYREF
  std::pair<int,int> __a; // [rsp+1D0h] [rbp-140h] BYREF
  _BYTE v28[15]; // [rsp+1E0h] [rbp-130h] BYREF
  int32_t v30[3]; // [rsp+1F0h] [rbp-120h] BYREF
  std::list<ItemData> v32; // [rsp+200h] [rbp-110h] BYREF
  bool v33[15]; // [rsp+210h] [rbp-100h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WinRefiningCfg> >,bool> v35; // [rsp+220h] [rbp-F0h]
  _BYTE v36[64]; // [rsp+230h] [rbp-E0h] BYREF
  std::pair<int,int> v37; // [rsp+270h] [rbp-A0h] BYREF
  _BYTE v38[15]; // [rsp+280h] [rbp-90h] BYREF
  int32_t v40[4]; // [rsp+290h] [rbp-80h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/WingEquipPolish.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }

void CfgData::InitWishRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/WishReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_WISH_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitWuHunCreateTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-90h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-80h] BYREF
  std::list<RateItem> v12; // [rsp+110h] [rbp-70h] BYREF
  _BYTE v13[15]; // [rsp+120h] [rbp-60h] BYREF
  std::string strItem; // [rsp+130h] [rbp-50h] BYREF
  std::list<RateItem> v17; // [rsp+140h] [rbp-40h] BYREF
  _BYTE v18[14]; // [rsp+150h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/WuHunMake.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_CREATE_WU_HUN_TABLE failed,please check!!!\n");
  }

void CfgData::InitWuHunItemTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<AddAttribute> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+F0h] [rbp-40h] BYREF
  int32_t v8[3]; // [rsp+100h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/WuHun.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_ITEM_TABLE failed,please check!!!\n");
  }

void CfgData::InitWuHunShopTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<CfgWuHunShop> *v2; // rax
  std::string strItem; // [rsp+100h] [rbp-30h] BYREF

  thisa = this;
  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/MysterShop.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_SHOP_TABLE failed,please check!!!\n");
  }

void CfgData::InitXianYaoTaskTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/XiangYaoTask.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileXiangY);
  }

void CfgData::InitXinMoTable()
{
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v7; // rax
  const CDBCFile::FIELD *v8; // rax
  std::string *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  const CDBCFile::FIELD *v15; // rax
  const CDBCFile::FIELD *v16; // rax
  const CDBCFile::FIELD *v19; // rax
  const CDBCFile::FIELD *v20; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+120h] [rbp-360h] BYREF
  std::string RateString; // [rsp+150h] [rbp-330h] BYREF
  std::list<AddAttribute> __x; // [rsp+160h] [rbp-320h] BYREF
  _BYTE v31[15]; // [rsp+170h] [rbp-310h] BYREF
  int32_t v33[3]; // [rsp+180h] [rbp-300h] BYREF
  std::list<ItemData> strItems; // [rsp+1C0h] [rbp-2C0h] BYREF
  bool bCombi[15]; // [rsp+1D0h] [rbp-2B0h] BYREF
  std::list<AddAttribute> v39; // [rsp+1E0h] [rbp-2A0h] BYREF
  _BYTE v40[15]; // [rsp+1F0h] [rbp-290h] BYREF
  int32_t v42[3]; // [rsp+200h] [rbp-280h] BYREF
  std::list<ItemData> v45; // [rsp+240h] [rbp-240h] BYREF
  bool v46[14]; // [rsp+250h] [rbp-230h] BYREF
  std::string delims; // [rsp+260h] [rbp-220h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+270h] [rbp-210h] BYREF
  std::string v52; // [rsp+280h] [rbp-200h] BYREF
  std::list<ItemData> v55; // [rsp+2C0h] [rbp-1C0h] BYREF
  bool v56[15]; // [rsp+2D0h] [rbp-1B0h] BYREF
  std::list<AddAttribute> v58; // [rsp+2E0h] [rbp-1A0h] BYREF
  _BYTE v59[15]; // [rsp+2F0h] [rbp-190h] BYREF
  int32_t v61[3]; // [rsp+300h] [rbp-180h] BYREF
  std::string v65; // [rsp+370h] [rbp-110h] BYREF
  std::string path; // [rsp+3C0h] [rbp-C0h] BYREF
  std::string str; // [rsp+3D0h] [rbp-B0h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/XinMoLevel.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoL);
    v1 = 0;
  }

void CfgData::InitXinMoTask(int32_t Level, int32_t Times)
{
  std::pair<const int,CfgTask> *v4; // rax
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v7; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+40h] [rbp-20h] BYREF

  std::vector<int>::vector(&TaskIdVt);
  for ( it._M_node = std::map<int,CfgTask>::begin(&m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgTask>::end(&m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.type == 42 )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.level <= Level
        && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.max_level >= Level;
      if ( v3 && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group == Times )
      {
        v4 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it);
        std::vector<int>::push_back(&TaskIdVt, &v4->first);
      }
    }
  }

void CfgData::InitXingMaiSlotTable()
{

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/XingMaiSlot.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingma);
  }

void CfgData::InitXingMaiTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ItemData> strItems; // [rsp+E0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+F0h] [rbp-60h] BYREF
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+110h] [rbp-40h] BYREF
  int32_t v12[3]; // [rsp+120h] [rbp-30h] BYREF

  CDBCFile &readFile(0);
  if ( !readFile.OpenFromTXT(, "./ServerConfig/Tables/AttributeXingMai.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, aOpenFileBuyFaB);
  }

void CfgData::InitXuWuTask(int32_t Level, int32_t Times)
{
  std::pair<const int,CfgTask> *v4; // rax
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v7; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+40h] [rbp-20h] BYREF

  std::vector<int>::vector(&TaskIdVt);
  for ( it._M_node = std::map<int,CfgTask>::begin(&m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgTask>::end(&m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.type == 9 )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.level <= Level
        && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.max_level >= Level;
      if ( v3 && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group == Times )
      {
        v4 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it);
        std::vector<int>::push_back(&TaskIdVt, &v4->first);
      }
    }
  }

void CfgData::InitXunLeiTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/XunLeiBox.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }

void CfgData::InitYYDaTing()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/YYDaTing.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }

void CfgData::InitYYVip()
{
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+110h] [rbp-50h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/YYHuiYuan.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
    v1 = 0;
  }

void CfgData::InitYellowDailyRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+140h] [rbp-70h] BYREF
  std::string v10; // [rsp+170h] [rbp-40h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/YellowEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_DAILY_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitYellowLevelRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string strItems; // [rsp+100h] [rbp-60h] BYREF
  std::string v9; // [rsp+130h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/YellowLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }

void CfgData::InitYellowRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string strItems; // [rsp+C0h] [rbp-30h] BYREF

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT(, "./ServerConfig/Tables/YellowReward.txt") )
  {
    Answer::Answer.print(::LogLevel::LOG_LEVEL_ERROR, "open FILE_YELLOW_REWARD_TABLE failed,please check!!!\n");
  }
