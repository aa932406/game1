// Decompiled methods for class: SuiJiLiBao
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl SuiJiLiBao::~SuiJiLiBao(SuiJiLiBao *const this)
{
  SuiJiLiBao::~SuiJiLiBao(this);
  operator delete(this);
}


#####################################
int32_t __cdecl SuiJiLiBao::effect(
        SuiJiLiBao *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v4; // ebx
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax
  Answer::Random *v8; // rax
  int8_t job; // bl
  int32_t v11; // ebx
  int32_t v12; // ebx
  Answer::Random *v14; // rax
  int32_t v15; // ebx
  CfgItemGiftRandom *v16; // rax
  CfgItemGiftRandom *v17; // rax
  CExtCharBag *Bag; // rax
  MemChrBag item; // [rsp+20h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGiftRandom*,std::vector<CfgItemGiftRandom> > it; // [rsp+40h] [rbp-60h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGiftRandom*,std::vector<CfgItemGiftRandom> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  int32_t bagslot; // [rsp+84h] [rbp-1Ch]
  int32_t roll; // [rsp+88h] [rbp-18h]
  bool find; // [rsp+8Fh] [rbp-11h]

  if ( std::vector<CfgItemGiftRandom>::empty(&this->m_gifts) )
    return 10002;
  bagslot = Player::getFirstFreeSlot(launcher);
  if ( bagslot >= 0 )
  {
    std::vector<MemChrBag>::vector(&items);
    v8 = Answer::Singleton<Answer::Random>::instance();
    roll = Answer::Random::generate(v8, 1, 1000);
    find = 0;
    for ( it._M_current = std::vector<CfgItemGiftRandom>::begin(&this->m_gifts)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgItemGiftRandom>::end(&this->m_gifts)._M_current;
      if ( !__gnu_cxx::operator!=<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>(&it, &__rhs) )
        break;
      if ( __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->job )
      {
        job = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->job;
        if ( job != Player::getJob(launcher) )
          continue;
      }
      v11 = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher);
      if ( v11 >= __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->MinLevel )
      {
        v12 = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher);
        if ( v12 <= __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->MaxLevel )
        {
          if ( __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->static_probability <= 0 )
          {
            v16 = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it);
            if ( v16->sum_probability < roll )
            {
              v17 = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it);
              roll -= v17->sum_probability;
            }
            else if ( !find )
            {
              memset(&item, 0, sizeof(item));
              item.itemId = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->item;
              item.itemClass = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->type;
              item.itemCount = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->count;
              item.bind = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->bind;
              std::vector<MemChrBag>::push_back(&items, &item);
              find = 1;
            }
          }
          else
          {
            v14 = Answer::Singleton<Answer::Random>::instance();
            v15 = Answer::Random::generate(v14, 1, 1000);
            if ( v15 <= __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->static_probability )
            {
              memset(&item, 0, sizeof(item));
              item.itemId = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->item;
              item.itemClass = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->type;
              item.itemCount = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->count;
              item.bind = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->bind;
              std::vector<MemChrBag>::push_back(&items, &item);
            }
          }
        }
      }
    }
    if ( std::vector<MemChrBag>::size(&items) )
    {
      Bag = Player::GetBag(launcher);
      if ( CExtCharBag::AddItemsAndMingGe(Bag, &items, ITEM_CHANGE_REASON::ICR_SUIJILIBAO) )
        v4 = 0;
      else
        v4 = 10016;
    }
    else
    {
      v4 = 10002;
    }
    std::vector<MemChrBag>::~vector(&items);
  }
  else
  {
    GateIndex = Player::getGateIndex(launcher);
    ConnId = Player::getConnId(launcher);
    v7 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v7, ConnId, GateIndex, 0x59u, 10054, 0);
  }
  return v4;
}


#####################################
void __cdecl SuiJiLiBao::broadcast(SuiJiLiBao *const this, Player *const launcher, int8_t nClass, int32_t nId)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v8; // bl
  GameService *v9; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  ConnId = Player::getConnId(launcher);
  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 236);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(launcher);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt8(packet, nClass);
    Answer::NetPacket::writeInt32(packet, nId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Player::getConnId(launcher);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v9, v8, packet);
  }
}


#####################################
bool __cdecl SuiJiLiBao::parseEffect(SuiJiLiBao *const this, int32_t id, const std::string *const strEffect)
{
  CfgData *v3; // rax
  const std::vector<CfgItemGiftRandom> *pCfg; // [rsp+28h] [rbp-8h]

  this->m_nId = id;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::getItemGiftRandom(v3, id);
  if ( !pCfg )
    return 0;
  std::vector<CfgItemGiftRandom>::operator=(&this->m_gifts, pCfg);
  return 1;
}


