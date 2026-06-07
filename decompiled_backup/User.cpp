// Decompiled methods for class: User
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl User::init(User *const this, int64_t uid, int32_t sid)
{
  this->m_uid = uid;
  this->m_sid = sid;
}


#####################################
void __cdecl User::reset(User *const this)
{
  this->m_uid = 0;
  this->m_sid = 0;
  this->m_cid = 0;
  this->m_player = 0;
}


#####################################
void __cdecl User::SetTencentInfo(User *const this, const TencentInfo *const info)
{
  TencentInfo::operator=(&this->m_tencentInfo, info);
}


