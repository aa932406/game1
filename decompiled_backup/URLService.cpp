// Decompiled methods for class: URLService
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl URLService::~URLService(URLService *const this)
{
  URLService::~URLService(this);
  operator delete(this);
}


#####################################
void __cdecl URLService::onNetPacket(URLService *const this, Answer::NetPacket *inPacket)
{
  if ( inPacket )
    Answer::NetPacket::destroy(inPacket);
}


#####################################
void __cdecl URLService::getUrl(URLService *const this, std::string *p_url)
{
  unsigned __int64 v2; // rdx
  URLService *v3; // rax
  bool v4; // bl
  uint32_t WOffset; // eax
  std::string str_http; // [rsp+10h] [rbp-90h] BYREF
  std::string quest; // [rsp+20h] [rbp-80h] BYREF
  std::string hostname; // [rsp+30h] [rbp-70h] BYREF
  std::string filename; // [rsp+40h] [rbp-60h] BYREF
  char v10; // [rsp+4Eh] [rbp-52h] BYREF
  char v11; // [rsp+4Fh] [rbp-51h] BYREF
  std::string v12; // [rsp+50h] [rbp-50h] BYREF
  std::string v13; // [rsp+60h] [rbp-40h] BYREF
  Answer::InetAddress serverAddr; // [rsp+70h] [rbp-30h] BYREF
  int pos1; // [rsp+80h] [rbp-20h]
  int pos2; // [rsp+84h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+88h] [rbp-18h]

  std::string::string(&filename);
  std::string::string(&hostname);
  pos1 = 0;
  pos2 = 0;
  std::allocator<char>::allocator(&v10);
  std::string::string(&quest, "GET ");
  std::allocator<char>::~allocator(&v10);
  std::string::operator+=(&quest, p_url);
  std::string::operator+=(&quest, " HTTP/1.0\r\n");
  std::string::operator+=(&quest, "User-agent:Mozilla/4.0\r\n");
  std::string::operator+=(&quest, "Accept-language:zh-cn\r\n\r\n");
  std::allocator<char>::allocator(&v11);
  std::string::string(&str_http, "http://");
  std::allocator<char>::~allocator(&v11);
  pos1 = std::string::find_first_of(p_url, &str_http, 0);
  pos2 = std::string::find_first_of(p_url, "/", pos1 + 7);
  std::string::substr(&v12, (unsigned __int64)p_url, pos1 + 7);
  std::string::operator=(&hostname, &v12);
  std::string::~string(&v12);
  v2 = std::string::size(p_url);
  pos1 = std::string::find_last_of(p_url, "/", v2);
  std::string::size(p_url);
  std::string::substr(&v13, (unsigned __int64)p_url, pos1 + 1);
  std::string::operator=(&filename, &v13);
  std::string::~string(&v13);
  Answer::InetAddress::InetAddress(&serverAddr, &hostname, 0x50u);
  v3 = Answer::Singleton<URLService>::instance();
  v4 = !Answer::TcpClient::connect(v3, &serverAddr);
  Answer::InetAddress::~InetAddress(&serverAddr);
  if ( !v4 )
  {
    packet = Answer::TcpClient::popNetpacket(this);
    if ( packet )
    {
      Answer::NetPacket::writeUTF8(packet, &quest);
      Answer::NetPacket::setType(packet, Answer::PackType::PACK_PROC);
      Answer::NetPacket::setProc(packet, 0x4E23u);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Answer::TcpClient::sendPacket(this, packet);
    }
  }
  std::string::~string(&str_http);
  std::string::~string(&quest);
  std::string::~string(&hostname);
  std::string::~string(&filename);
}


