#include "stdafx.h"
#include "URLService.h"

using namespace Answer;
using namespace std;

URLService::URLService()
	: TcpService(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER, 16384-NET_PACKET_HEAD_LEN, 0, 2000, "DBService")
{

}

URLService::~URLService(void)
{
}
void URLService::onNetPacket(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	inPacket->destroy();
}

void URLService::getUrl(string url)
{
	string filename;  
	string hostname;  
	int pos1 = 0;  
	int pos2 = 0;  


	string quest = "GET ";  
	quest += url;  
	quest += " HTTP/1.0\r\n";  
	quest += "User-agent:Mozilla/4.0\r\n";  
	quest += "Accept-language:zh-cn\r\n\r\n";  

	//get the hostname and filename from the word   
	string str_http = "http://";  
	pos1 = url.find_first_of (str_http, 0);  
	pos2 = url.find_first_of ("/", pos1+7);  
	hostname = url.substr( pos1+7, pos2-pos1-7 );  
	pos1 = url.find_last_of( "/", url.size() );  
	filename = url.substr( pos1+1, url.size()-pos1-1 );  
	//连接到gate服务器上
	if (!URL_SERVICE.connect(InetAddress(hostname, 80)))
	{
		//exit(EXIT_FAILURE);
		return;
	}
	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeUTF8(quest);
	packet->setType(PACK_PROC);
	packet->setProc(20003);
	packet->setSize(packet->getWOffset());
	sendPacket(packet);
}

