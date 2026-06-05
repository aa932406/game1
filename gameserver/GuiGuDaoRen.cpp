#include "GuiGuDaoRen.h"
#include "GameService.h"
#include "Player.h"
#include "Bag.h"
#include "Monster.h"
#include "Map.h"
#include "MapManager.h"
#include "PoolManager.h"
#include "Timer.h"

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
			const CfgMonster* pMonster = CFG_DATA.getMonster( (*it) );
			if ( pMonster != NULL && pMonster->boss_sign == 11 )
			{
				// TODO: 随机地图刷怪（需要 MapManager 完整 API）
				// 当前简化：仅更新计数，怪物的实际刷新暂不实现
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
	// TODO: 保存到DB
	// DB_SERVICE.SaveGuiGuDaoRenData( NpcId, BackItemCount[NpcId] );
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
	// TODO: 保存到DB
	// DB_SERVICE.SaveBackEquipCount( EquipCount );
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
	// TODO: 保存到DB
	// DB_SERVICE.SaveBackEQuipRank( pStu );
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

	int32_t MaxCount = GetMaxCount();
	if ( EquipCount < MaxCount )
	{
		// 未达标，发送公告
		// TODO: 发送公告 542（鬼谷道人回收未满）
	}
	else
	{
		// 已达标，发送公告 541
		// TODO: 发送公告 541（鬼谷道人回收已满）
		// TODO: MapManager::ResetMapMonster();
	}

	EquipCount = 0;
	UpdateEquipCount();

	// 发放排行榜奖励
	MutexGuard lock( m_RankLock );

	for ( size_t i = 0; i < m_EquipBackRank.size(); ++i )
	{
		int32_t TitleId = CFG_DATA.GetTongTianChiReward( (int32_t)(i + 1) );
		if ( TitleId > 0 )
		{
			// TODO: 发送邮件奖励
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
	// TODO: 保存 COST_VALUE / GET_VALUE / RATE_VALUE 到 sys_server_config
}

void CGuiGuDaoRen::SaveRecordToDB()
{
	// TODO: TRUNCATE mem_rong_he_record + INSERT INTO
}
