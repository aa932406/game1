// Decompiled methods for class: CZongHeYunYingHD
// Source: gameserver.cc
// Total methods: 26

#####################################
void __cdecl CZongHeYunYingHD::OnDaySwitch(CZongHeYunYingHD *const this)
{
  CfgData *v1; // rax
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  v1 = Answer::Singleton<CfgData>::instance();
  this->m_nDay = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
  if ( this->m_nDay == this->m_nEndDay )
    CZongHeYunYingHD::hideIcon(this, this->m_nIcon);
  if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_RANK_DAILY) )
    CZongHeYunYingHD::sendRechargeDailyRankReward(this);
  if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY) )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
    std::map<signed char,std::map<long,int>>::clear(&this->m_mRechargeDailyPlayer);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CZongHeYunYingHD::OnNewMinute(CZongHeYunYingHD *const this, int32_t nMinute)
{
  this->m_nMinute = nMinute;
  CZongHeYunYingHD::IsInTime(this);
}


#####################################
void __cdecl CZongHeYunYingHD::Init(CZongHeYunYingHD *const this, int32_t line)
{
  CfgData *v2; // rax
  CTimer *v3; // rax
  tm nowTime; // [rsp+10h] [rbp-40h] BYREF

  v2 = Answer::Singleton<CfgData>::instance();
  this->m_nDay = CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_NORMAL);
  v3 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&nowTime, v3);
  this->m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
  CZongHeYunYingHD::initCfgData(this);
  CZongHeYunYingHD::loadRankData(this);
}


#####################################
void __cdecl CZongHeYunYingHD::initOpenList(CZongHeYunYingHD *const this, const std::string *const str)
{
  std::string *v2; // rax
  const char *v3; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+10h] [rbp-60h] BYREF
  StringVector vOpen; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  char v7; // [rsp+4Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+50h] [rbp-20h] BYREF
  int8_t nType; // [rsp+5Fh] [rbp-11h]

  bzero(this->m_vOpen, 5u);
  std::allocator<char>::allocator(&v7);
  std::string::string(&delims, &unk_8F6567);
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
void __cdecl CZongHeYunYingHD::initCfgData(CZongHeYunYingHD *const this)
{
  Param2 *v1; // rbx
  std::string *v2; // rax
  const char *v3; // rax
  Param2 *v4; // rbx
  Param2 *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  Param2 *v8; // rbx
  std::string *v9; // rax
  const char *v10; // rax
  std::vector<MemChrBag> *v11; // rax
  int *v12; // rbx
  int *v13; // rbx
  int *v14; // rbx
  std::vector<MemChrBag> *v15; // rax
  int *v16; // rbx
  std::vector<MemChrBag> *v17; // rax
  char szCol[64]; // [rsp+10h] [rbp-590h] BYREF
  Answer::Inifile ini; // [rsp+50h] [rbp-550h] BYREF
  StringVector vIndex; // [rsp+90h] [rbp-510h] BYREF
  std::string file; // [rsp+B0h] [rbp-4F0h] BYREF
  char v22; // [rsp+BFh] [rbp-4E1h] BYREF
  std::string key; // [rsp+C0h] [rbp-4E0h] BYREF
  char v24; // [rsp+CFh] [rbp-4D1h] BYREF
  std::string section; // [rsp+D0h] [rbp-4D0h] BYREF
  char v26; // [rsp+DFh] [rbp-4C1h] BYREF
  std::string v27; // [rsp+E0h] [rbp-4C0h] BYREF
  char v28; // [rsp+EFh] [rbp-4B1h] BYREF
  std::string v29; // [rsp+F0h] [rbp-4B0h] BYREF
  char v30; // [rsp+FFh] [rbp-4A1h] BYREF
  std::string v31; // [rsp+100h] [rbp-4A0h] BYREF
  char v32; // [rsp+10Fh] [rbp-491h] BYREF
  std::string v33; // [rsp+110h] [rbp-490h] BYREF
  char v34; // [rsp+11Fh] [rbp-481h] BYREF
  Answer::Inifile v35; // [rsp+120h] [rbp-480h] BYREF
  char v36; // [rsp+15Fh] [rbp-441h] BYREF
  std::string v37; // [rsp+160h] [rbp-440h] BYREF
  char v38; // [rsp+16Fh] [rbp-431h] BYREF
  std::string v39; // [rsp+170h] [rbp-430h] BYREF
  char v40; // [rsp+17Fh] [rbp-421h] BYREF
  std::string v41; // [rsp+180h] [rbp-420h] BYREF
  char v42; // [rsp+18Fh] [rbp-411h] BYREF
  std::string v43; // [rsp+190h] [rbp-410h] BYREF
  char v44; // [rsp+19Fh] [rbp-401h] BYREF
  std::string v45; // [rsp+1A0h] [rbp-400h] BYREF
  char v46; // [rsp+1AFh] [rbp-3F1h] BYREF
  std::string v47; // [rsp+1B0h] [rbp-3F0h] BYREF
  char v48; // [rsp+1BFh] [rbp-3E1h] BYREF
  std::string v49; // [rsp+1C0h] [rbp-3E0h] BYREF
  char v50; // [rsp+1CFh] [rbp-3D1h] BYREF
  MemChrBagVector __x; // [rsp+1D0h] [rbp-3D0h] BYREF
  Answer::Inifile v52; // [rsp+1F0h] [rbp-3B0h] BYREF
  char v53; // [rsp+22Fh] [rbp-371h] BYREF
  std::string v54; // [rsp+230h] [rbp-370h] BYREF
  char v55; // [rsp+23Fh] [rbp-361h] BYREF
  std::string v56; // [rsp+240h] [rbp-360h] BYREF
  char v57; // [rsp+24Fh] [rbp-351h] BYREF
  std::string v58; // [rsp+250h] [rbp-350h] BYREF
  char v59; // [rsp+25Fh] [rbp-341h] BYREF
  std::string v60; // [rsp+260h] [rbp-340h] BYREF
  char v61; // [rsp+26Fh] [rbp-331h] BYREF
  std::string v62; // [rsp+270h] [rbp-330h] BYREF
  char v63; // [rsp+27Fh] [rbp-321h] BYREF
  std::string v64; // [rsp+280h] [rbp-320h] BYREF
  char v65; // [rsp+28Fh] [rbp-311h] BYREF
  std::string v66; // [rsp+290h] [rbp-310h] BYREF
  char v67; // [rsp+29Fh] [rbp-301h] BYREF
  Param2 v68; // [rsp+2A0h] [rbp-300h] BYREF
  std::vector<MemChrBag> p___x; // [rsp+2B0h] [rbp-2F0h] BYREF
  std::string delims; // [rsp+2D0h] [rbp-2D0h] BYREF
  char v71; // [rsp+2DFh] [rbp-2C1h] BYREF
  Answer::Inifile v72; // [rsp+2E0h] [rbp-2C0h] BYREF
  Answer::Inifile v73; // [rsp+330h] [rbp-270h] BYREF
  char v74; // [rsp+36Fh] [rbp-231h] BYREF
  std::string v75; // [rsp+370h] [rbp-230h] BYREF
  char v76; // [rsp+37Fh] [rbp-221h] BYREF
  std::string v77; // [rsp+380h] [rbp-220h] BYREF
  char v78; // [rsp+38Fh] [rbp-211h] BYREF
  std::string v79; // [rsp+390h] [rbp-210h] BYREF
  char v80; // [rsp+39Fh] [rbp-201h] BYREF
  std::string v81; // [rsp+3A0h] [rbp-200h] BYREF
  char v82; // [rsp+3AFh] [rbp-1F1h] BYREF
  std::string v83; // [rsp+3B0h] [rbp-1F0h] BYREF
  char v84; // [rsp+3BFh] [rbp-1E1h] BYREF
  std::string v85; // [rsp+3C0h] [rbp-1E0h] BYREF
  char v86; // [rsp+3CFh] [rbp-1D1h] BYREF
  std::string v87; // [rsp+3D0h] [rbp-1D0h] BYREF
  char v88; // [rsp+3DFh] [rbp-1C1h] BYREF
  std::vector<MemChrBag> v89; // [rsp+3E0h] [rbp-1C0h] BYREF
  std::string v90; // [rsp+400h] [rbp-1A0h] BYREF
  char v91; // [rsp+40Fh] [rbp-191h] BYREF
  std::string v92; // [rsp+410h] [rbp-190h] BYREF
  char v93; // [rsp+41Fh] [rbp-181h] BYREF
  std::string v94; // [rsp+420h] [rbp-180h] BYREF
  char v95; // [rsp+42Fh] [rbp-171h] BYREF
  std::string v96; // [rsp+430h] [rbp-170h] BYREF
  char v97; // [rsp+43Fh] [rbp-161h] BYREF
  MemChrBagVector v98; // [rsp+440h] [rbp-160h] BYREF
  Answer::Inifile v99; // [rsp+460h] [rbp-140h] BYREF
  char v100; // [rsp+49Fh] [rbp-101h] BYREF
  std::string v101; // [rsp+4A0h] [rbp-100h] BYREF
  char v102; // [rsp+4AFh] [rbp-F1h] BYREF
  std::string v103; // [rsp+4B0h] [rbp-F0h] BYREF
  char v104; // [rsp+4BFh] [rbp-E1h] BYREF
  std::string v105; // [rsp+4C0h] [rbp-E0h] BYREF
  char v106; // [rsp+4CFh] [rbp-D1h] BYREF
  std::string v107; // [rsp+4D0h] [rbp-D0h] BYREF
  char v108; // [rsp+4DFh] [rbp-C1h] BYREF
  std::string v109; // [rsp+4E0h] [rbp-C0h] BYREF
  char v110; // [rsp+4EFh] [rbp-B1h] BYREF
  std::vector<MemChrBag> v111; // [rsp+4F0h] [rbp-B0h] BYREF
  std::string v112; // [rsp+510h] [rbp-90h] BYREF
  char v113; // [rsp+51Fh] [rbp-81h] BYREF
  std::string v114; // [rsp+520h] [rbp-80h] BYREF
  char v115; // [rsp+52Fh] [rbp-71h] BYREF
  MemChrBagVector v116; // [rsp+530h] [rbp-70h] BYREF
  Answer::Inifile v117; // [rsp+550h] [rbp-50h] BYREF
  int32_t i_0; // [rsp+588h] [rbp-18h]
  int32_t i_1; // [rsp+58Ch] [rbp-14h]

  bzero(this->m_vStartDay, 0x14u);
  bzero(this->m_vEndDay, 0x14u);
  Answer::Inifile::Inifile(&ini);
  std::allocator<char>::allocator(&v22);
  std::string::string(&file, "./ServerConfig/Tables/ZongHeYunYingHD.cfg");
  Answer::Inifile::parse(&ini, &file);
  std::string::~string(&file);
  std::allocator<char>::~allocator(&v22);
  memset(szCol, 0, sizeof(szCol));
  std::allocator<char>::allocator(&v24);
  std::string::string(&key, "start_day");
  std::allocator<char>::allocator(&v26);
  std::string::string(&section, "CONFIG");
  this->m_nStartDay = Answer::Inifile::getIntValue(&ini, &section, &key);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v26);
  std::string::~string(&key);
  std::allocator<char>::~allocator(&v24);
  std::allocator<char>::allocator(&v28);
  std::string::string(&v27, "end_day");
  std::allocator<char>::allocator(&v30);
  std::string::string(&v29, "CONFIG");
  this->m_nEndDay = Answer::Inifile::getIntValue(&ini, &v29, &v27);
  std::string::~string(&v29);
  std::allocator<char>::~allocator(&v30);
  std::string::~string(&v27);
  std::allocator<char>::~allocator(&v28);
  std::allocator<char>::allocator(&v32);
  std::string::string(&v31, "icon");
  std::allocator<char>::allocator(&v34);
  std::string::string(&v33, "CONFIG");
  this->m_nIcon = Answer::Inifile::getIntValue(&ini, &v33, &v31);
  std::string::~string(&v33);
  std::allocator<char>::~allocator(&v34);
  std::string::~string(&v31);
  std::allocator<char>::~allocator(&v32);
  std::allocator<char>::allocator((char *)&v35.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::string::string(&v35.m_strMap._M_t._M_impl._M_header._M_parent, "open");
  std::allocator<char>::allocator((char *)&v35.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::string(&v35.m_strMap._M_t._M_impl._M_header._M_right, "CONFIG");
  Answer::Inifile::getStrValue(
    &v35,
    (const std::string *const)&ini,
    (const std::string *const)&v35.m_strMap._M_t._M_impl._M_header._M_right);
  CZongHeYunYingHD::initOpenList(this, (const std::string *const)&v35);
  std::string::~string(&v35);
  std::string::~string(&v35.m_strMap._M_t._M_impl._M_header._M_right);
  std::allocator<char>::~allocator((char *)&v35.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::~string(&v35.m_strMap._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v35.m_strMap._M_t._M_impl._M_header._M_left + 7);
  if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_DAILY) )
  {
    std::allocator<char>::allocator(&v36);
    std::string::string(&v35.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v38);
    std::string::string(&v37, "DAILY_RECHARGE");
    this->m_vStartDay[1] = Answer::Inifile::getIntValue(&ini, &v37, &v35.m_currentSection);
    std::string::~string(&v37);
    std::allocator<char>::~allocator(&v38);
    std::string::~string(&v35.m_currentSection);
    std::allocator<char>::~allocator(&v36);
    std::allocator<char>::allocator(&v40);
    std::string::string(&v39, "end_day");
    std::allocator<char>::allocator(&v42);
    std::string::string(&v41, "DAILY_RECHARGE");
    this->m_vEndDay[1] = Answer::Inifile::getIntValue(&ini, &v41, &v39);
    std::string::~string(&v41);
    std::allocator<char>::~allocator(&v42);
    std::string::~string(&v39);
    std::allocator<char>::~allocator(&v40);
    std::allocator<char>::allocator(&v44);
    std::string::string(&v43, "recharge_value");
    std::allocator<char>::allocator(&v46);
    std::string::string(&v45, "DAILY_RECHARGE");
    this->m_nRechargeDailyValue = Answer::Inifile::getIntValue(&ini, &v45, &v43);
    std::string::~string(&v45);
    std::allocator<char>::~allocator(&v46);
    std::string::~string(&v43);
    std::allocator<char>::~allocator(&v44);
    std::allocator<char>::allocator(&v48);
    std::string::string(&v47, "reward_limit");
    std::allocator<char>::allocator(&v50);
    std::string::string(&v49, "DAILY_RECHARGE");
    this->m_nRechargeDailyRewardLimit = Answer::Inifile::getIntValue(&ini, &v49, &v47);
    std::string::~string(&v49);
    std::allocator<char>::~allocator(&v50);
    std::string::~string(&v47);
    std::allocator<char>::~allocator(&v48);
    std::allocator<char>::allocator((char *)&v52.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(&v52.m_strMap._M_t._M_impl._M_header._M_parent, "reward");
    std::allocator<char>::allocator((char *)&v52.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(&v52.m_strMap._M_t._M_impl._M_header._M_right, "DAILY_RECHARGE");
    Answer::Inifile::getStrValue(
      &v52,
      (const std::string *const)&ini,
      (const std::string *const)&v52.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&__x, (const std::string *const)&v52);
    std::vector<MemChrBag>::operator=(&this->m_vRechargeDailyReward, &__x);
    std::vector<MemChrBag>::~vector(&__x);
    std::string::~string(&v52);
    std::string::~string(&v52.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v52.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v52.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v52.m_strMap._M_t._M_impl._M_header._M_left + 7);
  }
  if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_RANK_DAILY) )
  {
    std::allocator<char>::allocator(&v53);
    std::string::string(&v52.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v55);
    std::string::string(&v54, "RECHARGE_RANK_DAILY");
    this->m_vStartDay[2] = Answer::Inifile::getIntValue(&ini, &v54, &v52.m_currentSection);
    std::string::~string(&v54);
    std::allocator<char>::~allocator(&v55);
    std::string::~string(&v52.m_currentSection);
    std::allocator<char>::~allocator(&v53);
    std::allocator<char>::allocator(&v57);
    std::string::string(&v56, "end_day");
    std::allocator<char>::allocator(&v59);
    std::string::string(&v58, "RECHARGE_RANK_DAILY");
    this->m_vEndDay[2] = Answer::Inifile::getIntValue(&ini, &v58, &v56);
    std::string::~string(&v58);
    std::allocator<char>::~allocator(&v59);
    std::string::~string(&v56);
    std::allocator<char>::~allocator(&v57);
    std::allocator<char>::allocator(&v61);
    std::string::string(&v60, "area");
    std::allocator<char>::allocator(&v63);
    std::string::string(&v62, "RECHARGE_RANK_DAILY");
    this->m_nRechargeRankDailyArea = Answer::Inifile::getIntValue(&ini, &v62, &v60);
    std::string::~string(&v62);
    std::allocator<char>::~allocator(&v63);
    std::string::~string(&v60);
    std::allocator<char>::~allocator(&v61);
    std::allocator<char>::allocator(&v65);
    std::string::string(&v64, "size");
    std::allocator<char>::allocator(&v67);
    std::string::string(&v66, "RECHARGE_RANK_DAILY");
    this->m_nRechargeRankDailySize = Answer::Inifile::getIntValue(&ini, &v66, &v64);
    std::string::~string(&v66);
    std::allocator<char>::~allocator(&v67);
    std::string::~string(&v64);
    std::allocator<char>::~allocator(&v65);
    Param2::Param2(&v68, 0, 0);
    std::vector<Param2>::resize(&this->m_vRechargeRankDailyIndex, this->m_nRechargeRankDailyArea, v68);
    std::vector<MemChrBag>::vector(&p___x);
    std::vector<std::vector<MemChrBag>>::resize(
      &this->m_vRechargeRankDailyReward,
      this->m_nRechargeRankDailyArea,
      &p___x);
    std::vector<MemChrBag>::~vector(&p___x);
    std::vector<int>::resize(&this->m_vRechargeRankDailyMail, this->m_nRechargeRankDailyArea, 0);
    HIDWORD(v117.m_currentSection._M_dataplus._M_p) = 0;
    while ( this->m_nRechargeRankDailyArea > SHIDWORD(v117.m_currentSection._M_dataplus._M_p) )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "index_%d", HIDWORD(v117.m_currentSection._M_dataplus._M_p) + 1);
      std::allocator<char>::allocator(&v71);
      std::string::string(&delims, "-");
      std::allocator<char>::allocator((char *)&v72.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v72.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v72.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v72.m_strMap._M_t._M_impl._M_header._M_right, "RECHARGE_RANK_DAILY");
      Answer::Inifile::getStrValue(
        &v72,
        (const std::string *const)&ini,
        (const std::string *const)&v72.m_strMap._M_t._M_impl._M_header._M_right);
      Answer::StringUtility::split(&vIndex, (const std::string *const)&v72, &delims, 0);
      std::string::~string(&v72);
      std::string::~string(&v72.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v72.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v72.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v72.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::~string(&delims);
      std::allocator<char>::~allocator(&v71);
      if ( std::vector<std::string>::size(&vIndex) == 1 )
      {
        v1 = std::vector<Param2>::operator[](
               &this->m_vRechargeRankDailyIndex,
               SHIDWORD(v117.m_currentSection._M_dataplus._M_p));
        v2 = std::vector<std::string>::operator[](&vIndex, 0);
        v3 = (const char *)std::string::c_str(v2);
        v1->nParam1 = atoi(v3);
        v4 = std::vector<Param2>::operator[](
               &this->m_vRechargeRankDailyIndex,
               SHIDWORD(v117.m_currentSection._M_dataplus._M_p));
        v4->nParam2 = std::vector<Param2>::operator[](
                        &this->m_vRechargeRankDailyIndex,
                        SHIDWORD(v117.m_currentSection._M_dataplus._M_p))->nParam1;
      }
      else if ( std::vector<std::string>::size(&vIndex) == 2 )
      {
        v5 = std::vector<Param2>::operator[](
               &this->m_vRechargeRankDailyIndex,
               SHIDWORD(v117.m_currentSection._M_dataplus._M_p));
        v6 = std::vector<std::string>::operator[](&vIndex, 0);
        v7 = (const char *)std::string::c_str(v6);
        v5->nParam1 = atoi(v7);
        v8 = std::vector<Param2>::operator[](
               &this->m_vRechargeRankDailyIndex,
               SHIDWORD(v117.m_currentSection._M_dataplus._M_p));
        v9 = std::vector<std::string>::operator[](&vIndex, 1u);
        v10 = (const char *)std::string::c_str(v9);
        v8->nParam2 = atoi(v10);
      }
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward_%d", HIDWORD(v117.m_currentSection._M_dataplus._M_p) + 1);
      std::allocator<char>::allocator((char *)&v73.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v73.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v73.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v73.m_strMap._M_t._M_impl._M_header._M_right, "RECHARGE_RANK_DAILY");
      Answer::Inifile::getStrValue(
        &v73,
        (const std::string *const)&ini,
        (const std::string *const)&v73.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString((MemChrBagVector *)&v72.m_currentSection, (const std::string *const)&v73);
      v11 = std::vector<std::vector<MemChrBag>>::operator[](
              &this->m_vRechargeRankDailyReward,
              SHIDWORD(v117.m_currentSection._M_dataplus._M_p));
      std::vector<MemChrBag>::operator=(v11, (const std::vector<MemChrBag> *const)&v72.m_currentSection);
      std::vector<MemChrBag>::~vector((std::vector<MemChrBag> *const)&v72.m_currentSection);
      std::string::~string(&v73);
      std::string::~string(&v73.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v73.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v73.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v73.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail_%d", HIDWORD(v117.m_currentSection._M_dataplus._M_p) + 1);
      v12 = std::vector<int>::operator[](
              &this->m_vRechargeRankDailyMail,
              SHIDWORD(v117.m_currentSection._M_dataplus._M_p));
      std::allocator<char>::allocator(&v74);
      std::string::string(&v73.m_currentSection, szCol);
      std::allocator<char>::allocator(&v76);
      std::string::string(&v75, "RECHARGE_RANK_DAILY");
      *v12 = Answer::Inifile::getIntValue(&ini, &v75, &v73.m_currentSection);
      std::string::~string(&v75);
      std::allocator<char>::~allocator(&v76);
      std::string::~string(&v73.m_currentSection);
      std::allocator<char>::~allocator(&v74);
      std::vector<std::string>::~vector(&vIndex);
      ++HIDWORD(v117.m_currentSection._M_dataplus._M_p);
    }
  }
  if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY) )
  {
    std::allocator<char>::allocator(&v78);
    std::string::string(&v77, "start_day");
    std::allocator<char>::allocator(&v80);
    std::string::string(&v79, "RECHARGE_TEAM_SHOP_DAILY");
    this->m_vStartDay[3] = Answer::Inifile::getIntValue(&ini, &v79, &v77);
    std::string::~string(&v79);
    std::allocator<char>::~allocator(&v80);
    std::string::~string(&v77);
    std::allocator<char>::~allocator(&v78);
    std::allocator<char>::allocator(&v82);
    std::string::string(&v81, "end_day");
    std::allocator<char>::allocator(&v84);
    std::string::string(&v83, "RECHARGE_TEAM_SHOP_DAILY");
    this->m_vEndDay[3] = Answer::Inifile::getIntValue(&ini, &v83, &v81);
    std::string::~string(&v83);
    std::allocator<char>::~allocator(&v84);
    std::string::~string(&v81);
    std::allocator<char>::~allocator(&v82);
    std::allocator<char>::allocator(&v86);
    std::string::string(&v85, "size");
    std::allocator<char>::allocator(&v88);
    std::string::string(&v87, "RECHARGE_TEAM_SHOP_DAILY");
    this->m_nRechargeTeamShopDailySize = Answer::Inifile::getIntValue(&ini, &v87, &v85);
    std::string::~string(&v87);
    std::allocator<char>::~allocator(&v88);
    std::string::~string(&v85);
    std::allocator<char>::~allocator(&v86);
    std::vector<int>::resize(&this->m_vRechargeTeamShopDailyPlayer, this->m_nRechargeTeamShopDailySize, 0);
    std::vector<int>::resize(&this->m_vRechargeTeamShopDailyValue, this->m_nRechargeTeamShopDailySize, 0);
    std::vector<MemChrBag>::vector(&v89);
    std::vector<std::vector<MemChrBag>>::resize(
      &this->m_vRechargeTeamShopDailyReward,
      this->m_nRechargeTeamShopDailySize,
      &v89);
    std::vector<MemChrBag>::~vector(&v89);
    for ( i_0 = 0; this->m_nRechargeTeamShopDailySize > i_0; ++i_0 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "player_%d", i_0 + 1);
      v13 = std::vector<int>::operator[](&this->m_vRechargeTeamShopDailyPlayer, i_0);
      std::allocator<char>::allocator(&v91);
      std::string::string(&v90, szCol);
      std::allocator<char>::allocator(&v93);
      std::string::string(&v92, "RECHARGE_TEAM_SHOP_DAILY");
      *v13 = Answer::Inifile::getIntValue(&ini, &v92, &v90);
      std::string::~string(&v92);
      std::allocator<char>::~allocator(&v93);
      std::string::~string(&v90);
      std::allocator<char>::~allocator(&v91);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "recharge_%d", i_0 + 1);
      v14 = std::vector<int>::operator[](&this->m_vRechargeTeamShopDailyValue, i_0);
      std::allocator<char>::allocator(&v95);
      std::string::string(&v94, szCol);
      std::allocator<char>::allocator(&v97);
      std::string::string(&v96, "RECHARGE_TEAM_SHOP_DAILY");
      *v14 = Answer::Inifile::getIntValue(&ini, &v96, &v94);
      std::string::~string(&v96);
      std::allocator<char>::~allocator(&v97);
      std::string::~string(&v94);
      std::allocator<char>::~allocator(&v95);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward_%d", i_0 + 1);
      std::allocator<char>::allocator((char *)&v99.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v99.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v99.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v99.m_strMap._M_t._M_impl._M_header._M_right, "RECHARGE_TEAM_SHOP_DAILY");
      Answer::Inifile::getStrValue(
        &v99,
        (const std::string *const)&ini,
        (const std::string *const)&v99.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v98, (const std::string *const)&v99);
      v15 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeTeamShopDailyReward, i_0);
      std::vector<MemChrBag>::operator=(v15, &v98);
      std::vector<MemChrBag>::~vector(&v98);
      std::string::~string(&v99);
      std::string::~string(&v99.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v99.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v99.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v99.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_ONCE_SHOP) )
  {
    std::allocator<char>::allocator(&v100);
    std::string::string(&v99.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v102);
    std::string::string(&v101, "ONCE_SHOP");
    this->m_vStartDay[4] = Answer::Inifile::getIntValue(&ini, &v101, &v99.m_currentSection);
    std::string::~string(&v101);
    std::allocator<char>::~allocator(&v102);
    std::string::~string(&v99.m_currentSection);
    std::allocator<char>::~allocator(&v100);
    std::allocator<char>::allocator(&v104);
    std::string::string(&v103, "end_day");
    std::allocator<char>::allocator(&v106);
    std::string::string(&v105, "ONCE_SHOP");
    this->m_vEndDay[4] = Answer::Inifile::getIntValue(&ini, &v105, &v103);
    std::string::~string(&v105);
    std::allocator<char>::~allocator(&v106);
    std::string::~string(&v103);
    std::allocator<char>::~allocator(&v104);
    std::allocator<char>::allocator(&v108);
    std::string::string(&v107, "size");
    std::allocator<char>::allocator(&v110);
    std::string::string(&v109, "ONCE_SHOP");
    this->m_nOnceShopSize = Answer::Inifile::getIntValue(&ini, &v109, &v107);
    std::string::~string(&v109);
    std::allocator<char>::~allocator(&v110);
    std::string::~string(&v107);
    std::allocator<char>::~allocator(&v108);
    std::vector<int>::resize(&this->m_vOnceShopPrice, this->m_nOnceShopSize, 0);
    std::vector<MemChrBag>::vector(&v111);
    std::vector<std::vector<MemChrBag>>::resize(&this->m_vOnceShopItem, this->m_nOnceShopSize, &v111);
    std::vector<MemChrBag>::~vector(&v111);
    for ( i_1 = 0; this->m_nRechargeTeamShopDailySize > i_1; ++i_1 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price_%d", i_1 + 1);
      v16 = std::vector<int>::operator[](&this->m_vOnceShopPrice, i_1);
      std::allocator<char>::allocator(&v113);
      std::string::string(&v112, szCol);
      std::allocator<char>::allocator(&v115);
      std::string::string(&v114, "ONCE_SHOP");
      *v16 = Answer::Inifile::getIntValue(&ini, &v114, &v112);
      std::string::~string(&v114);
      std::allocator<char>::~allocator(&v115);
      std::string::~string(&v112);
      std::allocator<char>::~allocator(&v113);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "item_%d", i_1 + 1);
      std::allocator<char>::allocator((char *)&v117.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v117.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v117.m_currentSection._M_dataplus._M_p + 3);
      std::string::string(&v117.m_strMap._M_t._M_impl._M_header._M_right, "ONCE_SHOP");
      Answer::Inifile::getStrValue(
        &v117,
        (const std::string *const)&ini,
        (const std::string *const)&v117.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v116, (const std::string *const)&v117);
      v17 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vOnceShopItem, i_1);
      std::vector<MemChrBag>::operator=(v17, &v116);
      std::vector<MemChrBag>::~vector(&v116);
      std::string::~string(&v117);
      std::string::~string(&v117.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v117.m_currentSection._M_dataplus._M_p + 3);
      std::string::~string(&v117.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v117.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
  }
  Answer::Inifile::~Inifile(&ini);
}


#####################################
void __cdecl CZongHeYunYingHD::loadRankData(CZongHeYunYingHD *const this)
{
  int8_t m_nDay; // r12
  DBService *v2; // rax
  int32_t i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; i <= 4; ++i )
  {
    if ( this->m_vOpen[i] )
    {
      m_nDay = this->m_nDay;
      v2 = Answer::Singleton<DBService>::instance();
      DBService::LoadZHYYHDRank(v2, i, m_nDay);
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::GetIconState(
        CZongHeYunYingHD *const this,
        Player *player,
        IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CZongHeYunYingHD::needShowIcon(this) )
    {
      CZongHeYunYingHD::getIconState(&__x, this, player);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::SendIconState(CZongHeYunYingHD *const this, Player *player)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CZongHeYunYingHD::needShowIcon(this) )
    {
      CZongHeYunYingHD::getIconState(&icon, this, player);
      Player::SendIconState(player, &icon);
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::hideIcon(CZongHeYunYingHD *const this, int32_t nIconId)
{
  GameService *v2; // rax
  GameService *v3; // rax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 1 )
  {
    *(_DWORD *)&icon.nState = 4;
    *(_QWORD *)&icon.nLeftTime = 0;
    *(_QWORD *)&icon.nIconRight = 0;
    icon.nId = nIconId;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      ShowIcon::AppendInfo(&icon, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v5, 0, packet);
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::SendActivityInfo(CZongHeYunYingHD *const this, Player *player)
{
  int8_t v2; // bl
  GameService *v3; // rax
  int32_t TodayPayGold; // eax
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // eax
  size_t v7; // rbx
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  size_t v10; // rbx
  std::vector<FestivalRank> *v11; // rax
  FestivalRank *v12; // rax
  int32_t v13; // eax
  int8_t v14; // dl
  int32_t RechargePlayer; // eax
  CExtOperateLimit *v16; // rax
  int32_t v17; // eax
  CExtOperateLimit *v18; // rax
  int32_t v19; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v22; // bl
  GameService *v23; // rax
  Answer::MutexGuard lock; // [rsp+10h] [rbp-40h] BYREF
  int8_t connid; // [rsp+27h] [rbp-29h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]
  int8_t nCount; // [rsp+33h] [rbp-1Dh]
  uint32_t oldOffset; // [rsp+34h] [rbp-1Ch]
  uint32_t newOffset; // [rsp+38h] [rbp-18h]
  int32_t i; // [rsp+3Ch] [rbp-14h]

  if ( player )
  {
    connid = Player::getConnId(player);
    v2 = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, v2, Answer::PackType::PACK_DISPATCH, 0x2EB9u);
    if ( packet )
    {
      nCount = 0;
      oldOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt8(packet, 0);
      if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_DAILY) )
      {
        Answer::NetPacket::writeInt8(packet, 1);
        TodayPayGold = Player::GetTodayPayGold(player);
        Answer::NetPacket::writeInt32(packet, TodayPayGold);
        OperateLimit = Player::GetOperateLimit(player);
        LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1135);
        Answer::NetPacket::writeInt32(packet, LimitCount);
        ++nCount;
      }
      if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_RANK_DAILY) )
      {
        Answer::NetPacket::writeInt8(packet, 2);
        CZongHeYunYingHD::checkRankInvalid(this, connid, 2);
        Answer::NetPacket::writeInt32(packet, this->m_nRechargeRankDailySize);
        for ( i = 0; this->m_nRechargeRankDailySize > i; ++i )
        {
          Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
          v7 = i;
          v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeDailyRank, &connid);
          v9 = std::vector<FestivalRank>::operator[](v8, v7);
          Answer::NetPacket::writeUTF8(packet, &v9->strName);
          v10 = i;
          v11 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mRechargeDailyRank, &connid);
          v12 = std::vector<FestivalRank>::operator[](v11, v10);
          Answer::NetPacket::writeInt32(packet, v12->nScore);
          Answer::MutexGuard::~MutexGuard(&lock);
        }
        ++nCount;
      }
      if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY) )
      {
        Answer::NetPacket::writeInt8(packet, 3);
        v13 = Player::GetTodayPayGold(player);
        Answer::NetPacket::writeInt32(packet, v13);
        v14 = Player::getConnId(player);
        RechargePlayer = CZongHeYunYingHD::getRechargePlayer(this, v14);
        Answer::NetPacket::writeInt32(packet, RechargePlayer);
        v16 = Player::GetOperateLimit(player);
        v17 = CExtOperateLimit::GetLimitCount(v16, 1136);
        Answer::NetPacket::writeInt32(packet, v17);
        ++nCount;
      }
      if ( CZongHeYunYingHD::isOpen(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_ONCE_SHOP) )
      {
        Answer::NetPacket::writeInt8(packet, 4);
        v18 = Player::GetOperateLimit(player);
        v19 = CExtOperateLimit::GetLimitCount(v18, 1137);
        Answer::NetPacket::writeInt32(packet, v19);
        ++nCount;
      }
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt8(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v22 = Player::getConnId(player);
      v23 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v23, v22, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::OnRecharge(CZongHeYunYingHD *const this, Player *player, int32_t nValue)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  GameService *v5; // rax
  int8_t ConnId; // bl
  int8_t v7; // bl
  std::map<long int,int> *v8; // rax
  int *v9; // rbx
  int16_t m_nDay; // r12
  DBService *v11; // rax
  FestivalRank info; // [rsp+30h] [rbp-B0h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-80h] BYREF
  FestivalRankVector vUpdate; // [rsp+70h] [rbp-70h] BYREF
  _BYTE v15[16]; // [rsp+90h] [rbp-50h] BYREF
  __int64 Cid; // [rsp+A0h] [rbp-40h] BYREF
  char __k; // [rsp+AFh] [rbp-31h] BYREF
  _BYTE v18[23]; // [rsp+B0h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+C7h] [rbp-19h]
  int32_t nGetTimes; // [rsp+C8h] [rbp-18h]
  int32_t nTodayTimes; // [rsp+CCh] [rbp-14h]

  if ( player && CZongHeYunYingHD::IsInTime(this) )
  {
    bNeedSync = 0;
    if ( CZongHeYunYingHD::IsInTime(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_DAILY) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      nGetTimes = CExtOperateLimit::GetLimitCount(OperateLimit, 2069);
      nTodayTimes = Player::GetTodayPayGold(player) / this->m_nRechargeDailyValue;
      v4 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v4, 1135, nTodayTimes - nGetTimes);
      bNeedSync = 1;
    }
    if ( CZongHeYunYingHD::IsInTime(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_RANK_DAILY) )
    {
      FestivalRank::FestivalRank(&info);
      info.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v15);
      std::string::operator=(&info.strName, v15);
      std::string::~string(v15);
      info.nScore = Player::GetTodayPayGold(player);
      info.nTime = Unit::getNow(player);
      v5 = Answer::Singleton<GameService>::instance();
      if ( GameService::getLine(v5) == 1 )
      {
        ConnId = Player::getConnId(player);
        CZongHeYunYingHD::updateRankInfo(this, ConnId, 2, &info);
      }
      else
      {
        v7 = Player::getConnId(player);
        CZongHeYunYingHD::sendLineSocialPlayerInfo(this, v7, 2, &info);
      }
      FestivalRank::~FestivalRank(&info);
    }
    if ( CZongHeYunYingHD::IsInTime(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY) )
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
      Cid = Player::getCid(player);
      __k = Player::getConnId(player);
      v8 = std::map<signed char,std::map<long,int>>::operator[](&this->m_mRechargeDailyPlayer, &__k);
      v9 = std::map<long,int>::operator[](v8, &Cid);
      *v9 = Player::GetTodayPayGold(player);
      Answer::MutexGuard::~MutexGuard(&lock);
      std::vector<FestivalRank>::vector(&vUpdate);
      FestivalRank::FestivalRank(&info);
      info.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v18);
      std::string::operator=(&info.strName, v18);
      std::string::~string(v18);
      info.nScore = Player::GetTodayPayGold(player);
      info.nTime = Unit::getNow(player);
      std::vector<FestivalRank>::push_back(&vUpdate, &info);
      m_nDay = this->m_nDay;
      LOBYTE(v9) = Player::getConnId(player);
      v11 = Answer::Singleton<DBService>::instance();
      DBService::SaveZHYYHDRank(v11, (int8_t)v9, 3, m_nDay, &vUpdate);
      FestivalRank::~FestivalRank(&info);
      std::vector<FestivalRank>::~vector(&vUpdate);
    }
    if ( bNeedSync )
      CZongHeYunYingHD::SendIconState(this, player);
  }
}


#####################################
void __cdecl CZongHeYunYingHD::UpdatePlayerInfo(
        CZongHeYunYingHD *const this,
        int8_t connid,
        Answer::NetPacket *inPacket)
{
  FestivalRank info; // [rsp+20h] [rbp-50h] BYREF
  _BYTE v5[13]; // [rsp+50h] [rbp-20h] BYREF
  int8_t nType; // [rsp+5Dh] [rbp-13h]
  int16_t nDay; // [rsp+5Eh] [rbp-12h]

  if ( inPacket )
  {
    nType = Answer::NetPacket::readInt8(inPacket);
    nDay = Answer::NetPacket::readInt16(inPacket);
    FestivalRank::FestivalRank(&info);
    info.nCharId = Answer::NetPacket::readInt64(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v5, (bool)inPacket);
    std::string::operator=(&info.strName, v5);
    std::string::~string(v5);
    info.nScore = Answer::NetPacket::readInt32(inPacket);
    info.nTime = Answer::NetPacket::readInt32(inPacket);
    if ( nDay == this->m_nDay )
      CZongHeYunYingHD::updateRankInfo(this, connid, nType, &info);
    FestivalRank::~FestivalRank(&info);
  }
}


#####################################
void __cdecl CZongHeYunYingHD::sendLineSocialPlayerInfo(
        CZongHeYunYingHD *const this,
        int8_t connid,
        int8_t nType,
        const FestivalRank *const info)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, connid, Answer::PackType::PACK_DISPATCH, 0x4EC1u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 1);
    Answer::NetPacket::writeInt8(packet, nType);
    Answer::NetPacket::writeInt16(packet, this->m_nDay);
    Answer::NetPacket::writeInt64(packet, info->nCharId);
    Answer::NetPacket::writeUTF8(packet, &info->strName);
    Answer::NetPacket::writeInt32(packet, info->nScore);
    Answer::NetPacket::writeInt32(packet, info->nTime);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v6, connid, packet);
  }
}


#####################################
void __cdecl CZongHeYunYingHD::updateRankInfo(
        CZongHeYunYingHD *const this,
        int8_t connid,
        int8_t nType,
        const FestivalRank *const info)
{
  int v4; // ebx
  size_t v5; // rax
  int v6; // ebx
  FestivalRank *v7; // rbx
  FestivalRank *v8; // rax
  FestivalRank *v9; // rax
  FestivalRank *v10; // rax
  FestivalRank *v11; // rax
  FestivalRank *v12; // rax
  FestivalRank *v13; // rax
  int16_t m_nDay; // r13
  int8_t v15; // bl
  DBService *v16; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-BCh] BYREF
  CZongHeYunYingHD *thisa; // [rsp+18h] [rbp-B8h]
  Answer::MutexGuard lock_3; // [rsp+20h] [rbp-B0h] BYREF
  Answer::MutexGuard lock_2; // [rsp+30h] [rbp-A0h] BYREF
  Answer::MutexGuard lock_1; // [rsp+40h] [rbp-90h] BYREF
  Answer::MutexGuard lock_0; // [rsp+50h] [rbp-80h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-70h] BYREF
  FestivalRankVector vUpdate; // [rsp+70h] [rbp-60h] BYREF
  int32_t nRankSize; // [rsp+8Ch] [rbp-44h]
  FestivalRankVector *pRank; // [rsp+90h] [rbp-40h]
  FestivalRankVector *vRank; // [rsp+98h] [rbp-38h]
  int32_t nRankIndex; // [rsp+A4h] [rbp-2Ch]
  int16_t i; // [rsp+A8h] [rbp-28h]
  int16_t nOldIndex; // [rsp+AAh] [rbp-26h]
  int16_t i_0; // [rsp+ACh] [rbp-24h]
  int16_t i_1; // [rsp+AEh] [rbp-22h]

  thisa = this;
  connida[0] = connid;
  CZongHeYunYingHD::checkRankInvalid(this, connid, nType);
  nRankSize = 0;
  pRank = 0;
  if ( nType == 2 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    pRank = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeDailyRank, connida);
    nRankSize = thisa->m_nRechargeRankDailySize;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
  if ( pRank )
  {
    vRank = pRank;
    nRankIndex = -1;
    for ( i = 0; i < nRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &thisa->m_lock);
      if ( std::vector<FestivalRank>::operator[](vRank, i)->nScore >= info->nScore )
      {
        v4 = 1;
      }
      else
      {
        nRankIndex = i;
        v4 = 0;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v4 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      std::vector<FestivalRank>::vector(&vUpdate);
      v5 = std::vector<FestivalRank>::size(vRank);
      std::vector<FestivalRank>::reserve(&vUpdate, v5);
      nOldIndex = nRankSize - 1;
      for ( i_0 = 0; i_0 < nRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &thisa->m_lock);
        if ( std::vector<FestivalRank>::operator[](vRank, i_0)->nCharId == info->nCharId )
        {
          nOldIndex = i_0;
          v6 = 0;
        }
        else
        {
          v6 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v6 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &thisa->m_lock);
          v7 = std::vector<FestivalRank>::operator[](vRank, i_1 - 1);
          v8 = std::vector<FestivalRank>::operator[](vRank, i_1);
          FestivalRank::operator=(v8, v7);
          v9 = std::vector<FestivalRank>::operator[](vRank, i_1);
          v9->nIndex = i_1;
          v10 = std::vector<FestivalRank>::operator[](vRank, i_1);
          std::vector<FestivalRank>::push_back(&vUpdate, v10);
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock_3, &thisa->m_lock);
      v11 = std::vector<FestivalRank>::operator[](vRank, nRankIndex);
      FestivalRank::operator=(v11, info);
      v12 = std::vector<FestivalRank>::operator[](vRank, nRankIndex);
      v12->nIndex = nRankIndex;
      v13 = std::vector<FestivalRank>::operator[](vRank, nRankIndex);
      std::vector<FestivalRank>::push_back(&vUpdate, v13);
      Answer::MutexGuard::~MutexGuard(&lock_3);
      m_nDay = thisa->m_nDay;
      v15 = connida[0];
      v16 = Answer::Singleton<DBService>::instance();
      DBService::SaveZHYYHDRank(v16, v15, nType, m_nDay, &vUpdate);
      std::vector<FestivalRank>::~vector(&vUpdate);
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::UpdateRankInfo(
        CZongHeYunYingHD *const this,
        int8_t connid,
        int8_t nType,
        int32_t nDay,
        const FestivalRankVector *const vUpdateRank)
{
  CharId_t *p_nCharId; // rbx
  std::map<long int,int> *v6; // rax
  int *v7; // rbx
  const FestivalRank *v8; // rbx
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-ACh] BYREF
  CZongHeYunYingHD *thisa; // [rsp+18h] [rbp-A8h]
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<const FestivalRank*,std::vector<FestivalRank> > iter_0; // [rsp+30h] [rbp-90h] BYREF
  Answer::MutexGuard lock_0; // [rsp+40h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<const FestivalRank*,std::vector<FestivalRank> > iter; // [rsp+50h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const FestivalRank*,std::vector<FestivalRank> > __rhs; // [rsp+70h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const FestivalRank*,std::vector<FestivalRank> > v20; // [rsp+80h] [rbp-40h] BYREF
  int32_t nRankSize; // [rsp+94h] [rbp-2Ch]
  FestivalRankVector *pRank; // [rsp+98h] [rbp-28h]
  FestivalRankVector *vRank; // [rsp+A0h] [rbp-20h]
  int16_t nIndex; // [rsp+AEh] [rbp-12h]

  thisa = this;
  connida[0] = connid;
  CZongHeYunYingHD::checkRankInvalid(this, connid, nType);
  nRankSize = 0;
  pRank = 0;
  if ( nType == 2 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    pRank = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeDailyRank, connida);
    nRankSize = thisa->m_nRechargeRankDailySize;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
  else if ( nType == 3 )
  {
    for ( iter._M_current = std::vector<FestivalRank>::begin(vUpdateRank)._M_current;
          ;
          __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<FestivalRank>::end(vUpdateRank)._M_current;
      if ( !__gnu_cxx::operator!=<FestivalRank const*,std::vector<FestivalRank>>(&iter, &__rhs) )
        break;
      Answer::MutexGuard::MutexGuard(&lock_0, &thisa->m_lock);
      p_nCharId = &__gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator->(&iter)->nCharId;
      v6 = std::map<signed char,std::map<long,int>>::operator[](&thisa->m_mRechargeDailyPlayer, connida);
      v7 = std::map<long,int>::operator[](v6, p_nCharId);
      *v7 = __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator->(&iter)->nScore;
      Answer::MutexGuard::~MutexGuard(&lock_0);
    }
  }
  if ( pRank )
  {
    vRank = pRank;
    for ( iter_0._M_current = std::vector<FestivalRank>::begin(vUpdateRank)._M_current;
          ;
          __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator++(&iter_0) )
    {
      v20._M_current = std::vector<FestivalRank>::end(vUpdateRank)._M_current;
      if ( !__gnu_cxx::operator!=<FestivalRank const*,std::vector<FestivalRank>>(&iter_0, &v20) )
        break;
      nIndex = __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator->(&iter_0)->nIndex;
      if ( nIndex >= 0 && nIndex < nRankSize )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &thisa->m_lock);
        v8 = __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator*(&iter_0);
        v9 = std::vector<FestivalRank>::operator[](vRank, nIndex);
        FestivalRank::operator=(v9, v8);
        Answer::MutexGuard::~MutexGuard(&lock_1);
      }
    }
  }
}


#####################################
void __cdecl CZongHeYunYingHD::checkRankInvalid(CZongHeYunYingHD *const this, int8_t connid, int8_t nType)
{
  std::vector<FestivalRank> *v3; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CZongHeYunYingHD *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  if ( nType == 2 )
  {
    iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&thisa->m_mRechargeDailyRank, connida)._M_node;
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mRechargeDailyRank)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
    {
      std::vector<FestivalRank>::vector(&vRank);
      FestivalRank::FestivalRank(&p___x);
      std::vector<FestivalRank>::resize(&vRank, thisa->m_nRechargeRankDailySize, &p___x);
      FestivalRank::~FestivalRank(&p___x);
      v3 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeDailyRank, connida);
      std::vector<FestivalRank>::operator=(v3, &vRank);
      std::vector<FestivalRank>::~vector(&vRank);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
int32_t __cdecl CZongHeYunYingHD::GetRechargeDailyReward(CZongHeYunYingHD *const this, Player *player)
{
  int32_t v2; // ebx
  CExtOperateLimit *OperateLimit; // rax
  MemChrBag *v4; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v6; // rax
  CExtOperateLimit *v7; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+20h] [rbp-50h] BYREF
  MemChrBagVector vItem; // [rsp+30h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+50h] [rbp-20h] BYREF
  int32_t nLeftTimes; // [rsp+58h] [rbp-18h]
  int32_t nTodayTimes; // [rsp+5Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CZongHeYunYingHD::IsInTime(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_DAILY) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nLeftTimes = CExtOperateLimit::GetLimitCount(OperateLimit, 1135);
  std::vector<MemChrBag>::vector(&vItem, &this->m_vRechargeDailyReward);
  for ( iter._M_current = std::vector<MemChrBag>::begin(&vItem)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(&vItem)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
      break;
    v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter);
    v4->itemCount *= nLeftTimes;
  }
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &vItem, ITEM_CHANGE_REASON::ICR_ZHYYHD_RECHARGE_DAILY_REWARD) )
  {
    v2 = 10002;
  }
  else
  {
    nTodayTimes = Player::GetTodayPayGold(player) / this->m_nRechargeDailyValue;
    v6 = Player::GetOperateLimit(player);
    CExtOperateLimit::UpdateLimitCount(v6, 2069, nTodayTimes);
    v7 = Player::GetOperateLimit(player);
    CExtOperateLimit::Reset(v7, 1135);
    CZongHeYunYingHD::SendIconState(this, player);
    v2 = 0;
  }
  std::vector<MemChrBag>::~vector(&vItem);
  return v2;
}


#####################################
int32_t __cdecl CZongHeYunYingHD::GetRechargeTeamShopDailyReward(
        CZongHeYunYingHD *const this,
        Player *player,
        int32_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int8_t ConnId; // dl
  int32_t RechargePlayer; // ebx
  int32_t TodayPayGold; // ebx
  std::vector<MemChrBag> *v8; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v10; // rax
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CZongHeYunYingHD::IsInTime(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY) )
    return 10002;
  if ( nIndex < 0 || this->m_nRechargeTeamShopDailySize <= nIndex )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1136);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  ConnId = Player::getConnId(player);
  RechargePlayer = CZongHeYunYingHD::getRechargePlayer(this, ConnId);
  if ( RechargePlayer < *std::vector<int>::operator[](&this->m_vRechargeTeamShopDailyPlayer, nIndex) )
    return 10002;
  TodayPayGold = Player::GetTodayPayGold(player);
  if ( TodayPayGold < *std::vector<int>::operator[](&this->m_vRechargeTeamShopDailyValue, nIndex) )
    return 10002;
  v8 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeTeamShopDailyReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v8, ITEM_CHANGE_REASON::ICR_ZHYYHD_RECHARGE_TEAM_SHOP_REWARD) )
    return 10002;
  v10 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v10, 1136, nNewRecord);
  CZongHeYunYingHD::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CZongHeYunYingHD::BuyOnceShopItem(CZongHeYunYingHD *const this, Player *player, int32_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int64_t Currency; // rbx
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  int64_t v8; // rdx
  CExtOperateLimit *v9; // rax
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CZongHeYunYingHD::IsInTime(this, ZONG_HE_YUN_YING_HD_TYPE::ZHYYHDT_ONCE_SHOP) )
    return 10002;
  if ( nIndex < 0 || this->m_nOnceShopSize <= nIndex )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1137);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
  if ( Currency < *std::vector<int>::operator[](&this->m_vOnceShopPrice, nIndex) )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vOnceShopItem, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_ZHYYHD_ONCE_SHOP_ITEM) )
    return 10002;
  v8 = *std::vector<int>::operator[](&this->m_vOnceShopPrice, nIndex);
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          v8,
          CURRENCY_CHANGE_REASON::GCR_ZHYYHD_BUY_ONCE_SHOP_ITEM,
          nIndex) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1137, nNewRecord);
  return 0;
}


#####################################
bool __cdecl CZongHeYunYingHD::IsInTime(CZongHeYunYingHD *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
bool __cdecl CZongHeYunYingHD::needShowIcon(CZongHeYunYingHD *const this)
{
  return this->m_nDay >= this->m_nStartDay && this->m_nDay < this->m_nEndDay;
}


#####################################
bool __cdecl CZongHeYunYingHD::IsInTime(CZongHeYunYingHD *const this, ZONG_HE_YUN_YING_HD_TYPE nType)
{
  return CZongHeYunYingHD::IsOpen(this, nType)
      && this->m_nDay >= this->m_vStartDay[nType]
      && this->m_nDay < this->m_vEndDay[nType];
}


#####################################
bool __cdecl CZongHeYunYingHD::IsOpen(CZongHeYunYingHD *const this, ZONG_HE_YUN_YING_HD_TYPE nType)
{
  return CZongHeYunYingHD::IsInTime(this) && CZongHeYunYingHD::isOpen(this, nType);
}


#####################################
int32_t __cdecl CZongHeYunYingHD::getLeftTime(CZongHeYunYingHD *const this)
{
  CTimer *v2; // rax
  int nNowTime; // [rsp+18h] [rbp-8h]

  if ( !CZongHeYunYingHD::IsInTime(this) )
    return 0;
  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  return 86400 * (this->m_nEndDay - this->m_nDay) - (nNowTime - Answer::DayTime::dayzero(nNowTime));
}


#####################################
void __cdecl CZongHeYunYingHD::sendRechargeDailyRankReward(CZongHeYunYingHD *const this)
{
  GameService *v1; // rax
  int32_t nIndex; // ebx
  int32_t v3; // ebx
  std::vector<MemChrBag> *v5; // r14
  int32_t v6; // r13d
  CharId_t nCharId; // r12
  int8_t v8; // bl
  DBService *v9; // rax
  __gnu_cxx::__normal_iterator<const FestivalRank*,std::vector<FestivalRank> > iter; // [rsp+20h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > map_iter; // [rsp+30h] [rbp-90h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<FestivalRank*,std::vector<FestivalRank> > __i; // [rsp+60h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<FestivalRank*,std::vector<FestivalRank> > __rhs; // [rsp+70h] [rbp-50h] BYREF
  std::string Param; // [rsp+80h] [rbp-40h] BYREF
  char v17; // [rsp+8Fh] [rbp-31h] BYREF
  int32_t i; // [rsp+90h] [rbp-30h]
  int8_t connid; // [rsp+97h] [rbp-29h]
  FestivalRankVector *vRank; // [rsp+98h] [rbp-28h]

  if ( !std::map<signed char,std::vector<FestivalRank>>::empty(&this->m_mRechargeDailyRank) )
  {
    v1 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v1) == 1 )
    {
      for ( i = 0; this->m_nRechargeRankDailyArea > i; ++i )
      {
        Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
        for ( map_iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&this->m_mRechargeDailyRank)._M_node;
              ;
              std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&map_iter) )
        {
          __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&this->m_mRechargeDailyRank)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(
                  &map_iter,
                  &__x) )
            break;
          connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&map_iter)->first;
          vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&map_iter)->second;
          __i._M_current = std::vector<FestivalRank>::begin(vRank)._M_current;
          __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::__normal_iterator<FestivalRank*>(
            &iter,
            &__i);
          while ( 1 )
          {
            __rhs._M_current = std::vector<FestivalRank>::end(vRank)._M_current;
            if ( !__gnu_cxx::operator!=<FestivalRank const*,FestivalRank*,std::vector<FestivalRank>>(&iter, &__rhs) )
              break;
            if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
            {
              nIndex = __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator->(&iter)->nIndex;
              if ( nIndex >= std::vector<Param2>::operator[](&this->m_vRechargeRankDailyIndex, i)->nParam1 )
              {
                v3 = __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator->(&iter)->nIndex;
                if ( v3 <= std::vector<Param2>::operator[](&this->m_vRechargeRankDailyIndex, i)->nParam2 )
                {
                  std::allocator<char>::allocator(&v17);
                  std::string::string(&Param, &unk_8F6500);
                  v5 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeRankDailyReward, i);
                  v6 = *std::vector<int>::operator[](&this->m_vRechargeRankDailyMail, i);
                  nCharId = __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator->(&iter)->nCharId;
                  v8 = connid;
                  v9 = Answer::Singleton<DBService>::instance();
                  DBService::OnSendSysMail(
                    v9,
                    v8,
                    nCharId,
                    v6,
                    v5,
                    ITEM_CHANGE_REASON::ICR_ZHYYHD_RECHARGE_RANK_DAILY_REWARD,
                    &Param,
                    0);
                  std::string::~string(&Param);
                  std::allocator<char>::~allocator(&v17);
                }
              }
            }
            __gnu_cxx::__normal_iterator<FestivalRank const*,std::vector<FestivalRank>>::operator++(&iter);
          }
        }
        Answer::MutexGuard::~MutexGuard(&lock);
      }
    }
  }
}


#####################################
int32_t __cdecl CZongHeYunYingHD::getRechargePlayer(CZongHeYunYingHD *const this, int8_t connid)
{
  std::map<long int,int> *v2; // rax
  int32_t v3; // ebx
  int8_t connida[4]; // [rsp+4h] [rbp-2Ch] BYREF
  CZongHeYunYingHD *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  v2 = std::map<signed char,std::map<long,int>>::operator[](&this->m_mRechargeDailyPlayer, connida);
  v3 = std::map<long,int>::size(v2);
  Answer::MutexGuard::~MutexGuard(&lock);
  return v3;
}


