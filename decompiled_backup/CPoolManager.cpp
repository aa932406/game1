// Decompiled methods for class: CPoolManager
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CPoolManager::Init(CPoolManager *const this)
{
  uint32_t IntValue; // ebx
  uint32_t v2; // ecx
  uint32_t v3; // ebx
  uint32_t v4; // ecx
  uint32_t v5; // ebx
  uint32_t v6; // ecx
  uint32_t v7; // ebx
  uint32_t v8; // ecx
  uint32_t v9; // ebx
  uint32_t v10; // ecx
  uint32_t v11; // ebx
  uint32_t v12; // ecx
  uint32_t v13; // ebx
  uint32_t v14; // ecx
  uint32_t v15; // ebx
  uint32_t v16; // ecx
  uint32_t v17; // ebx
  uint32_t v18; // ecx
  uint32_t v19; // ebx
  uint32_t v20; // ecx
  uint32_t v21; // ebx
  uint32_t v22; // ecx
  uint32_t v23; // ebx
  uint32_t v24; // ecx
  uint32_t v25; // ebx
  uint32_t v26; // ecx
  uint32_t v27; // ebx
  uint32_t v28; // ecx
  uint32_t v29; // ebx
  uint32_t v30; // ecx
  uint32_t v31; // ebx
  uint32_t v32; // ecx
  uint32_t v33; // ebx
  uint32_t v34; // ecx
  Answer::Inifile ini; // [rsp+10h] [rbp-4A0h] BYREF
  std::string file; // [rsp+50h] [rbp-460h] BYREF
  char v37; // [rsp+5Fh] [rbp-451h] BYREF
  std::string key; // [rsp+60h] [rbp-450h] BYREF
  char v39; // [rsp+6Fh] [rbp-441h] BYREF
  std::string section; // [rsp+70h] [rbp-440h] BYREF
  char v41; // [rsp+7Fh] [rbp-431h] BYREF
  std::string v42; // [rsp+80h] [rbp-430h] BYREF
  char v43; // [rsp+8Fh] [rbp-421h] BYREF
  std::string v44; // [rsp+90h] [rbp-420h] BYREF
  char v45; // [rsp+9Fh] [rbp-411h] BYREF
  std::string v46; // [rsp+A0h] [rbp-410h] BYREF
  char v47; // [rsp+AFh] [rbp-401h] BYREF
  std::string v48; // [rsp+B0h] [rbp-400h] BYREF
  char v49; // [rsp+BFh] [rbp-3F1h] BYREF
  std::string v50; // [rsp+C0h] [rbp-3F0h] BYREF
  char v51; // [rsp+CFh] [rbp-3E1h] BYREF
  std::string v52; // [rsp+D0h] [rbp-3E0h] BYREF
  char v53; // [rsp+DFh] [rbp-3D1h] BYREF
  std::string v54; // [rsp+E0h] [rbp-3D0h] BYREF
  char v55; // [rsp+EFh] [rbp-3C1h] BYREF
  std::string v56; // [rsp+F0h] [rbp-3C0h] BYREF
  char v57; // [rsp+FFh] [rbp-3B1h] BYREF
  std::string v58; // [rsp+100h] [rbp-3B0h] BYREF
  char v59; // [rsp+10Fh] [rbp-3A1h] BYREF
  std::string v60; // [rsp+110h] [rbp-3A0h] BYREF
  char v61; // [rsp+11Fh] [rbp-391h] BYREF
  std::string v62; // [rsp+120h] [rbp-390h] BYREF
  char v63; // [rsp+12Fh] [rbp-381h] BYREF
  std::string v64; // [rsp+130h] [rbp-380h] BYREF
  char v65; // [rsp+13Fh] [rbp-371h] BYREF
  std::string v66; // [rsp+140h] [rbp-370h] BYREF
  char v67; // [rsp+14Fh] [rbp-361h] BYREF
  std::string v68; // [rsp+150h] [rbp-360h] BYREF
  char v69; // [rsp+15Fh] [rbp-351h] BYREF
  std::string v70; // [rsp+160h] [rbp-350h] BYREF
  char v71; // [rsp+16Fh] [rbp-341h] BYREF
  std::string v72; // [rsp+170h] [rbp-340h] BYREF
  char v73; // [rsp+17Fh] [rbp-331h] BYREF
  std::string v74; // [rsp+180h] [rbp-330h] BYREF
  char v75; // [rsp+18Fh] [rbp-321h] BYREF
  std::string v76; // [rsp+190h] [rbp-320h] BYREF
  char v77; // [rsp+19Fh] [rbp-311h] BYREF
  std::string v78; // [rsp+1A0h] [rbp-310h] BYREF
  char v79; // [rsp+1AFh] [rbp-301h] BYREF
  std::string v80; // [rsp+1B0h] [rbp-300h] BYREF
  char v81; // [rsp+1BFh] [rbp-2F1h] BYREF
  std::string v82; // [rsp+1C0h] [rbp-2F0h] BYREF
  char v83; // [rsp+1CFh] [rbp-2E1h] BYREF
  std::string v84; // [rsp+1D0h] [rbp-2E0h] BYREF
  char v85; // [rsp+1DFh] [rbp-2D1h] BYREF
  std::string v86; // [rsp+1E0h] [rbp-2D0h] BYREF
  char v87; // [rsp+1EFh] [rbp-2C1h] BYREF
  std::string v88; // [rsp+1F0h] [rbp-2C0h] BYREF
  char v89; // [rsp+1FFh] [rbp-2B1h] BYREF
  std::string v90; // [rsp+200h] [rbp-2B0h] BYREF
  char v91; // [rsp+20Fh] [rbp-2A1h] BYREF
  std::string v92; // [rsp+210h] [rbp-2A0h] BYREF
  char v93; // [rsp+21Fh] [rbp-291h] BYREF
  std::string v94; // [rsp+220h] [rbp-290h] BYREF
  char v95; // [rsp+22Fh] [rbp-281h] BYREF
  std::string v96; // [rsp+230h] [rbp-280h] BYREF
  char v97; // [rsp+23Fh] [rbp-271h] BYREF
  std::string v98; // [rsp+240h] [rbp-270h] BYREF
  char v99; // [rsp+24Fh] [rbp-261h] BYREF
  std::string v100; // [rsp+250h] [rbp-260h] BYREF
  char v101; // [rsp+25Fh] [rbp-251h] BYREF
  std::string v102; // [rsp+260h] [rbp-250h] BYREF
  char v103; // [rsp+26Fh] [rbp-241h] BYREF
  std::string v104; // [rsp+270h] [rbp-240h] BYREF
  char v105; // [rsp+27Fh] [rbp-231h] BYREF
  std::string v106; // [rsp+280h] [rbp-230h] BYREF
  char v107; // [rsp+28Fh] [rbp-221h] BYREF
  std::string v108; // [rsp+290h] [rbp-220h] BYREF
  char v109; // [rsp+29Fh] [rbp-211h] BYREF
  std::string v110; // [rsp+2A0h] [rbp-210h] BYREF
  char v111; // [rsp+2AFh] [rbp-201h] BYREF
  std::string v112; // [rsp+2B0h] [rbp-200h] BYREF
  char v113; // [rsp+2BFh] [rbp-1F1h] BYREF
  std::string v114; // [rsp+2C0h] [rbp-1F0h] BYREF
  char v115; // [rsp+2CFh] [rbp-1E1h] BYREF
  std::string v116; // [rsp+2D0h] [rbp-1E0h] BYREF
  char v117; // [rsp+2DFh] [rbp-1D1h] BYREF
  std::string v118; // [rsp+2E0h] [rbp-1D0h] BYREF
  char v119; // [rsp+2EFh] [rbp-1C1h] BYREF
  std::string v120; // [rsp+2F0h] [rbp-1C0h] BYREF
  char v121; // [rsp+2FFh] [rbp-1B1h] BYREF
  std::string v122; // [rsp+300h] [rbp-1B0h] BYREF
  char v123; // [rsp+30Fh] [rbp-1A1h] BYREF
  std::string v124; // [rsp+310h] [rbp-1A0h] BYREF
  char v125; // [rsp+31Fh] [rbp-191h] BYREF
  std::string v126; // [rsp+320h] [rbp-190h] BYREF
  char v127; // [rsp+32Fh] [rbp-181h] BYREF
  std::string v128; // [rsp+330h] [rbp-180h] BYREF
  char v129; // [rsp+33Fh] [rbp-171h] BYREF
  std::string v130; // [rsp+340h] [rbp-170h] BYREF
  char v131; // [rsp+34Fh] [rbp-161h] BYREF
  std::string v132; // [rsp+350h] [rbp-160h] BYREF
  char v133; // [rsp+35Fh] [rbp-151h] BYREF
  std::string v134; // [rsp+360h] [rbp-150h] BYREF
  char v135; // [rsp+36Fh] [rbp-141h] BYREF
  std::string v136; // [rsp+370h] [rbp-140h] BYREF
  char v137; // [rsp+37Fh] [rbp-131h] BYREF
  std::string v138; // [rsp+380h] [rbp-130h] BYREF
  char v139; // [rsp+38Fh] [rbp-121h] BYREF
  std::string v140; // [rsp+390h] [rbp-120h] BYREF
  char v141; // [rsp+39Fh] [rbp-111h] BYREF
  std::string v142; // [rsp+3A0h] [rbp-110h] BYREF
  char v143; // [rsp+3AFh] [rbp-101h] BYREF
  std::string v144; // [rsp+3B0h] [rbp-100h] BYREF
  char v145; // [rsp+3BFh] [rbp-F1h] BYREF
  std::string v146; // [rsp+3C0h] [rbp-F0h] BYREF
  char v147; // [rsp+3CFh] [rbp-E1h] BYREF
  std::string v148; // [rsp+3D0h] [rbp-E0h] BYREF
  char v149; // [rsp+3DFh] [rbp-D1h] BYREF
  std::string v150; // [rsp+3E0h] [rbp-D0h] BYREF
  char v151; // [rsp+3EFh] [rbp-C1h] BYREF
  std::string v152; // [rsp+3F0h] [rbp-C0h] BYREF
  char v153; // [rsp+3FFh] [rbp-B1h] BYREF
  std::string v154; // [rsp+400h] [rbp-B0h] BYREF
  char v155; // [rsp+40Fh] [rbp-A1h] BYREF
  std::string v156; // [rsp+410h] [rbp-A0h] BYREF
  char v157; // [rsp+41Fh] [rbp-91h] BYREF
  std::string v158; // [rsp+420h] [rbp-90h] BYREF
  char v159; // [rsp+42Fh] [rbp-81h] BYREF
  std::string v160; // [rsp+430h] [rbp-80h] BYREF
  char v161; // [rsp+43Fh] [rbp-71h] BYREF
  std::string v162; // [rsp+440h] [rbp-70h] BYREF
  char v163; // [rsp+44Fh] [rbp-61h] BYREF
  std::string v164; // [rsp+450h] [rbp-60h] BYREF
  char v165; // [rsp+45Fh] [rbp-51h] BYREF
  std::string v166; // [rsp+460h] [rbp-50h] BYREF
  char v167; // [rsp+46Fh] [rbp-41h] BYREF
  std::string v168; // [rsp+470h] [rbp-40h] BYREF
  char v169; // [rsp+47Fh] [rbp-31h] BYREF
  std::string v170; // [rsp+480h] [rbp-30h] BYREF
  char v171; // [rsp+48Fh] [rbp-21h] BYREF
  std::string v172; // [rsp+490h] [rbp-20h] BYREF
  _BYTE v173[17]; // [rsp+49Fh] [rbp-11h] BYREF

  Answer::Inifile::Inifile(&ini);
  std::allocator<char>::allocator(&v37);
  std::string::string(&file, "./ServerConfig/Config/PoolConfig.ini");
  Answer::Inifile::parse(&ini, &file);
  std::string::~string(&file);
  std::allocator<char>::~allocator(&v37);
  std::allocator<char>::allocator(&v39);
  std::string::string(&key, "max");
  std::allocator<char>::allocator(&v41);
  std::string::string(&section, "GameMsg");
  IntValue = Answer::Inifile::getIntValue(&ini, &section, &key);
  std::allocator<char>::allocator(&v43);
  std::string::string(&v42, "min");
  std::allocator<char>::allocator(&v45);
  std::string::string(&v44, "GameMsg");
  v2 = Answer::Inifile::getIntValue(&ini, &v44, &v42);
  CPoolManager::regPool<GameMsg>(this, v2, IntValue);
  std::string::~string(&v44);
  std::allocator<char>::~allocator(&v45);
  std::string::~string(&v42);
  std::allocator<char>::~allocator(&v43);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v41);
  std::string::~string(&key);
  std::allocator<char>::~allocator(&v39);
  std::allocator<char>::allocator(&v47);
  std::string::string(&v46, "max");
  std::allocator<char>::allocator(&v49);
  std::string::string(&v48, "User");
  v3 = Answer::Inifile::getIntValue(&ini, &v48, &v46);
  std::allocator<char>::allocator(&v51);
  std::string::string(&v50, "min");
  std::allocator<char>::allocator(&v53);
  std::string::string(&v52, "User");
  v4 = Answer::Inifile::getIntValue(&ini, &v52, &v50);
  CPoolManager::regPool<User>(this, v4, v3);
  std::string::~string(&v52);
  std::allocator<char>::~allocator(&v53);
  std::string::~string(&v50);
  std::allocator<char>::~allocator(&v51);
  std::string::~string(&v48);
  std::allocator<char>::~allocator(&v49);
  std::string::~string(&v46);
  std::allocator<char>::~allocator(&v47);
  std::allocator<char>::allocator(&v55);
  std::string::string(&v54, "max");
  std::allocator<char>::allocator(&v57);
  std::string::string(&v56, "Player");
  v5 = Answer::Inifile::getIntValue(&ini, &v56, &v54);
  std::allocator<char>::allocator(&v59);
  std::string::string(&v58, "min");
  std::allocator<char>::allocator(&v61);
  std::string::string(&v60, "Player");
  v6 = Answer::Inifile::getIntValue(&ini, &v60, &v58);
  CPoolManager::regPool<Player>(this, v6, v5);
  std::string::~string(&v60);
  std::allocator<char>::~allocator(&v61);
  std::string::~string(&v58);
  std::allocator<char>::~allocator(&v59);
  std::string::~string(&v56);
  std::allocator<char>::~allocator(&v57);
  std::string::~string(&v54);
  std::allocator<char>::~allocator(&v55);
  std::allocator<char>::allocator(&v63);
  std::string::string(&v62, "max");
  std::allocator<char>::allocator(&v65);
  std::string::string(&v64, "CObjPet");
  v7 = Answer::Inifile::getIntValue(&ini, &v64, &v62);
  std::allocator<char>::allocator(&v67);
  std::string::string(&v66, "min");
  std::allocator<char>::allocator(&v69);
  std::string::string(&v68, "CObjPet");
  v8 = Answer::Inifile::getIntValue(&ini, &v68, &v66);
  CPoolManager::regPool<CObjPet>(this, v8, v7);
  std::string::~string(&v68);
  std::allocator<char>::~allocator(&v69);
  std::string::~string(&v66);
  std::allocator<char>::~allocator(&v67);
  std::string::~string(&v64);
  std::allocator<char>::~allocator(&v65);
  std::string::~string(&v62);
  std::allocator<char>::~allocator(&v63);
  std::allocator<char>::allocator(&v71);
  std::string::string(&v70, "max");
  std::allocator<char>::allocator(&v73);
  std::string::string(&v72, "Monster");
  v9 = Answer::Inifile::getIntValue(&ini, &v72, &v70);
  std::allocator<char>::allocator(&v75);
  std::string::string(&v74, "min");
  std::allocator<char>::allocator(&v77);
  std::string::string(&v76, "Monster");
  v10 = Answer::Inifile::getIntValue(&ini, &v76, &v74);
  CPoolManager::regPool<Monster>(this, v10, v9);
  std::string::~string(&v76);
  std::allocator<char>::~allocator(&v77);
  std::string::~string(&v74);
  std::allocator<char>::~allocator(&v75);
  std::string::~string(&v72);
  std::allocator<char>::~allocator(&v73);
  std::string::~string(&v70);
  std::allocator<char>::~allocator(&v71);
  std::allocator<char>::allocator(&v79);
  std::string::string(&v78, "max");
  std::allocator<char>::allocator(&v81);
  std::string::string(&v80, "Dungeon");
  v11 = Answer::Inifile::getIntValue(&ini, &v80, &v78);
  std::allocator<char>::allocator(&v83);
  std::string::string(&v82, "min");
  std::allocator<char>::allocator(&v85);
  std::string::string(&v84, "Dungeon");
  v12 = Answer::Inifile::getIntValue(&ini, &v84, &v82);
  CPoolManager::regPool<Dungeon>(this, v12, v11);
  std::string::~string(&v84);
  std::allocator<char>::~allocator(&v85);
  std::string::~string(&v82);
  std::allocator<char>::~allocator(&v83);
  std::string::~string(&v80);
  std::allocator<char>::~allocator(&v81);
  std::string::~string(&v78);
  std::allocator<char>::~allocator(&v79);
  std::allocator<char>::allocator(&v87);
  std::string::string(&v86, "max");
  std::allocator<char>::allocator(&v89);
  std::string::string(&v88, "MonsterDungeon");
  v13 = Answer::Inifile::getIntValue(&ini, &v88, &v86);
  std::allocator<char>::allocator(&v91);
  std::string::string(&v90, "min");
  std::allocator<char>::allocator(&v93);
  std::string::string(&v92, "MonsterDungeon");
  v14 = Answer::Inifile::getIntValue(&ini, &v92, &v90);
  CPoolManager::regPool<MonsterDungeon>(this, v14, v13);
  std::string::~string(&v92);
  std::allocator<char>::~allocator(&v93);
  std::string::~string(&v90);
  std::allocator<char>::~allocator(&v91);
  std::string::~string(&v88);
  std::allocator<char>::~allocator(&v89);
  std::string::~string(&v86);
  std::allocator<char>::~allocator(&v87);
  std::allocator<char>::allocator(&v95);
  std::string::string(&v94, "max");
  std::allocator<char>::allocator(&v97);
  std::string::string(&v96, "CDropItem");
  v15 = Answer::Inifile::getIntValue(&ini, &v96, &v94);
  std::allocator<char>::allocator(&v99);
  std::string::string(&v98, "min");
  std::allocator<char>::allocator(&v101);
  std::string::string(&v100, "CDropItem");
  v16 = Answer::Inifile::getIntValue(&ini, &v100, &v98);
  CPoolManager::regPool<CDropItem>(this, v16, v15);
  std::string::~string(&v100);
  std::allocator<char>::~allocator(&v101);
  std::string::~string(&v98);
  std::allocator<char>::~allocator(&v99);
  std::string::~string(&v96);
  std::allocator<char>::~allocator(&v97);
  std::string::~string(&v94);
  std::allocator<char>::~allocator(&v95);
  std::allocator<char>::allocator(&v103);
  std::string::string(&v102, "max");
  std::allocator<char>::allocator(&v105);
  std::string::string(&v104, "Trap");
  v17 = Answer::Inifile::getIntValue(&ini, &v104, &v102);
  std::allocator<char>::allocator(&v107);
  std::string::string(&v106, "min");
  std::allocator<char>::allocator(&v109);
  std::string::string(&v108, "Trap");
  v18 = Answer::Inifile::getIntValue(&ini, &v108, &v106);
  CPoolManager::regPool<Trap>(this, v18, v17);
  std::string::~string(&v108);
  std::allocator<char>::~allocator(&v109);
  std::string::~string(&v106);
  std::allocator<char>::~allocator(&v107);
  std::string::~string(&v104);
  std::allocator<char>::~allocator(&v105);
  std::string::~string(&v102);
  std::allocator<char>::~allocator(&v103);
  std::allocator<char>::allocator(&v111);
  std::string::string(&v110, "max");
  std::allocator<char>::allocator(&v113);
  std::string::string(&v112, "PlantDungeon");
  v19 = Answer::Inifile::getIntValue(&ini, &v112, &v110);
  std::allocator<char>::allocator(&v115);
  std::string::string(&v114, "min");
  std::allocator<char>::allocator(&v117);
  std::string::string(&v116, "PlantDungeon");
  v20 = Answer::Inifile::getIntValue(&ini, &v116, &v114);
  CPoolManager::regPool<PlantDungeon>(this, v20, v19);
  std::string::~string(&v116);
  std::allocator<char>::~allocator(&v117);
  std::string::~string(&v114);
  std::allocator<char>::~allocator(&v115);
  std::string::~string(&v112);
  std::allocator<char>::~allocator(&v113);
  std::string::~string(&v110);
  std::allocator<char>::~allocator(&v111);
  std::allocator<char>::allocator(&v119);
  std::string::string(&v118, "max");
  std::allocator<char>::allocator(&v121);
  std::string::string(&v120, "MonsterActivity");
  v21 = Answer::Inifile::getIntValue(&ini, &v120, &v118);
  std::allocator<char>::allocator(&v123);
  std::string::string(&v122, "min");
  std::allocator<char>::allocator(&v125);
  std::string::string(&v124, "MonsterActivity");
  v22 = Answer::Inifile::getIntValue(&ini, &v124, &v122);
  CPoolManager::regPool<MonsterActivity>(this, v22, v21);
  std::string::~string(&v124);
  std::allocator<char>::~allocator(&v125);
  std::string::~string(&v122);
  std::allocator<char>::~allocator(&v123);
  std::string::~string(&v120);
  std::allocator<char>::~allocator(&v121);
  std::string::~string(&v118);
  std::allocator<char>::~allocator(&v119);
  std::allocator<char>::allocator(&v127);
  std::string::string(&v126, "max");
  std::allocator<char>::allocator(&v129);
  std::string::string(&v128, "NpcActivity");
  v23 = Answer::Inifile::getIntValue(&ini, &v128, &v126);
  std::allocator<char>::allocator(&v131);
  std::string::string(&v130, "min");
  std::allocator<char>::allocator(&v133);
  std::string::string(&v132, "NpcActivity");
  v24 = Answer::Inifile::getIntValue(&ini, &v132, &v130);
  CPoolManager::regPool<NpcActivity>(this, v24, v23);
  std::string::~string(&v132);
  std::allocator<char>::~allocator(&v133);
  std::string::~string(&v130);
  std::allocator<char>::~allocator(&v131);
  std::string::~string(&v128);
  std::allocator<char>::~allocator(&v129);
  std::string::~string(&v126);
  std::allocator<char>::~allocator(&v127);
  std::allocator<char>::allocator(&v135);
  std::string::string(&v134, "max");
  std::allocator<char>::allocator(&v137);
  std::string::string(&v136, "PlantActivity");
  v25 = Answer::Inifile::getIntValue(&ini, &v136, &v134);
  std::allocator<char>::allocator(&v139);
  std::string::string(&v138, "min");
  std::allocator<char>::allocator(&v141);
  std::string::string(&v140, "PlantActivity");
  v26 = Answer::Inifile::getIntValue(&ini, &v140, &v138);
  CPoolManager::regPool<PlantActivity>(this, v26, v25);
  std::string::~string(&v140);
  std::allocator<char>::~allocator(&v141);
  std::string::~string(&v138);
  std::allocator<char>::~allocator(&v139);
  std::string::~string(&v136);
  std::allocator<char>::~allocator(&v137);
  std::string::~string(&v134);
  std::allocator<char>::~allocator(&v135);
  std::allocator<char>::allocator(&v143);
  std::string::string(&v142, "max");
  std::allocator<char>::allocator(&v145);
  std::string::string(&v144, "Trailer");
  v27 = Answer::Inifile::getIntValue(&ini, &v144, &v142);
  std::allocator<char>::allocator(&v147);
  std::string::string(&v146, "min");
  std::allocator<char>::allocator(&v149);
  std::string::string(&v148, "Trailer");
  v28 = Answer::Inifile::getIntValue(&ini, &v148, &v146);
  CPoolManager::regPool<Trailer>(this, v28, v27);
  std::string::~string(&v148);
  std::allocator<char>::~allocator(&v149);
  std::string::~string(&v146);
  std::allocator<char>::~allocator(&v147);
  std::string::~string(&v144);
  std::allocator<char>::~allocator(&v145);
  std::string::~string(&v142);
  std::allocator<char>::~allocator(&v143);
  std::allocator<char>::allocator(&v151);
  std::string::string(&v150, "max");
  std::allocator<char>::allocator(&v153);
  std::string::string(&v152, "CObjCarrier");
  v29 = Answer::Inifile::getIntValue(&ini, &v152, &v150);
  std::allocator<char>::allocator(&v155);
  std::string::string(&v154, "min");
  std::allocator<char>::allocator(&v157);
  std::string::string(&v156, "CObjCarrier");
  v30 = Answer::Inifile::getIntValue(&ini, &v156, &v154);
  CPoolManager::regPool<CObjCarrier>(this, v30, v29);
  std::string::~string(&v156);
  std::allocator<char>::~allocator(&v157);
  std::string::~string(&v154);
  std::allocator<char>::~allocator(&v155);
  std::string::~string(&v152);
  std::allocator<char>::~allocator(&v153);
  std::string::~string(&v150);
  std::allocator<char>::~allocator(&v151);
  std::allocator<char>::allocator(&v159);
  std::string::string(&v158, "max");
  std::allocator<char>::allocator(&v161);
  std::string::string(&v160, "Territory");
  v31 = Answer::Inifile::getIntValue(&ini, &v160, &v158);
  std::allocator<char>::allocator(&v163);
  std::string::string(&v162, "min");
  std::allocator<char>::allocator(&v165);
  std::string::string(&v164, "Territory");
  v32 = Answer::Inifile::getIntValue(&ini, &v164, &v162);
  CPoolManager::regPool<CTerritory>(this, v32, v31);
  std::string::~string(&v164);
  std::allocator<char>::~allocator(&v165);
  std::string::~string(&v162);
  std::allocator<char>::~allocator(&v163);
  std::string::~string(&v160);
  std::allocator<char>::~allocator(&v161);
  std::string::~string(&v158);
  std::allocator<char>::~allocator(&v159);
  std::allocator<char>::allocator(&v167);
  std::string::string(&v166, "max");
  std::allocator<char>::allocator(&v169);
  std::string::string(&v168, "LittlerHelper");
  v33 = Answer::Inifile::getIntValue(&ini, &v168, &v166);
  std::allocator<char>::allocator(&v171);
  std::string::string(&v170, "min");
  std::allocator<char>::allocator(v173);
  std::string::string(&v172, "LittlerHelper");
  v34 = Answer::Inifile::getIntValue(&ini, &v172, &v170);
  CPoolManager::regPool<CLittleHelper>(this, v34, v33);
  std::string::~string(&v172);
  std::allocator<char>::~allocator(v173);
  std::string::~string(&v170);
  std::allocator<char>::~allocator(&v171);
  std::string::~string(&v168);
  std::allocator<char>::~allocator(&v169);
  std::string::~string(&v166);
  std::allocator<char>::~allocator(&v167);
  Answer::Inifile::~Inifile(&ini);
}


