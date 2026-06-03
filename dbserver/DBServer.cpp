#include "stdafx.h"

#include "DBServer.h"
#include "DBSaver.h"
#include "DataStruct.h"

#include <algorithm>
#include <string>
using namespace Answer;
using namespace std;

DBServer::DBServer()
		: TcpServer(16384-NET_PACKET_HEAD_LEN, 0, 2000, false)
{
	m_currentTime = 0;
	m_currentProc=0;
	m_PlayerConnection.clear();
}

DBServer::~DBServer()
{

}

void DBServer::onConnect(Answer::TcpConnection *conn)
{
	if (NULL == conn)
	{
		return;
	}
	conn->setCheckPackSize(false);
	conn->setCheckHalt(false);
	if (std::find(m_accetpIps.begin(), m_accetpIps.end(), conn->getIP()) == m_accetpIps.end())
	{
		LOG_WARN("DBServer::onConnect with invalid ip %s, halt it\n", conn->getIP().c_str());
		conn->halt();
	}

#ifdef _DEBUG
	else
	{
		printf( "DBServer::onConnect with ip %s\n", conn->getIP().c_str() );
	}
#endif
}

void DBServer::onDisconnect(Answer::TcpConnection *conn)
{
	if (NULL == conn)
	{
		return;
	}
	conn->setPtr(NULL);
	removeConn(conn);
	LOG_DEBUG("DBServer::onDisconnect with ip %s\n", conn->getIP().c_str());
}

void DBServer::onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	uint16_t proc = inPacket->getProc();

	int64_t nowTime= DayTime::tick();
	if (nowTime-m_currentTime <=30 && m_currentProc==proc) //小于30ms的包丢弃
	{
		m_currentTime =nowTime;
		LOG_ERROR("不正常的协议%d",proc);
		return;
	}
	m_currentProc =proc;
	switch (proc)
	{
	case IM_DB_GAME_SERVICE_CONNECT:			onDBGameServiceConnect(conn, inPacket);			break; //添加一个客户连接
	case IM_DB_LOAD_PLAYER:						onDBLoadPlayer(conn, inPacket);					break;
	case IM_DB_SAVE_PLAYER:						onDBSavePlayer(conn, inPacket);					break;
	case IM_DB_INSERT_EQUIP:					onDBInsertEquip(conn, inPacket);				break;
	case IM_DB_UPDATE_EQUIP:					onDBUpdateEquip(conn, inPacket);				break;
	case IM_DB_DELETE_EQUIP:					onDBDeleteEquip(conn, inPacket);				break;
	case IM_DB_INSERT_PET:						onDBInsertPet(conn, inPacket);					break;
	case IM_DB_UPDATE_PET:						onDBUpdatePet(conn, inPacket);					break;
	case IM_DB_DELETE_PET:						onDBDeletePet(conn, inPacket);					break;
	//case IM_DB_UPDATE_FAMILY_WAR:				onDBUpdateFamilyWar(conn, inPacket);			break;
	case IM_DB_LOG_TASK_RECEIVE:				onDBInsertTask(conn,inPacket);					break;
	case IM_DB_LOG_TASK_SUBMIT:					onDBUpdateTask(conn,inPacket);					break;
	case IM_DB_LOG_EQUIP_ENHANCE:				onDBInsertEquipEnhance(conn,inPacket);			break;
	case IM_DB_LOG_ARTIFACT_ADD_EXP:			onDBLogArtifactAddExp(conn, inPacket);			break;
	case IM_DB_LOG_ARTIFACT_ADD_MAX_LEVEL:		onDBLogArtifactAddMaxLevel(conn, inPacket);		break;
	case IM_DB_LOG_ARTIFACT_ADD_QUALITY:		onDBLogArtifactAddQuality(conn, inPacket);		break;
	case IM_DB_LOG_EQUIP_ADD_GEM:				onDBInsertEquipAddGem(conn, inPacket);			break;
	case IM_DB_LOG_ITEM_COMBINE:				onDBInsertItemCombine(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_SMITHING:				onDBInsertEquipSmithing(conn, inPacket);		break;
	case IM_DB_LOG_EQUIP_DISMANTLE:				onDBInsertEquipDismantle(conn, inPacket);		break;
	case IM_DB_LOG_IN_DUNGEON:					onDBInsertDungeon(conn, inPacket);				break;
	case IM_DB_LOG_OUT_DUNGEON:					onDBUpdateDungeon(conn, inPacket);				break;
	case IM_DB_LOG_KILL_BOSS:					onDBLogKillBoss(conn, inPacket);				break;
	case IM_DB_LOG_DAILY_GIFT:					onDBLogDailyGift(conn,inPacket);				break;
	case IM_DB_LOG_CREATE_FAMILY:				onDBInsertFamilyCreate(conn, inPacket);			break;
	case IM_DB_LOG_JOIN_FAMILY:					onDBInsertFamilyJoin(conn, inPacket);			break;
	case IM_DB_LOG_OUT_FAMILY:					onDBUpdateFamilyOut(conn, inPacket);			break;
	case IM_DB_LOG_ACHIEVEMENT:					onDBInsertAchievement(conn, inPacket);			break;
	case IM_DB_LOG_ITEM_CHANGE:					onDBInsertItemChange(conn,inPacket);			break;
	case IM_DB_LOG_EQUIP_ADD_GEM_SLOT:			onDBLogEquipAddGemSlot(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_APPEND_STAR:			onDBLogEquipAppendStar(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_COMBINE:				onDBLogEquipCombine(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_FORGE:					onDBLogEquipForge(conn, inPacket);				break;
	case IM_DB_LOG_EQUIP_LIFE:					onDBLogEquipLife(conn, inPacket);				break;
	case IM_DB_LOG_EQUIP_REFRESH_BIND:			onDBLogEquipRefreshBind(conn, inPacket);		break;
	case IM_DB_LOG_EQUIP_REFRESH_ELEMENT:		onDBLogEquipRefreshElement(conn, inPacket);		break;
	case IM_DB_LOG_EQUIP_REFRESH_FLOAT_ATTR:	onDBLogEquipRefreshFloatAttr(conn, inPacket);	break;
	case IM_DB_LOG_EQUIP_REMOVE_GEM:			onDBLogEquipRemoveGem(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_REMOVE_STAR:			onDBLogEquipRemoveStar(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_STRENGTHEN:			onDBLogEquipStrengthen(conn, inPacket);			break;
	case IM_DB_LOG_EQUIP_UPGRADE:				onDBLogEquipUpgrade(conn, inPacket);			break;
	case IM_DB_LOG_ACTIVITY_DATA:				onDBLogActivityData(conn,inPacket);				break;
	case IM_DB_LOG_PLAYER_LOGIN:				onDBLogPlayerLogin(conn, inPacket);				break;
	case IM_DB_LOG_PLAYER_DEAL:					onDBLogPlayerDeal(conn, inPacket);				break;
	case IM_DB_USER_PAY:						onDBUserPay(conn, inPacket);					break;
	case IM_DB_INSERT_MEMYELLOWSTONE:			onDBInsertMemYellowStone(conn, inPacket);		break;
	case IM_DB_LOG_CURRENCY:					onDBLogCurrency( conn, inPacket );				break;
	case IM_DB_ADD_RANSOM_INFO:					onDBAddRansom( conn, inPacket );				break;
	case IM_DB_DLE_RANSOM_INFO:					onDbDleRansom( conn, inPacket );				break;
	case IM_DB_SEND_MAIL_TO_DB:					onInsertMailToDB( conn, inPacket );				break;
	case IM_DB_NEW_MINUTE:						onNewMinuteCome( conn, inPacket );				break;
	case IM_DB_SAVE_FAMILY_WAR_RESULT:			onSaveFamilyWarResult( conn, inPacket );		break;
	case IM_DB_SAVE_TERRITORY_WAR_RESULT:		onSaveTerritoryWarResult( conn, inPacket );		break;
	case IM_DB_UPDATE_LOGIN_TIME:				onUpdateLoginTime(conn, inPacket);				break;
	default: break;
	}
}

void DBServer::setAcceptIps(const StringVector &acceptIps)
{
	m_accetpIps.assign(acceptIps.begin(), acceptIps.end());
}

void DBServer::onDBGameServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != NULL)
	{
		return;
	}

	conn->setPtr(conn);
	addConn(conn);
#ifdef _DEBUG
	printf( "DBServer::onDBGameServiceConnect with ip %s\n", conn->getIP().c_str() );
#endif
}

void DBServer::onDBLoadPlayer(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	int16_t cgindex = inPacket->readInt16();
	int32_t uid = inPacket->readInt32();
	int32_t sid = inPacket->readInt32();

	int64_t beginTick = DayTime::tick();

	MySqlDBGuard db( DBPOOL );
	char szSQL[MAX_SQL_LENGTH] = {};

	snprintf( szSQL, sizeof(szSQL)-1, "SELECT cid FROM `mem_character` WHERE `uid`=%d AND `sid`=%d AND `delete_time`=0", uid, sid );
	Answer::MySqlQuery result = db.query(szSQL);
	if ( result.getRowCount() != 1 )
	{
		return;
	}

	bool bInMap = false;
	PlayerDBData dbData;
	CharId_t cid = result.getInt64Value("cid");

	{
		MutexGuard lock(m_PlayerDBDataLock);
		std::map<CharId_t,PlayerDBData>::iterator findIter = m_PlayerDBData.find( cid );
		if ( findIter != m_PlayerDBData.end() )
		{
			if ( findIter->second.saveRefCount != 0 )
			{
				bInMap = true;
				findIter->second.cgindex = cgindex;
				dbData = findIter->second;
				dbData.LoadUseSpecialInfo( db, szSQL, uid, sid );
			}
		}
	}

	if ( !bInMap )
	{
		dbData.cgindex = cgindex;
		if ( !dbData.LoadFromDB( db, szSQL, uid, sid ) )
		{
			return;
		}

		MutexGuard lock(m_PlayerDBDataLock);
		m_PlayerDBData[cid] = dbData;
	}

	{
		MutexGuard lock(m_PlayerConnLock);
		m_PlayerConnection[dbData.chr.data.cid] = conn;
	}

	int64_t endTick = DayTime::tick();
	int32_t usedTick = static_cast<int32_t>( endTick - beginTick );

	LOG_INFO( "DBServer::onDBLoadPlayer() cid=%lld, used time=%d\n", dbData.chr.data.cid, usedTick );

	//broadcastEquipUpdated( dbData.equips.equipVt, NULL);	// TODO：需要新的更新方式
	//broadcastItemUpdated( dbData.items.itemVt, NULL);

	// send to gameserver
	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	dbData.PackageData( packet );
	packet->setType( PACK_DISPATCH );
	packet->setProc( IM_DB_PLAYER_LOADED );
	packet->setSize( packet->getWOffset() );

	conn->sendPacket(packet, true);
}

void DBServer::onUpdateLoginTime(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	CharId_t cid = inPacket->readInt64();
	int32_t login_time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_character` a LEFT JOIN `sys_user` b ON a.uid=b.uid AND a.sid=b.sid SET a.last_login_time=%d, b.last_login_time=%d WHERE a.cid=%lld", login_time, login_time, cid );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onSaveOver( CharId_t cid )
{
	MutexGuard lock(m_PlayerDBDataLock);
	std::map<CharId_t,PlayerDBData>::iterator findIter = m_PlayerDBData.find( cid );
	if ( findIter != m_PlayerDBData.end() )
	{
		findIter->second.saveRefCount--;
	}
}

void DBServer::onDBSavePlayer(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	int64_t beginTick = DayTime::tick();

	int32_t reason = inPacket->readInt32();
	int32_t param = inPacket->readInt32();

	PlayerDBData dbData;
	dbData.UnPackageData( inPacket );

	{
		MutexGuard lock(m_PlayerDBDataLock);
		dbData.saveRefCount = m_PlayerDBData[dbData.chr.data.cid].saveRefCount + 1;
		m_PlayerDBData[dbData.chr.data.cid] = dbData;
	}

	//SqlStringList sqls;
	PlayerDBSql playerdb( dbData.chr.data.cid );
	char szSQL[MAX_SQL_LENGTH] = {};
	dbData.SaveToSqlString( playerdb.sqls, szSQL, dbData.chr.data.cid );

	//MySqlDBGuard db(DBPOOL);

	//SqlStringList::iterator iter = sqls.begin();
	//SqlStringList::iterator eiter = sqls.end();
	//for ( ; iter != eiter; ++iter )
	//{
	//	db.excute( iter->c_str() );
	//}
	DB_SAVER.AddPlayerDB( playerdb );

	int64_t endTick = DayTime::tick();
	int32_t usedTick = static_cast<int32_t>( endTick - beginTick );
	LOG_INFO( "DBServer::onDBSavePlayer() cid=%lld, used time=%d\n", dbData.chr.data.cid, usedTick );

	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( dbData.chr.data.cid );
	packet->writeUTF8( dbData.chr.data.name );
	packet->writeInt32( usedTick );
	packet->writeInt32( dbData.sysUser.data.uid );
	packet->writeInt32( dbData.sysUser.data.sid );
	packet->writeInt32( reason );
	packet->writeInt32( param );
	packet->setType(PACK_DISPATCH);
	packet->setProc(IM_DB_PLAYER_SAVED);
	packet->setSize(packet->getWOffset());
	conn->sendPacket(packet, true);

	if ( reason != LR_SAVE_INTERVAL )
	{
		MutexGuard lock(m_PlayerConnLock);
		m_PlayerConnection.erase( dbData.chr.data.cid );
	}
}

void DBServer::onDBInsertEquip(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	MemEquip equip;

	equip.id					= inPacket->readInt64();
	equip.base					= inPacket->readInt32();
	equip.owner					= inPacket->readInt64();
	equip.star					= inPacket->readInt32();
	equip.starLucky				= inPacket->readInt32();
	equip.addAttr				= inPacket->readInt32();
	equip.UpGradeLucky			= inPacket->readInt32();
	equip.UpQuality				= inPacket->readInt32();
	std::string EquipString		= inPacket->readUTF8(true);
	equip.ParesEquipString( EquipString );

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, 
				"INSERT INTO `mem_equip` (`id`, `base`, `owner`,`star`,`starLucky`, `addAttr`,`UpGradeLucky`,`UpQuality`,`EquipGem`) VALUES (%lld, %d, %lld, %d, %d, %d,%d,%d,'%s')",
				equip.id, 
				equip.base, 
				equip.owner, 
				equip.star,
				equip.starLucky,
				equip.addAttr,
				equip.UpGradeLucky,
				equip.UpQuality,
				equip.GetEquipGemString().c_str()
				);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	broadcastEquipUpdated(equip, conn);
}

void DBServer::onDBUpdateEquip(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	MemEquip equip;

	equip.id				= inPacket->readInt64();
	equip.nFlag				= inPacket->readInt32();
	equip.base				= inPacket->readInt32();
	equip.owner				= inPacket->readInt64();
	equip.star				= inPacket->readInt32();
	equip.starLucky			= inPacket->readInt32();
	equip.addAttr			= inPacket->readInt32();
	equip.UpGradeLucky		= inPacket->readInt32();
	equip.UpQuality			= inPacket->readInt32();
	std::string EquipString = inPacket->readUTF8(true);
	equip.ParesEquipString( EquipString );

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, 
				"UPDATE `mem_equip` SET `base`=%d, `owner`=%lld, `star`=%d,`starLucky`=%d,`addAttr`=%d, `UpGradeLucky`=%d,`UpQuality`=%d, `EquipGem`='%s'  WHERE `id`=%lld",
				equip.base, 
				equip.owner, 
				equip.star,  
				equip.starLucky,
				equip.addAttr,
				equip.UpGradeLucky,
				equip.UpQuality,
				equip.GetEquipGemString().c_str(),
				equip.id
				);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	broadcastEquipUpdated(equip, conn);
}

void DBServer::onDBDeleteEquip(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	EquipId_t eid = inPacket->readInt64();

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_equip` SET `owner`=0 WHERE `id`=%lld", eid);

	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	//TODO: notify game server
}

void DBServer::onDBInsertPet(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	MemPetDBData pet;
	pet.UnPackageData( inPacket );

	char szSQL[MAX_SQL_LENGTH] = {};
	pet.InsertSqlString( szSQL );

	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	broadcastPetUpdated(pet, conn);
}

void DBServer::onDBUpdatePet(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	MemPetDBData pet;
	pet.UnPackageData( inPacket );

	char szSQL[MAX_SQL_LENGTH] = {};
	pet.UpdateSqlString( szSQL );

	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	broadcastPetUpdated(pet, conn);
}

void DBServer::onDBDeletePet(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_pet` SET `delflag`=1 WHERE `pid`=%lld", static_cast<int64_t>( nPetId ) );

	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	broadcastPetDeleted( nPetId, conn );
}

void DBServer::broadcastPetUpdated(const MemPetDBData &pet, Answer::TcpConnection *except)
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if (conn != NULL && conn != except)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			pet.PackageData( packet );
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_PET_UPDATED);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}

void DBServer::broadcastPetDeleted( PetId_t nPetId, Answer::TcpConnection *except)
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if (conn != NULL && conn != except)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			packet->writeInt64( nPetId );
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_PET_DELETED);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}
//
//void DBServer::onDBUpdateFamilyWar(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
//{
//	if (NULL == conn || NULL == inPacket)
//	{
//		return;
//	}
//	if (conn->getPtr() != conn)
//	{
//		return;
//	}
//
//	FamilyId_t family_id = inPacket->readInt64();
//	string family_name = inPacket->readUTF8(true);
//
//	//MySqlDBGuard db(DBPOOL);
//
//	//db.excute("DELETE FROM `mem_family_war`");
//	DB_SAVER.AddSqlString( "DELETE FROM `mem_family_war`" );
//
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_family_war` (`family_id`, `family_name`) VALUES (%lld, '%s')", family_id, family_name.c_str());
//	//db.excute(szSQL);
//	DB_SAVER.AddSqlString( szSQL );
//
//	broadcastFamilyWarUpdated(family_id, family_name, conn);
//}

void DBServer::onDBInsertTask(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogTask logTask = {};
	logTask.cid = inPacket->readInt64();
	logTask.tid = inPacket->readInt32();
	logTask.type = inPacket->readInt32();
	logTask.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, 
		"INSERT INTO `log_task` (`cid`, `tid`,`type`, `receive_time`) VALUES (%lld,%d,%d,%d)",
		logTask.cid, logTask.tid, logTask.type, logTask.time);

	DB_SAVER.AddSqlString( szSQL );

}

void DBServer::onDBUpdateTask(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogTask logTask = {};
	logTask.cid = inPacket->readInt64();
	logTask.tid = inPacket->readInt32();
	logTask.type = inPacket->readInt32();
	logTask.time = inPacket->readInt32();
	logTask.state = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, 
		"UPDATE `log_task` SET `submit_time`=%d,`state` = %d WHERE `cid`=%lld AND `tid` = %d AND `state` = 0",
		logTask.time, logTask.state, logTask.cid, logTask.tid );

	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertEquipEnhance(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipEnhance enhance = {};
	enhance.cid = inPacket->readInt64();
	snprintf(enhance.name,MAX_NAME_CCH_LENGTH,inPacket->readUTF8(true).c_str());
	enhance.equip_id = inPacket->readInt64();
	enhance.base_id = inPacket->readInt32();
	enhance.equip_quality = inPacket->readInt32();
	enhance.old_level = inPacket->readInt32();
	enhance.new_level = inPacket->readInt32();
	enhance.money_cost = inPacket->readInt32();
	enhance.sys_gold_cost = inPacket->readInt32();
	enhance.gold_cost = inPacket->readInt32();
	enhance.time = inPacket->readInt32();
	
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_enhance` (`cid`, `name`, `equip_id`, `base_id`, `equip_quality`, `old_level`, `new_level`, `money_cost`, `sys_gold_cost`, `gold_cost`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d, %d, %d, %d)",
		enhance.cid, enhance.name, enhance.equip_id, enhance.base_id, enhance.equip_quality, enhance.old_level, enhance.new_level, enhance.money_cost, enhance.sys_gold_cost, enhance.gold_cost, enhance.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogArtifactAddExp(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogArtifactAddExp artifactAddExp = {};
	artifactAddExp.cid = inPacket->readInt64();
	snprintf(artifactAddExp.name, sizeof(artifactAddExp.name)-1, inPacket->readUTF8(true).c_str());
	artifactAddExp.itemid = inPacket->readInt32();
	artifactAddExp.baseid = inPacket->readInt32();
	artifactAddExp.old_exp = inPacket->readInt32();
	artifactAddExp.old_level = inPacket->readInt32();
	artifactAddExp.new_exp = inPacket->readInt32();
	artifactAddExp.new_level = inPacket->readInt32();
	artifactAddExp.stone_id = inPacket->readInt32();
	artifactAddExp.stone_count = inPacket->readInt32();
	artifactAddExp.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_artifact_add_exp` (`cid`, `name`, `itemid`, `baseid`, `old_exp`, `old_level`, `new_exp`, `new_level`, `stone_id`, `stone_count`, `time`) VALUES (%lld, '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d)",
			 artifactAddExp.cid, artifactAddExp.name, artifactAddExp.itemid, artifactAddExp.baseid, artifactAddExp.old_exp, artifactAddExp.old_level, artifactAddExp.new_exp, artifactAddExp.new_level, artifactAddExp.stone_id, artifactAddExp.stone_count, artifactAddExp.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogArtifactAddMaxLevel(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogArtifactAddMaxLevel artifactAddMaxLevel = {};
	artifactAddMaxLevel.cid = inPacket->readInt64();
	snprintf(artifactAddMaxLevel.name, sizeof(artifactAddMaxLevel.name)-1, inPacket->readUTF8(true).c_str());
	artifactAddMaxLevel.itemid = inPacket->readInt32();
	artifactAddMaxLevel.baseid = inPacket->readInt32();
	artifactAddMaxLevel.old_max_level = inPacket->readInt32();
	artifactAddMaxLevel.new_max_level = inPacket->readInt32();
	artifactAddMaxLevel.stone_id = inPacket->readInt32();
	artifactAddMaxLevel.stone_count = inPacket->readInt32();
	artifactAddMaxLevel.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_artifact_add_max_level` (`cid`, `name`, `itemid`, `baseid`, `old_max_level`, `new_max_level`, `stone_id`, `stone_count`, `time`) VALUES (%lld, '%s', %d, %d, %d, %d, %d, %d, %d)",
		artifactAddMaxLevel.cid, artifactAddMaxLevel.name, artifactAddMaxLevel.itemid, artifactAddMaxLevel.baseid, artifactAddMaxLevel.old_max_level, artifactAddMaxLevel.new_max_level, artifactAddMaxLevel.stone_id, artifactAddMaxLevel.stone_count, artifactAddMaxLevel.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}


void DBServer::onDBInsertItemChange(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogItemChange item = {};
	item.cid		= inPacket->readInt64();
	snprintf(item.name, sizeof(item.name)-1, inPacket->readUTF8(true).c_str());
	item.flag		= inPacket->readInt8();
	item.reason		= inPacket->readInt32();
	item.id			= inPacket->readInt32();
	item.itemClass	= inPacket->readInt8();
	item.count		= inPacket->readInt32();
	item.time		= inPacket->readInt32();
	item.srcId		= inPacket->readInt64();

	//MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_item_change` (`cid`, `name`,`flag`,`reason`,`id`,`class`,`count`,`time`,`srcid`) VALUES (%lld,'%s',%d,%d,%d,%d,%d,%d,%lld)",
		item.cid, item.name,item.flag,item.reason,item.id,item.itemClass,item.count,item.time,item.srcId);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogArtifactAddQuality(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogArtifactAddQuality artifactAddQuality = {};
	artifactAddQuality.cid = inPacket->readInt64();
	snprintf(artifactAddQuality.name, sizeof(artifactAddQuality.name)-1, inPacket->readUTF8(true).c_str());
	artifactAddQuality.itemid = inPacket->readInt32();
	artifactAddQuality.baseid = inPacket->readInt32();
	artifactAddQuality.old_quality = inPacket->readInt32();
	artifactAddQuality.new_quality = inPacket->readInt32();
	artifactAddQuality.stone_id = inPacket->readInt32();
	artifactAddQuality.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_artifact_add_quality` (`cid`, `name`, `itemid`, `baseid`, `old_quality`, `new_quality`, `stone_id`, `time`) VALUES ('%lld', '%s', %d, %d, %d, %d, %d, %d)",
		artifactAddQuality.cid, artifactAddQuality.name, artifactAddQuality.itemid, artifactAddQuality.baseid, artifactAddQuality.old_quality, artifactAddQuality.new_quality, artifactAddQuality.stone_id, artifactAddQuality.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertEquipAddGem(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipAddGem equipAddGem = {};
	equipAddGem.cid = inPacket->readInt64();
	snprintf(equipAddGem.name, sizeof(equipAddGem.name)-1, inPacket->readUTF8(true).c_str());
	snprintf(equipAddGem.equip_name, sizeof(equipAddGem.equip_name)-1, inPacket->readUTF8(true).c_str());

	equipAddGem.equip_quality = inPacket->readInt32();
	snprintf(equipAddGem.gem_name, sizeof(equipAddGem.gem_name)-1, inPacket->readUTF8(true).c_str());
	equipAddGem.gem_level = inPacket->readInt32();
	equipAddGem.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_add_gem` (`cid`, `name`, `equip_name`, `equip_quality`, `gem_name`, `gem_level`, `time`) VALUES (%lld,'%s','%s',%d,'%s',%d,%d)",
			 equipAddGem.cid, equipAddGem.name, equipAddGem.equip_name, equipAddGem.equip_quality, equipAddGem.gem_name, equipAddGem.gem_level, equipAddGem.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertItemCombine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogItemCombine itemCombine = {};
	itemCombine.cid = inPacket->readInt64();
	snprintf(itemCombine.name, sizeof(itemCombine.name)-1, inPacket->readUTF8(true).c_str());
	itemCombine.old_item_id = inPacket->readInt32();
	itemCombine.old_item_num = inPacket->readInt32();
	itemCombine.new_item_id = inPacket->readInt32();
	itemCombine.new_item_num = inPacket->readInt32();
	itemCombine.money_cost = inPacket->readInt32();
	itemCombine.sys_gold_cost = inPacket->readInt32();
	itemCombine.gold_cost = inPacket->readInt32();
	itemCombine.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_item_combine` (`cid`, `name`, `old_item_id`, `old_item_num`, `new_item_id`, `new_item_num`, `money_cost`, `sys_gold_cost`, `gold_cost`, `time`) VALUES (%lld, '%s', %d, %d, %d, %d, %d, %d, %d, %d)",
		itemCombine.cid, itemCombine.name, itemCombine.old_item_id, itemCombine.old_item_num, itemCombine.new_item_id, itemCombine.new_item_num, itemCombine.money_cost, itemCombine.sys_gold_cost, itemCombine.gold_cost ,itemCombine.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertEquipSmithing(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipSmithing smithing = {};
	smithing.cid = inPacket->readInt64();
	snprintf(smithing.name, sizeof(smithing.name)-1, inPacket->readUTF8(true).c_str());
	smithing.equip_id = inPacket->readInt64();
	smithing.old_base_id = inPacket->readInt32();
	smithing.new_base_id = inPacket->readInt32();
	smithing.equip_quality = inPacket->readInt32();
	smithing.blueprint_id = inPacket->readInt32();
	smithing.blueprint_quality = inPacket->readInt32();
	smithing.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_smithing` (`cid`, `name`, `equip_id`, `old_base_id`, `new_base_id`, `equip_quality`, `blueprint_id`, `blueprint_quality`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d, %d)",
		smithing.cid, smithing.name, smithing.equip_id, smithing.old_base_id, smithing.new_base_id, smithing.equip_quality, smithing.blueprint_id, smithing.blueprint_quality, smithing.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertEquipDismantle(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipDismantle equipDismantle = {};
	equipDismantle.cid = inPacket->readInt64();
	snprintf(equipDismantle.name, sizeof(equipDismantle.name)-1, inPacket->readUTF8(true).c_str());
	equipDismantle.equip_id = inPacket->readInt64();
	equipDismantle.base = inPacket->readInt32();
	equipDismantle.enhance = inPacket->readInt32();
	equipDismantle.item1_id = inPacket->readInt32();
	equipDismantle.item1_count = inPacket->readInt32();
	equipDismantle.item2_id = inPacket->readInt32();
	equipDismantle.item2_count = inPacket->readInt32();
	equipDismantle.item3_id = inPacket->readInt32();
	equipDismantle.item3_count = inPacket->readInt32();
	equipDismantle.item4_id = inPacket->readInt32();
	equipDismantle.item4_count = inPacket->readInt32();
	equipDismantle.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_dismantle` (`cid`, `name`, `equip_id`, `base`, `enhance`, `item1_id`, `item1_count`, `item2_id`, `item2_count`, `item3_id`, `item3_count`, `item4_id`, `item4_count`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
		equipDismantle.cid, equipDismantle.name, equipDismantle.equip_id, equipDismantle.base, equipDismantle.enhance, equipDismantle.item1_id, equipDismantle.item1_count, equipDismantle.item2_id, equipDismantle.item2_count, equipDismantle.item3_id, equipDismantle.item3_count, equipDismantle.item4_id, equipDismantle.item4_count, equipDismantle.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertDungeon(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogDungeon dungeon = {};
	dungeon.cid = inPacket->readInt64();
	dungeon.did = inPacket->readInt32();
	dungeon.type = inPacket->readInt32();
	dungeon.level = inPacket->readInt32();
	dungeon.start_time = inPacket->readInt32();
	
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, 
		"INSERT INTO `log_dungeon` (`cid`,`did`,`type`,`level`,`start_time`) VALUES (%lld,%d,%d,%d,%d)",
		dungeon.cid, dungeon.did, dungeon.type, dungeon.level, dungeon.start_time );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertFamilyCreate(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogFamily familyCreate = {};
	familyCreate.cid = inPacket->readInt64();
	snprintf(familyCreate.name, sizeof(familyCreate.name)-1, inPacket->readUTF8(true).c_str());
	snprintf(familyCreate.family_name, sizeof(familyCreate.family_name)-1, inPacket->readUTF8(true).c_str());
	familyCreate.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_family_create` (`cid`, `name`,`family_name`, `create_time`) VALUES (%lld,'%s','%s',%d)",
		familyCreate.cid, familyCreate.name,familyCreate.family_name, familyCreate.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertFamilyJoin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogFamily familyCreate = {};
	familyCreate.cid = inPacket->readInt64();
	snprintf(familyCreate.name, sizeof(familyCreate.name)-1, inPacket->readUTF8(true).c_str());
	snprintf(familyCreate.family_name, sizeof(familyCreate.family_name)-1, inPacket->readUTF8(true).c_str());
	familyCreate.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_family_number` (`cid`, `name`,`family_name`, `join_time`) VALUES (%lld,'%s','%s',%d)",
		familyCreate.cid, familyCreate.name,familyCreate.family_name, familyCreate.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBUpdateFamilyOut(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogFamily familyCreate = {};
	familyCreate.cid = inPacket->readInt64();
	snprintf(familyCreate.name, sizeof(familyCreate.name)-1, inPacket->readUTF8(true).c_str());
	snprintf(familyCreate.family_name, sizeof(familyCreate.family_name)-1, inPacket->readUTF8(true).c_str());
	familyCreate.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `log_family_number` SET `out_time`=%d  WHERE `cid`=%lld AND `family_name` = '%s'",
		familyCreate.time, familyCreate.cid,familyCreate.family_name);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBInsertAchievement(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogAchievement achievement = {};
	achievement.cid = inPacket->readInt64();
	snprintf(achievement.name, sizeof(achievement.name)-1, inPacket->readUTF8(true).c_str());

	achievement.id = inPacket->readInt32();
	achievement.type = inPacket->readInt32();
	achievement.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_achievement` (`cid`, `name`,`id`, `type`,`time`) VALUES (%lld,'%s',%d,%d,%d)",
		achievement.cid, achievement.name,achievement.id,achievement.type, achievement.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBUpdateDungeon(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogDungeon dungeon = {};
	dungeon.cid = inPacket->readInt64();
	dungeon.did = inPacket->readInt32();
	dungeon.state = inPacket->readInt32();
	dungeon.start_time = inPacket->readInt32();
	dungeon.finish_time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, 
		"UPDATE `log_dungeon` SET `state`=%d ,`finish_time`=%d WHERE `cid`=%lld AND `did`=%d AND `start_time`=%d AND `state` = 0", 
		dungeon.state, dungeon.finish_time, dungeon.cid, dungeon.did, dungeon.start_time );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogKillBoss(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogBoss boss = {};
	boss.mid = inPacket->readInt32();
	boss.type = inPacket->readInt32();
	boss.killer = inPacket->readInt64();
	boss.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, 
		"INSERT INTO `log_boss` (`mid`,`type`,`killer`, `time`) VALUES (%d,%d,%lld,%d)",
		boss.mid, boss.type, boss.killer, boss.time );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipAddGemSlot(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipAddGemSlot equipAddGemSlot = {};
	equipAddGemSlot.cid = inPacket->readInt64();
	snprintf(equipAddGemSlot.name, sizeof(equipAddGemSlot)-1, inPacket->readUTF8(true).c_str());
	equipAddGemSlot.eid = inPacket->readInt64();
	equipAddGemSlot.baseid = inPacket->readInt32();
	equipAddGemSlot.old_gem_slot_num = inPacket->readInt32();
	equipAddGemSlot.new_gem_slot_num = inPacket->readInt32();
	equipAddGemSlot.stone_id = inPacket->readInt32();
	equipAddGemSlot.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_add_gem_slot` (`cid`, `name`, `eid`, `baseid`, `old_gem_slot_num`, `new_gem_slot_num`, `stone_id`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d)",
			 equipAddGemSlot.cid, equipAddGemSlot.name, equipAddGemSlot.eid, equipAddGemSlot.baseid, equipAddGemSlot.old_gem_slot_num, equipAddGemSlot.new_gem_slot_num, equipAddGemSlot.stone_id, equipAddGemSlot.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipAppendStar(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipAppendStar equipAppendStar = {};
	equipAppendStar.cid = inPacket->readInt64();
	snprintf(equipAppendStar.name, sizeof(equipAppendStar)-1, inPacket->readUTF8(true).c_str());
	equipAppendStar.eid = inPacket->readInt64();
	equipAppendStar.baseid = inPacket->readInt32();
	equipAppendStar.level = inPacket->readInt32();
	equipAppendStar.fuxing_stone_id = inPacket->readInt32();
	equipAppendStar.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_append_star` (`cid`, `name`, `eid`, `baseid`, `level`, `fuxing_stone_id`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d)",
			 equipAppendStar.cid, equipAppendStar.name, equipAppendStar.eid, equipAppendStar.baseid, equipAppendStar.level, equipAppendStar.fuxing_stone_id, equipAppendStar.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipCombine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipCombine equipCombine = {};
	equipCombine.cid = inPacket->readInt64();
	snprintf(equipCombine.name, sizeof(equipCombine.name), inPacket->readUTF8(true).c_str());
	equipCombine.eid = inPacket->readInt64();
	equipCombine.baseid = inPacket->readInt32();
	equipCombine.new_baseid = inPacket->readInt32();
	equipCombine.side_equip_1 = inPacket->readInt32();
	equipCombine.side_equip_2 = inPacket->readInt32();
	equipCombine.side_equip_3 = inPacket->readInt32();
	equipCombine.side_equip_4 = inPacket->readInt32();
	equipCombine.shouhu_stone_id = inPacket->readInt32();
	equipCombine.money = inPacket->readInt32();
	equipCombine.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_combine` (`cid`, `name`, `eid`, `baseid`, `new_baseid`, `side_equip_1`, `side_equip_2`, `side_equip_3`, `side_equip_4`, `shouhu_stone_id`, `money`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
			 equipCombine.cid, equipCombine.name, equipCombine.eid, equipCombine.baseid, equipCombine.new_baseid, equipCombine.side_equip_1, equipCombine.side_equip_2, equipCombine.side_equip_3, equipCombine.side_equip_4, equipCombine.shouhu_stone_id, equipCombine.money, equipCombine.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}


void DBServer::onDBLogEquipForge(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipForge equipForge= {};
	equipForge.cid = inPacket->readInt64();
	snprintf(equipForge.name, sizeof(equipForge.name)-1, inPacket->readUTF8(true).c_str());
	equipForge.eid = inPacket->readInt64();
	equipForge.baseid = inPacket->readInt32();
	equipForge.item_id = inPacket->readInt32();
	equipForge.money = inPacket->readInt32();
	equipForge.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_forge` (`cid`, `name`, `eid`, `baseid`, `item_id`, `money`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d)",
			 equipForge.cid, equipForge.name, equipForge.eid, equipForge.baseid, equipForge.item_id, equipForge.money, equipForge.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipLife(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipLife equipLife = {};
	equipLife.cid = inPacket->readInt64();
	snprintf(equipLife.name, sizeof(equipLife.name)-1, inPacket->readUTF8(true).c_str());
	equipLife.eid = inPacket->readInt64();
	equipLife.baseid = inPacket->readInt32();
	equipLife.type = inPacket->readInt32();
	equipLife.reason = inPacket->readInt32();
	equipLife.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_life` (`cid`, `name`, `eid`, `baseid`, `type`, `reason`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d)",
			 equipLife.cid, equipLife.name, equipLife.eid, equipLife.baseid, equipLife.type, equipLife.reason, equipLife.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipRefreshBind(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipRefreshBind equipRefreshBind = {};
	equipRefreshBind.cid = inPacket->readInt64();
	snprintf(equipRefreshBind.name, sizeof(equipRefreshBind.name)-1, inPacket->readUTF8(true).c_str());
	equipRefreshBind.eid = inPacket->readInt64();
	equipRefreshBind.baseid = inPacket->readInt32();
	equipRefreshBind.old_bind = inPacket->readInt32();
	equipRefreshBind.new_bind = inPacket->readInt32();
	equipRefreshBind.stone_id = inPacket->readInt32();
	equipRefreshBind.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_refresh_bind` (`cid`, `name`, `eid`, `baseid`, `old_bind`, `new_bind`, `stone_id`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d)",
		equipRefreshBind.cid, equipRefreshBind.name, equipRefreshBind.eid, equipRefreshBind.baseid, equipRefreshBind.old_bind, equipRefreshBind.new_bind, equipRefreshBind.stone_id, equipRefreshBind.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipRefreshElement(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipRefreshElement equipRefreshElement = {};
	equipRefreshElement.cid = inPacket->readInt64();
	snprintf(equipRefreshElement.name, sizeof(equipRefreshElement.name)-1, inPacket->readUTF8(true).c_str());
	equipRefreshElement.eid = inPacket->readInt64();
	equipRefreshElement.baseid = inPacket->readInt32();
	equipRefreshElement.old_element = inPacket->readInt32();
	equipRefreshElement.new_element = inPacket->readInt32();
	equipRefreshElement.stone_id = inPacket->readInt32();
	equipRefreshElement.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_refresh_element` (`cid`, `name`, `eid`, `baseid`, `old_element`, `new_element`, `stone_id`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d)",
		equipRefreshElement.cid, equipRefreshElement.name, equipRefreshElement.eid, equipRefreshElement.baseid, equipRefreshElement.old_element, equipRefreshElement.new_element, equipRefreshElement.stone_id, equipRefreshElement.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipRefreshFloatAttr(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipRefreshFloatAttr equipRefreshFloatAttr = {};
	equipRefreshFloatAttr.cid = inPacket->readInt64();
	snprintf(equipRefreshFloatAttr.name, sizeof(equipRefreshFloatAttr.name)-1, inPacket->readUTF8(true).c_str());
	equipRefreshFloatAttr.eid = inPacket->readInt64();
	equipRefreshFloatAttr.baseid = inPacket->readInt32();
	equipRefreshFloatAttr.old_float_attr = inPacket->readInt32();
	equipRefreshFloatAttr.new_float_attr = inPacket->readInt32();
	equipRefreshFloatAttr.stone_id = inPacket->readInt32();
	equipRefreshFloatAttr.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_refresh_float_attr` (`cid`, `name`, `eid`, `baseid`, `old_float_attr`, `new_float_attr`, `stone_id`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d)",
		equipRefreshFloatAttr.cid, equipRefreshFloatAttr.name, equipRefreshFloatAttr.eid, equipRefreshFloatAttr.baseid, equipRefreshFloatAttr.old_float_attr, equipRefreshFloatAttr.new_float_attr, equipRefreshFloatAttr.stone_id, equipRefreshFloatAttr.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipRemoveGem(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipRemoveGem equipRemoveGem = {};
	equipRemoveGem.cid = inPacket->readInt64();
	snprintf(equipRemoveGem.name, sizeof(equipRemoveGem.name)-1, inPacket->readUTF8(true).c_str());
	equipRemoveGem.eid = inPacket->readInt64();
	equipRemoveGem.baseid = inPacket->readInt32();
	equipRemoveGem.slot_index = inPacket->readInt32();
	equipRemoveGem.stone_id = inPacket->readInt32();
	equipRemoveGem.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_remove_gem` (`cid`, `name`, `eid`, `baseid`, `slot_index`, `stoneid`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d)",
		equipRemoveGem.cid, equipRemoveGem.name, equipRemoveGem.eid, equipRemoveGem.baseid, equipRemoveGem.slot_index, equipRemoveGem.stone_id,  equipRemoveGem.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipRemoveStar(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipRemoveStar equipRemoveStar = {};
	equipRemoveStar.cid = inPacket->readInt64();
	snprintf(equipRemoveStar.name, sizeof(equipRemoveStar)-1, inPacket->readUTF8(true).c_str());
	equipRemoveStar.eid = inPacket->readInt64();
	equipRemoveStar.baseid = inPacket->readInt32();
	equipRemoveStar.level = inPacket->readInt32();
	equipRemoveStar.fuxing_stone_id = inPacket->readInt32();
	equipRemoveStar.shouhu_stone_id = inPacket->readInt32();
	equipRemoveStar.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_remove_star` (`cid`, `name`, `eid`, `baseid`, `level`, `fuxing_stone_id`, `shouhu_stone_id`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d)",
			 equipRemoveStar.cid, equipRemoveStar.name, equipRemoveStar.eid, equipRemoveStar.baseid, equipRemoveStar.level, equipRemoveStar.fuxing_stone_id, equipRemoveStar.shouhu_stone_id, equipRemoveStar.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipStrengthen(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipStrengthen equipStrengthen = {};
	equipStrengthen.cid = inPacket->readInt64();
	snprintf(equipStrengthen.name, sizeof(equipStrengthen)-1, inPacket->readUTF8(true).c_str());
	equipStrengthen.eid = inPacket->readInt64();
	equipStrengthen.baseid = inPacket->readInt32();
	equipStrengthen.old_strength = inPacket->readInt32();
	equipStrengthen.new_strength = inPacket->readInt32();
	equipStrengthen.stone_id = inPacket->readInt32();
	equipStrengthen.stone_count = inPacket->readInt32();
	equipStrengthen.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_strengthen` (`cid`, `name`, `eid`, `baseid`, `old_strength`, `new_strength`, `stone_id`, `count`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d, %d)",
		equipStrengthen.cid, equipStrengthen.name, equipStrengthen.eid, equipStrengthen.baseid, equipStrengthen.old_strength, equipStrengthen.new_strength, equipStrengthen.stone_id, equipStrengthen.stone_count, equipStrengthen.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogEquipUpgrade(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	LogEquipUpgrade equipUpgrade = {};
	equipUpgrade.cid = inPacket->readInt64();
	snprintf(equipUpgrade.name, sizeof(equipUpgrade.name)-1, inPacket->readUTF8(true).c_str());
	equipUpgrade.eid = inPacket->readInt64();
	equipUpgrade.baseid = inPacket->readInt32();
	equipUpgrade.new_baseid = inPacket->readInt32();
	equipUpgrade.upgrade_stone_id = inPacket->readInt32();
	equipUpgrade.upgrade_stone_count = inPacket->readInt32();
	equipUpgrade.crystal_stone_id = inPacket->readInt32();
	equipUpgrade.zhenxing_stone_id = inPacket->readInt32();
	equipUpgrade.money = inPacket->readInt32();
	equipUpgrade.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_equip_upgrade` (`cid`, `name`, `eid`, `baseid`, `new_baseid`, `upgrade_stone_id`, `upgrade_stone_count`, `crystal_stone_id`, `zhenxing_stone_id`, `money`, `time`) VALUES (%lld, '%s', %lld, %d, %d, %d, %d, %d, %d, %d, %d)",
			 equipUpgrade.cid, equipUpgrade.name, equipUpgrade.eid, equipUpgrade.baseid, equipUpgrade.new_baseid, equipUpgrade.upgrade_stone_id, equipUpgrade.upgrade_stone_count, equipUpgrade.crystal_stone_id, equipUpgrade.zhenxing_stone_id, equipUpgrade.money, equipUpgrade.time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogCurrency( Answer::TcpConnection *conn, Answer::NetPacket* inPacket )
{
	if ( NULL == conn || NULL == inPacket )
	{
		return;
	}
	if ( conn->getPtr() != conn )
	{
		return;
	}
	CharId_t	cid		= inPacket->readInt64();
	std::string name	= inPacket->readUTF8( true );
	int32_t		nType	= inPacket->readInt32();
	int32_t		opWay	= inPacket->readInt32();
	int32_t		nVal	= inPacket->readInt32();
	int64_t		nParam	= inPacket->readInt64();
	int32_t		nTime	= inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `log_currency` (`cid`, `name`, `type`, `opway`, `value`, `param`, `time`) VALUES (%lld, '%s', %d, %d, %d, %lld, %d)",
		cid,
		name.c_str(),
		nType,
		opWay,
		nVal,
		nParam,
		nTime );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogActivityData(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}

	if (conn->getPtr() != conn)
	{
		return;
	}

	LogActivity activity={};
	activity.cid = inPacket->readInt64();
	activity.actid = inPacket->readInt32();
	activity.acttype = inPacket->readInt32();
	activity.time = inPacket->readInt32();
	activity.param = inPacket->readInt64();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `log_activity` (`cid`, `actid`, `acttype`, `time`, `param`) VALUES (%lld, %d, %d, %d, %lld)",
		activity.cid, activity.actid, activity.acttype, activity.time, activity.param );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogDailyGift(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}

	if (conn->getPtr() != conn)
	{
		return;
	}

	LogDailyGift gift={};
	gift.cid = inPacket->readInt64();
	gift.type = inPacket->readInt32();
	gift.giftid = inPacket->readInt32();
	gift.time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `log_daily_gift` (`cid`, `type`, `giftid`, `time`) VALUES (%lld, %d, %d, %d)",
		gift.cid, gift.type, gift.giftid, gift.time );
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBLogPlayerLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	CharId_t cid = inPacket->readInt64();
	int32_t action = inPacket->readInt32();
	int32_t time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};

	if (action == 0)
	{
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_player_login` (`cid`, `action`, `time`) VALUES (%lld, %d, %d)", cid, action, time);
		//MySqlDBGuard db(DBPOOL);
		//db.excute(szSQL);
		DB_SAVER.AddSqlString( szSQL );
	}
}

void DBServer::onDBLogPlayerDeal(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	CharId_t cid = inPacket->readInt64();
	char name[MAX_NAME_CCH_LENGTH+1] = {};
	snprintf(name, sizeof(name)-1, inPacket->readUTF8(true).c_str());
	CharId_t tcid = inPacket->readInt64();
	char tname[MAX_NAME_CCH_LENGTH+1] = {};
	snprintf(tname, sizeof(tname)-1, inPacket->readUTF8(true).c_str());
	int32_t reason = inPacket->readInt32();
	int32_t money = inPacket->readInt32();
	char szItems[MAX_SQL_LENGTH] = {};
	snprintf(szItems, sizeof(szItems)-1, inPacket->readUTF8(true).c_str());
	int32_t time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL), "INSERT INTO `log_player_deal` (`cid`, `name`, `tcid`, `tname`, `reason`, `money`, `items`, `time`) VALUES (%lld, '%s', %d, '%s', %d, %d, '%s', %d)", 
			 cid, name, tcid, tname, reason, money, szItems, time);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBUserPay(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	int32_t uid = inPacket->readInt32();
	int32_t sid = inPacket->readInt32();
	broadcastUserPayed(uid, sid, conn);
}

void DBServer::addConn(Answer::TcpConnection *conn)
{
	if (conn != NULL)
	{
		MutexGuard lock(m_connsLock);
		m_conns.push_back(conn);
	}
}

void DBServer::removeConn(Answer::TcpConnection *conn)
{
	if (conn != NULL)
	{
		MutexGuard lock(m_connsLock);
		m_conns.remove(conn);
	}
}

void DBServer::broadcastEquipUpdated(const MemEquip &equip, Answer::TcpConnection *except)
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if (conn != NULL && conn != except)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			packet->writeInt32(1);
			packet->writeInt64(equip.id);
			packet->writeInt32(equip.nFlag);
			packet->writeInt32(equip.base);
			packet->writeInt64(equip.owner);
			packet->writeInt32(equip.star);
			packet->writeInt32(equip.starLucky);
			packet->writeInt32(equip.addAttr);
			packet->writeInt32(equip.UpGradeLucky);
			packet->writeInt32(equip.UpQuality);
			packet->writeUTF8(equip.GetEquipGemString());
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_EQUIP_UPDATED);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}

void DBServer::broadcastEquipUpdated(const MemEquipVector &equips, Answer::TcpConnection *except)
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if (conn != NULL && conn != except)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			packet->writeInt32(static_cast<int32_t>(equips.size()));
			for (MemEquipVector::const_iterator itEquip = equips.begin(); itEquip != equips.end(); ++itEquip)
			{
				const MemEquip &equip = *itEquip;
				packet->writeInt64(equip.id);
				packet->writeInt32(equip.nFlag);
				packet->writeInt32(equip.base);
				packet->writeInt64(equip.owner);
				packet->writeInt32(equip.star);
				packet->writeInt32(equip.starLucky);
				packet->writeInt32(equip.addAttr);
				packet->writeInt32(equip.UpGradeLucky);
				packet->writeInt32(equip.UpQuality);
				packet->writeUTF8(equip.GetEquipGemString());
			}
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_EQUIP_UPDATED);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}

//void DBServer::broadcastFamilyWarUpdated(int32_t family_id, std::string family_name, Answer::TcpConnection *except)
//{
//	MutexGuard lock(m_connsLock);
//	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
//	{
//		TcpConnection *conn = *it;
//		if (conn != NULL && conn != except)
//		{
//			NetPacket *packet = popNetpacket();
//			if (NULL == packet)
//			{
//				continue;
//			}
//			packet->writeInt32(family_id);
//			packet->writeUTF8(family_name);
//			packet->setType(PACK_DISPATCH);
//			packet->setProc(IM_DB_FAMILY_WAR_UPDATED);
//			packet->setSize(packet->getWOffset());
//			conn->sendPacket(packet, true);
//		}
//	}
//}

void DBServer::broadcastUserPayed(int32_t uid, int32_t sid, Answer::TcpConnection *except)
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if (conn != NULL && conn != except)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			packet->writeInt32(uid);
			packet->writeInt32(sid);
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_USER_PAYED);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}

void DBServer::onDBInsertMemYellowStone(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}
	int16_t type = inPacket->readInt16();
	CharId_t cid = inPacket->readInt64();
	int32_t id = inPacket->readInt32();
	int32_t get_time = inPacket->readInt32();

	char szSQL[MAX_SQL_LENGTH] = {};
	//MySqlDBGuard db(DBPOOL);
	if (type == 1)
	{
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_yellow_stone` (`cid`,`id`,`get_time`) VALUES (%lld,%d, %d)",
			cid, id, get_time);
	}
	else if (type == 2)
	{
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_yellow_stone` (`cid`,`id`,`get_time`) VALUES (%lld,%d, %d)",
			cid, id, get_time);
	}
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
}

void DBServer::onDBAddRansom( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}
	DropEquipInfo DropEquip;
	DropEquip.CharId				= inPacket->readInt64();	
	DropEquip.CharName				= inPacket->readUTF8(true);
	DropEquip.KillerId				= inPacket->readInt64();
	DropEquip.KillerName			= inPacket->readUTF8(true);
	DropEquip.CanGetLastTime		= inPacket->readInt32();
	DropEquip.itemId				= inPacket->readInt32();
	DropEquip.itemClass				= inPacket->readInt8();
	DropEquip.itemCount				= inPacket->readInt32();
	DropEquip.bind					= inPacket->readInt8();
	DropEquip.endTime				= inPacket->readInt32();
	DropEquip.srcId					= inPacket->readInt64();
	DropEquip.Mid					= inPacket->readInt32();
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_char_ransom`(`CharId`,`CharName`,`KillerId`,`KillerName`,`CanGetLastTime`,`ItemId`,`ItemClass`,`ItemCount`,`Bind`,`EndTime`,`SrcId`,`Mid`) VALUES(%lld,'%s',%lld,'%s',%d,%d,%d,%d,%d,%d,%lld,%d)", 
		DropEquip.CharId,DropEquip.CharName.c_str(),DropEquip.KillerId,DropEquip.KillerName.c_str(),DropEquip.CanGetLastTime,DropEquip.itemId,DropEquip.itemClass,DropEquip.itemCount,DropEquip.bind,DropEquip.endTime,DropEquip.srcId,DropEquip.Mid);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );

	OnUpdateRansom( conn, DropEquip );
	
}

void DBServer::onDbDleRansom( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}

	EquipId_t eid = inPacket->readInt64();

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_char_ransom`  WHERE `SrcId`=%lld", eid);
	//MySqlDBGuard db(DBPOOL);
	//db.excute(szSQL);
	DB_SAVER.AddSqlString( szSQL );
	OnUpdateRansom(conn, eid );
}

void DBServer::OnUpdateRansom( Answer::TcpConnection *conn, EquipId_t EquipId )
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *ConTmp = *it;
		if (conn != NULL && ConTmp != conn)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			packet->writeInt8( SUB_RANSOM );
			packet->writeInt64( EquipId ); 
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_UPDATE_RANSOM);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}

void DBServer::OnUpdateRansom( Answer::TcpConnection *conn, DropEquipInfo& DropEquip )
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *ConTmp = *it;
		if (conn != NULL && ConTmp != conn)
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}
			packet->writeInt8( SUB_RANSOM );
			packet->writeInt64( DropEquip.CharId );	
			packet->writeUTF8( DropEquip.CharName	);
			packet->writeInt64( DropEquip.KillerId );
			packet->writeUTF8( DropEquip.KillerName );
			packet->writeInt32( DropEquip.CanGetLastTime );
			packet->writeInt32( DropEquip.itemId );
			packet->writeInt8( DropEquip.itemClass );
			packet->writeInt32( DropEquip.itemCount );
			packet->writeInt8( DropEquip.bind );		
			packet->writeInt32( DropEquip.endTime );
			packet->writeInt64( DropEquip.srcId	);
			packet->writeInt32( DropEquip.Mid );
			packet->setType(PACK_DISPATCH);
			packet->setProc(IM_DB_UPDATE_RANSOM);
			packet->setSize(packet->getWOffset());
			conn->sendPacket(packet, true);
		}
	}
}

void DBServer::onInsertMailToDB( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	if (conn->getPtr() != conn)
	{
		return;
	}
	MailInfo Mail = {};
	Mail.MailId			= inPacket->readInt32();
	Mail.SysMailId		= inPacket->readInt32();
	Mail.SenderId		= inPacket->readInt64();
	snprintf(Mail.SenderName, sizeof(Mail.SenderName)-1, inPacket->readUTF8(true).c_str());
	Mail.ReceiveId		= inPacket->readInt64();
	snprintf(Mail.ReceiveName, sizeof(Mail.ReceiveName)-1, inPacket->readUTF8(true).c_str());
	Mail.SendTime		= inPacket->readInt32();
	Mail.HasRead		= inPacket->readInt8();
	Mail.Extract		= inPacket->readInt8();
	snprintf(Mail.MailTitle, sizeof(Mail.MailTitle)-1, inPacket->readUTF8(true).c_str());
	snprintf(Mail.MailContent, sizeof(Mail.MailContent)-1, inPacket->readUTF8(true).c_str());
	Mail.Param			= inPacket->readUTF8(true);
	if ( Mail.Extract == 1 )
	{ 
		int8_t Count = inPacket->readInt8();
		if ( Count >= MAIL_MAX_FU_JIAN_COUNT )
		{
			return;
		}
		for ( int8_t i = 0; i < Count; ++i )
		{
			int8_t Index			= inPacket->readInt8();
			Mail.Item[Index].itemId		= inPacket->readInt32();
			Mail.Item[Index].itemClass	= inPacket->readInt8();
			Mail.Item[Index].itemCount	= inPacket->readInt32();
			Mail.Item[Index].bind		= inPacket->readInt8();
			Mail.Item[Index].endTime	= inPacket->readInt32();
			Mail.Item[Index].srcId		= inPacket->readInt64();
		}
	}
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_new_mail` (`SysMailId`,`SenderId`,`SenderName`,`ReceiveId`,`ReceiveName`,`SendTime`,`HasRead`,`Extract`,`MailTitle`,`MailContent`,`Item1`,`Item2`,`Item3`,`Item4`,`Item5`,`Item6`,`Param`) VALUES (%d,%lld,'%s',%lld,'%s',%d,%d,%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s')",
		//Mail.MailId,
		Mail.SysMailId,
		Mail.SenderId,
		Mail.SenderName,
		Mail.ReceiveId,
		Mail.ReceiveName,
		Mail.SendTime,
		Mail.HasRead,
		Mail.Extract,
		Mail.MailTitle,
		Mail.MailContent,
		GetItemString(Mail.Item[0]).c_str(),
		GetItemString(Mail.Item[1]).c_str(),
		GetItemString(Mail.Item[2]).c_str(),
		GetItemString(Mail.Item[3]).c_str(),
		GetItemString(Mail.Item[4]).c_str(),
		GetItemString(Mail.Item[5]).c_str(),
		Mail.Param.c_str());
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);
	//DB_SAVER.AddSqlString( szSQL );
	UpdateNewMail();
}
std::string DBServer::GetItemString( MemChrBag & Item )
{
	std::stringstream ss;
	if ( Item.itemId > 0 && Item.itemCount > 0 )
	{
		ss << Item.itemId << ":" << static_cast<int32_t>(Item.itemClass) << ":" << Item.itemCount << ":" << static_cast<int32_t>(Item.bind) << ":" << Item.endTime << ":" << Item.srcId;
	}
	return ss.str();
}

MemChrBag DBServer::ParesChrBagString( std::string ItemString )
{
	MemChrBag stu = {};
	if ( ItemString.empty() )
	{
		return stu;
	}
	StringVector ItemVector = Answer::StringUtility::split(ItemString, ":");
	if ( ItemVector.size() == 6 )
	{
		stu.itemId			= atoi(ItemVector[0].c_str());
		stu.itemClass		= (int8_t)atoi(ItemVector[1].c_str());
		stu.itemCount		= atoi(ItemVector[2].c_str());
		stu.bind			= (int8_t)atoi(ItemVector[3].c_str());
		stu.endTime			= atoi(ItemVector[4].c_str());
		stu.srcId			= _atoi64(ItemVector[5].c_str());
	}
	return stu;
}
void DBServer::UpdateNewMail()
{
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_new_mail`");
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query(szSQL);
	while( !result.eof() )
	{
		MailInfo Mail = {};
		Mail.MailId				= result.getIntValue("MailId");
		Mail.SysMailId			= result.getIntValue("SysMailId");
		Mail.SenderId			= result.getInt64Value("SenderId");
		snprintf(Mail.SenderName,MAX_NAME_CCH_LENGTH,result.getStringValue("SenderName"));
		Mail.ReceiveId			= result.getInt64Value("ReceiveId");
		snprintf(Mail.ReceiveName,MAX_NAME_CCH_LENGTH,result.getStringValue("ReceiveName"));
		Mail.SendTime			= result.getIntValue("SendTime");
		Mail.HasRead			= result.getIntValue("HasRead");
		Mail.Extract			= result.getIntValue("Extract");
		snprintf(Mail.MailTitle,MAIL_TITLE_MAX_LENGTH,result.getStringValue("MailTitle"));
		snprintf(Mail.MailContent,MAIL_CONTENT_MAX_LENGTH,result.getStringValue("MailContent"));
		Mail.Item[0]			= ParesChrBagString( result.getStringValue("Item1") );
		Mail.Item[1]			= ParesChrBagString( result.getStringValue("Item2") );
		Mail.Item[2]			= ParesChrBagString( result.getStringValue("Item3") );
		Mail.Item[3]			= ParesChrBagString( result.getStringValue("Item4") );
		Mail.Item[4]			= ParesChrBagString( result.getStringValue("Item5") );
		Mail.Item[5]			= ParesChrBagString( result.getStringValue("Item6") );
		Mail.Param				= result.getStringValue("Param");
		SendNewMailToGame( Mail );
		
		char szSQL[MAX_SQL_LENGTH] = "";
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_mail` (`MailId`,`SysMailId`,`SenderId`,`SenderName`,`ReceiveId`,`ReceiveName`,`SendTime`,`HasRead`,`Extract`,`MailTitle`,`MailContent`,`Item1`,`Item2`,`Item3`,`Item4`,`Item5`,`Item6`,`Param`) VALUES (%d,%d,%lld,'%s',%lld,'%s',%d,%d,%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s')",
			Mail.MailId,
			Mail.SysMailId,
			Mail.SenderId,
			Mail.SenderName,
			Mail.ReceiveId,
			Mail.ReceiveName,
			Mail.SendTime,
			Mail.HasRead,
			Mail.Extract,
			Mail.MailTitle,
			Mail.MailContent,
			GetItemString(Mail.Item[0]).c_str(),
			GetItemString(Mail.Item[1]).c_str(),
			GetItemString(Mail.Item[2]).c_str(),
			GetItemString(Mail.Item[3]).c_str(),
			GetItemString(Mail.Item[4]).c_str(),
			GetItemString(Mail.Item[5]).c_str(),
			Mail.Param.c_str());
		
		//db.excute(szSQL);
		DB_SAVER.AddSqlString( szSQL );
		char DeleteSql[MAX_SQL_LENGTH] = "";
		snprintf(DeleteSql, sizeof(DeleteSql)-1,"DELETE FROM `mem_new_mail` WHERE `MailId`=%d",Mail.MailId );
		db.excute(DeleteSql);
		result.nextRow();
	}
}

void DBServer::SendNewMailToGame( MailInfo& Mail )
{
	std::map<CharId_t,Answer::TcpConnection*>::iterator itTmp = m_PlayerConnection.find( Mail.ReceiveId );
	if ( itTmp != m_PlayerConnection.end() )
	{
		MutexGuard lock(m_connsLock);
		for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
		{
			TcpConnection *ConTmp = *it;
			if (ConTmp != NULL && ConTmp == itTmp->second )
			{
				NetPacket *packet = popNetpacket();
				if (NULL == packet)
				{
					return;
				}
				packet->writeInt64( itTmp->first );
				packet->writeInt32( Mail.MailId );
				packet->writeInt32( Mail.SysMailId );
				packet->writeInt64( Mail.SenderId );
				packet->writeUTF8( Mail.SenderName );
				packet->writeInt64( Mail.ReceiveId );
				packet->writeUTF8( Mail.ReceiveName );
				packet->writeInt32( Mail.SendTime );
				packet->writeInt8( Mail.HasRead );
				packet->writeInt8( Mail.Extract );
				packet->writeUTF8( Mail.MailTitle );
				packet->writeUTF8( Mail.MailContent );
				packet->writeUTF8( Mail.Param );
				if ( Mail.Extract == 1 )
				{ 
					int8_t Count = 0;
					int32_t Offset = packet->getWOffset();
					packet->writeInt8( Count );
					for ( int8_t i = 0; i < MAIL_MAX_FU_JIAN_COUNT; ++i )
					{
						if ( Mail.Item[i].itemId <= 0 || Mail.Item[i].itemCount <= 0 )
						{
							continue;
						}
						packet->writeInt8(i);
						packet->writeInt32( Mail.Item[i].itemId );
						packet->writeInt8( Mail.Item[i].itemClass );	
						packet->writeInt32( Mail.Item[i].itemCount );
						packet->writeInt8( Mail.Item[i].bind );	
						packet->writeInt32( Mail.Item[i].endTime );
						packet->writeInt64( Mail.Item[i].srcId );
						Count++;
					}
					*(int8_t*)( packet->getBuffer() + Offset ) =  Count;
				}
				packet->setType(PACK_DISPATCH);
				packet->setProc(IM_DB_UPDATE_NEW_MAIL);
				packet->setSize(packet->getWOffset());
				ConTmp->sendPacket(packet, true);
				break;
			}
		}
	}
}

void DBServer::onNewMinuteCome( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	UpdateNewMail();
	updateBroadcast();		// 更新公告
	updateBanChat();		// 更新禁言
	updateSeal();			// 更新封号
}

void DBServer::onSaveFamilyWarResult( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}

	if ( conn->getPtr() != conn )
	{
		return;
	}

	int32_t nActId		= inPacket->readInt32();
	FamilyId_t nFamilyId= inPacket->readInt64();
	int16_t nWinTimes	= inPacket->readInt16();
	int32_t nTime		= inPacket->readInt32();
	string  FamilyName  = inPacket->readUTF8( true );
	string  LeadyerName = inPacket->readUTF8( true );
	broadcastFamilyWarResult( nActId, nFamilyId, nTime, FamilyName, LeadyerName, conn );

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_family_war` (`familyid`, `wintimes`, `time`,`familyname`, `leadyername`) VALUES (%lld,%d,%d,'%s','%s')  ON DUPLICATE KEY UPDATE `familyid`=%lld, `wintimes`=%d, `familyname`='%s', `leadyername`='%s'", 
		nFamilyId, nWinTimes, nTime,FamilyName.c_str(), LeadyerName.c_str(), nFamilyId, nWinTimes, FamilyName.c_str(), LeadyerName.c_str() );
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);
}

void DBServer::broadcastFamilyWarResult( int32_t nActId, FamilyId_t nFamilyId, int16_t nWinTimes,string FamilyName, string LeadyerName, Answer::TcpConnection *except )
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if ( conn != NULL && conn != except )
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}

			packet->writeInt32( nActId );
			packet->writeInt64( nFamilyId );
			packet->writeInt16( nWinTimes );
			packet->writeUTF8( FamilyName );
			packet->writeUTF8( LeadyerName );
			packet->setType( PACK_DISPATCH );
			packet->setProc( IM_DB_UPDATE_FAMILY_WAR_RESULT );
			packet->setSize( packet->getWOffset() );
			conn->sendPacket( packet, true );
		}
	}
}

void DBServer::onSaveTerritoryWarResult( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}

	if ( conn->getPtr() != conn )
	{
		return;
	}

	int32_t nActId		= inPacket->readInt32();
	int32_t nTime		= inPacket->readInt32();
	string  winners		= inPacket->readUTF8( true );
	broadcastTerritoryWarResult( nActId, winners, conn );

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "INSERT INTO `mem_territory_war` (`actid`,`time`,`winners`) VALUES (%d,%d,'%s') ON DUPLICATE KEY UPDATE `winners`='%s'", nActId, nTime, winners.c_str(), winners.c_str() );
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);
}

void DBServer::broadcastTerritoryWarResult( int32_t nActId, string winners, Answer::TcpConnection *except )
{
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if ( conn != NULL && conn != except )
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}

			packet->writeInt32( nActId );
			packet->writeUTF8( winners );
			packet->setType( PACK_DISPATCH );
			packet->setProc( IM_DB_UPDATE_TERRITORY_WAR_RESULT );
			packet->setSize( packet->getWOffset() );
			conn->sendPacket( packet, true );
		}
	}
}

void DBServer::updateBroadcast()		// 更新公告
{
	GMBroadcastList broadcasts;

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `gmt_broadcast` WHERE `flag`=0");
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query(szSQL);
	while( !result.eof() )
	{
		int32_t nId			= result.getIntValue("idx");
		std::string strText	= result.getStringValue("text");
		int8_t	nType		= result.getIntValue("type");
		int32_t nStartTime	= result.getIntValue("start_time");
		int32_t nInterval	= result.getIntValue("interval");
		int32_t nTimes		= result.getIntValue("times");

		broadcasts.push_back( GMBroadcast( nId, strText, nType, nStartTime, nInterval, nTimes ) );

		bzero( szSQL, sizeof( szSQL ) );
		snprintf( szSQL, sizeof( szSQL )-1, "UPDATE `gmt_broadcast` SET `flag`=1 WHERE `idx`=%d", nId );
		db.excute( szSQL );
		result.nextRow();
	}

	sendGameBroadcasts( broadcasts );
}

void DBServer::updateBanChat()		// 更新禁言
{
	GMBanChatList banchat;

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `gmt_ban_chat` WHERE `flag`=0");
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query(szSQL);
	while( !result.eof() )
	{
		GMBanChat chat = {};
		chat.nCharId		= result.getInt64Value("cid");
		chat.nExpireTime	= result.getIntValue("expire_time");

		banchat.push_back( chat );

		bzero( szSQL, sizeof( szSQL ) );
		snprintf( szSQL, sizeof( szSQL )-1, "UPDATE `gmt_ban_chat` SET `flag`=1 WHERE `cid`=%lld", chat.nCharId );
		db.excute( szSQL );
		result.nextRow();
	}

	sendGameBanChat( banchat );
}

void DBServer::updateSeal()			// 更新封号
{
	GMSealList seals;

	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `gmt_seal` WHERE `flag`=0");
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query(szSQL);
	while( !result.eof() )
	{
		GMSeal seal = {};
		seal.nCharId		= result.getInt64Value("cid");
		seal.nExpireTime	= result.getIntValue("expire_time");

		seals.push_back( seal );

		bzero( szSQL, sizeof( szSQL ) );
		snprintf( szSQL, sizeof( szSQL )-1, "UPDATE `gmt_seal` SET `flag`=1 WHERE `cid`=%lld", seal.nCharId );
		db.excute( szSQL );
		result.nextRow();
	}

	sendGameSeal( seals );
}

void DBServer::sendGameBroadcasts( const GMBroadcastList& broadcasts )
{
	if ( broadcasts.empty() )
	{
		return;
	}
	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if ( conn != NULL )
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}

			packet->writeInt32( broadcasts.size() );
			for ( GMBroadcastList::const_iterator iter = broadcasts.begin(); iter != broadcasts.end(); ++iter )
			{
				packet->writeInt32( iter->nId );
				packet->writeUTF8( iter->strText );
				packet->writeInt8( iter->nType );
				packet->writeInt32( iter->nStartTime );
				packet->writeInt32( iter->nInterval );
				packet->writeInt32( iter->nTimes );

				packet->setType( PACK_DISPATCH );
				packet->setProc( IM_DB_UPDATE_GM_BROADCAST );
				packet->setSize( packet->getWOffset() );
				conn->sendPacket( packet, true );
			}
		}
	}
}

void DBServer::sendGameBanChat( const GMBanChatList& banchat )
{
	if ( banchat.empty() )
	{
		return;
	}

	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if ( conn != NULL )
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}

			packet->writeInt32( banchat.size() );
			for ( GMBanChatList::const_iterator iter = banchat.begin(); iter != banchat.end(); ++iter )
			{
				packet->writeInt64( iter->nCharId );
				packet->writeInt32( iter->nExpireTime );

				packet->setType( PACK_DISPATCH );
				packet->setProc( IM_DB_UPDATE_GM_BAN_CHAT );
				packet->setSize( packet->getWOffset() );
				conn->sendPacket( packet, true );
			}
		}
	}
}

void DBServer::sendGameSeal( const GMSealList& seals )
{
	if ( seals.empty() )
	{
		return;
	}

	MutexGuard lock(m_connsLock);
	for (TcpConnectionList::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		TcpConnection *conn = *it;
		if ( conn != NULL )
		{
			NetPacket *packet = popNetpacket();
			if (NULL == packet)
			{
				continue;
			}

			packet->writeInt32( seals.size() );
			for ( GMSealList::const_iterator iter = seals.begin(); iter != seals.end(); ++iter )
			{
				packet->writeInt64( iter->nCharId );
				packet->writeInt32( iter->nExpireTime );

				packet->setType( PACK_DISPATCH );
				packet->setProc( IM_DB_UPDATE_GM_SEAL );
				packet->setSize( packet->getWOffset() );
				conn->sendPacket( packet, true );
			}
		}
	}
}
