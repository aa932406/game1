#include "stdafx.h"
#include "Tencent.h"
#include "GameService.h"
#include "Bag.h"
#include "DataStructs.h"
#include "Player.h"
#include "Timer.h"
#include "OperateLimit.h"

using namespace Answer;

CTencent::CTencent()
	: m_pPlayer(NULL)
{
	InitTables();
}

CTencent::~CTencent()
{
}

void CTencent::InitTables()
{
	static bool bLoaded = false;
	if (bLoaded) return;
	bLoaded = true;

	m_tables.InitYellowRewardTable();
	m_tables.InitYellowDailyRewardTable();
	m_tables.InitYellowLevelRewardTable();
	m_tables.InitBlueRewardTable();
	m_tables.InitBlueDailyRewardTable();
	m_tables.InitBlueLevelRewardTable();
	m_tables.InitQQZoneRewardTable();
	m_tables.InitQQGameRewardTable();
	m_tables.InitTGPRewardTable();
	m_tables.InitTGPDailyRewardTable();
	m_tables.InitTGPLevelRewardTable();
	m_tables.InitTencentSevenDayLoginTable();
}

void CTencent::OnDaySwitch(int32_t nDiffDays)
{
	resetQZoneDailyReward();
	resetQQGameDailyReward();
	SendYellowStoneIcon();
	SendQZoneIcon();
	SendQQGameIcon();
	SendBlueStoneIcon();
	SendSevenDayLoginIcon();
}

void CTencent::GetInterestsProtocol(ProcIdList& procList)
{
	procList.push_back(215);	// CM_QQ_GAME_GIFT
	procList.push_back(216);	// CM_QZONE_GIFT
	procList.push_back(218);	// CM_YELLOW_NEWER_AWARD
	procList.push_back(220);	// CM_YELLOW_DAILY_AWARD
	procList.push_back(219);	// CM_YELLOW_YEAR_AWARD
	procList.push_back(221);	// CM_YELLOW_LEVEL_AWARD
	procList.push_back(223);	// CM_BLUE_AWARD
	procList.push_back(225);	// CM_BLUE_DAILY_AWARD
	procList.push_back(224);	// CM_BLUE_YEAR_AWARD
	procList.push_back(226);	// CM_BLUE_LEVEL_AWARD
	procList.push_back(227);	// CM_BLUE_HIGH_AWARD
	procList.push_back(228);	// CM_RELOAD_TENCENT_INFO
	procList.push_back(235);	// CM_REQUEST_SEVEN_DAY_LOGIN
	procList.push_back(236);	// CM_GET_SEVEN_DAY_LOGIN_REWARD
	procList.push_back(237);	// CM_GET_TGP_AWARD
	procList.push_back(238);	// CM_GET_TGP_DAILY_AWARD
	procList.push_back(239);	// CM_GET_TGP_LEVEL_AWARD
	procList.push_back(240);	// CM_REQUEST_TGP_INFO
}

int32_t CTencent::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket)
{
	if (!inPacket || !m_pPlayer)
	{
		return 10002;
	}

	// Only QQ platform
	if (m_pPlayer->getPf() != "qq")
	{
		return 2;
	}

	switch (nProcId)
	{
	case 215:	return onGetQQGameGift(inPacket);
	case 216:	return onGetQZoneGift(inPacket);
	case 218:	return onGetYellowNewerAward(inPacket);
	case 219:	return onGetYellowDailyAward(inPacket);
	case 220:	return onGetYellowYearAward(inPacket);
	case 221:	return onGetYellowLevelAward(inPacket);
	case 223:	return onGetBlueAward(inPacket);
	case 224:	return onGetBlueDailyAward(inPacket);
	case 225:	return onGetBlueYearAward(inPacket);
	case 226:	return onGetBlueLevelAward(inPacket);
	case 227:	return onGetBlueHighAward(inPacket);
	case 228:	return OnReloadTencentInfo(), 0;
	case 235:	return onRequestSevenDayLoginInfo(inPacket);
	case 236:	return onGetSevenDayLoginReward(inPacket);
	case 237:	return onGetTGPAward(inPacket);
	case 238:	return onGetTGPDailyAward(inPacket);
	case 239:	return onGetTGPLevelAward(inPacket);
	case 240:	return onRequestTGPInfo(inPacket);
	default:	return 0;
	}
}

void CTencent::InitTencentInfo(const TencentInfo* info)
{
	if (info)
	{
		m_info = *info;
	}
}

void CTencent::UpdateTencentInfo(const TencentInfo* info)
{
	if (m_pPlayer && info)
	{
		m_info = *info;
		SendBlueStoneIcon();
		SendBluePayIcon();
		m_pPlayer->setSyncToTeamFlag();
	}
}

void CTencent::OnReloadTencentInfo()
{
	// Reload Tencent info from player DB data
	if (m_pPlayer)
	{
		SendBlueStoneIcon();
		SendYellowStoneIcon();
	}
}

bool CTencent::IsYellowVip() const
{
	return m_info.m_bYellowVip != 0;
}

bool CTencent::IsYellowYearVip() const
{
	return m_info.m_bYellowYearVip != 0;
}

bool CTencent::IsYellowHighVip() const
{
	return m_info.m_bYellowHighVip != 0;
}

int32_t CTencent::GetYellowVipLevel() const
{
	return m_info.m_nYellowVipLevel;
}

bool CTencent::IsBlueVip() const
{
	return m_info.m_bBlueVip != 0;
}

bool CTencent::IsBlueYearVip() const
{
	return m_info.m_bBlueYearVip != 0;
}

bool CTencent::IsBlueHighVip() const
{
	return m_info.m_bBlueHighVip != 0;
}

int32_t CTencent::GetBlueVipLevel() const
{
	return m_info.m_nBlueVipLevel;
}

bool CTencent::isYellowEnter() const
{
	return m_pPlayer && m_pPlayer->getPf() == "qq";
}

bool CTencent::isBlueEnter() const
{
	return m_pPlayer && m_pPlayer->getPf() == "qq";
}

bool CTencent::isTGPEnter() const
{
	return m_pPlayer && m_pPlayer->getPf() == "qq";
}

void CTencent::AppendInfo(Answer::NetPacket* packet)
{
	if (!packet)
	{
		return;
	}

	// Write platform string
	packet->writeUTF8(m_info.m_pf);

	if (isYellowEnter())
	{
		packet->writeInt8(m_info.m_bYellowVip);
		packet->writeInt8(m_info.m_bYellowYearVip);
		packet->writeInt8(m_info.m_bYellowHighVip);
		packet->writeInt8(m_info.m_nYellowVipLevel);
	}
	else if (isBlueEnter())
	{
		packet->writeInt8(m_info.m_bBlueVip);
		packet->writeInt8(m_info.m_bBlueYearVip);
		packet->writeInt8(m_info.m_bBlueHighVip);
		packet->writeInt8(m_info.m_nBlueVipLevel);
	}
	else
	{
		packet->writeInt8(0);
		packet->writeInt8(0);
		packet->writeInt8(0);
		packet->writeInt8(0);
	}
}

std::string CTencent::GetPf() const
{
	return m_info.m_pf;
}

int32_t CTencent::getLoginDay()
{
	if (!m_pPlayer)
	{
		return 0;
	}

	CExtOperateLimit& opLimit = m_pPlayer->GetOperateLimit();
	int32_t nLoginCount = opLimit.GetLimitCount(1011);
	if (nLoginCount > 7)
	{
		return 7;
	}
	return nLoginCount;
}

bool CTencent::isInSevenDay()
{
	return m_pPlayer && TIMER.GetDaysFromStart() - m_pPlayer->getRecord(PR_DAILY_CHECK_LAST_UPDATE) <= 7;
}

bool CTencent::needShowSevenDayIcon()
{
	return m_pPlayer && TIMER.GetDaysFromStart() - m_pPlayer->getRecord(PR_DAILY_CHECK_LAST_UPDATE) <= 8;
}

bool CTencent::IsSevenDayLoginExchangeDay()
{
	if (!m_pPlayer)
	{
		return false;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return false;
	}
	return m_pPlayer->getRecord(PR_DAILY_CHECK_LAST_UPDATE) == 8;
}

bool CTencent::canGetYellowReward()
{
	if (!m_pPlayer)
	{
		return 0;
	}

	int32_t Count = 0;
	if (IsYellowVip() && GetYellowVipLevel() > 0)
	{
		if (!m_pPlayer->getRecord(37000))
			++Count;
		if (!m_pPlayer->getRecord(7000))
			++Count;
	}
	if (IsYellowYearVip() && !m_pPlayer->getRecord(7001))
		++Count;

	// Level gifts check — count remaining unclaimed level gifts (up to 10 levels)
	int32_t nOldRecord = m_pPlayer->getRecord(37001);
	int32_t nLevel = m_pPlayer->getLevel();
	for (int32_t i = 0; i < 10 && i < nLevel; ++i)
	{
		if (!(nOldRecord & (1 << i)))
			++Count;
	}
	if (IsYellowVip() && GetYellowVipLevel() > 0)
	{
		int32_t nVipRecord = m_pPlayer->getRecord(37008);
		for (int32_t i = 0; i < 10 && i < nLevel; ++i)
		{
			if (!(nVipRecord & (1 << i)))
				++Count;
		}
	}
	return Count;
}

bool CTencent::canGetBlueReward()
{
	if (!m_pPlayer)
	{
		return 0;
	}

	if (!IsBlueVip() || GetBlueVipLevel() <= 0)
	{
		return 0;
	}

	int32_t Count = 0;
	if (!m_pPlayer->getRecord(37002))
		++Count;
	if (!m_pPlayer->getRecord(7002))
		++Count;
	if (IsBlueYearVip() && !m_pPlayer->getRecord(7003))
		++Count;
	if (IsBlueHighVip() && !m_pPlayer->getRecord(7004))
		++Count;

	// Blue level gifts check — count remaining unclaimed level gifts (up to 10 levels)
	int32_t nOldRecord = m_pPlayer->getRecord(37003);
	int32_t nLevel = m_pPlayer->getLevel();
	for (int32_t i = 0; i < 10 && i < nLevel; ++i)
	{
		if (!(nOldRecord & (1 << i)))
			++Count;
	}
	return Count;
}

bool CTencent::needShowBluePayIcon()
{
	return std::abs(Answer::DayTime::daydiff(m_info.GetEndTime())) <= 2;
}

// ========== Icon helpers ==========

void CTencent::getYellowStoneIcon(ShowIcon& stu)
{
	stu.nId = 73;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	int32_t bReward = canGetYellowReward();
	if (bReward <= 0)
	{
		stu.nState = 4;
	}
	else
	{
		stu.nState = 2;
		stu.IconRight = bReward;
	}
}

void CTencent::getYellowNewerIcon(ShowIcon& stu)
{
	stu.nId = 172;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	int32_t bReward = canGetYellowReward();
	if (bReward <= 0)
	{
		stu.nState = 2;
	}
	else
	{
		stu.nState = 4;
	}
}

void CTencent::getBlueStoneIcon(ShowIcon& stu)
{
	stu.nId = 75;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	int32_t bReward = canGetBlueReward();
	if (bReward <= 0)
	{
		stu.nState = 4;
	}
	else
	{
		stu.nState = 2;
		stu.IconRight = bReward;
	}
}

void CTencent::getBluePayIcon(ShowIcon& stu)
{
	stu.nId = 77;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	stu.nState = 2; // show
}

void CTencent::getSevenDayLoginIcon(ShowIcon& stu)
{
	stu.nId = 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	stu.nState = 2; // show
}

void CTencent::getTGPIcon(ShowIcon& stu)
{
	stu.nId = 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	stu.nState = 2; // show
}

void CTencent::getQZoneIcon(ShowIcon& stu)
{
	stu.nId = 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	stu.nState = 2; // show
}

void CTencent::getQQGameIcon(ShowIcon& stu)
{
	stu.nId = 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	stu.nState = 2; // show
}

// ========== Icon State List methods ==========

void CTencent::GetYellowStoneIcon(IconStateList& IconList)
{
	if (m_pPlayer && isYellowEnter())
	{
		ShowIcon stu;
		getYellowStoneIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetYellowNewerIcon(IconStateList& IconList)
{
	if (m_pPlayer && isYellowEnter())
	{
		ShowIcon stu;
		getYellowNewerIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetBlueStoneIcon(IconStateList& IconList)
{
	if (m_pPlayer && isBlueEnter())
	{
		ShowIcon stu;
		getBlueStoneIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetBluePayIcon(IconStateList& IconList)
{
	if (m_pPlayer && isBlueEnter())
	{
		ShowIcon stu;
		getBluePayIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetSevenDayLoginIcon(IconStateList& IconList)
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq")
	{
		ShowIcon stu;
		getSevenDayLoginIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetTGPIcon(IconStateList& IconList)
{
	if (m_pPlayer && isTGPEnter())
	{
		ShowIcon stu;
		getTGPIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetFriendIcon(IconStateList& IconList)
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq" && isYellowEnter())
	{
		ShowIcon stu;
		stu.nId = 74;
		stu.nState = 0;
		stu.nLeftTime = 0;
		stu.IconLeft = 0;
		stu.IconRight = 0;
		stu.Effects = 0;
		IconList.push_back(stu);
	}
}

void CTencent::GetQZoneIcon(IconStateList& IconList)
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq" && m_info.m_pf == "qzone")
	{
		ShowIcon stu;
		getQZoneIcon(stu);
		IconList.push_back(stu);
	}
}

void CTencent::GetQQGameIcon(IconStateList& IconList)
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq" && m_info.m_pf == "qqgame")
	{
		ShowIcon stu;
		getQQGameIcon(stu);
		IconList.push_back(stu);
	}
}

// ========== Send Icon methods ==========

void CTencent::sendPlayerIcon(const ShowIcon& stu)
{
	if (!m_pPlayer)
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (!packet)
	{
		return;
	}

	packet->writeInt32(stu.nId);
	packet->writeInt8(stu.nState);
	packet->writeInt32(stu.nLeftTime);
	packet->writeInt8(stu.IconLeft);
	packet->writeInt32(stu.IconRight);
	packet->writeInt8(stu.Effects);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CTencent::SendYellowStoneIcon()
{
	if (m_pPlayer && isYellowEnter())
	{
		ShowIcon stu;
		getYellowStoneIcon(stu);
		sendPlayerIcon(stu);

		ShowIcon stu2;
		getYellowNewerIcon(stu2);
		sendPlayerIcon(stu2);
	}
}

void CTencent::SendYellowNewerIcon()
{
	if (m_pPlayer && isYellowEnter())
	{
		ShowIcon stu;
		getYellowNewerIcon(stu);
		sendPlayerIcon(stu);
	}
}

void CTencent::SendBlueStoneIcon()
{
	if (m_pPlayer && isBlueEnter())
	{
		ShowIcon stu;
		getBlueStoneIcon(stu);
		sendPlayerIcon(stu);

		ShowIcon stu2;
		getBluePayIcon(stu2);
		sendPlayerIcon(stu2);
	}
}

void CTencent::SendBluePayIcon()
{
	if (m_pPlayer && isBlueEnter())
	{
		ShowIcon stu;
		getBluePayIcon(stu);
		sendPlayerIcon(stu);
	}
}

void CTencent::SendSevenDayLoginIcon()
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq")
	{
		ShowIcon stu;
		getSevenDayLoginIcon(stu);
		sendPlayerIcon(stu);
	}
}

void CTencent::SendTGPIcon()
{
	if (m_pPlayer && isTGPEnter())
	{
		ShowIcon stu;
		getTGPIcon(stu);
		sendPlayerIcon(stu);
	}
}

void CTencent::SendQZoneIcon()
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq" && m_info.m_pf == "qzone")
	{
		ShowIcon stu;
		getQZoneIcon(stu);
		sendPlayerIcon(stu);
	}
}

void CTencent::SendQQGameIcon()
{
	if (m_pPlayer && m_pPlayer->getPf() == "qq" && m_info.m_pf == "qqgame")
	{
		ShowIcon stu;
		getQQGameIcon(stu);
		sendPlayerIcon(stu);
	}
}

bool CTencent::checkQQGiftCondition(int8_t nType, int32_t nCondition)
{
	if (!m_pPlayer)
	{
		return false;
	}

	switch (nType)
	{
	case 1: // always available
		return true;
	case 2: // level check
		return m_pPlayer->getLevel() >= nCondition;
	case 3: // daily type
		return true;
	case 4: // login count check
		{
			CExtOperateLimit& opLimit = m_pPlayer->GetOperateLimit();
			return opLimit.GetLimitCount(37007) > 7;
		}
	default:
		return false;
	}
}

// ========== Request handlers ==========

int32_t CTencent::onRequestYellowStoneInfo(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer)
	{
		return 10002;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2822);
	if (!packet)
	{
		return 10002;
	}

	packet->writeInt8((int8_t)m_pPlayer->getRecord(37000));
	packet->writeInt32(m_pPlayer->getRecord(7000));
	packet->writeInt8((int8_t)m_pPlayer->getRecord(7001));
	packet->writeInt32(m_pPlayer->getRecord(37001));
	packet->writeInt32(m_pPlayer->getRecord(37008));
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
	return 0;
}

int32_t CTencent::onRequestBlueStoneInfo(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer)
	{
		return 10002;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2824);
	if (!packet)
	{
		return 10002;
	}

	packet->writeInt8((int8_t)m_pPlayer->getRecord(37002));
	packet->writeInt32(m_pPlayer->getRecord(7002));
	packet->writeInt8((int8_t)m_pPlayer->getRecord(7003));
	packet->writeInt8((int8_t)m_pPlayer->getRecord(7004));
	packet->writeInt32(m_pPlayer->getRecord(37003));
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
	return 0;
}

int32_t CTencent::onGetYellowNewerAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsYellowVip() || GetYellowVipLevel() <= 0)
	{
		return 10002;
	}
	if (m_pPlayer->getRecord(37000))
	{
		return 10002;
	}

	const CfgYellowNewerGift* pGift = m_tables.GetYellowNewerGift();
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_YELLOW_NEWER_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37000, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendYellowStoneIcon();
	return 0;
}

int32_t CTencent::onGetYellowDailyAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsYellowVip())
	{
		return 10002;
	}
	if (m_pPlayer->getRecord(7000))
	{
		return 10002;
	}

	int32_t nLevel = GetYellowVipLevel();
	const CfgYellowDailyGift* pGift = m_tables.GetYellowDailyGift(nLevel);
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	const MemChrBagVector* pReward = IsYellowYearVip() && !pGift->vVipReward.empty()
		? &pGift->vVipReward : &pGift->vReward;
	if (!bag.AddItem(*pReward, IACR_YELLOW_DAILY_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(7000, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendYellowStoneIcon();
	return 0;
}

int32_t CTencent::onGetYellowYearAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsYellowVip() || !IsYellowYearVip())
	{
		return 10002;
	}
	if (m_pPlayer->getRecord(7001))
	{
		return 10002;
	}

	int32_t nLevel = GetYellowVipLevel();
	const CfgYellowDailyGift* pGift = m_tables.GetYellowDailyGift(nLevel);
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_YELLOW_YEAR_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(7001, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendYellowStoneIcon();
	return 0;
}

int32_t CTencent::onGetYellowLevelAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}

	int8_t nIndex = inPacket->readInt8();
	int8_t bVip = inPacket->readInt8();
	if (nIndex < 0)
	{
		return 10002;
	}

	const CfgYellowLevelGift* pGift = m_tables.GetYellowLevelGift(nIndex);
	if (!pGift)
	{
		return 10002;
	}
	if (m_pPlayer->getLevel() < pGift->nMinLevel)
	{
		return 10002;
	}

	int32_t nRecord = 37001;
	if (bVip)
	{
		if (!IsYellowVip() || GetYellowVipLevel() <= 0)
		{
			return 10002;
		}
		nRecord = 37008;
	}

	int32_t nOldRecord = m_pPlayer->getRecord(nRecord);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	const MemChrBagVector* pReward = bVip && !pGift->vVipReward.empty()
		? &pGift->vVipReward : &pGift->vReward;
	if (!bag.AddItem(*pReward, IACR_YELLOW_LEVEL_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(nRecord, nNewRecord);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, nIndex);
	SendYellowStoneIcon();
	return 0;
}

int32_t CTencent::onGetBlueAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsBlueVip() || GetBlueVipLevel() <= 0)
	{
		return 10002;
	}
	if (m_pPlayer->getRecord(37002))
	{
		return 10002;
	}

	const CfgBlueNewerGift* pGift = m_tables.GetBlueNewerGift();
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_BLUE_NEWER_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37002, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendBlueStoneIcon();
	return 0;
}

int32_t CTencent::onGetBlueDailyAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsBlueVip())
	{
		return 10002;
	}
	if (m_pPlayer->getRecord(7002))
	{
		return 10002;
	}

	int32_t nLevel = GetBlueVipLevel();
	const CfgBlueDailyGift* pGift = m_tables.GetBlueDailyGift(nLevel);
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_BLUE_DAILY_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(7002, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendBlueStoneIcon();
	return 0;
}

int32_t CTencent::onGetBlueYearAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsBlueVip() || !IsBlueYearVip())
	{
		return 10002;
	}

	if (m_pPlayer->getRecord(7003))
	{
		return 10002;
	}

	int32_t nLevel = GetBlueVipLevel();
	const CfgBlueYearGift* pGift = m_tables.GetBlueYearGift();
	if (!pGift || pGift->vReward.empty())
	{
		// fallback to daily gift
		const CfgBlueDailyGift* pDaily = m_tables.GetBlueDailyGift(nLevel);
		if (pDaily && !pDaily->vReward.empty())
		{
			CExtCharBag& bag = m_pPlayer->GetBag();
			if (!bag.AddItem(pDaily->vReward, IACR_BLUE_YEAR_REWARD))
			{
				return 10002;
			}
		}
	}
	else
	{
		CExtCharBag& bag = m_pPlayer->GetBag();
		if (!bag.AddItem(pGift->vReward, IACR_BLUE_YEAR_REWARD))
		{
			return 10002;
		}
	}

	m_pPlayer->updateRecord(7003, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendBlueStoneIcon();
	return 0;
}

int32_t CTencent::onGetBlueLevelAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}

	int8_t nIndex = inPacket->readInt8();

	const CfgBlueLevelGift* pGift = m_tables.GetBlueLevelGift(nIndex);
	if (!pGift)
	{
		return 10002;
	}
	if (m_pPlayer->getLevel() < pGift->nMinLevel)
	{
		return 10002;
	}

	int32_t nOldRecord = m_pPlayer->getRecord(37003);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_BLUE_LEVEL_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37003, nNewRecord);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, nIndex);
	SendBlueStoneIcon();
	return 0;
}

int32_t CTencent::onGetBlueHighAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (!IsBlueVip() || !IsBlueHighVip())
	{
		return 10002;
	}
	if (m_pPlayer->getRecord(7004))
	{
		return 10002;
	}

	int32_t nLevel = GetBlueVipLevel();
	const CfgBlueHighGift* pGift = m_tables.GetBlueHighGift();
	if (!pGift || pGift->vReward.empty())
	{
		// fallback to daily gift
		const CfgBlueDailyGift* pDaily = m_tables.GetBlueDailyGift(nLevel);
		if (pDaily && !pDaily->vReward.empty())
		{
			CExtCharBag& bag = m_pPlayer->GetBag();
			if (!bag.AddItem(pDaily->vReward, IACR_BLUE_HIGH_REWARD))
			{
				return 10002;
			}
		}
	}
	else
	{
		CExtCharBag& bag = m_pPlayer->GetBag();
		if (!bag.AddItem(pGift->vReward, IACR_BLUE_HIGH_REWARD))
		{
			return 10002;
		}
	}

	m_pPlayer->updateRecord(7004, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendBlueStoneIcon();
	return 0;
}

int32_t CTencent::onGetQZoneGift(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return 10002;
	}
	if (m_info.m_pf != "qzone")
	{
		return 10002;
	}

	int8_t nIndex = inPacket->readInt8();
	if (nIndex < 0)
	{
		return 10002;
	}

	const CfgQQZoneGift* pGift = m_tables.GetQQZoneGift(nIndex + 1);
	if (!pGift)
	{
		return 10002;
	}
	if (!checkQQGiftCondition(pGift->nType, pGift->nCondition))
	{
		return 10002;
	}

	int32_t nOldRecord = m_pPlayer->getRecord(37006);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_TENCENT_QZONE_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37006, nNewRecord);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, nIndex);
	SendQZoneIcon();
	return 0;
}

int32_t CTencent::onGetQQGameGift(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return 10002;
	}
	if (m_info.m_pf != "qqgame")
	{
		return 10002;
	}

	int8_t nIndex = inPacket->readInt8();
	if (nIndex < 0)
	{
		return 10002;
	}

	const CfgQQGameGift* pGift = m_tables.GetQQGameGift(nIndex + 1);
	if (!pGift)
	{
		return 10002;
	}
	if (!checkQQGiftCondition(pGift->nType, pGift->nCondition))
	{
		return 10002;
	}

	int32_t nOldRecord = m_pPlayer->getRecord(37009);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_TENCENT_QQGAME_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37009, nNewRecord);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, nIndex);
	SendQQGameIcon();
	return 0;
}

int32_t CTencent::onGetTGPAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return 10002;
	}

	if (m_pPlayer->getRecord(37004))
	{
		return 10002;
	}

	const CfgTGPGift* pGift = m_tables.GetTGPGift(m_info.m_pf);
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_TGP_NEWER_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37004, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendTGPIcon();
	return 0;
}

int32_t CTencent::onGetTGPDailyAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return 10002;
	}

	if (m_pPlayer->getRecord(7005))
	{
		return 10002;
	}

	const CfgTGPGift* pGift = m_tables.GetTGPGift(m_info.m_pf);
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_TGP_DAILY_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(7005, 1);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, 0);
	SendTGPIcon();
	return 0;
}

int32_t CTencent::onGetTGPLevelAward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return 10002;
	}

	int8_t nIndex = inPacket->readInt8();
	if (nIndex < 0)
	{
		return 10002;
	}

	const CfgTGPLevelGift* pGift = m_tables.GetTGPLevelGift(nIndex);
	if (!pGift)
	{
		return 10002;
	}
	if (m_pPlayer->getLevel() < pGift->nMinLevel)
	{
		return 10002;
	}

	int32_t nOldRecord = m_pPlayer->getRecord(37005);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_TGP_LEVEL_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37005, nNewRecord);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, nIndex);
	SendTGPIcon();
	return 0;
}

int32_t CTencent::onRequestTGPInfo(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer)
	{
		return 10002;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2825);
	if (!packet)
	{
		return 10002;
	}

	packet->writeInt8((int8_t)m_pPlayer->getRecord(37004));
	packet->writeInt8((int8_t)m_pPlayer->getRecord(7005));
	packet->writeInt32(m_pPlayer->getRecord(37005));
	packet->writeInt32(m_pPlayer->getRecord(37007));
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
	return 0;
}

int32_t CTencent::onRequestSevenDayLoginInfo(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer)
	{
		return 10002;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2826);
	if (!packet)
	{
		return 10002;
	}

	int32_t nLoginDay = getLoginDay();
	packet->writeInt8((int8_t)nLoginDay);
	int32_t nRecord = m_pPlayer->getRecord(37010);
	packet->writeInt32(nRecord);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
	return 0;
}

int32_t CTencent::onGetSevenDayLoginReward(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
	{
		return 10002;
	}

	int8_t nIndex = inPacket->readInt8();
	if (nIndex < 0)
	{
		return 10002;
	}

	const CfgSevenDayLoginGift* pGift = m_tables.GetSevenDayLoginGift(nIndex + 1);
	if (!pGift || pGift->vReward.empty())
	{
		return 10002;
	}

	int32_t nOldRecord = m_pPlayer->getRecord(37010);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
	{
		return 10002;
	}

	CExtCharBag& bag = m_pPlayer->GetBag();
	if (!bag.AddItem(pGift->vReward, IACR_TENCENT_SEVEN_DAY_LOGIN_REWARD))
	{
		return 10002;
	}

	m_pPlayer->updateRecord(37010, nNewRecord);
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), Proc, nIndex);
	SendSevenDayLoginIcon();
	return 0;
}

// ========== Daily reset helpers ==========

void CTencent::resetQZoneDailyReward()
{
	if (!m_pPlayer)
	{
		return;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return;
	}

	// Reset type 3 (daily) gifts in record
	int32_t nRecord = m_pPlayer->getRecord(37006);
	CfgQQZoneGiftMap::const_iterator iter = m_tables.GetQQZoneGiftMap().begin();
	for (; iter != m_tables.GetQQZoneGiftMap().end(); ++iter)
	{
		if (iter->second.nType == 3)
		{
			int32_t nSlot = iter->second.nSlot;
			nRecord &= ~(1 << (nSlot - 1));
		}
	}
	m_pPlayer->updateRecord(37006, nRecord);
}

void CTencent::resetQQGameDailyReward()
{
	if (!m_pPlayer)
	{
		return;
	}
	if (m_pPlayer->getPf() != "qq")
	{
		return;
	}

	// Reset type 3 (daily) gifts in record
	int32_t nRecord = m_pPlayer->getRecord(37009);
	CfgQQGameGiftMap::const_iterator iter = m_tables.GetQQGameGiftMap().begin();
	for (; iter != m_tables.GetQQGameGiftMap().end(); ++iter)
	{
		if (iter->second.nType == 3)
		{
			int32_t nSlot = iter->second.nSlot;
			nRecord &= ~(1 << (nSlot - 1));
		}
	}
	m_pPlayer->updateRecord(37009, nRecord);
}
