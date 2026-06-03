#include "stdafx.h"
#include "PetRank.h"
#include "FileDef.h"
#include "PetManager.h"
#include "PlayerManager.h"
#include "SocialService.h"
#include "SocialDaTiHD.h"
#include "FamilyManager.h"
#include "HallOfFame.h"
#include "RankManager.h"
#include "ZSZZDungeon.h"
#include <string>
#include <algorithm>
using namespace Answer;
using namespace std;

SocialService::SocialService()
	: TcpService(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER, 2048-NET_PACKET_HEAD_LEN, 0, 2000, "SocialService"), m_createTime(0)
{
	m_ItemLimitMap.clear();
	m_serverdiffDay		= 0;
}

SocialService::~SocialService()
{

}

void SocialService::onNetPacket(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	uint16_t proc = inPacket->getProc();
	if ( (proc > CM_SOCIAL_MIN && proc < CM_SOCIAL_MAX) || (proc > IM_GAME_SOCIAL_MIN && proc < IM_GAME_SOCIAL_MAX) )
	{
		int16_t cgindex = static_cast<int16_t>(inPacket->readInt32());
		SocialPlayer *player = PLAYER_MANAGER.GetPlayerByGateIndex( cgindex );
		if (player != NULL)
		{
			player->handleNetPacket(inPacket);
		}
	}
	else
	{
		switch (proc)
		{
		case CM_GM_RELOAD_INFO: onGMReloadInfo(inPacket); break;
		case IM_GATE_UPDATE_BAN_CHAT: onUpdateBanChat(inPacket); break;
		//case IM_SOCIAL_ADD_PLAYER_INFO: onAddPlayerInfo(inPacket); break;
		case IM_SOCIAL_UPDATE_PLAYER_INFO: onUpdatePlayerInfo(inPacket); break;
		case IM_SOCIAL_ADD_PLAYER: onAddPlayer(inPacket); break;
		//case IM_SOCIAL_FAMILY_ACTIVITY_PLAYER:onFamilyActivityPlayer(inPacket);break;
		//case IM_SOCIAL_WORLD_BOSS_ACTIVITY_RESULT: onWorldBossActivityResult(inPacket);break;
		case IM_SOCIAL_REMOVE_PLAYER: onRemovePlayer(inPacket); break;
		case IM_SOCIAL_NEW_MINUTE_COME: onNewMinuteCome(inPacket); break;
		//case IM_SOCIAL_FAMILY_WAR: onFamilyWar(inPacket); break;
		case IM_SOCIAL_ACTIVITY_CLEAR:onActivityClear(inPacket);break;
		//case IM_SOCIAL_UPDATE_GAMBLE:onUpdateGambleRecord(inPacket);break;

		case IM_SOCIAL_UPDATE_PET_DATA:			onUpdatePetData( inPacket );	break;
		case IM_SOCIAL_DELETE_PET_DATA:			onDeletePetData( inPacket );	break;

		case IM_SOCIAL_REQUEST_PET_RANK_DATA:	onRequestPetRankData( inPacket );	break;
 		case IM_SOCIAL_DA_TI_START_READY:	SOCIAL_DA_TI_HD.OnRecvHDReadyStart( inPacket ); break;	
 		case IM_SOCIAL_DA_TI_START:			SOCIAL_DA_TI_HD.OnRecvHDStart( inPacket ); break;
 		case IM_SOCIAL_DA_TI_END:			SOCIAL_DA_TI_HD.OnRecvHDEnd( inPacket ); break;
 		case IM_SOCIAL_QUESTIONS:			SOCIAL_DA_TI_HD.OnRecvQuestionsInfo( inPacket );break;
		case IM_SOCIAL_RAND_ANSWER:			SOCIAL_DA_TI_HD.OnRecvRandAnswer();break;
		case IM_SOCIAL_UPDATE_ZSZZ:			ZSZZ_DUNGEON_RANK.OnUpdateRankInfo( inPacket ); break;
		case IM_SOCIAL_SYN_SERVER_DAY:		onUpdateServerDiffDay( inPacket ); break;
		case IM_SOCIAL_REQUEST_FAMILY_INFO: onUpdateFamilyInfo(inPacket);break;
		default: break;
		}
	}
	inPacket->destroy();
}

void SocialService::startSocial()
{
	initFamily();
	//fetchFamilyLevel();
	fetchBanChat();
	fetchCreateTime();
	fetchNewServerActivity();
	fetchActivity();
	refreshRanks(false);
	//initRealTimeRank();
	InitShangChengTable();

	m_secondRecord = DayTime::now();
}

bool sortInt(const int32_t&left,const int32_t&right)
{
	if(left <right)
	{
		return true;
	}
	return false;
};

void SocialService::stopSocial()
{
	
}

void SocialService::fetchActivity()
{
	CDBCFile TabFile(0);
	bool ret = TabFile.OpenFromTXT("./ServerConfig/Tables/cfg_activity.txt");
	if ( ret == false )
	{
		LOG_ERROR("打开配置表错误 cfg_activity.txt");
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
		CfgActivity activity = {};
		activity.id			= TabFile.Search_Posistion(i,0)->iValue;
		int32_t weekday		= TabFile.Search_Posistion(i,9)->iValue;
		while (weekday > 0)
		{
			activity.weekday.push_back(weekday%10);
			weekday /= 10;
		}
		activity.startTime = TabFile.Search_Posistion(i,14)->iValue;

		if (activity.id == 1)
		{
			m_activity[activity.id] = activity;
		}
		else if (activity.id == 8)
		{
			m_activity[activity.id] = activity;
		}
	}
}

//void SocialService::fetchFamilyLevel()
//{
//	CDBCFile FamilyFile(0);
//	bool ret = FamilyFile.OpenFromTXT("./ServerConfig/Tables/cfg_family_level.txt");
//	if ( ret == false )
//	{
//		LOG_ERROR("open cfg_family_level.txt failed,please check!!");
//		return;
//	}
//
//	int32_t iBaseTableCount		=	FamilyFile.GetRecordsNum();
//	int32_t iBaseColumnCount	=	FamilyFile.GetFieldsNum();
//	if (iBaseColumnCount <=0)
//	{
//		return ;
//	}
//
//	for( int32_t i = 0;i < iBaseTableCount;i++ )
//	{
//		CfgFamilyLevel level	= {};
//		level.level				= FamilyFile.Search_Posistion(i,0)->iValue;
//		level.cost_money		= FamilyFile.Search_Posistion(i,1)->iValue;
//		level.niceleader_count	= FamilyFile.Search_Posistion(i,3)->iValue;
//		level.elder_count		= FamilyFile.Search_Posistion(i,2)->iValue;
//
//		m_familyLevel[level.level] = level;
//	}
//	////////////////////////////////////////////////////////
//	/*MySqlDBGuard db(DBPOOL);
//
//	MySqlQuery result = db.query("SELECT * FROM `cfg_family_level`");
//	while (!result.eof())
//	{
//		 CfgFamilyLevel level = {};
//		 level.level = result.getIntValue("level");
//		 level.cost_money = result.getIntValue("cost_money");
//		 level.niceleader_count = result.getIntValue("niceleader_count");
//		 level.elder_count = result.getIntValue("elder_count");
//
//		 m_familyLevel[level.level] = level;
//		 result.nextRow();
//	}*/
//}

//PlayerInfo* SocialService::getPlayerInfo(int32_t cid)
//{
//	Int32PlayerInfoMap::iterator it = m_cidPlayerInfo.find(cid);
//	if (it != m_cidPlayerInfo.end())
//	{
//		return it->second;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.name, a.sex, a.job,a.vip,a.level,a.sid,a.uid,a.last_logout_time,b.family_id,c.LimitCount FROM `mem_character` As a LEFT JOIN `mem_chr_family` As b ON a.cid = b.cid LEFT JOIN `mem_char_operate_limit` As c ON a.cid = c.cid and c.LimitId=37204 WHERE a.cid =%d", cid);
//	MySqlQuery result = db.query(szSQL);
//	if (result.getRowCount() <= 0)
//	{
//		return NULL;
//	}
//
//	PlayerInfo *playerInfo = new PlayerInfo();
//	if (NULL == playerInfo)
//	{
//		return NULL;
//	}
//	playerInfo->nCharId = cid;
//	playerInfo->strName = result.getStringValue("name");
//	playerInfo->nSex = result.getIntValue("sex");
//	playerInfo->nJob = result.getIntValue("job");
//	//playerInfo->kingdom = result.getIntValue("kingdom");
//	playerInfo->nLevel = result.getIntValue("level");
//	playerInfo->nLastLogoutTime = result.getIntValue("last_logout_time");
//	//playerInfo->fightPower =result.getIntValue("fight_power");
//	//playerInfo->kingdom_contribute = result.getIntValue("kingdom_contribute");
//	playerInfo->bLearnedXP = result.getIntValue("LimitCount") > 0;
//	playerInfo->nVip = static_cast<VipType>(result.getIntValue("vip"));
//	//playerInfo->nFamilyId = result.getIntValue("family_id");
//
//	m_cidPlayerInfo[playerInfo->nCharId] = playerInfo;
//	m_namePlayerInfo[playerInfo->strName] = playerInfo;
//
//	return playerInfo;
//}
//
//int32_t SocialService::updatePlayerInfo(int32_t cid, std::string name)
//{
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_character` SET `name`='%s' WHERE `cid`=%d", name.c_str(), cid);
//
//	MySqlDBGuard db(DBPOOL);
//
//	int32_t err = db.excute(szSQL);
//	if (err	== ERR_ANSWER_OK)
//	{
//		Int32PlayerInfoMap::iterator itCid = m_cidPlayerInfo.find(cid);
//		if (itCid != m_cidPlayerInfo.end())
//		{
//			PlayerInfo *playerInfo = itCid->second;
//			if (playerInfo != NULL)
//			{
//				string oldName = playerInfo->strName;
//
//				StringPlayerInfoMap::iterator itName = m_namePlayerInfo.find(playerInfo->strName);
//				if (itName != m_namePlayerInfo.end())
//				{
//					m_namePlayerInfo.erase(itName);
//					playerInfo->strName = name;
//					m_namePlayerInfo[playerInfo->strName] = playerInfo;
//				}
//			}
//		}
//	}
//
//	return err;
//}
//
//PlayerInfo* SocialService::getPlayerInfo(const std::string &name)
//{
//	StringPlayerInfoMap::iterator it = m_namePlayerInfo.find(name);
//	if (it != m_namePlayerInfo.end())
//	{
//		return it->second;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.name, a.sex, a.job,a.vip,a.level,a.sid,a.uid,a.last_logout_time,b.family_id,c.LimitCount FROM `mem_character` As a LEFT JOIN `mem_chr_family` As b ON a.cid = b.cid LEFT JOIN `mem_char_operate_limit` As c ON a.cid = c.cid and c.LimitId=37204 WHERE `name`='%s'", name.c_str());
//	MySqlQuery result = db.query(szSQL);
//	if (result.getRowCount() <= 0)
//	{
//		return NULL;
//	}
//	PlayerInfo *playerInfo = new PlayerInfo;
//	if (NULL == playerInfo)
//	{
//		return NULL;
//	}
//	playerInfo->nCharId = result.getIntValue("cid");
//	playerInfo->strName = name;
//	playerInfo->nSex = result.getIntValue("sex");
//	playerInfo->nJob = result.getIntValue("job");
//	//playerInfo->kingdom = result.getIntValue("kingdom");
//	playerInfo->nLevel = result.getIntValue("level");
//	playerInfo->nLastLogoutTime = result.getIntValue("last_logout_time");
//	//playerInfo->fightPower =result.getIntValue("fight_power");
//	//playerInfo->kingdom_contribute = result.getIntValue("kingdom_contribute");
//	playerInfo->bLearnedXP = result.getIntValue("LimitCount") > 0;
//	playerInfo->nVip = static_cast<VipType>(result.getIntValue("vip"));
//	playerInfo->nFamilyId = result.getIntValue("family_id");
//
//	m_cidPlayerInfo[playerInfo->nCharId] = playerInfo;
//	m_namePlayerInfo[playerInfo->strName] = playerInfo;
//	return playerInfo;
//}


//int32_t SocialService::getCidByName(const std::string &name)
//{
//	StringPlayerInfoMap::iterator it = m_namePlayerInfo.find(name);
//	if (it != m_namePlayerInfo.end())
//	{
//		return it->second->nCharId;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//	char szSQL[MAX_SQL_LENGTH] = {}; 
//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT `cid` FROM `mem_character` WHERE `name`= '%s'",name.c_str());
//	MySqlQuery result = db.query(szSQL);
//
//	if (result.getRowCount() > 0)
//	{
//		return result.getIntValue("cid");
//	}
//	return -1;
//}

//int32_t SocialService::getPlayerFamilyId(int32_t cid)
//{
//	MySqlDBGuard db(DBPOOL);
//
//	int32_t fid = 0;
//	{
//		char szSQL[MAX_SQL_LENGTH] = {};
//		snprintf(szSQL, sizeof(szSQL)-1, "SELECT `family_id` FROM `mem_chr_family` WHERE `cid`=%d", cid);
//		MySqlQuery result = db.query(szSQL);
//		if (result.getRowCount() > 0)
//		{
//			fid = result.getIntValue("family_id");
//		}
//	}
//
//	return fid;
//}

//void SocialService::clearFamilyApply(int32_t cid) 
//{
//	    MutexGuard lock(m_familyInfoLock);
//
//	    for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin();it != m_fidFamilyInfo.end();++it)
//	    {
//			 for (FamilyApplyInfoVector::iterator iter = it->second.appliers.begin();iter != it->second.appliers.end();++iter)
//			 {
//				  if (iter->cid == cid)
//				  {
//					   it->second.appliers.erase(iter);
//					   break;
//				  }
//			 }
//	    }
//}

//void  SocialService::getFamilyRewardList(int32_t type,int32_t kingdom,FamilyRewardInfoVector rewardInfo)
//{
// 	   MutexGuard lock(m_familyInfoLock);
// 
// 	   int32_t tempValue = 0;
// 	   for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin();it != m_fidFamilyInfo.end();++it)
// 	   {
// 		     if (it->second.kingdom == kingdom && (it->second.chuhan_war_ratio >= tempValue || rewardInfo.size() <= 5 ))
// 		     {
// 				 FamilyRewardInfo   info = {};
// 				 info.family_id = it->first;
// 				 info.name = it->second.name;
// 				 info.value = it->second.chuhan_war_ratio;
// 
// 				 rewardInfo.push_back(info);
// 		     }
// 	   }
//
//}
//
//FamilyInfo* SocialService::getFamilyInfo(int32_t fid)
//{
//	MutexGuard lock(m_familyInfoLock);
//	Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.find(fid);
//	if (it != m_fidFamilyInfo.end())
//	{
//		return &it->second;
//	}
//	else
//	{
//		return NULL;
//	}
//}

//CfgFamilyLevel* SocialService::getCfgFamilyLevel(int32_t level)
//{
//	CfgFamilyLevelTable::iterator it = m_familyLevel.find(level);
//	if (it != m_familyLevel.end())
//	{
//		return &(it->second);
//	}
//	
//	return NULL;
//}


//FamilyInfo* SocialService::getFamilyInfoByCid(int32_t cid)
//{
//	FamilyInfo* pFm=NULL;
//	MutexGuard lock(m_familyInfoLock);
//	Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin();
//	for (;it!=m_fidFamilyInfo.end();it++)
//	{
//		if(it->second.leader_cid ==cid)
//		{
//			pFm= &it->second;
//			break;
//		}
//	}
//	return pFm;
//}

void SocialService::getActivityRank(ActivityRankVector **activityRank)
{
	*activityRank = &m_activityRank;
}

//int32_t SocialService::setFamilyInfo(FamilyInfo* family, FamilyInfoIndex key, int32_t value,int16_t kingdom)
//{
//	std::string keyname = "";
//
//	if(family !=NULL)
//	{
//		switch (key)
//		{
//			case FII_COUNT: family->count = value; keyname = "count"; break;
//			case FII_LEVEL: family->level = value; keyname = "level"; break;
//			case FII_MONEY: family->money = value; keyname = "money"; break;
//			case FII_LEADER_CID: family->leader_cid = value; keyname = "leader_cid"; break;
//			default: return ERR_INVALID_DATA;
//		}
//
//		MySqlDBGuard db(DBPOOL);
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_family` SET `%s`='%d' WHERE `id`='%d'", keyname.c_str(), value, family->fid);
//
//		db.excute(szSQL);
//	}
//
//	
//	return ERR_OK;
//}

//FamilyMemberInfo* SocialService::getMemberInfo(FamilyInfo* family, int32_t cid)
//{
//	if (NULL == family)
//	{
//		return NULL;
//	}
//	for (FamilyMemberInfoVector::iterator it = family->members.begin(); it != family->members.end(); it++ )
//	{
//		if (it->cid == cid)
//		{
//			return &(*it);
//		}
//	}
//	return NULL;
//}

//int32_t SocialService::getPositionCount(FamilyInfo* family, int32_t pos)
//{
//	if (NULL == family)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t count = 0;
//	for (FamilyMemberInfoVector::iterator it = family->members.begin(); it != family->members.end(); it++ )
//	{
//		if (it->position == pos)
//		{
//			count++;
//		}
//	}
//	return count;
//}

//int32_t SocialService::setMemberInfo(FamilyInfo* family, int32_t cid, int32_t pos, int32_t contri)
//{
//	FamilyMemberInfo* member = getMemberInfo(family, cid);
//	if (member == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	member->position = pos;
//	member->contribute = contri;
//	
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = "";
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET `position`='%d' , `contribute`='%d'  WHERE `cid`='%d'",
//		pos, contri, cid);
//	db.excute(szSQL);
//
//	return ERR_OK;
//}

//int32_t SocialService::setMemberInfo(FamilyInfo* family, int32_t cid, FamilyMemberIndex key, int32_t value)
//{
//	FamilyMemberInfo* member = getMemberInfo(family, cid);
//	if (member == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	std::string keyname = "";
//	switch (key)
//	{
//	case FMI_POSI: member->position = value; keyname = "position"; break;
//	case FMI_CONTRI: member->contribute = value; keyname = "contribute"; break;
//	default: return ERR_INVALID_DATA;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = "";
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET `%s`='%d' WHERE `cid`='%d'", keyname.c_str(), value, cid);
//	db.excute(szSQL);
//
//	return ERR_OK;
//}

//int32_t SocialService::addMemberInfo(FamilyInfo* family, int32_t cid, FamilyMemberIndex key, int32_t addon)
//{
//	FamilyMemberInfo* member = getMemberInfo(family, cid);
//	if (member == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	std::string keyname = "";
//	int32_t newvalue = 0;
//	switch (key)
//	{
//	case FMI_CONTRI: member->contribute += addon; keyname = "contribute"; newvalue = member->contribute; break;
//	default: return ERR_INVALID_DATA;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = "";
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET `%s`='%d' WHERE `cid`='%d'", keyname.c_str(), newvalue, cid);
//	db.excute(szSQL);
//
//	return ERR_OK;
//}

//int32_t SocialService::removeMemberInfo(FamilyInfo* family, int32_t cid, bool update)
//{
//	if (NULL == family)
//	{
//		return ERR_INVALID_DATA;
//	}
//	if (update)
//	{
//		for (FamilyMemberInfoVector::iterator it = family->members.begin(); it != family->members.end(); it++ )
//		{
//			if (it->cid == cid)
//			{
//				family->members.erase(it);
//				break;
//			}
//		}
//	}
//
//	{
//		MySqlDBGuard db(DBPOOL);
//
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_chr_family` WHERE `cid`='%d'", cid);
//		db.excute(szSQL);
//	}
//
//	setFamilyInfo(family, FII_COUNT, family->count - 1);
//
//	return ERR_OK;
//}

//转职位
/*
int16_t SocialService::getPostionByContribute(int32_t cid)
{
	PlayerInfo* pPlayerInfo = getPlayerInfo(cid);
	if(pPlayerInfo != NULL)
	{
		int32_t contribute = pPlayerInfo->kingdom_contribute;
		int32_t zhenlongzhiqi = pPlayerInfo->zhenlongzhiqi;

		int32_t value = 0;
		int32_t temp = 0;
		int32_t zTemp = 0;
		for (CfgKingdomPostVector::iterator it = m_kingdomPost.begin();it != m_kingdomPost.end();++it)
		{
			if (it->contribute != 0 && it->contribute <= contribute && it->contribute >=temp)
			{
				temp = it->contribute;
				zTemp = it->zhenlongzhiqi;
				value = it->post;
			}
			else if (it->zhenlongzhiqi != 0 && it->zhenlongzhiqi <= zhenlongzhiqi && it->zhenlongzhiqi >= zTemp)
			{
				zTemp = it->zhenlongzhiqi;
				value = it->post;
			}
		}
		return value;
	}
	return 0;
}

int32_t SocialService::getPositionByContribute(int32_t contribute,int32_t zhenlongzhiqi)
{
	int32_t value = 0;
	int32_t temp = 0;
	int32_t zTemp = 0;
	for (CfgKingdomPostVector::iterator it = m_kingdomPost.begin();it != m_kingdomPost.end();++it)
	{
		if (it->contribute != 0 && it->contribute <= contribute && it->contribute >=temp)
		{
			temp = it->contribute;
			zTemp = it->zhenlongzhiqi;
			value = it->post;
		}
		else if (it->zhenlongzhiqi != 0 && it->zhenlongzhiqi <= zhenlongzhiqi && it->zhenlongzhiqi >= zTemp)
		{
			zTemp = it->zhenlongzhiqi;
			value = it->post;
		}
	}

	return value;
}*/

//int32_t SocialService::startTeamDungeon(int32_t cid)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		if (it->leader == cid)
//		{
//			m_teamDungeon.erase(it);
//			broadTeamDungeon();
//			return ERR_OK;
//		}
//	}
//
//	return ERR_INVALID_DATA;
//}

//void SocialService::broadcastInviteTeamDungeon(int32_t cid,int32_t familyID)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		if (it->leader == cid)
//		{
//			NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//			if (NULL == familyPacket)
//			{
//				continue;
//			}
//			familyPacket->writeInt32(cid);
//			familyPacket->writeUTF8(it->name);
//			familyPacket->writeInt32(it->dungeonID);
//			familyPacket->setType(PACK_DISPATCH);
//			familyPacket->setProc(SM_INVITE_TEAM_DUNGEON);
//			familyPacket->setSize(familyPacket->getWOffset());
//
//			familyBroadcast(familyID, 0, familyPacket);
//
//			break;
//		}
//	}
//}

//int32_t SocialService::kickOutTeamDungeon(int32_t cid,int32_t tcid,const std::string &name)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		for (int32_t i = 0; i < MAX_TEAM_NUM;++i)
//		{
//			if (it->num[i] > 0 && it->num[i] == cid)
//			{
//				if (it->leader == cid && !name.empty())
//				{
//					snprintf(it->name,MAX_NAME_CCH_LENGTH-1,name.c_str());
//					it->num[i] = 0;
//
//					for(int32_t j = i;j<MAX_TEAM_NUM-1;j++)
//					{
//						it->num[j] = it->num[j+1];
//					}
//					it->num[MAX_TEAM_NUM-1] = 0;
//
//					it->index--;
//					it->leader = tcid;
//
//					if (it->index == 0)
//					{
//						m_teamDungeon.erase(it);
//					}
//
//					broadTeamDungeon();
//
//					return ERR_OK;
//				}
//				else
//				{
//					it->num[i] = 0;
//					for(int32_t j = i;j<MAX_TEAM_NUM-1;j++)
//					{
//						it->num[j] = it->num[j+1];
//					}
//					it->num[MAX_TEAM_NUM-1] = 0;
//					it->index--;
//
//					if (it->index == 0)
//					{
//						m_teamDungeon.erase(it);
//					}
//
//					broadTeamDungeon();
//					return ERR_OK;
//				}
//			}
//		}
//	}
//
//	return ERR_INVALID_DATA;
//}

//bool SocialService::checkAddTeamDungeon(int32_t tcid,int32_t cid)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		if (it->leader == tcid && it->index < MAX_TEAM_NUM && it->num[it->index] != cid && it->leader != cid)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

//int32_t SocialService::addTeamDungeon(int32_t tcid,int32_t cid)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		if (it->leader == tcid && it->index < MAX_TEAM_NUM && it->num[it->index] != cid && it->leader != cid)
//		{
//			it->num[it->index] = cid;
//			it->index++;
//			
//
//			broadTeamDungeon();
//			return ERR_OK;
//		}
//	}
//
//	
//	return ERR_INVALID_DATA;
//}

//int32_t SocialService::createTeamDungeon(int32_t leader,const std::string &name,int32_t dungeonID,int32_t line)
//{
//	TeamDungeon dungeon = {};
//	dungeon.leader = leader;
//	snprintf(dungeon.name,MAX_NAME_CCH_LENGTH-1,name.c_str());
//	dungeon.index = 1;
//	dungeon.num[0] = leader;
//	dungeon.dungeonID = dungeonID;
//	dungeon.line = line;
//
//	MutexGuard lock(m_teamDungeonLock);
//	m_teamDungeon.push_front(dungeon);
//    
//	broadTeamDungeon();
//	return ERR_OK;
//}

//bool SocialService::checkCreateTeamDungeon(int32_t leader)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		if (it->leader ==leader)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

//void SocialService::clearTeamDungeon(int32_t leader)
//{
//	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//	{
//		if (it->leader == leader)
//		{
//			m_teamDungeon.erase(it);
//			break;
//		}
//	}
//
//	broadTeamDungeon();
//}

//int32_t SocialService::addFamily(int32_t cid, std::string name,std::string notice)
//{
//	int32_t familyid = 0;
//	PlayerInfo* info = getPlayerInfo(cid);
//	if (info == NULL)
//	{
//		return 0;
//	}
//
//	{
//		MySqlDBGuard db(DBPOOL);
//
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_family` (`name`, `leader_cid`, `creator_cid`, `create_time`, `level`,`kingdom`, `count`,`notice`) VALUES ('%s', '%d', '%d', '%d',1,'%d','1','%s')",
//			name.c_str(), info->cid, info->cid, DayTime::now(), info->kingdom,notice.c_str());
//		db.excute(szSQL);
//
//		familyid = db.lastInsertId();
//	}
//
//	MutexGuard lock(m_familyInfoLock);
//	FamilyInfo familyInfo = {};
//	familyInfo.fid = familyid;
//	familyInfo.name = name;
//	familyInfo.leader_cid = info->cid;
//	familyInfo.leader_name = info->name;
//	familyInfo.kingdom = info->kingdom;
//	familyInfo.level = 1;
//	familyInfo.notice = notice;
//	familyInfo.vip = info->vip;
//
//	addFamilyMember(&familyInfo, info->cid, info->name,FP_LEADER);
//	m_fidFamilyInfo[familyInfo.fid] = familyInfo;
//
//	return familyid;
//}

//int32_t SocialService::getFamilyTotal(int32_t nKingDomId)
//{
//	MutexGuard lock(m_familyInfoLock);
//	Int32FamilyInfoMap::iterator item =m_fidFamilyInfo.begin();
//	int32_t nTotal=0;
//	for (;item!=m_fidFamilyInfo.end();item++)
//	{
//		FamilyInfo fItem=item->second;
//		if (fItem.kingdom == nKingDomId) nTotal++;
//	}
//	return nTotal;
//}

//int32_t SocialService::addFamilyMember(FamilyInfo* family, int32_t cid, const std::string &name,int pos)
//{
//	if (NULL == family)
//	{
//		return ERR_INVALID_DATA;
//	}
//	if (family->count >= FAMAILY_MEMBER_COUNT+(family->level-1)*5) //too many
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (pos == FP_MEMBER)
//	{
//		FamilyApplyInfoVector::iterator itv;
//		for (itv = family->appliers.begin(); itv != family->appliers.end(); itv++ )
//		{
//			if (itv->cid == cid)
//			{
//				break;
//			}
//		}
//
//		if (itv == family->appliers.end()) //if no find, err
//		{
//			return ERR_INVALID_DATA;
//		}
//	}
//
//	{
//		MySqlDBGuard db(DBPOOL);
//
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_chr_family` (`cid`, `family_id`, `position`, `contribute`) VALUES ('%d', '%d', '%d', '0')",
//			cid, family->fid, pos);
//		db.excute(szSQL);
//	}
//
//	FamilyMemberInfo member = {};
//	member.cid = cid;
//	member.position = pos;
//	snprintf(member.name,MAX_NAME_CCH_LENGTH-1,name.c_str());
//	
//	family->members.push_back(member);
//
//	setFamilyInfo(family, FII_COUNT, family->count + 1);
//
//	return ERR_OK;
//}

//int32_t SocialService::addFamilyApplier(const Int32Vector &nums, int32_t cid, int32_t ckingdom ,Int32Int32Map & applyFid)
//{
//
//	for (Int32Vector::const_iterator it = nums.begin();it != nums.end();++it)
//	{
//		FamilyInfo* family = getFamilyInfo(*it);
//		if (family == NULL)
//		{
//			return ERR_INVALID_DATA;
//		}
//
//		if (family->kingdom != ckingdom)
//		{
//			return ERR_INVALID_DATA;
//		}
//
//		if (hasFamilyApplier(family, cid))
//		{
//			return ERR_FAMILY_ALREADY_APPLIED;
//		}
//
//		PlayerInfo* player = getPlayerInfo(cid);
//		if (player == NULL)
//		{
//			return ERR_INVALID_DATA;
//		}
//
//		FamilyApplyInfo applyInfo = {};
//		applyInfo.familyID = *it;
//		applyInfo.cid = cid;
//		applyInfo.time = DayTime::now();
//		applyInfo.name = player->name;
//		applyInfo.level = player->level;
//		applyInfo.job = player->job;
//
//		family->appliers.push_back(applyInfo);
//
//		applyFid[*it] = *it;
//		broadcastFamilyApply(*it, player->name);
//	}
//
//
//	sendAddFamilyApplier(player->kingdom,cid,fid);
//	
//
//	return ERR_OK;
//}

//void  SocialService::removeAllFamilyApplier(int32_t tcid)
//{
//	MutexGuard lock(m_familyInfoLock);
//	for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin(); it != m_fidFamilyInfo.end(); it++)
//	{
//		removeFamilyApplier(&it->second, tcid);
//	}
//}

//int32_t SocialService::removeFamilyApplier(FamilyInfo* family, int32_t cid)
//{
//	if (NULL == family)
//	{
//		return ERR_INVALID_DATA;
//	}
//	for (FamilyApplyInfoVector::iterator itv = family->appliers.begin(); itv != family->appliers.end(); itv++ )
//	{
//		if (itv->cid == cid)
//		{
//			family->appliers.erase(itv);
//			break;
//		}
//	}
//
//	return ERR_OK;
//}

//void SocialService::loadFamilyApply(Int32Int32Map &familyApply,int32_t cid)
//{
//	MutexGuard lock(m_familyInfoLock);
//	for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin(); it != m_fidFamilyInfo.end(); it++)
//	{
//		for(FamilyApplyInfoVector::iterator iter = it->second.appliers.begin();iter != it->second.appliers.end();++iter)
//		{
//			if (iter->cid == cid)
//			{
//				familyApply[it->second.fid] = it->second.fid;
//			}
//		}
//	}
//}

//int32_t SocialService::approveFamilyApply(int32_t fid, int32_t cid, int32_t tcid, int32_t result)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (!hasFamilyApplier(family, tcid))
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* judger = getMemberInfo(family, cid);
//	if (judger == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (judger->position < FP_VICE_LEADER)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	PlayerInfo* player = getPlayerInfo(tcid);
//	if (player == NULL || player->kingdom != family->kingdom)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (result == 1 && getPlayerFamilyId(tcid) == 0) //pass
//	{
//		int32_t err = addFamilyMember(family, tcid,player->name,FP_MEMBER);
//		if (err != ERR_OK)
//		{
//			return err;
//		}
//
//		//remove all apply messages
//		MutexGuard lock(m_familyInfoLock);
//		for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin(); it != m_fidFamilyInfo.end(); it++)
//		{
//			removeFamilyApplier(&it->second, tcid);
//		}
//	}
//	else
//	{
//		removeFamilyApplier(family, tcid);
//	}
//
//	return ERR_OK;
//}

//bool SocialService::hasFamilyApplier(FamilyInfo* family, int32_t cid)
//{
//	if (NULL == family)
//	{
//		return false;
//	}
//	for (FamilyApplyInfoVector::iterator itv = family->appliers.begin(); itv != family->appliers.end(); itv++ )
//	{
//		if (itv->cid == cid)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}


//int32_t SocialService::appointFamily(int32_t fid, int32_t cid, int32_t tcid, int32_t pos)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* apper = getMemberInfo(family, cid);
//	if (apper == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* appee = getMemberInfo(family, tcid);
//	if (appee == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (pos >= FP_LEADER)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (apper->position < FP_VICE_LEADER)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (apper->position < appee->position)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	CfgFamilyLevel*pFamilyLevel = SOCIAL_SERVICE.getCfgFamilyLevel(family->level);
//	if (pFamilyLevel == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (pos > FP_MEMBER && pos < FP_LEADER)
//	{
//		if (pFamilyLevel->level <= getPositionCount(family, pos)) //pos limit
//		{
//			return ERR_FAMILY_POSITION_LIMIT;
//		}
//	}
//
//	setMemberInfo(family, appee->cid, FMI_POSI, pos);
//
//	PlayerInfo* player = getPlayerInfo(cid);
//	if (player != NULL)
//	{
//		broadcastFamilyAppoint(fid, tcid, pos, player->name, appee->name);
//	}
//
//	return ERR_OK;
//}


//int32_t SocialService::changeNameFamily(int32_t fid, int32_t cid, std::string name)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* apper = getMemberInfo(family, cid);
//	if (apper == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_family` SET `name`='%s' WHERE `id`=%d", name.c_str(), fid);
//
//	int32_t err = db.excute(szSQL);
//	if (err == ERR_ANSWER_OK)
//	{
//		family->name = name;
//
//		for (FamilyMemberInfoVector::iterator it = family->members.begin(); it != family->members.end(); ++it)
//		{
//			SocialPlayer *socialPlayer = getPlayerByCid(it->cid);
//			if (socialPlayer != NULL)
//			{
//				//socialPlayer->sendGameSynFamily();
//			}
//		}
//	}
//
//	return err;
//}

//int32_t SocialService::kickFamily(int32_t fid, int32_t cid, int32_t tcid)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* kicker = getMemberInfo(family, cid);
//	if (kicker == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* kickee = getMemberInfo(family, tcid);
//	if (kickee == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (kicker->position < FP_VICE_LEADER)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (kicker->position <=  kickee->position)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	PlayerInfo* player = getPlayerInfo(cid);
//	PlayerInfo* tplayer = getPlayerInfo(tcid);
//	if (player != NULL && tplayer != NULL)
//	{
//		broadcastFamilyKick(fid, tcid, player->name, tplayer->name);
//	}
//
//	removeMemberInfo(family, tcid, true);
//
//	return ERR_OK;
//}

//int32_t SocialService::breakFamily(int32_t fid, int32_t cid)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* breaker = getMemberInfo(family, cid);
//	if (breaker == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	Int32Vector cids;
//	for (FamilyMemberInfoVector::iterator it = family->members.begin(); it != family->members.end(); it++ )
//	{
//		cids.push_back(it->cid);
//	}
//
//	breakFamily(family);
//	for (Int32Vector::iterator it = cids.begin(); it != cids.end(); it++)
//	{
//		SocialPlayer* targetPlayer = SOCIAL_SERVICE.getPlayerByCid(*it);
//		if(targetPlayer != NULL)
//		{
//			targetPlayer->setFamilyId(0);
//			targetPlayer->setFamilyPos(0);
//
//			targetPlayer->sendGameSynFamily(UFIR_LEAVE);
//			targetPlayer->sendFamilyStateData();
//		}
//	}
//
//	return ERR_OK;
//}
//
//int32_t SocialService::breakFamily(FamilyInfo* family)
//{
//	if (NULL == family)
//	{
//		return ERR_INVALID_DATA;
//	}
//	{
//		MySqlDBGuard db(DBPOOL);
//
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_family` WHERE `id`='%d'", family->fid);
//		db.excute(szSQL);
//	}
//
//	for (FamilyMemberInfoVector::iterator it = family->members.begin(); it != family->members.end(); it++ )
//	{
//		removeMemberInfo(family, it->cid, false);
//	}
//
//	MutexGuard lock(m_familyInfoLock);
//	Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.find(family->fid);
//	if (it != m_fidFamilyInfo.end())
//	{
//		m_fidFamilyInfo.erase(it);
//	}
//
//	return ERR_OK;
//}

//int32_t SocialService::leaveFamily(int32_t fid, int32_t cid)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyMemberInfo* leaver = getMemberInfo(family, cid);
//	if (leaver == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (leaver->position == FP_LEADER || family->count <= 1)
//	{
//			return ERR_INVALID_DATA;
//	}
//	else
//	{
//		PlayerInfo* player = getPlayerInfo(cid);
//		if (player != NULL)
//		{
//			broadcastFamilyLeave(fid, cid, player->name);
//		}
//
//		removeMemberInfo(family, cid, true);
//	}
//
//	return ERR_OK;
//}

//int32_t SocialService::openFamilyMap(int32_t fid, int32_t cid)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//// 
//// 	if (family->has_map != 0 || family->money < 1000)
//// 	{
//// 		return ERR_LACK_OF_FAMILY_MONEY;
//// 	}
//
//	FamilyMemberInfo* member = getMemberInfo(family, cid);
//	if (member == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (member->position < FP_VICE_LEADER)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//
//	return ERR_OK;
//}

//bool SocialService::isStoreItemEmpty(int32_t fid, int32_t slot_id)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return false;
//	}
//
//	Int32FamilyStoreItemMap::iterator it = family->items.find(slot_id);
//	if (it != family->items.end())
//	{
//		return false;
//	}
//
//	return true;
//}

//int32_t SocialService::addStoreItem(int32_t fid, int32_t slot_id, const MemChrBag &bagdata)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	Int32FamilyStoreItemMap::iterator it = family->items.find(slot_id);
//	if (it != family->items.end())
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = "";
//	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_fam_store` (`fid`, `slot`, `id`, `type`, `count`, `degree`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d')",
//		fid, slot_id, bagdata.itemId, bagdata.itemClass, bagdata.itemCount, 0);
//	db.excute(szSQL);
//
//	FamilyStoreItem item ;
//	item.id = bagdata.itemId;
//	item.type = bagdata.itemClass;
//	item.count = bagdata.itemCount;
//	item.slot = slot_id;
//	item.degree = 0;
//	item.expire =0;
//	family->items.insert(Int32FamilyStoreItemMap::value_type(slot_id, item));
//	return ERR_OK;
//}

//int32_t SocialService::removeStoreItem( int32_t fid, int32_t slot_id )
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	Int32FamilyStoreItemMap::iterator it = family->items.find(slot_id);
//	if (it == family->items.end())
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = "";
//	snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_fam_store` WHERE `fid` = '%d' AND `slot` = '%d'", fid, slot_id);
//	db.excute(szSQL);
//
//	family->items.erase(it);
//
//	return ERR_OK;
//}

//MemChrBag SocialService::getStoreItem(int32_t fid, int32_t slot_id)
//{
//	MemChrBag bagItem = {};
//
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return bagItem;
//	}
//
//	Int32FamilyStoreItemMap::iterator it = family->items.find(slot_id);
//	if (it == family->items.end())
//	{
//		return bagItem;
//	}
//
//	bagItem.itemId = it->second.id;
//	bagItem.itemClass = it->second.type;
//	bagItem.itemCount = it->second.count;
//
//	return bagItem;
//}

//int32_t SocialService::reorderStoreItem(int32_t fid, int32_t slot_id, int32_t slot_id2)
//{
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	Int32FamilyStoreItemMap::iterator it = family->items.find(slot_id);
//	if (it == family->items.end())
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	MySqlDBGuard db(DBPOOL);
//
//	Int32FamilyStoreItemMap::iterator it2 = family->items.find(slot_id2);
//	if (it2 != family->items.end()) //exchange
//	{
//		FamilyStoreItem t1 = it2->second;
//		t1.slot = slot_id;
//		FamilyStoreItem t2 = it->second;
//		t2.slot = slot_id2;
//		
//		family->items.erase(it);
//		family->items.erase(it2);
//
//		family->items.insert(Int32FamilyStoreItemMap::value_type(t1.slot, t1));
//		family->items.insert(Int32FamilyStoreItemMap::value_type(t2.slot, t2));
//
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_fam_store` WHERE `fid` = '%d' AND `slot` = '%d'", fid, slot_id);
//		db.excute(szSQL);
//
//		bzero(&szSQL, sizeof(szSQL));
//		snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_fam_store` WHERE `fid` = '%d' AND `slot` = '%d'", fid, slot_id2);
//		db.excute(szSQL);
//
//		bzero(&szSQL, sizeof(szSQL));
//		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_fam_store` (`fid`, `slot`, `id`, `type`, `count`, `expire`, `degree`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%d')",
//			fid, t1.slot, t1.id, t1.type, t1.count, t1.expire, t1.degree);
//		db.excute(szSQL);
//
//		bzero(&szSQL, sizeof(szSQL));
//		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_fam_store` (`fid`, `slot`, `id`, `type`, `count`, `expire`, `degree`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%d')",
//			fid, t2.slot, t2.id, t2.type, t2.count, t2.expire, t2.degree);
//		db.excute(szSQL);
//	}
//	else //move
//	{
//		FamilyStoreItem t1 = it->second;
//		t1.slot = slot_id2;
//
//		family->items.erase(it);
//
//		family->items.insert(Int32FamilyStoreItemMap::value_type(t1.slot, t1));
//
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_fam_store` SET `slot` = '%d' WHERE `fid` = '%d' AND `slot` = '%d'", slot_id2, fid, slot_id);
//		db.excute(szSQL);
//	}
//
//	return ERR_OK;
//}

//int32_t SocialService::addFamilyContribution(int32_t fid, int32_t cid, int32_t addon, int32_t rate){
//	FamilyInfo* family = getFamilyInfo(fid);
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	addMemberInfo(family, cid, FMI_CONTRI, addon);
//	return ERR_OK;
//}
//
//int32_t  SocialService::addSelfFamilyContribute(FamilyInfo*pFamily,int32_t cid,int32_t addon)
//{
//	if (pFamily == NULL)
//	{
//		return 0;
//	}
//
//	for (FamilyMemberInfoVector::iterator it = pFamily->members.begin();it != pFamily->members.end();++it)
//	{
//		if (it->cid == cid)
//		{
//			it->contribute += addon;
//			it->today_contribute += addon;
//			it->week_contribute += addon;
//
//			MySqlDBGuard db(DBPOOL);
//			char szSQL[MAX_SQL_LENGTH] = "";
//			snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET `contribute` = %d,`today_contribute` = %d,`week_contribute` = %d WHERE `cid` = %d",it->contribute,it->today_contribute,it->week_contribute,cid);
//			db.excute(szSQL);
//
//			return it->contribute;
//		}
//	}
//	return 0;
//}

//void SocialService::refeshFamilyDayContribute()
//{
//	for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin();it != m_fidFamilyInfo.end();++it)
//	{
//		for (FamilyMemberInfoVector::iterator iter = it->second.members.begin(); iter != it->second.members.end();++iter)
//		{
//			iter->today_contribute = 0;
//		}
//	}
//
//	MySqlDBGuard db(DBPOOL);
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET `today_contribute` = 0");
//	db.excute(szSQL);
//}

//void SocialService::refeshFamilyWeekContribute()
//{
//	for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin();it != m_fidFamilyInfo.end();++it)
//	{
//		for (FamilyMemberInfoVector::iterator iter = it->second.members.begin(); iter != it->second.members.end();++iter)
//		{
//			iter->week_contribute = 0;
//		}
//	}
//
//	MySqlDBGuard db(DBPOOL);
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET `week_contribute` = 0");
//	db.excute(szSQL);
//}

//void SocialService::sendGambleRecord()
//{
//	NetPacket *packet = popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(m_gambleIndex);
//	int32_t temp =  m_gambleSecondIndex;
//	for (int32_t i = 0; i < m_gambleIndex;++i)
//	{
//		packet->writeInt32(m_gambleRecord[temp].cid);
//		packet->writeUTF8(m_gambleRecord[temp].name);
//		packet->writeInt8(m_gambleRecord[temp].type);
//		packet->writeInt32(m_gambleRecord[temp].item);
//		packet->writeInt32(m_gambleRecord[temp].item_type);
//		packet->writeInt32(m_gambleRecord[temp].count);
//
//		if (temp == MAX_GAMBLE_RECORD-1)
//		{
//			temp = 0;
//		}
//		else
//		{
//			temp++;
//		}
//	}
//
//	packet->setType(PACK_DISPATCH);
//	packet->setProc(SM_GAMBLE_BORADCAST);
//	packet->setSize(packet->getWOffset()); 
//
//	worldBroadcast(packet);
//}

//int32_t SocialService::sendFamilyList(int32_t cgindex, int32_t kingdom,Int32Int32Map &familyApply)
//{
//	NetPacket *familyPacket = popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	MutexGuard lock(m_familyInfoLock);
//
//	int32_t familyCount = 0; 
//	familyPacket->writeInt16(familyCount);
//	for (Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin(); it != m_fidFamilyInfo.end(); it++)
//	{
//		if (it->second.kingdom == kingdom ||kingdom == 0)
//		{
//			familyPacket->writeInt32(it->second.fid);
//			familyPacket->writeInt16(it->second.rank);
//			familyPacket->writeUTF8(it->second.name);
//			familyPacket->writeUTF8(it->second.leader_name);
//			familyPacket->writeInt16(it->second.count);
//			familyPacket->writeInt16(it->second.level);
//			familyPacket->writeInt8(it->second.kingdom);
//			familyPacket->writeInt8(it->second.vip);
//			familyCount++;
//		}
//	}
//
//	int32_t oldOffset = familyPacket->getWOffset();
//	familyPacket->setWOffset(0);
//	familyPacket->writeInt16(familyCount);
//	familyPacket->setWOffset(oldOffset);
//	familyPacket->setSize(oldOffset);
//
//	familyPacket->writeInt16(familyApply.size());
//	for (Int32Int32Map::iterator it = familyApply.begin();it != familyApply.end();++it)
//	{
//		familyPacket->writeInt32(it->first);
//	}
//
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_LIST);
//	familyPacket->setSize(familyPacket->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(cgindex, familyPacket);
//
//	return ERR_OK;
//}
//
//void SocialService::broadcastFamilyApply(int32_t fid, std::string name)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_APPLY);
//	familyPacket->writeUTF8(name);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyApprove(int32_t fid, int32_t cid, std::string name, std::string fname)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_APPROVE);
//	familyPacket->writeInt32(cid);
//	familyPacket->writeUTF8(name);
//	familyPacket->writeUTF8(fname);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyLeave(int32_t fid, int32_t cid, std::string name)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_LEAVE);
//	familyPacket->writeInt32(cid);
//	familyPacket->writeUTF8(name);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyKick(int32_t fid, int32_t cid, std::string name, std::string tname)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_KICK);
//	familyPacket->writeInt32(cid);
//	familyPacket->writeUTF8(name);
//	familyPacket->writeUTF8(tname);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyAppoint(int32_t fid, int32_t cid, int32_t pos, std::string name, std::string tname)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_APPOINT);
//	familyPacket->writeInt32(cid);
//	familyPacket->writeInt32(pos);
//	familyPacket->writeUTF8(name);
//	familyPacket->writeUTF8(tname);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyOpenMap(int32_t fid, std::string name)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_OPEN_MAP);
//	familyPacket->writeUTF8(name);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyDonateCard(int32_t fid, std::string name, int32_t addon)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_DONATE_CARD);
//	familyPacket->writeUTF8(name);
//	familyPacket->writeInt32(addon);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyActivity(int32_t fid)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_ACTIVITY);
//	familyPacket->writeInt32(0);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilyLeaderDown(int32_t fid,int32_t cid,const std::string name,int32_t tcid,const std::string tname)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_LEADER_DOWN);
//	familyPacket->writeInt32(cid);
//	familyPacket->writeUTF8(name);
//	familyPacket->writeInt32(tcid);
//	familyPacket->writeUTF8(tname);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}
//
//void SocialService::broadcastFamilySetRewardRatio(int32_t fid,int32_t index)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(FET_SET_RATIO);
//	familyPacket->writeInt32(index);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_EVENT);
//	familyPacket->setSize(familyPacket->getWOffset());
//	familyBroadcast(fid, 0, familyPacket);
//}

//void SocialService::broadTeamDungeon()
//{ 
//// 	Int32Vector select;
//// 	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//// 	{
//// 		SocialPlayer* pLayer = SOCIAL_SERVICE.getPlayerByCid(it->leader);
//// 		if (pLayer == NULL)
//// 		{
//// 			m_teamDungeon.erase(it);
//// 		}
//// 	}
//// 
//// 	for (Int32Vector::iterator it = select.begin();it != select.end();++it)
//// 	{
//// 		for (TeamDungeonList::iterator iter = m_teamDungeon.begin();iter != m_teamDungeon.end();++iter)
//// 		{
//// 			if (iter->leader == *it)
//// 			{
//// 				m_teamDungeon.erase(iter);
//// 				break;
//// 			}
//// 		}
//// 	}
//
//	Int16Vector indexes;
//
//	{
//		MutexGuard lock(m_playerLock);
//		for (Int32SocialPlayerMap::iterator it1 = m_playerByCid.begin(); it1 != m_playerByCid.end(); ++it1)
//		{
//			NetPacket *packet = popNetpacket();
//			if (NULL == packet)
//			{
//				continue;
//			}
//			packet->writeInt8(m_teamDungeon.size());
//			TeamDungeon teamMember = {};
//			TeamDungeonList listSort;
//			for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//			{
//				bool b = true;
//				for (int32_t i= 0;i < MAX_TEAM_NUM;i++)
//				{
//					if (it->num[i] == it1->second->getCid())//队员或者队长
//					{
//						teamMember = *it;
//						b = false;
//						break;
//					}
//
//				}
//				if (b)
//				{
//					listSort.push_back(*it);
//				}
//
//
//			}
//			//队伍人数满则排在最后一个位置,玩家创建或加入队伍，则置顶为第一个
//			if (teamMember.dungeonID != 0)
//			{
//				packet->writeInt32(teamMember.leader);
//				packet->writeUTF8(teamMember.name);
//				packet->writeInt32(teamMember.dungeonID);
//				packet->writeInt8(teamMember.index);
//				packet->writeInt8(teamMember.line);
//				for (int i = 0;i < MAX_TEAM_NUM ;i++)
//				{
//					if (teamMember.num[i] != 0)
//					{
//						PlayerInfo * pLayer = getPlayerInfo(teamMember.num[i]);
//						if (NULL == pLayer)
//						{
//							continue;
//						}
//						packet->writeInt32(pLayer->cid);
//						packet->writeUTF8(pLayer->name);
//						packet->writeInt32(pLayer->job);
//						packet->writeInt32(pLayer->fightPower);
//						packet->writeInt32(pLayer->level);
//						packet->writeInt32(pLayer->sex);
//					}
//				}
//			}
//
//			listSort.sort();
//
//			for (TeamDungeonList::iterator it = listSort.begin();it != listSort.end();++it)
//			{
//				packet->writeInt32(it->leader);
//				packet->writeUTF8(it->name);
//				packet->writeInt32(it->dungeonID);
//				packet->writeInt8(it->index);
//				packet->writeInt8(it->line);
//				for (int i = 0;i < MAX_TEAM_NUM ;i++)
//				{
//					if (it->num[i] != 0)
//					{
//						PlayerInfo * pLayer = getPlayerInfo(it->num[i]);
//						if (NULL == pLayer)
//						{
//							continue;
//						}
//						packet->writeInt32(pLayer->cid);
//						packet->writeUTF8(pLayer->name);
//						packet->writeInt32(pLayer->job);
//						packet->writeInt32(pLayer->fightPower);
//						packet->writeInt32(pLayer->level);
//						packet->writeInt32(pLayer->sex);
//					}
//				}
//			}
//
//			packet->setType(PACK_DISPATCH);
//			packet->setProc(SM_TEAM_DUNGEON_BORADCAST);
//			packet->setSize(packet->getWOffset());
//			sendPacketTo(it1->second->getGateIndex(),packet);
//		}
//	}
//
//	 
//
//	//broadcast(packet);
//}

//void SocialService::sendTeamDungeonInfo()
//{
//// 	Int32Vector select;
//// 	for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//// 	{
//// 		SocialPlayer* pLayer = SOCIAL_SERVICE.getPlayerByCid(it->leader);
//// 		if (pLayer == NULL)
//// 		{
//// 			m_teamDungeon.erase(it);
//// 		}
//// 	}
//// 
//// 	for (Int32Vector::iterator it = select.begin();it != select.end();++it)
//// 	{
//// 		for (TeamDungeonList::iterator iter = m_teamDungeon.begin();iter != m_teamDungeon.end();++iter)
//// 		{
//// 			if (iter->leader == *it)
//// 			{
//// 				m_teamDungeon.erase(iter);
//// 				break;
//// 			}
//// 		}
//// 	}
//	Int16Vector indexes;
//
//	{
//		MutexGuard lock(m_playerLock);
//		for (Int32SocialPlayerMap::iterator it1 = m_playerByCid.begin(); it1 != m_playerByCid.end(); ++it1)
//		{
//			NetPacket *packet = popNetpacket();
//			if (NULL == packet)
//			{
//				continue;
//			}
//			packet->writeInt8(m_teamDungeon.size());
//			TeamDungeon teamMember = {};
//			TeamDungeonList listSort;
//			for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//			{
//				bool b = true;
//				for (int32_t i= 0;i < MAX_TEAM_NUM;i++)
//				{
//					if (it->num[i] == it1->second->getCid())//队员或者队长
//					{
//						teamMember = *it;
//						b = false;
//						break;
//					}
//			
//				}
//				if (b)
//				{
//					listSort.push_back(*it);
//				}
//		
//		
//			}
//			//队伍人数满则排在最后一个位置,玩家创建或加入队伍，则置顶为第一个
//			if (teamMember.dungeonID != 0)
//			{
//				packet->writeInt32(teamMember.leader);
//				packet->writeUTF8(teamMember.name);
//				packet->writeInt32(teamMember.dungeonID);
//				packet->writeInt8(teamMember.index);
//				packet->writeInt8(teamMember.line);
//				for (int i = 0;i < MAX_TEAM_NUM ;i++)
//				{
//					if (teamMember.num[i] != 0)
//					{
//						PlayerInfo * pLayer = getPlayerInfo(teamMember.num[i]);
//						if (NULL == pLayer)
//						{
//							continue;
//						}
//						packet->writeInt32(pLayer->cid);
//						packet->writeUTF8(pLayer->name);
//						packet->writeInt32(pLayer->job);
//						packet->writeInt32(pLayer->fightPower);
//						packet->writeInt32(pLayer->level);
//						packet->writeInt32(pLayer->sex);
//					}
//				}
//			}
//
//			listSort.sort();
//
//			for (TeamDungeonList::iterator it = listSort.begin();it != listSort.end();++it)
//			{
//				packet->writeInt32(it->leader);
//				packet->writeUTF8(it->name);
//				packet->writeInt32(it->dungeonID);
//				packet->writeInt8(it->index);
//				packet->writeInt8(it->line);
//
//				for (int i = 0;i < MAX_TEAM_NUM ;i++)
//				{
//					if (it->num[i] != 0)
//					{
//						PlayerInfo * pLayer = getPlayerInfo(it->num[i]);
//						if (NULL == pLayer)
//						{
//							continue;
//						}
//						packet->writeInt32(pLayer->cid);
//						packet->writeUTF8(pLayer->name);
//						packet->writeInt32(pLayer->job);
//						packet->writeInt32(pLayer->fightPower);
//						packet->writeInt32(pLayer->level);
//						packet->writeInt32(pLayer->sex);
//					}
//				}
//		
//		
//		
//			}
//	
//		// 	else
//		// 	{
//		// 		for (TeamDungeonList::iterator it = m_teamDungeon.begin();it != m_teamDungeon.end();++it)
//		// 		{
//		// 			packet->writeInt32(it->leader);
//		// 			packet->writeUTF8(it->name);
//		// 			packet->writeInt32(it->dungeonID);
//		// 			packet->writeInt8(it->index);
//		// 			packet->writeInt8(it->line);
//		// 		}
//		// 
//		// 	}
//		// 	
//			packet->setType(PACK_DISPATCH);
//			packet->setProc(SM_TEAM_DUNGEON_INFO);
//			packet->setSize(packet->getWOffset()); 
//			sendPacketTo(it1->second->getGateIndex(),packet);
//			
//		}
//	}
//		//	broadcast(packet);
//}

bool SocialService::isBanChat(int32_t uid)
{
	GmtBanChatTable::iterator it = m_banChats.find(uid);
	if (it != m_banChats.end())
	{
		return it->second.expire_time == 0 || it->second.expire_time > DayTime::now();
	}

	return false;
}

//void SocialService::initRealTimeRank()
//{
//	MySqlDBGuard db(DBPOOL);
//	//{
//	//	char szSQL[MAX_SQL_LENGTH] = {};
//	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT cid, name, level, exp FROM mem_character WHERE level > 0 ORDER BY level DESC, exp DESC LIMIT %d", N_ITEM_IN_REAL_TIME_RANK);
//	//	MySqlQuery resultm = db.query(szSQL);
//
//	//	while (!resultm.eof())
//	//	{
//	//		RankItem item;
//	//		item.cid = resultm.getIntValue("cid");
//	//		item.name = resultm.getStringValue("name");
//	//		item.value = resultm.getIntValue("level");
//	//		item.addix = resultm.getIntValue("exp");
//	//		m_realTimeRankLevel.push_back(item);
//
//	//		resultm.nextRow();
//	//	}
//	//}
//
//	//{
//	//	char szSQL[MAX_SQL_LENGTH] = {};
//	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT cid, name, fight_power FROM mem_character WHERE fight_power > 0 ORDER BY fight_power DESC LIMIT %d", N_ITEM_IN_REAL_TIME_RANK);
//	//	MySqlQuery resultm = db.query(szSQL);
//
//	//	while (!resultm.eof())
//	//	{
//	//		RankItem item;
//	//		item.cid = resultm.getIntValue("cid");
//	//		item.name = resultm.getStringValue("name");
//	//		item.value = resultm.getIntValue("fight_power");
//	//		m_realTimeRankFightPower.push_back(item);
//	//		resultm.nextRow();
//	//	}
//	//}
//
//	sendGameRealTimeRankBase();
//}

void SocialService::initFamily()
{
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query("SELECT * FROM `mem_family`");
	while (!result.eof())
	{
		//FamilyInfo familyInfo = {};
		//familyInfo.fid = result.getIntValue("id");
		//familyInfo.name = result.getStringValue("name");
		//familyInfo.leader_cid = result.getIntValue("leader_cid");
		//familyInfo.kingdom = result.getIntValue("kingdom");
		//familyInfo.rank = 0;
		//familyInfo.contribute = result.getIntValue("contribute");
		//familyInfo.money = result.getIntValue("money");
		//familyInfo.level = result.getIntValue("level");
		//familyInfo.notice = result.getStringValue("notice");

		//char szSQL[MAX_SQL_LENGTH] = {};
		//snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid,b.uid,a.position,a.contribute,a.today_contribute,a.week_contribute,b.name, b.vip FROM `mem_chr_family` As a LEFT JOIN `mem_character` As b ON a.cid = b.cid  WHERE `family_id`='%d'", familyInfo.fid);
		//MySqlQuery result_chr = db.query(szSQL);
		//FamilyMemberInfoVector members;
		//while (!result_chr.eof())
		//{
		//	FamilyMemberInfo member = {};
		//	member.cid = result_chr.getIntValue("cid");
		//	member.position = result_chr.getIntValue("position");
		//	member.contribute = result_chr.getIntValue("contribute");
		//	member.today_contribute = result_chr.getIntValue("today_contribute");
		//	member.week_contribute = result_chr.getIntValue("week_contribute");
		//	snprintf(member.name,MAX_NAME_CCH_LENGTH-1,result_chr.getStringValue("name"));

		//	if(member.position == FP_LEADER)
		//	{
		//		familyInfo.leader_cid = member.cid;
		//		familyInfo.leader_name = member.name;
		//		familyInfo.vip = static_cast<VipType>(result_chr.getIntValue("vip"));
		//	}

		//	members.push_back(member);
		//	++(familyInfo.count);

		//	result_chr.nextRow();
		//}

		//familyInfo.members = members;
		//m_fidFamilyInfo[familyInfo.fid] = familyInfo;

		result.nextRow();
	}
}
//
//void SocialService::getFamilyList(FamilyRankVector* plist,KDMSRVECTOR* pResult)
//{
//	if(plist ==NULL) return;
//	if(pResult ==NULL)return;
//
//	MutexGuard lock(m_familyInfoLock);
//	Int32FamilyInfoMap::iterator it = m_fidFamilyInfo.begin();
//	for (;it!=m_fidFamilyInfo.end();it++)
//	{
//		int32_t fid=(*it).first;
//		int32_t nKiller=0;
//		KDMSRVECTOR::iterator item=pResult->begin();
//		for(;item!=pResult->end();item++)
//		{
//			int32_t cid=(*item).cid;
//			int32_t nFid=getPlayerByCid(cid)->getFamilyId();
//			if(fid ==nFid && nFid!=0)
//			{
//				nKiller=nKiller+(*item).killerNum;
//			}
//		}
//		famliyRank fRank;
//		fRank.cid =(*it).second.leader_cid;
//		fRank.killer =nKiller;
//		fRank.kingDomId=(*it).second.kingdom;
//		plist->push_back(fRank);
//	}
//}

void SocialService::fetchBanChat()
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

void SocialService::InitShangChengTable()
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
	m_ShopCfg.clear();
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
		if ( ShangCheng.LimitType == LIMIT_TYPE_SERVER )
		{
			m_ShopCfg[ShangCheng.ShopId] = ShangCheng;
		}
	}

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query("SELECT * FROM `mem_limit_shop`");

	int32_t RefreshTime = 0;
	while(!result.eof())
	{
		int32_t ShopId = result.getIntValue("ShopId");
		m_ItemLimitMap[ShopId] = result.getIntValue("LimitCount");
		RefreshTime = result.getIntValue("RefreshTime");
		result.nextRow();
	}

	if ( (DayTime::daydiff(RefreshTime) >= 1 && time > 0))
	{
		RefreshLimitInfo();
	}
}

CfgGameShop* SocialService::GetCfgGameShop( int32_t ShopId )
{
	GameShopMap::iterator it = m_ShopCfg.find( ShopId );
	if ( it != m_ShopCfg.end() )
	{
		return &(it->second);
	}
	return NULL;
}

void SocialService::fetchNewServerActivity()
{
 	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query("SELECT `value` FROM `sys_server_config` WHERE `name`='startGame_time'");
	if (!result.eof())
	{
		m_newServerTime = atoi(result.getStringValue(0));
		if (!m_newServerTime)
		{
			m_newServerTime = Answer::DayTime::now();
		}
	}
	else
	{
		m_newServerTime = Answer::DayTime::now();
	}
}

MemChrBagVector SocialService::parseItemString(int32_t id, const std::string &strItems)
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
				itemData.itemId = atoi(item[0].c_str());
				itemData.itemClass = atoi(item[1].c_str());
				itemData.itemCount = atoi(item[2].c_str());
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
void SocialService::parseItemString(MemChrBagVector & items,const std::string &strItems)
{
	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 3 && atoi(item[0].c_str())>0)
			{
				MemChrBag itemData = {};
				itemData.itemId = atoi(item[0].c_str());
				itemData.itemClass = atoi(item[1].c_str());
				itemData.itemCount = atoi(item[2].c_str());
				items.push_back(itemData);
			}
		}
	}
}

void SocialService::fetchCreateTime()
{
	MySqlDBGuard db(DBPOOL);

	MySqlQuery result = db.query("SELECT `value`,`refresh_time` FROM `sys_server_config` WHERE `name` = 'startGame_time'");
	if (!result.eof())
	{
		m_createTime = atoi(result.getStringValue("value"));
	}
}

int32_t SocialService::getCreateTime()
{
	return m_createTime;
}

//SocialPlayer* SocialService::getPlayerByCid(int32_t cid)
//{
//	Int32SocialPlayerMap::iterator it = m_playerByCid.find(cid);
//	if (it != m_playerByCid.end())
//	{
//		return it->second;
//	}
//	else
//	{
//		return NULL;
//	}
//}

//SocialPlayer* SocialService::getPlayerByGateIndex(int32_t cgindex)
//{
//	Int32SocialPlayerMap::iterator it = m_playerByGateIndex.find(cgindex);
//	if (it != m_playerByGateIndex.end())
//	{
//		return it->second;
//	}
//	else
//	{
//		return NULL;
//	}
//}

void SocialService::onUpdateBanChat(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	int32_t action = inPacket->readInt32();
	GmtBanChat banChat = {};
	banChat.uid = inPacket->readInt32();
	banChat.expire_time = inPacket->readInt32();

	if (action)
	{
		m_banChats[banChat.uid] = banChat;
	}
	else
	{
		m_banChats.erase(banChat.uid);
	}
}

//void SocialService::onAddPlayerInfo(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return;
//	}
//	int32_t cid = inPacket->readInt32();
//	string name = inPacket->readUTF8(true);
//	Sex_t sex = inPacket->readInt8();
//	Job_t job = inPacket->readInt8();
//	int32_t kingdom = inPacket->readInt32();
//	int32_t level = inPacket->readInt32();
//	VipType vip = static_cast<VipType>(inPacket->readInt32());
//	int32_t family_id = inPacket->readInt32();
//	int32_t kingdom_contribute = inPacket->readInt32();
//	int32_t family_contribute = inPacket->readInt32();
//	int32_t nBattle = inPacket->readInt32();
//	bool bLearnedXP = inPacket->readInt8() > 0;
//
//	Int32PlayerInfoMap::iterator it = m_cidPlayerInfo.find(cid);
//	if (it == m_cidPlayerInfo.end())
//	{
//		PlayerInfo *playerInfo = new PlayerInfo;
//		if (NULL == playerInfo)
//		{
//			return;
//		}
//		playerInfo->nCharId = cid;
//		playerInfo->strName = name;
//		playerInfo->nSex = sex;
//		playerInfo->nJob = job;
//		playerInfo->nLevel = level;
//		playerInfo->nLastLogoutTime = 0; //login, set to 0...
//		playerInfo->nVip = vip;
//		playerInfo->nFamilyId = family_id;
//		playerInfo->nFamilyContribute = family_contribute;
//		playerInfo->nBattle = nBattle;
//		playerInfo->bLearnedXP = bLearnedXP;
//
//		m_cidPlayerInfo[playerInfo->nCharId] = playerInfo;
//		m_namePlayerInfo[playerInfo->strName] = playerInfo;
//	}
//	else
//	{
//		it->second->nJob = job;
//		it->second->nLevel = level;
//		it->second->nLastLogoutTime = 0;
//		it->second->nVip = vip;
//		it->second->nFamilyContribute = family_contribute;
//		it->second->bLearnedXP =  bLearnedXP;
//		it->second->nSex = sex;
//		it->second->nBattle = nBattle
//		it->second->nFamilyId = family_id;
//	}
//}

void SocialService::onUpdatePlayerInfo(Answer::NetPacket *inPacket)
{
	PLAYER_MANAGER.UpdatePlayer( inPacket );
}

//void SocialService::onRemovePlayerInfo(int32_t cid)
//{
//	Int32PlayerInfoMap::iterator it = m_cidPlayerInfo.find(cid);
//	if (it != m_cidPlayerInfo.end())
//	{
//		m_cidPlayerInfo.erase(it);
//	}
//}


//void SocialService::onUpdateGambleRecord(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return;
//	}
//	int32_t count = inPacket->readInt32();
//
//	for (int32_t i = 0; i < count;++i)
//	{
//		GambleRecord record = {};
//		record.cid = inPacket->readInt32();
//		snprintf(record.name,sizeof(record.name)-1,inPacket->readUTF8(true).c_str());
//		record.type = inPacket->readInt32();
//		record.item = inPacket->readInt32();
//		record.item_type = inPacket->readInt32();
//		record.count = inPacket->readInt32();
//
//
//		if (m_gambleIndex == MAX_GAMBLE_RECORD)
//		{
//		     m_gambleRecord[m_gambleSecondIndex] = record;
//			 if (m_gambleSecondIndex == MAX_GAMBLE_RECORD -1)
//			 {
//				 m_gambleSecondIndex = 0;
//			 }
//			 else
//			 {
//				 m_gambleSecondIndex++;
//			 }
//		}
//		else
//		{
//			 m_gambleRecord[m_gambleIndex] = record;
//			 m_gambleIndex++;
//		}
//	}
//
//	sendGambleRecord();
//	
//}

void SocialService::onAddPlayer(Answer::NetPacket *inPacket)
{
	PLAYER_MANAGER.AddPlayer( inPacket );
}
//
//void SocialService::onFamilyActivityPlayer(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return;
//	}
//	int32_t familyID = inPacket->readInt32();
//	int32_t rewardCount = inPacket->readInt16();
//	if (rewardCount != 6)
//	{
//		return;
//	}
//
//	int32_t rewards[6] = {};
//	for (int32_t i = 0; i < rewardCount; ++i)
//	{
//		rewards[i] = inPacket->readInt32();
//	}
//
//	int32_t count = inPacket->readInt16();
//	for (int32_t i = 0; i < count;++i)
//	{
//		int32_t cid = inPacket->readInt32();
//		std::string name = inPacket->readUTF8(true);
//
//		if (cid <= 0)
//		{
//			LOG_ERROR("onFamilyActivityPlayer wrong data with cid = %d,family_id = %d,name = %s\n", cid,familyID,name.c_str());
//		}
//		// 这里本来是系统邮件
//	}
//}
//
//void SocialService::onWorldBossActivityResult(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return;
//	}
//	int32_t isWin = inPacket->readInt32();
//	int32_t rewardCount = inPacket->readInt32();
//	Int32Vector rewards;
//	while (rewardCount-- > 0)
//	{
//		rewards.push_back(inPacket->readInt32());
//	}
//	int32_t playerCount = inPacket->readInt32();
//	while (playerCount-- > 0)
//	{
//		int32_t rank = inPacket->readInt32();
//		int32_t cid = inPacket->readInt32();
//		string name = inPacket->readUTF8(true);
//		//这里本来是系统邮件
//	}
//}

void SocialService::onRemovePlayer(Answer::NetPacket *inPacket)
{
	PLAYER_MANAGER.DelPlayer( inPacket );
}

void SocialService::onNewMinuteCome(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	int32_t minute = inPacket->readInt32();
	int32_t nNowTime = DayTime::now();

	if (minute)
	{
		//m_lastRankTime = 30 - minute%30;
		//m_secondRecord = DayTime::now();
		//if (minute%30 == 0)
		//{
		//	refreshRanks(true);	
		//}

		////敌国攻城活动结束刷新LOG数据
		//if (minute == 15*60+35)
		//{
		//	refreshActivityRankData();
		//}

		//if (minute == 18*60)
		//{
		//	refreshActivityRankData();
		//}

		////武神大赛活动结束刷新LOG数据
		//if (minute == 19*60+53)
		//{
		//	refreshActivityRankData();
		//}

		////楚汉争霸、国家战场、国君继位战活动结束刷新LOG数据
		//if (minute == 20*60+35)
		//{
		//	refreshActivityRankData();
		//}

		//if (DayTime::now() - m_newServerTime < 7 * 24 * 60 * 60)
		//{
		//	if (minute == 20 * 60 + 40)
		//	{
		//		sendRealTimeRankTime(RTRT_LEVEL);
		//	}
		//	else if (minute == 21 * 60)
		//	{
		//		genRealTimeRankResult(RTRT_LEVEL);
		//	}
		//	else if (minute == 21 * 60 + 10)
		//	{
		//		sendRealTimeRankTime(RTRT_FIGHT_POWER);
		//	}
		//	else if (minute == 21 * 60 + 30)
		//	{
		//		genRealTimeRankResult(RTRT_FIGHT_POWER);
		//	}
		//}

//		if (minute == 23*60 && (Answer::DayTime::daydiff(m_newServerTime) == 6 || Answer::DayTime::daydiff(m_newServerTime) == 14))
//		{
//			sendNewServerActivityReward();
//		}
	}

	if (minute == 0)//new day come
	{
		RefreshLimitInfo();
		FAMILY_MANAGER.ResetFamilyCount();
	}
	checkGMAnnouncement();

	FAMILY_MANAGER.CheckFamilyTotom( nNowTime );
	RANK_MANAGER.NewMinuteCome( minute, nNowTime );
	HALL_OF_FAME.OnNewMinuteCome( minute );
}

void SocialService::onActivityClear(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	int8_t ntype =inPacket->readInt8();
	int32_t nactid =inPacket->readInt32();
	int8_t kingdom=inPacket->readInt8();
	int8_t actTypeid=inPacket->readInt8();

	if(ntype == 1) //结果
	{
		//这里原来是发邮件的
	}
}

//
//void SocialService::familyBroadcast(int32_t family, int32_t level, Answer::NetPacket *inPacket)
//{
//	if (inPacket == NULL)
//	{
//		return;
//	}
//
//	if (family == 0)
//	{
//		inPacket->destroy();
//		return;
//	}
//
//	Int16Vector indexes;
//	for (Int32SocialPlayerMap::iterator it = m_playerByCid.begin(); it != m_playerByCid.end(); ++it)
//	{
//		if (it->second->GetFamilyId() == family && it->second->getLevel() >= level)
//		{
//			indexes.push_back(it->second->getGateIndex());
//		}
//	}
//	broadcast(indexes, inPacket);
//}

//void SocialService::familyExcludeBroadcast(int32_t family, int32_t level, Answer::NetPacket *inPacket)
//{
//	if (inPacket == NULL)
//	{
//		return;
//	}
//
//	Int16Vector indexes;
//	for (Int32SocialPlayerMap::iterator it = m_playerByCid.begin(); it != m_playerByCid.end(); ++it)
//	{
//		if (it->second->GetFamilyId() != 0 && it->second->GetFamilyId() != family && it->second->getLevel() >= level)
//		{
//			indexes.push_back(it->second->getGateIndex());
//		}
//	}
//
//	broadcast(indexes, inPacket);
//}

void SocialService::refreshRanks(bool sendTitle)
{
	//m_rankLevel.clear();
	//m_rankWealth.clear();
	//m_rankFightPower.clear();
	//m_rankLackeyLevel.clear();
	//m_rankEnhanceLevel.clear();
	//m_rankTotalFight.clear();
	//m_rankVicegeneralFight.clear();

	//MySqlDBGuard db(DBPOOL);
	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid, a.name, a.level, a.sex, a.job, a.kingdom,ifnull(c.name,''),d.uid FROM mem_character AS a LEFT JOIN mem_chr_family AS b ON a.cid = b.cid LEFT JOIN mem_family AS c ON c.id = b.family_id  LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY a.level DESC , a.exp DESC LIMIT 200");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.job = resultm.getIntValue("job");
	//			item.kingdom = resultm.getIntValue("kingdom");
	//			item.sex = resultm.getIntValue("sex");
	//			item.addstr = resultm.getStringValue(6,"name");
	//			item.value = resultm.getIntValue("level");
	//			m_rankLevel.push_back(item);
	//		}

	//		resultm.nextRow();
	//	}
	//}

	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid, a.name, a.money, a.level, a.job, a.kingdom,ifnull(c.name,''),d.uid FROM mem_character AS a LEFT JOIN mem_chr_family AS b ON a.cid = b.cid LEFT JOIN mem_family AS c ON c.id = b.family_id  LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY a.money DESC  LIMIT 200");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.job = resultm.getIntValue("job");
	//			item.kingdom = resultm.getIntValue("kingdom");
	//			item.sex = resultm.getIntValue("level");
	//			item.addstr = resultm.getStringValue(6,"name");
	//			item.value = resultm.getIntValue("money");
	//			m_rankWealth.push_back(item);
	//		}
	//		resultm.nextRow();
	//	}
	//}


	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid, a.name, a.fight_power, a.level, a.job, a.kingdom, ifnull( c.name, '' ),d.uid FROM mem_character AS a LEFT JOIN mem_chr_family AS b ON a.cid = b.cid LEFT JOIN mem_family AS c ON c.id = b.family_id  LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY a.fight_power DESC LIMIT 200");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.job = resultm.getIntValue("job");
	//			item.kingdom = resultm.getIntValue("kingdom");
	//			item.sex = resultm.getIntValue("level");
	//			item.addstr = resultm.getStringValue(6,"name");
	//			item.value = resultm.getIntValue("fight_power");
	//			m_rankFightPower.push_back(item);
	//		}
	//		resultm.nextRow();
	//	}
	//}

	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid, a.name, a.level,a.kingdom,a.job,ifnull(b.level,0),d.uid FROM mem_character AS a LEFT JOIN mem_chr_lackey AS b ON a.cid = b.cid LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY b.level DESC LIMIT 200");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.addix = resultm.getIntValue("level",1);
	//			item.job  = resultm.getIntValue("job");
	//			item.kingdom = resultm.getIntValue("kingdom");
	//			item.value = resultm.getIntValue("ifnull(b.level,0)",2);

	//			m_rankLackeyLevel.push_back(item);
	//		}
	//		resultm.nextRow();
	//	}
	//}

	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid, a.name, a.level, a.job, a.kingdom, a.enhance_total_level,d.uid FROM mem_character AS a  LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY a.enhance_total_level DESC LIMIT 200");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.addix = resultm.getIntValue("level");
	//			item.job  = resultm.getIntValue("job");
	//			item.kingdom = resultm.getIntValue("kingdom");
	//			item.value = resultm.getIntValue("enhance_total_level");

	//			m_rankEnhanceLevel.push_back(item);
	//		}
	//		resultm.nextRow();
	//	}
	//}

	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid,IFNULL(a.name,''),a.kingdom, b.fight, b.fight_power,b.base_id,b.level,d.uid FROM mem_character AS a RIGHT JOIN `mem_chr_vice_general` AS b ON a.cid = b.cid LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY b.fight_power DESC LIMIT 300");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.sex = resultm.getIntValue("level");
	//			item.addix = resultm.getIntValue("base_id");
	//			item.kingdom = resultm.getIntValue("kingdom");
	//			item.value = resultm.getIntValue("fight_power");

	//			int32_t ViceGeneralFight = resultm.getIntValue("fight");

	//			if (ViceGeneralFight == 1)
	//			{
	//				m_rankVicegeneralFight.push_back(item);
	//			}
	//			else
	//			{
	//				rid--;
	//			}
	//		}
	//		resultm.nextRow();
	//	}
	//}

	//{
	//	char szSQL[MAX_SQL_LENGTH] = {};
	//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid,IFNULL(a.name,''), a.level, a.job, b.battle,d.uid FROM mem_character AS a LEFT JOIN `mem_chr_attr` AS b ON a.cid = b.cid LEFT JOIN `gmt_ban_login` AS d ON a.uid = d.uid ORDER BY b.battle DESC LIMIT 200");
	//	MySqlQuery resultm = db.query(szSQL);

	//	int32_t rid = 0;
	//	while (!resultm.eof())
	//	{
	//		int32_t uid = resultm.getIntValue("uid");
	//		if (uid <= 0)
	//		{
	//			RankItem item;
	//			item.rankid = ++rid;
	//			item.cid = resultm.getIntValue("cid");
	//			item.name = resultm.getStringValue(1,"name");
	//			item.addix = resultm.getIntValue("level");
	//			item.job  = resultm.getIntValue("job");
	//			//item.kingdom = resultm.getIntValue("kingdom");
	//			item.value = resultm.getIntValue("battle");

	//			m_rankTotalFight.push_back(item);
	//		}
	//		resultm.nextRow();
	//	}
	//}
}

void SocialService::worldBroadcast(Answer::NetPacket *inPacket)
{
	if (inPacket == NULL)
	{
		return;
	}

	uint32_t oldSize = inPacket->getSize();
	uint32_t addonSize = sizeof(int16_t);

	if (inPacket->rightShift(addonSize))
	{
		inPacket->writeInt16(-1);
		inPacket->setSize(oldSize+addonSize);
		sendPacket(inPacket);
	}
	else
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(-1);
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setType(inPacket->getType());
		packet->setProc(inPacket->getProc());
		packet->setSize(sizeof(int16_t)+inPacket->getSize());
		packet->setSize(packet->getWOffset());
		sendPacket(packet);
		inPacket->destroy();
	}
}

void SocialService::broadcast( const Int16Vector& indexes, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	if (indexes.empty())
	{
		inPacket->destroy();
		return;
	}

	uint32_t oldSize = inPacket->getSize();
	uint32_t addonSize = (indexes.size()+1)*(sizeof(int16_t));

	if (inPacket->rightShift(addonSize))
	{
		inPacket->writeInt16(static_cast<int16_t>(indexes.size()));
		for ( Int16Vector::const_iterator it = indexes.begin(); it != indexes.end(); ++it )
		{
			inPacket->writeInt16(*it);
		}
		inPacket->setSize(oldSize+addonSize);
		SOCIAL_SERVICE.sendPacket(inPacket);
	}
	else
	{
		NetPacket *packet = SOCIAL_SERVICE.popNetpacket((indexes.size()+1)*sizeof(int16_t) + inPacket->getSize());
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(static_cast<int16_t>(indexes.size()));
		for ( Int16Vector::const_iterator it = indexes.begin(); it != indexes.end(); ++it )
		{
			packet->writeInt16(*it);
		}
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setType(inPacket->getType());
		packet->setProc(inPacket->getProc());
		packet->setSize(packet->getWOffset());
		SOCIAL_SERVICE.sendPacket(packet);
		inPacket->destroy();
	}
}

void SocialService::onGMReloadInfo(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	inPacket->readInt32();
	int32_t type = inPacket->readInt32();
	if (type == 1)
	{
		//fetchGameShopLimit();
	}
	else if (type == 2)
	{
		fetchGMAnnouncement();
	}
	else if (type == 3)
	{
		//fetchGameShopLimitSevenDay();
	}
}
void SocialService::fetchGMAnnouncement()
{
	MySqlDBGuard db(DBPOOL);

	Int32Int32Map lastacttimes;
	for (GmtAnnouncementTable::iterator it = m_gmAnnouncements.begin(); it != m_gmAnnouncements.end(); it++)
	{
		lastacttimes[it->second.id] = it->second.last_action_time;
	}

	m_gmAnnouncements.clear();
	MySqlQuery result = db.query("SELECT * FROM `gmt_announcement`");
	while (!result.eof())
	{
		GmtAnnouncement announcement = {};
		announcement.id = result.getIntValue("id");
		announcement.type = result.getIntValue("type");
		snprintf(announcement.content, MAX_GM_ANNOUNCEMENT, result.getStringValue("content"));
		announcement.begin_time = result.getIntValue("begin_time");
		announcement.end_time = result.getIntValue("end_time");
		announcement.interval = result.getIntValue("interval");
		announcement.enable = result.getIntValue("enable");
		Int32Int32Map::iterator it = lastacttimes.find(announcement.id);
		if (it != lastacttimes.end())
		{
			announcement.last_action_time = it->second;
		}

		m_gmAnnouncements[announcement.id] = announcement;

		result.nextRow();
	}
}
void SocialService::checkGMAnnouncement()
{
	int32_t nowTime = DayTime::now();

	for (GmtAnnouncementTable::iterator it = m_gmAnnouncements.begin(); it != m_gmAnnouncements.end(); ++it)
	{
		if (it->second.enable && nowTime >= it->second.begin_time && nowTime <= it->second.end_time)
		{
			if (nowTime - it->second.last_action_time >= it->second.interval*60)//minute to second
			{
				const GmtAnnouncement &announcement = it->second;

				NetPacket *packet = popNetpacket();
				if (NULL == packet)
				{
					continue;
				}
				packet->writeInt32(announcement.type);
				packet->writeUTF8(announcement.content);
				packet->setType(PACK_DISPATCH);
				packet->setProc(SM_GM_ANNOUNCEMENT);
				packet->setSize(packet->getWOffset()); 


				worldBroadcast(packet);

				it->second.last_action_time = nowTime;
			}
		}
	}
}

//AttrAddonInfoVector SocialService::parseEffect(int32_t id, const std::string &str)
//{
//	AttrAddonInfoVector attrAddons;
//
//	if (!str.empty())
//	{
//		StringVector strAttrAddons = StringUtility::split(str, "|");
//		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
//		{
//			StringVector strAttrAddon = StringUtility::split(*it, ":");
//			if (strAttrAddon.size() == 2)
//			{
//				AttrAddonInfo attrAddon = {};
//				attrAddon.index = atoi(strAttrAddon[0].c_str());
//				attrAddon.addon = atoi(strAttrAddon[1].c_str());
//				if (attrAddon.index > 0 && attrAddon.addon > 0)
//				{
//					attrAddons.push_back(attrAddon);
//				}
//			}
//			else
//			{
//				LOG_ERROR("CfgData::parseEffect wrong data with id = %d, str = %s\n", id, str.c_str());
//			}
//		}
//	}
//
//	return attrAddons;
//}
//
//AttrAddonInfoVector SocialService::parseEquipEffect(int32_t id, const std::string &str)
//{
//	AttrAddonInfoVector attrAddons;
//
//	if (!str.empty() && str!="0")
//	{
//		StringVector strAttrAddons = StringUtility::split(str, "|");
//		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
//		{
//			StringVector strAttrAddon = StringUtility::split(*it, ":");
//			if (strAttrAddon.size() == 2)
//			{
//				AttrAddonInfo attrAddon = {};
//				attrAddon.index = atoi(strAttrAddon[0].c_str());
//				attrAddon.addon = atoi(strAttrAddon[1].c_str());
//				if (attrAddon.index > 0 && attrAddon.addon > 0)
//				{
//					attrAddons.push_back(attrAddon);
//				}
//			}
//			else
//			{
//				LOG_ERROR("CfgData::parseEquipEffect wrong data with id = %d, str = %s\n", id, str.c_str());
//			}
//		}
//	}
//
//	return attrAddons;
//}

//ChangeJobIndexVector SocialService::parseChangeJobEffect(int32_t id, const std::string &str)
//{
//	ChangeJobIndexVector equipVector;
//
//	if (!str.empty() && str!="0")
//	{
//		StringVector strAttrAddons = StringUtility::split(str, "|");
//		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
//		{
//			StringVector strAttrAddon = StringUtility::split(*it, ":");
//			if (strAttrAddon.size() == 2)
//			{
//				ChangeJobIndex attrAddon = {};
//				attrAddon.job = atoi(strAttrAddon[0].c_str());
//				attrAddon.replace_id = atoi(strAttrAddon[1].c_str());
//				if (attrAddon.job > 0 && attrAddon.replace_id > 0)
//				{
//					equipVector.push_back(attrAddon);
//				}
//			}
//			else
//			{
//				LOG_ERROR("CfgData::parseChangeJobEquipEffect wrong data with id = %d, str = %s\n", id, str.c_str());
//			}
//		}
//	}
//
//	return equipVector;
//}

//void SocialService::GetPlayerVector(SocialPlayer* pPlayer, std::list<FriendInfo>& FriendList, int32_t MinLeve, int32_t MaxLevel )
//{
//	if ( NULL == pPlayer )
//	{
//		return;
//	}
//	int32_t nSize = 0;
//	if ( MinLeve <= 0 )
//	{
//		MinLeve = 1;
//	}
//	if ( MaxLevel <= 0 )
//	{
//		return;
//	}
//
//	for (Int32SocialPlayerMap::iterator it = m_playerByCid.begin(); it != m_playerByCid.end(); ++it)
//	{
//		if ( it->second->getLevel() >= MinLeve && it->second->getLevel() <= MaxLevel )
//		{
//			FriendInfo Friend = {};
//			Friend.Cid		= it->second->getCid();
//			Friend.Job		= it->second->getJob();
//			Friend.Level	= it->second->getLevel();
//			Friend.Name		= it->second->getName();
//			Friend.Sex		= it->second->getSex();
//			if ( pPlayer->getCid() == Friend.Cid || 
//				 pPlayer->GetFrined().IsInFriendList( Friend.Cid ) || 
//				 pPlayer->GetFrined().IsInEnemy( Friend.Cid, RLT_BLACKLIST ) ||
//				 pPlayer->GetFrined().IsInEnemy( Friend.Cid, RLT_IN_BLACKLIST ) )
//			{
//				continue;
//			}
//			FriendList.push_back( Friend );
//			++nSize;
//			if ( nSize >= 8 )
//			{
//				break;
//			}
//		}
//	}
//}

void SocialService::onUpdatePetData(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}

	SocialPetData petData = {};
	petData.nPetId		= inPacket->readInt64();
	petData.nBaseId		= inPacket->readInt32();
	petData.nOwner		= inPacket->readInt64();
	petData.nPoints		= inPacket->readInt32();
	petData.nRankFlag	= inPacket->readUInt32();
	snprintf( petData.strName, MAX_NAME_CCH_LENGTH, inPacket->readUTF8(true).c_str() );
	for ( int32_t i = 0; i < PET_ATTR_COUNT; ++i )
	{
		petData.vAttr[i]	= inPacket->readInt32();
	}

	PET_MANAGER.UpdatePet( petData );
}

void SocialService::onDeletePetData(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	PET_MANAGER.DelPet( nPetId );
}

void SocialService::onUpdateServerDiffDay( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}
	m_serverdiffDay = inPacket->readInt32();
}

int32_t SocialService::GetServerDiffDay()
{
	return m_serverdiffDay;
}	

void SocialService::onRequestPetRankData( NetPacket *inPacket )
{
	if (NULL == inPacket)
	{
		return;
	}

	int32_t nLine = inPacket->readInt32();
	PET_MANAGER.SendGameAllRankInfo( nLine );
}

//void SocialService::UpdatePetRankBattleToGameServer( PetId_t nPetId, int32_t nAddBattle )
//{
//	NetPacket *packet = popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//
//	packet->writeInt64( nPetId );
//	packet->writeInt32( nAddBattle );
//	packet->setType( PACK_PROC );
//	packet->setProc( IM_SOCIAL_GAME_UPDATE_PET_RANK );
//	packet->setSize( packet->getWOffset() );
//	SOCIAL_SERVICE.sendPacket( packet );
//}


void SocialService::PacketItemLimitInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}
	MutexGuard lock(m_limitShopLock);
	ItemLimitMap::iterator it =	m_ItemLimitMap.begin();
	int32_t nSize = m_ItemLimitMap.size();
	inPacket->writeInt32( nSize );
	for ( ; it != m_ItemLimitMap.end(); ++it )
	{
		inPacket->writeInt32( it->first );
		inPacket->writeInt32( it->second );
	}
}

int32_t	SocialService::GetLimitCount( int32_t ShopId )
{
	MutexGuard lock(m_limitShopLock);
	ItemLimitMap::iterator it = m_ItemLimitMap.find( ShopId );
	if ( it != m_ItemLimitMap.end() )
	{
		return it->second;
	}
	return NULL;
}

void SocialService::AddLimitCount( int32_t ShopId, int32_t AddCount )
{
	if ( ShopId <= 0 || AddCount <= 0 )
	{
		return;
	}
	MutexGuard lock(m_limitShopLock);
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	bzero(szSQL,sizeof(szSQL));
	ItemLimitMap::iterator it = m_ItemLimitMap.find( ShopId );
	if ( it != m_ItemLimitMap.end() )
	{
		m_ItemLimitMap[ShopId] +=  AddCount;
		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_limit_shop` SET `LimitCount`= %d WHERE ShopId=%d", m_ItemLimitMap[ShopId],it->first );
		db.excute(szSQL);
	}
	else
	{
		m_ItemLimitMap[ShopId] = AddCount;
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_limit_shop`(`ShopId`,`LimitCount`,`RefreshTime`) VALUES (%d, %d, %d)",ShopId, AddCount, DayTime::now());
		db.excute(szSQL);
	}
}

void SocialService::RefreshLimitInfo()
{
	MutexGuard lock(m_limitShopLock);
	m_ItemLimitMap.clear();
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "TRUNCATE TABLE `mem_limit_shop`");
	db.excute(szSQL);
}

void SocialService::SendSystemMail( CharId_t nReceiver, int32_t nMailId, const MemChrBag& item )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( GAME_SERVICE_LINE_SOCIAL );
	uint16_t nOffset = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt64( nReceiver );
	packet->writeInt32( nMailId );
	packet->writeInt32( item.itemId );
	packet->writeInt8( item.itemClass );
	packet->writeInt32( item.itemCount );
	packet->writeInt64( item.srcId );
	packet->writeInt8( item.bind );
	packet->writeInt32( item.endTime );	

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_SINGLE_GAME_SEND_SYSTEM_MAIL );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialService::SendSystemMail( CharId_t nReceiver, int32_t nMailId, const ItemDataList& items )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( GAME_SERVICE_LINE_SOCIAL );
	uint16_t nOffset = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt64( nReceiver );
	packet->writeInt32( nMailId );
	packet->writeInt32( items.size() );
	for ( ItemDataList::const_iterator iter = items.begin(); iter != items.end(); ++iter )
	{
		packet->writeInt8( iter->m_nClass );
		packet->writeInt32( iter->m_nId );
		packet->writeInt32( iter->m_nCount );
	}	

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_SINGLE_GAME_SEND_SYSTEM_MAIL2 );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialService::onUpdateFamilyInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}
	FAMILY_MANAGER.UpdateFamilyInfo();
}
