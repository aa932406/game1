// Decompiled: Answer
// Source: gameserver.cc

#####################################
void __cdecl Answer::NetPacket::writeInt8(Answer::NetPacket *const this, int8_t val)
{
  Answer::NetPacket::write<signed char>(this, val);
}


#####################################
void __cdecl Answer::NetPacket::writeInt32(Answer::NetPacket *const this, int32_t val)
{
  Answer::NetPacket::write<int>(this, val);
}


#####################################
void __cdecl Answer::NetPacket::reallocate(Answer::NetPacket *const this)
{
  char *buffer; // [rsp+18h] [rbp-8h]

  buffer = (char *)operator new[](2 * this->m_bufferSize + 7);
  memcpy(buffer, this->m_buffer - 7, this->m_bufferSize + 7);
  this->m_buffer -= 7;
  if ( this->m_buffer )
    operator delete[](this->m_buffer);
  this->m_buffer = buffer + 7;
  this->m_bufferSize *= 2;
}


#####################################
void __cdecl Answer::NetPacket::write<signed char>(Answer::NetPacket *const this, char val)
{
  if ( !this->m_wOverFlow )
  {
    if ( (unsigned __int64)this->m_wOffset + 1 <= this->m_bufferSize )
      goto LABEL_7;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( (unsigned __int64)this->m_wOffset + 1 <= this->m_bufferSize )
    {
LABEL_7:
      this->m_buffer[this->m_wOffset++] = val;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::NetPacket::write<int>(Answer::NetPacket *const this, int val)
{
  if ( !this->m_wOverFlow )
  {
    if ( (unsigned __int64)this->m_wOffset + 4 <= this->m_bufferSize )
      goto LABEL_7;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( (unsigned __int64)this->m_wOffset + 4 <= this->m_bufferSize )
    {
LABEL_7:
      *(_DWORD *)&this->m_buffer[this->m_wOffset] = val;
      this->m_wOffset += 4;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::NetPacket::writeInt16(Answer::NetPacket *const this, int16_t val)
{
  Answer::NetPacket::write<short>(this, val);
}


#####################################
void __cdecl Answer::NetPacket::writeInt64(Answer::NetPacket *const this, int64_t val)
{
  Answer::NetPacket::write<long>(this, val);
}


#####################################
void __cdecl Answer::NetPacket::writeUTF8(Answer::NetPacket *const this, const std::string *const val)
{
  int16_t v2; // dx
  uint32_t v3; // ebx
  const char *v4; // rcx

  v2 = std::string::length((std::string *)val);
  Answer::NetPacket::writeInt16(this, v2);
  v3 = std::string::length((std::string *)val);
  v4 = (const char *)std::string::c_str((std::string *)val);
  Answer::NetPacket::write(this, v4, v3);
}


#####################################
void __cdecl Answer::NetPacket::write(Answer::NetPacket *const this, const char *buf, uint32_t size)
{
  if ( !this->m_wOverFlow && buf )
  {
    if ( size + this->m_wOffset <= this->m_bufferSize )
      goto LABEL_8;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( size + this->m_wOffset <= this->m_bufferSize )
    {
LABEL_8:
      memcpy(&this->m_buffer[this->m_wOffset], buf, size);
      this->m_wOffset += size;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::NetPacket::write<short>(Answer::NetPacket *const this, __int16 val)
{
  if ( !this->m_wOverFlow )
  {
    if ( (unsigned __int64)this->m_wOffset + 2 <= this->m_bufferSize )
      goto LABEL_7;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( (unsigned __int64)this->m_wOffset + 2 <= this->m_bufferSize )
    {
LABEL_7:
      *(_WORD *)&this->m_buffer[this->m_wOffset] = val;
      this->m_wOffset += 2;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::NetPacket::write<long>(Answer::NetPacket *const this, __int64 val)
{
  if ( !this->m_wOverFlow )
  {
    if ( (unsigned __int64)this->m_wOffset + 8 <= this->m_bufferSize )
      goto LABEL_7;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( (unsigned __int64)this->m_wOffset + 8 <= this->m_bufferSize )
    {
LABEL_7:
      *(_QWORD *)&this->m_buffer[this->m_wOffset] = val;
      this->m_wOffset += 8;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::NetPacket::setWOffset(Answer::NetPacket *const this, uint32_t offset)
{
  if ( this->m_bufferSize >= offset )
    this->m_wOffset = offset;
}


#####################################
char __cdecl Answer::NetPacket::read<signed char>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 1 <= this->m_wOffset )
  {
    return this->m_buffer[this->m_rOffset++];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
__int16 __cdecl Answer::NetPacket::read<short>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 2 <= this->m_wOffset )
  {
    this->m_rOffset += 2;
    return *(_WORD *)&this->m_buffer[this->m_rOffset - 2];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
int __cdecl Answer::NetPacket::read<int>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 4 <= this->m_wOffset )
  {
    this->m_rOffset += 4;
    return *(_DWORD *)&this->m_buffer[this->m_rOffset - 4];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
__int64 __cdecl Answer::NetPacket::read<long>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 8 <= this->m_wOffset )
  {
    this->m_rOffset += 8;
    return *(_QWORD *)&this->m_buffer[this->m_rOffset - 8];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
void __cdecl Answer::NetPacket::destroy(Answer::NetPacket *const this)
{
  if ( this->m_pool )
  {
    Answer::NetPacketPool::push(this->m_pool, this);
  }
  else
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "NetPacket %p with m_pool == NULL, delete this\n", this);
    if ( this )
    {
      Answer::NetPacket::~NetPacket(this);
      operator delete(this);
    }
  }
}


#####################################
unsigned __int8 __cdecl Answer::NetPacket::read<unsigned char>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 1 <= this->m_wOffset )
  {
    return this->m_buffer[this->m_rOffset++];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
unsigned __int64 __cdecl Answer::NetPacket::read<unsigned long>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 8 <= this->m_wOffset )
  {
    this->m_rOffset += 8;
    return *(_QWORD *)&this->m_buffer[this->m_rOffset - 8];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
void __cdecl Answer::NetPacket::writeUInt16(Answer::NetPacket *const this, uint16_t val)
{
  Answer::NetPacket::write<unsigned short>(this, val);
}


#####################################
bool __cdecl Answer::NetPacket::rightShift(Answer::NetPacket *const this, uint32_t size)
{
  if ( this->m_bufferSize - this->m_wOffset < size )
    return 0;
  memmove(&this->m_buffer[size], this->m_buffer, this->m_wOffset);
  this->m_wOffset = 0;
  return 1;
}


#####################################
void __cdecl Answer::NetPacket::write<unsigned short>(Answer::NetPacket *const this, unsigned __int16 val)
{
  if ( !this->m_wOverFlow )
  {
    if ( (unsigned __int64)this->m_wOffset + 2 <= this->m_bufferSize )
      goto LABEL_7;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( (unsigned __int64)this->m_wOffset + 2 <= this->m_bufferSize )
    {
LABEL_7:
      *(_WORD *)&this->m_buffer[this->m_wOffset] = val;
      this->m_wOffset += 2;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::SafeQueue<GameMsg *>::push(Answer::SafeQueue<GameMsg*> *const this, GameMsg *val)
{
  GameMsg *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<GameMsg*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<GameMsg *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
unsigned int __cdecl Answer::NetPacket::read<unsigned int>(Answer::NetPacket *const this)
{
  if ( this->m_rOverFlow )
    return 0;
  if ( (unsigned __int64)this->m_rOffset + 4 <= this->m_wOffset )
  {
    this->m_rOffset += 4;
    return *(_DWORD *)&this->m_buffer[this->m_rOffset - 4];
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "netpacket type = %d, proc = %d read overflow\n",
      this->type,
      this->m_proc);
    this->m_rOverFlow = 1;
    return 0;
  }
}


#####################################
void __cdecl Answer::SafeQueue<Answer::NetPacket *>::push(
        Answer::SafeQueue<Answer::NetPacket*> *const this,
        Answer::NetPacket *val)
{
  Answer::NetPacket *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Answer::NetPacket*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Answer::NetPacket *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<GameMsg *>::size(Answer::SafeQueue<GameMsg*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<User *>::push(Answer::SafeQueue<User*> *const this, User *val)
{
  User *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<User*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<User *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<User *>::size(Answer::SafeQueue<User*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<Player *>::push(Answer::SafeQueue<Player*> *const this, Player *val)
{
  Player *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Player*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Player *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Player *>::size(Answer::SafeQueue<Player*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<CObjPet *>::push(Answer::SafeQueue<CObjPet*> *const this, CObjPet *val)
{
  CObjPet *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<CObjPet*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<CObjPet *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<CObjPet *>::size(Answer::SafeQueue<CObjPet*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<Monster *>::push(Answer::SafeQueue<Monster*> *const this, Monster *val)
{
  Monster *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Monster*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Monster *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Monster *>::size(Answer::SafeQueue<Monster*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<Dungeon *>::push(Answer::SafeQueue<Dungeon*> *const this, Dungeon *val)
{
  Dungeon *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Dungeon*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Dungeon *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Dungeon *>::size(Answer::SafeQueue<Dungeon*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<MonsterDungeon *>::push(
        Answer::SafeQueue<MonsterDungeon*> *const this,
        MonsterDungeon *val)
{
  MonsterDungeon *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<MonsterDungeon*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<MonsterDungeon *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<MonsterDungeon *>::size(Answer::SafeQueue<MonsterDungeon*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<CDropItem *>::push(Answer::SafeQueue<CDropItem*> *const this, CDropItem *val)
{
  CDropItem *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<CDropItem*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<CDropItem *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<CDropItem *>::size(Answer::SafeQueue<CDropItem*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<Trap *>::push(Answer::SafeQueue<Trap*> *const this, Trap *val)
{
  Trap *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Trap*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Trap *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Trap *>::size(Answer::SafeQueue<Trap*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<PlantDungeon *>::push(Answer::SafeQueue<PlantDungeon*> *const this, PlantDungeon *val)
{
  PlantDungeon *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<PlantDungeon*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<PlantDungeon *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<PlantDungeon *>::size(Answer::SafeQueue<PlantDungeon*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<MonsterActivity *>::push(
        Answer::SafeQueue<MonsterActivity*> *const this,
        MonsterActivity *val)
{
  MonsterActivity *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<MonsterActivity*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<MonsterActivity *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<MonsterActivity *>::size(Answer::SafeQueue<MonsterActivity*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<NpcActivity *>::push(Answer::SafeQueue<NpcActivity*> *const this, NpcActivity *val)
{
  NpcActivity *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<NpcActivity*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<NpcActivity *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<NpcActivity *>::size(Answer::SafeQueue<NpcActivity*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<PlantActivity *>::push(
        Answer::SafeQueue<PlantActivity*> *const this,
        PlantActivity *val)
{
  PlantActivity *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<PlantActivity*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<PlantActivity *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<PlantActivity *>::size(Answer::SafeQueue<PlantActivity*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<Trailer *>::push(Answer::SafeQueue<Trailer*> *const this, Trailer *val)
{
  Trailer *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Trailer*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Trailer *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Trailer *>::size(Answer::SafeQueue<Trailer*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<CObjCarrier *>::push(Answer::SafeQueue<CObjCarrier*> *const this, CObjCarrier *val)
{
  CObjCarrier *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<CObjCarrier*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<CObjCarrier *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<CObjCarrier *>::size(Answer::SafeQueue<CObjCarrier*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<CTerritory *>::push(Answer::SafeQueue<CTerritory*> *const this, CTerritory *val)
{
  CTerritory *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<CTerritory*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<CTerritory *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<CTerritory *>::size(Answer::SafeQueue<CTerritory*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::SafeQueue<CLittleHelper *>::push(
        Answer::SafeQueue<CLittleHelper*> *const this,
        CLittleHelper *val)
{
  CLittleHelper *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<CLittleHelper*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<CLittleHelper *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<CLittleHelper *>::size(Answer::SafeQueue<CLittleHelper*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
bool __cdecl Answer::CheckKey::CheckKeyValid()
{
  bool v0; // bl
  Answer::MD5 md5; // [rsp+0h] [rbp-1D0h] BYREF
  Answer::Inifile ini; // [rsp+A0h] [rbp-130h] BYREF
  std::string TmpKey; // [rsp+E0h] [rbp-F0h] BYREF
  std::string md5string; // [rsp+F0h] [rbp-E0h] BYREF
  std::string ValidKey; // [rsp+100h] [rbp-D0h] BYREF
  std::string key; // [rsp+110h] [rbp-C0h] BYREF
  std::string keydate; // [rsp+120h] [rbp-B0h] BYREF
  std::string inifile; // [rsp+130h] [rbp-A0h] BYREF
  char v10; // [rsp+13Fh] [rbp-91h] BYREF
  std::string v11; // [rsp+140h] [rbp-90h] BYREF
  char v12; // [rsp+14Fh] [rbp-81h] BYREF
  std::string section; // [rsp+150h] [rbp-80h] BYREF
  char v14; // [rsp+15Fh] [rbp-71h] BYREF
  _BYTE v15[15]; // [rsp+160h] [rbp-70h] BYREF
  char v16; // [rsp+16Fh] [rbp-61h] BYREF
  std::string v17; // [rsp+170h] [rbp-60h] BYREF
  char v18; // [rsp+17Fh] [rbp-51h] BYREF
  _BYTE v19[15]; // [rsp+180h] [rbp-50h] BYREF
  char v20; // [rsp+18Fh] [rbp-41h] BYREF
  std::string v21; // [rsp+190h] [rbp-40h] BYREF
  char v22; // [rsp+19Fh] [rbp-31h] BYREF
  std::string p_StringTime; // [rsp+1A0h] [rbp-30h] BYREF
  char v24; // [rsp+1AFh] [rbp-21h] BYREF
  int32_t keylevel; // [rsp+1B0h] [rbp-20h]
  int32_t StartTime; // [rsp+1B4h] [rbp-1Ch]
  int32_t DiffDay; // [rsp+1B8h] [rbp-18h]
  int32_t ValidDay; // [rsp+1BCh] [rbp-14h]

  std::allocator<char>::allocator(&v10);
  std::string::string(&inifile, ".key.ini");
  std::allocator<char>::~allocator(&v10);
  Answer::Inifile::Inifile(&ini);
  Answer::Inifile::parse(&ini, &inifile);
  std::allocator<char>::allocator(&v12);
  std::string::string(&v11, "keylevel");
  std::allocator<char>::allocator(&v14);
  std::string::string(&section, "key");
  keylevel = Answer::Inifile::getIntValue(&ini, &section, &v11);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v14);
  std::string::~string(&v11);
  std::allocator<char>::~allocator(&v12);
  std::allocator<char>::allocator(&v16);
  std::string::string(v15, "keydate");
  std::allocator<char>::allocator(&v18);
  std::string::string(&v17, "key");
  Answer::Inifile::getStrValue((Answer::Inifile *const)&keydate, (const std::string *const)&ini, &v17);
  std::string::~string(&v17);
  std::allocator<char>::~allocator(&v18);
  std::string::~string(v15);
  std::allocator<char>::~allocator(&v16);
  std::allocator<char>::allocator(&v20);
  std::string::string(v19, "key");
  std::allocator<char>::allocator(&v22);
  std::string::string(&v21, "key");
  Answer::Inifile::getStrValue((Answer::Inifile *const)&key, (const std::string *const)&ini, &v21);
  std::string::~string(&v21);
  std::allocator<char>::~allocator(&v22);
  std::string::~string(v19);
  std::allocator<char>::~allocator(&v20);
  std::string::string(&p_StringTime, &keydate);
  StartTime = Answer::DayTime::StringToIntTime(&p_StringTime);
  std::string::~string(&p_StringTime);
  DiffDay = Answer::DayTime::daydiff(StartTime);
  ValidDay = 0;
  std::allocator<char>::allocator(&v24);
  std::string::string(&ValidKey, &unk_8F67C6);
  std::allocator<char>::~allocator(&v24);
  if ( keylevel == 2 )
  {
    ValidDay = 35;
    std::string::operator=(&ValidKey, "ye4M0bKrZLZc3elShdL7zKfTAbzvtSZx");
  }
  else if ( keylevel > 2 )
  {
    if ( keylevel == 3 )
    {
      ValidDay = 180;
      std::string::operator=(&ValidKey, "B1e9krKz8p03iRXv0Dlpl1bTXOf1sN21");
    }
    else
    {
      if ( keylevel != 4 )
        goto LABEL_12;
      ValidDay = 360;
      std::string::operator=(&ValidKey, "FRNNCLcbSGMQYGQlGZASefeVKt7ieE4i");
    }
  }
  else
  {
    if ( keylevel != 1 )
    {
LABEL_12:
      v0 = 0;
      goto LABEL_16;
    }
    ValidDay = 15;
    std::string::operator=(&ValidKey, "9eTztuuKvYHL1VrF94Whe97zEVTp4gRy");
  }
  if ( DiffDay <= ValidDay )
  {
    std::operator+<char>(&md5string, &keydate);
    Answer::MD5::MD5(&md5);
    Answer::MD5::md5sum((Answer::MD5 *const)&TmpKey, (const std::string *const)&md5);
    v0 = !std::operator!=<char>(&TmpKey, &key);
    std::string::~string(&TmpKey);
    Answer::MD5::~MD5(&md5);
    std::string::~string(&md5string);
  }
  else
  {
    v0 = 0;
  }
LABEL_16:
  std::string::~string(&ValidKey);
  std::string::~string(&key);
  std::string::~string(&keydate);
  Answer::Inifile::~Inifile(&ini);
  std::string::~string(&inifile);
  return v0;
}


#####################################
void __cdecl Answer::MySqlQuery::setRes(Answer::MySqlQuery *const this, MYSQL_RES *res)
{
  Answer::MySqlQuery::freeRes(this);
  this->m_result = res;
  if ( this->m_result )
  {
    this->m_fieldCount = mysql_num_fields(this->m_result);
    this->m_rowCount = mysql_num_rows(this->m_result);
    mysql_data_seek(this->m_result, 0);
    this->m_currentRow = (MYSQL_ROW)mysql_fetch_row(this->m_result);
  }
}


#####################################
void __cdecl Answer::MySqlQuery::freeRes(Answer::MySqlQuery *const this)
{
  if ( this->m_result )
  {
    mysql_free_result(this->m_result);
    this->m_result = 0;
    this->m_rowCount = 0;
    this->m_fieldCount = 0;
    this->m_currentRow = 0;
  }
}


#####################################
int __cdecl Answer::MySqlQuery::seekRow(Answer::MySqlQuery *const this, int index)
{
  if ( this->m_rowCount <= 0 || index < 0 || this->m_rowCount <= index )
    return 0;
  mysql_data_seek(this->m_result, index);
  this->m_currentRow = (MYSQL_ROW)mysql_fetch_row(this->m_result);
  return index;
}


#####################################
void __cdecl Answer::MySqlQuery::nextRow(Answer::MySqlQuery *const this)
{
  if ( this->m_result )
    this->m_currentRow = (MYSQL_ROW)mysql_fetch_row(this->m_result);
}


#####################################
int __cdecl Answer::MySqlQuery::getIntValue(Answer::MySqlQuery *const this, int fieldIndex, const int intNull)
{
  if ( this->m_result
    && this->m_currentRow
    && this->m_fieldCount > 0
    && fieldIndex >= 0
    && this->m_fieldCount > fieldIndex
    && this->m_currentRow[fieldIndex] )
  {
    return atoi(this->m_currentRow[fieldIndex]);
  }
  else
  {
    return intNull;
  }
}


#####################################
int64_t __cdecl Answer::MySqlQuery::getInt64Value(
        Answer::MySqlQuery *const this,
        const char *fieldName,
        const int intNull)
{
  int fieldIndx; // [rsp+2Ch] [rbp-4h]

  if ( !this->m_result || !this->m_currentRow || !fieldName )
    return intNull;
  fieldIndx = Answer::MySqlQuery::getFieldIndex(this, fieldName);
  if ( this->m_result
    && this->m_currentRow
    && this->m_fieldCount > 0
    && fieldIndx >= 0
    && this->m_fieldCount > fieldIndx
    && this->m_currentRow[fieldIndx] )
  {
    return strtoll(this->m_currentRow[fieldIndx], 0, 10);
  }
  else
  {
    return intNull;
  }
}


#####################################
int __cdecl Answer::MySqlQuery::getIntValue(Answer::MySqlQuery *const this, const char *fieldName, const int intNull)
{
  int FieldIndex; // ecx

  if ( !this->m_result || !this->m_currentRow || !fieldName )
    return intNull;
  FieldIndex = Answer::MySqlQuery::getFieldIndex(this, fieldName);
  return Answer::MySqlQuery::getIntValue(this, FieldIndex, intNull);
}


#####################################
int __cdecl Answer::MySqlQuery::getFieldIndex(Answer::MySqlQuery *const this, const char *fieldName)
{
  int i; // [rsp+14h] [rbp-Ch]
  MYSQL_FIELD *field; // [rsp+18h] [rbp-8h]

  if ( !this->m_result || this->m_fieldCount <= 0 || !fieldName )
    return -1;
  mysql_field_seek(this->m_result, 0);
  for ( i = 0; this->m_fieldCount > i; ++i )
  {
    field = (MYSQL_FIELD *)mysql_fetch_field(this->m_result);
    if ( field && !strcasecmp(field->name, fieldName) )
      return i;
  }
  return -1;
}


#####################################
int __cdecl Answer::MySqlDB::open(
        Answer::MySqlDB *const this,
        const std::string *const host,
        const std::string *const user,
        const std::string *const passwd,
        const std::string *const db,
        unsigned int port)
{
  __int64 v7; // r14
  __int64 v8; // r13
  __int64 v9; // r12
  __int64 v10; // rbx
  const char *v11; // rax
  const char *v12; // rax
  MYSQL *pConnection; // [rsp+48h] [rbp-28h]

  pConnection = (MYSQL *)mysql_init(0);
  if ( pConnection )
  {
    v7 = std::string::c_str((std::string *)db);
    v8 = std::string::c_str((std::string *)passwd);
    v9 = std::string::c_str((std::string *)user);
    v10 = std::string::c_str((std::string *)host);
    if ( mysql_real_connect(pConnection, v10, v9, v8, v7, port, 0, 0x10000) )
    {
      if ( (unsigned int)mysql_set_character_set(pConnection, "utf8") )
      {
        v12 = (const char *)mysql_error(pConnection);
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "mysql_set_character_set with error %s\n", v12);
        mysql_close(pConnection);
        return 4;
      }
      else
      {
        Answer::MySqlDB::close(this);
        this->m_connection = pConnection;
        std::string::operator=(&this->m_host, host);
        std::string::operator=(&this->m_user, user);
        std::string::operator=(&this->m_passwd, passwd);
        std::string::operator=(&this->m_db, db);
        this->m_port = port;
        return 0;
      }
    }
    else
    {
      v11 = (const char *)mysql_error(pConnection);
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "mysql_real_connect failed with error %s\n", v11);
      return 4;
    }
  }
  else
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "mysql_init failed\n");
    return 4;
  }
}


#####################################
void __cdecl Answer::MySqlDB::close(Answer::MySqlDB *const this)
{
  if ( this->m_connection )
  {
    mysql_close(this->m_connection);
    this->m_connection = 0;
  }
}


#####################################
int __cdecl Answer::MySqlDB::reopen(Answer::MySqlDB *const this)
{
  return Answer::MySqlDB::open(this, &this->m_host, &this->m_user, &this->m_passwd, &this->m_db, this->m_port);
}


#####################################
int __cdecl Answer::MySqlDB::excute(Answer::MySqlDB *const this, const char *sql)
{
  int error; // [rsp+1Ch] [rbp-4h]

  if ( this->m_connection && sql )
  {
    if ( (unsigned int)mysql_query(this->m_connection, sql) )
    {
      error = mysql_errno(this->m_connection);
      if ( error == 2014 || error == 2006 || error == 2013 )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "mysql_real_query failed with error = %d, sql = %s, try reopen\n",
          error,
          sql);
        Answer::MySqlDB::reopen(this);
        if ( (unsigned int)mysql_query(this->m_connection, sql) )
        {
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "mysql_real_query still failed after reopen\n");
          return 4;
        }
        else
        {
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "mysql_real_query succeed after reopen\n");
          return 0;
        }
      }
      else
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "mysql_real_query failed with error = %d, sql = %s\n",
          error,
          sql);
        return 4;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "MySqlDB::excute return with m_connection = %p, sql = %p\n",
      this->m_connection,
      sql);
    return 4;
  }
}


#####################################
int64_t __cdecl Answer::DayTime::tick()
{
  timeval tv; // [rsp+0h] [rbp-20h] BYREF

  gettimeofday(&tv, 0);
  return 1000 * tv.tv_sec + tv.tv_usec / 1000;
}


#####################################
void __cdecl Answer::DayTime::sleep(int milliseconds)
{
  timespec rem; // [rsp+10h] [rbp-30h] BYREF
  timespec req; // [rsp+20h] [rbp-20h] BYREF

  req.tv_sec = (milliseconds - (__int64)(milliseconds % 1000)) / 1000;
  req.tv_nsec = 1000000LL * (milliseconds % 1000);
  nanosleep(&req, &rem);
}


#####################################
int __cdecl Answer::DayTime::Diff24Hour(int old)
{
  return (Answer::DayTime::now() - old) / 86400;
}


#####################################
int __cdecl Answer::DayTime::daydiff(int old)
{
  int32_t v1; // eax
  int oldzero; // [rsp+18h] [rbp-8h]

  oldzero = Answer::DayTime::dayzero(old);
  v1 = Answer::DayTime::now();
  return (Answer::DayTime::dayzero(v1) - oldzero) / 86400;
}


#####################################
int __cdecl Answer::DayTime::daydiffBw(int old, int32_t newTime)
{
  int oldzero; // [rsp+18h] [rbp-8h]

  oldzero = Answer::DayTime::dayzero(old);
  return (Answer::DayTime::dayzero(newTime) - oldzero) / 86400;
}


#####################################
int __cdecl Answer::DayTime::day18diff(int old)
{
  tm tmnow; // [rsp+10h] [rbp-A0h] BYREF
  tm tmold; // [rsp+50h] [rbp-60h] BYREF
  int told; // [rsp+90h] [rbp-20h]
  int result_old; // [rsp+94h] [rbp-1Ch]
  int tnow; // [rsp+98h] [rbp-18h]
  int result_now; // [rsp+9Ch] [rbp-14h]

  told = old;
  Answer::DayTime::localnow(&tmold, old);
  result_old = 0;
  if ( tmold.tm_hour <= 17 )
    result_old = told - 86400 + 60 - tmold.tm_sec + 3600 * (17 - tmold.tm_hour) + 60 * (59 - tmold.tm_min);
  else
    result_old = -60 * tmold.tm_min + told - tmold.tm_sec + -3600 * tmold.tm_hour + 64800;
  tnow = Answer::DayTime::now();
  Answer::DayTime::localnow(&tmnow, tnow);
  result_now = 0;
  if ( tmnow.tm_hour <= 17 )
    result_now = tnow - 86400 + 60 - tmnow.tm_sec + 3600 * (17 - tmnow.tm_hour) + 60 * (59 - tmnow.tm_min);
  else
    result_now = -60 * tmnow.tm_min + tnow - tmnow.tm_sec + -3600 * tmnow.tm_hour + 64800;
  return (result_now - result_old) / 86400;
}


#####################################
int __cdecl Answer::DayTime::hourzero(int time)
{
  tm tmtime; // [rsp+10h] [rbp-40h] BYREF

  Answer::DayTime::localnow(&tmtime, time);
  return time - tmtime.tm_sec - 60 * tmtime.tm_min;
}


#####################################
int __cdecl Answer::DayTime::dayzero(int time)
{
  tm tmtime; // [rsp+10h] [rbp-40h] BYREF

  Answer::DayTime::localnow(&tmtime, time);
  return time - tmtime.tm_sec + -3600 * tmtime.tm_hour - 60 * tmtime.tm_min;
}


#####################################
int __cdecl Answer::DayTime::weekzero(int time)
{
  tm tmtime; // [rsp+10h] [rbp-40h] BYREF

  Answer::DayTime::localnow(&tmtime, time);
  return time - tmtime.tm_sec + -3600 * tmtime.tm_hour - 60 * tmtime.tm_min - 86400 * ((tmtime.tm_wday + 6) % 7);
}


#####################################
int __cdecl Answer::DayTime::monthzero(int time)
{
  tm tmtime; // [rsp+10h] [rbp-40h] BYREF

  Answer::DayTime::localnow(&tmtime, time);
  return time - tmtime.tm_sec + -3600 * tmtime.tm_hour - 60 * tmtime.tm_min - 86400 * tmtime.tm_mday;
}


#####################################
int __cdecl Answer::DayTime::weekdiff(int old)
{
  int32_t v1; // eax
  int oldzero; // [rsp+18h] [rbp-8h]

  oldzero = Answer::DayTime::weekzero(old);
  v1 = Answer::DayTime::now();
  return (Answer::DayTime::weekzero(v1) - oldzero) / 604800;
}


#####################################
int __cdecl Answer::DayTime::monthdiff(int old)
{
  tm tmnow; // [rsp+10h] [rbp-80h] BYREF
  tm tmold; // [rsp+50h] [rbp-40h] BYREF

  Answer::DayTime::localnow(&tmold, old);
  Answer::DayTime::localnow(&tmnow);
  return tmnow.tm_mon + 12 * (tmnow.tm_year - tmold.tm_year) - tmold.tm_mon;
}


#####################################
bool __cdecl Answer::DayTime::betweendate(int32_t begin_date, int32_t end_date)
{
  tm tmtime; // [rsp+10h] [rbp-40h] BYREF
  int32_t date; // [rsp+4Ch] [rbp-4h]

  Answer::DayTime::localnow(&tmtime);
  date = 10000 * tmtime.tm_year + 100 * (tmtime.tm_mon + 1) + 19000000 + tmtime.tm_mday;
  return date >= begin_date && date <= end_date;
}


#####################################
int32_t __cdecl Answer::DayTime::StringToIntTime(std::string *p_StringTime)
{
  int32_t v1; // ebx
  std::_Ios_Openmode v2; // eax
  int v3; // ebx
  const char *v4; // rax
  _QWORD *v5; // rax
  _BYTE v7[368]; // [rsp+10h] [rbp-210h] BYREF
  tm localtm; // [rsp+180h] [rbp-A0h] BYREF
  int tm_time[8]; // [rsp+1C0h] [rbp-60h] BYREF
  char buf[16]; // [rsp+1E0h] [rbp-40h] BYREF
  std::string timestr; // [rsp+1F0h] [rbp-30h] BYREF
  int index; // [rsp+204h] [rbp-1Ch]
  time_t result; // [rsp+208h] [rbp-18h]

  if ( std::string::size(p_StringTime) != 19 )
    return 0;
  if ( !(unsigned int)std::string::compare(p_StringTime, "0000-00-00 00:00:00") )
    return 0;
  std::string::string(&timestr);
  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
    v7,
    p_StringTime,
    (unsigned int)v2);
  strcpy(buf, "-- :: ");
  index = 0;
  memset(tm_time, 0, 24);
  while ( 1 )
  {
    v5 = (_QWORD *)std::getline<char,std::char_traits<char>,std::allocator<char>>(
                     v7,
                     &timestr,
                     (unsigned int)buf[index]);
    if ( !std::ios::operator void *((char *)v5 + *(_QWORD *)(*v5 - 24LL)) )
      break;
    v3 = index;
    v4 = (const char *)std::string::c_str(&timestr);
    tm_time[v3] = atoi(v4);
    ++index;
  }
  memset(&localtm, 0, sizeof(localtm));
  localtm.tm_year = tm_time[0] - 1900;
  localtm.tm_mon = tm_time[1] - 1;
  localtm.tm_mday = tm_time[2];
  localtm.tm_hour = tm_time[3];
  localtm.tm_min = tm_time[4];
  localtm.tm_sec = tm_time[5];
  result = mktime(&localtm);
  v1 = result;
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v7);
  std::string::~string(&timestr);
  return v1;
}


#####################################
int __cdecl Answer::DBPool::init(
        Answer::DBPool *const this,
        int count,
        const std::string *const host,
        const std::string *const user,
        const std::string *const passwd,
        const std::string *const db,
        unsigned int port)
{
  Answer::MySqlDB *v8; // rbx
  Answer::MySqlDB *v9; // rbx
  Answer::MySqlDB *connection; // [rsp+30h] [rbp-30h] BYREF
  int i; // [rsp+38h] [rbp-28h]

  if ( count <= 0 )
    return 0;
  for ( i = 0; i < count; ++i )
  {
    v8 = (Answer::MySqlDB *)operator new(0x48u);
    Answer::MySqlDB::MySqlDB(v8);
    connection = v8;
    if ( Answer::MySqlDB::open(v8, host, user, passwd, db, port) )
    {
      v9 = connection;
      if ( connection )
      {
        Answer::MySqlDB::~MySqlDB(connection);
        operator delete(v9);
      }
    }
    else
    {
      Answer::BlockingQueue<Answer::MySqlDB *>::push(&this->m_pool, &connection);
    }
  }
  return Answer::BlockingQueue<Answer::MySqlDB *>::size(&this->m_pool);
}


#####################################
void __cdecl Answer::DBPool::clear(Answer::DBPool *const this)
{
  Answer::MySqlDB *connection; // [rsp+18h] [rbp-18h]

  while ( Answer::BlockingQueue<Answer::MySqlDB *>::size(&this->m_pool) > 0 )
  {
    connection = Answer::BlockingQueue<Answer::MySqlDB *>::pop(&this->m_pool);
    if ( connection )
    {
      Answer::MySqlDB::close(connection);
      Answer::MySqlDB::~MySqlDB(connection);
      operator delete(connection);
    }
  }
}


#####################################
void __cdecl Answer::DBPool::push(Answer::DBPool *const this, Answer::MySqlDB *connection)
{
  Answer::MySqlDB *connectiona; // [rsp+0h] [rbp-10h] BYREF
  Answer::DBPool *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  connectiona = connection;
  if ( connection )
    Answer::BlockingQueue<Answer::MySqlDB *>::push(&thisa->m_pool, &connectiona);
}


#####################################
int __cdecl Answer::MySqlDBGuard::excute(Answer::MySqlDBGuard *const this, const char *sql)
{
  if ( this->m_dbconn )
    return Answer::MySqlDB::excute(this->m_dbconn, sql);
  else
    return 4;
}


#####################################
int __cdecl Answer::MySqlDBGuard::lastInsertId(Answer::MySqlDBGuard *const this)
{
  if ( this->m_dbconn )
    return Answer::MySqlDB::lastInsertId(this->m_dbconn);
  else
    return 0;
}


#####################################
void __cdecl Answer::BlockingQueue<Answer::MySqlDB *>::push(
        Answer::BlockingQueue<Answer::MySqlDB*> *const this,
        Answer::MySqlDB *const *const val)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_mutex);
  Answer::SafeQueue<Answer::MySqlDB *>::push(&this->m_queue, *val);
  Answer::Condition::notify(&this->m_cond);
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl Answer::SafeQueue<Answer::MySqlDB *>::push(
        Answer::SafeQueue<Answer::MySqlDB*> *const this,
        Answer::MySqlDB *val)
{
  Answer::MySqlDB *vala; // [rsp+0h] [rbp-30h] BYREF
  Answer::SafeQueue<Answer::MySqlDB*> *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  vala = val;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  std::list<Answer::MySqlDB *>::push_back(&this->m_queue, &vala);
  ++thisa->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Answer::MySqlDB *>::size(Answer::SafeQueue<Answer::MySqlDB*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
std::string __cdecl Answer::InetAddress::getIP(const Answer::InetAddress *const this)
{
  struct in_addr *v1; // rsi
  char *v2; // rax
  _BYTE v4[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v4);
  v2 = inet_ntoa(v1[1]);
  std::string::string(this, v2);
  std::allocator<char>::~allocator(v4);
  return (std::string)this;
}


#####################################
uint16_t __cdecl Answer::InetAddress::getPort(const Answer::InetAddress *const this)
{
  return ntohs(this->m_addr.sin_port);
}


#####################################
bool __cdecl Answer::Inifile::parse(Answer::Inifile *const this, const std::string *const file)
{
  __int64 v2; // rax
  bool v3; // bl
  _BYTE v5[256]; // [rsp+10h] [rbp-230h] BYREF
  __int64 v6; // [rsp+110h] [rbp-130h] BYREF
  std::string strline; // [rsp+220h] [rbp-20h] BYREF

  v2 = std::string::c_str((std::string *)file);
  std::ifstream::basic_ifstream(v5, v2, 8);
  if ( (unsigned __int8)std::ifstream::is_open(v5) != 1 )
  {
    v3 = 0;
  }
  else
  {
    while ( (unsigned __int8)std::ios::eof(&v6) != 1 )
    {
      std::string::string(&strline);
      std::getline<char,std::char_traits<char>,std::allocator<char>>(v5, &strline, 10);
      Answer::Inifile::analyze(this, &strline);
      std::string::~string(&strline);
    }
    v3 = !std::map<std::string,std::string>::empty(&this->m_strMap);
  }
  std::ifstream::~ifstream(v5);
  return v3;
}


#####################################
std::string __cdecl Answer::Inifile::getStrValue(
        Answer::Inifile *const this,
        const std::string *const section,
        const std::string *const key)
{
  std::pair<const std::string,std::string > *v3; // rax
  std::_Rb_tree_iterator<std::pair<const std::string,std::string > > it; // [rsp+20h] [rbp-60h] BYREF
  std::string __x; // [rsp+30h] [rbp-50h] BYREF
  std::string __lhs; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::string,std::string > > v9; // [rsp+50h] [rbp-30h] BYREF

  std::string::string((std::string *)this);
  std::operator+<char>(&__lhs, key);
  std::operator+<char>(&__x, &__lhs);
  it._M_node = std::map<std::string,std::string>::find((std::map<std::string,std::string> *const)section, &__x)._M_node;
  std::string::~string(&__x);
  std::string::~string(&__lhs);
  v9._M_node = std::map<std::string,std::string>::end((std::map<std::string,std::string> *const)section)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<std::string const,std::string>>::operator!=(&it, &v9) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<std::string const,std::string>>::operator->(&it);
    std::string::operator=(this, &v3->second);
  }
  return (std::string)this;
}


#####################################
int __cdecl Answer::Inifile::getIntValue(
        Answer::Inifile *const this,
        const std::string *const section,
        const std::string *const key)
{
  const char *v3; // rax
  int v4; // ebx
  std::string v6; // [rsp+20h] [rbp-20h] BYREF

  Answer::Inifile::getStrValue((Answer::Inifile *const)&v6, (const std::string *const)this, section);
  v3 = (const char *)std::string::c_str(&v6);
  v4 = atoi(v3);
  std::string::~string(&v6);
  return v4;
}


#####################################
void __cdecl Answer::Inifile::analyze(Answer::Inifile *const this, const std::string *const strline)
{
  std::string *v3; // rax
  std::string strkey; // [rsp+10h] [rbp-A0h] BYREF
  std::string strtail; // [rsp+20h] [rbp-90h] BYREF
  std::string strhead; // [rsp+30h] [rbp-80h] BYREF
  std::string v7; // [rsp+40h] [rbp-70h] BYREF
  std::string v8; // [rsp+50h] [rbp-60h] BYREF
  std::string v9; // [rsp+60h] [rbp-50h] BYREF
  std::string __k; // [rsp+70h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+80h] [rbp-30h] BYREF
  size_t first; // [rsp+90h] [rbp-20h]
  size_t last; // [rsp+98h] [rbp-18h]

  first = std::string::find((std::string *)strline, 91, 0);
  last = std::string::rfind((std::string *)strline, 93, 0xFFFFFFFFFFFFFFFFLL);
  if ( first == -1 || last == -1 || last + 1 == first )
  {
    first = std::string::find((std::string *)strline, 61, 0);
    if ( first != -1 )
    {
      std::string::substr(&strhead, (unsigned __int64)strline, 0);
      std::string::substr(&strtail, (unsigned __int64)strline, first + 1);
      first = std::string::find_first_not_of(&strhead, " \t", 0);
      last = std::string::find_last_not_of(&strhead, " \t", 0xFFFFFFFFFFFFFFFFLL);
      if ( first != -1 && last != -1 )
      {
        std::string::substr(&strkey, (unsigned __int64)&strhead, first);
        first = std::string::find_first_not_of(&strtail, " \t", 0);
        last = std::string::find(&strtail, "\t#", first);
        if ( last != -1
          || (last = std::string::find(&strtail, " #", first), last != -1)
          || (last = std::string::find(&strtail, "\t//", first), last != -1)
          || (last = std::string::find(&strtail, " //", first), last != -1) )
        {
          std::string::substr(&v8, (unsigned __int64)&strtail, 0);
          std::string::operator=(&strtail, &v8);
          std::string::~string(&v8);
        }
        last = std::string::find_last_not_of(&strtail, " \t", 0xFFFFFFFFFFFFFFFFLL);
        if ( first != -1 && last != -1 )
        {
          std::string::substr(&v9, (unsigned __int64)&strtail, first);
          std::operator+<char>(&__lhs, &this->m_currentSection);
          std::operator+<char>(&__k, &__lhs);
          v3 = std::map<std::string,std::string>::operator[](&this->m_strMap, &__k);
          std::string::operator=(v3, &v9);
          std::string::~string(&__k);
          std::string::~string(&__lhs);
          std::string::~string(&v9);
        }
        std::string::~string(&strkey);
      }
      std::string::~string(&strtail);
      std::string::~string(&strhead);
    }
  }
  else
  {
    std::string::substr(&v7, (unsigned __int64)strline, first + 1);
    std::string::operator=(&this->m_currentSection, &v7);
    std::string::~string(&v7);
  }
}


#####################################
int __cdecl Answer::Logger::open(const char *path, const char *mode)
{
  FILE *fp; // [rsp+18h] [rbp-8h]

  if ( Answer::Logger::m_fp && Answer::Logger::m_fp != (FILE *)stdout && Answer::Logger::m_fp != (FILE *)stderr )
  {
    fclose(Answer::Logger::m_fp);
    Answer::Logger::m_fp = 0;
  }
  fp = fopen(path, mode);
  if ( !fp )
    return *__errno_location();
  Answer::Logger::m_fp = fp;
  return 0;
}


#####################################
int __cdecl Answer::Logger::close()
{
  if ( !Answer::Logger::m_fp || Answer::Logger::m_fp == (FILE *)stdout || Answer::Logger::m_fp == (FILE *)stderr )
    return 0;
  else
    return fclose(Answer::Logger::m_fp);
}


#####################################
void __cdecl Answer::Logger::setLogLevel(Answer::LogLevel level)
{
  if ( (unsigned int)level <= Answer::LogLevel::LOG_DUNGEON_INFO )
    Answer::Logger::m_logLevel = level;
}


#####################################
std::string __cdecl Answer::MD5::md5sum(Answer::MD5 *const this, const std::string *const inputString)
{
  std::string *v2; // rdx
  unsigned int v3; // r12d
  const char *v4; // rcx
  std::string *inputStringa; // [rsp+0h] [rbp-70h]
  char szMD5[48]; // [rsp+10h] [rbp-60h] BYREF
  char szDigest[27]; // [rsp+40h] [rbp-30h] BYREF
  char v9; // [rsp+5Bh] [rbp-15h] BYREF
  int i; // [rsp+5Ch] [rbp-14h]

  inputStringa = v2;
  memset(szDigest, 0, 16);
  v3 = std::string::length(v2);
  v4 = (const char *)std::string::c_str(inputStringa);
  Answer::MD5::MD5Update((Answer::MD5 *const)inputString, v4, v3);
  Answer::MD5::MD5Final((Answer::MD5 *const)inputString, szDigest);
  memset(szMD5, 0, 33);
  for ( i = 0; i <= 15; ++i )
    sprintf(&szMD5[2 * i], "%02x", (unsigned __int8)szDigest[i]);
  std::allocator<char>::allocator(&v9);
  std::string::string(this, szMD5);
  std::allocator<char>::~allocator(&v9);
  return (std::string)this;
}


#####################################
void __cdecl Answer::MD5::MD5Init(Answer::MD5 *const this)
{
  this->count[1] = 0;
  this->count[0] = this->count[1];
  this->state[0] = 1732584193;
  this->state[1] = -271733879;
  this->state[2] = -1732584194;
  this->state[3] = 271733878;
  Answer::MD5::MD5_memset(this, this->PADDING, 0, 0x40u);
  this->PADDING[0] = 0x80;
}


#####################################
void __cdecl Answer::MD5::MD5Update(Answer::MD5 *const this, const char *input, const unsigned int inputLen)
{
  unsigned int i; // [rsp+24h] [rbp-1Ch]
  uint32_t index; // [rsp+28h] [rbp-18h]

  index = (this->count[0] >> 3) & 0x3F;
  this->count[0] += 8 * inputLen;
  if ( this->count[0] < 8 * inputLen )
    ++this->count[1];
  this->count[1] += inputLen >> 29;
  if ( inputLen < 64 - index )
  {
    i = 0;
  }
  else
  {
    Answer::MD5::MD5_memcpy(this, &this->buffer[index], (unsigned __int8 *)input, 64 - index);
    Answer::MD5::MD5Transform(this, this->state, this->buffer);
    for ( i = 64 - index; i + 63 < inputLen; i += 64 )
      Answer::MD5::MD5Transform(this, this->state, (unsigned __int8 *)&input[i]);
    index = 0;
  }
  Answer::MD5::MD5_memcpy(this, &this->buffer[index], (unsigned __int8 *)&input[i], inputLen - i);
}


#####################################
void __cdecl Answer::MD5::MD5Final(Answer::MD5 *const this, char *digest)
{
  unsigned int v2; // eax
  unsigned __int8 bits[8]; // [rsp+10h] [rbp-20h] BYREF
  unsigned int index; // [rsp+18h] [rbp-18h]
  unsigned int padLen; // [rsp+1Ch] [rbp-14h]

  Answer::MD5::Encode(this, bits, this->count, 8u);
  index = (this->count[0] >> 3) & 0x3F;
  if ( index > 0x37 )
    v2 = 120 - index;
  else
    v2 = 56 - index;
  padLen = v2;
  Answer::MD5::MD5Update(this, (const char *)this->PADDING, v2);
  Answer::MD5::MD5Update(this, (const char *)bits, 8u);
  Answer::MD5::Encode(this, (unsigned __int8 *)digest, this->state, 0x10u);
  Answer::MD5::MD5Init(this);
}


#####################################
void __cdecl Answer::MD5::MD5Transform(Answer::MD5 *const this, uint32_t *state, unsigned __int8 *block)
{
  int v3; // et0
  int v4; // et0
  int v5; // et0
  int v6; // et0
  int v7; // et0
  int v8; // et0
  int v9; // et0
  int v10; // et0
  int v11; // et0
  int v12; // et0
  int v13; // et0
  int v14; // et0
  int v15; // et0
  int v16; // et0
  int v17; // et0
  int v18; // et0
  int v19; // et0
  int v20; // et0
  int v21; // et0
  int v22; // et0
  int v23; // et0
  int v24; // et0
  int v25; // et0
  int v26; // et0
  int v27; // et0
  int v28; // et0
  int v29; // et0
  int v30; // et0
  int v31; // et0
  int v32; // et0
  int v33; // et0
  int v34; // et0
  int v35; // et0
  int v36; // et0
  int v37; // et0
  int v38; // et0
  int v39; // et0
  int v40; // et0
  int v41; // et0
  int v42; // et0
  int v43; // et0
  int v44; // et0
  int v45; // et0
  int v46; // et0
  int v47; // et0
  int v48; // et0
  int v49; // et0
  int v50; // et0
  int v51; // et0
  int v52; // et0
  int v53; // et0
  int v54; // et0
  int v55; // et0
  int v56; // et0
  int v57; // et0
  int v58; // et0
  int v59; // et0
  int v60; // et0
  int v61; // et0
  int v62; // et0
  int v63; // et0
  int v64; // et0
  int v65; // et0
  uint32_t x[16]; // [rsp+20h] [rbp-60h] BYREF
  uint32_t a; // [rsp+60h] [rbp-20h]
  uint32_t b; // [rsp+64h] [rbp-1Ch]
  uint32_t c; // [rsp+68h] [rbp-18h]
  uint32_t d; // [rsp+6Ch] [rbp-14h]

  a = *state;
  b = state[1];
  c = state[2];
  d = state[3];
  Answer::MD5::Decode(this, x, block, 0x40u);
  a = a + (d & ~b | c & b) + x[0] - 680876936;
  v3 = __ROR4__(a, 25);
  a = b + v3;
  d = d + (c & ~(b + v3) | b & (b + v3)) + x[1] - 389564586;
  v4 = __ROR4__(d, 20);
  d = a + v4;
  c += (b & ~(a + v4) | a & (a + v4)) + x[2] + 606105819;
  v5 = __ROR4__(c, 15);
  c = d + v5;
  b = b + (a & ~(d + v5) | d & (d + v5)) + x[3] - 1044525330;
  v6 = __ROR4__(b, 10);
  b = c + v6;
  a = a + (d & ~(c + v6) | c & (c + v6)) + x[4] - 176418897;
  v7 = __ROR4__(a, 25);
  a = b + v7;
  d += (c & ~(b + v7) | b & (b + v7)) + x[5] + 1200080426;
  v8 = __ROR4__(d, 20);
  d = a + v8;
  c = c + (b & ~(a + v8) | a & (a + v8)) + x[6] - 1473231341;
  v9 = __ROR4__(c, 15);
  c = d + v9;
  b = b + (a & ~(d + v9) | d & (d + v9)) + x[7] - 45705983;
  v10 = __ROR4__(b, 10);
  b = c + v10;
  a += (d & ~(c + v10) | c & (c + v10)) + x[8] + 1770035416;
  v11 = __ROR4__(a, 25);
  a = b + v11;
  d = d + (c & ~(b + v11) | b & (b + v11)) + x[9] - 1958414417;
  v12 = __ROR4__(d, 20);
  d = a + v12;
  c = c + (b & ~(a + v12) | a & (a + v12)) + x[10] - 42063;
  v13 = __ROR4__(c, 15);
  c = d + v13;
  b = b + (a & ~(d + v13) | d & (d + v13)) + x[11] - 1990404162;
  v14 = __ROR4__(b, 10);
  b = c + v14;
  a += (d & ~(c + v14) | c & (c + v14)) + x[12] + 1804603682;
  v15 = __ROR4__(a, 25);
  a = b + v15;
  d = d + (c & ~(b + v15) | b & (b + v15)) + x[13] - 40341101;
  v16 = __ROR4__(d, 20);
  d = a + v16;
  c = c + (b & ~(a + v16) | a & (a + v16)) + x[14] - 1502002290;
  v17 = __ROR4__(c, 15);
  c = d + v17;
  b += (a & ~(d + v17) | d & (d + v17)) + x[15] + 1236535329;
  v18 = __ROR4__(b, 10);
  b = c + v18;
  a = a + (c & ~d | d & (c + v18)) + x[1] - 165796510;
  v19 = __ROR4__(a, 27);
  a = b + v19;
  d = d + (b & ~c | c & (b + v19)) + x[6] - 1069501632;
  v20 = __ROR4__(d, 23);
  d = a + v20;
  c += (a & ~b | b & (a + v20)) + x[11] + 643717713;
  v21 = __ROR4__(c, 18);
  c = d + v21;
  b = b + (d & ~a | a & (d + v21)) + x[0] - 373897302;
  v22 = __ROR4__(b, 12);
  b = c + v22;
  a = a + (c & ~d | d & (c + v22)) + x[5] - 701558691;
  v23 = __ROR4__(a, 27);
  a = b + v23;
  d += (b & ~c | c & (b + v23)) + x[10] + 38016083;
  v24 = __ROR4__(d, 23);
  d = a + v24;
  c = c + (a & ~b | b & (a + v24)) + x[15] - 660478335;
  v25 = __ROR4__(c, 18);
  c = d + v25;
  b = b + (d & ~a | a & (d + v25)) + x[4] - 405537848;
  v26 = __ROR4__(b, 12);
  b = c + v26;
  a += (c & ~d | d & (c + v26)) + x[9] + 568446438;
  v27 = __ROR4__(a, 27);
  a = b + v27;
  d = d + (b & ~c | c & (b + v27)) + x[14] - 1019803690;
  v28 = __ROR4__(d, 23);
  d = a + v28;
  c = c + (a & ~b | b & (a + v28)) + x[3] - 187363961;
  v29 = __ROR4__(c, 18);
  c = d + v29;
  b += (d & ~a | a & (d + v29)) + x[8] + 1163531501;
  v30 = __ROR4__(b, 12);
  b = c + v30;
  a = a + (c & ~d | d & (c + v30)) + x[13] - 1444681467;
  v31 = __ROR4__(a, 27);
  a = b + v31;
  d = d + (b & ~c | c & (b + v31)) + x[2] - 51403784;
  v32 = __ROR4__(d, 23);
  d = a + v32;
  c += (a & ~b | b & (a + v32)) + x[7] + 1735328473;
  v33 = __ROR4__(c, 18);
  c = d + v33;
  b = b + (d & ~a | a & (d + v33)) + x[12] - 1926607734;
  v34 = __ROR4__(b, 12);
  b = c + v34;
  a = a + (d ^ (c + v34) ^ c) + x[5] - 378558;
  v35 = __ROR4__(a, 28);
  a = b + v35;
  d = d + (c ^ (b + v35) ^ b) + x[8] - 2022574463;
  v36 = __ROR4__(d, 21);
  d = a + v36;
  c += (b ^ (a + v36) ^ a) + x[11] + 1839030562;
  v37 = __ROR4__(c, 16);
  c = d + v37;
  b = b + (a ^ (d + v37) ^ d) + x[14] - 35309556;
  v38 = __ROR4__(b, 9);
  b = c + v38;
  a = a + (d ^ (c + v38) ^ c) + x[1] - 1530992060;
  v39 = __ROR4__(a, 28);
  a = b + v39;
  d += (c ^ (b + v39) ^ b) + x[4] + 1272893353;
  v40 = __ROR4__(d, 21);
  d = a + v40;
  c = c + (b ^ (a + v40) ^ a) + x[7] - 155497632;
  v41 = __ROR4__(c, 16);
  c = d + v41;
  b = b + (a ^ (d + v41) ^ d) + x[10] - 1094730640;
  v42 = __ROR4__(b, 9);
  b = c + v42;
  a += (d ^ (c + v42) ^ c) + x[13] + 681279174;
  v43 = __ROR4__(a, 28);
  a = b + v43;
  d = d + (c ^ (b + v43) ^ b) + x[0] - 358537222;
  v44 = __ROR4__(d, 21);
  d = a + v44;
  c = c + (b ^ (a + v44) ^ a) + x[3] - 722521979;
  v45 = __ROR4__(c, 16);
  c = d + v45;
  b += (a ^ (d + v45) ^ d) + x[6] + 76029189;
  v46 = __ROR4__(b, 9);
  b = c + v46;
  a = a + (d ^ (c + v46) ^ c) + x[9] - 640364487;
  v47 = __ROR4__(a, 28);
  a = b + v47;
  d = d + (c ^ (b + v47) ^ b) + x[12] - 421815835;
  v48 = __ROR4__(d, 21);
  d = a + v48;
  c += (b ^ (a + v48) ^ a) + x[15] + 530742520;
  v49 = __ROR4__(c, 16);
  c = d + v49;
  b = b + (a ^ (d + v49) ^ d) + x[2] - 995338651;
  v50 = __ROR4__(b, 9);
  b = c + v50;
  a = a + (c ^ ((c + v50) | ~d)) + x[0] - 198630844;
  v51 = __ROR4__(a, 26);
  a = b + v51;
  d += (b ^ ((b + v51) | ~c)) + x[7] + 1126891415;
  v52 = __ROR4__(d, 22);
  d = a + v52;
  c = c + (a ^ ((a + v52) | ~b)) + x[14] - 1416354905;
  v53 = __ROR4__(c, 17);
  c = d + v53;
  b = b + (d ^ ((d + v53) | ~a)) + x[5] - 57434055;
  v54 = __ROR4__(b, 11);
  b = c + v54;
  a += (c ^ ((c + v54) | ~d)) + x[12] + 1700485571;
  v55 = __ROR4__(a, 26);
  a = b + v55;
  d = d + (b ^ ((b + v55) | ~c)) + x[3] - 1894986606;
  v56 = __ROR4__(d, 22);
  d = a + v56;
  c = c + (a ^ ((a + v56) | ~b)) + x[10] - 1051523;
  v57 = __ROR4__(c, 17);
  c = d + v57;
  b = b + (d ^ ((d + v57) | ~a)) + x[1] - 2054922799;
  v58 = __ROR4__(b, 11);
  b = c + v58;
  a += (c ^ ((c + v58) | ~d)) + x[8] + 1873313359;
  v59 = __ROR4__(a, 26);
  a = b + v59;
  d = d + (b ^ ((b + v59) | ~c)) + x[15] - 30611744;
  v60 = __ROR4__(d, 22);
  d = a + v60;
  c = c + (a ^ ((a + v60) | ~b)) + x[6] - 1560198380;
  v61 = __ROR4__(c, 17);
  c = d + v61;
  b += (d ^ ((d + v61) | ~a)) + x[13] + 1309151649;
  v62 = __ROR4__(b, 11);
  b = c + v62;
  a = a + (c ^ ((c + v62) | ~d)) + x[4] - 145523070;
  v63 = __ROR4__(a, 26);
  a = b + v63;
  d = d + (b ^ ((b + v63) | ~c)) + x[11] - 1120210379;
  v64 = __ROR4__(d, 22);
  d = a + v64;
  c += (a ^ ((a + v64) | ~b)) + x[2] + 718787259;
  v65 = __ROR4__(c, 17);
  c = d + v65;
  b = b + (d ^ ((d + v65) | ~a)) + x[9] - 343485551;
  b = d + v65 + __ROR4__(b, 11);
  *state += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  Answer::MD5::MD5_memset(this, (unsigned __int8 *)x, 0, 0x40u);
}


#####################################
void __cdecl Answer::MD5::Encode(Answer::MD5 *const this, unsigned __int8 *output, uint32_t *input, unsigned int len)
{
  unsigned int i; // [rsp+24h] [rbp-8h]
  unsigned int j; // [rsp+28h] [rbp-4h]

  i = 0;
  for ( j = 0; j < len; j += 4 )
  {
    output[j] = input[i];
    output[j + 1] = BYTE1(input[i]);
    output[j + 2] = BYTE2(input[i]);
    output[j + 3] = HIBYTE(input[i++]);
  }
}


#####################################
void __cdecl Answer::MD5::Decode(Answer::MD5 *const this, uint32_t *output, unsigned __int8 *input, unsigned int len)
{
  unsigned int i; // [rsp+24h] [rbp-8h]
  unsigned int j; // [rsp+28h] [rbp-4h]

  i = 0;
  for ( j = 0; j < len; j += 4 )
    output[i++] = (input[j + 2] << 16) | (input[j + 1] << 8) | input[j] | (input[j + 3] << 24);
}


#####################################
void __cdecl Answer::MD5::MD5_memcpy(
        Answer::MD5 *const this,
        unsigned __int8 *output,
        unsigned __int8 *input,
        unsigned int len)
{
  memcpy(output, input, len);
}


#####################################
void __cdecl Answer::MD5::MD5_memset(Answer::MD5 *const this, unsigned __int8 *output, int value, unsigned int len)
{
  memset(output, value, len);
}


#####################################
void __cdecl Answer::NetPacketPool::push(Answer::NetPacketPool *const this, Answer::NetPacket *netpacket)
{
  unsigned int m_bufferSize; // ebx
  int BufferSize; // eax
  Answer::NetPacket *v5; // rbx
  unsigned int m_maxCount; // ebx
  int v7; // eax

  if ( netpacket && !Answer::NetPacket::subRefCount(netpacket) )
  {
    if ( Answer::NetPacket::getBufferSize(netpacket) > this->m_bufferSize )
    {
      m_bufferSize = this->m_bufferSize;
      BufferSize = Answer::NetPacket::getBufferSize(netpacket);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_DEBUG,
        "NetPacketPool %p push large size, delete %p with size %d, m_bufferSize %d\n",
        this,
        netpacket,
        BufferSize,
        m_bufferSize);
      v5 = netpacket;
      if ( !netpacket )
        return;
      goto LABEL_8;
    }
    if ( Answer::SafeQueue<Answer::NetPacket *>::size(&this->m_pool) < (int)this->m_maxCount )
    {
      if ( this->m_log )
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_DEBUG,
          "NetPacketPool %p push netpacket %p to m_pool\n",
          this,
          netpacket);
      Answer::SafeQueue<Answer::NetPacket *>::push(&this->m_pool, netpacket);
    }
    else
    {
      m_maxCount = this->m_maxCount;
      v7 = Answer::SafeQueue<Answer::NetPacket *>::size(&this->m_pool);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_DEBUG,
        "NetPacketPool %p push pool is full delete %p with pool size %d, m_maxCount %d\n",
        this,
        netpacket,
        v7,
        m_maxCount);
      v5 = netpacket;
      if ( netpacket )
      {
LABEL_8:
        Answer::NetPacket::~NetPacket(netpacket);
        operator delete(v5);
      }
    }
  }
}


#####################################
void __cdecl Answer::NetPacket::reset(Answer::NetPacket *const this)
{
  this->m_rOffset = 0;
  this->m_wOffset = 0;
  this->m_rOverFlow = 0;
  this->m_wOverFlow = 0;
  this->type = Answer::PackType::PACK_UNKNOWN;
  this->m_proc = 0;
  this->m_size = 0;
  this->m_refCount = 1;
  this->m_scalable = 1;
}


#####################################
__int64 __cdecl Answer::NetPacket::subRefCount(Answer::NetPacket *const this)
{
  return _InterlockedDecrement64(&this->m_refCount);
}


#####################################
__int64 __cdecl Answer::SafeQueue<Answer::NetPacket *>::size(Answer::SafeQueue<Answer::NetPacket*> *const this)
{
  __int64 m_size; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  m_size = this->m_size;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_size;
}


#####################################
void __cdecl Answer::Random::init(Answer::Random *const this, bool useDevice)
{
  unsigned int v2; // eax

  if ( useDevice )
    this->m_fd = open("/dev/urandom", 0);
  v2 = time(0);
  srand(v2);
}


#####################################
int __cdecl Answer::Random::generate(Answer::Random *const this, int min, int max)
{
  bool bfu; // [rsp+17h] [rbp-9h]
  int32_t nTemp; // [rsp+18h] [rbp-8h]
  int addon; // [rsp+1Ch] [rbp-4h]

  bfu = 0;
  nTemp = max + 1 - min;
  if ( max + 1 == min )
    return 0;
  if ( nTemp < 0 )
  {
    nTemp = min - (max + 1);
    bfu = 1;
  }
  addon = (int)abs32(Answer::Random::randomInt(this)) % nTemp;
  if ( bfu )
    addon = -addon;
  return min + addon;
}


#####################################
int __cdecl Answer::Random::randomInt(Answer::Random *const this)
{
  int random; // [rsp+1Ch] [rbp-4h] BYREF

  random = 0;
  if ( this->m_fd != -1 && read(this->m_fd, &random, 4u) != -1 )
    return random;
  else
    return rand();
}


#####################################
int __cdecl Answer::StringUtility::utf8Strlen(const char *str)
{
  int byteLength; // [rsp+10h] [rbp-10h]
  int length; // [rsp+14h] [rbp-Ch]
  int index; // [rsp+18h] [rbp-8h]
  char ch_0; // [rsp+1Fh] [rbp-1h]
  char ch_0a; // [rsp+1Fh] [rbp-1h]

  if ( !str )
    return 0;
  byteLength = strlen(str);
  length = 0;
  index = 0;
  while ( index < byteLength )
  {
    ch_0 = str[index];
    ++length;
    if ( ++index >= byteLength )
      break;
    if ( ch_0 < 0 )
    {
      for ( ch_0a = 2 * ch_0; ch_0a < 0; ch_0a *= 2 )
        ++index;
    }
  }
  return length;
}


#####################################
std::string __cdecl Answer::StringUtility::combi(const Int32Vector *const ve, const std::string *const delims)
{
  const int *v2; // rax
  const int *v3; // rax
  std::string tempStr_0; // [rsp+10h] [rbp-B0h] BYREF
  char buff_0[32]; // [rsp+20h] [rbp-A0h] BYREF
  std::string tempStr; // [rsp+40h] [rbp-80h] BYREF
  char buff[32]; // [rsp+50h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > it; // [rsp+70h] [rbp-50h] BYREF
  char v10; // [rsp+7Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+80h] [rbp-40h] BYREF
  char v12; // [rsp+8Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > v13; // [rsp+90h] [rbp-30h] BYREF
  _BYTE v14[33]; // [rsp+9Fh] [rbp-21h] BYREF

  std::allocator<char>::allocator(&v10);
  std::string::string(ve, &unk_8F6F70);
  std::allocator<char>::~allocator(&v10);
  it._M_current = std::vector<int>::begin((const std::vector<int> *const)delims)._M_current;
  __rhs._M_current = std::vector<int>::end((const std::vector<int> *const)delims)._M_current;
  if ( __gnu_cxx::operator!=<int const*,std::vector<int>>(&it, &__rhs) )
  {
    memset(buff, 0, 20);
    std::allocator<char>::allocator(&v12);
    std::string::string(&tempStr, &unk_8F6F70);
    std::allocator<char>::~allocator(&v12);
    v2 = __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&it);
    sprintf(buff, "%d", *v2);
    std::string::operator=(&tempStr, buff);
    std::string::operator+=(ve, &tempStr);
    __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&it, 0);
    std::string::~string(&tempStr);
  }
  while ( 1 )
  {
    v13._M_current = std::vector<int>::end((const std::vector<int> *const)delims)._M_current;
    if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&it, &v13) )
      break;
    memset(buff_0, 0, 20);
    std::allocator<char>::allocator(v14);
    std::string::string(&tempStr_0, &unk_8F6F70);
    std::allocator<char>::~allocator(v14);
    v3 = __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&it);
    sprintf(buff_0, "%d", *v3);
    std::string::operator=(&tempStr_0, buff_0);
    std::string::operator+=(ve, ":");
    std::string::operator+=(ve, &tempStr_0);
    std::string::~string(&tempStr_0);
    __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&it);
  }
  return (std::string)ve;
}


#####################################
std::string __cdecl Answer::StringUtility::toString(int64_t val)
{
  std::_Ios_Openmode v1; // eax
  _BYTE v3[16]; // [rsp+10h] [rbp-180h] BYREF
  __int64 v4; // [rsp+20h] [rbp-170h] BYREF

  v1 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v3, (unsigned int)v1);
  std::ostream::operator<<(&v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(val, v3);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v3);
  return (std::string)val;
}


#####################################
std::string __cdecl Answer::StringUtility::replace(
        const std::string *const templatestr,
        const std::string *const findstr,
        const std::string *const replacestr)
{
  std::string *v3; // rcx
  unsigned __int64 v4; // rax
  __int64 v5; // rax
  std::string *replacestra; // [rsp+8h] [rbp-48h]
  size_t pos; // [rsp+28h] [rbp-28h]

  replacestra = v3;
  std::string::string((std::string *)templatestr, findstr);
  for ( pos = std::string::find((std::string *)templatestr, replacestr, 0);
        pos != -1;
        pos = std::string::find((std::string *)templatestr, replacestr, pos + v5) )
  {
    v4 = std::string::size((std::string *)replacestr);
    std::string::replace((std::string *)templatestr, pos, v4, replacestra);
    v5 = std::string::size(replacestra);
  }
  return (std::string)templatestr;
}


#####################################
void __cdecl Answer::TcpClient::~TcpClient(Answer::TcpClient *const this)
{
  Answer::TcpClient::~TcpClient(this);
  operator delete(this);
}


#####################################
void __cdecl Answer::TcpClient::run(Answer::TcpClient *const this)
{
  const char *v1; // rax
  const char *v2; // rax
  const char *v3; // rax
  fd_set wfds; // [rsp+10h] [rbp-140h] BYREF
  fd_set rfds; // [rsp+90h] [rbp-C0h] BYREF
  timeval timeout; // [rsp+110h] [rbp-40h] BYREF
  int err; // [rsp+128h] [rbp-28h]
  int __d0; // [rsp+12Ch] [rbp-24h]
  int __d1; // [rsp+130h] [rbp-20h]
  int __d0_0; // [rsp+134h] [rbp-1Ch]
  int __d1_0; // [rsp+138h] [rbp-18h]
  int error; // [rsp+13Ch] [rbp-14h]

  if ( !this->m_connected )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "TcpClient::run() enter with m_connected = false, return\n");
  }
  else
  {
    while ( this->m_connected )
    {
      memset(&rfds, 0, sizeof(rfds));
      __d0 = 0;
      __d1 = (unsigned int)&timeout;
      memset(&wfds, 0, sizeof(wfds));
      __d0_0 = 0;
      __d1_0 = (unsigned int)&rfds;
      rfds.fds_bits[this->m_fd / 64] |= 1LL << (this->m_fd % 64);
      if ( Answer::TcpClient::needSend(this) )
        wfds.fds_bits[this->m_fd / 64] |= 1LL << (this->m_fd % 64);
      timeout.tv_sec = 0;
      timeout.tv_usec = 50000;
      err = select(this->m_fd + 1, &rfds, &wfds, 0, &timeout);
      if ( err <= 0 )
      {
        if ( err )
        {
          error = *__errno_location();
          v3 = (const char *)std::string::c_str(&this->m_name);
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "TcpClient %s run select return %d, errno = %d\n",
            v3,
            err,
            error);
          if ( error != 4 )
            this->m_connected = 0;
        }
      }
      else
      {
        if ( ((rfds.fds_bits[this->m_fd / 64] >> (this->m_fd % 64)) & 1) != 0 && Answer::TcpClient::onRecv(this) == -1 )
        {
          v1 = (const char *)std::string::c_str(&this->m_name);
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "TcpClient %s run onRecv return SOCKET_ERROR\n", v1);
          this->m_connected = 0;
        }
        if ( ((wfds.fds_bits[this->m_fd / 64] >> (this->m_fd % 64)) & 1) != 0 && Answer::TcpClient::onSend(this) == -1 )
        {
          v2 = (const char *)std::string::c_str(&this->m_name);
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "TcpClient %s run onSend return SOCKET_ERROR\n", v2);
          this->m_connected = 0;
        }
      }
    }
    Answer::close(this->m_fd);
    this->m_fd = -1;
  }
}


#####################################
std::string __cdecl Answer::TcpClient::getName(Answer::TcpClient *const this)
{
  const std::string *v1; // rsi

  std::string::string((std::string *)this, v1 + 5);
  return (std::string)this;
}


#####################################
void __cdecl Answer::TcpClient::reset(Answer::TcpClient *const this)
{
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_fd != -1 )
  {
    Answer::close(this->m_fd);
    this->m_fd = -1;
  }
  this->m_connected = 0;
  bzero(this->m_recvBuffer, this->m_recvBufferSize);
  this->m_recvOffset = 0;
  if ( this->m_packet )
    Answer::NetPacket::destroy(this->m_packet);
  this->m_decodeState = 0;
  while ( 1 )
  {
    packet = Answer::SafeQueue<Answer::NetPacket *>::pop(&this->m_sendList);
    if ( !packet )
      break;
    Answer::NetPacket::destroy(packet);
  }
  this->m_parseLen = 0;
  bzero(this->m_sendBuffer, this->m_sendBufferSize);
  this->m_sendLen = 0;
  this->m_sendCursor = 0;
}


#####################################
bool __cdecl Answer::TcpClient::connect(Answer::TcpClient *const this, const Answer::InetAddress *const serverAddr)
{
  socklen_t AddrLen; // ebx
  const sockaddr_in *SockAddr; // rax
  const struct sockaddr *v5; // rax
  int v6; // r12d
  int Port; // ebx
  const char *v8; // rax
  char szPolicy[23]; // [rsp+10h] [rbp-40h] BYREF
  Answer::InetAddress v10; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_fd == -1 && !this->m_connected )
  {
    this->m_serverAddr = *serverAddr;
    this->m_fd = socket(2, 1, 0);
    if ( this->m_fd == -1 )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "TcpClient::connect socket return INVALID_SOCKET, return false\n");
      return 0;
    }
    else
    {
      AddrLen = Answer::InetAddress::getAddrLen(&this->m_serverAddr);
      SockAddr = Answer::InetAddress::getSockAddr(&this->m_serverAddr);
      v5 = Answer::sockaddr_cast(SockAddr);
      *(_DWORD *)&v10.m_addr.sin_zero[4] = connect(this->m_fd, v5, AddrLen);
      if ( *(_DWORD *)&v10.m_addr.sin_zero[4] == -1 )
      {
        v6 = *__errno_location();
        Port = Answer::InetAddress::getPort(&this->m_serverAddr);
        Answer::InetAddress::getIP(&v10);
        v8 = (const char *)std::string::c_str((std::string *)&v10);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "TcpClient::connect connect return SOCKET_ERROR,ip = %s,port=%d errno %d\n",
          v8,
          Port,
          v6);
        std::string::~string(&v10);
        Answer::close(this->m_fd);
        this->m_fd = -1;
        return 0;
      }
      else
      {
        memset(szPolicy, 0, sizeof(szPolicy));
        *(_DWORD *)&v10.m_addr.sin_zero[4] = send(this->m_fd, szPolicy, 0x17u, 0);
        if ( *(_DWORD *)&v10.m_addr.sin_zero[4] == 23 )
        {
          Answer::setnonblock(this->m_fd);
          Answer::setnodelay(this->m_fd);
          Answer::setkeepalive(this->m_fd, 300);
          this->m_connected = 1;
          return 1;
        }
        else
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "TcpClient::connect send return %d\n",
            *(_DWORD *)&v10.m_addr.sin_zero[4]);
          Answer::close(this->m_fd);
          this->m_fd = -1;
          return 0;
        }
      }
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "TcpClient::connect with m_fd %d, m_connected %d return false\n",
      this->m_fd,
      this->m_connected);
    return 0;
  }
}


#####################################
void __cdecl Answer::TcpClient::sendPacket(Answer::TcpClient *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    if ( this->m_connected )
    {
      Answer::NetPacket::encodeHeadInfo(packet);
      Answer::SafeQueue<Answer::NetPacket *>::push(&this->m_sendList, packet);
    }
    else
    {
      Answer::NetPacket::destroy(packet);
    }
  }
}


#####################################
bool __cdecl Answer::TcpClient::needSend(Answer::TcpClient *const this)
{
  return Answer::SafeQueue<Answer::NetPacket *>::size(&this->m_sendList) > 0 || this->m_sendCursor < this->m_sendLen;
}


#####################################
int __cdecl Answer::TcpClient::onRecv(Answer::TcpClient *const this)
{
  int m_recvBufferSize; // r12d
  int m_recvOffset; // ebx
  const char *v3; // rax
  const char *v4; // rax
  const char *v5; // rax
  Answer::InetAddress v7; // [rsp+10h] [rbp-20h] BYREF

  *(_DWORD *)v7.m_addr.sin_zero = recv(
                                    this->m_fd,
                                    &this->m_recvBuffer[this->m_recvOffset],
                                    this->m_recvBufferSize - this->m_recvOffset,
                                    0);
  if ( *(int *)v7.m_addr.sin_zero <= 0 )
  {
    if ( *(_DWORD *)v7.m_addr.sin_zero )
    {
      *(_DWORD *)&v7.m_addr.sin_zero[4] = *__errno_location();
      v5 = (const char *)std::string::c_str(&this->m_name);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_INFO,
        "TcpClient %s onRecv recv return %d, errno = %d\n",
        v5,
        *(_DWORD *)v7.m_addr.sin_zero,
        *(_DWORD *)&v7.m_addr.sin_zero[4]);
      if ( *(_DWORD *)&v7.m_addr.sin_zero[4] == 11 || *(_DWORD *)&v7.m_addr.sin_zero[4] == 4 )
        *(_DWORD *)v7.m_addr.sin_zero = 0;
    }
    else
    {
      v4 = (const char *)std::string::c_str(&this->m_name);
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "TcpClient %s onRecv recv return 0\n", v4);
      *(_DWORD *)v7.m_addr.sin_zero = -1;
    }
  }
  else
  {
    this->m_recvOffset += *(_DWORD *)v7.m_addr.sin_zero;
    if ( this->m_recvOffset <= this->m_recvBufferSize )
    {
      Answer::TcpClient::decodeRecvBuffer(this);
    }
    else
    {
      m_recvBufferSize = this->m_recvBufferSize;
      m_recvOffset = this->m_recvOffset;
      Answer::InetAddress::getIP(&v7);
      v3 = (const char *)std::string::c_str((std::string *)&v7);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_INFO,
        "TcpClient to ip %s m_recvOffset %d > m_recvBufferSize %d\n",
        v3,
        m_recvOffset,
        m_recvBufferSize);
      std::string::~string(&v7);
      *(_DWORD *)v7.m_addr.sin_zero = -1;
    }
  }
  return *(_DWORD *)v7.m_addr.sin_zero;
}


#####################################
int __cdecl Answer::TcpClient::onSend(Answer::TcpClient *const this)
{
  int m_sendLen; // r12d
  int m_sendCursor; // ebx
  const char *v3; // rax
  const char *v4; // rax
  const char *v5; // rax
  Answer::InetAddress v7; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_sendLen )
  {
    Answer::TcpClient::encodeSendBuffer(this);
    if ( !this->m_sendLen )
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "TcpClient::onSend m_sendLen == 0 after encodeSendBuffer\n");
  }
  *(_DWORD *)v7.m_addr.sin_zero = send(
                                    this->m_fd,
                                    &this->m_sendBuffer[this->m_sendCursor],
                                    this->m_sendLen - this->m_sendCursor,
                                    0);
  if ( *(int *)v7.m_addr.sin_zero <= 0 )
  {
    if ( *(_DWORD *)v7.m_addr.sin_zero )
    {
      *(_DWORD *)&v7.m_addr.sin_zero[4] = *__errno_location();
      v5 = (const char *)std::string::c_str(&this->m_name);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_INFO,
        "TcpClient %s onSend send return %d, errno = %d\n",
        v5,
        *(_DWORD *)v7.m_addr.sin_zero,
        *(_DWORD *)&v7.m_addr.sin_zero[4]);
      if ( *(_DWORD *)&v7.m_addr.sin_zero[4] == 11 || *(_DWORD *)&v7.m_addr.sin_zero[4] == 4 )
        *(_DWORD *)v7.m_addr.sin_zero = 0;
    }
    else
    {
      v4 = (const char *)std::string::c_str(&this->m_name);
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "TcpClient %s onSend send return 0\n", v4);
      *(_DWORD *)v7.m_addr.sin_zero = -1;
    }
  }
  else
  {
    this->m_sendCursor += *(_DWORD *)v7.m_addr.sin_zero;
    if ( this->m_sendCursor == this->m_sendLen )
    {
      this->m_sendLen = 0;
      this->m_sendCursor = 0;
    }
    else if ( this->m_sendCursor > this->m_sendLen )
    {
      m_sendLen = this->m_sendLen;
      m_sendCursor = this->m_sendCursor;
      Answer::InetAddress::getIP(&v7);
      v3 = (const char *)std::string::c_str((std::string *)&v7);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_INFO,
        "TcpClient to ip %s m_sendCursor %d > m_sendLen %d\n",
        v3,
        m_sendCursor,
        m_sendLen);
      std::string::~string(&v7);
      *(_DWORD *)v7.m_addr.sin_zero = -1;
    }
  }
  return *(_DWORD *)v7.m_addr.sin_zero;
}


#####################################
void __cdecl Answer::TcpClient::decodeRecvBuffer(Answer::TcpClient *const this)
{
  uint32_t Size; // ebx
  uint32_t v2; // ebx
  uint32_t haslen; // [rsp+18h] [rbp-28h] BYREF
  uint32_t needlen; // [rsp+1Ch] [rbp-24h] BYREF
  int decodeOffset; // [rsp+20h] [rbp-20h]
  uint8_t packType; // [rsp+25h] [rbp-1Bh]
  uint16_t proc; // [rsp+26h] [rbp-1Ah]
  uint32_t datalen; // [rsp+28h] [rbp-18h]
  uint32_t writelen; // [rsp+2Ch] [rbp-14h]

  decodeOffset = 0;
  while ( !this->m_decodeState && this->m_recvOffset - decodeOffset > 6
       || this->m_decodeState == 1 && this->m_recvOffset - decodeOffset > 0 )
  {
    if ( !this->m_decodeState )
    {
      packType = this->m_recvBuffer[decodeOffset];
      proc = *(_WORD *)&this->m_recvBuffer[decodeOffset + 1];
      datalen = *(_DWORD *)&this->m_recvBuffer[decodeOffset + 3];
      if ( (signed int)datalen > this->m_recvBufferSize )
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_INFO,
          "TcpClient::decodeRecvBuffer very large packet packType = %d, proc = %d, datalen = %d, m_recvBufferSize = %d\n",
          packType,
          proc,
          datalen,
          this->m_recvBufferSize);
      decodeOffset += 7;
      this->m_packet = Answer::NetPacketPool::pop(&this->m_bufferPool, datalen);
      Answer::NetPacket::setType(this->m_packet, (Answer::PackType)packType);
      Answer::NetPacket::setProc(this->m_packet, proc);
      Answer::NetPacket::setSize(this->m_packet, datalen);
      this->m_decodeState = 1;
    }
    if ( this->m_decodeState == 1 )
    {
      if ( this->m_packet )
      {
        Size = Answer::NetPacket::getSize(this->m_packet);
        needlen = Size - Answer::NetPacket::getWOffset(this->m_packet);
        haslen = this->m_recvOffset - decodeOffset;
        writelen = *std::min<unsigned int>(&needlen, &haslen);
        Answer::NetPacket::write(this->m_packet, &this->m_recvBuffer[decodeOffset], writelen);
        decodeOffset += writelen;
        v2 = Answer::NetPacket::getSize(this->m_packet);
        if ( v2 == Answer::NetPacket::getWOffset(this->m_packet) )
        {
          (*((void (__fastcall **)(Answer::TcpClient *const, Answer::NetPacket *))this->_vptr_Thread + 3))(
            this,
            this->m_packet);
          this->m_packet = 0;
          this->m_decodeState = 0;
        }
      }
    }
  }
  if ( this->m_recvOffset > decodeOffset )
    memmove(this->m_recvBuffer, &this->m_recvBuffer[decodeOffset], this->m_recvOffset - decodeOffset);
  this->m_recvOffset -= decodeOffset;
}


#####################################
void __cdecl Answer::TcpClient::encodeSendBuffer(Answer::TcpClient *const this)
{
  int m_sendLen; // ebx
  int m_sendBufferSize; // r13d
  int m_parseLen; // r12d
  uint32_t Size; // eax
  size_t v5; // rbx
  char *Buffer; // rax
  Answer::NetPacket *v7; // rax
  int32_t __b; // [rsp+28h] [rbp-38h] BYREF
  int32_t __a; // [rsp+2Ch] [rbp-34h] BYREF
  Answer::NetPacket *nextPacket; // [rsp+30h] [rbp-30h]
  int len; // [rsp+3Ch] [rbp-24h]

  nextPacket = Answer::SafeQueue<Answer::NetPacket *>::front(&this->m_sendList);
  while ( nextPacket )
  {
    __b = this->m_sendBufferSize - this->m_sendLen;
    __a = Answer::NetPacket::getSize(nextPacket) - this->m_parseLen;
    len = *std::min<int>(&__a, &__b);
    if ( len <= 0 )
    {
      m_sendLen = this->m_sendLen;
      m_sendBufferSize = this->m_sendBufferSize;
      m_parseLen = this->m_parseLen;
      Size = Answer::NetPacket::getSize(nextPacket);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "TcpClient::encodeSendBuffer len = %d, nextPacket->getSize() = %d, m_parseLen = %d, m_sendBufferSize = %d, m_sendLen = %d\n",
        len,
        Size,
        m_parseLen,
        m_sendBufferSize,
        m_sendLen);
      return;
    }
    v5 = len;
    Buffer = Answer::NetPacket::getBuffer(nextPacket);
    memcpy(&this->m_sendBuffer[this->m_sendLen], &Buffer[this->m_parseLen - 7], v5);
    this->m_parseLen += len;
    LODWORD(v5) = this->m_parseLen;
    if ( (_DWORD)v5 == Answer::NetPacket::getSize(nextPacket) )
    {
      v7 = Answer::SafeQueue<Answer::NetPacket *>::pop(&this->m_sendList);
      Answer::NetPacket::destroy(v7);
      nextPacket = Answer::SafeQueue<Answer::NetPacket *>::front(&this->m_sendList);
      this->m_parseLen = 0;
    }
    this->m_sendLen += len;
    if ( this->m_sendLen == this->m_sendBufferSize )
      return;
  }
}


#####################################
void __cdecl Answer::NetPacket::encodeHeadInfo(Answer::NetPacket *const this)
{
  uint32_t v1; // edx
  char *buffer; // [rsp+18h] [rbp-8h]

  buffer = this->m_buffer - 7;
  *buffer = this->type;
  *(_WORD *)(buffer + 1) = this->m_proc;
  *(_DWORD *)(buffer + 3) = this->m_size;
  v1 = Answer::NetPacket::getSize(this) + 7;
  Answer::NetPacket::setSize(this, v1);
}


#####################################
void __cdecl Answer::TcpService::~TcpService(Answer::TcpService *const this)
{
  Answer::TcpService::~TcpService(this);
  operator delete(this);
}


#####################################
void __cdecl Answer::TcpService::sendPacketTo(
        Answer::TcpService *const this,
        int16_t index,
        Answer::NetPacket *inPacket)
{
  unsigned int v3; // edx
  uint32_t Size; // ebx
  char *Buffer; // rcx
  Answer::PackType Type; // edx
  uint16_t v7; // dx
  uint32_t WOffset; // edx
  uint32_t oldSize; // [rsp+2Ch] [rbp-24h]
  int32_t proc; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( inPacket )
  {
    oldSize = Answer::NetPacket::getSize(inPacket);
    if ( !oldSize )
    {
      proc = Answer::NetPacket::getProc(inPacket);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "TcpService::sendPacketTo size == 0 with proc = %d\n",
        proc);
    }
    if ( Answer::NetPacket::rightShift(inPacket, 4u) )
    {
      Answer::NetPacket::writeInt16(inPacket, 1);
      Answer::NetPacket::writeInt16(inPacket, index);
      Answer::NetPacket::setSize(inPacket, oldSize + 4);
      Answer::TcpClient::sendPacket(this, inPacket);
    }
    else
    {
      v3 = Answer::NetPacket::getSize(inPacket) + 4;
      packet = Answer::TcpClient::popNetpacket(this, v3);
      Answer::NetPacket::writeInt16(packet, 1);
      Answer::NetPacket::writeInt16(packet, index);
      Size = Answer::NetPacket::getSize(inPacket);
      Buffer = Answer::NetPacket::getBuffer(inPacket);
      Answer::NetPacket::write(packet, Buffer, Size);
      Type = Answer::NetPacket::getType(inPacket);
      Answer::NetPacket::setType(packet, Type);
      v7 = Answer::NetPacket::getProc(inPacket);
      Answer::NetPacket::setProc(packet, v7);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Answer::NetPacket::destroy(inPacket);
      Answer::TcpClient::sendPacket(this, packet);
    }
  }
}


#####################################
int32_t __cdecl Answer::TcpService::replySuccess(
        Answer::TcpService *const this,
        int16_t index,
        uint16_t proc,
        int64_t addon)
{
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  packet = Answer::TcpClient::popNetpacket(this);
  Answer::NetPacket::writeInt16(packet, 1);
  Answer::NetPacket::writeInt16(packet, index);
  Answer::NetPacket::writeUInt8(packet, 1u);
  Answer::NetPacket::writeInt64(packet, addon);
  Answer::NetPacket::setType(packet, Answer::PackType::PACK_PROCREPLY);
  Answer::NetPacket::setProc(packet, proc);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  Answer::TcpClient::sendPacket(this, packet);
  return 0;
}


#####################################
int32_t __cdecl Answer::TcpService::replyfailure(
        Answer::TcpService *const this,
        int16_t index,
        uint16_t proc,
        int32_t errcode,
        int64_t addon)
{
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  packet = Answer::TcpClient::popNetpacket(this);
  Answer::NetPacket::writeInt16(packet, 1);
  Answer::NetPacket::writeInt16(packet, index);
  Answer::NetPacket::writeUInt8(packet, 0);
  Answer::NetPacket::writeInt32(packet, errcode);
  Answer::NetPacket::writeInt64(packet, addon);
  Answer::NetPacket::setType(packet, Answer::PackType::PACK_PROCREPLY);
  Answer::NetPacket::setProc(packet, proc);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  Answer::TcpClient::sendPacket(this, packet);
  return errcode;
}


#####################################
void __cdecl Answer::NetPacket::writeUInt8(Answer::NetPacket *const this, uint8_t val)
{
  Answer::NetPacket::write<unsigned char>(this, val);
}


#####################################
void __cdecl Answer::NetPacket::write<unsigned char>(Answer::NetPacket *const this, unsigned __int8 val)
{
  if ( !this->m_wOverFlow )
  {
    if ( (unsigned __int64)this->m_wOffset + 1 <= this->m_bufferSize )
      goto LABEL_7;
    if ( this->m_scalable )
      Answer::NetPacket::reallocate(this);
    if ( (unsigned __int64)this->m_wOffset + 1 <= this->m_bufferSize )
    {
LABEL_7:
      this->m_buffer[this->m_wOffset++] = val;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "netpacket type = %d, proc = %d write overflow\n",
        this->type,
        this->m_proc);
      this->m_wOverFlow = 1;
    }
  }
}


#####################################
void __cdecl Answer::Thread::~Thread(Answer::Thread *const this)
{
  Answer::Thread::~Thread(this);
  operator delete(this);
}


#####################################
int __cdecl Answer::Thread::start(Answer::Thread *const this)
{
  int err; // [rsp+1Ch] [rbp-14h]

  err = pthread_create(&this->m_thread, 0, (void *(*)(void *))Answer::Thread::threadEntry, this);
  if ( err )
    return err;
  else
    return 0;
}


#####################################
void __cdecl Answer::Thread::join(Answer::Thread *const this)
{
  pthread_join(this->m_thread, 0);
}


#####################################
int32_t __cdecl Answer::Zip::uncompressFile(const char *filename, uint8_t *dest, uint32_t *destLen)
{
  int *v4; // rax
  uLongf uDestLen; // [rsp+20h] [rbp-40h] BYREF
  FILE *file; // [rsp+28h] [rbp-38h]
  __int64 filelen; // [rsp+30h] [rbp-30h]
  Bytef *pSrc; // [rsp+38h] [rbp-28h]
  size_t srcLen; // [rsp+40h] [rbp-20h]
  int zerr; // [rsp+4Ch] [rbp-14h]

  if ( filename && dest && destLen )
  {
    file = fopen(filename, "rb");
    if ( file )
    {
      fseek(file, 0, 2);
      filelen = ftell(file);
      fseek(file, 0, 0);
      pSrc = (Bytef *)calloc(filelen, 1u);
      srcLen = fread(pSrc, 1u, filelen, file);
      uDestLen = *destLen;
      zerr = uncompress(dest, &uDestLen, pSrc, srcLen);
      if ( zerr )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "Zlib::uncompressFile uncompress return %d when uncompress %s\n",
          zerr,
          filename);
        *destLen = uDestLen;
        free(pSrc);
        return 1;
      }
      else
      {
        *destLen = uDestLen;
        free(pSrc);
        return 0;
      }
    }
    else
    {
      v4 = __errno_location();
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "Zlib::uncompressFile %s fopen return NULL, errno = %d\n",
        filename,
        *v4);
      return 1;
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "Zlib::uncompressFile with filename = %p, dest = %p, destLen = %p\n",
      filename,
      dest,
      destLen);
    return 1;
  }
}


#####################################
int32_t __cdecl Answer::Zip::compress(char *dest, unsigned __int64 destlen, const char *src, unsigned __int64 srclen)
{
  __int64 v4; // r9
  unsigned __int64 destlena; // [rsp+10h] [rbp-30h] BYREF
  char *desta; // [rsp+18h] [rbp-28h]
  int zerr; // [rsp+2Ch] [rbp-14h]

  desta = dest;
  destlena = destlen;
  zerr = compress2(dest, &destlena, src, srclen, 9, v4, srclen, src);
  if ( !zerr )
    return destlena;
  Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Zip::compress return %d\n", zerr);
  return -1;
}


#####################################
int32_t __cdecl Answer::Zip::uncompressbuf(
        char *dest,
        unsigned __int64 destlen,
        const char *src,
        unsigned __int64 srclen)
{
  unsigned __int64 destlena; // [rsp+10h] [rbp-30h] BYREF
  char *desta; // [rsp+18h] [rbp-28h]
  int zerr; // [rsp+2Ch] [rbp-14h]

  desta = dest;
  destlena = destlen;
  zerr = uncompress(dest, &destlena, src, srclen);
  if ( !zerr )
    return destlena;
  Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Zip::uncompressbuf return %d\n", zerr);
  return -1;
}


#####################################
void __cdecl Answer::Condition::wait(Answer::Condition *const this)
{
  pthread_mutex_t *PthreadMutex; // rax

  PthreadMutex = Answer::Mutex::getPthreadMutex(this->m_mutex);
  pthread_cond_wait(&this->m_cond, PthreadMutex);
}


#####################################
void __cdecl Answer::Condition::timedwait(Answer::Condition *const this, int32_t seconds)
{
  pthread_mutex_t *PthreadMutex; // rax
  timespec abstime; // [rsp+10h] [rbp-10h] BYREF

  abstime.tv_nsec = 0;
  abstime.tv_sec = seconds + Answer::DayTime::now();
  PthreadMutex = Answer::Mutex::getPthreadMutex(this->m_mutex);
  pthread_cond_timedwait(&this->m_cond, PthreadMutex, &abstime);
}


#####################################
int __cdecl Answer::setkeepalive(socket_t fd, int idleseconds)
{
  int keepcnt; // [rsp+1Ch] [rbp-14h] BYREF
  int keepintvl; // [rsp+20h] [rbp-10h] BYREF
  int keepidle; // [rsp+24h] [rbp-Ch] BYREF
  int keepalive; // [rsp+28h] [rbp-8h] BYREF
  int err; // [rsp+2Ch] [rbp-4h]

  keepalive = 1;
  keepidle = idleseconds;
  keepintvl = 10;
  keepcnt = 5;
  err = 0;
  err = setsockopt(fd, 1, 9, &keepalive, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setkeepalive\n");
  err = setsockopt(fd, 6, 4, &keepidle, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setkeepalive\n");
  err = setsockopt(fd, 6, 5, &keepintvl, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setkeepalive\n");
  err = setsockopt(fd, 6, 6, &keepcnt, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setkeepalive\n");
  return err;
}


#####################################
int __cdecl Answer::setnodelay(socket_t fd)
{
  socklen_t optval; // [rsp+18h] [rbp-8h] BYREF
  int err; // [rsp+1Ch] [rbp-4h]

  optval = 1;
  err = setsockopt(fd, 6, 1, &optval, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setnodelay\n");
  return err;
}


#####################################
int __cdecl Answer::setnonblock(socket_t fd)
{
  unsigned int opts; // [rsp+18h] [rbp-8h]
  int err; // [rsp+1Ch] [rbp-4h]

  opts = fcntl(fd, 3) | 0x800;
  err = fcntl(fd, 4, opts);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "fcntl return -1 in Answer::setnonblock\n");
  return err;
}


#####################################
int __cdecl Answer::setreuseaddr(socket_t fd)
{
  socklen_t val; // [rsp+18h] [rbp-8h] BYREF
  int err; // [rsp+1Ch] [rbp-4h]

  val = 1;
  err = setsockopt(fd, 1, 2, &val, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setreuseaddr\n");
  return err;
}


#####################################
int __cdecl Answer::setreuseport(socket_t fd)
{
  socklen_t val; // [rsp+18h] [rbp-8h] BYREF
  int err; // [rsp+1Ch] [rbp-4h]

  val = 1;
  err = setsockopt(fd, 1, 15, &val, 4u);
  if ( err == -1 )
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_DEBUG, "setsockopt return SOCKET_ERROR in Answer::setreuseport\n");
  return err;
}


#####################################
int __cdecl Answer::getreadbuffer(socket_t fd)
{
  socklen_t optlen; // [rsp+18h] [rbp-8h] BYREF
  socklen_t optval; // [rsp+1Ch] [rbp-4h] BYREF

  optval = 0;
  optlen = 4;
  getsockopt(fd, 1, 8, &optval, &optlen);
  return optval;
}


#####################################
int __cdecl Answer::setreadbuffer(socket_t fd, socket_t size)
{
  socket_t sizea; // [rsp+8h] [rbp-18h] BYREF
  socket_t fda; // [rsp+Ch] [rbp-14h]
  int err; // [rsp+1Ch] [rbp-4h]

  fda = fd;
  sizea = size;
  err = setsockopt(fd, 1, 8, &sizea, 4u);
  if ( err == -1 )
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_DEBUG,
      "setsockopt return SOCKET_ERROR in Answer::setreadbuffer\n");
  return err;
}


#####################################
int __cdecl Answer::getwritebuffer(socket_t fd)
{
  socklen_t optlen; // [rsp+18h] [rbp-8h] BYREF
  socklen_t optval; // [rsp+1Ch] [rbp-4h] BYREF

  optval = 0;
  optlen = 4;
  getsockopt(fd, 1, 7, &optval, &optlen);
  return optval;
}


#####################################
int __cdecl Answer::setwritebuffer(socket_t fd, socket_t size)
{
  socket_t sizea; // [rsp+8h] [rbp-18h] BYREF
  socket_t fda; // [rsp+Ch] [rbp-14h]
  int err; // [rsp+1Ch] [rbp-4h]

  fda = fd;
  sizea = size;
  err = setsockopt(fd, 1, 7, &sizea, 4u);
  if ( err == -1 )
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_DEBUG,
      "setsockopt return SOCKET_ERROR in Answer::setwritebuffer\n");
  return err;
}


