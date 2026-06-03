#include "stdafx.h"

#include "CharacterUser.h"

Character::Character()
{
	reset();
}

Character::~Character()
{

}

void Character::reset()
{
	m_cid = 0;
	m_name = "";
	m_sex = 0;
	m_style = 0;
	m_head = 0;
	m_job = 0;
	m_level = 0;
	m_mapid = 0;
	m_x = 0;
	m_y = 0;
}

User::User()
{
	reset();
}

User::~User()
{

}

void User::reset()
{
	m_uid = 0;
	m_sid = 0;
	m_fromip = "";
	m_lastLoginTime = 0;
	m_lastLoginIp = "";
	m_characterNum = -1;
	for (int i = 0; i < MAX_CHARACTER_NUM; ++i)
	{
		m_characters[i].reset();
	}
}

