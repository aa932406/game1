// Decompiled methods for class: SkillBook
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl SkillBook::~SkillBook(SkillBook *const this)
{
  SkillBook::~SkillBook(this);
  operator delete(this);
}


#####################################
int32_t __cdecl SkillBook::effect(
        SkillBook *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t m_SkillId; // ebx
  CExtCharSkill *CharSkill; // rax

  if ( *count <= 0 )
    return 2;
  m_SkillId = this->m_SkillId;
  CharSkill = Player::GetCharSkill(launcher);
  if ( CExtCharSkill::UseSkillBook(CharSkill, m_SkillId) )
    return 0;
  else
    return 10002;
}


#####################################
bool __cdecl SkillBook::parseEffect(SkillBook *const this, int32_t id, const std::string *const strEffect)
{
  bool v3; // bl
  std::string *v4; // rax
  const char *v5; // rax
  StringVector strParam; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  char v10; // [rsp+4Bh] [rbp-15h] BYREF
  int32_t nSzie; // [rsp+4Ch] [rbp-14h]

  this->m_itemid = id;
  std::allocator<char>::allocator(&v10);
  std::string::string(&delims, "|");
  Answer::StringUtility::split(&strParam, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v10);
  nSzie = std::vector<std::string>::size(&strParam);
  if ( nSzie == 1 )
  {
    v4 = std::vector<std::string>::operator[](&strParam, 0);
    v5 = (const char *)std::string::c_str(v4);
    this->m_SkillId = atoi(v5);
    v3 = this->m_SkillId > 0;
  }
  else
  {
    v3 = 0;
  }
  std::vector<std::string>::~vector(&strParam);
  return v3;
}


