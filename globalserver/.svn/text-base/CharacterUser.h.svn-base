#pragma once

#include <string>

class Character
{
public:
	Character();
	~Character();

public:
	void reset();

public:
	CharId_t m_cid;
	std::string m_name;
	int32_t m_sex;
	int32_t m_style;
	int32_t m_head;

	int32_t m_job;
	int32_t m_level;

	int32_t m_mapid;
	int32_t fight_power;
	int32_t m_x;
	int32_t m_y;
};

class User
{
public:
	User();
	~User();

public:
	void reset();

public:
	int32_t m_uid;
	int32_t m_sid;
	std::string m_fromip;
	int32_t m_lastLoginTime;
	std::string m_lastLoginIp;
	int32_t m_characterNum;
	Character m_characters[MAX_CHARACTER_NUM];
};

