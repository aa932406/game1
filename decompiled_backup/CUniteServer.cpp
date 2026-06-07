// Decompiled methods for class: CUniteServer
// Source: gameserver.cc
// Total methods: 41

#####################################
void __cdecl CUniteServer::OnDaySwitch(CUniteServer *const this)
{
  GameService *v1; // rax
  CfgData *v2; // rax
  CfgData *v3; // rax
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::isUniteServer(v2) )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      this->m_nDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_UNITE);
      if ( this->m_nDay == this->m_nEndDay )
      {
        v4 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
        if ( packet )
        {
          Answer::NetPacket::writeInt32(packet, this->m_nIcon);
          Answer::NetPacket::writeInt8(packet, 4);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt8(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt8(packet, 0);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v6 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v6, 0, packet);
        }
      }
    }
  }
}


#####################################
void __cdecl CUniteServer::OnNewMinute(CUniteServer *const this, int32_t nMinute)
{
  GameService *v2; // rax
  CfgData *v3; // rax

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::isUniteServer(v3) )
    {
      this->m_nMinute = nMinute;
      CUniteServer::checkSpiderQueen(this);
      CUniteServer::checkMysteryShopRefreshBroad(this);
    }
  }
}


#####################################
int32_t __cdecl CUniteServer::GetEndCollectDropTime(CUniteServer *const this)
{
  CfgData *v2; // rax

  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_COLLECT_DROP) )
    return 0;
  v2 = Answer::Singleton<CfgData>::instance();
  return 86400 * this->m_vEndDay[7] + CfgData::getServerStartDayZeroTime(v2, SERVER_TYPE::SVT_UNITE) - 1;
}


#####################################
bool __cdecl CUniteServer::RefreshMysteryShopItem(CUniteServer *const this, Player *player)
{
  return player
      && Player::DecCurrency(
           player,
           CURRENCY_TYPE::CURRENCY_GOLD,
           this->m_sMysteryShopRefreshCost,
           CURRENCY_CHANGE_REASON::GCR_MYSTERY_SHOP_REFRESH,
           0);
}


#####################################
void __cdecl CUniteServer::Init(CUniteServer *const this, int32_t line)
{
  CfgData *v2; // rax
  CfgData *v3; // rax
  CTimer *v4; // rax
  CUniteServer *v5; // rbx
  int v6; // eax
  int v7; // eax
  int32_t v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  MemChrBag v13; // [rsp+0h] [rbp-950h] BYREF
  int32_t linea; // [rsp+24h] [rbp-92Ch]
  CUniteServer *thisa; // [rsp+28h] [rbp-928h]
  char szCol[64]; // [rsp+30h] [rbp-920h] BYREF
  Answer::Inifile ini; // [rsp+70h] [rbp-8E0h] BYREF
  tm nowTime; // [rsp+B0h] [rbp-8A0h] BYREF
  LianRechargeCfg stu; // [rsp+F0h] [rbp-860h] BYREF
  TimeArea tarea; // [rsp+110h] [rbp-840h] BYREF
  std::string file; // [rsp+120h] [rbp-830h] BYREF
  char v22; // [rsp+12Fh] [rbp-821h] BYREF
  std::string key; // [rsp+130h] [rbp-820h] BYREF
  char v24; // [rsp+13Fh] [rbp-811h] BYREF
  std::string section; // [rsp+140h] [rbp-810h] BYREF
  char v26; // [rsp+14Fh] [rbp-801h] BYREF
  std::string v27; // [rsp+150h] [rbp-800h] BYREF
  char v28; // [rsp+15Fh] [rbp-7F1h] BYREF
  std::string v29; // [rsp+160h] [rbp-7F0h] BYREF
  char v30; // [rsp+16Fh] [rbp-7E1h] BYREF
  std::string v31; // [rsp+170h] [rbp-7E0h] BYREF
  char v32; // [rsp+17Fh] [rbp-7D1h] BYREF
  std::string v33; // [rsp+180h] [rbp-7D0h] BYREF
  char v34; // [rsp+18Fh] [rbp-7C1h] BYREF
  std::string v35; // [rsp+190h] [rbp-7C0h] BYREF
  char v36; // [rsp+19Fh] [rbp-7B1h] BYREF
  std::string v37; // [rsp+1A0h] [rbp-7B0h] BYREF
  char v38; // [rsp+1AFh] [rbp-7A1h] BYREF
  std::string v39; // [rsp+1B0h] [rbp-7A0h] BYREF
  char v40; // [rsp+1BFh] [rbp-791h] BYREF
  std::string v41; // [rsp+1C0h] [rbp-790h] BYREF
  char v42; // [rsp+1CFh] [rbp-781h] BYREF
  std::string v43; // [rsp+1D0h] [rbp-780h] BYREF
  char v44; // [rsp+1DFh] [rbp-771h] BYREF
  std::string v45; // [rsp+1E0h] [rbp-770h] BYREF
  char v46; // [rsp+1EBh] [rbp-765h] BYREF
  int __x; // [rsp+1ECh] [rbp-764h] BYREF
  std::string v48; // [rsp+1F0h] [rbp-760h] BYREF
  char v49; // [rsp+1FFh] [rbp-751h] BYREF
  std::string v50; // [rsp+200h] [rbp-750h] BYREF
  char v51; // [rsp+20Fh] [rbp-741h] BYREF
  MemChrBagVector v52; // [rsp+210h] [rbp-740h] BYREF
  Answer::Inifile v53; // [rsp+230h] [rbp-720h] BYREF
  char v54; // [rsp+26Fh] [rbp-6E1h] BYREF
  std::string v55; // [rsp+270h] [rbp-6E0h] BYREF
  char v56; // [rsp+27Fh] [rbp-6D1h] BYREF
  std::string v57; // [rsp+280h] [rbp-6D0h] BYREF
  char v58; // [rsp+28Fh] [rbp-6C1h] BYREF
  std::string v59; // [rsp+290h] [rbp-6C0h] BYREF
  char v60; // [rsp+29Fh] [rbp-6B1h] BYREF
  std::string v61; // [rsp+2A0h] [rbp-6B0h] BYREF
  char v62; // [rsp+2AFh] [rbp-6A1h] BYREF
  std::string v63; // [rsp+2B0h] [rbp-6A0h] BYREF
  char v64; // [rsp+2BBh] [rbp-695h] BYREF
  int IntValue; // [rsp+2BCh] [rbp-694h] BYREF
  std::string v66; // [rsp+2C0h] [rbp-690h] BYREF
  char v67; // [rsp+2CFh] [rbp-681h] BYREF
  std::string v68; // [rsp+2D0h] [rbp-680h] BYREF
  char v69; // [rsp+2DFh] [rbp-671h] BYREF
  MemChrBagVector v70; // [rsp+2E0h] [rbp-670h] BYREF
  Answer::Inifile v71; // [rsp+300h] [rbp-650h] BYREF
  char v72; // [rsp+33Fh] [rbp-611h] BYREF
  std::string v73; // [rsp+340h] [rbp-610h] BYREF
  char v74; // [rsp+34Fh] [rbp-601h] BYREF
  std::string v75; // [rsp+350h] [rbp-600h] BYREF
  char v76; // [rsp+35Fh] [rbp-5F1h] BYREF
  std::string v77; // [rsp+360h] [rbp-5F0h] BYREF
  char v78; // [rsp+36Fh] [rbp-5E1h] BYREF
  std::string v79; // [rsp+370h] [rbp-5E0h] BYREF
  char v80; // [rsp+37Fh] [rbp-5D1h] BYREF
  std::string v81; // [rsp+380h] [rbp-5D0h] BYREF
  char v82; // [rsp+38Bh] [rbp-5C5h] BYREF
  int v83; // [rsp+38Ch] [rbp-5C4h] BYREF
  std::string v84; // [rsp+390h] [rbp-5C0h] BYREF
  char v85; // [rsp+39Fh] [rbp-5B1h] BYREF
  std::string v86; // [rsp+3A0h] [rbp-5B0h] BYREF
  char v87; // [rsp+3AFh] [rbp-5A1h] BYREF
  std::string v88; // [rsp+3B0h] [rbp-5A0h] BYREF
  char v89; // [rsp+3BFh] [rbp-591h] BYREF
  std::string v90; // [rsp+3C0h] [rbp-590h] BYREF
  char v91; // [rsp+3CFh] [rbp-581h] BYREF
  std::string v92; // [rsp+3D0h] [rbp-580h] BYREF
  char v93; // [rsp+3DFh] [rbp-571h] BYREF
  std::string v94; // [rsp+3E0h] [rbp-570h] BYREF
  char v95; // [rsp+3EFh] [rbp-561h] BYREF
  std::string v96; // [rsp+3F0h] [rbp-560h] BYREF
  char v97; // [rsp+3FFh] [rbp-551h] BYREF
  std::string v98; // [rsp+400h] [rbp-550h] BYREF
  char v99; // [rsp+40Fh] [rbp-541h] BYREF
  std::string v100; // [rsp+410h] [rbp-540h] BYREF
  char v101; // [rsp+41Fh] [rbp-531h] BYREF
  std::string v102; // [rsp+420h] [rbp-530h] BYREF
  char v103; // [rsp+42Fh] [rbp-521h] BYREF
  std::string v104; // [rsp+430h] [rbp-520h] BYREF
  char v105; // [rsp+43Fh] [rbp-511h] BYREF
  std::string v106; // [rsp+440h] [rbp-510h] BYREF
  char v107; // [rsp+44Fh] [rbp-501h] BYREF
  std::string v108; // [rsp+450h] [rbp-500h] BYREF
  char v109; // [rsp+45Fh] [rbp-4F1h] BYREF
  std::string v110; // [rsp+460h] [rbp-4F0h] BYREF
  char v111; // [rsp+46Fh] [rbp-4E1h] BYREF
  std::string v112; // [rsp+470h] [rbp-4E0h] BYREF
  char v113; // [rsp+47Fh] [rbp-4D1h] BYREF
  std::string v114; // [rsp+480h] [rbp-4D0h] BYREF
  char v115; // [rsp+48Fh] [rbp-4C1h] BYREF
  std::string v116; // [rsp+490h] [rbp-4C0h] BYREF
  char v117; // [rsp+49Fh] [rbp-4B1h] BYREF
  std::string v118; // [rsp+4A0h] [rbp-4B0h] BYREF
  char v119; // [rsp+4AFh] [rbp-4A1h] BYREF
  std::string v120; // [rsp+4B0h] [rbp-4A0h] BYREF
  char v121; // [rsp+4BFh] [rbp-491h] BYREF
  std::string v122; // [rsp+4C0h] [rbp-490h] BYREF
  char v123; // [rsp+4CFh] [rbp-481h] BYREF
  std::string v124; // [rsp+4D0h] [rbp-480h] BYREF
  char v125; // [rsp+4DFh] [rbp-471h] BYREF
  std::string v126; // [rsp+4E0h] [rbp-470h] BYREF
  char v127; // [rsp+4EFh] [rbp-461h] BYREF
  std::string v128; // [rsp+4F0h] [rbp-460h] BYREF
  char v129; // [rsp+4FFh] [rbp-451h] BYREF
  std::string v130; // [rsp+500h] [rbp-450h] BYREF
  char v131; // [rsp+50Fh] [rbp-441h] BYREF
  std::string v132; // [rsp+510h] [rbp-440h] BYREF
  char v133; // [rsp+51Fh] [rbp-431h] BYREF
  std::string v134; // [rsp+520h] [rbp-430h] BYREF
  char v135; // [rsp+52Fh] [rbp-421h] BYREF
  std::string v136; // [rsp+530h] [rbp-420h] BYREF
  char v137; // [rsp+53Fh] [rbp-411h] BYREF
  std::string v138; // [rsp+540h] [rbp-410h] BYREF
  char v139; // [rsp+54Fh] [rbp-401h] BYREF
  std::string v140; // [rsp+550h] [rbp-400h] BYREF
  char v141; // [rsp+55Fh] [rbp-3F1h] BYREF
  std::string v142; // [rsp+560h] [rbp-3F0h] BYREF
  char v143; // [rsp+56Fh] [rbp-3E1h] BYREF
  std::string v144; // [rsp+570h] [rbp-3E0h] BYREF
  char v145; // [rsp+57Fh] [rbp-3D1h] BYREF
  std::string v146; // [rsp+580h] [rbp-3D0h] BYREF
  char v147; // [rsp+58Fh] [rbp-3C1h] BYREF
  std::string v148; // [rsp+590h] [rbp-3C0h] BYREF
  char v149; // [rsp+59Fh] [rbp-3B1h] BYREF
  std::string v150; // [rsp+5A0h] [rbp-3B0h] BYREF
  char v151; // [rsp+5AFh] [rbp-3A1h] BYREF
  std::string v152; // [rsp+5B0h] [rbp-3A0h] BYREF
  char v153; // [rsp+5BFh] [rbp-391h] BYREF
  std::string v154; // [rsp+5C0h] [rbp-390h] BYREF
  char v155; // [rsp+5CFh] [rbp-381h] BYREF
  std::string v156; // [rsp+5D0h] [rbp-380h] BYREF
  char v157; // [rsp+5DFh] [rbp-371h] BYREF
  std::string v158; // [rsp+5E0h] [rbp-370h] BYREF
  char v159; // [rsp+5EFh] [rbp-361h] BYREF
  std::string v160; // [rsp+5F0h] [rbp-360h] BYREF
  char v161; // [rsp+5FFh] [rbp-351h] BYREF
  std::string v162; // [rsp+600h] [rbp-350h] BYREF
  char v163; // [rsp+60Fh] [rbp-341h] BYREF
  std::string v164; // [rsp+610h] [rbp-340h] BYREF
  char v165; // [rsp+61Fh] [rbp-331h] BYREF
  std::string v166; // [rsp+620h] [rbp-330h] BYREF
  char v167; // [rsp+62Fh] [rbp-321h] BYREF
  std::string v168; // [rsp+630h] [rbp-320h] BYREF
  char v169; // [rsp+63Fh] [rbp-311h] BYREF
  std::string v170; // [rsp+640h] [rbp-310h] BYREF
  char v171; // [rsp+64Fh] [rbp-301h] BYREF
  std::string v172; // [rsp+650h] [rbp-300h] BYREF
  char v173; // [rsp+65Fh] [rbp-2F1h] BYREF
  std::string v174; // [rsp+660h] [rbp-2F0h] BYREF
  char v175; // [rsp+66Fh] [rbp-2E1h] BYREF
  std::string v176; // [rsp+670h] [rbp-2E0h] BYREF
  char v177; // [rsp+67Fh] [rbp-2D1h] BYREF
  std::string v178; // [rsp+680h] [rbp-2D0h] BYREF
  char v179; // [rsp+68Fh] [rbp-2C1h] BYREF
  std::string v180; // [rsp+690h] [rbp-2C0h] BYREF
  char v181; // [rsp+69Fh] [rbp-2B1h] BYREF
  std::string v182; // [rsp+6A0h] [rbp-2B0h] BYREF
  char v183; // [rsp+6AFh] [rbp-2A1h] BYREF
  std::string v184; // [rsp+6B0h] [rbp-2A0h] BYREF
  char v185; // [rsp+6BFh] [rbp-291h] BYREF
  std::string v186; // [rsp+6C0h] [rbp-290h] BYREF
  char v187; // [rsp+6CFh] [rbp-281h] BYREF
  std::string v188; // [rsp+6D0h] [rbp-280h] BYREF
  char v189; // [rsp+6DFh] [rbp-271h] BYREF
  std::string v190; // [rsp+6E0h] [rbp-270h] BYREF
  char v191; // [rsp+6EFh] [rbp-261h] BYREF
  std::string v192; // [rsp+6F0h] [rbp-260h] BYREF
  char v193; // [rsp+6FFh] [rbp-251h] BYREF
  std::string v194; // [rsp+700h] [rbp-250h] BYREF
  char v195; // [rsp+70Fh] [rbp-241h] BYREF
  std::string v196; // [rsp+710h] [rbp-240h] BYREF
  char v197; // [rsp+71Fh] [rbp-231h] BYREF
  std::string v198; // [rsp+720h] [rbp-230h] BYREF
  char v199; // [rsp+72Fh] [rbp-221h] BYREF
  Answer::Inifile v200; // [rsp+730h] [rbp-220h] BYREF
  char v201; // [rsp+76Fh] [rbp-1E1h] BYREF
  std::string v202; // [rsp+770h] [rbp-1E0h] BYREF
  char v203; // [rsp+77Fh] [rbp-1D1h] BYREF
  std::string v204; // [rsp+780h] [rbp-1D0h] BYREF
  char v205; // [rsp+78Fh] [rbp-1C1h] BYREF
  std::string v206; // [rsp+790h] [rbp-1C0h] BYREF
  char v207; // [rsp+79Fh] [rbp-1B1h] BYREF
  std::string v208; // [rsp+7A0h] [rbp-1B0h] BYREF
  char v209; // [rsp+7AFh] [rbp-1A1h] BYREF
  std::string v210; // [rsp+7B0h] [rbp-1A0h] BYREF
  char v211; // [rsp+7BBh] [rbp-195h] BYREF
  int v212; // [rsp+7BCh] [rbp-194h] BYREF
  std::string v213; // [rsp+7C0h] [rbp-190h] BYREF
  char v214; // [rsp+7CFh] [rbp-181h] BYREF
  std::string v215; // [rsp+7D0h] [rbp-180h] BYREF
  char v216; // [rsp+7DFh] [rbp-171h] BYREF
  MemChrBag v217; // [rsp+7E0h] [rbp-170h] BYREF
  Answer::Inifile v218; // [rsp+800h] [rbp-150h] BYREF
  char v219; // [rsp+83Fh] [rbp-111h] BYREF
  std::string v220; // [rsp+840h] [rbp-110h] BYREF
  char v221; // [rsp+84Fh] [rbp-101h] BYREF
  std::string v222; // [rsp+850h] [rbp-100h] BYREF
  char v223; // [rsp+85Fh] [rbp-F1h] BYREF
  std::string v224; // [rsp+860h] [rbp-F0h] BYREF
  char v225; // [rsp+86Fh] [rbp-E1h] BYREF
  std::string v226; // [rsp+870h] [rbp-E0h] BYREF
  char v227; // [rsp+87Fh] [rbp-D1h] BYREF
  std::string v228; // [rsp+880h] [rbp-D0h] BYREF
  char v229; // [rsp+88Fh] [rbp-C1h] BYREF
  MemChrBagVector v230; // [rsp+890h] [rbp-C0h] BYREF
  Answer::Inifile v231; // [rsp+8B0h] [rbp-A0h] BYREF
  char v232; // [rsp+8EFh] [rbp-61h] BYREF
  std::string v233; // [rsp+8F0h] [rbp-60h] BYREF
  char v234; // [rsp+8FFh] [rbp-51h] BYREF
  std::string v235; // [rsp+900h] [rbp-50h] BYREF
  char v236; // [rsp+90Fh] [rbp-41h] BYREF
  std::string v237; // [rsp+910h] [rbp-40h] BYREF
  char v238; // [rsp+91Fh] [rbp-31h] BYREF
  int32_t nSpiderQueenCount; // [rsp+920h] [rbp-30h]
  int32_t i; // [rsp+924h] [rbp-2Ch]
  int32_t i_0; // [rsp+928h] [rbp-28h]
  int32_t i_1; // [rsp+92Ch] [rbp-24h]
  int32_t i_2; // [rsp+930h] [rbp-20h]
  int32_t i_3; // [rsp+934h] [rbp-1Ch]
  int32_t i_4; // [rsp+938h] [rbp-18h]
  int32_t j; // [rsp+93Ch] [rbp-14h]

  thisa = this;
  linea = line;
  if ( line != 9 )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::isUniteServer(v2) )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      thisa->m_nDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_UNITE);
      v4 = Answer::Singleton<CTimer>::instance();
      CTimer::GetLocalNow(&nowTime, v4);
      thisa->m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
      Answer::Inifile::Inifile(&ini);
      std::allocator<char>::allocator(&v22);
      std::string::string(&file, "./ServerConfig/Tables/UnitServer.cfg");
      Answer::Inifile::parse(&ini, &file);
      std::string::~string(&file);
      std::allocator<char>::~allocator(&v22);
      memset(szCol, 0, sizeof(szCol));
      std::allocator<char>::allocator(&v24);
      std::string::string(&key, "start_day");
      std::allocator<char>::allocator(&v26);
      std::string::string(&section, "CONFIG");
      thisa->m_nStartDay = Answer::Inifile::getIntValue(&ini, &section, &key);
      std::string::~string(&section);
      std::allocator<char>::~allocator(&v26);
      std::string::~string(&key);
      std::allocator<char>::~allocator(&v24);
      std::allocator<char>::allocator(&v28);
      std::string::string(&v27, "end_day");
      std::allocator<char>::allocator(&v30);
      std::string::string(&v29, "CONFIG");
      thisa->m_nEndDay = Answer::Inifile::getIntValue(&ini, &v29, &v27);
      std::string::~string(&v29);
      std::allocator<char>::~allocator(&v30);
      std::string::~string(&v27);
      std::allocator<char>::~allocator(&v28);
      std::allocator<char>::allocator(&v32);
      std::string::string(&v31, "icon");
      std::allocator<char>::allocator(&v34);
      std::string::string(&v33, "CONFIG");
      thisa->m_nIcon = Answer::Inifile::getIntValue(&ini, &v33, &v31);
      std::string::~string(&v33);
      std::allocator<char>::~allocator(&v34);
      std::string::~string(&v31);
      std::allocator<char>::~allocator(&v32);
      std::allocator<char>::allocator(&v36);
      std::string::string(&v35, "start_day");
      std::allocator<char>::allocator(&v38);
      std::string::string(&v37, "HUO_YUE_DU");
      thisa->m_vStartDay[1] = Answer::Inifile::getIntValue(&ini, &v37, &v35);
      std::string::~string(&v37);
      std::allocator<char>::~allocator(&v38);
      std::string::~string(&v35);
      std::allocator<char>::~allocator(&v36);
      std::allocator<char>::allocator(&v40);
      std::string::string(&v39, "end_day");
      std::allocator<char>::allocator(&v42);
      std::string::string(&v41, "HUO_YUE_DU");
      thisa->m_vEndDay[1] = Answer::Inifile::getIntValue(&ini, &v41, &v39);
      std::string::~string(&v41);
      std::allocator<char>::~allocator(&v42);
      std::string::~string(&v39);
      std::allocator<char>::~allocator(&v40);
      std::allocator<char>::allocator(&v44);
      std::string::string(&v43, "size");
      std::allocator<char>::allocator(&v46);
      std::string::string(&v45, "HUO_YUE_DU");
      thisa->m_nHuoYueSize = Answer::Inifile::getIntValue(&ini, &v45, &v43);
      std::string::~string(&v45);
      std::allocator<char>::~allocator(&v46);
      std::string::~string(&v43);
      std::allocator<char>::~allocator(&v44);
      std::vector<int>::reserve(&thisa->m_vHuoYueValue, thisa->m_nHuoYueSize);
      std::vector<std::vector<MemChrBag>>::reserve(&thisa->m_vHuoYueGift, thisa->m_nHuoYueSize);
      for ( i = 0; thisa->m_nHuoYueSize > i; ++i )
      {
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "limit%d", i + 1);
        std::allocator<char>::allocator(&v49);
        std::string::string(&v48, szCol);
        std::allocator<char>::allocator(&v51);
        std::string::string(&v50, "HUO_YUE_DU");
        __x = Answer::Inifile::getIntValue(&ini, &v50, &v48);
        std::vector<int>::push_back(&thisa->m_vHuoYueValue, &__x);
        std::string::~string(&v50);
        std::allocator<char>::~allocator(&v51);
        std::string::~string(&v48);
        std::allocator<char>::~allocator(&v49);
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "gift%d", i + 1);
        std::allocator<char>::allocator((char *)&v53.m_strMap._M_t._M_impl._M_header._M_left + 7);
        std::string::string(&v53.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
        std::allocator<char>::allocator((char *)&v53.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::string(&v53.m_strMap._M_t._M_impl._M_header._M_right, "HUO_YUE_DU");
        Answer::Inifile::getStrValue(
          &v53,
          (const std::string *const)&ini,
          (const std::string *const)&v53.m_strMap._M_t._M_impl._M_header._M_right);
        CItemHelper::parseItemVectorString(&v52, (const std::string *const)&v53);
        std::vector<std::vector<MemChrBag>>::push_back(&thisa->m_vHuoYueGift, &v52);
        std::vector<MemChrBag>::~vector(&v52);
        std::string::~string(&v53);
        std::string::~string(&v53.m_strMap._M_t._M_impl._M_header._M_right);
        std::allocator<char>::~allocator((char *)&v53.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::~string(&v53.m_strMap._M_t._M_impl._M_header._M_parent);
        std::allocator<char>::~allocator((char *)&v53.m_strMap._M_t._M_impl._M_header._M_left + 7);
      }
      std::allocator<char>::allocator(&v54);
      std::string::string(&v53.m_currentSection, "start_day");
      std::allocator<char>::allocator(&v56);
      std::string::string(&v55, "RECHARGE");
      thisa->m_vStartDay[2] = Answer::Inifile::getIntValue(&ini, &v55, &v53.m_currentSection);
      std::string::~string(&v55);
      std::allocator<char>::~allocator(&v56);
      std::string::~string(&v53.m_currentSection);
      std::allocator<char>::~allocator(&v54);
      std::allocator<char>::allocator(&v58);
      std::string::string(&v57, "end_day");
      std::allocator<char>::allocator(&v60);
      std::string::string(&v59, "RECHARGE");
      thisa->m_vEndDay[2] = Answer::Inifile::getIntValue(&ini, &v59, &v57);
      std::string::~string(&v59);
      std::allocator<char>::~allocator(&v60);
      std::string::~string(&v57);
      std::allocator<char>::~allocator(&v58);
      std::allocator<char>::allocator(&v62);
      std::string::string(&v61, "size");
      std::allocator<char>::allocator(&v64);
      std::string::string(&v63, "RECHARGE");
      thisa->m_nRechargeDaysSize = Answer::Inifile::getIntValue(&ini, &v63, &v61);
      std::string::~string(&v63);
      std::allocator<char>::~allocator(&v64);
      std::string::~string(&v61);
      std::allocator<char>::~allocator(&v62);
      std::vector<int>::reserve(&thisa->m_vRechargeValue, thisa->m_nRechargeDaysSize);
      std::vector<std::vector<MemChrBag>>::reserve(&thisa->m_vRechargeGift, thisa->m_nRechargeDaysSize);
      for ( i_0 = 0; thisa->m_nRechargeDaysSize > i_0; ++i_0 )
      {
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "gold%d", i_0 + 1);
        std::allocator<char>::allocator(&v67);
        std::string::string(&v66, szCol);
        std::allocator<char>::allocator(&v69);
        std::string::string(&v68, "RECHARGE");
        IntValue = Answer::Inifile::getIntValue(&ini, &v68, &v66);
        std::vector<int>::push_back(&thisa->m_vRechargeValue, &IntValue);
        std::string::~string(&v68);
        std::allocator<char>::~allocator(&v69);
        std::string::~string(&v66);
        std::allocator<char>::~allocator(&v67);
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "gift%d", i_0 + 1);
        std::allocator<char>::allocator((char *)&v71.m_strMap._M_t._M_impl._M_header._M_left + 7);
        std::string::string(&v71.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
        std::allocator<char>::allocator((char *)&v71.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::string(&v71.m_strMap._M_t._M_impl._M_header._M_right, "RECHARGE");
        Answer::Inifile::getStrValue(
          &v71,
          (const std::string *const)&ini,
          (const std::string *const)&v71.m_strMap._M_t._M_impl._M_header._M_right);
        CItemHelper::parseItemVectorString(&v70, (const std::string *const)&v71);
        std::vector<std::vector<MemChrBag>>::push_back(&thisa->m_vRechargeGift, &v70);
        std::vector<MemChrBag>::~vector(&v70);
        std::string::~string(&v71);
        std::string::~string(&v71.m_strMap._M_t._M_impl._M_header._M_right);
        std::allocator<char>::~allocator((char *)&v71.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::~string(&v71.m_strMap._M_t._M_impl._M_header._M_parent);
        std::allocator<char>::~allocator((char *)&v71.m_strMap._M_t._M_impl._M_header._M_left + 7);
      }
      std::allocator<char>::allocator(&v72);
      std::string::string(&v71.m_currentSection, "start_day");
      std::allocator<char>::allocator(&v74);
      std::string::string(&v73, "XIAO_FEI_DRAW");
      thisa->m_vStartDay[8] = Answer::Inifile::getIntValue(&ini, &v73, &v71.m_currentSection);
      std::string::~string(&v73);
      std::allocator<char>::~allocator(&v74);
      std::string::~string(&v71.m_currentSection);
      std::allocator<char>::~allocator(&v72);
      std::allocator<char>::allocator(&v76);
      std::string::string(&v75, "end_day");
      std::allocator<char>::allocator(&v78);
      std::string::string(&v77, "XIAO_FEI_DRAW");
      thisa->m_vEndDay[8] = Answer::Inifile::getIntValue(&ini, &v77, &v75);
      std::string::~string(&v77);
      std::allocator<char>::~allocator(&v78);
      std::string::~string(&v75);
      std::allocator<char>::~allocator(&v76);
      std::allocator<char>::allocator(&v80);
      std::string::string(&v79, "size");
      std::allocator<char>::allocator(&v82);
      std::string::string(&v81, "XIAO_FEI_DRAW");
      thisa->m_XiaoFeiDrawSize = Answer::Inifile::getIntValue(&ini, &v81, &v79);
      std::string::~string(&v81);
      std::allocator<char>::~allocator(&v82);
      std::string::~string(&v79);
      std::allocator<char>::~allocator(&v80);
      std::vector<int>::reserve(&thisa->m_nXiaoFeiDrawValue, thisa->m_XiaoFeiDrawSize);
      for ( i_1 = 0; thisa->m_XiaoFeiDrawSize > i_1; ++i_1 )
      {
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "value%d", i_1 + 1);
        std::allocator<char>::allocator(&v85);
        std::string::string(&v84, szCol);
        std::allocator<char>::allocator(&v87);
        std::string::string(&v86, "XIAO_FEI_DRAW");
        v83 = Answer::Inifile::getIntValue(&ini, &v86, &v84);
        std::vector<int>::push_back(&thisa->m_nXiaoFeiDrawValue, &v83);
        std::string::~string(&v86);
        std::allocator<char>::~allocator(&v87);
        std::string::~string(&v84);
        std::allocator<char>::~allocator(&v85);
      }
      std::allocator<char>::allocator(&v89);
      std::string::string(&v88, "start_day");
      std::allocator<char>::allocator(&v91);
      std::string::string(&v90, "CHOU_JIANG");
      thisa->m_vStartDay[3] = Answer::Inifile::getIntValue(&ini, &v90, &v88);
      std::string::~string(&v90);
      std::allocator<char>::~allocator(&v91);
      std::string::~string(&v88);
      std::allocator<char>::~allocator(&v89);
      std::allocator<char>::allocator(&v93);
      std::string::string(&v92, "end_day");
      std::allocator<char>::allocator(&v95);
      std::string::string(&v94, "CHOU_JIANG");
      thisa->m_vEndDay[3] = Answer::Inifile::getIntValue(&ini, &v94, &v92);
      std::string::~string(&v94);
      std::allocator<char>::~allocator(&v95);
      std::string::~string(&v92);
      std::allocator<char>::~allocator(&v93);
      std::allocator<char>::allocator(&v97);
      std::string::string(&v96, "Type");
      std::allocator<char>::allocator(&v99);
      std::string::string(&v98, "CHOU_JIANG");
      thisa->m_ChouJiangType = Answer::Inifile::getIntValue(&ini, &v98, &v96);
      std::string::~string(&v98);
      std::allocator<char>::~allocator(&v99);
      std::string::~string(&v96);
      std::allocator<char>::~allocator(&v97);
      std::allocator<char>::allocator(&v101);
      std::string::string(&v100, "times");
      std::allocator<char>::allocator(&v103);
      std::string::string(&v102, "CHOU_JIANG");
      thisa->m_ChouJiangCount = Answer::Inifile::getIntValue(&ini, &v102, &v100);
      std::string::~string(&v102);
      std::allocator<char>::~allocator(&v103);
      std::string::~string(&v100);
      std::allocator<char>::~allocator(&v101);
      std::allocator<char>::allocator(&v105);
      std::string::string(&v104, "start_day");
      std::allocator<char>::allocator(&v107);
      std::string::string(&v106, "LIMIT_BUY");
      thisa->m_vStartDay[4] = Answer::Inifile::getIntValue(&ini, &v106, &v104);
      std::string::~string(&v106);
      std::allocator<char>::~allocator(&v107);
      std::string::~string(&v104);
      std::allocator<char>::~allocator(&v105);
      std::allocator<char>::allocator(&v109);
      std::string::string(&v108, "end_day");
      std::allocator<char>::allocator(&v111);
      std::string::string(&v110, "LIMIT_BUY");
      thisa->m_vEndDay[4] = Answer::Inifile::getIntValue(&ini, &v110, &v108);
      std::string::~string(&v110);
      std::allocator<char>::~allocator(&v111);
      std::string::~string(&v108);
      std::allocator<char>::~allocator(&v109);
      std::allocator<char>::allocator(&v113);
      std::string::string(&v112, "start_day");
      std::allocator<char>::allocator(&v115);
      std::string::string(&v114, "MYSTERY_SHOP");
      thisa->m_vStartDay[5] = Answer::Inifile::getIntValue(&ini, &v114, &v112);
      std::string::~string(&v114);
      std::allocator<char>::~allocator(&v115);
      std::string::~string(&v112);
      std::allocator<char>::~allocator(&v113);
      std::allocator<char>::allocator(&v117);
      std::string::string(&v116, "end_day");
      std::allocator<char>::allocator(&v119);
      std::string::string(&v118, "MYSTERY_SHOP");
      thisa->m_vEndDay[5] = Answer::Inifile::getIntValue(&ini, &v118, &v116);
      std::string::~string(&v118);
      std::allocator<char>::~allocator(&v119);
      std::string::~string(&v116);
      std::allocator<char>::~allocator(&v117);
      std::allocator<char>::allocator(&v121);
      std::string::string(&v120, "broad");
      std::allocator<char>::allocator(&v123);
      std::string::string(&v122, "MYSTERY_SHOP");
      thisa->m_nMysteryShopRefreshBroad = Answer::Inifile::getIntValue(&ini, &v122, &v120);
      std::string::~string(&v122);
      std::allocator<char>::~allocator(&v123);
      std::string::~string(&v120);
      std::allocator<char>::~allocator(&v121);
      std::allocator<char>::allocator(&v125);
      std::string::string(&v124, "cost_gold");
      std::allocator<char>::allocator(&v127);
      std::string::string(&v126, "MYSTERY_SHOP");
      thisa->m_sMysteryShopRefreshCost = Answer::Inifile::getIntValue(&ini, &v126, &v124);
      std::string::~string(&v126);
      std::allocator<char>::~allocator(&v127);
      std::string::~string(&v124);
      std::allocator<char>::~allocator(&v125);
      std::allocator<char>::allocator(&v129);
      std::string::string(&v128, "start_day");
      std::allocator<char>::allocator(&v131);
      std::string::string(&v130, "SPDER_QUEEN");
      thisa->m_vStartDay[6] = Answer::Inifile::getIntValue(&ini, &v130, &v128);
      std::string::~string(&v130);
      std::allocator<char>::~allocator(&v131);
      std::string::~string(&v128);
      std::allocator<char>::~allocator(&v129);
      std::allocator<char>::allocator(&v133);
      std::string::string(&v132, "end_day");
      std::allocator<char>::allocator(&v135);
      std::string::string(&v134, "SPDER_QUEEN");
      thisa->m_vEndDay[6] = Answer::Inifile::getIntValue(&ini, &v134, &v132);
      std::string::~string(&v134);
      std::allocator<char>::~allocator(&v135);
      std::string::~string(&v132);
      std::allocator<char>::~allocator(&v133);
      std::allocator<char>::allocator(&v137);
      std::string::string(&v136, "icon");
      std::allocator<char>::allocator(&v139);
      std::string::string(&v138, "SPDER_QUEEN");
      thisa->m_nSpiderQueenIcon = Answer::Inifile::getIntValue(&ini, &v138, &v136);
      std::string::~string(&v138);
      std::allocator<char>::~allocator(&v139);
      std::string::~string(&v136);
      std::allocator<char>::~allocator(&v137);
      std::allocator<char>::allocator(&v141);
      std::string::string(&v140, "start_broadcast");
      std::allocator<char>::allocator(&v143);
      std::string::string(&v142, "SPDER_QUEEN");
      thisa->m_nSpiderQueenStartBroadcast = Answer::Inifile::getIntValue(&ini, &v142, &v140);
      std::string::~string(&v142);
      std::allocator<char>::~allocator(&v143);
      std::string::~string(&v140);
      std::allocator<char>::~allocator(&v141);
      std::allocator<char>::allocator(&v145);
      std::string::string(&v144, "end_broadcast");
      std::allocator<char>::allocator(&v147);
      std::string::string(&v146, "SPDER_QUEEN");
      thisa->m_nSpiderQueenEndBroadcast = Answer::Inifile::getIntValue(&ini, &v146, &v144);
      std::string::~string(&v146);
      std::allocator<char>::~allocator(&v147);
      std::string::~string(&v144);
      std::allocator<char>::~allocator(&v145);
      std::allocator<char>::allocator(&v149);
      std::string::string(&v148, "kill_broadcast");
      std::allocator<char>::allocator(&v151);
      std::string::string(&v150, "SPDER_QUEEN");
      thisa->m_nSpiderQueenKillBroadcast = Answer::Inifile::getIntValue(&ini, &v150, &v148);
      std::string::~string(&v150);
      std::allocator<char>::~allocator(&v151);
      std::string::~string(&v148);
      std::allocator<char>::~allocator(&v149);
      std::allocator<char>::allocator(&v153);
      std::string::string(&v152, "count");
      std::allocator<char>::allocator(&v155);
      std::string::string(&v154, "SPDER_QUEEN");
      nSpiderQueenCount = Answer::Inifile::getIntValue(&ini, &v154, &v152);
      std::string::~string(&v154);
      std::allocator<char>::~allocator(&v155);
      std::string::~string(&v152);
      std::allocator<char>::~allocator(&v153);
      std::vector<TimeArea>::reserve(&thisa->m_vSpiderQueenMinute, nSpiderQueenCount);
      for ( i_2 = 0; i_2 < nSpiderQueenCount; ++i_2 )
      {
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "start_minute%d", i_2 + 1);
        std::allocator<char>::allocator(&v157);
        std::string::string(&v156, szCol);
        std::allocator<char>::allocator(&v159);
        std::string::string(&v158, "SPDER_QUEEN");
        tarea.nStartTime = Answer::Inifile::getIntValue(&ini, &v158, &v156);
        std::string::~string(&v158);
        std::allocator<char>::~allocator(&v159);
        std::string::~string(&v156);
        std::allocator<char>::~allocator(&v157);
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "end_minute%d", i_2 + 1);
        std::allocator<char>::allocator(&v161);
        std::string::string(&v160, szCol);
        std::allocator<char>::allocator(&v163);
        std::string::string(&v162, "SPDER_QUEEN");
        tarea.nEndTime = Answer::Inifile::getIntValue(&ini, &v162, &v160);
        std::string::~string(&v162);
        std::allocator<char>::~allocator(&v163);
        std::string::~string(&v160);
        std::allocator<char>::~allocator(&v161);
        std::vector<TimeArea>::push_back(&thisa->m_vSpiderQueenMinute, &tarea);
      }
      std::allocator<char>::allocator(&v165);
      std::string::string(&v164, "mapid");
      std::allocator<char>::allocator(&v167);
      std::string::string(&v166, "SPDER_QUEEN");
      thisa->m_MapId = Answer::Inifile::getIntValue(&ini, &v166, &v164);
      std::string::~string(&v166);
      std::allocator<char>::~allocator(&v167);
      std::string::~string(&v164);
      std::allocator<char>::~allocator(&v165);
      std::allocator<char>::allocator(&v169);
      std::string::string(&v168, "x");
      std::allocator<char>::allocator(&v171);
      std::string::string(&v170, "SPDER_QUEEN");
      thisa->m_X = Answer::Inifile::getIntValue(&ini, &v170, &v168);
      std::string::~string(&v170);
      std::allocator<char>::~allocator(&v171);
      std::string::~string(&v168);
      std::allocator<char>::~allocator(&v169);
      std::allocator<char>::allocator(&v173);
      std::string::string(&v172, "y");
      std::allocator<char>::allocator(&v175);
      std::string::string(&v174, "SPDER_QUEEN");
      thisa->m_Y = Answer::Inifile::getIntValue(&ini, &v174, &v172);
      std::string::~string(&v174);
      std::allocator<char>::~allocator(&v175);
      std::string::~string(&v172);
      std::allocator<char>::~allocator(&v173);
      std::allocator<char>::allocator(&v177);
      std::string::string(&v176, "mid");
      std::allocator<char>::allocator(&v179);
      std::string::string(&v178, "SPDER_QUEEN");
      thisa->m_Mid = Answer::Inifile::getIntValue(&ini, &v178, &v176);
      std::string::~string(&v178);
      std::allocator<char>::~allocator(&v179);
      std::string::~string(&v176);
      std::allocator<char>::~allocator(&v177);
      std::allocator<char>::allocator(&v181);
      std::string::string(&v180, "start_day");
      std::allocator<char>::allocator(&v183);
      std::string::string(&v182, "COLLECT_DROP");
      thisa->m_vStartDay[7] = Answer::Inifile::getIntValue(&ini, &v182, &v180);
      std::string::~string(&v182);
      std::allocator<char>::~allocator(&v183);
      std::string::~string(&v180);
      std::allocator<char>::~allocator(&v181);
      std::allocator<char>::allocator(&v185);
      std::string::string(&v184, "end_day");
      std::allocator<char>::allocator(&v187);
      std::string::string(&v186, "COLLECT_DROP");
      thisa->m_vEndDay[7] = Answer::Inifile::getIntValue(&ini, &v186, &v184);
      std::string::~string(&v186);
      std::allocator<char>::~allocator(&v187);
      std::string::~string(&v184);
      std::allocator<char>::~allocator(&v185);
      std::allocator<char>::allocator(&v189);
      std::string::string(&v188, "start_day");
      std::allocator<char>::allocator(&v191);
      std::string::string(&v190, "CHANGE_NAME_CARD");
      thisa->m_vStartDay[9] = Answer::Inifile::getIntValue(&ini, &v190, &v188);
      std::string::~string(&v190);
      std::allocator<char>::~allocator(&v191);
      std::string::~string(&v188);
      std::allocator<char>::~allocator(&v189);
      std::allocator<char>::allocator(&v193);
      std::string::string(&v192, "end_day");
      std::allocator<char>::allocator(&v195);
      std::string::string(&v194, "CHANGE_NAME_CARD");
      thisa->m_vEndDay[9] = Answer::Inifile::getIntValue(&ini, &v194, &v192);
      std::string::~string(&v194);
      std::allocator<char>::~allocator(&v195);
      std::string::~string(&v192);
      std::allocator<char>::~allocator(&v193);
      std::allocator<char>::allocator(&v197);
      std::string::string(&v196, "price");
      std::allocator<char>::allocator(&v199);
      std::string::string(&v198, "CHANGE_NAME_CARD");
      thisa->m_nPrice = Answer::Inifile::getIntValue(&ini, &v198, &v196);
      std::string::~string(&v198);
      std::allocator<char>::~allocator(&v199);
      std::string::~string(&v196);
      std::allocator<char>::~allocator(&v197);
      std::allocator<char>::allocator((char *)&v200.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v200.m_strMap._M_t._M_impl._M_header._M_parent, "item");
      std::allocator<char>::allocator((char *)&v200.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v200.m_strMap._M_t._M_impl._M_header._M_right, "CHANGE_NAME_CARD");
      Answer::Inifile::getStrValue(
        &v200,
        (const std::string *const)&ini,
        (const std::string *const)&v200.m_strMap._M_t._M_impl._M_header._M_right);
      v5 = thisa;
      CItemHelper::parseItemString(&v13, (const std::string *const)&v200);
      v5->m_Item = v13;
      std::string::~string(&v200);
      std::string::~string(&v200.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v200.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v200.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v200.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator(&v201);
      std::string::string(&v200.m_currentSection, "start_day");
      std::allocator<char>::allocator(&v203);
      std::string::string(&v202, "WING_LEVEL_UP");
      v6 = Answer::Inifile::getIntValue(&ini, &v202, &v200.m_currentSection);
      thisa->m_vStartDay[10] = v6;
      std::string::~string(&v202);
      std::allocator<char>::~allocator(&v203);
      std::string::~string(&v200.m_currentSection);
      std::allocator<char>::~allocator(&v201);
      std::allocator<char>::allocator(&v205);
      std::string::string(&v204, "end_day");
      std::allocator<char>::allocator(&v207);
      std::string::string(&v206, "WING_LEVEL_UP");
      v7 = Answer::Inifile::getIntValue(&ini, &v206, &v204);
      thisa->m_vEndDay[10] = v7;
      std::string::~string(&v206);
      std::allocator<char>::~allocator(&v207);
      std::string::~string(&v204);
      std::allocator<char>::~allocator(&v205);
      std::allocator<char>::allocator(&v209);
      std::string::string(&v208, "size");
      std::allocator<char>::allocator(&v211);
      std::string::string(&v210, "WING_LEVEL_UP");
      v8 = Answer::Inifile::getIntValue(&ini, &v210, &v208);
      thisa->m_nSize = v8;
      std::string::~string(&v210);
      std::allocator<char>::~allocator(&v211);
      std::string::~string(&v208);
      std::allocator<char>::~allocator(&v209);
      std::vector<int>::reserve(&thisa->m_UseItemCount, thisa->m_nSize);
      std::vector<MemChrBag>::reserve(&thisa->m_Items, thisa->m_nSize);
      for ( i_3 = 0; thisa->m_nSize > i_3; ++i_3 )
      {
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "value%d", i_3 + 1);
        std::allocator<char>::allocator(&v214);
        std::string::string(&v213, szCol);
        std::allocator<char>::allocator(&v216);
        std::string::string(&v215, "WING_LEVEL_UP");
        v212 = Answer::Inifile::getIntValue(&ini, &v215, &v213);
        std::vector<int>::push_back(&thisa->m_UseItemCount, &v212);
        std::string::~string(&v215);
        std::allocator<char>::~allocator(&v216);
        std::string::~string(&v213);
        std::allocator<char>::~allocator(&v214);
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "item%d", i_3 + 1);
        std::allocator<char>::allocator((char *)&v218.m_strMap._M_t._M_impl._M_header._M_left + 7);
        std::string::string(&v218.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
        std::allocator<char>::allocator((char *)&v218.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::string(&v218.m_strMap._M_t._M_impl._M_header._M_right, "WING_LEVEL_UP");
        Answer::Inifile::getStrValue(
          &v218,
          (const std::string *const)&ini,
          (const std::string *const)&v218.m_strMap._M_t._M_impl._M_header._M_right);
        CItemHelper::parseItemString(&v217, (const std::string *const)&v218);
        std::vector<MemChrBag>::push_back(&thisa->m_Items, &v217);
        std::string::~string(&v218);
        std::string::~string(&v218.m_strMap._M_t._M_impl._M_header._M_right);
        std::allocator<char>::~allocator((char *)&v218.m_strMap._M_t._M_impl._M_node_count + 7);
        std::string::~string(&v218.m_strMap._M_t._M_impl._M_header._M_parent);
        std::allocator<char>::~allocator((char *)&v218.m_strMap._M_t._M_impl._M_header._M_left + 7);
      }
      std::allocator<char>::allocator(&v219);
      std::string::string(&v218.m_currentSection, "start_day");
      std::allocator<char>::allocator(&v221);
      std::string::string(&v220, "LIAN_RECHARGE");
      v9 = Answer::Inifile::getIntValue(&ini, &v220, &v218.m_currentSection);
      thisa->m_vStartDay[11] = v9;
      std::string::~string(&v220);
      std::allocator<char>::~allocator(&v221);
      std::string::~string(&v218.m_currentSection);
      std::allocator<char>::~allocator(&v219);
      std::allocator<char>::allocator(&v223);
      std::string::string(&v222, "end_day");
      std::allocator<char>::allocator(&v225);
      std::string::string(&v224, "LIAN_RECHARGE");
      v10 = Answer::Inifile::getIntValue(&ini, &v224, &v222);
      thisa->m_vEndDay[11] = v10;
      std::string::~string(&v224);
      std::allocator<char>::~allocator(&v225);
      std::string::~string(&v222);
      std::allocator<char>::~allocator(&v223);
      for ( i_4 = 0; i_4 <= 1; ++i_4 )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<std::vector<MemChrBag>>::vector(&stu.vGiftVector);
        bzero(szCol, 0x40u);
        snprintf(szCol, 0x3Fu, "type%d", i_4);
        std::allocator<char>::allocator(&v227);
        std::string::string(&v226, szCol);
        std::allocator<char>::allocator(&v229);
        std::string::string(&v228, "LIAN_RECHARGE");
        stu.nValues = Answer::Inifile::getIntValue(&ini, &v228, &v226);
        std::string::~string(&v228);
        std::allocator<char>::~allocator(&v229);
        std::string::~string(&v226);
        std::allocator<char>::~allocator(&v227);
        for ( j = 0; j <= 2; ++j )
        {
          bzero(szCol, 0x40u);
          snprintf(szCol, 0x3Fu, "gift%d_%d", i_4, j);
          std::allocator<char>::allocator((char *)&v231.m_strMap._M_t._M_impl._M_header._M_left + 7);
          std::string::string(&v231.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
          std::allocator<char>::allocator((char *)&v231.m_strMap._M_t._M_impl._M_node_count + 7);
          std::string::string(&v231.m_strMap._M_t._M_impl._M_header._M_right, "LIAN_RECHARGE");
          Answer::Inifile::getStrValue(
            &v231,
            (const std::string *const)&ini,
            (const std::string *const)&v231.m_strMap._M_t._M_impl._M_header._M_right);
          CItemHelper::parseItemVectorString(&v230, (const std::string *const)&v231);
          std::vector<std::vector<MemChrBag>>::push_back(&stu.vGiftVector, &v230);
          std::vector<MemChrBag>::~vector(&v230);
          std::string::~string(&v231);
          std::string::~string(&v231.m_strMap._M_t._M_impl._M_header._M_right);
          std::allocator<char>::~allocator((char *)&v231.m_strMap._M_t._M_impl._M_node_count + 7);
          std::string::~string(&v231.m_strMap._M_t._M_impl._M_header._M_parent);
          std::allocator<char>::~allocator((char *)&v231.m_strMap._M_t._M_impl._M_header._M_left + 7);
        }
        std::vector<LianRechargeCfg>::push_back(&thisa->m_LianRechargeCfgVt, &stu);
        LianRechargeCfg::~LianRechargeCfg(&stu);
      }
      std::allocator<char>::allocator(&v232);
      std::string::string(&v231.m_currentSection, "start_day");
      std::allocator<char>::allocator(&v234);
      std::string::string(&v233, "CHOU_JIANG_TIMES");
      v11 = Answer::Inifile::getIntValue(&ini, &v233, &v231.m_currentSection);
      thisa->m_vStartDay[12] = v11;
      std::string::~string(&v233);
      std::allocator<char>::~allocator(&v234);
      std::string::~string(&v231.m_currentSection);
      std::allocator<char>::~allocator(&v232);
      std::allocator<char>::allocator(&v236);
      std::string::string(&v235, "end_day");
      std::allocator<char>::allocator(&v238);
      std::string::string(&v237, "CHOU_JIANG_TIMES");
      v12 = Answer::Inifile::getIntValue(&ini, &v237, &v235);
      thisa->m_vEndDay[12] = v12;
      std::string::~string(&v237);
      std::allocator<char>::~allocator(&v238);
      std::string::~string(&v235);
      std::allocator<char>::~allocator(&v236);
      Answer::Inifile::~Inifile(&ini);
    }
  }
}


#####################################
void __cdecl CUniteServer::OnGetChouJiangReward(CUniteServer *const this, Player *player, int32_t nIndex)
{
  CfgData *v3; // rax
  int32_t Record; // eax
  CExtCharBag *Bag; // rax
  const TreasureHunterCfg *CurCfg; // [rsp+20h] [rbp-20h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( player )
  {
    if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_CHOU_JIANG_TIMES) )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      CurCfg = CfgData::GetTreasureHunterCfg(v3, nIndex);
      if ( CurCfg )
      {
        if ( CurCfg->nType == 2 && Player::getRecord(player, 1412) >= CurCfg->nRequire )
        {
          Record = Player::getRecord(player, 1413);
          NewRecord = Record | (1 << (nIndex - 1));
          if ( NewRecord != Record )
          {
            Bag = Player::GetBag(player);
            if ( CExtCharBag::AddItem(Bag, &CurCfg->Items, ITEM_CHANGE_REASON::IDCR_HE_FU_CHOU_JIANG_TIMES) )
            {
              Player::updateRecord(player, 1413, NewRecord);
              CUniteServer::GongGao(this, CurCfg->GongGaoId, player);
              CUniteServer::SendIconState(this, player);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CUniteServer::OnAddChouJiangTimes(CUniteServer *const this, Player *player, int32_t AddTimes)
{
  CExtOperateLimit *OperateLimit; // rax
  bool NeedSendIcon; // [rsp+2Fh] [rbp-1h]

  NeedSendIcon = 0;
  if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_CHOU_JIANG_TIMES) )
  {
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1412, AddTimes);
    NeedSendIcon = 1;
  }
  if ( NeedSendIcon )
    CUniteServer::SendIconState(this, player);
}


#####################################
void __cdecl CUniteServer::OnRecharge(CUniteServer *const this, Player *player, int32_t AddValue)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v6; // rax
  CExtOperateLimit *v7; // rax
  bool NeedSendIcon; // [rsp+2Bh] [rbp-15h]
  int32_t OldValue; // [rsp+2Ch] [rbp-14h]

  if ( player )
  {
    NeedSendIcon = 0;
    if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_LIAN_RECHARGE) )
    {
      OldValue = Player::getRecord(player, 2132);
      if ( std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 0)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 0)->nValues )
      {
        OperateLimit = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1408, 1);
        NeedSendIcon = 1;
      }
      if ( std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 1u)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 1u)->nValues )
      {
        v6 = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(v6, 1409, 1);
        NeedSendIcon = 1;
      }
    }
    if ( CUniteServer::IsInUnitServerTime(this) )
    {
      v7 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v7, 2132, AddValue);
    }
    if ( NeedSendIcon )
      CUniteServer::SendIconState(this, player);
  }
}


#####################################
void __cdecl CUniteServer::GetLianRechargeReward(
        CUniteServer *const this,
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

  if ( player && CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_LIAN_RECHARGE) )
  {
    if ( nType )
    {
      if ( nType != 1 )
        return;
      RewardRecord = 1411;
      LianChongRecord = 1409;
    }
    else
    {
      RewardRecord = 1410;
      LianChongRecord = 1408;
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
        if ( CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::IDCR_HE_FU_LIAN_CHONG) )
        {
          Player::updateRecord(player, RewardRecord, NewRecord);
          CUniteServer::GongGao(this, 3012, player);
          CUniteServer::SendIconState(this, player);
        }
      }
    }
  }
}


#####################################
void __cdecl CUniteServer::GongGao(CUniteServer *const this, int32_t GongGaoId, Player *player)
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
void __cdecl CUniteServer::AddHuoYueDu(CUniteServer *const this, Player *player, int32_t Values)
{
  int32_t v4; // edx

  if ( player && Values > 0 && CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_HUO_YUE_DU) )
  {
    v4 = Values + Player::getRecord(player, 2089);
    Player::updateRecord(player, 2089, v4);
    CUniteServer::SendIconState(this, player);
  }
}


#####################################
void __cdecl CUniteServer::AddXiaoFeiValue(CUniteServer *const this, Player *player, int32_t Value)
{
  int32_t v4; // edx

  if ( player && Value > 0 && CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_XIAO_FEI_SUM_DRAW) )
  {
    v4 = Value + Player::getRecord(player, 1402);
    Player::updateRecord(player, 1402, v4);
    if ( CUniteServer::GetCanXiaoFeiDrawTime(this, player) > 0 )
      CUniteServer::SendIconState(this, player);
  }
}


#####################################
void __cdecl CUniteServer::AddWingLevelUp(CUniteServer *const this, Player *player, int32_t Value)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t OldCount; // [rsp+28h] [rbp-8h]

  if ( player && Value > 0 && CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_WING_LEVEL_UP) )
  {
    OldCount = CUniteServer::GetWingLevelUpRewardCount(this, player);
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1406, Value);
    if ( OldCount != CUniteServer::GetWingLevelUpRewardCount(this, player) )
      CUniteServer::SendIconState(this, player);
  }
}


#####################################
int32_t __cdecl CUniteServer::GetCanXiaoFeiDrawTime(CUniteServer *const this, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int nXiaoFeiSum; // [rsp+10h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+14h] [rbp-Ch]
  int32_t nCanGetTime; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_XIAO_FEI_SUM_DRAW) || !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nXiaoFeiSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1402);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 1403);
  nCanGetTime = 0;
  for ( i = 0; this->m_XiaoFeiDrawSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&this->m_nXiaoFeiDrawValue, i) <= nXiaoFeiSum )
      nCanGetTime = i + 1;
  }
  if ( nCanGetTime - nRewardTimes <= 0 )
    return 0;
  else
    return nCanGetTime - nRewardTimes;
}


#####################################
int32_t __cdecl CUniteServer::GetWingLevelUpRewardCount(CUniteServer *const this, Player *player)
{
  int32_t RewardCount; // [rsp+1Ch] [rbp-24h]
  int UseCount; // [rsp+20h] [rbp-20h]
  int32_t nOldRecord; // [rsp+24h] [rbp-1Ch]
  int32_t i; // [rsp+28h] [rbp-18h]

  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_WING_LEVEL_UP) || !player )
    return 0;
  RewardCount = 0;
  UseCount = Player::getRecord(player, 1406);
  nOldRecord = Player::getRecord(player, 1407);
  for ( i = 0; this->m_nSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&this->m_UseItemCount, i) <= UseCount && (nOldRecord | (1 << i)) != nOldRecord )
      ++RewardCount;
  }
  return RewardCount;
}


#####################################
void __cdecl CUniteServer::GetIconState(CUniteServer *const this, Player *player, IconStateList *const IconList)
{
  CfgData *v3; // rax
  bool v4; // al
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  v3 = Answer::Singleton<CfgData>::instance();
  v4 = !CfgData::isUniteServer(v3) || !player;
  if ( !v4 && this->m_nDay >= this->m_nStartDay && this->m_nDay < this->m_nEndDay )
  {
    CUniteServer::getIconState(&__x, this, player);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CUniteServer::GetSpiderQueenIconState(CUniteServer *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_BOSS) )
  {
    CUniteServer::getSpiderQueenIconState(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CUniteServer::SendIconState(CUniteServer *const this, Player *player)
{
  CfgData *v2; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::isUniteServer(v2) && CUniteServer::IsInUnitServerTime(this) )
    {
      CUniteServer::getIconState(&stu, this, player);
      Player::SendIconState(player, &stu);
    }
  }
}


#####################################
void __cdecl CUniteServer::SendSpiderQueenIconState(CUniteServer *const this)
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
      CUniteServer::getSpiderQueenIconState(&stu, this);
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
void __cdecl CUniteServer::SendUniteServerInfo(CUniteServer *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t Record; // edx
  int32_t v5; // edx
  int8_t v6; // dl
  int32_t v7; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player && CUniteServer::IsInUnitServerTime(this) )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E9Au);
    if ( packet )
    {
      Record = Player::getRecord(player, 1406);
      Answer::NetPacket::writeInt32(packet, Record);
      v5 = Player::getRecord(player, 1407);
      Answer::NetPacket::writeInt32(packet, v5);
      v6 = Player::getRecord(player, 1405);
      Answer::NetPacket::writeInt8(packet, v6);
      v7 = Player::getRecord(player, 1402);
      Answer::NetPacket::writeInt32(packet, v7);
      CUniteServer::appendRechargeInfo(this, packet, player);
      CUniteServer::appendDiscountGiftInfo(this, packet, player);
      CUniteServer::appendHuoYueDuInfo(this, packet, player);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v10 = Player::getConnId(player);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v11, v10, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CUniteServer::BroadcastSpiderQueenKilled(
        CUniteServer *const this,
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
    Answer::NetPacket::writeInt32(packet, this->m_nSpiderQueenKillBroadcast);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, 0, packet);
  }
}


#####################################
bool __cdecl CUniteServer::IsInUnitServerTime(CUniteServer *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  return CfgData::isUniteServer(v1) && this->m_nDay >= this->m_nStartDay && this->m_nDay < this->m_nEndDay;
}


#####################################
bool __cdecl CUniteServer::IsInTime(CUniteServer *const this, Unit_Server_Activity_typ nType)
{
  CfgData *v2; // rax

  v2 = Answer::Singleton<CfgData>::instance();
  return CfgData::isUniteServer(v2) && this->m_nDay >= this->m_vStartDay[nType] && this->m_nDay < this->m_vEndDay[nType];
}


#####################################
int32_t __cdecl CUniteServer::GetRechargeGift(CUniteServer *const this, Player *player, int32_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t TodayPayGold; // ebx
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  int32_t nRewardRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_DAILY_RECHARGE) )
    return 10002;
  if ( nIndex < 0 || this->m_nRechargeDaysSize <= nIndex )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRewardRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2029);
  TodayPayGold = Player::GetTodayPayGold(player);
  if ( TodayPayGold < *std::vector<int>::operator[](&this->m_vRechargeValue, nIndex) )
    return 10002;
  nNewRecord = nRewardRecord | (1 << nIndex);
  if ( nRewardRecord == nNewRecord )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_UNITE_SERVER_RECHARGE_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 2029, nNewRecord);
  CUniteServer::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CUniteServer::BuyDiscountGift(CUniteServer *const this, Player *player, int16_t nIndex)
{
  CfgData *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  int64_t Currency; // rax
  MemChrBagVector *p_vGift; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  CharId_t Cid; // rdx
  int16_t nIndexb; // [rsp+Ch] [rbp-64h]
  std::_Rb_tree_const_iterator<std::pair<const int,CfgBuyGift> > iter; // [rsp+20h] [rbp-50h] BYREF
  int __x; // [rsp+2Ch] [rbp-44h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgBuyGift> > v15; // [rsp+30h] [rbp-40h] BYREF
  std::string name; // [rsp+40h] [rbp-30h] BYREF
  const CfgBuyGiftTable *gifts; // [rsp+48h] [rbp-28h]
  const CfgBuyGift *cfgGifg; // [rsp+50h] [rbp-20h]
  int32_t nOldRecord; // [rsp+58h] [rbp-18h]
  int32_t nNewRecord; // [rsp+5Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_DAILY_LIMIT_SHOP) )
    return 10002;
  nIndexb = nIndex + 1;
  v4 = Answer::Singleton<CfgData>::instance();
  gifts = CfgData::GetBuyGiftTable(v4);
  __x = nIndexb;
  iter._M_node = std::map<int,CfgBuyGift>::find(gifts, &__x)._M_node;
  v15._M_node = std::map<int,CfgBuyGift>::end(gifts)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgBuyGift>>::operator==(&iter, &v15) )
    return 10002;
  cfgGifg = &std::_Rb_tree_const_iterator<std::pair<int const,CfgBuyGift>>::operator->(&iter)->second;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2090);
  nNewRecord = nOldRecord | (1 << nIndexb);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
  if ( Currency < cfgGifg->nGold )
    return 10002;
  p_vGift = &cfgGifg->vGift;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, p_vGift, ITEM_CHANGE_REASON::ICR_UNITE_SERVER_DISTINCT_GIFT) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          cfgGifg->nGold,
          CURRENCY_CHANGE_REASON::GCR_UNITE_SERVER_BUY_DISTINCT_GIFT,
          nIndexb) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 2090, nNewRecord);
  Player::getName((const Player *const)&name);
  Cid = Player::getCid(player);
  CUniteServer::sendBroadcast(this, cfgGifg->nBroad, Cid, &name);
  std::string::~string(&name);
  return 0;
}


#####################################
int32_t __cdecl CUniteServer::GetHuoYueDuGift(CUniteServer *const this, Player *player, int32_t nIndex)
{
  std::vector<MemChrBag> *v4; // rbx
  CExtCharBag *Bag; // rax
  int nHuoYueDu; // [rsp+24h] [rbp-1Ch]
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_HUO_YUE_DU) )
    return 10002;
  if ( nIndex < 0 || this->m_nHuoYueSize <= nIndex )
    return 10002;
  nHuoYueDu = Player::getRecord(player, 2089);
  if ( *std::vector<int>::operator[](&this->m_vHuoYueValue, nIndex) > nHuoYueDu )
    return 10002;
  nOldRecord = Player::getRecord(player, 1068);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  v4 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vHuoYueGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v4, ITEM_CHANGE_REASON::ICR_UNITE_SERVER_HUO_YUE_DU) )
    return 10002;
  Player::updateRecord(player, 1068, nNewRecord);
  CUniteServer::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl CUniteServer::BuyChangeNameCard(CUniteServer *const this, Player *player)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax

  if ( !player )
    return 2;
  if ( Player::getRecord(player, 1405) > 0 )
    return 2;
  Bag = Player::GetBag(player);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  if ( this->m_nPrice <= 0 )
    return 2;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          this->m_nPrice,
          CURRENCY_CHANGE_REASON::GCR_BUY_CHANGE_NAME_CARD,
          0) )
    return 2;
  v4 = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(v4, &this->m_Item, ITEM_CHANGE_REASON::IDCR_BUY_CHANGE_NAME_CARD) )
    return 10002;
  Player::updateRecord(player, 1405, 1);
  return 0;
}


#####################################
int32_t __cdecl CUniteServer::GetWingLevelUpGift(CUniteServer *const this, Player *player, int32_t nIndex)
{
  MemChrBag *v4; // rbx
  CExtCharBag *Bag; // rax
  int UseCount; // [rsp+24h] [rbp-1Ch]
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_WING_LEVEL_UP) )
    return 10002;
  if ( nIndex < 0 || this->m_nSize <= nIndex )
    return 10002;
  UseCount = Player::getRecord(player, 1406);
  if ( *std::vector<int>::operator[](&this->m_UseItemCount, nIndex) > UseCount )
    return 10002;
  nOldRecord = Player::getRecord(player, 1407);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  v4 = std::vector<MemChrBag>::operator[](&this->m_Items, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v4, ITEM_CHANGE_REASON::IDCR_WING_LEVEL_UP) )
    return 10002;
  Player::updateRecord(player, 1407, nNewRecord);
  CUniteServer::SendIconState(this, player);
  return 0;
}


#####################################
bool __cdecl CUniteServer::IsInSpiderQueenTime(CUniteServer *const this)
{
  int32_t m_nMinute; // ebx
  int32_t v3; // ebx
  uint32_t i; // [rsp+1Ch] [rbp-14h]

  if ( !CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_BOSS) )
    return 0;
  for ( i = 0; i < std::vector<TimeArea>::size(&this->m_vSpiderQueenMinute); ++i )
  {
    m_nMinute = this->m_nMinute;
    if ( m_nMinute >= std::vector<TimeArea>::operator[](&this->m_vSpiderQueenMinute, i)->nStartTime )
    {
      v3 = this->m_nMinute;
      if ( v3 < std::vector<TimeArea>::operator[](&this->m_vSpiderQueenMinute, i)->nEndTime )
        return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl CUniteServer::BossDie(CUniteServer *const this, int32_t MonsterId, std::string *p_name, CharId_t Cid)
{
  if ( this->m_MonsterId > 0 && this->m_MonsterId == MonsterId )
  {
    this->m_bDie = 1;
    CUniteServer::BroadcastSpiderQueenKilled(this, p_name, Cid);
    CUniteServer::SendSpiderQueenIconState(this);
  }
}


#####################################
void __cdecl CUniteServer::checkSpiderQueen(CUniteServer *const this)
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
  size_t v15; // rbx
  CfgMapMonster MapMonster; // [rsp+10h] [rbp-70h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+30h] [rbp-50h] BYREF
  uint32_t i; // [rsp+4Ch] [rbp-34h]
  CfgMonster *pMonster; // [rsp+50h] [rbp-30h]
  int32_t MonsterId; // [rsp+5Ch] [rbp-24h]
  Monster *monster; // [rsp+60h] [rbp-20h]
  Map *pMap; // [rsp+68h] [rbp-18h]

  if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_BOSS)
    && !std::vector<TimeArea>::empty(&this->m_vSpiderQueenMinute) )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) == 1 )
    {
      for ( i = 0; ; ++i )
      {
        v15 = i;
        if ( v15 >= std::vector<TimeArea>::size(&this->m_vSpiderQueenMinute) )
          break;
        m_nMinute = this->m_nMinute;
        if ( m_nMinute == std::vector<TimeArea>::operator[](&this->m_vSpiderQueenMinute, i)->nStartTime )
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
            nEndTime = std::vector<TimeArea>::operator[](&this->m_vSpiderQueenMinute, i)->nEndTime;
            v10 = std::vector<TimeArea>::operator[](&this->m_vSpiderQueenMinute, i);
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
          CUniteServer::broadcastSpiderQueenStart(this);
          CUniteServer::SendSpiderQueenIconState(this);
        }
        else
        {
          v13 = this->m_nMinute;
          if ( v13 == std::vector<TimeArea>::operator[](&this->m_vSpiderQueenMinute, i)->nEndTime && !this->m_bDie )
          {
            this->m_bDie = 1;
            CUniteServer::broadcastSpiderQueenEnd(this);
            CUniteServer::SendSpiderQueenIconState(this);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CUniteServer::broadcastSpiderQueenStart(CUniteServer *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_nSpiderQueenStartBroadcast);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CUniteServer::broadcastSpiderQueenEnd(CUniteServer *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_nSpiderQueenEndBroadcast);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CUniteServer::appendRechargeInfo(CUniteServer *const this, Answer::NetPacket *packet, Player *player)
{
  int32_t TodayPayGold; // edx
  CExtOperateLimit *OperateLimit; // rax
  int32_t v5; // ebx
  int8_t nState; // [rsp+23h] [rbp-1Dh]
  int nRewardRecord; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  if ( player )
  {
    TodayPayGold = Player::GetTodayPayGold(player);
    Answer::NetPacket::writeInt32(packet, TodayPayGold);
    Answer::NetPacket::writeInt8(packet, this->m_nRechargeDaysSize);
    OperateLimit = Player::GetOperateLimit(player);
    nRewardRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2029);
    for ( i = 0; this->m_nRechargeDaysSize > i; ++i )
    {
      nState = 0;
      v5 = Player::GetTodayPayGold(player);
      if ( v5 >= *std::vector<int>::operator[](&this->m_vRechargeValue, i) )
      {
        nState = 1;
        if ( ((nRewardRecord >> i) & 1) != 0 )
          nState = 2;
      }
      Answer::NetPacket::writeInt8(packet, nState);
    }
  }
}


#####################################
void __cdecl CUniteServer::appendDiscountGiftInfo(CUniteServer *const this, Answer::NetPacket *packet, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CfgData *v4; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgBuyGift> > iter; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgBuyGift> > __x; // [rsp+30h] [rbp-40h] BYREF
  int32_t nOldRecord; // [rsp+3Ch] [rbp-34h]
  int16_t nCount; // [rsp+42h] [rbp-2Eh]
  uint32_t oldOffset; // [rsp+44h] [rbp-2Ch]
  const CfgBuyGiftTable *gifts; // [rsp+48h] [rbp-28h]
  uint32_t newOffset; // [rsp+54h] [rbp-1Ch]
  int32_t nIndex; // [rsp+58h] [rbp-18h]
  int32_t nNewRecord; // [rsp+5Ch] [rbp-14h]

  if ( packet && player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2090);
    nCount = 0;
    oldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt16(packet, 0);
    v4 = Answer::Singleton<CfgData>::instance();
    gifts = CfgData::GetBuyGiftTable(v4);
    for ( iter._M_node = std::map<int,CfgBuyGift>::begin(gifts)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<int const,CfgBuyGift>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,CfgBuyGift>::end(gifts)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgBuyGift>>::operator!=(&iter, &__x) )
        break;
      nIndex = std::_Rb_tree_const_iterator<std::pair<int const,CfgBuyGift>>::operator->(&iter)->first;
      nNewRecord = nOldRecord | (1 << nIndex);
      if ( nOldRecord == nNewRecord )
      {
        ++nCount;
        Answer::NetPacket::writeInt16(packet, nIndex - 1);
      }
    }
    newOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, oldOffset);
    Answer::NetPacket::writeInt16(packet, nCount);
    Answer::NetPacket::setWOffset(packet, newOffset);
  }
}


#####################################
void __cdecl CUniteServer::appendHuoYueDuInfo(CUniteServer *const this, Answer::NetPacket *packet, Player *player)
{
  int32_t Record; // edx
  CExtOperateLimit *OperateLimit; // rax
  int32_t nOldRecord; // [rsp+24h] [rbp-2Ch]
  int16_t nCount; // [rsp+2Ah] [rbp-26h]
  uint32_t oldOffset; // [rsp+2Ch] [rbp-24h]
  uint32_t newOffset; // [rsp+30h] [rbp-20h]
  int32_t i; // [rsp+34h] [rbp-1Ch]

  if ( packet && player )
  {
    Record = Player::getRecord(player, 2089);
    Answer::NetPacket::writeInt32(packet, Record);
    OperateLimit = Player::GetOperateLimit(player);
    nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1068);
    nCount = 0;
    oldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt16(packet, 0);
    for ( i = 0; this->m_nHuoYueSize > i; ++i )
    {
      if ( nOldRecord == (nOldRecord | (1 << i)) )
      {
        ++nCount;
        Answer::NetPacket::writeInt16(packet, i);
      }
    }
    newOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, oldOffset);
    Answer::NetPacket::writeInt16(packet, nCount);
    Answer::NetPacket::setWOffset(packet, newOffset);
  }
}


#####################################
void __cdecl CUniteServer::sendBroadcast(
        CUniteServer *const this,
        int32_t nBroadId,
        CharId_t cid,
        const std::string *const name)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, nBroadId);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Answer::NetPacket::setProc(packet, 0x2CD6u);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v6, 0, packet);
  }
}


#####################################
int32_t __cdecl CUniteServer::getLeftTime(CUniteServer *const this)
{
  if ( !CUniteServer::IsInUnitServerTime(this) )
    return 0;
  else
    return 86400 * (this->m_nEndDay - this->m_nDay) - 60 * this->m_nMinute;
}


#####################################
void __cdecl CUniteServer::checkMysteryShopRefreshBroad(CUniteServer *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1
    && CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_MYSTERY_SHOP)
    && !(this->m_nMinute % 120) )
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
int32_t __cdecl CUniteServer::GetChouJiangType(CUniteServer *const this)
{
  if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_CHOU_JIANG) )
    return this->m_ChouJiangType;
  else
    return 0;
}


#####################################
int32_t __cdecl CUniteServer::GetChouJiangSpecialTime(CUniteServer *const this)
{
  if ( CUniteServer::IsInTime(this, Unit_Server_Activity_typ::US_CHOU_JIANG) )
    return this->m_ChouJiangCount;
  else
    return 0;
}


