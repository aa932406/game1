// Decompiled methods for class: TitleCard
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl TitleCard::~TitleCard(TitleCard *const this)
{
  TitleCard::~TitleCard(this);
  operator delete(this);
}


#####################################
int32_t __cdecl TitleCard::effect(
        TitleCard *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v5; // edx
  int32_t m_TitleId; // ebx
  CExtCharTitle *CharTitle; // rax
  int32_t Record; // [rsp+28h] [rbp-18h]

  if ( Player::getRecord(launcher, this->m_TitleId) == 1 )
    return 2;
  if ( this->m_Time == 1 )
  {
    Player::updateRecord(launcher, this->m_TitleId, 1);
  }
  else
  {
    if ( this->m_Time <= 0 )
      return 2;
    Record = Player::getRecord(launcher, this->m_TitleId);
    if ( Unit::getNow(launcher) >= Record )
    {
      v5 = this->m_Time * *count + Unit::getNow(launcher);
      Player::updateRecord(launcher, this->m_TitleId, v5);
    }
    else
    {
      Player::updateRecord(launcher, this->m_TitleId, this->m_Time * *count + Record);
    }
  }
  m_TitleId = this->m_TitleId;
  CharTitle = Player::GetCharTitle(launcher);
  CExtCharTitle::CheckAddTitle(CharTitle, 7, m_TitleId);
  return 0;
}


#####################################
bool __cdecl TitleCard::parseEffect(TitleCard *const this, int32_t id, const std::string *const strEffect)
{
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  bool v7; // bl
  StringVector Params; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v12[17]; // [rsp+4Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v12);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&Params, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v12);
  if ( std::vector<std::string>::size(&Params) == 2 )
  {
    v3 = std::vector<std::string>::operator[](&Params, 0);
    v4 = (const char *)std::string::c_str(v3);
    this->m_TitleId = atoi(v4);
    v5 = std::vector<std::string>::operator[](&Params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->m_Time = atoi(v6);
    v7 = 1;
  }
  else
  {
    v7 = 0;
  }
  std::vector<std::string>::~vector(&Params);
  return v7;
}


