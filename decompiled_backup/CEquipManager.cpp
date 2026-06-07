// Decompiled methods for class: CEquipManager
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CEquipManager::~CEquipManager(CEquipManager *const this)
{
  CEquipManager::~CEquipManager(this);
  operator delete(this);
}


#####################################
void __cdecl CEquipManager::OnEquipUpdated(CEquipManager *const this, const MemEquipVector *const vAmulet)
{
  const MemEquip *v2; // rbx
  const MemEquip *v3; // rax
  MemEquip *v4; // rax
  Answer::RwLockWrGuard lock; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const MemEquip*,std::vector<MemEquip> > iter; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const MemEquip*,std::vector<MemEquip> > __rhs; // [rsp+30h] [rbp-20h] BYREF

  for ( iter._M_current = std::vector<MemEquip>::begin(vAmulet)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemEquip const*,std::vector<MemEquip>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemEquip>::end(vAmulet)._M_current;
    if ( !__gnu_cxx::operator!=<MemEquip const*,std::vector<MemEquip>>(&iter, &__rhs) )
      break;
    Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwEquipLock);
    v2 = __gnu_cxx::__normal_iterator<MemEquip const*,std::vector<MemEquip>>::operator*(&iter);
    v3 = __gnu_cxx::__normal_iterator<MemEquip const*,std::vector<MemEquip>>::operator->(&iter);
    v4 = std::map<long,MemEquip>::operator[](&this->m_mEquip, &v3->id);
    MemEquip::operator=(v4, v2);
    Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
  }
}


#####################################
void __cdecl CEquipManager::UpdateMemEquip(
        CEquipManager *const this,
        int8_t connid,
        const MemEquip *const equip,
        int32_t nReason)
{
  MemEquip *v4; // rax
  DBService *v5; // rax
  Answer::RwLockWrGuard lock; // [rsp+20h] [rbp-20h] BYREF

  Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwEquipLock);
  v4 = std::map<long,MemEquip>::operator[](&this->m_mEquip, &equip->id);
  MemEquip::operator=(v4, equip);
  Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
  v5 = Answer::Singleton<DBService>::instance();
  DBService::updateMemEquip(v5, connid, equip, nReason);
}


#####################################
void __cdecl CEquipManager::DeleteMemEquip(
        CEquipManager *const this,
        int8_t connid,
        EquipId_t nEquipId,
        int32_t nReason)
{
  int v4; // ebx
  std::pair<const long int,MemEquip> *v5; // rax
  int8_t v6; // bl
  DBService *v7; // rax
  EquipId_t nEquipIda; // [rsp+8h] [rbp-98h] BYREF
  int8_t connida; // [rsp+14h] [rbp-8Ch]
  CEquipManager *thisa; // [rsp+18h] [rbp-88h]
  MemEquip equip; // [rsp+20h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,MemEquip> > iter; // [rsp+60h] [rbp-40h] BYREF
  Answer::RwLockWrGuard lock; // [rsp+70h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,MemEquip> > __x; // [rsp+80h] [rbp-20h] BYREF

  thisa = this;
  nEquipIda = nEquipId;
  connida = connid;
  MemEquip::MemEquip(&equip);
  Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwEquipLock);
  iter._M_node = std::map<long,MemEquip>::find(&this->m_mEquip, &nEquipIda)._M_node;
  __x._M_node = std::map<long,MemEquip>::end(&thisa->m_mEquip)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,MemEquip>>::operator==(&iter, &__x) )
  {
    v4 = 0;
  }
  else
  {
    v5 = std::_Rb_tree_iterator<std::pair<long const,MemEquip>>::operator->(&iter);
    MemEquip::operator=(&equip, &v5->second);
    std::map<long,MemEquip>::erase(&thisa->m_mEquip, iter);
    v4 = 1;
  }
  Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
  if ( v4 )
  {
    v6 = connida;
    v7 = Answer::Singleton<DBService>::instance();
    DBService::deleteMemEquip(v7, v6, &equip, nReason);
  }
  MemEquip::~MemEquip(&equip);
}


#####################################
void __cdecl CEquipManager::SendPlayerEquipInfo(CEquipManager *const this, Player *pPlayer)
{
  size_t v2; // rax
  const std::pair<const long int,MemEquip> *v3; // rax
  CharId_t owner; // rbx
  std::_Rb_tree_const_iterator<std::pair<const long int,MemEquip> > iter; // [rsp+10h] [rbp-80h] BYREF
  Answer::RwLockWrGuard lock; // [rsp+20h] [rbp-70h] BYREF
  MemEquipVector vEquip; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,MemEquip> > __it; // [rsp+50h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,MemEquip> > __x; // [rsp+60h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,MemEquip> > v10; // [rsp+70h] [rbp-20h] BYREF
  const MemEquip *equip; // [rsp+78h] [rbp-18h]

  if ( pPlayer )
  {
    std::vector<MemEquip>::vector(&vEquip);
    v2 = std::map<long,MemEquip>::size(&this->m_mEquip);
    std::vector<MemEquip>::reserve(&vEquip, v2);
    Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwEquipLock);
    __it._M_node = std::map<long,MemEquip>::begin(&this->m_mEquip)._M_node;
    std::_Rb_tree_const_iterator<std::pair<long const,MemEquip>>::_Rb_tree_const_iterator(&iter, &__it);
    while ( 1 )
    {
      v10._M_node = std::map<long,MemEquip>::end(&this->m_mEquip)._M_node;
      std::_Rb_tree_const_iterator<std::pair<long const,MemEquip>>::_Rb_tree_const_iterator(&__x, &v10);
      if ( !std::_Rb_tree_const_iterator<std::pair<long const,MemEquip>>::operator!=(&iter, &__x) )
        break;
      v3 = std::_Rb_tree_const_iterator<std::pair<long const,MemEquip>>::operator->(&iter);
      equip = &v3->second;
      owner = v3->second.owner;
      if ( owner == Player::getCid(pPlayer) )
        std::vector<MemEquip>::push_back(&vEquip, equip);
      std::_Rb_tree_const_iterator<std::pair<long const,MemEquip>>::operator++(&iter);
    }
    Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
    if ( !std::vector<MemEquip>::empty(&vEquip) )
      CEquipManager::SendPlayerEquipInfo(this, pPlayer, &vEquip);
    std::vector<MemEquip>::~vector(&vEquip);
  }
}


#####################################
void __cdecl CEquipManager::SendPlayerEquipInfo(
        CEquipManager *const this,
        Player *pPlayer,
        const MemEquip *const equip)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x274Du);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      MemEquip::PackageClientData(equip, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v7 = Player::getConnId(pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CEquipManager::SendPlayerEquipInfo(
        CEquipManager *const this,
        Player *pPlayer,
        const MemEquipVector *const vEquip)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t v5; // eax
  const MemEquip *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  __gnu_cxx::__normal_iterator<const MemEquip*,std::vector<MemEquip> > iter; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const MemEquip*,std::vector<MemEquip> > __rhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x274Du);
    if ( packet )
    {
      v5 = std::vector<MemEquip>::size(vEquip);
      Answer::NetPacket::writeInt32(packet, v5);
      for ( iter._M_current = std::vector<MemEquip>::begin(vEquip)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemEquip const*,std::vector<MemEquip>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<MemEquip>::end(vEquip)._M_current;
        if ( !__gnu_cxx::operator!=<MemEquip const*,std::vector<MemEquip>>(&iter, &__rhs) )
          break;
        v6 = __gnu_cxx::__normal_iterator<MemEquip const*,std::vector<MemEquip>>::operator->(&iter);
        MemEquip::PackageClientData(v6, packet);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v9 = Player::getConnId(pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CEquipManager::BroadcastEquipInfo(CEquipManager *const this, const MemEquip *const equip)
{
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x274Du);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 1);
    MemEquip::PackageClientData(equip, packet);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, packet);
  }
}


#####################################
int64_t __cdecl CEquipManager::getEquipId(CEquipManager *const this, int32_t nServerId)
{
  GameService *v2; // rax
  int64_t nNextId; // rbx
  int64_t *p_nMaxId; // r12
  std::pair<const int,ServerNewId> *v5; // rax
  std::pair<const int,ServerNewId> *v6; // rax
  int64_t v7; // rbx
  ServerNewId *v8; // rax
  ServerNewId *v9; // rax
  int32_t nServerIda; // [rsp+4h] [rbp-5Ch] BYREF
  CEquipManager *thisa; // [rsp+8h] [rbp-58h]
  ServerNewId NewId; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ServerNewId> > iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::RwLockWrGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ServerNewId> > __x; // [rsp+40h] [rbp-20h] BYREF

  thisa = this;
  nServerIda = nServerId;
  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    nServerIda = 0;
  Answer::RwLockWrGuard::RwLockWrGuard(&lock, &thisa->m_IdLock);
  iter._M_node = std::map<int,ServerNewId>::find(&thisa->m_mNewId, &nServerIda)._M_node;
  __x._M_node = std::map<int,ServerNewId>::end(&thisa->m_mNewId)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,ServerNewId>>::operator!=(&iter, &__x) )
  {
    nNextId = std::_Rb_tree_iterator<std::pair<int const,ServerNewId>>::operator->(&iter)->second.nNextId;
    if ( nNextId >= std::_Rb_tree_iterator<std::pair<int const,ServerNewId>>::operator->(&iter)->second.nMaxId )
    {
      p_nMaxId = &std::_Rb_tree_iterator<std::pair<int const,ServerNewId>>::operator->(&iter)->second.nMaxId;
      v5 = std::_Rb_tree_iterator<std::pair<int const,ServerNewId>>::operator->(&iter);
      CEquipManager::getEquipIdFromDB(thisa, nServerIda, &v5->second.nNextId, p_nMaxId);
    }
    v6 = std::_Rb_tree_iterator<std::pair<int const,ServerNewId>>::operator->(&iter);
    v7 = v6->second.nNextId;
    v6->second.nNextId = v7 + 1;
  }
  else
  {
    NewId.nNextId = 0;
    NewId.nMaxId = 0;
    CEquipManager::getEquipIdFromDB(thisa, nServerIda, &NewId.nNextId, &NewId.nMaxId);
    v8 = std::map<int,ServerNewId>::operator[](&thisa->m_mNewId, &nServerIda);
    *v8 = NewId;
    v9 = std::map<int,ServerNewId>::operator[](&thisa->m_mNewId, &nServerIda);
    v7 = v9->nNextId++;
  }
  Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
  return v7;
}


#####################################
void __cdecl CEquipManager::getEquipIdFromDB(
        CEquipManager *const this,
        int32_t nServerId,
        int64_t *const nNextId,
        int64_t *const nMaxId)
{
  Answer::DBPool *v4; // rax
  GameService *v5; // rax
  Answer::MySqlQuery *v6; // rax
  int32_t v7; // eax
  Answer::MySqlQuery *v8; // rax
  int32_t v9; // eax
  char szSql[4096]; // [rsp+20h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1020h] [rbp-80h] BYREF
  Answer::MySqlQuery result_0; // [rsp+1050h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+1070h] [rbp-30h] BYREF
  int32_t nNewEquipId; // [rsp+108Ch] [rbp-14h]

  v4 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v4);
  v5 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v5) == 9 )
  {
    v6 = Answer::MySqlDBGuard::query(&db, "call NewEquipId(@OutEquipId)");
    Answer::MySqlQuery::MySqlQuery(&result, v6);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      *nNextId = Answer::MySqlQuery::getInt64Value(&result, "OutEquipId", 0);
      *nMaxId = *nNextId + 20;
    }
    else
    {
      v7 = Answer::DayTime::now();
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "CEquipManager::GetEquipId() FAIL! time=%d\n", v7);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
  }
  else
  {
    memset(szSql, 0, sizeof(szSql));
    snprintf(szSql, 0xFFFu, "call NewEquipId(%d,@OutEquipId)", nServerId);
    v8 = Answer::MySqlDBGuard::query(&db, szSql);
    Answer::MySqlQuery::MySqlQuery(&result_0, v8);
    if ( !Answer::MySqlQuery::eof(&result_0) )
    {
      nNewEquipId = Answer::MySqlQuery::getIntValue(&result_0, 0, 0);
      *nNextId = nNewEquipId + ((__int64)nServerId << 32);
      *nMaxId = *nNextId + 20;
    }
    else
    {
      v9 = Answer::DayTime::now();
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "CEquipManager::GetEquipId() FAIL! time=%d\n", v9);
    }
    Answer::MySqlQuery::~MySqlQuery(&result_0);
  }
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


