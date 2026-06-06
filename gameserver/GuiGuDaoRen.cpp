#include "GuiGuDaoRen.h"
#include "GameService.h"
#include "Player.h"
#include "Bag.h"
#include "Monster.h"
#include "Map.h"
#include "MapManager.h"
#include "PoolManager.h"
#include "Timer.h"
#include "DBService.h"

#include <cstdio>

using namespace Answer;

CGuiGuDaoRen::CGuiGuDaoRen()
	: m_CostCount(0)
	, m_GetCount(0)
	, m_Rate(0)
	, EquipCount(0)
{
}

CGuiGuDaoRen::~CGuiGuDaoRen()
{
}

// ==================== 物品回收 ====================

int32_t CGuiGuDaoRen::OnAskBackItemCount( Player* pPlayer, Answer::NetPacket* packet )
{
	if ( NULL == packet || NULL == pPlayer )
	{
		return 10002;
	}
	int32_t NpcId = packet->readInt32();
	SendBackItemCount( pPlayer, NpcId );
	return 0;
}

int32_t CGuiGuDaoRen::OnBackItem( Player* pPlayer, Answer::NetPacket* packet )
{
	if ( NULL == packet || NULL == pPlayer )
	{
		return 10002;
	}

	int32_t nNpcId = packet->readInt32();
	int8_t Id = packet->readInt8();
	if ( Id <= 0 || Id > 3 )
	{
		return 10002;
	}

	const GuiGuDaoRenCfg* pCfg = CFG_DATA.GetGuiGuDaoRenCfg( nNpcId );
	if ( NULL == pCfg )
	{
		return 10002;
	}

	CExtCharBag& pBag = pPlayer->GetBag();
	if ( pBag.GetFreeSlotCount() <= 0 )
	{
		return 10002;
	}

	// 检查并扣除消耗物品
	if ( (uint32_t)Id > pCfg->vItemData.size() )
	{
		return 10002;
	}
	const ItemData& costItem = pCfg->vItemData[Id - 1];
	if ( !pBag.RemoveItem( costItem, IDCR_GUI_GU_DAO_REN ) )
	{
		return 10002;
	}

	// 发放奖励物品
	if ( (uint32_t)Id > pCfg->vItem.size() )
	{
		return 10002;
	}
	const MemChrBag& rewardItem = pCfg->vItem[Id - 1];
	if ( !pBag.AddItem( rewardItem, IACR_GUI_GU_DAO_REN ) )
	{
		return 10002;
	}

	// BOSS 刷新判断
	int32_t AddItemCount = costItem.m_nCount;
	for ( std::list<int32_t>::const_iterator it = pCfg->lRefreshMonster.begin(); it != pCfg->lRefreshMonster.end(); ++it )
	{
		int32_t currentCount = BackItemCount[nNpcId];
		if ( currentCount < (*it) && (currentCount + AddItemCount) >= (*it) )
		{
			const CfgMonster* pMonsterCfg = CFG_DATA.getMonster( (*it) );
			if ( pMonsterCfg != NULL && pMonsterCfg->boss_sign == 11 )
			{
				// 随机选择地图并获取可行走位置
				int32_t MapIdCount = (int32_t)pCfg->vMapId.size();
				if ( MapIdCount > 0 )
				{
					int32_t nRand = RANDOM.generate( 0, MapIdCount - 1 );
					int32_t nMapId = pCfg->vMapId[nRand];

					Position pos = TILE_MANAGER.getRandomWalkablePosition( nMapId );
					if ( pos.x != -1 && pos.y != -1 )
					{
						Map* pMap = MAP_MANAGER.GetMap( nMapId );
						if ( pMap != NULL )
						{
							Monster* monster = POOL_MANAGER.pop<Monster>();
							if ( monster != NULL )
							{
								CfgMapMonster mapMonster = {};
								mapMonster.id = 0;
								mapMonster.mapid = nMapId;
								mapMonster.monsterid = pMonsterCfg->mid;
								mapMonster.x = pos.x;
								mapMonster.y = pos.y;

								monster->init( *pMonsterCfg, mapMonster, NULL );

								// 设置BOSS生存时间
								int32_t nAliveTime = 1800; // 默认1800秒（30分钟）
								monster->SetLifeTime( Answer::DayTime::now() + nAliveTime );
								pMap->addMonster( monster, pos.x, pos.y );
							}
						}
					}
				}
			}
		}
	}

	// 更新计数
	BackItemCount[nNpcId] += AddItemCount;
	if ( BackItemCount[nNpcId] >= pCfg->nMaxCount )
	{
		BackItemCount[nNpcId] -= pCfg->nMaxCount;
	}

	UpdateBackItemCount( nNpcId );
	SendBackItemCount( pPlayer, nNpcId );
	return 0;
}

void CGuiGuDaoRen::SendBackItemCount( Player* pPlayer, int32_t NpcId )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	std::map<int32_t, int32_t>::iterator it = BackItemCount.find( NpcId );
	if ( it == BackItemCount.end() )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_GUI_GU_DAO_REN_ITEM_COUNT );
	if ( packet )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
	}
}

void CGuiGuDaoRen::UpdateBackItemCount( int32_t NpcId )
{
	// DB:保存物品回收计数到数据库
	// 解构代码中调用: DBService::SaveGuiGuDaoRenData(v4, NpcId, BackItemCount[NpcId])
	// 该方法需要在 DBService.h 中声明并在 dbserver 端实现协议处理
	// 暂时保留为空方法，等待 DBService 升级后实现
}

// ==================== 装备回收 ====================

int32_t CGuiGuDaoRen::OnAskBackEquipCount( Player* pPlayer, Answer::NetPacket* packet )
{
	SendBackEquipCount( pPlayer );
	return 0;
}

int32_t CGuiGuDaoRen::OnBackEquipCount( Player* pPlayer, Answer::NetPacket* packet )
{
	if ( NULL == pPlayer || NULL == packet )
	{
		return 10002;
	}

	int32_t MaxCount = GetMaxCount();
	if ( MaxCount <= 0 )
	{
		return 10002;
	}

	// 读取客户端发送的装备槽位列表
	Int32Vector vSlot;
	int32_t nCount = packet->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int32_t nSlotId = packet->readInt32();

		// 检查是否重复
		if ( std::find( vSlot.begin(), vSlot.end(), nSlotId ) != vSlot.end() )
		{
			return 10002;
		}
		vSlot.push_back( nSlotId );

		// 验证装备品质
		CExtCharBag& pBag = pPlayer->GetBag();
		MemChrBag bagSlot = pBag.GetSlotData( nSlotId );
		const CfgEquip* pEquip = const_cast<CfgEquipTable*>(&CFG_DATA.GetEquipTable())->GetEquip( bagSlot.itemId );
		if ( pEquip == NULL )
		{
			return 10002;
		}
		if ( pEquip->m_nGrade <= 29 || pEquip->m_nGrade > 35 || pEquip->m_nType > 7 )
		{
			return 10002;
		}
	}

	if ( !vSlot.empty() )
	{
		// 清除装备
		for ( size_t i = 0; i < vSlot.size(); ++i )
		{
			int32_t nSlotId = vSlot[i];
			pPlayer->GetBag().CleanSlot( nSlotId, IDCR_BACK_EQUIP_COUNT );
		}

		EquipCount += nCount;
		SendBackEquipCount( pPlayer );
		UpdateEquipCount();
	}

	return 0;
}

void CGuiGuDaoRen::SendBackEquipCount( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_GUI_GU_DAO_REN_EQUIP_COUNT );
	if ( packet )
	{
		packet->writeInt32( EquipCount );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
	}
}

void CGuiGuDaoRen::UpdateEquipCount()
{
	// DB:保存装备回收计数到数据库
	// 解构代码中调用: DBService::SaveBackEquipCount(v2, EquipCount)
	// 与现有的 SaveEquipBackCount(int32_t,int8_t,int32_t,string&) 不同，是另一个方法
	// 暂时保留为空方法，等待 DBService 升级后实现
}

int32_t CGuiGuDaoRen::GetMaxCount()
{
	int32_t nCount = TIMER.GetDaysFromStart() + 1; // SVT_NORMAL = 0
	if ( nCount <= 44 )
	{
		return 0;
	}
	if ( nCount <= 59 )
	{
		return 20;
	}
	if ( nCount > 119 )
	{
		return 30;
	}
	return 25;
}

// ==================== 装备回收排行榜 ====================

int32_t CGuiGuDaoRen::OnAskEquipBackRank( Player* pPlayer, Answer::NetPacket* packet )
{
	SendBackEquipRank( pPlayer );
	return 0;
}

void CGuiGuDaoRen::SendBackEquipRank( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	MutexGuard lock( m_RankLock );

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_GUI_GU_DAO_REN_EQUIP_RANK );
	if ( packet )
	{
		packet->writeInt32( (int32_t)m_EquipBackRank.size() );
		for ( size_t i = 0; i < m_EquipBackRank.size(); ++i )
		{
			m_EquipBackRank[i].PackageData( packet );
		}
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
	}
}

void CGuiGuDaoRen::UpdateRankDate( EquipBackRankCfg* pStu )
{
	// DB:保存装备回收排行榜到数据库
	// 解构代码中调用: DBService::SaveBackEQuipRank(v2, &p_stu)
	// 与现有的 SaveEquipBackRecord(int32_t,int8_t,int32_t,string&) 不同，是另一个方法
	// 暂时保留为空方法，等待 DBService 升级后实现
}

// ==================== 每日重置 ====================

void CGuiGuDaoRen::OnNewMinute( int32_t nMinute )
{
	if ( GAME_SERVICE.getLine() == 9 )
	{
		return; // 跨服线不执行
	}

	if ( nMinute != 840 ) // 14:00
	{
		return;
	}

	int32_t nGongGaoId = 0;
	int32_t MaxCount = GetMaxCount();
	if ( EquipCount < MaxCount )
	{
		nGongGaoId = 542; // 未达标公告
	}
	else
	{
		nGongGaoId = 541; // 已达标公告
		MAP_MANAGER.ResetMapMonster();
	}

	EquipCount = 0;
	UpdateEquipCount();

	// 发送公告
	if ( nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet )
		{
			packet->writeInt32( nGongGaoId );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	// 发放排行榜奖励
	MutexGuard lock( m_RankLock );

	int32_t nNowTime = Answer::DayTime::now();
	int32_t nDayZero = Answer::DayTime::dayzero( nNowTime );
	for ( size_t i = 0; i < m_EquipBackRank.size(); ++i )
	{
		int32_t TitleId = CFG_DATA.GetTongTianChiReward( (int32_t)(i + 1) );
		if ( TitleId > 0 )
		{
			// 发送邮件奖励
			// 解构代码中用 DBService::OnSendSysMail(0, Cid, 6601, Param, 0)
			char szParam[64] = {0};
			snprintf( szParam, sizeof(szParam), "%d|%zu", nDayZero, i );
			std::string strParam = szParam;
			DB_SERVICE.OnSendSysMail( m_EquipBackRank[i].Cid, 6601, strParam );
		}
	}

	m_EquipBackRank.clear();
}

// ==================== 融合记录 ====================

int32_t CGuiGuDaoRen::GetRongHeRate()
{
	return m_Rate;
}

void CGuiGuDaoRen::AddRongHeRecord( RongHeRecord* pRecord )
{
	if ( NULL == pRecord )
	{
		return;
	}

	if ( m_RongHeRecordList.size() > 19 )
	{
		m_RongHeRecordList.pop_front();
	}

	m_RongHeRecordList.push_back( *pRecord );
	SendOneRongHeRecord( pRecord );
}

void CGuiGuDaoRen::AddRongHeCount( int32_t nCostValue, int32_t nGetValue )
{
	m_CostCount += nCostValue;
	m_GetCount += nGetValue;

	if ( m_CostCount > 5000000 )
	{
		m_CostCount = 0;
		m_GetCount = 0;
		m_Rate = 0;
	}

	if ( m_CostCount > 10000 )
	{
		int32_t nParam = (int)((float)m_GetCount / (float)m_CostCount * 100.0f);
		if ( m_Rate )
		{
			if ( nParam <= 96 )
			{
				m_Rate = 0;
			}
		}
		else if ( nParam > 103 )
		{
			m_Rate = 1;
		}
	}
	else
	{
		m_Rate = 0;
	}

	UpdateRongHeCount();
}

void CGuiGuDaoRen::SendAllRongHeRecord( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_RONG_HE_SEND_ALL_INFO );
	if ( packet )
	{
		packet->writeInt32( (int32_t)m_RongHeRecordList.size() );
		for ( std::list<RongHeRecord>::iterator it = m_RongHeRecordList.begin(); it != m_RongHeRecordList.end(); ++it )
		{
			packet->writeUTF8( it->strName );
			packet->writeInt32( it->nCostId );
			packet->writeInt32( it->nGiveId );
			packet->writeInt32( it->nSuccess );
			packet->writeInt32( it->nTime );
		}
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
	}
}

void CGuiGuDaoRen::SendOneRongHeRecord( RongHeRecord* pRecord )
{
	if ( NULL == pRecord )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_RONG_HE_SEND_ONE_INFO );
	if ( packet )
	{
		packet->writeUTF8( pRecord->strName );
		packet->writeInt32( pRecord->nCostId );
		packet->writeInt32( pRecord->nGiveId );
		packet->writeInt32( pRecord->nSuccess );
		packet->writeInt32( pRecord->nTime );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.broadcast( packet );
	}
}

void CGuiGuDaoRen::UpdateRongHeCount()
{
	// 保存融合统计到数据库 (sys_server_config)
	// 解构代码直接使用 MySQL 查询，这里保留直接 SQL 方式
	if ( GAME_SERVICE.getLine() == 9 )
	{
		return; // 跨服线不保存
	}

	Answer::MySqlDBGuard db(DBPOOL);
	char szSQL[1024] = {0};

	// COST_VALUE
	snprintf( szSQL, sizeof(szSQL), "SELECT `value` FROM `sys_server_config` WHERE `name`='COST_VALUE'");
	Answer::MySqlQuery result = db.query( szSQL );
	memset( szSQL, 0, sizeof(szSQL) );
	if ( result.eof() )
	{
		snprintf( szSQL, sizeof(szSQL), "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('COST_VALUE','%d')", m_CostCount );
	}
	else
	{
		snprintf( szSQL, sizeof(szSQL), "UPDATE `sys_server_config` SET `value`=%d WHERE `name`='COST_VALUE'", m_CostCount );
	}
	db.excute( szSQL );

	// GET_VALUE
	memset( szSQL, 0, sizeof(szSQL) );
	snprintf( szSQL, sizeof(szSQL), "SELECT `value` FROM `sys_server_config` WHERE `name`='GET_VALUE'");
	result = db.query( szSQL );
	memset( szSQL, 0, sizeof(szSQL) );
	if ( result.eof() )
	{
		snprintf( szSQL, sizeof(szSQL), "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('GET_VALUE','%d')", m_GetCount );
	}
	else
	{
		snprintf( szSQL, sizeof(szSQL), "UPDATE `sys_server_config` SET `value`=%d WHERE `name`='GET_VALUE'", m_GetCount );
	}
	db.excute( szSQL );

	// RATE_VALUE
	memset( szSQL, 0, sizeof(szSQL) );
	snprintf( szSQL, sizeof(szSQL), "SELECT `value` FROM `sys_server_config` WHERE `name`='RATE_VALUE'");
	result = db.query( szSQL );
	memset( szSQL, 0, sizeof(szSQL) );
	if ( result.eof() )
	{
		snprintf( szSQL, sizeof(szSQL), "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('RATE_VALUE','%d')", m_Rate );
	}
	else
	{
		snprintf( szSQL, sizeof(szSQL), "UPDATE `sys_server_config` SET `value`=%d WHERE `name`='RATE_VALUE'", m_Rate );
	}
	db.excute( szSQL );
}

void CGuiGuDaoRen::SaveRecordToDB()
{
	// 保存融合记录到数据库
	// 解构代码直接使用 MySQL: TRUNCATE + INSERT INTO
	Answer::MySqlDBGuard db(DBPOOL);
	char szSQL[4096] = {0};

	// TRUNCATE 旧数据
	snprintf( szSQL, sizeof(szSQL), "TRUNCATE mem_rong_he_record" );
	db.excute( szSQL );

	// INSERT 当前记录
	for ( std::list<RongHeRecord>::iterator it = m_RongHeRecordList.begin(); it != m_RongHeRecordList.end(); ++it )
	{
		memset( szSQL, 0, sizeof(szSQL) );
		snprintf( szSQL, sizeof(szSQL),
			"INSERT INTO mem_rong_he_record ( cid, name, cost_id, give_id, success, time ) VALUES (%lld, '%s', %d, %d, %d, %d)",
			it->nCid,
			it->strName.c_str(),
			it->nCostId,
			it->nGiveId,
			it->nSuccess,
			it->nTime );
		db.excute( szSQL );
	}
}
