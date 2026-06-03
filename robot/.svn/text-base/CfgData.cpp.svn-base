
#include "stdafx.h"
#include "Shared.h"
#include "CfgData.h"
#include "FileDef.h"
#include <algorithm>
#include <limits>

using namespace Answer;
using namespace std;


CfgData::CfgData()
	:  m_avgLevel(40), m_createTime(0), m_debug(0),m_startServerTime(0)
{
	m_offlineExpRegion.id = 0;
	m_memFamilyWar.family_id = 0;
	m_memFamilyWar.family_name = "";
}

CfgData::~CfgData()
{

}

bool CfgData::init()
{
	fetchServerConfig();
	//fetchActivity();
	//fetchcfExActivity();
	//fetchAnnoucementTime();
	fetchBuff();
	fetchDungeon();
	fetchDungeonEvent();
	fetchDungeonMonster();
	fetchDungeonPlant();
	fetchDungeonTrap();
	//fetchFamily();

	fetchItem(false);
	fetchJob();
	fetchLevelAttr();
	fetchMap();
	fetchMapMonster();
	fetchMapPlant();
	fetchBornAttr();
	fetchChrShop();
	fetchMapRegion();
	fetchMonster();
	fetchMonsterDropGroup();
	fetchMonsterGroupDrop();
	fetchMonsterTaskDrop();
	fetchNpc();
	//fetchMovie();
	//fetchChargeRewards();
	//fetchOnlineReward();
	fetchPlant();
	fetchSkill();
	fetchTask();
	//fetchTaskCycleGroup();
	fetchTrailer();
	fetchTrap();
	//fetchVip();
	fetchDaily();
	//fetchAchievement();
	fetchGamble();
	fetchLevelExp();
	//fetchLevelGift();
	//fetchLevelGold();
	//fetchSignReward();
	//fetchSevenLogin();
	//fetchNewServerActivity();
	//fetchYellowStone();					//初始化黄钻礼包

	InitEquipTable();
	InitEquipUpGradeTable();
	InitEquipUpQualityTable();
	InitEquipUpStarTable();
	InitEquipAddAttrTable();
	InitEquipGoalTable();
	InitEquipSuitTable();
	InitPetTable();
	//InitPetAttrInitRateTable();
	//InitPetIllusionTable();
	InitSkillLevelUpTable();
	//InitTaskCycleStarTable();
	//InitPetKnightTable();
	//InitFamilyTable();
	//InitFamilyPositionTable();
	//InitFamilyPetRegistTable();
	//InitCharPetHatchPoolTable();
	//InitPetLucyItemTable();
	//InitTeamBuffTable();

	InitItemGemTable();
	InitItemCombiTable();

	//InitMountHearAttrTable();			// 初始化坐骑之心属性表
	//InitMountSkillTable();				// 初始化坐骑技能表
	//InitMountSkillLevelUp();			// 初始化坐骑技能升级表
	//InitMountTrainTable();				// 初始化坐骑升阶表

	//InitBagSlotOpenTimeTable();			// 初始化背包开启时间表
	//InitFriendExpTable();				// 初始化好友经验表
	//InitPkDropRateTable();				// pk掉落比例
	//InitQiangHuaWorthTable();			// 强化价值
	//InitSysMail();						// 初始化系统邮件信息
	//InitBossInfo();						// 初始化boss信息
	//InitFaBaoTable();					// 初始化法宝信息表
	//InitBuyFaBaoResTable();				// 初始化购买法宝资源表
	//InitDaTiHD();						// 初始化答题活动
	//InitShangChengTable();				// 初始化商城表
	//InitPetGiftTable();					// 初始化幻宠礼包表

	return true;
}

int32_t  CfgData::getDailyItemID(int32_t type)
{
	CfgDailyItemTable::iterator it = m_dailyItems.find(type);
	if (it != m_dailyItems.end())
	{
		return it->second.id;
	}

	return 0;
}

CfgDailyItem* CfgData::getDailyItemMark(int32_t type,int32_t id)
{
	  if (id >0)
	  {
		  for (CfgDailyItemTable::iterator it = m_dailyItems.begin();it != m_dailyItems.end();++it)
		  {
			  if (it->second.id == id)
			  {
				  return &(it->second);
			  }
		  }
	  }
	  else 
	  {
		  CfgDailyItemTable::iterator it = m_dailyItems.find(type);
		  if (it != m_dailyItems.end())
		  {
			  return &(it->second);
		  }
	  }
	 
	  return NULL;
}

int32_t CfgData::getDailyReward(int32_t id,int32_t level)
{
	  int32_t value = 0;
	  int32_t Templevel = 0;
	  CfgDailyRewardTable::iterator it = m_dailyReward.find(id);
	  if (it != m_dailyReward.end())
	  {
		    for (CfgDailyRewardVector::iterator iter = it->second.begin();iter != it->second.end();++iter)
		    {
				  if (iter->level <= level &&  iter->level >= Templevel)
				  {
					  value = iter->value;
					  Templevel = iter->level;
				  }
		    }
	  }

	  return value;
}

int32_t  CfgData::getDailyMarkGiftID(int32_t mark)
{
	CfgDailyMarkTable::iterator it = m_dailyMark.find(mark);
	if (it != m_dailyMark.end())
	{
		return it->second.gift_id;
	}

	return 0;
}

CfgNewServerGold* CfgData::getNewServerGold(int32_t id)
{
	CfgNewServerGoldTable::iterator it = m_newServerGold.find(id);
	if (it != m_newServerGold.end())
	{
		return &(it->second);
	}

	return NULL;
}

CfgNewServerLater* CfgData::getNewServerLater(int32_t id)
{
	CfgNewServerLaterTable::iterator it = m_newServerLater.find(id);
	if (it != m_newServerLater.end())
	{
		return &(it->second);
	}

	return NULL;
}

CfgNewServerActivity* CfgData::getNewServerActivityByID(int32_t type,int32_t value,int32_t &index)
{
	CfgNewServerActivityTable::iterator it = m_newServerActivity.find(type);
	if (it != m_newServerActivity.end())
	{
		int32_t temp = 1;
		for (CfgNewServerActivityVector::iterator iter = it->second.begin();iter != it->second.end();++iter)
		{
			if (iter->id == value)
			{
				index = temp;
                return &(it->second[temp-1]);
			}
			temp++;
		}
	}

	return NULL;
}

CfgNewServerActivity* CfgData::getNewServerActivity(int32_t type, int32_t value, int32_t param)
{
	CfgNewServerActivityTable::iterator itType = m_newServerActivity.find(type);
	if (itType != m_newServerActivity.end())
	{
		for (CfgNewServerActivityVector::iterator it = itType->second.begin(); it != itType->second.end(); ++it)
		{
			if (it->value == value && (param == 0 || it->param == param))
			{
				return &(*it);
			}
		}
	}
	return NULL;
}

void CfgData::calcAchievementCount()
{
	//for (CfgAchievementTable::iterator it = m_achievement.begin();it != m_achievement.end();++it)
	//{
	//	if (it->second.special.size()> 0)
	//	{
	//		continue;
	//	}

	//	uint32_t temp = 0;
	//	//outdoor
	//	for (Int32Vector::iterator iter = it->second.outdoor.begin(); iter != it->second.outdoor.end();++iter)
	//	{
	//			 CfgAcOutdoorCaveTable::iterator outdoor = m_acOutdoorCave.find(*iter);
	//			 if (outdoor != m_acOutdoorCave.end() && outdoor->second.flag == AWT_MUST)
	//			 {
	//				   ++temp;
	//			 }
	//	}

	////cave
	//	for (Int32Vector::iterator iter = it->second.cave.begin(); iter != it->second.cave.end();++iter)
	//	{
	//		 CfgAcOutdoorCaveTable::iterator cave = m_acOutdoorCave.find(*iter);
	//		 if (cave != m_acOutdoorCave.end() && cave->second.flag == AWT_MUST)
	//		 {
	//			 ++temp;
	//		 }
	//	}

	////growup
	//	for (Int32Vector::iterator iter = it->second.grow_up.begin(); iter != it->second.grow_up.end();++iter)
	//	{
	//		CfgAcGrowUpTable::iterator grow = m_acGrowUp.find(*iter);
	//		if (grow != m_acGrowUp.end() && grow->second.flag == AWT_MUST)
	//		{
	//			temp += grow->second.target_value.size();
	//		}
	//	}

	////daily
	//	for (Int32Vector::iterator iter = it->second.daily.begin(); iter != it->second.daily.end();++iter)
	//	{
	//		CfgAcDailyTable::iterator daily = m_acDaily.find(*iter);
	//		if (daily != m_acDaily.end() && daily->second.flag == AWT_MUST)
	//		{
	//				temp += daily->second.target_count.size();
	//		}
	//	}

	////challenge
	//	CfgAcChallengeTable::iterator challenge = m_acChallenge.find(it->second.challenge);
	//	if (challenge!= m_acChallenge.end() && challenge->second.flag ==AWT_MUST)
	//	{
	//		++temp;
	//	}
	//	

	//	AchievementCount acCount = {};
	//	acCount.count = temp;
	//	acCount.level = it->first;

	//	m_acCount[acCount.level] = acCount;
	//}
}

CfgDailySearchBack* CfgData::getDailySearchBack(int32_t id,int32_t level)
{
	   CfgDailySearchBack*pSearchBack = NULL;
	   CfgDailySearchBackTable::iterator it = m_dailySearchBack.find(id);
	   if (it != m_dailySearchBack.end())
	   {
		   int32_t tempLevel = 0;
		   for (CfgDailySearchBackVector::iterator iter = it->second.begin();iter != it->second.end();++iter)
		   {
			   if (iter->level <= level  &&   iter->level >= tempLevel)
			   {
				   pSearchBack  =  &(*iter);
				   tempLevel = iter->level;
			   }
		   }
	   }

	   return pSearchBack;
}

//const CfgKingdomTable& CfgData::getKingdomAll()
//{
//	return m_kingdoms;
//}
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

CfgActivityEventVector* CfgData::getActivityEvents(int32_t activity_id)
{
	CfgActivityEventTable::iterator it = m_activityEvents.find(activity_id);
	if (it != m_activityEvents.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgActivityMonster* CfgData::getActivityMonsterById(int32_t id,int32_t actid)
{
	CfgActivityMonster* pItem=NULL;
	CfgActivityMonsterVector* pItems=NULL;
	CfgActivityMonsterVector::iterator slItem;
	CfgActivityMonsterTable::iterator it=m_activityMonsters.begin();
	bool bFinde=false;
	for (;it!=m_activityMonsters.end();it++)
	{
		pItems =&(*it).second;
		slItem =pItems->begin();
		for (;slItem!=pItems->end();slItem++)
		{
			pItem =&(*slItem);
			if(pItem->activity_id ==actid && pItem->id ==id)
			{
				bFinde=true;
				break;
			}
		}
		if(bFinde) break;
	}
	return pItem;
}
CfgActivityMonsterVector* CfgData::getActivityMonster(int32_t activity_id, int32_t wave)
{
	CfgActivityMonsterTable::iterator it = m_activityMonsters.find(activity_id * 1000 + wave);
	if (it != m_activityMonsters.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgActivityNpcVector* CfgData::getActivityNpc(int32_t activity_id)
{
	CfgActivityNpcTable::iterator it = m_activityNpcs.find(activity_id);
	if (it != m_activityNpcs.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
}

CfgActivityPlantVector* CfgData::getActivityPlant(int32_t activity_id, int32_t wave)
{
	CfgActivityPlantTable::iterator it = m_activityPlants.find(activity_id * 1000 + wave);
	if (it != m_activityPlants.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
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

void  CfgData::getDungeonEvent(int32_t dungonid,int32_t type,CfgDungeonEventList &events)
{
	CfgDungeonEventTable::iterator it  = m_dungeonEvents.find(dungonid);
	if (it != m_dungeonEvents.end())
	{
		for (CfgDungeonEventList::iterator iter = it->second.begin();iter != it->second.end();++iter)
		{
			if (iter->type == type)
			{
				events.push_back(*iter);
			}
		}
	}
}

CfgDungeonEvent* CfgData::getDungeonEvent(int32_t dungeonID,int32_t type)
{
	CfgDungeonEventTable::iterator it  = m_dungeonEvents.find(dungeonID);
	if (it != m_dungeonEvents.end())
	{
		for (CfgDungeonEventList::iterator iter = it->second.begin();iter != it->second.end();++iter)
		{
			if (iter->type == type )
			{
				return &(*iter);
			}
		}
	}

	return NULL;
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

CfgChrShop* CfgData::getChrShopTop( int8_t type, int32_t nLevel )
{
	CfgChrShop* pFind = NULL;
	int32_t nMaxLevel = 0;
	for ( CfgChrShopTable::iterator iter = m_chrShops.begin(); iter != m_chrShops.end(); ++iter )
	{
		if ( iter->second.ItemClass != IC_NORMAL )
		{
			continue;
		}

		CfgItem* pItem = getItem( iter->second.ItemId );
		if ( pItem != NULL && pItem->type == type && pItem->level <= nLevel )
		{
			if (  nMaxLevel == 0 || pItem->level > nMaxLevel )
			{
				nMaxLevel = pItem->level;
				pFind = &( iter->second );
			}
		}
	}

	return pFind;
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

CfgMapMonster* CfgData::GetMapMonsterInfoByMid( int32_t mid, MapId_t mapid )
{
	CfgMonsterMap::iterator iter = m_CfgMapMonsters.begin();
	CfgMonsterMap::iterator eiter = m_CfgMapMonsters.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( iter->second.monsterid == mid && iter->second.mapid == mapid )
		{
			return &(iter->second);
		}
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

CfgMapRegion CfgData::getOfflineExpRegion()
{
	return m_offlineExpRegion;
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

CfgDungeonDropGroupVector* CfgData::getDungeonDropGroup(int32_t groupID)
{
	CfgDungeonDropGroupTable::iterator it = m_dungeonDropGroup.find(groupID);
	if (it != m_dungeonDropGroup.end())
	{
		return &(it->second);
	}
	else
	{
		return NULL;
	}
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

CfgOnlineReward* CfgData::getOnlineReward(int32_t id)
{
	CfgOnlineRewardTable::iterator it =  m_onlineRewards.find(id);
	if (it != m_onlineRewards.end())
	{
		return  &(it->second);
	}
    else
	{
		return NULL;
	}
}

CfgOnlineRewardVector CfgData::getOnlineRewardByType(int32_t type)
{
	CfgOnlineRewardVector rewards;
	for (CfgOnlineRewardTable::iterator it = m_onlineRewards.begin();it != m_onlineRewards.end();++it)
	{
		if (it->second.type == type)
		{
			rewards.push_back(it->second);
		}
	}
	return rewards;
}

int32_t CfgData::getOnlineTime(int32_t id)
{
	int32_t time = 0;
	for (CfgOnlineRewardTable::iterator it = m_onlineRewards.begin();it != m_onlineRewards.end();++it)
	{
		if (it->second.type == 1 && it->second.id <= id)
		{
			time += it->second.time;
		}
	}

	return time;
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

CfgAcOutdoorCave* CfgData::getAcOutdoorCave(int32_t id)
{
	CfgAcOutdoorCaveTable::iterator it = m_acOutdoorCave.find(id);
	if (it != m_acOutdoorCave.end())
	{
		return &(it->second);
	}

	return  NULL;
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


CfgAcTask* CfgData::getAcTaskByID(int32_t id)
{
	for (CfgAcTaskTable::iterator it = m_acTask.begin();it != m_acTask.end();++it)
	{
		if (it->second.id == id)
		{
			return &(it->second);
		}
	}

	return NULL;
}

CfgAcTask* CfgData::getAcTask(int32_t taskID)
{
	CfgAcTaskTable::iterator it = m_acTask.find(taskID);
	if (it != m_acTask.end())
	{
		return &(it->second);
	}

	return NULL;
}

int32_t CfgData::getAchievementCount(int32_t level)
{
	 AchievementCountTable::iterator it = m_acCount.find(level);
	 if (it != m_acCount.end())
	 {
		   return it->second.count;
	 }

	 return 0;
}

int32_t CfgData::getFirstAchievement()
{
	for (CfgAchievementTable::iterator it = m_achievement.begin();it != m_achievement.end();++it)
	{
		if (it->second.last == it->first)
		{
			return it->first;
		}
	}

	return 0;
}

void CfgData::initAcOutdoorCave(CfgAcOutdoorCavePTable &outdoorCave,int32_t level)
{
	CfgAchievementTable::iterator it = m_achievement.find(level);
	if (it  !=  m_achievement.end())
	{
		for (Int32Vector::iterator iter = it->second.outdoor.begin();iter != it->second.outdoor.end();++iter)
		{
			CfgAcOutdoorCaveTable::iterator itAc = m_acOutdoorCave.find(*iter);
			if (itAc != m_acOutdoorCave.end() && itAc->second.type == AOCT_RECORD)
			{
				outdoorCave[itAc->second.target_id].push_back(&((itAc->second)));
			}
		}

		for (Int32Vector::iterator iter = it->second.cave.begin();iter != it->second.cave.end();++iter)
		{
			CfgAcOutdoorCaveTable::iterator itAc = m_acOutdoorCave.find(*iter);
			if (itAc != m_acOutdoorCave.end() && itAc->second.type == AOCT_RECORD)
			{
				outdoorCave[itAc->second.target_id].push_back(&(itAc->second));
			}
		}
	}
}

CfgAcChallenge* CfgData::getAcChallenge(int32_t id)
{
	CfgAcChallengeTable::iterator it = m_acChallenge.find(id);
	if (it != m_acChallenge.end())
	{
		return &(it->second);
	}
	return NULL;
}

CfgAcGrowUp*CfgData::getAcGrowUp(int32_t id)
{
	 CfgAcGrowUpTable::iterator it = m_acGrowUp.find(id);
	 if (it != m_acGrowUp.end())
	 {
		 return &(it->second);
	 }

	 return NULL;
}

CfgAcExchange*CfgData::getAcExchange(int32_t id,int32_t index)
{
	CfgAcExchangeTable::iterator it = m_acExchange.find(id);
	if (it != m_acExchange.end())
	{
		for (CfgAcExchangeVector::iterator iter = it->second.begin();iter != it->second.end();++iter)
		{
			if (iter->index == index)
			{
				return  &(*iter);
			}
		}
	}
	return NULL;
}

CfgAcDaily*CfgData::getAcDaily(int32_t id)
{
	CfgAcDailyTable::iterator it = m_acDaily.find(id);
	if (it != m_acDaily.end())
	{
		return &(it->second);
	}

	return NULL;
}

CfgAchievement*CfgData::getAchievement(int32_t id)
{
	  CfgAchievementTable::iterator it = m_achievement.find(id);
	  if (it != m_achievement.end())
	  {
		  return &(it->second);
	  }

	  return NULL;
}

CfgAcSpecial* CfgData::getAcSpecial(int32_t id)
{
	 CfgAcSpecialTable::iterator it = m_acSpecial.find(id);
	 if (it != m_acSpecial.end())
	 {
		   return &(it->second);
	 }

	 return NULL;
}

CfgAcSpecial* CfgData::getAcSpecialByID(int32_t id)
{
	for (CfgAcSpecialTable::iterator it = m_acSpecial.begin();it != m_acSpecial.end();++it)
	{
		if (it->second.id == id)
		{
			return &(it->second);
		}
	}
	return NULL;
}

int32_t CfgData::generateKingdomTask(int32_t level)
{
	  int32_t  taskID = 0;
	  int32_t  minlevel = 0;
	  Int32Vector *groupVector = NULL;
	  if (level > 0 && level <= MAX_PLAYER_LEVEL)
	  {
		   for (Int32Int32VectorMap::iterator it = m_kingdomTask.begin();it != m_kingdomTask.end();++it)
		   {
			   if (it->first <=level  && minlevel < it->first )
			   {
				   groupVector = &(it->second);
				   minlevel = it->first;
			   }
		   }
	  }

	  if(groupVector != NULL)
	  {
		  random_shuffle(groupVector->begin(),groupVector->end());

		  return *(groupVector->begin());
	  }

	  return taskID;
}

//int32_t CfgData::generateCycleTasks(int32_t level)
//{
//
//	if (level > 0 && level <= MAX_PLAYER_LEVEL)
//	{
//		int32_t task_group = 0;
//
//		for (CfgTaskGroupTable::iterator it = m_taskGroups.begin(); it != m_taskGroups.end(); ++it)
//		{
//			if (level >= it->min_level && level <= it->max_level)
//			{
//				task_group = it->cycle_group;
//				break;
//			}
//		}
//
//		if (task_group > 0)
//		{
//			Int32Int32VectorMap::iterator it = m_taskCycles.find(task_group);
//			if (it != m_taskCycles.end())
//			{
//				random_shuffle(it->second.begin(),it->second.end());
//				return *(it->second.begin());
//			}
//		}
//	}
//
//	return 0;
//}


//int32_t CfgData::generateFamilyTask(int32_t level)
//{
//
//	if (level > 0 && level <= MAX_PLAYER_LEVEL)
//	{
//		int32_t task_group = 0;
//
//		for (CfgTaskGroupTable::iterator it = m_taskGroups.begin(); it != m_taskGroups.end(); ++it)
//		{
//			if (level >= it->min_level && level <= it->max_level)
//			{
//				task_group = it->family_group;
//				break;
//			}
//		}
//
//		if (task_group > 0)
//		{
//			Int32Int32VectorMap::iterator it = m_taskCycles.find(task_group);
//			if (it != m_taskCycles.end())
//			{
//				random_shuffle(it->second.begin(),it->second.end());
//				return *(it->second.begin());
//			}
//		}
//	}
//
//	return 0;
//}

CfgTask CfgData::getTaskKingdomGather()
{
	return m_taskKingdomGather;
}

CfgTask CfgData::getTaskKingdomMonster(int32_t level)
{
	CfgTask cfgTask;
	cfgTask.id = 0;

	for (CfgTaskVector::iterator it = m_taskKingdomMonster.begin(); it != m_taskKingdomMonster.end(); ++it)
	{
		if (level >= it->level && level <= it->max_level)
		{
			cfgTask = *it;
			break;
		}
	}

	return cfgTask;
}

CfgTask CfgData::getTaskKingdomTalk()
{
	return m_taskKingdomTalk;
}

CfgTask CfgData::getTaskKingdomHome()
{
	return m_taskKingdomHome;
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

//CfgVip CfgData::getVip(VipType type)
//{
//	CfgVip vip = {};
//	for (CfgVipTable::iterator it = m_vips.begin(); it != m_vips.end(); ++it)
//	{
//		if (it->second.type == type)
//		{
//			vip = it->second;
//		}
//	}
//	return vip;
//}

CfgItemBase* CfgData::getItemBase(int32_t id, int32_t type)
{
	switch (type)
	{
	case IC_NORMAL: return getItem(id);
	//case IC_EQUIP: return getEquip(id);
	default: return NULL;
	}
}

CfgSevenLogin* CfgData::getSevenReward(int32_t days)
{
    CfgSevenLoginTable::iterator it = m_sevenReward.find(days);
	if (it != m_sevenReward.end())
	{
		return &(it->second);
	}

	return NULL;
}

MemChrBagVector CfgData::getSignReward(int32_t count, int32_t minOrder, int32_t maxOrder)
{
	CfgSignRewardTable::iterator it = m_signReward.find(count);
	MemChrBagVector items;
	if (it != m_signReward.end())
	{
		for (SignVipRewardVector::iterator iter = it->second.vip.begin();iter != it->second.vip.end();++iter)
		{
			if (iter->vip_order <= maxOrder && iter->vip_order > minOrder)
			{
				items.insert(items.end(),iter->item.begin(),iter->item.end());
			}
		}
	}

	return items;
}

int32_t CfgData::getSignRewardIndex(int32_t count)
{
	bool find = false;
	int32_t index = -1;
	for (CfgSignRewardTable::iterator it = m_signReward.begin(); it != m_signReward.end(); ++it)
	{
		if (it->first <= count)
		{
			if (it->first == count)
			{
				find = true;
			}
			index++;
		}
	}
	if (find)
	{
		return index;
	}
	return -1;
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
	else if (itemClass == IC_EQUIP)
	{
		return 1;
	}
	else if (itemClass == IC_PET_EGG )
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
				return pGem->m_nPrice;
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

CfgLevelGift* CfgData::getLevelGift(int32_t level)
{
	CfgLevelGiftTable::iterator it = m_levelGift.find(level);
	if (it != m_levelGift.end())
	{
		return &(it->second);
	}

	return NULL;
}

CfgLevelGold* CfgData::getLevelGold(int32_t level)
{
	CfgLevelGoldTable::iterator it = m_levelGold.find(level);
	if (it != m_levelGold.end())
	{
		return &(it->second);
	}

	return NULL;
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

//int32_t CfgData::getMemFamilyWarFamilyId()
//{
//	return m_memFamilyWar.family_id;
//}
//
//std::string CfgData::getMemFamilyWarFamilyName()
//{
//	return m_memFamilyWar.family_name;
//}
//
//void CfgData::updateMemFamilyWar(const MemFamilyWar &familyWar)
//{
//	m_memFamilyWar = familyWar;
//	DB_SERVICE.updateMemFamilyWar(familyWar);
//	GAME_SERVICE.broadcastFamilyWarWinner();
//}
//
//void CfgData::onMemFamilyWarUpdated(const MemFamilyWar &familyWar)
//{
//	m_memFamilyWar = familyWar;
//}

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

void CfgData::fetchLevelGift()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_level_gift.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_level_gift.txt");
		return;
	}

	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	int32_t index = 0;
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		index++;
		CfgLevelGift gift = {};
		gift.level = TabFile.Search_Posistion(i,0)->iValue;
		parseItemStringWithJob(gift.level,TabFile.Search_Posistion(i,1)->pString,gift.item,gift.jobItem);
		gift.index = index;

		m_levelGift[gift.level] = gift;
	}
}

void CfgData::fetchLevelGold()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_level_gold.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_level_gold.txt");
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
		CfgLevelGold gold = {};
		gold.index	= TabFile.Search_Posistion(i,0)->iValue;
		gold.level	= TabFile.Search_Posistion(i,1)->iValue;
		gold.gold	= TabFile.Search_Posistion(i,2)->iValue;
		m_levelGold[gold.level] = gold;
	}
}

void CfgData::fetchSignReward()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_sign_reward.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_sign_reward.txt");
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
		reward.count = TabFile.Search_Posistion(i,0)->iValue;

		{
			SignVipReward signle = {};
			signle.vip_order = TabFile.Search_Posistion(i,1)->iValue;
			signle.item = parseTaskItemString(signle.vip_order,TabFile.Search_Posistion(i,2)->pString);
			reward.vip.push_back(signle);
		}

		{
			SignVipReward signle = {};
			signle.vip_order = TabFile.Search_Posistion(i,3)->iValue;
			signle.item = parseTaskItemString(signle.vip_order,TabFile.Search_Posistion(i,4)->pString);
			reward.vip.push_back(signle);
		}

		{
			SignVipReward signle = {};
			signle.vip_order = TabFile.Search_Posistion(i,5)->iValue;
			signle.item = parseTaskItemString(signle.vip_order,TabFile.Search_Posistion(i,6)->pString);
			reward.vip.push_back(signle);
		}

		{
			SignVipReward signle = {};
			signle.vip_order = TabFile.Search_Posistion(i,7)->iValue;
			signle.item = parseTaskItemString(signle.vip_order,TabFile.Search_Posistion(i,8)->pString);
			reward.vip.push_back(signle);
		}
		m_signReward[reward.count] = reward;
	}
}

void CfgData::fetchSevenLogin()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_seven_login_reward.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_seven_login_reward.txt");
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
		CfgSevenLogin reward = {};
		reward.days				= TabFile.Search_Posistion(i,0)->iValue;
		reward.level			= TabFile.Search_Posistion(i,1)->iValue;
		reward.fight_power		= TabFile.Search_Posistion(i,2)->iValue;
		reward.point			= TabFile.Search_Posistion(i,3)->iValue;
		reward.strategics		= TabFile.Search_Posistion(i,4)->iValue;
		reward.enhance			= TabFile.Search_Posistion(i,5)->iValue;
		reward.zizhi			= TabFile.Search_Posistion(i,6)->iValue;
		reward.kingdom_contribute = TabFile.Search_Posistion(i,7)->iValue;
		reward.mount			= TabFile.Search_Posistion(i,8)->iValue;
		parseItemStringWithJob(reward.days, TabFile.Search_Posistion(i,9)->pString, reward.item, reward.job_item);
		reward.vip				= TabFile.Search_Posistion(i,10)->iValue;

		m_sevenReward[reward.days] = reward;
	}
}

void CfgData::fetchYellowStone()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_yellow_stone.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_yellow_stone.txt");
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

void CfgData::fetchNewServerActivity()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_new_server_activity.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_new_server_activity.txt");
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
		CfgNewServerActivity activity = {};
		activity.id		 = TabFile.Search_Posistion(i,0)->iValue;
		activity.time	 = TabFile.Search_Posistion(i,1)->iValue;
		activity.type	 = TabFile.Search_Posistion(i,6)->iValue;
		activity.value	 = TabFile.Search_Posistion(i,7)->iValue;
		activity.param	 = TabFile.Search_Posistion(i,8)->iValue;
		activity.order	 = TabFile.Search_Posistion(i,9)->iValue;
		activity.item	 = parseItemString(activity.id,TabFile.Search_Posistion(i,10)->pString );

		m_newServerActivity[activity.type].push_back(activity);
	}

	CDBCFile TabFileGold(0);
	ret = TabFileGold.OpenFromTXT("./ServerConfig/Tables/cfg_new_server_gold.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_new_server_gold.txt");
		return;
	}

	iBaseTableCount			=	TabFileGold.GetRecordsNum();
	iBaseColumnCount		=	TabFileGold.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgNewServerGold gold = {};
		gold.id		= TabFileGold.Search_Posistion(i,0)->iValue;
		gold.type	= TabFileGold.Search_Posistion(i,1)->iValue;
		gold.cost	= TabFileGold.Search_Posistion(i,2)->iValue;
		gold.give	= TabFileGold.Search_Posistion(i,3)->iValue;
		m_newServerGold[gold.id] = gold;
	}

	CDBCFile TabFileLater(0);
	ret = TabFileLater.OpenFromTXT("./ServerConfig/Tables/cfg_new_server_later.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_new_server_later.txt");
		return;
	}

	iBaseTableCount			=	TabFileLater.GetRecordsNum();
	iBaseColumnCount		=	TabFileLater.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgNewServerLater later = {};
		later.id	= TabFileLater.Search_Posistion(i,0)->iValue;
		later.type	= TabFileLater.Search_Posistion(i,1)->iValue;
		later.index = TabFileLater.Search_Posistion(i,2)->iValue;
		later.value = TabFileLater.Search_Posistion(i,4)->iValue;
		later.items = parseItemString(later.id,TabFileLater.Search_Posistion(i,5)->pString );
		m_newServerLater[later.id] = later;
	}
}


void CfgData::fetchAchievement()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_ac_total.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_total.txt");
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
		CfgAchievement  ac = {};
		ac.id			= TabFile.Search_Posistion(i,0)->iValue;
		int32_t Type	= TabFile.Search_Posistion(i,1)->iValue;
		ac.outdoor		= parseAchievementString(ac.id,TabFile.Search_Posistion(i,3)->pString);
		ac.cave			= parseAchievementString(ac.id,TabFile.Search_Posistion(i,4)->pString);
		ac.grow_up		= parseAchievementString(ac.id,TabFile.Search_Posistion(i,5)->pString);
		ac.daily		= parseAchievementString(ac.id,TabFile.Search_Posistion(i,6)->pString);
		ac.challenge	= TabFile.Search_Posistion(i,7)->iValue;
		ac.exchange		= TabFile.Search_Posistion(i,8)->iValue;
		ac.special		= parseAchievementString(ac.id,TabFile.Search_Posistion(i,9)->pString);
		ac.last			= TabFile.Search_Posistion(i,11)->iValue;
		ac.next			= TabFile.Search_Posistion(i,12)->iValue;
		if ( 0 == Type )
		{
			m_achievement[ac.id] = ac;
		}
	}

	CDBCFile TabFileCave(0);
	ret = TabFileCave.OpenFromTXT("./ServerConfig/Tables/cfg_ac_outdoor_cave.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_outdoor_cave.txt");
		return;
	}

	iBaseTableCount			=	TabFileCave.GetRecordsNum();
	iBaseColumnCount		=	TabFileCave.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcOutdoorCave outdoor_cave;
		outdoor_cave.id			= TabFileCave.Search_Posistion(i,0)->iValue;
		outdoor_cave.point		= TabFileCave.Search_Posistion(i,3)->iValue;
		outdoor_cave.flag		= TabFileCave.Search_Posistion(i,4)->iValue;
		outdoor_cave.type		= TabFileCave.Search_Posistion(i,5)->iValue;
		outdoor_cave.target_id	= TabFileCave.Search_Posistion(i,6)->iValue;
		outdoor_cave.target_count = TabFileCave.Search_Posistion(i,7)->iValue;
		outdoor_cave.gold		= TabFileCave.Search_Posistion(i,9)->iValue;
		outdoor_cave.hufu		= TabFileCave.Search_Posistion(i,10)->iValue;
		m_acOutdoorCave[outdoor_cave.id] = outdoor_cave;
	}

	CDBCFile TabFileDaily(0);
	ret = TabFileDaily.OpenFromTXT("./ServerConfig/Tables/cfg_ac_daily.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_daily.txt");
		return;
	}

	iBaseTableCount			=	TabFileDaily.GetRecordsNum();
	iBaseColumnCount		=	TabFileDaily.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcDaily daily = {};
		daily.id			= TabFileDaily.Search_Posistion(i,0)->iValue;
		daily.type			= TabFileDaily.Search_Posistion(i,3)->iValue;
		daily.target_id		= TabFileDaily.Search_Posistion(i,4)->iValue;
		daily.target_count	= parseAchievementString(daily.id,TabFileDaily.Search_Posistion(i,5)->pString);
		daily.point			= parseAchievementString(daily.id,TabFileDaily.Search_Posistion(i,6)->pString);
		daily.gold			= parseAchievementString(daily.id,TabFileDaily.Search_Posistion(i,7)->pString);
		daily.hufu			= parseAchievementString(daily.id,TabFileDaily.Search_Posistion(i,8)->pString);
		daily.flag			= TabFileDaily.Search_Posistion(i,9)->iValue;

		m_acDaily[daily.id] = daily;
	}

	CDBCFile TabFileChallend(0);
	ret = TabFileChallend.OpenFromTXT("./ServerConfig/Tables/cfg_ac_challend.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_challend.txt");
		return;
	}

	iBaseTableCount			=	TabFileChallend.GetRecordsNum();
	iBaseColumnCount		=	TabFileChallend.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcChallenge challenge = {};
		challenge.id	= TabFileChallend.Search_Posistion(i,0)->iValue;

		AcChallengeFBInfo  fbinfo = {};
		fbinfo.id		= TabFileChallend.Search_Posistion(i,1)->iValue;
		fbinfo.point	= TabFileChallend.Search_Posistion(i,3)->iValue;
		challenge.fb.push_back(fbinfo);

		bzero(&fbinfo,sizeof(fbinfo));
		fbinfo.id		= TabFileChallend.Search_Posistion(i,4)->iValue;
		fbinfo.point	= TabFileChallend.Search_Posistion(i,6)->iValue;
		challenge.fb.push_back(fbinfo);

		bzero(&fbinfo,sizeof(fbinfo));
		fbinfo.id		= TabFileChallend.Search_Posistion(i,7)->iValue;
		fbinfo.point	= TabFileChallend.Search_Posistion(i,9)->iValue;
		challenge.fb.push_back(fbinfo);

		bzero(&fbinfo,sizeof(fbinfo));
		fbinfo.id		= TabFileChallend.Search_Posistion(i,10)->iValue;
		fbinfo.point	= TabFileChallend.Search_Posistion(i,12)->iValue;
		challenge.fb.push_back(fbinfo);

		challenge.point = TabFileChallend.Search_Posistion(i,13)->iValue;
		challenge.change_count = TabFileChallend.Search_Posistion(i,14)->iValue;
		challenge.flag	= TabFileChallend.Search_Posistion(i,15)->iValue;
		m_acChallenge[challenge.id] = challenge;
	}	 

	CDBCFile TabFileExchange(0);
	ret = TabFileExchange.OpenFromTXT("./ServerConfig/Tables/cfg_ac_exchange.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_exchange.txt");
		return;
	}

	iBaseTableCount			=	TabFileExchange.GetRecordsNum();
	iBaseColumnCount		=	TabFileExchange.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcExchange exchange = {};
		exchange.id			= TabFileExchange.Search_Posistion(i,0)->iValue;
		exchange.index		= TabFileExchange.Search_Posistion(i,1)->iValue;
		exchange.point		= TabFileExchange.Search_Posistion(i,4)->iValue;
		exchange.item		= paresAcExchangeString(exchange.id,TabFileExchange.Search_Posistion(i,5)->pString);
		exchange.money		= TabFileExchange.Search_Posistion(i,6)->iValue;
		exchange.exp		= TabFileExchange.Search_Posistion(i,7)->iValue;
		exchange.gold		= TabFileExchange.Search_Posistion(i,8)->iValue;
		exchange.jiangxing	= TabFileExchange.Search_Posistion(i,9)->iValue;
		exchange.wuhuen		= TabFileExchange.Search_Posistion(i,10)->iValue;
		exchange.jungong	= TabFileExchange.Search_Posistion(i,11)->iValue;
		exchange.group		= TabFileExchange.Search_Posistion(i,12)->iValue;
		exchange.group_first = TabFileExchange.Search_Posistion(i,13)->iValue;
		exchange.last		= TabFileExchange.Search_Posistion(i,14)->iValue;
		exchange.next		= TabFileExchange.Search_Posistion(i,15)->iValue;
		m_acExchange[exchange.id].push_back(exchange);
	}	 

	CDBCFile TabFileUp(0);
	ret = TabFileUp.OpenFromTXT("./ServerConfig/Tables/cfg_ac_grow_up.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_grow_up.txt");
		return;
	}

	iBaseTableCount			=	TabFileUp.GetRecordsNum();
	iBaseColumnCount		=	TabFileUp.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcGrowUp growup = {};
		growup.id		= TabFileUp.Search_Posistion(i,0)->iValue;
		growup.type		= TabFileUp.Search_Posistion(i,3)->iValue;
		growup.target_value = parseAchievementString(growup.id,TabFileUp.Search_Posistion(i,4)->pString);
		growup.point	= TabFileUp.Search_Posistion(i,5)->iValue;
		growup.flag		= TabFileUp.Search_Posistion(i,6)->iValue;
		m_acGrowUp[growup.id] = growup;
	}	 

	CDBCFile TabFileSpecial(0);
	ret = TabFileSpecial.OpenFromTXT("./ServerConfig/Tables/cfg_ac_special.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_special.txt");
		return;
	}

	iBaseTableCount			=	TabFileSpecial.GetRecordsNum();
	iBaseColumnCount		=	TabFileSpecial.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcSpecial  special = {};
		special.id		= TabFileSpecial.Search_Posistion(i,0)->iValue;
		special.type	= TabFileSpecial.Search_Posistion(i,4)->iValue;
		special.point	= TabFileSpecial.Search_Posistion(i,5)->iValue;
		special.gold	= TabFileSpecial.Search_Posistion(i,7)->iValue;
		special.hufu	= TabFileSpecial.Search_Posistion(i,8)->iValue;
		m_acSpecial[special.type] = special;
	}	 

	CDBCFile TabFileTask(0);
	ret = TabFileTask.OpenFromTXT("./ServerConfig/Tables/cfg_ac_task.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_ac_task.txt");
		return;
	}

	iBaseTableCount			=	TabFileTask.GetRecordsNum();
	iBaseColumnCount		=	TabFileTask.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgAcTask task = {};
		task.id			= TabFileTask.Search_Posistion(i,0)->iValue;
		task.taskID		= TabFileTask.Search_Posistion(i,5)->iValue;
		task.point		= TabFileTask.Search_Posistion(i,6)->iValue;
		m_acTask[task.taskID] = task;
	}	 
	 calcAchievementCount();
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
		activity.kingdom			= static_cast<int16_t>(ActivityFile.Search_Posistion(i,13)->iValue);
		activity.start_hour			= ActivityFile.Search_Posistion(i,14)->iValue;
		activity.duration			= ActivityFile.Search_Posistion(i,15)->iValue;
		std::string position		= ActivityFile.Search_Posistion(i,17)->pString;
		std::string awards			= ActivityFile.Search_Posistion(i,18)->pString;
		activity.typeId				= static_cast<int16_t>(ActivityFile.Search_Posistion(i,21)->iValue);
		activity.exp_add_interval	= ActivityFile.Search_Posistion(i,23)->iValue;
		
		while (weekday > 0)
		{
			activity.weekday.push_back(weekday%10);
			weekday /= 10;
		}
		if (activity.start_hour < 0 || activity.start_hour >= 60*24 || activity.duration < 0 || activity.start_hour+activity.duration >= 60*24)
		{
			LOG_ERROR("wrong activity data with id=%d\n", activity.id);
		}
		if(strlen(awards.c_str()) >0)
		{
			StringVector strParams = StringUtility::split(awards.c_str(), ":");
			int16_t nsize =strParams.size();
			bool bTrue = false;
			if (bTrue)
			{
				activity.gift_id.resize(nsize);
				for (int32_t i=0;i<nsize;i++)
				{
					activity.gift_id[i]=atoi(strParams[i].c_str());
				}
			}
			else
			{
				activity.gift_id.resize(5);
				activity.gift_id[0]=activity.gift_id[1]=activity.gift_id[2]=activity.gift_id[3]=activity.gift_id[4]=0;
			}
		}

		StringVector strParams = StringUtility::split(position.c_str(), ":");
		if(strParams.size()==2)
		{
			activity.target_mapid = atoi(strParams[0].c_str());

			StringVector stritemParams = StringUtility::split(strParams[1].c_str(), "|");
			int32_t nlenth =stritemParams.size();
			for (int32_t j = 0;j < nlenth;j++)
			{
				activity.target_regiona.push_back(atoi(stritemParams[j].c_str()));
			}
		}
		if (strParams.size() == 3)
		{
			activity.target_mapid = atoi(strParams[0].c_str());

			StringVector stritemParams = StringUtility::split(strParams[1].c_str(), "|");
			int32_t nlenth =stritemParams.size();
			for (int32_t j = 0;j < nlenth;j++)
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
		activity.state = AS_END;

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
		CfgActivityEvent activityEvent;
		activityEvent.activity_id		= ActivityEventFile.Search_Posistion(i,0)->iValue;
		activityEvent.trigger_id		= ActivityEventFile.Search_Posistion(i,1)->iValue;
		activityEvent.trigger_type		= ActivityEventFile.Search_Posistion(i,2)->iValue;
		std::string triggerParam		= ActivityEventFile.Search_Posistion(i,3)->pString;
		activityEvent.event_type		= ActivityEventFile.Search_Posistion(i,4)->iValue;
		std::string eventEffect			= ActivityEventFile.Search_Posistion(i,5)->pString;
		activityEvent.dialog			= ActivityEventFile.Search_Posistion(i,6)->pString;
		
		StringVector strParams			= StringUtility::split(triggerParam.c_str(), ":");
		for (StringVector::iterator it = strParams.begin(); it != strParams.end(); ++it)
		{
			activityEvent.trigger_param.push_back(atoi(it->c_str()));
		}
		
		StringVector strEffects = StringUtility::split(eventEffect.c_str(), ":");
		for (StringVector::iterator it = strEffects.begin(); it != strEffects.end(); ++it)
		{
			activityEvent.event_effect.push_back(atoi(it->c_str()));
		}

		activityEvent.done = false;
		m_activityEvents[activityEvent.activity_id].push_back(activityEvent);
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
		monster.id				= ActivityMonsterFile.Search_Posistion(i,0)->iValue;
		monster.activity_id		= ActivityMonsterFile.Search_Posistion(i,1)->iValue;
		monster.monster_id		= ActivityMonsterFile.Search_Posistion(i,2)->iValue;
		monster.count			= ActivityMonsterFile.Search_Posistion(i,3)->iValue;
		monster.wave			= ActivityMonsterFile.Search_Posistion(i,4)->iValue;
		monster.kingdom			= ActivityMonsterFile.Search_Posistion(i,5)->iValue;
		std::string regionId	= ActivityMonsterFile.Search_Posistion(i,6)->pString;
		monster.side			= static_cast<int8_t>(ActivityMonsterFile.Search_Posistion(i,7)->iValue);

		StringVector strRegions = StringUtility::split(regionId.c_str(), ":");
		for (StringVector::iterator it = strRegions.begin(); it != strRegions.end(); ++it)
		{
			monster.region_id.push_back(atoi(it->c_str()));
		}
		m_activityMonsters[monster.activity_id * 1000 + monster.wave].push_back(monster);
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
		m_activityNpcs[npc.activity_id].push_back(npc);
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

		m_activityPlants[plant.activity_id * 1000 + plant.wave].push_back(plant);
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
}

void CfgData::fetchAnnoucementTime()
{
	//MySqlDBGuard db(DBPOOL);

	//MySqlQuery result = db.query("SELECT * FROM `sys_annoucement_time` ORDER BY hour, minute ASC");
	//while (!result.eof())
	//{
	//	CfgAnnoucementTime annoucementTime;
	//	annoucementTime.id = result.getIntValue("id");
	//	int32_t weekday = result.getIntValue("weekday");
	//	while (weekday > 0)
	//	{
	//		annoucementTime.weekday.push_back(weekday%10);
	//		weekday /= 10;
	//	}
	//	annoucementTime.begin_date = result.getIntValue("begin_date");
	//	annoucementTime.end_date = result.getIntValue("end_date");
	//	annoucementTime.hour = result.getIntValue("hour");
	//	annoucementTime.minute = result.getIntValue("minute");
	//	annoucementTime.annoucement_id = result.getIntValue("annoucement_id");

	//	m_annoucementTimes.push_back(annoucementTime);

	//	result.nextRow();
	//}
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

		m_buffs[buff.id] = buff;
	}
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
		++nIndex;
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
		++nIndex;
		dungeon.double_cost		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		dungeon.reward_time		= DungeonFile.Search_Posistion(i,nIndex)->iValue;		++nIndex;
		++nIndex;
		std::string	costItem	= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;
		std::string	rewardOnce	= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;
		std::string	rewardItem	= DungeonFile.Search_Posistion(i,nIndex)->pString;		++nIndex;

		while (weekday > 0)
		{
			dungeon.weekday |= 1<<(weekday%10);
			weekday /= 10;
		}

		parasItemData( dungeon.costItem, costItem );
		parasItemData( dungeon.rewardOnce, rewardOnce );
		parasItemData( dungeon.rewardOnce, rewardOnce );
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
		CfgDungeonDropGroup group;
		group.id				= DungeonDropFile.Search_Posistion( i, 0 )->iValue;
		group.type				= DungeonDropFile.Search_Posistion( i, 1 )->iValue;
		group.item_id			= DungeonDropFile.Search_Posistion( i, 3 )->iValue;
		group.item_class		= DungeonDropFile.Search_Posistion( i, 4 )->iValue;
		group.bind_type			= DungeonDropFile.Search_Posistion( i, 5 )->iValue;
		group.count				= DungeonDropFile.Search_Posistion( i, 6 )->iValue;
		group.weight			= DungeonDropFile.Search_Posistion( i, 7 )->iValue;
		group.probability		= DungeonDropFile.Search_Posistion( i, 8 )->iValue;

		m_dungeonDropGroup[group.id].push_back(group);
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
		CfgDungeonEvent dungeonEvent;
		dungeonEvent.dungeon_id				= DungeonEventFile.Search_Posistion(i,0)->iValue;
		dungeonEvent.trigger_id				= DungeonEventFile.Search_Posistion(i,1)->iValue;
		dungeonEvent.type					= DungeonEventFile.Search_Posistion(i,2)->iValue;
		dungeonEvent.trigger_type			= DungeonEventFile.Search_Posistion(i,3)->iValue;
		std::string triggerParam			= DungeonEventFile.Search_Posistion(i,4)->pString;
		dungeonEvent.event_type				= DungeonEventFile.Search_Posistion(i,5)->iValue;
		dungeonEvent.effect					= DungeonEventFile.Search_Posistion(i,6)->pString;
		dungeonEvent.dialog					= DungeonEventFile.Search_Posistion(i,7)->pString;

		StringVector strTriggerParam		= StringUtility::split(triggerParam.c_str(), ":");
		for (StringVector::iterator it = strTriggerParam.begin(); it != strTriggerParam.end(); ++it)
		{
			dungeonEvent.trigger_param.push_back(atoi(it->c_str()));
		}
		dungeonEvent.m_done = false;

		if (!dungeonEvent.trigger_param.empty())
		{
			m_dungeonEvents[dungeonEvent.dungeon_id].push_back(dungeonEvent);
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
		CfgDungeonMonster dungeonMonster;
		dungeonMonster.id			= DungeonMonsterFile.Search_Posistion(i,0)->iValue;
		dungeonMonster.wave			= DungeonMonsterFile.Search_Posistion(i,1)->iValue;
		dungeonMonster.mid			= DungeonMonsterFile.Search_Posistion(i,2)->iValue;
		dungeonMonster.x			= DungeonMonsterFile.Search_Posistion(i,3)->iValue;
		dungeonMonster.y			= DungeonMonsterFile.Search_Posistion(i,4)->iValue;
		dungeonMonster.count		= DungeonMonsterFile.Search_Posistion(i,5)->iValue;
		dungeonMonster.side			= DungeonMonsterFile.Search_Posistion(i,6)->iValue;
		std::string road			= DungeonMonsterFile.Search_Posistion(i,7)->pString;
		dungeonMonster.delay		= DungeonMonsterFile.Search_Posistion(i,8)->iValue;
		dungeonMonster.times		= DungeonMonsterFile.Search_Posistion(i,9)->iValue;
		if ( road.size() > 3 )
		{
			StringVector vRoad = Answer::StringUtility::split( road, ":" );
			for ( uint32_t i = 0; i < vRoad.size(); ++i )
			{
				StringVector vPos = Answer::StringUtility::split( vRoad[i], "," );
				if ( vPos.size() == 2 )
				{
					dungeonMonster.road.push_back( Position( atoi( vPos[0].c_str() ), atoi( vPos[1].c_str() ) ) );
				}
			}
		}

		m_dungeonMonsters[dungeonMonster.id] = dungeonMonster;
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
		itemGift.job					= ItemGiftFile.Search_Posistion(i,5)->iValue;

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
		itemGiftRandom.static_probability	= ItemGiftRandFile.Search_Posistion(i,4)->iValue;
		itemGiftRandom.sum_probability		= ItemGiftRandFile.Search_Posistion(i,5)->iValue;

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
		LOG_ERROR("打开配置表错误 cfg_movie.txt");
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
		LOG_ERROR("打开配置表错误 cfg_level_exp.txt");
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

		if (mapRegion.id == RI_OFFLINE_EXP)
		{
			m_offlineExpRegion = mapRegion;
		}
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

		// 属性
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
		LOG_ERROR("打开配置表错误 cfg_gamble.txt");
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
		LOG_ERROR("打开配置表错误 cfg_gamble_equip.txt");
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
		LOG_ERROR("打开配置表错误 cfg_npc.txt");
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

		m_npcs[npc.id] = npc;
	}

	CDBCFile TabFileAir(0);
	ret = TabFileAir.OpenFromTXT("./ServerConfig/Tables/cfg_npc_airport.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_npc_airport.txt");
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

void CfgData::fetchChargeRewards()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_charge_rewards.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_charge_rewards.txt");
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
		CfgChargeRewards reward;
		reward.id			= TabFile.Search_Posistion(i,0)->iValue;
		reward.type			= TabFile.Search_Posistion(i,1)->iValue;
		reward.charge		= TabFile.Search_Posistion(i,2)->iValue;
		reward.money		= TabFile.Search_Posistion(i,3)->iValue;
		reward.sys_gold		= TabFile.Search_Posistion(i,4)->iValue;
		parseItemStringWithJob(reward.id,TabFile.Search_Posistion(i,5)->pString, reward.real_rewards, reward.real_job_rewards);
		m_chargeRewards.push_back(reward);
	}
}

void CfgData::fetchOnlineReward()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_online_reward.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_online_reward.txt");
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
		CfgOnlineReward reward;
		reward.id		= TabFile.Search_Posistion(i,0)->iValue;
		reward.type		= TabFile.Search_Posistion(i,1)->iValue;
		reward.time		= TabFile.Search_Posistion(i,2)->iValue;
		reward.gold		= TabFile.Search_Posistion(i,3)->iValue;
		reward.items	= parseTaskItemString(reward.id,TabFile.Search_Posistion(i,4)->pString);

		m_onlineRewards[reward.id] = reward;
	}
}

void CfgData::fetchPlant()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_plant.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_plant.txt");
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
			StringVector strItem = StringUtility::split(*it, ":");
			if (strItem.size() == 2)
			{
				CfgPlantItem item;
				item.item = atoi(strItem[0].c_str());
				item.probability = atoi(strItem[1].c_str());

				CfgItem *pCfgItem = CFG_DATA.getItem(item.item);
				if (pCfgItem != NULL)
				{
					plant.item.push_back(item);
				}
				else
				{
					LOG_ERROR("wrong plant cfg data with id = %d\n", plant.id);
				}
			}
		}
		plant.item_count	= TabFile.Search_Posistion(i,6)->iValue;
		plant.item_cost		= TabFile.Search_Posistion(i,7)->iValue;
		plant.start_hour	= TabFile.Search_Posistion(i,8)->iValue;
		plant.end_hour		= TabFile.Search_Posistion(i,9)->iValue;
		plant.gather_time	= TabFile.Search_Posistion(i,10)->iValue;
		plant.revive_time	= TabFile.Search_Posistion(i,11)->iValue;

		if (plant.item.empty() || plant.item_count <= 0)
		{
			LOG_ERROR("wrong plant cfg data with id = %d\n", plant.id);
		}
		m_plants[plant.id] = plant;
	}
}

void CfgData::fetchSkill()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_skill_info.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_skill_result.txt");
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
		LOG_ERROR("打开配置表错误 cfg_skill_info.txt");
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
		m_skills[SkillId].cd					= TabFileResult.Search_Posistion(i,11)->iValue;
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

void CfgData::fetchDaily()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_daily_item.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_daily_item.txt");
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
		CfgDailyItem  item = {};
		item.id			= TabFile.Search_Posistion(i,0)->iValue;
		item.type		= TabFile.Search_Posistion(i,1)->iValue;
		item.count		= TabFile.Search_Posistion(i,4)->iValue;
		item.mark		= TabFile.Search_Posistion(i,5)->iValue;
		item.level		= TabFile.Search_Posistion(i,7)->iValue;
		item.isBack		= TabFile.Search_Posistion(i,8)->iValue;
		m_dailyItems[item.type] = item;
	}

	CDBCFile TabFileReward(0);
	ret = TabFileReward.OpenFromTXT("./ServerConfig/Tables/cfg_daily_mark_reward.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_daily_mark_reward.txt");
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
		CfgDailyMark  mark = {};
		mark.mark		= TabFileReward.Search_Posistion(i,0)->iValue;
		mark.gift_id	= TabFileReward.Search_Posistion(i,1)->iValue;

		m_dailyMark[mark.mark] = mark;
	}

	CDBCFile TabFileItem(0);
	ret = TabFileItem.OpenFromTXT("./ServerConfig/Tables/cfg_daily_item_reward.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_daily_item_reward.txt");
		return;
	}

	iBaseTableCount			=	TabFileItem.GetRecordsNum();
	iBaseColumnCount		=	TabFileItem.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgDailySearchBack searchBack = {};
		searchBack.id			= TabFileItem.Search_Posistion(i,0)->iValue;
		searchBack.level		= TabFileItem.Search_Posistion(i,1)->iValue;
		searchBack.money		= TabFileItem.Search_Posistion(i,2)->iValue;
		searchBack.exp			= TabFileItem.Search_Posistion(i,3)->iValue;
		searchBack.jungong		= TabFileItem.Search_Posistion(i,5)->iValue;
		searchBack.wuhuen		= TabFileItem.Search_Posistion(i,6)->iValue;
		searchBack.luck			= TabFileItem.Search_Posistion(i,7)->iValue;
		searchBack.jiangxing	= TabFileItem.Search_Posistion(i,8)->iValue;
		searchBack.items		= parseAllItemString(searchBack.id, TabFileItem.Search_Posistion(i,9)->pString);

		m_dailySearchBack[searchBack.id].push_back(searchBack);
	}

	CDBCFile TabFileDailyReward(0);
	ret = TabFileDailyReward.OpenFromTXT("./ServerConfig/Tables/cfg_daily_reward.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_daily_reward.txt");
		return;
	}

	iBaseTableCount			=	TabFileDailyReward.GetRecordsNum();
	iBaseColumnCount		=	TabFileDailyReward.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		CfgDailyReward reward = {};
		reward.id		= TabFileDailyReward.Search_Posistion(i,0)->iValue;
		reward.level	= TabFileDailyReward.Search_Posistion(i,1)->iValue;
		reward.value	= TabFileDailyReward.Search_Posistion(i,2)->iValue;

		m_dailyReward[reward.id].push_back(reward);
	}
}

void CfgData::fetchTask()
{
	m_taskKingdomGather.id = 0;
	m_taskKingdomTalk.id = 0;
	m_taskKingdomHome.id = 0;


	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_task.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_task.txt");
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
		task.jiangxing			= TabFile.Search_Posistion(i,19)->iValue;
		task.wuhuen				= TabFile.Search_Posistion(i,20)->iValue;
		task.jungong			= TabFile.Search_Posistion(i,21)->iValue;
		task.award_item			= parseTaskItemString(task.id, TabFile.Search_Posistion(i,22)->pString);
		task.award_optional		= parseTaskItemJobString(task.id,TabFile.Search_Posistion(i,23)->pString);

		task.destCondition		= parseTaskDestString(task.id,TabFile.Search_Posistion(i,25)->pString);
		task.destSubmit			= parseTaskDestString(task.id,TabFile.Search_Posistion(i,26)->pString);

		task.condition			= TabFile.Search_Posistion(i,34)->iValue;
	//	task.done_count			= TabFile.Search_Posistion(i,1)->iValue;
		task.request = parseTaskCondition(task.id, task.condition, TabFile.Search_Posistion(i,35)->pString);

		m_tasks[task.id] = task;

		//if (task.type == TT_CYCLE || task.type == TT_FACTION || task.type == TT_CYCLE_XINFA || task.type == TT_CYCLE_YUELI)
		//{
		//	m_taskCycles[task.group].push_back(task.id);
		//}
		if ( task.type == TT_CYCLE )
		{
			m_cfgTaskCycleTable.AddTask( task.id, task.level, task.max_level );
		}
		//else if (task.type == TT_KINGDOM)
		//{
		//	m_kingdomTask[task.level].push_back(task.id);
		//}
	}
}

void CfgData::fetchTaskCycleGroup()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_task_cycle_group.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_task_cycle_group.txt");
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
		CfgTaskGroup taskGroup;
		taskGroup.min_level			= TabFile.Search_Posistion(i,1)->iValue;
		taskGroup.max_level			= TabFile.Search_Posistion(i,2)->iValue;
		taskGroup.cycle_group		= TabFile.Search_Posistion(i,3)->iValue;
		taskGroup.family_group		= TabFile.Search_Posistion(i,4)->iValue;
		m_taskGroups.push_back(taskGroup);
	}
}


void CfgData::fetchTrailer()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_trailer.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_trailer.txt");
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
		LOG_ERROR("打开配置表错误 cfg_trap.txt");
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
		trap.effect_delay	= TabFile.Search_Posistion(i,3)->iValue;
		trap.type			= TabFile.Search_Posistion(i,4)->iValue;
		trap.effect			= TabFile.Search_Posistion(i,6)->iValue;
		trap.item_cost		= TabFile.Search_Posistion(i,7)->iValue;

		m_traps[trap.id] = trap;
	}
}

//void CfgData::fetchVip()
//{
//	CDBCFile TabFile(0);
//	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_vip.txt");
//	if ( ret == false )
//	{
//		LOG_ERROR("打开配置表错误 cfg_vip.txt");
//		return;
//	}
//
//	int32_t iBaseTableCount			=	TabFile.GetRecordsNum();
//	int32_t iBaseColumnCount		=	TabFile.GetFieldsNum();
//	if (iBaseColumnCount <=0)
//	{
//		return ;
//	}
//	for( int32_t i = 0;i < iBaseTableCount;i++ )
//	{
//		CfgVip vip = {};
//		vip.id						= TabFile.Search_Posistion(i,0)->iValue;
//		vip.type					= TabFile.Search_Posistion(i,1)->iValue;
//		vip.gold_cost				= TabFile.Search_Posistion(i,2)->iValue;
//		vip.remain					= TabFile.Search_Posistion(i,3)->iValue;
//		vip.exp_addon_ratio			= TabFile.Search_Posistion(i,4)->iValue;
//		vip.fly_free				= TabFile.Search_Posistion(i,5)->iValue;
////		vip.daily_gift				= TabFile.Search_Posistion(i,0)->iValue;
//		vip.no_cd_enhance			= TabFile.Search_Posistion(i,6)->iValue;
//		vip.yumajian				= TabFile.Search_Posistion(i,7)->iValue;
//		vip.yanwuchang_middle		= TabFile.Search_Posistion(i,8)->iValue;
//		vip.yanwuchang_advance		= TabFile.Search_Posistion(i,9)->iValue;
//		vip.entrust_cd_reduce		= TabFile.Search_Posistion(i,10)->iValue;
//		vip.bagua_time_addon		= TabFile.Search_Posistion(i,11)->iValue;
//		vip.relief_addon			= TabFile.Search_Posistion(i,12)->iValue;
//		vip.order					= TabFile.Search_Posistion(i,13)->iValue;
//		vip.attr_addon				= parseEquipEffect(vip.type, TabFile.Search_Posistion(i,14)->pString);
//		vip.buy_num					= TabFile.Search_Posistion(i,15)->iValue;
//		m_vips[vip.type] = vip;
//	}
//}

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
		if (strMines.size() == 6)
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

AttrAddonVector CfgData::parseItemEffect(int32_t id, const std::string &str)//解析物品作用效果
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
			else
			{
				LOG_ERROR("CfgData::parseTaskItemString wrong data with id = %d, string = %s\n", id, strItems.c_str());
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
			else
			{
				LOG_ERROR("CfgData::parseTaskItemJobString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}

TaskDest CfgData::parseTaskDestString( int32_t id, const std::string &strItems )
{
	TaskDest dest = {};
	if ( !strItems.empty() )
	{
		StringVector vstr = Answer::StringUtility::split( strItems, "<>" );
		for ( uint32_t i = 0; i < vstr.size(); ++i )
		{
			if ( vstr[i] == "l" )
			{
				if ( vstr[i+1].size() == 1 )
				{
					dest.type = vstr[i+1][0];
					dest.pram = atoi(vstr[i+2].c_str());
				}
			}
		}

		//int e1 = strItems.find_first_of( "<l>" );
		//int e2 = strItems.find_first_of( "</l>" );
		//if ( e1 == -1 || e2 == -1 )
		//{
		//	return dest;
		//}

		//std::string str = strItems.substr( e1+3, e2-e1 );
		//if ( !str.empty() )
		//{
		//	int ee1 = str.find_first_of( "<" );
		//	int ee2 = str.find_first_of( ">" );
		//	int ee3 = str.find_last_of( "<" );
		//	if ( ee1 == -1 || ee2 == -1 || ee3 == -1 )
		//	{
		//		return dest;
		//	}
		//	std::string st = str.substr( ee1+1, ee2-ee1 );
		//	if ( !st.empty() )
		//	{
		//		dest.type = st[0];
		//	}

		//	std::string sp = str.substr( ee2+1, ee3-ee2 );
		//	if ( !sp.empty() )
		//	{
		//		dest.pram = atoi( sp.c_str() );
		//	}
		//}
	}

	return dest;
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

TaskRequest CfgData::parseTaskCondition(int32_t id, int32_t condition, const std::string &strRequest)
{
	TaskRequest request = {};

	StringVector requests = StringUtility::split(strRequest, ":");

	switch (condition)
	{
		//3个参数的
	case TC_ITEM:		//需要物品
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
		//2个参数的
	case TC_MONSTER_ID:		//指定怪物
	case TC_MONSTER_LEVEL:  //指定等级怪物
	case TC_PLANT:			//采集
	case TC_USER_SKILL:     //使用技能
	case TC_FINISH_TASK_TYPE://完成指定类型的任务
	case TC_USE_ITEM:
	case TC_DRESS_EQUIP:
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
		//1个参数的
	case TC_PLAYER_LEVEL:		//达到等级
	case TC_PET_ILLUSION:		//宠物幻化
	case TC_UP_EQUIP_STAR:		//装备强化
	case TC_UP_EQUIP_GRADE:		//装备升级
	case TC_UP_EQUIP_QUALITY:	//装备提品
	case TC_HALL_OF_FAME:
	case TC_DUNGEON:
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

void CfgData::fetchMemFamilyWar()
{
	//MySqlDBGuard db(DBPOOL);

	//MySqlQuery result = db.query("SELECT * FROM `mem_family_war`");
	//if (!result.eof())
	//{
	//	m_memFamilyWar.family_id = result.getIntValue("family_id");
	//	m_memFamilyWar.family_name = result.getStringValue("family_name");
	//}
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
	//MySqlDBGuard db(DBPOOL);

	//MySqlQuery result = db.query("SELECT `value` FROM `sys_server_config` WHERE `name`='create_time'");
	//if (!result.eof())
	//{
	//	m_createTime = atoi(result.getStringValue(0));
	//}
	//result = db.query("SELECT `value` FROM `sys_server_config` WHERE `name`='startGame_time'");
	//if (!result.eof())
	//{
	//	m_startServerTime = atoi(result.getStringValue(0));
	//}
	//else
	//{
	//	m_startServerTime = TIMER.GetNow();
	//	char mySql[1024]={0};
	//	snprintf(mySql,1023,"INSERT INTO `sys_server_config` (`name`,`value`) VALUES('%s','%d')","startGame_time",m_startServerTime);
	//	db.excute(mySql);
	//}
}

void CfgData::sendNewItems(const CfgItemTable &items)
{
	//NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_NEW_ITEM);
	//if (NULL == packet)
	//{
	//	return;
	//}
	//packet->writeInt32(static_cast<int32_t>(items.size()));
	//for (CfgItemTable::const_iterator it = items.begin(); it != items.end(); ++it)
	//{
	//	CfgItem	*pCfgItem = it->second;
	//	if (pCfgItem != NULL)
	//	{
	//		packet->writeInt32(pCfgItem->id);
	//		packet->writeUTF8(pCfgItem->name);
	//		packet->writeUTF8(pCfgItem->desc);
	//		packet->writeInt32(pCfgItem->type);
	//		packet->writeInt32(pCfgItem->level);
	//		packet->writeInt32(pCfgItem->job);
	//		packet->writeInt32(pCfgItem->in_value);
	//		packet->writeInt32(pCfgItem->out_value);
	//		packet->writeInt32(pCfgItem->bind);
	//		packet->writeInt32(pCfgItem->combine);
	//		packet->writeInt32(pCfgItem->quality);
	//		packet->writeUTF8(pCfgItem->url);
	//		packet->writeUTF8(pCfgItem->drop_url);
	//		packet->writeUTF8(pCfgItem->effect);
	//		packet->writeUTF8(pCfgItem->use_method);
	//		packet->writeInt32(pCfgItem->group_id);
	//		packet->writeInt32(pCfgItem->cd_group);
	//		packet->writeInt32(pCfgItem->overlay);
	//		packet->writeInt32(pCfgItem->can_sell);
	//		packet->writeInt32(pCfgItem->valid_time);
	//	}
	//}
	//packet->setSize(packet->getWOffset());
	//GAME_SERVICE.broadcast(packet);
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

void CfgData::setRealTimeRankLevelBase(int32_t base)
{
	m_realTimeRankLevelBase = base;
}

void CfgData::setRealTimeRankFightPowerBase(int32_t base)
{
	m_realTimeRankFightPowerBase = base;
}

int32_t CfgData::getRealTimeRankLevelBase()
{
	return m_realTimeRankLevelBase;
}

int32_t CfgData::getRealTimeRankFightPowerBase()
{
	return m_realTimeRankFightPowerBase;
}

void CfgData::fetchGmtBanChat()
{
	//MySqlDBGuard db(DBPOOL);

	//MySqlQuery result = db.query("SELECT * FROM `gmt_ban_chat`");
	//while (!result.eof())
	//{
	//	GmtBanChat banChat = {};
	//	banChat.uid = result.getIntValue("uid");
	//	banChat.expire_time = result.getIntValue("expire_time");

	//	m_banChats[banChat.uid] = banChat;

	//	result.nextRow();
	//}
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
		LOG_ERROR("open FILE_ITEM_EQUIP_TABLE 失败,请检查文件名大小写");
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
		equip.m_nId			= readFile.Search_Posistion( i, 0 )->iValue;
		equip.m_nType		= static_cast<int8_t>( readFile.Search_Posistion( i, 2 )->iValue );
		equip.m_nLevel		= readFile.Search_Posistion( i, 3 )->iValue;
		equip.m_nJob		= static_cast<int8_t>( readFile.Search_Posistion( i, 4 )->iValue );
		equip.m_nPrice		= readFile.Search_Posistion( i, 5 )->iValue;
		equip.m_nQuality	= static_cast<int8_t>( readFile.Search_Posistion( i, 6 )->iValue );
		equip.m_nSuitId		= readFile.Search_Posistion( i, 7 )->iValue;

		int32_t nIndex = 8;
		for ( int32_t j = 0; j < MAX_EQUIP_BASE_ATTR_COUNT; ++j )
		{
			equip.m_vAttr[j].index	= readFile.Search_Posistion( i, nIndex )->iValue;
			++nIndex;
			equip.m_vAttr[j].addon	= readFile.Search_Posistion( i, nIndex )->iValue;	
			++nIndex;
		}
		for ( int32_t k = 0; k < MAX_EQUIP_BASE_ATTR_COUNT; ++k )
		{
			equip.m_StarAttr[k].index = readFile.Search_Posistion( i, nIndex )->iValue;
			++nIndex;
			equip.m_StarAttr[k].addon = readFile.Search_Posistion( i, nIndex )->iValue;
			++nIndex;
		}
		equip.m_nGrade			= readFile.Search_Posistion( i, nIndex )->iValue;
		++nIndex;
		equip.m_nRansomWorth	= readFile.Search_Posistion( i, nIndex )->iValue;
		m_cfgEquip.AddEquip( equip );
	}
}

void CfgData::InitEquipUpGradeTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ITEM_EQUIP_UP_GRADE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_ITEM_EQUIP_UP_GRADE_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_EQUIP_UP_QUALITY_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_EQUIP_UP_STAR_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_EQUIP_ADD_ATTR_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_EQUIP_GOAL_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_EQUIP_SUIT_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_GEM_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_ITEM_COMBI_TABLE 失败,请检查文件名大小写");
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
		//名字这行不读
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
		LOG_ERROR("open FILE_BAG_SLOT_OPEN_TIME_TABLE 失败,请检查文件名大小写");
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

void CfgData::InitPetTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_TABLE 失败,请检查文件名大小写");
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

			// 技能概率加权
			nRate += readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			pet.m_vSkillRate[k]	= nRate;
		}
		// 幻兽ICON	//幻兽模型	//蛋的ICON	//孵化成功后ICON
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
		m_cfgPetTable.Add( pet );
	}
}

const CfgPetTable& CfgData::GetPetTable() const
{
	return m_cfgPetTable;
}

void CfgData::InitPetAttrInitRateTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_PET_INIT_ATTR_RATE_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_PET_INIT_ATTR_RATE_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_PET_ILLUSION_GROW_TABLE 失败,请检查文件名大小写");
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
		grow.nVicePoint		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		grow.nViceLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

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
		LOG_ERROR("open FILE_PET_KNIGHT_TABLE 失败,请检查文件名大小写");
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
			LOG_ERROR("open FILE_PET_KNIGHT_TABLE 失败,未定义的幻兽骑士类型");
			return;
		}
		++nIndex;	// 名称
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
		++nIndex;	// 描述
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
		LOG_ERROR("open FILE_PET_HATCH_POOL_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_PET_LUCKY_ITEM_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_FAMILY_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_FAMILY_POSITION_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_FAMILY_PET_REGIST_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_TEAM_BUFF_TABLE 失败,请检查文件名大小写");
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

void CfgData::InitSkillLevelUpTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_SKILL_LEVEL_UP_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_SKILL_LEVEL_UP_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_TASK_CYCLE_STAR_TABLE 失败,请检查文件名大小写");
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
		int8_t	nStar	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		bzero( vRate, sizeof( vRate ) );
		int32_t nMaxRate = 0;
		for ( int32_t j = 0; j < MAX_CYCLE_STARS; ++j )
		{
			nMaxRate	+= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
			vRate[j] = nMaxRate;
		}

		m_cfgTaskCycleTable.AddStarRate( nStar, vRate, nMaxRate );
	}
}

const CfgTaskCycleTable& CfgData::GetTaskCycleTable() const
{
	return m_cfgTaskCycleTable;
}


void CfgData::InitFriendExpTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FRIEND_EXP_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FRIEND_EXP_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_PK_DROP_RATE_TABLE 失败,请检查文件名大小写");
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
		LOG_ERROR("open FILE_QIANG_HUA_WORTH_TABLE 失败,请检查文件名大小写");
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

void CfgData::InitMountTrainTable()
{
	CDBCFile MountTrainFile(0);
	bool ret = MountTrainFile.OpenFromTXT("./ServerConfig/Tables/MountTrainTable.txt");
	if ( ret == false )
	{
		LOG_ERROR("open MountTrainTable.txt 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	MountTrainFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	MountTrainFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return ;
	}

	int32_t iValue =0;
	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		GameMountTrain stu;

		stu.m_MountLevel		= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,0)->iValue);
		stu.m_MountName			= MountTrainFile.Search_Posistion(i,1)->pString;
		stu.m_MountSkinID		= MountTrainFile.Search_Posistion(i,2)->iValue;
		stu.m_MinLucky			= MountTrainFile.Search_Posistion(i,3)->iValue;
		stu.m_MaxLucky			= MountTrainFile.Search_Posistion(i,4)->iValue;
		stu.m_Rate				= MountTrainFile.Search_Posistion(i,5)->iValue;
		stu.m_GetLucky			= MountTrainFile.Search_Posistion(i,6)->iValue;
		stu.m_NeedZiYuanType	= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,7)->iValue);
		stu.m_NeedZiyuanCount	= MountTrainFile.Search_Posistion(i,8)->iValue;
		//stu.m_NeedItemClass		= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,9)->iValue);
		stu.m_NeedItemId		= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,9)->iValue);
		//stu.m_NeedItemBingID	= MountTrainFile.Search_Posistion(i,11)->iValue;
		//stu.m_NeedItemUnBingID	= MountTrainFile.Search_Posistion(i,12)->iValue;
		stu.m_NeedItemCount		= MountTrainFile.Search_Posistion(i,10)->iValue;
		stu.m_IsActiveSkill		= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,11)->iValue);
		stu.m_IsCleanLuck		= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,12)->iValue);
		stu.m_CanEatMountHeart	= MountTrainFile.Search_Posistion(i,13)->iValue;
		stu.m_AddSpeed			= MountTrainFile.Search_Posistion(i,14)->iValue;

		for ( uint8_t j = 0; j < 7; j++ )
		{
			AddAttribute Attr;
			Attr.m_nAddAttrType		= static_cast<uint8_t>(MountTrainFile.Search_Posistion(i,15+(j*2) )->iValue);
			Attr.m_nAddAttrValue	= MountTrainFile.Search_Posistion(i,15 + (j*2) + 1 )->iValue;
			if ( Attr.m_nAddAttrValue > 0 )
			{
				stu.m_AddAttrList.push_back(Attr);
			}
		}
		m_MountTrainTBL.m_MountTrainMap[stu.m_MountLevel] = stu;
	}
}

void CfgData::InitMountHearAttrTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( "./ServerConfig/Tables/HearAttrTable.txt" );
	if ( ret == false )
	{
		LOG_ERROR("open HearAttrTable 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}
	CMountHeartTBL.clear();
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CMountHeart stu;
		stu.m_Type					= (uint8_t)readFile.Search_Posistion( i, 0 )->iValue;
		stu.m_NeedMountQuaLity		= (uint8_t)readFile.Search_Posistion( i, 1 )->iValue;
		//stu.m_NeedItemClass			= (uint8_t)readFile.Search_Posistion( i, 2 )->iValue;
		stu.m_NeedItemId			= (uint8_t)readFile.Search_Posistion( i, 2 )->iValue;
		//stu.m_NeedItemBingID		= readFile.Search_Posistion( i, 4 )->iValue;
		//stu.m_NeedItemUnBingID		= readFile.Search_Posistion( i, 5 )->iValue;
		for ( uint8_t j = 0; j < 7; j++ )
		{
			AddAttribute Attr;
			Attr.m_nAddAttrType  = static_cast<uint8_t>(readFile.Search_Posistion( i, 3+ j*2 )->iValue);
			Attr.m_nAddAttrValue = readFile.Search_Posistion( i, 3+ j*2 + 1)->iValue;
			if ( Attr.m_nAddAttrValue > 0)
			{
				stu.m_AddAttrList.push_back(Attr);
			}
		}
		CMountHeartTBL[stu.m_Type] = stu;
	}
}
void CfgData::InitMountSkillTable()
{

	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( "./ServerConfig/Tables/MountSkillLearn.txt" );
	if ( ret == false )
	{
		LOG_ERROR("open MountSkillLearn 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount		=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	int32_t iValue = 0;
	m_LearMountSkillTabl.clear();
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CLearnMountSkillTBL stu;
		stu.m_SkillType			= static_cast<uint8_t>(readFile.Search_Posistion( i, 0 )->iValue);
		stu.m_SkillName			= readFile.Search_Posistion( i, 1 )->pString;
		stu.m_NeedMountLevel	= static_cast<uint8_t>(readFile.Search_Posistion( i, 2 )->iValue);
		stu.m_StudyItemId		= static_cast<uint8_t>(readFile.Search_Posistion( i, 3 )->iValue);
		stu.m_StudyItemCount	= readFile.Search_Posistion( i, 4 )->iValue;
		stu.m_SkillEsc			= readFile.Search_Posistion( i, 5 )->pString;
		m_LearMountSkillTabl[stu.m_SkillType] = stu;
	}
}
void CfgData::InitMountSkillLevelUp()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( "./ServerConfig/Tables/MountSkillUp.txt" );
	if ( ret == false )
	{
		LOG_ERROR("open MountSkillUp.txt 失败,请检查文件名大小写");
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
		MountSKillLevelUp stu;
		stu.m_Index				= (uint8_t)readFile.Search_Posistion( i, 0 )->iValue;
		stu.m_SkillType			= (uint8_t)readFile.Search_Posistion( i, 1 )->iValue;
		stu.m_SkillLevel		= (uint8_t)readFile.Search_Posistion( i, 2 )->iValue;
		//stu.m_UpItemClass		= (uint8_t)readFile.Search_Posistion( i, 3 )->iValue;
		stu.m_UpItemId		= (uint8_t)readFile.Search_Posistion( i, 3 )->iValue;
		//stu.m_UpItemBingID		= readFile.Search_Posistion( i, 5 )->iValue;
		//stu.m_UpItemUnBingID	= readFile.Search_Posistion( i, 6 )->iValue;
		stu.m_UpItemCount		= readFile.Search_Posistion( i, 4 )->iValue;
		stu.m_AttrType			= (uint8_t)readFile.Search_Posistion( i, 5 )->iValue;
		stu.m_AttrRate			= readFile.Search_Posistion( i, 6 )->iValue;
		m_MountSkillLevelUpTable.Add(stu);
	}
}

GameMountTrainTBL&  CfgData::GetMountTrainTab()
{
	return m_MountTrainTBL;
}

CMountHeartMap& CfgData::	GetMountHeart()
{
	return CMountHeartTBL;
}

LearnMountSkillMap& CfgData::GetMountSkillTable()
{
	return m_LearMountSkillTabl;
}

MountSKillLevelUpTabl& CfgData::GetMountSkillLevelTable()
{
	return m_MountSkillLevelUpTable;
}

void CfgData::InitBuyFaBaoResTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_BUY_FA_BAO_RES_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_BUY_FA_BAO_RES_TABLE.txt 失败,请检查文件名大小写");
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

CfgDaTiHD&	CfgData::GetDaTiCfg()
{
	return m_DaTiHDCfg;
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
	//CDBCFile readFile(0);
	//bool ret = readFile.OpenFromTXT( FILE_DA_TI_HD_TABLE );
	//if ( ret == false )
	//{
	//	LOG_ERROR("open FILE_DA_TI_HD_TABLE.txt 失败,请检查文件名大小写");
	//	return;
	//}

	//int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	//int32_t iBaseColumnCount		=	readFile.GetFieldsNum();
	//if ( iBaseColumnCount <= 0 )
	//{
	//	return;
	//}

	//int32_t iValue = 0;
	//for( int32_t i = 0;i < iBaseTableCount; ++i )
	//{
	//	bzero( &m_DaTiHDCfg,sizeof( m_DaTiHDCfg ) );
	//	m_DaTiHDCfg.StartSeconds	= readFile.Search_Posistion( i, 1 )->iValue * 60;
	//	m_DaTiHDCfg.HDTime			= readFile.Search_Posistion( i, 2 )->iValue * 60;
	//}

	//CDBCFile ReadFile(0);
	//bool Ret = ReadFile.OpenFromTXT( FILE_QUESTIONS_TABLE );
	//if ( Ret == false )
	//{
	//	LOG_ERROR("open FILE_QUESTIONS_TABLE.txt 失败,请检查文件名大小写");
	//	return;
	//}

	//int32_t BaseTableCount			=	ReadFile.GetRecordsNum();
	//int32_t BaseColumnCount			=	ReadFile.GetFieldsNum();
	//if ( BaseColumnCount <= 0 )
	//{
	//	return;
	//}
	//m_QuestionsVct.clear();
	//for( int32_t j = 0;j < BaseTableCount; ++j )
	//{
	//	CfgQuestions Stu = {};
	//	Stu.QuestionId		= ReadFile.Search_Posistion( j, 0 )->iValue;
	//	Stu.AnswerId		= (int8_t)ReadFile.Search_Posistion( j, 6 )->iValue;
	//	m_QuestionsVct.push_back( Stu );
	//}
}

void CfgData::InitFaBaoTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FA_BAO_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FA_BAO_TABLE.txt 失败,请检查文件名大小写");
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
		Pos.x						= InitBossFile.Search_Posistion(i,1)->iValue;
		Pos.y						= InitBossFile.Search_Posistion(i,2)->iValue;
		stu.m_RevivePosVector		= paresPosition(InitBossFile.Search_Posistion(i,3)->pString);
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
		for ( int32_t j = 0; j < PET_ATTR_COUNT; ++j )
		{
			PetGift.m_vMaxAttr[j]	= PetGiftTable.Search_Posistion(i, 4 + j )->iValue;
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
			&& it->second.ShopType != BANG_SHI_SHANG_CHENG_TYPE )	// 相同id可能在绑石商城中存在
		{
			return &(it->second);
		}
	}
	return NULL;
}