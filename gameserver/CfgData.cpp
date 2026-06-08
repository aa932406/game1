
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

bool CfgData::init(int32_t line, int32_t debug)
{
	// 2019版：fetchServerConfig 接受 line 参数
	fetchServerConfig(line);
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
	CfgSkillMap::iterator it = m_skills.find(id);
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

void CfgData::fetchServerConfig(int32_t line)
{
	// 跨服模式下跳过
	if (line == 9)
		return;

	MySqlDBGuard db(DBPOOL);

	// 读取服务器配置（2019版：从 sys_server_start 表读取）
	MySqlQuery result = db.query("SELECT * FROM `sys_server_start`");
	if (!result.eof())
	{
		m_heFuTime = result.getIntValue("he_fu_time", 0);
		m_kaiFuTime = result.getIntValue("kai_fu_time", 0);
		m_serverType = result.getIntValue("type", 0);
	}

	// 兼容旧版：读取 create_time
	result = db.query("SELECT `value` FROM `sys_server_config` WHERE `name`='create_time'");
	if (!result.eof())
	{
		m_createTime = atoi(result.getStringValue(0));
	}

	// 兼容旧版：读取/写入 startGame_time
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
// NOTE: Disabled — these require further porting of decompiled code
// See README.md for remaining struct definitions needed
#if 1


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
  else
  {
    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      m_Wan360RewardTypeMap.clear();
      for ( int32_t i = 0; i < iBaseTableCount; ++i )
      {
        std::string strPlatform = TabFile.Search_Posistion( i, 0 )->pString;
        int32_t nIconId = TabFile.Search_Posistion( i, 1 )->iValue;
        m_Wan360RewardTypeMap[strPlatform] = nIconId;
      }
    }
  }
}
void CfgData::InitActDropTable()
{
  CDBCFile tabFile;
  ActDropItem dropItem;
  int32_t tableCount;
  int32_t columnCount;
  int32_t recordIndex;

  
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
      for (recordIndex = 0; recordIndex < tableCount; ++recordIndex)
      {
        int fieldIndex = 0;
        memset(&dropItem, 0, sizeof(dropItem));
        
        // 读取各字段数据
        dropItem.nType = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nMinLevel = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nMaxLevel = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nMapType = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nId = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nClass = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nCount = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        dropItem.nBind = tabFile.Search_Posistion(recordIndex, fieldIndex++)->iValue;
        
        // 读取开始时间
        const CDBCFile::FIELD* startTimeField = tabFile.Search_Posistion(recordIndex, fieldIndex++);
        std::string startTimeStr = startTimeField->pString;
        dropItem.nStartTime = Answer::DayTime::StringToIntTime(startTimeStr);
        
        fieldIndex++; // 跳过未使用的字段索引
        
        const CDBCFile::FIELD* endTimeField = tabFile.Search_Posistion(recordIndex, fieldIndex++);
        std::string endTimeStr = endTimeField->pString;
        dropItem.nEndTime = Answer::DayTime::StringToIntTime(endTimeStr);
        
        dropItem.nProbability = tabFile.Search_Posistion(recordIndex, ++fieldIndex)->iValue;
        fieldIndex++;
        
        // 添加到对应类型的掉落列表中
        m_ActDropItemListMap[dropItem.nType].push_back(dropItem);
      }
    }
  }
}

//#####################################
ActDropItemList CfgData::GetAcrDropList(int32_t nType)
{
	ActDropItemList result;
	auto it = m_ActDropItemListMap.find(nType);
	if (it != m_ActDropItemListMap.end())
		result = it->second;
	return result;
}

//#####################################
void CfgData::InitActiveSkillTable()
{
  const CDBCFile::FIELD *v1;
  CfgActiveSkill skill;
  CDBCFile TabFile(0);
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        skill.summon_attr = __x;
        
        skill.summon_limit = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 17;
        skill.boss_addon_damage = TabFile.Search_Posistion( i, nIndex++)->iValue;
        skill.append_value = TabFile.Search_Posistion( i, nIndex++)->iValue;
        skill.shu_lian_du = TabFile.Search_Posistion( i, nIndex++)->iValue;
        skill.cd += skill.cd_adjust;
        m_cfgSkillTable.AddActiveSkill(skill);

      }
    }
  }
}

//#####################################
void CfgData::InitAttrBattleTable()
{
  CDBCFile readFile(0);
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nAttr;
  int32_t nBattle;

  
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
      memset(this->m_cfgAttrBattle, 0, sizeof(m_cfgAttrBattle));
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
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  ItemDataList vItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nTimes;

  
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
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&vItem, (bool)bCombi);
        
        ++nIndex;
        m_cfgBFZLEnterCostTable.AddEnterCost(nTimes, vItem);
      }
    }
  }
}

//#####################################
void CfgData::InitBaoKuFuBen()
{
  int v1; // ebx
  BaoKuFuBen *v2;
  int32_t v3; // ebx
  int32_t v4; // ebx
  int32_t v5; // ebx
  int32_t v6; // ebx
  int32_t v7; // ebx
  int32_t v8; // ebx
  BaoKuRandom *v9;
  BaoKuRandom *p_stu_0;
  unsigned int v11; // r8d
  CDBCFile readFile_0(0);
  BaoKuRandom stu_0;
  BaoKuFuBen stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;
  int32_t j;

  CDBCFile::CDBCFile((CDBCFile *const)&stu_0, 0);
  if ( !stu_0.OpenFromTXT("./ServerConfig/Tables/BaoKuFuBen.txt") )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, aOpenFileBaoKuF);
    v1 = 0;
  }
  else
  {
    iBaseTableCount = stu_0.GetRecordsNum();
    iBaseColumnCount = stu_0.GetFieldsNum();
    if ( iBaseColumnCount > 0 )
    {
      std::map<int,BaoKuFuBen>::clear(&this->m_BaoKuFuBenMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.FuBenId = stu_0.Search_Posistion(i, 0)->iValue;
        stu.InitCount = stu_0.Search_Posistion(i, ++nIndex)->iValue;
        stu.BuyCount = stu_0.Search_Posistion(i, ++nIndex)->iValue;
        stu.Gold = stu_0.Search_Posistion(i, ++nIndex)->iValue;
        stu.AddTimes = stu_0.Search_Posistion(i, ++nIndex)->iValue;
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
          memcpy(v9, p_stu_0, 8 * v12);
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
	auto it = m_BaoKuFuBenMap.find(FuBenId);
	if (it != m_BaoKuFuBenMap.end())
		return &it->second;
	return NULL;
}

//#####################################
BaoKuRandomMap CfgData::GetBaoKuRandomMap()
{
  return m_BaoKuRandomMap;
}

//#####################################
void CfgData::InitBeastShrineEnterCostTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  ItemDataList vItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nTimes;

  
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
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&vItem, (bool)bCombi);
        
        ++nIndex;
        m_CfgBeastShrineTable.AddEnterCost(nTimes, vItem);
      }
    }
  }
}

//#####################################
void CfgData::InitBlueDailyRewardTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  CDBCFile TabFile(0);
  CfgTencentGift high;
  CfgTencentGift year;
  CfgTencentGift daily;
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v11;
  std::string v12;
  MemChrBagVector v14;
  std::string v15;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;
  int32_t nLevel;

  
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
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        daily.vRewards = __x;
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v12 = v2->pString;
        CItemHelper::parseItemVectorString(&v11, &v12);
        year.vRewards = v11;
        
        ++nIndex;
        
        v3 = TabFile.Search_Posistion( i, nIndex);
        v15 = v3->pString;
        CItemHelper::parseItemVectorString(&v14, &v15);
        high.vRewards = v14;
        
        ++nIndex;
        daily.nLevel = nLevel;
        year.nLevel = nLevel;
        high.nLevel = nLevel;
        m_cfgTencentTable.AddBlueDailyGift(daily);
        m_cfgTencentTable.AddBlueYearGift(year);
        m_cfgTencentTable.AddBlueHighGift(high);


      }
    }
  }
}

//#####################################
void CfgData::InitBlueLevelRewardTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile TabFile(0);
  CfgTencentGift gift;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;

  
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
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        gift.vRewards = __x;
        
        ++nIndex;
        m_cfgTencentTable.AddBlueLevelGift(nId, gift);

      }
    }
  }
}

//#####################################
void CfgData::InitBlueRewardTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile TabFile(0);
  MemChrBagVector vReward;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&vReward, &strItems);
        
        ++nIndex;
        m_cfgTencentTable.SetBlueNewerGift(vReward);
      }
    }
  }
}

//#####################################
void CfgData::InitBossDistribution()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  CDBCFile TabFile(0);
  std::string BossMapListString_0;
  MapBossInfo stu_0;
  std::string BossMapListString;
  BossLevelInfo stu;
  std::list<int> __x;
  BossLevelInfo p_stu;
  std::list<int> v13;
  MapBossInfo v14;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;

  
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
        stu.BossLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        BossMapListString = v2->pString;
        
        ++nIndex;
        parseInt32List(__x, BossMapListString);
        stu.BossMapList = __x;
        p_stu = stu;
        m_BossDistribution.AddBossLevelInfo(p_stu);


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
          stu_0.nId = TabFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          
          v3 = TabFile.Search_Posistion( i_0, nIndex_0);
          BossMapListString_0 = v3->pString;
          
          ++nIndex_0;
          parseInt32List(v13, BossMapListString_0);
          stu_0.BossMapList = v13;
          v14 = stu_0;
          m_BossDistribution.AddMapBossInfo(v14);


        }
      }
    }
  }
}

//#####################################
void CfgData::InitBossFirstKilledTable()
{
  CfgBossFirstKilled *v1;
  CDBCFile readFile(0);
  CfgBossFirstKilled stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
  const CDBCFile::FIELD *v1;
  BossKilledReward *v2;
  BossKilledReward *v3;
  CDBCFile readFile(0);
  BossKilledReward stu;
  int32_t BossId;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        /* std::vector<MemChrBag>::vector(&stu.Rewars); */
        stu.nType = readFile.Search_Posistion( i, nIndex++)->iValue;
        BossId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.Rewars = __x;
        
        ++nIndex;
        v2 = std::map<signed char,BossKilledReward>::operator[](&this->m_BossKilledRewardMap, &stu.nType);
        std::list<int>::push_back(&v2->BossList, &BossId);
        v3 = std::map<signed char,BossKilledReward>::operator[](&this->m_BossKilledRewardMap, &stu.nType);
        std::vector<MemChrBag>::operator=(&v3->Rewars, &stu.Rewars);

      }
    }
  }
}

//#####################################
BossKilledReward *CfgData::GetBossKilledReward(int32_t BossId)
{
	auto it = m_BossKilledRewardMap.find(BossId);
	if (it != m_BossKilledRewardMap.end())
		return &it->second;
	return NULL;
}

void CfgData::InitBuyGiftTable()
{
  const CDBCFile::FIELD *v1;
  CfgBuyGift *v2;
  CDBCFile readFile(0);
  CfgBuyGift stu;
  std::string items;
  MemChrBagVector __x;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nGold = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        items = v1->pString;
        
        ++nIndex;
        nIndex += 3;
        stu.nBroad = readFile.Search_Posistion( i, nIndex++)->iValue;
        CItemHelper::parseItemVectorString(&__x, &items);
        stu.vGift = __x;
        v2 = std::map<int,CfgBuyGift>::operator[](&this->m_cfgBuyGiftTable, &stu.nIndex);
        CfgBuyGift::operator=(v2, &stu);

      }
    }
  }
}

const CfgBuyGift* CfgData::GetBuyGift( int32_t nIndex ) const
{
	std::map<int32_t, CfgBuyGift>::const_iterator it = m_cfgBuyGiftTable.find( nIndex );
	if ( it != m_cfgBuyGiftTable.end() )
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitCampWarContKillTable()
{
  CDBCFile readFile(0);
  CfgCampWarContKill contKill;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        m_cfgCampWarTable.AddContKill(contKill);
      }
    }
  }
}

//#####################################
void CfgData::InitCampWarRewardTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile readFile(0);
  CfgCampWarReward reward;
  std::string failItem;
  std::string winItem;
  MemChrBagVector __x;
  MemChrBagVector v10;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        winItem = v1->pString;
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        failItem = v2->pString;
        
        ++nIndex;
        CItemHelper::parseItemVectorString(&__x, &failItem);
        reward.FailItems = __x;
        CItemHelper::parseItemVectorString(&v10, &winItem);
        reward.WinItems = v10;
        m_cfgCampWarTable.AddReward(reward);

      }
    }
  }
}

//#####################################
void CfgData::InitCarrierAttrTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgCarrierAttr stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.vAttr = __x;
        
        ++nIndex;
        m_cfgCarrierTable.AddCarrierAttr(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitCarrierTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgCarrier stu;
  std::list<int> __x;
  int32_t size[3];
  std::string path;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        std::string size("./ServerConfig/Tables/Carrier.txt");
        
        v1 = readFile.Search_Posistion( i, nIndex);
        path = v1->pString;
        parseInt32List(&__x, this, &path, (int32_t)size);
        stu.lSkills = __x;
        
        ++nIndex;
        m_cfgCarrierTable.AddCarrier(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitChargeDungeon()
{
  ChargeDungeonCfg *v1;
  CDBCFile readFile(0);
  ChargeDungeonCfg stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
	int32_t KaiFuDay = CFG_DATA.getServerDiffDay(SVT_NORMAL) + 1;
	auto it = m_ChargeDungeonCfgMap.find(nId);
	if (it != m_ChargeDungeonCfgMap.end())
	{
		if (it->second.nMinKaiFuDay <= KaiFuDay && it->second.nMaxKaiFuDay >= KaiFuDay
			&& it->second.nChargeValue <= Todaycharge)
			return it->second.nDungeonId;
	}
	return 0;
}

//#####################################
void CfgData::InitChouJiangTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  int v3; // ebx
  int v4; // ebx
  const CDBCFile::FIELD *v5;
  const CDBCFile::FIELD *v6;
  const CDBCFile::FIELD *v7;
  MemChrBag v9;

  CDBCFile readFile(0);
  ChouJiangCfg stu;
  ChouJiangLuckyCfg stu_0;
  std::string strItem;
  MemChrBagVector __x;
  std::string strItems;
  ChouJiangWeekReward p_stu;
  std::string v20;
  std::string v22;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;
  int32_t iBaseTableCount_1;
  int32_t iBaseColumnCount_1;
  int32_t i_1;
  int32_t nIndex_1;
  int32_t iBaseTableCount_2;
  int32_t iBaseColumnCount_2;
  int32_t i_2;
  int32_t nIndex_2;
  ItemData v44; // 0:kr00_12.12

  
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
        strItem = v2->pString;
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
        ChouJiangTable::AddChouJiangCfg(&m_ChouJiangTable, stu);
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
          memset(&stu_0.MaxLucky, 0, sizeof(int64_t));
          stu_0.MaxQuality = 0;
          nIndex_0 = 1;
          stu_0.MaxLucky = readFile.Search_Posistion( i_0, 1)->iValue;
          stu_0.MinQuality = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.MaxQuality = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          ChouJiangTable::AddChouJiangLuckyCfg(&m_ChouJiangTable, stu_0);
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
            strItems = v5->pString;
            CItemHelper::parseItemVectorString(&__x, &strItems);
            stu.Item = &__x;
            
            ++nIndex_1;
            ChouJiangWeekReward::ChouJiangWeekReward(&p_stu, (const ChouJiangWeekReward *const)&stu);
            ChouJiangTable::AddChouJiangWeekReward(&m_ChouJiangTable, &p_stu);

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
              v20 = v6->pString;
              v44 = CItemHelper::parseItemDataString(&v20);
              v8 = v44.m_nId;
              BYTE4(v8) = v44.m_nClass;
              *(_QWORD *)(&stu.Index + 1) = v8;
              *(_DWORD *)&stu.Item.itemClass = v44.m_nCount;
              
              stu.Item.itemCount = readFile.Search_Posistion( i_2, ++nIndex_2)->iValue;
              ++nIndex_2;
              
              v7 = readFile.Search_Posistion( i_2, nIndex_2);
              v22 = v7->pString;
              CItemHelper::parseItemString(&v9, &v22);
              *(MemChrBag *)&stu.Item.endTime = v9;
              
              ++nIndex_2;
              ChouJiangTable::AddChouJiangCost(&m_ChouJiangTable, *(ChouJiangCost *)&stu.Index);
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  ChristmasDuiHuan *v5;
  CDBCFile readFile(0);
  ChristmasDuiHuan stu;
  MemChrBagVector __x;
  std::string strItems;
  std::list<ItemData> v11;
  std::string p_StringTime;
  std::string v16;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nIndx = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.Items = __x;
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string bCombi(v2->pString);
        CItemHelper::parseItemDataListString(&v11, (bool)bCombi);
        stu.CostItems = v11;
        
        stu.nLimitCount = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        p_StringTime = v3->pString;
        stu.nStartTime = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v4 = readFile.Search_Posistion( i, nIndex);
        v16 = v4->pString;
        stu.nEndTime = Answer::DayTime::StringToIntTime(v16);
        
        ++nIndex;
        v5 = std::map<int,ChristmasDuiHuan>::operator[](&this->m_ChristmasDuiHuanMap, &stu.nIndx);
        ChristmasDuiHuan::operator=(v5, &stu);

      }
    }
  }
}

//#####################################
ChristmasDuiHuan *CfgData::GetChristmasDuiHuanCfg(int32_t nId)
{
	auto it = m_ChristmasDuiHuanMap.find(nId);
	if (it != m_ChristmasDuiHuanMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitCityWarContRewardTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgCityWarContReward stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vBreakReward = __x;
        
        stu.nBreakMailId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        m_cfgCityWarTable.AddContReward(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitCrossTowerCfgMap()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CrossTowerCfg *v3;
  CDBCFile TabFile(0);
  CrossTowerCfg stu;
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v9;
  std::string v10;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.RewardVt = __x;
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v10 = v2->pString;
        CItemHelper::parseItemVectorString(&v9, &v10);
        stu.TopRewardVt = v9;
        
        stu.MailId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,CrossTowerCfg>::operator[](&this->m_CrossTowerCfgMap, &stu.MapId);
        CrossTowerCfg::operator=(v3, &stu);

      }
    }
  }
}

//#####################################
CrossTowerCfg *CfgData::GetCrossTowerCfg(int32_t MapId)
{
	auto it = m_CrossTowerCfgMap.find(MapId);
	if (it != m_CrossTowerCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitCycleTowerTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  CDBCFile TabFile(0);
  CycleTowerCost stu_0;
  CycleTowerMapCfg stu;
  std::string strItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t MapId;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;
  int32_t Times;
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
          strItem = v2->pString;
          v21 = CItemHelper::parseItemDataString(&strItem);
          v3 = v21.m_nId;
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
DamnationCfg *CfgData::GetDamnationCfg(int32_t Level)
{
	auto it = m_DamnationCfgTable.find(Level);
	if (it != m_DamnationCfgTable.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitDiligenceCfgMap()
{
  const CDBCFile::FIELD *v1;
  DiligenceCfg *v2;
  CDBCFile TabFile(0);
  DiligenceCfg stu;
  std::list<RateItem> strItems;
  _BYTE v6[14];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nValues = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string v6(v1->pString);
        CItemHelper::parseRateItemDataListString(&strItems);
        stu.lItems = strItems;
        
        ++nIndex;
        v2 = std::map<int,DiligenceCfg>::operator[](&this->m_DiligenceCfgMap, &stu.nId);
        DiligenceCfg::operator=(v2, &stu);

      }
    }
  }
}

//#####################################
DiligenceCfg *CfgData::GetDiligenceCfg(int32_t nType)
{
	auto it = m_DiligenceCfgMap.find(nType);
	if (it != m_DiligenceCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitDrawTable()
{
  CDBCFile readFile(0);
  CfgDrawReward stu;
  MemChrBag item;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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

      }
    }
  }
}

//#####################################
void CfgData::InitDropRecordTable()
{
  CfgDropRecord *v1;
  CDBCFile TabFile(0);
  CfgDropRecord record;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        memset(&record.nIndex, 0, sizeof(int64_t));
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

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgDropRecord> > iter;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgDropRecord> > __x;

  auto iter = m_cfgDropRecordTable.find(nIndexa);
  auto __x = m_cfgDropRecordTable.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgDropRecord>>::operator!=(&iter, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,CfgDropRecord>>::operator->(&iter)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitDuiHuanLimitTable()
{
  DuiHuanLimit *v1;
  CDBCFile TabFile(0);
  int32_t MaxLevel;
  DuiHuanLimit stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        memset(&stu.ShengYaoBi, 0, sizeof(int64_t));
        memset(&stu.ConstCurrency, 0, sizeof(int64_t));
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
	auto it = m_DuiHuanLimit.find(Level);
	if (it != m_DuiHuanLimit.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitDungeonScoreTable()
{
  const CDBCFile::FIELD *v1;
  MemChrBag v2;

  CDBCFile TabFile(0);
  CfgDungeonScore score;
  std::string strItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItem = v1->pString;
        CItemHelper::parseItemString(&v2, &strItem);
        score.Item = v2;
        
        ++nIndex;
        CfgDungeonScoreTable::AddDungeonScore(&m_cfgDungeonScoreTable, &score);
      }
    }
  }
}

//#####################################
void CfgData::InitDungeonSummon()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CfgDungeonSummon *v3;
  CDBCFile DungeonTrapFile(0);
  CfgDungeonSummon stu;
  std::list<int> __x;
  int32_t size[3];
  std::string path;
  std::string strItem;
  std::pair<int,int> __k;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
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
        stu.nDungeon = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nIndex = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nGold = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLimit = DungeonTrapFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string size("./ServerConfig/Tables/cfg_dungeon_summon.txt");
        
        v1 = DungeonTrapFile.Search_Posistion( i, nIndex);
        path = v1->pString;
        parseInt32List(&__x, this, &path, (int32_t)size);
        stu.lMonsters = __x;
        
        ++nIndex;
        
        v2 = DungeonTrapFile.Search_Posistion( i, nIndex);
        strItem = v2->pString;
        v20 = CItemHelper::parseItemDataString(&strItem);
        v4 = v20.m_nId;
        BYTE4(v4) = v20.m_nClass;
        *(_QWORD *)&stu.ConstItem.m_nId = v4;
        stu.ConstItem.m_nCount = v20.m_nCount;
        
        stu.FreeCount = DungeonTrapFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        __k = std::make_pair<int,int>(stu.nDungeon, stu.nIndex);
        v3 = std::map<std::pair<int,int>,CfgDungeonSummon>::operator[](&this->m_cfgDungeonSummon, &__k);
        CfgDungeonSummon::operator=(v3, &stu);

      }
    }
  }
}

//#####################################
const CfgDungeonSummon *CfgData::GetDungeonSummon(int32_t nDungeon, int32_t nIndex)
{
	auto it = m_cfgDungeonSummon.find(std::make_pair(nDungeon, nIndex));
	if (it != m_cfgDungeonSummon.end())
		return &it->second;
	return NULL;
}

//#####################################

//#####################################
int32_t CfgData::GetEquipBackTaskId(int32_t PlayerLevel, int32_t Times)
{
	auto it = m_EquipBackTaskRate.lower_bound(PlayerLevel);
	if (it != m_EquipBackTaskRate.end())
	{
		auto pIt = it->second.find(Times);
		if (pIt != it->second.end() && !pIt->second.empty())
			return pIt->second.front().nValue;
	}
	return 0;
}

//#####################################
BackEquipTask *CfgData::GetBackEquipTask(int32_t Index)
{
	auto it = m_BackEquipTaskMap.find(Index);
	if (it != m_BackEquipTaskMap.end())
		return &it->second;
	return NULL;
}

//#####################################

//#####################################

//#####################################
void CfgData::InitEquipDecomposeTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgEquipDecompose stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        nIndex = 0;
        stu.m_nClass = readFile.Search_Posistion( i, 0)->iValue;
        stu.m_nId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.m_vGiveItems = __x;
        
        stu.m_nCostMoney = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.m_nLimitType = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.m_nLimitValue = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 2;
        stu.m_NpcId = readFile.Search_Posistion( i, nIndex++)->iValue;
        m_cfgEquip.AddEquipDecompose(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitEquipPosSuitTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgEquipPosSuit stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        nIndex = 1;
        stu.m_nLevel = readFile.Search_Posistion( i, 1)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/EquipPosSuit.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.m_vAttrAddon = __x;
        
        ++nIndex;
        m_cfgEquip.AddEquipPosSuit(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitEquipUpPhase()
{
  const CDBCFile::FIELD *v1;
  CDBCFile TabFile(0);
  cfgEquipUpPhase stu;
  std::list<ItemData> strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        stu.m_CostEquip = TabFile.Search_Posistion( i, 0)->iValue;
        
        v1 = TabFile.Search_Posistion( i, 1);
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&strItems, (bool)bCombi);
        stu.m_CostItems = strItems;
        
        stu.m_CostMoney = TabFile.Search_Posistion( i, 2)->iValue;
        stu.m_GiveEquip = TabFile.Search_Posistion( i, 3)->iValue;
        stu.m_GongGaoId = TabFile.Search_Posistion( i, 4)->iValue;
        m_cfgEquipUpPhaseTable.AddData(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitExchangeTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile readFile(0);
  CfgExchange stu;
  std::string rewards;
  std::string items;
  std::list<ItemData> strItems;
  MemChrBagVector __x;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        items = v1->pString;
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        rewards = v2->pString;
        
        stu.nLimit = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CItemHelper::parseItemDataListString(&strItems, (bool)&items);
        stu.vCost = strItems;
        CItemHelper::parseItemVectorString(&__x, &rewards);
        stu.vReward = __x;
        CfgExchangeTable::Add(&this->m_cfgExchangeTable, &stu);

      }
    }
  }
}

//#####################################
void CfgData::InitFamilyDonateTable()
{
  ContributionCfg *v1;
  CDBCFile TabFile(0);
  ContributionCfg stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
	auto it = m_FamilyDonateMap.find(nId);
	if (it != m_FamilyDonateMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitFamilyDungeonTable()
{
  CDBCFile TabFile(0);
  CfgFamilyDungeon stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        m_cfgFamilyDungeonTable.AddDungeon(stu);
      }
    }
  }
}


//#####################################
void CfgData::fetchBuff()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CfgBuff *v3;
  CDBCFile BuffFile(0);
  CfgBuff buff;
  BuffAttrVector __x;
  std::string str;
  std::string v9;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        str = v1->pString;
        CfgData::paraseBuffAttr(&__x, this, &str);
        buff.buffAttr = __x;
        
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
        v9 = v2->pString;
        buff.angry = CfgData::paraseParam2(this, &v9);
        
        buff.battle = BuffFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v3 = std::map<int,CfgBuff>::operator[](&this->m_buffs, &buff.id);
        CfgBuff::operator=(v3, &buff);

      }
    }
  }
}

//#####################################
BuffAttrVector *CfgData::paraseBuffAttr(const std::string *const str)
{
  std::string *v3;
  std::string *v4;
  const char *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  BuffAttr stu;
  StringVector vBuff;
  StringVector vstr;
  std::string delims;
  std::string v17;
  int32_t nSize;
  int32_t i;

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
          memset(&stu.attr, 0, sizeof(int64_t));
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
      }
    }
  }
  return retstr;
}

//#####################################
CurrencyList CfgData::paraseCurrency(const std::string *const str)
{
  const std::string *v2;
  std::string *v3;
  const char *v4;
  std::string *v5;
  const char *v6;
  CurrencyList result;
  const std::string *stra;
  CurrencyStu stu;
  StringVector vstr;
  std::string delims;
  _BYTE v12[33];

  
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
    std::list<CurrencyStu>::push_back(this, &stu);
  }
  return result;
}

//#####################################
Int32Vector *CfgData::paraseInt32Vector2(const std::string *const str,
        const std::string *const path,
        int32_t size)
{
  const char *v7;
  const char *v8;
  size_t v9;
  std::string *v10;
  const char *v11;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vstr;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x[9];

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
  }
  return retstr;
}

//#####################################
Int32Vector *CfgData::paraseInt32Vector(const std::string *const str,
        const std::string *const path,
        int32_t size)
{
  const char *v7;
  const char *v8;
  size_t v9;
  std::string *v10;
  const char *v11;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vstr;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x[9];

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
  }
  return retstr;
}

//#####################################
Int32List parseInt32List(const std::string *const str, int32_t size)
{
  int32_t v3; // ecx
  Int32List result;
  std::string *v7;
  const char *v8;

  const std::string *stra;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vstr;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x[9];

  stra = *(const std::string **)&size;
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
        std::list<int>::push_back(this, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
    }
  }
  return result;
}

//#####################################
Int32List parseInt32List(const std::string *const str,
        const std::string *const path,
        int32_t size)
{
  int32_t v4; // r8d
  Int32List result;
  const char *v8;
  const char *v9;
  std::string *v10;
  const char *v11;

  std::string *patha;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vstr;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x[9];

  patha = *(std::string **)&size;
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
        "parseInt32List() check size err from %s, where size = %d, str = %s\n",
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
        std::list<int>::push_back(this, __x);
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
      }
    }
  }
  return result;
}

//#####################################
Int32VtVector *CfgData::paraseInt32VtVector(const std::string *const str,
        const std::string *const path)
{
  size_t v5;
  const std::string *v6;
  size_t v7;
  std::string *v8;
  const char *v9;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vstr;
  Int32Vector probability;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin;
  StringVector SplitStr;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v20;
  std::string v21;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v23;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x[9];

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
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
    }
  }
  return retstr;
}

//#####################################
Param2 CfgData::paraseParam2(const std::string *const str)
{
  Param2 v3;
  std::string *v4;
  const char *v5;
  int32_t v6; // ebx
  std::string *v7;
  const char *v8;
  int32_t v9; // eax
  StringVector vParam;
  Param2 v11;
  std::string delims;
  Param2 v14;
  Param2 v15;

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
  }
  return v3;
}

//#####################################
Param2List CfgData::paraseParam2List(const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v4;
  Param2List result;
  std::string *v7;
  std::string *v8;
  const char *v9;
  int32_t v10; // r12d
  std::string *v11;
  const char *v12;
  int32_t v13; // eax
  const char *v14;
  const char *v15;
  std::string *patha;

  std::string *stra;
  StringVector vParam;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter;
  StringVector strParams;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v25;
  Param2 __x;

  stra = *(std::string **)&nIndex;
  nIndexa = (int)path;
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
        std::list<Param2>::push_back(this, &__x);
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
    }
  }
  return result;
}

//#####################################
void CfgData::fetchDungeon()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  const CDBCFile::FIELD *v5;
  const CDBCFile::FIELD *v6;
  const CDBCFile::FIELD *v7;
  CfgDungeon *v8;
  CfgDungeon *v9;
  CfgDungeonReward *v10;
  CfgDungeonDropGroup *v11;
  CfgDungeon dungeon;
  CDBCFile DungeonDropFile(0);
  CDBCFile DungeonRewardFile(0);
  CDBCFile DungeonFile(0);
  int32_t id;
  CfgDungeonDrop group;
  CfgDungeonReward reward;
  std::string strItem;
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v25;
  std::string v26;
  Int32Vector v28;
  std::string path;
  std::string str;
  MemChrBagVector v33;
  std::string v34;
  Int32Vector v36;
  std::string v37;
  std::string v39;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t nIndex;
  int32_t iBaseTableCount_Reward;
  int32_t iBaseColumnCount_Reward;
  int32_t iBaseTableCount_Drop;
  int32_t iBaseColumnCount_Drop;
  int32_t i;
  int32_t weekday;
  int32_t i_0;
  int32_t i_1;
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
        strItem = v2->pString;
        v55 = CItemHelper::parseItemDataString(&strItem);
        v12 = v55.m_nId;
        BYTE4(v12) = v55.m_nClass;
        *(_QWORD *)&dungeon.costItem.m_nId = v12;
        dungeon.costItem.m_nCount = v55.m_nCount;
        
        ++nIndex;
        
        v3 = DungeonFile.Search_Posistion( i, nIndex);
        strItems = v3->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        dungeon.rewardItem = __x;
        
        ++nIndex;
        
        v4 = DungeonFile.Search_Posistion( i, nIndex);
        v26 = v4->pString;
        CItemHelper::parseItemVectorString(&v25, &v26);
        dungeon.rewardOnce = v25;
        
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
        str = v5->pString;
        CfgData::paraseInt32Vector(&v28, this, &str, &path, 0);
        dungeon.win_star = v28;
        
        ++nIndex;
        
        v6 = DungeonFile.Search_Posistion( i, nIndex);
        v34 = v6->pString;
        CItemHelper::parseItemVectorString(&v33, &v34);
        dungeon.star_reward = v33;
        
        ++nIndex;
        
        v37 = "./ServerConfig/Tables/cfg_dungeon.txt";
        
        v7 = DungeonFile.Search_Posistion( i, nIndex);
        v39 = v7->pString;
        CfgData::paraseInt32Vector(&v36, this, &v39, &v37, 0);
        dungeon.star_ratio = v36;
        
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  std::string *v4;
  const char *v5;
  std::list<CfgMapEvent> *v6;
  CDBCFile DungeonEventFile(0);
  CfgMapEvent dungeonEvent;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector strTriggerParam;
  std::string triggerParam;
  std::string delims;
  std::string str;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        dungeonEvent.id = DungeonEventFile.Search_Posistion( i, 0)->iValue;
        dungeonEvent.trigger_id = DungeonEventFile.Search_Posistion( i, 1)->iValue;
        dungeonEvent.bInitOpen = DungeonEventFile.Search_Posistion( i, 2)->iValue == 0;
        dungeonEvent.trigger_type = DungeonEventFile.Search_Posistion( i, 3)->iValue;
        
        v1 = DungeonEventFile.Search_Posistion( i, 4);
        triggerParam = v1->pString;
        
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

      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonMonster()
{
  unsigned int id; // r12d
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  std::string *v5;
  std::string *v6;
  const char *v7;
  int32_t v8; // ebx
  std::string *v9;
  const char *v10;
  int32_t v11; // eax
  size_t v12;
  std::string *v13;
  std::string *v14;
  const char *v15;
  int32_t v16; // ebx
  std::string *v17;
  const char *v18;
  int32_t v19; // eax
  size_t v20;
  CfgDungeonMonster *v21;
  CDBCFile DungeonMonsterFile(0);
  CfgDungeonMonster monster;
  StringVector vPos_0;
  StringVector vRandPos;
  StringVector vPos;
  StringVector vRoad;
  std::string randpos;
  std::string road;
  std::list<Param2> __x;
  _BYTE v31[15];
  int32_t nIndex[3];
  std::string delims;
  std::string v39;
  Position v41;
  std::string v42;
  std::string v44;
  Position v46;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  uint32_t j;
  uint32_t j_0;

  
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
        monster.id = DungeonMonsterFile.Search_Posistion( i, 0)->iValue;
        monster.wave = DungeonMonsterFile.Search_Posistion( i, 1)->iValue;
        
        std::string v31("./ServerConfig/Tables/cfg_dungeon_monster.txt");
        id = monster.id;
        
        v2 = DungeonMonsterFile.Search_Posistion( i, 2);
        std::string nIndex(v2->pString);
        CfgData::paraseParam2List(
          &__x,
          this,
          (int32_t)nIndex,
          id);
        monster.mids = __x;
        
        monster.x = DungeonMonsterFile.Search_Posistion( i, 3)->iValue;
        monster.y = DungeonMonsterFile.Search_Posistion( i, 4)->iValue;
        monster.count = DungeonMonsterFile.Search_Posistion( i, 5)->iValue;
        monster.side = DungeonMonsterFile.Search_Posistion( i, 6)->iValue;
        
        v3 = DungeonMonsterFile.Search_Posistion( i, 7);
        road = v3->pString;
        
        monster.delay = DungeonMonsterFile.Search_Posistion( i, 8)->iValue;
        monster.times = DungeonMonsterFile.Search_Posistion( i, 9)->iValue;
        monster.money = DungeonMonsterFile.Search_Posistion( i, 10)->iValue;
        monster.life = DungeonMonsterFile.Search_Posistion( i, 11)->iValue;
        
        v4 = DungeonMonsterFile.Search_Posistion( i, 12);
        randpos = v4->pString;
        
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
              &monster.road.push_back(&v41);
            }
          }
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
          }
        }
        v21 = std::map<int,CfgDungeonMonster>::operator[](&this->m_dungeonMonsters, &monster.id);
        CfgDungeonMonster::operator=(v21, &monster);

      }
    }
  }
}

//#####################################
void CfgData::fetchDungeonPlant()
{
  CfgDungeonPlant *v1;
  CDBCFile DungeonPlantFile(0);
  CfgDungeonPlant dungeonPlant;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  CfgDungeonTrap *v1;
  CDBCFile DungeonTrapFile(0);
  CfgDungeonTrap dungeonTrap;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  CfgDungeonNpc *v1;
  CDBCFile DungeonTrapFile(0);
  CfgDungeonNpc dungeonNpc;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  CfgChrShop *v1;
  CDBCFile ChrShopFile(0);
  CfgChrShop chrShop;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  CDBCFile readFile(0);
  FamilyMedal Medal;
  std::list<AddAttribute> __x;
  _BYTE v7[15];
  int32_t v9[3];
  std::list<AddAttribute> v11;
  _BYTE v12[15];
  int32_t v14[2];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;

  
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
        Medal.nLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        Medal.nNeedFamilyLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        Medal.nNeedFamilyExp = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string v7("./ServerConfig/Tables/FamilyBadge.txt");
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string v9(v2->pString);
        CfgData::parseAddAttribues(
          &__x,
          this,
          (int32_t)v9,
          (unsigned int)nIndex);
        Medal.lAttrList = __x;
        
        Medal.nGongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        Medal.DefRdc = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        m_cfgFamilyTable.AddFamilyMedal(Medal);

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
          Medal.nLevel = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          Medal.nNeedFamilyLevel = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          Medal.nNeedFamilyExp = readFile.Search_Posistion( i_0, nIndex_0++)->iValue;
          nIndex_0 += 2;
          
          std::string v12("./ServerConfig/Tables/FamilyBadge.txt");
          
          v3 = readFile.Search_Posistion( i_0, nIndex_0);
          std::string v14(v3->pString);
          CfgData::parseAddAttribues(
            &v11,
            this,
            (int32_t)v14,
            (unsigned int)nIndex_0);
          Medal.lAttrList = v11;
          
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
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgFamilySkill stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nFamilyLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCostValue = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        path = "./ServerConfig/Tables/FamilySkill.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.vAttrAddon = __x;
        
        stu.nCostMoney = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.PlayerLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        m_cfgSkillTable.AddFamilySkill(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitFlopTable()
{
  const CDBCFile::FIELD *v1;
  FlopDrawCfg *v2;
  MemChrBag v3;

  CDBCFile readFile(0);
  FlopDrawCfg stu;
  std::string strItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItem = v1->pString;
        CItemHelper::parseItemString(&v3, &strItem);
        stu.m_Item = v3;
        
        stu.m_nRate = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.m_GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,FlopDrawCfg>::operator[](&m_FlopDrawCfgMap, &stu.m_nId);
        *v2 = stu;
      }
    }
  }
}

//#####################################
void CfgData::InitFunctionOpenMailMap()
{
  FunctionOpenMail *v1;
  CDBCFile readFile(0);
  int32_t nId;
  FunctionOpenMail stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
	auto it = m_FunctionOpenMailMap.find(nId);
	if (it != m_FunctionOpenMailMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitGemOpenHoleTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgGemOpenHole stu;
  std::list<ItemData> strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.m_nSlot = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.m_nCostMoney = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&strItems, (bool)bCombi);
        stu.m_lCostItem = strItems;
        
        ++nIndex;
        m_cfgItemGem.AddGemOpenHole(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitGemSuitTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgGemSuit stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.m_vAttrAddon = __x;
        
        ++nIndex;
        m_cfgItemGem.AddGemSuit(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitGoblinData()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile TabFile(0);
  cfgGoblinData stu;
  std::string path;
  std::string str;
  std::vector<Position> __x;
  std::string strPos;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        str = v1->pString;
        CfgData::parseCurrentDatas(this, &stu.m_RefreshMonsters, &str, i, &path);
        
        stu.m_mapId = TabFile.Search_Posistion( i, 3)->iValue;
        
        v2 = TabFile.Search_Posistion( i, 4);
        strPos = v2->pString;
        CfgData::paresPosition(&__x, this, &strPos);
        stu.m_RevivePosVector = __x;
        
        cfgGoblinTableData::Add(&this->m_cfgGoblinTableData, &stu);

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
  std::string *v6;
  CurrentData current;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector strMonsters;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;

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
  }
}

//#####################################
void CfgData::parseCurrentData(CurrentData *const current,
        const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  const char *v10;
  const char *v11;
  StringVector strCurrent;
  std::string delims;
  _BYTE v17[17];

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
  }
}

//#####################################
void CfgData::InitGoblinTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  std::list<AddAttribute> *v3;
  CDBCFile TabFile(0);
  AddAttrList AddAttrs;
  int32_t nId;
  GoblinCfg stu;
  auto v8
  _BYTE v9[32];

  _BYTE v11[15];
  int32_t v13[4];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nType;
  int32_t nLevel;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;

  
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
        memset(&stu.UpAttr, 0, sizeof(int64_t));
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
          
          std::string v11("./ServerConfig/Tables/GoblinSuit.txt");
          
          v2 = TabFile.Search_Posistion( i_0, nIndex_0);
          std::string v13(v2->pString);
          CfgData::parseAddAttribues(
            &AddAttrs,
            this,
            (int32_t)v13,
            (unsigned int)nIndex_0);
          
          ++nIndex_0;
          v3 = std::map<int,std::list<AddAttribute>>::operator[](&this->m_GoblinSuitMap, &nId);
          std::list<AddAttribute>::operator=(v3, &AddAttrs);
        }
      }
    }
  }
}

//#####################################
#if 0 // replaced by hand-written version at end of file
GoblinCfg *CfgData::GetGoblinCfg(int32_t nType, int32_t nLevel)
{
	auto it = m_GoblinCfgMap.find(std::make_pair(nType, nLevel));
	if (it != m_GoblinCfgMap.end())
		return &it->second;
	return NULL;
}
#endif

//#####################################
AddAttrList CfgData::GetGoblinSuitAttr(int32_t nId)
{
	AddAttrList result;
	auto it = m_GoblinSuitMap.find(nId);
	if (it != m_GoblinSuitMap.end())
		result = it->second;
	return result;
}

//#####################################

//#####################################
void CfgData::InitGongMinTable()
{
  const CDBCFile::FIELD *v1;
  GongMingCfg *v2;
  CDBCFile readFile(0);
  GongMingCfg stu;
  std::list<AddAttribute> __x;
  _BYTE v6[15];
  int32_t v8[3];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        
        std::string v6("./ServerConfig/Tables/GongMing.txt");
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string v8(v1->pString);
        CfgData::parseAddAttribues(
          &__x,
          this,
          (int32_t)v8,
          (unsigned int)nIndex);
        stu.lAttrList = __x;
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,GongMingCfg>::operator[](&this->m_GongMingCfgMap, &stu.nIndex);
        GongMingCfg::operator=(v2, &stu);

      }
    }
  }
}

//#####################################
GongMingCfg *CfgData::GetGongMingCfg(int32_t GongMinLevel)
{
	auto it = m_GongMingMap.find(GongMinLevel);
	if (it != m_GongMingMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitGroupIconTable()
{
  const CDBCFile::FIELD *v1;
  CfgGroupIcon *v2;
  CDBCFile readFile(0);
  CfgGroupIcon icon;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        memset(&icon.nId, 0, sizeof(int64_t));
        icon.platfrom._M_dataplus._M_p = 0;
        std::string::string(&icon.platfrom);
        icon.nId = readFile.Search_Posistion( i, 0)->iValue;
        icon.bShowInCross = readFile.Search_Posistion( i, 18)->iValue;
        v1 = readFile.Search_Posistion( i, 19);
        std::string::operator=(&icon.platfrom, v1->pString);
        v2 = std::map<int,CfgGroupIcon>::operator[](&this->m_cfgGroupIcons, &icon.nId);
        CfgGroupIcon::operator=(v2, &icon);

      }
    }
  }
}

//#####################################
bool CfgData::IsShowIcon(int32_t nIconId, const std::string *const platform)
{
  GameService *v4;
  bool v6; // al

  std::_Rb_tree_const_iterator<std::pair<const int,CfgGroupIcon> > iter;
  std::map<int, CfgGroupIcon>::iterator __it;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgGroupIcon> > __x;
  std::map<int, CfgGroupIcon>::iterator v13;
  const CfgGroupIcon *icon;

  auto __it = m_cfgGroupIcons.find(nIconIda);
  std::_Rb_tree_const_iterator<std::pair<int const,CfgGroupIcon>>::_Rb_tree_const_iterator(&iter, &__it);
  auto v13 = m_cfgGroupIcons.end();
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
  const CDBCFile::FIELD *v1;
  std::vector<GroupMonster> *v2;
  CDBCFile InitBossFile(0);
  GroupMonster stu;
  int32_t MapId;
  std::vector<Position> __x;
  std::string strPos;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        strPos = v1->pString;
        CfgData::paresPosition(&__x, this, &strPos);
        stu.RevivePos = __x;
        
        v2 = std::map<int,std::vector<GroupMonster>>::operator[](&this->m_GroupMonsterMap, &MapId);
        std::vector<GroupMonster>::push_back(v2, &stu);

      }
    }
  }
}

//#####################################
GroupMonsterVector *CfgData::GetGroupMonsterVector(int32_t MapId)
{
	auto it = m_GroupMonsterMap.find(MapId);
	if (it != m_GroupMonsterMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitGuWuCfgMap()
{
  GuWuCfg *v1;
  CDBCFile readFile(0);
  GuWuCfg stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
	auto it = m_GuWuCfgMap.find(Level);
	if (it != m_GuWuCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
GuiGuDaoRenCfg *CfgData::GetGuiGuDaoRenCfg(int32_t NpcId)
{
	auto it = m_GuiGuDaoRenCfgMap.find(NpcId);
	if (it != m_GuiGuDaoRenCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitHoeTable()
{
  HoeCfg *v1;
  CDBCFile readFile(0);
  HoeCfg Stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        memset(&Stu.nId, 0, sizeof(int64_t));
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
	auto it = m_HoeMap.find(nId);
	if (it != m_HoeMap.end())
		return &it->second;
	return NULL;
}

//#####################################
AttrAddonVector *CfgData::parseAttrAddon(const std::string *const addonAttr,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v6;
  std::string *v7;
  const char *v8;
  std::string *v9;
  const char *v10;
  const char *v11;
  const char *v12;
  AttrAddon attrAddon;
  StringVector strAttrAddon;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector strAttrAddons;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v24;
  _BYTE v25[33];

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
          "CfgData::parseAttrAddon() wrong data from %s, where index = %d, str = %s\n",
          v12,
          nIndex,
          v11);
      }
    }
  }
  return retstr;
}

//#####################################
TalentAddonList CfgData::paraseTalentAddon(const std::string *const str,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v4;
  TalentAddonList result;
  std::string *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  const char *v14;
  const char *v15;
  int v16; // r12d
  const char *v17;
  const char *v18;
  std::string *patha;

  std::string *stra;
  TalentAddon addon;
  StringVector strAddon;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector strAddons;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v29;
  _BYTE v30[33];

  stra = *(std::string **)&nIndex;
  nIndexa = (int)path;
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
        break;
      }
      
      v29.assign(":", v30);
      v7 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&strAddon, v7, &v29, 0);
      
      if ( std::vector<std::string>::size(&strAddon) == 3 )
      {
        memset(&addon.id, 0, sizeof(int64_t));
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
        std::list<TalentAddon>::push_back(this, &addon);
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
      if ( !v16 )
        goto LABEL_16;
    }
  }
  return result;
}

//#####################################
AddAttribute CfgData::parseAddAttribue(const std::string *const addonAttr,
        int32_t nIndex,
        const std::string *const path)
{
  AddAttribute v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  const char *v10;
  const char *v11;
  StringVector strAttrAddon;
  AddAttribute attribute;
  std::string delims;
  _BYTE v17[17];

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
      "CfgData::parseAttrAddon() wrong data from %s, where index = %d, str = %s\n",
      v11,
      nIndex,
      v10);
  }
  v5 = attribute;
  return v5;
}

//#####################################
AddAttrList CfgData::parseAddAttribues(const std::string *const addonAttr,
        int32_t nIndex,
        const std::string *const path)
{
  std::string *v4;
  AddAttrList result;
  std::string *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  const char *v12;
  const char *v13;
  std::string *patha;

  std::string *addonAttra;
  AddAttribute attr;
  StringVector strAttrAddon;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector strAttrAddons;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v24;
  _BYTE v25[33];

  addonAttra = *(std::string **)&nIndex;
  nIndexa = (int)path;
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
          std::list<AddAttribute>::push_back(this, &attr);
      }
      else
      {
        v12 = (const char *)std::string::c_str(addonAttra);
        v13 = (const char *)std::string::c_str(patha);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CfgData::parseAttrAddon() wrong data from %s, where index = %d, str = %s\n",
          v13,
          nIndexa,
          v12);
      }
    }
  }
  return result;
}

//#####################################
void CfgData::InitJewelPavilionTable()
{
  const CDBCFile::FIELD *v1;
  auto v2
  MemChrBag v3;

  CDBCFile TabFile(0);
  JewelPavilionCfg stu;
  std::string strItem;
  std::_Rb_tree_node_base::_Base_ptr M_node;
  bool second;
  _BYTE v11[64];

  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
      std::map<std::pair<int,int>,JewelPavilionCfg>::clear(&m_JewelPavilionCfgMap);
      for ( i = 0; i < iBaseTableCount; ++i )
      {
        nIndex = 0;
        memset(&stu, 0, sizeof(stu));
        stu.nDay = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nIndex = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItem = v1->pString;
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
               &m_JewelPavilionCfgMap,
               (const std::pair<const std::pair<int,int>,JewelPavilionCfg> *const)v11);

        v3.itemCount = *(_DWORD *)&v2.second;

        second = v2.second;
      }
    }
  }
}

//#####################################
JewelPavilionCfg *CfgData::GetJewelPavilionCfg(int32_t nDay, int32_t nIndex)
{
	auto it = m_JewelPavilionCfgMap.find(std::make_pair(nDay, nIndex));
	if (it != m_JewelPavilionCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitJueWeiTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgJueWei stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        stu.nNeedLevel = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nNeedViGour = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/JueWei.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.vAttr = __x;
        
        ++nIndex;
        m_cfgJueWeiTable.AddJueWei(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitLaDaShiHuiYuan()
{
  const CDBCFile::FIELD *v1;
  LuDaShiVip *v2;
  CDBCFile TabFile(0);
  LuDaShiVip stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.Rewards = __x;
        
        stu.nCondition = TabFile.Search_Posistion( i, 4)->iValue;
        stu.nVipType = TabFile.Search_Posistion( i, 8)->iValue;
        stu.nMaxCondition = TabFile.Search_Posistion( i, 11)->iValue;
        v2 = std::map<int,LuDaShiVip>::operator[](&this->m_LuDaShiVipMap, &stu.nIndex);
        LuDaShiVip::operator=(v2, &stu);

      }
    }
  }
}

//#####################################
LuDaShiVip *CfgData::GetLaDaShiHuiYuan(int32_t nIndex)
{
	auto it = m_LaDaShiVipMap.find(nIndex);
	if (it != m_LaDaShiVipMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitLevelChatTimesTable()
{
  int *v1;
  CDBCFile readFile(0);
  int32_t nLevel;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nTimes;

  
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

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,int> > iter;
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x;

  auto iter = m_cfgLevelChatTable.find(nLevela);
  auto __x = m_cfgLevelChatTable.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter)->second;
  else
    return -1;
}

//#####################################
void CfgData::InitLibraryTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  int v3; // ebx
  const CDBCFile::FIELD *v4;
  MemChrBag v6;

  CDBCFile readFile(0);
  CfgLibraryItem stu;
  CfgLibraryCost stu_1;
  CfgLibraryQuality stu_0;
  std::string strItem;
  std::string v14;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;
  int32_t iBaseTableCount_1;
  int32_t iBaseColumnCount_1;
  int32_t i_1;
  int32_t nIndex_1;
  ItemData v31; // 0:kr00_12.12

  
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
        strItem = v2->pString;
        CItemHelper::parseItemString(&v6, &strItem);
        stu.Item = v6;
        
        stu.Probability = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nDunGeonId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        CLibraryTable::AddCfgLibraryItem(&m_CLibraryTable, stu);
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
          memset(&stu_0.nIndex, 0, sizeof(int64_t));
          memset(&stu_0.nCount, 0, sizeof(int64_t));
          nIndex_0 = 0;
          stu_0.nIndex = readFile.Search_Posistion( i_0, 0)->iValue;
          stu_0.nQuality = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nCount = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          stu_0.nProbability = readFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          CLibraryTable::AddCfgLibraryQuality(&m_CLibraryTable, stu_0);
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
            v14 = v4->pString;
            v31 = CItemHelper::parseItemDataString(&v14);
            v5 = v31.m_nId;
            BYTE4(v5) = v31.m_nClass;
            *(_QWORD *)&stu_1.Item.m_nId = v5;
            stu_1.Item.m_nCount = v31.m_nCount;
            
            ++nIndex_1;
            CLibraryTable::AddCfgLibraryCost(&m_CLibraryTable, stu_1);
          }
        }
      }
    }
  }
}

//#####################################

//#####################################
void CfgData::InitLittleHelperCfg()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  LittleHelperCfg *v3;
  int v4; // ebx
  ShiQuCfg *v5;
  const CDBCFile::FIELD *v6;
  CDBCFile FileTable(0);
  LittleHelperCfg stu;
  ShiQuCfg stu_0;
  std::list<AddAttribute> __x;
  _BYTE v11[15];
  int32_t v13[3];
  MemChrBagVector v15;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;
  int32_t iBaseTableCount_1;
  int32_t iBaseColumnCount_1;
  int32_t i_1;
  int32_t nIndex_1;

  
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
        
        std::string v11("./ServerConfig/Tables/LittleHelper.txt");
        
        v2 = FileTable.Search_Posistion( i, nIndex);
        std::string v13(v2->pString);
        CfgData::parseAddAttribues(
          &__x,
          this,
          (int32_t)v13,
          (unsigned int)nIndex);
        stu.lAttr = __x;
        
        stu.nGold = FileTable.Search_Posistion( i, ++nIndex)->iValue;
        stu.nReGold = FileTable.Search_Posistion( i, ++nIndex)->iValue;
        stu.nTime = FileTable.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 5;
        stu.nGongGaoId = FileTable.Search_Posistion( i, nIndex++)->iValue;
        v3 = std::map<int,LittleHelperCfg>::operator[](&this->m_LittleHelperCfgMap, &stu.nId);
        LittleHelperCfg::operator=(v3, &stu);

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
            strItems = v6->pString;
            CItemHelper::parseItemVectorString(&v15, &strItems);
            std::vector<MemChrBag>::operator=(&this->m_ZeroBuyPetCfg.cItems, &v15);
            
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

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,ShiQuCfg> > it;
  std::_Rb_tree_const_iterator<std::pair<const int,ShiQuCfg> > __x;

  
  auto it = m_ShiQuCfgMap.find(nIda);
  auto __x = m_ShiQuCfgMap.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ShiQuCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,ShiQuCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const LittleHelperCfg *CfgData::GetLittleHelperCfg(int32_t nId)
{

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,LittleHelperCfg> > it;
  std::_Rb_tree_const_iterator<std::pair<const int,LittleHelperCfg> > __x;

  
  auto it = m_LittleHelperCfgMap.find(nIda);
  auto __x = m_LittleHelperCfgMap.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,LittleHelperCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,LittleHelperCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
void CfgData::InitLuckDropTable()
{
  const CDBCFile::FIELD *v1;
  std::string *v2;
  std::string *v3;
  const char *v4;
  std::string *v5;
  const char *v6;
  std::string *v7;
  const char *v8;
  std::string *v9;
  const char *v10;
  std::string *v11;
  const char *v12;
  CDBCFile readFile(0);
  SpecialItemDrop SpecialItem;
  LuckDrop stu;
  StringVector vstack;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector ItemVetcor;
  std::string ItemString;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v24;
  LuckDrop p_stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.Type = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.VipLevel = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        ItemString = v1->pString;
        
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
            &stu.ItemList.push_back(&SpecialItem);
          }
        }
        p_stu = stu;
        m_LuckDropTable.AddLuckDrop(p_stu);


      }
    }
  }
}

//#####################################
void CfgData::InitMYSJRewardTable()
{
  CCardGroupBoxManager *v1;
  CCardGroupBoxManager *v2;
  CDBCFile readFile(0);
  CfgMYSJReward stu;
  CardGroup card;
  CardGroupList cardList;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t nGroupId;
  int32_t nGroupIndex;
  int32_t i;
  int32_t nIndex;
  int32_t nId;

  
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
          &cardList.push_back(&card);
        }
        CfgMYSJRewardTable::Add(&this->m_cfgMYSJRewardTable, nId, &stu);
      }
      if ( nGroupId > 0 )
      {
        v2 = Answer::Singleton<CCardGroupBoxManager>::instance();
        CCardGroupBoxManager::Add(v2, nGroupId, &cardList);
      }
    }
  }
}

//#####################################
void CfgData::InitMaintainCompensateTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile readFile(0);
  CfgMaintainCompensate stu;
  std::string p_StringTime;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        p_StringTime = v1->pString;
        stu.nTime = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vItems = __x;
        
        ++nIndex;
        CfgMaintainCompensateTable::Add(&this->m_cfgMaintainCompensateTable, &stu);

      }
    }
  }
}

//#####################################
void CfgData::InitMapRoadTable()
{
  const CDBCFile::FIELD *v1;
  std::string *v2;
  std::string *v3;
  const char *v4;
  std::string *v5;
  const char *v6;
  CDBCFile readFile(0);
  CfgMapRoad stu;
  StringVector vPos;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter;
  StringVector vRoad;
  std::string strRoad;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v17;
  Position __x;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t x;
  int32_t y;

  
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
        stu.nIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nNextIndex = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nMapId = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strRoad = v1->pString;
        
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
            &stu.road.push_back(&__x);
          }
        }
        CfgMapRoadTable::Add(&this->m_cfgMapRoadTable, &stu);

      }
    }
  }
}

//#####################################

//#####################################
int32_t CfgData::GetMonsterReviveTime(int32_t Time, int32_t BossId)
{
  int32_t result; // eax
  CfgData *v4;

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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile TabFile(0);
  MiniClientCfg stu;
  MemChrBagVector __x;
  std::string strItems;
  auto v8
  _BYTE v9[80];
  std::pair<std::string,int> p___x;
  std::string __y;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vItems = __x;
        
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

      }
    }
  }
}

//#####################################
MiniClientCfg *CfgData::GetMiniClientCfg(std::string *p_Platform, int32_t nId)
{
	auto it = m_GetMiniClientMap.find(std::make_pair(*p_Platform, nId));
	if (it != m_GetMiniClientMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitMiniClientTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CfgMiniClient *v3;
  CDBCFile TabFile(0);
  CfgMiniClient stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vReward = __x;
        
        ++nIndex;
        v3 = std::map<std::string,CfgMiniClient>::operator[](&this->m_CfgMiniClient, &stu.strPlatfrom);
        CfgMiniClient::operator=(v3, &stu);

      }
    }
  }
}

//#####################################
const CfgMiniClient *CfgData::GetMiniClient(const std::string *const platform)
{
	auto it = m_CfgMiniClient.find(*platform);
	if (it != m_CfgMiniClient.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitMonsterAddAttrTable()
{
  std::list<CfgMonsterAddAttr> *v1;
  CDBCFile TabFile(0);
  CfgMonsterAddAttr AddAttrs;
  AttrAddon stu;
  int32_t Mid;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t j;

  
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

      }
    }
  }
}

//#####################################
AttrAddonVector *CfgData::GetAddMonsterAttrs(int32_t Mid,
        int32_t WorldLevel)
{
	auto it = m_MonstAddAttrMap.find(Mid);
	if (it != m_MonstAddAttrMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitMonsterRandTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile readFile(0);
  CfgMonsterRand stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  AttrAddonVector v10;
  std::string v11;
  std::string v13;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        nIndex = 0;
        stu.nId = readFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        
        path = "./ServerConfig/Tables/MonsterRand.txt";
        
        v1 = readFile.Search_Posistion( i, nIndex);
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.vAttrValue = __x;
        
        ++nIndex;
        
        v11 = "./ServerConfig/Tables/MonsterRand.txt";
        
        v2 = readFile.Search_Posistion( i, nIndex);
        v13 = v2->pString;
        parseAttrAddon(v10, v13, v11);
        stu.vAttrRatio = v10;
        
        stu.nSkill = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        m_cfgMonsterRandTable.AddMonsterRand(stu);

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


void CfgData::InitFamilyWarReliveTable()
{
    // NOTICE: CfgFamilyWarRelive struct and m_relive member belong to CfgFamilyWarTable class, not CfgData. No config file was found.
    // This function is kept as a stub for future implementation.
}

//////////////////////////////////////////////////////////////////////////
// CfgFamilyWarTable methods
//////////////////////////////////////////////////////////////////////////
void CfgFamilyWarTable::AddJoinReward(int32_t nLevel, int32_t nExp)
{
	CfgFamilyWarJoinReward reward;
	reward.level = nLevel;
	reward.addExp = nExp;
	m_reward.push_back(reward);
}

int32_t CfgFamilyWarTable::GetJoinReward(int32_t nLevel) const
{
	for (auto it = m_reward.begin(); it != m_reward.end(); ++it)
	{
		if (it->level >= nLevel)
			return it->addExp;
	}
	return 0;
}

void CfgData::InitGameTable()
{
	CDBCFile readFile(0);

	// ===== VipClubEquipPos.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/VipClubEquipPos.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/VipClubEquipPos.txt failed, please check!!!");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		VipEquipPosLevelUp stu;
		int32_t nIndex = 0;
		stu.nPos = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nNeedVip = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostGold = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_VipEquipPosLevelUpMap[std::make_pair(stu.nPos, stu.nLevel)] = stu;
	}

	// ===== VipClubEquipPosSuit.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/VipClubEquipPosSuit.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/VipClubEquipPosSuit.txt failed, please check!!!");
		return;
	}

	iBaseTableCount = readFile.GetRecordsNum();
	iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		VipEQuipPosSuit stu;
		int32_t nIndex = 0;
		stu.nSuitId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCount = readFile.Search_Posistion(i, nIndex++)->iValue;

		std::string attrStr = readFile.Search_Posistion(i, nIndex)->pString;
		std::list<AddAttribute> attrs;
		parseAttrAddon(attrs, attrStr, "./ServerConfig/Tables/VipClubEquipPosSuit.txt");
		stu.nAttrRate = 0; // parsed from attr if needed
		nIndex++;

		stu.nTalentId = readFile.Search_Posistion(i, ++nIndex)->iValue;
		stu.TalentLevel = readFile.Search_Posistion(i, ++nIndex)->iValue;

		m_VipEQuipPosSuitList.push_back(stu);
	}

	// ===== ClubAim.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/ClubAim.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/ClubAim.txt failed, please check!!!");
		return;
	}

	iBaseTableCount = readFile.GetRecordsNum();
	iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		ClbAimCfg stu;
		stu.nId = readFile.Search_Posistion(i, 0)->iValue;
		stu.nNeedVipLevel = readFile.Search_Posistion(i, 1)->iValue;
		stu.nNeedCount = readFile.Search_Posistion(i, 2)->iValue;
		stu.nAddDropTimes = readFile.Search_Posistion(i, 3)->iValue;
		m_ClbAimCfgList.push_back(stu);
	}

	// ===== VipClubLuckyDrop.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/VipClubLuckyDrop.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/VipClubLuckyDrop.txt failed, please check!!!");
		return;
	}

	iBaseTableCount = readFile.GetRecordsNum();
	iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CVipClubLuckyDrop stu;
		int32_t nIndex = 0;
		stu.nIndex = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = readFile.Search_Posistion(i, nIndex++)->iValue;

		std::string rateStr = readFile.Search_Posistion(i, nIndex)->pString;
		CItemHelper::parseRateItemDataListString(stu.lRateItemList);
		nIndex++;

		stu.nTotalRate = readFile.Search_Posistion(i, ++nIndex)->iValue;
		m_CVipClubLuckyDropMap[stu.nIndex] = stu;
	}

	// ===== ZhanHun.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/ZhanHun.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/ZhanHun.txt failed, please check!!!");
		return;
	}

	iBaseTableCount = readFile.GetRecordsNum();
	iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		ZhanHunCfg stu;
		int32_t nIndex = 0;
		stu.nMoney = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nSyb = readFile.Search_Posistion(i, nIndex++)->iValue;
		// skip a column
		nIndex++;

		std::string attrStr = readFile.Search_Posistion(i, nIndex)->pString;
		parseAttrAddon(stu.lAddAttrs, attrStr, "./ServerConfig/Tables/ZhanHun.txt");
		nIndex++;

		// skip 3 columns + nGongGaoId
		nIndex += 3;
		stu.nGongGaoId = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_ZhanHunCfgMap[stu.nMoney] = stu;
	}

	// ===== SunAndMoon.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/SunAndMoon.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/SunAndMoon.txt failed, please check!!!");
		return;
	}

	iBaseTableCount = readFile.GetRecordsNum();
	iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		SunAndMoonCfg stu;
		int32_t nIndex = 0;
		stu.nLevel = 0; // key field - not in struct, map key is read from col 0

		std::string itemStr = readFile.Search_Posistion(i, nIndex)->pString;
		CItemHelper::parseItemDataListString(stu.lConstItems, false);
		nIndex++;

		std::string attrStr = readFile.Search_Posistion(i, nIndex)->pString;
		parseAttrAddon(stu.lAttr, attrStr, "./ServerConfig/Tables/SunAndMoon.txt");
		nIndex++;

		stu.nGetItemTimes = readFile.Search_Posistion(i, ++nIndex)->iValue;
		stu.nSunTelentId = readFile.Search_Posistion(i, ++nIndex)->iValue;
		stu.nSunTelentLevel = readFile.Search_Posistion(i, ++nIndex)->iValue;
		stu.nMoonTelentId = readFile.Search_Posistion(i, ++nIndex)->iValue;
		stu.nMoonTelentLevel = readFile.Search_Posistion(i, ++nIndex)->iValue;
		nIndex++;
		stu.nGongGaoId = readFile.Search_Posistion(i, ++nIndex)->iValue;

		int32_t nKey = readFile.Search_Posistion(i, 0)->iValue;
		m_SunAndMoonCfgMap[nKey] = stu;
	}

	// ===== TreasureHunter.txt =====
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/TreasureHunter.txt"))
	{
		LOG_ERROR("open ./ServerConfig/Tables/TreasureHunter.txt failed, please check!!!");
		return;
	}

	iBaseTableCount = readFile.GetRecordsNum();
	iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0)
		return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		TreasureHunterCfg stu;
		int32_t nIndex = 0;
		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;

		std::string itemStr = readFile.Search_Posistion(i, nIndex)->pString;
		CItemHelper::parseItemVectorString(stu.Items, &itemStr);
		nIndex++;

		stu.nRequire = readFile.Search_Posistion(i, ++nIndex)->iValue;
		nIndex++;
		stu.GongGaoId = readFile.Search_Posistion(i, ++nIndex)->iValue;
		stu.nType = readFile.Search_Posistion(i, ++nIndex)->iValue;
		nIndex++;
		m_TreasureHunterCfgMap[stu.nId] = stu;
	}
}

//#####################################
const TreasureHunterCfg *CfgData::GetTreasureHunterCfg(int32_t nId)
{

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,TreasureHunterCfg> > it;
  std::_Rb_tree_const_iterator<std::pair<const int,TreasureHunterCfg> > __x;

  
  auto it = m_TreasureHunterCfgMap.find(nIda);
  auto __x = m_TreasureHunterCfgMap.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const SunAndMoonCfg *CfgData::GetSunAndMoonCfg(int32_t nLevel)
{

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,SunAndMoonCfg> > it;
  std::_Rb_tree_const_iterator<std::pair<const int,SunAndMoonCfg> > __x;

  auto it = m_SunAndMoonCfgMap.find(nLevela);
  auto __x = m_SunAndMoonCfgMap.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,SunAndMoonCfg>>::operator!=(&it, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,SunAndMoonCfg>>::operator->(&it)->second;
  else
    return 0;
}

//#####################################
const ZhanHunCfg *CfgData::GetZhanHunCfg(int32_t nLevel)
{

  const CfgData *thisa;
  std::_Rb_tree_const_iterator<std::pair<const int,ZhanHunCfg> > iter;
  std::_Rb_tree_const_iterator<std::pair<const int,ZhanHunCfg> > __x;

  auto iter = m_ZhanHunCfgMap.find(nLevela);
  auto __x = m_ZhanHunCfgMap.end();
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ZhanHunCfg>>::operator!=(&iter, &__x) )
    return &std::_Rb_tree_const_iterator<std::pair<int const,ZhanHunCfg>>::operator->(&iter)->second;
  else
    return 0;
}

//#####################################
const VipEquipPosLevelUp *CfgData::GetVipEquipPosLevelUp(int32_t nSlot,
        int32_t nLevel)
{
	auto it = m_VipEquipPosLevelUpMap.find(std::make_pair(nSlot, nLevel));
	if (it != m_VipEquipPosLevelUpMap.end())
		return &it->second;
	return NULL;
}

#if 0 // replaced by hand-written version at end of file
//#####################################
const VipEQuipPosSuit *CfgData::GetVipEQuipPosSuit(int32_t nLevel)
{
  const VipEQuipPosSuit *v2;
  std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit> > v4;

  const CfgData *thisa;
  std::reverse_iterator<std::_List_const_iterator<VipEQuipPosSuit> > it;
  std::list<VipEQuipPosSuit> v8;

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
#endif // replaced by hand-written version

//#####################################
const CVipClubLuckyDrop *CfgData::GetCVipClubLuckyDrop(int32_t nCondition)
{
	auto it = m_CVipClubLuckyDropMap.find(nCondition);
	if (it != m_CVipClubLuckyDropMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitMysteryShopTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  MemChrBag v4;

  CDBCFile readFile(0);
  CfgMysteryShop stu;
  std::string strItem;
  std::string v10;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  ItemData v17; // 0:kr00_12.12

  
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
        strItem = v1->pString;
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
        v10 = v2->pString;
        v17 = CItemHelper::parseItemDataString(&v10);
        v3 = v17.m_nId;
        BYTE4(v3) = v17.m_nClass;
        *(_QWORD *)&stu.exchange.m_nId = v3;
        stu.exchange.m_nCount = v17.m_nCount;
        
        ++nIndex;
        CfgMysteryShopTable::Add(&m_cfgMysteryShopTable, &stu);
      }
    }
  }
}

//#####################################
void CfgData::InitQQZoneRewardTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile TabFile(0);
  CfgQQGift gift;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        gift.nIndex = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        ++nIndex;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        gift.vReward = __x;
        
        gift.nCondition = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        m_cfgTencentTable.AddQQZoneGift(gift);

      }
    }
  }
}

//#####################################
void CfgData::InitRefreshMonsterCfgListMap()
{
  const CDBCFile::FIELD *v1;
  std::list<RefreshMonsterCfg> *v2;
  CDBCFile readFile(0);
  RefreshMonsterCfg stu;
  int32_t nActId;
  std::vector<Position> __x;
  std::string strPos;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strPos = v1->pString;
        CfgData::paresPosition(&__x, this, &strPos);
        stu.vRevivePosVector = __x;
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<RefreshMonsterCfg>>::operator[](&this->m_RefreshMonsterCfgListMap, &nActId);
        std::list<RefreshMonsterCfg>::push_back(v2, &stu);

      }
    }
  }
}

//#####################################
#if 0 // replaced by hand-written version at end of file
RefreshMonsterCfgList CfgData::GetRefreshMonsterCfgList(int32_t nActId)
{
	RefreshMonsterCfgList result;
	auto it = m_RefreshMonsterCfgMap.find(nActId);
	if (it != m_RefreshMonsterCfgMap.end())
		result = it->second;
	return result;
}
#endif // replaced by hand-written version

//#####################################
void CfgData::fetchItem(bool bSend)
{
	CfgItemTable newItems;
	Answer::RwLock::wrlock(&this->m_itemsLock);

	CDBCFile ItemFile(0);
	if (!ItemFile.OpenFromTXT("./ServerConfig/Tables/cfg_item.txt"))
	{
		LOG_ERROR("open cfg_item.txt failed,please check!!");
	}
	else
	{
		int32_t iBaseTableCount = ItemFile.GetRecordsNum();
		int32_t iBaseColumnCount = ItemFile.GetFieldsNum();
		if (iBaseColumnCount > 0)
		{
			for (int32_t i = 0; i < iBaseTableCount; ++i)
			{
				CfgItem* pItem = new CfgItem();
				pItem->id = ItemFile.Search_Posistion(i, 0)->iValue;
				pItem->name = ItemFile.Search_Posistion(i, 1)->pString;
				pItem->desc = ItemFile.Search_Posistion(i, 3)->pString;
				pItem->type = ItemFile.Search_Posistion(i, 4)->iValue;
				pItem->level = ItemFile.Search_Posistion(i, 5)->iValue;
				pItem->grade = ItemFile.Search_Posistion(i, 6)->iValue;
				pItem->job = ItemFile.Search_Posistion(i, 7)->iValue;
				pItem->in_value = ItemFile.Search_Posistion(i, 8)->iValue;
				pItem->out_value = ItemFile.Search_Posistion(i, 9)->iValue;
				pItem->bind = ItemFile.Search_Posistion(i, 10)->iValue;
				pItem->combine = ItemFile.Search_Posistion(i, 11)->iValue;
				pItem->quality = ItemFile.Search_Posistion(i, 12)->iValue;
				pItem->url = ItemFile.Search_Posistion(i, 13)->pString;
				pItem->drop_url = ItemFile.Search_Posistion(i, 14)->pString;
				pItem->effect = ItemFile.Search_Posistion(i, 15)->pString;
				pItem->use_method = ItemFile.Search_Posistion(i, 16)->pString;
				pItem->downgrade = ItemFile.Search_Posistion(i, 19)->iValue;
				pItem->group_id = ItemFile.Search_Posistion(i, 20)->iValue;
				pItem->cd_group = ItemFile.Search_Posistion(i, 21)->iValue;
				pItem->overlay = ItemFile.Search_Posistion(i, 22)->iValue;
				pItem->can_sell = ItemFile.Search_Posistion(i, 23)->iValue;
				pItem->broadcast = ItemFile.Search_Posistion(i, 24)->iValue;
				pItem->valid_time = ItemFile.Search_Posistion(i, 25)->iValue;
				pItem->item_Grade = ItemFile.Search_Posistion(i, 26)->iValue;
				pItem->CanDrop = ItemFile.Search_Posistion(i, 32)->iValue;
				pItem->useBroadcast = ItemFile.Search_Posistion(i, 33)->iValue;
				pItem->useInCarrier = ItemFile.Search_Posistion(i, 35)->iValue;
				pItem->GongGaoId = ItemFile.Search_Posistion(i, 40)->iValue;
				pItem->KunLingJingHua = ItemFile.Search_Posistion(i, 42)->iValue;
				pItem->XinMoBag = ItemFile.Search_Posistion(i, 43)->iValue;

				std::string str = ItemFile.Search_Posistion(i, 44)->pString;
				pItem->RongHeReceovery = parseInt32List(str);

				auto it = m_items.find(pItem->id);
				if (it == m_items.end())
				{
					newItems.insert(std::make_pair(pItem->id, pItem));
				}
				m_items[pItem->id] = pItem;
			}
			Answer::RwLock::unlock(&this->m_itemsLock);
			if (!newItems.empty() && bSend)
				sendNewItems(newItems);

			// ===== Item Gift =====
			Answer::RwLock::wrlock(&this->m_itemGiftsLock);
			m_itemGifts.clear();

			CDBCFile ItemGiftFile(0);
			if (!ItemGiftFile.OpenFromTXT("./ServerConfig/Tables/cfg_item_gift.txt"))
			{
				LOG_ERROR("open cfg_item_gift.txt failed,please check!!");
			}
			else
			{
				int32_t iBaseTableCount_Gift = ItemGiftFile.GetRecordsNum();
				int32_t iBaseColumnCount_Gift = ItemGiftFile.GetFieldsNum();
				if (iBaseColumnCount_Gift > 0)
				{
					for (int32_t i = 0; i < iBaseTableCount_Gift; ++i)
					{
						CfgItemGift itemGift;
						memset(&itemGift, 0, sizeof(itemGift));
						itemGift.id = ItemGiftFile.Search_Posistion(i, 0)->iValue;
						itemGift.item = ItemGiftFile.Search_Posistion(i, 2)->iValue;
						itemGift.type = ItemGiftFile.Search_Posistion(i, 3)->iValue;
						itemGift.count = ItemGiftFile.Search_Posistion(i, 4)->iValue;
						itemGift.bind = ItemGiftFile.Search_Posistion(i, 5)->iValue;
						itemGift.job = ItemGiftFile.Search_Posistion(i, 6)->iValue;
						itemGift.time = ItemGiftFile.Search_Posistion(i, 7)->iValue;

						auto it = m_itemGifts.find(itemGift.id);
						if (it == m_itemGifts.end())
						{
							CfgItemGiftVector* vec = new CfgItemGiftVector();
							m_itemGifts[itemGift.id] = vec;
						}
						m_itemGifts[itemGift.id]->push_back(itemGift);
					}

					// ===== Item Gift Random =====
					Answer::RwLock::unlock(&this->m_itemGiftsLock);
					Answer::RwLock::wrlock(&this->m_itemGiftRandomsLock);
					m_itemGiftRandoms.clear();

					CDBCFile ItemGiftRandFile(0);
					if (!ItemGiftRandFile.OpenFromTXT("./ServerConfig/Tables/cfg_item_gift_random.txt"))
					{
						LOG_ERROR("open cfg_item_gift_random.txt failed,please check!!");
					}
					else
					{
						int32_t iBaseTableCount_GiftRand = ItemGiftRandFile.GetRecordsNum();
						int32_t iBaseColumnCount_GiftRand = ItemGiftRandFile.GetFieldsNum();
						if (iBaseColumnCount_GiftRand > 0)
						{
							for (int32_t i = 0; i < iBaseTableCount_GiftRand; ++i)
							{
								CfgItemGiftRandom itemGiftRandom;
								itemGiftRandom.id = ItemGiftRandFile.Search_Posistion(i, 0)->iValue;
								itemGiftRandom.item = ItemGiftRandFile.Search_Posistion(i, 1)->iValue;
								itemGiftRandom.type = ItemGiftRandFile.Search_Posistion(i, 2)->iValue;
								itemGiftRandom.count = ItemGiftRandFile.Search_Posistion(i, 3)->iValue;
								itemGiftRandom.bind = ItemGiftRandFile.Search_Posistion(i, 4)->iValue;
								itemGiftRandom.static_probability = ItemGiftRandFile.Search_Posistion(i, 5)->iValue;
								itemGiftRandom.sum_probability = ItemGiftRandFile.Search_Posistion(i, 6)->iValue;
								itemGiftRandom.job = ItemGiftRandFile.Search_Posistion(i, 7)->iValue;
								itemGiftRandom.MinLevel = ItemGiftRandFile.Search_Posistion(i, 8)->iValue;
								itemGiftRandom.MaxLevel = ItemGiftRandFile.Search_Posistion(i, 9)->iValue;

								auto it = m_itemGiftRandoms.find(itemGiftRandom.id);
								if (it == m_itemGiftRandoms.end())
								{
									CfgItemGiftRandomVector* vec = new CfgItemGiftRandomVector();
									m_itemGiftRandoms[itemGiftRandom.id] = vec;
								}
								m_itemGiftRandoms[itemGiftRandom.id]->push_back(itemGiftRandom);
							}
							Answer::RwLock::unlock(&this->m_itemGiftRandomsLock);
						}
					}
				}
			}
		}
	}
}

//#####################################
void CfgData::fetchJob()
{
  CfgJob *v1;
  CDBCFile JobFile(0);
  CfgJob job;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  CfgMovie *v1;
  CDBCFile TabFile(0);
  CfgMovie movie;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t MoveId;

  
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CfgLevelExp *v3;
  CDBCFile TabFile(0);
  CfgLevelExp levelExp;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CfgLevelAttr *v3;
  CDBCFile LevelAttrFile(0);
  CfgLevelAttr levelAttr;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  AttrAddonVector v11;
  std::string v12;
  std::string v14;
  int __k;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        levelAttr.level = LevelAttrFile.Search_Posistion( i, 0)->iValue;
        levelAttr.job = LevelAttrFile.Search_Posistion( i, 1)->iValue;
        
        path = "./ServerConfig/Tables/cfg_level_attr.txt";
        
        v1 = LevelAttrFile.Search_Posistion( i, 2);
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        levelAttr.addonattr = __x;
        
        v12 = "./ServerConfig/Tables/cfg_level_attr.txt";
        
        v2 = LevelAttrFile.Search_Posistion( i, 3);
        v14 = v2->pString;
        parseAttrAddon(v11, v14, v12);
        levelAttr.addonPoint = v11;
        
        __k = (levelAttr.job << 16) | levelAttr.level;
        v3 = std::map<int,CfgLevelAttr>::operator[](&this->m_levelAttrs, &__k);
        CfgLevelAttr::operator=(v3, &levelAttr);

      }
    }
  }
}

//#####################################
void CfgData::fetchMap()
{
  const CDBCFile::FIELD *v1;
  CfgMap *v2;
  CfgMap map;
  CDBCFile MapFile(0);
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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

      }
    }
  }
}

//#####################################
void CfgData::fetchMapMonster()
{
  std::vector<CfgMapMonster> *v1;
  CfgMapMonster *v2;
  CDBCFile MapMonsterFile(0);
  CfgMapMonster mapmonster;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  std::vector<CfgMapPlant> *v1;
  CfgMapPlant *v2;
  CDBCFile MapPlantFile(0);
  int32_t id;
  CfgMapPlant mapPlant;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  CfgMapRegion *v1;
  std::vector<CfgMapRegion> *v2;
  CDBCFile MapRegionFile(0);
  CfgMapRegion mapRegion;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  const CDBCFile::FIELD *v5;
  std::string *v7;
  const char *v8;
  CfgMonster *v9;
  const CDBCFile::FIELD *v10;
  MemChrBag v11;

  CfgMonster monster;
  CDBCFile MonsterBroadcastFile(0);
  CDBCFile MonsterFile(0);
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter;
  StringVector vRand;
  std::string randtypes;
  std::string strSkill;
  std::string v22;
  std::string strItem;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t iBaseTableCountBroadcast;
  int32_t iBaseColumnCountBroadcast;
  int32_t i;
  int32_t nIndex;
  int32_t i_0;

  
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
        randtypes = v1->pString;
        
        monster.exp = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.type = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.revive_time = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        monster.skill_id = MonsterFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        v2 = MonsterFile.Search_Posistion( i, nIndex);
        strSkill = v2->pString;
        CfgData::parseMonsterSkill(thisa, monster.mid, (MonsterSkill (*const)[10])monster.unique_skill, &strSkill);
        
        ++nIndex;
        
        v3 = MonsterFile.Search_Posistion( i, nIndex);
        v22 = v3->pString;
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
        strItem = v5->pString;
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
        }
        v9 = std::map<int,CfgMonster>::operator[](&m_monsters, &monster.mid);
        CfgMonster::operator=(v9, &monster);

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
            std::vector<int>::push_back(&m_monsterBroadcasts, (const int *const)v10);
          }
        }
      }
    }
  }
}

//#####################################
void CfgData::fetchMonsterAI()
{
  CfgMonsterAI *v1;
  CDBCFile MonsterFile(0);
  CfgMonsterAI ai;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
  CfgMonsterAdjust monster;
  CDBCFile MonsterFile(0);
  auto v4
  _BYTE v5[224];

  auto v7
  _BYTE v8[224];
  std::pair<int,int> v9;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;

  
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  std::vector<CfgMonsterDropGroup> *v3;
  CDBCFile MonsterDropFile(0);
  CfgMonsterDropGroup monsterDropGroup;
  std::string p_StringTime;
  std::string v8;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        p_StringTime = v1->pString;
        monsterDropGroup.start_date = Answer::DayTime::StringToIntTime(p_StringTime);
        
        ++nIndex;
        
        v2 = MonsterDropFile.Search_Posistion( i, nIndex);
        v8 = v2->pString;
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
  std::vector<CfgMonsterGroupDrop> *v1;
  CDBCFile MonsterGroupFile(0);
  CfgMonsterGroupDrop monsterGroupDrop;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
  std::vector<CfgMonsterTaskDrop> *v1;
  CDBCFile MonsterTaskFile(0);
  CfgMonsterTaskDrop monsterTaskDrop;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        memset(&monsterTaskDrop.mid, 0, sizeof(int64_t));
        memset(&monsterTaskDrop.item, 0, sizeof(int64_t));
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
  const CDBCFile::FIELD *v1;
  std::string *v2;
  const char *v3;
  const CDBCFile::FIELD *v4;
  std::string *v5;
  const char *v6;
  size_t v7;
  const CDBCFile::FIELD *v8;
  std::string *v9;
  size_t v10;
  const CDBCFile::FIELD *v11;
  std::string *v12;
  std::string *v13;
  const char *v14;
  std::string *v15;
  const char *v16;
  std::string *v17;
  const char *v18;
  CfgNpc *v19;
  CfgNpcAirport *v20;
  CDBCFile TabFileAir(0);
  CDBCFile TabFile(0);
  CfgNpcAirport airport;
  int iValue;
  std::vector<int> v28;
  std::vector<std::string> v30;
  std::vector<CfgDungeonNpcCost> v31;
  CfgDungeonNpcCost NpcCost;
  StringVector CostItem;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter;
  StringVector vpf;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector CostVector;
  std::string platform;
  StringVector vparam;
  std::string param;
  StringVector mapids;
  std::string delims;
  std::string str;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  int __x;
  std::string v49;
  std::string v53;
  std::string v55;
  std::string v57;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v59;
  std::string v60;
  bool ret;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  uint32_t j;
  uint32_t j_0;
  int32_t i_0;

  
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
        str = v1->pString;
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
        param = v4->pString;
        
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
        platform = v8->pString;
        
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
        }
        
        v55 = "|";
        
        v11 = TabFile.Search_Posistion( i, 27);
        v57 = v11->pString;
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
          
          memset(&NpcCost.ItemType, 0, sizeof(int64_t));
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
        }
        v19 = std::map<int,CfgNpc>::operator[](&this->m_npcs, &airport.id);
        CfgNpc::operator=(v19, (const CfgNpc *const)&airport);
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
  const CDBCFile::FIELD *v1;
  std::string *v2;
  std::string *v3;
  const char *v4;
  std::string *v5;
  const char *v6;
  const CDBCFile::FIELD *v7;
  std::string *v8;
  std::string *v9;
  const char *v10;
  CfgPlant *v11;
  CDBCFile TabFile(0);
  CfgPlant plant;
  StringVector RateVt;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0;
  CfgPlantEvent Event;
  StringVector EventVt;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector ItemString;
  StringVector strItems;
  std::string delims;
  std::string str;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v26;
  std::string v28;
  std::string v30;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v32;
  std::string v33;
  int __x;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        str = v1->pString;
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
        v30 = v7->pString;
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
        }
        v11 = std::map<int,CfgPlant>::operator[](&this->m_plants, &plant.id);
        CfgPlant::operator=(v11, &plant);

      }
    }
  }
}

//#####################################
void CfgData::InitShenYaoPosSuitTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  ShenYaoPosSuit stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  ShenYaoPosSuit p_stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.vAttrAddon = __x;
        
        ++nIndex;
        p_stu = stu;
        m_cfgEquip.AddShenYaoPosSuit(p_stu);


      }
    }
  }
}

//#####################################
void CfgData::InitShenYaoPosTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile readFile(0);
  ShenYaoPos stu;
  AttrAddonVector __x;
  std::string path;
  std::string addonAttr;
  std::list<ItemData> strItems;
  ShenYaoPos p_stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        addonAttr = v1->pString;
        parseAttrAddon(__x, addonAttr, path);
        stu.vAttrAddon = __x;
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string bCombi(v2->pString);
        CItemHelper::parseItemDataListString(&strItems, (bool)bCombi);
        stu.nCost = strItems;
        
        stu.nGongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        p_stu = stu;
        m_cfgEquip.AddShenYaoPosCfg(p_stu);


      }
    }
  }
}

//#####################################
void CfgData::InitShiZhuangLevelTable()
{
  CDBCFile readFile(0);
  CfgShiZhuangLevel stu;
  AddAttribute AddAttr;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t j;

  
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
            &stu.vAttr.push_back(&AddAttr);
        }
        m_cfgShiZhuangTable.AddShiZhuangLevel(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitSpecialBossMapCfgMap()
{
  const CDBCFile::FIELD *v1;
  SpecialBossMapCfg *v2;
  CDBCFile TabFile(0);
  SpecialBossMapCfg stu;
  std::string strItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
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
        strItem = v1->pString;
        v13 = CItemHelper::parseItemDataString(&strItem);
        v3 = v13.m_nId;
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
	auto it = m_SpecialBossMapCfgMap.find(MapId);
	if (it != m_SpecialBossMapCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitSpecialMonster()
{
  CDBCFile TabFile(0);
  cfgSpecialMonster stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile TabFile(0);
  CfgTGPGift gift;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        gift.vReward = __x;
        
        ++nIndex;
        m_cfgTencentTable.AddTGPNewerGift(gift);

      }
    }
  }
}

//#####################################

//#####################################
void CfgData::fetchTask()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  const CDBCFile::FIELD *v5;
  const CDBCFile::FIELD *v6;
  CfgTask *v7;
  CfgTask task;
  CDBCFile TabFile(0);
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v13;
  std::string v14;
  MemChrJobBagVector v16;
  std::string v17;
  std::string strRequest;
  std::list<TaskDrop> v21;
  _BYTE v22[15];
  std::string path;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        task.items_receive = __x;
        
        task.award_exp = TabFile.Search_Posistion( i, 16)->iValue;
        task.award_money = TabFile.Search_Posistion( i, 17)->iValue;
        task.gold = TabFile.Search_Posistion( i, 18)->iValue;
        task.dilong = TabFile.Search_Posistion( i, 19)->iValue;
        task.rongyu = TabFile.Search_Posistion( i, 20)->iValue;
        task.fuwen = TabFile.Search_Posistion( i, 21)->iValue;
        task.BossScore = TabFile.Search_Posistion( i, 22)->iValue;
        
        v3 = TabFile.Search_Posistion( i, 23);
        v14 = v3->pString;
        CItemHelper::parseItemVectorString(&v13, &v14);
        task.award_item = v13;
        
        v4 = TabFile.Search_Posistion( i, 24);
        v17 = v4->pString;
        CfgData::parseTaskItemJobString(&v16, this, task.id, &v17);
        task.award_optional = v16;
        
        task.condition = TabFile.Search_Posistion( i, 35)->iValue;
        
        v5 = TabFile.Search_Posistion( i, 36);
        strRequest = v5->pString;
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
        
        std::string v22("./ServerConfig/Tables/cfg_task.txt");
        
        v6 = TabFile.Search_Posistion( i, 68);
        path = v6->pString;
        CfgData::parseTaskDrop(
          &v21,
          (int32_t)this,
          (unsigned int)task.id,
          &path);
        task.drop_list = v21;
        
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

      }
    }
  }
}

//#####################################
void CfgData::fetchTrap()
{
  const CDBCFile::FIELD *v1;
  CfgTrap *v2;
  CDBCFile TabFile(0);
  CfgTrap trap;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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

      }
    }
  }
}

//#####################################
std::vector<Position> *CfgData::paresPosition(
        std::vector<Position> *const std::string *const strPos)
{
  std::string *v3;
  std::string *v4;
  const char *v5;
  std::string *v6;
  const char *v7;
  Position stu;
  StringVector Pos;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector PosString;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v17;
  _BYTE v18[33];

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
    }
  }
  return retstr;
}

//#####################################
void CfgData::parseItemStringWithJob(int32_t id,
        const std::string *const strItems,
        MemChrBagVector *const items,
        MemChrJobBagVector *const jobItems)
{
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  std::string *v16;
  const char *v17;
  std::string *v18;
  const char *v19;
  const char *v20;
  MemChrBag itemData;
  MemChrJobBag job;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v32;
  _BYTE v33[17];

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
    }
  }
}

//#####################################
GongGaoList CfgData::parseGongGaoString(int32_t id, const std::string *const strItems)
{
  std::string *v3;
  GongGaoList result;
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *strItemsa;
  CfgGongGao stu;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v18;
  _BYTE v19[33];

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
        std::list<CfgGongGao>::push_back(this, &stu);
      }
    }
  }
  return result;
}

//#####################################
MemChrEquipBagVector *CfgData::parseEquipItemString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  std::string *v16;
  const char *v17;
  std::string *v18;
  const char *v19;
  std::string *v20;
  const char *v21;
  std::string *v22;
  const char *v23;
  std::string *v24;
  const char *v25;
  std::string *v26;
  const char *v27;
  std::string *v28;
  const char *v29;
  std::string *v30;
  const char *v31;
  std::string *v32;
  const char *v33;
  std::string *v34;
  const char *v35;
  std::string *v36;
  const char *v37;
  std::string *v38;
  const char *v39;
  std::string *v40;
  const char *v41;
  const char *v42;
  CfgEquipItem itemData_1;
  CfgEquipItem itemData_0;
  CfgEquipItem itemData;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v55;
  _BYTE v56[33];

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
    }
  }
  return retstr;
}

//#####################################
MemChrJobBagVector *CfgData::parseTaskItemJobString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  std::string *v16;
  const char *v17;
  std::string *v18;
  const char *v19;
  std::string *v20;
  const char *v21;
  std::string *v22;
  const char *v23;
  std::string *v24;
  const char *v25;
  std::string *v26;
  const char *v27;
  std::string *v28;
  const char *v29;
  std::string *v30;
  const char *v31;
  std::string *v32;
  const char *v33;
  std::string *v34;
  const char *v35;
  const char *v36;
  MemChrJobBag itemData_1;
  MemChrJobBag itemData_0;
  MemChrJobBag itemData;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v49;
  _BYTE v50[33];

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
    }
  }
  return retstr;
}

//#####################################
void CfgData::parseMonsterSkill(int32_t id,
        MonsterSkill (*const vSkill)[10],
        const std::string *const strSkill)
{
  int32_t v5; // eax
  std::string *v6;
  int32_t v7; // r12d
  std::string *v8;
  const char *v9;
  int32_t v10; // r12d
  std::string *v11;
  const char *v12;
  int32_t v13; // r12d
  std::string *v14;
  const char *v15;
  const char *v16;
  StringVector skill;
  StringVector skills;
  std::string delims;
  std::string v23;
  int32_t isize;
  int32_t i;

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
    }
  }
}

//#####################################
MemJobItemTable *CfgData::parseGambleEquip(int32_t id,
        const std::string *const strItems)
{
  std::string *v4;
  std::string *v5;
  const char *v6;
  std::string *v7;
  const char *v8;
  MemJobItem *v9;
  const char *v10;
  MemJobItem itemData;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v21;
  _BYTE v22[33];

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
    }
  }
  return retstr;
}

//#####################################
TaskRequest CfgData::parseTaskCondition(int32_t id,
        int32_t condition,
        const std::string *const strRequest)
{
  std::string *v4;
  const char *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  const char *v16;
  StringVector requests;
  TaskRequest request;
  std::string delims;
  TaskRequest v22;
  int32_t nSize;

  memset(&request.param1, 0, sizeof(int64_t));
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
  return v22;
}

//#####################################
TaskDropList CfgData::parseTaskDrop(int32_t id,
        const std::string *const str,
        const std::string *const path)
{
  TaskDropList result;
  std::string *v6;
  const std::string *v7;
  unsigned int64_t v8;
  const std::string *v9;
  const char *v10;
  unsigned int ida;
  TaskDrop stu;
  std::string strParam;
  std::string strCount;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vDrop;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::list<Param2> __x;
  int e;

  ida = (unsigned int)str;
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
      v10 = (const char *)std::string::c_str(&strCount);
      stu.nCount = atoi(v10);
      CfgData::paraseParam2List(
        &__x,
        *(const std::string *const *)&id,
        &strParam,
        ida);
      stu.lstJobGroup = __x;
      std::list<TaskDrop>::push_back(this, &stu);

      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
    }
  }
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
void CfgData::updateServerStartTime(int32_t kaiFuTime)
{
  COpenBeta *v2;

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
  GameService *v2;
  int32_t v3; // eax
  uint32_t WOffset; // eax
  GameService *v5;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > it;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > __x;
  Answer::NetPacket *packet;
  CfgItem *pCfgItem;

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2752u);
  if ( packet )
  {
    v3 = std::map<int,CfgItem *>::size(items);
    Answer::NetPacket::writeInt32(packet, v3);
    for (it = items.begin();
          std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator++(&it) )
    {
      __x = items.end();
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
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  CDBCFile TabFile(0);
  SevenTouZi stu;
  MemChrBagVector __x;
  std::string strItems;
  SevenTouZi p_stu;
  MemChrBagVector v10;
  std::string v11;
  MonthTouZi v13;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;

  
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
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nCondition = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vItem = __x;
        
        ++nIndex;
        p_stu = stu;
        m_cfgTouZiTable.AddSevenTouZi(p_stu);


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
          v11 = v3->pString;
          CItemHelper::parseItemVectorString(&v10, &v11);
          stu.nCondition = &v10;
          
          stu.nNoticeId = TabFile.Search_Posistion( i_0, ++nIndex_0)->iValue;
          ++nIndex_0;
          MonthTouZi::MonthTouZi(&v13, (const MonthTouZi *const)&stu);
          m_cfgTouZiTable.AddMonthTouZi(v13);

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
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const std::string *v5;
  std::string *v6;
  const char *v7;
  int *v8;
  std::string *v9;
  const char *v10;
  std::string *v11;
  const char *v12;
  const std::string *v14;
  std::string *v15;
  const char *v16;
  std::string *v17;
  const char *v18;
  std::string *v19;
  const char *v20;
  const CDBCFile::FIELD *v21;
  CDBCFile readFile(0);
  TreasureMapCfg stu;
  TreasureMapEventCfg stu_0;
  MapPos stuPos;
  StringVector vstr_0;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin_0;
  StringVector SplitStr_0;
  StringVector vstr;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iterBegin;
  StringVector SplitStr;
  std::string MapPosString;
  std::string RateString;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v40;
  int __k;
  std::string v43;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v45;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v46;
  std::string v47;
  Position v49;
  TreasureMapCfg p_stu;
  TreasureMapEventCfg v51;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;

  
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
        RateString = v2->pString;
        
        ++nIndex;
        
        v3 = readFile.Search_Posistion( i, nIndex);
        MapPosString = v3->pString;
        
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
              v8 = stu.m_EventRate[__k];
              v9 = std::vector<std::string>::operator[](&vstr, 1u);
              v10 = (const char *)std::string::c_str(v9);
              *v8 = atoi(v10);
              v8 = stu.m_MaxProbability;
              v11 = std::vector<std::string>::operator[](&vstr, 1u);
              v12 = (const char *)std::string::c_str(v11);
              stu.m_MaxProbability = (_DWORD)v8 + atoi(v12);
            }
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin);
          }
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
            __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iterBegin_0);
          }
        }
        p_stu = stu;
        m_TreasureMapTabale.AddTreasureMapCfg(p_stu);


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
          v51 = stu_0;
          m_TreasureMapTabale.AddTreasureMapEventCfg(v51);


        }
      }
    }
  }
}

//#####################################
void CfgData::InitWishRewardTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgWishReward stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;

  
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
        nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nTime = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vReward = __x;
        
        ++nIndex;
        CfgWishRewardTable::Add(&this->m_cfgWishRewardTable, nId, &stu);

      }
    }
  }
}

//#####################################
void CfgData::InitWuHunItemTable()
{
  const CDBCFile::FIELD *v1;
  WuHunItem *v2;
  CDBCFile TabFile(0);
  WuHunItem stu;
  std::list<AddAttribute> __x;
  _BYTE v6[15];
  int32_t v8[3];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nType = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nQuality = TabFile.Search_Posistion( i, nIndex++)->iValue;
        stu.nNeedQuality = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        std::string v6("./ServerConfig/Tables/WuHun.txt");
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string v8(v1->pString);
        CfgData::parseAddAttribues(
          &__x,
          this,
          (int32_t)v8,
          (unsigned int)nIndex);
        stu.lAttrList = __x;
        
        stu.nTalentId = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.nTalentLevel = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 8;
        stu.overlay = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 3;
        stu.nDressLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        v2 = std::map<int,WuHunItem>::operator[](&this->m_WuHunItemMap, &stu.nId);
        WuHunItem::operator=(v2, &stu);

      }
    }
  }
}

//#####################################
WuHunItem *CfgData::GetWuHunItem(int32_t nId)
{
	auto it = m_WuHunItemMap.find(nId);
	if (it != m_WuHunItemMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitWuHunShopTable()
{
  const CDBCFile::FIELD *v1;
  std::list<CfgWuHunShop> *v2;
  CfgWuHunShop *v3;
  MemChrBag v4;

  CDBCFile TabFile(0);
  CfgWuHunShop stu;
  int32_t ShopId;
  std::string strItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        strItem = v1->pString;
        CItemHelper::parseItemString(&v4, &strItem);
        stu.Item = v4;
        
        stu.Rate = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        stu.Const = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v2 = std::map<int,std::list<CfgWuHunShop>>::operator[](&m_CfgWuHunShopMap, &ShopId);
        std::list<CfgWuHunShop>::push_back(v2, &stu);
        v3 = std::map<int,CfgWuHunShop>::operator[](&m_CfgWuHunShopItemMap, &stu.Index);
        *v3 = stu;
      }
    }
  }
}

//#####################################
#if 0 // replaced by hand-written version at end of file
CfgWuHunShopList CfgData::GetWuHunShopItemList(int32_t ShopId)
{
	CfgWuHunShopList result;
	auto it = m_WuHunShopListMap.find(ShopId);
	if (it != m_WuHunShopListMap.end())
		result = it->second;
	return result;
}
#endif // replaced by hand-written version

#if 0 // replaced by hand-written version at end of file
//#####################################
CfgWuHunShop *CfgData::GetWuHunShopItem(int32_t nIndex)
{
	auto it = m_WuHunShopMap.find(nIndex);
	if (it != m_WuHunShopMap.end())
		return &it->second;
	return NULL;
}
#endif // replaced by hand-written version

//#####################################
void CfgData::InitYellowLevelRewardTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile TabFile(0);
  CfgTencentGift gift;
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v8;
  std::string v9;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;

  
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
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        gift.nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        gift.vRewards = __x;
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v9 = v2->pString;
        CItemHelper::parseItemVectorString(&v8, &v9);
        gift.vVipRewards = v8;
        
        ++nIndex;
        m_cfgTencentTable.AddYellowLevelGift(nId, gift);
        CfgTencentGift::~CfgTencentGift(&gift);
      }
    }
  }
}

//#####################################
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
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgTalentActive stu;
  std::list<ItemData> strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nId = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&strItems, (bool)bCombi);
        stu.lItems = strItems;
        
        ++nIndex;
        m_cfgSkillTable.AddTalentActive(stu);

      }
    }
  }
}

//#####################################

//#####################################
void CfgData::fetchTask()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  const CDBCFile::FIELD *v5;
  const CDBCFile::FIELD *v6;
  CfgTask *v7;
  CfgTask task;
  CDBCFile TabFile(0);
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v13;
  std::string v14;
  MemChrJobBagVector v16;
  std::string v17;
  std::string strRequest;
  std::list<TaskDrop> v21;
  _BYTE v22[15];
  std::string path;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        task.items_receive = __x;
        
        task.award_exp = TabFile.Search_Posistion( i, 16)->iValue;
        task.award_money = TabFile.Search_Posistion( i, 17)->iValue;
        task.gold = TabFile.Search_Posistion( i, 18)->iValue;
        task.dilong = TabFile.Search_Posistion( i, 19)->iValue;
        task.rongyu = TabFile.Search_Posistion( i, 20)->iValue;
        task.fuwen = TabFile.Search_Posistion( i, 21)->iValue;
        task.BossScore = TabFile.Search_Posistion( i, 22)->iValue;
        
        v3 = TabFile.Search_Posistion( i, 23);
        v14 = v3->pString;
        CItemHelper::parseItemVectorString(&v13, &v14);
        task.award_item = v13;
        
        v4 = TabFile.Search_Posistion( i, 24);
        v17 = v4->pString;
        CfgData::parseTaskItemJobString(&v16, this, task.id, &v17);
        task.award_optional = v16;
        
        task.condition = TabFile.Search_Posistion( i, 35)->iValue;
        
        v5 = TabFile.Search_Posistion( i, 36);
        strRequest = v5->pString;
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
        
        std::string v22("./ServerConfig/Tables/cfg_task.txt");
        
        v6 = TabFile.Search_Posistion( i, 68);
        path = v6->pString;
        CfgData::parseTaskDrop(
          &v21,
          (int32_t)this,
          (unsigned int)task.id,
          &path);
        task.drop_list = v21;
        
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
  const CDBCFile::FIELD *v1;
  CfgTrap *v2;
  CDBCFile TabFile(0);
  CfgTrap trap;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
  std::string *v3;
  std::string *v4;
  const char *v5;
  std::string *v6;
  const char *v7;
  Position stu;
  StringVector Pos;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector PosString;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v17;
  _BYTE v18[33];

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
    }
  }
  return retstr;
}

//#####################################
void CfgData::parseItemStringWithJob(int32_t id,
        const std::string *const strItems,
        MemChrBagVector *const items,
        MemChrJobBagVector *const jobItems)
{
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  std::string *v16;
  const char *v17;
  std::string *v18;
  const char *v19;
  const char *v20;
  MemChrBag itemData;
  MemChrJobBag job;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v32;
  _BYTE v33[17];

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
    }
  }
}

//#####################################
GongGaoList CfgData::parseGongGaoString(int32_t id, const std::string *const strItems)
{
  std::string *v3;
  GongGaoList result;
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *strItemsa;
  CfgGongGao stu;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v18;
  _BYTE v19[33];

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
        std::list<CfgGongGao>::push_back(this, &stu);
      }
    }
  }
  return result;
}

//#####################################
MemChrEquipBagVector *CfgData::parseEquipItemString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  std::string *v16;
  const char *v17;
  std::string *v18;
  const char *v19;
  std::string *v20;
  const char *v21;
  std::string *v22;
  const char *v23;
  std::string *v24;
  const char *v25;
  std::string *v26;
  const char *v27;
  std::string *v28;
  const char *v29;
  std::string *v30;
  const char *v31;
  std::string *v32;
  const char *v33;
  std::string *v34;
  const char *v35;
  std::string *v36;
  const char *v37;
  std::string *v38;
  const char *v39;
  std::string *v40;
  const char *v41;
  const char *v42;
  CfgEquipItem itemData_1;
  CfgEquipItem itemData_0;
  CfgEquipItem itemData;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v55;
  _BYTE v56[33];

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
    }
  }
  return retstr;
}

//#####################################
MemChrJobBagVector *CfgData::parseTaskItemJobString(int32_t id,
        const std::string *const strItems)
{
  std::string *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  std::string *v16;
  const char *v17;
  std::string *v18;
  const char *v19;
  std::string *v20;
  const char *v21;
  std::string *v22;
  const char *v23;
  std::string *v24;
  const char *v25;
  std::string *v26;
  const char *v27;
  std::string *v28;
  const char *v29;
  std::string *v30;
  const char *v31;
  std::string *v32;
  const char *v33;
  std::string *v34;
  const char *v35;
  const char *v36;
  MemChrJobBag itemData_1;
  MemChrJobBag itemData_0;
  MemChrJobBag itemData;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v49;
  _BYTE v50[33];

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
    }
  }
  return retstr;
}

//#####################################
void CfgData::parseMonsterSkill(int32_t id,
        MonsterSkill (*const vSkill)[10],
        const std::string *const strSkill)
{
  int32_t v5; // eax
  std::string *v6;
  int32_t v7; // r12d
  std::string *v8;
  const char *v9;
  int32_t v10; // r12d
  std::string *v11;
  const char *v12;
  int32_t v13; // r12d
  std::string *v14;
  const char *v15;
  const char *v16;
  StringVector skill;
  StringVector skills;
  std::string delims;
  std::string v23;
  int32_t isize;
  int32_t i;

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
    }
  }
}

//#####################################
MemJobItemTable *CfgData::parseGambleEquip(int32_t id,
        const std::string *const strItems)
{
  std::string *v4;
  std::string *v5;
  const char *v6;
  std::string *v7;
  const char *v8;
  MemJobItem *v9;
  const char *v10;
  MemJobItem itemData;
  StringVector item;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it;
  StringVector items_receive;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::string v21;
  _BYTE v22[33];

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
    }
  }
  return retstr;
}

//#####################################
TaskRequest CfgData::parseTaskCondition(int32_t id,
        int32_t condition,
        const std::string *const strRequest)
{
  std::string *v4;
  const char *v5;
  std::string *v6;
  const char *v7;
  std::string *v8;
  const char *v9;
  std::string *v10;
  const char *v11;
  std::string *v12;
  const char *v13;
  std::string *v14;
  const char *v15;
  const char *v16;
  StringVector requests;
  TaskRequest request;
  std::string delims;
  TaskRequest v22;
  int32_t nSize;

  memset(&request.param1, 0, sizeof(int64_t));
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
  return v22;
}

//#####################################
TaskDropList CfgData::parseTaskDrop(int32_t id,
        const std::string *const str,
        const std::string *const path)
{
  TaskDropList result;
  std::string *v6;
  const std::string *v7;
  unsigned int64_t v8;
  const std::string *v9;
  const char *v10;
  unsigned int ida;
  TaskDrop stu;
  std::string strParam;
  std::string strCount;
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter;
  StringVector vDrop;
  std::string delims;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i;
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs;
  std::list<Param2> __x;
  int e;

  ida = (unsigned int)str;
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
      v10 = (const char *)std::string::c_str(&strCount);
      stu.nCount = atoi(v10);
      CfgData::paraseParam2List(
        &__x,
        *(const std::string *const *)&id,
        &strParam,
        ida);
      stu.lstJobGroup = __x;
      std::list<TaskDrop>::push_back(this, &stu);
      TaskDrop::~TaskDrop(&stu);
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter);
    }
  }
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
void CfgData::updateServerStartTime(int32_t kaiFuTime)
{
  COpenBeta *v2;

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
  GameService *v2;
  int32_t v3; // eax
  uint32_t WOffset; // eax
  GameService *v5;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > it;
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > __x;
  Answer::NetPacket *packet;
  CfgItem *pCfgItem;

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2752u);
  if ( packet )
  {
    v3 = std::map<int,CfgItem *>::size(items);
    Answer::NetPacket::writeInt32(packet, v3);
    for (it = items.begin();
          std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator++(&it) )
    {
      __x = items.end();
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

//#####################################
void CfgData::InitTaskCycleRewardTable()
{
  CDBCFile readFile(0);
  TaskCycleReward stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        m_cfgTaskCycleTable.AddTaskReward(stu);
      }
    }
  }
}

//#####################################
QuestionsVector *CfgData::GetAllQuestions(int8_t nType)
{
  std::vector<CfgQuestions> *v3;
  int __k[5];

  __k[0] = nType;
  v3 = std::map<int,std::vector<CfgQuestions>>::operator[](&this->m_mQuestions, __k);
  std::vector<CfgQuestions>::vector(retstr, v3);
  return retstr;
}

//#####################################
void CfgData::InitTencentSevenDayLoginTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile TabFile(0);
  CfgTencentSevenDayLogin stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        stu.nDays = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vReward = __x;
        
        ++nIndex;
        m_cfgTencentTable.AddSevenDayLogin(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitTianLingTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  TianLingCfg *v3;
  CDBCFile readFile(0);
  TianLingCfg stu;
  std::list<ItemData> strItems;
  std::list<AddAttribute> __x;
  _BYTE v10[15];
  int32_t v12[3];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&strItems, (bool)bCombi);
        stu.CostItems = strItems;
        
        ++nIndex;
        
        std::string v10("./ServerConfig/Tables/TianLing.txt");
        
        v2 = readFile.Search_Posistion( i, nIndex);
        std::string v12(v2->pString);
        CfgData::parseAddAttribues(
          &__x,
          this,
          (int32_t)v12,
          (unsigned int)nIndex);
        stu.AttrList = __x;
        
        stu.GongGaoId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        nIndex += 4;
        stu.CostCoin = readFile.Search_Posistion( i, nIndex++)->iValue;
        v3 = std::map<int,TianLingCfg>::operator[](&this->m_TianLingCfgTable, &stu.Level);
        TianLingCfg::operator=(v3, &stu);

      }
    }
  }
}

//#####################################
TianLingCfg *CfgData::GetTianLingCfg(int32_t TianLingLevel)
{
	auto it = m_TianLingMap.find(TianLingLevel);
	if (it != m_TianLingMap.end())
		return &it->second;
	return NULL;
}

//#####################################

//#####################################
void CfgData::InitTongTianChiRanTable()
{
  int *v1;
  CDBCFile readFile(0);
  int32_t nId;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nTitleId;

  
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
	auto it = m_TongTianChiRewardMap.find(nId);
	if (it != m_TongTianChiRewardMap.end())
		return it->second;
	return 0;
}

//#####################################

//#####################################
void CfgData::InitTrailerTable()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  CDBCFile TabFile(0);
  CfgTrailerInfo stu; // [rsp+F0h] [rbp-C0h] OVERLAPPED BYREF
  std::list<AddAttribute> __x;
  _BYTE v8[15];
  int32_t v10[3];
  std::string strItem;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t nIndex_0;
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
        std::list<AddAttribute>::list(&stu.nRand);
        nIndex = 0;
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        ++nIndex;
        LOBYTE(stu.FullWeiWang) = TabFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        std::string v8("./ServerConfig/Tables/cfg_trailer.txt");
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        std::string v10(v2->pString);
        CfgData::parseAddAttribues(
          &__x,
          this,
          (int32_t)v10,
          (unsigned int)nIndex);
        std::list<AddAttribute>::operator=(&stu.nRand, &__x);
        
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
          strItem = v3->pString;
          v24 = CItemHelper::parseItemDataString(&strItem);
          v4 = v24.m_nId;
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

//#####################################
void CfgData::InitTrigSkillTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile readFile(0);
  CfgTrigSkill stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
        m_cfgSkillTable.AddTrigSkill(stu);

      }
    }
  }
}

//#####################################
void CfgData::InitUltimateChallengeCfg()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  UltimateChallengeCfg *v4;
  CDBCFile readFile(0);
  UltimateChallengeCfg stu;
  std::string strItem;
  MemChrBagVector __x;
  std::string strItems;
  std::list<Param2> v13;
  _BYTE v14[15];
  int32_t v16[3];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
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
        stu.CurMapId = readFile.Search_Posistion( i, nIndex++)->iValue;
        stu.NextMapId = readFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        stu.Floor = readFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = readFile.Search_Posistion( i, nIndex);
        strItem = v1->pString;
        v23 = CItemHelper::parseItemDataString(&strItem);
        v5 = v23.m_nId;
        BYTE4(v5) = v23.m_nClass;
        *(_QWORD *)&stu.CostItems.m_nId = v5;
        stu.CostItems.m_nCount = v23.m_nCount;
        
        ++nIndex;
        
        v2 = readFile.Search_Posistion( i, nIndex);
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.GetItems = __x;
        
        stu.MailId = readFile.Search_Posistion( i, ++nIndex)->iValue;
        stu.Score = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        
        std::string v14("./ServerConfig/Tables/limitChallenge.txt");
        
        v3 = readFile.Search_Posistion( i, nIndex);
        std::string v16(v3->pString);
        CfgData::paraseParam2List(
          &v13,
          this,
          (int32_t)v16,
          (unsigned int)nIndex);
        stu.DropRateList = v13;
        
        ++nIndex;
        stu.DoubleConst = readFile.Search_Posistion( i, ++nIndex)->iValue;
        ++nIndex;
        v4 = std::map<int,UltimateChallengeCfg>::operator[](&this->m_UltimateChallengeCfgMap, &stu.CurMapId);
        UltimateChallengeCfg::operator=(v4, &stu);

      }
    }
  }
}

#if 0 // replaced by hand-written version at end of file
//#####################################
UltimateChallengeCfg *CfgData::GetUltimateChallengeCfgMap(int32_t MapId)
{
	auto it = m_UltimateChallengeCfgMap.find(MapId);
	if (it != m_UltimateChallengeCfgMap.end())
		return &it->second;
	return NULL;
}
#endif // replaced by hand-written version

//#####################################
void CfgData::InitVplanTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  const CDBCFile::FIELD *v5;
  CDBCFile VplanEveryRevard(0);
  CDBCFile VplanLevelRevard(0);
  CDBCFile VplanRevard(0);
  VplanReward stu;
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v13;
  std::string v14;
  VplanReward p_stu;
  MemChrBagVector v17;
  std::string v18;
  VplanLevelReward v20;
  MemChrBagVector v21;
  std::string v22;
  MemChrBagVector v24;
  std::string v25;
  VplanEveryDayReward v27;
  bool ret;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t VplanLeveTableCount;
  int32_t VplanLeveColumnCount;
  int32_t VplanEveryRevardTableCount;
  int32_t VplanEveryRevardColumnCount;
  int32_t i;
  int32_t i_0;
  int32_t i_1;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.Reward = __x;
        
        v2 = VplanRevard.Search_Posistion( i, 2);
        v14 = v2->pString;
        CItemHelper::parseItemVectorString(&v13, &v14);
        stu.YearVipReward = v13;
        
        p_stu = stu;
        m_CfgVplan.AddVplanReward(p_stu);


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
            stu.Index = VplanLevelRevard.Search_Posistion( i_0, 0)->iValue;
            *(&stu.Index + 1) = VplanLevelRevard.Search_Posistion( i_0, 1)->iValue;
            
            v3 = VplanLevelRevard.Search_Posistion( i_0, 2);
            v18 = v3->pString;
            CItemHelper::parseItemVectorString(&v17, &v18);
            stu.Reward = v17;
            
            VplanLevelReward::VplanLevelReward(&v20, (const VplanLevelReward *const)&stu);
            m_CfgVplan.AddVplanLevelReward(v20);

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
                stu.Index = VplanEveryRevard.Search_Posistion( i_1, 0)->iValue;
                *(&stu.Index + 1) = VplanEveryRevard.Search_Posistion( i_1, 1)->iValue;
                
                v4 = VplanEveryRevard.Search_Posistion( i_1, 2);
                v22 = v4->pString;
                CItemHelper::parseItemVectorString(&v21, &v22);
                stu.Reward = v21;
                
                v5 = VplanEveryRevard.Search_Posistion( i_1, 3);
                v25 = v5->pString;
                CItemHelper::parseItemVectorString(&v24, &v25);
                stu.YearVipReward = v24;
                
                VplanEveryDayReward::VplanEveryDayReward(&v27, (const VplanEveryDayReward *const)&stu);
                m_CfgVplan.AddVplanEveryDayReward(v27);

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

//#####################################

//#####################################
WingEquipPolish *CfgData::GetWingEquipPolishCfg(int32_t nType, int32_t nLevel)
{
	auto it = m_WingEquipPolishMap.find(std::make_pair(nType, nLevel));
	if (it != m_WingEquipPolishMap.end())
		return &it->second;
	return NULL;
}

//#####################################
AddAttrList CfgData::GetWingEquipPolishSuitAttr(int32_t nId)
{
	AddAttrList result;
	auto it = m_WingEquipPolishSuitMap.find(nId);
	if (it != m_WingEquipPolishSuitMap.end())
		result = it->second;
	return result;
}

//#####################################
WinRefiningCfg *CfgData::GetWingEquipRefiningCfg(int32_t nType, int32_t nLevel)
{
	auto it = m_WinRefiningCfgMap.find(std::make_pair(nType, nLevel));
	if (it != m_WinRefiningCfgMap.end())
		return &it->second;
	return NULL;
}

//#####################################
AddAttrList CfgData::GetWingEquipRefiningSuitAttr(int32_t nId)
{
	AddAttrList result;
	auto it = m_WinRefiningSuitMap.find(nId);
	if (it != m_WinRefiningSuitMap.end())
		result = it->second;
	return result;
}

//#####################################

//#####################################
void CfgData::InitWuHunCreateTable()
{
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  const CDBCFile::FIELD *v3;
  const CDBCFile::FIELD *v4;
  CreateWuHun *v5;
  CDBCFile TabFile(0);
  CreateWuHun stu;
  std::list<ItemData> strItems;
  std::list<RateItem> v12;
  _BYTE v13[15];
  std::string strItem;
  std::list<RateItem> v17;
  _BYTE v18[14];
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
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
        stu.nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nIndex += 2;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        std::string bCombi(v1->pString);
        CItemHelper::parseItemDataListString(&strItems, (bool)bCombi);
        stu.ConstItem = strItems;
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        std::string v13(v2->pString);
        CItemHelper::parseRateItemDataListString(&v12);
        stu.GetItemRate = v12;
        
        ++nIndex;
        nIndex += 3;
        
        v3 = TabFile.Search_Posistion( i, nIndex);
        strItem = v3->pString;
        v25 = CItemHelper::parseItemDataString(&strItem);
        v6 = v25.m_nId;
        BYTE4(v6) = v25.m_nClass;
        *(_QWORD *)&stu.SpecialCost.m_nId = v6;
        stu.SpecialCost.m_nCount = v25.m_nCount;
        
        ++nIndex;
        
        v4 = TabFile.Search_Posistion( i, nIndex);
        std::string v18(v4->pString);
        CItemHelper::parseRateItemDataListString(&v17);
        stu.GetItemRate2 = v17;
        
        ++nIndex;
        v5 = std::map<int,CreateWuHun>::operator[](&this->m_CreateWuHunMap, &stu.nId);
        CreateWuHun::operator=(v5, &stu);

      }
    }
  }
}

//#####################################
CreateWuHun *CfgData::GetCreateWuHun(int32_t nId)
{
	auto it = m_CreateWuHunMap.find(nId);
	if (it != m_CreateWuHunMap.end())
		return &it->second;
	return NULL;
}

//#####################################

//#####################################
WuHunItem *CfgData::GetWuHunItem(int32_t nId)
{
	auto it = m_WuHunItemMap.find(nId);
	if (it != m_WuHunItemMap.end())
		return &it->second;
	return NULL;
}

//#####################################

//#####################################
#if 0 // replaced by hand-written version at end of file
CfgWuHunShopList CfgData::GetWuHunShopItemList(int32_t ShopId)
{
	CfgWuHunShopList result;
	auto it = m_CfgWuHunShopMap.find(ShopId);
	if (it != m_CfgWuHunShopMap.end())
		result = it->second;
	return result;
}
#endif // replaced by hand-written version

#if 0 // replaced by hand-written version at end of file
//#####################################
CfgWuHunShop *CfgData::GetWuHunShopItem(int32_t nIndex)
{
	auto it = m_CfgWuHunShopItemMap.find(nIndex);
	if (it != m_CfgWuHunShopItemMap.end())
		return &it->second;
	return NULL;
}
#endif // replaced by hand-written version

//#####################################
void CfgData::InitXianYaoTaskTable()
{
  CDBCFile readFile(0);
  XiangYaoTaskCfg stu;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;

  
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
	Int32Int32Map TaskIdRate;
	int32_t MaxRate = 0;
	int32_t SpareId = 0;

	auto it = m_XiangYaoTaskCfgList.begin();
	if (it != m_XiangYaoTaskCfgList.end())
		SpareId = it->TaskId;

	while (it != m_XiangYaoTaskCfgList.end())
	{
		if (it->MinLevel <= Level && it->MaxLevel >= Level)
		{
			if (!bBest || it->Star == 4)
			{
				TaskIdRate[it->TaskId] = it->Rate;
				MaxRate += it->Rate;
			}
		}
		++it;
	}

	if (MaxRate > 0)
	{
		auto* rand = Answer::Singleton<Answer::Random>::instance();
		int32_t nRand = rand->generate(1, MaxRate);
		for (auto itMap = TaskIdRate.begin(); itMap != TaskIdRate.end(); ++itMap)
		{
			if (itMap->second >= nRand)
				return itMap->first;
			nRand -= itMap->second;
		}
	}

	return SpareId;
}

//#####################################
int32_t CfgData::getXiangYaoStart(int32_t TaskId)
{
	auto it = m_XiangYaoTaskMap.find(TaskId);
	if (it != m_XiangYaoTaskMap.end())
		return it->second.nStart;
	return 0;
}

//#####################################

//#####################################
void CfgData::InitXunLeiTable()
{
  const CDBCFile::FIELD *v1;
  XunLeiCfg *v2;
  CDBCFile TabFile(0);
  XunLeiCfg stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.vRewards = __x;
        
        stu.nCondition = TabFile.Search_Posistion( i, 5)->iValue;
        v2 = std::map<int,XunLeiCfg>::operator[](&this->m_XunLeiCfgMap, &stu.nIndex);
        XunLeiCfg::operator=(v2, &stu);

      }
    }
  }
}

//#####################################
XunLeiCfg *CfgData::GetXunLeiCfg(int32_t nIndex)
{
	auto it = m_XunLeiMap.find(nIndex);
	if (it != m_XunLeiMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitYYDaTing()
{
  const CDBCFile::FIELD *v1;
  CfgYYGameApp *v2;
  CDBCFile TabFile(0);
  CfgYYGameApp stu;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;

  
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
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, 1)->iValue;
        
        v1 = TabFile.Search_Posistion( i, 3);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.Rewards = __x;
        
        stu.nCondition = TabFile.Search_Posistion( i, 4)->iValue;
        v2 = std::map<int,CfgYYGameApp>::operator[](&this->m_CfgYYGameAppMap, &stu.nIndex);
        CfgYYGameApp::operator=(v2, &stu);

      }
    }
  }
}

//#####################################
CfgYYGameApp *CfgData::GetYYGameApp(int32_t nIndex)
{
	auto it = m_YYGameAppMap.find(nIndex);
	if (it != m_YYGameAppMap.end())
		return &it->second;
	return NULL;
}

//#####################################
void CfgData::InitYYVip()
{
  int v1; // ebx
  const CDBCFile::FIELD *v2;
  CfgYYVip *v3;
  int v4; // ebx
  CDBCFile TabFile(0);
  CfgYYVip stu;
  CfgYYSuperBuff stu_1;
  CfgYYSuperBuff stu_0;
  MemChrBagVector __x;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t iBaseTableCount_0;
  int32_t iBaseColumnCount_0;
  int32_t i_0;
  int32_t iBaseTableCount_1;
  int32_t iBaseColumnCount_1;
  int32_t i_1;

  
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
        stu.nIndex = TabFile.Search_Posistion( i, 0)->iValue;
        stu.nType = TabFile.Search_Posistion( i, 1)->iValue;
        
        v2 = TabFile.Search_Posistion( i, 3);
        strItems = v2->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        stu.Rewards = __x;
        
        stu.nCondition = TabFile.Search_Posistion( i, 4)->iValue;
        stu.nPric = TabFile.Search_Posistion( i, 5)->iValue;
        stu.nLimit = TabFile.Search_Posistion( i, 6)->iValue;
        v3 = std::map<int,CfgYYVip>::operator[](&this->m_CfgYYVipMap, &stu.nIndex);
        CfgYYVip::operator=(v3, &stu);

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
          memset(&stu_0.SuperVipLevel, 0, sizeof(int64_t));
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
            memset(&stu_1.SuperVipLevel, 0, sizeof(int64_t));
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
	auto it = m_YYVipMap.find(nIndex);
	if (it != m_YYVipMap.end())
		return &it->second;
	return NULL;
}

//#####################################
const CfgYYSuperBuff *CfgData::GetSuperBuff(int32_t SuperLevel)
{
  std::_List_const_iterator<CfgYYSuperBuff> iter;
  std::_List_const_iterator<CfgYYSuperBuff> __x;

  for (iter = m_CfgYYSuperBuffList.begin();
        std::_List_const_iterator<CfgYYSuperBuff>::operator++(&iter) )
  {
    __x = m_CfgYYSuperBuffList.end();
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
  const CDBCFile::FIELD *v1;
  const CDBCFile::FIELD *v2;
  CDBCFile TabFile(0);
  CfgTencentGift year;
  CfgTencentGift daily;
  MemChrBagVector __x;
  std::string strItems;
  MemChrBagVector v9;
  std::string v10;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;
  int32_t nLevel;

  
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
        nId = TabFile.Search_Posistion( i, nIndex++)->iValue;
        nLevel = TabFile.Search_Posistion( i, nIndex++)->iValue;
        
        v1 = TabFile.Search_Posistion( i, nIndex);
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&__x, &strItems);
        daily.vRewards = __x;
        
        ++nIndex;
        
        v2 = TabFile.Search_Posistion( i, nIndex);
        v10 = v2->pString;
        CItemHelper::parseItemVectorString(&v9, &v10);
        year.vRewards = v9;
        
        ++nIndex;
        daily.nLevel = nLevel;
        year.nLevel = nLevel;
        m_cfgTencentTable.AddYellowDailyGift(daily);
        m_cfgTencentTable.AddYellowYearGift(year);
        CfgTencentGift::~CfgTencentGift(&year);
        CfgTencentGift::~CfgTencentGift(&daily);
      }
    }
  }
}

//#####################################

//#####################################
void CfgData::InitYellowRewardTable()
{
  const CDBCFile::FIELD *v1;
  CDBCFile TabFile(0);
  MemChrBagVector vReward;
  std::string strItems;
  int32_t iBaseTableCount;
  int32_t iBaseColumnCount;
  int32_t i;
  int32_t nIndex;
  int32_t nId;

  
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
        strItems = v1->pString;
        CItemHelper::parseItemVectorString(&vReward, &strItems);
        
        ++nIndex;
        m_cfgTencentTable.SetYellowNewerGift(vReward);
      }
    }
  }
}

//#####################################

#endif // end #if 0 — all good Init functions are before line 8061

// ===== New API convenience methods (hand-written) =====

const CfgEquipStrengthen* CfgData::GetEquipStrengthen(int32_t nPos, int32_t nLevel) const
{
    return m_cfgEquipStrengthen.Get(nPos, nLevel);
}

const CfgEquipUpPos* CfgData::GetEquipUpPos(int32_t nPos, int32_t nLevel) const
{
    return m_cfgEquipUpPos.Get(nPos, nLevel);
}

const GoblinCfg* CfgData::GetGoblinCfg(int32_t nType, int32_t nLevel) const
{
    std::map<std::pair<int32_t, int32_t>, GoblinCfg>::const_iterator it =
        m_GoblinCfgMap.find(std::make_pair(nType, nLevel));
    if (it != m_GoblinCfgMap.end())
        return &it->second;
    return NULL;
}

const VipEQuipPosSuit* CfgData::GetVipEQuipPosSuit(int32_t nSuitId) const
{
    VipEQuipPosSuitMap::const_iterator it = m_VipEQuipPosSuitList.find(nSuitId);
    if (it != m_VipEQuipPosSuitList.end())
        return &it->second;
    return NULL;
}

const CfgWuHunShop* CfgData::GetWuHunShopItem(int32_t nIndex) const
{
    std::map<int32_t, CfgWuHunShop>::const_iterator it = m_CfgWuHunShopItemMap.find(nIndex);
    if (it != m_CfgWuHunShopItemMap.end())
        return &it->second;
    return NULL;
}

CfgWuHunShopList CfgData::GetWuHunShopItemList() const
{
    CfgWuHunShopList result;
    for (std::map<int32_t, CfgWuHunShop>::const_iterator it = m_CfgWuHunShopItemMap.begin();
         it != m_CfgWuHunShopItemMap.end(); ++it)
    {
        result.push_back(it->second);
    }
    return result;
}

CfgJueWeiTable* CfgData::GetJueWeiTable()
{
    return &m_cfgJueWeiTable;
}

const UltimateChallengeCfg* CfgData::GetUltimateChallengeCfg(int32_t nLevel) const
{
    UltimateChallengeCfgMap::const_iterator it = m_UltimateChallengeCfgMap.find(nLevel);
    if (it != m_UltimateChallengeCfgMap.end())
        return &it->second;
    return NULL;
}

const RefreshMonsterCfgList& CfgData::GetRefreshMonsterCfgList() const
{
    // Return first available list, or empty static list
    if (!m_RefreshMonsterCfgListMap.empty())
        return m_RefreshMonsterCfgListMap.begin()->second;
    static RefreshMonsterCfgList emptyList;
    return emptyList;
}

// ===== 2019 Version Config Table Implementations =====

void CfgData::InitGuiGuDaoRenTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/TaoistTask.txt"))
	{
		LOG_ERROR("open FILE_GUI_GU_DAO_REN_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	m_GuiGuDaoRenCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		GuiGuDaoRenCfg stu;
		memset(&stu, 0, sizeof(stu));
		int32_t nIndex = 0;

		stu.nNpcId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nMaxCount = TabFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse RefreshMonster string
		std::string strRefreshMonster = TabFile.Search_Posistion(i, nIndex++)->pString;
		StringVector SplitStr = StringUtility::split(strRefreshMonster, "|");
		for (auto& str : SplitStr)
		{
			StringVector vstr = StringUtility::split(str, ":");
			if (vstr.size() == 4)
			{
				RefreshMonster tmp;
				tmp.nCount = atoi(vstr[0].c_str());
				tmp.BossId = atoi(vstr[1].c_str());
				tmp.AliveTime = atoi(vstr[2].c_str());
				tmp.GongGaoId = atoi(vstr[3].c_str());
				stu.lRefreshMonster.push_back(tmp);
			}
		}

		// Parse 3 item data entries
		for (int32_t j = 0; j < 3; ++j)
		{
			std::string strItem = TabFile.Search_Posistion(i, nIndex++)->pString;
			ItemData itemData = CItemHelper::parseItemDataString(strItem);
			stu.vItemData.push_back(itemData);

			std::string strItem2 = TabFile.Search_Posistion(i, nIndex++)->pString;
			MemChrBag bagItem;
			CItemHelper::parseItemString(bagItem, strItem2);
			stu.vItem.push_back(bagItem);
		}

		// Parse MapId
		std::string strMapId = TabFile.Search_Posistion(i, nIndex++)->pString;
		Int32Vector vMapId;
		paraseInt32Vector(vMapId, strMapId, "./ServerConfig/Tables/TaoistTask.txt", 0);
		stu.vMapId = vMapId;

		m_GuiGuDaoRenCfgMap[stu.nNpcId] = stu;
	}
}

GuiGuDaoRenCfg* CfgData::GetGuiGuDaoRenCfg(int32_t nNpcId)
{
	auto it = m_GuiGuDaoRenMap.find(NpcId);
	if (it != m_GuiGuDaoRenMap.end())
		return &it->second;
	return NULL;
}

void CfgData::InitEquipBackTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/EquipRecovery.txt"))
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_BACK failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		EquipBack stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse EquipList
		std::string strEquipList = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strEquipList, "|");
		for (auto& str : vStr)
		{
			stu.nEquipList.push_back(atoi(str.c_str()));
		}

		stu.nRecovType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRecovValues = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nBuyBackType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nBuyBackValue = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nOpenDay = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLimitNum = readFile.Search_Posistion(i, nIndex++)->iValue;
		nIndex += 3; // skip 3 columns
		stu.nDisplayDay = readFile.Search_Posistion(i, nIndex++)->iValue;

		m_cfgEquip.AddEquipBack(&stu);
	}
}

void CfgData::InitEquipBackTask()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/EquipRecoveryTask.txt"))
	{
		LOG_ERROR("open FILE_EQUIP_BACK_TASK failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	m_EquipBackTaskCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		EquipBackTaskCfg stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nNeedCount = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRewardType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRewardCount = readFile.Search_Posistion(i, nIndex++)->iValue;

		m_EquipBackTaskCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitStrengthenTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/EquipStrengthen.txt"))
	{
		LOG_ERROR("open FILE_STRENGTHEN_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	m_EquipStrengthenCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		EquipStrengthenCfg stu;
		int32_t nIndex = 0;

		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nMoney = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attribute list
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_EquipStrengthenCfgMap[stu.nLevel] = stu;
	}
}

void CfgData::InitEquipBoxTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/EquipBox.txt"))
	{
		LOG_ERROR("open FILE_EQUIP_BOX_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	m_EquipBoxTable.m_map.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgEquipBox stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		for (int32_t j = 0; j < 5; ++j)
			stu.vEquipId[j] = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nBind = (int8_t)readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse star rate list
		std::string strStar = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strStar, "|");
		for (auto& str : vStr)
		{
			StringVector vParam = StringUtility::split(str, ":");
			if (vParam.size() == 2)
			{
				Param2 p;
				p.nParam1 = atoi(vParam[0].c_str());
				p.nParam2 = atoi(vParam[1].c_str());
				stu.lstStar.push_back(p);
			}
		}

		m_EquipBoxTable.m_map[stu.nId] = stu;
	}
}

const CfgEquipBoxTable* CfgData::GetEquipBoxTable() const
{
	return &m_EquipBoxTable;
}

void CfgData::InitGoldEggTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/GoldEgg.txt"))
	{
		LOG_ERROR("open FILE_GOLD_EGG_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	m_GoldEggTable.m_map.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgGoldEgg stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nGroupId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostGold = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nOpenTimes = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nStartDate = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nEndDate = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse items
		int32_t nItemCount = readFile.Search_Posistion(i, nIndex++)->iValue;
		for (int32_t j = 0; j < nItemCount; ++j)
		{
			CfgGoldEggItem item;
			item.nItemId = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nItemClass = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nItemCount = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nBind = (int8_t)readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nProbability = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nLimitTime = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nBroadcast = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nJob = (int8_t)readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nMinLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
			item.nMaxLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
			stu.lstItem.push_back(item);
		}

		m_GoldEggTable.m_map[stu.nId] = stu;
	}
}

const CfgGoldEggTable* CfgData::GetGoldEggTable() const
{
	return &m_GoldEggTable;
}

void CfgData::InitLimitTimeTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/LimitTime.txt"))
	{
		LOG_ERROR("open FILE_LIMIT_TIME_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_LimitTimeTable.m_map.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgLimitTime stu;
		stu.nId = readFile.Search_Posistion(i, 0)->iValue;
		stu.nTime = readFile.Search_Posistion(i, 1)->iValue;
		m_LimitTimeTable.m_map[stu.nId] = stu;
	}
}

const CfgLimitTimeTable* CfgData::GetLimitTimeTable() const
{
	return &m_LimitTimeTable;
}

void CfgData::InitTalentTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/Talent.txt"))
	{
		LOG_ERROR("open FILE_TALENT_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_TalentCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgTalent stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nPageId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostValue = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nNeedLevel = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_TalentCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitTalentPageTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/TalentPage.txt"))
	{
		LOG_ERROR("open FILE_TALENT_PAGE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_TalentPageCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgTalentPage stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostValue = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse talent list
		std::string strTalents = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strTalents, "|");
		for (auto& str : vStr)
			stu.vTalents.push_back(atoi(str.c_str()));

		m_TalentPageCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitTalentActiveTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/TalentActive.txt"))
	{
		LOG_ERROR("open FILE_TALENT_ACTIVE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_TalentActiveCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgTalentActive stu;
		stu.nId = readFile.Search_Posistion(i, 0)->iValue;
		stu.nType = readFile.Search_Posistion(i, 1)->iValue;
		stu.nParam = readFile.Search_Posistion(i, 2)->iValue;
		m_TalentActiveCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitTitleTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/Title.txt"))
	{
		LOG_ERROR("open FILE_TITLE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_TitleCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgTitle stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nTimeType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nTime = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}
		stu.nGongGaoId = readFile.Search_Posistion(i, nIndex++)->iValue;

		m_TitleCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitWingCfgTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/WingEquip.txt"))
	{
		LOG_ERROR("open FILE_WING_CFG_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_WingEquipCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgWingEquip stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nQuality = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostMoney = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostItem = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostCount = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_WingEquipCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitWingEquipPolish()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/WingPolish.txt"))
	{
		LOG_ERROR("open FILE_WING_EQUIP_POLISH failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_WingPolishCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgWingPolish stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostMoney = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostItem = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostCount = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_WingPolishCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitEquipBlessTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/EquipBless.txt"))
	{
		LOG_ERROR("open FILE_EQUIP_BLESS_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_EquipBlessMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgEquipBless stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostMoney = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_EquipBlessMap[stu.nId] = stu;
	}
}

void CfgData::InitDamnationTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/Damnation.txt"))
	{
		LOG_ERROR("open FILE_DAMNATION_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_DamnationCfgTable.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgDamnation stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostMoney = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse cost items
		std::string strCostItems = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vItems = StringUtility::split(strCostItems, "|");
		for (auto& str : vItems)
			stu.CostItems.push_back(atoi(str.c_str()));

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.AttrList.push_back(attr);
			}
		}

		stu.nHpPecent = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nProbability = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nGongGaoId = readFile.Search_Posistion(i, nIndex++)->iValue;

		m_DamnationCfgTable[stu.nId] = stu;
	}
}

DamnationCfg* CfgData::GetDamnationCfg(int32_t Level)
{
	auto it = m_DamnationCfgTable.find(Level);
	if (it != m_DamnationCfgTable.end())
		return &it->second;
	return NULL;
}

void CfgData::InitMingGeTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/MingGe.txt"))
	{
		LOG_ERROR("open FILE_MING_GE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_MingGeCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgMingGe stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostValue = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_MingGeCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitRongHeCfg()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/RongHe.txt"))
	{
		LOG_ERROR("open FILE_RONG_HE_CFG failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_RongHeCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		RongHeCfg stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostValue = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse reward items
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strItems, "|");
		for (auto& str : vStr)
		{
			MemChrBag bagItem;
			StringVector vItem = StringUtility::split(str, ":");
			if (vItem.size() >= 3)
			{
				bagItem.itemId = atoi(vItem[0].c_str());
				bagItem.itemClass = atoi(vItem[1].c_str());
				bagItem.itemCount = atoi(vItem[2].c_str());
				if (vItem.size() > 3)
					bagItem.bind = (int8_t)atoi(vItem[3].c_str());
				stu.vItem.push_back(bagItem);
			}
		}

		m_RongHeCfgMap[stu.nId] = stu;
	}
}

const RongHeCfg* CfgData::GetRongHeCfg(int32_t nIndex) const
{
	auto it = m_RongHeCfgMap.find(nIndex);
	return it != m_RongHeCfgMap.end() ? &it->second : nullptr;
}

void CfgData::InitEquipRongHeTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/EquipRongHe.txt"))
	{
		LOG_ERROR("open FILE_EQUIP_RONG_HE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_EquipRongHeCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		EquipRongHeCfg stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nDstEquipId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostMoney = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse source equip list
		std::string strSrc = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vSrc = StringUtility::split(strSrc, "|");
		for (auto& str : vSrc)
			stu.vSrcEquip.push_back(atoi(str.c_str()));

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_EquipRongHeCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitXingMaiTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/XingMai.txt"))
	{
		LOG_ERROR("open FILE_XING_MAI_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_XingMaiCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgXingMai stu;
		int32_t nIndex = 0;

		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostValue = readFile.Search_Posistion(i, nIndex++)->iValue;

		// Parse attributes
		std::string strAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		StringVector vStr = StringUtility::split(strAttr, "|");
		for (auto& str : vStr)
		{
			StringVector vAttr = StringUtility::split(str, ":");
			if (vAttr.size() == 2)
			{
				AddAttribute attr;
				attr.m_nAddAttrType = (uint8_t)atoi(vAttr[0].c_str());
				attr.m_nAddAttrValue = atoi(vAttr[1].c_str());
				stu.lAttrList.push_back(attr);
			}
		}

		m_XingMaiCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitXingMaiSlotTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/XingMaiSlot.txt"))
	{
		LOG_ERROR("open FILE_XING_MAI_SLOT_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	m_XingMaiSlotCfgMap.clear();
	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgXingMaiSlot stu;
		stu.nId = readFile.Search_Posistion(i, 0)->iValue;
		stu.nSlotIndex = readFile.Search_Posistion(i, 1)->iValue;
		stu.nNeedLevel = readFile.Search_Posistion(i, 2)->iValue;
		stu.nCostType = readFile.Search_Posistion(i, 3)->iValue;
		stu.nCostValue = readFile.Search_Posistion(i, 4)->iValue;
		m_XingMaiSlotCfgMap[stu.nId] = stu;
	}
}

const XingMaiCfg* CfgData::GetXingMaiCfg(int32_t nLevel) const
{
	auto it = m_XingMaiCfgMap.find(nLevel);
	return it != m_XingMaiCfgMap.end() ? &it->second : nullptr;
}

void CfgData::InitXinMoTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/XinMo.txt"))
	{
		LOG_ERROR("open FILE_XIN_MO_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgXinMo stu;
		stu.nId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nHp = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nAttack = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nDefence = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nHit = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nDodge = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCrit = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nTough = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nExp = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_XinMoCfgMap[stu.nId] = stu;
	}
}

// ===== 42 Missing Init Function Implementations =====

int32_t CfgData::InitXuWuTask(int32_t Level, int32_t Times)
{
	Int32Vector TaskIdVt;
	for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		if (it->second.type == 9
			&& it->second.level <= Level && it->second.max_level >= Level
			&& it->second.group == Times)
		{
			TaskIdVt.push_back(it->first);
		}
	}
	if (!TaskIdVt.empty())
	{
		std::random_shuffle(TaskIdVt.begin(), TaskIdVt.end());
		return TaskIdVt.front();
	}
	return 0;
}

int32_t CfgData::InitXinMoTask(int32_t Level, int32_t Times)
{
	Int32Vector TaskIdVt;
	for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		if (it->second.type == 42
			&& it->second.level <= Level && it->second.max_level >= Level
			&& it->second.group == Times)
		{
			TaskIdVt.push_back(it->first);
		}
	}
	if (!TaskIdVt.empty())
	{
		std::random_shuffle(TaskIdVt.begin(), TaskIdVt.end());
		return TaskIdVt.front();
	}
	return 0;
}

void CfgData::InitSpecialTreasureMapRandTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialTreasureMap.txt"))
	{
		LOG_ERROR("open FILE_SPECIAL_TREASURE_MAP_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		SpecialTreasureMapRandCfg stu;
		memset(&stu, 0, sizeof(stu));
		int32_t nIndex = 0;
		stu.nItemId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vGetItems, strItems);
		stu.nRate = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItem = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemString(stu.vShowItem, strItem);
		stu.nGongGaoId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SpecialTreasureMapRandCfgList.push_back(stu);
	}
}

void CfgData::InitDaZheQuanTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/ItemDiscount.txt"))
	{
		LOG_ERROR("open FILE_DA_ZHE_QUAN_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		DaZheQuan stu;
		memset(&stu, 0, sizeof(stu));
		int32_t nIndex = 0;
		stu.Index = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.CurrencyType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.CurrencyValues = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.Items, strItems);
		m_DaZheQuanMap[stu.Index] = stu;
	}
}

void CfgData::InitQQGameRewardTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/QQGameDaTing.txt"))
	{
		LOG_ERROR("open FILE_QQGAME_REWARD_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgQQGift gift;
		gift.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		gift.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		++nIndex; // skip column
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(gift.vReward, strItems);
		gift.nCondition = TabFile.Search_Posistion(i, ++nIndex)->iValue;
		m_cfgTencentTable.AddQQGameGift(gift);
	}
}

void CfgData::InitTGPDailyRewardTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/TGPEverydayReward.txt"))
	{
		LOG_ERROR("open FILE_TGP_DAILY_REWARD_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgTGPGift gift;
		memset(&gift, 0, sizeof(gift));
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		gift.strPF = strPF;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(gift.vReward, strItems);
		m_cfgTencentTable.AddTGPDailyGift(gift);
	}
}

void CfgData::InitTGPLevelRewardTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/TGPLevelReward.txt"))
	{
		LOG_ERROR("open FILE_TGP_LEVEL_REWARD_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgTGPGift gift;
		memset(&gift, 0, sizeof(gift));
		gift.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		gift.strPF = strPF;
		gift.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(gift.vReward, strItems);
		m_cfgTencentTable.AddTGPLevelGift(gift);
	}
}

void CfgData::InitPassiveSkillTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/SkillPassiveAttr.txt"))
	{
		LOG_ERROR("Open FILE_PASSIVE_SKILL_TABLE fail, please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgPassiveSkill stu;
		memset(&stu, 0, sizeof(stu));
		stu.id = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.type = readFile.Search_Posistion(i, nIndex++)->iValue;
		++nIndex; // skip name
		std::string addonAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(stu.vAttrs, addonAttr, i, "./ServerConfig/Tables/SkillPassiveAttr.txt");
		std::string talentStr = readFile.Search_Posistion(i, nIndex++)->pString;
		parseAddAttribues(stu.lTalentAddon, talentStr, i, "./ServerConfig/Tables/SkillPassiveAttr.txt");
		++nIndex;
		m_cfgSkillTable.AddPassiveSkill(stu);
	}
}

void CfgData::InitPetAttrTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/PetAttr.txt"))
	{
		LOG_ERROR("open FILE_PET_ATTR_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgPetData pet;
		pet.m_nPetId = readFile.Search_Posistion(i, nIndex++)->iValue;
		std::string addonAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(pet.m_vBaseAttr, addonAttr, i, "./ServerConfig/Tables/PetAttr.txt");
		m_cfgPetTable.AddAttr(pet);
	}
}

void CfgData::InitPetUpStarTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/PetUpStar.txt"))
	{
		LOG_ERROR("open FILE_PET_UP_STAR_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgPetUpStar stu;
		stu.nPetId = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nStar = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nNeedStar = readFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vCostItems, strItems);
		++nIndex;
		std::string addonAttr = readFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(stu.vAttrs, addonAttr, i, "./ServerConfig/Tables/PetUpStar.txt");
		std::string skillStr = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemString(stu.vSkill, skillStr);
		std::string skillLevelStr = readFile.Search_Posistion(i, nIndex++)->pString;
		parseIntVectorString(stu.vSkillLevel, skillLevelStr);
		++nIndex;
		stu.GongGaoId = readFile.Search_Posistion(i, ++nIndex)->iValue;
		nIndex += 4; // skip 3 + 1
		stu.nCostGold = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_cfgPetTable.AddPetUpStar(stu);
	}
}

void CfgData::InitMysteryGiftTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/MysteriousGift.txt"))
	{
		LOG_ERROR("open FILE_MYSTERY_GIFT_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgMysteryGift stu;
		stu.nIndex = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCondition = readFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vItem, strItems);
		nIndex += 4; // skip 3 + 1
		stu.nBroadId = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_cfgMysteryGiftTable.Add(stu);
	}
}

void CfgData::InitSuperMemberTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/SuperMember.txt"))
	{
		LOG_ERROR("open FILE_SUPER_MEMBER_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSuperMember stu;
		stu.nIndex = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_cfgSuperMember[stu.nIndex] = stu;
	}
}

void CfgData::InitSouGouSkinTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/SogouSkin.txt"))
	{
		LOG_ERROR("open FILE_SOUGOU_SKIN_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSouGouSkin stu;
		stu.nIndex = readFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = readFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = readFile.Search_Posistion(i, nIndex++)->iValue;
		m_cfgSouGouSkin[stu.nIndex] = stu;
	}
}

void CfgData::InitWeiXinTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/WeiXin.txt"))
	{
		LOG_ERROR("open FILE_WEI_XIN_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgWeiXingGift stu;
		memset(&stu, 0, sizeof(stu));
		int32_t nIndex = 0;
		std::string strPF = readFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		stu.nIconId = readFile.Search_Posistion(i, nIndex++)->iValue;
		nIndex += 3; // skip 3 columns
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		m_cfgWeiXinTable.Add(stu);
	}
}

void CfgData::InitAdultGiftTable()
{
	CDBCFile readFile;
	if (!readFile.OpenFromTXT("./ServerConfig/Tables/ShenFenYanZheng.txt"))
	{
		LOG_ERROR("open FILE_ADULT_GIFT_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = readFile.GetRecordsNum();
	int32_t iBaseColumnCount = readFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgAdultGift stu;
		memset(&stu, 0, sizeof(stu));
		int32_t nIndex = 1; // skip column 0
		std::string strItems = readFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		std::string strPF = readFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		stu.nIconId = readFile.Search_Posistion(i, nIndex++)->iValue;
		++nIndex;
		m_cfgAdultGiftTable.Add(stu);
	}
}

void CfgData::InitBlacketMarketTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/BlackMarket.txt"))
	{
		LOG_ERROR("open FILE_BLACKET_MARKET_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgBlacketMarket stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vItem, strItems);
		stu.nPrice = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_BlacketMarketTable[stu.nIndex] = stu;
	}
}

void CfgData::InitSpeed360Reward()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/Speed360Reward.txt"))
	{
		LOG_ERROR("open FILE_SPEED_360_REWARD failed,please check!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		std::string strStart = TabFile.Search_Posistion(i, 1)->pString;
		m_Speed360Reward.StartTime = DayTime::StringToIntTime(strStart);
		std::string strEnd = TabFile.Search_Posistion(i, 2)->pString;
		m_Speed360Reward.EndTime = DayTime::StringToIntTime(strEnd);
		std::string strItems = TabFile.Search_Posistion(i, 4)->pString;
		CItemHelper::parseItemVectorString(m_Speed360Reward.Rewards, strItems);
	}
}

void CfgData::InitShunWangTable()
{
	// File 1: ShunWangHuiYuan.txt
	CDBCFile SwVip;
	if (!SwVip.OpenFromTXT("./ServerConfig/Tables/ShunWangHuiYuan.txt"))
	{
		LOG_ERROR("open FILE_SW_VIP_REWARD failed,please check!!\n");
		return;
	}

	int32_t count = SwVip.GetRecordsNum();
	int32_t cols = SwVip.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgSwVipReward stu;
			memset(&stu, 0, sizeof(stu));
			stu.nIndex = SwVip.Search_Posistion(i, nIndex++)->iValue;
			stu.nType = SwVip.Search_Posistion(i, nIndex++)->iValue;
			++nIndex; // skip
			std::string strItems = SwVip.Search_Posistion(i, nIndex++)->pString;
			CItemHelper::parseItemVectorString(stu.vReward, strItems);
			stu.nCondition = SwVip.Search_Posistion(i, ++nIndex)->iValue;
			m_CfgVplan.AddSwVipReward(stu);
		}
	}

	// File 2: ShunWangWangBa.txt
	CDBCFile SwBarVip;
	if (!SwBarVip.OpenFromTXT("./ServerConfig/Tables/ShunWangWangBa.txt"))
	{
		LOG_ERROR("open FILE_SW_BAR_VIP_REWARD failed,please check!!\n");
		return;
	}

	count = SwBarVip.GetRecordsNum();
	cols = SwBarVip.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgSwVipReward stu;
			memset(&stu, 0, sizeof(stu));
			stu.nIndex = SwBarVip.Search_Posistion(i, nIndex++)->iValue;
			stu.nType = SwBarVip.Search_Posistion(i, nIndex++)->iValue;
			++nIndex;
			std::string strItems = SwBarVip.Search_Posistion(i, nIndex++)->pString;
			CItemHelper::parseItemVectorString(stu.vReward, strItems);
			stu.nCondition = SwBarVip.Search_Posistion(i, ++nIndex)->iValue;
			m_CfgVplan.AddSwVipBarReward(stu);
		}
	}

	// File 3: ShunWangVIPBuff.txt
	CDBCFile SwVipBuff;
	if (!SwVipBuff.OpenFromTXT("./ServerConfig/Tables/ShunWangVIPBuff.txt"))
	{
		LOG_ERROR("open FILE_SW_VIP_BUFF failed,please check!!\n");
		return;
	}

	count = SwVipBuff.GetRecordsNum();
	cols = SwVipBuff.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgSwVipBuff stu;
			stu.nIndex = SwVipBuff.Search_Posistion(i, nIndex++)->iValue;
			stu.nType = SwVipBuff.Search_Posistion(i, nIndex++)->iValue;
			std::string strAttr = SwVipBuff.Search_Posistion(i, nIndex++)->pString;
			parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/ShunWangVIPBuff.txt");
			stu.nLevel = SwVipBuff.Search_Posistion(i, nIndex++)->iValue;
			m_CfgVplan.AddSwVipBuff(stu);
		}
	}
}

void CfgData::InitScoreShopTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/ScoreShop.txt"))
	{
		LOG_ERROR("open FILE_SCORE_SHOP_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgScoreShop stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vItem, strItems);
		stu.nScore = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLimitCount = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_ScoreShopTable[stu.nIndex] = stu;
	}
}

void CfgData::InitSpeciaEquipCfgMap()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialEquip.txt"))
	{
		LOG_ERROR("open FILE_SPECIAL_EQUIP_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSpecialEquip stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nPos = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strAttr = TabFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/SpecialEquip.txt");
		stu.nSuitId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SpeciaEquipCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitSpeciaSkillDistanceTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/SkillSpecialDamage.txt"))
	{
		LOG_ERROR("open FILE_SPECIA_SKILL_DISTANCE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSpeciaSkillDistance stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nSkillId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nDistance = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nDamage = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SpeciaSkillDistanceMap[stu.nId] = stu;
	}
}

void CfgData::InitLevelRefiningTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/LvRefining.txt"))
	{
		LOG_ERROR("open FILE_LEVEL_REFINING_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgLevelRefining stu;
		stu.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strAttr = TabFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/LvRefining.txt");
		stu.nCostGold = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostItem = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostCount = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_LevelRefiningMap[stu.nLevel] = stu;
	}
}

void CfgData::InitCachetCfg()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/Cachet.txt"))
	{
		LOG_ERROR("open FILE_CACHET_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgCachet stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nPos = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strAttr = TabFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/Cachet.txt");
		stu.nCostGold = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostItem = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostCount = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_CachetCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitSystemOpenReward()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/System.txt"))
	{
		LOG_ERROR("open FILE_SYSTEM_OPEN_REWARD failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSystemOpenReward stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		m_SystemOpenRewardMap[stu.nId] = stu;
	}
}

void CfgData::InitSpecialMap()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/SpecialMap.txt"))
	{
		LOG_ERROR("open FILE_SPECIAL_MAP_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSpecialMap stu;
		stu.nMapId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nEnterCount = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostValue = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SpecialMapTable[stu.nMapId] = stu;
	}
}

void CfgData::InitTestServerReward()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/TestActivity.txt"))
	{
		LOG_ERROR("open FILE_TEST_SERVER_REWARD_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgTestServerReward stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_TestServerRewardMap[stu.nIndex] = stu;
	}
}

void CfgData::InitShenWeiTaskTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/ShenWeiTask.txt"))
	{
		LOG_ERROR("open FILE_SHEN_WEI_TASK_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgShenWeiTask stu;
		stu.nTaskId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		m_ShenWeiTaskTable[stu.nTaskId] = stu;
	}
}

void CfgData::InitMobilePhoneGiftTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/ShouJi.txt"))
	{
		LOG_ERROR("open FILE_MOBILE_PHONE_GIFT_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		CfgMobilePhoneGift stu;
		memset(&stu, 0, sizeof(stu));
		int32_t nIndex = 0;
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		stu.nIconId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		nIndex += 3; // skip 3 columns
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		m_MobilePhoneGiftTable.Add(stu);
	}
}

void CfgData::InitSuperTeHuiTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/SuperDiscount.txt"))
	{
		LOG_ERROR("open FILE_SUPER_TE_HUI_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSuperTeHui stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vItem, strItems);
		stu.nPrice = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SuperTeHuiTable[stu.nIndex] = stu;
	}
}

void CfgData::InitShouHuRefining()
{
	// File 1: StarSpaceLevel.txt
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/StarSpaceLevel.txt"))
	{
		LOG_ERROR("open FILE_SHOU_HU_REFINING_LEVEL failed,please check!!!\n");
		return;
	}

	int32_t count = TabFile.GetRecordsNum();
	int32_t cols = TabFile.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgShouHuRefiningLevel stu;
			stu.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
			std::string strAttr = TabFile.Search_Posistion(i, nIndex++)->pString;
			parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/StarSpaceLevel.txt");
			stu.nCostGold = TabFile.Search_Posistion(i, nIndex++)->iValue;
			m_ShouHuRefiningLevelMap[stu.nLevel] = stu;
		}
	}

	// File 2: StarSpaceSuit.txt
	CDBCFile TabFile2;
	if (!TabFile2.OpenFromTXT("./ServerConfig/Tables/StarSpaceSuit.txt"))
	{
		LOG_ERROR("open FILE_SHOU_HU_REFINING_SUIT failed,please check!!!\n");
		return;
	}

	count = TabFile2.GetRecordsNum();
	cols = TabFile2.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgShouHuRefiningSuit stu;
			stu.nSuitId = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			stu.nCount = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			std::string strAttr = TabFile2.Search_Posistion(i, nIndex++)->pString;
			parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/StarSpaceSuit.txt");
			m_ShouHuRefiningSuitMap[stu.nSuitId] = stu;
		}
	}
}

void CfgData::InitShiZhuangTable()
{
	// File 1: ShiZhuang.txt
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuang.txt"))
	{
		LOG_ERROR("open FILE_SHI_ZHUANG_TABLE failed,please check!!!\n");
		return;
	}

	int32_t count = TabFile.GetRecordsNum();
	int32_t cols = TabFile.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgShiZhuang stu;
			stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
			stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
			std::string strAttr = TabFile.Search_Posistion(i, nIndex++)->pString;
			parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/ShiZhuang.txt");
			stu.nSuitId = TabFile.Search_Posistion(i, nIndex++)->iValue;
			m_ShiZhuangTable[stu.nId] = stu;
		}
	}

	// File 2: ShiZhuangSuit.txt
	CDBCFile TabFile2;
	if (!TabFile2.OpenFromTXT("./ServerConfig/Tables/ShiZhuangSuit.txt"))
	{
		LOG_ERROR("open FILE_SHI_ZHUANG_SUIT_TABLE failed,please check!!!\n");
		return;
	}

	count = TabFile2.GetRecordsNum();
	cols = TabFile2.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgShiZhuangSuit stu;
			stu.nSuitId = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			stu.nCount = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			std::string strAttr = TabFile2.Search_Posistion(i, nIndex++)->pString;
			parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/ShiZhuangSuit.txt");
			m_ShiZhuangSuitTable[stu.nSuitId] = stu;
		}
	}
}

void CfgData::InitMonthlyChouJiangTable()
{
	// File 1: TurntableReward.txt
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/TurntableReward.txt"))
	{
		LOG_ERROR("open FILE_MONTHLY_CHOU_JIANG_TABLE failed,please check!!!\n");
		return;
	}

	int32_t count = TabFile.GetRecordsNum();
	int32_t cols = TabFile.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgMonthlyChouJiang stu;
			stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
			stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
			std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
			CItemHelper::parseItemVectorString(stu.vReward, strItems);
			stu.nRate = TabFile.Search_Posistion(i, nIndex++)->iValue;
			m_MonthlyChouJiangTable[stu.nIndex] = stu;
		}
	}

	// File 2: TurntableRechargePoint.txt
	CDBCFile TabFile2;
	if (!TabFile2.OpenFromTXT("./ServerConfig/Tables/TurntableRechargePoint.txt"))
	{
		LOG_ERROR("open FILE_MONTHLY_CHOU_JIANG_RECHARGE failed,please check!!!\n");
		return;
	}

	count = TabFile2.GetRecordsNum();
	cols = TabFile2.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgMonthlyChouJiangRecharge stu;
			stu.nIndex = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			stu.nPoint = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			m_MonthlyChouJiangRechargeMap[stu.nIndex] = stu;
		}
	}
}

void CfgData::InitOutLinkFestivalTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/OutLinkFestival.txt"))
	{
		LOG_ERROR("open FILE_OUT_LINK_FESTIVAL_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgOutLinkFestival stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_OutLinkFestivalTable[stu.nIndex] = stu;
	}
}

void CfgData::InitSouGouDaTing()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/SouGouDaTing.txt"))
	{
		LOG_ERROR("open FILE_SOUGOU_DATING_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSouGouDaTing stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SouGouDaTingTable[stu.nIndex] = stu;
	}
}

void CfgData::InitPlatformDaTingMap()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/DaTing.txt"))
	{
		LOG_ERROR("open FILE_PLATFORM_DATING_MAP failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgPlatformDaTing stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		stu.nIconId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		m_PlatformDaTingMap[stu.nIndex] = stu;
	}
}

void CfgData::InitPlatformVipMap()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/OutLinkVip.txt"))
	{
		LOG_ERROR("open FILE_PLATFORM_VIP_MAP failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgPlatformVip stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		stu.nVipLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_PlatformVipMap[stu.nIndex] = stu;
	}
}

void CfgData::InitPlatformReward()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/Reward.txt"))
	{
		LOG_ERROR("open FILE_PLATFORM_REWARD failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgPlatformReward stu;
		stu.nIndex = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strPF = TabFile.Search_Posistion(i, nIndex++)->pString;
		stu.strPlatform = strPF;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_PlatformRewardMap[stu.nIndex] = stu;
	}
}

void CfgData::InitShangRenCfgMap()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/MagicBusiness.txt"))
	{
		LOG_ERROR("open FILE_SHANG_REN_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgShangRen stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vItem, strItems);
		stu.nPrice = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nRate = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_ShangRenCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitSelectItemCfgMap()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/GiftChoose.txt"))
	{
		LOG_ERROR("open FILE_SELECT_ITEM_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgSelectItem stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vItem, strItems);
		stu.nGongGaoId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_SelectItemCfgMap[stu.nId] = stu;
	}
}

void CfgData::InitGuardPrivilegeTable()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/GuardPrivilegeReward.txt"))
	{
		LOG_ERROR("open FILE_GUARD_PRIVILEGE_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgGuardPrivilege stu;
		stu.nIndex = (int8_t)TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nType = (int8_t)TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nDaily = (int8_t)TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
		CItemHelper::parseItemVectorString(stu.vReward, strItems);
		stu.nParam = TabFile.Search_Posistion(i, nIndex++)->iValue;
		m_GuardPrivilegeMap[stu.nIndex] = stu;
	}
}

void CfgData::InitShiZhuLevelUp()
{
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/ShiZhuangUpGrade.txt"))
	{
		LOG_ERROR("open FILE_SHI_ZHU_LEVEL_UP_TABLE failed,please check!!!\n");
		return;
	}

	int32_t iBaseTableCount = TabFile.GetRecordsNum();
	int32_t iBaseColumnCount = TabFile.GetFieldsNum();
	if (iBaseColumnCount <= 0) return;

	for (int32_t i = 0; i < iBaseTableCount; ++i)
	{
		int32_t nIndex = 0;
		CfgShiZhuLevelUp stu;
		stu.nId = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nLevel = TabFile.Search_Posistion(i, nIndex++)->iValue;
		stu.nCostGold = TabFile.Search_Posistion(i, nIndex++)->iValue;
		std::string strAttr = TabFile.Search_Posistion(i, nIndex++)->pString;
		parseAttrAddon(stu.vAttr, strAttr, i, "./ServerConfig/Tables/ShiZhuangUpGrade.txt");
		m_ShiZhuLevelUpMap[stu.nId] = stu;
	}
}

void CfgData::InitNationalDayTask()
{
	// File 1: PassportTask.txt
	CDBCFile TabFile;
	if (!TabFile.OpenFromTXT("./ServerConfig/Tables/PassportTask.txt"))
	{
		LOG_ERROR("open FILE_NATIONAL_DAY_TASK_TABLE failed,please check!!!\n");
		return;
	}

	int32_t count = TabFile.GetRecordsNum();
	int32_t cols = TabFile.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgNationalDayTask stu;
			stu.nTaskId = TabFile.Search_Posistion(i, nIndex++)->iValue;
			stu.nType = TabFile.Search_Posistion(i, nIndex++)->iValue;
			stu.nCondition = TabFile.Search_Posistion(i, nIndex++)->iValue;
			std::string strItems = TabFile.Search_Posistion(i, nIndex++)->pString;
			CItemHelper::parseItemVectorString(stu.vReward, strItems);
			stu.nPoint = TabFile.Search_Posistion(i, nIndex++)->iValue;
			m_NationalDayTaskTable[stu.nTaskId] = stu;
		}
	}

	// File 2: Passport.txt
	CDBCFile TabFile2;
	if (!TabFile2.OpenFromTXT("./ServerConfig/Tables/Passport.txt"))
	{
		LOG_ERROR("open FILE_NATIONAL_DAY_PASSPORT_TABLE failed,please check!!!\n");
		return;
	}

	count = TabFile2.GetRecordsNum();
	cols = TabFile2.GetFieldsNum();
	if (cols > 0)
	{
		for (int32_t i = 0; i < count; ++i)
		{
			int32_t nIndex = 0;
			CfgNationalDayPassport stu;
			stu.nLevel = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			stu.nPoint = TabFile2.Search_Posistion(i, nIndex++)->iValue;
			std::string strItems = TabFile2.Search_Posistion(i, nIndex++)->pString;
			CItemHelper::parseItemVectorString(stu.vReward, strItems);
			std::string strVipItems = TabFile2.Search_Posistion(i, nIndex++)->pString;
			CItemHelper::parseItemVectorString(stu.vVipReward, strVipItems);
			m_NationalDayPassportTable[stu.nLevel] = stu;
		}
	}
}

// ===== LuckDropTable Methods =====

LuckDropTable::LuckDropTable()
{
	m_LuckDropMap.clear();
}

void LuckDropTable::AddLuckDrop( LuckDrop* p_stu )
{
	std::pair<int,int> key = std::make_pair( p_stu->Type, p_stu->VipLevel );
	m_LuckDropMap[key] = *p_stu;
}

int32_t LuckDropTable::GetLuckRate( int32_t Type, int32_t VipLevel ) const
{
	std::pair<int,int> key = std::make_pair( Type, VipLevel );
	std::map<std::pair<int,int>, LuckDrop>::const_iterator it = m_LuckDropMap.find( key );
	if ( it != m_LuckDropMap.end() )
		return it->second.Rate;
	return 0;
}

void LuckDropTable::GetItem( MemChrBag* pItem, int32_t Type, int32_t VipLevel ) const
{
	if ( !pItem ) return;
	std::pair<int,int> key = std::make_pair( Type, VipLevel );
	std::map<std::pair<int,int>, LuckDrop>::const_iterator it = m_LuckDropMap.find( key );
	if ( it == m_LuckDropMap.end() )
		return;

	// 计算总概率
	int32_t MaxRate = 0;
	for ( SpecialItemDropList::const_iterator iter = it->second.ItemList.begin();
	      iter != it->second.ItemList.end(); ++iter )
	{
		MaxRate += iter->Rate;
	}

	if ( MaxRate <= 0 ) return;

	int32_t nRand = RANDOM->generate( 1, MaxRate );
	for ( SpecialItemDropList::const_iterator iter = it->second.ItemList.begin();
	      iter != it->second.ItemList.end(); ++iter )
	{
		if ( iter->Rate >= nRand )
		{
			pItem->itemId = iter->Item.itemId;
			pItem->itemClass = iter->Item.itemClass;
			pItem->itemCount = iter->Item.itemCount;
			pItem->bind = iter->Item.bind;
			return;
		}
		nRand -= iter->Rate;
	}
}

// ===== CfgData::GetLuckDropTableTable =====

LuckDropTable& CfgData::GetLuckDropTableTable()
{
	return m_LuckDropTable;
}
