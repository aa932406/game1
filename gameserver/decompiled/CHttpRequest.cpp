// Decompiled methods for class: CHttpRequest
// Source: gameserver.cc
// Total methods: 9

#####################################
void __cdecl CHttpRequest::~CHttpRequest(CHttpRequest *const this)
{
  CHttpRequest::~CHttpRequest(this);
  operator delete(this);
}


#####################################
void __cdecl CHttpRequest::run(CHttpRequest *const this)
{
  this->m_bRunning = 1;
  while ( this->m_bRunning )
  {
    CHttpRequest::SendGetRequest(this);
    Answer::DayTime::sleep(100);
  }
}


#####################################
void __cdecl CHttpRequest::Init(CHttpRequest *const this, std::string *p_ip_0, std::string *p_path)
{
  std::string::operator=(&this->m_ServerIp, p_ip_0);
  std::string::operator=(&this->m_ServerPath, p_path);
}


#####################################
void __cdecl CHttpRequest::Stop(CHttpRequest *const this)
{
  this->m_bRunning = 0;
  Answer::Thread::join(this);
}


#####################################
void __cdecl CHttpRequest::SendGetRequest(CHttpRequest *const this)
{
  std::string *v1; // rax
  std::string ReqString; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::string p_param; // [rsp+30h] [rbp-40h] BYREF
  std::string p_path; // [rsp+40h] [rbp-30h] BYREF
  std::string p_ip_0; // [rsp+50h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_GetStringLock);
  while ( !std::list<std::string>::empty(&this->m_lGetReqString) )
  {
    v1 = std::list<std::string>::front(&this->m_lGetReqString);
    std::string::string(&ReqString, v1);
    std::list<std::string>::pop_front(&this->m_lGetReqString);
    std::string::string(&p_param, &ReqString);
    std::string::string(&p_path, &this->m_ServerPath);
    std::string::string(&p_ip_0, &this->m_ServerIp);
    CHttpRequest::sendGetRequest(this, &p_ip_0, 80, &p_path, &p_param);
    std::string::~string(&p_ip_0);
    std::string::~string(&p_path);
    std::string::~string(&p_param);
    std::string::~string(&ReqString);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
std::string __cdecl CHttpRequest::UrlEncode(CHttpRequest *const this, const std::string *const str)
{
  std::string *v2; // rdx
  unsigned __int8 *v3; // rax
  char *v5; // rax
  unsigned __int8 v6; // dl
  signed __int8 v7; // al
  unsigned __int8 v8; // dl
  signed __int8 v9; // al
  std::string *stra; // [rsp+0h] [rbp-50h]
  char v12; // [rsp+1Fh] [rbp-31h] BYREF
  size_t length; // [rsp+20h] [rbp-30h]
  size_t i; // [rsp+28h] [rbp-28h]

  stra = v2;
  std::allocator<char>::allocator(&v12);
  std::string::string(this, &unk_8E0E60);
  std::allocator<char>::~allocator(&v12);
  length = std::string::length(stra);
  for ( i = 0; i < length; ++i )
  {
    v3 = (unsigned __int8 *)std::string::operator[](stra, i);
    if ( isalnum(*v3)
      || *(_BYTE *)std::string::operator[](stra, i) == 45
      || *(_BYTE *)std::string::operator[](stra, i) == 95
      || *(_BYTE *)std::string::operator[](stra, i) == 46
      || *(_BYTE *)std::string::operator[](stra, i) == 126
      || *(_BYTE *)std::string::operator[](stra, i) == 61
      || *(_BYTE *)std::string::operator[](stra, i) == 38 )
    {
      v5 = (char *)std::string::operator[](stra, i);
      std::string::operator+=(this, (unsigned int)*v5);
    }
    else if ( *(_BYTE *)std::string::operator[](stra, i) == 32 )
    {
      std::string::operator+=(this, "+");
    }
    else
    {
      std::string::operator+=(this, 37);
      v6 = (int)*(unsigned __int8 *)std::string::operator[](stra, i) >> 4;
      v7 = CHttpRequest::ToHex((CHttpRequest *const)str, v6);
      std::string::operator+=(this, (unsigned int)v7);
      v8 = *(_BYTE *)std::string::operator[](stra, i) & 0xF;
      v9 = CHttpRequest::ToHex((CHttpRequest *const)str, v8);
      std::string::operator+=(this, (unsigned int)v9);
    }
  }
  return (std::string)this;
}


#####################################
bool __cdecl CHttpRequest::isValidIpAddress(CHttpRequest *const this, const char *ipAddress)
{
  return inet_addr(ipAddress) != -1;
}


#####################################
bool __cdecl CHttpRequest::GetIpByDomainName(CHttpRequest *const this, const char *szHost, char *szIp)
{
  addrinfo hints; // [rsp+20h] [rbp-60h] BYREF
  addrinfo *res; // [rsp+58h] [rbp-28h] BYREF
  addrinfo *cur; // [rsp+60h] [rbp-20h]
  int ret; // [rsp+6Ch] [rbp-14h]

  bzero(&hints, 0x30u);
  hints.ai_family = 2;
  hints.ai_socktype = 1;
  ret = getaddrinfo(szHost, 0, &hints, &res);
  if ( ret == -1 )
    return 0;
  cur = res;
  if ( res )
    inet_ntop(2, &cur->ai_addr->sa_data[2], szIp, 0x10u);
  freeaddrinfo(res);
  return 1;
}


#####################################
void __cdecl CHttpRequest::sendGetRequest(
        CHttpRequest *const this,
        std::string *p_ip_0,
        int port,
        std::string *p_path,
        std::string *p_param)
{
  const char *v5; // rax
  int v6; // ebx
  const char *v7; // rax
  int v8; // ebx
  const char *v9; // rax
  const char *v10; // r12
  const char *v11; // rbx
  const char *v12; // rax
  const char *v13; // rdx
  const char *v14; // rax
  const char *v15; // rcx
  int v16; // ebx
  const char *v17; // rax
  size_t v18; // rax
  int v19; // ebx
  const char *v20; // rax
  char sendBuff[1024]; // [rsp+30h] [rbp-510h] BYREF
  char szIp[208]; // [rsp+430h] [rbp-110h] BYREF
  sockaddr_in ServerAddr1; // [rsp+500h] [rbp-40h] BYREF
  int nNetTimeout; // [rsp+514h] [rbp-2Ch] BYREF
  socket_t clientSocket; // [rsp+518h] [rbp-28h]
  int sendLen; // [rsp+51Ch] [rbp-24h]
  u_long ipLong; // [rsp+520h] [rbp-20h]
  int errNo; // [rsp+52Ch] [rbp-14h]

  clientSocket = socket(2, 1, 0);
  if ( clientSocket == -1 )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "HTTPClient::create socket return INVALID_SOCKET\n");
  }
  else
  {
    nNetTimeout = 5000;
    setsockopt(clientSocket, 1, 21, &nNetTimeout, 4u);
    v5 = (const char *)std::string::c_str(p_path);
    v6 = strlen(v5);
    v7 = (const char *)std::string::c_str(p_param);
    v8 = strlen(v7) + v6;
    v9 = (const char *)std::string::c_str(p_ip_0);
    sendLen = v8 + strlen(v9) + 100;
    if ( std::string::size(p_param) <= 0x320u )
    {
      v10 = (const char *)std::string::c_str(p_ip_0);
      v11 = (const char *)std::string::c_str(p_param);
      v12 = (const char *)std::string::c_str(p_path);
      snprintf(sendBuff, 0x3FFu, "GET /%s?%s HTTP/1.1\r\nHost: %s\r\n\r\n", v12, v11, v10);
      *(_QWORD *)&ServerAddr1.sin_family = 0;
      *(_QWORD *)ServerAddr1.sin_zero = 0;
      ipLong = 0;
      v13 = (const char *)std::string::c_str(p_ip_0);
      if ( CHttpRequest::isValidIpAddress(this, v13) )
      {
        v14 = (const char *)std::string::c_str(p_ip_0);
        ipLong = inet_addr(v14);
      }
      else
      {
        v15 = (const char *)std::string::c_str(p_ip_0);
        CHttpRequest::GetIpByDomainName(this, v15, szIp);
        ipLong = inet_addr(szIp);
      }
      ServerAddr1.sin_addr.s_addr = ipLong;
      ServerAddr1.sin_port = htons(port);
      ServerAddr1.sin_family = 2;
      errNo = connect(clientSocket, (const struct sockaddr *)&ServerAddr1, 0x10u);
      if ( errNo == -1 )
      {
        v16 = *__errno_location();
        v17 = (const char *)std::string::c_str(p_ip_0);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "HTTPClient::connect return SOCKET_ERROR,ip = %s,port=%d errno %d\n",
          v17,
          port,
          v16);
        close(clientSocket);
        clientSocket = -1;
      }
      else
      {
        v18 = strlen(sendBuff);
        if ( send(clientSocket, sendBuff, v18, 0) <= 0 )
        {
          v19 = *__errno_location();
          v20 = (const char *)std::string::c_str(p_ip_0);
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "HTTPClient::send return SOCKET_ERROR,ip = %s,port=%d errno %d\n",
            v20,
            port,
            v19);
        }
        close(clientSocket);
      }
    }
  }
}


