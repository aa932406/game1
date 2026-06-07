// Decompiled methods for class: CfgDrawTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgDrawTable::Add(CfgDrawTable *const this, const CfgDrawReward *const reward)
{
  CfgDraw *v2; // rax
  CfgDraw *v3; // rax
  CfgDraw draw; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<CfgDraw> eiter; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<CfgDraw> iter; // [rsp+40h] [rbp-20h] BYREF

  iter._M_node = std::list<CfgDraw>::begin(&this->m_Draws)._M_node;
  eiter._M_node = std::list<CfgDraw>::end(&this->m_Draws)._M_node;
  while ( std::_List_iterator<CfgDraw>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<CfgDraw>::operator->(&iter);
    if ( CfgDraw::GetType(v2) == reward->nType )
    {
      v3 = std::_List_iterator<CfgDraw>::operator->(&iter);
      CfgDraw::Add(v3, reward);
      return;
    }
    std::_List_iterator<CfgDraw>::operator++(&iter);
  }
  CfgDraw::CfgDraw(&draw, reward->nType);
  CfgDraw::Add(&draw, reward);
  std::list<CfgDraw>::push_back(&this->m_Draws, &draw);
  CfgDraw::~CfgDraw(&draw);
}


