#include "stdafx.h"

#include "User.h"

User::User()
{

}

User::~User()
{

}
void User::init(int32_t uid, int32_t sid)
{
	m_uid = uid;
	m_sid = sid;
}

void User::reset()
{
	m_uid =0;
	m_sid =0;
	m_cid = 0;
	m_player = NULL;
}

CharId_t User::getCid() const
{
	return m_cid;
}

void User::setCid(CharId_t cid)
{
	m_cid = cid;
}
int32_t User::getUid()
{
	return m_uid;
}
int32_t User::getSid()
{
	return m_sid;
}

Player* User::getPlayer()
{
	return m_player;
}

void User::setPlayer(Player *player)
{
	m_player = player;
}

void User::setOpenId(std::string openId)
{
	m_openId = openId;
}

std::string User::getOpenId()
{
	return m_openId;
}

void User::setOpenKey(std::string openKey)
{
	m_openKey = openKey;
}

std::string User::getOpenKey()
{
	return m_openKey;
}

void User::setPf(std::string pf)
{
	m_pf = pf;
}

std::string User::getPf()
{
	return m_pf;
}

void User::setPfKey(std::string pfKey)
{
	m_pfKey = pfKey;
}

std::string User::getPfKey()
{
	return m_pfKey;
}

int32_t User::getIsYellowVip()
{
	return m_is_yellow_vip;
}

void User::setIsYellowVip(int32_t isYellowVip)
{
	m_is_yellow_vip = isYellowVip;
}

int32_t User::getIsYellowYearVip()
{
	return m_is_yellow_year_vip;
}

void User::setIsYellowYearVip(int32_t isYellowYearVip)
{
	m_is_yellow_year_vip = isYellowYearVip;
}

int32_t User::getYellowVipLevel()
{
	return m_yellow_vip_level;
}

void User::setYellowVipLevel(int32_t yellowVipLevel)
{
	m_yellow_vip_level = yellowVipLevel;
}

int32_t User::getIsYellowHighVip()
{
	return m_is_yellow_high_vip;
}

void User::setIsYellowHighVip(int32_t isYellowHighVip)
{
	m_is_yellow_high_vip = isYellowHighVip;
}