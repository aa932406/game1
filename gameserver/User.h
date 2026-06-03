#pragma once

class Player;

class User
{
public:
	User();
	~User();

public:
	void reset();
	void init(int32_t uid, int32_t sid);
	CharId_t getCid() const;
	void setCid(CharId_t cid);
	int32_t getUid();
	int32_t getSid();
	Player* getPlayer();
	void setPlayer(Player *player);

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
	int32_t m_uid;
	int32_t m_sid;
	CharId_t m_cid;
	Player *m_player;

	std::string m_openId;
	std::string m_openKey;
	std::string m_pf;
	std::string m_pfKey;
	int32_t m_is_yellow_vip;
	int32_t m_is_yellow_year_vip;
	int32_t m_yellow_vip_level;
	int32_t m_is_yellow_high_vip;
};

