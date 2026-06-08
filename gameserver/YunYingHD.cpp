#include "YunYingHD.h"
#include "CfgData.h"
#include "Player.h"
#include "EquipManager.h"
#include "GameService.h"
#include "DBService.h"
#include "FestivalDoubleEleven.h"

CYunYingHD::CYunYingHD()
{
	m_TotalChongZhiDay = 0;
	m_nLastTeHui = 0;
}

CYunYingHD::~CYunYingHD()
{

}

void CYunYingHD::OnLoadFromDB( const PlayerDBData& dbData )
{
	CfgTotalChongZhi* pCfg = CFG_DATA.GetTotalChongZhiCfg( 1 );
	if ( NULL == pCfg )
	{
		return;
	}
	m_TotalChongZhiDay = pCfg->NewServerday;
}

void CYunYingHD::OnSaveToDB( PlayerDBData& dbData )
{

}

void CYunYingHD::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_GET_SHOU_CHONG_REWARD );
	procList.push_back( CM_ASK_SHOU_CHONG_INFO );

	procList.push_back( CM_ASK_SHOU_TE_HUI_INFO );
	procList.push_back( CM_BUY_TEI_HUI_GIFT );

	procList.push_back( CM_ASK_EVERYDAY_CHONG_ZHI_INFO );
	procList.push_back( CM_GET_EVERYDAY_CHONG_ZHI_LI_BAO );

	procList.push_back( CM_GET_THREE_PET_GIFT );

	procList.push_back( CM_GET_TOTAL_CHONG_ZHI_GIFT );
	procList.push_back( CM_ASK_TOTAL_CHONG_ZHI_INFO );
}

int32_t	CYunYingHD::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_GET_SHOU_CHONG_REWARD:
		{
			return OnGetShouChongReward( inPacket );
		}
	case CM_ASK_SHOU_CHONG_INFO:
		{
			SendShouChongInfo();
			break;
		}
	case CM_BUY_TEI_HUI_GIFT:
		{
			return OnGetBuyTeHuiItem( inPacket );
		}
	case CM_ASK_SHOU_TE_HUI_INFO:
		{
			SendTeHuiInfo();
			break;
		}
	case CM_ASK_EVERYDAY_CHONG_ZHI_INFO:
		{
			SendEveryDayChongZhiInfo();
			break;
		}
	case CM_GET_EVERYDAY_CHONG_ZHI_LI_BAO:
		{
			return OnGetEveryDayChongZhiGift( inPacket );
		}
	case CM_GET_THREE_PET_GIFT:
		{
			return OnGetThreePetGift( inPacket );
		}
	case CM_GET_TOTAL_CHONG_ZHI_GIFT:
		{
			return OnGetTotalChongZhi( inPacket );
		}
	case CM_ASK_TOTAL_CHONG_ZHI_INFO:
		{
			SendTotalChongZhiInfo();
			break;
		}
	default:
		break;
	}
	return ERR_OK;
}

void CYunYingHD::OnCleanUp()
{
	m_TotalChongZhiDay = 0;
	m_nLastTeHui = 0;
}

void CYunYingHD::OnUpdate( int64_t curTick )
{

}

void CYunYingHD::OnDaySwitch( int32_t nDiffDays )
{
	SendEveryDayChongZhiInfo( 3 );
	SendEveryDayChongZhiInfo( 2 );
	SendEveryDayChongZhiIcon( 3 );
	SendEveryDayChongZhiIcon( 2 );
	SendTotalChongZhiIcon();
}

int32_t	CYunYingHD::OnGetShouChongReward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetShouChongState() != 1 )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrEquipBagVector& Item = CFG_DATA.GetShouChongLiBao();
	MemChrBagVector addItemVt;
	MemEquipVector vEquip;
	if (!Item.empty())
	{
		for (MemChrEquipBagVector::iterator it =Item.begin();it !=  Item.end();++it)
		{
			if (m_pPlayer->getJob() == it->job || it->job == 0 )
			{
				MemChrBag  chrbag = {};
				chrbag.itemId    = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				chrbag.endTime	 = 0;
				if ( chrbag.itemClass == IC_EQUIP )
				{
					MemEquip equip = EQUIP_MANAGER.CreateMemEquip( chrbag.itemId, m_pPlayer->getSid(), m_pPlayer->getCid(), it->star );
					if ( equip.base <= 0 || equip.id <= 0 )
					{
						return false;
					}
					chrbag.srcId		= equip.id;	
					vEquip.push_back( equip );
				}
				addItemVt.push_back(chrbag);
			}
		}
	}
	m_pPlayer->autoUseItem(addItemVt);
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( addItemVt,  IACR_SHOU_CHONG ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !vEquip.empty() )
	{
		m_pPlayer->sendEquipInfo( vEquip );
	} 
	m_pPlayer->updateRecord( RP_SHOU_CHONG_LI_BAO, 1 );
	GongGao( BCI_SHOU_CHONG_LI_BAO );
	SendShouChongIcon();
	SendShouChongInfo();

	LogDailyGift logDailyGift = {};
	logDailyGift.cid = m_pPlayer->getCid();
	logDailyGift.type = DGT_SHOU_CHONG;
	logDailyGift.giftid = 0;
	logDailyGift.time = m_pPlayer->getNow();

	DB_SERVICE.InsertDailyGiftLog( logDailyGift );
	return ERR_OK;
}

int32_t	CYunYingHD::OnGetBuyTeHuiItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t		Index = inPacket->readInt8();
	NewServerFavorable* pCfg = CFG_DATA.GetNewServerFavorable( Index );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t OldRecord = m_pPlayer->getRecord( RP_BUY_TE_HUI_RECORD );
	int32_t NewRecord = OldRecord | ( 1 << (Index - 1) );
	if ( OldRecord == NewRecord )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pCfg->NeedGold <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	int64_t HaveMoney = m_pPlayer->GetCurrency( CURRENCY_GOLD );
	if ( HaveMoney < pCfg->NeedGold )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrEquipBagVector& Item = pCfg->ItemVector;
	MemChrBagVector addItemVt;
	MemEquipVector vEquip;
	if (!Item.empty())
	{
		for (MemChrEquipBagVector::iterator it =Item.begin();it !=  Item.end();++it)
		{
			if (m_pPlayer->getJob() == it->job || it->job == 0 )
			{
				MemChrBag  chrbag = {};
				chrbag.itemId    = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				chrbag.endTime	 = 0;
				if ( chrbag.itemClass == IC_EQUIP )
				{
					MemEquip equip = EQUIP_MANAGER.CreateMemEquip( chrbag.itemId, m_pPlayer->getSid(), m_pPlayer->getCid(), it->star );
					if ( equip.base <= 0 || equip.id <= 0 )
					{
						return false;
					}
					chrbag.srcId		= equip.id;	
					vEquip.push_back( equip );
				}
				addItemVt.push_back(chrbag);
			}
		}
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_BUY_TE_HUI_LI_BAO, Index ))
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( addItemVt,  IACR_NEW_SERVER_TE_HUI ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !vEquip.empty() )
	{
		m_pPlayer->sendEquipInfo( vEquip );
	} 
	m_pPlayer->updateRecord( RP_BUY_TE_HUI_RECORD, NewRecord );
	GongGaoList::iterator it = pCfg->GongGaoInfo.begin();
	for ( ; it != pCfg->GongGaoInfo.end(); ++it )
	{
		if ( it->Job == 0 || it->Job == m_pPlayer->getJob() )
		{
			GongGao( it->GongGaoId );
		}
	}
	SendTeHuiInfo();
	SendTeHuiIcon();
	return ERR_OK;
}

int32_t	CYunYingHD::OnGetEveryDayChongZhiGift( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t	Index = inPacket->readInt8();
	CfgEverydayChongZhi* pCfg =CFG_DATA.GetEveryDayChongZhiCfg( Index );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t TodayPayed = m_pPlayer->GetTodayPayGold();
	if ( pCfg->NeedGold > TodayPayed )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t OldRecord = m_pPlayer->getRecord( PR_EVERY_DAY_CHONG_ZHI_GIFT_RECORD );
	int32_t NewRecord = OldRecord | ( 1 << (Index - 1) );
	if ( OldRecord == NewRecord )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrEquipBagVector& Item = pCfg->ItemVector;
	MemChrBagVector addItemVt;
	MemEquipVector vEquip;
	if (!Item.empty())
	{
		for (MemChrEquipBagVector::iterator it =Item.begin();it !=  Item.end();++it)
		{
			if (m_pPlayer->getJob() == it->job || it->job == 0 )
			{
				MemChrBag  chrbag = {};
				chrbag.itemId    = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				chrbag.endTime	 = 0;
				if ( chrbag.itemClass == IC_EQUIP )
				{
					MemEquip equip = EQUIP_MANAGER.CreateMemEquip( chrbag.itemId, m_pPlayer->getSid(), m_pPlayer->getCid(), it->star );
					if ( equip.base <= 0 || equip.id <= 0 )
					{
						return false;
					}
					chrbag.srcId		= equip.id;	
					vEquip.push_back( equip );
				}
				addItemVt.push_back(chrbag);
			}
		}
	}
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( addItemVt,  IACR_EVERYDAY_CHONG_ZHI ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !vEquip.empty() )
	{
		m_pPlayer->sendEquipInfo( vEquip );
	} 
	m_pPlayer->updateRecord( PR_EVERY_DAY_CHONG_ZHI_GIFT_RECORD, NewRecord );
	GongGaoList::iterator it = pCfg->GongGaoInfo.begin();
	for ( ; it != pCfg->GongGaoInfo.end(); ++it )
	{
		if ( it->Job == 0 || it->Job == m_pPlayer->getJob() )
		{
			GongGao( it->GongGaoId );
		}
	}
	SendEveryDayChongZhiInfo();
	SendEveryDayChongZhiIcon();

	LogDailyGift logDailyGift = {};
	logDailyGift.cid = m_pPlayer->getCid();
	logDailyGift.type = DGT_SHOU_CHONG;
	logDailyGift.giftid = Index;
	logDailyGift.time = m_pPlayer->getNow();

	DB_SERVICE.InsertDailyGiftLog( logDailyGift );
	return ERR_OK;
}

int32_t	CYunYingHD::OnGetThreePetGift( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->getRecord( RP_THREE_PET_GIFT ) > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	NewServerFavorable&	pCfg = CFG_DATA.GetThreePetGift();
	if ( pCfg.NeedGold <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	int64_t HaveMoney = m_pPlayer->GetCurrency( CURRENCY_GOLD );
	if ( HaveMoney < pCfg.NeedGold )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrEquipBagVector& Item = pCfg.ItemVector;
	MemChrBagVector addItemVt;
	MemEquipVector vEquip;
	if (!Item.empty())
	{
		for (MemChrEquipBagVector::iterator it =Item.begin();it !=  Item.end();++it)
		{
			if (m_pPlayer->getJob() == it->job || it->job == 0 )
			{
				MemChrBag  chrbag = {};
				chrbag.itemId    = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				chrbag.endTime	 = 0;
				if ( chrbag.itemClass == IC_EQUIP )
				{
					MemEquip equip = EQUIP_MANAGER.CreateMemEquip( chrbag.itemId, m_pPlayer->getSid(), m_pPlayer->getCid(), it->star );
					if ( equip.base <= 0 || equip.id <= 0 )
					{
						return false;
					}
					chrbag.srcId		= equip.id;	
					vEquip.push_back( equip );
				}
				addItemVt.push_back(chrbag);
			}
		}
	}
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( addItemVt,  IACR_NEW_SERVER_TE_HUI ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg.NeedGold, GCR_BUY_THREE_PET_LI_BAO, pCfg.Index ))
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->updateRecord( RP_THREE_PET_GIFT , 1 );
	if ( !vEquip.empty() )
	{
		m_pPlayer->sendEquipInfo( vEquip );
	} 
	GongGaoList::iterator it = pCfg.GongGaoInfo.begin();
	for ( ; it != pCfg.GongGaoInfo.end(); ++it )
	{
		if ( it->Job == 0 || it->Job == m_pPlayer->getJob() )
		{
			GongGao( it->GongGaoId );
		}
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	SendThreePetGiftIcon();
	return ERR_OK;
}

int32_t	CYunYingHD::OnGetTotalChongZhi( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t	Index = inPacket->readInt8();
	CfgTotalChongZhi* pCfg =CFG_DATA.GetTotalChongZhiCfg( Index );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ZhongZhiValues = m_pPlayer->getRecord(RP_TOTAL_CHI_ZHI_VALUES);
	if ( pCfg->NeedGold > ZhongZhiValues )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t OldRecord = m_pPlayer->getRecord( RP_TOTAL_CHI_ZHI_REWARD );
	int32_t NewRecord = OldRecord | ( 1 << (Index - 1) );
	if ( OldRecord == NewRecord )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrEquipBagVector& Item = pCfg->ItemVector;
	MemChrBagVector addItemVt;
	MemEquipVector vEquip;
	if (!Item.empty())
	{
		for (MemChrEquipBagVector::iterator it =Item.begin();it !=  Item.end();++it)
		{
			if (m_pPlayer->getJob() == it->job || it->job == 0 )
			{
				MemChrBag  chrbag = {};
				chrbag.itemId    = it->id;
				chrbag.itemClass = it->type;
				chrbag.itemCount = it->count;
				chrbag.bind		 = it->bind;
				chrbag.endTime	 = 0;
				if ( chrbag.itemClass == IC_EQUIP )
				{
					MemEquip equip = EQUIP_MANAGER.CreateMemEquip( chrbag.itemId, m_pPlayer->getSid(), m_pPlayer->getCid(), it->star );
					if ( equip.base <= 0 || equip.id <= 0 )
					{
						return false;
					}
					chrbag.srcId		= equip.id;	
					vEquip.push_back( equip );
				}
				addItemVt.push_back(chrbag);
			}
		}
	}
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( addItemVt,  IACR_TOTAL_CHONG_ZHI ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !vEquip.empty() )
	{
		m_pPlayer->sendEquipInfo( vEquip );
	} 
	m_pPlayer->updateRecord( RP_TOTAL_CHI_ZHI_REWARD, NewRecord );
	GongGaoList::iterator it = pCfg->GongGaoInfo.begin();
	for ( ; it != pCfg->GongGaoInfo.end(); ++it )
	{
		if ( it->Job == 0 || it->Job == m_pPlayer->getJob() )
		{
			GongGao( it->GongGaoId );
		}
	}
	SendTotalChongZhiIcon();
	SendTotalChongZhiInfo();
	return ERR_OK;
}

int8_t CYunYingHD::GetShouChongState()
{
	if ( m_pPlayer->GetTotalPayGold() <= 0 )
	{
		return 0;
	}

	if ( m_pPlayer->getRecord(RP_SHOU_CHONG_LI_BAO) == 0 )
	{
		return 1;
	}
	else
	{
		return 2;
	}
}


void CYunYingHD::SendShouChongInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_SHOU_CHONG_INFO);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( GetShouChongState() );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);		
}

void CYunYingHD::SendShouChongIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_SHOU_CHONG_ICON ) )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetShouChongIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);	
}

void CYunYingHD::GetShouChongIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_SHOU_CHONG_ICON ) )
	{
		return;
	}
	if ( GetShouChongState() > 1 )
	{
		return;
	}
	IconList.push_back( GetShouChongIconStu() );
}

ShowIcon CYunYingHD::GetShouChongIconStu()
{
	ShowIcon stu = {};
	stu.nId			= CHOU_CHONG;
	if ( GetShouChongState() > 1 )
	{
		stu.nState  = AS_TIME_OUT;
	}
	else
	{
		stu.nState		= AS_RUNNING;
	}
	stu.nLeftTime	= -1;
	stu.Effects		= 1;
	return stu;
}

void CYunYingHD::SendTeHuiInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_NEW_SERVER_FAVORABLE);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getRecord( RP_BUY_TE_HUI_RECORD ) );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);	
}

void CYunYingHD::SendTeHuiIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_NEW_SERVER_TE_HUI ) )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetTeHuiIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);	
}

void CYunYingHD::GetTeHuiIconState( IconStateList& IconList )
{
 	if ( NULL == m_pPlayer )
 	{
 		return;
 	}
 	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_NEW_SERVER_TE_HUI ) )
 	{
 		return;
 	}
	if ( !IsHaveTeHuiGift() )
	{
		return;
	}
 	IconList.push_back( GetTeHuiIconStu() );
}

ShowIcon CYunYingHD::GetTeHuiIconStu()
{
 	ShowIcon stu = {};
 	stu.nId			= NEW_SERVER_TE_HUI;
	if ( !IsHaveTeHuiGift() )
	{
		stu.nState		= AS_TIME_OUT;
	}
	else
	{
		stu.nState		= AS_RUNNING;
	}
 	stu.nLeftTime	= -1;
 	stu.Effects		= 1;
 	return stu;
}

bool CYunYingHD::IsHaveTeHuiGift()
{
	int32_t OldRecord = m_pPlayer->getRecord( RP_BUY_TE_HUI_RECORD );
	NewServerFavorableMap CfgTeHuiMap = CFG_DATA.GetNewServerFavorableCfg();
	NewServerFavorableMap::iterator it = CfgTeHuiMap.begin();
	for ( ; it != CfgTeHuiMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( OldRecord == NewRecord )
		{
			continue;
		}
		return true;
	}
	return false;
}

void CYunYingHD::SendEveryDayChongZhiInfo( int8_t nType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t nRecord = 0;
	if ( nType == 3 || nType == 1 || nType == 4 )
	{
		nRecord = m_pPlayer->getRecord( PR_EVERY_DAY_CHONG_ZHI_GIFT_RECORD );
	}
	else if ( nType == 2 )
	{
		nRecord = m_pPlayer->getRecord( 2033 );
	}
	else
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_EVERYDAY_CHONG_ZHI);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( nType );
	packet->writeInt32( m_pPlayer->GetTodayPayGold() );
	packet->writeInt32( nRecord );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CYunYingHD::SendEveryDayChongZhiIcon( int8_t nType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !CanShowEveryChongZhiIcon() )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_EVERYDAY_SHOUCHONG ) )
	{
		return;
	}
	if ( nType != 2 )
	{
		ShowIcon stu = GetEveryDayChongZhiIconStu( nType );
		m_pPlayer->SendIconState( stu );
		return;
	}
	// nType == 2: FestivalDailyRecharge check
	CFestivalDoubleEleven* pFestival = Answer::Singleton<CFestivalDoubleEleven>::instance();
	if ( pFestival != NULL && pFestival->IsInTime( FAT_DAILY_RECHARGE ) )
	{
		ShowIcon stu = GetEveryDayChongZhiIconStu( nType );
		m_pPlayer->SendIconState( stu );
	}
}

void CYunYingHD::GetEveryDayChongZhiIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !CanShowEveryChongZhiIcon() )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_EVERYDAY_SHOUCHONG ) )
	{
		return;
	}
	int32_t HaveCount = 0;
	if ( HaveEveryDayChongZhiGiftCount( 3, HaveCount ) )
	{
		IconList.push_back( GetEveryDayChongZhiIconStu( 3 ) );
	}
	CFestivalDoubleEleven* pFestival = Answer::Singleton<CFestivalDoubleEleven>::instance();
	if ( pFestival != NULL && pFestival->IsInTime( FAT_DAILY_RECHARGE )
		&& HaveEveryDayChongZhiGiftCount( 2, HaveCount ) )
	{
		IconList.push_back( GetEveryDayChongZhiIconStu( 2 ) );
	}
}

ShowIcon CYunYingHD::GetEveryDayChongZhiIconStu( int8_t nType )
{
	ShowIcon stu = {};
	stu.nId			= getEveryDayChongZhiIcon( nType );
	if ( !IsHaveEveryDayChongZhiGift() )
	{
		stu.nState		= AS_TIME_OUT;
	}
	else
	{
		stu.nState		= AS_RUNNING;
	}
	stu.nLeftTime	= -1;
	return stu;
}

bool CYunYingHD::IsHaveEveryDayChongZhiGift()
{
	int32_t OldRecord = m_pPlayer->getRecord( PR_EVERY_DAY_CHONG_ZHI_GIFT_RECORD );
	EverydayChongZhiMap CfgEveryDayChongZhiMap = CFG_DATA.GetEveryDayTable();
	EverydayChongZhiMap::iterator it = CfgEveryDayChongZhiMap.begin();
	for ( ; it != CfgEveryDayChongZhiMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( OldRecord == NewRecord )
		{
			continue;
		}
		return true;
	}
	return false;
}

void CYunYingHD::GongGao( int32_t GongGaoId )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( GongGaoId );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->setSize(packet->getWOffset());
	packet->setProc( SM_SEND_NOTICE_PARAM );
	GAME_SERVICE.worldBroadcast(packet);
}


void CYunYingHD::SendThreePetGiftIcon()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetThreePetGiftIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);	
}

void CYunYingHD::GetThreePetGiftIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( m_pPlayer->getRecord( RP_THREE_PET_GIFT ) > 0 )
	{
		return;
	}
	IconList.push_back( GetThreePetGiftIconStu() );
}

ShowIcon CYunYingHD::GetThreePetGiftIconStu()
{
	ShowIcon stu = {};
	if ( NULL == m_pPlayer )
	{
		return stu;
	}
	stu.nId			= THREE_PET_ICON;
	if ( m_pPlayer->getRecord( RP_THREE_PET_GIFT ) > 0 )
	{
		stu.nState		= AS_TIME_OUT;
	}
	else
	{
		stu.nState		= AS_RUNNING;
	}
	stu.nLeftTime	= -1;
	return stu;
}

int32_t CYunYingHD::HaveTotalChongZhiRewardCount()
{
	int32_t HaveCount = 0;
	int32_t OldRecord = m_pPlayer->getRecord( RP_TOTAL_CHI_ZHI_REWARD );
	TotalChongZhiMap CfgTotalChongZhiMap = CFG_DATA.GetTotalChongZhiTable();
	TotalChongZhiMap::iterator it = CfgTotalChongZhiMap.begin();
	for ( ; it != CfgTotalChongZhiMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( OldRecord == NewRecord )
		{
			continue;
		}
		if ( it->second.NeedGold > m_pPlayer->getRecord(RP_TOTAL_CHI_ZHI_VALUES) )
		{
			continue;
		}
		HaveCount++;
	}
	return HaveCount;
}

void CYunYingHD::SendTotalChongZhiIcon()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetTotalChongZhiIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);	
}

void CYunYingHD::SendTotalChongZhiInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_TOTAL_CHONG_ZHI);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getRecord( RP_TOTAL_CHI_ZHI_VALUES ) );
	packet->writeInt32( m_pPlayer->getRecord( RP_TOTAL_CHI_ZHI_REWARD ) );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);	
}

void CYunYingHD::GetTotalChongZhiIconState( IconStateList& IconList )
{
	int32_t ServerDay = CFG_DATA.getServerDiffTime();
	if ( HaveTotalChongZhiRewardCount() <= 0 &&  ServerDay + 1 > m_TotalChongZhiDay )
	{
		return;
	}
	IconList.push_back( GetTotalChongZhiIconStu() );	
}

bool CYunYingHD::AllGetTotalChongZhiReward()
{
	int32_t HaveCount = 0;
	int32_t OldRecord = m_pPlayer->getRecord( RP_TOTAL_CHI_ZHI_REWARD );
	TotalChongZhiMap CfgTotalChongZhiMap = CFG_DATA.GetTotalChongZhiTable();
	TotalChongZhiMap::iterator it = CfgTotalChongZhiMap.begin();
	for ( ; it != CfgTotalChongZhiMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( OldRecord == NewRecord )
		{
			continue;
		}
		return false;
	}
	return true;
}

ShowIcon CYunYingHD::GetTotalChongZhiIconStu()
{
	ShowIcon stu = {};
	if ( NULL == m_pPlayer )
	{
		return stu;
	}
	int32_t ServerDay = CFG_DATA.getServerDiffTime();
	if ( AllGetTotalChongZhiReward() )
	{
		stu.nState		= AS_TIME_OUT;
	}
	else if ( HaveTotalChongZhiRewardCount() <= 0 &&  ServerDay + 1 > m_TotalChongZhiDay )
	{
		stu.nState		= AS_TIME_OUT;
	}
	else
	{
		stu.nState		= AS_RUNNING;
	}
	stu.IconRight	= HaveTotalChongZhiRewardCount();
	stu.nId			= TOTAL_CHONG_ZHI;
	stu.nLeftTime	= -1;
	return stu;
}

void CYunYingHD::AddTotalChongZhiCount( int32_t AddCount )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t ServerDay = CFG_DATA.getServerDiffTime();
	if ( ServerDay >= m_TotalChongZhiDay )
	{
		return;
	}
	m_pPlayer->GetOperateLimit().AddLimitCount( RP_TOTAL_CHI_ZHI_VALUES,AddCount );
	if ( HaveTotalChongZhiRewardCount() > 0 )
	{
		SendTotalChongZhiIcon();
	}
	SendTotalChongZhiInfo();
}
// ========== Missing methods from decompiled code ==========

int32_t CYunYingHD::getTeHuiLimitTime()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	int32_t nLimitTime = 0;
	int32_t nStartTime = m_pPlayer->getCreateTime();
	int32_t nNowTime = m_pPlayer->getNow();
	int32_t OldRecord = m_pPlayer->getRecord( RP_BUY_TE_HUI_RECORD );
	const NewServerFavorableMap& cfgMap = CFG_DATA.GetNewServerFavorableCfg();
	for ( NewServerFavorableMap::const_iterator iter = cfgMap.begin(); iter != cfgMap.end(); ++iter )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( iter->first - 1 ) );
		if ( OldRecord != NewRecord )
		{
			int32_t nTime = nStartTime + iter->second.nLimitTime - nNowTime;
			if ( nTime > 0 && ( nLimitTime == 0 || nLimitTime > nTime ) )
			{
				nLimitTime = nTime;
			}
		}
	}
	return nLimitTime;
}

void CYunYingHD::checkTeHuiTime()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t nLimitTime = 0;
	int32_t nIndex = 0;
	int32_t nStartTime = m_pPlayer->getCreateTime();
	int32_t nNowTime = m_pPlayer->getNow();
	int32_t OldRecord = m_pPlayer->getRecord( RP_BUY_TE_HUI_RECORD );
	const NewServerFavorableMap& cfgMap = CFG_DATA.GetNewServerFavorableCfg();
	for ( NewServerFavorableMap::const_iterator iter = cfgMap.begin(); iter != cfgMap.end(); ++iter )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( iter->first - 1 ) );
		if ( OldRecord != NewRecord )
		{
			int32_t nTime = nStartTime + iter->second.nLimitTime - nNowTime;
			if ( nTime > 0 && ( nLimitTime == 0 || nLimitTime > nTime ) )
			{
				nIndex = iter->first;
				nLimitTime = nTime;
			}
		}
	}
	if ( m_nLastTeHui != nIndex )
	{
		m_nLastTeHui = nIndex;
		SendTeHuiIcon();
	}
}

bool CYunYingHD::CanShowEveryChongZhiIcon()
{
	if ( m_pPlayer->GetTotalPayGold() <= 0 )
	{
		return false;
	}
	int32_t nRecord = m_pPlayer->getRecord( 1026 );
	return nRecord == ( nRecord | 2 );
}

int32_t CYunYingHD::getEveryDayChongZhiIcon( int8_t nType )
{
	if ( nType == 3 || nType == 1 || nType == 4 )
	{
		return 17;
	}
	if ( nType == 2 )
	{
		return 52;
	}
	return 0;
}

bool CYunYingHD::HaveEveryDayChongZhiGiftCount( int8_t nType, int32_t& Count )
{
	int32_t OldRecord = 0;
	if ( nType == 3 || nType == 1 || nType == 4 )
	{
		OldRecord = m_pPlayer->getRecord( PR_EVERY_DAY_CHONG_ZHI_GIFT_RECORD );
	}
	else if ( nType == 2 )
	{
		OldRecord = m_pPlayer->getRecord( 2033 );
	}
	else
	{
		return false;
	}
	bool CanShowIcon = false;
	// Use existing CFG_DATA.GetEveryDayTable() which returns EverydayChongZhiMap
	const EverydayChongZhiMap& CfgEveryDayChongZhiMap = CFG_DATA.GetEveryDayTable();
	for ( EverydayChongZhiMap::iterator it = CfgEveryDayChongZhiMap.begin(); it != CfgEveryDayChongZhiMap.end(); ++it )
	{
		int32_t NewRecord = OldRecord | ( 1 << ( it->first - 1 ) );
		if ( OldRecord != NewRecord )
		{
			CanShowIcon = true;
			if ( m_pPlayer->GetTodayPayGold() >= it->second.NeedGold )
			{
				++Count;
			}
		}
	}
	return CanShowIcon;
}

// ========== Mobile Phone Gift ==========

int32_t CYunYingHD::OnGetMobilePhoneGift( Answer::NetPacket *inPacket )
{
	// Need DBService::CheckMobilePhoneGiftEffect for cross-server verification
	// Not available in this version; fallback to OnDBGetMobilePhoneGift directly
	return OnDBGetMobilePhoneGift( inPacket );
}

int32_t CYunYingHD::OnDBGetMobilePhoneGift( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	// Prevent duplicate claims
	if ( m_pPlayer->getRecord( 37010 ) > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	std::string platform = m_pPlayer->GetPlatform();
	const CfgMobilePhoneGift* pCfg = CFG_DATA.GetMobilePhoneGift( platform );
	if ( pCfg == NULL || pCfg->vItem.empty() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->GetBag().AddItem( pCfg->vItem, IACR_ACTIVITY ) )
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->updateRecord( 37010, 1 );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

void CYunYingHD::GetMobilePhoneGiftIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	std::string platform = m_pPlayer->GetPlatform();
	const CfgMobilePhoneGift* pCfg = CFG_DATA.GetMobilePhoneGift( platform );
	if ( pCfg != NULL && pCfg->nIcon > 0 )
	{
		IconList.push_back( GetMobilePhoneGiftIconStu( pCfg->nIcon ) );
	}
}

void CYunYingHD::SendMobilePhoneGiftIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	std::string platform = m_pPlayer->GetPlatform();
	const CfgMobilePhoneGift* pCfg = CFG_DATA.GetMobilePhoneGift( platform );
	if ( pCfg != NULL && pCfg->nIcon > 0 )
	{
		ShowIcon stu = GetMobilePhoneGiftIconStu( pCfg->nIcon );
		m_pPlayer->SendIconState( stu );
	}
}

ShowIcon CYunYingHD::GetMobilePhoneGiftIconStu( int32_t nIcon )
{
	ShowIcon stu = {};
	stu.nId = nIcon;
	stu.nState = AS_RUNNING;
	stu.nLeftTime = -1;
	return stu;
}

void CYunYingHD::GetAdultGiftIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	std::string platform = m_pPlayer->GetPlatform();
	const CfgAdultGift* pCfg = CFG_DATA.GetAdultGiftTable()->GetAdultGift( platform );
	if ( pCfg != NULL && pCfg->nIconId > 0 )
	{
		IconList.push_back( GetAdultGiftIconStu( pCfg->nIconId ) );
	}
}

void CYunYingHD::SendAdultGiftIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	std::string platform = m_pPlayer->GetPlatform();
	const CfgAdultGift* pCfg = CFG_DATA.GetAdultGiftTable()->GetAdultGift( platform );
	if ( pCfg != NULL && pCfg->nIconId > 0 )
	{
		ShowIcon stu = GetAdultGiftIconStu( pCfg->nIconId );
		m_pPlayer->SendIconState( stu );
	}
}

ShowIcon CYunYingHD::GetAdultGiftIconStu( int32_t nIconId )
{
	ShowIcon stu = {};
	stu.nId = nIconId;
	stu.nState = AS_RUNNING;
	stu.nLeftTime = -1;
	return stu;
}

void CYunYingHD::SuperMemberRecharge( int32_t nGold )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t nowTime = m_pPlayer->getNow();
	m_pPlayer->GetOperateLimit().UpdateLimitCount( 1114, nowTime );
	m_pPlayer->GetOperateLimit().AddLimitCount( 1115, nGold );
	int32_t nOldRecord = m_pPlayer->GetOperateLimit().GetLimitCount( 1116 );
	int32_t nNewRecord = m_pPlayer->GetOperateLimit().GetLimitCount( 1115 );
	if ( nNewRecord > nOldRecord )
	{
		m_pPlayer->GetOperateLimit().UpdateLimitCount( 1116, nNewRecord );
	}
}

void CYunYingHD::GetSuperMemberIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	std::string platform = m_pPlayer->GetPlatform();
	const CfgSuperMember* pCfg = CFG_DATA.GetSuperMember( platform );
	if ( pCfg != NULL && pCfg->nIcon > 0 )
	{
		ShowIcon stu = {};
		stu.nId = pCfg->nIcon;
		stu.nState = AS_RUNNING;
		stu.nLeftTime = -1;
		IconList.push_back( stu );
	}
}

// ========== Zero Buy Pet ==========

int32_t CYunYingHD::OnGetZeroBuyPetGift( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->getRecord( 37502 ) < 0 || m_pPlayer->getRecord( 37503 ) > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	const ZeroBuyPetCfg* pCfg = CFG_DATA.GetZeroBuyPetCfg();
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->nGold )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->GetBag().AddItem( pCfg->cItems, IACR_ACTIVITY ) )
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nGold, GCR_BUY_THREE_PET_LI_BAO, 0 );
	int32_t Now = m_pPlayer->getNow();
	m_pPlayer->updateRecord( 37503, Now + 259200 );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

void CYunYingHD::OnZeroBuyPetOpen()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t Now = m_pPlayer->getNow();
	m_pPlayer->updateRecord( 37502, Now + 86400 ); // 1 day
	SendZeroBuyPetIcon();
}

void CYunYingHD::SendZeroBuyPetIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( m_pPlayer->GetPlayerFunctionOpen().IsOpened( 237 ) )
	{
		m_pPlayer->SendIconState( GetZeroBuyPetIconStu() );
	}
}

void CYunYingHD::GetZeroBuyPetIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( m_pPlayer->GetPlayerFunctionOpen().IsOpened( 237 ) )
	{
		IconList.push_back( GetZeroBuyPetIconStu() );
	}
}

ShowIcon CYunYingHD::GetZeroBuyPetIconStu()
{
	ShowIcon stu = {};
	stu.nId = 122;
	stu.nState = AS_RUNNING;
	stu.nLeftTime = -1;
	return stu;
}
