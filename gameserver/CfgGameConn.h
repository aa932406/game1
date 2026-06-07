#ifndef __CFG_GAME_CONN_H__
#define __CFG_GAME_CONN_H__

#include <string>
#include <list>

// 游戏服务器连接配置（DB/Gate）
struct CfgGameConn
{
	CfgGameConn() : port(0) {}
	CfgGameConn(const CfgGameConn& other) : host(other.host), port(other.port) {}
	~CfgGameConn() {}

	CfgGameConn& operator=(const CfgGameConn& other)
	{
		if (this != &other)
		{
			host = other.host;
			port = other.port;
		}
		return *this;
	}

	std::string	host;
	int32_t		port;
};

typedef std::list<CfgGameConn> CfgGameConnList;

#endif // __CFG_GAME_CONN_H__
