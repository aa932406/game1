#include "stdafx.h"
#include "Player.h"
#include "Map.h"
#include "MapManager.h"
#include "GameService.h"
#include "DBService.h"
#include "CfgData.h"
#include "ItemHelper.h"
#include "Bag.h"
#include "Equip.h"
#include "Vip.h"
#include "OpenBeta.h"
#include "EquipBack.h"
#include "TileManager.h"
#include "Plant.h"
#include "DropItem.h"
#include "XinMo.h"
#include "ActivityManager.h"
#include "FestivalActivity.h"
#include "Task.h"

// ======== 采集系统 ========

void Player::SetPlantId( EntityId_t PlantId )
{
	m_plantId = PlantId;
	SetNeedSyncAround();
}

EntityId_t Player::GetPlantId()
{
	return m_plantId;
}

void Player::SetStartGather( int64_t CurTick )
{
	m_startGatherTick = CurTick;
}

int64_t Player::GetStartGather()
{
	return m_startGatherTick;
}

void Player::BreakGather( bool IsNotify )
{
	if ( !m_pMap )
		return;

	if ( GetPlantId() > 0 )
	{
		int32_t Err = 0;
		EntityId_t PlantId = GetPlantId();
		Plant* plant = m_pMap->getPlant(PlantId);
		if ( plant )
			Err = plant->onBreakGather(this);
		SetPlantId(0);
		SetStartGather(0);
		if ( IsNotify )
			sendEndGather(Err);
	}
	SetPlantState(0);
}

void Player::sendEndGather( int32_t err )
{
	int8_t connid = getConnId();
	GameService* pService = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pService->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2745);
	if ( packet )
	{
		packet->writeInt32(err);
		packet->setSize(packet->getWOffset());
		pService->sendPacketTo(connid, getGateIndex(), packet);
	}
}

void Player::SetPlantState( bool bState )
{
	bool Change = false;
	if ( bState )
	{
		if ( m_PlantState != 1 )
		{
			m_PlantState = 1;
			Change = true;
		}
	}
	else if ( m_PlantState )
	{
		m_PlantState = 0;
		Change = true;
	}
	if ( Change )
		SetNeedSyncAround();
}

// ======== 网络包处理器 ========

int32_t Player::OnKaiFuHuoDongOperator( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 2;
	// CKaiFuHuoDong* pKaiFu = Answer::Singleton<CKaiFuHuoDong>::instance();
	// return pKaiFu->KaiFuHuoDongOperator(this, inPacket);
	return 0;
}

int32_t Player::OnEquipBackOperator( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 0;

	switch ( inPacket->getProc() )
	{
	case 0x357: // 855 - 金币找回
	{
		CEquipBack* pEB = Answer::Singleton<CEquipBack>::instance();
		return pEB->OnGoldBack(this, inPacket);
	}
	case 0x358: // 856 - 购买找回
	{
		CEquipBack* pEB = Answer::Singleton<CEquipBack>::instance();
		return pEB->OnBuyBack(this, inPacket);
	}
	case 0x359: // 857 - 发送装备找回信息
	{
		CEquipBack* pEB = Answer::Singleton<CEquipBack>::instance();
		pEB->SendEquipBackInfo(this);
		return 0;
	}
	// 0x35E-0x362 (862-866) - 归古岛人相关，暂缺
	default:
		return 2;
	}
}

int32_t Player::OnClickGame( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int32_t Now = getNow();
	int32_t Sid = getSid();
	int64_t Uid = getUid();
	int8_t connid = getConnId();
	DBService* pDB = Answer::Singleton<DBService>::instance();
	pDB->OnDBClickGame(connid, Uid, Sid, Now);
	return 0;
}

int32_t Player::OnOpenBetaOperator( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	GameService* pGS = Answer::Singleton<GameService>::instance();
	if ( pGS->getLine() == 9 )
		return 10002;

	uint16_t Proc = inPacket->getProc();
	if ( Proc == 681 )
	{
		// 请求公测活动信息
		COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
		pOB->SendActivityInfo(this);
		m_CExtFlopDraw.SendFlopRecord(this, 1);
	}
	else if ( Proc == 682 )
	{
		// 公测活动操作
		int8_t Type = inPacket->readInt8();
		COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
		if ( pOB->IsInTime(Type) )
		{
			switch ( Type )
			{
			case 1: // 在线奖励
				pOB->GetOnlineGift(this);
				break;
			case 2: // 充值奖励
				pOB->GetRechargeGift(this);
				break;
			case 3: // 商店
				{
					int8_t nIndex = inPacket->readInt8();
					pOB->BuyShopItem(this, nIndex);
				}
				break;
			case 5: // 翻牌
				{
					int32_t nIndex = inPacket->readInt32();
					pOB->FlopDraw(this, nIndex);
				}
				break;
			case 6: // 礼券
				pOB->GetLiQuan(this);
				break;
			case 7: // 签到
				pOB->GetQianDaoReward(this);
				break;
			case 8: // 烟花
				{
					int8_t nIndex = inPacket->readInt8();
					pOB->GetYanHuaReward(this, nIndex);
				}
				break;
			case 9: // BOSS
				pOB->GetBossGift(this);
				break;
			case 10: // 消费排行
				{
					int8_t nIndex = inPacket->readInt8();
					pOB->GetXiaoFeiRankReward(this, nIndex);
				}
				break;
			case 11: // 每日限购商店
				{
					int32_t nIndex = inPacket->readInt32();
					pOB->BuyDailyLimitShopItem(this, nIndex);
				}
				break;
			default:
				break;
			}
		}
	}
	else if ( Proc == 689 )
	{
		// 国庆等级礼包
		int32_t nLevel = inPacket->readInt32();
		if ( m_CNationalDayHd.BuyLevel(nLevel) )
		{
			uint16_t proc = inPacket->getProc();
			pGS->replySuccess(getConnId(), getGateIndex(), proc, nLevel);
			COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
			pOB->SendIconState(this);
		}
	}
	return 0;
}

int32_t Player::OnFestivalActivityOperator( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CFestivalActivity* pFA = Answer::Singleton<CFestivalActivity>::instance();
	// return pFA->Operator(this, inPacket);
	return 0;
}

int32_t Player::OnSubPkValus( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t BuyCount = inPacket->readInt32();
	if ( BuyCount <= 0 )
		return 10002;

	// 检查消耗
	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	int32_t Cost = pCfg->GetSubPkValueCost(BuyCount);
	if ( Cost <= 0 )
		return 10002;

	if ( !DecCurrency(CURRENCY_GOLD, Cost, GCR_SUB_PK_VALUE) )
		return 10002;

	SubPkValues(10 * BuyCount);

	uint16_t Proc = inPacket->getProc();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->replySuccess(getConnId(), getGateIndex(), Proc, BuyCount);
	return 0;
}

int32_t Player::OnLevelPrison( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	if ( getPkValue() > 99 )
		return 10002;

	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	CfgMapRegion* pCfgRegion = pCfg->getMapRegion(20001);
	if ( !pCfgRegion )
		return 10002;

	int32_t mapid = pCfgRegion->mapid;
	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(mapid);
	if ( !pTargetMap )
		return 10002;

	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
	if ( pos.x < 0 || pos.y < 0 )
		return 10002;

	switchMap(pTargetMap, pos.x, pos.y, 1);
	return 0;
}

// ======== 提示与信息 ========

int32_t Player::GetStartProtect()
{
	return m_StartProtect;
}

void Player::SetStartProtect( int32_t ProtectTime )
{
	m_StartProtect = ProtectTime;
}

int32_t Player::GetProtectTime()
{
	return m_StartProtect;
}

void Player::TiShiInfo( int32_t TiShiId, int32_t Pos )
{
	int8_t connid = getConnId();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2C97);
	if ( packet )
	{
		packet->writeInt32(Pos);
		packet->writeInt32(TiShiId);
		packet->setSize(packet->getWOffset());
		pGS->sendPacketTo(connid, getGateIndex(), packet);
	}
}

// ======== 掉落物品 ========

void Player::onDropItem( Player *pKiller, int32_t Mid )
{
	bool bDropItem = true;
	MemChrBagVector DropItemVt;

	// VIP特权不掉落
	if ( GetPlayerVip().GetVipFlg(1) && getRecord(2061) <= 0 )
		bDropItem = false;

	if ( bDropItem )
	{
		int32_t PkValue = getPkValue();
		CfgData* pCfg = Answer::Singleton<CfgData>::instance();
		PkDropRate* pPkDropRate = pCfg->GetPkDropRate(PkValue);
		if ( pPkDropRate )
		{
			int32_t nEquipRate = pPkDropRate->EquipRate;
			int32_t nUsualRate = pPkDropRate->UsualDropRate;

			CVip& vip = GetPlayerVip();
			if ( vip.GetVipFlg(3) )
				nEquipRate -= 30 * nEquipRate / 100;

			if ( Mid <= 0 )
				GetEquip().GetDropEquip(pKiller, pPkDropRate->EquipCount, nEquipRate, &DropItemVt, Mid);
			GetBag().GetDropItem(pKiller, pPkDropRate, nUsualRate, &DropItemVt, Mid);
		}
	}

	// 心魔背包掉落
	m_CXinMo.DieDropFromXinMoBag(&DropItemVt);

	// 构建掉落组
	DropItemVector dropItems;
	int32_t i = 0;
	int64_t HaveMoney = GetCurrency(CURRENCY_MONEY);
	int64_t DropMoneyCount = 0;

	for ( auto it = DropItemVt.begin(); it != DropItemVt.end() && i <= 120; ++it, ++i )
	{
		if ( it->bind != 1 && it->bind != 2 )
		{
			MemChrBag stu;
			memset(&stu, 0, sizeof(stu));
			stu.itemId = it->itemId;
			stu.itemClass = it->itemClass;
			stu.bind = it->bind;
			stu.itemCount = it->itemCount;
			stu.endTime = it->endTime;
			stu.srcId = it->srcId;
			dropItems.push_back(*(DropItem*)&stu);
		}
	}

	CDropItemGroup pDropItemGroup;
	if ( m_pMap )
	{
		Position CentosPos = getCurrentTile();
		std::string dropper = getName();
		pDropItemGroup.init(getConnId(), m_pMap, &CentosPos, pKiller, 1, 0, &dropItems, &dropper, Mid, 0, 0);
		m_pMap->addDropItemGroup(&pDropItemGroup);
	}
}

// ======== 随机传送/回城 ========

int32_t Player::OnRandPos( int32_t BagSlot )
{
	if ( InDungeon() || InActivity() || IsInStall() )
		return 2;
	if ( HasBuffState(CObjState::OBS_PLYSIS) || HasBuffState(CObjState::OBS_FROZEN) )
		return 10002;

	const Map* pMap = getMap();
	if ( !pMap )
		return 2;
	if ( pMap->GetType() != 1 )
		return 2;

	int32_t MapId = pMap->GetMapId();
	TileManager* pTM = Answer::Singleton<TileManager>::instance();
	Position Pos = pTM->getRandomWalkablePosition(MapId);
	if ( Pos.x == -1 || Pos.y == -1 )
		return 2;

	instantMove(Pos.x, Pos.y, InstanceMoveReason::IMR_SUI_JI, 0);
	GetTask().updateTaskUseItem(7079, 1);
	BreakGather(true);
	return 0;
}

int32_t Player::OnBackCity( int32_t BagSlot )
{
	return OnBackCity(BagSlot, false);
}

int32_t Player::OnBackCity( int32_t BagSlot, bool bXinMo )
{
	if ( !m_pMap || InDungeon() || InActivity() || IsInStall() )
		return 2;

	if ( !bXinMo && (HasBuffState(CObjState::OBS_PLYSIS) || HasBuffState(CObjState::OBS_FROZEN)) )
		return 10002;

	int32_t nMainCity;
	if ( Map::IsXinMoMap(m_pMap) )
	{
		nMainCity = 20003;
	}
	else
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		if ( pGS->getLine() == 9 )
			nMainCity = 20002;
		else
			nMainCity = 20001;
	}

	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	CfgMapRegion* pCfgMapRegion = pCfg->getMapRegion(nMainCity);
	if ( !pCfgMapRegion )
		return 2;

	int32_t mapid = pCfgMapRegion->mapid;
	if ( !pCfg->getMap(mapid) )
		return 2;

	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(pCfgMapRegion->mapid);
	if ( !pTargetMap )
		return 2;

	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgMapRegion);
	if ( pos.x < 0 || pos.y < 0 )
		return 2;

	if ( Map::IsXinMoMap(m_pMap) && bXinMo )
		m_CXinMo.CleanXinMoBag();

	if ( m_pMap == pTargetMap )
		instantMove(pos.x, pos.y, InstanceMoveReason::IMR_BACK_CITY, 0);
	else
		switchMap(pTargetMap, pos.x, pos.y, 1);

	GetTask().updateTaskCount(25, 0);
	m_isBackCity = 0;
	return 0;
}

void Player::BroadcastYanHua( int32_t nType )
{
	if ( !m_pMap )
		return;

	Direction dir = getDirection();
	Position CurrentTile = getCurrentTile();
	Position tartile = Map::GetDirTileByDistance(m_pMap, CurrentTile, dir, 2);

	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(Answer::PackType::PACK_DISPATCH, 0x2829);
	if ( packet )
	{
		CharId_t cid = getCid();
		packet->writeInt64(cid);
		packet->writeInt32(nType);
		packet->writeInt32(tartile.x);
		packet->writeInt32(tartile.y);
		packet->setSize(packet->getWOffset());
		m_pMap->broadcastAreaAround(packet, this);
	}
}

// ======== Boss Home / VIP 挂机 ========

int32_t Player::OnEnterBossHome( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	if ( !m_pMap || InDungeon() || InActivity() )
		return 10002;

	int32_t MapId = inPacket->readInt32();
	SendBossHomeInfo(MapId);
	return 0;
}

int32_t Player::OnLevelBossHome( Answer::NetPacket *inPacket )
{
	return LevelBossHome();
}

int32_t Player::LevelBossHome()
{
	if ( m_InBossHomeTime > 0 )
	{
		m_InBossHomeTime = 0;
		// 回城
		CfgData* pCfg = Answer::Singleton<CfgData>::instance();
		CfgMapRegion* pCfgRegion = pCfg->getMapRegion(20001);
		if ( pCfgRegion )
		{
			MapManager* pMM = Answer::Singleton<MapManager>::instance();
			Map* pTargetMap = pMM->GetMap(pCfgRegion->mapid);
			if ( pTargetMap )
			{
				Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
				if ( pos.x >= 0 && pos.y >= 0 )
					switchMap(pTargetMap, pos.x, pos.y, 1);
			}
		}
	}
	return 0;
}

void Player::SendBossHomeInfo( int32_t MapId )
{
	// 发送Boss之家信息给客户端
	int8_t connid = getConnId();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x29DC);
	if ( packet )
	{
		packet->writeInt32(MapId);
		packet->writeInt32(m_InBossHomeTime);
		packet->setSize(packet->getWOffset());
		pGS->sendPacketTo(connid, getGateIndex(), packet);
	}
}

int32_t Player::OnEnterVipGuaJiMap( Answer::NetPacket *packet )
{
	if ( !packet )
		return 10002;
	if ( !m_pMap || InDungeon() || InActivity() || IsInStall() )
		return 10002;

	// 检查VIP等级
	CVip& vip = GetPlayerVip();
	int32_t VipLevel = vip.GetVipLevel();
	if ( VipLevel < 3 )
		return 10002;

	// 进入VIP挂机地图
	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	CfgMapRegion* pCfgRegion = pCfg->getMapRegion(20004); // VIP挂机地图区域ID
	if ( !pCfgRegion )
		return 10002;

	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(pCfgRegion->mapid);
	if ( !pTargetMap )
		return 10002;

	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
	if ( pos.x < 0 || pos.y < 0 )
		return 10002;

	switchMap(pTargetMap, pos.x, pos.y, 1);
	return 0;
}

void Player::LeaveVipGuaJiMap()
{
	// 离开VIP挂机地图，回主城
	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	CfgMapRegion* pCfgRegion = pCfg->getMapRegion(20001);
	if ( !pCfgRegion )
		return;

	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(pCfgRegion->mapid);
	if ( !pTargetMap )
		return;

	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
	if ( pos.x >= 0 && pos.y >= 0 )
		switchMap(pTargetMap, pos.x, pos.y, 1);
}

// ======== 魔灵入侵 ========

int32_t Player::OnEnterMoLingRuQin( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	if ( !m_pMap || InDungeon() || InActivity() || IsInStall() )
		return 10002;

	// 魔灵入侵活动地图
	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	CfgMapRegion* pCfgRegion = pCfg->getMapRegion(20005);
	if ( !pCfgRegion )
		return 10002;

	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(pCfgRegion->mapid);
	if ( !pTargetMap )
		return 10002;

	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
	if ( pos.x < 0 || pos.y < 0 )
		return 10002;

	switchMap(pTargetMap, pos.x, pos.y, 1);
	return 0;
}

// ======== PK系统 ========

bool Player::SubPkValues( int32_t Addon )
{
	if ( getPkValue() <= 0 )
		return false;
	if ( Addon <= 0 )
		return false;
	addPkValue(-Addon);
	return true;
}

// ======== 充值处理 ========

void Player::PayedDispose( int32_t AddGold )
{
	int32_t TodayPayGold = GetTodayPayGold();

	// 月抽奖
	m_CMonthlyChouJiang.OnChongZhi(AddGold + TodayPayGold, TodayPayGold);

	// 跨服充值
	// CKiaFuRecharge::OnRecharge(this, GetTodayPayGold(), AddGold);

	// 双十一充值
	// CFestivalDoubleEleven::OnRecharge(this, GetTodayPayGold(), AddGold);

	// 国庆
	int32_t totalPay = AddGold + GetTodayPayGold();
	m_CNationalDayHd.AddNationalValue(NATIONAL_HD_TYPE::HHT_RECHARGE, TodayPayGold, totalPay);

	// 联合服务器
	// CUniteServer::OnRecharge(this, AddGold);

	// 运营活动累计充值
	GetPlayerYunYingHd().AddTotalChongZhiCount(AddGold);

	// 操作限制
	GetOperateLimit().AddLimitCount(2026, AddGold);

	// 超级会员充值
	GetPlayerYunYingHd().SuperMemberRecharge(AddGold);

	// 每日充值图标
	GetPlayerYunYingHd().SendEveryDayChongZhiIcon(3);
	GetPlayerYunYingHd().SendEveryDayChongZhiIcon(2);

	// 双十一充值记录+图标
	// CFestivalDoubleEleven::AddRechargeRecord(this, AddGold);
	// CFestivalDoubleEleven::SendIconState(this);

	// 联合服务器图标
	// CUniteServer::SendIconState(this);

	// 综合运营
	// CZongHeYunYingHD::OnRecharge(this, AddGold);

	// 公测图标
	COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
	pOB->SendIconState(this);

	// 开服活动图标
	// CKaiFuHuoDong::SendKaiFuHuoDongIcon(this);

	// 月抽奖图标
	m_CMonthlyChouJiang.SendIcon();
	m_CMonthlyChouJiang.SendMonthlyChouJiangInfo();

	// 奖励大厅图标
	GetPlayerDailyActivity().SendJiangLiDaTingIcon();

	// VIP经验
	GetPlayerVip().AddVipExp(AddGold);

	// 活跃度
	GetPlayerHuoYueDu().AddHuoYueDuRecord(8, AddGold, 0);
}

// ======== 升级 ========

void Player::LevelUped()
{
	int32_t OldLevel = m_levelStartTime; // 简化：使用旧等级
	int32_t NewLevel = getLevel();
	LevelUped(OldLevel, NewLevel);
}

void Player::LevelUped( int32_t OldLevel, int32_t NewLevel )
{
	// 日志
	int8_t ConnId = getConnId();
	DBService* pDB = Answer::Singleton<DBService>::instance();
	// DBService::AddPlatformLog(pDB, ConnId, PLDT_LEVEL_UP, &stu);

	SetLvelStartTime();

	// 日常活动升级
	GetPlayerDailyActivity().OnLevelUp();

	// 功能开放检查
	CFunctionOpen::CheckFunctionOpne(&m_PlayerFunctionOpen, 0, NewLevel);
	CFunctionOpen::CheckFunctionOpenMailByLevel(&m_PlayerFunctionOpen, NewLevel);

	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	int32_t ServerDiffDay = pCfg->getServerDiffDay(SERVER_TYPE::SVT_NORMAL);
	CFunctionOpen::CheckFunctionOpenMailByKaiFuDay(&m_PlayerFunctionOpen, ServerDiffDay + 1);

	// 投资图标
	GetPlayerGetTouZi().SendTouZiIcon();

	// 称号升级
	GetCharTitle().OnLevelUp(NewLevel);

	// 宠物升级
	GetCharPet().OnLevelUp();

	// V计划
	m_extVplan.sendSwVipIcon();

	// 大厅奖励
	m_DaTingReward.SendDaTingIcon();

	// 命格
	m_CMingGeExt.OnLevelUp(NewLevel);

	// 勋章升级
	GetPlayerGuanWei().OnLevelUp(NewLevel);

	// 开服活动
	// CKaiFuHuoDong::OnLevelUp(this, NewLevel);

	// 腾讯信息
	// m_extCharTencent.SendTGPIcon();
	// m_extCharTencent.SendBlueStoneIcon();

	// 公测图标
	COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
	pOB->SendIconState(this);

	// 活跃度
	GetPlayerHuoYueDu().OnLevelUp();

	// 开服天数
	int32_t KaiFuDay = pCfg->getServerDiffDay(SERVER_TYPE::SVT_NORMAL) + 1;
	m_SevenDayTask.OnLevelUp(NewLevel, KaiFuDay);

	// 奖励大厅
	GetPlayerDailyActivity().SendJiangLiDaTingIcon();

	// 经验球
	GetExpBall().OnLevelUp(NewLevel);

	// 更新属性
	RecalcAttr();
}

void Player::SetLvelStartTime()
{
	m_levelStartTime = getNow();
}

// ======== 附加属性 ========

void Player::AddAppendAttr()
{
	// 追加属性1 - record 1066 检查
	int32_t Record = getRecord(1066);
	if ( Record > getNow() )
	{
		AddAttrList AddAttr;
		CfgData* pCfg = Answer::Singleton<CfgData>::instance();
		pCfg->GetAppendAttr(AddAttr, 1);
		for ( auto it = AddAttr.begin(); it != AddAttr.end(); ++it )
		{
			AddAttrValue(it->m_nAddAttrType, it->m_nAddAttrValue);
		}
	}

	// 跨服爬塔冠军属性
	GameService* pGS = Answer::Singleton<GameService>::instance();
	if ( pGS->getLine() != 9 )
	{
		CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
		if ( pAM && pAM->GetCrossTowerWinner() )
		{
			AddAttrList AddAttr;
			CfgData* pCfg = Answer::Singleton<CfgData>::instance();
			pCfg->GetAppendAttr(AddAttr, 3);
			for ( auto it = AddAttr.begin(); it != AddAttr.end(); ++it )
			{
				AddAttrValue(it->m_nAddAttrType, it->m_nAddAttrValue);
			}
		}
	}

	// 公测追加属性
	COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
	pOB->GetAppendAttr(this);

	// 其他追加属性...
}

// ======== 经验倍率 ========

void Player::AddExpRate( int32_t AddValue )
{
	m_ExpRate += AddValue;
}

int32_t Player::GetExpRate()
{
	return m_ExpRate;
}

// ======== PK值相关 ========

int32_t Player::OnSubPkValus( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t BuyCount = inPacket->readInt32();
	if ( BuyCount <= 0 )
		return 10002;

	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	int32_t Cost = pCfg->GetSubPkValueCost(BuyCount);
	if ( Cost <= 0 )
		return 10002;

	if ( !DecCurrency(CURRENCY_GOLD, Cost, GCR_SUB_PK_VALUE) )
		return 10002;

	SubPkValues(10 * BuyCount);

	uint16_t Proc = inPacket->getProc();
	GameService* pGS2 = Answer::Singleton<GameService>::instance();
	pGS2->replySuccess(getConnId(), getGateIndex(), Proc, BuyCount);
	return 0;
}

// ======== 技能检查 ========

bool Player::HasSkill( int32_t SkillId )
{
	for ( auto it = m_skills.begin(); it != m_skills.end(); ++it )
	{
		if ( it->skillId == SkillId )
			return true;
	}
	return false;
}

// ======== 满血恢复 ========

int32_t Player::OnAskLastFullHpTime( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int8_t ConnId = getConnId();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(ConnId, Answer::PackType::PACK_DISPATCH, 0x2CB8);
	if ( !packet )
		return 10002;

	int32_t Record = getRecord(1067);
	packet->writeInt32(Record);
	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(ConnId, getGateIndex(), packet);
	return 0;
}

int32_t Player::OnFullHp( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t Now = getNow();
	int32_t LastTime = getRecord(1067);
	// 检查CD时间
	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	int32_t CD = pCfg->GetFullHpCD();
	if ( Now - LastTime < CD )
		return 10002;

	// 恢复满血
	updateRecord(1067, Now);
	// 回复HP逻辑...
	return 0;
}

// ======== PPTick ========

void Player::SetPPTick( int64_t CurTick )
{
	m_LastAddPPTick = CurTick;
}

// ======== 系统设置 ========

bool Player::GetSysSettingInfo( int32_t Index )
{
	auto it = m_SystemSetting.find(Index);
	if ( it != m_SystemSetting.end() )
		return it->second != 0;
	return false;
}

void Player::InitSysSetting()
{
	// 初始化系统设置
}

std::string Player::GetSysSetting()
{
	std::string result;
	for ( auto it = m_SystemSetting.begin(); it != m_SystemSetting.end(); ++it )
	{
		// 格式化设置
	}
	return result;
}

// ======== 跨服/运营相关 ========

int32_t Player::OnUniteServerRequestInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CUniteServer::SendUniteServerInfo(this);
	return 0;
}

int32_t Player::OnUniteServerGetRechargeGift( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int8_t nIndex = inPacket->readInt8();
	// if ( CUniteServer::GetRechargeGift(this, nIndex) )
	// 	return 10002;
	// uint16_t Proc = inPacket->getProc();
	// GameService::replySuccess(getConnId(), getGateIndex(), Proc, nIndex);
	return 0;
}

int32_t Player::OnDoubleElevenRequestInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CFestivalDoubleEleven::SendInfo(this);
	return 0;
}

int32_t Player::OnZHYYHDRequestInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CZHYYHD::SendInfo(this);
	return 0;
}

int32_t Player::OnZHYYHDGetRechargeDailyReward( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CZHYYHD::GetRechargeDailyReward(this, inPacket);
	return 0;
}

int32_t Player::OnZHYYHDGetRechargeTeamShopDailyReward( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CZHYYHD::GetRechargeTeamShopDailyReward(this, inPacket);
	return 0;
}

int32_t Player::OnZHYYHDBuyOnceShopItem( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CZHYYHD::BuyOnceShopItem(this, inPacket);
	return 0;
}

int32_t Player::OnGetKaiFuREcharge( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CKaiFuHuoDong::GetRecharge(this, inPacket);
	return 0;
}

int32_t Player::OnGetKaiFuChouJiang( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// CKaiFuHuoDong::GetChouJiang(this, inPacket);
	return 0;
}

int32_t Player::OnRequestMoYuShiJieRecord( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->SendMoYuShiJieRecord(this);
	return 0;
}

int32_t Player::OnFengHao( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 封号系统
	return 0;
}

int32_t Player::OnSetFcmTime( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 防沉迷时间设置
	return 0;
}

int32_t Player::OnCheckAccelerator( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 加速器检测
	return 0;
}

int32_t Player::OnGetMiniClientReward( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 微端奖励
	return 0;
}

int32_t Player::OnGetMapBossInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 地图Boss信息
	return 0;
}

int32_t Player::OnGetLevelBossInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 等级Boss信息
	return 0;
}

int32_t Player::OnPaiMaiHangHanHua( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 拍卖行喊话
	return 0;
}

int32_t Player::OnEnterSpecialBossMap( Answer::NetPacket *inPacket )
{
	if ( !m_pMap || !inPacket )
		return 10002;
	if ( InDungeon() || InActivity() )
		return 10002;

	int32_t nMapId = inPacket->readInt32();
	int32_t nPosX = inPacket->readInt32();
	int32_t nPosY = inPacket->readInt32();

	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTarMap = pMM->GetMap(nMapId);
	if ( !pTarMap )
		return 10002;

	// 检查是否可进入
	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	SpecialBossMapCfg* pCfgSB = pCfg->GetSpecialBossMapCfg(nMapId);
	if ( !pCfgSB )
		return 10002;

	// 检查地图是否可走
	if ( !pTarMap->isWalkablePosition(nPosX, nPosY) )
		return 10002;

	// 进入地图
	switchMap(pTarMap, nPosX, nPosY, 1);
	return 0;
}

int32_t Player::OnLeaveSpecialBossMap( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 离开特殊Boss地图，回主城
	OnBackCity(0, false);
	return 0;
}

int32_t Player::OnRollTheDice( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 掷骰子
	return 0;
}

int32_t Player::OnCycleTowerEvent( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 循环塔事件
	return 0;
}

int32_t Player::ChatValidateed( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->CheckChatValidateChatSend(this, inPacket);
	return 0;
}

int32_t Player::onBuyXuWuValue( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 购买虚无值
	return 0;
}

int32_t Player::OnChristmasDuiHuan( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 圣诞兑换
	return 0;
}

int32_t Player::onDungeonRandom( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 副本随机
	return 0;
}

int32_t Player::OnBuyRandomPosTimes( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 购买随机传送次数
	return 0;
}

int32_t Player::OnBuyJingLiValue( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 购买精力值
	return 0;
}

int32_t Player::onComBackCity( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	return OnBackCity(0, false);
}

int32_t Player::onDungeonNpc( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 副本NPC交互
	return 0;
}

int32_t Player::OnActivityWorldBossGuWu( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 世界Boss鼓舞
	return 0;
}

int32_t Player::OnActivityApplyCityWar( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 申请城战
	return 0;
}

int32_t Player::OnRequestActivityRankInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	// 请求活动排行
	return 0;
}

// ======== 扩展 initNetPacketHandlers ========

void Player::initNetPacketHandlers2019()
{
	// 开服活动
	setNetPacketHandler(495, (NetPacketHandler)OnKaiFuHuoDongOperator);
	setNetPacketHandler(496, (NetPacketHandler)OnKaiFuHuoDongOperator);
	setNetPacketHandler(497, (NetPacketHandler)OnKaiFuHuoDongOperator);
	setNetPacketHandler(498, (NetPacketHandler)OnKaiFuHuoDongOperator);

	// 世界Boss鼓舞
	setNetPacketHandler(835, (NetPacketHandler)OnActivityWorldBossGuWu);

	// PK值
	setNetPacketHandler(527, (NetPacketHandler)OnSubPkValus);
	setNetPacketHandler(528, (NetPacketHandler)OnLevelPrison);

	// 联合服务器
	setNetPacketHandler(870, (NetPacketHandler)OnUniteServerRequestInfo);
	setNetPacketHandler(871, (NetPacketHandler)OnUniteServerGetRechargeGift);
	setNetPacketHandler(872, (NetPacketHandler)OnUniteServerBuyDistinctGift);
	setNetPacketHandler(873, (NetPacketHandler)OnUniteServerHuoYueduGift);
	setNetPacketHandler(869, (NetPacketHandler)OnUniteBuyChangeNameCard);
	setNetPacketHandler(868, (NetPacketHandler)OnGetUniteWingLevelUpReward);
	setNetPacketHandler(887, (NetPacketHandler)OnUniteServerGetLianRechargeGift);
	setNetPacketHandler(888, (NetPacketHandler)OnUniteServerGetChouJiangTimesReward);

	// 开服充值/抽奖
	setNetPacketHandler(846, (NetPacketHandler)OnGetKaiFuREcharge);
	setNetPacketHandler(847, (NetPacketHandler)OnGetKaiFuChouJiang);

	// 双十一
	setNetPacketHandler(900, (NetPacketHandler)OnDoubleElevenRequestInfo);
	setNetPacketHandler(901, (NetPacketHandler)OnDoubleElevenGetLandGift);
	setNetPacketHandler(902, (NetPacketHandler)OnDoubleElevenGetDrawGift);
	setNetPacketHandler(907, (NetPacketHandler)OnDoubleElevenGetOnlineGift);
	setNetPacketHandler(908, (NetPacketHandler)OnDoubleElevenGetWishGift);
	setNetPacketHandler(903, (NetPacketHandler)OnDoubleElevenGetLandSumGift);
	setNetPacketHandler(904, (NetPacketHandler)OnDoubleElevenBuyDailyLimitShopItem);
	setNetPacketHandler(905, (NetPacketHandler)OnDoubleElevenGetHuoYueDuSumGift);
	setNetPacketHandler(909, (NetPacketHandler)OnDoubleElevenGetDailyRechargeGift);
	setNetPacketHandler(973, (NetPacketHandler)OnDoubleElevenGetRechargeSumGift);
	setNetPacketHandler(978, (NetPacketHandler)OnDoubleElevenGetPetIllusionItemGift);
	setNetPacketHandler(972, (NetPacketHandler)OnDoubleElevenGetXiaoFeiSumGift);
	setNetPacketHandler(970, (NetPacketHandler)OnDoubleElevenBuyGiftShopItem);
	setNetPacketHandler(971, (NetPacketHandler)OnDoubleElevenGetFaBaoCritBackItem);
	setNetPacketHandler(974, (NetPacketHandler)OnDoubleElevenBuyGiftShopItem2);
	setNetPacketHandler(976, (NetPacketHandler)OnDoubleElevenBuyGiftItem);
	setNetPacketHandler(975, (NetPacketHandler)OnDoubleElevenGetEquipUpStarBackItem);
	setNetPacketHandler(260, (NetPacketHandler)OnDoubleElevenBuyPetGift);
	setNetPacketHandler(540, (NetPacketHandler)OnFengHao);
	setNetPacketHandler(977, (NetPacketHandler)OnDoubleElevenGetRechargeBack);
	setNetPacketHandler(985, (NetPacketHandler)OnDoubleElevenGetEquipQingYiGift);
	setNetPacketHandler(986, (NetPacketHandler)OnDoubleElevenGetFriendQingYiGift);
	setNetPacketHandler(988, (NetPacketHandler)OnDoubleElevenRandScoreDrawGift);
	setNetPacketHandler(989, (NetPacketHandler)OnDoubleElevenRandGouWuChe);
	setNetPacketHandler(983, (NetPacketHandler)OnGetLianRechargeReward);

	// 魔域世界记录
	setNetPacketHandler(845, (NetPacketHandler)OnRequestMoYuShiJieRecord);

	// 防沉迷
	setNetPacketHandler(541, (NetPacketHandler)OnSetFcmTime);

	// 副本NPC/回城
	setNetPacketHandler(990, (NetPacketHandler)onDungeonNpc);
	setNetPacketHandler(991, (NetPacketHandler)onComBackCity);

	// 加速检测
	setNetPacketHandler(624, (NetPacketHandler)OnCheckAccelerator);

	// 综合运营
	setNetPacketHandler(661, (NetPacketHandler)OnZHYYHDRequestInfo);
	setNetPacketHandler(662, (NetPacketHandler)OnZHYYHDGetRechargeDailyReward);
	setNetPacketHandler(663, (NetPacketHandler)OnZHYYHDGetRechargeTeamShopDailyReward);
	setNetPacketHandler(664, (NetPacketHandler)OnZHYYHDBuyOnceShopItem);

	// 公测活动
	setNetPacketHandler(681, (NetPacketHandler)OnOpenBetaOperator);
	setNetPacketHandler(682, (NetPacketHandler)OnOpenBetaOperator);
	setNetPacketHandler(689, (NetPacketHandler)OnOpenBetaOperator);

	// 节日活动
	setNetPacketHandler(683, (NetPacketHandler)OnFestivalActivityOperator);
	setNetPacketHandler(684, (NetPacketHandler)OnFestivalActivityOperator);

	// 装备找回
	setNetPacketHandler(855, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(856, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(857, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(865, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(866, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(862, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(863, (NetPacketHandler)OnEquipBackOperator);
	setNetPacketHandler(864, (NetPacketHandler)OnEquipBackOperator);

	// 满血/微端
	setNetPacketHandler(669, (NetPacketHandler)OnAskLastFullHpTime);
	setNetPacketHandler(670, (NetPacketHandler)OnFullHp);
	setNetPacketHandler(513, (NetPacketHandler)OnGetMiniClientReward);

	// Boss信息
	setNetPacketHandler(205, (NetPacketHandler)OnGetMapBossInfo);
	setNetPacketHandler(204, (NetPacketHandler)OnGetLevelBossInfo);

	// 拍卖行喊话
	setNetPacketHandler(680, (NetPacketHandler)OnPaiMaiHangHanHua);

	// 特殊Boss地图
	setNetPacketHandler(207, (NetPacketHandler)OnEnterSpecialBossMap);
	setNetPacketHandler(208, (NetPacketHandler)OnLeaveSpecialBossMap);

	// 掷骰子/循环塔
	setNetPacketHandler(561, (NetPacketHandler)OnRollTheDice);
	setNetPacketHandler(562, (NetPacketHandler)OnCycleTowerEvent);

	// 聊天验证/虚无值
	setNetPacketHandler(563, (NetPacketHandler)ChatValidateed);
	setNetPacketHandler(564, (NetPacketHandler)onBuyXuWuValue);

	// 点击游戏
	setNetPacketHandler(480, (NetPacketHandler)OnClickGame);

	// 城战
	setNetPacketHandler(839, (NetPacketHandler)OnActivityApplyCityWar);
	setNetPacketHandler(836, (NetPacketHandler)OnRequestActivityRankInfo);

	// 圣诞/副本随机/传送
	setNetPacketHandler(982, (NetPacketHandler)OnChristmasDuiHuan);
	setNetPacketHandler(937, (NetPacketHandler)onDungeonRandom);
	setNetPacketHandler(938, (NetPacketHandler)OnBuyRandomPosTimes);
	setNetPacketHandler(939, (NetPacketHandler)OnBuyJingLiValue);

	// 跨服包转发
	setNetPacketHandler(996, (NetPacketHandler)onTeleportByItem);
	setNetPacketHandler(995, (NetPacketHandler)onSwitchMap);
	setNetPacketHandler(994, (NetPacketHandler)onMove);

	// 副本相关
	setNetPacketHandler(790, (NetPacketHandler)onDungeonBuildTower);
	setNetPacketHandler(792, (NetPacketHandler)onDungeonBuyTower);
	setNetPacketHandler(791, (NetPacketHandler)onDungeonStart);
	setNetPacketHandler(796, (NetPacketHandler)onDungeonSummonBoss);
	setNetPacketHandler(793, (NetPacketHandler)onBuyDungeonEnterTime);
	setNetPacketHandler(797, (NetPacketHandler)onDungeonSummon);
	setNetPacketHandler(795, (NetPacketHandler)onDungeonQuickDone);
	setNetPacketHandler(23, (NetPacketHandler)onDungeonSaoDang);
	setNetPacketHandler(24, (NetPacketHandler)onDungeonReset);
	setNetPacketHandler(27, (NetPacketHandler)onGuessTheSize);
	setNetPacketHandler(352, (NetPacketHandler)onEnterChargeDungeon);
	setNetPacketHandler(76, (NetPacketHandler)onDungeonYJSKGuWu);

	// 活动
	setNetPacketHandler(32, (NetPacketHandler)onActivityChangeMap);
	setNetPacketHandler(33, (NetPacketHandler)onFamilyWarActivePillar);
	setNetPacketHandler(47, (NetPacketHandler)onSpecialPlant);

	// 聊天
	setNetPacketHandler(194, (NetPacketHandler)onCrossPrivateChat);

	// 挂机
	setNetPacketHandler(334, (NetPacketHandler)onSetGuaJi);
}

// ======== Unit 虚函数实现 ========

void Player::SetNeedSyncAround()
{
	// 标记需要同步给周围玩家
	setNeedSync();
}

bool Player::canAttackTarget( CfgSkill* pCfg, Unit* pTarget )
{
	return checkSkillTarget( pCfg, pTarget );
}

void Player::reset()
{
	Unit::reset();
	while ( auto* packet = m_netPackets.pop() )
		Answer::NetPacket::destroy( packet );
	m_cgindex = 0;
	memset( &m_chr, 0, sizeof(m_chr) );
	memset( &m_sysUser, 0, sizeof(m_sysUser) );
	memset( &m_sysUserPreventWallow, 0, sizeof(m_sysUserPreventWallow) );
	m_pkMode_bk = 0;
	m_lastPkValueTick = 0;
	m_levelStartTime = 0;
	m_eventHP = 0;
	m_trailer = nullptr;
	m_needSyncStatus = false;
	m_needSyncToTeam = false;
	m_nDieTick = 0;
	m_InBossHomeTime = 0;
	m_ExpRate = 0;
	m_StartProtect = 0;
	m_isBackCity = false;
	m_bDie = false;
	m_PlantState = false;
	m_todayGoldCharge = 0;
	m_firstFiveDayGoldCharge = 0;
	m_plantId = 0;
	m_startGatherTick = 0;
	m_lastSaveTick = 0;
	m_lastPoolTick = 0;
	m_lastActionTick = 0;
	m_lastExpPoolTick = 0;
	m_lastMagicWeaponBuffTick = 0;
	m_jumpTime = 0;
	m_saveDataTimeCount = 0;
	m_Battle = 0;
	m_nCamp = 0;
	m_nGuaJi = 0;
	m_needRecalAttr = false;
	m_SystemSetting.clear();
	m_BeiGongAttr.clear();
	m_ExtSysMgr.OnCleanUp();
}

bool Player::refresh()
{
	if ( m_needRecalAttr )
		recalcAttr();
	checkSaveToDB();
	checkNetPackets();
	checkTrailer();
	checkPool();
	minuteCheck( true );
	checkSyncStatus();
	checkDie();
	int64_t Tick = getTick();
	m_ExtSysMgr.OnUpdate( Tick );
	return false;
}

EntityId_t Player::getUnitId() const
{
	return m_chr.cid;
}

CharId_t Player::getOwner() const
{
	return m_chr.cid;
}

int32_t Player::getLevel() const
{
	return m_chr.level;
}

void Player::SetLevel( int32_t Level )
{
	int32_t OldLevel = m_chr.level;
	m_chr.level = Level;
	LevelUped( OldLevel, Level );
}

int32_t Player::getDeadTime() const
{
	return (int32_t)m_nDieTick;
}

void Player::postDamage( int32_t damage, UnitHandle launcher )
{
	// 受击后进入战斗状态
	SetInFight();
}

bool Player::isFriendSide( Unit *pUnit )
{
	if ( !pUnit )
		return false;
	Player *pOther = dynamic_cast<Player*>( pUnit );
	if ( !pOther )
		return false;
	// 同队为友方
	if ( IsInTeam() && pOther->IsInTeam() && GetTeamId() == pOther->GetTeamId() )
		return true;
	// 同家族为友方
	if ( getFamilyId() > 0 && getFamilyId() == pOther->getFamilyId() )
		return true;
	return false;
}

bool Player::checkSkillTarget( CfgSkill *pCfg, Unit *pUnit )
{
	if ( !pCfg || !pUnit )
		return false;
	Player *pTarget = dynamic_cast<Player*>( pUnit );
	if ( !pTarget )
	{
		// 非玩家目标（怪物等），一般允许
		return true;
	}
	// 不能攻击自己
	if ( pTarget == this )
		return false;
	// 安全区不能PK
	if ( m_pMap && m_pMap->IsSafeMap() )
		return false;
	// 同队不能攻击
	if ( IsInTeam() && pTarget->IsInTeam() && GetTeamId() == pTarget->GetTeamId() )
		return false;
	// 同家族不能攻击
	if ( getFamilyId() > 0 && getFamilyId() == pTarget->getFamilyId() )
		return false;
	// 根据PK模式判断
	int32_t pkMode = getPkMode();
	switch ( pkMode )
	{
	case PK_MODE_PEACE:
		return false;
	case PK_MODE_TEAM:
		if ( IsInTeam() && pTarget->IsInTeam() && GetTeamId() == pTarget->GetTeamId() )
			return false;
		return true;
	case PK_MODE_LEGION:
		if ( getFamilyId() > 0 && getFamilyId() == pTarget->getFamilyId() )
			return false;
		return true;
	case PK_MODE_GOOD_EVIL:
		return pTarget->getPkValue() > 0;
	case PK_MODE_ALL:
		return true;
	default:
		return false;
	}
}

Position Player::getCurrentTile()
{
	return StaticObj::getCurrentTile( this );
}

int32_t Player::GetCalLevel() const
{
	return getLevel();
}

void Player::broadcastBasicData()
{
	Unit::broadcastBasicData( this );
}

bool Player::isRobot()
{
	return false;
}

void Player::saveToDB( int32_t reason, int32_t param )
{
	PlayerDBData dbData;
	SaveDBData( dbData );
	int8_t connid = getConnId();
	DB_SERVICE.savePlayer( connid, reason, param, dbData );
}

// ======== 基础属性 getter/setter ========

CharId_t Player::getCid() const
{
	return m_chr.cid;
}

std::string Player::getName() const
{
	return std::string( m_chr.name );
}

Sex_t Player::getSex() const
{
	return m_chr.sex;
}

Job_t Player::getJob() const
{
	return m_chr.job;
}

int64_t Player::getExp() const
{
	return m_chr.exp;
}

int32_t Player::getCreateTime() const
{
	return m_chr.create_time;
}

int32_t Player::getHead() const
{
	return m_chr.head;
}

int32_t Player::getLastLogoutTime() const
{
	return m_chr.last_logout_time;
}

int32_t Player::getLastLoginTime() const
{
	return m_chr.last_login_time;
}

FamilyId_t Player::getFamilyId() const
{
	return m_extCharFamily.GetFamilyId();
}

std::string Player::getFamilyName() const
{
	return m_extCharFamily.GetFamilyName();
}

int8_t Player::getFamilyPosition() const
{
	// 家族职位 - 待实现
	return 0;
}

int32_t Player::getUid() const
{
	return m_sysUser.uid;
}

int32_t Player::getSid() const
{
	return m_sysUser.sid;
}

std::string Player::getIP()
{
	return std::string( m_sysUser.IP );
}

// ======== 经验/等级 ========

void Player::delExp( int64_t nValue )
{
	m_chr.exp -= nValue;
	if ( m_chr.exp < 0 )
		m_chr.exp = 0;
	setNeedSyncSelf();
}

void Player::addExp( int64_t addon, bool Iswallow )
{
	if ( addon > 0 )
	{
		int64_t actual = addon;
		if ( Iswallow )
			actual = (int64_t)( (double)addon * benefitRatio() );
		m_chr.exp += actual;
		autoUpgradeLevel();
		setNeedSyncSelf();
	}
}

int64_t Player::GetLevelExp()
{
	int32_t lv = getLevel();
	return CFG_DATA.getNeedLevelExp( lv );
}

int64_t Player::GetLevelMaxExp()
{
	int32_t lv = getLevel();
	return CFG_DATA.getMaxExp( lv );
}

// ======== PK 系统 ========

int32_t Player::getPkMode()
{
	return m_chr.pk_mode;
}

void Player::setPkMode( int32_t mode, bool backUp )
{
	m_chr.pk_mode = mode;
	if ( backUp )
		m_pkMode_bk = m_chr.pk_mode;
	if ( mode != PK_MODE_PEACE )
		SetPkProtectTime( 0 );
	setNeedSyncSelf();
	SetNeedSyncAround();
}

void Player::resetPkModeOnEnterMap( const Map *pMap )
{
	if ( !pMap )
		return;
	int32_t mapPkMode = pMap->GetPkMode();
	if ( mapPkMode > 0 )
	{
		if ( mapPkMode == 1 )
			m_chr.pk_mode = PK_MODE_PEACE;
		else
			m_chr.pk_mode = mapPkMode;
		if ( m_chr.pk_time > 0 )
			m_chr.pk_time = 0;
	}
	else if ( m_chr.pk_mode != m_pkMode_bk )
	{
		m_chr.pk_mode = m_pkMode_bk;
	}
	setNeedSyncSelf();
	SetNeedSyncAround();
}

void Player::updatePkValue( Player *pKiller, Map* pMap )
{
	// 反编译源中逻辑复杂，此处先实现基础版本
	if ( !pKiller )
		return;
	if ( getPkValue() > 20 )
		pKiller->addPkValue( 10 );
	else
		pKiller->addPkValue( 10 );
}

void Player::addPkValue( int32_t addon )
{
	if ( addon > 0 && m_chr.pk_value <= 0 )
		m_lastPkValueTick = getTick();
	m_chr.pk_value += addon;
	if ( m_chr.pk_value < 0 )
		m_chr.pk_value = 0;
	if ( m_chr.pk_value > 99 )
		m_extFightChecker.ChangeBuleName( false );
	SetNeedSyncAround();
	setNeedSyncSelf();
}

int32_t Player::getPkValue()
{
	return m_chr.pk_value;
}

int32_t Player::getPkProtectTime()
{
	return m_chr.pk_time;
}

void Player::SetPkProtectTime( int32_t Time )
{
	m_chr.pk_time = Time;
	SetNeedSyncAround();
	setNeedSyncSelf();
}

void Player::SafeToPrison()
{
	if ( getPkValue() <= 99 )
		return;
	CfgMapRegion *pCfgRegion = CFG_DATA.getMapRegion( 20001 );
	if ( !pCfgRegion )
		return;
	Map *pTargetMap = MAP_MANAGER.GetMap( pCfgRegion->mapid );
	if ( !pTargetMap )
		return;
	Position pos = pTargetMap->getRandomWalkablePositionInRegion( *pCfgRegion );
	if ( pos.x < 0 || pos.y < 0 )
		return;
	switchMap( pTargetMap, pos.x, pos.y, true );
}

// ======== 金钱/充值 ========

void Player::syncGold()
{
	// 充值同步 - 由 DB 消息驱动
	// TODO: 反编译源中查询 sys_user.gold_pay 字段，需先在 SysUser 中添加该字段
}

void Player::syncTodayGoldPay()
{
	m_PlayerYunYingHD.SendEveryDayChongZhiInfo( 3 );
	m_PlayerYunYingHD.SendEveryDayChongZhiInfo( 2 );
}

void Player::updatePayGold()
{
	m_todayGoldCharge = 0;
}

// ======== 属性/战斗 ========

double Player::benefitRatio()
{
	if ( m_sysUser.adult )
		return 1.0;
	int32_t onlineTime = m_sysUser.total_online_time + getNow() - m_sysUser.last_login_time;
	if ( onlineTime > 17999 )
		return 0.0;
	if ( onlineTime <= 10799 )
		return 1.0;
	return 0.5;
}

BenefitType Player::benefitType()
{
	if ( m_sysUser.adult )
		return BT_NORMAL;
	int32_t onlineTime = m_sysUser.total_online_time + getNow() - m_sysUser.last_login_time;
	if ( onlineTime > 17999 )
		return BT_TIRED;
	if ( onlineTime > 10799 )
		return BT_HURT;
	return BT_NORMAL;
}

int32_t Player::getBattle() const
{
	return m_Battle;
}

int32_t Player::getClothesId()
{
	return m_extEquip.GetEquipSlot(2).itemId;
}

int32_t Player::getWeaponId()
{
	return m_extEquip.GetEquipSlot(0).itemId;
}

// ======== 背包/物品 ========

int32_t Player::GetFreeSlotCount()
{
	return m_extCharBag.GetFreeSlotCount();
}

MemChrBag Player::getBagSlotData( int32_t slot )
{
	return m_extCharBag.GetSlotData( slot );
}

void Player::setBagSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason, int32_t count )
{
	m_extCharBag.SetSlotData( slot, slotData, reason, count );
}

bool Player::hasItem( int32_t baseid, int32_t type, int32_t count )
{
	return m_extCharBag.HasItem( baseid, (int8_t)type, count );
}

bool Player::autoUseItem( const MemChrBag &item )
{
	// 自动使用物品
	return false;
}

void Player::autoUseItem( MemChrBagVector &items )
{
	// 批量自动使用物品
}

int32_t Player::getFirstFreeSlot()
{
	return m_extCharBag.GetFirstFreeSlot();
}

// ======== 任务/记录 ========

void Player::updateRecord( int32_t id, int32_t param )
{
	m_extOperateLimit.UpdateLimitCount( id, param );
}

int32_t Player::getRecord( int32_t id ) const
{
	return m_extOperateLimit.GetLimitCount( id );
}

void Player::clearRecordRange( int32_t start, int32_t end, int32_t diffDay )
{
	m_extOperateLimit.ResetRange( start, end, diffDay );
}

int32_t Player::GetContinueLoginCount() const
{
	return m_sysUser.continue_login_count;
}

bool Player::IsMiniClient() const
{
	return m_sysUser.type == 1;
}

void Player::updateLastTaskId( int32_t tid )
{
	m_chr.last_task_id = tid;
}

void Player::setTaskCanSubmit( int32_t tid )
{
	// 设置任务可提交 - 待实现
}

void Player::checkTaskCanSubmit( int32_t dungeonID )
{
	// 检查任务可提交 - 待实现
}

void Player::taskTalkWithNpc( int32_t npcid )
{
	// 与NPC对话 - 待实现
}

// ======== 位置/地图切换 ========

bool Player::isInRectangle( Position x, Position y ) const
{
	return const_cast<Unit*>(static_cast<const Unit*>(this))->isInRectangle( x, y );
}

bool Player::isLeader() const
{
	return m_chr.leader != 0;
}

int32_t Player::getLeaderCid() const
{
	return m_chr.leader;
}

void Player::setOldPosition()
{
	if ( m_pMap )
	{
		m_oldPosition.mapid = m_pMap->GetMapId();
		m_oldPosition.x = getCurrentTile().x;
		m_oldPosition.y = getCurrentTile().y;
		m_oldPosition.runnerId = m_pMap->GetRunnerId();
	}
}

PlayerPosition Player::getOldPosition()
{
	return m_oldPosition;
}

// ======== 腾讯黄钻 ========

int32_t Player::getIsYellowVip()
{
	return m_is_yellow_vip;
}

void Player::setIsYellowVip( int32_t isYellowVip )
{
	m_is_yellow_vip = isYellowVip;
}

int32_t Player::getIsYellowYearVip()
{
	return m_is_yellow_year_vip;
}

void Player::setIsYellowYearVip( int32_t isYellowYearVip )
{
	m_is_yellow_year_vip = isYellowYearVip;
}

int32_t Player::getYellowVipLevel()
{
	return m_yellow_vip_level;
}

void Player::setYellowVipLevel( int32_t yellowVipLevel )
{
	m_yellow_vip_level = yellowVipLevel;
}

int32_t Player::getIsYellowHighVip()
{
	return m_is_yellow_high_vip;
}

void Player::setIsYellowHighVip( int32_t isYellowHighVip )
{
	m_is_yellow_high_vip = isYellowHighVip;
}

int32_t Player::getMemYellowStone( CharId_t cid, int32_t id )
{
	return 0;
}

int32_t Player::getYellowGrowId()
{
	return 0;
}

// ======== 杂项 ========

void Player::addKillPlayerCount()
{
	m_chr.pk_killed_count++;
}

void Player::addContribution( int32_t addon, int32_t rate )
{
	// 贡献度增加（简化实现）
}

void Player::addEventHp( int32_t hpValue )
{
	m_eventHP += hpValue;
}

void Player::setGateIndex( int16_t index )
{
	m_cgindex = index;
}

int16_t Player::getGateIndex() const
{
	return m_cgindex;
}

void Player::setTrailer( Trailer* pTrailer )
{
	m_trailer = pTrailer;
	if ( pTrailer )
	{
		// 跟随者设置时接收任务
	}
	else
	{
		m_task.CleanTaskType( 5 );
	}
}

void Player::checkTrailer()
{
	if ( m_trailer )
	{
		// 检查跟随者是否需要同步移动
	}
}

Trailer* Player::getTrailer()
{
	return m_trailer;
}

void Player::onDamageEvent( UnitHandle target, int32_t attackValue )
{
	SetInFight();
}

void Player::onDamagedEvent( UnitHandle launcher, int32_t attackValue )
{
	SetInFight();
}

bool Player::IsDead() const
{
	return m_bDie;
}

int64_t Player::GetDieTick() const
{
	return m_nDieTick;
}

void Player::checkDie()
{
	if ( !m_bDie && !isAlive() )
	{
		m_bDie = true;
		m_nDieTick = getTick();
		int32_t v2 = getRecord( 1012 ) + 1;
		updateRecord( 1012, v2 );
		if ( m_pMap )
		{
			// 通知地图玩家死亡
		}
		m_extCharPet.OnPlayerDie();
		m_CharLittlerHelper.OnRest();
	}
}

void Player::setActFrontPosition()
{
	if ( m_pMap )
	{
		m_ActFrontPosition.mapid = m_pMap->GetMapId();
		m_ActFrontPosition.x = getCurrentTile().x;
		m_ActFrontPosition.y = getCurrentTile().y;
		m_ActFrontPosition.runnerId = m_pMap->GetRunnerId();
	}
}

PlayerAction Player::getAction()
{
	// 返回当前动作 - 简化实现
	return (PlayerAction)0;
}

void Player::kingdomTaskFaile()
{
	// 王国任务失败
}

void Player::setKingdomTaskState( int32_t tid, int32_t state )
{
	// 设置王国任务状态
}

void Player::onKillMonster( int32_t mid, int32_t level, int32_t exp, bool isBoss )
{
	// 击杀怪物处理 - 待完善任务和统计逻辑
}

void Player::sendActivityGain( int32_t activityId, int32_t exp, int32_t money, int32_t isEnd )
{
	// 发送活动奖励信息
}

void Player::setSyncStatusFlag()
{
	m_needSyncStatus = true;
}

void Player::setSyncToTeamFlag()
{
	m_needSyncToTeam = true;
}

void Player::addLogoutPacket( int32_t reason, int32_t param )
{
	// 添加登出网络包
}

void Player::broadcastLeave()
{
	// 广播离开
}

void Player::onActAddHL()
{
	// 活动添加活力
}

void Player::onNewDayCome()
{
	m_sysUser.continue_login_count++;
	refreshDailyCheck( false );
}

void Player::refreshDailyCheck( bool first )
{
	// 刷新每日检查
}

void Player::refeshKillerRecord()
{
	// 刷新击杀记录
}

bool Player::isFirstSevenDay()
{
	int32_t days = getCreatedDays();
	return days <= 7;
}

int32_t Player::getCreatedDays() const
{
	return Answer::DayTime::daydiff( m_chr.create_time ) + 1;
}

void Player::SendIconState( ShowIcon* pIcon )
{
	if ( !pIcon )
		return;
	int8_t connid = getConnId();
	GameService *pService = GAME_SERVICE;
	Answer::NetPacket *packet = pService->popNetpacket( connid, Answer::PackType::PACK_DISPATCH, 0x2803 );
	if ( packet )
	{
		packet->writeInt32( pIcon->nId );
		packet->writeInt8( pIcon->nState );
		packet->writeInt32( pIcon->nLeftTime );
		packet->setSize( packet->getWOffset() );
		pService->sendPacketTo( connid, getGateIndex(), packet );
	}
}

void Player::sendUpdateSocialPlayerInfo( PlayerInfoIndex index, int32_t value )
{
	// 发送社交玩家信息更新 - 待实现
}

void Player::sendJungongChangeInfo( int32_t addon, BenefitType bnfType )
{
	// 发送军功变更信息
}

void Player::sendWuhuenChangeInfo( int32_t addon, BenefitType bnfType )
{
	// 发送武魂变更信息
}

void Player::sendjiangxingChangeInfo( int32_t addon, BenefitType bnfType )
{
	// 发送将星变更信息
}

void Player::sendKingdomChangeInfo( int32_t addon )
{
	// 发送王国贡献变更信息
}

void Player::sendPvpInfo()
{
	// 发送PVP信息
}

void Player::sendChrLoginInInfo()
{
	// 发送角色登录信息
}

void Player::sendKillerRankSelf()
{
	// 发送击杀排行榜自身信息
}

void Player::sendGetGoldInfo()
{
	// 发送金币信息
}

void Player::sendYellowStone()
{
	// 发送黄钻信息
}

void Player::sendPreventWallow()
{
	// 发送防沉迷信息
}

void Player::checkSaveToDB()
{
	int64_t tick = getTick();
	if ( tick - m_lastSaveTick > 60000 )
	{
		saveToDB( 0, 0 );
		m_lastSaveTick = tick;
	}
}

void Player::checkSyncStatus()
{
	if ( m_needSyncStatus )
	{
		m_needSyncStatus = false;
		setNeedSyncSelf();
	}
	if ( m_needSyncToTeam )
	{
		m_needSyncToTeam = false;
		if ( IsInTeam() )
		{
			// 同步到队伍
		}
	}
}

void Player::checkPool()
{
	int64_t tick = getTick();
	if ( tick - m_lastPoolTick > 10000 )
	{
		m_lastPoolTick = tick;
	}
}

void Player::minuteCheck( bool bSend )
{
	// 每分钟检查
}

void Player::clearSelectedUnit()
{
	m_selectedUnit = UnitHandle();
}

bool Player::autoUpgradeLevel()
{
	if ( getLevel() >= GetMaxLevel() )
		return false;
	int64_t needExp = GetLevelExp();
	if ( m_chr.exp >= needExp )
	{
		return upgradeLevel( true );
	}
	return false;
}

bool Player::upgradeLevel( bool bAuto )
{
	int32_t oldLevel = getLevel();
	int32_t maxLevel = GetMaxLevel();
	if ( oldLevel >= maxLevel )
		return false;
	if ( m_chr.exp < GetLevelExp() )
		return false;
	m_chr.level++;
	m_chr.exp -= GetLevelExp();
	LevelUped( oldLevel, m_chr.level );
	setNeedSyncSelf();
	SetNeedSyncAround();
	if ( bAuto )
		autoUpgradeLevel();
	return true;
}

bool Player::isInWorldBossActivity()
{
	return false;
}

bool Player::isFirstDay()
{
	return getCreatedDays() <= 1;
}

bool Player::checkUseSkill()
{
	return true;
}

void Player::addSkill( int32_t skillid, int32_t level )
{
	// 技能添加 - 需要实现技能系统
}

void Player::removeSkill( int32_t skillid )
{
	// 技能移除 - 需要实现技能系统
}

MemChrSkillVector::iterator Player::findSkill( int32_t skillid )
{
	for ( auto it = m_skills.begin(); it != m_skills.end(); ++it )
	{
		if ( it->skillId == skillid )
			return it;
	}
	return m_skills.end();
}

int32_t Player::upgradeSkill( int32_t skillid, int32_t BagSlot )
{
	// 技能升级 - 需要实现技能系统
	return 0;
}

void Player::doSkillCost( CfgSkill *pCfgSkill, MemChrSkillVector::iterator &itSkill )
{
	// 技能消耗 - 需要实现技能系统
}

void Player::doSkillLevel( int32_t sid, int32_t slevel, UnitHandle target )
{
	// 技能等级 - 需要实现技能系统
}

void Player::setOpenId( std::string openId )
{
	m_openId = openId;
}

std::string Player::getOpenId()
{
	return m_openId;
}

void Player::setOpenKey( std::string openKey )
{
	m_openKey = openKey;
}

std::string Player::getOpenKey()
{
	return m_openKey;
}

void Player::setPf( std::string pf )
{
	m_pf = pf;
}

std::string Player::getPf()
{
	return m_pf;
}

void Player::setPfKey( std::string pfKey )
{
	m_pfKey = pfKey;
}

std::string Player::getPfKey()
{
	return m_pfKey;
}

int32_t Player::checkPreventWallow( Answer::NetPacket *inPacket )
{
	return 0;
}

int32_t Player::getIsYellowVip()
{
	return m_is_yellow_vip;
}

void Player::DieResetXp()
{
	// 死亡重置XP
}

void Player::AddBeiGongAttr( int32_t nType, int32_t nVal )
{
	m_BeiGongAttr[nType] += nVal;
}

void Player::SetPlantState( bool bState )
{
	m_PlantState = bState;
}

void Player::AddExpRate( int32_t AddValue )
{
	m_ExpRate += AddValue;
}

int32_t Player::GetExpRate()
{
	return m_ExpRate;
}

void Player::SetPPTick( int64_t CurTick )
{
	m_LastAddPPTick = CurTick;
}

void Player::SetPlantId( EntityId_t PlantId )
{
	m_plantId = PlantId;
	SetNeedSyncAround();
}

EntityId_t Player::GetPlantId()
{
	return m_plantId;
}

void Player::SetStartGather( int64_t CurTick )
{
	m_startGatherTick = CurTick;
}

int64_t Player::GetStartGather()
{
	return m_startGatherTick;
}

// ========== 地图切换/离开 ==========

int32_t Player::switchMap( Map *pMap, int32_t x, int32_t y, bool isFly )
{
	if ( !m_pMap || !pMap || m_pMap == pMap )
		return 10002;

	// 检查是否可以进入目标地图
	int32_t err = pMap->canEnter( this );
	if ( err )
	{
		GAME_SERVICE.replyfailure( m_connid, m_cgindex, 0x10, err, pMap->GetMapId() );
		return err;
	}

	// 如果当前在副本中，先离开副本
	if ( InDungeon() )
	{
		leaveDungeon();
		return 0;
	}

	// 记录换图日志
	setOldPosition();
	BreakGather( true );
	broadcastLeave();
	m_pMap->removePlayer( this, false );

	// 进入新地图
	pMap->addPlayer( this, x, y );

	// 回复客户端
	int32_t nRunnerId = m_pMap ? m_pMap->GetRunnerId() : 0;
	int32_t tarRunnerId = pMap->GetRunnerId();
	if ( nRunnerId == tarRunnerId )
	{
		GAME_SERVICE.replySuccess( m_connid, m_cgindex, 0x10, pMap->GetMapId() );
	}
	else
	{
		// 跨Runner需要通过PostMsg转发
		MAP_MANAGER.PostMsg( tarRunnerId, GMC_PLAYER_LEAVE_MAP, this, pMap, x, y, 0 );
	}

	return 0;
}

int32_t Player::leaveDungeon()
{
	if ( !m_pMap )
		return 10002;

	Dungeon *pDungeon = dynamic_cast<Dungeon*>( m_pMap );
	if ( !pDungeon )
	{
		Answer::Logger::print( Answer::LogLevel::LOG_LEVEL_INFO, "pDungeon NULL" );
		return 10002;
	}

	// 计算返回位置
	Position oldPos( m_oldPosition.x, m_oldPosition.y );
	if ( pDungeon->StayPosition() )
		oldPos = getCurrentTile();

	int32_t backMapId = pDungeon->GetBackMapId();
	if ( backMapId > 0 )
	{
		oldPos = pDungeon->GetBackPos();
	}
	else
	{
		backMapId = m_oldPosition.mapid;
	}

	Map *pTargetMap = MAP_MANAGER.GetMap( backMapId );
	if ( !pTargetMap )
	{
		int32_t runnerId = GetRunnerId();
		Answer::Logger::print( Answer::LogLevel::LOG_DUNGEON_INFO,
			"leave dungeon is null fail oldmap id %d, kingdom id %d\n", m_oldPosition.mapid, runnerId );
		return 10002;
	}

	if ( pTargetMap == pDungeon )
	{
		int32_t runnerId = GetRunnerId();
		Answer::Logger::print( Answer::LogLevel::LOG_DUNGEON_INFO,
			"==== id %d, kingdom id %d\n", m_oldPosition.mapid, runnerId );
		return 10002;
	}

	// 离开副本
	broadcastLeave();
	pDungeon->removePlayer( this, false );

	if ( !isAlive() )
		safeRevive();

	// 团队副本特殊处理
	if ( pDungeon->getDungeonType() == 12 )
		m_extCharTeamDungeon.LeaveTeamDungeon();

	// 离开坐骑
	if ( m_extCharCarrier.IsInCarrier() )
		m_extCharCarrier.LeaveCarrier();

	// 进入返回地图
	pTargetMap->addPlayer( this, oldPos.x, oldPos.y );
	pDungeon->onPlayerLeave( this );
	BreakGather( true );

	return 0;
}

int32_t Player::leaveActivity()
{
	if ( !m_pMap )
		return 10002;

	if ( !isAlive() )
	{
		AddHp( 100 );
		SetDieTick();
	}

	// 获取返回地图
	int32_t backMapId = m_oldPosition.mapid;
	Map *pTargetMap = MAP_MANAGER.GetMap( backMapId );
	int32_t nLine = GAME_SERVICE.getLine();

	if ( !pTargetMap || m_pMap == pTargetMap || nLine != 9 )
	{
		// 返回主城
		CfgMapRegion *pCfgRegion = CFG_DATA.getMapRegion( 20001 );
		if ( !pCfgRegion )
		{
			Answer::Logger::print( Answer::LogLevel::LOG_LEVEL_ERROR,
				"leave activity back city fail! city region err!\n" );
			return 10002;
		}
		backMapId = pCfgRegion->mapid;
		pTargetMap = MAP_MANAGER.GetMap( backMapId );
		if ( !pTargetMap )
		{
			Answer::Logger::print( Answer::LogLevel::LOG_DUNGEON_INFO,
				"leave activity back city fail! city map err!\n" );
			return 10002;
		}
		Position pos = pTargetMap->getRandomWalkablePositionInRegion( *pCfgRegion );
		if ( pos.x >= 0 && pos.y >= 0 )
		{
			m_oldPosition.mapid = pTargetMap->GetMapId();
			m_oldPosition.x = pos.x;
			m_oldPosition.y = pos.y;
		}
	}

	// 离开坐骑
	if ( m_extCharCarrier.IsInCarrier() )
		m_extCharCarrier.LeaveCarrier();

	// 离开当前地图
	broadcastLeave();
	int32_t curRunnerId = m_pMap->GetRunnerId();
	int32_t tarRunnerId = pTargetMap->GetRunnerId();

	if ( curRunnerId == tarRunnerId )
	{
		m_pMap->removePlayer( this, false );
		pTargetMap->addPlayer( this, m_oldPosition.x, m_oldPosition.y );
	}
	else
	{
		m_pMap->removePlayer( this, false );
		MAP_MANAGER.PostMsg( tarRunnerId, GMC_PLAYER_LEAVE_MAP, this, pTargetMap,
			m_oldPosition.x, m_oldPosition.y, 0 );
	}

	recalcAttr();

	// 通知客户端
	int8_t connid = m_connid;
	NetPacket* outPacket = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, 0x4EBD );
	if ( outPacket )
	{
		outPacket->writeInt32( m_cgindex );
		outPacket->writeInt32( 0 );
		outPacket->setSize( outPacket->getWOffset() );
		GAME_SERVICE.sendPacket( connid, outPacket );
	}

	BreakGather( true );

	// 跨服特殊处理
	if ( GAME_SERVICE.getLine() == 9 )
	{
		int32_t v20 = getNow() + 120;
		updateRecord( 1924, v20 );
		kickBackFromCross( 10114 );
	}

	return 0;
}

void Player::EnterMapGongGao( int32_t gongGaoId, int32_t mapId )
{
	// 进入地图公告 - 待完善公告系统
}

void Player::safeRevive()
{
	// 安全复活
	m_bDie = false;
	m_nDieTick = 0;
	AddHp( getMaxHp() );
	AddMp( getMaxMp() );
}

void Player::kickBackFromCross( int32_t reason )
{
	// 踢回本服 - 跨服系统待实现
}
