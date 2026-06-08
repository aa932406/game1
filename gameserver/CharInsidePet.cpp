
#include <algorithm>

#include "stdafx.h"
#include "CharInsidePet.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "ObjPet.h"
#include "RandHelper.h"
#include "PDUDefine.h"
#include "EquipManager.h"
#include "PetManager.h"

enum ERR_PET
{
	ERR_PET_USE_LUCKY_ITEM_FAIL	= 1,		// 宠物使用幸运值道具失败
};

enum INSIDE_PET_EXP_ILLUTION
{
	IPEI_ITEM		= 1,	// 道具
	IPEI_PET_EGG	= 2,	// 幻兽蛋
};

using namespace Answer;

CExtCharInsidePet::CExtCharInsidePet()
{
	OnCleanUp();
}

CExtCharInsidePet::~CExtCharInsidePet()
{
}

void CExtCharInsidePet::OnCleanUp()
{
	m_attrs.CleanUp();

	m_pPet				= NULL;
	m_bStartIllusion	= 0;
	m_nAttrType			= 0;
	m_nAttrValue		= 0;
	m_nOnlineTime		= 0;
	m_nLeftTime			= 0;
	m_nBuyExpTimes		= 0;
	m_nLastTick			= 0;
	m_nSpeed			= 0;
}

void CExtCharInsidePet::OnLoadFromDB( const PlayerDBData& dbData )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_pPet = PET_MANAGER.GetPet( dbData.m_CharInsidePet.nPetId );
	if ( NULL == m_pPet )
	{
		m_pPet = PET_MANAGER.CreateNewPet( GetInsidePetId( m_pPlayer->getJob() ), m_pPlayer, PFW_BORN );
		if ( NULL == m_pPet )
		{
			return;
		}
		PET_MANAGER.AddPet( m_pPlayer->getConnId(), m_pPet );
		m_pPet->SetPetBorn();
	}

	m_bStartIllusion= dbData.m_CharInsidePet.bStartIllusion;
	m_nAttrType		= dbData.m_CharInsidePet.nAttrType;
	m_nAttrValue	= dbData.m_CharInsidePet.nAttrValue;
	m_nOnlineTime	= dbData.m_CharInsidePet.nOnlineTime;
	m_nLeftTime		= dbData.m_CharInsidePet.nLeftTime;
	m_nBuyExpTimes	= dbData.m_CharInsidePet.nBuyExpTimes;

	m_nSpeed		= calBaseIllusionSpeed();
	recalAttr();
//	m_pPlayer->recalcAttr();
	m_pPlayer->GetCharPet().RecalPetsAttr();
}

void CExtCharInsidePet::OnSaveToDB( PlayerDBData& dbData )
{
	if ( NULL == m_pPet )
	{
		return;
	}
	dbData.m_CharInsidePet.nPetId			= m_pPet->GetPetId();
	dbData.m_CharInsidePet.bStartIllusion	= m_bStartIllusion;
	dbData.m_CharInsidePet.nAttrType		= m_nAttrType;
	dbData.m_CharInsidePet.nAttrValue		= m_nAttrValue;
	dbData.m_CharInsidePet.nOnlineTime		= m_nOnlineTime;
	dbData.m_CharInsidePet.nLeftTime		= m_nLeftTime;
	dbData.m_CharInsidePet.nBuyExpTimes		= m_nBuyExpTimes;
}

void CExtCharInsidePet::OnUpdate( int64_t curTick )
{
// 	if ( curTick - m_nLastTick >= 1000 )
// 	{
// 		m_nLastTick = curTick;
// 		checkBaseIllusionSpeed();
// 		checkBaseIllusion();
// 	}
}

void CExtCharInsidePet::OnDaySwitch( int32_t nDiffDays )
{
	m_nOnlineTime	= 0;
	m_nBuyExpTimes	= 0;
}

void CExtCharInsidePet::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back ( CM_INSIDE_PET_REQUEST_INFO );
	procList.push_back ( CM_INSIDE_PET_BASE_ILLUSION );
	procList.push_back ( CM_INSIDE_PET_GROW_ILLUSION );
	procList.push_back ( CM_INSIDE_PET_LUCKY_ILLUSION );
	procList.push_back ( CM_INSIDE_PET_EXP_ILLUSION );
	procList.push_back ( CM_INSIDE_PET_USE_LUCKY_ITEM );
	procList.push_back ( CM_INSIDE_PET_USE_PHASE_ITEM );
	procList.push_back ( CM_INSIDE_PET_BUY_EXP );
	procList.push_back ( CM_INSIDE_PET_REQUEST_BASE_ILLUSION );
	procList.push_back ( CM_INSIDE_PET_ITEM_ILLUSION );
}

int32_t CExtCharInsidePet::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch ( nProcId )
	{
	case CM_INSIDE_PET_REQUEST_INFO:			return onRequestInfo( inPacket );
//	case CM_INSIDE_PET_BASE_ILLUSION:			return onBaseIllusion( inPacket );
	case CM_INSIDE_PET_GROW_ILLUSION:			return onGrowIllusion( inPacket );
//	case CM_INSIDE_PET_LUCKY_ILLUSION:			return onLuckyIllusion( inPacket );
	case CM_INSIDE_PET_EXP_ILLUSION:			return onExpIllusion( inPacket );
	case CM_INSIDE_PET_USE_LUCKY_ITEM:			return onUseLuckyItem( inPacket );
	case CM_INSIDE_PET_USE_PHASE_ITEM:			return onUsePhaseItem( inPacket );
	case CM_INSIDE_PET_BUY_EXP:					return onBuyExp( inPacket );
	case CM_INSIDE_PET_ITEM_ILLUSION:			return onLiBaoIllusion( inPacket );
//	case CM_INSIDE_PET_REQUEST_BASE_ILLUSION:	return onRequestBaseIllusion( inPacket );
	default:	break;
	}
	return ERR_OK;
}

int32_t CExtCharInsidePet::onRequestInfo( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	sendBaseInfo();
	return ERR_OK;
}


// int32_t CExtCharInsidePet::onBaseIllusion( NetPacket *inPacket )
// {
// 	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 
// 	if ( m_bStartIllusion == 1 )
// 	{
// 		return ERR_INVALID_DATA;		// 正在修炼
// 	}
// 
// 	if ( IsReinTimesLimit() )
// 	{
// 		return ERR_INVALID_DATA;		// 转生次数不足
// 	}
// 
// 	m_nAttrType = randBaseAttr();
// 	if ( m_nAttrType == -1 )
// 	{
// 		return ERR_INVALID_DATA;		// 全满
// 	}
// 
// 	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, calBaseIllusionCost( m_pPet->GetStartPoints() ), VCR_BASE_ILLUSION ) )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
// 
// 	// 修炼开始
// 	m_bStartIllusion	= 1;
// 	m_nLeftTime			= calBaseIllusionTime( m_pPet->GetStartPoints() );
// 	m_nAttrValue		= calBaseAttrAddValue( m_nAttrType );
// 	m_nLastTick			= m_pPlayer->getTick();
// 
// 	sendBaseIllusionInfo();
// 	return GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_nLeftTime );
// }

int32_t CExtCharInsidePet::onGrowIllusion( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t	pid = static_cast<PetId_t>( inPacket->readInt64() );
	int8_t nUseItem = inPacket->readInt8();
	CObjPet* pPet = m_pPlayer->GetCharPet().GetPet( pid );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}
	if ( !pPet->IsXXoo() )
	{
		return ERR_INVALID_DATA;
	}
	if ( !pPet->IsRest() || pPet->GetKnight() != PK_NONE || pPet->IsRegInFamily() || m_pPlayer->GetCharPet().IsTopPet( pPet ) || pPet->GetQiShi() != 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( IsReinTimesLimit() )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Level = CFG_DATA.GetHuanHuaNeedRoleLevel( m_pPet->GetPoints() );
	if ( m_pPlayer->getLevel() < Level )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_pPet->GetGrowPoints() >= 10000 )
	{
		if ( m_pPet->GetPhase() != PP_ELECTRIC && m_pPet->GetPhase() != pPet->GetPhase() )
		{
			return false;
		}
	}

	const CfgPetIllusionGrow* pGrow = CFG_DATA.GetPetIllusionTable().GetGrow( m_pPet->GetGrowPoints() );
	const CfgPetIllusionGrow* pVicePetGrow = CFG_DATA.GetPetIllusionTable().GetGrowViceGrow( pPet->GetPoints() );
	if ( NULL == pGrow || NULL == pVicePetGrow )
	{
		return ERR_INVALID_DATA;
	}
	int32_t DiffTime = pVicePetGrow->Compensation - pGrow->Compensation + 1;
	if ( DiffTime <= 0  )
	{
		return ERR_INVALID_DATA;
	}
	if ( NULL == pGrow )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet->GetPoints() < pGrow->nVicePoint )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet->getLevel() < pGrow->nViceLevel )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->GetCurrency( CURRENCY_VIGOUR ) < 6000 )
	{
		return ERR_INVALID_DATA;
	}

	ItemData itemData = {};
	itemData.m_nClass = IC_NORMAL;
	itemData.m_nCount = 1*DiffTime;
	switch ( nUseItem )
	{
	case PIIT_NONE:
		break;
	case PIIT_LUCKY_GRASS:
		itemData.m_nId	= ISI_PET_LUCKY_GRASS;
		break;
	case PIIT_GOD_GRASS:
		itemData.m_nId	= ISI_PET_GOD_GRASS;
		break;
	default:
		return ERR_INVALID_DATA;
	}

	if ( itemData.m_nId > 0 )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( itemData, IDCR_PET_USE_ITEM ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, 6000, VCR_GROW_ILLUSION ) )
	{
		return ERR_INVALID_DATA;
	}

	for ( int32_t i = 0; i < DiffTime; i++ )
	{
		m_pPet->Illusion( pPet->GetPet(), PHT_GROW_ATTR, nUseItem );
	}
	m_pPlayer->GetCharPet().RemovePet( pPet );
	recalAttr();
	m_pPlayer->recalcAttr();
	m_pPlayer->GetCharPet().RecalPetsAttr();
	sendBaseInfo();
	m_pPlayer->GetAchievemnet().AddAchievement( AT_INSID_PET_POINTS,m_pPet->GetPoints() );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_HUAN_LING_POINTS,m_pPet->GetGrowPoints() );
	return replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), pid );
}

int32_t	CExtCharInsidePet::onLiBaoIllusion( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer || NULL == m_pPet )
	{
		return ERR_INVALID_DATA;
	}
	int32_t ShopId		= inPacket->readInt32();
	int8_t	nUseItem	= inPacket->readInt8();	
	if ( m_pPet->IsReinLimit() )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Level = CFG_DATA.GetHuanHuaNeedRoleLevel( m_pPet->GetPoints() );
	if ( m_pPlayer->getLevel() < Level )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_pPlayer->GetCurrency( CURRENCY_VIGOUR ) < 6000 )
	{
		return ERR_INVALID_DATA;
	}
	const CfgPetIllusionGrow* pGrow = CFG_DATA.GetPetIllusionTable().GetGrow( m_pPet->GetGrowPoints() );
	if ( NULL == pGrow )
	{
		return ERR_INVALID_DATA;
	}
	if ( !CFG_DATA.GetPetIllusionTable().IsRightShopId( m_pPet->GetGrowPoints(),ShopId ) )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Points = CFG_DATA.GetPetTable().GetBuyPetPoints(ShopId);
	const CfgPetIllusionGrow* pVicePetGrow = CFG_DATA.GetPetIllusionTable().GetGrowViceGrow( Points );
	if (  NULL == pVicePetGrow )
	{
		return ERR_INVALID_DATA;
	}
	int32_t DiffTime = pVicePetGrow->Compensation - pGrow->Compensation + 1;
	if ( DiffTime <= 0  )
	{
		return ERR_INVALID_DATA;
	}
	if ( ERR_OK != m_pPlayer->GetPlayerShangCheng().BuyShopItem( ShopId, 1, false ) )
	{
		return ERR_INVALID_DATA;
	}

	ItemData itemData = {};

	switch ( nUseItem )
	{
	case PIIT_NONE:	break;
	case PIIT_LUCKY_GRASS:	itemData.m_nId	= ISI_PET_LUCKY_GRASS;		break;
	case PIIT_GOD_GRASS:	itemData.m_nId	= ISI_PET_GOD_GRASS;		break;
	default:break;
	}
	itemData.m_nClass = IC_NORMAL;
	itemData.m_nCount = 1*DiffTime;

	if ( itemData.m_nId > 0 )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( itemData, IDCR_PET_USE_ITEM ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, 6000, VCR_GROW_ILLUSION ) )
	{
		return ERR_INVALID_DATA;
	}
	for ( int32_t i = 0; i < DiffTime; ++i )
	{
		m_pPet->growAttrIllusionByItem( nUseItem );
	}
	recalAttr();
	m_pPlayer->recalcAttr();
	m_pPlayer->GetCharPet().RecalPetsAttr();
	sendBaseInfo();
	m_pPlayer->GetAchievemnet().AddAchievement( AT_INSID_PET_POINTS,m_pPet->GetPoints() );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_HUAN_LING_POINTS,m_pPet->GetGrowPoints() );
	replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
	return ERR_OK;
}

// int32_t CExtCharInsidePet::onLuckyIllusion( NetPacket *inPacket )
// {
// 	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 
// 	PetId_t	pid = static_cast<PetId_t>( inPacket->readInt64() );
// 	CObjPet* pPet = m_pPlayer->GetCharPet().GetPet( pid );
// 	if ( NULL == pPet )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
// 
// 	if ( !pPet->IsRest() || pPet->GetKnight() != PK_NONE || pPet->IsRegInFamily() || m_pPlayer->GetCharPet().IsTopPet( pPet ) || pPet->GetQiShi() != 0 )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 
// 	if ( IsReinTimesLimit() )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
// 
// 	int32_t nMainVal = m_pPet->GetLucky();
// 	int32_t nViceVal = pPet->GetLucky();
// 	if ( nViceVal < nMainVal )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
// 
// 	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, 3000, 0 ) )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
// 
// 	if ( !m_pPet->Illusion( pPet->GetPet(), PHT_LUCKY, PIIT_NONE ) )
// 	{
// 		return ERR_INVALID_DATA;
// 	}
// 
// 	m_pPlayer->GetCharPet().RemovePet( pPet );
// 	sendBaseInfo();
// 	return GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), pid );
// }

int32_t CExtCharInsidePet::onExpIllusion( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int64_t nLevelUpNeedExp = m_pPet->getLevelUpExp();
	if ( nLevelUpNeedExp < 0 )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t	bDouble = inPacket->readInt8();
	int32_t size	= inPacket->readInt32();
	if ( bDouble == 1 )
	{
		if ( m_pPlayer->GetPlayerVip().GetVipLevel() <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
	}
	Int32List bagSlotList;
	Int32List eggSlotList;
	int32_t nAddExp = 0;
	int32_t nCostVigour = 3000;
	int32_t nCostGold = 0;
	for ( int32_t i = 0; i < size; ++i )
	{
		int8_t	nType	= inPacket->readInt8();	// 1 道具 2 幻兽蛋
		int32_t nSlot	= inPacket->readInt32();
		if ( nType == IPEI_ITEM )
		{
			const MemChrBag& slotData = m_pPlayer->GetBag().GetSlotData( nSlot );
			if ( slotData.itemClass == IC_EQUIP )
			{
				MemEquip equip = EQUIP_MANAGER.GetMemEquip( slotData.srcId );
				if ( equip.base != slotData.itemId )
				{
					return ERR_INVALID_DATA;
				}
				nAddExp += calEquipAddExp( equip );
			}
			else if ( slotData.itemClass == IC_NORMAL )
			{
				int32_t nExp = CFG_DATA.GetInsidePetTable().GetItemExp( slotData.itemId );
				if ( nExp <= 0 )
				{
					return ERR_INVALID_DATA;
				}
				nAddExp += nExp*slotData.itemCount;
			}
			else
			{
				return ERR_INVALID_DATA;
			}
			bagSlotList.push_back( nSlot );
			//nCostVigour += 1000;
		}
		else if ( nType == IPEI_PET_EGG )
		{
			PetEgg* pEgg = m_pPlayer->GetCharPet().GetEgg( nSlot );
			if ( NULL == pEgg )
			{
				return ERR_INVALID_DATA;
			}
			if ( pEgg->GetState() != PES_CAN_OPEN )
			{
				return ERR_INVALID_DATA;
			}
			eggSlotList.push_back( nSlot );
			nAddExp += calEggAddExp( *pEgg );
			//nCostVigour += 1000;
		}
		else
		{
			return ERR_INVALID_DATA;
		}
	}

	if ( m_pPlayer->GetCurrency( CURRENCY_VIGOUR ) < nCostVigour )
	{
		return ERR_INVALID_DATA;
	}
	if ( bDouble )
	{
		int32_t Level = m_pPlayer->getLevel() + m_pPlayer->GetSoulLevel();
		int32_t Rate =  Level * 300 + 500;
		if ( nAddExp % Rate == 0 )
		{
			nCostGold = nAddExp / Rate;
		}
		else
		{
			nCostGold = nAddExp / Rate + 1;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_INSIDE_PET_EXP_ILLUSION_DOUBLE ) )
		{
			return ERR_INVALID_DATA;
		}
		nAddExp *= 2;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, nCostVigour, VCR_EXP_ILLUSION ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( bagSlotList.size() > 0 )
	{
		MemChrBag emptySlot = {};
		for ( Int32List::iterator iter = bagSlotList.begin(); iter != bagSlotList.end(); ++iter )
		{
			m_pPlayer->GetBag().CleanSlot( *iter, IDCR_INSIDE_PET_EXP_ILLUSION );
		}
		m_pPlayer->GetBag().ForceSendDirty();
	}

	if ( eggSlotList.size() > 0 )
	{
		m_pPlayer->GetCharPet().RemoveEgg( eggSlotList );
		m_pPlayer->GetCharPet().ForceSendDirty();
	}

	// 先发成功包
	m_pPlayer->GetAchievemnet().AddAchievement( AT_INSID_PET_POINTS,m_pPet->GetPoints() );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_WU_LING_POINTS,GetWuLingPoints() );
	replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nAddExp );
	addExp( nAddExp );
	return ERR_OK;
}

int32_t CExtCharInsidePet::GetWuLingPoints()
{
	return m_pPet->GetLevel()*WU_LING_RATE;
}

int32_t CExtCharInsidePet::onUseLuckyItem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	// 检测道具
	const CfgPetLuckyItem*	pCfgLucky = CFG_DATA.GetCharPetTable().GetPetLuckyItem( m_pPet->GetLucky() );
	if ( NULL == pCfgLucky )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->GetCurrency( CURRENCY_VIGOUR ) < 3000 )
	{
		return ERR_INVALID_DATA;
	}
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	ItemData itemData = {};
	itemData.m_nClass	= pCfgLucky->nClass;
	itemData.m_nId		= pCfgLucky->nId;
	itemData.m_nCount	= pCfgLucky->nCount;
	if ( itemData.m_nId > 0 )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, IDCR_INSIDE_PET_USE_LUCKY_ITEM ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, 3000, VCR_EXP_ILLUSION ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCfgLucky->nRate < RANDOM.generate( 0, 10000 ) )
	{
		replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_PET_USE_LUCKY_ITEM_FAIL, m_pPet->GetLucky() );
		return ERR_INVALID_DATA;
	}
	m_pPlayer->GetAchievemnet().AddAchievement( AT_INSID_PET_POINTS,m_pPet->GetPoints() );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_LUCK_POINTS,m_pPet->GetLucky() );
	m_pPet->UseLuckyItem();
	sendBaseInfo();
	return replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), m_pPet->GetLucky() );
}

int32_t CExtCharInsidePet::onUsePhaseItem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nSlot	= inPacket->readInt32();
	MemChrBag slotData = m_pPlayer->getBagSlotData( nSlot );
	if ( slotData.itemClass != IC_NORMAL )
	{
		return ERR_INVALID_DATA;
	}

	if ( slotData.itemCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	PET_PHASE phase = PP_INVALID;
	if ( slotData.itemId == ISI_PET_KIWI_FRUIT )				// 奇异果
	{
		phase = PP_INVALID;
	}
	else if ( slotData.itemId == ISI_PET_ELECTRIC_POTION )		// 电浆药水
	{
		phase = PP_ELECTRIC;
	}
	else
	{
		return ERR_INVALID_DATA;
	}

	PET_PHASE finalPhase = m_pPet->ChangePhase( phase );
	if ( finalPhase == PP_ELECTRIC || finalPhase == PP_GOLD )
	{
		recalAttr();

		// 添加公告
		NetPacket *packet = popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_PET_BROADCASE );
		if (NULL == packet)
		{
			return ERR_INVALID_DATA;
		}

		packet->writeInt8( PBCT_PHASE );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->writeInt32( m_pPet->GetBaseId() );
		packet->writeUTF8( m_pPet->GetName() );
		packet->writeInt64( m_pPet->GetPetId() );
		packet->writeInt8( phase );

		packet->setSize( packet->getWOffset() );
		worldBroadcast(m_pPlayer->getConnId(), packet);
	}
	--slotData.itemCount;
	m_pPlayer->GetBag().SetSlotData( nSlot, slotData, IDCR_INSIDE_PET_CHANGE_PHASE );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_INSID_PET_POINTS,m_pPet->GetPoints() );
	return replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), finalPhase );
}

int32_t CExtCharInsidePet::onBuyExp( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int64_t nLevelUpNeedExp = m_pPet->getLevelUpExp();
	if ( nLevelUpNeedExp < 0 )
	{
		return ERR_SYETEM_ERR;
	}
	//int8_t currencyType = inPacket->readInt8();
	//if ( currencyType != CURRENCY_GOLD && currencyType != CURRENCY_CASH )
	//{
	//	return ERR_INVALID_DATA;
	//}

	//if ( m_nTodayBuyExpTimes >= VIP )
	//{
	//	return ERR_INVALID_DATA;
	//}
	int32_t Level = m_pPlayer->getLevel() + m_pPlayer->GetSoulLevel();
	int32_t nAddExp =  static_cast<int32_t>(( 0.05f * Level * Level + Level ) * 200 + 1000);

	if ( !m_pPlayer->DecGoldAndCash( 20, GCR_INSIDE_PET_EXP_ILLUSION_GOLD ) )
	{
		return ERR_INVALID_DATA;
	}

	++m_nBuyExpTimes;
	
	m_pPlayer->GetAchievemnet().AddAchievement( AT_INSID_PET_POINTS,m_pPet->GetPoints() );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_WU_LING_POINTS,GetWuLingPoints() );
	// 先发成功包
	replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nAddExp );
	addExp( nAddExp );
	return ERR_OK;
}

int32_t CExtCharInsidePet::onRequestBaseIllusion( NetPacket *inPacket )
{
	sendBaseIllusionInfo();
	return ERR_OK;
}

void CExtCharInsidePet::AddAttrToTarget( Unit* pUnit )
{
	if ( NULL == pUnit || NULL == m_pPet )
	{
		return;
	}

	pUnit->AddAttrValue( CObjAttrs::ATTR_HP,			m_attrs.GetAttr( CObjAttrs::ATTR_HP				) );
//	pUnit->AddAttrValue( CObjAttrs::ATTR_PHY_ATK_MIN,	m_attrs.GetAttr( CObjAttrs::ATTR_PHY_ATK_MIN	) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_PHY_ATK_MAX,	m_attrs.GetAttr( CObjAttrs::ATTR_PHY_ATK_MAX	) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_PHY_DEF,		m_attrs.GetAttr( CObjAttrs::ATTR_PHY_DEF		) );
//	pUnit->AddAttrValue( CObjAttrs::ATTR_MAG_ATK_MIN,	m_attrs.GetAttr( CObjAttrs::ATTR_MAG_ATK_MIN	) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX,	m_attrs.GetAttr( CObjAttrs::ATTR_MAG_ATK_MAX	) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_MAG_DEF,		m_attrs.GetAttr( CObjAttrs::ATTR_MAG_DEF		) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_DODGE,			m_attrs.GetAttr( CObjAttrs::ATTR_DODGE			) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_HITRATE,		m_attrs.GetAttr( CObjAttrs::ATTR_HITRATE		) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_CRITRATE,		m_attrs.GetAttr( CObjAttrs::ATTR_CRITRATE		) );
	pUnit->AddAttrValue( CObjAttrs::ATTR_TENACITY,		m_attrs.GetAttr( CObjAttrs::ATTR_TENACITY		) );
	if ( pUnit->getType() != ET_PET )
	{
		pUnit->AddAttrValue( CObjAttrs::ATTR_LUCKY,m_pPet->GetLucky() );
	}
}

void CExtCharInsidePet::OnLevelUp()
{
	recalAttr();

}

void CExtCharInsidePet::recalAttr()
{
	if ( NULL == m_pPet )
	{
		return;
	}
	// 计算属性
	calBaseAttr( CObjAttrs::ATTR_HP,			PET_ATTR_START_HP,			PET_ATTR_GROW_HP );
//	calBaseAttr( CObjAttrs::ATTR_PHY_ATK_MIN,	PET_ATTR_START_PHY_ATK_MIN,	PET_ATTR_GROW_PHY_ATK_MIN );
	calBaseAttr( CObjAttrs::ATTR_PHY_ATK_MAX,	PET_ATTR_START_PHY_ATK_MAX,	PET_ATTR_GROW_PHY_ATK_MAX );
	calBaseAttr( CObjAttrs::ATTR_PHY_DEF,		PET_ATTR_START_PHY_DEF,		PET_ATTR_GROW_PHY_DEF );
//	calBaseAttr( CObjAttrs::ATTR_MAG_ATK_MIN,	PET_ATTR_START_MAG_ATK_MIN,	PET_ATTR_GROW_MAG_ATK_MIN );
	calBaseAttr( CObjAttrs::ATTR_MAG_ATK_MAX,	PET_ATTR_START_MAG_ATK_MAX,	PET_ATTR_GROW_MAG_ATK_MAX );
	calBaseAttr( CObjAttrs::ATTR_MAG_DEF,		PET_ATTR_START_MAG_DEF,		PET_ATTR_GROW_MAG_DEF );
	calBaseAttr( CObjAttrs::ATTR_DODGE,			PET_ATTR_START_DODGE,		PET_ATTR_GROW_DODGE );
	calBaseAttr( CObjAttrs::ATTR_HITRATE,		PET_ATTR_START_HITRATE,		PET_ATTR_GROW_HITRATE );
	calBaseAttr( CObjAttrs::ATTR_CRITRATE,		PET_ATTR_START_CRITRATE,	PET_ATTR_GROW_CRITRATE );
	calBaseAttr( CObjAttrs::ATTR_TENACITY,		PET_ATTR_START_TENACITY,	PET_ATTR_GROW_TENACITY );

	const AttrAddonVector& attrAddons = CFG_DATA.GetInsidePetTable().GetAttrAddon( m_pPet->GetPetLevel(), m_pPlayer->getJob() );
	for ( uint32_t i = 0; i < attrAddons.size(); ++i )
	{
		CObjAttrs::Index_T index = static_cast<CObjAttrs::Index_T>( attrAddons[i].index );
		if ( attrAddons[i].addon > 0 )
		{
			m_attrs.SetAttr( index, m_attrs.GetAttr( index ) + attrAddons[i].addon );
		}
	}
}

void CExtCharInsidePet::sendBaseInfo()
{
	if ( NULL == m_pPlayer || NULL == m_pPet )
	{
		return;
	}

	NetPacket *packet = popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_INSIDE_PET_SEND_BASE_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( m_pPet->GetPetId() );
	packet->writeInt32( m_pPet->GetPetLevel() );
	packet->writeInt64( m_pPet->GetExp() );
	packet->writeInt32( m_pPet->GetRein() );
	packet->writeInt32( m_pPet->GetReinLimit() );
	packet->writeInt8( m_pPet->GetPhase() );
	packet->writeInt32( m_pPet->GetLucky() );
//	packet->writeInt32( m_pPet->GetStartPoints() );
	packet->writeInt32( m_pPet->GetGrowPoints() );
	packet->writeInt32( m_pPet->GetPoints() );
	packet->writeInt32( m_pPet->GetGrowTimes() );

	for ( int32_t i = PET_ATTR_GROW_HP; i < PET_ATTR_COUNT; ++i )
	{
		if ( i == PET_ATTR_GROW_PHY_ATK_MIN || i == PET_ATTR_GROW_MAG_ATK_MIN )
		{
			continue;
		}
		packet->writeInt32( m_pPet->GetBaseAttr( static_cast<PET_ATTR>( i ) ) );
	}

	packet->writeInt16( m_pPet->GetRankIndex( PRT_POINTS ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_HP ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_PHY_ATK_MIN ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_PHY_ATK_MAX ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_PHY_DEF ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_MAG_ATK_MIN ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_MAG_ATK_MAX ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_START_MAG_DEF ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_HP ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_PHY_ATK_MIN ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_PHY_ATK_MAX ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_PHY_DEF ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_MAG_ATK_MIN ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_MAG_ATK_MAX ) );
// 	packet->writeInt16( m_pPet->GetRankIndex( PRT_GROW_MAG_DEF ) );

	packet->writeInt16( m_nBuyExpTimes );
// 	packet->writeInt8( m_bStartIllusion );
// 	packet->writeInt8( m_nAttrType );
// 	packet->writeInt32( m_nAttrValue );
// 	packet->writeInt8( m_nSpeed );
// 	packet->writeInt32( m_nLeftTime );


	packet->setSize( packet->getWOffset() );
	sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t CExtCharInsidePet::GetRank( PET_RANK_TYPE nRankType )
{
	return m_pPet->GetRankIndex( nRankType );
}

void CExtCharInsidePet::sendBaseIllusionInfo()
{
// 	if ( NULL == m_pPlayer )
// 	{
// 		return;
// 	}
// 
// 	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_INSIDE_PET_SEND_BASE_ILLUSION );
// 	if (NULL == packet)
// 	{
// 		return;
// 	}
// 
// 	packet->writeInt8( m_bStartIllusion );
// 	packet->writeInt8( m_nAttrType );
// 	packet->writeInt32( m_nAttrValue );
// 	packet->writeInt8( m_nSpeed );
// 	packet->writeInt32( m_nLeftTime );
// 
// 	packet->setSize( packet->getWOffset() );
// 	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

// int8_t CExtCharInsidePet::randBaseAttr()
// {
// 	if ( NULL == m_pPet )
// 	{
// 		return -1;
// 	}
// 
// 	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_pPet->GetBaseId() );
// 	if ( NULL == pCfgPet )
// 	{
// 		return -1;
// 	}
// 
// 	int8_t nCount = 0;
// 	Int8Vector vAttr;
// 	vAttr.reserve( PET_ATTR_COUNT );
// 	for ( int8_t i = PET_ATTR_START_HP; i <= PET_ATTR_START_MAG_DEF; ++i )
// 	{
// 		if ( m_pPet->GetBaseAttr( static_cast<PET_ATTR>( i ) ) < pCfgPet->m_vMaxAttr[i] )
// 		{
// 			vAttr.push_back( i );
// 			++nCount;
// 		}
// 	}
// 
// 	if ( nCount <= 0 )
// 	{
// 		return -1;	// 已经全满了
// 	}
// 	else if ( nCount == 1 )
// 	{
// 		return vAttr[0];
// 	}
// 	else
// 	{
// 		int8_t nRand = RANDOM.generate( 0, nCount-1 );
// 		return vAttr[nRand];
// 	}
// }

int32_t CExtCharInsidePet::calBaseIllusionTime( int32_t startPoints )
{
	if ( startPoints < 200 )
	{
		return 3600;
	}
	if ( startPoints < 400 )
	{
		return 7200;
	}
	
	return 10800;
}

int32_t CExtCharInsidePet::calBaseIllusionCost( int32_t startPoints )
{
	if ( startPoints < 200 )
	{
		return 2000;
	}
	if ( startPoints < 400 )
	{
		return 3000;
	}

	return 4000;
}

int32_t CExtCharInsidePet::calBaseAttrAddValue( int8_t attr )
{
	int32_t nRand = RANDOM.generate( 2, 4 );
	if ( attr == PET_ATTR_START_HP )
	{
		return nRand * 2;
	}
	return nRand;
}

int8_t CExtCharInsidePet::calBaseIllusionSpeed()
{
	if ( m_nOnlineTime < 1800 )
	{
		return 1;
	}
	return 5;
}

void CExtCharInsidePet::checkBaseIllusionSpeed()
{
	int8_t nCurSpeed = calBaseIllusionSpeed();
	if ( m_nSpeed != nCurSpeed )
	{
		m_nSpeed = nCurSpeed;
		sendBaseIllusionInfo();
	}
}

void CExtCharInsidePet::checkBaseIllusion()
{
	if ( NULL == m_pPet )
	{
		return;
	}

	if ( m_bStartIllusion != 1 )
	{
		return;
	}

	++m_nOnlineTime;
	m_nLeftTime -= m_nSpeed;
	if ( m_nLeftTime <= 0 )
	{
		m_bStartIllusion = 0;
		m_pPet->AddBaseAttr( static_cast<PET_ATTR>( m_nAttrType ), m_nAttrValue );
		recalAttr();
		m_pPlayer->recalcAttr();
		m_pPlayer->GetCharPet().RecalPetsAttr();
		sendBaseInfo();
	}
}

bool CExtCharInsidePet::IsReinTimesLimit() const
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	int32_t nReinTimes = m_pPet->GetRein();
	if ( m_bStartIllusion )
	{
		++nReinTimes;	// 基础属性幻化中，预留1
	}
	return nReinTimes >= m_pPet->GetReinLimit();
}

int32_t	CExtCharInsidePet::calEggAddExp( const PetEgg& egg ) const
{
	const CfgPetData* pPetData = CFG_DATA.GetPetTable().GetPet( egg.GetBaseId() );
	if ( NULL == pPetData )
	{
		return 0;
	}
	CPet* pPet = PET_MANAGER.GetPet( egg.GetPetId() );
	if ( NULL == pPet )
	{
		return 0;
	}
	int32_t Exp = CFG_DATA.GetPetTable().GetWuHunExp(pPet->GetPoints());

	return pPetData->m_WuHunExp + Exp;
}

int32_t	CExtCharInsidePet::calEquipAddExp( const MemEquip& equip ) const
{
	const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( equip.base );
	if ( NULL == pCfgEquip )
	{
		return 0;
	}

	int32_t nBaseValue = pCfgEquip->m_nWuHunExp;
	int32_t nHoleValue = CFG_DATA.GetEquipTable().GetWuHunHoleExp( equip.GetGemSlotCount() );
	int32_t nStarValue = CFG_DATA.GetEquipTable().GetWuHunMoHunExp( equip.star );
	
	return nBaseValue + nHoleValue + nStarValue;
}

void CExtCharInsidePet::addExp( int64_t nAddExp )
{
	if ( NULL == m_pPet )
	{
		return;
	}

	if ( m_pPet->AddExp( nAddExp ) )
	{
		recalAttr();
		m_pPlayer->recalcAttr();
		m_pPlayer->GetCharPet().RecalPetsAttr();
		sendBaseInfo();
	}
}

void CExtCharInsidePet::calBaseAttr( CObjAttrs::Index_T nIndex, PET_ATTR startAttr, PET_ATTR growAttr )
{
	if ( NULL == m_pPlayer || NULL == m_pPet )
	{
		return;
	}
	int32_t nLevel = m_pPlayer->getLevel();
	m_attrs.SetAttr( nIndex, m_pPet->GetBaseAttr( startAttr ) + m_pPet->GetBaseAttr( growAttr ) * ( nLevel - 1 ) / 1000 );
}

int32_t CExtCharInsidePet::GetPoint()
{
	if ( NULL == m_pPet )
	{
		return 0;
	}
	return m_pPet->GetPoints();
}
