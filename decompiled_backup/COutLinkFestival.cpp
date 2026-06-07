// Decompiled methods for class: COutLinkFestival
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl COutLinkFestival::OnNewMinute(COutLinkFestival *const this, int32_t nMinute)
{
  GameService *v2; // rax
  CTimer *v3; // rax
  CfgData *v4; // rax
  int32_t OutLinkFestivalTable; // eax
  CfgOutLinkFestivalTable v6; // [rsp+10h] [rbp-20h] BYREF

  if ( !(nMinute % 60) )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) == 1 )
    {
      COutLinkFestival::checkIconState(this);
    }
    else
    {
      v3 = Answer::Singleton<CTimer>::instance();
      CTimer::GetNow(v3);
      v4 = Answer::Singleton<CfgData>::instance();
      OutLinkFestivalTable = (unsigned int)CfgData::GetOutLinkFestivalTable(v4);
      CfgOutLinkFestivalTable::GetShowIcons(&v6, OutLinkFestivalTable);
      std::list<CfgOutLinkFestival>::operator=(&this->m_lOutLinkIcons, &v6.m_lFestival);
      std::list<CfgOutLinkFestival>::~list(&v6.m_lFestival);
    }
  }
}


#####################################
void __cdecl COutLinkFestival::Init(COutLinkFestival *const this, int32_t line)
{
  CfgData *v2; // rax
  int32_t OutLinkFestivalTable; // eax
  CfgOutLinkFestivalTable v4; // [rsp+10h] [rbp-20h] BYREF

  Answer::DayTime::now();
  v2 = Answer::Singleton<CfgData>::instance();
  OutLinkFestivalTable = (unsigned int)CfgData::GetOutLinkFestivalTable(v2);
  CfgOutLinkFestivalTable::GetShowIcons(&v4, OutLinkFestivalTable);
  std::list<CfgOutLinkFestival>::operator=(&this->m_lOutLinkIcons, &v4.m_lFestival);
  std::list<CfgOutLinkFestival>::~list(&v4.m_lFestival);
}


#####################################
void __cdecl COutLinkFestival::GetIconState(COutLinkFestival *const this, IconStateList *const IconList)
{
  CTimer *v2; // rax
  CfgData *v3; // rax
  int32_t OutLinkFestivalTable; // eax
  const CfgOutLinkFestival *v5; // rax
  ShowIcon stu; // [rsp+10h] [rbp-90h] BYREF
  std::_List_const_iterator<CfgOutLinkFestival> iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  CfgOutLinkFestivalTable v9; // [rsp+50h] [rbp-50h] BYREF
  std::_List_iterator<CfgOutLinkFestival> __x; // [rsp+60h] [rbp-40h] BYREF
  std::_List_const_iterator<CfgOutLinkFestival> v11; // [rsp+70h] [rbp-30h] BYREF
  std::_List_iterator<CfgOutLinkFestival> v12; // [rsp+80h] [rbp-20h] BYREF
  int32_t nNowTime; // [rsp+8Ch] [rbp-14h]

  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  v3 = Answer::Singleton<CfgData>::instance();
  OutLinkFestivalTable = (unsigned int)CfgData::GetOutLinkFestivalTable(v3);
  CfgOutLinkFestivalTable::GetShowIcons(&v9, OutLinkFestivalTable);
  std::list<CfgOutLinkFestival>::operator=(&this->m_lOutLinkIcons, &v9.m_lFestival);
  std::list<CfgOutLinkFestival>::~list(&v9.m_lFestival);
  if ( !std::list<CfgOutLinkFestival>::empty(&this->m_lOutLinkIcons) )
  {
    __x._M_node = std::list<CfgOutLinkFestival>::begin(&this->m_lOutLinkIcons)._M_node;
    std::_List_const_iterator<CfgOutLinkFestival>::_List_const_iterator(&iter, &__x);
    while ( 1 )
    {
      v12._M_node = std::list<CfgOutLinkFestival>::end(&this->m_lOutLinkIcons)._M_node;
      std::_List_const_iterator<CfgOutLinkFestival>::_List_const_iterator(&v11, &v12);
      if ( !std::_List_const_iterator<CfgOutLinkFestival>::operator!=(&iter, &v11) )
        break;
      memset(&stu, 0, sizeof(stu));
      stu.nId = std::_List_const_iterator<CfgOutLinkFestival>::operator->(&iter)->nIcon;
      stu.nState = 2;
      v5 = std::_List_const_iterator<CfgOutLinkFestival>::operator->(&iter);
      stu.nLeftTime = v5->nEndTime - nNowTime;
      std::list<ShowIcon>::push_back(IconList, &stu);
      std::_List_const_iterator<CfgOutLinkFestival>::operator++(&iter);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl COutLinkFestival::checkIconState(COutLinkFestival *const this)
{
  CTimer *v1; // rax
  CfgData *v2; // rax
  int32_t OutLinkFestivalTable; // eax
  int32_t nIndex; // edx
  CfgOutLinkFestival *v5; // rax
  int32_t v6; // edx
  CfgOutLinkFestival *v7; // rax
  CfgOutLinkFestival *v8; // rax
  GameService *v9; // rax
  uint32_t WOffset; // eax
  GameService *v11; // rax
  GameService *v12; // rax
  uint32_t v13; // eax
  GameService *v14; // rax
  ShowIcon icon_0; // [rsp+10h] [rbp-120h] BYREF
  std::_List_iterator<CfgOutLinkFestival> iter_2; // [rsp+30h] [rbp-100h] BYREF
  ShowIcon icon; // [rsp+40h] [rbp-F0h] BYREF
  std::_List_iterator<CfgOutLinkFestival> iter_1; // [rsp+60h] [rbp-D0h] BYREF
  std::_List_iterator<CfgOutLinkFestival> iter_0; // [rsp+70h] [rbp-C0h] BYREF
  std::_List_iterator<CfgOutLinkFestival> iter; // [rsp+80h] [rbp-B0h] BYREF
  Answer::MutexGuard lock; // [rsp+90h] [rbp-A0h] BYREF
  CfgOutLinkFestivalList lHide; // [rsp+A0h] [rbp-90h] BYREF
  CfgOutLinkFestivalList lAdd; // [rsp+B0h] [rbp-80h] BYREF
  CfgOutLinkFestivalList lShowIcons; // [rsp+C0h] [rbp-70h] BYREF
  std::_List_iterator<CfgOutLinkFestival> __x; // [rsp+D0h] [rbp-60h] BYREF
  std::_List_iterator<CfgOutLinkFestival> v26; // [rsp+E0h] [rbp-50h] BYREF
  std::_List_iterator<CfgOutLinkFestival> v27; // [rsp+F0h] [rbp-40h] BYREF
  std::_List_iterator<CfgOutLinkFestival> v28; // [rsp+100h] [rbp-30h] BYREF
  int32_t nNowTime; // [rsp+10Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+110h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+118h] [rbp-18h]

  v1 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v1);
  v2 = Answer::Singleton<CfgData>::instance();
  OutLinkFestivalTable = (unsigned int)CfgData::GetOutLinkFestivalTable(v2);
  CfgOutLinkFestivalTable::GetShowIcons((const CfgOutLinkFestivalTable *const)&lShowIcons, OutLinkFestivalTable);
  std::list<CfgOutLinkFestival>::list(&lAdd);
  std::list<CfgOutLinkFestival>::list(&lHide);
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  for ( iter._M_node = std::list<CfgOutLinkFestival>::begin(&lShowIcons)._M_node;
        ;
        std::_List_iterator<CfgOutLinkFestival>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgOutLinkFestival>::end(&lShowIcons)._M_node;
    if ( !std::_List_iterator<CfgOutLinkFestival>::operator!=(&iter, &__x) )
      break;
    nIndex = std::_List_iterator<CfgOutLinkFestival>::operator->(&iter)->nIndex;
    if ( !COutLinkFestival::isInIconList(this, &this->m_lOutLinkIcons, nIndex) )
    {
      v5 = std::_List_iterator<CfgOutLinkFestival>::operator*(&iter);
      std::list<CfgOutLinkFestival>::push_back(&lAdd, v5);
    }
  }
  for ( iter_0._M_node = std::list<CfgOutLinkFestival>::begin(&this->m_lOutLinkIcons)._M_node;
        ;
        std::_List_iterator<CfgOutLinkFestival>::operator++(&iter_0) )
  {
    v26._M_node = std::list<CfgOutLinkFestival>::end(&this->m_lOutLinkIcons)._M_node;
    if ( !std::_List_iterator<CfgOutLinkFestival>::operator!=(&iter_0, &v26) )
      break;
    v6 = std::_List_iterator<CfgOutLinkFestival>::operator->(&iter_0)->nIndex;
    if ( !COutLinkFestival::isInIconList(this, &lShowIcons, v6) )
    {
      v7 = std::_List_iterator<CfgOutLinkFestival>::operator*(&iter_0);
      std::list<CfgOutLinkFestival>::push_back(&lHide, v7);
    }
  }
  std::list<CfgOutLinkFestival>::operator=(&this->m_lOutLinkIcons, &lShowIcons);
  Answer::MutexGuard::~MutexGuard(&lock);
  if ( !std::list<CfgOutLinkFestival>::empty(&lAdd) )
  {
    for ( iter_1._M_node = std::list<CfgOutLinkFestival>::begin(&lAdd)._M_node;
          ;
          std::_List_iterator<CfgOutLinkFestival>::operator++(&iter_1) )
    {
      v27._M_node = std::list<CfgOutLinkFestival>::end(&lAdd)._M_node;
      if ( !std::_List_iterator<CfgOutLinkFestival>::operator!=(&iter_1, &v27) )
        break;
      memset(&icon, 0, sizeof(icon));
      icon.nId = std::_List_iterator<CfgOutLinkFestival>::operator->(&iter_1)->nIcon;
      icon.nState = 2;
      v8 = std::_List_iterator<CfgOutLinkFestival>::operator->(&iter_1);
      icon.nLeftTime = v8->nEndTime - nNowTime;
      v9 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v9, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet )
      {
        ShowIcon::AppendInfo(&icon, packet);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v11, packet);
      }
    }
  }
  if ( !std::list<CfgOutLinkFestival>::empty(&lHide) )
  {
    for ( iter_2._M_node = std::list<CfgOutLinkFestival>::begin(&lHide)._M_node;
          ;
          std::_List_iterator<CfgOutLinkFestival>::operator++(&iter_2) )
    {
      v28._M_node = std::list<CfgOutLinkFestival>::end(&lHide)._M_node;
      if ( !std::_List_iterator<CfgOutLinkFestival>::operator!=(&iter_2, &v28) )
        break;
      memset(&icon_0, 0, sizeof(icon_0));
      icon_0.nId = std::_List_iterator<CfgOutLinkFestival>::operator->(&iter_2)->nIcon;
      icon_0.nState = 4;
      v12 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v12, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet_0 )
      {
        ShowIcon::AppendInfo(&icon_0, packet_0);
        v13 = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, v13);
        v14 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v14, packet_0);
      }
    }
  }
  std::list<CfgOutLinkFestival>::~list(&lHide);
  std::list<CfgOutLinkFestival>::~list(&lAdd);
  std::list<CfgOutLinkFestival>::~list(&lShowIcons);
}


#####################################
bool __cdecl COutLinkFestival::isInIconList(
        COutLinkFestival *const this,
        const CfgOutLinkFestivalList *const lst,
        int32_t nIndex)
{
  std::_List_const_iterator<CfgOutLinkFestival> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_const_iterator<CfgOutLinkFestival> __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<CfgOutLinkFestival>::begin(lst)._M_node;
        ;
        std::_List_const_iterator<CfgOutLinkFestival>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgOutLinkFestival>::end(lst)._M_node;
    if ( !std::_List_const_iterator<CfgOutLinkFestival>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_const_iterator<CfgOutLinkFestival>::operator->(&iter)->nIndex == nIndex )
      return 1;
  }
  return 0;
}


