#pragma once

class LoginService
	: public Answer::TcpService
{
public:
	LoginService();
	virtual ~LoginService();

protected:
	virtual void onNetPacket(Answer::NetPacket *inPacket);

private:
	void onUserLogin(int16_t pos, Answer::NetPacket *inPacket);
	//void onUserJoin(int16_t pos, Answer::NetPacket *inPacket);

	void realLogin(int16_t pos, int32_t uid, int32_t sid);
	int registerUser(int16_t pos, const std::string &passport, int32_t sid);
};
#define LOGIN_SERVER Answer::Singleton<LoginService>::instance()
