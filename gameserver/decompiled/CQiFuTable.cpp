// Decompiled methods for class: CQiFuTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CQiFuTable::InitQiFuTable(CQiFuTable *const this)
{
  std::map<signed char,QiFuCfg> *v1; // rax
  std::map<signed char,QiFuCfg> *v2; // rax
  QiFuCfg *v3; // rax
  std::map<signed char,QiFuCfg> *v4; // rax
  std::map<signed char,QiFuCfg> *v5; // rax
  CDBCFile QiFuTable; // [rsp+10h] [rbp-110h] BYREF
  QiFuTimesMap TimesMap; // [rsp+A0h] [rbp-80h] BYREF
  QiFuCfg stu; // [rsp+D0h] [rbp-50h] BYREF
  int32_t nLevel; // [rsp+ECh] [rbp-34h] BYREF
  char __k; // [rsp+F2h] [rbp-2Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-2Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-28h]
  int8_t nType; // [rsp+FFh] [rbp-21h]
  int32_t i; // [rsp+100h] [rbp-20h]
  int8_t Type; // [rsp+107h] [rbp-19h]
  int32_t Level; // [rsp+108h] [rbp-18h]
  int32_t Times; // [rsp+10Ch] [rbp-14h]

  CDBCFile::CDBCFile(&QiFuTable, 0);
  if ( !CDBCFile::OpenFromTXT(&QiFuTable, "./ServerConfig/Tables/QiFu.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_QI_FU_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum(&QiFuTable);
    iBaseColumnCount = CDBCFile::GetFieldsNum(&QiFuTable);
    if ( iBaseColumnCount > 0 )
    {
      std::map<signed char,QiFuCfg>::map(&TimesMap);
      nLevel = 0;
      nType = 0;
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        Type = CDBCFile::Search_Posistion(&QiFuTable, i, 1)->iValue;
        Level = CDBCFile::Search_Posistion(&QiFuTable, i, 2)->iValue;
        Times = CDBCFile::Search_Posistion(&QiFuTable, i, 3)->iValue;
        if ( nType != 1 || Type == 1 )
        {
          if ( nType == 2 && Type != 2 )
          {
            v2 = std::map<int,std::map<signed char,QiFuCfg>>::operator[](&this->m_QiFuExpCfg, &nLevel);
            std::map<signed char,QiFuCfg>::operator=(v2, &TimesMap);
            std::map<signed char,QiFuCfg>::clear(&TimesMap);
          }
        }
        else
        {
          v1 = std::map<int,std::map<signed char,QiFuCfg>>::operator[](&this->m_QiFuMoneyCfg, &nLevel);
          std::map<signed char,QiFuCfg>::operator=(v1, &TimesMap);
          std::map<signed char,QiFuCfg>::clear(&TimesMap);
        }
        nLevel = Level;
        nType = Type;
        stu.GetMoney = CDBCFile::Search_Posistion(&QiFuTable, i, 4)->iValue;
        stu.GetExp = CDBCFile::Search_Posistion(&QiFuTable, i, 5)->iValue;
        stu.CostGold = CDBCFile::Search_Posistion(&QiFuTable, i, 6)->iValue;
        stu.CostItemClass = CDBCFile::Search_Posistion(&QiFuTable, i, 7)->iValue;
        stu.CostItemId = CDBCFile::Search_Posistion(&QiFuTable, i, 8)->iValue;
        stu.CostItemCount = CDBCFile::Search_Posistion(&QiFuTable, i, 9)->iValue;
        stu.Rate = CDBCFile::Search_Posistion(&QiFuTable, i, 10)->iValue;
        __k = Times;
        v3 = std::map<signed char,QiFuCfg>::operator[](&TimesMap, &__k);
        *v3 = stu;
      }
      if ( nType == 1 )
      {
        v4 = std::map<int,std::map<signed char,QiFuCfg>>::operator[](&this->m_QiFuMoneyCfg, &nLevel);
        std::map<signed char,QiFuCfg>::operator=(v4, &TimesMap);
        std::map<signed char,QiFuCfg>::clear(&TimesMap);
      }
      else if ( nType == 2 )
      {
        v5 = std::map<int,std::map<signed char,QiFuCfg>>::operator[](&this->m_QiFuExpCfg, &nLevel);
        std::map<signed char,QiFuCfg>::operator=(v5, &TimesMap);
        std::map<signed char,QiFuCfg>::clear(&TimesMap);
      }
      std::map<signed char,QiFuCfg>::~map(&TimesMap);
    }
  }
  CDBCFile::~CDBCFile(&QiFuTable);
}


