// Decompiled methods for class: VipTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl VipTable::InitVipTable(VipTable *const this)
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  VipCfg *v9; // rax
  CDBCFile VipTable; // [rsp+10h] [rbp-230h] BYREF
  VipCfg stu; // [rsp+A0h] [rbp-1A0h] BYREF
  AttrAddon attr; // [rsp+120h] [rbp-120h] BYREF
  StringVector vstack; // [rsp+130h] [rbp-110h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+150h] [rbp-F0h] BYREF
  StringVector Attts; // [rsp+160h] [rbp-E0h] BYREF
  std::string AtttString; // [rsp+180h] [rbp-C0h] BYREF
  MemChrBagVector __x; // [rsp+190h] [rbp-B0h] BYREF
  std::string strItems; // [rsp+1B0h] [rbp-90h] BYREF
  char v19; // [rsp+1BFh] [rbp-81h] BYREF
  MemChrBagVector v20; // [rsp+1C0h] [rbp-80h] BYREF
  std::string v21; // [rsp+1E0h] [rbp-60h] BYREF
  char v22; // [rsp+1EEh] [rbp-52h] BYREF
  char v23; // [rsp+1EFh] [rbp-51h] BYREF
  std::string delims; // [rsp+1F0h] [rbp-50h] BYREF
  char v25; // [rsp+1FFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+200h] [rbp-40h] BYREF
  std::string v27; // [rsp+210h] [rbp-30h] BYREF
  char v28; // [rsp+21Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+220h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+224h] [rbp-1Ch]
  int32_t i; // [rsp+228h] [rbp-18h]
  int32_t nIndex; // [rsp+22Ch] [rbp-14h]

  CDBCFile::CDBCFile(&VipTable, 0);
  if ( !CDBCFile::OpenFromTXT(&VipTable, "./ServerConfig/Tables/VipNew.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VIP_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&VipTable);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&VipTable);
    if ( iBaseColumnCount > 0 )
    {
      std::map<signed char,VipCfg>::clear(&this->m_VipCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 116);
        std::vector<MemChrBag>::vector(&stu.Item);
        std::vector<MemChrBag>::vector(&stu.DayReward);
        std::vector<AttrAddon>::vector(&stu.AtttVector);
        nIndex = 0;
        stu.VipLevel = CDBCFile::Search_Posistion(&VipTable, i, 0)->iValue;
        stu.NeedVipExp = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v19);
        v1 = CDBCFile::Search_Posistion(&VipTable, i, nIndex);
        std::string::string(&strItems, v1->pString, &v19);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Item, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        std::string::~string(&strItems);
        std::allocator<char>::~allocator(&v19);
        ++nIndex;
        std::allocator<char>::allocator(&v22);
        v2 = CDBCFile::Search_Posistion(&VipTable, i, nIndex);
        std::string::string(&v21, v2->pString, &v22);
        CItemHelper::parseItemVectorString(&v20, &v21);
        std::vector<MemChrBag>::operator=(&stu.DayReward, &v20);
        std::vector<MemChrBag>::~vector(&v20);
        std::string::~string(&v21);
        std::allocator<char>::~allocator(&v22);
        ++nIndex;
        std::allocator<char>::allocator(&v23);
        v3 = CDBCFile::Search_Posistion(&VipTable, i, nIndex);
        std::string::string(&AtttString, v3->pString, &v23);
        std::allocator<char>::~allocator(&v23);
        ++nIndex;
        stu.Revive = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.Retroactive = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.Luck1 = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.Luck2 = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.TreasureTimes = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.EquipBackRate = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.StorePage = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.CycleTower = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        stu.ClubBuyTimes = CDBCFile::Search_Posistion(&VipTable, i, ++nIndex)->iValue;
        ++nIndex;
        std::allocator<char>::allocator(&v25);
        std::string::string(&delims, "|", &v25);
        Answer::StringUtility::split(&Attts, &AtttString, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v25);
        for ( it._M_current = std::vector<std::string>::begin(&Attts)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&Attts)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          std::allocator<char>::allocator(&v28);
          std::string::string(&v27, ":", &v28);
          v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          Answer::StringUtility::split(&vstack, v4, &v27, 0);
          std::string::~string(&v27);
          std::allocator<char>::~allocator(&v28);
          if ( std::vector<std::string>::size(&vstack) == 2 )
          {
            attr = 0;
            v5 = std::vector<std::string>::operator[](&vstack, 0);
            v6 = (const char *)std::string::c_str(v5);
            attr.index = atoi(v6);
            v7 = std::vector<std::string>::operator[](&vstack, 1u);
            v8 = (const char *)std::string::c_str(v7);
            attr.addon = atoi(v8);
            if ( attr.addon > 0 && attr.index > 0 )
              std::vector<AttrAddon>::push_back(&stu.AtttVector, &attr);
          }
          std::vector<std::string>::~vector(&vstack);
        }
        v9 = std::map<signed char,VipCfg>::operator[](&this->m_VipCfgMap, &stu.VipLevel);
        VipCfg::operator=(v9, &stu);
        std::vector<std::string>::~vector(&Attts);
        std::string::~string(&AtttString);
        VipCfg::~VipCfg(&stu);
      }
    }
  }
  CDBCFile::~CDBCFile(&VipTable);
}


#####################################
int8_t __cdecl VipTable::GetVipLevel(VipTable *const this, int32_t VipExp)
{
  std::pair<const signed char,VipCfg> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,VipCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,VipCfg> > __x; // [rsp+20h] [rbp-10h] BYREF
  int8_t VipLevel; // [rsp+2Bh] [rbp-5h]
  int32_t NeedVipExp; // [rsp+2Ch] [rbp-4h]

  if ( VipExp <= 0 )
    return 0;
  VipLevel = 0;
  NeedVipExp = 0;
  for ( it._M_node = std::map<signed char,VipCfg>::begin(&this->m_VipCfgMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,VipCfg>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,VipCfg>::end(&this->m_VipCfgMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,VipCfg>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,VipCfg>>::operator->(&it);
    NeedVipExp += v3->second.NeedVipExp;
    if ( NeedVipExp > VipExp )
      return std::_Rb_tree_iterator<std::pair<signed char const,VipCfg>>::operator->(&it)->first - 1;
    if ( std::_Rb_tree_iterator<std::pair<signed char const,VipCfg>>::operator->(&it)->first == 14 )
      return 14;
  }
  return VipLevel;
}


