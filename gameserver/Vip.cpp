#include "Vip.h"
#include "CfgData.h"
#include "GameService.h"
#include "DBService.h"
#include "CVipClub.h"
#include "EquipManager.h"
#include "EquipBack.h"
#include "Bag.h"
#include "SpecialEquip.h"
#include "ChrTask.h"
#include "Player.h"
#include "Map.h"
#include "share/Shared.h"

using namespace Answer;

CVip::CVip()
	: m_PlatinumVipEndTime(0)
	, m_DiamVipEndTime(0)
	, m_StarVipEndTime(0)
	, m_UsedCard(0)
	, m_LastUpdataTick(0)
	, m_Club(0)
	, m_ClubDropTimes(0)
	, m_BuyTimes(0)
	, m_nVip7Time(0)
	, m_nVip10Time(0)
{
}

CVip::~CVip()
{
}

void CVip::OnCleanUp()
{
	m_LastUpdataTick = 0;
	m_PlatinumVipEndTime = 0;
	m_StarVipEndTime = 0;
	m_DiamVipEndTime = 0;
	m_Club = 0;
	m_ClubDropTimes = 0;
	m_BuyTimes = 0;
	m_nVip7Time = 0;
	m_nVip10Time = 0;
	m_UsedCard = 0;
	m_VipLuckyDropMap.clear();
}

void CVip::OnLoadFromDB( const PlayerDBData& dbData )
{
	if ( !m_pPlayer )
		return;

	OnLoadVipEndTime( dbData.m_vipData.m_VipEndTime );
	int8_t VipType = GetVipType();
	m_pPlayer->sendUpdateSocialPlayerInfo( PlayerInfoIndex::PII_VIP, VipType );
	int8_t VipLevel = GetVipLevel();
	m_pPlayer->sendUpdateSocialPlayerInfo( PlayerInfoIndex::PII_VIP_LEVEL, VipLevel );

	// 初始化VipLuckyDropMap（1~14级）
	for ( int i = 1; i <= 14; ++i )
	{
		VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( i );
		if ( pVipCfg )
		{
			int32_t UpperTimes1 = 0;
			int32_t UpperTimes2 = 0;
			VipCfg* UpperCfg = CFG_DATA.GetVipTable().GetVipCfg( i - 1 );
			if ( UpperCfg )
			{
				UpperTimes1 = UpperCfg->Luck1;
				UpperTimes2 = UpperCfg->Luck2;
			}
			m_VipLuckyDropMap[i].CanDropOrdinaryTimes = pVipCfg->Luck1 - UpperTimes1;
			m_VipLuckyDropMap[i].CanDropSpecialTimes = pVipCfg->Luck2 - UpperTimes2;
			if ( i == 1 )
			{
				m_VipLuckyDropMap[i].CanDropOrdinaryTimes += m_pPlayer->getRecord( 1906 );
				m_VipLuckyDropMap[i].CanDropSpecialTimes += m_pPlayer->getRecord( 1907 );
			}
		}
	}

	std::string p_String( dbData.m_vipData.m_DropString );
	LoadDropString( p_String );

	m_Club = dbData.m_vipData.m_Club;
	m_ClubDropTimes = dbData.m_vipData.m_ClubDropTimes;
	m_BuyTimes = dbData.m_vipData.m_BuyTimes;
	m_nVip7Time = dbData.m_vipData.m_nVip7Time;
	m_nVip10Time = dbData.m_vipData.m_nVip10Time;
}

void CVip::OnSaveToDB( PlayerDBData& dbData )
{
	std::string strVipEndTime = OnSaveVipEndTime();
	dbData.m_vipData.m_VipEndTime = strVipEndTime;
	dbData.m_vipData.m_level = GetVipLevel();
	std::string strDropString = SaveDropString();
	dbData.m_vipData.m_DropString = strDropString;
	dbData.m_vipData.m_Club = m_Club;
	dbData.m_vipData.m_ClubDropTimes = m_ClubDropTimes;
	dbData.m_vipData.m_BuyTimes = m_BuyTimes;
	dbData.m_vipData.m_nVip7Time = m_nVip7Time;
	dbData.m_vipData.m_nVip10Time = m_nVip10Time;
}

void CVip::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 463 );	// OnBuyVipCard
	procList.push_back( 464 );	// OnGetVipGift
	procList.push_back( 465 );	// OnGetVipCardGift
	procList.push_back( 466 );	// OnBuyAllVipCard
	procList.push_back( 467 );	// OnEnterClub
	procList.push_back( 468 );	// OnBuyDropTimes
	procList.push_back( 345 );	// SendClubInfo
}

int32_t CVip::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return 2;

	switch ( nProcId )
	{
	case 463: return OnBuyVipCard( inPacket );
	case 464: return OnGetVipGift( inPacket );
	case 465: return OnGetVipCardGift( inPacket );
	case 466: return OnBuyAllVipCard( inPacket );
	case 467: return OnEnterClub( inPacket );
	case 468: return OnBuyDropTimes( inPacket );
	case 345: SendClubInfo(); return 2;
	default:  return 2;
	}
}

void CVip::OnUpdate( int64_t curTick )
{
	if ( curTick - m_LastUpdataTick > 60000 )
	{
		CheckVipEnd( curTick );
		m_LastUpdataTick = curTick;
	}
}

void CVip::OnDaySwitch( int32_t nDiffDays )
{
	SendVipInfo();
	if ( IsClub() )
		m_ClubDropTimes = 1;
	m_BuyTimes = 0;
	SendClubInfo();
}

// ========== VIP Level & Exp ==========

int8_t CVip::GetVipLevel()
{
	int32_t VipExp = GetVipExp();
	return CFG_DATA.GetVipTable().GetVipLevel( VipExp );
}

int32_t CVip::GetVipExp()
{
	if ( m_pPlayer )
		return m_pPlayer->getRecord( 1020 );
	return 0;
}

void CVip::AddVipExp( int32_t VipExp )
{
	if ( !m_pPlayer )
		return;

	int8_t OldVipLevel = GetVipLevel();
	CExtOperateLimit& OperateLimit = m_pPlayer->GetOperateLimit();
	OperateLimit.AddLimitCount( 1020, VipExp );
	int8_t NewVipLevel = GetVipLevel();

	if ( OldVipLevel != NewVipLevel )
	{
		CSpecialEquip* pSpecialEquip = m_pPlayer->GetCSpecialEquip();
		pSpecialEquip->SendSpecialEquipIcon();
		m_pPlayer->setSyncStatusFlag();
		m_pPlayer->sendUpdateSocialPlayerInfo( PlayerInfoIndex::PII_VIP_LEVEL, NewVipLevel );

		if ( IsClub() )
		{
			int32_t Now = m_pPlayer->getNow();
			std::string p_name = m_pPlayer->getName();
			CharId_t Cid = m_pPlayer->getCid();
			VIP_CLUB->UpdateClubData( Cid, p_name, NewVipLevel, Now );

			if ( OldVipLevel <= 6 && NewVipLevel > 6 )
			{
				m_nVip7Time = m_pPlayer->getNow();
				SendClubInfo();
			}
			if ( OldVipLevel <= 9 && NewVipLevel > 9 )
			{
				m_nVip10Time = m_pPlayer->getNow();
				SendClubInfo();
			}
		}

		m_pPlayer->recalcAttr( 0, 0 );

		// 首次成为VIP广播
		if ( !OldVipLevel )
		{
			GameService* pGS = GAME_SERVICE;
			Answer::NetPacket* packet = pGS->popNetpacket( 0, Answer::PackType::PACK_DISPATCH, 0x2CD6 );
			if ( packet )
			{
				packet->writeInt32( 448 );
				packet->writeInt64( m_pPlayer->getCid() );
				packet->writeUTF8( m_pPlayer->getName() );
				uint32_t WOffset = packet->getWOffset();
				packet->setSize( WOffset );
				pGS->worldBroadcast( 0, packet );
			}
		}
	}
	SendVipInfo();
}

void CVip::SubVipExp( int32_t VipExp )
{
	// SubVipExp - unused in 2019
}

int32_t CVip::GetVipEndTime()
{
	// 不再使用单字段，返回最大值
	int32_t Now = m_pPlayer->getNow();
	int32_t MaxEnd = 0;
	if ( m_PlatinumVipEndTime > Now && m_PlatinumVipEndTime > MaxEnd ) MaxEnd = m_PlatinumVipEndTime;
	if ( m_DiamVipEndTime > Now && m_DiamVipEndTime > MaxEnd ) MaxEnd = m_DiamVipEndTime;
	if ( m_StarVipEndTime > Now && m_StarVipEndTime > MaxEnd ) MaxEnd = m_StarVipEndTime;
	return MaxEnd;
}

int32_t CVip::AddDailyTaskTimes()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->DailyTaskTimes;
	return 0;
}

int32_t CVip::GetMaxVipLevel() const
{
	return 15;
}

int8_t CVip::GetVipType()
{
	if ( !m_pPlayer )
		return 0;
	int32_t Now = m_pPlayer->getNow();
	if ( m_PlatinumVipEndTime > Now ) return 1;
	if ( m_DiamVipEndTime > Now ) return 2;
	if ( m_StarVipEndTime > Now ) return 3;
	return 0;
}

bool CVip::GetVipFlg( int8_t VipType )
{
	if ( !m_pPlayer )
		return false;
	int32_t Now = m_pPlayer->getNow();
	switch ( VipType )
	{
	case 1: return m_PlatinumVipEndTime > Now;
	case 2: return m_DiamVipEndTime > Now;
	case 3: return m_StarVipEndTime > Now;
	}
	return false;
}

// ========== VIP Card Operations ==========

void CVip::AddVipTime( int8_t VipType, int32_t Seconds )
{
	if ( !m_pPlayer )
		return;
	int32_t Now = m_pPlayer->getNow();
	switch ( VipType )
	{
	case 1:
		m_PlatinumVipEndTime = ( m_PlatinumVipEndTime <= Now ) ? Seconds + Now : Seconds + m_PlatinumVipEndTime;
		break;
	case 2:
		m_DiamVipEndTime = ( m_DiamVipEndTime <= Now ) ? Seconds + Now : Seconds + m_DiamVipEndTime;
		break;
	case 3:
		m_StarVipEndTime = ( m_StarVipEndTime <= Now ) ? Seconds + Now : Seconds + m_StarVipEndTime;
		break;
	}
}

int32_t CVip::OnBuyVipCard( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 2;

	int8_t VipType = inPacket->readInt8();
	VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( VipType );
	if ( !pVip )
		return 2;
	if ( GetVipLevel() < pVip->VipLevel )
		return 2;

	int32_t NeedGold = GetVipFlg( VipType ) ? pVip->ReNeedGold : pVip->NeedGold;
	if ( NeedGold <= 0 )
		return 2;
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, NeedGold, GCR_BUY_VIP_CARD, VipType ) )
		return 2;

	AddVipTime( VipType, pVip->AddVipTime );
	m_pPlayer->recalcAttr( 0, 0 );
	m_pPlayer->setSyncStatusFlag();

	uint16_t Proc = inPacket->getProc();
	int16_t GateIndex = m_pPlayer->getGateIndex();
	int8_t ConnId = m_pPlayer->getConnId();
	GAME_SERVICE->replySuccess( ConnId, GateIndex, Proc, VipType );

	int8_t VipLevel = GetVipLevel();
	BuyGongGao( 22, VipType, VipLevel );
	ChrTask& Task = m_pPlayer->GetTask();
	Task.updateTaskCount( 22, 0 );
	SendVipInfo();
	return 0;
}

int32_t CVip::OnBuyAllVipCard( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 2;

	int32_t NeedGold = 0;
	int32_t NeeVipLevel = 0;
	for ( int i = 0; i <= 2; ++i )
	{
		VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( i + 1 );
		if ( pVip )
		{
			NeedGold += pVip->NeedGold;
			if ( pVip->VipLevel > NeeVipLevel )
				NeeVipLevel = pVip->VipLevel;
		}
	}
	if ( GetVipLevel() < NeeVipLevel )
		return 2;
	if ( NeedGold <= 0 )
		return 2;
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, 19064, GCR_BUY_VIP_CARD, 0 ) )
		return 2;

	for ( int i = 0; i <= 2; ++i )
	{
		VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( i + 1 );
		if ( pVip )
		{
			AddVipTime( i + 1, pVip->AddVipTime );
			int8_t VipLevel = GetVipLevel();
			BuyGongGao( 22, i + 1, VipLevel );
		}
	}
	m_pPlayer->recalcAttr( 0, 0 );
	m_pPlayer->setSyncStatusFlag();

	uint16_t Proc = inPacket->getProc();
	int16_t GateIndex = m_pPlayer->getGateIndex();
	int8_t ConnId = m_pPlayer->getConnId();
	GAME_SERVICE->replySuccess( ConnId, GateIndex, Proc, 0 );
	ChrTask& Task = m_pPlayer->GetTask();
	Task.updateTaskCount( 22, 0 );
	SendVipInfo();
	return 0;
}

int32_t CVip::OnGetVipCardGift( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 2;

	int8_t Type = inPacket->readInt8();
	if ( !GetVipFlg( Type ) )
		return 2;

	int32_t Record = m_pPlayer->getRecord( 2018 );
	int32_t NewRecord = Record | ( 1 << ( Type - 1 ) );
	if ( NewRecord == Record )
		return 10002;

	VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( Type );
	if ( !pVip )
		return 2;

	if ( pVip->Money > 0 )
		m_pPlayer->AddCurrency( CURRENCY_BIND_MONEY, pVip->Money, MCR_VIP_CARD, 0 );
	if ( pVip->TianShuJinHua > 0 )
	{
		CFaBao* PlayerFaBao = m_pPlayer->GetPlayerFaBaoPtr();
		PlayerFaBao->AddFaBaoRes( (FaBaoResourceType)0, pVip->TianShuJinHua );
	}
	if ( pVip->WeiWang > 0 )
		m_pPlayer->AddCurrency( CURRENCY_HONOR, pVip->WeiWang, MCR_VIP_CARD, 0 );

	m_pPlayer->updateRecord( 2018, NewRecord );
	SendVipInfo();
	return 0;
}

// ========== VIP Gift ==========

int32_t CVip::OnGetVipGift( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 0;

	int8_t VipGiftLevel = inPacket->readInt8();
	if ( VipGiftLevel <= 0 )
		return 2;
	if ( GetVipLevel() < VipGiftLevel )
		return 2;

	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipGiftLevel );
	if ( !pVipCfg )
		return 2;

	int32_t oldRecord = m_pPlayer->getRecord( 1021 );
	int32_t NewRecord = oldRecord | ( 1 << ( VipGiftLevel - 1 ) );
	if ( oldRecord == NewRecord )
		return 10002;

	CExtCharBag* Bag = m_pPlayer->GetBag();
	if ( !Bag->AddItem( &pVipCfg->Item, ITEM_CHANGE_REASON::ICR_VIP_GIFT ) )
		return 2;

	m_pPlayer->updateRecord( 1021, NewRecord );
	SendVipInfo();

	// 广播领取VIP礼包
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket( 0, Answer::PackType::PACK_DISPATCH, 0x2CD6 );
	if ( packet )
	{
		packet->writeInt32( 449 );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeUTF8( m_pPlayer->getName() );
		uint32_t WOffset = packet->getWOffset();
		packet->setSize( WOffset );
		pGS->worldBroadcast( 0, packet );
	}
	return 0;
}

void CVip::GetVipGiftIconState( IconStateList& IconList )
{
	IconList.clear();
	for ( int i = 1; i <= GetVipLevel(); i++ )
	{
		IconState icon;
		icon.nIconId = i;
		icon.bState = true;
		IconList.push_back( icon );
	}
}

void CVip::SendVipGiftIcon()
{
	if ( !m_pPlayer )
		return;

	ShowIcon icon = GetVipGiftIconStu();
	int8_t connid = m_pPlayer->getConnId();
	NetPacket* outPacket = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( !outPacket )
		return;

	outPacket->writeInt32( icon.nId );
	outPacket->writeInt8( icon.bState ? 1 : 0 );
	outPacket->setSize( outPacket->getWOffset() );
	GAME_SERVICE.sendPacket( connid, outPacket );
}

ShowIcon CVip::GetVipGiftIconStu()
{
	ShowIcon icon;
	icon.nIconId = 0;
	icon.bState = false;
	int8_t VipLevel = GetVipLevel();
	int32_t Record = m_pPlayer ? m_pPlayer->getRecord( 1021 ) : 0;
	for ( int i = 1; i <= VipLevel; i++ )
	{
		if ( !( Record & ( 1 << ( i - 1 ) ) ) )
		{
			icon.nIconId = i;
			icon.bState = true;
			return icon;
		}
	}
	return icon;
}

// ========== VIP Attr ==========

void CVip::AddVipAttr()
{
	// VIP卡属性
	for ( int i = 0; i <= 2; ++i )
	{
		if ( !GetVipFlg( i + 1 ) )
			continue;
		VipCardCfg* pVip = CFG_DATA.GetVipCardCfg( i + 1 );
		if ( !pVip )
			continue;
		for ( AddAttrList::iterator it = pVip->AddAttr.begin(); it != pVip->AddAttr.end(); ++it )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue );
		}
	}

	// VIP等级属性
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
	{
		for ( AttrAddonVector::iterator it = pVipCfg->AtttVector.begin(); it != pVipCfg->AtttVector.end(); ++it )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)it->index, it->addon );
		}
	}
}

int32_t CVip::GetExpRate()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->ExpRate;
	return 0;
}

int32_t CVip::GetOpenBagRate()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->OpenBag;
	return 0;
}

int32_t CVip::GetAddPetDeportCount()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->PetDeport;
	return 0;
}

int32_t CVip::GetHallOfFameBuyTimes()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->HallOfFameBuyTimes;
	return 0;
}

int32_t CVip::GetVipEquipBackRate()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->EquipBackRate;
	return 2;
}

int32_t CVip::GetTreasureTimes()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->TreasureTimes;
	return 0;
}

int32_t CVip::GetCycleTowerTimes()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->CycleTower;
	return 0;
}

int32_t CVip::GetStorePage()
{
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( pVipCfg )
		return pVipCfg->StorePage;
	return 0;
}

bool CVip::CanFreeFlying()
{
	// VIP特权：免费飞行
	return GetVipLevel() >= 3;
}

bool CVip::CanSiteRevive()
{
	if ( !m_pPlayer )
		return false;
	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( !pVipCfg )
		return false;
	return m_pPlayer->getRecord( 2021 ) < pVipCfg->SiteRevive;
}

bool CVip::HaveVipPrivilege()
{
	if ( !m_pPlayer )
		return false;
	int32_t Now = m_pPlayer->getNow();
	if ( m_DiamVipEndTime > Now ) return true;
	if ( m_PlatinumVipEndTime > Now ) return true;
	if ( m_StarVipEndTime > Now ) return true;
	return false;
}

bool CVip::CanAuction()
{
	int32_t nDay = CFG_DATA.getServerDiffDay( SVT_NORMAL ) + 1;
	if ( nDay <= 10 )
	{
		if ( nDay > 1 && GetVipLevel() <= 0 )
			return false;
	}
	else if ( GetVipLevel() <= 1 )
	{
		return false;
	}
	return true;
}

bool CVip::UseVipTiYanCard()
{
	if ( IsUsedTiYanCard() )
		return false;
	SetVipUsed( 1 );
	TiYanVipGongGao();
	return true;
}

bool CVip::IsUsedTiYanCard()
{
	return ( m_UsedCard & 0x01 ) != 0;
}

void CVip::SetVipUsed( int8_t VipId )
{
	m_UsedCard |= ( 1 << ( VipId - 1 ) );
}

void CVip::TiYanVipGongGao()
{
	if ( !m_pPlayer ) return;
	int8_t VipLevel = GetVipLevel();
	BuyGongGao( 23, 0, VipLevel );
}

// ========== VIP Club ==========

int32_t CVip::OnEnterClub( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 2;
	if ( GetVipLevel() <= 0 )
		return 2;

	m_Club = 1;
	m_ClubDropTimes = 1;

	int32_t Now = m_pPlayer->getNow();
	int32_t VipLevel = GetVipLevel();
	std::string p_name = m_pPlayer->getName();
	CharId_t Cid = m_pPlayer->getCid();
	VIP_CLUB->UpdateClubData( Cid, p_name, VipLevel, Now );
	SendClubInfo();

	int32_t nVipLevel = GetVipLevel();
	if ( nVipLevel > 6 )
		m_nVip7Time = m_pPlayer->getNow();
	if ( nVipLevel > 9 )
		m_nVip10Time = m_pPlayer->getNow();

	// 世界广播加入Club
	int8_t ConnId = m_pPlayer->getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket( ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6 );
	if ( packet )
	{
		packet->writeInt32( 3008 );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeUTF8( m_pPlayer->getName() );
		uint32_t WOffset = packet->getWOffset();
		packet->setSize( WOffset );
		int8_t v8 = m_pPlayer->getConnId();
		pGS->worldBroadcast( v8, packet );
	}
	return 0;
}

int32_t CVip::OnBuyDropTimes( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 2;

	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( !pVipCfg )
		return 2;
	if ( m_BuyTimes >= pVipCfg->ClubBuyTimes )
		return 2;

	int32_t nPrice = 0;
	if ( m_BuyTimes == 0 )
		nPrice = 500;
	else if ( m_BuyTimes == 1 )
		nPrice = 1000;
	else if ( m_BuyTimes == 2 )
		nPrice = 2000;
	else
		return 2;

	if ( m_pPlayer->DecCurrency( CURRENCY_GOLD, nPrice, GCR_VIP_BUY_DROP_TIMES, 0 ) )
	{
		++m_BuyTimes;
		++m_ClubDropTimes;
		SendClubInfo();
	}
	return 2;
}

void CVip::AddClubDropTime()
{
	if ( IsClub() && m_ClubDropTimes <= 0 )
	{
		m_ClubDropTimes = 1;
		SendClubInfo();
	}
}

void CVip::GetClubDrop( int32_t Mid )
{
	if ( !m_pPlayer )
		return;
	if ( m_Club <= 0 || m_ClubDropTimes <= 0 )
		return;

	CVipClub* pClub = VIP_CLUB;
	int32_t nLevel = pClub->GetClubLevel();
	const CVipClubLuckyDrop* pCfg = CFG_DATA.GetCVipClubLuckyDrop( nLevel - 1 );
	if ( !pCfg )
		return;

	int32_t ClubRate = RANDOM->generate( 1, 1000 );
	if ( pCfg->nRate < ClubRate )
		return;

	// 计算总概率
	int32_t MaxRate = 0;
	for ( std::list<RateItem>::const_iterator it = pCfg->lRateItemList.begin();
	      it != pCfg->lRateItemList.end(); ++it )
	{
		MaxRate += it->nRate;
	}

	MemChrBag stu;
	memset( &stu, 0, sizeof( stu ) );
	int32_t GongGaoId = 0;
	int32_t nRand = RANDOM->generate( 1, MaxRate );

	for ( std::list<RateItem>::const_iterator iter = pCfg->lRateItemList.begin();
	      iter != pCfg->lRateItemList.end(); ++iter )
	{
		if ( iter->nRate >= nRand )
		{
			stu.itemId = iter->nItemId;
			stu.itemClass = iter->nItemClass;
			stu.itemCount = iter->nItemCount;
			stu.bind = iter->nBind;
			GongGaoId = iter->nGongGaoId;
			break;
		}
		nRand -= iter->nRate;
	}

	if ( stu.itemId <= 0 || stu.itemCount <= 0 )
		return;

	// 装备类处理
	if ( stu.itemClass == 2 )
	{
		int32_t mapid = m_pPlayer->getMapId();
		std::string p_name = m_pPlayer->getName();
		CharId_t nCreaterId = m_pPlayer->getCid();
		int32_t Sid = m_pPlayer->getSid();
		int8_t ConnId = m_pPlayer->getConnId();

		MemEquip equip = EQUIP_MANAGER.CreateMemEquip( ConnId, 1474, stu.itemId, Sid, nCreaterId, p_name, mapid, Mid, 0, 0, 0 );
		if ( equip.id > 0 )
		{
			EQUIP_MANAGER.SendPlayerEquipInfo( m_pPlayer, &equip );
			stu.srcId = equip.id;
		}

		const CfgEquip* pEquip = CFG_DATA.getEquip( stu.itemId );
		if ( pEquip && pEquip->m_backIndex > 0 )
		{
			EQUIP_BACK.KiaFuEquipBack( pEquip->m_backIndex, stu.itemId, Mid, m_pPlayer );
		}
	}

	CExtCharBag* Bag = m_pPlayer->GetBag();
	if ( !Bag->AddItem( &stu, ITEM_CHANGE_REASON::ICR_CLUB_DROP ) )
	{
		// 邮件发送
		std::stringstream ss;
		ss << stu.itemId;
		std::string Param = ss.str();
		CharId_t Cid = m_pPlayer->getCid();
		DB_SERVICE.OnSendSysMail( m_pPlayer->getConnId(), Cid, 6611, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP, &Param, 0 );
	}

	--m_ClubDropTimes;
	SendClubInfo();

	// 公告广播
	if ( GongGaoId > 0 )
	{
		GameService* pGS = GAME_SERVICE;
		Answer::NetPacket* packet = pGS->popNetpacket( 0, Answer::PackType::PACK_DISPATCH, 0x2CD6 );
		if ( packet )
		{
			packet->writeInt32( GongGaoId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( m_pPlayer->getMapId() );
			packet->writeInt32( Mid );
			packet->writeInt8( stu.itemClass );
			packet->writeInt32( stu.itemId );
			uint32_t WOffset = packet->getWOffset();
			packet->setSize( WOffset );
			pGS->worldBroadcast( 0, packet );
		}
	}

	// 掉落结果通知
	int8_t v31 = m_pPlayer->getConnId();
	GameService* pGS2 = GAME_SERVICE;
	Answer::NetPacket* packet2 = pGS2->popNetpacket( v31, Answer::PackType::PACK_DISPATCH, 0x2CDA );
	if ( packet2 )
	{
		packet2->writeInt32( nLevel );
		packet2->writeInt8( 0 );
		packet2->writeInt32( stu.itemId );
		packet2->writeInt8( stu.itemClass );
		packet2->writeInt32( stu.itemCount );
		uint32_t WOffset2 = packet2->getWOffset();
		packet2->setSize( WOffset2 );
		int16_t GateIndex = m_pPlayer->getGateIndex();
		int8_t v35 = m_pPlayer->getConnId();
		pGS2->sendPacketTo( v35, GateIndex, packet2 );
	}
}

// ========== Lucky Drop ==========

bool CVip::AddVipLuckyDrop( int32_t Type, int32_t Times )
{
	if ( Times <= 0 )
		return false;
	if ( Type == 1 )
	{
		int __k = 1;
		m_VipLuckyDropMap[__k].CanDropOrdinaryTimes += Times;
		CExtOperateLimit& OperateLimit = m_pPlayer->GetOperateLimit();
		OperateLimit.AddLimitCount( 1906, Times );
		return true;
	}
	else if ( Type == 2 )
	{
		int v10 = 1;
		m_VipLuckyDropMap[v10].CanDropSpecialTimes += Times;
		CExtOperateLimit& OperateLimit = m_pPlayer->GetOperateLimit();
		OperateLimit.AddLimitCount( 1907, Times );
		return true;
	}
	return false;
}

void CVip::AddDropTimes( int32_t Type, int32_t VipLevel )
{
	if ( VipLevel > 0 && VipLevel <= 14 )
	{
		if ( Type == 1 )
			++m_VipLuckyDropMap[VipLevel].DropOrdinaryTimes;
		else if ( Type == 2 )
			++m_VipLuckyDropMap[VipLevel].DropSpecialTimes;
	}
}

int32_t CVip::GetDropVipLevel( int32_t Type )
{
	Int32Vector CanDroplevel;
	if ( Type == 1 )
	{
		for ( int i = 1; i <= 14; ++i )
		{
			if ( GetVipLevel() < i ) break;
			if ( m_VipLuckyDropMap[i].DropOrdinaryTimes < m_VipLuckyDropMap[i].CanDropOrdinaryTimes )
				return i;
		}
	}
	else if ( Type == 2 )
	{
		for ( int i = 1; i <= 14; ++i )
		{
			if ( GetVipLevel() < i ) break;
			if ( m_VipLuckyDropMap[i].DropSpecialTimes < m_VipLuckyDropMap[i].CanDropSpecialTimes )
				return i;
		}
	}
	return 0;
}

void CVip::GetLuckDropType( int32_t Mid )
{
	MemChrBag stu;
	memset( &stu, 0, sizeof( stu ) );
	if ( !m_pPlayer )
		return;

	int8_t VipLevel = GetVipLevel();
	VipCfg* pVipCfg = CFG_DATA.GetVipTable().GetVipCfg( VipLevel );
	if ( !pVipCfg )
		return;

	int32_t DropTimes1 = m_pPlayer->getRecord( 1911 );
	int32_t DropTimes2 = m_pPlayer->getRecord( 1912 );
	int32_t Luck1 = pVipCfg->Luck1;

	if ( Luck1 + m_pPlayer->getRecord( 1906 ) > DropTimes1 )
	{
		// 检查Type1幸运掉落
		int32_t VipLevel_1 = GetDropVipLevel( 1 );
		int32_t nRand = RANDOM->generate( 1, 10000 );
		LuckDropTable& table = CFG_DATA.GetLuckDropTableTable();
		int32_t CfgRand = table.GetLuckRate( 1, VipLevel_1 );
		if ( nRand < CfgRand )
		{
			// Type1掉落
			MemChrBag Item;
			memset( &Item, 0, sizeof( Item ) );
			table.GetItem( &Item, 1, VipLevel_1 );
			m_pPlayer->updateRecord( 1911, DropTimes1 + 1 );
			stu.itemId = Item.itemId;
			stu.itemClass = Item.itemClass;
			stu.itemCount = Item.itemCount;
			stu.bind = Item.bind;
			SendLuckDrop( 1, Item, Mid );
			SendVipInfo();
			AddDropTimes( 1, VipLevel_1 );

			// 装备类处理
			if ( Item.itemClass == 2 )
			{
				int32_t MapId = m_pPlayer->getMapId();
				std::string p_name = m_pPlayer->getName();
				CharId_t Cid = m_pPlayer->getCid();
				int32_t Sid = m_pPlayer->getSid();
				int32_t itemId = stu.itemId;
				int8_t ConnId = m_pPlayer->getConnId();

				MemEquip equip = EQUIP_MANAGER.CreateMemEquip( ConnId, 1416, itemId, Sid, Cid, p_name, MapId, Mid, 0, 0, 0 );
				if ( equip.id > 0 )
				{
					EQUIP_MANAGER.SendPlayerEquipInfo( m_pPlayer, &equip );
					stu.srcId = equip.id;
				}

				const CfgEquip* pEquip = CFG_DATA.getEquip( Item.itemId );
				if ( pEquip && pEquip->m_backIndex > 0 )
				{
					EQUIP_BACK.KiaFuEquipBack( pEquip->m_backIndex, Item.itemId, Mid, m_pPlayer );
				}
			}

			CExtCharBag* Bag = m_pPlayer->GetBag();
			if ( !Bag->AddItem( &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP ) )
			{
				std::stringstream ss;
				ss << stu.itemId;
				std::string Param = ss.str();
				CharId_t v27 = m_pPlayer->getCid();
				DB_SERVICE.OnSendSysMail( m_pPlayer->getConnId(), v27, 1501, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP, &Param, 0 );
			}
			return;
		}
	}

	// 检查Type2
	int32_t Luck2 = pVipCfg->Luck2;
	if ( Luck2 + m_pPlayer->getRecord( 1907 ) > DropTimes2 )
	{
		int32_t VipLevel_2 = GetDropVipLevel( 2 );
		int32_t nRand_0 = RANDOM->generate( 1, 10000 );
		LuckDropTable& table = CFG_DATA.GetLuckDropTableTable();
		int32_t CfgRand_0 = table.GetLuckRate( 2, VipLevel_2 );
		if ( nRand_0 < CfgRand_0 )
		{
			MemChrBag Item;
			memset( &Item, 0, sizeof( Item ) );
			table.GetItem( &Item, 2, VipLevel_2 );
			m_pPlayer->updateRecord( 1912, DropTimes2 + 1 );
			stu.itemId = Item.itemId;
			stu.itemClass = Item.itemClass;
			stu.itemCount = Item.itemCount;
			stu.bind = Item.bind;
			SendLuckDrop( 2, Item, Mid );
			SendVipInfo();
			AddDropTimes( 2, VipLevel_2 );

			// 装备类处理
			if ( Item.itemClass == 2 )
			{
				int32_t MapId = m_pPlayer->getMapId();
				std::string v58 = m_pPlayer->getName();
				CharId_t Cid = m_pPlayer->getCid();
				int32_t Sid = m_pPlayer->getSid();
				int32_t itemId = stu.itemId;
				int8_t ConnId = m_pPlayer->getConnId();

				MemEquip equip = EQUIP_MANAGER.CreateMemEquip( ConnId, 1416, itemId, Sid, Cid, v58, MapId, Mid, 0, 0, 0 );
				if ( equip.id > 0 )
				{
					EQUIP_MANAGER.SendPlayerEquipInfo( m_pPlayer, &equip );
					stu.srcId = equip.id;
				}

				const CfgEquip* pEquip_0 = CFG_DATA.getEquip( Item.itemId );
				if ( pEquip_0 && pEquip_0->m_backIndex > 0 )
				{
					EQUIP_BACK.KiaFuEquipBack( pEquip_0->m_backIndex, Item.itemId, Mid, m_pPlayer );
				}
			}

			CExtCharBag* Bag = m_pPlayer->GetBag();
			if ( !Bag->AddItem( &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP ) )
			{
				std::stringstream ss;
				ss << stu.itemId;
				std::string v59 = ss.str();
				CharId_t v51 = m_pPlayer->getCid();
				DB_SERVICE.OnSendSysMail( m_pPlayer->getConnId(), v51, 1502, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP, &v59, 0 );
			}
		}
	}
}

void CVip::SendLuckDrop( int32_t nType, MemChrBag stu, int32_t Mid )
{
	int8_t ConnId = m_pPlayer->getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket( ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDA );
	if ( packet )
	{
		packet->writeInt32( 0 );
		packet->writeInt8( nType );
		packet->writeInt32( stu.itemId );
		packet->writeInt8( stu.itemClass );
		packet->writeInt32( stu.itemCount );
		uint32_t WOffset = packet->getWOffset();
		packet->setSize( WOffset );
		int16_t GateIndex = m_pPlayer->getGateIndex();
		int8_t v8 = m_pPlayer->getConnId();
		pGS->sendPacketTo( v8, GateIndex, packet );
	}

	int32_t GongGaoId = 0;
	if ( nType == 1 ) GongGaoId = 456;
	else if ( nType == 2 ) GongGaoId = 457;

	if ( GongGaoId > 0 )
	{
		GameService* pGS2 = GAME_SERVICE;
		Answer::NetPacket* packet_0 = pGS2->popNetpacket( 0, Answer::PackType::PACK_DISPATCH, 0x2CD6 );
		if ( packet_0 )
		{
			packet_0->writeInt32( GongGaoId );
			packet_0->writeInt64( m_pPlayer->getCid() );
			packet_0->writeUTF8( m_pPlayer->getName() );
			packet_0->writeInt32( m_pPlayer->getMapId() );
			packet_0->writeInt32( Mid );
			packet_0->writeInt8( stu.itemClass );
			packet_0->writeInt32( stu.itemId );
			uint32_t WOffset = packet_0->getWOffset();
			packet_0->setSize( WOffset );
			pGS2->worldBroadcast( 0, packet_0 );
		}
	}
}

// ========== Send Info ==========

void CVip::SendVipInfo()
{
	if ( !m_pPlayer )
		return;

	int8_t ConnId = m_pPlayer->getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket( ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD9 );
	if ( packet )
	{
		packet->writeInt32( m_PlatinumVipEndTime );
		packet->writeInt32( m_DiamVipEndTime );
		packet->writeInt32( m_StarVipEndTime );
		packet->writeInt32( GetVipExp() );
		packet->writeInt32( m_pPlayer->getRecord( 1021 ) );
		packet->writeInt32( m_pPlayer->getRecord( 2018 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1911 ) );
		packet->writeInt32( m_pPlayer->getRecord( 1912 ) );
		uint32_t WOffset = packet->getWOffset();
		packet->setSize( WOffset );
		int16_t GateIndex = m_pPlayer->getGateIndex();
		int8_t v10 = m_pPlayer->getConnId();
		pGS->sendPacketTo( v10, GateIndex, packet );
	}
}

void CVip::SendClubInfo()
{
	if ( !m_pPlayer )
		return;

	int8_t ConnId = m_pPlayer->getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket( ConnId, Answer::PackType::PACK_DISPATCH, 0x2CF7 );
	if ( packet )
	{
		packet->writeInt32( m_Club );
		packet->writeInt32( m_ClubDropTimes );
		packet->writeInt32( m_BuyTimes );
		VIP_CLUB->AppendClubWallInfo( packet );
		uint32_t WOffset = packet->getWOffset();
		packet->setSize( WOffset );
		int16_t GateIndex = m_pPlayer->getGateIndex();
		int8_t v6 = m_pPlayer->getConnId();
		pGS->sendPacketTo( v6, GateIndex, packet );
	}
}

// ========== BuyGongGao ==========

void CVip::BuyGongGao( int32_t GongGaoId, int8_t VipType, int8_t VipLevel )
{
	int8_t ConnId = m_pPlayer->getConnId();
	GameService* pGS = GAME_SERVICE;
	Answer::NetPacket* packet = pGS->popNetpacket( ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6 );
	if ( packet )
	{
		packet->writeInt32( GongGaoId );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeInt8( VipType );
		packet->writeInt8( VipLevel );
		uint32_t WOffset = packet->getWOffset();
		packet->setSize( WOffset );
		int8_t v8 = m_pPlayer->getConnId();
		pGS->worldBroadcast( v8, packet );
	}
}

// ========== Vip End Time Persistence ==========

void CVip::OnLoadVipEndTime( const std::string& VipEndTime )
{
	if ( !m_pPlayer )
		return;

	StringVector endTime;
	StringUtility::split( endTime, VipEndTime, ":" );
	if ( endTime.size() == 3 )
	{
		m_PlatinumVipEndTime = atoi( endTime[0].c_str() );
		m_DiamVipEndTime = atoi( endTime[1].c_str() );
		m_StarVipEndTime = atoi( endTime[2].c_str() );
	}
}

std::string CVip::OnSaveVipEndTime()
{
	std::stringstream ss;
	ss << m_PlatinumVipEndTime << ":" << m_DiamVipEndTime << ":" << m_StarVipEndTime;
	return ss.str();
}

void CVip::LoadDropString( const std::string& p_String )
{
	if ( !m_pPlayer )
		return;

	StringVector DropString;
	StringUtility::split( DropString, p_String, "|" );

	for ( StringVector::iterator it = DropString.begin(); it != DropString.end(); ++it )
	{
		StringVector DropTimesString;
		StringUtility::split( DropTimesString, *it, ":" );
		if ( DropTimesString.size() == 3 )
		{
			int __k = atoi( DropTimesString[0].c_str() );
			m_VipLuckyDropMap[__k].DropOrdinaryTimes = atoi( DropTimesString[1].c_str() );
			m_VipLuckyDropMap[__k].DropSpecialTimes = atoi( DropTimesString[2].c_str() );
		}
	}
}

std::string CVip::SaveDropString()
{
	std::stringstream ss;
	for ( int i = 1; i <= 14; ++i )
	{
		ss << i << ":" << m_VipLuckyDropMap[i].DropOrdinaryTimes << ":" << m_VipLuckyDropMap[i].DropSpecialTimes;
		if ( i < 14 ) ss << "|";
	}
	return ss.str();
}

// ========== CheckVipEnd ==========

void CVip::CheckVipEnd( int64_t Tick )
{
	if ( !m_pPlayer )
		return;

	int32_t Now = m_pPlayer->getNow();
	std::string EmptyStr;

	if ( m_PlatinumVipEndTime > 0 && m_PlatinumVipEndTime < Now )
	{
		CharId_t Cid = m_pPlayer->getCid();
		DB_SERVICE.OnSendSysMail( m_pPlayer->getConnId(), Cid, 6387, &EmptyStr, 0 );
		m_PlatinumVipEndTime = 0;
		m_pPlayer->RecalcAttr();
	}
	if ( m_DiamVipEndTime > 0 && m_DiamVipEndTime < Now )
	{
		CharId_t Cid = m_pPlayer->getCid();
		DB_SERVICE.OnSendSysMail( m_pPlayer->getConnId(), Cid, 6388, &EmptyStr, 0 );
		m_DiamVipEndTime = 0;
		m_pPlayer->RecalcAttr();
	}
	if ( m_StarVipEndTime > 0 && m_StarVipEndTime < Now )
	{
		CharId_t Cid = m_pPlayer->getCid();
		DB_SERVICE.OnSendSysMail( m_pPlayer->getConnId(), Cid, 6389, &EmptyStr, 0 );
		m_StarVipEndTime = 0;
		m_pPlayer->RecalcAttr();
	}
}
