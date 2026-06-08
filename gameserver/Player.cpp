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
	CKaiFuHuoDong* pKaiFu = Answer::Singleton<CKaiFuHuoDong>::instance();
	return pKaiFu->KaiFuHuoDongOperator(this, inPacket);
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

	GameService* pGS = Answer::Singleton<GameService>::instance();
	if ( pGS->getLine() == 9 )
		return 10002;

	int32_t Err = -1;
	uint16_t Proc = inPacket->getProc();
	int32_t nProcId = Proc;

	if ( Proc == 683 )
	{
		int8_t Type = inPacket->readInt8();
		if ( Type == 2 )
		{
			int8_t nIndex = inPacket->readInt8();
			CFestivalActivity* pFA = Answer::Singleton<CFestivalActivity>::instance();
			Err = pFA->GetDaTiReward(this, nIndex);
		}
		else if ( Type == 5 )
		{
			int32_t nIndex = inPacket->readInt8();
			CFestivalActivity* pFA = Answer::Singleton<CFestivalActivity>::instance();
			if ( !pFA->DuiHuan(this, nIndex) )
			{
				uint16_t replyProc = inPacket->getProc();
				int16_t GateIndex = getGateIndex();
				int8_t ConnId = getConnId();
				GameService* pGS2 = Answer::Singleton<GameService>::instance();
				pGS2->replySuccess(ConnId, GateIndex, replyProc, Type);
			}
		}
	}
	else if ( Proc == 684 )
	{
		std::string DaAn;
		inPacket->readUTF8(DaAn);
		std::string p_DaAn(DaAn);
		CFestivalActivity* pFA = Answer::Singleton<CFestivalActivity>::instance();
		bool bOk = (pFA->DaTi(this, &p_DaAn) == 0);
		uint16_t replyProc = inPacket->getProc();
		int16_t GateIndex = getGateIndex();
		if ( bOk )
		{
			int8_t ConnId = getConnId();
			GameService* pGS2 = Answer::Singleton<GameService>::instance();
			pGS2->replySuccess(ConnId, GateIndex, replyProc, 0);
		}
		else
		{
			int8_t ConnId = getConnId();
			GameService* pGS2 = Answer::Singleton<GameService>::instance();
			pGS2->replyfailure(ConnId, GateIndex, replyProc, 0, 0);
		}
	}
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
	{
		CKiaFuRecharge* pKFR = Answer::Singleton<CKiaFuRecharge>::instance();
		pKFR->OnRecharge(this, GetTodayPayGold(), AddGold);
	}

	// 双十一充值
	{
		CFestivalDoubleEleven* pFDE = Answer::Singleton<CFestivalDoubleEleven>::instance();
		pFDE->OnRecharge(this, GetTodayPayGold(), AddGold);
	}

	// 国庆
	int32_t totalPay = AddGold + GetTodayPayGold();
	m_CNationalDayHd.AddNationalValue(NATIONAL_HD_TYPE::HHT_RECHARGE, TodayPayGold, totalPay);

	// 联合服务器
	{
		CUniteServer* pUS = Answer::Singleton<CUniteServer>::instance();
		pUS->OnRecharge(this, AddGold);
	}

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
	{
		CFestivalDoubleEleven* pFDE = Answer::Singleton<CFestivalDoubleEleven>::instance();
		pFDE->AddRechargeRecord(this, AddGold);
		pFDE->SendIconState(this);
	}

	// 联合服务器图标
	{
		CUniteServer* pUS = Answer::Singleton<CUniteServer>::instance();
		pUS->SendIconState(this);
	}

	// 综合运营
	{
		CZongHeYunYingHD* pZHYHD = Answer::Singleton<CZongHeYunYingHD>::instance();
		pZHYHD->OnRecharge(this, AddGold);
	}

	// 公测图标
	COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
	pOB->SendIconState(this);

	// 开服活动图标
	{
		CKaiFuHuoDong* pKFHD = Answer::Singleton<CKaiFuHuoDong>::instance();
		pKFHD->SendKaiFuHuoDongIcon(this);
	}

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
	{
		CKaiFuHuoDong* pKFHD = Answer::Singleton<CKaiFuHuoDong>::instance();
		pKFHD->OnLevelUp(this, NewLevel);
	}

	// 腾讯信息
	m_extCharTencent.SendTGPIcon();
	m_extCharTencent.SendBlueStoneIcon();

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
	CUniteServer* pUS = Answer::Singleton<CUniteServer>::instance();
	pUS->SendUniteServerInfo(this);
	return 0;
}

int32_t Player::OnUniteServerGetRechargeGift( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int8_t nIndex = inPacket->readInt8();
	CUniteServer* pUS = Answer::Singleton<CUniteServer>::instance();
	if ( pUS->GetRechargeGift(this, nIndex) )
		return 10002;
	uint16_t Proc = inPacket->getProc();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->replySuccess(getConnId(), getGateIndex(), Proc, nIndex);
	return 0;
}

int32_t Player::OnDoubleElevenRequestInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	CFestivalDoubleEleven* pFDE = Answer::Singleton<CFestivalDoubleEleven>::instance();
	pFDE->SendActivityInfo(this);
	return 0;
}

int32_t Player::OnZHYYHDRequestInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	CZongHeYunYingHD* pZHYHD = Answer::Singleton<CZongHeYunYingHD>::instance();
	pZHYHD->SendActivityInfo(this);
	return 0;
}

int32_t Player::OnZHYYHDGetRechargeDailyReward( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	CZongHeYunYingHD* pZHYHD = Answer::Singleton<CZongHeYunYingHD>::instance();
	pZHYHD->GetRechargeDailyReward(this);
	uint16_t Proc = inPacket->getProc();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->replySuccess(getConnId(), getGateIndex(), Proc, 0);
	return 0;
}

int32_t Player::OnZHYYHDGetRechargeTeamShopDailyReward( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int32_t nIndex = inPacket->readInt32();
	CZongHeYunYingHD* pZHYHD = Answer::Singleton<CZongHeYunYingHD>::instance();
	pZHYHD->GetRechargeTeamShopDailyReward(this, nIndex);
	uint16_t Proc = inPacket->getProc();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->replySuccess(getConnId(), getGateIndex(), Proc, nIndex);
	return 0;
}

int32_t Player::OnZHYYHDBuyOnceShopItem( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int32_t nIndex = inPacket->readInt32();
	CZongHeYunYingHD* pZHYHD = Answer::Singleton<CZongHeYunYingHD>::instance();
	pZHYHD->BuyOnceShopItem(this, nIndex);
	uint16_t Proc = inPacket->getProc();
	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->replySuccess(getConnId(), getGateIndex(), Proc, nIndex);
	return 0;
}

int32_t Player::OnGetKaiFuREcharge( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int32_t nHdType = inPacket->readInt32();
	int32_t nType = inPacket->readInt32();
	int32_t nIndex = inPacket->readInt32();
	CKiaFuRecharge* pKFR = Answer::Singleton<CKiaFuRecharge>::instance();
	switch ( nHdType )
	{
		case 1:
			pKFR->OnGetRechargeSumReward(this, nIndex);
			break;
		case 2:
			pKFR->GetLianRechargeReward(this, nType, nIndex);
			break;
		case 4:
			pKFR->OnGetXiaoFeiReward(this, nIndex);
			break;
	}
	return 0;
}

int32_t Player::OnGetKaiFuChouJiang( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	int32_t nIndex = inPacket->readInt32();
	CKiaFuRecharge* pKFR = Answer::Singleton<CKiaFuRecharge>::instance();
	pKFR->OnGetChouJiangReward(this, nIndex);
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

// ======== P0-a: 构造/析构/初始化 ========

Player::Player()
{
}

Player::~Player()
{
}

void Player::init( PlayerDBData& dbData )
{
	int32_t nowTime = getNow();

	m_connid = dbData.connid;
	m_cgindex = dbData.cgindex;
	memcpy(&m_chr, &dbData.chr.data, sizeof(m_chr));

	if ( m_chr.pk_time <= nowTime )
		m_chr.pk_time = 0;
	if ( !m_chr.pk_mode )
		m_chr.pk_mode = 1;
	m_pkMode_bk = m_chr.pk_mode;

	m_levelStartTime = nowTime;
	m_lastPkValueTick = getTick();
	m_nLastSaveOnlineTime = nowTime;
	m_chr.last_login_time = nowTime;

	memcpy(&m_sysUser, &dbData.sysUser.data, sizeof(m_sysUser));
	m_sysUser.last_login_time = nowTime;
	m_sysUser.total_offline_time += nowTime - m_sysUser.last_logout_time;
	if ( m_sysUser.total_offline_time > 17999 )
	{
		m_sysUser.total_online_time = 0;
		m_sysUser.total_offline_time = 0;
	}
	m_sysUserPreventWallow = dbData.sysUserPreventWallow.data;

	m_task.init(this, &dbData.taskData.taskVt);
	memcpy(m_actions, dbData.actionData.actionArry, sizeof(m_actions));
	memcpy(&m_autoFight, &dbData.autoFight.data, sizeof(m_autoFight));
	m_systemSetting = dbData.systemSetting.data;

	tm localNow;
	getLocalNow(&localNow);
	m_lastLocalNow = localNow;
	m_lastSaveTick = getTick();

	initBuff(&dbData.buffData.buffVt);
	m_ExtSysMgr.OnLoadFromDB(dbData);

	if ( m_sysUser.last_logout_time <= 0 )
	{
		updateRecord(1016, 0);
		updateRecord(2003, 0);
		updateRecord(1908, 100000);
		CfgData* pCfg = Answer::Singleton<CfgData>::instance();
		const EnergyCfg* pEnergyCfg = pCfg->GetEnergyCfg();
		if ( pEnergyCfg )
			updateRecord(37305, pEnergyCfg->MaxEnergy);
		updateRecord(37307, nowTime);
		SendJingLiValue();
	}
	else
	{
		int32_t offlineTime = nowTime - m_sysUser.last_logout_time;
		GetOperateLimit().AddLimitCount(1019, offlineTime);
		int32_t nOffLineDay = Answer::DayTime::daydiffBw(m_sysUser.last_logout_time, nowTime);
		int32_t curCount = m_extOperateLimit.GetLimitCount(37007);
		if ( curCount < nOffLineDay )
			m_extOperateLimit.UpdateLimitCount(37007, nOffLineDay);
	}

	m_PlayerFunctionOpen.InitFunctionOpen(0, getLevel());
	m_PlayerFunctionOpen.InitFunctionOpenMailByLevel(getLevel());
	CfgData* pCfgData = Answer::Singleton<CfgData>::instance();
	int32_t ServerDiffDay = pCfgData->getServerDiffDay(SERVER_TYPE::SVT_NORMAL);
	m_PlayerFunctionOpen.InitFunctionOpenMailByKaiFuDay(ServerDiffDay + 1);
	m_PlayerFunctionOpen.CheckFunctionOpenMailByKaiFuDay(ServerDiffDay + 1);

	refreshDailyCheck(0);
	checkFestivalVersion();

	if ( dbData.sysUser.data.gold_pay > 0 )
		syncGold(dbData.sysUser.data.gold_pay);

	m_extCharTitle.InitTitle();
	m_InBossHomeTime = getRecord(2008);

	CEquipManager* pEM = Answer::Singleton<CEquipManager>::instance();
	pEM->SendPlayerEquipInfo(this);

	InitSysSetting();
	setSyncStatusFlag();
	minuteCheck(0);
	recalcAttr(1, 1);
	setHP(dbData.chr.data.hp);
	setMP(dbData.chr.data.mp);
	setKunLi(dbData.chr.data.kun_li);
	adjustUnitAttr();

	if ( !isAlive() )
		m_bDie = 1;

	int32_t MapId = StaticObj::getMapId(this);
	int32_t vNow = getNow();
	CharId_t Cid = getCid();
	DBService* pDB = Answer::Singleton<DBService>::instance();
	pDB->logPlayerLogin(m_connid, Cid, 1, vNow, MapId);

	CfgData* pCfg2 = Answer::Singleton<CfgData>::instance();
	CfgMapRegion* pCfgRegion = pCfg2->getMapRegion(20001);
	if ( pCfgRegion )
	{
		MapManager* pMM = Answer::Singleton<MapManager>::instance();
		Map* pTempMap = pMM->GetMap(pCfgRegion->mapid);
		if ( pTempMap )
		{
			Position pos = pTempMap->getRandomWalkablePositionInRegion(pCfgRegion);
			if ( pos.x >= 0 && pos.y >= 0 )
			{
				m_oldPosition.mapid = pTempMap->GetMapId();
				m_oldPosition.x = pos.x;
				m_oldPosition.y = pos.y;
				m_oldPosition.runnerId = pTempMap->GetRunnerId();
			}
		}
	}

	if ( Answer::DayTime::daydiff(dbData.chr.data.last_login_time) > 0 )
	{
		int32_t nTime = Answer::DayTime::dayzero(dbData.chr.data.create_time);
		int32_t nDay = Answer::DayTime::daydiff(dbData.chr.data.create_time);
		if ( nDay <= 30 )
		{
			DBService* pDB2 = Answer::Singleton<DBService>::instance();
			pDB2->LogPlayerStay(getConnId(), nTime, nDay);
		}
	}

	CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
	FamilyId_t winFamily = pAM->GetCityWarWinner(getConnId());
	if ( winFamily > 0 )
	{
		if ( getFamilyId() == winFamily )
			SetActState(1);
	}

	if ( IsMiniClient() )
		GetPlayerHuoYueDu().AddHuoYueDuRecord(7, 0, 0);

	std::string fromWay;
	GetFromWay(fromWay);
	if ( fromWay == "kkk" && getRecord(1920) <= 0 )
	{
		updateRecord(1920, 1);
		std::string Param;
		DBService* pDB3 = Answer::Singleton<DBService>::instance();
		pDB3->OnSendSysMail(getConnId(), getCid(), 6398, &Param, 0);
	}

	sendUpdateSocialPlayerInfo(PlayerInfoIndex::PII_LOAD, 1);
	ResetJingLi();

	LoginGongGao();

	std::string p_PickString(m_autoFight);
	m_CharLittlerhelper.parsePickString(&p_PickString);

	m_TeJieCRI = getTick();

	m_ExtSysMgr.InitSystem();
}

void Player::initNetPacketHandlers()
{
	setNetPacketHandler(8, onLogout);
	setNetPacketHandler(9, onSyncTime);
	setNetPacketHandler(10, onMove);
	setNetPacketHandler(11, onJump);
	setNetPacketHandler(12, onTrailerMove);
	setNetPacketHandler(16, onSwitchMap);
	setNetPacketHandler(18, onEnterDungeon);
	setNetPacketHandler(21, onLeaveDungeon);
	setNetPacketHandler(790, onDungeonBuildTower);
	setNetPacketHandler(792, onDungeonBuyTower);
	setNetPacketHandler(791, onDungeonStart);
	setNetPacketHandler(28, onDungeonSelectReward);
	setNetPacketHandler(796, onDungeonSummonBoss);
	setNetPacketHandler(793, onBuyDungeonEnterTime);
	setNetPacketHandler(797, onDungeonSummon);
	setNetPacketHandler(795, onDungeonQuickDone);
	setNetPacketHandler(23, onDungeonSaoDang);
	setNetPacketHandler(24, onDungeonReset);
	setNetPacketHandler(27, onGuessTheSize);
	setNetPacketHandler(352, onEnterChargeDungeon);
	setNetPacketHandler(76, onDungeonYJSKGuWu);
	setNetPacketHandler(29, onEnterActivity);
	setNetPacketHandler(30, onLeaveActivity);
	setNetPacketHandler(31, onGetAwardActivity);
	setNetPacketHandler(32, onActivityChangeMap);
	setNetPacketHandler(33, onFamilyWarActivePillar);
	setNetPacketHandler(41, onPickDropItem);
	setNetPacketHandler(42, onBeginGather);
	setNetPacketHandler(43, onEndGather);
	setNetPacketHandler(47, onSpecialPlant);
	setNetPacketHandler(44, onUseTrap);
	setNetPacketHandler(45, onSwitchPkMode);
	setNetPacketHandler(56, onSafeRevive);
	setNetPacketHandler(57, onSiteRevive);
	setNetPacketHandler(58, onStrongRevive);
	setNetPacketHandler(59, onQueryChrInfo);
	setNetPacketHandler(60, onUpgradeLevel);
	setNetPacketHandler(299, checkPreventWallow);
	setNetPacketHandler(114, onQueryTaskList);
	setNetPacketHandler(115, onReceiveTask);
	setNetPacketHandler(116, onSubmitTask);
	setNetPacketHandler(117, onGiveUpTask);
	setNetPacketHandler(118, onSetTaskCanSubmit);
	setNetPacketHandler(125, onTalkWithNpc);
	setNetPacketHandler(126, onQuickDone);
	setNetPacketHandler(127, onTeleport);
	setNetPacketHandler(128, onTeleportActivity);
	setNetPacketHandler(142, onAddAction);
	setNetPacketHandler(143, onRemoveAction);
	setNetPacketHandler(144, onExchangeAction);
	setNetPacketHandler(145, onSetAutoFight);
	setNetPacketHandler(146, onSetSystemSetting);
	setNetPacketHandler(149, onBuyChrShopItem);
	setNetPacketHandler(151, onBuyBackChrShopItem);
	setNetPacketHandler(152, onBuyResource);
	setNetPacketHandler(153, onBuyTaskCount);
	setNetPacketHandler(159, onTeleportByItem);
	setNetPacketHandler(161, onClickPayButton);
	setNetPacketHandler(162, onMapEntered);
	setNetPacketHandler(163, onDebugCmd);
	setNetPacketHandler(190, onQueryKillerRankSelf);
	setNetPacketHandler(197, onGamePublicChat);
	setNetPacketHandler(194, onCrossPrivateChat);
	setNetPacketHandler(333, onUpdateFlyIconInt);
	setNetPacketHandler(334, onSetGuaJi);
	setNetPacketHandler(438, OnAskBossInfo);
	setNetPacketHandler(830, OnRequestActivityInfo);
	setNetPacketHandler(836, OnRequestActivityRankInfo);
	setNetPacketHandler(833, OnActivityGetDailyReward);
	setNetPacketHandler(839, OnActivityApplyCityWar);
	setNetPacketHandler(480, OnClickGame);
	setNetPacketHandler(495, OnKaiFuHuoDongOperator);
	setNetPacketHandler(496, OnKaiFuHuoDongOperator);
	setNetPacketHandler(497, OnKaiFuHuoDongOperator);
	setNetPacketHandler(498, OnKaiFuHuoDongOperator);
	setNetPacketHandler(835, OnActivityWorldBossGuWu);
	setNetPacketHandler(527, OnSubPkValus);
	setNetPacketHandler(528, OnLevelPrison);
	setNetPacketHandler(870, OnUniteServerRequestInfo);
	setNetPacketHandler(871, OnUniteServerGetRechargeGift);
	setNetPacketHandler(872, OnUniteServerBuyDistinctGift);
	setNetPacketHandler(873, OnUniteServerHuoYueduGift);
	setNetPacketHandler(869, OnUniteBuyChangeNameCard);
	setNetPacketHandler(868, OnGetUniteWingLevelUpReward);
	setNetPacketHandler(887, OnUniteServerGetLianRechargeGift);
	setNetPacketHandler(888, OnUniteServerGetChouJiangTimesReward);
	setNetPacketHandler(846, OnGetKaiFuREcharge);
	setNetPacketHandler(847, OnGetKaiFuChouJiang);
	setNetPacketHandler(900, OnDoubleElevenRequestInfo);
	setNetPacketHandler(901, OnDoubleElevenGetLandGift);
	setNetPacketHandler(902, OnDoubleElevenGetDrawGift);
	setNetPacketHandler(907, OnDoubleElevenGetOnlineGift);
	setNetPacketHandler(908, OnDoubleElevenGetWishGift);
	setNetPacketHandler(903, OnDoubleElevenGetLandSumGift);
	setNetPacketHandler(904, OnDoubleElevenBuyDailyLimitShopItem);
	setNetPacketHandler(905, OnDoubleElevenGetHuoYueDuSumGift);
	setNetPacketHandler(909, OnDoubleElevenGetDailyRechargeGift);
	setNetPacketHandler(973, OnDoubleElevenGetRechargeSumGift);
	setNetPacketHandler(978, OnDoubleElevenGetPetIllusionItemGift);
	setNetPacketHandler(972, OnDoubleElevenGetXiaoFeiSumGift);
	setNetPacketHandler(845, OnRequestMoYuShiJieRecord);
	setNetPacketHandler(970, OnDoubleElevenBuyGiftShopItem);
	setNetPacketHandler(971, OnDoubleElevenGetFaBaoCritBackItem);
	setNetPacketHandler(974, OnDoubleElevenBuyGiftShopItem2);
	setNetPacketHandler(976, OnDoubleElevenBuyGiftItem);
	setNetPacketHandler(975, OnDoubleElevenGetEquipUpStarBackItem);
	setNetPacketHandler(260, OnDoubleElevenBuyPetGift);
	setNetPacketHandler(540, OnFengHao);
	setNetPacketHandler(977, OnDoubleElevenGetRechargeBack);
	setNetPacketHandler(985, OnDoubleElevenGetEquipQingYiGift);
	setNetPacketHandler(986, OnDoubleElevenGetFriendQingYiGift);
	setNetPacketHandler(988, OnDoubleElevenRandScoreDrawGift);
	setNetPacketHandler(989, OnDoubleElevenRandGouWuChe);
	setNetPacketHandler(983, OnGetLianRechargeReward);
	setNetPacketHandler(541, OnSetFcmTime);
	setNetPacketHandler(990, onDungeonNpc);
	setNetPacketHandler(991, onComBackCity);
	setNetPacketHandler(624, OnCheckAccelerator);
	setNetPacketHandler(661, OnZHYYHDRequestInfo);
	setNetPacketHandler(662, OnZHYYHDGetRechargeDailyReward);
	setNetPacketHandler(663, OnZHYYHDGetRechargeTeamShopDailyReward);
	setNetPacketHandler(664, OnZHYYHDBuyOnceShopItem);
	setNetPacketHandler(681, OnOpenBetaOperator);
	setNetPacketHandler(682, OnOpenBetaOperator);
	setNetPacketHandler(689, OnOpenBetaOperator);
	setNetPacketHandler(683, OnFestivalActivityOperator);
	setNetPacketHandler(684, OnFestivalActivityOperator);
	setNetPacketHandler(855, OnEquipBackOperator);
	setNetPacketHandler(856, OnEquipBackOperator);
	setNetPacketHandler(857, OnEquipBackOperator);
	setNetPacketHandler(865, OnEquipBackOperator);
	setNetPacketHandler(866, OnEquipBackOperator);
	setNetPacketHandler(862, OnEquipBackOperator);
	setNetPacketHandler(863, OnEquipBackOperator);
	setNetPacketHandler(864, OnEquipBackOperator);
	setNetPacketHandler(669, OnAskLastFullHpTime);
	setNetPacketHandler(670, OnFullHp);
	setNetPacketHandler(513, OnGetMiniClientReward);
	setNetPacketHandler(205, OnGetMapBossInfo);
	setNetPacketHandler(204, OnGetLevelBossInfo);
	setNetPacketHandler(680, OnPaiMaiHangHanHua);
	setNetPacketHandler(207, OnEnterSpecialBossMap);
	setNetPacketHandler(208, OnLeaveSpecialBossMap);
	setNetPacketHandler(561, OnRollTheDice);
	setNetPacketHandler(562, OnCycleTowerEvent);
	setNetPacketHandler(563, ChatValidateed);
	setNetPacketHandler(564, onBuyXuWuValue);
	setNetPacketHandler(996, onTeleportByItem);
	setNetPacketHandler(995, onSwitchMap);
	setNetPacketHandler(994, onMove);
	setNetPacketHandler(982, OnChristmasDuiHuan);
	setNetPacketHandler(937, onDungeonRandom);
	setNetPacketHandler(938, OnBuyRandomPosTimes);
	setNetPacketHandler(939, OnBuyJingLiValue);
}

void Player::InitExtSystems()
{
	m_extOperateLimit.Init(this);
	m_ExtSysMgr.Register(&m_extOperateLimit);
	m_PlayerFunctionOpen.Init(this);
	m_ExtSysMgr.Register(&m_PlayerFunctionOpen);
	m_extCurrency.Init(this);
	m_ExtSysMgr.Register(&m_extCurrency);
	m_extCharBag.Init(this);
	m_ExtSysMgr.Register(&m_extCharBag);
	m_extEquip.Init(this);
	m_ExtSysMgr.Register(&m_extEquip);
	m_extFightChecker.Init(this);
	m_ExtSysMgr.Register(&m_extFightChecker);
	m_extCharTeam.Init(this);
	m_ExtSysMgr.Register(&m_extCharTeam);
	m_extCharPet.Init(this);
	m_ExtSysMgr.Register(&m_extCharPet);
	m_extCharSkill.Init(this);
	m_ExtSysMgr.Register(&m_extCharSkill);
	m_extTaskCycle.Init(this);
	m_ExtSysMgr.Register(&m_extTaskCycle);
	m_ScoreShop.Init(this);
	m_ExtSysMgr.Register(&m_ScoreShop);
	m_extCharFamily.Init(this);
	m_ExtSysMgr.Register(&m_extCharFamily);
	m_extCharTeamDungeon.Init(this);
	m_ExtSysMgr.Register(&m_extCharTeamDungeon);
	m_extCharWorship.Init(this);
	m_ExtSysMgr.Register(&m_extCharWorship);
	m_extCharAuction.Init(this);
	m_ExtSysMgr.Register(&m_extCharAuction);
	m_extCharHallOfFame.Init(this);
	m_ExtSysMgr.Register(&m_extCharHallOfFame);
	m_extCharTitle.Init(this);
	m_ExtSysMgr.Register(&m_extCharTitle);
	m_extCharMysteryShop.Init(this);
	m_ExtSysMgr.Register(&m_extCharMysteryShop);
	m_extCharMysteryGift.Init(this);
	m_ExtSysMgr.Register(&m_extCharMysteryGift);
	m_extCharExchange.Init(this);
	m_ExtSysMgr.Register(&m_extCharExchange);
	m_extCharDraw.Init(this);
	m_ExtSysMgr.Register(&m_extCharDraw);
	m_extCharWish.Init(this);
	m_ExtSysMgr.Register(&m_extCharWish);
	m_extBlackMarket.Init(this);
	m_ExtSysMgr.Register(&m_extBlackMarket);
	m_extCharTencent.Init(this);
	m_ExtSysMgr.Register(&m_extCharTencent);
	m_extCharWing.Init(this);
	m_ExtSysMgr.Register(&m_extCharWing);
	m_extMagicBox.Init(this);
	m_ExtSysMgr.Register(&m_extMagicBox);
	m_extCharCarrier.Init(this);
	m_ExtSysMgr.Register(&m_extCharCarrier);
	m_extCharJueWei.Init(this);
	m_ExtSysMgr.Register(&m_extCharJueWei);
	m_PlayerDepot.Init(this);
	m_ExtSysMgr.Register(&m_PlayerDepot);
	m_PlayerTrade.Init(this);
	m_ExtSysMgr.Register(&m_PlayerTrade);
	m_PlayerMail.Init(this);
	m_ExtSysMgr.Register(&m_PlayerMail);
	m_FRiendExp.Init(this);
	m_ExtSysMgr.Register(&m_FRiendExp);
	m_PlayerFaBao.Init(this);
	m_ExtSysMgr.Register(&m_PlayerFaBao);
	m_PlayerShangCheng.Init(this);
	m_ExtSysMgr.Register(&m_PlayerShangCheng);
	m_PlayerQiFu.Init(this);
	m_ExtSysMgr.Register(&m_PlayerQiFu);
	m_PlayerDailyActivity.Init(this);
	m_ExtSysMgr.Register(&m_PlayerDailyActivity);
	m_PlayerVip.Init(this);
	m_ExtSysMgr.Register(&m_PlayerVip);
	m_PlayerYunYingHD.Init(this);
	m_ExtSysMgr.Register(&m_PlayerYunYingHD);
	m_PlayerTouZi.Init(this);
	m_ExtSysMgr.Register(&m_PlayerTouZi);
	m_PlayerHuoYueDu.Init(this);
	m_ExtSysMgr.Register(&m_PlayerHuoYueDu);
	m_extCharPortal.Init(this);
	m_ExtSysMgr.Register(&m_extCharPortal);
	m_Wan360.Init(this);
	m_ExtSysMgr.Register(&m_Wan360);
	m_Vplan.Init(this);
	m_ExtSysMgr.Register(&m_Vplan);
	m_XingMai.Init(this);
	m_ExtSysMgr.Register(&m_XingMai);
	m_TianLing.Init(this);
	m_ExtSysMgr.Register(&m_TianLing);
	m_PlayerChouJiang.Init(this);
	m_ExtSysMgr.Register(&m_PlayerChouJiang);
	m_TreasureMap.Init(this);
	m_ExtSysMgr.Register(&m_TreasureMap);
	m_CMoneyRewardTask.Init(this);
	m_ExtSysMgr.Register(&m_CMoneyRewardTask);
	m_CSpecialEquip.Init(this);
	m_ExtSysMgr.Register(&m_CSpecialEquip);
	m_Curse.Init(this);
	m_ExtSysMgr.Register(&m_Curse);
	m_CLevelRefining.Init(this);
	m_ExtSysMgr.Register(&m_CLevelRefining);
	m_ShenWei.Init(this);
	m_ExtSysMgr.Register(&m_ShenWei);
	m_CBossKilledReward.Init(this);
	m_ExtSysMgr.Register(&m_CBossKilledReward);
	m_CTestServerReward.Init(this);
	m_ExtSysMgr.Register(&m_CTestServerReward);
	m_CWuHunShop.Init(this);
	m_ExtSysMgr.Register(&m_CWuHunShop);
	m_CCharWuHun.Init(this);
	m_ExtSysMgr.Register(&m_CCharWuHun);
	m_CSuperTeHui.Init(this);
	m_ExtSysMgr.Register(&m_CSuperTeHui);
	m_CGoblin.Init(this);
	m_ExtSysMgr.Register(&m_CGoblin);
	m_extShiZhuang.Init(this);
	m_ExtSysMgr.Register(&m_extShiZhuang);
	m_CMonthlyChouJiang.Init(this);
	m_ExtSysMgr.Register(&m_CMonthlyChouJiang);
	m_CGuardPrivilege.Init(this);
	m_ExtSysMgr.Register(&m_CGuardPrivilege);
	m_CDaTingReward.Init(this);
	m_ExtSysMgr.Register(&m_CDaTingReward);
	m_CMingGeExt.Init(this);
	m_ExtSysMgr.Register(&m_CMingGeExt);
	m_CKunExt.Init(this);
	m_ExtSysMgr.Register(&m_CKunExt);
	m_CExtFlopDraw.Init(this);
	m_ExtSysMgr.Register(&m_CExtFlopDraw);
	m_CSevenDayTask.Init(this);
	m_ExtSysMgr.Register(&m_CSevenDayTask);
	m_CGongMing.Init(this);
	m_ExtSysMgr.Register(&m_CGongMing);
	m_CXinMo.Init(this);
	m_ExtSysMgr.Register(&m_CXinMo);
	m_CharLittlerhelper.Init(this);
	m_ExtSysMgr.Register(&m_CharLittlerhelper);
	m_CNationalDayHd.Init(this);
	m_ExtSysMgr.Register(&m_CNationalDayHd);
	m_CRongHe.Init(this);
	m_ExtSysMgr.Register(&m_CRongHe);
}

void Player::SaveDBData( PlayerDBData& dbData )
{
	int32_t mapid = m_chr.mapid;
	int32_t x = m_chr.x;
	int32_t y = m_chr.y;

	if ( m_pMap )
	{
		mapid = m_pMap->GetMapId();
		x = StaticObj::getCurrentTile(this).x;
		y = StaticObj::getCurrentTile(this).y;
		if ( StaticObj::InDungeon(this) || StaticObj::InActivity(this) )
		{
			mapid = m_oldPosition.mapid;
			x = m_oldPosition.x;
			y = m_oldPosition.y;
		}
	}

	dbData.chr.data.cid = m_chr.cid;
	snprintf(dbData.chr.data.name, 30, m_chr.name);
	snprintf(dbData.chr.data.familyName, 30, m_chr.familyName);
	dbData.chr.data.sex = m_chr.sex;
	dbData.chr.data.job = m_chr.job;
	dbData.chr.data.level = m_chr.level;
	dbData.chr.data.exp = m_chr.exp;
	dbData.chr.data.mapid = mapid;
	dbData.chr.data.x = x;
	dbData.chr.data.y = y;
	dbData.chr.data.hp = getHP();
	dbData.chr.data.mp = GetMP();
	dbData.chr.data.kun_li = getKunLi();
	dbData.chr.data.battle = getBattle();
	dbData.chr.data.head = m_chr.head;
	dbData.chr.data.pk_mode = m_pkMode_bk;
	dbData.chr.data.pk_value = m_chr.pk_value;
	dbData.chr.data.pk_time = (m_chr.pk_time > getNow()) ? m_chr.pk_time : 0;
	dbData.chr.data.kill_count = m_chr.kill_count;
	dbData.chr.data.last_task_id = m_chr.last_task_id;
	dbData.chr.data.logout_count = m_chr.logout_count;
	m_chr.level_stay_time = m_chr.level_stay_time + getNow() - m_levelStartTime;
	dbData.chr.data.level_stay_time = m_chr.level_stay_time;
	dbData.chr.data.last_login_time = m_chr.last_login_time;
	dbData.chr.data.last_logout_time = m_chr.last_logout_time;
	dbData.chr.data.create_time = m_chr.create_time;
	dbData.chr.data.pay_click_count = m_chr.pay_click_count;
	dbData.chr.weapon = getMainWeaponId();
	dbData.chr.cloth = getClothesId();
	dbData.chr.wing = m_extCharWing.GetLevel();
	dbData.chr.equipStar = m_extEquip.GetEquipAllStar();
	dbData.chr.equipGem = m_extEquip.GetEquipAllGemLevel();
	dbData.chr.moneyDropRatio = GetAllMoneyRate();

	for ( int32_t i = 0; i <= 49; ++i )
		dbData.attrData.vAttr[i] = GetAttrValue((CObjAttrs::Index_T)i);

	dbData.sysUser.data.uid = m_sysUser.uid;
	dbData.sysUser.data.sid = m_sysUser.sid;
	dbData.sysUser.data.gold_cost_total = m_sysUser.gold_cost_total;
	dbData.sysUser.data.map_enter_time = m_sysUser.map_enter_time;
	dbData.sysUser.data.last_login_time = m_sysUser.last_login_time;
	dbData.sysUser.data.last_logout_time = m_sysUser.last_logout_time;
	dbData.sysUser.data.total_login_count = getRecord(1011);
	dbData.sysUser.data.continue_login_count = m_sysUser.continue_login_count;
	dbData.sysUser.data.total_online_time = m_sysUser.total_online_time;
	dbData.sysUser.data.total_offline_time = m_sysUser.total_offline_time;
	dbData.sysUserPreventWallow.data = m_sysUserPreventWallow;

	MemChrBuffVector buffs;
	getItemBuffs(buffs);
	dbData.buffData.buffVt = buffs;

	m_task.SaveDBData(dbData);
	memcpy(dbData.actionData.actionArry, m_actions, sizeof(dbData.actionData.actionArry));
	memcpy(&dbData.autoFight.data, &m_autoFight, sizeof(dbData.autoFight.data));

	std::string sysSetting;
	GetSysSetting(sysSetting);
	dbData.systemSetting.data = sysSetting;

	updateRecord(2008, m_InBossHomeTime);
	m_ExtSysMgr.OnSaveToDB(dbData);
}

int32_t Player::enterDungeon( Player* player, int32_t nDungeonId, ProcId_t nProc, int32_t nBuffId, int32_t nLevel, int8_t nHard, int8_t nQuality, int32_t nEvent )
{
	CfgData* pCfgData = Answer::Singleton<CfgData>::instance();
	CfgDungeon* pCfgDungeon = pCfgData->getDungeon(nDungeonId);
	if ( !pCfgDungeon || !player->m_pMap )
		return 10002;
	if ( player->benefitType() != BenefitType::BT_NORMAL )
		return 10002;
	if ( player->IsInStall() )
		return 10002;

	bool bChangeDungeon = true;
	Dungeon* pCurDungeon = nullptr;
	if ( player->m_pMap )
		pCurDungeon = dynamic_cast<Dungeon*>(player->m_pMap);

	if ( pCfgDungeon->type == 35 )
	{
		if ( !pCurDungeon )
			return 10002;
		if ( pCurDungeon->getDungeonType() != 25 )
			return 10002;
		int8_t Hard = pCurDungeon->GetHard();
		CfgData* pCfg2 = Answer::Singleton<CfgData>::instance();
		const CfgFamilyDungeonTable* pFDT = pCfg2->GetFamilyDungeonTable();
		const CfgFamilyDungeon* pCfg = pFDT->GetDungeon(Hard);
		if ( !pCfg )
			return 10002;
		if ( pCfg->nBaoKuFuBen != nDungeonId )
			return 10002;
		CfgNpc* cfgNpc = pCfgData->getNpc(5015);
		if ( !cfgNpc )
			return 10002;
		if ( !player->m_pMap->NearNpc(cfgNpc->id, StaticObj::GetPosX(player), StaticObj::GetPosY(player), 10) )
			return 10002;
	}
	else if ( pCfgDungeon->type == 36 && !player->m_pMap->IsBeastShrine() )
	{
		return 10002;
	}

	if ( pCurDungeon )
	{
		int32_t DungeonType = pCurDungeon->getDungeonType();
		if ( DungeonType == 22 )
		{
			if ( pCfgDungeon->id != pCurDungeon->getDungeonId() )
				return 10002;
			if ( pCurDungeon->getState() != DungeonState::DS_WIN && pCurDungeon->getState() != DungeonState::DS_FAIL )
				return 10002;
			bChangeDungeon = false;
		}
		else if ( DungeonType != 25 )
		{
			if ( DungeonType != 16 )
				return 10002;
			if ( pCfgDungeon->type != 16 )
				return 10002;
		}
		if ( bChangeDungeon )
			player->leaveDungeon();
	}
	else if ( StaticObj::InDungeon(player) || StaticObj::InActivity(player) )
	{
		return 10002;
	}

	if ( player->m_extCharTeamDungeon.IsInTeamDungeon() )
		return 10002;

	if ( pCfgDungeon->type != 12 )
	{
		if ( player->m_trailer )
		{
			GameService* pGS = Answer::Singleton<GameService>::instance();
			return pGS->replyfailure(player->getConnId(), player->getGateIndex(), nProc, 10055, player->getCid());
		}

		tm localNow;
		player->getLocalNow(&localNow);
		int32_t weekday = pCfgDungeon->weekday;
		if ( ((weekday >> GetWeekDay(localNow.tm_wday)) & 1) == 0 )
			return 10002;
		if ( localNow.tm_hour < pCfgDungeon->start_hour || localNow.tm_hour > pCfgDungeon->end_hour )
			return 10002;

		if ( pCfgDungeon->job > 0 && pCfgDungeon->job != player->getJob() )
			return 10002;

		if ( player->getLevel() < pCfgDungeon->level || player->getLevel() > pCfgDungeon->maxLevel )
		{
			GameService* pGS = Answer::Singleton<GameService>::instance();
			pGS->replyfailure(player->getConnId(), player->getGateIndex(), nProc, 10022, player->getCid());
			return 10002;
		}

		if ( pCfgDungeon->last_id > 0 && !player->m_extOperateLimit.CheckIsLimitedForever(pCfgDungeon->last_id + 20000) )
			return 10002;

		if ( pCfgDungeon->type == 16 )
		{
			int32_t star = pCfgDungeon->star;
			if ( star != player->m_extOperateLimit.GetLimitCount(37210) + 1 )
				return 10002;
		}

		int32_t Record = player->getRecord(pCfgDungeon->group_id);
		if ( Record >= player->GetDungeonDailyEnterLimit(nDungeonId) )
		{
			GameService* pGS = Answer::Singleton<GameService>::instance();
			pGS->replyfailure(player->getConnId(), player->getGateIndex(), nProc, 10023, player->getCid());
			return 10002;
		}

		int8_t vip = pCfgDungeon->vip;
		if ( vip > player->GetPlayerVip().GetVipLevel() )
			return 2;

		if ( pCfgDungeon->TeQuan > 0 )
		{
			if ( !player->GetPlayerVip().GetVipFlg(pCfgDungeon->TeQuan) )
				return 2;
		}

		ItemData costItem = pCfgDungeon->costItem;
		if ( pCfgDungeon->type == 22 )
			costItem.m_nCount = player->getRecord(pCfgDungeon->group_id) / 2 + 1;
		else if ( pCfgDungeon->type == 36 && nProc == 810 )
			costItem.m_nCount = 0;

		if ( pCfgDungeon->task_id > 0 )
		{
			CfgTask* pCfgTask = pCfgData->getTask(pCfgDungeon->task_id);
			if ( pCfgTask && player->m_task.GetTypeTask(pCfgTask->type) )
				return 10002;
		}

		if ( costItem.m_nCount > 0 && !player->m_extCharBag.HasItem(&costItem) )
			return 10002;

		if ( pCfgDungeon->costMoney > 0 )
		{
			int64_t money = player->GetCurrency().GetMoneyBindAndNoBind();
			if ( money < pCfgDungeon->costMoney )
				return 2;
		}

		if ( pCfgDungeon->costGold > 0 )
		{
			int64_t gold = player->GetCurrency(CURRENCY_TYPE::CURRENCY_GOLD);
			if ( gold < pCfgDungeon->costGold )
				return 2;
		}

		Dungeon* pDungeon = pCurDungeon;
		if ( bChangeDungeon )
		{
			MapManager* pMM = Answer::Singleton<MapManager>::instance();
			pDungeon = pMM->NewDungeon(nDungeonId);
		}
		if ( !pDungeon )
		{
			GameService* pGS = Answer::Singleton<GameService>::instance();
			pGS->replyfailure(player->getConnId(), player->getGateIndex(), nProc, 50004, 0);
			return 10002;
		}

		if ( pCfgDungeon->type != 17 )
		{
			if ( pCfgDungeon->costMoney > 0 )
			{
				if ( !player->GetCurrency().DecMoneyAndNoBind(pCfgDungeon->costMoney, CURRENCY_CHANGE_REASON::MCR_ENTER_DUNGEON, 0) )
					return 2;
			}
			if ( pCfgDungeon->costGold > 0 )
			{
				if ( !player->DecCurrency(CURRENCY_TYPE::CURRENCY_GOLD, pCfgDungeon->costGold, CURRENCY_CHANGE_REASON::GCR_ENTER_DUNGEON, nDungeonId) )
					return 2;
			}
			if ( costItem.m_nCount > 0 )
				player->m_extCharBag.RemoveItem(&costItem, ITEM_CHANGE_REASON::ICR_ENETR_DUNGEON);
		}

		if ( nBuffId > 0 ) pDungeon->SetMonsterBuff(nBuffId);
		if ( nLevel > 0 ) pDungeon->SetLevel(nLevel);
		if ( nHard > 0 ) pDungeon->SetHard(nHard);
		if ( nQuality > 0 ) pDungeon->SetQuality(nQuality);
		if ( nEvent > 0 ) pDungeon->OpenEvent(nEvent);

		if ( bChangeDungeon )
		{
			Position pos(pCfgDungeon->x, pCfgDungeon->y);
			if ( pDungeon->StayPosition() )
				pos = StaticObj::getCurrentTile(player);
			pDungeon->start(0);
			player->setOldPosition();
			player->broadcastLeave();
			player->m_pMap->removePlayer(player, 0);
			GameService* pGS = Answer::Singleton<GameService>::instance();
			pGS->replySuccess(player->getConnId(), player->getGateIndex(), nProc, nDungeonId);
			pDungeon->addPlayer(player, pos.x, pos.y);
			int32_t RunnerId = pDungeon->GetRunnerId();
			MapManager* pMM = Answer::Singleton<MapManager>::instance();
			pMM->PostMsg(RunnerId, GameMsgCode::GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0);
		}
		else
		{
			GameService* pGS = Answer::Singleton<GameService>::instance();
			pGS->replySuccess(player->getConnId(), player->getGateIndex(), nProc, nDungeonId);
			pDungeon->restart(0);
		}

		if ( pCfgDungeon->type != 13 && pCfgDungeon->type != 15 && pCfgDungeon->type != 17 )
		{
			int32_t newCount = player->getRecord(pCfgDungeon->group_id) + 1;
			player->updateRecord(pCfgDungeon->group_id, newCount);
			int32_t groupId = pCfgDungeon->group_id;
			player->GetPlayerHuoYueDu().AddHuoYueDuRecord(2, groupId, 0);
			int32_t curCount = player->getRecord(pCfgDungeon->group_id);
			player->m_PlayerDailyActivity.AddDungeonRecord(pCfgDungeon->type, curCount, 0);
		}

		if ( pCfgDungeon->type == 22 )
			player->SendNewEquipDungeonIconState();

		LogDungeon logDungeon;
		memset(&logDungeon, 0, sizeof(logDungeon));
		logDungeon.cid = player->getCid();
		logDungeon.did = nDungeonId;
		logDungeon.type = pDungeon->getDungeonType();
		logDungeon.level = player->getLevel();
		logDungeon.start_time = pDungeon->GetStartTime();
		DBService* pDB = Answer::Singleton<DBService>::instance();
		pDB->insertDungeon(player->getConnId(), &logDungeon);

		player->m_CNationalDayHd.AddNationalValue(NATIONAL_HD_TYPE::HHT_YJSK, 1, pCfgDungeon->group_id);
	}
	return 0;
}

// ======== P0-b: 核心网络包处理器 ========

int32_t Player::onMove( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;
	if ( IsInStall() )
		return 10002;
	if ( HasBuffState(CObjState::OBS_BINGDONG) || HasBuffState(CObjState::OBS_YUNXUAN)
		|| HasBuffState(CObjState::OBS_SLEEP) || HasBuffState(CObjState::OBS_PLYSIS)
		|| HasBuffState(CObjState::OBS_FROZEN) )
		return 10002;
	if ( m_pMap->GetMapParam() == 21 )
		return 10002;

	int64_t Tick = getTick();
	if ( !GetCharSkill().CanUseSkillAndMove(Tick, 0) )
	{
		setStand();
		return 10002;
	}

	BreakGather(1);
	int32_t ProcId = inPacket->getProc();
	LogProc(ProcId);

	int16_t currentX = inPacket->readInt16();
	int16_t currentY = inPacket->readInt16();
	int16_t targetX = inPacket->readInt16();
	int16_t targetY = inPacket->readInt16();
	int16_t finalX = inPacket->readInt16();
	int16_t finalY = inPacket->readInt16();
	inPacket->readInt8();

	Tile* pCurrentTile = m_pMap->getTile(currentX, currentY);
	Tile* pTargetTile = m_pMap->getTile(targetX, targetY);
	Tile* pFinalTile = m_pMap->getTile(finalX, finalY);

	if ( GetStartProtect() > 0 && (currentX != targetX || currentY != targetY) )
		SetStartProtect(0);

	if ( pCurrentTile && pTargetTile && pFinalTile )
	{
		Position pos(currentX, currentY);
		Position CurrentTile = StaticObj::getCurrentTile(this);
		int32_t ndistan = CurrentTile.tileDistance(pos);
		if ( ndistan <= 3 )
		{
			setTargetTile(targetX, targetY);
			m_extCharPet.SetTargetTile(targetX, targetY, getDirection());
			m_CharLittlerhelper.SetTargetTile(targetX, targetY, getDirection());
			broadcastMove();
			return 0;
		}
		else
		{
			Position curPos = StaticObj::getCurrentTile(this);
			instantMove(curPos.x, curPos.y, InstanceMoveReason::IMR_PULL_BACK, 0);
			return 10002;
		}
	}
	return 10002;
}

int32_t Player::onTrailerMove( Answer::NetPacket *inPacket )
{
	if ( !m_pMap || !m_trailer || !inPacket )
		return 10002;

	int32_t mapId = inPacket->readInt32();
	int16_t currentX = inPacket->readInt16();
	int16_t currentY = inPacket->readInt16();
	int16_t targetX = inPacket->readInt16();
	int16_t targetY = inPacket->readInt16();

	if ( StaticObj::getMapId(m_trailer) != mapId )
		return 10002;

	Position pos = StaticObj::getCurrentPixel(this);
	Position CurrentPixel = StaticObj::getCurrentPixel(m_trailer);
	double Dist = CurrentPixel.distance(pos);

	if ( Dist < 700.0 )
	{
		Position Pixel = Map::tileToPixel(targetX, targetY);
		Position myPixel = StaticObj::getCurrentPixel(this);
		double DistTar = myPixel.distance(Pixel);
		if ( DistTar < 700.0 )
			return m_trailer->move(mapId, currentX, currentY, targetX, targetY, 0, 0, Direction::DOWN);
		return 10002;
	}
	else
	{
		Position curPos(currentX, currentY);
		Position trailerTile = StaticObj::getCurrentTile(m_trailer);
		int32_t ndistan = trailerTile.tileDistance(curPos);
		if ( ndistan > 3 )
		{
			Position tPos = StaticObj::getCurrentTile(m_trailer);
			m_trailer->instantMove(tPos.x, tPos.y, InstanceMoveReason::IMR_PULL_BACK, 0);
		}
		return 10002;
	}
}

int32_t Player::onJump( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;
	if ( HasBuffState(CObjState::OBS_BINGDONG) || HasBuffState(CObjState::OBS_YUNXUAN)
		|| HasBuffState(CObjState::OBS_SLEEP) || HasBuffState(CObjState::OBS_PLYSIS)
		|| HasBuffState(CObjState::OBS_FROZEN) )
		return 10002;

	BreakGather(1);
	int16_t currentX = inPacket->readInt16();
	int16_t currentY = inPacket->readInt16();
	int16_t targetX = inPacket->readInt16();
	int16_t targetY = inPacket->readInt16();

	if ( !m_pMap->isWalkablePosition(targetX, targetY) )
		return 10002;

	Position pos(targetX, targetY);
	Position CurrentTile = StaticObj::getCurrentTile(this);
	int32_t dist = CurrentTile.tileDistance(pos);
	if ( dist > 5 )
		return 10002;

	setTargetTile(targetX, targetY);
	broadcastMove();
	return 0;
}

int32_t Player::onHit( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;
	if ( HasBuffState(CObjState::OBS_CHENMO) || HasBuffState(CObjState::OBS_YUNXUAN)
		|| HasBuffState(CObjState::OBS_SLEEP) || HasBuffState(CObjState::OBS_PLYSIS)
		|| HasBuffState(CObjState::OBS_FROZEN) )
		return 10002;

	BreakGather(1);
	int16_t currentX = inPacket->readInt16();
	int16_t currentY = inPacket->readInt16();
	int16_t targetX = inPacket->readInt16();
	int16_t targetY = inPacket->readInt16();

	if ( !m_pMap->isWalkablePosition(targetX, targetY) )
		return 10002;

	Position targetPos(targetX, targetY);
	Position CurrentTile = StaticObj::getCurrentTile(this);
	int32_t distToTarget = CurrentTile.tileDistance(targetPos);

	if ( distToTarget > 16 )
	{
		Position curPos(currentX, currentY);
		int32_t distToCurrent = CurrentTile.tileDistance(curPos);
		Position curPos2(currentX, currentY);
		Position targetPos2(targetX, targetY);
		int32_t distCurrentToTarget = curPos2.tileDistance(targetPos2);

		if ( distToCurrent <= 6 && distCurrentToTarget <= 10 )
		{
			instantMove(targetX, targetY, InstanceMoveReason::IMR_HIT, 0);
			return 0;
		}
		Position myPos = StaticObj::getCurrentTile(this);
		instantMove(myPos.x, myPos.y, InstanceMoveReason::IMR_PULL_BACK, 0);
		return 10002;
	}

	instantMove(targetX, targetY, InstanceMoveReason::IMR_HIT, 0);
	return 0;
}

int32_t Player::onSwitchPkMode( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t pkMode = inPacket->readInt32();
	if ( getLevel() <= 69 )
		return 10002;
	if ( pkMode == 2 && !IsInTeam() )
		return 10002;
	if ( pkMode == 3 && getFamilyId() <= 0 )
		return 10002;
	if ( pkMode == 5 )
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		if ( pGS->getLine() != 9 )
			return 10002;
	}

	if ( !m_pMap->IsPkDisabled() && pkMode > 0 && pkMode <= 7 )
	{
		if ( pkMode != 1 )
			m_chr.pk_time = 0;
		setPkMode(pkMode, 1);
		GameService* pGS = Answer::Singleton<GameService>::instance();
		pGS->replySuccess(getConnId(), getGateIndex(), inPacket->getProc(), pkMode);
	}
	return 0;
}

int32_t Player::onSafeRevive( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	if ( StaticObj::InDungeon(this) )
	{
		if ( m_pMap )
		{
			m_pMap->onPlayerSafeRevive(this);
			if ( m_pMap->hasAutoFight() )
				GetCharLittlerHelper().OnAutoWork();
		}
		return 0;
	}

	int32_t Now = getNow();
	if ( Now >= m_extOperateLimit.GetLimitCount(1111) )
	{
		safeRevive();
		if ( m_pMap && m_pMap->hasAutoFight() )
			GetCharLittlerHelper().OnAutoWork();
		GameService* pGS = Answer::Singleton<GameService>::instance();
		pGS->replySuccess(getConnId(), getGateIndex(), inPacket->getProc(), 0);
		return 0;
	}
	return 10002;
}

int32_t Player::onSiteRevive( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;
	if ( isAlive() )
		return 10002;

	if ( !m_pMap->IsNormalMap() && m_pMap->GetMapId() != 50129 )
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		return pGS->replyfailure(getConnId(), getGateIndex(), inPacket->getProc(), 10061, 0);
	}

	auto doRevive = [&]() {
		recalcAttr(1, 100);
		SetDieTick();
		FillMP(100);
		SetStartProtect(getNow());
		setNeedSyncSelf();
		m_pMap->addPlayer(this, 0);
		if ( m_pMap->hasAutoFight() )
			GetCharLittlerHelper().OnAutoWork();
		GameService* pGS = Answer::Singleton<GameService>::instance();
		pGS->replySuccess(getConnId(), getGateIndex(), inPacket->getProc(), 0);
	};

	if ( m_pMap->IsDungeonMap() )
	{
		if ( m_pMap->onPlayerSiteRevive(this) != 1 )
			return 10002;
		doRevive();
		return 0;
	}

	if ( GetPlayerVip().CanSiteRevive() )
	{
		GetOperateLimit().AddLimitCount(2021, 1);
		doRevive();
		return 0;
	}

	int32_t Slot = inPacket->readInt32();
	Int32Vector vSlot;
	vSlot.push_back(Slot);
	ItemData data;
	data.m_nId = 9;
	data.m_nClass = 1;
	data.m_nCount = 1;

	bool bOk = false;
	if ( m_extCharBag.RemoveItem(&vSlot, &data, ITEM_CHANGE_REASON::ICR_SITE_REVIVE)
		|| DecCurrency(CURRENCY_TYPE::CURRENCY_GOLD, 100, CURRENCY_CHANGE_REASON::GCT_LI_JI_FU_HUO, 0) )
	{
		bOk = true;
	}

	if ( bOk )
	{
		doRevive();
		return 0;
	}
	return 10002;
}

int32_t Player::onSubmitTask( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t tid = inPacket->readInt32();
	int8_t bDouble = inPacket->readInt8();

	CfgData* pCfgData = Answer::Singleton<CfgData>::instance();
	CfgTask* cfgTask = pCfgData->getTask(tid);
	if ( !cfgTask )
		return 10002;

	int32_t nTimes = 1;
	if ( bDouble > 0 )
	{
		float Rate = 1.0f;
		if ( GetPlayerVip().GetVipFlg(2) )
			Rate = 0.8f;
		if ( GetCurrency(CURRENCY_TYPE::CURRENCY_GOLD) < (int)((float)cfgTask->Double * Rate) )
			return 10002;
		nTimes = 2;
	}

	if ( m_task.submit(tid, nTimes) )
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		return pGS->replyfailure(getConnId(), getGateIndex(), inPacket->getProc(), 10070, tid);
	}

	if ( bDouble > 0 && cfgTask->Double > 0 )
	{
		float Rate = 1.0f;
		if ( GetPlayerVip().GetVipFlg(2) )
			Rate = 0.8f;
		DecCurrency(CURRENCY_TYPE::CURRENCY_GOLD, (int)((float)cfgTask->Double * Rate), CURRENCY_CHANGE_REASON::GCR_TASK_DOUBLE_REWARD, 0);
	}
	return 0;
}

int32_t Player::onGamePublicChat( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int8_t channel = inPacket->readInt8();
	std::string content;
	inPacket->readUTF8(content);
	int32_t targetId = inPacket->readInt32();

	if ( content.empty() || content.size() > 256 )
		return 10002;

	GameService* pGS = Answer::Singleton<GameService>::instance();
	if ( !pGS->ChatValidate(getConnId(), channel, content) )
		return 10002;

	pGS->broadcastChat(getConnId(), getGateIndex(), channel, getCid(), getName(), content, targetId);
	return 0;
}

int32_t Player::onCrossPrivateChat( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t targetCid = inPacket->readInt32();
	std::string content;
	inPacket->readUTF8(content);

	if ( content.empty() || content.size() > 256 )
		return 10002;

	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->sendCrossPrivateChat(getConnId(), getGateIndex(), getCid(), targetCid, content);
	return 0;
}

int32_t Player::onPickDropItem( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t dropId = inPacket->readInt32();
	m_pMap->onPickDropItem(this, dropId);
	return 0;
}

int32_t Player::onSwitchMap( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t targetMapId = inPacket->readInt32();
	int16_t x = inPacket->readInt16();
	int16_t y = inPacket->readInt16();

	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(targetMapId);
	if ( !pTargetMap )
		return 10002;

	if ( !pTargetMap->canEnter(this) )
		return 10002;

	switchMap(pTargetMap, x, y, 1);
	return 0;
}

int32_t Player::onLeaveDungeon( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	leaveDungeon();
	return 0;
}

int32_t Player::onEnterDungeon( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t nDungeonId = inPacket->readInt32();
	ProcId_t nProc = inPacket->getProc();
	return enterDungeon(this, nDungeonId, nProc, 0, 0, 0, 0, 0);
}

int32_t Player::onEnterChargeDungeon( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t nDungeonId = inPacket->readInt32();
	ProcId_t nProc = inPacket->getProc();
	return enterDungeon(this, nDungeonId, nProc, 0, 0, 0, 0, 0);
}

int32_t Player::onEnterActivity( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t nActivityId = inPacket->readInt32();
	CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
	return pAM->enterActivity(this, nActivityId);
}

int32_t Player::onLeaveActivity( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;
	leaveActivity();
	return 0;
}

int32_t Player::onGetAwardActivity( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t nAwardId = inPacket->readInt32();
	CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
	return pAM->getAwardActivity(this, nAwardId);
}

int32_t Player::onActivityChangeMap( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int16_t x = inPacket->readInt16();
	int16_t y = inPacket->readInt16();

	if ( !m_pMap->isWalkablePosition(x, y) )
		return 10002;

	instantMove(x, y, InstanceMoveReason::IMR_TRANSFER, 0);
	return 0;
}

int32_t Player::onLogout( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	GameService* pGS = Answer::Singleton<GameService>::instance();
	pGS->onPlayerLogout(this);
	return 0;
}

int32_t Player::onSyncTime( Answer::NetPacket *inPacket )
{
	return 0;
}

int32_t Player::onBeginGather( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t npcId = inPacket->readInt32();
	return m_pMap->onBeginGather(this, npcId);
}

int32_t Player::onEndGather( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	BreakGather(0);
	return 0;
}

int32_t Player::onSpecialPlant( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t plantId = inPacket->readInt32();
	int32_t x = inPacket->readInt16();
	int32_t y = inPacket->readInt16();
	return m_pMap->onSpecialPlant(this, plantId, x, y);
}

int32_t Player::onUseTrap( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t trapId = inPacket->readInt32();
	return m_pMap->onUseTrap(this, trapId);
}

int32_t Player::onFamilyWarActivePillar( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t pillarId = inPacket->readInt32();
	CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
	pAM->onFamilyWarActivePillar(this, pillarId);
	return 0;
}

int32_t Player::onDungeonBuildTower( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t towerType = inPacket->readInt32();
	int16_t x = inPacket->readInt16();
	int16_t y = inPacket->readInt16();
	return pDungeon->buildTower(this, towerType, x, y);
}

int32_t Player::onDungeonBuyTower( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t towerId = inPacket->readInt32();
	return pDungeon->buyTower(this, towerId);
}

int32_t Player::onDungeonStart( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	pDungeon->start(0);
	return 0;
}

int32_t Player::onDungeonSelectReward( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t rewardIndex = inPacket->readInt32();
	return pDungeon->selectReward(this, rewardIndex);
}

int32_t Player::onDungeonSummonBoss( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t bossId = inPacket->readInt32();
	return pDungeon->summonBoss(this, bossId);
}

int32_t Player::onBuyDungeonEnterTime( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	int32_t dungeonId = inPacket->readInt32();
	return m_extCharTeamDungeon.onBuyDungeonEnterTime(this, dungeonId);
}

int32_t Player::onDungeonSummon( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t summonType = inPacket->readInt32();
	return pDungeon->summon(this, summonType);
}

int32_t Player::onDungeonQuickDone( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	pDungeon->quickDone(this);
	return 0;
}

int32_t Player::onDungeonSaoDang( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t count = inPacket->readInt32();
	return pDungeon->saoDang(this, count);
}

int32_t Player::onDungeonReset( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	pDungeon->reset(this);
	return 0;
}

int32_t Player::onGuessTheSize( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int8_t guess = inPacket->readInt8();
	return pDungeon->guessTheSize(this, guess);
}

int32_t Player::onDungeonYJSKGuWu( Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 10002;

	Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
	if ( !pDungeon )
		return 10002;

	int32_t type = inPacket->readInt32();
	return pDungeon->yjskGuWu(this, type);
}

int32_t Player::onDungeonNpc( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pMap )
		return 10002;

	int32_t npcId = inPacket->readInt32();
	return m_pMap->onDungeonNpc(this, npcId);
}

int32_t Player::onKillMonster( Unit *pMonster )
{
	if ( !pMonster )
		return 0;

	m_task.onKillMonster(pMonster);
	m_extCharSkill.onKillMonster(pMonster);
	m_PlayerDailyActivity.OnKillMonster(pMonster);
	return 0;
}

// ======== P0-c: 信息发送器 ========

void Player::sendBasicInfo( int32_t reason )
{
	if ( reason == 3 )
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2828);
		if ( !packet ) return;
		packet->writeInt32(0);
		packet->setSize(packet->getWOffset());
		pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
	}

	SyncTime();
	sendChrLoginInInfo();
	sendChrInfo();
	sendCharAttrInfo();
	m_extCurrency.SendCurrencyInfo(1);
	m_extCharBag.SendBagItem();
	m_extCharBag.SendBagSellItem();
	m_extCharBag.SendLimitCount();
	m_extEquip.SendEquipInfo();
	m_extEquip.SendGemInfo();
	m_extEquip.SendPosLevelInfo();
	m_extEquip.SendStrenGthenInfo();
	m_PlayerDepot.SendDepotCurrency();
	m_PlayerDepot.SendDepotInfo();
	m_PlayerDepot.SendDepotItem();
	m_PlayerVip.SendVipInfo();
	m_extCharSkill.SendTalentInfo();
	m_extCharSkill.SendTalentAddon();
	m_extCharPet.SendPetInfo();
	m_task.sendTaskList();
	m_extMagicBox.SendItemCombiPoint();
	m_PlayerDailyActivity.SendSearchBackInfo();
	m_PlayerChouJiang.SendChouJiangItem();
	m_CBossKilledReward.SendBossKilledInfo();
	sendAutoFight();
	sendSystemSetting();
	sendChrRecord();
	sendLoginInfo();
	m_CSpecialEquip.SendActivationInfo();
	m_extTaskCycle.SendTaskCycle();
	m_CMoneyRewardTask.sendTaskInfo();
	m_CMoneyRewardTask.SendPdbfTaskInfo();
	m_CMoneyRewardTask.SendBackEquipTaskInfo();
	m_CMoneyRewardTask.SendTrailerInfo();
	m_CMoneyRewardTask.SendXiangYaoTaskInfo();
	m_CMoneyRewardTask.SendShenWeiTaskInfo();
	m_PlayerDailyActivity.SendDailyActivityInfo();
	m_extCharWorship.SendWorshipInfo();
	m_PlayerQiFu.SendQiFuInfo();
	m_PlayerHuoYueDu.SendHuoYueDuInfo();
	m_PlayerShangCheng.SendLimitInfo();
	m_extCharTitle.SendTitleInfo();
	m_FRiendExp.SendDieRecord();
	m_FRiendExp.SendDieBoard();
	m_PlayerFaBao.SendAllFaBaoInfo();
	m_CCharWuHun.sendWuHunInfo();
	m_CWuHunShop.sendShopRefreshTimes();
	m_extCharJueWei.sendJueWeiInfo();
	m_extCharWing.SendWingInfo();
	m_CGoblin.SendAllGoblinInfo();
	m_extShiZhuang.SendShiZhuangInfo();
	m_CGoblin.SendAllShouHuRefiningInfo();
	m_CGoblin.SendAllWingEquipPolishInfo();
	m_CGoblin.SendAllMoFuZhuNengInfo();
	m_CGoblin.SendAllWingEquipRefiningInfo();
	m_CGoblin.SendAllVipEquipPosLevelInfo();
	m_extCharFamily.SendHoe();
	m_CMingGeExt.SendMingGeBagInfo(1);
	m_CMingGeExt.SendMingGeBagInfo(2);
	m_CMingGeExt.SendMingGeBagInfo(3);
	m_CMingGeExt.SendMingGeInfo();
	m_CKunExt.SendKunLingInfo();
	m_CKunExt.SendLingZhuBagAllItem();
	m_CKunExt.SendDanTianInfo(-1);
	m_CKunExt.SendLingZhuPosInfo(-1);
	m_CGongMing.SendGongMinInfo();
	m_extEquip.SendShenYaoPosLevelInfo();
	m_CXinMo.SendXiMoInfo();
	m_CXinMo.SendAllItem();
	m_CXinMo.SendXinMoQiQingLevel(0);
	m_CXinMo.SendXinQingInfo();
	m_PlayerVip.SendClubInfo();
	m_CSpecialEquip.SendActivationInfo();
	m_CRongHe.SendAllRongHeInfo();
	SendJingLiValue();
	m_CharLittlerhelper.SendCharLittlerhelper();
	m_PlayerYunYingHD.SendShouChongInfo();
	SendCycleTowerInfo();
	sendActionList();
	SendHDIcon();
}

void Player::sendLoginInfo()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2718);
	if ( !packet ) return;

	packet->writeInt32(m_chr.last_task_id);
	packet->writeInt32(m_sysUser.adult);
	packet->writeInt32(m_sysUser.total_online_time);
	packet->writeInt32(getRecord(1009));

	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	packet->writeInt8(pCfg->getServerType());
	packet->writeInt32(pCfg->getServerStartTime(SERVER_TYPE::SVT_NORMAL));
	packet->writeInt32(pCfg->getServerStartDayZeroTime(SERVER_TYPE::SVT_NORMAL));
	packet->writeInt32(pCfg->getServerDiffDay(SERVER_TYPE::SVT_NORMAL));
	packet->writeInt32(pCfg->getServerStartTime(SERVER_TYPE::SVT_UNITE));
	packet->writeInt32(pCfg->getServerStartDayZeroTime(SERVER_TYPE::SVT_UNITE));
	packet->writeInt32(pCfg->getServerDiffDay(SERVER_TYPE::SVT_UNITE));
	packet->writeInt32(m_chr.create_time);
	packet->writeInt32(m_sysUserPreventWallow.isGrowUp);
	packet->writeInt32(getRecord(1011));
	packet->writeInt32(m_sysUser.continue_login_count);

	CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
	packet->writeInt64(pAM->GetCityWarWinner(getConnId()));

	std::string crossTowerName;
	pAM->GetCrossTowerName(crossTowerName);
	packet->writeUTF8(&crossTowerName);
	packet->writeInt64(pAM->GetCrossTowerWinner());

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendChrInfo()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2755);
	if ( !packet ) return;

	packet->writeInt64(getCid());

	std::string name;
	getName(name);
	packet->writeUTF8(&name);

	packet->writeInt64(getFamilyId());

	std::string familyName;
	getFamilyName(familyName);
	packet->writeUTF8(&familyName);

	packet->writeInt8(getSex());
	packet->writeInt8(getJob());
	packet->writeInt16(getLevel());
	packet->writeInt64(getExp());
	packet->writeInt64(GetLevelExp());
	packet->writeInt32(getHP());
	packet->writeInt32(GetMP());
	packet->writeInt32(m_extCharSkill.GetPower());
	packet->writeInt32(m_nJumpEnergy);
	packet->writeInt32(m_extCharTitle.GetDressTitleId());
	packet->writeInt32(getPkValue());
	packet->writeInt8(getPkMode());

	int32_t pkProtect = getPkProtectTime() - getNow();
	packet->writeInt32(pkProtect > 0 ? pkProtect : 0);

	packet->writeInt8(m_extFightChecker.IsBuleName());
	packet->writeInt8(m_extOperateLimit.CheckIsLimitedForever(37203));
	packet->writeInt8(IsInStall());

	m_extCharTencent.AppendInfo(packet);
	packet->writeInt32(m_extCharTencent.GetEndTime());
	m_Vplan.AppendYYInfo(packet);
	m_Vplan.AppendSwVipInfo(packet);

	std::string platform;
	GetPlatform(platform);
	if ( platform == "37wan" )
		packet->writeInt8(m_Vplan.GetPlatformVipLevel());
	else
		packet->writeInt8(0);

	packet->writeInt32(m_extCharCarrier.GetCarrierId());
	packet->writeInt32(getHP());
	packet->writeInt32(getKunLi());
	packet->writeInt8(GetTotalPayGold() > 0 ? 1 : 0);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendChrLoginInInfo()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2802);
	if ( !packet ) return;

	packet->writeInt64(m_sysUser.uid);
	packet->writeInt64(m_chr.cid);
	packet->writeInt8(m_sysUser.gm_level);

	CfgData* pCfg = Answer::Singleton<CfgData>::instance();
	packet->writeInt8(pCfg->getDebug());
	packet->writeInt32(pGS->getLine());

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendGainInfo( int32_t type, int64_t value, BenefitType benefitType )
{
	if ( benefitType == BenefitType::BT_NORMAL && !value )
		return;

	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2763);
	if ( !packet ) return;

	packet->writeInt32(type);
	packet->writeInt64(value);
	packet->writeInt32((int32_t)benefitType);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendActivityGain( int32_t activityId, int32_t exp, int32_t money, int32_t isEnd )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2764);
	if ( !packet ) return;

	packet->writeInt32(activityId);
	packet->writeInt32(exp);
	packet->writeInt32(money);
	packet->writeInt32(isEnd);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendBuyItemInfo( int32_t item_id, int32_t item_type, int32_t count, int32_t money, int32_t index )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2765);
	if ( !packet ) return;

	packet->writeInt32(item_id);
	packet->writeInt32(item_type);
	packet->writeInt32(count);
	packet->writeInt32(money);
	packet->writeInt32(index);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendSellItemInfo( int32_t item_id, int32_t item_type, int32_t count, int32_t money )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2766);
	if ( !packet ) return;

	packet->writeInt32(item_id);
	packet->writeInt32(item_type);
	packet->writeInt32(count);
	packet->writeInt32(money);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendItemEffect( const std::string &effect )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2762);
	if ( !packet ) return;

	packet->writeUTF8(&effect);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendKillerRankSelf()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27F2);
	if ( !packet ) return;

	packet->writeInt32(getRecord(1010));

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendPreventWallow()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2823);
	if ( !packet ) return;

	packet->writeInt32(m_sysUserPreventWallow.isGrowUp);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendActionList()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27A4);
	if ( !packet ) return;

	packet->writeInt32(m_actions[12].id);
	packet->writeInt32(m_actions[12].type);
	for ( int32_t i = 1; i <= 10; ++i )
	{
		packet->writeInt32(m_actions[i].id);
		packet->writeInt32(m_actions[i].type);
	}

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendAutoFight()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27A5);
	if ( !packet ) return;

	std::string val(m_autoFight);
	packet->writeUTF8(&val);
	std::string pickStr(m_autoFight.pick);
	packet->writeUTF8(&pickStr);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendSystemSetting()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27A6);
	if ( !packet ) return;

	int32_t nSize = (int32_t)m_SystemSetting.size();
	packet->writeInt32(nSize);
	for ( auto it = m_SystemSetting.begin(); it != m_SystemSetting.end(); ++it )
	{
		packet->writeInt32(it->first);
		packet->writeInt32(it->second);
	}

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendKilledByPlayer( CharId_t cid, const std::string &name )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27B0);
	if ( !packet ) return;

	packet->writeInt64(cid);
	packet->writeUTF8(&name);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendUpdateSocialPlayerInfo( PlayerInfoIndex index, int32_t value )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_PROC, 0x4E33);
	if ( !packet ) return;

	packet->writeInt64(getCid());
	packet->writeInt32((int32_t)index);
	packet->writeInt64(value);

	packet->setSize(packet->getWOffset());
	pGS->sendPacket(getConnId(), packet);
}

void Player::sendGambel( const MemChrBagVector& item )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27A7);
	if ( !packet ) return;

	int32_t nSize = (int32_t)item.size();
	packet->writeInt32(nSize);
	for ( int32_t i = 0; i < nSize; ++i )
	{
		packet->writeInt32(item[i].id);
		packet->writeInt32(item[i].count);
	}

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::SendHDIcon()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27B1);
	if ( !packet ) return;

	m_PlayerYunYingHD.SendEveryDayChongZhiIcon(packet);
	m_PlayerYunYingHD.SendEveryDayXiaoFeiIcon(packet);
	m_CKiaFuRecharge.SendIconState(packet);
	m_CNationalDayHd.SendIconState(packet);
	m_PlayerVip.SendVipGiftIcon(packet);
	m_CMonthlyChouJiang.SendMonthlyChouJiangIcon(packet);
	m_PlayerDailyActivity.SendJiangLiDaTingIcon(packet);
	m_CDaTingReward.SendDaTingIcon(packet);
	m_PlayerTouZi.SendTouZiIcon(packet);
	m_extCharTitle.SendTitleIcon(packet);
	m_CGuardPrivilege.SendIconState(packet);
	m_CSuperTeHui.SendIconState(packet);
	m_CGoblin.SendIconState(packet);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

// ======== P0-d: 空壳函数补全 ========

void Player::onKillMonster( int32_t mid, int32_t groupId, int32_t level, int32_t exp, bool isBoss, bool bKiller )
{
	if ( bKiller )
	{
		if ( isBoss )
			GetPlayerHuoYueDu().AddHuoYueDuRecord(4, 0, 0);
		GetPlayerHuoYueDu().AddHuoYueDuRecord(3, 0, 0);
	}

	m_task.updateTaskMonster(mid, groupId, level);

	int32_t ExpRate = 0;
	int32_t nCurLevel = getLevel();
	int32_t tLevel = nCurLevel - level;
	float LevelRatio = 1.0f;

	if ( !isBoss && level <= 179 )
	{
		if ( tLevel < -30 )
			LevelRatio = 1.5f;
		else if ( tLevel < -15 )
			LevelRatio = 1.2f;
		else if ( tLevel <= 14 )
			LevelRatio = 1.0f;
		else if ( tLevel <= 29 )
			LevelRatio = 0.8f;
		else if ( tLevel <= 59 )
			LevelRatio = 0.3f;
		else
			LevelRatio = 0.1f;
	}

	ExpRate = GetAllExpRate();
	int32_t nFinalExp = (int)(((float)ExpRate / 100.0f + 1.0f) * (float)exp * LevelRatio);
	if ( !bKiller )
		nFinalExp /= 2;

	int32_t baseExp = (int)((float)exp * LevelRatio);
	addExp(nFinalExp, baseExp, 1);

	if ( StaticObj::InDungeon(this) )
	{
		Dungeon* pDungeon = dynamic_cast<Dungeon*>(m_pMap);
		if ( pDungeon && pDungeon->getDungeonType() == 23 )
			pDungeon->AddMonsterExp(nFinalExp);
	}

	CfgData* pCfgData = Answer::Singleton<CfgData>::instance();
	CfgMonsterTaskDropVector* pCfgMonsterTaskDrop = pCfgData->getMonsterTaskDrop(mid);
	if ( pCfgMonsterTaskDrop )
	{
		for ( auto it = pCfgMonsterTaskDrop->begin(); it != pCfgMonsterTaskDrop->end(); ++it )
		{
			int32_t randVal = Answer::Random::generate(1, 1000);
			if ( randVal <= it->probability )
				m_task.updateTaskDrop(it->tid, it->item);
		}
	}

	int32_t randVal2 = Answer::Random::generate(1, 1000);
	if ( randVal2 <= 100 )
		m_extCharSkill.AddSuitSkillEnergy();
}

void Player::refreshDailyCheck( bool first )
{
	int32_t lastRecord = getRecord(1001);
	int32_t daydiff = Answer::DayTime::daydiff(lastRecord);

	if ( daydiff > 0 )
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		if ( pGS->getLine() == 9 )
		{
			kickBackFromCross(10115);
			return;
		}
	}

	if ( daydiff == 1 )
		++m_sysUser.continue_login_count;
	else if ( daydiff > 1 )
		m_sysUser.continue_login_count = 1;

	if ( daydiff > 0 )
	{
		if ( m_pMap && m_pMap->IsXinMoMap() )
			OnBackCity(1, 1);

		saveOnlineTime();
		clearRecordRange(2000, 19999, daydiff);
		syncTodayGoldPay();

		int32_t loginCount = getRecord(1011) + 1;
		updateRecord(1011, loginCount);

		int32_t loginRecord = getRecord(1069);
		int32_t newRecord = (loginRecord << daydiff) + 1;
		updateRecord(1069, newRecord);

		m_ExtSysMgr.OnDaySwitch(daydiff);

		SendFamilyWarIcon();

		CUniteServer* pUS = Answer::Singleton<CUniteServer>::instance();
		pUS->SendIconState(this);

		CFestivalDoubleEleven* pFDE = Answer::Singleton<CFestivalDoubleEleven>::instance();
		pFDE->SendIconState(this);

		CFestivalActivity* pFA = Answer::Singleton<CFestivalActivity>::instance();
		pFA->SendIconState(this);

		CZongHeYunYingHD* pZHYHD = Answer::Singleton<CZongHeYunYingHD>::instance();
		pZHYHD->SendIconState(this);

		CKiaFuRecharge* pKFR = Answer::Singleton<CKiaFuRecharge>::instance();
		pKFR->SendIconState(this);
		pKFR->SendChouJiangIconState(this);

		COpenBeta* pOB = Answer::Singleton<COpenBeta>::instance();
		pOB->SendIconState(this);

		OnMonthSwitch();

		int32_t PetRecord = getRecord(1030);
		if ( PetRecord > 0 && getNow() >= PetRecord )
		{
			int32_t nIndex = getRecord(1031);
			CKaiFuHuoDong* pKFHD = Answer::Singleton<CKaiFuHuoDong>::instance();
			CfgKaiFuHuoDongData* pCfg = pKFHD->GetKaiFuHuoDongData(nIndex);
			if ( pCfg )
			{
				MemChrBag mailItem;
				memset(&mailItem, 0, sizeof(mailItem));
				mailItem.itemId = 2;
				mailItem.itemCount = pCfg->Conditions;
				std::string Param;
				DBService* pDB = Answer::Singleton<DBService>::instance();
				pDB->OnSendSysMail(0, getCid(), 6370, &mailItem, ITEM_CHANGE_REASON::ICR_KAI_HUO_DONG_PET, &Param, 0);
			}
			updateRecord(1030, 0);
			m_extCharPet.SendPetStaus();
		}

		int32_t Record1905 = getRecord(1905);
		if ( Record1905 > 0 )
			AddCurrency(CURRENCY_TYPE::CURRENCY_GOLD, Record1905, CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_FREE_GIFT, 0);
	}

	updateRecord(1001, getNow());
}

void Player::InitSysSetting()
{
	if ( m_systemSetting.empty() )
		return;

	StringVector mineString;
	Answer::StringUtility::split(mineString, m_systemSetting, "|");

	for ( auto it = mineString.begin(); it != mineString.end(); ++it )
	{
		StringVector StringVt;
		Answer::StringUtility::split(StringVt, *it, ":");
		if ( StringVt.size() == 2 )
		{
			int32_t Key = atoi(StringVt[0].c_str());
			int32_t Values = atoi(StringVt[1].c_str());
			m_SystemSetting[Key] = Values;
		}
	}

	int32_t key7 = 7;
	m_SystemSetting[key7] = 0;
}

void Player::minuteCheck( bool bSend )
{
	int32_t nowTime = getNow();
	tm localNow;
	getLocalNow(&localNow);

	int32_t Record = getRecord(1002);
	if ( nowTime - Record > 59 )
	{
		updateRecord(1002, nowTime);
		UpdateGmGold();
	}

	if ( m_lastLocalNow.tm_min != localNow.tm_min )
	{
		ResetJingLi();

		if ( m_pMap && m_pMap->IsXinMoMap() && 60 * localNow.tm_hour + localNow.tm_min == 1435 )
		{
			GameService* pGS = Answer::Singleton<GameService>::instance();
			Answer::NetPacket* packet = pGS->popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2D41);
			if ( packet )
			{
				packet->writeInt32(1);
				packet->setSize(packet->getWOffset());
				pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
			}
		}
	}

	if ( m_lastLocalNow.tm_mday != localNow.tm_mday )
	{
		onNewDayCome();
		CKaiFuHuoDong* pKFHD = Answer::Singleton<CKaiFuHuoDong>::instance();
		pKFHD->SendKaiFuHuoDongIcon(this);
		pKFHD->SendKaiFuPetIcon(this);
		SendCycleTowerInfo();
	}

	if ( m_lastLocalNow.tm_hour != 18 && localNow.tm_hour == 18 )
		refeshKillerRecord();

	m_lastLocalNow = localNow;
}

void Player::syncGold( int32_t nGold )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	if ( pGS->getLine() == 9 )
	{
		if ( m_sysUser.gold_pay != nGold )
		{
			m_sysUser.gold_pay = nGold;
			SendRechargeNotice(nGold);
		}
	}
	else
	{
		DBPool* pDBPool = Answer::Singleton<DBPool>::instance();
		MySqlDBGuard db(pDBPool);
		char szSQL[4096];
		memset(szSQL, 0, sizeof(szSQL));
		snprintf(szSQL, 4096, "call GetPayGold(%lld,%d,@OutPayGold)", (int64_t)m_sysUser.uid, m_sysUser.sid);
		auto result = db.query(szSQL);
		MySqlQuery query(result);
		if ( !query.eof() )
		{
			int32_t gold_pay = query.getIntValue(0, 0);
			if ( gold_pay > 0 )
			{
				m_sysUser.gold_pay = 0;
				AddCurrency(CURRENCY_TYPE::CURRENCY_GOLD, gold_pay, CURRENCY_CHANGE_REASON::GCR_RECHARGE, 0);
				m_sysUser.gold_pay_total += gold_pay;
				setNeedSyncSelf();
				syncTodayGoldPay();
				m_PlayerYunYingHD.SendShouChongInfo();
				PayedDispose(gold_pay);
			}
		}
	}
}

void Player::addLogoutPacket( int32_t reason, int32_t param )
{
	if ( m_pMap )
	{
		GameService* pGS = Answer::Singleton<GameService>::instance();
		Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 8);
		if ( packet )
		{
			packet->writeInt32(reason);
			packet->writeInt32(param);
			packet->setSize(packet->getWOffset());
			m_netPackets.push(packet);
		}
	}
	else
	{
		Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO,
			"Player::addLogoutPacket with m_pMap == NULL, cid = %lld\n", m_chr.cid);
		saveToDB(reason, param);
		GameService* pGS = Answer::Singleton<GameService>::instance();
		pGS->onPlayerLogout(this);
	}
}

void Player::kickBackFromCross( int32_t Reason )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_PROC, 0x4E2C);
	if ( packet )
	{
		packet->writeInt64(getUid());
		packet->writeInt32(getSid());
		packet->setSize(packet->getWOffset());
		pGS->sendPacket(getConnId(), packet);
		Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO,
			"Kick_back_from_cross cid=%lld\tReason=%d\n", getCid(), Reason);
	}
}

void Player::refeshKillerRecord()
{
	int32_t Record = getRecord(1010);
	updateRecord(1010, Record);
}

void Player::EnterMapGongGao( int32_t gongGaoId, int32_t mapId )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27B2);
	if ( !packet ) return;

	packet->writeInt32(gongGaoId);
	packet->writeInt32(mapId);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::broadcastLeave()
{
	if ( !m_pMap ) return;
	m_pMap->broadcastLeave(this);
}

// ======== P0-f+P0-g: 剩余缺失方法+空壳函数补全 ========

void Player::recalcAttr( bool bNow, bool bInit )
{
	if ( !bNow )
	{
		m_needRecalAttr = true;
		return;
	}

	m_needRecalAttr = false;
	CObjAttrs oldAttr;
	memcpy(&oldAttr, GetBaseAttr(), sizeof(oldAttr));

	m_BeiGongAttr.clear();
	ResetAttrs();
	setBaseAttr();

	m_extCharSkill.AddCharAttr();
	m_extEquip.AddCharAttr();
	m_extCharPet.AddCharAttr();
	m_extCharWing.AddCharAttr();
	m_extCharJueWei.AddCharAttr();
	m_PlayerFaBao.AddPlayerAttr();
	m_extCharTitle.AddCharAttr();
	m_PlayerVip.AddVipAttr();
	m_extCharFamily.AddSkillAttr();
	m_XingMai.AddCharAttr();
	m_TianLing.AddCharAttr();
	m_CSpecialEquip.AddCharAttr();
	m_Curse.AddCharAttr();
	m_ShenWei.AddCharAttr();
	m_CCharWuHun.AddCharAttr();
	m_CGoblin.AddChrAttr();
	m_extShiZhuang.AddPlayerAttr();
	m_Vplan.AddAttr();
	m_CGoblin.AddShouHuChrAttr();
	m_CGoblin.AddWingEquipPolishChrAttr();
	m_CGoblin.AddWingEquipRefiningChrAttr();
	m_CGoblin.AddVipEquipPosLevelCharAttr();
	m_CMingGeExt.AddAttr();
	m_CKunExt.AddCharAttr();
	m_CGongMing.AddCharAttr();
	m_CXinMo.AddCharAttr();

	int32_t ShiHua = getRecord(1153);
	if ( ShiHua > 0 )
		AddAttrValue(CObjAttrs::ATTR_XUAN_YUN, ShiHua);
	int32_t Valuse = getRecord(1154);
	if ( Valuse > 0 )
		AddAttrValue(CObjAttrs::ATTR_QIE_GE_PEC, Valuse);
	int32_t DropRate = getRecord(37505);
	if ( DropRate > 0 )
		AddAttrValue(CObjAttrs::ATTR_DROP_RATE, DropRate);

	int32_t PetRecord = getRecord(1030);
	if ( PetRecord > 0 )
	{
		int32_t nIndex = getRecord(1031);
		CKaiFuHuoDong* pKFHD = Answer::Singleton<CKaiFuHuoDong>::instance();
		CfgKaiFuHuoDongData* pCfg = pKFHD->GetKaiFuHuoDongData(nIndex);
		if ( pCfg )
			AddAttrValue(CObjAttrs::ATTR_QIE_GE_PEC, pCfg->PetAttr);
	}

	m_CharLittlerhelper.AddCharAttr();
	AddAppendAttr();
	CalBattle();
	adjustUnitAttr();

	if ( !bInit )
	{
		AttrAddonList addAttrs;
		CObjAttrs newAttr;
		memcpy(&newAttr, GetBaseAttr(), sizeof(newAttr));

		for ( int32_t i = 0; i <= 49; ++i )
		{
			int32_t nOldAttr = oldAttr.GetAttr((CObjAttrs::Index_T)i);
			int32_t nNewAttr = newAttr.GetAttr((CObjAttrs::Index_T)i);
			if ( nNewAttr > nOldAttr )
			{
				AttrAddon addon;
				addon.index = i;
				addon.addon = nNewAttr - nOldAttr;
				addAttrs.push_back(addon);
			}
		}

		if ( !addAttrs.empty() )
			sendAttrAddon(addAttrs);
	}

	setNeedSync();
	setNeedSyncAttr();
	SendBeiGongAttr();
}

void Player::sendCharAttrInfo()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2756);
	if ( !packet ) return;

	appendCharAttrInfo(packet);
	packet->writeInt32(getBattle());
	packet->writeInt32(GetAllMoneyRate());

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::appendCharAttrInfo( Answer::NetPacket* packet )
{
	if ( !packet ) return;
	for ( int32_t i = 1; i <= 49; ++i )
		packet->writeInt32(GetAttrValue((CObjAttrs::Index_T)i));
}

void Player::sendAttrAddon( const AttrAddonList& attrs )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x2757);
	if ( !packet ) return;

	packet->writeInt32((int32_t)attrs.size());
	for ( auto it = attrs.begin(); it != attrs.end(); ++it )
	{
		packet->writeInt8(it->index);
		packet->writeInt32(it->addon);
	}

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

bool Player::checkNetPackets()
{
	while ( true )
	{
		Answer::NetPacket* packet = m_netPackets.pop();
		if ( !packet )
			break;

		ProcId_t nProc = packet->getProc();

		if ( !isAlive() && !isDeadProc(nProc) )
		{
			packet->destroy();
			continue;
		}

		NetPacketHandler handler = getNetPacketHandler(nProc);
		if ( handler )
		{
			int32_t ret = handler(this, packet);
			if ( ret == 1 )
			{
				packet->destroy();
				return false;
			}
		}

		int32_t nErr = m_ExtSysMgr.DispatchNetDatas(nProc, packet);

		if ( NeedJianKong() )
		{
			proc_log stu;
			stu.log_Sid = getSid();
			stu.log_time = getNow();
			std::string passport;
			GetPassport(passport);
			stu.passport = passport;
			stu.cid = getCid();
			std::string name;
			getName(name);
			stu.name = name;
			stu.op_time = getNow();
			stu.proc_id = packet->getProc();
			DBService* pDB = Answer::Singleton<DBService>::instance();
			pDB->AddPlatformLog(getConnId(), PLATFORM_LOG_DATA_TYPE::PLDT_PROC, &stu);
		}

		packet->destroy();

		if ( nProc == 8 )
			return true;
	}
	return false;
}

void Player::saveToDB( int32_t reason, int32_t param )
{
	PlayerDBData dbData;
	SaveDBData(dbData);

	int32_t logout_time = getNow();
	dbData.chr.data.last_logout_time = logout_time;
	dbData.sysUser.data.last_logout_time = logout_time;

	saveOnlineTime();
	DBService* pDB = Answer::Singleton<DBService>::instance();
	pDB->savePlayer(getConnId(), reason, param, &dbData);
}

int32_t Player::verifyBagInfo( const Int32Vector& vSlot, int32_t nType, int32_t nNeedCount )
{
	int32_t nCount = 0;
	for ( size_t i = 0; i < vSlot.size(); ++i )
	{
		MemChrBag* pItem = m_extCharBag.GetItemBySlot(vSlot[i]);
		if ( !pItem )
			return -1;
		if ( nType > 0 && pItem->itemId != nType )
			return -1;
		++nCount;
	}
	if ( nCount < nNeedCount )
		return -1;
	return 0;
}

int32_t Player::verifyBagInfoForGroup( const Int32Vector& vSlot, const ItemData& data, int32_t nNeedCount )
{
	int32_t nCount = 0;
	for ( size_t i = 0; i < vSlot.size(); ++i )
	{
		MemChrBag* pItem = m_extCharBag.GetItemBySlot(vSlot[i]);
		if ( !pItem )
			return -1;
		if ( pItem->itemId != data.m_nId )
			return -1;
		nCount += pItem->itemCount;
	}
	if ( nCount < nNeedCount )
		return -1;
	return 0;
}

void Player::onDamageEvent( int32_t damage, UnitHandle launcher, int32_t skillId )
{
	if ( damage <= 0 ) return;

	AddHp(-damage);
	if ( getHP() <= 0 )
	{
		m_bDie = true;
		m_nDieTick = getTick();
		onDamagedEvent(launcher, skillId);
	}
}

void Player::onDamagedEvent( UnitHandle killer, int32_t skillId )
{
	if ( !m_bDie ) return;

	if ( killer )
	{
		Unit* pKiller = (Unit*)killer;
		if ( pKiller->getUnitId() == getUnitId() )
			return;

		m_chr.kill_count++;
		sendKilledByPlayer(getCid(), getName());
	}

	SetDieTick();
	m_extCharSkill.onPlayerDie();
	m_extFightChecker.OnPlayerDie();

	if ( m_pMap )
		m_pMap->onPlayerDie(this);
}

void Player::updatePkValue( int32_t delta )
{
	if ( delta == 0 ) return;

	int32_t oldPkValue = m_chr.pk_value;
	m_chr.pk_value += delta;
	if ( m_chr.pk_value < 0 )
		m_chr.pk_value = 0;

	int32_t maxPkValue = 9999;
	if ( m_chr.pk_value > maxPkValue )
		m_chr.pk_value = maxPkValue;

	if ( oldPkValue != m_chr.pk_value )
		setNeedSyncSelf();
}

void Player::addSkill( int32_t skillid, int32_t level )
{
	m_extCharSkill.addSkill(skillid, level);
}

void Player::removeSkill( int32_t skillid )
{
	m_extCharSkill.removeSkill(skillid);
}

void Player::DieResetXp()
{
	m_extCharSkill.DieResetXp();
}

void Player::sendChrRecord()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27A8);
	if ( !packet ) return;

	m_extOperateLimit.SendRecordList(packet);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendSkillList()
{
	m_extCharSkill.SendSkillList();
}

void Player::sendNewSkill( int32_t skillid )
{
	m_extCharSkill.SendNewSkill(skillid);
}

void Player::sendPvpInfo()
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27B3);
	if ( !packet ) return;

	packet->writeInt32(getPkValue());
	packet->writeInt8(getPkMode());
	packet->writeInt32(getPkProtectTime());

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendGetGoldInfo()
{
	m_extCurrency.SendCurrencyInfo(0);
}

void Player::sendYellowStone()
{
	m_extCharTencent.SendBlueStoneIcon();
}

void Player::sendJungongChangeInfo( int32_t addon, BenefitType bnfType )
{
	sendGainInfo(1, addon, bnfType);
}

void Player::sendWuhuenChangeInfo( int32_t addon, BenefitType bnfType )
{
	sendGainInfo(2, addon, bnfType);
}

void Player::sendjiangxingChangeInfo( int32_t addon, BenefitType bnfType )
{
	sendGainInfo(3, addon, bnfType);
}

void Player::sendKingdomChangeInfo( int32_t addon )
{
	sendGainInfo(4, addon, BenefitType::BT_NORMAL);
}

void Player::sendFightExpMoney( int32_t exp, int32_t kingdom_contribute )
{
	sendGainInfo(0, exp, BenefitType::BT_NORMAL);
}

void Player::sendViewStarFinished( int32_t sid, int32_t level )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27B4);
	if ( !packet ) return;

	packet->writeInt32(sid);
	packet->writeInt32(level);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendToastInfo( CharId_t cid, CharId_t beCid )
{
	GameService* pGS = Answer::Singleton<GameService>::instance();
	Answer::NetPacket* packet = pGS->popNetpacket(getConnId(), Answer::PackType::PACK_DISPATCH, 0x27B5);
	if ( !packet ) return;

	packet->writeInt64(cid);
	packet->writeInt64(beCid);

	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(getConnId(), getGateIndex(), packet);
}

void Player::sendActivityState()
{
	m_PlayerDailyActivity.SendDailyActivityInfo();
}

void Player::setTaskCanSubmit( int32_t tid )
{
	m_task.setTaskCanSubmit(tid);
}

void Player::checkTaskCanSubmit( int32_t dungeonID )
{
	m_task.checkTaskCanSubmit(dungeonID);
}

void Player::taskTalkWithNpc( int32_t npcid )
{
	m_task.talkWithNpc(npcid);
}

void Player::autoUseItem( MemChrBagVector &items )
{
	m_extCharBag.autoUseItem(items);
}

void Player::addContribution( int32_t addon, int32_t rate )
{
	m_extCharFamily.addContribution(addon, rate);
}

void Player::kingdomTaskFaile()
{
	m_task.kingdomTaskFaile();
}

void Player::setKingdomTaskState( int32_t tid, int32_t state )
{
	m_task.setKingdomTaskState(tid, state);
}

void Player::onActAddHL()
{
	GetPlayerHuoYueDu().AddHuoYueDuRecord(3, 0, 0);
}

void Player::doSkillCost( CfgSkill *pCfgSkill, MemChrSkillVector::iterator &itSkill )
{
	m_extCharSkill.doSkillCost(pCfgSkill, itSkill);
}

void Player::doSkillLevel( int32_t sid, int32_t slevel, UnitHandle target )
{
	m_extCharSkill.doSkillLevel(sid, slevel, target);
}

// ===== P6-2: Missing method implementations =====

void Player::setBaseAttr()
{
	int32_t level = getLevel();
	Job_t job = getJob();
	CfgData* pCfg = CFG_DATA;
	CfgLevelAttr levelAttr;
	pCfg->getLevelAttr(levelAttr, job, level);
	if ( levelAttr.job > 0 && levelAttr.level > 0 )
	{
		for ( auto it = levelAttr.addonattr.begin(); it != levelAttr.addonattr.end(); ++it )
		{
			AddAttrValue(it->index, it->addon);
			if ( it->index == 45 )
				AddBeiGongAttr(1, it->addon);
		}
	}
}

bool Player::isDeadProc(ProcId_t nProc) const
{
	if ( nProc > 0x4E20 && nProc <= 0x61AA )
		return true;
	if ( nProc <= 0x3A )
		return nProc >= 0x38 || nProc == 8 || nProc == 38;
	if ( nProc == 434 )
		return true;
	if ( nProc > 0x1B2 )
		return nProc == 440 || nProc == 463;
	return nProc == 197;
}

bool Player::isPreventWallow(std::string card)
{
	int nLen = card.length();
	if ( nLen != 18 )
		return true;
	if ( !CheckString(card) )
		return true;
	if ( BirthdayIsRight(card) == 0 )
		return true;
	int no[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
	const char* id = "10X98765432";
	const char* p = card.c_str();
	int sum = 0;
	for ( int i = 0; i < nLen - 1; ++i )
		sum += (p[i] - '0') * no[i];
	bool bResult = false;
	if ( (p[17] < '0' || p[17] > '9') && p[17] != 'X' && p[17] != 'x' )
		bResult = true;
	int wi = sum % 11;
	if ( p[17] == 'x' || p[17] == 'X' )
	{
		if ( id[wi] != 'x' && id[wi] != 'X' )
			return true;
	}
	else if ( id[wi] != p[17] )
	{
		return true;
	}
	return bResult;
}

Int32Vector Player::getStrategicsReadState(int32_t *pIndexArry)
{
	Int32Vector result;
	for ( int32_t i = 0; i < MAX_STRATEGICS_READ_COUNT; ++i )
	{
		int32_t nIndex = pIndexArry[i];
		result.push_back(getRecord(nIndex));
	}
	return result;
}

int32_t Player::doTeleport(int32_t aid)
{
	if ( !m_pMap )
		return 10002;
	CfgData* pCfg = CFG_DATA;
	CfgTeleport* pCfgTeleport = pCfg->getTeleport(aid);
	if ( !pCfgTeleport )
		return 10002;
	int32_t nRegionId = pCfgTeleport->regionId;
	CfgMapRegion* pCfgRegion = pCfg->getMapRegion(nRegionId);
	if ( !pCfgRegion )
		return 10002;
	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(pCfgRegion->mapid);
	if ( !pTargetMap )
		return 10002;
	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
	if ( pos.x < 0 || pos.y < 0 )
		return 10002;
	if ( m_pMap != pTargetMap )
		return switchMap(pTargetMap, pos.x, pos.y, 1);
	instantMove(pos.x, pos.y, InstanceMoveReason::IMR_TELEPORT, 0);
	return 0;
}

int32_t Player::doTeleportActivity(int32_t aid)
{
	if ( !m_pMap )
		return 10002;
	CfgData* pCfg = CFG_DATA;
	CfgActivity* activityInfo = pCfg->getActivity(aid);
	if ( !activityInfo || !activityInfo->target_mapid )
		return 10002;
	CActivityManager* pAM = Answer::Singleton<CActivityManager>::instance();
	if ( !pAM->IsActivityRunning(activityInfo->id) )
		return 10002;
	if ( activityInfo->target_regiona.empty() )
		return 10002;
	int32_t nReginId = getActivityBirthRegion(&activityInfo->target_regiona);
	CfgMapRegion* pCfgRegion = pCfg->getMapRegion(nReginId);
	if ( !pCfgRegion )
		return 10002;
	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(activityInfo->target_mapid);
	if ( !pTargetMap )
		return 10002;
	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgRegion);
	if ( pos.x < 0 || pos.y < 0 )
		return 10002;
	if ( m_pMap != pTargetMap )
		return switchMap(pTargetMap, pos.x, pos.y, 1);
	instantMove(pos.x, pos.y, InstanceMoveReason::IMR_ACTIVITY, 0);
	return 0;
}

void Player::sendPlayerEquipInfo()
{
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2774);
	if ( packet )
	{
		GetEquip().PackageEquipInfo(packet);
		packet->setSize(packet->getWOffset());
		pGS->sendPacketTo(connid, getGateIndex(), packet);
	}
}

void Player::sendEquipInfo(const MemEquip &memEquip)
{
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2775);
	if ( packet )
	{
		packet->writeInt64(memEquip.id);
		packet->writeInt32(memEquip.base);
		packet->writeInt8(memEquip.star);
		packet->writeInt32(memEquip.MapId);
		packet->writeInt32(memEquip.Mid);
		packet->writeInt32(memEquip.time);
		packet->writeUTF8(memEquip.name);
		packet->writeInt32(memEquip.Lucky);
		packet->setSize(packet->getWOffset());
		pGS->sendPacketTo(connid, getGateIndex(), packet);
	}
}

void Player::sendEquipInfo(const MemEquipVector &memEquips)
{
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2776);
	if ( packet )
	{
		packet->writeInt32(memEquips.size());
		for ( auto it = memEquips.begin(); it != memEquips.end(); ++it )
		{
			packet->writeInt64(it->id);
			packet->writeInt32(it->base);
			packet->writeInt8(it->star);
			packet->writeInt32(it->MapId);
			packet->writeInt32(it->Mid);
			packet->writeInt32(it->time);
			packet->writeUTF8(it->name);
			packet->writeInt32(it->Lucky);
		}
		packet->setSize(packet->getWOffset());
		pGS->sendPacketTo(connid, getGateIndex(), packet);
	}
}

void Player::sendPublicChat(int32_t channel, Answer::NetPacket *inPacket)
{
	if ( !inPacket )
		return;
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* chatPacket = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x27F7);
	if ( !chatPacket )
		return;
	chatPacket->writeInt32(channel);
	chatPacket->writeInt32(getLevel());
	chatPacket->writeInt8(m_sysUser.gm_level);
	chatPacket->writeInt64(getCid());
	chatPacket->writeInt32(getSid());
	chatPacket->writeUTF8(getIP());
	chatPacket->writeInt8(GetPlayerVip().GetVipType());
	chatPacket->writeInt8(GetPlayerVip().GetVipLevel());
	chatPacket->writeInt8(getSex());
	chatPacket->writeInt8(pGS->getLine());
	chatPacket->writeUTF8(getName());
	chatPacket->writeInt8(getJob());
	chatPacket->writeInt8(GetCharJueWei().GetJueWei());
	m_extCharTencent.AppendInfo(chatPacket);
	m_extVplan.AppendYYInfo(chatPacket);
	m_extVplan.AppendSwVipInfo(chatPacket);
	chatPacket->writeInt8(connid);
	chatPacket->write(inPacket->getBuffer(), inPacket->getSize());
	chatPacket->setSize(chatPacket->getWOffset());
	std::string platform = getPf();
	bool bCanSend = (platform != "37wan" && platform != "tanwan" && platform != "w360");
	if ( bCanSend || !pGS->SendChatValidate(this, channel, chatPacket) )
	{
		if ( channel == 1 || channel == 6 )
		{
			pGS->worldBroadcast(connid, chatPacket);
		}
		else if ( channel == 4 && IsInTeam() )
		{
			GetCharTeam().Broadcast(chatPacket);
		}
		else if ( channel == 5 && m_pMap )
		{
			m_pMap->broadcast(chatPacket);
		}
		else if ( channel == 7 )
		{
			pGS->broadcast(chatPacket);
		}
		else
		{
			Answer::NetPacket::destroy(chatPacket);
		}
	}
}

int32_t Player::queryAutoBuyBagInfo(const Int32Vector& vSlot, int32_t nItemId, int32_t& count, int32_t nShopId)
{
	if ( count <= 0 )
		return 0;
	int32_t nCount = count;
	int32_t slotCount = vSlot.size();
	for ( int32_t i = 0; i < slotCount; ++i )
	{
		MemChrBag bagSlot = getBagSlotData(vSlot[i]);
		if ( !bagSlot.itemId )
			return 10002;
		if ( bagSlot.itemId != nItemId )
			return 10002;
		if ( bagSlot.itemCount >= nCount )
		{
			nCount = 0;
			break;
		}
		nCount -= bagSlot.itemCount;
	}
	if ( nCount > 0 )
	{
		CfgData* pCfg = CFG_DATA;
		CfgGameShop* pCfgGameShop = pCfg->GetGameShop(nShopId);
		if ( !pCfgGameShop )
			return 10002;
		int32_t totalCost = nCount * pCfgGameShop->Price;
		int64_t nTotalGold = GetCurrency(CURRENCY_GOLD);
		if ( totalCost > nTotalGold )
			return 10002;
		DecCurrency(CURRENCY_GOLD, totalCost, GCR_AUTOBUYBAG, nShopId);
	}
	count -= nCount;
	return 0;
}

bool Player::queryBagInfo(Answer::NetPacket* inPacket, Int32Vector& vSlot)
{
	if ( !inPacket )
		return false;
	int32_t slotCount = inPacket->readInt32();
	if ( slotCount > 150 )
		return false;
	vSlot.resize(slotCount, 0);
	for ( int32_t i = 0; i < slotCount; ++i )
		vSlot[i] = inPacket->readInt32();
	return true;
}

void Player::queryBagInfoByItemId(int32_t nItemId, int32_t nCount, Int32Vector& vSlot)
{
	vSlot.clear();
	int32_t remaining = nCount;
	int32_t freeSlot = getFirstFreeSlot();
	for ( int32_t i = 0; i < freeSlot && remaining > 0; ++i )
	{
		MemChrBag bagSlot = getBagSlotData(i);
		if ( bagSlot.itemId == nItemId && bagSlot.itemCount > 0 )
		{
			vSlot.push_back(i);
			remaining -= bagSlot.itemCount;
		}
	}
}

int Player::BirthdayIsRight(std::string cardId)
{
	if ( cardId.length() != 18 )
		return 0;
	int year = (cardId[6] - '0') * 1000 + (cardId[7] - '0') * 100 + (cardId[8] - '0') * 10 + (cardId[9] - '0');
	int month = (cardId[10] - '0') * 10 + (cardId[11] - '0');
	int day = (cardId[12] - '0') * 10 + (cardId[13] - '0');
	if ( month < 1 || month > 12 )
		return 0;
	int maxDay = GetDay(year, month);
	if ( day < 1 || day > maxDay )
		return 0;
	return 1;
}

int Player::GetDay(int year, int month)
{
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ( month < 1 || month > 12 )
		return 0;
	int maxDay = days[month - 1];
	if ( month == 2 )
	{
		if ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 )
			maxDay = 29;
	}
	return maxDay;
}

bool Player::CheckString(std::string card)
{
	const char* szStr = "1234567890";
	int nLen1 = card.length();
	int nLen2 = strlen(szStr);
	for ( int i = 0; i < nLen1; ++i )
	{
		bool bFound = false;
		for ( int j = 0; j < nLen2; ++j )
		{
			if ( card[i] == szStr[j] )
			{
				bFound = true;
				break;
			}
		}
		if ( !bFound )
		{
			if ( i == 17 && (card[17] == 'x' || card[17] == 'X') )
				return true;
			return false;
		}
	}
	return true;
}

void Player::moveToReviveRegion(bool bInAct)
{
	if ( !m_pMap )
		return;
	int32_t region = m_pMap->getReviveRegion(this);
	CfgData* pCfg = CFG_DATA;
	CfgMapRegion* pCfgMapRegion = pCfg->getMapRegion(region);
	if ( !pCfgMapRegion )
		return;
	if ( !pCfg->getMap(pCfgMapRegion->mapid) )
		return;
	MapManager* pMM = Answer::Singleton<MapManager>::instance();
	Map* pTargetMap = pMM->GetMap(pCfgMapRegion->mapid);
	if ( !pTargetMap )
		return;
	Position pos = pTargetMap->getRandomWalkablePositionInRegion(pCfgMapRegion);
	if ( pos.x >= 0 && pos.y >= 0 )
	{
		if ( m_pMap == pTargetMap )
			instantMove(pos.x, pos.y, InstanceMoveReason::IMR_FU_HUO, 0);
		else
			switchMap(pTargetMap, pos.x, pos.y, 1);
	}
}

int32_t Player::getActivityBirthRegion(Int32Vector* pRegsions) const
{
	if ( !pRegsions )
		return 0;
	int32_t lenth = pRegsions->size();
	if ( lenth == 1 )
		return pRegsions->at(0);
	int32_t nIndex = RANDOM.generate(0, lenth - 1);
	return pRegsions->at(nIndex);
}

Answer::NetPacket* Player::getOtherQueryInfo()
{
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x281C);
	if ( !packet )
		return nullptr;
	packet->writeInt64(getCid());
	packet->writeInt32(getSid());
	packet->writeUTF8(getName());
	packet->writeInt32(getLevel());
	packet->writeInt8(getJob());
	packet->writeInt32(0);
	packet->writeUTF8(getFamilyName());
	packet->writeInt64(getFamilyId());
	m_extCharTencent.AppendInfo(packet);
	GetEquip().PackageEquipInfo(packet);
	appendCharAttrInfo(packet);
	packet->writeInt32(getDeadTime());
	packet->writeInt32(GetAllMoneyRate());
	packet->writeInt32(getPkValue());
	packet->writeInt32(GetCharWing().GetHuanHua());
	packet->writeInt8(10);
	for ( int8_t i = 0; i <= 9; ++i )
	{
		packet->writeInt8(i);
		packet->writeInt32(GetEquip().GetPosLevel(i));
	}
	packet->writeInt8(10);
	for ( int8_t i = 0; i <= 9; ++i )
	{
		packet->writeInt8(i);
		packet->writeInt32(GetEquip().getStrenGthenLevel(i));
	}
	GetEquip().PackageGemInfo(packet);
	m_CGoblin.AppendInfo(packet);
	GetShiZhuang().PackShiZhuangInfo(packet);
	GetEquip().PackageShenYaoPosLevelUp(packet);
	packet->setSize(packet->getWOffset());
	return packet;
}

void Player::UpdateKilledByPlayer(CharId_t KillerId)
{
	GameService* pGS = GAME_SERVICE;
	if ( pGS->getLine() != 9 )
	{
		int8_t connid = getConnId();
		Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_PROC, 0x4EB1);
		if ( packet )
		{
			packet->writeInt32(getGateIndex());
			packet->writeInt64(KillerId);
			packet->setSize(packet->getWOffset());
			pGS->sendPacket(connid, packet);
		}
	}
}

void Player::sendToastInfo(CharId_t cid, CharId_t beCid)
{
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x27B5);
	if ( !packet )
		return;
	packet->writeInt64(cid);
	packet->writeInt64(beCid);
	packet->setSize(packet->getWOffset());
	pGS->sendPacketTo(connid, getGateIndex(), packet);
}

void Player::sendActivityState()
{
	m_PlayerDailyActivity.SendDailyActivityInfo();
}

void Player::addNetPacket(Answer::NetPacket *inPacket, uint32_t rsize)
{
	if ( !inPacket || inPacket->getSize() <= rsize )
		return;
	uint32_t size = inPacket->getSize();
	uint16_t proc = inPacket->getProc();
	Answer::PackType type = inPacket->getType();
	int8_t connid = getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket(connid, type, proc, size);
	if ( packet )
	{
		uint32_t remainSize = inPacket->getSize() - rsize;
		packet->write(inPacket->getBuffer() + rsize, remainSize);
		packet->setSize(remainSize);
		m_netPackets.push(packet);
	}
}

void Player::appendInfo(Answer::NetPacket *packet)
{
	if ( !packet )
		return;
	packet->writeInt8(getType());
	packet->writeInt64(getCid());
	packet->writeUTF8(getName());
	packet->writeInt64(getFamilyId());
	packet->writeInt8(getFamilyPosition());
	packet->writeUTF8(getFamilyName());
	packet->writeInt8(getSex());
	packet->writeInt8(getJob());
	packet->writeInt8(0);
	packet->writeInt16(getLevel());
	packet->writeInt8(m_chr.pk_mode);
	packet->writeInt32(m_chr.pk_value);
	packet->writeInt8(GetFightChecker().IsBuleName());
	int32_t pkProtect = getPkProtectTime() - getNow();
	if ( pkProtect <= 0 )
		pkProtect = 0;
	packet->writeInt32(pkProtect);
	Position curTile = getCurrentTile();
	packet->writeInt16(curTile.x);
	packet->writeInt16(curTile.y);
	Position targetTile = getTargetTile();
	packet->writeInt16(targetTile.x);
	packet->writeInt16(targetTile.y);
	packet->writeInt32(getHp());
	packet->writeInt32(getMp());
	packet->writeInt32(getMaxHp());
	packet->writeInt32(getMaxMp());
	packageBuffList(packet);
	packet->writeInt16(getSpeed());
	packet->writeInt8(getHead());
	packet->writeInt8(GetTeamStatus());
	packet->writeInt32(getAction());
	packet->writeInt8(m_PlantState);
	packet->writeInt32(getMainWeaponId());
	packet->writeInt32(getClothesId());
	packet->writeInt32(getWingId());
	packet->writeInt32(m_CGoblin.GetWingEquipPolishSuitId());
	packet->writeInt8(GetPlayerVip().GetVipType());
	packet->writeInt8(GetPlayerVip().GetVipLevel());
	packet->writeInt8(GetCharJueWei().GetJueWei());
	GetCharTitle().AppendDressTitle(packet);
	packet->writeInt8(GetCamp());
	packet->writeInt8(0);
	packet->writeInt32(getShiZhuangWeapon());
	packet->writeInt32(getShiZhuangClothes());
	packet->writeInt32(GetShiZhuang().GetEffectId());
	packet->writeInt32(getShiZhuangFeet());
	m_extCharTencent.AppendInfo(packet);
	m_extVplan.AppendYYInfo(packet);
	m_extVplan.AppendSwVipInfo(packet);
	packet->writeInt8(getConnId());
	packet->writeInt8(0);
	packet->writeInt32(GetCharCarrier().GetCarrierId());
	packet->writeInt8(GetActState());
	packet->writeInt32(getRecord(3));
	packet->writeInt8(GetCharPet().IsFitting());
	packet->writeInt32(getRecord(1148));
	packet->writeInt32(getRecord(1153));
}

void Player::RecalcAttr()
{
	recalcAttr(false, false);
}
