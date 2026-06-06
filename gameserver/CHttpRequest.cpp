#include "CHttpRequest.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

using namespace Answer;

CHttpRequest::CHttpRequest()
    : m_bRunning( false )
{
}

CHttpRequest::~CHttpRequest()
{
    Stop();
}

void CHttpRequest::Init( const std::string& p_ip, const std::string& p_path )
{
    m_ServerIp = p_ip;
    m_ServerPath = p_path;
}

void CHttpRequest::Stop()
{
    m_bRunning = false;
    join();
}

void CHttpRequest::AddGetRequest( const std::string& strReq )
{
    Answer::MutexGuard lock( m_GetStringLock );
    m_lGetReqString.push_back( strReq );
}

void CHttpRequest::run()
{
    m_bRunning = true;
    while ( m_bRunning )
    {
        SendGetRequest();
        Answer::DayTime::sleep( 100 );
    }
}

void CHttpRequest::SendGetRequest()
{
    Answer::MutexGuard lock( m_GetStringLock );

    while ( !m_lGetReqString.empty() )
    {
        std::string ReqString = m_lGetReqString.front();
        m_lGetReqString.pop_front();

        sendGetRequest( m_ServerIp, 80, m_ServerPath, ReqString );
    }
}

void CHttpRequest::sendGetRequest(
    const std::string& p_ip,
    int port,
    const std::string& p_path,
    const std::string& p_param )
{
    int clientSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if ( clientSocket == -1 )
    {
        LOG_ERROR( "HTTPClient::create socket return INVALID_SOCKET\n" );
        return;
    }

    // Set socket timeout
    int nNetTimeout = 5000;
    setsockopt( clientSocket, SOL_SOCKET, SO_SNDTIMEO, &nNetTimeout, sizeof(nNetTimeout) );

    // Build request string
    char sendBuff[1024];
    if ( p_param.size() > 800 )
    {
        close( clientSocket );
        return;
    }

    snprintf( sendBuff, sizeof(sendBuff) - 1,
              "GET /%s?%s HTTP/1.1\r\nHost: %s\r\n\r\n",
              p_path.c_str(), p_param.c_str(), p_ip.c_str() );

    // Resolve IP
    struct sockaddr_in ServerAddr;
    memset( &ServerAddr, 0, sizeof(ServerAddr) );
    u_long ipLong = 0;

    if ( isValidIpAddress( p_ip.c_str() ) )
    {
        ipLong = inet_addr( p_ip.c_str() );
    }
    else
    {
        char szIp[16];
        GetIpByDomainName( p_ip.c_str(), szIp );
        ipLong = inet_addr( szIp );
    }

    ServerAddr.sin_addr.s_addr = ipLong;
    ServerAddr.sin_port = htons( port );
    ServerAddr.sin_family = AF_INET;

    int errNo = connect( clientSocket, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr) );
    if ( errNo == -1 )
    {
        LOG_ERROR( "HTTPClient::connect return SOCKET_ERROR,ip = %s,port=%d errno %d\n",
                   p_ip.c_str(), port, errno );
        close( clientSocket );
        return;
    }

    if ( send( clientSocket, sendBuff, strlen(sendBuff), 0 ) <= 0 )
    {
        LOG_ERROR( "HTTPClient::send return SOCKET_ERROR,ip = %s,port=%d errno %d\n",
                   p_ip.c_str(), port, errno );
    }

    close( clientSocket );
}

std::string CHttpRequest::UrlEncode( const std::string& str )
{
    std::string result;

    for ( size_t i = 0; i < str.length(); ++i )
    {
        unsigned char c = (unsigned char)str[i];
        if ( isalnum( c )
            || c == '-'
            || c == '_'
            || c == '.'
            || c == '~'
            || c == '='
            || c == '&' )
        {
            result += c;
        }
        else if ( c == ' ' )
        {
            result += '+';
        }
        else
        {
            result += '%';
            result += ToHex( c >> 4 );
            result += ToHex( c & 0xF );
        }
    }

    return result;
}

char CHttpRequest::ToHex( unsigned char c )
{
    if ( c <= 9 )
    {
        return '0' + c;
    }
    return 'A' + c - 10;
}




bool CHttpRequest::isValidIpAddress( const char* ipAddress )
{
    return inet_addr( ipAddress ) != INADDR_NONE;
}

bool CHttpRequest::GetIpByDomainName( const char* szHost, char* szIp )
{
    struct addrinfo hints;
    struct addrinfo* res = NULL;

    memset( &hints, 0, sizeof(hints) );
    hints.ai_family = AF_INET;      // IPv4
    hints.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo( szHost, NULL, &hints, &res );
    if ( ret != 0 )
    {
        return false;
    }

    if ( res != NULL )
    {
        struct sockaddr_in* addr = (struct sockaddr_in*)res->ai_addr;
        inet_ntop( AF_INET, &addr->sin_addr, szIp, 16 );
    }

    freeaddrinfo( res );
    return true;
}
