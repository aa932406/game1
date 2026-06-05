// Decompiled methods for class: CfgData
// Source: gameserver.cc
// Total methods: 266

#####################################
bool __cdecl CfgData::init(CfgData *const this, int32_t line, int32_t debug)
{
  CfgData::fetchServerConfig(this, line);
  CfgData::fetchActivity(this);
  CfgData::fetchBuff(this);
  CfgData::fetchDungeon(this);
  CfgData::fetchDungeonEvent(this);
  CfgData::fetchDungeonMonster(this);
  CfgData::fetchDungeonPlant(this);
  CfgData::fetchDungeonTrap(this);
  CfgData::fetchDungeonNpc(this);
  CfgData::fetchItem(this, 0);
  CfgData::fetchJob(this);
  CfgData::fetchLevelAttr(this);
  CfgData::fetchMap(this);
  CfgData::fetchMapMonster(this);
  CfgData::fetchMapPlant(this);
  CfgData::fetchChrShop(this);
  CfgData::fetchMapRegion(this);
  CfgData::fetchMonster(this);
  CfgData::fetchMonsterAI(this);
  CfgData::fetchMonsterAdjustTable(this);
  CfgData::fetchMonsterDropGroup(this);
  CfgData::fetchMonsterGroupDrop(this);
  CfgData::fetchMonsterTaskDrop(this);
  CfgData::fetchNpc(this);
  CfgData::fetchMovie(this);
  CfgData::fetchPlant(this);
  CfgData::fetchTask(this);
  CfgData::fetchTrap(this);
  CfgData::fetchLevelExp(this);
  CfgData::fetchSignReward(this);
  CfgData::InitGroupIconTable(this);
  CfgData::InitActiveSkillTable(this);
  CfgData::InitPassiveSkillTable(this);
  CfgData::InitTrigSkillTable(this);
  CfgData::InitTalentTable(this);
  CfgData::InitTalentPageTable(this);
  CfgData::InitFamilySkillTable(this);
  CfgData::InitTalentActiveTable(this);
  CfgData::InitEquipTable(this);
  CfgData::InitEquipUpStarTable(this);
  CfgData::InitEquipSuitTable(this);
  CfgData::InitEquipDecomposeTable(this);
  CfgData::InitEquipUpPosTable(this);
  CfgData::InitEquipPosSuitTable(this);
  CfgData::InitEquipBoxTable(this);
  CfgData::InitItemGemTable(this);
  CfgData::InitGemOpenHoleTable(this);
  CfgData::InitGemLevelUpTable(this);
  CfgData::InitGemSuitTable(this);
  CfgData::InitItemCombiTable(this);
  CfgData::InitMonsterRandTable(this);
  CfgData::InitCarrierTable(this);
  CfgData::InitCarrierAttrTable(this);
  CfgData::InitJueWeiTable(this);
  CfgData::InitPetTable(this);
  CfgData::InitPetAttrTable(this);
  CfgData::InitPetUpStarTable(this);
  CfgData::InitSkillLevelUpTable(this);
  CfgData::InitTaskCycleStarTable(this);
  CfgData::InitTaskCycleRewardTable(this);
  CfgData::InitFamilyTable(this);
  CfgData::InitFamilyWarJoinRewardTable(this);
  CfgData::InitFamilyWarReliveTable(this);
  CfgData::InitFamilyLightExpTable(this);
  CfgData::InitHorseRacingRewardTable(this);
  CfgData::InitCampWarRewardTable(this);
  CfgData::InitCampWarContKillTable(this);
  CfgData::InitCityWarContRewardTable(this);
  CfgData::InitHallOfFameRewardTable(this);
  CfgData::InitTitleTable(this);
  CfgData::InitGoldEggTable(this);
  CfgData::InitLimitTimeTable(this);
  CfgData::InitMysteryShopTable(this);
  CfgData::InitBuyGiftTable(this);
  CfgData::InitExchangeTable(this);
  CfgData::InitMysteryGiftTable(this);
  CfgData::InitDrawTable(this);
  CfgData::InitMapRoadTable(this);
  CfgData::InitTrailerTable(this);
  CfgData::InitMYSJRewardTable(this);
  CfgData::InitMaintainCompensateTable(this);
  CfgData::InitWishRewardTable(this);
  CfgData::InitBFZLEnterCostTable(this);
  CfgData::InitBlacketMarketTable(this);
  CfgData::InitLevelChatTimesTable(this);
  CfgData::InitSuperMemberTable(this);
  CfgData::InitSouGouSkinTable(this);
  CfgData::InitPetEquipTable(this);
  CfgData::InitWeiXinTable(this);
  CfgData::InitAdultGiftTable(this);
  CfgData::InitQQZoneRewardTable(this);
  CfgData::InitQQGameRewardTable(this);
  CfgData::InitYellowRewardTable(this);
  CfgData::InitYellowDailyRewardTable(this);
  CfgData::InitYellowLevelRewardTable(this);
  CfgData::InitBlueRewardTable(this);
  CfgData::InitBlueDailyRewardTable(this);
  CfgData::InitBlueLevelRewardTable(this);
  CfgData::InitTGPRewardTable(this);
  CfgData::InitTGPDailyRewardTable(this);
  CfgData::InitTGPLevelRewardTable(this);
  CfgData::InitFamilyDungeonTable(this);
  CfgData::InitDropRecordTable(this);
  CfgData::InitDungeonScoreTable(this);
  CfgData::InitDungeonSummon(this);
  CfgData::InitSysMail(this);
  CfgData::InitBossInfo(this);
  CfgData::InitFaBaoTable(this);
  CfgData::InitDaTiHD(this);
  CfgData::InitShangChengTable(this);
  CfgData::InitOnLimeReward(this);
  CfgData::InitSevenLoginReward(this);
  CfgData::InitLevelGift(this);
  CfgData::InitWeekOnlineReward(this);
  CfgData::InitOffLineExpTable(this);
  CfgData::InitVipCardTable(this);
  CfgData::InitFunctionOpenTable(this);
  CfgData::InitPlantEventTable(this);
  CfgData::InitZiYuanZhaoHuiTable(this);
  CfgData::InitMoHuaHuanYiTable(this);
  CfgData::InitShouChongLiBao(this);
  CfgData::InitNewServerFavorable(this);
  CfgData::InitMobilePhoneGiftTable(this);
  CfgData::InitEveryDayChongZhi(this);
  CfgData::InitKaiFuHuoDongTable(this);
  CfgData::InitHuoYueDuTable(this);
  CfgData::InitAppendAttrTable(this);
  CfgData::InitFamilyRewardTable(this);
  CfgData::InitTotalChongZhiTable(this);
  CfgData::InitSpecialTreasureMapRandTable(this);
  CfgData::InitMonsterAddAttrTable(this);
  CfgData::InitDaZheQuanTable(this);
  CfgData::Init360RewardTable(this);
  CfgData::Init360RewardTypeTable(this);
  CfgData::InitVplanTable(this);
  CfgData::InitShunWangTable(this);
  CfgData::InitSpeed360Reward(this);
  CfgData::InitTencentSevenDayLoginTable(this);
  CfgData::InitGoblinData(this);
  CfgData::InitSpecialMonster(this);
  CfgData::InitEquipUpPhase(this);
  CfgData::InitTouZiTable(this);
  CfgData::InitGroupMonster(this);
  CfgData::InitPkDropRateTable(this);
  CfgData::InitEquipBackTable(this);
  CfgData::InitStrengthenTable(this);
  CfgData::InitBuyFaBaoResTable(this);
  CfgData::InitXingMaiTable(this);
  CfgData::InitXingMaiSlotTable(this);
  CfgData::InitTianLingTable(this);
  CfgData::InitGongMinTable(this);
  CfgData::InitBeastShrineEnterCostTable(this);
  CfgData::InitDamnationTable(this);
  CfgData::InitAttrBattleTable(this);
  CfgData::InitScoreShopTable(this);
  CfgData::InitChouJiangTable(this);
  CfgData::InitWingCfgTable(this);
  CfgData::InitLibraryTable(this);
  CfgData::InitTreasureMapTabale(this);
  CfgData::InitEquipBackTask(this);
  CfgData::InitSpeciaEquipCfgMap(this);
  CfgData::InitSpeciaSkillDistanceTable(this);
  CfgData::InitLuckDropTable(this);
  CfgData::InitLevelRefiningTable(this);
  CfgData::InitBossFirstKilledTable(this);
  CfgData::InitUltimateChallengeCfg(this);
  CfgData::InitCachetCfg(this);
  CfgData::InitBossKilledReward(this);
  CfgData::InitSystemOpenReward(this);
  CfgData::InitSpecialMap(this);
  CfgData::InitTestServerReward(this);
  CfgData::InitEquipBlessTable(this);
  CfgData::InitGuWuCfgMap(this);
  CfgData::InitFunctionOpenMailMap(this);
  CfgData::InitXianYaoTaskTable(this);
  CfgData::InitShenWeiTaskTable(this);
  CfgData::InitMiniClientTable(this);
  CfgData::InitWuHunShopTable(this);
  CfgData::InitWuHunItemTable(this);
  CfgData::InitWuHunCreateTable(this);
  CfgData::InitBossDistribution(this);
  CfgData::InitSpecialBossMapCfgMap(this);
  CfgData::InitDuiHuanLimitTable(this);
  CfgData::InitSuperTeHuiTable(this);
  CfgData::InitJewelPavilionTable(this);
  CfgData::InitGoblinTable(this);
  CfgData::InitShouHuRefining(this);
  CfgData::InitWingEquipPolish(this);
  CfgData::InitGuiGuDaoRenTable(this);
  CfgData::InitShiZhuangTable(this);
  CfgData::InitShiZhuangLevelTable(this);
  CfgData::InitMonthlyChouJiangTable(this);
  CfgData::InitActDropTable(this);
  CfgData::InitSevenTaskTable(this);
  CQiFuTable::InitQiFuTable(&this->m_QiFuTable);
  VipTable::InitVipTable(&this->m_VipTable);
  CfgData::InitOutLinkFestivalTable(this);
  CfgData::InitYYDaTing(this);
  CfgData::InitYYVip(this);
  CfgData::InitSouGouDaTing(this);
  CfgData::InitXunLeiTable(this);
  CfgData::InitCycleTowerTable(this);
  CfgData::InitPlatformDaTingMap(this);
  CfgData::InitMiniClientMap(this);
  CfgData::InitPlatformVipMap(this);
  CfgData::InitShangRenCfgMap(this);
  CfgData::InitSelectItemCfgMap(this);
  CfgData::InitGuardPrivilegeTable(this);
  CfgData::InitPlatformReward(this);
  CfgData::InitDiligenceCfgMap(this);
  CfgData::InitFamilyDonateTable(this);
  CfgData::InitFamilyMedalTable(this);
  CfgData::InitHoeTable(this);
  CfgData::InitMingGeTable(this);
  CfgData::InitCrossTowerCfgMap(this);
  CfgData::InitKunLingTable(this);
  CfgData::InitLaDaShiHuiYuan(this);
  CfgData::InitFlopTable(this);
  CfgData::InitMoFuTable(this);
  CfgData::InitChristmasDuiHuanTable(this);
  CfgData::InitBaoKuFuBen(this);
  CfgData::InitChargeDungeon(this);
  CfgData::InitShenYaoPosTable(this);
  CfgData::InitShenYaoPosSuitTable(this);
  CfgData::InitTongTianChiRanTable(this);
  CfgData::InitXinMoTable(this);
  CfgData::InitGameTable(this);
  CfgData::InitRefreshMonsterCfgListMap(this);
  CfgData::InitLittleHelperCfg(this);
  CfgData::InitShiZhuLevelUp(this);
  CfgData::InitNationalDayTask(this);
  CfgData::InitRongHeCfg(this);
  this->m_MapMonsterId = (int)&unk_989680;
  this->m_debug = debug;
  return 1;
}


#####################################
void __cdecl CfgData::reload(CfgData *const this)
{
  ItemEffectManager *v1; // rax

  CfgData::fetchItem(this, 1);
  v1 = Answer::Singleton<ItemEffectManager>::instance();
  ItemEffectManager::init(v1);
}


#####################################
int32_t __cdecl CfgData::GetMapMonsterId(CfgData *const this)
{
  return ++this->m_MapMonsterId;
}


#####################################
bool __cdecl CfgData::getMovie(CfgData *const this, int32_t id)
{
  int32_t ida; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgMovie> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgMovie> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  ida = id;
  it._M_node = std::map<int,CfgMovie>::find(&this->m_movie, &ida)._M_node;
  __x._M_node = std::map<int,CfgMovie>::end(&thisa->m_movie)._M_node;
  return std::_Rb_tree_iterator<std::pair<int const,CfgMovie>>::operator!=(&it, &__x);
}


#####################################
bool __cdecl CfgData::isMonsterBroadcast(CfgData *const this, int32_t mid)
{
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v3; // rax
  int32_t mida; // [rsp+4h] [rbp-3Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-38h]
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __lhs; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  mida = mid;
  __rhs._M_current = std::vector<int>::end(&this->m_monsterBroadcasts)._M_current;
  M_current = std::vector<int>::end(&this->m_monsterBroadcasts)._M_current;
  v3._M_current = std::vector<int>::begin(&this->m_monsterBroadcasts)._M_current;
  __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<int *,std::vector<int>>,int>(
                       v3,
                       (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current,
                       &mida)._M_current;
  return __gnu_cxx::operator!=<int *,std::vector<int>>(&__lhs, &__rhs);
}


#####################################
int8_t __cdecl CfgData::GetTaskType(CfgData *const this, int32_t id)
{
  int v2; // eax
  int32_t ida; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  ida = id;
  it._M_node = std::map<int,CfgTask>::find(&this->m_tasks, &ida)._M_node;
  __x._M_node = std::map<int,CfgTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.type;
  else
    LOBYTE(v2) = 0;
  return v2;
}


#####################################
void __cdecl CfgData::InitMoneyRewardTask(
        CfgData *const this,
        TaskStateInfo (*const MoneyRewardTask)[9],
        int32_t Level)
{
  Answer::Random *v5; // rax
  int v6; // ebx
  int v7; // ebx
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t i; // [rsp+38h] [rbp-18h]
  int32_t nRand; // [rsp+3Ch] [rbp-14h]

  for ( i = 0; i <= 8; ++i )
  {
    (*MoneyRewardTask)[i].TaskId = 0;
    (*MoneyRewardTask)[i].TaskState = 0;
  }
  for ( it._M_node = std::map<int,CfgTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.type == 2
      && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.level <= Level
      && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.max_level >= Level
      && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group > 0
      && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group <= 9 )
    {
      if ( (*MoneyRewardTask)[std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group - 1].TaskId <= 0 )
      {
        v7 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group - 1;
        (*MoneyRewardTask)[v7].TaskId = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->first;
        (*MoneyRewardTask)[std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group - 1].TaskState = 1;
      }
      else
      {
        v5 = Answer::Singleton<Answer::Random>::instance();
        nRand = Answer::Random::generate(v5, 1, 100);
        if ( nRand <= 29 )
        {
          v6 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.group - 1;
          (*MoneyRewardTask)[v6].TaskId = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->first;
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CfgData::InitXuWuTask(CfgData *const this, int32_t Level, int32_t Times)
{
  bool v3; // al
  std::pair<const int,CfgTask> *v4; // rax
  int32_t v5; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v7; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+10h] [rbp-50h] BYREF
  Int32Vector TaskIdVt; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+40h] [rbp-20h] BYREF

  std::vector<int>::vector(&TaskIdVt);
  for ( it._M_node = std::map<int,CfgTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgTask>::end(&this->m_tasks)._M_node;
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
  if ( std::vector<int>::size(&TaskIdVt) )
  {
    M_current = std::vector<int>::end(&TaskIdVt)._M_current;
    v7._M_current = std::vector<int>::begin(&TaskIdVt)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
      v7,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    v5 = *std::vector<int>::front(&TaskIdVt);
  }
  else
  {
    v5 = 0;
  }
  std::vector<int>::~vector(&TaskIdVt);
  return v5;
}


#####################################
int32_t __cdecl CfgData::InitXinMoTask(CfgData *const this, int32_t Level, int32_t Times)
{
  bool v3; // al
  std::pair<const int,CfgTask> *v4; // rax
  int32_t v5; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v7; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+10h] [rbp-50h] BYREF
  Int32Vector TaskIdVt; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+40h] [rbp-20h] BYREF

  std::vector<int>::vector(&TaskIdVt);
  for ( it._M_node = std::map<int,CfgTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgTask>::end(&this->m_tasks)._M_node;
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
  if ( std::vector<int>::size(&TaskIdVt) )
  {
    M_current = std::vector<int>::end(&TaskIdVt)._M_current;
    v7._M_current = std::vector<int>::begin(&TaskIdVt)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
      v7,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    v5 = *std::vector<int>::front(&TaskIdVt);
  }
  else
  {
    v5 = 0;
  }
  std::vector<int>::~vector(&TaskIdVt);
  return v5;
}


#####################################
int32_t __cdecl CfgData::RandPdbfTask(CfgData *const this, int32_t Level)
{
  std::pair<const int,CfgTask> *v3; // rax
  int32_t v4; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v6; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > it; // [rsp+10h] [rbp-50h] BYREF
  Int32Vector TaskVt; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgTask> > __x; // [rsp+40h] [rbp-20h] BYREF

  std::vector<int>::vector(&TaskVt);
  for ( it._M_node = std::map<int,CfgTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.type == 4
      && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.level <= Level
      && std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it)->second.max_level >= Level )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,CfgTask>>::operator->(&it);
      std::vector<int>::push_back(&TaskVt, &v3->first);
    }
  }
  if ( std::vector<int>::size(&TaskVt) )
  {
    M_current = std::vector<int>::end(&TaskVt)._M_current;
    v6._M_current = std::vector<int>::begin(&TaskVt)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
      v6,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    v4 = *std::vector<int>::front(&TaskVt);
  }
  else
  {
    v4 = 0;
  }
  std::vector<int>::~vector(&TaskVt);
  return v4;
}


#####################################
int32_t __cdecl CfgData::getOverlay(CfgData *const this, int32_t nId, int8_t nClass)
{
  const CfgItemGemTable *ItemGemTable; // rax
  CfgItem *cfgItem; // [rsp+10h] [rbp-30h]
  int32_t overlay; // [rsp+1Ch] [rbp-24h]
  const CfgItemGem *cfgGem; // [rsp+20h] [rbp-20h]
  int32_t overlay_0; // [rsp+2Ch] [rbp-14h]
  WuHunItem *pWuHun; // [rsp+30h] [rbp-10h]
  int32_t overlay_1; // [rsp+3Ch] [rbp-4h]

  if ( nClass == 3 )
  {
    ItemGemTable = CfgData::GetItemGemTable(this);
    cfgGem = CfgItemGemTable::GetItemGem(ItemGemTable, nId);
    if ( !cfgGem )
      return 0;
    overlay_0 = cfgGem->m_nLayNum;
    if ( !overlay_0 )
      return 1;
    return overlay_0;
  }
  else
  {
    if ( nClass <= 3 )
    {
      if ( nClass != 1 )
        return 1;
      cfgItem = CfgData::getItem(this, nId);
      if ( cfgItem )
      {
        overlay = cfgItem->overlay;
        if ( !overlay )
          return 1;
        return overlay;
      }
      return 0;
    }
    if ( nClass != 8 )
    {
      if ( nClass == 11 )
        return 99;
      return 1;
    }
    pWuHun = CfgData::GetWuHunItem(this, nId);
    if ( !pWuHun )
      return 0;
    overlay_1 = pWuHun->overlay;
    if ( !overlay_1 )
      return 1;
    return overlay_1;
  }
}


#####################################
int32_t __cdecl CfgData::getOutValue(CfgData *const this, int32_t nId, int8_t nClass)
{
  const CfgItemGemTable *ItemGemTable; // rax
  CfgItem *pItem; // [rsp+10h] [rbp-20h]
  const CfgEquip *pEquip; // [rsp+18h] [rbp-18h]
  const CfgItemGem *pGem; // [rsp+20h] [rbp-10h]
  const CfgPetEquip *pPetEquip; // [rsp+28h] [rbp-8h]

  if ( nClass == 2 )
  {
    pEquip = CfgData::getEquip(this, nId);
    if ( pEquip )
      return pEquip->m_nPrice;
  }
  else if ( nClass > 2 )
  {
    if ( nClass == 3 )
    {
      ItemGemTable = CfgData::GetItemGemTable(this);
      pGem = CfgItemGemTable::GetItemGem(ItemGemTable, nId);
      if ( pGem )
        return pGem->m_nPrice;
    }
    else if ( nClass == 7 )
    {
      pPetEquip = CfgPetEquipTable::GetEquip(&this->m_cfgPetEquipTable, nId);
      if ( pPetEquip )
        return pPetEquip->nPrice;
    }
  }
  else if ( nClass == 1 )
  {
    pItem = CfgData::getItem(this, nId);
    if ( pItem )
      return pItem->out_value;
  }
  return -1;
}


#####################################
bool __cdecl CfgData::dropBroadcast(CfgData *const this, int32_t nId, int8_t nClass)
{
  CfgItem *pItem; // [rsp+18h] [rbp-18h]
  const CfgEquip *pEquip; // [rsp+20h] [rbp-10h]
  const CfgPetEquip *pPetEquip; // [rsp+28h] [rbp-8h]

  switch ( nClass )
  {
    case 2:
      pEquip = CfgData::getEquip(this, nId);
      if ( pEquip )
        return pEquip->m_nBroadcast > 0;
      break;
    case 7:
      pPetEquip = CfgPetEquipTable::GetEquip(&this->m_cfgPetEquipTable, nId);
      if ( pPetEquip )
        return pPetEquip->nBroadcast > 0;
      break;
    case 1:
      pItem = CfgData::getItem(this, nId);
      if ( pItem )
        return pItem->broadcast > 0;
      break;
  }
  return 0;
}


#####################################
bool __cdecl CfgData::canSell(CfgData *const this, int32_t nId, int8_t nClass)
{
  CfgItem *pCfgItem; // [rsp+18h] [rbp-8h]

  return nClass != 1 || (pCfgItem = CfgData::getItem(this, nId)) == 0 || pCfgItem->can_sell != 0;
}


#####################################
int64_t __cdecl CfgData::getNeedLevelExp(CfgData *const this, int32_t level)
{
  int32_t levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  levela = level;
  it._M_node = std::map<int,CfgLevelExp>::find(&this->m_levelExps, &levela)._M_node;
  __x._M_node = std::map<int,CfgLevelExp>::end(&thisa->m_levelExps)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator->(&it)->second.upgrade_exp;
  else
    return std::numeric_limits<long>::max();
}


#####################################
int64_t __cdecl CfgData::getMaxExp(CfgData *const this, int32_t level)
{
  int32_t levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  levela = level;
  it._M_node = std::map<int,CfgLevelExp>::find(&this->m_levelExps, &levela)._M_node;
  __x._M_node = std::map<int,CfgLevelExp>::end(&thisa->m_levelExps)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator->(&it)->second.max_exp;
  else
    return std::numeric_limits<long>::max();
}


#####################################
int32_t __cdecl CfgData::GetPetExp(CfgData *const this, int32_t level)
{
  int32_t levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  levela = level;
  it._M_node = std::map<int,CfgLevelExp>::find(&this->m_levelExps, &levela)._M_node;
  __x._M_node = std::map<int,CfgLevelExp>::end(&thisa->m_levelExps)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator->(&it)->second.pet_exp;
  else
    return std::numeric_limits<int>::max();
}


#####################################
int32_t __cdecl CfgData::GetTalentPoint(CfgData *const this, int32_t level)
{
  int32_t levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  levela = level;
  iter._M_node = std::map<int,CfgLevelExp>::find(&this->m_levelExps, &levela)._M_node;
  __x._M_node = std::map<int,CfgLevelExp>::end(&thisa->m_levelExps)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator->(&iter)->second.talent_point;
  else
    return 0;
}


#####################################
int32_t __cdecl CfgData::GetAttrPoint(CfgData *const this, int32_t level)
{
  int32_t levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelExp> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  levela = level;
  iter._M_node = std::map<int,CfgLevelExp>::find(&this->m_levelExps, &levela)._M_node;
  __x._M_node = std::map<int,CfgLevelExp>::end(&thisa->m_levelExps)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,CfgLevelExp>>::operator->(&iter)->second.attr_point;
  else
    return 0;
}


#####################################
int32_t __cdecl CfgData::getBaseJob(CfgData *const this, int32_t job)
{
  if ( job == 2 )
    return 2;
  if ( job == 3 )
    return 3;
  return job == 1;
}


#####################################
void __cdecl CfgData::InitGroupIconTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgGroupIcon *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgGroupIcon icon; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GroupIcon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_GROUP_ICON_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        *(_QWORD *)&icon.nId = 0;
        icon.platfrom._M_dataplus._M_p = 0;
        std::string::string(&icon.platfrom);
        icon.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        icon.bShowInCross = CDBCFile::Search_Posistion(&readFile, i, 18)->iValue;
        v1 = CDBCFile::Search_Posistion(&readFile, i, 19);
        std::string::operator=(&icon.platfrom, v1->pString);
        v2 = std::map<int,CfgGroupIcon>::operator[](&this->m_cfgGroupIcons, &icon.nId);
        CfgGroupIcon::operator=(v2, &icon);
        CfgGroupIcon::~CfgGroupIcon(&icon);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
bool __cdecl CfgData::IsShowIcon(CfgData *const this, int32_t nIconId, const std::string *const platform)
{
  GameService *v4; // rax
  bool v6; // al
  int32_t nIconIda; // [rsp+14h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+18h] [rbp-48h]
  std::_Rb_tree_const_iterator<std::pair<const int,CfgGroupIcon> > iter; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgGroupIcon> > __it; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgGroupIcon> > __x; // [rsp+40h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgGroupIcon> > v13; // [rsp+50h] [rbp-10h] BYREF
  const CfgGroupIcon *icon; // [rsp+58h] [rbp-8h]

  thisa = this;
  nIconIda = nIconId;
  __it._M_node = std::map<int,CfgGroupIcon>::find(&this->m_cfgGroupIcons, &nIconIda)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::_Rb_tree_const_iterator(&iter, &__it);
  v13._M_node = std::map<int,CfgGroupIcon>::end(&thisa->m_cfgGroupIcons)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::_Rb_tree_const_iterator(&__x, &v13);
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::operator==(&iter, &__x) )
    return 0;
  icon = &std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::operator->(&iter)->second;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 && !icon->bShowInCross )
    return 0;
  v6 = std::operator!=<char>(&icon->platfrom, "-1") && std::operator!=<char>(platform, &icon->platfrom);
  return !v6;
}


#####################################
void __cdecl CfgData::InitFamilyRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  FamilyTaskReward *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  FamilyTaskReward stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/FamilyTaskRing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_TASK_RING failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.Rewards);
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.NeedCount = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        v2 = std::map<int,FamilyTaskReward>::operator[](&this->m_FamilyTaskReward, &stu.Index);
        FamilyTaskReward::operator=(v2, &stu);
        FamilyTaskReward::~FamilyTaskReward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitAppendAttrTable(CfgData *const this)
{
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  AddAttribute Attr; // [rsp+A0h] [rbp-50h] BYREF
  CfgAppendAttr stu; // [rsp+B0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+CCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+D0h] [rbp-20h]
  int32_t i; // [rsp+D4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+D8h] [rbp-18h]
  int32_t j; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/AdditionalAttribute.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_APPEND_ATTR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<AddAttribute>::list(&stu.AttrList);
        stu.Id = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.Job = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        for ( j = 0; j <= 9; ++j )
        {
          AddAttribute::AddAttribute(&Attr);
          Attr.m_nAddAttrType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
          Attr.m_nAddAttrValue = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
          if ( Attr.m_nAddAttrValue > 0 )
            std::list<AddAttribute>::push_back(&stu.AttrList, &Attr);
        }
        std::list<CfgAppendAttr>::push_back(&this->m_AppendAttrTable, &stu);
        CfgAppendAttr::~CfgAppendAttr(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitHuoYueDuTable(CfgData *const this)
{
  CfgHuoYueDu *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgHuoYueDuReward *v3; // rax
  CDBCFile TabFileReward; // [rsp+10h] [rbp-1B0h] BYREF
  CDBCFile TabFile; // [rsp+A0h] [rbp-120h] BYREF
  CfgHuoYueDuReward stu_0; // [rsp+130h] [rbp-90h] BYREF
  CfgHuoYueDu stu; // [rsp+150h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+170h] [rbp-50h] BYREF
  std::string strItems; // [rsp+190h] [rbp-30h] BYREF
  char v10; // [rsp+19Dh] [rbp-23h] BYREF
  char __k; // [rsp+19Eh] [rbp-22h] BYREF
  bool ret; // [rsp+19Fh] [rbp-21h]
  int32_t iBaseTableCount; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1A4h] [rbp-1Ch]
  int32_t i; // [rsp+1A8h] [rbp-18h]
  int32_t i_0; // [rsp+1ACh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  ret = CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/HuoYueDu.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_HUO_YUE_DU_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.Type = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        stu.Effect = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        stu.Count = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        stu.Gold = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        stu.AddHuoYueDu = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        stu.IsCanSec = CDBCFile::Search_Posistion(&TabFile, i, 6)->iValue > 0;
        v1 = std::map<int,CfgHuoYueDu>::operator[](&this->m_HuoYueDuTable, &stu.Index);
        *v1 = stu;
      }
      CDBCFile::CDBCFile(&TabFileReward, 0);
      ret = CDBCFile::OpenFromTXT(&TabFileReward, "./ServerConfig/Tables/HuoYueDuReward.txt");
      if ( !ret )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_HUO_YUE_DU_REWARD_TABLE failed,please check!!!\n");
      }
      else
      {
        iBaseTableCount = CDBCFile::GetRecordsNum(&TabFileReward);
        iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFileReward);
        if ( iBaseColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount; ++i_0 )
          {
            memset(&stu_0, 0, sizeof(stu_0));
            std::vector<MemChrBag>::vector(&stu_0.Items);
            stu_0.Id = CDBCFile::Search_Posistion(&TabFileReward, i_0, 0)->iValue;
            stu_0.NeedHuoYueDu = CDBCFile::Search_Posistion(&TabFileReward, i_0, 1)->iValue;
            std::allocator<char>::allocator(&v10);
            v2 = CDBCFile::Search_Posistion(&TabFileReward, i_0, 2);
            std::string::string(&strItems, v2->pString, &v10);
            CItemHelper::parseItemVectorString(&__x, &strItems);
            std::vector<MemChrBag>::operator=(&stu_0.Items, &__x);
            std::vector<MemChrBag>::~vector(&__x);
            std::string::~string(&strItems);
            std::allocator<char>::~allocator(&v10);
            __k = stu_0.Id;
            v3 = std::map<signed char,CfgHuoYueDuReward>::operator[](&this->m_HuoYueDuRewardTable, &__k);
            CfgHuoYueDuReward::operator=(v3, &stu_0);
            CfgHuoYueDuReward::~CfgHuoYueDuReward(&stu_0);
          }
        }
      }
      CDBCFile::~CDBCFile(&TabFileReward);
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitKaiFuHuoDongTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CfgKaiFuHuoDongData *v4; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-140h] BYREF
  CfgKaiFuHuoDongData stu; // [rsp+A0h] [rbp-B0h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-50h] BYREF
  std::string strItems; // [rsp+120h] [rbp-30h] BYREF
  char v9; // [rsp+12Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t Index; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/NewServer.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_KAI_FU_HUO_DONG failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.ItemVector);
        std::string::string(&stu.ItemString);
        std::string::string(&stu.FlopString);
        Index = 0;
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.Type = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.Level = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.StartDay = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.EndDay = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.Conditions = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        ++Index;
        if ( stu.Type == 17 )
        {
          v1 = CDBCFile::Search_Posistion(&TabFile, i, Index);
          std::string::operator=(&stu.ItemString, v1->pString);
        }
        else
        {
          std::allocator<char>::allocator(&v9);
          v2 = CDBCFile::Search_Posistion(&TabFile, i, Index);
          std::string::string(&strItems, v2->pString, &v9);
          CItemHelper::parseItemVectorString(&__x, &strItems);
          std::vector<MemChrBag>::operator=(&stu.ItemVector, &__x);
          std::vector<MemChrBag>::~vector(&__x);
          std::string::~string(&strItems);
          std::allocator<char>::~allocator(&v9);
        }
        stu.PetAttr = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.Limit = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        stu.PetEffect = CDBCFile::Search_Posistion(&TabFile, i, ++Index)->iValue;
        ++Index;
        Index += 5;
        stu.Conditions1 = CDBCFile::Search_Posistion(&TabFile, i, Index++)->iValue;
        v3 = CDBCFile::Search_Posistion(&TabFile, i, Index);
        std::string::operator=(&stu.FlopString, v3->pString);
        ++Index;
        v4 = std::map<int,CfgKaiFuHuoDongData>::operator[](&this->m_KaiFuHuoDongTable, &stu.Index);
        CfgKaiFuHuoDongData::operator=(v4, &stu);
        CfgKaiFuHuoDongData::~CfgKaiFuHuoDongData(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitDropRecordTable(CfgData *const this)
{
  CfgDropRecord *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgDropRecord record; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/DropRecord.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DROP_RECORD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&record.nIndex = 0;
        *(_DWORD *)&record.nItemClass = 0;
        record.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        record.nItemId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        record.nItemClass = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        record.nSpecial = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,CfgDropRecord>::operator[](&this->m_cfgDropRecordTable, &record.nIndex);
        *v1 = record;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitDungeonScoreTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  MemChrBag v2; // [rsp+0h] [rbp-120h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-F8h]
  CDBCFile TabFile; // [rsp+30h] [rbp-F0h] BYREF
  CfgDungeonScore score; // [rsp+C0h] [rbp-60h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/DungeonScore.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DUNGEON_SCORE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&score, 0, sizeof(score));
        score.nDungeonId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        score.nKillCount = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v7);
        CItemHelper::parseItemString(&v2, &strItem);
        score.Item = v2;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        CfgDungeonScoreTable::AddDungeonScore(&thisa->m_cfgDungeonScoreTable, &score);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitDungeonSummon(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgDungeonSummon *v3; // rax
  __int64 v4; // rax
  CDBCFile DungeonTrapFile; // [rsp+10h] [rbp-130h] BYREF
  CfgDungeonSummon stu; // [rsp+A0h] [rbp-A0h] BYREF
  std::list<int> __x; // [rsp+D0h] [rbp-70h] BYREF
  int32_t size[3]; // [rsp+E0h] [rbp-60h] BYREF
  char v9; // [rsp+EFh] [rbp-51h] BYREF
  std::string path; // [rsp+F0h] [rbp-50h] BYREF
  char v11; // [rsp+FFh] [rbp-41h] BYREF
  std::string strItem; // [rsp+100h] [rbp-40h] BYREF
  char v13; // [rsp+10Fh] [rbp-31h] BYREF
  std::pair<int,int> __k; // [rsp+110h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]
  ItemData v20; // 0:kr00_12.12

  CDBCFile::CDBCFile(&DungeonTrapFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonTrapFile, "./ServerConfig/Tables/cfg_dungeon_summon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DUNGEON_SUMMON_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonTrapFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonTrapFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgDungeonSummon::CfgDungeonSummon(&stu);
        stu.nDungeon = CDBCFile::Search_Posistion(&DungeonTrapFile, i, nIndex++)->iValue;
        stu.nIndex = CDBCFile::Search_Posistion(&DungeonTrapFile, i, nIndex++)->iValue;
        stu.nGold = CDBCFile::Search_Posistion(&DungeonTrapFile, i, nIndex++)->iValue;
        stu.nLimit = CDBCFile::Search_Posistion(&DungeonTrapFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v9);
        std::string::string(size, "./ServerConfig/Tables/cfg_dungeon_summon.txt", &v9);
        std::allocator<char>::allocator(&v11);
        v1 = CDBCFile::Search_Posistion(&DungeonTrapFile, i, nIndex);
        std::string::string(&path, v1->pString, &v11);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.lMonsters, &__x);
        std::list<int>::~list(&__x);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v11);
        std::string::~string(size);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&DungeonTrapFile, i, nIndex);
        std::string::string(&strItem, v2->pString, &v13);
        v20 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v4) = v20.m_nId;
        BYTE4(v4) = v20.m_nClass;
        *(_QWORD *)&stu.ConstItem.m_nId = v4;
        stu.ConstItem.m_nCount = v20.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v13);
        stu.FreeCount = CDBCFile::Search_Posistion(&DungeonTrapFile, i, ++nIndex)->iValue;
        ++nIndex;
        __k = std::make_pair<int,int>(stu.nDungeon, stu.nIndex);
        v3 = std::map<std::pair<int,int>,CfgDungeonSummon>::operator[](&this->m_cfgDungeonSummon, &__k);
        CfgDungeonSummon::operator=(v3, &stu);
        CfgDungeonSummon::~CfgDungeonSummon(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&DungeonTrapFile);
}


#####################################
void __cdecl CfgData::InitSpecialTreasureMapRandTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  MemChrBag v3; // [rsp+0h] [rbp-170h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-148h]
  CDBCFile TabFile; // [rsp+30h] [rbp-140h] BYREF
  SpecialTreasureMapRandCfg stu; // [rsp+C0h] [rbp-B0h] BYREF
  MemChrBagVector __x; // [rsp+110h] [rbp-60h] BYREF
  std::string strItems; // [rsp+130h] [rbp-40h] BYREF
  char v9; // [rsp+13Fh] [rbp-31h] BYREF
  std::string strItem; // [rsp+140h] [rbp-30h] BYREF
  char v11; // [rsp+152h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+154h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+158h] [rbp-18h]
  int32_t i; // [rsp+15Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/SpecialTreasureMap.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_SPECIAL_TREASURE_MAP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vGetItems);
        stu.nItemId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&strItems, v1->pString, &v9);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vGetItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v9);
        stu.nRate = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 4);
        std::string::string(&strItem, v2->pString, &v11);
        CItemHelper::parseItemString(&v3, &strItem);
        stu.vShowItem = v3;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v11);
        stu.nGongGaoId = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        std::list<SpecialTreasureMapRandCfg>::push_back(&thisa->m_SpecialTreasureMapRandCfgList, &stu);
        SpecialTreasureMapRandCfg::~SpecialTreasureMapRandCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitMonsterAddAttrTable(CfgData *const this)
{
  std::list<CfgMonsterAddAttr> *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  CfgMonsterAddAttr AddAttrs; // [rsp+A0h] [rbp-50h] BYREF
  AttrAddon stu; // [rsp+C0h] [rbp-30h] BYREF
  int32_t Mid; // [rsp+C8h] [rbp-28h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t j; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MonstAddAttr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_ADD_ATTR failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        Mid = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        memset(&AddAttrs, 0, sizeof(AddAttrs));
        std::vector<AttrAddon>::vector(&AddAttrs.AttrVector);
        AddAttrs.WorldBossLevelMin = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        AddAttrs.WorldBossLevelMax = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        for ( j = 0; j <= 6; ++j )
        {
          stu = 0;
          stu.index = CDBCFile::Search_Posistion(&TabFile, i, 2 * j + 3)->iValue;
          stu.addon = CDBCFile::Search_Posistion(&TabFile, i, 2 * (j + 2))->iValue;
          std::vector<AttrAddon>::push_back(&AddAttrs.AttrVector, &stu);
        }
        v1 = std::map<int,std::list<CfgMonsterAddAttr>>::operator[](&this->m_MonstAddAttrMap, &Mid);
        std::list<CfgMonsterAddAttr>::push_back(v1, &AddAttrs);
        CfgMonsterAddAttr::~CfgMonsterAddAttr(&AddAttrs);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitDaZheQuanTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  DaZheQuan *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  DaZheQuan stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/ItemDiscount.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DA_ZHE_QUAN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.Items);
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.CurrencyType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        stu.CurrencyValues = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        v2 = std::map<int,DaZheQuan>::operator[](&this->m_DaZheQuanMap, &stu.Index);
        DaZheQuan::operator=(v2, &stu);
        DaZheQuan::~DaZheQuan(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::Init360RewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  Wan360Reward *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  Wan360Reward stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/GameLobby.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_360_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.Items);
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        v2 = std::map<int,Wan360Reward>::operator[](&this->m_Wan360RewardMap, &stu.Index);
        Wan360Reward::operator=(v2, &stu);
        Wan360Reward::~Wan360Reward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::Init360RewardTypeTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  int *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-C0h] BYREF
  std::string platform; // [rsp+A0h] [rbp-30h] BYREF
  char v5; // [rsp+AEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t icon; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/GameLobbyType.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_360_REWARD_TYPE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        std::allocator<char>::allocator(&v5);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 0);
        std::string::string(&platform, v1->pString, &v5);
        std::allocator<char>::~allocator(&v5);
        icon = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        v2 = std::map<std::string,int>::operator[](&this->m_Wan360RewardTypeMap, &platform);
        *v2 = icon;
        std::string::~string(&platform);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
int32_t __cdecl CfgData::Get360RewardIcon(CfgData *const this, const std::string *const platform)
{
  return *std::map<std::string,int>::operator[](&this->m_Wan360RewardTypeMap, platform);
}


#####################################
void __cdecl CfgData::InitTotalChongZhiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgTotalChongZhi *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-140h] BYREF
  CfgTotalChongZhi stu; // [rsp+A0h] [rbp-B0h] BYREF
  MemChrEquipBagVector __x; // [rsp+E0h] [rbp-70h] BYREF
  std::string strItems; // [rsp+100h] [rbp-50h] BYREF
  char v8; // [rsp+10Fh] [rbp-41h] BYREF
  std::list<CfgGongGao> v9; // [rsp+110h] [rbp-40h] BYREF
  _BYTE v10[18]; // [rsp+120h] [rbp-30h] BYREF
  char v11; // [rsp+132h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+134h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+138h] [rbp-18h]
  int32_t i; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/ChongZhiHuiKui.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TOTAL_CHONG_ZHI_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; iBaseTableCount - 1 > i; ++i )
      {
        memset(&stu, 0, 52);
        std::vector<CfgEquipItem>::vector(&stu.ItemVector);
        std::list<CfgGongGao>::list(&stu.GongGaoInfo);
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.NeedGold = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&strItems, v1->pString, &v8);
        CfgData::parseEquipItemString(&__x, this, stu.Index, &strItems);
        std::vector<CfgEquipItem>::operator=(&stu.ItemVector, &__x);
        std::vector<CfgEquipItem>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(v10, v2->pString, &v11);
        CfgData::parseGongGaoString(
          (CfgData *const)&v9,
          (int32_t)this,
          (const std::string *const)(unsigned int)stu.Index);
        std::list<CfgGongGao>::operator=(&stu.GongGaoInfo, &v9);
        std::list<CfgGongGao>::~list(&v9);
        std::string::~string(v10);
        std::allocator<char>::~allocator(&v11);
        stu.NewServerday = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        v3 = std::map<signed char,CfgTotalChongZhi>::operator[](&this->m_TotalChongZhiTable, &stu.Index);
        CfgTotalChongZhi::operator=(v3, &stu);
        CfgTotalChongZhi::~CfgTotalChongZhi(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitEveryDayChongZhi(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-130h] BYREF
  CfgEverydayChongZhi stu; // [rsp+A0h] [rbp-A0h] BYREF
  MemChrEquipBagVector __x; // [rsp+D0h] [rbp-70h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-50h] BYREF
  char v7; // [rsp+FFh] [rbp-41h] BYREF
  std::list<CfgGongGao> v8; // [rsp+100h] [rbp-40h] BYREF
  _BYTE v9[18]; // [rsp+110h] [rbp-30h] BYREF
  char v10; // [rsp+122h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+124h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+128h] [rbp-18h]
  int32_t i; // [rsp+12Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MeiRiChongZhi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EVERYDAY_CHONG_ZHI failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<CfgEquipItem>::vector(&stu.ItemVector);
        std::list<CfgGongGao>::list(&stu.GongGaoInfo);
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.Type = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        stu.NeedGold = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v1->pString, &v7);
        CfgData::parseEquipItemString(&__x, this, stu.Index, &strItems);
        std::vector<CfgEquipItem>::operator=(&stu.ItemVector, &__x);
        std::vector<CfgEquipItem>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 4);
        std::string::string(v9, v2->pString, &v10);
        CfgData::parseGongGaoString(
          (CfgData *const)&v8,
          (int32_t)this,
          (const std::string *const)(unsigned int)stu.Index);
        std::list<CfgGongGao>::operator=(&stu.GongGaoInfo, &v8);
        std::list<CfgGongGao>::~list(&v8);
        std::string::~string(v9);
        std::allocator<char>::~allocator(&v10);
        std::list<CfgEverydayChongZhi>::push_back(&this->m_EveryDayChongZhiTable, &stu);
        CfgEverydayChongZhi::~CfgEverydayChongZhi(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitNewServerFavorable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  NewServerFavorable *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  CDBCFile TabFile2; // [rsp+10h] [rbp-220h] BYREF
  CDBCFile TabFile; // [rsp+A0h] [rbp-190h] BYREF
  NewServerFavorable stu; // [rsp+130h] [rbp-100h] BYREF
  MemChrEquipBagVector __x; // [rsp+170h] [rbp-C0h] BYREF
  std::string strItems; // [rsp+190h] [rbp-A0h] BYREF
  char v11; // [rsp+19Fh] [rbp-91h] BYREF
  std::list<CfgGongGao> v12; // [rsp+1A0h] [rbp-90h] BYREF
  _BYTE v13[15]; // [rsp+1B0h] [rbp-80h] BYREF
  char v14; // [rsp+1BFh] [rbp-71h] BYREF
  MemChrEquipBagVector v15; // [rsp+1C0h] [rbp-70h] BYREF
  std::string v16; // [rsp+1E0h] [rbp-50h] BYREF
  char v17; // [rsp+1EFh] [rbp-41h] BYREF
  std::list<CfgGongGao> v18; // [rsp+1F0h] [rbp-40h] BYREF
  _BYTE v19[14]; // [rsp+200h] [rbp-30h] BYREF
  char v20; // [rsp+20Eh] [rbp-22h] BYREF
  bool ret; // [rsp+20Fh] [rbp-21h]
  int32_t iBaseTableCount; // [rsp+210h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+214h] [rbp-1Ch]
  int32_t i; // [rsp+218h] [rbp-18h]
  int32_t i_0; // [rsp+21Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  ret = CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TeHui.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_NEW_SERVER_FAVORABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        NewServerFavorable::NewServerFavorable(&stu);
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        std::allocator<char>::allocator(&v11);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        std::string::string(&strItems, v1->pString, &v11);
        CfgData::parseEquipItemString(&__x, this, stu.Index, &strItems);
        std::vector<CfgEquipItem>::operator=(&stu.ItemVector, &__x);
        std::vector<CfgEquipItem>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v11);
        stu.NeedGold = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(v13, v2->pString, &v14);
        CfgData::parseGongGaoString(
          (CfgData *const)&v12,
          (int32_t)this,
          (const std::string *const)(unsigned int)stu.Index);
        std::list<CfgGongGao>::operator=(&stu.GongGaoInfo, &v12);
        std::list<CfgGongGao>::~list(&v12);
        std::string::~string(v13);
        std::allocator<char>::~allocator(&v14);
        stu.nLimitTime = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        v3 = std::map<signed char,NewServerFavorable>::operator[](&this->m_NewServerFavorable, &stu.Index);
        NewServerFavorable::operator=(v3, &stu);
        NewServerFavorable::~NewServerFavorable(&stu);
      }
      CDBCFile::CDBCFile(&TabFile2, 0);
      ret = CDBCFile::OpenFromTXT(&TabFile2, "./ServerConfig/Tables/SanChong.txt");
      if ( !ret )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_THREE_PET_GIFT failed,please check!!!\n");
      }
      else
      {
        iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile2);
        iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile2);
        if ( iBaseColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount; ++i_0 )
          {
            NewServerFavorable::NewServerFavorable(&stu);
            this->m_ThreePetGift.Index = CDBCFile::Search_Posistion(&TabFile2, i_0, 0)->iValue;
            std::allocator<char>::allocator(&v17);
            v4 = CDBCFile::Search_Posistion(&TabFile2, i_0, 1);
            std::string::string(&v16, v4->pString, &v17);
            CfgData::parseEquipItemString(&v15, this, stu.Index, &v16);
            std::vector<CfgEquipItem>::operator=(&this->m_ThreePetGift.ItemVector, &v15);
            std::vector<CfgEquipItem>::~vector(&v15);
            std::string::~string(&v16);
            std::allocator<char>::~allocator(&v17);
            this->m_ThreePetGift.NeedGold = CDBCFile::Search_Posistion(&TabFile2, i_0, 2)->iValue;
            std::allocator<char>::allocator(&v20);
            v5 = CDBCFile::Search_Posistion(&TabFile2, i_0, 3);
            std::string::string(v19, v5->pString, &v20);
            CfgData::parseGongGaoString(
              (CfgData *const)&v18,
              (int32_t)this,
              (const std::string *const)(unsigned int)stu.Index);
            std::list<CfgGongGao>::operator=(&this->m_ThreePetGift.GongGaoInfo, &v18);
            std::list<CfgGongGao>::~list(&v18);
            std::string::~string(v19);
            std::allocator<char>::~allocator(&v20);
            this->m_ThreePetGift.nLimitTime = CDBCFile::Search_Posistion(&TabFile2, i_0, 4)->iValue;
            NewServerFavorable::~NewServerFavorable(&stu);
          }
        }
      }
      CDBCFile::~CDBCFile(&TabFile2);
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitShouChongLiBao(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgShouChong stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrEquipBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/ShouChong.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SHOU_CHONG_LI_BAO failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgShouChong::CfgShouChong(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nGold = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&strItems, v1->pString, &v6);
        CfgData::parseEquipItemString(&__x, this, 1, &strItems);
        std::vector<CfgEquipItem>::operator=(&stu.vReward, &__x);
        std::vector<CfgEquipItem>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        stu.nBroadcast = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        CfgShouChongTable::Add(&this->m_cfgShouChongTable, &stu);
        CfgShouChong::~CfgShouChong(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitMoHuaHuanYiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgEquipExchange *v2; // rax
  __int64 v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  CfgEquipExchange stu; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItem; // [rsp+C0h] [rbp-30h] BYREF
  char v7; // [rsp+D2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+D4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+D8h] [rbp-18h]
  int32_t i; // [rsp+DCh] [rbp-14h]
  ItemData v12; // 0:kr00_12.12

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MoHuaZhuanYi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MO_HUA_ZHUAN_YI_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        stu.Level = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.Money = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&strItem, v1->pString, &v7);
        v12 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v3) = v12.m_nId;
        BYTE4(v3) = v12.m_nClass;
        *(_QWORD *)&stu.CostItem.m_nId = v3;
        stu.CostItem.m_nCount = v12.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v7);
        v2 = std::map<signed char,CfgEquipExchange>::operator[](&this->m_CfgEquipExchangeMap, &stu.Level);
        *v2 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitZiYuanZhaoHuiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-160h] BYREF
  CfgSearchBack stu; // [rsp+A0h] [rbp-D0h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-80h] BYREF
  std::string strItems; // [rsp+110h] [rbp-60h] BYREF
  char v7; // [rsp+11Fh] [rbp-51h] BYREF
  MemChrBagVector v8; // [rsp+120h] [rbp-50h] BYREF
  std::string v9; // [rsp+140h] [rbp-30h] BYREF
  char v10; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount_Gift; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount_Gift; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ZiYuanZhaoHui.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ZYZH_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount_Gift = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount_Gift = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount_Gift > 0 )
    {
      for ( i = 0; i < iBaseTableCount_Gift; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vItemReward);
        std::vector<MemChrBag>::vector(&stu.vFreeReward);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nTimes = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nSubType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nOpenType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nMinLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nMaxLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nGoldCost = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vFreeReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v9, v2->pString, &v10);
        CItemHelper::parseItemVectorString(&v8, &v9);
        std::vector<MemChrBag>::operator=(&stu.vItemReward, &v8);
        std::vector<MemChrBag>::~vector(&v8);
        std::string::~string(&v9);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        CfgSearchBackTable::AddSearchBack(&this->m_cfgSearchBackTable, &stu);
        CfgSearchBack::~CfgSearchBack(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitPlantEventTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgPlantEventEffect *v2; // rax
  CDBCFile ItemGiftFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgPlantEventEffect Event; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount_Gift; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount_Gift; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&ItemGiftFile, 0);
  if ( !CDBCFile::OpenFromTXT(&ItemGiftFile, "./ServerConfig/Tables/PlantEvent.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PLANT_EVENT_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount_Gift = CDBCFile::GetRecordsNum(&ItemGiftFile);
    iBaseColumnCount_Gift = CDBCFile::GetFieldsNum(&ItemGiftFile);
    if ( iBaseColumnCount_Gift > 0 )
    {
      for ( i = 0; i < iBaseTableCount_Gift; ++i )
      {
        CfgPlantEventEffect::CfgPlantEventEffect(&Event);
        Event.EventId = CDBCFile::Search_Posistion(&ItemGiftFile, i, 0)->iValue;
        Event.EventType = CDBCFile::Search_Posistion(&ItemGiftFile, i, 1)->iValue;
        v1 = CDBCFile::Search_Posistion(&ItemGiftFile, i, 2);
        std::string::operator=(&Event.EventEffect, v1->pString);
        Event.GongGaoId = CDBCFile::Search_Posistion(&ItemGiftFile, i, 3)->iValue;
        v2 = std::map<int,CfgPlantEventEffect>::operator[](&this->m_PlantEventMap, &Event.EventId);
        CfgPlantEventEffect::operator=(v2, &Event);
        CfgPlantEventEffect::~CfgPlantEventEffect(&Event);
      }
    }
  }
  CDBCFile::~CDBCFile(&ItemGiftFile);
}


#####################################
void __cdecl CfgData::InitFunctionOpenTable(CfgData *const this)
{
  FunctionOpenCfg *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-C0h] BYREF
  FunctionOpenCfg stu; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_unlock.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FUNCTION_OPEN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        *(_QWORD *)&stu.Type = 0;
        stu.Level = 0;
        stu.Type = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        stu.TaskId = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        stu.Level = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        v1 = std::map<int,FunctionOpenCfg>::operator[](&this->m_FunctionOpenCfg, &stu.Type);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitVipCardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  VipCardCfg *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-130h] BYREF
  VipCardCfg VipCard; // [rsp+A0h] [rbp-A0h] BYREF
  std::list<AddAttribute> __x; // [rsp+E0h] [rbp-60h] BYREF
  _BYTE v6[15]; // [rsp+F0h] [rbp-50h] BYREF
  char v7; // [rsp+FFh] [rbp-41h] BYREF
  int32_t v8[5]; // [rsp+100h] [rbp-40h] BYREF
  char v9; // [rsp+117h] [rbp-29h] BYREF
  int __k; // [rsp+118h] [rbp-28h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/Privilege.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VIP_CARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&VipCard, 0, 52);
        std::list<AddAttribute>::list(&VipCard.AddAttr);
        VipCard.VipCardId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        VipCard.AddVipTime = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        VipCard.NeedGold = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        std::string::string(v6, "./ServerConfig/Tables/Privilege.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&VipCard.AddAttr, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v8);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(v6);
        std::allocator<char>::~allocator(&v7);
        VipCard.VipLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        VipCard.ReNeedGold = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        VipCard.Money = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        VipCard.TianShuJinHua = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        VipCard.WeiWang = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        __k = VipCard.VipCardId;
        v2 = std::map<int,VipCardCfg>::operator[](&this->m_VipCardTable, &__k);
        VipCardCfg::operator=(v2, &VipCard);
        VipCardCfg::~VipCardCfg(&VipCard);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitOffLineExpTable(CfgData *const this)
{
  CfgOffLineExp *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgOffLineExp reward; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/OfflineExp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_OFF_LINE_EXP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&reward, 0, sizeof(reward));
        reward.Level = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        reward.MinuteExp = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        reward.TwoTimes = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        reward.ThreeTimes = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        reward.BaseExp = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        v1 = std::map<int,CfgOffLineExp>::operator[](&this->m_OffLineExpTable, &reward.Level);
        *v1 = reward;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitWeekOnlineReward(CfgData *const this)
{
  CfgWeekOnlineReward *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgWeekOnlineReward reward; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WeekOnlineReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WEEK_ONLINE_REWARD failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        *(_QWORD *)&reward.Week = 0;
        reward.UpperLimit = 0;
        reward.Week = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        reward.Cash = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        reward.UpperLimit = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        v1 = std::map<int,CfgWeekOnlineReward>::operator[](&this->m_WeekOnlineReward, &reward.Week);
        *v1 = reward;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitLevelGift(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgLevelGift *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  CfgLevelGift reward; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+EBh] [rbp-25h] BYREF
  int __k; // [rsp+ECh] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_level_gift.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LEVEL_GIFT failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&reward, 0, sizeof(reward));
        std::vector<MemChrBag>::vector(&reward.ItemVector);
        reward.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        reward.Level = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&reward.ItemVector, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        __k = reward.Index;
        v2 = std::map<int,CfgLevelGift>::operator[](&this->m_LevelGift, &__k);
        CfgLevelGift::operator=(v2, &reward);
        CfgLevelGift::~CfgLevelGift(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitSevenLoginReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgSevenLoginRewrad *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  CfgSevenLoginRewrad reward; // [rsp+A0h] [rbp-70h] BYREF
  MemChrEquipBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_seven_login_reward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SEVEN_LOGIN_REWARD failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&reward, 0, sizeof(reward));
        std::vector<CfgEquipItem>::vector(&reward.ItemVector);
        reward.Day = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        std::string::string(&strItems, v1->pString, &v7);
        CfgData::parseEquipItemString(&__x, this, reward.Day, &strItems);
        std::vector<CfgEquipItem>::operator=(&reward.ItemVector, &__x);
        std::vector<CfgEquipItem>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        v2 = std::map<signed char,CfgSevenLoginRewrad>::operator[](&this->m_SevenLoginReward, &reward.Day);
        CfgSevenLoginRewrad::operator=(v2, &reward);
        CfgSevenLoginRewrad::~CfgSevenLoginRewrad(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitOnLimeReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgOnlineReward *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  CfgOnlineReward reward; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_online_reward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ONLINE_REWARD failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&reward, 0, sizeof(reward));
        std::vector<MemChrBag>::vector(&reward.ItemVector);
        reward.Id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        reward.NeedTime = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&reward.ItemVector, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        v2 = std::map<signed char,CfgOnlineReward>::operator[](&this->m_OnLineReward, &reward.Id);
        CfgOnlineReward::operator=(v2, &reward);
        CfgOnlineReward::~CfgOnlineReward(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::fetchSignReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgSignReward *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  CfgSignReward reward; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+F1h] [rbp-1Fh] BYREF
  char __k; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_sign_reward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SIGIN_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&reward, 0, sizeof(reward));
        std::vector<MemChrBag>::vector(&reward.ItemVector);
        reward.count = (char)CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&reward.ItemVector, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        __k = reward.count;
        v2 = std::map<signed char,CfgSignReward>::operator[](&this->m_signReward, &__k);
        CfgSignReward::operator=(v2, &reward);
        CfgSignReward::~CfgSignReward(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitQQZoneRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgQQGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/QQZone.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_QQZONE_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgQQGift::CfgQQGift(&gift);
        gift.nIndex = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        gift.nType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        gift.nCondition = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgTencentTable::AddQQZoneGift(&this->m_cfgTencentTable, &gift);
        CfgQQGift::~CfgQQGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitQQGameRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgQQGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/QQGameDaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_QQGAME_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgQQGift::CfgQQGift(&gift);
        gift.nIndex = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        gift.nType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        gift.nCondition = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgTencentTable::AddQQGameGift(&this->m_cfgTencentTable, &gift);
        CfgQQGift::~CfgQQGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitYellowRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  MemChrBagVector vReward; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+C0h] [rbp-30h] BYREF
  char v5; // [rsp+CAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+CCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+D0h] [rbp-20h]
  int32_t i; // [rsp+D4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+D8h] [rbp-18h]
  int32_t nId; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/YellowReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_YELLOW_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v5);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v5);
        CItemHelper::parseItemVectorString(&vReward, &strItems);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v5);
        ++nIndex;
        CfgTencentTable::SetYellowNewerGift(&this->m_cfgTencentTable, &vReward);
        std::vector<MemChrBag>::~vector(&vReward);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitTencentSevenDayLoginTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  CfgTencentSevenDayLogin stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TencentSevenDayLogin.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TENCENT_SEVEN_DAY_LOGIN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentSevenDayLogin::CfgTencentSevenDayLogin(&stu);
        stu.nDays = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgTencentTable::AddSevenDayLogin(&this->m_cfgTencentTable, &stu);
        CfgTencentSevenDayLogin::~CfgTencentSevenDayLogin(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitYellowDailyRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-1A0h] BYREF
  CfgTencentGift year; // [rsp+A0h] [rbp-110h] BYREF
  CfgTencentGift daily; // [rsp+E0h] [rbp-D0h] BYREF
  MemChrBagVector __x; // [rsp+120h] [rbp-90h] BYREF
  std::string strItems; // [rsp+140h] [rbp-70h] BYREF
  char v8; // [rsp+14Fh] [rbp-61h] BYREF
  MemChrBagVector v9; // [rsp+150h] [rbp-60h] BYREF
  std::string v10; // [rsp+170h] [rbp-40h] BYREF
  char v11; // [rsp+186h] [rbp-2Ah] BYREF
  int32_t iBaseTableCount; // [rsp+188h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+18Ch] [rbp-24h]
  int32_t i; // [rsp+190h] [rbp-20h]
  int32_t nIndex; // [rsp+194h] [rbp-1Ch]
  int32_t nId; // [rsp+198h] [rbp-18h]
  int32_t nLevel; // [rsp+19Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/YellowEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_DAILY_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&daily);
        CfgTencentGift::CfgTencentGift(&year);
        nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v8);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&daily.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v10, v2->pString, &v11);
        CItemHelper::parseItemVectorString(&v9, &v10);
        std::vector<MemChrBag>::operator=(&year.vRewards, &v9);
        std::vector<MemChrBag>::~vector(&v9);
        std::string::~string(&v10);
        std::allocator<char>::~allocator(&v11);
        ++nIndex;
        daily.nLevel = nLevel;
        year.nLevel = nLevel;
        CfgTencentTable::AddYellowDailyGift(&this->m_cfgTencentTable, &daily);
        CfgTencentTable::AddYellowYearGift(&this->m_cfgTencentTable, &year);
        CfgTencentGift::~CfgTencentGift(&year);
        CfgTencentGift::~CfgTencentGift(&daily);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitYellowLevelRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-150h] BYREF
  CfgTencentGift gift; // [rsp+A0h] [rbp-C0h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-80h] BYREF
  std::string strItems; // [rsp+100h] [rbp-60h] BYREF
  char v7; // [rsp+10Fh] [rbp-51h] BYREF
  MemChrBagVector v8; // [rsp+110h] [rbp-50h] BYREF
  std::string v9; // [rsp+130h] [rbp-30h] BYREF
  char v10; // [rsp+13Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+13Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+140h] [rbp-20h]
  int32_t i; // [rsp+144h] [rbp-1Ch]
  int32_t nIndex; // [rsp+148h] [rbp-18h]
  int32_t nId; // [rsp+14Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/YellowLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&gift);
        nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        gift.nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v9, v2->pString, &v10);
        CItemHelper::parseItemVectorString(&v8, &v9);
        std::vector<MemChrBag>::operator=(&gift.vVipRewards, &v8);
        std::vector<MemChrBag>::~vector(&v8);
        std::string::~string(&v9);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        CfgTencentTable::AddYellowLevelGift(&this->m_cfgTencentTable, nId, &gift);
        CfgTencentGift::~CfgTencentGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitBlueRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  MemChrBagVector vReward; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+C0h] [rbp-30h] BYREF
  char v5; // [rsp+CAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+CCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+D0h] [rbp-20h]
  int32_t i; // [rsp+D4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+D8h] [rbp-18h]
  int32_t nId; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/BlueReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BLUE_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v5);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v5);
        CItemHelper::parseItemVectorString(&vReward, &strItems);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v5);
        ++nIndex;
        CfgTencentTable::SetBlueNewerGift(&this->m_cfgTencentTable, &vReward);
        std::vector<MemChrBag>::~vector(&vReward);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitBlueDailyRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-210h] BYREF
  CfgTencentGift high; // [rsp+A0h] [rbp-180h] BYREF
  CfgTencentGift year; // [rsp+E0h] [rbp-140h] BYREF
  CfgTencentGift daily; // [rsp+120h] [rbp-100h] BYREF
  MemChrBagVector __x; // [rsp+160h] [rbp-C0h] BYREF
  std::string strItems; // [rsp+180h] [rbp-A0h] BYREF
  char v10; // [rsp+18Fh] [rbp-91h] BYREF
  MemChrBagVector v11; // [rsp+190h] [rbp-90h] BYREF
  std::string v12; // [rsp+1B0h] [rbp-70h] BYREF
  char v13; // [rsp+1BFh] [rbp-61h] BYREF
  MemChrBagVector v14; // [rsp+1C0h] [rbp-60h] BYREF
  std::string v15; // [rsp+1E0h] [rbp-40h] BYREF
  char v16; // [rsp+1F6h] [rbp-2Ah] BYREF
  int32_t iBaseTableCount; // [rsp+1F8h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+1FCh] [rbp-24h]
  int32_t i; // [rsp+200h] [rbp-20h]
  int32_t nIndex; // [rsp+204h] [rbp-1Ch]
  int32_t nId; // [rsp+208h] [rbp-18h]
  int32_t nLevel; // [rsp+20Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/BlueEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BLUE_DAILY_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&daily);
        CfgTencentGift::CfgTencentGift(&year);
        CfgTencentGift::CfgTencentGift(&high);
        nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v10);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&daily.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v12, v2->pString, &v13);
        CItemHelper::parseItemVectorString(&v11, &v12);
        std::vector<MemChrBag>::operator=(&year.vRewards, &v11);
        std::vector<MemChrBag>::~vector(&v11);
        std::string::~string(&v12);
        std::allocator<char>::~allocator(&v13);
        ++nIndex;
        std::allocator<char>::allocator(&v16);
        v3 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v15, v3->pString, &v16);
        CItemHelper::parseItemVectorString(&v14, &v15);
        std::vector<MemChrBag>::operator=(&high.vRewards, &v14);
        std::vector<MemChrBag>::~vector(&v14);
        std::string::~string(&v15);
        std::allocator<char>::~allocator(&v16);
        ++nIndex;
        daily.nLevel = nLevel;
        year.nLevel = nLevel;
        high.nLevel = nLevel;
        CfgTencentTable::AddBlueDailyGift(&this->m_cfgTencentTable, &daily);
        CfgTencentTable::AddBlueYearGift(&this->m_cfgTencentTable, &year);
        CfgTencentTable::AddBlueHighGift(&this->m_cfgTencentTable, &high);
        CfgTencentGift::~CfgTencentGift(&high);
        CfgTencentGift::~CfgTencentGift(&year);
        CfgTencentGift::~CfgTencentGift(&daily);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitBlueLevelRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-120h] BYREF
  CfgTencentGift gift; // [rsp+A0h] [rbp-90h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v6; // [rsp+10Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+10Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+110h] [rbp-20h]
  int32_t i; // [rsp+114h] [rbp-1Ch]
  int32_t nIndex; // [rsp+118h] [rbp-18h]
  int32_t nId; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/BlueLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BLUE_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&gift);
        nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        gift.nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgTencentTable::AddBlueLevelGift(&this->m_cfgTencentTable, nId, &gift);
        CfgTencentGift::~CfgTencentGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitTGPRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgTGPGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TGPReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TGP_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&gift, 0, sizeof(gift));
        std::string::string(&gift.strPF);
        std::vector<MemChrBag>::vector(&gift.vReward);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&gift, v1->pString);
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        CfgTencentTable::AddTGPNewerGift(&this->m_cfgTencentTable, &gift);
        CfgTGPGift::~CfgTGPGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitTGPDailyRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgTGPGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TGPEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TGP_DAILY_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&gift, 0, sizeof(gift));
        std::string::string(&gift.strPF);
        std::vector<MemChrBag>::vector(&gift.vReward);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&gift, v1->pString);
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        CfgTencentTable::AddTGPDailyGift(&this->m_cfgTencentTable, &gift);
        CfgTGPGift::~CfgTGPGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitTGPLevelRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgTGPGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TGPLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TGP_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&gift, 0, sizeof(gift));
        std::string::string(&gift.strPF);
        std::vector<MemChrBag>::vector(&gift.vReward);
        gift.nIndex = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&gift, v1->pString);
        gift.nLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        CfgTencentTable::AddTGPLevelGift(&this->m_cfgTencentTable, &gift);
        CfgTGPGift::~CfgTGPGift(&gift);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitFamilyDungeonTable(CfgData *const this)
{
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  CfgFamilyDungeon stu; // [rsp+A0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/FamilyDungeon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_DUNGEON_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.nHard = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nDungeonId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nFamilyLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nCostMoney = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 7;
        stu.nBaoKuFuBen = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nNpcId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.X = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.Y = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nTime = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        CfgFamilyDungeonTable::AddDungeon(&this->m_cfgFamilyDungeonTable, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::fetchActivity(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  __int64 v6; // rax
  int *v7; // rbx
  std::string *v8; // rax
  const char *v9; // rax
  __int64 v10; // rax
  int *v11; // rbx
  std::string *v12; // rax
  const char *v13; // rax
  __int64 v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  size_t v17; // rbx
  __int64 v18; // rax
  std::string *v19; // rax
  const char *v20; // rax
  std::string *v21; // rax
  __int64 v22; // rax
  std::string *v23; // rax
  const char *v24; // rax
  std::string *v25; // rax
  const char *v26; // rax
  std::string *v27; // rax
  __int64 v28; // rax
  std::string *v29; // rax
  const char *v30; // rax
  std::string *v31; // rax
  __int64 v32; // rax
  std::string *v33; // rax
  const char *v34; // rax
  std::string *v35; // rax
  const char *v36; // rax
  size_t v37; // rbx
  CfgActivity *v38; // rax
  const CDBCFile::FIELD *v39; // rax
  const CDBCFile::FIELD *v40; // rax
  __int64 v41; // rax
  std::string *v42; // rax
  const char *v43; // rax
  std::map<int,std::list<CfgMapEvent>> *v44; // rax
  std::list<CfgMapEvent> *v45; // rax
  const CDBCFile::FIELD *v46; // rax
  const CDBCFile::FIELD *v47; // rax
  std::string *v48; // rax
  std::string *v49; // rax
  const char *v50; // rax
  int32_t v51; // ebx
  std::string *v52; // rax
  const char *v53; // rax
  int32_t v54; // eax
  size_t v55; // rbx
  std::string *v56; // rax
  std::string *v57; // rax
  const char *v58; // rax
  int32_t v59; // ebx
  std::string *v60; // rax
  const char *v61; // rax
  int32_t v62; // eax
  size_t v63; // rbx
  CfgActivityMonster *v64; // rax
  const CDBCFile::FIELD *v65; // rax
  __int64 v66; // rax
  std::string *v67; // rax
  const char *v68; // rax
  CfgActivityNpc *v69; // rax
  const CDBCFile::FIELD *v70; // rax
  CfgActivityPlant *v71; // rax
  CfgActivityDrop *v72; // rax
  CfgActivityTrap *v73; // rax
  CDBCFile ActivityTrapFile; // [rsp+10h] [rbp-A00h] BYREF
  std::vector<int> v75; // [rsp+A0h] [rbp-970h] BYREF
  int v76; // [rsp+B8h] [rbp-958h]
  std::vector<int> v77; // [rsp+C0h] [rbp-950h] BYREF
  std::vector<int> v78; // [rsp+D8h] [rbp-938h] BYREF
  int iValue; // [rsp+F0h] [rbp-920h]
  int v80; // [rsp+F4h] [rbp-91Ch]
  int v81; // [rsp+F8h] [rbp-918h]
  CDBCFile ActivityDropFile; // [rsp+100h] [rbp-910h] BYREF
  CDBCFile ActivityPlantFile; // [rsp+190h] [rbp-880h] BYREF
  CDBCFile ActivityNpcFile; // [rsp+220h] [rbp-7F0h] BYREF
  CDBCFile ActivityMonsterFile; // [rsp+2B0h] [rbp-760h] BYREF
  CDBCFile ActivityEventFile; // [rsp+340h] [rbp-6D0h] BYREF
  CDBCFile ActivityFile; // [rsp+3D0h] [rbp-640h] BYREF
  CfgActivityPlant plant; // [rsp+460h] [rbp-5B0h] BYREF
  int v89; // [rsp+498h] [rbp-578h]
  std::vector<Position> v90; // [rsp+4A0h] [rbp-570h] BYREF
  int v91; // [rsp+4B8h] [rbp-558h]
  bool v92; // [rsp+4BCh] [rbp-554h]
  CfgActivityTrap trap; // [rsp+4C0h] [rbp-550h] BYREF
  CfgActivityDrop drop; // [rsp+4D0h] [rbp-540h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+4F0h] [rbp-520h] BYREF
  StringVector strRegions; // [rsp+500h] [rbp-510h] BYREF
  std::string regionId; // [rsp+520h] [rbp-4F0h] BYREF
  StringVector vPos_0; // [rsp+530h] [rbp-4E0h] BYREF
  StringVector vRandPos; // [rsp+550h] [rbp-4C0h] BYREF
  StringVector vPos; // [rsp+570h] [rbp-4A0h] BYREF
  StringVector vRoad; // [rsp+590h] [rbp-480h] BYREF
  std::string randpos; // [rsp+5B0h] [rbp-460h] BYREF
  std::string road; // [rsp+5C0h] [rbp-450h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+5D0h] [rbp-440h] BYREF
  StringVector strParams_2; // [rsp+5E0h] [rbp-430h] BYREF
  std::string triggerParam; // [rsp+600h] [rbp-410h] BYREF
  int32_t tstart; // [rsp+60Ch] [rbp-404h] BYREF
  StringVector stritemParams_0; // [rsp+610h] [rbp-400h] BYREF
  StringVector stritemParams; // [rsp+630h] [rbp-3E0h] BYREF
  StringVector vStartHour; // [rsp+650h] [rbp-3C0h] BYREF
  StringVector strParams_1; // [rsp+670h] [rbp-3A0h] BYREF
  StringVector strParams_0; // [rsp+690h] [rbp-380h] BYREF
  StringVector strParams; // [rsp+6B0h] [rbp-360h] BYREF
  StringVector strMaps; // [rsp+6D0h] [rbp-340h] BYREF
  std::string daily; // [rsp+6F0h] [rbp-320h] BYREF
  std::string awards; // [rsp+700h] [rbp-310h] BYREF
  std::string position; // [rsp+710h] [rbp-300h] BYREF
  std::string start_hour; // [rsp+720h] [rbp-2F0h] BYREF
  std::string maps; // [rsp+730h] [rbp-2E0h] BYREF
  char v120; // [rsp+747h] [rbp-2C9h] BYREF
  char v121; // [rsp+748h] [rbp-2C8h] BYREF
  char v122; // [rsp+749h] [rbp-2C7h] BYREF
  char v123; // [rsp+74Ah] [rbp-2C6h] BYREF
  char v124; // [rsp+74Bh] [rbp-2C5h] BYREF
  int __x; // [rsp+74Ch] [rbp-2C4h] BYREF
  std::string delims; // [rsp+750h] [rbp-2C0h] BYREF
  char v127; // [rsp+75Fh] [rbp-2B1h] BYREF
  std::string str; // [rsp+760h] [rbp-2B0h] BYREF
  char v129; // [rsp+76Fh] [rbp-2A1h] BYREF
  std::string v130; // [rsp+770h] [rbp-2A0h] BYREF
  char v131; // [rsp+77Fh] [rbp-291h] BYREF
  std::string v132; // [rsp+780h] [rbp-290h] BYREF
  char v133; // [rsp+78Fh] [rbp-281h] BYREF
  std::string v134; // [rsp+790h] [rbp-280h] BYREF
  char v135; // [rsp+79Fh] [rbp-271h] BYREF
  std::string v136; // [rsp+7A0h] [rbp-270h] BYREF
  char v137; // [rsp+7ABh] [rbp-265h] BYREF
  int v138; // [rsp+7ACh] [rbp-264h] BYREF
  std::string v139; // [rsp+7B0h] [rbp-260h] BYREF
  char v140; // [rsp+7BFh] [rbp-251h] BYREF
  std::string v141; // [rsp+7C0h] [rbp-250h] BYREF
  char v142; // [rsp+7CFh] [rbp-241h] BYREF
  std::string v143; // [rsp+7D0h] [rbp-240h] BYREF
  char v144; // [rsp+7DFh] [rbp-231h] BYREF
  std::string v145; // [rsp+7E0h] [rbp-230h] BYREF
  char v146; // [rsp+7EBh] [rbp-225h] BYREF
  int v147; // [rsp+7ECh] [rbp-224h] BYREF
  std::string v148; // [rsp+7F0h] [rbp-220h] BYREF
  char v149; // [rsp+7FFh] [rbp-211h] BYREF
  std::string v150; // [rsp+800h] [rbp-210h] BYREF
  char v151; // [rsp+80Bh] [rbp-205h] BYREF
  int v152; // [rsp+80Ch] [rbp-204h] BYREF
  StringVector v153; // [rsp+810h] [rbp-200h] BYREF
  std::string v154; // [rsp+830h] [rbp-1E0h] BYREF
  char v155; // [rsp+83Fh] [rbp-1D1h] BYREF
  std::string v156; // [rsp+840h] [rbp-1D0h] BYREF
  char v157; // [rsp+84Bh] [rbp-1C5h] BYREF
  int v158; // [rsp+84Ch] [rbp-1C4h] BYREF
  std::string v159; // [rsp+850h] [rbp-1C0h] BYREF
  char v160; // [rsp+85Eh] [rbp-1B2h] BYREF
  char v161; // [rsp+85Fh] [rbp-1B1h] BYREF
  std::string v162; // [rsp+860h] [rbp-1B0h] BYREF
  char v163; // [rsp+86Fh] [rbp-1A1h] BYREF
  std::string v164; // [rsp+870h] [rbp-1A0h] BYREF
  char v165; // [rsp+87Fh] [rbp-191h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+880h] [rbp-190h] BYREF
  int v167; // [rsp+888h] [rbp-188h] BYREF
  char v168; // [rsp+88Eh] [rbp-182h] BYREF
  char v169; // [rsp+88Fh] [rbp-181h] BYREF
  std::string v170; // [rsp+890h] [rbp-180h] BYREF
  char v171; // [rsp+89Fh] [rbp-171h] BYREF
  std::string v172; // [rsp+8A0h] [rbp-170h] BYREF
  char v173; // [rsp+8AFh] [rbp-161h] BYREF
  Position v174; // [rsp+8B0h] [rbp-160h] BYREF
  std::string v175; // [rsp+8C0h] [rbp-150h] BYREF
  char v176; // [rsp+8CFh] [rbp-141h] BYREF
  std::string v177; // [rsp+8D0h] [rbp-140h] BYREF
  char v178; // [rsp+8DFh] [rbp-131h] BYREF
  Position v179; // [rsp+8E0h] [rbp-130h] BYREF
  char v180; // [rsp+8EFh] [rbp-121h] BYREF
  std::string v181; // [rsp+8F0h] [rbp-120h] BYREF
  char v182; // [rsp+8FFh] [rbp-111h] BYREF
  std::string v183; // [rsp+900h] [rbp-110h] BYREF
  char v184; // [rsp+90Fh] [rbp-101h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v185; // [rsp+910h] [rbp-100h] BYREF
  int v186; // [rsp+91Ch] [rbp-F4h] BYREF
  std::vector<Position> v187; // [rsp+920h] [rbp-F0h] BYREF
  std::string strPos; // [rsp+940h] [rbp-D0h] BYREF
  char v189; // [rsp+956h] [rbp-BAh] BYREF
  int32_t iBaseTableCount; // [rsp+958h] [rbp-B8h]
  int32_t iBaseColumnCount; // [rsp+95Ch] [rbp-B4h]
  int32_t i; // [rsp+960h] [rbp-B0h]
  int32_t weekday; // [rsp+964h] [rbp-ACh]
  int16_t nsize; // [rsp+96Ah] [rbp-A6h]
  int32_t j; // [rsp+96Ch] [rbp-A4h]
  int16_t nsize_0; // [rsp+972h] [rbp-9Eh]
  int32_t j_0; // [rsp+974h] [rbp-9Ch]
  uint32_t j_1; // [rsp+978h] [rbp-98h]
  int32_t nlenth; // [rsp+97Ch] [rbp-94h]
  int32_t j_2; // [rsp+980h] [rbp-90h]
  int32_t nlenth_0; // [rsp+984h] [rbp-8Ch]
  int32_t j_3; // [rsp+988h] [rbp-88h]
  int32_t k; // [rsp+98Ch] [rbp-84h]
  uint32_t j_4; // [rsp+990h] [rbp-80h]
  int32_t iBaseTableCount_Event; // [rsp+998h] [rbp-78h]
  int32_t iBaseColumnCount_Event; // [rsp+99Ch] [rbp-74h]
  int32_t iBaseTableCount_Monster; // [rsp+9A4h] [rbp-6Ch]
  int32_t iBaseColumnCount_Monster; // [rsp+9A8h] [rbp-68h]
  int32_t iBaseTableCount_Npc; // [rsp+9B0h] [rbp-60h]
  int32_t iBaseColumnCount_Npc; // [rsp+9B4h] [rbp-5Ch]
  int32_t iBaseTableCount_Plant; // [rsp+9BCh] [rbp-54h]
  int32_t iBaseColumnCount_Plant; // [rsp+9C0h] [rbp-50h]
  int32_t iBaseTableCount_Drop; // [rsp+9C8h] [rbp-48h]
  int32_t iBaseColumnCount_Drop; // [rsp+9CCh] [rbp-44h]
  int32_t iBaseTableCount_Trap; // [rsp+9D4h] [rbp-3Ch]
  int32_t iBaseColumnCount_Trap; // [rsp+9D8h] [rbp-38h]
  int32_t i_0; // [rsp+9DCh] [rbp-34h]
  int32_t nIndex; // [rsp+9E0h] [rbp-30h]
  int32_t i_1; // [rsp+9E4h] [rbp-2Ch]
  uint32_t j_5; // [rsp+9E8h] [rbp-28h]
  uint32_t j_6; // [rsp+9ECh] [rbp-24h]
  int32_t i_2; // [rsp+9F0h] [rbp-20h]
  int32_t i_3; // [rsp+9F4h] [rbp-1Ch]
  int32_t i_4; // [rsp+9F8h] [rbp-18h]
  int32_t i_5; // [rsp+9FCh] [rbp-14h]

  CDBCFile::CDBCFile(&ActivityFile, 0);
  if ( !CDBCFile::OpenFromTXT(&ActivityFile, "./ServerConfig/Tables/cfg_activity.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_activity.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&ActivityFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&ActivityFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgActivity::CfgActivity((CfgActivity *const)&ActivityTrapFile);
        LODWORD(ActivityTrapFile._vptr_CDBCFile) = CDBCFile::Search_Posistion(&ActivityFile, i, 0)->iValue;
        HIDWORD(ActivityTrapFile.m_pStringBuf) = CDBCFile::Search_Posistion(&ActivityFile, i, 5)->iValue;
        weekday = CDBCFile::Search_Posistion(&ActivityFile, i, 9)->iValue;
        LODWORD(ActivityTrapFile.m_theType._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(&ActivityFile, i, 10)->iValue;
        HIDWORD(ActivityTrapFile.m_theType._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(&ActivityFile, i, 11)->iValue;
        ActivityTrapFile.m_nRecordsNum = CDBCFile::Search_Posistion(&ActivityFile, i, 12)->iValue;
        std::allocator<char>::allocator(&v120);
        v1 = CDBCFile::Search_Posistion(&ActivityFile, i, 13);
        std::string::string(&maps, v1->pString, &v120);
        std::allocator<char>::~allocator(&v120);
        std::allocator<char>::allocator(&v121);
        v2 = CDBCFile::Search_Posistion(&ActivityFile, i, 14);
        std::string::string(&start_hour, v2->pString, &v121);
        std::allocator<char>::~allocator(&v121);
        LODWORD(ActivityTrapFile.m_pStringBuf) = CDBCFile::Search_Posistion(&ActivityFile, i, 15)->iValue;
        std::allocator<char>::allocator(&v122);
        v3 = CDBCFile::Search_Posistion(&ActivityFile, i, 17);
        std::string::string(&position, v3->pString, &v122);
        std::allocator<char>::~allocator(&v122);
        std::allocator<char>::allocator(&v123);
        v4 = CDBCFile::Search_Posistion(&ActivityFile, i, 18);
        std::string::string(&awards, v4->pString, &v123);
        std::allocator<char>::~allocator(&v123);
        WORD2(ActivityTrapFile._vptr_CDBCFile) = CDBCFile::Search_Posistion(&ActivityFile, i, 21)->iValue;
        iValue = CDBCFile::Search_Posistion(&ActivityFile, i, 23)->iValue;
        v80 = CDBCFile::Search_Posistion(&ActivityFile, i, 24)->iValue;
        v81 = CDBCFile::Search_Posistion(&ActivityFile, i, 25)->iValue;
        std::allocator<char>::allocator(&v124);
        v5 = CDBCFile::Search_Posistion(&ActivityFile, i, 26);
        std::string::string(&daily, v5->pString, &v124);
        std::allocator<char>::~allocator(&v124);
        LOBYTE(ActivityTrapFile.m_nStringBufSize) = CDBCFile::Search_Posistion(&ActivityFile, i, 30)->iValue;
        while ( weekday > 0 )
        {
          __x = weekday % 10;
          std::vector<int>::push_back((std::vector<int> *const)&ActivityTrapFile.m_ID, &__x);
          weekday /= 10;
        }
        if ( *(_BYTE *)std::string::c_str(&awards) )
        {
          std::allocator<char>::allocator(&v127);
          std::string::string(&delims, ":", &v127);
          std::allocator<char>::allocator(&v129);
          v6 = std::string::c_str(&awards);
          std::string::string(&str, v6, &v129);
          Answer::StringUtility::split(&strParams, &str, &delims, 0);
          std::string::~string(&str);
          std::allocator<char>::~allocator(&v129);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v127);
          nsize = std::vector<std::string>::size(&strParams);
          switch ( WORD2(ActivityTrapFile._vptr_CDBCFile) )
          {
            case 1:
              nsize = 8;
              break;
            case 6:
              nsize = 1;
              break;
            case 8:
              nsize = 2;
              break;
            case 0xB:
              nsize = 6;
              break;
            case 0xC:
              nsize = 5;
              break;
            default:
              break;
          }
          std::vector<int>::resize(&v77, nsize, 0);
          for ( j = 0; nsize > j; ++j )
          {
            v7 = std::vector<int>::operator[](&v77, j);
            v8 = std::vector<std::string>::operator[](&strParams, j);
            v9 = (const char *)std::string::c_str(v8);
            *v7 = atoi(v9);
          }
          std::vector<std::string>::~vector(&strParams);
        }
        if ( *(_BYTE *)std::string::c_str(&daily) )
        {
          std::allocator<char>::allocator(&v131);
          std::string::string(&v130, ":", &v131);
          std::allocator<char>::allocator(&v133);
          v10 = std::string::c_str(&daily);
          std::string::string(&v132, v10, &v133);
          Answer::StringUtility::split(&strParams_0, &v132, &v130, 0);
          std::string::~string(&v132);
          std::allocator<char>::~allocator(&v133);
          std::string::~string(&v130);
          std::allocator<char>::~allocator(&v131);
          nsize_0 = std::vector<std::string>::size(&strParams_0);
          std::vector<int>::resize(&v78, nsize_0, 0);
          for ( j_0 = 0; nsize_0 > j_0; ++j_0 )
          {
            v11 = std::vector<int>::operator[](&v78, j_0);
            v12 = std::vector<std::string>::operator[](&strParams_0, j_0);
            v13 = (const char *)std::string::c_str(v12);
            *v11 = atoi(v13);
          }
          std::vector<std::string>::~vector(&strParams_0);
        }
        std::allocator<char>::allocator(&v135);
        std::string::string(&v134, ":", &v135);
        std::allocator<char>::allocator(&v137);
        v14 = std::string::c_str(&maps);
        std::string::string(&v136, v14, &v137);
        Answer::StringUtility::split(&strMaps, &v136, &v134, 0);
        std::string::~string(&v136);
        std::allocator<char>::~allocator(&v137);
        std::string::~string(&v134);
        std::allocator<char>::~allocator(&v135);
        if ( std::vector<std::string>::size(&strMaps) )
        {
          for ( j_1 = 0; ; ++j_1 )
          {
            v17 = j_1;
            if ( v17 >= std::vector<std::string>::size(&strMaps) )
              break;
            v15 = std::vector<std::string>::operator[](&strMaps, j_1);
            v16 = (const char *)std::string::c_str(v15);
            v138 = atoi(v16);
            std::vector<int>::push_back((std::vector<int> *const)&ActivityTrapFile.m_hashIndex, &v138);
          }
        }
        std::allocator<char>::allocator(&v140);
        std::string::string(&v139, ":", &v140);
        std::allocator<char>::allocator(&v142);
        v18 = std::string::c_str(&position);
        std::string::string(&v141, v18, &v142);
        Answer::StringUtility::split(&strParams_1, &v141, &v139, 0);
        std::string::~string(&v141);
        std::allocator<char>::~allocator(&v142);
        std::string::~string(&v139);
        std::allocator<char>::~allocator(&v140);
        if ( std::vector<std::string>::size(&strParams_1) == 2 )
        {
          v19 = std::vector<std::string>::operator[](&strParams_1, 0);
          v20 = (const char *)std::string::c_str(v19);
          LODWORD(ActivityTrapFile.m_hashIndex._M_ht._M_buckets._M_impl._M_end_of_storage) = atoi(v20);
          std::allocator<char>::allocator(&v144);
          std::string::string(&v143, "|", &v144);
          std::allocator<char>::allocator(&v146);
          v21 = std::vector<std::string>::operator[](&strParams_1, 1u);
          v22 = std::string::c_str(v21);
          std::string::string(&v145, v22, &v146);
          Answer::StringUtility::split(&stritemParams, &v145, &v143, 0);
          std::string::~string(&v145);
          std::allocator<char>::~allocator(&v146);
          std::string::~string(&v143);
          std::allocator<char>::~allocator(&v144);
          nlenth = std::vector<std::string>::size(&stritemParams);
          for ( j_2 = 0; j_2 < nlenth; ++j_2 )
          {
            v23 = std::vector<std::string>::operator[](&stritemParams, j_2);
            v24 = (const char *)std::string::c_str(v23);
            v147 = atoi(v24);
            std::vector<int>::push_back(
              (std::vector<int> *const)&ActivityTrapFile.m_hashIndex._M_ht._M_num_elements,
              &v147);
          }
          std::vector<std::string>::~vector(&stritemParams);
        }
        else if ( std::vector<std::string>::size(&strParams_1) == 3 )
        {
          v25 = std::vector<std::string>::operator[](&strParams_1, 0);
          v26 = (const char *)std::string::c_str(v25);
          LODWORD(ActivityTrapFile.m_hashIndex._M_ht._M_buckets._M_impl._M_end_of_storage) = atoi(v26);
          std::allocator<char>::allocator(&v149);
          std::string::string(&v148, "|", &v149);
          std::allocator<char>::allocator(&v151);
          v27 = std::vector<std::string>::operator[](&strParams_1, 1u);
          v28 = std::string::c_str(v27);
          std::string::string(&v150, v28, &v151);
          Answer::StringUtility::split(&stritemParams_0, &v150, &v148, 0);
          std::string::~string(&v150);
          std::allocator<char>::~allocator(&v151);
          std::string::~string(&v148);
          std::allocator<char>::~allocator(&v149);
          nlenth_0 = std::vector<std::string>::size(&stritemParams_0);
          for ( j_3 = 0; j_3 < nlenth_0; ++j_3 )
          {
            v29 = std::vector<std::string>::operator[](&stritemParams_0, j_3);
            v30 = (const char *)std::string::c_str(v29);
            v152 = atoi(v30);
            std::vector<int>::push_back(
              (std::vector<int> *const)&ActivityTrapFile.m_hashIndex._M_ht._M_num_elements,
              &v152);
          }
          std::allocator<char>::allocator(&v155);
          std::string::string(&v154, "|", &v155);
          std::allocator<char>::allocator(&v157);
          v31 = std::vector<std::string>::operator[](&strParams_1, 2u);
          v32 = std::string::c_str(v31);
          std::string::string(&v156, v32, &v157);
          Answer::StringUtility::split(&v153, &v156, &v154, 0);
          std::vector<std::string>::operator=(&stritemParams_0, &v153);
          std::vector<std::string>::~vector(&v153);
          std::string::~string(&v156);
          std::allocator<char>::~allocator(&v157);
          std::string::~string(&v154);
          std::allocator<char>::~allocator(&v155);
          nlenth_0 = std::vector<std::string>::size(&stritemParams_0);
          for ( k = 0; k < nlenth_0; ++k )
          {
            v33 = std::vector<std::string>::operator[](&stritemParams_0, k);
            v34 = (const char *)std::string::c_str(v33);
            v158 = atoi(v34);
            std::vector<int>::push_back(&v75, &v158);
          }
          std::vector<std::string>::~vector(&stritemParams_0);
        }
        std::allocator<char>::allocator(&v160);
        std::string::string(&v159, ":", &v160);
        Answer::StringUtility::split(&vStartHour, &start_hour, &v159, 0);
        std::string::~string(&v159);
        std::allocator<char>::~allocator(&v160);
        if ( std::vector<std::string>::size(&vStartHour) )
        {
          for ( j_4 = 0; ; ++j_4 )
          {
            v37 = j_4;
            if ( v37 >= std::vector<std::string>::size(&vStartHour) )
              break;
            v35 = std::vector<std::string>::operator[](&vStartHour, j_4);
            v36 = (const char *)std::string::c_str(v35);
            tstart = atoi(v36);
            if ( (unsigned int)tstart < 0x5A0
              && SLODWORD(ActivityTrapFile.m_pStringBuf) >= 0
              && LODWORD(ActivityTrapFile.m_pStringBuf) + tstart <= 1439 )
            {
              std::vector<int>::push_back((std::vector<int> *const)&ActivityTrapFile.m_vDataBuf, &tstart);
            }
            else
            {
              Answer::Logger::print(
                Answer::LogLevel::LOG_LEVEL_ERROR,
                "wrong activity data with id=%d\n",
                LODWORD(ActivityTrapFile._vptr_CDBCFile));
            }
          }
        }
        v76 = 0;
        v38 = std::map<int,CfgActivity>::operator[](&this->m_activities, (const int *const)&ActivityTrapFile);
        CfgActivity::operator=(v38, (const CfgActivity *const)&ActivityTrapFile);
        std::vector<std::string>::~vector(&vStartHour);
        std::vector<std::string>::~vector(&strParams_1);
        std::vector<std::string>::~vector(&strMaps);
        std::string::~string(&daily);
        std::string::~string(&awards);
        std::string::~string(&position);
        std::string::~string(&start_hour);
        std::string::~string(&maps);
        CfgActivity::~CfgActivity((CfgActivity *const)&ActivityTrapFile);
      }
      CDBCFile::CDBCFile(&ActivityEventFile, 0);
      if ( !CDBCFile::OpenFromTXT(&ActivityEventFile, "./ServerConfig/Tables/cfg_activity_event.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_activity_event.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_Event = CDBCFile::GetRecordsNum(&ActivityEventFile);
        iBaseColumnCount_Event = CDBCFile::GetFieldsNum(&ActivityEventFile);
        if ( iBaseColumnCount_Event > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount_Event; ++i_0 )
          {
            CfgMapEvent::CfgMapEvent((CfgMapEvent *const)&plant);
            nIndex = 0;
            plant.id = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, 0)->iValue;
            plant.activity_id = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, ++nIndex)->iValue;
            plant.plant_id = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, ++nIndex)->iValue;
            v92 = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, ++nIndex)->iValue == 0;
            plant.count = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, ++nIndex)->iValue;
            ++nIndex;
            std::allocator<char>::allocator(&v161);
            v39 = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, nIndex);
            std::string::string(&triggerParam, v39->pString, &v161);
            std::allocator<char>::~allocator(&v161);
            LODWORD(plant.EnterPosVector._M_impl._M_finish) = CDBCFile::Search_Posistion(
                                                                &ActivityEventFile,
                                                                i_0,
                                                                ++nIndex)->iValue;
            v40 = CDBCFile::Search_Posistion(&ActivityEventFile, i_0, ++nIndex);
            std::string::operator=(&plant.EnterPosVector._M_impl._M_end_of_storage, v40->pString);
            ++nIndex;
            std::allocator<char>::allocator(&v163);
            std::string::string(&v162, ":", &v163);
            std::allocator<char>::allocator(&v165);
            v41 = std::string::c_str(&triggerParam);
            std::string::string(&v164, v41, &v165);
            Answer::StringUtility::split(&strParams_2, &v164, &v162, 0);
            std::string::~string(&v164);
            std::allocator<char>::~allocator(&v165);
            std::string::~string(&v162);
            std::allocator<char>::~allocator(&v163);
            for ( it._M_current = std::vector<std::string>::begin(&strParams_2)._M_current;
                  ;
                  __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
            {
              __rhs._M_current = std::vector<std::string>::end(&strParams_2)._M_current;
              if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
                break;
              v42 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
              v43 = (const char *)std::string::c_str(v42);
              v167 = atoi(v43);
              std::vector<int>::push_back((std::vector<int> *const)&plant.wave, &v167);
            }
            v44 = std::map<int,std::map<int,std::list<CfgMapEvent>>>::operator[](&this->m_activityEvents, &plant.id);
            v45 = std::map<int,std::list<CfgMapEvent>>::operator[](v44, &plant.activity_id);
            std::list<CfgMapEvent>::push_back(v45, (const CfgMapEvent *const)&plant);
            std::vector<std::string>::~vector(&strParams_2);
            std::string::~string(&triggerParam);
            CfgMapEvent::~CfgMapEvent((CfgMapEvent *const)&plant);
          }
          CDBCFile::CDBCFile(&ActivityMonsterFile, 0);
          if ( !CDBCFile::OpenFromTXT(&ActivityMonsterFile, "./ServerConfig/Tables/cfg_activity_monster.txt") )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open cfg_activity_monster.txt failed,please check!!");
          }
          else
          {
            iBaseTableCount_Monster = CDBCFile::GetRecordsNum(&ActivityMonsterFile);
            iBaseColumnCount_Monster = CDBCFile::GetFieldsNum(&ActivityMonsterFile);
            if ( iBaseColumnCount_Monster > 0 )
            {
              for ( i_1 = 0; i_1 < iBaseTableCount_Monster; ++i_1 )
              {
                CfgActivityMonster::CfgActivityMonster((CfgActivityMonster *const)&plant);
                plant.id = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 0)->iValue;
                plant.activity_id = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 1)->iValue;
                plant.plant_id = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 2)->iValue;
                plant.count = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 3)->iValue;
                plant.wave = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 4)->iValue;
                plant.region_id = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 5)->iValue;
                plant.whoplant = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 6)->iValue;
                std::allocator<char>::allocator(&v168);
                v46 = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 7);
                std::string::string(&road, v46->pString, &v168);
                std::allocator<char>::~allocator(&v168);
                LODWORD(plant.EnterPosVector._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(
                                                                            &ActivityMonsterFile,
                                                                            i_1,
                                                                            8)->iValue;
                HIDWORD(plant.EnterPosVector._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(
                                                                            &ActivityMonsterFile,
                                                                            i_1,
                                                                            9)->iValue;
                v89 = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 10)->iValue;
                std::allocator<char>::allocator(&v169);
                v47 = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 11);
                std::string::string(&randpos, v47->pString, &v169);
                std::allocator<char>::~allocator(&v169);
                v91 = CDBCFile::Search_Posistion(&ActivityMonsterFile, i_1, 12)->iValue;
                if ( std::string::size(&road) > 3u )
                {
                  std::allocator<char>::allocator(&v171);
                  std::string::string(&v170, ":", &v171);
                  Answer::StringUtility::split(&vRoad, &road, &v170, 0);
                  std::string::~string(&v170);
                  std::allocator<char>::~allocator(&v171);
                  for ( j_5 = 0; ; ++j_5 )
                  {
                    v55 = j_5;
                    if ( v55 >= std::vector<std::string>::size(&vRoad) )
                      break;
                    std::allocator<char>::allocator(&v173);
                    std::string::string(&v172, ",", &v173);
                    v48 = std::vector<std::string>::operator[](&vRoad, j_5);
                    Answer::StringUtility::split(&vPos, v48, &v172, 0);
                    std::string::~string(&v172);
                    std::allocator<char>::~allocator(&v173);
                    if ( std::vector<std::string>::size(&vPos) == 2 )
                    {
                      v49 = std::vector<std::string>::operator[](&vPos, 1u);
                      v50 = (const char *)std::string::c_str(v49);
                      v51 = atoi(v50);
                      v52 = std::vector<std::string>::operator[](&vPos, 0);
                      v53 = (const char *)std::string::c_str(v52);
                      v54 = atoi(v53);
                      Position::Position(&v174, v54, v51);
                      std::list<Position>::push_back((std::list<Position> *const)&plant.EnterPosVector, &v174);
                    }
                    std::vector<std::string>::~vector(&vPos);
                  }
                  std::vector<std::string>::~vector(&vRoad);
                }
                if ( std::string::size(&randpos) > 3u )
                {
                  std::allocator<char>::allocator(&v176);
                  std::string::string(&v175, "|", &v176);
                  Answer::StringUtility::split(&vRandPos, &randpos, &v175, 0);
                  std::string::~string(&v175);
                  std::allocator<char>::~allocator(&v176);
                  for ( j_6 = 0; ; ++j_6 )
                  {
                    v63 = j_6;
                    if ( v63 >= std::vector<std::string>::size(&vRandPos) )
                      break;
                    std::allocator<char>::allocator(&v178);
                    std::string::string(&v177, ":", &v178);
                    v56 = std::vector<std::string>::operator[](&vRandPos, j_6);
                    Answer::StringUtility::split(&vPos_0, v56, &v177, 0);
                    std::string::~string(&v177);
                    std::allocator<char>::~allocator(&v178);
                    if ( std::vector<std::string>::size(&vPos_0) == 2 )
                    {
                      v57 = std::vector<std::string>::operator[](&vPos_0, 1u);
                      v58 = (const char *)std::string::c_str(v57);
                      v59 = atoi(v58);
                      v60 = std::vector<std::string>::operator[](&vPos_0, 0);
                      v61 = (const char *)std::string::c_str(v60);
                      v62 = atoi(v61);
                      Position::Position(&v179, v62, v59);
                      std::vector<Position>::push_back(&v90, &v179);
                    }
                    std::vector<std::string>::~vector(&vPos_0);
                  }
                  std::vector<std::string>::~vector(&vRandPos);
                }
                v64 = std::map<int,CfgActivityMonster>::operator[](&this->m_activityMonsters, &plant.id);
                CfgActivityMonster::operator=(v64, (const CfgActivityMonster *const)&plant);
                std::string::~string(&randpos);
                std::string::~string(&road);
                CfgActivityMonster::~CfgActivityMonster((CfgActivityMonster *const)&plant);
              }
              CDBCFile::CDBCFile(&ActivityNpcFile, 0);
              if ( !CDBCFile::OpenFromTXT(&ActivityNpcFile, "./ServerConfig/Tables/cfg_activity_npc.txt") )
              {
                Answer::Logger::print(
                  Answer::LogLevel::LOG_LEVEL_ERROR,
                  "open cfg_activity_npc.txt failed,please check!!");
              }
              else
              {
                iBaseTableCount_Npc = CDBCFile::GetRecordsNum(&ActivityNpcFile);
                iBaseColumnCount_Npc = CDBCFile::GetFieldsNum(&ActivityNpcFile);
                if ( iBaseColumnCount_Npc > 0 )
                {
                  for ( i_2 = 0; i_2 < iBaseTableCount_Npc; ++i_2 )
                  {
                    CfgActivityNpc::CfgActivityNpc((CfgActivityNpc *const)&plant);
                    plant.id = CDBCFile::Search_Posistion(&ActivityNpcFile, i_2, 0)->iValue;
                    plant.activity_id = CDBCFile::Search_Posistion(&ActivityNpcFile, i_2, 1)->iValue;
                    plant.plant_id = CDBCFile::Search_Posistion(&ActivityNpcFile, i_2, 2)->iValue;
                    plant.count = CDBCFile::Search_Posistion(&ActivityNpcFile, i_2, 3)->iValue;
                    std::allocator<char>::allocator(&v180);
                    v65 = CDBCFile::Search_Posistion(&ActivityNpcFile, i_2, 4);
                    std::string::string(&regionId, v65->pString, &v180);
                    std::allocator<char>::~allocator(&v180);
                    std::allocator<char>::allocator(&v182);
                    std::string::string(&v181, ":", &v182);
                    std::allocator<char>::allocator(&v184);
                    v66 = std::string::c_str(&regionId);
                    std::string::string(&v183, v66, &v184);
                    Answer::StringUtility::split(&strRegions, &v183, &v181, 0);
                    std::string::~string(&v183);
                    std::allocator<char>::~allocator(&v184);
                    std::string::~string(&v181);
                    std::allocator<char>::~allocator(&v182);
                    for ( it_0._M_current = std::vector<std::string>::begin(&strRegions)._M_current;
                          ;
                          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0) )
                    {
                      v185._M_current = std::vector<std::string>::end(&strRegions)._M_current;
                      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v185) )
                        break;
                      v67 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_0);
                      v68 = (const char *)std::string::c_str(v67);
                      v186 = atoi(v68);
                      std::vector<int>::push_back((std::vector<int> *const)&plant.wave, &v186);
                    }
                    v69 = std::map<int,CfgActivityNpc>::operator[](&this->m_activityNpcs, &plant.id);
                    CfgActivityNpc::operator=(v69, (const CfgActivityNpc *const)&plant);
                    std::vector<std::string>::~vector(&strRegions);
                    std::string::~string(&regionId);
                    CfgActivityNpc::~CfgActivityNpc((CfgActivityNpc *const)&plant);
                  }
                  CDBCFile::CDBCFile(&ActivityPlantFile, 0);
                  if ( !CDBCFile::OpenFromTXT(&ActivityPlantFile, "./ServerConfig/Tables/cfg_activity_plant.txt") )
                  {
                    Answer::Logger::print(
                      Answer::LogLevel::LOG_LEVEL_ERROR,
                      "open cfg_activity_plant.txt failed,please check!!");
                  }
                  else
                  {
                    iBaseTableCount_Plant = CDBCFile::GetRecordsNum(&ActivityPlantFile);
                    iBaseColumnCount_Plant = CDBCFile::GetFieldsNum(&ActivityPlantFile);
                    if ( iBaseColumnCount_Plant > 0 )
                    {
                      for ( i_3 = 0; i_3 < iBaseTableCount_Plant; ++i_3 )
                      {
                        CfgActivityPlant::CfgActivityPlant(&plant);
                        plant.id = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 0)->iValue;
                        plant.activity_id = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 1)->iValue;
                        plant.plant_id = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 2)->iValue;
                        plant.count = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 3)->iValue;
                        plant.wave = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 4)->iValue;
                        plant.region_id = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 5)->iValue;
                        plant.whoplant = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 6)->iValue;
                        std::allocator<char>::allocator(&v189);
                        v70 = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 7);
                        std::string::string(&strPos, v70->pString, &v189);
                        CfgData::paresPosition(&v187, this, &strPos);
                        std::vector<Position>::operator=(&plant.EnterPosVector, &v187);
                        std::vector<Position>::~vector(&v187);
                        std::string::~string(&strPos);
                        std::allocator<char>::~allocator(&v189);
                        plant.life_time = CDBCFile::Search_Posistion(&ActivityPlantFile, i_3, 8)->iValue;
                        v71 = std::map<int,CfgActivityPlant>::operator[](&this->m_activityPlants, &plant.id);
                        CfgActivityPlant::operator=(v71, &plant);
                        CfgActivityPlant::~CfgActivityPlant(&plant);
                      }
                      CDBCFile::CDBCFile(&ActivityDropFile, 0);
                      if ( !CDBCFile::OpenFromTXT(&ActivityDropFile, "./ServerConfig/Tables/cfg_activity_drop.txt") )
                      {
                        Answer::Logger::print(
                          Answer::LogLevel::LOG_LEVEL_ERROR,
                          "open cfg_activity_drop.txt failed,please check!!");
                      }
                      else
                      {
                        iBaseTableCount_Drop = CDBCFile::GetRecordsNum(&ActivityDropFile);
                        iBaseColumnCount_Drop = CDBCFile::GetFieldsNum(&ActivityDropFile);
                        if ( iBaseColumnCount_Drop > 0 )
                        {
                          for ( i_4 = 0; i_4 < iBaseTableCount_Drop; ++i_4 )
                          {
                            drop.id = CDBCFile::Search_Posistion(&ActivityDropFile, i_4, 0)->iValue;
                            drop.activity_id = CDBCFile::Search_Posistion(&ActivityDropFile, i_4, 1)->iValue;
                            drop.monster_min_level = CDBCFile::Search_Posistion(&ActivityDropFile, i_4, 2)->iValue;
                            drop.drop_group_id = CDBCFile::Search_Posistion(&ActivityDropFile, i_4, 3)->iValue;
                            drop.probability = CDBCFile::Search_Posistion(&ActivityDropFile, i_4, 4)->iValue;
                            drop.bind_type = CDBCFile::Search_Posistion(&ActivityDropFile, i_4, 5)->iValue;
                            v72 = std::map<int,CfgActivityDrop>::operator[](&this->m_activityDrops, &drop.id);
                            *v72 = drop;
                          }
                          CDBCFile::CDBCFile(&ActivityTrapFile, 0);
                          if ( !CDBCFile::OpenFromTXT(&ActivityTrapFile, "./ServerConfig/Tables/cfg_activity_trap.txt") )
                          {
                            Answer::Logger::print(
                              Answer::LogLevel::LOG_LEVEL_ERROR,
                              "open cfg_activity_trap.txt failed,please check!!");
                          }
                          else
                          {
                            iBaseTableCount_Trap = CDBCFile::GetRecordsNum(&ActivityTrapFile);
                            iBaseColumnCount_Trap = CDBCFile::GetFieldsNum(&ActivityTrapFile);
                            if ( iBaseColumnCount_Trap > 0 )
                            {
                              for ( i_5 = 0; i_5 < iBaseTableCount_Trap; ++i_5 )
                              {
                                trap.id = CDBCFile::Search_Posistion(&ActivityTrapFile, i_5, 0)->iValue;
                                trap.tid = CDBCFile::Search_Posistion(&ActivityTrapFile, i_5, 1)->iValue;
                                trap.x = CDBCFile::Search_Posistion(&ActivityTrapFile, i_5, 2)->iValue;
                                trap.y = CDBCFile::Search_Posistion(&ActivityTrapFile, i_5, 3)->iValue;
                                v73 = std::map<int,CfgActivityTrap>::operator[](&this->m_activityTraps, &trap.id);
                                *v73 = trap;
                              }
                            }
                          }
                          CDBCFile::~CDBCFile(&ActivityTrapFile);
                        }
                      }
                      CDBCFile::~CDBCFile(&ActivityDropFile);
                    }
                  }
                  CDBCFile::~CDBCFile(&ActivityPlantFile);
                }
              }
              CDBCFile::~CDBCFile(&ActivityNpcFile);
            }
          }
          CDBCFile::~CDBCFile(&ActivityMonsterFile);
        }
      }
      CDBCFile::~CDBCFile(&ActivityEventFile);
    }
  }
  CDBCFile::~CDBCFile(&ActivityFile);
}


#####################################
void __cdecl CfgData::fetchBuff(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgBuff *v3; // rax
  CDBCFile BuffFile; // [rsp+10h] [rbp-160h] BYREF
  CfgBuff buff; // [rsp+A0h] [rbp-D0h] BYREF
  BuffAttrVector __x; // [rsp+110h] [rbp-60h] BYREF
  std::string str; // [rsp+130h] [rbp-40h] BYREF
  char v8; // [rsp+13Fh] [rbp-31h] BYREF
  std::string v9; // [rsp+140h] [rbp-30h] BYREF
  char v10; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&BuffFile, 0);
  if ( !CDBCFile::OpenFromTXT(&BuffFile, "./ServerConfig/Tables/cfg_buff.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_buff.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&BuffFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&BuffFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgBuff::CfgBuff(&buff);
        buff.id = CDBCFile::Search_Posistion(&BuffFile, i, nIndex++)->iValue;
        buff.groupid = CDBCFile::Search_Posistion(&BuffFile, i, nIndex++)->iValue;
        buff.attack_type = CDBCFile::Search_Posistion(&BuffFile, i, nIndex++)->iValue;
        buff.level = CDBCFile::Search_Posistion(&BuffFile, i, nIndex++)->iValue;
        ++nIndex;
        buff.beneficial = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.special = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.duration = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.interval = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&BuffFile, i, nIndex);
        std::string::string(&str, v1->pString, &v8);
        CfgData::paraseBuffAttr(&__x, this, &str);
        std::vector<BuffAttr>::operator=(&buff.buffAttr, &__x);
        std::vector<BuffAttr>::~vector(&__x);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        buff.isShow = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        buff.modify = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.control = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.hpValue = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.hpPecent = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.shieldValue = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.shieldRatio = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.effectType = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.effectTimes = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.canRemove = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        buff.canRecover = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&BuffFile, i, nIndex);
        std::string::string(&v9, v2->pString, &v10);
        buff.angry = CfgData::paraseParam2(this, &v9);
        std::string::~string(&v9);
        std::allocator<char>::~allocator(&v10);
        buff.battle = CDBCFile::Search_Posistion(&BuffFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,CfgBuff>::operator[](&this->m_buffs, &buff.id);
        CfgBuff::operator=(v3, &buff);
        CfgBuff::~CfgBuff(&buff);
      }
    }
  }
  CDBCFile::~CDBCFile(&BuffFile);
}


#####################################
void __cdecl CfgData::fetchDungeon(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  CfgDungeon *v8; // rax
  CfgDungeon *v9; // rax
  CfgDungeonReward *v10; // rax
  CfgDungeonDropGroup *v11; // rax
  __int64 v12; // rax
  CfgDungeon dungeon; // [rsp+10h] [rbp-480h] BYREF
  CDBCFile DungeonDropFile; // [rsp+130h] [rbp-360h] BYREF
  CDBCFile DungeonRewardFile; // [rsp+1C0h] [rbp-2D0h] BYREF
  CDBCFile DungeonFile; // [rsp+250h] [rbp-240h] BYREF
  int32_t id; // [rsp+2ECh] [rbp-1A4h] BYREF
  CfgDungeonDrop group; // [rsp+2F0h] [rbp-1A0h] BYREF
  CfgDungeonReward reward; // [rsp+310h] [rbp-180h] BYREF
  std::string strItem; // [rsp+330h] [rbp-160h] BYREF
  char v21; // [rsp+33Fh] [rbp-151h] BYREF
  MemChrBagVector __x; // [rsp+340h] [rbp-150h] BYREF
  std::string strItems; // [rsp+360h] [rbp-130h] BYREF
  char v24; // [rsp+36Fh] [rbp-121h] BYREF
  MemChrBagVector v25; // [rsp+370h] [rbp-120h] BYREF
  std::string v26; // [rsp+390h] [rbp-100h] BYREF
  char v27; // [rsp+39Fh] [rbp-F1h] BYREF
  Int32Vector v28; // [rsp+3A0h] [rbp-F0h] BYREF
  std::string path; // [rsp+3C0h] [rbp-D0h] BYREF
  char v30; // [rsp+3CFh] [rbp-C1h] BYREF
  std::string str; // [rsp+3D0h] [rbp-C0h] BYREF
  char v32; // [rsp+3DFh] [rbp-B1h] BYREF
  MemChrBagVector v33; // [rsp+3E0h] [rbp-B0h] BYREF
  std::string v34; // [rsp+400h] [rbp-90h] BYREF
  char v35; // [rsp+40Fh] [rbp-81h] BYREF
  Int32Vector v36; // [rsp+410h] [rbp-80h] BYREF
  std::string v37; // [rsp+430h] [rbp-60h] BYREF
  char v38; // [rsp+43Fh] [rbp-51h] BYREF
  std::string v39; // [rsp+440h] [rbp-50h] BYREF
  char v40; // [rsp+44Ah] [rbp-46h] BYREF
  int32_t iBaseTableCount; // [rsp+44Ch] [rbp-44h]
  int32_t iBaseColumnCount; // [rsp+450h] [rbp-40h]
  int32_t nIndex; // [rsp+454h] [rbp-3Ch]
  int32_t iBaseTableCount_Reward; // [rsp+45Ch] [rbp-34h]
  int32_t iBaseColumnCount_Reward; // [rsp+460h] [rbp-30h]
  int32_t iBaseTableCount_Drop; // [rsp+468h] [rbp-28h]
  int32_t iBaseColumnCount_Drop; // [rsp+46Ch] [rbp-24h]
  int32_t i; // [rsp+470h] [rbp-20h]
  int32_t weekday; // [rsp+474h] [rbp-1Ch]
  int32_t i_0; // [rsp+478h] [rbp-18h]
  int32_t i_1; // [rsp+47Ch] [rbp-14h]
  ItemData v55; // 0:kr00_12.12

  CDBCFile::CDBCFile(&DungeonFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonFile, "./ServerConfig/Tables/cfg_dungeon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonFile);
    if ( iBaseColumnCount > 0 )
    {
      nIndex = 0;
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&dungeon, 0, sizeof(dungeon));
        std::string::string(&dungeon.name);
        std::vector<MemChrBag>::vector(&dungeon.rewardOnce);
        std::vector<MemChrBag>::vector(&dungeon.rewardItem);
        std::vector<int>::vector(&dungeon.win_star);
        std::vector<MemChrBag>::vector(&dungeon.star_reward);
        std::vector<int>::vector(&dungeon.star_ratio);
        dungeon.id = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex++)->iValue;
        v1 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::operator=(&dungeon.name, v1->pString);
        ++nIndex;
        ++nIndex;
        dungeon.mapid = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.x = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.y = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.type = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.sequence = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.group_id = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.duration = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.job = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.level = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.maxLevel = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.vip = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.player_num = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        weekday = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.start_hour = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.end_hour = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.daily_count = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        dungeon.last_id = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.next_id = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.player_buff = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.star = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.double_cost = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.reward_time = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v21);
        v2 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::string(&strItem, v2->pString, &v21);
        v55 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v12) = v55.m_nId;
        BYTE4(v12) = v55.m_nClass;
        *(_QWORD *)&dungeon.costItem.m_nId = v12;
        dungeon.costItem.m_nCount = v55.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v21);
        ++nIndex;
        std::allocator<char>::allocator(&v24);
        v3 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::string(&strItems, v3->pString, &v24);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&dungeon.rewardItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v24);
        ++nIndex;
        std::allocator<char>::allocator(&v27);
        v4 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::string(&v26, v4->pString, &v27);
        CItemHelper::parseItemVectorString(&v25, &v26);
        std::vector<MemChrBag>::operator=(&dungeon.rewardOnce, &v25);
        std::vector<MemChrBag>::~vector(&v25);
        std::string::~string(&v26);
        std::allocator<char>::~allocator(&v27);
        ++nIndex;
        dungeon.Battle = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.costMoney = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.costGold = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.buyTimes = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.buyCost = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.quickDoneCost = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.quickDoneDrop = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.needUpTowerStar = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.summon_cost = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.summon_boss = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.rand_time = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        dungeon.task_id = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.stay_position = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v30);
        std::string::string(&path, "./ServerConfig/Tables/cfg_dungeon.txt", &v30);
        std::allocator<char>::allocator(&v32);
        v5 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::string(&str, v5->pString, &v32);
        CfgData::paraseInt32Vector(&v28, this, &str, &path, 0);
        std::vector<int>::operator=(&dungeon.win_star, &v28);
        std::vector<int>::~vector(&v28);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v32);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v30);
        ++nIndex;
        std::allocator<char>::allocator(&v35);
        v6 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::string(&v34, v6->pString, &v35);
        CItemHelper::parseItemVectorString(&v33, &v34);
        std::vector<MemChrBag>::operator=(&dungeon.star_reward, &v33);
        std::vector<MemChrBag>::~vector(&v33);
        std::string::~string(&v34);
        std::allocator<char>::~allocator(&v35);
        ++nIndex;
        std::allocator<char>::allocator(&v38);
        std::string::string(&v37, "./ServerConfig/Tables/cfg_dungeon.txt", &v38);
        std::allocator<char>::allocator(&v40);
        v7 = CDBCFile::Search_Posistion(&DungeonFile, i, nIndex);
        std::string::string(&v39, v7->pString, &v40);
        CfgData::paraseInt32Vector(&v36, this, &v39, &v37, 0);
        std::vector<int>::operator=(&dungeon.star_ratio, &v36);
        std::vector<int>::~vector(&v36);
        std::string::~string(&v39);
        std::allocator<char>::~allocator(&v40);
        std::string::~string(&v37);
        std::allocator<char>::~allocator(&v38);
        ++nIndex;
        dungeon.TeQuan = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.backMapId = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.backX = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.backY = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        dungeon.CanEnter = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        dungeon.BuffId = CDBCFile::Search_Posistion(&DungeonFile, i, ++nIndex)->iValue;
        ++nIndex;
        while ( weekday > 0 )
        {
          dungeon.weekday |= 1 << ((char)weekday % 10);
          weekday /= 10;
        }
        v8 = std::map<int,CfgDungeon>::operator[](&this->m_dungeons, &dungeon.id);
        CfgDungeon::operator=(v8, &dungeon);
        if ( dungeon.type == 16 )
        {
          v9 = std::map<int,CfgDungeon>::operator[](&this->m_mUpTowerDungeon, &dungeon.star);
          CfgDungeon::operator=(v9, &dungeon);
        }
        CfgDungeon::~CfgDungeon(&dungeon);
      }
      CDBCFile::CDBCFile(&DungeonRewardFile, 0);
      if ( !CDBCFile::OpenFromTXT(&DungeonRewardFile, "./ServerConfig/Tables/cfg_dungeon_reward.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_reward.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_Reward = CDBCFile::GetRecordsNum(&DungeonRewardFile);
        iBaseColumnCount_Reward = CDBCFile::GetFieldsNum(&DungeonRewardFile);
        if ( iBaseColumnCount_Reward > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount_Reward; ++i_0 )
          {
            reward.dungeonID = CDBCFile::Search_Posistion(&DungeonRewardFile, i_0, 0)->iValue;
            reward.exp = CDBCFile::Search_Posistion(&DungeonRewardFile, i_0, 1)->iValue;
            reward.money = CDBCFile::Search_Posistion(&DungeonRewardFile, i_0, 2)->iValue;
            reward.cash = CDBCFile::Search_Posistion(&DungeonRewardFile, i_0, 3)->iValue;
            reward.groupID = CDBCFile::Search_Posistion(&DungeonRewardFile, i_0, 4)->iValue;
            v10 = std::map<int,CfgDungeonReward>::operator[](&this->m_dungeonReward, &reward.dungeonID);
            *v10 = reward;
          }
          CDBCFile::CDBCFile(&DungeonDropFile, 0);
          if ( !CDBCFile::OpenFromTXT(&DungeonDropFile, "./ServerConfig/Tables/cfg_dungeon_drop_group.txt") )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open cfg_dungeon_drop_group.txt failed,please check!!");
          }
          else
          {
            iBaseTableCount_Drop = CDBCFile::GetRecordsNum(&DungeonDropFile);
            iBaseColumnCount_Drop = CDBCFile::GetFieldsNum(&DungeonDropFile);
            if ( iBaseColumnCount_Drop > 0 )
            {
              for ( i_1 = 0; i_1 < iBaseTableCount_Drop; ++i_1 )
              {
                id = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 0)->iValue;
                group.type = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 1)->iValue;
                group.item_id = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 3)->iValue;
                group.item_class = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 4)->iValue;
                group.bind_type = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 5)->iValue;
                group.count = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 6)->iValue;
                group.weight = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 7)->iValue;
                group.probability = CDBCFile::Search_Posistion(&DungeonDropFile, i_1, 8)->iValue;
                v11 = std::map<int,CfgDungeonDropGroup>::operator[](&this->m_dungeonDropGroup, &id);
                CfgDungeonDropGroup::Add(v11, &group);
              }
            }
          }
          CDBCFile::~CDBCFile(&DungeonDropFile);
        }
      }
      CDBCFile::~CDBCFile(&DungeonRewardFile);
    }
  }
  CDBCFile::~CDBCFile(&DungeonFile);
}


#####################################
void __cdecl CfgData::fetchDungeonEvent(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  __int64 v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::list<CfgMapEvent> *v6; // rax
  CDBCFile DungeonEventFile; // [rsp+10h] [rbp-180h] BYREF
  CfgMapEvent dungeonEvent; // [rsp+A0h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+100h] [rbp-90h] BYREF
  StringVector strTriggerParam; // [rsp+110h] [rbp-80h] BYREF
  std::string triggerParam; // [rsp+130h] [rbp-60h] BYREF
  char v12; // [rsp+13Fh] [rbp-51h] BYREF
  std::string delims; // [rsp+140h] [rbp-50h] BYREF
  char v14; // [rsp+14Fh] [rbp-41h] BYREF
  std::string str; // [rsp+150h] [rbp-40h] BYREF
  char v16; // [rsp+15Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+160h] [rbp-30h] BYREF
  int __x; // [rsp+16Ch] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+174h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+178h] [rbp-18h]
  int32_t i; // [rsp+17Ch] [rbp-14h]

  CDBCFile::CDBCFile(&DungeonEventFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonEventFile, "./ServerConfig/Tables/cfg_dungeon_event.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_event.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonEventFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonEventFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgMapEvent::CfgMapEvent(&dungeonEvent);
        dungeonEvent.id = CDBCFile::Search_Posistion(&DungeonEventFile, i, 0)->iValue;
        dungeonEvent.trigger_id = CDBCFile::Search_Posistion(&DungeonEventFile, i, 1)->iValue;
        dungeonEvent.bInitOpen = CDBCFile::Search_Posistion(&DungeonEventFile, i, 2)->iValue == 0;
        dungeonEvent.trigger_type = CDBCFile::Search_Posistion(&DungeonEventFile, i, 3)->iValue;
        std::allocator<char>::allocator(&v12);
        v1 = CDBCFile::Search_Posistion(&DungeonEventFile, i, 4);
        std::string::string(&triggerParam, v1->pString, &v12);
        std::allocator<char>::~allocator(&v12);
        dungeonEvent.event_type = CDBCFile::Search_Posistion(&DungeonEventFile, i, 5)->iValue;
        v2 = CDBCFile::Search_Posistion(&DungeonEventFile, i, 6);
        std::string::operator=(&dungeonEvent.effect, v2->pString);
        dungeonEvent.repeate = CDBCFile::Search_Posistion(&DungeonEventFile, i, 7)->iValue;
        std::allocator<char>::allocator(&v14);
        std::string::string(&delims, ":", &v14);
        std::allocator<char>::allocator(&v16);
        v3 = std::string::c_str(&triggerParam);
        std::string::string(&str, v3, &v16);
        Answer::StringUtility::split(&strTriggerParam, &str, &delims, 0);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v16);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v14);
        for ( it._M_current = std::vector<std::string>::begin(&strTriggerParam)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strTriggerParam)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v5 = (const char *)std::string::c_str(v4);
          __x = atoi(v5);
          std::vector<int>::push_back(&dungeonEvent.trigger_param, &__x);
        }
        if ( !std::vector<int>::empty(&dungeonEvent.trigger_param) )
        {
          v6 = std::map<int,std::list<CfgMapEvent>>::operator[](&this->m_dungeonEvents, &dungeonEvent.id);
          std::list<CfgMapEvent>::push_back(v6, &dungeonEvent);
        }
        std::vector<std::string>::~vector(&strTriggerParam);
        std::string::~string(&triggerParam);
        CfgMapEvent::~CfgMapEvent(&dungeonEvent);
      }
    }
  }
  CDBCFile::~CDBCFile(&DungeonEventFile);
}


#####################################
void __cdecl CfgData::fetchDungeonMonster(CfgData *const this)
{
  unsigned int id; // r12d
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  int32_t v8; // ebx
  std::string *v9; // rax
  const char *v10; // rax
  int32_t v11; // eax
  size_t v12; // rbx
  std::string *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  int32_t v16; // ebx
  std::string *v17; // rax
  const char *v18; // rax
  int32_t v19; // eax
  size_t v20; // rbx
  CfgDungeonMonster *v21; // rax
  CDBCFile DungeonMonsterFile; // [rsp+10h] [rbp-250h] BYREF
  CfgDungeonMonster monster; // [rsp+A0h] [rbp-1C0h] BYREF
  StringVector vPos_0; // [rsp+110h] [rbp-150h] BYREF
  StringVector vRandPos; // [rsp+130h] [rbp-130h] BYREF
  StringVector vPos; // [rsp+150h] [rbp-110h] BYREF
  StringVector vRoad; // [rsp+170h] [rbp-F0h] BYREF
  std::string randpos; // [rsp+190h] [rbp-D0h] BYREF
  std::string road; // [rsp+1A0h] [rbp-C0h] BYREF
  std::list<Param2> __x; // [rsp+1B0h] [rbp-B0h] BYREF
  _BYTE v31[15]; // [rsp+1C0h] [rbp-A0h] BYREF
  char v32; // [rsp+1CFh] [rbp-91h] BYREF
  int32_t nIndex[3]; // [rsp+1D0h] [rbp-90h] BYREF
  char v34; // [rsp+1DDh] [rbp-83h] BYREF
  char v35; // [rsp+1DEh] [rbp-82h] BYREF
  char v36; // [rsp+1DFh] [rbp-81h] BYREF
  std::string delims; // [rsp+1E0h] [rbp-80h] BYREF
  char v38; // [rsp+1EFh] [rbp-71h] BYREF
  std::string v39; // [rsp+1F0h] [rbp-70h] BYREF
  char v40; // [rsp+1FFh] [rbp-61h] BYREF
  Position v41; // [rsp+200h] [rbp-60h] BYREF
  std::string v42; // [rsp+210h] [rbp-50h] BYREF
  char v43; // [rsp+21Fh] [rbp-41h] BYREF
  std::string v44; // [rsp+220h] [rbp-40h] BYREF
  char v45; // [rsp+22Fh] [rbp-31h] BYREF
  Position v46; // [rsp+230h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+23Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+240h] [rbp-20h]
  int32_t i; // [rsp+244h] [rbp-1Ch]
  uint32_t j; // [rsp+248h] [rbp-18h]
  uint32_t j_0; // [rsp+24Ch] [rbp-14h]

  CDBCFile::CDBCFile(&DungeonMonsterFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonMonsterFile, "./ServerConfig/Tables/cfg_dungeon_monster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_monster.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonMonsterFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonMonsterFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgDungeonMonster::CfgDungeonMonster(&monster);
        monster.id = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 0)->iValue;
        monster.wave = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v32);
        std::string::string(v31, "./ServerConfig/Tables/cfg_dungeon_monster.txt", &v32);
        id = monster.id;
        std::allocator<char>::allocator(&v34);
        v2 = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 2);
        std::string::string(nIndex, v2->pString, &v34);
        CfgData::paraseParam2List(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)nIndex,
          (const std::string *const)id);
        std::list<Param2>::operator=(&monster.mids, &__x);
        std::list<Param2>::~list(&__x);
        std::string::~string(nIndex);
        std::allocator<char>::~allocator(&v34);
        std::string::~string(v31);
        std::allocator<char>::~allocator(&v32);
        monster.x = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 3)->iValue;
        monster.y = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 4)->iValue;
        monster.count = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 5)->iValue;
        monster.side = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 6)->iValue;
        std::allocator<char>::allocator(&v35);
        v3 = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 7);
        std::string::string(&road, v3->pString, &v35);
        std::allocator<char>::~allocator(&v35);
        monster.delay = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 8)->iValue;
        monster.times = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 9)->iValue;
        monster.money = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 10)->iValue;
        monster.life = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 11)->iValue;
        std::allocator<char>::allocator(&v36);
        v4 = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 12);
        std::string::string(&randpos, v4->pString, &v36);
        std::allocator<char>::~allocator(&v36);
        monster.wait = CDBCFile::Search_Posistion(&DungeonMonsterFile, i, 13)->iValue;
        if ( std::string::size(&road) > 3u )
        {
          std::allocator<char>::allocator(&v38);
          std::string::string(&delims, ":", &v38);
          Answer::StringUtility::split(&vRoad, &road, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v38);
          for ( j = 0; ; ++j )
          {
            v12 = j;
            if ( v12 >= std::vector<std::string>::size(&vRoad) )
              break;
            std::allocator<char>::allocator(&v40);
            std::string::string(&v39, ",", &v40);
            v5 = std::vector<std::string>::operator[](&vRoad, j);
            Answer::StringUtility::split(&vPos, v5, &v39, 0);
            std::string::~string(&v39);
            std::allocator<char>::~allocator(&v40);
            if ( std::vector<std::string>::size(&vPos) == 2 )
            {
              v6 = std::vector<std::string>::operator[](&vPos, 1u);
              v7 = (const char *)std::string::c_str(v6);
              v8 = atoi(v7);
              v9 = std::vector<std::string>::operator[](&vPos, 0);
              v10 = (const char *)std::string::c_str(v9);
              v11 = atoi(v10);
              Position::Position(&v41, v11, v8);
              std::list<Position>::push_back(&monster.road, &v41);
            }
            std::vector<std::string>::~vector(&vPos);
          }
          std::vector<std::string>::~vector(&vRoad);
        }
        if ( std::string::size(&randpos) > 3u )
        {
          std::allocator<char>::allocator(&v43);
          std::string::string(&v42, "|", &v43);
          Answer::StringUtility::split(&vRandPos, &randpos, &v42, 0);
          std::string::~string(&v42);
          std::allocator<char>::~allocator(&v43);
          for ( j_0 = 0; ; ++j_0 )
          {
            v20 = j_0;
            if ( v20 >= std::vector<std::string>::size(&vRandPos) )
              break;
            std::allocator<char>::allocator(&v45);
            std::string::string(&v44, ":", &v45);
            v13 = std::vector<std::string>::operator[](&vRandPos, j_0);
            Answer::StringUtility::split(&vPos_0, v13, &v44, 0);
            std::string::~string(&v44);
            std::allocator<char>::~allocator(&v45);
            if ( std::vector<std::string>::size(&vPos_0) == 2 )
            {
              v14 = std::vector<std::string>::operator[](&vPos_0, 1u);
              v15 = (const char *)std::string::c_str(v14);
              v16 = atoi(v15);
              v17 = std::vector<std::string>::operator[](&vPos_0, 0);
              v18 = (const char *)std::string::c_str(v17);
              v19 = atoi(v18);
              Position::Position(&v46, v19, v16);
              std::vector<Position>::push_back(&monster.randpos, &v46);
            }
            std::vector<std::string>::~vector(&vPos_0);
          }
          std::vector<std::string>::~vector(&vRandPos);
        }
        v21 = std::map<int,CfgDungeonMonster>::operator[](&this->m_dungeonMonsters, &monster.id);
        CfgDungeonMonster::operator=(v21, &monster);
        std::string::~string(&randpos);
        std::string::~string(&road);
        CfgDungeonMonster::~CfgDungeonMonster(&monster);
      }
    }
  }
  CDBCFile::~CDBCFile(&DungeonMonsterFile);
}


#####################################
void __cdecl CfgData::fetchDungeonPlant(CfgData *const this)
{
  CfgDungeonPlant *v1; // rax
  CDBCFile DungeonPlantFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgDungeonPlant dungeonPlant; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&DungeonPlantFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonPlantFile, "./ServerConfig/Tables/cfg_dungeon_plant.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_plant.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonPlantFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonPlantFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        dungeonPlant.id = CDBCFile::Search_Posistion(&DungeonPlantFile, i, 0)->iValue;
        dungeonPlant.pid = CDBCFile::Search_Posistion(&DungeonPlantFile, i, 1)->iValue;
        dungeonPlant.x = CDBCFile::Search_Posistion(&DungeonPlantFile, i, 2)->iValue;
        dungeonPlant.y = CDBCFile::Search_Posistion(&DungeonPlantFile, i, 3)->iValue;
        v1 = std::map<int,CfgDungeonPlant>::operator[](&this->m_dungeonPlants, &dungeonPlant.id);
        *v1 = dungeonPlant;
      }
    }
  }
  CDBCFile::~CDBCFile(&DungeonPlantFile);
}


#####################################
void __cdecl CfgData::fetchDungeonTrap(CfgData *const this)
{
  CfgDungeonTrap *v1; // rax
  CDBCFile DungeonTrapFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgDungeonTrap dungeonTrap; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&DungeonTrapFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonTrapFile, "./ServerConfig/Tables/cfg_dungeon_trap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_trap.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonTrapFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonTrapFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        dungeonTrap.id = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 0)->iValue;
        dungeonTrap.tid = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 1)->iValue;
        dungeonTrap.x = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 2)->iValue;
        dungeonTrap.y = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 3)->iValue;
        v1 = std::map<int,CfgDungeonTrap>::operator[](&this->m_dungeonTraps, &dungeonTrap.id);
        *v1 = dungeonTrap;
      }
    }
  }
  CDBCFile::~CDBCFile(&DungeonTrapFile);
}


#####################################
void __cdecl CfgData::fetchDungeonNpc(CfgData *const this)
{
  CfgDungeonNpc *v1; // rax
  CDBCFile DungeonTrapFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgDungeonNpc dungeonNpc; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&DungeonTrapFile, 0);
  if ( !CDBCFile::OpenFromTXT(&DungeonTrapFile, "./ServerConfig/Tables/cfg_dungeon_npc.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_npc.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&DungeonTrapFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&DungeonTrapFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        dungeonNpc.id = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 0)->iValue;
        dungeonNpc.NpcId = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 1)->iValue;
        dungeonNpc.x = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 2)->iValue;
        dungeonNpc.y = CDBCFile::Search_Posistion(&DungeonTrapFile, i, 3)->iValue;
        v1 = std::map<int,CfgDungeonNpc>::operator[](&this->m_dungeonNpcs, &dungeonNpc.id);
        *v1 = dungeonNpc;
      }
    }
  }
  CDBCFile::~CDBCFile(&DungeonTrapFile);
}


#####################################
void __cdecl CfgData::fetchChrShop(CfgData *const this)
{
  CfgChrShop *v1; // rax
  CDBCFile ChrShopFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgChrShop chrShop; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&ChrShopFile, 0);
  if ( !CDBCFile::OpenFromTXT(&ChrShopFile, "./ServerConfig/Tables/cfg_chr_shop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_chr_shop.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&ChrShopFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&ChrShopFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        chrShop.Index = CDBCFile::Search_Posistion(&ChrShopFile, i, 0)->iValue;
        chrShop.ItemId = CDBCFile::Search_Posistion(&ChrShopFile, i, 1)->iValue;
        chrShop.ItemClass = CDBCFile::Search_Posistion(&ChrShopFile, i, 2)->iValue;
        chrShop.IsBind = CDBCFile::Search_Posistion(&ChrShopFile, i, 3)->iValue;
        chrShop.LimitCount = CDBCFile::Search_Posistion(&ChrShopFile, i, 4)->iValue;
        chrShop.Price = CDBCFile::Search_Posistion(&ChrShopFile, i, 5)->iValue;
        chrShop.ConstType = CDBCFile::Search_Posistion(&ChrShopFile, i, 9)->iValue;
        chrShop.QiQinglevel = CDBCFile::Search_Posistion(&ChrShopFile, i, 10)->iValue;
        v1 = std::map<int,CfgChrShop>::operator[](&this->m_chrShops, &chrShop.Index);
        *v1 = chrShop;
      }
    }
  }
  CDBCFile::~CDBCFile(&ChrShopFile);
}


#####################################
void __cdecl CfgData::InitRefreshMonsterCfgListMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::list<RefreshMonsterCfg> *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  RefreshMonsterCfg stu; // [rsp+A0h] [rbp-90h] BYREF
  int32_t nActId; // [rsp+DCh] [rbp-54h] BYREF
  std::vector<Position> __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ActivityServer.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ACT_SHUA_GUAI_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<Position>::vector(&stu.vRevivePosVector);
        nIndex = 0;
        nActId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nStartTime = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDiffTime = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strPos, v1->pString, &v8);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.vRevivePosVector, &__x);
        std::vector<Position>::~vector(&__x);
        std::string::~string(&strPos);
        std::allocator<char>::~allocator(&v8);
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<RefreshMonsterCfg>>::operator[](&this->m_RefreshMonsterCfgListMap, &nActId);
        std::list<RefreshMonsterCfg>::push_back(v2, &stu);
        RefreshMonsterCfg::~RefreshMonsterCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::fetchItem(CfgData *const this, bool bSend)
{
  CfgItem *v2; // rbx
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  CfgItem *v5; // rbx
  CfgItem *v6; // rbx
  CfgItem *v7; // rbx
  CfgItem *v8; // rbx
  CfgItem *v9; // rbx
  CfgItem *v10; // rbx
  CfgItem *v11; // rbx
  CfgItem *v12; // rbx
  CfgItem *v13; // rbx
  const CDBCFile::FIELD *v14; // rax
  const CDBCFile::FIELD *v15; // rax
  const CDBCFile::FIELD *v16; // rax
  const CDBCFile::FIELD *v17; // rax
  CfgItem *v18; // rbx
  CfgItem *v19; // rbx
  CfgItem *v20; // rbx
  CfgItem *v21; // rbx
  CfgItem *v22; // rbx
  CfgItem *v23; // rbx
  CfgItem *v24; // rbx
  CfgItem *v25; // rbx
  CfgItem *v26; // rbx
  CfgItem *v27; // rbx
  CfgItem *v28; // rbx
  CfgItem *v29; // rbx
  CfgItem *v30; // rbx
  CfgItem *v31; // rbx
  CfgItem *v32; // rbx
  const CDBCFile::FIELD *v33; // rax
  CfgItem **v34; // rax
  CfgItemGiftVector *v36; // rbx
  CfgItemGiftVector **v37; // rax
  CfgItemGiftRandomVector *v38; // rbx
  CfgItemGiftRandomVector **v39; // rax
  CDBCFile ItemGiftRandFile; // [rsp+20h] [rbp-310h] BYREF
  CDBCFile ItemGiftFile; // [rsp+B0h] [rbp-280h] BYREF
  CDBCFile ItemFile; // [rsp+140h] [rbp-1F0h] BYREF
  CfgItemTable newItems; // [rsp+1D0h] [rbp-160h] BYREF
  CfgItemGiftRandom itemGiftRandom; // [rsp+200h] [rbp-130h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftRandomVector*> > it; // [rsp+230h] [rbp-100h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftVector*> > it_0; // [rsp+240h] [rbp-F0h] BYREF
  CfgItemGift itemGift; // [rsp+250h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItem*> > it_1; // [rsp+270h] [rbp-C0h] BYREF
  CfgItem *pItem; // [rsp+278h] [rbp-B8h] BYREF
  std::string str; // [rsp+280h] [rbp-B0h] BYREF
  char v51; // [rsp+28Fh] [rbp-A1h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItem*> > __x; // [rsp+290h] [rbp-A0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,CfgItem*> >,bool> v53; // [rsp+2A0h] [rbp-90h]
  std::pair<const int,CfgItem*> v54; // [rsp+2B0h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftVector*> > v55; // [rsp+2C0h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftRandomVector*> > v56; // [rsp+2D0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+2E4h] [rbp-4Ch]
  int32_t iBaseColumnCount; // [rsp+2E8h] [rbp-48h]
  int32_t iBaseTableCount_Gift; // [rsp+2F0h] [rbp-40h]
  int32_t iBaseColumnCount_Gift; // [rsp+2F4h] [rbp-3Ch]
  int32_t iBaseTableCount_GiftRand; // [rsp+2FCh] [rbp-34h]
  int32_t iBaseColumnCount_GiftRand; // [rsp+300h] [rbp-30h]
  int32_t i_1; // [rsp+304h] [rbp-2Ch]
  int32_t i_0; // [rsp+308h] [rbp-28h]
  int32_t i; // [rsp+30Ch] [rbp-24h]

  std::map<int,CfgItem *>::map(&newItems);
  Answer::RwLock::wrlock(&this->m_itemsLock);
  CDBCFile::CDBCFile(&ItemFile, 0);
  if ( !CDBCFile::OpenFromTXT(&ItemFile, "./ServerConfig/Tables/cfg_item.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_item.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&ItemFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&ItemFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i_1 = 0; i_1 < iBaseTableCount; ++i_1 )
      {
        v2 = (CfgItem *)operator new(0xA0u);
        CfgItem::CfgItem(v2);
        pItem = v2;
        v2->id = CDBCFile::Search_Posistion(&ItemFile, i_1, 0)->iValue;
        v3 = CDBCFile::Search_Posistion(&ItemFile, i_1, 1);
        std::string::operator=(&pItem->name, v3->pString);
        v4 = CDBCFile::Search_Posistion(&ItemFile, i_1, 3);
        std::string::operator=(&pItem->desc, v4->pString);
        v5 = pItem;
        v5->type = CDBCFile::Search_Posistion(&ItemFile, i_1, 4)->iValue;
        v6 = pItem;
        v6->level = CDBCFile::Search_Posistion(&ItemFile, i_1, 5)->iValue;
        v7 = pItem;
        v7->grade = CDBCFile::Search_Posistion(&ItemFile, i_1, 6)->iValue;
        v8 = pItem;
        v8->job = CDBCFile::Search_Posistion(&ItemFile, i_1, 7)->iValue;
        v9 = pItem;
        v9->in_value = CDBCFile::Search_Posistion(&ItemFile, i_1, 8)->iValue;
        v10 = pItem;
        v10->out_value = CDBCFile::Search_Posistion(&ItemFile, i_1, 9)->iValue;
        v11 = pItem;
        v11->bind = CDBCFile::Search_Posistion(&ItemFile, i_1, 10)->iValue;
        v12 = pItem;
        v12->combine = CDBCFile::Search_Posistion(&ItemFile, i_1, 11)->iValue;
        v13 = pItem;
        v13->quality = CDBCFile::Search_Posistion(&ItemFile, i_1, 12)->iValue;
        v14 = CDBCFile::Search_Posistion(&ItemFile, i_1, 13);
        std::string::operator=(&pItem->url, v14->pString);
        v15 = CDBCFile::Search_Posistion(&ItemFile, i_1, 14);
        std::string::operator=(&pItem->drop_url, v15->pString);
        v16 = CDBCFile::Search_Posistion(&ItemFile, i_1, 15);
        std::string::operator=(&pItem->effect, v16->pString);
        v17 = CDBCFile::Search_Posistion(&ItemFile, i_1, 16);
        std::string::operator=(&pItem->use_method, v17->pString);
        v18 = pItem;
        v18->downgrade = CDBCFile::Search_Posistion(&ItemFile, i_1, 19)->iValue;
        v19 = pItem;
        v19->group_id = CDBCFile::Search_Posistion(&ItemFile, i_1, 20)->iValue;
        v20 = pItem;
        v20->cd_group = CDBCFile::Search_Posistion(&ItemFile, i_1, 21)->iValue;
        v21 = pItem;
        v21->overlay = CDBCFile::Search_Posistion(&ItemFile, i_1, 22)->iValue;
        v22 = pItem;
        v22->can_sell = CDBCFile::Search_Posistion(&ItemFile, i_1, 23)->iValue;
        v23 = pItem;
        v23->broadcast = CDBCFile::Search_Posistion(&ItemFile, i_1, 24)->iValue;
        v24 = pItem;
        v24->valid_time = CDBCFile::Search_Posistion(&ItemFile, i_1, 25)->iValue;
        v25 = pItem;
        v25->item_Grade = CDBCFile::Search_Posistion(&ItemFile, i_1, 26)->iValue;
        v26 = pItem;
        v26->CanDrop = CDBCFile::Search_Posistion(&ItemFile, i_1, 32)->iValue;
        v27 = pItem;
        v27->useBroadcast = CDBCFile::Search_Posistion(&ItemFile, i_1, 33)->iValue;
        v28 = pItem;
        v28->useInCarrier = CDBCFile::Search_Posistion(&ItemFile, i_1, 35)->iValue;
        v29 = pItem;
        v29->GongGaoId = CDBCFile::Search_Posistion(&ItemFile, i_1, 40)->iValue;
        v30 = pItem;
        v30->KunLingJingHua = CDBCFile::Search_Posistion(&ItemFile, i_1, 42)->iValue;
        v31 = pItem;
        v31->XinMoBag = CDBCFile::Search_Posistion(&ItemFile, i_1, 43)->iValue;
        v32 = pItem;
        std::allocator<char>::allocator(&v51);
        v33 = CDBCFile::Search_Posistion(&ItemFile, i_1, 44);
        std::string::string(&str, v33->pString, &v51);
        v32->RongHeReceovery = CfgData::paraseParam2(this, &str);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v51);
        it_1._M_node = std::map<int,CfgItem *>::find(&this->m_items, &pItem->id)._M_node;
        __x._M_node = std::map<int,CfgItem *>::end(&this->m_items)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgItem *>>::operator==(&it_1, &__x) )
        {
          std::pair<int const,CfgItem *>::pair(&v54, &pItem->id, &pItem);
          v53 = std::map<int,CfgItem *>::insert(&newItems, &v54);
        }
        v34 = std::map<int,CfgItem *>::operator[](&this->m_items, &pItem->id);
        *v34 = pItem;
      }
      Answer::RwLock::unlock(&this->m_itemsLock);
      if ( !std::map<int,CfgItem *>::empty(&newItems) && bSend )
        CfgData::sendNewItems(this, &newItems);
      Answer::RwLock::wrlock(&this->m_itemGiftsLock);
      std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::clear(&this->m_itemGifts);
      CDBCFile::CDBCFile(&ItemGiftFile, 0);
      if ( !CDBCFile::OpenFromTXT(&ItemGiftFile, "./ServerConfig/Tables/cfg_item_gift.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_item_gift.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_Gift = CDBCFile::GetRecordsNum(&ItemGiftFile);
        iBaseColumnCount_Gift = CDBCFile::GetFieldsNum(&ItemGiftFile);
        if ( iBaseColumnCount_Gift > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount_Gift; ++i_0 )
          {
            memset(&itemGift, 0, sizeof(itemGift));
            itemGift.id = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 0)->iValue;
            itemGift.item = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 2)->iValue;
            itemGift.type = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 3)->iValue;
            itemGift.count = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 4)->iValue;
            itemGift.bind = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 5)->iValue;
            itemGift.job = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 6)->iValue;
            itemGift.time = CDBCFile::Search_Posistion(&ItemGiftFile, i_0, 7)->iValue;
            it_0._M_node = std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::find(
                             &this->m_itemGifts,
                             &itemGift.id)._M_node;
            v55._M_node = std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::end(&this->m_itemGifts)._M_node;
            if ( std::_Rb_tree_iterator<std::pair<int const,std::vector<CfgItemGift> *>>::operator==(&it_0, &v55) )
            {
              v36 = (CfgItemGiftVector *)operator new(0x18u);
              std::vector<CfgItemGift>::vector(v36);
              *std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::operator[](
                 &this->m_itemGifts,
                 &itemGift.id) = v36;
            }
            v37 = std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::operator[](
                    &this->m_itemGifts,
                    &itemGift.id);
            std::vector<CfgItemGift>::push_back(*v37, &itemGift);
          }
          Answer::RwLock::unlock(&this->m_itemGiftsLock);
          Answer::RwLock::wrlock(&this->m_itemGiftRandomsLock);
          std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::clear(&this->m_itemGiftRandoms);
          CDBCFile::CDBCFile(&ItemGiftRandFile, 0);
          if ( !CDBCFile::OpenFromTXT(&ItemGiftRandFile, "./ServerConfig/Tables/cfg_item_gift_random.txt") )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open cfg_item_gift_random.txt failed,please check!!");
          }
          else
          {
            iBaseTableCount_GiftRand = CDBCFile::GetRecordsNum(&ItemGiftRandFile);
            iBaseColumnCount_GiftRand = CDBCFile::GetFieldsNum(&ItemGiftRandFile);
            if ( iBaseColumnCount_GiftRand > 0 )
            {
              for ( i = 0; i < iBaseTableCount_GiftRand; ++i )
              {
                itemGiftRandom.id = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 0)->iValue;
                itemGiftRandom.item = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 1)->iValue;
                itemGiftRandom.type = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 2)->iValue;
                itemGiftRandom.count = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 3)->iValue;
                itemGiftRandom.bind = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 4)->iValue;
                itemGiftRandom.static_probability = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 5)->iValue;
                itemGiftRandom.sum_probability = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 6)->iValue;
                itemGiftRandom.job = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 7)->iValue;
                itemGiftRandom.MinLevel = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 8)->iValue;
                itemGiftRandom.MaxLevel = CDBCFile::Search_Posistion(&ItemGiftRandFile, i, 9)->iValue;
                it._M_node = std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::find(
                               &this->m_itemGiftRandoms,
                               &itemGiftRandom.id)._M_node;
                v56._M_node = std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::end(&this->m_itemGiftRandoms)._M_node;
                if ( std::_Rb_tree_iterator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>::operator==(
                       &it,
                       &v56) )
                {
                  v38 = (CfgItemGiftRandomVector *)operator new(0x18u);
                  std::vector<CfgItemGiftRandom>::vector(v38);
                  *std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::operator[](
                     &this->m_itemGiftRandoms,
                     &itemGiftRandom.id) = v38;
                }
                v39 = std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::operator[](
                        &this->m_itemGiftRandoms,
                        &itemGiftRandom.id);
                std::vector<CfgItemGiftRandom>::push_back(*v39, &itemGiftRandom);
              }
              Answer::RwLock::unlock(&this->m_itemGiftRandomsLock);
            }
          }
          CDBCFile::~CDBCFile(&ItemGiftRandFile);
        }
      }
      CDBCFile::~CDBCFile(&ItemGiftFile);
    }
  }
  CDBCFile::~CDBCFile(&ItemFile);
  std::map<int,CfgItem *>::~map(&newItems);
}


#####################################
void __cdecl CfgData::fetchJob(CfgData *const this)
{
  CfgJob *v1; // rax
  CDBCFile JobFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgJob job; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&JobFile, 0);
  if ( !CDBCFile::OpenFromTXT(&JobFile, "./ServerConfig/Tables/cfg_job.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_job.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&JobFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&JobFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        job.id = CDBCFile::Search_Posistion(&JobFile, i, 0)->iValue;
        job.job_task = CDBCFile::Search_Posistion(&JobFile, i, 4)->iValue;
        job.attack_attr = CDBCFile::Search_Posistion(&JobFile, i, 5)->iValue;
        job.base_skill = CDBCFile::Search_Posistion(&JobFile, i, 6)->iValue;
        v1 = std::map<int,CfgJob>::operator[](&this->m_jobs, &job.id);
        *v1 = job;
      }
    }
  }
  CDBCFile::~CDBCFile(&JobFile);
}


#####################################
void __cdecl CfgData::fetchMovie(CfgData *const this)
{
  CfgMovie *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgMovie movie; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t MoveId; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_movie.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_movie.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        movie.id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        MoveId = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        if ( movie.id == MoveId )
        {
          v1 = std::map<int,CfgMovie>::operator[](&this->m_movie, &movie.id);
          v1->id = movie.id;
        }
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::fetchLevelExp(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgLevelExp *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  CfgLevelExp levelExp; // [rsp+A0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+D4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+D8h] [rbp-18h]
  int32_t i; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_level_exp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_level_exp.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        levelExp.level = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        levelExp.upgrade_exp = strtoll(v1->pString, 0, 10);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        levelExp.max_exp = strtoll(v2->pString, 0, 10);
        levelExp.pet_exp = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        levelExp.mount_exp = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        levelExp.vicegeneral_id = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        levelExp.attr_point = CDBCFile::Search_Posistion(&TabFile, i, 6)->iValue;
        levelExp.talent_point = CDBCFile::Search_Posistion(&TabFile, i, 7)->iValue;
        v3 = std::map<int,CfgLevelExp>::operator[](&this->m_levelExps, &levelExp.level);
        *v3 = levelExp;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::fetchLevelAttr(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgLevelAttr *v3; // rax
  CDBCFile LevelAttrFile; // [rsp+10h] [rbp-170h] BYREF
  CfgLevelAttr levelAttr; // [rsp+A0h] [rbp-E0h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-A0h] BYREF
  std::string path; // [rsp+100h] [rbp-80h] BYREF
  char v8; // [rsp+10Fh] [rbp-71h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-70h] BYREF
  char v10; // [rsp+11Fh] [rbp-61h] BYREF
  AttrAddonVector v11; // [rsp+120h] [rbp-60h] BYREF
  std::string v12; // [rsp+140h] [rbp-40h] BYREF
  char v13; // [rsp+14Fh] [rbp-31h] BYREF
  std::string v14; // [rsp+150h] [rbp-30h] BYREF
  char v15; // [rsp+15Bh] [rbp-25h] BYREF
  int __k; // [rsp+15Ch] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+164h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+168h] [rbp-18h]
  int32_t i; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile(&LevelAttrFile, 0);
  if ( !CDBCFile::OpenFromTXT(&LevelAttrFile, "./ServerConfig/Tables/cfg_level_attr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PLAYER_LEVEL_ATTR_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&LevelAttrFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&LevelAttrFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgLevelAttr::CfgLevelAttr(&levelAttr);
        levelAttr.level = CDBCFile::Search_Posistion(&LevelAttrFile, i, 0)->iValue;
        levelAttr.job = CDBCFile::Search_Posistion(&LevelAttrFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v8);
        std::string::string(&path, "./ServerConfig/Tables/cfg_level_attr.txt", &v8);
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&LevelAttrFile, i, 2);
        std::string::string(&addonAttr, v1->pString, &v10);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&levelAttr.addonattr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v10);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v8);
        std::allocator<char>::allocator(&v13);
        std::string::string(&v12, "./ServerConfig/Tables/cfg_level_attr.txt", &v13);
        std::allocator<char>::allocator(&v15);
        v2 = CDBCFile::Search_Posistion(&LevelAttrFile, i, 3);
        std::string::string(&v14, v2->pString, &v15);
        CfgData::paraseAttrAddon(&v11, this, &v14, i, &v12);
        std::vector<AttrAddon>::operator=(&levelAttr.addonPoint, &v11);
        std::vector<AttrAddon>::~vector(&v11);
        std::string::~string(&v14);
        std::allocator<char>::~allocator(&v15);
        std::string::~string(&v12);
        std::allocator<char>::~allocator(&v13);
        __k = (levelAttr.job << 16) | levelAttr.level;
        v3 = std::map<int,CfgLevelAttr>::operator[](&this->m_levelAttrs, &__k);
        CfgLevelAttr::operator=(v3, &levelAttr);
        CfgLevelAttr::~CfgLevelAttr(&levelAttr);
      }
    }
  }
  CDBCFile::~CDBCFile(&LevelAttrFile);
}


#####################################
void __cdecl CfgData::fetchMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgMap *v2; // rax
  CfgMap map; // [rsp+10h] [rbp-140h] BYREF
  CDBCFile MapFile; // [rsp+A0h] [rbp-B0h] BYREF
  int32_t iBaseTableCount; // [rsp+134h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+138h] [rbp-18h]
  int32_t i; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&MapFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MapFile, "./ServerConfig/Tables/cfg_map.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MapFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MapFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgMap::CfgMap(&map);
        map.id = CDBCFile::Search_Posistion(&MapFile, i, 0)->iValue;
        v1 = CDBCFile::Search_Posistion(&MapFile, i, 1);
        std::string::operator=(&map.name, v1->pString);
        map.type = CDBCFile::Search_Posistion(&MapFile, i, 2)->iValue;
        map.param = CDBCFile::Search_Posistion(&MapFile, i, 3)->iValue;
        map.width = CDBCFile::Search_Posistion(&MapFile, i, 4)->iValue;
        map.height = CDBCFile::Search_Posistion(&MapFile, i, 5)->iValue;
        map.revive = CDBCFile::Search_Posistion(&MapFile, i, 6)->iValue;
        map.pk_mode = CDBCFile::Search_Posistion(&MapFile, i, 7)->iValue;
        map.anti_protect = CDBCFile::Search_Posistion(&MapFile, i, 8)->iValue;
        map.isMount = CDBCFile::Search_Posistion(&MapFile, i, 9)->iValue;
        map.isFly = CDBCFile::Search_Posistion(&MapFile, i, 10)->iValue;
        map.isVicegeneral = CDBCFile::Search_Posistion(&MapFile, i, 11)->iValue;
        map.player_level = CDBCFile::Search_Posistion(&MapFile, i, 12)->iValue;
        map.player_level_max = CDBCFile::Search_Posistion(&MapFile, i, 13)->iValue;
        map.team_member = CDBCFile::Search_Posistion(&MapFile, i, 14)->iValue;
        map.hide_mini = CDBCFile::Search_Posistion(&MapFile, i, 15)->iValue;
        map.runnerId = CDBCFile::Search_Posistion(&MapFile, i, 23)->iValue;
        map.jump = CDBCFile::Search_Posistion(&MapFile, i, 30)->iValue;
        map.GongGaoId = CDBCFile::Search_Posistion(&MapFile, i, 33)->iValue;
        map.reviveTime = CDBCFile::Search_Posistion(&MapFile, i, 35)->iValue;
        map.pvp = CDBCFile::Search_Posistion(&MapFile, i, 36)->iValue;
        map.cross = CDBCFile::Search_Posistion(&MapFile, i, 38)->iValue;
        map.x = CDBCFile::Search_Posistion(&MapFile, i, 44)->iValue;
        map.y = CDBCFile::Search_Posistion(&MapFile, i, 45)->iValue;
        map.drop_rate = CDBCFile::Search_Posistion(&MapFile, i, 47)->iValue;
        map.XingMaiLevel = CDBCFile::Search_Posistion(&MapFile, i, 48)->iValue;
        map.SuitId = CDBCFile::Search_Posistion(&MapFile, i, 49)->iValue;
        map.JueWeiLevel = CDBCFile::Search_Posistion(&MapFile, i, 50)->iValue;
        map.VipLevel = CDBCFile::Search_Posistion(&MapFile, i, 51)->iValue;
        map.NeedBroadcast = CDBCFile::Search_Posistion(&MapFile, i, 54)->iValue;
        map.MapCanUsePet = CDBCFile::Search_Posistion(&MapFile, i, 55)->iValue;
        map.SignOut = CDBCFile::Search_Posistion(&MapFile, i, 56)->iValue;
        map.Rdx = CDBCFile::Search_Posistion(&MapFile, i, 58)->iValue;
        map.Refresh = CDBCFile::Search_Posistion(&MapFile, i, 60)->iValue;
        map.CanRand = CDBCFile::Search_Posistion(&MapFile, i, 61)->iValue;
        map.LimitDay = CDBCFile::Search_Posistion(&MapFile, i, 62)->iValue;
        map.XinMoAct = CDBCFile::Search_Posistion(&MapFile, i, 63)->iValue;
        v2 = std::map<int,CfgMap>::operator[](&this->m_maps, &map.id);
        CfgMap::operator=(v2, &map);
        CfgMap::~CfgMap(&map);
      }
    }
  }
  CDBCFile::~CDBCFile(&MapFile);
}


#####################################
void __cdecl CfgData::fetchMapMonster(CfgData *const this)
{
  std::vector<CfgMapMonster> *v1; // rax
  CfgMapMonster *v2; // rax
  CDBCFile MapMonsterFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgMapMonster mapmonster; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&MapMonsterFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MapMonsterFile, "./ServerConfig/Tables/cfg_map_monster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map_monster.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MapMonsterFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MapMonsterFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&mapmonster, 0, sizeof(mapmonster));
        mapmonster.id = CDBCFile::Search_Posistion(&MapMonsterFile, i, 0)->iValue;
        mapmonster.mapid = CDBCFile::Search_Posistion(&MapMonsterFile, i, 1)->iValue;
        mapmonster.monsterid = CDBCFile::Search_Posistion(&MapMonsterFile, i, 2)->iValue;
        mapmonster.x = CDBCFile::Search_Posistion(&MapMonsterFile, i, 3)->iValue;
        mapmonster.y = CDBCFile::Search_Posistion(&MapMonsterFile, i, 4)->iValue;
        mapmonster.hide = CDBCFile::Search_Posistion(&MapMonsterFile, i, 5)->iValue;
        mapmonster.side = CDBCFile::Search_Posistion(&MapMonsterFile, i, 6)->iValue;
        mapmonster.boss = CDBCFile::Search_Posistion(&MapMonsterFile, i, 7)->iValue;
        mapmonster.Day = CDBCFile::Search_Posistion(&MapMonsterFile, i, 8)->iValue;
        v1 = std::map<int,std::vector<CfgMapMonster>>::operator[](&this->m_mapMonsters, &mapmonster.mapid);
        std::vector<CfgMapMonster>::push_back(v1, &mapmonster);
        v2 = std::map<int,CfgMapMonster>::operator[](&this->m_CfgMapMonsters, &mapmonster.id);
        *v2 = mapmonster;
      }
    }
  }
  CDBCFile::~CDBCFile(&MapMonsterFile);
}


#####################################
void __cdecl CfgData::fetchMapPlant(CfgData *const this)
{
  std::vector<CfgMapPlant> *v1; // rax
  CfgMapPlant *v2; // rax
  CDBCFile MapPlantFile; // [rsp+10h] [rbp-D0h] BYREF
  int32_t id; // [rsp+ACh] [rbp-34h] BYREF
  CfgMapPlant mapPlant; // [rsp+B0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&MapPlantFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MapPlantFile, "./ServerConfig/Tables/cfg_map_plant.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map_plant.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MapPlantFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MapPlantFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        id = CDBCFile::Search_Posistion(&MapPlantFile, i, 0)->iValue;
        mapPlant.mapid = CDBCFile::Search_Posistion(&MapPlantFile, i, 1)->iValue;
        mapPlant.plantid = CDBCFile::Search_Posistion(&MapPlantFile, i, 2)->iValue;
        mapPlant.x = CDBCFile::Search_Posistion(&MapPlantFile, i, 3)->iValue;
        mapPlant.y = CDBCFile::Search_Posistion(&MapPlantFile, i, 4)->iValue;
        v1 = std::map<int,std::vector<CfgMapPlant>>::operator[](&this->m_mapPlants, &mapPlant.mapid);
        std::vector<CfgMapPlant>::push_back(v1, &mapPlant);
        v2 = std::map<int,CfgMapPlant>::operator[](&this->m_mMapPlants, &id);
        *v2 = mapPlant;
      }
    }
  }
  CDBCFile::~CDBCFile(&MapPlantFile);
}


#####################################
void __cdecl CfgData::fetchMapRegion(CfgData *const this)
{
  CfgMapRegion *v1; // rax
  std::vector<CfgMapRegion> *v2; // rax
  CDBCFile MapRegionFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgMapRegion mapRegion; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&MapRegionFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MapRegionFile, "./ServerConfig/Tables/cfg_map_region.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map_region.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MapRegionFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MapRegionFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        mapRegion.id = CDBCFile::Search_Posistion(&MapRegionFile, i, 0)->iValue;
        mapRegion.mapid = CDBCFile::Search_Posistion(&MapRegionFile, i, 2)->iValue;
        mapRegion.min_x = CDBCFile::Search_Posistion(&MapRegionFile, i, 3)->iValue;
        mapRegion.min_y = CDBCFile::Search_Posistion(&MapRegionFile, i, 4)->iValue;
        mapRegion.max_x = CDBCFile::Search_Posistion(&MapRegionFile, i, 5)->iValue;
        mapRegion.max_y = CDBCFile::Search_Posistion(&MapRegionFile, i, 6)->iValue;
        mapRegion.type = CDBCFile::Search_Posistion(&MapRegionFile, i, 7)->iValue;
        mapRegion.mId = CDBCFile::Search_Posistion(&MapRegionFile, i, 9)->iValue;
        v1 = std::map<int,CfgMapRegion>::operator[](&this->m_mapRegions, &mapRegion.id);
        *v1 = mapRegion;
        v2 = std::map<int,std::vector<CfgMapRegion>>::operator[](&this->m_mapRegionsByMapId, &mapRegion.mapid);
        std::vector<CfgMapRegion>::push_back(v2, &mapRegion);
      }
    }
  }
  CDBCFile::~CDBCFile(&MapRegionFile);
}


#####################################
void __cdecl CfgData::fetchMonster(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  std::string *v7; // rax
  const char *v8; // rax
  CfgMonster *v9; // rax
  const CDBCFile::FIELD *v10; // rax
  MemChrBag v11; // [rsp+0h] [rbp-4B0h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-488h]
  CfgMonster monster; // [rsp+30h] [rbp-480h] BYREF
  CDBCFile MonsterBroadcastFile; // [rsp+2D0h] [rbp-1E0h] BYREF
  CDBCFile MonsterFile; // [rsp+360h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+3F0h] [rbp-C0h] BYREF
  StringVector vRand; // [rsp+400h] [rbp-B0h] BYREF
  std::string randtypes; // [rsp+420h] [rbp-90h] BYREF
  char v19; // [rsp+42Fh] [rbp-81h] BYREF
  std::string strSkill; // [rsp+430h] [rbp-80h] BYREF
  char v21; // [rsp+43Fh] [rbp-71h] BYREF
  std::string v22; // [rsp+440h] [rbp-70h] BYREF
  char v23; // [rsp+44Fh] [rbp-61h] BYREF
  std::string strItem; // [rsp+450h] [rbp-60h] BYREF
  char v25; // [rsp+45Fh] [rbp-51h] BYREF
  std::string delims; // [rsp+460h] [rbp-50h] BYREF
  char v27; // [rsp+46Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+470h] [rbp-40h] BYREF
  int __x; // [rsp+478h] [rbp-38h] BYREF
  int32_t iBaseTableCount; // [rsp+480h] [rbp-30h]
  int32_t iBaseColumnCount; // [rsp+484h] [rbp-2Ch]
  int32_t iBaseTableCountBroadcast; // [rsp+48Ch] [rbp-24h]
  int32_t iBaseColumnCountBroadcast; // [rsp+490h] [rbp-20h]
  int32_t i; // [rsp+494h] [rbp-1Ch]
  int32_t nIndex; // [rsp+498h] [rbp-18h]
  int32_t i_0; // [rsp+49Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile(&MonsterFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MonsterFile, "./ServerConfig/Tables/Monster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MonsterFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MonsterFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monster, 0, 668);
        std::vector<int>::vector(&monster.rand_types);
        monster.mid = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        monster.group_id = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.level = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.quality = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[1] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[2] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[3] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[4] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[5] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[6] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[7] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[8] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[9] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[10] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[11] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[12] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[13] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[14] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[15] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[16] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[17] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[18] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[19] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[20] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[21] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[22] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[23] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[24] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[25] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[26] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[27] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[28] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.rand_count = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v19);
        v1 = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex);
        std::string::string(&randtypes, v1->pString, &v19);
        std::allocator<char>::~allocator(&v19);
        monster.exp = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.type = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.revive_time = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.skill_id = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v21);
        v2 = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex);
        std::string::string(&strSkill, v2->pString, &v21);
        CfgData::parseMonsterSkill(thisa, monster.mid, (MonsterSkill (*const)[10])monster.unique_skill, &strSkill);
        std::string::~string(&strSkill);
        std::allocator<char>::~allocator(&v21);
        ++nIndex;
        std::allocator<char>::allocator(&v23);
        v3 = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex);
        std::string::string(&v22, v3->pString, &v23);
        CfgData::parseMonsterSkill(thisa, monster.mid, (MonsterSkill (*const)[10])monster.random_skill, &v22);
        std::string::~string(&v22);
        std::allocator<char>::~allocator(&v23);
        monster.hpPercent = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.ai = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 9;
        monster.broadcast = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        monster.drop_free = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        nIndex += 2;
        monster.boss_sign = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        nIndex += 5;
        monster.BossSocre = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        monster.TaskShare = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        nIndex += 4;
        monster.camp = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        nIndex += 2;
        monster.kill_point = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        monster.revive_skin = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        ++nIndex;
        monster.PortalRatio = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.PortalId = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.PortalDuration = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        monster.prestige = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.dust = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.is_building = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.PureDamage = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        monster.IfCurse = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        monster.Score = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.IsShowOwner = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        monster.DiligenceType = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        monster.DiligenceValue = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex++)->iValue;
        v4 = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex);
        monster.MonsterHp = strtoll(v4->pString, 0, 10);
        monster.CanTunshi = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.Mid2 = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.FamilyValue = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        monster.vAttr[41] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[42] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[43] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[44] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.IsXinMoMonster = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.QieGe = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[49] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.Energy = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v25);
        v5 = CDBCFile::Search_Posistion(&MonsterFile, i, nIndex);
        std::string::string(&strItem, v5->pString, &v25);
        CItemHelper::parseItemString(&v11, &strItem);
        monster.cItem = v11;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v25);
        monster.IsSunAndMoon = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        monster.corpse_time = 3000;
        if ( (unsigned __int8)std::string::empty(&randtypes) != 1 && std::operator!=<char>(&randtypes, "-1") )
        {
          std::allocator<char>::allocator(&v27);
          std::string::string(&delims, ":", &v27);
          Answer::StringUtility::split(&vRand, &randtypes, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v27);
          for ( iter._M_current = std::vector<std::string>::begin(&vRand)._M_current;
                ;
                __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<std::string>::end(&vRand)._M_current;
            if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
              break;
            v7 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
            v8 = (const char *)std::string::c_str(v7);
            __x = atoi(v8);
            std::vector<int>::push_back(&monster.rand_types, &__x);
          }
          std::vector<std::string>::~vector(&vRand);
        }
        v9 = std::map<int,CfgMonster>::operator[](&thisa->m_monsters, &monster.mid);
        CfgMonster::operator=(v9, &monster);
        std::string::~string(&randtypes);
        CfgMonster::~CfgMonster(&monster);
      }
      CDBCFile::CDBCFile(&MonsterBroadcastFile, 0);
      if ( !CDBCFile::OpenFromTXT(&MonsterBroadcastFile, "./ServerConfig/Tables/cfg_monster_broadcast.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_broadcast.txt failed,please check!!");
      }
      else
      {
        iBaseTableCountBroadcast = CDBCFile::GetRecordsNum(&MonsterBroadcastFile);
        iBaseColumnCountBroadcast = CDBCFile::GetFieldsNum(&MonsterBroadcastFile);
        if ( iBaseColumnCountBroadcast > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCountBroadcast; ++i_0 )
          {
            v10 = CDBCFile::Search_Posistion(&MonsterBroadcastFile, i_0, 1);
            std::vector<int>::push_back(&thisa->m_monsterBroadcasts, (const int *const)v10);
          }
        }
      }
      CDBCFile::~CDBCFile(&MonsterBroadcastFile);
    }
  }
  CDBCFile::~CDBCFile(&MonsterFile);
}


#####################################
void __cdecl CfgData::fetchMonsterAI(CfgData *const this)
{
  CfgMonsterAI *v1; // rax
  CDBCFile MonsterFile; // [rsp+10h] [rbp-F0h] BYREF
  CfgMonsterAI ai; // [rsp+A0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&MonsterFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MonsterFile, "./ServerConfig/Tables/MonsterAi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_AI_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MonsterFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MonsterFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&ai, 0, sizeof(ai));
        ai.id = CDBCFile::Search_Posistion(&MonsterFile, i, 0)->iValue;
        ai.style = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.target = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.escape_hp = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.view_range = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.move_range = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.rest_range = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.rest_time_min = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.rest_time_max = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.rest_ratio = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.run_distance = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.run_range = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.run_cd = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ai.pursuit_range = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,CfgMonsterAI>::operator[](&this->m_mMonsterAI, &ai.id);
        *v1 = ai;
      }
    }
  }
  CDBCFile::~CDBCFile(&MonsterFile);
}


#####################################
void __cdecl CfgData::fetchMonsterAdjustTable(CfgData *const this)
{
  int v1; // ebx
  CfgMonsterAdjust monster; // [rsp+20h] [rbp-3A0h] BYREF
  CDBCFile MonsterFile; // [rsp+100h] [rbp-2C0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,CfgMonsterAdjust> >,bool> v4; // [rsp+190h] [rbp-230h]
  _BYTE v5[224]; // [rsp+1A0h] [rbp-220h] BYREF
  std::pair<int,int> __a; // [rsp+280h] [rbp-140h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,CfgMonsterAdjust> >,bool> v7; // [rsp+290h] [rbp-130h]
  _BYTE v8[224]; // [rsp+2A0h] [rbp-120h] BYREF
  std::pair<int,int> v9; // [rsp+380h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+38Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+390h] [rbp-30h]
  int32_t i; // [rsp+394h] [rbp-2Ch]
  int32_t nIndex; // [rsp+398h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+3A0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+3A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+3A8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+3ACh] [rbp-14h]

  CDBCFile::CDBCFile(&MonsterFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MonsterFile, "./ServerConfig/Tables/MonsterAdjust.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_ADJUST_TABLE failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MonsterFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MonsterFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monster, 0, sizeof(monster));
        monster.mid = CDBCFile::Search_Posistion(&MonsterFile, i, 0)->iValue;
        monster.adj_level = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.level = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[1] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[2] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[3] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[4] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[5] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[6] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[7] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[8] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[9] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[10] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[11] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[12] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[13] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[14] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[15] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[16] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[17] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[18] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[19] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[20] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[21] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[22] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[23] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[24] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[25] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[26] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[27] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[28] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[41] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[42] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[43] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        monster.vAttr[44] = CDBCFile::Search_Posistion(&MonsterFile, i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(monster.mid, monster.adj_level);
        std::pair<std::pair const<int,int>,CfgMonsterAdjust>::pair(
          (std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v5,
          &__a,
          &monster);
        v4 = std::map<std::pair<int,int>,CfgMonsterAdjust>::insert(
               &this->m_mMonsterAdjust,
               (const std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v5);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&MonsterFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&MonsterFile, 0);
    if ( !CDBCFile::OpenFromTXT(&MonsterFile, "./ServerConfig/Tables/BossGrow.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_GROW_TABLE failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&MonsterFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&MonsterFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&monster, 0, sizeof(monster));
          monster.mid = CDBCFile::Search_Posistion(&MonsterFile, i_0, 0)->iValue;
          monster.adj_level = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.exp = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          monster.vAttr[1] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[2] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[3] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[4] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[5] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[6] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[7] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[8] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[9] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[10] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[11] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[12] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[13] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[14] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[15] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[16] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[17] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[18] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[19] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[20] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[21] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[22] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[23] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[24] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[25] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[26] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[27] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[28] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[41] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[42] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[43] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          monster.vAttr[44] = CDBCFile::Search_Posistion(&MonsterFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          v9 = std::make_pair<int,int>(monster.mid, monster.adj_level);
          std::pair<std::pair const<int,int>,CfgMonsterAdjust>::pair(
            (std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v8,
            &v9,
            &monster);
          v7 = std::map<std::pair<int,int>,CfgMonsterAdjust>::insert(
                 &this->m_mMonsterAdjust,
                 (const std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v8);
        }
      }
    }
    CDBCFile::~CDBCFile(&MonsterFile);
  }
}


#####################################
void __cdecl CfgData::fetchMonsterDropGroup(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::vector<CfgMonsterDropGroup> *v3; // rax
  CDBCFile MonsterDropFile; // [rsp+10h] [rbp-110h] BYREF
  CfgMonsterDropGroup monsterDropGroup; // [rsp+A0h] [rbp-80h] BYREF
  std::string p_StringTime; // [rsp+E0h] [rbp-40h] BYREF
  char v7; // [rsp+EFh] [rbp-31h] BYREF
  std::string v8; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&MonsterDropFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MonsterDropFile, "./ServerConfig/Tables/cfg_monster_drop_group.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_drop_group.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MonsterDropFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MonsterDropFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monsterDropGroup, 0, sizeof(monsterDropGroup));
        monsterDropGroup.group_id = CDBCFile::Search_Posistion(&MonsterDropFile, i, 0)->iValue;
        monsterDropGroup.item_id = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.item_class = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.item_count = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.bind_type = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.weight = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.probability = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.cost_type = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.cost_value = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.limit_time = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.daily_limit = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&MonsterDropFile, i, nIndex);
        std::string::string(&p_StringTime, v1->pString, &v7);
        monsterDropGroup.start_date = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v2 = CDBCFile::Search_Posistion(&MonsterDropFile, i, nIndex);
        std::string::string(&v8, v2->pString, &v9);
        monsterDropGroup.end_date = Answer::DayTime::StringToIntTime(&v8);
        std::string::~string(&v8);
        std::allocator<char>::~allocator(&v9);
        monsterDropGroup.record = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        monsterDropGroup.festival_group = CDBCFile::Search_Posistion(&MonsterDropFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,std::vector<CfgMonsterDropGroup>>::operator[](
               &this->m_monsterDropGroups,
               &monsterDropGroup.group_id);
        std::vector<CfgMonsterDropGroup>::push_back(v3, &monsterDropGroup);
      }
    }
  }
  CDBCFile::~CDBCFile(&MonsterDropFile);
}


#####################################
void __cdecl CfgData::fetchMonsterGroupDrop(CfgData *const this)
{
  std::vector<CfgMonsterGroupDrop> *v1; // rax
  CDBCFile MonsterGroupFile; // [rsp+10h] [rbp-E0h] BYREF
  CfgMonsterGroupDrop monsterGroupDrop; // [rsp+A0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&MonsterGroupFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MonsterGroupFile, "./ServerConfig/Tables/cfg_monster_group_drop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_group_drop.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MonsterGroupFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MonsterGroupFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monsterGroupDrop, 0, sizeof(monsterGroupDrop));
        monsterGroupDrop.mid = CDBCFile::Search_Posistion(&MonsterGroupFile, i, 0)->iValue;
        monsterGroupDrop.group_id = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.probability = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.begin_time = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.end_time = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.repeat = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.job = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.grow_level = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.dropType = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.bind_type = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.hard = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.quality = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.world_event = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        monsterGroupDrop.DropLimit = CDBCFile::Search_Posistion(&MonsterGroupFile, i, ++nIndex)->iValue;
        ++nIndex;
        if ( monsterGroupDrop.begin_time >= 0x5A0u
          || monsterGroupDrop.end_time >= 0x5A0u
          || monsterGroupDrop.begin_time > monsterGroupDrop.end_time
          || monsterGroupDrop.repeat <= 0 )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "wrong cfg_monster_group_drop data with mid = %d, group_id = %d\n",
            monsterGroupDrop.mid,
            monsterGroupDrop.group_id);
        }
        v1 = std::map<int,std::vector<CfgMonsterGroupDrop>>::operator[](
               &this->m_monsterGroupDrops,
               &monsterGroupDrop.mid);
        std::vector<CfgMonsterGroupDrop>::push_back(v1, &monsterGroupDrop);
      }
    }
  }
  CDBCFile::~CDBCFile(&MonsterGroupFile);
}


#####################################
void __cdecl CfgData::fetchMonsterTaskDrop(CfgData *const this)
{
  std::vector<CfgMonsterTaskDrop> *v1; // rax
  CDBCFile MonsterTaskFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgMonsterTaskDrop monsterTaskDrop; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&MonsterTaskFile, 0);
  if ( !CDBCFile::OpenFromTXT(&MonsterTaskFile, "./ServerConfig/Tables/cfg_monster_task_drop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_task_drop.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&MonsterTaskFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&MonsterTaskFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        *(_QWORD *)&monsterTaskDrop.mid = 0;
        *(_QWORD *)&monsterTaskDrop.item = 0;
        monsterTaskDrop.mid = CDBCFile::Search_Posistion(&MonsterTaskFile, i, 0)->iValue;
        monsterTaskDrop.tid = CDBCFile::Search_Posistion(&MonsterTaskFile, i, 1)->iValue;
        monsterTaskDrop.item = CDBCFile::Search_Posistion(&MonsterTaskFile, i, 2)->iValue;
        monsterTaskDrop.probability = CDBCFile::Search_Posistion(&MonsterTaskFile, i, 3)->iValue;
        v1 = std::map<int,std::vector<CfgMonsterTaskDrop>>::operator[](&this->m_monsterTaskDrops, &monsterTaskDrop.mid);
        std::vector<CfgMonsterTaskDrop>::push_back(v1, &monsterTaskDrop);
      }
    }
  }
  CDBCFile::~CDBCFile(&MonsterTaskFile);
}


#####################################
void __cdecl CfgData::fetchNpc(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  const char *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  size_t v7; // rbx
  const CDBCFile::FIELD *v8; // rax
  std::string *v9; // rax
  size_t v10; // rbx
  const CDBCFile::FIELD *v11; // rax
  std::string *v12; // rbx
  std::string *v13; // rax
  const char *v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  std::string *v17; // rax
  const char *v18; // rax
  CfgNpc *v19; // rax
  CfgNpcAirport *v20; // rax
  CDBCFile TabFileAir; // [rsp+10h] [rbp-360h] BYREF
  CDBCFile TabFile; // [rsp+A0h] [rbp-2D0h] BYREF
  CfgNpcAirport airport; // [rsp+130h] [rbp-240h] BYREF
  int iValue; // [rsp+150h] [rbp-220h]
  int v25; // [rsp+154h] [rbp-21Ch]
  int v26; // [rsp+158h] [rbp-218h]
  int v27; // [rsp+15Ch] [rbp-214h]
  std::vector<int> v28; // [rsp+160h] [rbp-210h] BYREF
  char v29; // [rsp+178h] [rbp-1F8h]
  std::vector<std::string> v30; // [rsp+180h] [rbp-1F0h] BYREF
  std::vector<CfgDungeonNpcCost> v31; // [rsp+198h] [rbp-1D8h] BYREF
  CfgDungeonNpcCost NpcCost; // [rsp+1B0h] [rbp-1C0h] BYREF
  StringVector CostItem; // [rsp+1C0h] [rbp-1B0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+1E0h] [rbp-190h] BYREF
  StringVector vpf; // [rsp+1F0h] [rbp-180h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+210h] [rbp-160h] BYREF
  StringVector CostVector; // [rsp+220h] [rbp-150h] BYREF
  std::string platform; // [rsp+240h] [rbp-130h] BYREF
  StringVector vparam; // [rsp+250h] [rbp-120h] BYREF
  std::string param; // [rsp+270h] [rbp-100h] BYREF
  StringVector mapids; // [rsp+280h] [rbp-F0h] BYREF
  std::string delims; // [rsp+2A0h] [rbp-D0h] BYREF
  char v43; // [rsp+2AFh] [rbp-C1h] BYREF
  std::string str; // [rsp+2B0h] [rbp-C0h] BYREF
  char v45; // [rsp+2BFh] [rbp-B1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+2C0h] [rbp-B0h] BYREF
  int __x; // [rsp+2C8h] [rbp-A8h] BYREF
  char v48; // [rsp+2CFh] [rbp-A1h] BYREF
  std::string v49; // [rsp+2D0h] [rbp-A0h] BYREF
  char v50; // [rsp+2E7h] [rbp-89h] BYREF
  int v51; // [rsp+2E8h] [rbp-88h] BYREF
  char v52; // [rsp+2EFh] [rbp-81h] BYREF
  std::string v53; // [rsp+2F0h] [rbp-80h] BYREF
  char v54; // [rsp+2FFh] [rbp-71h] BYREF
  std::string v55; // [rsp+300h] [rbp-70h] BYREF
  char v56; // [rsp+30Fh] [rbp-61h] BYREF
  std::string v57; // [rsp+310h] [rbp-60h] BYREF
  char v58; // [rsp+31Fh] [rbp-51h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v59; // [rsp+320h] [rbp-50h] BYREF
  std::string v60; // [rsp+330h] [rbp-40h] BYREF
  char v61; // [rsp+346h] [rbp-2Ah] BYREF
  bool ret; // [rsp+347h] [rbp-29h]
  int32_t iBaseTableCount; // [rsp+348h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+34Ch] [rbp-24h]
  int32_t i; // [rsp+350h] [rbp-20h]
  uint32_t j; // [rsp+354h] [rbp-1Ch]
  uint32_t j_0; // [rsp+358h] [rbp-18h]
  int32_t i_0; // [rsp+35Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  ret = CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_npc.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_npc.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgNpc::CfgNpc((CfgNpc *const)&airport);
        airport.id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        airport.npcid = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        std::allocator<char>::allocator(&v43);
        std::string::string(&delims, "|", &v43);
        std::allocator<char>::allocator(&v45);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 6);
        std::string::string(&str, v1->pString, &v45);
        Answer::StringUtility::split(&mapids, &str, &delims, 0);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v45);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v43);
        for ( it._M_current = std::vector<std::string>::begin(&mapids)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&mapids)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v3 = (const char *)std::string::c_str(v2);
          __x = atoi(v3);
          std::vector<int>::push_back((std::vector<int> *const)&airport.player_kingdom, &__x);
        }
        iValue = CDBCFile::Search_Posistion(&TabFile, i, 7)->iValue;
        v25 = CDBCFile::Search_Posistion(&TabFile, i, 8)->iValue;
        v26 = CDBCFile::Search_Posistion(&TabFile, i, 9)->iValue;
        v27 = CDBCFile::Search_Posistion(&TabFile, i, 10)->iValue;
        std::allocator<char>::allocator(&v48);
        v4 = CDBCFile::Search_Posistion(&TabFile, i, 21);
        std::string::string(&param, v4->pString, &v48);
        std::allocator<char>::~allocator(&v48);
        std::allocator<char>::allocator(&v50);
        std::string::string(&v49, ":", &v50);
        Answer::StringUtility::split(&vparam, &param, &v49, 0);
        std::string::~string(&v49);
        std::allocator<char>::~allocator(&v50);
        for ( j = 0; ; ++j )
        {
          v7 = j;
          if ( v7 >= std::vector<std::string>::size(&vparam) )
            break;
          v5 = std::vector<std::string>::operator[](&vparam, j);
          v6 = (const char *)std::string::c_str(v5);
          v51 = atoi(v6);
          std::vector<int>::push_back(&v28, &v51);
        }
        v29 = CDBCFile::Search_Posistion(&TabFile, i, 23)->iValue;
        std::allocator<char>::allocator(&v52);
        v8 = CDBCFile::Search_Posistion(&TabFile, i, 25);
        std::string::string(&platform, v8->pString, &v52);
        std::allocator<char>::~allocator(&v52);
        if ( std::operator!=<char>(&platform, "0") )
        {
          std::allocator<char>::allocator(&v54);
          std::string::string(&v53, "|", &v54);
          Answer::StringUtility::split(&vpf, &platform, &v53, 0);
          std::string::~string(&v53);
          std::allocator<char>::~allocator(&v54);
          for ( j_0 = 0; ; ++j_0 )
          {
            v10 = j_0;
            if ( v10 >= std::vector<std::string>::size(&vpf) )
              break;
            v9 = std::vector<std::string>::operator[](&vpf, j_0);
            std::vector<std::string>::push_back(&v30, v9);
          }
          std::vector<std::string>::~vector(&vpf);
        }
        std::allocator<char>::allocator(&v56);
        std::string::string(&v55, "|", &v56);
        std::allocator<char>::allocator(&v58);
        v11 = CDBCFile::Search_Posistion(&TabFile, i, 27);
        std::string::string(&v57, v11->pString, &v58);
        Answer::StringUtility::split(&CostVector, &v57, &v55, 0);
        std::string::~string(&v57);
        std::allocator<char>::~allocator(&v58);
        std::string::~string(&v55);
        std::allocator<char>::~allocator(&v56);
        for ( iter._M_current = std::vector<std::string>::begin(&CostVector)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter, 0) )
        {
          v59._M_current = std::vector<std::string>::end(&CostVector)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &v59) )
            break;
          std::allocator<char>::allocator(&v61);
          std::string::string(&v60, ":", &v61);
          v12 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
          Answer::StringUtility::split(&CostItem, v12, &v60, 0);
          std::string::~string(&v60);
          std::allocator<char>::~allocator(&v61);
          *(_QWORD *)&NpcCost.ItemType = 0;
          NpcCost.ItemCount = 0;
          if ( std::vector<std::string>::size(&CostItem) == 3 )
          {
            v13 = std::vector<std::string>::operator[](&CostItem, 0);
            v14 = (const char *)std::string::c_str(v13);
            NpcCost.ItemType = atoi(v14);
            v15 = std::vector<std::string>::operator[](&CostItem, 1u);
            v16 = (const char *)std::string::c_str(v15);
            NpcCost.ItemId = atoi(v16);
            v17 = std::vector<std::string>::operator[](&CostItem, 2u);
            v18 = (const char *)std::string::c_str(v17);
            NpcCost.ItemCount = atoi(v18);
          }
          std::vector<CfgDungeonNpcCost>::push_back(&v31, &NpcCost);
          std::vector<std::string>::~vector(&CostItem);
        }
        v19 = std::map<int,CfgNpc>::operator[](&this->m_npcs, &airport.id);
        CfgNpc::operator=(v19, (const CfgNpc *const)&airport);
        std::vector<std::string>::~vector(&CostVector);
        std::string::~string(&platform);
        std::vector<std::string>::~vector(&vparam);
        std::string::~string(&param);
        std::vector<std::string>::~vector(&mapids);
        CfgNpc::~CfgNpc((CfgNpc *const)&airport);
      }
      CDBCFile::CDBCFile(&TabFileAir, 0);
      ret = CDBCFile::OpenFromTXT(&TabFileAir, "./ServerConfig/Tables/cfg_npc_airport.txt");
      if ( !ret )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_npc_airport.txt failed,please check!!!\n");
      }
      else
      {
        iBaseTableCount = CDBCFile::GetRecordsNum(&TabFileAir);
        iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFileAir);
        if ( iBaseColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount; ++i_0 )
          {
            airport.id = CDBCFile::Search_Posistion(&TabFileAir, i_0, 0)->iValue;
            airport.npcid = CDBCFile::Search_Posistion(&TabFileAir, i_0, 1)->iValue;
            airport.player_kingdom = CDBCFile::Search_Posistion(&TabFileAir, i_0, 3)->iValue;
            airport.kingdom_id = CDBCFile::Search_Posistion(&TabFileAir, i_0, 4)->iValue;
            airport.map_id = CDBCFile::Search_Posistion(&TabFileAir, i_0, 5)->iValue;
            airport.map_x = CDBCFile::Search_Posistion(&TabFileAir, i_0, 6)->iValue;
            airport.map_y = CDBCFile::Search_Posistion(&TabFileAir, i_0, 7)->iValue;
            airport.cost = CDBCFile::Search_Posistion(&TabFileAir, i_0, 8)->iValue;
            v20 = std::map<int,CfgNpcAirport>::operator[](&this->m_npcAirports, &airport.id);
            *v20 = airport;
          }
        }
      }
      CDBCFile::~CDBCFile(&TabFileAir);
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::fetchPlant(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  std::string *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  CfgPlant *v11; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-250h] BYREF
  CfgPlant plant; // [rsp+A0h] [rbp-1C0h] BYREF
  StringVector RateVt; // [rsp+110h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+130h] [rbp-130h] BYREF
  CfgPlantEvent Event; // [rsp+140h] [rbp-120h] BYREF
  StringVector EventVt; // [rsp+150h] [rbp-110h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+170h] [rbp-F0h] BYREF
  StringVector ItemString; // [rsp+180h] [rbp-E0h] BYREF
  StringVector strItems; // [rsp+1A0h] [rbp-C0h] BYREF
  std::string delims; // [rsp+1C0h] [rbp-A0h] BYREF
  char v22; // [rsp+1CFh] [rbp-91h] BYREF
  std::string str; // [rsp+1D0h] [rbp-90h] BYREF
  char v24; // [rsp+1DFh] [rbp-81h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1E0h] [rbp-80h] BYREF
  std::string v26; // [rsp+1F0h] [rbp-70h] BYREF
  char v27; // [rsp+1FFh] [rbp-61h] BYREF
  std::string v28; // [rsp+200h] [rbp-60h] BYREF
  char v29; // [rsp+20Fh] [rbp-51h] BYREF
  std::string v30; // [rsp+210h] [rbp-50h] BYREF
  char v31; // [rsp+21Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v32; // [rsp+220h] [rbp-40h] BYREF
  std::string v33; // [rsp+230h] [rbp-30h] BYREF
  char v34; // [rsp+23Bh] [rbp-25h] BYREF
  int __x; // [rsp+23Ch] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+244h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+248h] [rbp-18h]
  int32_t i; // [rsp+24Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_plant.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_plant.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&plant, 0, sizeof(plant));
        std::vector<CfgPlantEvent>::vector(&plant.Events);
        std::vector<int>::vector(&plant.ItemVt);
        plant.id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        plant.type = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        plant.level = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        std::allocator<char>::allocator(&v22);
        std::string::string(&delims, "|", &v22);
        std::allocator<char>::allocator(&v24);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 5);
        std::string::string(&str, v1->pString, &v24);
        Answer::StringUtility::split(&strItems, &str, &delims, 0);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v24);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v22);
        for ( it._M_current = std::vector<std::string>::begin(&strItems)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strItems)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          std::allocator<char>::allocator(&v27);
          std::string::string(&v26, ":", &v27);
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          Answer::StringUtility::split(&EventVt, v2, &v26, 0);
          std::string::~string(&v26);
          std::allocator<char>::~allocator(&v27);
          if ( std::vector<std::string>::size(&EventVt) == 2 )
          {
            v3 = std::vector<std::string>::operator[](&EventVt, 0);
            v4 = (const char *)std::string::c_str(v3);
            Event.EventId = atoi(v4);
            v5 = std::vector<std::string>::operator[](&EventVt, 1u);
            v6 = (const char *)std::string::c_str(v5);
            Event.Probability = atoi(v6);
            plant.EventMaxRate += Event.Probability;
            std::vector<CfgPlantEvent>::push_back(&plant.Events, &Event);
          }
          std::vector<std::string>::~vector(&EventVt);
        }
        plant.item_cost = CDBCFile::Search_Posistion(&TabFile, i, 6)->iValue;
        plant.start_hour = CDBCFile::Search_Posistion(&TabFile, i, 7)->iValue;
        plant.end_hour = CDBCFile::Search_Posistion(&TabFile, i, 8)->iValue;
        plant.gather_time = CDBCFile::Search_Posistion(&TabFile, i, 9)->iValue;
        plant.revive_time = CDBCFile::Search_Posistion(&TabFile, i, 10)->iValue;
        plant.hide_time = CDBCFile::Search_Posistion(&TabFile, i, 16)->iValue;
        plant.get_points = CDBCFile::Search_Posistion(&TabFile, i, 18)->iValue;
        plant.boss_id = CDBCFile::Search_Posistion(&TabFile, i, 19)->iValue;
        plant.BuffId = CDBCFile::Search_Posistion(&TabFile, i, 20)->iValue;
        plant.revive_skin = CDBCFile::Search_Posistion(&TabFile, i, 21)->iValue;
        plant.TaskId = CDBCFile::Search_Posistion(&TabFile, i, 22)->iValue;
        std::allocator<char>::allocator(&v29);
        std::string::string(&v28, "|", &v29);
        std::allocator<char>::allocator(&v31);
        v7 = CDBCFile::Search_Posistion(&TabFile, i, 23);
        std::string::string(&v30, v7->pString, &v31);
        Answer::StringUtility::split(&ItemString, &v30, &v28, 0);
        std::string::~string(&v30);
        std::allocator<char>::~allocator(&v31);
        std::string::~string(&v28);
        std::allocator<char>::~allocator(&v29);
        for ( it_0._M_current = std::vector<std::string>::begin(&ItemString)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0) )
        {
          v32._M_current = std::vector<std::string>::end(&ItemString)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v32) )
            break;
          std::allocator<char>::allocator(&v34);
          std::string::string(&v33, ":", &v34);
          v8 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_0);
          Answer::StringUtility::split(&RateVt, v8, &v33, 0);
          std::string::~string(&v33);
          std::allocator<char>::~allocator(&v34);
          if ( std::vector<std::string>::size(&RateVt) == 2 )
          {
            v9 = std::vector<std::string>::operator[](&RateVt, 0);
            v10 = (const char *)std::string::c_str(v9);
            __x = atoi(v10);
            std::vector<int>::push_back(&plant.ItemVt, &__x);
          }
          std::vector<std::string>::~vector(&RateVt);
        }
        v11 = std::map<int,CfgPlant>::operator[](&this->m_plants, &plant.id);
        CfgPlant::operator=(v11, &plant);
        std::vector<std::string>::~vector(&ItemString);
        std::vector<std::string>::~vector(&strItems);
        CfgPlant::~CfgPlant(&plant);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitActiveSkillTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgActiveSkill skill; // [rsp+10h] [rbp-1A0h] BYREF
  CDBCFile TabFile; // [rsp+C0h] [rbp-F0h] BYREF
  AttrAddonVector __x; // [rsp+150h] [rbp-60h] BYREF
  std::string path; // [rsp+170h] [rbp-40h] BYREF
  char v6; // [rsp+17Fh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+180h] [rbp-30h] BYREF
  char v8; // [rsp+18Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+190h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+194h] [rbp-1Ch]
  int32_t i; // [rsp+198h] [rbp-18h]
  int32_t nIndex; // [rsp+19Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_skill_info.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_ACTIVE_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&skill, 0, sizeof(skill));
        std::vector<AttrAddon>::vector(&skill.summon_attr);
        nIndex = 0;
        skill.id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        ++nIndex;
        skill.talent = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.groupid = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.job = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.kind = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.distance = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.range = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.area = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.self = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.target_num = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.beneficial = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.tar_type = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.addon_skill = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.addon_time = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.addon_cd = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.addon_delay = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.addon_trig_times = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.cd = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.cd_adjust = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.mp = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.power = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.special = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.attack_type = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.attack_modify = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.building_modify = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.buff_rate = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.buff = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        skill.chantTime = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.summon_id = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        skill.summon_delay = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/cfg_skill_info.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&skill.summon_attr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        skill.summon_limit = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 17;
        skill.boss_addon_damage = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        skill.append_value = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        skill.shu_lian_du = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        skill.cd += skill.cd_adjust;
        CfgSkillTable::AddActiveSkill(&this->m_cfgSkillTable, &skill);
        CfgActiveSkill::~CfgActiveSkill(&skill);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitPassiveSkillTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-160h] BYREF
  CfgPassiveSkill stu; // [rsp+A0h] [rbp-D0h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-90h] BYREF
  std::string path; // [rsp+100h] [rbp-70h] BYREF
  char v7; // [rsp+10Fh] [rbp-61h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-60h] BYREF
  char v9; // [rsp+11Fh] [rbp-51h] BYREF
  std::list<TalentAddon> v10; // [rsp+120h] [rbp-50h] BYREF
  _BYTE v11[15]; // [rsp+130h] [rbp-40h] BYREF
  char v12; // [rsp+13Fh] [rbp-31h] BYREF
  int32_t v13[3]; // [rsp+140h] [rbp-30h] BYREF
  char v14; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillPassiveAttr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_PASSIVE_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 52);
        std::vector<AttrAddon>::vector(&stu.vAttrs);
        std::list<TalentAddon>::list(&stu.lTalentAddon);
        stu.id = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.type = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        std::string::string(&path, "./ServerConfig/Tables/SkillPassiveAttr.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v9);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttrs, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        std::string::string(v11, "./ServerConfig/Tables/SkillPassiveAttr.txt", &v12);
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v13, v2->pString, &v14);
        CfgData::paraseTalentAddon(
          (CfgData *const)&v10,
          (const std::string *const)this,
          (int32_t)v13,
          (const std::string *const)(unsigned int)i);
        std::list<TalentAddon>::operator=(&stu.lTalentAddon, &v10);
        std::list<TalentAddon>::~list(&v10);
        std::string::~string(v13);
        std::allocator<char>::~allocator(&v14);
        std::string::~string(v11);
        std::allocator<char>::~allocator(&v12);
        stu.dropMoneyRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgSkillTable::AddPassiveSkill(&this->m_cfgSkillTable, &stu);
        CfgPassiveSkill::~CfgPassiveSkill(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTrigSkillTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-F0h] BYREF
  CfgTrigSkill stu; // [rsp+A0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillTrig.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TRIG_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTrigSkill::CfgTrigSkill(&stu);
        stu.id = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.groupid = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.trigType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::operator=(&stu.trigParam, v1->pString);
        stu.targetType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.trigRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.cdTime = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.trigBuff = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.special = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.specialParam = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.IsPvp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgSkillTable::AddTrigSkill(&this->m_cfgSkillTable, &stu);
        CfgTrigSkill::~CfgTrigSkill(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitFamilySkillTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  CfgFamilySkill stu; // [rsp+A0h] [rbp-90h] BYREF
  AttrAddonVector __x; // [rsp+D0h] [rbp-60h] BYREF
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FamilySkill.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_FAMILY_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgFamilySkill::CfgFamilySkill(&stu);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nFamilyLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nCostValue = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/FamilySkill.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        stu.nCostMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.PlayerLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgSkillTable::AddFamilySkill(&this->m_cfgSkillTable, &stu);
        CfgFamilySkill::~CfgFamilySkill(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTalentActiveTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-F0h] BYREF
  CfgTalentActive stu; // [rsp+A0h] [rbp-60h] BYREF
  std::list<ItemData> strItems; // [rsp+C0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+D0h] [rbp-30h] BYREF
  char v6; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillActive.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_ACTIVE_TALENT_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalentActive::CfgTalentActive(&stu);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgSkillTable::AddTalentActive(&this->m_cfgSkillTable, &stu);
        CfgTalentActive::~CfgTalentActive(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTalentTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-150h] BYREF
  CfgTalent stu; // [rsp+A0h] [rbp-C0h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-60h] BYREF
  char v7; // [rsp+10Fh] [rbp-51h] BYREF
  std::list<int> __x; // [rsp+110h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+120h] [rbp-40h] BYREF
  char v10; // [rsp+12Fh] [rbp-31h] BYREF
  std::string path; // [rsp+130h] [rbp-30h] BYREF
  char v12; // [rsp+13Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+144h] [rbp-1Ch]
  int32_t i; // [rsp+148h] [rbp-18h]
  int32_t nIndex; // [rsp+14Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillTalent.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalent::CfgTalent(&stu);
        stu.id = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.skillid = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.maxLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Playerlevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v7);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.costItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        std::string::string(size, "./ServerConfig/Tables/SkillTalent.txt", &v10);
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&path, v2->pString, &v12);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.powerSkills, &__x);
        std::list<int>::~list(&__x);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v12);
        std::string::~string(size);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        ++nIndex;
        stu.battle = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.Point = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgTalentTable::AddTalent(&this->m_cfgTalentTable, &stu);
        CfgTalent::~CfgTalent(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTalentPageTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgTalentPage stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  char v6; // [rsp+DFh] [rbp-31h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF
  char v8; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillTree.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_PAGE_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalentPage::CfgTalentPage(&stu);
        stu.job = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        std::string::string(size, "./ServerConfig/Tables/SkillTree.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&path, v1->pString, &v8);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.talents, &__x);
        std::list<int>::~list(&__x);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(size);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgTalentTable::AddTalentPage(&this->m_cfgTalentTable, &stu);
        CfgTalentPage::~CfgTalentPage(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::fetchTask(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  CfgTask *v7; // rax
  CfgTask task; // [rsp+10h] [rbp-2A0h] BYREF
  CDBCFile TabFile; // [rsp+130h] [rbp-180h] BYREF
  MemChrBagVector __x; // [rsp+1C0h] [rbp-F0h] BYREF
  std::string strItems; // [rsp+1E0h] [rbp-D0h] BYREF
  char v12; // [rsp+1EFh] [rbp-C1h] BYREF
  MemChrBagVector v13; // [rsp+1F0h] [rbp-C0h] BYREF
  std::string v14; // [rsp+210h] [rbp-A0h] BYREF
  char v15; // [rsp+21Fh] [rbp-91h] BYREF
  MemChrJobBagVector v16; // [rsp+220h] [rbp-90h] BYREF
  std::string v17; // [rsp+240h] [rbp-70h] BYREF
  char v18; // [rsp+24Fh] [rbp-61h] BYREF
  std::string strRequest; // [rsp+250h] [rbp-60h] BYREF
  char v20; // [rsp+25Fh] [rbp-51h] BYREF
  std::list<TaskDrop> v21; // [rsp+260h] [rbp-50h] BYREF
  _BYTE v22[15]; // [rsp+270h] [rbp-40h] BYREF
  char v23; // [rsp+27Fh] [rbp-31h] BYREF
  std::string path; // [rsp+280h] [rbp-30h] BYREF
  char v25; // [rsp+292h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+294h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+298h] [rbp-18h]
  int32_t i; // [rsp+29Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_task.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_task.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTask::CfgTask(&task);
        task.id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        snprintf(task.name, 0x1Eu, v1->pString);
        task.type = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        task.group = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        task.can_giveup = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        task.pretask = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        task.posttask = CDBCFile::Search_Posistion(&TabFile, i, 6)->iValue;
        task.main_order = CDBCFile::Search_Posistion(&TabFile, i, 7)->iValue;
        task.job = CDBCFile::Search_Posistion(&TabFile, i, 8)->iValue;
        task.level = CDBCFile::Search_Posistion(&TabFile, i, 9)->iValue;
        task.max_level = CDBCFile::Search_Posistion(&TabFile, i, 10)->iValue;
        task.kingdom = CDBCFile::Search_Posistion(&TabFile, i, 11)->iValue;
        task.start_npc = CDBCFile::Search_Posistion(&TabFile, i, 12)->iValue;
        task.end_npc = CDBCFile::Search_Posistion(&TabFile, i, 13)->iValue;
        task.dungeon = CDBCFile::Search_Posistion(&TabFile, i, 14)->iValue;
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 15);
        std::string::string(&strItems, v2->pString, &v12);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&task.items_receive, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v12);
        task.award_exp = CDBCFile::Search_Posistion(&TabFile, i, 16)->iValue;
        task.award_money = CDBCFile::Search_Posistion(&TabFile, i, 17)->iValue;
        task.gold = CDBCFile::Search_Posistion(&TabFile, i, 18)->iValue;
        task.dilong = CDBCFile::Search_Posistion(&TabFile, i, 19)->iValue;
        task.rongyu = CDBCFile::Search_Posistion(&TabFile, i, 20)->iValue;
        task.fuwen = CDBCFile::Search_Posistion(&TabFile, i, 21)->iValue;
        task.BossScore = CDBCFile::Search_Posistion(&TabFile, i, 22)->iValue;
        std::allocator<char>::allocator(&v15);
        v3 = CDBCFile::Search_Posistion(&TabFile, i, 23);
        std::string::string(&v14, v3->pString, &v15);
        CItemHelper::parseItemVectorString(&v13, &v14);
        std::vector<MemChrBag>::operator=(&task.award_item, &v13);
        std::vector<MemChrBag>::~vector(&v13);
        std::string::~string(&v14);
        std::allocator<char>::~allocator(&v15);
        std::allocator<char>::allocator(&v18);
        v4 = CDBCFile::Search_Posistion(&TabFile, i, 24);
        std::string::string(&v17, v4->pString, &v18);
        CfgData::parseTaskItemJobString(&v16, this, task.id, &v17);
        std::vector<MemChrJobBag>::operator=(&task.award_optional, &v16);
        std::vector<MemChrJobBag>::~vector(&v16);
        std::string::~string(&v17);
        std::allocator<char>::~allocator(&v18);
        task.condition = CDBCFile::Search_Posistion(&TabFile, i, 35)->iValue;
        std::allocator<char>::allocator(&v20);
        v5 = CDBCFile::Search_Posistion(&TabFile, i, 36);
        std::string::string(&strRequest, v5->pString, &v20);
        task.request = CfgData::parseTaskCondition(this, task.id, task.condition, &strRequest);
        std::string::~string(&strRequest);
        std::allocator<char>::~allocator(&v20);
        task.GongXian = CDBCFile::Search_Posistion(&TabFile, i, 50)->iValue;
        task.JunTuanZiJin = CDBCFile::Search_Posistion(&TabFile, i, 51)->iValue;
        task.Double = CDBCFile::Search_Posistion(&TabFile, i, 52)->iValue;
        task.acScore = CDBCFile::Search_Posistion(&TabFile, i, 53)->iValue;
        task.quickDoneCost = CDBCFile::Search_Posistion(&TabFile, i, 55)->iValue;
        task.quality = CDBCFile::Search_Posistion(&TabFile, i, 61)->iValue;
        task.ratio = CDBCFile::Search_Posistion(&TabFile, i, 62)->iValue;
        task.dust = CDBCFile::Search_Posistion(&TabFile, i, 63)->iValue;
        task.activity_score = CDBCFile::Search_Posistion(&TabFile, i, 65)->iValue;
        task.talent_point = CDBCFile::Search_Posistion(&TabFile, i, 67)->iValue;
        std::allocator<char>::allocator(&v23);
        std::string::string(v22, "./ServerConfig/Tables/cfg_task.txt", &v23);
        std::allocator<char>::allocator(&v25);
        v6 = CDBCFile::Search_Posistion(&TabFile, i, 68);
        std::string::string(&path, v6->pString, &v25);
        CfgData::parseTaskDrop(
          (CfgData *const)&v21,
          (int32_t)this,
          (const std::string *const)(unsigned int)task.id,
          &path);
        std::list<TaskDrop>::operator=(&task.drop_list, &v21);
        std::list<TaskDrop>::~list(&v21);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v25);
        std::string::~string(v22);
        std::allocator<char>::~allocator(&v23);
        task.DoubleGold = CDBCFile::Search_Posistion(&TabFile, i, 69)->iValue;
        task.BuffId = CDBCFile::Search_Posistion(&TabFile, i, 70)->iValue;
        v7 = std::map<int,CfgTask>::operator[](&this->m_tasks, &task.id);
        CfgTask::operator=(v7, &task);
        if ( task.type == 3 )
          CfgTaskCycleTable::AddTask(&this->m_cfgTaskCycleTable, task.id, task.level, task.max_level);
        if ( task.type == 37 )
          CfgFamilyTask::AddFamilyTask(&this->m_FamilyTaskTable, task.id, task.level, task.max_level);
        if ( task.type == 41 )
          CfgActivityTaskTable::AddTask(&this->m_cfgActivityTaskTable, task.id, task.level, task.max_level, task.ratio);
        CfgTask::~CfgTask(&task);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::fetchTrap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgTrap *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgTrap trap; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/cfg_trap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_trap.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTrap::CfgTrap(&trap);
        trap.id = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        trap.cd = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        trap.delay = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        trap.event_type = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 6);
        std::string::operator=(&trap.effect, v1->pString);
        trap.item_cost = CDBCFile::Search_Posistion(&TabFile, i, 7)->iValue;
        trap.life = CDBCFile::Search_Posistion(&TabFile, i, 12)->iValue;
        v2 = std::map<int,CfgTrap>::operator[](&this->m_traps, &trap.id);
        CfgTrap::operator=(v2, &trap);
        CfgTrap::~CfgTrap(&trap);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::parseItemStringWithJob(
        CfgData *const this,
        int32_t id,
        const std::string *const strItems,
        MemChrBagVector *const items,
        MemChrJobBagVector *const jobItems)
{
  std::string *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  const char *v20; // rax
  MemChrBag itemData; // [rsp+30h] [rbp-D0h] BYREF
  MemChrJobBag job; // [rsp+50h] [rbp-B0h] BYREF
  StringVector item; // [rsp+70h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+90h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+A0h] [rbp-60h] BYREF
  std::string delims; // [rsp+C0h] [rbp-40h] BYREF
  char v30; // [rsp+CFh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+D0h] [rbp-30h] BYREF
  std::string v32; // [rsp+E0h] [rbp-20h] BYREF
  _BYTE v33[17]; // [rsp+EFh] [rbp-11h] BYREF

  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1 )
  {
    std::allocator<char>::allocator(&v30);
    std::string::string(&delims, "|", &v30);
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v30);
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(v33);
      std::string::string(&v32, ":", v33);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v32, 0);
      std::string::~string(&v32);
      std::allocator<char>::~allocator(v33);
      if ( std::vector<std::string>::size(&item) == 3 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.itemId = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.itemClass = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.itemCount = atoi(v11);
        std::vector<MemChrBag>::push_back(items, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 4 )
      {
        memset(&job, 0, sizeof(job));
        v12 = std::vector<std::string>::operator[](&item, 0);
        v13 = (const char *)std::string::c_str(v12);
        job.id = atoi(v13);
        v14 = std::vector<std::string>::operator[](&item, 1u);
        v15 = (const char *)std::string::c_str(v14);
        job.type = atoi(v15);
        v16 = std::vector<std::string>::operator[](&item, 2u);
        v17 = (const char *)std::string::c_str(v16);
        job.count = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 3u);
        v19 = (const char *)std::string::c_str(v18);
        job.job = atoi(v19);
        std::vector<MemChrJobBag>::push_back(jobItems, &job);
      }
      else
      {
        v20 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseItemString wrong data with id = %d, string = %s\n",
          id,
          v20);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
}


#####################################
void __cdecl CfgData::parseMonsterSkill(
        CfgData *const this,
        int32_t id,
        MonsterSkill (*const vSkill)[10],
        const std::string *const strSkill)
{
  int32_t v5; // eax
  std::string *v6; // rbx
  int32_t v7; // r12d
  std::string *v8; // rax
  const char *v9; // rax
  int32_t v10; // r12d
  std::string *v11; // rax
  const char *v12; // rax
  int32_t v13; // r12d
  std::string *v14; // rax
  const char *v15; // rax
  const char *v16; // rax
  StringVector skill; // [rsp+20h] [rbp-80h] BYREF
  StringVector skills; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v22; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v23; // [rsp+70h] [rbp-30h] BYREF
  char v24; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty((std::string *)strSkill) != 1
    && std::string::size((std::string *)strSkill) > 3u )
  {
    std::allocator<char>::allocator(&v22);
    std::string::string(&delims, "|", &v22);
    Answer::StringUtility::split(&skills, strSkill, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v22);
    if ( std::vector<std::string>::size(&skills) > 9 )
      v5 = 10;
    else
      v5 = std::vector<std::string>::size(&skills);
    isize = v5;
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v24);
      std::string::string(&v23, ":", &v24);
      v6 = std::vector<std::string>::operator[](&skills, i);
      Answer::StringUtility::split(&skill, v6, &v23, 0);
      std::string::~string(&v23);
      std::allocator<char>::~allocator(&v24);
      if ( std::vector<std::string>::size(&skill) == 3 )
      {
        v7 = i;
        v8 = std::vector<std::string>::operator[](&skill, 0);
        v9 = (const char *)std::string::c_str(v8);
        (*vSkill)[v7].maxHp = atoi(v9);
        v10 = i;
        v11 = std::vector<std::string>::operator[](&skill, 1u);
        v12 = (const char *)std::string::c_str(v11);
        (*vSkill)[v10].minHp = atoi(v12);
        v13 = i;
        v14 = std::vector<std::string>::operator[](&skill, 2u);
        v15 = (const char *)std::string::c_str(v14);
        (*vSkill)[v13].skillid = atoi(v15);
      }
      else
      {
        v16 = (const char *)std::string::c_str((std::string *)strSkill);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseMonsterSkill wrong data with id = %d, string = %s\n",
          id,
          v16);
      }
      std::vector<std::string>::~vector(&skill);
    }
    std::vector<std::string>::~vector(&skills);
  }
}


#####################################
int32_t __cdecl CfgData::getServerStartTime(CfgData *const this, SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return this->m_heFuTime;
  else
    return this->m_kaiFuTime;
}


#####################################
int32_t __cdecl CfgData::getServerStartDayZeroTime(CfgData *const this, SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return Answer::DayTime::dayzero(this->m_heFuTime);
  else
    return Answer::DayTime::dayzero(this->m_kaiFuTime);
}


#####################################
int32_t __cdecl CfgData::getServerDiffDay(CfgData *const this, SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return Answer::DayTime::daydiff(this->m_heFuTime);
  else
    return Answer::DayTime::daydiff(this->m_kaiFuTime);
}


#####################################
void __cdecl CfgData::fetchServerConfig(CfgData *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1060h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-30h] BYREF

  if ( line != 9 )
  {
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `sys_server_start`");
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    v3 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      this->m_heFuTime = Answer::MySqlQuery::getIntValue(&result, "he_fu_time", 0);
      this->m_kaiFuTime = Answer::MySqlQuery::getIntValue(&result, "kai_fu_time", 0);
      this->m_serverType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl CfgData::updateServerStartTime(CfgData *const this, int32_t kaiFuTime)
{
  COpenBeta *v2; // rax

  if ( !CfgData::getServerType(this) )
  {
    this->m_kaiFuTime = kaiFuTime;
    v2 = Answer::Singleton<COpenBeta>::instance();
    COpenBeta::updateStartTime(v2);
  }
}


#####################################
void __cdecl CfgData::sendNewItems(CfgData *const this, const CfgItemTable *const items)
{
  GameService *v2; // rax
  int32_t v3; // eax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-10h]
  CfgItem *pCfgItem; // [rsp+38h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2752u);
  if ( packet )
  {
    v3 = std::map<int,CfgItem *>::size(items);
    Answer::NetPacket::writeInt32(packet, v3);
    for ( it._M_node = std::map<int,CfgItem *>::begin(items)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator++(&it) )
    {
      __x._M_node = std::map<int,CfgItem *>::end(items)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator!=(&it, &__x) )
        break;
      pCfgItem = std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it)->second;
      if ( pCfgItem )
      {
        Answer::NetPacket::writeInt32(packet, pCfgItem->id);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->name);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->desc);
        Answer::NetPacket::writeInt32(packet, pCfgItem->type);
        Answer::NetPacket::writeInt32(packet, pCfgItem->level);
        Answer::NetPacket::writeInt32(packet, pCfgItem->job);
        Answer::NetPacket::writeInt32(packet, pCfgItem->in_value);
        Answer::NetPacket::writeInt32(packet, pCfgItem->out_value);
        Answer::NetPacket::writeInt32(packet, pCfgItem->bind);
        Answer::NetPacket::writeInt32(packet, pCfgItem->combine);
        Answer::NetPacket::writeInt32(packet, pCfgItem->quality);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->url);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->drop_url);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->effect);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->use_method);
        Answer::NetPacket::writeInt32(packet, pCfgItem->group_id);
        Answer::NetPacket::writeInt32(packet, pCfgItem->cd_group);
        Answer::NetPacket::writeInt32(packet, pCfgItem->overlay);
        Answer::NetPacket::writeInt32(packet, pCfgItem->can_sell);
        Answer::NetPacket::writeInt32(packet, pCfgItem->valid_time);
      }
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v5, packet);
  }
}


#####################################
void __cdecl CfgData::InitEquipTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CfgEquip equip; // [rsp+10h] [rbp-220h] BYREF
  CDBCFile readFile; // [rsp+C0h] [rbp-170h] BYREF
  AttrAddonVector __x; // [rsp+150h] [rbp-E0h] BYREF
  std::string path; // [rsp+170h] [rbp-C0h] BYREF
  char v8; // [rsp+17Fh] [rbp-B1h] BYREF
  std::string addonAttr; // [rsp+180h] [rbp-B0h] BYREF
  char v10; // [rsp+18Fh] [rbp-A1h] BYREF
  AttrAddonVector v11; // [rsp+190h] [rbp-A0h] BYREF
  std::string v12; // [rsp+1B0h] [rbp-80h] BYREF
  char v13; // [rsp+1BFh] [rbp-71h] BYREF
  std::string v14; // [rsp+1C0h] [rbp-70h] BYREF
  char v15; // [rsp+1CFh] [rbp-61h] BYREF
  AttrAddonVector v16; // [rsp+1D0h] [rbp-60h] BYREF
  std::string v17; // [rsp+1F0h] [rbp-40h] BYREF
  char v18; // [rsp+1FFh] [rbp-31h] BYREF
  std::string v19; // [rsp+200h] [rbp-30h] BYREF
  char v20; // [rsp+20Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+210h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+214h] [rbp-1Ch]
  int32_t i; // [rsp+218h] [rbp-18h]
  int32_t nIndex; // [rsp+21Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Equip.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&equip, 0, 172);
        std::vector<AttrAddon>::vector(&equip.m_vAttrAddon);
        std::vector<AttrAddon>::vector(&equip.m_vElement);
        std::vector<AttrAddon>::vector(&equip.m_BaseAttr);
        nIndex = 0;
        equip.m_nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        equip.m_nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nGrade = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nJob = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nQuality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nSuitId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nSuitId2 = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_nPrice = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        std::string::string(&path, "./ServerConfig/Tables/Equip.txt", &v8);
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v10);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&equip.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v10);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        std::string::string(&v12, "./ServerConfig/Tables/Equip.txt", &v13);
        std::allocator<char>::allocator(&v15);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v14, v2->pString, &v15);
        CfgData::paraseAttrAddon(&v11, this, &v14, i, &v12);
        std::vector<AttrAddon>::operator=(&equip.m_vElement, &v11);
        std::vector<AttrAddon>::~vector(&v11);
        std::string::~string(&v14);
        std::allocator<char>::~allocator(&v15);
        std::string::~string(&v12);
        std::allocator<char>::~allocator(&v13);
        ++nIndex;
        nIndex += 10;
        equip.m_DropLuck = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        equip.m_DropRate = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        equip.m_BackType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        equip.m_BackValue = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        equip.m_nBroadcast = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        equip.m_backIndex = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        equip.m_nLimitStar = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_BackGold = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v18);
        std::string::string(&v17, "./ServerConfig/Tables/Equip.txt", &v18);
        std::allocator<char>::allocator(&v20);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v19, v3->pString, &v20);
        CfgData::paraseAttrAddon(&v16, this, &v19, i, &v17);
        std::vector<AttrAddon>::operator=(&equip.m_BaseAttr, &v16);
        std::vector<AttrAddon>::~vector(&v16);
        std::string::~string(&v19);
        std::allocator<char>::~allocator(&v20);
        std::string::~string(&v17);
        std::allocator<char>::~allocator(&v18);
        equip.m_PolishLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        equip.m_MoFuHuiShou = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_SellDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_GongMingLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_WingEquipRefiningLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_XinMoExp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_XinMoBag = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_CanRongHe = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        equip.m_TeJieParam = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipTable::AddEquip(&this->m_cfgEquip, &equip);
        CfgEquip::~CfgEquip(&equip);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipUpStarTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-160h] BYREF
  CfgEquipUpStar stu; // [rsp+A0h] [rbp-D0h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-80h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-70h] BYREF
  char v7; // [rsp+10Fh] [rbp-61h] BYREF
  AttrAddonVector __x; // [rsp+110h] [rbp-60h] BYREF
  std::string path; // [rsp+130h] [rbp-40h] BYREF
  char v10; // [rsp+13Fh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+140h] [rbp-30h] BYREF
  char v12; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/EquipUpStar.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_UP_STAR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgEquipUpStar::CfgEquipUpStar(&stu);
        stu.m_nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.m_nStar = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.m_nRate = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.m_nSuccessAddStar = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.m_nFailLostStar = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v7);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.m_lCosItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v7);
        stu.m_nCostMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        std::string::string(&path, "./ServerConfig/Tables/EquipUpStar.txt", &v10);
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v2->pString, &v12);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v12);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        ++nIndex;
        stu.m_nCostXingMai = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.m_RongLianAttr = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipTable::AddEquipUpStar(&this->m_cfgEquip, &stu);
        CfgEquipUpStar::~CfgEquipUpStar(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipSuitTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-150h] BYREF
  CfgEquipSuit equip; // [rsp+A0h] [rbp-C0h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-80h] BYREF
  std::string path; // [rsp+100h] [rbp-60h] BYREF
  char v7; // [rsp+10Fh] [rbp-51h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-50h] BYREF
  char v9; // [rsp+11Fh] [rbp-41h] BYREF
  std::list<int> v10; // [rsp+120h] [rbp-40h] BYREF
  int32_t size[3]; // [rsp+130h] [rbp-30h] BYREF
  char v12; // [rsp+13Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+144h] [rbp-1Ch]
  int32_t i; // [rsp+148h] [rbp-18h]
  int32_t nIndex; // [rsp+14Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/EquipSuit.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgEquipSuit::CfgEquipSuit(&equip);
        equip.m_nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        equip.m_nCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        std::string::string(&path, "./ServerConfig/Tables/EquipSuit.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v9);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&equip.m_lstSuitAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(size, v2->pString, &v12);
        CfgData::paraseInt32List((CfgData *const)&v10, (const std::string *const)this, (int32_t)size);
        std::list<int>::operator=(&equip.m_IdList, &v10);
        std::list<int>::~list(&v10);
        std::string::~string(size);
        std::allocator<char>::~allocator(&v12);
        ++nIndex;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        equip.m_nBuffId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipTable::AddEquipSuit(&this->m_cfgEquip, &equip);
        CfgEquipSuit::~CfgEquipSuit(&equip);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipDecomposeTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  CfgEquipDecompose stu; // [rsp+A0h] [rbp-90h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v6; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/EquipDecompose.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_DECOMPOSE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipDecompose::CfgEquipDecompose(&stu);
        nIndex = 0;
        stu.m_nClass = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.m_nId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.m_vGiveItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        stu.m_nCostMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.m_nLimitType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.m_nLimitValue = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        stu.m_NpcId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgEquipTable::AddEquipDecompose(&this->m_cfgEquip, &stu);
        CfgEquipDecompose::~CfgEquipDecompose(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipUpPosTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  __int64 v4; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-170h] BYREF
  CfgEquipUpPos stu; // [rsp+A0h] [rbp-E0h] BYREF
  AttrAddonVector __x; // [rsp+F0h] [rbp-90h] BYREF
  std::string path; // [rsp+110h] [rbp-70h] BYREF
  char v9; // [rsp+11Fh] [rbp-61h] BYREF
  std::string addonAttr; // [rsp+120h] [rbp-60h] BYREF
  char v11; // [rsp+12Fh] [rbp-51h] BYREF
  std::list<ItemData> strItems; // [rsp+130h] [rbp-50h] BYREF
  bool bCombi[15]; // [rsp+140h] [rbp-40h] BYREF
  char v14; // [rsp+14Fh] [rbp-31h] BYREF
  std::string strItem; // [rsp+150h] [rbp-30h] BYREF
  char v16; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]
  ItemData v22; // 0:kr00_12.12

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/EquipUpPos.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_UP_POS_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipUpPos::CfgEquipUpPos(&stu);
        nIndex = 0;
        stu.m_nType = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.m_nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.m_nRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.m_nCostMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        std::string::string(&path, "./ServerConfig/Tables/EquipUpPos.txt", &v9);
        std::allocator<char>::allocator(&v11);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v11);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v11);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v9);
        stu.m_nNeedLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v2->pString, &v14);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.m_nConstItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v14);
        stu.m_GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v16);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v3->pString, &v16);
        v22 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v4) = v22.m_nId;
        BYTE4(v4) = v22.m_nClass;
        *(_QWORD *)&stu.m_BaoHuConst.m_nId = v4;
        stu.m_BaoHuConst.m_nCount = v22.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v16);
        ++nIndex;
        CfgEquipTable::AddEquipUpPos(&this->m_cfgEquip, &stu);
        CfgEquipUpPos::~CfgEquipUpPos(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipPosSuitTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgEquipPosSuit stu; // [rsp+A0h] [rbp-80h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-60h] BYREF
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  char v6; // [rsp+EFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/EquipPosSuit.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_POS_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipPosSuit::CfgEquipPosSuit(&stu);
        nIndex = 1;
        stu.m_nLevel = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/EquipPosSuit.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgEquipTable::AddEquipPosSuit(&this->m_cfgEquip, &stu);
        CfgEquipPosSuit::~CfgEquipPosSuit(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitShenYaoPosTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-190h] BYREF
  ShenYaoPos stu; // [rsp+A0h] [rbp-100h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-C0h] BYREF
  std::string path; // [rsp+100h] [rbp-A0h] BYREF
  char v7; // [rsp+10Fh] [rbp-91h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-90h] BYREF
  char v9; // [rsp+11Fh] [rbp-81h] BYREF
  std::list<ItemData> strItems; // [rsp+120h] [rbp-80h] BYREF
  bool bCombi[15]; // [rsp+130h] [rbp-70h] BYREF
  char v12; // [rsp+13Fh] [rbp-61h] BYREF
  ShenYaoPos p_stu; // [rsp+140h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShengZhuangAttr.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_UP_POS_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        ShenYaoPos::ShenYaoPos(&stu);
        nIndex = 0;
        stu.nSlotId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        std::string::string(&path, "./ServerConfig/Tables/ShengZhuangAttr.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v9);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v2->pString, &v12);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.nCost, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v12);
        stu.nGongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ShenYaoPos::ShenYaoPos(&p_stu, &stu);
        CfgEquipTable::AddShenYaoPosCfg(&this->m_cfgEquip, &p_stu);
        ShenYaoPos::~ShenYaoPos(&p_stu);
        ShenYaoPos::~ShenYaoPos(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitShenYaoPosSuitTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-140h] BYREF
  ShenYaoPosSuit stu; // [rsp+A0h] [rbp-B0h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-90h] BYREF
  std::string path; // [rsp+E0h] [rbp-70h] BYREF
  char v6; // [rsp+EFh] [rbp-61h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  ShenYaoPosSuit p_stu; // [rsp+100h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShengZhuangSuit.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_POS_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        ShenYaoPosSuit::ShenYaoPosSuit(&stu);
        nIndex = 1;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/EquipPosSuit.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        ShenYaoPosSuit::ShenYaoPosSuit(&p_stu, &stu);
        CfgEquipTable::AddShenYaoPosSuit(&this->m_cfgEquip, &p_stu);
        ShenYaoPosSuit::~ShenYaoPosSuit(&p_stu);
        ShenYaoPosSuit::~ShenYaoPosSuit(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipBackTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  const char *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-190h] BYREF
  EquipBack stu; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-C0h] BYREF
  StringVector vStr; // [rsp+F0h] [rbp-B0h] BYREF
  std::string EquipList; // [rsp+110h] [rbp-90h] BYREF
  char v9; // [rsp+11Fh] [rbp-81h] BYREF
  std::string delims; // [rsp+120h] [rbp-80h] BYREF
  char v11; // [rsp+12Fh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+130h] [rbp-70h] BYREF
  int __x; // [rsp+13Ch] [rbp-64h] BYREF
  EquipBack p_stu; // [rsp+140h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/EquipRecovery.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BACK failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        EquipBack::EquipBack(&stu);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&EquipList, v1->pString, &v9);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        std::string::string(&delims, "|", &v11);
        Answer::StringUtility::split(&vStr, &EquipList, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v11);
        for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
            break;
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
          v3 = (const char *)std::string::c_str(v2);
          __x = atoi(v3);
          std::list<int>::push_back(&stu.nEquipList, &__x);
        }
        stu.nRecovType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nRecovValues = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nBuyBackType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nBuyBackValue = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nOpenDay = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nLimitNum = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 3;
        stu.nDisplayDay = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        EquipBack::EquipBack(&p_stu, &stu);
        CfgEquipTable::AddEquipBack(&this->m_cfgEquip, &p_stu);
        EquipBack::~EquipBack(&p_stu);
        std::vector<std::string>::~vector(&vStr);
        std::string::~string(&EquipList);
        EquipBack::~EquipBack(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitStrengthenTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  __int64 v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-190h] BYREF
  EquipStrengthenCfg stu; // [rsp+A0h] [rbp-100h] BYREF
  std::string strItem; // [rsp+E0h] [rbp-C0h] BYREF
  char v7; // [rsp+EFh] [rbp-B1h] BYREF
  AttrAddonVector __x; // [rsp+F0h] [rbp-B0h] BYREF
  std::string path; // [rsp+110h] [rbp-90h] BYREF
  char v10; // [rsp+11Fh] [rbp-81h] BYREF
  std::string addonAttr; // [rsp+120h] [rbp-80h] BYREF
  char v12; // [rsp+12Fh] [rbp-71h] BYREF
  EquipStrengthenCfg p_stu; // [rsp+130h] [rbp-70h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]
  ItemData v19; // 0:kr00_12.12

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MieShenRongLian.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BACK failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        EquipStrengthenCfg::EquipStrengthenCfg(&stu);
        nIndex = 0;
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.Pos = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v7);
        v19 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v3) = v19.m_nId;
        BYTE4(v3) = v19.m_nClass;
        *(_QWORD *)&stu.ConstItem.m_nId = v3;
        stu.ConstItem.m_nCount = v19.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v7);
        stu.AttrRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.DropRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        std::string::string(&path, "./ServerConfig/Tables/MieShenRongLian.txt", &v10);
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v2->pString, &v12);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v12);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v10);
        stu.NeedPos = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        EquipStrengthenCfg::EquipStrengthenCfg(&p_stu, &stu);
        CfgEquipTable::AddEequipStrengthenCfg(&this->m_cfgEquip, &p_stu);
        EquipStrengthenCfg::~EquipStrengthenCfg(&p_stu);
        EquipStrengthenCfg::~EquipStrengthenCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipBoxTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  CfgEquipBox stu; // [rsp+A0h] [rbp-90h] BYREF
  std::list<Param2> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v5[15]; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  int32_t v7[3]; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/cfg_item_gift_equip.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BOX_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipBox::CfgEquipBox(&stu);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.vEquipId[1] = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.vEquipId[2] = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.vEquipId[3] = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nWeight = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBind = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(v5, "./ServerConfig/Tables/EquipPosSuit.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v7, v1->pString, &v8);
        CfgData::paraseParam2List(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v7,
          (const std::string *const)(unsigned int)i);
        std::list<Param2>::operator=(&stu.lstStar, &__x);
        std::list<Param2>::~list(&__x);
        std::string::~string(v7);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(v5);
        std::allocator<char>::~allocator(&v6);
        stu.nProbility = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipBoxTable::AddEquipBox(&this->m_cfgEquipBoxTalbe, &stu);
        CfgEquipBox::~CfgEquipBox(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitItemGemTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::string *v4; // rax
  const char *v5; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-190h] BYREF
  CfgItemGem gem; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-C0h] BYREF
  StringVector vStr; // [rsp+F0h] [rbp-B0h] BYREF
  std::string str; // [rsp+110h] [rbp-90h] BYREF
  AttrAddonVector __x; // [rsp+120h] [rbp-80h] BYREF
  std::string path; // [rsp+140h] [rbp-60h] BYREF
  char v13; // [rsp+14Fh] [rbp-51h] BYREF
  std::string addonAttr; // [rsp+150h] [rbp-50h] BYREF
  char v15; // [rsp+15Eh] [rbp-42h] BYREF
  char v16; // [rsp+15Fh] [rbp-41h] BYREF
  std::string delims; // [rsp+160h] [rbp-40h] BYREF
  char v18; // [rsp+16Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+170h] [rbp-30h] BYREF
  char v20; // [rsp+17Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ItemGem.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_GEM_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&gem, 0, sizeof(gem));
        std::list<signed char>::list(&gem.m_lAddPos);
        std::vector<AttrAddon>::vector(&gem.m_vAttrAddon);
        gem.m_nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        gem.m_nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        gem.m_nPrice = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        gem.m_nQuality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        gem.m_nLayNum = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        std::string::string(&path, "./ServerConfig/Tables/ItemGem.txt", &v13);
        std::allocator<char>::allocator(&v15);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v15);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&gem.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v15);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v13);
        ++nIndex;
        std::allocator<char>::allocator(&v16);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&str, v2->pString, &v16);
        std::allocator<char>::~allocator(&v16);
        gem.m_nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        if ( (unsigned __int8)std::string::empty(&str) != 1 && std::operator!=<char>(&str, "-1") )
        {
          std::allocator<char>::allocator(&v18);
          std::string::string(&delims, ":", &v18);
          Answer::StringUtility::split(&vStr, &str, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v18);
          for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
                ;
                __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
            if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
              break;
            v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
            v5 = (const char *)std::string::c_str(v4);
            v20 = atoi(v5);
            std::list<signed char>::push_back(&gem.m_lAddPos, &v20);
          }
          std::vector<std::string>::~vector(&vStr);
        }
        CfgItemGemTable::Add(&this->m_cfgItemGem, &gem);
        std::string::~string(&str);
        CfgItemGem::~CfgItemGem(&gem);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGemOpenHoleTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-F0h] BYREF
  CfgGemOpenHole stu; // [rsp+A0h] [rbp-60h] BYREF
  std::list<ItemData> strItems; // [rsp+C0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+D0h] [rbp-30h] BYREF
  char v6; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GemOpenHole.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GEM_OPEN_HOLE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<ItemData>::list(&stu.m_lCostItem);
        stu.m_nSlot = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.m_nCostMoney = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.m_lCostItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgItemGemTable::AddGemOpenHole(&this->m_cfgItemGem, &stu);
        CfgGemOpenHole::~CfgGemOpenHole(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGemLevelUpTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgGemLevelUp stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GemLevelUp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileGemLev);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::list<ItemData>::list(&stu.lCostItems);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nNextId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lCostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v6);
        stu.nCostMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBroadId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgItemGemTable::AddGemLevelUp(&this->m_cfgItemGem, &stu);
        CfgGemLevelUp::~CfgGemLevelUp(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGemSuitTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgGemSuit stu; // [rsp+A0h] [rbp-80h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-60h] BYREF
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  char v6; // [rsp+EFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GemSuit.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GEM_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        memset(&stu, 0, sizeof(stu));
        std::vector<AttrAddon>::vector(&stu.m_vAttrAddon);
        stu.m_nLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/GemSuit.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgItemGemTable::AddGemSuit(&this->m_cfgItemGem, &stu);
        CfgGemSuit::~CfgGemSuit(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitItemCombiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  CfgItemCombi itemCombi; // [rsp+10h] [rbp-240h] BYREF
  CDBCFile readFile; // [rsp+B0h] [rbp-1A0h] BYREF
  std::list<ItemData> strItems; // [rsp+140h] [rbp-110h] BYREF
  bool bCombi[15]; // [rsp+150h] [rbp-100h] BYREF
  char v10; // [rsp+15Fh] [rbp-F1h] BYREF
  MemChrBagVector __x; // [rsp+160h] [rbp-F0h] BYREF
  std::string v12; // [rsp+180h] [rbp-D0h] BYREF
  char v13; // [rsp+18Fh] [rbp-C1h] BYREF
  MemChrBagVector v14; // [rsp+190h] [rbp-C0h] BYREF
  std::string v15; // [rsp+1B0h] [rbp-A0h] BYREF
  char v16; // [rsp+1BFh] [rbp-91h] BYREF
  MemChrBagVector v17; // [rsp+1C0h] [rbp-90h] BYREF
  std::string v18; // [rsp+1E0h] [rbp-70h] BYREF
  char v19; // [rsp+1EFh] [rbp-61h] BYREF
  Int32VtVector v20; // [rsp+1F0h] [rbp-60h] BYREF
  std::string path; // [rsp+210h] [rbp-40h] BYREF
  char v22; // [rsp+21Fh] [rbp-31h] BYREF
  std::string str; // [rsp+220h] [rbp-30h] BYREF
  char v24; // [rsp+22Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+230h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+234h] [rbp-1Ch]
  int32_t i; // [rsp+238h] [rbp-18h]
  int32_t nIndex; // [rsp+23Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ItemCombi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_COMBI_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgItemCombi::CfgItemCombi(&itemCombi);
        itemCombi.m_nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v10);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&itemCombi.m_lCostItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v12, v2->pString, &v13);
        CItemHelper::parseItemVectorString(&__x, &v12);
        std::vector<MemChrBag>::operator=(&itemCombi.m_vGiveItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&v12);
        std::allocator<char>::~allocator(&v13);
        itemCombi.m_nMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        itemCombi.m_nRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        itemCombi.m_nTotalRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        itemCombi.m_bBroadcast = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v16);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v15, v3->pString, &v16);
        CItemHelper::parseItemVectorString(&v14, &v15);
        std::vector<MemChrBag>::operator=(&itemCombi.m_vBackItem, &v14);
        std::vector<MemChrBag>::~vector(&v14);
        std::string::~string(&v15);
        std::allocator<char>::~allocator(&v16);
        ++nIndex;
        itemCombi.m_bNeedActive = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        itemCombi.m_nCostPoint = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v19);
        v4 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v18, v4->pString, &v19);
        CItemHelper::parseItemVectorString(&v17, &v18);
        std::vector<MemChrBag>::operator=(&itemCombi.m_vSpecialItems, &v17);
        std::vector<MemChrBag>::~vector(&v17);
        std::string::~string(&v18);
        std::allocator<char>::~allocator(&v19);
        ++nIndex;
        std::allocator<char>::allocator(&v22);
        std::string::string(&path, "./ServerConfig/Tables/ItemCombi.txt", &v22);
        std::allocator<char>::allocator(&v24);
        v5 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&str, v5->pString, &v24);
        CfgData::paraseInt32VtVector(&v20, this, &str, &path);
        std::vector<std::vector<int>>::operator=(&itemCombi.m_vProbability, &v20);
        std::vector<std::vector<int>>::~vector(&v20);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v24);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v22);
        itemCombi.m_nCombiType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgItemCombiTable::Add(&this->m_cfgItemCombi, &itemCombi);
        CfgItemCombi::~CfgItemCombi(&itemCombi);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMonsterRandTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-170h] BYREF
  CfgMonsterRand stu; // [rsp+A0h] [rbp-E0h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-A0h] BYREF
  std::string path; // [rsp+100h] [rbp-80h] BYREF
  char v7; // [rsp+10Fh] [rbp-71h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-70h] BYREF
  char v9; // [rsp+11Fh] [rbp-61h] BYREF
  AttrAddonVector v10; // [rsp+120h] [rbp-60h] BYREF
  std::string v11; // [rsp+140h] [rbp-40h] BYREF
  char v12; // [rsp+14Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+150h] [rbp-30h] BYREF
  char v14; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MonsterRand.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_RAND_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgMonsterRand::CfgMonsterRand(&stu);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        std::string::string(&path, "./ServerConfig/Tables/MonsterRand.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v9);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttrValue, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        std::string::string(&v11, "./ServerConfig/Tables/MonsterRand.txt", &v12);
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v13, v2->pString, &v14);
        CfgData::paraseAttrAddon(&v10, this, &v13, i, &v11);
        std::vector<AttrAddon>::operator=(&stu.vAttrRatio, &v10);
        std::vector<AttrAddon>::~vector(&v10);
        std::string::~string(&v13);
        std::allocator<char>::~allocator(&v14);
        std::string::~string(&v11);
        std::allocator<char>::~allocator(&v12);
        stu.nSkill = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgMonsterRandTable::AddMonsterRand(&this->m_cfgMonsterRandTable, &stu);
        CfgMonsterRand::~CfgMonsterRand(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitWingCfgTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-1D0h] BYREF
  WingCfg stu; // [rsp+A0h] [rbp-140h] BYREF
  std::list<ItemData> strItems; // [rsp+100h] [rbp-E0h] BYREF
  bool bCombi[15]; // [rsp+110h] [rbp-D0h] BYREF
  char v7; // [rsp+11Fh] [rbp-C1h] BYREF
  AttrAddonVector __x; // [rsp+120h] [rbp-C0h] BYREF
  std::string path; // [rsp+140h] [rbp-A0h] BYREF
  char v10; // [rsp+14Fh] [rbp-91h] BYREF
  std::string addonAttr; // [rsp+150h] [rbp-90h] BYREF
  char v12; // [rsp+15Fh] [rbp-81h] BYREF
  WingCfg p_stu; // [rsp+160h] [rbp-80h] BYREF
  int32_t iBaseTableCount; // [rsp+1C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1C4h] [rbp-1Ch]
  int32_t i; // [rsp+1C8h] [rbp-18h]
  int32_t nIndex; // [rsp+1CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/AttributeWing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WING_CFG_TABEL failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::list<ItemData>::list(&stu.ConstItems);
        std::vector<AttrAddon>::vector(&stu.AddonVector);
        nIndex = 0;
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v7);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.ConstItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v7);
        stu.StartPoints = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.SuccessPoints = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MaxPoints = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Rate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.FailAddPoints = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.SkillId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.SkillLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.IsClear = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        std::string::string(&path, "./ServerConfig/Tables/AttributeWing.txt", &v10);
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v2->pString, &v12);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.AddonVector, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v12);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        WingCfg::WingCfg(&p_stu, &stu);
        CfgWingTable::AddWingCfg(&this->m_cfgWing, &p_stu);
        WingCfg::~WingCfg(&p_stu);
        WingCfg::~WingCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitCarrierTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgCarrier stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  char v6; // [rsp+DFh] [rbp-31h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF
  char v8; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Carrier.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::list<int>::list(&stu.lSkills);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(size, "./ServerConfig/Tables/Carrier.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&path, v1->pString, &v8);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.lSkills, &__x);
        std::list<int>::~list(&__x);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(size);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgCarrierTable::AddCarrier(&this->m_cfgCarrierTable, &stu);
        CfgCarrier::~CfgCarrier(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitCarrierAttrTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgCarrierAttr stu; // [rsp+A0h] [rbp-80h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-60h] BYREF
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  char v6; // [rsp+EFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Carrier_attr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_ATTR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<AttrAddon>::vector(&stu.vAttr);
        nIndex = 0;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/Carrier_attr.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgCarrierTable::AddCarrierAttr(&this->m_cfgCarrierTable, &stu);
        CfgCarrierAttr::~CfgCarrierAttr(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitJueWeiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  CfgJueWei stu; // [rsp+A0h] [rbp-90h] BYREF
  AttrAddonVector __x; // [rsp+D0h] [rbp-60h] BYREF
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/JueWei.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<AttrAddon>::vector(&stu.vAttr);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nNeedLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nNeedViGour = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/JueWei.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgJueWeiTable::AddJueWei(&this->m_cfgJueWeiTable, &stu);
        CfgJueWei::~CfgJueWei(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitPetTable(CfgData *const this)
{
  int32_t v1; // ebx
  int32_t v2; // ebx
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  CfgPetData pet; // [rsp+A0h] [rbp-90h] BYREF
  int32_t iBaseTableCount; // [rsp+10Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+110h] [rbp-20h]
  int32_t i; // [rsp+114h] [rbp-1Ch]
  int32_t nIndex; // [rsp+118h] [rbp-18h]
  int32_t j; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Pet.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PET_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgPetData::CfgPetData(&pet);
        pet.m_nPetId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        pet.m_Quality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        for ( j = 0; j <= 8; ++j )
        {
          v1 = j;
          pet.m_vSkill[v1] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
          v2 = j;
          pet.m_vSkillOpen[v2] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        }
        CfgPetTable::Add(&this->m_cfgPetTable, &pet);
        CfgPetData::~CfgPetData(&pet);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitPetAttrTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-160h] BYREF
  CfgPetData pet; // [rsp+A0h] [rbp-D0h] BYREF
  AttrAddonVector __x; // [rsp+110h] [rbp-60h] BYREF
  std::string path; // [rsp+130h] [rbp-40h] BYREF
  char v6; // [rsp+13Fh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+140h] [rbp-30h] BYREF
  char v8; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/PetAttr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PET_ATTR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgPetData::CfgPetData(&pet);
        pet.m_nPetId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/PetAttr.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&pet.m_vBaseAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgPetTable::AddAttr(&this->m_cfgPetTable, &pet);
        CfgPetData::~CfgPetData(&pet);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitPetUpStarTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-200h] BYREF
  CfgPetUpStar stu; // [rsp+A0h] [rbp-170h] BYREF
  std::list<ItemData> strItems; // [rsp+110h] [rbp-100h] BYREF
  bool bCombi[15]; // [rsp+120h] [rbp-F0h] BYREF
  char v9; // [rsp+12Fh] [rbp-E1h] BYREF
  AttrAddonVector __x; // [rsp+130h] [rbp-E0h] BYREF
  std::string path; // [rsp+150h] [rbp-C0h] BYREF
  char v12; // [rsp+15Fh] [rbp-B1h] BYREF
  std::string addonAttr; // [rsp+160h] [rbp-B0h] BYREF
  char v14; // [rsp+16Fh] [rbp-A1h] BYREF
  AttrAddonVector v15; // [rsp+170h] [rbp-A0h] BYREF
  std::string v16; // [rsp+190h] [rbp-80h] BYREF
  char v17; // [rsp+19Fh] [rbp-71h] BYREF
  std::string v18; // [rsp+1A0h] [rbp-70h] BYREF
  char v19; // [rsp+1AFh] [rbp-61h] BYREF
  Int32Vector v20; // [rsp+1B0h] [rbp-60h] BYREF
  std::string v21; // [rsp+1D0h] [rbp-40h] BYREF
  char v22; // [rsp+1DFh] [rbp-31h] BYREF
  std::string str; // [rsp+1E0h] [rbp-30h] BYREF
  char v24; // [rsp+1EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+1F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1F4h] [rbp-1Ch]
  int32_t i; // [rsp+1F8h] [rbp-18h]
  int32_t nIndex; // [rsp+1FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/PetUpStar.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PET_UP_STAR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgPetUpStar::CfgPetUpStar(&stu);
        stu.nStar = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nCostMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v9);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lCostItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        std::string::string(&path, "./ServerConfig/Tables/PetUpStar.txt", &v12);
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v2->pString, &v14);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAddPetAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v14);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v12);
        ++nIndex;
        std::allocator<char>::allocator(&v17);
        std::string::string(&v16, "./ServerConfig/Tables/PetUpStar.txt", &v17);
        std::allocator<char>::allocator(&v19);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v18, v3->pString, &v19);
        CfgData::paraseAttrAddon(&v15, this, &v18, i, &v16);
        std::vector<AttrAddon>::operator=(&stu.vAddPlayerAttr, &v15);
        std::vector<AttrAddon>::~vector(&v15);
        std::string::~string(&v18);
        std::allocator<char>::~allocator(&v19);
        std::string::~string(&v16);
        std::allocator<char>::~allocator(&v17);
        ++nIndex;
        std::allocator<char>::allocator(&v22);
        std::string::string(&v21, "./ServerConfig/Tables/PetUpStar.txt", &v22);
        std::allocator<char>::allocator(&v24);
        v4 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&str, v4->pString, &v24);
        CfgData::paraseInt32Vector(&v20, this, &str, &v21, 0);
        std::vector<int>::operator=(&stu.vSkillLevel, &v20);
        std::vector<int>::~vector(&v20);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v24);
        std::string::~string(&v21);
        std::allocator<char>::~allocator(&v22);
        ++nIndex;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 3;
        stu.nCostGold = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgPetTable::AddPetUpStar(&this->m_cfgPetTable, &stu);
        CfgPetUpStar::~CfgPetUpStar(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitFamilyTable(CfgData *const this)
{
  int v1; // ebx
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgFamily family; // [rsp+A0h] [rbp-70h] BYREF
  CfgFamilyBoss stu; // [rsp+C0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+DCh] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+E0h] [rbp-30h]
  int32_t i; // [rsp+E4h] [rbp-2Ch]
  int32_t nIndex; // [rsp+E8h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+F4h] [rbp-1Ch]
  int32_t i_0; // [rsp+F8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Family.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      CfgFamily::CfgFamily(&family);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgFamily::CleanUp(&family);
        family.nLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        family.nExp = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        family.nMaxMembers = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        family.vPosition[1] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        family.vPosition[2] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        family.nMaxBossPoints = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgFamilyTable::Add(&this->m_cfgFamilyTable, &family);
      }
      CfgFamily::~CfgFamily(&family);
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FamilyBoss.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_BOSS_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu.nFamilyLevel = 0;
          *(_QWORD *)&stu.FamilyExp = 0;
          nIndex_0 = 0;
          stu.nFamilyLevel = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          stu.BossMid = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu.FamilyExp = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CfgFamilyTable::AddFamilyBoss(&this->m_cfgFamilyTable, &stu);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile);
  }
}


#####################################
void __cdecl CfgData::InitFamilyMedalTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-150h] BYREF
  FamilyMedal Medal; // [rsp+A0h] [rbp-C0h] BYREF
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-90h] BYREF
  _BYTE v7[15]; // [rsp+E0h] [rbp-80h] BYREF
  char v8; // [rsp+EFh] [rbp-71h] BYREF
  int32_t v9[3]; // [rsp+F0h] [rbp-70h] BYREF
  char v10; // [rsp+FFh] [rbp-61h] BYREF
  std::list<AddAttribute> v11; // [rsp+100h] [rbp-60h] BYREF
  _BYTE v12[15]; // [rsp+110h] [rbp-50h] BYREF
  char v13; // [rsp+11Fh] [rbp-41h] BYREF
  int32_t v14[2]; // [rsp+120h] [rbp-40h] BYREF
  char v15; // [rsp+12Ah] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+12Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+130h] [rbp-30h]
  int32_t i; // [rsp+134h] [rbp-2Ch]
  int32_t nIndex; // [rsp+138h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+144h] [rbp-1Ch]
  int32_t i_0; // [rsp+148h] [rbp-18h]
  int32_t nIndex_0; // [rsp+14Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FamilyBadge.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_MEDAL_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&Medal, 0, sizeof(Medal));
        std::list<AddAttribute>::list(&Medal.lAttrList);
        Medal.nLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        Medal.nNeedFamilyLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        Medal.nNeedFamilyExp = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        std::string::string(v7, "./ServerConfig/Tables/FamilyBadge.txt", &v8);
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v9, v2->pString, &v10);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v9,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&Medal.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v9);
        std::allocator<char>::~allocator(&v10);
        std::string::~string(v7);
        std::allocator<char>::~allocator(&v8);
        Medal.nGongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        Medal.DefRdc = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgFamilyTable::AddFamilyMedal(&this->m_cfgFamilyTable, &Medal);
        FamilyMedal::~FamilyMedal(&Medal);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/BadgeStreng.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_MEDAL_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&Medal, 0, 32);
          std::list<AddAttribute>::list(&Medal.lAttrList);
          Medal.nLevel = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0++)->iValue;
          Medal.nNeedFamilyLevel = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0++)->iValue;
          Medal.nNeedFamilyExp = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0++)->iValue;
          nIndex_0 += 2;
          std::allocator<char>::allocator(&v13);
          std::string::string(v12, "./ServerConfig/Tables/FamilyBadge.txt", &v13);
          std::allocator<char>::allocator(&v15);
          v3 = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0);
          std::string::string(v14, v3->pString, &v15);
          CfgData::parseAddAttribues(
            (CfgData *const)&v11,
            (const std::string *const)this,
            (int32_t)v14,
            (const std::string *const)(unsigned int)nIndex_0);
          std::list<AddAttribute>::operator=(&Medal.lAttrList, &v11);
          std::list<AddAttribute>::~list(&v11);
          std::string::~string(v14);
          std::allocator<char>::~allocator(&v15);
          std::string::~string(v12);
          std::allocator<char>::~allocator(&v13);
          ++nIndex_0;
          CfgFamilyTable::AddFamilySelfMedal(&this->m_cfgFamilyTable, (const FamilySelfMedal *const)&Medal);
          FamilySelfMedal::~FamilySelfMedal((FamilySelfMedal *const)&Medal);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile);
  }
}


#####################################
void __cdecl CfgData::InitHoeTable(CfgData *const this)
{
  HoeCfg *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  HoeCfg Stu; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Hoe.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_HOE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&Stu.nId = 0;
        Stu.nDouble = 0;
        Stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        Stu.nNextId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        Stu.nDouble = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,HoeCfg>::operator[](&this->m_HoeCfgMap, &Stu.nId);
        *v1 = Stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTitleTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-1F0h] BYREF
  CfgTitle title; // [rsp+A0h] [rbp-160h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+100h] [rbp-100h] BYREF
  StringVector strParams; // [rsp+110h] [rbp-F0h] BYREF
  std::string dressattr; // [rsp+130h] [rbp-D0h] BYREF
  std::string getttr; // [rsp+140h] [rbp-C0h] BYREF
  std::string params; // [rsp+150h] [rbp-B0h] BYREF
  char v14; // [rsp+15Dh] [rbp-A3h] BYREF
  char v15; // [rsp+15Eh] [rbp-A2h] BYREF
  char v16; // [rsp+15Fh] [rbp-A1h] BYREF
  std::string delims; // [rsp+160h] [rbp-A0h] BYREF
  char v18; // [rsp+16Fh] [rbp-91h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+170h] [rbp-90h] BYREF
  int __x; // [rsp+17Ch] [rbp-84h] BYREF
  AttrAddonVector v21; // [rsp+180h] [rbp-80h] BYREF
  std::string path; // [rsp+1A0h] [rbp-60h] BYREF
  char v23; // [rsp+1AFh] [rbp-51h] BYREF
  AttrAddonVector v24; // [rsp+1B0h] [rbp-50h] BYREF
  std::string v25; // [rsp+1D0h] [rbp-30h] BYREF
  char v26; // [rsp+1DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+1E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1E4h] [rbp-1Ch]
  int32_t i; // [rsp+1E8h] [rbp-18h]
  int32_t nIndex; // [rsp+1ECh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Title.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TITLE_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTitle::CfgTitle(&title);
        nIndex = 0;
        title.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        title.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v14);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&params, v1->pString, &v14);
        std::allocator<char>::~allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&readFile, i, ++nIndex);
        std::string::operator=(&title.sPlatform, v2->pString);
        title.nJob = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        title.nSex = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        title.nSpecial = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        title.nPriority = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v15);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&getttr, v3->pString, &v15);
        std::allocator<char>::~allocator(&v15);
        ++nIndex;
        std::allocator<char>::allocator(&v16);
        v4 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&dressattr, v4->pString, &v16);
        std::allocator<char>::~allocator(&v16);
        ++nIndex;
        std::allocator<char>::allocator(&v18);
        std::string::string(&delims, ":", &v18);
        Answer::StringUtility::split(&strParams, &params, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v18);
        for ( it._M_current = std::vector<std::string>::begin(&strParams)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strParams)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v6 = (const char *)std::string::c_str(v5);
          __x = atoi(v6);
          std::vector<int>::push_back(&title.vParams, &__x);
        }
        std::allocator<char>::allocator(&v23);
        std::string::string(&path, "./ServerConfig/Tables/Title.txt", &v23);
        CfgData::paraseAttrAddon(&v21, this, &getttr, i, &path);
        std::vector<AttrAddon>::operator=(&title.vGetAttr, &v21);
        std::vector<AttrAddon>::~vector(&v21);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v23);
        std::allocator<char>::allocator(&v26);
        std::string::string(&v25, "./ServerConfig/Tables/Title.txt", &v26);
        CfgData::paraseAttrAddon(&v24, this, &dressattr, i, &v25);
        std::vector<AttrAddon>::operator=(&title.vDressAttr, &v24);
        std::vector<AttrAddon>::~vector(&v24);
        std::string::~string(&v25);
        std::allocator<char>::~allocator(&v26);
        CfgTitleTable::Add(&this->m_cfgTitleTable, &title);
        std::vector<std::string>::~vector(&strParams);
        std::string::~string(&dressattr);
        std::string::~string(&getttr);
        std::string::~string(&params);
        CfgTitle::~CfgTitle(&title);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGoldEggTable(CfgData *const this)
{
  int v1; // ebx
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgGoldEgg stu; // [rsp+A0h] [rbp-70h] BYREF
  int iValue; // [rsp+C8h] [rbp-48h]
  int32_t iBaseTableCount; // [rsp+D8h] [rbp-38h]
  int32_t iBaseColumnCount; // [rsp+DCh] [rbp-34h]
  int32_t i; // [rsp+E0h] [rbp-30h]
  int32_t nIndex; // [rsp+E4h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+F0h] [rbp-20h]
  int32_t i_0; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+F8h] [rbp-18h]
  int32_t nId; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ItemGoldEggOpen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOLD_EGG_OPEN_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgGoldEgg::CfgGoldEgg(&stu);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nGroupId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nOpenTimes = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nCostMoney = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nCostGold = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgGoldEggTable::AddGoldEgg(&this->m_cfgGoldEggTable, &stu);
        CfgGoldEgg::~CfgGoldEgg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ItemGoldEgg.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOLD_EGG_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, sizeof(stu));
          iValue = 0;
          nId = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          stu.nId = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          LOBYTE(stu.nGroupId) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu.nOpenTimes = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          LOBYTE(stu.nCostMoney) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu.nCostGold = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          *((_BYTE *)&stu.nCostGold + 4) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          LODWORD(stu.lstItem._M_impl._M_node._M_next) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          HIDWORD(stu.lstItem._M_impl._M_node._M_next) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          LODWORD(stu.lstItem._M_impl._M_node._M_prev) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          HIDWORD(stu.lstItem._M_impl._M_node._M_prev) = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          iValue = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CfgGoldEggTable::AddGoldEggProduce(&this->m_cfgGoldEggTable, nId, (const CfgGoldEggItem *const)&stu);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile);
  }
}


#####################################
void __cdecl CfgData::InitLimitTimeTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const char *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-E0h] BYREF
  std::string strTime; // [rsp+A0h] [rbp-50h] BYREF
  CfgLimitTime stu; // [rsp+B0h] [rbp-40h] BYREF
  char v6; // [rsp+BFh] [rbp-31h] BYREF
  std::string p_StringTime; // [rsp+C0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/LimitTime.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LIMIT_TIME_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.nIndex = 0;
        stu.nTime = 0;
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strTime, v1->pString, &v6);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        if ( stu.nType == 2 )
        {
          std::string::string(&p_StringTime, &strTime);
          Answer::DayTime::StringToIntTime(&p_StringTime);
          std::string::~string(&p_StringTime);
        }
        else if ( stu.nType == 3 || stu.nType == 1 )
        {
          v2 = (const char *)std::string::c_str(&strTime);
          stu.nTime = atoi(v2);
        }
        CfgLimitTimeTable::AddLimitTime(&this->m_cfgLimitTimeTable, &stu);
        std::string::~string(&strTime);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMysteryShopTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  __int64 v3; // rax
  MemChrBag v4; // [rsp+0h] [rbp-150h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-128h]
  CDBCFile readFile; // [rsp+30h] [rbp-120h] BYREF
  CfgMysteryShop stu; // [rsp+C0h] [rbp-90h] BYREF
  std::string strItem; // [rsp+110h] [rbp-40h] BYREF
  char v9; // [rsp+11Fh] [rbp-31h] BYREF
  std::string v10; // [rsp+120h] [rbp-30h] BYREF
  char v11; // [rsp+12Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]
  ItemData v17; // 0:kr00_12.12

  thisa = this;
  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MysteriousShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSTERY_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v9);
        CItemHelper::parseItemString(&v4, &strItem);
        stu.item = v4;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v9);
        stu.nCostType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nPrice = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.nRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nMinLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nMaxLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBroad = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v10, v2->pString, &v11);
        v17 = CItemHelper::parseItemDataString(&v10);
        LODWORD(v3) = v17.m_nId;
        BYTE4(v3) = v17.m_nClass;
        *(_QWORD *)&stu.exchange.m_nId = v3;
        stu.exchange.m_nCount = v17.m_nCount;
        std::string::~string(&v10);
        std::allocator<char>::~allocator(&v11);
        ++nIndex;
        CfgMysteryShopTable::Add(&thisa->m_cfgMysteryShopTable, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitBuyGiftTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgBuyGift *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgBuyGift stu; // [rsp+A0h] [rbp-80h] BYREF
  std::string items; // [rsp+D0h] [rbp-50h] BYREF
  char v6; // [rsp+DFh] [rbp-41h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TimeLimit.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BUY_GIFT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgBuyGift::CfgBuyGift(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nGold = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&items, v1->pString, &v6);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        nIndex += 3;
        stu.nBroad = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CItemHelper::parseItemVectorString(&__x, &items);
        std::vector<MemChrBag>::operator=(&stu.vGift, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        v2 = std::map<int,CfgBuyGift>::operator[](&this->m_cfgBuyGiftTable, &stu.nIndex);
        CfgBuyGift::operator=(v2, &stu);
        std::string::~string(&items);
        CfgBuyGift::~CfgBuyGift(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMysteryGiftTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgMysteryGift stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MysteriousGift.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSTERY_GIFT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgMysteryGift::CfgMysteryGift(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nCondition = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        nIndex += 3;
        stu.nBroadId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgMysteryGiftTable::Add(&this->m_cfgMysteryGiftTable, &stu);
        CfgMysteryGift::~CfgMysteryGift(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitDrawTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgDrawReward stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBag item; // [rsp+D0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Draw.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DRAW_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgDrawReward::CfgDrawReward(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nRate = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        memset(&item, 0, sizeof(item));
        item.itemClass = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        item.itemId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        item.itemCount = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        item.bind = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nBroad = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::vector<MemChrBag>::push_back(&stu.vItem, &item);
        CfgDrawTable::Add(&this->m_cfgDrawTable, &stu);
        CfgDrawReward::~CfgDrawReward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitFlopTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  FlopDrawCfg *v2; // rax
  MemChrBag v3; // [rsp+0h] [rbp-120h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-F8h]
  CDBCFile readFile; // [rsp+30h] [rbp-F0h] BYREF
  FlopDrawCfg stu; // [rsp+C0h] [rbp-60h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FlopActivity.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FLOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.m_nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.m_nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v8);
        CItemHelper::parseItemString(&v3, &strItem);
        stu.m_Item = v3;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v8);
        stu.m_nRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.m_GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,FlopDrawCfg>::operator[](&thisa->m_FlopDrawCfgMap, &stu.m_nId);
        *v2 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitLevelChatTimesTable(CfgData *const this)
{
  int *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  int32_t nLevel; // [rsp+A4h] [rbp-2Ch] BYREF
  int32_t iBaseTableCount; // [rsp+ACh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+B0h] [rbp-20h]
  int32_t i; // [rsp+B4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+B8h] [rbp-18h]
  int32_t nTimes; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/PublicChatTimes.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_LEVEL_CHAT_TIMES_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nLevel = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        nTimes = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,int>::operator[](&this->m_cfgLevelChatTable, &nLevel);
        *v1 = nTimes;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
int32_t __cdecl CfgData::GetChatTimes(const CfgData *const this, int32_t nLevel)
{
  int32_t nLevela; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,int> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nLevela = nLevel;
  iter._M_node = std::map<int,int>::find(&this->m_cfgLevelChatTable, &nLevela)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_cfgLevelChatTable)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter)->second;
  else
    return -1;
}


#####################################
void __cdecl CfgData::InitSuperMemberTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgSuperMember *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  std::string platform; // [rsp+A0h] [rbp-40h] BYREF
  CfgSuperMember stu; // [rsp+B0h] [rbp-30h]
  char v6; // [rsp+BEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SuperMember.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SUPER_MEMBER_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.nGold = 0;
        stu.nIcon = 0;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&platform, v1->pString, &v6);
        std::allocator<char>::~allocator(&v6);
        stu.nGold = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nQQ = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.nIcon = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<std::string,CfgSuperMember>::operator[](&this->m_cfgSuperMember, &platform);
        *v2 = stu;
        std::string::~string(&platform);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitSouGouSkinTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgSouGouSkin *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgSouGouSkin stu; // [rsp+A0h] [rbp-80h] BYREF
  std::string platform; // [rsp+C0h] [rbp-60h] BYREF
  char v7; // [rsp+CFh] [rbp-51h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v10; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SogouSkin.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SOU_GOU_SKIN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vReward);
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&platform, v1->pString, &v7);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v10);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v10);
        stu.nIcon = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<std::string,CfgSouGouSkin>::operator[](&this->m_cfgSouGouSkin, &platform);
        CfgSouGouSkin::operator=(v3, &stu);
        std::string::~string(&platform);
        CfgSouGouSkin::~CfgSouGouSkin(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitPetEquipTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-190h] BYREF
  CfgPetEquip stu; // [rsp+A0h] [rbp-100h] BYREF
  AttrAddonVector __x; // [rsp+100h] [rbp-A0h] BYREF
  std::string path; // [rsp+120h] [rbp-80h] BYREF
  char v7; // [rsp+12Fh] [rbp-71h] BYREF
  std::string addonAttr; // [rsp+130h] [rbp-70h] BYREF
  char v9; // [rsp+13Fh] [rbp-61h] BYREF
  AttrAddonVector v10; // [rsp+140h] [rbp-60h] BYREF
  std::string v11; // [rsp+160h] [rbp-40h] BYREF
  char v12; // [rsp+16Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+170h] [rbp-30h] BYREF
  char v14; // [rsp+17Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/PetEquip.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PET_EQUIP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 84);
        std::vector<AttrAddon>::vector(&stu.vAttr);
        std::vector<AttrAddon>::vector(&stu.vOwnerAttr);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nPrice = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nQuality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nSuitId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        std::string::string(&path, "./ServerConfig/Tables/PetEquip.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&addonAttr, v1->pString, &v9);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        nIndex += 5;
        stu.nBroadcast = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.bCanDrop = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nGrade = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v12);
        std::string::string(&v11, "./ServerConfig/Tables/PetEquip.txt", &v12);
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v13, v2->pString, &v14);
        CfgData::paraseAttrAddon(&v10, this, &v13, i, &v11);
        std::vector<AttrAddon>::operator=(&stu.vOwnerAttr, &v10);
        std::vector<AttrAddon>::~vector(&v10);
        std::string::~string(&v13);
        std::allocator<char>::~allocator(&v14);
        std::string::~string(&v11);
        std::allocator<char>::~allocator(&v12);
        stu.nNeedStar = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgPetEquipTable::AddEquip(&this->m_cfgPetEquipTable, &stu);
        CfgPetEquip::~CfgPetEquip(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitWeiXinTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgWeiXingGift stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/WeiXin.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WEI_XIN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.strPlatform);
        std::vector<MemChrBag>::vector(&stu.vReward);
        nIndex = 0;
        v1 = CDBCFile::Search_Posistion(&readFile, i, 0);
        std::string::operator=(&stu, v1->pString);
        stu.nIconId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        CfgWeiXinTable::Add(&this->m_cfgWeiXinTable, &stu);
        CfgWeiXingGift::~CfgWeiXingGift(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitAdultGiftTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgAdultGift stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShenFenYanZheng.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ADULT_GIFT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.strPlatform);
        std::vector<MemChrBag>::vector(&stu.vReward);
        nIndex = 1;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&readFile, i, ++nIndex);
        std::string::operator=(&stu, v2->pString);
        stu.nIconId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgAdultGiftTable::Add(&this->m_cfgAdultGiftTable, &stu);
        CfgAdultGift::~CfgAdultGift(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMapRoadTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-180h] BYREF
  CfgMapRoad stu; // [rsp+A0h] [rbp-F0h] BYREF
  StringVector vPos; // [rsp+C0h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-B0h] BYREF
  StringVector vRoad; // [rsp+F0h] [rbp-A0h] BYREF
  std::string strRoad; // [rsp+110h] [rbp-80h] BYREF
  char v13; // [rsp+11Fh] [rbp-71h] BYREF
  std::string delims; // [rsp+120h] [rbp-70h] BYREF
  char v15; // [rsp+12Fh] [rbp-61h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+130h] [rbp-60h] BYREF
  std::string v17; // [rsp+140h] [rbp-50h] BYREF
  char v18; // [rsp+14Fh] [rbp-41h] BYREF
  Position __x; // [rsp+150h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+168h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+16Ch] [rbp-24h]
  int32_t i; // [rsp+170h] [rbp-20h]
  int32_t nIndex; // [rsp+174h] [rbp-1Ch]
  int32_t x; // [rsp+178h] [rbp-18h]
  int32_t y; // [rsp+17Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MapRoad.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_ROAD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgMapRoad::CfgMapRoad(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nNextIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nMapId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v13);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strRoad, v1->pString, &v13);
        std::allocator<char>::~allocator(&v13);
        ++nIndex;
        std::allocator<char>::allocator(&v15);
        std::string::string(&delims, "|", &v15);
        Answer::StringUtility::split(&vRoad, &strRoad, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v15);
        for ( iter._M_current = std::vector<std::string>::begin(&vRoad)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<std::string>::end(&vRoad)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
            break;
          std::allocator<char>::allocator(&v18);
          std::string::string(&v17, ":", &v18);
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
          Answer::StringUtility::split(&vPos, v2, &v17, 0);
          std::string::~string(&v17);
          std::allocator<char>::~allocator(&v18);
          if ( std::vector<std::string>::size(&vPos) == 2 )
          {
            v3 = std::vector<std::string>::operator[](&vPos, 0);
            v4 = (const char *)std::string::c_str(v3);
            x = atoi(v4);
            v5 = std::vector<std::string>::operator[](&vPos, 1u);
            v6 = (const char *)std::string::c_str(v5);
            y = atoi(v6);
            Position::Position(&__x, x, y);
            std::list<Position>::push_back(&stu.road, &__x);
          }
          std::vector<std::string>::~vector(&vPos);
        }
        CfgMapRoadTable::Add(&this->m_cfgMapRoadTable, &stu);
        std::vector<std::string>::~vector(&vRoad);
        std::string::~string(&strRoad);
        CfgMapRoad::~CfgMapRoad(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMYSJRewardTable(CfgData *const this)
{
  CCardGroupBoxManager *v1; // rax
  CCardGroupBoxManager *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgMYSJReward stu; // [rsp+A0h] [rbp-80h] BYREF
  CardGroup card; // [rsp+D0h] [rbp-50h] BYREF
  CardGroupList cardList; // [rsp+E0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-2Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-28h]
  int32_t nGroupId; // [rsp+FCh] [rbp-24h]
  int32_t nGroupIndex; // [rsp+100h] [rbp-20h]
  int32_t i; // [rsp+104h] [rbp-1Ch]
  int32_t nIndex; // [rsp+108h] [rbp-18h]
  int32_t nId; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MoYuShiJieReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSJ_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      nGroupId = 0;
      nGroupIndex = 0;
      std::list<CardGroup>::list(&cardList);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nClass = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBind = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nWeight = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nShow = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nGroup = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nMin = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nMax = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBroad = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nSpecial = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        if ( stu.nGroup > 0 && stu.nWeight > 0 )
        {
          if ( nGroupId )
          {
            if ( stu.nGroup != nGroupId )
            {
              v1 = Answer::Singleton<CCardGroupBoxManager>::instance();
              CCardGroupBoxManager::Add(v1, nGroupId, &cardList);
              nGroupId = stu.nGroup;
              nGroupIndex = 0;
              std::list<CardGroup>::clear(&cardList);
            }
          }
          else
          {
            nGroupId = stu.nGroup;
          }
          stu.nIndex = ++nGroupIndex;
          card.id = nGroupIndex;
          card.count = stu.nWeight;
          card.min = stu.nMin;
          card.max = stu.nMax;
          std::list<CardGroup>::push_back(&cardList, &card);
        }
        CfgMYSJRewardTable::Add(&this->m_cfgMYSJRewardTable, nId, &stu);
      }
      if ( nGroupId > 0 )
      {
        v2 = Answer::Singleton<CCardGroupBoxManager>::instance();
        CCardGroupBoxManager::Add(v2, nGroupId, &cardList);
      }
      std::list<CardGroup>::~list(&cardList);
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMaintainCompensateTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgMaintainCompensate stu; // [rsp+A0h] [rbp-80h] BYREF
  std::string p_StringTime; // [rsp+C0h] [rbp-60h] BYREF
  char v6; // [rsp+CFh] [rbp-51h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MaintainCompensate.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MAINTAIN_COMPENSATE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgMaintainCompensate::CfgMaintainCompensate(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&p_StringTime, v1->pString, &v6);
        stu.nTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v9);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        CfgMaintainCompensateTable::Add(&this->m_cfgMaintainCompensateTable, &stu);
        CfgMaintainCompensate::~CfgMaintainCompensate(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitWishRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgWishReward stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+EAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+F0h] [rbp-20h]
  int32_t i; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+F8h] [rbp-18h]
  int32_t nId; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/WishReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WISH_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgWishReward::CfgWishReward(&stu);
        nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nTime = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        ++nIndex;
        CfgWishRewardTable::Add(&this->m_cfgWishRewardTable, nId, &stu);
        CfgWishReward::~CfgWishReward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitBFZLEnterCostTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  ItemDataList vItem; // [rsp+A0h] [rbp-40h] BYREF
  bool bCombi[10]; // [rsp+B0h] [rbp-30h] BYREF
  char v5; // [rsp+BAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+BCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+C0h] [rbp-20h]
  int32_t i; // [rsp+C4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+C8h] [rbp-18h]
  int32_t nTimes; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/BingFengZouLang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BFZL_ENTER_COST_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        nTimes = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v5);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v5);
        CItemHelper::parseItemDataListString((const std::string *const)&vItem, (bool)bCombi);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v5);
        ++nIndex;
        CfgBFZLEnterCostTable::AddEnterCost(&this->m_cfgBFZLEnterCostTable, nTimes, &vItem);
        std::list<ItemData>::~list(&vItem);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitBlacketMarketTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile readFile; // [rsp+20h] [rbp-150h] BYREF
  MemChrBag item3; // [rsp+B0h] [rbp-C0h] BYREF
  MemChrBag item2; // [rsp+D0h] [rbp-A0h] BYREF
  MemChrBag item1; // [rsp+F0h] [rbp-80h] BYREF
  std::string strItem; // [rsp+110h] [rbp-60h] BYREF
  char v9; // [rsp+11Fh] [rbp-51h] BYREF
  std::string v10; // [rsp+120h] [rbp-50h] BYREF
  char v11; // [rsp+12Fh] [rbp-41h] BYREF
  std::string v12; // [rsp+130h] [rbp-40h] BYREF
  char v13; // [rsp+13Ah] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+13Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+140h] [rbp-30h]
  int32_t i; // [rsp+144h] [rbp-2Ch]
  int32_t nIndex; // [rsp+148h] [rbp-28h]
  int32_t nDays; // [rsp+14Ch] [rbp-24h]
  int8_t nOrder; // [rsp+153h] [rbp-1Dh]
  int32_t nOldPrice; // [rsp+154h] [rbp-1Ch]
  int32_t nPrice; // [rsp+158h] [rbp-18h]
  int32_t nBroadcast; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/BlackMarket.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BLACK_MARKET_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nDays = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        nOrder = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v9);
        CItemHelper::parseItemString(&item1, &strItem);
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v10, v2->pString, &v11);
        CItemHelper::parseItemString(&item2, &v10);
        std::string::~string(&v10);
        std::allocator<char>::~allocator(&v11);
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v12, v3->pString, &v13);
        CItemHelper::parseItemString(&item3, &v12);
        std::string::~string(&v12);
        std::allocator<char>::~allocator(&v13);
        nOldPrice = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        nPrice = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        nBroadcast = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgBlacketMarketTable::Add(&this->m_cfgBlacketMarketTable, nDays, nOrder, 1, &item1, nPrice, nBroadcast);
        CfgBlacketMarketTable::Add(&this->m_cfgBlacketMarketTable, nDays, nOrder, 2, &item2, nPrice, nBroadcast);
        CfgBlacketMarketTable::Add(&this->m_cfgBlacketMarketTable, nDays, nOrder, 3, &item3, nPrice, nBroadcast);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitExchangeTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-130h] BYREF
  CfgExchange stu; // [rsp+A0h] [rbp-A0h] BYREF
  std::string rewards; // [rsp+D0h] [rbp-70h] BYREF
  std::string items; // [rsp+E0h] [rbp-60h] BYREF
  char v7; // [rsp+EEh] [rbp-52h] BYREF
  char v8; // [rsp+EFh] [rbp-51h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-50h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/JiZiDuiJiang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EXCHANGE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgExchange::CfgExchange(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&items, v1->pString, &v7);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&rewards, v2->pString, &v8);
        std::allocator<char>::~allocator(&v8);
        stu.nLimit = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)&items);
        std::list<ItemData>::operator=(&stu.vCost, &strItems);
        std::list<ItemData>::~list(&strItems);
        CItemHelper::parseItemVectorString(&__x, &rewards);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        CfgExchangeTable::Add(&this->m_cfgExchangeTable, &stu);
        std::string::~string(&rewards);
        std::string::~string(&items);
        CfgExchange::~CfgExchange(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitFamilyWarJoinRewardTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  int32_t iBaseTableCount; // [rsp+A8h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+ACh] [rbp-24h]
  int32_t i; // [rsp+B0h] [rbp-20h]
  int32_t nIndex; // [rsp+B4h] [rbp-1Ch]
  int32_t level; // [rsp+B8h] [rbp-18h]
  int32_t exp; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FamilyWarJoinReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_FAMILY_WAR_JOIN_REWARD_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        level = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        exp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgFamilyWarTable::AddJoinReward(&this->m_cfgFamilyWarTable, level, exp);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitFamilyLightExpTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+30h] [rbp-D0h] BYREF
  PassionBubbleCfg stu; // [rsp+C0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+DCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+E0h] [rbp-20h]
  int32_t i; // [rsp+E4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+E8h] [rbp-18h]
  int32_t Rate; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/PassionBubble.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_LIGHT_EXP_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.X = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Y = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Money = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Score = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        Rate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        if ( Rate <= 1 )
          stu.nId = 0;
        CfgFamilyLightExpTable::Add(&this->m_cfgFamilyLightExpTable, stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitHorseRacingRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgHorseRacingReward reward; // [rsp+A0h] [rbp-80h] BYREF
  std::string strItem; // [rsp+D0h] [rbp-50h] BYREF
  char v5; // [rsp+DFh] [rbp-41h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/HorseRacintReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_HORSE_RACING_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&reward, 0, sizeof(reward));
        std::vector<MemChrBag>::vector(&reward.Items);
        reward.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        reward.nMaxIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        reward.nExp = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        reward.nMoney = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v5);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v5);
        std::allocator<char>::~allocator(&v5);
        ++nIndex;
        CItemHelper::parseItemVectorString(&__x, &strItem);
        std::vector<MemChrBag>::operator=(&reward.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        CfgHorseRacingRewardTable::Add(&this->m_cfgHorseRacingRewardTable, &reward);
        std::string::~string(&strItem);
        CfgHorseRacingReward::~CfgHorseRacingReward(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitCampWarRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-150h] BYREF
  CfgCampWarReward reward; // [rsp+A0h] [rbp-C0h] BYREF
  std::string failItem; // [rsp+E0h] [rbp-80h] BYREF
  std::string winItem; // [rsp+F0h] [rbp-70h] BYREF
  char v7; // [rsp+FEh] [rbp-62h] BYREF
  char v8; // [rsp+FFh] [rbp-61h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-60h] BYREF
  MemChrBagVector v10; // [rsp+120h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+144h] [rbp-1Ch]
  int32_t i; // [rsp+148h] [rbp-18h]
  int32_t nIndex; // [rsp+14Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/CampWarReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CAMP_WAR_REWARD_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&reward, 0, sizeof(reward));
        std::vector<MemChrBag>::vector(&reward.FailItems);
        std::vector<MemChrBag>::vector(&reward.WinItems);
        reward.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        reward.nMaxIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        reward.nWinMailId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        reward.nFailMailId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&winItem, v1->pString, &v7);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&failItem, v2->pString, &v8);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        CItemHelper::parseItemVectorString(&__x, &failItem);
        std::vector<MemChrBag>::operator=(&reward.FailItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        CItemHelper::parseItemVectorString(&v10, &winItem);
        std::vector<MemChrBag>::operator=(&reward.WinItems, &v10);
        std::vector<MemChrBag>::~vector(&v10);
        CfgCampWarTable::AddReward(&this->m_cfgCampWarTable, &reward);
        std::string::~string(&failItem);
        std::string::~string(&winItem);
        CfgCampWarReward::~CfgCampWarReward(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitCampWarContKillTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgCampWarContKill contKill; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/CampWarContKill.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CAMP_WAR_CONT_KILL_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&contKill, 0, sizeof(contKill));
        contKill.nLevel = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        contKill.nKillCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        contKill.nKillPoint = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        contKill.nBroadcast = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        contKill.nBreakBroadcast = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        contKill.nTitle = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgCampWarTable::AddContKill(&this->m_cfgCampWarTable, &contKill);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitCityWarContRewardTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgCityWarContReward stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GongChengZhanJiangLi.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_CITY_WAR_CONT_REWARD_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 36);
        std::vector<MemChrBag>::vector(&stu.vBreakReward);
        stu.id = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v6);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vBreakReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v6);
        stu.nBreakMailId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgCityWarTable::AddContReward(&this->m_cfgCityWarTable, &stu);
        CfgCityWarContReward::~CfgCityWarContReward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitHallOfFameRewardTable(CfgData *const this)
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
  size_t v13; // rbx
  CDBCFile readFile; // [rsp+10h] [rbp-170h] BYREF
  HallOfFameReward reward; // [rsp+A0h] [rbp-E0h] BYREF
  MemChrBag item; // [rsp+D0h] [rbp-B0h] BYREF
  StringVector vParam; // [rsp+F0h] [rbp-90h] BYREF
  StringVector vItems; // [rsp+110h] [rbp-70h] BYREF
  std::string items; // [rsp+130h] [rbp-50h] BYREF
  char v20; // [rsp+13Fh] [rbp-41h] BYREF
  std::string delims; // [rsp+140h] [rbp-40h] BYREF
  char v22; // [rsp+14Fh] [rbp-31h] BYREF
  std::string v23; // [rsp+150h] [rbp-30h] BYREF
  char v24; // [rsp+15Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+15Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+160h] [rbp-20h]
  int32_t i; // [rsp+164h] [rbp-1Ch]
  int32_t nIndex; // [rsp+168h] [rbp-18h]
  uint32_t j; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FameReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_HALL_OF_FAME_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        HallOfFameReward::HallOfFameReward(&reward);
        nIndex = 0;
        reward.nIndexMin = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        reward.nIndexMax = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        reward.nHonor = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v20);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&items, v1->pString, &v20);
        std::allocator<char>::~allocator(&v20);
        ++nIndex;
        if ( std::string::size(&items) > 3u )
        {
          std::allocator<char>::allocator(&v22);
          std::string::string(&delims, "|", &v22);
          Answer::StringUtility::split(&vItems, &items, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v22);
          for ( j = 0; ; ++j )
          {
            v13 = j;
            if ( v13 >= std::vector<std::string>::size(&vItems) )
              break;
            std::allocator<char>::allocator(&v24);
            std::string::string(&v23, ":", &v24);
            v2 = std::vector<std::string>::operator[](&vItems, j);
            Answer::StringUtility::split(&vParam, v2, &v23, 0);
            std::string::~string(&v23);
            std::allocator<char>::~allocator(&v24);
            if ( std::vector<std::string>::size(&vParam) == 5 )
            {
              memset(&item, 0, sizeof(item));
              v3 = std::vector<std::string>::operator[](&vParam, 0);
              v4 = (const char *)std::string::c_str(v3);
              item.itemId = atoi(v4);
              v5 = std::vector<std::string>::operator[](&vParam, 1u);
              v6 = (const char *)std::string::c_str(v5);
              item.itemClass = atoi(v6);
              v7 = std::vector<std::string>::operator[](&vParam, 2u);
              v8 = (const char *)std::string::c_str(v7);
              item.itemCount = atoi(v8);
              v9 = std::vector<std::string>::operator[](&vParam, 3u);
              v10 = (const char *)std::string::c_str(v9);
              item.bind = atoi(v10);
              v11 = std::vector<std::string>::operator[](&vParam, 4u);
              v12 = (const char *)std::string::c_str(v11);
              item.endTime = atoi(v12);
              std::vector<MemChrBag>::push_back(&reward.items, &item);
            }
            std::vector<std::string>::~vector(&vParam);
          }
          std::vector<std::string>::~vector(&vItems);
        }
        CfgHallOfFameTable::AddReward(&this->m_cfgHallOfFameTable, &reward);
        std::string::~string(&items);
        HallOfFameReward::~HallOfFameReward(&reward);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitSkillLevelUpTable(CfgData *const this)
{
  int32_t v1; // ebx
  int32_t v2; // ebx
  CDBCFile readFile; // [rsp+10h] [rbp-F0h] BYREF
  CfgSkillLevelUp cfgSkill; // [rsp+A0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+D8h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+DCh] [rbp-24h]
  int32_t i; // [rsp+E0h] [rbp-20h]
  int32_t nIndex; // [rsp+E4h] [rbp-1Ch]
  int32_t j; // [rsp+E8h] [rbp-18h]
  int32_t k; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillLevelUp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SKILL_LEVEL_UP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      memset(&cfgSkill, 0, sizeof(cfgSkill));
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        bzero(&cfgSkill, 0x2Cu);
        cfgSkill.nSkillId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        for ( j = 0; j <= 4; ++j )
        {
          v1 = j;
          cfgSkill.nBookId[v1] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        }
        for ( k = 0; k <= 4; ++k )
        {
          v2 = k;
          cfgSkill.nBattle[v2] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        }
        CfgSkillLevelUpTable::Add(&this->m_cfgSkillLevelUpTable, &cfgSkill);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTaskCycleStarTable(CfgData *const this)
{
  int32_t v1; // ebx
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CycleStarRate stu; // [rsp+A0h] [rbp-80h] BYREF
  int32_t vRate[10]; // [rsp+D0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+FCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+100h] [rbp-20h]
  int32_t i; // [rsp+104h] [rbp-1Ch]
  int32_t nIndex; // [rsp+108h] [rbp-18h]
  int32_t j; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TaskCycleStar.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TASK_CYCLE_STAR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      memset(vRate, 0, sizeof(vRate));
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        for ( j = 0; j <= 9; ++j )
        {
          v1 = j;
          stu.Rate[v1] = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        }
        stu.TenStarTimes = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgTaskCycleTable::AddStarRate(&this->m_cfgTaskCycleTable, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTaskCycleRewardTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  TaskCycleReward stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TaskCycleReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TASK_CYCLE_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        memset(&stu, 0, sizeof(stu));
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        stu.nClass = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBind = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgTaskCycleTable::AddTaskReward(&this->m_cfgTaskCycleTable, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitDaTiHD(CfgData *const this)
{
  std::vector<CfgQuestions> *v1; // rax
  CDBCFile ReadFile; // [rsp+10h] [rbp-C0h] BYREF
  CfgQuestions Stu; // [rsp+A0h] [rbp-30h] BYREF
  int __k; // [rsp+A8h] [rbp-28h] BYREF
  int32_t BaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t BaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t j; // [rsp+B8h] [rbp-18h]
  int8_t nType; // [rsp+BFh] [rbp-11h]

  CDBCFile::CDBCFile(&ReadFile, 0);
  if ( !CDBCFile::OpenFromTXT(&ReadFile, "./ServerConfig/Tables/Questions.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_QUESTIONS_TABLE.txt failed,please check!!!\n");
  }
  else
  {
    BaseTableCount = CDBCFile::GetRecordsNum(&ReadFile);
    BaseColumnCount = CDBCFile::GetFieldsNum(&ReadFile);
    if ( BaseColumnCount > 0 )
    {
      for ( j = 0; j < BaseTableCount; ++j )
      {
        Stu = 0;
        Stu.QuestionId = CDBCFile::Search_Posistion(&ReadFile, j, 0)->iValue;
        Stu.AnswerId = CDBCFile::Search_Posistion(&ReadFile, j, 6)->iValue;
        nType = CDBCFile::Search_Posistion(&ReadFile, j, 7)->iValue;
        __k = nType;
        v1 = std::map<int,std::vector<CfgQuestions>>::operator[](&this->m_mQuestions, &__k);
        std::vector<CfgQuestions>::push_back(v1, &Stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&ReadFile);
}


#####################################
void __cdecl CfgData::InitFaBaoTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  CfgFaBao stu; // [rsp+A0h] [rbp-90h] BYREF
  AttrAddonVector __x; // [rsp+D0h] [rbp-60h] BYREF
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+10Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+110h] [rbp-20h]
  int32_t iValue; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int8_t Type; // [rsp+11Fh] [rbp-11h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/FaBao.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FA_BAO_TABLE.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      iValue = 0;
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgFaBao::CfgFaBao(&stu);
        Type = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.FaBaoLevel = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        stu.NeedCurr = CDBCFile::Search_Posistion(&readFile, i, 3)->iValue;
        stu.nNeedLevel = CDBCFile::Search_Posistion(&readFile, i, 4)->iValue;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/FaBao.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, 6);
        std::string::string(&addonAttr, v1->pString, &v8);
        CfgData::paraseAttrAddon(&__x, this, &addonAttr, i, &path);
        std::vector<AttrAddon>::operator=(&stu.vAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        std::string::~string(&addonAttr);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, 7)->iValue;
        FaBaoTable::AddFaBao(&this->m_FaBaoTable, Type, &stu);
        CfgFaBao::~CfgFaBao(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitBossInfo(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  BossInfo *v2; // rax
  CDBCFile InitBossFile; // [rsp+10h] [rbp-100h] BYREF
  BossInfo stu; // [rsp+A0h] [rbp-70h] BYREF
  std::vector<Position> __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&InitBossFile, 0);
  if ( !CDBCFile::OpenFromTXT(&InitBossFile, "./ServerConfig/Tables/BossInfo.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_INFO_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&InitBossFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&InitBossFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        BossInfo::BossInfo(&stu);
        stu.m_nBossId = CDBCFile::Search_Posistion(&InitBossFile, i, 0)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&InitBossFile, i, 1);
        std::string::string(&strPos, v1->pString, &v7);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.m_vRevivePos, &__x);
        std::vector<Position>::~vector(&__x);
        std::string::~string(&strPos);
        std::allocator<char>::~allocator(&v7);
        v2 = std::map<int,BossInfo>::operator[](&this->m_BossInfo, &stu.m_nBossId);
        BossInfo::operator=(v2, &stu);
        BossInfo::~BossInfo(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&InitBossFile);
}


#####################################
void __cdecl CfgData::InitPkDropRateTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  PkDropRate stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/PkDrop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFilePkDrop);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        stu.PkValues = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.EquipCount = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        stu.EquipRate = CDBCFile::Search_Posistion(&readFile, i, 2)->iValue;
        stu.UsualCountRate = CDBCFile::Search_Posistion(&readFile, i, 3)->iValue;
        stu.UsualDropRate = CDBCFile::Search_Posistion(&readFile, i, 4)->iValue;
        stu.OverlayRate = CDBCFile::Search_Posistion(&readFile, i, 5)->iValue;
        stu.MoneyRate = CDBCFile::Search_Posistion(&readFile, i, 6)->iValue;
        std::list<PkDropRate>::push_back(&this->m_PkDropRateList, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGroupMonster(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::vector<GroupMonster> *v2; // rax
  CDBCFile InitBossFile; // [rsp+10h] [rbp-110h] BYREF
  GroupMonster stu; // [rsp+A0h] [rbp-80h] BYREF
  int32_t MapId; // [rsp+CCh] [rbp-54h] BYREF
  std::vector<Position> __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&InitBossFile, 0);
  if ( !CDBCFile::OpenFromTXT(&InitBossFile, "./ServerConfig/Tables/RegionRefresh.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_INFO_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&InitBossFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&InitBossFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,std::vector<GroupMonster>>::clear(&this->m_GroupMonsterMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<Position>::vector(&stu.RevivePos);
        MapId = CDBCFile::Search_Posistion(&InitBossFile, i, 0)->iValue;
        stu.RegionCount = CDBCFile::Search_Posistion(&InitBossFile, i, 1)->iValue;
        stu.Mid = CDBCFile::Search_Posistion(&InitBossFile, i, 2)->iValue;
        stu.MonsterCount = CDBCFile::Search_Posistion(&InitBossFile, i, 3)->iValue;
        stu.IsSpecial = CDBCFile::Search_Posistion(&InitBossFile, i, 4)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&InitBossFile, i, 5);
        std::string::string(&strPos, v1->pString, &v8);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.RevivePos, &__x);
        std::vector<Position>::~vector(&__x);
        std::string::~string(&strPos);
        std::allocator<char>::~allocator(&v8);
        v2 = std::map<int,std::vector<GroupMonster>>::operator[](&this->m_GroupMonsterMap, &MapId);
        std::vector<GroupMonster>::push_back(v2, &stu);
        GroupMonster::~GroupMonster(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&InitBossFile);
}


#####################################
void __cdecl CfgData::InitSysMail(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  CfgSysMail *v5; // rax
  CDBCFile SysMailFile; // [rsp+10h] [rbp-120h] BYREF
  CfgSysMail mail; // [rsp+A0h] [rbp-90h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v10; // [rsp+112h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+114h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+118h] [rbp-18h]
  int32_t i; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&SysMailFile, 0);
  if ( !CDBCFile::OpenFromTXT(&SysMailFile, "./ServerConfig/Tables/cfg_sys_mail.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SYS_MAIL_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&SysMailFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&SysMailFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgSysMail::CfgSysMail(&mail);
        mail.id = CDBCFile::Search_Posistion(&SysMailFile, i, 0)->iValue;
        v1 = CDBCFile::Search_Posistion(&SysMailFile, i, 1);
        std::string::operator=(&mail.sender_name, v1->pString);
        v2 = CDBCFile::Search_Posistion(&SysMailFile, i, 2);
        std::string::operator=(&mail.title, v2->pString);
        v3 = CDBCFile::Search_Posistion(&SysMailFile, i, 3);
        std::string::operator=(&mail.content, v3->pString);
        std::allocator<char>::allocator(&v10);
        v4 = CDBCFile::Search_Posistion(&SysMailFile, i, 4);
        std::string::string(&strItems, v4->pString, &v10);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&mail.item, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v10);
        v5 = std::map<int,CfgSysMail>::operator[](&this->m_sysMail, &mail.id);
        CfgSysMail::operator=(v5, &mail);
        CfgSysMail::~CfgSysMail(&mail);
      }
    }
  }
  CDBCFile::~CDBCFile(&SysMailFile);
}


#####################################
void __cdecl CfgData::InitShangChengTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgGameShop *v3; // rax
  CDBCFile ShangChengTable; // [rsp+10h] [rbp-110h] BYREF
  CfgGameShop ShangCheng; // [rsp+A0h] [rbp-80h] BYREF
  std::string p_StringTime; // [rsp+E0h] [rbp-40h] BYREF
  char v7; // [rsp+EFh] [rbp-31h] BYREF
  std::string v8; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&ShangChengTable, 0);
  if ( !CDBCFile::OpenFromTXT(&ShangChengTable, "./ServerConfig/Tables/cfg_game_shop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GAME_SHOP_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&ShangChengTable);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&ShangChengTable);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&ShangCheng, 0, sizeof(ShangCheng));
        ShangCheng.ShopId = CDBCFile::Search_Posistion(&ShangChengTable, i, 0)->iValue;
        ShangCheng.ItemId = CDBCFile::Search_Posistion(&ShangChengTable, i, 1)->iValue;
        ShangCheng.ItemClass = CDBCFile::Search_Posistion(&ShangChengTable, i, 2)->iValue;
        ShangCheng.ItemBind = CDBCFile::Search_Posistion(&ShangChengTable, i, 3)->iValue;
        ShangCheng.LimitType = CDBCFile::Search_Posistion(&ShangChengTable, i, 4)->iValue;
        ShangCheng.LimitCount = CDBCFile::Search_Posistion(&ShangChengTable, i, 5)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&ShangChengTable, i, 6);
        std::string::string(&p_StringTime, v1->pString, &v7);
        ShangCheng.LimitStartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v7);
        std::allocator<char>::allocator(&v9);
        v2 = CDBCFile::Search_Posistion(&ShangChengTable, i, 7);
        std::string::string(&v8, v2->pString, &v9);
        ShangCheng.LimitEndTime = Answer::DayTime::StringToIntTime(&v8);
        std::string::~string(&v8);
        std::allocator<char>::~allocator(&v9);
        ShangCheng.OriginalPrice = CDBCFile::Search_Posistion(&ShangChengTable, i, 8)->iValue;
        ShangCheng.Price = CDBCFile::Search_Posistion(&ShangChengTable, i, 9)->iValue;
        ShangCheng.ShopType = CDBCFile::Search_Posistion(&ShangChengTable, i, 10)->iValue;
        ShangCheng.CostType = CDBCFile::Search_Posistion(&ShangChengTable, i, 13)->iValue;
        ShangCheng.VipLevelLimit = CDBCFile::Search_Posistion(&ShangChengTable, i, 14)->iValue;
        ShangCheng.BroadcastId = CDBCFile::Search_Posistion(&ShangChengTable, i, 16)->iValue;
        v3 = std::map<int,CfgGameShop>::operator[](&this->m_GameShopMap, &ShangCheng.ShopId);
        *v3 = ShangCheng;
      }
    }
  }
  CDBCFile::~CDBCFile(&ShangChengTable);
}


#####################################
void __cdecl CfgData::InitSpeed360Reward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile Speed360Revard; // [rsp+10h] [rbp-100h] BYREF
  std::string p_StringTime; // [rsp+A0h] [rbp-70h] BYREF
  char v6; // [rsp+AFh] [rbp-61h] BYREF
  std::string v7; // [rsp+B0h] [rbp-60h] BYREF
  char v8; // [rsp+BFh] [rbp-51h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v11; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&Speed360Revard, 0);
  if ( !CDBCFile::OpenFromTXT(&Speed360Revard, "./ServerConfig/Tables/Speed360Reward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_REWARD failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&Speed360Revard);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&Speed360Revard);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&Speed360Revard, i, 1);
        std::string::string(&p_StringTime, v1->pString, &v6);
        this->m_Speed360Reward.StartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v6);
        std::allocator<char>::allocator(&v8);
        v2 = CDBCFile::Search_Posistion(&Speed360Revard, i, 2);
        std::string::string(&v7, v2->pString, &v8);
        this->m_Speed360Reward.EndTime = Answer::DayTime::StringToIntTime(&v7);
        std::string::~string(&v7);
        std::allocator<char>::~allocator(&v8);
        std::allocator<char>::allocator(&v11);
        v3 = CDBCFile::Search_Posistion(&Speed360Revard, i, 4);
        std::string::string(&strItems, v3->pString, &v11);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&this->m_Speed360Reward.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v11);
      }
    }
  }
  CDBCFile::~CDBCFile(&Speed360Revard);
}


#####################################
void __cdecl CfgData::InitVplanTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  CDBCFile VplanEveryRevard; // [rsp+10h] [rbp-3B0h] BYREF
  CDBCFile VplanLevelRevard; // [rsp+A0h] [rbp-320h] BYREF
  CDBCFile VplanRevard; // [rsp+130h] [rbp-290h] BYREF
  VplanReward stu; // [rsp+1C0h] [rbp-200h] BYREF
  MemChrBagVector __x; // [rsp+200h] [rbp-1C0h] BYREF
  std::string strItems; // [rsp+220h] [rbp-1A0h] BYREF
  char v12; // [rsp+22Fh] [rbp-191h] BYREF
  MemChrBagVector v13; // [rsp+230h] [rbp-190h] BYREF
  std::string v14; // [rsp+250h] [rbp-170h] BYREF
  char v15; // [rsp+25Fh] [rbp-161h] BYREF
  VplanReward p_stu; // [rsp+260h] [rbp-160h] BYREF
  MemChrBagVector v17; // [rsp+2A0h] [rbp-120h] BYREF
  std::string v18; // [rsp+2C0h] [rbp-100h] BYREF
  char v19; // [rsp+2CFh] [rbp-F1h] BYREF
  VplanLevelReward v20; // [rsp+2D0h] [rbp-F0h] BYREF
  MemChrBagVector v21; // [rsp+2F0h] [rbp-D0h] BYREF
  std::string v22; // [rsp+310h] [rbp-B0h] BYREF
  char v23; // [rsp+31Fh] [rbp-A1h] BYREF
  MemChrBagVector v24; // [rsp+320h] [rbp-A0h] BYREF
  std::string v25; // [rsp+340h] [rbp-80h] BYREF
  char v26; // [rsp+34Fh] [rbp-71h] BYREF
  VplanEveryDayReward v27; // [rsp+350h] [rbp-70h] BYREF
  bool ret; // [rsp+38Bh] [rbp-35h]
  int32_t iBaseTableCount; // [rsp+38Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+390h] [rbp-30h]
  int32_t VplanLeveTableCount; // [rsp+394h] [rbp-2Ch]
  int32_t VplanLeveColumnCount; // [rsp+398h] [rbp-28h]
  int32_t VplanEveryRevardTableCount; // [rsp+39Ch] [rbp-24h]
  int32_t VplanEveryRevardColumnCount; // [rsp+3A0h] [rbp-20h]
  int32_t i; // [rsp+3A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+3A8h] [rbp-18h]
  int32_t i_1; // [rsp+3ACh] [rbp-14h]

  CDBCFile::CDBCFile(&VplanRevard, 0);
  ret = CDBCFile::OpenFromTXT(&VplanRevard, "./ServerConfig/Tables/VplanReward.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_REWARD failed,please check!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&VplanRevard);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&VplanRevard);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.Reward);
        std::vector<MemChrBag>::vector(&stu.YearVipReward);
        stu.Index = CDBCFile::Search_Posistion(&VplanRevard, i, 0)->iValue;
        std::allocator<char>::allocator(&v12);
        v1 = CDBCFile::Search_Posistion(&VplanRevard, i, 1);
        std::string::string(&strItems, v1->pString, &v12);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Reward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v12);
        std::allocator<char>::allocator(&v15);
        v2 = CDBCFile::Search_Posistion(&VplanRevard, i, 2);
        std::string::string(&v14, v2->pString, &v15);
        CItemHelper::parseItemVectorString(&v13, &v14);
        std::vector<MemChrBag>::operator=(&stu.YearVipReward, &v13);
        std::vector<MemChrBag>::~vector(&v13);
        std::string::~string(&v14);
        std::allocator<char>::~allocator(&v15);
        VplanReward::VplanReward(&p_stu, &stu);
        CfgVplan::AddVplanReward(&this->m_CfgVplan, &p_stu);
        VplanReward::~VplanReward(&p_stu);
        VplanReward::~VplanReward(&stu);
      }
      CDBCFile::CDBCFile(&VplanLevelRevard, 0);
      ret = CDBCFile::OpenFromTXT(&VplanLevelRevard, "./ServerConfig/Tables/VplanLevelReward.txt");
      if ( !ret )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_LEVEL_REWARD failed,please check!!\n");
      }
      else
      {
        VplanLeveTableCount = CDBCFile::GetRecordsNum(&VplanLevelRevard);
        VplanLeveColumnCount = CDBCFile::GetFieldsNum(&VplanLevelRevard);
        if ( VplanLeveColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < VplanLeveTableCount; ++i_0 )
          {
            memset(&stu, 0, 32);
            std::vector<MemChrBag>::vector(&stu.Reward);
            stu.Index = CDBCFile::Search_Posistion(&VplanLevelRevard, i_0, 0)->iValue;
            *(&stu.Index + 1) = CDBCFile::Search_Posistion(&VplanLevelRevard, i_0, 1)->iValue;
            std::allocator<char>::allocator(&v19);
            v3 = CDBCFile::Search_Posistion(&VplanLevelRevard, i_0, 2);
            std::string::string(&v18, v3->pString, &v19);
            CItemHelper::parseItemVectorString(&v17, &v18);
            std::vector<MemChrBag>::operator=(&stu.Reward, &v17);
            std::vector<MemChrBag>::~vector(&v17);
            std::string::~string(&v18);
            std::allocator<char>::~allocator(&v19);
            VplanLevelReward::VplanLevelReward(&v20, (const VplanLevelReward *const)&stu);
            CfgVplan::AddVplanLevelReward(&this->m_CfgVplan, &v20);
            VplanLevelReward::~VplanLevelReward(&v20);
            VplanLevelReward::~VplanLevelReward((VplanLevelReward *const)&stu);
          }
          CDBCFile::CDBCFile(&VplanEveryRevard, 0);
          ret = CDBCFile::OpenFromTXT(&VplanEveryRevard, "./ServerConfig/Tables/VplanEverydayReward.txt");
          if ( !ret )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open FILE_VPLAN_EVERYDAY_REWARD failed,please check!!\n");
          }
          else
          {
            VplanEveryRevardTableCount = CDBCFile::GetRecordsNum(&VplanEveryRevard);
            VplanEveryRevardColumnCount = CDBCFile::GetFieldsNum(&VplanEveryRevard);
            if ( VplanEveryRevardColumnCount > 0 )
            {
              for ( i_1 = 0; i_1 < VplanEveryRevardTableCount; ++i_1 )
              {
                memset(&stu, 0, sizeof(stu));
                std::vector<MemChrBag>::vector(&stu.Reward);
                std::vector<MemChrBag>::vector(&stu.YearVipReward);
                stu.Index = CDBCFile::Search_Posistion(&VplanEveryRevard, i_1, 0)->iValue;
                *(&stu.Index + 1) = CDBCFile::Search_Posistion(&VplanEveryRevard, i_1, 1)->iValue;
                std::allocator<char>::allocator(&v23);
                v4 = CDBCFile::Search_Posistion(&VplanEveryRevard, i_1, 2);
                std::string::string(&v22, v4->pString, &v23);
                CItemHelper::parseItemVectorString(&v21, &v22);
                std::vector<MemChrBag>::operator=(&stu.Reward, &v21);
                std::vector<MemChrBag>::~vector(&v21);
                std::string::~string(&v22);
                std::allocator<char>::~allocator(&v23);
                std::allocator<char>::allocator(&v26);
                v5 = CDBCFile::Search_Posistion(&VplanEveryRevard, i_1, 3);
                std::string::string(&v25, v5->pString, &v26);
                CItemHelper::parseItemVectorString(&v24, &v25);
                std::vector<MemChrBag>::operator=(&stu.YearVipReward, &v24);
                std::vector<MemChrBag>::~vector(&v24);
                std::string::~string(&v25);
                std::allocator<char>::~allocator(&v26);
                VplanEveryDayReward::VplanEveryDayReward(&v27, (const VplanEveryDayReward *const)&stu);
                CfgVplan::AddVplanEveryDayReward(&this->m_CfgVplan, &v27);
                VplanEveryDayReward::~VplanEveryDayReward(&v27);
                VplanEveryDayReward::~VplanEveryDayReward((VplanEveryDayReward *const)&stu);
              }
            }
          }
          CDBCFile::~CDBCFile(&VplanEveryRevard);
        }
      }
      CDBCFile::~CDBCFile(&VplanLevelRevard);
    }
  }
  CDBCFile::~CDBCFile(&VplanRevard);
}


#####################################
void __cdecl CfgData::InitShunWangTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile SwVipBuff; // [rsp+10h] [rbp-290h] BYREF
  CDBCFile SwBarVip; // [rsp+A0h] [rbp-200h] BYREF
  CDBCFile SwVip; // [rsp+130h] [rbp-170h] BYREF
  CfgSwVipReward stu; // [rsp+1C0h] [rbp-E0h] BYREF
  Param2 stu_0; // [rsp+1F0h] [rbp-B0h] BYREF
  MemChrBagVector __x; // [rsp+200h] [rbp-A0h] BYREF
  std::string strItems; // [rsp+220h] [rbp-80h] BYREF
  char v10; // [rsp+22Fh] [rbp-71h] BYREF
  MemChrBagVector v11; // [rsp+230h] [rbp-70h] BYREF
  std::string v12; // [rsp+250h] [rbp-50h] BYREF
  char v13; // [rsp+25Ah] [rbp-46h] BYREF
  bool ret; // [rsp+25Bh] [rbp-45h]
  int32_t SwVipTableCount; // [rsp+25Ch] [rbp-44h]
  int32_t SwVipColumnCount; // [rsp+260h] [rbp-40h]
  int32_t SwBarVipTableCount; // [rsp+264h] [rbp-3Ch]
  int32_t SwBarVipColumnCount; // [rsp+268h] [rbp-38h]
  int32_t SwVipBuffTableCount; // [rsp+26Ch] [rbp-34h]
  int32_t SwVipBuffColumnCount; // [rsp+270h] [rbp-30h]
  int32_t i; // [rsp+274h] [rbp-2Ch]
  int32_t nIndex; // [rsp+278h] [rbp-28h]
  int32_t i_0; // [rsp+27Ch] [rbp-24h]
  int32_t nIndex_0; // [rsp+280h] [rbp-20h]
  int32_t i_1; // [rsp+284h] [rbp-1Ch]
  int32_t nIndex_1; // [rsp+288h] [rbp-18h]
  int8_t nType; // [rsp+28Fh] [rbp-11h]

  CDBCFile::CDBCFile(&SwVip, 0);
  ret = CDBCFile::OpenFromTXT(&SwVip, "./ServerConfig/Tables/ShunWangHuiYuan.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SW_VIP_REWARD failed,please check!!\n");
  }
  else
  {
    SwVipTableCount = CDBCFile::GetRecordsNum(&SwVip);
    SwVipColumnCount = CDBCFile::GetFieldsNum(&SwVip);
    if ( SwVipColumnCount > 0 )
    {
      for ( i = 0; i < SwVipTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vReward);
        stu.nIndex = CDBCFile::Search_Posistion(&SwVip, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&SwVip, i, nIndex++)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&SwVip, i, nIndex);
        std::string::string(&strItems, v1->pString, &v10);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v10);
        stu.nCondition = CDBCFile::Search_Posistion(&SwVip, i, ++nIndex)->iValue;
        ++nIndex;
        CfgVplan::AddSwVipReward(&this->m_CfgVplan, &stu);
        CfgSwVipReward::~CfgSwVipReward(&stu);
      }
      CDBCFile::CDBCFile(&SwBarVip, 0);
      ret = CDBCFile::OpenFromTXT(&SwBarVip, "./ServerConfig/Tables/ShunWangWangBa.txt");
      if ( !ret )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SW_BAR_VIP_REWARD failed,please check!!\n");
      }
      else
      {
        SwBarVipTableCount = CDBCFile::GetRecordsNum(&SwBarVip);
        SwBarVipColumnCount = CDBCFile::GetFieldsNum(&SwBarVip);
        if ( SwBarVipColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < SwBarVipTableCount; ++i_0 )
          {
            nIndex_0 = 0;
            memset(&stu, 0, sizeof(stu));
            std::vector<MemChrBag>::vector(&stu.vReward);
            stu.nIndex = CDBCFile::Search_Posistion(&SwBarVip, i_0, nIndex_0++)->iValue;
            stu.nType = CDBCFile::Search_Posistion(&SwBarVip, i_0, nIndex_0++)->iValue;
            ++nIndex_0;
            std::allocator<char>::allocator(&v13);
            v2 = CDBCFile::Search_Posistion(&SwBarVip, i_0, nIndex_0);
            std::string::string(&v12, v2->pString, &v13);
            CItemHelper::parseItemVectorString(&v11, &v12);
            std::vector<MemChrBag>::operator=(&stu.vReward, &v11);
            std::vector<MemChrBag>::~vector(&v11);
            std::string::~string(&v12);
            std::allocator<char>::~allocator(&v13);
            stu.nCondition = CDBCFile::Search_Posistion(&SwBarVip, i_0, ++nIndex_0)->iValue;
            ++nIndex_0;
            CfgVplan::AddSwVipBarReward(&this->m_CfgVplan, &stu);
            CfgSwVipReward::~CfgSwVipReward(&stu);
          }
          CDBCFile::CDBCFile(&SwVipBuff, 0);
          ret = CDBCFile::OpenFromTXT(&SwVipBuff, "./ServerConfig/Tables/ShunWangVIPBuff.txt");
          if ( !ret )
          {
            Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SW_VIP_BUFF failed,please check!!\n");
          }
          else
          {
            SwVipBuffTableCount = CDBCFile::GetRecordsNum(&SwVipBuff);
            SwVipBuffColumnCount = CDBCFile::GetFieldsNum(&SwVipBuff);
            if ( SwVipBuffColumnCount > 0 )
            {
              for ( i_1 = 0; i_1 < SwVipBuffTableCount; ++i_1 )
              {
                nIndex_1 = 0;
                Param2::Param2(&stu_0, 0, 0);
                nType = CDBCFile::Search_Posistion(&SwVipBuff, i_1, ++nIndex_1)->iValue;
                stu_0.nParam1 = CDBCFile::Search_Posistion(&SwVipBuff, i_1, ++nIndex_1)->iValue;
                ++nIndex_1;
                stu_0.nParam2 = CDBCFile::Search_Posistion(&SwVipBuff, i_1, ++nIndex_1)->iValue;
                ++nIndex_1;
                CfgVplan::AddSwVipExpRatio(&this->m_CfgVplan, nType, &stu_0);
              }
            }
          }
          CDBCFile::~CDBCFile(&SwVipBuff);
        }
      }
      CDBCFile::~CDBCFile(&SwBarVip);
    }
  }
  CDBCFile::~CDBCFile(&SwVip);
}


#####################################
void __cdecl CfgData::InitGoblinData(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-140h] BYREF
  cfgGoblinData stu; // [rsp+A0h] [rbp-B0h] BYREF
  std::string path; // [rsp+E0h] [rbp-70h] BYREF
  char v6; // [rsp+EFh] [rbp-61h] BYREF
  std::string str; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  std::vector<Position> __x; // [rsp+100h] [rbp-50h] BYREF
  std::string strPos; // [rsp+120h] [rbp-30h] BYREF
  char v11; // [rsp+132h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+134h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+138h] [rbp-18h]
  int32_t i; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/Goblin.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C7820);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<CurrentData>::vector(&stu.m_RefreshMonsters);
        std::vector<Position>::vector(&stu.m_RevivePosVector);
        stu.m_nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.m_nRefreshTime = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v6);
        std::string::string(&path, "./ServerConfig/Tables/Goblin.txt", &v6);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 2);
        std::string::string(&str, v1->pString, &v8);
        CfgData::parseCurrentDatas(this, &stu.m_RefreshMonsters, &str, i, &path);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v8);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v6);
        stu.m_mapId = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 4);
        std::string::string(&strPos, v2->pString, &v11);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.m_RevivePosVector, &__x);
        std::vector<Position>::~vector(&__x);
        std::string::~string(&strPos);
        std::allocator<char>::~allocator(&v11);
        cfgGoblinTableData::Add(&this->m_cfgGoblinTableData, &stu);
        cfgGoblinData::~cfgGoblinData(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::parseCurrentDatas(
        CfgData *const this,
        CurrentDatas *const currentDatas,
        const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6; // rdx
  CurrentData current; // [rsp+30h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-60h] BYREF
  StringVector strMonsters; // [rsp+50h] [rbp-50h] BYREF
  std::string delims; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+7Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-20h] BYREF

  if ( !(unsigned __int8)std::string::empty((std::string *)str)
    && !std::operator==<char>(str, "-1")
    && !std::operator==<char>(str, "0") )
  {
    std::allocator<char>::allocator(&v14);
    std::string::string(&delims, "|", &v14);
    Answer::StringUtility::split(&strMonsters, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v14);
    for ( it._M_current = std::vector<std::string>::begin(&strMonsters)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strMonsters)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      v6 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      CfgData::parseCurrentData(this, &current, v6, nIndex, path);
      std::vector<CurrentData>::push_back(currentDatas, &current);
    }
    std::vector<std::string>::~vector(&strMonsters);
  }
}


#####################################
void __cdecl CfgData::parseCurrentData(
        CfgData *const this,
        CurrentData *const current,
        const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  const char *v10; // rbx
  const char *v11; // rax
  StringVector strCurrent; // [rsp+30h] [rbp-40h] BYREF
  std::string delims; // [rsp+50h] [rbp-20h] BYREF
  _BYTE v17[17]; // [rsp+5Fh] [rbp-11h] BYREF

  if ( !(unsigned __int8)std::string::empty((std::string *)str)
    && !std::operator==<char>(str, "-1")
    && !std::operator==<char>(str, "0") )
  {
    std::allocator<char>::allocator(v17);
    std::string::string(&delims, ":", v17);
    Answer::StringUtility::split(&strCurrent, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(v17);
    if ( std::vector<std::string>::size(&strCurrent) == 2 )
    {
      v6 = std::vector<std::string>::operator[](&strCurrent, 0);
      v7 = (const char *)std::string::c_str(v6);
      current->nId = atoi(v7);
      v8 = std::vector<std::string>::operator[](&strCurrent, 1u);
      v9 = (const char *)std::string::c_str(v8);
      current->nValue = atoi(v9);
    }
    else
    {
      v10 = (const char *)std::string::c_str((std::string *)str);
      v11 = (const char *)std::string::c_str((std::string *)path);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::parseCurrentData() wrong data from %s, where index = %d, str = %s\n",
        v11,
        nIndex,
        v10);
    }
    std::vector<std::string>::~vector(&strCurrent);
  }
}


#####################################
void __cdecl CfgData::InitSpecialMonster(CfgData *const this)
{
  CDBCFile TabFile; // [rsp+10h] [rbp-D0h] BYREF
  cfgSpecialMonster stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/SpecialMonster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C78C8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        stu.m_mid = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.Type = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        stu.Value = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        stu.Portal = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        stu.Award = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        stu.HurtDrop = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        stu.EscapeOdds = CDBCFile::Search_Posistion(&TabFile, i, 6)->iValue;
        cfgSpecialMonsterTable::Add(&this->m_cfgSpecialMonsterTable, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitEquipUpPhase(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  cfgEquipUpPhase stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-40h] BYREF
  bool bCombi[18]; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/EquipUpPhase.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C7918);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::list<ItemData>::list(&stu.m_CostItems);
        stu.m_CostEquip = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        std::allocator<char>::allocator(&v6);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 1);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.m_CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v6);
        stu.m_CostMoney = CDBCFile::Search_Posistion(&TabFile, i, 2)->iValue;
        stu.m_GiveEquip = CDBCFile::Search_Posistion(&TabFile, i, 3)->iValue;
        stu.m_GongGaoId = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        cfgEquipUpPhaseTable::AddData(&this->m_cfgEquipUpPhaseTable, &stu);
        cfgEquipUpPhase::~cfgEquipUpPhase(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitTouZiTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-1B0h] BYREF
  SevenTouZi stu; // [rsp+A0h] [rbp-120h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-F0h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-D0h] BYREF
  char v8; // [rsp+FFh] [rbp-C1h] BYREF
  SevenTouZi p_stu; // [rsp+100h] [rbp-C0h] BYREF
  MemChrBagVector v10; // [rsp+130h] [rbp-90h] BYREF
  std::string v11; // [rsp+150h] [rbp-70h] BYREF
  char v12; // [rsp+15Fh] [rbp-61h] BYREF
  MonthTouZi v13; // [rsp+160h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+18Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+190h] [rbp-30h]
  int32_t i; // [rsp+194h] [rbp-2Ch]
  int32_t nIndex; // [rsp+198h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+1A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+1ACh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/QiRiTouZi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SEVEN_DAY_TOU_ZI_TABEL failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vItem);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nCondition = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v8);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        SevenTouZi::SevenTouZi(&p_stu, &stu);
        CfgTouZiTable::AddSevenTouZi(&this->m_cfgTouZiTable, &p_stu);
        SevenTouZi::~SevenTouZi(&p_stu);
        SevenTouZi::~SevenTouZi(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/ChaoJiTouZi.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONTH_TOU_ZI_TABLE failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, 36);
          std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.nCondition);
          stu.nId = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0++)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v12);
          v3 = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0);
          std::string::string(&v11, v3->pString, &v12);
          CItemHelper::parseItemVectorString(&v10, &v11);
          std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.nCondition, &v10);
          std::vector<MemChrBag>::~vector(&v10);
          std::string::~string(&v11);
          std::allocator<char>::~allocator(&v12);
          LODWORD(stu.vItem._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(&TabFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          MonthTouZi::MonthTouZi(&v13, (const MonthTouZi *const)&stu);
          CfgTouZiTable::AddMonthTouZi(&this->m_cfgTouZiTable, &v13);
          MonthTouZi::~MonthTouZi(&v13);
          MonthTouZi::~MonthTouZi((MonthTouZi *const)&stu);
        }
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
  }
}


#####################################
void __cdecl CfgData::InitBuyFaBaoResTable(CfgData *const this)
{
  BuyFaBaoResCfg *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  BuyFaBaoResCfg stu; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/BuyFaBaoRes.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBuyFaB);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        stu.id = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.FaBaoResType = CDBCFile::Search_Posistion(&readFile, i, 1)->iValue;
        stu.NeedGold = CDBCFile::Search_Posistion(&readFile, i, 2)->iValue;
        stu.GetResValues = CDBCFile::Search_Posistion(&readFile, i, 3)->iValue;
        v1 = std::map<int,BuyFaBaoResCfg>::operator[](&this->m_FaBaoResMap, &stu.id);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitXingMaiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  XingMaiCfg *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-140h] BYREF
  XingMaiCfg stu; // [rsp+A0h] [rbp-B0h] BYREF
  std::list<ItemData> strItems; // [rsp+E0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+110h] [rbp-40h] BYREF
  char v11; // [rsp+11Fh] [rbp-31h] BYREF
  int32_t v12[3]; // [rsp+120h] [rbp-30h] BYREF
  char v13; // [rsp+12Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/AttributeXingMai.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBuyFaB);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,XingMaiCfg>::clear(&this->m_XingMaiCfgTable);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        XingMaiCfg::XingMaiCfg(&stu);
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.PlayerLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v8);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v8);
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        std::string::string(v10, "./ServerConfig/Tables/AttributeXingMai.txt", &v11);
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v12, v2->pString, &v13);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v12,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.AttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v12);
        std::allocator<char>::~allocator(&v13);
        std::string::~string(v10);
        std::allocator<char>::~allocator(&v11);
        ++nIndex;
        nIndex += 3;
        stu.NeedBossScore = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.BossScoreLimit = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        v3 = std::map<int,XingMaiCfg>::operator[](&this->m_XingMaiCfgTable, &stu.Level);
        XingMaiCfg::operator=(v3, &stu);
        XingMaiCfg::~XingMaiCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitXingMaiSlotTable(CfgData *const this)
{
  CfgXingMaiSlot *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgXingMaiSlot stu; // [rsp+A0h] [rbp-40h]
  int __k; // [rsp+B8h] [rbp-28h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XingMaiSlot.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingma);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nScore = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        __k = stu.nIndex;
        v1 = std::map<int,CfgXingMaiSlot>::operator[](&this->m_cfgXingMaiSlotTable, &__k);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTianLingTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  TianLingCfg *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-130h] BYREF
  TianLingCfg stu; // [rsp+A0h] [rbp-A0h] BYREF
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+E0h] [rbp-60h] BYREF
  char v8; // [rsp+EFh] [rbp-51h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+100h] [rbp-40h] BYREF
  char v11; // [rsp+10Fh] [rbp-31h] BYREF
  int32_t v12[3]; // [rsp+110h] [rbp-30h] BYREF
  char v13; // [rsp+11Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TianLing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileAttrib);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        TianLingCfg::TianLingCfg(&stu);
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.CostMoney = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v8);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        std::string::string(v10, "./ServerConfig/Tables/TianLing.txt", &v11);
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v12, v2->pString, &v13);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v12,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.AttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v12);
        std::allocator<char>::~allocator(&v13);
        std::string::~string(v10);
        std::allocator<char>::~allocator(&v11);
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 4;
        stu.CostCoin = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        v3 = std::map<int,TianLingCfg>::operator[](&this->m_TianLingCfgTable, &stu.Level);
        TianLingCfg::operator=(v3, &stu);
        TianLingCfg::~TianLingCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGongMinTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  GongMingCfg *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  GongMingCfg stu; // [rsp+A0h] [rbp-80h] BYREF
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+E0h] [rbp-40h] BYREF
  char v7; // [rsp+EFh] [rbp-31h] BYREF
  int32_t v8[3]; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GongMing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileGongMi);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        GongMingCfg::GongMingCfg(&stu);
        stu.nChong = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nStar = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.NeedGongMingZhi = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        std::string::string(v6, "./ServerConfig/Tables/GongMing.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v8);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(v6);
        std::allocator<char>::~allocator(&v7);
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,GongMingCfg>::operator[](&this->m_GongMingCfgMap, &stu.nIndex);
        GongMingCfg::operator=(v2, &stu);
        GongMingCfg::~GongMingCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitBeastShrineEnterCostTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  ItemDataList vItem; // [rsp+A0h] [rbp-40h] BYREF
  bool bCombi[10]; // [rsp+B0h] [rbp-30h] BYREF
  char v5; // [rsp+BAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+BCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+C0h] [rbp-20h]
  int32_t i; // [rsp+C4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+C8h] [rbp-18h]
  int32_t nTimes; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/AnimalMapCost.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBfzlEn_0);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nTimes = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v5);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v5);
        CItemHelper::parseItemDataListString((const std::string *const)&vItem, (bool)bCombi);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v5);
        ++nIndex;
        CfgBeastShrineTable::AddEnterCost(&this->m_CfgBeastShrineTable, nTimes, &vItem);
        std::list<ItemData>::~list(&vItem);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitDamnationTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  DamnationCfg *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-140h] BYREF
  DamnationCfg stu; // [rsp+A0h] [rbp-B0h] BYREF
  std::list<ItemData> strItems; // [rsp+E0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+110h] [rbp-40h] BYREF
  char v11; // [rsp+11Fh] [rbp-31h] BYREF
  int32_t v12[3]; // [rsp+120h] [rbp-30h] BYREF
  char v13; // [rsp+12Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Curse.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileDamnat);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        DamnationCfg::DamnationCfg(&stu);
        stu.Level = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v8);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        std::string::string(v10, "./ServerConfig/Tables/Curse.txt", &v11);
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v12, v2->pString, &v13);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v12,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.AttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v12);
        std::allocator<char>::~allocator(&v13);
        std::string::~string(v10);
        std::allocator<char>::~allocator(&v11);
        stu.Probability = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.HpPecent = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 3;
        stu.CostMoney = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        v3 = std::map<int,DamnationCfg>::operator[](&this->m_DamnationCfgTable, &stu.Level);
        DamnationCfg::operator=(v3, &stu);
        DamnationCfg::~DamnationCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitAttrBattleTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  int32_t iBaseTableCount; // [rsp+A8h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+ACh] [rbp-24h]
  int32_t i; // [rsp+B0h] [rbp-20h]
  int32_t nIndex; // [rsp+B4h] [rbp-1Ch]
  int32_t nAttr; // [rsp+B8h] [rbp-18h]
  int32_t nBattle; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/AttrBattle.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ATTR_BATTLE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      bzero(this->m_cfgAttrBattle, 0xC8u);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nAttr = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        nBattle = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        if ( nAttr > 0 && nAttr <= 49 )
          this->m_cfgAttrBattle[nAttr] = nBattle;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
int32_t __cdecl CfgData::GetAttrBattle(CfgData *const this, int32_t nAttr)
{
  if ( nAttr <= 0 || nAttr > 49 )
    return 0;
  else
    return this->m_cfgAttrBattle[nAttr];
}


#####################################
void __cdecl CfgData::InitScoreShopTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  ScoreShopCfg *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  ScoreShopCfg stu; // [rsp+A0h] [rbp-90h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+100h] [rbp-30h] BYREF
  char v7; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ScoreShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SCORE_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,ScoreShopCfg>::clear(&this->m_ScoreShopCfgTable);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 73);
        std::list<ItemData>::list(&stu.CostItems);
        nIndex = 0;
        stu.Index = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        stu.PlayerLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.LimitType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.LimitCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Item.itemId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Item.itemClass = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Item.itemCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Item.bind = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.CostType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.CostValue = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v7);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        stu.IsRecord = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,ScoreShopCfg>::operator[](&this->m_ScoreShopCfgTable, &stu.Index);
        ScoreShopCfg::operator=(v2, &stu);
        ScoreShopCfg::~ScoreShopCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitChouJiangTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  int v4; // ebx
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  __int64 v8; // rax
  MemChrBag v9; // [rsp+50h] [rbp-200h] BYREF
  CfgData *thisa; // [rsp+78h] [rbp-1D8h]
  CDBCFile readFile; // [rsp+80h] [rbp-1D0h] BYREF
  ChouJiangCfg stu; // [rsp+110h] [rbp-140h] BYREF
  ChouJiangLuckyCfg stu_0; // [rsp+160h] [rbp-F0h]
  std::string strItem; // [rsp+170h] [rbp-E0h] BYREF
  char v15; // [rsp+17Fh] [rbp-D1h] BYREF
  MemChrBagVector __x; // [rsp+180h] [rbp-D0h] BYREF
  std::string strItems; // [rsp+1A0h] [rbp-B0h] BYREF
  char v18; // [rsp+1AFh] [rbp-A1h] BYREF
  ChouJiangWeekReward p_stu; // [rsp+1B0h] [rbp-A0h] BYREF
  std::string v20; // [rsp+1D0h] [rbp-80h] BYREF
  char v21; // [rsp+1DFh] [rbp-71h] BYREF
  std::string v22; // [rsp+1E0h] [rbp-70h] BYREF
  char v23; // [rsp+1F2h] [rbp-5Eh] BYREF
  int32_t iBaseTableCount; // [rsp+1F4h] [rbp-5Ch]
  int32_t iBaseColumnCount; // [rsp+1F8h] [rbp-58h]
  int32_t i; // [rsp+1FCh] [rbp-54h]
  int32_t nIndex; // [rsp+200h] [rbp-50h]
  int32_t iBaseTableCount_0; // [rsp+208h] [rbp-48h]
  int32_t iBaseColumnCount_0; // [rsp+20Ch] [rbp-44h]
  int32_t i_0; // [rsp+210h] [rbp-40h]
  int32_t nIndex_0; // [rsp+214h] [rbp-3Ch]
  int32_t iBaseTableCount_1; // [rsp+21Ch] [rbp-34h]
  int32_t iBaseColumnCount_1; // [rsp+220h] [rbp-30h]
  int32_t i_1; // [rsp+224h] [rbp-2Ch]
  int32_t nIndex_1; // [rsp+228h] [rbp-28h]
  int32_t iBaseTableCount_2; // [rsp+230h] [rbp-20h]
  int32_t iBaseColumnCount_2; // [rsp+234h] [rbp-1Ch]
  int32_t i_2; // [rsp+238h] [rbp-18h]
  int32_t nIndex_2; // [rsp+23Ch] [rbp-14h]
  ItemData v44; // 0:kr00_12.12

  thisa = this;
  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TreasureBase.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CHOU_JIANG_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        nIndex = 0;
        stu.Index = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v15);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v2->pString, &v15);
        CItemHelper::parseItemString(&v9, &strItem);
        stu.Item = v9;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v15);
        stu.Quality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Probability = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.SubLuckValue = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.PersonalRecord = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.ServerRecord = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.Type = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MinDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MaxDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.JifenDel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        ChouJiangTable::AddChouJiangCfg(&thisa->m_ChouJiangTable, stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TreasureLucky.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_CHOU_JIANG_LUCK_TABLE failed,please check!!!\n");
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu_0.MaxLucky = 0;
          stu_0.MaxQuality = 0;
          nIndex_0 = 1;
          stu_0.MaxLucky = CDBCFile::Search_Posistion(&readFile, i_0, 1)->iValue;
          stu_0.MinQuality = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu_0.MaxQuality = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          ChouJiangTable::AddChouJiangLuckyCfg(&thisa->m_ChouJiangTable, stu_0);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    CDBCFile::~CDBCFile(&readFile);
    if ( v3 )
    {
      CDBCFile::CDBCFile(&readFile, 0);
      if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TreasureWeek.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_CHOU_JIANG_REWARD_TABLE failed,please check!!!\n");
        v4 = 0;
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&readFile);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&readFile);
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            memset(&stu, 0, 32);
            std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.Item);
            nIndex_1 = 0;
            stu.Index = CDBCFile::Search_Posistion(&readFile, i_1, 0)->iValue;
            *(&stu.Index + 1) = CDBCFile::Search_Posistion(&readFile, i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            std::allocator<char>::allocator(&v18);
            v5 = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1);
            std::string::string(&strItems, v5->pString, &v18);
            CItemHelper::parseItemVectorString(&__x, &strItems);
            std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.Item, &__x);
            std::vector<MemChrBag>::~vector(&__x);
            std::string::~string(&strItems);
            std::allocator<char>::~allocator(&v18);
            ++nIndex_1;
            ChouJiangWeekReward::ChouJiangWeekReward(&p_stu, (const ChouJiangWeekReward *const)&stu);
            ChouJiangTable::AddChouJiangWeekReward(&thisa->m_ChouJiangTable, &p_stu);
            ChouJiangWeekReward::~ChouJiangWeekReward(&p_stu);
            ChouJiangWeekReward::~ChouJiangWeekReward((ChouJiangWeekReward *const)&stu);
          }
          v4 = 1;
        }
        else
        {
          v4 = 0;
        }
      }
      CDBCFile::~CDBCFile(&readFile);
      if ( v4 )
      {
        CDBCFile::CDBCFile(&readFile, 0);
        if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TreasureConsume.txt") )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "open FILE_CHOU_JIANG_REWARD_TABLE failed,please check!!!\n");
        }
        else
        {
          iBaseTableCount_2 = CDBCFile::GetRecordsNum(&readFile);
          iBaseColumnCount_2 = CDBCFile::GetFieldsNum(&readFile);
          if ( iBaseColumnCount_2 > 0 )
          {
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              memset(&stu, 0, 0x38u);
              nIndex_2 = 0;
              stu.Index = CDBCFile::Search_Posistion(&readFile, i_2, 0)->iValue;
              ++nIndex_2;
              std::allocator<char>::allocator(&v21);
              v6 = CDBCFile::Search_Posistion(&readFile, i_2, nIndex_2);
              std::string::string(&v20, v6->pString, &v21);
              v44 = CItemHelper::parseItemDataString(&v20);
              LODWORD(v8) = v44.m_nId;
              BYTE4(v8) = v44.m_nClass;
              *(_QWORD *)(&stu.Index + 1) = v8;
              *(_DWORD *)&stu.Item.itemClass = v44.m_nCount;
              std::string::~string(&v20);
              std::allocator<char>::~allocator(&v21);
              stu.Item.itemCount = CDBCFile::Search_Posistion(&readFile, i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              std::allocator<char>::allocator(&v23);
              v7 = CDBCFile::Search_Posistion(&readFile, i_2, nIndex_2);
              std::string::string(&v22, v7->pString, &v23);
              CItemHelper::parseItemString(&v9, &v22);
              *(MemChrBag *)&stu.Item.endTime = v9;
              std::string::~string(&v22);
              std::allocator<char>::~allocator(&v23);
              ++nIndex_2;
              ChouJiangTable::AddChouJiangCost(&thisa->m_ChouJiangTable, *(ChouJiangCost *)&stu.Index);
            }
          }
        }
        CDBCFile::~CDBCFile(&readFile);
      }
    }
  }
}


#####################################
void __cdecl CfgData::InitLibraryTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  const CDBCFile::FIELD *v4; // rax
  __int64 v5; // rax
  MemChrBag v6; // [rsp+30h] [rbp-190h] BYREF
  CfgData *thisa; // [rsp+58h] [rbp-168h]
  CDBCFile readFile; // [rsp+60h] [rbp-160h] BYREF
  CfgLibraryItem stu; // [rsp+F0h] [rbp-D0h] BYREF
  CfgLibraryCost stu_1; // [rsp+120h] [rbp-A0h] BYREF
  CfgLibraryQuality stu_0; // [rsp+140h] [rbp-80h]
  std::string strItem; // [rsp+150h] [rbp-70h] BYREF
  char v13; // [rsp+15Fh] [rbp-61h] BYREF
  std::string v14; // [rsp+160h] [rbp-60h] BYREF
  char v15; // [rsp+176h] [rbp-4Ah] BYREF
  int32_t iBaseTableCount; // [rsp+178h] [rbp-48h]
  int32_t iBaseColumnCount; // [rsp+17Ch] [rbp-44h]
  int32_t i; // [rsp+180h] [rbp-40h]
  int32_t nIndex; // [rsp+184h] [rbp-3Ch]
  int32_t iBaseTableCount_0; // [rsp+18Ch] [rbp-34h]
  int32_t iBaseColumnCount_0; // [rsp+190h] [rbp-30h]
  int32_t i_0; // [rsp+194h] [rbp-2Ch]
  int32_t nIndex_0; // [rsp+198h] [rbp-28h]
  int32_t iBaseTableCount_1; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount_1; // [rsp+1A4h] [rbp-1Ch]
  int32_t i_1; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex_1; // [rsp+1ACh] [rbp-14h]
  ItemData v31; // 0:kr00_12.12

  thisa = this;
  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ChestItemRandom.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LIBRARY_ITEM_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        nIndex = 0;
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nQuality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v2->pString, &v13);
        CItemHelper::parseItemString(&v6, &strItem);
        stu.Item = v6;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v13);
        stu.Probability = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDunGeonId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CLibraryTable::AddCfgLibraryItem(&thisa->m_CLibraryTable, stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ChestItemQuality.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_LIBRARY_QUALITY__TABLE failed,please check!!!\n");
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu_0.nIndex = 0;
          *(_QWORD *)&stu_0.nCount = 0;
          nIndex_0 = 0;
          stu_0.nIndex = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          stu_0.nQuality = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu_0.nCount = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu_0.nProbability = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CLibraryTable::AddCfgLibraryQuality(&thisa->m_CLibraryTable, stu_0);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    CDBCFile::~CDBCFile(&readFile);
    if ( v3 )
    {
      CDBCFile::CDBCFile(&readFile, 0);
      if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ChestConsume.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_LIBRARY_COST_TABLE failed,please check!!!\n");
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&readFile);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&readFile);
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            memset(&stu_1, 0, sizeof(stu_1));
            nIndex_1 = 0;
            stu_1.Times = CDBCFile::Search_Posistion(&readFile, i_1, 0)->iValue;
            stu_1.nDunGeonId = CDBCFile::Search_Posistion(&readFile, i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            std::allocator<char>::allocator(&v15);
            v4 = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1);
            std::string::string(&v14, v4->pString, &v15);
            v31 = CItemHelper::parseItemDataString(&v14);
            LODWORD(v5) = v31.m_nId;
            BYTE4(v5) = v31.m_nClass;
            *(_QWORD *)&stu_1.Item.m_nId = v5;
            stu_1.Item.m_nCount = v31.m_nCount;
            std::string::~string(&v14);
            std::allocator<char>::~allocator(&v15);
            ++nIndex_1;
            CLibraryTable::AddCfgLibraryCost(&thisa->m_CLibraryTable, stu_1);
          }
        }
      }
      CDBCFile::~CDBCFile(&readFile);
    }
  }
}


#####################################
void __cdecl CfgData::InitTreasureMapTabale(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  int *v8; // rbx
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
  CDBCFile readFile; // [rsp+10h] [rbp-320h] BYREF
  TreasureMapCfg stu; // [rsp+A0h] [rbp-290h] BYREF
  TreasureMapEventCfg stu_0; // [rsp+100h] [rbp-230h] BYREF
  MapPos stuPos; // [rsp+120h] [rbp-210h] BYREF
  StringVector vstr_0; // [rsp+130h] [rbp-200h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin_0; // [rsp+150h] [rbp-1E0h] BYREF
  StringVector SplitStr_0; // [rsp+160h] [rbp-1D0h] BYREF
  StringVector vstr; // [rsp+180h] [rbp-1B0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+1A0h] [rbp-190h] BYREF
  StringVector SplitStr; // [rsp+1B0h] [rbp-180h] BYREF
  std::string MapPosString; // [rsp+1D0h] [rbp-160h] BYREF
  std::string RateString; // [rsp+1E0h] [rbp-150h] BYREF
  char v34; // [rsp+1EEh] [rbp-142h] BYREF
  char v35; // [rsp+1EFh] [rbp-141h] BYREF
  std::string delims; // [rsp+1F0h] [rbp-140h] BYREF
  char v37; // [rsp+1FFh] [rbp-131h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+200h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+210h] [rbp-120h] BYREF
  std::string v40; // [rsp+220h] [rbp-110h] BYREF
  char v41; // [rsp+22Bh] [rbp-105h] BYREF
  int __k; // [rsp+22Ch] [rbp-104h] BYREF
  std::string v43; // [rsp+230h] [rbp-100h] BYREF
  char v44; // [rsp+23Fh] [rbp-F1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v45; // [rsp+240h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v46; // [rsp+250h] [rbp-E0h] BYREF
  std::string v47; // [rsp+260h] [rbp-D0h] BYREF
  char v48; // [rsp+26Fh] [rbp-C1h] BYREF
  Position v49; // [rsp+270h] [rbp-C0h] BYREF
  TreasureMapCfg p_stu; // [rsp+280h] [rbp-B0h] BYREF
  TreasureMapEventCfg v51; // [rsp+2E0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+2FCh] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+300h] [rbp-30h]
  int32_t i; // [rsp+304h] [rbp-2Ch]
  int32_t nIndex; // [rsp+308h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+310h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+314h] [rbp-1Ch]
  int32_t i_0; // [rsp+318h] [rbp-18h]
  int32_t nIndex_0; // [rsp+31Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TreasureMapBase.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TREASURE_MAP_CFG_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::map<int,int>::map(&stu.m_EventRate);
        std::vector<MapPos>::vector(&stu.m_MaxPosVector);
        nIndex = 0;
        stu.m_ItemId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v34);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&RateString, v2->pString, &v34);
        std::allocator<char>::~allocator(&v34);
        ++nIndex;
        std::allocator<char>::allocator(&v35);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&MapPosString, v3->pString, &v35);
        std::allocator<char>::~allocator(&v35);
        ++nIndex;
        if ( std::operator!=<char>(&RateString, &byte_8C33CF) && std::operator!=<char>(&RateString, "-1") )
        {
          std::allocator<char>::allocator(&v37);
          std::string::string(&delims, "|", &v37);
          Answer::StringUtility::split(&SplitStr, &RateString, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v37);
          __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
            &iterBegin,
            &__i);
          while ( 1 )
          {
            __rhs._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
            if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &__rhs) )
              break;
            std::allocator<char>::allocator(&v41);
            std::string::string(&v40, ":", &v41);
            v5 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
            Answer::StringUtility::split(&vstr, v5, &v40, 0);
            std::string::~string(&v40);
            std::allocator<char>::~allocator(&v41);
            if ( std::vector<std::string>::size(&vstr) == 2 )
            {
              v6 = std::vector<std::string>::operator[](&vstr, 0);
              v7 = (const char *)std::string::c_str(v6);
              __k = atoi(v7);
              v8 = std::map<int,int>::operator[](&stu.m_EventRate, &__k);
              v9 = std::vector<std::string>::operator[](&vstr, 1u);
              v10 = (const char *)std::string::c_str(v9);
              *v8 = atoi(v10);
              LODWORD(v8) = stu.m_MaxProbability;
              v11 = std::vector<std::string>::operator[](&vstr, 1u);
              v12 = (const char *)std::string::c_str(v11);
              stu.m_MaxProbability = (_DWORD)v8 + atoi(v12);
            }
            std::vector<std::string>::~vector(&vstr);
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
          }
          std::vector<std::string>::~vector(&SplitStr);
        }
        if ( std::operator!=<char>(&MapPosString, &byte_8C33CF) && std::operator!=<char>(&MapPosString, "-1") )
        {
          std::allocator<char>::allocator(&v44);
          std::string::string(&v43, "|", &v44);
          Answer::StringUtility::split(&SplitStr_0, &MapPosString, &v43, 0);
          std::string::~string(&v43);
          std::allocator<char>::~allocator(&v44);
          v45._M_current = std::vector<std::string>::begin(&SplitStr_0)._M_current;
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
            &iterBegin_0,
            &v45);
          while ( 1 )
          {
            v46._M_current = std::vector<std::string>::end(&SplitStr_0)._M_current;
            if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin_0, &v46) )
              break;
            std::allocator<char>::allocator(&v48);
            std::string::string(&v47, ":", &v48);
            v14 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin_0);
            Answer::StringUtility::split(&vstr_0, v14, &v47, 0);
            std::string::~string(&v47);
            std::allocator<char>::~allocator(&v48);
            if ( std::vector<std::string>::size(&vstr_0) == 3 )
            {
              Position::Position(&v49, 0, 0);
              stuPos.m_MapId = 0;
              stuPos.m_Pos = v49;
              v15 = std::vector<std::string>::operator[](&vstr_0, 0);
              v16 = (const char *)std::string::c_str(v15);
              stuPos.m_MapId = atoi(v16);
              v17 = std::vector<std::string>::operator[](&vstr_0, 1u);
              v18 = (const char *)std::string::c_str(v17);
              stuPos.m_Pos.x = atoi(v18);
              v19 = std::vector<std::string>::operator[](&vstr_0, 2u);
              v20 = (const char *)std::string::c_str(v19);
              stuPos.m_Pos.y = atoi(v20);
              std::vector<MapPos>::push_back(&stu.m_MaxPosVector, &stuPos);
            }
            std::vector<std::string>::~vector(&vstr_0);
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin_0);
          }
          std::vector<std::string>::~vector(&SplitStr_0);
        }
        TreasureMapCfg::TreasureMapCfg(&p_stu, &stu);
        TreasureMapTabale::AddTreasureMapCfg(&this->m_TreasureMapTabale, &p_stu);
        TreasureMapCfg::~TreasureMapCfg(&p_stu);
        std::string::~string(&MapPosString);
        std::string::~string(&RateString);
        TreasureMapCfg::~TreasureMapCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TreasureMapEvent.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_TREASURE_MAP_EVENT_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          memset(&stu_0, 0, 20);
          std::string::string(&stu_0.m_EventParam);
          nIndex_0 = 0;
          stu_0.m_EventId = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          stu_0.m_EventType = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          v21 = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0);
          std::string::operator=(&stu_0.m_EventParam, v21->pString);
          stu_0.m_GongGaoId = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          TreasureMapEventCfg::TreasureMapEventCfg(&v51, &stu_0);
          TreasureMapTabale::AddTreasureMapEventCfg(&this->m_TreasureMapTabale, &v51);
          TreasureMapEventCfg::~TreasureMapEventCfg(&v51);
          TreasureMapEventCfg::~TreasureMapEventCfg(&stu_0);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile);
  }
}


#####################################
void __cdecl CfgData::InitEquipBackTask(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  BackEquipTask *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  std::string *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  std::map<int,std::list<Param2>> *v13; // rax
  std::list<Param2> *v14; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-250h] BYREF
  BackEquipTask stu; // [rsp+A0h] [rbp-1C0h] BYREF
  Param2 stu_0; // [rsp+F0h] [rbp-170h] BYREF
  StringVector TaskRates; // [rsp+100h] [rbp-160h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+120h] [rbp-140h] BYREF
  StringVector TaskRateVetcor; // [rsp+130h] [rbp-130h] BYREF
  Param2List param; // [rsp+150h] [rbp-110h] BYREF
  std::string TaskRate; // [rsp+160h] [rbp-100h] BYREF
  int32_t Times; // [rsp+168h] [rbp-F8h] BYREF
  int32_t Level; // [rsp+16Ch] [rbp-F4h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+170h] [rbp-F0h] BYREF
  StringVector ItemVetcor; // [rsp+180h] [rbp-E0h] BYREF
  std::string NeedEquipString; // [rsp+1A0h] [rbp-C0h] BYREF
  char v28; // [rsp+1AFh] [rbp-B1h] BYREF
  MemChrBagVector __x; // [rsp+1B0h] [rbp-B0h] BYREF
  std::string strItems; // [rsp+1D0h] [rbp-90h] BYREF
  char v31; // [rsp+1DFh] [rbp-81h] BYREF
  std::string delims; // [rsp+1E0h] [rbp-80h] BYREF
  char v33; // [rsp+1EFh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1F0h] [rbp-70h] BYREF
  int v35; // [rsp+1F8h] [rbp-68h] BYREF
  char v36; // [rsp+1FFh] [rbp-61h] BYREF
  std::string v37; // [rsp+200h] [rbp-60h] BYREF
  char v38; // [rsp+20Fh] [rbp-51h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v39; // [rsp+210h] [rbp-50h] BYREF
  std::string v40; // [rsp+220h] [rbp-40h] BYREF
  char v41; // [rsp+22Ah] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+22Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+230h] [rbp-30h]
  int32_t i; // [rsp+234h] [rbp-2Ch]
  int32_t nIndex; // [rsp+238h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+240h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+244h] [rbp-1Ch]
  int32_t i_0; // [rsp+248h] [rbp-18h]
  int32_t nIndex_0; // [rsp+24Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TaskRecovery.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EQUIP_BACK_TASK failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<int>::vector(&stu.Equips);
        std::vector<MemChrBag>::vector(&stu.Items);
        nIndex = 0;
        stu.Index = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v28);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&NeedEquipString, v2->pString, &v28);
        std::allocator<char>::~allocator(&v28);
        stu.PlayerLevelMin = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.PlayerLevelMax = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Star = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GetCurr = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v31);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v3->pString, &v31);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v31);
        stu.RandGold = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v33);
        std::string::string(&delims, "|", &v33);
        Answer::StringUtility::split(&ItemVetcor, &NeedEquipString, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v33);
        for ( it._M_current = std::vector<std::string>::begin(&ItemVetcor)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&ItemVetcor)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          v5 = (const char *)std::string::c_str(v4);
          v35 = atoi(v5);
          std::vector<int>::push_back(&stu.Equips, &v35);
        }
        v6 = std::map<int,BackEquipTask>::operator[](&this->m_EquipBackTable, &stu.Index);
        BackEquipTask::operator=(v6, &stu);
        std::vector<std::string>::~vector(&ItemVetcor);
        std::string::~string(&NeedEquipString);
        BackEquipTask::~BackEquipTask(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/RecoveryTaskRate.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EQUIP_BACK_TASK failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          memset(&stu, 0, sizeof(stu));
          std::vector<int>::vector(&stu.Equips);
          std::vector<MemChrBag>::vector(&stu.Items);
          nIndex_0 = 0;
          Level = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          Times = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v36);
          v7 = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0);
          std::string::string(&TaskRate, v7->pString, &v36);
          std::allocator<char>::~allocator(&v36);
          ++nIndex_0;
          std::list<Param2>::list(&param);
          std::allocator<char>::allocator(&v38);
          std::string::string(&v37, "|", &v38);
          Answer::StringUtility::split(&TaskRateVetcor, &TaskRate, &v37, 0);
          std::string::~string(&v37);
          std::allocator<char>::~allocator(&v38);
          for ( it_0._M_current = std::vector<std::string>::begin(&TaskRateVetcor)._M_current;
                ;
                __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0) )
          {
            v39._M_current = std::vector<std::string>::end(&TaskRateVetcor)._M_current;
            if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v39) )
              break;
            std::allocator<char>::allocator(&v41);
            std::string::string(&v40, ":", &v41);
            v8 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_0);
            Answer::StringUtility::split(&TaskRates, v8, &v40, 0);
            std::string::~string(&v40);
            std::allocator<char>::~allocator(&v41);
            if ( std::vector<std::string>::size(&TaskRates) == 2 )
            {
              Param2::Param2(&stu_0, 0, 0);
              v9 = std::vector<std::string>::operator[](&TaskRates, 0);
              v10 = (const char *)std::string::c_str(v9);
              stu_0.nParam1 = atoi(v10);
              v11 = std::vector<std::string>::operator[](&TaskRates, 1u);
              v12 = (const char *)std::string::c_str(v11);
              stu_0.nParam2 = atoi(v12);
              std::list<Param2>::push_back(&param, &stu_0);
            }
            std::vector<std::string>::~vector(&TaskRates);
          }
          v13 = std::map<int,std::map<int,std::list<Param2>>>::operator[](&this->m_EquipBackTaskRate, &Level);
          v14 = std::map<int,std::list<Param2>>::operator[](v13, &Times);
          std::list<Param2>::operator=(v14, &param);
          std::vector<std::string>::~vector(&TaskRateVetcor);
          std::list<Param2>::~list(&param);
          std::string::~string(&TaskRate);
          BackEquipTask::~BackEquipTask(&stu);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile);
  }
}


#####################################
int32_t __cdecl CfgData::GetEquipBackTaskId(CfgData *const this, int32_t PlayerLevel, int32_t Times)
{
  std::pair<const int,std::map<int,std::list<Param2>> > *v3; // rax
  std::pair<const int,std::map<int,std::list<Param2>> > *v4; // rax
  Answer::Random *v5; // rax
  std::pair<const int,std::list<Param2> > *v6; // rax
  Param2 *v7; // rax
  Param2 *v9; // rax
  std::pair<const int,std::list<Param2> > *v10; // rax
  int32_t Timesa; // [rsp+0h] [rbp-70h] BYREF
  int32_t PlayerLevela; // [rsp+4h] [rbp-6Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-68h]
  std::_List_iterator<Param2> itbeg; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<Param2> > > pIt; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,std::list<Param2>> > > it; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,std::list<Param2>> > > __x; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<Param2> > > v18; // [rsp+50h] [rbp-20h] BYREF
  std::_List_iterator<Param2> v19; // [rsp+60h] [rbp-10h] BYREF
  int32_t TaskId; // [rsp+68h] [rbp-8h]
  int32_t nRand; // [rsp+6Ch] [rbp-4h]

  thisa = this;
  PlayerLevela = PlayerLevel;
  Timesa = Times;
  TaskId = 0;
  it._M_node = std::map<int,std::map<int,std::list<Param2>>>::lower_bound(&this->m_EquipBackTaskRate, &PlayerLevela)._M_node;
  __x._M_node = std::map<int,std::map<int,std::list<Param2>>>::end(&thisa->m_EquipBackTaskRate)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::map<int,std::list<Param2>>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,std::list<Param2>>>>::operator->(&it);
    pIt._M_node = std::map<int,std::list<Param2>>::find(&v3->second, &Timesa)._M_node;
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,std::list<Param2>>>>::operator->(&it);
    v18._M_node = std::map<int,std::list<Param2>>::end(&v4->second)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,std::list<Param2>>>::operator!=(&pIt, &v18) )
    {
      v5 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v5, 1, 10000);
      v6 = std::_Rb_tree_iterator<std::pair<int const,std::list<Param2>>>::operator->(&pIt);
      for ( itbeg._M_node = std::list<Param2>::begin(&v6->second)._M_node;
            ;
            std::_List_iterator<Param2>::operator++(&itbeg, 0) )
      {
        v10 = std::_Rb_tree_iterator<std::pair<int const,std::list<Param2>>>::operator->(&pIt);
        v19._M_node = std::list<Param2>::end(&v10->second)._M_node;
        if ( !std::_List_iterator<Param2>::operator!=(&itbeg, &v19) )
          break;
        v7 = std::_List_iterator<Param2>::operator->(&itbeg);
        if ( v7->nParam2 >= nRand )
          return std::_List_iterator<Param2>::operator->(&itbeg)->nParam1;
        v9 = std::_List_iterator<Param2>::operator->(&itbeg);
        nRand -= v9->nParam2;
      }
    }
  }
  return TaskId;
}


#####################################
void __cdecl CfgData::InitSpeciaEquipCfgMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  SpeciaEquipCfg *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-160h] BYREF
  SpeciaEquipCfg stu; // [rsp+A0h] [rbp-D0h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-80h] BYREF
  _BYTE v7[15]; // [rsp+100h] [rbp-70h] BYREF
  char v8; // [rsp+10Fh] [rbp-61h] BYREF
  int32_t v9[3]; // [rsp+110h] [rbp-60h] BYREF
  char v10; // [rsp+11Fh] [rbp-51h] BYREF
  std::list<AddAttribute> v11; // [rsp+120h] [rbp-50h] BYREF
  _BYTE v12[15]; // [rsp+130h] [rbp-40h] BYREF
  char v13; // [rsp+13Fh] [rbp-31h] BYREF
  int32_t v14[3]; // [rsp+140h] [rbp-30h] BYREF
  char v15; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SpecialEquip.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBuyFaB);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        SpeciaEquipCfg::SpeciaEquipCfg(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        std::string::string(v7, "./ServerConfig/Tables/SpecialEquip.txt", &v8);
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v9, v1->pString, &v10);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v9,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.nAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v9);
        std::allocator<char>::~allocator(&v10);
        std::string::~string(v7);
        std::allocator<char>::~allocator(&v8);
        stu.nNeedVipLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nContinueLogin = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nNeedGold = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        std::string::string(v12, "./ServerConfig/Tables/SpecialEquip.txt", &v13);
        std::allocator<char>::allocator(&v15);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v14, v2->pString, &v15);
        CfgData::parseAddAttribues(
          (CfgData *const)&v11,
          (const std::string *const)this,
          (int32_t)v14,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.nAttrList2, &v11);
        std::list<AddAttribute>::~list(&v11);
        std::string::~string(v14);
        std::allocator<char>::~allocator(&v15);
        std::string::~string(v12);
        std::allocator<char>::~allocator(&v13);
        stu.nGongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        stu.nTalentId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nBuyLimitVipLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,SpeciaEquipCfg>::operator[](&this->m_SpeciaEquipCfgMap, &stu.nIndex);
        SpeciaEquipCfg::operator=(v3, &stu);
        SpeciaEquipCfg::~SpeciaEquipCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitSpeciaSkillDistanceTable(CfgData *const this)
{
  SpeciaSkillDistance *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  SpeciaSkillDistance stu; // [rsp+A0h] [rbp-40h]
  std::pair<int,int> __k; // [rsp+B0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SkillSpecialDamage.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SPECIAL_DAMAGE_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.SkillId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.Distance = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.PoFang = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.SkillModify = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        __k = std::make_pair<int,int>(stu.SkillId, stu.Distance);
        v1 = std::map<std::pair<int,int>,SpeciaSkillDistance>::operator[](&this->m_SpeciaSkillDistanceTable, &__k);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitLuckDropTable(CfgData *const this)
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
  CDBCFile readFile; // [rsp+10h] [rbp-1C0h] BYREF
  SpecialItemDrop SpecialItem; // [rsp+A0h] [rbp-130h] BYREF
  LuckDrop stu; // [rsp+D0h] [rbp-100h] BYREF
  StringVector vstack; // [rsp+F0h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+110h] [rbp-C0h] BYREF
  StringVector ItemVetcor; // [rsp+120h] [rbp-B0h] BYREF
  std::string ItemString; // [rsp+140h] [rbp-90h] BYREF
  char v20; // [rsp+14Fh] [rbp-81h] BYREF
  std::string delims; // [rsp+150h] [rbp-80h] BYREF
  char v22; // [rsp+15Fh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+160h] [rbp-70h] BYREF
  std::string v24; // [rsp+170h] [rbp-60h] BYREF
  char v25; // [rsp+17Fh] [rbp-51h] BYREF
  LuckDrop p_stu; // [rsp+180h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+1B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1B4h] [rbp-1Ch]
  int32_t i; // [rsp+1B8h] [rbp-18h]
  int32_t nIndex; // [rsp+1BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/LuckyRate.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LUCK_DROP_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 28);
        std::list<SpecialItemDrop>::list(&stu.ItemList);
        stu.Type = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.VipLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v20);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&ItemString, v1->pString, &v20);
        std::allocator<char>::~allocator(&v20);
        stu.Rate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v22);
        std::string::string(&delims, "|", &v22);
        Answer::StringUtility::split(&ItemVetcor, &ItemString, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v22);
        for ( it._M_current = std::vector<std::string>::begin(&ItemVetcor)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&ItemVetcor)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          std::allocator<char>::allocator(&v25);
          std::string::string(&v24, ":", &v25);
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          Answer::StringUtility::split(&vstack, v2, &v24, 0);
          std::string::~string(&v24);
          std::allocator<char>::~allocator(&v25);
          if ( std::vector<std::string>::size(&vstack) == 5 )
          {
            memset(&SpecialItem, 0, sizeof(SpecialItem));
            v3 = std::vector<std::string>::operator[](&vstack, 0);
            v4 = (const char *)std::string::c_str(v3);
            SpecialItem.Item.itemId = atoi(v4);
            v5 = std::vector<std::string>::operator[](&vstack, 1u);
            v6 = (const char *)std::string::c_str(v5);
            SpecialItem.Item.itemClass = atoi(v6);
            v7 = std::vector<std::string>::operator[](&vstack, 2u);
            v8 = (const char *)std::string::c_str(v7);
            SpecialItem.Item.itemCount = atoi(v8);
            v9 = std::vector<std::string>::operator[](&vstack, 3u);
            v10 = (const char *)std::string::c_str(v9);
            SpecialItem.Item.bind = atoi(v10);
            v11 = std::vector<std::string>::operator[](&vstack, 4u);
            v12 = (const char *)std::string::c_str(v11);
            SpecialItem.Rate = atoi(v12);
            std::list<SpecialItemDrop>::push_back(&stu.ItemList, &SpecialItem);
          }
          std::vector<std::string>::~vector(&vstack);
        }
        LuckDrop::LuckDrop(&p_stu, &stu);
        LuckDropTable::AddLuckDrop(&this->m_LuckDropTable, &p_stu);
        LuckDrop::~LuckDrop(&p_stu);
        std::vector<std::string>::~vector(&ItemVetcor);
        std::string::~string(&ItemString);
        LuckDrop::~LuckDrop(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitLevelRefiningTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  int32_t v3; // eax
  std::string *v4; // rax
  const char *v5; // rax
  int32_t v6; // eax
  std::string *v7; // rax
  const char *v8; // rax
  LevelRefinCfg *v9; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-180h] BYREF
  LevelRefinCfg stu; // [rsp+A0h] [rbp-F0h] BYREF
  StringVector VLevelUp; // [rsp+E0h] [rbp-B0h] BYREF
  StringVector NeedGoldVetcor; // [rsp+100h] [rbp-90h] BYREF
  std::string sLevelUp; // [rsp+120h] [rbp-70h] BYREF
  std::string vNeedGoldString; // [rsp+130h] [rbp-60h] BYREF
  char v16; // [rsp+13Eh] [rbp-52h] BYREF
  char v17; // [rsp+13Fh] [rbp-51h] BYREF
  std::string delims; // [rsp+140h] [rbp-50h] BYREF
  char v19; // [rsp+14Bh] [rbp-45h] BYREF
  int __x; // [rsp+14Ch] [rbp-44h] BYREF
  std::string v21; // [rsp+150h] [rbp-40h] BYREF
  char v22; // [rsp+15Fh] [rbp-31h] BYREF
  int v23; // [rsp+160h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+168h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+16Ch] [rbp-24h]
  int32_t i; // [rsp+170h] [rbp-20h]
  int32_t nIndex; // [rsp+174h] [rbp-1Ch]
  int32_t j; // [rsp+178h] [rbp-18h]
  int32_t k; // [rsp+17Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/LvRefining.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LEVEL_REFIN_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<int>::vector(&stu.vNeedGold);
        std::vector<int>::vector(&stu.nLevelUp);
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v16);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&vNeedGoldString, v1->pString, &v16);
        std::allocator<char>::~allocator(&v16);
        ++nIndex;
        std::allocator<char>::allocator(&v17);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&sLevelUp, v2->pString, &v17);
        std::allocator<char>::~allocator(&v17);
        stu.nLimit = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nGongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v19);
        std::string::string(&delims, "|", &v19);
        Answer::StringUtility::split(&NeedGoldVetcor, &vNeedGoldString, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v19);
        v3 = std::vector<std::string>::size(&NeedGoldVetcor);
        if ( v3 >= stu.nLimit )
        {
          for ( j = 0; stu.nLimit > j; ++j )
          {
            v4 = std::vector<std::string>::operator[](&NeedGoldVetcor, j);
            v5 = (const char *)std::string::c_str(v4);
            __x = atoi(v5);
            std::vector<int>::push_back(&stu.vNeedGold, &__x);
          }
        }
        std::allocator<char>::allocator(&v22);
        std::string::string(&v21, "|", &v22);
        Answer::StringUtility::split(&VLevelUp, &sLevelUp, &v21, 0);
        std::string::~string(&v21);
        std::allocator<char>::~allocator(&v22);
        v6 = std::vector<std::string>::size(&VLevelUp);
        if ( v6 >= stu.nLimit )
        {
          for ( k = 0; stu.nLimit > k; ++k )
          {
            v7 = std::vector<std::string>::operator[](&VLevelUp, k);
            v8 = (const char *)std::string::c_str(v7);
            v23 = atoi(v8);
            std::vector<int>::push_back(&stu.nLevelUp, &v23);
          }
        }
        v9 = std::map<int,LevelRefinCfg>::operator[](&this->m_LevelRefinCfgMap, &stu.nLevel);
        LevelRefinCfg::operator=(v9, &stu);
        std::vector<std::string>::~vector(&VLevelUp);
        std::vector<std::string>::~vector(&NeedGoldVetcor);
        std::string::~string(&sLevelUp);
        std::string::~string(&vNeedGoldString);
        LevelRefinCfg::~LevelRefinCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitBossFirstKilledTable(CfgData *const this)
{
  CfgBossFirstKilled *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgBossFirstKilled stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/BossKill.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BOSS_FIRST_KILLED_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.Mid = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.RewardType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.RewardValue = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.StartDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.EndDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,CfgBossFirstKilled>::operator[](&this->m_CfgBossFirstKilledMap, &stu.Mid);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitUltimateChallengeCfg(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  UltimateChallengeCfg *v4; // rax
  __int64 v5; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-170h] BYREF
  UltimateChallengeCfg stu; // [rsp+A0h] [rbp-E0h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-90h] BYREF
  char v9; // [rsp+FFh] [rbp-81h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-80h] BYREF
  std::string strItems; // [rsp+120h] [rbp-60h] BYREF
  char v12; // [rsp+12Fh] [rbp-51h] BYREF
  std::list<Param2> v13; // [rsp+130h] [rbp-50h] BYREF
  _BYTE v14[15]; // [rsp+140h] [rbp-40h] BYREF
  char v15; // [rsp+14Fh] [rbp-31h] BYREF
  int32_t v16[3]; // [rsp+150h] [rbp-30h] BYREF
  char v17; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]
  ItemData v23; // 0:kr00_12.12

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/limitChallenge.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ULTIMATE_CHALLENGE_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.GetItems);
        std::list<Param2>::list(&stu.DropRateList);
        stu.CurMapId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.NextMapId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        nIndex += 2;
        stu.Floor = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v9);
        v23 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v5) = v23.m_nId;
        BYTE4(v5) = v23.m_nClass;
        *(_QWORD *)&stu.CostItems.m_nId = v5;
        stu.CostItems.m_nCount = v23.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v12);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.GetItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v12);
        stu.MailId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Score = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v15);
        std::string::string(v14, "./ServerConfig/Tables/limitChallenge.txt", &v15);
        std::allocator<char>::allocator(&v17);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v16, v3->pString, &v17);
        CfgData::paraseParam2List(
          (CfgData *const)&v13,
          (const std::string *const)this,
          (int32_t)v16,
          (const std::string *const)(unsigned int)nIndex);
        std::list<Param2>::operator=(&stu.DropRateList, &v13);
        std::list<Param2>::~list(&v13);
        std::string::~string(v16);
        std::allocator<char>::~allocator(&v17);
        std::string::~string(v14);
        std::allocator<char>::~allocator(&v15);
        ++nIndex;
        stu.DoubleConst = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v4 = std::map<int,UltimateChallengeCfg>::operator[](&this->m_UltimateChallengeCfgMap, &stu.CurMapId);
        UltimateChallengeCfg::operator=(v4, &stu);
        UltimateChallengeCfg::~UltimateChallengeCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitCachetCfg(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgCachet *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  CfgCachet stu; // [rsp+A0h] [rbp-80h] BYREF
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+E0h] [rbp-40h] BYREF
  char v7; // [rsp+EFh] [rbp-31h] BYREF
  int32_t v8[3]; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Cachet.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CACHET_CFG_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<AddAttribute>::list(&stu.nAttrList);
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nNeedCacht = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        std::string::string(v6, "./ServerConfig/Tables/SpecialEquip.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.nAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v8);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(v6);
        std::allocator<char>::~allocator(&v7);
        stu.nDeduct = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nGongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,CfgCachet>::operator[](&this->m_CfgCachetMap, &stu.nLevel);
        CfgCachet::operator=(v2, &stu);
        CfgCachet::~CfgCachet(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
int32_t __cdecl CfgData::GetCachetLevel(CfgData *const this, int64_t Exp)
{
  std::pair<const int,CfgCachet> *v2; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgCachet> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgCachet> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Level; // [rsp+2Ch] [rbp-4h]

  Level = 1;
  for ( it._M_node = std::map<int,CfgCachet>::begin(&this->m_CfgCachetMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgCachet>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgCachet>::end(&this->m_CfgCachetMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgCachet>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgCachet>>::operator->(&it)->second.nNeedCacht <= Exp )
    {
      v2 = std::_Rb_tree_iterator<std::pair<int const,CfgCachet>>::operator->(&it);
      if ( v2->second.nLevel > Level )
        Level = std::_Rb_tree_iterator<std::pair<int const,CfgCachet>>::operator->(&it)->second.nLevel;
    }
  }
  return Level;
}


#####################################
void __cdecl CfgData::InitBossKilledReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  BossKilledReward *v2; // rax
  BossKilledReward *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-120h] BYREF
  BossKilledReward stu; // [rsp+A0h] [rbp-90h] BYREF
  int32_t BossId; // [rsp+DCh] [rbp-54h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v9; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GoldReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BOSS_KILLED_REWARD_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<int>::list(&stu.BossList);
        std::vector<MemChrBag>::vector(&stu.Rewars);
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        BossId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v9);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewars, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        v2 = std::map<signed char,BossKilledReward>::operator[](&this->m_BossKilledRewardMap, &stu.nType);
        std::list<int>::push_back(&v2->BossList, &BossId);
        v3 = std::map<signed char,BossKilledReward>::operator[](&this->m_BossKilledRewardMap, &stu.nType);
        std::vector<MemChrBag>::operator=(&v3->Rewars, &stu.Rewars);
        BossKilledReward::~BossKilledReward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitSystemOpenReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  SystemOpenGift *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  SystemOpenGift stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/System.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SYSTEM_OPEN_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 36);
        std::vector<MemChrBag>::vector(&stu.Gifts);
        stu.Id = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        nIndex += 2;
        stu.TypeId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Gifts, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        nIndex += 2;
        stu.Star = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        v2 = std::map<int,SystemOpenGift>::operator[](&this->m_SystemOpenGiftMap, &stu.Id);
        SystemOpenGift::operator=(v2, &stu);
        SystemOpenGift::~SystemOpenGift(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitSpecialMap(CfgData *const this)
{
  SpecialMap *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  SpecialMap stu; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/SpecialMap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SPECIAL_MAP_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.CurMapId = 0;
        stu.MaxPlayer = 0;
        stu.CurMapId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.NextMapId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MaxPlayer = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,SpecialMap>::operator[](&this->m_SpecialMapMap, &stu.CurMapId);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
bool __cdecl CfgData::IsSpecialMap(CfgData *const this, int32_t MapId)
{
  int32_t MapIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,SpecialMap> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SpecialMap> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  MapIda = MapId;
  it._M_node = std::map<int,SpecialMap>::find(&this->m_SpecialMapMap, &MapIda)._M_node;
  __x._M_node = std::map<int,SpecialMap>::end(&thisa->m_SpecialMapMap)._M_node;
  return std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator!=(&it, &__x);
}


#####################################
void __cdecl CfgData::InitTestServerReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  TestServerReward *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-110h] BYREF
  TestServerReward stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/TestActivity.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TEST_SERVER_REWARD_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 44);
        std::vector<MemChrBag>::vector(&stu.vItems);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nParm = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nGongId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,TestServerReward>::operator[](&this->m_TestServerRewardMap, &stu.nId);
        TestServerReward::operator=(v2, &stu);
        TestServerReward::~TestServerReward(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitEquipBlessTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  CfgEquipBless stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/LuckyValue.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgEquipBless::CfgEquipBless(&stu);
        stu.nBless = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nAddRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.nRemineRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBroad = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipBlessTable::Add(&this->m_cfgEquipBlessTable, &stu);
        CfgEquipBless::~CfgEquipBless(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitGuWuCfgMap(CfgData *const this)
{
  GuWuCfg *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  GuWuCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GuWu.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.Money = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Gold = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MoneyRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GoldRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MoneyBuffId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.GoldBuffId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,GuWuCfg>::operator[](&this->m_GuWuCfgMap, &stu.nLevel);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitFunctionOpenMailMap(CfgData *const this)
{
  FunctionOpenMail *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-E0h] BYREF
  int32_t nId; // [rsp+ACh] [rbp-44h] BYREF
  FunctionOpenMail stu; // [rsp+B0h] [rbp-40h]
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MailGuide.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nMailID = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDayLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,FunctionOpenMail>::operator[](&this->m_FunctionOpenMailMap, &nId);
        *v1 = stu;
        if ( nId <= 0 || nId > 199 )
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "read FILE_MAIL_GUIDE_TABLE nId =%d\n", nId);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitXianYaoTaskTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  XiangYaoTaskCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XiangYaoTask.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXiangY);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.TaskId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.Star = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MinLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.MaxLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.Rate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::list<XiangYaoTaskCfg>::push_back(&this->m_XiangYaoTaskCfgList, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
int32_t __cdecl CfgData::RandXiangYaoTaskId(CfgData *const this, int32_t Level, bool bBest)
{
  bool v3; // al
  XiangYaoTaskCfg *v4; // rax
  int *v5; // rbx
  XiangYaoTaskCfg *v6; // rax
  int32_t first; // ebx
  Answer::Random *v8; // rax
  std::pair<const int,int> *v9; // rax
  std::pair<const int,int> *v10; // rax
  Int32Int32Map TaskIdRate; // [rsp+10h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > itMap; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> it; // [rsp+50h] [rbp-60h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> __x; // [rsp+60h] [rbp-50h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> v17; // [rsp+70h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v18; // [rsp+80h] [rbp-30h] BYREF
  int32_t MaxRate; // [rsp+94h] [rbp-1Ch]
  int32_t SpareId; // [rsp+98h] [rbp-18h]
  int32_t nRand; // [rsp+9Ch] [rbp-14h]

  std::map<int,int>::map(&TaskIdRate);
  MaxRate = 0;
  SpareId = 0;
  it._M_node = std::list<XiangYaoTaskCfg>::begin(&this->m_XiangYaoTaskCfgList)._M_node;
  __x._M_node = std::list<XiangYaoTaskCfg>::end(&this->m_XiangYaoTaskCfgList)._M_node;
  if ( std::_List_iterator<XiangYaoTaskCfg>::operator!=(&it, &__x) )
    SpareId = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->TaskId;
  while ( 1 )
  {
    v17._M_node = std::list<XiangYaoTaskCfg>::end(&this->m_XiangYaoTaskCfgList)._M_node;
    if ( !std::_List_iterator<XiangYaoTaskCfg>::operator!=(&it, &v17) )
      break;
    v3 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->MinLevel <= Level
      && std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->MaxLevel >= Level;
    if ( v3 && (!bBest || std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->Star == 4) )
    {
      v4 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it);
      v5 = std::map<int,int>::operator[](&TaskIdRate, &v4->TaskId);
      *v5 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->Rate;
      v6 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it);
      MaxRate += v6->Rate;
    }
    std::_List_iterator<XiangYaoTaskCfg>::operator++(&it, 0);
  }
  if ( MaxRate > 0 )
  {
    v8 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v8, 1, MaxRate);
    for ( itMap._M_node = std::map<int,int>::begin(&TaskIdRate)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itMap, 0) )
    {
      v18._M_node = std::map<int,int>::end(&TaskIdRate)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itMap, &v18) )
        break;
      v9 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
      if ( v9->second >= nRand )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap)->first;
        goto LABEL_21;
      }
      v10 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
      nRand -= v10->second;
    }
    first = SpareId;
  }
  else
  {
    first = SpareId;
  }
LABEL_21:
  std::map<int,int>::~map(&TaskIdRate);
  return first;
}


#####################################
int32_t __cdecl CfgData::getXiangYaoStart(CfgData *const this, int32_t TaskId)
{
  std::_List_iterator<XiangYaoTaskCfg> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<XiangYaoTaskCfg>::begin(&this->m_XiangYaoTaskCfgList)._M_node;
        ;
        std::_List_iterator<XiangYaoTaskCfg>::operator++(&it, 0) )
  {
    __x._M_node = std::list<XiangYaoTaskCfg>::end(&this->m_XiangYaoTaskCfgList)._M_node;
    if ( !std::_List_iterator<XiangYaoTaskCfg>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->TaskId == TaskId )
      return std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->Star;
  }
  return 0;
}


#####################################
void __cdecl CfgData::InitShenWeiTaskTable(CfgData *const this)
{
  ShenWeiTaskCfg *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  ShenWeiTaskCfg stu; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShenWeiTask.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXiangY);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        stu.nTaskId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDoubleCost = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,ShenWeiTaskCfg>::operator[](&this->m_ShenWeiTaskCfgMap, &stu.nIndex);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMingGeTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  CDBCFile readFile; // [rsp+10h] [rbp-1B0h] BYREF
  CMingGeCfg stu; // [rsp+A0h] [rbp-120h] BYREF
  Param2 stu_1; // [rsp+E0h] [rbp-E0h] BYREF
  MingGeDrawCost stu_0; // [rsp+F0h] [rbp-D0h]
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-C0h] BYREF
  _BYTE v9[15]; // [rsp+110h] [rbp-B0h] BYREF
  char v10; // [rsp+11Fh] [rbp-A1h] BYREF
  int32_t v11[3]; // [rsp+120h] [rbp-A0h] BYREF
  char v12; // [rsp+12Fh] [rbp-91h] BYREF
  CMingGeCfg p_stu; // [rsp+130h] [rbp-90h] BYREF
  int32_t iBaseTableCount; // [rsp+174h] [rbp-4Ch]
  int32_t iBaseColumnCount; // [rsp+178h] [rbp-48h]
  int32_t i; // [rsp+17Ch] [rbp-44h]
  int32_t nIndex; // [rsp+180h] [rbp-40h]
  int32_t iBaseTableCount_0; // [rsp+188h] [rbp-38h]
  int32_t iBaseColumnCount_0; // [rsp+18Ch] [rbp-34h]
  int32_t i_0; // [rsp+190h] [rbp-30h]
  int32_t nIndex_0; // [rsp+194h] [rbp-2Ch]
  int32_t iBaseTableCount_1; // [rsp+19Ch] [rbp-24h]
  int32_t iBaseColumnCount_1; // [rsp+1A0h] [rbp-20h]
  int32_t i_1; // [rsp+1A4h] [rbp-1Ch]
  int32_t nIndex_1; // [rsp+1A8h] [rbp-18h]
  int32_t nType; // [rsp+1ACh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MingGe.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CMingGeCfg::CMingGeCfg(&stu);
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v10);
        std::string::string(v9, "./ServerConfig/Tables/MingGe.txt", &v10);
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v11, v2->pString, &v12);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v11,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v11);
        std::allocator<char>::~allocator(&v12);
        std::string::~string(v9);
        std::allocator<char>::~allocator(&v10);
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nCanPickup = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nQuality = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDecExp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDecMoney = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nUpExp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nNextId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nCostChip = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        CMingGeCfg::CMingGeCfg(&p_stu, &stu);
        CMingGeTable::AddMingGeCfg(&this->m_CMingGeTable, &p_stu);
        CMingGeCfg::~CMingGeCfg(&p_stu);
        CMingGeCfg::~CMingGeCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MingGeDrawCost.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe_0);
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          stu_0.nType = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          stu_0.nConstMoney = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu_0.nConstGold = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          stu_0.nRate = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CMingGeTable::AddMingGeDrawCost(&this->m_CMingGeTable, stu_0);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    CDBCFile::~CDBCFile(&readFile);
    if ( v3 )
    {
      CDBCFile::CDBCFile(&readFile, 0);
      if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/MingGeDraw.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe_1);
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&readFile);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&readFile);
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            nType = CDBCFile::Search_Posistion(&readFile, i_1, 0)->iValue;
            ++nIndex_1;
            Param2::Param2(&stu_1, 0, 0);
            stu_1.nParam1 = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1++)->iValue;
            stu_1.nParam2 = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1++)->iValue;
            CMingGeTable::AddMingGeDrawRate(&this->m_CMingGeTable, nType, stu_1);
          }
        }
      }
      CDBCFile::~CDBCFile(&readFile);
    }
  }
}


#####################################
int32_t __cdecl CfgData::GetMonsterReviveTime(CfgData *const this, int32_t Time, int32_t BossId)
{
  int32_t result; // eax
  CfgData *v4; // rax

  if ( BossId != 1 )
    return Time;
  if ( Time <= 0 )
    return Time;
  v4 = Answer::Singleton<CfgData>::instance();
  switch ( CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL) )
  {
    case 0:
      result = 10 * (Time / 100);
      break;
    case 1:
    case 2:
      result = 30 * (Time / 100);
      break;
    case 3:
      result = 50 * (Time / 100);
      break;
    case 4:
      result = 60 * (Time / 100);
      break;
    case 5:
      result = 70 * (Time / 100);
      break;
    case 6:
      result = 80 * (Time / 100);
      break;
    default:
      result = Time;
      break;
  }
  return result;
}


#####################################
void __cdecl CfgData::InitMobilePhoneGiftTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgMobilePhoneGift *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgMobilePhoneGift stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/ShouJi.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MOBILE_PHONE_GIFT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        memset(&stu, 0, 36);
        std::string::string(&stu.strPlatfrom);
        std::vector<MemChrBag>::vector(&stu.vItem);
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v8);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex);
        std::string::operator=(&stu, v2->pString);
        stu.nIcon = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<std::string,CfgMobilePhoneGift>::operator[](&this->m_CfgMobilePhoneGift, &stu.strPlatfrom);
        CfgMobilePhoneGift::operator=(v3, &stu);
        CfgMobilePhoneGift::~CfgMobilePhoneGift(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitMiniClientTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgMiniClient *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgMiniClient stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WeiDuan.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MINI_CLIENT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.strPlatfrom);
        std::vector<MemChrBag>::vector(&stu.vReward);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&stu, v1->pString);
        stu.nIconDownload = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nIconLogin = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v8);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        v3 = std::map<std::string,CfgMiniClient>::operator[](&this->m_CfgMiniClient, &stu.strPlatfrom);
        CfgMiniClient::operator=(v3, &stu);
        CfgMiniClient::~CfgMiniClient(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitWuHunShopTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::list<CfgWuHunShop> *v2; // rax
  CfgWuHunShop *v3; // rax
  MemChrBag v4; // [rsp+0h] [rbp-130h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-108h]
  CDBCFile TabFile; // [rsp+30h] [rbp-100h] BYREF
  CfgWuHunShop stu; // [rsp+C0h] [rbp-70h] BYREF
  int32_t ShopId; // [rsp+FCh] [rbp-34h] BYREF
  std::string strItem; // [rsp+100h] [rbp-30h] BYREF
  char v10; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MysterShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.Index = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        ShopId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v10);
        CItemHelper::parseItemString(&v4, &strItem);
        stu.Item = v4;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v10);
        stu.Rate = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.Const = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<CfgWuHunShop>>::operator[](&thisa->m_CfgWuHunShopMap, &ShopId);
        std::list<CfgWuHunShop>::push_back(v2, &stu);
        v3 = std::map<int,CfgWuHunShop>::operator[](&thisa->m_CfgWuHunShopItemMap, &stu.Index);
        *v3 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitWuHunItemTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  WuHunItem *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-120h] BYREF
  WuHunItem stu; // [rsp+A0h] [rbp-90h] BYREF
  std::list<AddAttribute> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+F0h] [rbp-40h] BYREF
  char v7; // [rsp+FFh] [rbp-31h] BYREF
  int32_t v8[3]; // [rsp+100h] [rbp-30h] BYREF
  char v9; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WuHun.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_ITEM_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<AddAttribute>::list(&stu.lAttrList);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nQuality = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nNeedQuality = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        std::string::string(v6, "./ServerConfig/Tables/WuHun.txt", &v7);
        std::allocator<char>::allocator(&v9);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v8);
        std::allocator<char>::~allocator(&v9);
        std::string::~string(v6);
        std::allocator<char>::~allocator(&v7);
        stu.nTalentId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nTalentLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 8;
        stu.overlay = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        nIndex += 3;
        stu.nDressLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        v2 = std::map<int,WuHunItem>::operator[](&this->m_WuHunItemMap, &stu.nId);
        WuHunItem::operator=(v2, &stu);
        WuHunItem::~WuHunItem(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitWuHunCreateTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  CreateWuHun *v5; // rax
  __int64 v6; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-170h] BYREF
  CreateWuHun stu; // [rsp+A0h] [rbp-E0h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-90h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-80h] BYREF
  char v11; // [rsp+10Fh] [rbp-71h] BYREF
  std::list<RateItem> v12; // [rsp+110h] [rbp-70h] BYREF
  _BYTE v13[15]; // [rsp+120h] [rbp-60h] BYREF
  char v14; // [rsp+12Fh] [rbp-51h] BYREF
  std::string strItem; // [rsp+130h] [rbp-50h] BYREF
  char v16; // [rsp+13Fh] [rbp-41h] BYREF
  std::list<RateItem> v17; // [rsp+140h] [rbp-40h] BYREF
  _BYTE v18[14]; // [rsp+150h] [rbp-30h] BYREF
  char v19; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]
  ItemData v25; // 0:kr00_12.12

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WuHunMake.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CREATE_WU_HUN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<ItemData>::list(&stu.ConstItem);
        std::list<RateItem>::list(&stu.GetItemRate);
        std::list<RateItem>::list(&stu.GetItemRate2);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        nIndex += 2;
        std::allocator<char>::allocator(&v11);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(bCombi, v1->pString, &v11);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.ConstItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v11);
        ++nIndex;
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v13, v2->pString, &v14);
        CItemHelper::parseRateItemDataListString((const std::string *const)&v12);
        std::list<RateItem>::operator=(&stu.GetItemRate, &v12);
        std::list<RateItem>::~list(&v12);
        std::string::~string(v13);
        std::allocator<char>::~allocator(&v14);
        ++nIndex;
        nIndex += 3;
        std::allocator<char>::allocator(&v16);
        v3 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItem, v3->pString, &v16);
        v25 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v6) = v25.m_nId;
        BYTE4(v6) = v25.m_nClass;
        *(_QWORD *)&stu.SpecialCost.m_nId = v6;
        stu.SpecialCost.m_nCount = v25.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v16);
        ++nIndex;
        std::allocator<char>::allocator(&v19);
        v4 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v18, v4->pString, &v19);
        CItemHelper::parseRateItemDataListString((const std::string *const)&v17);
        std::list<RateItem>::operator=(&stu.GetItemRate2, &v17);
        std::list<RateItem>::~list(&v17);
        std::string::~string(v18);
        std::allocator<char>::~allocator(&v19);
        ++nIndex;
        v5 = std::map<int,CreateWuHun>::operator[](&this->m_CreateWuHunMap, &stu.nId);
        CreateWuHun::operator=(v5, &stu);
        CreateWuHun::~CreateWuHun(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitBossDistribution(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-180h] BYREF
  std::string BossMapListString_0; // [rsp+A0h] [rbp-F0h] BYREF
  MapBossInfo stu_0; // [rsp+B0h] [rbp-E0h] BYREF
  std::string BossMapListString; // [rsp+D0h] [rbp-C0h] BYREF
  BossLevelInfo stu; // [rsp+E0h] [rbp-B0h] BYREF
  char v9; // [rsp+FFh] [rbp-91h] BYREF
  std::list<int> __x; // [rsp+100h] [rbp-90h] BYREF
  BossLevelInfo p_stu; // [rsp+110h] [rbp-80h] BYREF
  char v12; // [rsp+12Fh] [rbp-61h] BYREF
  std::list<int> v13; // [rsp+130h] [rbp-60h] BYREF
  MapBossInfo v14; // [rsp+140h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+15Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+160h] [rbp-30h]
  int32_t i; // [rsp+164h] [rbp-2Ch]
  int32_t nIndex; // [rsp+168h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+170h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+174h] [rbp-1Ch]
  int32_t i_0; // [rsp+178h] [rbp-18h]
  int32_t nIndex_0; // [rsp+17Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MonsterRefreshInMaps.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_LEVEL_IFNO_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<int>::list(&stu.BossMapList);
        stu.BossLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v9);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&BossMapListString, v2->pString, &v9);
        std::allocator<char>::~allocator(&v9);
        ++nIndex;
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, (int32_t)&BossMapListString);
        std::list<int>::operator=(&stu.BossMapList, &__x);
        std::list<int>::~list(&__x);
        BossLevelInfo::BossLevelInfo(&p_stu, &stu);
        BossDistribution::AddBossLevelInfo(&this->m_BossDistribution, &p_stu);
        BossLevelInfo::~BossLevelInfo(&p_stu);
        std::string::~string(&BossMapListString);
        BossLevelInfo::~BossLevelInfo(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MapClassInfo.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu_0, 0, sizeof(stu_0));
          std::list<int>::list(&stu_0.BossMapList);
          stu_0.nId = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0++)->iValue;
          std::allocator<char>::allocator(&v12);
          v3 = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0);
          std::string::string(&BossMapListString_0, v3->pString, &v12);
          std::allocator<char>::~allocator(&v12);
          ++nIndex_0;
          CfgData::paraseInt32List((CfgData *const)&v13, (const std::string *const)this, (int32_t)&BossMapListString_0);
          std::list<int>::operator=(&stu_0.BossMapList, &v13);
          std::list<int>::~list(&v13);
          MapBossInfo::MapBossInfo(&v14, &stu_0);
          BossDistribution::AddMapBossInfo(&this->m_BossDistribution, &v14);
          MapBossInfo::~MapBossInfo(&v14);
          std::string::~string(&BossMapListString_0);
          MapBossInfo::~MapBossInfo(&stu_0);
        }
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
  }
}


#####################################
void __cdecl CfgData::InitSpecialBossMapCfgMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  SpecialBossMapCfg *v2; // rax
  __int64 v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  SpecialBossMapCfg stu; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItem; // [rsp+C0h] [rbp-30h] BYREF
  char v7; // [rsp+CEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]
  ItemData v13; // 0:kr00_12.12

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MapConsume.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.MapId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v7);
        v13 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v3) = v13.m_nId;
        BYTE4(v3) = v13.m_nClass;
        *(_QWORD *)&stu.ConstItem.m_nId = v3;
        stu.ConstItem.m_nCount = v13.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v7);
        stu.StartCD = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.ContinuedTime = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,SpecialBossMapCfg>::operator[](&this->m_SpecialBossMapCfgMap, &stu.MapId);
        *v2 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitDuiHuanLimitTable(CfgData *const this)
{
  DuiHuanLimit *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-E0h] BYREF
  int32_t MaxLevel; // [rsp+ACh] [rbp-44h] BYREF
  DuiHuanLimit stu; // [rsp+B0h] [rbp-40h]
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/ExchangeShengYaoBi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,DuiHuanLimit>::clear(&this->m_DuiHuanLimit);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        *(_QWORD *)&stu.ShengYaoBi = 0;
        *(_QWORD *)&stu.ConstCurrency = 0;
        MaxLevel = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        stu.ShengYaoBi = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.ConstGold = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.ConstCurrency = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.Limit = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,DuiHuanLimit>::operator[](&this->m_DuiHuanLimit, &MaxLevel);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitSuperTeHuiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  SuperTeHuiCfg *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  SuperTeHuiCfg stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/SuperDiscount.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SUPER_DISCOUNT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,SuperTeHuiCfg>::clear(&this->m_SuperTeHuiCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.Items);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nNeedVip = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nPrice = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nGongGaoId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,SuperTeHuiCfg>::operator[](&this->m_SuperTeHuiCfgMap, &stu.nIndex);
        SuperTeHuiCfg::operator=(v2, &stu);
        SuperTeHuiCfg::~SuperTeHuiCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitJewelPavilionTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,JewelPavilionCfg> >,bool> v2; // rax
  MemChrBag v3; // [rsp+0h] [rbp-180h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-158h]
  CDBCFile TabFile; // [rsp+30h] [rbp-150h] BYREF
  JewelPavilionCfg stu; // [rsp+C0h] [rbp-C0h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-90h] BYREF
  char v8; // [rsp+FFh] [rbp-81h] BYREF
  std::_Rb_tree_node_base::_Base_ptr M_node; // [rsp+100h] [rbp-80h]
  bool second; // [rsp+108h] [rbp-78h]
  _BYTE v11[64]; // [rsp+110h] [rbp-70h] BYREF
  std::pair<int,int> __a; // [rsp+150h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TreasureShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TREASURE_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,JewelPavilionCfg>::clear(&thisa->m_JewelPavilionCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nDay = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItem, v1->pString, &v8);
        CItemHelper::parseItemString(&v3, &strItem);
        stu.Item = v3;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v8);
        stu.nPrice = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(stu.nDay, stu.nIndex);
        std::pair<std::pair const<int,int>,JewelPavilionCfg>::pair(
          (std::pair<const std::pair<int,int>,JewelPavilionCfg> *const)v11,
          &__a,
          &stu);
        v2 = std::map<std::pair<int,int>,JewelPavilionCfg>::insert(
               &thisa->m_JewelPavilionCfgMap,
               (const std::pair<const std::pair<int,int>,JewelPavilionCfg> *const)v11);
        *(_QWORD *)&v3.itemId = v2.first._M_node;
        v3.itemCount = *(_DWORD *)&v2.second;
        M_node = v2.first._M_node;
        second = v2.second;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitWingEquipPolish(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  int v4; // ebx
  const CDBCFile::FIELD *v5; // rax
  std::list<AddAttribute> *v6; // rax
  int v7; // ebx
  const CDBCFile::FIELD *v8; // rax
  const CDBCFile::FIELD *v9; // rax
  std::list<AddAttribute> *v10; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-2F0h] BYREF
  WingEquipPolish stu; // [rsp+B0h] [rbp-260h] BYREF
  AddAttrList AddAttrs_0; // [rsp+F0h] [rbp-220h] BYREF
  int32_t nId_0; // [rsp+10Ch] [rbp-204h] BYREF
  AddAttrList AddAttrs; // [rsp+110h] [rbp-200h] BYREF
  int32_t nId; // [rsp+12Ch] [rbp-1E4h] BYREF
  std::list<AddAttribute> __x; // [rsp+130h] [rbp-1E0h] BYREF
  _BYTE v18[15]; // [rsp+140h] [rbp-1D0h] BYREF
  char v19; // [rsp+14Fh] [rbp-1C1h] BYREF
  int32_t v20[3]; // [rsp+150h] [rbp-1C0h] BYREF
  char v21; // [rsp+15Fh] [rbp-1B1h] BYREF
  std::list<ItemData> strItems; // [rsp+160h] [rbp-1B0h] BYREF
  bool bCombi[15]; // [rsp+170h] [rbp-1A0h] BYREF
  char v24; // [rsp+17Fh] [rbp-191h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WingEquipPolish> >,bool> v25; // [rsp+180h] [rbp-190h]
  _BYTE v26[64]; // [rsp+190h] [rbp-180h] BYREF
  std::pair<int,int> __a; // [rsp+1D0h] [rbp-140h] BYREF
  _BYTE v28[15]; // [rsp+1E0h] [rbp-130h] BYREF
  char v29; // [rsp+1EFh] [rbp-121h] BYREF
  int32_t v30[3]; // [rsp+1F0h] [rbp-120h] BYREF
  char v31; // [rsp+1FFh] [rbp-111h] BYREF
  std::list<ItemData> v32; // [rsp+200h] [rbp-110h] BYREF
  bool v33[15]; // [rsp+210h] [rbp-100h] BYREF
  char v34; // [rsp+21Fh] [rbp-F1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WinRefiningCfg> >,bool> v35; // [rsp+220h] [rbp-F0h]
  _BYTE v36[64]; // [rsp+230h] [rbp-E0h] BYREF
  std::pair<int,int> v37; // [rsp+270h] [rbp-A0h] BYREF
  _BYTE v38[15]; // [rsp+280h] [rbp-90h] BYREF
  char v39; // [rsp+28Fh] [rbp-81h] BYREF
  int32_t v40[4]; // [rsp+290h] [rbp-80h] BYREF
  char v41; // [rsp+2A2h] [rbp-6Eh] BYREF
  int32_t iBaseTableCount; // [rsp+2A4h] [rbp-6Ch]
  int32_t iBaseColumnCount; // [rsp+2A8h] [rbp-68h]
  int32_t i; // [rsp+2ACh] [rbp-64h]
  int32_t nIndex; // [rsp+2B0h] [rbp-60h]
  int32_t nType; // [rsp+2B4h] [rbp-5Ch]
  int32_t nLevel; // [rsp+2B8h] [rbp-58h]
  int32_t iBaseTableCount_0; // [rsp+2C0h] [rbp-50h]
  int32_t iBaseColumnCount_0; // [rsp+2C4h] [rbp-4Ch]
  int32_t i_0; // [rsp+2C8h] [rbp-48h]
  int32_t nIndex_0; // [rsp+2CCh] [rbp-44h]
  int32_t iBaseTableCount_1; // [rsp+2D4h] [rbp-3Ch]
  int32_t iBaseColumnCount_1; // [rsp+2D8h] [rbp-38h]
  int32_t i_1; // [rsp+2DCh] [rbp-34h]
  int32_t nIndex_1; // [rsp+2E0h] [rbp-30h]
  int32_t nType_0; // [rsp+2E4h] [rbp-2Ch]
  int32_t nLevel_0; // [rsp+2E8h] [rbp-28h]
  int32_t iBaseTableCount_2; // [rsp+2F0h] [rbp-20h]
  int32_t iBaseColumnCount_2; // [rsp+2F4h] [rbp-1Ch]
  int32_t i_2; // [rsp+2F8h] [rbp-18h]
  int32_t nIndex_2; // [rsp+2FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WingEquipPolish.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,WingEquipPolish>::clear(&this->m_WingEquipPolishCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 52);
        std::list<AddAttribute>::list(&stu.lAttrList);
        std::list<ItemData>::list(&stu.lCostList);
        nType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v19);
        std::string::string(v18, "./ServerConfig/Tables/StarSpaceLevel.txt", &v19);
        std::allocator<char>::allocator(&v21);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v20, v2->pString, &v21);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v20,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v20);
        std::allocator<char>::~allocator(&v21);
        std::string::~string(v18);
        std::allocator<char>::~allocator(&v19);
        ++nIndex;
        std::allocator<char>::allocator(&v24);
        v3 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(bCombi, v3->pString, &v24);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lCostList, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v24);
        stu.nConstMoney = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.SuitId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.GongGaoId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(nType, nLevel);
        std::pair<std::pair const<int,int>,WingEquipPolish>::pair(
          (std::pair<const std::pair<int,int>,WingEquipPolish> *const)v26,
          &__a,
          &stu);
        v25 = std::map<std::pair<int,int>,WingEquipPolish>::insert(
                &this->m_WingEquipPolishCfgMap,
                (const std::pair<const std::pair<int,int>,WingEquipPolish> *const)v26);
        std::pair<std::pair const<int,int>,WingEquipPolish>::~pair((std::pair<const std::pair<int,int>,WingEquipPolish> *const)v26);
        WingEquipPolish::~WingEquipPolish(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WingEquipPolishSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,std::list<AddAttribute>>::clear(&this->m_WingEquipPolishSuitMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          nId = CDBCFile::Search_Posistion(&TabFile, i_0, 0)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v29);
          std::string::string(v28, "./ServerConfig/Tables/StarSpaceSuit.txt", &v29);
          std::allocator<char>::allocator(&v31);
          v5 = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0);
          std::string::string(v30, v5->pString, &v31);
          CfgData::parseAddAttribues(
            (CfgData *const)&AddAttrs,
            (const std::string *const)this,
            (int32_t)v30,
            (const std::string *const)(unsigned int)nIndex_0);
          std::string::~string(v30);
          std::allocator<char>::~allocator(&v31);
          std::string::~string(v28);
          std::allocator<char>::~allocator(&v29);
          ++nIndex_0;
          v6 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_WingEquipPolishSuitMap, &nId);
          std::list<AddAttribute>::operator=(v6, &AddAttrs);
          std::list<AddAttribute>::~list(&AddAttrs);
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
    if ( v4 )
    {
      CDBCFile::CDBCFile(&TabFile, 0);
      if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WingEquipRefine.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_WING_EQUIP_REFINING failed,please check!!!\n");
        v7 = 0;
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&TabFile);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&TabFile);
        if ( iBaseColumnCount_1 > 0 )
        {
          std::map<std::pair<int,int>,WinRefiningCfg>::clear(&this->m_WinRefiningCfgMap);
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            memset(&stu, 0, 44);
            std::list<ItemData>::list((std::list<ItemData> *const)&stu.lAttrList._M_impl._M_node._M_prev);
            nType_0 = CDBCFile::Search_Posistion(&TabFile, i_1, nIndex_1++)->iValue;
            nLevel_0 = CDBCFile::Search_Posistion(&TabFile, i_1, nIndex_1++)->iValue;
            std::allocator<char>::allocator(&v34);
            v8 = CDBCFile::Search_Posistion(&TabFile, i_1, nIndex_1);
            std::string::string(v33, v8->pString, &v34);
            CItemHelper::parseItemDataListString((const std::string *const)&v32, (bool)v33);
            std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.lAttrList._M_impl._M_node._M_prev, &v32);
            std::list<ItemData>::~list(&v32);
            std::string::~string(v33);
            std::allocator<char>::~allocator(&v34);
            LODWORD(stu.lAttrList._M_impl._M_node._M_next) = CDBCFile::Search_Posistion(&TabFile, i_1, ++nIndex_1)->iValue;
            LODWORD(stu.lCostList._M_impl._M_node._M_prev) = CDBCFile::Search_Posistion(&TabFile, i_1, ++nIndex_1)->iValue;
            stu.nConstMoney = CDBCFile::Search_Posistion(&TabFile, i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            v37 = std::make_pair<int,int>(nType_0, nLevel_0);
            std::pair<std::pair const<int,int>,WinRefiningCfg>::pair(
              (std::pair<const std::pair<int,int>,WinRefiningCfg> *const)v36,
              &v37,
              (const WinRefiningCfg *const)&stu);
            v35 = std::map<std::pair<int,int>,WinRefiningCfg>::insert(
                    &this->m_WinRefiningCfgMap,
                    (const std::pair<const std::pair<int,int>,WinRefiningCfg> *const)v36);
            std::pair<std::pair const<int,int>,WinRefiningCfg>::~pair((std::pair<const std::pair<int,int>,WinRefiningCfg> *const)v36);
            WinRefiningCfg::~WinRefiningCfg((WinRefiningCfg *const)&stu);
          }
          v7 = 1;
        }
        else
        {
          v7 = 0;
        }
      }
      CDBCFile::~CDBCFile(&TabFile);
      if ( v7 )
      {
        CDBCFile::CDBCFile(&TabFile, 0);
        if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WingEquipRefineSuit.txt") )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "open FILE_WING_EQUIP_REFINING_SUIT failed,please check!!!\n");
        }
        else
        {
          iBaseTableCount_2 = CDBCFile::GetRecordsNum(&TabFile);
          iBaseColumnCount_2 = CDBCFile::GetFieldsNum(&TabFile);
          if ( iBaseColumnCount_2 > 0 )
          {
            std::map<int,std::list<AddAttribute>>::clear(&this->m_WingEquipRefiningSuitMap);
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              nIndex_2 = 0;
              nId_0 = CDBCFile::Search_Posistion(&TabFile, i_2, 0)->iValue;
              ++nIndex_2;
              std::allocator<char>::allocator(&v39);
              std::string::string(v38, "./ServerConfig/Tables/StarSpaceSuit.txt", &v39);
              std::allocator<char>::allocator(&v41);
              v9 = CDBCFile::Search_Posistion(&TabFile, i_2, nIndex_2);
              std::string::string(v40, v9->pString, &v41);
              CfgData::parseAddAttribues(
                (CfgData *const)&AddAttrs_0,
                (const std::string *const)this,
                (int32_t)v40,
                (const std::string *const)(unsigned int)nIndex_2);
              std::string::~string(v40);
              std::allocator<char>::~allocator(&v41);
              std::string::~string(v38);
              std::allocator<char>::~allocator(&v39);
              ++nIndex_2;
              v10 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_WingEquipRefiningSuitMap, &nId_0);
              std::list<AddAttribute>::operator=(v10, &AddAttrs_0);
              std::list<AddAttribute>::~list(&AddAttrs_0);
            }
          }
        }
        CDBCFile::~CDBCFile(&TabFile);
      }
    }
  }
}


#####################################
void __cdecl CfgData::InitShouHuRefining(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::list<AddAttribute> *v5; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-1E0h] BYREF
  ShouHuRefinishingCfg stu; // [rsp+B0h] [rbp-150h] BYREF
  AddAttrList AddAttrs; // [rsp+E0h] [rbp-120h] BYREF
  int32_t nId; // [rsp+FCh] [rbp-104h] BYREF
  std::list<ItemData> strItems; // [rsp+100h] [rbp-100h] BYREF
  bool bCombi[15]; // [rsp+110h] [rbp-F0h] BYREF
  char v12; // [rsp+11Fh] [rbp-E1h] BYREF
  std::list<AddAttribute> __x; // [rsp+120h] [rbp-E0h] BYREF
  _BYTE v14[15]; // [rsp+130h] [rbp-D0h] BYREF
  char v15; // [rsp+13Fh] [rbp-C1h] BYREF
  int32_t v16[3]; // [rsp+140h] [rbp-C0h] BYREF
  char v17; // [rsp+14Fh] [rbp-B1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,ShouHuRefinishingCfg> >,bool> v18; // [rsp+150h] [rbp-B0h]
  _BYTE v19[48]; // [rsp+160h] [rbp-A0h] BYREF
  std::pair<int,int> __a; // [rsp+190h] [rbp-70h] BYREF
  _BYTE v21[15]; // [rsp+1A0h] [rbp-60h] BYREF
  char v22; // [rsp+1AFh] [rbp-51h] BYREF
  int32_t v23[4]; // [rsp+1B0h] [rbp-50h] BYREF
  char v24; // [rsp+1C2h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+1C4h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+1C8h] [rbp-38h]
  int32_t i; // [rsp+1CCh] [rbp-34h]
  int32_t nIndex; // [rsp+1D0h] [rbp-30h]
  int32_t nType; // [rsp+1D4h] [rbp-2Ch]
  int32_t nLevel; // [rsp+1D8h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+1E0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+1E4h] [rbp-1Ch]
  int32_t i_0; // [rsp+1E8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+1ECh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/StarSpaceLevel.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,ShouHuRefinishingCfg>::clear(&this->m_ShouHuRefinishingCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 36);
        std::list<ItemData>::list(&stu.lCostList);
        std::list<AddAttribute>::list(&stu.lAttrList);
        nType = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        nLevel = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v12);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(bCombi, v2->pString, &v12);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lCostList, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v12);
        ++nIndex;
        std::allocator<char>::allocator(&v15);
        std::string::string(v14, "./ServerConfig/Tables/StarSpaceLevel.txt", &v15);
        std::allocator<char>::allocator(&v17);
        v3 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v16, v3->pString, &v17);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v16,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v16);
        std::allocator<char>::~allocator(&v17);
        std::string::~string(v14);
        std::allocator<char>::~allocator(&v15);
        stu.SuitId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(nType, nLevel);
        std::pair<std::pair const<int,int>,ShouHuRefinishingCfg>::pair(
          (std::pair<const std::pair<int,int>,ShouHuRefinishingCfg> *const)v19,
          &__a,
          &stu);
        v18 = std::map<std::pair<int,int>,ShouHuRefinishingCfg>::insert(
                &this->m_ShouHuRefinishingCfgMap,
                (const std::pair<const std::pair<int,int>,ShouHuRefinishingCfg> *const)v19);
        std::pair<std::pair const<int,int>,ShouHuRefinishingCfg>::~pair((std::pair<const std::pair<int,int>,ShouHuRefinishingCfg> *const)v19);
        ShouHuRefinishingCfg::~ShouHuRefinishingCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/StarSpaceSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,std::list<AddAttribute>>::clear(&this->m_ShouHuRefinishingSuitMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          nId = CDBCFile::Search_Posistion(&TabFile, i_0, 0)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v22);
          std::string::string(v21, "./ServerConfig/Tables/StarSpaceSuit.txt", &v22);
          std::allocator<char>::allocator(&v24);
          v4 = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0);
          std::string::string(v23, v4->pString, &v24);
          CfgData::parseAddAttribues(
            (CfgData *const)&AddAttrs,
            (const std::string *const)this,
            (int32_t)v23,
            (const std::string *const)(unsigned int)nIndex_0);
          std::string::~string(v23);
          std::allocator<char>::~allocator(&v24);
          std::string::~string(v21);
          std::allocator<char>::~allocator(&v22);
          ++nIndex_0;
          v5 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_ShouHuRefinishingSuitMap, &nId);
          std::list<AddAttribute>::operator=(v5, &AddAttrs);
          std::list<AddAttribute>::~list(&AddAttrs);
        }
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
  }
}


#####################################
void __cdecl CfgData::InitGoblinTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  std::list<AddAttribute> *v3; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-160h] BYREF
  AddAttrList AddAttrs; // [rsp+B0h] [rbp-D0h] BYREF
  int32_t nId; // [rsp+CCh] [rbp-B4h] BYREF
  GoblinCfg stu; // [rsp+D0h] [rbp-B0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,GoblinCfg> >,bool> v8; // [rsp+E0h] [rbp-A0h]
  _BYTE v9[32]; // [rsp+F0h] [rbp-90h] BYREF
  std::pair<int,int> __a; // [rsp+110h] [rbp-70h] BYREF
  _BYTE v11[15]; // [rsp+120h] [rbp-60h] BYREF
  char v12; // [rsp+12Fh] [rbp-51h] BYREF
  int32_t v13[4]; // [rsp+130h] [rbp-50h] BYREF
  char v14; // [rsp+142h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+144h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+148h] [rbp-38h]
  int32_t i; // [rsp+14Ch] [rbp-34h]
  int32_t nIndex; // [rsp+150h] [rbp-30h]
  int32_t nType; // [rsp+154h] [rbp-2Ch]
  int32_t nLevel; // [rsp+158h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+164h] [rbp-1Ch]
  int32_t i_0; // [rsp+168h] [rbp-18h]
  int32_t nIndex_0; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/GoblinUp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,GoblinCfg>::clear(&this->m_GoblinCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.UpAttr = 0;
        stu.ConstCurr = 0;
        nType = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        nLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.UpAttr = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.SuitId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.ConstCurr = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(nType, nLevel);
        std::pair<std::pair const<int,int>,GoblinCfg>::pair(
          (std::pair<const std::pair<int,int>,GoblinCfg> *const)v9,
          &__a,
          &stu);
        v8 = std::map<std::pair<int,int>,GoblinCfg>::insert(
               &this->m_GoblinCfgMap,
               (const std::pair<const std::pair<int,int>,GoblinCfg> *const)v9);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/GoblinSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,std::list<AddAttribute>>::clear(&this->m_GoblinSuitMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          nId = CDBCFile::Search_Posistion(&TabFile, i_0, 0)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v12);
          std::string::string(v11, "./ServerConfig/Tables/GoblinSuit.txt", &v12);
          std::allocator<char>::allocator(&v14);
          v2 = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0);
          std::string::string(v13, v2->pString, &v14);
          CfgData::parseAddAttribues(
            (CfgData *const)&AddAttrs,
            (const std::string *const)this,
            (int32_t)v13,
            (const std::string *const)(unsigned int)nIndex_0);
          std::string::~string(v13);
          std::allocator<char>::~allocator(&v14);
          std::string::~string(v11);
          std::allocator<char>::~allocator(&v12);
          ++nIndex_0;
          v3 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_GoblinSuitMap, &nId);
          std::list<AddAttribute>::operator=(v3, &AddAttrs);
          std::list<AddAttribute>::~list(&AddAttrs);
        }
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
  }
}


#####################################
void __cdecl CfgData::InitGuiGuDaoRenTable(CfgData *const this)
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
  GuiGuDaoRenCfg *v14; // rax
  __int64 v15; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-250h] BYREF
  GuiGuDaoRenCfg stu; // [rsp+B0h] [rbp-1C0h] BYREF
  RefreshMonster tmpStu; // [rsp+110h] [rbp-160h] BYREF
  StringVector vstr; // [rsp+120h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+140h] [rbp-130h] BYREF
  StringVector SplitStr; // [rsp+150h] [rbp-120h] BYREF
  std::string RefreshMonsterString; // [rsp+170h] [rbp-100h] BYREF
  char v23; // [rsp+17Fh] [rbp-F1h] BYREF
  std::string delims; // [rsp+180h] [rbp-F0h] BYREF
  char v25; // [rsp+18Fh] [rbp-E1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+190h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1A0h] [rbp-D0h] BYREF
  std::string v28; // [rsp+1B0h] [rbp-C0h] BYREF
  char v29; // [rsp+1BFh] [rbp-B1h] BYREF
  ItemData __x; // [rsp+1C0h] [rbp-B0h] BYREF
  std::string strItem; // [rsp+1D0h] [rbp-A0h] BYREF
  char v32; // [rsp+1DFh] [rbp-91h] BYREF
  MemChrBag v33; // [rsp+1E0h] [rbp-90h] BYREF
  std::string v34; // [rsp+200h] [rbp-70h] BYREF
  char v35; // [rsp+20Fh] [rbp-61h] BYREF
  Int32Vector v36; // [rsp+210h] [rbp-60h] BYREF
  std::string path; // [rsp+230h] [rbp-40h] BYREF
  char v38; // [rsp+23Fh] [rbp-31h] BYREF
  std::string str; // [rsp+240h] [rbp-30h] BYREF
  char v40; // [rsp+24Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+24Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+250h] [rbp-20h]
  int32_t i; // [rsp+254h] [rbp-1Ch]
  int32_t nIndex; // [rsp+258h] [rbp-18h]
  int32_t j; // [rsp+25Ch] [rbp-14h]
  ItemData v47; // 0:kr00_12.12

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TaoistTask.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GUI_GU_DAO_REN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,GuiGuDaoRenCfg>::clear(&this->m_GuiGuDaoRenCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::list<RefreshMonster>::list(&stu.lRefreshMonster);
        std::vector<ItemData>::vector(&stu.vItemData);
        std::vector<MemChrBag>::vector(&stu.vItem);
        std::vector<int>::vector(&stu.vMapId);
        nIndex = 0;
        stu.nNpcId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nMaxCount = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v23);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&RefreshMonsterString, v1->pString, &v23);
        std::allocator<char>::~allocator(&v23);
        ++nIndex;
        std::allocator<char>::allocator(&v25);
        std::string::string(&delims, "|", &v25);
        Answer::StringUtility::split(&SplitStr, &RefreshMonsterString, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v25);
        __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
          &iterBegin,
          &__i);
        while ( 1 )
        {
          __rhs._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
          if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &__rhs) )
            break;
          std::allocator<char>::allocator(&v29);
          std::string::string(&v28, ":", &v29);
          v2 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
          Answer::StringUtility::split(&vstr, v2, &v28, 0);
          std::string::~string(&v28);
          std::allocator<char>::~allocator(&v29);
          if ( std::vector<std::string>::size(&vstr) == 4 )
          {
            *(_QWORD *)&tmpStu.nCount = 0;
            *(_QWORD *)&tmpStu.AliveTime = 0;
            v3 = std::vector<std::string>::operator[](&vstr, 0);
            v4 = (const char *)std::string::c_str(v3);
            tmpStu.nCount = atoi(v4);
            v5 = std::vector<std::string>::operator[](&vstr, 1u);
            v6 = (const char *)std::string::c_str(v5);
            tmpStu.BossId = atoi(v6);
            v7 = std::vector<std::string>::operator[](&vstr, 2u);
            v8 = (const char *)std::string::c_str(v7);
            tmpStu.AliveTime = atoi(v8);
            v9 = std::vector<std::string>::operator[](&vstr, 3u);
            v10 = (const char *)std::string::c_str(v9);
            tmpStu.GongGaoId = atoi(v10);
            std::list<RefreshMonster>::push_back(&stu.lRefreshMonster, &tmpStu);
          }
          std::vector<std::string>::~vector(&vstr);
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
        }
        std::vector<ItemData>::reserve(&stu.vItemData, 3u);
        std::vector<MemChrBag>::reserve(&stu.vItem, 3u);
        for ( j = 0; j <= 2; ++j )
        {
          std::allocator<char>::allocator(&v32);
          v11 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
          std::string::string(&strItem, v11->pString, &v32);
          v47 = CItemHelper::parseItemDataString(&strItem);
          LODWORD(v15) = v47.m_nId;
          BYTE4(v15) = v47.m_nClass;
          *(_QWORD *)&__x.m_nId = v15;
          __x.m_nCount = v47.m_nCount;
          std::vector<ItemData>::push_back(&stu.vItemData, &__x);
          std::string::~string(&strItem);
          std::allocator<char>::~allocator(&v32);
          ++nIndex;
          std::allocator<char>::allocator(&v35);
          v12 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
          std::string::string(&v34, v12->pString, &v35);
          CItemHelper::parseItemString(&v33, &v34);
          std::vector<MemChrBag>::push_back(&stu.vItem, &v33);
          std::string::~string(&v34);
          std::allocator<char>::~allocator(&v35);
          ++nIndex;
        }
        std::allocator<char>::allocator(&v38);
        std::string::string(&path, "./ServerConfig/Tables/TaoistTask.txt", &v38);
        std::allocator<char>::allocator(&v40);
        v13 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&str, v13->pString, &v40);
        CfgData::paraseInt32Vector(&v36, this, &str, &path, 0);
        std::vector<int>::operator=(&stu.vMapId, &v36);
        std::vector<int>::~vector(&v36);
        std::string::~string(&str);
        std::allocator<char>::~allocator(&v40);
        std::string::~string(&path);
        std::allocator<char>::~allocator(&v38);
        ++nIndex;
        v14 = std::map<int,GuiGuDaoRenCfg>::operator[](&this->m_GuiGuDaoRenCfgMap, &stu.nNpcId);
        GuiGuDaoRenCfg::operator=(v14, &stu);
        std::vector<std::string>::~vector(&SplitStr);
        std::string::~string(&RefreshMonsterString);
        GuiGuDaoRenCfg::~GuiGuDaoRenCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitShiZhuangTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-190h] BYREF
  CfgShiZhuang stu; // [rsp+A0h] [rbp-100h] BYREF
  ShiZhuangSuitInfo SuitInfo; // [rsp+C0h] [rbp-E0h] BYREF
  ShiZhuangSuitCfg stu_0; // [rsp+E0h] [rbp-C0h] BYREF
  AddAttribute AddAttr; // [rsp+100h] [rbp-A0h] BYREF
  std::list<AddAttribute> __x; // [rsp+110h] [rbp-90h] BYREF
  _BYTE v9[15]; // [rsp+120h] [rbp-80h] BYREF
  char v10; // [rsp+12Fh] [rbp-71h] BYREF
  int32_t v11[3]; // [rsp+130h] [rbp-70h] BYREF
  char v12; // [rsp+13Fh] [rbp-61h] BYREF
  ShiZhuangSuitCfg p_stu; // [rsp+140h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+164h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+168h] [rbp-38h]
  int32_t i; // [rsp+16Ch] [rbp-34h]
  int32_t nIndex; // [rsp+170h] [rbp-30h]
  int32_t j; // [rsp+174h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+17Ch] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+180h] [rbp-20h]
  int32_t i_0; // [rsp+184h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+188h] [rbp-18h]
  int32_t j_0; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShiZhuang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileShiZhu_0);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgShiZhuang::CfgShiZhuang(&stu);
        nIndex = 0;
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        for ( j = 0; j <= 6; ++j )
        {
          AddAttribute::AddAttribute(&AddAttr);
          AddAttr.m_nAddAttrType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
          AddAttr.m_nAddAttrValue = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
          if ( AddAttr.m_nAddAttrValue > 0 )
            std::list<AddAttribute>::push_back(&stu.vAttr, &AddAttr);
        }
        nIndex += 7;
        stu.nSuitId = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        CfgShiZhuangTable::AddShiZhuang(&this->m_cfgShiZhuangTable, &stu);
        CfgShiZhuang::~CfgShiZhuang(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShiZhuangSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileShiZhu_1);
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          ShiZhuangSuitCfg::ShiZhuangSuitCfg(&stu_0);
          nIndex_0 = 0;
          stu_0.nSuidId = CDBCFile::Search_Posistion(&readFile, i_0, 0)->iValue;
          ++nIndex_0;
          stu_0.nCount = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          ++nIndex_0;
          for ( j_0 = 0; j_0 <= 2; ++j_0 )
          {
            ShiZhuangSuitInfo::ShiZhuangSuitInfo(&SuitInfo);
            SuitInfo.nSuitLevel = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0++)->iValue;
            SuitInfo.nLevel = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0++)->iValue;
            std::allocator<char>::allocator(&v10);
            std::string::string(v9, "./ServerConfig/Tables/ShiZhuangSuit.txt", &v10);
            std::allocator<char>::allocator(&v12);
            v2 = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0);
            std::string::string(v11, v2->pString, &v12);
            CfgData::parseAddAttribues(
              (CfgData *const)&__x,
              (const std::string *const)this,
              (int32_t)v11,
              (const std::string *const)(unsigned int)nIndex_0);
            std::list<AddAttribute>::operator=(&SuitInfo.vAttr, &__x);
            std::list<AddAttribute>::~list(&__x);
            std::string::~string(v11);
            std::allocator<char>::~allocator(&v12);
            std::string::~string(v9);
            std::allocator<char>::~allocator(&v10);
            ++nIndex_0;
            ++nIndex_0;
            ++nIndex_0;
            std::list<ShiZhuangSuitInfo>::push_back(&stu_0.lInfo, &SuitInfo);
            ShiZhuangSuitInfo::~ShiZhuangSuitInfo(&SuitInfo);
          }
          ShiZhuangSuitCfg::ShiZhuangSuitCfg(&p_stu, &stu_0);
          CfgShiZhuangTable::AddShiZhuangSuitInfo(&this->m_cfgShiZhuangTable, &p_stu);
          ShiZhuangSuitCfg::~ShiZhuangSuitCfg(&p_stu);
          ShiZhuangSuitCfg::~ShiZhuangSuitCfg(&stu_0);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile);
  }
}


#####################################
void __cdecl CfgData::InitShiZhuangLevelTable(CfgData *const this)
{
  CDBCFile readFile; // [rsp+10h] [rbp-100h] BYREF
  CfgShiZhuangLevel stu; // [rsp+A0h] [rbp-70h] BYREF
  AddAttribute AddAttr; // [rsp+E0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+F0h] [rbp-20h]
  int32_t i; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+F8h] [rbp-18h]
  int32_t j; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/ShiZhuangLevel.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileShiZhu_2);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgShiZhuangLevel::CfgShiZhuangLevel(&stu);
        nIndex = 0;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nLevelExp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nNeedLevel = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nCostItem = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nGetExp = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nSmallCritRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nLargeCritRate = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nBroadcast = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        for ( j = 0; j <= 6; ++j )
        {
          AddAttribute::AddAttribute(&AddAttr);
          AddAttr.m_nAddAttrType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
          AddAttr.m_nAddAttrValue = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
          if ( AddAttr.m_nAddAttrValue > 0 )
            std::list<AddAttribute>::push_back(&stu.vAttr, &AddAttr);
        }
        CfgShiZhuangTable::AddShiZhuangLevel(&this->m_cfgShiZhuangTable, &stu);
        CfgShiZhuangLevel::~CfgShiZhuangLevel(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMonthlyChouJiangTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+30h] [rbp-110h] BYREF
  MonthlyChouJiangCfg stu; // [rsp+C0h] [rbp-80h]
  RateItem ItemRate; // [rsp+D0h] [rbp-70h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-50h] BYREF
  char v7; // [rsp+102h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-38h]
  int32_t i; // [rsp+10Ch] [rbp-34h]
  int32_t nIndex; // [rsp+110h] [rbp-30h]
  int32_t Month; // [rsp+114h] [rbp-2Ch]
  int32_t nId; // [rsp+118h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+124h] [rbp-1Ch]
  int32_t i_0; // [rsp+128h] [rbp-18h]
  int32_t nIndex_0; // [rsp+12Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TurntableReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TURNTABLE_REWARD_TABLE failed, please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        Month = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        nId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItem, v2->pString, &v7);
        CItemHelper::parseRateItemDataString(&ItemRate, &strItem);
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        MonthlyChouJiangTable::AddMonthlyChouJiangItemMap(&this->m_MonthlyChouJiangTable, Month, nId, ItemRate);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/TurntableRechargePoint.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_TURNTABLE_RECHARGE_POINT failed, please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          *(_QWORD *)&stu.nId = 0;
          *(_QWORD *)&stu.nAddValues = 0;
          stu.nId = CDBCFile::Search_Posistion(&TabFile, i_0, 0)->iValue;
          stu.nRecharges = CDBCFile::Search_Posistion(&TabFile, i_0, ++nIndex_0)->iValue;
          stu.nAddValues = CDBCFile::Search_Posistion(&TabFile, i_0, ++nIndex_0)->iValue;
          stu.nGetTimes = CDBCFile::Search_Posistion(&TabFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          MonthlyChouJiangTable::AddMonthlyChouJiangCfg(&this->m_MonthlyChouJiangTable, stu);
        }
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
  }
}


#####################################
void __cdecl CfgData::InitActDropTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ActDropItem> *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  ActDropItem stu; // [rsp+A0h] [rbp-70h] BYREF
  int32_t Type; // [rsp+CCh] [rbp-44h] BYREF
  std::string p_StringTime; // [rsp+D0h] [rbp-40h] BYREF
  char v8; // [rsp+DFh] [rbp-31h] BYREF
  std::string v9; // [rsp+E0h] [rbp-30h] BYREF
  char v10; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/shoujihuodong.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ACTDROP_TABLE failed, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        Type = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nMinLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nMaxLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nMapType = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nClass = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nCount = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nBind = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&p_StringTime, v1->pString, &v8);
        stu.nStartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v9, v2->pString, &v10);
        stu.nEndTime = Answer::DayTime::StringToIntTime(&v9);
        std::string::~string(&v9);
        std::allocator<char>::~allocator(&v10);
        stu.nProbability = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,std::list<ActDropItem>>::operator[](&this->m_ActDropItemListMap, &Type);
        std::list<ActDropItem>::push_back(v3, &stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitOutLinkFestivalTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-F0h] BYREF
  CfgOutLinkFestival stu; // [rsp+A0h] [rbp-60h] BYREF
  std::string p_StringTime; // [rsp+C0h] [rbp-40h] BYREF
  char v7; // [rsp+CFh] [rbp-31h] BYREF
  std::string v8; // [rsp+D0h] [rbp-30h] BYREF
  char v9; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/OutLinkFestival.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_OUT_LINK_FESTIVAL_TABLE failed, please check!!!\n");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.strPlatfrom);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&p_StringTime, v1->pString, &v7);
        stu.nStartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        std::allocator<char>::allocator(&v9);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v8, v2->pString, &v9);
        stu.nEndTime = Answer::DayTime::StringToIntTime(&v8);
        std::string::~string(&v8);
        std::allocator<char>::~allocator(&v9);
        stu.nIcon = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        v3 = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex);
        std::string::operator=(&stu.strPlatfrom, v3->pString);
        ++nIndex;
        CfgOutLinkFestivalTable::Add(&this->m_cfgOutLinkFestivalTable, &stu);
        CfgOutLinkFestival::~CfgOutLinkFestival(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitYYDaTing(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgYYGameApp *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgYYGameApp stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/YYDaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::vector<MemChrBag>::vector(&stu.Rewards);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nCondition = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        v2 = std::map<int,CfgYYGameApp>::operator[](&this->m_CfgYYGameAppMap, &stu.nIndex);
        CfgYYGameApp::operator=(v2, &stu);
        CfgYYGameApp::~CfgYYGameApp(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitLaDaShiHuiYuan(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  LuDaShiVip *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  LuDaShiVip stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/LuDaShiHuiYuan.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9220);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 44);
        std::vector<MemChrBag>::vector(&stu.Rewards);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nCondition = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        stu.nVipType = CDBCFile::Search_Posistion(&TabFile, i, 8)->iValue;
        stu.nMaxCondition = CDBCFile::Search_Posistion(&TabFile, i, 11)->iValue;
        v2 = std::map<int,LuDaShiVip>::operator[](&this->m_LuDaShiVipMap, &stu.nIndex);
        LuDaShiVip::operator=(v2, &stu);
        LuDaShiVip::~LuDaShiVip(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitYYVip(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  CfgYYVip *v3; // rax
  int v4; // ebx
  CDBCFile TabFile; // [rsp+10h] [rbp-150h] BYREF
  CfgYYVip stu; // [rsp+A0h] [rbp-C0h] BYREF
  CfgYYSuperBuff stu_1; // [rsp+D0h] [rbp-90h] BYREF
  CfgYYSuperBuff stu_0; // [rsp+E0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-70h] BYREF
  std::string strItems; // [rsp+110h] [rbp-50h] BYREF
  char v11; // [rsp+122h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+124h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+128h] [rbp-38h]
  int32_t i; // [rsp+12Ch] [rbp-34h]
  int32_t iBaseTableCount_0; // [rsp+134h] [rbp-2Ch]
  int32_t iBaseColumnCount_0; // [rsp+138h] [rbp-28h]
  int32_t i_0; // [rsp+13Ch] [rbp-24h]
  int32_t iBaseTableCount_1; // [rsp+144h] [rbp-1Ch]
  int32_t iBaseColumnCount_1; // [rsp+148h] [rbp-18h]
  int32_t i_1; // [rsp+14Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/YYHuiYuan.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 44);
        std::vector<MemChrBag>::vector(&stu.Rewards);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v2->pString, &v11);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v11);
        stu.nCondition = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        stu.nPric = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        stu.nLimit = CDBCFile::Search_Posistion(&TabFile, i, 6)->iValue;
        v3 = std::map<int,CfgYYVip>::operator[](&this->m_CfgYYVipMap, &stu.nIndex);
        CfgYYVip::operator=(v3, &stu);
        CfgYYVip::~CfgYYVip(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/YYChaowanBoss.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu_0.SuperVipLevel = 0;
          stu_0.AttrType = 0;
          stu_0.SuperVipLevel = CDBCFile::Search_Posistion(&TabFile, i_0, 1)->iValue;
          stu_0.AttrRate = CDBCFile::Search_Posistion(&TabFile, i_0, 3)->iValue;
          stu_0.AttrType = CDBCFile::Search_Posistion(&TabFile, i_0, 5)->iValue;
          std::list<CfgYYSuperBuff>::push_front(&this->m_CfgYYSuperBuffList, &stu_0);
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
    if ( v4 )
    {
      CDBCFile::CDBCFile(&TabFile, 0);
      if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/SpecialThirtySevenBuff.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&TabFile);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&TabFile);
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            *(_QWORD *)&stu_1.SuperVipLevel = 0;
            stu_1.AttrType = 0;
            stu_1.SuperVipLevel = CDBCFile::Search_Posistion(&TabFile, i_1, 1)->iValue;
            stu_1.AttrRate = CDBCFile::Search_Posistion(&TabFile, i_1, 3)->iValue;
            stu_1.AttrType = CDBCFile::Search_Posistion(&TabFile, i_1, 5)->iValue;
            std::list<CfgYYSuperBuff>::push_front(&this->m_Cfg37wanSuperBuffList, &stu_1);
          }
        }
      }
      CDBCFile::~CDBCFile(&TabFile);
    }
  }
}


#####################################
void __cdecl CfgData::InitSouGouDaTing(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  CfgSgGameApp *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  CfgSgGameApp stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/SouGouDaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vRewards);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nCondition = CDBCFile::Search_Posistion(&TabFile, i, 4)->iValue;
        v2 = std::map<int,CfgSgGameApp>::operator[](&this->m_CfgSgGameAppMap, &stu.nIndex);
        CfgSgGameApp::operator=(v2, &stu);
        CfgSgGameApp::~CfgSgGameApp(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitPlatformDaTingMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-1A0h] BYREF
  PlatformDaTing stu; // [rsp+B0h] [rbp-110h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-D0h] BYREF
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  char v7; // [rsp+11Fh] [rbp-A1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1A4h] [rbp-1Ch]
  int32_t i; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex; // [rsp+1ACh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/DaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9320);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.Platform);
        std::vector<MemChrBag>::vector(&stu.vItems);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&stu, v1->pString);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.nParam = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nIcon = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nParam2 = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::string::string(&__y, &stu.Platform);
        std::make_pair<std::string,int>(&p___x.first, (int)&__y);
        std::pair<std::pair const<std::string,int>,PlatformDaTing>::pair(
          (std::pair<const std::pair<std::string,int>,PlatformDaTing> *const)v9,
          &p___x,
          &stu);
        v8 = std::map<std::pair<std::string,int>,PlatformDaTing>::insert(
               &this->m_PlatformDaTingMap,
               (const std::pair<const std::pair<std::string,int>,PlatformDaTing> *const)v9);
        std::pair<std::pair const<std::string,int>,PlatformDaTing>::~pair((std::pair<const std::pair<std::string,int>,PlatformDaTing> *const)v9);
        std::pair<std::string,int>::~pair(&p___x);
        std::string::~string(&__y);
        PlatformDaTing::~PlatformDaTing(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitMiniClientMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-1A0h] BYREF
  MiniClientCfg stu; // [rsp+B0h] [rbp-110h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-D0h] BYREF
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  char v7; // [rsp+11Fh] [rbp-A1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1A4h] [rbp-1Ch]
  int32_t i; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex; // [rsp+1ACh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/WeiDuanDaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9320);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<std::string,int>,MiniClientCfg>::clear(&this->m_GetMiniClientMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.Platform);
        std::vector<MemChrBag>::vector(&stu.vItems);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&stu, v1->pString);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        stu.nParam = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nIcon = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nParam2 = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::string::string(&__y, &stu.Platform);
        std::make_pair<std::string,int>(&p___x.first, (int)&__y);
        std::pair<std::pair const<std::string,int>,MiniClientCfg>::pair(
          (std::pair<const std::pair<std::string,int>,MiniClientCfg> *const)v9,
          &p___x,
          &stu);
        v8 = std::map<std::pair<std::string,int>,MiniClientCfg>::insert(
               &this->m_GetMiniClientMap,
               (const std::pair<const std::pair<std::string,int>,MiniClientCfg> *const)v9);
        std::pair<std::pair const<std::string,int>,MiniClientCfg>::~pair((std::pair<const std::pair<std::string,int>,MiniClientCfg> *const)v9);
        std::pair<std::string,int>::~pair(&p___x);
        std::string::~string(&__y);
        MiniClientCfg::~MiniClientCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitPlatformVipMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-180h] BYREF
  PlatformVip stu; // [rsp+B0h] [rbp-F0h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-C0h] BYREF
  std::string strItems; // [rsp+100h] [rbp-A0h] BYREF
  char v7; // [rsp+10Fh] [rbp-91h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformVip> >,bool> v8; // [rsp+110h] [rbp-90h]
  _BYTE v9[64]; // [rsp+120h] [rbp-80h] BYREF
  std::pair<std::string,int> p___x; // [rsp+160h] [rbp-40h] BYREF
  std::string __y; // [rsp+170h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/OutLinkVip.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C93A0);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 44);
        std::string::string(&stu.sPlatform);
        std::vector<MemChrBag>::vector(&stu.vItem);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::operator=(&stu, v1->pString);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nNeedVipLevel = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v7);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v2->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        nIndex += 2;
        stu.nIcon = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::string::string(&__y, &stu.sPlatform);
        std::make_pair<std::string,int>(&p___x.first, (int)&__y);
        std::pair<std::pair const<std::string,int>,PlatformVip>::pair(
          (std::pair<const std::pair<std::string,int>,PlatformVip> *const)v9,
          &p___x,
          &stu);
        v8 = std::map<std::pair<std::string,int>,PlatformVip>::insert(
               &this->m_PlatformVipMap,
               (const std::pair<const std::pair<std::string,int>,PlatformVip> *const)v9);
        std::pair<std::pair const<std::string,int>,PlatformVip>::~pair((std::pair<const std::pair<std::string,int>,PlatformVip> *const)v9);
        std::pair<std::string,int>::~pair(&p___x);
        std::string::~string(&__y);
        PlatformVip::~PlatformVip(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitPlatformReward(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile; // [rsp+20h] [rbp-1A0h] BYREF
  PlatformRewardCfg stu; // [rsp+B0h] [rbp-110h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-D0h] BYREF
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  char v7; // [rsp+11Fh] [rbp-A1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformRewardCfg> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1A4h] [rbp-1Ch]
  int32_t i; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex; // [rsp+1ACh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/Reward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C93F8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 52);
        std::vector<MemChrBag>::vector(&stu.vItem);
        std::string::string(&stu.sPlatform);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nIcon = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        v2 = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex);
        std::string::operator=(&stu.sPlatform, v2->pString);
        stu.nIsAllShow = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::string::string(&__y, &stu.sPlatform);
        std::make_pair<std::string,int>(&p___x.first, (int)&__y);
        std::pair<std::pair const<std::string,int>,PlatformRewardCfg>::pair(
          (std::pair<const std::pair<std::string,int>,PlatformRewardCfg> *const)v9,
          &p___x,
          &stu);
        v8 = std::map<std::pair<std::string,int>,PlatformRewardCfg>::insert(
               &this->m_PlatformRewardCfgMap,
               (const std::pair<const std::pair<std::string,int>,PlatformRewardCfg> *const)v9);
        std::pair<std::pair const<std::string,int>,PlatformRewardCfg>::~pair((std::pair<const std::pair<std::string,int>,PlatformRewardCfg> *const)v9);
        std::pair<std::string,int>::~pair(&p___x);
        std::string::~string(&__y);
        PlatformRewardCfg::~PlatformRewardCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitDiligenceCfgMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  DiligenceCfg *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-F0h] BYREF
  DiligenceCfg stu; // [rsp+A0h] [rbp-60h] BYREF
  std::list<RateItem> strItems; // [rsp+C0h] [rbp-40h] BYREF
  _BYTE v6[14]; // [rsp+D0h] [rbp-30h] BYREF
  char v7; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/QinFen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9450);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<RateItem>::list(&stu.lItems);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.nValues = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(v6, v1->pString, &v7);
        CItemHelper::parseRateItemDataListString((const std::string *const)&strItems);
        std::list<RateItem>::operator=(&stu.lItems, &strItems);
        std::list<RateItem>::~list(&strItems);
        std::string::~string(v6);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        v2 = std::map<int,DiligenceCfg>::operator[](&this->m_DiligenceCfgMap, &stu.nId);
        DiligenceCfg::operator=(v2, &stu);
        DiligenceCfg::~DiligenceCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitFamilyDonateTable(CfgData *const this)
{
  ContributionCfg *v1; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-D0h] BYREF
  ContributionCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/FamilyDonate.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C94A0);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,ContributionCfg>::clear(&this->m_ContributionCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nCount = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nExp = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.nContributionValue = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,ContributionCfg>::operator[](&this->m_ContributionCfgMap, &stu.nId);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitShangRenCfgMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  ShangRenCfg *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  ShangRenCfg stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/MagicBusiness.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C94F8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 36);
        std::vector<MemChrBag>::vector(&stu.vItem);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nPrice = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,ShangRenCfg>::operator[](&this->m_ShangRenCfgMap, &stu.nId);
        ShangRenCfg::operator=(v2, &stu);
        ShangRenCfg::~ShangRenCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitSelectItemCfgMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  SelectItemCfg *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  SelectItemCfg stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v7; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/GiftChoose.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9548);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vItem);
        stu.nId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        ++nIndex;
        v2 = std::map<int,SelectItemCfg>::operator[](&this->m_SelectItemCfgMap, &stu.nId);
        SelectItemCfg::operator=(v2, &stu);
        SelectItemCfg::~SelectItemCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitCycleTowerTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  __int64 v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-100h] BYREF
  CycleTowerCost stu_0; // [rsp+A0h] [rbp-70h]
  CycleTowerMapCfg stu; // [rsp+B0h] [rbp-60h]
  std::string strItem; // [rsp+C0h] [rbp-50h] BYREF
  char v8; // [rsp+D2h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+D4h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+D8h] [rbp-38h]
  int32_t i; // [rsp+DCh] [rbp-34h]
  int32_t nIndex; // [rsp+E0h] [rbp-30h]
  int32_t MapId; // [rsp+E4h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+F0h] [rbp-20h]
  int32_t i_0; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+F8h] [rbp-18h]
  int32_t Times; // [rsp+FCh] [rbp-14h]
  ItemData v21; // 0:kr00_12.12

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/LunHuiEvent.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C95A0);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        MapId = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.Floor = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.FloorType = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        stu.MonsterId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        CycleTowerTable::AddCycleTowerMapCfg(&this->m_CycleTowerTable, MapId, stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&TabFile, 0);
    if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/LunHuiConsume.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C95F8);
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&TabFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&TabFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 1;
          Times = CDBCFile::Search_Posistion(&TabFile, i_0, 1)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v8);
          v2 = CDBCFile::Search_Posistion(&TabFile, i_0, nIndex_0);
          std::string::string(&strItem, v2->pString, &v8);
          v21 = CItemHelper::parseItemDataString(&strItem);
          LODWORD(v3) = v21.m_nId;
          BYTE4(v3) = v21.m_nClass;
          *(_QWORD *)&stu_0.CostData.m_nId = v3;
          stu_0.CostData.m_nCount = v21.m_nCount;
          std::string::~string(&strItem);
          std::allocator<char>::~allocator(&v8);
          stu_0.CostGold = CDBCFile::Search_Posistion(&TabFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CycleTowerTable::AddCycleTowerCost(&this->m_CycleTowerTable, Times, stu_0);
        }
      }
    }
    CDBCFile::~CDBCFile(&TabFile);
  }
}


#####################################
void __cdecl CfgData::InitXunLeiTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  XunLeiCfg *v2; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-110h] BYREF
  XunLeiCfg stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/XunLeiBox.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::vector<MemChrBag>::vector(&stu.vRewards);
        stu.nIndex = CDBCFile::Search_Posistion(&TabFile, i, 0)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&TabFile, i, 1)->iValue;
        std::allocator<char>::allocator(&v7);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, 3);
        std::string::string(&strItems, v1->pString, &v7);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v7);
        stu.nCondition = CDBCFile::Search_Posistion(&TabFile, i, 5)->iValue;
        v2 = std::map<int,XunLeiCfg>::operator[](&this->m_XunLeiCfgMap, &stu.nIndex);
        XunLeiCfg::operator=(v2, &stu);
        XunLeiCfg::~XunLeiCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitCrossTowerCfgMap(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CrossTowerCfg *v3; // rax
  CDBCFile TabFile; // [rsp+10h] [rbp-170h] BYREF
  CrossTowerCfg stu; // [rsp+A0h] [rbp-E0h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-80h] BYREF
  std::string strItems; // [rsp+120h] [rbp-60h] BYREF
  char v8; // [rsp+12Fh] [rbp-51h] BYREF
  MemChrBagVector v9; // [rsp+130h] [rbp-50h] BYREF
  std::string v10; // [rsp+150h] [rbp-30h] BYREF
  char v11; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile(&TabFile, 0);
  if ( !CDBCFile::OpenFromTXT(&TabFile, "./ServerConfig/Tables/KuaFuMap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&TabFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&TabFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.RewardVt);
        std::vector<MemChrBag>::vector(&stu.TopRewardVt);
        stu.MapId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.NextMapId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.LastMapId = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.MaxPlayer = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.MaxScore = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.MinScore = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.KillCount = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        stu.Floor = CDBCFile::Search_Posistion(&TabFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v8);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.RewardVt, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        v2 = CDBCFile::Search_Posistion(&TabFile, i, nIndex);
        std::string::string(&v10, v2->pString, &v11);
        CItemHelper::parseItemVectorString(&v9, &v10);
        std::vector<MemChrBag>::operator=(&stu.TopRewardVt, &v9);
        std::vector<MemChrBag>::~vector(&v9);
        std::string::~string(&v10);
        std::allocator<char>::~allocator(&v11);
        stu.MailId = CDBCFile::Search_Posistion(&TabFile, i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,CrossTowerCfg>::operator[](&this->m_CrossTowerCfgMap, &stu.MapId);
        CrossTowerCfg::operator=(v3, &stu);
        CrossTowerCfg::~CrossTowerCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&TabFile);
}


#####################################
void __cdecl CfgData::InitGuardPrivilegeTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-130h] BYREF
  CfgGuardPrivilege stu; // [rsp+A0h] [rbp-A0h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-80h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-60h] BYREF
  char v8; // [rsp+EFh] [rbp-51h] BYREF
  std::string p_StringTime; // [rsp+F0h] [rbp-50h] BYREF
  char v10; // [rsp+FFh] [rbp-41h] BYREF
  std::string v11; // [rsp+100h] [rbp-40h] BYREF
  char v12; // [rsp+116h] [rbp-2Ah] BYREF
  int32_t iBaseTableCount; // [rsp+118h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+11Ch] [rbp-24h]
  int32_t i; // [rsp+120h] [rbp-20h]
  int32_t nIndex; // [rsp+124h] [rbp-1Ch]
  int32_t nStartTime; // [rsp+128h] [rbp-18h]
  int32_t nEndTime; // [rsp+12Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/GuardPrivilegeReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileGuardP);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgGuardPrivilege::CfgGuardPrivilege(&stu);
        stu.nIndex = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nType = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nDaily = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.nParam = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v8);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v10);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&p_StringTime, v2->pString, &v10);
        nStartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        std::allocator<char>::allocator(&v12);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v11, v3->pString, &v12);
        nEndTime = Answer::DayTime::StringToIntTime(&v11);
        std::string::~string(&v11);
        std::allocator<char>::~allocator(&v12);
        ++nIndex;
        if ( !i )
          CfgGuardPrivilegeTable::SetTime(&this->m_cfgGuardPrivilegeTable, nStartTime, nEndTime);
        CfgGuardPrivilegeTable::Add(&this->m_cfgGuardPrivilegeTable, &stu);
        CfgGuardPrivilege::~CfgGuardPrivilege(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitMoFuTable(CfgData *const this)
{
  int v1; // ebx
  MoFuSkillCfg *v2; // rax
  int v3; // ebx
  const CDBCFile::FIELD *v4; // rax
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,ZhuNengCfg> >,bool> v5; // rax
  const CDBCFile::FIELD *v6; // rax
  MoFuDuiHuan *v7; // rax
  __int64 v8; // rax
  MemChrBag v9; // [rsp+0h] [rbp-250h] BYREF
  std::_Rb_tree_node_base::_Base_ptr M_node; // [rsp+20h] [rbp-230h]
  int v11; // [rsp+28h] [rbp-228h]
  CfgData *thisa; // [rsp+38h] [rbp-218h]
  CDBCFile readFile_0; // [rsp+40h] [rbp-210h] BYREF
  MoFuDuiHuan stu_1; // [rsp+D0h] [rbp-180h] BYREF
  ZhuNengCfg stu_0; // [rsp+160h] [rbp-F0h] BYREF
  MoFuSkillCfg stu; // [rsp+180h] [rbp-D0h] BYREF
  std::string strItem; // [rsp+190h] [rbp-C0h] BYREF
  char v18; // [rsp+19Fh] [rbp-B1h] BYREF
  std::_Rb_tree_node_base::_Base_ptr v19; // [rsp+1A0h] [rbp-B0h]
  bool second; // [rsp+1A8h] [rbp-A8h]
  _BYTE v21[48]; // [rsp+1B0h] [rbp-A0h] BYREF
  std::pair<int,int> __a; // [rsp+1E0h] [rbp-70h] BYREF
  std::string v23; // [rsp+1F0h] [rbp-60h] BYREF
  char v24; // [rsp+206h] [rbp-4Ah] BYREF
  int32_t iBaseTableCount; // [rsp+208h] [rbp-48h]
  int32_t iBaseColumnCount; // [rsp+20Ch] [rbp-44h]
  int32_t i; // [rsp+210h] [rbp-40h]
  int32_t nIndex; // [rsp+214h] [rbp-3Ch]
  int32_t iBaseTableCount_0; // [rsp+21Ch] [rbp-34h]
  int32_t iBaseColumnCount_0; // [rsp+220h] [rbp-30h]
  int32_t i_0; // [rsp+224h] [rbp-2Ch]
  int32_t nIndex_0; // [rsp+228h] [rbp-28h]
  int32_t iBaseTableCount_1; // [rsp+230h] [rbp-20h]
  int32_t iBaseColumnCount_1; // [rsp+234h] [rbp-1Ch]
  int32_t i_1; // [rsp+238h] [rbp-18h]
  int32_t nIndex_1; // [rsp+23Ch] [rbp-14h]
  ItemData v40; // 0:kr00_12.12

  thisa = this;
  CDBCFile::CDBCFile((CDBCFile *const)&stu_1, 0);
  if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_1, "./ServerConfig/Tables/MoFuSkill.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileLingZh_2);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum((const CDBCFile *const)&stu_1);
    iBaseColumnCount = CDBCFile::GetFieldsNum((const CDBCFile *const)&stu_1);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,MoFuSkillCfg>::clear(&thisa->m_MoFuSkillCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.nLevel = 0;
        *(_QWORD *)&stu.nSkillLevel = 0;
        stu.nLevel = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i, 0)->iValue;
        stu.nSkillTalent = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i, ++nIndex)->iValue;
        stu.nSkillLevel = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i, ++nIndex)->iValue;
        stu.nActivation = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,MoFuSkillCfg>::operator[](&thisa->m_MoFuSkillCfgMap, &stu.nLevel);
        *v2 = stu;
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile((CDBCFile *const)&stu_1);
  if ( v1 )
  {
    CDBCFile::CDBCFile((CDBCFile *const)&stu_1, 0);
    if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_1, "./ServerConfig/Tables/ZhuNeng.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileLingZh_2);
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum((const CDBCFile *const)&stu_1);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum((const CDBCFile *const)&stu_1);
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<std::pair<int,int>,ZhuNengCfg>::clear(&thisa->m_ZhuNengCfgMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu_0, 0, sizeof(stu_0));
          stu_0.nLevel = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i_0, 0)->iValue;
          stu_0.nSlotType = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          std::allocator<char>::allocator(&v18);
          v4 = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i_0, nIndex_0);
          std::string::string(&strItem, v4->pString, &v18);
          v40 = CItemHelper::parseItemDataString(&strItem);
          LODWORD(v8) = v40.m_nId;
          BYTE4(v8) = v40.m_nClass;
          *(_QWORD *)&stu_0.Item.m_nId = v8;
          stu_0.Item.m_nCount = v40.m_nCount;
          std::string::~string(&strItem);
          std::allocator<char>::~allocator(&v18);
          stu_0.BasicAttr = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          stu_0.GongGaoId = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_1, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          __a = std::make_pair<int,int>(stu_0.nSlotType, stu_0.nLevel);
          std::pair<std::pair const<int,int>,ZhuNengCfg>::pair(
            (std::pair<const std::pair<int,int>,ZhuNengCfg> *const)v21,
            &__a,
            &stu_0);
          v5 = std::map<std::pair<int,int>,ZhuNengCfg>::insert(
                 &thisa->m_ZhuNengCfgMap,
                 (const std::pair<const std::pair<int,int>,ZhuNengCfg> *const)v21);
          M_node = v5.first._M_node;
          v11 = *(_DWORD *)&v5.second;
          v19 = v5.first._M_node;
          second = v5.second;
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    CDBCFile::~CDBCFile((CDBCFile *const)&stu_1);
    if ( v3 )
    {
      CDBCFile::CDBCFile(&readFile_0, 0);
      if ( !CDBCFile::OpenFromTXT(&readFile_0, "./ServerConfig/Tables/MoFuExchange.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileLingZh_2);
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&readFile_0);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&readFile_0);
        if ( iBaseColumnCount_1 > 0 )
        {
          std::map<int,MoFuDuiHuan>::clear(&thisa->m_MoFuDuiHuanMap);
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            memset(&stu_1, 0, sizeof(stu_1));
            stu_1.nId = CDBCFile::Search_Posistion(&readFile_0, i_1, 0)->iValue;
            ++nIndex_1;
            std::allocator<char>::allocator(&v24);
            v6 = CDBCFile::Search_Posistion(&readFile_0, i_1, nIndex_1);
            std::string::string(&v23, v6->pString, &v24);
            CItemHelper::parseItemString(&v9, &v23);
            stu_1.Item = v9;
            std::string::~string(&v23);
            std::allocator<char>::~allocator(&v24);
            stu_1.ConstScore = CDBCFile::Search_Posistion(&readFile_0, i_1, ++nIndex_1)->iValue;
            stu_1.WeekLimit = CDBCFile::Search_Posistion(&readFile_0, i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            v7 = std::map<int,MoFuDuiHuan>::operator[](&thisa->m_MoFuDuiHuanMap, &stu_1.nId);
            *v7 = stu_1;
          }
        }
      }
      CDBCFile::~CDBCFile(&readFile_0);
    }
  }
}


#####################################
void __cdecl CfgData::InitChristmasDuiHuanTable(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  ChristmasDuiHuan *v5; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-160h] BYREF
  ChristmasDuiHuan stu; // [rsp+A0h] [rbp-D0h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-90h] BYREF
  std::string strItems; // [rsp+100h] [rbp-70h] BYREF
  char v10; // [rsp+10Fh] [rbp-61h] BYREF
  std::list<ItemData> v11; // [rsp+110h] [rbp-60h] BYREF
  bool bCombi[15]; // [rsp+120h] [rbp-50h] BYREF
  char v13; // [rsp+12Fh] [rbp-41h] BYREF
  std::string p_StringTime; // [rsp+130h] [rbp-40h] BYREF
  char v15; // [rsp+13Fh] [rbp-31h] BYREF
  std::string v16; // [rsp+140h] [rbp-30h] BYREF
  char v17; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Christmas.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileLingZh_2);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,ChristmasDuiHuan>::clear(&this->m_ChristmasDuiHuanMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 60);
        std::vector<MemChrBag>::vector(&stu.Items);
        std::list<ItemData>::list(&stu.CostItems);
        stu.nIndx = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v10);
        v1 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&strItems, v1->pString, &v10);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v10);
        ++nIndex;
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(bCombi, v2->pString, &v13);
        CItemHelper::parseItemDataListString((const std::string *const)&v11, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &v11);
        std::list<ItemData>::~list(&v11);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v13);
        stu.nLimitCount = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v15);
        v3 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&p_StringTime, v3->pString, &v15);
        stu.nStartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
        std::string::~string(&p_StringTime);
        std::allocator<char>::~allocator(&v15);
        ++nIndex;
        std::allocator<char>::allocator(&v17);
        v4 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(&v16, v4->pString, &v17);
        stu.nEndTime = Answer::DayTime::StringToIntTime(&v16);
        std::string::~string(&v16);
        std::allocator<char>::~allocator(&v17);
        ++nIndex;
        v5 = std::map<int,ChristmasDuiHuan>::operator[](&this->m_ChristmasDuiHuanMap, &stu.nIndx);
        ChristmasDuiHuan::operator=(v5, &stu);
        ChristmasDuiHuan::~ChristmasDuiHuan(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
void __cdecl CfgData::InitTongTianChiRanTable(CfgData *const this)
{
  int *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-C0h] BYREF
  int32_t nId; // [rsp+A4h] [rbp-2Ch] BYREF
  int32_t iBaseTableCount; // [rsp+ACh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+B0h] [rbp-20h]
  int32_t i; // [rsp+B4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+B8h] [rbp-18h]
  int32_t nTitleId; // [rsp+BCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/tongtianpaihang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileTongTi);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,int>::clear(&this->m_TongTianChiRankReward);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        ++nIndex;
        nTitleId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,int>::operator[](&this->m_TongTianChiRankReward, &nId);
        *v1 = nTitleId;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
int32_t __cdecl CfgData::GetTongTianChiReward(CfgData *const this, int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,int>::lower_bound(&this->m_TongTianChiRankReward, &nIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_TongTianChiRankReward)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
void __cdecl CfgData::InitChargeDungeon(CfgData *const this)
{
  ChargeDungeonCfg *v1; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-D0h] BYREF
  ChargeDungeonCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/charge_dungeon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileCharge);
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = CDBCFile::Search_Posistion(&readFile, i, 0)->iValue;
        stu.nMinKaiFuDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nMaxKaiFuDay = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nChargeValue = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        stu.nDungeonId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,ChargeDungeonCfg>::operator[](&this->m_ChargeDungeonCfgMap, &stu.nId);
        *v1 = stu;
      }
    }
  }
  CDBCFile::~CDBCFile(&readFile);
}


#####################################
int32_t __cdecl CfgData::GetChargeDungeonId(CfgData *const this, int32_t nId, int32_t Todaycharge)
{
  CfgData *v3; // rax
  const std::pair<const int,ChargeDungeonCfg> *v4; // rax
  const std::pair<const int,ChargeDungeonCfg> *v5; // rax
  char v6; // al
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_const_iterator<std::pair<const int,ChargeDungeonCfg> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ChargeDungeonCfg> > __it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,ChargeDungeonCfg> > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ChargeDungeonCfg> > v14; // [rsp+40h] [rbp-10h] BYREF
  int32_t KaiFuDay; // [rsp+4Ch] [rbp-4h]

  thisa = this;
  nIda = nId;
  v3 = Answer::Singleton<CfgData>::instance();
  KaiFuDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1;
  __it._M_node = std::map<int,ChargeDungeonCfg>::find(&this->m_ChargeDungeonCfgMap, &nIda)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::_Rb_tree_const_iterator(&it, &__it);
  v14._M_node = std::map<int,ChargeDungeonCfg>::end(&thisa->m_ChargeDungeonCfgMap)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::_Rb_tree_const_iterator(&__x, &v14);
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator!=(&it, &__x)
    && ((v4 = std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it),
         v4->second.nMinKaiFuDay > KaiFuDay)
     || (v5 = std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it),
         v5->second.nMaxKaiFuDay < KaiFuDay)
     || std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it)->second.nChargeValue > Todaycharge
      ? (v6 = 0)
      : (v6 = 1),
        v6) )
  {
    return std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it)->second.nDungeonId;
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl CfgData::InitBaoKuFuBen(CfgData *const this)
{
  int v1; // ebx
  BaoKuFuBen *v2; // rax
  int32_t v3; // ebx
  int32_t v4; // ebx
  int32_t v5; // ebx
  int32_t v6; // ebx
  int32_t v7; // ebx
  int32_t v8; // ebx
  BaoKuRandom *v9; // rax
  BaoKuRandom *p_stu_0; // rbx
  unsigned int v11; // r8d
  __int64 v12; // rcx
  CDBCFile readFile_0; // [rsp+10h] [rbp-170h] BYREF
  BaoKuRandom stu_0; // [rsp+A0h] [rbp-E0h] BYREF
  BaoKuFuBen stu; // [rsp+130h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+148h] [rbp-38h]
  int32_t iBaseColumnCount; // [rsp+14Ch] [rbp-34h]
  int32_t i; // [rsp+150h] [rbp-30h]
  int32_t nIndex; // [rsp+154h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+15Ch] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+160h] [rbp-20h]
  int32_t i_0; // [rsp+164h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+168h] [rbp-18h]
  int32_t j; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile((CDBCFile *const)&stu_0, 0);
  if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_0, "./ServerConfig/Tables/BaoKuFuBen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBaoKuF);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum((const CDBCFile *const)&stu_0);
    iBaseColumnCount = CDBCFile::GetFieldsNum((const CDBCFile *const)&stu_0);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,BaoKuFuBen>::clear(&this->m_BaoKuFuBenMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.FuBenId = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, 0)->iValue;
        stu.InitCount = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.BuyCount = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.Gold = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.AddTimes = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,BaoKuFuBen>::operator[](&this->m_BaoKuFuBenMap, &stu.FuBenId);
        *v2 = stu;
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile((CDBCFile *const)&stu_0);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile_0, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile_0, "./ServerConfig/Tables/BaoKuRandom.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBaoKuF_0);
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile_0);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile_0);
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,BaoKuRandom>::clear(&this->m_BaoKuRandomMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu_0, 0, sizeof(stu_0));
          stu_0.Index = CDBCFile::Search_Posistion(&readFile_0, i_0, 0)->iValue;
          stu_0.XValue = CDBCFile::Search_Posistion(&readFile_0, i_0, ++nIndex_0)->iValue;
          stu_0.YValue = CDBCFile::Search_Posistion(&readFile_0, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          for ( j = 0; j <= 4; ++j )
          {
            v3 = j;
            stu_0.Items[v3].nRate = CDBCFile::Search_Posistion(&readFile_0, i_0, nIndex_0++)->iValue;
            v4 = j;
            stu_0.Items[v4].nItemId = CDBCFile::Search_Posistion(&readFile_0, i_0, nIndex_0++)->iValue;
            v5 = j;
            stu_0.Items[v5].nItemClass = CDBCFile::Search_Posistion(&readFile_0, i_0, nIndex_0++)->iValue;
            v6 = j;
            stu_0.Items[v6].nItemCount = CDBCFile::Search_Posistion(&readFile_0, i_0, nIndex_0++)->iValue;
            v7 = j;
            stu_0.Items[v7].nBind = CDBCFile::Search_Posistion(&readFile_0, i_0, nIndex_0++)->iValue;
            v8 = j;
            stu_0.Items[v8].nGongGaoId = CDBCFile::Search_Posistion(&readFile_0, i_0, nIndex_0++)->iValue;
          }
          v9 = std::map<int,BaoKuRandom>::operator[](&this->m_BaoKuRandomMap, &stu_0.Index);
          p_stu_0 = &stu_0;
          v11 = 132;
          if ( ((unsigned __int8)v9 & 4) != 0 )
          {
            v9->Index = stu_0.Index;
            v9 = (BaoKuRandom *)((char *)v9 + 4);
            p_stu_0 = (BaoKuRandom *)&stu_0.XValue;
            v11 = 128;
          }
          v12 = v11 >> 3;
          qmemcpy(v9, p_stu_0, 8 * v12);
          if ( (v11 & 4) != 0 )
            *(&v9->Index + 2 * v12) = *(&p_stu_0->Index + 2 * v12);
        }
      }
    }
    CDBCFile::~CDBCFile(&readFile_0);
  }
}


#####################################
void __cdecl CfgData::InitXinMoTable(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  int v6; // ebx
  const CDBCFile::FIELD *v7; // rax
  const CDBCFile::FIELD *v8; // rax
  std::string *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  int v14; // ebx
  const CDBCFile::FIELD *v15; // rax
  const CDBCFile::FIELD *v16; // rax
  int v17; // ebx
  int v18; // ebx
  const CDBCFile::FIELD *v19; // rax
  const CDBCFile::FIELD *v20; // rax
  CDBCFile readFile; // [rsp+10h] [rbp-470h] BYREF
  XinMoCfg stu; // [rsp+A0h] [rbp-3E0h] BYREF
  int iValue; // [rsp+D0h] [rbp-3B0h]
  XinQingCfg stu_0; // [rsp+E0h] [rbp-3A0h]
  Param2 Param; // [rsp+F0h] [rbp-390h] BYREF
  StringVector vParam; // [rsp+100h] [rbp-380h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+120h] [rbp-360h] BYREF
  StringVector strParams; // [rsp+130h] [rbp-350h] BYREF
  std::string RateString; // [rsp+150h] [rbp-330h] BYREF
  std::list<AddAttribute> __x; // [rsp+160h] [rbp-320h] BYREF
  _BYTE v31[15]; // [rsp+170h] [rbp-310h] BYREF
  char v32; // [rsp+17Fh] [rbp-301h] BYREF
  int32_t v33[3]; // [rsp+180h] [rbp-300h] BYREF
  char v34; // [rsp+18Fh] [rbp-2F1h] BYREF
  XinMoCfg p_Stu; // [rsp+190h] [rbp-2F0h] BYREF
  std::list<ItemData> strItems; // [rsp+1C0h] [rbp-2C0h] BYREF
  bool bCombi[15]; // [rsp+1D0h] [rbp-2B0h] BYREF
  char v38; // [rsp+1DFh] [rbp-2A1h] BYREF
  std::list<AddAttribute> v39; // [rsp+1E0h] [rbp-2A0h] BYREF
  _BYTE v40[15]; // [rsp+1F0h] [rbp-290h] BYREF
  char v41; // [rsp+1FFh] [rbp-281h] BYREF
  int32_t v42[3]; // [rsp+200h] [rbp-280h] BYREF
  char v43; // [rsp+20Fh] [rbp-271h] BYREF
  QiQingCfg v44; // [rsp+210h] [rbp-270h] BYREF
  std::list<ItemData> v45; // [rsp+240h] [rbp-240h] BYREF
  bool v46[14]; // [rsp+250h] [rbp-230h] BYREF
  char v47; // [rsp+25Eh] [rbp-222h] BYREF
  char v48; // [rsp+25Fh] [rbp-221h] BYREF
  std::string delims; // [rsp+260h] [rbp-220h] BYREF
  char v50; // [rsp+26Fh] [rbp-211h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+270h] [rbp-210h] BYREF
  std::string v52; // [rsp+280h] [rbp-200h] BYREF
  char v53; // [rsp+28Fh] [rbp-1F1h] BYREF
  EquipJinHua v54; // [rsp+290h] [rbp-1F0h] BYREF
  std::list<ItemData> v55; // [rsp+2C0h] [rbp-1C0h] BYREF
  bool v56[15]; // [rsp+2D0h] [rbp-1B0h] BYREF
  char v57; // [rsp+2DFh] [rbp-1A1h] BYREF
  std::list<AddAttribute> v58; // [rsp+2E0h] [rbp-1A0h] BYREF
  _BYTE v59[15]; // [rsp+2F0h] [rbp-190h] BYREF
  char v60; // [rsp+2FFh] [rbp-181h] BYREF
  int32_t v61[3]; // [rsp+300h] [rbp-180h] BYREF
  char v62; // [rsp+30Fh] [rbp-171h] BYREF
  XinMoQiQingLevelUpCfg v63; // [rsp+310h] [rbp-170h] BYREF
  MemChrBagVector v64; // [rsp+350h] [rbp-130h] BYREF
  std::string v65; // [rsp+370h] [rbp-110h] BYREF
  char v66; // [rsp+37Fh] [rbp-101h] BYREF
  XinQingReward p_stu; // [rsp+380h] [rbp-100h] BYREF
  Int32Vector v68; // [rsp+3A0h] [rbp-E0h] BYREF
  std::string path; // [rsp+3C0h] [rbp-C0h] BYREF
  char v70; // [rsp+3CFh] [rbp-B1h] BYREF
  std::string str; // [rsp+3D0h] [rbp-B0h] BYREF
  char v72; // [rsp+3E2h] [rbp-9Eh] BYREF
  int32_t iBaseTableCount; // [rsp+3E4h] [rbp-9Ch]
  int32_t iBaseColumnCount; // [rsp+3E8h] [rbp-98h]
  int32_t i; // [rsp+3ECh] [rbp-94h]
  int32_t nIndex; // [rsp+3F0h] [rbp-90h]
  int32_t iBaseTableCount_0; // [rsp+3F8h] [rbp-88h]
  int32_t iBaseColumnCount_0; // [rsp+3FCh] [rbp-84h]
  int32_t i_0; // [rsp+400h] [rbp-80h]
  int32_t nIndex_0; // [rsp+404h] [rbp-7Ch]
  int32_t iBaseTableCount_1; // [rsp+40Ch] [rbp-74h]
  int32_t iBaseColumnCount_1; // [rsp+410h] [rbp-70h]
  int32_t i_1; // [rsp+414h] [rbp-6Ch]
  int32_t nIndex_1; // [rsp+418h] [rbp-68h]
  int32_t iBaseTableCount_2; // [rsp+420h] [rbp-60h]
  int32_t iBaseColumnCount_2; // [rsp+424h] [rbp-5Ch]
  int32_t i_2; // [rsp+428h] [rbp-58h]
  int32_t nIndex_2; // [rsp+42Ch] [rbp-54h]
  int32_t iBaseTableCount_3; // [rsp+434h] [rbp-4Ch]
  int32_t iBaseColumnCount_3; // [rsp+438h] [rbp-48h]
  int32_t i_3; // [rsp+43Ch] [rbp-44h]
  int32_t nIndex_3; // [rsp+440h] [rbp-40h]
  int32_t iBaseTableCount_4; // [rsp+448h] [rbp-38h]
  int32_t iBaseColumnCount_4; // [rsp+44Ch] [rbp-34h]
  int32_t i_4; // [rsp+450h] [rbp-30h]
  int32_t nIndex_4; // [rsp+454h] [rbp-2Ch]
  int32_t nId; // [rsp+458h] [rbp-28h]
  int32_t iBaseTableCount_5; // [rsp+460h] [rbp-20h]
  int32_t iBaseColumnCount_5; // [rsp+464h] [rbp-1Ch]
  int32_t i_5; // [rsp+468h] [rbp-18h]
  int32_t nIndex_5; // [rsp+46Ch] [rbp-14h]

  CDBCFile::CDBCFile(&readFile, 0);
  if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XinMoLevel.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoL);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&readFile);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&readFile);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 44);
        std::list<AddAttribute>::list(&stu.Attr);
        stu.XinMoLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.CostMoney = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.ConstShenYaoBi = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.ConstExp = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        stu.NeedQiQingLevel = CDBCFile::Search_Posistion(&readFile, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v32);
        std::string::string(v31, "./ServerConfig/Tables/XinMoLevel.txt", &v32);
        std::allocator<char>::allocator(&v34);
        v2 = CDBCFile::Search_Posistion(&readFile, i, nIndex);
        std::string::string(v33, v2->pString, &v34);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v33,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.Attr, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v33);
        std::allocator<char>::~allocator(&v34);
        std::string::~string(v31);
        std::allocator<char>::~allocator(&v32);
        stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i, ++nIndex)->iValue;
        ++nIndex;
        XinMoCfg::XinMoCfg(&p_Stu, &stu);
        XinMoTable::AddXingMoCfg(&this->m_XinMoTable, &p_Stu);
        XinMoCfg::~XinMoCfg(&p_Stu);
        XinMoCfg::~XinMoCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&readFile);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&readFile, 0);
    if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XinMoQiQing.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoQ);
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&readFile);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&readFile);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, 44);
          std::list<ItemData>::list((std::list<ItemData> *const)&stu.ConstShenYaoBi);
          std::list<AddAttribute>::list(&stu.Attr);
          stu.XinMoLevel = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0++)->iValue;
          std::allocator<char>::allocator(&v38);
          v4 = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0);
          std::string::string(bCombi, v4->pString, &v38);
          CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
          std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.ConstShenYaoBi, &strItems);
          std::list<ItemData>::~list(&strItems);
          std::string::~string(bCombi);
          std::allocator<char>::~allocator(&v38);
          ++nIndex_0;
          std::allocator<char>::allocator(&v41);
          std::string::string(v40, "./ServerConfig/Tables/XinMoQiQing.txt", &v41);
          std::allocator<char>::allocator(&v43);
          v5 = CDBCFile::Search_Posistion(&readFile, i_0, nIndex_0);
          std::string::string(v42, v5->pString, &v43);
          CfgData::parseAddAttribues(
            (CfgData *const)&v39,
            (const std::string *const)this,
            (int32_t)v42,
            (const std::string *const)(unsigned int)nIndex_0);
          std::list<AddAttribute>::operator=(&stu.Attr, &v39);
          std::list<AddAttribute>::~list(&v39);
          std::string::~string(v42);
          std::allocator<char>::~allocator(&v43);
          std::string::~string(v40);
          std::allocator<char>::~allocator(&v41);
          stu.GongGaoId = CDBCFile::Search_Posistion(&readFile, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          QiQingCfg::QiQingCfg(&v44, (const QiQingCfg *const)&stu);
          XinMoTable::AddQiQingCfg(&this->m_XinMoTable, &v44);
          QiQingCfg::~QiQingCfg(&v44);
          QiQingCfg::~QiQingCfg((QiQingCfg *const)&stu);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    CDBCFile::~CDBCFile(&readFile);
    if ( v3 )
    {
      CDBCFile::CDBCFile(&readFile, 0);
      if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XinMoJingHua.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingMo);
        v6 = 0;
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&readFile);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&readFile);
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            memset(&stu, 0, 44);
            std::list<ItemData>::list((std::list<ItemData> *const)&stu.ConstShenYaoBi);
            std::list<Param2>::list((std::list<Param2> *const)&stu.Attr);
            stu.XinMoLevel = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1++)->iValue;
            std::allocator<char>::allocator(&v47);
            v7 = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1);
            std::string::string(v46, v7->pString, &v47);
            CItemHelper::parseItemDataListString((const std::string *const)&v45, (bool)v46);
            std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.ConstShenYaoBi, &v45);
            std::list<ItemData>::~list(&v45);
            std::string::~string(v46);
            std::allocator<char>::~allocator(&v47);
            ++nIndex_1;
            std::allocator<char>::allocator(&v48);
            v8 = CDBCFile::Search_Posistion(&readFile, i_1, nIndex_1);
            std::string::string(&RateString, v8->pString, &v48);
            std::allocator<char>::~allocator(&v48);
            ++nIndex_1;
            std::allocator<char>::allocator(&v50);
            std::string::string(&delims, "|", &v50);
            Answer::StringUtility::split(&strParams, &RateString, &delims, 0);
            std::string::~string(&delims);
            std::allocator<char>::~allocator(&v50);
            for ( iter._M_current = std::vector<std::string>::begin(&strParams)._M_current;
                  ;
                  __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
            {
              __rhs._M_current = std::vector<std::string>::end(&strParams)._M_current;
              if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
                break;
              std::allocator<char>::allocator(&v53);
              std::string::string(&v52, ":", &v53);
              v9 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
              Answer::StringUtility::split(&vParam, v9, &v52, 0);
              std::string::~string(&v52);
              std::allocator<char>::~allocator(&v53);
              if ( std::vector<std::string>::size(&vParam) == 2 )
              {
                Param2::Param2(&Param, 0, 0);
                v10 = std::vector<std::string>::operator[](&vParam, 0);
                v11 = (const char *)std::string::c_str(v10);
                Param.nParam1 = atoi(v11);
                v12 = std::vector<std::string>::operator[](&vParam, 1u);
                v13 = (const char *)std::string::c_str(v12);
                Param.nParam2 = atoi(v13);
                stu.GongGaoId += Param.nParam2;
                std::list<Param2>::push_back((std::list<Param2> *const)&stu.Attr, &Param);
              }
              std::vector<std::string>::~vector(&vParam);
            }
            EquipJinHua::EquipJinHua(&v54, (const EquipJinHua *const)&stu);
            XinMoTable::AddEquipJinHuaCfg(&this->m_XinMoTable, &v54);
            EquipJinHua::~EquipJinHua(&v54);
            std::vector<std::string>::~vector(&strParams);
            std::string::~string(&RateString);
            EquipJinHua::~EquipJinHua((EquipJinHua *const)&stu);
          }
          v6 = 1;
        }
        else
        {
          v6 = 0;
        }
      }
      CDBCFile::~CDBCFile(&readFile);
      if ( v6 )
      {
        CDBCFile::CDBCFile(&readFile, 0);
        if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/QiQingJinJie.txt") )
        {
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingMo_0);
          v14 = 0;
        }
        else
        {
          iBaseTableCount_2 = CDBCFile::GetRecordsNum(&readFile);
          iBaseColumnCount_2 = CDBCFile::GetFieldsNum(&readFile);
          if ( iBaseColumnCount_2 > 0 )
          {
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              nIndex_2 = 0;
              XinMoQiQingLevelUpCfg::XinMoQiQingLevelUpCfg((XinMoQiQingLevelUpCfg *const)&stu);
              stu.XinMoLevel = CDBCFile::Search_Posistion(&readFile, i_2, nIndex_2++)->iValue;
              stu.CostMoney = CDBCFile::Search_Posistion(&readFile, i_2, nIndex_2++)->iValue;
              std::allocator<char>::allocator(&v57);
              v15 = CDBCFile::Search_Posistion(&readFile, i_2, nIndex_2);
              std::string::string(v56, v15->pString, &v57);
              CItemHelper::parseItemDataListString((const std::string *const)&v55, (bool)v56);
              std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.ConstShenYaoBi, &v55);
              std::list<ItemData>::~list(&v55);
              std::string::~string(v56);
              std::allocator<char>::~allocator(&v57);
              LODWORD(stu.Attr._M_impl._M_node._M_next) = CDBCFile::Search_Posistion(&readFile, i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              std::allocator<char>::allocator(&v60);
              std::string::string(v59, "./ServerConfig/Tables/QiQingJinJie.txt", &v60);
              std::allocator<char>::allocator(&v62);
              v16 = CDBCFile::Search_Posistion(&readFile, i_2, nIndex_2);
              std::string::string(v61, v16->pString, &v62);
              CfgData::parseAddAttribues(
                (CfgData *const)&v58,
                (const std::string *const)this,
                (int32_t)v61,
                (const std::string *const)(unsigned int)nIndex_2);
              std::list<AddAttribute>::operator=(
                (std::list<AddAttribute> *const)&stu.Attr._M_impl._M_node._M_prev,
                &v58);
              std::list<AddAttribute>::~list(&v58);
              std::string::~string(v61);
              std::allocator<char>::~allocator(&v62);
              std::string::~string(v59);
              std::allocator<char>::~allocator(&v60);
              iValue = CDBCFile::Search_Posistion(&readFile, i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              XinMoQiQingLevelUpCfg::XinMoQiQingLevelUpCfg(&v63, (const XinMoQiQingLevelUpCfg *const)&stu);
              XinMoTable::AddXinMoQiQingLevelUpCfg(&this->m_XinMoTable, &v63);
              XinMoQiQingLevelUpCfg::~XinMoQiQingLevelUpCfg(&v63);
              XinMoQiQingLevelUpCfg::~XinMoQiQingLevelUpCfg((XinMoQiQingLevelUpCfg *const)&stu);
            }
            v14 = 1;
          }
          else
          {
            v14 = 0;
          }
        }
        CDBCFile::~CDBCFile(&readFile);
        if ( v14 )
        {
          CDBCFile::CDBCFile(&readFile, 0);
          if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XinQing.txt") )
          {
            Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingMo_0);
            v17 = 0;
          }
          else
          {
            iBaseTableCount_3 = CDBCFile::GetRecordsNum(&readFile);
            iBaseColumnCount_3 = CDBCFile::GetFieldsNum(&readFile);
            if ( iBaseColumnCount_3 > 0 )
            {
              for ( i_3 = 0; i_3 < iBaseTableCount_3; ++i_3 )
              {
                nIndex_3 = 0;
                stu_0.nLeftCount = CDBCFile::Search_Posistion(&readFile, i_3, 0)->iValue;
                stu_0.nAppearCount = CDBCFile::Search_Posistion(&readFile, i_3, ++nIndex_3)->iValue;
                stu_0.Rate = CDBCFile::Search_Posistion(&readFile, i_3, ++nIndex_3)->iValue;
                ++nIndex_3;
                XinMoTable::AddXinQingCfg(&this->m_XinMoTable, stu_0);
              }
              v17 = 1;
            }
            else
            {
              v17 = 0;
            }
          }
          CDBCFile::~CDBCFile(&readFile);
          if ( v17 )
          {
            CDBCFile::CDBCFile(&readFile, 0);
            if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/XinQingReward.txt") )
            {
              Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoX);
              v18 = 0;
            }
            else
            {
              iBaseTableCount_4 = CDBCFile::GetRecordsNum(&readFile);
              iBaseColumnCount_4 = CDBCFile::GetFieldsNum(&readFile);
              if ( iBaseColumnCount_4 > 0 )
              {
                for ( i_4 = 0; i_4 < iBaseTableCount_4; ++i_4 )
                {
                  nIndex_4 = 0;
                  nId = CDBCFile::Search_Posistion(&readFile, i_4, 0)->iValue;
                  ++nIndex_4;
                  memset(&stu, 0, 32);
                  std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.ConstShenYaoBi);
                  std::allocator<char>::allocator(&v66);
                  v19 = CDBCFile::Search_Posistion(&readFile, i_4, nIndex_4);
                  std::string::string(&v65, v19->pString, &v66);
                  CItemHelper::parseItemVectorString(&v64, &v65);
                  std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.ConstShenYaoBi, &v64);
                  std::vector<MemChrBag>::~vector(&v64);
                  std::string::~string(&v65);
                  std::allocator<char>::~allocator(&v66);
                  stu.XinMoLevel = CDBCFile::Search_Posistion(&readFile, i_4, ++nIndex_4)->iValue;
                  ++nIndex_4;
                  XinQingReward::XinQingReward(&p_stu, (const XinQingReward *const)&stu);
                  XinMoTable::AddXinQingReward(&this->m_XinMoTable, nId, &p_stu);
                  XinQingReward::~XinQingReward(&p_stu);
                  XinQingReward::~XinQingReward((XinQingReward *const)&stu);
                }
                v18 = 1;
              }
              else
              {
                v18 = 0;
              }
            }
            CDBCFile::~CDBCFile(&readFile);
            if ( v18 )
            {
              CDBCFile::CDBCFile(&readFile, 0);
              if ( !CDBCFile::OpenFromTXT(&readFile, "./ServerConfig/Tables/Energy.txt") )
              {
                Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEnergy);
              }
              else
              {
                iBaseTableCount_5 = CDBCFile::GetRecordsNum(&readFile);
                iBaseColumnCount_5 = CDBCFile::GetFieldsNum(&readFile);
                if ( iBaseColumnCount_5 > 0 )
                {
                  for ( i_5 = 0; i_5 < iBaseTableCount_5; ++i_5 )
                  {
                    nIndex_5 = 1;
                    this->m_EnergyCfg.MaxEnergy = CDBCFile::Search_Posistion(&readFile, i_5, 1)->iValue;
                    this->m_EnergyCfg.EnergyTime = CDBCFile::Search_Posistion(&readFile, i_5, ++nIndex_5)->iValue;
                    ++nIndex_5;
                    std::allocator<char>::allocator(&v70);
                    std::string::string(&path, "./ServerConfig/Tables/Energy.txt", &v70);
                    std::allocator<char>::allocator(&v72);
                    v20 = CDBCFile::Search_Posistion(&readFile, i_5, nIndex_5);
                    std::string::string(&str, v20->pString, &v72);
                    CfgData::paraseInt32Vector2(&v68, this, &str, &path, 0);
                    std::vector<int>::operator=(&this->m_EnergyCfg.EnergyPrice, &v68);
                    std::vector<int>::~vector(&v68);
                    std::string::~string(&str);
                    std::allocator<char>::~allocator(&v72);
                    std::string::~string(&path);
                    std::allocator<char>::~allocator(&v70);
                    this->m_EnergyCfg.BuyAddEnergy = CDBCFile::Search_Posistion(&readFile, i_5, ++nIndex_5)->iValue;
                    ++nIndex_5;
                  }
                }
              }
              CDBCFile::~CDBCFile(&readFile);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CfgData::InitLittleHelperCfg(CfgData *const this)
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  LittleHelperCfg *v3; // rax
  int v4; // ebx
  ShiQuCfg *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  CDBCFile FileTable; // [rsp+10h] [rbp-190h] BYREF
  LittleHelperCfg stu; // [rsp+A0h] [rbp-100h] BYREF
  ShiQuCfg stu_0; // [rsp+D0h] [rbp-D0h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-B0h] BYREF
  _BYTE v11[15]; // [rsp+100h] [rbp-A0h] BYREF
  char v12; // [rsp+10Fh] [rbp-91h] BYREF
  int32_t v13[3]; // [rsp+110h] [rbp-90h] BYREF
  char v14; // [rsp+11Fh] [rbp-81h] BYREF
  MemChrBagVector v15; // [rsp+120h] [rbp-80h] BYREF
  std::string strItems; // [rsp+140h] [rbp-60h] BYREF
  char v17; // [rsp+156h] [rbp-4Ah] BYREF
  int32_t iBaseTableCount; // [rsp+158h] [rbp-48h]
  int32_t iBaseColumnCount; // [rsp+15Ch] [rbp-44h]
  int32_t i; // [rsp+160h] [rbp-40h]
  int32_t nIndex; // [rsp+164h] [rbp-3Ch]
  int32_t iBaseTableCount_0; // [rsp+16Ch] [rbp-34h]
  int32_t iBaseColumnCount_0; // [rsp+170h] [rbp-30h]
  int32_t i_0; // [rsp+174h] [rbp-2Ch]
  int32_t nIndex_0; // [rsp+178h] [rbp-28h]
  int32_t iBaseTableCount_1; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount_1; // [rsp+184h] [rbp-1Ch]
  int32_t i_1; // [rsp+188h] [rbp-18h]
  int32_t nIndex_1; // [rsp+18Ch] [rbp-14h]

  CDBCFile::CDBCFile(&FileTable, 0);
  if ( !CDBCFile::OpenFromTXT(&FileTable, "./ServerConfig/Tables/LittleHelper.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_LITTLE_HELPER_CFG_TABLE.txt failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&FileTable);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&FileTable);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        LittleHelperCfg::LittleHelperCfg(&stu);
        stu.nId = CDBCFile::Search_Posistion(&FileTable, i, nIndex++)->iValue;
        nIndex += 3;
        stu.nSpeed = CDBCFile::Search_Posistion(&FileTable, i, nIndex++)->iValue;
        nIndex += 2;
        std::allocator<char>::allocator(&v12);
        std::string::string(v11, "./ServerConfig/Tables/LittleHelper.txt", &v12);
        std::allocator<char>::allocator(&v14);
        v2 = CDBCFile::Search_Posistion(&FileTable, i, nIndex);
        std::string::string(v13, v2->pString, &v14);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v13,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttr, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v13);
        std::allocator<char>::~allocator(&v14);
        std::string::~string(v11);
        std::allocator<char>::~allocator(&v12);
        stu.nGold = CDBCFile::Search_Posistion(&FileTable, i, ++nIndex)->iValue;
        stu.nReGold = CDBCFile::Search_Posistion(&FileTable, i, ++nIndex)->iValue;
        stu.nTime = CDBCFile::Search_Posistion(&FileTable, i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 5;
        stu.nGongGaoId = CDBCFile::Search_Posistion(&FileTable, i, nIndex++)->iValue;
        v3 = std::map<int,LittleHelperCfg>::operator[](&this->m_LittleHelperCfgMap, &stu.nId);
        LittleHelperCfg::operator=(v3, &stu);
        LittleHelperCfg::~LittleHelperCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&FileTable);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&FileTable, 0);
    if ( !CDBCFile::OpenFromTXT(&FileTable, "./ServerConfig/Tables/ShieldItem.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SHI_QU_TABLE.txt failed,please check!!");
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&FileTable);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&FileTable);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          stu_0.nId = CDBCFile::Search_Posistion(&FileTable, i_0, 0)->iValue;
          stu_0.nItemId = CDBCFile::Search_Posistion(&FileTable, i_0, ++nIndex_0)->iValue;
          stu_0.nType = CDBCFile::Search_Posistion(&FileTable, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          stu_0.nMinGrade = CDBCFile::Search_Posistion(&FileTable, i_0, ++nIndex_0)->iValue;
          stu_0.nMaxGrade = CDBCFile::Search_Posistion(&FileTable, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          v5 = std::map<int,ShiQuCfg>::operator[](&this->m_ShiQuCfgMap, &stu_0.nId);
          *v5 = stu_0;
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    CDBCFile::~CDBCFile(&FileTable);
    if ( v4 )
    {
      CDBCFile::CDBCFile(&FileTable, 0);
      if ( !CDBCFile::OpenFromTXT(&FileTable, "./ServerConfig/Tables/ZeroBuyPet.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_ZERO_BUY_PET_TABLE.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_1 = CDBCFile::GetRecordsNum(&FileTable);
        iBaseColumnCount_1 = CDBCFile::GetFieldsNum(&FileTable);
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 2;
            this->m_ZeroBuyPetCfg.nTime = CDBCFile::Search_Posistion(&FileTable, i_1, 2)->iValue;
            ++nIndex_1;
            std::allocator<char>::allocator(&v17);
            v6 = CDBCFile::Search_Posistion(&FileTable, i_1, nIndex_1);
            std::string::string(&strItems, v6->pString, &v17);
            CItemHelper::parseItemVectorString(&v15, &strItems);
            std::vector<MemChrBag>::operator=(&this->m_ZeroBuyPetCfg.cItems, &v15);
            std::vector<MemChrBag>::~vector(&v15);
            std::string::~string(&strItems);
            std::allocator<char>::~allocator(&v17);
            this->m_ZeroBuyPetCfg.nGold = CDBCFile::Search_Posistion(&FileTable, i_1, ++nIndex_1)->iValue;
            this->m_ZeroBuyPetCfg.nMailId = CDBCFile::Search_Posistion(&FileTable, i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
          }
        }
      }
      CDBCFile::~CDBCFile(&FileTable);
    }
  }
}


#####################################
void __cdecl CfgData::InitShiZhuLevelUp(CfgData *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  ShiZhuLevelUp *v3; // rax
  CDBCFile FileTable; // [rsp+10h] [rbp-140h] BYREF
  ShiZhuLevelUp stu; // [rsp+A0h] [rbp-B0h] BYREF
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-80h] BYREF
  bool bCombi[15]; // [rsp+E0h] [rbp-70h] BYREF
  char v8; // [rsp+EFh] [rbp-61h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-60h] BYREF
  _BYTE v10[15]; // [rsp+100h] [rbp-50h] BYREF
  char v11; // [rsp+10Fh] [rbp-41h] BYREF
  int32_t v12[3]; // [rsp+110h] [rbp-40h] BYREF
  char v13; // [rsp+11Fh] [rbp-31h] BYREF
  std::pair<int,int> __k; // [rsp+120h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]

  CDBCFile::CDBCFile(&FileTable, 0);
  if ( !CDBCFile::OpenFromTXT(&FileTable, "./ServerConfig/Tables/ShiZhuangUpGrade.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_SHI_ZHUANG_LEVEL_UP_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&FileTable);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&FileTable);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        ShiZhuLevelUp::ShiZhuLevelUp(&stu);
        stu.nId = CDBCFile::Search_Posistion(&FileTable, i, nIndex++)->iValue;
        stu.nLevel = CDBCFile::Search_Posistion(&FileTable, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v8);
        v1 = CDBCFile::Search_Posistion(&FileTable, i, nIndex);
        std::string::string(bCombi, v1->pString, &v8);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lCostItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        std::string::~string(bCombi);
        std::allocator<char>::~allocator(&v8);
        ++nIndex;
        std::allocator<char>::allocator(&v11);
        std::string::string(v10, "./ServerConfig/Tables/ShiZhuangUpGrade.txt", &v11);
        std::allocator<char>::allocator(&v13);
        v2 = CDBCFile::Search_Posistion(&FileTable, i, nIndex);
        std::string::string(v12, v2->pString, &v13);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v12,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttr, &__x);
        std::list<AddAttribute>::~list(&__x);
        std::string::~string(v12);
        std::allocator<char>::~allocator(&v13);
        std::string::~string(v10);
        std::allocator<char>::~allocator(&v11);
        ++nIndex;
        __k = std::make_pair<int,int>(stu.nId, stu.nLevel);
        v3 = std::map<std::pair<int,int>,ShiZhuLevelUp>::operator[](&this->m_ShiZhuLevelUpMap, &__k);
        ShiZhuLevelUp::operator=(v3, &stu);
        ShiZhuLevelUp::~ShiZhuLevelUp(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&FileTable);
}


#####################################
void __cdecl CfgData::InitNationalDayTask(CfgData *const this)
{
  int v1; // ebx
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,NationalDayTaskCfg> >,bool> v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  NationalDayLevelCfg *v5; // rax
  MemChrBag v6; // [rsp+0h] [rbp-230h] BYREF
  std::_Rb_tree_node_base::_Base_ptr M_node; // [rsp+20h] [rbp-210h]
  int v8; // [rsp+28h] [rbp-208h]
  CfgData *thisa; // [rsp+38h] [rbp-1F8h]
  CDBCFile FileTable_0; // [rsp+40h] [rbp-1F0h] BYREF
  NationalDayLevelCfg stu_0; // [rsp+D0h] [rbp-160h] BYREF
  NationalDayTaskCfg stu; // [rsp+160h] [rbp-D0h] BYREF
  std::_Rb_tree_node_base::_Base_ptr v13; // [rsp+180h] [rbp-B0h]
  bool second; // [rsp+188h] [rbp-A8h]
  _BYTE v15[32]; // [rsp+190h] [rbp-A0h] BYREF
  std::pair<int,int> __a; // [rsp+1B0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+1C0h] [rbp-70h] BYREF
  std::string strItems; // [rsp+1E0h] [rbp-50h] BYREF
  char v19; // [rsp+1EFh] [rbp-41h] BYREF
  std::string strItem; // [rsp+1F0h] [rbp-40h] BYREF
  char v21; // [rsp+1FAh] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+1FCh] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+200h] [rbp-30h]
  int32_t i; // [rsp+204h] [rbp-2Ch]
  int32_t nIndex; // [rsp+208h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+210h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+214h] [rbp-1Ch]
  int32_t i_0; // [rsp+218h] [rbp-18h]
  int32_t nIndex_0; // [rsp+21Ch] [rbp-14h]

  thisa = this;
  CDBCFile::CDBCFile((CDBCFile *const)&stu_0, 0);
  if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_0, "./ServerConfig/Tables/PassportTask.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MO_SHEN_JIANG_LING_TABLE.txt failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum((const CDBCFile *const)&stu_0);
    iBaseColumnCount = CDBCFile::GetFieldsNum((const CDBCFile *const)&stu_0);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nType = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, 0)->iValue;
        stu.nId = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.nParam = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.nNeedValue = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.nSocre = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(stu.nType, stu.nId);
        std::pair<std::pair const<int,int>,NationalDayTaskCfg>::pair(
          (std::pair<const std::pair<int,int>,NationalDayTaskCfg> *const)v15,
          &__a,
          &stu);
        v2 = std::map<std::pair<int,int>,NationalDayTaskCfg>::insert(
               &thisa->m_NationalDayTaskCfgMap,
               (const std::pair<const std::pair<int,int>,NationalDayTaskCfg> *const)v15);
        M_node = v2.first._M_node;
        v8 = *(_DWORD *)&v2.second;
        v13 = v2.first._M_node;
        second = v2.second;
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile((CDBCFile *const)&stu_0);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&FileTable_0, 0);
    if ( !CDBCFile::OpenFromTXT(&FileTable_0, "./ServerConfig/Tables/Passport.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_MO_SHEN_JIANG_LING_TABLE.txt failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&FileTable_0);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&FileTable_0);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu_0, 0, 76);
          std::vector<MemChrBag>::vector(&stu_0.vGeneralReward);
          stu_0.nLevel = CDBCFile::Search_Posistion(&FileTable_0, i_0, nIndex_0++)->iValue;
          stu_0.nScore = CDBCFile::Search_Posistion(&FileTable_0, i_0, nIndex_0++)->iValue;
          std::allocator<char>::allocator(&v19);
          v3 = CDBCFile::Search_Posistion(&FileTable_0, i_0, nIndex_0);
          std::string::string(&strItems, v3->pString, &v19);
          CItemHelper::parseItemVectorString(&__x, &strItems);
          std::vector<MemChrBag>::operator=(&stu_0.vGeneralReward, &__x);
          std::vector<MemChrBag>::~vector(&__x);
          std::string::~string(&strItems);
          std::allocator<char>::~allocator(&v19);
          ++nIndex_0;
          std::allocator<char>::allocator(&v21);
          v4 = CDBCFile::Search_Posistion(&FileTable_0, i_0, nIndex_0);
          std::string::string(&strItem, v4->pString, &v21);
          CItemHelper::parseItemString(&v6, &strItem);
          stu_0.vSeniorReward = v6;
          std::string::~string(&strItem);
          std::allocator<char>::~allocator(&v21);
          stu_0.nBuyCost = CDBCFile::Search_Posistion(&FileTable_0, i_0, ++nIndex_0)->iValue;
          stu_0.nUnlockCost = CDBCFile::Search_Posistion(&FileTable_0, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          stu_0.nGongGaoId = CDBCFile::Search_Posistion(&FileTable_0, i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          v5 = std::map<int,NationalDayLevelCfg>::operator[](&thisa->m_NationalDayLevelCfgMap, &stu_0.nLevel);
          NationalDayLevelCfg::operator=(v5, &stu_0);
          NationalDayLevelCfg::~NationalDayLevelCfg(&stu_0);
        }
      }
    }
    CDBCFile::~CDBCFile(&FileTable_0);
  }
}


#####################################
void __cdecl CfgData::InitRongHeCfg(CfgData *const this)
{
  int v1; // ebx
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
  RongHeCfg *v23; // rax
  EquipRongHe *v24; // rax
  __int64 v25; // rax
  CDBCFile FileTable; // [rsp+10h] [rbp-1D0h] BYREF
  RongHeItem RongHe; // [rsp+A0h] [rbp-140h] BYREF
  RongHeCfg stu; // [rsp+E0h] [rbp-100h] BYREF
  EquipRongHe stu_0; // [rsp+110h] [rbp-D0h] BYREF
  StringVector tv; // [rsp+120h] [rbp-C0h] BYREF
  StringVector vStr; // [rsp+140h] [rbp-A0h] BYREF
  std::string RongHeString; // [rsp+160h] [rbp-80h] BYREF
  std::string strItem; // [rsp+170h] [rbp-70h] BYREF
  char v34; // [rsp+17Eh] [rbp-62h] BYREF
  char v35; // [rsp+17Fh] [rbp-61h] BYREF
  std::string delims; // [rsp+180h] [rbp-60h] BYREF
  char v37; // [rsp+18Fh] [rbp-51h] BYREF
  std::string v38; // [rsp+190h] [rbp-50h] BYREF
  char v39; // [rsp+1A2h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+1A4h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+1A8h] [rbp-38h]
  int32_t i; // [rsp+1ACh] [rbp-34h]
  int32_t nIndex; // [rsp+1B0h] [rbp-30h]
  int32_t isize; // [rsp+1B4h] [rbp-2Ch]
  int32_t i_0; // [rsp+1B8h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+1C0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+1C4h] [rbp-1Ch]
  int32_t i_1; // [rsp+1C8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+1CCh] [rbp-14h]
  ItemData v52; // 0:kr00_12.12

  CDBCFile::CDBCFile(&FileTable, 0);
  if ( !CDBCFile::OpenFromTXT(&FileTable, "./ServerConfig/Tables/ItemMix.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_RONG_HE_TABLE.txt failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&FileTable);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&FileTable);
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<RongHeItem>::list(&stu.lRongHeItemList);
        stu.nId = CDBCFile::Search_Posistion(&FileTable, i, nIndex++)->iValue;
        std::allocator<char>::allocator(&v34);
        v2 = CDBCFile::Search_Posistion(&FileTable, i, nIndex);
        std::string::string(&strItem, v2->pString, &v34);
        v52 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v25) = v52.m_nId;
        BYTE4(v25) = v52.m_nClass;
        *(_QWORD *)&stu.nCostItem.m_nId = v25;
        stu.nCostItem.m_nCount = v52.m_nCount;
        std::string::~string(&strItem);
        std::allocator<char>::~allocator(&v34);
        ++nIndex;
        std::allocator<char>::allocator(&v35);
        v3 = CDBCFile::Search_Posistion(&FileTable, i, nIndex);
        std::string::string(&RongHeString, v3->pString, &v35);
        std::allocator<char>::~allocator(&v35);
        ++nIndex;
        std::allocator<char>::allocator(&v37);
        std::string::string(&delims, "|", &v37);
        Answer::StringUtility::split(&vStr, &RongHeString, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v37);
        isize = std::vector<std::string>::size(&vStr);
        for ( i_0 = 0; i_0 < isize; ++i_0 )
        {
          std::allocator<char>::allocator(&v39);
          std::string::string(&v38, ":", &v39);
          v4 = std::vector<std::string>::operator[](&vStr, i_0);
          Answer::StringUtility::split(&tv, v4, &v38, 0);
          std::string::~string(&v38);
          std::allocator<char>::~allocator(&v39);
          if ( std::vector<std::string>::size(&tv) == 9 )
          {
            memset(&RongHe, 0, sizeof(RongHe));
            v5 = std::vector<std::string>::operator[](&tv, 0);
            v6 = (const char *)std::string::c_str(v5);
            RongHe.item.itemId = atoi(v6);
            v7 = std::vector<std::string>::operator[](&tv, 1u);
            v8 = (const char *)std::string::c_str(v7);
            RongHe.item.itemClass = atoi(v8);
            v9 = std::vector<std::string>::operator[](&tv, 2u);
            v10 = (const char *)std::string::c_str(v9);
            RongHe.item.itemCount = atoi(v10);
            v11 = std::vector<std::string>::operator[](&tv, 3u);
            v12 = (const char *)std::string::c_str(v11);
            RongHe.item.bind = atoi(v12);
            v13 = std::vector<std::string>::operator[](&tv, 4u);
            v14 = (const char *)std::string::c_str(v13);
            RongHe.nRate = atoi(v14);
            v15 = std::vector<std::string>::operator[](&tv, 5u);
            v16 = (const char *)std::string::c_str(v15);
            RongHe.nRate2 = atoi(v16);
            v17 = std::vector<std::string>::operator[](&tv, 6u);
            v18 = (const char *)std::string::c_str(v17);
            RongHe.nGongGaoId = atoi(v18);
            v19 = std::vector<std::string>::operator[](&tv, 7u);
            v20 = (const char *)std::string::c_str(v19);
            RongHe.nSuccess = atoi(v20);
            v21 = std::vector<std::string>::operator[](&tv, 8u);
            v22 = (const char *)std::string::c_str(v21);
            RongHe.nRecord = atoi(v22);
            stu.nMaxRate += RongHe.nRate;
            stu.nMaxRate2 += RongHe.nRate2;
            std::list<RongHeItem>::push_back(&stu.lRongHeItemList, &RongHe);
          }
          std::vector<std::string>::~vector(&tv);
        }
        v23 = std::map<int,RongHeCfg>::operator[](&this->m_RongHeCfgMap, &stu.nId);
        RongHeCfg::operator=(v23, &stu);
        std::vector<std::string>::~vector(&vStr);
        std::string::~string(&RongHeString);
        RongHeCfg::~RongHeCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  CDBCFile::~CDBCFile(&FileTable);
  if ( v1 )
  {
    CDBCFile::CDBCFile(&FileTable, 0);
    if ( !CDBCFile::OpenFromTXT(&FileTable, "./ServerConfig/Tables/MixGem.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_RONG_HE_EQUIP_TABLE.txt failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = CDBCFile::GetRecordsNum(&FileTable);
      iBaseColumnCount_0 = CDBCFile::GetFieldsNum(&FileTable);
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_1 = 0; i_1 < iBaseTableCount_0; ++i_1 )
        {
          nIndex_0 = 0;
          *(_QWORD *)&stu_0.nItemId = 0;
          stu_0.nAttrRate = 0;
          stu_0.nItemId = CDBCFile::Search_Posistion(&FileTable, i_1, 0)->iValue;
          stu_0.nMaxEquip = CDBCFile::Search_Posistion(&FileTable, i_1, ++nIndex_0)->iValue;
          stu_0.nAttrRate = CDBCFile::Search_Posistion(&FileTable, i_1, ++nIndex_0)->iValue;
          ++nIndex_0;
          v24 = std::map<int,EquipRongHe>::operator[](&this->m_EquipRongHeMap, &stu_0.nItemId);
          *v24 = stu_0;
        }
      }
    }
    CDBCFile::~CDBCFile(&FileTable);
  }
}


