
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
	InitStrengthenTable();
	InitEquipBackTable();
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
	InitClbAimCfg();
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
	InitEquipRongHeTable();

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

const CfgFamilyBoss* CfgFamilyTable::GetFamilyBoss( int32_t FamilyLevel, int32_t BossId ) const
{
    if ( FamilyLevel <= 0 )
    {
        std::map<int32_t, CfgFamilyBoss>::const_iterator iter = m_mFamilyBossByMid.find( BossId );
        if ( iter != m_mFamilyBossByMid.end() )
        {
            return &iter->second;
        }
    }
    else
    {
        std::map<int32_t, CfgFamilyBoss>::const_iterator iter = m_mFamilyBoss.find( FamilyLevel );
        if ( iter != m_mFamilyBoss.end() )
        {
            return &iter->second;
        }
    }
    return NULL;
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

const TestServerReward* CfgData::GetTestServerReward( int32_t nId ) const
{
    TestServerRewardMap::const_iterator iter = m_TestServerRewardMap.find( nId );
    if ( iter != m_TestServerRewardMap.end() )
    {
        return &iter->second;
    }
    return NULL;
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

    m_Wan360RewardMap.clear();
    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {
        Wan360Reward stu;
        memset(&stu, 0, sizeof(stu));
        stu.Index = TabFile.Search_Posistion(i, 0)->iValue;
        std::string strItems = TabFile.Search_Posistion(i, 1)->pString;
        stu.Items = CItemHelper::parseItemVectorString(strItems);
        m_Wan360RewardMap[stu.Index] = stu;
    }
}

void CfgData::Init360RewardTypeTable()
{

  CDBCFile TabFile(0);
  if ( !TabFile.OpenFromTXT("./ServerConfig/Tables/GameLobbyType.txt") )
  {
    LOG_ERROR("open FILE_360_REWARD_TYPE_TABLE failed,please check!!!");
  }
}
void CfgData::InitActDropTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::list<ActDropItem> *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-100h] BYREF
  ActDropItem stu; // [rsp+A0h] [rbp-70h] BYREF
  int32_t Type; // [rsp+CCh] [rbp-44h] BYREF
  std::string p_StringTime; // [rsp+D0h] [rbp-40h] BYREF
  char v8; // [rsp+DFh] [rbp-31h] BYREF
  std::string v9; // [rsp+E0h] [rbp-30h] BYREF
  char v10; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/shoujihuodong.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ACTDROP_TABLE failed, please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        Type = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nMinLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMaxLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMapType = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nClass = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCount = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBind = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        p_StringTime.assign(v1->pString);
        stu.nStartTime = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v9.assign(v2->pString);
        stu.nEndTime = Answer::DayTime::StringToIntTime(v9);
        
        stu.nProbability = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,std::list<ActDropItem>>::operator[](&this->m_ActDropItemListMap, &Type);
        std::list<ActDropItem>::push_back(v3, &stu);
      }
    }
  }
}

//#####################################
// local variable allocation has failed, the output may be wrong!
ActDropItemList CfgData::GetAcrDropList(int32_t nType)
{
  int32_t v2; // edx
  ActDropItemList result; // rax
  std::pair<const int,std::list<ActDropItem> > *v4; // rax
  int32_t nTypea; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,std::list<ActDropItem> > > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<ActDropItem> > > __x; // [rsp+20h] [rbp-30h] BYREF

  thisa = *(CfgData **)&nType;
  nTypea = v2;
  std::list<ActDropItem>::list((std::list<ActDropItem> *const)this);
  std::list<ActDropItem>::clear((std::list<ActDropItem> *const)this);
  it._M_node = std::map<int,std::list<ActDropItem>>::find(
                 (std::map<int,std::list<ActDropItem>> *const)(*(_QWORD *)&nType + 11832LL),
                 &nTypea)._M_node;
  __x._M_node = std::map<int,std::list<ActDropItem>>::end(&thisa->m_ActDropItemListMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<ActDropItem>>>::operator!=(&it, &__x) )
  {
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::list<ActDropItem>>>::operator->(&it);
    std::list<ActDropItem>::operator=((std::list<ActDropItem> *const)this, &v4->second);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
void CfgData::InitActiveSkillTable()
{
  const CDBCFile::FIELD *v1; // rax
  CfgActiveSkill skill; // [rsp+10h] [rbp-1A0h] BYREF
  CDBCFile TabFile(0); // [rsp+C0h] [rbp-F0h] BYREF
  AttrAddonVector __x; // [rsp+150h] [rbp-60h] BYREF
  std::string path; // [rsp+170h] [rbp-40h] BYREF
  char v6; // [rsp+17Fh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+180h] [rbp-30h] BYREF
  char v8; // [rsp+18Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+190h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+194h] [rbp-1Ch]
  int32_t i; // [rsp+198h] [rbp-18h]
  int32_t nIndex; // [rsp+19Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_skill_info.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_ACTIVE_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&skill, 0, sizeof(skill));
        /* std::vector<AttrAddon>::vector(&skill.summon_attr); */
        nIndex = 0;
        skill.id = TabFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        skill.talent = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.groupid = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.job = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.kind = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.distance = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.range = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.area = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.self = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.target_num = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.beneficial = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.tar_type = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.addon_skill = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.addon_time = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.addon_cd = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.addon_delay = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.addon_trig_times = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.cd = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.cd_adjust = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.mp = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.power = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.special = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.attack_type = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.attack_modify = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.building_modify = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.buff_rate = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.buff = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        skill.chantTime = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.summon_id = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        skill.summon_delay = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/cfg_skill_info.txt";
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&skill.summon_attr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        skill.summon_limit = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 17;
        skill.boss_addon_damage = TabFile.Search_Posistion( i, nIndex++)->iValue;
        skill.append_value = TabFile.Search_Posistion( i, nIndex++)->iValue;
        skill.shu_lian_du = TabFile.Search_Posistion( i, nIndex++)->iValue;
        skill.cd += skill.cd_adjust;
        CfgSkillTable::AddActiveSkill(&this->m_cfgSkillTable, &skill);
        /* CfgActiveSkill::~CfgActiveSkill(&skill); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitAttrBattleTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-C0h] BYREF
  int32_t iBaseTableCount; // [rsp+A8h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+ACh] [rbp-24h]
  int32_t i; // [rsp+B0h] [rbp-20h]
  int32_t nIndex; // [rsp+B4h] [rbp-1Ch]
  int32_t nAttr; // [rsp+B8h] [rbp-18h]
  int32_t nBattle; // [rsp+BCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/AttrBattle.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ATTR_BATTLE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      bzero(this->m_cfgAttrBattle, 0xC8u);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nAttr = readFile.Search_Posistion( i, 0)->iValue;
        nBattle = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        if ( nAttr > 0 && nAttr <= 49 )
          this->m_cfgAttrBattle[nAttr] = nBattle;
      }
    }
  }
}

//#####################################
int32_t CfgData::GetAttrBattle(int32_t nAttr)
{
  if ( nAttr <= 0 || nAttr > 49 )
    return 0;
  else
    return this->m_cfgAttrBattle[nAttr];
}

//#####################################
void CfgData::InitBFZLEnterCostTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  ItemDataList vItem; // [rsp+A0h] [rbp-40h] BYREF
  bool bCombi[10]; // [rsp+B0h] [rbp-30h] BYREF
  char v5; // [rsp+BAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+BCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+C0h] [rbp-20h]
  int32_t i; // [rsp+C4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+C8h] [rbp-18h]
  int32_t nTimes; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/BingFengZouLang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BFZL_ENTER_COST_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        nTimes = readFile.Search_Posistion( i, 1)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v5);
        CItemHelper::parseItemDataListString((const std::string *const)&vItem, (bool)bCombi);
        
        ++nIndex;
        CfgBFZLEnterCostTable::AddEnterCost(&this->m_cfgBFZLEnterCostTable, nTimes, &vItem);
        std::list<ItemData>::~list(&vItem);
      }
    }
  }
}

//#####################################
void CfgData::InitBaoKuFuBen()
{
  int v1; // ebx
  BaoKuFuBen *v2; // rax
  int32_t v3; // ebx
  int32_t v4; // ebx
  int32_t v5; // ebx
  int32_t v6; // ebx
  int32_t v7; // ebx
  int32_t v8; // ebx
  BaoKuRandom *v9; // rax
  BaoKuRandom *p_stu_0; // rbx
  unsigned int v11; // r8d
  int64_t v12; // rcx
  CDBCFile readFile_0(0); // [rsp+10h] [rbp-170h] BYREF
  BaoKuRandom stu_0; // [rsp+A0h] [rbp-E0h] BYREF
  BaoKuFuBen stu; // [rsp+130h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+148h] [rbp-38h]
  int32_t iBaseColumnCount; // [rsp+14Ch] [rbp-34h]
  int32_t i; // [rsp+150h] [rbp-30h]
  int32_t nIndex; // [rsp+154h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+15Ch] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+160h] [rbp-20h]
  int32_t i_0; // [rsp+164h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+168h] [rbp-18h]
  int32_t j; // [rsp+16Ch] [rbp-14h]

  CDBCFile::CDBCFile((CDBCFile *const)&stu_0, 0);
  if ( !CDBCFile::OpenFromTXT((CDBCFile *const)&stu_0, "./ServerConfig/Tables/BaoKuFuBen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBaoKuF);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = CDBCFile::GetRecordsNum((const CDBCFile *const)&stu_0);
    iBaseColumnCount = CDBCFile::GetFieldsNum((const CDBCFile *const)&stu_0);
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,BaoKuFuBen>::clear(&this->m_BaoKuFuBenMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.FuBenId = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, 0)->iValue;
        stu.InitCount = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.BuyCount = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.Gold = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        stu.AddTimes = CDBCFile::Search_Posistion((const CDBCFile *const)&stu_0, i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,BaoKuFuBen>::operator[](&this->m_BaoKuFuBenMap, &stu.FuBenId);
        *v2 = stu;
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT(_0, "./ServerConfig/Tables/BaoKuRandom.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBaoKuF_0);
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum(_0);
      iBaseColumnCount_0 = readFile.GetFieldsNum(_0);
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,BaoKuRandom>::clear(&this->m_BaoKuRandomMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu_0, 0, sizeof(stu_0));
          stu_0.Index = readFile_0.Search_Posistion( i_0, 0)->iValue;
          stu_0.XValue = readFile_0.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.YValue = readFile_0.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          for ( j = 0; j <= 4; ++j )
          {
            v3 = j;
            stu_0.Items[v3].nRate = readFile_0.Search_Posistion( i_0, nIndex_0++)->iValue;
            v4 = j;
            stu_0.Items[v4].nItemId = readFile_0.Search_Posistion( i_0, nIndex_0++)->iValue;
            v5 = j;
            stu_0.Items[v5].nItemClass = readFile_0.Search_Posistion( i_0, nIndex_0++)->iValue;
            v6 = j;
            stu_0.Items[v6].nItemCount = readFile_0.Search_Posistion( i_0, nIndex_0++)->iValue;
            v7 = j;
            stu_0.Items[v7].nBind = readFile_0.Search_Posistion( i_0, nIndex_0++)->iValue;
            v8 = j;
            stu_0.Items[v8].nGongGaoId = readFile_0.Search_Posistion( i_0, nIndex_0++)->iValue;
          }
          v9 = std::map<int,BaoKuRandom>::operator[](&this->m_BaoKuRandomMap, &stu_0.Index);
          p_stu_0 = &stu_0;
          v11 = 132;
          if ( ((unsigned __int8)v9 & 4) != 0 )
          {
            v9->Index = stu_0.Index;
            v9 = (BaoKuRandom *)((char *)v9 + 4);
            p_stu_0 = (BaoKuRandom *)&stu_0.XValue;
            v11 = 128;
          }
          v12 = v11 >> 3;
          qmemcpy(v9, p_stu_0, 8 * v12);
          if ( (v11 & 4) != 0 )
            *(&v9->Index + 2 * v12) = *(&p_stu_0->Index + 2 * v12);
        }
      }
    }
  }
}

//#####################################
BaoKuFuBen *CfgData::GetBaoKuFuBen(int32_t FuBenId)
{
  int32_t FuBenIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,BaoKuFuBen> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BaoKuFuBen> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  FuBenIda = FuBenId;
  it._M_node = std::map<int,BaoKuFuBen>::find(&this->m_BaoKuFuBenMap, &FuBenIda)._M_node;
  __x._M_node = std::map<int,BaoKuFuBen>::end(&thisa->m_BaoKuFuBenMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BaoKuFuBen>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,BaoKuFuBen>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
BaoKuRandomMap CfgData::GetBaoKuRandomMap()
{
  return m_BaoKuRandomMap;
}

//#####################################
void CfgData::InitBeastShrineEnterCostTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  ItemDataList vItem; // [rsp+A0h] [rbp-40h] BYREF
  bool bCombi[10]; // [rsp+B0h] [rbp-30h] BYREF
  char v5; // [rsp+BAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+BCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+C0h] [rbp-20h]
  int32_t i; // [rsp+C4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+C8h] [rbp-18h]
  int32_t nTimes; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/AnimalMapCost.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBfzlEn_0);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nTimes = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v5);
        CItemHelper::parseItemDataListString((const std::string *const)&vItem, (bool)bCombi);
        
        ++nIndex;
        CfgBeastShrineTable::AddEnterCost(&this->m_CfgBeastShrineTable, nTimes, &vItem);
        std::list<ItemData>::~list(&vItem);
      }
    }
  }
}

//#####################################
void CfgData::InitBlueDailyRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-210h] BYREF
  CfgTencentGift high; // [rsp+A0h] [rbp-180h] BYREF
  CfgTencentGift year; // [rsp+E0h] [rbp-140h] BYREF
  CfgTencentGift daily; // [rsp+120h] [rbp-100h] BYREF
  MemChrBagVector __x; // [rsp+160h] [rbp-C0h] BYREF
  std::string strItems; // [rsp+180h] [rbp-A0h] BYREF
  char v10; // [rsp+18Fh] [rbp-91h] BYREF
  MemChrBagVector v11; // [rsp+190h] [rbp-90h] BYREF
  std::string v12; // [rsp+1B0h] [rbp-70h] BYREF
  char v13; // [rsp+1BFh] [rbp-61h] BYREF
  MemChrBagVector v14; // [rsp+1C0h] [rbp-60h] BYREF
  std::string v15; // [rsp+1E0h] [rbp-40h] BYREF
  char v16; // [rsp+1F6h] [rbp-2Ah] BYREF
  int32_t iBaseTableCount; // [rsp+1F8h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+1FCh] [rbp-24h]
  int32_t i; // [rsp+200h] [rbp-20h]
  int32_t nIndex; // [rsp+204h] [rbp-1Ch]
  int32_t nId; // [rsp+208h] [rbp-18h]
  int32_t nLevel; // [rsp+20Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/BlueEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BLUE_DAILY_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&daily);
        CfgTencentGift::CfgTencentGift(&year);
        CfgTencentGift::CfgTencentGift(&high);
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&daily.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v12.assign(v2->pString);
        CItemHelper::parseItemVectorString(&v11, &v12);
        std::vector<MemChrBag>::operator=(&year.vRewards, &v11);
        std::vector<MemChrBag>::~vector(&v11);
        
        ++nIndex;
        
        v3 = TabFile.Search_Posistion( i, nIndex);
        v15.assign(v3->pString);
        CItemHelper::parseItemVectorString(&v14, &v15);
        std::vector<MemChrBag>::operator=(&high.vRewards, &v14);
        std::vector<MemChrBag>::~vector(&v14);
        
        ++nIndex;
        daily.nLevel = nLevel;
        year.nLevel = nLevel;
        high.nLevel = nLevel;
        CfgTencentTable::AddBlueDailyGift(&this->m_cfgTencentTable, &daily);
        CfgTencentTable::AddBlueYearGift(&this->m_cfgTencentTable, &year);
        CfgTencentTable::AddBlueHighGift(&this->m_cfgTencentTable, &high);
        /* CfgTencentGift::~CfgTencentGift(&high); - auto cleanup */
        /* /* CfgTencentGift::~CfgTencentGift(&year); - auto cleanup */ - auto cleanup */
        /* /* CfgTencentGift::~CfgTencentGift(&daily); - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitBlueLevelRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-120h] BYREF
  CfgTencentGift gift; // [rsp+A0h] [rbp-90h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v6; // [rsp+10Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+10Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+110h] [rbp-20h]
  int32_t i; // [rsp+114h] [rbp-1Ch]
  int32_t nIndex; // [rsp+118h] [rbp-18h]
  int32_t nId; // [rsp+11Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/BlueLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BLUE_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&gift);
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        CfgTencentTable::AddBlueLevelGift(&this->m_cfgTencentTable, nId, &gift);
        /* /* /* CfgTencentGift::~CfgTencentGift(&gift); - auto cleanup */ - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitBlueRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  MemChrBagVector vReward; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+C0h] [rbp-30h] BYREF
  char v5; // [rsp+CAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+CCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+D0h] [rbp-20h]
  int32_t i; // [rsp+D4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+D8h] [rbp-18h]
  int32_t nId; // [rsp+DCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/BlueReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BLUE_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = TabFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&vReward, &strItems);
        
        ++nIndex;
        CfgTencentTable::SetBlueNewerGift(&this->m_cfgTencentTable, &vReward);
        std::vector<MemChrBag>::~vector(&vReward);
      }
    }
  }
}

//#####################################
void CfgData::InitBossDistribution()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-180h] BYREF
  std::string BossMapListString_0; // [rsp+A0h] [rbp-F0h] BYREF
  MapBossInfo stu_0; // [rsp+B0h] [rbp-E0h] BYREF
  std::string BossMapListString; // [rsp+D0h] [rbp-C0h] BYREF
  BossLevelInfo stu; // [rsp+E0h] [rbp-B0h] BYREF
  char v9; // [rsp+FFh] [rbp-91h] BYREF
  std::list<int> __x; // [rsp+100h] [rbp-90h] BYREF
  BossLevelInfo p_stu; // [rsp+110h] [rbp-80h] BYREF
  char v12; // [rsp+12Fh] [rbp-61h] BYREF
  std::list<int> v13; // [rsp+130h] [rbp-60h] BYREF
  MapBossInfo v14; // [rsp+140h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+15Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+160h] [rbp-30h]
  int32_t i; // [rsp+164h] [rbp-2Ch]
  int32_t nIndex; // [rsp+168h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+170h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+174h] [rbp-1Ch]
  int32_t i_0; // [rsp+178h] [rbp-18h]
  int32_t nIndex_0; // [rsp+17Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/MonsterRefreshInMaps.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_LEVEL_IFNO_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<int>::list(&stu.BossMapList);
        stu.BossLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        BossMapListString.assign(v2->pString);
        
        ++nIndex;
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, (int32_t)&BossMapListString);
        std::list<int>::operator=(&stu.BossMapList, &__x);
        std::list<int>::~list(&__x);
        BossLevelInfo::BossLevelInfo(&p_stu, &stu);
        BossDistribution::AddBossLevelInfo(&this->m_BossDistribution, &p_stu);
        /* BossLevelInfo::~BossLevelInfo(&p_stu); - auto cleanup */
        /* BossLevelInfo::~BossLevelInfo(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/MapClassInfo.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu_0, 0, sizeof(stu_0));
          std::list<int>::list(&stu_0.BossMapList);
          stu_0.nId = TabFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          
          v3 = TabFile.Search_Posistion( i_0, nIndex_0);
          BossMapListString_0.assign(v3->pString);
          
          ++nIndex_0;
          CfgData::paraseInt32List((CfgData *const)&v13, (const std::string *const)this, (int32_t)&BossMapListString_0);
          std::list<int>::operator=(&stu_0.BossMapList, &v13);
          std::list<int>::~list(&v13);
          MapBossInfo::MapBossInfo(&v14, &stu_0);
          BossDistribution::AddMapBossInfo(&this->m_BossDistribution, &v14);
          /* MapBossInfo::~MapBossInfo(&v14); - auto cleanup */
          /* MapBossInfo::~MapBossInfo(&stu_0); - auto cleanup */
        }
      }
    }
  }
}

//#####################################
void CfgData::InitBossFirstKilledTable()
{
  CfgBossFirstKilled *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgBossFirstKilled stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/BossKill.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BOSS_FIRST_KILLED_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.Mid = readFile.Search_Posistion( i, 0)->iValue;
        stu.RewardType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.RewardValue = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.StartDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.EndDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,CfgBossFirstKilled>::operator[](&this->m_CfgBossFirstKilledMap, &stu.Mid);
        *v1 = stu;
      }
    }
  }
}

//#####################################
void CfgData::InitBossKilledReward()
{
  const CDBCFile::FIELD *v1; // rax
  BossKilledReward *v2; // rax
  BossKilledReward *v3; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-120h] BYREF
  BossKilledReward stu; // [rsp+A0h] [rbp-90h] BYREF
  int32_t BossId; // [rsp+DCh] [rbp-54h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v9; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GoldReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_BOSS_KILLED_REWARD_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<int>::list(&stu.BossList);
        /* std::vector<MemChrBag>::vector(&stu.Rewars); */
        stu.nType = readFile.Search_Posistion( i, nIndex++)->iValue;
        BossId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewars, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        v2 = std::map<signed char,BossKilledReward>::operator[](&this->m_BossKilledRewardMap, &stu.nType);
        std::list<int>::push_back(&v2->BossList, &BossId);
        v3 = std::map<signed char,BossKilledReward>::operator[](&this->m_BossKilledRewardMap, &stu.nType);
        std::vector<MemChrBag>::operator=(&v3->Rewars, &stu.Rewars);
        /* BossKilledReward::~BossKilledReward(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
BossKilledReward *CfgData::GetBossKilledReward(int32_t BossId)
{
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledReward> > it; // [rsp+10h] [rbp-20h] BYREF
  char __x; // [rsp+1Fh] [rbp-11h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledReward> > v5; // [rsp+20h] [rbp-10h] BYREF

  __x = BossId;
  it._M_node = std::map<signed char,BossKilledReward>::find(&this->m_BossKilledRewardMap, &__x)._M_node;
  v5._M_node = std::map<signed char,BossKilledReward>::end(&this->m_BossKilledRewardMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,BossKilledReward>>::operator!=(&it, &v5) )
    return &std::_Rb_tree_iterator<std::pair<signed char const,BossKilledReward>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitBuyGiftTable()
{
  const CDBCFile::FIELD *v1; // rax
  CfgBuyGift *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgBuyGift stu; // [rsp+A0h] [rbp-80h] BYREF
  std::string items; // [rsp+D0h] [rbp-50h] BYREF
  char v6; // [rsp+DFh] [rbp-41h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TimeLimit.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BUY_GIFT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgBuyGift::CfgBuyGift(&stu);
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nGold = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        items.assign(v1->pString);
        
        ++nIndex;
        nIndex += 3;
        stu.nBroad = readFile.Search_Posistion( i, nIndex++)->iValue;
        CItemHelper::parseItemVectorString(&__x, &items);
        std::vector<MemChrBag>::operator=(&stu.vGift, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        v2 = std::map<int,CfgBuyGift>::operator[](&this->m_cfgBuyGiftTable, &stu.nIndex);
        CfgBuyGift::operator=(v2, &stu);
        /* CfgBuyGift::~CfgBuyGift(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitCampWarContKillTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgCampWarContKill contKill; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/CampWarContKill.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CAMP_WAR_CONT_KILL_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&contKill, 0, sizeof(contKill));
        contKill.nLevel = readFile.Search_Posistion( i, 0)->iValue;
        contKill.nKillCount = readFile.Search_Posistion( i, ++nIndex)->iValue;
        contKill.nKillPoint = readFile.Search_Posistion( i, ++nIndex)->iValue;
        contKill.nBroadcast = readFile.Search_Posistion( i, ++nIndex)->iValue;
        contKill.nBreakBroadcast = readFile.Search_Posistion( i, ++nIndex)->iValue;
        contKill.nTitle = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgCampWarTable::AddContKill(&this->m_cfgCampWarTable, &contKill);
      }
    }
  }
}

//#####################################
void CfgData::InitCampWarRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-150h] BYREF
  CfgCampWarReward reward; // [rsp+A0h] [rbp-C0h] BYREF
  std::string failItem; // [rsp+E0h] [rbp-80h] BYREF
  std::string winItem; // [rsp+F0h] [rbp-70h] BYREF
  char v7; // [rsp+FEh] [rbp-62h] BYREF
  char v8; // [rsp+FFh] [rbp-61h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-60h] BYREF
  MemChrBagVector v10; // [rsp+120h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+144h] [rbp-1Ch]
  int32_t i; // [rsp+148h] [rbp-18h]
  int32_t nIndex; // [rsp+14Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/CampWarReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CAMP_WAR_REWARD_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&reward, 0, sizeof(reward));
        /* std::vector<MemChrBag>::vector(&reward.FailItems); */
        /* std::vector<MemChrBag>::vector(&reward.WinItems); */
        reward.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        reward.nMaxIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        reward.nWinMailId = readFile.Search_Posistion( i, nIndex++)->iValue;
        reward.nFailMailId = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        winItem.assign(v1->pString);
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        failItem.assign(v2->pString);
        
        ++nIndex;
        CItemHelper::parseItemVectorString(&__x, &failItem);
        std::vector<MemChrBag>::operator=(&reward.FailItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        CItemHelper::parseItemVectorString(&v10, &winItem);
        std::vector<MemChrBag>::operator=(&reward.WinItems, &v10);
        std::vector<MemChrBag>::~vector(&v10);
        CfgCampWarTable::AddReward(&this->m_cfgCampWarTable, &reward);
        /* CfgCampWarReward::~CfgCampWarReward(&reward); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitCarrierAttrTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgCarrierAttr stu; // [rsp+A0h] [rbp-80h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-60h] BYREF
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  char v6; // [rsp+EFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Carrier_attr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_ATTR_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        /* /* std::vector<AttrAddon>::vector(&stu.vAttr); */ */
        nIndex = 0;
        stu.nLevel = readFile.Search_Posistion( i, 0)->iValue;
        stu.nId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/Carrier_attr.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.vAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        CfgCarrierTable::AddCarrierAttr(&this->m_cfgCarrierTable, &stu);
        /* CfgCarrierAttr::~CfgCarrierAttr(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitCarrierTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgCarrier stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  char v6; // [rsp+DFh] [rbp-31h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF
  char v8; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Carrier.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::list<int>::list(&stu.lSkills);
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        std::string::string(size, "./ServerConfig/Tables/Carrier.txt", &v6);
        
        v1 = readFile.Search_Posistion( i, nIndex);
        path.assign(v1->pString);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.lSkills, &__x);
        std::list<int>::~list(&__x);
        
        ++nIndex;
        CfgCarrierTable::AddCarrier(&this->m_cfgCarrierTable, &stu);
        /* CfgCarrier::~CfgCarrier(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitChargeDungeon()
{
  ChargeDungeonCfg *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  ChargeDungeonCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/charge_dungeon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileCharge);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nMinKaiFuDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMaxKaiFuDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nChargeValue = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDungeonId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,ChargeDungeonCfg>::operator[](&this->m_ChargeDungeonCfgMap, &stu.nId);
        *v1 = stu;
      }
    }
  }
}

//#####################################
int32_t CfgData::GetChargeDungeonId(int32_t nId, int32_t Todaycharge)
{
  CfgData *v3; // rax
  const std::pair<const int,ChargeDungeonCfg> *v4; // rax
  const std::pair<const int,ChargeDungeonCfg> *v5; // rax
  char v6; // al
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_const_iterator<std::pair<const int,ChargeDungeonCfg> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ChargeDungeonCfg> > __it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,ChargeDungeonCfg> > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ChargeDungeonCfg> > v14; // [rsp+40h] [rbp-10h] BYREF
  int32_t KaiFuDay; // [rsp+4Ch] [rbp-4h]

  thisa = this;
  nIda = nId;
  v3 = Answer::Singleton<CfgData>::instance();
  KaiFuDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1;
  __it._M_node = std::map<int,ChargeDungeonCfg>::find(&this->m_ChargeDungeonCfgMap, &nIda)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::_Rb_tree_const_iterator(&it, &__it);
  v14._M_node = std::map<int,ChargeDungeonCfg>::end(&thisa->m_ChargeDungeonCfgMap)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::_Rb_tree_const_iterator(&__x, &v14);
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator!=(&it, &__x)
    && ((v4 = std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it),
         v4->second.nMinKaiFuDay > KaiFuDay)
     || (v5 = std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it),
         v5->second.nMaxKaiFuDay < KaiFuDay)
     || std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it)->second.nChargeValue > Todaycharge
      ? (v6 = 0)
      : (v6 = 1),
        v6) )
  {
    return std::_Rb_tree_const_iterator<std::pair<int const,ChargeDungeonCfg>>::operator->(&it)->second.nDungeonId;
  }
  else
  {
    return 0;
  }
}

//#####################################
void CfgData::InitChouJiangTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  int v4; // ebx
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  int64_t v8; // rax
  MemChrBag v9; // [rsp+50h] [rbp-200h] BYREF
  CfgData *thisa; // [rsp+78h] [rbp-1D8h]
  CDBCFile readFile(0); // [rsp+80h] [rbp-1D0h] BYREF
  ChouJiangCfg stu; // [rsp+110h] [rbp-140h] BYREF
  ChouJiangLuckyCfg stu_0; // [rsp+160h] [rbp-F0h]
  std::string strItem; // [rsp+170h] [rbp-E0h] BYREF
  char v15; // [rsp+17Fh] [rbp-D1h] BYREF
  MemChrBagVector __x; // [rsp+180h] [rbp-D0h] BYREF
  std::string strItems; // [rsp+1A0h] [rbp-B0h] BYREF
  char v18; // [rsp+1AFh] [rbp-A1h] BYREF
  ChouJiangWeekReward p_stu; // [rsp+1B0h] [rbp-A0h] BYREF
  std::string v20; // [rsp+1D0h] [rbp-80h] BYREF
  char v21; // [rsp+1DFh] [rbp-71h] BYREF
  std::string v22; // [rsp+1E0h] [rbp-70h] BYREF
  char v23; // [rsp+1F2h] [rbp-5Eh] BYREF
  int32_t iBaseTableCount; // [rsp+1F4h] [rbp-5Ch]
  int32_t iBaseColumnCount; // [rsp+1F8h] [rbp-58h]
  int32_t i; // [rsp+1FCh] [rbp-54h]
  int32_t nIndex; // [rsp+200h] [rbp-50h]
  int32_t iBaseTableCount_0; // [rsp+208h] [rbp-48h]
  int32_t iBaseColumnCount_0; // [rsp+20Ch] [rbp-44h]
  int32_t i_0; // [rsp+210h] [rbp-40h]
  int32_t nIndex_0; // [rsp+214h] [rbp-3Ch]
  int32_t iBaseTableCount_1; // [rsp+21Ch] [rbp-34h]
  int32_t iBaseColumnCount_1; // [rsp+220h] [rbp-30h]
  int32_t i_1; // [rsp+224h] [rbp-2Ch]
  int32_t nIndex_1; // [rsp+228h] [rbp-28h]
  int32_t iBaseTableCount_2; // [rsp+230h] [rbp-20h]
  int32_t iBaseColumnCount_2; // [rsp+234h] [rbp-1Ch]
  int32_t i_2; // [rsp+238h] [rbp-18h]
  int32_t nIndex_2; // [rsp+23Ch] [rbp-14h]
  ItemData v44; // 0:kr00_12.12

  thisa = this;
  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureBase.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CHOU_JIANG_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        nIndex = 0;
        stu.Index = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        strItem.assign(v2->pString);
        CItemHelper::parseItemString(&v9, &strItem);
        stu.Item = v9;
        
        stu.Quality = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Probability = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.SubLuckValue = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.PersonalRecord = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.ServerRecord = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.Type = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MinDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MaxDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.JifenDel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ChouJiangTable::AddChouJiangCfg(&thisa->m_ChouJiangTable, stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureLucky.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_CHOU_JIANG_LUCK_TABLE failed,please check!!!\n");
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu_0.MaxLucky = 0;
          stu_0.MaxQuality = 0;
          nIndex_0 = 1;
          stu_0.MaxLucky = readFile.Search_Posistion( i_0, 1)->iValue;
          stu_0.MinQuality = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.MaxQuality = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          ChouJiangTable::AddChouJiangLuckyCfg(&thisa->m_ChouJiangTable, stu_0);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    if ( v3 )
    {
      
      if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureWeek.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_CHOU_JIANG_REWARD_TABLE failed,please check!!!\n");
        v4 = 0;
      }
      else
      {
        iBaseTableCount_1 = readFile.GetRecordsNum();
        iBaseColumnCount_1 = readFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            memset(&stu, 0, 32);
            std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.Item);
            nIndex_1 = 0;
            stu.Index = readFile.Search_Posistion( i_1, 0)->iValue;
            *(&stu.Index + 1) = readFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            
            v5 = readFile.Search_Posistion( i_1, nIndex_1);
            strItems.assign(v5->pString);
            CItemHelper::parseItemVectorString(&__x, &strItems);
            std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.Item, &__x);
            std::vector<MemChrBag>::~vector(&__x);
            
            ++nIndex_1;
            ChouJiangWeekReward::ChouJiangWeekReward(&p_stu, (const ChouJiangWeekReward *const)&stu);
            ChouJiangTable::AddChouJiangWeekReward(&thisa->m_ChouJiangTable, &p_stu);
            /* ChouJiangWeekReward::~ChouJiangWeekReward(&p_stu); - auto cleanup */
            ChouJiangWeekReward::~ChouJiangWeekReward((ChouJiangWeekReward *const)&stu);
          }
          v4 = 1;
        }
        else
        {
          v4 = 0;
        }
      }
      if ( v4 )
      {
        
        if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureConsume.txt") )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "open FILE_CHOU_JIANG_REWARD_TABLE failed,please check!!!\n");
        }
        else
        {
          iBaseTableCount_2 = readFile.GetRecordsNum();
          iBaseColumnCount_2 = readFile.GetFieldsNum();
          if ( iBaseColumnCount_2 > 0 )
          {
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              memset(&stu, 0, 0x38u);
              nIndex_2 = 0;
              stu.Index = readFile.Search_Posistion( i_2, 0)->iValue;
              ++nIndex_2;
              
              v6 = readFile.Search_Posistion( i_2, nIndex_2);
              v20.assign(v6->pString);
              v44 = CItemHelper::parseItemDataString(&v20);
              LODWORD(v8) = v44.m_nId;
              BYTE4(v8) = v44.m_nClass;
              *(_QWORD *)(&stu.Index + 1) = v8;
              *(_DWORD *)&stu.Item.itemClass = v44.m_nCount;
              
              stu.Item.itemCount = readFile.Search_Posistion( i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              
              v7 = readFile.Search_Posistion( i_2, nIndex_2);
              v22.assign(v7->pString);
              CItemHelper::parseItemString(&v9, &v22);
              *(MemChrBag *)&stu.Item.endTime = v9;
              
              ++nIndex_2;
              ChouJiangTable::AddChouJiangCost(&thisa->m_ChouJiangTable, *(ChouJiangCost *)&stu.Index);
            }
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::InitChristmasDuiHuanTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  ChristmasDuiHuan *v5; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-160h] BYREF
  ChristmasDuiHuan stu; // [rsp+A0h] [rbp-D0h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-90h] BYREF
  std::string strItems; // [rsp+100h] [rbp-70h] BYREF
  char v10; // [rsp+10Fh] [rbp-61h] BYREF
  std::list<ItemData> v11; // [rsp+110h] [rbp-60h] BYREF
  bool bCombi[15]; // [rsp+120h] [rbp-50h] BYREF
  char v13; // [rsp+12Fh] [rbp-41h] BYREF
  std::string p_StringTime; // [rsp+130h] [rbp-40h] BYREF
  char v15; // [rsp+13Fh] [rbp-31h] BYREF
  std::string v16; // [rsp+140h] [rbp-30h] BYREF
  char v17; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Christmas.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileLingZh_2);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,ChristmasDuiHuan>::clear(&this->m_ChristmasDuiHuanMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 60);
        /* /* /* std::vector<MemChrBag>::vector(&stu.Items); */ */ */
        std::list<ItemData>::list(&stu.CostItems);
        stu.nIndx = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v2->pString, &v13);
        CItemHelper::parseItemDataListString((const std::string *const)&v11, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &v11);
        std::list<ItemData>::~list(&v11);
        
        stu.nLimitCount = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        p_StringTime.assign(v3->pString);
        stu.nStartTime = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v4 = readFile.Search_Posistion( i, nIndex);
        v16.assign(v4->pString);
        stu.nEndTime = Answer::DayTime::StringToIntTime(v16);
        
        ++nIndex;
        v5 = std::map<int,ChristmasDuiHuan>::operator[](&this->m_ChristmasDuiHuanMap, &stu.nIndx);
        ChristmasDuiHuan::operator=(v5, &stu);
        /* ChristmasDuiHuan::~ChristmasDuiHuan(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
ChristmasDuiHuan *CfgData::GetChristmasDuiHuanCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,ChristmasDuiHuan> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ChristmasDuiHuan> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,ChristmasDuiHuan>::find(&this->m_ChristmasDuiHuanMap, &nIda)._M_node;
  __x._M_node = std::map<int,ChristmasDuiHuan>::end(&thisa->m_ChristmasDuiHuanMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,ChristmasDuiHuan>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,ChristmasDuiHuan>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitCityWarContRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgCityWarContReward stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GongChengZhanJiangLi.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_CITY_WAR_CONT_REWARD_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 36);
        /* std::vector<MemChrBag>::vector(&stu.vBreakReward); */
        stu.id = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vBreakReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.nBreakMailId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgCityWarTable::AddContReward(&this->m_cfgCityWarTable, &stu);
        /* CfgCityWarContReward::~CfgCityWarContReward(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitCrossTowerCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CrossTowerCfg *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-170h] BYREF
  CrossTowerCfg stu; // [rsp+A0h] [rbp-E0h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-80h] BYREF
  std::string strItems; // [rsp+120h] [rbp-60h] BYREF
  char v8; // [rsp+12Fh] [rbp-51h] BYREF
  MemChrBagVector v9; // [rsp+130h] [rbp-50h] BYREF
  std::string v10; // [rsp+150h] [rbp-30h] BYREF
  char v11; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/KuaFuMap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        /* std::vector<MemChrBag>::vector(&stu.RewardVt); */
        /* std::vector<MemChrBag>::vector(&stu.TopRewardVt); */
        stu.MapId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.NextMapId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.LastMapId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.MaxPlayer = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.MaxScore = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.MinScore = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.KillCount = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.Floor = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.RewardVt, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v10.assign(v2->pString);
        CItemHelper::parseItemVectorString(&v9, &v10);
        std::vector<MemChrBag>::operator=(&stu.TopRewardVt, &v9);
        std::vector<MemChrBag>::~vector(&v9);
        
        stu.MailId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,CrossTowerCfg>::operator[](&this->m_CrossTowerCfgMap, &stu.MapId);
        CrossTowerCfg::operator=(v3, &stu);
        /* CrossTowerCfg::~CrossTowerCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
CrossTowerCfg *CfgData::GetCrossTowerCfg(int32_t MapId)
{
  int32_t MapIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CrossTowerCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CrossTowerCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  MapIda = MapId;
  it._M_node = std::map<int,CrossTowerCfg>::find(&this->m_CrossTowerCfgMap, &MapIda)._M_node;
  __x._M_node = std::map<int,CrossTowerCfg>::end(&thisa->m_CrossTowerCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CrossTowerCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CrossTowerCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitCycleTowerTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int64_t v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-100h] BYREF
  CycleTowerCost stu_0; // [rsp+A0h] [rbp-70h]
  CycleTowerMapCfg stu; // [rsp+B0h] [rbp-60h]
  std::string strItem; // [rsp+C0h] [rbp-50h] BYREF
  char v8; // [rsp+D2h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+D4h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+D8h] [rbp-38h]
  int32_t i; // [rsp+DCh] [rbp-34h]
  int32_t nIndex; // [rsp+E0h] [rbp-30h]
  int32_t MapId; // [rsp+E4h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+F0h] [rbp-20h]
  int32_t i_0; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+F8h] [rbp-18h]
  int32_t Times; // [rsp+FCh] [rbp-14h]
  ItemData v21; // 0:kr00_12.12

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/LunHuiEvent.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C95A0);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        MapId = TabFile.Search_Posistion( i, 0)->iValue;
        stu.Floor = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.FloorType = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MonsterId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CycleTowerTable::AddCycleTowerMapCfg(&this->m_CycleTowerTable, MapId, stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/LunHuiConsume.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C95F8);
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 1;
          Times = TabFile.Search_Posistion( i_0, 1)->iValue;
          ++nIndex_0;
          
          v2 = TabFile.Search_Posistion( i_0, nIndex_0);
          strItem.assign(v2->pString);
          v21 = CItemHelper::parseItemDataString(&strItem);
          LODWORD(v3) = v21.m_nId;
          BYTE4(v3) = v21.m_nClass;
          *(_QWORD *)&stu_0.CostData.m_nId = v3;
          stu_0.CostData.m_nCount = v21.m_nCount;
          
          stu_0.CostGold = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CycleTowerTable::AddCycleTowerCost(&this->m_CycleTowerTable, Times, stu_0);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitDamnationTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  DamnationCfg *v3; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-140h] BYREF
  DamnationCfg stu; // [rsp+A0h] [rbp-B0h] BYREF
  std::list<ItemData> strItems; // [rsp+E0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+110h] [rbp-40h] BYREF
  char v11; // [rsp+11Fh] [rbp-31h] BYREF
  int32_t v12[3]; // [rsp+120h] [rbp-30h] BYREF
  char v13; // [rsp+12Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Curse.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileDamnat);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        DamnationCfg::DamnationCfg(&stu);
        stu.Level = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v8);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        ++nIndex;
        
        std::string::string(v10, "./ServerConfig/Tables/Curse.txt", &v11);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v12, v2->pString, &v13);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v12,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.AttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.Probability = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.HpPecent = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 3;
        stu.CostMoney = readFile.Search_Posistion( i, nIndex++)->iValue;
        v3 = std::map<int,DamnationCfg>::operator[](&this->m_DamnationCfgTable, &stu.Level);
        DamnationCfg::operator=(v3, &stu);
        /* DamnationCfg::~DamnationCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
DamnationCfg *CfgData::GetDamnationCfg(int32_t Level)
{
  int32_t Levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,DamnationCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,DamnationCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Levela = Level;
  it._M_node = std::map<int,DamnationCfg>::find(&this->m_DamnationCfgTable, &Levela)._M_node;
  __x._M_node = std::map<int,DamnationCfg>::end(&thisa->m_DamnationCfgTable)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,DamnationCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,DamnationCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitDiligenceCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  DiligenceCfg *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-F0h] BYREF
  DiligenceCfg stu; // [rsp+A0h] [rbp-60h] BYREF
  std::list<RateItem> strItems; // [rsp+C0h] [rbp-40h] BYREF
  _BYTE v6[14]; // [rsp+D0h] [rbp-30h] BYREF
  char v7; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/QinFen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9450);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<RateItem>::list(&stu.lItems);
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nValues = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v6, v1->pString, &v7);
        CItemHelper::parseRateItemDataListString((const std::string *const)&strItems);
        std::list<RateItem>::operator=(&stu.lItems, &strItems);
        std::list<RateItem>::~list(&strItems);
        
        ++nIndex;
        v2 = std::map<int,DiligenceCfg>::operator[](&this->m_DiligenceCfgMap, &stu.nId);
        DiligenceCfg::operator=(v2, &stu);
        /* DiligenceCfg::~DiligenceCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
DiligenceCfg *CfgData::GetDiligenceCfg(int32_t nType)
{
  int32_t nTypea; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,DiligenceCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,DiligenceCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nTypea = nType;
  it._M_node = std::map<int,DiligenceCfg>::find(&this->m_DiligenceCfgMap, &nTypea)._M_node;
  __x._M_node = std::map<int,DiligenceCfg>::end(&thisa->m_DiligenceCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,DiligenceCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,DiligenceCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitDrawTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgDrawReward stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBag item; // [rsp+D0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Draw.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DRAW_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgDrawReward::CfgDrawReward(&stu);
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nRate = readFile.Search_Posistion( i, nIndex++)->iValue;
        memset(&item, 0, sizeof(item));
        item.itemClass = readFile.Search_Posistion( i, nIndex++)->iValue;
        item.itemId = readFile.Search_Posistion( i, nIndex++)->iValue;
        item.itemCount = readFile.Search_Posistion( i, nIndex++)->iValue;
        item.bind = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nBroad = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        std::vector<MemChrBag>::push_back(&stu.vItem, &item);
        CfgDrawTable::Add(&this->m_cfgDrawTable, &stu);
        /* CfgDrawReward::~CfgDrawReward(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitDropRecordTable()
{
  CfgDropRecord *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgDropRecord record; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/DropRecord.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DROP_RECORD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&record.nIndex = 0;
        *(_DWORD *)&record.nItemClass = 0;
        record.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        record.nItemId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        record.nItemClass = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        record.nSpecial = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,CfgDropRecord>::operator[](&this->m_cfgDropRecordTable, &record.nIndex);
        *v1 = record;
      }
    }
  }
}

//#####################################
const CfgDropRecord *CfgData::GetDropRecord(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,CfgDropRecord> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgDropRecord> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  iter._M_node = std::map<int,CfgDropRecord>::find(&this->m_cfgDropRecordTable, &nIndexa)._M_node;
  __x._M_node = std::map<int,CfgDropRecord>::end(&thisa->m_cfgDropRecordTable)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgDropRecord>>::operator!=(&iter, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,CfgDropRecord>>::operator->(&iter)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitDuiHuanLimitTable()
{
  DuiHuanLimit *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  int32_t MaxLevel; // [rsp+ACh] [rbp-44h] BYREF
  DuiHuanLimit stu; // [rsp+B0h] [rbp-40h]
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/ExchangeShengYaoBi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,DuiHuanLimit>::clear(&this->m_DuiHuanLimit);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        *(_QWORD *)&stu.ShengYaoBi = 0;
        *(_QWORD *)&stu.ConstCurrency = 0;
        MaxLevel = TabFile.Search_Posistion( i, 1)->iValue;
        stu.ShengYaoBi = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.ConstGold = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.ConstCurrency = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Limit = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,DuiHuanLimit>::operator[](&this->m_DuiHuanLimit, &MaxLevel);
        *v1 = stu;
      }
    }
  }
}

//#####################################
DuiHuanLimit *CfgData::GetDuiHuanLimitCount(int32_t Level)
{
  int32_t Levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,DuiHuanLimit> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,DuiHuanLimit> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Levela = Level;
  it._M_node = std::map<int,DuiHuanLimit>::lower_bound(&this->m_DuiHuanLimit, &Levela)._M_node;
  __x._M_node = std::map<int,DuiHuanLimit>::end(&thisa->m_DuiHuanLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,DuiHuanLimit>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,DuiHuanLimit>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitDungeonScoreTable()
{
  const CDBCFile::FIELD *v1; // rax
  MemChrBag v2; // [rsp+0h] [rbp-120h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-F8h]
  CDBCFile TabFile(0); // [rsp+30h] [rbp-F0h] BYREF
  CfgDungeonScore score; // [rsp+C0h] [rbp-60h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  thisa = this;
  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/DungeonScore.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DUNGEON_SCORE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&score, 0, sizeof(score));
        score.nDungeonId = TabFile.Search_Posistion( i, 0)->iValue;
        score.nKillCount = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        CItemHelper::parseItemString(&v2, &strItem);
        score.Item = v2;
        
        ++nIndex;
        CfgDungeonScoreTable::AddDungeonScore(&thisa->m_cfgDungeonScoreTable, &score);
      }
    }
  }
}

//#####################################
void CfgData::InitDungeonSummon()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgDungeonSummon *v3; // rax
  int64_t v4; // rax
  CDBCFile DungeonTrapFile(0); // [rsp+10h] [rbp-130h] BYREF
  CfgDungeonSummon stu; // [rsp+A0h] [rbp-A0h] BYREF
  std::list<int> __x; // [rsp+D0h] [rbp-70h] BYREF
  int32_t size[3]; // [rsp+E0h] [rbp-60h] BYREF
  char v9; // [rsp+EFh] [rbp-51h] BYREF
  std::string path; // [rsp+F0h] [rbp-50h] BYREF
  char v11; // [rsp+FFh] [rbp-41h] BYREF
  std::string strItem; // [rsp+100h] [rbp-40h] BYREF
  char v13; // [rsp+10Fh] [rbp-31h] BYREF
  std::pair<int,int> __k; // [rsp+110h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]
  ItemData v20; // 0:kr00_12.12

  
  if ( !DungeonTrapFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_summon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_DUNGEON_SUMMON_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonTrapFile.GetRecordsNum();
    iBaseColumnCount = DungeonTrapFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgDungeonSummon::CfgDungeonSummon(&stu);
        stu.nDungeon = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nIndex = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nGold = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLimit = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(size, "./ServerConfig/Tables/cfg_dungeon_summon.txt", &v9);
        
        v1 = DungeonTrapFile.Search_Posistion( i, nIndex);
        path.assign(v1->pString);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.lMonsters, &__x);
        std::list<int>::~list(&__x);
        
        ++nIndex;
        
        v2 = DungeonTrapFile.Search_Posistion( i, nIndex);
        strItem.assign(v2->pString);
        v20 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v4) = v20.m_nId;
        BYTE4(v4) = v20.m_nClass;
        *(_QWORD *)&stu.ConstItem.m_nId = v4;
        stu.ConstItem.m_nCount = v20.m_nCount;
        
        stu.FreeCount = DungeonTrapFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __k = std::make_pair<int,int>(stu.nDungeon, stu.nIndex);
        v3 = std::map<std::pair<int,int>,CfgDungeonSummon>::operator[](&this->m_cfgDungeonSummon, &__k);
        CfgDungeonSummon::operator=(v3, &stu);
        /* CfgDungeonSummon::~CfgDungeonSummon(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
const CfgDungeonSummon *CfgData::GetDungeonSummon(int32_t nDungeon, int32_t nIndex)
{
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,CfgDungeonSummon> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,CfgDungeonSummon> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(nDungeon, nIndex);
  iter._M_node = std::map<std::pair<int,int>,CfgDungeonSummon>::find(&this->m_cfgDungeonSummon, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,CfgDungeonSummon>::end(&this->m_cfgDungeonSummon)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,CfgDungeonSummon>>::operator!=(&iter, &v6) )
    return (const CfgDungeonSummon *)((char *)std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,CfgDungeonSummon>>::operator->(&iter)
                                    + 8);
  else
    return 0;
}

//#####################################
void CfgData::InitEquipBackTask()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  BackEquipTask *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  std::string *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  std::map<int,std::list<Param2>> *v13; // rax
  std::list<Param2> *v14; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-250h] BYREF
  BackEquipTask stu; // [rsp+A0h] [rbp-1C0h] BYREF
  Param2 stu_0; // [rsp+F0h] [rbp-170h] BYREF
  StringVector TaskRates; // [rsp+100h] [rbp-160h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+120h] [rbp-140h] BYREF
  StringVector TaskRateVetcor; // [rsp+130h] [rbp-130h] BYREF
  Param2List param; // [rsp+150h] [rbp-110h] BYREF
  std::string TaskRate; // [rsp+160h] [rbp-100h] BYREF
  int32_t Times; // [rsp+168h] [rbp-F8h] BYREF
  int32_t Level; // [rsp+16Ch] [rbp-F4h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+170h] [rbp-F0h] BYREF
  StringVector ItemVetcor; // [rsp+180h] [rbp-E0h] BYREF
  std::string NeedEquipString; // [rsp+1A0h] [rbp-C0h] BYREF
  char v28; // [rsp+1AFh] [rbp-B1h] BYREF
  MemChrBagVector __x; // [rsp+1B0h] [rbp-B0h] BYREF
  std::string strItems; // [rsp+1D0h] [rbp-90h] BYREF
  char v31; // [rsp+1DFh] [rbp-81h] BYREF
  std::string delims; // [rsp+1E0h] [rbp-80h] BYREF
  char v33; // [rsp+1EFh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1F0h] [rbp-70h] BYREF
  int v35; // [rsp+1F8h] [rbp-68h] BYREF
  char v36; // [rsp+1FFh] [rbp-61h] BYREF
  std::string v37; // [rsp+200h] [rbp-60h] BYREF
  char v38; // [rsp+20Fh] [rbp-51h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v39; // [rsp+210h] [rbp-50h] BYREF
  std::string v40; // [rsp+220h] [rbp-40h] BYREF
  char v41; // [rsp+22Ah] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+22Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+230h] [rbp-30h]
  int32_t i; // [rsp+234h] [rbp-2Ch]
  int32_t nIndex; // [rsp+238h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+240h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+244h] [rbp-1Ch]
  int32_t i_0; // [rsp+248h] [rbp-18h]
  int32_t nIndex_0; // [rsp+24Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TaskRecovery.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EQUIP_BACK_TASK failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        /* /* std::vector<int>::vector(&stu.Equips); */ */
        std::vector<MemChrBag>::vector(&stu.Items);
        nIndex = 0;
        stu.Index = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        NeedEquipString.assign(v2->pString);
        
        stu.PlayerLevelMin = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.PlayerLevelMax = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Star = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GetCurr = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v3->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Items, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.RandGold = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        delims = "|";
        Answer::StringUtility::split(&ItemVetcor, &NeedEquipString, &delims, 0);
        
        for ( it._M_current = std::vector<std::string>::begin(&ItemVetcor)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&ItemVetcor)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          v5 = (const char *)std::string::c_str(v4);
          v35 = atoi(v5);
          std::vector<int>::push_back(&stu.Equips, &v35);
        }
        v6 = std::map<int,BackEquipTask>::operator[](&this->m_EquipBackTable, &stu.Index);
        BackEquipTask::operator=(v6, &stu);
        std::vector<std::string>::~vector(&ItemVetcor);
        /* /* BackEquipTask::~BackEquipTask(&stu); - auto cleanup */ - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/RecoveryTaskRate.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EQUIP_BACK_TASK failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          memset(&stu, 0, sizeof(stu));
          std::vector<int>::vector(&stu.Equips);
          std::vector<MemChrBag>::vector(&stu.Items);
          nIndex_0 = 0;
          Level = readFile.Search_Posistion( i_0, 0)->iValue;
          Times = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          
          v7 = readFile.Search_Posistion( i_0, nIndex_0);
          TaskRate.assign(v7->pString);
          
          ++nIndex_0;
          std::list<Param2>::list(&param);
          
          v37 = "|";
          Answer::StringUtility::split(&TaskRateVetcor, &TaskRate, &v37, 0);
          
          for ( it_0._M_current = std::vector<std::string>::begin(&TaskRateVetcor)._M_current;
                __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0) )
          {
            v39._M_current = std::vector<std::string>::end(&TaskRateVetcor)._M_current;
            if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v39) )
              break;
            
            v40 = ":";
            v8 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_0);
            Answer::StringUtility::split(&TaskRates, v8, &v40, 0);
            
            if ( std::vector<std::string>::size(&TaskRates) == 2 )
            {
              Param2::Param2(&stu_0, 0, 0);
              v9 = std::vector<std::string>::operator[](&TaskRates, 0);
              v10 = (const char *)std::string::c_str(v9);
              stu_0.nParam1 = atoi(v10);
              v11 = std::vector<std::string>::operator[](&TaskRates, 1u);
              v12 = (const char *)std::string::c_str(v11);
              stu_0.nParam2 = atoi(v12);
              std::list<Param2>::push_back(&param, &stu_0);
            }
            std::vector<std::string>::~vector(&TaskRates);
          }
          v13 = std::map<int,std::map<int,std::list<Param2>>>::operator[](&this->m_EquipBackTaskRate, &Level);
          v14 = std::map<int,std::list<Param2>>::operator[](v13, &Times);
          std::list<Param2>::operator=(v14, &param);
          std::vector<std::string>::~vector(&TaskRateVetcor);
          std::list<Param2>::~list(&param);
          BackEquipTask::~BackEquipTask(&stu);
        }
      }
    }
  }
}

//#####################################
int32_t CfgData::GetEquipBackTaskId(int32_t PlayerLevel, int32_t Times)
{
  std::pair<const int,std::map<int,std::list<Param2>> > *v3; // rax
  std::pair<const int,std::map<int,std::list<Param2>> > *v4; // rax
  Answer::Random *v5; // rax
  std::pair<const int,std::list<Param2> > *v6; // rax
  Param2 *v7; // rax
  Param2 *v9; // rax
  std::pair<const int,std::list<Param2> > *v10; // rax
  int32_t Timesa; // [rsp+0h] [rbp-70h] BYREF
  int32_t PlayerLevela; // [rsp+4h] [rbp-6Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-68h]
  std::_List_iterator<Param2> itbeg; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<Param2> > > pIt; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,std::list<Param2>> > > it; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,std::list<Param2>> > > __x; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<Param2> > > v18; // [rsp+50h] [rbp-20h] BYREF
  std::_List_iterator<Param2> v19; // [rsp+60h] [rbp-10h] BYREF
  int32_t TaskId; // [rsp+68h] [rbp-8h]
  int32_t nRand; // [rsp+6Ch] [rbp-4h]

  thisa = this;
  PlayerLevela = PlayerLevel;
  Timesa = Times;
  TaskId = 0;
  it._M_node = std::map<int,std::map<int,std::list<Param2>>>::lower_bound(&this->m_EquipBackTaskRate, &PlayerLevela)._M_node;
  __x._M_node = std::map<int,std::map<int,std::list<Param2>>>::end(&thisa->m_EquipBackTaskRate)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::map<int,std::list<Param2>>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,std::list<Param2>>>>::operator->(&it);
    pIt._M_node = std::map<int,std::list<Param2>>::find(&v3->second, &Timesa)._M_node;
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,std::list<Param2>>>>::operator->(&it);
    v18._M_node = std::map<int,std::list<Param2>>::end(&v4->second)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,std::list<Param2>>>::operator!=(&pIt, &v18) )
    {
      v5 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v5, 1, 10000);
      v6 = std::_Rb_tree_iterator<std::pair<int const,std::list<Param2>>>::operator->(&pIt);
      for ( itbeg._M_node = std::list<Param2>::begin(&v6->second)._M_node;
            std::_List_iterator<Param2>::operator++(&itbeg, 0) )
      {
        v10 = std::_Rb_tree_iterator<std::pair<int const,std::list<Param2>>>::operator->(&pIt);
        v19._M_node = std::list<Param2>::end(&v10->second)._M_node;
        if ( !std::_List_iterator<Param2>::operator!=(&itbeg, &v19) )
          break;
        v7 = std::_List_iterator<Param2>::operator->(&itbeg);
        if ( v7->nParam2 >= nRand )
          return std::_List_iterator<Param2>::operator->(&itbeg)->nParam1;
        v9 = std::_List_iterator<Param2>::operator->(&itbeg);
        nRand -= v9->nParam2;
      }
    }
  }
  return TaskId;
}

//#####################################
BackEquipTask *CfgData::GetBackEquipTask(int32_t Index)
{
  int32_t Indexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,BackEquipTask> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackEquipTask> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Indexa = Index;
  it._M_node = std::map<int,BackEquipTask>::find(&this->m_EquipBackTable, &Indexa)._M_node;
  __x._M_node = std::map<int,BackEquipTask>::end(&thisa->m_EquipBackTable)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackEquipTask>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,BackEquipTask>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitEquipBlessTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgEquipBless stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/LuckyValue.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgEquipBless::CfgEquipBless(&stu);
        stu.nBless = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nAddRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.nRemineRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBroad = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipBlessTable::Add(&this->m_cfgEquipBlessTable, &stu);
        /* CfgEquipBless::~CfgEquipBless(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitEquipBoxTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-120h] BYREF
  CfgEquipBox stu; // [rsp+A0h] [rbp-90h] BYREF
  std::list<Param2> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v5[15]; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  int32_t v7[3]; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/cfg_item_gift_equip.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BOX_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipBox::CfgEquipBox(&stu);
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.vEquipId[1] = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.vEquipId[2] = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.vEquipId[3] = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nWeight = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBind = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        std::string::string(v5, "./ServerConfig/Tables/EquipPosSuit.txt", &v6);
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v7, v1->pString, &v8);
        CfgData::paraseParam2List(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v7,
          (const std::string *const)(unsigned int)i);
        std::list<Param2>::operator=(&stu.lstStar, &__x);
        std::list<Param2>::~list(&__x);
        
        stu.nProbility = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgEquipBoxTable::AddEquipBox(&this->m_cfgEquipBoxTalbe, &stu);
        /* CfgEquipBox::~CfgEquipBox(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitEquipDecomposeTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-120h] BYREF
  CfgEquipDecompose stu; // [rsp+A0h] [rbp-90h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+100h] [rbp-30h] BYREF
  char v6; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/EquipDecompose.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_DECOMPOSE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipDecompose::CfgEquipDecompose(&stu);
        nIndex = 0;
        stu.m_nClass = readFile.Search_Posistion( i, 0)->iValue;
        stu.m_nId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.m_vGiveItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.m_nCostMoney = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.m_nLimitType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.m_nLimitValue = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        stu.m_NpcId = readFile.Search_Posistion( i, nIndex++)->iValue;
        CfgEquipTable::AddEquipDecompose(&this->m_cfgEquip, &stu);
        /* CfgEquipDecompose::~CfgEquipDecompose(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitEquipPosSuitTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgEquipPosSuit stu; // [rsp+A0h] [rbp-80h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-60h] BYREF
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  char v6; // [rsp+EFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/EquipPosSuit.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_POS_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgEquipPosSuit::CfgEquipPosSuit(&stu);
        nIndex = 1;
        stu.m_nLevel = readFile.Search_Posistion( i, 1)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/EquipPosSuit.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        CfgEquipTable::AddEquipPosSuit(&this->m_cfgEquip, &stu);
        /* CfgEquipPosSuit::~CfgEquipPosSuit(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitEquipUpPhase()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-100h] BYREF
  cfgEquipUpPhase stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-40h] BYREF
  bool bCombi[18]; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+F2h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-18h]
  int32_t i; // [rsp+FCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/EquipUpPhase.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C7918);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::list<ItemData>::list(&stu.m_CostItems);
        stu.m_CostEquip = TabFile.Search_Posistion( i, 0)->iValue;
        
        v1 = TabFile.Search_Posistion( i, 1);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.m_CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        stu.m_CostMoney = TabFile.Search_Posistion( i, 2)->iValue;
        stu.m_GiveEquip = TabFile.Search_Posistion( i, 3)->iValue;
        stu.m_GongGaoId = TabFile.Search_Posistion( i, 4)->iValue;
        cfgEquipUpPhaseTable::AddData(&this->m_cfgEquipUpPhaseTable, &stu);
        /* cfgEquipUpPhase::~cfgEquipUpPhase(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitExchangeTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-130h] BYREF
  CfgExchange stu; // [rsp+A0h] [rbp-A0h] BYREF
  std::string rewards; // [rsp+D0h] [rbp-70h] BYREF
  std::string items; // [rsp+E0h] [rbp-60h] BYREF
  char v7; // [rsp+EEh] [rbp-52h] BYREF
  char v8; // [rsp+EFh] [rbp-51h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-50h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/JiZiDuiJiang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_EXCHANGE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgExchange::CfgExchange(&stu);
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        items.assign(v1->pString);
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        rewards.assign(v2->pString);
        
        stu.nLimit = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)&items);
        std::list<ItemData>::operator=(&stu.vCost, &strItems);
        std::list<ItemData>::~list(&strItems);
        CItemHelper::parseItemVectorString(&__x, &rewards);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        CfgExchangeTable::Add(&this->m_cfgExchangeTable, &stu);
        /* CfgExchange::~CfgExchange(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitFamilyDonateTable()
{
  ContributionCfg *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-D0h] BYREF
  ContributionCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/FamilyDonate.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C94A0);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,ContributionCfg>::clear(&this->m_ContributionCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCount = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nExp = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nContributionValue = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,ContributionCfg>::operator[](&this->m_ContributionCfgMap, &stu.nId);
        *v1 = stu;
      }
    }
  }
}

//#####################################
ContributionCfg *CfgData::GettFamilyDonateCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,ContributionCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ContributionCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,ContributionCfg>::find(&this->m_ContributionCfgMap, &nIda)._M_node;
  __x._M_node = std::map<int,ContributionCfg>::end(&thisa->m_ContributionCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,ContributionCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,ContributionCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitFamilyDungeonTable()
{
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  CfgFamilyDungeon stu; // [rsp+A0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/FamilyDungeon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_DUNGEON_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.nHard = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nDungeonId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nFamilyLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCostMoney = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 7;
        stu.nBaoKuFuBen = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nNpcId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.X = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.Y = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nTime = TabFile.Search_Posistion( i, nIndex++)->iValue;
        CfgFamilyDungeonTable::AddDungeon(&this->m_cfgFamilyDungeonTable, &stu);
      }
    }
  }
}

//#####################################
void CfgData::fetchActivity()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  int64_t v6; // rax
  int *v7; // rbx
  std::string *v8; // rax
  const char *v9; // rax
  int64_t v10; // rax
  int *v11; // rbx
  std::string *v12; // rax
  const char *v13; // rax
  int64_t v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  size_t v17; // rbx
  int64_t v18; // rax
  std::string *v19; // rax
  const char *v20; // rax
  std::string *v21; // rax
  int64_t v22; // rax
  std::string *v23; // rax
  const char *v24; // rax
  std::string *v25; // rax
  const char *v26; // rax
  std::string *v27; // rax
  int64_t v28; // rax
  std::string *v29; // rax
  const char *v30; // rax
  std::string *v31; // rax
  int64_t v32; // rax
  std::string *v33; // rax
  const char *v34; // rax
  std::string *v35; // rax
  const char *v36; // rax
  size_t v37; // rbx
  CfgActivity *v38; // rax
  const CDBCFile::FIELD *v39; // rax
  const CDBCFile::FIELD *v40; // rax
  int64_t v41; // rax
  std::string *v42; // rax
  const char *v43; // rax
  std::map<int,std::list<CfgMapEvent>> *v44; // rax
  std::list<CfgMapEvent> *v45; // rax
  const CDBCFile::FIELD *v46; // rax
  const CDBCFile::FIELD *v47; // rax
  std::string *v48; // rax
  std::string *v49; // rax
  const char *v50; // rax
  int32_t v51; // ebx
  std::string *v52; // rax
  const char *v53; // rax
  int32_t v54; // eax
  size_t v55; // rbx
  std::string *v56; // rax
  std::string *v57; // rax
  const char *v58; // rax
  int32_t v59; // ebx
  std::string *v60; // rax
  const char *v61; // rax
  int32_t v62; // eax
  size_t v63; // rbx
  CfgActivityMonster *v64; // rax
  const CDBCFile::FIELD *v65; // rax
  int64_t v66; // rax
  std::string *v67; // rax
  const char *v68; // rax
  CfgActivityNpc *v69; // rax
  const CDBCFile::FIELD *v70; // rax
  CfgActivityPlant *v71; // rax
  CfgActivityDrop *v72; // rax
  CfgActivityTrap *v73; // rax
  CDBCFile ActivityTrapFile(0); // [rsp+10h] [rbp-A00h] BYREF
  std::vector<int> v75; // [rsp+A0h] [rbp-970h] BYREF
  int v76; // [rsp+B8h] [rbp-958h]
  std::vector<int> v77; // [rsp+C0h] [rbp-950h] BYREF
  std::vector<int> v78; // [rsp+D8h] [rbp-938h] BYREF
  int iValue; // [rsp+F0h] [rbp-920h]
  int v80; // [rsp+F4h] [rbp-91Ch]
  int v81; // [rsp+F8h] [rbp-918h]
  CDBCFile ActivityDropFile(0); // [rsp+100h] [rbp-910h] BYREF
  CDBCFile ActivityPlantFile(0); // [rsp+190h] [rbp-880h] BYREF
  CDBCFile ActivityNpcFile(0); // [rsp+220h] [rbp-7F0h] BYREF
  CDBCFile ActivityMonsterFile(0); // [rsp+2B0h] [rbp-760h] BYREF
  CDBCFile ActivityEventFile(0); // [rsp+340h] [rbp-6D0h] BYREF
  CDBCFile ActivityFile(0); // [rsp+3D0h] [rbp-640h] BYREF
  CfgActivityPlant plant; // [rsp+460h] [rbp-5B0h] BYREF
  int v89; // [rsp+498h] [rbp-578h]
  std::vector<Position> v90; // [rsp+4A0h] [rbp-570h] BYREF
  int v91; // [rsp+4B8h] [rbp-558h]
  bool v92; // [rsp+4BCh] [rbp-554h]
  CfgActivityTrap trap; // [rsp+4C0h] [rbp-550h] BYREF
  CfgActivityDrop drop; // [rsp+4D0h] [rbp-540h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+4F0h] [rbp-520h] BYREF
  StringVector strRegions; // [rsp+500h] [rbp-510h] BYREF
  std::string regionId; // [rsp+520h] [rbp-4F0h] BYREF
  StringVector vPos_0; // [rsp+530h] [rbp-4E0h] BYREF
  StringVector vRandPos; // [rsp+550h] [rbp-4C0h] BYREF
  StringVector vPos; // [rsp+570h] [rbp-4A0h] BYREF
  StringVector vRoad; // [rsp+590h] [rbp-480h] BYREF
  std::string randpos; // [rsp+5B0h] [rbp-460h] BYREF
  std::string road; // [rsp+5C0h] [rbp-450h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+5D0h] [rbp-440h] BYREF
  StringVector strParams_2; // [rsp+5E0h] [rbp-430h] BYREF
  std::string triggerParam; // [rsp+600h] [rbp-410h] BYREF
  int32_t tstart; // [rsp+60Ch] [rbp-404h] BYREF
  StringVector stritemParams_0; // [rsp+610h] [rbp-400h] BYREF
  StringVector stritemParams; // [rsp+630h] [rbp-3E0h] BYREF
  StringVector vStartHour; // [rsp+650h] [rbp-3C0h] BYREF
  StringVector strParams_1; // [rsp+670h] [rbp-3A0h] BYREF
  StringVector strParams_0; // [rsp+690h] [rbp-380h] BYREF
  StringVector strParams; // [rsp+6B0h] [rbp-360h] BYREF
  StringVector strMaps; // [rsp+6D0h] [rbp-340h] BYREF
  std::string daily; // [rsp+6F0h] [rbp-320h] BYREF
  std::string awards; // [rsp+700h] [rbp-310h] BYREF
  std::string position; // [rsp+710h] [rbp-300h] BYREF
  std::string start_hour; // [rsp+720h] [rbp-2F0h] BYREF
  std::string maps; // [rsp+730h] [rbp-2E0h] BYREF
  char v120; // [rsp+747h] [rbp-2C9h] BYREF
  char v121; // [rsp+748h] [rbp-2C8h] BYREF
  char v122; // [rsp+749h] [rbp-2C7h] BYREF
  char v123; // [rsp+74Ah] [rbp-2C6h] BYREF
  char v124; // [rsp+74Bh] [rbp-2C5h] BYREF
  int __x; // [rsp+74Ch] [rbp-2C4h] BYREF
  std::string delims; // [rsp+750h] [rbp-2C0h] BYREF
  char v127; // [rsp+75Fh] [rbp-2B1h] BYREF
  std::string str; // [rsp+760h] [rbp-2B0h] BYREF
  char v129; // [rsp+76Fh] [rbp-2A1h] BYREF
  std::string v130; // [rsp+770h] [rbp-2A0h] BYREF
  char v131; // [rsp+77Fh] [rbp-291h] BYREF
  std::string v132; // [rsp+780h] [rbp-290h] BYREF
  char v133; // [rsp+78Fh] [rbp-281h] BYREF
  std::string v134; // [rsp+790h] [rbp-280h] BYREF
  char v135; // [rsp+79Fh] [rbp-271h] BYREF
  std::string v136; // [rsp+7A0h] [rbp-270h] BYREF
  char v137; // [rsp+7ABh] [rbp-265h] BYREF
  int v138; // [rsp+7ACh] [rbp-264h] BYREF
  std::string v139; // [rsp+7B0h] [rbp-260h] BYREF
  char v140; // [rsp+7BFh] [rbp-251h] BYREF
  std::string v141; // [rsp+7C0h] [rbp-250h] BYREF
  char v142; // [rsp+7CFh] [rbp-241h] BYREF
  std::string v143; // [rsp+7D0h] [rbp-240h] BYREF
  char v144; // [rsp+7DFh] [rbp-231h] BYREF
  std::string v145; // [rsp+7E0h] [rbp-230h] BYREF
  char v146; // [rsp+7EBh] [rbp-225h] BYREF
  int v147; // [rsp+7ECh] [rbp-224h] BYREF
  std::string v148; // [rsp+7F0h] [rbp-220h] BYREF
  char v149; // [rsp+7FFh] [rbp-211h] BYREF
  std::string v150; // [rsp+800h] [rbp-210h] BYREF
  char v151; // [rsp+80Bh] [rbp-205h] BYREF
  int v152; // [rsp+80Ch] [rbp-204h] BYREF
  StringVector v153; // [rsp+810h] [rbp-200h] BYREF
  std::string v154; // [rsp+830h] [rbp-1E0h] BYREF
  char v155; // [rsp+83Fh] [rbp-1D1h] BYREF
  std::string v156; // [rsp+840h] [rbp-1D0h] BYREF
  char v157; // [rsp+84Bh] [rbp-1C5h] BYREF
  int v158; // [rsp+84Ch] [rbp-1C4h] BYREF
  std::string v159; // [rsp+850h] [rbp-1C0h] BYREF
  char v160; // [rsp+85Eh] [rbp-1B2h] BYREF
  char v161; // [rsp+85Fh] [rbp-1B1h] BYREF
  std::string v162; // [rsp+860h] [rbp-1B0h] BYREF
  char v163; // [rsp+86Fh] [rbp-1A1h] BYREF
  std::string v164; // [rsp+870h] [rbp-1A0h] BYREF
  char v165; // [rsp+87Fh] [rbp-191h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+880h] [rbp-190h] BYREF
  int v167; // [rsp+888h] [rbp-188h] BYREF
  char v168; // [rsp+88Eh] [rbp-182h] BYREF
  char v169; // [rsp+88Fh] [rbp-181h] BYREF
  std::string v170; // [rsp+890h] [rbp-180h] BYREF
  char v171; // [rsp+89Fh] [rbp-171h] BYREF
  std::string v172; // [rsp+8A0h] [rbp-170h] BYREF
  char v173; // [rsp+8AFh] [rbp-161h] BYREF
  Position v174; // [rsp+8B0h] [rbp-160h] BYREF
  std::string v175; // [rsp+8C0h] [rbp-150h] BYREF
  char v176; // [rsp+8CFh] [rbp-141h] BYREF
  std::string v177; // [rsp+8D0h] [rbp-140h] BYREF
  char v178; // [rsp+8DFh] [rbp-131h] BYREF
  Position v179; // [rsp+8E0h] [rbp-130h] BYREF
  char v180; // [rsp+8EFh] [rbp-121h] BYREF
  std::string v181; // [rsp+8F0h] [rbp-120h] BYREF
  char v182; // [rsp+8FFh] [rbp-111h] BYREF
  std::string v183; // [rsp+900h] [rbp-110h] BYREF
  char v184; // [rsp+90Fh] [rbp-101h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v185; // [rsp+910h] [rbp-100h] BYREF
  int v186; // [rsp+91Ch] [rbp-F4h] BYREF
  std::vector<Position> v187; // [rsp+920h] [rbp-F0h] BYREF
  std::string strPos; // [rsp+940h] [rbp-D0h] BYREF
  char v189; // [rsp+956h] [rbp-BAh] BYREF
  int32_t iBaseTableCount; // [rsp+958h] [rbp-B8h]
  int32_t iBaseColumnCount; // [rsp+95Ch] [rbp-B4h]
  int32_t i; // [rsp+960h] [rbp-B0h]
  int32_t weekday; // [rsp+964h] [rbp-ACh]
  int16_t nsize; // [rsp+96Ah] [rbp-A6h]
  int32_t j; // [rsp+96Ch] [rbp-A4h]
  int16_t nsize_0; // [rsp+972h] [rbp-9Eh]
  int32_t j_0; // [rsp+974h] [rbp-9Ch]
  uint32_t j_1; // [rsp+978h] [rbp-98h]
  int32_t nlenth; // [rsp+97Ch] [rbp-94h]
  int32_t j_2; // [rsp+980h] [rbp-90h]
  int32_t nlenth_0; // [rsp+984h] [rbp-8Ch]
  int32_t j_3; // [rsp+988h] [rbp-88h]
  int32_t k; // [rsp+98Ch] [rbp-84h]
  uint32_t j_4; // [rsp+990h] [rbp-80h]
  int32_t iBaseTableCount_Event; // [rsp+998h] [rbp-78h]
  int32_t iBaseColumnCount_Event; // [rsp+99Ch] [rbp-74h]
  int32_t iBaseTableCount_Monster; // [rsp+9A4h] [rbp-6Ch]
  int32_t iBaseColumnCount_Monster; // [rsp+9A8h] [rbp-68h]
  int32_t iBaseTableCount_Npc; // [rsp+9B0h] [rbp-60h]
  int32_t iBaseColumnCount_Npc; // [rsp+9B4h] [rbp-5Ch]
  int32_t iBaseTableCount_Plant; // [rsp+9BCh] [rbp-54h]
  int32_t iBaseColumnCount_Plant; // [rsp+9C0h] [rbp-50h]
  int32_t iBaseTableCount_Drop; // [rsp+9C8h] [rbp-48h]
  int32_t iBaseColumnCount_Drop; // [rsp+9CCh] [rbp-44h]
  int32_t iBaseTableCount_Trap; // [rsp+9D4h] [rbp-3Ch]
  int32_t iBaseColumnCount_Trap; // [rsp+9D8h] [rbp-38h]
  int32_t i_0; // [rsp+9DCh] [rbp-34h]
  int32_t nIndex; // [rsp+9E0h] [rbp-30h]
  int32_t i_1; // [rsp+9E4h] [rbp-2Ch]
  uint32_t j_5; // [rsp+9E8h] [rbp-28h]
  uint32_t j_6; // [rsp+9ECh] [rbp-24h]
  int32_t i_2; // [rsp+9F0h] [rbp-20h]
  int32_t i_3; // [rsp+9F4h] [rbp-1Ch]
  int32_t i_4; // [rsp+9F8h] [rbp-18h]
  int32_t i_5; // [rsp+9FCh] [rbp-14h]

  
  if ( !ActivityFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_activity.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = ActivityFile.GetRecordsNum();
    iBaseColumnCount = ActivityFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgActivity::CfgActivity((CfgActivity *const)&ActivityTrapFile);
        LODWORD(ActivityTrapFile._vptr_CDBCFile) = ActivityFile.Search_Posistion( i, 0)->iValue;
        HIDWORD(ActivityTrapFile.m_pStringBuf) = ActivityFile.Search_Posistion( i, 5)->iValue;
        weekday = ActivityFile.Search_Posistion( i, 9)->iValue;
        LODWORD(ActivityTrapFile.m_theType._M_impl._M_end_of_storage) = ActivityFile.Search_Posistion( i, 10)->iValue;
        HIDWORD(ActivityTrapFile.m_theType._M_impl._M_end_of_storage) = ActivityFile.Search_Posistion( i, 11)->iValue;
        ActivityTrapFile.m_nRecordsNum = ActivityFile.Search_Posistion( i, 12)->iValue;
        
        v1 = ActivityFile.Search_Posistion( i, 13);
        maps.assign(v1->pString);
        
        v2 = ActivityFile.Search_Posistion( i, 14);
        start_hour.assign(v2->pString);
        
        LODWORD(ActivityTrapFile.m_pStringBuf) = ActivityFile.Search_Posistion( i, 15)->iValue;
        
        v3 = ActivityFile.Search_Posistion( i, 17);
        position.assign(v3->pString);
        
        v4 = ActivityFile.Search_Posistion( i, 18);
        awards.assign(v4->pString);
        
        WORD2(ActivityTrapFile._vptr_CDBCFile) = ActivityFile.Search_Posistion( i, 21)->iValue;
        iValue = ActivityFile.Search_Posistion( i, 23)->iValue;
        v80 = ActivityFile.Search_Posistion( i, 24)->iValue;
        v81 = ActivityFile.Search_Posistion( i, 25)->iValue;
        
        v5 = ActivityFile.Search_Posistion( i, 26);
        daily.assign(v5->pString);
        
        LOBYTE(ActivityTrapFile.m_nStringBufSize) = ActivityFile.Search_Posistion( i, 30)->iValue;
        while ( weekday > 0 )
        {
          __x = weekday % 10;
          std::vector<int>::push_back((std::vector<int> *const)&ActivityTrapFile.m_ID, &__x);
          weekday /= 10;
        }
        if ( *(_BYTE *)std::string::c_str(&awards) )
        {
          
          delims = ":";
          
          v6 = std::string::c_str(&awards);
          str.assign(v6);
          Answer::StringUtility::split(&strParams, &str, &delims, 0);
          
          nsize = std::vector<std::string>::size(&strParams);
          switch ( WORD2(ActivityTrapFile._vptr_CDBCFile) )
          {
            case 1:
              nsize = 8;
              break;
            case 6:
              nsize = 1;
              break;
            case 8:
              nsize = 2;
              break;
            case 0xB:
              nsize = 6;
              break;
            case 0xC:
              nsize = 5;
              break;
            default:
              break;
          }
          std::vector<int>::resize(&v77, nsize, 0);
          for ( j = 0; nsize > j; ++j )
          {
            v7 = std::vector<int>::operator[](&v77, j);
            v8 = std::vector<std::string>::operator[](&strParams, j);
            v9 = (const char *)std::string::c_str(v8);
            *v7 = atoi(v9);
          }
          std::vector<std::string>::~vector(&strParams);
        }
        if ( *(_BYTE *)std::string::c_str(&daily) )
        {
          
          v130 = ":";
          
          v10 = std::string::c_str(&daily);
          v132.assign(v10);
          Answer::StringUtility::split(&strParams_0, &v132, &v130, 0);
          
          nsize_0 = std::vector<std::string>::size(&strParams_0);
          std::vector<int>::resize(&v78, nsize_0, 0);
          for ( j_0 = 0; nsize_0 > j_0; ++j_0 )
          {
            v11 = std::vector<int>::operator[](&v78, j_0);
            v12 = std::vector<std::string>::operator[](&strParams_0, j_0);
            v13 = (const char *)std::string::c_str(v12);
            *v11 = atoi(v13);
          }
          std::vector<std::string>::~vector(&strParams_0);
        }
        
        v134 = ":";
        
        v14 = std::string::c_str(&maps);
        v136.assign(v14);
        Answer::StringUtility::split(&strMaps, &v136, &v134, 0);
        
        if ( std::vector<std::string>::size(&strMaps) )
        {
          for ( j_1 = 0; ; ++j_1 )
          {
            v17 = j_1;
            if ( v17 >= std::vector<std::string>::size(&strMaps) )
              break;
            v15 = std::vector<std::string>::operator[](&strMaps, j_1);
            v16 = (const char *)std::string::c_str(v15);
            v138 = atoi(v16);
            std::vector<int>::push_back((std::vector<int> *const)&ActivityTrapFile.m_hashIndex, &v138);
          }
        }
        
        v139 = ":";
        
        v18 = std::string::c_str(&position);
        v141.assign(v18);
        Answer::StringUtility::split(&strParams_1, &v141, &v139, 0);
        
        if ( std::vector<std::string>::size(&strParams_1) == 2 )
        {
          v19 = std::vector<std::string>::operator[](&strParams_1, 0);
          v20 = (const char *)std::string::c_str(v19);
          LODWORD(ActivityTrapFile.m_hashIndex._M_ht._M_buckets._M_impl._M_end_of_storage) = atoi(v20);
          
          v143 = "|";
          
          v21 = std::vector<std::string>::operator[](&strParams_1, 1u);
          v22 = std::string::c_str(v21);
          v145.assign(v22);
          Answer::StringUtility::split(&stritemParams, &v145, &v143, 0);
          
          nlenth = std::vector<std::string>::size(&stritemParams);
          for ( j_2 = 0; j_2 < nlenth; ++j_2 )
          {
            v23 = std::vector<std::string>::operator[](&stritemParams, j_2);
            v24 = (const char *)std::string::c_str(v23);
            v147 = atoi(v24);
            std::vector<int>::push_back(
              (std::vector<int> *const)&ActivityTrapFile.m_hashIndex._M_ht._M_num_elements,
              &v147);
          }
          std::vector<std::string>::~vector(&stritemParams);
        }
        else if ( std::vector<std::string>::size(&strParams_1) == 3 )
        {
          v25 = std::vector<std::string>::operator[](&strParams_1, 0);
          v26 = (const char *)std::string::c_str(v25);
          LODWORD(ActivityTrapFile.m_hashIndex._M_ht._M_buckets._M_impl._M_end_of_storage) = atoi(v26);
          
          v148 = "|";
          
          v27 = std::vector<std::string>::operator[](&strParams_1, 1u);
          v28 = std::string::c_str(v27);
          v150.assign(v28);
          Answer::StringUtility::split(&stritemParams_0, &v150, &v148, 0);
          
          nlenth_0 = std::vector<std::string>::size(&stritemParams_0);
          for ( j_3 = 0; j_3 < nlenth_0; ++j_3 )
          {
            v29 = std::vector<std::string>::operator[](&stritemParams_0, j_3);
            v30 = (const char *)std::string::c_str(v29);
            v152 = atoi(v30);
            std::vector<int>::push_back(
              (std::vector<int> *const)&ActivityTrapFile.m_hashIndex._M_ht._M_num_elements,
              &v152);
          }
          
          v154 = "|";
          
          v31 = std::vector<std::string>::operator[](&strParams_1, 2u);
          v32 = std::string::c_str(v31);
          v156.assign(v32);
          Answer::StringUtility::split(&v153, &v156, &v154, 0);
          std::vector<std::string>::operator=(&stritemParams_0, &v153);
          std::vector<std::string>::~vector(&v153);
          
          nlenth_0 = std::vector<std::string>::size(&stritemParams_0);
          for ( k = 0; k < nlenth_0; ++k )
          {
            v33 = std::vector<std::string>::operator[](&stritemParams_0, k);
            v34 = (const char *)std::string::c_str(v33);
            v158 = atoi(v34);
            std::vector<int>::push_back(&v75, &v158);
          }
          std::vector<std::string>::~vector(&stritemParams_0);
        }
        
        v159 = ":";
        Answer::StringUtility::split(&vStartHour, &start_hour, &v159, 0);
        
        if ( std::vector<std::string>::size(&vStartHour) )
        {
          for ( j_4 = 0; ; ++j_4 )
          {
            v37 = j_4;
            if ( v37 >= std::vector<std::string>::size(&vStartHour) )
              break;
            v35 = std::vector<std::string>::operator[](&vStartHour, j_4);
            v36 = (const char *)std::string::c_str(v35);
            tstart = atoi(v36);
            if ( (unsigned int)tstart < 0x5A0
              && SLODWORD(ActivityTrapFile.m_pStringBuf) >= 0
              && LODWORD(ActivityTrapFile.m_pStringBuf) + tstart <= 1439 )
            {
              std::vector<int>::push_back((std::vector<int> *const)&ActivityTrapFile.m_vDataBuf, &tstart);
            }
            else
            {
              Answer::Logger::print(
                Answer::LogLevel::LOG_LEVEL_ERROR,
                "wrong activity data with id=%d\n",
                LODWORD(ActivityTrapFile._vptr_CDBCFile));
            }
          }
        }
        v76 = 0;
        v38 = std::map<int,CfgActivity>::operator[](&this->m_activities, (const int *const)&ActivityTrapFile);
        CfgActivity::operator=(v38, (const CfgActivity *const)&ActivityTrapFile);
        std::vector<std::string>::~vector(&vStartHour);
        std::vector<std::string>::~vector(&strParams_1);
        std::vector<std::string>::~vector(&strMaps);
        CfgActivity::~CfgActivity((CfgActivity *const)&ActivityTrapFile);
      }
      
      if ( !ActivityEventFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity_event.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_activity_event.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_Event = ActivityEventFile.GetRecordsNum();
        iBaseColumnCount_Event = ActivityEventFile.GetFieldsNum();
        if ( iBaseColumnCount_Event > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount_Event; ++i_0 )
          {
            CfgMapEvent::CfgMapEvent((CfgMapEvent *const)&plant);
            nIndex = 0;
            plant.id = ActivityEventFile.Search_Posistion( i_0, 0)->iValue;
            plant.activity_id = ActivityEventFile.Search_Posistion( i_0, ++nIndex)->iValue;
            plant.plant_id = ActivityEventFile.Search_Posistion( i_0, ++nIndex)->iValue;
            v92 = ActivityEventFile.Search_Posistion( i_0, ++nIndex)->iValue == 0;
            plant.count = ActivityEventFile.Search_Posistion( i_0, ++nIndex)->iValue;
            ++nIndex;
            
            v39 = ActivityEventFile.Search_Posistion( i_0, nIndex);
            triggerParam.assign(v39->pString);
            
            LODWORD(plant.EnterPosVector._M_impl._M_finish) = CDBCFile::Search_Posistion(
                                                                &ActivityEventFile,
                                                                i_0,
                                                                ++nIndex)->iValue;
            v40 = ActivityEventFile.Search_Posistion( i_0, ++nIndex);
            std::string::operator=(&plant.EnterPosVector._M_impl._M_end_of_storage, v40->pString);
            ++nIndex;
            
            v162 = ":";
            
            v41 = std::string::c_str(&triggerParam);
            v164.assign(v41);
            Answer::StringUtility::split(&strParams_2, &v164, &v162, 0);
            
            for ( it._M_current = std::vector<std::string>::begin(&strParams_2)._M_current;
                  __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
            {
              __rhs._M_current = std::vector<std::string>::end(&strParams_2)._M_current;
              if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
                break;
              v42 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
              v43 = (const char *)std::string::c_str(v42);
              v167 = atoi(v43);
              std::vector<int>::push_back((std::vector<int> *const)&plant.wave, &v167);
            }
            v44 = std::map<int,std::map<int,std::list<CfgMapEvent>>>::operator[](&this->m_activityEvents, &plant.id);
            v45 = std::map<int,std::list<CfgMapEvent>>::operator[](v44, &plant.activity_id);
            std::list<CfgMapEvent>::push_back(v45, (const CfgMapEvent *const)&plant);
            std::vector<std::string>::~vector(&strParams_2);
            CfgMapEvent::~CfgMapEvent((CfgMapEvent *const)&plant);
          }
          
          if ( !ActivityMonsterFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity_monster.txt") )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open cfg_activity_monster.txt failed,please check!!");
          }
          else
          {
            iBaseTableCount_Monster = ActivityMonsterFile.GetRecordsNum();
            iBaseColumnCount_Monster = ActivityMonsterFile.GetFieldsNum();
            if ( iBaseColumnCount_Monster > 0 )
            {
              for ( i_1 = 0; i_1 < iBaseTableCount_Monster; ++i_1 )
              {
                CfgActivityMonster::CfgActivityMonster((CfgActivityMonster *const)&plant);
                plant.id = ActivityMonsterFile.Search_Posistion( i_1, 0)->iValue;
                plant.activity_id = ActivityMonsterFile.Search_Posistion( i_1, 1)->iValue;
                plant.plant_id = ActivityMonsterFile.Search_Posistion( i_1, 2)->iValue;
                plant.count = ActivityMonsterFile.Search_Posistion( i_1, 3)->iValue;
                plant.wave = ActivityMonsterFile.Search_Posistion( i_1, 4)->iValue;
                plant.region_id = ActivityMonsterFile.Search_Posistion( i_1, 5)->iValue;
                plant.whoplant = ActivityMonsterFile.Search_Posistion( i_1, 6)->iValue;
                
                v46 = ActivityMonsterFile.Search_Posistion( i_1, 7);
                road.assign(v46->pString);
                
                LODWORD(plant.EnterPosVector._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(
                                                                            &ActivityMonsterFile,
                                                                            i_1,
                                                                            8)->iValue;
                HIDWORD(plant.EnterPosVector._M_impl._M_end_of_storage) = CDBCFile::Search_Posistion(
                                                                            &ActivityMonsterFile,
                                                                            i_1,
                                                                            9)->iValue;
                v89 = ActivityMonsterFile.Search_Posistion( i_1, 10)->iValue;
                
                v47 = ActivityMonsterFile.Search_Posistion( i_1, 11);
                randpos.assign(v47->pString);
                
                v91 = ActivityMonsterFile.Search_Posistion( i_1, 12)->iValue;
                if ( std::string::size(&road) > 3u )
                {
                  
                  v170 = ":";
                  Answer::StringUtility::split(&vRoad, &road, &v170, 0);
                  
                  for ( j_5 = 0; ; ++j_5 )
                  {
                    v55 = j_5;
                    if ( v55 >= std::vector<std::string>::size(&vRoad) )
                      break;
                    
                    v172 = ",";
                    v48 = std::vector<std::string>::operator[](&vRoad, j_5);
                    Answer::StringUtility::split(&vPos, v48, &v172, 0);
                    
                    if ( std::vector<std::string>::size(&vPos) == 2 )
                    {
                      v49 = std::vector<std::string>::operator[](&vPos, 1u);
                      v50 = (const char *)std::string::c_str(v49);
                      v51 = atoi(v50);
                      v52 = std::vector<std::string>::operator[](&vPos, 0);
                      v53 = (const char *)std::string::c_str(v52);
                      v54 = atoi(v53);
                      Position::Position(&v174, v54, v51);
                      std::list<Position>::push_back((std::list<Position> *const)&plant.EnterPosVector, &v174);
                    }
                    std::vector<std::string>::~vector(&vPos);
                  }
                  std::vector<std::string>::~vector(&vRoad);
                }
                if ( std::string::size(&randpos) > 3u )
                {
                  
                  v175 = "|";
                  Answer::StringUtility::split(&vRandPos, &randpos, &v175, 0);
                  
                  for ( j_6 = 0; ; ++j_6 )
                  {
                    v63 = j_6;
                    if ( v63 >= std::vector<std::string>::size(&vRandPos) )
                      break;
                    
                    v177 = ":";
                    v56 = std::vector<std::string>::operator[](&vRandPos, j_6);
                    Answer::StringUtility::split(&vPos_0, v56, &v177, 0);
                    
                    if ( std::vector<std::string>::size(&vPos_0) == 2 )
                    {
                      v57 = std::vector<std::string>::operator[](&vPos_0, 1u);
                      v58 = (const char *)std::string::c_str(v57);
                      v59 = atoi(v58);
                      v60 = std::vector<std::string>::operator[](&vPos_0, 0);
                      v61 = (const char *)std::string::c_str(v60);
                      v62 = atoi(v61);
                      Position::Position(&v179, v62, v59);
                      std::vector<Position>::push_back(&v90, &v179);
                    }
                    std::vector<std::string>::~vector(&vPos_0);
                  }
                  std::vector<std::string>::~vector(&vRandPos);
                }
                v64 = std::map<int,CfgActivityMonster>::operator[](&this->m_activityMonsters, &plant.id);
                CfgActivityMonster::operator=(v64, (const CfgActivityMonster *const)&plant);
                CfgActivityMonster::~CfgActivityMonster((CfgActivityMonster *const)&plant);
              }
              
              if ( !ActivityNpcFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity_npc.txt") )
              {
                Answer::Logger::print(
                  Answer::LogLevel::LOG_LEVEL_ERROR,
                  "open cfg_activity_npc.txt failed,please check!!");
              }
              else
              {
                iBaseTableCount_Npc = ActivityNpcFile.GetRecordsNum();
                iBaseColumnCount_Npc = ActivityNpcFile.GetFieldsNum();
                if ( iBaseColumnCount_Npc > 0 )
                {
                  for ( i_2 = 0; i_2 < iBaseTableCount_Npc; ++i_2 )
                  {
                    CfgActivityNpc::CfgActivityNpc((CfgActivityNpc *const)&plant);
                    plant.id = ActivityNpcFile.Search_Posistion( i_2, 0)->iValue;
                    plant.activity_id = ActivityNpcFile.Search_Posistion( i_2, 1)->iValue;
                    plant.plant_id = ActivityNpcFile.Search_Posistion( i_2, 2)->iValue;
                    plant.count = ActivityNpcFile.Search_Posistion( i_2, 3)->iValue;
                    
                    v65 = ActivityNpcFile.Search_Posistion( i_2, 4);
                    regionId.assign(v65->pString);
                    
                    v181 = ":";
                    
                    v66 = std::string::c_str(&regionId);
                    v183.assign(v66);
                    Answer::StringUtility::split(&strRegions, &v183, &v181, 0);
                    
                    for ( it_0._M_current = std::vector<std::string>::begin(&strRegions)._M_current;
                          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0) )
                    {
                      v185._M_current = std::vector<std::string>::end(&strRegions)._M_current;
                      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v185) )
                        break;
                      v67 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_0);
                      v68 = (const char *)std::string::c_str(v67);
                      v186 = atoi(v68);
                      std::vector<int>::push_back((std::vector<int> *const)&plant.wave, &v186);
                    }
                    v69 = std::map<int,CfgActivityNpc>::operator[](&this->m_activityNpcs, &plant.id);
                    CfgActivityNpc::operator=(v69, (const CfgActivityNpc *const)&plant);
                    std::vector<std::string>::~vector(&strRegions);
                    CfgActivityNpc::~CfgActivityNpc((CfgActivityNpc *const)&plant);
                  }
                  
                  if ( !ActivityPlantFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity_plant.txt") )
                  {
                    Answer::Logger::print(
                      Answer::LogLevel::LOG_LEVEL_ERROR,
                      "open cfg_activity_plant.txt failed,please check!!");
                  }
                  else
                  {
                    iBaseTableCount_Plant = ActivityPlantFile.GetRecordsNum();
                    iBaseColumnCount_Plant = ActivityPlantFile.GetFieldsNum();
                    if ( iBaseColumnCount_Plant > 0 )
                    {
                      for ( i_3 = 0; i_3 < iBaseTableCount_Plant; ++i_3 )
                      {
                        CfgActivityPlant::CfgActivityPlant(&plant);
                        plant.id = ActivityPlantFile.Search_Posistion( i_3, 0)->iValue;
                        plant.activity_id = ActivityPlantFile.Search_Posistion( i_3, 1)->iValue;
                        plant.plant_id = ActivityPlantFile.Search_Posistion( i_3, 2)->iValue;
                        plant.count = ActivityPlantFile.Search_Posistion( i_3, 3)->iValue;
                        plant.wave = ActivityPlantFile.Search_Posistion( i_3, 4)->iValue;
                        plant.region_id = ActivityPlantFile.Search_Posistion( i_3, 5)->iValue;
                        plant.whoplant = ActivityPlantFile.Search_Posistion( i_3, 6)->iValue;
                        
                        v70 = ActivityPlantFile.Search_Posistion( i_3, 7);
                        strPos.assign(v70->pString);
                        CfgData::paresPosition(&v187, this, &strPos);
                        std::vector<Position>::operator=(&plant.EnterPosVector, &v187);
                        std::vector<Position>::~vector(&v187);
                        
                        plant.life_time = ActivityPlantFile.Search_Posistion( i_3, 8)->iValue;
                        v71 = std::map<int,CfgActivityPlant>::operator[](&this->m_activityPlants, &plant.id);
                        CfgActivityPlant::operator=(v71, &plant);
                        /* CfgActivityPlant::~CfgActivityPlant(&plant); - auto cleanup */
                      }
                      
                      if ( !ActivityDropFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity_drop.txt") )
                      {
                        Answer::Logger::print(
                          Answer::LogLevel::LOG_LEVEL_ERROR,
                          "open cfg_activity_drop.txt failed,please check!!");
                      }
                      else
                      {
                        iBaseTableCount_Drop = ActivityDropFile.GetRecordsNum();
                        iBaseColumnCount_Drop = ActivityDropFile.GetFieldsNum();
                        if ( iBaseColumnCount_Drop > 0 )
                        {
                          for ( i_4 = 0; i_4 < iBaseTableCount_Drop; ++i_4 )
                          {
                            drop.id = ActivityDropFile.Search_Posistion( i_4, 0)->iValue;
                            drop.activity_id = ActivityDropFile.Search_Posistion( i_4, 1)->iValue;
                            drop.monster_min_level = ActivityDropFile.Search_Posistion( i_4, 2)->iValue;
                            drop.drop_group_id = ActivityDropFile.Search_Posistion( i_4, 3)->iValue;
                            drop.probability = ActivityDropFile.Search_Posistion( i_4, 4)->iValue;
                            drop.bind_type = ActivityDropFile.Search_Posistion( i_4, 5)->iValue;
                            v72 = std::map<int,CfgActivityDrop>::operator[](&this->m_activityDrops, &drop.id);
                            *v72 = drop;
                          }
                          
                          if ( !ActivityTrapFile.OpenFromTXT( "./ServerConfig/Tables/cfg_activity_trap.txt") )
                          {
                            Answer::Logger::print(
                              Answer::LogLevel::LOG_LEVEL_ERROR,
                              "open cfg_activity_trap.txt failed,please check!!");
                          }
                          else
                          {
                            iBaseTableCount_Trap = ActivityTrapFile.GetRecordsNum();
                            iBaseColumnCount_Trap = ActivityTrapFile.GetFieldsNum();
                            if ( iBaseColumnCount_Trap > 0 )
                            {
                              for ( i_5 = 0; i_5 < iBaseTableCount_Trap; ++i_5 )
                              {
                                trap.id = ActivityTrapFile.Search_Posistion( i_5, 0)->iValue;
                                trap.tid = ActivityTrapFile.Search_Posistion( i_5, 1)->iValue;
                                trap.x = ActivityTrapFile.Search_Posistion( i_5, 2)->iValue;
                                trap.y = ActivityTrapFile.Search_Posistion( i_5, 3)->iValue;
                                v73 = std::map<int,CfgActivityTrap>::operator[](&this->m_activityTraps, &trap.id);
                                *v73 = trap;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchBuff()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgBuff *v3; // rax
  CDBCFile BuffFile(0); // [rsp+10h] [rbp-160h] BYREF
  CfgBuff buff; // [rsp+A0h] [rbp-D0h] BYREF
  BuffAttrVector __x; // [rsp+110h] [rbp-60h] BYREF
  std::string str; // [rsp+130h] [rbp-40h] BYREF
  char v8; // [rsp+13Fh] [rbp-31h] BYREF
  std::string v9; // [rsp+140h] [rbp-30h] BYREF
  char v10; // [rsp+14Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+150h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+154h] [rbp-1Ch]
  int32_t i; // [rsp+158h] [rbp-18h]
  int32_t nIndex; // [rsp+15Ch] [rbp-14h]

  
  if ( !BuffFile.OpenFromTXT( "./ServerConfig/Tables/cfg_buff.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_buff.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = BuffFile.GetRecordsNum();
    iBaseColumnCount = BuffFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgBuff::CfgBuff(&buff);
        buff.id = BuffFile.Search_Posistion( i, nIndex++)->iValue;
        buff.groupid = BuffFile.Search_Posistion( i, nIndex++)->iValue;
        buff.attack_type = BuffFile.Search_Posistion( i, nIndex++)->iValue;
        buff.level = BuffFile.Search_Posistion( i, nIndex++)->iValue;
        ++nIndex;
        buff.beneficial = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.special = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.duration = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.interval = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = BuffFile.Search_Posistion( i, nIndex);
        str.assign(v1->pString);
        CfgData::paraseBuffAttr(&__x, this, &str);
        std::vector<BuffAttr>::operator=(&buff.buffAttr, &__x);
        std::vector<BuffAttr>::~vector(&__x);
        
        ++nIndex;
        buff.isShow = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        buff.modify = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.control = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.hpValue = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.hpPecent = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.shieldValue = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.shieldRatio = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.effectType = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.effectTimes = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.canRemove = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        buff.canRecover = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        
        v2 = BuffFile.Search_Posistion( i, nIndex);
        v9.assign(v2->pString);
        buff.angry = CfgData::paraseParam2(this, &v9);
        
        buff.battle = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,CfgBuff>::operator[](&this->m_buffs, &buff.id);
        CfgBuff::operator=(v3, &buff);
        /* CfgBuff::~CfgBuff(&buff); - auto cleanup */
      }
    }
  }
}

//#####################################
BuffAttrVector *CfgData::paraseBuffAttr(const std::string *const str)
{
  std::string *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  BuffAttr stu; // [rsp+10h] [rbp-A0h] BYREF
  StringVector vBuff; // [rsp+20h] [rbp-90h] BYREF
  StringVector vstr; // [rsp+40h] [rbp-70h] BYREF
  std::string delims; // [rsp+60h] [rbp-50h] BYREF
  char v16; // [rsp+6Fh] [rbp-41h] BYREF
  std::string v17; // [rsp+70h] [rbp-40h] BYREF
  char v18; // [rsp+87h] [rbp-29h] BYREF
  int32_t nSize; // [rsp+88h] [rbp-28h]
  int32_t i; // [rsp+8Ch] [rbp-24h]

  std::vector<BuffAttr>::vector(retstr);
  if ( std::string::size((std::string *)str) > 4u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&vstr, str, &delims, 0);
    
    if ( !std::vector<std::string>::empty(&vstr) )
    {
      nSize = std::vector<std::string>::size(&vstr);
      std::vector<BuffAttr>::reserve(retstr, nSize);
      for ( i = 0; i < nSize; ++i )
      {
        
        v17 = ":";
        v3 = std::vector<std::string>::operator[](&vstr, i);
        Answer::StringUtility::split(&vBuff, v3, &v17, 0);
        
        if ( std::vector<std::string>::size(&vBuff) == 3 )
        {
          *(_QWORD *)&stu.attr = 0;
          stu.addon = 0;
          v4 = std::vector<std::string>::operator[](&vBuff, 0);
          v5 = (const char *)std::string::c_str(v4);
          stu.attr = atoi(v5);
          v6 = std::vector<std::string>::operator[](&vBuff, 1u);
          v7 = (const char *)std::string::c_str(v6);
          stu.ratio = atoi(v7);
          v8 = std::vector<std::string>::operator[](&vBuff, 2u);
          v9 = (const char *)std::string::c_str(v8);
          stu.addon = atoi(v9);
          std::vector<BuffAttr>::push_back(retstr, &stu);
        }
        std::vector<std::string>::~vector(&vBuff);
      }
    }
    std::vector<std::string>::~vector(&vstr);
  }
  return retstr;
}

//#####################################
CurrencyList CfgData::paraseCurrency(const std::string *const str)
{
  const std::string *v2; // rdx
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  CurrencyList result; // rax
  const std::string *stra; // [rsp+0h] [rbp-70h]
  CurrencyStu stu; // [rsp+10h] [rbp-60h] BYREF
  StringVector vstr; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  _BYTE v12[33]; // [rsp+4Fh] [rbp-21h] BYREF

  stra = v2;
  std::list<CurrencyStu>::list((std::list<CurrencyStu> *const)this);
  std::list<CurrencyStu>::clear((std::list<CurrencyStu> *const)this);
  
  delims.assign(":", v12);
  Answer::StringUtility::split(&vstr, stra, &delims, 0);
  
  if ( std::vector<std::string>::size(&vstr) == 2 )
  {
    v3 = std::vector<std::string>::operator[](&vstr, 0);
    v4 = (const char *)std::string::c_str(v3);
    *(_DWORD *)&stu.Type = (unsigned __int8)atoi(v4);
    v5 = std::vector<std::string>::operator[](&vstr, 1u);
    v6 = (const char *)std::string::c_str(v5);
    stu.Values = atoi(v6);
    std::list<CurrencyStu>::push_back((std::list<CurrencyStu> *const)this, &stu);
  }
  std::vector<std::string>::~vector(&vstr);
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
Int32Vector *CfgData::paraseInt32Vector2(const std::string *const str,
        const std::string *const path,
        int32_t size)
{
  const char *v7; // r12
  const char *v8; // rax
  size_t v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+20h] [rbp-80h] BYREF
  StringVector vstr; // [rsp+30h] [rbp-70h] BYREF
  std::string delims; // [rsp+50h] [rbp-50h] BYREF
  char v19; // [rsp+5Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+60h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  int __x[9]; // [rsp+7Ch] [rbp-24h] BYREF

  std::vector<int>::vector(retstr);
  if ( !std::operator==<char>(str, &byte_8C33CF) && !std::operator==<char>(str, "-1") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&vstr, str, &delims, 0);
    
    if ( size > 0 && std::vector<std::string>::size(&vstr) != size )
    {
      v7 = (const char *)std::string::c_str((std::string *)str);
      v8 = (const char *)std::string::c_str((std::string *)path);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::paraseInt32Vector() check size err from %s, where size = %d, str = %s\n",
        v8,
        size,
        v7);
    }
    else
    {
      v9 = std::vector<std::string>::size(&vstr);
      std::vector<int>::reserve(retstr, v9);
      __i._M_current = std::vector<std::string>::begin(&vstr)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iter,
        &__i);
      while ( 1 )
      {
        __rhs._M_current = std::vector<std::string>::end(&vstr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
          break;
        v10 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
        v11 = (const char *)std::string::c_str(v10);
        __x[0] = atoi(v11);
        std::vector<int>::push_back(retstr, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
    }
    std::vector<std::string>::~vector(&vstr);
  }
  return retstr;
}

//#####################################
Int32Vector *CfgData::paraseInt32Vector(const std::string *const str,
        const std::string *const path,
        int32_t size)
{
  const char *v7; // r12
  const char *v8; // rax
  size_t v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+20h] [rbp-80h] BYREF
  StringVector vstr; // [rsp+30h] [rbp-70h] BYREF
  std::string delims; // [rsp+50h] [rbp-50h] BYREF
  char v19; // [rsp+5Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+60h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  int __x[9]; // [rsp+7Ch] [rbp-24h] BYREF

  std::vector<int>::vector(retstr);
  if ( !std::operator==<char>(str, &byte_8C33CF) && !std::operator==<char>(str, "-1") )
  {
    
    delims = ":";
    Answer::StringUtility::split(&vstr, str, &delims, 0);
    
    if ( size > 0 && std::vector<std::string>::size(&vstr) != size )
    {
      v7 = (const char *)std::string::c_str((std::string *)str);
      v8 = (const char *)std::string::c_str((std::string *)path);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::paraseInt32Vector() check size err from %s, where size = %d, str = %s\n",
        v8,
        size,
        v7);
    }
    else
    {
      v9 = std::vector<std::string>::size(&vstr);
      std::vector<int>::reserve(retstr, v9);
      __i._M_current = std::vector<std::string>::begin(&vstr)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iter,
        &__i);
      while ( 1 )
      {
        __rhs._M_current = std::vector<std::string>::end(&vstr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
          break;
        v10 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
        v11 = (const char *)std::string::c_str(v10);
        __x[0] = atoi(v11);
        std::vector<int>::push_back(retstr, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
    }
    std::vector<std::string>::~vector(&vstr);
  }
  return retstr;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
Int32List CfgData::paraseInt32List(const std::string *const str, int32_t size)
{
  int32_t v3; // ecx
  Int32List result; // rax
  std::string *v7; // rax
  const char *v8; // rax
  int32_t sizea; // [rsp+Ch] [rbp-94h]
  const std::string *stra; // [rsp+10h] [rbp-90h]
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+20h] [rbp-80h] BYREF
  StringVector vstr; // [rsp+30h] [rbp-70h] BYREF
  std::string delims; // [rsp+50h] [rbp-50h] BYREF
  char v14; // [rsp+5Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+60h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  int __x[9]; // [rsp+7Ch] [rbp-24h] BYREF

  stra = *(const std::string **)&size;
  sizea = v3;
  std::list<int>::list((std::list<int> *const)this);
  if ( !std::operator==<char>(stra, &byte_8C33CF) && !std::operator==<char>(stra, "-1") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&vstr, stra, &delims, 0);
    
    if ( sizea <= 0 || std::vector<std::string>::size(&vstr) == sizea )
    {
      __i._M_current = std::vector<std::string>::begin(&vstr)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iter,
        &__i);
      while ( 1 )
      {
        __rhs._M_current = std::vector<std::string>::end(&vstr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
          break;
        v7 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
        v8 = (const char *)std::string::c_str(v7);
        __x[0] = atoi(v8);
        std::list<int>::push_back((std::list<int> *const)this, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
    }
    std::vector<std::string>::~vector(&vstr);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
Int32List CfgData::paraseInt32List(const std::string *const str,
        const std::string *const path,
        int32_t size)
{
  int32_t v4; // r8d
  Int32List result; // rax
  const char *v8; // r12
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  int32_t sizea; // [rsp+4h] [rbp-9Ch]
  std::string *patha; // [rsp+8h] [rbp-98h]
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+20h] [rbp-80h] BYREF
  StringVector vstr; // [rsp+30h] [rbp-70h] BYREF
  std::string delims; // [rsp+50h] [rbp-50h] BYREF
  char v18; // [rsp+5Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+60h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  int __x[9]; // [rsp+7Ch] [rbp-24h] BYREF

  patha = *(std::string **)&size;
  sizea = v4;
  std::list<int>::list((std::list<int> *const)this);
  if ( !std::operator==<char>(path, &byte_8C33CF) && !std::operator==<char>(path, "-1") )
  {
    
    delims = ":";
    Answer::StringUtility::split(&vstr, path, &delims, 0);
    
    if ( sizea > 0 && std::vector<std::string>::size(&vstr) != sizea )
    {
      v8 = (const char *)std::string::c_str((std::string *)path);
      v9 = (const char *)std::string::c_str(patha);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::paraseInt32List() check size err from %s, where size = %d, str = %s\n",
        v9,
        sizea,
        v8);
    }
    else
    {
      __i._M_current = std::vector<std::string>::begin(&vstr)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iter,
        &__i);
      while ( 1 )
      {
        __rhs._M_current = std::vector<std::string>::end(&vstr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
          break;
        v10 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
        v11 = (const char *)std::string::c_str(v10);
        __x[0] = atoi(v11);
        std::list<int>::push_back((std::list<int> *const)this, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
    }
    std::vector<std::string>::~vector(&vstr);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
Int32VtVector *CfgData::paraseInt32VtVector(const std::string *const str,
        const std::string *const path)
{
  size_t v5; // rax
  const std::string *v6; // rax
  size_t v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+20h] [rbp-100h] BYREF
  StringVector vstr; // [rsp+30h] [rbp-F0h] BYREF
  Int32Vector probability; // [rsp+50h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+70h] [rbp-B0h] BYREF
  StringVector SplitStr; // [rsp+80h] [rbp-A0h] BYREF
  std::string delims; // [rsp+A0h] [rbp-80h] BYREF
  char v18; // [rsp+AFh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+B0h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v20; // [rsp+C0h] [rbp-60h] BYREF
  std::string v21; // [rsp+D0h] [rbp-50h] BYREF
  char v22; // [rsp+DFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v23; // [rsp+E0h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+F0h] [rbp-30h] BYREF
  int __x[9]; // [rsp+FCh] [rbp-24h] BYREF

  std::vector<std::vector<int>>::vector(retstr);
  if ( !std::operator==<char>(str, &byte_8C33CF) && !std::operator==<char>(str, "-1") )
  {
    std::vector<std::vector<int>>::clear(retstr);
    
    delims = "|";
    Answer::StringUtility::split(&SplitStr, str, &delims, 0);
    
    v5 = std::vector<std::string>::size(&SplitStr);
    std::vector<std::vector<int>>::reserve(retstr, v5);
    __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
    __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
      &iterBegin,
      &__i);
    while ( 1 )
    {
      v20._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
      if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &v20) )
        break;
      /* std::vector<int>::vector(&probability); */
      
      v21 = ":";
      v6 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
      Answer::StringUtility::split(&vstr, v6, &v21, 0);
      
      v7 = std::vector<std::string>::size(&vstr);
      std::vector<int>::reserve(&probability, v7);
      v23._M_current = std::vector<std::string>::begin(&vstr)._M_current;
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
        &iter,
        &v23);
      while ( 1 )
      {
        __rhs._M_current = std::vector<std::string>::end(&vstr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
          break;
        v8 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
        v9 = (const char *)std::string::c_str(v8);
        __x[0] = atoi(v9);
        std::vector<int>::push_back(&probability, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
      std::vector<std::vector<int>>::push_back(retstr, &probability);
      std::vector<std::string>::~vector(&vstr);
      std::vector<int>::~vector(&probability);
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
    }
    std::vector<std::string>::~vector(&SplitStr);
  }
  return retstr;
}

//#####################################
Param2 CfgData::paraseParam2(const std::string *const str)
{
  Param2 v3; // rbx
  std::string *v4; // rax
  const char *v5; // rax
  int32_t v6; // ebx
  std::string *v7; // rax
  const char *v8; // rax
  int32_t v9; // eax
  StringVector vParam; // [rsp+10h] [rbp-70h] BYREF
  Param2 v11; // [rsp+30h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-40h] BYREF
  char v13; // [rsp+4Fh] [rbp-31h] BYREF
  Param2 v14; // [rsp+50h] [rbp-30h] BYREF
  Param2 v15; // [rsp+60h] [rbp-20h] BYREF

  if ( std::operator==<char>(str, &byte_8C33CF) || std::operator==<char>(str, "-1") )
  {
    Param2::Param2(&v11, 0, 0);
    return v11;
  }
  else
  {
    
    delims = ":";
    Answer::StringUtility::split(&vParam, str, &delims, 0);
    
    if ( std::vector<std::string>::size(&vParam) == 2 )
    {
      v4 = std::vector<std::string>::operator[](&vParam, 1u);
      v5 = (const char *)std::string::c_str(v4);
      v6 = atoi(v5);
      v7 = std::vector<std::string>::operator[](&vParam, 0);
      v8 = (const char *)std::string::c_str(v7);
      v9 = atoi(v8);
      Param2::Param2(&v14, v9, v6);
      v3 = v14;
    }
    else
    {
      Param2::Param2(&v15, 0, 0);
      v3 = v15;
    }
    std::vector<std::string>::~vector(&vParam);
  }
  return v3;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
Param2List CfgData::paraseParam2List(const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v4; // r8
  Param2List result; // rax
  std::string *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  int32_t v10; // r12d
  std::string *v11; // rax
  const char *v12; // rax
  int32_t v13; // eax
  const char *v14; // r12
  const char *v15; // rax
  std::string *patha; // [rsp+0h] [rbp-D0h]
  int32_t nIndexa; // [rsp+Ch] [rbp-C4h]
  std::string *stra; // [rsp+10h] [rbp-C0h]
  StringVector vParam; // [rsp+20h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-90h] BYREF
  StringVector strParams; // [rsp+50h] [rbp-80h] BYREF
  std::string delims; // [rsp+70h] [rbp-60h] BYREF
  char v23; // [rsp+7Fh] [rbp-51h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-50h] BYREF
  std::string v25; // [rsp+90h] [rbp-40h] BYREF
  char v26; // [rsp+9Fh] [rbp-31h] BYREF
  Param2 __x; // [rsp+A0h] [rbp-30h] BYREF

  stra = *(std::string **)&nIndex;
  nIndexa = (int)path;
  patha = v4;
  std::list<Param2>::list((std::list<Param2> *const)this);
  if ( !std::operator==<char>(stra, &byte_8C33CF) && !std::operator==<char>(stra, "-1") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&strParams, stra, &delims, 0);
    
    for ( iter._M_current = std::vector<std::string>::begin(&strParams)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strParams)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      
      v25 = ":";
      v7 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&vParam, v7, &v25, 0);
      
      if ( std::vector<std::string>::size(&vParam) == 2 )
      {
        v8 = std::vector<std::string>::operator[](&vParam, 1u);
        v9 = (const char *)std::string::c_str(v8);
        v10 = atoi(v9);
        v11 = std::vector<std::string>::operator[](&vParam, 0);
        v12 = (const char *)std::string::c_str(v11);
        v13 = atoi(v12);
        Param2::Param2(&__x, v13, v10);
        std::list<Param2>::push_back((std::list<Param2> *const)this, &__x);
      }
      else
      {
        v14 = (const char *)std::string::c_str(stra);
        v15 = (const char *)std::string::c_str(patha);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::paraseParam2List() wrong data from %s, where index = %d, str = %s\n",
          v15,
          nIndexa,
          v14);
      }
      std::vector<std::string>::~vector(&vParam);
    }
    std::vector<std::string>::~vector(&strParams);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
void CfgData::fetchDungeon()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  CfgDungeon *v8; // rax
  CfgDungeon *v9; // rax
  CfgDungeonReward *v10; // rax
  CfgDungeonDropGroup *v11; // rax
  int64_t v12; // rax
  CfgDungeon dungeon; // [rsp+10h] [rbp-480h] BYREF
  CDBCFile DungeonDropFile(0); // [rsp+130h] [rbp-360h] BYREF
  CDBCFile DungeonRewardFile(0); // [rsp+1C0h] [rbp-2D0h] BYREF
  CDBCFile DungeonFile(0); // [rsp+250h] [rbp-240h] BYREF
  int32_t id; // [rsp+2ECh] [rbp-1A4h] BYREF
  CfgDungeonDrop group; // [rsp+2F0h] [rbp-1A0h] BYREF
  CfgDungeonReward reward; // [rsp+310h] [rbp-180h] BYREF
  std::string strItem; // [rsp+330h] [rbp-160h] BYREF
  char v21; // [rsp+33Fh] [rbp-151h] BYREF
  MemChrBagVector __x; // [rsp+340h] [rbp-150h] BYREF
  std::string strItems; // [rsp+360h] [rbp-130h] BYREF
  char v24; // [rsp+36Fh] [rbp-121h] BYREF
  MemChrBagVector v25; // [rsp+370h] [rbp-120h] BYREF
  std::string v26; // [rsp+390h] [rbp-100h] BYREF
  char v27; // [rsp+39Fh] [rbp-F1h] BYREF
  Int32Vector v28; // [rsp+3A0h] [rbp-F0h] BYREF
  std::string path; // [rsp+3C0h] [rbp-D0h] BYREF
  char v30; // [rsp+3CFh] [rbp-C1h] BYREF
  std::string str; // [rsp+3D0h] [rbp-C0h] BYREF
  char v32; // [rsp+3DFh] [rbp-B1h] BYREF
  MemChrBagVector v33; // [rsp+3E0h] [rbp-B0h] BYREF
  std::string v34; // [rsp+400h] [rbp-90h] BYREF
  char v35; // [rsp+40Fh] [rbp-81h] BYREF
  Int32Vector v36; // [rsp+410h] [rbp-80h] BYREF
  std::string v37; // [rsp+430h] [rbp-60h] BYREF
  char v38; // [rsp+43Fh] [rbp-51h] BYREF
  std::string v39; // [rsp+440h] [rbp-50h] BYREF
  char v40; // [rsp+44Ah] [rbp-46h] BYREF
  int32_t iBaseTableCount; // [rsp+44Ch] [rbp-44h]
  int32_t iBaseColumnCount; // [rsp+450h] [rbp-40h]
  int32_t nIndex; // [rsp+454h] [rbp-3Ch]
  int32_t iBaseTableCount_Reward; // [rsp+45Ch] [rbp-34h]
  int32_t iBaseColumnCount_Reward; // [rsp+460h] [rbp-30h]
  int32_t iBaseTableCount_Drop; // [rsp+468h] [rbp-28h]
  int32_t iBaseColumnCount_Drop; // [rsp+46Ch] [rbp-24h]
  int32_t i; // [rsp+470h] [rbp-20h]
  int32_t weekday; // [rsp+474h] [rbp-1Ch]
  int32_t i_0; // [rsp+478h] [rbp-18h]
  int32_t i_1; // [rsp+47Ch] [rbp-14h]
  ItemData v55; // 0:kr00_12.12

  
  if ( !DungeonFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonFile.GetRecordsNum();
    iBaseColumnCount = DungeonFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      nIndex = 0;
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&dungeon, 0, sizeof(dungeon));
        std::string::string(&dungeon.name);
        /* std::vector<MemChrBag>::vector(&dungeon.rewardOnce); */
        /* std::vector<MemChrBag>::vector(&dungeon.rewardItem); */
        /* std::vector<int>::vector(&dungeon.win_star); */
        /* std::vector<MemChrBag>::vector(&dungeon.star_reward); */
        /* std::vector<int>::vector(&dungeon.star_ratio); */
        dungeon.id = DungeonFile.Search_Posistion( i, nIndex++)->iValue;
        v1 = DungeonFile.Search_Posistion( i, nIndex);
        std::string::operator=(&dungeon.name, v1->pString);
        ++nIndex;
        ++nIndex;
        dungeon.mapid = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.x = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.y = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.type = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.sequence = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.group_id = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.duration = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.job = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.level = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.maxLevel = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.vip = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.player_num = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        weekday = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.start_hour = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.end_hour = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.daily_count = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        dungeon.last_id = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.next_id = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.player_buff = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.star = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.double_cost = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.reward_time = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        
        v2 = DungeonFile.Search_Posistion( i, nIndex);
        strItem.assign(v2->pString);
        v55 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v12) = v55.m_nId;
        BYTE4(v12) = v55.m_nClass;
        *(_QWORD *)&dungeon.costItem.m_nId = v12;
        dungeon.costItem.m_nCount = v55.m_nCount;
        
        ++nIndex;
        
        v3 = DungeonFile.Search_Posistion( i, nIndex);
        strItems.assign(v3->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&dungeon.rewardItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v4 = DungeonFile.Search_Posistion( i, nIndex);
        v26.assign(v4->pString);
        CItemHelper::parseItemVectorString(&v25, &v26);
        std::vector<MemChrBag>::operator=(&dungeon.rewardOnce, &v25);
        std::vector<MemChrBag>::~vector(&v25);
        
        ++nIndex;
        dungeon.Battle = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.costMoney = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.costGold = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.buyTimes = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.buyCost = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.quickDoneCost = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.quickDoneDrop = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.needUpTowerStar = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.summon_cost = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.summon_boss = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.rand_time = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        dungeon.task_id = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        dungeon.stay_position = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/cfg_dungeon.txt";
        
        v5 = DungeonFile.Search_Posistion( i, nIndex);
        str.assign(v5->pString);
        CfgData::paraseInt32Vector(&v28, this, &str, &path, 0);
        std::vector<int>::operator=(&dungeon.win_star, &v28);
        std::vector<int>::~vector(&v28);
        
        ++nIndex;
        
        v6 = DungeonFile.Search_Posistion( i, nIndex);
        v34.assign(v6->pString);
        CItemHelper::parseItemVectorString(&v33, &v34);
        std::vector<MemChrBag>::operator=(&dungeon.star_reward, &v33);
        std::vector<MemChrBag>::~vector(&v33);
        
        ++nIndex;
        
        v37 = "./ServerConfig/Tables/cfg_dungeon.txt";
        
        v7 = DungeonFile.Search_Posistion( i, nIndex);
        v39.assign(v7->pString);
        CfgData::paraseInt32Vector(&v36, this, &v39, &v37, 0);
        std::vector<int>::operator=(&dungeon.star_ratio, &v36);
        std::vector<int>::~vector(&v36);
        
        ++nIndex;
        dungeon.TeQuan = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.backMapId = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.backX = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.backY = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        dungeon.CanEnter = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        dungeon.BuffId = DungeonFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        while ( weekday > 0 )
        {
          dungeon.weekday |= 1 << ((char)weekday % 10);
          weekday /= 10;
        }
        v8 = std::map<int,CfgDungeon>::operator[](&this->m_dungeons, &dungeon.id);
        CfgDungeon::operator=(v8, &dungeon);
        if ( dungeon.type == 16 )
        {
          v9 = std::map<int,CfgDungeon>::operator[](&this->m_mUpTowerDungeon, &dungeon.star);
          CfgDungeon::operator=(v9, &dungeon);
        }
        /* CfgDungeon::~CfgDungeon(&dungeon); - auto cleanup */
      }
      
      if ( !DungeonRewardFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_reward.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_reward.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_Reward = DungeonRewardFile.GetRecordsNum();
        iBaseColumnCount_Reward = DungeonRewardFile.GetFieldsNum();
        if ( iBaseColumnCount_Reward > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount_Reward; ++i_0 )
          {
            reward.dungeonID = DungeonRewardFile.Search_Posistion( i_0, 0)->iValue;
            reward.exp = DungeonRewardFile.Search_Posistion( i_0, 1)->iValue;
            reward.money = DungeonRewardFile.Search_Posistion( i_0, 2)->iValue;
            reward.cash = DungeonRewardFile.Search_Posistion( i_0, 3)->iValue;
            reward.groupID = DungeonRewardFile.Search_Posistion( i_0, 4)->iValue;
            v10 = std::map<int,CfgDungeonReward>::operator[](&this->m_dungeonReward, &reward.dungeonID);
            *v10 = reward;
          }
          
          if ( !DungeonDropFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_drop_group.txt") )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open cfg_dungeon_drop_group.txt failed,please check!!");
          }
          else
          {
            iBaseTableCount_Drop = DungeonDropFile.GetRecordsNum();
            iBaseColumnCount_Drop = DungeonDropFile.GetFieldsNum();
            if ( iBaseColumnCount_Drop > 0 )
            {
              for ( i_1 = 0; i_1 < iBaseTableCount_Drop; ++i_1 )
              {
                id = DungeonDropFile.Search_Posistion( i_1, 0)->iValue;
                group.type = DungeonDropFile.Search_Posistion( i_1, 1)->iValue;
                group.item_id = DungeonDropFile.Search_Posistion( i_1, 3)->iValue;
                group.item_class = DungeonDropFile.Search_Posistion( i_1, 4)->iValue;
                group.bind_type = DungeonDropFile.Search_Posistion( i_1, 5)->iValue;
                group.count = DungeonDropFile.Search_Posistion( i_1, 6)->iValue;
                group.weight = DungeonDropFile.Search_Posistion( i_1, 7)->iValue;
                group.probability = DungeonDropFile.Search_Posistion( i_1, 8)->iValue;
                v11 = std::map<int,CfgDungeonDropGroup>::operator[](&this->m_dungeonDropGroup, &id);
                CfgDungeonDropGroup::Add(v11, &group);
              }
            }
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonEvent()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  int64_t v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::list<CfgMapEvent> *v6; // rax
  CDBCFile DungeonEventFile(0); // [rsp+10h] [rbp-180h] BYREF
  CfgMapEvent dungeonEvent; // [rsp+A0h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+100h] [rbp-90h] BYREF
  StringVector strTriggerParam; // [rsp+110h] [rbp-80h] BYREF
  std::string triggerParam; // [rsp+130h] [rbp-60h] BYREF
  char v12; // [rsp+13Fh] [rbp-51h] BYREF
  std::string delims; // [rsp+140h] [rbp-50h] BYREF
  char v14; // [rsp+14Fh] [rbp-41h] BYREF
  std::string str; // [rsp+150h] [rbp-40h] BYREF
  char v16; // [rsp+15Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+160h] [rbp-30h] BYREF
  int __x; // [rsp+16Ch] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+174h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+178h] [rbp-18h]
  int32_t i; // [rsp+17Ch] [rbp-14h]

  
  if ( !DungeonEventFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_event.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_event.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonEventFile.GetRecordsNum();
    iBaseColumnCount = DungeonEventFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgMapEvent::CfgMapEvent(&dungeonEvent);
        dungeonEvent.id = DungeonEventFile.Search_Posistion( i, 0)->iValue;
        dungeonEvent.trigger_id = DungeonEventFile.Search_Posistion( i, 1)->iValue;
        dungeonEvent.bInitOpen = DungeonEventFile.Search_Posistion( i, 2)->iValue == 0;
        dungeonEvent.trigger_type = DungeonEventFile.Search_Posistion( i, 3)->iValue;
        
        v1 = DungeonEventFile.Search_Posistion( i, 4);
        triggerParam.assign(v1->pString);
        
        dungeonEvent.event_type = DungeonEventFile.Search_Posistion( i, 5)->iValue;
        v2 = DungeonEventFile.Search_Posistion( i, 6);
        std::string::operator=(&dungeonEvent.effect, v2->pString);
        dungeonEvent.repeate = DungeonEventFile.Search_Posistion( i, 7)->iValue;
        
        delims = ":";
        
        v3 = std::string::c_str(&triggerParam);
        str.assign(v3);
        Answer::StringUtility::split(&strTriggerParam, &str, &delims, 0);
        
        for ( it._M_current = std::vector<std::string>::begin(&strTriggerParam)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strTriggerParam)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v5 = (const char *)std::string::c_str(v4);
          __x = atoi(v5);
          std::vector<int>::push_back(&dungeonEvent.trigger_param, &__x);
        }
        if ( !std::vector<int>::empty(&dungeonEvent.trigger_param) )
        {
          v6 = std::map<int,std::list<CfgMapEvent>>::operator[](&this->m_dungeonEvents, &dungeonEvent.id);
          std::list<CfgMapEvent>::push_back(v6, &dungeonEvent);
        }
        std::vector<std::string>::~vector(&strTriggerParam);
        /* CfgMapEvent::~CfgMapEvent(&dungeonEvent); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonMonster()
{
  unsigned int id; // r12d
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  int32_t v8; // ebx
  std::string *v9; // rax
  const char *v10; // rax
  int32_t v11; // eax
  size_t v12; // rbx
  std::string *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  int32_t v16; // ebx
  std::string *v17; // rax
  const char *v18; // rax
  int32_t v19; // eax
  size_t v20; // rbx
  CfgDungeonMonster *v21; // rax
  CDBCFile DungeonMonsterFile(0); // [rsp+10h] [rbp-250h] BYREF
  CfgDungeonMonster monster; // [rsp+A0h] [rbp-1C0h] BYREF
  StringVector vPos_0; // [rsp+110h] [rbp-150h] BYREF
  StringVector vRandPos; // [rsp+130h] [rbp-130h] BYREF
  StringVector vPos; // [rsp+150h] [rbp-110h] BYREF
  StringVector vRoad; // [rsp+170h] [rbp-F0h] BYREF
  std::string randpos; // [rsp+190h] [rbp-D0h] BYREF
  std::string road; // [rsp+1A0h] [rbp-C0h] BYREF
  std::list<Param2> __x; // [rsp+1B0h] [rbp-B0h] BYREF
  _BYTE v31[15]; // [rsp+1C0h] [rbp-A0h] BYREF
  char v32; // [rsp+1CFh] [rbp-91h] BYREF
  int32_t nIndex[3]; // [rsp+1D0h] [rbp-90h] BYREF
  char v34; // [rsp+1DDh] [rbp-83h] BYREF
  char v35; // [rsp+1DEh] [rbp-82h] BYREF
  char v36; // [rsp+1DFh] [rbp-81h] BYREF
  std::string delims; // [rsp+1E0h] [rbp-80h] BYREF
  char v38; // [rsp+1EFh] [rbp-71h] BYREF
  std::string v39; // [rsp+1F0h] [rbp-70h] BYREF
  char v40; // [rsp+1FFh] [rbp-61h] BYREF
  Position v41; // [rsp+200h] [rbp-60h] BYREF
  std::string v42; // [rsp+210h] [rbp-50h] BYREF
  char v43; // [rsp+21Fh] [rbp-41h] BYREF
  std::string v44; // [rsp+220h] [rbp-40h] BYREF
  char v45; // [rsp+22Fh] [rbp-31h] BYREF
  Position v46; // [rsp+230h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+23Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+240h] [rbp-20h]
  int32_t i; // [rsp+244h] [rbp-1Ch]
  uint32_t j; // [rsp+248h] [rbp-18h]
  uint32_t j_0; // [rsp+24Ch] [rbp-14h]

  
  if ( !DungeonMonsterFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_monster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_monster.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonMonsterFile.GetRecordsNum();
    iBaseColumnCount = DungeonMonsterFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgDungeonMonster::CfgDungeonMonster(&monster);
        monster.id = DungeonMonsterFile.Search_Posistion( i, 0)->iValue;
        monster.wave = DungeonMonsterFile.Search_Posistion( i, 1)->iValue;
        
        std::string::string(v31, "./ServerConfig/Tables/cfg_dungeon_monster.txt", &v32);
        id = monster.id;
        
        v2 = DungeonMonsterFile.Search_Posistion( i, 2);
        std::string::string(nIndex, v2->pString, &v34);
        CfgData::paraseParam2List(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)nIndex,
          (const std::string *const)id);
        std::list<Param2>::operator=(&monster.mids, &__x);
        std::list<Param2>::~list(&__x);
        
        monster.x = DungeonMonsterFile.Search_Posistion( i, 3)->iValue;
        monster.y = DungeonMonsterFile.Search_Posistion( i, 4)->iValue;
        monster.count = DungeonMonsterFile.Search_Posistion( i, 5)->iValue;
        monster.side = DungeonMonsterFile.Search_Posistion( i, 6)->iValue;
        
        v3 = DungeonMonsterFile.Search_Posistion( i, 7);
        road.assign(v3->pString);
        
        monster.delay = DungeonMonsterFile.Search_Posistion( i, 8)->iValue;
        monster.times = DungeonMonsterFile.Search_Posistion( i, 9)->iValue;
        monster.money = DungeonMonsterFile.Search_Posistion( i, 10)->iValue;
        monster.life = DungeonMonsterFile.Search_Posistion( i, 11)->iValue;
        
        v4 = DungeonMonsterFile.Search_Posistion( i, 12);
        randpos.assign(v4->pString);
        
        monster.wait = DungeonMonsterFile.Search_Posistion( i, 13)->iValue;
        if ( std::string::size(&road) > 3u )
        {
          
          delims = ":";
          Answer::StringUtility::split(&vRoad, &road, &delims, 0);
          
          for ( j = 0; ; ++j )
          {
            v12 = j;
            if ( v12 >= std::vector<std::string>::size(&vRoad) )
              break;
            
            v39 = ",";
            v5 = std::vector<std::string>::operator[](&vRoad, j);
            Answer::StringUtility::split(&vPos, v5, &v39, 0);
            
            if ( std::vector<std::string>::size(&vPos) == 2 )
            {
              v6 = std::vector<std::string>::operator[](&vPos, 1u);
              v7 = (const char *)std::string::c_str(v6);
              v8 = atoi(v7);
              v9 = std::vector<std::string>::operator[](&vPos, 0);
              v10 = (const char *)std::string::c_str(v9);
              v11 = atoi(v10);
              Position::Position(&v41, v11, v8);
              std::list<Position>::push_back(&monster.road, &v41);
            }
            std::vector<std::string>::~vector(&vPos);
          }
          std::vector<std::string>::~vector(&vRoad);
        }
        if ( std::string::size(&randpos) > 3u )
        {
          
          v42 = "|";
          Answer::StringUtility::split(&vRandPos, &randpos, &v42, 0);
          
          for ( j_0 = 0; ; ++j_0 )
          {
            v20 = j_0;
            if ( v20 >= std::vector<std::string>::size(&vRandPos) )
              break;
            
            v44 = ":";
            v13 = std::vector<std::string>::operator[](&vRandPos, j_0);
            Answer::StringUtility::split(&vPos_0, v13, &v44, 0);
            
            if ( std::vector<std::string>::size(&vPos_0) == 2 )
            {
              v14 = std::vector<std::string>::operator[](&vPos_0, 1u);
              v15 = (const char *)std::string::c_str(v14);
              v16 = atoi(v15);
              v17 = std::vector<std::string>::operator[](&vPos_0, 0);
              v18 = (const char *)std::string::c_str(v17);
              v19 = atoi(v18);
              Position::Position(&v46, v19, v16);
              std::vector<Position>::push_back(&monster.randpos, &v46);
            }
            std::vector<std::string>::~vector(&vPos_0);
          }
          std::vector<std::string>::~vector(&vRandPos);
        }
        v21 = std::map<int,CfgDungeonMonster>::operator[](&this->m_dungeonMonsters, &monster.id);
        CfgDungeonMonster::operator=(v21, &monster);
        /* CfgDungeonMonster::~CfgDungeonMonster(&monster); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonPlant()
{
  CfgDungeonPlant *v1; // rax
  CDBCFile DungeonPlantFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgDungeonPlant dungeonPlant; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  
  if ( !DungeonPlantFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_plant.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_plant.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonPlantFile.GetRecordsNum();
    iBaseColumnCount = DungeonPlantFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        dungeonPlant.id = DungeonPlantFile.Search_Posistion( i, 0)->iValue;
        dungeonPlant.pid = DungeonPlantFile.Search_Posistion( i, 1)->iValue;
        dungeonPlant.x = DungeonPlantFile.Search_Posistion( i, 2)->iValue;
        dungeonPlant.y = DungeonPlantFile.Search_Posistion( i, 3)->iValue;
        v1 = std::map<int,CfgDungeonPlant>::operator[](&this->m_dungeonPlants, &dungeonPlant.id);
        *v1 = dungeonPlant;
      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonTrap()
{
  CfgDungeonTrap *v1; // rax
  CDBCFile DungeonTrapFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgDungeonTrap dungeonTrap; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  
  if ( !DungeonTrapFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_trap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_trap.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonTrapFile.GetRecordsNum();
    iBaseColumnCount = DungeonTrapFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        dungeonTrap.id = DungeonTrapFile.Search_Posistion( i, 0)->iValue;
        dungeonTrap.tid = DungeonTrapFile.Search_Posistion( i, 1)->iValue;
        dungeonTrap.x = DungeonTrapFile.Search_Posistion( i, 2)->iValue;
        dungeonTrap.y = DungeonTrapFile.Search_Posistion( i, 3)->iValue;
        v1 = std::map<int,CfgDungeonTrap>::operator[](&this->m_dungeonTraps, &dungeonTrap.id);
        *v1 = dungeonTrap;
      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonNpc()
{
  CfgDungeonNpc *v1; // rax
  CDBCFile DungeonTrapFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgDungeonNpc dungeonNpc; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  
  if ( !DungeonTrapFile.OpenFromTXT( "./ServerConfig/Tables/cfg_dungeon_npc.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_dungeon_npc.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = DungeonTrapFile.GetRecordsNum();
    iBaseColumnCount = DungeonTrapFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        dungeonNpc.id = DungeonTrapFile.Search_Posistion( i, 0)->iValue;
        dungeonNpc.NpcId = DungeonTrapFile.Search_Posistion( i, 1)->iValue;
        dungeonNpc.x = DungeonTrapFile.Search_Posistion( i, 2)->iValue;
        dungeonNpc.y = DungeonTrapFile.Search_Posistion( i, 3)->iValue;
        v1 = std::map<int,CfgDungeonNpc>::operator[](&this->m_dungeonNpcs, &dungeonNpc.id);
        *v1 = dungeonNpc;
      }
    }
  }
}

//#####################################
void CfgData::fetchChrShop()
{
  CfgChrShop *v1; // rax
  CDBCFile ChrShopFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgChrShop chrShop; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !ChrShopFile.OpenFromTXT( "./ServerConfig/Tables/cfg_chr_shop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_chr_shop.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = ChrShopFile.GetRecordsNum();
    iBaseColumnCount = ChrShopFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        chrShop.Index = ChrShopFile.Search_Posistion( i, 0)->iValue;
        chrShop.ItemId = ChrShopFile.Search_Posistion( i, 1)->iValue;
        chrShop.ItemClass = ChrShopFile.Search_Posistion( i, 2)->iValue;
        chrShop.IsBind = ChrShopFile.Search_Posistion( i, 3)->iValue;
        chrShop.LimitCount = ChrShopFile.Search_Posistion( i, 4)->iValue;
        chrShop.Price = ChrShopFile.Search_Posistion( i, 5)->iValue;
        chrShop.ConstType = ChrShopFile.Search_Posistion( i, 9)->iValue;
        chrShop.QiQinglevel = ChrShopFile.Search_Posistion( i, 10)->iValue;
        v1 = std::map<int,CfgChrShop>::operator[](&this->m_chrShops, &chrShop.Index);
        *v1 = chrShop;
      }
    }
  }
}

//#####################################
void CfgData::InitFamilyMedalTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-150h] BYREF
  FamilyMedal Medal; // [rsp+A0h] [rbp-C0h] BYREF
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-90h] BYREF
  _BYTE v7[15]; // [rsp+E0h] [rbp-80h] BYREF
  char v8; // [rsp+EFh] [rbp-71h] BYREF
  int32_t v9[3]; // [rsp+F0h] [rbp-70h] BYREF
  char v10; // [rsp+FFh] [rbp-61h] BYREF
  std::list<AddAttribute> v11; // [rsp+100h] [rbp-60h] BYREF
  _BYTE v12[15]; // [rsp+110h] [rbp-50h] BYREF
  char v13; // [rsp+11Fh] [rbp-41h] BYREF
  int32_t v14[2]; // [rsp+120h] [rbp-40h] BYREF
  char v15; // [rsp+12Ah] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+12Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+130h] [rbp-30h]
  int32_t i; // [rsp+134h] [rbp-2Ch]
  int32_t nIndex; // [rsp+138h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+144h] [rbp-1Ch]
  int32_t i_0; // [rsp+148h] [rbp-18h]
  int32_t nIndex_0; // [rsp+14Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/FamilyBadge.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_MEDAL_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&Medal, 0, sizeof(Medal));
        std::list<AddAttribute>::list(&Medal.lAttrList);
        Medal.nLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        Medal.nNeedFamilyLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        Medal.nNeedFamilyExp = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v7, "./ServerConfig/Tables/FamilyBadge.txt", &v8);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v9, v2->pString, &v10);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v9,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&Medal.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        Medal.nGongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        Medal.DefRdc = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgFamilyTable::AddFamilyMedal(&this->m_cfgFamilyTable, &Medal);
        /* FamilyMedal::~FamilyMedal(&Medal); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/BadgeStreng.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FAMILY_MEDAL_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&Medal, 0, 32);
          std::list<AddAttribute>::list(&Medal.lAttrList);
          Medal.nLevel = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          Medal.nNeedFamilyLevel = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          Medal.nNeedFamilyExp = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          nIndex_0 += 2;
          
          std::string::string(v12, "./ServerConfig/Tables/FamilyBadge.txt", &v13);
          
          v3 = readFile.Search_Posistion( i_0, nIndex_0);
          std::string::string(v14, v3->pString, &v15);
          CfgData::parseAddAttribues(
            (CfgData *const)&v11,
            (const std::string *const)this,
            (int32_t)v14,
            (const std::string *const)(unsigned int)nIndex_0);
          std::list<AddAttribute>::operator=(&Medal.lAttrList, &v11);
          std::list<AddAttribute>::~list(&v11);
          
          ++nIndex_0;
          CfgFamilyTable::AddFamilySelfMedal(&this->m_cfgFamilyTable, (const FamilySelfMedal *const)&Medal);
          FamilySelfMedal::~FamilySelfMedal((FamilySelfMedal *const)&Medal);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitFamilySkillTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-120h] BYREF
  CfgFamilySkill stu; // [rsp+A0h] [rbp-90h] BYREF
  AttrAddonVector __x; // [rsp+D0h] [rbp-60h] BYREF
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/FamilySkill.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_FAMILY_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgFamilySkill::CfgFamilySkill(&stu);
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nFamilyLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCostValue = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        path = "./ServerConfig/Tables/FamilySkill.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        stu.nCostMoney = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.PlayerLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgSkillTable::AddFamilySkill(&this->m_cfgSkillTable, &stu);
        /* CfgFamilySkill::~CfgFamilySkill(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitFlopTable()
{
  const CDBCFile::FIELD *v1; // rax
  FlopDrawCfg *v2; // rax
  MemChrBag v3; // [rsp+0h] [rbp-120h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-F8h]
  CDBCFile readFile(0); // [rsp+30h] [rbp-F0h] BYREF
  FlopDrawCfg stu; // [rsp+C0h] [rbp-60h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  thisa = this;
  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/FlopActivity.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_FLOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.m_nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.m_nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        CItemHelper::parseItemString(&v3, &strItem);
        stu.m_Item = v3;
        
        stu.m_nRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.m_GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,FlopDrawCfg>::operator[](&thisa->m_FlopDrawCfgMap, &stu.m_nId);
        *v2 = stu;
      }
    }
  }
}

//#####################################
void CfgData::InitFunctionOpenMailMap()
{
  FunctionOpenMail *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-E0h] BYREF
  int32_t nId; // [rsp+ACh] [rbp-44h] BYREF
  FunctionOpenMail stu; // [rsp+B0h] [rbp-40h]
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MailGuide.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDay = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMailID = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDayLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,FunctionOpenMail>::operator[](&this->m_FunctionOpenMailMap, &nId);
        *v1 = stu;
        if ( nId <= 0 || nId > 199 )
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "read FILE_MAIL_GUIDE_TABLE nId =%d\n", nId);
      }
    }
  }
}

//#####################################
FunctionOpenMail *CfgData::GetOpenFunctionMailnCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,FunctionOpenMail>::find(&this->m_FunctionOpenMailMap, &nIda)._M_node;
  __x._M_node = std::map<int,FunctionOpenMail>::end(&thisa->m_FunctionOpenMailMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitGemOpenHoleTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-F0h] BYREF
  CfgGemOpenHole stu; // [rsp+A0h] [rbp-60h] BYREF
  std::list<ItemData> strItems; // [rsp+C0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+D0h] [rbp-30h] BYREF
  char v6; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GemOpenHole.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GEM_OPEN_HOLE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<ItemData>::list(&stu.m_lCostItem);
        stu.m_nSlot = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.m_nCostMoney = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.m_lCostItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        ++nIndex;
        CfgItemGemTable::AddGemOpenHole(&this->m_cfgItemGem, &stu);
        /* CfgGemOpenHole::~CfgGemOpenHole(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitGemSuitTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgGemSuit stu; // [rsp+A0h] [rbp-80h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-60h] BYREF
  std::string path; // [rsp+E0h] [rbp-40h] BYREF
  char v6; // [rsp+EFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GemSuit.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GEM_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        memset(&stu, 0, sizeof(stu));
        /* std::vector<AttrAddon>::vector(&stu.m_vAttrAddon); */
        stu.m_nLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        path = "./ServerConfig/Tables/GemSuit.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.m_vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        CfgItemGemTable::AddGemSuit(&this->m_cfgItemGem, &stu);
        /* CfgGemSuit::~CfgGemSuit(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitGoblinData()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-140h] BYREF
  cfgGoblinData stu; // [rsp+A0h] [rbp-B0h] BYREF
  std::string path; // [rsp+E0h] [rbp-70h] BYREF
  char v6; // [rsp+EFh] [rbp-61h] BYREF
  std::string str; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  std::vector<Position> __x; // [rsp+100h] [rbp-50h] BYREF
  std::string strPos; // [rsp+120h] [rbp-30h] BYREF
  char v11; // [rsp+132h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+134h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+138h] [rbp-18h]
  int32_t i; // [rsp+13Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/Goblin.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C7820);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        /* std::vector<CurrentData>::vector(&stu.m_RefreshMonsters); */
        /* std::vector<Position>::vector(&stu.m_RevivePosVector); */
        stu.m_nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.m_nRefreshTime = TabFile.Search_Posistion( i, 1)->iValue;
        
        path = "./ServerConfig/Tables/Goblin.txt";
        
        v1 = TabFile.Search_Posistion( i, 2);
        str.assign(v1->pString);
        CfgData::parseCurrentDatas(this, &stu.m_RefreshMonsters, &str, i, &path);
        
        stu.m_mapId = TabFile.Search_Posistion( i, 3)->iValue;
        
        v2 = TabFile.Search_Posistion( i, 4);
        strPos.assign(v2->pString);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.m_RevivePosVector, &__x);
        std::vector<Position>::~vector(&__x);
        
        cfgGoblinTableData::Add(&this->m_cfgGoblinTableData, &stu);
        /* cfgGoblinData::~cfgGoblinData(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::parseCurrentDatas(CurrentDatas *const currentDatas,
        const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6; // rdx
  CurrentData current; // [rsp+30h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-60h] BYREF
  StringVector strMonsters; // [rsp+50h] [rbp-50h] BYREF
  std::string delims; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+7Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-20h] BYREF

  if ( !(unsigned __int8)std::string::empty((std::string *)str)
    && !std::operator==<char>(str, "-1")
    && !std::operator==<char>(str, "0") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&strMonsters, str, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&strMonsters)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strMonsters)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      v6 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      CfgData::parseCurrentData(this, &current, v6, nIndex, path);
      std::vector<CurrentData>::push_back(currentDatas, &current);
    }
    std::vector<std::string>::~vector(&strMonsters);
  }
}

//#####################################
void CfgData::parseCurrentData(CurrentData *const current,
        const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  const char *v10; // rbx
  const char *v11; // rax
  StringVector strCurrent; // [rsp+30h] [rbp-40h] BYREF
  std::string delims; // [rsp+50h] [rbp-20h] BYREF
  _BYTE v17[17]; // [rsp+5Fh] [rbp-11h] BYREF

  if ( !(unsigned __int8)std::string::empty((std::string *)str)
    && !std::operator==<char>(str, "-1")
    && !std::operator==<char>(str, "0") )
  {
    
    delims.assign(":", v17);
    Answer::StringUtility::split(&strCurrent, str, &delims, 0);
    
    if ( std::vector<std::string>::size(&strCurrent) == 2 )
    {
      v6 = std::vector<std::string>::operator[](&strCurrent, 0);
      v7 = (const char *)std::string::c_str(v6);
      current->nId = atoi(v7);
      v8 = std::vector<std::string>::operator[](&strCurrent, 1u);
      v9 = (const char *)std::string::c_str(v8);
      current->nValue = atoi(v9);
    }
    else
    {
      v10 = (const char *)std::string::c_str((std::string *)str);
      v11 = (const char *)std::string::c_str((std::string *)path);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::parseCurrentData() wrong data from %s, where index = %d, str = %s\n",
        v11,
        nIndex,
        v10);
    }
    std::vector<std::string>::~vector(&strCurrent);
  }
}

//#####################################
void CfgData::InitGoblinTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  std::list<AddAttribute> *v3; // rax
  CDBCFile TabFile(0); // [rsp+20h] [rbp-160h] BYREF
  AddAttrList AddAttrs; // [rsp+B0h] [rbp-D0h] BYREF
  int32_t nId; // [rsp+CCh] [rbp-B4h] BYREF
  GoblinCfg stu; // [rsp+D0h] [rbp-B0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,GoblinCfg> >,bool> v8; // [rsp+E0h] [rbp-A0h]
  _BYTE v9[32]; // [rsp+F0h] [rbp-90h] BYREF
  std::pair<int,int> __a; // [rsp+110h] [rbp-70h] BYREF
  _BYTE v11[15]; // [rsp+120h] [rbp-60h] BYREF
  char v12; // [rsp+12Fh] [rbp-51h] BYREF
  int32_t v13[4]; // [rsp+130h] [rbp-50h] BYREF
  char v14; // [rsp+142h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+144h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+148h] [rbp-38h]
  int32_t i; // [rsp+14Ch] [rbp-34h]
  int32_t nIndex; // [rsp+150h] [rbp-30h]
  int32_t nType; // [rsp+154h] [rbp-2Ch]
  int32_t nLevel; // [rsp+158h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+164h] [rbp-1Ch]
  int32_t i_0; // [rsp+168h] [rbp-18h]
  int32_t nIndex_0; // [rsp+16Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/GoblinUp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,GoblinCfg>::clear(&this->m_GoblinCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.UpAttr = 0;
        stu.ConstCurr = 0;
        nType = TabFile.Search_Posistion( i, 0)->iValue;
        nLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.UpAttr = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.SuitId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.ConstCurr = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(nType, nLevel);
        std::pair<std::pair const<int,int>,GoblinCfg>::pair(
          (std::pair<const std::pair<int,int>,GoblinCfg> *const)v9,
          &__a,
          &stu);
        v8 = std::map<std::pair<int,int>,GoblinCfg>::insert(
               &this->m_GoblinCfgMap,
               (const std::pair<const std::pair<int,int>,GoblinCfg> *const)v9);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/GoblinSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,std::list<AddAttribute>>::clear(&this->m_GoblinSuitMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          nId = TabFile.Search_Posistion( i_0, 0)->iValue;
          ++nIndex_0;
          
          std::string::string(v11, "./ServerConfig/Tables/GoblinSuit.txt", &v12);
          
          v2 = TabFile.Search_Posistion( i_0, nIndex_0);
          std::string::string(v13, v2->pString, &v14);
          CfgData::parseAddAttribues(
            (CfgData *const)&AddAttrs,
            (const std::string *const)this,
            (int32_t)v13,
            (const std::string *const)(unsigned int)nIndex_0);
          
          ++nIndex_0;
          v3 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_GoblinSuitMap, &nId);
          std::list<AddAttribute>::operator=(v3, &AddAttrs);
          std::list<AddAttribute>::~list(&AddAttrs);
        }
      }
    }
  }
}

//#####################################
GoblinCfg *CfgData::GetGoblinCfg(int32_t nType, int32_t nLevel)
{
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,GoblinCfg> > it; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,GoblinCfg> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(nType, nLevel);
  it._M_node = std::map<std::pair<int,int>,GoblinCfg>::find(&this->m_GoblinCfgMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,GoblinCfg>::end(&this->m_GoblinCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,GoblinCfg>>::operator!=(&it, &v6) )
    return (GoblinCfg *)((char *)std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,GoblinCfg>>::operator->(&it)
                       + 8);
  else
    return 0;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
AddAttrList CfgData::GetGoblinSuitAttr(int32_t nId)
{
  int32_t v2; // edx
  std::pair<const int,std::list<AddAttribute> > *v3; // rax
  AddAttrList result; // rax
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,std::list<AddAttribute> > > it; // [rsp+10h] [rbp-40h] BYREF
  AddAttrList Attrs; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<AddAttribute> > > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = *(CfgData **)&nId;
  nIda = v2;
  std::list<AddAttribute>::list(&Attrs);
  std::list<AddAttribute>::clear(&Attrs);
  it._M_node = std::map<int,std::list<AddAttribute>>::find(
                 (std::map<int,std::list<AddAttribute>> *const)(*(_QWORD *)&nId + 11208LL),
                 &nIda)._M_node;
  __x._M_node = std::map<int,std::list<AddAttribute>>::end(&thisa->m_GoblinSuitMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<AddAttribute>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::list<AddAttribute>>>::operator->(&it);
    std::list<AddAttribute>::list((std::list<AddAttribute> *const)this, &v3->second);
  }
  else
  {
    std::list<AddAttribute>::list((std::list<AddAttribute> *const)this, &Attrs);
  }
  std::list<AddAttribute>::~list(&Attrs);
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
void CfgData::InitGoldEggTable()
{
  int v1; // ebx
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgGoldEgg stu; // [rsp+A0h] [rbp-70h] BYREF
  int iValue; // [rsp+C8h] [rbp-48h]
  int32_t iBaseTableCount; // [rsp+D8h] [rbp-38h]
  int32_t iBaseColumnCount; // [rsp+DCh] [rbp-34h]
  int32_t i; // [rsp+E0h] [rbp-30h]
  int32_t nIndex; // [rsp+E4h] [rbp-2Ch]
  int32_t iBaseTableCount_0; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount_0; // [rsp+F0h] [rbp-20h]
  int32_t i_0; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex_0; // [rsp+F8h] [rbp-18h]
  int32_t nId; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ItemGoldEggOpen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOLD_EGG_OPEN_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgGoldEgg::CfgGoldEgg(&stu);
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nGroupId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nOpenTimes = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCostMoney = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCostGold = readFile.Search_Posistion( i, nIndex++)->iValue;
        CfgGoldEggTable::AddGoldEgg(&this->m_cfgGoldEggTable, &stu);
        /* CfgGoldEgg::~CfgGoldEgg(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ItemGoldEgg.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOLD_EGG_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, sizeof(stu));
          iValue = 0;
          nId = readFile.Search_Posistion( i_0, 0)->iValue;
          stu.nId = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          LOBYTE(stu.nGroupId) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.nOpenTimes = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          LOBYTE(stu.nCostMoney) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.nCostGold = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          *((_BYTE *)&stu.nCostGold + 4) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          LODWORD(stu.lstItem._M_impl._M_node._M_next) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          HIDWORD(stu.lstItem._M_impl._M_node._M_next) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          LODWORD(stu.lstItem._M_impl._M_node._M_prev) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          HIDWORD(stu.lstItem._M_impl._M_node._M_prev) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          iValue = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CfgGoldEggTable::AddGoldEggProduce(&this->m_cfgGoldEggTable, nId, (const CfgGoldEggItem *const)&stu);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitGongMinTable()
{
  const CDBCFile::FIELD *v1; // rax
  GongMingCfg *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  GongMingCfg stu; // [rsp+A0h] [rbp-80h] BYREF
  std::list<AddAttribute> __x; // [rsp+D0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+E0h] [rbp-40h] BYREF
  char v7; // [rsp+EFh] [rbp-31h] BYREF
  int32_t v8[3]; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GongMing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileGongMi);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        GongMingCfg::GongMingCfg(&stu);
        stu.nChong = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nStar = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.NeedGongMingZhi = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v6, "./ServerConfig/Tables/GongMing.txt", &v7);
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,GongMingCfg>::operator[](&this->m_GongMingCfgMap, &stu.nIndex);
        GongMingCfg::operator=(v2, &stu);
        /* GongMingCfg::~GongMingCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
GongMingCfg *CfgData::GetGongMingCfg(int32_t GongMinLevel)
{
  int32_t GongMinLevela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,GongMingCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GongMingCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  GongMinLevela = GongMinLevel;
  it._M_node = std::map<int,GongMingCfg>::find(&this->m_GongMingCfgMap, &GongMinLevela)._M_node;
  __x._M_node = std::map<int,GongMingCfg>::end(&thisa->m_GongMingCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,GongMingCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,GongMingCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitGroupIconTable()
{
  const CDBCFile::FIELD *v1; // rax
  CfgGroupIcon *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgGroupIcon icon; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GroupIcon.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_GROUP_ICON_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        *(_QWORD *)&icon.nId = 0;
        icon.platfrom._M_dataplus._M_p = 0;
        std::string::string(&icon.platfrom);
        icon.nId = readFile.Search_Posistion( i, 0)->iValue;
        icon.bShowInCross = readFile.Search_Posistion( i, 18)->iValue;
        v1 = readFile.Search_Posistion( i, 19);
        std::string::operator=(&icon.platfrom, v1->pString);
        v2 = std::map<int,CfgGroupIcon>::operator[](&this->m_cfgGroupIcons, &icon.nId);
        CfgGroupIcon::operator=(v2, &icon);
        /* CfgGroupIcon::~CfgGroupIcon(&icon); - auto cleanup */
      }
    }
  }
}

//#####################################
bool CfgData::IsShowIcon(int32_t nIconId, const std::string *const platform)
{
  GameService *v4; // rax
  bool v6; // al
  int32_t nIconIda; // [rsp+14h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+18h] [rbp-48h]
  std::_Rb_tree_const_iterator<std::pair<const int,CfgGroupIcon> > iter; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgGroupIcon> > __it; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgGroupIcon> > __x; // [rsp+40h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgGroupIcon> > v13; // [rsp+50h] [rbp-10h] BYREF
  const CfgGroupIcon *icon; // [rsp+58h] [rbp-8h]

  thisa = this;
  nIconIda = nIconId;
  __it._M_node = std::map<int,CfgGroupIcon>::find(&this->m_cfgGroupIcons, &nIconIda)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::_Rb_tree_const_iterator(&iter, &__it);
  v13._M_node = std::map<int,CfgGroupIcon>::end(&thisa->m_cfgGroupIcons)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::_Rb_tree_const_iterator(&__x, &v13);
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::operator==(&iter, &__x) )
    return 0;
  icon = &std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::operator->(&iter)->second;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 && !icon->bShowInCross )
    return 0;
  v6 = std::operator!=<char>(&icon->platfrom, "-1") && std::operator!=<char>(platform, &icon->platfrom);
  return !v6;
}

//#####################################
void CfgData::InitGroupMonster()
{
  const CDBCFile::FIELD *v1; // rax
  std::vector<GroupMonster> *v2; // rax
  CDBCFile InitBossFile(0); // [rsp+10h] [rbp-110h] BYREF
  GroupMonster stu; // [rsp+A0h] [rbp-80h] BYREF
  int32_t MapId; // [rsp+CCh] [rbp-54h] BYREF
  std::vector<Position> __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  
  if ( !InitBossFile.OpenFromTXT( "./ServerConfig/Tables/RegionRefresh.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_INFO_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = InitBossFile.GetRecordsNum();
    iBaseColumnCount = InitBossFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,std::vector<GroupMonster>>::clear(&this->m_GroupMonsterMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        /* std::vector<Position>::vector(&stu.RevivePos); */
        MapId = InitBossFile.Search_Posistion( i, 0)->iValue;
        stu.RegionCount = InitBossFile.Search_Posistion( i, 1)->iValue;
        stu.Mid = InitBossFile.Search_Posistion( i, 2)->iValue;
        stu.MonsterCount = InitBossFile.Search_Posistion( i, 3)->iValue;
        stu.IsSpecial = InitBossFile.Search_Posistion( i, 4)->iValue;
        
        v1 = InitBossFile.Search_Posistion( i, 5);
        strPos.assign(v1->pString);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.RevivePos, &__x);
        std::vector<Position>::~vector(&__x);
        
        v2 = std::map<int,std::vector<GroupMonster>>::operator[](&this->m_GroupMonsterMap, &MapId);
        std::vector<GroupMonster>::push_back(v2, &stu);
        /* GroupMonster::~GroupMonster(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
GroupMonsterVector *CfgData::GetGroupMonsterVector(int32_t MapId)
{
  std::pair<const int,std::vector<GroupMonster> > *v3; // rax
  int32_t MapIda; // [rsp+4h] [rbp-5Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-58h]
  std::_Rb_tree_iterator<std::pair<const int,std::vector<GroupMonster> > > it; // [rsp+10h] [rbp-50h] BYREF
  GroupMonsterVector GroupMonsterVectorStu; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::vector<GroupMonster> > > __x; // [rsp+40h] [rbp-20h] BYREF

  thisa = this;
  MapIda = MapId;
  /* std::vector<GroupMonster>::vector(&GroupMonsterVectorStu); */
  it._M_node = std::map<int,std::vector<GroupMonster>>::find(&this->m_GroupMonsterMap, &MapIda)._M_node;
  __x._M_node = std::map<int,std::vector<GroupMonster>>::end(&thisa->m_GroupMonsterMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::vector<GroupMonster>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::vector<GroupMonster>>>::operator->(&it);
    std::vector<GroupMonster>::vector(retstr, &v3->second);
  }
  else
  {
    std::vector<GroupMonster>::vector(retstr, &GroupMonsterVectorStu);
  }
  std::vector<GroupMonster>::~vector(&GroupMonsterVectorStu);
  return retstr;
}

//#####################################
void CfgData::InitGuWuCfgMap()
{
  GuWuCfg *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  GuWuCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/GuWu.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEquipB_0);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.nLevel = readFile.Search_Posistion( i, 0)->iValue;
        stu.Money = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Gold = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MoneyRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GoldRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MoneyBuffId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GoldBuffId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,GuWuCfg>::operator[](&this->m_GuWuCfgMap, &stu.nLevel);
        *v1 = stu;
      }
    }
  }
}

//#####################################
GuWuCfg *CfgData::GetGuWuCfg(int32_t Level)
{
  int32_t Levela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,GuWuCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GuWuCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Levela = Level;
  it._M_node = std::map<int,GuWuCfg>::find(&this->m_GuWuCfgMap, &Levela)._M_node;
  __x._M_node = std::map<int,GuWuCfg>::end(&thisa->m_GuWuCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,GuWuCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,GuWuCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitGuiGuDaoRenTable()
{
  const CDBCFile::FIELD *v1; // rax
  const std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  const CDBCFile::FIELD *v11; // rax
  const CDBCFile::FIELD *v12; // rax
  const CDBCFile::FIELD *v13; // rax
  GuiGuDaoRenCfg *v14; // rax
  int64_t v15; // rax
  CDBCFile TabFile(0); // [rsp+20h] [rbp-250h] BYREF
  GuiGuDaoRenCfg stu; // [rsp+B0h] [rbp-1C0h] BYREF
  RefreshMonster tmpStu; // [rsp+110h] [rbp-160h] BYREF
  StringVector vstr; // [rsp+120h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+140h] [rbp-130h] BYREF
  StringVector SplitStr; // [rsp+150h] [rbp-120h] BYREF
  std::string RefreshMonsterString; // [rsp+170h] [rbp-100h] BYREF
  char v23; // [rsp+17Fh] [rbp-F1h] BYREF
  std::string delims; // [rsp+180h] [rbp-F0h] BYREF
  char v25; // [rsp+18Fh] [rbp-E1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+190h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1A0h] [rbp-D0h] BYREF
  std::string v28; // [rsp+1B0h] [rbp-C0h] BYREF
  char v29; // [rsp+1BFh] [rbp-B1h] BYREF
  ItemData __x; // [rsp+1C0h] [rbp-B0h] BYREF
  std::string strItem; // [rsp+1D0h] [rbp-A0h] BYREF
  char v32; // [rsp+1DFh] [rbp-91h] BYREF
  MemChrBag v33; // [rsp+1E0h] [rbp-90h] BYREF
  std::string v34; // [rsp+200h] [rbp-70h] BYREF
  char v35; // [rsp+20Fh] [rbp-61h] BYREF
  Int32Vector v36; // [rsp+210h] [rbp-60h] BYREF
  std::string path; // [rsp+230h] [rbp-40h] BYREF
  char v38; // [rsp+23Fh] [rbp-31h] BYREF
  std::string str; // [rsp+240h] [rbp-30h] BYREF
  char v40; // [rsp+24Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+24Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+250h] [rbp-20h]
  int32_t i; // [rsp+254h] [rbp-1Ch]
  int32_t nIndex; // [rsp+258h] [rbp-18h]
  int32_t j; // [rsp+25Ch] [rbp-14h]
  ItemData v47; // 0:kr00_12.12

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/TaoistTask.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GUI_GU_DAO_REN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,GuiGuDaoRenCfg>::clear(&this->m_GuiGuDaoRenCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::list<RefreshMonster>::list(&stu.lRefreshMonster);
        /* std::vector<ItemData>::vector(&stu.vItemData); */
        /* /* /* std::vector<MemChrBag>::vector(&stu.vItem); */ */ */
        /* std::vector<int>::vector(&stu.vMapId); */
        nIndex = 0;
        stu.nNpcId = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nMaxCount = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        RefreshMonsterString.assign(v1->pString);
        
        ++nIndex;
        
        delims = "|";
        Answer::StringUtility::split(&SplitStr, &RefreshMonsterString, &delims, 0);
        
        __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
          &iterBegin,
          &__i);
        while ( 1 )
        {
          __rhs._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
          if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &__rhs) )
            break;
          
          v28 = ":";
          v2 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
          Answer::StringUtility::split(&vstr, v2, &v28, 0);
          
          if ( std::vector<std::string>::size(&vstr) == 4 )
          {
            *(_QWORD *)&tmpStu.nCount = 0;
            *(_QWORD *)&tmpStu.AliveTime = 0;
            v3 = std::vector<std::string>::operator[](&vstr, 0);
            v4 = (const char *)std::string::c_str(v3);
            tmpStu.nCount = atoi(v4);
            v5 = std::vector<std::string>::operator[](&vstr, 1u);
            v6 = (const char *)std::string::c_str(v5);
            tmpStu.BossId = atoi(v6);
            v7 = std::vector<std::string>::operator[](&vstr, 2u);
            v8 = (const char *)std::string::c_str(v7);
            tmpStu.AliveTime = atoi(v8);
            v9 = std::vector<std::string>::operator[](&vstr, 3u);
            v10 = (const char *)std::string::c_str(v9);
            tmpStu.GongGaoId = atoi(v10);
            std::list<RefreshMonster>::push_back(&stu.lRefreshMonster, &tmpStu);
          }
          std::vector<std::string>::~vector(&vstr);
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
        }
        std::vector<ItemData>::reserve(&stu.vItemData, 3u);
        std::vector<MemChrBag>::reserve(&stu.vItem, 3u);
        for ( j = 0; j <= 2; ++j )
        {
          
          v11 = TabFile.Search_Posistion( i, nIndex);
          strItem.assign(v11->pString);
          v47 = CItemHelper::parseItemDataString(&strItem);
          LODWORD(v15) = v47.m_nId;
          BYTE4(v15) = v47.m_nClass;
          *(_QWORD *)&__x.m_nId = v15;
          __x.m_nCount = v47.m_nCount;
          std::vector<ItemData>::push_back(&stu.vItemData, &__x);
          
          ++nIndex;
          
          v12 = TabFile.Search_Posistion( i, nIndex);
          v34.assign(v12->pString);
          CItemHelper::parseItemString(&v33, &v34);
          std::vector<MemChrBag>::push_back(&stu.vItem, &v33);
          
          ++nIndex;
        }
        
        path = "./ServerConfig/Tables/TaoistTask.txt";
        
        v13 = TabFile.Search_Posistion( i, nIndex);
        str.assign(v13->pString);
        CfgData::paraseInt32Vector(&v36, this, &str, &path, 0);
        std::vector<int>::operator=(&stu.vMapId, &v36);
        std::vector<int>::~vector(&v36);
        
        ++nIndex;
        v14 = std::map<int,GuiGuDaoRenCfg>::operator[](&this->m_GuiGuDaoRenCfgMap, &stu.nNpcId);
        GuiGuDaoRenCfg::operator=(v14, &stu);
        std::vector<std::string>::~vector(&SplitStr);
        /* GuiGuDaoRenCfg::~GuiGuDaoRenCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
GuiGuDaoRenCfg *CfgData::GetGuiGuDaoRenCfg(int32_t NpcId)
{
  int32_t NpcIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,GuiGuDaoRenCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GuiGuDaoRenCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  NpcIda = NpcId;
  it._M_node = std::map<int,GuiGuDaoRenCfg>::find(&this->m_GuiGuDaoRenCfgMap, &NpcIda)._M_node;
  __x._M_node = std::map<int,GuiGuDaoRenCfg>::end(&thisa->m_GuiGuDaoRenCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,GuiGuDaoRenCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,GuiGuDaoRenCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitHoeTable()
{
  HoeCfg *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-C0h] BYREF
  HoeCfg Stu; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Hoe.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_HOE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&Stu.nId = 0;
        Stu.nDouble = 0;
        Stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        Stu.nNextId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        Stu.nDouble = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,HoeCfg>::operator[](&this->m_HoeCfgMap, &Stu.nId);
        *v1 = Stu;
      }
    }
  }
}

//#####################################
HoeCfg *CfgData::GetHoeCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,HoeCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HoeCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,HoeCfg>::find(&this->m_HoeCfgMap, &nIda)._M_node;
  __x._M_node = std::map<int,HoeCfg>::end(&thisa->m_HoeCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,HoeCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,HoeCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
AttrAddonVector *CfgData::paraseAttrAddon(const std::string *const addonAttr,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  const char *v11; // r12
  const char *v12; // rax
  AttrAddon attrAddon; // [rsp+20h] [rbp-B0h] BYREF
  StringVector strAttrAddon; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector strAttrAddons; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v22; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v24; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v25[33]; // [rsp+AFh] [rbp-21h] BYREF

  std::vector<AttrAddon>::vector(retstr);
  if ( !(unsigned __int8)std::string::empty((std::string *)addonAttr)
    && !std::operator==<char>(addonAttr, "-1")
    && !std::operator==<char>(addonAttr, "0") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&strAttrAddons, addonAttr, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&strAttrAddons)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strAttrAddons)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v24.assign(":", v25);
      v6 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&strAttrAddon, v6, &v24, 0);
      
      if ( std::vector<std::string>::size(&strAttrAddon) == 2 )
      {
        attrAddon = 0;
        v7 = std::vector<std::string>::operator[](&strAttrAddon, 0);
        v8 = (const char *)std::string::c_str(v7);
        attrAddon.index = atoi(v8);
        v9 = std::vector<std::string>::operator[](&strAttrAddon, 1u);
        v10 = (const char *)std::string::c_str(v9);
        attrAddon.addon = atoi(v10);
        if ( attrAddon.index > 0 && attrAddon.addon > 0 )
          std::vector<AttrAddon>::push_back(retstr, &attrAddon);
      }
      else
      {
        v11 = (const char *)std::string::c_str((std::string *)addonAttr);
        v12 = (const char *)std::string::c_str((std::string *)path);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::paraseAttrAddon() wrong data from %s, where index = %d, str = %s\n",
          v12,
          nIndex,
          v11);
      }
      std::vector<std::string>::~vector(&strAttrAddon);
    }
    std::vector<std::string>::~vector(&strAttrAddons);
  }
  return retstr;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
TalentAddonList CfgData::paraseTalentAddon(const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v4; // r8
  TalentAddonList result; // rax
  std::string *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  const char *v14; // r12
  const char *v15; // rax
  int v16; // r12d
  const char *v17; // r12
  const char *v18; // rax
  std::string *patha; // [rsp+0h] [rbp-D0h]
  int32_t nIndexa; // [rsp+Ch] [rbp-C4h]
  std::string *stra; // [rsp+10h] [rbp-C0h]
  TalentAddon addon; // [rsp+20h] [rbp-B0h] BYREF
  StringVector strAddon; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector strAddons; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v27; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v29; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v30[33]; // [rsp+AFh] [rbp-21h] BYREF

  stra = *(std::string **)&nIndex;
  nIndexa = (int)path;
  patha = v4;
  std::list<TalentAddon>::list((std::list<TalentAddon> *const)this);
  if ( !(unsigned __int8)std::string::empty(stra) && !std::operator==<char>(stra, "-1") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&strAddons, stra, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&strAddons)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strAddons)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
      {
LABEL_16:
        std::vector<std::string>::~vector(&strAddons);
        break;
      }
      
      v29.assign(":", v30);
      v7 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&strAddon, v7, &v29, 0);
      
      if ( std::vector<std::string>::size(&strAddon) == 3 )
      {
        *(_QWORD *)&addon.id = 0;
        addon.addon = 0;
        v8 = std::vector<std::string>::operator[](&strAddon, 0);
        v9 = (const char *)std::string::c_str(v8);
        addon.id = atoi(v9);
        v10 = std::vector<std::string>::operator[](&strAddon, 1u);
        v11 = (const char *)std::string::c_str(v10);
        addon.type = atoi(v11);
        v12 = std::vector<std::string>::operator[](&strAddon, 2u);
        v13 = (const char *)std::string::c_str(v12);
        addon.addon = atoi(v13);
        if ( addon.type > 8u )
        {
          v14 = (const char *)std::string::c_str(stra);
          v15 = (const char *)std::string::c_str(patha);
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "CfgData::paraseTalentAddon() wrong type from %s, where index = %d, str = %s\n",
            v15,
            nIndexa,
            v14);
          v16 = 0;
          goto LABEL_13;
        }
        std::list<TalentAddon>::push_back((std::list<TalentAddon> *const)this, &addon);
      }
      else
      {
        v17 = (const char *)std::string::c_str(stra);
        v18 = (const char *)std::string::c_str(patha);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::paraseTalentAddon() wrong data from %s, where index = %d, str = %s\n",
          v18,
          nIndexa,
          v17);
      }
      v16 = 1;
LABEL_13:
      std::vector<std::string>::~vector(&strAddon);
      if ( !v16 )
        goto LABEL_16;
    }
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
AddAttribute CfgData::parseAddAttribue(const std::string *const addonAttr,
        int32_t nIndex,
        const std::string *const path)
{
  AddAttribute v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  const char *v10; // rbx
  const char *v11; // rax
  StringVector strAttrAddon; // [rsp+20h] [rbp-50h] BYREF
  AddAttribute attribute; // [rsp+40h] [rbp-30h] BYREF
  std::string delims; // [rsp+50h] [rbp-20h] BYREF
  _BYTE v17[17]; // [rsp+5Fh] [rbp-11h] BYREF

  AddAttribute::AddAttribute(&attribute);
  if ( (unsigned __int8)std::string::empty((std::string *)addonAttr) || std::operator==<char>(addonAttr, "-1") )
    return attribute;
  
  delims.assign(":", v17);
  Answer::StringUtility::split(&strAttrAddon, addonAttr, &delims, 0);
  
  if ( std::vector<std::string>::size(&strAttrAddon) == 2 )
  {
    v6 = std::vector<std::string>::operator[](&strAttrAddon, 0);
    v7 = (const char *)std::string::c_str(v6);
    attribute.m_nAddAttrType = atoi(v7);
    v8 = std::vector<std::string>::operator[](&strAttrAddon, 1u);
    v9 = (const char *)std::string::c_str(v8);
    attribute.m_nAddAttrValue = atoi(v9);
  }
  else
  {
    v10 = (const char *)std::string::c_str((std::string *)addonAttr);
    v11 = (const char *)std::string::c_str((std::string *)path);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "CfgData::paraseAttrAddon() wrong data from %s, where index = %d, str = %s\n",
      v11,
      nIndex,
      v10);
  }
  v5 = attribute;
  std::vector<std::string>::~vector(&strAttrAddon);
  return v5;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
AddAttrList CfgData::parseAddAttribues(const std::string *const addonAttr,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v4; // r8
  AddAttrList result; // rax
  std::string *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  const char *v12; // r12
  const char *v13; // rax
  std::string *patha; // [rsp+0h] [rbp-D0h]
  int32_t nIndexa; // [rsp+Ch] [rbp-C4h]
  std::string *addonAttra; // [rsp+10h] [rbp-C0h]
  AddAttribute attr; // [rsp+20h] [rbp-B0h] BYREF
  StringVector strAttrAddon; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector strAttrAddons; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v22; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v24; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v25[33]; // [rsp+AFh] [rbp-21h] BYREF

  addonAttra = *(std::string **)&nIndex;
  nIndexa = (int)path;
  patha = v4;
  std::list<AddAttribute>::list((std::list<AddAttribute> *const)this);
  if ( !(unsigned __int8)std::string::empty(addonAttra)
    && !std::operator==<char>(addonAttra, "-1")
    && !std::operator==<char>(addonAttra, "0") )
  {
    
    delims = "|";
    Answer::StringUtility::split(&strAttrAddons, addonAttra, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&strAttrAddons)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strAttrAddons)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v24.assign(":", v25);
      v7 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&strAttrAddon, v7, &v24, 0);
      
      if ( std::vector<std::string>::size(&strAttrAddon) == 2 )
      {
        AddAttribute::AddAttribute(&attr);
        v8 = std::vector<std::string>::operator[](&strAttrAddon, 0);
        v9 = (const char *)std::string::c_str(v8);
        attr.m_nAddAttrType = atoi(v9);
        v10 = std::vector<std::string>::operator[](&strAttrAddon, 1u);
        v11 = (const char *)std::string::c_str(v10);
        attr.m_nAddAttrValue = atoi(v11);
        if ( attr.m_nAddAttrType && attr.m_nAddAttrValue > 0 )
          std::list<AddAttribute>::push_back((std::list<AddAttribute> *const)this, &attr);
      }
      else
      {
        v12 = (const char *)std::string::c_str(addonAttra);
        v13 = (const char *)std::string::c_str(patha);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::paraseAttrAddon() wrong data from %s, where index = %d, str = %s\n",
          v13,
          nIndexa,
          v12);
      }
      std::vector<std::string>::~vector(&strAttrAddon);
    }
    std::vector<std::string>::~vector(&strAttrAddons);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
void CfgData::InitJewelPavilionTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,JewelPavilionCfg> >,bool> v2; // rax
  MemChrBag v3; // [rsp+0h] [rbp-180h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-158h]
  CDBCFile TabFile(0); // [rsp+30h] [rbp-150h] BYREF
  JewelPavilionCfg stu; // [rsp+C0h] [rbp-C0h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-90h] BYREF
  char v8; // [rsp+FFh] [rbp-81h] BYREF
  std::_Rb_tree_node_base::_Base_ptr M_node; // [rsp+100h] [rbp-80h]
  bool second; // [rsp+108h] [rbp-78h]
  _BYTE v11[64]; // [rsp+110h] [rbp-70h] BYREF
  std::pair<int,int> __a; // [rsp+150h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]

  thisa = this;
  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/TreasureShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TREASURE_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,JewelPavilionCfg>::clear(&thisa->m_JewelPavilionCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nDay = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nIndex = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        CItemHelper::parseItemString(&v3, &strItem);
        stu.Item = v3;
        
        stu.nPrice = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(stu.nDay, stu.nIndex);
        std::pair<std::pair const<int,int>,JewelPavilionCfg>::pair(
          (std::pair<const std::pair<int,int>,JewelPavilionCfg> *const)v11,
          &__a,
          &stu);
        v2 = std::map<std::pair<int,int>,JewelPavilionCfg>::insert(
               &thisa->m_JewelPavilionCfgMap,
               (const std::pair<const std::pair<int,int>,JewelPavilionCfg> *const)v11);
        *(_QWORD *)&v3.itemId = v2.first._M_node;
        v3.itemCount = *(_DWORD *)&v2.second;
        M_node = v2.first._M_node;
        second = v2.second;
      }
    }
  }
}

//#####################################
JewelPavilionCfg *CfgData::GetJewelPavilionCfg(int32_t nDay, int32_t nIndex)
{
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,JewelPavilionCfg> > it; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,JewelPavilionCfg> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(nDay, nIndex);
  it._M_node = std::map<std::pair<int,int>,JewelPavilionCfg>::find(&this->m_JewelPavilionCfgMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,JewelPavilionCfg>::end(&this->m_JewelPavilionCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,JewelPavilionCfg>>::operator!=(&it, &v6) )
    return (JewelPavilionCfg *)((char *)std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,JewelPavilionCfg>>::operator->(&it)
                              + 8);
  else
    return 0;
}

//#####################################
void CfgData::InitJueWeiTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-120h] BYREF
  CfgJueWei stu; // [rsp+A0h] [rbp-90h] BYREF
  AttrAddonVector __x; // [rsp+D0h] [rbp-60h] BYREF
  std::string path; // [rsp+F0h] [rbp-40h] BYREF
  char v6; // [rsp+FFh] [rbp-31h] BYREF
  std::string addonAttr; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/JueWei.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CARRIER_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::vector<AttrAddon>::vector(&stu.vAttr);
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nNeedLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nNeedViGour = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/JueWei.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.vAttr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        CfgJueWeiTable::AddJueWei(&this->m_cfgJueWeiTable, &stu);
        /* CfgJueWei::~CfgJueWei(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitLaDaShiHuiYuan()
{
  const CDBCFile::FIELD *v1; // rax
  LuDaShiVip *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-110h] BYREF
  LuDaShiVip stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/LuDaShiHuiYuan.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9220);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 44);
        /* /* /* std::vector<MemChrBag>::vector(&stu.Rewards); */ */ */
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, 1)->iValue;
        
        v1 = TabFile.Search_Posistion( i, 3);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.nCondition = TabFile.Search_Posistion( i, 4)->iValue;
        stu.nVipType = TabFile.Search_Posistion( i, 8)->iValue;
        stu.nMaxCondition = TabFile.Search_Posistion( i, 11)->iValue;
        v2 = std::map<int,LuDaShiVip>::operator[](&this->m_LuDaShiVipMap, &stu.nIndex);
        LuDaShiVip::operator=(v2, &stu);
        /* LuDaShiVip::~LuDaShiVip(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
LuDaShiVip *CfgData::GetLaDaShiHuiYuan(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,LuDaShiVip> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,LuDaShiVip> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  it._M_node = std::map<int,LuDaShiVip>::find(&this->m_LuDaShiVipMap, &nIndexa)._M_node;
  __x._M_node = std::map<int,LuDaShiVip>::end(&thisa->m_LuDaShiVipMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,LuDaShiVip>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,LuDaShiVip>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitLevelChatTimesTable()
{
  int *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-C0h] BYREF
  int32_t nLevel; // [rsp+A4h] [rbp-2Ch] BYREF
  int32_t iBaseTableCount; // [rsp+ACh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+B0h] [rbp-20h]
  int32_t i; // [rsp+B4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+B8h] [rbp-18h]
  int32_t nTimes; // [rsp+BCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/PublicChatTimes.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_LEVEL_CHAT_TIMES_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nLevel = readFile.Search_Posistion( i, 0)->iValue;
        nTimes = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,int>::operator[](&this->m_cfgLevelChatTable, &nLevel);
        *v1 = nTimes;
      }
    }
  }
}

//#####################################
int32_t CfgData::GetChatTimes(int32_t nLevel)
{
  int32_t nLevela; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,int> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nLevela = nLevel;
  iter._M_node = std::map<int,int>::find(&this->m_cfgLevelChatTable, &nLevela)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_cfgLevelChatTable)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter)->second;
  else
    return -1;
}

//#####################################
void CfgData::InitLibraryTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  const CDBCFile::FIELD *v4; // rax
  int64_t v5; // rax
  MemChrBag v6; // [rsp+30h] [rbp-190h] BYREF
  CfgData *thisa; // [rsp+58h] [rbp-168h]
  CDBCFile readFile(0); // [rsp+60h] [rbp-160h] BYREF
  CfgLibraryItem stu; // [rsp+F0h] [rbp-D0h] BYREF
  CfgLibraryCost stu_1; // [rsp+120h] [rbp-A0h] BYREF
  CfgLibraryQuality stu_0; // [rsp+140h] [rbp-80h]
  std::string strItem; // [rsp+150h] [rbp-70h] BYREF
  char v13; // [rsp+15Fh] [rbp-61h] BYREF
  std::string v14; // [rsp+160h] [rbp-60h] BYREF
  char v15; // [rsp+176h] [rbp-4Ah] BYREF
  int32_t iBaseTableCount; // [rsp+178h] [rbp-48h]
  int32_t iBaseColumnCount; // [rsp+17Ch] [rbp-44h]
  int32_t i; // [rsp+180h] [rbp-40h]
  int32_t nIndex; // [rsp+184h] [rbp-3Ch]
  int32_t iBaseTableCount_0; // [rsp+18Ch] [rbp-34h]
  int32_t iBaseColumnCount_0; // [rsp+190h] [rbp-30h]
  int32_t i_0; // [rsp+194h] [rbp-2Ch]
  int32_t nIndex_0; // [rsp+198h] [rbp-28h]
  int32_t iBaseTableCount_1; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount_1; // [rsp+1A4h] [rbp-1Ch]
  int32_t i_1; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex_1; // [rsp+1ACh] [rbp-14h]
  ItemData v31; // 0:kr00_12.12

  thisa = this;
  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ChestItemRandom.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LIBRARY_ITEM_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        nIndex = 0;
        stu.nIndex = readFile.Search_Posistion( i, 0)->iValue;
        stu.nQuality = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        strItem.assign(v2->pString);
        CItemHelper::parseItemString(&v6, &strItem);
        stu.Item = v6;
        
        stu.Probability = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDunGeonId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CLibraryTable::AddCfgLibraryItem(&thisa->m_CLibraryTable, stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ChestItemQuality.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_LIBRARY_QUALITY__TABLE failed,please check!!!\n");
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu_0.nIndex = 0;
          *(_QWORD *)&stu_0.nCount = 0;
          nIndex_0 = 0;
          stu_0.nIndex = readFile.Search_Posistion( i_0, 0)->iValue;
          stu_0.nQuality = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nCount = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nProbability = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CLibraryTable::AddCfgLibraryQuality(&thisa->m_CLibraryTable, stu_0);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    if ( v3 )
    {
      
      if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ChestConsume.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_LIBRARY_COST_TABLE failed,please check!!!\n");
      }
      else
      {
        iBaseTableCount_1 = readFile.GetRecordsNum();
        iBaseColumnCount_1 = readFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            memset(&stu_1, 0, sizeof(stu_1));
            nIndex_1 = 0;
            stu_1.Times = readFile.Search_Posistion( i_1, 0)->iValue;
            stu_1.nDunGeonId = readFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            
            v4 = readFile.Search_Posistion( i_1, nIndex_1);
            v14.assign(v4->pString);
            v31 = CItemHelper::parseItemDataString(&v14);
            LODWORD(v5) = v31.m_nId;
            BYTE4(v5) = v31.m_nClass;
            *(_QWORD *)&stu_1.Item.m_nId = v5;
            stu_1.Item.m_nCount = v31.m_nCount;
            
            ++nIndex_1;
            CLibraryTable::AddCfgLibraryCost(&thisa->m_CLibraryTable, stu_1);
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::InitLimitTimeTable()
{
  const CDBCFile::FIELD *v1; // rax
  const char *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-E0h] BYREF
  std::string strTime; // [rsp+A0h] [rbp-50h] BYREF
  CfgLimitTime stu; // [rsp+B0h] [rbp-40h] BYREF
  char v6; // [rsp+BFh] [rbp-31h] BYREF
  std::string p_StringTime; // [rsp+C0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/LimitTime.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LIMIT_TIME_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        *(_QWORD *)&stu.nIndex = 0;
        stu.nTime = 0;
        stu.nIndex = readFile.Search_Posistion( i, 0)->iValue;
        stu.nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strTime.assign(v1->pString);
        
        ++nIndex;
        if ( stu.nType == 2 )
        {
          p_StringTime = strTime;
          Answer::DayTime::StringToIntTime(p_StringTime);
        }
        else if ( stu.nType == 3 || stu.nType == 1 )
        {
          v2 = (const char *)std::string::c_str(&strTime);
          stu.nTime = atoi(v2);
        }
        CfgLimitTimeTable::AddLimitTime(&this->m_cfgLimitTimeTable, &stu);
      }
    }
  }
}

//#####################################
void CfgData::InitLittleHelperCfg()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  LittleHelperCfg *v3; // rax
  int v4; // ebx
  ShiQuCfg *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  CDBCFile FileTable(0); // [rsp+10h] [rbp-190h] BYREF
  LittleHelperCfg stu; // [rsp+A0h] [rbp-100h] BYREF
  ShiQuCfg stu_0; // [rsp+D0h] [rbp-D0h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-B0h] BYREF
  _BYTE v11[15]; // [rsp+100h] [rbp-A0h] BYREF
  char v12; // [rsp+10Fh] [rbp-91h] BYREF
  int32_t v13[3]; // [rsp+110h] [rbp-90h] BYREF
  char v14; // [rsp+11Fh] [rbp-81h] BYREF
  MemChrBagVector v15; // [rsp+120h] [rbp-80h] BYREF
  std::string strItems; // [rsp+140h] [rbp-60h] BYREF
  char v17; // [rsp+156h] [rbp-4Ah] BYREF
  int32_t iBaseTableCount; // [rsp+158h] [rbp-48h]
  int32_t iBaseColumnCount; // [rsp+15Ch] [rbp-44h]
  int32_t i; // [rsp+160h] [rbp-40h]
  int32_t nIndex; // [rsp+164h] [rbp-3Ch]
  int32_t iBaseTableCount_0; // [rsp+16Ch] [rbp-34h]
  int32_t iBaseColumnCount_0; // [rsp+170h] [rbp-30h]
  int32_t i_0; // [rsp+174h] [rbp-2Ch]
  int32_t nIndex_0; // [rsp+178h] [rbp-28h]
  int32_t iBaseTableCount_1; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount_1; // [rsp+184h] [rbp-1Ch]
  int32_t i_1; // [rsp+188h] [rbp-18h]
  int32_t nIndex_1; // [rsp+18Ch] [rbp-14h]

  
  if ( !FileTable.OpenFromTXT( "./ServerConfig/Tables/LittleHelper.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_LITTLE_HELPER_CFG_TABLE.txt failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = FileTable.GetRecordsNum();
    iBaseColumnCount = FileTable.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        LittleHelperCfg::LittleHelperCfg(&stu);
        stu.nId = FileTable.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 3;
        stu.nSpeed = FileTable.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        
        std::string::string(v11, "./ServerConfig/Tables/LittleHelper.txt", &v12);
        
        v2 = FileTable.Search_Posistion( i, nIndex);
        std::string::string(v13, v2->pString, &v14);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v13,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttr, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.nGold = FileTable.Search_Posistion( i, ++nIndex)->iValue;
        stu.nReGold = FileTable.Search_Posistion( i, ++nIndex)->iValue;
        stu.nTime = FileTable.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 5;
        stu.nGongGaoId = FileTable.Search_Posistion( i, nIndex++)->iValue;
        v3 = std::map<int,LittleHelperCfg>::operator[](&this->m_LittleHelperCfgMap, &stu.nId);
        LittleHelperCfg::operator=(v3, &stu);
        /* LittleHelperCfg::~LittleHelperCfg(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !FileTable.OpenFromTXT( "./ServerConfig/Tables/ShieldItem.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SHI_QU_TABLE.txt failed,please check!!");
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = FileTable.GetRecordsNum();
      iBaseColumnCount_0 = FileTable.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          stu_0.nId = FileTable.Search_Posistion( i_0, 0)->iValue;
          stu_0.nItemId = FileTable.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nType = FileTable.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          stu_0.nMinGrade = FileTable.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nMaxGrade = FileTable.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          v5 = std::map<int,ShiQuCfg>::operator[](&this->m_ShiQuCfgMap, &stu_0.nId);
          *v5 = stu_0;
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    if ( v4 )
    {
      
      if ( !FileTable.OpenFromTXT( "./ServerConfig/Tables/ZeroBuyPet.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_ZERO_BUY_PET_TABLE.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_1 = FileTable.GetRecordsNum();
        iBaseColumnCount_1 = FileTable.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 2;
            this->m_ZeroBuyPetCfg.nTime = FileTable.Search_Posistion( i_1, 2)->iValue;
            ++nIndex_1;
            
            v6 = FileTable.Search_Posistion( i_1, nIndex_1);
            strItems.assign(v6->pString);
            CItemHelper::parseItemVectorString(&v15, &strItems);
            std::vector<MemChrBag>::operator=(&this->m_ZeroBuyPetCfg.cItems, &v15);
            std::vector<MemChrBag>::~vector(&v15);
            
            this->m_ZeroBuyPetCfg.nGold = FileTable.Search_Posistion( i_1, ++nIndex_1)->iValue;
            this->m_ZeroBuyPetCfg.nMailId = FileTable.Search_Posistion( i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
          }
        }
      }
    }
  }
}

//#####################################
const ZeroBuyPetCfg *CfgData::GetZeroBuyPetCfg()
{
  if ( ZeroBuyPetCfg::IsEmpty(&this->m_ZeroBuyPetCfg) )
    return 0;
  else
    return &this->m_ZeroBuyPetCfg;
}

//#####################################
const ShiQuCfg *CfgData::GetShiQuCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,ShiQuCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,ShiQuCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,ShiQuCfg>::find(&this->m_ShiQuCfgMap, &nIda)._M_node;
  __x._M_node = std::map<int,ShiQuCfg>::end(&thisa->m_ShiQuCfgMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ShiQuCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,ShiQuCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const LittleHelperCfg *CfgData::GetLittleHelperCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,LittleHelperCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,LittleHelperCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,LittleHelperCfg>::find(&this->m_LittleHelperCfgMap, &nIda)._M_node;
  __x._M_node = std::map<int,LittleHelperCfg>::end(&thisa->m_LittleHelperCfgMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,LittleHelperCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,LittleHelperCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitLuckDropTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-1C0h] BYREF
  SpecialItemDrop SpecialItem; // [rsp+A0h] [rbp-130h] BYREF
  LuckDrop stu; // [rsp+D0h] [rbp-100h] BYREF
  StringVector vstack; // [rsp+F0h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+110h] [rbp-C0h] BYREF
  StringVector ItemVetcor; // [rsp+120h] [rbp-B0h] BYREF
  std::string ItemString; // [rsp+140h] [rbp-90h] BYREF
  char v20; // [rsp+14Fh] [rbp-81h] BYREF
  std::string delims; // [rsp+150h] [rbp-80h] BYREF
  char v22; // [rsp+15Fh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+160h] [rbp-70h] BYREF
  std::string v24; // [rsp+170h] [rbp-60h] BYREF
  char v25; // [rsp+17Fh] [rbp-51h] BYREF
  LuckDrop p_stu; // [rsp+180h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+1B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1B4h] [rbp-1Ch]
  int32_t i; // [rsp+1B8h] [rbp-18h]
  int32_t nIndex; // [rsp+1BCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/LuckyRate.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_LUCK_DROP_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 28);
        std::list<SpecialItemDrop>::list(&stu.ItemList);
        stu.Type = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.VipLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        ItemString.assign(v1->pString);
        
        stu.Rate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        delims = "|";
        Answer::StringUtility::split(&ItemVetcor, &ItemString, &delims, 0);
        
        for ( it._M_current = std::vector<std::string>::begin(&ItemVetcor)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&ItemVetcor)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          
          v24 = ":";
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          Answer::StringUtility::split(&vstack, v2, &v24, 0);
          
          if ( std::vector<std::string>::size(&vstack) == 5 )
          {
            memset(&SpecialItem, 0, sizeof(SpecialItem));
            v3 = std::vector<std::string>::operator[](&vstack, 0);
            v4 = (const char *)std::string::c_str(v3);
            SpecialItem.Item.itemId = atoi(v4);
            v5 = std::vector<std::string>::operator[](&vstack, 1u);
            v6 = (const char *)std::string::c_str(v5);
            SpecialItem.Item.itemClass = atoi(v6);
            v7 = std::vector<std::string>::operator[](&vstack, 2u);
            v8 = (const char *)std::string::c_str(v7);
            SpecialItem.Item.itemCount = atoi(v8);
            v9 = std::vector<std::string>::operator[](&vstack, 3u);
            v10 = (const char *)std::string::c_str(v9);
            SpecialItem.Item.bind = atoi(v10);
            v11 = std::vector<std::string>::operator[](&vstack, 4u);
            v12 = (const char *)std::string::c_str(v11);
            SpecialItem.Rate = atoi(v12);
            std::list<SpecialItemDrop>::push_back(&stu.ItemList, &SpecialItem);
          }
          std::vector<std::string>::~vector(&vstack);
        }
        LuckDrop::LuckDrop(&p_stu, &stu);
        LuckDropTable::AddLuckDrop(&this->m_LuckDropTable, &p_stu);
        /* LuckDrop::~LuckDrop(&p_stu); - auto cleanup */
        std::vector<std::string>::~vector(&ItemVetcor);
        /* LuckDrop::~LuckDrop(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitMYSJRewardTable()
{
  CCardGroupBoxManager *v1; // rax
  CCardGroupBoxManager *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgMYSJReward stu; // [rsp+A0h] [rbp-80h] BYREF
  CardGroup card; // [rsp+D0h] [rbp-50h] BYREF
  CardGroupList cardList; // [rsp+E0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+F4h] [rbp-2Ch]
  int32_t iBaseColumnCount; // [rsp+F8h] [rbp-28h]
  int32_t nGroupId; // [rsp+FCh] [rbp-24h]
  int32_t nGroupIndex; // [rsp+100h] [rbp-20h]
  int32_t i; // [rsp+104h] [rbp-1Ch]
  int32_t nIndex; // [rsp+108h] [rbp-18h]
  int32_t nId; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MoYuShiJieReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSJ_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      nGroupId = 0;
      nGroupIndex = 0;
      std::list<CardGroup>::list(&cardList);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nClass = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCount = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBind = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nWeight = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nShow = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nGroup = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMin = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMax = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBroad = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nSpecial = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        if ( stu.nGroup > 0 && stu.nWeight > 0 )
        {
          if ( nGroupId )
          {
            if ( stu.nGroup != nGroupId )
            {
              v1 = Answer::Singleton<CCardGroupBoxManager>::instance();
              CCardGroupBoxManager::Add(v1, nGroupId, &cardList);
              nGroupId = stu.nGroup;
              nGroupIndex = 0;
              std::list<CardGroup>::clear(&cardList);
            }
          }
          else
          {
            nGroupId = stu.nGroup;
          }
          stu.nIndex = ++nGroupIndex;
          card.id = nGroupIndex;
          card.count = stu.nWeight;
          card.min = stu.nMin;
          card.max = stu.nMax;
          std::list<CardGroup>::push_back(&cardList, &card);
        }
        CfgMYSJRewardTable::Add(&this->m_cfgMYSJRewardTable, nId, &stu);
      }
      if ( nGroupId > 0 )
      {
        v2 = Answer::Singleton<CCardGroupBoxManager>::instance();
        CCardGroupBoxManager::Add(v2, nGroupId, &cardList);
      }
      std::list<CardGroup>::~list(&cardList);
    }
  }
}

//#####################################
void CfgData::InitMaintainCompensateTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgMaintainCompensate stu; // [rsp+A0h] [rbp-80h] BYREF
  std::string p_StringTime; // [rsp+C0h] [rbp-60h] BYREF
  char v6; // [rsp+CFh] [rbp-51h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MaintainCompensate.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_MAINTAIN_COMPENSATE_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgMaintainCompensate::CfgMaintainCompensate(&stu);
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        p_StringTime.assign(v1->pString);
        stu.nTime = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        CfgMaintainCompensateTable::Add(&this->m_cfgMaintainCompensateTable, &stu);
        /* CfgMaintainCompensate::~CfgMaintainCompensate(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitMapRoadTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-180h] BYREF
  CfgMapRoad stu; // [rsp+A0h] [rbp-F0h] BYREF
  StringVector vPos; // [rsp+C0h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-B0h] BYREF
  StringVector vRoad; // [rsp+F0h] [rbp-A0h] BYREF
  std::string strRoad; // [rsp+110h] [rbp-80h] BYREF
  char v13; // [rsp+11Fh] [rbp-71h] BYREF
  std::string delims; // [rsp+120h] [rbp-70h] BYREF
  char v15; // [rsp+12Fh] [rbp-61h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+130h] [rbp-60h] BYREF
  std::string v17; // [rsp+140h] [rbp-50h] BYREF
  char v18; // [rsp+14Fh] [rbp-41h] BYREF
  Position __x; // [rsp+150h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+168h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+16Ch] [rbp-24h]
  int32_t i; // [rsp+170h] [rbp-20h]
  int32_t nIndex; // [rsp+174h] [rbp-1Ch]
  int32_t x; // [rsp+178h] [rbp-18h]
  int32_t y; // [rsp+17Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MapRoad.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_ROAD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgMapRoad::CfgMapRoad(&stu);
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nNextIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nMapId = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strRoad.assign(v1->pString);
        
        ++nIndex;
        
        delims = "|";
        Answer::StringUtility::split(&vRoad, &strRoad, &delims, 0);
        
        for ( iter._M_current = std::vector<std::string>::begin(&vRoad)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<std::string>::end(&vRoad)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
            break;
          
          v17 = ":";
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
          Answer::StringUtility::split(&vPos, v2, &v17, 0);
          
          if ( std::vector<std::string>::size(&vPos) == 2 )
          {
            v3 = std::vector<std::string>::operator[](&vPos, 0);
            v4 = (const char *)std::string::c_str(v3);
            x = atoi(v4);
            v5 = std::vector<std::string>::operator[](&vPos, 1u);
            v6 = (const char *)std::string::c_str(v5);
            y = atoi(v6);
            Position::Position(&__x, x, y);
            std::list<Position>::push_back(&stu.road, &__x);
          }
          std::vector<std::string>::~vector(&vPos);
        }
        CfgMapRoadTable::Add(&this->m_cfgMapRoadTable, &stu);
        std::vector<std::string>::~vector(&vRoad);
        /* CfgMapRoad::~CfgMapRoad(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitMingGeTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  CDBCFile readFile(0); // [rsp+10h] [rbp-1B0h] BYREF
  CMingGeCfg stu; // [rsp+A0h] [rbp-120h] BYREF
  Param2 stu_1; // [rsp+E0h] [rbp-E0h] BYREF
  MingGeDrawCost stu_0; // [rsp+F0h] [rbp-D0h]
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-C0h] BYREF
  _BYTE v9[15]; // [rsp+110h] [rbp-B0h] BYREF
  char v10; // [rsp+11Fh] [rbp-A1h] BYREF
  int32_t v11[3]; // [rsp+120h] [rbp-A0h] BYREF
  char v12; // [rsp+12Fh] [rbp-91h] BYREF
  CMingGeCfg p_stu; // [rsp+130h] [rbp-90h] BYREF
  int32_t iBaseTableCount; // [rsp+174h] [rbp-4Ch]
  int32_t iBaseColumnCount; // [rsp+178h] [rbp-48h]
  int32_t i; // [rsp+17Ch] [rbp-44h]
  int32_t nIndex; // [rsp+180h] [rbp-40h]
  int32_t iBaseTableCount_0; // [rsp+188h] [rbp-38h]
  int32_t iBaseColumnCount_0; // [rsp+18Ch] [rbp-34h]
  int32_t i_0; // [rsp+190h] [rbp-30h]
  int32_t nIndex_0; // [rsp+194h] [rbp-2Ch]
  int32_t iBaseTableCount_1; // [rsp+19Ch] [rbp-24h]
  int32_t iBaseColumnCount_1; // [rsp+1A0h] [rbp-20h]
  int32_t i_1; // [rsp+1A4h] [rbp-1Ch]
  int32_t nIndex_1; // [rsp+1A8h] [rbp-18h]
  int32_t nType; // [rsp+1ACh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MingGe.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CMingGeCfg::CMingGeCfg(&stu);
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v9, "./ServerConfig/Tables/MingGe.txt", &v10);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v11, v2->pString, &v12);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v11,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCanPickup = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nQuality = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDecExp = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDecMoney = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nUpExp = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nNextId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCostChip = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CMingGeCfg::CMingGeCfg(&p_stu, &stu);
        CMingGeTable::AddMingGeCfg(&this->m_CMingGeTable, &p_stu);
        /* CMingGeCfg::~CMingGeCfg(&p_stu); - auto cleanup */
        /* CMingGeCfg::~CMingGeCfg(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MingGeDrawCost.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe_0);
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          stu_0.nType = readFile.Search_Posistion( i_0, 0)->iValue;
          stu_0.nConstMoney = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nConstGold = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nRate = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CMingGeTable::AddMingGeDrawCost(&this->m_CMingGeTable, stu_0);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    if ( v3 )
    {
      
      if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MingGeDraw.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileMingGe_1);
      }
      else
      {
        iBaseTableCount_1 = readFile.GetRecordsNum();
        iBaseColumnCount_1 = readFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            nType = readFile.Search_Posistion( i_1, 0)->iValue;
            ++nIndex_1;
            Param2::Param2(&stu_1, 0, 0);
            stu_1.nParam1 = readFile.Search_Posistion( i_1, nIndex_1++)->iValue;
            stu_1.nParam2 = readFile.Search_Posistion( i_1, nIndex_1++)->iValue;
            CMingGeTable::AddMingGeDrawRate(&this->m_CMingGeTable, nType, stu_1);
          }
        }
      }
    }
  }
}

//#####################################
int32_t CfgData::GetMonsterReviveTime(int32_t Time, int32_t BossId)
{
  int32_t result; // eax
  CfgData *v4; // rax

  if ( BossId != 1 )
    return Time;
  if ( Time <= 0 )
    return Time;
  v4 = Answer::Singleton<CfgData>::instance();
  switch ( CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL) )
  {
    case 0:
      result = 10 * (Time / 100);
      break;
    case 1:
    case 2:
      result = 30 * (Time / 100);
      break;
    case 3:
      result = 50 * (Time / 100);
      break;
    case 4:
      result = 60 * (Time / 100);
      break;
    case 5:
      result = 70 * (Time / 100);
      break;
    case 6:
      result = 80 * (Time / 100);
      break;
    default:
      result = Time;
      break;
  }
  return result;
}

//#####################################
void CfgData::InitMiniClientMap()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile(0); // [rsp+20h] [rbp-1A0h] BYREF
  MiniClientCfg stu; // [rsp+B0h] [rbp-110h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-D0h] BYREF
  std::string strItems; // [rsp+110h] [rbp-B0h] BYREF
  char v7; // [rsp+11Fh] [rbp-A1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> >,bool> v8; // [rsp+120h] [rbp-A0h]
  _BYTE v9[80]; // [rsp+130h] [rbp-90h] BYREF
  std::pair<std::string,int> p___x; // [rsp+180h] [rbp-40h] BYREF
  std::string __y; // [rsp+190h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1A4h] [rbp-1Ch]
  int32_t i; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex; // [rsp+1ACh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WeiDuanDaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C9320);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<std::string,int>,MiniClientCfg>::clear(&this->m_GetMiniClientMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.Platform);
        /* std::vector<MemChrBag>::vector(&stu.vItems); */
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::operator=(&stu, v1->pString);
        stu.nId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nType = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.nParam = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.nIcon = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nParam2 = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __y.assign(&stu.Platform);
        std::make_pair<std::string,int>(&p___x.first, (int)&__y);
        std::pair<std::pair const<std::string,int>,MiniClientCfg>::pair(
          (std::pair<const std::pair<std::string,int>,MiniClientCfg> *const)v9,
          &p___x,
          &stu);
        v8 = std::map<std::pair<std::string,int>,MiniClientCfg>::insert(
               &this->m_GetMiniClientMap,
               (const std::pair<const std::pair<std::string,int>,MiniClientCfg> *const)v9);
        std::pair<std::pair const<std::string,int>,MiniClientCfg>::~pair((std::pair<const std::pair<std::string,int>,MiniClientCfg> *const)v9);
        std::pair<std::string,int>::~pair(&p___x);
        /* MiniClientCfg::~MiniClientCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
MiniClientCfg *CfgData::GetMiniClientCfg(std::string *p_Platform, int32_t nId)
{
  std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> > it; // [rsp+20h] [rbp-50h] BYREF
  std::pair<std::string,int> p___x; // [rsp+30h] [rbp-40h] BYREF
  std::string __y[2]; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> > __x; // [rsp+50h] [rbp-20h] BYREF

  std::string::string(__y, p_Platform);
  std::make_pair<std::string,int>(&p___x.first, (int)__y);
  it._M_node = std::map<std::pair<std::string,int>,MiniClientCfg>::find(&this->m_GetMiniClientMap, &p___x)._M_node;
  std::pair<std::string,int>::~pair(&p___x);
  __x._M_node = std::map<std::pair<std::string,int>,MiniClientCfg>::end(&this->m_GetMiniClientMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator!=(&it, &__x) )
    return (MiniClientCfg *)((char *)std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                           + 16);
  else
    return 0;
}

//#####################################
void CfgData::InitMiniClientTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgMiniClient *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgMiniClient stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v8; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WeiDuan.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MINI_CLIENT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::string::string(&stu.strPlatfrom);
        /* std::vector<MemChrBag>::vector(&stu.vReward); */
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::operator=(&stu, v1->pString);
        stu.nIconDownload = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nIconLogin = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        v3 = std::map<std::string,CfgMiniClient>::operator[](&this->m_CfgMiniClient, &stu.strPlatfrom);
        CfgMiniClient::operator=(v3, &stu);
        /* CfgMiniClient::~CfgMiniClient(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
const CfgMiniClient *CfgData::GetMiniClient(const std::string *const platform)
{
  std::_Rb_tree_const_iterator<std::pair<const std::string,CfgMiniClient> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::string,CfgMiniClient> > __x; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::map<std::string,CfgMiniClient>::find(&this->m_CfgMiniClient, platform)._M_node;
  __x._M_node = std::map<std::string,CfgMiniClient>::end(&this->m_CfgMiniClient)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<std::string const,CfgMiniClient>>::operator!=(&iter, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<std::string const,CfgMiniClient>>::operator->(&iter)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitMonsterAddAttrTable()
{
  std::list<CfgMonsterAddAttr> *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  CfgMonsterAddAttr AddAttrs; // [rsp+A0h] [rbp-50h] BYREF
  AttrAddon stu; // [rsp+C0h] [rbp-30h] BYREF
  int32_t Mid; // [rsp+C8h] [rbp-28h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t j; // [rsp+DCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/MonstAddAttr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_ADD_ATTR failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        Mid = TabFile.Search_Posistion( i, 0)->iValue;
        memset(&AddAttrs, 0, sizeof(AddAttrs));
        /* std::vector<AttrAddon>::vector(&AddAttrs.AttrVector); */
        AddAttrs.WorldBossLevelMin = TabFile.Search_Posistion( i, 1)->iValue;
        AddAttrs.WorldBossLevelMax = TabFile.Search_Posistion( i, 2)->iValue;
        for ( j = 0; j <= 6; ++j )
        {
          stu = 0;
          stu.index = TabFile.Search_Posistion( i, 2 * j + 3)->iValue;
          stu.addon = TabFile.Search_Posistion( i, 2 * (j + 2))->iValue;
          std::vector<AttrAddon>::push_back(&AddAttrs.AttrVector, &stu);
        }
        v1 = std::map<int,std::list<CfgMonsterAddAttr>>::operator[](&this->m_MonstAddAttrMap, &Mid);
        std::list<CfgMonsterAddAttr>::push_back(v1, &AddAttrs);
        /* CfgMonsterAddAttr::~CfgMonsterAddAttr(&AddAttrs); - auto cleanup */
      }
    }
  }
}

//#####################################
AttrAddonVector *CfgData::GetAddMonsterAttrs(int32_t Mid,
        int32_t WorldLevel)
{
  std::pair<const int,std::list<CfgMonsterAddAttr> > *v4; // rax
  CfgMonsterAddAttr *v6; // rax
  std::pair<const int,std::list<CfgMonsterAddAttr> > *v7; // rax
  int32_t Mida; // [rsp+4h] [rbp-7Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-78h]
  std::_List_iterator<CfgMonsterAddAttr> iter; // [rsp+10h] [rbp-70h] BYREF
  AttrAddonVector AttrVector; // [rsp+20h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgMonsterAddAttr> > > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgMonsterAddAttr> > > __x; // [rsp+50h] [rbp-30h] BYREF
  std::_List_iterator<CfgMonsterAddAttr> v16; // [rsp+60h] [rbp-20h] BYREF

  thisa = this;
  Mida = Mid;
  it._M_node = std::map<int,std::list<CfgMonsterAddAttr>>::find(&this->m_MonstAddAttrMap, &Mida)._M_node;
  __x._M_node = std::map<int,std::list<CfgMonsterAddAttr>>::end(&thisa->m_MonstAddAttrMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<CfgMonsterAddAttr>>>::operator!=(&it, &__x) )
  {
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::list<CfgMonsterAddAttr>>>::operator->(&it);
    for ( iter._M_node = std::list<CfgMonsterAddAttr>::begin(&v4->second)._M_node;
          std::_List_iterator<CfgMonsterAddAttr>::operator++(&iter) )
    {
      v7 = std::_Rb_tree_iterator<std::pair<int const,std::list<CfgMonsterAddAttr>>>::operator->(&it);
      v16._M_node = std::list<CfgMonsterAddAttr>::end(&v7->second)._M_node;
      if ( !std::_List_iterator<CfgMonsterAddAttr>::operator!=(&iter, &v16) )
        break;
      if ( std::_List_iterator<CfgMonsterAddAttr>::operator->(&iter)->WorldBossLevelMin <= WorldLevel
        && std::_List_iterator<CfgMonsterAddAttr>::operator->(&iter)->WorldBossLevelMax >= WorldLevel )
      {
        v6 = std::_List_iterator<CfgMonsterAddAttr>::operator->(&iter);
        std::vector<AttrAddon>::vector(retstr, &v6->AttrVector);
        return retstr;
      }
    }
  }
  /* std::vector<AttrAddon>::vector(&AttrVector); */
  std::vector<AttrAddon>::vector(retstr, &AttrVector);
  std::vector<AttrAddon>::~vector(&AttrVector);
  return retstr;
}

//#####################################
void CfgData::InitMonsterRandTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-170h] BYREF
  CfgMonsterRand stu; // [rsp+A0h] [rbp-E0h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-A0h] BYREF
  std::string path; // [rsp+100h] [rbp-80h] BYREF
  char v7; // [rsp+10Fh] [rbp-71h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-70h] BYREF
  char v9; // [rsp+11Fh] [rbp-61h] BYREF
  AttrAddonVector v10; // [rsp+120h] [rbp-60h] BYREF
  std::string v11; // [rsp+140h] [rbp-40h] BYREF
  char v12; // [rsp+14Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+150h] [rbp-30h] BYREF
  char v14; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MonsterRand.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_RAND_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgMonsterRand::CfgMonsterRand(&stu);
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/MonsterRand.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.vAttrValue, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        
        v11 = "./ServerConfig/Tables/MonsterRand.txt";
        
        v2 = readFile.Search_Posistion( i, nIndex);
        v13.assign(v2->pString);
        paraseAttrAddon(v10, v13, v11);
        std::vector<AttrAddon>::operator=(&stu.vAttrRatio, &v10);
        std::vector<AttrAddon>::~vector(&v10);
        
        stu.nSkill = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgMonsterRandTable::AddMonsterRand(&this->m_cfgMonsterRandTable, &stu);
        /* CfgMonsterRand::~CfgMonsterRand(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################

void CfgData::InitClbAimCfg()
{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/ClubAim.txt");
    if (ret == false)
    {
        LOG_ERROR("open ./ServerConfig/Tables/ClubAim.txt failed, please check!!!");
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
        ClbAimCfg stu;
        stu.nId = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nNeedVipLevel = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nNeedCount = TabFile.Search_Posistion(i, 2)->iValue;
        stu.nAddDropTimes = TabFile.Search_Posistion(i, 3)->iValue;
        m_ClbAimCfgList.push_back(stu);
    }
}

void CfgData::InitEquipBackTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  const char *v3; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-190h] BYREF
  EquipBack stu; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+E0h] [rbp-C0h] BYREF
  StringVector vStr; // [rsp+F0h] [rbp-B0h] BYREF
  std::string EquipList; // [rsp+110h] [rbp-90h] BYREF
  char v9; // [rsp+11Fh] [rbp-81h] BYREF
  std::string delims; // [rsp+120h] [rbp-80h] BYREF
  char v11; // [rsp+12Fh] [rbp-71h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+130h] [rbp-70h] BYREF
  int __x; // [rsp+13Ch] [rbp-64h] BYREF
  EquipBack p_stu; // [rsp+140h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/EquipRecovery.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ITEM_EQUIP_BACK failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        EquipBack::EquipBack(&stu);
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        EquipList.assign(v1->pString);
        
        ++nIndex;
        
        delims = "|";
        Answer::StringUtility::split(&vStr, &EquipList, &delims, 0);
        
        for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
            break;
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
          v3 = (const char *)std::string::c_str(v2);
          __x = atoi(v3);
          std::list<int>::push_back(&stu.nEquipList, &__x);
        }
        stu.nRecovType = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nRecovValues = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nBuyBackType = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nBuyBackValue = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nOpenDay = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLimitNum = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 3;
        stu.nDisplayDay = readFile.Search_Posistion( i, nIndex++)->iValue;
        EquipBack::EquipBack(&p_stu, &stu);
        CfgEquipTable::AddEquipBack(&this->m_cfgEquip, &p_stu);
        /* EquipBack::~EquipBack(&p_stu); - auto cleanup */
        std::vector<std::string>::~vector(&vStr);
        /* EquipBack::~EquipBack(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitFamilyWarReliveTable()
{
    // NOTICE: CfgFamilyWarRelive struct and m_relive member belong to CfgFamilyWarTable class, not CfgData. No config file was found.
    // This function is kept as a stub for future implementation.
}

void CfgData::InitGameTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  int v4; // ebx
  const CDBCFile::FIELD *v5; // rax
  int v6; // ebx
  int v7; // ebx
  const CDBCFile::FIELD *v8; // rax
  CVipClubLuckyDrop *v9; // rax
  int v10; // ebx
  const CDBCFile::FIELD *v11; // rax
  ZhanHunCfg *v12; // rax
  int v13; // ebx
  const CDBCFile::FIELD *v14; // rax
  const CDBCFile::FIELD *v15; // rax
  SunAndMoonCfg *v16; // rax
  const CDBCFile::FIELD *v17; // rax
  TreasureHunterCfg *v18; // rax
  CDBCFile readFile(0); // [rsp+20h] [rbp-330h] BYREF
  SunAndMoonCfg stu; // [rsp+B0h] [rbp-2A0h] OVERLAPPED BYREF
  ClbAimCfg stu_0; // [rsp+F0h] [rbp-260h] BYREF
  std::list<AddAttribute> __x; // [rsp+100h] [rbp-250h] BYREF
  _BYTE v23[15]; // [rsp+110h] [rbp-240h] BYREF
  char v24; // [rsp+11Fh] [rbp-231h] BYREF
  int32_t v25[3]; // [rsp+120h] [rbp-230h] BYREF
  char v26; // [rsp+12Fh] [rbp-221h] BYREF
  std::list<ItemData> strItems; // [rsp+130h] [rbp-220h] BYREF
  bool bCombi[15]; // [rsp+140h] [rbp-210h] BYREF
  char v29; // [rsp+14Fh] [rbp-201h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,VipEquipPosLevelUp> >,bool> v30; // [rsp+150h] [rbp-200h]
  _BYTE v31[64]; // [rsp+160h] [rbp-1F0h] BYREF
  std::pair<int,int> __a; // [rsp+1A0h] [rbp-1B0h] BYREF
  std::list<AddAttribute> v33; // [rsp+1B0h] [rbp-1A0h] BYREF
  _BYTE v34[15]; // [rsp+1C0h] [rbp-190h] BYREF
  char v35; // [rsp+1CFh] [rbp-181h] BYREF
  int32_t v36[3]; // [rsp+1D0h] [rbp-180h] BYREF
  char v37; // [rsp+1DFh] [rbp-171h] BYREF
  std::list<RateItem> v38; // [rsp+1E0h] [rbp-170h] BYREF
  _BYTE v39[15]; // [rsp+1F0h] [rbp-160h] BYREF
  char v40; // [rsp+1FFh] [rbp-151h] BYREF
  std::list<AddAttribute> v41; // [rsp+200h] [rbp-150h] BYREF
  _BYTE v42[15]; // [rsp+210h] [rbp-140h] BYREF
  char v43; // [rsp+21Fh] [rbp-131h] BYREF
  int32_t v44[3]; // [rsp+220h] [rbp-130h] BYREF
  char v45; // [rsp+22Fh] [rbp-121h] BYREF
  std::list<ItemData> v46; // [rsp+230h] [rbp-120h] BYREF
  bool v47[15]; // [rsp+240h] [rbp-110h] BYREF
  char v48; // [rsp+24Fh] [rbp-101h] BYREF
  std::list<AddAttribute> v49; // [rsp+250h] [rbp-100h] BYREF
  _BYTE v50[15]; // [rsp+260h] [rbp-F0h] BYREF
  char v51; // [rsp+26Fh] [rbp-E1h] BYREF
  int32_t v52[3]; // [rsp+270h] [rbp-E0h] BYREF
  char v53; // [rsp+27Fh] [rbp-D1h] BYREF
  MemChrBagVector v54; // [rsp+280h] [rbp-D0h] BYREF
  std::string v55; // [rsp+2A0h] [rbp-B0h] BYREF
  char v56; // [rsp+2B6h] [rbp-9Ah] BYREF
  int32_t iBaseTableCount; // [rsp+2B8h] [rbp-98h]
  int32_t iBaseColumnCount; // [rsp+2BCh] [rbp-94h]
  int32_t i; // [rsp+2C0h] [rbp-90h]
  int32_t nIndex; // [rsp+2C4h] [rbp-8Ch]
  int32_t iBaseTableCount_0; // [rsp+2CCh] [rbp-84h]
  int32_t iBaseColumnCount_0; // [rsp+2D0h] [rbp-80h]
  int32_t i_0; // [rsp+2D4h] [rbp-7Ch]
  int32_t nIndex_0; // [rsp+2D8h] [rbp-78h]
  int32_t iBaseTableCount_1; // [rsp+2E0h] [rbp-70h]
  int32_t iBaseColumnCount_1; // [rsp+2E4h] [rbp-6Ch]
  int32_t i_1; // [rsp+2E8h] [rbp-68h]
  int32_t nIndex_1; // [rsp+2ECh] [rbp-64h]
  int32_t iBaseTableCount_2; // [rsp+2F4h] [rbp-5Ch]
  int32_t iBaseColumnCount_2; // [rsp+2F8h] [rbp-58h]
  int32_t i_2; // [rsp+2FCh] [rbp-54h]
  int32_t nIndex_2; // [rsp+300h] [rbp-50h]
  int32_t iBaseTableCount_3; // [rsp+308h] [rbp-48h]
  int32_t iBaseColumnCount_3; // [rsp+30Ch] [rbp-44h]
  int32_t i_3; // [rsp+310h] [rbp-40h]
  int32_t nIndex_3; // [rsp+314h] [rbp-3Ch]
  int32_t iBaseTableCount_4; // [rsp+31Ch] [rbp-34h]
  int32_t iBaseColumnCount_4; // [rsp+320h] [rbp-30h]
  int32_t i_4; // [rsp+324h] [rbp-2Ch]
  int32_t nIndex_4; // [rsp+328h] [rbp-28h]
  int32_t iBaseTableCount_5; // [rsp+330h] [rbp-20h]
  int32_t iBaseColumnCount_5; // [rsp+334h] [rbp-1Ch]
  int32_t i_5; // [rsp+338h] [rbp-18h]
  int32_t nIndex_5; // [rsp+33Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/VipClubEquipPos.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileVipEqu);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 52);
        std::list<AddAttribute>::list((std::list<AddAttribute> *const)&stu.lConstItems._M_impl._M_node._M_prev);
        std::list<ItemData>::list((std::list<ItemData> *const)&stu.lAttr._M_impl._M_node._M_prev);
        stu.nLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        *(&stu.nLevel + 1) = readFile.Search_Posistion( i, nIndex++)->iValue;
        LODWORD(stu.lConstItems._M_impl._M_node._M_next) = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v23, "./ServerConfig/Tables/VipClubEquipPos.txt", &v24);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v25, v2->pString, &v26);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v25,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(
          (std::list<AddAttribute> *const)&stu.lConstItems._M_impl._M_node._M_prev,
          &__x);
        std::list<AddAttribute>::~list(&__x);
        
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v3->pString, &v29);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.lAttr._M_impl._M_node._M_prev, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        stu.nSunTelentLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(stu.nLevel, *(&stu.nLevel + 1));
        std::pair<std::pair const<int,int>,VipEquipPosLevelUp>::pair(
          (std::pair<const std::pair<int,int>,VipEquipPosLevelUp> *const)v31,
          &__a,
          (const VipEquipPosLevelUp *const)&stu);
        v30 = std::map<std::pair<int,int>,VipEquipPosLevelUp>::insert(
                &this->m_VipEquipPosLevelUpMap,
                (const std::pair<const std::pair<int,int>,VipEquipPosLevelUp> *const)v31);
        std::pair<std::pair const<int,int>,VipEquipPosLevelUp>::~pair((std::pair<const std::pair<int,int>,VipEquipPosLevelUp> *const)v31);
        VipEquipPosLevelUp::~VipEquipPosLevelUp((VipEquipPosLevelUp *const)&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/VipClubEquipPosSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileVipEqu_0);
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, 32);
          std::list<AddAttribute>::list((std::list<AddAttribute> *const)&stu.lConstItems);
          stu.nLevel = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          *(&stu.nLevel + 1) = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          
          std::string::string(v34, "./ServerConfig/Tables/VipClubEquipPosSuit.txt", &v35);
          
          v5 = readFile.Search_Posistion( i_0, nIndex_0);
          std::string::string(v36, v5->pString, &v37);
          CfgData::parseAddAttribues(
            (CfgData *const)&v33,
            (const std::string *const)this,
            (int32_t)v36,
            (const std::string *const)(unsigned int)nIndex_0);
          std::list<AddAttribute>::operator=((std::list<AddAttribute> *const)&stu.lConstItems, &v33);
          std::list<AddAttribute>::~list(&v33);
          
          LODWORD(stu.lAttr._M_impl._M_node._M_next) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          HIDWORD(stu.lAttr._M_impl._M_node._M_next) = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          std::list<VipEQuipPosSuit>::push_back(&this->m_VipEQuipPosSuitList, (const VipEQuipPosSuit *const)&stu);
          VipEQuipPosSuit::~VipEQuipPosSuit((VipEQuipPosSuit *const)&stu);
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    if ( v4 )
    {
      
      if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ClubAim.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileVipClu);
        v6 = 0;
      }
      else
      {
        iBaseTableCount_1 = readFile.GetRecordsNum();
        iBaseColumnCount_1 = readFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            *(_QWORD *)&stu_0.nId = 0;
            *(_QWORD *)&stu_0.nNeedCount = 0;
            stu_0.nId = readFile.Search_Posistion( i_1, 0)->iValue;
            stu_0.nNeedVipLevel = readFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            stu_0.nNeedCount = readFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            stu_0.nAddDropTimes = readFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            std::list<ClbAimCfg>::push_back(&this->m_ClbAimCfgList, &stu_0);
          }
          v6 = 1;
        }
        else
        {
          v6 = 0;
        }
      }
      if ( v6 )
      {
        
        if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/VipClubLuckyDrop.txt") )
        {
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileVipClu_0);
          v7 = 0;
        }
        else
        {
          iBaseTableCount_2 = readFile.GetRecordsNum();
          iBaseColumnCount_2 = readFile.GetFieldsNum();
          if ( iBaseColumnCount_2 > 0 )
          {
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              nIndex_2 = 0;
              memset(&stu, 0, 28);
              std::list<RateItem>::list((std::list<RateItem> *const)&stu.lConstItems);
              *(&stu.nLevel + 1) = readFile.Search_Posistion( i_2, nIndex_2++)->iValue;
              stu.nLevel = readFile.Search_Posistion( i_2, nIndex_2++)->iValue;
              
              v8 = readFile.Search_Posistion( i_2, nIndex_2);
              std::string::string(v39, v8->pString, &v40);
              CItemHelper::parseRateItemDataListString((const std::string *const)&v38);
              std::list<RateItem>::operator=((std::list<RateItem> *const)&stu.lConstItems, &v38);
              std::list<RateItem>::~list(&v38);
              
              LODWORD(stu.lAttr._M_impl._M_node._M_next) = readFile.Search_Posistion( i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              v9 = std::map<int,CVipClubLuckyDrop>::operator[](&this->m_CVipClubLuckyDropMap, &stu.nLevel);
              CVipClubLuckyDrop::operator=(v9, (const CVipClubLuckyDrop *const)&stu);
              CVipClubLuckyDrop::~CVipClubLuckyDrop((CVipClubLuckyDrop *const)&stu);
            }
            v7 = 1;
          }
          else
          {
            v7 = 0;
          }
        }
        if ( v7 )
        {
          
          if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ZhanHun.txt") )
          {
            Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileVipClu_0);
            v10 = 0;
          }
          else
          {
            iBaseTableCount_3 = readFile.GetRecordsNum();
            iBaseColumnCount_3 = readFile.GetFieldsNum();
            if ( iBaseColumnCount_3 > 0 )
            {
              for ( i_3 = 0; i_3 < iBaseTableCount_3; ++i_3 )
              {
                nIndex_3 = 0;
                memset(&stu, 0, 36);
                std::list<AddAttribute>::list((std::list<AddAttribute> *const)&stu.lConstItems._M_impl._M_node._M_prev);
                stu.nLevel = readFile.Search_Posistion( i_3, nIndex_3++)->iValue;
                *(&stu.nLevel + 1) = readFile.Search_Posistion( i_3, nIndex_3++)->iValue;
                LODWORD(stu.lConstItems._M_impl._M_node._M_next) = CDBCFile::Search_Posistion(
                                                                     &readFile,
                                                                     i_3,
                                                                     nIndex_3++)->iValue;
                
                std::string::string(v42, "./ServerConfig/Tables/ZhanHun.txt", &v43);
                
                v11 = readFile.Search_Posistion( i_3, nIndex_3);
                std::string::string(v44, v11->pString, &v45);
                CfgData::parseAddAttribues(
                  (CfgData *const)&v41,
                  (const std::string *const)this,
                  (int32_t)v44,
                  (const std::string *const)(unsigned int)nIndex_3);
                std::list<AddAttribute>::operator=(
                  (std::list<AddAttribute> *const)&stu.lConstItems._M_impl._M_node._M_prev,
                  &v41);
                std::list<AddAttribute>::~list(&v41);
                
                ++nIndex_3;
                nIndex_3 += 3;
                LODWORD(stu.lAttr._M_impl._M_node._M_prev) = readFile.Search_Posistion( i_3, nIndex_3++)->iValue;
                v12 = std::map<int,ZhanHunCfg>::operator[](&this->m_ZhanHunCfgMap, &stu.nLevel);
                ZhanHunCfg::operator=(v12, (const ZhanHunCfg *const)&stu);
                ZhanHunCfg::~ZhanHunCfg((ZhanHunCfg *const)&stu);
              }
              v10 = 1;
            }
            else
            {
              v10 = 0;
            }
          }
          if ( v10 )
          {
            
            if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/SunAndMoon.txt") )
            {
              Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileVipClu_0);
              v13 = 0;
            }
            else
            {
              iBaseTableCount_4 = readFile.GetRecordsNum();
              iBaseColumnCount_4 = readFile.GetFieldsNum();
              if ( iBaseColumnCount_4 > 0 )
              {
                for ( i_4 = 0; i_4 < iBaseTableCount_4; ++i_4 )
                {
                  nIndex_4 = 0;
                  memset(&stu, 0, sizeof(stu));
                  std::list<ItemData>::list(&stu.lConstItems);
                  std::list<AddAttribute>::list(&stu.lAttr);
                  stu.nLevel = readFile.Search_Posistion( i_4, nIndex_4++)->iValue;
                  
                  v14 = readFile.Search_Posistion( i_4, nIndex_4);
                  std::string::string(v47, v14->pString, &v48);
                  CItemHelper::parseItemDataListString((const std::string *const)&v46, (bool)v47);
                  std::list<ItemData>::operator=(&stu.lConstItems, &v46);
                  std::list<ItemData>::~list(&v46);
                  
                  ++nIndex_4;
                  
                  std::string::string(v50, "./ServerConfig/Tables/SunAndMoon.txt", &v51);
                  
                  v15 = readFile.Search_Posistion( i_4, nIndex_4);
                  std::string::string(v52, v15->pString, &v53);
                  CfgData::parseAddAttribues(
                    (CfgData *const)&v49,
                    (const std::string *const)this,
                    (int32_t)v52,
                    (const std::string *const)(unsigned int)nIndex_4);
                  std::list<AddAttribute>::operator=(&stu.lAttr, &v49);
                  std::list<AddAttribute>::~list(&v49);
                  
                  stu.nGetItemTimes = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  stu.nSunTelentId = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  stu.nSunTelentLevel = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  stu.nMoonTelentId = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  stu.nMoonTelentLevel = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  ++nIndex_4;
                  stu.nGongGaoId = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  ++nIndex_4;
                  v16 = std::map<int,SunAndMoonCfg>::operator[](&this->m_SunAndMoonCfgMap, &stu.nLevel);
                  SunAndMoonCfg::operator=(v16, &stu);
                  /* SunAndMoonCfg::~SunAndMoonCfg(&stu); - auto cleanup */
                }
                v13 = 1;
              }
              else
              {
                v13 = 0;
              }
            }
            if ( v13 )
            {
              
              if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureHunter.txt") )
              {
                Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileTreasu_2);
              }
              else
              {
                iBaseTableCount_5 = readFile.GetRecordsNum();
                iBaseColumnCount_5 = readFile.GetFieldsNum();
                if ( iBaseColumnCount_5 > 0 )
                {
                  for ( i_5 = 0; i_5 < iBaseTableCount_5; ++i_5 )
                  {
                    nIndex_5 = 0;
                    memset(&stu, 0, 44);
                    std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.lConstItems);
                    stu.nLevel = readFile.Search_Posistion( i_5, nIndex_5++)->iValue;
                    
                    v17 = readFile.Search_Posistion( i_5, nIndex_5);
                    v55.assign(v17->pString);
                    CItemHelper::parseItemVectorString(&v54, &v55);
                    std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.lConstItems, &v54);
                    std::vector<MemChrBag>::~vector(&v54);
                    
                    LODWORD(stu.lAttr._M_impl._M_node._M_prev) = readFile.Search_Posistion( i_5, ++nIndex_5)->iValue;
                    ++nIndex_5;
                    ++nIndex_5;
                    HIDWORD(stu.lAttr._M_impl._M_node._M_prev) = readFile.Search_Posistion( i_5, ++nIndex_5)->iValue;
                    stu.nGetItemTimes = readFile.Search_Posistion( i_5, ++nIndex_5)->iValue;
                    ++nIndex_5;
                    v18 = std::map<int,TreasureHunterCfg>::operator[](&this->m_TreasureHunterCfgMap, &stu.nLevel);
                    TreasureHunterCfg::operator=(v18, (const TreasureHunterCfg *const)&stu);
                    TreasureHunterCfg::~TreasureHunterCfg((TreasureHunterCfg *const)&stu);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

//#####################################
const TreasureHunterCfg *CfgData::GetTreasureHunterCfg(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,TreasureHunterCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,TreasureHunterCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,TreasureHunterCfg>::find(&this->m_TreasureHunterCfgMap, &nIda)._M_node;
  __x._M_node = std::map<int,TreasureHunterCfg>::end(&thisa->m_TreasureHunterCfgMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const SunAndMoonCfg *CfgData::GetSunAndMoonCfg(int32_t nLevel)
{
  int32_t nLevela; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,SunAndMoonCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SunAndMoonCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nLevela = nLevel;
  it._M_node = std::map<int,SunAndMoonCfg>::find(&this->m_SunAndMoonCfgMap, &nLevela)._M_node;
  __x._M_node = std::map<int,SunAndMoonCfg>::end(&thisa->m_SunAndMoonCfgMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,SunAndMoonCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,SunAndMoonCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const ZhanHunCfg *CfgData::GetZhanHunCfg(int32_t nLevel)
{
  int32_t nLevela; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,ZhanHunCfg> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,ZhanHunCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nLevela = nLevel;
  iter._M_node = std::map<int,ZhanHunCfg>::find(&this->m_ZhanHunCfgMap, &nLevela)._M_node;
  __x._M_node = std::map<int,ZhanHunCfg>::end(&thisa->m_ZhanHunCfgMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ZhanHunCfg>>::operator!=(&iter, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,ZhanHunCfg>>::operator->(&iter)->second;
  else
    return 0;
}

//#####################################
const VipEquipPosLevelUp *CfgData::GetVipEquipPosLevelUp(int32_t nSlot,
        int32_t nLevel)
{
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,VipEquipPosLevelUp> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,VipEquipPosLevelUp> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(nSlot, nLevel);
  iter._M_node = std::map<std::pair<int,int>,VipEquipPosLevelUp>::find(&this->m_VipEquipPosLevelUpMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,VipEquipPosLevelUp>::end(&this->m_VipEquipPosLevelUpMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,VipEquipPosLevelUp>>::operator!=(&iter, &v6) )
    return (const VipEquipPosLevelUp *)((char *)std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,VipEquipPosLevelUp>>::operator->(&iter)
                                      + 8);
  else
    return 0;
}

//#####################################
const VipEQuipPosSuit *CfgData::GetVipEQuipPosSuit(int32_t nLevel)
{
  const VipEQuipPosSuit *v2; // rax
  std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit> > v4; // [rsp+0h] [rbp-40h] BYREF
  int32_t nLevela; // [rsp+14h] [rbp-2Ch]
  const CfgData *thisa; // [rsp+18h] [rbp-28h]
  std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit> > it; // [rsp+20h] [rbp-20h] BYREF
  std::list<VipEQuipPosSuit> v8; // [rsp+30h] [rbp-10h] BYREF

  thisa = this;
  nLevela = nLevel;
  std::list<VipEQuipPosSuit>::rbegin((const std::list<VipEQuipPosSuit> *const)&it);
  while ( 1 )
  {
    std::list<VipEQuipPosSuit>::rend(&v8);
    if ( !std::operator!=<std::_List_const_iterator<VipEQuipPosSuit>>(
            &it,
            (const std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit> > *const)&v8) )
      break;
    v2 = std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit>>::operator->(&it);
    if ( v2->nLevel <= nLevela )
      return std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit>>::operator*(&it);
    std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit>>::operator++(&v4, (int)&it);
  }
  return 0;
}

//#####################################
const CVipClubLuckyDrop *CfgData::GetCVipClubLuckyDrop(int32_t nCondition)
{
  int32_t nConditiona; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CVipClubLuckyDrop> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CVipClubLuckyDrop> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nConditiona = nCondition;
  it._M_node = std::map<int,CVipClubLuckyDrop>::find(&this->m_CVipClubLuckyDropMap, &nConditiona)._M_node;
  __x._M_node = std::map<int,CVipClubLuckyDrop>::end(&thisa->m_CVipClubLuckyDropMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CVipClubLuckyDrop>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CVipClubLuckyDrop>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitMysteryShopTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  int64_t v3; // rax
  MemChrBag v4; // [rsp+0h] [rbp-150h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-128h]
  CDBCFile readFile(0); // [rsp+30h] [rbp-120h] BYREF
  CfgMysteryShop stu; // [rsp+C0h] [rbp-90h] BYREF
  std::string strItem; // [rsp+110h] [rbp-40h] BYREF
  char v9; // [rsp+11Fh] [rbp-31h] BYREF
  std::string v10; // [rsp+120h] [rbp-30h] BYREF
  char v11; // [rsp+12Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]
  ItemData v17; // 0:kr00_12.12

  thisa = this;
  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/MysteriousShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MYSTERY_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        CItemHelper::parseItemString(&v4, &strItem);
        stu.item = v4;
        
        stu.nCostType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nPrice = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.nRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMinLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nMaxLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBroad = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        v10.assign(v2->pString);
        v17 = CItemHelper::parseItemDataString(&v10);
        LODWORD(v3) = v17.m_nId;
        BYTE4(v3) = v17.m_nClass;
        *(_QWORD *)&stu.exchange.m_nId = v3;
        stu.exchange.m_nCount = v17.m_nCount;
        
        ++nIndex;
        CfgMysteryShopTable::Add(&thisa->m_cfgMysteryShopTable, &stu);
      }
    }
  }
}

//#####################################
void CfgData::InitQQZoneRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgQQGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v6; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/QQZone.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_QQZONE_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgQQGift::CfgQQGift(&gift);
        gift.nIndex = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        gift.nCondition = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgTencentTable::AddQQZoneGift(&this->m_cfgTencentTable, &gift);
        /* CfgQQGift::~CfgQQGift(&gift); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitRefreshMonsterCfgListMap()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<RefreshMonsterCfg> *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-120h] BYREF
  RefreshMonsterCfg stu; // [rsp+A0h] [rbp-90h] BYREF
  int32_t nActId; // [rsp+DCh] [rbp-54h] BYREF
  std::vector<Position> __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string strPos; // [rsp+100h] [rbp-30h] BYREF
  char v8; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ActivityServer.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_ACT_SHUA_GUAI_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        /* std::vector<Position>::vector(&stu.vRevivePosVector); */
        nIndex = 0;
        nActId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nIndex = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCount = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nStartTime = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDiffTime = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strPos.assign(v1->pString);
        CfgData::paresPosition(&__x, this, &strPos);
        std::vector<Position>::operator=(&stu.vRevivePosVector, &__x);
        std::vector<Position>::~vector(&__x);
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<RefreshMonsterCfg>>::operator[](&this->m_RefreshMonsterCfgListMap, &nActId);
        std::list<RefreshMonsterCfg>::push_back(v2, &stu);
        /* RefreshMonsterCfg::~RefreshMonsterCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
// local variable allocation has failed, the output may be wrong!
RefreshMonsterCfgList CfgData::GetRefreshMonsterCfgList(int32_t nActId)
{
  int32_t v2; // edx
  std::pair<const int,std::list<RefreshMonsterCfg> > *v3; // rax
  RefreshMonsterCfgList result; // rax
  int32_t nActIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  RefreshMonsterCfgList stu; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<RefreshMonsterCfg> > > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<RefreshMonsterCfg> > > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = *(CfgData **)&nActId;
  nActIda = v2;
  it._M_node = std::map<int,std::list<RefreshMonsterCfg>>::find(
                 (std::map<int,std::list<RefreshMonsterCfg>> *const)(*(_QWORD *)&nActId + 14168LL),
                 &nActIda)._M_node;
  __x._M_node = std::map<int,std::list<RefreshMonsterCfg>>::end(&thisa->m_RefreshMonsterCfgListMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<RefreshMonsterCfg>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::list<RefreshMonsterCfg>>>::operator->(&it);
    std::list<RefreshMonsterCfg>::list((std::list<RefreshMonsterCfg> *const)this, &v3->second);
  }
  else
  {
    std::list<RefreshMonsterCfg>::list(&stu);
    std::list<RefreshMonsterCfg>::list((std::list<RefreshMonsterCfg> *const)this, &stu);
    std::list<RefreshMonsterCfg>::~list(&stu);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
void CfgData::fetchItem(bool bSend)
{
  CfgItem *v2; // rbx
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  CfgItem *v5; // rbx
  CfgItem *v6; // rbx
  CfgItem *v7; // rbx
  CfgItem *v8; // rbx
  CfgItem *v9; // rbx
  CfgItem *v10; // rbx
  CfgItem *v11; // rbx
  CfgItem *v12; // rbx
  CfgItem *v13; // rbx
  const CDBCFile::FIELD *v14; // rax
  const CDBCFile::FIELD *v15; // rax
  const CDBCFile::FIELD *v16; // rax
  const CDBCFile::FIELD *v17; // rax
  CfgItem *v18; // rbx
  CfgItem *v19; // rbx
  CfgItem *v20; // rbx
  CfgItem *v21; // rbx
  CfgItem *v22; // rbx
  CfgItem *v23; // rbx
  CfgItem *v24; // rbx
  CfgItem *v25; // rbx
  CfgItem *v26; // rbx
  CfgItem *v27; // rbx
  CfgItem *v28; // rbx
  CfgItem *v29; // rbx
  CfgItem *v30; // rbx
  CfgItem *v31; // rbx
  CfgItem *v32; // rbx
  const CDBCFile::FIELD *v33; // rax
  CfgItem **v34; // rax
  CfgItemGiftVector *v36; // rbx
  CfgItemGiftVector **v37; // rax
  CfgItemGiftRandomVector *v38; // rbx
  CfgItemGiftRandomVector **v39; // rax
  CDBCFile ItemGiftRandFile(0); // [rsp+20h] [rbp-310h] BYREF
  CDBCFile ItemGiftFile(0); // [rsp+B0h] [rbp-280h] BYREF
  CDBCFile ItemFile(0); // [rsp+140h] [rbp-1F0h] BYREF
  CfgItemTable newItems; // [rsp+1D0h] [rbp-160h] BYREF
  CfgItemGiftRandom itemGiftRandom; // [rsp+200h] [rbp-130h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftRandomVector*> > it; // [rsp+230h] [rbp-100h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftVector*> > it_0; // [rsp+240h] [rbp-F0h] BYREF
  CfgItemGift itemGift; // [rsp+250h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItem*> > it_1; // [rsp+270h] [rbp-C0h] BYREF
  CfgItem *pItem; // [rsp+278h] [rbp-B8h] BYREF
  std::string str; // [rsp+280h] [rbp-B0h] BYREF
  char v51; // [rsp+28Fh] [rbp-A1h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItem*> > __x; // [rsp+290h] [rbp-A0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,CfgItem*> >,bool> v53; // [rsp+2A0h] [rbp-90h]
  std::pair<const int,CfgItem*> v54; // [rsp+2B0h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftVector*> > v55; // [rsp+2C0h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItemGiftRandomVector*> > v56; // [rsp+2D0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+2E4h] [rbp-4Ch]
  int32_t iBaseColumnCount; // [rsp+2E8h] [rbp-48h]
  int32_t iBaseTableCount_Gift; // [rsp+2F0h] [rbp-40h]
  int32_t iBaseColumnCount_Gift; // [rsp+2F4h] [rbp-3Ch]
  int32_t iBaseTableCount_GiftRand; // [rsp+2FCh] [rbp-34h]
  int32_t iBaseColumnCount_GiftRand; // [rsp+300h] [rbp-30h]
  int32_t i_1; // [rsp+304h] [rbp-2Ch]
  int32_t i_0; // [rsp+308h] [rbp-28h]
  int32_t i; // [rsp+30Ch] [rbp-24h]

  std::map<int,CfgItem *>::map(&newItems);
  Answer::RwLock::wrlock(&this->m_itemsLock);
  
  if ( !ItemFile.OpenFromTXT( "./ServerConfig/Tables/cfg_item.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_item.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = ItemFile.GetRecordsNum();
    iBaseColumnCount = ItemFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i_1 = 0; i_1 < iBaseTableCount; ++i_1 )
      {
        v2 = (CfgItem *)operator new(0xA0u);
        CfgItem::CfgItem(v2);
        pItem = v2;
        v2->id = ItemFile.Search_Posistion( i_1, 0)->iValue;
        v3 = ItemFile.Search_Posistion( i_1, 1);
        std::string::operator=(&pItem->name, v3->pString);
        v4 = ItemFile.Search_Posistion( i_1, 3);
        std::string::operator=(&pItem->desc, v4->pString);
        v5 = pItem;
        v5->type = ItemFile.Search_Posistion( i_1, 4)->iValue;
        v6 = pItem;
        v6->level = ItemFile.Search_Posistion( i_1, 5)->iValue;
        v7 = pItem;
        v7->grade = ItemFile.Search_Posistion( i_1, 6)->iValue;
        v8 = pItem;
        v8->job = ItemFile.Search_Posistion( i_1, 7)->iValue;
        v9 = pItem;
        v9->in_value = ItemFile.Search_Posistion( i_1, 8)->iValue;
        v10 = pItem;
        v10->out_value = ItemFile.Search_Posistion( i_1, 9)->iValue;
        v11 = pItem;
        v11->bind = ItemFile.Search_Posistion( i_1, 10)->iValue;
        v12 = pItem;
        v12->combine = ItemFile.Search_Posistion( i_1, 11)->iValue;
        v13 = pItem;
        v13->quality = ItemFile.Search_Posistion( i_1, 12)->iValue;
        v14 = ItemFile.Search_Posistion( i_1, 13);
        std::string::operator=(&pItem->url, v14->pString);
        v15 = ItemFile.Search_Posistion( i_1, 14);
        std::string::operator=(&pItem->drop_url, v15->pString);
        v16 = ItemFile.Search_Posistion( i_1, 15);
        std::string::operator=(&pItem->effect, v16->pString);
        v17 = ItemFile.Search_Posistion( i_1, 16);
        std::string::operator=(&pItem->use_method, v17->pString);
        v18 = pItem;
        v18->downgrade = ItemFile.Search_Posistion( i_1, 19)->iValue;
        v19 = pItem;
        v19->group_id = ItemFile.Search_Posistion( i_1, 20)->iValue;
        v20 = pItem;
        v20->cd_group = ItemFile.Search_Posistion( i_1, 21)->iValue;
        v21 = pItem;
        v21->overlay = ItemFile.Search_Posistion( i_1, 22)->iValue;
        v22 = pItem;
        v22->can_sell = ItemFile.Search_Posistion( i_1, 23)->iValue;
        v23 = pItem;
        v23->broadcast = ItemFile.Search_Posistion( i_1, 24)->iValue;
        v24 = pItem;
        v24->valid_time = ItemFile.Search_Posistion( i_1, 25)->iValue;
        v25 = pItem;
        v25->item_Grade = ItemFile.Search_Posistion( i_1, 26)->iValue;
        v26 = pItem;
        v26->CanDrop = ItemFile.Search_Posistion( i_1, 32)->iValue;
        v27 = pItem;
        v27->useBroadcast = ItemFile.Search_Posistion( i_1, 33)->iValue;
        v28 = pItem;
        v28->useInCarrier = ItemFile.Search_Posistion( i_1, 35)->iValue;
        v29 = pItem;
        v29->GongGaoId = ItemFile.Search_Posistion( i_1, 40)->iValue;
        v30 = pItem;
        v30->KunLingJingHua = ItemFile.Search_Posistion( i_1, 42)->iValue;
        v31 = pItem;
        v31->XinMoBag = ItemFile.Search_Posistion( i_1, 43)->iValue;
        v32 = pItem;
        
        v33 = ItemFile.Search_Posistion( i_1, 44);
        str.assign(v33->pString);
        v32->RongHeReceovery = CfgData::paraseParam2(this, &str);
        
        it_1._M_node = std::map<int,CfgItem *>::find(&this->m_items, &pItem->id)._M_node;
        __x._M_node = std::map<int,CfgItem *>::end(&this->m_items)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgItem *>>::operator==(&it_1, &__x) )
        {
          std::pair<int const,CfgItem *>::pair(&v54, &pItem->id, &pItem);
          v53 = std::map<int,CfgItem *>::insert(&newItems, &v54);
        }
        v34 = std::map<int,CfgItem *>::operator[](&this->m_items, &pItem->id);
        *v34 = pItem;
      }
      Answer::RwLock::unlock(&this->m_itemsLock);
      if ( !std::map<int,CfgItem *>::empty(&newItems) && bSend )
        CfgData::sendNewItems(this, &newItems);
      Answer::RwLock::wrlock(&this->m_itemGiftsLock);
      std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::clear(&this->m_itemGifts);
      
      if ( !ItemGiftFile.OpenFromTXT( "./ServerConfig/Tables/cfg_item_gift.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_item_gift.txt failed,please check!!");
      }
      else
      {
        iBaseTableCount_Gift = ItemGiftFile.GetRecordsNum();
        iBaseColumnCount_Gift = ItemGiftFile.GetFieldsNum();
        if ( iBaseColumnCount_Gift > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount_Gift; ++i_0 )
          {
            memset(&itemGift, 0, sizeof(itemGift));
            itemGift.id = ItemGiftFile.Search_Posistion( i_0, 0)->iValue;
            itemGift.item = ItemGiftFile.Search_Posistion( i_0, 2)->iValue;
            itemGift.type = ItemGiftFile.Search_Posistion( i_0, 3)->iValue;
            itemGift.count = ItemGiftFile.Search_Posistion( i_0, 4)->iValue;
            itemGift.bind = ItemGiftFile.Search_Posistion( i_0, 5)->iValue;
            itemGift.job = ItemGiftFile.Search_Posistion( i_0, 6)->iValue;
            itemGift.time = ItemGiftFile.Search_Posistion( i_0, 7)->iValue;
            it_0._M_node = std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::find(
                             &this->m_itemGifts,
                             &itemGift.id)._M_node;
            v55._M_node = std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::end(&this->m_itemGifts)._M_node;
            if ( std::_Rb_tree_iterator<std::pair<int const,std::vector<CfgItemGift> *>>::operator==(&it_0, &v55) )
            {
              v36 = (CfgItemGiftVector *)operator new(0x18u);
              std::vector<CfgItemGift>::vector(v36);
              *std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::operator[](
                 &this->m_itemGifts,
                 &itemGift.id) = v36;
            }
            v37 = std::map<int,std::vector<CfgItemGift> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGift> *>>>::operator[](
                    &this->m_itemGifts,
                    &itemGift.id);
            std::vector<CfgItemGift>::push_back(*v37, &itemGift);
          }
          Answer::RwLock::unlock(&this->m_itemGiftsLock);
          Answer::RwLock::wrlock(&this->m_itemGiftRandomsLock);
          std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::clear(&this->m_itemGiftRandoms);
          
          if ( !ItemGiftRandFile.OpenFromTXT( "./ServerConfig/Tables/cfg_item_gift_random.txt") )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open cfg_item_gift_random.txt failed,please check!!");
          }
          else
          {
            iBaseTableCount_GiftRand = ItemGiftRandFile.GetRecordsNum();
            iBaseColumnCount_GiftRand = ItemGiftRandFile.GetFieldsNum();
            if ( iBaseColumnCount_GiftRand > 0 )
            {
              for ( i = 0; i < iBaseTableCount_GiftRand; ++i )
              {
                itemGiftRandom.id = ItemGiftRandFile.Search_Posistion( i, 0)->iValue;
                itemGiftRandom.item = ItemGiftRandFile.Search_Posistion( i, 1)->iValue;
                itemGiftRandom.type = ItemGiftRandFile.Search_Posistion( i, 2)->iValue;
                itemGiftRandom.count = ItemGiftRandFile.Search_Posistion( i, 3)->iValue;
                itemGiftRandom.bind = ItemGiftRandFile.Search_Posistion( i, 4)->iValue;
                itemGiftRandom.static_probability = ItemGiftRandFile.Search_Posistion( i, 5)->iValue;
                itemGiftRandom.sum_probability = ItemGiftRandFile.Search_Posistion( i, 6)->iValue;
                itemGiftRandom.job = ItemGiftRandFile.Search_Posistion( i, 7)->iValue;
                itemGiftRandom.MinLevel = ItemGiftRandFile.Search_Posistion( i, 8)->iValue;
                itemGiftRandom.MaxLevel = ItemGiftRandFile.Search_Posistion( i, 9)->iValue;
                it._M_node = std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::find(
                               &this->m_itemGiftRandoms,
                               &itemGiftRandom.id)._M_node;
                v56._M_node = std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::end(&this->m_itemGiftRandoms)._M_node;
                if ( std::_Rb_tree_iterator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>::operator==(
                       &it,
                       &v56) )
                {
                  v38 = (CfgItemGiftRandomVector *)operator new(0x18u);
                  std::vector<CfgItemGiftRandom>::vector(v38);
                  *std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::operator[](
                     &this->m_itemGiftRandoms,
                     &itemGiftRandom.id) = v38;
                }
                v39 = std::map<int,std::vector<CfgItemGiftRandom> *,std::less<int>,std::allocator<std::pair<int const,std::vector<CfgItemGiftRandom> *>>>::operator[](
                        &this->m_itemGiftRandoms,
                        &itemGiftRandom.id);
                std::vector<CfgItemGiftRandom>::push_back(*v39, &itemGiftRandom);
              }
              Answer::RwLock::unlock(&this->m_itemGiftRandomsLock);
            }
          }
        }
      }
    }
  }
  std::map<int,CfgItem *>::~map(&newItems);
}

//#####################################
void CfgData::fetchJob()
{
  CfgJob *v1; // rax
  CDBCFile JobFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgJob job; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  
  if ( !JobFile.OpenFromTXT( "./ServerConfig/Tables/cfg_job.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_job.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = JobFile.GetRecordsNum();
    iBaseColumnCount = JobFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        job.id = JobFile.Search_Posistion( i, 0)->iValue;
        job.job_task = JobFile.Search_Posistion( i, 4)->iValue;
        job.attack_attr = JobFile.Search_Posistion( i, 5)->iValue;
        job.base_skill = JobFile.Search_Posistion( i, 6)->iValue;
        v1 = std::map<int,CfgJob>::operator[](&this->m_jobs, &job.id);
        *v1 = job;
      }
    }
  }
}

//#####################################
void CfgData::fetchMovie()
{
  CfgMovie *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgMovie movie; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+B4h] [rbp-1Ch]
  int32_t i; // [rsp+B8h] [rbp-18h]
  int32_t MoveId; // [rsp+BCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_movie.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_movie.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        movie.id = TabFile.Search_Posistion( i, 0)->iValue;
        MoveId = TabFile.Search_Posistion( i, 2)->iValue;
        if ( movie.id == MoveId )
        {
          v1 = std::map<int,CfgMovie>::operator[](&this->m_movie, &movie.id);
          v1->id = movie.id;
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchLevelExp()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgLevelExp *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  CfgLevelExp levelExp; // [rsp+A0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+D4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+D8h] [rbp-18h]
  int32_t i; // [rsp+DCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_level_exp.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_level_exp.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        levelExp.level = TabFile.Search_Posistion( i, 0)->iValue;
        v1 = TabFile.Search_Posistion( i, 1);
        levelExp.upgrade_exp = strtoll(v1->pString, 0, 10);
        v2 = TabFile.Search_Posistion( i, 2);
        levelExp.max_exp = strtoll(v2->pString, 0, 10);
        levelExp.pet_exp = TabFile.Search_Posistion( i, 3)->iValue;
        levelExp.mount_exp = TabFile.Search_Posistion( i, 4)->iValue;
        levelExp.vicegeneral_id = TabFile.Search_Posistion( i, 5)->iValue;
        levelExp.attr_point = TabFile.Search_Posistion( i, 6)->iValue;
        levelExp.talent_point = TabFile.Search_Posistion( i, 7)->iValue;
        v3 = std::map<int,CfgLevelExp>::operator[](&this->m_levelExps, &levelExp.level);
        *v3 = levelExp;
      }
    }
  }
}

//#####################################
void CfgData::fetchLevelAttr()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CfgLevelAttr *v3; // rax
  CDBCFile LevelAttrFile(0); // [rsp+10h] [rbp-170h] BYREF
  CfgLevelAttr levelAttr; // [rsp+A0h] [rbp-E0h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-A0h] BYREF
  std::string path; // [rsp+100h] [rbp-80h] BYREF
  char v8; // [rsp+10Fh] [rbp-71h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-70h] BYREF
  char v10; // [rsp+11Fh] [rbp-61h] BYREF
  AttrAddonVector v11; // [rsp+120h] [rbp-60h] BYREF
  std::string v12; // [rsp+140h] [rbp-40h] BYREF
  char v13; // [rsp+14Fh] [rbp-31h] BYREF
  std::string v14; // [rsp+150h] [rbp-30h] BYREF
  char v15; // [rsp+15Bh] [rbp-25h] BYREF
  int __k; // [rsp+15Ch] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+164h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+168h] [rbp-18h]
  int32_t i; // [rsp+16Ch] [rbp-14h]

  
  if ( !LevelAttrFile.OpenFromTXT( "./ServerConfig/Tables/cfg_level_attr.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_PLAYER_LEVEL_ATTR_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = LevelAttrFile.GetRecordsNum();
    iBaseColumnCount = LevelAttrFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgLevelAttr::CfgLevelAttr(&levelAttr);
        levelAttr.level = LevelAttrFile.Search_Posistion( i, 0)->iValue;
        levelAttr.job = LevelAttrFile.Search_Posistion( i, 1)->iValue;
        
        path = "./ServerConfig/Tables/cfg_level_attr.txt";
        
        v1 = LevelAttrFile.Search_Posistion( i, 2);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&levelAttr.addonattr, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        v12 = "./ServerConfig/Tables/cfg_level_attr.txt";
        
        v2 = LevelAttrFile.Search_Posistion( i, 3);
        v14.assign(v2->pString);
        paraseAttrAddon(v11, v14, v12);
        std::vector<AttrAddon>::operator=(&levelAttr.addonPoint, &v11);
        std::vector<AttrAddon>::~vector(&v11);
        
        __k = (levelAttr.job << 16) | levelAttr.level;
        v3 = std::map<int,CfgLevelAttr>::operator[](&this->m_levelAttrs, &__k);
        CfgLevelAttr::operator=(v3, &levelAttr);
        /* CfgLevelAttr::~CfgLevelAttr(&levelAttr); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::fetchMap()
{
  const CDBCFile::FIELD *v1; // rax
  CfgMap *v2; // rax
  CfgMap map; // [rsp+10h] [rbp-140h] BYREF
  CDBCFile MapFile(0); // [rsp+A0h] [rbp-B0h] BYREF
  int32_t iBaseTableCount; // [rsp+134h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+138h] [rbp-18h]
  int32_t i; // [rsp+13Ch] [rbp-14h]

  
  if ( !MapFile.OpenFromTXT( "./ServerConfig/Tables/cfg_map.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MapFile.GetRecordsNum();
    iBaseColumnCount = MapFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgMap::CfgMap(&map);
        map.id = MapFile.Search_Posistion( i, 0)->iValue;
        v1 = MapFile.Search_Posistion( i, 1);
        std::string::operator=(&map.name, v1->pString);
        map.type = MapFile.Search_Posistion( i, 2)->iValue;
        map.param = MapFile.Search_Posistion( i, 3)->iValue;
        map.width = MapFile.Search_Posistion( i, 4)->iValue;
        map.height = MapFile.Search_Posistion( i, 5)->iValue;
        map.revive = MapFile.Search_Posistion( i, 6)->iValue;
        map.pk_mode = MapFile.Search_Posistion( i, 7)->iValue;
        map.anti_protect = MapFile.Search_Posistion( i, 8)->iValue;
        map.isMount = MapFile.Search_Posistion( i, 9)->iValue;
        map.isFly = MapFile.Search_Posistion( i, 10)->iValue;
        map.isVicegeneral = MapFile.Search_Posistion( i, 11)->iValue;
        map.player_level = MapFile.Search_Posistion( i, 12)->iValue;
        map.player_level_max = MapFile.Search_Posistion( i, 13)->iValue;
        map.team_member = MapFile.Search_Posistion( i, 14)->iValue;
        map.hide_mini = MapFile.Search_Posistion( i, 15)->iValue;
        map.runnerId = MapFile.Search_Posistion( i, 23)->iValue;
        map.jump = MapFile.Search_Posistion( i, 30)->iValue;
        map.GongGaoId = MapFile.Search_Posistion( i, 33)->iValue;
        map.reviveTime = MapFile.Search_Posistion( i, 35)->iValue;
        map.pvp = MapFile.Search_Posistion( i, 36)->iValue;
        map.cross = MapFile.Search_Posistion( i, 38)->iValue;
        map.x = MapFile.Search_Posistion( i, 44)->iValue;
        map.y = MapFile.Search_Posistion( i, 45)->iValue;
        map.drop_rate = MapFile.Search_Posistion( i, 47)->iValue;
        map.XingMaiLevel = MapFile.Search_Posistion( i, 48)->iValue;
        map.SuitId = MapFile.Search_Posistion( i, 49)->iValue;
        map.JueWeiLevel = MapFile.Search_Posistion( i, 50)->iValue;
        map.VipLevel = MapFile.Search_Posistion( i, 51)->iValue;
        map.NeedBroadcast = MapFile.Search_Posistion( i, 54)->iValue;
        map.MapCanUsePet = MapFile.Search_Posistion( i, 55)->iValue;
        map.SignOut = MapFile.Search_Posistion( i, 56)->iValue;
        map.Rdx = MapFile.Search_Posistion( i, 58)->iValue;
        map.Refresh = MapFile.Search_Posistion( i, 60)->iValue;
        map.CanRand = MapFile.Search_Posistion( i, 61)->iValue;
        map.LimitDay = MapFile.Search_Posistion( i, 62)->iValue;
        map.XinMoAct = MapFile.Search_Posistion( i, 63)->iValue;
        v2 = std::map<int,CfgMap>::operator[](&this->m_maps, &map.id);
        CfgMap::operator=(v2, &map);
        /* CfgMap::~CfgMap(&map); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::fetchMapMonster()
{
  std::vector<CfgMapMonster> *v1; // rax
  CfgMapMonster *v2; // rax
  CDBCFile MapMonsterFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgMapMonster mapmonster; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !MapMonsterFile.OpenFromTXT( "./ServerConfig/Tables/cfg_map_monster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map_monster.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MapMonsterFile.GetRecordsNum();
    iBaseColumnCount = MapMonsterFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&mapmonster, 0, sizeof(mapmonster));
        mapmonster.id = MapMonsterFile.Search_Posistion( i, 0)->iValue;
        mapmonster.mapid = MapMonsterFile.Search_Posistion( i, 1)->iValue;
        mapmonster.monsterid = MapMonsterFile.Search_Posistion( i, 2)->iValue;
        mapmonster.x = MapMonsterFile.Search_Posistion( i, 3)->iValue;
        mapmonster.y = MapMonsterFile.Search_Posistion( i, 4)->iValue;
        mapmonster.hide = MapMonsterFile.Search_Posistion( i, 5)->iValue;
        mapmonster.side = MapMonsterFile.Search_Posistion( i, 6)->iValue;
        mapmonster.boss = MapMonsterFile.Search_Posistion( i, 7)->iValue;
        mapmonster.Day = MapMonsterFile.Search_Posistion( i, 8)->iValue;
        v1 = std::map<int,std::vector<CfgMapMonster>>::operator[](&this->m_mapMonsters, &mapmonster.mapid);
        std::vector<CfgMapMonster>::push_back(v1, &mapmonster);
        v2 = std::map<int,CfgMapMonster>::operator[](&this->m_CfgMapMonsters, &mapmonster.id);
        *v2 = mapmonster;
      }
    }
  }
}

//#####################################
void CfgData::fetchMapPlant()
{
  std::vector<CfgMapPlant> *v1; // rax
  CfgMapPlant *v2; // rax
  CDBCFile MapPlantFile(0); // [rsp+10h] [rbp-D0h] BYREF
  int32_t id; // [rsp+ACh] [rbp-34h] BYREF
  CfgMapPlant mapPlant; // [rsp+B0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !MapPlantFile.OpenFromTXT( "./ServerConfig/Tables/cfg_map_plant.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map_plant.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MapPlantFile.GetRecordsNum();
    iBaseColumnCount = MapPlantFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        id = MapPlantFile.Search_Posistion( i, 0)->iValue;
        mapPlant.mapid = MapPlantFile.Search_Posistion( i, 1)->iValue;
        mapPlant.plantid = MapPlantFile.Search_Posistion( i, 2)->iValue;
        mapPlant.x = MapPlantFile.Search_Posistion( i, 3)->iValue;
        mapPlant.y = MapPlantFile.Search_Posistion( i, 4)->iValue;
        v1 = std::map<int,std::vector<CfgMapPlant>>::operator[](&this->m_mapPlants, &mapPlant.mapid);
        std::vector<CfgMapPlant>::push_back(v1, &mapPlant);
        v2 = std::map<int,CfgMapPlant>::operator[](&this->m_mMapPlants, &id);
        *v2 = mapPlant;
      }
    }
  }
}

//#####################################
void CfgData::fetchMapRegion()
{
  CfgMapRegion *v1; // rax
  std::vector<CfgMapRegion> *v2; // rax
  CDBCFile MapRegionFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgMapRegion mapRegion; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !MapRegionFile.OpenFromTXT( "./ServerConfig/Tables/cfg_map_region.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_map_region.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MapRegionFile.GetRecordsNum();
    iBaseColumnCount = MapRegionFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        mapRegion.id = MapRegionFile.Search_Posistion( i, 0)->iValue;
        mapRegion.mapid = MapRegionFile.Search_Posistion( i, 2)->iValue;
        mapRegion.min_x = MapRegionFile.Search_Posistion( i, 3)->iValue;
        mapRegion.min_y = MapRegionFile.Search_Posistion( i, 4)->iValue;
        mapRegion.max_x = MapRegionFile.Search_Posistion( i, 5)->iValue;
        mapRegion.max_y = MapRegionFile.Search_Posistion( i, 6)->iValue;
        mapRegion.type = MapRegionFile.Search_Posistion( i, 7)->iValue;
        mapRegion.mId = MapRegionFile.Search_Posistion( i, 9)->iValue;
        v1 = std::map<int,CfgMapRegion>::operator[](&this->m_mapRegions, &mapRegion.id);
        *v1 = mapRegion;
        v2 = std::map<int,std::vector<CfgMapRegion>>::operator[](&this->m_mapRegionsByMapId, &mapRegion.mapid);
        std::vector<CfgMapRegion>::push_back(v2, &mapRegion);
      }
    }
  }
}

//#####################################
void CfgData::fetchMonster()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  std::string *v7; // rax
  const char *v8; // rax
  CfgMonster *v9; // rax
  const CDBCFile::FIELD *v10; // rax
  MemChrBag v11; // [rsp+0h] [rbp-4B0h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-488h]
  CfgMonster monster; // [rsp+30h] [rbp-480h] BYREF
  CDBCFile MonsterBroadcastFile(0); // [rsp+2D0h] [rbp-1E0h] BYREF
  CDBCFile MonsterFile(0); // [rsp+360h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+3F0h] [rbp-C0h] BYREF
  StringVector vRand; // [rsp+400h] [rbp-B0h] BYREF
  std::string randtypes; // [rsp+420h] [rbp-90h] BYREF
  char v19; // [rsp+42Fh] [rbp-81h] BYREF
  std::string strSkill; // [rsp+430h] [rbp-80h] BYREF
  char v21; // [rsp+43Fh] [rbp-71h] BYREF
  std::string v22; // [rsp+440h] [rbp-70h] BYREF
  char v23; // [rsp+44Fh] [rbp-61h] BYREF
  std::string strItem; // [rsp+450h] [rbp-60h] BYREF
  char v25; // [rsp+45Fh] [rbp-51h] BYREF
  std::string delims; // [rsp+460h] [rbp-50h] BYREF
  char v27; // [rsp+46Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+470h] [rbp-40h] BYREF
  int __x; // [rsp+478h] [rbp-38h] BYREF
  int32_t iBaseTableCount; // [rsp+480h] [rbp-30h]
  int32_t iBaseColumnCount; // [rsp+484h] [rbp-2Ch]
  int32_t iBaseTableCountBroadcast; // [rsp+48Ch] [rbp-24h]
  int32_t iBaseColumnCountBroadcast; // [rsp+490h] [rbp-20h]
  int32_t i; // [rsp+494h] [rbp-1Ch]
  int32_t nIndex; // [rsp+498h] [rbp-18h]
  int32_t i_0; // [rsp+49Ch] [rbp-14h]

  thisa = this;
  
  if ( !MonsterFile.OpenFromTXT( "./ServerConfig/Tables/Monster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = MonsterFile.GetRecordsNum();
    iBaseColumnCount = MonsterFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monster, 0, 668);
        /* std::vector<int>::vector(&monster.rand_types); */
        monster.mid = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        monster.group_id = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.level = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.quality = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[1] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[2] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[3] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[4] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[5] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[6] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[7] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[8] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[9] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[10] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[11] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[12] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[13] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[14] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[15] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[16] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[17] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[18] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[19] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[20] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[21] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[22] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[23] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[24] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[25] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[26] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[27] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[28] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.rand_count = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = MonsterFile.Search_Posistion( i, nIndex);
        randtypes.assign(v1->pString);
        
        monster.exp = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.type = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.revive_time = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.skill_id = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v2 = MonsterFile.Search_Posistion( i, nIndex);
        strSkill.assign(v2->pString);
        CfgData::parseMonsterSkill(thisa, monster.mid, (MonsterSkill (*const)[10])monster.unique_skill, &strSkill);
        
        ++nIndex;
        
        v3 = MonsterFile.Search_Posistion( i, nIndex);
        v22.assign(v3->pString);
        CfgData::parseMonsterSkill(thisa, monster.mid, (MonsterSkill (*const)[10])monster.random_skill, &v22);
        
        monster.hpPercent = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.ai = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 9;
        monster.broadcast = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        monster.drop_free = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        monster.boss_sign = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 5;
        monster.BossSocre = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        monster.TaskShare = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 4;
        monster.camp = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        monster.kill_point = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        monster.revive_skin = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        ++nIndex;
        monster.PortalRatio = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.PortalId = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.PortalDuration = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        monster.prestige = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.dust = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.is_building = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.PureDamage = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        monster.IfCurse = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        monster.Score = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.IsShowOwner = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        monster.DiligenceType = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        monster.DiligenceValue = MonsterFile.Search_Posistion( i, nIndex++)->iValue;
        v4 = MonsterFile.Search_Posistion( i, nIndex);
        monster.MonsterHp = strtoll(v4->pString, 0, 10);
        monster.CanTunshi = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.Mid2 = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.FamilyValue = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        monster.vAttr[41] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[42] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[43] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[44] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.IsXinMoMonster = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.QieGe = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[49] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.Energy = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v5 = MonsterFile.Search_Posistion( i, nIndex);
        strItem.assign(v5->pString);
        CItemHelper::parseItemString(&v11, &strItem);
        monster.cItem = v11;
        
        monster.IsSunAndMoon = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        monster.corpse_time = 3000;
        if ( (unsigned __int8)std::string::empty(&randtypes) != 1 && std::operator!=<char>(&randtypes, "-1") )
        {
          
          delims = ":";
          Answer::StringUtility::split(&vRand, &randtypes, &delims, 0);
          
          for ( iter._M_current = std::vector<std::string>::begin(&vRand)._M_current;
                __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<std::string>::end(&vRand)._M_current;
            if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
              break;
            v7 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
            v8 = (const char *)std::string::c_str(v7);
            __x = atoi(v8);
            std::vector<int>::push_back(&monster.rand_types, &__x);
          }
          std::vector<std::string>::~vector(&vRand);
        }
        v9 = std::map<int,CfgMonster>::operator[](&thisa->m_monsters, &monster.mid);
        CfgMonster::operator=(v9, &monster);
        /* CfgMonster::~CfgMonster(&monster); - auto cleanup */
      }
      
      if ( !MonsterBroadcastFile.OpenFromTXT( "./ServerConfig/Tables/cfg_monster_broadcast.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_broadcast.txt failed,please check!!");
      }
      else
      {
        iBaseTableCountBroadcast = MonsterBroadcastFile.GetRecordsNum();
        iBaseColumnCountBroadcast = MonsterBroadcastFile.GetFieldsNum();
        if ( iBaseColumnCountBroadcast > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCountBroadcast; ++i_0 )
          {
            v10 = MonsterBroadcastFile.Search_Posistion( i_0, 1);
            std::vector<int>::push_back(&thisa->m_monsterBroadcasts, (const int *const)v10);
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchMonsterAI()
{
  CfgMonsterAI *v1; // rax
  CDBCFile MonsterFile(0); // [rsp+10h] [rbp-F0h] BYREF
  CfgMonsterAI ai; // [rsp+A0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  
  if ( !MonsterFile.OpenFromTXT( "./ServerConfig/Tables/MonsterAi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_AI_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = MonsterFile.GetRecordsNum();
    iBaseColumnCount = MonsterFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&ai, 0, sizeof(ai));
        ai.id = MonsterFile.Search_Posistion( i, 0)->iValue;
        ai.style = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.target = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.escape_hp = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.view_range = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.move_range = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.rest_range = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.rest_time_min = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.rest_time_max = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.rest_ratio = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.run_distance = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.run_range = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.run_cd = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ai.pursuit_range = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,CfgMonsterAI>::operator[](&this->m_mMonsterAI, &ai.id);
        *v1 = ai;
      }
    }
  }
}

//#####################################
void CfgData::fetchMonsterAdjustTable()
{
  int v1; // ebx
  CfgMonsterAdjust monster; // [rsp+20h] [rbp-3A0h] BYREF
  CDBCFile MonsterFile(0); // [rsp+100h] [rbp-2C0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,CfgMonsterAdjust> >,bool> v4; // [rsp+190h] [rbp-230h]
  _BYTE v5[224]; // [rsp+1A0h] [rbp-220h] BYREF
  std::pair<int,int> __a; // [rsp+280h] [rbp-140h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,CfgMonsterAdjust> >,bool> v7; // [rsp+290h] [rbp-130h]
  _BYTE v8[224]; // [rsp+2A0h] [rbp-120h] BYREF
  std::pair<int,int> v9; // [rsp+380h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+38Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+390h] [rbp-30h]
  int32_t i; // [rsp+394h] [rbp-2Ch]
  int32_t nIndex; // [rsp+398h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+3A0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+3A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+3A8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+3ACh] [rbp-14h]

  
  if ( !MonsterFile.OpenFromTXT( "./ServerConfig/Tables/MonsterAdjust.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONSTER_ADJUST_TABLE failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = MonsterFile.GetRecordsNum();
    iBaseColumnCount = MonsterFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monster, 0, sizeof(monster));
        monster.mid = MonsterFile.Search_Posistion( i, 0)->iValue;
        monster.adj_level = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.level = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[1] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[2] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[3] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[4] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[5] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[6] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[7] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[8] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[9] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[10] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[11] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[12] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[13] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[14] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[15] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[16] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[17] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[18] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[19] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[20] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[21] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[22] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[23] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[24] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[25] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[26] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[27] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[28] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[41] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[42] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[43] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.vAttr[44] = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(monster.mid, monster.adj_level);
        std::pair<std::pair const<int,int>,CfgMonsterAdjust>::pair(
          (std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v5,
          &__a,
          &monster);
        v4 = std::map<std::pair<int,int>,CfgMonsterAdjust>::insert(
               &this->m_mMonsterAdjust,
               (const std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v5);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !MonsterFile.OpenFromTXT( "./ServerConfig/Tables/BossGrow.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_BOSS_GROW_TABLE failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = MonsterFile.GetRecordsNum();
      iBaseColumnCount_0 = MonsterFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&monster, 0, sizeof(monster));
          monster.mid = MonsterFile.Search_Posistion( i_0, 0)->iValue;
          monster.adj_level = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.exp = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          monster.vAttr[1] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[2] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[3] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[4] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[5] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[6] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[7] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[8] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[9] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[10] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[11] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[12] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[13] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[14] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[15] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[16] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[17] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[18] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[19] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[20] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[21] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[22] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[23] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[24] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[25] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[26] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[27] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[28] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[41] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[42] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[43] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          monster.vAttr[44] = MonsterFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          v9 = std::make_pair<int,int>(monster.mid, monster.adj_level);
          std::pair<std::pair const<int,int>,CfgMonsterAdjust>::pair(
            (std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v8,
            &v9,
            &monster);
          v7 = std::map<std::pair<int,int>,CfgMonsterAdjust>::insert(
                 &this->m_mMonsterAdjust,
                 (const std::pair<const std::pair<int,int>,CfgMonsterAdjust> *const)v8);
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchMonsterDropGroup()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  std::vector<CfgMonsterDropGroup> *v3; // rax
  CDBCFile MonsterDropFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgMonsterDropGroup monsterDropGroup; // [rsp+A0h] [rbp-80h] BYREF
  std::string p_StringTime; // [rsp+E0h] [rbp-40h] BYREF
  char v7; // [rsp+EFh] [rbp-31h] BYREF
  std::string v8; // [rsp+F0h] [rbp-30h] BYREF
  char v9; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !MonsterDropFile.OpenFromTXT( "./ServerConfig/Tables/cfg_monster_drop_group.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_drop_group.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MonsterDropFile.GetRecordsNum();
    iBaseColumnCount = MonsterDropFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monsterDropGroup, 0, sizeof(monsterDropGroup));
        monsterDropGroup.group_id = MonsterDropFile.Search_Posistion( i, 0)->iValue;
        monsterDropGroup.item_id = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.item_class = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.item_count = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.bind_type = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.weight = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.probability = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.cost_type = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.cost_value = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.limit_time = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.daily_limit = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = MonsterDropFile.Search_Posistion( i, nIndex);
        p_StringTime.assign(v1->pString);
        monsterDropGroup.start_date = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v2 = MonsterDropFile.Search_Posistion( i, nIndex);
        v8.assign(v2->pString);
        monsterDropGroup.end_date = Answer::DayTime::StringToIntTime(v8);
        
        monsterDropGroup.record = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterDropGroup.festival_group = MonsterDropFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,std::vector<CfgMonsterDropGroup>>::operator[](
               &this->m_monsterDropGroups,
               &monsterDropGroup.group_id);
        std::vector<CfgMonsterDropGroup>::push_back(v3, &monsterDropGroup);
      }
    }
  }
}

//#####################################
void CfgData::fetchMonsterGroupDrop()
{
  std::vector<CfgMonsterGroupDrop> *v1; // rax
  CDBCFile MonsterGroupFile(0); // [rsp+10h] [rbp-E0h] BYREF
  CfgMonsterGroupDrop monsterGroupDrop; // [rsp+A0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]

  
  if ( !MonsterGroupFile.OpenFromTXT( "./ServerConfig/Tables/cfg_monster_group_drop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_group_drop.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MonsterGroupFile.GetRecordsNum();
    iBaseColumnCount = MonsterGroupFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&monsterGroupDrop, 0, sizeof(monsterGroupDrop));
        monsterGroupDrop.mid = MonsterGroupFile.Search_Posistion( i, 0)->iValue;
        monsterGroupDrop.group_id = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.probability = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.begin_time = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.end_time = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.repeat = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.job = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.grow_level = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.dropType = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.bind_type = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.hard = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.quality = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.world_event = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        monsterGroupDrop.DropLimit = MonsterGroupFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        if ( monsterGroupDrop.begin_time >= 0x5A0u
          || monsterGroupDrop.end_time >= 0x5A0u
          || monsterGroupDrop.begin_time > monsterGroupDrop.end_time
          || monsterGroupDrop.repeat <= 0 )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "wrong cfg_monster_group_drop data with mid = %d, group_id = %d\n",
            monsterGroupDrop.mid,
            monsterGroupDrop.group_id);
        }
        v1 = std::map<int,std::vector<CfgMonsterGroupDrop>>::operator[](
               &this->m_monsterGroupDrops,
               &monsterGroupDrop.mid);
        std::vector<CfgMonsterGroupDrop>::push_back(v1, &monsterGroupDrop);
      }
    }
  }
}

//#####################################
void CfgData::fetchMonsterTaskDrop()
{
  std::vector<CfgMonsterTaskDrop> *v1; // rax
  CDBCFile MonsterTaskFile(0); // [rsp+10h] [rbp-C0h] BYREF
  CfgMonsterTaskDrop monsterTaskDrop; // [rsp+A0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+B4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  
  if ( !MonsterTaskFile.OpenFromTXT( "./ServerConfig/Tables/cfg_monster_task_drop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_monster_task_drop.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = MonsterTaskFile.GetRecordsNum();
    iBaseColumnCount = MonsterTaskFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        *(_QWORD *)&monsterTaskDrop.mid = 0;
        *(_QWORD *)&monsterTaskDrop.item = 0;
        monsterTaskDrop.mid = MonsterTaskFile.Search_Posistion( i, 0)->iValue;
        monsterTaskDrop.tid = MonsterTaskFile.Search_Posistion( i, 1)->iValue;
        monsterTaskDrop.item = MonsterTaskFile.Search_Posistion( i, 2)->iValue;
        monsterTaskDrop.probability = MonsterTaskFile.Search_Posistion( i, 3)->iValue;
        v1 = std::map<int,std::vector<CfgMonsterTaskDrop>>::operator[](&this->m_monsterTaskDrops, &monsterTaskDrop.mid);
        std::vector<CfgMonsterTaskDrop>::push_back(v1, &monsterTaskDrop);
      }
    }
  }
}

//#####################################
void CfgData::fetchNpc()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  const char *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  size_t v7; // rbx
  const CDBCFile::FIELD *v8; // rax
  std::string *v9; // rax
  size_t v10; // rbx
  const CDBCFile::FIELD *v11; // rax
  std::string *v12; // rbx
  std::string *v13; // rax
  const char *v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  std::string *v17; // rax
  const char *v18; // rax
  CfgNpc *v19; // rax
  CfgNpcAirport *v20; // rax
  CDBCFile TabFileAir(0); // [rsp+10h] [rbp-360h] BYREF
  CDBCFile TabFile(0); // [rsp+A0h] [rbp-2D0h] BYREF
  CfgNpcAirport airport; // [rsp+130h] [rbp-240h] BYREF
  int iValue; // [rsp+150h] [rbp-220h]
  int v25; // [rsp+154h] [rbp-21Ch]
  int v26; // [rsp+158h] [rbp-218h]
  int v27; // [rsp+15Ch] [rbp-214h]
  std::vector<int> v28; // [rsp+160h] [rbp-210h] BYREF
  char v29; // [rsp+178h] [rbp-1F8h]
  std::vector<std::string> v30; // [rsp+180h] [rbp-1F0h] BYREF
  std::vector<CfgDungeonNpcCost> v31; // [rsp+198h] [rbp-1D8h] BYREF
  CfgDungeonNpcCost NpcCost; // [rsp+1B0h] [rbp-1C0h] BYREF
  StringVector CostItem; // [rsp+1C0h] [rbp-1B0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+1E0h] [rbp-190h] BYREF
  StringVector vpf; // [rsp+1F0h] [rbp-180h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+210h] [rbp-160h] BYREF
  StringVector CostVector; // [rsp+220h] [rbp-150h] BYREF
  std::string platform; // [rsp+240h] [rbp-130h] BYREF
  StringVector vparam; // [rsp+250h] [rbp-120h] BYREF
  std::string param; // [rsp+270h] [rbp-100h] BYREF
  StringVector mapids; // [rsp+280h] [rbp-F0h] BYREF
  std::string delims; // [rsp+2A0h] [rbp-D0h] BYREF
  char v43; // [rsp+2AFh] [rbp-C1h] BYREF
  std::string str; // [rsp+2B0h] [rbp-C0h] BYREF
  char v45; // [rsp+2BFh] [rbp-B1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+2C0h] [rbp-B0h] BYREF
  int __x; // [rsp+2C8h] [rbp-A8h] BYREF
  char v48; // [rsp+2CFh] [rbp-A1h] BYREF
  std::string v49; // [rsp+2D0h] [rbp-A0h] BYREF
  char v50; // [rsp+2E7h] [rbp-89h] BYREF
  int v51; // [rsp+2E8h] [rbp-88h] BYREF
  char v52; // [rsp+2EFh] [rbp-81h] BYREF
  std::string v53; // [rsp+2F0h] [rbp-80h] BYREF
  char v54; // [rsp+2FFh] [rbp-71h] BYREF
  std::string v55; // [rsp+300h] [rbp-70h] BYREF
  char v56; // [rsp+30Fh] [rbp-61h] BYREF
  std::string v57; // [rsp+310h] [rbp-60h] BYREF
  char v58; // [rsp+31Fh] [rbp-51h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v59; // [rsp+320h] [rbp-50h] BYREF
  std::string v60; // [rsp+330h] [rbp-40h] BYREF
  char v61; // [rsp+346h] [rbp-2Ah] BYREF
  bool ret; // [rsp+347h] [rbp-29h]
  int32_t iBaseTableCount; // [rsp+348h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+34Ch] [rbp-24h]
  int32_t i; // [rsp+350h] [rbp-20h]
  uint32_t j; // [rsp+354h] [rbp-1Ch]
  uint32_t j_0; // [rsp+358h] [rbp-18h]
  int32_t i_0; // [rsp+35Ch] [rbp-14h]

  
  ret = TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_npc.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_npc.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgNpc::CfgNpc((CfgNpc *const)&airport);
        airport.id = TabFile.Search_Posistion( i, 0)->iValue;
        airport.npcid = TabFile.Search_Posistion( i, 4)->iValue;
        
        delims = "|";
        
        v1 = TabFile.Search_Posistion( i, 6);
        str.assign(v1->pString);
        Answer::StringUtility::split(&mapids, &str, &delims, 0);
        
        for ( it._M_current = std::vector<std::string>::begin(&mapids)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&mapids)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v3 = (const char *)std::string::c_str(v2);
          __x = atoi(v3);
          std::vector<int>::push_back((std::vector<int> *const)&airport.player_kingdom, &__x);
        }
        iValue = TabFile.Search_Posistion( i, 7)->iValue;
        v25 = TabFile.Search_Posistion( i, 8)->iValue;
        v26 = TabFile.Search_Posistion( i, 9)->iValue;
        v27 = TabFile.Search_Posistion( i, 10)->iValue;
        
        v4 = TabFile.Search_Posistion( i, 21);
        param.assign(v4->pString);
        
        v49 = ":";
        Answer::StringUtility::split(&vparam, &param, &v49, 0);
        
        for ( j = 0; ; ++j )
        {
          v7 = j;
          if ( v7 >= std::vector<std::string>::size(&vparam) )
            break;
          v5 = std::vector<std::string>::operator[](&vparam, j);
          v6 = (const char *)std::string::c_str(v5);
          v51 = atoi(v6);
          std::vector<int>::push_back(&v28, &v51);
        }
        v29 = TabFile.Search_Posistion( i, 23)->iValue;
        
        v8 = TabFile.Search_Posistion( i, 25);
        platform.assign(v8->pString);
        
        if ( std::operator!=<char>(&platform, "0") )
        {
          
          v53 = "|";
          Answer::StringUtility::split(&vpf, &platform, &v53, 0);
          
          for ( j_0 = 0; ; ++j_0 )
          {
            v10 = j_0;
            if ( v10 >= std::vector<std::string>::size(&vpf) )
              break;
            v9 = std::vector<std::string>::operator[](&vpf, j_0);
            std::vector<std::string>::push_back(&v30, v9);
          }
          std::vector<std::string>::~vector(&vpf);
        }
        
        v55 = "|";
        
        v11 = TabFile.Search_Posistion( i, 27);
        v57.assign(v11->pString);
        Answer::StringUtility::split(&CostVector, &v57, &v55, 0);
        
        for ( iter._M_current = std::vector<std::string>::begin(&CostVector)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter, 0) )
        {
          v59._M_current = std::vector<std::string>::end(&CostVector)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &v59) )
            break;
          
          v60 = ":";
          v12 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
          Answer::StringUtility::split(&CostItem, v12, &v60, 0);
          
          *(_QWORD *)&NpcCost.ItemType = 0;
          NpcCost.ItemCount = 0;
          if ( std::vector<std::string>::size(&CostItem) == 3 )
          {
            v13 = std::vector<std::string>::operator[](&CostItem, 0);
            v14 = (const char *)std::string::c_str(v13);
            NpcCost.ItemType = atoi(v14);
            v15 = std::vector<std::string>::operator[](&CostItem, 1u);
            v16 = (const char *)std::string::c_str(v15);
            NpcCost.ItemId = atoi(v16);
            v17 = std::vector<std::string>::operator[](&CostItem, 2u);
            v18 = (const char *)std::string::c_str(v17);
            NpcCost.ItemCount = atoi(v18);
          }
          std::vector<CfgDungeonNpcCost>::push_back(&v31, &NpcCost);
          std::vector<std::string>::~vector(&CostItem);
        }
        v19 = std::map<int,CfgNpc>::operator[](&this->m_npcs, &airport.id);
        CfgNpc::operator=(v19, (const CfgNpc *const)&airport);
        std::vector<std::string>::~vector(&CostVector);
        std::vector<std::string>::~vector(&vparam);
        std::vector<std::string>::~vector(&mapids);
        CfgNpc::~CfgNpc((CfgNpc *const)&airport);
      }
      
      ret = TabFile.OpenFromTXT(Air, "./ServerConfig/Tables/cfg_npc_airport.txt");
      if ( !ret )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_npc_airport.txt failed,please check!!!\n");
      }
      else
      {
        iBaseTableCount = TabFile.GetRecordsNum(Air);
        iBaseColumnCount = TabFile.GetFieldsNum(Air);
        if ( iBaseColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < iBaseTableCount; ++i_0 )
          {
            airport.id = TabFileAir.Search_Posistion( i_0, 0)->iValue;
            airport.npcid = TabFileAir.Search_Posistion( i_0, 1)->iValue;
            airport.player_kingdom = TabFileAir.Search_Posistion( i_0, 3)->iValue;
            airport.kingdom_id = TabFileAir.Search_Posistion( i_0, 4)->iValue;
            airport.map_id = TabFileAir.Search_Posistion( i_0, 5)->iValue;
            airport.map_x = TabFileAir.Search_Posistion( i_0, 6)->iValue;
            airport.map_y = TabFileAir.Search_Posistion( i_0, 7)->iValue;
            airport.cost = TabFileAir.Search_Posistion( i_0, 8)->iValue;
            v20 = std::map<int,CfgNpcAirport>::operator[](&this->m_npcAirports, &airport.id);
            *v20 = airport;
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchPlant()
{
  const CDBCFile::FIELD *v1; // rax
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  const CDBCFile::FIELD *v7; // rax
  std::string *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  CfgPlant *v11; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-250h] BYREF
  CfgPlant plant; // [rsp+A0h] [rbp-1C0h] BYREF
  StringVector RateVt; // [rsp+110h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+130h] [rbp-130h] BYREF
  CfgPlantEvent Event; // [rsp+140h] [rbp-120h] BYREF
  StringVector EventVt; // [rsp+150h] [rbp-110h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+170h] [rbp-F0h] BYREF
  StringVector ItemString; // [rsp+180h] [rbp-E0h] BYREF
  StringVector strItems; // [rsp+1A0h] [rbp-C0h] BYREF
  std::string delims; // [rsp+1C0h] [rbp-A0h] BYREF
  char v22; // [rsp+1CFh] [rbp-91h] BYREF
  std::string str; // [rsp+1D0h] [rbp-90h] BYREF
  char v24; // [rsp+1DFh] [rbp-81h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+1E0h] [rbp-80h] BYREF
  std::string v26; // [rsp+1F0h] [rbp-70h] BYREF
  char v27; // [rsp+1FFh] [rbp-61h] BYREF
  std::string v28; // [rsp+200h] [rbp-60h] BYREF
  char v29; // [rsp+20Fh] [rbp-51h] BYREF
  std::string v30; // [rsp+210h] [rbp-50h] BYREF
  char v31; // [rsp+21Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v32; // [rsp+220h] [rbp-40h] BYREF
  std::string v33; // [rsp+230h] [rbp-30h] BYREF
  char v34; // [rsp+23Bh] [rbp-25h] BYREF
  int __x; // [rsp+23Ch] [rbp-24h] BYREF
  int32_t iBaseTableCount; // [rsp+244h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+248h] [rbp-18h]
  int32_t i; // [rsp+24Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_plant.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_plant.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&plant, 0, sizeof(plant));
        /* std::vector<CfgPlantEvent>::vector(&plant.Events); */
        /* std::vector<int>::vector(&plant.ItemVt); */
        plant.id = TabFile.Search_Posistion( i, 0)->iValue;
        plant.type = TabFile.Search_Posistion( i, 3)->iValue;
        plant.level = TabFile.Search_Posistion( i, 4)->iValue;
        
        delims = "|";
        
        v1 = TabFile.Search_Posistion( i, 5);
        str.assign(v1->pString);
        Answer::StringUtility::split(&strItems, &str, &delims, 0);
        
        for ( it._M_current = std::vector<std::string>::begin(&strItems)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strItems)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          
          v26 = ":";
          v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
          Answer::StringUtility::split(&EventVt, v2, &v26, 0);
          
          if ( std::vector<std::string>::size(&EventVt) == 2 )
          {
            v3 = std::vector<std::string>::operator[](&EventVt, 0);
            v4 = (const char *)std::string::c_str(v3);
            Event.EventId = atoi(v4);
            v5 = std::vector<std::string>::operator[](&EventVt, 1u);
            v6 = (const char *)std::string::c_str(v5);
            Event.Probability = atoi(v6);
            plant.EventMaxRate += Event.Probability;
            std::vector<CfgPlantEvent>::push_back(&plant.Events, &Event);
          }
          std::vector<std::string>::~vector(&EventVt);
        }
        plant.item_cost = TabFile.Search_Posistion( i, 6)->iValue;
        plant.start_hour = TabFile.Search_Posistion( i, 7)->iValue;
        plant.end_hour = TabFile.Search_Posistion( i, 8)->iValue;
        plant.gather_time = TabFile.Search_Posistion( i, 9)->iValue;
        plant.revive_time = TabFile.Search_Posistion( i, 10)->iValue;
        plant.hide_time = TabFile.Search_Posistion( i, 16)->iValue;
        plant.get_points = TabFile.Search_Posistion( i, 18)->iValue;
        plant.boss_id = TabFile.Search_Posistion( i, 19)->iValue;
        plant.BuffId = TabFile.Search_Posistion( i, 20)->iValue;
        plant.revive_skin = TabFile.Search_Posistion( i, 21)->iValue;
        plant.TaskId = TabFile.Search_Posistion( i, 22)->iValue;
        
        v28 = "|";
        
        v7 = TabFile.Search_Posistion( i, 23);
        v30.assign(v7->pString);
        Answer::StringUtility::split(&ItemString, &v30, &v28, 0);
        
        for ( it_0._M_current = std::vector<std::string>::begin(&ItemString)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0) )
        {
          v32._M_current = std::vector<std::string>::end(&ItemString)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v32) )
            break;
          
          v33 = ":";
          v8 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_0);
          Answer::StringUtility::split(&RateVt, v8, &v33, 0);
          
          if ( std::vector<std::string>::size(&RateVt) == 2 )
          {
            v9 = std::vector<std::string>::operator[](&RateVt, 0);
            v10 = (const char *)std::string::c_str(v9);
            __x = atoi(v10);
            std::vector<int>::push_back(&plant.ItemVt, &__x);
          }
          std::vector<std::string>::~vector(&RateVt);
        }
        v11 = std::map<int,CfgPlant>::operator[](&this->m_plants, &plant.id);
        CfgPlant::operator=(v11, &plant);
        std::vector<std::string>::~vector(&ItemString);
        std::vector<std::string>::~vector(&strItems);
        /* CfgPlant::~CfgPlant(&plant); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitShenYaoPosSuitTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-140h] BYREF
  ShenYaoPosSuit stu; // [rsp+A0h] [rbp-B0h] BYREF
  AttrAddonVector __x; // [rsp+C0h] [rbp-90h] BYREF
  std::string path; // [rsp+E0h] [rbp-70h] BYREF
  char v6; // [rsp+EFh] [rbp-61h] BYREF
  std::string addonAttr; // [rsp+F0h] [rbp-60h] BYREF
  char v8; // [rsp+FFh] [rbp-51h] BYREF
  ShenYaoPosSuit p_stu; // [rsp+100h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+130h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+134h] [rbp-1Ch]
  int32_t i; // [rsp+138h] [rbp-18h]
  int32_t nIndex; // [rsp+13Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ShengZhuangSuit.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_POS_SUIT_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        ShenYaoPosSuit::ShenYaoPosSuit(&stu);
        nIndex = 1;
        stu.nLevel = readFile.Search_Posistion( i, 1)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/EquipPosSuit.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        ShenYaoPosSuit::ShenYaoPosSuit(&p_stu, &stu);
        CfgEquipTable::AddShenYaoPosSuit(&this->m_cfgEquip, &p_stu);
        /* ShenYaoPosSuit::~ShenYaoPosSuit(&p_stu); - auto cleanup */
        /* ShenYaoPosSuit::~ShenYaoPosSuit(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitShenYaoPosTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-190h] BYREF
  ShenYaoPos stu; // [rsp+A0h] [rbp-100h] BYREF
  AttrAddonVector __x; // [rsp+E0h] [rbp-C0h] BYREF
  std::string path; // [rsp+100h] [rbp-A0h] BYREF
  char v7; // [rsp+10Fh] [rbp-91h] BYREF
  std::string addonAttr; // [rsp+110h] [rbp-90h] BYREF
  char v9; // [rsp+11Fh] [rbp-81h] BYREF
  std::list<ItemData> strItems; // [rsp+120h] [rbp-80h] BYREF
  bool bCombi[15]; // [rsp+130h] [rbp-70h] BYREF
  char v12; // [rsp+13Fh] [rbp-61h] BYREF
  ShenYaoPos p_stu; // [rsp+140h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+180h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+184h] [rbp-1Ch]
  int32_t i; // [rsp+188h] [rbp-18h]
  int32_t nIndex; // [rsp+18Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ShengZhuangAttr.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ITEM_EQUIP_UP_POS_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        ShenYaoPos::ShenYaoPos(&stu);
        nIndex = 0;
        stu.nSlotId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/ShengZhuangAttr.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v1->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.vAttrAddon, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v2->pString, &v12);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.nCost, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        stu.nGongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ShenYaoPos::ShenYaoPos(&p_stu, &stu);
        CfgEquipTable::AddShenYaoPosCfg(&this->m_cfgEquip, &p_stu);
        /* ShenYaoPos::~ShenYaoPos(&p_stu); - auto cleanup */
        /* ShenYaoPos::~ShenYaoPos(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitShiZhuangLevelTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgShiZhuangLevel stu; // [rsp+A0h] [rbp-70h] BYREF
  AddAttribute AddAttr; // [rsp+E0h] [rbp-30h] BYREF
  int32_t iBaseTableCount; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+F0h] [rbp-20h]
  int32_t i; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+F8h] [rbp-18h]
  int32_t j; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/ShiZhuangLevel.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileShiZhu_2);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgShiZhuangLevel::CfgShiZhuangLevel(&stu);
        nIndex = 0;
        stu.nType = readFile.Search_Posistion( i, 0)->iValue;
        stu.nLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nLevelExp = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nNeedLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCostItem = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nGetExp = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nSmallCritRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nLargeCritRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBroadcast = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        for ( j = 0; j <= 6; ++j )
        {
          AddAttribute::AddAttribute(&AddAttr);
          AddAttr.m_nAddAttrType = readFile.Search_Posistion( i, nIndex++)->iValue;
          AddAttr.m_nAddAttrValue = readFile.Search_Posistion( i, nIndex++)->iValue;
          if ( AddAttr.m_nAddAttrValue > 0 )
            std::list<AddAttribute>::push_back(&stu.vAttr, &AddAttr);
        }
        CfgShiZhuangTable::AddShiZhuangLevel(&this->m_cfgShiZhuangTable, &stu);
        /* CfgShiZhuangLevel::~CfgShiZhuangLevel(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitSpecialBossMapCfgMap()
{
  const CDBCFile::FIELD *v1; // rax
  SpecialBossMapCfg *v2; // rax
  int64_t v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  SpecialBossMapCfg stu; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItem; // [rsp+C0h] [rbp-30h] BYREF
  char v7; // [rsp+CEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+D0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+D4h] [rbp-1Ch]
  int32_t i; // [rsp+D8h] [rbp-18h]
  int32_t nIndex; // [rsp+DCh] [rbp-14h]
  ItemData v13; // 0:kr00_12.12

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/MapConsume.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MAP_BOSS_INFO_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.MapId = TabFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        v13 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v3) = v13.m_nId;
        BYTE4(v3) = v13.m_nClass;
        *(_QWORD *)&stu.ConstItem.m_nId = v3;
        stu.ConstItem.m_nCount = v13.m_nCount;
        
        stu.StartCD = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.ContinuedTime = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,SpecialBossMapCfg>::operator[](&this->m_SpecialBossMapCfgMap, &stu.MapId);
        *v2 = stu;
      }
    }
  }
}

//#####################################
SpecialBossMapCfg *CfgData::GetSpecialBossMapCfg(int32_t MapId)
{
  int32_t MapIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,SpecialBossMapCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SpecialBossMapCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  MapIda = MapId;
  it._M_node = std::map<int,SpecialBossMapCfg>::find(&this->m_SpecialBossMapCfgMap, &MapIda)._M_node;
  __x._M_node = std::map<int,SpecialBossMapCfg>::end(&thisa->m_SpecialBossMapCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,SpecialBossMapCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,SpecialBossMapCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitSpecialMonster()
{
  CDBCFile TabFile(0); // [rsp+10h] [rbp-D0h] BYREF
  cfgSpecialMonster stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/SpecialMonster.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C78C8);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        stu.m_mid = TabFile.Search_Posistion( i, 0)->iValue;
        stu.Type = TabFile.Search_Posistion( i, 1)->iValue;
        stu.Value = TabFile.Search_Posistion( i, 2)->iValue;
        stu.Portal = TabFile.Search_Posistion( i, 3)->iValue;
        stu.Award = TabFile.Search_Posistion( i, 4)->iValue;
        stu.HurtDrop = TabFile.Search_Posistion( i, 5)->iValue;
        stu.EscapeOdds = TabFile.Search_Posistion( i, 6)->iValue;
        cfgSpecialMonsterTable::Add(&this->m_cfgSpecialMonsterTable, &stu);
      }
    }
  }
}

//#####################################
void CfgData::InitTGPRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgTGPGift gift; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+FEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+100h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+104h] [rbp-1Ch]
  int32_t i; // [rsp+108h] [rbp-18h]
  int32_t nIndex; // [rsp+10Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/TGPReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TGP_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&gift, 0, sizeof(gift));
        std::string::string(&gift.strPF);
        /* std::vector<MemChrBag>::vector(&gift.vReward); */
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::operator=(&gift, v1->pString);
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        CfgTencentTable::AddTGPNewerGift(&this->m_cfgTencentTable, &gift);
        /* CfgTGPGift::~CfgTGPGift(&gift); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitTalentPageTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgTalentPage stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  char v6; // [rsp+DFh] [rbp-31h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF
  char v8; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/SkillTree.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_PAGE_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalentPage::CfgTalentPage(&stu);
        stu.job = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(size, "./ServerConfig/Tables/SkillTree.txt", &v6);
        
        v1 = readFile.Search_Posistion( i, nIndex);
        path.assign(v1->pString);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.talents, &__x);
        std::list<int>::~list(&__x);
        
        ++nIndex;
        CfgTalentTable::AddTalentPage(&this->m_cfgTalentTable, &stu);
        /* /* CfgTalentPage::~CfgTalentPage(&stu); - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::fetchTask()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  CfgTask *v7; // rax
  CfgTask task; // [rsp+10h] [rbp-2A0h] BYREF
  CDBCFile TabFile(0); // [rsp+130h] [rbp-180h] BYREF
  MemChrBagVector __x; // [rsp+1C0h] [rbp-F0h] BYREF
  std::string strItems; // [rsp+1E0h] [rbp-D0h] BYREF
  char v12; // [rsp+1EFh] [rbp-C1h] BYREF
  MemChrBagVector v13; // [rsp+1F0h] [rbp-C0h] BYREF
  std::string v14; // [rsp+210h] [rbp-A0h] BYREF
  char v15; // [rsp+21Fh] [rbp-91h] BYREF
  MemChrJobBagVector v16; // [rsp+220h] [rbp-90h] BYREF
  std::string v17; // [rsp+240h] [rbp-70h] BYREF
  char v18; // [rsp+24Fh] [rbp-61h] BYREF
  std::string strRequest; // [rsp+250h] [rbp-60h] BYREF
  char v20; // [rsp+25Fh] [rbp-51h] BYREF
  std::list<TaskDrop> v21; // [rsp+260h] [rbp-50h] BYREF
  _BYTE v22[15]; // [rsp+270h] [rbp-40h] BYREF
  char v23; // [rsp+27Fh] [rbp-31h] BYREF
  std::string path; // [rsp+280h] [rbp-30h] BYREF
  char v25; // [rsp+292h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+294h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+298h] [rbp-18h]
  int32_t i; // [rsp+29Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_task.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_task.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTask::CfgTask(&task);
        task.id = TabFile.Search_Posistion( i, 0)->iValue;
        v1 = TabFile.Search_Posistion( i, 1);
        snprintf(task.name, 0x1Eu, v1->pString);
        task.type = TabFile.Search_Posistion( i, 2)->iValue;
        task.group = TabFile.Search_Posistion( i, 3)->iValue;
        task.can_giveup = TabFile.Search_Posistion( i, 4)->iValue;
        task.pretask = TabFile.Search_Posistion( i, 5)->iValue;
        task.posttask = TabFile.Search_Posistion( i, 6)->iValue;
        task.main_order = TabFile.Search_Posistion( i, 7)->iValue;
        task.job = TabFile.Search_Posistion( i, 8)->iValue;
        task.level = TabFile.Search_Posistion( i, 9)->iValue;
        task.max_level = TabFile.Search_Posistion( i, 10)->iValue;
        task.kingdom = TabFile.Search_Posistion( i, 11)->iValue;
        task.start_npc = TabFile.Search_Posistion( i, 12)->iValue;
        task.end_npc = TabFile.Search_Posistion( i, 13)->iValue;
        task.dungeon = TabFile.Search_Posistion( i, 14)->iValue;
        
        v2 = TabFile.Search_Posistion( i, 15);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&task.items_receive, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        task.award_exp = TabFile.Search_Posistion( i, 16)->iValue;
        task.award_money = TabFile.Search_Posistion( i, 17)->iValue;
        task.gold = TabFile.Search_Posistion( i, 18)->iValue;
        task.dilong = TabFile.Search_Posistion( i, 19)->iValue;
        task.rongyu = TabFile.Search_Posistion( i, 20)->iValue;
        task.fuwen = TabFile.Search_Posistion( i, 21)->iValue;
        task.BossScore = TabFile.Search_Posistion( i, 22)->iValue;
        
        v3 = TabFile.Search_Posistion( i, 23);
        v14.assign(v3->pString);
        CItemHelper::parseItemVectorString(&v13, &v14);
        std::vector<MemChrBag>::operator=(&task.award_item, &v13);
        std::vector<MemChrBag>::~vector(&v13);
        
        v4 = TabFile.Search_Posistion( i, 24);
        v17.assign(v4->pString);
        CfgData::parseTaskItemJobString(&v16, this, task.id, &v17);
        std::vector<MemChrJobBag>::operator=(&task.award_optional, &v16);
        std::vector<MemChrJobBag>::~vector(&v16);
        
        task.condition = TabFile.Search_Posistion( i, 35)->iValue;
        
        v5 = TabFile.Search_Posistion( i, 36);
        strRequest.assign(v5->pString);
        task.request = CfgData::parseTaskCondition(this, task.id, task.condition, &strRequest);
        
        task.GongXian = TabFile.Search_Posistion( i, 50)->iValue;
        task.JunTuanZiJin = TabFile.Search_Posistion( i, 51)->iValue;
        task.Double = TabFile.Search_Posistion( i, 52)->iValue;
        task.acScore = TabFile.Search_Posistion( i, 53)->iValue;
        task.quickDoneCost = TabFile.Search_Posistion( i, 55)->iValue;
        task.quality = TabFile.Search_Posistion( i, 61)->iValue;
        task.ratio = TabFile.Search_Posistion( i, 62)->iValue;
        task.dust = TabFile.Search_Posistion( i, 63)->iValue;
        task.activity_score = TabFile.Search_Posistion( i, 65)->iValue;
        task.talent_point = TabFile.Search_Posistion( i, 67)->iValue;
        
        std::string::string(v22, "./ServerConfig/Tables/cfg_task.txt", &v23);
        
        v6 = TabFile.Search_Posistion( i, 68);
        path.assign(v6->pString);
        CfgData::parseTaskDrop(
          (CfgData *const)&v21,
          (int32_t)this,
          (const std::string *const)(unsigned int)task.id,
          &path);
        std::list<TaskDrop>::operator=(&task.drop_list, &v21);
        std::list<TaskDrop>::~list(&v21);
        
        task.DoubleGold = TabFile.Search_Posistion( i, 69)->iValue;
        task.BuffId = TabFile.Search_Posistion( i, 70)->iValue;
        v7 = std::map<int,CfgTask>::operator[](&this->m_tasks, &task.id);
        CfgTask::operator=(v7, &task);
        if ( task.type == 3 )
          CfgTaskCycleTable::AddTask(&this->m_cfgTaskCycleTable, task.id, task.level, task.max_level);
        if ( task.type == 37 )
          CfgFamilyTask::AddFamilyTask(&this->m_FamilyTaskTable, task.id, task.level, task.max_level);
        if ( task.type == 41 )
          CfgActivityTaskTable::AddTask(&this->m_cfgActivityTaskTable, task.id, task.level, task.max_level, task.ratio);
        /* /* CfgTask::~CfgTask(&task); - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::fetchTrap()
{
  const CDBCFile::FIELD *v1; // rax
  CfgTrap *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgTrap trap; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_trap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_trap.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTrap::CfgTrap(&trap);
        trap.id = TabFile.Search_Posistion( i, 0)->iValue;
        trap.cd = TabFile.Search_Posistion( i, 2)->iValue;
        trap.delay = TabFile.Search_Posistion( i, 3)->iValue;
        trap.event_type = TabFile.Search_Posistion( i, 4)->iValue;
        v1 = TabFile.Search_Posistion( i, 6);
        std::string::operator=(&trap.effect, v1->pString);
        trap.item_cost = TabFile.Search_Posistion( i, 7)->iValue;
        trap.life = TabFile.Search_Posistion( i, 12)->iValue;
        v2 = std::map<int,CfgTrap>::operator[](&this->m_traps, &trap.id);
        CfgTrap::operator=(v2, &trap);
        /* /* CfgTrap::~CfgTrap(&trap); - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
std::vector<Position> *CfgData::paresPosition(
        std::vector<Position> *const std::string *const strPos)
{
  std::string *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  Position stu; // [rsp+10h] [rbp-B0h] BYREF
  StringVector Pos; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-80h] BYREF
  StringVector PosString; // [rsp+50h] [rbp-70h] BYREF
  std::string delims; // [rsp+70h] [rbp-50h] BYREF
  char v15; // [rsp+7Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-40h] BYREF
  std::string v17; // [rsp+90h] [rbp-30h] BYREF
  _BYTE v18[33]; // [rsp+9Fh] [rbp-21h] BYREF

  std::vector<Position>::vector(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strPos) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&PosString, strPos, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&PosString)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&PosString)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v17.assign(":", v18);
      v3 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&Pos, v3, &v17, 0);
      
      if ( std::vector<std::string>::size(&Pos) == 2 )
      {
        Position::Position(&stu, 0, 0);
        v4 = std::vector<std::string>::operator[](&Pos, 0);
        v5 = (const char *)std::string::c_str(v4);
        stu.x = atoi(v5);
        v6 = std::vector<std::string>::operator[](&Pos, 1u);
        v7 = (const char *)std::string::c_str(v6);
        stu.y = atoi(v7);
        std::vector<Position>::push_back(retstr, &stu);
      }
      std::vector<std::string>::~vector(&Pos);
    }
    std::vector<std::string>::~vector(&PosString);
  }
  return retstr;
}

//#####################################
void CfgData::parseItemStringWithJob(int32_t id,
        const std::string *const strItems,
        MemChrBagVector *const items,
        MemChrJobBagVector *const jobItems)
{
  std::string *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  const char *v20; // rax
  MemChrBag itemData; // [rsp+30h] [rbp-D0h] BYREF
  MemChrJobBag job; // [rsp+50h] [rbp-B0h] BYREF
  StringVector item; // [rsp+70h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+90h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+A0h] [rbp-60h] BYREF
  std::string delims; // [rsp+C0h] [rbp-40h] BYREF
  char v30; // [rsp+CFh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+D0h] [rbp-30h] BYREF
  std::string v32; // [rsp+E0h] [rbp-20h] BYREF
  _BYTE v33[17]; // [rsp+EFh] [rbp-11h] BYREF

  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v32.assign(":", v33);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v32, 0);
      
      if ( std::vector<std::string>::size(&item) == 3 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.itemId = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.itemClass = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.itemCount = atoi(v11);
        std::vector<MemChrBag>::push_back(items, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 4 )
      {
        memset(&job, 0, sizeof(job));
        v12 = std::vector<std::string>::operator[](&item, 0);
        v13 = (const char *)std::string::c_str(v12);
        job.id = atoi(v13);
        v14 = std::vector<std::string>::operator[](&item, 1u);
        v15 = (const char *)std::string::c_str(v14);
        job.type = atoi(v15);
        v16 = std::vector<std::string>::operator[](&item, 2u);
        v17 = (const char *)std::string::c_str(v16);
        job.count = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 3u);
        v19 = (const char *)std::string::c_str(v18);
        job.job = atoi(v19);
        std::vector<MemChrJobBag>::push_back(jobItems, &job);
      }
      else
      {
        v20 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseItemString wrong data with id = %d, string = %s\n",
          id,
          v20);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
}

//#####################################
GongGaoList CfgData::parseGongGaoString(int32_t id, const std::string *const strItems)
{
  std::string *v3; // rcx
  GongGaoList result; // rax
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *strItemsa; // [rsp+8h] [rbp-C8h]
  CfgGongGao stu; // [rsp+20h] [rbp-B0h] BYREF
  StringVector item; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v16; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v18; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v19[33]; // [rsp+AFh] [rbp-21h] BYREF

  strItemsa = v3;
  std::list<CfgGongGao>::list((std::list<CfgGongGao> *const)this);
  if ( (unsigned __int8)std::string::empty(strItemsa) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItemsa, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v18.assign(":", v19);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v18, 0);
      
      if ( std::vector<std::string>::size(&item) == 2 )
      {
        stu = 0;
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        stu.Job = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        stu.GongGaoId = atoi(v9);
        std::list<CfgGongGao>::push_back((std::list<CfgGongGao> *const)this, &stu);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
MemChrEquipBagVector *CfgData::parseEquipItemString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  std::string *v20; // rax
  const char *v21; // rax
  std::string *v22; // rax
  const char *v23; // rax
  std::string *v24; // rax
  const char *v25; // rax
  std::string *v26; // rax
  const char *v27; // rax
  std::string *v28; // rax
  const char *v29; // rax
  std::string *v30; // rax
  const char *v31; // rax
  std::string *v32; // rax
  const char *v33; // rax
  std::string *v34; // rax
  const char *v35; // rax
  std::string *v36; // rax
  const char *v37; // rax
  std::string *v38; // rax
  const char *v39; // rax
  std::string *v40; // rax
  const char *v41; // rax
  const char *v42; // rax
  CfgEquipItem itemData_1; // [rsp+20h] [rbp-100h] BYREF
  CfgEquipItem itemData_0; // [rsp+40h] [rbp-E0h] BYREF
  CfgEquipItem itemData; // [rsp+60h] [rbp-C0h] BYREF
  StringVector item; // [rsp+80h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+A0h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+B0h] [rbp-70h] BYREF
  std::string delims; // [rsp+D0h] [rbp-50h] BYREF
  char v53; // [rsp+DFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+E0h] [rbp-40h] BYREF
  std::string v55; // [rsp+F0h] [rbp-30h] BYREF
  _BYTE v56[33]; // [rsp+FFh] [rbp-21h] BYREF

  std::vector<CfgEquipItem>::vector(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1
    && std::string::size((std::string *)strItems) > 4u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v55.assign(":", v56);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v55, 0);
      
      if ( std::vector<std::string>::size(&item) == 5 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.id = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.type = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.count = atoi(v11);
        v12 = std::vector<std::string>::operator[](&item, 3u);
        v13 = (const char *)std::string::c_str(v12);
        itemData.bind = atoi(v13);
        v14 = std::vector<std::string>::operator[](&item, 4u);
        v15 = (const char *)std::string::c_str(v14);
        itemData.job = atoi(v15);
        std::vector<CfgEquipItem>::push_back(retstr, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 6 )
      {
        memset(&itemData_0, 0, sizeof(itemData_0));
        v16 = std::vector<std::string>::operator[](&item, 0);
        v17 = (const char *)std::string::c_str(v16);
        itemData_0.id = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 1u);
        v19 = (const char *)std::string::c_str(v18);
        itemData_0.type = atoi(v19);
        v20 = std::vector<std::string>::operator[](&item, 2u);
        v21 = (const char *)std::string::c_str(v20);
        itemData_0.count = atoi(v21);
        v22 = std::vector<std::string>::operator[](&item, 3u);
        v23 = (const char *)std::string::c_str(v22);
        itemData_0.bind = atoi(v23);
        v24 = std::vector<std::string>::operator[](&item, 4u);
        v25 = (const char *)std::string::c_str(v24);
        itemData_0.job = atoi(v25);
        v26 = std::vector<std::string>::operator[](&item, 5u);
        v27 = (const char *)std::string::c_str(v26);
        itemData_0.star = atoi(v27);
        std::vector<CfgEquipItem>::push_back(retstr, &itemData_0);
      }
      else if ( std::vector<std::string>::size(&item) <= 6 )
      {
        v42 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n",
          id,
          v42);
      }
      else
      {
        memset(&itemData_1, 0, sizeof(itemData_1));
        v28 = std::vector<std::string>::operator[](&item, 0);
        v29 = (const char *)std::string::c_str(v28);
        itemData_1.id = atoi(v29);
        v30 = std::vector<std::string>::operator[](&item, 1u);
        v31 = (const char *)std::string::c_str(v30);
        itemData_1.type = atoi(v31);
        v32 = std::vector<std::string>::operator[](&item, 2u);
        v33 = (const char *)std::string::c_str(v32);
        itemData_1.count = atoi(v33);
        v34 = std::vector<std::string>::operator[](&item, 3u);
        v35 = (const char *)std::string::c_str(v34);
        itemData_1.bind = atoi(v35);
        v36 = std::vector<std::string>::operator[](&item, 4u);
        v37 = (const char *)std::string::c_str(v36);
        itemData_1.job = atoi(v37);
        v38 = std::vector<std::string>::operator[](&item, 5u);
        v39 = (const char *)std::string::c_str(v38);
        itemData_1.star = atoi(v39);
        v40 = std::vector<std::string>::operator[](&item, 6u);
        v41 = (const char *)std::string::c_str(v40);
        itemData_1.weight = atoi(v41);
        std::vector<CfgEquipItem>::push_back(retstr, &itemData_1);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  return retstr;
}

//#####################################
MemChrJobBagVector *CfgData::parseTaskItemJobString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  std::string *v20; // rax
  const char *v21; // rax
  std::string *v22; // rax
  const char *v23; // rax
  std::string *v24; // rax
  const char *v25; // rax
  std::string *v26; // rax
  const char *v27; // rax
  std::string *v28; // rax
  const char *v29; // rax
  std::string *v30; // rax
  const char *v31; // rax
  std::string *v32; // rax
  const char *v33; // rax
  std::string *v34; // rax
  const char *v35; // rax
  const char *v36; // rax
  MemChrJobBag itemData_1; // [rsp+20h] [rbp-100h] BYREF
  MemChrJobBag itemData_0; // [rsp+40h] [rbp-E0h] BYREF
  MemChrJobBag itemData; // [rsp+60h] [rbp-C0h] BYREF
  StringVector item; // [rsp+80h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+A0h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+B0h] [rbp-70h] BYREF
  std::string delims; // [rsp+D0h] [rbp-50h] BYREF
  char v47; // [rsp+DFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+E0h] [rbp-40h] BYREF
  std::string v49; // [rsp+F0h] [rbp-30h] BYREF
  _BYTE v50[33]; // [rsp+FFh] [rbp-21h] BYREF

  std::vector<MemChrJobBag>::vector(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1
    && std::string::size((std::string *)strItems) > 4u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v49.assign(":", v50);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v49, 0);
      
      if ( std::vector<std::string>::size(&item) == 4 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.id = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.type = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.count = atoi(v11);
        v12 = std::vector<std::string>::operator[](&item, 3u);
        v13 = (const char *)std::string::c_str(v12);
        itemData.job = atoi(v13);
        std::vector<MemChrJobBag>::push_back(retstr, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 5 )
      {
        memset(&itemData_0, 0, sizeof(itemData_0));
        v14 = std::vector<std::string>::operator[](&item, 0);
        v15 = (const char *)std::string::c_str(v14);
        itemData_0.id = atoi(v15);
        v16 = std::vector<std::string>::operator[](&item, 1u);
        v17 = (const char *)std::string::c_str(v16);
        itemData_0.type = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 2u);
        v19 = (const char *)std::string::c_str(v18);
        itemData_0.count = atoi(v19);
        v20 = std::vector<std::string>::operator[](&item, 3u);
        v21 = (const char *)std::string::c_str(v20);
        itemData_0.bind = atoi(v21);
        v22 = std::vector<std::string>::operator[](&item, 4u);
        v23 = (const char *)std::string::c_str(v22);
        itemData_0.job = atoi(v23);
        std::vector<MemChrJobBag>::push_back(retstr, &itemData_0);
      }
      else if ( std::vector<std::string>::size(&item) == 6 )
      {
        memset(&itemData_1, 0, sizeof(itemData_1));
        v24 = std::vector<std::string>::operator[](&item, 0);
        v25 = (const char *)std::string::c_str(v24);
        itemData_1.id = atoi(v25);
        v26 = std::vector<std::string>::operator[](&item, 1u);
        v27 = (const char *)std::string::c_str(v26);
        itemData_1.type = atoi(v27);
        v28 = std::vector<std::string>::operator[](&item, 2u);
        v29 = (const char *)std::string::c_str(v28);
        itemData_1.count = atoi(v29);
        v30 = std::vector<std::string>::operator[](&item, 3u);
        v31 = (const char *)std::string::c_str(v30);
        itemData_1.bind = atoi(v31);
        v32 = std::vector<std::string>::operator[](&item, 4u);
        v33 = (const char *)std::string::c_str(v32);
        itemData_1.job = atoi(v33);
        v34 = std::vector<std::string>::operator[](&item, 5u);
        v35 = (const char *)std::string::c_str(v34);
        itemData_1.time = atoi(v35);
        std::vector<MemChrJobBag>::push_back(retstr, &itemData_1);
      }
      else
      {
        v36 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n",
          id,
          v36);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  return retstr;
}

//#####################################
void CfgData::parseMonsterSkill(int32_t id,
        MonsterSkill (*const vSkill)[10],
        const std::string *const strSkill)
{
  int32_t v5; // eax
  std::string *v6; // rbx
  int32_t v7; // r12d
  std::string *v8; // rax
  const char *v9; // rax
  int32_t v10; // r12d
  std::string *v11; // rax
  const char *v12; // rax
  int32_t v13; // r12d
  std::string *v14; // rax
  const char *v15; // rax
  const char *v16; // rax
  StringVector skill; // [rsp+20h] [rbp-80h] BYREF
  StringVector skills; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v22; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v23; // [rsp+70h] [rbp-30h] BYREF
  char v24; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty((std::string *)strSkill) != 1
    && std::string::size((std::string *)strSkill) > 3u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&skills, strSkill, &delims, 0);
    
    if ( std::vector<std::string>::size(&skills) > 9 )
      v5 = 10;
    else
      v5 = std::vector<std::string>::size(&skills);
    isize = v5;
    for ( i = 0; i < isize; ++i )
    {
      
      v23 = ":";
      v6 = std::vector<std::string>::operator[](&skills, i);
      Answer::StringUtility::split(&skill, v6, &v23, 0);
      
      if ( std::vector<std::string>::size(&skill) == 3 )
      {
        v7 = i;
        v8 = std::vector<std::string>::operator[](&skill, 0);
        v9 = (const char *)std::string::c_str(v8);
        (*vSkill)[v7].maxHp = atoi(v9);
        v10 = i;
        v11 = std::vector<std::string>::operator[](&skill, 1u);
        v12 = (const char *)std::string::c_str(v11);
        (*vSkill)[v10].minHp = atoi(v12);
        v13 = i;
        v14 = std::vector<std::string>::operator[](&skill, 2u);
        v15 = (const char *)std::string::c_str(v14);
        (*vSkill)[v13].skillid = atoi(v15);
      }
      else
      {
        v16 = (const char *)std::string::c_str((std::string *)strSkill);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseMonsterSkill wrong data with id = %d, string = %s\n",
          id,
          v16);
      }
      std::vector<std::string>::~vector(&skill);
    }
    std::vector<std::string>::~vector(&skills);
  }
}

//#####################################
MemJobItemTable *CfgData::parseGambleEquip(int32_t id,
        const std::string *const strItems)
{
  std::string *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  MemJobItem *v9; // rax
  const char *v10; // rax
  MemJobItem itemData; // [rsp+20h] [rbp-B0h] BYREF
  StringVector item; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v19; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v21; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v22[33]; // [rsp+AFh] [rbp-21h] BYREF

  std::map<int,MemJobItem>::map(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v21.assign(":", v22);
      v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v4, &v21, 0);
      
      if ( std::vector<std::string>::size(&item) == 2 )
      {
        itemData = 0;
        v5 = std::vector<std::string>::operator[](&item, 0);
        v6 = (const char *)std::string::c_str(v5);
        itemData.job = atoi(v6);
        v7 = std::vector<std::string>::operator[](&item, 1u);
        v8 = (const char *)std::string::c_str(v7);
        itemData.item = atoi(v8);
        v9 = std::map<int,MemJobItem>::operator[](retstr, (const int *const)&itemData);
        *v9 = itemData;
      }
      else
      {
        v10 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseGambleEquip wrong data with id = %d, string = %s\n",
          id,
          v10);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  return retstr;
}

//#####################################
TaskRequest CfgData::parseTaskCondition(int32_t id,
        int32_t condition,
        const std::string *const strRequest)
{
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  const char *v16; // rax
  StringVector requests; // [rsp+30h] [rbp-60h] BYREF
  TaskRequest request; // [rsp+50h] [rbp-40h]
  std::string delims; // [rsp+60h] [rbp-30h] BYREF
  char v21; // [rsp+6Fh] [rbp-21h] BYREF
  TaskRequest v22; // [rsp+70h] [rbp-20h]
  int32_t nSize; // [rsp+7Ch] [rbp-14h]

  *(_QWORD *)&request.param1 = 0;
  request.param3 = 0;
  
  delims = ":";
  Answer::StringUtility::split(&requests, strRequest, &delims, 0);
  
  nSize = std::vector<std::string>::size(&requests);
  switch ( nSize )
  {
    case 3:
      v4 = std::vector<std::string>::operator[](&requests, 0);
      v5 = (const char *)std::string::c_str(v4);
      request.param1 = atoi(v5);
      v6 = std::vector<std::string>::operator[](&requests, 1u);
      v7 = (const char *)std::string::c_str(v6);
      request.param2 = atoi(v7);
      v8 = std::vector<std::string>::operator[](&requests, 2u);
      v9 = (const char *)std::string::c_str(v8);
      request.param3 = atoi(v9);
      break;
    case 2:
      v10 = std::vector<std::string>::operator[](&requests, 0);
      v11 = (const char *)std::string::c_str(v10);
      request.param1 = atoi(v11);
      v12 = std::vector<std::string>::operator[](&requests, 1u);
      v13 = (const char *)std::string::c_str(v12);
      request.param2 = atoi(v13);
      break;
    case 1:
      v14 = std::vector<std::string>::operator[](&requests, 0);
      v15 = (const char *)std::string::c_str(v14);
      request.param1 = atoi(v15);
      break;
    default:
      v16 = (const char *)std::string::c_str((std::string *)strRequest);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::parseTaskCondition wrong data with id = %d, string = %s\n",
        id,
        v16);
      break;
  }
  v22 = request;
  std::vector<std::string>::~vector(&requests);
  return v22;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
TaskDropList CfgData::parseTaskDrop(int32_t id,
        const std::string *const str,
        const std::string *const path)
{
  TaskDropList result; // rax
  std::string *v6; // rax
  const std::string *v7; // rax
  unsigned int64_t v8; // r12
  const std::string *v9; // rax
  const char *v10; // rax
  unsigned int ida; // [rsp+14h] [rbp-ECh]
  TaskDrop stu; // [rsp+20h] [rbp-E0h] BYREF
  std::string strParam; // [rsp+40h] [rbp-C0h] BYREF
  std::string strCount; // [rsp+50h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+60h] [rbp-A0h] BYREF
  StringVector vDrop; // [rsp+70h] [rbp-90h] BYREF
  std::string delims; // [rsp+90h] [rbp-70h] BYREF
  char v19; // [rsp+9Fh] [rbp-61h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+A0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+B0h] [rbp-50h] BYREF
  std::list<Param2> __x; // [rsp+C0h] [rbp-40h] BYREF
  int e; // [rsp+DCh] [rbp-24h]

  ida = (unsigned int)str;
  std::list<TaskDrop>::list((std::list<TaskDrop> *const)this);
  if ( !(unsigned __int8)std::string::empty((std::string *)path) && !std::operator==<char>(path, "-1") )
  {
    
    delims = ",";
    Answer::StringUtility::split(&vDrop, path, &delims, 0);
    
    __i._M_current = std::vector<std::string>::begin(&vDrop)._M_current;
    __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
      &iter,
      &__i);
    while ( 1 )
    {
      __rhs._M_current = std::vector<std::string>::end(&vDrop)._M_current;
      if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      v6 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
      e = std::string::find_first_of(v6, 124, 0);
      v7 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
      std::string::substr(&strCount, (unsigned int64_t)v7, 0);
      v8 = e + 1;
      v9 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
      std::string::substr(&strParam, (unsigned int64_t)v9, v8);
      memset(&stu, 0, sizeof(stu));
      std::list<Param2>::list(&stu.lstJobGroup);
      v10 = (const char *)std::string::c_str(&strCount);
      stu.nCount = atoi(v10);
      CfgData::paraseParam2List(
        (CfgData *const)&__x,
        *(const std::string *const *)&id,
        (int32_t)&strParam,
        (const std::string *const)ida);
      std::list<Param2>::operator=(&stu.lstJobGroup, &__x);
      std::list<Param2>::~list(&__x);
      std::list<TaskDrop>::push_back((std::list<TaskDrop> *const)this, &stu);
      /* /* TaskDrop::~TaskDrop(&stu); - auto cleanup */ - auto cleanup */
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
    }
    std::vector<std::string>::~vector(&vDrop);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
int32_t CfgData::getServerStartTime(SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return this->m_heFuTime;
  else
    return this->m_kaiFuTime;
}

//#####################################
int32_t CfgData::getServerStartDayZeroTime(SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return Answer::DayTime::dayzero(this->m_heFuTime);
  else
    return Answer::DayTime::dayzero(this->m_kaiFuTime);
}

//#####################################
int32_t CfgData::getServerDiffDay(SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return Answer::DayTime::daydiff(this->m_heFuTime);
  else
    return Answer::DayTime::daydiff(this->m_kaiFuTime);
}

//#####################################
void CfgData::fetchServerConfig(int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1060h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-30h] BYREF

  if ( line != 9 )
  {
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `sys_server_start`");
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    v3 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      this->m_heFuTime = Answer::MySqlQuery::getIntValue(&result, "he_fu_time", 0);
      this->m_kaiFuTime = Answer::MySqlQuery::getIntValue(&result, "kai_fu_time", 0);
      this->m_serverType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    }
    Answer::/* /* MySqlQuery::~MySqlQuery(&result); - auto cleanup */ - auto cleanup */
    Answer::/* /* MySqlDBGuard::~MySqlDBGuard(&db); - auto cleanup */ - auto cleanup */
  }
}

//#####################################
void CfgData::updateServerStartTime(int32_t kaiFuTime)
{
  COpenBeta *v2; // rax

  if ( !CfgData::getServerType(this) )
  {
    this->m_kaiFuTime = kaiFuTime;
    v2 = Answer::Singleton<COpenBeta>::instance();
    COpenBeta::updateStartTime(v2);
  }
}

//#####################################
void CfgData::sendNewItems(const CfgItemTable *const items)
{
  GameService *v2; // rax
  int32_t v3; // eax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-10h]
  CfgItem *pCfgItem; // [rsp+38h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2752u);
  if ( packet )
  {
    v3 = std::map<int,CfgItem *>::size(items);
    Answer::NetPacket::writeInt32(packet, v3);
    for ( it._M_node = std::map<int,CfgItem *>::begin(items)._M_node;
          std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator++(&it) )
    {
      __x._M_node = std::map<int,CfgItem *>::end(items)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator!=(&it, &__x) )
        break;
      pCfgItem = std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it)->second;
      if ( pCfgItem )
      {
        Answer::NetPacket::writeInt32(packet, pCfgItem->id);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->name);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->desc);
        Answer::NetPacket::writeInt32(packet, pCfgItem->type);
        Answer::NetPacket::writeInt32(packet, pCfgItem->level);
        Answer::NetPacket::writeInt32(packet, pCfgItem->job);
        Answer::NetPacket::writeInt32(packet, pCfgItem->in_value);
        Answer::NetPacket::writeInt32(packet, pCfgItem->out_value);
        Answer::NetPacket::writeInt32(packet, pCfgItem->bind);
        Answer::NetPacket::writeInt32(packet, pCfgItem->combine);
        Answer::NetPacket::writeInt32(packet, pCfgItem->quality);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->url);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->drop_url);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->effect);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->use_method);
        Answer::NetPacket::writeInt32(packet, pCfgItem->group_id);
        Answer::NetPacket::writeInt32(packet, pCfgItem->cd_group);
        Answer::NetPacket::writeInt32(packet, pCfgItem->overlay);
        Answer::NetPacket::writeInt32(packet, pCfgItem->can_sell);
        Answer::NetPacket::writeInt32(packet, pCfgItem->valid_time);
      }
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v5, packet);
  }
}

//#####################################
void CfgData::InitTouZiTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-1B0h] BYREF
  SevenTouZi stu; // [rsp+A0h] [rbp-120h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-F0h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-D0h] BYREF
  char v8; // [rsp+FFh] [rbp-C1h] BYREF
  SevenTouZi p_stu; // [rsp+100h] [rbp-C0h] BYREF
  MemChrBagVector v10; // [rsp+130h] [rbp-90h] BYREF
  std::string v11; // [rsp+150h] [rbp-70h] BYREF
  char v12; // [rsp+15Fh] [rbp-61h] BYREF
  MonthTouZi v13; // [rsp+160h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+18Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+190h] [rbp-30h]
  int32_t i; // [rsp+194h] [rbp-2Ch]
  int32_t nIndex; // [rsp+198h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+1A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+1ACh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/QiRiTouZi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SEVEN_DAY_TOU_ZI_TABEL failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vItem);
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCondition = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        SevenTouZi::SevenTouZi(&p_stu, &stu);
        CfgTouZiTable::AddSevenTouZi(&this->m_cfgTouZiTable, &p_stu);
        /* /* SevenTouZi::~SevenTouZi(&p_stu); - auto cleanup */ - auto cleanup */
        /* /* SevenTouZi::~SevenTouZi(&stu); - auto cleanup */ - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/ChaoJiTouZi.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONTH_TOU_ZI_TABLE failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, 36);
          std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.nCondition);
          stu.nId = TabFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          ++nIndex_0;
          
          v3 = TabFile.Search_Posistion( i_0, nIndex_0);
          v11.assign(v3->pString);
          CItemHelper::parseItemVectorString(&v10, &v11);
          std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.nCondition, &v10);
          std::vector<MemChrBag>::~vector(&v10);
          
          LODWORD(stu.vItem._M_impl._M_end_of_storage) = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          MonthTouZi::MonthTouZi(&v13, (const MonthTouZi *const)&stu);
          CfgTouZiTable::AddMonthTouZi(&this->m_cfgTouZiTable, &v13);
          /* /* MonthTouZi::~MonthTouZi(&v13); - auto cleanup */ - auto cleanup */
          MonthTouZi::~MonthTouZi((MonthTouZi *const)&stu);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitTreasureMapTabale()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  int *v8; // rbx
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  const std::string *v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  std::string *v17; // rax
  const char *v18; // rax
  std::string *v19; // rax
  const char *v20; // rax
  const CDBCFile::FIELD *v21; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-320h] BYREF
  TreasureMapCfg stu; // [rsp+A0h] [rbp-290h] BYREF
  TreasureMapEventCfg stu_0; // [rsp+100h] [rbp-230h] BYREF
  MapPos stuPos; // [rsp+120h] [rbp-210h] BYREF
  StringVector vstr_0; // [rsp+130h] [rbp-200h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin_0; // [rsp+150h] [rbp-1E0h] BYREF
  StringVector SplitStr_0; // [rsp+160h] [rbp-1D0h] BYREF
  StringVector vstr; // [rsp+180h] [rbp-1B0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+1A0h] [rbp-190h] BYREF
  StringVector SplitStr; // [rsp+1B0h] [rbp-180h] BYREF
  std::string MapPosString; // [rsp+1D0h] [rbp-160h] BYREF
  std::string RateString; // [rsp+1E0h] [rbp-150h] BYREF
  char v34; // [rsp+1EEh] [rbp-142h] BYREF
  char v35; // [rsp+1EFh] [rbp-141h] BYREF
  std::string delims; // [rsp+1F0h] [rbp-140h] BYREF
  char v37; // [rsp+1FFh] [rbp-131h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+200h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+210h] [rbp-120h] BYREF
  std::string v40; // [rsp+220h] [rbp-110h] BYREF
  char v41; // [rsp+22Bh] [rbp-105h] BYREF
  int __k; // [rsp+22Ch] [rbp-104h] BYREF
  std::string v43; // [rsp+230h] [rbp-100h] BYREF
  char v44; // [rsp+23Fh] [rbp-F1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v45; // [rsp+240h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v46; // [rsp+250h] [rbp-E0h] BYREF
  std::string v47; // [rsp+260h] [rbp-D0h] BYREF
  char v48; // [rsp+26Fh] [rbp-C1h] BYREF
  Position v49; // [rsp+270h] [rbp-C0h] BYREF
  TreasureMapCfg p_stu; // [rsp+280h] [rbp-B0h] BYREF
  TreasureMapEventCfg v51; // [rsp+2E0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+2FCh] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+300h] [rbp-30h]
  int32_t i; // [rsp+304h] [rbp-2Ch]
  int32_t nIndex; // [rsp+308h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+310h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+314h] [rbp-1Ch]
  int32_t i_0; // [rsp+318h] [rbp-18h]
  int32_t nIndex_0; // [rsp+31Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureMapBase.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TREASURE_MAP_CFG_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::map<int,int>::map(&stu.m_EventRate);
        /* /* std::vector<MapPos>::vector(&stu.m_MaxPosVector); */ */
        nIndex = 0;
        stu.m_ItemId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        RateString.assign(v2->pString);
        
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        MapPosString.assign(v3->pString);
        
        ++nIndex;
        if ( std::operator!=<char>(&RateString, &byte_8C33CF) && std::operator!=<char>(&RateString, "-1") )
        {
          
          delims = "|";
          Answer::StringUtility::split(&SplitStr, &RateString, &delims, 0);
          
          __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
            &iterBegin,
            &__i);
          while ( 1 )
          {
            __rhs._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
            if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &__rhs) )
              break;
            
            v40 = ":";
            v5 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
            Answer::StringUtility::split(&vstr, v5, &v40, 0);
            
            if ( std::vector<std::string>::size(&vstr) == 2 )
            {
              v6 = std::vector<std::string>::operator[](&vstr, 0);
              v7 = (const char *)std::string::c_str(v6);
              __k = atoi(v7);
              v8 = std::map<int,int>::operator[](&stu.m_EventRate, &__k);
              v9 = std::vector<std::string>::operator[](&vstr, 1u);
              v10 = (const char *)std::string::c_str(v9);
              *v8 = atoi(v10);
              LODWORD(v8) = stu.m_MaxProbability;
              v11 = std::vector<std::string>::operator[](&vstr, 1u);
              v12 = (const char *)std::string::c_str(v11);
              stu.m_MaxProbability = (_DWORD)v8 + atoi(v12);
            }
            std::vector<std::string>::~vector(&vstr);
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
          }
          std::vector<std::string>::~vector(&SplitStr);
        }
        if ( std::operator!=<char>(&MapPosString, &byte_8C33CF) && std::operator!=<char>(&MapPosString, "-1") )
        {
          
          v43 = "|";
          Answer::StringUtility::split(&SplitStr_0, &MapPosString, &v43, 0);
          
          v45._M_current = std::vector<std::string>::begin(&SplitStr_0)._M_current;
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
            &iterBegin_0,
            &v45);
          while ( 1 )
          {
            v46._M_current = std::vector<std::string>::end(&SplitStr_0)._M_current;
            if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin_0, &v46) )
              break;
            
            v47 = ":";
            v14 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin_0);
            Answer::StringUtility::split(&vstr_0, v14, &v47, 0);
            
            if ( std::vector<std::string>::size(&vstr_0) == 3 )
            {
              Position::Position(&v49, 0, 0);
              stuPos.m_MapId = 0;
              stuPos.m_Pos = v49;
              v15 = std::vector<std::string>::operator[](&vstr_0, 0);
              v16 = (const char *)std::string::c_str(v15);
              stuPos.m_MapId = atoi(v16);
              v17 = std::vector<std::string>::operator[](&vstr_0, 1u);
              v18 = (const char *)std::string::c_str(v17);
              stuPos.m_Pos.x = atoi(v18);
              v19 = std::vector<std::string>::operator[](&vstr_0, 2u);
              v20 = (const char *)std::string::c_str(v19);
              stuPos.m_Pos.y = atoi(v20);
              std::vector<MapPos>::push_back(&stu.m_MaxPosVector, &stuPos);
            }
            std::vector<std::string>::~vector(&vstr_0);
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin_0);
          }
          std::vector<std::string>::~vector(&SplitStr_0);
        }
        TreasureMapCfg::TreasureMapCfg(&p_stu, &stu);
        TreasureMapTabale::AddTreasureMapCfg(&this->m_TreasureMapTabale, &p_stu);
        /* /* TreasureMapCfg::~TreasureMapCfg(&p_stu); - auto cleanup */ - auto cleanup */
        /* /* TreasureMapCfg::~TreasureMapCfg(&stu); - auto cleanup */ - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureMapEvent.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_TREASURE_MAP_EVENT_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          memset(&stu_0, 0, 20);
          std::string::string(&stu_0.m_EventParam);
          nIndex_0 = 0;
          stu_0.m_EventId = readFile.Search_Posistion( i_0, 0)->iValue;
          stu_0.m_EventType = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          v21 = readFile.Search_Posistion( i_0, ++nIndex_0);
          std::string::operator=(&stu_0.m_EventParam, v21->pString);
          stu_0.m_GongGaoId = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          TreasureMapEventCfg::TreasureMapEventCfg(&v51, &stu_0);
          TreasureMapTabale::AddTreasureMapEventCfg(&this->m_TreasureMapTabale, &v51);
          /* /* TreasureMapEventCfg::~TreasureMapEventCfg(&v51); - auto cleanup */ - auto cleanup */
          /* /* TreasureMapEventCfg::~TreasureMapEventCfg(&stu_0); - auto cleanup */ - auto cleanup */
        }
      }
    }
  }
}

//#####################################
void CfgData::InitWishRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgWishReward stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+EAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+F0h] [rbp-20h]
  int32_t i; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+F8h] [rbp-18h]
  int32_t nId; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/WishReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WISH_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgWishReward::CfgWishReward(&stu);
        nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nTime = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        CfgWishRewardTable::Add(&this->m_cfgWishRewardTable, nId, &stu);
        /* /* CfgWishReward::~CfgWishReward(&stu); - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitWuHunItemTable()
{
  const CDBCFile::FIELD *v1; // rax
  WuHunItem *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-120h] BYREF
  WuHunItem stu; // [rsp+A0h] [rbp-90h] BYREF
  std::list<AddAttribute> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+F0h] [rbp-40h] BYREF
  char v7; // [rsp+FFh] [rbp-31h] BYREF
  int32_t v8[3]; // [rsp+100h] [rbp-30h] BYREF
  char v9; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WuHun.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_ITEM_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<AddAttribute>::list(&stu.lAttrList);
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nQuality = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nNeedQuality = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v6, "./ServerConfig/Tables/WuHun.txt", &v7);
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.nTalentId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nTalentLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 8;
        stu.overlay = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 3;
        stu.nDressLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        v2 = std::map<int,WuHunItem>::operator[](&this->m_WuHunItemMap, &stu.nId);
        WuHunItem::operator=(v2, &stu);
        /* /* WuHunItem::~WuHunItem(&stu); - auto cleanup */ - auto cleanup */
      }
    }
  }
}

//#####################################
WuHunItem *CfgData::GetWuHunItem(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,WuHunItem> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunItem> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,WuHunItem>::find(&this->m_WuHunItemMap, &nIda)._M_node;
  __x._M_node = std::map<int,WuHunItem>::end(&thisa->m_WuHunItemMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WuHunItem>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,WuHunItem>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitWuHunShopTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<CfgWuHunShop> *v2; // rax
  CfgWuHunShop *v3; // rax
  MemChrBag v4; // [rsp+0h] [rbp-130h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-108h]
  CDBCFile TabFile(0); // [rsp+30h] [rbp-100h] BYREF
  CfgWuHunShop stu; // [rsp+C0h] [rbp-70h] BYREF
  int32_t ShopId; // [rsp+FCh] [rbp-34h] BYREF
  std::string strItem; // [rsp+100h] [rbp-30h] BYREF
  char v10; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  thisa = this;
  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/MysterShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.Index = TabFile.Search_Posistion( i, 0)->iValue;
        ShopId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        CItemHelper::parseItemString(&v4, &strItem);
        stu.Item = v4;
        
        stu.Rate = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.Const = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<CfgWuHunShop>>::operator[](&thisa->m_CfgWuHunShopMap, &ShopId);
        std::list<CfgWuHunShop>::push_back(v2, &stu);
        v3 = std::map<int,CfgWuHunShop>::operator[](&thisa->m_CfgWuHunShopItemMap, &stu.Index);
        *v3 = stu;
      }
    }
  }
}

//#####################################
// local variable allocation has failed, the output may be wrong!
CfgWuHunShopList CfgData::GetWuHunShopItemList(int32_t ShopId)
{
  int32_t v2; // edx
  CfgWuHunShopList result; // rax
  std::pair<const int,std::list<CfgWuHunShop> > *v4; // rax
  int32_t ShopIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  CfgWuHunShopList list; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgWuHunShop> > > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgWuHunShop> > > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = *(CfgData **)&ShopId;
  ShopIda = v2;
  it._M_node = std::map<int,std::list<CfgWuHunShop>>::find(
                 (std::map<int,std::list<CfgWuHunShop>> *const)(*(_QWORD *)&ShopId + 10680LL),
                 &ShopIda)._M_node;
  __x._M_node = std::map<int,std::list<CfgWuHunShop>>::end(&thisa->m_CfgWuHunShopMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<CfgWuHunShop>>>::operator==(&it, &__x) )
  {
    std::list<CfgWuHunShop>::list(&list);
    std::list<CfgWuHunShop>::list((std::list<CfgWuHunShop> *const)this, &list);
    std::list<CfgWuHunShop>::~list(&list);
  }
  else
  {
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::list<CfgWuHunShop>>>::operator->(&it);
    std::list<CfgWuHunShop>::list((std::list<CfgWuHunShop> *const)this, &v4->second);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
CfgWuHunShop *CfgData::GetWuHunShopItem(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgWuHunShop> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgWuHunShop> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  it._M_node = std::map<int,CfgWuHunShop>::find(&this->m_CfgWuHunShopItemMap, &nIndexa)._M_node;
  __x._M_node = std::map<int,CfgWuHunShop>::end(&thisa->m_CfgWuHunShopItemMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgWuHunShop>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CfgWuHunShop>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitYellowLevelRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-150h] BYREF
  CfgTencentGift gift; // [rsp+A0h] [rbp-C0h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-80h] BYREF
  std::string strItems; // [rsp+100h] [rbp-60h] BYREF
  char v7; // [rsp+10Fh] [rbp-51h] BYREF
  MemChrBagVector v8; // [rsp+110h] [rbp-50h] BYREF
  std::string v9; // [rsp+130h] [rbp-30h] BYREF
  char v10; // [rsp+13Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+13Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+140h] [rbp-20h]
  int32_t i; // [rsp+144h] [rbp-1Ch]
  int32_t nIndex; // [rsp+148h] [rbp-18h]
  int32_t nId; // [rsp+14Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YellowLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&gift);
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v9.assign(v2->pString);
        CItemHelper::parseItemVectorString(&v8, &v9);
        std::vector<MemChrBag>::operator=(&gift.vVipRewards, &v8);
        std::vector<MemChrBag>::~vector(&v8);
        
        ++nIndex;
        CfgTencentTable::AddYellowLevelGift(&this->m_cfgTencentTable, nId, &gift);
        CfgTencentGift::~CfgTencentGift(&gift);
      }
    }
  }
}

//#####################################
void CfgData::InitTalentActiveTable()
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
        ZhanHunCfg stu = {};
        int32_t nLevel = TabFile.Search_Posistion(i, 0)->iValue;
        stu.nMoney = TabFile.Search_Posistion(i, 1)->iValue;
        stu.nSyb = TabFile.Search_Posistion(i, 2)->iValue;

        std::string strAttr = TabFile.Search_Posistion(i, 3)->pString;
        if (!strAttr.empty())
        {
            StringVector vAttrs = Answer::StringUtility::split(strAttr, "|");
            for (size_t j = 0; j < vAttrs.size(); ++j)
            {
                StringVector vPair = Answer::StringUtility::split(vAttrs[j], ":");
                if (vPair.size() >= 2)
                {
                    AddAttribute attr;
                    attr.m_nAddAttrType = (uint8_t)atoi(vPair[0].c_str());
                    attr.m_nAddAttrValue = atoi(vPair[1].c_str());
                    if (attr.m_nAddAttrType > 0 && attr.m_nAddAttrValue > 0)
                    {
                        stu.lAddAttrs.push_back(attr);
                    }
                }
            }
        }

        stu.nGongGaoId = TabFile.Search_Posistion(i, 7)->iValue;

        m_ZhanHunCfgMap[nLevel] = stu;
    }
}
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-F0h] BYREF
  CfgTalentActive stu; // [rsp+A0h] [rbp-60h] BYREF
  std::list<ItemData> strItems; // [rsp+C0h] [rbp-40h] BYREF
  bool bCombi[14]; // [rsp+D0h] [rbp-30h] BYREF
  char v6; // [rsp+DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/SkillActive.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_ACTIVE_TALENT_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalentActive::CfgTalentActive(&stu);
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v6);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        ++nIndex;
        CfgSkillTable::AddTalentActive(&this->m_cfgSkillTable, &stu);
        /* CfgTalentActive::~CfgTalentActive(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitTalentPageTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgTalentPage stu; // [rsp+A0h] [rbp-70h] BYREF
  std::list<int> __x; // [rsp+C0h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+D0h] [rbp-40h] BYREF
  char v6; // [rsp+DFh] [rbp-31h] BYREF
  std::string path; // [rsp+E0h] [rbp-30h] BYREF
  char v8; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/SkillTree.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_PAGE_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalentPage::CfgTalentPage(&stu);
        stu.job = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(size, "./ServerConfig/Tables/SkillTree.txt", &v6);
        
        v1 = readFile.Search_Posistion( i, nIndex);
        path.assign(v1->pString);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.talents, &__x);
        std::list<int>::~list(&__x);
        
        ++nIndex;
        CfgTalentTable::AddTalentPage(&this->m_cfgTalentTable, &stu);
        CfgTalentPage::~CfgTalentPage(&stu);
      }
    }
  }
}

//#####################################
void CfgData::fetchTask()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  const CDBCFile::FIELD *v6; // rax
  CfgTask *v7; // rax
  CfgTask task; // [rsp+10h] [rbp-2A0h] BYREF
  CDBCFile TabFile(0); // [rsp+130h] [rbp-180h] BYREF
  MemChrBagVector __x; // [rsp+1C0h] [rbp-F0h] BYREF
  std::string strItems; // [rsp+1E0h] [rbp-D0h] BYREF
  char v12; // [rsp+1EFh] [rbp-C1h] BYREF
  MemChrBagVector v13; // [rsp+1F0h] [rbp-C0h] BYREF
  std::string v14; // [rsp+210h] [rbp-A0h] BYREF
  char v15; // [rsp+21Fh] [rbp-91h] BYREF
  MemChrJobBagVector v16; // [rsp+220h] [rbp-90h] BYREF
  std::string v17; // [rsp+240h] [rbp-70h] BYREF
  char v18; // [rsp+24Fh] [rbp-61h] BYREF
  std::string strRequest; // [rsp+250h] [rbp-60h] BYREF
  char v20; // [rsp+25Fh] [rbp-51h] BYREF
  std::list<TaskDrop> v21; // [rsp+260h] [rbp-50h] BYREF
  _BYTE v22[15]; // [rsp+270h] [rbp-40h] BYREF
  char v23; // [rsp+27Fh] [rbp-31h] BYREF
  std::string path; // [rsp+280h] [rbp-30h] BYREF
  char v25; // [rsp+292h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+294h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+298h] [rbp-18h]
  int32_t i; // [rsp+29Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_task.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_task.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTask::CfgTask(&task);
        task.id = TabFile.Search_Posistion( i, 0)->iValue;
        v1 = TabFile.Search_Posistion( i, 1);
        snprintf(task.name, 0x1Eu, v1->pString);
        task.type = TabFile.Search_Posistion( i, 2)->iValue;
        task.group = TabFile.Search_Posistion( i, 3)->iValue;
        task.can_giveup = TabFile.Search_Posistion( i, 4)->iValue;
        task.pretask = TabFile.Search_Posistion( i, 5)->iValue;
        task.posttask = TabFile.Search_Posistion( i, 6)->iValue;
        task.main_order = TabFile.Search_Posistion( i, 7)->iValue;
        task.job = TabFile.Search_Posistion( i, 8)->iValue;
        task.level = TabFile.Search_Posistion( i, 9)->iValue;
        task.max_level = TabFile.Search_Posistion( i, 10)->iValue;
        task.kingdom = TabFile.Search_Posistion( i, 11)->iValue;
        task.start_npc = TabFile.Search_Posistion( i, 12)->iValue;
        task.end_npc = TabFile.Search_Posistion( i, 13)->iValue;
        task.dungeon = TabFile.Search_Posistion( i, 14)->iValue;
        
        v2 = TabFile.Search_Posistion( i, 15);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&task.items_receive, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        task.award_exp = TabFile.Search_Posistion( i, 16)->iValue;
        task.award_money = TabFile.Search_Posistion( i, 17)->iValue;
        task.gold = TabFile.Search_Posistion( i, 18)->iValue;
        task.dilong = TabFile.Search_Posistion( i, 19)->iValue;
        task.rongyu = TabFile.Search_Posistion( i, 20)->iValue;
        task.fuwen = TabFile.Search_Posistion( i, 21)->iValue;
        task.BossScore = TabFile.Search_Posistion( i, 22)->iValue;
        
        v3 = TabFile.Search_Posistion( i, 23);
        v14.assign(v3->pString);
        CItemHelper::parseItemVectorString(&v13, &v14);
        std::vector<MemChrBag>::operator=(&task.award_item, &v13);
        std::vector<MemChrBag>::~vector(&v13);
        
        v4 = TabFile.Search_Posistion( i, 24);
        v17.assign(v4->pString);
        CfgData::parseTaskItemJobString(&v16, this, task.id, &v17);
        std::vector<MemChrJobBag>::operator=(&task.award_optional, &v16);
        std::vector<MemChrJobBag>::~vector(&v16);
        
        task.condition = TabFile.Search_Posistion( i, 35)->iValue;
        
        v5 = TabFile.Search_Posistion( i, 36);
        strRequest.assign(v5->pString);
        task.request = CfgData::parseTaskCondition(this, task.id, task.condition, &strRequest);
        
        task.GongXian = TabFile.Search_Posistion( i, 50)->iValue;
        task.JunTuanZiJin = TabFile.Search_Posistion( i, 51)->iValue;
        task.Double = TabFile.Search_Posistion( i, 52)->iValue;
        task.acScore = TabFile.Search_Posistion( i, 53)->iValue;
        task.quickDoneCost = TabFile.Search_Posistion( i, 55)->iValue;
        task.quality = TabFile.Search_Posistion( i, 61)->iValue;
        task.ratio = TabFile.Search_Posistion( i, 62)->iValue;
        task.dust = TabFile.Search_Posistion( i, 63)->iValue;
        task.activity_score = TabFile.Search_Posistion( i, 65)->iValue;
        task.talent_point = TabFile.Search_Posistion( i, 67)->iValue;
        
        std::string::string(v22, "./ServerConfig/Tables/cfg_task.txt", &v23);
        
        v6 = TabFile.Search_Posistion( i, 68);
        path.assign(v6->pString);
        CfgData::parseTaskDrop(
          (CfgData *const)&v21,
          (int32_t)this,
          (const std::string *const)(unsigned int)task.id,
          &path);
        std::list<TaskDrop>::operator=(&task.drop_list, &v21);
        std::list<TaskDrop>::~list(&v21);
        
        task.DoubleGold = TabFile.Search_Posistion( i, 69)->iValue;
        task.BuffId = TabFile.Search_Posistion( i, 70)->iValue;
        v7 = std::map<int,CfgTask>::operator[](&this->m_tasks, &task.id);
        CfgTask::operator=(v7, &task);
        if ( task.type == 3 )
          CfgTaskCycleTable::AddTask(&this->m_cfgTaskCycleTable, task.id, task.level, task.max_level);
        if ( task.type == 37 )
          CfgFamilyTask::AddFamilyTask(&this->m_FamilyTaskTable, task.id, task.level, task.max_level);
        if ( task.type == 41 )
          CfgActivityTaskTable::AddTask(&this->m_cfgActivityTaskTable, task.id, task.level, task.max_level, task.ratio);
        CfgTask::~CfgTask(&task);
      }
    }
  }
}

//#####################################
void CfgData::fetchTrap()
{
  const CDBCFile::FIELD *v1; // rax
  CfgTrap *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-D0h] BYREF
  CfgTrap trap; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C4h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+C8h] [rbp-18h]
  int32_t i; // [rsp+CCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_trap.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open cfg_trap.txt failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTrap::CfgTrap(&trap);
        trap.id = TabFile.Search_Posistion( i, 0)->iValue;
        trap.cd = TabFile.Search_Posistion( i, 2)->iValue;
        trap.delay = TabFile.Search_Posistion( i, 3)->iValue;
        trap.event_type = TabFile.Search_Posistion( i, 4)->iValue;
        v1 = TabFile.Search_Posistion( i, 6);
        std::string::operator=(&trap.effect, v1->pString);
        trap.item_cost = TabFile.Search_Posistion( i, 7)->iValue;
        trap.life = TabFile.Search_Posistion( i, 12)->iValue;
        v2 = std::map<int,CfgTrap>::operator[](&this->m_traps, &trap.id);
        CfgTrap::operator=(v2, &trap);
        CfgTrap::~CfgTrap(&trap);
      }
    }
  }
}

//#####################################
std::vector<Position> *CfgData::paresPosition(
        std::vector<Position> *const std::string *const strPos)
{
  std::string *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  Position stu; // [rsp+10h] [rbp-B0h] BYREF
  StringVector Pos; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-80h] BYREF
  StringVector PosString; // [rsp+50h] [rbp-70h] BYREF
  std::string delims; // [rsp+70h] [rbp-50h] BYREF
  char v15; // [rsp+7Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-40h] BYREF
  std::string v17; // [rsp+90h] [rbp-30h] BYREF
  _BYTE v18[33]; // [rsp+9Fh] [rbp-21h] BYREF

  std::vector<Position>::vector(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strPos) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&PosString, strPos, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&PosString)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&PosString)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v17.assign(":", v18);
      v3 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&Pos, v3, &v17, 0);
      
      if ( std::vector<std::string>::size(&Pos) == 2 )
      {
        Position::Position(&stu, 0, 0);
        v4 = std::vector<std::string>::operator[](&Pos, 0);
        v5 = (const char *)std::string::c_str(v4);
        stu.x = atoi(v5);
        v6 = std::vector<std::string>::operator[](&Pos, 1u);
        v7 = (const char *)std::string::c_str(v6);
        stu.y = atoi(v7);
        std::vector<Position>::push_back(retstr, &stu);
      }
      std::vector<std::string>::~vector(&Pos);
    }
    std::vector<std::string>::~vector(&PosString);
  }
  return retstr;
}

//#####################################
void CfgData::parseItemStringWithJob(int32_t id,
        const std::string *const strItems,
        MemChrBagVector *const items,
        MemChrJobBagVector *const jobItems)
{
  std::string *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  const char *v20; // rax
  MemChrBag itemData; // [rsp+30h] [rbp-D0h] BYREF
  MemChrJobBag job; // [rsp+50h] [rbp-B0h] BYREF
  StringVector item; // [rsp+70h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+90h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+A0h] [rbp-60h] BYREF
  std::string delims; // [rsp+C0h] [rbp-40h] BYREF
  char v30; // [rsp+CFh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+D0h] [rbp-30h] BYREF
  std::string v32; // [rsp+E0h] [rbp-20h] BYREF
  _BYTE v33[17]; // [rsp+EFh] [rbp-11h] BYREF

  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v32.assign(":", v33);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v32, 0);
      
      if ( std::vector<std::string>::size(&item) == 3 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.itemId = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.itemClass = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.itemCount = atoi(v11);
        std::vector<MemChrBag>::push_back(items, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 4 )
      {
        memset(&job, 0, sizeof(job));
        v12 = std::vector<std::string>::operator[](&item, 0);
        v13 = (const char *)std::string::c_str(v12);
        job.id = atoi(v13);
        v14 = std::vector<std::string>::operator[](&item, 1u);
        v15 = (const char *)std::string::c_str(v14);
        job.type = atoi(v15);
        v16 = std::vector<std::string>::operator[](&item, 2u);
        v17 = (const char *)std::string::c_str(v16);
        job.count = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 3u);
        v19 = (const char *)std::string::c_str(v18);
        job.job = atoi(v19);
        std::vector<MemChrJobBag>::push_back(jobItems, &job);
      }
      else
      {
        v20 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseItemString wrong data with id = %d, string = %s\n",
          id,
          v20);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
}

//#####################################
GongGaoList CfgData::parseGongGaoString(int32_t id, const std::string *const strItems)
{
  std::string *v3; // rcx
  GongGaoList result; // rax
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *strItemsa; // [rsp+8h] [rbp-C8h]
  CfgGongGao stu; // [rsp+20h] [rbp-B0h] BYREF
  StringVector item; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v16; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v18; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v19[33]; // [rsp+AFh] [rbp-21h] BYREF

  strItemsa = v3;
  std::list<CfgGongGao>::list((std::list<CfgGongGao> *const)this);
  if ( (unsigned __int8)std::string::empty(strItemsa) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItemsa, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v18.assign(":", v19);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v18, 0);
      
      if ( std::vector<std::string>::size(&item) == 2 )
      {
        stu = 0;
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        stu.Job = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        stu.GongGaoId = atoi(v9);
        std::list<CfgGongGao>::push_back((std::list<CfgGongGao> *const)this, &stu);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
MemChrEquipBagVector *CfgData::parseEquipItemString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  std::string *v20; // rax
  const char *v21; // rax
  std::string *v22; // rax
  const char *v23; // rax
  std::string *v24; // rax
  const char *v25; // rax
  std::string *v26; // rax
  const char *v27; // rax
  std::string *v28; // rax
  const char *v29; // rax
  std::string *v30; // rax
  const char *v31; // rax
  std::string *v32; // rax
  const char *v33; // rax
  std::string *v34; // rax
  const char *v35; // rax
  std::string *v36; // rax
  const char *v37; // rax
  std::string *v38; // rax
  const char *v39; // rax
  std::string *v40; // rax
  const char *v41; // rax
  const char *v42; // rax
  CfgEquipItem itemData_1; // [rsp+20h] [rbp-100h] BYREF
  CfgEquipItem itemData_0; // [rsp+40h] [rbp-E0h] BYREF
  CfgEquipItem itemData; // [rsp+60h] [rbp-C0h] BYREF
  StringVector item; // [rsp+80h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+A0h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+B0h] [rbp-70h] BYREF
  std::string delims; // [rsp+D0h] [rbp-50h] BYREF
  char v53; // [rsp+DFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+E0h] [rbp-40h] BYREF
  std::string v55; // [rsp+F0h] [rbp-30h] BYREF
  _BYTE v56[33]; // [rsp+FFh] [rbp-21h] BYREF

  std::vector<CfgEquipItem>::vector(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1
    && std::string::size((std::string *)strItems) > 4u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v55.assign(":", v56);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v55, 0);
      
      if ( std::vector<std::string>::size(&item) == 5 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.id = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.type = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.count = atoi(v11);
        v12 = std::vector<std::string>::operator[](&item, 3u);
        v13 = (const char *)std::string::c_str(v12);
        itemData.bind = atoi(v13);
        v14 = std::vector<std::string>::operator[](&item, 4u);
        v15 = (const char *)std::string::c_str(v14);
        itemData.job = atoi(v15);
        std::vector<CfgEquipItem>::push_back(retstr, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 6 )
      {
        memset(&itemData_0, 0, sizeof(itemData_0));
        v16 = std::vector<std::string>::operator[](&item, 0);
        v17 = (const char *)std::string::c_str(v16);
        itemData_0.id = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 1u);
        v19 = (const char *)std::string::c_str(v18);
        itemData_0.type = atoi(v19);
        v20 = std::vector<std::string>::operator[](&item, 2u);
        v21 = (const char *)std::string::c_str(v20);
        itemData_0.count = atoi(v21);
        v22 = std::vector<std::string>::operator[](&item, 3u);
        v23 = (const char *)std::string::c_str(v22);
        itemData_0.bind = atoi(v23);
        v24 = std::vector<std::string>::operator[](&item, 4u);
        v25 = (const char *)std::string::c_str(v24);
        itemData_0.job = atoi(v25);
        v26 = std::vector<std::string>::operator[](&item, 5u);
        v27 = (const char *)std::string::c_str(v26);
        itemData_0.star = atoi(v27);
        std::vector<CfgEquipItem>::push_back(retstr, &itemData_0);
      }
      else if ( std::vector<std::string>::size(&item) <= 6 )
      {
        v42 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n",
          id,
          v42);
      }
      else
      {
        memset(&itemData_1, 0, sizeof(itemData_1));
        v28 = std::vector<std::string>::operator[](&item, 0);
        v29 = (const char *)std::string::c_str(v28);
        itemData_1.id = atoi(v29);
        v30 = std::vector<std::string>::operator[](&item, 1u);
        v31 = (const char *)std::string::c_str(v30);
        itemData_1.type = atoi(v31);
        v32 = std::vector<std::string>::operator[](&item, 2u);
        v33 = (const char *)std::string::c_str(v32);
        itemData_1.count = atoi(v33);
        v34 = std::vector<std::string>::operator[](&item, 3u);
        v35 = (const char *)std::string::c_str(v34);
        itemData_1.bind = atoi(v35);
        v36 = std::vector<std::string>::operator[](&item, 4u);
        v37 = (const char *)std::string::c_str(v36);
        itemData_1.job = atoi(v37);
        v38 = std::vector<std::string>::operator[](&item, 5u);
        v39 = (const char *)std::string::c_str(v38);
        itemData_1.star = atoi(v39);
        v40 = std::vector<std::string>::operator[](&item, 6u);
        v41 = (const char *)std::string::c_str(v40);
        itemData_1.weight = atoi(v41);
        std::vector<CfgEquipItem>::push_back(retstr, &itemData_1);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  return retstr;
}

//#####################################
MemChrJobBagVector *CfgData::parseTaskItemJobString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  std::string *v20; // rax
  const char *v21; // rax
  std::string *v22; // rax
  const char *v23; // rax
  std::string *v24; // rax
  const char *v25; // rax
  std::string *v26; // rax
  const char *v27; // rax
  std::string *v28; // rax
  const char *v29; // rax
  std::string *v30; // rax
  const char *v31; // rax
  std::string *v32; // rax
  const char *v33; // rax
  std::string *v34; // rax
  const char *v35; // rax
  const char *v36; // rax
  MemChrJobBag itemData_1; // [rsp+20h] [rbp-100h] BYREF
  MemChrJobBag itemData_0; // [rsp+40h] [rbp-E0h] BYREF
  MemChrJobBag itemData; // [rsp+60h] [rbp-C0h] BYREF
  StringVector item; // [rsp+80h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+A0h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+B0h] [rbp-70h] BYREF
  std::string delims; // [rsp+D0h] [rbp-50h] BYREF
  char v47; // [rsp+DFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+E0h] [rbp-40h] BYREF
  std::string v49; // [rsp+F0h] [rbp-30h] BYREF
  _BYTE v50[33]; // [rsp+FFh] [rbp-21h] BYREF

  std::vector<MemChrJobBag>::vector(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1
    && std::string::size((std::string *)strItems) > 4u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v49.assign(":", v50);
      v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v5, &v49, 0);
      
      if ( std::vector<std::string>::size(&item) == 4 )
      {
        memset(&itemData, 0, sizeof(itemData));
        v6 = std::vector<std::string>::operator[](&item, 0);
        v7 = (const char *)std::string::c_str(v6);
        itemData.id = atoi(v7);
        v8 = std::vector<std::string>::operator[](&item, 1u);
        v9 = (const char *)std::string::c_str(v8);
        itemData.type = atoi(v9);
        v10 = std::vector<std::string>::operator[](&item, 2u);
        v11 = (const char *)std::string::c_str(v10);
        itemData.count = atoi(v11);
        v12 = std::vector<std::string>::operator[](&item, 3u);
        v13 = (const char *)std::string::c_str(v12);
        itemData.job = atoi(v13);
        std::vector<MemChrJobBag>::push_back(retstr, &itemData);
      }
      else if ( std::vector<std::string>::size(&item) == 5 )
      {
        memset(&itemData_0, 0, sizeof(itemData_0));
        v14 = std::vector<std::string>::operator[](&item, 0);
        v15 = (const char *)std::string::c_str(v14);
        itemData_0.id = atoi(v15);
        v16 = std::vector<std::string>::operator[](&item, 1u);
        v17 = (const char *)std::string::c_str(v16);
        itemData_0.type = atoi(v17);
        v18 = std::vector<std::string>::operator[](&item, 2u);
        v19 = (const char *)std::string::c_str(v18);
        itemData_0.count = atoi(v19);
        v20 = std::vector<std::string>::operator[](&item, 3u);
        v21 = (const char *)std::string::c_str(v20);
        itemData_0.bind = atoi(v21);
        v22 = std::vector<std::string>::operator[](&item, 4u);
        v23 = (const char *)std::string::c_str(v22);
        itemData_0.job = atoi(v23);
        std::vector<MemChrJobBag>::push_back(retstr, &itemData_0);
      }
      else if ( std::vector<std::string>::size(&item) == 6 )
      {
        memset(&itemData_1, 0, sizeof(itemData_1));
        v24 = std::vector<std::string>::operator[](&item, 0);
        v25 = (const char *)std::string::c_str(v24);
        itemData_1.id = atoi(v25);
        v26 = std::vector<std::string>::operator[](&item, 1u);
        v27 = (const char *)std::string::c_str(v26);
        itemData_1.type = atoi(v27);
        v28 = std::vector<std::string>::operator[](&item, 2u);
        v29 = (const char *)std::string::c_str(v28);
        itemData_1.count = atoi(v29);
        v30 = std::vector<std::string>::operator[](&item, 3u);
        v31 = (const char *)std::string::c_str(v30);
        itemData_1.bind = atoi(v31);
        v32 = std::vector<std::string>::operator[](&item, 4u);
        v33 = (const char *)std::string::c_str(v32);
        itemData_1.job = atoi(v33);
        v34 = std::vector<std::string>::operator[](&item, 5u);
        v35 = (const char *)std::string::c_str(v34);
        itemData_1.time = atoi(v35);
        std::vector<MemChrJobBag>::push_back(retstr, &itemData_1);
      }
      else
      {
        v36 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n",
          id,
          v36);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  return retstr;
}

//#####################################
void CfgData::parseMonsterSkill(int32_t id,
        MonsterSkill (*const vSkill)[10],
        const std::string *const strSkill)
{
  int32_t v5; // eax
  std::string *v6; // rbx
  int32_t v7; // r12d
  std::string *v8; // rax
  const char *v9; // rax
  int32_t v10; // r12d
  std::string *v11; // rax
  const char *v12; // rax
  int32_t v13; // r12d
  std::string *v14; // rax
  const char *v15; // rax
  const char *v16; // rax
  StringVector skill; // [rsp+20h] [rbp-80h] BYREF
  StringVector skills; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v22; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v23; // [rsp+70h] [rbp-30h] BYREF
  char v24; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty((std::string *)strSkill) != 1
    && std::string::size((std::string *)strSkill) > 3u )
  {
    
    delims = "|";
    Answer::StringUtility::split(&skills, strSkill, &delims, 0);
    
    if ( std::vector<std::string>::size(&skills) > 9 )
      v5 = 10;
    else
      v5 = std::vector<std::string>::size(&skills);
    isize = v5;
    for ( i = 0; i < isize; ++i )
    {
      
      v23 = ":";
      v6 = std::vector<std::string>::operator[](&skills, i);
      Answer::StringUtility::split(&skill, v6, &v23, 0);
      
      if ( std::vector<std::string>::size(&skill) == 3 )
      {
        v7 = i;
        v8 = std::vector<std::string>::operator[](&skill, 0);
        v9 = (const char *)std::string::c_str(v8);
        (*vSkill)[v7].maxHp = atoi(v9);
        v10 = i;
        v11 = std::vector<std::string>::operator[](&skill, 1u);
        v12 = (const char *)std::string::c_str(v11);
        (*vSkill)[v10].minHp = atoi(v12);
        v13 = i;
        v14 = std::vector<std::string>::operator[](&skill, 2u);
        v15 = (const char *)std::string::c_str(v14);
        (*vSkill)[v13].skillid = atoi(v15);
      }
      else
      {
        v16 = (const char *)std::string::c_str((std::string *)strSkill);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseMonsterSkill wrong data with id = %d, string = %s\n",
          id,
          v16);
      }
      std::vector<std::string>::~vector(&skill);
    }
    std::vector<std::string>::~vector(&skills);
  }
}

//#####################################
MemJobItemTable *CfgData::parseGambleEquip(int32_t id,
        const std::string *const strItems)
{
  std::string *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  MemJobItem *v9; // rax
  const char *v10; // rax
  MemJobItem itemData; // [rsp+20h] [rbp-B0h] BYREF
  StringVector item; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector items_receive; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v19; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  std::string v21; // [rsp+A0h] [rbp-30h] BYREF
  _BYTE v22[33]; // [rsp+AFh] [rbp-21h] BYREF

  std::map<int,MemJobItem>::map(retstr);
  if ( (unsigned __int8)std::string::empty((std::string *)strItems) != 1 )
  {
    
    delims = "|";
    Answer::StringUtility::split(&items_receive, strItems, &delims, 0);
    
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      
      v21.assign(":", v22);
      v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&item, v4, &v21, 0);
      
      if ( std::vector<std::string>::size(&item) == 2 )
      {
        itemData = 0;
        v5 = std::vector<std::string>::operator[](&item, 0);
        v6 = (const char *)std::string::c_str(v5);
        itemData.job = atoi(v6);
        v7 = std::vector<std::string>::operator[](&item, 1u);
        v8 = (const char *)std::string::c_str(v7);
        itemData.item = atoi(v8);
        v9 = std::map<int,MemJobItem>::operator[](retstr, (const int *const)&itemData);
        *v9 = itemData;
      }
      else
      {
        v10 = (const char *)std::string::c_str((std::string *)strItems);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseGambleEquip wrong data with id = %d, string = %s\n",
          id,
          v10);
      }
      std::vector<std::string>::~vector(&item);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  return retstr;
}

//#####################################
TaskRequest CfgData::parseTaskCondition(int32_t id,
        int32_t condition,
        const std::string *const strRequest)
{
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  const char *v16; // rax
  StringVector requests; // [rsp+30h] [rbp-60h] BYREF
  TaskRequest request; // [rsp+50h] [rbp-40h]
  std::string delims; // [rsp+60h] [rbp-30h] BYREF
  char v21; // [rsp+6Fh] [rbp-21h] BYREF
  TaskRequest v22; // [rsp+70h] [rbp-20h]
  int32_t nSize; // [rsp+7Ch] [rbp-14h]

  *(_QWORD *)&request.param1 = 0;
  request.param3 = 0;
  
  delims = ":";
  Answer::StringUtility::split(&requests, strRequest, &delims, 0);
  
  nSize = std::vector<std::string>::size(&requests);
  switch ( nSize )
  {
    case 3:
      v4 = std::vector<std::string>::operator[](&requests, 0);
      v5 = (const char *)std::string::c_str(v4);
      request.param1 = atoi(v5);
      v6 = std::vector<std::string>::operator[](&requests, 1u);
      v7 = (const char *)std::string::c_str(v6);
      request.param2 = atoi(v7);
      v8 = std::vector<std::string>::operator[](&requests, 2u);
      v9 = (const char *)std::string::c_str(v8);
      request.param3 = atoi(v9);
      break;
    case 2:
      v10 = std::vector<std::string>::operator[](&requests, 0);
      v11 = (const char *)std::string::c_str(v10);
      request.param1 = atoi(v11);
      v12 = std::vector<std::string>::operator[](&requests, 1u);
      v13 = (const char *)std::string::c_str(v12);
      request.param2 = atoi(v13);
      break;
    case 1:
      v14 = std::vector<std::string>::operator[](&requests, 0);
      v15 = (const char *)std::string::c_str(v14);
      request.param1 = atoi(v15);
      break;
    default:
      v16 = (const char *)std::string::c_str((std::string *)strRequest);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CfgData::parseTaskCondition wrong data with id = %d, string = %s\n",
        id,
        v16);
      break;
  }
  v22 = request;
  std::vector<std::string>::~vector(&requests);
  return v22;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
TaskDropList CfgData::parseTaskDrop(int32_t id,
        const std::string *const str,
        const std::string *const path)
{
  TaskDropList result; // rax
  std::string *v6; // rax
  const std::string *v7; // rax
  unsigned int64_t v8; // r12
  const std::string *v9; // rax
  const char *v10; // rax
  unsigned int ida; // [rsp+14h] [rbp-ECh]
  TaskDrop stu; // [rsp+20h] [rbp-E0h] BYREF
  std::string strParam; // [rsp+40h] [rbp-C0h] BYREF
  std::string strCount; // [rsp+50h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+60h] [rbp-A0h] BYREF
  StringVector vDrop; // [rsp+70h] [rbp-90h] BYREF
  std::string delims; // [rsp+90h] [rbp-70h] BYREF
  char v19; // [rsp+9Fh] [rbp-61h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+A0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+B0h] [rbp-50h] BYREF
  std::list<Param2> __x; // [rsp+C0h] [rbp-40h] BYREF
  int e; // [rsp+DCh] [rbp-24h]

  ida = (unsigned int)str;
  std::list<TaskDrop>::list((std::list<TaskDrop> *const)this);
  if ( !(unsigned __int8)std::string::empty((std::string *)path) && !std::operator==<char>(path, "-1") )
  {
    
    delims = ",";
    Answer::StringUtility::split(&vDrop, path, &delims, 0);
    
    __i._M_current = std::vector<std::string>::begin(&vDrop)._M_current;
    __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
      &iter,
      &__i);
    while ( 1 )
    {
      __rhs._M_current = std::vector<std::string>::end(&vDrop)._M_current;
      if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      v6 = (std::string *)__gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
      e = std::string::find_first_of(v6, 124, 0);
      v7 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
      std::string::substr(&strCount, (unsigned int64_t)v7, 0);
      v8 = e + 1;
      v9 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator->(&iter);
      std::string::substr(&strParam, (unsigned int64_t)v9, v8);
      memset(&stu, 0, sizeof(stu));
      std::list<Param2>::list(&stu.lstJobGroup);
      v10 = (const char *)std::string::c_str(&strCount);
      stu.nCount = atoi(v10);
      CfgData::paraseParam2List(
        (CfgData *const)&__x,
        *(const std::string *const *)&id,
        (int32_t)&strParam,
        (const std::string *const)ida);
      std::list<Param2>::operator=(&stu.lstJobGroup, &__x);
      std::list<Param2>::~list(&__x);
      std::list<TaskDrop>::push_back((std::list<TaskDrop> *const)this, &stu);
      TaskDrop::~TaskDrop(&stu);
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
    }
    std::vector<std::string>::~vector(&vDrop);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
int32_t CfgData::getServerStartTime(SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return this->m_heFuTime;
  else
    return this->m_kaiFuTime;
}

//#####################################
int32_t CfgData::getServerStartDayZeroTime(SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return Answer::DayTime::dayzero(this->m_heFuTime);
  else
    return Answer::DayTime::dayzero(this->m_kaiFuTime);
}

//#####################################
int32_t CfgData::getServerDiffDay(SERVER_TYPE nType)
{
  if ( nType == SERVER_TYPE::SVT_UNITE )
    return Answer::DayTime::daydiff(this->m_heFuTime);
  else
    return Answer::DayTime::daydiff(this->m_kaiFuTime);
}

//#####################################
void CfgData::fetchServerConfig(int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1060h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-30h] BYREF

  if ( line != 9 )
  {
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `sys_server_start`");
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    v3 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      this->m_heFuTime = Answer::MySqlQuery::getIntValue(&result, "he_fu_time", 0);
      this->m_kaiFuTime = Answer::MySqlQuery::getIntValue(&result, "kai_fu_time", 0);
      this->m_serverType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}

//#####################################
void CfgData::updateServerStartTime(int32_t kaiFuTime)
{
  COpenBeta *v2; // rax

  if ( !CfgData::getServerType(this) )
  {
    this->m_kaiFuTime = kaiFuTime;
    v2 = Answer::Singleton<COpenBeta>::instance();
    COpenBeta::updateStartTime(v2);
  }
}

//#####################################
void CfgData::sendNewItems(const CfgItemTable *const items)
{
  GameService *v2; // rax
  int32_t v3; // eax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-10h]
  CfgItem *pCfgItem; // [rsp+38h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2752u);
  if ( packet )
  {
    v3 = std::map<int,CfgItem *>::size(items);
    Answer::NetPacket::writeInt32(packet, v3);
    for ( it._M_node = std::map<int,CfgItem *>::begin(items)._M_node;
          std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator++(&it) )
    {
      __x._M_node = std::map<int,CfgItem *>::end(items)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator!=(&it, &__x) )
        break;
      pCfgItem = std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it)->second;
      if ( pCfgItem )
      {
        Answer::NetPacket::writeInt32(packet, pCfgItem->id);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->name);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->desc);
        Answer::NetPacket::writeInt32(packet, pCfgItem->type);
        Answer::NetPacket::writeInt32(packet, pCfgItem->level);
        Answer::NetPacket::writeInt32(packet, pCfgItem->job);
        Answer::NetPacket::writeInt32(packet, pCfgItem->in_value);
        Answer::NetPacket::writeInt32(packet, pCfgItem->out_value);
        Answer::NetPacket::writeInt32(packet, pCfgItem->bind);
        Answer::NetPacket::writeInt32(packet, pCfgItem->combine);
        Answer::NetPacket::writeInt32(packet, pCfgItem->quality);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->url);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->drop_url);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->effect);
        Answer::NetPacket::writeUTF8(packet, &pCfgItem->use_method);
        Answer::NetPacket::writeInt32(packet, pCfgItem->group_id);
        Answer::NetPacket::writeInt32(packet, pCfgItem->cd_group);
        Answer::NetPacket::writeInt32(packet, pCfgItem->overlay);
        Answer::NetPacket::writeInt32(packet, pCfgItem->can_sell);
        Answer::NetPacket::writeInt32(packet, pCfgItem->valid_time);
      }
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v5, packet);
  }
}

//#####################################
void CfgData::InitTalentTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-150h] BYREF
  CfgTalent stu; // [rsp+A0h] [rbp-C0h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-60h] BYREF
  char v7; // [rsp+10Fh] [rbp-51h] BYREF
  std::list<int> __x; // [rsp+110h] [rbp-50h] BYREF
  int32_t size[3]; // [rsp+120h] [rbp-40h] BYREF
  char v10; // [rsp+12Fh] [rbp-31h] BYREF
  std::string path; // [rsp+130h] [rbp-30h] BYREF
  char v12; // [rsp+13Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+140h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+144h] [rbp-1Ch]
  int32_t i; // [rsp+148h] [rbp-18h]
  int32_t nIndex; // [rsp+14Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/SkillTalent.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TALENT_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTalent::CfgTalent(&stu);
        stu.id = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.Level = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.skillid = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.maxLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Playerlevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        ++nIndex;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v7);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.costItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        ++nIndex;
        
        std::string::string(size, "./ServerConfig/Tables/SkillTalent.txt", &v10);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        path.assign(v2->pString);
        CfgData::paraseInt32List((CfgData *const)&__x, (const std::string *const)this, &path, (int32_t)size);
        std::list<int>::operator=(&stu.powerSkills, &__x);
        std::list<int>::~list(&__x);
        
        ++nIndex;
        ++nIndex;
        stu.battle = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.Point = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgTalentTable::AddTalent(&this->m_cfgTalentTable, &stu);
        /* CfgTalent::~CfgTalent(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitTaskCycleRewardTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  TaskCycleReward stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TaskCycleReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TASK_CYCLE_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 1;
        memset(&stu, 0, sizeof(stu));
        stu.nId = readFile.Search_Posistion( i, 1)->iValue;
        stu.nClass = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nCount = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nBind = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgTaskCycleTable::AddTaskReward(&this->m_cfgTaskCycleTable, &stu);
      }
    }
  }
}

//#####################################
QuestionsVector *CfgData::GetAllQuestions(int8_t nType)
{
  std::vector<CfgQuestions> *v3; // rax
  int __k[5]; // [rsp+1Ch] [rbp-14h] BYREF

  __k[0] = nType;
  v3 = std::map<int,std::vector<CfgQuestions>>::operator[](&this->m_mQuestions, __k);
  std::vector<CfgQuestions>::vector(retstr, v3);
  return retstr;
}

//#####################################
void CfgData::InitTencentSevenDayLoginTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgTencentSevenDayLogin stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+EEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+F0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+F4h] [rbp-1Ch]
  int32_t i; // [rsp+F8h] [rbp-18h]
  int32_t nIndex; // [rsp+FCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/TencentSevenDayLogin.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TENCENT_SEVEN_DAY_LOGIN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentSevenDayLogin::CfgTencentSevenDayLogin(&stu);
        stu.nDays = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        CfgTencentTable::AddSevenDayLogin(&this->m_cfgTencentTable, &stu);
        /* CfgTencentSevenDayLogin::~CfgTencentSevenDayLogin(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitTianLingTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  TianLingCfg *v3; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-130h] BYREF
  TianLingCfg stu; // [rsp+A0h] [rbp-A0h] BYREF
  std::list<ItemData> strItems; // [rsp+D0h] [rbp-70h] BYREF
  bool bCombi[15]; // [rsp+E0h] [rbp-60h] BYREF
  char v8; // [rsp+EFh] [rbp-51h] BYREF
  std::list<AddAttribute> __x; // [rsp+F0h] [rbp-50h] BYREF
  _BYTE v10[15]; // [rsp+100h] [rbp-40h] BYREF
  char v11; // [rsp+10Fh] [rbp-31h] BYREF
  int32_t v12[3]; // [rsp+110h] [rbp-30h] BYREF
  char v13; // [rsp+11Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+120h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+124h] [rbp-1Ch]
  int32_t i; // [rsp+128h] [rbp-18h]
  int32_t nIndex; // [rsp+12Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TianLing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileAttrib);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        TianLingCfg::TianLingCfg(&stu);
        stu.Level = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.CostMoney = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v8);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.CostItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        ++nIndex;
        
        std::string::string(v10, "./ServerConfig/Tables/TianLing.txt", &v11);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v12, v2->pString, &v13);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v12,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.AttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 4;
        stu.CostCoin = readFile.Search_Posistion( i, nIndex++)->iValue;
        v3 = std::map<int,TianLingCfg>::operator[](&this->m_TianLingCfgTable, &stu.Level);
        TianLingCfg::operator=(v3, &stu);
        /* TianLingCfg::~TianLingCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
TianLingCfg *CfgData::GetTianLingCfg(int32_t TianLingLevel)
{
  int32_t TianLingLevela; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,TianLingCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,TianLingCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  TianLingLevela = TianLingLevel;
  it._M_node = std::map<int,TianLingCfg>::find(&this->m_TianLingCfgTable, &TianLingLevela)._M_node;
  __x._M_node = std::map<int,TianLingCfg>::end(&thisa->m_TianLingCfgTable)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,TianLingCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,TianLingCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitTitleTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-1F0h] BYREF
  CfgTitle title; // [rsp+A0h] [rbp-160h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+100h] [rbp-100h] BYREF
  StringVector strParams; // [rsp+110h] [rbp-F0h] BYREF
  std::string dressattr; // [rsp+130h] [rbp-D0h] BYREF
  std::string getttr; // [rsp+140h] [rbp-C0h] BYREF
  std::string params; // [rsp+150h] [rbp-B0h] BYREF
  char v14; // [rsp+15Dh] [rbp-A3h] BYREF
  char v15; // [rsp+15Eh] [rbp-A2h] BYREF
  char v16; // [rsp+15Fh] [rbp-A1h] BYREF
  std::string delims; // [rsp+160h] [rbp-A0h] BYREF
  char v18; // [rsp+16Fh] [rbp-91h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+170h] [rbp-90h] BYREF
  int __x; // [rsp+17Ch] [rbp-84h] BYREF
  AttrAddonVector v21; // [rsp+180h] [rbp-80h] BYREF
  std::string path; // [rsp+1A0h] [rbp-60h] BYREF
  char v23; // [rsp+1AFh] [rbp-51h] BYREF
  AttrAddonVector v24; // [rsp+1B0h] [rbp-50h] BYREF
  std::string v25; // [rsp+1D0h] [rbp-30h] BYREF
  char v26; // [rsp+1DEh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+1E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1E4h] [rbp-1Ch]
  int32_t i; // [rsp+1E8h] [rbp-18h]
  int32_t nIndex; // [rsp+1ECh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Title.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TITLE_TABLE failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        CfgTitle::CfgTitle(&title);
        nIndex = 0;
        title.nId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        title.nType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        params.assign(v1->pString);
        
        v2 = readFile.Search_Posistion( i, ++nIndex);
        std::string::operator=(&title.sPlatform, v2->pString);
        title.nJob = readFile.Search_Posistion( i, ++nIndex)->iValue;
        title.nSex = readFile.Search_Posistion( i, ++nIndex)->iValue;
        title.nSpecial = readFile.Search_Posistion( i, ++nIndex)->iValue;
        title.nPriority = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        getttr.assign(v3->pString);
        
        ++nIndex;
        
        v4 = readFile.Search_Posistion( i, nIndex);
        dressattr.assign(v4->pString);
        
        ++nIndex;
        
        delims = ":";
        Answer::StringUtility::split(&strParams, &params, &delims, 0);
        
        for ( it._M_current = std::vector<std::string>::begin(&strParams)._M_current;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strParams)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v5 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v6 = (const char *)std::string::c_str(v5);
          __x = atoi(v6);
          std::vector<int>::push_back(&title.vParams, &__x);
        }
        
        path = "./ServerConfig/Tables/Title.txt";
        paraseAttrAddon(v21, getttr, path);
        std::vector<AttrAddon>::operator=(&title.vGetAttr, &v21);
        std::vector<AttrAddon>::~vector(&v21);
        
        v25 = "./ServerConfig/Tables/Title.txt";
        paraseAttrAddon(v24, dressattr, v25);
        std::vector<AttrAddon>::operator=(&title.vDressAttr, &v24);
        std::vector<AttrAddon>::~vector(&v24);
        
        CfgTitleTable::Add(&this->m_cfgTitleTable, &title);
        std::vector<std::string>::~vector(&strParams);
        /* CfgTitle::~CfgTitle(&title); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitTongTianChiRanTable()
{
  int *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-C0h] BYREF
  int32_t nId; // [rsp+A4h] [rbp-2Ch] BYREF
  int32_t iBaseTableCount; // [rsp+ACh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+B0h] [rbp-20h]
  int32_t i; // [rsp+B4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+B8h] [rbp-18h]
  int32_t nTitleId; // [rsp+BCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/tongtianpaihang.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileTongTi);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,int>::clear(&this->m_TongTianChiRankReward);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        nTitleId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v1 = std::map<int,int>::operator[](&this->m_TongTianChiRankReward, &nId);
        *v1 = nTitleId;
      }
    }
  }
}

//#####################################
int32_t CfgData::GetTongTianChiReward(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,int>::lower_bound(&this->m_TongTianChiRankReward, &nIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_TongTianChiRankReward)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitTouZiTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-1B0h] BYREF
  SevenTouZi stu; // [rsp+A0h] [rbp-120h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-F0h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-D0h] BYREF
  char v8; // [rsp+FFh] [rbp-C1h] BYREF
  SevenTouZi p_stu; // [rsp+100h] [rbp-C0h] BYREF
  MemChrBagVector v10; // [rsp+130h] [rbp-90h] BYREF
  std::string v11; // [rsp+150h] [rbp-70h] BYREF
  char v12; // [rsp+15Fh] [rbp-61h] BYREF
  MonthTouZi v13; // [rsp+160h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+18Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+190h] [rbp-30h]
  int32_t i; // [rsp+194h] [rbp-2Ch]
  int32_t nIndex; // [rsp+198h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+1A0h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+1A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+1A8h] [rbp-18h]
  int32_t nIndex_0; // [rsp+1ACh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/QiRiTouZi.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_SEVEN_DAY_TOU_ZI_TABEL failed,please check!!");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::vector<MemChrBag>::vector(&stu.vItem);
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCondition = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vItem, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        SevenTouZi::SevenTouZi(&p_stu, &stu);
        CfgTouZiTable::AddSevenTouZi(&this->m_cfgTouZiTable, &p_stu);
        SevenTouZi::~SevenTouZi(&p_stu);
        SevenTouZi::~SevenTouZi(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/ChaoJiTouZi.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_MONTH_TOU_ZI_TABLE failed,please check!!");
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, 36);
          std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.nCondition);
          stu.nId = TabFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          ++nIndex_0;
          
          v3 = TabFile.Search_Posistion( i_0, nIndex_0);
          v11.assign(v3->pString);
          CItemHelper::parseItemVectorString(&v10, &v11);
          std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.nCondition, &v10);
          std::vector<MemChrBag>::~vector(&v10);
          
          LODWORD(stu.vItem._M_impl._M_end_of_storage) = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          MonthTouZi::MonthTouZi(&v13, (const MonthTouZi *const)&stu);
          CfgTouZiTable::AddMonthTouZi(&this->m_cfgTouZiTable, &v13);
          MonthTouZi::~MonthTouZi(&v13);
          MonthTouZi::~MonthTouZi((MonthTouZi *const)&stu);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitTrailerTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  int64_t v4; // rax
  CDBCFile TabFile(0); // [rsp+60h] [rbp-150h] BYREF
  CfgTrailerInfo stu; // [rsp+F0h] [rbp-C0h] OVERLAPPED BYREF
  std::list<AddAttribute> __x; // [rsp+140h] [rbp-70h] BYREF
  _BYTE v8[15]; // [rsp+150h] [rbp-60h] BYREF
  char v9; // [rsp+15Fh] [rbp-51h] BYREF
  int32_t v10[3]; // [rsp+160h] [rbp-50h] BYREF
  char v11; // [rsp+16Fh] [rbp-41h] BYREF
  std::string strItem; // [rsp+170h] [rbp-40h] BYREF
  char v13; // [rsp+17Ah] [rbp-36h] BYREF
  int32_t iBaseTableCount; // [rsp+17Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+180h] [rbp-30h]
  int32_t i; // [rsp+184h] [rbp-2Ch]
  int32_t nIndex; // [rsp+188h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+190h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+194h] [rbp-1Ch]
  int32_t i_0; // [rsp+198h] [rbp-18h]
  int32_t nIndex_0; // [rsp+19Ch] [rbp-14h]
  ItemData v24; // 0:kr00_12.12

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/cfg_trailer.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_TRAILER_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::list<AddAttribute>::list((std::list<AddAttribute> *const)&stu.nRand);
        nIndex = 0;
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        LOBYTE(stu.FullWeiWang) = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        std::string::string(v8, "./ServerConfig/Tables/cfg_trailer.txt", &v9);
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v10, v2->pString, &v11);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v10,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=((std::list<AddAttribute> *const)&stu.nRand, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        ++nIndex;
        nIndex += 5;
        stu.RobberyMoney = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.RobberyVigour = TabFile.Search_Posistion( i, nIndex++)->iValue;
        CfgTrailerTable::Add(&this->m_cfgTrailerTable, (const CfgTrailer *const)&stu);
        CfgTrailer::~CfgTrailer((CfgTrailer *const)&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YaBiao.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_YAO_BIAO_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          memset(&stu, 0, sizeof(stu));
          nIndex_0 = 0;
          stu.nIndex = TabFile.Search_Posistion( i_0, 0)->iValue;
          stu.TrailerId = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.nRand = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.FullMoney = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.FullVigour = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.FullFuWen = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberyMoney = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberyVigour = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberyFuWen = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberMoney = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberVigour = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberFuWen = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          
          v3 = TabFile.Search_Posistion( i_0, nIndex_0);
          strItem.assign(v3->pString);
          v24 = CItemHelper::parseItemDataString(&strItem);
          LODWORD(v4) = v24.m_nId;
          BYTE4(v4) = v24.m_nClass;
          *(_QWORD *)&stu.CostItem.m_nId = v4;
          stu.CostItem.m_nCount = v24.m_nCount;
          
          ++nIndex_0;
          stu.NpcId = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.FullWeiWang = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberyWeiWang = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu.RobberWeiWang = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CfgTrailerTable::AddCfgTrailerInfo(&this->m_cfgTrailerTable, stu);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitTreasureMapTabale()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const std::string *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  int *v8; // rbx
  std::string *v9; // rax
  const char *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  const std::string *v14; // rax
  std::string *v15; // rax
  const char *v16; // rax
  std::string *v17; // rax
  const char *v18; // rax
  std::string *v19; // rax
  const char *v20; // rax
  const CDBCFile::FIELD *v21; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-320h] BYREF
  TreasureMapCfg stu; // [rsp+A0h] [rbp-290h] BYREF
  TreasureMapEventCfg stu_0; // [rsp+100h] [rbp-230h] BYREF
  MapPos stuPos; // [rsp+120h] [rbp-210h] BYREF
  StringVector vstr_0; // [rsp+130h] [rbp-200h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin_0; // [rsp+150h] [rbp-1E0h] BYREF
  StringVector SplitStr_0; // [rsp+160h] [rbp-1D0h] BYREF
  StringVector vstr; // [rsp+180h] [rbp-1B0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin; // [rsp+1A0h] [rbp-190h] BYREF
  StringVector SplitStr; // [rsp+1B0h] [rbp-180h] BYREF
  std::string MapPosString; // [rsp+1D0h] [rbp-160h] BYREF
  std::string RateString; // [rsp+1E0h] [rbp-150h] BYREF
  char v34; // [rsp+1EEh] [rbp-142h] BYREF
  char v35; // [rsp+1EFh] [rbp-141h] BYREF
  std::string delims; // [rsp+1F0h] [rbp-140h] BYREF
  char v37; // [rsp+1FFh] [rbp-131h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+200h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+210h] [rbp-120h] BYREF
  std::string v40; // [rsp+220h] [rbp-110h] BYREF
  char v41; // [rsp+22Bh] [rbp-105h] BYREF
  int __k; // [rsp+22Ch] [rbp-104h] BYREF
  std::string v43; // [rsp+230h] [rbp-100h] BYREF
  char v44; // [rsp+23Fh] [rbp-F1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v45; // [rsp+240h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v46; // [rsp+250h] [rbp-E0h] BYREF
  std::string v47; // [rsp+260h] [rbp-D0h] BYREF
  char v48; // [rsp+26Fh] [rbp-C1h] BYREF
  Position v49; // [rsp+270h] [rbp-C0h] BYREF
  TreasureMapCfg p_stu; // [rsp+280h] [rbp-B0h] BYREF
  TreasureMapEventCfg v51; // [rsp+2E0h] [rbp-50h] BYREF
  int32_t iBaseTableCount; // [rsp+2FCh] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+300h] [rbp-30h]
  int32_t i; // [rsp+304h] [rbp-2Ch]
  int32_t nIndex; // [rsp+308h] [rbp-28h]
  int32_t iBaseTableCount_0; // [rsp+310h] [rbp-20h]
  int32_t iBaseColumnCount_0; // [rsp+314h] [rbp-1Ch]
  int32_t i_0; // [rsp+318h] [rbp-18h]
  int32_t nIndex_0; // [rsp+31Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureMapBase.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_TREASURE_MAP_CFG_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::map<int,int>::map(&stu.m_EventRate);
        std::vector<MapPos>::vector(&stu.m_MaxPosVector);
        nIndex = 0;
        stu.m_ItemId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        RateString.assign(v2->pString);
        
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        MapPosString.assign(v3->pString);
        
        ++nIndex;
        if ( std::operator!=<char>(&RateString, &byte_8C33CF) && std::operator!=<char>(&RateString, "-1") )
        {
          
          delims = "|";
          Answer::StringUtility::split(&SplitStr, &RateString, &delims, 0);
          
          __i._M_current = std::vector<std::string>::begin(&SplitStr)._M_current;
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
            &iterBegin,
            &__i);
          while ( 1 )
          {
            __rhs._M_current = std::vector<std::string>::end(&SplitStr)._M_current;
            if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin, &__rhs) )
              break;
            
            v40 = ":";
            v5 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin);
            Answer::StringUtility::split(&vstr, v5, &v40, 0);
            
            if ( std::vector<std::string>::size(&vstr) == 2 )
            {
              v6 = std::vector<std::string>::operator[](&vstr, 0);
              v7 = (const char *)std::string::c_str(v6);
              __k = atoi(v7);
              v8 = std::map<int,int>::operator[](&stu.m_EventRate, &__k);
              v9 = std::vector<std::string>::operator[](&vstr, 1u);
              v10 = (const char *)std::string::c_str(v9);
              *v8 = atoi(v10);
              LODWORD(v8) = stu.m_MaxProbability;
              v11 = std::vector<std::string>::operator[](&vstr, 1u);
              v12 = (const char *)std::string::c_str(v11);
              stu.m_MaxProbability = (_DWORD)v8 + atoi(v12);
            }
            std::vector<std::string>::~vector(&vstr);
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
          }
          std::vector<std::string>::~vector(&SplitStr);
        }
        if ( std::operator!=<char>(&MapPosString, &byte_8C33CF) && std::operator!=<char>(&MapPosString, "-1") )
        {
          
          v43 = "|";
          Answer::StringUtility::split(&SplitStr_0, &MapPosString, &v43, 0);
          
          v45._M_current = std::vector<std::string>::begin(&SplitStr_0)._M_current;
          __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
            &iterBegin_0,
            &v45);
          while ( 1 )
          {
            v46._M_current = std::vector<std::string>::end(&SplitStr_0)._M_current;
            if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&iterBegin_0, &v46) )
              break;
            
            v47 = ":";
            v14 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iterBegin_0);
            Answer::StringUtility::split(&vstr_0, v14, &v47, 0);
            
            if ( std::vector<std::string>::size(&vstr_0) == 3 )
            {
              Position::Position(&v49, 0, 0);
              stuPos.m_MapId = 0;
              stuPos.m_Pos = v49;
              v15 = std::vector<std::string>::operator[](&vstr_0, 0);
              v16 = (const char *)std::string::c_str(v15);
              stuPos.m_MapId = atoi(v16);
              v17 = std::vector<std::string>::operator[](&vstr_0, 1u);
              v18 = (const char *)std::string::c_str(v17);
              stuPos.m_Pos.x = atoi(v18);
              v19 = std::vector<std::string>::operator[](&vstr_0, 2u);
              v20 = (const char *)std::string::c_str(v19);
              stuPos.m_Pos.y = atoi(v20);
              std::vector<MapPos>::push_back(&stu.m_MaxPosVector, &stuPos);
            }
            std::vector<std::string>::~vector(&vstr_0);
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin_0);
          }
          std::vector<std::string>::~vector(&SplitStr_0);
        }
        TreasureMapCfg::TreasureMapCfg(&p_stu, &stu);
        TreasureMapTabale::AddTreasureMapCfg(&this->m_TreasureMapTabale, &p_stu);
        TreasureMapCfg::~TreasureMapCfg(&p_stu);
        TreasureMapCfg::~TreasureMapCfg(&stu);
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/TreasureMapEvent.txt") )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "open FILE_TREASURE_MAP_EVENT_TABLE failed,please check!!!\n");
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          memset(&stu_0, 0, 20);
          std::string::string(&stu_0.m_EventParam);
          nIndex_0 = 0;
          stu_0.m_EventId = readFile.Search_Posistion( i_0, 0)->iValue;
          stu_0.m_EventType = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          v21 = readFile.Search_Posistion( i_0, ++nIndex_0);
          std::string::operator=(&stu_0.m_EventParam, v21->pString);
          stu_0.m_GongGaoId = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          TreasureMapEventCfg::TreasureMapEventCfg(&v51, &stu_0);
          TreasureMapTabale::AddTreasureMapEventCfg(&this->m_TreasureMapTabale, &v51);
          TreasureMapEventCfg::~TreasureMapEventCfg(&v51);
          TreasureMapEventCfg::~TreasureMapEventCfg(&stu_0);
        }
      }
    }
  }
}

//#####################################
void CfgData::InitTrigSkillTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-F0h] BYREF
  CfgTrigSkill stu; // [rsp+A0h] [rbp-60h] BYREF
  int32_t iBaseTableCount; // [rsp+E0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+E4h] [rbp-1Ch]
  int32_t i; // [rsp+E8h] [rbp-18h]
  int32_t nIndex; // [rsp+ECh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/SkillTrig.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Open FILE_TRIG_SKILL_TABLE fail, please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTrigSkill::CfgTrigSkill(&stu);
        stu.id = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.groupid = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.trigType = readFile.Search_Posistion( i, nIndex++)->iValue;
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::operator=(&stu.trigParam, v1->pString);
        stu.targetType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.trigRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.cdTime = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.trigBuff = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.special = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.specialParam = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.IsPvp = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CfgSkillTable::AddTrigSkill(&this->m_cfgSkillTable, &stu);
        /* CfgTrigSkill::~CfgTrigSkill(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitUltimateChallengeCfg()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  UltimateChallengeCfg *v4; // rax
  int64_t v5; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-170h] BYREF
  UltimateChallengeCfg stu; // [rsp+A0h] [rbp-E0h] BYREF
  std::string strItem; // [rsp+F0h] [rbp-90h] BYREF
  char v9; // [rsp+FFh] [rbp-81h] BYREF
  MemChrBagVector __x; // [rsp+100h] [rbp-80h] BYREF
  std::string strItems; // [rsp+120h] [rbp-60h] BYREF
  char v12; // [rsp+12Fh] [rbp-51h] BYREF
  std::list<Param2> v13; // [rsp+130h] [rbp-50h] BYREF
  _BYTE v14[15]; // [rsp+140h] [rbp-40h] BYREF
  char v15; // [rsp+14Fh] [rbp-31h] BYREF
  int32_t v16[3]; // [rsp+150h] [rbp-30h] BYREF
  char v17; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]
  ItemData v23; // 0:kr00_12.12

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/limitChallenge.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_ULTIMATE_CHALLENGE_TABLE.txt failed,please check!!");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        /* std::vector<MemChrBag>::vector(&stu.GetItems); */
        std::list<Param2>::list(&stu.DropRateList);
        stu.CurMapId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.NextMapId = readFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        stu.Floor = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        v23 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v5) = v23.m_nId;
        BYTE4(v5) = v23.m_nClass;
        *(_QWORD *)&stu.CostItems.m_nId = v5;
        stu.CostItems.m_nCount = v23.m_nCount;
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.GetItems, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.MailId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Score = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        std::string::string(v14, "./ServerConfig/Tables/limitChallenge.txt", &v15);
        
        v3 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v16, v3->pString, &v17);
        CfgData::paraseParam2List(
          (CfgData *const)&v13,
          (const std::string *const)this,
          (int32_t)v16,
          (const std::string *const)(unsigned int)nIndex);
        std::list<Param2>::operator=(&stu.DropRateList, &v13);
        std::list<Param2>::~list(&v13);
        
        ++nIndex;
        stu.DoubleConst = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v4 = std::map<int,UltimateChallengeCfg>::operator[](&this->m_UltimateChallengeCfgMap, &stu.CurMapId);
        UltimateChallengeCfg::operator=(v4, &stu);
        /* UltimateChallengeCfg::~UltimateChallengeCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
UltimateChallengeCfg *CfgData::GetUltimateChallengeCfgMap(int32_t MapId)
{
  int32_t MapIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,UltimateChallengeCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,UltimateChallengeCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  MapIda = MapId;
  it._M_node = std::map<int,UltimateChallengeCfg>::find(&this->m_UltimateChallengeCfgMap, &MapIda)._M_node;
  __x._M_node = std::map<int,UltimateChallengeCfg>::end(&thisa->m_UltimateChallengeCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,UltimateChallengeCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,UltimateChallengeCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitVplanTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  CDBCFile VplanEveryRevard(0); // [rsp+10h] [rbp-3B0h] BYREF
  CDBCFile VplanLevelRevard(0); // [rsp+A0h] [rbp-320h] BYREF
  CDBCFile VplanRevard(0); // [rsp+130h] [rbp-290h] BYREF
  VplanReward stu; // [rsp+1C0h] [rbp-200h] BYREF
  MemChrBagVector __x; // [rsp+200h] [rbp-1C0h] BYREF
  std::string strItems; // [rsp+220h] [rbp-1A0h] BYREF
  char v12; // [rsp+22Fh] [rbp-191h] BYREF
  MemChrBagVector v13; // [rsp+230h] [rbp-190h] BYREF
  std::string v14; // [rsp+250h] [rbp-170h] BYREF
  char v15; // [rsp+25Fh] [rbp-161h] BYREF
  VplanReward p_stu; // [rsp+260h] [rbp-160h] BYREF
  MemChrBagVector v17; // [rsp+2A0h] [rbp-120h] BYREF
  std::string v18; // [rsp+2C0h] [rbp-100h] BYREF
  char v19; // [rsp+2CFh] [rbp-F1h] BYREF
  VplanLevelReward v20; // [rsp+2D0h] [rbp-F0h] BYREF
  MemChrBagVector v21; // [rsp+2F0h] [rbp-D0h] BYREF
  std::string v22; // [rsp+310h] [rbp-B0h] BYREF
  char v23; // [rsp+31Fh] [rbp-A1h] BYREF
  MemChrBagVector v24; // [rsp+320h] [rbp-A0h] BYREF
  std::string v25; // [rsp+340h] [rbp-80h] BYREF
  char v26; // [rsp+34Fh] [rbp-71h] BYREF
  VplanEveryDayReward v27; // [rsp+350h] [rbp-70h] BYREF
  bool ret; // [rsp+38Bh] [rbp-35h]
  int32_t iBaseTableCount; // [rsp+38Ch] [rbp-34h]
  int32_t iBaseColumnCount; // [rsp+390h] [rbp-30h]
  int32_t VplanLeveTableCount; // [rsp+394h] [rbp-2Ch]
  int32_t VplanLeveColumnCount; // [rsp+398h] [rbp-28h]
  int32_t VplanEveryRevardTableCount; // [rsp+39Ch] [rbp-24h]
  int32_t VplanEveryRevardColumnCount; // [rsp+3A0h] [rbp-20h]
  int32_t i; // [rsp+3A4h] [rbp-1Ch]
  int32_t i_0; // [rsp+3A8h] [rbp-18h]
  int32_t i_1; // [rsp+3ACh] [rbp-14h]

  
  ret = VplanRevard.OpenFromTXT( "./ServerConfig/Tables/VplanReward.txt");
  if ( !ret )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_REWARD failed,please check!!\n");
  }
  else
  {
    iBaseTableCount = VplanRevard.GetRecordsNum();
    iBaseColumnCount = VplanRevard.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        /* /* /* std::vector<MemChrBag>::vector(&stu.Reward); */ */ */
        /* /* std::vector<MemChrBag>::vector(&stu.YearVipReward); */ */
        stu.Index = VplanRevard.Search_Posistion( i, 0)->iValue;
        
        v1 = VplanRevard.Search_Posistion( i, 1);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Reward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        v2 = VplanRevard.Search_Posistion( i, 2);
        v14.assign(v2->pString);
        CItemHelper::parseItemVectorString(&v13, &v14);
        std::vector<MemChrBag>::operator=(&stu.YearVipReward, &v13);
        std::vector<MemChrBag>::~vector(&v13);
        
        VplanReward::VplanReward(&p_stu, &stu);
        CfgVplan::AddVplanReward(&this->m_CfgVplan, &p_stu);
        /* VplanReward::~VplanReward(&p_stu); - auto cleanup */
        /* VplanReward::~VplanReward(&stu); - auto cleanup */
      }
      
      ret = VplanLevelRevard.OpenFromTXT( "./ServerConfig/Tables/VplanLevelReward.txt");
      if ( !ret )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_VPLAN_LEVEL_REWARD failed,please check!!\n");
      }
      else
      {
        VplanLeveTableCount = VplanLevelRevard.GetRecordsNum();
        VplanLeveColumnCount = VplanLevelRevard.GetFieldsNum();
        if ( VplanLeveColumnCount > 0 )
        {
          for ( i_0 = 0; i_0 < VplanLeveTableCount; ++i_0 )
          {
            memset(&stu, 0, 32);
            std::vector<MemChrBag>::vector(&stu.Reward);
            stu.Index = VplanLevelRevard.Search_Posistion( i_0, 0)->iValue;
            *(&stu.Index + 1) = VplanLevelRevard.Search_Posistion( i_0, 1)->iValue;
            
            v3 = VplanLevelRevard.Search_Posistion( i_0, 2);
            v18.assign(v3->pString);
            CItemHelper::parseItemVectorString(&v17, &v18);
            std::vector<MemChrBag>::operator=(&stu.Reward, &v17);
            std::vector<MemChrBag>::~vector(&v17);
            
            VplanLevelReward::VplanLevelReward(&v20, (const VplanLevelReward *const)&stu);
            CfgVplan::AddVplanLevelReward(&this->m_CfgVplan, &v20);
            /* VplanLevelReward::~VplanLevelReward(&v20); - auto cleanup */
            VplanLevelReward::~VplanLevelReward((VplanLevelReward *const)&stu);
          }
          
          ret = VplanEveryRevard.OpenFromTXT( "./ServerConfig/Tables/VplanEverydayReward.txt");
          if ( !ret )
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "open FILE_VPLAN_EVERYDAY_REWARD failed,please check!!\n");
          }
          else
          {
            VplanEveryRevardTableCount = VplanEveryRevard.GetRecordsNum();
            VplanEveryRevardColumnCount = VplanEveryRevard.GetFieldsNum();
            if ( VplanEveryRevardColumnCount > 0 )
            {
              for ( i_1 = 0; i_1 < VplanEveryRevardTableCount; ++i_1 )
              {
                memset(&stu, 0, sizeof(stu));
                std::vector<MemChrBag>::vector(&stu.Reward);
                std::vector<MemChrBag>::vector(&stu.YearVipReward);
                stu.Index = VplanEveryRevard.Search_Posistion( i_1, 0)->iValue;
                *(&stu.Index + 1) = VplanEveryRevard.Search_Posistion( i_1, 1)->iValue;
                
                v4 = VplanEveryRevard.Search_Posistion( i_1, 2);
                v22.assign(v4->pString);
                CItemHelper::parseItemVectorString(&v21, &v22);
                std::vector<MemChrBag>::operator=(&stu.Reward, &v21);
                std::vector<MemChrBag>::~vector(&v21);
                
                v5 = VplanEveryRevard.Search_Posistion( i_1, 3);
                v25.assign(v5->pString);
                CItemHelper::parseItemVectorString(&v24, &v25);
                std::vector<MemChrBag>::operator=(&stu.YearVipReward, &v24);
                std::vector<MemChrBag>::~vector(&v24);
                
                VplanEveryDayReward::VplanEveryDayReward(&v27, (const VplanEveryDayReward *const)&stu);
                CfgVplan::AddVplanEveryDayReward(&this->m_CfgVplan, &v27);
                /* VplanEveryDayReward::~VplanEveryDayReward(&v27); - auto cleanup */
                VplanEveryDayReward::~VplanEveryDayReward((VplanEveryDayReward *const)&stu);
              }
            }
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::InitWingCfgTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-1D0h] BYREF
  WingCfg stu; // [rsp+A0h] [rbp-140h] BYREF
  std::list<ItemData> strItems; // [rsp+100h] [rbp-E0h] BYREF
  bool bCombi[15]; // [rsp+110h] [rbp-D0h] BYREF
  char v7; // [rsp+11Fh] [rbp-C1h] BYREF
  AttrAddonVector __x; // [rsp+120h] [rbp-C0h] BYREF
  std::string path; // [rsp+140h] [rbp-A0h] BYREF
  char v10; // [rsp+14Fh] [rbp-91h] BYREF
  std::string addonAttr; // [rsp+150h] [rbp-90h] BYREF
  char v12; // [rsp+15Fh] [rbp-81h] BYREF
  WingCfg p_stu; // [rsp+160h] [rbp-80h] BYREF
  int32_t iBaseTableCount; // [rsp+1C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+1C4h] [rbp-1Ch]
  int32_t i; // [rsp+1C8h] [rbp-18h]
  int32_t nIndex; // [rsp+1CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/AttributeWing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WING_CFG_TABEL failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, sizeof(stu));
        std::list<ItemData>::list(&stu.ConstItems);
        /* std::vector<AttrAddon>::vector(&stu.AddonVector); */
        nIndex = 0;
        stu.Level = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v7);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.ConstItems, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        stu.StartPoints = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.SuccessPoints = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MaxPoints = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Rate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.FailAddPoints = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.SkillId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.SkillLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.IsClear = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/AttributeWing.txt";
        
        v2 = readFile.Search_Posistion( i, nIndex);
        addonAttr.assign(v2->pString);
        paraseAttrAddon(__x, addonAttr, path);
        std::vector<AttrAddon>::operator=(&stu.AddonVector, &__x);
        std::vector<AttrAddon>::~vector(&__x);
        
        ++nIndex;
        WingCfg::WingCfg(&p_stu, &stu);
        CfgWingTable::AddWingCfg(&this->m_cfgWing, &p_stu);
        /* WingCfg::~WingCfg(&p_stu); - auto cleanup */
        /* WingCfg::~WingCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
void CfgData::InitWingEquipPolish()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  int v4; // ebx
  const CDBCFile::FIELD *v5; // rax
  std::list<AddAttribute> *v6; // rax
  int v7; // ebx
  const CDBCFile::FIELD *v8; // rax
  const CDBCFile::FIELD *v9; // rax
  std::list<AddAttribute> *v10; // rax
  CDBCFile TabFile(0); // [rsp+20h] [rbp-2F0h] BYREF
  WingEquipPolish stu; // [rsp+B0h] [rbp-260h] BYREF
  AddAttrList AddAttrs_0; // [rsp+F0h] [rbp-220h] BYREF
  int32_t nId_0; // [rsp+10Ch] [rbp-204h] BYREF
  AddAttrList AddAttrs; // [rsp+110h] [rbp-200h] BYREF
  int32_t nId; // [rsp+12Ch] [rbp-1E4h] BYREF
  std::list<AddAttribute> __x; // [rsp+130h] [rbp-1E0h] BYREF
  _BYTE v18[15]; // [rsp+140h] [rbp-1D0h] BYREF
  char v19; // [rsp+14Fh] [rbp-1C1h] BYREF
  int32_t v20[3]; // [rsp+150h] [rbp-1C0h] BYREF
  char v21; // [rsp+15Fh] [rbp-1B1h] BYREF
  std::list<ItemData> strItems; // [rsp+160h] [rbp-1B0h] BYREF
  bool bCombi[15]; // [rsp+170h] [rbp-1A0h] BYREF
  char v24; // [rsp+17Fh] [rbp-191h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WingEquipPolish> >,bool> v25; // [rsp+180h] [rbp-190h]
  _BYTE v26[64]; // [rsp+190h] [rbp-180h] BYREF
  std::pair<int,int> __a; // [rsp+1D0h] [rbp-140h] BYREF
  _BYTE v28[15]; // [rsp+1E0h] [rbp-130h] BYREF
  char v29; // [rsp+1EFh] [rbp-121h] BYREF
  int32_t v30[3]; // [rsp+1F0h] [rbp-120h] BYREF
  char v31; // [rsp+1FFh] [rbp-111h] BYREF
  std::list<ItemData> v32; // [rsp+200h] [rbp-110h] BYREF
  bool v33[15]; // [rsp+210h] [rbp-100h] BYREF
  char v34; // [rsp+21Fh] [rbp-F1h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WinRefiningCfg> >,bool> v35; // [rsp+220h] [rbp-F0h]
  _BYTE v36[64]; // [rsp+230h] [rbp-E0h] BYREF
  std::pair<int,int> v37; // [rsp+270h] [rbp-A0h] BYREF
  _BYTE v38[15]; // [rsp+280h] [rbp-90h] BYREF
  char v39; // [rsp+28Fh] [rbp-81h] BYREF
  int32_t v40[4]; // [rsp+290h] [rbp-80h] BYREF
  char v41; // [rsp+2A2h] [rbp-6Eh] BYREF
  int32_t iBaseTableCount; // [rsp+2A4h] [rbp-6Ch]
  int32_t iBaseColumnCount; // [rsp+2A8h] [rbp-68h]
  int32_t i; // [rsp+2ACh] [rbp-64h]
  int32_t nIndex; // [rsp+2B0h] [rbp-60h]
  int32_t nType; // [rsp+2B4h] [rbp-5Ch]
  int32_t nLevel; // [rsp+2B8h] [rbp-58h]
  int32_t iBaseTableCount_0; // [rsp+2C0h] [rbp-50h]
  int32_t iBaseColumnCount_0; // [rsp+2C4h] [rbp-4Ch]
  int32_t i_0; // [rsp+2C8h] [rbp-48h]
  int32_t nIndex_0; // [rsp+2CCh] [rbp-44h]
  int32_t iBaseTableCount_1; // [rsp+2D4h] [rbp-3Ch]
  int32_t iBaseColumnCount_1; // [rsp+2D8h] [rbp-38h]
  int32_t i_1; // [rsp+2DCh] [rbp-34h]
  int32_t nIndex_1; // [rsp+2E0h] [rbp-30h]
  int32_t nType_0; // [rsp+2E4h] [rbp-2Ch]
  int32_t nLevel_0; // [rsp+2E8h] [rbp-28h]
  int32_t iBaseTableCount_2; // [rsp+2F0h] [rbp-20h]
  int32_t iBaseColumnCount_2; // [rsp+2F4h] [rbp-1Ch]
  int32_t i_2; // [rsp+2F8h] [rbp-18h]
  int32_t nIndex_2; // [rsp+2FCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WingEquipPolish.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<std::pair<int,int>,WingEquipPolish>::clear(&this->m_WingEquipPolishCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 52);
        std::list<AddAttribute>::list(&stu.lAttrList);
        std::list<ItemData>::list(&stu.lCostList);
        nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v18, "./ServerConfig/Tables/StarSpaceLevel.txt", &v19);
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v20, v2->pString, &v21);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v20,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        ++nIndex;
        
        v3 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v3->pString, &v24);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.lCostList, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        stu.nConstMoney = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.SuitId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.GongGaoId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __a = std::make_pair<int,int>(nType, nLevel);
        std::pair<std::pair const<int,int>,WingEquipPolish>::pair(
          (std::pair<const std::pair<int,int>,WingEquipPolish> *const)v26,
          &__a,
          &stu);
        v25 = std::map<std::pair<int,int>,WingEquipPolish>::insert(
                &this->m_WingEquipPolishCfgMap,
                (const std::pair<const std::pair<int,int>,WingEquipPolish> *const)v26);
        std::pair<std::pair const<int,int>,WingEquipPolish>::~pair((std::pair<const std::pair<int,int>,WingEquipPolish> *const)v26);
        /* WingEquipPolish::~WingEquipPolish(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WingEquipPolishSuit.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_GOBLIN_SUIT_TABLE failed,please check!!!\n");
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        std::map<int,std::list<AddAttribute>>::clear(&this->m_WingEquipPolishSuitMap);
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          nId = TabFile.Search_Posistion( i_0, 0)->iValue;
          ++nIndex_0;
          
          std::string::string(v28, "./ServerConfig/Tables/StarSpaceSuit.txt", &v29);
          
          v5 = TabFile.Search_Posistion( i_0, nIndex_0);
          std::string::string(v30, v5->pString, &v31);
          CfgData::parseAddAttribues(
            (CfgData *const)&AddAttrs,
            (const std::string *const)this,
            (int32_t)v30,
            (const std::string *const)(unsigned int)nIndex_0);
          
          ++nIndex_0;
          v6 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_WingEquipPolishSuitMap, &nId);
          std::list<AddAttribute>::operator=(v6, &AddAttrs);
          std::list<AddAttribute>::~list(&AddAttrs);
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    if ( v4 )
    {
      
      if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WingEquipRefine.txt") )
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "open FILE_WING_EQUIP_REFINING failed,please check!!!\n");
        v7 = 0;
      }
      else
      {
        iBaseTableCount_1 = TabFile.GetRecordsNum();
        iBaseColumnCount_1 = TabFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          std::map<std::pair<int,int>,WinRefiningCfg>::clear(&this->m_WinRefiningCfgMap);
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            memset(&stu, 0, 44);
            std::list<ItemData>::list((std::list<ItemData> *const)&stu.lAttrList._M_impl._M_node._M_prev);
            nType_0 = TabFile.Search_Posistion( i_1, nIndex_1++)->iValue;
            nLevel_0 = TabFile.Search_Posistion( i_1, nIndex_1++)->iValue;
            
            v8 = TabFile.Search_Posistion( i_1, nIndex_1);
            std::string::string(v33, v8->pString, &v34);
            CItemHelper::parseItemDataListString((const std::string *const)&v32, (bool)v33);
            std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.lAttrList._M_impl._M_node._M_prev, &v32);
            std::list<ItemData>::~list(&v32);
            
            LODWORD(stu.lAttrList._M_impl._M_node._M_next) = TabFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            LODWORD(stu.lCostList._M_impl._M_node._M_prev) = TabFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            stu.nConstMoney = TabFile.Search_Posistion( i_1, ++nIndex_1)->iValue;
            ++nIndex_1;
            v37 = std::make_pair<int,int>(nType_0, nLevel_0);
            std::pair<std::pair const<int,int>,WinRefiningCfg>::pair(
              (std::pair<const std::pair<int,int>,WinRefiningCfg> *const)v36,
              &v37,
              (const WinRefiningCfg *const)&stu);
            v35 = std::map<std::pair<int,int>,WinRefiningCfg>::insert(
                    &this->m_WinRefiningCfgMap,
                    (const std::pair<const std::pair<int,int>,WinRefiningCfg> *const)v36);
            std::pair<std::pair const<int,int>,WinRefiningCfg>::~pair((std::pair<const std::pair<int,int>,WinRefiningCfg> *const)v36);
            WinRefiningCfg::~WinRefiningCfg((WinRefiningCfg *const)&stu);
          }
          v7 = 1;
        }
        else
        {
          v7 = 0;
        }
      }
      if ( v7 )
      {
        
        if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WingEquipRefineSuit.txt") )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "open FILE_WING_EQUIP_REFINING_SUIT failed,please check!!!\n");
        }
        else
        {
          iBaseTableCount_2 = TabFile.GetRecordsNum();
          iBaseColumnCount_2 = TabFile.GetFieldsNum();
          if ( iBaseColumnCount_2 > 0 )
          {
            std::map<int,std::list<AddAttribute>>::clear(&this->m_WingEquipRefiningSuitMap);
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              nIndex_2 = 0;
              nId_0 = TabFile.Search_Posistion( i_2, 0)->iValue;
              ++nIndex_2;
              
              std::string::string(v38, "./ServerConfig/Tables/StarSpaceSuit.txt", &v39);
              
              v9 = TabFile.Search_Posistion( i_2, nIndex_2);
              std::string::string(v40, v9->pString, &v41);
              CfgData::parseAddAttribues(
                (CfgData *const)&AddAttrs_0,
                (const std::string *const)this,
                (int32_t)v40,
                (const std::string *const)(unsigned int)nIndex_2);
              
              ++nIndex_2;
              v10 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_WingEquipRefiningSuitMap, &nId_0);
              std::list<AddAttribute>::operator=(v10, &AddAttrs_0);
              std::list<AddAttribute>::~list(&AddAttrs_0);
            }
          }
        }
      }
    }
  }
}

//#####################################
WingEquipPolish *CfgData::GetWingEquipPolishCfg(int32_t nType, int32_t nLevel)
{
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WingEquipPolish> > it; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WingEquipPolish> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(nType, nLevel);
  it._M_node = std::map<std::pair<int,int>,WingEquipPolish>::find(&this->m_WingEquipPolishCfgMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,WingEquipPolish>::end(&this->m_WingEquipPolishCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,WingEquipPolish>>::operator!=(&it, &v6) )
    return (WingEquipPolish *)((char *)std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,WingEquipPolish>>::operator->(&it)
                             + 8);
  else
    return 0;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
AddAttrList CfgData::GetWingEquipPolishSuitAttr(int32_t nId)
{
  int32_t v2; // edx
  std::pair<const int,std::list<AddAttribute> > *v3; // rax
  AddAttrList result; // rax
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,std::list<AddAttribute> > > it; // [rsp+10h] [rbp-40h] BYREF
  AddAttrList Attrs; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<AddAttribute> > > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = *(CfgData **)&nId;
  nIda = v2;
  std::list<AddAttribute>::list(&Attrs);
  std::list<AddAttribute>::clear(&Attrs);
  it._M_node = std::map<int,std::list<AddAttribute>>::find(
                 (std::map<int,std::list<AddAttribute>> *const)(*(_QWORD *)&nId + 11400LL),
                 &nIda)._M_node;
  __x._M_node = std::map<int,std::list<AddAttribute>>::end(&thisa->m_WingEquipPolishSuitMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<AddAttribute>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::list<AddAttribute>>>::operator->(&it);
    std::list<AddAttribute>::list((std::list<AddAttribute> *const)this, &v3->second);
  }
  else
  {
    std::list<AddAttribute>::list((std::list<AddAttribute> *const)this, &Attrs);
  }
  std::list<AddAttribute>::~list(&Attrs);
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
WinRefiningCfg *CfgData::GetWingEquipRefiningCfg(int32_t nType, int32_t nLevel)
{
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WinRefiningCfg> > it; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<int,int>,WinRefiningCfg> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(nType, nLevel);
  it._M_node = std::map<std::pair<int,int>,WinRefiningCfg>::find(&this->m_WinRefiningCfgMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,WinRefiningCfg>::end(&this->m_WinRefiningCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,WinRefiningCfg>>::operator!=(&it, &v6) )
    return (WinRefiningCfg *)((char *)std::_Rb_tree_iterator<std::pair<std::pair const<int,int>,WinRefiningCfg>>::operator->(&it)
                            + 8);
  else
    return 0;
}

//#####################################
// local variable allocation has failed, the output may be wrong!
AddAttrList CfgData::GetWingEquipRefiningSuitAttr(int32_t nId)
{
  int32_t v2; // edx
  std::pair<const int,std::list<AddAttribute> > *v3; // rax
  AddAttrList result; // rax
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,std::list<AddAttribute> > > it; // [rsp+10h] [rbp-40h] BYREF
  AddAttrList Attrs; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<AddAttribute> > > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = *(CfgData **)&nId;
  nIda = v2;
  std::list<AddAttribute>::list(&Attrs);
  std::list<AddAttribute>::clear(&Attrs);
  it._M_node = std::map<int,std::list<AddAttribute>>::find(
                 (std::map<int,std::list<AddAttribute>> *const)(*(_QWORD *)&nId + 11496LL),
                 &nIda)._M_node;
  __x._M_node = std::map<int,std::list<AddAttribute>>::end(&thisa->m_WingEquipRefiningSuitMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<AddAttribute>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::list<AddAttribute>>>::operator->(&it);
    std::list<AddAttribute>::list((std::list<AddAttribute> *const)this, &v3->second);
  }
  else
  {
    std::list<AddAttribute>::list((std::list<AddAttribute> *const)this, &Attrs);
  }
  std::list<AddAttribute>::~list(&Attrs);
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
void CfgData::InitWishRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-100h] BYREF
  CfgWishReward stu; // [rsp+A0h] [rbp-70h] BYREF
  MemChrBagVector __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+E0h] [rbp-30h] BYREF
  char v6; // [rsp+EAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+ECh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+F0h] [rbp-20h]
  int32_t i; // [rsp+F4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+F8h] [rbp-18h]
  int32_t nId; // [rsp+FCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/WishReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WISH_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgWishReward::CfgWishReward(&stu);
        nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nTime = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vReward, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        CfgWishRewardTable::Add(&this->m_cfgWishRewardTable, nId, &stu);
        CfgWishReward::~CfgWishReward(&stu);
      }
    }
  }
}

//#####################################
void CfgData::InitWuHunCreateTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  const CDBCFile::FIELD *v3; // rax
  const CDBCFile::FIELD *v4; // rax
  CreateWuHun *v5; // rax
  int64_t v6; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-170h] BYREF
  CreateWuHun stu; // [rsp+A0h] [rbp-E0h] BYREF
  std::list<ItemData> strItems; // [rsp+F0h] [rbp-90h] BYREF
  bool bCombi[15]; // [rsp+100h] [rbp-80h] BYREF
  char v11; // [rsp+10Fh] [rbp-71h] BYREF
  std::list<RateItem> v12; // [rsp+110h] [rbp-70h] BYREF
  _BYTE v13[15]; // [rsp+120h] [rbp-60h] BYREF
  char v14; // [rsp+12Fh] [rbp-51h] BYREF
  std::string strItem; // [rsp+130h] [rbp-50h] BYREF
  char v16; // [rsp+13Fh] [rbp-41h] BYREF
  std::list<RateItem> v17; // [rsp+140h] [rbp-40h] BYREF
  _BYTE v18[14]; // [rsp+150h] [rbp-30h] BYREF
  char v19; // [rsp+15Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+160h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+164h] [rbp-1Ch]
  int32_t i; // [rsp+168h] [rbp-18h]
  int32_t nIndex; // [rsp+16Ch] [rbp-14h]
  ItemData v25; // 0:kr00_12.12

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WuHunMake.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_CREATE_WU_HUN_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<ItemData>::list(&stu.ConstItem);
        std::list<RateItem>::list(&stu.GetItemRate);
        std::list<RateItem>::list(&stu.GetItemRate2);
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(bCombi, v1->pString, &v11);
        CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
        std::list<ItemData>::operator=(&stu.ConstItem, &strItems);
        std::list<ItemData>::~list(&strItems);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v13, v2->pString, &v14);
        CItemHelper::parseRateItemDataListString((const std::string *const)&v12);
        std::list<RateItem>::operator=(&stu.GetItemRate, &v12);
        std::list<RateItem>::~list(&v12);
        
        ++nIndex;
        nIndex += 3;
        
        v3 = TabFile.Search_Posistion( i, nIndex);
        strItem.assign(v3->pString);
        v25 = CItemHelper::parseItemDataString(&strItem);
        LODWORD(v6) = v25.m_nId;
        BYTE4(v6) = v25.m_nClass;
        *(_QWORD *)&stu.SpecialCost.m_nId = v6;
        stu.SpecialCost.m_nCount = v25.m_nCount;
        
        ++nIndex;
        
        v4 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v18, v4->pString, &v19);
        CItemHelper::parseRateItemDataListString((const std::string *const)&v17);
        std::list<RateItem>::operator=(&stu.GetItemRate2, &v17);
        std::list<RateItem>::~list(&v17);
        
        ++nIndex;
        v5 = std::map<int,CreateWuHun>::operator[](&this->m_CreateWuHunMap, &stu.nId);
        CreateWuHun::operator=(v5, &stu);
        /* CreateWuHun::~CreateWuHun(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
CreateWuHun *CfgData::GetCreateWuHun(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CreateWuHun> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CreateWuHun> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,CreateWuHun>::find(&this->m_CreateWuHunMap, &nIda)._M_node;
  __x._M_node = std::map<int,CreateWuHun>::end(&thisa->m_CreateWuHunMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CreateWuHun>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CreateWuHun>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitWuHunItemTable()
{
  const CDBCFile::FIELD *v1; // rax
  WuHunItem *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-120h] BYREF
  WuHunItem stu; // [rsp+A0h] [rbp-90h] BYREF
  std::list<AddAttribute> __x; // [rsp+E0h] [rbp-50h] BYREF
  _BYTE v6[15]; // [rsp+F0h] [rbp-40h] BYREF
  char v7; // [rsp+FFh] [rbp-31h] BYREF
  int32_t v8[3]; // [rsp+100h] [rbp-30h] BYREF
  char v9; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/WuHun.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_ITEM_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        std::list<AddAttribute>::list(&stu.lAttrList);
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nQuality = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nNeedQuality = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v6, "./ServerConfig/Tables/WuHun.txt", &v7);
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string::string(v8, v1->pString, &v9);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v8,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.lAttrList, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.nTalentId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nTalentLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 8;
        stu.overlay = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 3;
        stu.nDressLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        v2 = std::map<int,WuHunItem>::operator[](&this->m_WuHunItemMap, &stu.nId);
        WuHunItem::operator=(v2, &stu);
        WuHunItem::~WuHunItem(&stu);
      }
    }
  }
}

//#####################################
WuHunItem *CfgData::GetWuHunItem(int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,WuHunItem> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunItem> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,WuHunItem>::find(&this->m_WuHunItemMap, &nIda)._M_node;
  __x._M_node = std::map<int,WuHunItem>::end(&thisa->m_WuHunItemMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WuHunItem>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,WuHunItem>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitWuHunShopTable()
{
  const CDBCFile::FIELD *v1; // rax
  std::list<CfgWuHunShop> *v2; // rax
  CfgWuHunShop *v3; // rax
  MemChrBag v4; // [rsp+0h] [rbp-130h] BYREF
  CfgData *thisa; // [rsp+28h] [rbp-108h]
  CDBCFile TabFile(0); // [rsp+30h] [rbp-100h] BYREF
  CfgWuHunShop stu; // [rsp+C0h] [rbp-70h] BYREF
  int32_t ShopId; // [rsp+FCh] [rbp-34h] BYREF
  std::string strItem; // [rsp+100h] [rbp-30h] BYREF
  char v10; // [rsp+10Eh] [rbp-22h] BYREF
  int32_t iBaseTableCount; // [rsp+110h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+114h] [rbp-1Ch]
  int32_t i; // [rsp+118h] [rbp-18h]
  int32_t nIndex; // [rsp+11Ch] [rbp-14h]

  thisa = this;
  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/MysterShop.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_WU_HUN_SHOP_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.Index = TabFile.Search_Posistion( i, 0)->iValue;
        ShopId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItem.assign(v1->pString);
        CItemHelper::parseItemString(&v4, &strItem);
        stu.Item = v4;
        
        stu.Rate = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.Const = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<CfgWuHunShop>>::operator[](&thisa->m_CfgWuHunShopMap, &ShopId);
        std::list<CfgWuHunShop>::push_back(v2, &stu);
        v3 = std::map<int,CfgWuHunShop>::operator[](&thisa->m_CfgWuHunShopItemMap, &stu.Index);
        *v3 = stu;
      }
    }
  }
}

//#####################################
// local variable allocation has failed, the output may be wrong!
CfgWuHunShopList CfgData::GetWuHunShopItemList(int32_t ShopId)
{
  int32_t v2; // edx
  CfgWuHunShopList result; // rax
  std::pair<const int,std::list<CfgWuHunShop> > *v4; // rax
  int32_t ShopIda; // [rsp+4h] [rbp-4Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-48h]
  CfgWuHunShopList list; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgWuHunShop> > > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgWuHunShop> > > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = *(CfgData **)&ShopId;
  ShopIda = v2;
  it._M_node = std::map<int,std::list<CfgWuHunShop>>::find(
                 (std::map<int,std::list<CfgWuHunShop>> *const)(*(_QWORD *)&ShopId + 10680LL),
                 &ShopIda)._M_node;
  __x._M_node = std::map<int,std::list<CfgWuHunShop>>::end(&thisa->m_CfgWuHunShopMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<CfgWuHunShop>>>::operator==(&it, &__x) )
  {
    std::list<CfgWuHunShop>::list(&list);
    std::list<CfgWuHunShop>::list((std::list<CfgWuHunShop> *const)this, &list);
    std::list<CfgWuHunShop>::~list(&list);
  }
  else
  {
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::list<CfgWuHunShop>>>::operator->(&it);
    std::list<CfgWuHunShop>::list((std::list<CfgWuHunShop> *const)this, &v4->second);
  }
  result._M_impl._M_node._M_next = &this->m_emptyEvents._M_impl._M_node;
  return result;
}

//#####################################
CfgWuHunShop *CfgData::GetWuHunShopItem(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgWuHunShop> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgWuHunShop> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  it._M_node = std::map<int,CfgWuHunShop>::find(&this->m_CfgWuHunShopItemMap, &nIndexa)._M_node;
  __x._M_node = std::map<int,CfgWuHunShop>::end(&thisa->m_CfgWuHunShopItemMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgWuHunShop>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CfgWuHunShop>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitXianYaoTaskTable()
{
  CDBCFile readFile(0); // [rsp+10h] [rbp-D0h] BYREF
  XiangYaoTaskCfg stu; // [rsp+A0h] [rbp-40h] BYREF
  int32_t iBaseTableCount; // [rsp+C0h] [rbp-20h]
  int32_t iBaseColumnCount; // [rsp+C4h] [rbp-1Ch]
  int32_t i; // [rsp+C8h] [rbp-18h]
  int32_t nIndex; // [rsp+CCh] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/XiangYaoTask.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXiangY);
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        stu.TaskId = readFile.Search_Posistion( i, 0)->iValue;
        stu.Star = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MinLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.MaxLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Rate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        std::list<XiangYaoTaskCfg>::push_back(&this->m_XiangYaoTaskCfgList, &stu);
      }
    }
  }
}

//#####################################
int32_t CfgData::RandXiangYaoTaskId(int32_t Level, bool bBest)
{
  bool v3; // al
  XiangYaoTaskCfg *v4; // rax
  int *v5; // rbx
  XiangYaoTaskCfg *v6; // rax
  int32_t first; // ebx
  Answer::Random *v8; // rax
  std::pair<const int,int> *v9; // rax
  std::pair<const int,int> *v10; // rax
  Int32Int32Map TaskIdRate; // [rsp+10h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > itMap; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> it; // [rsp+50h] [rbp-60h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> __x; // [rsp+60h] [rbp-50h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> v17; // [rsp+70h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v18; // [rsp+80h] [rbp-30h] BYREF
  int32_t MaxRate; // [rsp+94h] [rbp-1Ch]
  int32_t SpareId; // [rsp+98h] [rbp-18h]
  int32_t nRand; // [rsp+9Ch] [rbp-14h]

  std::map<int,int>::map(&TaskIdRate);
  MaxRate = 0;
  SpareId = 0;
  it._M_node = std::list<XiangYaoTaskCfg>::begin(&this->m_XiangYaoTaskCfgList)._M_node;
  __x._M_node = std::list<XiangYaoTaskCfg>::end(&this->m_XiangYaoTaskCfgList)._M_node;
  if ( std::_List_iterator<XiangYaoTaskCfg>::operator!=(&it, &__x) )
    SpareId = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->TaskId;
  while ( 1 )
  {
    v17._M_node = std::list<XiangYaoTaskCfg>::end(&this->m_XiangYaoTaskCfgList)._M_node;
    if ( !std::_List_iterator<XiangYaoTaskCfg>::operator!=(&it, &v17) )
      break;
    v3 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->MinLevel <= Level
      && std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->MaxLevel >= Level;
    if ( v3 && (!bBest || std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->Star == 4) )
    {
      v4 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it);
      v5 = std::map<int,int>::operator[](&TaskIdRate, &v4->TaskId);
      *v5 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->Rate;
      v6 = std::_List_iterator<XiangYaoTaskCfg>::operator->(&it);
      MaxRate += v6->Rate;
    }
    std::_List_iterator<XiangYaoTaskCfg>::operator++(&it, 0);
  }
  if ( MaxRate > 0 )
  {
    v8 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v8, 1, MaxRate);
    for ( itMap._M_node = std::map<int,int>::begin(&TaskIdRate)._M_node;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itMap, 0) )
    {
      v18._M_node = std::map<int,int>::end(&TaskIdRate)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itMap, &v18) )
        break;
      v9 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
      if ( v9->second >= nRand )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap)->first;
        goto LABEL_21;
      }
      v10 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
      nRand -= v10->second;
    }
    first = SpareId;
  }
  else
  {
    first = SpareId;
  }
LABEL_21:
  std::map<int,int>::~map(&TaskIdRate);
  return first;
}

//#####################################
int32_t CfgData::getXiangYaoStart(int32_t TaskId)
{
  std::_List_iterator<XiangYaoTaskCfg> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<XiangYaoTaskCfg> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<XiangYaoTaskCfg>::begin(&this->m_XiangYaoTaskCfgList)._M_node;
        std::_List_iterator<XiangYaoTaskCfg>::operator++(&it, 0) )
  {
    __x._M_node = std::list<XiangYaoTaskCfg>::end(&this->m_XiangYaoTaskCfgList)._M_node;
    if ( !std::_List_iterator<XiangYaoTaskCfg>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->TaskId == TaskId )
      return std::_List_iterator<XiangYaoTaskCfg>::operator->(&it)->Star;
  }
  return 0;
}

//#####################################
void CfgData::InitXinMoTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  int v3; // ebx
  const CDBCFile::FIELD *v4; // rax
  const CDBCFile::FIELD *v5; // rax
  int v6; // ebx
  const CDBCFile::FIELD *v7; // rax
  const CDBCFile::FIELD *v8; // rax
  std::string *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  int v14; // ebx
  const CDBCFile::FIELD *v15; // rax
  const CDBCFile::FIELD *v16; // rax
  int v17; // ebx
  int v18; // ebx
  const CDBCFile::FIELD *v19; // rax
  const CDBCFile::FIELD *v20; // rax
  CDBCFile readFile(0); // [rsp+10h] [rbp-470h] BYREF
  XinMoCfg stu; // [rsp+A0h] [rbp-3E0h] BYREF
  int iValue; // [rsp+D0h] [rbp-3B0h]
  XinQingCfg stu_0; // [rsp+E0h] [rbp-3A0h]
  Param2 Param; // [rsp+F0h] [rbp-390h] BYREF
  StringVector vParam; // [rsp+100h] [rbp-380h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+120h] [rbp-360h] BYREF
  StringVector strParams; // [rsp+130h] [rbp-350h] BYREF
  std::string RateString; // [rsp+150h] [rbp-330h] BYREF
  std::list<AddAttribute> __x; // [rsp+160h] [rbp-320h] BYREF
  _BYTE v31[15]; // [rsp+170h] [rbp-310h] BYREF
  char v32; // [rsp+17Fh] [rbp-301h] BYREF
  int32_t v33[3]; // [rsp+180h] [rbp-300h] BYREF
  char v34; // [rsp+18Fh] [rbp-2F1h] BYREF
  XinMoCfg p_Stu; // [rsp+190h] [rbp-2F0h] BYREF
  std::list<ItemData> strItems; // [rsp+1C0h] [rbp-2C0h] BYREF
  bool bCombi[15]; // [rsp+1D0h] [rbp-2B0h] BYREF
  char v38; // [rsp+1DFh] [rbp-2A1h] BYREF
  std::list<AddAttribute> v39; // [rsp+1E0h] [rbp-2A0h] BYREF
  _BYTE v40[15]; // [rsp+1F0h] [rbp-290h] BYREF
  char v41; // [rsp+1FFh] [rbp-281h] BYREF
  int32_t v42[3]; // [rsp+200h] [rbp-280h] BYREF
  char v43; // [rsp+20Fh] [rbp-271h] BYREF
  QiQingCfg v44; // [rsp+210h] [rbp-270h] BYREF
  std::list<ItemData> v45; // [rsp+240h] [rbp-240h] BYREF
  bool v46[14]; // [rsp+250h] [rbp-230h] BYREF
  char v47; // [rsp+25Eh] [rbp-222h] BYREF
  char v48; // [rsp+25Fh] [rbp-221h] BYREF
  std::string delims; // [rsp+260h] [rbp-220h] BYREF
  char v50; // [rsp+26Fh] [rbp-211h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+270h] [rbp-210h] BYREF
  std::string v52; // [rsp+280h] [rbp-200h] BYREF
  char v53; // [rsp+28Fh] [rbp-1F1h] BYREF
  EquipJinHua v54; // [rsp+290h] [rbp-1F0h] BYREF
  std::list<ItemData> v55; // [rsp+2C0h] [rbp-1C0h] BYREF
  bool v56[15]; // [rsp+2D0h] [rbp-1B0h] BYREF
  char v57; // [rsp+2DFh] [rbp-1A1h] BYREF
  std::list<AddAttribute> v58; // [rsp+2E0h] [rbp-1A0h] BYREF
  _BYTE v59[15]; // [rsp+2F0h] [rbp-190h] BYREF
  char v60; // [rsp+2FFh] [rbp-181h] BYREF
  int32_t v61[3]; // [rsp+300h] [rbp-180h] BYREF
  char v62; // [rsp+30Fh] [rbp-171h] BYREF
  XinMoQiQingLevelUpCfg v63; // [rsp+310h] [rbp-170h] BYREF
  MemChrBagVector v64; // [rsp+350h] [rbp-130h] BYREF
  std::string v65; // [rsp+370h] [rbp-110h] BYREF
  char v66; // [rsp+37Fh] [rbp-101h] BYREF
  XinQingReward p_stu; // [rsp+380h] [rbp-100h] BYREF
  Int32Vector v68; // [rsp+3A0h] [rbp-E0h] BYREF
  std::string path; // [rsp+3C0h] [rbp-C0h] BYREF
  char v70; // [rsp+3CFh] [rbp-B1h] BYREF
  std::string str; // [rsp+3D0h] [rbp-B0h] BYREF
  char v72; // [rsp+3E2h] [rbp-9Eh] BYREF
  int32_t iBaseTableCount; // [rsp+3E4h] [rbp-9Ch]
  int32_t iBaseColumnCount; // [rsp+3E8h] [rbp-98h]
  int32_t i; // [rsp+3ECh] [rbp-94h]
  int32_t nIndex; // [rsp+3F0h] [rbp-90h]
  int32_t iBaseTableCount_0; // [rsp+3F8h] [rbp-88h]
  int32_t iBaseColumnCount_0; // [rsp+3FCh] [rbp-84h]
  int32_t i_0; // [rsp+400h] [rbp-80h]
  int32_t nIndex_0; // [rsp+404h] [rbp-7Ch]
  int32_t iBaseTableCount_1; // [rsp+40Ch] [rbp-74h]
  int32_t iBaseColumnCount_1; // [rsp+410h] [rbp-70h]
  int32_t i_1; // [rsp+414h] [rbp-6Ch]
  int32_t nIndex_1; // [rsp+418h] [rbp-68h]
  int32_t iBaseTableCount_2; // [rsp+420h] [rbp-60h]
  int32_t iBaseColumnCount_2; // [rsp+424h] [rbp-5Ch]
  int32_t i_2; // [rsp+428h] [rbp-58h]
  int32_t nIndex_2; // [rsp+42Ch] [rbp-54h]
  int32_t iBaseTableCount_3; // [rsp+434h] [rbp-4Ch]
  int32_t iBaseColumnCount_3; // [rsp+438h] [rbp-48h]
  int32_t i_3; // [rsp+43Ch] [rbp-44h]
  int32_t nIndex_3; // [rsp+440h] [rbp-40h]
  int32_t iBaseTableCount_4; // [rsp+448h] [rbp-38h]
  int32_t iBaseColumnCount_4; // [rsp+44Ch] [rbp-34h]
  int32_t i_4; // [rsp+450h] [rbp-30h]
  int32_t nIndex_4; // [rsp+454h] [rbp-2Ch]
  int32_t nId; // [rsp+458h] [rbp-28h]
  int32_t iBaseTableCount_5; // [rsp+460h] [rbp-20h]
  int32_t iBaseColumnCount_5; // [rsp+464h] [rbp-1Ch]
  int32_t i_5; // [rsp+468h] [rbp-18h]
  int32_t nIndex_5; // [rsp+46Ch] [rbp-14h]

  
  if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/XinMoLevel.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoL);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = readFile.GetRecordsNum();
    iBaseColumnCount = readFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, 44);
        std::list<AddAttribute>::list(&stu.Attr);
        stu.XinMoLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.CostMoney = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.ConstShenYaoBi = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.ConstExp = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.NeedQiQingLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string::string(v31, "./ServerConfig/Tables/XinMoLevel.txt", &v32);
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string::string(v33, v2->pString, &v34);
        CfgData::parseAddAttribues(
          (CfgData *const)&__x,
          (const std::string *const)this,
          (int32_t)v33,
          (const std::string *const)(unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.Attr, &__x);
        std::list<AddAttribute>::~list(&__x);
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        XinMoCfg::XinMoCfg(&p_Stu, &stu);
        XinMoTable::AddXingMoCfg(&this->m_XinMoTable, &p_Stu);
        /* XinMoCfg::~XinMoCfg(&p_Stu); - auto cleanup */
        /* XinMoCfg::~XinMoCfg(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/XinMoQiQing.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoQ);
      v3 = 0;
    }
    else
    {
      iBaseTableCount_0 = readFile.GetRecordsNum();
      iBaseColumnCount_0 = readFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          nIndex_0 = 0;
          memset(&stu, 0, 44);
          std::list<ItemData>::list((std::list<ItemData> *const)&stu.ConstShenYaoBi);
          std::list<AddAttribute>::list(&stu.Attr);
          stu.XinMoLevel = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          
          v4 = readFile.Search_Posistion( i_0, nIndex_0);
          std::string::string(bCombi, v4->pString, &v38);
          CItemHelper::parseItemDataListString((const std::string *const)&strItems, (bool)bCombi);
          std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.ConstShenYaoBi, &strItems);
          std::list<ItemData>::~list(&strItems);
          
          ++nIndex_0;
          
          std::string::string(v40, "./ServerConfig/Tables/XinMoQiQing.txt", &v41);
          
          v5 = readFile.Search_Posistion( i_0, nIndex_0);
          std::string::string(v42, v5->pString, &v43);
          CfgData::parseAddAttribues(
            (CfgData *const)&v39,
            (const std::string *const)this,
            (int32_t)v42,
            (const std::string *const)(unsigned int)nIndex_0);
          std::list<AddAttribute>::operator=(&stu.Attr, &v39);
          std::list<AddAttribute>::~list(&v39);
          
          stu.GongGaoId = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          QiQingCfg::QiQingCfg(&v44, (const QiQingCfg *const)&stu);
          XinMoTable::AddQiQingCfg(&this->m_XinMoTable, &v44);
          /* QiQingCfg::~QiQingCfg(&v44); - auto cleanup */
          QiQingCfg::~QiQingCfg((QiQingCfg *const)&stu);
        }
        v3 = 1;
      }
      else
      {
        v3 = 0;
      }
    }
    if ( v3 )
    {
      
      if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/XinMoJingHua.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingMo);
        v6 = 0;
      }
      else
      {
        iBaseTableCount_1 = readFile.GetRecordsNum();
        iBaseColumnCount_1 = readFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            nIndex_1 = 0;
            memset(&stu, 0, 44);
            std::list<ItemData>::list((std::list<ItemData> *const)&stu.ConstShenYaoBi);
            std::list<Param2>::list((std::list<Param2> *const)&stu.Attr);
            stu.XinMoLevel = readFile.Search_Posistion( i_1, nIndex_1++)->iValue;
            
            v7 = readFile.Search_Posistion( i_1, nIndex_1);
            std::string::string(v46, v7->pString, &v47);
            CItemHelper::parseItemDataListString((const std::string *const)&v45, (bool)v46);
            std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.ConstShenYaoBi, &v45);
            std::list<ItemData>::~list(&v45);
            
            ++nIndex_1;
            
            v8 = readFile.Search_Posistion( i_1, nIndex_1);
            RateString.assign(v8->pString);
            
            ++nIndex_1;
            
            delims = "|";
            Answer::StringUtility::split(&strParams, &RateString, &delims, 0);
            
            for ( iter._M_current = std::vector<std::string>::begin(&strParams)._M_current;
                  __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
            {
              __rhs._M_current = std::vector<std::string>::end(&strParams)._M_current;
              if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
                break;
              
              v52 = ":";
              v9 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
              Answer::StringUtility::split(&vParam, v9, &v52, 0);
              
              if ( std::vector<std::string>::size(&vParam) == 2 )
              {
                Param2::Param2(&Param, 0, 0);
                v10 = std::vector<std::string>::operator[](&vParam, 0);
                v11 = (const char *)std::string::c_str(v10);
                Param.nParam1 = atoi(v11);
                v12 = std::vector<std::string>::operator[](&vParam, 1u);
                v13 = (const char *)std::string::c_str(v12);
                Param.nParam2 = atoi(v13);
                stu.GongGaoId += Param.nParam2;
                std::list<Param2>::push_back((std::list<Param2> *const)&stu.Attr, &Param);
              }
              std::vector<std::string>::~vector(&vParam);
            }
            EquipJinHua::EquipJinHua(&v54, (const EquipJinHua *const)&stu);
            XinMoTable::AddEquipJinHuaCfg(&this->m_XinMoTable, &v54);
            /* EquipJinHua::~EquipJinHua(&v54); - auto cleanup */
            std::vector<std::string>::~vector(&strParams);
            EquipJinHua::~EquipJinHua((EquipJinHua *const)&stu);
          }
          v6 = 1;
        }
        else
        {
          v6 = 0;
        }
      }
      if ( v6 )
      {
        
        if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/QiQingJinJie.txt") )
        {
          Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingMo_0);
          v14 = 0;
        }
        else
        {
          iBaseTableCount_2 = readFile.GetRecordsNum();
          iBaseColumnCount_2 = readFile.GetFieldsNum();
          if ( iBaseColumnCount_2 > 0 )
          {
            for ( i_2 = 0; i_2 < iBaseTableCount_2; ++i_2 )
            {
              nIndex_2 = 0;
              XinMoQiQingLevelUpCfg::XinMoQiQingLevelUpCfg((XinMoQiQingLevelUpCfg *const)&stu);
              stu.XinMoLevel = readFile.Search_Posistion( i_2, nIndex_2++)->iValue;
              stu.CostMoney = readFile.Search_Posistion( i_2, nIndex_2++)->iValue;
              
              v15 = readFile.Search_Posistion( i_2, nIndex_2);
              std::string::string(v56, v15->pString, &v57);
              CItemHelper::parseItemDataListString((const std::string *const)&v55, (bool)v56);
              std::list<ItemData>::operator=((std::list<ItemData> *const)&stu.ConstShenYaoBi, &v55);
              std::list<ItemData>::~list(&v55);
              
              LODWORD(stu.Attr._M_impl._M_node._M_next) = readFile.Search_Posistion( i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              
              std::string::string(v59, "./ServerConfig/Tables/QiQingJinJie.txt", &v60);
              
              v16 = readFile.Search_Posistion( i_2, nIndex_2);
              std::string::string(v61, v16->pString, &v62);
              CfgData::parseAddAttribues(
                (CfgData *const)&v58,
                (const std::string *const)this,
                (int32_t)v61,
                (const std::string *const)(unsigned int)nIndex_2);
              std::list<AddAttribute>::operator=(
                (std::list<AddAttribute> *const)&stu.Attr._M_impl._M_node._M_prev,
                &v58);
              std::list<AddAttribute>::~list(&v58);
              
              iValue = readFile.Search_Posistion( i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              XinMoQiQingLevelUpCfg::XinMoQiQingLevelUpCfg(&v63, (const XinMoQiQingLevelUpCfg *const)&stu);
              XinMoTable::AddXinMoQiQingLevelUpCfg(&this->m_XinMoTable, &v63);
              /* XinMoQiQingLevelUpCfg::~XinMoQiQingLevelUpCfg(&v63); - auto cleanup */
              XinMoQiQingLevelUpCfg::~XinMoQiQingLevelUpCfg((XinMoQiQingLevelUpCfg *const)&stu);
            }
            v14 = 1;
          }
          else
          {
            v14 = 0;
          }
        }
        if ( v14 )
        {
          
          if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/XinQing.txt") )
          {
            Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXingMo_0);
            v17 = 0;
          }
          else
          {
            iBaseTableCount_3 = readFile.GetRecordsNum();
            iBaseColumnCount_3 = readFile.GetFieldsNum();
            if ( iBaseColumnCount_3 > 0 )
            {
              for ( i_3 = 0; i_3 < iBaseTableCount_3; ++i_3 )
              {
                nIndex_3 = 0;
                stu_0.nLeftCount = readFile.Search_Posistion( i_3, 0)->iValue;
                stu_0.nAppearCount = readFile.Search_Posistion( i_3, ++nIndex_3)->iValue;
                stu_0.Rate = readFile.Search_Posistion( i_3, ++nIndex_3)->iValue;
                ++nIndex_3;
                XinMoTable::AddXinQingCfg(&this->m_XinMoTable, stu_0);
              }
              v17 = 1;
            }
            else
            {
              v17 = 0;
            }
          }
          if ( v17 )
          {
            
            if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/XinQingReward.txt") )
            {
              Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileXinMoX);
              v18 = 0;
            }
            else
            {
              iBaseTableCount_4 = readFile.GetRecordsNum();
              iBaseColumnCount_4 = readFile.GetFieldsNum();
              if ( iBaseColumnCount_4 > 0 )
              {
                for ( i_4 = 0; i_4 < iBaseTableCount_4; ++i_4 )
                {
                  nIndex_4 = 0;
                  nId = readFile.Search_Posistion( i_4, 0)->iValue;
                  ++nIndex_4;
                  memset(&stu, 0, 32);
                  std::vector<MemChrBag>::vector((std::vector<MemChrBag> *const)&stu.ConstShenYaoBi);
                  
                  v19 = readFile.Search_Posistion( i_4, nIndex_4);
                  v65.assign(v19->pString);
                  CItemHelper::parseItemVectorString(&v64, &v65);
                  std::vector<MemChrBag>::operator=((std::vector<MemChrBag> *const)&stu.ConstShenYaoBi, &v64);
                  std::vector<MemChrBag>::~vector(&v64);
                  
                  stu.XinMoLevel = readFile.Search_Posistion( i_4, ++nIndex_4)->iValue;
                  ++nIndex_4;
                  XinQingReward::XinQingReward(&p_stu, (const XinQingReward *const)&stu);
                  XinMoTable::AddXinQingReward(&this->m_XinMoTable, nId, &p_stu);
                  /* XinQingReward::~XinQingReward(&p_stu); - auto cleanup */
                  XinQingReward::~XinQingReward((XinQingReward *const)&stu);
                }
                v18 = 1;
              }
              else
              {
                v18 = 0;
              }
            }
            if ( v18 )
            {
              
              if ( !readFile.OpenFromTXT( "./ServerConfig/Tables/Energy.txt") )
              {
                Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileEnergy);
              }
              else
              {
                iBaseTableCount_5 = readFile.GetRecordsNum();
                iBaseColumnCount_5 = readFile.GetFieldsNum();
                if ( iBaseColumnCount_5 > 0 )
                {
                  for ( i_5 = 0; i_5 < iBaseTableCount_5; ++i_5 )
                  {
                    nIndex_5 = 1;
                    this->m_EnergyCfg.MaxEnergy = readFile.Search_Posistion( i_5, 1)->iValue;
                    this->m_EnergyCfg.EnergyTime = readFile.Search_Posistion( i_5, ++nIndex_5)->iValue;
                    ++nIndex_5;
                    
                    path = "./ServerConfig/Tables/Energy.txt";
                    
                    v20 = readFile.Search_Posistion( i_5, nIndex_5);
                    str.assign(v20->pString);
                    CfgData::paraseInt32Vector2(&v68, this, &str, &path, 0);
                    std::vector<int>::operator=(&this->m_EnergyCfg.EnergyPrice, &v68);
                    std::vector<int>::~vector(&v68);
                    
                    this->m_EnergyCfg.BuyAddEnergy = readFile.Search_Posistion( i_5, ++nIndex_5)->iValue;
                    ++nIndex_5;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

//#####################################
// local variable allocation has failed, the output may be wrong!
void CfgData::InitXunLeiTable()
{
  const CDBCFile::FIELD *v1; // rax
  XunLeiCfg *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-110h] BYREF
  XunLeiCfg stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/XunLeiBox.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        /* std::vector<MemChrBag>::vector(&stu.vRewards); */
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, 1)->iValue;
        
        v1 = TabFile.Search_Posistion( i, 3);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.nCondition = TabFile.Search_Posistion( i, 5)->iValue;
        v2 = std::map<int,XunLeiCfg>::operator[](&this->m_XunLeiCfgMap, &stu.nIndex);
        XunLeiCfg::operator=(v2, &stu);
        /* XunLeiCfg::~XunLeiCfg(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
XunLeiCfg *CfgData::GetXunLeiCfg(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  it._M_node = std::map<int,XunLeiCfg>::find(&this->m_XunLeiCfgMap, &nIndexa)._M_node;
  __x._M_node = std::map<int,XunLeiCfg>::end(&thisa->m_XunLeiCfgMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitYYDaTing()
{
  const CDBCFile::FIELD *v1; // rax
  CfgYYGameApp *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-110h] BYREF
  CfgYYGameApp stu; // [rsp+A0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+F0h] [rbp-30h] BYREF
  char v7; // [rsp+102h] [rbp-1Eh] BYREF
  int32_t iBaseTableCount; // [rsp+104h] [rbp-1Ch]
  int32_t iBaseColumnCount; // [rsp+108h] [rbp-18h]
  int32_t i; // [rsp+10Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YYDaTing.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 36);
        std::vector<MemChrBag>::vector(&stu.Rewards);
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, 1)->iValue;
        
        v1 = TabFile.Search_Posistion( i, 3);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.nCondition = TabFile.Search_Posistion( i, 4)->iValue;
        v2 = std::map<int,CfgYYGameApp>::operator[](&this->m_CfgYYGameAppMap, &stu.nIndex);
        CfgYYGameApp::operator=(v2, &stu);
        /* CfgYYGameApp::~CfgYYGameApp(&stu); - auto cleanup */
      }
    }
  }
}

//#####################################
CfgYYGameApp *CfgData::GetYYGameApp(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgYYGameApp> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgYYGameApp> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  it._M_node = std::map<int,CfgYYGameApp>::find(&this->m_CfgYYGameAppMap, &nIndexa)._M_node;
  __x._M_node = std::map<int,CfgYYGameApp>::end(&thisa->m_CfgYYGameAppMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgYYGameApp>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CfgYYGameApp>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitYYVip()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2; // rax
  CfgYYVip *v3; // rax
  int v4; // ebx
  CDBCFile TabFile(0); // [rsp+10h] [rbp-150h] BYREF
  CfgYYVip stu; // [rsp+A0h] [rbp-C0h] BYREF
  CfgYYSuperBuff stu_1; // [rsp+D0h] [rbp-90h] BYREF
  CfgYYSuperBuff stu_0; // [rsp+E0h] [rbp-80h] BYREF
  MemChrBagVector __x; // [rsp+F0h] [rbp-70h] BYREF
  std::string strItems; // [rsp+110h] [rbp-50h] BYREF
  char v11; // [rsp+122h] [rbp-3Eh] BYREF
  int32_t iBaseTableCount; // [rsp+124h] [rbp-3Ch]
  int32_t iBaseColumnCount; // [rsp+128h] [rbp-38h]
  int32_t i; // [rsp+12Ch] [rbp-34h]
  int32_t iBaseTableCount_0; // [rsp+134h] [rbp-2Ch]
  int32_t iBaseColumnCount_0; // [rsp+138h] [rbp-28h]
  int32_t i_0; // [rsp+13Ch] [rbp-24h]
  int32_t iBaseTableCount_1; // [rsp+144h] [rbp-1Ch]
  int32_t iBaseColumnCount_1; // [rsp+148h] [rbp-18h]
  int32_t i_1; // [rsp+14Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YYHuiYuan.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        memset(&stu, 0, 44);
        std::vector<MemChrBag>::vector(&stu.Rewards);
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, 1)->iValue;
        
        v2 = TabFile.Search_Posistion( i, 3);
        strItems.assign(v2->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&stu.Rewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        stu.nCondition = TabFile.Search_Posistion( i, 4)->iValue;
        stu.nPric = TabFile.Search_Posistion( i, 5)->iValue;
        stu.nLimit = TabFile.Search_Posistion( i, 6)->iValue;
        v3 = std::map<int,CfgYYVip>::operator[](&this->m_CfgYYVipMap, &stu.nIndex);
        CfgYYVip::operator=(v3, &stu);
        /* CfgYYVip::~CfgYYVip(&stu); - auto cleanup */
      }
      v1 = 1;
    }
    else
    {
      v1 = 0;
    }
  }
  if ( v1 )
  {
    
    if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YYChaowanBoss.txt") )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
      v4 = 0;
    }
    else
    {
      iBaseTableCount_0 = TabFile.GetRecordsNum();
      iBaseColumnCount_0 = TabFile.GetFieldsNum();
      if ( iBaseColumnCount_0 > 0 )
      {
        for ( i_0 = 0; i_0 < iBaseTableCount_0; ++i_0 )
        {
          *(_QWORD *)&stu_0.SuperVipLevel = 0;
          stu_0.AttrType = 0;
          stu_0.SuperVipLevel = TabFile.Search_Posistion( i_0, 1)->iValue;
          stu_0.AttrRate = TabFile.Search_Posistion( i_0, 3)->iValue;
          stu_0.AttrType = TabFile.Search_Posistion( i_0, 5)->iValue;
          std::list<CfgYYSuperBuff>::push_front(&this->m_CfgYYSuperBuffList, &stu_0);
        }
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    if ( v4 )
    {
      
      if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/SpecialThirtySevenBuff.txt") )
      {
        Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, &byte_8C91C8);
      }
      else
      {
        iBaseTableCount_1 = TabFile.GetRecordsNum();
        iBaseColumnCount_1 = TabFile.GetFieldsNum();
        if ( iBaseColumnCount_1 > 0 )
        {
          for ( i_1 = 0; i_1 < iBaseTableCount_1; ++i_1 )
          {
            *(_QWORD *)&stu_1.SuperVipLevel = 0;
            stu_1.AttrType = 0;
            stu_1.SuperVipLevel = TabFile.Search_Posistion( i_1, 1)->iValue;
            stu_1.AttrRate = TabFile.Search_Posistion( i_1, 3)->iValue;
            stu_1.AttrType = TabFile.Search_Posistion( i_1, 5)->iValue;
            std::list<CfgYYSuperBuff>::push_front(&this->m_Cfg37wanSuperBuffList, &stu_1);
          }
        }
      }
    }
  }
}

//#####################################
CfgYYVip *CfgData::GetYYVip(int32_t nIndex)
{
  int32_t nIndexa; // [rsp+4h] [rbp-2Ch] BYREF
  CfgData *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgYYVip> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgYYVip> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIndexa = nIndex;
  it._M_node = std::map<int,CfgYYVip>::find(&this->m_CfgYYVipMap, &nIndexa)._M_node;
  __x._M_node = std::map<int,CfgYYVip>::end(&thisa->m_CfgYYVipMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgYYVip>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_iterator<std::pair<int const,CfgYYVip>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const CfgYYSuperBuff *CfgData::GetSuperBuff(int32_t SuperLevel)
{
  std::_List_const_iterator<CfgYYSuperBuff> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<CfgYYSuperBuff> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<CfgYYSuperBuff>::begin(&this->m_CfgYYSuperBuffList)._M_node;
        std::_List_const_iterator<CfgYYSuperBuff>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgYYSuperBuff>::end(&this->m_CfgYYSuperBuffList)._M_node;
    if ( !std::_List_const_iterator<CfgYYSuperBuff>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_const_iterator<CfgYYSuperBuff>::operator->(&iter)->SuperVipLevel <= SuperLevel )
      return std::_List_const_iterator<CfgYYSuperBuff>::operator*(&iter);
  }
  return 0;
}

//#####################################
const CfgYYSuperBuff *CfgData::Get37wanSuperBuff(int32_t SuperLevel)
{
  std::_List_const_iterator<CfgYYSuperBuff> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<CfgYYSuperBuff> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<CfgYYSuperBuff>::begin(&this->m_Cfg37wanSuperBuffList)._M_node;
        std::_List_const_iterator<CfgYYSuperBuff>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgYYSuperBuff>::end(&this->m_Cfg37wanSuperBuffList)._M_node;
    if ( !std::_List_const_iterator<CfgYYSuperBuff>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_const_iterator<CfgYYSuperBuff>::operator->(&iter)->SuperVipLevel <= SuperLevel )
      return std::_List_const_iterator<CfgYYSuperBuff>::operator*(&iter);
  }
  return 0;
}

//#####################################
void CfgData::InitYellowDailyRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-1A0h] BYREF
  CfgTencentGift year; // [rsp+A0h] [rbp-110h] BYREF
  CfgTencentGift daily; // [rsp+E0h] [rbp-D0h] BYREF
  MemChrBagVector __x; // [rsp+120h] [rbp-90h] BYREF
  std::string strItems; // [rsp+140h] [rbp-70h] BYREF
  char v8; // [rsp+14Fh] [rbp-61h] BYREF
  MemChrBagVector v9; // [rsp+150h] [rbp-60h] BYREF
  std::string v10; // [rsp+170h] [rbp-40h] BYREF
  char v11; // [rsp+186h] [rbp-2Ah] BYREF
  int32_t iBaseTableCount; // [rsp+188h] [rbp-28h]
  int32_t iBaseColumnCount; // [rsp+18Ch] [rbp-24h]
  int32_t i; // [rsp+190h] [rbp-20h]
  int32_t nIndex; // [rsp+194h] [rbp-1Ch]
  int32_t nId; // [rsp+198h] [rbp-18h]
  int32_t nLevel; // [rsp+19Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YellowEverydayReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_DAILY_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&daily);
        CfgTencentGift::CfgTencentGift(&year);
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&daily.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v10.assign(v2->pString);
        CItemHelper::parseItemVectorString(&v9, &v10);
        std::vector<MemChrBag>::operator=(&year.vRewards, &v9);
        std::vector<MemChrBag>::~vector(&v9);
        
        ++nIndex;
        daily.nLevel = nLevel;
        year.nLevel = nLevel;
        CfgTencentTable::AddYellowDailyGift(&this->m_cfgTencentTable, &daily);
        CfgTencentTable::AddYellowYearGift(&this->m_cfgTencentTable, &year);
        CfgTencentGift::~CfgTencentGift(&year);
        CfgTencentGift::~CfgTencentGift(&daily);
      }
    }
  }
}

//#####################################
void CfgData::InitYellowLevelRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  const CDBCFile::FIELD *v2; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-150h] BYREF
  CfgTencentGift gift; // [rsp+A0h] [rbp-C0h] BYREF
  MemChrBagVector __x; // [rsp+E0h] [rbp-80h] BYREF
  std::string strItems; // [rsp+100h] [rbp-60h] BYREF
  char v7; // [rsp+10Fh] [rbp-51h] BYREF
  MemChrBagVector v8; // [rsp+110h] [rbp-50h] BYREF
  std::string v9; // [rsp+130h] [rbp-30h] BYREF
  char v10; // [rsp+13Ah] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+13Ch] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+140h] [rbp-20h]
  int32_t i; // [rsp+144h] [rbp-1Ch]
  int32_t nIndex; // [rsp+148h] [rbp-18h]
  int32_t nId; // [rsp+14Ch] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YellowLevelReward.txt") )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "open FILE_YELLOW_LEVEL_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        CfgTencentGift::CfgTencentGift(&gift);
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&__x, &strItems);
        std::vector<MemChrBag>::operator=(&gift.vRewards, &__x);
        std::vector<MemChrBag>::~vector(&__x);
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v9.assign(v2->pString);
        CItemHelper::parseItemVectorString(&v8, &v9);
        std::vector<MemChrBag>::operator=(&gift.vVipRewards, &v8);
        std::vector<MemChrBag>::~vector(&v8);
        
        ++nIndex;
        CfgTencentTable::AddYellowLevelGift(&this->m_cfgTencentTable, nId, &gift);
        CfgTencentGift::~CfgTencentGift(&gift);
      }
    }
  }
}

//#####################################
void CfgData::InitYellowRewardTable()
{
  const CDBCFile::FIELD *v1; // rax
  CDBCFile TabFile(0); // [rsp+10h] [rbp-E0h] BYREF
  MemChrBagVector vReward; // [rsp+A0h] [rbp-50h] BYREF
  std::string strItems; // [rsp+C0h] [rbp-30h] BYREF
  char v5; // [rsp+CAh] [rbp-26h] BYREF
  int32_t iBaseTableCount; // [rsp+CCh] [rbp-24h]
  int32_t iBaseColumnCount; // [rsp+D0h] [rbp-20h]
  int32_t i; // [rsp+D4h] [rbp-1Ch]
  int32_t nIndex; // [rsp+D8h] [rbp-18h]
  int32_t nId; // [rsp+DCh] [rbp-14h]

  
  if ( !TabFile.OpenFromTXT( "./ServerConfig/Tables/YellowReward.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "open FILE_YELLOW_REWARD_TABLE failed,please check!!!\n");
  }
  else
  {
    iBaseTableCount = TabFile.GetRecordsNum();
    iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        nId = TabFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems.assign(v1->pString);
        CItemHelper::parseItemVectorString(&vReward, &strItems);
        
        ++nIndex;
        CfgTencentTable::SetYellowNewerGift(&this->m_cfgTencentTable, &vReward);
        std::vector<MemChrBag>::~vector(&vReward);
      }
    }
  }
}

//#####################################
