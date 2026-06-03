#include "Vip.h"
#include "GameService.h"
const int32_t DAILY_SUB_EXP			= 5;		//vip卡到期后每天减得exp

CVip::CVip()
{

}

CVip::~CVip()
{
	OnCleanUp();
}

void CVip::OnCleanUp()
{		
	m_VipEndTime		= 0;		
	m_UsedCard			= 0;			
}

void CVip::OnDaySwitch( int32_t nDiffDays )
{
	if ( GetVipType() <= 0 )
	{
		SubVipExp( DAILY_SUB_EXP );
	}
	else
	{
		VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( GetVipType() );
		if ( NULL != pVip )
		{
			if ( pVip->AddVipExp > 0 )
			{
				AddVipExp( pVip->DailyAddExp );
			}
		}
	}
}

void CVip::OnUpdate( int64_t curTick )
{
	CheckVipEnd( curTick );
}

void CVip::OnLoadFromDB( const PlayerDBData& dbData )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_UsedCard		= dbData.chr.data.vip;
	m_VipEndTime	= dbData.chr.data.vip_end_time;
	m_pPlayer->sendUpdateSocialPlayerInfo(PII_VIP, GetVipType() );
	m_pPlayer->sendUpdateSocialPlayerInfo( PII_VIP_LEVEL, GetVipLevel() );
}

void CVip::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.chr.data.vip				= m_UsedCard;
	dbData.chr.data.vip_end_time	= m_VipEndTime;
}

void CVip::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_BUY_VIP );
	procList.push_back( CM_GET_VIP_GIFT );
	procList.push_back( CM_GET_VIP_CARD_GIFT );
}

int32_t	CVip::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_BUY_VIP:
		{
			return OnBuyVipCard( inPacket );
		}
	case CM_GET_VIP_GIFT:
		{
			return OnGetVipGift( inPacket );

		}
	case CM_GET_VIP_CARD_GIFT:
		{
			return OnGetVipCardGift( inPacket );
		}
	default:
		return ERR_SYETEM_ERR;
	}
}

int32_t	CVip::OnBuyVipCard( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t VipType  = inPacket->readInt8();

	if ( VipType == VT_TI_YAN_CARD )	//体验卡不能购买
	{
		return ERR_SYETEM_ERR;
	}

	VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( VipType );
	if ( NULL == pVip )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pVip->NeedGold <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pVip->NeedGold, GCR_BUY_VIP_CARD, VipType ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( IsUsedTiYanCard() )
	{
		m_pPlayer->updateRecord( RP_IS_USED_VIP_TI_YAN_CARD, 0 );
	}
	int8_t OldVipType = GetVipType();
	AddVipTime( pVip->AddVipTime );
	SetVipUsed( VipType );
	AddVipExp( pVip->AddVipExp );
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), VipType );
	if ( OldVipType > VipType )
	{
		BuyGongGao( BCI_VIP_GONG_GAO_2, OldVipType, GetVipLevel() );
	}
	else
	{
		BuyGongGao( BCI_VIP_GONG_GAO_1, VipType, GetVipLevel() );
	}
	SendVipGiftIcon();
	return ERR_OK;
}

int32_t	CVip::OnGetVipCardGift( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->getRecord( RP_GET_VIP_CARD_GIFT) > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( GetVipType() );
	if ( NULL == pVip )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pVip->Items.size() > 0 )
	{
		if ( !m_pPlayer->GetBag().AddItemsAndEggs( pVip->Items, IACR_VIP_CARD_GIFT ) )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->updateRecord( RP_GET_VIP_CARD_GIFT, 1 );
		SendVipInfo();
		SendVipGiftIcon();
	}
	return ERR_SYETEM_ERR;
}

void CVip::TiYanVipGongGao()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL != packet)
	{
		packet->writeInt32( BCI_VIP_GONG_GAO_3 );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(packet);
	}
}

void CVip::BuyGongGao( int32_t GongGaoId, int8_t VipType, int8_t VipLevel )
{

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL != packet)
	{
		packet->writeInt32( GongGaoId );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeInt8( VipType );
		packet->writeInt8( VipLevel );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(packet);
	}
}

int32_t CVip::OnGetVipGift( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_OK;
	}
	int8_t VipGiftLevel		= inPacket->readInt8();
	if ( VipGiftLevel <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( VipGiftLevel > GetVipLevel() )
	{
		return ERR_SYETEM_ERR;
	}
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipGiftLevel );
	if ( NULL == pVipCfg )
	{
		return ERR_SYETEM_ERR;
	}
// 	if ( m_pPlayer->GetBag().GetbagFreeSize() < static_cast<int32_t>( pVipCfg->Item.size() ) )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
	int32_t oldRecord = m_pPlayer->getRecord( PR_VIP_GIFT_RECORD );
	int32_t NewRecord = oldRecord | ( 1 << ( VipGiftLevel-1 ) );
	if ( oldRecord == NewRecord )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( pVipCfg->Item, IACR_GET_VIP_GIFT ) )
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->updateRecord( PR_VIP_GIFT_RECORD, NewRecord );
	SendVipInfo();
	return ERR_OK;
}

void CVip::AddVipExp( int32_t VipExp )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t OldVipLevel = GetVipLevel();
	m_pPlayer->GetOperateLimit().AddLimitCount( PR_VIP_EXP, VipExp );
	m_pPlayer->sendUpdateSocialPlayerInfo(PII_VIP, GetVipType() );
	m_pPlayer->sendUpdateSocialPlayerInfo( PII_VIP_LEVEL, GetVipLevel() );
	int32_t VipLevel = GetVipLevel();
	if (  VipLevel > m_pPlayer->getRecord( PR_MAX_VIP_LEVEL ) )
	{
		m_pPlayer->updateRecord( PR_MAX_VIP_LEVEL, VipLevel );
	}
	if ( OldVipLevel != VipLevel )
	{
		m_pPlayer->setSyncStatusFlag();
	}
	SendVipInfo();
	m_pPlayer->recalcAttr();
}

void CVip::SubVipExp( int32_t VipExp )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( 1 );	//vip最多降到一级
	if ( NULL == pVipCfg )
	{
		return;
	}	
	if ( m_pPlayer->getRecord( PR_VIP_EXP) > pVipCfg->NeedVipExp )
	{
		m_pPlayer->GetOperateLimit().AddLimitCount( PR_VIP_EXP, -1 * DAILY_SUB_EXP );
		if ( m_pPlayer->getRecord( PR_VIP_EXP) < pVipCfg->NeedVipExp )
		{
			m_pPlayer->updateRecord( PR_VIP_EXP, pVipCfg->NeedVipExp );
		}
	}
	m_pPlayer->sendUpdateSocialPlayerInfo(PII_VIP, GetVipType());
	m_pPlayer->sendUpdateSocialPlayerInfo( PII_VIP_LEVEL, GetVipLevel() );
}

int32_t	CVip::GetMaxVipLevel() const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	return m_pPlayer->getRecord( PR_MAX_VIP_LEVEL );
}

int32_t CVip::GetAddPetDeportCount()
{
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( GetMaxVipLevel() );
	if ( NULL == pVipCfg )
	{
		return 0;
	}
	if ( pVipCfg->PetDeport > PET_VIP_ADD_DEPORT_SIZE || pVipCfg->PetDeport <= 0 )
	{
		return 0;
	}
	return pVipCfg->PetDeport;
};

int32_t CVip::GetHallOfFameBuyTimes()
{
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( GetMaxVipLevel() );
	if ( NULL == pVipCfg )
	{
		return 0;
	}

	return pVipCfg->HallOfFameBuyTimes;
};

bool CVip::CanSiteRevive()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( GetVipLevel() );
	if ( NULL == pVipCfg )
	{
		return false;
	}
	if ( pVipCfg->SiteRevive > m_pPlayer->getRecord( RP_VIP_SITEREVIVE_TIMES ) )
	{
		return true;
	}
	return false;
}

int8_t	CVip::GetVipLevel()
{
	if ( GetVipType() <= 0 )
	{
		return 0;
	}
	int8_t VipLevel = CFG_DATA.GetVipTable().GetVipLevel( GetVipExp() );
	return VipLevel;
}

int32_t	CVip::GetVipExp()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	int32_t TiYanCardExp = 0;
	if ( IsUsedTiYanCard() )
	{
		VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( VT_TI_YAN_CARD );
		if ( NULL == pVip )
		{
			return ERR_SYETEM_ERR;
		}
		TiYanCardExp = pVip->AddVipExp;
	}
	return m_pPlayer->getRecord( PR_VIP_EXP ) + TiYanCardExp;
}

void CVip::AddVipTime( int32_t Seconds )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t Now = m_pPlayer->getNow();
	if ( m_VipEndTime < Now )
	{
		m_VipEndTime = Now + Seconds;
	}
	else
	{
		m_VipEndTime += Seconds;
	}
}
	
int32_t	CVip::GetVipEndTime()
{
	return m_VipEndTime;
}

int8_t CVip::GetVipType()
{
	if ( GetVipEndTime() <= 0 )
	{
		return 0;
	}
	int8_t VipType = 0;
	int8_t i = 0;
	while( i < VIP_CARD_TYPE_COUNT )
	{
		if ( ( ( m_UsedCard >> i ) & 1 )> 0 )
		{
			VipType = i + 1;
		}
		i++;
	}
	return VipType;
}

void CVip::SetVipUsed( int8_t VipId )
{
	m_UsedCard |= 1 << ( VipId - 1);
}

bool CVip::UseVipTiYanCard()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( VT_TI_YAN_CARD );
	if ( NULL == pVip )
	{
		return false;
	}
	if ( GetVipType() <= 0 )
	{
		m_pPlayer->updateRecord( RP_IS_USED_VIP_TI_YAN_CARD, 1 );
	}
	AddVipTime( pVip->AddVipTime );
	SetVipUsed( VT_TI_YAN_CARD );
	int32_t VipLevel = GetVipLevel();
	if (  VipLevel > m_pPlayer->getRecord( PR_MAX_VIP_LEVEL ) )
	{
		m_pPlayer->updateRecord( PR_MAX_VIP_LEVEL, VipLevel );
	}
	SendVipInfo();
	m_pPlayer->recalcAttr();
	TiYanVipGongGao();
	return true;
}

void CVip::AddVipAttr()
{
	int8_t i = 0;
	while( i < VIP_CARD_TYPE_COUNT )
	{
		if ( ( ( m_UsedCard >> i ) & 1) > 0 ) 
		{
			VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( i+1 );
			if ( NULL == pVip )
			{
				i++;
				continue;
			}
			AddAttrList::iterator it = pVip->AddAttr.begin();
			for ( ;it != pVip->AddAttr.end(); ++it )
			{
				m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>(it->m_nAddAttrType), it->m_nAddAttrValue );
			}
		}
		i++;
	}
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( GetVipLevel() );
	if ( NULL == pVipCfg )
	{
		return;
	}
	AttrAddonVector::iterator it = pVipCfg->AtttVector.begin();
	for ( ; it != pVipCfg->AtttVector.end(); ++ it )
	{
		m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>(it->index), it->addon );
	}
}

bool CVip::IsUsedTiYanCard()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( m_pPlayer->getRecord( RP_IS_USED_VIP_TI_YAN_CARD ) > 0 )
	{
		return true;
	}
	return false;
}

void CVip::CheckVipEnd( int64_t curTick )
{
	if ( m_VipEndTime > 0 && NULL != m_pPlayer )
	{
		if ( curTick - m_LastUpdataTick >= 1000 )
		{
			m_LastUpdataTick = curTick;
			int32_t Now = m_pPlayer->getNow();
			if ( Now - 10 * 60 > m_pPlayer->getRecord( RP_VIP_LAST_ADD_EXP_TIME ) )
			{
				 m_pPlayer->updateRecord( RP_VIP_LAST_ADD_EXP_TIME,Now );
				 VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( GetVipType() );
				 if ( NULL != pVip )
				 {
					m_pPlayer->addExp( pVip->AddPlayerExp );
					m_pPlayer->GetCharPet().OnAddExp( pVip->AddPetExp, false );
				 }

			}
			if (  Now > m_VipEndTime )
			{
				if ( IsUsedTiYanCard() )
				{
					m_pPlayer->updateRecord( RP_IS_USED_VIP_TI_YAN_CARD, 0 );
				}
				m_VipEndTime = 0;
				SendVipInfo();
				m_pPlayer->sendUpdateSocialPlayerInfo(PII_VIP, GetVipType() );
				m_pPlayer->sendUpdateSocialPlayerInfo( PII_VIP_LEVEL, GetVipLevel() );
			}

		}
	}
}

int32_t CVip::GetExpRate()
{
	if ( GetVipEndTime() <= 0 )
	{
		return 0;
	}
	VipCardCfg* pVipCard = CFG_DATA.GetVipCardCfg( GetVipType() );
	if ( NULL == pVipCard )
	{
		return 0;
	}
	VipCfg*  pVip = CFG_DATA.GetVipTable().GetVipCfg( GetVipLevel() );
	if( NULL == pVip )
	{
		return 0;
	}
	int32_t ExpRate = 0;
	if ( pVip->ExpRate > 0 )
	{
		ExpRate += pVip->ExpRate;
	}
	if ( pVipCard->ExpRate > 0 )
	{
		ExpRate += pVipCard->ExpRate;
	}
	return ExpRate;
}

int32_t	CVip::AddDailyTaskTimes()
{
	VipCfg*  pVip = CFG_DATA.GetVipTable().GetVipCfg( GetVipLevel() );
	if( NULL == pVip )
	{
		return 0;
	}
	return pVip->DailyTaskTimes;
}

int32_t CVip::GetOpenBagRate()
{
	VipCfg*  pVip = CFG_DATA.GetVipTable().GetVipCfg( GetVipLevel() );
	if( NULL == pVip )
	{
		return 0;
	}
	return  pVip->OpenBag;
}

bool CVip::CanFreeFlying()
{
	if ( GetVipType() <= 0 )
	{
		return false;
	}
	return true;
}

void CVip::SendVipInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_VIP_INFO );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_UsedCard );
	packet->writeInt32( m_VipEndTime );
	packet->writeInt32( GetVipExp() );
	packet->writeInt32( m_pPlayer->getRecord( PR_VIP_GIFT_RECORD ) );
	packet->writeInt8( GetMaxVipLevel() );
	packet->writeInt8( (int8_t)m_pPlayer->getRecord( RP_GET_VIP_CARD_GIFT) );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CVip::SendVipGiftIcon()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetVipGiftIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

ShowIcon CVip::GetVipGiftIconStu()
{
	ShowIcon stu = {};
	if ( NULL == m_pPlayer )
	{
		return stu;
	}
	stu.nId			= VIP_CARD_ICON;
	stu.nState		= AS_RUNNING;
	stu.nLeftTime	= -1;
	if ( m_pPlayer->getRecord( RP_GET_VIP_CARD_GIFT ) <= 0 && GetVipType() > 1 )
	{
		stu.IconRight	= 1;
	}
	return stu;
}

void CVip::	GetVipGiftIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	IconList.push_back( GetVipGiftIconStu() );
}