// Decompiled: tpoc
// Source: gameserver.cc

#####################################
void __cdecl tpoc::ObjectPoolBase::push<PlantActivity>(tpoc::ObjectPoolBase *const this, PlantActivity *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, PlantActivity *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Trap>(tpoc::ObjectPoolBase *const this, Trap *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Trap *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<CObjCarrier>(tpoc::ObjectPoolBase *const this, CObjCarrier *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, CObjCarrier *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<CLittleHelper>(tpoc::ObjectPoolBase *const this, CLittleHelper *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, CLittleHelper *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<CObjPet>(tpoc::ObjectPoolBase *const this, CObjPet *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, CObjPet *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<MonsterDungeon>(tpoc::ObjectPoolBase *const this, MonsterDungeon *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, MonsterDungeon *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<PlantDungeon>(tpoc::ObjectPoolBase *const this, PlantDungeon *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, PlantDungeon *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<CDropItem>(tpoc::ObjectPoolBase *const this, CDropItem *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, CDropItem *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Npc>(tpoc::ObjectPoolBase *const this, Npc *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Npc *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Player>(tpoc::ObjectPoolBase *const this, Player *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Player *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<User>(tpoc::ObjectPoolBase *const this, User *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, User *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<NpcActivity>(tpoc::ObjectPoolBase *const this, NpcActivity *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, NpcActivity *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Trailer>(tpoc::ObjectPoolBase *const this, Trailer *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Trailer *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Dungeon>(tpoc::ObjectPoolBase *const this, Dungeon *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Dungeon *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<CTerritory>(tpoc::ObjectPoolBase *const this, CTerritory *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, CTerritory *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<GameMsg>(tpoc::ObjectPoolBase *const this, GameMsg *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, GameMsg *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<MonsterActivity>(tpoc::ObjectPoolBase *const this, MonsterActivity *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, MonsterActivity *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Monster>(tpoc::ObjectPoolBase *const this, Monster *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Monster *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


#####################################
void __cdecl tpoc::ObjectPool<GameMsg>::_push(tpoc::ObjectPool<GameMsg> *const this, void *pObj)
{
  GameMsg *v2; // rax

  if ( pObj )
  {
    GameMsg::reset((GameMsg *const)pObj);
    Answer::SafeQueue<GameMsg *>::push(&this->m_pool, (GameMsg *)pObj);
    if ( Answer::SafeQueue<GameMsg *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<GameMsg *>::pop(&this->m_pool);
      operator delete(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<User>::_push(tpoc::ObjectPool<User> *const this, void *pObj)
{
  User *v2; // rax
  User *v3; // rbx

  if ( pObj )
  {
    User::reset((User *const)pObj);
    Answer::SafeQueue<User *>::push(&this->m_pool, (User *)pObj);
    if ( Answer::SafeQueue<User *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<User *>::pop(&this->m_pool);
      v3 = v2;
      if ( v2 )
      {
        User::~User(v2);
        operator delete(v3);
      }
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<Player>::_push(tpoc::ObjectPool<Player> *const this, void *pObj)
{
  Player *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<Player *>::push(&this->m_pool, (Player *)pObj);
    if ( Answer::SafeQueue<Player *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<Player *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(Player *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<CObjPet>::_push(tpoc::ObjectPool<CObjPet> *const this, void *pObj)
{
  CObjPet *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<CObjPet *>::push(&this->m_pool, (CObjPet *)pObj);
    if ( Answer::SafeQueue<CObjPet *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<CObjPet *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(CObjPet *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<Monster>::_push(tpoc::ObjectPool<Monster> *const this, void *pObj)
{
  Monster *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<Monster *>::push(&this->m_pool, (Monster *)pObj);
    if ( Answer::SafeQueue<Monster *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<Monster *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(Monster *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<Dungeon>::_push(tpoc::ObjectPool<Dungeon> *const this, void *pObj)
{
  Dungeon *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 232LL))(pObj);
    Answer::SafeQueue<Dungeon *>::push(&this->m_pool, (Dungeon *)pObj);
    if ( Answer::SafeQueue<Dungeon *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<Dungeon *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(Dungeon *))v2->_vptr_Map + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<MonsterDungeon>::_push(tpoc::ObjectPool<MonsterDungeon> *const this, void *pObj)
{
  MonsterDungeon *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<MonsterDungeon *>::push(&this->m_pool, (MonsterDungeon *)pObj);
    if ( Answer::SafeQueue<MonsterDungeon *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<MonsterDungeon *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(MonsterDungeon *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<CDropItem>::_push(tpoc::ObjectPool<CDropItem> *const this, void *pObj)
{
  CDropItem *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<CDropItem *>::push(&this->m_pool, (CDropItem *)pObj);
    if ( Answer::SafeQueue<CDropItem *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<CDropItem *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(CDropItem *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<Trap>::_push(tpoc::ObjectPool<Trap> *const this, void *pObj)
{
  Trap *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<Trap *>::push(&this->m_pool, (Trap *)pObj);
    if ( Answer::SafeQueue<Trap *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<Trap *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(Trap *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<PlantDungeon>::_push(tpoc::ObjectPool<PlantDungeon> *const this, void *pObj)
{
  PlantDungeon *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<PlantDungeon *>::push(&this->m_pool, (PlantDungeon *)pObj);
    if ( Answer::SafeQueue<PlantDungeon *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<PlantDungeon *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(PlantDungeon *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<MonsterActivity>::_push(tpoc::ObjectPool<MonsterActivity> *const this, void *pObj)
{
  MonsterActivity *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<MonsterActivity *>::push(&this->m_pool, (MonsterActivity *)pObj);
    if ( Answer::SafeQueue<MonsterActivity *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<MonsterActivity *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(MonsterActivity *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<NpcActivity>::_push(tpoc::ObjectPool<NpcActivity> *const this, void *pObj)
{
  NpcActivity *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<NpcActivity *>::push(&this->m_pool, (NpcActivity *)pObj);
    if ( Answer::SafeQueue<NpcActivity *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<NpcActivity *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(NpcActivity *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<PlantActivity>::_push(tpoc::ObjectPool<PlantActivity> *const this, void *pObj)
{
  PlantActivity *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<PlantActivity *>::push(&this->m_pool, (PlantActivity *)pObj);
    if ( Answer::SafeQueue<PlantActivity *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<PlantActivity *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(PlantActivity *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<Trailer>::_push(tpoc::ObjectPool<Trailer> *const this, void *pObj)
{
  Trailer *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<Trailer *>::push(&this->m_pool, (Trailer *)pObj);
    if ( Answer::SafeQueue<Trailer *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<Trailer *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(Trailer *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<CObjCarrier>::_push(tpoc::ObjectPool<CObjCarrier> *const this, void *pObj)
{
  CObjCarrier *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<CObjCarrier *>::push(&this->m_pool, (CObjCarrier *)pObj);
    if ( Answer::SafeQueue<CObjCarrier *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<CObjCarrier *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(CObjCarrier *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<CTerritory>::_push(tpoc::ObjectPool<CTerritory> *const this, void *pObj)
{
  CTerritory *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 232LL))(pObj);
    Answer::SafeQueue<CTerritory *>::push(&this->m_pool, (CTerritory *)pObj);
    if ( Answer::SafeQueue<CTerritory *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<CTerritory *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(CTerritory *))v2->_vptr_Map + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPool<CLittleHelper>::_push(tpoc::ObjectPool<CLittleHelper> *const this, void *pObj)
{
  CLittleHelper *v2; // rax

  if ( pObj )
  {
    (*(void (__fastcall **)(void *))(*(_QWORD *)pObj + 48LL))(pObj);
    Answer::SafeQueue<CLittleHelper *>::push(&this->m_pool, (CLittleHelper *)pObj);
    if ( Answer::SafeQueue<CLittleHelper *>::size(&this->m_pool) > this->m_maxCount )
    {
      v2 = Answer::SafeQueue<CLittleHelper *>::pop(&this->m_pool);
      if ( v2 )
        (*((void (__fastcall **)(CLittleHelper *))v2->_vptr_Entity + 1))(v2);
    }
  }
}


#####################################
void __cdecl tpoc::ObjectPoolBase::push<Plant>(tpoc::ObjectPoolBase *const this, Plant *pObj)
{
  (*((void (__fastcall **)(tpoc::ObjectPoolBase *const, Plant *))this->_vptr_ObjectPoolBase + 1))(this, pObj);
}


