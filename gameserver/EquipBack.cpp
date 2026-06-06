#include "EquipBack.h"
#include "DBService.h"
#include "GameService.h"
#include "Bag.h"
#include "Player.h"

CEquipBack::CEquipBack()
{
}

CEquipBack::~CEquipBack()
{
}

void CEquipBack::Init()
{
	// Runtime data is loaded asynchronously via DBService callbacks
	// Configuration data is loaded via CfgData::InitEquipBackTable()
}

int32_t CEquipBack::OnGoldBack( Player* pPlayer, Answer::NetPacket* packet )
{
	if ( NULL == pPlayer || NULL == packet )
	{
		return 10002;
	}

	pPlayer->GetTask().updateTaskCount( 42 );

	int32_t nId = packet->readInt32();
	const EquipBackCfg* pCfg = CFG_DATA.GetEquipTable().GetEquipBackCfg( nId );
	if ( NULL == pCfg )
	{
		return 10002;
	}

	Int32Vector vSlot;
	pPlayer->queryBagInfo( packet, vSlot );

	ItemDataList ItemList;
	for ( std::list<int32_t>::const_iterator it = pCfg->nEquipList.begin(); it != pCfg->nEquipList.end(); ++it )
	{
		ItemData item;
		item.m_nClass = 2;
		item.m_nCount = 1;
		item.m_nId = *it;
		ItemList.push_back( item );
	}

	if ( ItemList.empty() )
	{
		return 10002;
	}

	int32_t ret = 10002;

	// Type 1: 金币回购
	if ( pCfg->nType == 1 )
	{
		if ( pCfg->nLimitNum <= 0 )
		{
			return 10002;
		}

		if ( pCfg->nDisplayDay > 0 )
		{
			int32_t nDayDiff = CFG_DATA.getServerDiffDay( 0 ) + 1;
			if ( pCfg->nDisplayDay > nDayDiff )
			{
				return 10002;
			}
		}

		{
			std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.find( nId );
			if ( it != m_BackLimitInfoMap.end() && it->second.nCount >= pCfg->nLimitNum )
			{
				return 10002;
			}
		}

		if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
		{
			return 10002;
		}

		if ( !pPlayer->GetBag().AddAndRemoveItem( MemChrBagVector(), IACR_NONE, vSlot, ItemList, IDCR_BACK_EQUIP_COUNT ) )
		{
			return 10002;
		}

		pPlayer->AddCurrency( (CURRENCY_TYPE)pCfg->nRecovType, pCfg->nRecovValues, GCR_EQUIP_GOLD_BACK, 0 );

		BackLimitInfo stu;
		stu.nId = nId;
		stu.nCount = 1;
		stu.sLastName = pPlayer->getName();
		AddLimitCount( &stu );
		SendEquipBackLimitChange( pPlayer, nId );

		int32_t nItemId = ItemList.front().m_nId;
		Answer::NetPacket* pBroadcast = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( pBroadcast != NULL )
		{
			pBroadcast->writeInt32( 451 );
			pBroadcast->writeUTF8( pPlayer->getName() );
			pBroadcast->writeInt64( pPlayer->getCid() );
			pBroadcast->writeInt32( nItemId );
			pBroadcast->writeInt32( pCfg->nRecovValues );
			pBroadcast->setSize( pBroadcast->getWOffset() );
			GAME_SERVICE.worldBroadcast( pBroadcast );
		}
		ret = 0;
	}
	// Type 2: 开服回购
	else if ( pCfg->nType == 2 )
	{
		int32_t nDayDiff = CFG_DATA.getServerDiffDay( 0 );
		if ( nDayDiff + 1 > pCfg->nOpenDay )
		{
			return 10002;
		}

		if ( pCfg->nLimitNum <= 0 )
		{
			return 10002;
		}

		{
			std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.find( nId );
			if ( it != m_BackLimitInfoMap.end() && it->second.nCount >= pCfg->nLimitNum )
			{
				return 10002;
			}
		}

		if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
		{
			return 10002;
		}

		if ( !pPlayer->GetBag().AddAndRemoveItem( MemChrBagVector(), IACR_NONE, vSlot, ItemList, IDCR_BACK_EQUIP_COUNT ) )
		{
			return 10002;
		}

		pPlayer->AddCurrency( (CURRENCY_TYPE)pCfg->nRecovType, pCfg->nRecovValues, GCR_EQUIP_GOLD_BACK, 0 );

		BackLimitInfo stu;
		stu.nId = nId;
		stu.nCount = 1;
		stu.sLastName = pPlayer->getName();
		AddLimitCount( &stu );
		SendEquipBackLimitChange( pPlayer, nId );

		int32_t nItemId = ItemList.front().m_nId;
		Answer::NetPacket* pBroadcast = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( pBroadcast != NULL )
		{
			pBroadcast->writeInt32( 443 );
			pBroadcast->writeInt64( pPlayer->getCid() );
			pBroadcast->writeUTF8( pPlayer->getName() );
			pBroadcast->writeInt32( nItemId );
			pBroadcast->writeInt8( (int8_t)pCfg->nRecovType );
			pBroadcast->writeInt32( pCfg->nRecovValues );
			pBroadcast->setSize( pBroadcast->getWOffset() );
			GAME_SERVICE.worldBroadcast( pBroadcast );
		}
		ret = 0;
	}

	if ( ret != 0 )
	{
		return ret;
	}

	BackRecord record;
	record.nId = nId;
	record.nType = 1;
	record.nTime = Answer::DayTime::now();
	record.name = pPlayer->getName();

	SendEquipBackOnRecord( pPlayer, &record );
	AddRecord( &record );

	return 0;
}

int32_t CEquipBack::OnBuyBack( Player* pPlayer, Answer::NetPacket* packet )
{
	if ( NULL == pPlayer || NULL == packet )
	{
		return 10002;
	}

	int32_t nId = packet->readInt32();
	const EquipBackCfg* pCfg = CFG_DATA.GetEquipTable().GetEquipBackCfg( nId );
	if ( NULL == pCfg )
	{
		return 10002;
	}

	if ( pCfg->nType != 1 )
	{
		return 10002;
	}

	if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
	{
		return 10002;
	}

	std::map<int32_t, BackDepot>::iterator it = m_BackDepotMap.find( nId );
	if ( it == m_BackDepotMap.end() || it->second.Count <= 0 )
	{
		return 10002;
	}

	MemChrBagVector ItemVt;
	for ( std::list<int32_t>::const_iterator itList = pCfg->nEquipList.begin(); itList != pCfg->nEquipList.end(); ++itList )
	{
		MemChrBag item;
		memset( &item, 0, sizeof( item ) );
		item.itemId = *itList;
		item.itemCount = 1;
		ItemVt.push_back( item );
	}

	if ( pPlayer->GetBag().GetFreeSlotCount() < (int32_t)ItemVt.size() )
	{
		return 10002;
	}

	if ( !pPlayer->DecCurrency( (CURRENCY_TYPE)pCfg->nBuyBackType, pCfg->nBuyBackValue, GCR_EQUIP_BUY_BACK, 0 ) )
	{
		return 10002;
	}

	BackDepot deptStu;
	deptStu.nId = nId;
	deptStu.Count = -1;
	ChangeDeptCount( deptStu );

	pPlayer->GetBag().AddItem( ItemVt, (ITEM_ADD_REASON)IACR_EQUIP_BUY_BACK );

	BackRecord record;
	record.nId = nId;
	record.nType = 2;
	record.nTime = Answer::DayTime::now();
	record.name = pPlayer->getName();

	SendEquipBackOnRecord( pPlayer, &record );
	SendEquipBackCountChange( pPlayer, nId );
	AddRecord( &record );

	int32_t nItemId = ItemVt.empty() ? 0 : ItemVt.front().itemId;
	Answer::NetPacket* pBroadcast = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( pBroadcast != NULL )
	{
		pBroadcast->writeInt32( 452 );
		pBroadcast->writeUTF8( pPlayer->getName() );
		pBroadcast->writeInt64( pPlayer->getCid() );
		pBroadcast->writeInt32( nItemId );
		pBroadcast->writeInt32( pCfg->nBuyBackValue );
		pBroadcast->setSize( pBroadcast->getWOffset() );
		GAME_SERVICE.worldBroadcast( pBroadcast );
	}

	return 0;
}

void CEquipBack::KiaFuEquipBack( int32_t Index, int32_t EquipId, int32_t Mid, Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	const EquipBackCfg* pCfg = CFG_DATA.GetEquipTable().GetEquipBackCfg( Index );
	if ( NULL == pCfg )
	{
		return;
	}

	bool bFound = false;
	for ( std::list<int32_t>::const_iterator it = pCfg->nEquipList.begin(); it != pCfg->nEquipList.end(); ++it )
	{
		if ( *it == EquipId )
		{
			bFound = true;
			break;
		}
	}
	if ( !bFound || pCfg->nEquipList.empty() )
	{
		return;
	}

	int32_t nDayDiff = CFG_DATA.getServerDiffDay( 0 );
	if ( nDayDiff + 1 > pCfg->nOpenDay || pCfg->nLimitNum <= 0 )
	{
		return;
	}

	{
		std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.find( Index );
		if ( it != m_BackLimitInfoMap.end() && it->second.nCount >= pCfg->nLimitNum )
		{
			return;
		}
	}

	if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
	{
		return;
	}

	MemChrBag item;
	memset( &item, 0, sizeof( item ) );
	item.itemId = (int32_t)pCfg->nRecovType;
	item.itemCount = pCfg->nRecovValues;

	char szParam[32] = { 0 };
	snprintf( szParam, sizeof( szParam ) - 1, "%d", EquipId );
	std::string Param( szParam );

	DB_SERVICE.OnSendSysMail( pPlayer->getCid(), 6373, item, Param );

	Answer::NetPacket* pBroadcast = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( pBroadcast != NULL )
	{
		pBroadcast->writeInt32( 441 );
		pBroadcast->writeInt64( pPlayer->getCid() );
		pBroadcast->writeUTF8( pPlayer->getName() );
		pBroadcast->writeInt8( 2 );
		pBroadcast->writeInt32( EquipId );
		pBroadcast->writeInt32( 1 );
		pBroadcast->writeInt8( (int8_t)pCfg->nRecovType );
		pBroadcast->writeInt32( pCfg->nRecovValues );
		pBroadcast->setSize( pBroadcast->getWOffset() );
		GAME_SERVICE.worldBroadcast( pBroadcast );
	}

	BackLimitInfo stu;
	stu.nId = Index;
	stu.nCount = 1;
	stu.sLastName = pPlayer->getName();
	AddLimitCount( &stu );
	SendEquipBackLimitChange( pPlayer, Index );
}

void CEquipBack::AddLimitCount( BackLimitInfo* p_stu )
{
	if ( NULL == p_stu )
	{
		return;
	}

	Answer::MutexGuard lock( m_DepotLock );

	std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.find( p_stu->nId );
	if ( it != m_BackLimitInfoMap.end() )
	{
		it->second.nCount += p_stu->nCount;
		it->second.sLastName = p_stu->sLastName;
		it->second.nId = p_stu->nId;
	}
	else
	{
		m_BackLimitInfoMap[p_stu->nId] = *p_stu;
	}

	std::map<int32_t, BackLimitInfo>::iterator itTmp = m_BackLimitInfoMap.find( p_stu->nId );
	if ( itTmp != m_BackLimitInfoMap.end() )
	{
		DB_SERVICE.SaveEquipBackCount( itTmp->first, 2, itTmp->second.nCount, itTmp->second.sLastName );
	}
}

void CEquipBack::ChangeDeptCount( BackDepot stu )
{
	Answer::MutexGuard lock( m_DepotLock );

	std::map<int32_t, BackDepot>::iterator it = m_BackDepotMap.find( stu.nId );
	if ( it != m_BackDepotMap.end() )
	{
		it->second.Count += stu.Count;
		it->second.nId = stu.nId;
	}
	else
	{
		m_BackDepotMap[stu.nId] = stu;
	}

	std::map<int32_t, BackDepot>::iterator itTmp = m_BackDepotMap.find( stu.nId );
	if ( itTmp != m_BackDepotMap.end() )
	{
		std::string name;
		DB_SERVICE.SaveEquipBackCount( itTmp->first, 1, itTmp->second.Count, name );
	}
}

void CEquipBack::AddRecord( BackRecord* p_stu )
{
	if ( NULL == p_stu )
	{
		return;
	}

	Answer::MutexGuard lock( m_RecordLock );

	if ( m_BackRecord.size() > 50 )
	{
		m_BackRecord.pop_front();
	}

	DB_SERVICE.SaveEquipBackRecord( p_stu->nId, p_stu->nType, p_stu->nTime, p_stu->name );

	m_BackRecord.push_back( *p_stu );
}

void CEquipBack::SendEquipBackInfo( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_EQUIP_BACK_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( (int32_t)m_BackRecord.size() );
	for ( std::list<BackRecord>::iterator it = m_BackRecord.begin(); it != m_BackRecord.end(); ++it )
	{
		packet->writeInt32( it->nId );
		packet->writeInt8( it->nType );
		packet->writeUTF8( it->name );
		packet->writeInt32( it->nTime );
	}

	packet->writeInt32( (int32_t)m_BackDepotMap.size() );
	for ( std::map<int32_t, BackDepot>::iterator it = m_BackDepotMap.begin(); it != m_BackDepotMap.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.Count );
	}

	packet->writeInt32( (int32_t)m_BackLimitInfoMap.size() );
	for ( std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.begin(); it != m_BackLimitInfoMap.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.nCount );
		packet->writeUTF8( it->second.sLastName );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

void CEquipBack::SendEquipBackOnRecord( Player* pPlayer, BackRecord* p_stu )
{
	if ( NULL == pPlayer || NULL == p_stu )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_EQUIP_BACK_ONE_RECORD );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( p_stu->nId );
	packet->writeInt8( p_stu->nType );
	packet->writeUTF8( p_stu->name );
	packet->writeInt32( p_stu->nTime );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

void CEquipBack::SendEquipBackCountChange( Player* pPlayer, int32_t nId )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	std::map<int32_t, BackDepot>::iterator it = m_BackDepotMap.find( nId );
	if ( it == m_BackDepotMap.end() )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_EQUIP_BACK_COUNT_CHANGE );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( it->first );
	packet->writeInt32( it->second.Count );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

void CEquipBack::SendEquipBackLimitChange( Player* pPlayer, int32_t nId )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.find( nId );
	if ( it == m_BackLimitInfoMap.end() )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_EQUIP_BACK_LIMIT_CHANGE );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( it->first );
	packet->writeInt32( it->second.nCount );
	packet->writeUTF8( it->second.sLastName );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

void CEquipBack::UpdateEquipRecord( int32_t nId, int8_t nType, int32_t nTime, std::string* p_Name )
{
	if ( NULL == p_Name )
	{
		return;
	}

	BackRecord stu;
	stu.nId = nId;
	stu.nType = nType;
	stu.nTime = nTime;
	stu.name = *p_Name;

	Answer::MutexGuard lock( m_RecordLock );

	if ( m_BackRecord.size() > 50 )
	{
		m_BackRecord.pop_front();
	}

	m_BackRecord.push_back( stu );
}

void CEquipBack::UpdateEquipBackInfo( int32_t nId, int8_t nType, int32_t nCount, std::string* p_Name )
{
	if ( nType == 1 )
	{
		BackDepot stu;
		stu.nId = nId;
		stu.Count = nCount;

		Answer::MutexGuard lock( m_DepotLock );

		std::map<int32_t, BackDepot>::iterator it = m_BackDepotMap.find( stu.nId );
		if ( it != m_BackDepotMap.end() )
		{
			it->second.Count = stu.Count;
			it->second.nId = stu.nId;
		}
		else
		{
			m_BackDepotMap[stu.nId] = stu;
		}
	}
	else if ( nType == 2 )
	{
		BackLimitInfo stu;
		stu.nId = nId;
		stu.nCount = nCount;
		if ( p_Name != NULL )
		{
			stu.sLastName = *p_Name;
		}

		Answer::MutexGuard lock( m_DepotLock );

		std::map<int32_t, BackLimitInfo>::iterator it = m_BackLimitInfoMap.find( stu.nId );
		if ( it != m_BackLimitInfoMap.end() )
		{
			it->second.nCount = stu.nCount;
			it->second.sLastName = stu.sLastName;
			it->second.nId = stu.nId;
		}
		else
		{
			m_BackLimitInfoMap[stu.nId] = stu;
		}
	}
}
