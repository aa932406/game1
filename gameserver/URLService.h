#pragma once
class URLService :
	public Answer::TcpService
{
public:
	URLService();
	virtual ~URLService();
protected:
	//接收来自db数据包
	virtual void onNetPacket(Answer::NetPacket *inPacket);
public:
	void getUrl(std::string url);
};
#define URL_SERVICE Answer::Singleton<URLService>::instance()
