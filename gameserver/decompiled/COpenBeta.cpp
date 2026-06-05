// Decompiled methods for class: COpenBeta
// Source: gameserver.cc
// Total methods: 44

#####################################
void __cdecl COpenBeta::Init(COpenBeta *const this, int32_t line)
{
  CTimer *v2; // rax
  int32_t v3; // eax
  int v4; // ebx
  ShopGoods *v5; // rbx
  ShopGoods *v6; // rax
  int *v7; // rbx
  ShopGoods *v8; // rbx
  ShopGoods *v9; // rax
  int *v10; // rbx
  ShopGoods *v11; // rbx
  ShopGoods *v12; // rax
  int *v13; // rbx
  int *v14; // rbx
  std::vector<MemChrBag> *v15; // rax
  ItemData v16; // kr20_12
  int *v17; // rbx
  ItemData *v18; // rbx
  ItemData v19; // kr34_12
  MemChrBag *v20; // rbx
  int *v21; // rbx
  int *v22; // rbx
  ItemData *v23; // rbx
  int IntValue; // eax
  int v25; // eax
  int32_t v26; // eax
  MemChrBag *v27; // rbx
  int *v28; // rbx
  int v29; // eax
  int v30; // eax
  int32_t v31; // eax
  MemChrBag *v32; // rbx
  int *v33; // rbx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  __int64 v38; // rax
  __int64 v39; // rax
  MemChrBag v40; // [rsp+0h] [rbp-E80h]
  MemChrBag v41; // [rsp+0h] [rbp-E80h]
  MemChrBag v42; // [rsp+0h] [rbp-E80h]
  MemChrBag v43; // [rsp+20h] [rbp-E60h] BYREF
  __int64 v44; // [rsp+40h] [rbp-E40h]
  int32_t m_nCount; // [rsp+48h] [rbp-E38h]
  int32_t linea; // [rsp+54h] [rbp-E2Ch]
  COpenBeta *thisa; // [rsp+58h] [rbp-E28h]
  char szCol[64]; // [rsp+60h] [rbp-E20h] BYREF
  Answer::Inifile ini; // [rsp+A0h] [rbp-DE0h] BYREF
  tm nowTime; // [rsp+E0h] [rbp-DA0h] BYREF
  TimeArea tarea; // [rsp+120h] [rbp-D60h] BYREF
  std::string file; // [rsp+130h] [rbp-D50h] BYREF
  char v53; // [rsp+13Fh] [rbp-D41h] BYREF
  Answer::Inifile v54; // [rsp+140h] [rbp-D40h] BYREF
  char v55; // [rsp+17Fh] [rbp-D01h] BYREF
  std::string section; // [rsp+180h] [rbp-D00h] BYREF
  char v57; // [rsp+18Fh] [rbp-CF1h] BYREF
  std::string key; // [rsp+190h] [rbp-CF0h] BYREF
  char v59; // [rsp+19Fh] [rbp-CE1h] BYREF
  std::string v60; // [rsp+1A0h] [rbp-CE0h] BYREF
  char v61; // [rsp+1AFh] [rbp-CD1h] BYREF
  std::string v62; // [rsp+1B0h] [rbp-CD0h] BYREF
  char v63; // [rsp+1BFh] [rbp-CC1h] BYREF
  std::string v64; // [rsp+1C0h] [rbp-CC0h] BYREF
  char v65; // [rsp+1CFh] [rbp-CB1h] BYREF
  std::string v66; // [rsp+1D0h] [rbp-CB0h] BYREF
  char v67; // [rsp+1DFh] [rbp-CA1h] BYREF
  std::string v68; // [rsp+1E0h] [rbp-CA0h] BYREF
  char v69; // [rsp+1EFh] [rbp-C91h] BYREF
  std::string v70; // [rsp+1F0h] [rbp-C90h] BYREF
  char v71; // [rsp+1FFh] [rbp-C81h] BYREF
  std::string v72; // [rsp+200h] [rbp-C80h] BYREF
  char v73; // [rsp+20Bh] [rbp-C75h] BYREF
  int __x; // [rsp+20Ch] [rbp-C74h] BYREF
  std::string v75; // [rsp+210h] [rbp-C70h] BYREF
  char v76; // [rsp+21Fh] [rbp-C61h] BYREF
  std::string v77; // [rsp+220h] [rbp-C60h] BYREF
  char v78; // [rsp+22Fh] [rbp-C51h] BYREF
  MemChrBagVector v79; // [rsp+230h] [rbp-C50h] BYREF
  Answer::Inifile v80; // [rsp+250h] [rbp-C30h] BYREF
  char v81; // [rsp+28Fh] [rbp-BF1h] BYREF
  std::string v82; // [rsp+290h] [rbp-BF0h] BYREF
  char v83; // [rsp+29Fh] [rbp-BE1h] BYREF
  std::string v84; // [rsp+2A0h] [rbp-BE0h] BYREF
  char v85; // [rsp+2AFh] [rbp-BD1h] BYREF
  std::string v86; // [rsp+2B0h] [rbp-BD0h] BYREF
  char v87; // [rsp+2BFh] [rbp-BC1h] BYREF
  std::string v88; // [rsp+2C0h] [rbp-BC0h] BYREF
  char v89; // [rsp+2CFh] [rbp-BB1h] BYREF
  std::string v90; // [rsp+2D0h] [rbp-BB0h] BYREF
  char v91; // [rsp+2DFh] [rbp-BA1h] BYREF
  std::string v92; // [rsp+2E0h] [rbp-BA0h] BYREF
  char v93; // [rsp+2EFh] [rbp-B91h] BYREF
  std::string v94; // [rsp+2F0h] [rbp-B90h] BYREF
  char v95; // [rsp+2FFh] [rbp-B81h] BYREF
  std::string v96; // [rsp+300h] [rbp-B80h] BYREF
  char v97; // [rsp+30Fh] [rbp-B71h] BYREF
  std::string v98; // [rsp+310h] [rbp-B70h] BYREF
  char v99; // [rsp+31Fh] [rbp-B61h] BYREF
  std::string v100; // [rsp+320h] [rbp-B60h] BYREF
  char v101; // [rsp+32Fh] [rbp-B51h] BYREF
  std::string v102; // [rsp+330h] [rbp-B50h] BYREF
  char v103; // [rsp+33Fh] [rbp-B41h] BYREF
  std::string v104; // [rsp+340h] [rbp-B40h] BYREF
  char v105; // [rsp+34Fh] [rbp-B31h] BYREF
  std::string v106; // [rsp+350h] [rbp-B30h] BYREF
  char v107; // [rsp+35Fh] [rbp-B21h] BYREF
  std::string v108; // [rsp+360h] [rbp-B20h] BYREF
  char v109; // [rsp+36Fh] [rbp-B11h] BYREF
  std::string v110; // [rsp+370h] [rbp-B10h] BYREF
  char v111; // [rsp+37Fh] [rbp-B01h] BYREF
  std::string v112; // [rsp+380h] [rbp-B00h] BYREF
  char v113; // [rsp+38Fh] [rbp-AF1h] BYREF
  std::string v114; // [rsp+390h] [rbp-AF0h] BYREF
  char v115; // [rsp+39Fh] [rbp-AE1h] BYREF
  std::string v116; // [rsp+3A0h] [rbp-AE0h] BYREF
  char v117; // [rsp+3AFh] [rbp-AD1h] BYREF
  std::string v118; // [rsp+3B0h] [rbp-AD0h] BYREF
  char v119; // [rsp+3BFh] [rbp-AC1h] BYREF
  std::string v120; // [rsp+3C0h] [rbp-AC0h] BYREF
  char v121; // [rsp+3CFh] [rbp-AB1h] BYREF
  std::string v122; // [rsp+3D0h] [rbp-AB0h] BYREF
  char v123; // [rsp+3DFh] [rbp-AA1h] BYREF
  std::string v124; // [rsp+3E0h] [rbp-AA0h] BYREF
  char v125; // [rsp+3EFh] [rbp-A91h] BYREF
  std::string v126; // [rsp+3F0h] [rbp-A90h] BYREF
  char v127; // [rsp+3FFh] [rbp-A81h] BYREF
  std::string v128; // [rsp+400h] [rbp-A80h] BYREF
  char v129; // [rsp+40Fh] [rbp-A71h] BYREF
  std::string v130; // [rsp+410h] [rbp-A70h] BYREF
  char v131; // [rsp+41Fh] [rbp-A61h] BYREF
  std::string v132; // [rsp+420h] [rbp-A60h] BYREF
  char v133; // [rsp+42Fh] [rbp-A51h] BYREF
  std::string v134; // [rsp+430h] [rbp-A50h] BYREF
  char v135; // [rsp+43Fh] [rbp-A41h] BYREF
  std::string v136; // [rsp+440h] [rbp-A40h] BYREF
  char v137; // [rsp+44Fh] [rbp-A31h] BYREF
  std::string v138; // [rsp+450h] [rbp-A30h] BYREF
  char v139; // [rsp+45Fh] [rbp-A21h] BYREF
  std::string v140; // [rsp+460h] [rbp-A20h] BYREF
  char v141; // [rsp+46Fh] [rbp-A11h] BYREF
  std::string v142; // [rsp+470h] [rbp-A10h] BYREF
  char v143; // [rsp+47Fh] [rbp-A01h] BYREF
  std::string v144; // [rsp+480h] [rbp-A00h] BYREF
  char v145; // [rsp+48Fh] [rbp-9F1h] BYREF
  std::string v146; // [rsp+490h] [rbp-9F0h] BYREF
  char v147; // [rsp+49Fh] [rbp-9E1h] BYREF
  std::string v148; // [rsp+4A0h] [rbp-9E0h] BYREF
  char v149; // [rsp+4AFh] [rbp-9D1h] BYREF
  std::string v150; // [rsp+4B0h] [rbp-9D0h] BYREF
  char v151; // [rsp+4BFh] [rbp-9C1h] BYREF
  std::string v152; // [rsp+4C0h] [rbp-9C0h] BYREF
  char v153; // [rsp+4CFh] [rbp-9B1h] BYREF
  std::string v154; // [rsp+4D0h] [rbp-9B0h] BYREF
  char v155; // [rsp+4DFh] [rbp-9A1h] BYREF
  std::string v156; // [rsp+4E0h] [rbp-9A0h] BYREF
  char v157; // [rsp+4EFh] [rbp-991h] BYREF
  std::string v158; // [rsp+4F0h] [rbp-990h] BYREF
  char v159; // [rsp+4FFh] [rbp-981h] BYREF
  std::string v160; // [rsp+500h] [rbp-980h] BYREF
  char v161; // [rsp+50Fh] [rbp-971h] BYREF
  std::string v162; // [rsp+510h] [rbp-970h] BYREF
  char v163; // [rsp+51Fh] [rbp-961h] BYREF
  ShopGoods p___x; // [rsp+520h] [rbp-960h] BYREF
  std::string v165; // [rsp+540h] [rbp-940h] BYREF
  char v166; // [rsp+54Fh] [rbp-931h] BYREF
  std::string v167; // [rsp+550h] [rbp-930h] BYREF
  char v168; // [rsp+55Fh] [rbp-921h] BYREF
  MemChrBagVector v169; // [rsp+560h] [rbp-920h] BYREF
  Answer::Inifile v170; // [rsp+580h] [rbp-900h] BYREF
  char v171; // [rsp+5BFh] [rbp-8C1h] BYREF
  std::string v172; // [rsp+5C0h] [rbp-8C0h] BYREF
  char v173; // [rsp+5CFh] [rbp-8B1h] BYREF
  std::string v174; // [rsp+5D0h] [rbp-8B0h] BYREF
  char v175; // [rsp+5DFh] [rbp-8A1h] BYREF
  std::string v176; // [rsp+5E0h] [rbp-8A0h] BYREF
  char v177; // [rsp+5EFh] [rbp-891h] BYREF
  std::string v178; // [rsp+5F0h] [rbp-890h] BYREF
  char v179; // [rsp+5FFh] [rbp-881h] BYREF
  std::string v180; // [rsp+600h] [rbp-880h] BYREF
  char v181; // [rsp+60Fh] [rbp-871h] BYREF
  std::string v182; // [rsp+610h] [rbp-870h] BYREF
  char v183; // [rsp+61Fh] [rbp-861h] BYREF
  std::string v184; // [rsp+620h] [rbp-860h] BYREF
  char v185; // [rsp+62Fh] [rbp-851h] BYREF
  ShopGoods v186; // [rsp+630h] [rbp-850h] BYREF
  std::string v187; // [rsp+650h] [rbp-830h] BYREF
  char v188; // [rsp+65Fh] [rbp-821h] BYREF
  std::string v189; // [rsp+660h] [rbp-820h] BYREF
  char v190; // [rsp+66Fh] [rbp-811h] BYREF
  MemChrBagVector v191; // [rsp+670h] [rbp-810h] BYREF
  Answer::Inifile v192; // [rsp+690h] [rbp-7F0h] BYREF
  char v193; // [rsp+6CFh] [rbp-7B1h] BYREF
  std::string v194; // [rsp+6D0h] [rbp-7B0h] BYREF
  char v195; // [rsp+6DFh] [rbp-7A1h] BYREF
  std::string v196; // [rsp+6E0h] [rbp-7A0h] BYREF
  char v197; // [rsp+6EFh] [rbp-791h] BYREF
  std::string v198; // [rsp+6F0h] [rbp-790h] BYREF
  char v199; // [rsp+6FFh] [rbp-781h] BYREF
  std::string v200; // [rsp+700h] [rbp-780h] BYREF
  char v201; // [rsp+70Fh] [rbp-771h] BYREF
  std::string v202; // [rsp+710h] [rbp-770h] BYREF
  char v203; // [rsp+71Fh] [rbp-761h] BYREF
  std::string v204; // [rsp+720h] [rbp-760h] BYREF
  char v205; // [rsp+72Fh] [rbp-751h] BYREF
  std::string v206; // [rsp+730h] [rbp-750h] BYREF
  char v207; // [rsp+73Fh] [rbp-741h] BYREF
  ShopGoods v208; // [rsp+740h] [rbp-740h] BYREF
  std::string v209; // [rsp+760h] [rbp-720h] BYREF
  char v210; // [rsp+76Fh] [rbp-711h] BYREF
  std::string v211; // [rsp+770h] [rbp-710h] BYREF
  char v212; // [rsp+77Fh] [rbp-701h] BYREF
  MemChrBagVector v213; // [rsp+780h] [rbp-700h] BYREF
  Answer::Inifile v214; // [rsp+7A0h] [rbp-6E0h] BYREF
  char v215; // [rsp+7DFh] [rbp-6A1h] BYREF
  std::string v216; // [rsp+7E0h] [rbp-6A0h] BYREF
  char v217; // [rsp+7EFh] [rbp-691h] BYREF
  std::string v218; // [rsp+7F0h] [rbp-690h] BYREF
  char v219; // [rsp+7FFh] [rbp-681h] BYREF
  std::string v220; // [rsp+800h] [rbp-680h] BYREF
  char v221; // [rsp+80Fh] [rbp-671h] BYREF
  std::string v222; // [rsp+810h] [rbp-670h] BYREF
  char v223; // [rsp+81Fh] [rbp-661h] BYREF
  std::string v224; // [rsp+820h] [rbp-660h] BYREF
  char v225; // [rsp+82Fh] [rbp-651h] BYREF
  std::string v226; // [rsp+830h] [rbp-650h] BYREF
  char v227; // [rsp+83Fh] [rbp-641h] BYREF
  std::string v228; // [rsp+840h] [rbp-640h] BYREF
  char v229; // [rsp+84Fh] [rbp-631h] BYREF
  std::string v230; // [rsp+850h] [rbp-630h] BYREF
  char v231; // [rsp+85Fh] [rbp-621h] BYREF
  std::string v232; // [rsp+860h] [rbp-620h] BYREF
  char v233; // [rsp+86Fh] [rbp-611h] BYREF
  std::string v234; // [rsp+870h] [rbp-610h] BYREF
  char v235; // [rsp+87Fh] [rbp-601h] BYREF
  std::string v236; // [rsp+880h] [rbp-600h] BYREF
  char v237; // [rsp+88Fh] [rbp-5F1h] BYREF
  MemChrBagVector v238; // [rsp+890h] [rbp-5F0h] BYREF
  Answer::Inifile v239; // [rsp+8B0h] [rbp-5D0h] BYREF
  char v240; // [rsp+8EFh] [rbp-591h] BYREF
  std::string v241; // [rsp+8F0h] [rbp-590h] BYREF
  char v242; // [rsp+8FFh] [rbp-581h] BYREF
  std::string v243; // [rsp+900h] [rbp-580h] BYREF
  char v244; // [rsp+90Fh] [rbp-571h] BYREF
  std::string v245; // [rsp+910h] [rbp-570h] BYREF
  char v246; // [rsp+91Fh] [rbp-561h] BYREF
  std::string v247; // [rsp+920h] [rbp-560h] BYREF
  char v248; // [rsp+92Fh] [rbp-551h] BYREF
  std::string v249; // [rsp+930h] [rbp-550h] BYREF
  char v250; // [rsp+93Fh] [rbp-541h] BYREF
  std::string v251; // [rsp+940h] [rbp-540h] BYREF
  char v252; // [rsp+94Fh] [rbp-531h] BYREF
  std::string v253; // [rsp+950h] [rbp-530h] BYREF
  char v254; // [rsp+95Fh] [rbp-521h] BYREF
  std::string v255; // [rsp+960h] [rbp-520h] BYREF
  char v256; // [rsp+96Fh] [rbp-511h] BYREF
  std::string v257; // [rsp+970h] [rbp-510h] BYREF
  char v258; // [rsp+97Fh] [rbp-501h] BYREF
  std::string v259; // [rsp+980h] [rbp-500h] BYREF
  char v260; // [rsp+98Fh] [rbp-4F1h] BYREF
  std::string v261; // [rsp+990h] [rbp-4F0h] BYREF
  char v262; // [rsp+99Fh] [rbp-4E1h] BYREF
  std::vector<MemChrBag> v263; // [rsp+9A0h] [rbp-4E0h] BYREF
  std::string v264; // [rsp+9C0h] [rbp-4C0h] BYREF
  char v265; // [rsp+9CFh] [rbp-4B1h] BYREF
  std::string v266; // [rsp+9D0h] [rbp-4B0h] BYREF
  char v267; // [rsp+9DFh] [rbp-4A1h] BYREF
  MemChrBagVector v268; // [rsp+9E0h] [rbp-4A0h] BYREF
  Answer::Inifile v269; // [rsp+A00h] [rbp-480h] BYREF
  char v270; // [rsp+A3Fh] [rbp-441h] BYREF
  std::string v271; // [rsp+A40h] [rbp-440h] BYREF
  char v272; // [rsp+A4Fh] [rbp-431h] BYREF
  std::string v273; // [rsp+A50h] [rbp-430h] BYREF
  char v274; // [rsp+A5Fh] [rbp-421h] BYREF
  std::string v275; // [rsp+A60h] [rbp-420h] BYREF
  char v276; // [rsp+A6Fh] [rbp-411h] BYREF
  std::string v277; // [rsp+A70h] [rbp-410h] BYREF
  char v278; // [rsp+A7Fh] [rbp-401h] BYREF
  std::string v279; // [rsp+A80h] [rbp-400h] BYREF
  char v280; // [rsp+A8Fh] [rbp-3F1h] BYREF
  ItemData v281; // [rsp+A90h] [rbp-3F0h]
  std::string v282; // [rsp+AA0h] [rbp-3E0h] BYREF
  char v283; // [rsp+AAFh] [rbp-3D1h] BYREF
  std::string v284; // [rsp+AB0h] [rbp-3D0h] BYREF
  char v285; // [rsp+ABFh] [rbp-3C1h] BYREF
  Answer::Inifile v286; // [rsp+AC0h] [rbp-3C0h] BYREF
  char v287; // [rsp+AFFh] [rbp-381h] BYREF
  std::string v288; // [rsp+B00h] [rbp-380h] BYREF
  char v289; // [rsp+B0Fh] [rbp-371h] BYREF
  std::string v290; // [rsp+B10h] [rbp-370h] BYREF
  char v291; // [rsp+B1Fh] [rbp-361h] BYREF
  std::string v292; // [rsp+B20h] [rbp-360h] BYREF
  char v293; // [rsp+B2Fh] [rbp-351h] BYREF
  std::string v294; // [rsp+B30h] [rbp-350h] BYREF
  char v295; // [rsp+B3Fh] [rbp-341h] BYREF
  std::string v296; // [rsp+B40h] [rbp-340h] BYREF
  char v297; // [rsp+B4Fh] [rbp-331h] BYREF
  MemChrBag v298; // [rsp+B50h] [rbp-330h]
  ItemData v299; // [rsp+B70h] [rbp-310h]
  Answer::Inifile v300; // [rsp+B80h] [rbp-300h] BYREF
  char v301; // [rsp+BBFh] [rbp-2C1h] BYREF
  std::string v302; // [rsp+BC0h] [rbp-2C0h] BYREF
  char v303; // [rsp+BCFh] [rbp-2B1h] BYREF
  std::string v304; // [rsp+BD0h] [rbp-2B0h] BYREF
  char v305; // [rsp+BDFh] [rbp-2A1h] BYREF
  std::string v306; // [rsp+BE0h] [rbp-2A0h] BYREF
  char v307; // [rsp+BEFh] [rbp-291h] BYREF
  Answer::Inifile v308; // [rsp+BF0h] [rbp-290h] BYREF
  char v309; // [rsp+C2Fh] [rbp-251h] BYREF
  std::string v310; // [rsp+C30h] [rbp-250h] BYREF
  char v311; // [rsp+C3Fh] [rbp-241h] BYREF
  std::string v312; // [rsp+C40h] [rbp-240h] BYREF
  char v313; // [rsp+C4Fh] [rbp-231h] BYREF
  std::string v314; // [rsp+C50h] [rbp-230h] BYREF
  char v315; // [rsp+C5Fh] [rbp-221h] BYREF
  std::string v316; // [rsp+C60h] [rbp-220h] BYREF
  char v317; // [rsp+C6Fh] [rbp-211h] BYREF
  std::string v318; // [rsp+C70h] [rbp-210h] BYREF
  char v319; // [rsp+C7Fh] [rbp-201h] BYREF
  MemChrBag v320; // [rsp+C80h] [rbp-200h]
  Answer::Inifile v321; // [rsp+CA0h] [rbp-1E0h] BYREF
  char v322; // [rsp+CDFh] [rbp-1A1h] BYREF
  std::string v323; // [rsp+CE0h] [rbp-1A0h] BYREF
  char v324; // [rsp+CEFh] [rbp-191h] BYREF
  std::string v325; // [rsp+CF0h] [rbp-190h] BYREF
  char v326; // [rsp+CFFh] [rbp-181h] BYREF
  std::string v327; // [rsp+D00h] [rbp-180h] BYREF
  char v328; // [rsp+D0Fh] [rbp-171h] BYREF
  std::string v329; // [rsp+D10h] [rbp-170h] BYREF
  char v330; // [rsp+D1Fh] [rbp-161h] BYREF
  std::string v331; // [rsp+D20h] [rbp-160h] BYREF
  char v332; // [rsp+D2Fh] [rbp-151h] BYREF
  std::string v333; // [rsp+D30h] [rbp-150h] BYREF
  char v334; // [rsp+D3Fh] [rbp-141h] BYREF
  std::string v335; // [rsp+D40h] [rbp-140h] BYREF
  char v336; // [rsp+D4Fh] [rbp-131h] BYREF
  MemChrBag v337; // [rsp+D50h] [rbp-130h]
  Answer::Inifile v338; // [rsp+D70h] [rbp-110h] BYREF
  char v339; // [rsp+DAFh] [rbp-D1h] BYREF
  std::string v340; // [rsp+DB0h] [rbp-D0h] BYREF
  char v341; // [rsp+DBFh] [rbp-C1h] BYREF
  std::string v342; // [rsp+DC0h] [rbp-C0h] BYREF
  char v343; // [rsp+DCFh] [rbp-B1h] BYREF
  std::string v344; // [rsp+DD0h] [rbp-B0h] BYREF
  char v345; // [rsp+DDFh] [rbp-A1h] BYREF
  std::string v346; // [rsp+DE0h] [rbp-A0h] BYREF
  char v347; // [rsp+DEFh] [rbp-91h] BYREF
  std::string v348; // [rsp+DF0h] [rbp-90h] BYREF
  char v349; // [rsp+DFFh] [rbp-81h] BYREF
  std::string v350; // [rsp+E00h] [rbp-80h] BYREF
  char v351; // [rsp+E0Fh] [rbp-71h] BYREF
  std::string v352; // [rsp+E10h] [rbp-70h] BYREF
  char v353; // [rsp+E1Fh] [rbp-61h] BYREF
  std::string v354; // [rsp+E20h] [rbp-60h] BYREF
  char v355; // [rsp+E2Fh] [rbp-51h] BYREF
  std::string v356; // [rsp+E30h] [rbp-50h] BYREF
  char v357; // [rsp+E43h] [rbp-3Dh] BYREF
  int32_t nBossCount; // [rsp+E44h] [rbp-3Ch]
  int32_t i; // [rsp+E48h] [rbp-38h]
  int32_t i_0; // [rsp+E4Ch] [rbp-34h]
  int32_t i_1; // [rsp+E50h] [rbp-30h]
  int32_t i_2; // [rsp+E54h] [rbp-2Ch]
  int32_t i_3; // [rsp+E58h] [rbp-28h]
  int32_t i_4; // [rsp+E5Ch] [rbp-24h]
  int32_t i_5; // [rsp+E60h] [rbp-20h]
  int32_t i_6; // [rsp+E64h] [rbp-1Ch]
  int32_t i_7; // [rsp+E68h] [rbp-18h]
  int32_t i_8; // [rsp+E6Ch] [rbp-14h]
  ItemData v369; // 0:kr00_12.12
  ItemData v370; // 0:kr14_12.12

  thisa = this;
  linea = line;
  if ( line != 9 )
  {
    v2 = Answer::Singleton<CTimer>::instance();
    CTimer::GetLocalNow(&nowTime, v2);
    thisa->m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
    Answer::Inifile::Inifile(&ini);
    std::allocator<char>::allocator(&v53);
    std::string::string(&file, "./ServerConfig/Tables/OpenBetaAct.cfg");
    Answer::Inifile::parse(&ini, &file);
    std::string::~string(&file);
    std::allocator<char>::~allocator(&v53);
    memset(szCol, 0, sizeof(szCol));
    std::allocator<char>::allocator((char *)&v54.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(&v54.m_strMap._M_t._M_impl._M_header._M_parent, "start_time");
    std::allocator<char>::allocator((char *)&v54.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(&v54.m_strMap._M_t._M_impl._M_header._M_right, "CONFIG");
    Answer::Inifile::getStrValue(
      &v54,
      (const std::string *const)&ini,
      (const std::string *const)&v54.m_strMap._M_t._M_impl._M_header._M_right);
    thisa->m_nStartDay = Answer::DayTime::StringToIntTime((std::string *)&v54);
    std::string::~string(&v54);
    std::string::~string(&v54.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v54.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v54.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v54.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator(&v55);
    std::string::string(&v54.m_currentSection, "end_day");
    std::allocator<char>::allocator(&v57);
    std::string::string(&section, "CONFIG");
    thisa->m_nEndDay = Answer::Inifile::getIntValue(&ini, &section, &v54.m_currentSection);
    std::string::~string(&section);
    std::allocator<char>::~allocator(&v57);
    std::string::~string(&v54.m_currentSection);
    std::allocator<char>::~allocator(&v55);
    std::allocator<char>::allocator(&v59);
    std::string::string(&key, "icon");
    std::allocator<char>::allocator(&v61);
    std::string::string(&v60, "CONFIG");
    thisa->m_nIcon = Answer::Inifile::getIntValue(&ini, &v60, &key);
    std::string::~string(&v60);
    std::allocator<char>::~allocator(&v61);
    std::string::~string(&key);
    std::allocator<char>::~allocator(&v59);
    v3 = Answer::DayTime::now();
    v4 = Answer::DayTime::dayzero(v3);
    thisa->m_nDay = (v4 - Answer::DayTime::dayzero(thisa->m_nStartDay)) / 86400;
    std::allocator<char>::allocator(&v63);
    std::string::string(&v62, "start_day");
    std::allocator<char>::allocator(&v65);
    std::string::string(&v64, "RECHARGE");
    thisa->m_vStartDay[2] = Answer::Inifile::getIntValue(&ini, &v64, &v62);
    std::string::~string(&v64);
    std::allocator<char>::~allocator(&v65);
    std::string::~string(&v62);
    std::allocator<char>::~allocator(&v63);
    std::allocator<char>::allocator(&v67);
    std::string::string(&v66, "end_day");
    std::allocator<char>::allocator(&v69);
    std::string::string(&v68, "RECHARGE");
    thisa->m_vEndDay[2] = Answer::Inifile::getIntValue(&ini, &v68, &v66);
    std::string::~string(&v68);
    std::allocator<char>::~allocator(&v69);
    std::string::~string(&v66);
    std::allocator<char>::~allocator(&v67);
    std::allocator<char>::allocator(&v71);
    std::string::string(&v70, "size");
    std::allocator<char>::allocator(&v73);
    std::string::string(&v72, "RECHARGE");
    thisa->m_nRechargeDaysSize = Answer::Inifile::getIntValue(&ini, &v72, &v70);
    std::string::~string(&v72);
    std::allocator<char>::~allocator(&v73);
    std::string::~string(&v70);
    std::allocator<char>::~allocator(&v71);
    std::vector<int>::reserve(&thisa->m_vRechargeValue, thisa->m_nRechargeDaysSize);
    std::vector<std::vector<MemChrBag>>::reserve(&thisa->m_vRechargeGift, thisa->m_nRechargeDaysSize);
    for ( i = 0; thisa->m_nRechargeDaysSize > i; ++i )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "gold%d", i + 1);
      std::allocator<char>::allocator(&v76);
      std::string::string(&v75, szCol);
      std::allocator<char>::allocator(&v78);
      std::string::string(&v77, "RECHARGE");
      __x = Answer::Inifile::getIntValue(&ini, &v77, &v75);
      std::vector<int>::push_back(&thisa->m_vRechargeValue, &__x);
      std::string::~string(&v77);
      std::allocator<char>::~allocator(&v78);
      std::string::~string(&v75);
      std::allocator<char>::~allocator(&v76);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "gift%d", i + 1);
      std::allocator<char>::allocator((char *)&v80.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v80.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v80.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v80.m_strMap._M_t._M_impl._M_header._M_right, "RECHARGE");
      Answer::Inifile::getStrValue(
        &v80,
        (const std::string *const)&ini,
        (const std::string *const)&v80.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v79, (const std::string *const)&v80);
      std::vector<std::vector<MemChrBag>>::push_back(&thisa->m_vRechargeGift, &v79);
      std::vector<MemChrBag>::~vector(&v79);
      std::string::~string(&v80);
      std::string::~string(&v80.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v80.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v80.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v80.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::allocator<char>::allocator(&v81);
    std::string::string(&v80.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v83);
    std::string::string(&v82, "CHOU_JIANG");
    thisa->m_vStartDay[4] = Answer::Inifile::getIntValue(&ini, &v82, &v80.m_currentSection);
    std::string::~string(&v82);
    std::allocator<char>::~allocator(&v83);
    std::string::~string(&v80.m_currentSection);
    std::allocator<char>::~allocator(&v81);
    std::allocator<char>::allocator(&v85);
    std::string::string(&v84, "end_day");
    std::allocator<char>::allocator(&v87);
    std::string::string(&v86, "CHOU_JIANG");
    thisa->m_vEndDay[4] = Answer::Inifile::getIntValue(&ini, &v86, &v84);
    std::string::~string(&v86);
    std::allocator<char>::~allocator(&v87);
    std::string::~string(&v84);
    std::allocator<char>::~allocator(&v85);
    std::allocator<char>::allocator(&v89);
    std::string::string(&v88, "Type");
    std::allocator<char>::allocator(&v91);
    std::string::string(&v90, "CHOU_JIANG");
    thisa->m_ChouJiangType = Answer::Inifile::getIntValue(&ini, &v90, &v88);
    std::string::~string(&v90);
    std::allocator<char>::~allocator(&v91);
    std::string::~string(&v88);
    std::allocator<char>::~allocator(&v89);
    std::allocator<char>::allocator(&v93);
    std::string::string(&v92, "start_day");
    std::allocator<char>::allocator(&v95);
    std::string::string(&v94, "COLLECT_DROP");
    thisa->m_vStartDay[8] = Answer::Inifile::getIntValue(&ini, &v94, &v92);
    std::string::~string(&v94);
    std::allocator<char>::~allocator(&v95);
    std::string::~string(&v92);
    std::allocator<char>::~allocator(&v93);
    std::allocator<char>::allocator(&v97);
    std::string::string(&v96, "end_day");
    std::allocator<char>::allocator(&v99);
    std::string::string(&v98, "COLLECT_DROP");
    thisa->m_vEndDay[8] = Answer::Inifile::getIntValue(&ini, &v98, &v96);
    std::string::~string(&v98);
    std::allocator<char>::~allocator(&v99);
    std::string::~string(&v96);
    std::allocator<char>::~allocator(&v97);
    std::allocator<char>::allocator(&v101);
    std::string::string(&v100, "start_day");
    std::allocator<char>::allocator(&v103);
    std::string::string(&v102, "BOSS");
    thisa->m_vStartDay[9] = Answer::Inifile::getIntValue(&ini, &v102, &v100);
    std::string::~string(&v102);
    std::allocator<char>::~allocator(&v103);
    std::string::~string(&v100);
    std::allocator<char>::~allocator(&v101);
    std::allocator<char>::allocator(&v105);
    std::string::string(&v104, "end_day");
    std::allocator<char>::allocator(&v107);
    std::string::string(&v106, "BOSS");
    thisa->m_vEndDay[9] = Answer::Inifile::getIntValue(&ini, &v106, &v104);
    std::string::~string(&v106);
    std::allocator<char>::~allocator(&v107);
    std::string::~string(&v104);
    std::allocator<char>::~allocator(&v105);
    std::allocator<char>::allocator(&v109);
    std::string::string(&v108, "icon");
    std::allocator<char>::allocator(&v111);
    std::string::string(&v110, "BOSS");
    thisa->m_nBossIcon = Answer::Inifile::getIntValue(&ini, &v110, &v108);
    std::string::~string(&v110);
    std::allocator<char>::~allocator(&v111);
    std::string::~string(&v108);
    std::allocator<char>::~allocator(&v109);
    std::allocator<char>::allocator(&v113);
    std::string::string(&v112, "start_broadcast");
    std::allocator<char>::allocator(&v115);
    std::string::string(&v114, "BOSS");
    thisa->m_nBossStartBroadcast = Answer::Inifile::getIntValue(&ini, &v114, &v112);
    std::string::~string(&v114);
    std::allocator<char>::~allocator(&v115);
    std::string::~string(&v112);
    std::allocator<char>::~allocator(&v113);
    std::allocator<char>::allocator(&v117);
    std::string::string(&v116, "end_broadcast");
    std::allocator<char>::allocator(&v119);
    std::string::string(&v118, "BOSS");
    thisa->m_nBossEndBroadcast = Answer::Inifile::getIntValue(&ini, &v118, &v116);
    std::string::~string(&v118);
    std::allocator<char>::~allocator(&v119);
    std::string::~string(&v116);
    std::allocator<char>::~allocator(&v117);
    std::allocator<char>::allocator(&v121);
    std::string::string(&v120, "kill_broadcast");
    std::allocator<char>::allocator(&v123);
    std::string::string(&v122, "BOSS");
    thisa->m_nBossKillBroadcast = Answer::Inifile::getIntValue(&ini, &v122, &v120);
    std::string::~string(&v122);
    std::allocator<char>::~allocator(&v123);
    std::string::~string(&v120);
    std::allocator<char>::~allocator(&v121);
    std::allocator<char>::allocator(&v125);
    std::string::string(&v124, "count");
    std::allocator<char>::allocator(&v127);
    std::string::string(&v126, "BOSS");
    nBossCount = Answer::Inifile::getIntValue(&ini, &v126, &v124);
    std::string::~string(&v126);
    std::allocator<char>::~allocator(&v127);
    std::string::~string(&v124);
    std::allocator<char>::~allocator(&v125);
    std::vector<TimeArea>::reserve(&thisa->m_vBossMinute, nBossCount);
    for ( i_0 = 0; i_0 < nBossCount; ++i_0 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "start_minute%d", i_0 + 1);
      std::allocator<char>::allocator(&v129);
      std::string::string(&v128, szCol);
      std::allocator<char>::allocator(&v131);
      std::string::string(&v130, "BOSS");
      tarea.nStartTime = Answer::Inifile::getIntValue(&ini, &v130, &v128);
      std::string::~string(&v130);
      std::allocator<char>::~allocator(&v131);
      std::string::~string(&v128);
      std::allocator<char>::~allocator(&v129);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "end_minute%d", i_0 + 1);
      std::allocator<char>::allocator(&v133);
      std::string::string(&v132, szCol);
      std::allocator<char>::allocator(&v135);
      std::string::string(&v134, "BOSS");
      tarea.nEndTime = Answer::Inifile::getIntValue(&ini, &v134, &v132);
      std::string::~string(&v134);
      std::allocator<char>::~allocator(&v135);
      std::string::~string(&v132);
      std::allocator<char>::~allocator(&v133);
      std::vector<TimeArea>::push_back(&thisa->m_vBossMinute, &tarea);
    }
    std::allocator<char>::allocator(&v137);
    std::string::string(&v136, "mapid");
    std::allocator<char>::allocator(&v139);
    std::string::string(&v138, "BOSS");
    thisa->m_MapId = Answer::Inifile::getIntValue(&ini, &v138, &v136);
    std::string::~string(&v138);
    std::allocator<char>::~allocator(&v139);
    std::string::~string(&v136);
    std::allocator<char>::~allocator(&v137);
    std::allocator<char>::allocator(&v141);
    std::string::string(&v140, "x");
    std::allocator<char>::allocator(&v143);
    std::string::string(&v142, "BOSS");
    thisa->m_X = Answer::Inifile::getIntValue(&ini, &v142, &v140);
    std::string::~string(&v142);
    std::allocator<char>::~allocator(&v143);
    std::string::~string(&v140);
    std::allocator<char>::~allocator(&v141);
    std::allocator<char>::allocator(&v145);
    std::string::string(&v144, "y");
    std::allocator<char>::allocator(&v147);
    std::string::string(&v146, "BOSS");
    thisa->m_Y = Answer::Inifile::getIntValue(&ini, &v146, &v144);
    std::string::~string(&v146);
    std::allocator<char>::~allocator(&v147);
    std::string::~string(&v144);
    std::allocator<char>::~allocator(&v145);
    std::allocator<char>::allocator(&v149);
    std::string::string(&v148, "mid");
    std::allocator<char>::allocator(&v151);
    std::string::string(&v150, "BOSS");
    thisa->m_Mid = Answer::Inifile::getIntValue(&ini, &v150, &v148);
    std::string::~string(&v150);
    std::allocator<char>::~allocator(&v151);
    std::string::~string(&v148);
    std::allocator<char>::~allocator(&v149);
    std::allocator<char>::allocator(&v153);
    std::string::string(&v152, "start_day");
    std::allocator<char>::allocator(&v155);
    std::string::string(&v154, "DAILY_LIMIT_SHOP");
    thisa->m_vStartDay[3] = Answer::Inifile::getIntValue(&ini, &v154, &v152);
    std::string::~string(&v154);
    std::allocator<char>::~allocator(&v155);
    std::string::~string(&v152);
    std::allocator<char>::~allocator(&v153);
    std::allocator<char>::allocator(&v157);
    std::string::string(&v156, "end_day");
    std::allocator<char>::allocator(&v159);
    std::string::string(&v158, "DAILY_LIMIT_SHOP");
    thisa->m_vEndDay[3] = Answer::Inifile::getIntValue(&ini, &v158, &v156);
    std::string::~string(&v158);
    std::allocator<char>::~allocator(&v159);
    std::string::~string(&v156);
    std::allocator<char>::~allocator(&v157);
    std::allocator<char>::allocator(&v161);
    std::string::string(&v160, "size");
    std::allocator<char>::allocator(&v163);
    std::string::string(&v162, "DAILY_LIMIT_SHOP");
    thisa->m_nDailyLimitShopSize = Answer::Inifile::getIntValue(&ini, &v162, &v160);
    std::string::~string(&v162);
    std::allocator<char>::~allocator(&v163);
    std::string::~string(&v160);
    std::allocator<char>::~allocator(&v161);
    memset(&p___x, 0, 28);
    ShopGoods::ShopGoods(&p___x);
    std::vector<ShopGoods>::resize(&thisa->m_vDailyLimitShopGoods, thisa->m_nDailyLimitShopSize, &p___x);
    ShopGoods::~ShopGoods(&p___x);
    std::vector<int>::resize(&thisa->m_vDailyLimitShopBroadcast, thisa->m_nDailyLimitShopSize, 0);
    for ( i_1 = 0; thisa->m_nDailyLimitShopSize > i_1; ++i_1 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_1 + 1);
      v5 = std::vector<ShopGoods>::operator[](&thisa->m_vDailyLimitShopGoods, i_1);
      std::allocator<char>::allocator(&v166);
      std::string::string(&v165, szCol);
      std::allocator<char>::allocator(&v168);
      std::string::string(&v167, "DAILY_LIMIT_SHOP");
      v5->nPrice = Answer::Inifile::getIntValue(&ini, &v167, &v165);
      std::string::~string(&v167);
      std::allocator<char>::~allocator(&v168);
      std::string::~string(&v165);
      std::allocator<char>::~allocator(&v166);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "goods%d", i_1 + 1);
      std::allocator<char>::allocator((char *)&v170.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v170.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v170.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v170.m_strMap._M_t._M_impl._M_header._M_right, "DAILY_LIMIT_SHOP");
      Answer::Inifile::getStrValue(
        &v170,
        (const std::string *const)&ini,
        (const std::string *const)&v170.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v169, (const std::string *const)&v170);
      v6 = std::vector<ShopGoods>::operator[](&thisa->m_vDailyLimitShopGoods, i_1);
      std::vector<MemChrBag>::operator=(&v6->vItem, &v169);
      std::vector<MemChrBag>::~vector(&v169);
      std::string::~string(&v170);
      std::string::~string(&v170.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v170.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v170.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v170.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_1 + 1);
      v7 = std::vector<int>::operator[](&thisa->m_vDailyLimitShopBroadcast, i_1);
      std::allocator<char>::allocator(&v171);
      std::string::string(&v170.m_currentSection, szCol);
      std::allocator<char>::allocator(&v173);
      std::string::string(&v172, "DAILY_LIMIT_SHOP");
      *v7 = Answer::Inifile::getIntValue(&ini, &v172, &v170.m_currentSection);
      std::string::~string(&v172);
      std::allocator<char>::~allocator(&v173);
      std::string::~string(&v170.m_currentSection);
      std::allocator<char>::~allocator(&v171);
    }
    std::allocator<char>::allocator(&v175);
    std::string::string(&v174, "start_day");
    std::allocator<char>::allocator(&v177);
    std::string::string(&v176, "TITLE");
    thisa->m_vStartDay[6] = Answer::Inifile::getIntValue(&ini, &v176, &v174);
    std::string::~string(&v176);
    std::allocator<char>::~allocator(&v177);
    std::string::~string(&v174);
    std::allocator<char>::~allocator(&v175);
    std::allocator<char>::allocator(&v179);
    std::string::string(&v178, "end_day");
    std::allocator<char>::allocator(&v181);
    std::string::string(&v180, "TITLE");
    thisa->m_vEndDay[6] = Answer::Inifile::getIntValue(&ini, &v180, &v178);
    std::string::~string(&v180);
    std::allocator<char>::~allocator(&v181);
    std::string::~string(&v178);
    std::allocator<char>::~allocator(&v179);
    std::allocator<char>::allocator(&v183);
    std::string::string(&v182, "size");
    std::allocator<char>::allocator(&v185);
    std::string::string(&v184, "TITLE");
    thisa->m_nTitleShopSize = Answer::Inifile::getIntValue(&ini, &v184, &v182);
    std::string::~string(&v184);
    std::allocator<char>::~allocator(&v185);
    std::string::~string(&v182);
    std::allocator<char>::~allocator(&v183);
    std::vector<int>::resize(&thisa->m_vTitleShopBroadcast, thisa->m_nTitleShopSize, 0);
    memset(&v186, 0, 28);
    ShopGoods::ShopGoods(&v186);
    std::vector<ShopGoods>::resize(&thisa->m_vTitleShopGoods, thisa->m_nTitleShopSize, &v186);
    ShopGoods::~ShopGoods(&v186);
    for ( i_2 = 0; thisa->m_nTitleShopSize > i_2; ++i_2 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_2 + 1);
      v8 = std::vector<ShopGoods>::operator[](&thisa->m_vTitleShopGoods, i_2);
      std::allocator<char>::allocator(&v188);
      std::string::string(&v187, szCol);
      std::allocator<char>::allocator(&v190);
      std::string::string(&v189, "TITLE");
      v8->nPrice = Answer::Inifile::getIntValue(&ini, &v189, &v187);
      std::string::~string(&v189);
      std::allocator<char>::~allocator(&v190);
      std::string::~string(&v187);
      std::allocator<char>::~allocator(&v188);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "goods%d", i_2 + 1);
      std::allocator<char>::allocator((char *)&v192.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v192.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v192.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v192.m_strMap._M_t._M_impl._M_header._M_right, "TITLE");
      Answer::Inifile::getStrValue(
        &v192,
        (const std::string *const)&ini,
        (const std::string *const)&v192.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v191, (const std::string *const)&v192);
      v9 = std::vector<ShopGoods>::operator[](&thisa->m_vTitleShopGoods, i_2);
      std::vector<MemChrBag>::operator=(&v9->vItem, &v191);
      std::vector<MemChrBag>::~vector(&v191);
      std::string::~string(&v192);
      std::string::~string(&v192.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v192.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v192.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v192.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_2 + 1);
      v10 = std::vector<int>::operator[](&thisa->m_vTitleShopBroadcast, i_2);
      std::allocator<char>::allocator(&v193);
      std::string::string(&v192.m_currentSection, szCol);
      std::allocator<char>::allocator(&v195);
      std::string::string(&v194, "TITLE");
      *v10 = Answer::Inifile::getIntValue(&ini, &v194, &v192.m_currentSection);
      std::string::~string(&v194);
      std::allocator<char>::~allocator(&v195);
      std::string::~string(&v192.m_currentSection);
      std::allocator<char>::~allocator(&v193);
    }
    std::allocator<char>::allocator(&v197);
    std::string::string(&v196, "start_day");
    std::allocator<char>::allocator(&v199);
    std::string::string(&v198, "SHI_ZHUANG");
    thisa->m_vStartDay[7] = Answer::Inifile::getIntValue(&ini, &v198, &v196);
    std::string::~string(&v198);
    std::allocator<char>::~allocator(&v199);
    std::string::~string(&v196);
    std::allocator<char>::~allocator(&v197);
    std::allocator<char>::allocator(&v201);
    std::string::string(&v200, "end_day");
    std::allocator<char>::allocator(&v203);
    std::string::string(&v202, "SHI_ZHUANG");
    thisa->m_vEndDay[7] = Answer::Inifile::getIntValue(&ini, &v202, &v200);
    std::string::~string(&v202);
    std::allocator<char>::~allocator(&v203);
    std::string::~string(&v200);
    std::allocator<char>::~allocator(&v201);
    std::allocator<char>::allocator(&v205);
    std::string::string(&v204, "size");
    std::allocator<char>::allocator(&v207);
    std::string::string(&v206, "SHI_ZHUANG");
    thisa->m_nShiZhuangShopSize = Answer::Inifile::getIntValue(&ini, &v206, &v204);
    std::string::~string(&v206);
    std::allocator<char>::~allocator(&v207);
    std::string::~string(&v204);
    std::allocator<char>::~allocator(&v205);
    std::vector<int>::resize(&thisa->m_vShiZhuangShopBroadcast, thisa->m_nShiZhuangShopSize, 0);
    memset(&v208, 0, 28);
    ShopGoods::ShopGoods(&v208);
    std::vector<ShopGoods>::resize(&thisa->m_vShizhuangShopGoods, thisa->m_nShiZhuangShopSize, &v208);
    ShopGoods::~ShopGoods(&v208);
    for ( i_3 = 0; thisa->m_nShiZhuangShopSize > i_3; ++i_3 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_3 + 1);
      v11 = std::vector<ShopGoods>::operator[](&thisa->m_vShizhuangShopGoods, i_3);
      std::allocator<char>::allocator(&v210);
      std::string::string(&v209, szCol);
      std::allocator<char>::allocator(&v212);
      std::string::string(&v211, "SHI_ZHUANG");
      v11->nPrice = Answer::Inifile::getIntValue(&ini, &v211, &v209);
      std::string::~string(&v211);
      std::allocator<char>::~allocator(&v212);
      std::string::~string(&v209);
      std::allocator<char>::~allocator(&v210);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "goods%d", i_3 + 1);
      std::allocator<char>::allocator((char *)&v214.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v214.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v214.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v214.m_strMap._M_t._M_impl._M_header._M_right, "SHI_ZHUANG");
      Answer::Inifile::getStrValue(
        &v214,
        (const std::string *const)&ini,
        (const std::string *const)&v214.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v213, (const std::string *const)&v214);
      v12 = std::vector<ShopGoods>::operator[](&thisa->m_vShizhuangShopGoods, i_3);
      std::vector<MemChrBag>::operator=(&v12->vItem, &v213);
      std::vector<MemChrBag>::~vector(&v213);
      std::string::~string(&v214);
      std::string::~string(&v214.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v214.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v214.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v214.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "broadcast%d", i_3 + 1);
      v13 = std::vector<int>::operator[](&thisa->m_vShiZhuangShopBroadcast, i_3);
      std::allocator<char>::allocator(&v215);
      std::string::string(&v214.m_currentSection, szCol);
      std::allocator<char>::allocator(&v217);
      std::string::string(&v216, "SHI_ZHUANG");
      *v13 = Answer::Inifile::getIntValue(&ini, &v216, &v214.m_currentSection);
      std::string::~string(&v216);
      std::allocator<char>::~allocator(&v217);
      std::string::~string(&v214.m_currentSection);
      std::allocator<char>::~allocator(&v215);
    }
    std::allocator<char>::allocator(&v219);
    std::string::string(&v218, "start_day");
    std::allocator<char>::allocator(&v221);
    std::string::string(&v220, "RED_PACK");
    thisa->m_vStartDay[1] = Answer::Inifile::getIntValue(&ini, &v220, &v218);
    std::string::~string(&v220);
    std::allocator<char>::~allocator(&v221);
    std::string::~string(&v218);
    std::allocator<char>::~allocator(&v219);
    std::allocator<char>::allocator(&v223);
    std::string::string(&v222, "end_day");
    std::allocator<char>::allocator(&v225);
    std::string::string(&v224, "RED_PACK");
    thisa->m_vEndDay[1] = Answer::Inifile::getIntValue(&ini, &v224, &v222);
    std::string::~string(&v224);
    std::allocator<char>::~allocator(&v225);
    std::string::~string(&v222);
    std::allocator<char>::~allocator(&v223);
    std::allocator<char>::allocator(&v227);
    std::string::string(&v226, "start_time");
    std::allocator<char>::allocator(&v229);
    std::string::string(&v228, "RED_PACK");
    thisa->m_nOnlineStartMinute = Answer::Inifile::getIntValue(&ini, &v228, &v226);
    std::string::~string(&v228);
    std::allocator<char>::~allocator(&v229);
    std::string::~string(&v226);
    std::allocator<char>::~allocator(&v227);
    std::allocator<char>::allocator(&v231);
    std::string::string(&v230, "end_time");
    std::allocator<char>::allocator(&v233);
    std::string::string(&v232, "RED_PACK");
    thisa->m_nOnlineEndMinute = Answer::Inifile::getIntValue(&ini, &v232, &v230);
    std::string::~string(&v232);
    std::allocator<char>::~allocator(&v233);
    std::string::~string(&v230);
    std::allocator<char>::~allocator(&v231);
    std::allocator<char>::allocator(&v235);
    std::string::string(&v234, "dis_time");
    std::allocator<char>::allocator(&v237);
    std::string::string(&v236, "RED_PACK");
    thisa->m_nOnlineTimeArea = 60 * Answer::Inifile::getIntValue(&ini, &v236, &v234);
    std::string::~string(&v236);
    std::allocator<char>::~allocator(&v237);
    std::string::~string(&v234);
    std::allocator<char>::~allocator(&v235);
    std::allocator<char>::allocator((char *)&v239.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(&v239.m_strMap._M_t._M_impl._M_header._M_parent, "reward");
    std::allocator<char>::allocator((char *)&v239.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(&v239.m_strMap._M_t._M_impl._M_header._M_right, "RED_PACK");
    Answer::Inifile::getStrValue(
      &v239,
      (const std::string *const)&ini,
      (const std::string *const)&v239.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v238, (const std::string *const)&v239);
    std::vector<MemChrBag>::operator=(&thisa->m_vOnlineReward, &v238);
    std::vector<MemChrBag>::~vector(&v238);
    std::string::~string(&v239);
    std::string::~string(&v239.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v239.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v239.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v239.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::allocator<char>::allocator(&v240);
    std::string::string(&v239.m_currentSection, "max_count");
    std::allocator<char>::allocator(&v242);
    std::string::string(&v241, "RED_PACK");
    thisa->m_nMaxCount = Answer::Inifile::getIntValue(&ini, &v241, &v239.m_currentSection);
    std::string::~string(&v241);
    std::allocator<char>::~allocator(&v242);
    std::string::~string(&v239.m_currentSection);
    std::allocator<char>::~allocator(&v240);
    std::allocator<char>::allocator(&v244);
    std::string::string(&v243, "start_day");
    std::allocator<char>::allocator(&v246);
    std::string::string(&v245, "XIAO_FEI_SUM_RANK");
    thisa->m_vStartDay[5] = Answer::Inifile::getIntValue(&ini, &v245, &v243);
    std::string::~string(&v245);
    std::allocator<char>::~allocator(&v246);
    std::string::~string(&v243);
    std::allocator<char>::~allocator(&v244);
    std::allocator<char>::allocator(&v248);
    std::string::string(&v247, "end_day");
    std::allocator<char>::allocator(&v250);
    std::string::string(&v249, "XIAO_FEI_SUM_RANK");
    thisa->m_vEndDay[5] = Answer::Inifile::getIntValue(&ini, &v249, &v247);
    std::string::~string(&v249);
    std::allocator<char>::~allocator(&v250);
    std::string::~string(&v247);
    std::allocator<char>::~allocator(&v248);
    std::allocator<char>::allocator(&v252);
    std::string::string(&v251, "show_size");
    std::allocator<char>::allocator(&v254);
    std::string::string(&v253, "XIAO_FEI_SUM_RANK");
    thisa->m_nShowSize = Answer::Inifile::getIntValue(&ini, &v253, &v251);
    std::string::~string(&v253);
    std::allocator<char>::~allocator(&v254);
    std::string::~string(&v251);
    std::allocator<char>::~allocator(&v252);
    std::allocator<char>::allocator(&v256);
    std::string::string(&v255, "size");
    std::allocator<char>::allocator(&v258);
    std::string::string(&v257, "XIAO_FEI_SUM_RANK");
    thisa->m_nXiaoFeiSumRankSize = Answer::Inifile::getIntValue(&ini, &v257, &v255);
    std::string::~string(&v257);
    std::allocator<char>::~allocator(&v258);
    std::string::~string(&v255);
    std::allocator<char>::~allocator(&v256);
    std::allocator<char>::allocator(&v260);
    std::string::string(&v259, "limit");
    std::allocator<char>::allocator(&v262);
    std::string::string(&v261, "XIAO_FEI_SUM_RANK");
    thisa->m_nXiaoFeiSumRankLimit = Answer::Inifile::getIntValue(&ini, &v261, &v259);
    std::string::~string(&v261);
    std::allocator<char>::~allocator(&v262);
    std::string::~string(&v259);
    std::allocator<char>::~allocator(&v260);
    std::vector<int>::resize(&thisa->m_vXiaoFeiSumRankMail, thisa->m_nXiaoFeiSumRankSize, 0);
    std::vector<MemChrBag>::vector(&v263);
    std::vector<std::vector<MemChrBag>>::resize(&thisa->m_vXiaoFeiSumRankReward, thisa->m_nXiaoFeiSumRankSize, &v263);
    std::vector<MemChrBag>::~vector(&v263);
    for ( i_4 = 0; thisa->m_nXiaoFeiSumRankSize > i_4; ++i_4 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "mail%d", i_4 + 1);
      v14 = std::vector<int>::operator[](&thisa->m_vXiaoFeiSumRankMail, i_4);
      std::allocator<char>::allocator(&v265);
      std::string::string(&v264, szCol);
      std::allocator<char>::allocator(&v267);
      std::string::string(&v266, "XIAO_FEI_SUM_RANK");
      *v14 = Answer::Inifile::getIntValue(&ini, &v266, &v264);
      std::string::~string(&v266);
      std::allocator<char>::~allocator(&v267);
      std::string::~string(&v264);
      std::allocator<char>::~allocator(&v265);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "reward%d", i_4 + 1);
      std::allocator<char>::allocator((char *)&v269.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v269.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v269.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v269.m_strMap._M_t._M_impl._M_header._M_right, "XIAO_FEI_SUM_RANK");
      Answer::Inifile::getStrValue(
        &v269,
        (const std::string *const)&ini,
        (const std::string *const)&v269.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v268, (const std::string *const)&v269);
      v15 = std::vector<std::vector<MemChrBag>>::operator[](&thisa->m_vXiaoFeiSumRankReward, i_4);
      std::vector<MemChrBag>::operator=(v15, &v268);
      std::vector<MemChrBag>::~vector(&v268);
      std::string::~string(&v269);
      std::string::~string(&v269.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v269.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v269.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v269.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::allocator<char>::allocator(&v270);
    std::string::string(&v269.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v272);
    std::string::string(&v271, "OBT_FLOP");
    thisa->m_vStartDay[11] = Answer::Inifile::getIntValue(&ini, &v271, &v269.m_currentSection);
    std::string::~string(&v271);
    std::allocator<char>::~allocator(&v272);
    std::string::~string(&v269.m_currentSection);
    std::allocator<char>::~allocator(&v270);
    std::allocator<char>::allocator(&v274);
    std::string::string(&v273, "end_day");
    std::allocator<char>::allocator(&v276);
    std::string::string(&v275, "OBT_FLOP");
    thisa->m_vEndDay[11] = Answer::Inifile::getIntValue(&ini, &v275, &v273);
    std::string::~string(&v275);
    std::allocator<char>::~allocator(&v276);
    std::string::~string(&v273);
    std::allocator<char>::~allocator(&v274);
    std::allocator<char>::allocator(&v278);
    std::string::string(&v277, "size");
    std::allocator<char>::allocator(&v280);
    std::string::string(&v279, "OBT_FLOP");
    thisa->m_FlopSize = Answer::Inifile::getIntValue(&ini, &v279, &v277);
    std::string::~string(&v279);
    std::allocator<char>::~allocator(&v280);
    std::string::~string(&v277);
    std::allocator<char>::~allocator(&v278);
    std::vector<int>::resize(&thisa->m_FlopType, thisa->m_FlopSize, 0);
    v281.m_nId = 0;
    v281.m_nClass = 0;
    v281.m_nCount = 0;
    v16.m_nId = 0;
    v16.m_nClass = 0;
    v16.m_nCount = 0;
    std::vector<ItemData>::resize(&thisa->m_FlopCost, thisa->m_FlopSize, v16);
    for ( i_5 = 0; thisa->m_FlopSize > i_5; ++i_5 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "type%d", i_5 + 1);
      v17 = std::vector<int>::operator[](&thisa->m_FlopType, i_5);
      std::allocator<char>::allocator(&v283);
      std::string::string(&v282, szCol);
      std::allocator<char>::allocator(&v285);
      std::string::string(&v284, "OBT_FLOP");
      *v17 = Answer::Inifile::getIntValue(&ini, &v284, &v282);
      std::string::~string(&v284);
      std::allocator<char>::~allocator(&v285);
      std::string::~string(&v282);
      std::allocator<char>::~allocator(&v283);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "cost%d", i_5 + 1);
      v18 = std::vector<ItemData>::operator[](&thisa->m_FlopCost, i_5);
      std::allocator<char>::allocator((char *)&v286.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v286.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v286.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v286.m_strMap._M_t._M_impl._M_header._M_right, "OBT_FLOP");
      Answer::Inifile::getStrValue(
        &v286,
        (const std::string *const)&ini,
        (const std::string *const)&v286.m_strMap._M_t._M_impl._M_header._M_right);
      v369 = CItemHelper::parseItemDataString((const std::string *const)&v286);
      LODWORD(v38) = v369.m_nId;
      BYTE4(v38) = v369.m_nClass;
      v44 = v38;
      m_nCount = v369.m_nCount;
      *(_QWORD *)&v18->m_nId = v38;
      v18->m_nCount = m_nCount;
      std::string::~string(&v286);
      std::string::~string(&v286.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v286.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v286.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v286.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::allocator<char>::allocator(&v287);
    std::string::string(&v286.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v289);
    std::string::string(&v288, "OBT_LI_QUAN");
    thisa->m_vStartDay[10] = Answer::Inifile::getIntValue(&ini, &v288, &v286.m_currentSection);
    std::string::~string(&v288);
    std::allocator<char>::~allocator(&v289);
    std::string::~string(&v286.m_currentSection);
    std::allocator<char>::~allocator(&v287);
    std::allocator<char>::allocator(&v291);
    std::string::string(&v290, "end_day");
    std::allocator<char>::allocator(&v293);
    std::string::string(&v292, "OBT_LI_QUAN");
    thisa->m_vEndDay[10] = Answer::Inifile::getIntValue(&ini, &v292, &v290);
    std::string::~string(&v292);
    std::allocator<char>::~allocator(&v293);
    std::string::~string(&v290);
    std::allocator<char>::~allocator(&v291);
    std::allocator<char>::allocator(&v295);
    std::string::string(&v294, "size");
    std::allocator<char>::allocator(&v297);
    std::string::string(&v296, "OBT_LI_QUAN");
    thisa->m_LiQuanSize = Answer::Inifile::getIntValue(&ini, &v296, &v294);
    std::string::~string(&v296);
    std::allocator<char>::~allocator(&v297);
    std::string::~string(&v294);
    std::allocator<char>::~allocator(&v295);
    v298.itemId = 0;
    v298.itemClass = 0;
    v298.itemCount = 0;
    v298.bind = 0;
    v298.endTime = 0;
    v298.srcId = 0;
    *(_OWORD *)&v40.itemId = *(_OWORD *)&v298.itemId;
    *(_OWORD *)&v40.endTime = *(unsigned __int64 *)&v298.endTime;
    std::vector<MemChrBag>::resize(&thisa->m_LiQuanItem, thisa->m_LiQuanSize, v40);
    v299.m_nId = 0;
    v299.m_nClass = 0;
    v299.m_nCount = 0;
    v19.m_nId = 0;
    v19.m_nClass = 0;
    v19.m_nCount = 0;
    std::vector<ItemData>::resize(&thisa->m_ItemDataVector, thisa->m_LiQuanSize, v19);
    std::vector<int>::resize(&thisa->m_LiQuanPriceVt, thisa->m_LiQuanSize, 0);
    std::vector<int>::resize(&thisa->m_LiQuanLimitCount, thisa->m_LiQuanSize, 0);
    for ( i_6 = 0; thisa->m_LiQuanSize > i_6; ++i_6 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "item%d", i_6 + 1);
      v20 = std::vector<MemChrBag>::operator[](&thisa->m_LiQuanItem, i_6);
      std::allocator<char>::allocator((char *)&v300.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v300.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v300.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v300.m_strMap._M_t._M_impl._M_header._M_right, "OBT_LI_QUAN");
      Answer::Inifile::getStrValue(
        &v300,
        (const std::string *const)&ini,
        (const std::string *const)&v300.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemString(&v43, (const std::string *const)&v300);
      *v20 = v43;
      std::string::~string(&v300);
      std::string::~string(&v300.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v300.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v300.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v300.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_6 + 1);
      v21 = std::vector<int>::operator[](&thisa->m_LiQuanPriceVt, i_6);
      std::allocator<char>::allocator(&v301);
      std::string::string(&v300.m_currentSection, szCol);
      std::allocator<char>::allocator(&v303);
      std::string::string(&v302, "OBT_LI_QUAN");
      *v21 = Answer::Inifile::getIntValue(&ini, &v302, &v300.m_currentSection);
      std::string::~string(&v302);
      std::allocator<char>::~allocator(&v303);
      std::string::~string(&v300.m_currentSection);
      std::allocator<char>::~allocator(&v301);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "limit%d", i_6 + 1);
      v22 = std::vector<int>::operator[](&thisa->m_LiQuanLimitCount, i_6);
      std::allocator<char>::allocator(&v305);
      std::string::string(&v304, szCol);
      std::allocator<char>::allocator(&v307);
      std::string::string(&v306, "OBT_LI_QUAN");
      *v22 = Answer::Inifile::getIntValue(&ini, &v306, &v304);
      std::string::~string(&v306);
      std::allocator<char>::~allocator(&v307);
      std::string::~string(&v304);
      std::allocator<char>::~allocator(&v305);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "costitem%d", i_6 + 1);
      v23 = std::vector<ItemData>::operator[](&thisa->m_ItemDataVector, i_6);
      std::allocator<char>::allocator((char *)&v308.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v308.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v308.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v308.m_strMap._M_t._M_impl._M_header._M_right, "OBT_LI_QUAN");
      Answer::Inifile::getStrValue(
        &v308,
        (const std::string *const)&ini,
        (const std::string *const)&v308.m_strMap._M_t._M_impl._M_header._M_right);
      v370 = CItemHelper::parseItemDataString((const std::string *const)&v308);
      LODWORD(v39) = v370.m_nId;
      BYTE4(v39) = v370.m_nClass;
      *(_QWORD *)&v43.itemId = v39;
      v43.itemCount = v370.m_nCount;
      *(_QWORD *)&v23->m_nId = v39;
      v23->m_nCount = v43.itemCount;
      std::string::~string(&v308);
      std::string::~string(&v308.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v308.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v308.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v308.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::allocator<char>::allocator(&v309);
    std::string::string(&v308.m_currentSection, "start_day");
    std::allocator<char>::allocator(&v311);
    std::string::string(&v310, "OBT_QIAN_DAO");
    IntValue = Answer::Inifile::getIntValue(&ini, &v310, &v308.m_currentSection);
    thisa->m_vStartDay[12] = IntValue;
    std::string::~string(&v310);
    std::allocator<char>::~allocator(&v311);
    std::string::~string(&v308.m_currentSection);
    std::allocator<char>::~allocator(&v309);
    std::allocator<char>::allocator(&v313);
    std::string::string(&v312, "end_day");
    std::allocator<char>::allocator(&v315);
    std::string::string(&v314, "OBT_QIAN_DAO");
    v25 = Answer::Inifile::getIntValue(&ini, &v314, &v312);
    thisa->m_vEndDay[12] = v25;
    std::string::~string(&v314);
    std::allocator<char>::~allocator(&v315);
    std::string::~string(&v312);
    std::allocator<char>::~allocator(&v313);
    std::allocator<char>::allocator(&v317);
    std::string::string(&v316, "size");
    std::allocator<char>::allocator(&v319);
    std::string::string(&v318, "OBT_QIAN_DAO");
    v26 = Answer::Inifile::getIntValue(&ini, &v318, &v316);
    thisa->m_QianDaoSize = v26;
    std::string::~string(&v318);
    std::allocator<char>::~allocator(&v319);
    std::string::~string(&v316);
    std::allocator<char>::~allocator(&v317);
    v320.itemId = 0;
    v320.itemClass = 0;
    v320.itemCount = 0;
    v320.bind = 0;
    v320.endTime = 0;
    v320.srcId = 0;
    *(_OWORD *)&v41.itemId = *(_OWORD *)&v320.itemId;
    *(_OWORD *)&v41.endTime = *(unsigned __int64 *)&v320.endTime;
    std::vector<MemChrBag>::resize(&thisa->m_QianDaoReward, thisa->m_QianDaoSize, v41);
    std::vector<int>::resize(&thisa->m_BuQianPrice, thisa->m_QianDaoSize, 0);
    for ( i_7 = 0; thisa->m_QianDaoSize > i_7; ++i_7 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "item%d", i_7 + 1);
      v27 = std::vector<MemChrBag>::operator[](&thisa->m_QianDaoReward, i_7);
      std::allocator<char>::allocator((char *)&v321.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v321.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v321.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v321.m_strMap._M_t._M_impl._M_header._M_right, "OBT_QIAN_DAO");
      Answer::Inifile::getStrValue(
        &v321,
        (const std::string *const)&ini,
        (const std::string *const)&v321.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemString(&v43, (const std::string *const)&v321);
      *v27 = v43;
      std::string::~string(&v321);
      std::string::~string(&v321.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v321.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v321.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v321.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "price%d", i_7 + 1);
      v28 = std::vector<int>::operator[](&thisa->m_BuQianPrice, i_7);
      std::allocator<char>::allocator(&v322);
      std::string::string(&v321.m_currentSection, szCol);
      std::allocator<char>::allocator(&v324);
      std::string::string(&v323, "OBT_QIAN_DAO");
      *v28 = Answer::Inifile::getIntValue(&ini, &v323, &v321.m_currentSection);
      std::string::~string(&v323);
      std::allocator<char>::~allocator(&v324);
      std::string::~string(&v321.m_currentSection);
      std::allocator<char>::~allocator(&v322);
    }
    std::allocator<char>::allocator(&v326);
    std::string::string(&v325, "start_day");
    std::allocator<char>::allocator(&v328);
    std::string::string(&v327, "OBT_YAN_HUA");
    v29 = Answer::Inifile::getIntValue(&ini, &v327, &v325);
    thisa->m_vStartDay[13] = v29;
    std::string::~string(&v327);
    std::allocator<char>::~allocator(&v328);
    std::string::~string(&v325);
    std::allocator<char>::~allocator(&v326);
    std::allocator<char>::allocator(&v330);
    std::string::string(&v329, "end_day");
    std::allocator<char>::allocator(&v332);
    std::string::string(&v331, "OBT_YAN_HUA");
    v30 = Answer::Inifile::getIntValue(&ini, &v331, &v329);
    thisa->m_vEndDay[13] = v30;
    std::string::~string(&v331);
    std::allocator<char>::~allocator(&v332);
    std::string::~string(&v329);
    std::allocator<char>::~allocator(&v330);
    std::allocator<char>::allocator(&v334);
    std::string::string(&v333, "size");
    std::allocator<char>::allocator(&v336);
    std::string::string(&v335, "OBT_YAN_HUA");
    v31 = Answer::Inifile::getIntValue(&ini, &v335, &v333);
    thisa->m_YanHuaSize = v31;
    std::string::~string(&v335);
    std::allocator<char>::~allocator(&v336);
    std::string::~string(&v333);
    std::allocator<char>::~allocator(&v334);
    v337.itemId = 0;
    v337.itemClass = 0;
    v337.itemCount = 0;
    v337.bind = 0;
    v337.endTime = 0;
    v337.srcId = 0;
    *(_OWORD *)&v42.itemId = *(_OWORD *)&v337.itemId;
    *(_OWORD *)&v42.endTime = *(unsigned __int64 *)&v337.endTime;
    std::vector<MemChrBag>::resize(&thisa->m_YanHuaReward, thisa->m_YanHuaSize, v42);
    std::vector<int>::resize(&thisa->m_YanHuaPointVt, thisa->m_YanHuaSize, 0);
    for ( i_8 = 0; thisa->m_YanHuaSize > i_8; ++i_8 )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "item%d", i_8 + 1);
      v32 = std::vector<MemChrBag>::operator[](&thisa->m_YanHuaReward, i_8);
      std::allocator<char>::allocator((char *)&v338.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v338.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v338.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v338.m_strMap._M_t._M_impl._M_header._M_right, "OBT_YAN_HUA");
      Answer::Inifile::getStrValue(
        &v338,
        (const std::string *const)&ini,
        (const std::string *const)&v338.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemString(&v43, (const std::string *const)&v338);
      *v32 = v43;
      std::string::~string(&v338);
      std::string::~string(&v338.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v338.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v338.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v338.m_strMap._M_t._M_impl._M_header._M_left + 7);
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "point%d", i_8 + 1);
      v33 = std::vector<int>::operator[](&thisa->m_YanHuaPointVt, i_8);
      std::allocator<char>::allocator(&v339);
      std::string::string(&v338.m_currentSection, szCol);
      std::allocator<char>::allocator(&v341);
      std::string::string(&v340, "OBT_YAN_HUA");
      *v33 = Answer::Inifile::getIntValue(&ini, &v340, &v338.m_currentSection);
      std::string::~string(&v340);
      std::allocator<char>::~allocator(&v341);
      std::string::~string(&v338.m_currentSection);
      std::allocator<char>::~allocator(&v339);
    }
    std::allocator<char>::allocator(&v343);
    std::string::string(&v342, "start_day");
    std::allocator<char>::allocator(&v345);
    std::string::string(&v344, "OBT_GUO_QING_TASK");
    v34 = Answer::Inifile::getIntValue(&ini, &v344, &v342);
    thisa->m_vStartDay[16] = v34;
    std::string::~string(&v344);
    std::allocator<char>::~allocator(&v345);
    std::string::~string(&v342);
    std::allocator<char>::~allocator(&v343);
    std::allocator<char>::allocator(&v347);
    std::string::string(&v346, "end_day");
    std::allocator<char>::allocator(&v349);
    std::string::string(&v348, "OBT_GUO_QING_TASK");
    v35 = Answer::Inifile::getIntValue(&ini, &v348, &v346);
    thisa->m_vEndDay[16] = v35;
    std::string::~string(&v348);
    std::allocator<char>::~allocator(&v349);
    std::string::~string(&v346);
    std::allocator<char>::~allocator(&v347);
    std::allocator<char>::allocator(&v351);
    std::string::string(&v350, "start_day");
    std::allocator<char>::allocator(&v353);
    std::string::string(&v352, "OBT_GUO_QING_REWARD");
    v36 = Answer::Inifile::getIntValue(&ini, &v352, &v350);
    thisa->m_vStartDay[17] = v36;
    std::string::~string(&v352);
    std::allocator<char>::~allocator(&v353);
    std::string::~string(&v350);
    std::allocator<char>::~allocator(&v351);
    std::allocator<char>::allocator(&v355);
    std::string::string(&v354, "end_day");
    std::allocator<char>::allocator(&v357);
    std::string::string(&v356, "OBT_GUO_QING_REWARD");
    v37 = Answer::Inifile::getIntValue(&ini, &v356, &v354);
    thisa->m_vEndDay[17] = v37;
    std::string::~string(&v356);
    std::allocator<char>::~allocator(&v357);
    std::string::~string(&v354);
    std::allocator<char>::~allocator(&v355);
    COpenBeta::loadXiaoFeiSumRank(thisa);
    COpenBeta::LoadYanHuaValue(thisa);
    Answer::Inifile::~Inifile(&ini);
  }
}


#####################################
int32_t __cdecl COpenBeta::GetFlopType(COpenBeta *const this, int32_t nFlopId)
{
  GameService *v2; // rax

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    return 0;
  if ( nFlopId >= 0 && this->m_FlopSize > nFlopId )
    return *std::vector<int>::operator[](&this->m_FlopType, nFlopId);
  return 0;
}


#####################################
bool __cdecl COpenBeta::CanFlopDraw(COpenBeta *const this, Player *pPlayer, int32_t FlopId)
{
  GameService *v3; // rax
  ItemData *v5; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v9; // rax
  int32_t FlopTimes; // [rsp+20h] [rbp-20h]
  int BuyTimes; // [rsp+28h] [rbp-18h]
  int32_t NeedCost; // [rsp+2Ch] [rbp-14h]

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 0;
  if ( !COpenBeta::IsInTime(this, 11) )
    return 0;
  if ( !pPlayer || FlopId < 0 || this->m_FlopSize <= FlopId )
    return 0;
  if ( std::vector<ItemData>::operator[](&this->m_FlopCost, FlopId)->m_nId > 0 )
  {
    v5 = std::vector<ItemData>::operator[](&this->m_FlopCost, FlopId);
    Bag = Player::GetBag(pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, v5, ITEM_CHANGE_REASON::IDCR_FLOP) )
      return 0;
  }
  if ( *std::vector<int>::operator[](&this->m_FlopType, FlopId) == 2 )
    return 1;
  FlopTimes = Player::getRecord(pPlayer, 2114);
  if ( FlopTimes >= COpenBeta::GetMaxFlopTimes(this, pPlayer) )
  {
    BuyTimes = Player::getRecord(pPlayer, 2113);
    if ( this->m_nDay == this->m_vEndDay[11] - 1 || BuyTimes <= 1 )
    {
      NeedCost = 500 * (BuyTimes + 1);
      if ( NeedCost > 0 )
      {
        if ( !Player::DecCurrency(pPlayer, CURRENCY_TYPE::CURRENCY_GOLD, NeedCost, CURRENCY_CHANGE_REASON::GCR_FLOP, 0) )
        {
          return 0;
        }
        else
        {
          OperateLimit = Player::GetOperateLimit(pPlayer);
          CExtOperateLimit::AddLimitCount(OperateLimit, 2113, 1);
          v9 = Player::GetOperateLimit(pPlayer);
          CExtOperateLimit::AddLimitCount(v9, 2114, 1);
          return 1;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v7 = Player::GetOperateLimit(pPlayer);
    CExtOperateLimit::AddLimitCount(v7, 2114, 1);
    return 1;
  }
}


#####################################
int32_t __cdecl COpenBeta::GetMaxFlopTimes(COpenBeta *const this, Player *pPlayer)
{
  GameService *v3; // rax
  int32_t Times; // [rsp+18h] [rbp-8h]

  if ( !pPlayer )
    return 0;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 0;
  Times = 1;
  if ( Player::GetTodayPayGold(pPlayer) > 0 )
    Times = 2;
  return Player::getRecord(pPlayer, 2113) + Times;
}


#####################################
void __cdecl COpenBeta::OnDaySwitch(COpenBeta *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    this->m_nDay = Answer::DayTime::daydiff(this->m_nStartDay);
    if ( this->m_nDay == this->m_nEndDay )
    {
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( !packet )
        return;
      Answer::NetPacket::writeInt32(packet, this->m_nIcon);
      Answer::NetPacket::writeInt8(packet, 4);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
    if ( this->m_nDay == this->m_vEndDay[5] )
      COpenBeta::sendXiaoFeiSumRankMail(this);
    if ( COpenBeta::IsOpenBetaTime(this) )
    {
      v5 = Answer::Singleton<GameService>::instance();
      GameService::SendOpenBetaIcon(v5);
    }
  }
}


#####################################
void __cdecl COpenBeta::OnNewMinute(COpenBeta *const this, int32_t nMinute)
{
  GameService *v2; // rax

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
  {
    this->m_nMinute = nMinute;
    COpenBeta::CheckBoss(this);
    COpenBeta::checkXiaoFeiSumRank(this);
  }
}


#####################################
void __cdecl COpenBeta::updateStartTime(COpenBeta *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  GameService::getLine(v1);
}


#####################################
void __cdecl COpenBeta::GetIconState(COpenBeta *const this, Player *player, IconStateList *const IconList)
{
  GameService *v3; // rax
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    v3 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v3) != 9 && this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay )
    {
      COpenBeta::getIconState(&__x, this, player);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl COpenBeta::SendIconState(COpenBeta *const this, Player *player)
{
  GameService *v2; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) != 9 && COpenBeta::IsOpenBetaTime(this) )
    {
      COpenBeta::getIconState(&stu, this, player);
      Player::SendIconState(player, &stu);
    }
  }
}


#####################################
void __cdecl COpenBeta::SendActivityInfo(COpenBeta *const this, Player *player)
{
  GameService *v2; // rax
  int8_t ConnId; // bl
  GameService *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+20h] [rbp-20h]
  int nRecord; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  if ( player )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) != 9 )
    {
      Player::getConnId(player);
      ConnId = Player::getConnId(player);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EBDu);
      if ( packet )
      {
        OperateLimit = Player::GetOperateLimit(player);
        nRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1917);
        Answer::NetPacket::writeInt8(packet, this->m_nTitleShopSize);
        for ( i = 0; this->m_nTitleShopSize > i; ++i )
          Answer::NetPacket::writeInt8(packet, (nRecord >> i) & 1);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(player);
        v8 = Player::getConnId(player);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, v8, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl COpenBeta::GetBossIconState(COpenBeta *const this, IconStateList *const IconList)
{
  GameService *v2; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 && COpenBeta::IsInBossTime(this) )
  {
    COpenBeta::getBossIconState(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl COpenBeta::SendBossIconState(COpenBeta *const this)
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
      COpenBeta::getBossIconState(&stu, this);
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
bool __cdecl COpenBeta::IsInBossTime(COpenBeta *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  return GameService::getLine(v1) != 9 && COpenBeta::IsInTime(this, 9);
}


#####################################
void __cdecl COpenBeta::BossDie(COpenBeta *const this, int32_t MonsterId, std::string *p_name, CharId_t Cid)
{
  GameService *v4; // rax

  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) != 9 && this->m_MonsterId > 0 && this->m_MonsterId == MonsterId )
  {
    this->m_bDie = 1;
    COpenBeta::BroadcastBossKilled(this, p_name, Cid);
    COpenBeta::SendBossIconState(this);
  }
}


#####################################
void __cdecl COpenBeta::BroadcastBossKilled(COpenBeta *const this, const std::string *const name, CharId_t cid)
{
  GameService *v3; // rax
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) != 9 )
  {
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nBossKillBroadcast);
      Answer::NetPacket::writeUTF8(packet, name);
      Answer::NetPacket::writeInt64(packet, cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v6, 0, packet);
    }
  }
}


#####################################
void __cdecl COpenBeta::CheckBoss(COpenBeta *const this)
{
  GameService *v1; // rax
  GameService *v3; // rax
  int32_t m_nMinute; // ebx
  int32_t m_Mid; // ebx
  CfgData *v6; // rax
  CfgData *v7; // rax
  CPoolManager *v8; // rax
  int32_t v9; // ebx
  int32_t nEndTime; // r12d
  TimeArea *v11; // rax
  int32_t m_MapId; // ebx
  MapManager *v13; // rax
  int32_t v14; // ebx
  size_t v16; // rbx
  CfgMapMonster MapMonster; // [rsp+10h] [rbp-70h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+30h] [rbp-50h] BYREF
  uint32_t i; // [rsp+4Ch] [rbp-34h]
  CfgMonster *pMonster; // [rsp+50h] [rbp-30h]
  int32_t MonsterId; // [rsp+5Ch] [rbp-24h]
  Monster *monster; // [rsp+60h] [rbp-20h]
  Map *pMap; // [rsp+68h] [rbp-18h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9
    && COpenBeta::IsInTime(this, 9)
    && !std::vector<TimeArea>::empty(&this->m_vBossMinute) )
  {
    v3 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v3) == 1 )
    {
      for ( i = 0; ; ++i )
      {
        v16 = i;
        if ( v16 >= std::vector<TimeArea>::size(&this->m_vBossMinute) )
          break;
        m_nMinute = this->m_nMinute;
        if ( m_nMinute == std::vector<TimeArea>::operator[](&this->m_vBossMinute, i)->nStartTime )
        {
          m_Mid = this->m_Mid;
          v6 = Answer::Singleton<CfgData>::instance();
          pMonster = CfgData::getMonster(v6, m_Mid);
          if ( !pMonster || pMonster->boss_sign != 11 )
            return;
          v7 = Answer::Singleton<CfgData>::instance();
          MonsterId = CfgData::GetMapMonsterId(v7);
          memset(&MapMonster.mapid, 0, 24);
          MapMonster.id = MonsterId;
          MapMonster.mapid = this->m_MapId;
          MapMonster.x = this->m_X;
          MapMonster.y = this->m_Y;
          this->m_MonsterId = MonsterId;
          v8 = Answer::Singleton<CPoolManager>::instance();
          monster = CPoolManager::pop<Monster>(v8);
          if ( monster && pMonster )
          {
            std::vector<AttrAddon>::vector(&vAttrAddon);
            Monster::init(monster, pMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
            std::vector<AttrAddon>::~vector(&vAttrAddon);
            v9 = Answer::DayTime::now();
            nEndTime = std::vector<TimeArea>::operator[](&this->m_vBossMinute, i)->nEndTime;
            v11 = std::vector<TimeArea>::operator[](&this->m_vBossMinute, i);
            Monster::SetLifeTime(monster, v9 + 60 * (nEndTime - v11->nStartTime));
            m_MapId = this->m_MapId;
            v13 = Answer::Singleton<MapManager>::instance();
            pMap = MapManager::GetMap(v13, m_MapId);
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
          COpenBeta::broadcastBossStart(this);
          COpenBeta::SendBossIconState(this);
        }
        else
        {
          v14 = this->m_nMinute;
          if ( v14 == std::vector<TimeArea>::operator[](&this->m_vBossMinute, i)->nEndTime && !this->m_bDie )
          {
            this->m_bDie = 1;
            COpenBeta::broadcastBossEnd(this);
            COpenBeta::SendBossIconState(this);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl COpenBeta::broadcastBossStart(COpenBeta *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nBossStartBroadcast);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
void __cdecl COpenBeta::broadcastBossEnd(COpenBeta *const this)
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nBossEndBroadcast);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


#####################################
int32_t __cdecl COpenBeta::GetRechargeGift(COpenBeta *const this, Player *player, int32_t nIndex)
{
  GameService *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t TodayPayGold; // ebx
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int32_t nRewardRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 2) )
    return 10002;
  if ( nIndex < 0 || this->m_nRechargeDaysSize <= nIndex )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRewardRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2091);
  TodayPayGold = Player::GetTodayPayGold(player);
  if ( TodayPayGold < *std::vector<int>::operator[](&this->m_vRechargeValue, nIndex) )
    return 10002;
  nNewRecord = nRewardRecord | (1 << nIndex);
  if ( nRewardRecord == nNewRecord )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vRechargeGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 2091, nNewRecord);
  COpenBeta::SendIconState(this, player);
  COpenBeta::SendResult(this, player, 2, nIndex, 0);
  return 0;
}


#####################################
int32_t __cdecl COpenBeta::BuyGiftShopItem(COpenBeta *const this, Player *player, int8_t nIndex)
{
  GameService *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  CharId_t Cid; // r12
  int32_t v9; // ebx
  std::string name; // [rsp+20h] [rbp-30h] BYREF
  int32_t nOldRecord; // [rsp+30h] [rbp-20h]
  int32_t nNewRecord; // [rsp+34h] [rbp-1Ch]
  const ShopGoods *goods; // [rsp+38h] [rbp-18h]

  if ( !player )
    return 10002;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 3) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nDailyLimitShopSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2092);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  goods = std::vector<ShopGoods>::operator[](&this->m_vDailyLimitShopGoods, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_OPEN_BETA,
          0) )
    return 10002;
  v7 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v7, 2092, nNewRecord);
  if ( *std::vector<int>::operator[](&this->m_vDailyLimitShopBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&name);
    Cid = Player::getCid(player);
    v9 = *std::vector<int>::operator[](&this->m_vDailyLimitShopBroadcast, nIndex);
    COpenBeta::sendBroadcast(this, v9, Cid, &name);
    std::string::~string(&name);
  }
  COpenBeta::SendResult(this, player, 3, nIndex, 0);
  return 0;
}


#####################################
int32_t __cdecl COpenBeta::BuyTitleShopItem(COpenBeta *const this, Player *player, int8_t nIndex)
{
  GameService *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  CharId_t Cid; // r12
  int32_t v9; // ebx
  std::string name; // [rsp+20h] [rbp-30h] BYREF
  int32_t nOldRecord; // [rsp+30h] [rbp-20h]
  int32_t nNewRecord; // [rsp+34h] [rbp-1Ch]
  const ShopGoods *goods; // [rsp+38h] [rbp-18h]

  if ( !player )
    return 10002;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 6) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nTitleShopSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1917);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  goods = std::vector<ShopGoods>::operator[](&this->m_vTitleShopGoods, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_OPEN_BETA,
          0) )
    return 10002;
  v7 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v7, 1917, nNewRecord);
  if ( *std::vector<int>::operator[](&this->m_vTitleShopBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&name);
    Cid = Player::getCid(player);
    v9 = *std::vector<int>::operator[](&this->m_vTitleShopBroadcast, nIndex);
    COpenBeta::sendBroadcast(this, v9, Cid, &name);
    std::string::~string(&name);
  }
  COpenBeta::SendResult(this, player, 6, nIndex, 0);
  return 0;
}


#####################################
int32_t __cdecl COpenBeta::BuyShiZhuangShopItem(COpenBeta *const this, Player *player, int8_t nIndex)
{
  GameService *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  CharId_t Cid; // r12
  int32_t v9; // ebx
  std::string name; // [rsp+20h] [rbp-30h] BYREF
  int32_t nOldRecord; // [rsp+30h] [rbp-20h]
  int32_t nNewRecord; // [rsp+34h] [rbp-1Ch]
  const ShopGoods *goods; // [rsp+38h] [rbp-18h]

  if ( !player )
    return 10002;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 7) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_nShiZhuangShopSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1918);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  goods = std::vector<ShopGoods>::operator[](&this->m_vShizhuangShopGoods, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_OPEN_BETA,
          0) )
    return 10002;
  v7 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v7, 1918, nNewRecord);
  if ( *std::vector<int>::operator[](&this->m_vShiZhuangShopBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&name);
    Cid = Player::getCid(player);
    v9 = *std::vector<int>::operator[](&this->m_vShiZhuangShopBroadcast, nIndex);
    COpenBeta::sendBroadcast(this, v9, Cid, &name);
    std::string::~string(&name);
  }
  COpenBeta::SendResult(this, player, 7, nIndex, 0);
  return 0;
}


#####################################
int32_t __cdecl COpenBeta::BuyLiQuan(COpenBeta *const this, Player *player, int8_t nIndex)
{
  GameService *v3; // rax
  int32_t v5; // ebx
  int64_t Currency; // rbx
  CExtCharBag *Bag; // rax
  ItemData *v8; // rbx
  CExtCharBag *v9; // rax
  int64_t v10; // rdx
  CExtOperateLimit *OperateLimit; // rax
  MemChrBag *v12; // rbx
  CExtCharBag *v13; // rax

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  if ( !player )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 10) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_LiQuanSize )
    return 10002;
  v5 = *std::vector<int>::operator[](&this->m_LiQuanLimitCount, nIndex);
  if ( v5 <= Player::getRecord(player, nIndex + 10000) )
    return 10002;
  if ( *std::vector<int>::operator[](&this->m_LiQuanPriceVt, nIndex) > 0 )
  {
    Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
    if ( Currency < *std::vector<int>::operator[](&this->m_LiQuanPriceVt, nIndex) )
      return 10002;
  }
  Bag = Player::GetBag(player);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 10002;
  v8 = std::vector<ItemData>::operator[](&this->m_ItemDataVector, nIndex);
  v9 = Player::GetBag(player);
  if ( !CExtCharBag::RemoveItem(v9, v8, ITEM_CHANGE_REASON::IDCR_OPEN_BETA_LI_QUAN) )
    return 10002;
  if ( *std::vector<int>::operator[](&this->m_LiQuanPriceVt, nIndex) > 0 )
  {
    v10 = *std::vector<int>::operator[](&this->m_LiQuanPriceVt, nIndex);
    if ( !Player::DecCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD, v10, CURRENCY_CHANGE_REASON::GCR_OPEN_BETA, 0) )
      return 10002;
  }
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, nIndex + 10000, 1);
  v12 = std::vector<MemChrBag>::operator[](&this->m_LiQuanItem, nIndex);
  v13 = Player::GetBag(player);
  CExtCharBag::AddItem(v13, v12, ITEM_CHANGE_REASON::IDCR_OPEN_BETA_LI_QUAN);
  return 0;
}


#####################################
void __cdecl COpenBeta::AddOnlineRecord(COpenBeta *const this, Player *player)
{
  GameService *v2; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  CExtOperateLimit *v6; // rax
  int32_t nOnlineTime; // [rsp+20h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+24h] [rbp-Ch]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9
    && COpenBeta::IsInTime(this, 1)
    && player
    && this->m_nMinute >= this->m_nOnlineStartMinute
    && this->m_nMinute < this->m_nOnlineEndMinute )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2093);
    v5 = Player::GetOperateLimit(player);
    nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 2094);
    if ( this->m_nMaxCount > nRewardTimes )
    {
      v6 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v6, 2093, 1);
      if ( nOnlineTime / this->m_nOnlineTimeArea - nRewardTimes != (nOnlineTime + 1) / this->m_nOnlineTimeArea
                                                                 - nRewardTimes )
        COpenBeta::SendIconState(this, player);
    }
  }
}


#####################################
bool __cdecl COpenBeta::canGetOnlineGift(COpenBeta *const this, Player *player)
{
  GameService *v2; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t nOnlineTime; // [rsp+28h] [rbp-8h]
  int32_t nRewardTimes; // [rsp+2Ch] [rbp-4h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    return 0;
  if ( !player )
    return 0;
  if ( !COpenBeta::IsInTime(this, 1) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2093);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 2094);
  return this->m_nMaxCount > nRewardTimes && nOnlineTime / this->m_nOnlineTimeArea > nRewardTimes;
}


#####################################
int32_t __cdecl COpenBeta::GetOnlineTimeRewardTime(COpenBeta *const this, Player *player)
{
  GameService *v2; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t nOnlineTime; // [rsp+28h] [rbp-8h]
  int nRewardTimes; // [rsp+2Ch] [rbp-4h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    return 0;
  if ( !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2093);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 2094);
  if ( nOnlineTime / this->m_nOnlineTimeArea > nRewardTimes )
    return 0;
  else
    return (nRewardTimes + 1) * this->m_nOnlineTimeArea - nOnlineTime;
}


#####################################
int32_t __cdecl COpenBeta::GetOnlineGift(COpenBeta *const this, Player *player)
{
  GameService *v3; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t OnlineTimeRewardTime; // edx

  if ( !player )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  if ( !COpenBeta::canGetOnlineGift(this, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &this->m_vOnlineReward, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 2094, 1);
  COpenBeta::SendIconState(this, player);
  OnlineTimeRewardTime = COpenBeta::GetOnlineTimeRewardTime(this, player);
  COpenBeta::SendResult(this, player, 1, OnlineTimeRewardTime, 0);
  return 0;
}


#####################################
bool __cdecl COpenBeta::IsInTime(COpenBeta *const this, int8_t Type)
{
  GameService *v2; // rax

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    return 0;
  if ( Type <= 0 || Type > 17 )
    return 0;
  return this->m_nDay >= this->m_vStartDay[Type] && this->m_nDay < this->m_vEndDay[Type];
}


#####################################
int32_t __cdecl COpenBeta::getLeftTime(COpenBeta *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
    return 0;
  else
    return 86400 * (this->m_nEndDay - this->m_nDay) - 60 * this->m_nMinute;
}


#####################################
bool __cdecl COpenBeta::IsOpenBetaTime(COpenBeta *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
    return 0;
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
int32_t __cdecl COpenBeta::GetEndCollectDropTime(COpenBeta *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
    return 0;
  if ( !COpenBeta::IsInTime(this, 8) )
    return 0;
  return 86400 * this->m_vEndDay[8] + Answer::DayTime::dayzero(this->m_nStartDay) - 1;
}


#####################################
int32_t __cdecl COpenBeta::GetChouJiangType(COpenBeta *const this)
{
  GameService *v1; // rax

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
    return 0;
  if ( COpenBeta::IsInTime(this, 4) )
    return this->m_ChouJiangType;
  return 0;
}


#####################################
void __cdecl COpenBeta::LoadYanHuaValue(COpenBeta *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  const char *StringValue; // rax
  char mySql[1024]; // [rsp+10h] [rbp-460h] BYREF
  Answer::MySqlDBGuard db; // [rsp+410h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+440h] [rbp-30h] BYREF

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(mySql, 0, sizeof(mySql));
    snprintf(mySql, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='YAN_HUA'");
    v3 = Answer::MySqlDBGuard::query(&db, mySql);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      StringValue = Answer::MySqlQuery::getStringValue(&result, 0, &byte_8E800F);
      this->m_CurrYanHuaPoint = atoi(StringValue);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl COpenBeta::UpdateYanHuaValue(COpenBeta *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  char mySql_0[1024]; // [rsp+10h] [rbp-860h] BYREF
  char mySql[1024]; // [rsp+410h] [rbp-460h] BYREF
  Answer::MySqlDBGuard db; // [rsp+810h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+840h] [rbp-30h] BYREF

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(mySql, 0, sizeof(mySql));
    snprintf(mySql, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='YAN_HUA'");
    v3 = Answer::MySqlDBGuard::query(&db, mySql);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    memset(mySql_0, 0, sizeof(mySql_0));
    if ( Answer::MySqlQuery::eof(&result) )
      snprintf(
        mySql_0,
        0x3FFu,
        "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('YAN_HUA','%d')",
        this->m_CurrYanHuaPoint);
    else
      snprintf(
        mySql_0,
        0x3FFu,
        "UPDATE `sys_server_config` SET `value`= %d WHERE `name`='YAN_HUA'",
        this->m_CurrYanHuaPoint);
    Answer::MySqlDBGuard::excute(&db, mySql_0);
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl COpenBeta::AddYanHuaPoint(COpenBeta *const this, int32_t Values)
{
  GameService *v2; // rax
  int32_t m_CurrYanHuaPoint; // ebx
  GameService *v5; // rax
  bool NeedSendIcon; // [rsp+17h] [rbp-19h]
  int OldPoint; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 && COpenBeta::IsInTime(this, 13) )
  {
    NeedSendIcon = 0;
    OldPoint = this->m_CurrYanHuaPoint;
    this->m_CurrYanHuaPoint = Values + OldPoint;
    COpenBeta::UpdateYanHuaValue(this);
    for ( i = 0; this->m_YanHuaSize > i; ++i )
    {
      if ( *std::vector<int>::operator[](&this->m_YanHuaPointVt, i) > OldPoint )
      {
        m_CurrYanHuaPoint = this->m_CurrYanHuaPoint;
        if ( m_CurrYanHuaPoint >= *std::vector<int>::operator[](&this->m_YanHuaPointVt, i) )
        {
          NeedSendIcon = 1;
          break;
        }
      }
    }
    if ( NeedSendIcon )
    {
      v5 = Answer::Singleton<GameService>::instance();
      GameService::SendOpenBetaIcon(v5);
    }
  }
}


#####################################
int32_t __cdecl COpenBeta::GetYanHuaPointReward(COpenBeta *const this, Player *player, int8_t nIndex)
{
  GameService *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t m_CurrYanHuaPoint; // ebx
  MemChrBag *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 13) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_YanHuaSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1930);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  m_CurrYanHuaPoint = this->m_CurrYanHuaPoint;
  if ( m_CurrYanHuaPoint < *std::vector<int>::operator[](&this->m_YanHuaPointVt, nIndex) )
    return 10002;
  v7 = std::vector<MemChrBag>::operator[](&this->m_YanHuaReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1930, nNewRecord);
  COpenBeta::SendResult(this, player, 13, nIndex, 0);
  COpenBeta::SendIconState(this, player);
  return 0;
}


#####################################
int32_t __cdecl COpenBeta::GetQianDaoReward(COpenBeta *const this, Player *player, int8_t nIndex, int8_t nType)
{
  GameService *v5; // rax
  CExtOperateLimit *OperateLimit; // rax
  int64_t Currency; // rbx
  MemChrBag *v8; // rbx
  CExtCharBag *Bag; // rax
  int64_t v10; // rdx
  CExtOperateLimit *v11; // rax
  int32_t nOldRecord; // [rsp+24h] [rbp-1Ch]
  int nNewRecord; // [rsp+28h] [rbp-18h]
  int nQianDaoStartDay; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  v5 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v5) == 9 )
    return 10002;
  if ( !COpenBeta::IsInTime(this, 12) )
    return 10002;
  if ( nIndex < 0 || nIndex >= this->m_QianDaoSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1931);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  nQianDaoStartDay = this->m_nDay - this->m_vStartDay[12];
  if ( nQianDaoStartDay < 0 )
    return 10002;
  if ( this->m_QianDaoSize <= nQianDaoStartDay )
    return 10002;
  if ( nIndex > nQianDaoStartDay )
    return 10002;
  if ( nIndex == nQianDaoStartDay )
    goto LABEL_23;
  if ( nType != 1 )
    return 10002;
  Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
  if ( Currency < *std::vector<int>::operator[](&this->m_BuQianPrice, nIndex) )
    return 10002;
LABEL_23:
  v8 = std::vector<MemChrBag>::operator[](&this->m_QianDaoReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v8, ITEM_CHANGE_REASON::ICR_OPEN_BETA) )
    return 10002;
  if ( nIndex != nQianDaoStartDay )
  {
    v10 = *std::vector<int>::operator[](&this->m_BuQianPrice, nIndex);
    if ( !Player::DecCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD, v10, CURRENCY_CHANGE_REASON::GCR_OPEN_BETA, 0) )
      return 10002;
  }
  v11 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v11, 1931, nNewRecord);
  COpenBeta::SendResult(this, player, 12, nIndex, 0);
  COpenBeta::SendIconState(this, player);
  return 0;
}


#####################################
void __cdecl COpenBeta::loadXiaoFeiSumRank(COpenBeta *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  FestivalRank *v4; // rbx
  const char *StringValue; // rbx
  FestivalRank *v6; // rax
  FestivalRank *v7; // rbx
  FestivalRank *v8; // rbx
  std::vector<FestivalRank> *v10; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    v3 = Answer::MySqlDBGuard::query(
           &db,
           "SELECT * FROM `mem_open_beta_rank` WHERE `type`=5 ORDER BY `count` DESC,`time`");
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    nIndex = 0;
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, this->m_nShowSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    while ( !Answer::MySqlQuery::eof(&result) && this->m_nShowSize > nIndex )
    {
      v4 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
      v4->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8E800F);
      v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
      std::string::operator=(&v6->strName, StringValue);
      v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
      v7->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
      v8 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
      v8->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
      ++nIndex;
      Answer::MySqlQuery::nextRow(&result);
    }
    __k = 0;
    v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &__k);
    std::vector<FestivalRank>::operator=(v10, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl COpenBeta::updateXiaoFeiSumRank(COpenBeta *const this, Player *player, int32_t AddValues)
{
  GameService *v3; // rax
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
    v3 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v3) != 9 && COpenBeta::IsInTime(this, 5) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1919, AddValues);
      v5 = Player::GetOperateLimit(player);
      nScore = CExtOperateLimit::GetLimitCount(v5, 1919);
      if ( this->m_nXiaoFeiSumRankLimit <= nScore )
      {
        connid = Player::getConnId(player);
        nCharId = Player::getCid(player);
        Player::getName((const Player *const)&strName);
        COpenBeta::checkXiaoFeiSumRankInvalid(this, connid);
        nRankIndex = -1;
        for ( i = 0; i < this->m_nShowSize; ++i )
        {
          Answer::MutexGuard::MutexGuard(&lock_0, &this->m_lock);
          v6 = i;
          v7 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
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
          nOldIndex = this->m_nShowSize - 1;
          for ( i_0 = 0; i_0 < this->m_nShowSize; ++i_0 )
          {
            Answer::MutexGuard::MutexGuard(&lock_1, &this->m_lock);
            v10 = i_0;
            v11 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
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
          if ( nOldIndex < nRankIndex )
            nRankIndex = nOldIndex;
          if ( nOldIndex != nRankIndex )
          {
            for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
            {
              Answer::MutexGuard::MutexGuard(&lock_2, &this->m_lock);
              v14 = i_1 - 1;
              v15 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
              v16 = std::vector<FestivalRank>::operator[](v15, v14);
              v17 = i_1;
              v18 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
              v19 = std::vector<FestivalRank>::operator[](v18, v17);
              FestivalRank::operator=(v19, v16);
              v20 = i_1;
              v21 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
              std::vector<FestivalRank>::operator[](v21, v20)->bChange = 1;
              Answer::MutexGuard::~MutexGuard(&lock_2);
            }
          }
          Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
          v22 = nRankIndex;
          v23 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v24 = std::vector<FestivalRank>::operator[](v23, v22);
          v24->nCharId = nCharId;
          v25 = nRankIndex;
          v26 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v27 = std::vector<FestivalRank>::operator[](v26, v25);
          std::string::operator=(&v27->strName, &strName);
          v28 = nRankIndex;
          v29 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v30 = std::vector<FestivalRank>::operator[](v29, v28);
          v30->nScore = nScore;
          v31 = nRankIndex;
          v32 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          v33 = std::vector<FestivalRank>::operator[](v32, v31);
          v33->nTime = Unit::getNow(player);
          v34 = nRankIndex;
          v35 = std::map<signed char,std::vector<FestivalRank>>::operator[](&this->m_mXiaoFeiSumRank, &connid);
          std::vector<FestivalRank>::operator[](v35, v34)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock);
        }
        std::string::~string(&strName);
      }
    }
  }
}


#####################################
void __cdecl COpenBeta::checkXiaoFeiSumRankInvalid(COpenBeta *const this, int8_t connid)
{
  GameService *v2; // rax
  std::vector<FestivalRank> *v3; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  COpenBeta *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&thisa->m_mXiaoFeiSumRank, connida)._M_node;
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mXiaoFeiSumRank)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
    {
      std::vector<FestivalRank>::vector(&vRank);
      FestivalRank::FestivalRank(&p___x);
      std::vector<FestivalRank>::resize(&vRank, thisa->m_nShowSize, &p___x);
      FestivalRank::~FestivalRank(&p___x);
      v3 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
      std::vector<FestivalRank>::operator=(v3, &vRank);
      std::vector<FestivalRank>::~vector(&vRank);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl COpenBeta::checkXiaoFeiSumRank(COpenBeta *const this)
{
  GameService *v1; // rax
  int32_t nTime; // r15d
  int32_t nScore; // r14d
  int32_t v4; // r13d
  int32_t v5; // r12d
  FestivalRank *v6; // rax
  const char *v7; // rbx
  FestivalRank *v8; // rax
  Answer::DBPool *v9; // rax
  char szSQL[4096]; // [rsp+40h] [rbp-10A0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1040h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+1070h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+1080h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+1090h] [rbp-50h] BYREF
  int8_t connid; // [rsp+109Fh] [rbp-41h]
  FestivalRankVector *vRank; // [rsp+10A0h] [rbp-40h]
  int16_t i; // [rsp+10AEh] [rbp-32h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 && COpenBeta::IsInTime(this, 5) )
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
      for ( i = 0; i < this->m_nShowSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
        {
          std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
          memset(szSQL, 0, sizeof(szSQL));
          nTime = std::vector<FestivalRank>::operator[](vRank, i)->nTime;
          nScore = std::vector<FestivalRank>::operator[](vRank, i)->nScore;
          v4 = std::vector<FestivalRank>::operator[](vRank, i)->nTime;
          v5 = std::vector<FestivalRank>::operator[](vRank, i)->nScore;
          v6 = std::vector<FestivalRank>::operator[](vRank, i);
          v7 = (const char *)std::string::c_str(&v6->strName);
          v8 = std::vector<FestivalRank>::operator[](vRank, i);
          snprintf(
            szSQL,
            0xFFFu,
            "INSERT INTO `mem_open_beta_rank` (`type`, `day`, `cid`, `name`, `count`,`time`) VALUES (%d,%d,%lld,'%s',%d,%"
            "d)  ON DUPLICATE KEY UPDATE `count`=%d,`time`=%d",
            5,
            0,
            v8->nCharId,
            v7,
            v5,
            v4,
            nScore,
            nTime);
          v9 = Answer::Singleton<Answer::DBPool>::instance();
          Answer::MySqlDBGuard::MySqlDBGuard(&db, v9);
          Answer::MySqlDBGuard::excute(&db, szSQL);
          Answer::MySqlDBGuard::~MySqlDBGuard(&db);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl COpenBeta::sendXiaoFeiSumRankMail(COpenBeta *const this)
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
          std::string::string(&Param, &byte_8E800F);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vXiaoFeiSumRankReward, i);
          v3 = *std::vector<int>::operator[](&this->m_vXiaoFeiSumRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v6, v5, nCharId, v3, v2, ITEM_CHANGE_REASON::ICR_OPEN_BETA, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl COpenBeta::sendBroadcast(
        COpenBeta *const this,
        int32_t nBroadId,
        CharId_t cid,
        const std::string *const name)
{
  GameService *v4; // rax
  GameService *v5; // rax
  uint32_t WOffset; // edx
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) != 9 )
  {
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nBroadId);
      Answer::NetPacket::writeUTF8(packet, name);
      Answer::NetPacket::writeInt64(packet, cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Answer::NetPacket::setProc(packet, 0x2CD6u);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v7, 0, packet);
    }
  }
}


#####################################
void __cdecl COpenBeta::SendResult(COpenBeta *const this, Player *pPlayer, int8_t Type, int32_t Index, int32_t param)
{
  GameService *v5; // rax
  int8_t ConnId; // bl
  GameService *v7; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( pPlayer )
  {
    v5 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v5) != 9 )
    {
      ConnId = Player::getConnId(pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EBEu);
      if ( packet )
      {
        Answer::NetPacket::writeInt8(packet, Type);
        Answer::NetPacket::writeInt32(packet, Index);
        Answer::NetPacket::writeInt32(packet, param);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pPlayer);
        v10 = Player::getConnId(pPlayer);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v11, v10, GateIndex, packet);
      }
    }
  }
}


