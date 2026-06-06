#ifndef __TPOC_HTTP_REQUEST_H__
#define __TPOC_HTTP_REQUEST_H__

#include "share/Shared.h"
#include <string>
#include <list>

class CHttpRequest : public Answer::Thread
{
public:
    CHttpRequest();
    virtual ~CHttpRequest();

    void    Init( const std::string& p_ip, const std::string& p_path );
    void    Stop();
    void    AddGetRequest( const std::string& strReq );

protected:
    virtual void run();

private:
    void    SendGetRequest();
    void    sendGetRequest( const std::string& p_ip, int port, const std::string& p_path, const std::string& p_param );

    std::string UrlEncode( const std::string& str );

    static char ToHex( unsigned char c );

    bool    isValidIpAddress( const char* ipAddress );
    bool    GetIpByDomainName( const char* szHost, char* szIp );

private:
    std::string         m_ServerIp;
    std::string         m_ServerPath;
    std::list<std::string>  m_lGetReqString;
    Answer::Mutex       m_GetStringLock;
    volatile bool       m_bRunning;
};

#endif //__TPOC_HTTP_REQUEST_H__
