#include "stdafx.h"

#include "CharacterService.h"
#include <algorithm>
#include <string>

using namespace Answer;
using namespace std;

#define RANDOM Answer::Singleton<Answer::Random>::instance()

CharacterService::CharacterService()
	: TcpService(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER, 2048-NET_PACKET_HEAD_LEN, 0, 2000, "CharacterService")
{
	bzero(&m_bornRegion, sizeof(m_bornRegion));
	m_bornAttr.clear();
	m_version = 0;
}

CharacterService::~CharacterService()
{

}

void CharacterService::onNetPacket(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	uint16_t proc = inPacket->getProc();
	if (proc > IM_MIN && proc < IM_MAX)
	{
		switch (proc)
		{
		case IM_GATE_ADD_USER: onAddUser(inPacket); break;
		case IM_GATE_REMOVE_USER: onRemoveUser(inPacket); break;
		default: break;
		}
	}
	else
	{
		int16_t cgindex = static_cast<int16_t>(inPacket->readInt32());
		if (cgindex > 0 && cgindex < MAX_CONNECTION)
		{
			switch (proc)
			{
			case CM_GET_CHARACTER: onGetCharacter(cgindex, inPacket); break;
			case CM_NEW_CHARACTER: onNewCharacter(cgindex, inPacket); break;
			//case CM_DEL_CHARACTER: onDelCharacter(cgindex, inPacket); break;
			default: break;
			}
		}
	}

	inPacket->destroy();
}

bool CharacterService::init(int32_t version)
{
	m_version = version;
	CDBCFile MapRegionFile(0);
	bool ret = MapRegionFile.OpenFromTXT("./ServerConfig/Tables/cfg_map_region.txt");
	if ( ret == false )
	{
		LOG_ERROR("open cfg_map_region.txt failed,please check!!");
		return false;
	}

	int32_t iBaseTableCount		=	MapRegionFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	MapRegionFile.GetFieldsNum();
	if (iBaseColumnCount <=0)
	{
		return false;
	}

	for( int32_t i = 0;i < iBaseTableCount;i++ )
	{
		m_bornRegion.id			= MapRegionFile.Search_Posistion(i,0)->iValue;
		m_bornRegion.mapid		= MapRegionFile.Search_Posistion(i,2)->iValue;
		m_bornRegion.min_x		= MapRegionFile.Search_Posistion(i,3)->iValue;
		m_bornRegion.min_y		= MapRegionFile.Search_Posistion(i,4)->iValue;
		m_bornRegion.max_x		= MapRegionFile.Search_Posistion(i,5)->iValue;
		m_bornRegion.max_y		= MapRegionFile.Search_Posistion(i,6)->iValue;
		m_bornRegion.type		= MapRegionFile.Search_Posistion(i,7)->iValue;
	}
	////////////////////////////////////////////////////////////////
	/*m_version = version;

	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `cfg_map_region` WHERE `id`=%d", PBA_REGION);

	MySqlQuery result = db.query(szSQL);
	if (!result.eof())
	{
		m_bornRegion.id = result.getIntValue("id");
		m_bornRegion.mapid = result.getIntValue("mapid");
		m_bornRegion.min_x = result.getIntValue("min_x");
		m_bornRegion.min_y = result.getIntValue("min_y");
		m_bornRegion.max_x = result.getIntValue("max_x");
		m_bornRegion.max_y = result.getIntValue("max_y");
		m_bornRegion.type = result.getIntValue("type");
	}*/

	if (m_bornRegion.id <= 0)
	{
		return false;
	}

	CDBCFile BornFile(0);
	bool retBorn = BornFile.OpenFromTXT("./ServerConfig/Tables/cfg_born_attr.txt");
	if ( retBorn == false )
	{
		LOG_ERROR("open cfg_born_attr.txt failed,please check!!");
		return false;
	}

	int32_t iBaseTableCountBorn		=	BornFile.GetRecordsNum();
	int32_t iBaseColumnCountBorn	=	BornFile.GetFieldsNum();
	if (iBaseColumnCountBorn <=0)
	{
		return false;
	}

	for( int32_t i = 0;i < iBaseTableCountBorn;i++ )
	{
		CfgBornAttr  attr = {};
		attr.job				= BornFile.Search_Posistion(i,0)->iValue;
		attr.attr			= parseAttrEffect(attr.job,BornFile.Search_Posistion(i,1)->pString);

		m_bornAttr[attr.job]	= attr;
	}
	/////////////////////////////////////////////////////////////////
	/*bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `cfg_born_attr`");
	result = db.query(szSQL);
	while (!result.eof())
	{
		CfgBornAttr  attr = {};
		attr.job = result.getIntValue("job");
		attr.attr = parseAttrEffect(attr.job,result.getStringValue("num_attr"));

		m_bornAttr[attr.job] = attr;

		result.nextRow();
	}*/
	CDBCFile SillDefaultFile(0);
	bool retDefault = SillDefaultFile.OpenFromTXT("./ServerConfig/Tables/SkillDefault.txt");
	if ( retDefault == false )
	{
		LOG_ERROR("open SkillDefault.txt failed,please check!!");
		return false;
	}

	int32_t iBaseTableCountSillDefault		=	SillDefaultFile.GetRecordsNum();
	int32_t iBaseColumnCountSillDefault		=	SillDefaultFile.GetFieldsNum();
	if (iBaseColumnCountSillDefault <=0)
	{
		return false;
	}

	for( int32_t i = 0;i < iBaseTableCountSillDefault;i++ )
	{
		CfgBornAttr  attr = {};
		int8_t Job				= SillDefaultFile.Search_Posistion(i,0)->iValue;
		m_SkillDefault[Job]		= SillDefaultFile.Search_Posistion(i,1)->iValue;
	}
	return true;
}

void CharacterService::onAddUser(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	int16_t cgindex = inPacket->readInt16();
	int32_t uid = inPacket->readInt32();
	int32_t sid = inPacket->readInt32();
	string fromip = inPacket->readUTF8(true);

	if (cgindex > 0 && cgindex < MAX_CONNECTION)
	{
		m_users[cgindex].m_uid = uid;
		m_users[cgindex].m_sid = sid;
		m_users[cgindex].m_fromip = fromip;
	}
}

void CharacterService::onRemoveUser(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	int16_t cgindex = inPacket->readInt16();
	if (cgindex > 0 && cgindex < MAX_CONNECTION)
	{
		m_users[cgindex].reset();
	}
}

void CharacterService::onGetCharacter(int16_t cgindex, Answer::NetPacket *inPacket)
{
	User &user = m_users[cgindex];
	if (user.m_uid > 0)
	{
		loadCharacterList(cgindex, user.m_uid, user.m_sid);
		sendCharacterList(cgindex);
	}
}

void CharacterService::onNewCharacter(int16_t cgindex, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	User &user = m_users[cgindex];
	if (user.m_uid <= 0 || user.m_characterNum < 0 || user.m_characterNum >= MAX_CHARACTER_NUM)
	{
		return;
	}

	Character chr;
	chr.m_name = inPacket->readUTF8(true);
	chr.m_sex = inPacket->readInt32();
	chr.m_job = inPacket->readInt32();
	chr.m_head = inPacket->readInt32();

	chr.m_level = 1;
	int32_t SkillId		= 0;
	if (chr.m_name.empty() || StringUtility::utf8Strlen(chr.m_name.c_str()) > MAX_NAME_LENGTH)
	{
		return;
	}

	if (chr.m_sex != SEX_MALE && chr.m_sex != SEX_FEMALE)
	{
		return;
	}

	if (chr.m_job < PJ_ZHANSHI || chr.m_job >= PJ_JOB_COUNT)
	{
		return;
	}
	std::map<int8_t,int32_t>::iterator it = m_SkillDefault.find(chr.m_job);
	if ( it != m_SkillDefault.end() )
	{
		SkillId = it->second;
	}
	
	if (chr.m_head < MIN_HEAD_ID || chr.m_head > MAX_HEAD_ID)
	{
		return;
	}
	//SecondAttr attr = {};

	/*
	chr.m_mapid = m_bornRegion.mapid;
	Position pos = getRandomPositionInRegion(m_bornRegion);
	chr.m_x = pos.x;
	chr.m_y = pos.y;
	*/
	chr.m_mapid = -1;	// 出生点在第一次登陆时会修复

	chr.fight_power = 0;//calcBornAttr(chr.m_job, attr);

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT `cid` FROM `mem_character` WHERE `name`='%s'", chr.m_name.c_str());

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query(szSQL);
	if (result.getRowCount() != 0)
	{
		replyfailure(cgindex, inPacket->getProc(), ERR_NAME_EXIST);
		return;
	}

	// getcid
	chr.m_cid = GetNewCharId( user.m_sid );
	if ( chr.m_cid <= 0 )
	{
		replyfailure(cgindex, inPacket->getProc(), ERR_INVALID_DATA );
		return;
	}

	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_character` (`cid`, `uid`, `sid`, `name`, `sex`,`job`, `level`,  `mapid`, `x`, `y`, `hp`, `mp`,`pp`, `head`, `create_time`) VALUES (%lld, %d, %d, '%s', %d, %d, %d, %d,%d, %d, %d, %d, %d, %d, %d)", 
		chr.m_cid, user.m_uid, user.m_sid, chr.m_name.c_str(), chr.m_sex,chr.m_job, chr.m_level, chr.m_mapid, chr.m_x, chr.m_y, 9999999, 9999999,99999999, chr.m_head, DayTime::now() );
	if (db.excute(szSQL) != ERR_ANSWER_OK)
	{
		replyfailure(cgindex, inPacket->getProc(), ERR_NAME_EXIST);
		return;
	}
	//chr.m_cid = db.lastInsertId();

	//bzero(szSQL, sizeof(szSQL));
	//snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_peoplebook` (`cid`,`taoyuan_level`, `refugee`, `resident`,`servant`, `squire`, `relief_time`, `ty_exp`, `ty_money`, `recruit_time`, `change_exp_time`, `yanwuchang_level`, `vicegeneral_id`, `cultivation_time`, `is_cultivation`) VALUES (%d, %d, %d, %d, %d, %d, %d,  %d, %d, %d, %d, %d, %d, %d, %d)", 
	//	chr.m_cid ,1,30,0,0,0,0,0,0,0,DayTime::now(),1,0,0,0);
	//db.excute(szSQL);

	//bzero(szSQL, sizeof(szSQL));
	//snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_glebebook` (`cid`, `shejitu_level`,`production_count`,`mine_id`,`mine_time`,`shenlongding_level`, `refining_count`,`active_index`,`lingtaifudi_level`,`mount_id`,`is_cultivation`,`cultivation_time`) VALUES (%d, %d,%d, '%s','%s',%d, %d,%d,%d,%d,%d,%d)", 
	//	chr.m_cid ,1,0,"","",1,0,1,1,0,0,0);
	//db.excute(szSQL);

	//bzero(szSQL, sizeof(szSQL));
	//snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_skybook` (`cid`,`kunlunjing_count`,`jiutianta_count`,`fengyinbang_count`) VALUES (%d, %d, %d, %d)", 
	//	chr.m_cid ,0,0,0);
	//db.excute(szSQL);

	// 初始化插入基础属性
	//bzero(szSQL, sizeof(szSQL));
	//snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_chr_attr` (`cid`,`maxhp`,`maxmp`,`attack`,`pdef`,`mdef`,`vp`,`dp`,`htip`,`vpp`,`prevp`,`prerost`,`prebk`,`preduce`,`mreduce`,`total_fight_power`) VALUES (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)", 
	//	chr.m_cid ,attr.maxhp,attr.maxmp,attr.attack,attr.pdef,attr.mdef,attr.vp,attr.dp,attr.hitp,attr.vpp,attr.prevp,attr.preforst,attr.prebk,attr.preduce,attr.mreduce,chr.fight_power);
	//db.excute(szSQL);

	bzero(szSQL, sizeof(szSQL));
	if (m_version == 1)
	{
		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `sys_user` SET `cash`=0,`gold` = 0 WHERE `uid`=%d AND `sid`=%d", user.m_uid, user.m_sid);
	}
	else
	{
		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `sys_user` SET `cash`=0 WHERE `uid`=%d AND `sid`=%d", user.m_uid, user.m_sid);
	}
	
	db.excute(szSQL);
  
	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `sys_user` SET `chr_create_time`=UNIX_TIMESTAMP() WHERE `uid`=%d AND `sid`=%d AND `chr_create_time`=0", user.m_uid, user.m_sid);
	db.excute(szSQL);
	//第一个任务
	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_chr_task` (cid,tid,state,monster) VALUES (%lld,%d,%d,%d)", chr.m_cid, 10000,3,0);
	db.excute(szSQL);
	//天赋技能，最基础技能
	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_chr_skill` (`cid`, `sid`, `level`) VALUES (%lld, %d, %d)", chr.m_cid, SkillId, 1);
	db.excute(szSQL);
	bzero(szSQL, sizeof(szSQL));
	snprintf( szSQL, sizeof( szSQL ) - 1, "INSERT INTO `mem_chr_action` (`cid`, `slot`, `id`, `type`) VALUES (%lld, %d, %d, %d)", chr.m_cid, 1, SkillId, 2 );
	
	db.excute(szSQL);

	user.m_characters[user.m_characterNum] = chr;
	user.m_characterNum++;

	sendCharacterList(cgindex);
}

//void CharacterService::onDelCharacter(int16_t cgindex, Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return;
//	}
//
//	CharId_t cid = inPacket->readInt64();
//
//	User &user = m_users[cgindex];
//	if (cid > 0 && user.m_uid > 0 && user.m_characterNum > 0)
//	{
//		int chrindex = 0;
//		for (; chrindex < user.m_characterNum; ++chrindex)
//		{
//			if (user.m_characters[chrindex].m_cid == cid)
//			{
//				break;
//			}
//		}
//
//		if (chrindex < user.m_characterNum)
//		{
//			FamilyId_t family_id = 0;
//			char szSQL[MAX_SQL_LENGTH] = {};
//			snprintf(szSQL, sizeof(szSQL)-1, "SELECT `family_id`, `position` FROM `mem_chr_family` WHERE `cid`=%lld", cid);
//
//			MySqlDBGuard db(DBPOOL);
//			MySqlQuery result = db.query(szSQL);
//			if (!result.eof())
//			{
//				int32_t position = result.getIntValue("position");
//				family_id = result.getInt64Value("family_id");
//				if (position == FP_LEADER)
//				{
//					replyfailure(cgindex, inPacket->getProc(), ERR_DELETE_CHR_AS_FAMILY_LEADER);
//					return;
//				}
//			}
//
//			bzero(szSQL, sizeof(szSQL));
//			snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_character` SET `delete_time`=%d WHERE `cid`=%lld", DayTime::now(), cid);
//
//			db.excute(szSQL);
//
//			for (chrindex++; chrindex < user.m_characterNum; ++chrindex)
//			{
//				user.m_characters[chrindex-1] = user.m_characters[chrindex];
//			}
//
//			user.m_characterNum--;
//
//			sendCharacterList(cgindex);
//
//			sendDeleteCharacter(cid, family_id);
//		}
//	}
//}

void CharacterService::sendCharacterList(int16_t cgindex)
{
	const User &user = m_users[cgindex];
	if (user.m_uid > 0 && user.m_characterNum >= 0)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(user.m_lastLoginTime);
		packet->writeUTF8(user.m_lastLoginIp);
		packet->write(user.m_characterNum);
		for (int i = 0; i < user.m_characterNum; ++i)
		{
			packet->writeInt64(user.m_characters[i].m_cid);
			packet->writeUTF8(user.m_characters[i].m_name);
			packet->writeInt32(user.m_characters[i].m_sex);
			packet->writeInt32(user.m_characters[i].m_style);
			packet->writeInt32(user.m_characters[i].m_head);
			packet->writeInt32(0);	// kingdom
			packet->writeInt32(user.m_characters[i].m_job);
			packet->writeInt32(user.m_characters[i].m_level);
			packet->writeInt32(user.m_characters[i].m_mapid);
			packet->writeInt32(user.m_characters[i].m_x);
			packet->writeInt32(user.m_characters[i].m_y);
		}
		packet->setType(PACK_DISPATCH);
		packet->setProc(SM_CHARACTER_LIST);
		packet->setSize(packet->getWOffset());
		sendPacketTo(cgindex, packet);
	}
}

void CharacterService::loadCharacterList(int16_t cgindex, int32_t uid, int32_t sid)
{
	User &user = m_users[cgindex];

	MySqlDBGuard db(DBPOOL);

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT last_login_time,last_login_ip FROM `sys_user` As a WHERE `uid`=%d AND `sid`=%d", uid, sid);
	MySqlQuery result = db.query(szSQL);
	if (result.getRowCount() == 1)
	{
		user.m_lastLoginTime = result.getIntValue("last_login_time");
		user.m_lastLoginIp = result.getStringValue("last_login_ip");
	}

	user.m_characterNum = 0;
	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT `cid`, `name`, `sex`, `job`, `level`, `mapid`, `x`, `y`, `head` FROM `mem_character` WHERE `uid`='%d' AND `sid`=%d AND `delete_time`=0", uid, sid);

	result = db.query(szSQL);
	if (!result.eof())
	{
		Character chr;
		chr.m_cid = result.getInt64Value("cid");
		chr.m_name = result.getStringValue("name");
		chr.m_sex = result.getIntValue("sex");
		chr.m_job = result.getIntValue("job");
		chr.m_level = result.getIntValue("level");
		chr.m_mapid = result.getIntValue("mapid");
		chr.m_x = result.getIntValue("x");
		chr.m_y = result.getIntValue("y");
		chr.m_head = result.getIntValue("head");
		
		user.m_characters[user.m_characterNum] = chr;
		user.m_characterNum++;

		if (result.getRowCount() > 1)
		{
			LOG_INFO("Player loadcharList error%d,uid:%d,sid:%d",result.getRowCount(),uid,sid);
		}
		result.nextRow();
	}

	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `sys_user` SET `last_login_ip`='%s' WHERE `uid`=%d AND `sid`=%d", user.m_fromip.c_str(), uid, sid);
	db.excute(szSQL);

	bzero(szSQL, sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `sys_user` SET `chr_list_time`=UNIX_TIMESTAMP() WHERE `uid`=%d AND `sid`=%d AND `chr_list_time`=0", uid, sid);
	db.excute(szSQL);
}

//void CharacterService::sendDeleteCharacter( CharId_t cid, FamilyId_t family_id )
//{
//	NetPacket *packet = popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt64(cid);
//	packet->writeInt64(family_id);
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_DELETE_CHARACTER);
//	packet->setSize(packet->getWOffset());
//	sendPacket(packet);
//}

AttrAddonVector CharacterService::parseAttrEffect(int32_t id, const std::string &str)
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
				LOG_ERROR("CfgData::parseAttrEffect  wrong data with id = %d, str = %s\n", id, str.c_str());
			}
		}
	}

	return attrAddons;
}

Position CharacterService::getRandomPositionInRegion(const CfgMapRegion &region)
{
	Position pos(-1, -1);

	int32_t minXAddHalfY = xAddHalfY(region.min_x, region.min_y);
	int32_t maxXAddHalfY = xAddHalfY(region.max_x, region.max_y);

	int32_t minXSubHalfY = xSubHalfY(region.min_x, region.min_y);
	int32_t maxXSubHalfY = xSubHalfY(region.max_x, region.max_y);

	if (minXSubHalfY < maxXSubHalfY)
	{
		int32_t rollXAddHalfY = RANDOM.generate(minXAddHalfY, maxXAddHalfY);
		int32_t rollXSubHalfY = RANDOM.generate(minXSubHalfY, maxXSubHalfY);

		pos.x = (rollXAddHalfY+rollXSubHalfY)/2;
		pos.y = rollXAddHalfY - rollXSubHalfY;
	}

	return pos;
}

int32_t CharacterService::xAddHalfY(int32_t x, int32_t y)
{
	return x + y/2;
}

int32_t CharacterService::xSubHalfY(int32_t x, int32_t y)
{
	return x - y/2;
}

//int32_t CharacterService::calcBornAttr(int32_t job,SecondAttr &attr)
//{
//	int32_t fightPower = 0;
//	int32_t temp = 0;
//	CfgBornAttrTable::iterator it = m_bornAttr.find(job);
//	if (it != m_bornAttr.end())
//	{
//		for (AttrAddonVector::iterator iter = it->second.attr.begin();iter !=it->second.attr.end();++iter)
//		{
//			switch(iter->index)
//			{
//			case  ATTR_ATTACK:
//				attr.attack  = iter->addon;
//				fightPower += iter->addon;
//				break;
//			case  ATTR_PDEF:
//				attr.pdef  = iter->addon;
//				fightPower += iter->addon;
//				break;
//			case  ATTR_MDEF:
//				attr.mdef  = iter->addon;
//				fightPower += iter->addon;
//				break;
//			case  ATTR_MAXHP:
//				attr.maxhp  = iter->addon;
//				fightPower += iter->addon/10;
//				break;
//			case  ATTR_MAXMP:
//				attr.maxmp = iter->addon;
//				fightPower += iter->addon/30;
//				break;
//			case  ATTR_VP:
//				attr.vp = iter->addon;
//				temp += iter->addon/100;
//				break;
//			case  ATTR_VPP:
//				attr.vpp = iter->addon;
//				temp += iter->addon/100;
//				break;
//			case  ATTR_PREBK:
//				attr.prebk = iter->addon;
//				temp += iter->addon/100;
//				break;
//			case  ATTR_PREFROST:
//				attr.preforst = iter->addon;
//				temp += iter->addon/100;
//				break;
//			case  ATTR_PREDUCE:
//				attr.preduce = iter->addon;
//				temp += iter->addon/100;
//				break;
//			case  ATTR_MREDUCE:
//				attr.mreduce = iter->addon;
//				temp += iter->addon/100;
//				break;
//			case  ATTR_HTIP:
//				attr.hitp = iter->addon;
//				temp += iter->addon/200;
//				break;
//			case  ATTR_DP:
//				attr.dp = iter->addon;
//				temp += iter->addon/200;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//
//	temp  += 1;
//	return  fightPower = static_cast<int32_t>(fightPower*temp);
//}

CharId_t CharacterService::GetNewCharId( int32_t nServerId )
{
	char szSql[MAX_SQL_LENGTH] = {};
	snprintf( szSql, sizeof( szSql ) - 1, "call NewCharId(%d,@OutCharId)", nServerId );

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( szSql );
	if ( !result.eof() )
	{
		int32_t nNewCharId = result.getIntValue( 0 );
		if ( nNewCharId > 0 )
		{
			return ( static_cast<CharId_t>( nServerId ) << 32 ) + nNewCharId;
		}
	}

	LOG_ERROR( "CharacterService::GetNewCharId() FAIL!!!!!!! time=%d\n", Answer::DayTime::now() );
	return 0;
}
