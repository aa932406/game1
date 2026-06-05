// Decompiled methods for class: CDaTiHD
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl CDaTiHD::~CDaTiHD(CDaTiHD *const this)
{
  CDaTiHD::~CDaTiHD(this);
  operator delete(this);
}


#####################################
void __cdecl CDaTiHD::reset(CDaTiHD *const this)
{
  CActivity::reset(this);
  this->m_DaTiIndex = 0;
  this->m_LastSendQuestions = 0;
  this->m_RandAnswerDaTiIndex = 0;
}


#####################################
void __cdecl CDaTiHD::CheckActivity(CDaTiHD *const this)
{
  CTimer *v1; // rsi
  ACTIVITY_STATE v2; // eax
  CTimer *v3; // rax
  CTimer *v4; // rax
  tm localnow_0; // [rsp+10h] [rbp-A0h] BYREF
  tm localnow; // [rsp+50h] [rbp-60h] BYREF
  bool bRightLine; // [rsp+8Fh] [rbp-21h]
  ACTIVITY_STATE nState; // [rsp+90h] [rbp-20h]
  int32_t NowSeconds; // [rsp+94h] [rbp-1Ch]
  int32_t startSeconds; // [rsp+98h] [rbp-18h]
  int32_t NowSeconds_0; // [rsp+9Ch] [rbp-14h]

  if ( (*((unsigned __int8 (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 48))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_TIME_OUT;
  }
  else if ( (*((unsigned __int8 (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 49))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  }
  else
  {
    v1 = Answer::Singleton<CTimer>::instance();
    CTimer::GetLocalNow(&localnow, v1);
    bRightLine = (*((__int64 (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 26))(this);
    v2 = (*((unsigned int (__fastcall **)(CDaTiHD *const, tm *))this->_vptr_CActivity + 50))(this, &localnow);
    nState = v2;
    if ( v2 == ACTIVITY_STATE::AS_READY )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END || this->m_nState == ACTIVITY_STATE::AS_NOT_START )
      {
        this->m_nState = ACTIVITY_STATE::AS_READY;
        if ( bRightLine )
          (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 46))(this);
      }
      if ( this->m_nState == ACTIVITY_STATE::AS_READY && bRightLine )
      {
        v3 = Answer::Singleton<CTimer>::instance();
        CTimer::GetLocalNow(&localnow_0, v3);
        NowSeconds = 60 * localnow_0.tm_min + 3600 * localnow_0.tm_hour + localnow_0.tm_sec;
        startSeconds = 60 * *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, 0);
        if ( startSeconds - NowSeconds <= 100 && !this->m_IsSendReadyStartToCs )
        {
          (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 10))(this);
          CDaTiHD::SendReadyStartDaTiHD(this);
          this->m_IsSendReadyStartToCs = 1;
        }
      }
    }
    else if ( v2 > ACTIVITY_STATE::AS_READY )
    {
      if ( v2 == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( this->m_nState == ACTIVITY_STATE::AS_READY )
        {
          this->m_nState = ACTIVITY_STATE::AS_RUNNING;
          if ( bRightLine )
          {
            CDaTiHD::RandomQuestions(this);
            CDaTiHD::SendStartDaTiHD(this);
            (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 47))(this);
            (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 10))(this);
          }
        }
        else if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING && bRightLine )
        {
          v4 = Answer::Singleton<CTimer>::instance();
          CTimer::GetLocalNow(&localnow_0, v4);
          NowSeconds_0 = 60 * localnow_0.tm_min + 3600 * localnow_0.tm_hour + localnow_0.tm_sec;
          if ( this->m_LastSendQuestions + 20 <= NowSeconds_0 )
          {
            ++this->m_DaTiIndex;
            CDaTiHD::SendQuestionsInfo(this, NowSeconds_0);
            this->m_LastSendQuestions = NowSeconds_0;
          }
        }
      }
      else if ( v2 == ACTIVITY_STATE::AS_END )
      {
        if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
        {
          this->m_nState = ACTIVITY_STATE::AS_END;
          if ( bRightLine )
          {
            CDaTiHD::SendEndDaTiHD(this);
            (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 10))(this);
          }
          (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 29))(this);
        }
        this->m_nState = ACTIVITY_STATE::AS_END;
      }
    }
    else if ( v2 == ACTIVITY_STATE::AS_NOT_START )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END )
      {
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
      else if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
      {
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
        if ( bRightLine )
        {
          CDaTiHD::SendEndDaTiHD(this);
          (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 10))(this);
        }
        (*((void (__fastcall **)(CDaTiHD *const))this->_vptr_CActivity + 29))(this);
      }
    }
  }
}


#####################################
void __cdecl CDaTiHD::RandAnswer(CDaTiHD *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_PROC, 0x4E47u);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 0);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v3, 0, packet);
  }
}


#####################################
void __cdecl CDaTiHD::RandomQuestions(CDaTiHD *const this)
{
  CFestivalDoubleEleven *v1; // rax
  CfgData *v2; // rax
  CfgData *v3; // rax
  unsigned int v4; // eax
  CfgQuestions *M_current; // rbx
  __gnu_cxx::__normal_iterator<CfgQuestions*,std::vector<CfgQuestions> > v6; // rax
  QuestionsVector __x; // [rsp+10h] [rbp-50h] BYREF
  QuestionsVector v8; // [rsp+30h] [rbp-30h] BYREF

  v1 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::IsInTime(v1, FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI) )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    CfgData::GetAllQuestions(&__x, v2, 1);
    std::vector<CfgQuestions>::operator=(&this->m_QuestionsVct, &__x);
    std::vector<CfgQuestions>::~vector(&__x);
  }
  else
  {
    v3 = Answer::Singleton<CfgData>::instance();
    CfgData::GetAllQuestions(&v8, v3, 0);
    std::vector<CfgQuestions>::operator=(&this->m_QuestionsVct, &v8);
    std::vector<CfgQuestions>::~vector(&v8);
  }
  v4 = time(0);
  srand(v4);
  M_current = std::vector<CfgQuestions>::end(&this->m_QuestionsVct)._M_current;
  v6._M_current = std::vector<CfgQuestions>::begin(&this->m_QuestionsVct)._M_current;
  std::random_shuffle<__gnu_cxx::__normal_iterator<CfgQuestions *,std::vector<CfgQuestions>>>(
    v6,
    (__gnu_cxx::__normal_iterator<CfgQuestions*,std::vector<CfgQuestions> >)M_current);
}


#####################################
void __cdecl CDaTiHD::SendReadyStartDaTiHD(CDaTiHD *const this)
{
  GameService *v1; // rax
  CTimer *v2; // rax
  int32_t Id; // eax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  tm localnow; // [rsp+10h] [rbp-60h] BYREF
  Answer::NetPacket *packet; // [rsp+50h] [rbp-20h]
  int32_t NowSeconds; // [rsp+58h] [rbp-18h]
  int32_t StartSeconds; // [rsp+5Ch] [rbp-14h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_PROC, 0x4E43u);
  if ( packet )
  {
    v2 = Answer::Singleton<CTimer>::instance();
    CTimer::GetLocalNow(&localnow, v2);
    NowSeconds = 60 * localnow.tm_min + 3600 * localnow.tm_hour + localnow.tm_sec;
    StartSeconds = 60 * *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, 0);
    Answer::NetPacket::writeInt32(packet, NowSeconds);
    Answer::NetPacket::writeInt32(packet, StartSeconds);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v5, 0, packet);
  }
}


#####################################
void __cdecl CDaTiHD::SendEndDaTiHD(CDaTiHD *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_PROC, 0x4E45u);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 0);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v3, 0, packet);
  }
}


#####################################
void __cdecl CDaTiHD::SendStartDaTiHD(CDaTiHD *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_PROC, 0x4E44u);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 0);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v3, 0, packet);
  }
}


#####################################
void __cdecl CDaTiHD::SendQuestionsInfo(CDaTiHD *const this, int32_t NowSeconds)
{
  size_t m_DaTiIndex; // rbx
  GameService *v3; // rax
  int32_t QuestionId; // edx
  int8_t AnswerId; // dl
  uint32_t WOffset; // edx
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_DaTiIndex <= 0x1Eu )
  {
    m_DaTiIndex = this->m_DaTiIndex;
    if ( m_DaTiIndex <= std::vector<CfgQuestions>::size(&this->m_QuestionsVct) )
    {
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_PROC, 0x4E46u);
      if ( packet )
      {
        Answer::NetPacket::writeInt8(packet, this->m_DaTiIndex);
        QuestionId = std::vector<CfgQuestions>::operator[](&this->m_QuestionsVct, this->m_DaTiIndex - 1)->QuestionId;
        Answer::NetPacket::writeInt32(packet, QuestionId);
        AnswerId = std::vector<CfgQuestions>::operator[](&this->m_QuestionsVct, this->m_DaTiIndex - 1)->AnswerId;
        Answer::NetPacket::writeInt8(packet, AnswerId);
        Answer::NetPacket::writeInt32(packet, NowSeconds);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacket(v7, 0, packet);
      }
    }
  }
}


#####################################
void __cdecl CDaTiHD::broadcastReady(CDaTiHD *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 132);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CDaTiHD::broadcastStart(CDaTiHD *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 133);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


