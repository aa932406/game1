#include "stdafx.h"

#include "ServiceServer.h"
#include "User.h"


User::User()
{

}

User::~User()
{

}

void User::reset()
{
	m_index = 0;
	m_uid = 0;
	m_sid = 0;
	m_gameConn = NULL;
	m_isGM = false;
	m_lastActiveTick = 0;
	m_isPHP=false;
	m_phpConn =NULL;
	m_autoIncrease = 0;
	m_isInGame = false;
}

int16_t User::getIndex()
{
	return m_index;
}

void User::setIndex(int16_t index)
{
	m_index = index;
}

int32_t User::getUid()
{
	return m_uid;
}

void User::setUid(int32_t uid)
{
	m_uid = uid;
}

int32_t User::getSid()
{
	return m_sid;
}

void User::setSid(int32_t sid)
{
	m_sid = sid;
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


Answer::TcpConnection* User::getGameConn()
{
	return m_gameConn;
}

void User::setGameConn(Answer::TcpConnection *conn)
{
	SERVICE_SERVER.onSwitchGameService(m_gameConn, conn);
	m_gameConn = conn;
}

Answer::TcpConnection* User::getPHPConn()
{
	return m_phpConn;
}
void User::setPHPConn(Answer::TcpConnection *conn)
{
	m_phpConn =conn;
}

bool User::isPHP()
{
	return m_isPHP;
}
void User::setIsPHP(bool isPHP)
{
	m_isPHP =isPHP;
}

bool User::isGM()
{
	return m_isGM;
}

void User::setIsGM(bool isGM)
{
	m_isGM = isGM;
}

bool User::isInGame()
{
	return m_isInGame;
}

void User::setIsInGame(bool isInGame)
{
	m_isInGame = isInGame;
}

bool User::isActive(int64_t nowTick)
{
	return nowTick - m_lastActiveTick <= 10 * 60 * 1000;
}

void User::updateActiveTick()
{
	m_lastActiveTick = Answer::DayTime::tick();
}

bool User::checkAutoIncreaseAndUpdate(int32_t newAutoIncrease)
{
	if (newAutoIncrease <= m_autoIncrease)
	{
		return false;
	}
	int8_t ncount =newAutoIncrease-m_autoIncrease;
	if(ncount !=1)
	{
		return false;
	}
	m_autoIncrease = newAutoIncrease;
	return true;
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