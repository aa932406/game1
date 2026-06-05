
#include "stdafx.h"
#include "CfgData.h"
#include "DBService.h"
#include "GameService.h"
#include "ItemEffect.h"
#include "FileDef.h"
#include "Timer.h"
#include "ItemHelper.h"
#include <algorithm>
#include <limits>

using namespace Answer;
using namespace std;


CfgData::CfgData()
	:  m_avgLevel(40), m_createTime(0), m_debug(0),m_startServerTime(0)
{

}

CfgData::~CfgData()
{

}

bool CfgData::init(int32_t equipIdInterval, int32_t viceGeneralIdInterval,int32_t lackeyInterval, int32_t debug)
{
	// Decompiled-compatible init ordering
	fetchServerConfig();
	fetchActivity();
	fetchcfExActivity();
	fetchAnnoucementTime();
	fetchBuff();
	fetchDungeon();
	fetchDungeonEvent();
	fetchDungeonMonster();
	fetchDungeonPlant();
	fetchDungeonTrap();
	fetchDungeonNpc();
	fetchItem(false);
	fetchJob();
	fetchLevelAttr();
	fetchMap();
	fetchMapMonster();
	fetchMapPlant();
	fetchChrShop();
	fetchMapRegion();
	fetchMonster();
	fetchMonsterAI();
	fetchMonsterAdjustTable();
	fetchMonsterDropGroup();
	fetchMonsterGroupDrop();
	fetchMonsterTaskDrop();
	fetchNpc();
	fetchMovie();
	fetchPlant();
	fetchTask();
	fetchTrap();
	fetchLevelExp();
	fetchSignReward();

	// Init* tables (decompiled order)
	InitGroupIconTable();
	InitActiveSkillTable();
	InitPassiveSkillTable();
	InitTrigSkillTable();
	InitTalentTable();
	InitTalentPageTable();
	InitFamilySkillTable();
	InitTalentActiveTable();
	InitEquipTable();
	InitEquipUpStarTable();
	InitEquipSuitTable();
	InitEquipDecomposeTable();
	InitEquipUpPosTable();
	InitEquipPosSuitTable();
	InitEquipBoxTable();
	InitItemGemTable();
	InitGemOpenHoleTable();
	InitGemLevelUpTable();
	InitGemSuitTable();
	InitItemCombiTable();
	InitMonsterRandTable();
	InitCarrierTable();
	InitCarrierAttrTable();
	InitJueWeiTable();
	InitPetTable();
	InitPetAttrTable();
	InitPetUpStarTable();
	InitSkillLevelUpTable();
	InitTaskCycleStarTable();
	InitTaskCycleRewardTable();
	InitFamilyTable();
	InitFamilyWarJoinRewardTable();
	InitFamilyWarReliveTable();
	InitFamilyLightExpTable();
	InitHorseRacingRewardTable();
	InitCampWarRewardTable();
	InitCampWarContKillTable();
	InitCityWarContRewardTable();
	InitHallOfFameRewardTable();
	InitTitleTable();
	InitGoldEggTable();
	InitLimitTimeTable();
	InitMysteryShopTable();
	InitBuyGiftTable();
	InitExchangeTable();
	InitMysteryGiftTable();
	InitDrawTable();
	InitMapRoadTable();
	InitTrailerTable();
	InitMYSJRewardTable();
	InitMaintainCompensateTable();
	InitWishRewardTable();
	InitBFZLEnterCostTable();
	InitBlacketMarketTable();
	InitLevelChatTimesTable();
	InitSuperMemberTable();
	InitSouGouSkinTable();
	InitPetEquipTable();
	InitWeiXinTable();
	InitAdultGiftTable();
	InitQQZoneRewardTable();
	InitQQGameRewardTable();
	InitYellowRewardTable();
	InitYellowDailyRewardTable();
	InitYellowLevelRewardTable();
	InitBlueRewardTable();
	InitBlueDailyRewardTable();
	InitBlueLevelRewardTable();
	InitTGPRewardTable();
	InitTGPDailyRewardTable();
	InitTGPLevelRewardTable();
	InitFamilyDungeonTable();
	InitDropRecordTable();
	InitDungeonScoreTable();
	InitDungeonSummon();
	InitSysMail();
	InitBossInfo();
	InitFaBaoTable();
	InitDaTiHD();
	InitShangChengTable();
	InitOnLimeReward();
	InitSevenLoginReward();
	InitLevelGift();
	InitWeekOnlineReward();
	InitOffLineExpTable();
	InitVipCardTable();
	InitFunctionOpenTable();
	InitPlantEventTable();
	InitZiYuanZhaoHuiTable();
	InitMoHuaHuanYiTable();
	InitShouChongLiBao();
	InitNewServerFavorable();
	InitMobilePhoneGiftTable();
	InitEveryDayChongZhi();
	InitKaiFuHuoDongTable();
	InitHuoYueDuTable();
	InitAppendAttrTable();
	InitFamilyRewardTable();
	InitTotalChongZhiTable();
	InitSpecialTreasureMapRandTable();
	InitMonsterAddAttrTable();
	InitDaZheQuanTable();
	Init360RewardTable();
	Init360RewardTypeTable();
	InitVplanTable();
	InitShunWangTable();
	InitSpeed360Reward();
	InitTencentSevenDayLoginTable();
	InitGoblinData();
	InitSpecialMonster();
	InitEquipUpPhase();
	InitTouZiTable();
	InitGroupMonster();
	InitPkDropRateTable();
	InitEquipBackTable();
	InitStrengthenTable();
	InitBuyFaBaoResTable();
	InitXingMaiTable();
	InitXingMaiSlotTable();
	InitTianLingTable();
	InitZhanHunTable();
	InitSunAndMoonTable();
	InitGongMinTable();
	InitBeastShrineEnterCostTable();
	InitDamnationTable();
	InitAttrBattleTable();
	InitScoreShopTable();
	InitChouJiangTable();
	InitWingCfgTable();
	InitLibraryTable();
	InitTreasureMapTabale();
	InitEquipBackTask();
	InitSpeciaEquipCfgMap();
	InitSpeciaSkillDistanceTable();
	InitLuckDropTable();
	InitLevelRefiningTable();
	InitBossFirstKilledTable();
	InitUltimateChallengeCfg();
	InitCachetCfg();
	InitBossKilledReward();
	InitSystemOpenReward();
	InitSpecialMap();
	InitTestServerReward();
	InitEquipBlessTable();
	InitGuWuCfgMap();
	InitFunctionOpenMailMap();
	InitXianYaoTaskTable();
	InitShenWeiTaskTable();
	InitMiniClientTable();
	InitWuHunShopTable();
	InitWuHunItemTable();
	InitWuHunCreateTable();
	InitBossDistribution();
	InitSpecialBossMapCfgMap();
	InitDuiHuanLimitTable();
	InitSuperTeHuiTable();
	InitJewelPavilionTable();
	InitGoblinTable();
	InitShouHuRefining();
	InitWingEquipPolish();
	InitGuiGuDaoRenTable();
	InitShiZhuangTable();
	InitShiZhuangLevelTable();
	InitMonthlyChouJiangTable();
	InitActDropTable();
	InitSevenTaskTable();
	m_QiFuTable.InitQiFuTable();
	m_VipTable.InitVipTable();
	InitOutLinkFestivalTable();
	InitYYDaTing();
	InitYYVip();
	InitSouGouDaTing();
	InitXunLeiTable();
	InitCycleTowerTable();
	InitPlatformDaTingMap();
	InitMiniClientMap();
	InitPlatformVipMap();
	InitShangRenCfgMap();
	InitSelectItemCfgMap();
	InitGuardPrivilegeTable();
	InitPlatformReward();
	InitDiligenceCfgMap();
	InitFamilyDonateTable();
	InitFamilyMedalTable();
	InitHoeTable();
	InitMingGeTable();
	InitCrossTowerCfgMap();
	InitKunLingTable();
	InitLaDaShiHuiYuan();
	InitFlopTable();
	InitMoFuTable();
	InitChristmasDuiHuanTable();
	InitBaoKuFuBen();
	InitChargeDungeon();
	InitShenYaoPosTable();
	InitShenYaoPosSuitTable();
	InitTongTianChiRanTable();
	InitXinMoTable();
	InitGameTable();
	InitRefreshMonsterCfgListMap();
	InitLittleHelperCfg();
	InitShiZhuLevelUp();
	InitNationalDayTask();
	InitRongHeCfg();

	m_TouZiCfg.InitTouZiTable();
	m_ChouJiangConfig.InitCJConfig();
	m_debug = debug;

	return true;
}

void CfgData::reload()
{
	fetchItem(true);

	ITEM_EFFECT.init();
}

const CfgActivityTable& CfgData::getAllActivity()
{
	return m_activities;
}

CfgActivity* CfgData::getActivity(int32_t id)
{
	CfgActivityTable::iterator it = m_activities.find(id);
	if (it != m_activities.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

const CfgMapEventList& CfgData::getActivityEvents( int32_t activity_id, MapId_t nMapId )
{
	CfgMapEventTable::iterator it = m_activityEvents.find(activity_id);
	if ( it == m_activityEvents.end() )
	{
		return m_emptyEvents;
	}

	CfgMapEventMap::iterator iter = it->second.find( nMapId );
	if ( iter == it->second.end() )
	{
		return m_emptyEvents;
	}
	
	return iter->second;
}

CfgActivityMonster* CfgData::getActivityMonster( int32_t id )
{
	CfgActivityMonsterTable::iterator it = m_activityMonsters.find( id );
	if ( it != m_activityMonsters.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgActivityNpc* CfgData::getActivityNpc(int32_t id)
{
	CfgActivityNpcTable::iterator it = m_activityNpcs.find(id);
	if (it != m_activityNpcs.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgActivityPlant* CfgData::getActivityPlant( int32_t Id )
{
	CfgActivityPlantTable::iterator it = m_activityPlants.find( Id );
	if (it != m_activityPlants.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgActivityTrap* CfgData::getActivityTrap( int32_t id )
{
	CfgActivityTrapTable::iterator it = m_activityTraps.find( id );
	if ( it != m_activityTraps.end() )
	{
		return &(it->second);
	}

	return NULL;
}

CfgActivityDropTable* CfgData::getActivityDrops()
{
	return &m_activityDrops;
}

const CfgAnnoucementTimeTable& CfgData::getAllAnnoucementTime() const
{
	return m_annoucementTimes;
}

CfgBuff* CfgData::getBuff(int32_t id)
{
	CfgBuffTable::iterator it = m_buffs.find(id);
	if (it != m_buffs.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

const CfgDungeonTable& CfgData::getDungeonAll()
{
	return m_dungeons;
}

CfgDungeon* CfgData::getDungeon(int32_t id)
{
	CfgDungeonTable::iterator it = m_dungeons.find(id);
	if (it != m_dungeons.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

//CfgDungeon* CfgData::getDengTianTiFirstDungeon()
//{
//	for (CfgDungeonTable::iterator it = m_dungeons.begin();it != m_dungeons.end();++it)
//	{
//		if (it->second.type == DT_DENGTIANTI && it->second.id == it->second.last_id)
//		{
//			return &(it->second);
//		}
//	}
//
//	return NULL;
//}

const CfgMapEventList& CfgData::getDungeonEvent( int32_t dungonid )
{
	CfgMapEventMap::iterator it  = m_dungeonEvents.find(dungonid);
	if ( it != m_dungeonEvents.end())
	{
		return it->second;
	}
	return m_emptyEvents;
}

CfgDungeonMonster* CfgData::getDungeonMonster(int32_t id)
{
	CfgDungeonMonsterTable::iterator it = m_dungeonMonsters.find(id);
	if (it != m_dungeonMonsters.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgDungeonPlant* CfgData::getDungeonPlant(int32_t id)
{
	CfgDungeonPlantTable::iterator it = m_dungeonPlants.find(id);
	if (it != m_dungeonPlants.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgDungeonTrap* CfgData::getDungeonTrap(int32_t id)
{
	CfgDungeonTrapTable::iterator it = m_dungeonTraps.find(id);
	if (it != m_dungeonTraps.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

const CfgEquip* CfgData::getEquip( int32_t id ) const
{
	return m_cfgEquip.GetEquip( id );
}

CfgChrShop* CfgData::getChrShop( int32_t Index )
{
	CfgChrShopTable::iterator it = m_chrShops.find( Index );
	if ( it != m_chrShops.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgGambleEquip* CfgData::getGambleEquip(int32_t id)
{
	CfgGambleEquipTable::iterator it = m_gambleEquip.find(id);
	if (it != m_gambleEquip.end())
	{
		return &(it->second);
	}

	return NULL;
}

CfgGamble* CfgData::getGamble(int32_t ratio,int32_t type)
{    
	int32_t temp = 0;
	CfgGamble*pGamble  = NULL;

	if (type == 1)
	{
		for (CfgGambleVector::iterator it = m_gamble.begin();it != m_gamble.end();++it)
		{
			if (it->ratio >= ratio &&  ratio > temp)
			{ 
				return &(*it);
			}
			temp = it->ratio;
		}
	}
	else if (type == 2)
	{
		for (CfgGambleVector::iterator it = m_gamble_second.begin();it != m_gamble_second.end();++it)
		{
			if (it->ratio >= ratio &&  ratio > temp)
			{ 
				return &(*it);
			}
			temp = it->ratio;
		}
	}
	else if (type == 3)
	{
		for (CfgGambleVector::iterator it = m_gamble_three.begin();it != m_gamble_three.end();++it)
		{
			if (it->ratio >= ratio &&  ratio > temp)
			{ 
				return &(*it);
			}
			temp = it->ratio;
		}
	}
	

	return pGamble;
}

CfgItemTable CfgData::getAllItem()
{
	CfgItemTable items;

	Answer::RwLockRdGuard lock(m_itemsLock);

	items = m_items;

	return items;
}

CfgItem* CfgData::getItem(int32_t id)
{
	if (id <= 0)
	{
		return NULL;
	}

	Answer::RwLockRdGuard lock(m_itemsLock);

	CfgItemTable::iterator it = m_items.find(id);
	if (it != m_items.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

CfgItemGiftVector* CfgData::getItemGift(int32_t id)
{
	Answer::RwLockRdGuard lock(m_itemGiftsLock);

	CfgItemGiftTable::iterator it = m_itemGifts.find(id);
	if (it != m_itemGifts.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

CfgItemGiftRandomVector* CfgData::getItemGiftRandom(int32_t id)
{
	Answer::RwLockRdGuard lock(m_itemGiftRandomsLock);

	CfgItemGiftRandomTable::iterator it = m_itemGiftRandoms.find(id);
	if (it != m_itemGiftRandoms.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

CfgJob* CfgData::getJob(int32_t id)
{
	CfgJobTable::iterator it = m_jobs.find(id);
	if (it != m_jobs.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

bool CfgData::getMovie(int32_t id)
{
	CfgMovieTable::iterator it = m_movie.find(id);
	if (it != m_movie.end())
	{
		return true;
	}
	return false;
}

const CfgMapTable& CfgData::getMapAll()
{
	return m_maps;
}

CfgMap* CfgData::getMap(int32_t id)
{
	CfgMapTable::iterator it = m_maps.find(id);
	if (it != m_maps.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

Int32Vector* CfgData::getFamilyBossActivityReward(int32_t level)
{
	CfgFamilyLevelTable::iterator it = m_familyLevel.find(level);
	if (it != m_familyLevel.end())
	{
		return &(it->second.rewards);
	}

	return NULL;
}

CfgMapMonsterVector* CfgData::getMonstersOnMap(int32_t mapid)
{
	CfgMapMonsterTable::iterator it = m_mapMonsters.find(mapid);
	if (it != m_mapMonsters.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgMapMonster* CfgData::GetMapMonsterInfo( int32_t id )
{
	CfgMonsterMap::iterator it = m_CfgMapMonsters.find(id);
	if ( it != m_CfgMapMonsters.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgMapPlantVector* CfgData::getPlantOnMap(int32_t mapid)
{
	CfgMapPlantTable::iterator it = m_mapPlants.find(mapid);
	if (it != m_mapPlants.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgMapRegion* CfgData::getMapRegion(int32_t id)
{
	CfgMapRegionTable::iterator it = m_mapRegions.find(id);
	if (it != m_mapRegions.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgMapRegionVector* CfgData::getRegionOnMap(int32_t mapid)
{
	Int32CfgMapRegionVectorMap::iterator it = m_mapRegionsByMapId.find(mapid);
	if (it != m_mapRegionsByMapId.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgMonster* CfgData::getMonster(int32_t mid)
{
	CfgMonsterTable::iterator it = m_monsters.find(mid);
	if (it != m_monsters.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

bool CfgData::isMonsterBroadcast(int32_t mid)
{
	return std::find(m_monsterBroadcasts.begin(), m_monsterBroadcasts.end(), mid) != m_monsterBroadcasts.end();
}

CfgDungeonReward* CfgData::getDungeonReward(int32_t dungeonID)
{
	   CfgDungeonRewardTable::iterator it = m_dungeonReward.find(dungeonID);
	   if (it != m_dungeonReward.end())
	   {
		   return &(it->second);
	   }

	   return NULL;
}

const CfgDungeonDrop* CfgData::randDungeonDrop(int32_t dungeonID)
{
	CfgDungeonDropGroupTable::iterator it = m_dungeonDropGroup.find(dungeonID);
	if (it != m_dungeonDropGroup.end())
	{
		return it->second.RandDrop();
	}

	return NULL;
}

CfgMonsterDropGroupVector* CfgData::getMonsterDropGroup(int32_t group_id)
{
	CfgMonsterDropGroupTable::iterator it = m_monsterDropGroups.find(group_id);
	if (it != m_monsterDropGroups.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgMonsterGroupDropVector* CfgData::getMonsterGroupDrop(int32_t mid)
{
	CfgMonsterGroupDropTable::iterator it = m_monsterGroupDrops.find(mid);
	if (it != m_monsterGroupDrops.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgMonsterTaskDropVector* CfgData::getMonsterTaskDrop(int32_t mid)
{
	CfgMonsterTaskDropTable::iterator it = m_monsterTaskDrops.find(mid);
	if (it != m_monsterTaskDrops.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgNpc* CfgData::getNpc(int32_t npcid)
{
	CfgNpcTable::iterator it = m_npcs.find(npcid);
	if (it != m_npcs.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

const CfgNpcTable& CfgData::getNpcAll()
{
	return m_npcs;
}

CfgChangeJobAttr*CfgData::getChangeJobAttr(int32_t index)
{
	CfgChangeJobAttrTable::iterator it = m_changeAttr.find(index);
	if (it != m_changeAttr.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgBornAttr* CfgData::getBornAttr(Job_t jobindex)
{
	CfgBornAttrTable::iterator it = m_bornAttr.find(jobindex);
	if (it != m_bornAttr.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgNpcAirport* CfgData::getNpcAirport(int32_t id)
{
	CfgNpcAirportTable::iterator it = m_npcAirports.find(id);
	if (it != m_npcAirports.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgPlant* CfgData::getPlant(int32_t id)
{
	CfgPlantTable::iterator it = m_plants.find(id);
	if (it != m_plants.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgSkill* CfgData::getSkill(int32_t id)
{
	CfgSkillTable::iterator it = m_skills.find(id);
	if (it != m_skills.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgTask* CfgData::getTask(int32_t id)
{
	CfgTaskTable::iterator it = m_tasks.find(id);
	if (it != m_tasks.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgYellowStone* CfgData::getYellowStone(int32_t id)
{
	CfgYellowStoneTables::iterator it = m_yellowStone.find(id);
	if (it != m_yellowStone.end())
	{
		return &(it->second);
	}
	return NULL;
}

CfgTrailer* CfgData::getTrailer()
{
	return  &m_tailers;
}

CfgTrap* CfgData::getTrap(int32_t id)
{
	CfgTrapTable::iterator it = m_traps.find(id);
	if (it != m_traps.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgItemBase* CfgData::getItemBase(int32_t id, int32_t type)
{
	switch (type)
	{
	case IC_NORMAL: return getItem(id);
	//case IC_EQUIP: return getEquip(id);
	default: return NULL;
	}
}

std::string CfgData::getItemName(int32_t id, int32_t type)
{
	CfgItemBase *cfgItemBase = getItemBase(id, type);
	if (cfgItemBase != NULL)
	{
		return cfgItemBase->name;
	}
	else
	{
		return "";
	}
}

int32_t CfgData::getOverlay(int32_t id, int32_t itemClass)
{
	if (itemClass == IC_NORMAL)
	{
		CfgItem *cfgItem = getItem(id);
		if (cfgItem != NULL)
		{
			int32_t overlay = cfgItem->overlay;
			if (overlay == 0)
			{
				overlay = 1;
			}

			return overlay;
		}
	}
	else if ( itemClass == IC_GEM )
	{
		const CfgItemGem *cfgGem = GetItemGemTable().GetItemGem( id );
		if ( cfgGem != NULL )
		{
			int32_t overlay = cfgGem->m_nLayNum;
			if (overlay == 0)
			{
				overlay = 1;
			}

			return overlay;
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

int32_t CfgData::getInValue(int32_t id, int32_t type)
{
	CfgItemBase *cfgItemBase = getItemBase(id, type);
	if (cfgItemBase != NULL)
	{
		return cfgItemBase->in_value;
	}
	else
	{
		return -1;
	}
}

int32_t CfgData::getOutValue(int32_t id, int32_t type)
{
	switch ( type )
	{
	case IC_NORMAL:
		{
			const CfgItem* pItem = getItem( id );
			if ( pItem != NULL )
			{
				return pItem->out_value;
			}
		}
		break;
	case IC_EQUIP:
		{
			const CfgEquip* pEquip = getEquip( id );
			if ( pEquip != NULL )
			{
				return pEquip->m_nPrice;
			}
		}
		break;
	case IC_GEM:
		{
			const CfgItemGem* pGem = GetItemGemTable().GetItemGem( id );
			if ( pGem != NULL )
			{
				return pGem->m_OutValue;
			}
		}
		break;
	default:
		break;
	}
	return -1;
}


bool CfgData::canSell(int32_t id, int32_t itemClass)
{
	if (itemClass == IC_NORMAL)
	{
		CfgItem *cfgItem = getItem(id);
		if (cfgItem != NULL)
		{
			return cfgItem->can_sell != 0;
		}
	}

	return true;
}


CfgLevelExp* CfgData::getUpgradeExp(int32_t level)
{
	CfgLevelExpTable::iterator it = m_levelExps.find(level);
	if (it != m_levelExps.end())
	{
		return &(it->second);
	}

	return NULL;
}

int64_t CfgData::getNeedLevelExp(int32_t level)
{
	CfgLevelExpTable::iterator it = m_levelExps.find(level);
	if (it != m_levelExps.end())
	{
		return it->second.upgrade_exp;
	}
	else
	{
		return numeric_limits<int64_t>::max();
	}
}

int64_t CfgData::getMaxExp(int32_t level)
{
	CfgLevelExpTable::iterator it = m_levelExps.find(level);
	if (it != m_levelExps.end())
	{
		return it->second.max_exp;
	}
	else
	{
		return numeric_limits<int64_t>::max();
	}
}

int32_t	CfgData::GetPetExp( int32_t level )
{
	CfgLevelExpTable::iterator it = m_levelExps.find( level );
	if ( it != m_levelExps.end() )
	{
		return it->second.pet_exp;
	}
	else
	{
		return numeric_limits<int32_t>::max();
	}
}

CfgLevelAttr CfgData::getLevelAttr(int32_t job,int32_t level)
{
	CfgLevelAttrTable::iterator it = m_levelAttrs.find(((job << 16)|level));
	if (it != m_levelAttrs.end())
	{
		return it->second;
	} 
	else
	{
		CfgLevelAttr levelAttr = {};
		return levelAttr;
	}
}

int32_t CfgData::getBaseJob(int32_t job)
{
	switch (job)
	{
	case PJ_ZHANSHI:
		return PJ_ZHANSHI;
	case PJ_FASHI:
		return PJ_FASHI;
	case PJ_LONGQI:
		return PJ_LONGQI;
	default:
		return 0;
	}
}

bool sortInt(const int32_t&left,const int32_t&right)
{
	if(left <right)
	{
		return true;
	}
	return false;
};

AttrAddonVector CfgData::getItemEffect(int32_t id)
{
	  CfgItem* pItem = getItem(id);
	  if (pItem != NULL)
	  {
		  return parseItemEffect(id,pItem->effect);
	  }
	  AttrAddonVector attr;
	  return attr;
}

void CfgData::onAvgLevelUpdated(int32_t avgLevel)
{
	m_avgLevel = avgLevel;
}

int32_t CfgData::getCreateTime()
{
	return m_createTime;
}

int32_t CfgData::getDebug()
{
	return m_debug;
}

CTouZiCfg&	CfgData::GetTouZhiCfg()
{
	return m_TouZiCfg;
}

void CfgData::parasKaiFuHuoDongCondition( std::string& Effect, int32_t Conditions, int32_t& Param1, int32_t& Param2 )
{
	if ( Effect.empty() )
	{
		return;
	}
	StringVector requests = StringUtility::split(Effect, ":");
	switch ( Conditions )
	{
	case KFHDC_LEVEL_UP:
	case KFHDC_PET_POINT:			
	case KFHDC_JUN_TUAN_LEADER:	
	case KFHDC_JUN_TUAN_WIN:		
	case KFHDC_FAMILY_WAR_JOIN:	
	case KFHDC_BATTLE_POINT:
		{
			if ( requests.size() == 1 )
			{
				Param1 = atoi( requests[0].c_str() );
			}
			break;
		}
	case KFHDC_PET_RANK:	
	case KFHDC_BATTLE_RANK:		
		{
			if ( requests.size() == 2 )
			{
				Param1	= atoi( requests[0].c_str() );
				Param2  = atoi( requests[1].c_str() );
			}
			break;
		}
	default:
		break;
	}
}

void CfgData::InitGuangWeiTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_GUAN_WEI_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_GUAN_WEI_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgGuanWei stu = {};
		stu.GuanWei				= TabFile.Search_Posistion(i,0)->iValue;
		stu.NeedLevel			= TabFile.Search_Posistion(i,1)->iValue;
		stu.NeedWeiWang			= TabFile.Search_Posistion(i,2)->iValue;
		stu.GetExp				= TabFile.Search_Posistion(i,3)->iValue;
		stu.GetMoney			= TabFile.Search_Posistion(i,4)->iValue;
		stu.Items				= parseItemString( stu.GuanWei,TabFile.Search_Posistion(i,5)->pString );
		stu.MailId				= TabFile.Search_Posistion(i,6)->iValue;
		for ( int32_t j = 0; j < 9; j++ )
		{	
			AddAttribute attr;
			attr.m_nAddAttrType		= TabFile.Search_Posistion(i,7 + 2 * j )->iValue;
			attr.m_nAddAttrValue	= TabFile.Search_Posistion(i,7 + 2 * j + 1 )->iValue;
			if ( attr.m_nAddAttrValue <= 0 )
			{
				continue;
			}
			stu.Attrs.push_back( attr );
		}
		stu.Battle				= TabFile.Search_Posistion(i,25)->iValue;		
		m_GuanWeiCfg[stu.GuanWei] = stu;
	}

	CDBCFile TabFileQiShi(0);
	ret = TabFileQiShi.OpenFromTXT(FILE_QI_SHI_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_QI_SHI_TABLE");
		return;
	}

	iBaseTableCount			=	TabFileQiShi.GetRecordsNum();
	iBaseColumnCount		=	TabFileQiShi.GetFieldsNum();
	if ( iBaseColumnCount <=0 )
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgQiShi stu = {};
		stu.QiShiPos			= TabFileQiShi.Search_Posistion(i,0)->iValue;
		stu.NeedGuanWei			= TabFileQiShi.Search_Posistion(i,1)->iValue;
		stu.AddBattle			= TabFileQiShi.Search_Posistion(i,2)->iValue;
		stu.AttrType			= TabFileQiShi.Search_Posistion(i,3)->iValue;
		stu.AttrType2			= TabFileQiShi.Search_Posistion(i,4)->iValue;
		for ( int32_t j = 0; j < MAX_QI_SHI_QUALITY_SIZE; j++ )
		{
			stu.vQuality[j]			= TabFileQiShi.Search_Posistion(i,5 + 3 * j )->iValue;
			stu.vEffectValue[j]		= TabFileQiShi.Search_Posistion(i,5 + 3 * j + 1 )->iValue;
			stu.vEffectValue2[j]	= TabFileQiShi.Search_Posistion(i,5 + 3 * j + 2 )->iValue;
		}
		m_QiShiCfg[stu.QiShiPos] = stu;
	}	
}


CfgGuanWei* CfgData::GetGuanWeiCfg( int32_t index )
{
	GuanWeiMap::iterator it = m_GuanWeiCfg.find( index );
	if ( it != m_GuanWeiCfg.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgQiShi* CfgData::GetQiShiCfg( int32_t index )
{
	QiShiMap::iterator it = m_QiShiCfg.find( index );
	if( it != m_QiShiCfg.end() )
	{
		return &( it->second );
	}
	return NULL;
}

AddAttrList CfgData::GetQiShiAttr( int32_t index, int32_t Quality )
{
	AddAttrList AttrList;
	QiShiMap::iterator it = m_QiShiCfg.find(index);
	if ( it != m_QiShiCfg.end() )
	{	
		AddAttribute stu;
		int32_t Max = -1;
		stu.m_nAddAttrType = it->second.AttrType;
		for ( int32_t i = 0; i < MAX_QI_SHI_QUALITY_SIZE; ++i )
		{
// 			if ( it->second.vQuality[i] < 0 )
// 			{
// 				break;
// 			}
			if ( Quality < it->second.vQuality[i] )
			{
				break;
			}

			Max = i;
		}

		if ( Max >= 0 )
		{
			stu.m_nAddAttrValue = it->second.vEffectValue[Max];
		}
		if ( stu.m_nAddAttrType > 0 && stu.m_nAddAttrValue > 0 )
		{
			AttrList.push_back( stu );
		}

		stu.m_nAddAttrType		= it->second.AttrType2;
		if ( Max >= 0 )
		{
			stu.m_nAddAttrValue     = it->second.vEffectValue2[Max];
		}
		if ( stu.m_nAddAttrType > 0 && stu.m_nAddAttrValue > 0 )
		{
			AttrList.push_back( stu );
		}
	}
	return AttrList;
}

void CfgData::InitBuyAcSocreTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT( FILE_BUY_AC_SOCRE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_BUY_AC_SOCRE_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		CfgBuyAcSocre  stu = {};
		stu.Index			= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		++nIndex;
		stu.CostType		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.CostValues		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.GetValues		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		m_BuyAcSocreMap[stu.Index] = stu;
	}
}

CfgBuyAcSocre* CfgData::GetBuyAcScoreCfg( int32_t Index )
{
	BuyAcSocerMap::iterator it = m_BuyAcSocreMap.find(Index);
	if ( it != m_BuyAcSocreMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitXunZhangTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT( FILE_XUN_ZHANG_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_XUN_ZHANG_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		CfgXunZhang  stu = {};
		stu.EquipId			= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.CostSocre		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.NextEquipId		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		m_XunZhangMap[stu.EquipId] = stu;
	}
}

CfgXunZhang* CfgData::GetXunZhangCfg( int32_t EquipId )
{
	XunZhangMap::iterator it = m_XunZhangMap.find( EquipId );
	if ( it != m_XunZhangMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitAchievementTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT( FILE_ACHIEVEMENT_TASK_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_ACHIEVEMENT_TASK_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		CfgAchievement  stu = {};
		stu.Index		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		++nIndex;
		++nIndex;
		stu.Socre		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		++nIndex;
		++nIndex;
		stu.ZhiYuan		= paraseCurrency( TabFile.Search_Posistion(i,nIndex)->pString ); ++nIndex;
		stu.Group		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.Request		= parseAchievementCondition( stu.Index, stu.Group, TabFile.Search_Posistion(i,nIndex)->pString ); ++nIndex;
		m_AchievementTable.AddAchievementTask( stu );
	}
}

const AchievementTable&	CfgData::GetAchievementTable() const
{
	return m_AchievementTable;
}

void AchievementTable::OnCleanUP()
{
	m_AchievementTaskMap.clear();
}

void AchievementTable::AddAchievementTask( CfgAchievement Stu )
{
	m_AchievementTaskMap[Stu.Index] = Stu;
}

const CfgAchievement* AchievementTable::GetAchievementTask( int32_t Index ) const
{
	AchievementTask::const_iterator it = m_AchievementTaskMap.find( Index );
	if ( it != m_AchievementTaskMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

const AchievementTask AchievementTable::GetAchievementTaskMap() const
{
	return m_AchievementTaskMap;
}

void CfgData::InitFamilyRewardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT( FILE_FAMILY_TASK_RING );
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_FAMILY_TASK_RING");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		FamilyTaskReward stu = {};
		stu.Index		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.NeedCount	= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.Rewards		= parseItemString(stu.Index, TabFile.Search_Posistion(i,nIndex)->pString ); ++nIndex;
		m_FamilyTaskReward[stu.Index] = stu;
	}
}

FamilyTaskReward* CfgData::GetFamilyReward( int32_t Index )
{
	FamilyTaskRewardMap::iterator it = m_FamilyTaskReward.find(Index);
	if ( it != m_FamilyTaskReward.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitPetBuyTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_BUY_PET_INFO);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_BUY_PET_INFO");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		PetBuyInfo stu = {};
		stu.ShopId		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		++nIndex;
		++nIndex;
		stu.Points		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		m_cfgPetTable.AddPetBuy( stu );
	}
}

void CfgData::InitwuHunExpTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_WU_HUN_EXP);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_WU_HUN_EXP");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		CWuHunExp stu = {};
		stu.Points		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.Exp			= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		m_cfgPetTable.AddWuHunExp( stu );
	}
}

void CfgData::InitAppendAttrTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_APPEND_ATTR_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_APPEND_ATTR_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		CfgAppendAttr stu = {};
		stu.Id			= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		stu.Job			= (int8_t)TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
		for ( int32_t j = 0; j < 10; j++ )
		{
			AddAttribute Attr;
			Attr.m_nAddAttrType		= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
			Attr.m_nAddAttrValue	= TabFile.Search_Posistion(i,nIndex)->iValue; ++nIndex;
			if ( Attr.m_nAddAttrType < 0 || Attr.m_nAddAttrValue <= 0 )
			{
				continue;
			}
			stu.AttrList.push_back( Attr );
		}
		m_AppendAttrTable.push_back( stu );
	}
}

AddAttrList CfgData::GetAppendAttr( int32_t Id, int8_t Job )
{
	AddAttrList list;
	AppendAttrTable::iterator it = m_AppendAttrTable.begin();
	for ( ; it != m_AppendAttrTable.end(); ++it )
	{
		if ( it->Id == Id && ( it->Job == Job || it->Job == 0 ) )
		{
			return it->AttrList;
		}
	}
	return list;
}

void CfgData::InitHuoYueDuTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_HUO_YUE_DU_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_HUO_YUE_DU_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgHuoYueDu stu = {};
		stu.Index			= TabFile.Search_Posistion(i,0)->iValue;
		stu.Type			= (int8_t)TabFile.Search_Posistion(i,1)->iValue;
		stu.Effect			= TabFile.Search_Posistion(i,2)->iValue;
		stu.Count			= TabFile.Search_Posistion(i,3)->iValue;
		stu.Gold			= TabFile.Search_Posistion(i,4)->iValue;
		stu.AddHuoYueDu		= TabFile.Search_Posistion(i,5)->iValue;
		stu.IsCanSec		= TabFile.Search_Posistion(i,6)->iValue > 0 ? 1:0;
		m_HuoYueDuTable[stu.Index] = stu;
	}

	CDBCFile TabFileReward(0);
	ret = TabFileReward.OpenFromTXT(FILE_HUO_YUE_DU_REWARD_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_HUO_YUE_DU_REWARD_TABLE");
		return;
	}

	iBaseTableCount			=	TabFileReward.GetRecordsNum();
	iBaseColumnCount		=	TabFileReward.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgHuoYueDuReward stu = {};
		stu.Id						= TabFileReward.Search_Posistion(i,0)->iValue;
		stu.NeedHuoYueDu			= TabFileReward.Search_Posistion(i,1)->iValue;
		stu.Items					= parseItemString(stu.Id,TabFileReward.Search_Posistion(i,2)->pString);
		m_HuoYueDuRewardTable[stu.Id] = stu;
	}
}

CfgHuoYueDu* CfgData::GetHuoYueDuCfg( int32_t Index )
{
	HuoYueDuTable::iterator it = m_HuoYueDuTable.find(Index);
	if ( it != m_HuoYueDuTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

HuoYueDuTable& CfgData::GetHuoYueDuTable()
{
	return m_HuoYueDuTable;
}

CfgHuoYueDuReward* CfgData::GetHuoYueDuReward( int32_t Index )
{
	HuoYueDuRewardTable::iterator it = m_HuoYueDuRewardTable.find(Index);
	if ( it != m_HuoYueDuRewardTable.end() )
	{
		return &( it->second );
	}
	return NULL;
}

HuoYueDuRewardTable& CfgData::GetHuoYueDuRewardTable()
{
	return m_HuoYueDuRewardTable;
}

void CfgData::InitKaiFuHuoDongTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_KAI_FU_HUO_DONG);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ�����FILE_KAI_FU_HUO_DONG");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgKaiFuHuoDongData stu = {};
		stu.Index			= TabFile.Search_Posistion(i,0)->iValue;
		stu.Type			= (int8_t)TabFile.Search_Posistion(i,1)->iValue;
		stu.StartDay		= TabFile.Search_Posistion(i,2)->iValue;
		stu.EndDay			= TabFile.Search_Posistion(i,3)->iValue;
		stu.GetRewardDay	= TabFile.Search_Posistion(i,4)->iValue;
		stu.Conditions		= TabFile.Search_Posistion(i,5)->iValue;
		std::string	Effect	= TabFile.Search_Posistion(i,6)->pString;
		parasKaiFuHuoDongCondition( Effect,stu.Conditions, stu.Parm1, stu.Parm2  );
		stu.ItemVector		= parseItemString(stu.Index,TabFile.Search_Posistion(i,7)->pString);
		stu.LimitCount		= TabFile.Search_Posistion(i,8)->iValue;
		m_KaiFuHuoDongTable[stu.Index] = stu;
	}
}

KaiFuHuoDongCfg& CfgData::GetKaiFuHuoDongCfg()
{
	return m_KaiFuHuoDongTable;
}


void CfgData::InitHuanHuaNeedRoleLevelTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_HUAN_HUA_NEED_ROLE_LEVEL_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_HUAN_HUA_NEED_ROLE_LEVEL_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount ;i++ )
	{
		CfgHuanHuaNeedRoleLevel stu = {};
		stu.MinQualit		= TabFile.Search_Posistion(i,0)->iValue;
		stu.MaxQualit		= TabFile.Search_Posistion(i,1)->iValue;
		stu.NeedLevel		= TabFile.Search_Posistion(i,2)->iValue;
		m_HuanHuaNeedRoleLevelList.push_back( stu );
	}
}

int32_t CfgData::GetHuanHuaNeedRoleLevel( int32_t Points )
{
	HuanHuaNeedRoleLevelList::iterator it = m_HuanHuaNeedRoleLevelList.begin();
	for ( ; it != m_HuanHuaNeedRoleLevelList.end(); ++it )
	{
		if ( Points >= it->MinQualit &&  Points <= it->MaxQualit)
		{
			return it->NeedLevel;
		}
	}
	return 9999999;
}

void CfgData::InitWarVictoryTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_WAR_VICTORY_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_WAR_VICTORY_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount ;i++ )
	{
		WarVictoryHd stu = {};
		stu.Index			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		stu.Type			= (int8_t)TabFile.Search_Posistion(i,1)->iValue;
		stu.StartTime		= Answer::DayTime::StringToIntTime( TabFile.Search_Posistion(i,2)->pString );
		stu.EndTime			= Answer::DayTime::StringToIntTime( TabFile.Search_Posistion(i,3)->pString );
		stu.NeedGold		= TabFile.Search_Posistion(i,4)->iValue;
		stu.Rewards			= parseItemString(stu.Index, TabFile.Search_Posistion(i,5)->pString );
		stu.Times			= TabFile.Search_Posistion(i,6)->iValue;
		stu.GongGaoId		= parseGongGaoString(stu.Index,TabFile.Search_Posistion(i,7)->pString );
		m_WarVictoryHdMap[stu.Index] = stu;
	}
}

void CfgData::InitGemLevelUpTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_GEM_LEVEL_UP_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_GEM_LEVEL_UP_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgGemLevelUp stu = {};
        int32_t nGemId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nNeedItemId = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nNeedItemCount = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nCostMoney = TabFile.Search_Posistion(i, 3)->iValue;
        stu.nNextGemId = TabFile.Search_Posistion(i, 4)->iValue;
        stu.nBroadId = TabFile.Search_Posistion(i, 5)->iValue;
        m_cfgGemLevelUp.Add(nGemId, stu);
    }
}

void CfgData::InitMoFuTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_MOFU_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_MOFU_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgMoFu stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nCostGold = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nRecycleItemId = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nRecycleItemCount = TabFile.Search_Posistion(i, 3)->iValue;
        m_cfgMoFu.Add(nId, stu);
    }
}

void CfgData::InitShenYaoEquipTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_SHENYAO_EQUIP_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_SHENYAO_EQUIP_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgShenYaoEquip stu = {};
        int32_t nPos = TabFile.Search_Posistion(i, 0)->iValue;
        int32_t nLevel = TabFile.Search_Posistion(i, 1)->iValue;
        stu.m_vAddAttr = parseEquipEffect(nPos * 10000 + nLevel, TabFile.Search_Posistion(i, 2)->pString);
        stu.nCostGold = TabFile.Search_Posistion(i, 3)->iValue;
        m_cfgShenYao.Add(nPos, nLevel, stu);
    }
}

void CfgData::InitEquipStrengthenTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_EQUIP_STRENGTHEN_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_EQUIP_STRENGTHEN_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgEquipStrengthen stu = {};
        int32_t nPos = TabFile.Search_Posistion(i, 0)->iValue;
        int32_t nLevel = TabFile.Search_Posistion(i, 1)->iValue;
        stu.m_vAddAttr = parseEquipEffect(nPos * 10000 + nLevel, TabFile.Search_Posistion(i, 2)->pString);
        stu.m_CostItem.m_nClass = TabFile.Search_Posistion(i, 3)->iValue;
        stu.m_CostItem.m_nId = TabFile.Search_Posistion(i, 4)->iValue;
        stu.m_CostItem.m_nCount = TabFile.Search_Posistion(i, 5)->iValue;
        stu.m_nGongGaoId = TabFile.Search_Posistion(i, 6)->iValue;
        m_cfgEquipStrengthen.Add(nPos, nLevel, stu);
    }
}

void CfgData::InitEquipUpPosTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_EQUIP_UP_POS_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_EQUIP_UP_POS_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgEquipUpPos stu = {};
        int32_t nPos = TabFile.Search_Posistion(i, 0)->iValue;
        int32_t nLevel = TabFile.Search_Posistion(i, 1)->iValue;
        stu.m_vAddAttr = parseEquipEffect(nPos * 10000 + nLevel, TabFile.Search_Posistion(i, 2)->pString);
        stu.m_nNeedLevel = TabFile.Search_Posistion(i, 3)->iValue;
        stu.m_CostItem.m_nClass = TabFile.Search_Posistion(i, 4)->iValue;
        stu.m_CostItem.m_nId = TabFile.Search_Posistion(i, 5)->iValue;
        stu.m_CostItem.m_nCount = TabFile.Search_Posistion(i, 6)->iValue;
        stu.m_nTotalRate = TabFile.Search_Posistion(i, 7)->iValue;
        stu.m_nRate = TabFile.Search_Posistion(i, 8)->iValue;
        stu.m_nGongGaoId = TabFile.Search_Posistion(i, 9)->iValue;
        m_cfgEquipUpPos.Add(nPos, nLevel, stu);
    }
}

void CfgData::InitCurrencyDuiHuanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_CURRENCY_DUIHUAN_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_CURRENCY_DUIHUAN_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgCurrencyDuiHuan stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.m_nMoShi = TabFile.Search_Posistion(i, 1)->iValue;
        stu.m_nShengYaoBi = TabFile.Search_Posistion(i, 2)->iValue;
        stu.m_nJinBi = TabFile.Search_Posistion(i, 3)->iValue;
        stu.m_nDailyLimit = TabFile.Search_Posistion(i, 4)->iValue;
        m_cfgCurrencyDuiHuan.Add(nId, stu);
    }
}

void CfgData::InitMoFuSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_MOFU_SUIT_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_MOFU_SUIT_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgMoFuSuit stu = {};
        int32_t nSuitId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nSuitId = nSuitId;
        stu.nNeedCount = TabFile.Search_Posistion(i, 1)->iValue;
        stu.vAddAttr = parseEquipEffect(nSuitId, TabFile.Search_Posistion(i, 2)->pString);
        m_cfgMoFuSuit.Add(nSuitId, stu);
    }
}

void CfgData::InitPetEquipTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_PET_EQUIP_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_PET_EQUIP_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgPetEquip stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nId = nId;
        stu.nPetId = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nEquipId = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nAttrType = TabFile.Search_Posistion(i, 3)->iValue;
        stu.nAttrValue = TabFile.Search_Posistion(i, 4)->iValue;
        stu.nLevel = TabFile.Search_Posistion(i, 5)->iValue;
        m_cfgPetEquip.Add(nId, stu);
    }
}

void CfgData::InitCityWarTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_CITY_WAR_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_CITY_WAR_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgCityWar stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nId = nId;
        stu.nMapId = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nDuration = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nRewardExp = TabFile.Search_Posistion(i, 3)->iValue;
        stu.nRewardMoney = TabFile.Search_Posistion(i, 4)->iValue;
        stu.nNeedLevel = TabFile.Search_Posistion(i, 5)->iValue;
        stu.nMinPlayer = TabFile.Search_Posistion(i, 6)->iValue;
        stu.nMaxPlayer = TabFile.Search_Posistion(i, 7)->iValue;
        m_cfgCityWar.Add(nId, stu);
    }
}

void CfgData::InitCampWarTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_CAMP_WAR_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_CAMP_WAR_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgCampWar stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nId = nId;
        stu.nMapId = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nDuration = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nNeedLevel = TabFile.Search_Posistion(i, 3)->iValue;
        stu.nRewardExp = TabFile.Search_Posistion(i, 4)->iValue;
        stu.nRewardMoney = TabFile.Search_Posistion(i, 5)->iValue;
        m_cfgCampWar.Add(nId, stu);
    }
}

void CfgData::InitPeerlessWarTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_PEERLESS_WAR_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_PEERLESS_WAR_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgPeerlessWar stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nId = nId;
        stu.nMapId = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nDuration = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nNeedLevel = TabFile.Search_Posistion(i, 3)->iValue;
        stu.nRewardExp = TabFile.Search_Posistion(i, 4)->iValue;
        stu.nRewardMoney = TabFile.Search_Posistion(i, 5)->iValue;
        stu.nMaxPlayer = TabFile.Search_Posistion(i, 6)->iValue;
        m_cfgPeerlessWar.Add(nId, stu);
    }
}

void CfgData::InitWorldBossTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_WORLD_BOSS_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_WORLD_BOSS_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgWorldBoss stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nId = nId;
        stu.nBossId = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nMapId = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nLevel = TabFile.Search_Posistion(i, 3)->iValue;
        stu.nReviveTime = TabFile.Search_Posistion(i, 4)->iValue;
        stu.nRewardExp = TabFile.Search_Posistion(i, 5)->iValue;
        stu.nRewardMoney = TabFile.Search_Posistion(i, 6)->iValue;
        stu.nHp = TabFile.Search_Posistion(i, 7)->iValue;
        stu.nAttack = TabFile.Search_Posistion(i, 8)->iValue;
        stu.nDefense = TabFile.Search_Posistion(i, 9)->iValue;
        m_cfgWorldBoss.Add(nId, stu);
    }
}

void CfgData::InitGemAddTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_GEM_ADD_TABLE);
    if (ret == false)
    {
        LOG_ERROR("open FILE_GEM_ADD_TABLE failed");
        return;
    }
    int32_t nCount = TabFile.GetRecordsNum();
    int32_t nCol = TabFile.GetFieldsNum();
    if (nCol <= 0) return;
    for (int32_t i = 0; i < nCount; ++i)
    {
        CfgGemAdd stu = {};
        int32_t nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nId = nId;
        stu.nGemType = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nAddRate = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nEffectValue = TabFile.Search_Posistion(i, 3)->iValue;
        m_cfgGemAdd.Add(nId, stu);
    }
}



WarVictoryHd* CfgData::GetWarVictoryHdCfg( int8_t Index )
{
	WarVictoryHdMap::iterator it = m_WarVictoryHdMap.find( Index );
	if ( it != m_WarVictoryHdMap.end() )
	{
		return &( it->second );
	}
	return NULL;
}


void CfgData::InitTotalChongZhiTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_TOTAL_CHONG_ZHI_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_TOTAL_CHONG_ZHI_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount -1 ;i++ ) //���ű����һ�������û��
	{
		CfgTotalChongZhi stu = {};
		stu.Index			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		stu.NeedGold		= TabFile.Search_Posistion(i,1)->iValue;
		stu.ItemVector		= parseEquipItemString( stu.Index,TabFile.Search_Posistion(i,2)->pString);
		stu.GongGaoInfo		= parseGongGaoString( stu.Index, TabFile.Search_Posistion(i,3)->pString );
		stu.NewServerday	= TabFile.Search_Posistion(i,4)->iValue;
		m_TotalChongZhiTable[stu.Index] = stu;
	}
}

CfgTotalChongZhi* CfgData::GetTotalChongZhiCfg( int8_t Index )
{	
	TotalChongZhiMap::iterator it = m_TotalChongZhiTable.find( Index );
	if ( it != m_TotalChongZhiTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

TotalChongZhiMap& CfgData::GetTotalChongZhiTable()
{
	return m_TotalChongZhiTable;
}

void CfgData::InitEveryDayChongZhi()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_EVERYDAY_CHONG_ZHI);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_EVERYDAY_CHONG_ZHI");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgEverydayChongZhi stu = {};
		stu.Index			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		stu.NeedGold		= TabFile.Search_Posistion(i,1)->iValue;
		stu.ItemVector		= parseEquipItemString( stu.Index,TabFile.Search_Posistion(i,2)->pString);
		stu.GongGaoInfo		= parseGongGaoString( stu.Index, TabFile.Search_Posistion(i,3)->pString );
		m_EveryDayChongZhiTable[stu.Index] = stu;
	}
}

CfgEverydayChongZhi* CfgData::GetEveryDayChongZhiCfg( int8_t Index )
{	
	EverydayChongZhiMap::iterator it = m_EveryDayChongZhiTable.find( Index );
	if ( it != m_EveryDayChongZhiTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

EverydayChongZhiMap& CfgData::GetEveryDayTable()
{
	return m_EveryDayChongZhiTable;
}

void CfgData::InitNewServerFavorable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_NEW_SERVER_FAVORABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_NEW_SERVER_FAVORABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		NewServerFavorable stu = {};
		stu.Index			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		stu.ItemVector		= parseEquipItemString( stu.Index,TabFile.Search_Posistion(i,1)->pString);
		stu.NeedGold		= TabFile.Search_Posistion(i,2)->iValue;
		stu.GongGaoInfo		= parseGongGaoString( stu.Index, TabFile.Search_Posistion(i,3)->pString );
		m_NewServerFavorable[stu.Index] = stu;
	}
	
	CDBCFile TabFile2(0);
	ret = TabFile2.OpenFromTXT(FILE_THREE_PET_GIFT);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_THREE_PET_GIFT");
		return;
	}

	iBaseTableCount			=	TabFile2.GetRecordsNum();
	iBaseColumnCount		=	TabFile2.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0; i < iBaseTableCount; i++ )
	{
		NewServerFavorable stu = {};
		m_ThreePetGift.Index			= (int8_t)TabFile2.Search_Posistion(i,0)->iValue;
		m_ThreePetGift.ItemVector		= parseEquipItemString( stu.Index,TabFile2.Search_Posistion(i,1)->pString);
		m_ThreePetGift.NeedGold			= TabFile2.Search_Posistion(i,2)->iValue;
		m_ThreePetGift.GongGaoInfo		= parseGongGaoString( stu.Index, TabFile2.Search_Posistion(i,3)->pString );
	}
}

NewServerFavorable& CfgData::GetThreePetGift()
{
	return m_ThreePetGift;
}

NewServerFavorable* CfgData::GetNewServerFavorable( int8_t Index )
{	
	NewServerFavorableMap::iterator it = m_NewServerFavorable.find( Index );
	if ( it != m_NewServerFavorable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

NewServerFavorableMap& CfgData::GetNewServerFavorableCfg()
{
	return m_NewServerFavorable;
}

void CfgData::InitShouChongLiBao()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_SHOU_CHONG_LI_BAO);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_SHOU_CHONG_LI_BAO");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		m_ShouChongLiBao	= parseEquipItemString( 1,TabFile.Search_Posistion(i,1)->pString);
	}
}

MemChrEquipBagVector& CfgData::GetShouChongLiBao()
{
	return m_ShouChongLiBao;
}

void CfgData::InitMoHuaHuanYiTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_MO_HUA_ZHUAN_YI_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_MO_HUA_ZHUAN_YI_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgEquipExchange stu = {};
		stu.Level			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		stu.CostType		= (int8_t)TabFile.Search_Posistion(i,1)->iValue;
		stu.Money			= TabFile.Search_Posistion(i,2)->iValue;
		stu.MoShi			= TabFile.Search_Posistion(i,3)->iValue;
		stu.BindMoShi		= TabFile.Search_Posistion(i,4)->iValue;
		m_CfgEquipExchangeMap[stu.Level] = stu;
	}
}

CfgEquipExchange* CfgData::GetEquipExchange( int8_t Level ) 
{
	CfgEquipExchangeMap::iterator it = m_CfgEquipExchangeMap.find( Level );
	if ( it != m_CfgEquipExchangeMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitZiYuanZhaoHuiTable()
{
	CDBCFile ItemGiftFile(0);
	bool retItemGift = ItemGiftFile.OpenFromTXT(FILE_ZYZH_TABLE);
	if ( retItemGift == false )
	{
		LOG_ERROR("open FILE_ZYZH_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Gift		=	ItemGiftFile.GetRecordsNum();
	int32_t iBaseColumnCount_Gift		=	ItemGiftFile.GetFieldsNum();
	if (iBaseColumnCount_Gift <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Gift;i++ )
	{
		CfgZiYuanZhaoHui stu  = {};
		stu.Index			= ItemGiftFile.Search_Posistion(i,0)->iValue;
		stu.Type			= ItemGiftFile.Search_Posistion(i,1)->iValue;
		stu.Times			= ItemGiftFile.Search_Posistion(i,2)->iValue;
		stu.Id				= ItemGiftFile.Search_Posistion(i,3)->iValue;
		stu.NeedMoney		= ItemGiftFile.Search_Posistion(i,4)->iValue;
		stu.NeedGold		= ItemGiftFile.Search_Posistion(i,5)->iValue;
		stu.GetCurrencyList	= paraseCurrency(ItemGiftFile.Search_Posistion(i,6)->pString);
		stu.GetExpValues	= ItemGiftFile.Search_Posistion(i,7)->iValue;
		m_ZiYuanZhaoHuiTable[stu.Index] =stu;
	}
}

CfgZYZHMap& CfgData::GetZYZHList()
{
	return m_ZiYuanZhaoHuiTable;
}

CfgZiYuanZhaoHui* CfgData::GetZiYuanZhaoHui( int32_t Index )
{
	CfgZYZHMap::iterator it = m_ZiYuanZhaoHuiTable.find( Index );
	if ( it != m_ZiYuanZhaoHuiTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitPlantEventTable()
{
	CDBCFile ItemGiftFile(0);
	bool retItemGift = ItemGiftFile.OpenFromTXT(FILE_PLANT_EVENT_TABLE);
	if ( retItemGift == false )
	{
		LOG_ERROR("open FILE_PLANT_EVENT_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Gift		=	ItemGiftFile.GetRecordsNum();
	int32_t iBaseColumnCount_Gift		=	ItemGiftFile.GetFieldsNum();
	if (iBaseColumnCount_Gift <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Gift;i++ )
	{
		CfgPlantEventEffect Event;
		Event.EventId						= ItemGiftFile.Search_Posistion(i,0)->iValue;
		Event.EventType						= ItemGiftFile.Search_Posistion(i,1)->iValue;
		Event.EventEffect					= ItemGiftFile.Search_Posistion(i,2)->pString;
		Event.GongGaoId						= ItemGiftFile.Search_Posistion(i,3)->iValue;
		m_PlantEventMap[Event.EventId] = Event;
	}
}

CfgPlantEventEffect* CfgData::GetPlantEvent( int32_t EventId )
{
	PlantEventMap::iterator it = m_PlantEventMap.find(EventId);
	if ( it != m_PlantEventMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}


void CfgData::InitAutoPetGfit()
{
	CDBCFile ItemGiftFile(0);
	bool retItemGift = ItemGiftFile.OpenFromTXT(FILE_AUTO_PET_GIFT);
	if ( retItemGift == false )
	{
		LOG_ERROR("open FILE_AUTO_PET_GIFT failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Gift		=	ItemGiftFile.GetRecordsNum();
	int32_t iBaseColumnCount_Gift		=	ItemGiftFile.GetFieldsNum();
	if (iBaseColumnCount_Gift <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Gift;i++ )
	{
		CfgItemGift itemGift;
		itemGift.id						= ItemGiftFile.Search_Posistion(i,0)->iValue;
		itemGift.item					= ItemGiftFile.Search_Posistion(i,2)->iValue;
		itemGift.type					= ItemGiftFile.Search_Posistion(i,3)->iValue;
		itemGift.count					= ItemGiftFile.Search_Posistion(i,4)->iValue;
	//	itemGift.bind					= ItemGiftFile.Search_Posistion(i,5)->iValue;
		itemGift.job					= ItemGiftFile.Search_Posistion(i,5)->iValue;

		CfgItemGiftTable::iterator it	= m_PetGifts.find(itemGift.id);
		if (it == m_PetGifts.end())
		{
			m_PetGifts[itemGift.id] = new CfgItemGiftVector;
		}
		m_PetGifts[itemGift.id]->push_back(itemGift);
	}
}

CfgItemGiftVector* CfgData::getPetGift(int32_t id)
{
	Answer::RwLockRdGuard lock(m_itemGiftsLock);

	CfgItemGiftTable::iterator it = m_PetGifts.find(id);
	if (it != m_PetGifts.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void CfgData::InitMoLingRuQinMap()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_MO_LING_RU_QING_HD_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_MO_LING_RU_QING_HD_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMoLingRuQinMapInfo stu = {};
		stu.MapId				= TabFile.Search_Posistion(i,0)->iValue;
		stu.NpcId				= TabFile.Search_Posistion(i,1)->iValue;
		stu.NpcCount			= TabFile.Search_Posistion(i,2)->iValue;
		stu.m_RevivePosVector	= paresPosition( TabFile.Search_Posistion(i,3)->pString );
		m_MoLingRuQinMap[stu.MapId] = stu;
	}
}

CfgMoLingRuQinMapInfo* CfgData::GetMLRQMapInfo( int32_t MapId )
{
	MoLingRuQinMap::iterator it = m_MoLingRuQinMap.find(MapId);
	if ( it != m_MoLingRuQinMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}


void CfgData::InitFunctionOpenTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_FUNCTION_OPEN_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_FUNCTION_OPEN_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		FunctionOpenCfg stu = {};
		stu.Type				= TabFile.Search_Posistion(i,2)->iValue;
		stu.TaskId				= TabFile.Search_Posistion(i,1)->iValue;
		stu.Level				= TabFile.Search_Posistion(i,3)->iValue;
		m_FunctionOpenCfg[stu.Type] = stu;
	}
}

FunctionOpenCfgMap& CfgData::GetOpenFunctionTable()
{
	return m_FunctionOpenCfg;
}

FunctionOpenCfg* CfgData::GetOpenFunctionCfg( int32_t FunctionId )
{
	FunctionOpenCfgMap::iterator it = m_FunctionOpenCfg.find( FunctionId );
	if ( it != m_FunctionOpenCfg.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitVipGuaJiMap()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_VIP_GUA_JI_MAP);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_VIP_GUA_JI_MAP");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		VipGuaJiMap stu = {};
		stu.MapId				= TabFile.Search_Posistion(i,0)->iValue;
		stu.StartTime			= TabFile.Search_Posistion(i,1)->iValue;
		stu.EndTime				= TabFile.Search_Posistion(i,2)->iValue;
		stu.VipLevel			= TabFile.Search_Posistion(i,3)->iValue;
		m_VipGuaJiMap[stu.MapId] = stu;
	}
}

bool CfgData::IsVipGuaJiMap( int32_t MapId )
{
	VipGuaJiMapTable::iterator it = m_VipGuaJiMap.find( MapId );
	if ( it != m_VipGuaJiMap.end() )
	{
		return true;
	}
	return false;
}

VipGuaJiMap* CfgData::GetVipGuaJiMapCfg( int32_t MapId)
{
	VipGuaJiMapTable::iterator it = m_VipGuaJiMap.find( MapId );
	if ( it != m_VipGuaJiMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitBossHomeTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_BOSS_HOME_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_BOSS_HOME_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgBossHome BossHomeCfg = {};
		BossHomeCfg.MapId				= TabFile.Search_Posistion(i,0)->iValue;
		BossHomeCfg.Grade			= TabFile.Search_Posistion(i,1)->iValue;
		BossHomeCfg.EnterPosVector		= paresPosition(TabFile.Search_Posistion(i,2)->pString);
		BossHomeCfg.NeedVipLevel		= TabFile.Search_Posistion(i,3)->iValue;
		BossHomeCfg.NeedGold			= TabFile.Search_Posistion(i,4)->iValue;
		BossHomeCfg.IntervalTime		= TabFile.Search_Posistion(i,5)->iValue;
		BossHomeCfg.NeedCash			= TabFile.Search_Posistion(i,6)->iValue;
		parasItemData( BossHomeCfg.CostItem, TabFile.Search_Posistion(i,7)->pString );
		m_BossHomeTable[BossHomeCfg.MapId] = BossHomeCfg;
	}
}

CfgBossHome* CfgData::GetBossHomeCfg( int32_t MapId )
{
	BossHomeTable::iterator it = m_BossHomeTable.find( MapId );
	if ( it != m_BossHomeTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

bool CfgData::IsBossHomeMap( int32_t MapId )
{
	BossHomeTable::iterator it = m_BossHomeTable.find( MapId );
	if ( it != m_BossHomeTable.end() )
	{
		return true;
	}
	return false;
}

void CfgData::InitVipCardTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_VIP_CARD_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_VIP_CARD_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		VipCardCfg VipCard = {};
		VipCard.VipCardId			= TabFile.Search_Posistion(i,0)->iValue;
		VipCard.AddVipExp			= TabFile.Search_Posistion(i,1)->iValue;
		VipCard.DailyAddExp			= TabFile.Search_Posistion(i,2)->iValue;
		VipCard.AddVipTime			= TabFile.Search_Posistion(i,3)->iValue;
		VipCard.NeedGold			= TabFile.Search_Posistion(i,4)->iValue;
		VipCard.ExpRate				= TabFile.Search_Posistion(i,5)->iValue;
		VipCard.AddPlayerExp		= TabFile.Search_Posistion(i,6)->iValue;
		VipCard.AddPetExp			= TabFile.Search_Posistion(i,7)->iValue;
		for ( int32_t j = 0; j < 5; j++ )
		{
			AddAttribute stu;
			stu.m_nAddAttrType		= TabFile.Search_Posistion( i,j * 2 + 8 )->iValue;
			stu.m_nAddAttrValue		= TabFile.Search_Posistion( i,j * 2 + 9 )->iValue;
			if ( stu.m_nAddAttrValue <= 0 || stu.m_nAddAttrType <= 0 )
			{
				continue;
			}
			VipCard.AddAttr.push_back( stu );
		}
		VipCard.Items				= parseItemString( VipCard.VipCardId, TabFile.Search_Posistion( i,18 )->pString );
		m_VipCardTable[VipCard.VipCardId] = VipCard;
	}
}

VipCardCfg* CfgData::GetVipCardCfg( int8_t VipType )
{
	VipCardCfgMap::iterator it = m_VipCardTable.find( VipType );
	if ( it != m_VipCardTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitOffLineExpTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_OFF_LINE_EXP_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_OFF_LINE_EXP_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgOffLineExp reward = {};
		reward.Level			= TabFile.Search_Posistion(i,1)->iValue;
		reward.MinuteExp		= TabFile.Search_Posistion(i,2)->iValue;
		reward.TwoTimes			= TabFile.Search_Posistion(i,3)->iValue;
		reward.ThreeTimes		= TabFile.Search_Posistion(i,4)->iValue;
		reward.BaseExp			= TabFile.Search_Posistion(i,5)->iValue;
		m_OffLineExpTable[reward.Level] = reward;
	}
}

CfgOffLineExp* CfgData::GetOfflineExpCfg( int32_t Level )
{
	CfgOffLineExpTable::iterator it = m_OffLineExpTable.lower_bound( Level );
	if ( it != m_OffLineExpTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitWeekOnlineReward()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_WEEK_ONLINE_REWARD);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_WEEK_ONLINE_REWARD");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgWeekOnlineReward reward = {};
		reward.Week				= TabFile.Search_Posistion(i,0)->iValue;
		reward.Cash				= TabFile.Search_Posistion(i,1)->iValue;
		reward.UpperLimit	    = TabFile.Search_Posistion(i,2)->iValue;
		m_WeekOnlineReward[reward.Week] = reward;
	}
}

CfgWeekOnlineReward* CfgData::GetWeekOnlineReward( int32_t Week )
{
	if ( Week <= 0 )
	{
		return NULL;
	}
	CfgWeekOnlineRewardTable::iterator it = m_WeekOnlineReward.find( Week );
	if ( it != m_WeekOnlineReward.end() )
	{
		return &(it->second);
	}
	CfgWeekOnlineRewardTable::reverse_iterator Rit = m_WeekOnlineReward.rbegin();
	if ( Rit != m_WeekOnlineReward.rend() )
	{
		return &(Rit->second);
	}
	return NULL;
}

void CfgData::InitLevelGift()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_LEVEL_GIFT);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_LEVEL_GIFT");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgLevelGift reward = {};
		reward.Index			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		reward.Level			= TabFile.Search_Posistion(i,1)->iValue;
		reward.ItemVector	    = parseItemString(reward.Index,TabFile.Search_Posistion(i,2)->pString);
		m_LevelGift[reward.Index] = reward;
	}
}

CfgLevelGift* CfgData::GetLevelGiftCfg( int8_t Index )
{
	CfgLevelGiftTable::iterator it= m_LevelGift.find( Index );
	if ( it != m_LevelGift.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgLevelGiftTable& CfgData::GetLeveGiftTable()
{
	return m_LevelGift;
}

void CfgData::InitSevenLoginReward()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_SEVEN_LOGIN_REWARD);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_SEVEN_LOGIN_REWARD");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgSevenLoginRewrad reward = {};
		reward.Day			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		reward.ItemVector	= parseEquipItemString(reward.Day,TabFile.Search_Posistion(i,1)->pString);
		m_SevenLoginReward[reward.Day] = reward;
	}
}

CfgSevenLoginRewrad* CfgData::GetSevenLoginRewardCfg( int8_t Day )
{
	CfgSevenLoginRewradTable::iterator it= m_SevenLoginReward.find( Day );
	if ( it != m_SevenLoginReward.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitOnLimeReward()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_ONLINE_REWARD);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_ONLINE_REWARD");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgOnlineReward reward = {};
		reward.Id			= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		reward.NeedTime		= TabFile.Search_Posistion(i,1)->iValue;
		reward.ItemVector	= parseItemString(reward.Id,TabFile.Search_Posistion(i,2)->pString);
		m_OnLineReward[reward.Id] = reward;
	}
}

CfgOnlineReward* CfgData::GetOnlineRewardCfg( int8_t id )
{
	CfgOnlineRewardTable::iterator it= m_OnLineReward.find( id );
	if ( it != m_OnLineReward.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgOnlineRewardTable& CfgData::GetOnLineRewardTable()
{
	return m_OnLineReward;
}


void CfgData::fetchSignReward()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_SIGIN_REWARD_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� FILE_SIGIN_REWARD_TABLE");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgSignReward reward = {};
		reward.count = (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		reward.ItemVector = parseItemString(reward.count,TabFile.Search_Posistion(i,1)->pString);
		m_signReward[reward.count] = reward;
	}
}

MemChrBagVector CfgData::GetSignReward( int8_t SiginCount )
{
	MemChrBagVector items;
	CfgSignRewardTable::iterator it = m_signReward.find(SiginCount);
	if ( it != m_signReward.end() )
	{
		items = it->second.ItemVector; 
	}
	return items;
}

CfgSignRewardTable& CfgData::GetSignRewardTable()
{
	return m_signReward;
}

void CfgData::fetchYellowStone()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_yellow_stone.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_yellow_stone.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgYellowStone yellowAward={};
		yellowAward.id			= TabFile.Search_Posistion(i,0)->iValue;
		yellowAward.level		= TabFile.Search_Posistion(i,1)->iValue;
		yellowAward.yellow_type = TabFile.Search_Posistion(i,2)->iValue;
		string SwardsString		= TabFile.Search_Posistion(i,3)->pString;
		yellowAward.awards		= parseItemString( yellowAward.id, SwardsString.c_str() );
		m_yellowStone[yellowAward.id] = yellowAward;
	}		
}

void CfgData::fetchActivity()
{
	CDBCFile ActivityFile(0);
	bool ret = ActivityFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_activity.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	ActivityFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	ActivityFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgActivity activity;
		activity.id					= ActivityFile.Search_Posistion(i,0)->iValue;
		activity.level				= ActivityFile.Search_Posistion(i,5)->iValue;
		int32_t weekday				= ActivityFile.Search_Posistion(i,9)->iValue;
		activity.begin_date			= ActivityFile.Search_Posistion(i,10)->iValue;
		activity.end_date			= ActivityFile.Search_Posistion(i,11)->iValue;
		activity.line				= ActivityFile.Search_Posistion(i,12)->iValue;
		std::string maps			= ActivityFile.Search_Posistion(i,13)->pString;
		std::string start_hour		= ActivityFile.Search_Posistion(i,14)->pString;
		activity.duration			= ActivityFile.Search_Posistion(i,15)->iValue;
		std::string position		= ActivityFile.Search_Posistion(i,17)->pString;
		std::string awards			= ActivityFile.Search_Posistion(i,18)->pString;
		activity.typeId				= static_cast<int16_t>(ActivityFile.Search_Posistion(i,21)->iValue);
		activity.exp_add_interval	= ActivityFile.Search_Posistion(i,23)->iValue;
		activity.iconid				= ActivityFile.Search_Posistion(i,24)->iValue;
		std::string daily			= ActivityFile.Search_Posistion(i,25)->pString;
		
		while (weekday > 0)
		{
			activity.weekday.push_back(weekday%10);
			weekday /= 10;
		}
		
		if(strlen(awards.c_str()) >0)
		{
			StringVector strParams = StringUtility::split(awards.c_str(), ":");
			int16_t nsize =strParams.size();
			activity.gift_id.resize(nsize);
			for ( int32_t j = 0; j< nsize; ++j )
			{
				activity.gift_id[j] = atoi( strParams[j].c_str() );
			}
		}

		if(strlen(daily.c_str()) >0)
		{
			StringVector strParams = StringUtility::split(daily.c_str(), ":");
			int16_t nsize =strParams.size();
			activity.daily_reward.resize(nsize);
			for ( int32_t j = 0; j< nsize; ++j )
			{
				activity.daily_reward[j] = atoi( strParams[j].c_str() );
			}
		}

		StringVector strMaps = StringUtility::split( maps.c_str(), ":" );
		if ( strMaps.size() > 0 )
		{
			for ( uint32_t j = 0; j < strMaps.size(); ++j )
			{
				activity.maps.push_back( atoi( strMaps[j].c_str() ) );
			}
		}

		StringVector strParams = StringUtility::split(position.c_str(), ":");
		if(strParams.size()==2)
		{
			activity.target_mapid = atoi(strParams[0].c_str());

			StringVector stritemParams = StringUtility::split(strParams[1].c_str(), "|");
			int32_t nlenth =stritemParams.size();
			for ( int32_t j = 0; j < nlenth; ++j )
			{
				activity.target_regiona.push_back(atoi(stritemParams[j].c_str()));
			}
		}
		else if (strParams.size() == 3)
		{
			activity.target_mapid = atoi(strParams[0].c_str());

			StringVector stritemParams = StringUtility::split(strParams[1].c_str(), "|");
			int32_t nlenth =stritemParams.size();
			for ( int32_t j = 0; j < nlenth; ++j )
			{
				activity.target_regiona.push_back(atoi(stritemParams[j].c_str()));
			}

			stritemParams = StringUtility::split(strParams[2].c_str(), "|");
			nlenth =stritemParams.size();
			for (int32_t k = 0;k < nlenth;k++)
			{
				activity.target_regionb.push_back(atoi(stritemParams[k].c_str()));
			}
		}

		StringVector vStartHour = StringUtility::split( start_hour, ":" );
		if ( vStartHour.size() > 0 )
		{
			for ( uint32_t j = 0; j < vStartHour.size(); ++j )
			{
				int32_t tstart = atoi( vStartHour[j].c_str() );
				if ( tstart < 0 || tstart >= 60*24 || activity.duration < 0 || tstart+activity.duration >= 60*24 )
				{
					LOG_ERROR("wrong activity data with id=%d\n", activity.id);
				}
				else
				{
					activity.start_hour.push_back( tstart );
				}
			}
		}
		activity.state = AS_NOT_START;

		m_activities[activity.id] = activity;
	}

	CDBCFile ActivityEventFile(0);
	bool retEvent = ActivityEventFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity_event.txt");
	if ( retEvent == false )
	{
		LOG_ERROR("open cfg_activity_event.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Event		=	ActivityEventFile.GetRecordsNum();
	int32_t iBaseColumnCount_Event		=	ActivityEventFile.GetFieldsNum();
	if (iBaseColumnCount_Event <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Event;i++ )
	{
		CfgMapEvent activityEvent;
		int32_t nIndex = 0;
		activityEvent.id				= ActivityEventFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		activityEvent.mapid				= ActivityEventFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		activityEvent.trigger_id		= ActivityEventFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		activityEvent.bOpen				= ActivityEventFile.Search_Posistion( i, nIndex )->iValue == 0;	++nIndex;
		activityEvent.trigger_type		= ActivityEventFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		std::string triggerParam		= ActivityEventFile.Search_Posistion( i, nIndex )->pString;		++nIndex;
		activityEvent.event_type		= ActivityEventFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		activityEvent.effect			= ActivityEventFile.Search_Posistion( i, nIndex )->pString;		++nIndex;
		//activityEvent.dialog			= ActivityEventFile.Search_Posistion( i, nIndex )->pString;		++nIndex;
		
		StringVector strParams			= StringUtility::split(triggerParam.c_str(), ":");
		for (StringVector::iterator it = strParams.begin(); it != strParams.end(); ++it)
		{
			activityEvent.trigger_param.push_back(atoi(it->c_str()));
		}
		
		//StringVector strEffects = StringUtility::split(eventEffect.c_str(), ":");
		//for (StringVector::iterator it = strEffects.begin(); it != strEffects.end(); ++it)
		//{
		//	activityEvent.effect.push_back(atoi(it->c_str()));
		//}

		activityEvent.bDone = false;
		m_activityEvents[activityEvent.id][activityEvent.mapid].push_back(activityEvent);
	}

	CDBCFile ActivityMonsterFile(0);
	bool retMonster = ActivityMonsterFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity_monster.txt");
	if ( retMonster == false )
	{
		LOG_ERROR("open cfg_activity_monster.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Monster		=	ActivityMonsterFile.GetRecordsNum();
	int32_t iBaseColumnCount_Monster	=	ActivityMonsterFile.GetFieldsNum();
	if (iBaseColumnCount_Monster <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Monster;i++ )
	{
		CfgActivityMonster monster;
		monster.id			= ActivityMonsterFile.Search_Posistion(i,0)->iValue;
		monster.wave		= ActivityMonsterFile.Search_Posistion(i,1)->iValue;
		monster.mid			= ActivityMonsterFile.Search_Posistion(i,2)->iValue;
		monster.x			= ActivityMonsterFile.Search_Posistion(i,3)->iValue;
		monster.y			= ActivityMonsterFile.Search_Posistion(i,4)->iValue;
		monster.count		= ActivityMonsterFile.Search_Posistion(i,5)->iValue;
		monster.side		= ActivityMonsterFile.Search_Posistion(i,6)->iValue;
		std::string road	= ActivityMonsterFile.Search_Posistion(i,7)->pString;
		monster.delay		= ActivityMonsterFile.Search_Posistion(i,8)->iValue;
		monster.times		= ActivityMonsterFile.Search_Posistion(i,9)->iValue;
		if ( road.size() > 3 )
		{
			StringVector vRoad = Answer::StringUtility::split( road, ":" );
			for ( uint32_t j = 0; j < vRoad.size(); ++j )
			{
				StringVector vPos = Answer::StringUtility::split( vRoad[j], "," );
				if ( vPos.size() == 2 )
				{
					monster.road.push_back( Position( atoi( vPos[0].c_str() ), atoi( vPos[1].c_str() ) ) );
				}
			}
		}

		m_activityMonsters[monster.id] = monster;
	}

	CDBCFile ActivityNpcFile(0);
	bool retNpc = ActivityNpcFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity_npc.txt");
	if ( retNpc == false )
	{
		LOG_ERROR("open cfg_activity_npc.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Npc		=	ActivityNpcFile.GetRecordsNum();
	int32_t iBaseColumnCount_Npc	=	ActivityNpcFile.GetFieldsNum();
	if (iBaseColumnCount_Npc <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Npc;i++ )
	{
		CfgActivityNpc npc;
		npc.id					= ActivityNpcFile.Search_Posistion(i,0)->iValue;
		npc.activity_id			= ActivityNpcFile.Search_Posistion(i,1)->iValue;
		npc.npc_id				= ActivityNpcFile.Search_Posistion(i,2)->iValue;
		npc.count				= ActivityNpcFile.Search_Posistion(i,3)->iValue;
		std::string regionId	= ActivityNpcFile.Search_Posistion(i,4)->pString;

		StringVector strRegions = StringUtility::split(regionId.c_str(), ":");
		for (StringVector::iterator it = strRegions.begin(); it != strRegions.end(); ++it)
		{
			npc.region_id.push_back(atoi(it->c_str()));
		}
		m_activityNpcs[npc.id]=(npc);
	}

	CDBCFile ActivityPlantFile(0);
	bool retPlant = ActivityPlantFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity_plant.txt");
	if ( retPlant == false )
	{
		LOG_ERROR("open cfg_activity_plant.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Plant		=	ActivityPlantFile.GetRecordsNum();
	int32_t iBaseColumnCount_Plant		=	ActivityPlantFile.GetFieldsNum();
	if (iBaseColumnCount_Plant <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Plant;i++ )
	{
		CfgActivityPlant plant;
		plant.id					= ActivityPlantFile.Search_Posistion(i,0)->iValue;
		plant.activity_id			= ActivityPlantFile.Search_Posistion(i,1)->iValue;
		plant.plant_id				= ActivityPlantFile.Search_Posistion(i,2)->iValue;
		plant.count					= ActivityPlantFile.Search_Posistion(i,3)->iValue;
		plant.wave					= ActivityPlantFile.Search_Posistion(i,4)->iValue;
		plant.region_id				= ActivityPlantFile.Search_Posistion(i,5)->iValue;
		plant.whoplant				= ActivityPlantFile.Search_Posistion(i,6)->iValue;
		plant.EnterPosVector		= paresPosition(ActivityPlantFile.Search_Posistion(i,7)->pString);
		m_activityPlants[plant.id]=plant;
	}

	CDBCFile ActivityDropFile(0);
	bool retDrop = ActivityDropFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity_drop.txt");
	if ( retDrop == false )
	{
		LOG_ERROR("open cfg_activity_drop.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Drop		=	ActivityDropFile.GetRecordsNum();
	int32_t iBaseColumnCount_Drop		=	ActivityDropFile.GetFieldsNum();
	if (iBaseColumnCount_Drop <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Drop;i++ )
	{
		CfgActivityDrop drop;
		drop.id						= ActivityDropFile.Search_Posistion(i,0)->iValue;
		drop.activity_id			= ActivityDropFile.Search_Posistion(i,1)->iValue;
		drop.monster_min_level		= ActivityDropFile.Search_Posistion(i,2)->iValue;
		drop.drop_group_id			= ActivityDropFile.Search_Posistion(i,3)->iValue;
		drop.probability			= ActivityDropFile.Search_Posistion(i,4)->iValue;

		m_activityDrops[drop.id] = drop;
	}

	CDBCFile ActivityTrapFile(0);
	bool retTrap = ActivityTrapFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity_trap.txt");
	if ( retTrap == false )
	{
		LOG_ERROR("open cfg_activity_trap.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Trap		=	ActivityTrapFile.GetRecordsNum();
	int32_t iBaseColumnCount_Trap		=	ActivityTrapFile.GetFieldsNum();
	if ( iBaseColumnCount_Trap <=0 )
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Trap;i++ )
	{
		CfgActivityTrap trap;
		trap.id		= ActivityTrapFile.Search_Posistion(i,0)->iValue;
		trap.tid	= ActivityTrapFile.Search_Posistion(i,1)->iValue;
		trap.x		= ActivityTrapFile.Search_Posistion(i,2)->iValue;
		trap.y		= ActivityTrapFile.Search_Posistion(i,3)->iValue;

		m_activityTraps[trap.id] = trap;
	}
}

void CfgData::fetchAnnoucementTime()
{
	MySqlDBGuard db(DBPOOL);

	MySqlQuery result = db.query("SELECT * FROM `sys_annoucement_time` ORDER BY hour, minute ASC");
	while (!result.eof())
	{
		CfgAnnoucementTime annoucementTime;
		annoucementTime.id = result.getIntValue("id");
		int32_t weekday = result.getIntValue("weekday");
		while (weekday > 0)
		{
			annoucementTime.weekday.push_back(weekday%10);
			weekday /= 10;
		}
		annoucementTime.begin_date = result.getIntValue("begin_date");
		annoucementTime.end_date = result.getIntValue("end_date");
		annoucementTime.hour = result.getIntValue("hour");
		annoucementTime.minute = result.getIntValue("minute");
		annoucementTime.annoucement_id = result.getIntValue("annoucement_id");

		m_annoucementTimes.push_back(annoucementTime);

		result.nextRow();
	}
}

void CfgData::fetchBuff()
{
	CDBCFile BuffFile(0);
	bool ret = BuffFile.OpenFromTXT("./ServerConfig/Tables/cfg_buff.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_buff.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	BuffFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	BuffFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgBuff buff;
		buff.id							= BuffFile.Search_Posistion(i,0)->iValue;
		buff.beneficial					= BuffFile.Search_Posistion(i,3)->iValue;
		buff.special					= BuffFile.Search_Posistion(i,4)->iValue;
		buff.duration					= BuffFile.Search_Posistion(i,5)->iValue;
		buff.interval					= BuffFile.Search_Posistion(i,6)->iValue;
		buff.buffAttr[0].attr			= BuffFile.Search_Posistion(i,7)->iValue;
		buff.buffAttr[0].ratio_base		= BuffFile.Search_Posistion(i,8)->iValue;
		buff.buffAttr[0].ratio_ratio	= BuffFile.Search_Posistion(i,9)->iValue;
		buff.buffAttr[0].addon_base		= BuffFile.Search_Posistion(i,10)->iValue;
		buff.buffAttr[0].addon_ratio	= BuffFile.Search_Posistion(i,11)->iValue;
		buff.buffAttr[1].attr			= BuffFile.Search_Posistion(i,12)->iValue;
		buff.buffAttr[1].ratio_base		= BuffFile.Search_Posistion(i,13)->iValue;
		buff.buffAttr[1].ratio_ratio	= BuffFile.Search_Posistion(i,14)->iValue;
		buff.buffAttr[1].addon_base		= BuffFile.Search_Posistion(i,15)->iValue;
		buff.buffAttr[1].addon_ratio	= BuffFile.Search_Posistion(i,16)->iValue;
		buff.isShow						= BuffFile.Search_Posistion(i,18)->iValue;
		m_buffs[buff.id] = buff;
	}
}

CurrencyList CfgData::paraseCurrency( const std::string& str )
{
	CurrencyList TmpList;
	TmpList.clear();
	StringVector vstr = Answer::StringUtility::split( str, ":" );
	if ( vstr.size() == 2 )
	{
		CurrencyStu stu = {};
		stu.Type		= atoi( vstr[0].c_str() );
		stu.Values		= atoi( vstr[1].c_str() );
		TmpList.push_back(stu);
	}
	return TmpList;
}

void CfgData::parasItemData( ItemData& data, const std::string& str )
{
	bzero( &data, sizeof( data ) );
	StringVector vstr = Answer::StringUtility::split( str, ":" );
	if ( vstr.size() == 3 )
	{
		data.m_nClass	= atoi( vstr[0].c_str() );
		data.m_nId		= atoi( vstr[1].c_str() );
		data.m_nCount	= atoi( vstr[2].c_str() );
	}
}

void CfgData::parasItemData( MemChrBag& data, const std::string& str )
{
	bzero( &data, sizeof( data ) );
	StringVector vstr = Answer::StringUtility::split( str, ":" );
	if ( vstr.size() == 3 )
	{
		data.itemClass	= atoi( vstr[0].c_str() );
		data.itemId		= atoi( vstr[1].c_str() );
		data.itemCount	= atoi( vstr[2].c_str() );
	}
	else if ( vstr.size() == 4 )
	{
		data.itemClass	= atoi( vstr[0].c_str() );
		data.itemId		= atoi( vstr[1].c_str() );
		data.itemCount	= atoi( vstr[2].c_str() );
		data.bind		= atoi( vstr[3].c_str() );
	}
}

void CfgData::fetchDungeon()
{
	CDBCFile DungeonFile(0);
	bool ret = DungeonFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_dungeon.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	DungeonFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	DungeonFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	int32_t nIndex = 0;
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		nIndex = 0;
		CfgDungeon dungeon;
		dungeon.id				= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.name			= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;
		++nIndex;
		++nIndex;
		dungeon.mapid			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.x				= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.y				= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.type			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		dungeon.group_id		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.duration		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.level			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.maxLevel		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.vip				= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.player_num		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		int32_t weekday			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.start_hour		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.end_hour		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.daily_count		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		dungeon.last_id			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.next_id			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.player_buff		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		++nIndex;
		dungeon.star			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.double_cost		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.reward_time		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		std::string	costItem	= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;
		std::string	rewardItem	= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;
		std::string	rewardOnce	= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;
		++nIndex;
		dungeon.Battle			= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.costMoney		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.costGold		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;

		while (weekday > 0)
		{
			dungeon.weekday |= 1<<(weekday%10);
			weekday /= 10;
		}

		parasItemData( dungeon.costItem, costItem );
		parasItemData( dungeon.rewardOnce, rewardOnce );
		parasItemData( dungeon.rewardItem, rewardItem );
		m_dungeons[dungeon.id] = dungeon;
	}

	CDBCFile DungeonRewardFile(0);
	bool retReward = DungeonRewardFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_reward.txt");
	if ( retReward == false )
	{
		LOG_ERROR("open cfg_dungeon_reward.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Reward		=	DungeonRewardFile.GetRecordsNum();
	int32_t iBaseColumnCount_Reward		=	DungeonRewardFile.GetFieldsNum();
	if (iBaseColumnCount_Reward <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Reward;i++ )
	{
		CfgDungeonReward  reward;
		reward.dungeonID			= DungeonRewardFile.Search_Posistion(i,0)->iValue;
		reward.exp					= DungeonRewardFile.Search_Posistion(i,1)->iValue;
		reward.money				= DungeonRewardFile.Search_Posistion(i,2)->iValue;
		reward.cash					= DungeonRewardFile.Search_Posistion(i,3)->iValue;
		reward.groupID				= DungeonRewardFile.Search_Posistion(i,4)->iValue;

		m_dungeonReward[reward.dungeonID] =  reward;
	}

	CDBCFile DungeonDropFile(0);
	bool retDrop = DungeonDropFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_drop_group.txt");
	if ( retDrop == false )
	{
		LOG_ERROR("open cfg_dungeon_drop_group.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Drop		=	DungeonDropFile.GetRecordsNum();
	int32_t iBaseColumnCount_Drop		=	DungeonDropFile.GetFieldsNum();
	if (iBaseColumnCount_Drop <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Drop;i++ )
	{
		CfgDungeonDrop group;
		int32_t	id				= DungeonDropFile.Search_Posistion( i, 0 )->iValue;
		group.type				= DungeonDropFile.Search_Posistion( i, 1 )->iValue;
		group.item_id			= DungeonDropFile.Search_Posistion( i, 3 )->iValue;
		group.item_class		= DungeonDropFile.Search_Posistion( i, 4 )->iValue;
		group.bind_type			= DungeonDropFile.Search_Posistion( i, 5 )->iValue;
		group.count				= DungeonDropFile.Search_Posistion( i, 6 )->iValue;
		group.weight			= DungeonDropFile.Search_Posistion( i, 7 )->iValue;
		group.probability		= DungeonDropFile.Search_Posistion( i, 8 )->iValue;

		m_dungeonDropGroup[id].Add(group);
	}
}

void CfgData::fetchDungeonEvent()
{
	CDBCFile DungeonEventFile(0);
	bool ret = DungeonEventFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_event.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_dungeon_event.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	DungeonEventFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	DungeonEventFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMapEvent dungeonEvent;
		dungeonEvent.id				= DungeonEventFile.Search_Posistion(i,0)->iValue;
		dungeonEvent.trigger_id		= DungeonEventFile.Search_Posistion(i,1)->iValue;
		dungeonEvent.bOpen			= DungeonEventFile.Search_Posistion(i,2)->iValue == 0;
		dungeonEvent.trigger_type	= DungeonEventFile.Search_Posistion(i,3)->iValue;
		std::string triggerParam	= DungeonEventFile.Search_Posistion(i,4)->pString;
		dungeonEvent.event_type		= DungeonEventFile.Search_Posistion(i,5)->iValue;
		dungeonEvent.effect			= DungeonEventFile.Search_Posistion(i,6)->pString;
		//dungeonEvent.dialog		= DungeonEventFile.Search_Posistion(i,7)->pString;

		StringVector strTriggerParam= StringUtility::split(triggerParam.c_str(), ":");
		for (StringVector::iterator it = strTriggerParam.begin(); it != strTriggerParam.end(); ++it)
		{
			dungeonEvent.trigger_param.push_back(atoi(it->c_str()));
		}
		dungeonEvent.bDone = false;

		if (!dungeonEvent.trigger_param.empty())
		{
			m_dungeonEvents[dungeonEvent.id].push_back(dungeonEvent);
		}
	}
}

void CfgData::fetchDungeonMonster()
{
	CDBCFile DungeonMonsterFile(0);
	bool ret = DungeonMonsterFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_monster.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_dungeon_monster.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	DungeonMonsterFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	DungeonMonsterFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgDungeonMonster monster;
		monster.id			= DungeonMonsterFile.Search_Posistion(i,0)->iValue;
		monster.wave		= DungeonMonsterFile.Search_Posistion(i,1)->iValue;
		monster.mid			= DungeonMonsterFile.Search_Posistion(i,2)->iValue;
		monster.x			= DungeonMonsterFile.Search_Posistion(i,3)->iValue;
		monster.y			= DungeonMonsterFile.Search_Posistion(i,4)->iValue;
		monster.count		= DungeonMonsterFile.Search_Posistion(i,5)->iValue;
		monster.side		= DungeonMonsterFile.Search_Posistion(i,6)->iValue;
		std::string road	= DungeonMonsterFile.Search_Posistion(i,7)->pString;
		monster.delay		= DungeonMonsterFile.Search_Posistion(i,8)->iValue;
		monster.times		= DungeonMonsterFile.Search_Posistion(i,9)->iValue;
		monster.money		= DungeonMonsterFile.Search_Posistion(i,10)->iValue;
		if ( road.size() > 3 )
		{
			StringVector vRoad = Answer::StringUtility::split( road, ":" );
			for ( uint32_t j = 0; j < vRoad.size(); ++j )
			{
				StringVector vPos = Answer::StringUtility::split( vRoad[j], "," );
				if ( vPos.size() == 2 )
				{
					monster.road.push_back( Position( atoi( vPos[0].c_str() ), atoi( vPos[1].c_str() ) ) );
				}
			}
		}

		m_dungeonMonsters[monster.id] = monster;
	}
}

void CfgData::fetchDungeonPlant()
{
	CDBCFile DungeonPlantFile(0);
	bool ret = DungeonPlantFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_plant.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_dungeon_plant.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	DungeonPlantFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	DungeonPlantFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgDungeonPlant dungeonPlant;
		dungeonPlant.id						= DungeonPlantFile.Search_Posistion(i,0)->iValue;
		dungeonPlant.pid					= DungeonPlantFile.Search_Posistion(i,1)->iValue;
		dungeonPlant.x						= DungeonPlantFile.Search_Posistion(i,2)->iValue;
		dungeonPlant.y						= DungeonPlantFile.Search_Posistion(i,3)->iValue;
		m_dungeonPlants[dungeonPlant.id]	= dungeonPlant;
	}
}

void CfgData::fetchDungeonTrap()
{
	CDBCFile DungeonTrapFile(0);
	bool ret = DungeonTrapFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_trap.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_dungeon_trap.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	DungeonTrapFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	DungeonTrapFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgDungeonTrap dungeonTrap;
		dungeonTrap.id					= DungeonTrapFile.Search_Posistion(i,0)->iValue;
		dungeonTrap.tid					= DungeonTrapFile.Search_Posistion(i,1)->iValue;
		dungeonTrap.x					= DungeonTrapFile.Search_Posistion(i,2)->iValue;
		dungeonTrap.y					= DungeonTrapFile.Search_Posistion(i,3)->iValue;

		m_dungeonTraps[dungeonTrap.id]	= dungeonTrap;
	}
}

void CfgData::fetchChrShop()
{
	CDBCFile ChrShopFile(0);
	bool ret = ChrShopFile.OpenFromTXT("./ServerConfig/Tables/cfg_chr_shop.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_chr_shop.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	ChrShopFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	ChrShopFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgChrShop  chrShop;
		chrShop.Index			= ChrShopFile.Search_Posistion(i,0)->iValue;
		chrShop.ItemId			= ChrShopFile.Search_Posistion(i,1)->iValue;
		chrShop.ItemClass		= ChrShopFile.Search_Posistion(i,2)->iValue;
		chrShop.IsBind			= ChrShopFile.Search_Posistion(i,3)->iValue;
		chrShop.LimitCount		= ChrShopFile.Search_Posistion(i,4)->iValue;
		chrShop.Price			= ChrShopFile.Search_Posistion(i,5)->iValue;
		m_chrShops[chrShop.Index]	= chrShop;
	}
}

void CfgData::fetchItem(bool bSend)
{
	CfgItemTable newItems;
	m_itemsLock.wrlock();
	CDBCFile ItemFile(0);
	bool ret = ItemFile.OpenFromTXT("./ServerConfig/Tables/cfg_item.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_item.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	ItemFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	ItemFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgItem *pItem			= new CfgItem;
		pItem->id				= ItemFile.Search_Posistion(i,0)->iValue;
		pItem->name				= ItemFile.Search_Posistion(i,1)->pString;
		pItem->desc				= ItemFile.Search_Posistion(i,3)->pString;
		pItem->type				= ItemFile.Search_Posistion(i,4)->iValue;
		pItem->level			= ItemFile.Search_Posistion(i,5)->iValue;
		pItem->grade			= ItemFile.Search_Posistion(i,6)->iValue;
		pItem->job				= ItemFile.Search_Posistion(i,7)->iValue;
		pItem->in_value			= ItemFile.Search_Posistion(i,8)->iValue;
		pItem->out_value		= ItemFile.Search_Posistion(i,9)->iValue;
		pItem->bind				= ItemFile.Search_Posistion(i,10)->iValue;
		pItem->combine			= ItemFile.Search_Posistion(i,11)->iValue;
		pItem->quality			= ItemFile.Search_Posistion(i,12)->iValue;
		pItem->url				= ItemFile.Search_Posistion(i,13)->pString;
		pItem->drop_url			= ItemFile.Search_Posistion(i,14)->pString;
		pItem->effect			= ItemFile.Search_Posistion(i,15)->pString;
		pItem->use_method		= ItemFile.Search_Posistion(i,16)->pString;
		pItem->downgrade		= ItemFile.Search_Posistion(i,19)->iValue;
		pItem->group_id			= ItemFile.Search_Posistion(i,20)->iValue;
		pItem->cd_group			= ItemFile.Search_Posistion(i,21)->iValue;
		pItem->overlay			= ItemFile.Search_Posistion(i,22)->iValue;
		pItem->can_sell			= ItemFile.Search_Posistion(i,23)->iValue;
		pItem->broadcast		= ItemFile.Search_Posistion(i,24)->iValue;
		pItem->valid_time		= ItemFile.Search_Posistion(i,25)->iValue;
		pItem->item_Grade		= ItemFile.Search_Posistion(i,26)->iValue;

		CfgItemTable::iterator it = m_items.find(pItem->id);
		if (it == m_items.end())
		{
			newItems.insert(CfgItemTable::value_type(pItem->id, pItem));
		}

		m_items[pItem->id] = pItem;
	}
	m_itemsLock.unlock();

	if (!newItems.empty() && bSend)
	{
		sendNewItems(newItems);
	}

	m_itemGiftsLock.wrlock();
	m_itemGifts.clear();
	//////////////////////////////////////////////////
	CDBCFile ItemGiftFile(0);
	bool retItemGift = ItemGiftFile.OpenFromTXT("./ServerConfig/Tables/cfg_item_gift.txt");
	if ( retItemGift == false )
	{
		LOG_ERROR("open cfg_item_gift.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_Gift		=	ItemGiftFile.GetRecordsNum();
	int32_t iBaseColumnCount_Gift		=	ItemGiftFile.GetFieldsNum();
	if (iBaseColumnCount_Gift <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_Gift;i++ )
	{
		CfgItemGift itemGift;
		itemGift.id						= ItemGiftFile.Search_Posistion(i,0)->iValue;
		itemGift.item					= ItemGiftFile.Search_Posistion(i,2)->iValue;
		itemGift.type					= ItemGiftFile.Search_Posistion(i,3)->iValue;
		itemGift.count					= ItemGiftFile.Search_Posistion(i,4)->iValue;
		itemGift.bind					= ItemGiftFile.Search_Posistion(i,5)->iValue;
		itemGift.job					= ItemGiftFile.Search_Posistion(i,6)->iValue;

		CfgItemGiftTable::iterator it	= m_itemGifts.find(itemGift.id);
		if (it == m_itemGifts.end())
		{
			m_itemGifts[itemGift.id] = new CfgItemGiftVector;
		}

		m_itemGifts[itemGift.id]->push_back(itemGift);
	}
	
	m_itemGiftsLock.unlock();
	m_itemGiftRandomsLock.wrlock();
	m_itemGiftRandoms.clear();
	/////////////////////////////////////////////////////////////
	CDBCFile ItemGiftRandFile(0);
	bool retItemGiftRand = ItemGiftRandFile.OpenFromTXT("./ServerConfig/Tables/cfg_item_gift_random.txt");
	if ( retItemGiftRand == false )
	{
		LOG_ERROR("open cfg_item_gift_random.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_GiftRand		=	ItemGiftRandFile.GetRecordsNum();
	int32_t iBaseColumnCount_GiftRand		=	ItemGiftRandFile.GetFieldsNum();
	if (iBaseColumnCount_GiftRand <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_GiftRand;i++ )
	{
		CfgItemGiftRandom itemGiftRandom;
		itemGiftRandom.id					= ItemGiftRandFile.Search_Posistion(i,0)->iValue;
		itemGiftRandom.item					= ItemGiftRandFile.Search_Posistion(i,1)->iValue;
		itemGiftRandom.type					= ItemGiftRandFile.Search_Posistion(i,2)->iValue;
		itemGiftRandom.count				= ItemGiftRandFile.Search_Posistion(i,3)->iValue;
		itemGiftRandom.bind					= ItemGiftRandFile.Search_Posistion(i,4)->iValue;
		itemGiftRandom.static_probability	= ItemGiftRandFile.Search_Posistion(i,5)->iValue;
		itemGiftRandom.sum_probability		= ItemGiftRandFile.Search_Posistion(i,6)->iValue;
		itemGiftRandom.job					= ItemGiftRandFile.Search_Posistion(i,7)->iValue;

		CfgItemGiftRandomTable::iterator it	= m_itemGiftRandoms.find(itemGiftRandom.id);
		if (it == m_itemGiftRandoms.end())
		{
			m_itemGiftRandoms[itemGiftRandom.id] = new CfgItemGiftRandomVector;
		}

		m_itemGiftRandoms[itemGiftRandom.id]->push_back(itemGiftRandom);
	}
	/////////////////////////////////////////////////////////////
	m_itemGiftRandomsLock.unlock();
}

void CfgData::fetchJob()
{
	CDBCFile JobFile(0);
	bool ret = JobFile.OpenFromTXT("./ServerConfig/Tables/cfg_job.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_job.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	JobFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	JobFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgJob job;
		job.id				= JobFile.Search_Posistion(i,0)->iValue;
		job.job_task		= JobFile.Search_Posistion(i,4)->iValue;
		job.attack_attr		= JobFile.Search_Posistion(i,5)->iValue;
		job.base_skill		= JobFile.Search_Posistion(i,6)->iValue;
		m_jobs[job.id]		= job;
	}
}

void CfgData::fetchMovie()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_movie.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_movie.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMovie movie;
		movie.id			= TabFile.Search_Posistion(i,0)->iValue;
		int32_t  MoveId		= TabFile.Search_Posistion(i,2)->iValue;
		if ( movie.id == MoveId )
		{
			m_movie[movie.id] = movie;
		}
	}
}



void CfgData::fetchLevelExp()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_level_exp.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_level_exp.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgLevelExp levelExp;

		levelExp.level				= TabFile.Search_Posistion(i,0)->iValue;
		levelExp.upgrade_exp		= _atoi64(TabFile.Search_Posistion(i,1)->pString);
		levelExp.max_exp			= _atoi64(TabFile.Search_Posistion(i,2)->pString);
		levelExp.pet_exp			= TabFile.Search_Posistion(i,3)->iValue;
		levelExp.mount_exp			= TabFile.Search_Posistion(i,4)->iValue;
		levelExp.vicegeneral_id		= TabFile.Search_Posistion(i,5)->iValue;
		m_levelExps[levelExp.level] = levelExp;
	}
}

void CfgData::fetchLevelAttr()
{
	CDBCFile LevelAttrFile(0);
	bool ret = LevelAttrFile.OpenFromTXT("./ServerConfig/Tables/cfg_level_attr.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_level_attr.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	LevelAttrFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	LevelAttrFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgLevelAttr levelAttr;
		levelAttr.level		= LevelAttrFile.Search_Posistion(i,0)->iValue;
		levelAttr.job		= LevelAttrFile.Search_Posistion(i,1)->iValue;
		levelAttr.addonattr	= parseEquipEffect(levelAttr.job,LevelAttrFile.Search_Posistion(i,2)->pString);

		m_levelAttrs[((levelAttr.job<<16)|levelAttr.level)] = levelAttr;
	}
}

void CfgData::fetchMap()
{
	CDBCFile MapFile(0);
	bool ret = MapFile.OpenFromTXT("./ServerConfig/Tables/cfg_map.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_map.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MapFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MapFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMap map;
		map.id					= MapFile.Search_Posistion(i,0)->iValue;
		map.name				= MapFile.Search_Posistion(i,1)->pString;
		map.type				= MapFile.Search_Posistion(i,2)->iValue;
		map.param				= MapFile.Search_Posistion(i,3)->iValue;
		map.width				= MapFile.Search_Posistion(i,4)->iValue;
		map.height				= MapFile.Search_Posistion(i,5)->iValue;
		map.revive				= MapFile.Search_Posistion(i,6)->iValue;
		map.pk_mode				= MapFile.Search_Posistion(i,7)->iValue;
		map.anti_protect		= MapFile.Search_Posistion(i,8)->iValue;
		map.isMount				= MapFile.Search_Posistion(i,9)->iValue;
		map.isFly				= MapFile.Search_Posistion(i,10)->iValue;
		map.isVicegeneral		= MapFile.Search_Posistion(i,11)->iValue;
		map.player_level		= MapFile.Search_Posistion(i,12)->iValue;
		map.player_level_max	= MapFile.Search_Posistion(i,13)->iValue;
		map.team_member			= MapFile.Search_Posistion(i,14)->iValue;
		map.hide_mini			= MapFile.Search_Posistion(i,15)->iValue;
		map.runnerId			= MapFile.Search_Posistion(i,23)->iValue;
		map.jump				= MapFile.Search_Posistion(i,30)->iValue;
		m_maps[map.id]			= map;
	}
}


void CfgData::fetchMapMonster()
{
	CDBCFile MapMonsterFile(0);
	bool ret = MapMonsterFile.OpenFromTXT("./ServerConfig/Tables/cfg_map_monster.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_map_monster.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MapMonsterFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MapMonsterFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMapMonster mapmonster;
		mapmonster.id			= MapMonsterFile.Search_Posistion(i,0)->iValue;
		mapmonster.mapid		= MapMonsterFile.Search_Posistion(i,1)->iValue;
		mapmonster.monsterid	= MapMonsterFile.Search_Posistion(i,2)->iValue;
		mapmonster.x			= MapMonsterFile.Search_Posistion(i,3)->iValue;
		mapmonster.y			= MapMonsterFile.Search_Posistion(i,4)->iValue;
		m_mapMonsters[mapmonster.mapid].push_back(mapmonster);
		m_CfgMapMonsters[mapmonster.id] = mapmonster;
	}
}

void CfgData::fetchMapPlant()
{
	CDBCFile MapPlantFile(0);
	bool ret = MapPlantFile.OpenFromTXT("./ServerConfig/Tables/cfg_map_plant.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_map_plant.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MapPlantFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MapPlantFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMapPlant mapPlant;
		mapPlant.mapid			= MapPlantFile.Search_Posistion(i,1)->iValue;
		mapPlant.plantid		= MapPlantFile.Search_Posistion(i,2)->iValue;
		mapPlant.x				= MapPlantFile.Search_Posistion(i,3)->iValue;
		mapPlant.y				= MapPlantFile.Search_Posistion(i,4)->iValue;
		m_mapPlants[mapPlant.mapid].push_back(mapPlant);
	}
}

void CfgData::fetchMapRegion()
{
	CDBCFile MapRegionFile(0);
	bool ret = MapRegionFile.OpenFromTXT("./ServerConfig/Tables/cfg_map_region.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_map_region.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MapRegionFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MapRegionFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMapRegion mapRegion;
		mapRegion.id			= MapRegionFile.Search_Posistion(i,0)->iValue;
		mapRegion.mapid			= MapRegionFile.Search_Posistion(i,2)->iValue;
		mapRegion.min_x			= MapRegionFile.Search_Posistion(i,3)->iValue;
		mapRegion.min_y			= MapRegionFile.Search_Posistion(i,4)->iValue;
		mapRegion.max_x			= MapRegionFile.Search_Posistion(i,5)->iValue;
		mapRegion.max_y			= MapRegionFile.Search_Posistion(i,6)->iValue;
		mapRegion.type			= MapRegionFile.Search_Posistion(i,7)->iValue;

		m_mapRegions[mapRegion.id] = mapRegion;
		m_mapRegionsByMapId[mapRegion.mapid].push_back(mapRegion);
	}
}

void CfgData::fetchMonster()
{
	CDBCFile MonsterFile(0);
	bool ret = MonsterFile.OpenFromTXT( FILE_MONSTER_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_MONSTER_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MonsterFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MonsterFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMonster monster = {};
		monster.mid					= MonsterFile.Search_Posistion(i,0)->iValue;
		monster.name				= MonsterFile.Search_Posistion(i,1)->pString;
		monster.level				= MonsterFile.Search_Posistion(i,2)->iValue;
		monster.quality				= MonsterFile.Search_Posistion(i,3)->iValue;

		// ����
		monster.hp					= MonsterFile.Search_Posistion(i,4)->iValue;
		monster.phy_atk_min			= MonsterFile.Search_Posistion(i,5)->iValue;
		monster.phy_atk_max			= MonsterFile.Search_Posistion(i,6)->iValue;
		monster.mag_atk_min			= MonsterFile.Search_Posistion(i,7)->iValue;
		monster.mag_atk_max			= MonsterFile.Search_Posistion(i,8)->iValue;
		monster.phy_def				= MonsterFile.Search_Posistion(i,9)->iValue;
		monster.mag_def				= MonsterFile.Search_Posistion(i,10)->iValue;
		monster.hitrate				= MonsterFile.Search_Posistion(i,11)->iValue;
		monster.dodge				= MonsterFile.Search_Posistion(i,12)->iValue;
		monster.critrate			= MonsterFile.Search_Posistion(i,13)->iValue;
		monster.dmg_add				= MonsterFile.Search_Posistion(i,14)->iValue;
		monster.dmg_rdc				= MonsterFile.Search_Posistion(i,15)->iValue;
		monster.dmg_add_pec			= MonsterFile.Search_Posistion(i,16)->iValue;
		monster.dmg_rdc_pec			= MonsterFile.Search_Posistion(i,17)->iValue;
		monster.movespeed			= MonsterFile.Search_Posistion(i,18)->iValue;
		monster.battle				= MonsterFile.Search_Posistion(i,19)->iValue;

		monster.exp					= MonsterFile.Search_Posistion(i,20)->iValue;
		monster.type				= MonsterFile.Search_Posistion(i,21)->iValue;
		monster.kingdom_contribute	= MonsterFile.Search_Posistion(i,22)->iValue;
		monster.revive_time			= MonsterFile.Search_Posistion(i,24)->iValue;
		monster.skill_id			= MonsterFile.Search_Posistion(i,25)->iValue;
		parseMonsterSkill( monster.mid, monster.unique_skill, MonsterFile.Search_Posistion(i,26)->pString );
		parseMonsterSkill( monster.mid, monster.random_skill, MonsterFile.Search_Posistion(i,27)->pString );
		monster.angry_time			= MonsterFile.Search_Posistion(i,28)->iValue;
		monster.standby				= MonsterFile.Search_Posistion(i,29)->iValue;
		monster.hpPercent			= MonsterFile.Search_Posistion(i,30)->iValue;
		monster.ai_style			= MonsterFile.Search_Posistion(i,31)->iValue;
		monster.ai_target			= MonsterFile.Search_Posistion(i,32)->iValue;
		monster.has_kingdom			= MonsterFile.Search_Posistion(i,33)->iValue;
		monster.view_range			= MonsterFile.Search_Posistion(i,34)->iValue;
		monster.move_range			= MonsterFile.Search_Posistion(i,35)->iValue;
		monster.broadcast			= MonsterFile.Search_Posistion(i,45)->iValue;
		monster.drop_free			= MonsterFile.Search_Posistion(i,46)->iValue;
		monster.group_id			= MonsterFile.Search_Posistion(i,50)->iValue;
		monster.boss_sign			= MonsterFile.Search_Posistion(i,51)->iValue;
		monster.BossSocre			= MonsterFile.Search_Posistion(i,57)->iValue;
		monster.TaskShare			= MonsterFile.Search_Posistion(i,58)->iValue;
		monster.corpse_time			= 3000;

		m_monsters[monster.mid]		= monster;
	}

	CDBCFile MonsterBroadcastFile(0);
	bool retBroadcast = MonsterBroadcastFile.OpenFromTXT("./ServerConfig/Tables/cfg_monster_broadcast.txt");
	if ( retBroadcast == false )
	{
		LOG_ERROR("open cfg_monster_broadcast.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCountBroadcast		=	MonsterBroadcastFile.GetRecordsNum();
	int32_t iBaseColumnCountBroadcast		=	MonsterBroadcastFile.GetFieldsNum();
	if (iBaseColumnCountBroadcast <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCountBroadcast;i++ )
	{
		m_monsterBroadcasts.push_back(MonsterBroadcastFile.Search_Posistion(i,1)->iValue);
	}
}

void CfgData::fetchMonsterDropGroup()
{
	CDBCFile MonsterDropFile(0);
	bool ret = MonsterDropFile.OpenFromTXT("./ServerConfig/Tables/cfg_monster_drop_group.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_monster_drop_group.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MonsterDropFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MonsterDropFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMonsterDropGroup monsterDropGroup = {};
		monsterDropGroup.group_id		= MonsterDropFile.Search_Posistion( i, 0 )->iValue;
		monsterDropGroup.item_id		= MonsterDropFile.Search_Posistion( i, 1 )->iValue;
		monsterDropGroup.item_class		= MonsterDropFile.Search_Posistion( i, 2 )->iValue;
		monsterDropGroup.bind_type		= MonsterDropFile.Search_Posistion( i, 3 )->iValue;
		monsterDropGroup.probability	= MonsterDropFile.Search_Posistion( i, 4 )->iValue;
		monsterDropGroup.cost_type		= MonsterDropFile.Search_Posistion( i, 5 )->iValue;
		monsterDropGroup.cost_value		= MonsterDropFile.Search_Posistion( i, 6 )->iValue;

		m_monsterDropGroups[monsterDropGroup.group_id].push_back( monsterDropGroup );
	}
}

void CfgData::fetchMonsterGroupDrop()
{
	CDBCFile MonsterGroupFile(0);
	bool ret = MonsterGroupFile.OpenFromTXT("./ServerConfig/Tables/cfg_monster_group_drop.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_monster_group_drop.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MonsterGroupFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MonsterGroupFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMonsterGroupDrop monsterGroupDrop;
		monsterGroupDrop.mid			= MonsterGroupFile.Search_Posistion(i,0)->iValue;
		monsterGroupDrop.group_id		= MonsterGroupFile.Search_Posistion(i,1)->iValue;
		monsterGroupDrop.probability	= MonsterGroupFile.Search_Posistion(i,2)->iValue;
		monsterGroupDrop.begin_time		= MonsterGroupFile.Search_Posistion(i,3)->iValue;
		monsterGroupDrop.end_time		= MonsterGroupFile.Search_Posistion(i,4)->iValue;
		monsterGroupDrop.repeat			= MonsterGroupFile.Search_Posistion(i,5)->iValue;
		monsterGroupDrop.job			= MonsterGroupFile.Search_Posistion(i,6)->iValue;
		if (monsterGroupDrop.begin_time < 0 || monsterGroupDrop.begin_time > 60*24-1 || 
			monsterGroupDrop.end_time < 0 || monsterGroupDrop.end_time > 60*24-1 || 
			monsterGroupDrop.begin_time > monsterGroupDrop.end_time || 
			monsterGroupDrop.repeat <= 0)
		{
			LOG_ERROR("wrong cfg_monster_group_drop data with mid = %d, group_id = %d\n", monsterGroupDrop.mid, monsterGroupDrop.group_id);
		}

		m_monsterGroupDrops[monsterGroupDrop.mid].push_back(monsterGroupDrop);
	}
}

void CfgData::fetchMonsterTaskDrop()
{
	CDBCFile MonsterTaskFile(0);
	bool ret = MonsterTaskFile.OpenFromTXT("./ServerConfig/Tables/cfg_monster_task_drop.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_monster_task_drop.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	MonsterTaskFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MonsterTaskFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgMonsterTaskDrop monsterTaskDrop	= {};
		monsterTaskDrop.mid					= MonsterTaskFile.Search_Posistion(i,0)->iValue;
		monsterTaskDrop.tid					= MonsterTaskFile.Search_Posistion(i,1)->iValue;
		monsterTaskDrop.item				= MonsterTaskFile.Search_Posistion(i,2)->iValue;
		monsterTaskDrop.probability			= MonsterTaskFile.Search_Posistion(i,3)->iValue;
		m_monsterTaskDrops[monsterTaskDrop.mid].push_back(monsterTaskDrop);
	}
}

void CfgData::fetchBornAttr()
{
	CDBCFile BornFile(0);
	bool ret = BornFile.OpenFromTXT("./ServerConfig/Tables/cfg_born_attr.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_born_attr.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	BornFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	BornFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgBornAttr bornAttr;
		bornAttr.job				= BornFile.Search_Posistion(i,0)->iValue;
		bornAttr.bornAttr			= parseEquipEffect(bornAttr.job,BornFile.Search_Posistion(i,1)->pString);

		m_bornAttr[bornAttr.job]	= bornAttr;
	}

	CDBCFile ChangeJobFile(0);
	bool retChangeJob = ChangeJobFile.OpenFromTXT("./ServerConfig/Tables/cfg_change_job_attr.txt");
	if ( retChangeJob == false )
	{
		LOG_ERROR("open cfg_change_job_attr.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount_ChangeJob		=	ChangeJobFile.GetRecordsNum();
	int32_t iBaseColumnCount_ChangeJob		=	ChangeJobFile.GetFieldsNum();
	if (iBaseColumnCount_ChangeJob <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount_ChangeJob;i++ )
	{
		CfgChangeJobAttr changeAttr;
		changeAttr.index				= ChangeJobFile.Search_Posistion(i,0)->iValue;
		changeAttr.changeAttr			= parseEquipEffect(changeAttr.index,ChangeJobFile.Search_Posistion(i,1)->pString);

		m_changeAttr[changeAttr.index]	= changeAttr;
	}
}

void CfgData::fetchFamily()
{
	CDBCFile FamilyFile(0);
	bool ret = FamilyFile.OpenFromTXT("./ServerConfig/Tables/cfg_family_level.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_family_level.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	FamilyFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	FamilyFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgFamilyLevel level = {};
		level.level					= FamilyFile.Search_Posistion(i,0)->iValue;
		level.rewards				= parseInt32VectorString(level.level,FamilyFile.Search_Posistion(i,4)->pString);

		m_familyLevel[level.level]	= level;
	}
}

void  CfgData::fetchGamble()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_gamble.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_gamble.txt");
		return;
	}
	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgGamble gamble = {};
		gamble.id			= TabFile.Search_Posistion(i,0)->iValue;
		int32_t	type		= TabFile.Search_Posistion(i,1)->iValue;
		gamble.item			= TabFile.Search_Posistion(i,2)->iValue;
		gamble.item_type	= TabFile.Search_Posistion(i,3)->iValue;
		gamble.count		= TabFile.Search_Posistion(i,4)->iValue;
		gamble.ratio		= TabFile.Search_Posistion(i,5)->iValue;
		gamble.isBroadcast	= TabFile.Search_Posistion(i,6)->iValue;
		if ( 1 == type )
		{
			m_gamble.push_back(gamble);
		}
		else if ( 2 == type )
		{
			m_gamble_second.push_back(gamble);
		}
		else if ( 3 == type )
		{
			m_gamble_three.push_back(gamble);
		}
	}

	CDBCFile TabFileEquip(0);
	ret = TabFileEquip.OpenFromTXT("./ServerConfig/Tables/cfg_gamble_equip.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_gamble_equip.txt");
		return;
	}
	iBaseTableCount			=	TabFileEquip.GetRecordsNum();
	iBaseColumnCount		=	TabFileEquip.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgGambleEquip equip = {};
		equip.id		= TabFileEquip.Search_Posistion(i,0)->iValue;
		equip.type		= TabFileEquip.Search_Posistion(i,1)->iValue;
		equip.equip		= parseGambleEquip(equip.id,TabFileEquip.Search_Posistion(i,2)->pString);
		m_gambleEquip[equip.id] = equip;
	}
};

void CfgData::fetchNpc()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_npc.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_npc.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgNpc npc;
		npc.id			= TabFile.Search_Posistion(i,0)->iValue;
		npc.level		= TabFile.Search_Posistion(i,4)->iValue;
		StringVector mapids = StringUtility::split(TabFile.Search_Posistion(i,6)->pString, "|");
		for (StringVector::iterator it = mapids.begin(); it != mapids.end(); ++it)
		{
			npc.mapids.push_back(atoi(it->c_str()));
		}
		npc.x			= TabFile.Search_Posistion(i,7)->iValue;
		npc.y			= TabFile.Search_Posistion(i,8)->iValue;
		npc.func		= TabFile.Search_Posistion(i,9)->iValue;
		npc.func_extra	= TabFile.Search_Posistion(i,10)->iValue;
		std::string param = TabFile.Search_Posistion(i,21)->pString;
		StringVector vparam = StringUtility::split( param, ":" );
		for ( uint32_t j = 0; j < vparam.size(); ++j )
		{
			npc.params.push_back( atoi( vparam[j].c_str() ) );
		}
		m_npcs[npc.id] = npc;
	}

	CDBCFile TabFileAir(0);
	ret = TabFileAir.OpenFromTXT("./ServerConfig/Tables/cfg_npc_airport.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_npc_airport.txt");
		return;
	}

	iBaseTableCount			=	TabFileAir.GetRecordsNum();
	iBaseColumnCount		=	TabFileAir.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgNpcAirport airport;
		airport.id					= TabFileAir.Search_Posistion(i,0)->iValue;
		airport.npcid				= TabFileAir.Search_Posistion(i,1)->iValue;
		airport.player_kingdom		= TabFileAir.Search_Posistion(i,3)->iValue;
		airport.kingdom_id			= TabFileAir.Search_Posistion(i,4)->iValue;
		airport.map_id				= TabFileAir.Search_Posistion(i,5)->iValue;
		airport.map_x				= TabFileAir.Search_Posistion(i,6)->iValue;
		airport.map_y				= TabFileAir.Search_Posistion(i,7)->iValue;
		airport.cost				= TabFileAir.Search_Posistion(i,8)->iValue;

		m_npcAirports[airport.id] = airport;
	}
}

void CfgData::fetchPlant()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_plant.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_plant.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgPlant plant={};
		plant.id		= TabFile.Search_Posistion(i,0)->iValue;
		plant.type		= TabFile.Search_Posistion(i,3)->iValue;
		plant.level		= TabFile.Search_Posistion(i,4)->iValue;
		StringVector strItems = StringUtility::split(TabFile.Search_Posistion(i,5)->pString, "|");
		for (StringVector::iterator it = strItems.begin(); it != strItems.end(); ++it)
		{
			StringVector EventVt = StringUtility::split(*it, ":");
			if (EventVt.size() == 2)
			{
				CfgPlantEvent Event;
				Event.EventId = atoi(EventVt[0].c_str());
				Event.Probability = atoi(EventVt[1].c_str());
				plant.EventMaxRate += Event.Probability;
				plant.Events.push_back(Event);
			}
		}
		plant.item_cost		= TabFile.Search_Posistion(i,6)->iValue;
		plant.start_hour	= TabFile.Search_Posistion(i,7)->iValue;
		plant.end_hour		= TabFile.Search_Posistion(i,8)->iValue;
		plant.gather_time	= TabFile.Search_Posistion(i,9)->iValue;
		plant.revive_time	= TabFile.Search_Posistion(i,10)->iValue;
		m_plants[plant.id] = plant;
	}
}

void CfgData::fetchSkill()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_skill_info.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_skill_result.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgSkill skill ={};
		int32_t nIndex = 0;
		skill.id				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		skill.job				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex; 
		skill.type				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.kind				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.distance			= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.range				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.area				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.self				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.target_num		= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		skill.beneficial		= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		skill.sp				= TabFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		nIndex = 25;
		skill.change_skill_id   = parseChangeJobEffect(skill.id,TabFile.Search_Posistion(i,nIndex)->pString);		++nIndex;
		m_skills[skill.id] = skill;
	}
	CDBCFile TabFileResult(0);
	ret = TabFileResult.OpenFromTXT("./ServerConfig/Tables/cfg_skill_result.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_skill_result.txt");
		return;
	}

	iBaseTableCount			=	TabFileResult.GetRecordsNum();
	iBaseColumnCount		=	TabFileResult.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t	SkillId		= TabFileResult.Search_Posistion(i,0)->iValue;

		m_skills[SkillId].study_level			= TabFileResult.Search_Posistion(i,4)->iValue;
		m_skills[SkillId].money_base			= TabFileResult.Search_Posistion(i,5)->iValue;
		m_skills[SkillId].money_ratio			= TabFileResult.Search_Posistion(i,6)->iValue;
		m_skills[SkillId].jungong_base			= TabFileResult.Search_Posistion(i,7)->iValue;
		m_skills[SkillId].jungong_ratio			= TabFileResult.Search_Posistion(i,8)->iValue;
		m_skills[SkillId].level_base			= TabFileResult.Search_Posistion(i,9)->iValue;
		m_skills[SkillId].maxLevel				= TabFileResult.Search_Posistion(i,10)->iValue;
		m_skills[SkillId].cd					= static_cast<int32_t>(TabFileResult.Search_Posistion(i,11)->iValue * 0.9f);
		m_skills[SkillId].mp_cost_base			= TabFileResult.Search_Posistion(i,12)->iValue;
		m_skills[SkillId].mp_cost_ratio			= TabFileResult.Search_Posistion(i,13)->iValue;
		m_skills[SkillId].angry_cost			= TabFileResult.Search_Posistion(i,14)->iValue;
		m_skills[SkillId].special				= TabFileResult.Search_Posistion(i,15)->iValue;
		m_skills[SkillId].attack_type			= TabFileResult.Search_Posistion(i,16)->iValue;
		m_skills[SkillId].attack_modify_base	= TabFileResult.Search_Posistion(i,17)->iValue;
		m_skills[SkillId].attack_modify_ratio	= TabFileResult.Search_Posistion(i,18)->iValue;
		m_skills[SkillId].attack_addon_base		= TabFileResult.Search_Posistion(i,19)->iValue;
		m_skills[SkillId].attack_addon_ratio	= TabFileResult.Search_Posistion(i,20)->iValue;
		m_skills[SkillId].buff_rate_base		= TabFileResult.Search_Posistion(i,21)->iValue;
		m_skills[SkillId].buff_rate_ratio		= TabFileResult.Search_Posistion(i,22)->iValue;
		m_skills[SkillId].buff					= TabFileResult.Search_Posistion(i,23)->iValue;
	}
}

void CfgData::fetchTask()
{

	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_task.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_task.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgTask task;
		task.id					= TabFile.Search_Posistion(i,0)->iValue;
		snprintf(task.name, MAX_NAME_CCH_LENGTH, TabFile.Search_Posistion(i,1)->pString);
		task.type				= TabFile.Search_Posistion(i,2)->iValue;
		task.group				= TabFile.Search_Posistion(i,3)->iValue;
		task.can_giveup			= TabFile.Search_Posistion(i,4)->iValue;
		task.pretask			= TabFile.Search_Posistion(i,5)->iValue;
		task.posttask			= TabFile.Search_Posistion(i,6)->iValue;
		task.main_order			= TabFile.Search_Posistion(i,7)->iValue;
		task.job				= TabFile.Search_Posistion(i,8)->iValue;
		task.level				= TabFile.Search_Posistion(i,9)->iValue;
		task.max_level			= TabFile.Search_Posistion(i,10)->iValue;
		task.kingdom			= TabFile.Search_Posistion(i,11)->iValue;
		task.start_npc			= TabFile.Search_Posistion(i,12)->iValue;
		task.end_npc			= TabFile.Search_Posistion(i,13)->iValue;
		task.dungeon			= TabFile.Search_Posistion(i,14)->iValue;
		task.items_receive		= parseTaskItemString(task.id, TabFile.Search_Posistion(i,15)->pString);
		task.award_exp			= TabFile.Search_Posistion(i,16)->iValue;
		task.award_money		= TabFile.Search_Posistion(i,17)->iValue;
		task.gold				= TabFile.Search_Posistion(i,18)->iValue;
		task.dilong				= TabFile.Search_Posistion(i,19)->iValue;
		task.rongyu				= TabFile.Search_Posistion(i,20)->iValue;
		task.fuwen				= TabFile.Search_Posistion(i,21)->iValue;
		task.shuguang			= TabFile.Search_Posistion(i,22)->iValue;
		task.award_item			= parseTaskItemString(task.id, TabFile.Search_Posistion(i,23)->pString);
		task.award_optional		= parseTaskItemJobString(task.id,TabFile.Search_Posistion(i,24)->pString);
		task.condition			= TabFile.Search_Posistion(i,35)->iValue;
	//	task.done_count			= TabFile.Search_Posistion(i,1)->iValue;
		task.request = parseTaskCondition(task.id, task.condition, TabFile.Search_Posistion(i,36)->pString);
		task.GongXian			= TabFile.Search_Posistion(i,50)->iValue;
		task.JunTuanZiJin		= TabFile.Search_Posistion(i,51)->iValue;
		m_tasks[task.id] = task;

		if ( task.type == TT_CYCLE )
		{
			m_cfgTaskCycleTable.AddTask( task.id, task.level, task.max_level );
		}
		if ( task.type == TT_FAMILY )
		{
			m_FamilyTaskTable.AddFamilyTask( task.id, task.level, task.max_level );
		}

	}
}

void CfgData::fetchTrailer()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_trailer.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_trailer.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		m_tailers.id		= TabFile.Search_Posistion(i,0)->iValue;
		m_tailers.name		= TabFile.Search_Posistion(i,1)->pString;
		m_tailers.level		= TabFile.Search_Posistion(i,2)->iValue;
		m_tailers.pdef		= TabFile.Search_Posistion(i,3)->iValue;
		m_tailers.mdef		= TabFile.Search_Posistion(i,4)->iValue;
		m_tailers.maxhp		= TabFile.Search_Posistion(i,5)->iValue;
		m_tailers.sp		= TabFile.Search_Posistion(i,6)->iValue;
		m_tailers.time		= TabFile.Search_Posistion(i,7)->iValue;
	}
}

void CfgData::fetchTrap()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_trap.txt");
	if ( ret == false )
	{
		LOG_ERROR("�����ñ����� cfg_trap.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgTrap trap;
		trap.id				= TabFile.Search_Posistion(i,0)->iValue;
		trap.cd				= TabFile.Search_Posistion(i,2)->iValue;
		trap.delay			= TabFile.Search_Posistion(i,3)->iValue;
		trap.event_type		= TabFile.Search_Posistion(i,4)->iValue;
		trap.effect			= TabFile.Search_Posistion(i,6)->pString;
		trap.item_cost		= TabFile.Search_Posistion(i,7)->iValue;

		m_traps[trap.id] = trap;
	}
}

FamilyRegionVector CfgData::parseFamilyRegionEffect(int32_t id, const std::string &str)
{
	FamilyRegionVector regionVector;

	if (!str.empty())
	{
		StringVector strAttrAddons = StringUtility::split(str, "|");
		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
		{
			StringVector strAttrAddon = StringUtility::split(*it, ":");
			if (strAttrAddon.size() == 3)
			{
				FamilyRegion regionAddon = {};
				regionAddon.family_index  = atoi(strAttrAddon[0].c_str());
				regionAddon.x = atoi(strAttrAddon[1].c_str());
				regionAddon.y = atoi(strAttrAddon[2].c_str());

				if (regionAddon.family_index > 0 && regionAddon.x > 0 && regionAddon.y >0)
				{
					regionVector.push_back(regionAddon);
				}
			}
			else
			{
				LOG_ERROR("CfgData::parseFamilyRegionEffect wrong data with id = %d, str = %s\n", id, str.c_str());
			}
		}
	}

	return regionVector;
}

ChangeJobIndexVector CfgData::parseChangeJobEffect(int32_t id, const std::string &str)
{
	ChangeJobIndexVector equipVector;

	if (!str.empty() && str!="0")
	{
		StringVector strAttrAddons = StringUtility::split(str, "|");
		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
		{
			StringVector strAttrAddon = StringUtility::split(*it, ":");
			if (strAttrAddon.size() == 2)
			{
				ChangeJobIndex attrAddon = {};
				attrAddon.job = atoi(strAttrAddon[0].c_str());
				attrAddon.replace_id = atoi(strAttrAddon[1].c_str());
				if (attrAddon.job > 0 && attrAddon.replace_id > 0)
				{
					equipVector.push_back(attrAddon);
				}
			}
			else
			{
				LOG_ERROR("CfgData::parseChangeJobEquipEffect wrong data with id = %d, str = %s\n", id, str.c_str());
			}
		}
	}

	return equipVector;
}

AttrAddonVector CfgData::parseEquipEffect(int32_t id, const std::string &str)
{
	AttrAddonVector attrAddons;

	if (!str.empty() && str!="0")
	{
		StringVector strAttrAddons = StringUtility::split(str, "|");
		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
		{
			StringVector strAttrAddon = StringUtility::split(*it, ":");
			if (strAttrAddon.size() == 2)
			{
				AttrAddon attrAddon = {};
				attrAddon.index = atoi(strAttrAddon[0].c_str());
				attrAddon.addon = atoi(strAttrAddon[1].c_str());
				if (attrAddon.index > 0 && attrAddon.addon > 0)
				{
					attrAddons.push_back(attrAddon);
				}
			}
			else
			{
				LOG_ERROR("CfgData::parseEquipEffect wrong data with id = %d, str = %s\n", id, str.c_str());
			}
		}
	}

	return attrAddons;
}

Int32Vector CfgData::parseInt32VectorString(int32_t id,const std::string &str)
{
	Int32Vector  values;

	if (!str.empty())
	{
		StringVector strMines = StringUtility::split(str, ":");
		if (strMines.size() > 0)
		{
			for (StringVector::iterator it = strMines.begin();it != strMines.end();++it)
			{
				values.push_back(atoi((*it).c_str()));
			}
		}
		else
		{
			LOG_ERROR("CfgData::parseInt32VectorString wrong data with id = %d, str = %s\n", id, str.c_str());
		}
	}

	return values;
}

Int32Vector CfgData::parseShejituEffect(int32_t id,const std::string &str)
{
	Int32Vector  mines;

	if (!str.empty())
	{
		StringVector strMines = StringUtility::split(str, "|");
		for (StringVector::iterator it = strMines.begin();it != strMines.end();++it)
		{
			mines.push_back(atoi((*it).c_str()));
		}
	}

	return mines;
}

AttrAddonVector CfgData::parseEffect(int32_t id, const std::string &str)
{
	AttrAddonVector attrAddons;

	if (!str.empty())
	{
		StringVector strAttrAddons = StringUtility::split(str, "|");
		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
		{
			StringVector strAttrAddon = StringUtility::split(*it, ":");
			if (strAttrAddon.size() == 2)
			{
				AttrAddon attrAddon = {};
				attrAddon.index = atoi(strAttrAddon[0].c_str());
				attrAddon.addon = atoi(strAttrAddon[1].c_str());
				if (attrAddon.index > 0 && attrAddon.addon > 0)
				{
					attrAddons.push_back(attrAddon);
				}
			}
			else
			{
				LOG_ERROR("CfgData::parseEffect wrong data with id = %d, str = %s\n", id, str.c_str());
			}
		}
	}

	return attrAddons;
}

AttrAddonVector CfgData::parseItemEffect(int32_t id, const std::string &str)//������Ʒ����Ч��
{
	AttrAddonVector attrAddons;

	if (!str.empty())
	{
		StringVector strAttrAddons = StringUtility::split(str, "|");
		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
		{
			StringVector strAttrAddon = StringUtility::split(*it, ":");
			if (strAttrAddon.size() == 2)
			{
				AttrAddon attrAddon = {};
				attrAddon.index = atoi(strAttrAddon[0].c_str());
				attrAddon.addon = atoi(strAttrAddon[1].c_str());
				if (attrAddon.index > 0 && attrAddon.addon > 0)
				{
					attrAddons.push_back(attrAddon);
				}
			}
			else
			{
				LOG_ERROR("CfgData::parseItemEffect wrong data with id = %d, str = %s\n", id, str.c_str());
			}
		}
	}
	return attrAddons;
}

MemChrBagVector CfgData::parseAllItemString(int32_t id, const std::string &strItems)
{
	MemChrBagVector items;

	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 2)
			{
				MemChrBag itemData = {};
				itemData.itemId = atoi(item[0].c_str());
				itemData.itemCount = atoi(item[1].c_str());
				itemData.itemClass = IC_NORMAL;
				items.push_back(itemData);
			}
			else
			{
				LOG_ERROR("CfgData::parseAllItemString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}

std::vector<Position> CfgData::paresPosition( const std::string &strPos )
{
	std::vector<Position> PosVector;
	if ( !strPos.empty() )
	{
		StringVector PosString = StringUtility::split(strPos, "|");
		for (StringVector::iterator it = PosString.begin(); it != PosString.end(); ++it)
		{
			StringVector Pos = StringUtility::split(*it, ":");
			if (Pos.size() == 2)
			{
				Position stu;
				stu.x					= atoi(Pos[0].c_str());
				stu.y					= atoi(Pos[1].c_str());
				PosVector.push_back(stu);
			}
		}
	}
	return PosVector;
}

MemChrBagVector CfgData::parseItemString(int32_t id, const std::string &strItems)
{
	MemChrBagVector items;

	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 3)
			{
				MemChrBag itemData = {};
				itemData.itemId			= atoi(item[0].c_str());
				itemData.itemClass		= atoi(item[1].c_str());
				itemData.itemCount		= atoi(item[2].c_str());
				items.push_back(itemData);
			}
			else if ( item.size() == 4 )
			{
				MemChrBag itemData = {};
				itemData.itemId			= atoi(item[0].c_str());
				itemData.itemClass		= atoi(item[1].c_str());
				itemData.itemCount		= atoi(item[2].c_str());
				itemData.bind			= atoi(item[3].c_str());
				items.push_back(itemData);
			}
			else if ( item.size() == 5 )
			{
				MemChrBag itemData = {};
				itemData.itemId			= atoi(item[0].c_str());
				itemData.itemClass		= atoi(item[1].c_str());
				itemData.itemCount		= atoi(item[2].c_str());
				itemData.bind			= atoi(item[3].c_str());
				itemData.endTime		= atoi(item[4].c_str());
				items.push_back(itemData);
			}
			else
			{
				LOG_ERROR("CfgData::parseItemString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}


void CfgData::parseItemStringWithJob(int32_t id,const std::string &strItems,MemChrBagVector &items,MemChrJobBagVector&jobItems)
{
	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 3)
			{
				MemChrBag itemData = {};
				itemData.itemId = atoi(item[0].c_str());
				itemData.itemClass = atoi(item[1].c_str());
				itemData.itemCount = atoi(item[2].c_str());
				items.push_back(itemData);
			}
			else if (item.size() == 4)
			{
				MemChrJobBag  job = {};
				job.id = atoi(item[0].c_str());
				job.type = atoi(item[1].c_str());
				job.count = atoi(item[2].c_str());
				job.job = atoi(item[3].c_str());
				jobItems.push_back(job);
			}
			else
			{
				LOG_ERROR("CfgData::parseTaskItemString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}
	
}

MemChrBagVector CfgData::parseTaskItemString(int32_t id, const std::string &strItems)
{
	MemChrBagVector items;

	if (!strItems.empty() && strItems.size() > 3)
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 3)
			{
				MemChrBag itemData = {};
				itemData.itemId = atoi(item[0].c_str());
				itemData.itemClass = atoi(item[1].c_str());
				itemData.itemCount = atoi(item[2].c_str());
				items.push_back(itemData);
			}
			if ( item.size() == 4 )
			{
				MemChrBag itemData = {};
				itemData.itemId		= atoi(item[0].c_str());
				itemData.itemClass  = atoi(item[1].c_str());
				itemData.itemCount  = atoi(item[2].c_str());
				itemData.bind		= atoi(item[3].c_str());
				items.push_back(itemData);
			}
			else
			{
				LOG_ERROR("CfgData::parseTaskItemString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}

GongGaoList CfgData::parseGongGaoString(int32_t id, const std::string &strItems)
{
	GongGaoList GongGao;
	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if ( item.size() == 2 )
			{
				CfgGongGao stu = {};
				stu.Job			= atoi(item[0].c_str());
				stu.GongGaoId	= atoi(item[1].c_str());
				GongGao.push_back( stu );
			}
		}
	}

	return GongGao;
}

MemChrEquipBagVector CfgData::parseEquipItemString(int32_t id, const std::string &strItems)
{
	MemChrEquipBagVector items;

	if (!strItems.empty() && strItems.size() > 4)
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if ( item.size() == 5 )
			{
				CfgEquipItem itemData = {};
				itemData.id		= atoi(item[0].c_str());
				itemData.type	= atoi(item[1].c_str());
				itemData.count	= atoi(item[2].c_str());
				itemData.bind	= atoi(item[3].c_str());
				itemData.job	= atoi(item[4].c_str());
				items.push_back( itemData );
			}
			else if ( item.size() == 6 )
			{
				CfgEquipItem itemData = {};
				itemData.id		= atoi(item[0].c_str());
				itemData.type	= atoi(item[1].c_str());
				itemData.count	= atoi(item[2].c_str());
				itemData.bind	= atoi(item[3].c_str());
				itemData.job	= atoi(item[4].c_str());
				itemData.star	= atoi(item[5].c_str());
				items.push_back( itemData );
			}
			else
			{
				LOG_ERROR("CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}

MemChrJobBagVector CfgData::parseTaskItemJobString(int32_t id, const std::string &strItems)
{
	MemChrJobBagVector items;

	if (!strItems.empty() && strItems.size() > 4)
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 4)
			{
				MemChrJobBag itemData = {};
				itemData.id = atoi(item[0].c_str());
				itemData.type = atoi(item[1].c_str());
				itemData.count = atoi(item[2].c_str());
				itemData.job = atoi(item[3].c_str());
			
				items.push_back(itemData);
			}
			else if ( item.size() == 5 )
			{
				MemChrJobBag itemData = {};
				itemData.id = atoi(item[0].c_str());
				itemData.type = atoi(item[1].c_str());
				itemData.count = atoi(item[2].c_str());
				itemData.bind = atoi(item[3].c_str());
				itemData.job = atoi(item[4].c_str());
				items.push_back( itemData );
			}
			else
			{
				LOG_ERROR("CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}

void CfgData::parseMonsterSkill(int32_t id, MonsterSkill (&vSkill)[MAX_MONSTER_SKILL], const std::string &strSkill)
{
	if ( !strSkill.empty() && strSkill.size() > 3 )
	{
		StringVector skills = StringUtility::split(strSkill, "|");
		int32_t isize = skills.size() < MAX_MONSTER_SKILL ? skills.size() : MAX_MONSTER_SKILL;
		for ( int32_t i = 0; i < isize; ++i  )
		{
			StringVector skill = StringUtility::split(skills[i], ":");
			if (skill.size() == 3)
			{
				MonsterSkill monsterSkill = {};
				monsterSkill.maxHp		= atoi(skill[0].c_str());
				monsterSkill.minHp		= atoi(skill[1].c_str());
				monsterSkill.skillid	= atoi(skill[2].c_str());
				monsterSkill.done		= false;
				vSkill[i] = monsterSkill;
			}
			else
			{
				LOG_ERROR("CfgData::parseMonsterSkill wrong data with id = %d, string = %s\n", id, strSkill.c_str());
			}
		}
	}
}

AcExchangeItemVector CfgData::paresAcExchangeString(int32_t id,const std::string &str)
{
	  AcExchangeItemVector item;
	  if (!str.empty()&& str!="0")
	  {
		  StringVector FirstValue = StringUtility::split(str, "|");
		  for (StringVector::iterator it = FirstValue.begin();it != FirstValue.end();++it)
		  {
			  StringVector secondValue = StringUtility::split(*it, ":");
			  if (secondValue.size() == 3)
			  {
				  AcExchangeItem exchange = {};
				  exchange.id = atoi(secondValue[0].c_str());
				  exchange.count = atoi(secondValue[1].c_str());
				  exchange.job = atoi(secondValue[2].c_str());

				  item.push_back(exchange);
			  }
			  else
			  {
				   LOG_ERROR("CfgData::paresAcExchangeString wrong data with id = %d, string = %s\n", id, str.c_str());
			  }
		  }
	  }
	  return item;
}

Int32Vector CfgData::parseAchievementString(int32_t id,const std::string &str)
{
	Int32Vector acVector;
	if (!str.empty()&& str!="0")
	{
		StringVector items = StringUtility::split(str, "|");
		for (StringVector::iterator it = items.begin(); it != items.end(); ++it)
		{
			acVector.push_back(atoi((*it).c_str()));
		}
	}
	return acVector;
}

MemJobItemTable CfgData::parseGambleEquip(int32_t id,const std::string &strItems)
{
	MemJobItemTable items;
	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 2)
			{
				MemJobItem itemData = {};
				itemData.job = atoi(item[0].c_str());
				itemData.item = atoi(item[1].c_str());

				items[itemData.job] = itemData;
			}
			else
			{
				LOG_ERROR("CfgData::parseGambleEquip wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}

AchievementRequest CfgData::parseAchievementCondition(int32_t id, int32_t condition, const std::string &strRequest)
{
	AchievementRequest request = {};
	StringVector requests = StringUtility::split(strRequest, ":");
	switch (condition)
	{
	case AT_TEAM:				
	case AT_FRIEND:				
	case AT_FAMILY:				
	case AT_EQUIP_UP_STAR:		
	case AT_PET_ILLUSION:		
	case AT_LOGIN:				
	case AT_LEVEL:				
	case AT_THREE_PET:
	case AT_PET_KNIGHT:
	case AT_KILL_BOSS:	
	case AT_KILL_MONSSTER:
	case AT_GUAN_WEI:
	case AT_INSID_PET_POINTS:	
	case AT_WU_LING_POINTS:	
	case AT_HUAN_LING_POINTS:	
	case AT_LUCK_POINTS:		
	case AT_QI_FU_EXP:	 
	case AT_QI_FU_MONEY:	
	case AT_CHOU_JIANG:	
	case AT_JUE_WEI:		
	case AT_HALL_FAME:	
		{
			if ( requests.size() == 1 )
			{
				request.param1= atoi( requests[0].c_str() );
			}
		}
		break;
	case AT_PET_POINTS_COUNT:
	case AT_DRESS_EQUIP:			 
	case AT_KILL_MONSTER_BY_MID:
	case AT_DUNGEON:
	case AT_FA_BAO:
	case AT_ACTIVITY:
		{
			if ( requests.size() == 2 )
			{
				request.param1	= atoi( requests[0].c_str() );
				request.param2	= atoi( requests[1].c_str() );
			}
		}
		break;
	default:
		//LOG_ERROR("CfgData::parseTaskCondition wrong data with id = %d, string = %s\n", id, strRequest.c_str());
		break;
	}

	return request;
}

TaskRequest CfgData::parseTaskCondition(int32_t id, int32_t condition, const std::string &strRequest)
{
	TaskRequest request = {};

	StringVector requests = StringUtility::split(strRequest, ":");

	switch (condition)
	{
	//3��������
	case TC_ITEM:		//��Ҫ��Ʒ
		if (requests.size() == 3)
		{
			request.param1 = atoi(requests[0].c_str()); //item id
			request.param2 = atoi(requests[1].c_str()); //item type
			request.param3 = atoi(requests[2].c_str()); //item count;
		}
		else
		{
			LOG_ERROR("CfgData::parseTaskCondition wrong data with id = %d, string = %s\n", id, strRequest.c_str());
		}
		break;
	//2��������
	case TC_MONSTER_ID:		//ָ������
	case TC_MONSTER_LEVEL:  //ָ���ȼ�����
	case TC_PLANT:			//�ɼ�
	case TC_USER_SKILL:     //ʹ�ü���
	case TC_FINISH_TASK_TYPE://���ָ�����͵�����
	case TC_USE_ITEM:
	case TC_DRESS_EQUIP:
	case TC_EQUIP_STAR_COUNT:
	case TC_PET_POINTS_COUNT:
		if (requests.size() == 2)
		{
			request.param1 = atoi(requests[0].c_str());
			request.param2 = atoi(requests[1].c_str()); 
		}
		else
		{
			LOG_ERROR("CfgData::parseTaskCondition wrong data with id = %d, string = %s\n", id, strRequest.c_str());
		}
		break;
	//1��������
	case TC_PLAYER_LEVEL:		//�ﵽ�ȼ�
	case TC_PET_ILLUSION:		//����û�
	case TC_UP_EQUIP_STAR:		//װ��ǿ��
	case TC_UP_EQUIP_GRADE:		//װ������
	case TC_UP_EQUIP_QUALITY:	//װ����Ʒ
	case TC_HALL_OF_FAME:
	case TC_DUNGEON:
	case TC_KILL_BOSS_COUNT:
		{
			if (requests.size() == 1)
			{
				request.param1= atoi(requests[0].c_str());
			}
			else
			{
				LOG_ERROR("CfgData::parseTaskCondition wrong data with id = %d, string = %s\n", id, strRequest.c_str());
			}
			break;
		}
	default:
		//LOG_ERROR("CfgData::parseTaskCondition wrong data with id = %d, string = %s\n", id, strRequest.c_str());
		break;
	}

	return request;
}

const int32_t CfgData::getServerStartTime()
{
	return m_startServerTime;
}

const int32_t CfgData::getServerStartDayTime()
{
	return DayTime::dayzero(m_startServerTime);
}

const int32_t CfgData::getServerDiffTime()
{
	return DayTime::daydiff(m_startServerTime);
}

int32_t CfgData::getServerType() const
{
	// Default: main server
	return 0;
}

bool CfgData::isUniteServer() const
{
	// Default: not a united server
	return false;
}

int32_t CfgData::getServerDiffDay( int32_t serverType ) const
{
	// Returns days since server start
	return DayTime::daydiff(m_startServerTime);
}

//void CfgData::fetchKingdom()
//{
//	CDBCFile KingdomFile(0);
//	bool ret = KingdomFile.OpenFromTXT("./ServerConfig/Tables/cfg_kingdom.txt");
//	if ( ret == false )
//	{
//		LOG_ERROR("open cfg_kingdom.txt failed,please check!!");
//		return;
//	}
//
//	int32_t iBaseTableCount		=	KingdomFile.GetRecordsNum();
//	int32_t iBaseColumnCount	=	KingdomFile.GetFieldsNum();
//	if (iBaseColumnCount <=0)
//	{
//		return ;
//	}
//
//	for( int32_t i = 0;i < iBaseTableCount;i++ )
//	{
//		CfgKingdom kingdom;
//		kingdom.id				= KingdomFile.Search_Posistion(i,0)->iValue;
//		kingdom.name			= KingdomFile.Search_Posistion(i,1)->pString;
//		kingdom.task_id			= KingdomFile.Search_Posistion(i,2)->iValue;
//		kingdom.random_gift		= KingdomFile.Search_Posistion(i,3)->iValue;
//		m_kingdoms[kingdom.id]	= kingdom;
//	}
//}

void CfgData::fetchServerConfig()
{
	MySqlDBGuard db(DBPOOL);

	MySqlQuery result = db.query("SELECT `value` FROM `sys_server_config` WHERE `name`='create_time'");
	if (!result.eof())
	{
		m_createTime = atoi(result.getStringValue(0));
	}
	result = db.query("SELECT `value` FROM `sys_server_config` WHERE `name`='startGame_time'");
	if (!result.eof())
	{
		m_startServerTime = atoi(result.getStringValue(0));
	}
	else
	{
		m_startServerTime = TIMER.GetNow();
		char mySql[1024]={0};
		snprintf(mySql,1023,"INSERT INTO `sys_server_config` (`name`,`value`) VALUES('%s','%d')","startGame_time",m_startServerTime);
		db.excute(mySql);
	}
}

void CfgData::sendNewItems(const CfgItemTable &items)
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_NEW_ITEM);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(static_cast<int32_t>(items.size()));
	for (CfgItemTable::const_iterator it = items.begin(); it != items.end(); ++it)
	{
		CfgItem	*pCfgItem = it->second;
		if (pCfgItem != NULL)
		{
			packet->writeInt32(pCfgItem->id);
			packet->writeUTF8(pCfgItem->name);
			packet->writeUTF8(pCfgItem->desc);
			packet->writeInt32(pCfgItem->type);
			packet->writeInt32(pCfgItem->level);
			packet->writeInt32(pCfgItem->job);
			packet->writeInt32(pCfgItem->in_value);
			packet->writeInt32(pCfgItem->out_value);
			packet->writeInt32(pCfgItem->bind);
			packet->writeInt32(pCfgItem->combine);
			packet->writeInt32(pCfgItem->quality);
			packet->writeUTF8(pCfgItem->url);
			packet->writeUTF8(pCfgItem->drop_url);
			packet->writeUTF8(pCfgItem->effect);
			packet->writeUTF8(pCfgItem->use_method);
			packet->writeInt32(pCfgItem->group_id);
			packet->writeInt32(pCfgItem->cd_group);
			packet->writeInt32(pCfgItem->overlay);
			packet->writeInt32(pCfgItem->can_sell);
			packet->writeInt32(pCfgItem->valid_time);
		}
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.broadcast(packet);
}

bool CfgData::isBanChat(int32_t uid, int32_t nowTime)
{
	MutexGuard lock(m_banChatsLock);
	GmtBanChatTable::iterator it = m_banChats.find(uid);
	if (it != m_banChats.end())
	{
		return it->second.expire_time == 0 || nowTime < it->second.expire_time;
	}

	return false;
}

void CfgData::onBanChatUpdated(int32_t action, int32_t uid, int32_t expire_time)
{
	MutexGuard lock(m_banChatsLock);
	if (action)
	{
		GmtBanChat banChat = {};
		banChat.uid = uid;
		banChat.expire_time = expire_time;
		m_banChats[uid] = banChat;
	}
	else
	{
		m_banChats.erase(uid);
	}
}

void CfgData::fetchGmtBanChat()
{
	MySqlDBGuard db(DBPOOL);

	MySqlQuery result = db.query("SELECT * FROM `gmt_ban_chat`");
	while (!result.eof())
	{
		GmtBanChat banChat = {};
		banChat.uid = result.getIntValue("uid");
		banChat.expire_time = result.getIntValue("expire_time");

		m_banChats[banChat.uid] = banChat;

		result.nextRow();
	}
}

void CfgData::getExParams(cfgParams& params,const std::string& str)
{
	params.clear();
	StringVector FirstValue = StringUtility::split(str, "|");
	for (StringVector::iterator it = FirstValue.begin();it != FirstValue.end();++it)
	{
		StringVector secondValue = StringUtility::split(*it, ":");
		if (secondValue.size() == 2)
		{
			cfgParam item={};
			item.param1 =atoi(secondValue[0].c_str());
			item.param2 =atoi(secondValue[1].c_str());
			params.push_back(item);
		}
	}
}

void CfgData::fetchcfExActivity()
{
	CDBCFile ChrActivityFile(0);
	bool ret = ChrActivityFile.OpenFromTXT("./ServerConfig/Tables/cfg_chr_activity.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_chr_activity.txt failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	ChrActivityFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	ChrActivityFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		cfgExActivity activity;
		activity.actid				= static_cast<int16_t>(ChrActivityFile.Search_Posistion(i,1)->iValue);
		std::string gifts			= ChrActivityFile.Search_Posistion(i,2)->pString;
		activity.starttime			= ChrActivityFile.Search_Posistion(i,3)->iValue;
		activity.endtime			= ChrActivityFile.Search_Posistion(i,4)->iValue;

		snprintf(activity.strgifts,199,"%s",gifts.c_str());
		getExParams(activity.gifts,activity.strgifts);
		m_cfgExActivitys[activity.actid] = activity;
	}
}

void CfgData::InitEquipTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquip equip = {};
		int32_t nIndex = 0;
		equip.m_nId			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		++nIndex;
		equip.m_nType		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		equip.m_nLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		equip.m_nSoulLevel	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		equip.m_nJob		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		equip.m_nPrice		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		equip.m_nQuality	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		equip.m_nSuitId		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		for ( int32_t j = 0; j < MAX_EQUIP_BASE_ATTR_COUNT; ++j )
		{
			equip.m_vAttr[j].index	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			equip.m_vAttr[j].addon	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}
		for ( int32_t k = 0; k < MAX_EQUIP_BASE_ATTR_COUNT; ++k )
		{
			equip.m_StarAttr[k].index = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			equip.m_StarAttr[k].addon = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}
		equip.m_Battle			= readFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		equip.m_nGrade			= readFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		equip.m_nRansomWorth	= readFile.Search_Posistion( i, nIndex )->iValue;		nIndex += 11;
		equip.m_nWuHunExp		= readFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;
		equip.m_nBroadcast		= readFile.Search_Posistion( i, nIndex )->iValue;		++nIndex;

		m_cfgEquip.AddEquip( equip );
	}
}

void CfgData::InitEquipUpGradeTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_UP_GRADE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_UP_GRADE_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	ItemData costItem = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquipUpGrade equip;
		equip.m_nId							= readFile.Search_Posistion( i, 0 )->iValue;
		equip.m_nGiveId						= readFile.Search_Posistion( i, 1 )->iValue;
		equip.m_nFailLine					= readFile.Search_Posistion( i, 2 )->iValue;
		equip.m_nSuccessLine				= readFile.Search_Posistion( i, 3 )->iValue;
		equip.m_nFullLucky					= readFile.Search_Posistion( i, 4 )->iValue;
		equip.m_nGetLucky					= readFile.Search_Posistion( i, 5 )->iValue;
		equip.m_nRate						= readFile.Search_Posistion( i, 6 )->iValue;
		equip.m_nTotalRate					= readFile.Search_Posistion( i, 7 )->iValue;
		equip.m_CostUsualItem.m_nClass		= readFile.Search_Posistion( i, 8 )->iValue;
		equip.m_CostUsualItem.m_nId			= readFile.Search_Posistion( i, 9 )->iValue;
		equip.m_CostUsualItem.m_nCount		= readFile.Search_Posistion( i, 10 )->iValue;
		equip.m_CostSpecialItem.m_nClass	= readFile.Search_Posistion( i, 11 )->iValue;
		equip.m_CostSpecialItem.m_nId		= readFile.Search_Posistion( i, 12 )->iValue;
		equip.m_CostSpecialItem.m_nCount	= readFile.Search_Posistion( i, 13 )->iValue;
		m_cfgEquip.AddEquipUpGrade( equip );
	}
}

void CfgData::InitEquipUpQualityTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_UP_QUALITY_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_UP_QUALITY_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	ItemData costItem = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquipUpQuality equip;
		equip.m_nId							= readFile.Search_Posistion( i, 0 )->iValue;
		equip.m_nGiveId						= readFile.Search_Posistion( i, 1 )->iValue;
		equip.m_nFailLine					= readFile.Search_Posistion( i, 2 )->iValue;
		equip.m_nSuccessLine				= readFile.Search_Posistion( i, 3 )->iValue;
		equip.m_nFullLucky					= readFile.Search_Posistion( i, 4 )->iValue;
		equip.m_nGetLucky					= readFile.Search_Posistion( i, 5 )->iValue;
		equip.m_nRate						= readFile.Search_Posistion( i, 6 )->iValue;
		equip.m_nTotalRate					= readFile.Search_Posistion( i, 7 )->iValue;
		equip.m_CostUsualItem.m_nClass		= readFile.Search_Posistion( i, 8 )->iValue;
		equip.m_CostUsualItem.m_nId			= readFile.Search_Posistion( i, 9 )->iValue;
		equip.m_CostUsualItem.m_nCount		= readFile.Search_Posistion( i, 10 )->iValue;
		equip.m_CostSpecialItem.m_nClass	= readFile.Search_Posistion( i, 11 )->iValue;
		equip.m_CostSpecialItem.m_nId		= readFile.Search_Posistion( i, 12 )->iValue;
		equip.m_CostSpecialItem.m_nCount	= readFile.Search_Posistion( i, 13 )->iValue;
		equip.m_OpenHoleRate				= readFile.Search_Posistion( i, 14 )->iValue;
		equip.m_OpenSecondHoleRate			= readFile.Search_Posistion( i, 15 )->iValue;
		m_cfgEquip.AddEquipUpQuality( equip );
	}
}

void CfgData::InitEquipUpStarTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_UP_STAR_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_UP_STAR_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	ItemData costItem = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquipUpStar equip;
		equip.m_nStar					= readFile.Search_Posistion( i, 0 )->iValue;
		equip.m_nFailLine				= readFile.Search_Posistion( i, 1 )->iValue;
		equip.m_nSuccessLine			= readFile.Search_Posistion( i, 2 )->iValue;
		equip.m_nFullLucky				= readFile.Search_Posistion( i, 3 )->iValue;
		equip.m_nFailAddLucky			= readFile.Search_Posistion( i, 4 )->iValue;
		equip.m_nRate					= readFile.Search_Posistion( i, 5 )->iValue;
		equip.m_nTotalRate				= readFile.Search_Posistion( i, 6 )->iValue;
		equip.m_CostUsualItem.m_nClass	= readFile.Search_Posistion( i, 7 )->iValue;	
		equip.m_CostUsualItem.m_nId		= readFile.Search_Posistion( i, 8 )->iValue;	
		equip.m_CostUsualItem.m_nCount	= readFile.Search_Posistion( i, 9 )->iValue;	
		equip.m_CostSpecialItem.m_nClass	= readFile.Search_Posistion( i, 10 )->iValue;
		equip.m_CostSpecialItem.m_nId		= readFile.Search_Posistion( i, 11 )->iValue;
		equip.m_CostSpecialItem.m_nCount	= readFile.Search_Posistion( i, 12 )->iValue;
		m_cfgEquip.AddEquipUpStar( equip );
	}
}

void CfgData::InitEquipAddAttrTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_ADD_ATTR_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_ADD_ATTR_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgAddAttr attr = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquipAddAttr equip;
		equip.m_nLevel			= readFile.Search_Posistion( i, 0 )->iValue;

		int32_t nIndex = 1;
		for ( int32_t j = 0; j < MAX_EQUIP_ADD_ATTR_COUNT; ++j )
		{
			bzero( &attr, sizeof( attr ) );
			attr.m_nAttr	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			attr.m_nValue	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			attr.m_nRate	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			if ( attr.m_nValue > 0 )
			{
				attr.m_nRate += equip.m_nMaxRate;
				equip.m_nMaxRate = attr.m_nRate;
				equip.m_lstAddAttr.push_back( attr );
			}
		}

		m_cfgEquip.AddEquipAddAttr( equip );
	}
}

void CfgData::InitEquipGoalTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_GOAL_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_GOAL_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquipGoal equip;
		equip.m_nIndex			= readFile.Search_Posistion( i, 0 )->iValue;
		equip.m_nType			= readFile.Search_Posistion( i, 1 )->iValue;
		equip.m_nParam			= readFile.Search_Posistion( i, 2 )->iValue;
		int32_t nIndex = 3;
		for ( int32_t j = 0; j < MAX_EQUIP_ADD_ATTR_COUNT; ++j )
		{
			equip.m_vAddAttr[j].index	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			equip.m_vAddAttr[j].addon	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}

		m_cfgEquip.AddEquipGoal( equip );
	}
}

void CfgData::InitEquipSuitTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_SUIT_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_SUIT_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgEquipSuit equip;
		equip.m_nId			= readFile.Search_Posistion( i, 0 )->iValue;
		std::string	str		= readFile.Search_Posistion( i, 2 )->pString;
		if ( str != "-1" )
		{
			StringVector vStr = StringUtility::split( str, "|" );
			for ( StringVector::iterator iter = vStr.begin(); iter != vStr.end(); ++iter )
			{
				int32_t nEquipId = atoi( iter->c_str() );
				if ( nEquipId > 0 )
				{
					equip.m_lstEquips.push_back( nEquipId );
				}
			}
		}
		int32_t nIndex = 3;
		for ( int32_t j = 0; j < MAX_EQUIP_ADD_ATTR_COUNT; ++j )
		{
			CfgSuitAttr addAttr = {};
			addAttr.m_nCount	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			addAttr.m_nAttr		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			addAttr.m_nValue	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			equip.m_lstSuitAttr.push_back( addAttr );
		}

		m_cfgEquip.AddEquipSuit( equip );
	}
}

void CfgData::InitWuHunHoleTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_WUHUN_HOLE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_WUHUN_HOLE_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nHole	= readFile.Search_Posistion( i, 0 )->iValue;
		int32_t nExp	= readFile.Search_Posistion( i, 1 )->iValue;

		m_cfgEquip.AddWuHunHoleExp( nHole, nExp );
	}
}

void CfgData::InitWuHunMoHunTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_WUHUN_MOHUN_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_WUHUN_MOHUN_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nLevel	= readFile.Search_Posistion( i, 0 )->iValue;
		int32_t nExp	= readFile.Search_Posistion( i, 1 )->iValue;

		m_cfgEquip.AddWuHunMoHunExp( nLevel, nExp );
	}
}

const CfgEquipTable& CfgData::GetEquipTable() const
{
	return m_cfgEquip;
}


void CfgData::InitItemGemTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_GEM_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_GEM_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgItemGem gem = {};
		gem.m_nId				= readFile.Search_Posistion( i, 0 )->iValue;
		gem.m_nType				= static_cast<int8_t>( readFile.Search_Posistion( i, 2 )->iValue );
		gem.m_nLevel			= readFile.Search_Posistion( i, 3 )->iValue;
		gem.m_nPrice			= readFile.Search_Posistion( i, 4 )->iValue;
		gem.m_nQuality			= static_cast<int8_t>( readFile.Search_Posistion( i, 5 )->iValue );
		gem.m_nLayNum			= readFile.Search_Posistion( i, 6 )->iValue;
		gem.m_EffectType		= readFile.Search_Posistion( i, 7 )->iValue;	
		gem.m_AddRate			= readFile.Search_Posistion( i, 8 )->iValue;
		gem.m_nGemLevel			= static_cast<int8_t>( readFile.Search_Posistion( i, 9 )->iValue );
		gem.m_nGrade			= readFile.Search_Posistion( i, 10 )->iValue;
		gem.m_nRansomWorth		= readFile.Search_Posistion( i, 11 )->iValue;
		gem.m_OutValue			= readFile.Search_Posistion( i, 18 )->iValue;
		gem.m_InValue			= readFile.Search_Posistion( i, 19 )->iValue;
		gem.m_nBroadcast		= readFile.Search_Posistion( i, 23 )->iValue;
		m_cfgItemGem.Add( gem );
	}
}

const CfgItemGemTable& CfgData::GetItemGemTable() const
{
	return m_cfgItemGem;
}

void CfgData::InitItemCombiTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_COMBI_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_COMBI_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgItemCombi itemCombi;
		int32_t Index = 0;
		itemCombi.m_nId			= readFile.Search_Posistion( i, Index )->iValue; Index++;
		//�������в���
		Index++;

		for ( int32_t j = 0; j < 3; j++ )
		{
			ItemData data = {};
			data.m_nId			= readFile.Search_Posistion( i, Index )->iValue; Index++;
			data.m_nClass		= readFile.Search_Posistion( i, Index )->iValue; Index++;
			data.m_nCount		= readFile.Search_Posistion( i, Index )->iValue; Index++;
			bool ItemIsInList = false;
			ItemDataList::iterator it = itemCombi.CostList.begin();
			for ( ; it != itemCombi.CostList.end(); ++it )
			{
				if ( it->m_nClass == data.m_nClass && it->m_nId == data.m_nId )
				{
					ItemIsInList = true;
					it->m_nCount += data.m_nCount;
				}
			}
			if ( !ItemIsInList )
			{
				itemCombi.CostList.push_back( data );
			}
		}
		itemCombi.m_nGiveId		= readFile.Search_Posistion( i, Index )->iValue; Index++;
		itemCombi.m_nGiveClass	= static_cast<int8_t>( readFile.Search_Posistion( i, Index )->iValue ); Index++;
		itemCombi.m_nGiveCount	= readFile.Search_Posistion( i, Index )->iValue; Index++;
		itemCombi.m_nMoney		= readFile.Search_Posistion( i, Index )->iValue; Index++;
		itemCombi.m_nRate		= readFile.Search_Posistion( i, Index )->iValue; Index++;
		itemCombi.m_nTotalRate	= readFile.Search_Posistion( i, Index )->iValue; Index++;
		Index++;
		Index++;
		itemCombi.m_IsGongGao	= readFile.Search_Posistion( i, Index )->iValue; Index++;
		m_cfgItemCombi.Add( itemCombi );
	}
}

const CfgItemCombiTable& CfgData::GetItemCombiTable() const
{
	return m_cfgItemCombi;
}

void CfgData::InitBagSlotOpenTimeTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_BAG_SLOT_OPEN_TIME_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_BAG_SLOT_OPEN_TIME_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgBagSlotOpenTime stu = {};
		stu.m_nSlot				= readFile.Search_Posistion( i, 0 )->iValue;
		stu.m_nSeconds			= readFile.Search_Posistion( i, 1 )->iValue;
		stu.m_nBagAddExp		= readFile.Search_Posistion( i, 2 )->iValue;		
		stu.m_nBagAddHp			= readFile.Search_Posistion( i, 3 )->iValue;
		stu.m_nDepotNeedSeconds = readFile.Search_Posistion( i, 4 )->iValue;
		stu.m_nDepotAddExp		= readFile.Search_Posistion( i, 5 )->iValue;	
		stu.m_nDepotAddHp		= readFile.Search_Posistion( i, 6 )->iValue;
		
		m_cfgBagSlotOpenTime.Add( stu );
	}
}

const CfgBagSlotOpenTimeTable& CfgData::GetBagSlotOpenTimeTable() const
{
	return m_cfgBagSlotOpenTime;
}

void CfgData::InitPlayerInitPetTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PLAYER_INIT_PET_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PLAYER_INIT_PET_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		Job_t job			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string	strPets = readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		if ( job <= 0 || job >= PJ_JOB_COUNT )
		{
			continue;
		}
		if ( strPets.size() < 3 )
		{
			continue;
		}
		Int32List pets;
		StringVector vPets = Answer::StringUtility::split( strPets, ":" );
		if ( vPets.size() > 0 )
		{
			for ( uint32_t j = 0; j < vPets.size(); ++j )
			{
				pets.push_back( atoi( vPets[j].c_str() ) );
			}
		}
		m_cfgPetTable.AddInitPet( job, pets );
	}
}

void CfgData::InitPetPackageTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_PACKAGE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_PACKAGE_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	PetPackageCost stu = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		bzero( &stu, sizeof( stu ) );
		int32_t nIndex = 0;
		stu.nPoints		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nCostType	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nCostValue	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nXoCostType	= readFile.Search_Posistion( i, nIndex )->iValue;   ++nIndex;
		stu.nXoCostValue= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		m_cfgPetTable.AddPetPackageCost( stu );
	}
}

void CfgData::InitPetTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		CfgPetData pet;

		pet.m_nPetId			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		pet.m_strName			= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		pet.m_nPetJob			= static_cast<Job_t>( readFile.Search_Posistion( i, nIndex )->iValue );	++nIndex;
		pet.m_nOrderJob			= static_cast<Job_t>( readFile.Search_Posistion( i, nIndex )->iValue );	++nIndex;
		pet.m_nRein				= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		pet.m_nRare				= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		pet.m_nPhase			= static_cast<PET_PHASE>( readFile.Search_Posistion( i, nIndex )->iValue );	++nIndex;
		pet.m_nLucky			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		for ( int32_t j = 0; j < PET_ATTR_COUNT; ++j )
		{
			pet.m_vMaxAttr[j]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			pet.m_vMaxPoints[j]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}

		int32_t nRate = 0;
		pet.m_nSkillId			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		pet.m_nSecondSkillId	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		for ( int32_t k = 0; k < PET_SKILL_COUNT; ++k )
		{
			pet.m_vSkill[k]		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

			// ���ܸ��ʼ�Ȩ
			nRate += readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			pet.m_vSkillRate[k]	= nRate;
		}
		// ����ICON	//����ģ��	//����ICON	//�����ɹ���ICON
		nIndex += 4;
		pet.m_nHatchTime		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		pet.m_nMutiHatchTime	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		// Desc	//Cost	//DropIcon
		nIndex += 3;
		pet.m_nRideSkin			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		//ModelPlace	//PetName	//PetDesc
		nIndex += 3;
		pet.m_nGrowRatio		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		nIndex += 1;
		pet.m_nXxoo				= (int8_t)readFile.Search_Posistion( i, nIndex )->iValue; ++nIndex;
		nIndex += 5;
		pet.m_Zoarium			= (int8_t)readFile.Search_Posistion( i, nIndex )->iValue; ++nIndex;
		nIndex += 9;
		pet.m_WuHunExp			= readFile.Search_Posistion( i, nIndex )->iValue; ++nIndex;
		m_cfgPetTable.Add( pet );
	}
}

const CfgPetTable& CfgData::GetPetTable() const
{
	return m_cfgPetTable;
}

void CfgData::InitPetEggTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_EGG_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_EGG_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		CfgPetEgg egg = {};

		egg.nId		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		++nIndex;	// name
		egg.nPetId	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		egg.nLevel	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		egg.nRein	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		for ( int32_t j = 0; j < PET_ATTR_COUNT; ++j )
		{
			egg.vAttr[j] = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}
		++nIndex;
		egg.nHatchingTime		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		egg.nMutiHatchingTime	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		++nIndex;
		egg.nPrice				= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		++nIndex;
		++nIndex;
		++nIndex;
		egg.nWuHunExp			= readFile.Search_Posistion( i, nIndex )->iValue;
		++nIndex;
		++nIndex;
		++nIndex;
		egg.broadcast			= readFile.Search_Posistion( i, nIndex )->iValue;

		m_cfgPetEggTable.Add( egg );
	}
}

const CfgPetEggTable& CfgData::GetPetEggTable() const
{
	return m_cfgPetEggTable;
}

void CfgData::InitPetAttrInitRateTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_INIT_ATTR_RATE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_INIT_ATTR_RATE_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int32_t nPercent	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nStartRate	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nLuckyRate	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nGrowRate	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgPetAttrInitRateTable.add( nPercent, nStartRate, nLuckyRate, nGrowRate );
	}
}

const CfgPetAttrInitRateTable& CfgData::GetPetAttrInitRateTable() const
{
	return m_cfgPetAttrInitRateTable;
}

void CfgData::InitPetIllusionTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_ILLUSION_GROW_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_ILLUSION_GROW_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgPetIllusionGrow grow = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		if ( i == iBaseTableCount - 1 )
		{
			break;
		}
		int32_t nIndex = 0;
		bzero( &grow, sizeof( grow ) );
		grow.nMainPointMin	= readFile.Search_Posistion( i, nIndex )->iValue;
		grow.nMainPointMax	= readFile.Search_Posistion( i+1, nIndex )->iValue;	++nIndex;
		grow.nVicePoint		= readFile.Search_Posistion( i, nIndex )->iValue;
		grow.nVicePointMax	= readFile.Search_Posistion( i+1, nIndex )->iValue;	++nIndex;
		grow.nViceLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		grow.nShopIds		= parseInt32VectorString( i,readFile.Search_Posistion( i, nIndex )->pString); ++nIndex; 
		++nIndex;
		grow.Compensation	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgPetIllusionTable.AddGrow( grow );
	}
}

const CfgPetIllusionTable& CfgData::GetPetIllusionTable() const
{
	return m_cfgPetIllusionTable;
}

void CfgData::InitPetKnightTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_KNIGHT_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_KNIGHT_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int32_t nKnight	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		if ( nKnight <= PK_NONE || nKnight >= PET_KNIGHT_SIZE )
		{
			LOG_ERROR("open FILE_PET_KNIGHT_TABLE ʧ��,δ����Ļ�����ʿ����");
			return;
		}
		++nIndex;	// ����
		m_cfgPetKnightTable.m_vKnight[nKnight].nLevel = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		m_cfgPetKnightTable.m_vKnight[nKnight].nTitle = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string petType = readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		StringVector vString = Answer::StringUtility::split( petType, "|" );
		for ( uint32_t j = 0; j < vString.size(); ++j )
		{
			int32_t nPetId = atoi( vString[j].c_str() );
			if ( nPetId > 0 )
			{
				m_cfgPetKnightTable.m_vKnight[nKnight].compIdList.push_back( nPetId );
			}
		}

		m_cfgPetKnightTable.m_vKnight[nKnight].nEffectType = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		++nIndex;	// ����
		for ( int32_t k = 0; k < MAX_KNIGHT_QUALITY_SIZE; ++k )
		{
			m_cfgPetKnightTable.m_vKnight[nKnight].vQuality[k]		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			m_cfgPetKnightTable.m_vKnight[nKnight].vEffectValue[k]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}
	}
}

const CfgPetKnightTable& CfgData::GetPetKnightTable() const
{
	return m_cfgPetKnightTable;
}

void CfgData::InitCharPetHatchPoolTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_HATCH_POOL_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_HATCH_POOL_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int32_t nOrder	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		if ( nOrder < 0 )
		{
			continue;
		}
		int32_t nHatchPoolLevel			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nHatchPoolVipLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nMutiHatchPoolLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nMutiHatchPoolVipLevel	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		if ( nOrder < PET_HATCH_POOL_SIZE )
		{
			m_cfgCharPetTable.m_vHatchPool[nOrder].nLevel	= nHatchPoolLevel;
			m_cfgCharPetTable.m_vHatchPool[nOrder].nVipLevel= nHatchPoolVipLevel;
		}
		if ( nOrder < PET_MUTI_HATCH_POOL_SIZE )
		{
			m_cfgCharPetTable.m_vMutiHatchPool[nOrder].nLevel	= nMutiHatchPoolLevel;
			m_cfgCharPetTable.m_vMutiHatchPool[nOrder].nVipLevel= nMutiHatchPoolVipLevel;
		}
	}
}

void CfgData::InitPetLucyItemTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_LUCKY_ITEM_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_LUCKY_ITEM_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgPetLuckyItem stu = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		bzero( &stu, sizeof(stu) );
		stu.nLucky	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nClass	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nId		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nCount	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nRate	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgCharPetTable.addPetLuckyUseItem( stu );
	}
}

const CfgCharPetTable& CfgData::GetCharPetTable() const
{
	return m_cfgCharPetTable;
}

void CfgData::InitFamilyTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgFamily family;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		family.CleanUp();
		family.nLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.nExp			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.nBattle		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.nMaxMembers	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nTotomCount	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string totoms	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		StringVector vTotom = StringUtility::split( totoms, ":" );
		for ( uint32_t j = 0; j < vTotom.size(); ++j )
		{
			m_cfgFamilyTable.AddActiveTotom( atoi( vTotom[j].c_str() ), family.nLevel );
		}
		family.vPosition[FP_VICE]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_HONOR_VICE]		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_ELDER]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_HONOR_ELDER]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_SENETE]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_HONOR_SENETE]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_ELIT]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_SENIOR]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgFamilyTable.Add( family );
	}
}

void CfgData::InitFamilyPositionTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_POSITION_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_POSITION_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgFamilyPosition position;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		bzero( &position, sizeof( position ) );
		int8_t	nPosition			= readFile.Search_Posistion( i, 0 )->iValue;
		position.nNeedContribution	= readFile.Search_Posistion( i, 2 )->iValue;
		position.nShareBattleRatio	= readFile.Search_Posistion( i, 4 )->iValue;

		m_cfgFamilyTable.Add( nPosition, position );
	}
}

const CfgFamilyTable& CfgData::GetFamilyTable() const
{
	return m_cfgFamilyTable;
}

void CfgData::InitFamilyPetRegistTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_PET_REGIST_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_PET_REGIST_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int32_t nLevel	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nCount	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		m_cfgFamilyPetRegistTable.Add( nLevel, nCount );
	}
}

const CfgFamilyPetRegistTable& CfgData::GetFamilyPetRegistTable() const
{
	return m_cfgFamilyPetRegistTable;
}

void CfgData::InitTeamBuffTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_TEAM_BUFF_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_TEAM_BUFF_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 4;
		int32_t nNum		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nExpRatio	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nHPRatio	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		m_cfgTeamTable.Add( nNum, nExpRatio, nHPRatio );
	}
}

const CfgTeamTable& CfgData::GetTeamTable() const
{
	return m_cfgTeamTable;
}

void CfgData::InitInsidePetTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_INSIDE_PET_ATTR_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_INSIDE_PET_ATTR_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		int32_t		level		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t		exp			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string addonattr1	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		std::string addonattr2	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		std::string addonattr3	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;

		AttrAddonVector attrAddons1 = parasePetAttrAddon( addonattr1 );
		AttrAddonVector attrAddons2 = parasePetAttrAddon( addonattr2 );
		AttrAddonVector attrAddons3 = parasePetAttrAddon( addonattr3 );

		m_cfgInsidePetTable.Add( level, exp, attrAddons1, attrAddons2, attrAddons3 );
	}
}

AttrAddonVector CfgData::parasePetAttrAddon( const std::string& addonAttr )
{
	AttrAddonVector attrAddons;
	StringVector strAttrAddons = StringUtility::split( addonAttr, "|" );
	for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
	{
		StringVector strAttrAddon = StringUtility::split( *it, ":" );
		if ( strAttrAddon.size() == 2 )
		{
			AttrAddon attrAddon = {};
			attrAddon.index = atoi(strAttrAddon[0].c_str());
			attrAddon.addon = atoi(strAttrAddon[1].c_str());
			if ( attrAddon.index > 0 && attrAddon.addon > 0 )
			{
				attrAddons.push_back( attrAddon );
			}
		}
		else
		{
			LOG_ERROR("CfgData::parasePetAttrAddon() wrong data with str = %s\n", addonAttr.c_str());
		}
	}
	return attrAddons;
}

void CfgData::InitInsidePetExpItemTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_INSIDE_PET_EXP_ITEM_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_INSIDE_PET_EXP_ITEM_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		int32_t	id	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t	exp	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgInsidePetTable.AddExpItem( id, exp );
	}
}

const CfgInsidePetTable& CfgData::GetInsidePetTable() const
{
	return m_cfgInsidePetTable;
}

void CfgData::InitSoulAttrTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_SOUL_ATTR_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_SOUL_ATTR_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		int32_t		level		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t		exp			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string addonattr1	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		std::string addonattr2	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		std::string addonattr3	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		int32_t		Battle		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		AttrAddonVector attrAddons1 = parasePetAttrAddon( addonattr1 );
		AttrAddonVector attrAddons2 = parasePetAttrAddon( addonattr2 );
		AttrAddonVector attrAddons3 = parasePetAttrAddon( addonattr3 );

		m_cfgSoulAttrTable.Add( level, exp, attrAddons1, attrAddons2, attrAddons3, Battle );
	}
}

const CfgSoulAttrTable& CfgData::GetSoulAttrTable() const
{
	return m_cfgSoulAttrTable;
}

void CfgData::InitFamilyWarJoinRewardTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_WAR_JOIN_REWARD_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_WAR_JOIN_REWARD_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		int32_t	level	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t	exp		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgFamilyWarJoinRewardTable.Add( level, exp );
	}
}

const CfgFamilyWarJoinRewardTable& CfgData::GetFamilyWarJoinRewardTable() const
{
	return m_cfgFamilyWarJoinRewardTable;
}

void CfgData::InitFamilyLightExpTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_LIGHT_EXP_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_LIGHT_EXP_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		int32_t	level	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t	exp		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgFamilyLightExpTable.Add( level, exp );
	}
}

const CfgFamilyLightExpTable& CfgData::GetFamilyLightExpTable() const
{
	return m_cfgFamilyLightExpTable;
}

void CfgData::InitHorseRacingRewardTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_HORSE_RACING_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_HORSE_RACING_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		int32_t nIndex = 0;
		CfgHorseRacingReward reward = {};
		reward.nIndex		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nMaxIndex	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nExp			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nMoney		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string strItem	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		reward.Items		= parseItemString( reward.nIndex,strItem );
		m_cfgHorseRacingRewardTable.Add( reward );
	}
}

const CfgHorseRacingRewardTable& CfgData::GetHorseRacingRewardTable() const
{
	return m_cfgHorseRacingRewardTable;
}


void CfgData::InitHallOfFameRewardTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_HALL_OF_FAME_REWARD_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_HALL_OF_FAME_REWARD_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		HallOfFameReward reward; 
		int32_t nIndex = 0;
		reward.nIndexMin	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nIndexMax	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nHonor		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string items	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;

		if ( items.size() > 3 )
		{
			StringVector vItems = Answer::StringUtility::split( items, "|" );
			for ( uint32_t j = 0; j < vItems.size(); ++j )
			{
				StringVector vParam = Answer::StringUtility::split( vItems[j], ":" );
				if ( vParam.size() == 3 )
				{
					MemChrBag item = {};
					item.itemId		= atoi( vParam[0].c_str() );
					item.itemClass	= atoi( vParam[1].c_str() );
					item.itemCount	= atoi( vParam[2].c_str() );
					reward.items.push_back( item );
				}
			}
		}

		m_cfgHallOfFameTable.AddReward( reward );
	}
}

const CfgHallOfFameTable& CfgData::GetHallOfFameTable() const
{
	return m_cfgHallOfFameTable;
}

void CfgData::InitSkillLevelUpTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_SKILL_LEVEL_UP_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_SKILL_LEVEL_UP_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgSkillLevelUp cfgSkill = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		bzero( &cfgSkill, sizeof( cfgSkill ) );
		cfgSkill.nSkillId		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		for ( int32_t j = 0; j < MAX_SKILL_LEVEL; ++j )
		{
			cfgSkill.nBookId[j]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}

		m_cfgSkillLevelUpTable.Add( cfgSkill );
	}
}

const CfgSkillLevelUpTable& CfgData::GetSkillLevelUpTable() const
{
	return m_cfgSkillLevelUpTable;
}

void CfgData::InitTaskCycleStarTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_TASK_CYCLE_STAR_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_TASK_CYCLE_STAR_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	int32_t vRate[MAX_CYCLE_STARS] = {};
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		CycleStarRate stu = {};
		stu.Level		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		for ( int32_t j = 0; j < MAX_CYCLE_STARS; ++j )
		{
			stu.Rate[j] = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		}
		stu.TenStarTimes = readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		m_cfgTaskCycleTable.AddStarRate( stu );
	}
}

const CfgTaskCycleTable& CfgData::GetTaskCycleTable() const
{
	return m_cfgTaskCycleTable;
}

const CfgFamilyTask& CfgData::GetFamilyTaskTable() const
{
	return m_FamilyTaskTable;
}

void CfgData::InitFriendExpTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FRIEND_EXP_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FRIEND_EXP_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgFriendExp stu = {};
		stu.Level				= readFile.Search_Posistion( i, 0 )->iValue;
		stu.Exp					= readFile.Search_Posistion( i, 1 )->iValue;
		m_FriendExpTable[stu.Level] = stu; 
	}
}

void CfgData::InitPkDropRateTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PK_DROP_RATE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PK_DROP_RATE_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		PkDropRate stu = {};
		stu.PkValues						= readFile.Search_Posistion( i, 0 )->iValue;
		stu.EquipCount						= readFile.Search_Posistion( i, 1 )->iValue;
		stu.EquipRate						= readFile.Search_Posistion( i, 2 )->iValue;
		stu.UsualCountRate					= readFile.Search_Posistion( i, 3 )->iValue;		
		stu.UsualDropRate					= readFile.Search_Posistion( i, 4 )->iValue;
		stu.SpecialCountRate				= readFile.Search_Posistion( i, 5 )->iValue;
		stu.SpecialDropRate					= readFile.Search_Posistion( i, 6 )->iValue;
		stu.OverlayRate						= readFile.Search_Posistion( i, 7 )->iValue;
		stu.MoneyRate						= readFile.Search_Posistion( i, 8 )->iValue;
		m_PkDropRateTable.push_back(stu); 
	}
}

PkDropRate* CfgData::GetPkDropRate( int32_t PkValues )
{
	std::list<PkDropRate>::iterator it = m_PkDropRateTable.begin();
	for ( ; it != m_PkDropRateTable.end(); ++it )
	{
		if ( PkValues <= it->PkValues )
		{
			return &(*it);
		}
	}
	return NULL;
}

void CfgData::InitQiangHuaWorthTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_QIANG_HUA_WORTH_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_QIANG_HUA_WORTH_TABLE ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		QiangHuaWorthTable stu = {};
		int8_t	quality	  = 	(int8_t)readFile.Search_Posistion( i, 0 )->iValue;
		for ( int32_t j = 0; j < EQUIP_MAX_STAT; ++j )
		{
			stu.Worth[j] = readFile.Search_Posistion( i, 1 + j )->iValue;
		}
		m_QiangHuaWorthTable[quality] = stu;
	}
}

int32_t CfgData::GetQiangHuaWorth( int8_t Quality, int8_t Star )
{
	if ( Star <= 0 || Star > EQUIP_MAX_STAT )
	{
		return 0;
	}

	QiangHuaWorthMap::iterator it = m_QiangHuaWorthTable.find( Quality );
	if ( it != m_QiangHuaWorthTable.end() )
	{
		return it->second.Worth[Star-1];
	}
	return 0;
}

int32_t CfgData::GetFriendExpByLevel( int32_t Level )
{
	CfgFriendExpTable::iterator it = m_FriendExpTable.find( Level );
	if ( it != m_FriendExpTable.end() )
	{
		return it->second.Exp;
	}
	return 0;
}

void CfgData::InitBuyFaBaoResTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_BUY_FA_BAO_RES_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_BUY_FA_BAO_RES_TABLE.txt ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	int32_t iValue = 0;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		BuyFaBaoResCfg stu;
		stu.id				= readFile.Search_Posistion( i, 0 )->iValue;
		stu.FaBaoResType	= (int8_t)readFile.Search_Posistion( i, 1 )->iValue;
		stu.NeedGold		= readFile.Search_Posistion( i, 2 )->iValue;
		stu.GetResValues	= readFile.Search_Posistion( i, 3 )->iValue;
		m_FaBaoResMap[stu.id]= stu;
	}
}

BuyFaBaoResCfg* CfgData::GetBuyFaBaoResCfg( int32_t Id )
{
	FaBaoResMap::iterator it = m_FaBaoResMap.find( Id );
	if ( it != m_FaBaoResMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

QuestionsVector	CfgData::GetAllQuestions()
{
	return m_QuestionsVct;
}

CfgPetGift*	CfgData::GetPetCfg( int32_t nId )
{
	PetGiftMap::iterator it = m_PetGiftTable.find( nId );
	if ( it != m_PetGiftTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void CfgData::InitDaTiHD()
{
	CDBCFile ReadFile(0);
	bool Ret = ReadFile.OpenFromTXT( FILE_QUESTIONS_TABLE );
	if ( Ret == false )
	{
		LOG_ERROR("open FILE_QUESTIONS_TABLE.txt ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t BaseTableCount			=	ReadFile.GetRecordsNum();
	int32_t BaseColumnCount			=	ReadFile.GetFieldsNum();
	if ( BaseColumnCount <= 0 )
	{
		return;
	}
	m_QuestionsVct.clear();
	for( int32_t j = 0;j < BaseTableCount; ++j )
	{
		CfgQuestions Stu = {};
		Stu.QuestionId		= ReadFile.Search_Posistion( j, 0 )->iValue;
		Stu.AnswerId		= (int8_t)ReadFile.Search_Posistion( j, 6 )->iValue;
		m_QuestionsVct.push_back( Stu );
	}
}

void CfgData::InitFaBaoTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FA_BAO_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FA_BAO_TABLE.txt ʧ��,�����ļ�����Сд");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	int32_t iValue = 0;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgFaBao stu;
		stu.FaBaoId			= readFile.Search_Posistion( i, 0 )->iValue;
		stu.NextFaBaoId		= readFile.Search_Posistion( i, 2 )->iValue;
		stu.FaBaoType		= readFile.Search_Posistion( i, 3 )->iValue;
		stu.FaBaoLevel		= readFile.Search_Posistion( i, 4 )->iValue;
		stu.NeedRes			= readFile.Search_Posistion( i, 5 )->iValue;
		for ( int32_t j = 0; j < 7; j++ )
		{
			AddAttribute AddAttr;
			AddAttr.m_nAddAttrType	= readFile.Search_Posistion( i, 6 + j*2 )->iValue;
			AddAttr.m_nAddAttrValue	= readFile.Search_Posistion( i, 6 + j*2 + 1 )->iValue;
			if ( AddAttr.m_nAddAttrValue > 0 )
			{
				stu.m_AttrList.push_back( AddAttr );
			}	
		}
		m_FaBaoTable.AddFaBao(  stu );
	}
}

FaBaoTable&	CfgData::GetFaBaoTable()
{
	return m_FaBaoTable;
}

void CfgData::InitBossInfo()
{
	CDBCFile InitBossFile(0);
	bool ret = InitBossFile.OpenFromTXT(FILE_BOSS_INFO_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_BOSS_INFO_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	InitBossFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	InitBossFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		BossInfo stu;
		stu.m_BossId				= InitBossFile.Search_Posistion(i,0)->iValue;
		Position Pos;
		Pos.x						= InitBossFile.Search_Posistion(i,2)->iValue;
		Pos.y						= InitBossFile.Search_Posistion(i,3)->iValue;
		stu.m_RevivePosVector		= paresPosition(InitBossFile.Search_Posistion(i,4)->pString);
		stu.m_NeedResetReviveTime	= (int8_t)InitBossFile.Search_Posistion(i,6)->iValue;
		stu.m_IsShow				= (int8_t)InitBossFile.Search_Posistion(i,7)->iValue;
		m_BossInfo[stu.m_BossId] = stu;
	}
}

BossInfo* CfgData::GetBossInfo( int32_t BossId )
{
	BossInfoMap::iterator it = m_BossInfo.find( BossId );
	if ( it != m_BossInfo.end() )
	{
		return &(it->second);
	}
	return NULL;
}

BossInfoMap& CfgData::GetBossInfoMap()
{
	return m_BossInfo;
}

void CfgData::InitSysMail()
{
	CDBCFile SysMailFile(0);
	bool ret = SysMailFile.OpenFromTXT(FILE_SYS_MAIL_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_SYS_MAIL_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	SysMailFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	SysMailFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgSysMail mail;
		mail.id				= SysMailFile.Search_Posistion(i,0)->iValue;
		mail.sender_name	= SysMailFile.Search_Posistion(i,1)->pString;
		mail.title			= SysMailFile.Search_Posistion(i,2)->pString;
		mail.content		= SysMailFile.Search_Posistion(i,3)->pString;
		mail.item			= parseItemString(mail.id,SysMailFile.Search_Posistion(i,4)->pString);

		m_sysMail[mail.id] = mail;
	}
}

CfgSysMail*	CfgData::GetSysMail( int32_t Id )
{
	CfgSysMailTable::iterator it = m_sysMail.find( Id );
	if ( it != m_sysMail.end() )
	{
		return &(it->second);
	}
	return NULL;
}

FaBaoTable::FaBaoTable()
{
	m_FaBaoTable.clear();
}

CfgFaBao* FaBaoTable::GetFaBaoCfg( int32_t FaBaoId )
{
	FaBaoMap::iterator it = m_FaBaoTable.find( FaBaoId );
	if ( it != m_FaBaoTable.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void FaBaoTable::AddFaBao( CfgFaBao& Stu )
{
	m_FaBaoTable[Stu.FaBaoId] = Stu;
}

CTouZiCfg::CTouZiCfg()
{
	m_MoonCardCfgMap.clear();
	m_LevelUpCfgMap.clear();
}

void CTouZiCfg::InitTouZiTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_MOON_CARD_TOU_ZI_TABEL);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_MOON_CARD_TOU_ZI_TABEL failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		MoonCardTouZiCfg stu = {};
		stu.Index			= (int16_t)TabFile.Search_Posistion(i,0)->iValue;
		stu.NeedDay			= (int16_t)TabFile.Search_Posistion(i,1)->iValue;
		stu.CurrencyType	= (int8_t)TabFile.Search_Posistion(i,2)->iValue;
		stu.CurrencyValues	= TabFile.Search_Posistion(i,3)->iValue;
		m_MoonCardCfgMap[stu.Index] = stu;
	}

	CDBCFile LevelTabFile(0);
	bool ret1 = LevelTabFile.OpenFromTXT(FILE_LEVEL_UP_TOU_ZI_TABLE);
	if ( ret1 == false )
	{
		LOG_ERROR("open FILE_LEVEL_UP_TOU_ZI_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount1		=	LevelTabFile.GetRecordsNum();
	int32_t iBaseColumnCount1		=	LevelTabFile.GetFieldsNum();
	if (iBaseColumnCount1 <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount1;i++ )
	{
		LevelUpTouZiCfg stu = {};
		stu.Index			= (int16_t)LevelTabFile.Search_Posistion(i,0)->iValue;
		stu.NeedLevel		= LevelTabFile.Search_Posistion(i,1)->iValue;
		stu.Rate			= LevelTabFile.Search_Posistion(i,2)->iValue;
		m_LevelUpCfgMap[stu.Index] = stu;
	}
}

MoonCardTouZiCfg* CTouZiCfg::GetMoonCardTouZiCfg( int16_t Index )
{
	MoonCardTouZiCfgMap::iterator it = m_MoonCardCfgMap.find( Index );
	if ( it != m_MoonCardCfgMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

LevelUpTouZiCfg* CTouZiCfg::GetLevelUpTouZiCfg( int16_t Index )
{
	LevelUpTouZiCfgMap::iterator it = m_LevelUpCfgMap.find( Index );
	if ( it != m_LevelUpCfgMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

MoonCardTouZiCfgMap& CTouZiCfg::GetMoonCardTable()
{
	return m_MoonCardCfgMap;
}

LevelUpTouZiCfgMap&	CTouZiCfg::GetLevelUpTable()
{
	return m_LevelUpCfgMap;
}

ChouJiangConfig::ChouJiangConfig()
{
	m_CJShopMap.clear();
	m_CJCostMap.clear();
	m_CJCfgList.clear();	
}	
	
void ChouJiangConfig::InitShopMap()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_CHOU_JIANG_SHOP_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_CHOU_JIANG_SHOP_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		ChouJiangShop CJShop = {};
		CJShop.Index		= TabFile.Search_Posistion(i,0)->iValue;
		CJShop.ItemId		= TabFile.Search_Posistion(i,1)->iValue;
		CJShop.ItemClass	= (int8_t)TabFile.Search_Posistion(i,2)->iValue;
		CJShop.ItemCount	= TabFile.Search_Posistion(i,3)->iValue;
		CJShop.NeedScore	= TabFile.Search_Posistion(i,4)->iValue;
		CJShop.Type			= TabFile.Search_Posistion(i,5)->iValue;
		CJShop.Limit		= TabFile.Search_Posistion(i,6)->iValue;
		CJShop.Bind			= (int8_t)TabFile.Search_Posistion(i,7)->iValue;
		m_CJShopMap[CJShop.Index] = CJShop;
	}
}

void ChouJiangConfig::InitCostMap()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_CHOU_JIANG_COST_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_CHOU_JIANG_COST_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		ChouJiangCost CJCost = {};
		CJCost.ChouJiangType		= (int8_t)TabFile.Search_Posistion(i,0)->iValue;
		CJCost.CostGold				= TabFile.Search_Posistion(i,1)->iValue;
		CJCost.CostGold2			= TabFile.Search_Posistion(i,2)->iValue;
		CJCost.CostItemClass		= (int8_t)TabFile.Search_Posistion(i,3)->iValue;
		CJCost.CostItemId			= TabFile.Search_Posistion(i,4)->iValue;
		CJCost.CostItemCount		= TabFile.Search_Posistion(i,5)->iValue;
		CJCost.AddScore				= TabFile.Search_Posistion(i,6)->iValue;
		m_CJCostMap[CJCost.ChouJiangType] = CJCost;
	}
}

void ChouJiangConfig::InitCfgList()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT(FILE_CHOU_JIANG_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_CHOU_JIANG_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		ChouJiangCfg CJCfg = {};
		CJCfg.ChouJiangType		= (int8_t)TabFile.Search_Posistion(i,1)->iValue;
		CJCfg.ItemClass			= (int8_t)TabFile.Search_Posistion(i,2)->iValue;
		CJCfg.ItemId			= TabFile.Search_Posistion(i,3)->iValue;
		CJCfg.ItemCount			= TabFile.Search_Posistion(i,4)->iValue;
		CJCfg.Quality			= (int8_t)TabFile.Search_Posistion(i,5)->iValue;
		CJCfg.Star				= (int8_t)TabFile.Search_Posistion(i,6)->iValue;
		CJCfg.Probability		= TabFile.Search_Posistion(i,7)->iValue;
		CJCfg.IsRecord			= (int8_t)TabFile.Search_Posistion(i,8)->iValue;
		CJCfg.IsGongGao			= (int8_t)TabFile.Search_Posistion(i,9)->iValue;
		m_CJCfgList.push_back( CJCfg );
	}
}

void ChouJiangConfig::InitCJConfig()
{
	InitShopMap();
	InitCostMap();
	InitCfgList();
}

ChouJiangCost* ChouJiangConfig::GetCJCost( int8_t ChouJiangType )
{
	CJCostMap::iterator it = m_CJCostMap.find( ChouJiangType );
	if ( it != m_CJCostMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

ChouJiangShop* ChouJiangConfig::GetCJShop( int8_t Index )
{
	CJShopMap::iterator it =  m_CJShopMap.find( Index );
	if ( it != m_CJShopMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

ChouJiangCfg ChouJiangConfig::GetCJCfg( int8_t ChouJiangType, bool IsSpecial )
{
	CJCfgList::iterator it = m_CJCfgList.begin();
	CJCfgList CJCfgTmpList;
	CJCfgTmpList.clear();
	int32_t MaxProbability = 0;
	for ( ; it != m_CJCfgList.end(); ++it )	
	{
		if ( IsSpecial )
		{
			if ( it->ChouJiangType == ChouJiangType && it->Quality == 4 )
			{
				MaxProbability += it->Probability;
				CJCfgTmpList.push_back(*it);
			}
		}
		else
		{
			if ( it->ChouJiangType == ChouJiangType )
			{
				MaxProbability += it->Probability;
				CJCfgTmpList.push_back(*it);
			}
		}
	}
	CJCfgList::iterator itTmp = CJCfgTmpList.begin();
	int32_t nRand = RANDOM.generate( 0, MaxProbability );
	for ( ; itTmp != CJCfgTmpList.end(); ++itTmp )
	{
		if ( itTmp->Probability >= nRand )
		{
			return *itTmp;
		}
		else
		{
			nRand -= itTmp->Probability;
		}
	}
	ChouJiangCfg stu = {};
	return stu;
}

void CfgData::InitPetGiftTable()
{
	CDBCFile PetGiftTable(0);
	bool ret = PetGiftTable.OpenFromTXT(FILE_PET_LI_BAO_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_LI_BAO_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	PetGiftTable.GetRecordsNum();
	int32_t iBaseColumnCount	=	PetGiftTable.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgPetGift PetGift = {};
		PetGift.nId						= PetGiftTable.Search_Posistion(i,0)->iValue;
		PetGift.nPetBaseId				= PetGiftTable.Search_Posistion(i,2)->iValue;
		PetGift.nLevel					= PetGiftTable.Search_Posistion(i,3)->iValue;
		PetGift.nGrowTimes				= PetGiftTable.Search_Posistion(i,4)->iValue;
		for ( int32_t j = 0; j < PET_ATTR_COUNT; ++j )
		{
			PetGift.m_vMaxAttr[j]	= PetGiftTable.Search_Posistion(i, 5 + j )->iValue;
		}
		m_PetGiftTable[PetGift.nId] = PetGift;
	}
}



void CfgData::InitShangChengTable()
{
	CDBCFile ShangChengTable(0);
	bool ret = ShangChengTable.OpenFromTXT(FILE_GAME_SHOP_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_GAME_SHOP_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	ShangChengTable.GetRecordsNum();
	int32_t iBaseColumnCount	=	ShangChengTable.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgGameShop ShangCheng = {};
		ShangCheng.ShopId				= ShangChengTable.Search_Posistion(i,0)->iValue;
		ShangCheng.ItemId				= ShangChengTable.Search_Posistion(i,1)->iValue;
		ShangCheng.ItemClass			= ShangChengTable.Search_Posistion(i,2)->iValue;
		ShangCheng.ItemBind				= ShangChengTable.Search_Posistion(i,3)->iValue;
		ShangCheng.LimitType			= ShangChengTable.Search_Posistion(i,4)->iValue;
		ShangCheng.LimitCount			= ShangChengTable.Search_Posistion(i,5)->iValue;
		ShangCheng.LimitStartTime		= Answer::DayTime::StringToIntTime( ShangChengTable.Search_Posistion(i,6)->pString );
		ShangCheng.LimitEndTime			= Answer::DayTime::StringToIntTime( ShangChengTable.Search_Posistion(i,7)->pString );
		ShangCheng.OriginalPrice		= ShangChengTable.Search_Posistion(i,8)->iValue;
		ShangCheng.Price				= ShangChengTable.Search_Posistion(i,9)->iValue;
		ShangCheng.ShopType				= ShangChengTable.Search_Posistion(i,10)->iValue;
		ShangCheng.VipLevelLimit		= ShangChengTable.Search_Posistion(i,14)->iValue;

		m_GameShopMap[ShangCheng.ShopId] = ShangCheng;
	}
}

CfgGameShop* CfgData::GetGameShop(int32_t nShopId )
{
	GameShopMap::iterator it = m_GameShopMap.find( nShopId );
	if ( it != m_GameShopMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

CfgGameShop* CfgData::GetGameShopItem( int8_t Class, int32_t Id )
{
	GameShopMap::iterator it = m_GameShopMap.begin();
	for ( ; it != m_GameShopMap.end(); ++it )
	{
		if ( it->second.ItemClass == Class && it->second.ItemId == Id 
			&& it->second.ShopType != BANG_SHI_SHANG_CHENG_TYPE )	// ��ͬid�����ڰ�ʯ�̳��д���
		{
			return &(it->second);
		}
	}
	return NULL;
}

ChouJiangConfig& CfgData::GetChouJiangCfg()
{
	return m_ChouJiangConfig;
}

CQiFuTable&	CfgData::GetQiFuTable()
{
	return m_QiFuTable;
}


VipTable& CfgData::GetVipTable()
{
	return m_VipTable;
}

CQiFuTable::CQiFuTable()
{
	m_QiFuMoneyCfg.clear();
	m_QiFuExpCfg.clear();
}
	
void CQiFuTable::InitQiFuTable()
{
	CDBCFile QiFuTable(0);
	bool ret = QiFuTable.OpenFromTXT(FILE_QI_FU_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_QI_FU_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	QiFuTable.GetRecordsNum();
	int32_t iBaseColumnCount	=	QiFuTable.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	QiFuTimesMap TimesMap;
	int32_t nLevel = 0;
	int8_t	nType  = 0;
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		QiFuCfg		stu = {};
		int8_t		Type		= (int8_t)QiFuTable.Search_Posistion(i,1)->iValue;
		int32_t		Level		= QiFuTable.Search_Posistion(i,2)->iValue;
		int32_t		Times		= QiFuTable.Search_Posistion(i,3)->iValue;

		if ( nType == QT_MONEY && nType != Type )
		{
			m_QiFuMoneyCfg[nLevel] = TimesMap;
			TimesMap.clear();
		}
		else if ( nType == QT_EXP && nType != Type )
		{
			m_QiFuExpCfg[nLevel] = TimesMap;
			TimesMap.clear();
		}

		nLevel = Level;
		nType  = Type;
	
		stu.GetMoney			= QiFuTable.Search_Posistion(i,4)->iValue;
		stu.GetExp				= QiFuTable.Search_Posistion(i,5)->iValue;
		stu.CostGold			= QiFuTable.Search_Posistion(i,6)->iValue;
		stu.CostItemClass		= (int8_t)QiFuTable.Search_Posistion(i,7)->iValue;
		stu.CostItemId			= QiFuTable.Search_Posistion(i,8)->iValue;
		stu.CostItemCount		= QiFuTable.Search_Posistion(i,9)->iValue;
		TimesMap[Times]=stu;
	}
	if ( nType == QT_MONEY  )
	{
		m_QiFuMoneyCfg[nLevel] = TimesMap;
		TimesMap.clear();
	}
	else if ( nType == QT_EXP )
	{
		m_QiFuExpCfg[nLevel] = TimesMap;
		TimesMap.clear();
	}
}

QiFuCfg* CQiFuTable::GetQiFuCfg( int8_t QiFuType, int32_t nLevel, int8_t QiFuTimes )
{
	int32_t Level = nLevel / 10 * 10;
	if ( QiFuType == QT_MONEY )
	{
		QiFuCfgMap::iterator it = m_QiFuMoneyCfg.find( Level );
		if ( it != m_QiFuMoneyCfg.end() )
		{
			QiFuTimesMap::iterator itTmp = it->second.find( QiFuTimes );
			if ( itTmp != it->second.end() )
			{
				return &(itTmp->second);
			}
		}
	}
	else if ( QiFuType == QT_EXP )
	{
		QiFuCfgMap::iterator it = m_QiFuExpCfg.find( Level );
		if ( it != m_QiFuExpCfg.end() )
		{
			QiFuTimesMap::iterator itTmp = it->second.find( QiFuTimes );
			if ( itTmp != it->second.end() )
			{
				return &(itTmp->second);
			}
		}
	}
	return NULL;
	
}

VipTable::VipTable()
{
	m_VipCfgMap.clear();
}

void VipTable::InitVipTable()
{
	CDBCFile VipTable(0);
	bool ret = VipTable.OpenFromTXT(FILE_VIP_TABLE);
	if ( ret == false )
	{
		LOG_ERROR("open FILE_VIP_TABLE failed,please check!!");
		return;
	}

	int32_t iBaseTableCount		=	VipTable.GetRecordsNum();
	int32_t iBaseColumnCount	=	VipTable.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	m_VipCfgMap.clear();
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		VipCfg		stu = {};
		stu.VipLevel			= (int8_t)VipTable.Search_Posistion(i,0)->iValue;
		stu.QiFuMoneyTimes		= (int8_t)VipTable.Search_Posistion(i,1)->iValue;
		stu.QiFuExpTimes		= (int8_t)VipTable.Search_Posistion(i,2)->iValue;
		stu.Retroactive			= (int8_t)VipTable.Search_Posistion(i,3)->iValue;
		stu.NeedVipExp			= VipTable.Search_Posistion(i,4)->iValue;
		stu.ExpRate				= VipTable.Search_Posistion(i,5)->iValue;
		stu.OpenBag				= VipTable.Search_Posistion(i,6)->iValue;
		stu.DailyTaskTimes		= VipTable.Search_Posistion(i,7)->iValue;
		stu.Item				= CItemHelper::parseItemString(stu.VipLevel, VipTable.Search_Posistion(i,8)->pString );
		stu.PetDeport			= VipTable.Search_Posistion(i,9)->iValue;
		string AtttString		= VipTable.Search_Posistion(i,10)->pString;
		stu.FamilyLightAddRate	= VipTable.Search_Posistion(i,11)->iValue;
		stu.HallOfFameBuyTimes	= VipTable.Search_Posistion(i,12)->iValue;
		stu.SiteRevive			= VipTable.Search_Posistion(i,13)->iValue;
		StringVector Attts = StringUtility::split(AtttString, "|");
		for ( StringVector::iterator it = Attts.begin();it != Attts.end();++it )
		{
			StringVector vstack = StringUtility::split( *it, ":" );
			if ( vstack.size() == 2 )
			{
				AttrAddon attr = {};
				attr.index	 = atoi( vstack[0].c_str() );
				attr.addon	 = atoi( vstack[1].c_str() );
				stu.AtttVector.push_back( attr );
			}
		}
		m_VipCfgMap[stu.VipLevel] = stu;
	}
}

VipCfg* VipTable::GetVipCfg( int8_t VipLevel )
{
	VipCfgMap::iterator it = m_VipCfgMap.find(VipLevel);
	if ( it != m_VipCfgMap.end() )
	{
		return &(it->second);
	}
	return NULL;
}

int8_t VipTable::GetVipLevel( int32_t VipExp )
{
	if ( VipExp <= 0 )
	{
		return 0;
	}
	int8_t	VipLevel = 0;
	int32_t NeedVipExp = 0;
	VipCfgMap::iterator it = m_VipCfgMap.begin();
	for ( ; it != m_VipCfgMap.end(); ++it )
	{
		NeedVipExp += it->second.NeedVipExp;
		if (  NeedVipExp > VipExp )
		{
			VipLevel = it->first - 1;
			break;
		}
		else if ( it->first == MAX_VIP_LEVEL )
		{
			return MAX_VIP_LEVEL;
		}
	}
	return VipLevel;
}// Auto-generated stub implementations for missing CfgData Init* methods
#include "stdafx.h"
#include "CfgData.h"


void CfgData::Init360RewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GameLobby.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GameLobby.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GameLobby.txt
    }
}

void CfgData::Init360RewardTypeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GameLobbyType.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GameLobbyType.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GameLobbyType.txt
    }
}

void CfgData::InitActDropTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/shoujihuodong.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/shoujihuodong.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/shoujihuodong.txt
    }
}

void CfgData::InitActiveSkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_skill_info.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/cfg_skill_info.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/cfg_skill_info.txt
    }
}

void CfgData::InitAdultGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShenFenYanZheng.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShenFenYanZheng.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShenFenYanZheng.txt
    }
}

void CfgData::InitAttrBattleTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AttrBattle.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AttrBattle.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AttrBattle.txt
    }
}

void CfgData::InitBFZLEnterCostTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BingFengZouLang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BingFengZouLang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BingFengZouLang.txt
    }
}

void CfgData::InitBaoKuFuBen()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BaoKuFuBen.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BaoKuFuBen.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BaoKuFuBen.txt
    }
}

void CfgData::InitBeastShrineEnterCostTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AnimalMapCost.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AnimalMapCost.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AnimalMapCost.txt
    }
}

void CfgData::InitBlacketMarketTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlackMarket.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlackMarket.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        int32_t nDays = TabFile.GetInt(i, 0);
        int32_t nIndex = TabFile.GetInt(i, 1);

        // Parse 3 job-specific item strings
        std::string itemsStr[3] = {
            TabFile.GetString(i, 2),
            TabFile.GetString(i, 3),
            TabFile.GetString(i, 4)
        };

        int32_t nOldPrice = TabFile.GetInt(i, 5);
        int32_t nPrice = TabFile.GetInt(i, 6);
        int32_t nBroadcast = TabFile.GetInt(i, 7);

        for (int32_t job = 0; job < 3; ++job)
        {
            CfgBlackMarketGoods goods;
            goods.nDays = nDays;
            goods.nIndex = nIndex;
            goods.nOldPrice = nOldPrice;
            goods.nPrice = nPrice;
            goods.nBroadcast = nBroadcast;

            // Parse item string: itemId:itemClass:itemCount:bind
            if (!itemsStr[job].empty())
            {
                std::vector<std::string> parts = StringUtility::split(itemsStr[job], ':');
                if (parts.size() >= 3)
                {
                    goods.item.itemId = StringUtility::toInt(parts[0]);
                    goods.item.itemClass = (int8_t)StringUtility::toInt(parts[1]);
                    goods.item.itemCount = StringUtility::toInt(parts[2]);
                    if (parts.size() >= 4)
                    {
                        // bind flag - unused but available
                    }
                }
            }

            m_BlacketMarketTable.AddGoods(nDays, nIndex, job, goods);
        }
    }
}

void CfgData::InitBlueDailyRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueEverydayReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlueEverydayReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlueEverydayReward.txt
    }
}

void CfgData::InitBlueLevelRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueLevelReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlueLevelReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlueLevelReward.txt
    }
}

void CfgData::InitBlueRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BlueReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BlueReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BlueReward.txt
    }
}

void CfgData::InitBossDistribution()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MonsterRefreshInMaps.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MonsterRefreshInMaps.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MonsterRefreshInMaps.txt
    }
}

void CfgData::InitBossFirstKilledTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/BossKill.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/BossKill.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/BossKill.txt
    }
}

void CfgData::InitBossKilledReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GoldReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GoldReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GoldReward.txt
    }
}

void CfgData::InitLevelRefiningTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LvRefining.txt");
	if ( ret == false )
	{
		LOG_ERROR("open ./ServerConfig/Tables/LvRefining.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	for ( int32_t i = 0; i < iBaseTableCount; ++i )
	{
		LevelRefinCfg stu;
		stu.LV				= TabFile.GetInt( i, "LV", 0 );
		stu.nLimit			= TabFile.GetInt( i, "limit", 0 );
		stu.nGongGaoId		= TabFile.GetInt( i, "Notice", 0 );

		std::string sGold = TabFile.GetString( i, "Gold", "" );
		StringVector vGold;
		Answer::StringUtility::split( &vGold, sGold, "|", 0 );
		for ( size_t j = 0; j < vGold.size(); ++j )
		{
			stu.vNeedGold.push_back( atoi( vGold[j].c_str() ) );
		}

		std::string sLvUp = TabFile.GetString( i, "LvUp", "" );
		StringVector vLvUp;
		Answer::StringUtility::split( &vLvUp, sLvUp, "|", 0 );
		for ( size_t j = 0; j < vLvUp.size(); ++j )
		{
			stu.nLevelUp.push_back( atoi( vLvUp[j].c_str() ) );
		}

		m_RefiningTable[stu.LV] = stu;
	}
}

LevelRefinCfg* CfgData::GetRefining( int32_t nLevel )
{
	LevelRefinCfgMap::iterator it = m_RefiningTable.find( nLevel );
	if ( it != m_RefiningTable.end() )
	{
		return &it->second;
	}
	return NULL;
}

LevelRefinCfgMap& CfgData::GetRefiningTable()
{
	return m_RefiningTable;
}

void CfgData::InitBuyGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TimeLimit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TimeLimit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TimeLimit.txt
    }
}

void CfgData::InitCachetCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Cachet.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Cachet.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Cachet.txt
    }
}

void CfgData::InitCampWarContKillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/CampWarContKill.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/CampWarContKill.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/CampWarContKill.txt
    }
}

void CfgData::InitCampWarRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/CampWarReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/CampWarReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/CampWarReward.txt
    }
}

void CfgData::InitCarrierAttrTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Carrier_attr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Carrier_attr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Carrier_attr.txt
    }
}

void CfgData::InitCarrierTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Carrier.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Carrier.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Carrier.txt
    }
}

void CfgData::InitChargeDungeon()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/charge_dungeon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/charge_dungeon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/charge_dungeon.txt
    }
}

void CfgData::InitChouJiangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TreasureBase.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TreasureBase.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TreasureBase.txt
    }
}

void CfgData::InitChristmasDuiHuanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Christmas.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Christmas.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Christmas.txt
    }
}

void CfgData::InitCityWarContRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GongChengZhanJiangLi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GongChengZhanJiangLi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GongChengZhanJiangLi.txt
    }
}

void CfgData::InitCrossTowerCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/KuaFuMap.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/KuaFuMap.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/KuaFuMap.txt
    }
}

void CfgData::InitCycleTowerTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LunHuiEvent.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LunHuiEvent.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LunHuiEvent.txt
    }
}

void CfgData::InitDaZheQuanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ItemDiscount.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ItemDiscount.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ItemDiscount.txt
    }
}

void CfgData::InitDamnationTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Curse.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Curse.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Curse.txt
    }
}

void CfgData::InitDiligenceCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QinFen.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QinFen.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QinFen.txt
    }
}

void CfgData::InitDrawTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Draw.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Draw.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Draw.txt
    }
}

void CfgData::InitDropRecordTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/DropRecord.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/DropRecord.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/DropRecord.txt
    }
}

void CfgData::InitDuiHuanLimitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ExchangeShengYaoBi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ExchangeShengYaoBi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ExchangeShengYaoBi.txt
    }
}

void CfgData::InitDungeonScoreTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/DungeonScore.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/DungeonScore.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/DungeonScore.txt
    }
}

void CfgData::InitDungeonSummon()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_dungeon_summon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/cfg_dungeon_summon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/cfg_dungeon_summon.txt
    }
}

void CfgData::InitEquipBackTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipRecovery.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipRecovery.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipRecovery.txt
    }
}

void CfgData::InitEquipBackTask()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TaskRecovery.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TaskRecovery.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TaskRecovery.txt
    }
}

void CfgData::InitEquipBlessTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LuckyValue.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LuckyValue.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LuckyValue.txt
    }
}

void CfgData::InitEquipBoxTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_item_gift_equip.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/cfg_item_gift_equip.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/cfg_item_gift_equip.txt
    }
}

void CfgData::InitEquipDecomposeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipDecompose.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipDecompose.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipDecompose.txt
    }
}

void CfgData::InitEquipPosSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipPosSuit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipPosSuit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipPosSuit.txt
    }
}

void CfgData::InitEquipUpPhase()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/EquipUpPhase.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/EquipUpPhase.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/EquipUpPhase.txt
    }
}

void CfgData::InitExchangeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/JiZiDuiJiang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/JiZiDuiJiang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/JiZiDuiJiang.txt
    }
}

void CfgData::InitFamilyDonateTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilyDonate.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilyDonate.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilyDonate.txt
    }
}

void CfgData::InitFamilyDungeonTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilyDungeon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilyDungeon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilyDungeon.txt
    }
}

void CfgData::InitFamilyMedalTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilyBadge.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilyBadge.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilyBadge.txt
    }
}

void CfgData::InitFamilySkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FamilySkill.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FamilySkill.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FamilySkill.txt
    }
}

void CfgData::InitFlopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/FlopActivity.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/FlopActivity.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/FlopActivity.txt
    }
}

void CfgData::InitFunctionOpenMailMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MailGuide.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MailGuide.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MailGuide.txt
    }
}

void CfgData::InitGemOpenHoleTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GemOpenHole.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GemOpenHole.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GemOpenHole.txt
    }
}

void CfgData::InitGemSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GemSuit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GemSuit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GemSuit.txt
    }
}

void CfgData::InitGoblinData()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Goblin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Goblin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Goblin.txt
    }
}

void CfgData::InitGoblinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GoblinUp.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GoblinUp.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GoblinUp.txt
    }
}

void CfgData::InitGoldEggTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ItemGoldEggOpen.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ItemGoldEggOpen.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ItemGoldEggOpen.txt
    }
}

void CfgData::InitGongMinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GongMing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GongMing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GongMing.txt
    }
}

void CfgData::InitGroupIconTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GroupIcon.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GroupIcon.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GroupIcon.txt
    }
}

void CfgData::InitGroupMonster()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/RegionRefresh.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/RegionRefresh.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/RegionRefresh.txt
    }
}

void CfgData::InitGuWuCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GuWu.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GuWu.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GuWu.txt
    }
}

void CfgData::InitGuardPrivilegeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GuardPrivilegeReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GuardPrivilegeReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        CfgGuardPrivilege item;
        item.nIndex = (int8_t)TabFile.GetData(i, 0);
        item.nType = (int8_t)TabFile.GetData(i, 1);
        item.nDaily = (int8_t)TabFile.GetData(i, 2);
        item.nParam = TabFile.GetData(i, 3);
        std::string strReward = TabFile.GetStringData(i, 4);
        CItemHelper::parseItemVectorString(item.vReward, strReward);
        m_GuardPrivilegeMap[item.nIndex] = item;
        // Parse start/end time from first record only
        if (i == 0)
        {
            std::string startStr = TabFile.GetStringData(i, 5);
            std::string endStr = TabFile.GetStringData(i, 6);
            // Simple time parsing: assume format "YYYY-MM-DD HH:MM:SS"
            struct tm tmStart = {}, tmEnd = {};
            strptime(startStr.c_str(), "%Y-%m-%d %H:%M:%S", &tmStart);
            strptime(endStr.c_str(), "%Y-%m-%d %H:%M:%S", &tmEnd);
            m_nGuardPrivilegeStartTime = (int32_t)mktime(&tmStart);
            m_nGuardPrivilegeEndTime = (int32_t)mktime(&tmEnd);
        }
    }
}

void CfgData::InitGuiGuDaoRenTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TaoistTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TaoistTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TaoistTask.txt
    }
}

void CfgData::InitHoeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Hoe.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Hoe.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Hoe.txt
    }
}

void CfgData::InitJewelPavilionTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TreasureShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TreasureShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TreasureShop.txt
    }
}

void CfgData::InitJueWeiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/JueWei.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/JueWei.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/JueWei.txt
    }
}

void CfgData::InitLaDaShiHuiYuan()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LuDaShiHuiYuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LuDaShiHuiYuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LuDaShiHuiYuan.txt
    }
}

void CfgData::InitLevelChatTimesTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PublicChatTimes.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PublicChatTimes.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PublicChatTimes.txt
    }
}

void CfgData::InitLevelRefiningTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LvRefining.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LvRefining.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LvRefining.txt
    }
}

void CfgData::InitLibraryTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ChestItemRandom.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ChestItemRandom.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ChestItemRandom.txt
    }
}

void CfgData::InitLimitTimeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LimitTime.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LimitTime.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LimitTime.txt
    }
}

void CfgData::InitLittleHelperCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LittleHelper.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LittleHelper.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LittleHelper.txt
    }
}

void CfgData::InitLuckDropTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/LuckyRate.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/LuckyRate.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/LuckyRate.txt
    }
}

void CfgData::InitMYSJRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MoYuShiJieReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MoYuShiJieReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MoYuShiJieReward.txt
    }
}

void CfgData::InitMaintainCompensateTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MaintainCompensate.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MaintainCompensate.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MaintainCompensate.txt
    }
}

void CfgData::InitMapRoadTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MapRoad.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MapRoad.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MapRoad.txt
    }
}

void CfgData::InitMingGeTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MingGe.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MingGe.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MingGe.txt
    }
}

void CfgData::InitMiniClientMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WeiDuanDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WeiDuanDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WeiDuanDaTing.txt
    }
}

void CfgData::InitMiniClientTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WeiDuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WeiDuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WeiDuan.txt
    }
}

void CfgData::InitMobilePhoneGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShouJi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShouJi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShouJi.txt
    }
}

void CfgData::InitMonsterAddAttrTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MonstAddAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MonstAddAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MonstAddAttr.txt
    }
}

void CfgData::InitMonsterRandTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MonsterRand.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MonsterRand.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MonsterRand.txt
    }
}

void CfgData::InitMonthlyChouJiangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TurntableReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TurntableReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TurntableReward.txt
    }
}

void CfgData::InitMysteryGiftTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MysteriousGift.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MysteriousGift.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MysteriousGift.txt
    }
}

void CfgData::InitMysteryShopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MysteriousShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MysteriousShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MysteriousShop.txt
    }
}

void CfgData::InitNationalDayTask()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PassportTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PassportTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PassportTask.txt
    }
}

void CfgData::InitOutLinkFestivalTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/OutLinkFestival.txt");
    if (ret == false)
    {
        LOG_ERROR( "open ./ServerConfig/Tables/OutLinkFestival.txt failed, please check!!!" );
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        CfgOutLinkFestival stu = {};
        int32_t nIndex = 0;
        stu.nIndex       = TabFile.Search_Posistion(i, nIndex)->iValue; ++nIndex;
        stu.nStartTime   = Answer::DayTime::StringToIntTime( TabFile.Search_Posistion(i, nIndex)->pString ); ++nIndex;
        stu.nEndTime     = Answer::DayTime::StringToIntTime( TabFile.Search_Posistion(i, nIndex)->pString ); ++nIndex;
        stu.nIcon        = TabFile.Search_Posistion(i, nIndex)->iValue; ++nIndex;
        stu.strPlatform  = TabFile.Search_Posistion(i, nIndex)->pString; ++nIndex;
        m_OutLinkFestivalTable.Add( stu );
    }
}

const CfgOutLinkFestivalTable* CfgData::GetOutLinkFestivalTable()
{
    return &m_OutLinkFestivalTable;
}

void CfgData::InitPassiveSkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillPassiveAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillPassiveAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillPassiveAttr.txt
    }
}

void CfgData::InitPetAttrTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PetAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PetAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PetAttr.txt
    }
}

void CfgData::InitPetUpStarTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/PetUpStar.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/PetUpStar.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/PetUpStar.txt
    }
}

void CfgData::InitPlatformDaTingMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/DaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/DaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/DaTing.txt
    }
}

void CfgData::InitPlatformReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Reward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Reward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Reward.txt
    }
}

void CfgData::InitPlatformVipMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/OutLinkVip.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/OutLinkVip.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/OutLinkVip.txt
    }
}

void CfgData::InitQQGameRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QQGameDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QQGameDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QQGameDaTing.txt
    }
}

void CfgData::InitQQZoneRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QQZone.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QQZone.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QQZone.txt
    }
}

void CfgData::InitRefreshMonsterCfgListMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ActivityServer.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ActivityServer.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ActivityServer.txt
    }
}

void CfgData::InitRongHeCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ItemMix.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ItemMix.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ItemMix.txt
    }
}

void CfgData::InitScoreShopTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ScoreShop.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ScoreShop.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ScoreShop.txt
    }
}

void CfgData::InitSelectItemCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/GiftChoose.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/GiftChoose.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/GiftChoose.txt
    }
}

void CfgData::InitShangRenCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MagicBusiness.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MagicBusiness.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MagicBusiness.txt
    }
}

void CfgData::InitShenWeiTaskTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShenWeiTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShenWeiTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShenWeiTask.txt
    }
}

void CfgData::InitShenYaoPosSuitTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShengZhuangSuit.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShengZhuangSuit.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShengZhuangSuit.txt
    }
}

void CfgData::InitShenYaoPosTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShengZhuangAttr.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShengZhuangAttr.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShengZhuangAttr.txt
    }
}

void CfgData::InitShiZhuLevelUp()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuangUpGrade.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShiZhuangUpGrade.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShiZhuangUpGrade.txt
    }
}

void CfgData::InitShiZhuangLevelTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuangLevel.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShiZhuangLevel.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShiZhuangLevel.txt
    }
}

void CfgData::InitShiZhuangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShiZhuang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShiZhuang.txt
    }
}

void CfgData::InitShouHuRefining()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/StarSpaceLevel.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/StarSpaceLevel.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/StarSpaceLevel.txt
    }
}

void CfgData::InitSevenTaskTable()
{
    // Parse SevenTask tasks
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SevenDayGod.txt");
    if (ret == false)
    {
        LOG_ERROR( "open ./ServerConfig/Tables/SevenDayGod.txt failed, please check!!!" );
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        SevenTaskCfg cfg = {};
        int32_t nIdx = 0;
        cfg.nIndex       = TabFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        cfg.nType        = TabFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        cfg.nCondition   = TabFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        // Award format: itemId:itemClass:count:bind
        std::string awardStr = TabFile.Search_Posistion(i, nIdx)->pString; ++nIdx;
        CfgData::parasItemData( cfg.Item, awardStr );
        cfg.nStartDay    = TabFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        cfg.nEndDay      = TabFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        ++nIdx; // skip Desc
        m_SevenTaskTable.AddTaskCfg( cfg );
    }

    // Parse SevenTask sum rewards
    CDBCFile SumFile(0);
    ret = SumFile.OpenFromTXT("./ServerConfig/Tables/SevenTaskSumReward.txt");
    if (ret == false)
    {
        LOG_ERROR( "open ./ServerConfig/Tables/SevenTaskSumReward.txt failed, please check!!!" );
        return;
    }

    iBaseTableCount = SumFile.GetRecordsNum();
    iBaseColumnCount = SumFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        SevenTaskSumReward cfg = {};
        int32_t nIdx = 0;
        cfg.nIndex         = SumFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        cfg.nFinishCount   = SumFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        std::string awardStr = SumFile.Search_Posistion(i, nIdx)->pString; ++nIdx;
        CfgData::parasItemData( cfg.Item, awardStr );
        cfg.nGongGaoId     = SumFile.Search_Posistion(i, nIdx)->iValue; ++nIdx;
        m_SevenTaskTable.AddSumReward( cfg );
    }
}

const SevenTaskTable* CfgData::GetSevenTaskTable()
{
    return &m_SevenTaskTable;
}

void CfgData::InitShunWangTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ShunWangHuiYuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ShunWangHuiYuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/ShunWangHuiYuan.txt
    }
}

void CfgData::InitSouGouDaTing()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SouGouDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SouGouDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SouGouDaTing.txt
    }
}

void CfgData::InitSouGouSkinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SogouSkin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SogouSkin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SogouSkin.txt
    }
}

void CfgData::InitSpeciaEquipCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialEquip.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialEquip.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        SpeciaEquipCfg cfg;
        cfg.nId = TabFile.GetInt(i, 0);
        // nName is skipped (string, index 1)
        // Parse AddAttr string (index 2) - format: "type:value|type:value|..."
        std::string attrStr = TabFile.GetString(i, 2);
        if (!attrStr.empty())
        {
            std::vector<std::string> attrPairs = StringUtility::split(attrStr, '|');
            for (size_t ai = 0; ai < attrPairs.size(); ++ai)
            {
                std::vector<std::string> parts = StringUtility::split(attrPairs[ai], ':');
                if (parts.size() >= 2)
                {
                    AddAttribute attr;
                    attr.m_nAddAttrType = (uint8_t)StringUtility::toInt(parts[0]);
                    attr.m_nAddAttrValue = StringUtility::toInt(parts[1]);
                    cfg.lAttrList.push_back(attr);
                }
            }
        }
        cfg.nNeedVipLevel = TabFile.GetInt(i, 3);
        cfg.nContinueLogin = TabFile.GetInt(i, 4);
        cfg.nNeedGold = TabFile.GetInt(i, 5);
        // AddAttr2 (index 6) is skipped
        cfg.nGongGaoId = TabFile.GetInt(i, 7);
        cfg.nDisplayID = TabFile.GetInt(i, 8);
        // SkillDesc (index 9) is skipped
        cfg.nTalentId = TabFile.GetInt(i, 10);
        // SkillIcon (index 11) is skipped
        cfg.nBuyLimitVipLevel = TabFile.GetInt(i, 12);
        m_SpeciaEquipCfgMap[cfg.nId] = cfg;
    }
}

void CfgData::InitSpeciaSkillDistanceTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillSpecialDamage.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillSpecialDamage.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillSpecialDamage.txt
    }
}

void CfgData::InitSpecialBossMapCfgMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MapConsume.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MapConsume.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MapConsume.txt
    }
}

void CfgData::InitSpecialMap()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialMap.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialMap.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialMap.txt
    }
}

void CfgData::InitSpecialMonster()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialMonster.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialMonster.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialMonster.txt
    }
}

void CfgData::InitSpecialTreasureMapRandTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialTreasureMap.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SpecialTreasureMap.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SpecialTreasureMap.txt
    }
}

void CfgData::InitSpeed360Reward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Speed360Reward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Speed360Reward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Speed360Reward.txt
    }
}

void CfgData::InitStrengthenTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MieShenRongLian.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/MieShenRongLian.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/MieShenRongLian.txt
    }
}

void CfgData::InitSuperMemberTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SuperMember.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SuperMember.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SuperMember.txt
    }
}

void CfgData::InitSuperTeHuiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SuperDiscount.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SuperDiscount.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SuperDiscount.txt
    }
}

void CfgData::InitSystemOpenReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/System.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/System.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/System.txt
    }
}

void CfgData::InitTGPDailyRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPEverydayReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TGPEverydayReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TGPEverydayReward.txt
    }
}

void CfgData::InitTGPLevelRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPLevelReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TGPLevelReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TGPLevelReward.txt
    }
}

void CfgData::InitTGPRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TGPReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TGPReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TGPReward.txt
    }
}

void CfgData::InitTalentActiveTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillActive.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillActive.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillActive.txt
    }
}

void CfgData::InitTalentPageTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillTree.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillTree.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillTree.txt
    }
}

void CfgData::InitTalentTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillTalent.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillTalent.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillTalent.txt
    }
}

void CfgData::InitTaskCycleRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TaskCycleReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TaskCycleReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TaskCycleReward.txt
    }
}

void CfgData::InitTencentSevenDayLoginTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TencentSevenDayLogin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TencentSevenDayLogin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TencentSevenDayLogin.txt
    }
}

void CfgData::InitTestServerReward()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TestActivity.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TestActivity.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TestActivity.txt
    }
}


void CfgData::InitTianLingTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TianLing.txt");
	if (ret == false)
	{
		LOG_ERROR("open ./ServerConfig/Tables/TianLing.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		TianLingCfg cfg;
		int32_t nLevel = TabFile.GetInt(i, 0);		// Level
		cfg.CostMoney = TabFile.GetInt(i, 1);		// Gold
		cfg.CostCoin = TabFile.GetInt(i, 9);		// Coin
		cfg.GongGaoId = TabFile.GetInt(i, 4);		// NoticeID

		// Res -> CostItems
		std::string sRes = TabFile.GetString(i, 2);
		if (sRes != "-1" && !sRes.empty())
		{
			StringVector vec = Answer::StringUtility::split(sRes, ":");
			if (vec.size() >= 3)
			{
				ItemData item;
				item.m_nId = Answer::StringUtility::toInt(vec[0]);
				item.m_nClass = (int8_t)Answer::StringUtility::toInt(vec[1]);
				item.m_nCount = Answer::StringUtility::toInt(vec[2]);
				cfg.CostItems.push_back(item);
			}
		}

		// Attr -> AttrList
		std::string sAttr = TabFile.GetString(i, 3);
		if (!sAttr.empty() && sAttr != "-1")
		{
			StringVector pairs = Answer::StringUtility::split(sAttr, "|");
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				StringVector kv = Answer::StringUtility::split(pairs[j], ":");
				if (kv.size() >= 2)
				{
					AddAttribute attr;
					attr.m_nAddAttrType = Answer::StringUtility::toInt(kv[0]);
					attr.m_nAddAttrValue = Answer::StringUtility::toInt(kv[1]);
					cfg.AttrList.push_back(attr);
				}
			}
		}

		m_TianLingCfgMap[nLevel] = cfg;
	}
}

void CfgData::InitZhanHunTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ZhanHun.txt");
	if (ret == false)
	{
		LOG_ERROR("open ./ServerConfig/Tables/ZhanHun.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		ZhanHunCfg cfg;
		int32_t nLevel = TabFile.GetInt(i, 0);		// Level
		cfg.nMoney = TabFile.GetInt(i, 1);			// Money
		cfg.nSyb = TabFile.GetInt(i, 2);			// Syb
		cfg.nGongGaoId = TabFile.GetInt(i, 7);		// NoticeID

		// Attr -> lAddAttrs
		std::string sAttr = TabFile.GetString(i, 3);
		if (!sAttr.empty() && sAttr != "-1")
		{
			StringVector pairs = Answer::StringUtility::split(sAttr, "|");
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				StringVector kv = Answer::StringUtility::split(pairs[j], ":");
				if (kv.size() >= 2)
				{
					AddAttribute attr;
					attr.m_nAddAttrType = Answer::StringUtility::toInt(kv[0]);
					attr.m_nAddAttrValue = Answer::StringUtility::toInt(kv[1]);
					cfg.lAddAttrs.push_back(attr);
				}
			}
		}

		m_ZhanHunCfgMap[nLevel] = cfg;
	}
}

void CfgData::InitSunAndMoonTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SunAndMoon.txt");
	if (ret == false)
	{
		LOG_ERROR("open ./ServerConfig/Tables/SunAndMoon.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		SunAndMoonCfg cfg;
		int32_t nLevel = TabFile.GetInt(i, 0);			// Level
		std::string sCostItem = TabFile.GetString(i, 1);	// CostItem
		std::string sAttrStr = TabFile.GetString(i, 2);	// AttrStr
		cfg.nGetItemTimes = TabFile.GetInt(i, 3);		// AbsorbCount
		cfg.nSunTelentId = TabFile.GetInt(i, 4);		// SunTelentId
		cfg.nSunTelentLevel = TabFile.GetInt(i, 5);		// SunSkillLevel
		cfg.nMoonTelentId = TabFile.GetInt(i, 6);		// MoonTelentId
		cfg.nMoonTelentLevel = TabFile.GetInt(i, 7);	// MoonSkillLevel
		cfg.nGongGaoId = TabFile.GetInt(i, 9);			// Notice

		// CostItem -> lConstItems
		if (!sCostItem.empty() && sCostItem != "-1")
		{
			StringVector vec = Answer::StringUtility::split(sCostItem, ":");
			if (vec.size() >= 3)
			{
				ItemData item;
				item.m_nId = Answer::StringUtility::toInt(vec[0]);
				item.m_nClass = (int8_t)Answer::StringUtility::toInt(vec[1]);
				item.m_nCount = Answer::StringUtility::toInt(vec[2]);
				cfg.lConstItems.push_back(item);
			}
		}

		// AttrStr -> lAttr
		if (!sAttrStr.empty() && sAttrStr != "-1")
		{
			StringVector pairs = Answer::StringUtility::split(sAttrStr, "|");
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				StringVector kv = Answer::StringUtility::split(pairs[j], ":");
				if (kv.size() >= 2)
				{
					AddAttribute attr;
					attr.m_nAddAttrType = Answer::StringUtility::toInt(kv[0]);
					attr.m_nAddAttrValue = Answer::StringUtility::toInt(kv[1]);
					cfg.lAttr.push_back(attr);
				}
			}
		}

		m_SunAndMoonCfgMap[nLevel] = cfg;
	}
}

const TianLingCfg* CfgData::GetTianLingCfg( int32_t nLevel )
{
	TianLingCfgMap::const_iterator iter = m_TianLingCfgMap.find( nLevel );
	if ( iter != m_TianLingCfgMap.end() )
	{
		return &iter->second;
	}
	return NULL;
}

const TianLingCfgMap& CfgData::GetTianLingCfgMap()
{
	return m_TianLingCfgMap;
}

const ZhanHunCfg* CfgData::GetZhanHunCfg( int32_t nLevel )
{
	ZhanHunCfgMap::const_iterator iter = m_ZhanHunCfgMap.find( nLevel );
	if ( iter != m_ZhanHunCfgMap.end() )
	{
		return &iter->second;
	}
	return NULL;
}

const ZhanHunCfgMap& CfgData::GetZhanHunCfgMap()
{
	return m_ZhanHunCfgMap;
}

const SunAndMoonCfg* CfgData::GetSunAndMoonCfg( int32_t nLevel )
{
	SunAndMoonCfgMap::const_iterator iter = m_SunAndMoonCfgMap.find( nLevel );
	if ( iter != m_SunAndMoonCfgMap.end() )
	{
		return &iter->second;
	}
	return NULL;
}

const SunAndMoonCfgMap& CfgData::GetSunAndMoonCfgMap()
{
	return m_SunAndMoonCfgMap;
}


void CfgData::InitTitleTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/Title.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/Title.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/Title.txt
    }
}

void CfgData::InitTongTianChiRanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/tongtianpaihang.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/tongtianpaihang.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/tongtianpaihang.txt
    }
}

void CfgData::InitTouZiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/QiRiTouZi.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/QiRiTouZi.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/QiRiTouZi.txt
    }
}

void CfgData::InitTreasureMapTabale()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/TreasureMapBase.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/TreasureMapBase.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/TreasureMapBase.txt
    }
}

void CfgData::InitTrigSkillTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/SkillTrig.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/SkillTrig.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/SkillTrig.txt
    }
}

void CfgData::InitUltimateChallengeCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/limitChallenge.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/limitChallenge.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/limitChallenge.txt
    }
}

void CfgData::InitVplanTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/VplanReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/VplanReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/VplanReward.txt
    }
}

void CfgData::InitWeiXinTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WeiXin.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WeiXin.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WeiXin.txt
    }
}

void CfgData::InitWingCfgTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AttributeWing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AttributeWing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AttributeWing.txt
    }
}

void CfgData::InitWingEquipPolish()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WingEquipPolish.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WingEquipPolish.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WingEquipPolish.txt
    }
}

void CfgData::InitWishRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WishReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/WishReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/WishReward.txt
    }
}

void CfgData::InitWuHunCreateTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WuHunMake.txt");
	if (ret == false)
	{
		LOG_ERROR("open ./ServerConfig/Tables/WuHunMake.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CreateWuHun stu;
		TabFile.GetRecordData(i);
		stu.nId = TabFile.GetIntValue(0, 0);
		stu.nLv = TabFile.GetIntValue(1, 0);
		stu.nType = TabFile.GetIntValue(2, 0);

		std::string strNeedItem = TabFile.GetStringValue(3, "");
		if (!strNeedItem.empty() && strNeedItem != "-1")
		{
			StringVector items = Answer::StringUtility::split(strNeedItem, "|");
			for (StringVector::iterator it = items.begin(); it != items.end(); ++it)
			{
				RateItem rate;
				StringVector tv = Answer::StringUtility::split(*it, ":");
				if (tv.size() >= 3)
				{
					rate.nItemId = atoi(tv[0].c_str());
					rate.nItemClass = (int8_t)atoi(tv[1].c_str());
					rate.nItemCount = atoi(tv[2].c_str());
					rate.nRate = 10000;
					stu.ConstItem.push_back(rate);
				}
			}
		}

		std::string strGainItem = TabFile.GetStringValue(4, "");
		if (!strGainItem.empty() && strGainItem != "-1")
		{
			StringVector items = Answer::StringUtility::split(strGainItem, "|");
			int32_t nTotalRate = 0;
			for (StringVector::iterator it = items.begin(); it != items.end(); ++it)
			{
				RateItem rate;
				StringVector tv = Answer::StringUtility::split(*it, ":");
				if (tv.size() >= 3)
				{
					rate.nItemId = atoi(tv[0].c_str());
					rate.nItemClass = (int8_t)atoi(tv[1].c_str());
					rate.nItemCount = atoi(tv[2].c_str());
					if (tv.size() >= 5)
					{
						rate.nRate = atoi(tv[4].c_str());
						rate.nBind = (int8_t)atoi(tv[3].c_str());
						if (tv.size() >= 6)
						{
							rate.nGongGaoId = atoi(tv[5].c_str());
						}
					}
					nTotalRate += rate.nRate;
					rate.nRate = nTotalRate;
					stu.GetItemRate.push_back(rate);
				}
			}
		}

		stu.nNpcID = TabFile.GetIntValue(5, 0);
		stu.nWuHunID = TabFile.GetIntValue(6, 0);

		std::string strNeedItem1 = TabFile.GetStringValue(8, "");
		if (!strNeedItem1.empty() && strNeedItem1 != "-1")
		{
			StringVector items = Answer::StringUtility::split(strNeedItem1, "|");
			for (StringVector::iterator it = items.begin(); it != items.end(); ++it)
			{
				RateItem rate;
				StringVector tv = Answer::StringUtility::split(*it, ":");
				if (tv.size() >= 3)
				{
					rate.nItemId = atoi(tv[0].c_str());
					rate.nItemClass = (int8_t)atoi(tv[1].c_str());
					rate.nItemCount = atoi(tv[2].c_str());
					if (tv.size() >= 4)
					{
						rate.nRate = atoi(tv[3].c_str());
					}
					stu.SpecialCost.m_nId = rate.nItemId;
					stu.SpecialCost.m_nClass = rate.nItemClass;
					stu.SpecialCost.m_nCount = rate.nItemCount;
				}
			}
		}

		std::string strGainItem1 = TabFile.GetStringValue(9, "");
		if (!strGainItem1.empty() && strGainItem1 != "-1")
		{
			StringVector items = Answer::StringUtility::split(strGainItem1, "|");
			int32_t nTotalRate = 0;
			for (StringVector::iterator it = items.begin(); it != items.end(); ++it)
			{
				RateItem rate;
				StringVector tv = Answer::StringUtility::split(*it, ":");
				if (tv.size() >= 3)
				{
					rate.nItemId = atoi(tv[0].c_str());
					rate.nItemClass = (int8_t)atoi(tv[1].c_str());
					rate.nItemCount = atoi(tv[2].c_str());
					if (tv.size() >= 5)
					{
						rate.nRate = atoi(tv[4].c_str());
						rate.nBind = (int8_t)atoi(tv[3].c_str());
					}
					nTotalRate += rate.nRate;
					rate.nRate = nTotalRate;
					stu.GetItemRate2.push_back(rate);
				}
			}
		}

		m_CreateWuHunMap[stu.nId] = stu;
	}
}

void CfgData::InitWuHunItemTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/WuHun.txt");
	if (ret == false)
	{
		LOG_ERROR("open ./ServerConfig/Tables/WuHun.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		WuHunItem stu;
		TabFile.GetRecordData(i);
		stu.nId = TabFile.GetIntValue(0, 0);
		stu.nLv = TabFile.GetIntValue(1, 0);
		stu.nType = TabFile.GetIntValue(2, 0);
		stu.nQuality1 = TabFile.GetIntValue(3, 0);
		stu.nGainCondition = TabFile.GetIntValue(4, 0);

		std::string strAttr = TabFile.GetStringValue(5, "");
		if (!strAttr.empty() && strAttr != "-1")
		{
			StringVector tv = Answer::StringUtility::split(strAttr, "|");
			for (StringVector::iterator it = tv.begin(); it != tv.end(); ++it)
			{
				StringVector av = Answer::StringUtility::split(*it, ":");
				if (av.size() == 2)
				{
					AddAttribute attr;
					attr.m_nAddAttrType = (uint8_t)atoi(av[0].c_str());
					attr.m_nAddAttrValue = atoi(av[1].c_str());
					stu.lAttrList.push_back(attr);
				}
			}
		}

		stu.nTalentId = TabFile.GetIntValue(6, 0);
		stu.nTalentLevel = TabFile.GetIntValue(7, 0);
		stu.sName = TabFile.GetStringValue(8, "");
		stu.nAuction = TabFile.GetIntValue(13, 0);
		stu.nPrice = TabFile.GetIntValue(15, 0);
		stu.nOverlay = TabFile.GetIntValue(16, 0);
		stu.nGrade = TabFile.GetIntValue(17, 0);
		stu.nQuality = TabFile.GetIntValue(19, 0);
		stu.nDressLevel = TabFile.GetIntValue(20, 0);
		stu.nNeedQuality = TabFile.GetIntValue(3, 0);

		m_WuHunItemMap[stu.nId] = stu;
	}
}

void CfgData::InitWuHunShopTable()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/MysterShop.txt");
	if (ret == false)
	{
		LOG_ERROR("open ./ServerConfig/Tables/MysterShop.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		TabFile.GetRecordData(i);
	}
}

void CfgData::InitXianYaoTaskTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XiangYaoTask.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XiangYaoTask.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XiangYaoTask.txt
    }
}

void CfgData::InitXinMoTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XinMoLevel.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XinMoLevel.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XinMoLevel.txt
    }
}

void CfgData::InitXinMoTask(int32_t Level, int32_t Times)
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_INITXINMOTASK);
    if (ret == false)
    {
        LOG_ERROR("open FILE_INITXINMOTASK failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // no file
    }
}

void CfgData::InitXingMaiSlotTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XingMaiSlot.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XingMaiSlot.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XingMaiSlot.txt
    }
}

void CfgData::InitXingMaiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/AttributeXingMai.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/AttributeXingMai.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/AttributeXingMai.txt
    }
}

void CfgData::InitXuWuTask(int32_t Level, int32_t Times)
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT(FILE_INITXUWUTASK);
    if (ret == false)
    {
        LOG_ERROR("open FILE_INITXUWUTASK failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // no file
    }
}

void CfgData::InitXunLeiTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/XunLeiBox.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/XunLeiBox.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/XunLeiBox.txt
    }
}

void CfgData::InitYYDaTing()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YYDaTing.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YYDaTing.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YYDaTing.txt
    }
}

void CfgData::InitYYVip()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YYHuiYuan.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YYHuiYuan.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YYHuiYuan.txt
    }
}

void CfgData::InitYellowDailyRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowEverydayReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YellowEverydayReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YellowEverydayReward.txt
    }
}

void CfgData::InitYellowLevelRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowLevelReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YellowLevelReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YellowLevelReward.txt
    }
}

void CfgData::InitYellowRewardTable()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/YellowReward.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/YellowReward.txt failed, please check!!!");
        return;
    }

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {
        return;
    }
const CfgZongHeYunYingHD* CfgData::GetZongHeYunYingHDCfg()
{
	return NULL; // TODO: load from ZongHeYunYingHD.cfg
}


    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // ./ServerConfig/Tables/YellowReward.txt
    }
}

const GongMingCfg* CfgData::GetGongMingCfg( int32_t nLevel )
{
    GongMingCfgMap::const_iterator iter = m_GongMingCfgMap.find( nLevel );
    if ( iter != m_GongMingCfgMap.end() )
        return &iter->second;
    return NULL;
}

const GongMingCfgMap& CfgData::GetGongMingCfgMap()
{
    return m_GongMingCfgMap;
}
const CfgGuardPrivilege* CfgData::GetGuardPrivilege( int8_t nIndex )
{
    CfgGuardPrivilegeMap::const_iterator iter = m_GuardPrivilegeMap.find( nIndex );
    if ( iter != m_GuardPrivilegeMap.end() )
        return &iter->second;
    return NULL;
}

const CfgGuardPrivilegeMap& CfgData::GetGuardPrivilegeMap()
{
    return m_GuardPrivilegeMap;
}

int32_t CfgData::GetGuardPrivilegeStartTime()
{
    return m_nGuardPrivilegeStartTime;
}

int32_t CfgData::GetGuardPrivilegeEndTime()
{
    return m_nGuardPrivilegeEndTime;
}

const SpeciaEquipCfg* CfgData::GetSpeciaEquipCfg( int32_t nId )
{
    SpeciaEquipCfgMap::const_iterator iter = m_SpeciaEquipCfgMap.find( nId );
    if ( iter != m_SpeciaEquipCfgMap.end() )
        return &iter->second;
    return NULL;
}


WuHunItem* CfgData::GetWuHunItem( int32_t nId )
{
	WuHunItemMap::iterator iter = m_WuHunItemMap.find( nId );
	if ( iter != m_WuHunItemMap.end() )
	{
		return &( iter->second );
	}
	return NULL;
}

CreateWuHun* CfgData::GetCreateWuHun( int32_t nId )
{
	CreateWuHunMap::iterator iter = m_CreateWuHunMap.find( nId );
	if ( iter != m_CreateWuHunMap.end() )
	{
		return &( iter->second );
	}
	return NULL;
}

const CfgBlacketMarketTable* CfgData::GetBlacketMarketTable()
{
    return &m_BlacketMarketTable;
}void CfgData::InitMagicBoxTable()
{
	// TODO: 从数据表加载魔盒配置
}
void CfgData::InitFlopDrawTable()
{
	// TODO: 从数据表加载翻牌抽奖配置
}
const CfgFlopDrawTable& CfgData::GetFlopDrawTable() const
{
	return m_cfgFlopDraw;
}


// ========== 金币奖励任务配置存根 ==========
void CfgData::InitMoneyRewardTask( TaskStateInfo (*pTask)[9], int32_t nLevel )
{
	// TODO: 从配置表加载金币奖励任务
}

int32_t CfgData::RandPdbfTask( int32_t nLevel )
{
	return 0;
}

const BackEquipTask* CfgData::GetBackEquipTask( int32_t nId )
{
	BackEquipTaskMap::const_iterator iter = m_cfgBackEquipTask.find( nId );
	if ( iter != m_cfgBackEquipTask.end() )
		return &iter->second;
	return NULL;
}

int32_t CfgData::GetEquipBackTaskId( int32_t nLevel, int32_t nRandTimes )
{
	return 0;
}

const ShenWeiTaskCfg* CfgData::GetShenWeiTaskCfg( int32_t nIndex )
{
	ShenWeiTaskCfgMap::const_iterator iter = m_cfgShenWeiTask.find( nIndex );
	if ( iter != m_cfgShenWeiTask.end() )
		return &iter->second;
	return NULL;
}

int32_t CfgData::RandXiangYaoTaskId( int32_t nLevel, bool bBest )
{
	return 0;
}

int32_t CfgData::getXiangYaoStart( int32_t nTaskId )
{
	return 0;
}

int32_t CfgData::InitXuWuTask( int32_t nLevel, int32_t nFlag )
{
	return 0;
}

int32_t CfgData::InitXinMoTask( int32_t nLevel, int32_t nFlag )
{
	return 0;
}


// ========== V计划配置存根 ==========
const CfgVplanMap* CfgData::GetCfgVplanMap() const
{
	return &m_cfgVplan;
}

const CfgYYVipMap* CfgData::GetCfgYYVipMap() const
{
	return &m_cfgYYVip;
}

const CfgXunLeiMap* CfgData::GetXunLeiTable() const
{
	return &m_cfgXunLei;
}

const CfgLuDaShiMap* CfgData::GetLaDaShiHuiYuanMap() const
{
	return &m_cfgLuDaShi;
}

const CfgSwVipRewardMap* CfgData::GetSwVipRewardMap() const
{
	return &m_cfgSwVipReward;
}

const CfgSwVipRewardMap* CfgData::GetSwVipBarRewardMap() const
{
	return &m_cfgSwVipBar;
}

const CfgYYGameAppMap* CfgData::GetYYGameAppMap() const
{
	return &m_cfgYYGameApp;
}

const CfgSgGameAppMap* CfgData::GetSgGameAppMap() const
{
	return &m_cfgSgGameApp;
}
// ========== NationalDay config getters ==========
const NationalDayTaskCfg* CfgData::GetNationalDayTaskCfg( int32_t nType, int32_t nId ) const
{
	std::pair<int,int> key( nType, nId );
	NationalDayTaskCfgMap::const_iterator it = m_NationalDayTaskCfgMap.find( key );
	if ( it != m_NationalDayTaskCfgMap.end() )
		return &it->second;
	return NULL;
}

const NationalDayLevelCfg* CfgData::GetNationalDayLevelCfg( int32_t nLevel ) const
{
	NationalDayLevelCfgMap::const_iterator it = m_NationalDayLevelCfgMap.find( nLevel );
	if ( it != m_NationalDayLevelCfgMap.end() )
		return &it->second;
	return NULL;
}

const NationalDayTaskCfgMap* CfgData::GetNationalDayTaskCfgMap() const
{
	return &m_NationalDayTaskCfgMap;
}

const NationalDayLevelCfgMap* CfgData::GetNationalDayLevelCfgMap() const
{
	return &m_NationalDayLevelCfgMap;
}
