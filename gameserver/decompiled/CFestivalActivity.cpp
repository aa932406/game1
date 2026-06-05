// Decompiled methods for class: CFestivalActivity
// Source: gameserver.cc
// Total methods: 21

#####################################
void __cdecl CFestivalActivity::OnDaySwitch(CFestivalActivity *const this)
{
  CTimer *v1; // rax
  int v2; // ebx
  int nowTime; // [rsp+1Ch] [rbp-14h]

  v1 = Answer::Singleton<CTimer>::instance();
  nowTime = CTimer::GetNow(v1);
  v2 = Answer::DayTime::dayzero(nowTime);
  this->m_nDay = (v2 - Answer::DayTime::dayzero(this->m_nStartDay)) / 86400;
  if ( this->m_nDay == this->m_nEndDay )
    CFestivalActivity::hideIcon(this, this->m_nIcon);
}


#####################################
void __cdecl CFestivalActivity::hideIcon(CFestivalActivity *const this, int32_t nIconId)
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
void __cdecl CFestivalActivity::OnNewMinute(CFestivalActivity *const this, int32_t nMinute)
{
  int32_t m_PlantId; // ebx
  CfgData *v3; // rax
  MapPos *M_current; // rbx
  __gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> > v5; // rax
  int32_t m_PlantCount; // eax
  MapId_t m_MapId; // ebx
  MapManager *v8; // rax
  Plant *v9; // rbx
  int32_t m_NpcId; // ebx
  CfgData *v11; // rax
  MapPos *v12; // rbx
  __gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> > v13; // rax
  int32_t m_NpcCount; // eax
  MapId_t v15; // ebx
  MapManager *v16; // rax
  Npc *v17; // rbx
  int32_t v18; // eax
  int32_t y; // r12d
  MapPos *v20; // rax
  CfgMapPlant stu; // [rsp+10h] [rbp-80h] BYREF
  int32_t nLeftTime; // [rsp+2Ch] [rbp-64h]
  CfgPlant *pCfgPlant; // [rsp+30h] [rbp-60h]
  CfgNpc *pCfgNpc; // [rsp+38h] [rbp-58h]
  int32_t nFreshCount; // [rsp+40h] [rbp-50h]
  int32_t i; // [rsp+44h] [rbp-4Ch]
  Map *pMap; // [rsp+48h] [rbp-48h]
  Plant *plant; // [rsp+50h] [rbp-40h]
  int32_t nFreshCount_0; // [rsp+58h] [rbp-38h]
  int32_t i_0; // [rsp+5Ch] [rbp-34h]
  Map *pMap_0; // [rsp+60h] [rbp-30h]
  Npc *npc; // [rsp+68h] [rbp-28h]

  this->m_nMinute = nMinute;
  nLeftTime = CFestivalActivity::getLeftTime(this);
  if ( nLeftTime > 0 && !this->m_nDay && !nMinute )
  {
    m_PlantId = this->m_PlantId;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfgPlant = CfgData::getPlant(v3, m_PlantId);
    if ( pCfgPlant )
    {
      M_current = std::vector<MapPos>::end(&this->m_PlantMapPosVt)._M_current;
      v5._M_current = std::vector<MapPos>::begin(&this->m_PlantMapPosVt)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<MapPos *,std::vector<MapPos>>>(
        v5,
        (__gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> >)M_current);
      if ( (int)std::vector<MapPos>::size(&this->m_PlantMapPosVt) <= this->m_PlantCount )
        m_PlantCount = std::vector<MapPos>::size(&this->m_PlantMapPosVt);
      else
        m_PlantCount = this->m_PlantCount;
      nFreshCount = m_PlantCount;
      for ( i = 0; i < nFreshCount; ++i )
      {
        m_MapId = std::vector<MapPos>::operator[](&this->m_PlantMapPosVt, i)->m_MapId;
        v8 = Answer::Singleton<MapManager>::instance();
        pMap = MapManager::GetMap(v8, m_MapId);
        v9 = (Plant *)operator new(0xE0u);
        Plant::Plant(v9);
        plant = v9;
        if ( v9 && pMap )
        {
          *(_QWORD *)&stu.mapid = 0;
          *(_QWORD *)&stu.x = 0;
          stu.mapid = std::vector<MapPos>::operator[](&this->m_PlantMapPosVt, i)->m_MapId;
          stu.plantid = this->m_PlantId;
          stu.x = std::vector<MapPos>::operator[](&this->m_PlantMapPosVt, i)->m_Pos.x;
          stu.y = std::vector<MapPos>::operator[](&this->m_PlantMapPosVt, i)->m_Pos.y;
          Plant::init(plant, pMap, pCfgPlant, &stu, 0);
          Plant::setLifeTime(plant, nLeftTime);
          Map::addPlant(pMap, plant);
        }
      }
    }
    m_NpcId = this->m_NpcId;
    v11 = Answer::Singleton<CfgData>::instance();
    pCfgNpc = CfgData::getNpc(v11, m_NpcId);
    if ( pCfgNpc )
    {
      v12 = std::vector<MapPos>::end(&this->m_NpcMapPosVt)._M_current;
      v13._M_current = std::vector<MapPos>::begin(&this->m_NpcMapPosVt)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<MapPos *,std::vector<MapPos>>>(
        v13,
        (__gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> >)v12);
      if ( (int)std::vector<MapPos>::size(&this->m_NpcMapPosVt) <= this->m_NpcCount )
        m_NpcCount = std::vector<MapPos>::size(&this->m_NpcMapPosVt);
      else
        m_NpcCount = this->m_NpcCount;
      nFreshCount_0 = m_NpcCount;
      for ( i_0 = 0; i_0 < nFreshCount_0; ++i_0 )
      {
        v15 = std::vector<MapPos>::operator[](&this->m_NpcMapPosVt, i_0)->m_MapId;
        v16 = Answer::Singleton<MapManager>::instance();
        pMap_0 = MapManager::GetMap(v16, v15);
        v17 = (Npc *)operator new(0x4E8u);
        Npc::Npc(v17);
        npc = v17;
        if ( v17 )
        {
          if ( pMap_0 )
          {
            v18 = Answer::DayTime::now();
            Npc::init(npc, pCfgNpc, nLeftTime + v18);
            y = std::vector<MapPos>::operator[](&this->m_NpcMapPosVt, i_0)->m_Pos.y;
            v20 = std::vector<MapPos>::operator[](&this->m_NpcMapPosVt, i_0);
            Map::addNpc(pMap_0, npc, v20->m_Pos.x, y);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CFestivalActivity::Init(CFestivalActivity *const this)
{
  CTimer *v1; // rax
  tm nowTime; // [rsp+10h] [rbp-40h] BYREF
  int32_t nVersion; // [rsp+4Ch] [rbp-4h]

  CFestivalActivity::initCfgData(this);
  nVersion = CFestivalActivity::loadVersion(this);
  if ( nVersion > 0 && this->m_nVersion != nVersion || !nVersion )
    CFestivalActivity::saveVersion(this);
  v1 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&nowTime, v1);
  this->m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
}


#####################################
void __cdecl CFestivalActivity::initCfgData(CFestivalActivity *const this)
{
  int32_t v1; // eax
  int v2; // ebx
  const std::string *v4; // rbx
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  int32_t m_PlantId; // ebx
  CfgData *v12; // rax
  MapPos *M_current; // rbx
  __gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> > v14; // rax
  int32_t m_PlantCount; // eax
  MapId_t m_MapId; // ebx
  MapManager *v17; // rax
  Plant *v18; // rbx
  CFestivalActivity *v19; // rbx
  CFestivalActivity *v20; // rbx
  size_t v22; // rbx
  std::vector<std::string> *v23; // rax
  std::string *v24; // rbx
  size_t v25; // r12
  std::vector<std::string> *v26; // rax
  std::string *v27; // rax
  int IntValue; // eax
  int v29; // eax
  int32_t v30; // eax
  int32_t v31; // eax
  const std::string *v33; // rbx
  std::string *v34; // rax
  const char *v35; // rax
  std::string *v36; // rax
  const char *v37; // rax
  std::string *v38; // rax
  const char *v39; // rax
  int32_t m_NpcId; // ebx
  CfgData *v41; // rax
  MapPos *v42; // rbx
  __gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> > v43; // rax
  int32_t v44; // eax
  int32_t m_NpcCount; // eax
  MapId_t v46; // ebx
  MapManager *v47; // rax
  Npc *v48; // rbx
  int32_t v49; // eax
  int32_t y; // r12d
  MapPos *v51; // rax
  int v52; // eax
  int v53; // eax
  int32_t v54; // eax
  int v55; // eax
  int v56; // eax
  int32_t v57; // eax
  ChangeItemCfg *v58; // rax
  MemChrBag v59; // [rsp+0h] [rbp-840h] BYREF
  CFestivalActivity *thisa; // [rsp+28h] [rbp-818h]
  char szCol[64]; // [rsp+30h] [rbp-810h] BYREF
  ChangeItemCfg stu_0; // [rsp+70h] [rbp-7D0h] BYREF
  Answer::Inifile ini; // [rsp+B0h] [rbp-790h] BYREF
  MapPos stuPos_0; // [rsp+F0h] [rbp-750h] BYREF
  StringVector vstr_0; // [rsp+100h] [rbp-740h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin_0; // [rsp+120h] [rbp-720h] BYREF
  StringVector SplitStr_1; // [rsp+130h] [rbp-710h] BYREF
  std::string MapPosString_0; // [rsp+150h] [rbp-6F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+160h] [rbp-6E0h] BYREF
  StringVector SplitStr_0; // [rsp+170h] [rbp-6D0h] BYREF
  std::string DaAnString; // [rsp+190h] [rbp-6B0h] BYREF
  CfgMapPlant stu; // [rsp+1A0h] [rbp-6A0h] BYREF
  MapPos stuPos; // [rsp+1B0h] [rbp-690h] BYREF
  StringVector vstr; // [rsp+1C0h] [rbp-680h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+1E0h] [rbp-660h] BYREF
  StringVector SplitStr; // [rsp+1F0h] [rbp-650h] BYREF
  std::string MapPosString; // [rsp+210h] [rbp-630h] BYREF
  std::string file; // [rsp+220h] [rbp-620h] BYREF
  char v79; // [rsp+22Fh] [rbp-611h] BYREF
  std::string key; // [rsp+230h] [rbp-610h] BYREF
  char v81; // [rsp+23Fh] [rbp-601h] BYREF
  std::string section; // [rsp+240h] [rbp-600h] BYREF
  char v83; // [rsp+24Fh] [rbp-5F1h] BYREF
  Answer::Inifile v84; // [rsp+250h] [rbp-5F0h] BYREF
  char v85; // [rsp+28Fh] [rbp-5B1h] BYREF
  std::string v86; // [rsp+290h] [rbp-5B0h] BYREF
  char v87; // [rsp+29Fh] [rbp-5A1h] BYREF
  std::string v88; // [rsp+2A0h] [rbp-5A0h] BYREF
  char v89; // [rsp+2AFh] [rbp-591h] BYREF
  std::string v90; // [rsp+2B0h] [rbp-590h] BYREF
  char v91; // [rsp+2BFh] [rbp-581h] BYREF
  Answer::Inifile v92; // [rsp+2C0h] [rbp-580h] BYREF
  char v93; // [rsp+2FFh] [rbp-541h] BYREF
  std::string v94; // [rsp+300h] [rbp-540h] BYREF
  char v95; // [rsp+30Fh] [rbp-531h] BYREF
  std::string v96; // [rsp+310h] [rbp-530h] BYREF
  char v97; // [rsp+31Fh] [rbp-521h] BYREF
  std::string v98; // [rsp+320h] [rbp-520h] BYREF
  char v99; // [rsp+32Fh] [rbp-511h] BYREF
  std::string v100; // [rsp+330h] [rbp-510h] BYREF
  char v101; // [rsp+33Fh] [rbp-501h] BYREF
  std::string v102; // [rsp+340h] [rbp-500h] BYREF
  char v103; // [rsp+34Fh] [rbp-4F1h] BYREF
  std::string v104; // [rsp+350h] [rbp-4F0h] BYREF
  char v105; // [rsp+35Fh] [rbp-4E1h] BYREF
  std::string v106; // [rsp+360h] [rbp-4E0h] BYREF
  char v107; // [rsp+36Fh] [rbp-4D1h] BYREF
  _BYTE v108[15]; // [rsp+370h] [rbp-4D0h] BYREF
  char v109; // [rsp+37Fh] [rbp-4C1h] BYREF
  std::string v110; // [rsp+380h] [rbp-4C0h] BYREF
  char v111; // [rsp+38Fh] [rbp-4B1h] BYREF
  std::string delims; // [rsp+390h] [rbp-4B0h] BYREF
  char v113; // [rsp+39Fh] [rbp-4A1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+3A0h] [rbp-4A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+3B0h] [rbp-490h] BYREF
  std::string v116; // [rsp+3C0h] [rbp-480h] BYREF
  char v117; // [rsp+3CFh] [rbp-471h] BYREF
  Position v118; // [rsp+3D0h] [rbp-470h] BYREF
  std::string v119; // [rsp+3E0h] [rbp-460h] BYREF
  char v120; // [rsp+3EFh] [rbp-451h] BYREF
  std::string v121; // [rsp+3F0h] [rbp-450h] BYREF
  char v122; // [rsp+3FFh] [rbp-441h] BYREF
  std::string v123; // [rsp+400h] [rbp-440h] BYREF
  char v124; // [rsp+40Fh] [rbp-431h] BYREF
  std::string v125; // [rsp+410h] [rbp-430h] BYREF
  char v126; // [rsp+41Fh] [rbp-421h] BYREF
  std::string v127; // [rsp+420h] [rbp-420h] BYREF
  char v128; // [rsp+42Fh] [rbp-411h] BYREF
  std::string v129; // [rsp+430h] [rbp-410h] BYREF
  char v130; // [rsp+43Fh] [rbp-401h] BYREF
  Answer::Inifile v131; // [rsp+440h] [rbp-400h] BYREF
  _BYTE v132[15]; // [rsp+480h] [rbp-3C0h] BYREF
  char v133; // [rsp+48Fh] [rbp-3B1h] BYREF
  std::string v134; // [rsp+490h] [rbp-3B0h] BYREF
  char v135; // [rsp+49Fh] [rbp-3A1h] BYREF
  std::vector<std::string> p___x; // [rsp+4A0h] [rbp-3A0h] BYREF
  _BYTE v137[15]; // [rsp+4C0h] [rbp-380h] BYREF
  char v138; // [rsp+4CFh] [rbp-371h] BYREF
  std::string v139; // [rsp+4D0h] [rbp-370h] BYREF
  char v140; // [rsp+4DFh] [rbp-361h] BYREF
  std::string v141; // [rsp+4E0h] [rbp-360h] BYREF
  char v142; // [rsp+4EFh] [rbp-351h] BYREF
  std::string v143; // [rsp+4F0h] [rbp-350h] BYREF
  std::string v144; // [rsp+500h] [rbp-340h] BYREF
  char v145; // [rsp+50Fh] [rbp-331h] BYREF
  std::string v146; // [rsp+510h] [rbp-330h] BYREF
  char v147; // [rsp+51Fh] [rbp-321h] BYREF
  std::string v148; // [rsp+520h] [rbp-320h] BYREF
  char v149; // [rsp+52Fh] [rbp-311h] BYREF
  std::string v150; // [rsp+530h] [rbp-310h] BYREF
  char v151; // [rsp+53Fh] [rbp-301h] BYREF
  std::string v152; // [rsp+540h] [rbp-300h] BYREF
  char v153; // [rsp+54Fh] [rbp-2F1h] BYREF
  std::string v154; // [rsp+550h] [rbp-2F0h] BYREF
  char v155; // [rsp+55Fh] [rbp-2E1h] BYREF
  std::string v156; // [rsp+560h] [rbp-2E0h] BYREF
  char v157; // [rsp+56Fh] [rbp-2D1h] BYREF
  std::string v158; // [rsp+570h] [rbp-2D0h] BYREF
  char v159; // [rsp+57Fh] [rbp-2C1h] BYREF
  _BYTE v160[15]; // [rsp+580h] [rbp-2C0h] BYREF
  char v161; // [rsp+58Fh] [rbp-2B1h] BYREF
  std::string v162; // [rsp+590h] [rbp-2B0h] BYREF
  char v163; // [rsp+59Fh] [rbp-2A1h] BYREF
  std::string v164; // [rsp+5A0h] [rbp-2A0h] BYREF
  char v165; // [rsp+5AFh] [rbp-291h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v166; // [rsp+5B0h] [rbp-290h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v167; // [rsp+5C0h] [rbp-280h] BYREF
  std::string v168; // [rsp+5D0h] [rbp-270h] BYREF
  char v169; // [rsp+5DFh] [rbp-261h] BYREF
  Position v170; // [rsp+5E0h] [rbp-260h] BYREF
  std::string v171; // [rsp+5F0h] [rbp-250h] BYREF
  char v172; // [rsp+5FFh] [rbp-241h] BYREF
  std::string v173; // [rsp+600h] [rbp-240h] BYREF
  char v174; // [rsp+60Fh] [rbp-231h] BYREF
  std::string v175; // [rsp+610h] [rbp-230h] BYREF
  char v176; // [rsp+61Fh] [rbp-221h] BYREF
  std::string v177; // [rsp+620h] [rbp-220h] BYREF
  char v178; // [rsp+62Fh] [rbp-211h] BYREF
  std::string v179; // [rsp+630h] [rbp-210h] BYREF
  char v180; // [rsp+63Fh] [rbp-201h] BYREF
  std::string v181; // [rsp+640h] [rbp-200h] BYREF
  char v182; // [rsp+64Fh] [rbp-1F1h] BYREF
  std::string v183; // [rsp+650h] [rbp-1F0h] BYREF
  char v184; // [rsp+65Fh] [rbp-1E1h] BYREF
  std::string v185; // [rsp+660h] [rbp-1E0h] BYREF
  char v186; // [rsp+66Fh] [rbp-1D1h] BYREF
  std::string v187; // [rsp+670h] [rbp-1D0h] BYREF
  char v188; // [rsp+67Fh] [rbp-1C1h] BYREF
  std::string v189; // [rsp+680h] [rbp-1C0h] BYREF
  char v190; // [rsp+68Fh] [rbp-1B1h] BYREF
  std::string v191; // [rsp+690h] [rbp-1B0h] BYREF
  char v192; // [rsp+69Fh] [rbp-1A1h] BYREF
  std::string v193; // [rsp+6A0h] [rbp-1A0h] BYREF
  char v194; // [rsp+6AFh] [rbp-191h] BYREF
  ChangeItemCfg v195; // [rsp+6B0h] [rbp-190h] BYREF
  std::list<ItemData> strItems; // [rsp+6F0h] [rbp-150h] BYREF
  Answer::Inifile v197; // [rsp+700h] [rbp-140h] BYREF
  char v198; // [rsp+73Fh] [rbp-101h] BYREF
  std::string v199; // [rsp+740h] [rbp-100h] BYREF
  char v200; // [rsp+74Fh] [rbp-F1h] BYREF
  MemChrBagVector __x; // [rsp+750h] [rbp-F0h] BYREF
  Answer::Inifile v202; // [rsp+770h] [rbp-D0h] BYREF
  char v203; // [rsp+7AFh] [rbp-91h] BYREF
  std::string v204; // [rsp+7B0h] [rbp-90h] BYREF
  char v205; // [rsp+7BBh] [rbp-85h] BYREF
  int32_t nLeftTime; // [rsp+7BCh] [rbp-84h]
  CfgPlant *pCfgPlant; // [rsp+7C0h] [rbp-80h]
  int32_t nFreshCount; // [rsp+7C8h] [rbp-78h]
  int32_t i; // [rsp+7CCh] [rbp-74h]
  Map *pMap; // [rsp+7D0h] [rbp-70h]
  Plant *plant; // [rsp+7D8h] [rbp-68h]
  int32_t nDay; // [rsp+7E4h] [rbp-5Ch]
  int32_t i_0; // [rsp+7E8h] [rbp-58h]
  int32_t nSize; // [rsp+7ECh] [rbp-54h]
  int32_t j; // [rsp+7F0h] [rbp-50h]
  int32_t nLeftTime_0; // [rsp+7F4h] [rbp-4Ch]
  CfgNpc *pCfgNpc; // [rsp+7F8h] [rbp-48h]
  int32_t nFreshCount_0; // [rsp+800h] [rbp-40h]
  int32_t i_1; // [rsp+804h] [rbp-3Ch]
  Map *pMap_0; // [rsp+808h] [rbp-38h]
  Npc *npc; // [rsp+810h] [rbp-30h]
  int32_t i_2; // [rsp+81Ch] [rbp-24h]

  thisa = this;
  bzero(this->m_vStartDay, 0x18u);
  bzero(this->m_vEndDay, 0x18u);
  Answer::Inifile::Inifile(&ini);
  std::allocator<char>::allocator(&v79);
  std::string::string(&file, "./ServerConfig/Tables/FestivalActivity.cfg", &v79);
  Answer::Inifile::parse(&ini, &file);
  std::string::~string(&file);
  std::allocator<char>::~allocator(&v79);
  memset(szCol, 0, sizeof(szCol));
  std::allocator<char>::allocator(&v81);
  std::string::string(&key, "version", &v81);
  std::allocator<char>::allocator(&v83);
  std::string::string(&section, "CONFIG", &v83);
  this->m_nVersion = Answer::Inifile::getIntValue(&ini, &section, &key);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v83);
  std::string::~string(&key);
  std::allocator<char>::~allocator(&v81);
  std::allocator<char>::allocator((char *)&v84.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::string::string(
    &v84.m_strMap._M_t._M_impl._M_header._M_parent,
    "start_time",
    (char *)&v84.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::allocator<char>::allocator((char *)&v84.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::string(
    &v84.m_strMap._M_t._M_impl._M_header._M_right,
    "CONFIG",
    (char *)&v84.m_strMap._M_t._M_impl._M_node_count + 7);
  Answer::Inifile::getStrValue(
    &v84,
    (const std::string *const)&ini,
    (const std::string *const)&v84.m_strMap._M_t._M_impl._M_header._M_right);
  thisa->m_nStartDay = Answer::DayTime::StringToIntTime((std::string *)&v84);
  std::string::~string(&v84);
  std::string::~string(&v84.m_strMap._M_t._M_impl._M_header._M_right);
  std::allocator<char>::~allocator((char *)&v84.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::~string(&v84.m_strMap._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v84.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::allocator<char>::allocator(&v85);
  std::string::string(&v84.m_currentSection, "end_day", &v85);
  std::allocator<char>::allocator(&v87);
  std::string::string(&v86, "CONFIG", &v87);
  thisa->m_nEndDay = Answer::Inifile::getIntValue(&ini, &v86, &v84.m_currentSection);
  std::string::~string(&v86);
  std::allocator<char>::~allocator(&v87);
  std::string::~string(&v84.m_currentSection);
  std::allocator<char>::~allocator(&v85);
  std::allocator<char>::allocator(&v89);
  std::string::string(&v88, "icon", &v89);
  std::allocator<char>::allocator(&v91);
  std::string::string(&v90, "CONFIG", &v91);
  thisa->m_nIcon = Answer::Inifile::getIntValue(&ini, &v90, &v88);
  std::string::~string(&v90);
  std::allocator<char>::~allocator(&v91);
  std::string::~string(&v88);
  std::allocator<char>::~allocator(&v89);
  std::allocator<char>::allocator((char *)&v92.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::string::string(
    &v92.m_strMap._M_t._M_impl._M_header._M_parent,
    "open",
    (char *)&v92.m_strMap._M_t._M_impl._M_header._M_left + 7);
  std::allocator<char>::allocator((char *)&v92.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::string(
    &v92.m_strMap._M_t._M_impl._M_header._M_right,
    "CONFIG",
    (char *)&v92.m_strMap._M_t._M_impl._M_node_count + 7);
  Answer::Inifile::getStrValue(
    &v92,
    (const std::string *const)&ini,
    (const std::string *const)&v92.m_strMap._M_t._M_impl._M_header._M_right);
  CFestivalActivity::initOpenList(thisa, (const std::string *const)&v92);
  std::string::~string(&v92);
  std::string::~string(&v92.m_strMap._M_t._M_impl._M_header._M_right);
  std::allocator<char>::~allocator((char *)&v92.m_strMap._M_t._M_impl._M_node_count + 7);
  std::string::~string(&v92.m_strMap._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v92.m_strMap._M_t._M_impl._M_header._M_left + 7);
  v1 = Answer::DayTime::now();
  v2 = Answer::DayTime::dayzero(v1);
  thisa->m_nDay = (v2 - Answer::DayTime::dayzero(thisa->m_nStartDay)) / 86400;
  if ( CFestivalActivity::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE_2::FAT2_COLLECTION) )
  {
    std::allocator<char>::allocator(&v93);
    std::string::string(&v92.m_currentSection, "start_day", &v93);
    std::allocator<char>::allocator(&v95);
    std::string::string(&v94, "COLLECTION", &v95);
    thisa->m_vStartDay[1] = Answer::Inifile::getIntValue(&ini, &v94, &v92.m_currentSection);
    std::string::~string(&v94);
    std::allocator<char>::~allocator(&v95);
    std::string::~string(&v92.m_currentSection);
    std::allocator<char>::~allocator(&v93);
    std::allocator<char>::allocator(&v97);
    std::string::string(&v96, "end_day", &v97);
    std::allocator<char>::allocator(&v99);
    std::string::string(&v98, "COLLECTION", &v99);
    thisa->m_vEndDay[1] = Answer::Inifile::getIntValue(&ini, &v98, &v96);
    std::string::~string(&v98);
    std::allocator<char>::~allocator(&v99);
    std::string::~string(&v96);
    std::allocator<char>::~allocator(&v97);
    std::allocator<char>::allocator(&v101);
    std::string::string(&v100, "plant", &v101);
    std::allocator<char>::allocator(&v103);
    std::string::string(&v102, "COLLECTION", &v103);
    thisa->m_PlantId = Answer::Inifile::getIntValue(&ini, &v102, &v100);
    std::string::~string(&v102);
    std::allocator<char>::~allocator(&v103);
    std::string::~string(&v100);
    std::allocator<char>::~allocator(&v101);
    std::allocator<char>::allocator(&v105);
    std::string::string(&v104, "count", &v105);
    std::allocator<char>::allocator(&v107);
    std::string::string(&v106, "COLLECTION", &v107);
    thisa->m_PlantCount = Answer::Inifile::getIntValue(&ini, &v106, &v104);
    std::string::~string(&v106);
    std::allocator<char>::~allocator(&v107);
    std::string::~string(&v104);
    std::allocator<char>::~allocator(&v105);
    std::allocator<char>::allocator(&v109);
    std::string::string(v108, "map", &v109);
    std::allocator<char>::allocator(&v111);
    std::string::string(&v110, "COLLECTION", &v111);
    Answer::Inifile::getStrValue((Answer::Inifile *const)&MapPosString, (const std::string *const)&ini, &v110);
    std::string::~string(&v110);
    std::allocator<char>::~allocator(&v111);
    std::string::~string(v108);
    std::allocator<char>::~allocator(&v109);
    if ( std::operator!=<char>(&MapPosString, &_lhs) && std::operator!=<char>(&MapPosString, "-1") )
    {
      std::allocator<char>::allocator(&v113);
      std::string::string(&delims, "|", &v113);
      Answer::StringUtility::split(&SplitStr, &MapPosString, &delims, 0);
      std::string::~string(&delims);
      std::allocator<char>::~allocator(&v113);
      __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iterBegin,
        &__i);
      while ( 1 )
      {
        __rhs._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &__rhs) )
          break;
        std::allocator<char>::allocator(&v117);
        std::string::string(&v116, ":", &v117);
        v4 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
        Answer::StringUtility::split(&vstr, v4, &v116, 0);
        std::string::~string(&v116);
        std::allocator<char>::~allocator(&v117);
        if ( std::vector<std::string>::size(&vstr) == 3 )
        {
          Position::Position(&v118, 0, 0);
          stuPos.m_MapId = 0;
          stuPos.m_Pos = v118;
          v5 = std::vector<std::string>::operator[](&vstr, 0);
          v6 = (const char *)std::string::c_str(v5);
          stuPos.m_MapId = atoi(v6);
          v7 = std::vector<std::string>::operator[](&vstr, 1u);
          v8 = (const char *)std::string::c_str(v7);
          stuPos.m_Pos.x = atoi(v8);
          v9 = std::vector<std::string>::operator[](&vstr, 2u);
          v10 = (const char *)std::string::c_str(v9);
          stuPos.m_Pos.y = atoi(v10);
          std::vector<MapPos>::push_back(&thisa->m_PlantMapPosVt, &stuPos);
        }
        std::vector<std::string>::~vector(&vstr);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
      }
      std::vector<std::string>::~vector(&SplitStr);
    }
    std::allocator<char>::allocator(&v120);
    std::string::string(&v119, "time", &v120);
    std::allocator<char>::allocator(&v122);
    std::string::string(&v121, "COLLECTION", &v122);
    thisa->m_Times = Answer::Inifile::getIntValue(&ini, &v121, &v119);
    std::string::~string(&v121);
    std::allocator<char>::~allocator(&v122);
    std::string::~string(&v119);
    std::allocator<char>::~allocator(&v120);
    nLeftTime = CFestivalActivity::getLeftTime(thisa);
    if ( nLeftTime > 0 )
    {
      m_PlantId = thisa->m_PlantId;
      v12 = Answer::Singleton<CfgData>::instance();
      pCfgPlant = CfgData::getPlant(v12, m_PlantId);
      if ( pCfgPlant )
      {
        M_current = std::vector<MapPos>::end(&thisa->m_PlantMapPosVt)._M_current;
        v14._M_current = std::vector<MapPos>::begin(&thisa->m_PlantMapPosVt)._M_current;
        std::random_shuffle<__gnu_cxx::__normal_iterator<MapPos *,std::vector<MapPos>>>(
          v14,
          (__gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> >)M_current);
        if ( (int)std::vector<MapPos>::size(&thisa->m_PlantMapPosVt) <= thisa->m_PlantCount )
          m_PlantCount = std::vector<MapPos>::size(&thisa->m_PlantMapPosVt);
        else
          m_PlantCount = thisa->m_PlantCount;
        nFreshCount = m_PlantCount;
        for ( i = 0; i < nFreshCount; ++i )
        {
          m_MapId = std::vector<MapPos>::operator[](&thisa->m_PlantMapPosVt, i)->m_MapId;
          v17 = Answer::Singleton<MapManager>::instance();
          pMap = MapManager::GetMap(v17, m_MapId);
          v18 = (Plant *)operator new(0xE0u);
          Plant::Plant(v18);
          plant = v18;
          if ( v18 && pMap )
          {
            *(_QWORD *)&stu.mapid = 0;
            *(_QWORD *)&stu.x = 0;
            stu.mapid = std::vector<MapPos>::operator[](&thisa->m_PlantMapPosVt, i)->m_MapId;
            stu.plantid = thisa->m_PlantId;
            stu.x = std::vector<MapPos>::operator[](&thisa->m_PlantMapPosVt, i)->m_Pos.x;
            stu.y = std::vector<MapPos>::operator[](&thisa->m_PlantMapPosVt, i)->m_Pos.y;
            Plant::init(plant, pMap, pCfgPlant, &stu, 0);
            Plant::setLifeTime(plant, nLeftTime);
            Map::addPlant(pMap, plant);
          }
        }
      }
    }
    std::string::~string(&MapPosString);
  }
  if ( CFestivalActivity::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DA_TI) )
  {
    std::allocator<char>::allocator(&v124);
    std::string::string(&v123, "start_day", &v124);
    std::allocator<char>::allocator(&v126);
    std::string::string(&v125, "DATI", &v126);
    thisa->m_vStartDay[2] = Answer::Inifile::getIntValue(&ini, &v125, &v123);
    std::string::~string(&v125);
    std::allocator<char>::~allocator(&v126);
    std::string::~string(&v123);
    std::allocator<char>::~allocator(&v124);
    std::allocator<char>::allocator(&v128);
    std::string::string(&v127, "end_day", &v128);
    std::allocator<char>::allocator(&v130);
    std::string::string(&v129, "DATI", &v130);
    thisa->m_vEndDay[2] = Answer::Inifile::getIntValue(&ini, &v129, &v127);
    std::string::~string(&v129);
    std::allocator<char>::~allocator(&v130);
    std::string::~string(&v127);
    std::allocator<char>::~allocator(&v128);
    std::allocator<char>::allocator((char *)&v131.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(
      &v131.m_strMap._M_t._M_impl._M_header._M_parent,
      "gift_day",
      (char *)&v131.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator((char *)&v131.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(
      &v131.m_strMap._M_t._M_impl._M_header._M_right,
      "DATI",
      (char *)&v131.m_strMap._M_t._M_impl._M_node_count + 7);
    Answer::Inifile::getStrValue(
      &v131,
      (const std::string *const)&ini,
      (const std::string *const)&v131.m_strMap._M_t._M_impl._M_header._M_right);
    v19 = thisa;
    CItemHelper::parseItemString(&v59, (const std::string *const)&v131);
    v19->m_DayGift = v59;
    std::string::~string(&v131);
    std::string::~string(&v131.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v131.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v131.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v131.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator(&v133);
    std::string::string(v132, "gift_act", &v133);
    std::allocator<char>::allocator(&v135);
    std::string::string(&v134, "DATI", &v135);
    Answer::Inifile::getStrValue((Answer::Inifile *const)&v131.m_currentSection, (const std::string *const)&ini, &v134);
    v20 = thisa;
    CItemHelper::parseItemString(&v59, &v131.m_currentSection);
    v20->m_ActGift = v59;
    std::string::~string(&v131.m_currentSection);
    std::string::~string(&v134);
    std::allocator<char>::~allocator(&v135);
    std::string::~string(v132);
    std::allocator<char>::~allocator(&v133);
    nDay = thisa->m_vEndDay[2] - thisa->m_vStartDay[2];
    if ( nDay > 0 )
    {
      std::vector<std::string>::vector(&p___x);
      std::vector<std::vector<std::string>>::resize(&thisa->m_StringVtVector, nDay, &p___x);
      std::vector<std::string>::~vector(&p___x);
      for ( i_0 = 0; i_0 < nDay; ++i_0 )
      {
        snprintf(szCol, 0x3Fu, "da_an%d", i_0 + 1);
        std::allocator<char>::allocator(&v138);
        std::string::string(v137, szCol, &v138);
        std::allocator<char>::allocator(&v140);
        std::string::string(&v139, "DATI", &v140);
        Answer::Inifile::getStrValue((Answer::Inifile *const)&DaAnString, (const std::string *const)&ini, &v139);
        std::string::~string(&v139);
        std::allocator<char>::~allocator(&v140);
        std::string::~string(v137);
        std::allocator<char>::~allocator(&v138);
        if ( std::operator!=<char>(&DaAnString, &_lhs) && std::operator!=<char>(&DaAnString, "-1") )
        {
          std::allocator<char>::allocator(&v142);
          std::string::string(&v141, "|", &v142);
          Answer::StringUtility::split(&SplitStr_0, &DaAnString, &v141, 0);
          std::string::~string(&v141);
          std::allocator<char>::~allocator(&v142);
          nSize = std::vector<std::string>::size(&SplitStr_0);
          if ( nSize > 0 )
          {
            std::string::string(&v143);
            v22 = nSize;
            v23 = std::vector<std::vector<std::string>>::operator[](&thisa->m_StringVtVector, i_0);
            std::vector<std::string>::resize(v23, v22, &v143);
            std::string::~string(&v143);
            it._M_current = std::vector<std::string>::begin(&SplitStr_0)._M_current;
            for ( j = 0; j < nSize; ++j )
            {
              v24 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
              v25 = j;
              v26 = std::vector<std::vector<std::string>>::operator[](&thisa->m_StringVtVector, i_0);
              v27 = std::vector<std::string>::operator[](v26, v25);
              std::string::operator=(v27, v24);
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it, 0);
            }
          }
          std::vector<std::string>::~vector(&SplitStr_0);
        }
        std::string::~string(&DaAnString);
      }
    }
  }
  if ( CFestivalActivity::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE_2::FAT2_NPC) )
  {
    std::allocator<char>::allocator(&v145);
    std::string::string(&v144, "start_day", &v145);
    std::allocator<char>::allocator(&v147);
    std::string::string(&v146, "NPC", &v147);
    IntValue = Answer::Inifile::getIntValue(&ini, &v146, &v144);
    thisa->m_vStartDay[3] = IntValue;
    std::string::~string(&v146);
    std::allocator<char>::~allocator(&v147);
    std::string::~string(&v144);
    std::allocator<char>::~allocator(&v145);
    std::allocator<char>::allocator(&v149);
    std::string::string(&v148, "end_day", &v149);
    std::allocator<char>::allocator(&v151);
    std::string::string(&v150, "NPC", &v151);
    v29 = Answer::Inifile::getIntValue(&ini, &v150, &v148);
    thisa->m_vEndDay[3] = v29;
    std::string::~string(&v150);
    std::allocator<char>::~allocator(&v151);
    std::string::~string(&v148);
    std::allocator<char>::~allocator(&v149);
    std::allocator<char>::allocator(&v153);
    std::string::string(&v152, "npcid", &v153);
    std::allocator<char>::allocator(&v155);
    std::string::string(&v154, "NPC", &v155);
    v30 = Answer::Inifile::getIntValue(&ini, &v154, &v152);
    thisa->m_NpcId = v30;
    std::string::~string(&v154);
    std::allocator<char>::~allocator(&v155);
    std::string::~string(&v152);
    std::allocator<char>::~allocator(&v153);
    std::allocator<char>::allocator(&v157);
    std::string::string(&v156, "count", &v157);
    std::allocator<char>::allocator(&v159);
    std::string::string(&v158, "NPC", &v159);
    v31 = Answer::Inifile::getIntValue(&ini, &v158, &v156);
    thisa->m_NpcCount = v31;
    std::string::~string(&v158);
    std::allocator<char>::~allocator(&v159);
    std::string::~string(&v156);
    std::allocator<char>::~allocator(&v157);
    std::allocator<char>::allocator(&v161);
    std::string::string(v160, "map", &v161);
    std::allocator<char>::allocator(&v163);
    std::string::string(&v162, "NPC", &v163);
    Answer::Inifile::getStrValue((Answer::Inifile *const)&MapPosString_0, (const std::string *const)&ini, &v162);
    std::string::~string(&v162);
    std::allocator<char>::~allocator(&v163);
    std::string::~string(v160);
    std::allocator<char>::~allocator(&v161);
    if ( std::operator!=<char>(&MapPosString_0, &_lhs) && std::operator!=<char>(&MapPosString_0, "-1") )
    {
      std::allocator<char>::allocator(&v165);
      std::string::string(&v164, "|", &v165);
      Answer::StringUtility::split(&SplitStr_1, &MapPosString_0, &v164, 0);
      std::string::~string(&v164);
      std::allocator<char>::~allocator(&v165);
      v166._M_current = std::vector<std::string>::begin(&SplitStr_1)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iterBegin_0,
        &v166);
      while ( 1 )
      {
        v167._M_current = std::vector<std::string>::end(&SplitStr_1)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin_0, &v167) )
          break;
        std::allocator<char>::allocator(&v169);
        std::string::string(&v168, ":", &v169);
        v33 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin_0);
        Answer::StringUtility::split(&vstr_0, v33, &v168, 0);
        std::string::~string(&v168);
        std::allocator<char>::~allocator(&v169);
        if ( std::vector<std::string>::size(&vstr_0) == 3 )
        {
          Position::Position(&v170, 0, 0);
          stuPos_0.m_MapId = 0;
          stuPos_0.m_Pos = v170;
          v34 = std::vector<std::string>::operator[](&vstr_0, 0);
          v35 = (const char *)std::string::c_str(v34);
          stuPos_0.m_MapId = atoi(v35);
          v36 = std::vector<std::string>::operator[](&vstr_0, 1u);
          v37 = (const char *)std::string::c_str(v36);
          stuPos_0.m_Pos.x = atoi(v37);
          v38 = std::vector<std::string>::operator[](&vstr_0, 2u);
          v39 = (const char *)std::string::c_str(v38);
          stuPos_0.m_Pos.y = atoi(v39);
          std::vector<MapPos>::push_back(&thisa->m_NpcMapPosVt, &stuPos_0);
        }
        std::vector<std::string>::~vector(&vstr_0);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin_0);
      }
      std::vector<std::string>::~vector(&SplitStr_1);
    }
    nLeftTime_0 = CFestivalActivity::getLeftTime(thisa);
    if ( nLeftTime_0 > 0 )
    {
      m_NpcId = thisa->m_NpcId;
      v41 = Answer::Singleton<CfgData>::instance();
      pCfgNpc = CfgData::getNpc(v41, m_NpcId);
      if ( pCfgNpc )
      {
        v42 = std::vector<MapPos>::end(&thisa->m_NpcMapPosVt)._M_current;
        v43._M_current = std::vector<MapPos>::begin(&thisa->m_NpcMapPosVt)._M_current;
        std::random_shuffle<__gnu_cxx::__normal_iterator<MapPos *,std::vector<MapPos>>>(
          v43,
          (__gnu_cxx::__normal_iterator<MapPos*,std::vector<MapPos> >)v42);
        v44 = std::vector<MapPos>::size(&thisa->m_NpcMapPosVt);
        if ( v44 <= thisa->m_NpcCount )
          m_NpcCount = std::vector<MapPos>::size(&thisa->m_NpcMapPosVt);
        else
          m_NpcCount = thisa->m_NpcCount;
        nFreshCount_0 = m_NpcCount;
        for ( i_1 = 0; i_1 < nFreshCount_0; ++i_1 )
        {
          v46 = std::vector<MapPos>::operator[](&thisa->m_NpcMapPosVt, i_1)->m_MapId;
          v47 = Answer::Singleton<MapManager>::instance();
          pMap_0 = MapManager::GetMap(v47, v46);
          v48 = (Npc *)operator new(0x4E8u);
          Npc::Npc(v48);
          npc = v48;
          if ( v48 && pMap_0 )
          {
            v49 = Answer::DayTime::now();
            Npc::init(npc, pCfgNpc, nLeftTime_0 + v49);
            y = std::vector<MapPos>::operator[](&thisa->m_NpcMapPosVt, i_1)->m_Pos.y;
            v51 = std::vector<MapPos>::operator[](&thisa->m_NpcMapPosVt, i_1);
            Map::addNpc(pMap_0, npc, v51->m_Pos.x, y);
          }
        }
      }
    }
    std::string::~string(&MapPosString_0);
  }
  if ( CFestivalActivity::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE_2::FAT2_COLLECTION2) )
  {
    std::allocator<char>::allocator(&v172);
    std::string::string(&v171, "start_day", &v172);
    std::allocator<char>::allocator(&v174);
    std::string::string(&v173, "COLLECTION2", &v174);
    v52 = Answer::Inifile::getIntValue(&ini, &v173, &v171);
    thisa->m_vStartDay[4] = v52;
    std::string::~string(&v173);
    std::allocator<char>::~allocator(&v174);
    std::string::~string(&v171);
    std::allocator<char>::~allocator(&v172);
    std::allocator<char>::allocator(&v176);
    std::string::string(&v175, "end_day", &v176);
    std::allocator<char>::allocator(&v178);
    std::string::string(&v177, "COLLECTION2", &v178);
    v53 = Answer::Inifile::getIntValue(&ini, &v177, &v175);
    thisa->m_vEndDay[4] = v53;
    std::string::~string(&v177);
    std::allocator<char>::~allocator(&v178);
    std::string::~string(&v175);
    std::allocator<char>::~allocator(&v176);
    std::allocator<char>::allocator(&v180);
    std::string::string(&v179, "plant_time", &v180);
    std::allocator<char>::allocator(&v182);
    std::string::string(&v181, "COLLECTION2", &v182);
    v54 = Answer::Inifile::getIntValue(&ini, &v181, &v179);
    thisa->m_PlantTime = v54;
    std::string::~string(&v181);
    std::allocator<char>::~allocator(&v182);
    std::string::~string(&v179);
    std::allocator<char>::~allocator(&v180);
  }
  if ( CFestivalActivity::isOpen(thisa, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DUI_HUAN) )
  {
    std::allocator<char>::allocator(&v184);
    std::string::string(&v183, "start_day", &v184);
    std::allocator<char>::allocator(&v186);
    std::string::string(&v185, "DUI_HUAN", &v186);
    v55 = Answer::Inifile::getIntValue(&ini, &v185, &v183);
    thisa->m_vStartDay[5] = v55;
    std::string::~string(&v185);
    std::allocator<char>::~allocator(&v186);
    std::string::~string(&v183);
    std::allocator<char>::~allocator(&v184);
    std::allocator<char>::allocator(&v188);
    std::string::string(&v187, "end_day", &v188);
    std::allocator<char>::allocator(&v190);
    std::string::string(&v189, "DUI_HUAN", &v190);
    v56 = Answer::Inifile::getIntValue(&ini, &v189, &v187);
    thisa->m_vEndDay[5] = v56;
    std::string::~string(&v189);
    std::allocator<char>::~allocator(&v190);
    std::string::~string(&v187);
    std::allocator<char>::~allocator(&v188);
    std::allocator<char>::allocator(&v192);
    std::string::string(&v191, "size", &v192);
    std::allocator<char>::allocator(&v194);
    std::string::string(&v193, "DUI_HUAN", &v194);
    v57 = Answer::Inifile::getIntValue(&ini, &v193, &v191);
    thisa->m_DuiHuanSize = v57;
    std::string::~string(&v193);
    std::allocator<char>::~allocator(&v194);
    std::string::~string(&v191);
    std::allocator<char>::~allocator(&v192);
    memset(&v195, 0, 52);
    ChangeItemCfg::ChangeItemCfg(&v195);
    std::vector<ChangeItemCfg>::resize(&thisa->m_ChangeItemCfgVt, thisa->m_DuiHuanSize, &v195);
    ChangeItemCfg::~ChangeItemCfg(&v195);
    for ( i_2 = 0; thisa->m_DuiHuanSize > i_2; ++i_2 )
    {
      memset(&stu_0, 0, 52);
      std::list<ItemData>::list(&stu_0.lCostItem);
      std::vector<MemChrBag>::vector(&stu_0.GetItems);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "need_item%d", i_2 + 1);
      std::allocator<char>::allocator((char *)&v197.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v197.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v197.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v197.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v197.m_strMap._M_t._M_impl._M_header._M_right,
        "DUI_HUAN",
        (char *)&v197.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v197,
        (const std::string *const)&ini,
        (const std::string *const)&v197.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)&v197);
      std::list<ItemData>::operator=(&stu_0.lCostItem, &strItems);
      std::list<ItemData>::~list(&strItems);
      std::string::~string(&v197);
      std::string::~string(&v197.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v197.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v197.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v197.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "need_gold%d", i_2 + 1);
      std::allocator<char>::allocator(&v198);
      std::string::string(&v197.m_currentSection, szCol, &v198);
      std::allocator<char>::allocator(&v200);
      std::string::string(&v199, "DUI_HUAN", &v200);
      stu_0.nCostGold = Answer::Inifile::getIntValue(&ini, &v199, &v197.m_currentSection);
      std::string::~string(&v199);
      std::allocator<char>::~allocator(&v200);
      std::string::~string(&v197.m_currentSection);
      std::allocator<char>::~allocator(&v198);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "get_item%d", i_2 + 1);
      std::allocator<char>::allocator((char *)&v202.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(
        &v202.m_strMap._M_t._M_impl._M_header._M_parent,
        szCol,
        (char *)&v202.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::allocator<char>::allocator((char *)&v202.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(
        &v202.m_strMap._M_t._M_impl._M_header._M_right,
        "DUI_HUAN",
        (char *)&v202.m_strMap._M_t._M_impl._M_node_count + 7);
      Answer::Inifile::getStrValue(
        &v202,
        (const std::string *const)&ini,
        (const std::string *const)&v202.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&__x, (const std::string *const)&v202);
      std::vector<MemChrBag>::operator=(&stu_0.GetItems, &__x);
      std::vector<MemChrBag>::~vector(&__x);
      std::string::~string(&v202);
      std::string::~string(&v202.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v202.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v202.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v202.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "time%d", i_2 + 1);
      std::allocator<char>::allocator(&v203);
      std::string::string(&v202.m_currentSection, szCol, &v203);
      std::allocator<char>::allocator(&v205);
      std::string::string(&v204, "DUI_HUAN", &v205);
      stu_0.Times = Answer::Inifile::getIntValue(&ini, &v204, &v202.m_currentSection);
      std::string::~string(&v204);
      std::allocator<char>::~allocator(&v205);
      std::string::~string(&v202.m_currentSection);
      std::allocator<char>::~allocator(&v203);
      v58 = std::vector<ChangeItemCfg>::operator[](&thisa->m_ChangeItemCfgVt, i_2);
      ChangeItemCfg::operator=(v58, &stu_0);
      ChangeItemCfg::~ChangeItemCfg(&stu_0);
    }
  }
  Answer::Inifile::~Inifile(&ini);
}


#####################################
int32_t __cdecl CFestivalActivity::loadVersion(CFestivalActivity *const this)
{
  Answer::DBPool *v1; // rax
  const char *v2; // rax
  Answer::MySqlQuery *v3; // rax
  const char *StringValue; // rax
  int32_t v5; // ebx
  char szSQL[4096]; // [rsp+10h] [rbp-1070h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-40h] BYREF
  std::string tname; // [rsp+1060h] [rbp-20h] BYREF
  _BYTE v11[17]; // [rsp+106Fh] [rbp-11h] BYREF

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  memset(szSQL, 0, sizeof(szSQL));
  std::allocator<char>::allocator(v11);
  std::string::string(&tname, "sys_server_config", v11);
  std::allocator<char>::~allocator(v11);
  v2 = (const char *)std::string::c_str(&tname);
  snprintf(szSQL, 0xFFFu, "SELECT * FROM `%s` WHERE `name`='FESTIVAL_2_VERSION'", v2);
  v3 = Answer::MySqlDBGuard::query(&db, szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v3);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "value", &_lhs);
    v5 = atoi(StringValue);
  }
  else
  {
    v5 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  std::string::~string(&tname);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  return v5;
}


#####################################
void __cdecl CFestivalActivity::saveVersion(CFestivalActivity *const this)
{
  Answer::DBPool *v1; // rax
  int32_t m_nVersion; // r12d
  const char *v3; // rax
  char szSQL[4096]; // [rsp+20h] [rbp-1050h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1020h] [rbp-50h] BYREF
  std::string tname; // [rsp+1050h] [rbp-20h] BYREF
  char v7; // [rsp+105Bh] [rbp-15h] BYREF
  int32_t nNowTime; // [rsp+105Ch] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  memset(szSQL, 0, sizeof(szSQL));
  nNowTime = Answer::DayTime::now();
  std::allocator<char>::allocator(&v7);
  std::string::string(&tname, "sys_server_config", &v7);
  std::allocator<char>::~allocator(&v7);
  m_nVersion = this->m_nVersion;
  v3 = (const char *)std::string::c_str(&tname);
  snprintf(
    szSQL,
    0xFFFu,
    "INSERT INTO `%s` ( `name`, `value`, `refresh_time` ) VALUES ( 'FESTIVAL_2_VERSION', %d, %d ) ON DUPLICATE KEY UPDATE"
    " `value`=%d, `refresh_time`=%d",
    v3,
    m_nVersion,
    nNowTime,
    m_nVersion,
    nNowTime);
  Answer::MySqlDBGuard::excute(&db, szSQL);
  std::string::~string(&tname);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CFestivalActivity::GetIconState(
        CFestivalActivity *const this,
        Player *player,
        IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CFestivalActivity::needShowIcon(this) )
    {
      CFestivalActivity::getIconState(&__x, this, player);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CFestivalActivity::SendIconState(CFestivalActivity *const this, Player *player)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CFestivalActivity::needShowIcon(this) )
    {
      CFestivalActivity::getIconState(&stu, this, player);
      Player::SendIconState(player, &stu);
    }
  }
}


#####################################
bool __cdecl CFestivalActivity::needShowIcon(CFestivalActivity *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
    return 0;
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
int32_t __cdecl CFestivalActivity::getLeftTime(CFestivalActivity *const this)
{
  CTimer *v2; // rax
  int nNowTime; // [rsp+18h] [rbp-8h]

  if ( this->m_nDay < 0 )
    return 0;
  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  return 86400 * (this->m_nEndDay - this->m_nDay) - (nNowTime - Answer::DayTime::dayzero(nNowTime));
}


#####################################
bool __cdecl CFestivalActivity::IsInTime(CFestivalActivity *const this, FESTIVAL_ACTIVITY_TYPE_2 nType)
{
  return CFestivalActivity::IsOpen(this, nType)
      && this->m_nDay >= this->m_vStartDay[nType]
      && this->m_nDay < this->m_vEndDay[nType];
}


#####################################
bool __cdecl CFestivalActivity::IsInTime(CFestivalActivity *const this)
{
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
bool __cdecl CFestivalActivity::IsOpen(CFestivalActivity *const this, FESTIVAL_ACTIVITY_TYPE_2 nType)
{
  return CFestivalActivity::IsInTime(this) && CFestivalActivity::isOpen(this, nType);
}


#####################################
void __cdecl CFestivalActivity::initOpenList(CFestivalActivity *const this, const std::string *const str)
{
  std::string *v2; // rax
  const char *v3; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+10h] [rbp-60h] BYREF
  StringVector vOpen; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  char v7; // [rsp+4Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+50h] [rbp-20h] BYREF
  int8_t nType; // [rsp+5Fh] [rbp-11h]

  bzero(this->m_vOpen, 6u);
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
    if ( nType > 0 && nType <= 5 )
      this->m_vOpen[nType] = 1;
  }
  std::vector<std::string>::~vector(&vOpen);
}


#####################################
int32_t __cdecl CFestivalActivity::GetPlantTimes(CFestivalActivity *const this)
{
  if ( !CFestivalActivity::IsInTime(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_COLLECTION) )
    return 0;
  else
    return this->m_Times;
}


#####################################
int32_t __cdecl CFestivalActivity::GetPlantTimes2(CFestivalActivity *const this)
{
  if ( !CFestivalActivity::IsInTime(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_COLLECTION2) )
    return 0;
  else
    return this->m_PlantTime;
}


#####################################
int32_t __cdecl CFestivalActivity::GetActDay(CFestivalActivity *const this, FESTIVAL_ACTIVITY_TYPE_2 nType)
{
  int32_t index; // [rsp+14h] [rbp-8h]

  index = this->m_nDay - this->m_vStartDay[nType];
  if ( index >= 0 && index <= this->m_vEndDay[nType] - this->m_vStartDay[nType] - 1 )
    return this->m_nDay - this->m_vStartDay[nType];
  else
    return -1;
}


#####################################
int32_t __cdecl CFestivalActivity::GetDaTiReward(CFestivalActivity *const this, Player *player, int8_t RewardType)
{
  std::vector<std::string> *v4; // rax
  CExtCharBag *Bag; // rax
  MemChrBag item; // [rsp+20h] [rbp-40h] BYREF
  int32_t DaTiTimes; // [rsp+4Ch] [rbp-14h]
  int32_t index; // [rsp+50h] [rbp-10h]
  int32_t nSize; // [rsp+54h] [rbp-Ch]
  int32_t DaAnCount; // [rsp+58h] [rbp-8h]
  int32_t record; // [rsp+5Ch] [rbp-4h]

  if ( !player )
    return 10002;
  if ( !CFestivalActivity::IsInTime(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DA_TI) )
    return 0;
  DaTiTimes = Player::getRecord(player, 2120);
  index = CFestivalActivity::GetActDay(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DA_TI);
  nSize = std::vector<std::vector<std::string>>::size(&this->m_StringVtVector);
  if ( index < 0 || index >= nSize )
    return 10002;
  v4 = std::vector<std::vector<std::string>>::operator[](&this->m_StringVtVector, index);
  DaAnCount = std::vector<std::string>::size(v4);
  if ( DaTiTimes < DaAnCount )
    return 10002;
  record = 0;
  memset(&item, 0, sizeof(item));
  if ( RewardType == 1 )
  {
    record = 2121;
    item = this->m_DayGift;
  }
  else
  {
    record = 37401;
    item = this->m_ActGift;
  }
  if ( Player::getRecord(player, record) > 0 )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::IDCR_DA_TI_ACT) )
    return 10002;
  Player::updateRecord(player, record, 1);
  return 0;
}


#####################################
int32_t __cdecl CFestivalActivity::DaTi(CFestivalActivity *const this, Player *player, std::string *p_DaAn)
{
  std::vector<std::string> *v5; // rax
  std::vector<std::string> *v6; // rax
  std::string *v7; // rax
  int DaTiTimes; // [rsp+20h] [rbp-20h]
  int index; // [rsp+24h] [rbp-1Ch]
  int32_t nSize; // [rsp+28h] [rbp-18h]
  int32_t DaAnCount; // [rsp+2Ch] [rbp-14h]

  if ( !player || std::operator==<char>(&_lhs, p_DaAn) )
    return 10002;
  if ( !CFestivalActivity::IsInTime(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DA_TI) )
    return 0;
  DaTiTimes = Player::getRecord(player, 2120);
  index = CFestivalActivity::GetActDay(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DA_TI);
  nSize = std::vector<std::vector<std::string>>::size(&this->m_StringVtVector);
  if ( index < 0 || index >= nSize )
    return 10002;
  v5 = std::vector<std::vector<std::string>>::operator[](&this->m_StringVtVector, index);
  DaAnCount = std::vector<std::string>::size(v5);
  if ( DaTiTimes < 0 || DaTiTimes >= DaAnCount )
    return 10002;
  v6 = std::vector<std::vector<std::string>>::operator[](&this->m_StringVtVector, index);
  v7 = std::vector<std::string>::operator[](v6, DaTiTimes);
  if ( !std::operator==<char>(v7, p_DaAn) )
    return 10002;
  Player::updateRecord(player, 2120, DaTiTimes + 1);
  return 0;
}


#####################################
int32_t __cdecl CFestivalActivity::DuiHuan(CFestivalActivity *const this, Player *player, int32_t nIndex)
{
  int32_t Record; // ebx
  int64_t Currency; // rbx
  ChangeItemCfg *v6; // rbx
  MemChrBagVector *p_GetItems; // r12
  CExtCharBag *Bag; // rax
  int64_t nCostGold; // rdx
  int32_t v10; // edx

  if ( !player )
    return 10002;
  if ( nIndex < 0 || this->m_DuiHuanSize <= nIndex )
    return 10002;
  if ( !CFestivalActivity::IsInTime(this, FESTIVAL_ACTIVITY_TYPE_2::FAT2_DUI_HUAN) )
    return 10002;
  Record = Player::getRecord(player, nIndex + 10101);
  if ( Record >= std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex)->Times )
    return 10002;
  if ( std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex)->nCostGold > 0 )
  {
    Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
    if ( Currency < std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex)->nCostGold )
      return 10002;
  }
  v6 = std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex);
  p_GetItems = &std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex)->GetItems;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddAndRemoveItem(Bag, p_GetItems, &v6->lCostItem, ITEM_CHANGE_REASON::IDCR_FESTIVAL_ACT_2) )
    return 10002;
  if ( std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex)->nCostGold > 0 )
  {
    nCostGold = std::vector<ChangeItemCfg>::operator[](&this->m_ChangeItemCfgVt, nIndex)->nCostGold;
    Player::DecCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD, nCostGold, CURRENCY_CHANGE_REASON::GCR_FESTIVAL_ACT_2, 0);
  }
  v10 = Player::getRecord(player, nIndex + 10101) + 1;
  Player::updateRecord(player, nIndex + 10101, v10);
  return 0;
}


