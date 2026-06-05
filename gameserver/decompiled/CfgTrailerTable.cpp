// Decompiled methods for class: CfgTrailerTable
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CfgTrailerTable::Add(CfgTrailerTable *const this, const CfgTrailer *const stu)
{
  CfgTrailer *v2; // rax

  v2 = std::map<int,CfgTrailer>::operator[](&this->m_mTrailer, &stu->nId);
  CfgTrailer::operator=(v2, stu);
}


#####################################
void __cdecl CfgTrailerTable::AddCfgTrailerInfo(CfgTrailerTable *const this, CfgTrailerInfo stu)
{
  CfgTrailerInfo *v2; // rax

  v2 = std::map<int,CfgTrailerInfo>::operator[](&this->m_CfgTrailerInfoMap, &stu.nIndex);
  *v2 = stu;
}


#####################################
int8_t __cdecl CfgTrailerTable::RandQuality(const CfgTrailerTable *const this, int8_t Quality)
{
  Answer::Random *v2; // rax
  const std::pair<const int,CfgTrailerInfo> *v3; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTrailerInfo> > iter; // [rsp+10h] [rbp-20h] BYREF
  int __x; // [rsp+1Ch] [rbp-14h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTrailerInfo> > v7; // [rsp+20h] [rbp-10h] BYREF
  int32_t nRand; // [rsp+2Ch] [rbp-4h]

  v2 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v2, 1, 1000);
  __x = Quality;
  iter._M_node = std::map<int,CfgTrailerInfo>::find(&this->m_CfgTrailerInfoMap, &__x)._M_node;
  v7._M_node = std::map<int,CfgTrailerInfo>::end(&this->m_CfgTrailerInfoMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgTrailerInfo>>::operator!=(&iter, &v7)
    && (v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgTrailerInfo>>::operator->(&iter),
        v3->second.nRand > nRand) )
  {
    return Quality + 1;
  }
  else
  {
    return Quality;
  }
}


