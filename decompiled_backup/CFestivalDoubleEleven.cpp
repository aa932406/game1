// Decompiled methods for class: CFestivalDoubleEleven
// Source: gameserver.cc
// Total methods: 136

#####################################
void __cdecl CFestivalDoubleEleven::OnDaySwitch(CFestivalDoubleEleven *const this)
{
  CTimer *v1; // rax
  int v2; // ebx
  int nowTime; // [rsp+1Ch] [rbp-14h]

  v1 = Answer::Singleton<CTimer>::instance();
  nowTime = CTimer::GetNow(v1);
  v2 = Answer::DayTime::dayzero(nowTime);
  this->m_nDay = (v2 - Answer::DayTime::dayzero(this->m_nStartDay)) / 86400;
  if ( this->m_nDay == this->m_nIconHideDay )
    CFestivalDoubleEleven::hideIcon(this, this->m_nIcon);
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE)
    && (this->m_nDay == this->m_vStartDay[14] || this->m_nDay == this->m_vEndDay[14]) )
  {
    CFestivalDoubleEleven::BroadCastMoYuShiJieIconState(this);
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE)
    && this->m_nDay == this->m_vEndDay[2] )
  {
    CFestivalDoubleEleven::hideIcon(this, 52);
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK) && this->m_nDay == this->m_vEndDay[4] )
    CFestivalDoubleEleven::sendDrawRankMail(this);
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK)
    && this->m_nDay == this->m_vEndDay[16] )
  {
    CFestivalDoubleEleven::sendXiaoFeiSumRankMail(this);
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
    CFestivalDoubleEleven::sendXiaoFeiRankMail(this);
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK)
    && this->m_nDay == this->m_vEndDay[32] )
  {
    CFestivalDoubleEleven::sendRechargeSumRankMail(this);
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK)
    && this->m_nDay == this->m_vEndDay[43] )
  {
    CFestivalDoubleEleven::sendBossScoreRankMail(this);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::OnNewMinute(CFestivalDoubleEleven *const this, int32_t nMinute)
{
  this->m_nMinute = nMinute;
  CFestivalDoubleEleven::HotUpdate(this);
  if ( CFestivalDoubleEleven::IsInTime(this) )
  {
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK) )
      CFestivalDoubleEleven::checkDrawRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_WORLD_BOSS) )
      CFestivalDoubleEleven::checkWorldBoss(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
      CFestivalDoubleEleven::checkXiaoFeiRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK) )
      CFestivalDoubleEleven::checkXiaoFeiSumRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP) )
      CFestivalDoubleEleven::checkRefreshMysteryShop(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK) )
      CFestivalDoubleEleven::checkRechargeSumRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK) )
      CFestivalDoubleEleven::checkCrossRechargeSumRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK) )
      CFestivalDoubleEleven::checkCrossXiaoFeiSumRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_CHOU_JIANG_RANK) )
      CFestivalDoubleEleven::checkCrossChouJiangRank(this);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK) )
      CFestivalDoubleEleven::checkBossScoreRank(this);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::Init(CFestivalDoubleEleven *const this, int32_t line)
{
  CTimer *v2; // rax
  tm nowTime; // [rsp+10h] [rbp-40h] BYREF
  int32_t nVersion; // [rsp+4Ch] [rbp-4h]

  CFestivalDoubleEleven::initCfgData(this);
  nVersion = CFestivalDoubleEleven::loadVersion(this, line);
  if ( nVersion <= 0 || this->m_nVersion == nVersion )
  {
    CFestivalDoubleEleven::loadRankData(this, line);
    if ( !nVersion )
      CFestivalDoubleEleven::saveVersion(this, line);
  }
  else
  {
    CFestivalDoubleEleven::resetRankData(this, line);
    CFestivalDoubleEleven::saveVersion(this, line);
  }
  v2 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&nowTime, v2);
  this->m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
}


#####################################
void __cdecl CFestivalDoubleEleven::initOpenList(CFestivalDoubleEleven *const this, const std::string *const str)
{
  std::string *v2; // rax
  const char *v3; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+10h] [rbp-60h] BYREF
  StringVector vOpen; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  char v7; // [rsp+4Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+50h] [rbp-20h] BYREF
  int8_t nType; // [rsp+5Fh] [rbp-11h]

  bzero(this->m_vOpen, 0x2Fu);
  std::allocator<char>::allocator(&v7);
  std::string::string(&delims, "|", &v7);
  Answer::StringUtility::split(&vOpen, str, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v7);
  for ( iter._M_current = std::vector<std::string>::begin(&vOpen)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<std::string>::end(&vOpen)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
      break;
    v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
    v3 = (const char *)std::string::c_str(v2);
    nType = atoi(v3);
    if ( nType > 0 && nType <= 46 )
      this->m_vOpen[nType] = 1;
  }
  std::vector<std::string>::~vector(&vOpen);
}


#####################################
void __cdecl CFestivalDoubleEleven::HotUpdate(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  char szCol[64]; // [rsp+10h] [rbp-D0h] BYREF
  Answer::Inifile ini; // [rsp+50h] [rbp-90h] BYREF
  std::string file; // [rsp+90h] [rbp-50h] BYREF
  char v5; // [rsp+9Fh] [rbp-41h] BYREF
  std::string key; // [rsp+A0h] [rbp-40h] BYREF
  char v7; // [rsp+AFh] [rbp-31h] BYREF
  std::string section; // [rsp+B0h] [rbp-30h] BYREF
  char v9; // [rsp+C3h] [rbp-1Dh] BYREF
  int32_t nHotSign; // [rsp+C4h] [rbp-1Ch]
  int32_t nOldVersion; // [rsp+C8h] [rbp-18h]
  int32_t line; // [rsp+CCh] [rbp-14h]

  Answer::Inifile::Inifile(&ini);
  std::allocator<char>::allocator(&v5);
  std::string::string(&file, "./ServerConfig/Tables/FestivalDoubleEleven.cfg", &v5);
  Answer::Inifile::parse(&ini, &file);
  std::string::~string(&file);
  std::allocator<char>::~allocator(&v5);
  memset(szCol, 0, sizeof(szCol));
  std::allocator<char>::allocator(&v7);
  std::string::string(&key, "hot_sign", &v7);
  std::allocator<char>::allocator(&v9);
  std::string::string(&section, "CONFIG", &v9);
  nHotSign = Answer::Inifile::getIntValue(&ini, &section, &key);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v9);
  std::string::~string(&key);
  std::allocator<char>::~allocator(&v7);
  if ( this->m_nHotSign < nHotSign )
  {
    nOldVersion = this->m_nVersion;
    v1 = Answer::Singleton<GameService>::instance();
    line = GameService::getLine(v1);
    CFestivalDoubleEleven::initCfgData(this);
    if ( this->m_nVersion != nOldVersion )
    {
      CFestivalDoubleEleven::saveVersion(this, line);
      CFestivalDoubleEleven::resetRankData(this, line);
      CFestivalDoubleEleven::resetPlayerData(this);
    }
  }
  Answer::Inifile::~Inifile(&ini);
}


#####################################
void __cdecl CFestivalDoubleEleven::initCfgData(CFestivalDoubleEleven *const this)
{
  int32_t v1; // eax
  int v2; // ebx
  std::vector<MemChrBag> *v3; // rax
  int *v4; // rbx
  std::vector<MemChrBag> *v5; // rax
  TimeArea *v6; // rbx
  TimeArea *v7; // rbx
  int *v8; // rbx
  std::vector<MemChrBag> *v9; // rax
  std::vector<MemChrBag> *v10; // rax
  int *v11; // rbx
  int *v12; // rbx
  std::vector<MemChrBag> *v13; // rax
  std::vector<MemChrBag> *v14; // rax
  int *v15; // rbx
  int *v16; // rbx
  std::vector<MemChrBag> *v17; // rax
  int *v18; // rbx
  std::vector<MemChrBag> *v19; // rax
  size_t m_nGiftShopSize; // rbx
  std::vector<ShopGoods> *v21; // rax
  size_t v22; // rbx
  std::vector<ShopGoods> *v23; // rax
  ShopGoods *v24; // rbx
  size_t v25; // rbx
  std::vector<ShopGoods> *v26; // rax
  ShopGoods *v27; // rax
  int *v28; // rbx
  MemChrBag *v29; // rbx
  int v30; // eax
  int v31; // eax
  int32_t v32; // eax
  CFestivalDoubleEleven *v33; // rbx
  int v34; // eax
  int v35; // eax
  int32_t v36; // eax
  int *v37; // rbx
  std::vector<MemChrBag> *v38; // rax
  int *v39; // rbx
  int v40; // eax
  int v41; // eax
  int32_t v42; // eax
  int *v43; // rbx
  std::vector<MemChrBag> *v44; // rax
  int *v45; // rbx
  int v46; // eax
  int v47; // eax
  int32_t v48; // eax
  int v49; // eax
  int v50; // eax
  int32_t v51; // eax
  int *v52; // rbx
  std::vector<MemChrBag> *v53; // rax
  int v54; // eax
  int v55; // eax
  int32_t v56; // eax
  ShopGoods *v57; // rbx
  ShopGoods *v58; // rax
  int *v59; // rbx
  int v60; // eax
  int v61; // eax
  int32_t v62; // eax
  int32_t v63; // eax
  int *v64; // rax
  int v65; // eax
  int v66; // eax
  int32_t v67; // eax
  int v68; // eax
  int v69; // eax
  int32_t v70; // eax
  int *v71; // rbx
  int *v72; // rbx
  std::vector<MemChrBag> *v73; // rax
  int v74; // eax
  int v75; // eax
  int32_t v76; // eax
  int *v77; // rbx
  int *v78; // rbx
  int v79; // eax
  int v80; // eax
  int32_t v81; // eax
  int v82; // eax
  int v83; // eax
  int32_t v84; // eax
  int *v85; // rbx
  std::vector<MemChrBag> *v86; // rax
  int v87; // eax
  int v88; // eax
  int32_t v89; // eax
  int *v90; // rbx
  int *v91; // rbx
  std::vector<MemChrBag> *v92; // rax
  int v93; // eax
  int v94; // eax
  int32_t v95; // eax
  int *v96; // rbx
  int *v97; // rbx
  std::vector<MemChrBag> *v98; // rax
  int v99; // eax
  int v100; // eax
  int32_t v101; // eax
  int *v102; // rbx
  int *v103; // rbx
  std::vector<MemChrBag> *v104; // rax
  int v105; // eax
  int v106; // eax
  int v107; // eax
  int v108; // eax
  int32_t v109; // eax
  int *v110; // rbx
  int *v111; // rbx
  std::vector<MemChrBag> *v112; // rax
  int v113; // eax
  int v114; // eax
  int32_t v115; // eax
  int *v116; // rbx
  std::vector<MemChrBag> *v117; // rax
  int v118; // eax
  int v119; // eax
  int32_t v120; // eax
  int *v121; // rbx
  std::vector<MemChrBag> *v122; // rax
  int v123; // eax
  int v124; // eax
  int v125; // eax
  int v126; // eax
  int32_t v127; // eax
  int32_t v128; // eax
  int *v129; // rbx
  std::vector<MemChrBag> *v130; // rax
  int32_t v131; // eax
  int *v132; // rbx
  int *v133; // rbx
  std::vector<MemChrBag> *v134; // rax
  int v135; // eax
  int v136; // eax
  int32_t v137; // eax
  int *v138; // rbx
  int32_t v139; // eax
  int *v140; // rbx
  int32_t v141; // eax
  RateItem *v142; // rbx
  __int64 v143; // rax
  int v144; // eax
  int v145; // eax
  int32_t v146; // eax
  MemChrBag *v147; // rbx
  int *v148; // rbx
  int v149; // eax
  int v150; // eax
  __int64 v151; // rax
  MemChrBag v152; // [rsp+0h] [rbp-2810h]
  RateItem v153; // [rsp+0h] [rbp-2810h]
  MemChrBag v154; // [rsp+0h] [rbp-2810h]
  MemChrBag v155; // [rsp+20h] [rbp-27F0h] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+48h] [rbp-27C8h]
  char szCol[64]; // [rsp+50h] [rbp-27C0h] BYREF
  Answer::Inifile ini; // [rsp+90h] [rbp-2780h] BYREF
  LianRechargeCfg stu; // [rsp+D0h] [rbp-2740h] BYREF
  int32_t nStar; // [rsp+FCh] [rbp-2714h] BYREF
  std::string file; // [rsp+100h] [rbp-2710h] BYREF
  char v162; // [rsp+10Fh] [rbp-2701h] BYREF
  std::string key; // [rsp+110h] [rbp-2700h] BYREF
  char v164; // [rsp+11Fh] [rbp-26F1h] BYREF
  std::string section; // [rsp+120h] [rbp-26F0h] BYREF
  char v166; // [rsp+12Fh] [rbp-26E1h] BYREF
  std::string v167; // [rsp+130h] [rbp-26E0h] BYREF
  char v168; // [rsp+13Fh] [rbp-26D1h] BYREF
  std::string v169; // [rsp+140h] [rbp-26D0h] BYREF
  char v170; // [rsp+14Fh] [rbp-26C1h] BYREF
  Answer::Inifile v171; // [rsp+150h] [rbp-26C0h] BYREF
  char v172; // [rsp+18Fh] [rbp-2681h] BYREF
  std::string v173; // [rsp+190h] [rbp-2680h] BYREF
  char v174; // [rsp+19Fh] [rbp-2671h] BYREF
  std::string v175; // [rsp+1A0h] [rbp-2670h] BYREF
  char v176; // [rsp+1AFh] [rbp-2661h] BYREF
  std::string v177; // [rsp+1B0h] [rbp-2660h] BYREF
  char v178; // [rsp+1BFh] [rbp-2651h] BYREF
  std::string v179; // [rsp+1C0h] [rbp-2650h] BYREF
  char v180; // [rsp+1CFh] [rbp-2641h] BYREF
  std::string v181; // [rsp+1D0h] [rbp-2640h] BYREF
  char v182; // [rsp+1DFh] [rbp-2631h] BYREF
  std::string v183; // [rsp+1E0h] [rbp-2630h] BYREF
  char v184; // [rsp+1EFh] [rbp-2621h] BYREF
  std::string v185; // [rsp+1F0h] [rbp-2620h] BYREF
  char v186; // [rsp+1FFh] [rbp-2611h] BYREF
  std::string v187; // [rsp+200h] [rbp-2610h] BYREF
  char v188; // [rsp+20Fh] [rbp-2601h] BYREF
  std::string v189; // [rsp+210h] [rbp-2600h] BYREF
  char v190; // [rsp+21Fh] [rbp-25F1h] BYREF
  std::string v191; // [rsp+220h] [rbp-25F0h] BYREF
  char v192; // [rsp+22Fh] [rbp-25E1h] BYREF
  std::string v193; // [rsp+230h] [rbp-25E0h] BYREF
  char v194; // [rsp+23Fh] [rbp-25D1h] BYREF
  Answer::Inifile v195; // [rsp+240h] [rbp-25D0h] BYREF
  char v196; // [rsp+27Fh] [rbp-2591h] BYREF
  std::string v197; // [rsp+280h] [rbp-2590h] BYREF
  char v198; // [rsp+28Fh] [rbp-2581h] BYREF
  std::string v199; // [rsp+290h] [rbp-2580h] BYREF
  char v200; // [rsp+29Fh] [rbp-2571h] BYREF
  std::string v201; // [rsp+2A0h] [rbp-2570h] BYREF
  char v202; // [rsp+2AFh] [rbp-2561h] BYREF
  std::vector<MemChrBag> p___x; // [rsp+2B0h] [rbp-2560h] BYREF
  MemChrBagVector __x; // [rsp+2D0h] [rbp-2540h] BYREF
  Answer::Inifile v205; // [rsp+2F0h] [rbp-2520h] BYREF
  char v206; // [rsp+32Fh] [rbp-24E1h] BYREF
  std::string v207; // [rsp+330h] [rbp-24E0h] BYREF
  char v208; // [rsp+33Fh] [rbp-24D1h] BYREF
  std::string v209; // [rsp+340h] [rbp-24D0h] BYREF
  char v210; // [rsp+34Fh] [rbp-24C1h] BYREF
  std::string v211; // [rsp+350h] [rbp-24C0h] BYREF
  char v212; // [rsp+35Fh] [rbp-24B1h] BYREF
  std::string v213; // [rsp+360h] [rbp-24B0h] BYREF
  char v214; // [rsp+36Fh] [rbp-24A1h] BYREF
  std::string v215; // [rsp+370h] [rbp-24A0h] BYREF
  char v216; // [rsp+37Fh] [rbp-2491h] BYREF
  std::string v217; // [rsp+380h] [rbp-2490h] BYREF
  char v218; // [rsp+38Fh] [rbp-2481h] BYREF
  std::string v219; // [rsp+390h] [rbp-2480h] BYREF
  char v220; // [rsp+39Fh] [rbp-2471h] BYREF
  std::string v221; // [rsp+3A0h] [rbp-2470h] BYREF
  char v222; // [rsp+3AFh] [rbp-2461h] BYREF
  std::string v223; // [rsp+3B0h] [rbp-2460h] BYREF
  char v224; // [rsp+3BFh] [rbp-2451h] BYREF
  MemChrBagVector v225; // [rsp+3C0h] [rbp-2450h] BYREF
  Answer::Inifile v226; // [rsp+3E0h] [rbp-2430h] BYREF
  char v227; // [rsp+41Fh] [rbp-23F1h] BYREF
  std::string v228; // [rsp+420h] [rbp-23F0h] BYREF
  char v229; // [rsp+42Fh] [rbp-23E1h] BYREF
  std::string v230; // [rsp+430h] [rbp-23E0h] BYREF
  char v231; // [rsp+43Fh] [rbp-23D1h] BYREF
  std::string v232; // [rsp+440h] [rbp-23D0h] BYREF
  char v233; // [rsp+44Fh] [rbp-23C1h] BYREF
  std::string v234; // [rsp+450h] [rbp-23C0h] BYREF
  char v235; // [rsp+45Fh] [rbp-23B1h] BYREF
  std::string v236; // [rsp+460h] [rbp-23B0h] BYREF
  char v237; // [rsp+46Fh] [rbp-23A1h] BYREF
  std::string v238; // [rsp+470h] [rbp-23A0h] BYREF
  char v239; // [rsp+47Fh] [rbp-2391h] BYREF
  std::string v240; // [rsp+480h] [rbp-2390h] BYREF
  char v241; // [rsp+48Fh] [rbp-2381h] BYREF
  std::vector<MemChrBag> v242; // [rsp+490h] [rbp-2380h] BYREF
  std::string v243; // [rsp+4B0h] [rbp-2360h] BYREF
  char v244; // [rsp+4BFh] [rbp-2351h] BYREF
  std::string v245; // [rsp+4C0h] [rbp-2350h] BYREF
  char v246; // [rsp+4CFh] [rbp-2341h] BYREF
  MemChrBagVector v247; // [rsp+4D0h] [rbp-2340h] BYREF
  Answer::Inifile v248; // [rsp+4F0h] [rbp-2320h] BYREF
  char v249; // [rsp+52Fh] [rbp-22E1h] BYREF
  std::string v250; // [rsp+530h] [rbp-22E0h] BYREF
  char v251; // [rsp+53Fh] [rbp-22D1h] BYREF
  std::string v252; // [rsp+540h] [rbp-22D0h] BYREF
  char v253; // [rsp+54Fh] [rbp-22C1h] BYREF
  std::string v254; // [rsp+550h] [rbp-22C0h] BYREF
  char v255; // [rsp+55Fh] [rbp-22B1h] BYREF
  std::string v256; // [rsp+560h] [rbp-22B0h] BYREF
  char v257; // [rsp+56Fh] [rbp-22A1h] BYREF
  std::string v258; // [rsp+570h] [rbp-22A0h] BYREF
  char v259; // [rsp+57Fh] [rbp-2291h] BYREF
  std::string v260; // [rsp+580h] [rbp-2290h] BYREF
  char v261; // [rsp+58Fh] [rbp-2281h] BYREF
  std::string v262; // [rsp+590h] [rbp-2280h] BYREF
  char v263; // [rsp+59Fh] [rbp-2271h] BYREF
  std::string v264; // [rsp+5A0h] [rbp-2270h] BYREF
  char v265; // [rsp+5AFh] [rbp-2261h] BYREF
  std::string v266; // [rsp+5B0h] [rbp-2260h] BYREF
  char v267; // [rsp+5BFh] [rbp-2251h] BYREF
  std::string v268; // [rsp+5C0h] [rbp-2250h] BYREF
  char v269; // [rsp+5CFh] [rbp-2241h] BYREF
  std::string v270; // [rsp+5D0h] [rbp-2240h] BYREF
  char v271; // [rsp+5DFh] [rbp-2231h] BYREF
  std::string v272; // [rsp+5E0h] [rbp-2230h] BYREF
  char v273; // [rsp+5EFh] [rbp-2221h] BYREF
  std::string v274; // [rsp+5F0h] [rbp-2220h] BYREF
  char v275; // [rsp+5FFh] [rbp-2211h] BYREF
  std::string v276; // [rsp+600h] [rbp-2210h] BYREF
  char v277; // [rsp+60Fh] [rbp-2201h] BYREF
  std::string v278; // [rsp+610h] [rbp-2200h] BYREF
  char v279; // [rsp+61Fh] [rbp-21F1h] BYREF
  std::string v280; // [rsp+620h] [rbp-21F0h] BYREF
  char v281; // [rsp+62Fh] [rbp-21E1h] BYREF
  std::string v282; // [rsp+630h] [rbp-21E0h] BYREF
  char v283; // [rsp+63Fh] [rbp-21D1h] BYREF
  TimeArea v284; // [rsp+640h] [rbp-21D0h]
  std::string v285; // [rsp+650h] [rbp-21C0h] BYREF
  char v286; // [rsp+65Fh] [rbp-21B1h] BYREF
  std::string v287; // [rsp+660h] [rbp-21B0h] BYREF
  char v288; // [rsp+66Fh] [rbp-21A1h] BYREF
  std::string v289; // [rsp+670h] [rbp-21A0h] BYREF
  char v290; // [rsp+67Fh] [rbp-2191h] BYREF
  std::string v291; // [rsp+680h] [rbp-2190h] BYREF
  char v292; // [rsp+68Fh] [rbp-2181h] BYREF
  std::string v293; // [rsp+690h] [rbp-2180h] BYREF
  char v294; // [rsp+69Fh] [rbp-2171h] BYREF
  std::string v295; // [rsp+6A0h] [rbp-2170h] BYREF
  char v296; // [rsp+6AFh] [rbp-2161h] BYREF
  std::string v297; // [rsp+6B0h] [rbp-2160h] BYREF
  char v298; // [rsp+6BFh] [rbp-2151h] BYREF
  std::string v299; // [rsp+6C0h] [rbp-2150h] BYREF
  char v300; // [rsp+6CFh] [rbp-2141h] BYREF
  std::string v301; // [rsp+6D0h] [rbp-2140h] BYREF
  char v302; // [rsp+6DFh] [rbp-2131h] BYREF
  std::string v303; // [rsp+6E0h] [rbp-2130h] BYREF
  char v304; // [rsp+6EFh] [rbp-2121h] BYREF
  std::string v305; // [rsp+6F0h] [rbp-2120h] BYREF
  char v306; // [rsp+6FFh] [rbp-2111h] BYREF
  std::string v307; // [rsp+700h] [rbp-2110h] BYREF
  char v308; // [rsp+70Fh] [rbp-2101h] BYREF
  std::string v309; // [rsp+710h] [rbp-2100h] BYREF
  char v310; // [rsp+71Fh] [rbp-20F1h] BYREF
  std::string v311; // [rsp+720h] [rbp-20F0h] BYREF
  char v312; // [rsp+72Fh] [rbp-20E1h] BYREF
  std::string v313; // [rsp+730h] [rbp-20E0h] BYREF
  char v314; // [rsp+73Fh] [rbp-20D1h] BYREF
  std::string v315; // [rsp+740h] [rbp-20D0h] BYREF
  char v316; // [rsp+74Fh] [rbp-20C1h] BYREF
  std::string v317; // [rsp+750h] [rbp-20C0h] BYREF
  char v318; // [rsp+75Fh] [rbp-20B1h] BYREF
  std::string v319; // [rsp+760h] [rbp-20B0h] BYREF
  char v320; // [rsp+76Fh] [rbp-20A1h] BYREF
  std::vector<MemChrBag> v321; // [rsp+770h] [rbp-20A0h] BYREF
  std::string v322; // [rsp+790h] [rbp-2080h] BYREF
  char v323; // [rsp+79Fh] [rbp-2071h] BYREF
  std::string v324; // [rsp+7A0h] [rbp-2070h] BYREF
  char v325; // [rsp+7AFh] [rbp-2061h] BYREF
  MemChrBagVector v326; // [rsp+7B0h] [rbp-2060h] BYREF
  Answer::Inifile v327; // [rsp+7D0h] [rbp-2040h] BYREF
  char v328; // [rsp+80Fh] [rbp-2001h] BYREF
  std::string v329; // [rsp+810h] [rbp-2000h] BYREF
  char v330; // [rsp+81Fh] [rbp-1FF1h] BYREF
  std::string v331; // [rsp+820h] [rbp-1FF0h] BYREF
  char v332; // [rsp+82Fh] [rbp-1FE1h] BYREF
  std::string v333; // [rsp+830h] [rbp-1FE0h] BYREF
  char v334; // [rsp+83Fh] [rbp-1FD1h] BYREF
  MemChrBagVector v335; // [rsp+840h] [rbp-1FD0h] BYREF
  Answer::Inifile v336; // [rsp+860h] [rbp-1FB0h] BYREF
  char v337; // [rsp+89Fh] [rbp-1F71h] BYREF
  std::string v338; // [rsp+8A0h] [rbp-1F70h] BYREF
  char v339; // [rsp+8AFh] [rbp-1F61h] BYREF
  std::string v340; // [rsp+8B0h] [rbp-1F60h] BYREF
  char v341; // [rsp+8BFh] [rbp-1F51h] BYREF
  std::string v342; // [rsp+8C0h] [rbp-1F50h] BYREF
  char v343; // [rsp+8CFh] [rbp-1F41h] BYREF
  std::string v344; // [rsp+8D0h] [rbp-1F40h] BYREF
  char v345; // [rsp+8DFh] [rbp-1F31h] BYREF
  std::string v346; // [rsp+8E0h] [rbp-1F30h] BYREF
  char v347; // [rsp+8EFh] [rbp-1F21h] BYREF
  std::string v348; // [rsp+8F0h] [rbp-1F20h] BYREF
  char v349; // [rsp+8FFh] [rbp-1F11h] BYREF
  std::string v350; // [rsp+900h] [rbp-1F10h] BYREF
  char v351; // [rsp+90Fh] [rbp-1F01h] BYREF
  std::string v352; // [rsp+910h] [rbp-1F00h] BYREF
  char v353; // [rsp+91Fh] [rbp-1EF1h] BYREF
  std::string v354; // [rsp+920h] [rbp-1EF0h] BYREF
  char v355; // [rsp+92Fh] [rbp-1EE1h] BYREF
  std::vector<MemChrBag> v356; // [rsp+930h] [rbp-1EE0h] BYREF
  MemChrBagVector v357; // [rsp+950h] [rbp-1EC0h] BYREF
  Answer::Inifile v358; // [rsp+970h] [rbp-1EA0h] BYREF
  char v359; // [rsp+9AFh] [rbp-1E61h] BYREF
  std::string v360; // [rsp+9B0h] [rbp-1E60h] BYREF
  char v361; // [rsp+9BFh] [rbp-1E51h] BYREF
  std::string v362; // [rsp+9C0h] [rbp-1E50h] BYREF
  char v363; // [rsp+9CFh] [rbp-1E41h] BYREF
  std::string v364; // [rsp+9D0h] [rbp-1E40h] BYREF
  char v365; // [rsp+9DFh] [rbp-1E31h] BYREF
  std::string v366; // [rsp+9E0h] [rbp-1E30h] BYREF
  char v367; // [rsp+9EFh] [rbp-1E21h] BYREF
  std::string v368; // [rsp+9F0h] [rbp-1E20h] BYREF
  char v369; // [rsp+9FFh] [rbp-1E11h] BYREF
  std::string v370; // [rsp+A00h] [rbp-1E10h] BYREF
  char v371; // [rsp+A0Fh] [rbp-1E01h] BYREF
  std::string v372; // [rsp+A10h] [rbp-1E00h] BYREF
  char v373; // [rsp+A1Fh] [rbp-1DF1h] BYREF
  std::string v374; // [rsp+A20h] [rbp-1DF0h] BYREF
  char v375; // [rsp+A2Fh] [rbp-1DE1h] BYREF
  std::string v376; // [rsp+A30h] [rbp-1DE0h] BYREF
  char v377; // [rsp+A3Fh] [rbp-1DD1h] BYREF
  MemChrBagVector v378; // [rsp+A40h] [rbp-1DD0h] BYREF
  Answer::Inifile v379; // [rsp+A60h] [rbp-1DB0h] BYREF
  char v380; // [rsp+A9Fh] [rbp-1D71h] BYREF
  std::string v381; // [rsp+AA0h] [rbp-1D70h] BYREF
  char v382; // [rsp+AAFh] [rbp-1D61h] BYREF
  std::string v383; // [rsp+AB0h] [rbp-1D60h] BYREF
  char v384; // [rsp+ABFh] [rbp-1D51h] BYREF
  std::string v385; // [rsp+AC0h] [rbp-1D50h] BYREF
  char v386; // [rsp+ACFh] [rbp-1D41h] BYREF
  std::string v387; // [rsp+AD0h] [rbp-1D40h] BYREF
  char v388; // [rsp+ADFh] [rbp-1D31h] BYREF
  std::string v389; // [rsp+AE0h] [rbp-1D30h] BYREF
  char v390; // [rsp+AEFh] [rbp-1D21h] BYREF
  std::string v391; // [rsp+AF0h] [rbp-1D20h] BYREF
  char v392; // [rsp+AFFh] [rbp-1D11h] BYREF
  std::string v393; // [rsp+B00h] [rbp-1D10h] BYREF
  char v394; // [rsp+B0Fh] [rbp-1D01h] BYREF
  MemChrBagVector v395; // [rsp+B10h] [rbp-1D00h] BYREF
  Answer::Inifile v396; // [rsp+B30h] [rbp-1CE0h] BYREF
  char v397; // [rsp+B6Fh] [rbp-1CA1h] BYREF
  std::string v398; // [rsp+B70h] [rbp-1CA0h] BYREF
  char v399; // [rsp+B7Fh] [rbp-1C91h] BYREF
  std::string v400; // [rsp+B80h] [rbp-1C90h] BYREF
  char v401; // [rsp+B8Fh] [rbp-1C81h] BYREF
  std::string v402; // [rsp+B90h] [rbp-1C80h] BYREF
  char v403; // [rsp+B9Fh] [rbp-1C71h] BYREF
  std::string v404; // [rsp+BA0h] [rbp-1C70h] BYREF
  char v405; // [rsp+BAFh] [rbp-1C61h] BYREF
  std::string v406; // [rsp+BB0h] [rbp-1C60h] BYREF
  char v407; // [rsp+BBFh] [rbp-1C51h] BYREF
  std::vector<MemChrBag> v408; // [rsp+BC0h] [rbp-1C50h] BYREF
  std::string v409; // [rsp+BE0h] [rbp-1C30h] BYREF
  char v410; // [rsp+BEFh] [rbp-1C21h] BYREF
  std::string v411; // [rsp+BF0h] [rbp-1C20h] BYREF
  char v412; // [rsp+BFFh] [rbp-1C11h] BYREF
  std::string v413; // [rsp+C00h] [rbp-1C10h] BYREF
  char v414; // [rsp+C0Fh] [rbp-1C01h] BYREF
  std::string v415; // [rsp+C10h] [rbp-1C00h] BYREF
  char v416; // [rsp+C1Fh] [rbp-1BF1h] BYREF
  MemChrBagVector v417; // [rsp+C20h] [rbp-1BF0h] BYREF
  Answer::Inifile v418; // [rsp+C40h] [rbp-1BD0h] BYREF
  char v419; // [rsp+C7Fh] [rbp-1B91h] BYREF
  std::string v420; // [rsp+C80h] [rbp-1B90h] BYREF
  char v421; // [rsp+C8Fh] [rbp-1B81h] BYREF
  std::string v422; // [rsp+C90h] [rbp-1B80h] BYREF
  char v423; // [rsp+C9Fh] [rbp-1B71h] BYREF
  std::string v424; // [rsp+CA0h] [rbp-1B70h] BYREF
  char v425; // [rsp+CAFh] [rbp-1B61h] BYREF
  std::string v426; // [rsp+CB0h] [rbp-1B60h] BYREF
  char v427; // [rsp+CBFh] [rbp-1B51h] BYREF
  std::string v428; // [rsp+CC0h] [rbp-1B50h] BYREF
  char v429; // [rsp+CCBh] [rbp-1B45h] BYREF
  int IntValue; // [rsp+CCCh] [rbp-1B44h] BYREF
  std::string v431; // [rsp+CD0h] [rbp-1B40h] BYREF
  char v432; // [rsp+CDFh] [rbp-1B31h] BYREF
  std::string v433; // [rsp+CE0h] [rbp-1B30h] BYREF
  char v434; // [rsp+CEFh] [rbp-1B21h] BYREF
  std::string v435; // [rsp+CF0h] [rbp-1B20h] BYREF
  char v436; // [rsp+CFFh] [rbp-1B11h] BYREF
  std::string v437; // [rsp+D00h] [rbp-1B10h] BYREF
  char v438; // [rsp+D0Fh] [rbp-1B01h] BYREF
  std::string v439; // [rsp+D10h] [rbp-1B00h] BYREF
  char v440; // [rsp+D1Fh] [rbp-1AF1h] BYREF
  std::string v441; // [rsp+D20h] [rbp-1AF0h] BYREF
  char v442; // [rsp+D2Fh] [rbp-1AE1h] BYREF
  std::string v443; // [rsp+D30h] [rbp-1AE0h] BYREF
  char v444; // [rsp+D3Fh] [rbp-1AD1h] BYREF
  std::string v445; // [rsp+D40h] [rbp-1AD0h] BYREF
  char v446; // [rsp+D4Fh] [rbp-1AC1h] BYREF
  std::string v447; // [rsp+D50h] [rbp-1AC0h] BYREF
  char v448; // [rsp+D5Fh] [rbp-1AB1h] BYREF
  std::string v449; // [rsp+D60h] [rbp-1AB0h] BYREF
  char v450; // [rsp+D6Fh] [rbp-1AA1h] BYREF
  std::vector<MemChrBag> v451; // [rsp+D70h] [rbp-1AA0h] BYREF
  MemChrBagVector v452; // [rsp+D90h] [rbp-1A80h] BYREF
  Answer::Inifile v453; // [rsp+DB0h] [rbp-1A60h] BYREF
  char v454; // [rsp+DEFh] [rbp-1A21h] BYREF
  std::string v455; // [rsp+DF0h] [rbp-1A20h] BYREF
  char v456; // [rsp+DFFh] [rbp-1A11h] BYREF
  std::string v457; // [rsp+E00h] [rbp-1A10h] BYREF
  char v458; // [rsp+E0Fh] [rbp-1A01h] BYREF
  std::string v459; // [rsp+E10h] [rbp-1A00h] BYREF
  char v460; // [rsp+E1Fh] [rbp-19F1h] BYREF
  std::string v461; // [rsp+E20h] [rbp-19F0h] BYREF
  char v462; // [rsp+E2Fh] [rbp-19E1h] BYREF
  std::string v463; // [rsp+E30h] [rbp-19E0h] BYREF
  char v464; // [rsp+E3Fh] [rbp-19D1h] BYREF
  std::vector<MemChrBag> v465; // [rsp+E40h] [rbp-19D0h] BYREF
  std::string v466; // [rsp+E60h] [rbp-19B0h] BYREF
  char v467; // [rsp+E6Fh] [rbp-19A1h] BYREF
  std::string v468; // [rsp+E70h] [rbp-19A0h] BYREF
  char v469; // [rsp+E7Fh] [rbp-1991h] BYREF
  std::string v470; // [rsp+E80h] [rbp-1990h] BYREF
  char v471; // [rsp+E8Fh] [rbp-1981h] BYREF
  std::string v472; // [rsp+E90h] [rbp-1980h] BYREF
  char v473; // [rsp+E9Fh] [rbp-1971h] BYREF
  MemChrBagVector v474; // [rsp+EA0h] [rbp-1970h] BYREF
  Answer::Inifile v475; // [rsp+EC0h] [rbp-1950h] BYREF
  char v476; // [rsp+EFFh] [rbp-1911h] BYREF
  std::string v477; // [rsp+F00h] [rbp-1910h] BYREF
  char v478; // [rsp+F0Fh] [rbp-1901h] BYREF
  std::string v479; // [rsp+F10h] [rbp-1900h] BYREF
  char v480; // [rsp+F1Fh] [rbp-18F1h] BYREF
  std::string v481; // [rsp+F20h] [rbp-18F0h] BYREF
  char v482; // [rsp+F2Fh] [rbp-18E1h] BYREF
  std::string v483; // [rsp+F30h] [rbp-18E0h] BYREF
  char v484; // [rsp+F3Fh] [rbp-18D1h] BYREF
  std::string v485; // [rsp+F40h] [rbp-18D0h] BYREF
  char v486; // [rsp+F4Fh] [rbp-18C1h] BYREF
  std::string v487; // [rsp+F50h] [rbp-18C0h] BYREF
  char v488; // [rsp+F5Fh] [rbp-18B1h] BYREF
  std::string v489; // [rsp+F60h] [rbp-18B0h] BYREF
  char v490; // [rsp+F6Fh] [rbp-18A1h] BYREF
  std::vector<MemChrBag> v491; // [rsp+F70h] [rbp-18A0h] BYREF
  std::string v492; // [rsp+F90h] [rbp-1880h] BYREF
  char v493; // [rsp+F9Fh] [rbp-1871h] BYREF
  std::string v494; // [rsp+FA0h] [rbp-1870h] BYREF
  char v495; // [rsp+FAFh] [rbp-1861h] BYREF
  MemChrBagVector v496; // [rsp+FB0h] [rbp-1860h] BYREF
  Answer::Inifile v497; // [rsp+FD0h] [rbp-1840h] BYREF
  char v498; // [rsp+100Fh] [rbp-1801h] BYREF
  std::string v499; // [rsp+1010h] [rbp-1800h] BYREF
  char v500; // [rsp+101Fh] [rbp-17F1h] BYREF
  std::string v501; // [rsp+1020h] [rbp-17F0h] BYREF
  char v502; // [rsp+102Fh] [rbp-17E1h] BYREF
  std::string v503; // [rsp+1030h] [rbp-17E0h] BYREF
  char v504; // [rsp+103Fh] [rbp-17D1h] BYREF
  std::string v505; // [rsp+1040h] [rbp-17D0h] BYREF
  char v506; // [rsp+104Fh] [rbp-17C1h] BYREF
  std::string v507; // [rsp+1050h] [rbp-17C0h] BYREF
  char v508; // [rsp+105Fh] [rbp-17B1h] BYREF
  std::vector<ShopGoods> v509; // [rsp+1060h] [rbp-17B0h] BYREF
  ShopGoods v510; // [rsp+1080h] [rbp-1790h] BYREF
  std::string v511; // [rsp+10A0h] [rbp-1770h] BYREF
  char v512; // [rsp+10AFh] [rbp-1761h] BYREF
  std::string v513; // [rsp+10B0h] [rbp-1760h] BYREF
  char v514; // [rsp+10BFh] [rbp-1751h] BYREF
  MemChrBagVector v515; // [rsp+10C0h] [rbp-1750h] BYREF
  Answer::Inifile v516; // [rsp+10E0h] [rbp-1730h] BYREF
  char v517; // [rsp+111Fh] [rbp-16F1h] BYREF
  std::string v518; // [rsp+1120h] [rbp-16F0h] BYREF
  char v519; // [rsp+112Fh] [rbp-16E1h] BYREF
  std::string v520; // [rsp+1130h] [rbp-16E0h] BYREF
  char v521; // [rsp+113Fh] [rbp-16D1h] BYREF
  std::string v522; // [rsp+1140h] [rbp-16D0h] BYREF
  char v523; // [rsp+114Fh] [rbp-16C1h] BYREF
  std::string v524; // [rsp+1150h] [rbp-16C0h] BYREF
  char v525; // [rsp+115Fh] [rbp-16B1h] BYREF
  std::string v526; // [rsp+1160h] [rbp-16B0h] BYREF
  char v527; // [rsp+116Fh] [rbp-16A1h] BYREF
  std::string v528; // [rsp+1170h] [rbp-16A0h] BYREF
  char v529; // [rsp+117Fh] [rbp-1691h] BYREF
  std::string v530; // [rsp+1180h] [rbp-1690h] BYREF
  char v531; // [rsp+118Fh] [rbp-1681h] BYREF
  std::string v532; // [rsp+1190h] [rbp-1680h] BYREF
  char v533; // [rsp+119Fh] [rbp-1671h] BYREF
  std::string v534; // [rsp+11A0h] [rbp-1670h] BYREF
  char v535; // [rsp+11AFh] [rbp-1661h] BYREF
  std::string v536; // [rsp+11B0h] [rbp-1660h] BYREF
  char v537; // [rsp+11BFh] [rbp-1651h] BYREF
  std::string v538; // [rsp+11C0h] [rbp-1650h] BYREF
  char v539; // [rsp+11CFh] [rbp-1641h] BYREF
  std::string v540; // [rsp+11D0h] [rbp-1640h] BYREF
  char v541; // [rsp+11DFh] [rbp-1631h] BYREF
  std::string v542; // [rsp+11E0h] [rbp-1630h] BYREF
  char v543; // [rsp+11EFh] [rbp-1621h] BYREF
  std::string v544; // [rsp+11F0h] [rbp-1620h] BYREF
  char v545; // [rsp+11FFh] [rbp-1611h] BYREF
  std::string v546; // [rsp+1200h] [rbp-1610h] BYREF
  char v547; // [rsp+120Fh] [rbp-1601h] BYREF
  MemChrBag v548; // [rsp+1210h] [rbp-1600h]
  std::string v549; // [rsp+1230h] [rbp-15E0h] BYREF
  char v550; // [rsp+123Fh] [rbp-15D1h] BYREF
  std::string v551; // [rsp+1240h] [rbp-15D0h] BYREF
  char v552; // [rsp+124Fh] [rbp-15C1h] BYREF
  Answer::Inifile v553; // [rsp+1250h] [rbp-15C0h] BYREF
  char v554; // [rsp+128Fh] [rbp-1581h] BYREF
  std::string v555; // [rsp+1290h] [rbp-1580h] BYREF
  char v556; // [rsp+129Fh] [rbp-1571h] BYREF
  std::string v557; // [rsp+12A0h] [rbp-1570h] BYREF
  char v558; // [rsp+12AFh] [rbp-1561h] BYREF
  std::string v559; // [rsp+12B0h] [rbp-1560h] BYREF
  char v560; // [rsp+12BFh] [rbp-1551h] BYREF
  std::string v561; // [rsp+12C0h] [rbp-1550h] BYREF
  char v562; // [rsp+12CFh] [rbp-1541h] BYREF
  std::string v563; // [rsp+12D0h] [rbp-1540h] BYREF
  char v564; // [rsp+12DFh] [rbp-1531h] BYREF
  Answer::Inifile v565; // [rsp+12E0h] [rbp-1530h] BYREF
  char v566; // [rsp+131Fh] [rbp-14F1h] BYREF
  std::string v567; // [rsp+1320h] [rbp-14F0h] BYREF
  char v568; // [rsp+132Fh] [rbp-14E1h] BYREF
  std::string v569; // [rsp+1330h] [rbp-14E0h] BYREF
  char v570; // [rsp+133Fh] [rbp-14D1h] BYREF
  std::string v571; // [rsp+1340h] [rbp-14D0h] BYREF
  char v572; // [rsp+134Fh] [rbp-14C1h] BYREF
  std::string v573; // [rsp+1350h] [rbp-14C0h] BYREF
  char v574; // [rsp+135Fh] [rbp-14B1h] BYREF
  std::string v575; // [rsp+1360h] [rbp-14B0h] BYREF
  char v576; // [rsp+136Fh] [rbp-14A1h] BYREF
  std::vector<MemChrBag> v577; // [rsp+1370h] [rbp-14A0h] BYREF
  std::string v578; // [rsp+1390h] [rbp-1480h] BYREF
  char v579; // [rsp+139Fh] [rbp-1471h] BYREF
  std::string v580; // [rsp+13A0h] [rbp-1470h] BYREF
  char v581; // [rsp+13AFh] [rbp-1461h] BYREF
  MemChrBagVector v582; // [rsp+13B0h] [rbp-1460h] BYREF
  Answer::Inifile v583; // [rsp+13D0h] [rbp-1440h] BYREF
  char v584; // [rsp+140Fh] [rbp-1401h] BYREF
  std::string v585; // [rsp+1410h] [rbp-1400h] BYREF
  char v586; // [rsp+141Fh] [rbp-13F1h] BYREF
  std::string v587; // [rsp+1420h] [rbp-13F0h] BYREF
  char v588; // [rsp+142Fh] [rbp-13E1h] BYREF
  std::string v589; // [rsp+1430h] [rbp-13E0h] BYREF
  char v590; // [rsp+143Fh] [rbp-13D1h] BYREF
  std::string v591; // [rsp+1440h] [rbp-13D0h] BYREF
  char v592; // [rsp+144Fh] [rbp-13C1h] BYREF
  std::string v593; // [rsp+1450h] [rbp-13C0h] BYREF
  char v594; // [rsp+145Fh] [rbp-13B1h] BYREF
  std::string v595; // [rsp+1460h] [rbp-13B0h] BYREF
  char v596; // [rsp+146Fh] [rbp-13A1h] BYREF
  std::string v597; // [rsp+1470h] [rbp-13A0h] BYREF
  char v598; // [rsp+147Fh] [rbp-1391h] BYREF
  std::vector<MemChrBag> v599; // [rsp+1480h] [rbp-1390h] BYREF
  std::string v600; // [rsp+14A0h] [rbp-1370h] BYREF
  char v601; // [rsp+14AFh] [rbp-1361h] BYREF
  std::string v602; // [rsp+14B0h] [rbp-1360h] BYREF
  char v603; // [rsp+14BFh] [rbp-1351h] BYREF
  MemChrBagVector v604; // [rsp+14C0h] [rbp-1350h] BYREF
  Answer::Inifile v605; // [rsp+14E0h] [rbp-1330h] BYREF
  char v606; // [rsp+151Fh] [rbp-12F1h] BYREF
  std::string v607; // [rsp+1520h] [rbp-12F0h] BYREF
  char v608; // [rsp+152Fh] [rbp-12E1h] BYREF
  std::string v609; // [rsp+1530h] [rbp-12E0h] BYREF
  char v610; // [rsp+153Fh] [rbp-12D1h] BYREF
  std::string v611; // [rsp+1540h] [rbp-12D0h] BYREF
  char v612; // [rsp+154Fh] [rbp-12C1h] BYREF
  std::string v613; // [rsp+1550h] [rbp-12C0h] BYREF
  char v614; // [rsp+155Fh] [rbp-12B1h] BYREF
  std::string v615; // [rsp+1560h] [rbp-12B0h] BYREF
  char v616; // [rsp+156Fh] [rbp-12A1h] BYREF
  std::string v617; // [rsp+1570h] [rbp-12A0h] BYREF
  char v618; // [rsp+157Fh] [rbp-1291h] BYREF
  std::string v619; // [rsp+1580h] [rbp-1290h] BYREF
  char v620; // [rsp+158Fh] [rbp-1281h] BYREF
  MemChrBagVector v621; // [rsp+1590h] [rbp-1280h] BYREF
  Answer::Inifile v622; // [rsp+15B0h] [rbp-1260h] BYREF
  char v623; // [rsp+15EFh] [rbp-1221h] BYREF
  std::string v624; // [rsp+15F0h] [rbp-1220h] BYREF
  char v625; // [rsp+15FFh] [rbp-1211h] BYREF
  std::string v626; // [rsp+1600h] [rbp-1210h] BYREF
  char v627; // [rsp+160Fh] [rbp-1201h] BYREF
  std::string v628; // [rsp+1610h] [rbp-1200h] BYREF
  char v629; // [rsp+161Fh] [rbp-11F1h] BYREF
  std::string v630; // [rsp+1620h] [rbp-11F0h] BYREF
  char v631; // [rsp+162Fh] [rbp-11E1h] BYREF
  std::string v632; // [rsp+1630h] [rbp-11E0h] BYREF
  char v633; // [rsp+163Fh] [rbp-11D1h] BYREF
  std::vector<MemChrBag> v634; // [rsp+1640h] [rbp-11D0h] BYREF
  std::string v635; // [rsp+1660h] [rbp-11B0h] BYREF
  char v636; // [rsp+166Fh] [rbp-11A1h] BYREF
  std::string v637; // [rsp+1670h] [rbp-11A0h] BYREF
  char v638; // [rsp+167Fh] [rbp-1191h] BYREF
  MemChrBagVector v639; // [rsp+1680h] [rbp-1190h] BYREF
  Answer::Inifile v640; // [rsp+16A0h] [rbp-1170h] BYREF
  char v641; // [rsp+16DFh] [rbp-1131h] BYREF
  std::string v642; // [rsp+16E0h] [rbp-1130h] BYREF
  char v643; // [rsp+16EFh] [rbp-1121h] BYREF
  std::string v644; // [rsp+16F0h] [rbp-1120h] BYREF
  char v645; // [rsp+16FFh] [rbp-1111h] BYREF
  std::string v646; // [rsp+1700h] [rbp-1110h] BYREF
  char v647; // [rsp+170Fh] [rbp-1101h] BYREF
  std::string v648; // [rsp+1710h] [rbp-1100h] BYREF
  char v649; // [rsp+171Fh] [rbp-10F1h] BYREF
  std::string v650; // [rsp+1720h] [rbp-10F0h] BYREF
  char v651; // [rsp+172Fh] [rbp-10E1h] BYREF
  ShopGoods v652; // [rsp+1730h] [rbp-10E0h] BYREF
  std::string v653; // [rsp+1750h] [rbp-10C0h] BYREF
  char v654; // [rsp+175Fh] [rbp-10B1h] BYREF
  std::string v655; // [rsp+1760h] [rbp-10B0h] BYREF
  char v656; // [rsp+176Fh] [rbp-10A1h] BYREF
  MemChrBagVector v657; // [rsp+1770h] [rbp-10A0h] BYREF
  Answer::Inifile v658; // [rsp+1790h] [rbp-1080h] BYREF
  char v659; // [rsp+17CFh] [rbp-1041h] BYREF
  std::string v660; // [rsp+17D0h] [rbp-1040h] BYREF
  char v661; // [rsp+17DFh] [rbp-1031h] BYREF
  std::string v662; // [rsp+17E0h] [rbp-1030h] BYREF
  char v663; // [rsp+17EFh] [rbp-1021h] BYREF
  std::string v664; // [rsp+17F0h] [rbp-1020h] BYREF
  char v665; // [rsp+17FFh] [rbp-1011h] BYREF
  std::string v666; // [rsp+1800h] [rbp-1010h] BYREF
  char v667; // [rsp+180Fh] [rbp-1001h] BYREF
  std::string v668; // [rsp+1810h] [rbp-1000h] BYREF
  char v669; // [rsp+181Fh] [rbp-FF1h] BYREF
  std::string v670; // [rsp+1820h] [rbp-FF0h] BYREF
  char v671; // [rsp+182Fh] [rbp-FE1h] BYREF
  std::string v672; // [rsp+1830h] [rbp-FE0h] BYREF
  char v673; // [rsp+183Fh] [rbp-FD1h] BYREF
  std::string v674; // [rsp+1840h] [rbp-FD0h] BYREF
  char v675; // [rsp+184Fh] [rbp-FC1h] BYREF
  std::string v676; // [rsp+1850h] [rbp-FC0h] BYREF
  char v677; // [rsp+185Fh] [rbp-FB1h] BYREF
  std::string v678; // [rsp+1860h] [rbp-FB0h] BYREF
  char v679; // [rsp+186Fh] [rbp-FA1h] BYREF
  std::string v680; // [rsp+1870h] [rbp-FA0h] BYREF
  char v681; // [rsp+187Fh] [rbp-F91h] BYREF
  std::string v682; // [rsp+1880h] [rbp-F90h] BYREF
  char v683; // [rsp+188Fh] [rbp-F81h] BYREF
  std::string v684; // [rsp+1890h] [rbp-F80h] BYREF
  char v685; // [rsp+189Fh] [rbp-F71h] BYREF
  std::string v686; // [rsp+18A0h] [rbp-F70h] BYREF
  char v687; // [rsp+18AFh] [rbp-F61h] BYREF
  std::string v688; // [rsp+18B0h] [rbp-F60h] BYREF
  char v689; // [rsp+18BFh] [rbp-F51h] BYREF
  std::string v690; // [rsp+18C0h] [rbp-F50h] BYREF
  char v691; // [rsp+18CFh] [rbp-F41h] BYREF
  std::string v692; // [rsp+18D0h] [rbp-F40h] BYREF
  char v693; // [rsp+18DFh] [rbp-F31h] BYREF
  std::string v694; // [rsp+18E0h] [rbp-F30h] BYREF
  char v695; // [rsp+18EFh] [rbp-F21h] BYREF
  std::string v696; // [rsp+18F0h] [rbp-F20h] BYREF
  char v697; // [rsp+18FBh] [rbp-F15h] BYREF
  int v698; // [rsp+18FCh] [rbp-F14h] BYREF
  std::string v699; // [rsp+1900h] [rbp-F10h] BYREF
  char v700; // [rsp+190Fh] [rbp-F01h] BYREF
  std::string v701; // [rsp+1910h] [rbp-F00h] BYREF
  char v702; // [rsp+191Fh] [rbp-EF1h] BYREF
  std::string v703; // [rsp+1920h] [rbp-EF0h] BYREF
  char v704; // [rsp+192Fh] [rbp-EE1h] BYREF
  std::string v705; // [rsp+1930h] [rbp-EE0h] BYREF
  char v706; // [rsp+193Fh] [rbp-ED1h] BYREF
  std::string v707; // [rsp+1940h] [rbp-ED0h] BYREF
  char v708; // [rsp+194Fh] [rbp-EC1h] BYREF
  std::string v709; // [rsp+1950h] [rbp-EC0h] BYREF
  char v710; // [rsp+195Fh] [rbp-EB1h] BYREF
  std::string v711; // [rsp+1960h] [rbp-EB0h] BYREF
  char v712; // [rsp+196Fh] [rbp-EA1h] BYREF
  std::string v713; // [rsp+1970h] [rbp-EA0h] BYREF
  char v714; // [rsp+197Fh] [rbp-E91h] BYREF
  std::vector<MemChrBag> v715; // [rsp+1980h] [rbp-E90h] BYREF
  std::string v716; // [rsp+19A0h] [rbp-E70h] BYREF
  char v717; // [rsp+19AFh] [rbp-E61h] BYREF
  std::string v718; // [rsp+19B0h] [rbp-E60h] BYREF
  char v719; // [rsp+19BFh] [rbp-E51h] BYREF
  std::string v720; // [rsp+19C0h] [rbp-E50h] BYREF
  char v721; // [rsp+19CFh] [rbp-E41h] BYREF
  std::string v722; // [rsp+19D0h] [rbp-E40h] BYREF
  char v723; // [rsp+19DFh] [rbp-E31h] BYREF
  MemChrBagVector v724; // [rsp+19E0h] [rbp-E30h] BYREF
  Answer::Inifile v725; // [rsp+1A00h] [rbp-E10h] BYREF
  char v726; // [rsp+1A3Fh] [rbp-DD1h] BYREF
  std::string v727; // [rsp+1A40h] [rbp-DD0h] BYREF
  char v728; // [rsp+1A4Fh] [rbp-DC1h] BYREF
  std::string v729; // [rsp+1A50h] [rbp-DC0h] BYREF
  char v730; // [rsp+1A5Fh] [rbp-DB1h] BYREF
  std::string v731; // [rsp+1A60h] [rbp-DB0h] BYREF
  char v732; // [rsp+1A6Fh] [rbp-DA1h] BYREF
  std::string v733; // [rsp+1A70h] [rbp-DA0h] BYREF
  char v734; // [rsp+1A7Fh] [rbp-D91h] BYREF
  std::string v735; // [rsp+1A80h] [rbp-D90h] BYREF
  char v736; // [rsp+1A8Fh] [rbp-D81h] BYREF
  std::string v737; // [rsp+1A90h] [rbp-D80h] BYREF
  char v738; // [rsp+1A9Fh] [rbp-D71h] BYREF
  std::string v739; // [rsp+1AA0h] [rbp-D70h] BYREF
  char v740; // [rsp+1AAFh] [rbp-D61h] BYREF
  std::string v741; // [rsp+1AB0h] [rbp-D60h] BYREF
  char v742; // [rsp+1ABFh] [rbp-D51h] BYREF
  std::string v743; // [rsp+1AC0h] [rbp-D50h] BYREF
  char v744; // [rsp+1ACFh] [rbp-D41h] BYREF
  std::string v745; // [rsp+1AD0h] [rbp-D40h] BYREF
  char v746; // [rsp+1ADFh] [rbp-D31h] BYREF
  std::string v747; // [rsp+1AE0h] [rbp-D30h] BYREF
  char v748; // [rsp+1AEFh] [rbp-D21h] BYREF
  std::string v749; // [rsp+1AF0h] [rbp-D20h] BYREF
  char v750; // [rsp+1AFFh] [rbp-D11h] BYREF
  std::string v751; // [rsp+1B00h] [rbp-D10h] BYREF
  char v752; // [rsp+1B0Fh] [rbp-D01h] BYREF
  std::string v753; // [rsp+1B10h] [rbp-D00h] BYREF
  char v754; // [rsp+1B1Fh] [rbp-CF1h] BYREF
  std::string v755; // [rsp+1B20h] [rbp-CF0h] BYREF
  char v756; // [rsp+1B2Fh] [rbp-CE1h] BYREF
  std::string v757; // [rsp+1B30h] [rbp-CE0h] BYREF
  char v758; // [rsp+1B3Fh] [rbp-CD1h] BYREF
  std::string v759; // [rsp+1B40h] [rbp-CD0h] BYREF
  char v760; // [rsp+1B4Fh] [rbp-CC1h] BYREF
  std::string v761; // [rsp+1B50h] [rbp-CC0h] BYREF
  char v762; // [rsp+1B5Fh] [rbp-CB1h] BYREF
  std::string v763; // [rsp+1B60h] [rbp-CB0h] BYREF
  char v764; // [rsp+1B6Fh] [rbp-CA1h] BYREF
  std::string v765; // [rsp+1B70h] [rbp-CA0h] BYREF
  char v766; // [rsp+1B7Fh] [rbp-C91h] BYREF
  std::string v767; // [rsp+1B80h] [rbp-C90h] BYREF
  char v768; // [rsp+1B8Fh] [rbp-C81h] BYREF
  std::vector<MemChrBag> v769; // [rsp+1B90h] [rbp-C80h] BYREF
  std::string v770; // [rsp+1BB0h] [rbp-C60h] BYREF
  char v771; // [rsp+1BBFh] [rbp-C51h] BYREF
  std::string v772; // [rsp+1BC0h] [rbp-C50h] BYREF
  char v773; // [rsp+1BCFh] [rbp-C41h] BYREF
  MemChrBagVector v774; // [rsp+1BD0h] [rbp-C40h] BYREF
  Answer::Inifile v775; // [rsp+1BF0h] [rbp-C20h] BYREF
  char v776; // [rsp+1C2Fh] [rbp-BE1h] BYREF
  std::string v777; // [rsp+1C30h] [rbp-BE0h] BYREF
  char v778; // [rsp+1C3Fh] [rbp-BD1h] BYREF
  std::string v779; // [rsp+1C40h] [rbp-BD0h] BYREF
  char v780; // [rsp+1C4Fh] [rbp-BC1h] BYREF
  std::string v781; // [rsp+1C50h] [rbp-BC0h] BYREF
  char v782; // [rsp+1C5Fh] [rbp-BB1h] BYREF
  std::string v783; // [rsp+1C60h] [rbp-BB0h] BYREF
  char v784; // [rsp+1C6Fh] [rbp-BA1h] BYREF
  std::string v785; // [rsp+1C70h] [rbp-BA0h] BYREF
  char v786; // [rsp+1C7Fh] [rbp-B91h] BYREF
  std::vector<MemChrBag> v787; // [rsp+1C80h] [rbp-B90h] BYREF
  std::string v788; // [rsp+1CA0h] [rbp-B70h] BYREF
  char v789; // [rsp+1CAFh] [rbp-B61h] BYREF
  std::string v790; // [rsp+1CB0h] [rbp-B60h] BYREF
  char v791; // [rsp+1CBFh] [rbp-B51h] BYREF
  std::string v792; // [rsp+1CC0h] [rbp-B50h] BYREF
  char v793; // [rsp+1CCFh] [rbp-B41h] BYREF
  std::string v794; // [rsp+1CD0h] [rbp-B40h] BYREF
  char v795; // [rsp+1CDFh] [rbp-B31h] BYREF
  MemChrBagVector v796; // [rsp+1CE0h] [rbp-B30h] BYREF
  Answer::Inifile v797; // [rsp+1D00h] [rbp-B10h] BYREF
  char v798; // [rsp+1D3Fh] [rbp-AD1h] BYREF
  std::string v799; // [rsp+1D40h] [rbp-AD0h] BYREF
  char v800; // [rsp+1D4Fh] [rbp-AC1h] BYREF
  std::string v801; // [rsp+1D50h] [rbp-AC0h] BYREF
  char v802; // [rsp+1D5Fh] [rbp-AB1h] BYREF
  std::string v803; // [rsp+1D60h] [rbp-AB0h] BYREF
  char v804; // [rsp+1D6Fh] [rbp-AA1h] BYREF
  std::string v805; // [rsp+1D70h] [rbp-AA0h] BYREF
  char v806; // [rsp+1D7Fh] [rbp-A91h] BYREF
  std::string v807; // [rsp+1D80h] [rbp-A90h] BYREF
  char v808; // [rsp+1D8Fh] [rbp-A81h] BYREF
  std::vector<MemChrBag> v809; // [rsp+1D90h] [rbp-A80h] BYREF
  std::string v810; // [rsp+1DB0h] [rbp-A60h] BYREF
  char v811; // [rsp+1DBFh] [rbp-A51h] BYREF
  std::string v812; // [rsp+1DC0h] [rbp-A50h] BYREF
  char v813; // [rsp+1DCFh] [rbp-A41h] BYREF
  std::string v814; // [rsp+1DD0h] [rbp-A40h] BYREF
  char v815; // [rsp+1DDFh] [rbp-A31h] BYREF
  std::string v816; // [rsp+1DE0h] [rbp-A30h] BYREF
  char v817; // [rsp+1DEFh] [rbp-A21h] BYREF
  MemChrBagVector v818; // [rsp+1DF0h] [rbp-A20h] BYREF
  Answer::Inifile v819; // [rsp+1E10h] [rbp-A00h] BYREF
  char v820; // [rsp+1E4Fh] [rbp-9C1h] BYREF
  std::string v821; // [rsp+1E50h] [rbp-9C0h] BYREF
  char v822; // [rsp+1E5Fh] [rbp-9B1h] BYREF
  std::string v823; // [rsp+1E60h] [rbp-9B0h] BYREF
  char v824; // [rsp+1E6Fh] [rbp-9A1h] BYREF
  std::string v825; // [rsp+1E70h] [rbp-9A0h] BYREF
  char v826; // [rsp+1E7Fh] [rbp-991h] BYREF
  std::string v827; // [rsp+1E80h] [rbp-990h] BYREF
  char v828; // [rsp+1E8Fh] [rbp-981h] BYREF
  std::string v829; // [rsp+1E90h] [rbp-980h] BYREF
  char v830; // [rsp+1E9Fh] [rbp-971h] BYREF
  std::vector<MemChrBag> v831; // [rsp+1EA0h] [rbp-970h] BYREF
  std::string v832; // [rsp+1EC0h] [rbp-950h] BYREF
  char v833; // [rsp+1ECFh] [rbp-941h] BYREF
  std::string v834; // [rsp+1ED0h] [rbp-940h] BYREF
  char v835; // [rsp+1EDFh] [rbp-931h] BYREF
  std::string v836; // [rsp+1EE0h] [rbp-930h] BYREF
  char v837; // [rsp+1EEFh] [rbp-921h] BYREF
  std::string v838; // [rsp+1EF0h] [rbp-920h] BYREF
  char v839; // [rsp+1EFFh] [rbp-911h] BYREF
  MemChrBagVector v840; // [rsp+1F00h] [rbp-910h] BYREF
  Answer::Inifile v841; // [rsp+1F20h] [rbp-8F0h] BYREF
  char v842; // [rsp+1F5Fh] [rbp-8B1h] BYREF
  std::string v843; // [rsp+1F60h] [rbp-8B0h] BYREF
  char v844; // [rsp+1F6Fh] [rbp-8A1h] BYREF
  std::string v845; // [rsp+1F70h] [rbp-8A0h] BYREF
  char v846; // [rsp+1F7Fh] [rbp-891h] BYREF
  std::string v847; // [rsp+1F80h] [rbp-890h] BYREF
  char v848; // [rsp+1F8Fh] [rbp-881h] BYREF
  std::string v849; // [rsp+1F90h] [rbp-880h] BYREF
  char v850; // [rsp+1F9Fh] [rbp-871h] BYREF
  std::string v851; // [rsp+1FA0h] [rbp-870h] BYREF
  char v852; // [rsp+1FAFh] [rbp-861h] BYREF
  std::string v853; // [rsp+1FB0h] [rbp-860h] BYREF
  char v854; // [rsp+1FBFh] [rbp-851h] BYREF
  std::string v855; // [rsp+1FC0h] [rbp-850h] BYREF
  char v856; // [rsp+1FCFh] [rbp-841h] BYREF
  std::string v857; // [rsp+1FD0h] [rbp-840h] BYREF
  char v858; // [rsp+1FDFh] [rbp-831h] BYREF
  std::string v859; // [rsp+1FE0h] [rbp-830h] BYREF
  char v860; // [rsp+1FEFh] [rbp-821h] BYREF
  std::vector<MemChrBag> v861; // [rsp+1FF0h] [rbp-820h] BYREF
  std::string v862; // [rsp+2010h] [rbp-800h] BYREF
  char v863; // [rsp+201Fh] [rbp-7F1h] BYREF
  std::string v864; // [rsp+2020h] [rbp-7F0h] BYREF
  char v865; // [rsp+202Fh] [rbp-7E1h] BYREF
  std::string v866; // [rsp+2030h] [rbp-7E0h] BYREF
  char v867; // [rsp+203Fh] [rbp-7D1h] BYREF
  std::string v868; // [rsp+2040h] [rbp-7D0h] BYREF
  char v869; // [rsp+204Fh] [rbp-7C1h] BYREF
  MemChrBagVector v870; // [rsp+2050h] [rbp-7C0h] BYREF
  Answer::Inifile v871; // [rsp+2070h] [rbp-7A0h] BYREF
  char v872; // [rsp+20AFh] [rbp-761h] BYREF
  std::string v873; // [rsp+20B0h] [rbp-760h] BYREF
  char v874; // [rsp+20BFh] [rbp-751h] BYREF
  std::string v875; // [rsp+20C0h] [rbp-750h] BYREF
  char v876; // [rsp+20CFh] [rbp-741h] BYREF
  std::string v877; // [rsp+20D0h] [rbp-740h] BYREF
  char v878; // [rsp+20DFh] [rbp-731h] BYREF
  std::string v879; // [rsp+20E0h] [rbp-730h] BYREF
  char v880; // [rsp+20EFh] [rbp-721h] BYREF
  std::string v881; // [rsp+20F0h] [rbp-720h] BYREF
  char v882; // [rsp+20FFh] [rbp-711h] BYREF
  std::vector<MemChrBag> v883; // [rsp+2100h] [rbp-710h] BYREF
  std::string v884; // [rsp+2120h] [rbp-6F0h] BYREF
  char v885; // [rsp+212Fh] [rbp-6E1h] BYREF
  std::string v886; // [rsp+2130h] [rbp-6E0h] BYREF
  char v887; // [rsp+213Fh] [rbp-6D1h] BYREF
  MemChrBagVector v888; // [rsp+2140h] [rbp-6D0h] BYREF
  Answer::Inifile v889; // [rsp+2160h] [rbp-6B0h] BYREF
  char v890; // [rsp+219Fh] [rbp-671h] BYREF
  std::string v891; // [rsp+21A0h] [rbp-670h] BYREF
  char v892; // [rsp+21AFh] [rbp-661h] BYREF
  std::string v893; // [rsp+21B0h] [rbp-660h] BYREF
  char v894; // [rsp+21BFh] [rbp-651h] BYREF
  std::string v895; // [rsp+21C0h] [rbp-650h] BYREF
  char v896; // [rsp+21CFh] [rbp-641h] BYREF
  std::string v897; // [rsp+21D0h] [rbp-640h] BYREF
  char v898; // [rsp+21DFh] [rbp-631h] BYREF
  std::string v899; // [rsp+21E0h] [rbp-630h] BYREF
  char v900; // [rsp+21EFh] [rbp-621h] BYREF
  std::vector<MemChrBag> v901; // [rsp+21F0h] [rbp-620h] BYREF
  std::string v902; // [rsp+2210h] [rbp-600h] BYREF
  char v903; // [rsp+221Fh] [rbp-5F1h] BYREF
  std::string v904; // [rsp+2220h] [rbp-5F0h] BYREF
  char v905; // [rsp+222Fh] [rbp-5E1h] BYREF
  MemChrBagVector v906; // [rsp+2230h] [rbp-5E0h] BYREF
  Answer::Inifile v907; // [rsp+2250h] [rbp-5C0h] BYREF
  char v908; // [rsp+228Fh] [rbp-581h] BYREF
  std::string v909; // [rsp+2290h] [rbp-580h] BYREF
  char v910; // [rsp+229Fh] [rbp-571h] BYREF
  std::string v911; // [rsp+22A0h] [rbp-570h] BYREF
  char v912; // [rsp+22AFh] [rbp-561h] BYREF
  std::string v913; // [rsp+22B0h] [rbp-560h] BYREF
  char v914; // [rsp+22BFh] [rbp-551h] BYREF
  std::string v915; // [rsp+22C0h] [rbp-550h] BYREF
  char v916; // [rsp+22CFh] [rbp-541h] BYREF
  std::string v917; // [rsp+22D0h] [rbp-540h] BYREF
  char v918; // [rsp+22DFh] [rbp-531h] BYREF
  std::string v919; // [rsp+22E0h] [rbp-530h] BYREF
  char v920; // [rsp+22EFh] [rbp-521h] BYREF
  std::string v921; // [rsp+22F0h] [rbp-520h] BYREF
  char v922; // [rsp+22FFh] [rbp-511h] BYREF
  std::string v923; // [rsp+2300h] [rbp-510h] BYREF
  char v924; // [rsp+230Fh] [rbp-501h] BYREF
  std::string v925; // [rsp+2310h] [rbp-500h] BYREF
  char v926; // [rsp+231Fh] [rbp-4F1h] BYREF
  std::string v927; // [rsp+2320h] [rbp-4F0h] BYREF
  char v928; // [rsp+232Fh] [rbp-4E1h] BYREF
  std::string v929; // [rsp+2330h] [rbp-4E0h] BYREF
  char v930; // [rsp+233Fh] [rbp-4D1h] BYREF
  std::vector<MemChrBag> v931; // [rsp+2340h] [rbp-4D0h] BYREF
  std::string v932; // [rsp+2360h] [rbp-4B0h] BYREF
  char v933; // [rsp+236Fh] [rbp-4A1h] BYREF
  std::string v934; // [rsp+2370h] [rbp-4A0h] BYREF
  char v935; // [rsp+237Fh] [rbp-491h] BYREF
  MemChrBagVector v936; // [rsp+2380h] [rbp-490h] BYREF
  Answer::Inifile v937; // [rsp+23A0h] [rbp-470h] BYREF
  char v938; // [rsp+23DFh] [rbp-431h] BYREF
  std::string v939; // [rsp+23E0h] [rbp-430h] BYREF
  char v940; // [rsp+23EFh] [rbp-421h] BYREF
  std::vector<MemChrBag> v941; // [rsp+23F0h] [rbp-420h] BYREF
  std::string v942; // [rsp+2410h] [rbp-400h] BYREF
  char v943; // [rsp+241Fh] [rbp-3F1h] BYREF
  std::string v944; // [rsp+2420h] [rbp-3F0h] BYREF
  char v945; // [rsp+242Fh] [rbp-3E1h] BYREF
  std::string v946; // [rsp+2430h] [rbp-3E0h] BYREF
  char v947; // [rsp+243Fh] [rbp-3D1h] BYREF
  std::string v948; // [rsp+2440h] [rbp-3D0h] BYREF
  char v949; // [rsp+244Fh] [rbp-3C1h] BYREF
  MemChrBagVector v950; // [rsp+2450h] [rbp-3C0h] BYREF
  Answer::Inifile v951; // [rsp+2470h] [rbp-3A0h] BYREF
  char v952; // [rsp+24AFh] [rbp-361h] BYREF
  std::string v953; // [rsp+24B0h] [rbp-360h] BYREF
  char v954; // [rsp+24BFh] [rbp-351h] BYREF
  std::string v955; // [rsp+24C0h] [rbp-350h] BYREF
  char v956; // [rsp+24CFh] [rbp-341h] BYREF
  std::string v957; // [rsp+24D0h] [rbp-340h] BYREF
  char v958; // [rsp+24DFh] [rbp-331h] BYREF
  std::string v959; // [rsp+24E0h] [rbp-330h] BYREF
  char v960; // [rsp+24EFh] [rbp-321h] BYREF
  std::string v961; // [rsp+24F0h] [rbp-320h] BYREF
  char v962; // [rsp+24FFh] [rbp-311h] BYREF
  std::string v963; // [rsp+2500h] [rbp-310h] BYREF
  char v964; // [rsp+250Fh] [rbp-301h] BYREF
  std::string v965; // [rsp+2510h] [rbp-300h] BYREF
  char v966; // [rsp+251Fh] [rbp-2F1h] BYREF
  std::string v967; // [rsp+2520h] [rbp-2F0h] BYREF
  char v968; // [rsp+252Fh] [rbp-2E1h] BYREF
  std::string v969; // [rsp+2530h] [rbp-2E0h] BYREF
  char v970; // [rsp+253Fh] [rbp-2D1h] BYREF
  std::string v971; // [rsp+2540h] [rbp-2D0h] BYREF
  char v972; // [rsp+254Fh] [rbp-2C1h] BYREF
  std::string v973; // [rsp+2550h] [rbp-2C0h] BYREF
  char v974; // [rsp+255Fh] [rbp-2B1h] BYREF
  std::string v975; // [rsp+2560h] [rbp-2B0h] BYREF
  char v976; // [rsp+256Fh] [rbp-2A1h] BYREF
  std::string v977; // [rsp+2570h] [rbp-2A0h] BYREF
  char v978; // [rsp+257Fh] [rbp-291h] BYREF
  RateItem v979; // [rsp+2580h] [rbp-290h]
  std::string strItem; // [rsp+25A0h] [rbp-270h] BYREF
  char v981; // [rsp+25AFh] [rbp-261h] BYREF
  Answer::Inifile v982; // [rsp+25B0h] [rbp-260h] BYREF
  char v983; // [rsp+25EFh] [rbp-221h] BYREF
  std::string v984; // [rsp+25F0h] [rbp-220h] BYREF
  char v985; // [rsp+25FFh] [rbp-211h] BYREF
  std::string v986; // [rsp+2600h] [rbp-210h] BYREF
  char v987; // [rsp+260Fh] [rbp-201h] BYREF
  std::string v988; // [rsp+2610h] [rbp-200h] BYREF
  char v989; // [rsp+261Fh] [rbp-1F1h] BYREF
  std::string v990; // [rsp+2620h] [rbp-1F0h] BYREF
  char v991; // [rsp+262Fh] [rbp-1E1h] BYREF
  std::string v992; // [rsp+2630h] [rbp-1E0h] BYREF
  char v993; // [rsp+263Fh] [rbp-1D1h] BYREF
  MemChrBag v994; // [rsp+2640h] [rbp-1D0h]
  Answer::Inifile v995; // [rsp+2660h] [rbp-1B0h] BYREF
  char v996; // [rsp+269Fh] [rbp-171h] BYREF
  std::string v997; // [rsp+26A0h] [rbp-170h] BYREF
  char v998; // [rsp+26AFh] [rbp-161h] BYREF
  std::string v999; // [rsp+26B0h] [rbp-160h] BYREF
  char v1000; // [rsp+26BFh] [rbp-151h] BYREF
  std::string v1001; // [rsp+26C0h] [rbp-150h] BYREF
  char v1002; // [rsp+26CFh] [rbp-141h] BYREF
  std::string v1003; // [rsp+26D0h] [rbp-140h] BYREF
  char v1004; // [rsp+26DFh] [rbp-131h] BYREF
  std::string v1005; // [rsp+26E0h] [rbp-130h] BYREF
  char v1006; // [rsp+26EFh] [rbp-121h] BYREF
  std::string v1007; // [rsp+26F0h] [rbp-120h] BYREF
  char v1008; // [rsp+26FFh] [rbp-111h] BYREF
  std::string v1009; // [rsp+2700h] [rbp-110h] BYREF
  char v1010; // [rsp+270Fh] [rbp-101h] BYREF
  MemChrBagVector v1011; // [rsp+2710h] [rbp-100h] BYREF
  Answer::Inifile v1012; // [rsp+2730h] [rbp-E0h] BYREF
  int32_t i_0; // [rsp+2768h] [rbp-A8h]
  int32_t nCount; // [rsp+276Ch] [rbp-A4h]
  int32_t i_1; // [rsp+2770h] [rbp-A0h]
  int32_t i_2; // [rsp+2774h] [rbp-9Ch]
  int32_t i_3; // [rsp+2778h] [rbp-98h]
  int32_t i_4; // [rsp+277Ch] [rbp-94h]
  int32_t i_5; // [rsp+2780h] [rbp-90h]
  int32_t i_6; // [rsp+2784h] [rbp-8Ch]
  int32_t i_7; // [rsp+2788h] [rbp-88h]
  int32_t i_8; // [rsp+278Ch] [rbp-84h]
  int32_t nDaySize; // [rsp+2790h] [rbp-80h]
  int32_t i_9; // [rsp+2794h] [rbp-7Ch]
  int32_t j; // [rsp+2798h] [rbp-78h]
  int32_t i_10; // [rsp+279Ch] [rbp-74h]
  int32_t i_11; // [rsp+27A0h] [rbp-70h]
  int32_t i_12; // [rsp+27A4h] [rbp-6Ch]
  int32_t i_13; // [rsp+27A8h] [rbp-68h]
  int32_t i_14; // [rsp+27ACh] [rbp-64h]
  int32_t i_15; // [rsp+27B0h] [rbp-60h]
  int32_t nCount_0; // [rsp+27B4h] [rbp-5Ch]
  int32_t i_16; // [rsp+27B8h] [rbp-58h]
  int32_t i_17; // [rsp+27BCh] [rbp-54h]
  int32_t i_18; // [rsp+27C0h] [rbp-50h]
  int32_t i_19; // [rsp+27C4h] [rbp-4Ch]
  int32_t i_20; // [rsp+27C8h] [rbp-48h]
  int32_t i_21; // [rsp+27CCh] [rbp-44h]
  int32_t i_22; // [rsp+27D0h] [rbp-40h]
  int32_t i_23; // [rsp+27D4h] [rbp-3Ch]
  int32_t i_24; // [rsp+27D8h] [rbp-38h]
  int32_t i_25; // [rsp+27DCh] [rbp-34h]
  int32_t i_26; // [rsp+27E0h] [rbp-30h]
  int32_t i_27; // [rsp+27E4h] [rbp-2Ch]
  int32_t i_28; // [rsp+27E8h] [rbp-28h]
  int32_t i_29; // [rsp+27ECh] [rbp-24h]
  int32_t i_30; // [rsp+27F0h] [rbp-20h]
  int32_t i_31; // [rsp+27F4h] [rbp-1Ch]
  int32_t i_32; // [rsp+27F8h] [rbp-18h]
  int32_t j_0; // [rsp+27FCh] [rbp-14h]
  ItemData v1051; // 0:kr00_12.12

  thisa = this;
  bzero(this->m_vStartDay, 0xBCu);
  bzero(this->m_vEndDay, 0xBCu);
  Answer::Inifile::Inifile(&ini);
  std::allocator<char>::allocator(&v162);
  std::string::string(&file, "./ServerConfig/Tables/FestivalDoubleEleven.cfg", &v162);
  Answer::Inifile::parse(&ini, &file);
  std::string::~string(&file);
  std::allocator<char>::~allocator(&v162);
  memset(szCol, 0, sizeof(szCol));
  std::allocator<char>::allocator(&v164);
  std::string::string(&key, "hot_sign", &v164);
  std::allocator<char>::allocator(&v166);
  std::string::string(&section, "CONFIG", &v166);
  this->m_nHotSign = Answer::Inifile::getIntValue(&ini, &section, &key);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v166);
  std::string::~string(&key);
  std::allocator<char>::~allocator(&v164);
  std::allocator<char>::allocator(&v168);
  std::string::string(&v167, "version", &v168);
  std::allocator<char>::allocator(&v170);
  std::string::string(&v169, "CONFIG", &v170);
  thisa->m_nVersion = Answer::Inifile::getIntValue(&ini, &v169, &v167);
  std::string::~string(&v169);
  std::allocator<char>::~allocator(&v170);
  std::string::~string(&v167);
  std::allocator<char>::~allocator(&v168);
  std::allocator<char>::allocator((char *)&v171.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::string::string(
    &v171.m_strMap._M_t._M_impl._M_header._M_parent,
    "start_time",
    (char *)&v171.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::allocator<char>::allocator((char *)&v171.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::string(
    &v171.m_strMap._M_t._M_impl._M_header._M_right,
    "CONFIG",
    (char *)&v171.m_strMap._M_t._M_impl._M_node_count + 7);
  Answer::Inifile::getStrValue(
    &v171,
    (const std::string *const)&ini,
    (const std::string *const)&v171.m_strMap._M_t._M_impl._M_header._M_right);
  thisa->m_nStartDay = Answer::DayTime::StringToIntTime((std::string *)&v171);
  std::string::~string(&v171);
  std::string::~string(&v171.m_strMap._M_t._M_impl._M_header._M_right);
  std::allocator<char>::~allocator((char *)&v171.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::~string(&v171.m_strMap._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v171.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::allocator<char>::allocator(&v172);
  std::string::string(&v171.m_currentSection, "end_day", &v172);
  std::allocator<char>::allocator(&v174);
  std::string::string(&v173, "CONFIG", &v174);
  thisa->m_nEndDay = Answer::Inifile::getIntValue(&ini, &v173, &v171.m_currentSection);
  std::string::~string(&v173);
  std::allocator<char>::~allocator(&v174);
  std::string::~string(&v171.m_currentSection);
  std::allocator<char>::~allocator(&v172);
  std::allocator<char>::allocator(&v176);
  std::string::string(&v175, "icon", &v176);
  std::allocator<char>::allocator(&v178);
  std::string::string(&v177, "CONFIG", &v178);
  thisa->m_nIcon = Answer::Inifile::getIntValue(&ini, &v177, &v175);
  std::string::~string(&v177);
  std::allocator<char>::~allocator(&v178);
  std::string::~string(&v175);
  std::allocator<char>::~allocator(&v176);
  std::allocator<char>::allocator(&v180);
  std::string::string(&v179, "icon_hide_day", &v180);
  std::allocator<char>::allocator(&v182);
  std::string::string(&v181, "CONFIG", &v182);
  thisa->m_nIconHideDay = Answer::Inifile::getIntValue(&ini, &v181, &v179);
  std::string::~string(&v181);
  std::allocator<char>::~allocator(&v182);
  std::string::~string(&v179);
  std::allocator<char>::~allocator(&v180);
  std::allocator<char>::allocator(&v184);
  std::string::string(&v183, "game_start_day", &v184);
  std::allocator<char>::allocator(&v186);
  std::string::string(&v185, "CONFIG", &v186);
  thisa->m_nGameStartDay = Answer::Inifile::getIntValue(&ini, &v185, &v183);
  std::string::~string(&v185);
  std::allocator<char>::~allocator(&v186);
  std::string::~string(&v183);
  std::allocator<char>::~allocator(&v184);
  std::allocator<char>::allocator(&v188);
  std::string::string(&v187, "unite_start_day", &v188);
  std::allocator<char>::allocator(&v190);
  std::string::string(&v189, "CONFIG", &v190);
  thisa->m_nUniteStartDay = Answer::Inifile::getIntValue(&ini, &v189, &v187);
  std::string::~string(&v189);
  std::allocator<char>::~allocator(&v190);
  std::string::~string(&v187);
  std::allocator<char>::~allocator(&v188);
  std::allocator<char>::allocator(&v192);
  std::string::string(&v191, "drop_group", &v192);
  std::allocator<char>::allocator(&v194);
  std::string::string(&v193, "CONFIG", &v194);
  thisa->m_nDropGroup = Answer::Inifile::getIntValue(&ini, &v193, &v191);
  std::string::~string(&v193);
  std::allocator<char>::~allocator(&v194);
  std::string::~string(&v191);
  std::allocator<char>::~allocator(&v192);
  std::allocator<char>::allocator((char *)&v195.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::string::string(
    &v195.m_strMap._M_t._M_impl._M_header._M_parent,
    "open",
    (char *)&v195.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::allocator<char>::allocator((char *)&v195.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::string(
    &v195.m_strMap._M_t._M_impl._M_header._M_right,
    "CONFIG",
    (char *)&v195.m_strMap._M_t._M_impl._M_node_count + 7);
  Answer::Inifile::getStrValue(
    &v195,
    (const std::string *const)&ini,
    (const std::string *const)&v195.m_strMap._M_t._M_impl._M_header._M_right);
  CFestivalDoubleEleven::initOpenList(thisa, (const std::string *const)&v195);
  std::string::~string(&v195);
  std::string::~string(&v195.m_strMap._M_t._M_impl._M_header._M_right);
  std::allocator<char>::~allocator((char *)&v195.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::~string(&v195.m_strMap._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v195.m_strMap._M_t._M_impl._M_header._M_left + 7);
  v1 = Answer::DayTime::now();
  v2 = Answer::DayTime::dayzero(v1);
  thisa->m_nDay = (v2 - Answer::DayTime::dayzero(thisa->m_nStartDay)) / 86400;
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_LAND) )
  {
    std::allocator<char>::allocator(&v196);
    std::string::string(&v195.m_currentSection, "start_day", &v196);
    std::allocator<char>::allocator(&v198);
    std::string::string(&v197, "LAND", &v198);
    thisa->m_vStartDay[1] = Answer::Inifile::getIntValue(&ini, &v197, &v195.m_currentSection);
    std::string::~string(&v197);
    std::allocator<char>::~allocator(&v198);
    std::string::~string(&v195.m_currentSection);
    std::allocator<char>::~allocator(&v196);
    std::allocator<char>::allocator(&v200);
    std::string::string(&v199, "end_day", &v200);
    std::allocator<char>::allocator(&v202);
    std::string::string(&v201, "LAND", &v202);
    thisa->m_vEndDay[1] = Answer::Inifile::getIntValue(&ini, &v201, &v199);
    std::string::~string(&v201);
    std::allocator<char>::~allocator(&v202);
    std::string::~string(&v199);
    std::allocator<char>::~allocator(&v200);
    std::vector<MemChrBag>::vector(&p___x);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vLandGift, thisa->m_nEndDay, &p___x);
    std::vector<MemChrBag>::~vector(&p___x);
    HIDWORD(v1012.m_currentSection._M_dataplus._M_p) = 0;
    while ( thisa->m_nEndDay > SHIDWORD(v1012.m_currentSection._M_dataplus._M_p) )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "gift%d", HIDWORD(v1012.m_currentSection._M_dataplus._M_p) + 1);
      std::allocator<char>::allocator((char *)&v205.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v205.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v205.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v205.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v205.m_strMap._M_t._M_impl._M_header._M_right,
        "LAND",
        (char *)&v205.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v205,
        (const std::string *const)&ini,
        (const std::string *const)&v205.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&__x, (const std::string *const)&v205);
      v3 = std::vector<std::vector<MemChrBag>>::operator[](
             &thisa->m_vLandGift,
             SHIDWORD(v1012.m_currentSection._M_dataplus._M_p));
      std::vector<MemChrBag>::operator=(v3, &__x);
      std::vector<MemChrBag>::~vector(&__x);
      std::string::~string(&v205);
      std::string::~string(&v205.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v205.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v205.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v205.m_strMap._M_t._M_impl._M_header._M_left + 7);
      ++HIDWORD(v1012.m_currentSection._M_dataplus._M_p);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE) )
  {
    std::allocator<char>::allocator(&v206);
    std::string::string(&v205.m_currentSection, "start_day", &v206);
    std::allocator<char>::allocator(&v208);
    std::string::string(&v207, "DAILY_RECHARGE", &v208);
    thisa->m_vStartDay[2] = Answer::Inifile::getIntValue(&ini, &v207, &v205.m_currentSection);
    std::string::~string(&v207);
    std::allocator<char>::~allocator(&v208);
    std::string::~string(&v205.m_currentSection);
    std::allocator<char>::~allocator(&v206);
    std::allocator<char>::allocator(&v210);
    std::string::string(&v209, "end_day", &v210);
    std::allocator<char>::allocator(&v212);
    std::string::string(&v211, "DAILY_RECHARGE", &v212);
    thisa->m_vEndDay[2] = Answer::Inifile::getIntValue(&ini, &v211, &v209);
    std::string::~string(&v211);
    std::allocator<char>::~allocator(&v212);
    std::string::~string(&v209);
    std::allocator<char>::~allocator(&v210);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW) )
  {
    std::allocator<char>::allocator(&v214);
    std::string::string(&v213, "start_day", &v214);
    std::allocator<char>::allocator(&v216);
    std::string::string(&v215, "LUCKY_DRAW", &v216);
    thisa->m_vStartDay[3] = Answer::Inifile::getIntValue(&ini, &v215, &v213);
    std::string::~string(&v215);
    std::allocator<char>::~allocator(&v216);
    std::string::~string(&v213);
    std::allocator<char>::~allocator(&v214);
    std::allocator<char>::allocator(&v218);
    std::string::string(&v217, "end_day", &v218);
    std::allocator<char>::allocator(&v220);
    std::string::string(&v219, "LUCKY_DRAW", &v220);
    thisa->m_vEndDay[3] = Answer::Inifile::getIntValue(&ini, &v219, &v217);
    std::string::~string(&v219);
    std::allocator<char>::~allocator(&v220);
    std::string::~string(&v217);
    std::allocator<char>::~allocator(&v218);
    std::allocator<char>::allocator(&v222);
    std::string::string(&v221, "loop_times", &v222);
    std::allocator<char>::allocator(&v224);
    std::string::string(&v223, "LUCKY_DRAW", &v224);
    thisa->m_nDrawLoopTimes = Answer::Inifile::getIntValue(&ini, &v223, &v221);
    std::string::~string(&v223);
    std::allocator<char>::~allocator(&v224);
    std::string::~string(&v221);
    std::allocator<char>::~allocator(&v222);
    std::allocator<char>::allocator((char *)&v226.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v226.m_strMap._M_t._M_impl._M_header._M_parent,
      "loop_reward",
      (char *)&v226.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v226.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v226.m_strMap._M_t._M_impl._M_header._M_right,
      "LUCKY_DRAW",
      (char *)&v226.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v226,
      (const std::string *const)&ini,
      (const std::string *const)&v226.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v225, (const std::string *const)&v226);
    std::vector<MemChrBag>::operator=(&thisa->m_vDrawLoopReward, &v225);
    std::vector<MemChrBag>::~vector(&v225);
    std::string::~string(&v226);
    std::string::~string(&v226.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v226.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v226.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v226.m_strMap._M_t._M_impl._M_header._M_left + 7);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK) )
  {
    std::allocator<char>::allocator(&v227);
    std::string::string(&v226.m_currentSection, "start_day", &v227);
    std::allocator<char>::allocator(&v229);
    std::string::string(&v228, "LUCKY_DRAW", &v229);
    thisa->m_vStartDay[4] = Answer::Inifile::getIntValue(&ini, &v228, &v226.m_currentSection);
    std::string::~string(&v228);
    std::allocator<char>::~allocator(&v229);
    std::string::~string(&v226.m_currentSection);
    std::allocator<char>::~allocator(&v227);
    std::allocator<char>::allocator(&v231);
    std::string::string(&v230, "end_day", &v231);
    std::allocator<char>::allocator(&v233);
    std::string::string(&v232, "LUCKY_DRAW", &v233);
    thisa->m_vEndDay[4] = Answer::Inifile::getIntValue(&ini, &v232, &v230);
    std::string::~string(&v232);
    std::allocator<char>::~allocator(&v233);
    std::string::~string(&v230);
    std::allocator<char>::~allocator(&v231);
    std::allocator<char>::allocator(&v235);
    std::string::string(&v234, "rank_size", &v235);
    std::allocator<char>::allocator(&v237);
    std::string::string(&v236, "LUCKY_DRAW_RANK", &v237);
    thisa->m_nDrawRankSize = Answer::Inifile::getIntValue(&ini, &v236, &v234);
    std::string::~string(&v236);
    std::allocator<char>::~allocator(&v237);
    std::string::~string(&v234);
    std::allocator<char>::~allocator(&v235);
    std::allocator<char>::allocator(&v239);
    std::string::string(&v238, "rank_limit", &v239);
    std::allocator<char>::allocator(&v241);
    std::string::string(&v240, "LUCKY_DRAW_RANK", &v241);
    thisa->m_nDrawRankLimit = Answer::Inifile::getIntValue(&ini, &v240, &v238);
    std::string::~string(&v240);
    std::allocator<char>::~allocator(&v241);
    std::string::~string(&v238);
    std::allocator<char>::~allocator(&v239);
    std::vector<int>::resize(&thisa->m_vDrawRankMail, thisa->m_nDrawRankSize, 0);
    std::vector<MemChrBag>::vector(&v242);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vDrawRankReward, thisa->m_nDrawRankSize, &v242);
    std::vector<MemChrBag>::~vector(&v242);
    for ( i_0 = 0; thisa->m_nDrawRankSize > i_0; ++i_0 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "rank_mail%d", i_0 + 1);
      v4 = std::vector<int>::operator[](&thisa->m_vDrawRankMail, i_0);
      std::allocator<char>::allocator(&v244);
      std::string::string(&v243, szCol, &v244);
      std::allocator<char>::allocator(&v246);
      std::string::string(&v245, "LUCKY_DRAW_RANK", &v246);
      *v4 = Answer::Inifile::getIntValue(&ini, &v245, &v243);
      std::string::~string(&v245);
      std::allocator<char>::~allocator(&v246);
      std::string::~string(&v243);
      std::allocator<char>::~allocator(&v244);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "rank_reward%d", i_0 + 1);
      std::allocator<char>::allocator((char *)&v248.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v248.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v248.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v248.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v248.m_strMap._M_t._M_impl._M_header._M_right,
        "LUCKY_DRAW_RANK",
        (char *)&v248.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v248,
        (const std::string *const)&ini,
        (const std::string *const)&v248.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v247, (const std::string *const)&v248);
      v5 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vDrawRankReward, i_0);
      std::vector<MemChrBag>::operator=(v5, &v247);
      std::vector<MemChrBag>::~vector(&v247);
      std::string::~string(&v248);
      std::string::~string(&v248.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v248.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v248.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v248.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_EXCHANGE) )
  {
    std::allocator<char>::allocator(&v249);
    std::string::string(&v248.m_currentSection, "start_day", &v249);
    std::allocator<char>::allocator(&v251);
    std::string::string(&v250, "EXCHANGE", &v251);
    thisa->m_vStartDay[5] = Answer::Inifile::getIntValue(&ini, &v250, &v248.m_currentSection);
    std::string::~string(&v250);
    std::allocator<char>::~allocator(&v251);
    std::string::~string(&v248.m_currentSection);
    std::allocator<char>::~allocator(&v249);
    std::allocator<char>::allocator(&v253);
    std::string::string(&v252, "end_day", &v253);
    std::allocator<char>::allocator(&v255);
    std::string::string(&v254, "EXCHANGE", &v255);
    thisa->m_vEndDay[5] = Answer::Inifile::getIntValue(&ini, &v254, &v252);
    std::string::~string(&v254);
    std::allocator<char>::~allocator(&v255);
    std::string::~string(&v252);
    std::allocator<char>::~allocator(&v253);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_WORLD_BOSS) )
  {
    std::allocator<char>::allocator(&v257);
    std::string::string(&v256, "start_day", &v257);
    std::allocator<char>::allocator(&v259);
    std::string::string(&v258, "WORLD_BOSS", &v259);
    thisa->m_vStartDay[6] = Answer::Inifile::getIntValue(&ini, &v258, &v256);
    std::string::~string(&v258);
    std::allocator<char>::~allocator(&v259);
    std::string::~string(&v256);
    std::allocator<char>::~allocator(&v257);
    std::allocator<char>::allocator(&v261);
    std::string::string(&v260, "end_day", &v261);
    std::allocator<char>::allocator(&v263);
    std::string::string(&v262, "WORLD_BOSS", &v263);
    thisa->m_vEndDay[6] = Answer::Inifile::getIntValue(&ini, &v262, &v260);
    std::string::~string(&v262);
    std::allocator<char>::~allocator(&v263);
    std::string::~string(&v260);
    std::allocator<char>::~allocator(&v261);
    std::allocator<char>::allocator(&v265);
    std::string::string(&v264, "icon", &v265);
    std::allocator<char>::allocator(&v267);
    std::string::string(&v266, "WORLD_BOSS", &v267);
    thisa->m_nWorldBossIcon = Answer::Inifile::getIntValue(&ini, &v266, &v264);
    std::string::~string(&v266);
    std::allocator<char>::~allocator(&v267);
    std::string::~string(&v264);
    std::allocator<char>::~allocator(&v265);
    std::allocator<char>::allocator(&v269);
    std::string::string(&v268, "start_broadcast", &v269);
    std::allocator<char>::allocator(&v271);
    std::string::string(&v270, "WORLD_BOSS", &v271);
    thisa->m_nWorldBossStartBroadcast = Answer::Inifile::getIntValue(&ini, &v270, &v268);
    std::string::~string(&v270);
    std::allocator<char>::~allocator(&v271);
    std::string::~string(&v268);
    std::allocator<char>::~allocator(&v269);
    std::allocator<char>::allocator(&v273);
    std::string::string(&v272, "end_broadcast", &v273);
    std::allocator<char>::allocator(&v275);
    std::string::string(&v274, "WORLD_BOSS", &v275);
    thisa->m_nWorldBossEndBroadcast = Answer::Inifile::getIntValue(&ini, &v274, &v272);
    std::string::~string(&v274);
    std::allocator<char>::~allocator(&v275);
    std::string::~string(&v272);
    std::allocator<char>::~allocator(&v273);
    std::allocator<char>::allocator(&v277);
    std::string::string(&v276, "kill_broadcast", &v277);
    std::allocator<char>::allocator(&v279);
    std::string::string(&v278, "WORLD_BOSS", &v279);
    thisa->m_nWorldBossKillBroadcast = Answer::Inifile::getIntValue(&ini, &v278, &v276);
    std::string::~string(&v278);
    std::allocator<char>::~allocator(&v279);
    std::string::~string(&v276);
    std::allocator<char>::~allocator(&v277);
    std::allocator<char>::allocator(&v281);
    std::string::string(&v280, "count", &v281);
    std::allocator<char>::allocator(&v283);
    std::string::string(&v282, "WORLD_BOSS", &v283);
    nCount = Answer::Inifile::getIntValue(&ini, &v282, &v280);
    std::string::~string(&v282);
    std::allocator<char>::~allocator(&v283);
    std::string::~string(&v280);
    std::allocator<char>::~allocator(&v281);
    v284 = 0;
    std::vector<TimeArea>::resize(&thisa->m_vWorldBossMinute, nCount, 0);
    for ( i_1 = 0; i_1 < nCount; ++i_1 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "start_minute%d", i_1 + 1);
      v6 = std::vector<TimeArea>::operator[](&thisa->m_vWorldBossMinute, i_1);
      std::allocator<char>::allocator(&v286);
      std::string::string(&v285, szCol, &v286);
      std::allocator<char>::allocator(&v288);
      std::string::string(&v287, "WORLD_BOSS", &v288);
      v6->nStartTime = Answer::Inifile::getIntValue(&ini, &v287, &v285);
      std::string::~string(&v287);
      std::allocator<char>::~allocator(&v288);
      std::string::~string(&v285);
      std::allocator<char>::~allocator(&v286);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "end_minute%d", i_1 + 1);
      v7 = std::vector<TimeArea>::operator[](&thisa->m_vWorldBossMinute, i_1);
      std::allocator<char>::allocator(&v290);
      std::string::string(&v289, szCol, &v290);
      std::allocator<char>::allocator(&v292);
      std::string::string(&v291, "WORLD_BOSS", &v292);
      v7->nEndTime = Answer::Inifile::getIntValue(&ini, &v291, &v289);
      std::string::~string(&v291);
      std::allocator<char>::~allocator(&v292);
      std::string::~string(&v289);
      std::allocator<char>::~allocator(&v290);
    }
    std::allocator<char>::allocator(&v294);
    std::string::string(&v293, "mapid", &v294);
    std::allocator<char>::allocator(&v296);
    std::string::string(&v295, "WORLD_BOSS", &v296);
    thisa->m_MapId = Answer::Inifile::getIntValue(&ini, &v295, &v293);
    std::string::~string(&v295);
    std::allocator<char>::~allocator(&v296);
    std::string::~string(&v293);
    std::allocator<char>::~allocator(&v294);
    std::allocator<char>::allocator(&v298);
    std::string::string(&v297, "x", &v298);
    std::allocator<char>::allocator(&v300);
    std::string::string(&v299, "WORLD_BOSS", &v300);
    thisa->m_X = Answer::Inifile::getIntValue(&ini, &v299, &v297);
    std::string::~string(&v299);
    std::allocator<char>::~allocator(&v300);
    std::string::~string(&v297);
    std::allocator<char>::~allocator(&v298);
    std::allocator<char>::allocator(&v302);
    std::string::string(&v301, "y", &v302);
    std::allocator<char>::allocator(&v304);
    std::string::string(&v303, "WORLD_BOSS", &v304);
    thisa->m_Y = Answer::Inifile::getIntValue(&ini, &v303, &v301);
    std::string::~string(&v303);
    std::allocator<char>::~allocator(&v304);
    std::string::~string(&v301);
    std::allocator<char>::~allocator(&v302);
    std::allocator<char>::allocator(&v306);
    std::string::string(&v305, "mid", &v306);
    std::allocator<char>::allocator(&v308);
    std::string::string(&v307, "WORLD_BOSS", &v308);
    thisa->m_Mid = Answer::Inifile::getIntValue(&ini, &v307, &v305);
    std::string::~string(&v307);
    std::allocator<char>::~allocator(&v308);
    std::string::~string(&v305);
    std::allocator<char>::~allocator(&v306);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM) )
  {
    std::allocator<char>::allocator(&v310);
    std::string::string(&v309, "start_day", &v310);
    std::allocator<char>::allocator(&v312);
    std::string::string(&v311, "HUO_YUE_DU_SUM", &v312);
    thisa->m_vStartDay[7] = Answer::Inifile::getIntValue(&ini, &v311, &v309);
    std::string::~string(&v311);
    std::allocator<char>::~allocator(&v312);
    std::string::~string(&v309);
    std::allocator<char>::~allocator(&v310);
    std::allocator<char>::allocator(&v314);
    std::string::string(&v313, "end_day", &v314);
    std::allocator<char>::allocator(&v316);
    std::string::string(&v315, "HUO_YUE_DU_SUM", &v316);
    thisa->m_vEndDay[7] = Answer::Inifile::getIntValue(&ini, &v315, &v313);
    std::string::~string(&v315);
    std::allocator<char>::~allocator(&v316);
    std::string::~string(&v313);
    std::allocator<char>::~allocator(&v314);
    std::allocator<char>::allocator(&v318);
    std::string::string(&v317, "size", &v318);
    std::allocator<char>::allocator(&v320);
    std::string::string(&v319, "HUO_YUE_DU_SUM", &v320);
    thisa->m_nHuoYueDuSumSize = Answer::Inifile::getIntValue(&ini, &v319, &v317);
    std::string::~string(&v319);
    std::allocator<char>::~allocator(&v320);
    std::string::~string(&v317);
    std::allocator<char>::~allocator(&v318);
    std::vector<int>::resize(&thisa->m_vHuoYueDuSumLimit, thisa->m_nHuoYueDuSumSize, 0);
    std::vector<MemChrBag>::vector(&v321);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vHuoYueDuSumReward, thisa->m_nHuoYueDuSumSize, &v321);
    std::vector<MemChrBag>::~vector(&v321);
    for ( i_2 = 0; thisa->m_nHuoYueDuSumSize > i_2; ++i_2 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "value%d", i_2 + 1);
      v8 = std::vector<int>::operator[](&thisa->m_vHuoYueDuSumLimit, i_2);
      std::allocator<char>::allocator(&v323);
      std::string::string(&v322, szCol, &v323);
      std::allocator<char>::allocator(&v325);
      std::string::string(&v324, "HUO_YUE_DU_SUM", &v325);
      *v8 = Answer::Inifile::getIntValue(&ini, &v324, &v322);
      std::string::~string(&v324);
      std::allocator<char>::~allocator(&v325);
      std::string::~string(&v322);
      std::allocator<char>::~allocator(&v323);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_2 + 1);
      std::allocator<char>::allocator((char *)&v327.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v327.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v327.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v327.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v327.m_strMap._M_t._M_impl._M_header._M_right,
        "HUO_YUE_DU_SUM",
        (char *)&v327.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v327,
        (const std::string *const)&ini,
        (const std::string *const)&v327.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v326, (const std::string *const)&v327);
      v9 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vHuoYueDuSumReward, i_2);
      std::vector<MemChrBag>::operator=(v9, &v326);
      std::vector<MemChrBag>::~vector(&v326);
      std::string::~string(&v327);
      std::string::~string(&v327.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v327.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v327.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v327.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP) )
  {
    std::allocator<char>::allocator(&v328);
    std::string::string(&v327.m_currentSection, "start_day", &v328);
    std::allocator<char>::allocator(&v330);
    std::string::string(&v329, "DAILY_LIMIT_SHOP", &v330);
    thisa->m_vStartDay[8] = Answer::Inifile::getIntValue(&ini, &v329, &v327.m_currentSection);
    std::string::~string(&v329);
    std::allocator<char>::~allocator(&v330);
    std::string::~string(&v327.m_currentSection);
    std::allocator<char>::~allocator(&v328);
    std::allocator<char>::allocator(&v332);
    std::string::string(&v331, "end_day", &v332);
    std::allocator<char>::allocator(&v334);
    std::string::string(&v333, "DAILY_LIMIT_SHOP", &v334);
    thisa->m_vEndDay[8] = Answer::Inifile::getIntValue(&ini, &v333, &v331);
    std::string::~string(&v333);
    std::allocator<char>::~allocator(&v334);
    std::string::~string(&v331);
    std::allocator<char>::~allocator(&v332);
    std::allocator<char>::allocator((char *)&v336.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v336.m_strMap._M_t._M_impl._M_header._M_parent,
      "item",
      (char *)&v336.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v336.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v336.m_strMap._M_t._M_impl._M_header._M_right,
      "DAILY_LIMIT_SHOP",
      (char *)&v336.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v336,
      (const std::string *const)&ini,
      (const std::string *const)&v336.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v335, (const std::string *const)&v336);
    std::vector<MemChrBag>::operator=(&thisa->m_vDailyLimitShopItem, &v335);
    std::vector<MemChrBag>::~vector(&v335);
    std::string::~string(&v336);
    std::string::~string(&v336.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v336.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v336.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v336.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator(&v337);
    std::string::string(&v336.m_currentSection, "cost_type", &v337);
    std::allocator<char>::allocator(&v339);
    std::string::string(&v338, "DAILY_LIMIT_SHOP", &v339);
    thisa->m_nDailyLimitShopCostType = Answer::Inifile::getIntValue(&ini, &v338, &v336.m_currentSection);
    std::string::~string(&v338);
    std::allocator<char>::~allocator(&v339);
    std::string::~string(&v336.m_currentSection);
    std::allocator<char>::~allocator(&v337);
    std::allocator<char>::allocator(&v341);
    std::string::string(&v340, "cost_value", &v341);
    std::allocator<char>::allocator(&v343);
    std::string::string(&v342, "DAILY_LIMIT_SHOP", &v343);
    thisa->m_nDailyLimitShopCostValue = Answer::Inifile::getIntValue(&ini, &v342, &v340);
    std::string::~string(&v342);
    std::allocator<char>::~allocator(&v343);
    std::string::~string(&v340);
    std::allocator<char>::~allocator(&v341);
    std::allocator<char>::allocator(&v345);
    std::string::string(&v344, "limit", &v345);
    std::allocator<char>::allocator(&v347);
    std::string::string(&v346, "DAILY_LIMIT_SHOP", &v347);
    thisa->m_nDailyLimitShopLimit = Answer::Inifile::getIntValue(&ini, &v346, &v344);
    std::string::~string(&v346);
    std::allocator<char>::~allocator(&v347);
    std::string::~string(&v344);
    std::allocator<char>::~allocator(&v345);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM) )
  {
    std::allocator<char>::allocator(&v349);
    std::string::string(&v348, "start_day", &v349);
    std::allocator<char>::allocator(&v351);
    std::string::string(&v350, "LAND_SUM", &v351);
    thisa->m_vStartDay[9] = Answer::Inifile::getIntValue(&ini, &v350, &v348);
    std::string::~string(&v350);
    std::allocator<char>::~allocator(&v351);
    std::string::~string(&v348);
    std::allocator<char>::~allocator(&v349);
    std::allocator<char>::allocator(&v353);
    std::string::string(&v352, "end_day", &v353);
    std::allocator<char>::allocator(&v355);
    std::string::string(&v354, "LAND_SUM", &v355);
    thisa->m_vEndDay[9] = Answer::Inifile::getIntValue(&ini, &v354, &v352);
    std::string::~string(&v354);
    std::allocator<char>::~allocator(&v355);
    std::string::~string(&v352);
    std::allocator<char>::~allocator(&v353);
    std::vector<MemChrBag>::vector(&v356);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vLandSumGift, thisa->m_nEndDay, &v356);
    std::vector<MemChrBag>::~vector(&v356);
    for ( i_3 = 0; thisa->m_nEndDay > i_3; ++i_3 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "gift%d", i_3 + 1);
      std::allocator<char>::allocator((char *)&v358.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v358.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v358.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v358.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v358.m_strMap._M_t._M_impl._M_header._M_right,
        "LAND_SUM",
        (char *)&v358.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v358,
        (const std::string *const)&ini,
        (const std::string *const)&v358.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v357, (const std::string *const)&v358);
      v10 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vLandSumGift, i_3);
      std::vector<MemChrBag>::operator=(v10, &v357);
      std::vector<MemChrBag>::~vector(&v357);
      std::string::~string(&v358);
      std::string::~string(&v358.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v358.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v358.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v358.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME) )
  {
    std::allocator<char>::allocator(&v359);
    std::string::string(&v358.m_currentSection, "start_day", &v359);
    std::allocator<char>::allocator(&v361);
    std::string::string(&v360, "DAILY_ONLINE", &v361);
    thisa->m_vStartDay[10] = Answer::Inifile::getIntValue(&ini, &v360, &v358.m_currentSection);
    std::string::~string(&v360);
    std::allocator<char>::~allocator(&v361);
    std::string::~string(&v358.m_currentSection);
    std::allocator<char>::~allocator(&v359);
    std::allocator<char>::allocator(&v363);
    std::string::string(&v362, "end_day", &v363);
    std::allocator<char>::allocator(&v365);
    std::string::string(&v364, "DAILY_ONLINE", &v365);
    thisa->m_vEndDay[10] = Answer::Inifile::getIntValue(&ini, &v364, &v362);
    std::string::~string(&v364);
    std::allocator<char>::~allocator(&v365);
    std::string::~string(&v362);
    std::allocator<char>::~allocator(&v363);
    std::allocator<char>::allocator(&v367);
    std::string::string(&v366, "start_time", &v367);
    std::allocator<char>::allocator(&v369);
    std::string::string(&v368, "DAILY_ONLINE", &v369);
    thisa->m_nOnlineStartMinute = Answer::Inifile::getIntValue(&ini, &v368, &v366);
    std::string::~string(&v368);
    std::allocator<char>::~allocator(&v369);
    std::string::~string(&v366);
    std::allocator<char>::~allocator(&v367);
    std::allocator<char>::allocator(&v371);
    std::string::string(&v370, "end_time", &v371);
    std::allocator<char>::allocator(&v373);
    std::string::string(&v372, "DAILY_ONLINE", &v373);
    thisa->m_nOnlineEndMinute = Answer::Inifile::getIntValue(&ini, &v372, &v370);
    std::string::~string(&v372);
    std::allocator<char>::~allocator(&v373);
    std::string::~string(&v370);
    std::allocator<char>::~allocator(&v371);
    std::allocator<char>::allocator(&v375);
    std::string::string(&v374, "dis_time", &v375);
    std::allocator<char>::allocator(&v377);
    std::string::string(&v376, "DAILY_ONLINE", &v377);
    thisa->m_nOnlineTimeArea = 60 * Answer::Inifile::getIntValue(&ini, &v376, &v374);
    std::string::~string(&v376);
    std::allocator<char>::~allocator(&v377);
    std::string::~string(&v374);
    std::allocator<char>::~allocator(&v375);
    std::allocator<char>::allocator((char *)&v379.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v379.m_strMap._M_t._M_impl._M_header._M_parent,
      "reward",
      (char *)&v379.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v379.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v379.m_strMap._M_t._M_impl._M_header._M_right,
      "DAILY_ONLINE",
      (char *)&v379.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v379,
      (const std::string *const)&ini,
      (const std::string *const)&v379.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v378, (const std::string *const)&v379);
    std::vector<MemChrBag>::operator=(&thisa->m_vOnlineReward, &v378);
    std::vector<MemChrBag>::~vector(&v378);
    std::string::~string(&v379);
    std::string::~string(&v379.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v379.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v379.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v379.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator(&v380);
    std::string::string(&v379.m_currentSection, "max_count", &v380);
    std::allocator<char>::allocator(&v382);
    std::string::string(&v381, "DAILY_ONLINE", &v382);
    thisa->m_nMaxCount = Answer::Inifile::getIntValue(&ini, &v381, &v379.m_currentSection);
    std::string::~string(&v381);
    std::allocator<char>::~allocator(&v382);
    std::string::~string(&v379.m_currentSection);
    std::allocator<char>::~allocator(&v380);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_BEST_WISH) )
  {
    std::allocator<char>::allocator(&v384);
    std::string::string(&v383, "start_day", &v384);
    std::allocator<char>::allocator(&v386);
    std::string::string(&v385, "BEST_WISH", &v386);
    thisa->m_vStartDay[11] = Answer::Inifile::getIntValue(&ini, &v385, &v383);
    std::string::~string(&v385);
    std::allocator<char>::~allocator(&v386);
    std::string::~string(&v383);
    std::allocator<char>::~allocator(&v384);
    std::allocator<char>::allocator(&v388);
    std::string::string(&v387, "end_day", &v388);
    std::allocator<char>::allocator(&v390);
    std::string::string(&v389, "BEST_WISH", &v390);
    thisa->m_vEndDay[11] = Answer::Inifile::getIntValue(&ini, &v389, &v387);
    std::string::~string(&v389);
    std::allocator<char>::~allocator(&v390);
    std::string::~string(&v387);
    std::allocator<char>::~allocator(&v388);
    std::allocator<char>::allocator(&v392);
    std::string::string(&v391, "recharge", &v392);
    std::allocator<char>::allocator(&v394);
    std::string::string(&v393, "BEST_WISH", &v394);
    thisa->m_nWishRecharge = Answer::Inifile::getIntValue(&ini, &v393, &v391);
    std::string::~string(&v393);
    std::allocator<char>::~allocator(&v394);
    std::string::~string(&v391);
    std::allocator<char>::~allocator(&v392);
    std::allocator<char>::allocator((char *)&v396.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v396.m_strMap._M_t._M_impl._M_header._M_parent,
      "reward",
      (char *)&v396.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v396.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v396.m_strMap._M_t._M_impl._M_header._M_right,
      "BEST_WISH",
      (char *)&v396.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v396,
      (const std::string *const)&ini,
      (const std::string *const)&v396.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v395, (const std::string *const)&v396);
    std::vector<MemChrBag>::operator=(&thisa->m_vWishReward, &v395);
    std::vector<MemChrBag>::~vector(&v395);
    std::string::~string(&v396);
    std::string::~string(&v396.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v396.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v396.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v396.m_strMap._M_t._M_impl._M_header._M_left + 7);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
  {
    std::allocator<char>::allocator(&v397);
    std::string::string(&v396.m_currentSection, "start_day", &v397);
    std::allocator<char>::allocator(&v399);
    std::string::string(&v398, "XIAO_FEI_RANK", &v399);
    thisa->m_vStartDay[12] = Answer::Inifile::getIntValue(&ini, &v398, &v396.m_currentSection);
    std::string::~string(&v398);
    std::allocator<char>::~allocator(&v399);
    std::string::~string(&v396.m_currentSection);
    std::allocator<char>::~allocator(&v397);
    std::allocator<char>::allocator(&v401);
    std::string::string(&v400, "end_day", &v401);
    std::allocator<char>::allocator(&v403);
    std::string::string(&v402, "XIAO_FEI_RANK", &v403);
    thisa->m_vEndDay[12] = Answer::Inifile::getIntValue(&ini, &v402, &v400);
    std::string::~string(&v402);
    std::allocator<char>::~allocator(&v403);
    std::string::~string(&v400);
    std::allocator<char>::~allocator(&v401);
    std::allocator<char>::allocator(&v405);
    std::string::string(&v404, "size", &v405);
    std::allocator<char>::allocator(&v407);
    std::string::string(&v406, "XIAO_FEI_RANK", &v407);
    thisa->m_nXiaoFeiRankSize = Answer::Inifile::getIntValue(&ini, &v406, &v404);
    std::string::~string(&v406);
    std::allocator<char>::~allocator(&v407);
    std::string::~string(&v404);
    std::allocator<char>::~allocator(&v405);
    std::vector<int>::resize(&thisa->m_vXiaoFeiRankLimit, thisa->m_nXiaoFeiRankSize, 0);
    std::vector<int>::resize(&thisa->m_vXiaoFeiRankMail, thisa->m_nXiaoFeiRankSize, 0);
    std::vector<MemChrBag>::vector(&v408);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vXiaoFeiRankReward, thisa->m_nXiaoFeiRankSize, &v408);
    std::vector<MemChrBag>::~vector(&v408);
    for ( i_4 = 0; thisa->m_nXiaoFeiRankSize > i_4; ++i_4 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_4 + 1);
      v11 = std::vector<int>::operator[](&thisa->m_vXiaoFeiRankLimit, i_4);
      std::allocator<char>::allocator(&v410);
      std::string::string(&v409, szCol, &v410);
      std::allocator<char>::allocator(&v412);
      std::string::string(&v411, "XIAO_FEI_RANK", &v412);
      *v11 = Answer::Inifile::getIntValue(&ini, &v411, &v409);
      std::string::~string(&v411);
      std::allocator<char>::~allocator(&v412);
      std::string::~string(&v409);
      std::allocator<char>::~allocator(&v410);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_4 + 1);
      v12 = std::vector<int>::operator[](&thisa->m_vXiaoFeiRankMail, i_4);
      std::allocator<char>::allocator(&v414);
      std::string::string(&v413, szCol, &v414);
      std::allocator<char>::allocator(&v416);
      std::string::string(&v415, "XIAO_FEI_RANK", &v416);
      *v12 = Answer::Inifile::getIntValue(&ini, &v415, &v413);
      std::string::~string(&v415);
      std::allocator<char>::~allocator(&v416);
      std::string::~string(&v413);
      std::allocator<char>::~allocator(&v414);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_4 + 1);
      std::allocator<char>::allocator((char *)&v418.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v418.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v418.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v418.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v418.m_strMap._M_t._M_impl._M_header._M_right,
        "XIAO_FEI_RANK",
        (char *)&v418.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v418,
        (const std::string *const)&ini,
        (const std::string *const)&v418.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v417, (const std::string *const)&v418);
      v13 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vXiaoFeiRankReward, i_4);
      std::vector<MemChrBag>::operator=(v13, &v417);
      std::vector<MemChrBag>::~vector(&v417);
      std::string::~string(&v418);
      std::string::~string(&v418.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v418.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v418.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v418.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW) )
  {
    std::allocator<char>::allocator(&v419);
    std::string::string(&v418.m_currentSection, "start_day", &v419);
    std::allocator<char>::allocator(&v421);
    std::string::string(&v420, "XIAO_FEI_DRAW", &v421);
    thisa->m_vStartDay[13] = Answer::Inifile::getIntValue(&ini, &v420, &v418.m_currentSection);
    std::string::~string(&v420);
    std::allocator<char>::~allocator(&v421);
    std::string::~string(&v418.m_currentSection);
    std::allocator<char>::~allocator(&v419);
    std::allocator<char>::allocator(&v423);
    std::string::string(&v422, "end_day", &v423);
    std::allocator<char>::allocator(&v425);
    std::string::string(&v424, "XIAO_FEI_DRAW", &v425);
    thisa->m_vEndDay[13] = Answer::Inifile::getIntValue(&ini, &v424, &v422);
    std::string::~string(&v424);
    std::allocator<char>::~allocator(&v425);
    std::string::~string(&v422);
    std::allocator<char>::~allocator(&v423);
    std::allocator<char>::allocator(&v427);
    std::string::string(&v426, "size", &v427);
    std::allocator<char>::allocator(&v429);
    std::string::string(&v428, "XIAO_FEI_DRAW", &v429);
    thisa->m_nXiaoFeiDrawSize = Answer::Inifile::getIntValue(&ini, &v428, &v426);
    std::string::~string(&v428);
    std::allocator<char>::~allocator(&v429);
    std::string::~string(&v426);
    std::allocator<char>::~allocator(&v427);
    std::vector<int>::reserve(&thisa->m_nXiaoFeiDrawValue, thisa->m_nXiaoFeiDrawSize);
    for ( i_5 = 0; thisa->m_nXiaoFeiDrawSize > i_5; ++i_5 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "value%d", i_5 + 1);
      std::allocator<char>::allocator(&v432);
      std::string::string(&v431, szCol, &v432);
      std::allocator<char>::allocator(&v434);
      std::string::string(&v433, "XIAO_FEI_DRAW", &v434);
      IntValue = Answer::Inifile::getIntValue(&ini, &v433, &v431);
      std::vector<int>::push_back(&thisa->m_nXiaoFeiDrawValue, &IntValue);
      std::string::~string(&v433);
      std::allocator<char>::~allocator(&v434);
      std::string::~string(&v431);
      std::allocator<char>::~allocator(&v432);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE) )
  {
    std::allocator<char>::allocator(&v436);
    std::string::string(&v435, "start_day", &v436);
    std::allocator<char>::allocator(&v438);
    std::string::string(&v437, "MO_YU_SHI_JIE", &v438);
    thisa->m_vStartDay[14] = Answer::Inifile::getIntValue(&ini, &v437, &v435);
    std::string::~string(&v437);
    std::allocator<char>::~allocator(&v438);
    std::string::~string(&v435);
    std::allocator<char>::~allocator(&v436);
    std::allocator<char>::allocator(&v440);
    std::string::string(&v439, "end_day", &v440);
    std::allocator<char>::allocator(&v442);
    std::string::string(&v441, "MO_YU_SHI_JIE", &v442);
    thisa->m_vEndDay[14] = Answer::Inifile::getIntValue(&ini, &v441, &v439);
    std::string::~string(&v441);
    std::allocator<char>::~allocator(&v442);
    std::string::~string(&v439);
    std::allocator<char>::~allocator(&v440);
    std::allocator<char>::allocator(&v444);
    std::string::string(&v443, "icon", &v444);
    std::allocator<char>::allocator(&v446);
    std::string::string(&v445, "MO_YU_SHI_JIE", &v446);
    thisa->m_nMoYuShiJieIconId = Answer::Inifile::getIntValue(&ini, &v445, &v443);
    std::string::~string(&v445);
    std::allocator<char>::~allocator(&v446);
    std::string::~string(&v443);
    std::allocator<char>::~allocator(&v444);
    std::allocator<char>::allocator(&v448);
    std::string::string(&v447, "drop_size", &v448);
    std::allocator<char>::allocator(&v450);
    std::string::string(&v449, "MO_YU_SHI_JIE", &v450);
    thisa->m_nMoYuShiJieDropSize = Answer::Inifile::getIntValue(&ini, &v449, &v447);
    std::string::~string(&v449);
    std::allocator<char>::~allocator(&v450);
    std::string::~string(&v447);
    std::allocator<char>::~allocator(&v448);
    std::vector<MemChrBag>::vector(&v451);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vMoYuShiJieDrop, thisa->m_nMoYuShiJieDropSize, &v451);
    std::vector<MemChrBag>::~vector(&v451);
    for ( i_6 = 0; thisa->m_nMoYuShiJieDropSize > i_6; ++i_6 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "drop_%d", i_6 + 1);
      std::allocator<char>::allocator((char *)&v453.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v453.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v453.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v453.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v453.m_strMap._M_t._M_impl._M_header._M_right,
        "MO_YU_SHI_JIE",
        (char *)&v453.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v453,
        (const std::string *const)&ini,
        (const std::string *const)&v453.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v452, (const std::string *const)&v453);
      v14 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vMoYuShiJieDrop, i_6);
      std::vector<MemChrBag>::operator=(v14, &v452);
      std::vector<MemChrBag>::~vector(&v452);
      std::string::~string(&v453);
      std::string::~string(&v453.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v453.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v453.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v453.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE_2) )
  {
    std::allocator<char>::allocator(&v454);
    std::string::string(&v453.m_currentSection, "start_day", &v454);
    std::allocator<char>::allocator(&v456);
    std::string::string(&v455, "DAILY_RECHARGE_2", &v456);
    thisa->m_vStartDay[15] = Answer::Inifile::getIntValue(&ini, &v455, &v453.m_currentSection);
    std::string::~string(&v455);
    std::allocator<char>::~allocator(&v456);
    std::string::~string(&v453.m_currentSection);
    std::allocator<char>::~allocator(&v454);
    std::allocator<char>::allocator(&v458);
    std::string::string(&v457, "end_day", &v458);
    std::allocator<char>::allocator(&v460);
    std::string::string(&v459, "DAILY_RECHARGE_2", &v460);
    thisa->m_vEndDay[15] = Answer::Inifile::getIntValue(&ini, &v459, &v457);
    std::string::~string(&v459);
    std::allocator<char>::~allocator(&v460);
    std::string::~string(&v457);
    std::allocator<char>::~allocator(&v458);
    std::allocator<char>::allocator(&v462);
    std::string::string(&v461, "size", &v462);
    std::allocator<char>::allocator(&v464);
    std::string::string(&v463, "DAILY_RECHARGE_2", &v464);
    thisa->m_nDailyRechargeSize = Answer::Inifile::getIntValue(&ini, &v463, &v461);
    std::string::~string(&v463);
    std::allocator<char>::~allocator(&v464);
    std::string::~string(&v461);
    std::allocator<char>::~allocator(&v462);
    std::vector<int>::resize(&thisa->m_vDailyRechargeLimit, thisa->m_nDailyRechargeSize, 0);
    std::vector<int>::resize(&thisa->m_vDailyRechargeBroad, thisa->m_nDailyRechargeSize, 0);
    std::vector<MemChrBag>::vector(&v465);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vDailyRechargeReward, thisa->m_nDailyRechargeSize, &v465);
    std::vector<MemChrBag>::~vector(&v465);
    for ( i_7 = 0; thisa->m_nDailyRechargeSize > i_7; ++i_7 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_7 + 1);
      v15 = std::vector<int>::operator[](&thisa->m_vDailyRechargeLimit, i_7);
      std::allocator<char>::allocator(&v467);
      std::string::string(&v466, szCol, &v467);
      std::allocator<char>::allocator(&v469);
      std::string::string(&v468, "DAILY_RECHARGE_2", &v469);
      *v15 = Answer::Inifile::getIntValue(&ini, &v468, &v466);
      std::string::~string(&v468);
      std::allocator<char>::~allocator(&v469);
      std::string::~string(&v466);
      std::allocator<char>::~allocator(&v467);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_7 + 1);
      v16 = std::vector<int>::operator[](&thisa->m_vDailyRechargeBroad, i_7);
      std::allocator<char>::allocator(&v471);
      std::string::string(&v470, szCol, &v471);
      std::allocator<char>::allocator(&v473);
      std::string::string(&v472, "DAILY_RECHARGE_2", &v473);
      *v16 = Answer::Inifile::getIntValue(&ini, &v472, &v470);
      std::string::~string(&v472);
      std::allocator<char>::~allocator(&v473);
      std::string::~string(&v470);
      std::allocator<char>::~allocator(&v471);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_7 + 1);
      std::allocator<char>::allocator((char *)&v475.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v475.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v475.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v475.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v475.m_strMap._M_t._M_impl._M_header._M_right,
        "DAILY_RECHARGE_2",
        (char *)&v475.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v475,
        (const std::string *const)&ini,
        (const std::string *const)&v475.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v474, (const std::string *const)&v475);
      v17 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vDailyRechargeReward, i_7);
      std::vector<MemChrBag>::operator=(v17, &v474);
      std::vector<MemChrBag>::~vector(&v474);
      std::string::~string(&v475);
      std::string::~string(&v475.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v475.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v475.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v475.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK) )
  {
    std::allocator<char>::allocator(&v476);
    std::string::string(&v475.m_currentSection, "start_day", &v476);
    std::allocator<char>::allocator(&v478);
    std::string::string(&v477, "XIAO_FEI_SUM_RANK", &v478);
    thisa->m_vStartDay[16] = Answer::Inifile::getIntValue(&ini, &v477, &v475.m_currentSection);
    std::string::~string(&v477);
    std::allocator<char>::~allocator(&v478);
    std::string::~string(&v475.m_currentSection);
    std::allocator<char>::~allocator(&v476);
    std::allocator<char>::allocator(&v480);
    std::string::string(&v479, "end_day", &v480);
    std::allocator<char>::allocator(&v482);
    std::string::string(&v481, "XIAO_FEI_SUM_RANK", &v482);
    thisa->m_vEndDay[16] = Answer::Inifile::getIntValue(&ini, &v481, &v479);
    std::string::~string(&v481);
    std::allocator<char>::~allocator(&v482);
    std::string::~string(&v479);
    std::allocator<char>::~allocator(&v480);
    std::allocator<char>::allocator(&v484);
    std::string::string(&v483, "size", &v484);
    std::allocator<char>::allocator(&v486);
    std::string::string(&v485, "XIAO_FEI_SUM_RANK", &v486);
    thisa->m_nXiaoFeiSumRankSize = Answer::Inifile::getIntValue(&ini, &v485, &v483);
    std::string::~string(&v485);
    std::allocator<char>::~allocator(&v486);
    std::string::~string(&v483);
    std::allocator<char>::~allocator(&v484);
    std::allocator<char>::allocator(&v488);
    std::string::string(&v487, "limit", &v488);
    std::allocator<char>::allocator(&v490);
    std::string::string(&v489, "XIAO_FEI_SUM_RANK", &v490);
    thisa->m_nXiaoFeiSumRankLimit = Answer::Inifile::getIntValue(&ini, &v489, &v487);
    std::string::~string(&v489);
    std::allocator<char>::~allocator(&v490);
    std::string::~string(&v487);
    std::allocator<char>::~allocator(&v488);
    std::vector<int>::resize(&thisa->m_vXiaoFeiSumRankMail, thisa->m_nXiaoFeiSumRankSize, 0);
    std::vector<MemChrBag>::vector(&v491);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vXiaoFeiSumRankReward, thisa->m_nXiaoFeiSumRankSize, &v491);
    std::vector<MemChrBag>::~vector(&v491);
    for ( i_8 = 0; thisa->m_nXiaoFeiSumRankSize > i_8; ++i_8 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_8 + 1);
      v18 = std::vector<int>::operator[](&thisa->m_vXiaoFeiSumRankMail, i_8);
      std::allocator<char>::allocator(&v493);
      std::string::string(&v492, szCol, &v493);
      std::allocator<char>::allocator(&v495);
      std::string::string(&v494, "XIAO_FEI_SUM_RANK", &v495);
      *v18 = Answer::Inifile::getIntValue(&ini, &v494, &v492);
      std::string::~string(&v494);
      std::allocator<char>::~allocator(&v495);
      std::string::~string(&v492);
      std::allocator<char>::~allocator(&v493);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_8 + 1);
      std::allocator<char>::allocator((char *)&v497.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v497.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v497.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v497.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v497.m_strMap._M_t._M_impl._M_header._M_right,
        "XIAO_FEI_SUM_RANK",
        (char *)&v497.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v497,
        (const std::string *const)&ini,
        (const std::string *const)&v497.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v496, (const std::string *const)&v497);
      v19 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vXiaoFeiSumRankReward, i_8);
      std::vector<MemChrBag>::operator=(v19, &v496);
      std::vector<MemChrBag>::~vector(&v496);
      std::string::~string(&v497);
      std::string::~string(&v497.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v497.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v497.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v497.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_GIFT_SHOP) )
  {
    std::allocator<char>::allocator(&v498);
    std::string::string(&v497.m_currentSection, "start_day", &v498);
    std::allocator<char>::allocator(&v500);
    std::string::string(&v499, "GIFT_SHOP", &v500);
    thisa->m_vStartDay[17] = Answer::Inifile::getIntValue(&ini, &v499, &v497.m_currentSection);
    std::string::~string(&v499);
    std::allocator<char>::~allocator(&v500);
    std::string::~string(&v497.m_currentSection);
    std::allocator<char>::~allocator(&v498);
    std::allocator<char>::allocator(&v502);
    std::string::string(&v501, "end_day", &v502);
    std::allocator<char>::allocator(&v504);
    std::string::string(&v503, "GIFT_SHOP", &v504);
    thisa->m_vEndDay[17] = Answer::Inifile::getIntValue(&ini, &v503, &v501);
    std::string::~string(&v503);
    std::allocator<char>::~allocator(&v504);
    std::string::~string(&v501);
    std::allocator<char>::~allocator(&v502);
    nDaySize = thisa->m_vEndDay[17] - thisa->m_vStartDay[17];
    std::allocator<char>::allocator(&v506);
    std::string::string(&v505, "size", &v506);
    std::allocator<char>::allocator(&v508);
    std::string::string(&v507, "GIFT_SHOP", &v508);
    thisa->m_nGiftShopSize = Answer::Inifile::getIntValue(&ini, &v507, &v505);
    std::string::~string(&v507);
    std::allocator<char>::~allocator(&v508);
    std::string::~string(&v505);
    std::allocator<char>::~allocator(&v506);
    std::vector<ShopGoods>::vector(&v509);
    std::vector<std::vector<ShopGoods>>::resize(&thisa->m_vGiftShopGoods, nDaySize, &v509);
    std::vector<ShopGoods>::~vector(&v509);
    for ( i_9 = 0; i_9 < nDaySize; ++i_9 )
    {
      memset(&v510, 0, 28);
      ShopGoods::ShopGoods(&v510);
      m_nGiftShopSize = thisa->m_nGiftShopSize;
      v21 = std::vector<std::vector<ShopGoods>>::operator[](&thisa->m_vGiftShopGoods, i_9);
      std::vector<ShopGoods>::resize(v21, m_nGiftShopSize, &v510);
      ShopGoods::~ShopGoods(&v510);
      for ( j = 0; thisa->m_nGiftShopSize > j; ++j )
      {
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "price_%d_%d", i_9 + 1, j + 1);
        v22 = j;
        v23 = std::vector<std::vector<ShopGoods>>::operator[](&thisa->m_vGiftShopGoods, i_9);
        v24 = std::vector<ShopGoods>::operator[](v23, v22);
        std::allocator<char>::allocator(&v512);
        std::string::string(&v511, szCol, &v512);
        std::allocator<char>::allocator(&v514);
        std::string::string(&v513, "GIFT_SHOP", &v514);
        v24->nPrice = Answer::Inifile::getIntValue(&ini, &v513, &v511);
        std::string::~string(&v513);
        std::allocator<char>::~allocator(&v514);
        std::string::~string(&v511);
        std::allocator<char>::~allocator(&v512);
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "goods_%d_%d", i_9 + 1, j + 1);
        std::allocator<char>::allocator((char *)&v516.m_strMap._M_t._M_impl._M_header._M_left + 7);
        std::string::string(
          &v516.m_strMap._M_t._M_impl._M_header._M_parent,
          szCol,
          (char *)&v516.m_strMap._M_t._M_impl._M_header._M_left + 7);
        std::allocator<char>::allocator((char *)&v516.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::string(
          &v516.m_strMap._M_t._M_impl._M_header._M_right,
          "GIFT_SHOP",
          (char *)&v516.m_strMap._M_t._M_impl._M_node_count + 7);
        Answer::Inifile::getStrValue(
          &v516,
          (const std::string *const)&ini,
          (const std::string *const)&v516.m_strMap._M_t._M_impl._M_header._M_right);
        CItemHelper::parseItemVectorString(&v515, (const std::string *const)&v516);
        v25 = j;
        v26 = std::vector<std::vector<ShopGoods>>::operator[](&thisa->m_vGiftShopGoods, i_9);
        v27 = std::vector<ShopGoods>::operator[](v26, v25);
        std::vector<MemChrBag>::operator=(&v27->vItem, &v515);
        std::vector<MemChrBag>::~vector(&v515);
        std::string::~string(&v516);
        std::string::~string(&v516.m_strMap._M_t._M_impl._M_header._M_right);
        std::allocator<char>::~allocator((char *)&v516.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::~string(&v516.m_strMap._M_t._M_impl._M_header._M_parent);
        std::allocator<char>::~allocator((char *)&v516.m_strMap._M_t._M_impl._M_header._M_left + 7);
      }
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG) )
  {
    std::allocator<char>::allocator(&v517);
    std::string::string(&v516.m_currentSection, "start_day", &v517);
    std::allocator<char>::allocator(&v519);
    std::string::string(&v518, "CHOU_JIANG", &v519);
    thisa->m_vStartDay[18] = Answer::Inifile::getIntValue(&ini, &v518, &v516.m_currentSection);
    std::string::~string(&v518);
    std::allocator<char>::~allocator(&v519);
    std::string::~string(&v516.m_currentSection);
    std::allocator<char>::~allocator(&v517);
    std::allocator<char>::allocator(&v521);
    std::string::string(&v520, "end_day", &v521);
    std::allocator<char>::allocator(&v523);
    std::string::string(&v522, "CHOU_JIANG", &v523);
    thisa->m_vEndDay[18] = Answer::Inifile::getIntValue(&ini, &v522, &v520);
    std::string::~string(&v522);
    std::allocator<char>::~allocator(&v523);
    std::string::~string(&v520);
    std::allocator<char>::~allocator(&v521);
    std::allocator<char>::allocator(&v525);
    std::string::string(&v524, "Type", &v525);
    std::allocator<char>::allocator(&v527);
    std::string::string(&v526, "CHOU_JIANG", &v527);
    thisa->m_ChouJiangType = Answer::Inifile::getIntValue(&ini, &v526, &v524);
    std::string::~string(&v526);
    std::allocator<char>::~allocator(&v527);
    std::string::~string(&v524);
    std::allocator<char>::~allocator(&v525);
    std::allocator<char>::allocator(&v529);
    std::string::string(&v528, "times", &v529);
    std::allocator<char>::allocator(&v531);
    std::string::string(&v530, "CHOU_JIANG", &v531);
    thisa->m_ChouJiangCount = Answer::Inifile::getIntValue(&ini, &v530, &v528);
    std::string::~string(&v530);
    std::allocator<char>::~allocator(&v531);
    std::string::~string(&v528);
    std::allocator<char>::~allocator(&v529);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
  {
    std::allocator<char>::allocator(&v533);
    std::string::string(&v532, "start_day", &v533);
    std::allocator<char>::allocator(&v535);
    std::string::string(&v534, "FA_BAO_BACK", &v535);
    thisa->m_vStartDay[19] = Answer::Inifile::getIntValue(&ini, &v534, &v532);
    std::string::~string(&v534);
    std::allocator<char>::~allocator(&v535);
    std::string::~string(&v532);
    std::allocator<char>::~allocator(&v533);
    std::allocator<char>::allocator(&v537);
    std::string::string(&v536, "end_day", &v537);
    std::allocator<char>::allocator(&v539);
    std::string::string(&v538, "FA_BAO_BACK", &v539);
    thisa->m_vEndDay[19] = Answer::Inifile::getIntValue(&ini, &v538, &v536);
    std::string::~string(&v538);
    std::allocator<char>::~allocator(&v539);
    std::string::~string(&v536);
    std::allocator<char>::~allocator(&v537);
    std::allocator<char>::allocator(&v541);
    std::string::string(&v540, "fa_bao_type", &v541);
    std::allocator<char>::allocator(&v543);
    std::string::string(&v542, "FA_BAO_BACK", &v543);
    thisa->m_FaBaoType = Answer::Inifile::getIntValue(&ini, &v542, &v540);
    std::string::~string(&v542);
    std::allocator<char>::~allocator(&v543);
    std::string::~string(&v540);
    std::allocator<char>::~allocator(&v541);
    std::allocator<char>::allocator(&v545);
    std::string::string(&v544, "nSize", &v545);
    std::allocator<char>::allocator(&v547);
    std::string::string(&v546, "FA_BAO_BACK", &v547);
    thisa->m_nSize = Answer::Inifile::getIntValue(&ini, &v546, &v544);
    std::string::~string(&v546);
    std::allocator<char>::~allocator(&v547);
    std::string::~string(&v544);
    std::allocator<char>::~allocator(&v545);
    std::vector<int>::resize(&thisa->m_NeedValue, thisa->m_nSize, 0);
    v548.itemId = 0;
    v548.itemClass = 0;
    v548.itemCount = 0;
    v548.bind = 0;
    v548.endTime = 0;
    v548.srcId = 0;
    *(_OWORD *)&v152.itemId = *(_OWORD *)&v548.itemId;
    *(_OWORD *)&v152.endTime = *(unsigned __int64 *)&v548.endTime;
    std::vector<MemChrBag>::resize(&thisa->m_BackItem, thisa->m_nSize, v152);
    for ( i_10 = 0; thisa->m_nSize > i_10; ++i_10 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "need_value%d", i_10 + 1);
      v28 = std::vector<int>::operator[](&thisa->m_NeedValue, i_10);
      std::allocator<char>::allocator(&v550);
      std::string::string(&v549, szCol, &v550);
      std::allocator<char>::allocator(&v552);
      std::string::string(&v551, "FA_BAO_BACK", &v552);
      *v28 = Answer::Inifile::getIntValue(&ini, &v551, &v549);
      std::string::~string(&v551);
      std::allocator<char>::~allocator(&v552);
      std::string::~string(&v549);
      std::allocator<char>::~allocator(&v550);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "back_item%d", i_10 + 1);
      v29 = std::vector<MemChrBag>::operator[](&thisa->m_BackItem, i_10);
      std::allocator<char>::allocator((char *)&v553.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v553.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v553.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v553.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v553.m_strMap._M_t._M_impl._M_header._M_right,
        "FA_BAO_BACK",
        (char *)&v553.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v553,
        (const std::string *const)&ini,
        (const std::string *const)&v553.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemString(&v155, (const std::string *const)&v553);
      *v29 = v155;
      std::string::~string(&v553);
      std::string::~string(&v553.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v553.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v553.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v553.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP) )
  {
    std::allocator<char>::allocator(&v554);
    std::string::string(&v553.m_currentSection, "start_day", &v554);
    std::allocator<char>::allocator(&v556);
    std::string::string(&v555, "MYSTERY_SHOP", &v556);
    v30 = Answer::Inifile::getIntValue(&ini, &v555, &v553.m_currentSection);
    thisa->m_vStartDay[20] = v30;
    std::string::~string(&v555);
    std::allocator<char>::~allocator(&v556);
    std::string::~string(&v553.m_currentSection);
    std::allocator<char>::~allocator(&v554);
    std::allocator<char>::allocator(&v558);
    std::string::string(&v557, "end_day", &v558);
    std::allocator<char>::allocator(&v560);
    std::string::string(&v559, "MYSTERY_SHOP", &v560);
    v31 = Answer::Inifile::getIntValue(&ini, &v559, &v557);
    thisa->m_vEndDay[20] = v31;
    std::string::~string(&v559);
    std::allocator<char>::~allocator(&v560);
    std::string::~string(&v557);
    std::allocator<char>::~allocator(&v558);
    std::allocator<char>::allocator(&v562);
    std::string::string(&v561, "refresh_broadcast", &v562);
    std::allocator<char>::allocator(&v564);
    std::string::string(&v563, "MYSTERY_SHOP", &v564);
    v32 = Answer::Inifile::getIntValue(&ini, &v563, &v561);
    thisa->m_nMysteryShopRefreshBroad = v32;
    std::string::~string(&v563);
    std::allocator<char>::~allocator(&v564);
    std::string::~string(&v561);
    std::allocator<char>::~allocator(&v562);
    std::allocator<char>::allocator((char *)&v565.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v565.m_strMap._M_t._M_impl._M_header._M_parent,
      "refresh_cost",
      (char *)&v565.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v565.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v565.m_strMap._M_t._M_impl._M_header._M_right,
      "MYSTERY_SHOP",
      (char *)&v565.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v565,
      (const std::string *const)&ini,
      (const std::string *const)&v565.m_strMap._M_t._M_impl._M_header._M_right);
    v33 = thisa;
    v1051 = CItemHelper::parseItemDataString((const std::string *const)&v565);
    LODWORD(v151) = v1051.m_nId;
    BYTE4(v151) = v1051.m_nClass;
    *(_QWORD *)&v33->m_sMysteryShopRefreshCost.m_nId = v151;
    v33->m_sMysteryShopRefreshCost.m_nCount = v1051.m_nCount;
    std::string::~string(&v565);
    std::string::~string(&v565.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v565.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v565.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v565.m_strMap._M_t._M_impl._M_header._M_left + 7);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_GIFT) )
  {
    std::allocator<char>::allocator(&v566);
    std::string::string(&v565.m_currentSection, "start_day", &v566);
    std::allocator<char>::allocator(&v568);
    std::string::string(&v567, "RECHARGE_SUM_GIFT", &v568);
    v34 = Answer::Inifile::getIntValue(&ini, &v567, &v565.m_currentSection);
    thisa->m_vStartDay[21] = v34;
    std::string::~string(&v567);
    std::allocator<char>::~allocator(&v568);
    std::string::~string(&v565.m_currentSection);
    std::allocator<char>::~allocator(&v566);
    std::allocator<char>::allocator(&v570);
    std::string::string(&v569, "end_day", &v570);
    std::allocator<char>::allocator(&v572);
    std::string::string(&v571, "RECHARGE_SUM_GIFT", &v572);
    v35 = Answer::Inifile::getIntValue(&ini, &v571, &v569);
    thisa->m_vEndDay[21] = v35;
    std::string::~string(&v571);
    std::allocator<char>::~allocator(&v572);
    std::string::~string(&v569);
    std::allocator<char>::~allocator(&v570);
    std::allocator<char>::allocator(&v574);
    std::string::string(&v573, "size", &v574);
    std::allocator<char>::allocator(&v576);
    std::string::string(&v575, "RECHARGE_SUM_GIFT", &v576);
    v36 = Answer::Inifile::getIntValue(&ini, &v575, &v573);
    thisa->m_nRechargeSumSize = v36;
    std::string::~string(&v575);
    std::allocator<char>::~allocator(&v576);
    std::string::~string(&v573);
    std::allocator<char>::~allocator(&v574);
    std::vector<int>::resize(&thisa->m_vRechargeSumLimit, thisa->m_nRechargeSumSize, 0);
    std::vector<MemChrBag>::vector(&v577);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vRechargeSumReward, thisa->m_nRechargeSumSize, &v577);
    std::vector<MemChrBag>::~vector(&v577);
    std::vector<int>::resize(&thisa->m_vRechargeSumBroadcast, thisa->m_nRechargeSumSize, 0);
    for ( i_11 = 0; thisa->m_nRechargeSumSize > i_11; ++i_11 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_11 + 1);
      v37 = std::vector<int>::operator[](&thisa->m_vRechargeSumLimit, i_11);
      std::allocator<char>::allocator(&v579);
      std::string::string(&v578, szCol, &v579);
      std::allocator<char>::allocator(&v581);
      std::string::string(&v580, "RECHARGE_SUM_GIFT", &v581);
      *v37 = Answer::Inifile::getIntValue(&ini, &v580, &v578);
      std::string::~string(&v580);
      std::allocator<char>::~allocator(&v581);
      std::string::~string(&v578);
      std::allocator<char>::~allocator(&v579);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_11 + 1);
      std::allocator<char>::allocator((char *)&v583.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v583.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v583.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v583.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v583.m_strMap._M_t._M_impl._M_header._M_right,
        "RECHARGE_SUM_GIFT",
        (char *)&v583.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v583,
        (const std::string *const)&ini,
        (const std::string *const)&v583.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v582, (const std::string *const)&v583);
      v38 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vRechargeSumReward, i_11);
      std::vector<MemChrBag>::operator=(v38, &v582);
      std::vector<MemChrBag>::~vector(&v582);
      std::string::~string(&v583);
      std::string::~string(&v583.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v583.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v583.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v583.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_11 + 1);
      v39 = std::vector<int>::operator[](&thisa->m_vRechargeSumBroadcast, i_11);
      std::allocator<char>::allocator(&v584);
      std::string::string(&v583.m_currentSection, szCol, &v584);
      std::allocator<char>::allocator(&v586);
      std::string::string(&v585, "RECHARGE_SUM_GIFT", &v586);
      *v39 = Answer::Inifile::getIntValue(&ini, &v585, &v583.m_currentSection);
      std::string::~string(&v585);
      std::allocator<char>::~allocator(&v586);
      std::string::~string(&v583.m_currentSection);
      std::allocator<char>::~allocator(&v584);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT) )
  {
    std::allocator<char>::allocator(&v588);
    std::string::string(&v587, "start_day", &v588);
    std::allocator<char>::allocator(&v590);
    std::string::string(&v589, "XIAO_FEI_SUM_GIFT", &v590);
    v40 = Answer::Inifile::getIntValue(&ini, &v589, &v587);
    thisa->m_vStartDay[22] = v40;
    std::string::~string(&v589);
    std::allocator<char>::~allocator(&v590);
    std::string::~string(&v587);
    std::allocator<char>::~allocator(&v588);
    std::allocator<char>::allocator(&v592);
    std::string::string(&v591, "end_day", &v592);
    std::allocator<char>::allocator(&v594);
    std::string::string(&v593, "XIAO_FEI_SUM_GIFT", &v594);
    v41 = Answer::Inifile::getIntValue(&ini, &v593, &v591);
    thisa->m_vEndDay[22] = v41;
    std::string::~string(&v593);
    std::allocator<char>::~allocator(&v594);
    std::string::~string(&v591);
    std::allocator<char>::~allocator(&v592);
    std::allocator<char>::allocator(&v596);
    std::string::string(&v595, "size", &v596);
    std::allocator<char>::allocator(&v598);
    std::string::string(&v597, "XIAO_FEI_SUM_GIFT", &v598);
    v42 = Answer::Inifile::getIntValue(&ini, &v597, &v595);
    thisa->m_nXiaoFeiSumSize = v42;
    std::string::~string(&v597);
    std::allocator<char>::~allocator(&v598);
    std::string::~string(&v595);
    std::allocator<char>::~allocator(&v596);
    std::vector<int>::resize(&thisa->m_vXiaoFeiSumLimit, thisa->m_nXiaoFeiSumSize, 0);
    std::vector<MemChrBag>::vector(&v599);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vXiaoFeiSumReward, thisa->m_nXiaoFeiSumSize, &v599);
    std::vector<MemChrBag>::~vector(&v599);
    std::vector<int>::resize(&thisa->m_vXiaoFeiSumBroadcast, thisa->m_nXiaoFeiSumSize, 0);
    for ( i_12 = 0; thisa->m_nXiaoFeiSumSize > i_12; ++i_12 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_12 + 1);
      v43 = std::vector<int>::operator[](&thisa->m_vXiaoFeiSumLimit, i_12);
      std::allocator<char>::allocator(&v601);
      std::string::string(&v600, szCol, &v601);
      std::allocator<char>::allocator(&v603);
      std::string::string(&v602, "XIAO_FEI_SUM_GIFT", &v603);
      *v43 = Answer::Inifile::getIntValue(&ini, &v602, &v600);
      std::string::~string(&v602);
      std::allocator<char>::~allocator(&v603);
      std::string::~string(&v600);
      std::allocator<char>::~allocator(&v601);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_12 + 1);
      std::allocator<char>::allocator((char *)&v605.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v605.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v605.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v605.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v605.m_strMap._M_t._M_impl._M_header._M_right,
        "XIAO_FEI_SUM_GIFT",
        (char *)&v605.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v605,
        (const std::string *const)&ini,
        (const std::string *const)&v605.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v604, (const std::string *const)&v605);
      v44 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vXiaoFeiSumReward, i_12);
      std::vector<MemChrBag>::operator=(v44, &v604);
      std::vector<MemChrBag>::~vector(&v604);
      std::string::~string(&v605);
      std::string::~string(&v605.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v605.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v605.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v605.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_12 + 1);
      v45 = std::vector<int>::operator[](&thisa->m_vXiaoFeiSumBroadcast, i_12);
      std::allocator<char>::allocator(&v606);
      std::string::string(&v605.m_currentSection, szCol, &v606);
      std::allocator<char>::allocator(&v608);
      std::string::string(&v607, "XIAO_FEI_SUM_GIFT", &v608);
      *v45 = Answer::Inifile::getIntValue(&ini, &v607, &v605.m_currentSection);
      std::string::~string(&v607);
      std::allocator<char>::~allocator(&v608);
      std::string::~string(&v605.m_currentSection);
      std::allocator<char>::~allocator(&v606);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_PET_GIFT) )
  {
    std::allocator<char>::allocator(&v610);
    std::string::string(&v609, "start_day", &v610);
    std::allocator<char>::allocator(&v612);
    std::string::string(&v611, "BUY_PET_GIFT", &v612);
    v46 = Answer::Inifile::getIntValue(&ini, &v611, &v609);
    thisa->m_vStartDay[23] = v46;
    std::string::~string(&v611);
    std::allocator<char>::~allocator(&v612);
    std::string::~string(&v609);
    std::allocator<char>::~allocator(&v610);
    std::allocator<char>::allocator(&v614);
    std::string::string(&v613, "end_day", &v614);
    std::allocator<char>::allocator(&v616);
    std::string::string(&v615, "BUY_PET_GIFT", &v616);
    v47 = Answer::Inifile::getIntValue(&ini, &v615, &v613);
    thisa->m_vEndDay[23] = v47;
    std::string::~string(&v615);
    std::allocator<char>::~allocator(&v616);
    std::string::~string(&v613);
    std::allocator<char>::~allocator(&v614);
    std::allocator<char>::allocator(&v618);
    std::string::string(&v617, "price", &v618);
    std::allocator<char>::allocator(&v620);
    std::string::string(&v619, "BUY_PET_GIFT", &v620);
    v48 = Answer::Inifile::getIntValue(&ini, &v619, &v617);
    thisa->m_Price = v48;
    std::string::~string(&v619);
    std::allocator<char>::~allocator(&v620);
    std::string::~string(&v617);
    std::allocator<char>::~allocator(&v618);
    std::allocator<char>::allocator((char *)&v622.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v622.m_strMap._M_t._M_impl._M_header._M_parent,
      "goods",
      (char *)&v622.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v622.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v622.m_strMap._M_t._M_impl._M_header._M_right,
      "BUY_PET_GIFT",
      (char *)&v622.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v622,
      (const std::string *const)&ini,
      (const std::string *const)&v622.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v621, (const std::string *const)&v622);
    std::vector<MemChrBag>::operator=(&thisa->m_Items, &v621);
    std::vector<MemChrBag>::~vector(&v621);
    std::string::~string(&v622);
    std::string::~string(&v622.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v622.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v622.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v622.m_strMap._M_t._M_impl._M_header._M_left + 7);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI) )
  {
    std::allocator<char>::allocator(&v623);
    std::string::string(&v622.m_currentSection, "start_day", &v623);
    std::allocator<char>::allocator(&v625);
    std::string::string(&v624, "DA_TI", &v625);
    v49 = Answer::Inifile::getIntValue(&ini, &v624, &v622.m_currentSection);
    thisa->m_vStartDay[24] = v49;
    std::string::~string(&v624);
    std::allocator<char>::~allocator(&v625);
    std::string::~string(&v622.m_currentSection);
    std::allocator<char>::~allocator(&v623);
    std::allocator<char>::allocator(&v627);
    std::string::string(&v626, "end_day", &v627);
    std::allocator<char>::allocator(&v629);
    std::string::string(&v628, "DA_TI", &v629);
    v50 = Answer::Inifile::getIntValue(&ini, &v628, &v626);
    thisa->m_vEndDay[24] = v50;
    std::string::~string(&v628);
    std::allocator<char>::~allocator(&v629);
    std::string::~string(&v626);
    std::allocator<char>::~allocator(&v627);
    std::allocator<char>::allocator(&v631);
    std::string::string(&v630, "size", &v631);
    std::allocator<char>::allocator(&v633);
    std::string::string(&v632, "DA_TI", &v633);
    v51 = Answer::Inifile::getIntValue(&ini, &v632, &v630);
    thisa->m_nDaTiRankSize = v51;
    std::string::~string(&v632);
    std::allocator<char>::~allocator(&v633);
    std::string::~string(&v630);
    std::allocator<char>::~allocator(&v631);
    std::vector<int>::resize(&thisa->m_vDaTiRankMail, thisa->m_nDaTiRankSize, 0);
    std::vector<MemChrBag>::vector(&v634);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vDaTiRankReward, thisa->m_nDaTiRankSize, &v634);
    std::vector<MemChrBag>::~vector(&v634);
    for ( i_13 = 0; thisa->m_nDaTiRankSize > i_13; ++i_13 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_13 + 1);
      v52 = std::vector<int>::operator[](&thisa->m_vDaTiRankMail, i_13);
      std::allocator<char>::allocator(&v636);
      std::string::string(&v635, szCol, &v636);
      std::allocator<char>::allocator(&v638);
      std::string::string(&v637, "DA_TI", &v638);
      *v52 = Answer::Inifile::getIntValue(&ini, &v637, &v635);
      std::string::~string(&v637);
      std::allocator<char>::~allocator(&v638);
      std::string::~string(&v635);
      std::allocator<char>::~allocator(&v636);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_13 + 1);
      std::allocator<char>::allocator((char *)&v640.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v640.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v640.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v640.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v640.m_strMap._M_t._M_impl._M_header._M_right,
        "DA_TI",
        (char *)&v640.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v640,
        (const std::string *const)&ini,
        (const std::string *const)&v640.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v639, (const std::string *const)&v640);
      v53 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vDaTiRankReward, i_13);
      std::vector<MemChrBag>::operator=(v53, &v639);
      std::vector<MemChrBag>::~vector(&v639);
      std::string::~string(&v640);
      std::string::~string(&v640.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v640.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v640.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v640.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP_2) )
  {
    std::allocator<char>::allocator(&v641);
    std::string::string(&v640.m_currentSection, "start_day", &v641);
    std::allocator<char>::allocator(&v643);
    std::string::string(&v642, "DAILY_LIMIT_SHOP_2", &v643);
    v54 = Answer::Inifile::getIntValue(&ini, &v642, &v640.m_currentSection);
    thisa->m_vStartDay[25] = v54;
    std::string::~string(&v642);
    std::allocator<char>::~allocator(&v643);
    std::string::~string(&v640.m_currentSection);
    std::allocator<char>::~allocator(&v641);
    std::allocator<char>::allocator(&v645);
    std::string::string(&v644, "end_day", &v645);
    std::allocator<char>::allocator(&v647);
    std::string::string(&v646, "DAILY_LIMIT_SHOP_2", &v647);
    v55 = Answer::Inifile::getIntValue(&ini, &v646, &v644);
    thisa->m_vEndDay[25] = v55;
    std::string::~string(&v646);
    std::allocator<char>::~allocator(&v647);
    std::string::~string(&v644);
    std::allocator<char>::~allocator(&v645);
    std::allocator<char>::allocator(&v649);
    std::string::string(&v648, "size", &v649);
    std::allocator<char>::allocator(&v651);
    std::string::string(&v650, "DAILY_LIMIT_SHOP_2", &v651);
    v56 = Answer::Inifile::getIntValue(&ini, &v650, &v648);
    thisa->m_nDailyLimitShop2Size = v56;
    std::string::~string(&v650);
    std::allocator<char>::~allocator(&v651);
    std::string::~string(&v648);
    std::allocator<char>::~allocator(&v649);
    memset(&v652, 0, 28);
    ShopGoods::ShopGoods(&v652);
    std::vector<ShopGoods>::resize(&thisa->m_vDailyLimitShop2Goods, thisa->m_nDailyLimitShop2Size, &v652);
    ShopGoods::~ShopGoods(&v652);
    std::vector<int>::resize(&thisa->m_vDailyLimitShop2Broadcast, thisa->m_nDailyLimitShop2Size, 0);
    for ( i_14 = 0; thisa->m_nDailyLimitShop2Size > i_14; ++i_14 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_14 + 1);
      v57 = std::vector<ShopGoods>::operator[](&thisa->m_vDailyLimitShop2Goods, i_14);
      std::allocator<char>::allocator(&v654);
      std::string::string(&v653, szCol, &v654);
      std::allocator<char>::allocator(&v656);
      std::string::string(&v655, "DAILY_LIMIT_SHOP_2", &v656);
      v57->nPrice = Answer::Inifile::getIntValue(&ini, &v655, &v653);
      std::string::~string(&v655);
      std::allocator<char>::~allocator(&v656);
      std::string::~string(&v653);
      std::allocator<char>::~allocator(&v654);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "goods%d", i_14 + 1);
      std::allocator<char>::allocator((char *)&v658.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v658.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v658.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v658.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v658.m_strMap._M_t._M_impl._M_header._M_right,
        "DAILY_LIMIT_SHOP_2",
        (char *)&v658.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v658,
        (const std::string *const)&ini,
        (const std::string *const)&v658.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v657, (const std::string *const)&v658);
      v58 = std::vector<ShopGoods>::operator[](&thisa->m_vDailyLimitShop2Goods, i_14);
      std::vector<MemChrBag>::operator=(&v58->vItem, &v657);
      std::vector<MemChrBag>::~vector(&v657);
      std::string::~string(&v658);
      std::string::~string(&v658.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v658.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v658.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v658.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_14 + 1);
      v59 = std::vector<int>::operator[](&thisa->m_vDailyLimitShop2Broadcast, i_14);
      std::allocator<char>::allocator(&v659);
      std::string::string(&v658.m_currentSection, szCol, &v659);
      std::allocator<char>::allocator(&v661);
      std::string::string(&v660, "DAILY_LIMIT_SHOP_2", &v661);
      *v59 = Answer::Inifile::getIntValue(&ini, &v660, &v658.m_currentSection);
      std::string::~string(&v660);
      std::allocator<char>::~allocator(&v661);
      std::string::~string(&v658.m_currentSection);
      std::allocator<char>::~allocator(&v659);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) )
  {
    std::allocator<char>::allocator(&v663);
    std::string::string(&v662, "start_day", &v663);
    std::allocator<char>::allocator(&v665);
    std::string::string(&v664, "EQUIP_UPSTAR_BACK", &v665);
    v60 = Answer::Inifile::getIntValue(&ini, &v664, &v662);
    thisa->m_vStartDay[26] = v60;
    std::string::~string(&v664);
    std::allocator<char>::~allocator(&v665);
    std::string::~string(&v662);
    std::allocator<char>::~allocator(&v663);
    std::allocator<char>::allocator(&v667);
    std::string::string(&v666, "end_day", &v667);
    std::allocator<char>::allocator(&v669);
    std::string::string(&v668, "EQUIP_UPSTAR_BACK", &v669);
    v61 = Answer::Inifile::getIntValue(&ini, &v668, &v666);
    thisa->m_vEndDay[26] = v61;
    std::string::~string(&v668);
    std::allocator<char>::~allocator(&v669);
    std::string::~string(&v666);
    std::allocator<char>::~allocator(&v667);
    std::allocator<char>::allocator(&v671);
    std::string::string(&v670, "back_id", &v671);
    std::allocator<char>::allocator(&v673);
    std::string::string(&v672, "EQUIP_UPSTAR_BACK", &v673);
    v62 = Answer::Inifile::getIntValue(&ini, &v672, &v670);
    thisa->m_nEquipUpStarBackId = v62;
    std::string::~string(&v672);
    std::allocator<char>::~allocator(&v673);
    std::string::~string(&v670);
    std::allocator<char>::~allocator(&v671);
    std::allocator<char>::allocator(&v675);
    std::string::string(&v674, "size", &v675);
    std::allocator<char>::allocator(&v677);
    std::string::string(&v676, "EQUIP_UPSTAR_BACK", &v677);
    v63 = Answer::Inifile::getIntValue(&ini, &v676, &v674);
    thisa->m_nEquipUpStarSize = v63;
    std::string::~string(&v676);
    std::allocator<char>::~allocator(&v677);
    std::string::~string(&v674);
    std::allocator<char>::~allocator(&v675);
    std::map<int,int>::clear(&thisa->m_mEquipUpStarBackStarCount);
    for ( i_15 = 0; thisa->m_nEquipUpStarSize > i_15; ++i_15 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "star%d", i_15 + 1);
      std::allocator<char>::allocator(&v679);
      std::string::string(&v678, szCol, &v679);
      std::allocator<char>::allocator(&v681);
      std::string::string(&v680, "EQUIP_UPSTAR_BACK", &v681);
      nStar = Answer::Inifile::getIntValue(&ini, &v680, &v678);
      std::string::~string(&v680);
      std::allocator<char>::~allocator(&v681);
      std::string::~string(&v678);
      std::allocator<char>::~allocator(&v679);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "count%d", i_15 + 1);
      std::allocator<char>::allocator(&v683);
      std::string::string(&v682, szCol, &v683);
      std::allocator<char>::allocator(&v685);
      std::string::string(&v684, "EQUIP_UPSTAR_BACK", &v685);
      nCount_0 = Answer::Inifile::getIntValue(&ini, &v684, &v682);
      std::string::~string(&v684);
      std::allocator<char>::~allocator(&v685);
      std::string::~string(&v682);
      std::allocator<char>::~allocator(&v683);
      v64 = std::map<int,int>::operator[](&thisa->m_mEquipUpStarBackStarCount, &nStar);
      *v64 = nCount_0;
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_DRAW) )
  {
    std::allocator<char>::allocator(&v687);
    std::string::string(&v686, "start_day", &v687);
    std::allocator<char>::allocator(&v689);
    std::string::string(&v688, "RECHARGE_DRAW", &v689);
    v65 = Answer::Inifile::getIntValue(&ini, &v688, &v686);
    thisa->m_vStartDay[27] = v65;
    std::string::~string(&v688);
    std::allocator<char>::~allocator(&v689);
    std::string::~string(&v686);
    std::allocator<char>::~allocator(&v687);
    std::allocator<char>::allocator(&v691);
    std::string::string(&v690, "end_day", &v691);
    std::allocator<char>::allocator(&v693);
    std::string::string(&v692, "RECHARGE_DRAW", &v693);
    v66 = Answer::Inifile::getIntValue(&ini, &v692, &v690);
    thisa->m_vEndDay[27] = v66;
    std::string::~string(&v692);
    std::allocator<char>::~allocator(&v693);
    std::string::~string(&v690);
    std::allocator<char>::~allocator(&v691);
    std::allocator<char>::allocator(&v695);
    std::string::string(&v694, "size", &v695);
    std::allocator<char>::allocator(&v697);
    std::string::string(&v696, "RECHARGE_DRAW", &v697);
    v67 = Answer::Inifile::getIntValue(&ini, &v696, &v694);
    thisa->m_RechargeDrawSize = v67;
    std::string::~string(&v696);
    std::allocator<char>::~allocator(&v697);
    std::string::~string(&v694);
    std::allocator<char>::~allocator(&v695);
    std::vector<int>::reserve(&thisa->m_nRechargeDrawValue, thisa->m_RechargeDrawSize);
    for ( i_16 = 0; thisa->m_RechargeDrawSize > i_16; ++i_16 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "value%d", i_16 + 1);
      std::allocator<char>::allocator(&v700);
      std::string::string(&v699, szCol, &v700);
      std::allocator<char>::allocator(&v702);
      std::string::string(&v701, "RECHARGE_DRAW", &v702);
      v698 = Answer::Inifile::getIntValue(&ini, &v701, &v699);
      std::vector<int>::push_back(&thisa->m_nRechargeDrawValue, &v698);
      std::string::~string(&v701);
      std::allocator<char>::~allocator(&v702);
      std::string::~string(&v699);
      std::allocator<char>::~allocator(&v700);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_GIFT) )
  {
    std::allocator<char>::allocator(&v704);
    std::string::string(&v703, "start_day", &v704);
    std::allocator<char>::allocator(&v706);
    std::string::string(&v705, "BUY_GIFT", &v706);
    v68 = Answer::Inifile::getIntValue(&ini, &v705, &v703);
    thisa->m_vStartDay[28] = v68;
    std::string::~string(&v705);
    std::allocator<char>::~allocator(&v706);
    std::string::~string(&v703);
    std::allocator<char>::~allocator(&v704);
    std::allocator<char>::allocator(&v708);
    std::string::string(&v707, "end_day", &v708);
    std::allocator<char>::allocator(&v710);
    std::string::string(&v709, "BUY_GIFT", &v710);
    v69 = Answer::Inifile::getIntValue(&ini, &v709, &v707);
    thisa->m_vEndDay[28] = v69;
    std::string::~string(&v709);
    std::allocator<char>::~allocator(&v710);
    std::string::~string(&v707);
    std::allocator<char>::~allocator(&v708);
    std::allocator<char>::allocator(&v712);
    std::string::string(&v711, "size", &v712);
    std::allocator<char>::allocator(&v714);
    std::string::string(&v713, "BUY_GIFT", &v714);
    v70 = Answer::Inifile::getIntValue(&ini, &v713, &v711);
    thisa->m_nBuyGiftSize = v70;
    std::string::~string(&v713);
    std::allocator<char>::~allocator(&v714);
    std::string::~string(&v711);
    std::allocator<char>::~allocator(&v712);
    std::vector<int>::resize(&thisa->m_vBuyGiftPrice, thisa->m_nBuyGiftSize, 0);
    std::vector<int>::resize(&thisa->m_vBuyGiftBroadcast, thisa->m_nBuyGiftSize, 0);
    std::vector<MemChrBag>::vector(&v715);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vBuyGiftItem, thisa->m_nBuyGiftSize, &v715);
    std::vector<MemChrBag>::~vector(&v715);
    for ( i_17 = 0; thisa->m_nBuyGiftSize > i_17; ++i_17 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_17 + 1);
      v71 = std::vector<int>::operator[](&thisa->m_vBuyGiftPrice, i_17);
      std::allocator<char>::allocator(&v717);
      std::string::string(&v716, szCol, &v717);
      std::allocator<char>::allocator(&v719);
      std::string::string(&v718, "BUY_GIFT", &v719);
      *v71 = Answer::Inifile::getIntValue(&ini, &v718, &v716);
      std::string::~string(&v718);
      std::allocator<char>::~allocator(&v719);
      std::string::~string(&v716);
      std::allocator<char>::~allocator(&v717);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_17 + 1);
      v72 = std::vector<int>::operator[](&thisa->m_vBuyGiftBroadcast, i_17);
      std::allocator<char>::allocator(&v721);
      std::string::string(&v720, szCol, &v721);
      std::allocator<char>::allocator(&v723);
      std::string::string(&v722, "BUY_GIFT", &v723);
      *v72 = Answer::Inifile::getIntValue(&ini, &v722, &v720);
      std::string::~string(&v722);
      std::allocator<char>::~allocator(&v723);
      std::string::~string(&v720);
      std::allocator<char>::~allocator(&v721);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "item%d", i_17 + 1);
      std::allocator<char>::allocator((char *)&v725.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v725.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v725.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v725.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v725.m_strMap._M_t._M_impl._M_header._M_right,
        "BUY_GIFT",
        (char *)&v725.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v725,
        (const std::string *const)&ini,
        (const std::string *const)&v725.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v724, (const std::string *const)&v725);
      v73 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vBuyGiftItem, i_17);
      std::vector<MemChrBag>::operator=(v73, &v724);
      std::vector<MemChrBag>::~vector(&v724);
      std::string::~string(&v725);
      std::string::~string(&v725.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v725.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v725.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v725.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
  {
    std::allocator<char>::allocator(&v726);
    std::string::string(&v725.m_currentSection, "start_day", &v726);
    std::allocator<char>::allocator(&v728);
    std::string::string(&v727, "RECHARGE_BACK", &v728);
    v74 = Answer::Inifile::getIntValue(&ini, &v727, &v725.m_currentSection);
    thisa->m_vStartDay[29] = v74;
    std::string::~string(&v727);
    std::allocator<char>::~allocator(&v728);
    std::string::~string(&v725.m_currentSection);
    std::allocator<char>::~allocator(&v726);
    std::allocator<char>::allocator(&v730);
    std::string::string(&v729, "end_day", &v730);
    std::allocator<char>::allocator(&v732);
    std::string::string(&v731, "RECHARGE_BACK", &v732);
    v75 = Answer::Inifile::getIntValue(&ini, &v731, &v729);
    thisa->m_vEndDay[29] = v75;
    std::string::~string(&v731);
    std::allocator<char>::~allocator(&v732);
    std::string::~string(&v729);
    std::allocator<char>::~allocator(&v730);
    std::allocator<char>::allocator(&v734);
    std::string::string(&v733, "size", &v734);
    std::allocator<char>::allocator(&v736);
    std::string::string(&v735, "RECHARGE_BACK", &v736);
    v76 = Answer::Inifile::getIntValue(&ini, &v735, &v733);
    thisa->m_nRechargeBackSize = v76;
    std::string::~string(&v735);
    std::allocator<char>::~allocator(&v736);
    std::string::~string(&v733);
    std::allocator<char>::~allocator(&v734);
    std::vector<int>::resize(&thisa->m_vRechargeBackLimit, thisa->m_nRechargeBackSize, 0);
    std::vector<int>::resize(&thisa->m_vRechargeBackValue, thisa->m_nRechargeBackSize, 0);
    for ( i_18 = 0; thisa->m_nRechargeBackSize > i_18; ++i_18 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "recharge%d", i_18 + 1);
      v77 = std::vector<int>::operator[](&thisa->m_vRechargeBackLimit, i_18);
      std::allocator<char>::allocator(&v738);
      std::string::string(&v737, szCol, &v738);
      std::allocator<char>::allocator(&v740);
      std::string::string(&v739, "RECHARGE_BACK", &v740);
      *v77 = Answer::Inifile::getIntValue(&ini, &v739, &v737);
      std::string::~string(&v739);
      std::allocator<char>::~allocator(&v740);
      std::string::~string(&v737);
      std::allocator<char>::~allocator(&v738);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "back%d", i_18 + 1);
      v78 = std::vector<int>::operator[](&thisa->m_vRechargeBackValue, i_18);
      std::allocator<char>::allocator(&v742);
      std::string::string(&v741, szCol, &v742);
      std::allocator<char>::allocator(&v744);
      std::string::string(&v743, "RECHARGE_BACK", &v744);
      *v78 = Answer::Inifile::getIntValue(&ini, &v743, &v741);
      std::string::~string(&v743);
      std::allocator<char>::~allocator(&v744);
      std::string::~string(&v741);
      std::allocator<char>::~allocator(&v742);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE) )
  {
    std::allocator<char>::allocator(&v746);
    std::string::string(&v745, "start_day", &v746);
    std::allocator<char>::allocator(&v748);
    std::string::string(&v747, "BOSS_SCORE", &v748);
    v79 = Answer::Inifile::getIntValue(&ini, &v747, &v745);
    thisa->m_vStartDay[30] = v79;
    std::string::~string(&v747);
    std::allocator<char>::~allocator(&v748);
    std::string::~string(&v745);
    std::allocator<char>::~allocator(&v746);
    std::allocator<char>::allocator(&v750);
    std::string::string(&v749, "end_day", &v750);
    std::allocator<char>::allocator(&v752);
    std::string::string(&v751, "BOSS_SCORE", &v752);
    v80 = Answer::Inifile::getIntValue(&ini, &v751, &v749);
    thisa->m_vEndDay[30] = v80;
    std::string::~string(&v751);
    std::allocator<char>::~allocator(&v752);
    std::string::~string(&v749);
    std::allocator<char>::~allocator(&v750);
    std::allocator<char>::allocator(&v754);
    std::string::string(&v753, "add_value", &v754);
    std::allocator<char>::allocator(&v756);
    std::string::string(&v755, "BOSS_SCORE", &v756);
    v81 = Answer::Inifile::getIntValue(&ini, &v755, &v753);
    thisa->m_nBossScoreRate = v81;
    std::string::~string(&v755);
    std::allocator<char>::~allocator(&v756);
    std::string::~string(&v753);
    std::allocator<char>::~allocator(&v754);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM) )
  {
    std::allocator<char>::allocator(&v758);
    std::string::string(&v757, "start_day", &v758);
    std::allocator<char>::allocator(&v760);
    std::string::string(&v759, "PET_ILLUSION_ITEM", &v760);
    v82 = Answer::Inifile::getIntValue(&ini, &v759, &v757);
    thisa->m_vStartDay[31] = v82;
    std::string::~string(&v759);
    std::allocator<char>::~allocator(&v760);
    std::string::~string(&v757);
    std::allocator<char>::~allocator(&v758);
    std::allocator<char>::allocator(&v762);
    std::string::string(&v761, "end_day", &v762);
    std::allocator<char>::allocator(&v764);
    std::string::string(&v763, "PET_ILLUSION_ITEM", &v764);
    v83 = Answer::Inifile::getIntValue(&ini, &v763, &v761);
    thisa->m_vEndDay[31] = v83;
    std::string::~string(&v763);
    std::allocator<char>::~allocator(&v764);
    std::string::~string(&v761);
    std::allocator<char>::~allocator(&v762);
    std::allocator<char>::allocator(&v766);
    std::string::string(&v765, "size", &v766);
    std::allocator<char>::allocator(&v768);
    std::string::string(&v767, "PET_ILLUSION_ITEM", &v768);
    v84 = Answer::Inifile::getIntValue(&ini, &v767, &v765);
    thisa->m_nPetIllusionItemSize = v84;
    std::string::~string(&v767);
    std::allocator<char>::~allocator(&v768);
    std::string::~string(&v765);
    std::allocator<char>::~allocator(&v766);
    std::vector<int>::resize(&thisa->m_vPetIllusionItemLimit, thisa->m_nPetIllusionItemSize, 0);
    std::vector<MemChrBag>::vector(&v769);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vPetIllusionItemReward, thisa->m_nPetIllusionItemSize, &v769);
    std::vector<MemChrBag>::~vector(&v769);
    for ( i_19 = 0; thisa->m_nPetIllusionItemSize > i_19; ++i_19 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_19 + 1);
      v85 = std::vector<int>::operator[](&thisa->m_vPetIllusionItemLimit, i_19);
      std::allocator<char>::allocator(&v771);
      std::string::string(&v770, szCol, &v771);
      std::allocator<char>::allocator(&v773);
      std::string::string(&v772, "PET_ILLUSION_ITEM", &v773);
      *v85 = Answer::Inifile::getIntValue(&ini, &v772, &v770);
      std::string::~string(&v772);
      std::allocator<char>::~allocator(&v773);
      std::string::~string(&v770);
      std::allocator<char>::~allocator(&v771);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_19 + 1);
      std::allocator<char>::allocator((char *)&v775.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v775.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v775.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v775.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v775.m_strMap._M_t._M_impl._M_header._M_right,
        "PET_ILLUSION_ITEM",
        (char *)&v775.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v775,
        (const std::string *const)&ini,
        (const std::string *const)&v775.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v774, (const std::string *const)&v775);
      v86 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vPetIllusionItemReward, i_19);
      std::vector<MemChrBag>::operator=(v86, &v774);
      std::vector<MemChrBag>::~vector(&v774);
      std::string::~string(&v775);
      std::string::~string(&v775.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v775.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v775.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v775.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK) )
  {
    std::allocator<char>::allocator(&v776);
    std::string::string(&v775.m_currentSection, "start_day", &v776);
    std::allocator<char>::allocator(&v778);
    std::string::string(&v777, "RECHARGE_SUM_RANK", &v778);
    v87 = Answer::Inifile::getIntValue(&ini, &v777, &v775.m_currentSection);
    thisa->m_vStartDay[32] = v87;
    std::string::~string(&v777);
    std::allocator<char>::~allocator(&v778);
    std::string::~string(&v775.m_currentSection);
    std::allocator<char>::~allocator(&v776);
    std::allocator<char>::allocator(&v780);
    std::string::string(&v779, "end_day", &v780);
    std::allocator<char>::allocator(&v782);
    std::string::string(&v781, "RECHARGE_SUM_RANK", &v782);
    v88 = Answer::Inifile::getIntValue(&ini, &v781, &v779);
    thisa->m_vEndDay[32] = v88;
    std::string::~string(&v781);
    std::allocator<char>::~allocator(&v782);
    std::string::~string(&v779);
    std::allocator<char>::~allocator(&v780);
    std::allocator<char>::allocator(&v784);
    std::string::string(&v783, "size", &v784);
    std::allocator<char>::allocator(&v786);
    std::string::string(&v785, "RECHARGE_SUM_RANK", &v786);
    v89 = Answer::Inifile::getIntValue(&ini, &v785, &v783);
    thisa->m_nRechargeSumRankSize = v89;
    std::string::~string(&v785);
    std::allocator<char>::~allocator(&v786);
    std::string::~string(&v783);
    std::allocator<char>::~allocator(&v784);
    std::vector<int>::resize(&thisa->m_vRechargeSumRankLimit, thisa->m_nRechargeSumRankSize, 0);
    std::vector<int>::resize(&thisa->m_vRechargeSumRankMail, thisa->m_nRechargeSumRankSize, 0);
    std::vector<MemChrBag>::vector(&v787);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vRechargeSumRankReward, thisa->m_nRechargeSumRankSize, &v787);
    std::vector<MemChrBag>::~vector(&v787);
    for ( i_20 = 0; thisa->m_nRechargeSumRankSize > i_20; ++i_20 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_20 + 1);
      v90 = std::vector<int>::operator[](&thisa->m_vRechargeSumRankLimit, i_20);
      std::allocator<char>::allocator(&v789);
      std::string::string(&v788, szCol, &v789);
      std::allocator<char>::allocator(&v791);
      std::string::string(&v790, "RECHARGE_SUM_RANK", &v791);
      *v90 = Answer::Inifile::getIntValue(&ini, &v790, &v788);
      std::string::~string(&v790);
      std::allocator<char>::~allocator(&v791);
      std::string::~string(&v788);
      std::allocator<char>::~allocator(&v789);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_20 + 1);
      v91 = std::vector<int>::operator[](&thisa->m_vRechargeSumRankMail, i_20);
      std::allocator<char>::allocator(&v793);
      std::string::string(&v792, szCol, &v793);
      std::allocator<char>::allocator(&v795);
      std::string::string(&v794, "RECHARGE_SUM_RANK", &v795);
      *v91 = Answer::Inifile::getIntValue(&ini, &v794, &v792);
      std::string::~string(&v794);
      std::allocator<char>::~allocator(&v795);
      std::string::~string(&v792);
      std::allocator<char>::~allocator(&v793);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_20 + 1);
      std::allocator<char>::allocator((char *)&v797.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v797.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v797.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v797.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v797.m_strMap._M_t._M_impl._M_header._M_right,
        "RECHARGE_SUM_RANK",
        (char *)&v797.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v797,
        (const std::string *const)&ini,
        (const std::string *const)&v797.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v796, (const std::string *const)&v797);
      v92 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vRechargeSumRankReward, i_20);
      std::vector<MemChrBag>::operator=(v92, &v796);
      std::vector<MemChrBag>::~vector(&v796);
      std::string::~string(&v797);
      std::string::~string(&v797.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v797.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v797.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v797.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK) )
  {
    std::allocator<char>::allocator(&v798);
    std::string::string(&v797.m_currentSection, "start_day", &v798);
    std::allocator<char>::allocator(&v800);
    std::string::string(&v799, "CROSS_RECHARGE_SUM_RANK", &v800);
    v93 = Answer::Inifile::getIntValue(&ini, &v799, &v797.m_currentSection);
    thisa->m_vStartDay[33] = v93;
    std::string::~string(&v799);
    std::allocator<char>::~allocator(&v800);
    std::string::~string(&v797.m_currentSection);
    std::allocator<char>::~allocator(&v798);
    std::allocator<char>::allocator(&v802);
    std::string::string(&v801, "end_day", &v802);
    std::allocator<char>::allocator(&v804);
    std::string::string(&v803, "CROSS_RECHARGE_SUM_RANK", &v804);
    v94 = Answer::Inifile::getIntValue(&ini, &v803, &v801);
    thisa->m_vEndDay[33] = v94;
    std::string::~string(&v803);
    std::allocator<char>::~allocator(&v804);
    std::string::~string(&v801);
    std::allocator<char>::~allocator(&v802);
    std::allocator<char>::allocator(&v806);
    std::string::string(&v805, "size", &v806);
    std::allocator<char>::allocator(&v808);
    std::string::string(&v807, "CROSS_RECHARGE_SUM_RANK", &v808);
    v95 = Answer::Inifile::getIntValue(&ini, &v807, &v805);
    thisa->m_nCrossRechargeSumRankSize = v95;
    std::string::~string(&v807);
    std::allocator<char>::~allocator(&v808);
    std::string::~string(&v805);
    std::allocator<char>::~allocator(&v806);
    std::vector<int>::resize(&thisa->m_vCrossRechargeSumRankLimit, thisa->m_nCrossRechargeSumRankSize, 0);
    std::vector<int>::resize(&thisa->m_vCrossRechargeSumRankMail, thisa->m_nCrossRechargeSumRankSize, 0);
    std::vector<MemChrBag>::vector(&v809);
    std::vector<std::vector<MemChrBag>>::resize(
      &thisa->m_vCrossRechargeSumRankReward,
      thisa->m_nCrossRechargeSumRankSize,
      &v809);
    std::vector<MemChrBag>::~vector(&v809);
    for ( i_21 = 0; thisa->m_nCrossRechargeSumRankSize > i_21; ++i_21 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_21 + 1);
      v96 = std::vector<int>::operator[](&thisa->m_vCrossRechargeSumRankLimit, i_21);
      std::allocator<char>::allocator(&v811);
      std::string::string(&v810, szCol, &v811);
      std::allocator<char>::allocator(&v813);
      std::string::string(&v812, "CROSS_RECHARGE_SUM_RANK", &v813);
      *v96 = Answer::Inifile::getIntValue(&ini, &v812, &v810);
      std::string::~string(&v812);
      std::allocator<char>::~allocator(&v813);
      std::string::~string(&v810);
      std::allocator<char>::~allocator(&v811);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_21 + 1);
      v97 = std::vector<int>::operator[](&thisa->m_vCrossRechargeSumRankMail, i_21);
      std::allocator<char>::allocator(&v815);
      std::string::string(&v814, szCol, &v815);
      std::allocator<char>::allocator(&v817);
      std::string::string(&v816, "CROSS_RECHARGE_SUM_RANK", &v817);
      *v97 = Answer::Inifile::getIntValue(&ini, &v816, &v814);
      std::string::~string(&v816);
      std::allocator<char>::~allocator(&v817);
      std::string::~string(&v814);
      std::allocator<char>::~allocator(&v815);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_21 + 1);
      std::allocator<char>::allocator((char *)&v819.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v819.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v819.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v819.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v819.m_strMap._M_t._M_impl._M_header._M_right,
        "CROSS_RECHARGE_SUM_RANK",
        (char *)&v819.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v819,
        (const std::string *const)&ini,
        (const std::string *const)&v819.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v818, (const std::string *const)&v819);
      v98 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vCrossRechargeSumRankReward, i_21);
      std::vector<MemChrBag>::operator=(v98, &v818);
      std::vector<MemChrBag>::~vector(&v818);
      std::string::~string(&v819);
      std::string::~string(&v819.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v819.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v819.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v819.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK) )
  {
    std::allocator<char>::allocator(&v820);
    std::string::string(&v819.m_currentSection, "start_day", &v820);
    std::allocator<char>::allocator(&v822);
    std::string::string(&v821, "CROSS_XIAO_FEI_SUM_RANK", &v822);
    v99 = Answer::Inifile::getIntValue(&ini, &v821, &v819.m_currentSection);
    thisa->m_vStartDay[34] = v99;
    std::string::~string(&v821);
    std::allocator<char>::~allocator(&v822);
    std::string::~string(&v819.m_currentSection);
    std::allocator<char>::~allocator(&v820);
    std::allocator<char>::allocator(&v824);
    std::string::string(&v823, "end_day", &v824);
    std::allocator<char>::allocator(&v826);
    std::string::string(&v825, "CROSS_XIAO_FEI_SUM_RANK", &v826);
    v100 = Answer::Inifile::getIntValue(&ini, &v825, &v823);
    thisa->m_vEndDay[34] = v100;
    std::string::~string(&v825);
    std::allocator<char>::~allocator(&v826);
    std::string::~string(&v823);
    std::allocator<char>::~allocator(&v824);
    std::allocator<char>::allocator(&v828);
    std::string::string(&v827, "size", &v828);
    std::allocator<char>::allocator(&v830);
    std::string::string(&v829, "CROSS_XIAO_FEI_SUM_RANK", &v830);
    v101 = Answer::Inifile::getIntValue(&ini, &v829, &v827);
    thisa->m_nCrossXiaoFeiSumRankSize = v101;
    std::string::~string(&v829);
    std::allocator<char>::~allocator(&v830);
    std::string::~string(&v827);
    std::allocator<char>::~allocator(&v828);
    std::vector<int>::resize(&thisa->m_vCrossXiaoFeiSumRankLimit, thisa->m_nCrossXiaoFeiSumRankSize, 0);
    std::vector<int>::resize(&thisa->m_vCrossXiaoFeiSumRankMail, thisa->m_nCrossXiaoFeiSumRankSize, 0);
    std::vector<MemChrBag>::vector(&v831);
    std::vector<std::vector<MemChrBag>>::resize(
      &thisa->m_vCrossXiaoFeiSumRankReward,
      thisa->m_nCrossXiaoFeiSumRankSize,
      &v831);
    std::vector<MemChrBag>::~vector(&v831);
    for ( i_22 = 0; thisa->m_nCrossXiaoFeiSumRankSize > i_22; ++i_22 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_22 + 1);
      v102 = std::vector<int>::operator[](&thisa->m_vCrossXiaoFeiSumRankLimit, i_22);
      std::allocator<char>::allocator(&v833);
      std::string::string(&v832, szCol, &v833);
      std::allocator<char>::allocator(&v835);
      std::string::string(&v834, "CROSS_XIAO_FEI_SUM_RANK", &v835);
      *v102 = Answer::Inifile::getIntValue(&ini, &v834, &v832);
      std::string::~string(&v834);
      std::allocator<char>::~allocator(&v835);
      std::string::~string(&v832);
      std::allocator<char>::~allocator(&v833);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_22 + 1);
      v103 = std::vector<int>::operator[](&thisa->m_vCrossXiaoFeiSumRankMail, i_22);
      std::allocator<char>::allocator(&v837);
      std::string::string(&v836, szCol, &v837);
      std::allocator<char>::allocator(&v839);
      std::string::string(&v838, "CROSS_XIAO_FEI_SUM_RANK", &v839);
      *v103 = Answer::Inifile::getIntValue(&ini, &v838, &v836);
      std::string::~string(&v838);
      std::allocator<char>::~allocator(&v839);
      std::string::~string(&v836);
      std::allocator<char>::~allocator(&v837);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_22 + 1);
      std::allocator<char>::allocator((char *)&v841.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v841.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v841.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v841.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v841.m_strMap._M_t._M_impl._M_header._M_right,
        "CROSS_XIAO_FEI_SUM_RANK",
        (char *)&v841.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v841,
        (const std::string *const)&ini,
        (const std::string *const)&v841.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v840, (const std::string *const)&v841);
      v104 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vCrossXiaoFeiSumRankReward, i_22);
      std::vector<MemChrBag>::operator=(v104, &v840);
      std::vector<MemChrBag>::~vector(&v840);
      std::string::~string(&v841);
      std::string::~string(&v841.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v841.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v841.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v841.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_PET_EQUIP_CHOU_JIANG) )
  {
    std::allocator<char>::allocator(&v842);
    std::string::string(&v841.m_currentSection, "start_day", &v842);
    std::allocator<char>::allocator(&v844);
    std::string::string(&v843, "PET_EQUIP_CHOU_JIANG", &v844);
    v105 = Answer::Inifile::getIntValue(&ini, &v843, &v841.m_currentSection);
    thisa->m_vStartDay[35] = v105;
    std::string::~string(&v843);
    std::allocator<char>::~allocator(&v844);
    std::string::~string(&v841.m_currentSection);
    std::allocator<char>::~allocator(&v842);
    std::allocator<char>::allocator(&v846);
    std::string::string(&v845, "end_day", &v846);
    std::allocator<char>::allocator(&v848);
    std::string::string(&v847, "PET_EQUIP_CHOU_JIANG", &v848);
    v106 = Answer::Inifile::getIntValue(&ini, &v847, &v845);
    thisa->m_vEndDay[35] = v106;
    std::string::~string(&v847);
    std::allocator<char>::~allocator(&v848);
    std::string::~string(&v845);
    std::allocator<char>::~allocator(&v846);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_CHOU_JIANG_RANK) )
  {
    std::allocator<char>::allocator(&v850);
    std::string::string(&v849, "start_day", &v850);
    std::allocator<char>::allocator(&v852);
    std::string::string(&v851, "CROSS_CHOU_JIANG_RANK", &v852);
    v107 = Answer::Inifile::getIntValue(&ini, &v851, &v849);
    thisa->m_vStartDay[37] = v107;
    std::string::~string(&v851);
    std::allocator<char>::~allocator(&v852);
    std::string::~string(&v849);
    std::allocator<char>::~allocator(&v850);
    std::allocator<char>::allocator(&v854);
    std::string::string(&v853, "end_day", &v854);
    std::allocator<char>::allocator(&v856);
    std::string::string(&v855, "CROSS_CHOU_JIANG_RANK", &v856);
    v108 = Answer::Inifile::getIntValue(&ini, &v855, &v853);
    thisa->m_vEndDay[37] = v108;
    std::string::~string(&v855);
    std::allocator<char>::~allocator(&v856);
    std::string::~string(&v853);
    std::allocator<char>::~allocator(&v854);
    std::allocator<char>::allocator(&v858);
    std::string::string(&v857, "size", &v858);
    std::allocator<char>::allocator(&v860);
    std::string::string(&v859, "CROSS_CHOU_JIANG_RANK", &v860);
    v109 = Answer::Inifile::getIntValue(&ini, &v859, &v857);
    thisa->m_nCrossChouJiangRankSize = v109;
    std::string::~string(&v859);
    std::allocator<char>::~allocator(&v860);
    std::string::~string(&v857);
    std::allocator<char>::~allocator(&v858);
    std::vector<int>::resize(&thisa->m_vCrossChouJiangRankLimit, thisa->m_nCrossChouJiangRankSize, 0);
    std::vector<int>::resize(&thisa->m_vCrossChouJiangRankMail, thisa->m_nCrossChouJiangRankSize, 0);
    std::vector<MemChrBag>::vector(&v861);
    std::vector<std::vector<MemChrBag>>::resize(
      &thisa->m_vCrossChouJiangRankReward,
      thisa->m_nCrossChouJiangRankSize,
      &v861);
    std::vector<MemChrBag>::~vector(&v861);
    for ( i_23 = 0; thisa->m_nCrossChouJiangRankSize > i_23; ++i_23 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_23 + 1);
      v110 = std::vector<int>::operator[](&thisa->m_vCrossChouJiangRankLimit, i_23);
      std::allocator<char>::allocator(&v863);
      std::string::string(&v862, szCol, &v863);
      std::allocator<char>::allocator(&v865);
      std::string::string(&v864, "CROSS_CHOU_JIANG_RANK", &v865);
      *v110 = Answer::Inifile::getIntValue(&ini, &v864, &v862);
      std::string::~string(&v864);
      std::allocator<char>::~allocator(&v865);
      std::string::~string(&v862);
      std::allocator<char>::~allocator(&v863);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_23 + 1);
      v111 = std::vector<int>::operator[](&thisa->m_vCrossChouJiangRankMail, i_23);
      std::allocator<char>::allocator(&v867);
      std::string::string(&v866, szCol, &v867);
      std::allocator<char>::allocator(&v869);
      std::string::string(&v868, "CROSS_CHOU_JIANG_RANK", &v869);
      *v111 = Answer::Inifile::getIntValue(&ini, &v868, &v866);
      std::string::~string(&v868);
      std::allocator<char>::~allocator(&v869);
      std::string::~string(&v866);
      std::allocator<char>::~allocator(&v867);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_23 + 1);
      std::allocator<char>::allocator((char *)&v871.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v871.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v871.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v871.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v871.m_strMap._M_t._M_impl._M_header._M_right,
        "CROSS_CHOU_JIANG_RANK",
        (char *)&v871.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v871,
        (const std::string *const)&ini,
        (const std::string *const)&v871.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v870, (const std::string *const)&v871);
      v112 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vCrossChouJiangRankReward, i_23);
      std::vector<MemChrBag>::operator=(v112, &v870);
      std::vector<MemChrBag>::~vector(&v870);
      std::string::~string(&v871);
      std::string::~string(&v871.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v871.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v871.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v871.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_QING_YI) )
  {
    std::allocator<char>::allocator(&v872);
    std::string::string(&v871.m_currentSection, "start_day", &v872);
    std::allocator<char>::allocator(&v874);
    std::string::string(&v873, "QING_YI_PEI", &v874);
    v113 = Answer::Inifile::getIntValue(&ini, &v873, &v871.m_currentSection);
    thisa->m_vStartDay[38] = v113;
    std::string::~string(&v873);
    std::allocator<char>::~allocator(&v874);
    std::string::~string(&v871.m_currentSection);
    std::allocator<char>::~allocator(&v872);
    std::allocator<char>::allocator(&v876);
    std::string::string(&v875, "end_day", &v876);
    std::allocator<char>::allocator(&v878);
    std::string::string(&v877, "QING_YI_PEI", &v878);
    v114 = Answer::Inifile::getIntValue(&ini, &v877, &v875);
    thisa->m_vEndDay[38] = v114;
    std::string::~string(&v877);
    std::allocator<char>::~allocator(&v878);
    std::string::~string(&v875);
    std::allocator<char>::~allocator(&v876);
    std::allocator<char>::allocator(&v880);
    std::string::string(&v879, "size", &v880);
    std::allocator<char>::allocator(&v882);
    std::string::string(&v881, "QING_YI_PEI", &v882);
    v115 = Answer::Inifile::getIntValue(&ini, &v881, &v879);
    thisa->m_nEquipQingYiSize = v115;
    std::string::~string(&v881);
    std::allocator<char>::~allocator(&v882);
    std::string::~string(&v879);
    std::allocator<char>::~allocator(&v880);
    std::vector<int>::resize(&thisa->m_vEquipQingYiLimit, thisa->m_nEquipQingYiSize, 0);
    std::vector<MemChrBag>::vector(&v883);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vEquipQingYiReward, thisa->m_nEquipQingYiSize, &v883);
    std::vector<MemChrBag>::~vector(&v883);
    for ( i_24 = 0; thisa->m_nEquipQingYiSize > i_24; ++i_24 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_24 + 1);
      v116 = std::vector<int>::operator[](&thisa->m_vEquipQingYiLimit, i_24);
      std::allocator<char>::allocator(&v885);
      std::string::string(&v884, szCol, &v885);
      std::allocator<char>::allocator(&v887);
      std::string::string(&v886, "QING_YI_PEI", &v887);
      *v116 = Answer::Inifile::getIntValue(&ini, &v886, &v884);
      std::string::~string(&v886);
      std::allocator<char>::~allocator(&v887);
      std::string::~string(&v884);
      std::allocator<char>::~allocator(&v885);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_24 + 1);
      std::allocator<char>::allocator((char *)&v889.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v889.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v889.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v889.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v889.m_strMap._M_t._M_impl._M_header._M_right,
        "QING_YI_PEI",
        (char *)&v889.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v889,
        (const std::string *const)&ini,
        (const std::string *const)&v889.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v888, (const std::string *const)&v889);
      v117 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vEquipQingYiReward, i_24);
      std::vector<MemChrBag>::operator=(v117, &v888);
      std::vector<MemChrBag>::~vector(&v888);
      std::string::~string(&v889);
      std::string::~string(&v889.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v889.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v889.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v889.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI) )
  {
    std::allocator<char>::allocator(&v890);
    std::string::string(&v889.m_currentSection, "start_day", &v890);
    std::allocator<char>::allocator(&v892);
    std::string::string(&v891, "FRIEND_QING_YI", &v892);
    v118 = Answer::Inifile::getIntValue(&ini, &v891, &v889.m_currentSection);
    thisa->m_vStartDay[39] = v118;
    std::string::~string(&v891);
    std::allocator<char>::~allocator(&v892);
    std::string::~string(&v889.m_currentSection);
    std::allocator<char>::~allocator(&v890);
    std::allocator<char>::allocator(&v894);
    std::string::string(&v893, "end_day", &v894);
    std::allocator<char>::allocator(&v896);
    std::string::string(&v895, "FRIEND_QING_YI", &v896);
    v119 = Answer::Inifile::getIntValue(&ini, &v895, &v893);
    thisa->m_vEndDay[39] = v119;
    std::string::~string(&v895);
    std::allocator<char>::~allocator(&v896);
    std::string::~string(&v893);
    std::allocator<char>::~allocator(&v894);
    std::allocator<char>::allocator(&v898);
    std::string::string(&v897, "size", &v898);
    std::allocator<char>::allocator(&v900);
    std::string::string(&v899, "FRIEND_QING_YI", &v900);
    v120 = Answer::Inifile::getIntValue(&ini, &v899, &v897);
    thisa->m_nFriendQingYiSize = v120;
    std::string::~string(&v899);
    std::allocator<char>::~allocator(&v900);
    std::string::~string(&v897);
    std::allocator<char>::~allocator(&v898);
    std::vector<int>::resize(&thisa->m_vFriendQingYiLimit, thisa->m_nFriendQingYiSize, 0);
    std::vector<MemChrBag>::vector(&v901);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vFriendQingYiReward, thisa->m_nFriendQingYiSize, &v901);
    std::vector<MemChrBag>::~vector(&v901);
    for ( i_25 = 0; thisa->m_nFriendQingYiSize > i_25; ++i_25 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_25 + 1);
      v121 = std::vector<int>::operator[](&thisa->m_vFriendQingYiLimit, i_25);
      std::allocator<char>::allocator(&v903);
      std::string::string(&v902, szCol, &v903);
      std::allocator<char>::allocator(&v905);
      std::string::string(&v904, "FRIEND_QING_YI", &v905);
      *v121 = Answer::Inifile::getIntValue(&ini, &v904, &v902);
      std::string::~string(&v904);
      std::allocator<char>::~allocator(&v905);
      std::string::~string(&v902);
      std::allocator<char>::~allocator(&v903);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_25 + 1);
      std::allocator<char>::allocator((char *)&v907.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v907.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v907.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v907.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v907.m_strMap._M_t._M_impl._M_header._M_right,
        "FRIEND_QING_YI",
        (char *)&v907.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v907,
        (const std::string *const)&ini,
        (const std::string *const)&v907.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v906, (const std::string *const)&v907);
      v122 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vFriendQingYiReward, i_25);
      std::vector<MemChrBag>::operator=(v122, &v906);
      std::vector<MemChrBag>::~vector(&v906);
      std::string::~string(&v907);
      std::string::~string(&v907.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v907.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v907.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v907.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_SCORE_SHOP) )
  {
    std::allocator<char>::allocator(&v908);
    std::string::string(&v907.m_currentSection, "start_day", &v908);
    std::allocator<char>::allocator(&v910);
    std::string::string(&v909, "SCORE_SHOP", &v910);
    v123 = Answer::Inifile::getIntValue(&ini, &v909, &v907.m_currentSection);
    thisa->m_vStartDay[42] = v123;
    std::string::~string(&v909);
    std::allocator<char>::~allocator(&v910);
    std::string::~string(&v907.m_currentSection);
    std::allocator<char>::~allocator(&v908);
    std::allocator<char>::allocator(&v912);
    std::string::string(&v911, "end_day", &v912);
    std::allocator<char>::allocator(&v914);
    std::string::string(&v913, "SCORE_SHOP", &v914);
    v124 = Answer::Inifile::getIntValue(&ini, &v913, &v911);
    thisa->m_vEndDay[42] = v124;
    std::string::~string(&v913);
    std::allocator<char>::~allocator(&v914);
    std::string::~string(&v911);
    std::allocator<char>::~allocator(&v912);
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK) )
  {
    std::allocator<char>::allocator(&v916);
    std::string::string(&v915, "start_day", &v916);
    std::allocator<char>::allocator(&v918);
    std::string::string(&v917, "BOSS_SCORE_RANK", &v918);
    v125 = Answer::Inifile::getIntValue(&ini, &v917, &v915);
    thisa->m_vStartDay[43] = v125;
    std::string::~string(&v917);
    std::allocator<char>::~allocator(&v918);
    std::string::~string(&v915);
    std::allocator<char>::~allocator(&v916);
    std::allocator<char>::allocator(&v920);
    std::string::string(&v919, "end_day", &v920);
    std::allocator<char>::allocator(&v922);
    std::string::string(&v921, "BOSS_SCORE_RANK", &v922);
    v126 = Answer::Inifile::getIntValue(&ini, &v921, &v919);
    thisa->m_vEndDay[43] = v126;
    std::string::~string(&v921);
    std::allocator<char>::~allocator(&v922);
    std::string::~string(&v919);
    std::allocator<char>::~allocator(&v920);
    std::allocator<char>::allocator(&v924);
    std::string::string(&v923, "rank_size", &v924);
    std::allocator<char>::allocator(&v926);
    std::string::string(&v925, "BOSS_SCORE_RANK", &v926);
    v127 = Answer::Inifile::getIntValue(&ini, &v925, &v923);
    thisa->m_BossScoreRankSize = v127;
    std::string::~string(&v925);
    std::allocator<char>::~allocator(&v926);
    std::string::~string(&v923);
    std::allocator<char>::~allocator(&v924);
    std::allocator<char>::allocator(&v928);
    std::string::string(&v927, "rank_reward_size", &v928);
    std::allocator<char>::allocator(&v930);
    std::string::string(&v929, "BOSS_SCORE_RANK", &v930);
    v128 = Answer::Inifile::getIntValue(&ini, &v929, &v927);
    thisa->m_BossScoreRewardSize = v128;
    std::string::~string(&v929);
    std::allocator<char>::~allocator(&v930);
    std::string::~string(&v927);
    std::allocator<char>::~allocator(&v928);
    std::vector<int>::resize(&thisa->m_vBossScoreRankMail, thisa->m_BossScoreRewardSize, 0);
    std::vector<MemChrBag>::vector(&v931);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vBossScoreRankReward, thisa->m_BossScoreRewardSize, &v931);
    std::vector<MemChrBag>::~vector(&v931);
    for ( i_26 = 0; thisa->m_BossScoreRewardSize > i_26; ++i_26 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_26 + 1);
      v129 = std::vector<int>::operator[](&thisa->m_vBossScoreRankMail, i_26);
      std::allocator<char>::allocator(&v933);
      std::string::string(&v932, szCol, &v933);
      std::allocator<char>::allocator(&v935);
      std::string::string(&v934, "BOSS_SCORE_RANK", &v935);
      *v129 = Answer::Inifile::getIntValue(&ini, &v934, &v932);
      std::string::~string(&v934);
      std::allocator<char>::~allocator(&v935);
      std::string::~string(&v932);
      std::allocator<char>::~allocator(&v933);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_26 + 1);
      std::allocator<char>::allocator((char *)&v937.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v937.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v937.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v937.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v937.m_strMap._M_t._M_impl._M_header._M_right,
        "BOSS_SCORE_RANK",
        (char *)&v937.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v937,
        (const std::string *const)&ini,
        (const std::string *const)&v937.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v936, (const std::string *const)&v937);
      v130 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vBossScoreRankReward, i_26);
      std::vector<MemChrBag>::operator=(v130, &v936);
      std::vector<MemChrBag>::~vector(&v936);
      std::string::~string(&v937);
      std::string::~string(&v937.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v937.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v937.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v937.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::allocator<char>::allocator(&v938);
    std::string::string(&v937.m_currentSection, "get_size", &v938);
    std::allocator<char>::allocator(&v940);
    std::string::string(&v939, "BOSS_SCORE_RANK", &v940);
    v131 = Answer::Inifile::getIntValue(&ini, &v939, &v937.m_currentSection);
    thisa->m_GetReardSize = v131;
    std::string::~string(&v939);
    std::allocator<char>::~allocator(&v940);
    std::string::~string(&v937.m_currentSection);
    std::allocator<char>::~allocator(&v938);
    std::vector<int>::resize(&thisa->m_vBossScoreiLimit, thisa->m_GetReardSize, 0);
    std::vector<MemChrBag>::vector(&v941);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vBossScoreReward, thisa->m_GetReardSize, &v941);
    std::vector<MemChrBag>::~vector(&v941);
    std::vector<int>::resize(&thisa->m_vGetBossScoreMail, thisa->m_GetReardSize, 0);
    for ( i_27 = 0; thisa->m_GetReardSize > i_27; ++i_27 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_27 + 1);
      v132 = std::vector<int>::operator[](&thisa->m_vBossScoreiLimit, i_27);
      std::allocator<char>::allocator(&v943);
      std::string::string(&v942, szCol, &v943);
      std::allocator<char>::allocator(&v945);
      std::string::string(&v944, "BOSS_SCORE_RANK", &v945);
      *v132 = Answer::Inifile::getIntValue(&ini, &v944, &v942);
      std::string::~string(&v944);
      std::allocator<char>::~allocator(&v945);
      std::string::~string(&v942);
      std::allocator<char>::~allocator(&v943);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "get_mail%d", i_27 + 1);
      v133 = std::vector<int>::operator[](&thisa->m_vGetBossScoreMail, i_27);
      std::allocator<char>::allocator(&v947);
      std::string::string(&v946, szCol, &v947);
      std::allocator<char>::allocator(&v949);
      std::string::string(&v948, "BOSS_SCORE_RANK", &v949);
      *v133 = Answer::Inifile::getIntValue(&ini, &v948, &v946);
      std::string::~string(&v948);
      std::allocator<char>::~allocator(&v949);
      std::string::~string(&v946);
      std::allocator<char>::~allocator(&v947);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "get_reward%d", i_27 + 1);
      std::allocator<char>::allocator((char *)&v951.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v951.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v951.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v951.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v951.m_strMap._M_t._M_impl._M_header._M_right,
        "BOSS_SCORE_RANK",
        (char *)&v951.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v951,
        (const std::string *const)&ini,
        (const std::string *const)&v951.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v950, (const std::string *const)&v951);
      v134 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vBossScoreReward, i_27);
      std::vector<MemChrBag>::operator=(v134, &v950);
      std::vector<MemChrBag>::~vector(&v950);
      std::string::~string(&v951);
      std::string::~string(&v951.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v951.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v951.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v951.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
  {
    std::allocator<char>::allocator(&v952);
    std::string::string(&v951.m_currentSection, "start_day", &v952);
    std::allocator<char>::allocator(&v954);
    std::string::string(&v953, "FAT_BOSS_SCORE_DRAW", &v954);
    v135 = Answer::Inifile::getIntValue(&ini, &v953, &v951.m_currentSection);
    thisa->m_vStartDay[44] = v135;
    std::string::~string(&v953);
    std::allocator<char>::~allocator(&v954);
    std::string::~string(&v951.m_currentSection);
    std::allocator<char>::~allocator(&v952);
    std::allocator<char>::allocator(&v956);
    std::string::string(&v955, "end_day", &v956);
    std::allocator<char>::allocator(&v958);
    std::string::string(&v957, "FAT_BOSS_SCORE_DRAW", &v958);
    v136 = Answer::Inifile::getIntValue(&ini, &v957, &v955);
    thisa->m_vEndDay[44] = v136;
    std::string::~string(&v957);
    std::allocator<char>::~allocator(&v958);
    std::string::~string(&v955);
    std::allocator<char>::~allocator(&v956);
    std::allocator<char>::allocator(&v960);
    std::string::string(&v959, "socre_size", &v960);
    std::allocator<char>::allocator(&v962);
    std::string::string(&v961, "FAT_BOSS_SCORE_DRAW", &v962);
    v137 = Answer::Inifile::getIntValue(&ini, &v961, &v959);
    thisa->m_nScoreSize = v137;
    std::string::~string(&v961);
    std::allocator<char>::~allocator(&v962);
    std::string::~string(&v959);
    std::allocator<char>::~allocator(&v960);
    std::vector<int>::resize(&thisa->m_vScoreLimit, thisa->m_nScoreSize, 0);
    for ( i_28 = 0; thisa->m_nScoreSize > i_28; ++i_28 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "socre_limit%d", i_28 + 1);
      v138 = std::vector<int>::operator[](&thisa->m_vScoreLimit, i_28);
      std::allocator<char>::allocator(&v964);
      std::string::string(&v963, szCol, &v964);
      std::allocator<char>::allocator(&v966);
      std::string::string(&v965, "FAT_BOSS_SCORE_DRAW", &v966);
      *v138 = Answer::Inifile::getIntValue(&ini, &v965, &v963);
      std::string::~string(&v965);
      std::allocator<char>::~allocator(&v966);
      std::string::~string(&v963);
      std::allocator<char>::~allocator(&v964);
    }
    std::allocator<char>::allocator(&v968);
    std::string::string(&v967, "daily_recharge_size", &v968);
    std::allocator<char>::allocator(&v970);
    std::string::string(&v969, "FAT_BOSS_SCORE_DRAW", &v970);
    v139 = Answer::Inifile::getIntValue(&ini, &v969, &v967);
    thisa->m_nDailyRechargeDrawSize = v139;
    std::string::~string(&v969);
    std::allocator<char>::~allocator(&v970);
    std::string::~string(&v967);
    std::allocator<char>::~allocator(&v968);
    std::vector<int>::resize(&thisa->m_nDailyRechargeDrawLimit, thisa->m_nDailyRechargeDrawSize, 0);
    for ( i_29 = 0; thisa->m_nDailyRechargeDrawSize > i_29; ++i_29 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "recharge_limit%d", i_29 + 1);
      v140 = std::vector<int>::operator[](&thisa->m_nDailyRechargeDrawLimit, i_29);
      std::allocator<char>::allocator(&v972);
      std::string::string(&v971, szCol, &v972);
      std::allocator<char>::allocator(&v974);
      std::string::string(&v973, "FAT_BOSS_SCORE_DRAW", &v974);
      *v140 = Answer::Inifile::getIntValue(&ini, &v973, &v971);
      std::string::~string(&v973);
      std::allocator<char>::~allocator(&v974);
      std::string::~string(&v971);
      std::allocator<char>::~allocator(&v972);
    }
    std::allocator<char>::allocator(&v976);
    std::string::string(&v975, "reward_size", &v976);
    std::allocator<char>::allocator(&v978);
    std::string::string(&v977, "FAT_BOSS_SCORE_DRAW", &v978);
    v141 = Answer::Inifile::getIntValue(&ini, &v977, &v975);
    thisa->m_nRewardSize = v141;
    std::string::~string(&v977);
    std::allocator<char>::~allocator(&v978);
    std::string::~string(&v975);
    std::allocator<char>::~allocator(&v976);
    v979.nItemId = 0;
    v979.nItemClass = 0;
    v979.nItemCount = 0;
    v979.nBind = 0;
    *(_QWORD *)&v979.nRate = 0;
    *(_OWORD *)&v153.nItemId = *(_OWORD *)&v979.nItemId;
    *(_QWORD *)&v153.nRate = 0;
    std::vector<RateItem>::resize(&thisa->m_vBossScoreDrawReward, thisa->m_nRewardSize, v153);
    for ( i_30 = 0; thisa->m_nRewardSize > i_30; ++i_30 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_30 + 1);
      v142 = std::vector<RateItem>::operator[](&thisa->m_vBossScoreDrawReward, i_30);
      std::allocator<char>::allocator(&v981);
      std::allocator<char>::allocator((char *)&v982.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v982.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v982.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v982.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v982.m_strMap._M_t._M_impl._M_header._M_right,
        "FAT_BOSS_SCORE_DRAW",
        (char *)&v982.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v982,
        (const std::string *const)&ini,
        (const std::string *const)&v982.m_strMap._M_t._M_impl._M_header._M_right);
      v143 = std::string::c_str((std::string *)&v982);
      std::string::string(&strItem, v143, &v981);
      CItemHelper::parseRateItemDataString((RateItem *)&v155, &strItem);
      *v142 = *(RateItem *)&v155.itemId;
      std::string::~string(&strItem);
      std::string::~string(&v982);
      std::string::~string(&v982.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v982.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v982.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v982.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::~allocator(&v981);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_GOU_WU_CHE) )
  {
    std::allocator<char>::allocator(&v983);
    std::string::string(&v982.m_currentSection, "start_day", &v983);
    std::allocator<char>::allocator(&v985);
    std::string::string(&v984, "FAT_GOU_WU_CHE", &v985);
    v144 = Answer::Inifile::getIntValue(&ini, &v984, &v982.m_currentSection);
    thisa->m_vStartDay[45] = v144;
    std::string::~string(&v984);
    std::allocator<char>::~allocator(&v985);
    std::string::~string(&v982.m_currentSection);
    std::allocator<char>::~allocator(&v983);
    std::allocator<char>::allocator(&v987);
    std::string::string(&v986, "end_day", &v987);
    std::allocator<char>::allocator(&v989);
    std::string::string(&v988, "FAT_GOU_WU_CHE", &v989);
    v145 = Answer::Inifile::getIntValue(&ini, &v988, &v986);
    thisa->m_vEndDay[45] = v145;
    std::string::~string(&v988);
    std::allocator<char>::~allocator(&v989);
    std::string::~string(&v986);
    std::allocator<char>::~allocator(&v987);
    std::allocator<char>::allocator(&v991);
    std::string::string(&v990, "item_size", &v991);
    std::allocator<char>::allocator(&v993);
    std::string::string(&v992, "FAT_GOU_WU_CHE", &v993);
    v146 = Answer::Inifile::getIntValue(&ini, &v992, &v990);
    thisa->m_nGouWuCheSize = v146;
    std::string::~string(&v992);
    std::allocator<char>::~allocator(&v993);
    std::string::~string(&v990);
    std::allocator<char>::~allocator(&v991);
    std::vector<int>::resize(&thisa->m_vGouWuCheGiftPrice, thisa->m_nGouWuCheSize, 0);
    v994.itemId = 0;
    v994.itemClass = 0;
    v994.itemCount = 0;
    v994.bind = 0;
    v994.endTime = 0;
    v994.srcId = 0;
    *(_OWORD *)&v154.itemId = *(_OWORD *)&v994.itemId;
    *(_OWORD *)&v154.endTime = *(unsigned __int64 *)&v994.endTime;
    std::vector<MemChrBag>::resize(&thisa->m_vGouWuCheItem, thisa->m_nGouWuCheSize, v154);
    for ( i_31 = 0; thisa->m_nGouWuCheSize > i_31; ++i_31 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_31 + 1);
      v147 = std::vector<MemChrBag>::operator[](&thisa->m_vGouWuCheItem, i_31);
      std::allocator<char>::allocator((char *)&v995.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v995.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v995.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v995.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v995.m_strMap._M_t._M_impl._M_header._M_right,
        "FAT_GOU_WU_CHE",
        (char *)&v995.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v995,
        (const std::string *const)&ini,
        (const std::string *const)&v995.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemString(&v155, (const std::string *const)&v995);
      *v147 = v155;
      std::string::~string(&v995);
      std::string::~string(&v995.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v995.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v995.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v995.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "Price%d", i_31 + 1);
      v148 = std::vector<int>::operator[](&thisa->m_vGouWuCheGiftPrice, i_31);
      std::allocator<char>::allocator(&v996);
      std::string::string(&v995.m_currentSection, szCol, &v996);
      std::allocator<char>::allocator(&v998);
      std::string::string(&v997, "FAT_GOU_WU_CHE", &v998);
      *v148 = Answer::Inifile::getIntValue(&ini, &v997, &v995.m_currentSection);
      std::string::~string(&v997);
      std::allocator<char>::~allocator(&v998);
      std::string::~string(&v995.m_currentSection);
      std::allocator<char>::~allocator(&v996);
    }
  }
  std::allocator<char>::allocator(&v1000);
  std::string::string(&v999, "start_day", &v1000);
  std::allocator<char>::allocator(&v1002);
  std::string::string(&v1001, "LIAN_RECHARGE", &v1002);
  v149 = Answer::Inifile::getIntValue(&ini, &v1001, &v999);
  thisa->m_vStartDay[46] = v149;
  std::string::~string(&v1001);
  std::allocator<char>::~allocator(&v1002);
  std::string::~string(&v999);
  std::allocator<char>::~allocator(&v1000);
  std::allocator<char>::allocator(&v1004);
  std::string::string(&v1003, "end_day", &v1004);
  std::allocator<char>::allocator(&v1006);
  std::string::string(&v1005, "LIAN_RECHARGE", &v1006);
  v150 = Answer::Inifile::getIntValue(&ini, &v1005, &v1003);
  thisa->m_vEndDay[46] = v150;
  std::string::~string(&v1005);
  std::allocator<char>::~allocator(&v1006);
  std::string::~string(&v1003);
  std::allocator<char>::~allocator(&v1004);
  for ( i_32 = 0; i_32 <= 1; ++i_32 )
  {
    memset(&stu, 0, sizeof(stu));
    std::vector<std::vector<MemChrBag>>::vector(&stu.vGiftVector);
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "type%d", i_32);
    std::allocator<char>::allocator(&v1008);
    std::string::string(&v1007, szCol, &v1008);
    std::allocator<char>::allocator(&v1010);
    std::string::string(&v1009, "LIAN_RECHARGE", &v1010);
    stu.nValues = Answer::Inifile::getIntValue(&ini, &v1009, &v1007);
    std::string::~string(&v1009);
    std::allocator<char>::~allocator(&v1010);
    std::string::~string(&v1007);
    std::allocator<char>::~allocator(&v1008);
    for ( j_0 = 0; j_0 <= 3; ++j_0 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "gift%d_%d", i_32, j_0);
      std::allocator<char>::allocator((char *)&v1012.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v1012.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v1012.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v1012.m_currentSection._M_dataplus._M_p + 3);
      std::string::string(
        &v1012.m_strMap._M_t._M_impl._M_header._M_right,
        "LIAN_RECHARGE",
        (char *)&v1012.m_currentSection._M_dataplus._M_p + 3);
      Answer::Inifile::getStrValue(
        &v1012,
        (const std::string *const)&ini,
        (const std::string *const)&v1012.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v1011, (const std::string *const)&v1012);
      std::vector<std::vector<MemChrBag>>::push_back(&stu.vGiftVector, &v1011);
      std::vector<MemChrBag>::~vector(&v1011);
      std::string::~string(&v1012);
      std::string::~string(&v1012.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v1012.m_currentSection._M_dataplus._M_p + 3);
      std::string::~string(&v1012.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v1012.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::vector<LianRechargeCfg>::push_back(&thisa->m_LianRechargeCfgVt, &stu);
    LianRechargeCfg::~LianRechargeCfg(&stu);
  }
  Answer::Inifile::~Inifile(&ini);
}


#####################################
void __cdecl CFestivalDoubleEleven::OnRecharge(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t OldValue,
        int32_t AddValue)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v7; // rax
  bool NeedSendIcon; // [rsp+2Fh] [rbp-11h]

  if ( player )
  {
    NeedSendIcon = 0;
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_LIAN_CHONG) )
    {
      if ( std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 0)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 0)->nValues )
      {
        OperateLimit = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1634, 1);
        NeedSendIcon = 1;
      }
      if ( std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 1u)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 1u)->nValues )
      {
        v7 = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(v7, 1635, 1);
        NeedSendIcon = 1;
      }
    }
    if ( NeedSendIcon )
      CFestivalDoubleEleven::SendIconState(this, player);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::loadRankData(CFestivalDoubleEleven *const this, int32_t line)
{
  DBService *v2; // rax
  DBService *v3; // rax
  DBService *v4; // rax
  DBService *v5; // rax
  DBService *v6; // rax
  DBService *v7; // rax
  DBService *v8; // rax
  DBService *v9; // rax
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK) )
  {
    if ( line == 9 )
    {
      v2 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v2, 4, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadDrawRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
  {
    if ( line == 9 )
    {
      for ( i = 0; this->m_nEndDay > i; ++i )
      {
        v3 = Answer::Singleton<DBService>::instance();
        DBService::LoadDoubleElevenRank(v3, 12, i);
      }
    }
    else
    {
      CFestivalDoubleEleven::loadXiaoFeiRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK) )
  {
    if ( line == 9 )
    {
      v4 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v4, 16, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadXiaoFeiSumRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK) )
  {
    if ( line == 9 )
    {
      v5 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v5, 32, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadRechargeSumRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK) )
  {
    if ( line == 9 )
    {
      v6 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v6, 33, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadCrossRechargeSumRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK) )
  {
    if ( line == 9 )
    {
      v7 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v7, 34, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadCrossXiaoFeiSumRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_CHOU_JIANG_RANK) )
  {
    if ( line == 9 )
    {
      v8 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v8, 37, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadCrossChouJiangRank(this);
    }
  }
  if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK) )
  {
    if ( line == 9 )
    {
      v9 = Answer::Singleton<DBService>::instance();
      DBService::LoadDoubleElevenRank(v9, 43, 0);
    }
    else
    {
      CFestivalDoubleEleven::loadBossScoreRank(this);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::resetRankData(CFestivalDoubleEleven *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-40h] BYREF

  if ( line == 1 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    Answer::MySqlDBGuard::excute(&db, "DELETE FROM mem_double_eleven_rank");
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
  std::map<signed char,std::vector<FestivalRank>>::clear(&this->m_mDrawRank);
  std::map<signed char,std::vector<std::vector<FestivalRank>>>::clear(&this->m_mXiaoFeiRank);
  std::map<signed char,std::vector<FestivalRank>>::clear(&this->m_mXiaoFeiSumRank);
  std::map<signed char,std::vector<FestivalRank>>::clear(&this->m_mRechargeSumRank);
  std::map<signed char,std::vector<FestivalRank>>::clear(&this->m_mCrossXiaoFeiSumRank);
  std::map<signed char,std::vector<FestivalRank>>::clear(&this->m_mCrossRechargeSumRank);
  std::map<signed char,std::vector<FestivalRank>>::clear(&this->m_mCrossChouJiangRank);
}


#####################################
void __cdecl CFestivalDoubleEleven::resetPlayerData(CFestivalDoubleEleven *const this)
{
  int32_t m_nVersion; // ebx
  GameService *v2; // rax

  m_nVersion = this->m_nVersion;
  v2 = Answer::Singleton<GameService>::instance();
  GameService::ResetFestivalData(v2, m_nVersion);
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::loadVersion(CFestivalDoubleEleven *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  const char *v3; // rax
  Answer::MySqlQuery *v4; // rax
  const char *StringValue; // rax
  int32_t v6; // ebx
  char szSQL[4096]; // [rsp+10h] [rbp-1070h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-40h] BYREF
  std::string tname; // [rsp+1060h] [rbp-20h] BYREF
  _BYTE v12[17]; // [rsp+106Fh] [rbp-11h] BYREF

  v2 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
  memset(szSQL, 0, sizeof(szSQL));
  std::allocator<char>::allocator(v12);
  std::string::string(&tname, "sys_server_config", v12);
  std::allocator<char>::~allocator(v12);
  if ( line == 9 )
    std::string::operator=(&tname, "cross_sys_server_config");
  v3 = (const char *)std::string::c_str(&tname);
  snprintf(szSQL, 0xFFFu, "SELECT * FROM `%s` WHERE `name`='FESTIVAL_VERSION'", v3);
  v4 = Answer::MySqlDBGuard::query(&db, szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v4);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "value", &byte_8D8B2F);
    v6 = atoi(StringValue);
  }
  else
  {
    v6 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  std::string::~string(&tname);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  return v6;
}


#####################################
void __cdecl CFestivalDoubleEleven::saveVersion(CFestivalDoubleEleven *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  int32_t m_nVersion; // ebx
  const char *v4; // rax
  char szSQL[4096]; // [rsp+20h] [rbp-1050h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1020h] [rbp-50h] BYREF
  std::string tname; // [rsp+1050h] [rbp-20h] BYREF
  char v8; // [rsp+105Bh] [rbp-15h] BYREF
  int32_t nNowTime; // [rsp+105Ch] [rbp-14h]

  v2 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
  memset(szSQL, 0, sizeof(szSQL));
  nNowTime = Answer::DayTime::now();
  std::allocator<char>::allocator(&v8);
  std::string::string(&tname, "sys_server_config", &v8);
  std::allocator<char>::~allocator(&v8);
  if ( line == 9 )
    std::string::operator=(&tname, "cross_sys_server_config");
  m_nVersion = this->m_nVersion;
  v4 = (const char *)std::string::c_str(&tname);
  snprintf(
    szSQL,
    0xFFFu,
    "INSERT INTO `%s` ( `name`, `value`, `refresh_time` ) VALUES ( 'FESTIVAL_VERSION', %d, %d ) ON DUPLICATE KEY UPDATE `"
    "value`=%d, `refresh_time`=%d",
    v4,
    m_nVersion,
    nNowTime,
    m_nVersion,
    nNowTime);
  Answer::MySqlDBGuard::excute(&db, szSQL);
  std::string::~string(&tname);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::loadDrawRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=4 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_nDrawRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_nDrawRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateDrawRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nDrawRankSize )
  {
    CFestivalDoubleEleven::checkDrawRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mDrawRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mDrawRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mDrawRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mDrawRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkDrawRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mDrawRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mDrawRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nDrawRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mDrawRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkDrawRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mDrawRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mDrawRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_nDrawRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 4, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::sendDrawRankMail(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mDrawRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mDrawRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < this->m_nDrawRankSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vDrawRankReward, i);
          v3 = *std::vector<int>::operator[](&this->m_vDrawRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(
            v6,
            v5,
            nCharId,
            v3,
            v2,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_DRAW_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::GetIconState(
        CFestivalDoubleEleven *const this,
        Player *player,
        IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CFestivalDoubleEleven::needShowIcon(this) )
    {
      CFestivalDoubleEleven::getIconState(&__x, this, player);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::SendIconState(CFestivalDoubleEleven *const this, Player *player)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CFestivalDoubleEleven::needShowIcon(this) )
    {
      CFestivalDoubleEleven::getIconState(&stu, this, player);
      Player::SendIconState(player, &stu);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::hideIcon(CFestivalDoubleEleven *const this, int32_t nIconId)
{
  GameService *v2; // rax
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 1 )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nIconId);
      Answer::NetPacket::writeInt8(packet, 4);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v5, 0, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::SendActivityInfo(CFestivalDoubleEleven *const this, Player *player)
{
  int8_t v2; // bl
  GameService *v3; // rax
  int8_t v4; // al
  int32_t TodayPayGold; // eax
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // eax
  CExtOperateLimit *v8; // rax
  int32_t v9; // eax
  size_t v10; // rbx
  std::vector<FestivalRank> *v11; // rax
  FestivalRank *v12; // rax
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rax
  CExtOperateLimit *v16; // rax
  int32_t v17; // eax
  CExtOperateLimit *v18; // rax
  int32_t m_nDailyLimitShopLimit; // ebx
  CExtOperateLimit *v20; // rax
  int32_t v21; // eax
  CExtOperateLimit *v22; // rax
  CExtOperateLimit *v23; // rax
  int32_t v24; // eax
  int32_t OnlineTimeRewardTime; // eax
  int8_t v26; // al
  int8_t Record; // al
  CExtOperateLimit *v28; // rax
  int32_t v29; // eax
  int8_t v30; // al
  CExtCharWish *CharWish; // rax
  CExtOperateLimit *v32; // rax
  int32_t v33; // eax
  size_t v34; // rbx
  size_t v35; // r12
  std::vector<std::vector<FestivalRank>> *v36; // rax
  std::vector<FestivalRank> *v37; // rax
  FestivalRank *v38; // rax
  size_t v39; // rbx
  size_t v40; // r12
  std::vector<std::vector<FestivalRank>> *v41; // rax
  std::vector<FestivalRank> *v42; // rax
  FestivalRank *v43; // rax
  CExtOperateLimit *v44; // rax
  int32_t v45; // eax
  CExtOperateLimit *v46; // rax
  int32_t v47; // eax
  int32_t v48; // eax
  CExtOperateLimit *v49; // rax
  CExtOperateLimit *v50; // rax
  int32_t v51; // eax
  size_t v52; // rbx
  std::vector<FestivalRank> *v53; // rax
  FestivalRank *v54; // rax
  size_t v55; // rbx
  std::vector<FestivalRank> *v56; // rax
  FestivalRank *v57; // rax
  size_t v58; // rbx
  std::vector<FestivalRank> *v59; // rax
  FestivalRank *v60; // rax
  int32_t m_nDay; // eax
  CExtOperateLimit *v62; // rax
  CExtOperateLimit *v63; // rax
  int32_t v64; // eax
  CExtOperateLimit *v65; // rax
  int32_t v66; // eax
  CExtOperateLimit *v67; // rax
  int32_t v68; // eax
  CExtOperateLimit *v69; // rax
  CExtOperateLimit *v70; // rax
  int32_t v71; // eax
  CExtOperateLimit *v72; // rax
  CExtOperateLimit *v73; // rax
  CExtOperateLimit *v74; // rax
  int32_t v75; // eax
  CExtOperateLimit *v76; // rax
  int32_t v77; // eax
  CExtOperateLimit *v78; // rax
  int32_t v79; // eax
  CExtOperateLimit *v80; // rax
  CExtOperateLimit *v81; // rax
  int32_t v82; // eax
  CExtOperateLimit *v83; // rax
  int32_t v84; // eax
  CExtOperateLimit *v85; // rax
  int32_t v86; // eax
  CExtOperateLimit *v87; // rax
  CExtOperateLimit *v88; // rax
  int32_t v89; // eax
  size_t v90; // rbx
  std::vector<FestivalRank> *v91; // rax
  FestivalRank *v92; // rax
  size_t v93; // rbx
  std::vector<FestivalRank> *v94; // rax
  FestivalRank *v95; // rax
  size_t v96; // rbx
  std::vector<FestivalRank> *v97; // rax
  FestivalRank *v98; // rax
  size_t v99; // rbx
  std::vector<FestivalRank> *v100; // rax
  FestivalRank *v101; // rax
  size_t v102; // rbx
  std::vector<FestivalRank> *v103; // rax
  FestivalRank *v104; // rax
  CExtOperateLimit *v105; // rax
  int32_t v106; // eax
  CExtOperateLimit *v107; // rax
  int32_t v108; // eax
  int32_t v109; // eax
  int32_t v110; // eax
  int32_t v111; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v114; // bl
  GameService *v115; // rax
  Answer::MutexGuard lock_3; // [rsp+10h] [rbp-100h] BYREF
  Answer::MutexGuard lock_2; // [rsp+20h] [rbp-F0h] BYREF
  Answer::MutexGuard lock_1; // [rsp+30h] [rbp-E0h] BYREF
  Answer::MutexGuard lock_0; // [rsp+40h] [rbp-D0h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-C0h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-B1h] BYREF
  Answer::NetPacket *packet; // [rsp+60h] [rbp-B0h]
  int8_t nCount; // [rsp+6Fh] [rbp-A1h]
  uint32_t oldOffset; // [rsp+70h] [rbp-A0h]
  uint32_t newOffset; // [rsp+74h] [rbp-9Ch]
  int32_t i; // [rsp+78h] [rbp-98h]
  int32_t nRewardSign; // [rsp+7Ch] [rbp-94h]
  int32_t i_0; // [rsp+80h] [rbp-90h]
  int8_t nState; // [rsp+87h] [rbp-89h]
  int32_t nLandDays; // [rsp+88h] [rbp-88h]
  int32_t nRecord; // [rsp+8Ch] [rbp-84h]
  int32_t i_1; // [rsp+90h] [rbp-80h]
  int32_t i_2; // [rsp+94h] [rbp-7Ch]
  int32_t j; // [rsp+98h] [rbp-78h]
  int32_t nRewardSign_0; // [rsp+9Ch] [rbp-74h]
  int32_t i_3; // [rsp+A0h] [rbp-70h]
  int8_t nState_0; // [rsp+A7h] [rbp-69h]
  int32_t i_4; // [rsp+A8h] [rbp-68h]
  int32_t nSize; // [rsp+ACh] [rbp-64h]
  int32_t nRecord_0; // [rsp+B0h] [rbp-60h]
  int32_t i_5; // [rsp+B4h] [rbp-5Ch]
  int32_t j_0; // [rsp+B8h] [rbp-58h]
  int32_t nRewardSign_1; // [rsp+BCh] [rbp-54h]
  int32_t i_6; // [rsp+C0h] [rbp-50h]
  int8_t nState_1; // [rsp+C7h] [rbp-49h]
  int32_t nRewardSign_2; // [rsp+C8h] [rbp-48h]
  int32_t i_7; // [rsp+CCh] [rbp-44h]
  int8_t nState_2; // [rsp+D3h] [rbp-3Dh]
  int32_t nRecord_1; // [rsp+D4h] [rbp-3Ch]
  int32_t i_8; // [rsp+D8h] [rbp-38h]
  int32_t nRecord_2; // [rsp+DCh] [rbp-34h]
  int32_t i_9; // [rsp+E0h] [rbp-30h]
  int32_t nRewardSign_3; // [rsp+E4h] [rbp-2Ch]
  int32_t i_10; // [rsp+E8h] [rbp-28h]
  int8_t nState_3; // [rsp+EFh] [rbp-21h]
  int32_t i_11; // [rsp+F0h] [rbp-20h]
  int32_t i_12; // [rsp+F4h] [rbp-1Ch]
  int32_t nRecord_3; // [rsp+F8h] [rbp-18h]
  int32_t i_13; // [rsp+FCh] [rbp-14h]

  if ( player )
  {
    connid = Player::getConnId(player);
    v2 = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, v2, Answer::PackType::PACK_DISPATCH, 0x2EB8u);
    if ( packet )
    {
      nCount = 0;
      oldOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt8(packet, 0);
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_LAND) )
      {
        Answer::NetPacket::writeInt8(packet, 1);
        Answer::NetPacket::writeInt32(packet, this->m_nDay);
        v4 = !CFestivalDoubleEleven::canGetLandGift(this, player);
        Answer::NetPacket::writeInt8(packet, v4);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE) )
      {
        Answer::NetPacket::writeInt8(packet, 2);
        TodayPayGold = Player::GetTodayPayGold(player);
        Answer::NetPacket::writeInt32(packet, TodayPayGold);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW) )
      {
        Answer::NetPacket::writeInt8(packet, 3);
        OperateLimit = Player::GetOperateLimit(player);
        LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1601);
        Answer::NetPacket::writeInt32(packet, LimitCount);
        v8 = Player::GetOperateLimit(player);
        v9 = CExtOperateLimit::GetLimitCount(v8, 1602);
        Answer::NetPacket::writeInt32(packet, v9);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK) )
      {
        CFestivalDoubleEleven::checkDrawRankInvalid(this, connid);
        Answer::NetPacket::writeInt8(packet, 4);
        Answer::NetPacket::writeInt8(packet, this->m_nDrawRankSize);
        for ( i = 0; this->m_nDrawRankSize > i; ++i )
        {
          Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
          v10 = i;
          v11 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v12 = std::vector<FestivalRank>::operator[](v11, v10);
          Answer::NetPacket::writeUTF8(packet, &v12->strName);
          v13 = i;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          Answer::NetPacket::writeInt32(packet, v15->nScore);
          Answer::MutexGuard::~MutexGuard(&lock);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM) )
      {
        Answer::NetPacket::writeInt8(packet, 7);
        v16 = Player::GetOperateLimit(player);
        v17 = CExtOperateLimit::GetLimitCount(v16, 1603);
        Answer::NetPacket::writeInt32(packet, v17);
        v18 = Player::GetOperateLimit(player);
        nRewardSign = CExtOperateLimit::GetLimitCount(v18, 1604);
        Answer::NetPacket::writeInt8(packet, this->m_nHuoYueDuSumSize);
        for ( i_0 = 0; this->m_nHuoYueDuSumSize > i_0; ++i_0 )
        {
          nState = (nRewardSign >> i_0) & 1;
          Answer::NetPacket::writeInt8(packet, nState);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP) )
      {
        Answer::NetPacket::writeInt8(packet, 8);
        m_nDailyLimitShopLimit = this->m_nDailyLimitShopLimit;
        v20 = Player::GetOperateLimit(player);
        v21 = CExtOperateLimit::GetLimitCount(v20, 2034);
        Answer::NetPacket::writeInt32(packet, m_nDailyLimitShopLimit - v21);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM) )
      {
        Answer::NetPacket::writeInt8(packet, 9);
        nLandDays = CFestivalDoubleEleven::getLandSum(this, player);
        Answer::NetPacket::writeInt8(packet, nLandDays);
        v22 = Player::GetOperateLimit(player);
        nRecord = CExtOperateLimit::GetLimitCount(v22, 1614);
        for ( i_1 = 0; i_1 < nLandDays; ++i_1 )
          Answer::NetPacket::writeInt8(packet, (nRecord >> i_1) & 1);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME) )
      {
        Answer::NetPacket::writeInt8(packet, 10);
        v23 = Player::GetOperateLimit(player);
        v24 = CExtOperateLimit::GetLimitCount(v23, 2037);
        Answer::NetPacket::writeInt32(packet, v24);
        OnlineTimeRewardTime = CFestivalDoubleEleven::GetOnlineTimeRewardTime(this, player);
        Answer::NetPacket::writeInt32(packet, OnlineTimeRewardTime);
        v26 = this->m_nMinute >= this->m_nOnlineStartMinute && this->m_nMinute < this->m_nOnlineEndMinute;
        Answer::NetPacket::writeInt8(packet, v26);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_PET_GIFT) )
      {
        Answer::NetPacket::writeInt8(packet, 23);
        Record = Player::getRecord(player, 1631);
        Answer::NetPacket::writeInt8(packet, Record);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BEST_WISH) )
      {
        Answer::NetPacket::writeInt8(packet, 11);
        v28 = Player::GetOperateLimit(player);
        v29 = CExtOperateLimit::GetLimitCount(v28, 2026);
        Answer::NetPacket::writeInt32(packet, v29);
        v30 = !CFestivalDoubleEleven::canGetWishGift(this, player);
        Answer::NetPacket::writeInt8(packet, v30);
        CharWish = Player::GetCharWish(player);
        CExtCharWish::AppendWishInfo(CharWish, packet);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
      {
        CFestivalDoubleEleven::checkXiaoFeiRankInvalid(this, connid);
        Answer::NetPacket::writeInt8(packet, 12);
        v32 = Player::GetOperateLimit(player);
        v33 = CExtOperateLimit::GetLimitCount(v32, 2031);
        Answer::NetPacket::writeInt32(packet, v33);
        Answer::NetPacket::writeInt8(packet, this->m_nDay);
        Answer::NetPacket::writeInt8(packet, this->m_nEndDay);
        for ( i_2 = 0; this->m_nEndDay > i_2; ++i_2 )
        {
          Answer::NetPacket::writeInt8(packet, this->m_nXiaoFeiRankSize);
          for ( j = 0; this->m_nXiaoFeiRankSize > j; ++j )
          {
            Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
            v34 = j;
            v35 = i_2;
            v36 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &this->m_mXiaoFeiRank,
                    &connid);
            v37 = std::vector<std::vector<FestivalRank>>::operator[](v36, v35);
            v38 = std::vector<FestivalRank>::operator[](v37, v34);
            Answer::NetPacket::writeUTF8(packet, &v38->strName);
            v39 = j;
            v40 = i_2;
            v41 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &this->m_mXiaoFeiRank,
                    &connid);
            v42 = std::vector<std::vector<FestivalRank>>::operator[](v41, v40);
            v43 = std::vector<FestivalRank>::operator[](v42, v39);
            Answer::NetPacket::writeInt32(packet, v43->nScore);
            Answer::MutexGuard::~MutexGuard(&lock_0);
          }
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW) )
      {
        Answer::NetPacket::writeInt8(packet, 13);
        v44 = Player::GetOperateLimit(player);
        v45 = CExtOperateLimit::GetLimitCount(v44, 1605);
        Answer::NetPacket::writeInt32(packet, v45);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_GOU_WU_CHE) )
      {
        Answer::NetPacket::writeInt8(packet, 45);
        v46 = Player::GetOperateLimit(player);
        v47 = CExtOperateLimit::GetLimitCount(v46, 2112);
        Answer::NetPacket::writeInt32(packet, v47);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE_2) )
      {
        Answer::NetPacket::writeInt8(packet, 15);
        v48 = Player::GetTodayPayGold(player);
        Answer::NetPacket::writeInt32(packet, v48);
        v49 = Player::GetOperateLimit(player);
        nRewardSign_0 = CExtOperateLimit::GetLimitCount(v49, 2033);
        Answer::NetPacket::writeInt8(packet, this->m_nDailyRechargeSize);
        for ( i_3 = 0; this->m_nDailyRechargeSize > i_3; ++i_3 )
        {
          nState_0 = (nRewardSign_0 >> i_3) & 1;
          Answer::NetPacket::writeInt8(packet, nState_0);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK) )
      {
        CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(this, connid);
        Answer::NetPacket::writeInt8(packet, 16);
        v50 = Player::GetOperateLimit(player);
        v51 = CExtOperateLimit::GetLimitCount(v50, 1605);
        Answer::NetPacket::writeInt32(packet, v51);
        Answer::NetPacket::writeInt8(packet, this->m_nXiaoFeiSumRankSize);
        for ( i_4 = 0; this->m_nXiaoFeiSumRankSize > i_4; ++i_4 )
        {
          Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
          v52 = i_4;
          v53 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v54 = std::vector<FestivalRank>::operator[](v53, v52);
          Answer::NetPacket::writeInt64(packet, v54->nCharId);
          v55 = i_4;
          v56 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v57 = std::vector<FestivalRank>::operator[](v56, v55);
          Answer::NetPacket::writeUTF8(packet, &v57->strName);
          v58 = i_4;
          v59 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v60 = std::vector<FestivalRank>::operator[](v59, v58);
          Answer::NetPacket::writeInt32(packet, v60->nScore);
          Answer::MutexGuard::~MutexGuard(&lock_1);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_GIFT_SHOP) )
      {
        Answer::NetPacket::writeInt8(packet, 17);
        if ( this->m_nDay >= this->m_vEndDay[17] )
          m_nDay = this->m_vEndDay[17];
        else
          m_nDay = this->m_nDay;
        nSize = m_nDay - this->m_vStartDay[17];
        v62 = Player::GetOperateLimit(player);
        nRecord_0 = CExtOperateLimit::GetLimitCount(v62, 1607);
        Answer::NetPacket::writeInt8(packet, nSize);
        for ( i_5 = 0; i_5 <= nSize; ++i_5 )
        {
          Answer::NetPacket::writeInt8(packet, this->m_nGiftShopSize);
          for ( j_0 = 0; this->m_nGiftShopSize > j_0; ++j_0 )
            Answer::NetPacket::writeInt8(packet, (nRecord_0 >> (j_0 + i_5 * LOBYTE(this->m_nGiftShopSize))) & 1);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
      {
        Answer::NetPacket::writeInt8(packet, 19);
        v63 = Player::GetOperateLimit(player);
        v64 = CExtOperateLimit::GetLimitCount(v63, 1630);
        Answer::NetPacket::writeInt32(packet, v64);
        v65 = Player::GetOperateLimit(player);
        v66 = CExtOperateLimit::GetLimitCount(v65, 1629);
        Answer::NetPacket::writeInt32(packet, v66);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_GIFT) )
      {
        Answer::NetPacket::writeInt8(packet, 21);
        v67 = Player::GetOperateLimit(player);
        v68 = CExtOperateLimit::GetLimitCount(v67, 1615);
        Answer::NetPacket::writeInt32(packet, v68);
        v69 = Player::GetOperateLimit(player);
        nRewardSign_1 = CExtOperateLimit::GetLimitCount(v69, 1616);
        Answer::NetPacket::writeInt8(packet, this->m_nRechargeSumSize);
        for ( i_6 = 0; this->m_nRechargeSumSize > i_6; ++i_6 )
        {
          nState_1 = (nRewardSign_1 >> i_6) & 1;
          Answer::NetPacket::writeInt8(packet, nState_1);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT) )
      {
        Answer::NetPacket::writeInt8(packet, 22);
        v70 = Player::GetOperateLimit(player);
        v71 = CExtOperateLimit::GetLimitCount(v70, 1605);
        Answer::NetPacket::writeInt32(packet, v71);
        v72 = Player::GetOperateLimit(player);
        nRewardSign_2 = CExtOperateLimit::GetLimitCount(v72, 1606);
        Answer::NetPacket::writeInt8(packet, this->m_nXiaoFeiSumSize);
        for ( i_7 = 0; this->m_nXiaoFeiSumSize > i_7; ++i_7 )
        {
          nState_2 = (nRewardSign_2 >> i_7) & 1;
          Answer::NetPacket::writeInt8(packet, nState_2);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP_2) )
      {
        Answer::NetPacket::writeInt8(packet, 25);
        v73 = Player::GetOperateLimit(player);
        nRecord_1 = CExtOperateLimit::GetLimitCount(v73, 2035);
        Answer::NetPacket::writeInt8(packet, this->m_nDailyLimitShop2Size);
        for ( i_8 = 0; this->m_nDailyLimitShop2Size > i_8; ++i_8 )
          Answer::NetPacket::writeInt8(packet, (nRecord_1 >> i_8) & 1);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) )
      {
        Answer::NetPacket::writeInt8(packet, 26);
        v74 = Player::GetOperateLimit(player);
        v75 = CExtOperateLimit::GetLimitCount(v74, 1617);
        Answer::NetPacket::writeInt32(packet, v75);
        v76 = Player::GetOperateLimit(player);
        v77 = CExtOperateLimit::GetLimitCount(v76, 1618);
        Answer::NetPacket::writeInt32(packet, v77);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_DRAW) )
      {
        Answer::NetPacket::writeInt8(packet, 27);
        v78 = Player::GetOperateLimit(player);
        v79 = CExtOperateLimit::GetLimitCount(v78, 1615);
        Answer::NetPacket::writeInt32(packet, v79);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_GIFT) )
      {
        Answer::NetPacket::writeInt8(packet, 28);
        v80 = Player::GetOperateLimit(player);
        nRecord_2 = CExtOperateLimit::GetLimitCount(v80, 1619);
        Answer::NetPacket::writeInt8(packet, this->m_nBuyGiftSize);
        for ( i_9 = 0; this->m_nBuyGiftSize > i_9; ++i_9 )
          Answer::NetPacket::writeInt8(packet, (nRecord_2 >> i_9) & 1);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
      {
        Answer::NetPacket::writeInt8(packet, 29);
        v81 = Player::GetOperateLimit(player);
        v82 = CExtOperateLimit::GetLimitCount(v81, 1620);
        Answer::NetPacket::writeInt32(packet, v82);
        v83 = Player::GetOperateLimit(player);
        v84 = CExtOperateLimit::GetLimitCount(v83, 1621);
        Answer::NetPacket::writeInt32(packet, v84);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM) )
      {
        Answer::NetPacket::writeInt8(packet, 31);
        v85 = Player::GetOperateLimit(player);
        v86 = CExtOperateLimit::GetLimitCount(v85, 1622);
        Answer::NetPacket::writeInt32(packet, v86);
        v87 = Player::GetOperateLimit(player);
        nRewardSign_3 = CExtOperateLimit::GetLimitCount(v87, 1623);
        Answer::NetPacket::writeInt8(packet, this->m_nPetIllusionItemSize);
        for ( i_10 = 0; this->m_nPetIllusionItemSize > i_10; ++i_10 )
        {
          nState_3 = (nRewardSign_3 >> i_10) & 1;
          Answer::NetPacket::writeInt8(packet, nState_3);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK) )
      {
        CFestivalDoubleEleven::checkRechargeSumRankInvalid(this, connid);
        Answer::NetPacket::writeInt8(packet, 32);
        v88 = Player::GetOperateLimit(player);
        v89 = CExtOperateLimit::GetLimitCount(v88, 1615);
        Answer::NetPacket::writeInt32(packet, v89);
        Answer::NetPacket::writeInt8(packet, this->m_nRechargeSumRankSize);
        for ( i_11 = 0; this->m_nRechargeSumRankSize > i_11; ++i_11 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
          v90 = i_11;
          v91 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
          v92 = std::vector<FestivalRank>::operator[](v91, v90);
          Answer::NetPacket::writeUTF8(packet, &v92->strName);
          v93 = i_11;
          v94 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
          v95 = std::vector<FestivalRank>::operator[](v94, v93);
          Answer::NetPacket::writeInt32(packet, v95->nScore);
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK) )
      {
        CFestivalDoubleEleven::checkBossScoreRankInvalid(this, connid);
        Answer::NetPacket::writeInt8(packet, 43);
        Answer::NetPacket::writeInt8(packet, this->m_BossScoreRankSize);
        for ( i_12 = 0; this->m_BossScoreRankSize > i_12; ++i_12 )
        {
          Answer::MutexGuard::MutexGuard(&lock_3, &this->m_lock);
          v96 = i_12;
          v97 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
          v98 = std::vector<FestivalRank>::operator[](v97, v96);
          Answer::NetPacket::writeInt64(packet, v98->nCharId);
          v99 = i_12;
          v100 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
          v101 = std::vector<FestivalRank>::operator[](v100, v99);
          Answer::NetPacket::writeUTF8(packet, &v101->strName);
          v102 = i_12;
          v103 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
          v104 = std::vector<FestivalRank>::operator[](v103, v102);
          Answer::NetPacket::writeInt32(packet, v104->nScore);
          Answer::MutexGuard::~MutexGuard(&lock_3);
        }
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI) )
      {
        Answer::NetPacket::writeInt8(packet, 39);
        v105 = Player::GetOperateLimit(player);
        v106 = CExtOperateLimit::GetLimitCount(v105, 1624);
        Answer::NetPacket::writeInt32(packet, v106);
        v107 = Player::GetOperateLimit(player);
        nRecord_3 = CExtOperateLimit::GetLimitCount(v107, 1625);
        Answer::NetPacket::writeInt8(packet, this->m_nFriendQingYiSize);
        for ( i_13 = 0; this->m_nFriendQingYiSize > i_13; ++i_13 )
          Answer::NetPacket::writeInt8(packet, (nRecord_3 >> i_13) & 1);
        ++nCount;
      }
      if ( CFestivalDoubleEleven::isOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
      {
        Answer::NetPacket::writeInt8(packet, 44);
        v108 = Player::GetTodayPayGold(player);
        Answer::NetPacket::writeInt32(packet, v108);
        v109 = Player::getRecord(player, 2095);
        Answer::NetPacket::writeInt32(packet, v109);
        v110 = Player::getRecord(player, 1628);
        Answer::NetPacket::writeInt32(packet, v110);
        v111 = Player::getRecord(player, 2096);
        Answer::NetPacket::writeInt32(packet, v111);
        ++nCount;
      }
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt8(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v114 = Player::getConnId(player);
      v115 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v115, v114, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CFestivalDoubleEleven::IsInTime(CFestivalDoubleEleven *const this)
{
  CfgData *v1; // rax
  CfgData *v2; // rax
  CfgData *v4; // rax
  int32_t nDiffDay; // [rsp+18h] [rbp-8h]
  int32_t nDiffDay_0; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    nDiffDay = CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_UNITE);
    if ( this->m_nUniteStartDay > 0 && this->m_nUniteStartDay > nDiffDay )
      return 0;
  }
  else
  {
    v4 = Answer::Singleton<CfgData>::instance();
    nDiffDay_0 = CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL);
    if ( this->m_nGameStartDay > 0 && this->m_nGameStartDay > nDiffDay_0 )
      return 0;
  }
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
bool __cdecl CFestivalDoubleEleven::needShowIcon(CFestivalDoubleEleven *const this)
{
  CfgData *v1; // rax
  CfgData *v2; // rax
  CfgData *v4; // rax
  int32_t nDiffDay; // [rsp+18h] [rbp-8h]
  int32_t nDiffDay_0; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    nDiffDay = CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_UNITE);
    if ( this->m_nUniteStartDay > 0 && this->m_nUniteStartDay > nDiffDay )
      return 0;
  }
  else
  {
    v4 = Answer::Singleton<CfgData>::instance();
    nDiffDay_0 = CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL);
    if ( this->m_nGameStartDay > 0 && this->m_nGameStartDay > nDiffDay_0 )
      return 0;
  }
  return this->m_nDay >= 0 && this->m_nDay < this->m_nIconHideDay;
}


#####################################
bool __cdecl CFestivalDoubleEleven::IsInTime(CFestivalDoubleEleven *const this, FESTIVAL_ACTIVITY_TYPE nType)
{
  return CFestivalDoubleEleven::IsOpen(this, nType)
      && this->m_nDay >= this->m_vStartDay[nType]
      && this->m_nDay < this->m_vEndDay[nType];
}


#####################################
bool __cdecl CFestivalDoubleEleven::IsOpen(CFestivalDoubleEleven *const this, FESTIVAL_ACTIVITY_TYPE nType)
{
  return CFestivalDoubleEleven::IsInTime(this) && CFestivalDoubleEleven::isOpen(this, nType);
}


#####################################
bool __cdecl CFestivalDoubleEleven::CheckDropGroup(CFestivalDoubleEleven *const this, int32_t nDropGroup)
{
  return CFestivalDoubleEleven::IsInTime(this) && this->m_nDropGroup == nDropGroup;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetLandGift(CFestivalDoubleEleven *const this, Player *player)
{
  std::vector<MemChrBag> *v4; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax
  int nIndex; // [rsp+1Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::canGetLandGift(this, player) )
    return 10002;
  nIndex = this->m_nDay;
  if ( this->m_nDay < 0 || (int)std::vector<std::vector<MemChrBag>>::size(&this->m_vLandGift) <= nIndex )
    return 10002;
  v4 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vLandGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v4, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_LAND_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(OperateLimit, 2030, 1);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetLandSumGift(CFestivalDoubleEleven *const this, Player *player, int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM) )
    return 10002;
  if ( nIndex < 0 || nIndex >= CFestivalDoubleEleven::getLandSum(this, player) )
    return 10002;
  if ( nIndex < 0 || nIndex >= (int)std::vector<std::vector<MemChrBag>>::size(&this->m_vLandSumGift) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1614);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vLandSumGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_LAND_SUM_GIFT) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1614, nNewRecord);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetDrawGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::canGetDrawGift(this, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &this->m_vDrawLoopReward, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_GRAW_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 1602, 1);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetOnlineGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::canGetOnlineGift(this, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &this->m_vOnlineReward, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_ONLINE_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 2037, 1);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GouWuChe(
        CFestivalDoubleEleven *const this,
        Player *player,
        Int32List *p_nIndexList)
{
  int32_t v3; // ebx
  int *v5; // rax
  int *v6; // rax
  int *v7; // rax
  int *v8; // rax
  MemChrBag *v9; // rax
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // eax
  CExtCharBag *v13; // rax
  std::_List_iterator<int> it; // [rsp+20h] [rbp-60h] BYREF
  MemChrBagVector items; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<int> __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t OldRecord; // [rsp+5Ch] [rbp-24h]
  int32_t nNewRecord; // [rsp+60h] [rbp-20h]
  int32_t PriceSum; // [rsp+64h] [rbp-1Ch]
  int32_t nSize; // [rsp+68h] [rbp-18h]
  int32_t Rate; // [rsp+6Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_GOU_WU_CHE) )
    return 10002;
  OldRecord = Player::getRecord(player, 2112);
  nNewRecord = 0;
  PriceSum = 0;
  std::vector<MemChrBag>::vector(&items);
  for ( it._M_node = std::list<int>::begin(p_nIndexList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
  {
    __x._M_node = std::list<int>::end(p_nIndexList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    if ( *std::_List_iterator<int>::operator*(&it) < 0
      && *std::_List_iterator<int>::operator*(&it) >= this->m_nGouWuCheSize )
    {
      v3 = 10002;
      goto LABEL_35;
    }
    v5 = std::_List_iterator<int>::operator*(&it);
    nNewRecord = OldRecord | (1 << *v5);
    if ( nNewRecord == OldRecord )
    {
      v3 = 10002;
      goto LABEL_35;
    }
    v6 = std::_List_iterator<int>::operator*(&it);
    v7 = std::vector<int>::operator[](&this->m_vGouWuCheGiftPrice, *v6);
    PriceSum += *v7;
    v8 = std::_List_iterator<int>::operator*(&it);
    v9 = std::vector<MemChrBag>::operator[](&this->m_vGouWuCheItem, *v8);
    std::vector<MemChrBag>::push_back(&items, v9);
    OldRecord = nNewRecord;
  }
  if ( PriceSum <= 0 || (int)std::vector<MemChrBag>::size(&items) <= 0 )
  {
    v3 = 10002;
  }
  else
  {
    nSize = std::list<int>::size(p_nIndexList);
    Bag = Player::GetBag(player);
    FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
    if ( FreeSlotCount >= nSize )
    {
      Rate = 0;
      switch ( nSize )
      {
        case 1:
          Rate = 9;
          break;
        case 2:
          Rate = 8;
          break;
        case 3:
          Rate = 7;
          break;
        case 4:
          Rate = 6;
          break;
        case 5:
          Rate = 5;
          break;
        default:
          break;
      }
      if ( Rate )
      {
        if ( !Player::DecCurrency(
                player,
                CURRENCY_TYPE::CURRENCY_GOLD,
                Rate * PriceSum / 10,
                CURRENCY_CHANGE_REASON::GCR_GOU_WU_CHE,
                0) )
        {
          v3 = 10002;
        }
        else
        {
          Player::updateRecord(player, 2112, nNewRecord);
          v13 = Player::GetBag(player);
          CExtCharBag::AddItemsAndMingGe(v13, &items, ITEM_CHANGE_REASON::IDCR_GOU_WU_CHE);
          v3 = 0;
        }
      }
      else
      {
        v3 = 10002;
      }
    }
    else
    {
      v3 = 10002;
    }
  }
LABEL_35:
  std::vector<MemChrBag>::~vector(&items);
  return v3;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetWishGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::canGetWishGift(this, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &this->m_vWishReward, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_WISH_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 2038, 1);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::BuyDailyLimitShopItem(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v5; // rax

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 2034) >= this->m_nDailyLimitShopLimit )
    return 10002;
  if ( Player::GetCurrency(player, (const CURRENCY_TYPE)this->m_nDailyLimitShopCostType) < this->m_nDailyLimitShopCostValue )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &this->m_vDailyLimitShopItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_LIMIT) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          (const CURRENCY_TYPE)this->m_nDailyLimitShopCostType,
          this->m_nDailyLimitShopCostValue,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_LIMIT_SHOP,
          0) )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(v5, 2034, 1);
  return 0;
}


#####################################
bool __cdecl CFestivalDoubleEleven::BuyTitle(CFestivalDoubleEleven *const this, Player *player)
{
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v6; // rax

  if ( !player )
    return 0;
  if ( Player::getRecord(player, 1631) > 0 )
    return 0;
  if ( this->m_Price <= 0 || !std::vector<MemChrBag>::size(&this->m_Items) )
    return 0;
  Bag = Player::GetBag(player);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
  if ( FreeSlotCount < (int)std::vector<MemChrBag>::size(&this->m_Items) )
    return 0;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          this->m_Price,
          CURRENCY_CHANGE_REASON::GCR_BUY_TITLE,
          0) )
    return 0;
  v6 = Player::GetBag(player);
  CExtCharBag::AddItem(v6, &this->m_Items, ITEM_CHANGE_REASON::IDCR_BUY_TITLE);
  Player::updateRecord(player, 1631, 1);
  return 1;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::BuyGiftShopItem(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  std::vector<ShopGoods> *v5; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  int32_t nDayIndex; // [rsp+2Ch] [rbp-24h]
  int32_t nOldRecord; // [rsp+30h] [rbp-20h]
  int nNewRecord; // [rsp+34h] [rbp-1Ch]
  ShopGoods *goods; // [rsp+38h] [rbp-18h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_GIFT_SHOP) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nGiftShopSize )
    return 10002;
  nDayIndex = this->m_nDay - this->m_vStartDay[17];
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1607);
  nNewRecord = nOldRecord | (1 << (nDayIndex * LOBYTE(this->m_nGiftShopSize) + nIndex));
  if ( nOldRecord == nNewRecord )
    return 10002;
  v5 = std::vector<std::vector<ShopGoods>>::operator[](&this->m_vGiftShopGoods, nDayIndex);
  goods = std::vector<ShopGoods>::operator[](v5, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM,
          0) )
    return 10002;
  v7 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v7, 1607, nNewRecord);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::BuyGiftShopItem2(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v6; // rax
  CharId_t Cid; // r13
  int32_t v8; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-40h] BYREF
  int32_t nOldRecord; // [rsp+30h] [rbp-30h]
  int32_t nNewRecord; // [rsp+34h] [rbp-2Ch]
  const ShopGoods *goods; // [rsp+38h] [rbp-28h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP_2) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nDailyLimitShop2Size )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2035);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  goods = std::vector<ShopGoods>::operator[](&this->m_vDailyLimitShop2Goods, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM_2) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM_2,
          0) )
    return 10002;
  v6 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v6, 2035, nNewRecord);
  if ( *std::vector<int>::operator[](&this->m_vDailyLimitShop2Broadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v8 = *std::vector<int>::operator[](&this->m_vDailyLimitShop2Broadcast, nIndex);
    ConnId = Player::getConnId(player);
    CFestivalDoubleEleven::broadcastPlayerAction(this, ConnId, v8, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::BuyGiftItem(CFestivalDoubleEleven *const this, Player *player, int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int64_t Currency; // rbx
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  int64_t v8; // rdx
  CharId_t Cid; // r13
  int32_t v10; // r12d
  int8_t ConnId; // bl
  CExtOperateLimit *v12; // rax
  std::string strCharName; // [rsp+20h] [rbp-30h] BYREF
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int32_t nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nBuyGiftSize )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1619);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
  if ( Currency < *std::vector<int>::operator[](&this->m_vBuyGiftPrice, nIndex) )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vBuyGiftItem, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_GIFT_ITEM) )
    return 10002;
  v8 = *std::vector<int>::operator[](&this->m_vBuyGiftPrice, nIndex);
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          v8,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_GIFT_ITEM,
          0) )
    return 10002;
  if ( *std::vector<int>::operator[](&this->m_vBuyGiftBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v10 = *std::vector<int>::operator[](&this->m_vBuyGiftBroadcast, nIndex);
    ConnId = Player::getConnId(player);
    CFestivalDoubleEleven::broadcastPlayerAction(this, ConnId, v10, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  v12 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v12, 1619, nNewRecord);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetRechargeBack(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  int nRechargeBack; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRechargeBack = CExtOperateLimit::GetLimitCount(OperateLimit, 1620);
  if ( nRechargeBack <= 0 )
    return 10002;
  if ( !Player::AddCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          nRechargeBack,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_RECHARGE_BACK,
          0) )
    return 10002;
  v4 = Player::GetOperateLimit(player);
  CExtOperateLimit::Reset(v4, 1620);
  v5 = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(v5, 1621, nRechargeBack);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetEquipUpStarBackItem(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v5; // rax
  CExtOperateLimit *v6; // rax
  MemChrBag item; // [rsp+10h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+3Ch] [rbp-4h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1617);
  if ( nCount <= 0 )
    return 10002;
  memset(&item, 0, sizeof(item));
  item.itemId = this->m_nEquipUpStarBackId;
  item.itemClass = 1;
  item.itemCount = nCount;
  item.bind = 1;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_EQUIP_UPSTAR_BACK) )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  CExtOperateLimit::Reset(v5, 1617);
  v6 = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(v6, 1618, nCount);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetHuoYueDuSumGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // ebx
  CExtOperateLimit *v6; // rax
  int32_t v7; // eax
  std::vector<MemChrBag> *v8; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v10; // rax
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM) )
    return 10002;
  if ( nIndex < 0 || this->m_nHuoYueDuSumSize <= nIndex )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1603);
  if ( LimitCount < *std::vector<int>::operator[](&this->m_vHuoYueDuSumLimit, nIndex) )
    return 10002;
  v6 = Player::GetOperateLimit(player);
  v7 = CExtOperateLimit::GetLimitCount(v6, 1604);
  nNewSign = v7 | (1 << nIndex);
  if ( nNewSign == v7 )
    return 10002;
  v8 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vHuoYueDuSumReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v8, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_HUO_YUE_DU) )
    return 10002;
  v10 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v10, 1604, nNewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetDailyRechargeGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  int32_t TodayPayGold; // ebx
  CExtOperateLimit *OperateLimit; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  CharId_t Cid; // r13
  int32_t v10; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-30h] BYREF
  int32_t nRewardSign; // [rsp+28h] [rbp-28h]
  int32_t nNewSign; // [rsp+2Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE_2) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nDailyRechargeSize )
    return 10002;
  TodayPayGold = Player::GetTodayPayGold(player);
  if ( TodayPayGold < *std::vector<int>::operator[](&this->m_vDailyRechargeLimit, nIndex) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRewardSign = CExtOperateLimit::GetLimitCount(OperateLimit, 2033);
  nNewSign = nRewardSign | (1 << nIndex);
  if ( nNewSign == nRewardSign )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vDailyRechargeReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_DAILY_RECHARGE_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 2033, nNewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  if ( *std::vector<int>::operator[](&this->m_vDailyRechargeBroad, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v10 = *std::vector<int>::operator[](&this->m_vDailyRechargeBroad, nIndex);
    ConnId = Player::getConnId(player);
    CFestivalDoubleEleven::broadcastPlayerAction(this, ConnId, v10, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetRechargeSumGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  CharId_t Cid; // r13
  int32_t v10; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-40h] BYREF
  int32_t nRechargeSum; // [rsp+34h] [rbp-2Ch]
  int32_t nRewardSign; // [rsp+38h] [rbp-28h]
  int32_t nNewSign; // [rsp+3Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_GIFT) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nRechargeSumSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRechargeSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
  if ( *std::vector<int>::operator[](&this->m_vRechargeSumLimit, nIndex) > nRechargeSum )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  nRewardSign = CExtOperateLimit::GetLimitCount(v5, 1616);
  nNewSign = nRewardSign | (1 << nIndex);
  if ( nNewSign == nRewardSign )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeSumReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_RECHARGE_SUM_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 1616, nNewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  if ( *std::vector<int>::operator[](&this->m_vRechargeSumBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v10 = *std::vector<int>::operator[](&this->m_vRechargeSumBroadcast, nIndex);
    ConnId = Player::getConnId(player);
    CFestivalDoubleEleven::broadcastPlayerAction(this, ConnId, v10, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetPetIllusionItemGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t LimitCount; // eax
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int nIllusionSum; // [rsp+24h] [rbp-1Ch]
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nPetIllusionItemSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nIllusionSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1622);
  if ( *std::vector<int>::operator[](&this->m_vPetIllusionItemLimit, nIndex) > nIllusionSum )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(v5, 1623);
  nNewSign = LimitCount | (1 << nIndex);
  if ( nNewSign == LimitCount )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vPetIllusionItemReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_PET_ILLUSION_REWARD) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1623, nNewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetXiaoFeiSumGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t nId)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CharId_t Cid; // r13
  int32_t v9; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-40h] BYREF
  int32_t nRechargeSum; // [rsp+34h] [rbp-2Ch]
  int32_t nRewardSign; // [rsp+38h] [rbp-28h]
  int32_t NewSign; // [rsp+3Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT) )
    return 10002;
  if ( nId < 0 || this->m_nXiaoFeiSumSize <= nId )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRechargeSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
  if ( *std::vector<int>::operator[](&this->m_vXiaoFeiSumLimit, nId) > nRechargeSum )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  nRewardSign = CExtOperateLimit::GetLimitCount(v5, 1606);
  NewSign = nRewardSign | (1 << nId);
  if ( nRewardSign == NewSign )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vXiaoFeiSumReward, nId);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_XIAO_FAI_SUM_GIFT) )
    return 10002;
  Player::updateRecord(player, 1606, NewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  if ( *std::vector<int>::operator[](&this->m_vXiaoFeiSumBroadcast, nId) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v9 = *std::vector<int>::operator[](&this->m_vXiaoFeiSumBroadcast, nId);
    ConnId = Player::getConnId(player);
    CFestivalDoubleEleven::broadcastPlayerAction(this, ConnId, v9, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}


#####################################
void __cdecl CFestivalDoubleEleven::GetLianRechargeReward(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t nType,
        int32_t nIndex)
{
  int32_t Record; // eax
  LianRechargeCfg *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  int32_t RewardRecord; // [rsp+2Ch] [rbp-24h]
  int32_t LianChongRecord; // [rsp+30h] [rbp-20h]
  int NewRecord; // [rsp+3Ch] [rbp-14h]

  if ( player && CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_LIAN_CHONG) )
  {
    if ( nType )
    {
      if ( nType != 1 )
        return;
      RewardRecord = 1637;
      LianChongRecord = 1635;
    }
    else
    {
      RewardRecord = 1636;
      LianChongRecord = 1634;
    }
    if ( nIndex + 1 <= Player::getRecord(player, LianChongRecord) )
    {
      Record = Player::getRecord(player, RewardRecord);
      NewRecord = Record | (1 << nIndex);
      if ( NewRecord != Record )
      {
        v5 = std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, nType);
        v6 = std::vector<std::vector<MemChrBag>>::operator[](&v5->vGiftVector, nIndex);
        Bag = Player::GetBag(player);
        if ( CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::IDCR_DOUBLE_ELEVEN_LIAN_CHONG) )
        {
          Player::updateRecord(player, RewardRecord, NewRecord);
          CFestivalDoubleEleven::GongGao(this, 3012, player);
          CFestivalDoubleEleven::SendIconState(this, player);
        }
      }
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::GongGao(CFestivalDoubleEleven *const this, int32_t GongGaoId, Player *player)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::UpdateRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int8_t nType,
        int16_t nDay,
        int16_t nIndex,
        const FestivalRank *const info)
{
  switch ( nType )
  {
    case 4:
      CFestivalDoubleEleven::updateDrawRank(this, connid, nIndex, info);
      break;
    case 12:
      CFestivalDoubleEleven::updateXiaoFeiRank(this, connid, nDay, nIndex, info);
      break;
    case 16:
      CFestivalDoubleEleven::updateXiaoFeiSumRank(this, connid, nIndex, info);
      break;
    case 32:
      CFestivalDoubleEleven::updateRechargeSumRank(this, connid, nIndex, info);
      break;
    case 33:
      CFestivalDoubleEleven::updateCrossRechargeSumRank(this, connid, nIndex, info);
      break;
    case 34:
      CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(this, connid, nIndex, info);
      break;
    case 37:
      CFestivalDoubleEleven::updateCrossChouJiangRank(this, connid, nIndex, info);
      break;
    case 43:
      CFestivalDoubleEleven::updateBossScoreRank(this, connid, nIndex, info);
      break;
    default:
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CFestivalDoubleEleven::UpdateRank() wrong type = %d",
        nType);
      break;
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddDrawTimes(CFestivalDoubleEleven *const this, Player *player, int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  size_t v6; // rbx
  std::vector<FestivalRank> *v7; // rax
  FestivalRank *v8; // rax
  int v9; // ebx
  size_t v10; // rbx
  std::vector<FestivalRank> *v11; // rax
  FestivalRank *v12; // rax
  int v13; // ebx
  size_t v14; // rbx
  std::vector<FestivalRank> *v15; // rax
  FestivalRank *v16; // rbx
  size_t v17; // r12
  std::vector<FestivalRank> *v18; // rax
  FestivalRank *v19; // rax
  size_t v20; // rbx
  std::vector<FestivalRank> *v21; // rax
  size_t v22; // rbx
  std::vector<FestivalRank> *v23; // rax
  FestivalRank *v24; // rax
  size_t v25; // rbx
  std::vector<FestivalRank> *v26; // rax
  FestivalRank *v27; // rax
  size_t v28; // rbx
  std::vector<FestivalRank> *v29; // rax
  FestivalRank *v30; // rax
  size_t v31; // rbx
  std::vector<FestivalRank> *v32; // rax
  FestivalRank *v33; // rbx
  size_t v34; // rbx
  std::vector<FestivalRank> *v35; // rax
  Answer::MutexGuard lock_2; // [rsp+20h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+40h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-50h] BYREF
  std::string strName; // [rsp+60h] [rbp-40h] BYREF
  int8_t connid; // [rsp+73h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+74h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+78h] [rbp-28h]
  int32_t nRankIndex; // [rsp+84h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+88h] [rbp-18h]
  int16_t i; // [rsp+8Ah] [rbp-16h]
  int16_t i_0; // [rsp+8Ch] [rbp-14h]
  int16_t i_1; // [rsp+8Eh] [rbp-12h]

  if ( player )
  {
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW)
      || CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1601, nCount);
      v5 = Player::GetOperateLimit(player);
      nScore = CExtOperateLimit::GetLimitCount(v5, 1601);
      CFestivalDoubleEleven::SendIconState(this, player);
      if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_CHOU_JIANG_RANK) )
        CFestivalDoubleEleven::updateCrossChouJiangRank(this, player);
      if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK)
        && this->m_nDrawRankLimit <= nScore )
      {
        connid = Player::getConnId(player);
        nCharId = Player::getCid(player);
        Player::getName((const Player *const)&strName);
        CFestivalDoubleEleven::checkDrawRankInvalid(this, connid);
        nRankIndex = -1;
        for ( i = 0; i < this->m_nDrawRankSize; ++i )
        {
          Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
          v6 = i;
          v7 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v8 = std::vector<FestivalRank>::operator[](v7, v6);
          if ( v8->nScore >= nScore )
          {
            v9 = 1;
          }
          else
          {
            nRankIndex = i;
            v9 = 0;
          }
          Answer::MutexGuard::~MutexGuard(&lock_0);
          if ( !v9 )
            break;
        }
        if ( nRankIndex >= 0 )
        {
          nOldIndex = this->m_nDrawRankSize - 1;
          for ( i_0 = 0; i_0 < this->m_nDrawRankSize; ++i_0 )
          {
            Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
            v10 = i_0;
            v11 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
            v12 = std::vector<FestivalRank>::operator[](v11, v10);
            if ( v12->nCharId == nCharId )
            {
              nOldIndex = i_0;
              v13 = 0;
            }
            else
            {
              v13 = 1;
            }
            Answer::MutexGuard::~MutexGuard(&lock_1);
            if ( !v13 )
              break;
          }
          if ( nOldIndex != nRankIndex )
          {
            for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
            {
              Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
              v14 = i_1 - 1;
              v15 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
              v16 = std::vector<FestivalRank>::operator[](v15, v14);
              v17 = i_1;
              v18 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
              v19 = std::vector<FestivalRank>::operator[](v18, v17);
              FestivalRank::operator=(v19, v16);
              v20 = i_1;
              v21 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
              std::vector<FestivalRank>::operator[](v21, v20)->bChange = 1;
              Answer::MutexGuard::~MutexGuard(&lock_2);
            }
          }
          Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
          v22 = nRankIndex;
          v23 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v24 = std::vector<FestivalRank>::operator[](v23, v22);
          v24->nCharId = nCharId;
          v25 = nRankIndex;
          v26 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v27 = std::vector<FestivalRank>::operator[](v26, v25);
          std::string::operator=(&v27->strName, &strName);
          v28 = nRankIndex;
          v29 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v30 = std::vector<FestivalRank>::operator[](v29, v28);
          v30->nScore = nScore;
          v31 = nRankIndex;
          v32 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          v33 = std::vector<FestivalRank>::operator[](v32, v31);
          v33->nTime = Unit::getNow(player);
          v34 = nRankIndex;
          v35 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mDrawRank, &connid);
          std::vector<FestivalRank>::operator[](v35, v34)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock);
        }
        std::string::~string(&strName);
      }
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddHuoYueDu(CFestivalDoubleEleven *const this, Player *player, int32_t nValue)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( player )
  {
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1603, nValue);
      CFestivalDoubleEleven::SendIconState(this, player);
    }
  }
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::getLeftTime(CFestivalDoubleEleven *const this)
{
  CTimer *v2; // rax
  int nNowTime; // [rsp+18h] [rbp-8h]

  if ( !CFestivalDoubleEleven::IsInTime(this) )
    return 0;
  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  return 86400 * (this->m_nEndDay - this->m_nDay) - (nNowTime - Answer::DayTime::dayzero(nNowTime));
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetLandGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_LAND) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 2030) <= 0;
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetLandSumGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t nLandDays; // [rsp+14h] [rbp-1Ch]
  int nRecord; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM) )
    return 0;
  nLandDays = CFestivalDoubleEleven::getLandSum(this, player);
  OperateLimit = Player::GetOperateLimit(player);
  nRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1614);
  for ( i = 0; i < nLandDays; ++i )
  {
    if ( ((nRecord >> i) & 1) == 0 )
      return 1;
  }
  return 0;
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetDrawGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nDrawTimes; // [rsp+28h] [rbp-8h]

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nDrawTimes = CExtOperateLimit::GetLimitCount(OperateLimit, 1601);
  v4 = Player::GetOperateLimit(player);
  return nDrawTimes / this->m_nDrawLoopTimes > CExtOperateLimit::GetLimitCount(v4, 1602);
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetOnlineGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nOnlineTime; // [rsp+28h] [rbp-8h]
  int32_t nRewardTimes; // [rsp+2Ch] [rbp-4h]

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2036);
  v4 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v4, 2037);
  return this->m_nMaxCount > nRewardTimes && nOnlineTime / this->m_nOnlineTimeArea > nRewardTimes;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetOnlineTimeRewardTime(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nOnlineTime; // [rsp+28h] [rbp-8h]
  int nRewardTimes; // [rsp+2Ch] [rbp-4h]

  if ( !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2036);
  v4 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v4, 2037);
  if ( nOnlineTime / this->m_nOnlineTimeArea > nRewardTimes )
    return 0;
  else
    return (nRewardTimes + 1) * this->m_nOnlineTimeArea - nOnlineTime;
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetWishGift(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nRecharge; // [rsp+18h] [rbp-8h]
  int32_t nReward; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BEST_WISH) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nRecharge = CExtOperateLimit::GetLimitCount(OperateLimit, 2026);
  v4 = Player::GetOperateLimit(player);
  nReward = CExtOperateLimit::GetLimitCount(v4, 2038);
  return this->m_nWishRecharge <= nRecharge && !nReward;
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetFaBaoBack(CFestivalDoubleEleven *const this, Player *player)
{
  int32_t Record; // ebx
  int32_t OldRecord; // [rsp+14h] [rbp-1Ch]
  int32_t i; // [rsp+18h] [rbp-18h]

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
    return 0;
  OldRecord = Player::getRecord(player, 1629);
  for ( i = 0; this->m_nSize > i; ++i )
  {
    if ( OldRecord != (OldRecord | (1 << i)) )
    {
      Record = Player::getRecord(player, 1630);
      if ( Record >= *std::vector<int>::operator[](&this->m_NeedValue, i) )
        return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetEquipUpStarBack(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 1617) > 0;
}


#####################################
bool __cdecl CFestivalDoubleEleven::canGetRechargeBack(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 0;
  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 1620) > 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::getLandSum(CFestivalDoubleEleven *const this, Player *player)
{
  int32_t m_nDay; // eax
  int32_t v4; // eax
  CExtOperateLimit *OperateLimit; // rax
  int32_t nEndDay; // [rsp+18h] [rbp-28h]
  int32_t nStart; // [rsp+1Ch] [rbp-24h]
  int32_t nEnd; // [rsp+20h] [rbp-20h]
  int nLandRecord; // [rsp+24h] [rbp-1Ch]
  int32_t nCount; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 0;
  if ( this->m_nDay >= this->m_vEndDay[9] )
    m_nDay = this->m_vEndDay[9];
  else
    m_nDay = this->m_nDay;
  nEndDay = m_nDay;
  if ( this->m_nDay <= m_nDay )
    v4 = 0;
  else
    v4 = this->m_nDay - m_nDay;
  nStart = v4;
  nEnd = nEndDay + v4 - this->m_vStartDay[9];
  OperateLimit = Player::GetOperateLimit(player);
  nLandRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1069);
  nCount = 0;
  for ( i = nStart; i <= nEnd; ++i )
  {
    if ( ((nLandRecord >> i) & 1) != 0 )
      ++nCount;
  }
  return nCount;
}


#####################################
void __cdecl CFestivalDoubleEleven::GetWorldBossIconState(
        CFestivalDoubleEleven *const this,
        IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CFestivalDoubleEleven::IsInWorldBossTime(this) )
  {
    CFestivalDoubleEleven::getWorldBossIconState(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::SendWorldBossIconState(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // eax
  GameService *v4; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      CFestivalDoubleEleven::getWorldBossIconState(&stu, this);
      Answer::NetPacket::writeInt32(packet, stu.nId);
      Answer::NetPacket::writeInt8(packet, stu.nState);
      Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
      Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
      Answer::NetPacket::writeInt32(packet, stu.nIconRight);
      Answer::NetPacket::writeInt8(packet, stu.nEffects);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkWorldBoss(CFestivalDoubleEleven *const this)
{
  GameService *v2; // rax
  int32_t m_nMinute; // ebx
  int32_t m_Mid; // ebx
  CfgData *v5; // rax
  CfgData *v6; // rax
  CPoolManager *v7; // rax
  int32_t v8; // ebx
  int32_t nEndTime; // r12d
  TimeArea *v10; // rax
  int32_t m_MapId; // ebx
  MapManager *v12; // rax
  int32_t v13; // ebx
  size_t v14; // rbx
  CfgMapMonster MapMonster; // [rsp+10h] [rbp-70h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+30h] [rbp-50h] BYREF
  uint32_t i; // [rsp+4Ch] [rbp-34h]
  CfgMonster *pMonster; // [rsp+50h] [rbp-30h]
  int32_t MonsterId; // [rsp+5Ch] [rbp-24h]
  Monster *monster; // [rsp+60h] [rbp-20h]
  Map *pMap; // [rsp+68h] [rbp-18h]

  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_WORLD_BOSS)
    && !std::vector<TimeArea>::empty(&this->m_vWorldBossMinute) )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) == 1 )
    {
      for ( i = 0; ; ++i )
      {
        v14 = i;
        if ( v14 >= std::vector<TimeArea>::size(&this->m_vWorldBossMinute) )
          break;
        m_nMinute = this->m_nMinute;
        if ( m_nMinute == std::vector<TimeArea>::operator[](&this->m_vWorldBossMinute, i)->nStartTime )
        {
          m_Mid = this->m_Mid;
          v5 = Answer::Singleton<CfgData>::instance();
          pMonster = CfgData::getMonster(v5, m_Mid);
          if ( !pMonster || pMonster->boss_sign != 11 )
            return;
          v6 = Answer::Singleton<CfgData>::instance();
          MonsterId = CfgData::GetMapMonsterId(v6);
          memset(&MapMonster.mapid, 0, 24);
          MapMonster.id = MonsterId;
          MapMonster.mapid = this->m_MapId;
          MapMonster.x = this->m_X;
          MapMonster.y = this->m_Y;
          this->m_MonsterId = MonsterId;
          v7 = Answer::Singleton<CPoolManager>::instance();
          monster = CPoolManager::pop<Monster>(v7);
          if ( monster && pMonster )
          {
            std::vector<AttrAddon>::vector(&vAttrAddon);
            Monster::init(monster, pMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
            std::vector<AttrAddon>::~vector(&vAttrAddon);
            v8 = Answer::DayTime::now();
            nEndTime = std::vector<TimeArea>::operator[](&this->m_vWorldBossMinute, i)->nEndTime;
            v10 = std::vector<TimeArea>::operator[](&this->m_vWorldBossMinute, i);
            Monster::SetLifeTime(monster, v8 + 60 * (nEndTime - v10->nStartTime));
            m_MapId = this->m_MapId;
            v12 = Answer::Singleton<MapManager>::instance();
            pMap = MapManager::GetMap(v12, m_MapId);
            if ( pMap )
            {
              (*((void (__fastcall **)(Map *, Monster *, _QWORD, _QWORD))pMap->_vptr_Map + 28))(
                pMap,
                monster,
                (unsigned int)MapMonster.x,
                (unsigned int)MapMonster.y);
              this->m_bDie = 0;
            }
          }
          CFestivalDoubleEleven::broadcastWorldBossStart(this);
          CFestivalDoubleEleven::SendWorldBossIconState(this);
        }
        else
        {
          v13 = this->m_nMinute;
          if ( v13 == std::vector<TimeArea>::operator[](&this->m_vWorldBossMinute, i)->nEndTime )
          {
            this->m_bDie = 1;
            CFestivalDoubleEleven::broadcastWorldBossEnd(this);
            CFestivalDoubleEleven::SendWorldBossIconState(this);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::BossDie(
        CFestivalDoubleEleven *const this,
        int32_t MonsterId,
        std::string *p_name,
        CharId_t Cid)
{
  if ( this->m_MonsterId > 0 && this->m_MonsterId == MonsterId )
  {
    this->m_bDie = 1;
    CFestivalDoubleEleven::BroadcastWorldBossKilled(this, p_name, Cid);
    CFestivalDoubleEleven::SendWorldBossIconState(this);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::BroadcastWorldBossKilled(
        CFestivalDoubleEleven *const this,
        const std::string *const name,
        CharId_t cid)
{
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_nWorldBossKillBroadcast);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, 0, packet);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::broadcastWorldBossStart(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nWorldBossStartBroadcast);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::broadcastWorldBossEnd(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nWorldBossEndBroadcast);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddOnlineRecord(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  int32_t nOnlineTime; // [rsp+20h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+24h] [rbp-Ch]

  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME)
    && player
    && this->m_nMinute >= this->m_nOnlineStartMinute
    && this->m_nMinute < this->m_nOnlineEndMinute )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2036);
    v4 = Player::GetOperateLimit(player);
    nRewardTimes = CExtOperateLimit::GetLimitCount(v4, 2037);
    if ( this->m_nMaxCount > nRewardTimes )
    {
      v5 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v5, 2036, 1);
      if ( nOnlineTime / this->m_nOnlineTimeArea - nRewardTimes != (nOnlineTime + 1) / this->m_nOnlineTimeArea
                                                                 - nRewardTimes )
        CFestivalDoubleEleven::SendIconState(this, player);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::UpdateXiaoFeiRank(CFestivalDoubleEleven *const this, Player *player)
{
  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
    CFestivalDoubleEleven::updateXiaoFeiRank(this, player);
  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK) )
    CFestivalDoubleEleven::updateXiaoFeiSumRank(this, player);
  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK) )
    CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(this, player);
}


#####################################
void __cdecl CFestivalDoubleEleven::AddXiaoFeiRecord(CFestivalDoubleEleven *const this, Player *player, int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nOldCount; // [rsp+24h] [rbp-Ch]

  if ( player && CFestivalDoubleEleven::IsInTime(this) )
  {
    nOldCount = CFestivalDoubleEleven::GetXiaoFeiSumGiftCount(this, player);
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
    v4 = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(v4, 1605, nCount);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW)
      && CFestivalDoubleEleven::CanUseXiaoFeiDraw(this, player) )
    {
      CFestivalDoubleEleven::SendIconState(this, player);
    }
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT)
      && CFestivalDoubleEleven::GetXiaoFeiSumGiftCount(this, player) != nOldCount )
    {
      CFestivalDoubleEleven::SendIconState(this, player);
    }
  }
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetXiaoFeiSumGiftCount(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t LimitCount; // eax
  int32_t Count; // [rsp+1Ch] [rbp-24h]
  int nRewardSum; // [rsp+20h] [rbp-20h]
  int32_t i; // [rsp+24h] [rbp-1Ch]

  Count = 0;
  if ( !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nRewardSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
  for ( i = 0; this->m_nXiaoFeiSumSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&this->m_vXiaoFeiSumLimit, i) <= nRewardSum )
    {
      v4 = Player::GetOperateLimit(player);
      LimitCount = CExtOperateLimit::GetLimitCount(v4, 1606);
      if ( (LimitCount | (1 << i)) != LimitCount )
        ++Count;
    }
  }
  return Count;
}


#####################################
void __cdecl CFestivalDoubleEleven::AddRechargeRecord(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nAddValue; // [rsp+2Ch] [rbp-4h]

  if ( player && CFestivalDoubleEleven::IsInTime(this) )
  {
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1615, nCount);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK) )
      CFestivalDoubleEleven::updateRechargeSumRank(this, player);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK) )
      CFestivalDoubleEleven::updateCrossRechargeSumRank(this, player);
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
    {
      nAddValue = CFestivalDoubleEleven::calRechargeBack(this, nCount);
      v4 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v4, 1620, nAddValue);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddPetIllusionItemRecord(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( player )
  {
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1622, nCount);
      CFestivalDoubleEleven::SendIconState(this, player);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddFriendQingYi(CFestivalDoubleEleven *const this, Player *player, int32_t nValue)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( player )
  {
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1624, nValue);
      CFestivalDoubleEleven::SendIconState(this, player);
    }
  }
}


#####################################
bool __cdecl CFestivalDoubleEleven::CanUseXiaoFeiDraw(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int nXiaoFeiSum; // [rsp+10h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+14h] [rbp-Ch]
  int32_t nCanGetTime; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW) || !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nXiaoFeiSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 1606);
  nCanGetTime = 0;
  for ( i = 0; this->m_nXiaoFeiDrawSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&this->m_nXiaoFeiDrawValue, i) <= nXiaoFeiSum )
      nCanGetTime = i + 1;
  }
  return nCanGetTime - nRewardTimes > 0;
}


#####################################
bool __cdecl CFestivalDoubleEleven::CanUseRechargeDraw(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int nChongZhi; // [rsp+10h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+14h] [rbp-Ch]
  int32_t nCanGetTime; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !CFestivalDoubleEleven::IsOpen(this, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_DRAW) || !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nChongZhi = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 1632);
  nCanGetTime = 0;
  for ( i = 0; this->m_RechargeDrawSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&this->m_nRechargeDrawValue, i) <= nChongZhi )
      nCanGetTime = i + 1;
  }
  return nCanGetTime - nRewardTimes > 0;
}


#####################################
void __cdecl CFestivalDoubleEleven::loadXiaoFeiRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  size_t m_nXiaoFeiRankSize; // rbx
  std::vector<FestivalRank> *v3; // rax
  Answer::MySqlQuery *v4; // rax
  size_t v5; // rbx
  std::vector<FestivalRank> *v6; // rax
  FestivalRank *v7; // rbx
  const char *StringValue; // rbx
  size_t v9; // r12
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  size_t v12; // rbx
  std::vector<FestivalRank> *v13; // rax
  FestivalRank *v14; // rbx
  size_t v15; // rbx
  std::vector<FestivalRank> *v16; // rax
  FestivalRank *v17; // rbx
  std::vector<std::vector<FestivalRank>> *v19; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-10E0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-E0h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-B0h] BYREF
  FestivalRankVtVt vRank; // [rsp+1060h] [rbp-90h] BYREF
  std::vector<FestivalRank> p___x; // [rsp+1080h] [rbp-70h] BYREF
  FestivalRank v25; // [rsp+10A0h] [rbp-50h] BYREF
  char __k; // [rsp+10D7h] [rbp-19h] BYREF
  int32_t i; // [rsp+10D8h] [rbp-18h]
  int32_t nIndex; // [rsp+10DCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  memset(szSQL, 0, sizeof(szSQL));
  std::vector<std::vector<FestivalRank>>::vector(&vRank);
  std::vector<FestivalRank>::vector(&p___x);
  std::vector<std::vector<FestivalRank>>::resize(&vRank, this->m_nEndDay, &p___x);
  std::vector<FestivalRank>::~vector(&p___x);
  for ( i = 0; this->m_nEndDay > i; ++i )
  {
    FestivalRank::FestivalRank(&v25);
    m_nXiaoFeiRankSize = this->m_nXiaoFeiRankSize;
    v3 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
    std::vector<FestivalRank>::resize(v3, m_nXiaoFeiRankSize, &v25);
    FestivalRank::~FestivalRank(&v25);
    bzero(szSQL, 0x1000u);
    snprintf(
      szSQL,
      0xFFFu,
      "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=12 AND `day`=%d ORDER BY `count` DESC,`time`",
      i);
    v4 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v4);
    nIndex = 0;
    while ( !Answer::MySqlQuery::eof(&result) && this->m_nXiaoFeiRankSize > nIndex )
    {
      v5 = nIndex;
      v6 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v7 = std::vector<FestivalRank>::operator[](v6, v5);
      v7->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
      v9 = nIndex;
      v10 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v11 = std::vector<FestivalRank>::operator[](v10, v9);
      std::string::operator=(&v11->strName, StringValue);
      v12 = nIndex;
      v13 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v14 = std::vector<FestivalRank>::operator[](v13, v12);
      v14->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
      v15 = nIndex;
      v16 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v17 = std::vector<FestivalRank>::operator[](v16, v15);
      v17->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
      ++nIndex;
      Answer::MySqlQuery::nextRow(&result);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
  }
  __k = 0;
  v19 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &__k);
  std::vector<std::vector<FestivalRank>>::operator=(v19, &vRank);
  std::vector<std::vector<FestivalRank>>::~vector(&vRank);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateXiaoFeiRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  size_t m_nDay; // r12
  std::vector<std::vector<FestivalRank>> *v6; // rax
  std::vector<FestivalRank> *v7; // rax
  FestivalRank *v8; // rax
  int v9; // ebx
  size_t v10; // rbx
  size_t v11; // r12
  std::vector<std::vector<FestivalRank>> *v12; // rax
  std::vector<FestivalRank> *v13; // rax
  FestivalRank *v14; // rax
  int v15; // ebx
  size_t v16; // rbx
  size_t v17; // r12
  std::vector<std::vector<FestivalRank>> *v18; // rax
  std::vector<FestivalRank> *v19; // rax
  FestivalRank *v20; // rbx
  size_t v21; // r12
  size_t v22; // r13
  std::vector<std::vector<FestivalRank>> *v23; // rax
  std::vector<FestivalRank> *v24; // rax
  FestivalRank *v25; // rax
  size_t v26; // rbx
  size_t v27; // r12
  std::vector<std::vector<FestivalRank>> *v28; // rax
  std::vector<FestivalRank> *v29; // rax
  size_t v30; // rbx
  size_t v31; // r12
  std::vector<std::vector<FestivalRank>> *v32; // rax
  std::vector<FestivalRank> *v33; // rax
  FestivalRank *v34; // rax
  size_t v35; // rbx
  size_t v36; // r12
  std::vector<std::vector<FestivalRank>> *v37; // rax
  std::vector<FestivalRank> *v38; // rax
  FestivalRank *v39; // rax
  size_t v40; // rbx
  size_t v41; // r12
  std::vector<std::vector<FestivalRank>> *v42; // rax
  std::vector<FestivalRank> *v43; // rax
  FestivalRank *v44; // rax
  size_t v45; // rbx
  size_t v46; // r12
  std::vector<std::vector<FestivalRank>> *v47; // rax
  std::vector<FestivalRank> *v48; // rax
  FestivalRank *v49; // rbx
  size_t v50; // rbx
  size_t v51; // r12
  std::vector<std::vector<FestivalRank>> *v52; // rax
  std::vector<FestivalRank> *v53; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-90h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-80h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::string strName; // [rsp+50h] [rbp-50h] BYREF
  int8_t connid; // [rsp+63h] [rbp-3Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-3Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-38h]
  int32_t nRankIndex; // [rsp+74h] [rbp-2Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-28h]
  int16_t i; // [rsp+7Ah] [rbp-26h]
  int16_t i_0; // [rsp+7Ch] [rbp-24h]
  int16_t i_1; // [rsp+7Eh] [rbp-22h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 2031);
    if ( this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay )
    {
      connid = Player::getConnId(player);
      nCharId = Player::getCid(player);
      Player::getName((const Player *const)&strName);
      CFestivalDoubleEleven::checkXiaoFeiRankInvalid(this, connid);
      nRankIndex = -1;
      for ( i = 0; i < this->m_nXiaoFeiRankSize; ++i )
      {
        v3 = std::vector<int>::operator[](&this->m_vXiaoFeiRankLimit, i);
        if ( *v3 <= nScore )
        {
          Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
          v4 = i;
          m_nDay = this->m_nDay;
          v6 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
          v7 = std::vector<std::vector<FestivalRank>>::operator[](v6, m_nDay);
          v8 = std::vector<FestivalRank>::operator[](v7, v4);
          if ( v8->nScore >= nScore )
          {
            v9 = 1;
          }
          else
          {
            nRankIndex = i;
            v9 = 0;
          }
          Answer::MutexGuard::~MutexGuard(&lock_0);
          if ( !v9 )
            break;
        }
      }
      if ( nRankIndex >= 0 )
      {
        nOldIndex = this->m_nXiaoFeiRankSize - 1;
        for ( i_0 = 0; i_0 < this->m_nXiaoFeiRankSize; ++i_0 )
        {
          Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
          v10 = i_0;
          v11 = this->m_nDay;
          v12 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
          v13 = std::vector<std::vector<FestivalRank>>::operator[](v12, v11);
          v14 = std::vector<FestivalRank>::operator[](v13, v10);
          if ( v14->nCharId == nCharId )
          {
            nOldIndex = i_0;
            v15 = 0;
          }
          else
          {
            v15 = 1;
          }
          Answer::MutexGuard::~MutexGuard(&lock_1);
          if ( !v15 )
            break;
        }
        if ( nOldIndex < nRankIndex )
          nRankIndex = nOldIndex;
        if ( nOldIndex != nRankIndex )
        {
          for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
          {
            Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
            v16 = i_1 - 1;
            v17 = this->m_nDay;
            v18 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &this->m_mXiaoFeiRank,
                    &connid);
            v19 = std::vector<std::vector<FestivalRank>>::operator[](v18, v17);
            v20 = std::vector<FestivalRank>::operator[](v19, v16);
            v21 = i_1;
            v22 = this->m_nDay;
            v23 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &this->m_mXiaoFeiRank,
                    &connid);
            v24 = std::vector<std::vector<FestivalRank>>::operator[](v23, v22);
            v25 = std::vector<FestivalRank>::operator[](v24, v21);
            FestivalRank::operator=(v25, v20);
            v26 = i_1;
            v27 = this->m_nDay;
            v28 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &this->m_mXiaoFeiRank,
                    &connid);
            v29 = std::vector<std::vector<FestivalRank>>::operator[](v28, v27);
            std::vector<FestivalRank>::operator[](v29, v26)->bChange = 1;
            Answer::MutexGuard::~MutexGuard(&lock_2);
          }
        }
        Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
        v30 = nRankIndex;
        v31 = this->m_nDay;
        v32 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
        v33 = std::vector<std::vector<FestivalRank>>::operator[](v32, v31);
        v34 = std::vector<FestivalRank>::operator[](v33, v30);
        v34->nCharId = nCharId;
        v35 = nRankIndex;
        v36 = this->m_nDay;
        v37 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
        v38 = std::vector<std::vector<FestivalRank>>::operator[](v37, v36);
        v39 = std::vector<FestivalRank>::operator[](v38, v35);
        std::string::operator=(&v39->strName, &strName);
        v40 = nRankIndex;
        v41 = this->m_nDay;
        v42 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
        v43 = std::vector<std::vector<FestivalRank>>::operator[](v42, v41);
        v44 = std::vector<FestivalRank>::operator[](v43, v40);
        v44->nScore = nScore;
        v45 = nRankIndex;
        v46 = this->m_nDay;
        v47 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
        v48 = std::vector<std::vector<FestivalRank>>::operator[](v47, v46);
        v49 = std::vector<FestivalRank>::operator[](v48, v45);
        v49->nTime = Unit::getNow(player);
        v50 = nRankIndex;
        v51 = this->m_nDay;
        v52 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&this->m_mXiaoFeiRank, &connid);
        v53 = std::vector<std::vector<FestivalRank>>::operator[](v52, v51);
        std::vector<FestivalRank>::operator[](v53, v50)->bChange = 1;
        Answer::MutexGuard::~MutexGuard(&lock);
      }
      std::string::~string(&strName);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::updateXiaoFeiRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nDay,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<std::vector<FestivalRank>> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<std::vector<FestivalRank>> *v7; // rax
  std::vector<FestivalRank> *v8; // rax
  std::vector<std::vector<FestivalRank>> *v9; // rax
  std::vector<FestivalRank> *v10; // rax
  std::vector<std::vector<FestivalRank>> *v12; // rax
  std::vector<FestivalRank> *v13; // rax
  FestivalRank *v14; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nDay >= 0 && nDay < thisa->m_nEndDay && nIndex >= 0 && nIndex < thisa->m_nXiaoFeiRankSize )
  {
    CFestivalDoubleEleven::checkXiaoFeiRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v5 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida);
    v6 = std::vector<std::vector<FestivalRank>>::operator[](v5, nDay);
    if ( std::vector<FestivalRank>::operator[](v6, nIndex)->nScore < info->nScore
      || (v7 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida),
          v8 = std::vector<std::vector<FestivalRank>>::operator[](v7, nDay),
          std::vector<FestivalRank>::operator[](v8, nIndex)->nScore == info->nScore)
      && (v9 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida),
          v10 = std::vector<std::vector<FestivalRank>>::operator[](v9, nDay),
          std::vector<FestivalRank>::operator[](v10, nIndex)->nTime < info->nTime) )
    {
      v12 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida);
      v13 = std::vector<std::vector<FestivalRank>>::operator[](v12, nDay);
      v14 = std::vector<FestivalRank>::operator[](v13, nIndex);
      FestivalRank::operator=(v14, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkXiaoFeiRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  size_t m_nXiaoFeiRankSize; // rbx
  std::vector<FestivalRank> *v3; // rax
  std::vector<std::vector<FestivalRank>> *v4; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-CCh] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-C8h]
  FestivalRankVtVt vRank; // [rsp+10h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > iter; // [rsp+30h] [rbp-A0h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > __x; // [rsp+50h] [rbp-80h] BYREF
  std::vector<FestivalRank> p___x; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank v12; // [rsp+80h] [rbp-50h] BYREF
  int32_t i; // [rsp+BCh] [rbp-14h]

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::find(&this->m_mXiaoFeiRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::end(&thisa->m_mXiaoFeiRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator==(
         &iter,
         &__x) )
  {
    std::vector<std::vector<FestivalRank>>::vector(&vRank);
    std::vector<FestivalRank>::vector(&p___x);
    std::vector<std::vector<FestivalRank>>::resize(&vRank, thisa->m_nEndDay, &p___x);
    std::vector<FestivalRank>::~vector(&p___x);
    for ( i = 0; thisa->m_nEndDay > i; ++i )
    {
      FestivalRank::FestivalRank(&v12);
      m_nXiaoFeiRankSize = thisa->m_nXiaoFeiRankSize;
      v3 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      std::vector<FestivalRank>::resize(v3, m_nXiaoFeiRankSize, &v12);
      FestivalRank::~FestivalRank(&v12);
    }
    v4 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida);
    std::vector<std::vector<FestivalRank>>::operator=(v4, &vRank);
    std::vector<std::vector<FestivalRank>>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkXiaoFeiRank(CFestivalDoubleEleven *const this)
{
  size_t v1; // rbx
  std::vector<FestivalRank> *v2; // rax
  size_t v3; // rbx
  std::vector<FestivalRank> *v4; // rax
  size_t v5; // rbx
  std::vector<FestivalRank> *v6; // rax
  size_t v7; // rbx
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // r13
  int16_t v10; // r14
  int16_t m_nDay; // r12
  DBService *v12; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVtVt *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  if ( this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::begin(&this->m_mXiaoFeiRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::end(&this->m_mXiaoFeiRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator!=(
              &iter,
              &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->second;
      for ( i = 0; i < this->m_nXiaoFeiRankSize; ++i )
      {
        v1 = i;
        v2 = std::vector<std::vector<FestivalRank>>::operator[](vRank, this->m_nDay);
        if ( std::vector<FestivalRank>::operator[](v2, v1)->nCharId <= 0 )
          break;
        v3 = i;
        v4 = std::vector<std::vector<FestivalRank>>::operator[](vRank, this->m_nDay);
        if ( std::vector<FestivalRank>::operator[](v4, v3)->bChange )
        {
          v5 = i;
          v6 = std::vector<std::vector<FestivalRank>>::operator[](vRank, this->m_nDay);
          std::vector<FestivalRank>::operator[](v6, v5)->bChange = 0;
          v7 = i;
          v8 = std::vector<std::vector<FestivalRank>>::operator[](vRank, this->m_nDay);
          v9 = std::vector<FestivalRank>::operator[](v8, v7);
          v10 = i;
          m_nDay = this->m_nDay;
          LOBYTE(v7) = connid;
          v12 = Answer::Singleton<DBService>::instance();
          DBService::SaveDoubleElevenRank(v12, v7, 12, m_nDay, v10, v9);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::sendXiaoFeiRankMail(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  size_t v2; // rbx
  std::vector<FestivalRank> *v3; // rax
  std::vector<MemChrBag> *v4; // r14
  int32_t v5; // r13d
  size_t v6; // rbx
  std::vector<FestivalRank> *v7; // rax
  CharId_t nCharId; // r12
  DBService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v14; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVtVt *vRank; // [rsp+60h] [rbp-30h]
  int32_t nIndex; // [rsp+68h] [rbp-28h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 && this->m_nDay > 0 && this->m_nDay <= this->m_nEndDay )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::begin(&this->m_mXiaoFeiRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::end(&this->m_mXiaoFeiRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator!=(
              &iter,
              &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->second;
      nIndex = this->m_nDay - 1;
      for ( i = 0; i < this->m_nXiaoFeiRankSize; ++i )
      {
        v2 = i;
        v3 = std::vector<std::vector<FestivalRank>>::operator[](vRank, nIndex);
        if ( std::vector<FestivalRank>::operator[](v3, v2)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v14);
          std::string::string(&Param, &byte_8D8B2F, &v14);
          v4 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vXiaoFeiRankReward, i);
          v5 = *std::vector<int>::operator[](&this->m_vXiaoFeiRankMail, i);
          v6 = i;
          v7 = std::vector<std::vector<FestivalRank>>::operator[](vRank, nIndex);
          nCharId = std::vector<FestivalRank>::operator[](v7, v6)->nCharId;
          LOBYTE(v6) = connid;
          v9 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(
            v9,
            v6,
            nCharId,
            v5,
            v4,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_XIAO_FEI_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v14);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::loadXiaoFeiSumRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=16 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_nXiaoFeiSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_nXiaoFeiSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateXiaoFeiSumRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  size_t v3; // rbx
  std::vector<FestivalRank> *v4; // rax
  FestivalRank *v5; // rax
  int v6; // ebx
  size_t v7; // rbx
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int v10; // ebx
  size_t v11; // rbx
  std::vector<FestivalRank> *v12; // rax
  FestivalRank *v13; // rbx
  size_t v14; // r12
  std::vector<FestivalRank> *v15; // rax
  FestivalRank *v16; // rax
  size_t v17; // rbx
  std::vector<FestivalRank> *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  FestivalRank *v21; // rax
  size_t v22; // rbx
  std::vector<FestivalRank> *v23; // rax
  FestivalRank *v24; // rax
  size_t v25; // rbx
  std::vector<FestivalRank> *v26; // rax
  FestivalRank *v27; // rax
  size_t v28; // rbx
  std::vector<FestivalRank> *v29; // rax
  FestivalRank *v30; // rbx
  size_t v31; // rbx
  std::vector<FestivalRank> *v32; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
    if ( this->m_nXiaoFeiSumRankLimit <= nScore )
    {
      connid = Player::getConnId(player);
      nCharId = Player::getCid(player);
      Player::getName((const Player *const)&strName);
      CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(this, connid);
      nRankIndex = -1;
      for ( i = 0; i < this->m_nXiaoFeiSumRankSize; ++i )
      {
        Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
        v3 = i;
        v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
        v5 = std::vector<FestivalRank>::operator[](v4, v3);
        if ( v5->nScore >= nScore )
        {
          v6 = 1;
        }
        else
        {
          nRankIndex = i;
          v6 = 0;
        }
        Answer::MutexGuard::~MutexGuard(&lock_0);
        if ( !v6 )
          break;
      }
      if ( nRankIndex >= 0 )
      {
        nOldIndex = this->m_nXiaoFeiSumRankSize - 1;
        for ( i_0 = 0; i_0 < this->m_nXiaoFeiSumRankSize; ++i_0 )
        {
          Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
          v7 = i_0;
          v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v9 = std::vector<FestivalRank>::operator[](v8, v7);
          if ( v9->nCharId == nCharId )
          {
            nOldIndex = i_0;
            v10 = 0;
          }
          else
          {
            v10 = 1;
          }
          Answer::MutexGuard::~MutexGuard(&lock_1);
          if ( !v10 )
            break;
        }
        if ( nOldIndex < nRankIndex )
          nRankIndex = nOldIndex;
        if ( nOldIndex != nRankIndex )
        {
          for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
          {
            Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
            v11 = i_1 - 1;
            v12 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
            v13 = std::vector<FestivalRank>::operator[](v12, v11);
            v14 = i_1;
            v15 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
            v16 = std::vector<FestivalRank>::operator[](v15, v14);
            FestivalRank::operator=(v16, v13);
            v17 = i_1;
            v18 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
            std::vector<FestivalRank>::operator[](v18, v17)->bChange = 1;
            Answer::MutexGuard::~MutexGuard(&lock_2);
          }
        }
        Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
        v19 = nRankIndex;
        v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
        v21 = std::vector<FestivalRank>::operator[](v20, v19);
        v21->nCharId = nCharId;
        v22 = nRankIndex;
        v23 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
        v24 = std::vector<FestivalRank>::operator[](v23, v22);
        std::string::operator=(&v24->strName, &strName);
        v25 = nRankIndex;
        v26 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
        v27 = std::vector<FestivalRank>::operator[](v26, v25);
        v27->nScore = nScore;
        v28 = nRankIndex;
        v29 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
        v30 = std::vector<FestivalRank>::operator[](v29, v28);
        v30->nTime = Unit::getNow(player);
        v31 = nRankIndex;
        v32 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
        std::vector<FestivalRank>::operator[](v32, v31)->bChange = 1;
        Answer::MutexGuard::~MutexGuard(&lock);
      }
      std::string::~string(&strName);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::updateXiaoFeiSumRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nXiaoFeiSumRankSize )
  {
    CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mXiaoFeiSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mXiaoFeiSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nXiaoFeiSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkXiaoFeiSumRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mXiaoFeiSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mXiaoFeiSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_nXiaoFeiSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 16, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::sendXiaoFeiSumRankMail(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mXiaoFeiSumRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mXiaoFeiSumRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < this->m_nXiaoFeiSumRankSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vXiaoFeiSumRankReward, i);
          v3 = *std::vector<int>::operator[](&this->m_vXiaoFeiSumRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(
            v6,
            v5,
            nCharId,
            v3,
            v2,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_XIAO_FEI_SUM_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::loadRechargeSumRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=32 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_nRechargeSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_nRechargeSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateRechargeSumRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    CFestivalDoubleEleven::checkRechargeSumRankInvalid(this, connid);
    nRankIndex = -1;
    for ( i = 0; i < this->m_nRechargeSumRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
      v3 = std::vector<int>::operator[](&this->m_vRechargeSumRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = this->m_nRechargeSumRankSize - 1;
      for ( i_0 = 0; i_0 < this->m_nRechargeSumRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeSumRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::updateRechargeSumRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nRechargeSumRankSize )
  {
    CFestivalDoubleEleven::checkRechargeSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkRechargeSumRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mRechargeSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mRechargeSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nRechargeSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkRechargeSumRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mRechargeSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mRechargeSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_nRechargeSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 32, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::sendRechargeSumRankMail(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mRechargeSumRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mRechargeSumRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < this->m_nRechargeSumRankSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeSumRankReward, i);
          v3 = *std::vector<int>::operator[](&this->m_vRechargeSumRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(
            v6,
            v5,
            nCharId,
            v3,
            v2,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_RECHARGE_SUM_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::GetMoYuShiJieIconState(
        CFestivalDoubleEleven *const this,
        IconStateList *const iconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE) )
  {
    CFestivalDoubleEleven::getMoYuShiJieIconState(&__x, this);
    std::list<ShowIcon>::push_back(iconList, &__x);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::BroadCastMoYuShiJieIconState(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // eax
  GameService *v4; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    CFestivalDoubleEleven::getMoYuShiJieIconState(&stu, this);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, stu.nId);
      Answer::NetPacket::writeInt8(packet, stu.nState);
      Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
      Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
      Answer::NetPacket::writeInt32(packet, stu.nIconRight);
      Answer::NetPacket::writeInt8(packet, stu.nEffects);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddMoYuShiJieDrop(
        CFestivalDoubleEleven *const this,
        int32_t nFloor,
        MemChrBagVector *const vItem)
{
  std::vector<MemChrBag> *v3; // rax
  std::vector<MemChrBag> *v4; // rax
  Answer::Random *v5; // rax
  size_t v6; // rbx
  std::vector<MemChrBag> *v7; // rax
  MemChrBag *v8; // rdx
  int nIndex; // [rsp+24h] [rbp-1Ch]
  int32_t nMax; // [rsp+28h] [rbp-18h]

  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE) )
  {
    nIndex = nFloor - 1;
    if ( nFloor - 1 >= 0 && this->m_nMoYuShiJieDropSize > nIndex )
    {
      v3 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vMoYuShiJieDrop, nIndex);
      if ( !std::vector<MemChrBag>::empty(v3) )
      {
        v4 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vMoYuShiJieDrop, nIndex);
        nMax = std::vector<MemChrBag>::size(v4) - 1;
        v5 = Answer::Singleton<Answer::Random>::instance();
        v6 = Answer::Random::generate(v5, 0, nMax);
        v7 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vMoYuShiJieDrop, nIndex);
        v8 = std::vector<MemChrBag>::operator[](v7, v6);
        std::vector<MemChrBag>::push_back(vItem, v8);
      }
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::AddEquipUpStarBack(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t nStar)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t nStara; // [rsp+Ch] [rbp-34h] BYREF
  Player *playera; // [rsp+10h] [rbp-30h]
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-10h] BYREF
  int32_t nAddCount; // [rsp+3Ch] [rbp-4h]

  thisa = this;
  playera = player;
  nStara = nStar;
  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) && playera )
  {
    iter._M_node = std::map<int,int>::find(&thisa->m_mEquipUpStarBackStarCount, &nStara)._M_node;
    __x._M_node = std::map<int,int>::end(&thisa->m_mEquipUpStarBackStarCount)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&iter, &__x) )
    {
      nAddCount = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      if ( nAddCount > 0 )
      {
        OperateLimit = Player::GetOperateLimit(playera);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1617, nAddCount);
        CFestivalDoubleEleven::SendIconState(thisa, playera);
      }
    }
  }
}


#####################################
bool __cdecl CFestivalDoubleEleven::RefreshMysteryShopItem(CFestivalDoubleEleven *const this, Player *player)
{
  int64_t m_nCount; // r12
  CURRENCY_TYPE v4; // ebx
  CExtCharBag *Bag; // rax

  if ( !player )
    return 0;
  if ( this->m_sMysteryShopRefreshCost.m_nClass == 4 )
  {
    m_nCount = this->m_sMysteryShopRefreshCost.m_nCount;
    v4 = TranseCurrencyType((CURRENCY_ITEM_ID)this->m_sMysteryShopRefreshCost.m_nId);
    return Player::DecCurrency(player, v4, m_nCount, CURRENCY_CHANGE_REASON::GCR_MYSTERY_SHOP_REFRESH, 0);
  }
  else
  {
    Bag = Player::GetBag(player);
    return CExtCharBag::RemoveItem(Bag, &this->m_sMysteryShopRefreshCost, ITEM_CHANGE_REASON::ICR_MYSTERY_SHOP_REFRESH);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkRefreshMysteryShop(CFestivalDoubleEleven *const this)
{
  if ( !(this->m_nMinute % 120) )
    CFestivalDoubleEleven::broadcastRefreshMysteryShop(this);
}


#####################################
void __cdecl CFestivalDoubleEleven::broadcastRefreshMysteryShop(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nMysteryShopRefreshBroad);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::broadcastPlayerAction(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int32_t nBroadId,
        CharId_t nCharId,
        const std::string *const strCharName)
{
  GameService *v5; // rax
  uint32_t WOffset; // edx
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, connid, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, nBroadId);
    Answer::NetPacket::writeUTF8(packet, strCharName);
    Answer::NetPacket::writeInt64(packet, nCharId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v7 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v7, connid, packet);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::SendDaTiReward(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int32_t nIndex,
        CharId_t nCharId)
{
  std::vector<MemChrBag> *v4; // r13
  int32_t v5; // r12d
  DBService *v6; // rax
  std::string Param; // [rsp+30h] [rbp-30h] BYREF
  _BYTE v10[33]; // [rsp+3Fh] [rbp-21h] BYREF

  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI)
    && nIndex > 0
    && this->m_nDaTiRankSize >= nIndex )
  {
    std::allocator<char>::allocator(v10);
    std::string::string(&Param, &byte_8D8B2F, v10);
    v4 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vDaTiRankReward, nIndex - 1);
    v5 = *std::vector<int>::operator[](&this->m_vDaTiRankMail, nIndex - 1);
    v6 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(
      v6,
      connid,
      nCharId,
      v5,
      v4,
      ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_DA_TI_RANK_REWARD,
      &Param,
      0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(v10);
  }
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::CalBossScoreAddValue(CFestivalDoubleEleven *const this, int32_t nValue)
{
  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE) )
    return nValue * this->m_nBossScoreRate / 100;
  else
    return nValue;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::calRechargeBack(CFestivalDoubleEleven *const this, int32_t nValue)
{
  int32_t nValuea; // [rsp+4h] [rbp-1Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-18h]
  int32_t nBackValue; // [rsp+18h] [rbp-8h]
  int32_t nResult; // [rsp+1Ch] [rbp-4h]

  thisa = this;
  nValuea = nValue;
  for ( nBackValue = 0; nValuea > 0; nBackValue += nResult )
  {
    nResult = CFestivalDoubleEleven::calRechargeBackHelper(thisa, &nValuea);
    if ( nResult <= 0 )
      break;
  }
  return nBackValue;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::calRechargeBackHelper(CFestivalDoubleEleven *const this, int32_t *const nValue)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  int32_t i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; this->m_nRechargeBackSize > i; ++i )
  {
    v2 = *nValue;
    if ( v2 >= *std::vector<int>::operator[](&this->m_vRechargeBackLimit, i) )
    {
      v3 = *nValue;
      *nValue = v3 - *std::vector<int>::operator[](&this->m_vRechargeBackLimit, i);
      return *std::vector<int>::operator[](&this->m_vRechargeBackValue, i);
    }
  }
  return 0;
}


#####################################
void __cdecl CFestivalDoubleEleven::loadCrossRechargeSumRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=33 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_nCrossRechargeSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_nCrossRechargeSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateCrossRechargeSumRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(this, connid);
    nRankIndex = -1;
    for ( i = 0; i < this->m_nCrossRechargeSumRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
      v3 = std::vector<int>::operator[](&this->m_vCrossRechargeSumRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = this->m_nCrossRechargeSumRankSize - 1;
      for ( i_0 = 0; i_0 < this->m_nCrossRechargeSumRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossRechargeSumRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::updateCrossRechargeSumRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nCrossRechargeSumRankSize )
  {
    CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mCrossRechargeSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mCrossRechargeSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nCrossRechargeSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkCrossRechargeSumRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mCrossRechargeSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mCrossRechargeSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_nCrossRechargeSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 33, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::loadCrossXiaoFeiSumRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=34 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_nCrossXiaoFeiSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_nCrossXiaoFeiSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(this, connid);
    nRankIndex = -1;
    for ( i = 0; i < this->m_nCrossXiaoFeiSumRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
      v3 = std::vector<int>::operator[](&this->m_vCrossXiaoFeiSumRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = this->m_nCrossXiaoFeiSumRankSize - 1;
      for ( i_0 = 0; i_0 < this->m_nCrossXiaoFeiSumRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossXiaoFeiSumRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mCrossXiaoFeiSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mCrossXiaoFeiSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nCrossXiaoFeiSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nCrossXiaoFeiSumRankSize )
  {
    CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkCrossXiaoFeiSumRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mCrossXiaoFeiSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mCrossXiaoFeiSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_nCrossXiaoFeiSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 34, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::loadCrossChouJiangRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=37 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_nCrossChouJiangRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_nCrossChouJiangRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateCrossChouJiangRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1601);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(this, connid);
    nRankIndex = -1;
    for ( i = 0; i < this->m_nCrossChouJiangRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
      v3 = std::vector<int>::operator[](&this->m_vCrossChouJiangRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = this->m_nCrossChouJiangRankSize - 1;
      for ( i_0 = 0; i_0 < this->m_nCrossChouJiangRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mCrossChouJiangRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::updateCrossChouJiangRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nCrossChouJiangRankSize )
  {
    CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mCrossChouJiangRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mCrossChouJiangRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nCrossChouJiangRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkCrossChouJiangRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mCrossChouJiangRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mCrossChouJiangRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_nCrossChouJiangRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 37, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetEquipQingYiGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // eax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_QING_YI) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nEquipQingYiSize )
    return 10002;
  if ( *std::vector<int>::operator[](&this->m_vEquipQingYiLimit, nIndex) > 0 )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1125);
  nNewSign = LimitCount | (1 << nIndex);
  if ( nNewSign == LimitCount )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vEquipQingYiReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_EQUIP_QING_YI_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 1125, nNewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetFriendQingYiGift(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t LimitCount; // eax
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int nFriendQingYi; // [rsp+24h] [rbp-1Ch]
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nFriendQingYiSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nFriendQingYi = CExtOperateLimit::GetLimitCount(OperateLimit, 1624);
  if ( *std::vector<int>::operator[](&this->m_vFriendQingYiLimit, nIndex) > nFriendQingYi )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(v5, 1625);
  nNewSign = LimitCount | (1 << nIndex);
  if ( nNewSign == LimitCount )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vFriendQingYiReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_FRIEND_QING_YI_GIFT) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1625, nNewSign);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
void __cdecl CFestivalDoubleEleven::UpdateMonsterScore(
        CFestivalDoubleEleven *const this,
        Player *player,
        int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t Times; // [rsp+2Ch] [rbp-4h]

  if ( player && CFestivalDoubleEleven::IsInTime(this) )
  {
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1626, nCount);
      CFestivalDoubleEleven::updateBossScoreRank(this, player);
    }
    if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
    {
      v4 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v4, 2095, nCount);
      Times = Player::getRecord(player, 2096);
      if ( CFestivalDoubleEleven::GetScoreCanDrawTime(this, player) > Times )
        CFestivalDoubleEleven::SendIconState(this, player);
    }
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::loadBossScoreRank(CFestivalDoubleEleven *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=43 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, this->m_BossScoreRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && this->m_BossScoreRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalDoubleEleven::updateBossScoreRank(CFestivalDoubleEleven *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v3; // rax
  int *v4; // rax
  int v5; // ebx
  CExtOperateLimit *v6; // rax
  std::vector<MemChrBag> *v7; // r13
  int32_t v8; // r12d
  DBService *v9; // rax
  size_t v10; // rbx
  std::vector<FestivalRank> *v11; // rax
  FestivalRank *v12; // rax
  int v13; // ebx
  size_t v14; // rbx
  std::vector<FestivalRank> *v15; // rax
  FestivalRank *v16; // rax
  int v17; // ebx
  size_t v18; // rbx
  std::vector<FestivalRank> *v19; // rax
  FestivalRank *v20; // rbx
  size_t v21; // r12
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  size_t v26; // rbx
  std::vector<FestivalRank> *v27; // rax
  FestivalRank *v28; // rax
  size_t v29; // rbx
  std::vector<FestivalRank> *v30; // rax
  FestivalRank *v31; // rax
  size_t v32; // rbx
  std::vector<FestivalRank> *v33; // rax
  FestivalRank *v34; // rax
  size_t v35; // rbx
  std::vector<FestivalRank> *v36; // rax
  FestivalRank *v37; // rbx
  size_t v38; // rbx
  std::vector<FestivalRank> *v39; // rax
  Answer::MutexGuard lock_2; // [rsp+20h] [rbp-B0h] BYREF
  Answer::MutexGuard lock_1; // [rsp+30h] [rbp-A0h] BYREF
  Answer::MutexGuard lock_0; // [rsp+40h] [rbp-90h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-80h] BYREF
  std::string strName; // [rsp+60h] [rbp-70h] BYREF
  int8_t connid; // [rsp+6Fh] [rbp-61h] BYREF
  std::string Param; // [rsp+70h] [rbp-60h] BYREF
  char v47; // [rsp+87h] [rbp-49h] BYREF
  int32_t nScore; // [rsp+88h] [rbp-48h]
  int32_t nRecord; // [rsp+8Ch] [rbp-44h]
  CharId_t nCharId; // [rsp+90h] [rbp-40h]
  int32_t nRankIndex; // [rsp+9Ch] [rbp-34h]
  int16_t nOldIndex; // [rsp+A2h] [rbp-2Eh]
  int32_t k; // [rsp+A4h] [rbp-2Ch]
  int16_t i; // [rsp+AAh] [rbp-26h]
  int16_t i_0; // [rsp+ACh] [rbp-24h]
  int16_t i_1; // [rsp+AEh] [rbp-22h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1626);
    v3 = Player::GetOperateLimit(player);
    nRecord = CExtOperateLimit::GetLimitCount(v3, 1627);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    for ( k = 0; this->m_GetReardSize > k; ++k )
    {
      if ( k + 1 > nRecord )
      {
        v4 = std::vector<int>::operator[](&this->m_vBossScoreiLimit, k);
        if ( *v4 > nScore )
          break;
        v5 = k + 1;
        v6 = Player::GetOperateLimit(player);
        CExtOperateLimit::UpdateLimitCount(v6, 1627, v5);
        std::allocator<char>::allocator(&v47);
        std::string::string(&Param, &byte_8D8B2F, &v47);
        v7 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vBossScoreReward, k);
        v8 = *std::vector<int>::operator[](&this->m_vGetBossScoreMail, k);
        LOBYTE(v5) = connid;
        v9 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(v9, v5, nCharId, v8, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BOSS_RANK, &Param, 0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(&v47);
      }
    }
    CFestivalDoubleEleven::checkBossScoreRankInvalid(this, connid);
    nRankIndex = -1;
    for ( i = 0; i < this->m_BossScoreRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
      v10 = i;
      v11 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
      v12 = std::vector<FestivalRank>::operator[](v11, v10);
      if ( v12->nScore >= nScore )
      {
        v13 = 1;
      }
      else
      {
        nRankIndex = i;
        v13 = 0;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v13 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = this->m_BossScoreRankSize - 1;
      for ( i_0 = 0; i_0 < this->m_BossScoreRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
        v14 = i_0;
        v15 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
        v16 = std::vector<FestivalRank>::operator[](v15, v14);
        if ( v16->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v17 = 0;
        }
        else
        {
          v17 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v17 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
          v18 = i_1 - 1;
          v19 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
          v20 = std::vector<FestivalRank>::operator[](v19, v18);
          v21 = i_1;
          v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
          v23 = std::vector<FestivalRank>::operator[](v22, v21);
          FestivalRank::operator=(v23, v20);
          v24 = i_1;
          v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
          std::vector<FestivalRank>::operator[](v25, v24)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
      v26 = nRankIndex;
      v27 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
      v28 = std::vector<FestivalRank>::operator[](v27, v26);
      v28->nCharId = nCharId;
      v29 = nRankIndex;
      v30 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
      v31 = std::vector<FestivalRank>::operator[](v30, v29);
      std::string::operator=(&v31->strName, &strName);
      v32 = nRankIndex;
      v33 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
      v34 = std::vector<FestivalRank>::operator[](v33, v32);
      v34->nScore = nScore;
      v35 = nRankIndex;
      v36 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
      v37 = std::vector<FestivalRank>::operator[](v36, v35);
      v37->nTime = Unit::getNow(player);
      v38 = nRankIndex;
      v39 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mBossScoreRank, &connid);
      std::vector<FestivalRank>::operator[](v39, v38)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::updateBossScoreRank(
        CFestivalDoubleEleven *const this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank *const info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_BossScoreRankSize )
  {
    CFestivalDoubleEleven::checkBossScoreRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CFestivalDoubleEleven::checkBossScoreRankInvalid(CFestivalDoubleEleven *const this, int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&this->m_mBossScoreRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mBossScoreRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_BossScoreRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::checkBossScoreRank(CFestivalDoubleEleven *const this)
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mBossScoreRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mBossScoreRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < this->m_BossScoreRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 43, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CFestivalDoubleEleven::sendBossScoreRankMail(CFestivalDoubleEleven *const this)
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mBossScoreRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mBossScoreRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < this->m_BossScoreRewardSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vBossScoreRankReward, i);
          v3 = *std::vector<int>::operator[](&this->m_vBossScoreRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v6, v5, nCharId, v3, v2, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BOSS_RANK, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
int8_t __cdecl CFestivalDoubleEleven::GetChouJiangType(CFestivalDoubleEleven *const this)
{
  int v1; // eax

  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG) )
    return this->m_ChouJiangType;
  else
    LOBYTE(v1) = 0;
  return v1;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetChouJiangSpecialTime(CFestivalDoubleEleven *const this)
{
  if ( CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG) )
    return this->m_ChouJiangCount;
  else
    return 0;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetScoreCanDrawTime(CFestivalDoubleEleven *const this, Player *pPlayer)
{
  int32_t Count; // [rsp+1Ch] [rbp-14h]
  int Score; // [rsp+20h] [rbp-10h]
  int Recharge; // [rsp+24h] [rbp-Ch]
  int32_t i; // [rsp+28h] [rbp-8h]
  int32_t i_0; // [rsp+2Ch] [rbp-4h]

  if ( !pPlayer )
    return 0;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
    return 0;
  Count = 0;
  Score = Player::getRecord(pPlayer, 2095);
  for ( i = 0; this->m_nScoreSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&this->m_vScoreLimit, i) <= Score )
      ++Count;
  }
  Recharge = Player::GetTodayPayGold(pPlayer);
  for ( i_0 = 0; this->m_nDailyRechargeDrawSize > i_0; ++i_0 )
  {
    if ( *std::vector<int>::operator[](&this->m_nDailyRechargeDrawLimit, i_0) <= Recharge )
      ++Count;
  }
  return Count;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::OnRandScoreDrawItem(CFestivalDoubleEleven *const this, Player *pPlayer)
{
  int32_t v2; // ebx
  int32_t Record; // ebx
  CExtCharBag *Bag; // rax
  RateItem *v5; // rbx
  RateItem *v6; // rax
  Answer::Random *v7; // rax
  std::pair<const int,RateItem> *v8; // rax
  std::pair<const int,RateItem> *v9; // rax
  int8_t ConnId; // bl
  GameService *v11; // rax
  std::pair<const int,RateItem> *v12; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v15; // bl
  GameService *v16; // rax
  std::pair<const int,RateItem> *v17; // rax
  CExtCharBag *v18; // rax
  CExtOperateLimit *OperateLimit; // rax
  int8_t v20; // bl
  GameService *v21; // rax
  CharId_t Cid; // rax
  uint32_t v23; // eax
  int8_t v24; // bl
  GameService *v25; // rax
  RateItemMap items; // [rsp+10h] [rbp-E0h] BYREF
  MemChrBag bagItem; // [rsp+40h] [rbp-B0h] BYREF
  int32_t i; // [rsp+6Ch] [rbp-84h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,RateItem> > it; // [rsp+70h] [rbp-80h] BYREF
  RateItem stu; // [rsp+80h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,RateItem> > __x; // [rsp+A0h] [rbp-50h] BYREF
  std::string val; // [rsp+B0h] [rbp-40h] BYREF
  int32_t OldRecord; // [rsp+C0h] [rbp-30h]
  int32_t MaxRate; // [rsp+C4h] [rbp-2Ch]
  int32_t nRand; // [rsp+C8h] [rbp-28h]
  int32_t NewRecord; // [rsp+CCh] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+D0h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+D8h] [rbp-18h]

  if ( !pPlayer )
    return 2;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
    return 2;
  Record = Player::getRecord(pPlayer, 2096);
  if ( Record >= CFestivalDoubleEleven::GetScoreCanDrawTime(this, pPlayer) )
    return 2;
  Bag = Player::GetBag(pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  OldRecord = Player::getRecord(pPlayer, 1628);
  std::map<int,RateItem>::map(&items);
  MaxRate = 0;
  for ( i = 0; this->m_nRewardSize > i; ++i )
  {
    if ( ((OldRecord >> i) & 1) == 0 )
    {
      v5 = std::map<int,RateItem>::operator[](&items, &i);
      *v5 = *std::vector<RateItem>::operator[](&this->m_vBossScoreDrawReward, i);
      v6 = std::vector<RateItem>::operator[](&this->m_vBossScoreDrawReward, i);
      MaxRate += v6->nRate;
    }
  }
  if ( MaxRate > 0 )
  {
    memset(&stu, 0, sizeof(stu));
    v7 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v7, 1, MaxRate);
    for ( it._M_node = std::map<int,RateItem>::begin(&items)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,RateItem>::end(&items)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator!=(&it, &__x) )
        break;
      v8 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
      if ( v8->second.nRate > nRand )
      {
        stu = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it)->second;
        v9 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
        NewRecord = OldRecord | (1 << v9->first);
        Player::updateRecord(pPlayer, 1628, NewRecord);
        ConnId = Player::getConnId(pPlayer);
        v11 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v11, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDFu);
        if ( packet )
        {
          v12 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v12->first);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(pPlayer);
          v15 = Player::getConnId(pPlayer);
          v16 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v16, v15, GateIndex, packet);
        }
        break;
      }
      v17 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
      nRand -= v17->second.nRate;
    }
    if ( stu.nItemId > 0 && stu.nItemCount > 0 )
    {
      *(&bagItem.endTime + 1) = 0;
      bagItem.srcId = 0;
      *(_DWORD *)&bagItem.itemClass = (unsigned __int8)stu.nItemClass;
      bagItem.itemCount = stu.nItemCount;
      bagItem.itemId = stu.nItemId;
      *(_QWORD *)&bagItem.bind = (unsigned __int8)stu.nBind;
      v18 = Player::GetBag(pPlayer);
      CExtCharBag::AddItem(v18, &bagItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_SOCRE_DRAW);
      OperateLimit = Player::GetOperateLimit(pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 2096, 1);
      if ( stu.nGongGaoId > 0 )
      {
        v20 = Player::getConnId(pPlayer);
        v21 = Answer::Singleton<GameService>::instance();
        packet_0 = GameService::popNetpacket(v21, v20, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( packet_0 )
        {
          Answer::NetPacket::writeInt32(packet_0, stu.nGongGaoId);
          Cid = Player::getCid(pPlayer);
          Answer::NetPacket::writeInt64(packet_0, Cid);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet_0, &val);
          std::string::~string(&val);
          Answer::NetPacket::writeInt32(packet_0, bagItem.itemId);
          Answer::NetPacket::writeInt8(packet_0, bagItem.itemClass);
          Answer::NetPacket::writeInt32(packet_0, bagItem.itemCount);
          v23 = Answer::NetPacket::getWOffset(packet_0);
          Answer::NetPacket::setSize(packet_0, v23);
          v24 = Player::getConnId(pPlayer);
          v25 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v25, v24, packet_0);
        }
      }
      CFestivalDoubleEleven::SendIconState(this, pPlayer);
      v2 = 0;
    }
    else
    {
      v2 = 2;
    }
  }
  else
  {
    v2 = 2;
  }
  std::map<int,RateItem>::~map(&items);
  return v2;
}


#####################################
int32_t __cdecl CFestivalDoubleEleven::GetFaBaoCritBackItem(
        CFestivalDoubleEleven *const this,
        Player *player,
        int8_t nType)
{
  int32_t v4; // ebx
  CExtCharBag *Bag; // rax
  MemChrBag item; // [rsp+20h] [rbp-40h] BYREF
  int32_t OldRecord; // [rsp+48h] [rbp-18h]
  int32_t NewRecord; // [rsp+4Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
    return 10002;
  if ( nType < 0 || nType >= this->m_nSize )
    return 10002;
  OldRecord = Player::getRecord(player, 1629);
  NewRecord = OldRecord | (1 << nType);
  if ( OldRecord == NewRecord )
    return 10002;
  v4 = *std::vector<int>::operator[](&this->m_NeedValue, nType);
  if ( v4 > Player::getRecord(player, 1630) )
    return 10002;
  item = *std::vector<MemChrBag>::operator[](&this->m_BackItem, nType);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::IDCR_DOUBLE_ELEVEN_FA_BAO_CRIT_BACK) )
    return 10002;
  Player::updateRecord(player, 1629, NewRecord);
  CFestivalDoubleEleven::SendIconState(this, player);
  return 0;
}


#####################################
void __cdecl CFestivalDoubleEleven::AddFaBaoValue(
        CFestivalDoubleEleven *const this,
        Player *pPlayer,
        int32_t Type,
        int32_t Value)
{
  CExtOperateLimit *OperateLimit; // rax
  bool CanOldGet; // [rsp+2Eh] [rbp-2h]
  bool CanNewGet; // [rsp+2Fh] [rbp-1h]

  if ( pPlayer )
  {
    if ( Value > 0 && CFestivalDoubleEleven::IsInTime(this, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
    {
      CanOldGet = CFestivalDoubleEleven::canGetFaBaoBack(this, pPlayer);
      if ( this->m_FaBaoType == Type )
      {
        OperateLimit = Player::GetOperateLimit(pPlayer);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1630, Value);
        CanNewGet = CFestivalDoubleEleven::canGetFaBaoBack(this, pPlayer);
        if ( !CanOldGet && CanNewGet )
          CFestivalDoubleEleven::SendIconState(this, pPlayer);
      }
    }
  }
}


