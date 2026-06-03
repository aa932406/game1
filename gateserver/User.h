#pragma once

#include <string>

class User
{
public:
	User();
	~User();

public:
	void reset();

	int16_t getIndex();
	void setIndex(int16_t index);

	int32_t getUid();
	void setUid(int32_t uid);

	int32_t getSid();
	void setSid(int32_t sid);

	
	Answer::TcpConnection* getGameConn();
	void setGameConn(Answer::TcpConnection *conn);

	Answer::TcpConnection* getPHPConn();
	void setPHPConn(Answer::TcpConnection *conn);

	bool isPHP();
	void setIsPHP(bool isPHP);

	bool isGM();
	void setIsGM(bool isGM);

	bool isInGame();
	void setIsInGame(bool isInGame);

	bool isActive(int64_t nowTick);
	void updateActiveTick();

	bool checkAutoIncreaseAndUpdate(int32_t newAutoIncrease);


	void setOpenId(std::string openId);
	std::string getOpenId();
	void setOpenKey(std::string openKey);
	std::string getOpenKey();
	void setPf(std::string pf);
	std::string getPf();
	void setPfKey(std::string pfKey);
	std::string getPfKey();

	int32_t getIsYellowVip();
	void setIsYellowVip(int32_t isYellowVip);
	int32_t getIsYellowYearVip();
	void setIsYellowYearVip(int32_t isYellowYearVip);
	int32_t getYellowVipLevel();
	void setYellowVipLevel(int32_t yellowVipLevel);
	int32_t getIsYellowHighVip();
	void setIsYellowHighVip(int32_t isYellowHighVip);

private:
	int16_t m_index;
	int32_t m_uid;
	int32_t m_sid;

	Answer::TcpConnection* m_phpConn;
	Answer::TcpConnection *m_gameConn;
	bool m_isGM;
	bool m_isPHP;

	bool m_isInGame;

	int64_t m_lastActiveTick;

	int32_t m_autoIncrease;

	std::string m_openId;
	std::string m_openKey;
	std::string m_pf;
	std::string m_pfKey;

	int32_t m_is_yellow_vip;
	int32_t m_is_yellow_year_vip;
	int32_t m_yellow_vip_level;
	int32_t m_is_yellow_high_vip;
};

