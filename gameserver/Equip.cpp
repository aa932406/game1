
#include <algorithm>

#include "stdafx.h"
#include "Equip.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "EquipManager.h"
#include "RandHelper.h"
#include "EquipRansom.h"

#define USUAL_ITEM		1  //ʹ����ͨ��Ʒ
#define SPECIAL_ITEM	2  //ʹ��������Ʒ

#define SPECIAL_STAT	9					//������Ǽ�,9���Ժ�������ͨ����
#define NEED_GONG_GAO_STAT 6				//6��Ҫ����
#define XIANG_QIAN_GONG_GAO_GEM_LEVEL	5	//��ʯ�����ȼ�
int32_t GemOpenNeedStarLevel[GEM_SLOT_NUM] = { 4, 5, 6 };
#define MAX_SUIT_EQUIP	 120
enum ERR_EQUIP
{
	ERR_EQUIP_UPGRADE_FAIL		= 1,	// װ������ʧ��
	ERR_EQUIP_UPQUALITY_FAIL	= 2,	// װ����Ʒʧ��
	ERR_EQUIP_UPSTAR_FAIL		= 3,	// װ������ʧ��
};

using namespace Answer;

CExtEquip::CExtEquip()
{
	OnCleanUp();
}

CExtEquip::~CExtEquip()
{
}

void CExtEquip::OnCleanUp()
{
	bzero( m_vMemEquip, sizeof( m_vMemEquip ) );
	bzero( m_vMemGem, sizeof( m_vMemGem ) );
	bzero( m_vMemStrengthen, sizeof( m_vMemStrengthen ) );
	bzero( m_vMemPosLevel, sizeof( m_vMemPosLevel ) );
	bzero( m_vShenYaoEquipPos, sizeof( m_vShenYaoEquipPos ) );

	m_lstDirty.clear();										// ������

	m_nEquipGoalStarLevel	= 0;							// ��װǿ���ȼ�
	m_nEquipGoalGemLevel	= 0;							// ��װ��ʯ�ȼ�
	m_mEquipSuit.clear();									// ��װ����
}

void CExtEquip::OnLoadFromDB( const PlayerDBData& dbData )
{
	memcpy( m_vMemEquip, dbData.equipData.charEquip, sizeof( m_vMemEquip ) );
	memcpy( m_vMemGem, dbData.gemData.data, sizeof( m_vMemGem ) );

	checkEquipGoalStarLevel();
	checkEquipGoalGemLevel();
	checkEquipSuit();
}

void CExtEquip::OnSaveToDB( PlayerDBData& dbData )
{
	memcpy( dbData.equipData.charEquip, m_vMemEquip, sizeof( m_vMemEquip ) );
	memcpy( dbData.gemData.data, m_vMemGem, sizeof( m_vMemGem ) );
	dbData.chr.weapon	= m_vMemEquip[EQUIP_SLOT_WEAPON].itemId;
	dbData.chr.cloth	= m_vMemEquip[EQUIP_SLOT_CLOTH].itemId;
}

void CExtEquip::OnUpdate( int64_t curTick )
{
	checkDirty();
}

void CExtEquip::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back ( CM_EQUIP_REQUEST_INFO );
	procList.push_back ( CM_EQUIP_DRESS );
	procList.push_back ( CM_EQUIP_UNDRESS );
	procList.push_back ( CM_EQUIP_UP_GRADE );
	procList.push_back ( CM_EQUIP_UP_STAR );
	procList.push_back ( CM_EQUIP_UP_QUALITY );
	procList.push_back ( CM_EQUIP_ADD_GEM );
	procList.push_back ( CM_EQUIP_REMOVE_GEM );
	procList.push_back ( CM_EQUIP_ITEM_COMBI );
	procList.push_back ( CM_EQUIP_EXCHANGE_STAR );
	procList.push_back ( CM_NEW_ADD_GEM );
	procList.push_back ( CM_NEW_REMOVE_GEM );
	procList.push_back ( CM_OPQN_GEM_HOLE );
	procList.push_back ( CM_ACHIEVEMENT_UP_XUN_ZHANG );
	procList.push_back ( CM_BACK_EQUIP );
	procList.push_back ( CM_EQUIP_STREN_GHTHEN );
	procList.push_back ( CM_EQUIP_UP_PHASE );
	procList.push_back ( CM_EQUIP_UP_POS );
	procList.push_back ( CM_GEM_ADD );
	procList.push_back ( CM_GEM_LEVEL_UP );
	procList.push_back ( CM_GEM_OPEN_HOLE );
	procList.push_back ( CM_GEM_REMOVE );
	procList.push_back ( CM_MOFU_DUIHUAN );
	procList.push_back ( CM_MOFU_HUISHOU );
	procList.push_back ( CM_RELIEVE_BIND );
	procList.push_back ( CM_SHENYAO_POS_LEVEL_UP );
	procList.push_back ( CM_XINMO_EQUIP_HUISHOU );
}

int32_t CExtEquip::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch ( nProcId )
	{
	case CM_EQUIP_REQUEST_INFO:		return	onRequestEquipInfo( inPacket );
	case CM_EQUIP_DRESS:			return	onEquipDress( inPacket );
	case CM_EQUIP_UNDRESS:			return	onEquipUnDress( inPacket );
	case CM_EQUIP_UP_GRADE:			return	onEquipUpGrade( inPacket );
	case CM_EQUIP_UP_STAR:			return	onEquipUpStar( inPacket );
	case CM_EQUIP_UP_QUALITY:		return	onEquipUpQuality( inPacket );
//	case CM_EQUIP_ADD_GEM:			return	onEquipAddGem( inPacket );
//	case CM_EQUIP_REMOVE_GEM:		return	onEquipRemoveGem( inPacket );
	case CM_EQUIP_ITEM_COMBI:		return	onEquipItemCombi( inPacket );
	case CM_EQUIP_EXCHANGE_STAR:	return	onEquipExchangeStar( inPacket );
	case CM_NEW_ADD_GEM:			return  OnNewEquipAddGem( inPacket );
	case CM_NEW_REMOVE_GEM:			return  OnNewEquipRemoveGem( inPacket );
	case CM_OPQN_GEM_HOLE:			return  OnNewEquipOpenHole( inPacket );
	case CM_ACHIEVEMENT_UP_XUN_ZHANG: return onUpXunZhangLevel( inPacket );
	case CM_BACK_EQUIP:			return onBackEquip( inPacket );
	case CM_EQUIP_STREN_GHTHEN:	return onEquipStrenGthen( inPacket );
	case CM_EQUIP_UP_PHASE:		return onEquipUpPhase( inPacket );
	case CM_EQUIP_UP_POS:		return onEquipUpPos( inPacket );
	case CM_GEM_ADD:			return onGemAdd( inPacket );
	case CM_GEM_LEVEL_UP:		return onGemLevelUp( inPacket );
	case CM_GEM_OPEN_HOLE:		return onGemOpenHole( inPacket );
	case CM_GEM_REMOVE:			return onGemRemove( inPacket );
	case CM_MOFU_DUIHUAN:		return onMoFuDuiHuan( inPacket );
	case CM_MOFU_HUISHOU:		return onMoFuHuiShou( inPacket );
	case CM_RELIEVE_BIND:		return onRelieveBind( inPacket );
	case CM_SHENYAO_POS_LEVEL_UP:	return onShenYaoPosLevelUp( inPacket );
	case CM_XINMO_EQUIP_HUISHOU:	return OnXinMoEquipHuiShou( inPacket );
	default:	break;
	}
	return ERR_OK;
}

int32_t CExtEquip::onRequestEquipInfo( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	EquipId_t nEquipId = inPacket->readInt64();
	MemEquip equip = EQUIP_MANAGER.GetMemEquip( nEquipId );
	if ( equip.id != nEquipId )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->sendEquipInfo( equip );
	return ERR_OK;
}

int32_t CExtEquip::onEquipDress( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t	nBagSlot	= inPacket->readInt32();
	int8_t	nEquipSlot	= inPacket->readInt8();

	if ( !onEquipExchange( nBagSlot, nEquipSlot ) )
	{
		return ERR_SYETEM_ERR;
	}
	//checkGemSlotOpen();
	return ERR_OK;
}

int32_t CExtEquip::onEquipUnDress( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t	nEquipSlot	= inPacket->readInt8();

	int32_t nBagSlot = m_pPlayer->getFirstFreeSlot();
	if ( nBagSlot < 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !onEquipExchange( nBagSlot, nEquipSlot ) )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtEquip::onEquipUpGrade( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t nUpType  = inPacket->readInt8();
	int8_t nBagType	= inPacket->readInt8();
	int32_t nPos	= inPacket->readInt32();
	int8_t nAutoBuy	= inPacket->readInt8();

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	MemChrBag bagItem = {};
	if ( nBagType == CBT_EQUIP )
	{
		if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		bagItem = m_vMemEquip[nPos];
	}
	else if ( nBagType == CBT_BAG )
	{
		bagItem = m_pPlayer->getBagSlotData( nPos );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( bagItem.itemClass != IC_EQUIP || bagItem.itemId <= 0 || bagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip equip = EQUIP_MANAGER.GetMemEquip( bagItem.srcId );
	if ( equip.base != bagItem.itemId )
	{
		return ERR_SYETEM_ERR;
	}

	const CfgEquipUpGrade* pCfgUpGrade = CFG_DATA.GetEquipTable().GetEquipUpGrade( bagItem.itemId );
	if ( NULL == pCfgUpGrade )
	{
		return ERR_SYETEM_ERR;
	}

	const CfgEquip* pDestEquip = CFG_DATA.GetEquipTable().GetEquip( pCfgUpGrade->m_nGiveId );
	if ( NULL == pDestEquip )
	{
		return ERR_SYETEM_ERR;
	}

	if ( m_pPlayer->getLevel() < pDestEquip->m_nLevel || m_pPlayer->GetSoulLevel() < pDestEquip->m_nSoulLevel )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t		BindCount		= 0;
	int32_t		UnBindCount		= 0;
	if ( SPECIAL_ITEM == nUpType )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( pCfgUpGrade->m_CostSpecialItem, IDCR_EQUIP_UPGRADE, BindCount, UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		equip.base = pCfgUpGrade->m_nGiveId;
		equip.UpGradeLucky = 0;
		++equip.nFlag;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		if ( nBagType == CBT_EQUIP )
		{
			if ( BindCount > 0 )
			{
				m_vMemEquip[nPos].bind = IBS_BIND;
			}
			m_vMemEquip[nPos].itemId = pCfgUpGrade->m_nGiveId;
			addDirty( nPos );
			checkEquipSuit();
			m_pPlayer->recalcAttr();
			m_pPlayer->GetTask().updateTaskCount( TC_DRESS_EQUIP );
			if ( nPos == EQUIP_SLOT_WEAPON || nPos == EQUIP_SLOT_CLOTH )
			{
				m_pPlayer->setSyncStatusFlag();
				m_pPlayer->setSyncToTeamFlag();
				if ( nPos == EQUIP_SLOT_WEAPON )
				{
					m_pPlayer->sendUpdateSocialPlayerInfo( PII_WEAPON, pCfgUpGrade->m_nGiveId );
				}
				else if ( nPos == EQUIP_SLOT_CLOTH )
				{
					m_pPlayer->sendUpdateSocialPlayerInfo( PII_CLOTH, pCfgUpGrade->m_nGiveId );
				}
			}
		}
		else
		{
			if ( BindCount > 0 )
			{
				bagItem.bind = IBS_BIND;
			}
			bagItem.itemId = pCfgUpGrade->m_nGiveId;
			m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
		}
		m_pPlayer->GetTask().updateTaskCount( TC_UP_EQUIP_GRADE );
		EquipUpGradeGongGao( pCfgUpGrade->m_nGiveId, pCfgUpGrade->m_nId, equip.id );
		GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), pCfgUpGrade->m_nGiveId );
		return ERR_OK;
	}

	if ( nAutoBuy > 0 )
	{
		int32_t nBuyCount = 0;
		ItemData costItem = pCfgUpGrade->m_CostUsualItem;
		int32_t	nItemCount = m_pPlayer->GetBag().GetItemCount( vSlot, costItem.m_nClass, costItem.m_nId );
		if ( nItemCount < costItem.m_nCount )
		{
			nBuyCount = costItem.m_nCount - nItemCount;
			costItem.m_nCount = nItemCount;
		}
		int32_t nCostGold = 0;
		int32_t nShopId = 0;
		if ( nBuyCount > 0 )
		{
			CfgGameShop *pCfgGameShop = CFG_DATA.GetGameShopItem( costItem.m_nClass, costItem.m_nId );
			if ( NULL == pCfgGameShop )
			{
				return ERR_SYETEM_ERR;
			}
			nShopId = pCfgGameShop->ShopId;
			nCostGold = nBuyCount * pCfgGameShop->Price;
			if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nCostGold )
			{
				return ERR_SYETEM_ERR;
			}
		}
		if ( costItem.m_nCount > 0 && !m_pPlayer->GetBag().RemoveItem( costItem, IDCR_EQUIP_UPGRADE, BindCount, UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		if ( nCostGold > 0 )
		{
			if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_EQUIP_UPGRADE_AUTOBUY, nShopId ) )
			{
				return ERR_SYETEM_ERR;
			}
		}

	}
	else
	{
		if ( !m_pPlayer->GetBag().RemoveItem( pCfgUpGrade->m_CostUsualItem, IDCR_EQUIP_UPGRADE, BindCount, UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	if ( nBagType == CBT_EQUIP )
	{
		if ( BindCount > 0 )
		{
			m_vMemEquip[nPos].bind = IBS_BIND;
			addDirty( nPos );
		}
	}
	else
	{
		if ( BindCount > 0 )
		{
			bagItem.bind = IBS_BIND;
			m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
		}
	}
	bool bSuccess = false;
	if ( equip.UpGradeLucky >= pCfgUpGrade->m_nSuccessLine )
	{
		bSuccess = true;
	}
	else if ( equip.UpGradeLucky >= pCfgUpGrade->m_nFailLine )
	{
		int32_t nRand = RANDOM.generate( 1, pCfgUpGrade->m_nTotalRate );
		if ( nRand <= pCfgUpGrade->m_nRate )
		{
			bSuccess = true;
		}
	}
	m_pPlayer->GetTask().updateTaskCount( TC_UP_EQUIP_GRADE );
	if ( !bSuccess )
	{
		equip.UpGradeLucky += pCfgUpGrade->m_nGetLucky;
		++equip.nFlag;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_EQUIP_UPGRADE_FAIL, pCfgUpGrade->m_nGetLucky );
		return ERR_SYETEM_ERR;
	}

	equip.base = pCfgUpGrade->m_nGiveId;
	equip.UpGradeLucky = 0;
	++equip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( equip );
	if ( nBagType == CBT_EQUIP )
	{
		m_vMemEquip[nPos].itemId = pCfgUpGrade->m_nGiveId;
		addDirty( nPos );
		checkEquipSuit();
		m_pPlayer->recalcAttr();
		if ( nPos == EQUIP_SLOT_WEAPON || nPos == EQUIP_SLOT_CLOTH )
		{
			m_pPlayer->setSyncStatusFlag();
			m_pPlayer->setSyncToTeamFlag();
			if ( nPos == EQUIP_SLOT_WEAPON )
			{
				m_pPlayer->sendUpdateSocialPlayerInfo( PII_WEAPON, pCfgUpGrade->m_nGiveId );
			}
			else if ( nPos == EQUIP_SLOT_CLOTH )
			{
				m_pPlayer->sendUpdateSocialPlayerInfo( PII_CLOTH, pCfgUpGrade->m_nGiveId );
			}
		}
		m_pPlayer->GetTask().updateTaskCount( TC_DRESS_EQUIP );
	}
	else
	{
		bagItem.itemId = pCfgUpGrade->m_nGiveId;
		m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
	}
	EquipUpGradeGongGao( pCfgUpGrade->m_nGiveId, pCfgUpGrade->m_nId,equip.id );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), pCfgUpGrade->m_nGiveId );
	return ERR_OK;
}

int32_t CExtEquip::onEquipUpStar( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t nUpType  = inPacket->readInt8();
	int8_t nBagType	= inPacket->readInt8();
	int32_t nPos	= inPacket->readInt32();
	int8_t nAutoBuy	= inPacket->readInt8();

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	MemChrBag bagItem = {};
	if ( nBagType == CBT_EQUIP )
	{
		if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		bagItem = m_vMemEquip[nPos];
	}
	else if ( nBagType == CBT_BAG )
	{
		bagItem = m_pPlayer->getBagSlotData( nPos );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( bagItem.itemClass != IC_EQUIP || bagItem.itemId <= 0 || bagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip equip = EQUIP_MANAGER.GetMemEquip( bagItem.srcId );
	if ( equip.base != bagItem.itemId )
	{
		return ERR_SYETEM_ERR;
	}
	if ( equip.star >= EQUIP_MAX_STAT )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgEquipUpStar* pCfgUpStar = CFG_DATA.GetEquipTable().GetEquipUpStar( equip.star );
	if ( NULL == pCfgUpStar )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t BindCount	= 0;
	int32_t UnBindCount = 0;
	if ( SPECIAL_ITEM == nUpType )
	{
		if ( SPECIAL_STAT <= equip.star )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->GetBag().RemoveItem( pCfgUpStar->m_CostSpecialItem, IDCR_EQUIP_UPSTAR, BindCount,UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		if ( nBagType == CBT_EQUIP )
		{
			m_pPlayer->recalcAttr();
			m_pPlayer->GetTask().updateTaskCount( TC_EQUIP_STAR_COUNT );
		}
		UpStarSuccess( equip, nBagType, nPos, bagItem, BindCount > 0 ? true:false );
		GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), equip.star );
		m_pPlayer->GetTask().updateTaskCount( TC_UP_EQUIP_STAR );
		m_pPlayer->GetAchievemnet().AddAchievement( AT_EQUIP_UP_STAR );
		m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_EQUIP_STAT_UP );
		m_pPlayer->GetAchievemnet().AddAchievement( AT_DRESS_EQUIP );
		return ERR_OK;
	}
	if ( nAutoBuy > 0 )
	{
		int32_t nBuyCount = 0;
		ItemData costItem = pCfgUpStar->m_CostUsualItem;
		int32_t	nItemCount = m_pPlayer->GetBag().GetItemCount( vSlot, costItem.m_nClass, costItem.m_nId );
		if ( nItemCount < costItem.m_nCount )
		{
			nBuyCount = costItem.m_nCount - nItemCount;
			costItem.m_nCount = nItemCount;
		}
		int32_t nCostGold = 0;
		int32_t	nShopId = 0;
		if ( nBuyCount > 0 )
		{
			CfgGameShop *pCfgGameShop = CFG_DATA.GetGameShopItem( costItem.m_nClass, costItem.m_nId );
			if ( NULL == pCfgGameShop )
			{
				return ERR_SYETEM_ERR;
			}
			nShopId = pCfgGameShop->ShopId;
			nCostGold = nBuyCount * pCfgGameShop->Price;
			if ( nCostGold <= 0 )
			{
				return ERR_SYETEM_ERR;
			}
			if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nCostGold )
			{
				return ERR_SYETEM_ERR;
			}
		}
		if ( costItem.m_nCount > 0 && !m_pPlayer->GetBag().RemoveItem( costItem, IDCR_EQUIP_UPSTAR, BindCount,UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		if ( nCostGold > 0 )
		{
			if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_EQUIP_UPSTAR_AUTOBUY, nShopId ) )
			{
				return ERR_SYETEM_ERR;
			}
			m_pPlayer->GetCurrency().SynCurrency();
		}
	}
	else
	{
		if ( !m_pPlayer->GetBag().RemoveItem( pCfgUpStar->m_CostUsualItem, IDCR_EQUIP_UPSTAR, BindCount,UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->GetBag().ForceSendDirty();
	}
	bool bSuccess = false;
	if ( nBagType == CBT_EQUIP )
	{
		if ( BindCount > 0 )
		{
			m_vMemEquip[nPos].bind = IBS_BIND;
			addDirty( nPos );
		}
	}
	else
	{
		if ( BindCount > 0 )
		{
			bagItem.bind = IBS_BIND;
			m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
		}
	}
	if ( equip.star >= SPECIAL_STAT )
	{
		int32_t nRand = RANDOM.generate( 1, pCfgUpStar->m_nTotalRate );
		if ( nRand <= pCfgUpStar->m_nRate )
		{
			bSuccess = true;
		}
	}
	else
	{
		if ( equip.starLucky >= pCfgUpStar->m_nSuccessLine )
		{
			bSuccess = true;
		}
		else if ( equip.starLucky >= pCfgUpStar->m_nFailLine )
		{
			int32_t nRand = RANDOM.generate( 1, pCfgUpStar->m_nTotalRate );
			if ( nRand <= pCfgUpStar->m_nRate )
			{
				bSuccess = true;
			}
		}
	}
	m_pPlayer->GetTask().updateTaskCount( TC_UP_EQUIP_STAR );
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_EQUIP_STAT_UP );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_EQUIP_UP_STAR );
	if ( !bSuccess )
	{
		if ( SPECIAL_STAT < equip.star )
		{
			equip.star--;
			equip.starLucky = 0;
		}
		else if ( SPECIAL_STAT == equip.star )
		{
			//9Ã¯Â¿Â½Ã¯Â¿Â½Ã¯Â¿Â½Ã¯Â¿Â½ÃÂ§Ã¯Â¿Â½Ã¯Â¿Â½,ÃÂ°Ã¯Â¿Â½Ã¯Â¿Â½ÃÂ²ÃÂ´Ã¯Â¿Â½Ã¯Â¿Â½ÃÂ»Ã¯Â¿Â½ÃÂ±Ã¯Â¿Â½
			GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_EQUIP_UPSTAR_FAIL, equip.star );
			return ERR_SYETEM_ERR;
		}
		else
		{
			equip.starLucky += pCfgUpStar->m_nFailAddLucky;
		}
		++equip.nFlag;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		if ( SPECIAL_STAT <= equip.star )
		{
			GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_EQUIP_UPSTAR_FAIL, equip.star );
		}
		else
		{
			GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_EQUIP_UPSTAR_FAIL, pCfgUpStar->m_nFailAddLucky );
		}

		return ERR_SYETEM_ERR;
	}
	UpStarSuccess( equip, nBagType, nPos, bagItem, BindCount > 0 ? true:false );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_DRESS_EQUIP );
	if ( nBagType == CBT_EQUIP )
	{
		m_pPlayer->recalcAttr();
		m_pPlayer->GetTask().updateTaskCount( TC_EQUIP_STAR_COUNT );
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), equip.star );
	return ERR_OK;
}

void CExtEquip::UpStarSuccess( MemEquip& equip, int8_t nBagType, int8_t nPos, MemChrBag& bagItem, bool bBind  )
{
	++equip.star;
	equip.starLucky = 0;
	++equip.nFlag;
	if ( nBagType == CBT_EQUIP )
	{
		if ( bBind )
		{
			m_vMemEquip[nPos].bind = IBS_BIND;
		}
		addDirty( nPos );
		checkEquipSuit();
		m_pPlayer->recalcAttr();
	}
	else
	{
		if ( bBind )
		{
			bagItem.bind = IBS_BIND;
		}
		m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
		m_pPlayer->GetBag().ForceSendDirty();
	}
	EQUIP_MANAGER.UpdateMemEquip( equip );
	if ( nBagType == CBT_EQUIP )
	{
		checkEquipGoalStarLevel();
		m_pPlayer->recalcAttr();
	}
	if ( equip.star >= NEED_GONG_GAO_STAT )
	{
		EquipUpStarGongGao( equip );
	}
}

int32_t CExtEquip::onEquipUpQuality( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t  nUpType     = inPacket->readInt8();
	int8_t	nBagType	= inPacket->readInt8();
	int32_t	nPos		= inPacket->readInt32();
	int8_t	nAutoBuy	= inPacket->readInt8();

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	MemChrBag bagItem = {};
	if ( nBagType == CBT_EQUIP )
	{
		if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		bagItem = m_vMemEquip[nPos];
	}
	else if ( nBagType == CBT_BAG )
	{
		bagItem = m_pPlayer->getBagSlotData( nPos );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( bagItem.itemClass != IC_EQUIP || bagItem.itemId <= 0 || bagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip equip = EQUIP_MANAGER.GetMemEquip( bagItem.srcId );
	if ( equip.base != bagItem.itemId )
	{
		return ERR_SYETEM_ERR;
	}

	const CfgEquipUpQuality* pCfgUpQuality = CFG_DATA.GetEquipTable().GetEquipUpQuality( bagItem.itemId );
	if ( NULL == pCfgUpQuality )
	{
		return ERR_SYETEM_ERR;
	}

	const CfgEquip* pDestEquip = CFG_DATA.GetEquipTable().GetEquip( pCfgUpQuality->m_nGiveId );
	if ( NULL == pDestEquip )
	{
		return ERR_SYETEM_ERR;
	}

	if ( m_pPlayer->getLevel() < pDestEquip->m_nLevel )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t		BindCount	= 0;
	int32_t		UnBindCount	= 0;
	if ( SPECIAL_ITEM == nUpType )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( pCfgUpQuality->m_CostSpecialItem, IDCR_EQUIP_UPQUALITY, BindCount,UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		equip.base = pCfgUpQuality->m_nGiveId;
		equip.UpGradeLucky = 0;
		if ( nBagType == CBT_EQUIP )
		{
			if ( BindCount > 0 )
			{
				m_vMemEquip[nPos].bind = IBS_BIND;
			}
			m_vMemEquip[nPos].itemId = pCfgUpQuality->m_nGiveId;
			addDirty( nPos );
			sendDirty();
			checkEquipSuit();
			if ( nPos == EQUIP_SLOT_WEAPON || nPos == EQUIP_SLOT_CLOTH )
			{
				m_pPlayer->setSyncStatusFlag();
				m_pPlayer->setSyncToTeamFlag();
				if ( nPos == EQUIP_SLOT_WEAPON )
				{
					m_pPlayer->sendUpdateSocialPlayerInfo( PII_WEAPON, pCfgUpQuality->m_nGiveId );
				}
				else if ( nPos == EQUIP_SLOT_CLOTH )
				{
					m_pPlayer->sendUpdateSocialPlayerInfo( PII_CLOTH, pCfgUpQuality->m_nGiveId );
				}
			}
			
		}
		else
		{
			if ( BindCount > 0 )
			{
				bagItem.bind	= IBS_BIND;
			}
			bagItem.itemId = pCfgUpQuality->m_nGiveId;
			m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
			m_pPlayer->GetBag().ForceSendDirty();
		}
		UpQualityOpenGemHole( equip, pCfgUpQuality, nBagType, nPos );
		++equip.nFlag;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		if ( nBagType == CBT_EQUIP )
		{
			m_pPlayer->recalcAttr();
		}
		if ( pDestEquip->m_nQuality == IQ_GOLD )
		{
			EquipUpQualityGongGao( pCfgUpQuality->m_nGiveId, pCfgUpQuality->m_nId, equip.id );
		}
		m_pPlayer->GetTask().updateTaskCount( TC_UP_EQUIP_QUALITY );
		GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), pCfgUpQuality->m_nGiveId );
		return ERR_OK;
	}

	if ( nAutoBuy > 0 )
	{
		int32_t nBuyCount = 0;
		ItemData costItem = pCfgUpQuality->m_CostUsualItem;
		int32_t	nItemCount = m_pPlayer->GetBag().GetItemCount( vSlot, costItem.m_nClass, costItem.m_nId );
		if ( nItemCount < costItem.m_nCount )
		{
			nBuyCount = costItem.m_nCount - nItemCount;
			costItem.m_nCount = nItemCount;
		}
		int32_t nCostGold = 0;
		int32_t nShopId = 0;
		if ( nBuyCount > 0 )
		{
			CfgGameShop *pCfgGameShop = CFG_DATA.GetGameShopItem( costItem.m_nClass, costItem.m_nId );
			if ( NULL == pCfgGameShop )
			{
				return ERR_SYETEM_ERR;
			}
			nShopId = pCfgGameShop->ShopId;
			nCostGold = nBuyCount * pCfgGameShop->Price;
			if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nCostGold )
			{
				return ERR_SYETEM_ERR;
			}
		}
		if ( costItem.m_nCount > 0 && !m_pPlayer->GetBag().RemoveItem( costItem, IDCR_EQUIP_UPQUALITY, BindCount, UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		if ( nCostGold > 0 )
		{
			if( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_EQUIP_UPQUALITY_AUTOBUY, nShopId ) )
			{
				return ERR_SYETEM_ERR;
			}
		}

	}
	else
	{
		if ( !m_pPlayer->GetBag().RemoveItem( pCfgUpQuality->m_CostUsualItem, IDCR_EQUIP_UPQUALITY, BindCount,UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	if ( nBagType == CBT_EQUIP )
	{
		if ( BindCount > 0 )
		{
			m_vMemEquip[nPos].bind = IBS_BIND;
			addDirty( nPos );
		}
	}
	else
	{
		if ( BindCount > 0 )
		{
			bagItem.bind = IBS_BIND;
			m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
		}
	}
	bool bSuccess = false;
	if ( equip.UpQuality >= pCfgUpQuality->m_nSuccessLine )
	{
		bSuccess = true;
	}
	else if ( equip.UpQuality >= pCfgUpQuality->m_nFailLine )
	{
		int32_t nRand = RANDOM.generate( 1, pCfgUpQuality->m_nTotalRate );
		if ( nRand <= pCfgUpQuality->m_nRate )
		{
			bSuccess = true;
		}
	}
	m_pPlayer->GetTask().updateTaskCount( TC_UP_EQUIP_QUALITY );
	if ( !bSuccess )
	{
		equip.UpQuality += pCfgUpQuality->m_nGetLucky;
		++equip.nFlag;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_EQUIP_UPQUALITY_FAIL, pCfgUpQuality->m_nGetLucky );
		return ERR_SYETEM_ERR;
	}

	equip.base		= pCfgUpQuality->m_nGiveId;
	equip.UpQuality = 0;
	if ( nBagType == CBT_EQUIP )
	{
		m_vMemEquip[nPos].itemId = pCfgUpQuality->m_nGiveId;
		addDirty( nPos );
		sendDirty();
		checkEquipSuit();
		if ( nPos == EQUIP_SLOT_WEAPON || nPos == EQUIP_SLOT_CLOTH )
		{
			m_pPlayer->setSyncStatusFlag();
			m_pPlayer->setSyncToTeamFlag();
			if ( nPos == EQUIP_SLOT_WEAPON )
			{
				m_pPlayer->sendUpdateSocialPlayerInfo( PII_WEAPON, pCfgUpQuality->m_nGiveId );
			}
			else if ( nPos == EQUIP_SLOT_CLOTH )
			{
				m_pPlayer->sendUpdateSocialPlayerInfo( PII_CLOTH, pCfgUpQuality->m_nGiveId );
			}
		}
	}
	else
	{
		bagItem.itemId = pCfgUpQuality->m_nGiveId;
		m_pPlayer->GetBag().SetSlotData( nPos, bagItem );
		m_pPlayer->GetBag().ForceSendDirty();
	}
	UpQualityOpenGemHole( equip, pCfgUpQuality,  nBagType, nPos );
	++equip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( equip );
	if ( nBagType == CBT_EQUIP )
	{
		m_pPlayer->recalcAttr();
	}
	if ( pDestEquip->m_nQuality == IQ_GOLD )
	{
		EquipUpQualityGongGao( pCfgUpQuality->m_nGiveId, pCfgUpQuality->m_nId,equip.id );
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), pCfgUpQuality->m_nGiveId );
	return ERR_OK;
}

void CExtEquip::UpQualityOpenGemHole( MemEquip& equip, const CfgEquipUpQuality* pCfgUpQuality , int8_t BagType, int32_t slot)
{
	if ( NULL == pCfgUpQuality )
	{
		return;
	}
	if ( equip.GemHole[0] < 0 )
	{
		int32_t nRand = RANDOM.generate( 1, 10000 );
		if ( nRand <= pCfgUpQuality->m_OpenHoleRate )
		{
			equip.GemHole[0] = 0;
			m_pPlayer->sendEquipInfo( equip );
			SendOpenGemHole( 0, BagType, slot );
			EquipUpQualityOpenGemHole( equip, 0 );
		}
	}
	else if( equip.GemHole[1] < 0 )
	{
		int32_t nRand = RANDOM.generate( 1, 10000 );
		if ( nRand <= pCfgUpQuality->m_OpenSecondHoleRate )
		{
			equip.GemHole[1] = 0;
			m_pPlayer->sendEquipInfo( equip );
			SendOpenGemHole( 1,  BagType, slot );
			EquipUpQualityOpenGemHole( equip, 1 );
		}
	}
}

void CExtEquip::SendOpenGemHole( int8_t HoleIndex, int8_t BagType, int32_t slot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_OPEN_GEM_HOLE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( HoleIndex );
	packet->writeInt8( BagType );
	packet->writeInt32( slot );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t CExtEquip::onEquipAddGem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t	nEquipPos	= inPacket->readInt8();
	int32_t nBagSlot	= inPacket->readInt32();

	if ( nEquipPos < 0 || nEquipPos >= EQUIP_SLOT_TOTAL_NUM )
	{
		return ERR_SYETEM_ERR;
	}

	MemChrBag item = m_pPlayer->getBagSlotData( nBagSlot );
	if ( item.itemId <= 0 || item.itemClass != IC_GEM || item.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( item.itemId );
	if ( NULL == pGem )
	{
		return ERR_SYETEM_ERR;
	}

	if ( pGem->m_nLevel >  m_pPlayer->getLevel() )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t nGemSlot = getGemSlot( pGem->m_nType );
	if ( nGemSlot < 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !isGemSlotOpen( nGemSlot ) )
	{
		return ERR_SYETEM_ERR;
	}

	ItemData data = {};
	data.m_nId			= item.itemId;
	data.m_nClass		= item.itemClass;
	data.m_nCount		= 1;

	if ( m_vMemGem[nEquipPos][nGemSlot] > 0 )
	{
		MemChrBag addGem = {};
		addGem.itemId		= m_vMemGem[nEquipPos][nGemSlot];
		addGem.itemClass	= IC_GEM;
		addGem.bind			= IBS_BIND;
		addGem.itemCount	= 1;


		Int32Vector vSlot( 1, nBagSlot );

		if ( !m_pPlayer->GetBag().AddAndRemoveItem( addGem, IACR_REMOVE_GEM, vSlot, data, IDCR_ADD_GEM ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		Int32Vector vSlot( 1, nBagSlot );
		if ( !m_pPlayer->GetBag().RemoveItem( vSlot, data, IDCR_ADD_GEM ) )
		{
			return ERR_SYETEM_ERR;
		}
	}

	m_vMemGem[nEquipPos][nGemSlot] = pGem->m_nId;

	checkEquipGoalGemLevel();
	m_pPlayer->recalcAttr();
	SendGemInfo( nEquipPos, (int8_t)nGemSlot );
	
	LogEquipAddGem equipAddGemLog = {};

	equipAddGemLog.cid			= m_pPlayer->getCid();
	snprintf(equipAddGemLog.name, sizeof(equipAddGemLog.name)-1, m_pPlayer->getName().c_str());
	//snprintf(equipAddGemLog.equip_name, sizeof(equipAddGemLog.equip_name)-1, pEquip->name.c_str());
	//snprintf(equipAddGemLog.gem_name, sizeof(equipAddGemLog.gem_name)-1, pGem->name.c_str());
	//equipAddGemLog.equip_quality = pEquip->quality;
	equipAddGemLog.equip_quality= nEquipPos;
	equipAddGemLog.gem_level	= pGem->m_nLevel;
	equipAddGemLog.time			= m_pPlayer->getNow();

	DB_SERVICE.insertEquipAddgem( equipAddGemLog );
	
	return ERR_OK;
}

int32_t CExtEquip::onEquipRemoveGem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t nPos		= inPacket->readInt8();
	int8_t nSlot	= inPacket->readInt8();

	if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM || nSlot < 0 || nSlot >= GEM_SLOT_NUM )
	{
		return ERR_SYETEM_ERR;
	}

	if ( 0 == m_vMemGem[nPos][nSlot] )
	{
		return ERR_SYETEM_ERR;
	}

	MemChrBag addGem  = {};
	addGem.itemId		= m_vMemGem[nPos][nSlot];
	addGem.itemClass	= IC_GEM;
	addGem.bind			= IBS_BIND;
	addGem.itemCount	= 1;
	if ( !m_pPlayer->GetBag().AddItem( addGem, IACR_REMOVE_GEM ) )
	{
		return ERR_INVALID_DATA;
	}

	m_vMemGem[nPos][nSlot] = 0;
	checkEquipGoalGemLevel();
	m_pPlayer->recalcAttr();
	SendGemInfo( nPos, nSlot );

	LogEquipRemoveGem equipRemoveGemLog = {};

	equipRemoveGemLog.cid			= m_pPlayer->getCid();
	snprintf(equipRemoveGemLog.name, sizeof(equipRemoveGemLog.name)-1, m_pPlayer->getName().c_str());
	equipRemoveGemLog.time			= m_pPlayer->getNow();
	//equipRemoveGemLog.eid			= pMemEquip->id;
	//equipRemoveGemLog.baseid		= pMemEquip->base;
	equipRemoveGemLog.slot_index	= nPos;
	equipRemoveGemLog.stone_id		= addGem.itemId;

	DB_SERVICE.logEquipRemoveGem( equipRemoveGemLog );

	return ERR_OK;
}

bool CExtEquip::checkCombiItemList( ItemDataList& NeedItemList, Int32Vector& vSlot, int32_t& nCanGiveCount, int32_t& nCanGiveUnBindCount ) const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	bool IsSucceed = false;
	int32_t isize = vSlot.size();
	ItemDataList::iterator it = NeedItemList.begin();
	int32_t ItemIndex = 0;	//ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ¼ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·
	for ( ; it != NeedItemList.end(); ++it )
	{
		ItemIndex++;
		IsSucceed = true;
		int32_t nItemCount		= 0;
		int32_t nUnBindCount	= 0;
		Int32Vector SlotID;
		SlotID.clear();
		for ( int32_t i = 0; i < isize; ++i )
		{
			if ( !m_pPlayer->GetBag().IsSlotValid( vSlot[i] ) )
			{
				return false;
			}
			//ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ¶ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ¸ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½id
			Int32Vector::iterator Slotit = SlotID.begin();
			for ( ; Slotit != SlotID.end(); ++Slotit )
			{
				if ( *Slotit == vSlot[i] )
				{
					return false;
				}
			}
			SlotID.push_back( vSlot[i] );
			const MemChrBag& bagItem = m_pPlayer->GetBag().GetSlotData( vSlot[i] );
			if ( bagItem.itemId != it->m_nId 
				|| bagItem.itemClass != it->m_nClass 
				|| bagItem.itemCount <= 0
				|| bagItem.endTime != 0 )		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ±ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ²ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ³ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
			{
				continue;
			}
			if ( bagItem.bind == IBS_UNBIND )
			{
				nUnBindCount += bagItem.itemCount;
			}
			nItemCount += bagItem.itemCount;
		}
		if ( ItemIndex == 1 )
		{
			nCanGiveUnBindCount = nUnBindCount / it->m_nCount;
			nCanGiveCount		= nItemCount / it->m_nCount;
		}
		if ( ( nUnBindCount / it->m_nCount ) < nCanGiveUnBindCount )
		{
			nCanGiveUnBindCount = nUnBindCount / it->m_nCount;
		}
		if ( nItemCount / it->m_nCount < nCanGiveCount )
		{
			nCanGiveCount = nItemCount / it->m_nCount;
		}
	}
	if ( IsSucceed )
	{
		return true;
	}
	return false;
}

int32_t CExtEquip::onEquipItemCombi( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
 		{
 			return ERR_SYETEM_ERR;
 		}
 	
 		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
 		int32_t nId			= inPacket->readInt32();
 		int32_t nTimes		= inPacket->readInt32();
 	
 		Int32Vector vSlot;
 		m_pPlayer->queryBagInfo( inPacket, vSlot );
 		int8_t AutoBuy		= inPacket->readInt8();
 		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ¶ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
 		if ( nTimes <= 0 )
 		{
 			return ERR_SYETEM_ERR;
 		}
 	
 		const CfgItemCombi* pCfgItemCombi = CFG_DATA.GetItemCombiTable().GetItemCombi( nId );
 		if ( NULL == pCfgItemCombi )
 		{
 			return ERR_SYETEM_ERR;
 		}
 	
		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ®ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
		if ( pCfgItemCombi->m_nMoney < 0 )
		{
			return ERR_SYETEM_ERR;
		}
		int64_t nRamainMoney = m_pPlayer->GetCurrency().GetMoneyBindAndNoBind();
		if ( nRamainMoney < pCfgItemCombi->m_nMoney * nTimes )
		{
			return ERR_SYETEM_ERR;
		}
		
		ItemDataList NeedItemList	= pCfgItemCombi->CostList;
 		int32_t nGiveId		= pCfgItemCombi->m_nGiveId;
 		int8_t nGiveClass	= pCfgItemCombi->m_nGiveClass;
 		int32_t nGiveCount	= pCfgItemCombi->m_nGiveCount;
		
		ItemDataList::iterator it = NeedItemList.begin();
		int32_t CanCombiBindTimes = 0;
		int32_t CanCombiAllTimes  = 0;
		int32_t NeedGold		  = 0;
		ItemDataList SubItem;
		for ( ; it != NeedItemList.end(); ++it )
		{
			int32_t HaveBindCount	= m_pPlayer->GetBag().HaveItemCount( *it, true, false );
			int32_t HaveUnBindCount = m_pPlayer->GetBag().HaveItemCount( *it, false, false );
			if ( (*it).m_nCount * nTimes > HaveBindCount + HaveUnBindCount )
			{
				if ( AutoBuy != 1 )
				{
					return ERR_SYETEM_ERR;
				}
				int32_t DiffCount = (*it).m_nCount * nTimes - (HaveBindCount + HaveUnBindCount);
				CfgGameShop* pShop = CFG_DATA.GetGameShopItem((*it).m_nClass, (*it).m_nId );
				if ( NULL == pShop )
				{
					return ERR_SYETEM_ERR;
				}
				NeedGold += pShop->Price * DiffCount;
				ItemData stu = *it;
				stu.m_nCount = HaveBindCount + HaveUnBindCount;
				SubItem.push_back( stu );
				CanCombiAllTimes = nTimes;
			}
			else
			{
				CanCombiAllTimes  = ( HaveBindCount + HaveUnBindCount ) / (*it).m_nCount;
				if ( CanCombiAllTimes > nTimes )
				{
					CanCombiAllTimes = nTimes;
				}
				ItemData stu = *it;
				stu.m_nCount = CanCombiAllTimes * (*it).m_nCount;
				SubItem.push_back( stu );
			}
			int32_t BindTimes = HaveBindCount / (*it).m_nCount;
			if ( BindTimes > CanCombiBindTimes )
			{
				CanCombiBindTimes = BindTimes;
			}
			if ( CanCombiAllTimes > BindTimes && HaveBindCount %  (*it).m_nCount != 0 )
			{
				CanCombiBindTimes++;
			}
		}
 		int64_t HaveGold = m_pPlayer->GetCurrency( CURRENCY_GOLD );
		if ( HaveGold < NeedGold )
		{
			return ERR_SYETEM_ERR;
		}
		if ( CanCombiBindTimes > CanCombiAllTimes )
		{
			CanCombiBindTimes = CanCombiAllTimes;
		}
		int32_t  nUnBindTimes = RandHelper::CalRandTimes( CanCombiAllTimes - CanCombiBindTimes, pCfgItemCombi->m_nRate, pCfgItemCombi->m_nTotalRate );
		int32_t nBindTimes	  = RandHelper::CalRandTimes( CanCombiBindTimes, pCfgItemCombi->m_nRate, pCfgItemCombi->m_nTotalRate );
 		int32_t nSuccessTimes = nBindTimes + nUnBindTimes;

		int32_t nGiveBind   = nBindTimes * nGiveCount;
		int32_t nGiveUnBind = nUnBindTimes * nGiveCount;
		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ¾ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
		MemChrBagVector addVt;
		if ( nGiveBind > 0 )
		{
			MemChrBag giveBind = {};
			giveBind.itemId		= nGiveId;
			giveBind.itemClass	= nGiveClass;
			giveBind.itemCount	= nGiveBind;
			giveBind.bind		= IBS_BIND;
			int32_t nLayNum = CFG_DATA.getOverlay( giveBind.itemId, giveBind.itemClass );
			while( giveBind.itemCount > 0 )
			{
				if ( giveBind.itemCount > nLayNum )
				{
					MemChrBag item = giveBind;
					item.itemCount = nLayNum;
					giveBind.itemCount -= nLayNum;
					addVt.push_back( item );
				}
				else
				{
					addVt.push_back( giveBind );
					giveBind.itemCount = 0;
				}
			}
		}
		if ( nGiveUnBind > 0 )
		{
			MemChrBag giveUnBind = {};
			giveUnBind.itemId		= nGiveId;
			giveUnBind.itemClass	= nGiveClass;
			giveUnBind.itemCount	= nGiveUnBind;
			giveUnBind.bind			= IBS_UNBIND;
			int32_t nLayNum = CFG_DATA.getOverlay( giveUnBind.itemId, giveUnBind.itemClass );
			while( giveUnBind.itemCount > 0 )
			{
				if ( giveUnBind.itemCount > nLayNum )
				{
					MemChrBag item = giveUnBind;
					item.itemCount = nLayNum;
					giveUnBind.itemCount -= nLayNum;
					addVt.push_back( item );
				}
				else
				{
					addVt.push_back( giveUnBind );
					giveUnBind.itemCount = 0;
				}
			}
		}
		if ( nGiveClass == IC_PET_EGG )
		{
			if ( m_pPlayer->GetCharPet().GetEggBagAddHatchBagFreeCount() < nGiveBind + nGiveUnBind )
			{
				m_pPlayer->TiShiInfo( PET_EGG_BAG_NOT_ENOUGH );
				return ERR_SYETEM_ERR;
			}
		}
		else
		{
			if ( m_pPlayer->GetBag().GetFreeSlotCount() < static_cast<int32_t>( addVt.size() ) )
			{
				m_pPlayer->TiShiInfo( BAG_SLOT_NOT_ENOUGH );
				return ERR_SYETEM_ERR;
			}
		}


		if ( !m_pPlayer->GetBag().RemoveCombiItem( SubItem, IDCR_COMBINE ) )
		{
			return ERR_SYETEM_ERR;
		}
		if ( NeedGold > 0 )
		{
			if ( !m_pPlayer->DecCurrency(CURRENCY_GOLD, NeedGold,GCR_ITEM_COMBI_AUTO_BUY, nId) )
			{
				return ERR_SYETEM_ERR;
			}
		}
		if ( pCfgItemCombi->m_nMoney * nTimes > 0 )
		{
			if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfgItemCombi->m_nMoney * nTimes, MCR_COMBI_ITEM ))
			{
				return ERR_SYETEM_ERR;
			}
		}
		
 		if ( nSuccessTimes <= 0 )
 		{
 			GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nSuccessTimes );
 			return ERR_SYETEM_ERR;
 		}
 		if ( !m_pPlayer->GetBag().AddItemsAndEggs( addVt, IACR_COMBINE ) )
 		{
 			return ERR_SYETEM_ERR;
 		}
 		if ( pCfgItemCombi->m_IsGongGao > 0 )
		{
			CombiGongGao( pCfgItemCombi->m_nGiveId, pCfgItemCombi->m_nGiveClass );
		}
 		GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nSuccessTimes );
  	 	return ERR_OK;
}

int32_t CExtEquip::onEquipExchangeStar( NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t	nSrcBagType	= inPacket->readInt8();
	int32_t	nSrcSlot	= inPacket->readInt32();
	int8_t	nDesBagType	= inPacket->readInt8();
	int32_t	nDesSlot	= inPacket->readInt32();
	int8_t  nCostType	= inPacket->readInt8();	

	MemChrBag srcSlot = {};
	if ( nSrcBagType == CBT_EQUIP )
	{
		if ( nSrcSlot < 0 || nSrcSlot >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		srcSlot = GetEquipSlot( nSrcSlot );
	}
	else if ( nSrcBagType == CBT_BAG )
	{
		srcSlot = m_pPlayer->GetBag().GetSlotData( nSrcSlot );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( srcSlot.itemId <= 0 || srcSlot.itemClass != IC_EQUIP || srcSlot.srcId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemChrBag desSlot = {};
	if ( nDesBagType == CBT_EQUIP )
	{
		if ( nDesSlot < 0 || nDesSlot >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		desSlot = GetEquipSlot( nDesSlot );
	}
	else if ( nDesBagType == CBT_BAG )
	{
		desSlot = m_pPlayer->GetBag().GetSlotData( nDesSlot );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( desSlot.itemId <= 0 || desSlot.itemClass != IC_EQUIP || desSlot.srcId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip srcEquip = EQUIP_MANAGER.GetMemEquip( srcSlot.srcId );
	if ( srcEquip.base != srcSlot.itemId )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip desEquip = EQUIP_MANAGER.GetMemEquip( desSlot.srcId );
	if ( desEquip.base != desSlot.itemId )
	{
		return ERR_SYETEM_ERR;
	}
	if ( srcEquip.star <= desEquip.star )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgEquip* pSrcEquip = CFG_DATA.GetEquipTable().GetEquip( srcSlot.itemId );
	const CfgEquip* pDesEquip = CFG_DATA.GetEquipTable().GetEquip( desSlot.itemId );
	if ( NULL == pSrcEquip || NULL == pDesEquip )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pSrcEquip->m_nType != pDesEquip->m_nType )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pSrcEquip->m_nQuality >= pDesEquip->m_nQuality && pSrcEquip->m_nLevel >= pDesEquip->m_nLevel )
	{
		return ERR_SYETEM_ERR;
	}
	CfgEquipExchange* pCfg = CFG_DATA.GetEquipExchange( srcEquip.star );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pCfg->CostType == 1 )
	{
		if ( pCfg->Money <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfg->Money, MCR_EQUIP_EXCHANGE_STAR ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		if ( nCostType == 1 )
		{
			if ( pCfg->MoShi <= 0 )
			{
				return ERR_SYETEM_ERR;
			}
			if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD,pCfg->MoShi,GCR_EQUIP_EXCHANGE_STAR, srcEquip.star ) )
			{
				return ERR_SYETEM_ERR;
			}
		}
		else
		{
			if ( pCfg->BindMoShi <= 0 )
			{
				return ERR_SYETEM_ERR;
			}
			if ( !m_pPlayer->DecCurrency( CURRENCY_CASH,pCfg->BindMoShi,GCC_EQUIP_EXCHANGE_STAR, srcEquip.star ) )
			{
				return ERR_SYETEM_ERR;
			}
		}
	}
	if ( nDesBagType == CBT_EQUIP )
	{
		if ( srcSlot.bind == IBS_BIND || nCostType == 2 )
		{
			m_vMemEquip[nDesSlot].bind = IBS_BIND;
		}
		addDirty( nDesSlot );
		checkDirty();
		m_pPlayer->recalcAttr();
	}
	else
	{
		if ( srcSlot.bind == IBS_BIND || nCostType == 2 )
		{
			desSlot.bind = IBS_BIND;
		}
		m_pPlayer->GetBag().SetSlotData( nDesSlot, desSlot );
		m_pPlayer->GetBag().ForceSendDirty();
	}

	desEquip.star		= srcEquip.star;
	desEquip.starLucky	= srcEquip.starLucky;

	srcEquip.star		= 0;
	srcEquip.starLucky	= 0;

	++srcEquip.nFlag;
	++desEquip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( srcEquip );
	EQUIP_MANAGER.UpdateMemEquip( desEquip );
	if ( nSrcBagType == CBT_EQUIP || nDesBagType == CBT_EQUIP )
	{
		checkEquipGoalStarLevel();
		m_pPlayer->recalcAttr();
	}

// 	MemEquipVector vEquip;
// 	vEquip.reserve( 2 );
// 	vEquip.push_back( srcEquip );
// 	vEquip.push_back( desEquip );
// 	m_pPlayer->sendEquipInfo( vEquip );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t	CExtEquip::onUpXunZhangLevel( Answer::NetPacket * inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	MemChrBag bagItem = m_vMemEquip[EQUIP_SLOT_XUNZHANG];
	CfgXunZhang* pCfg = CFG_DATA.GetXunZhangCfg( bagItem.itemId );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}
	if ( pCfg->CostSocre <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( pCfg->NextEquipId <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_AC_SOCRE, pCfg->CostSocre, ACHIEVEMNET_UP_XUN_ZHANG ) )
	{
		return ERR_INVALID_DATA;
	}
	if ( bagItem.itemId == 0 )
	{
		MemEquip equip = EQUIP_MANAGER.CreateMemEquip( pCfg->NextEquipId, m_pPlayer->getSid(), m_pPlayer->getCid() );
		if ( equip.base != pCfg->NextEquipId )
		{
			return ERR_INVALID_DATA;
		}
		bagItem.itemClass = IC_EQUIP;
		bagItem.itemCount = 1;
		bagItem.bind	  = IBS_BIND;
		bagItem.srcId	  = equip.id;
		bagItem.itemId	  = pCfg->NextEquipId;
		m_pPlayer->sendEquipInfo( equip );
		m_vMemEquip[EQUIP_SLOT_XUNZHANG] = bagItem;
	}
	else
	{
		m_vMemEquip[EQUIP_SLOT_XUNZHANG].itemId	  = pCfg->NextEquipId;
		MemEquip equip = EQUIP_MANAGER.GetMemEquip(m_vMemEquip[EQUIP_SLOT_XUNZHANG].srcId );
		if ( bagItem.itemId != equip.base )
		{
			return ERR_INVALID_DATA;
		}
		equip.base = pCfg->NextEquipId;
		equip.nFlag++;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		m_pPlayer->sendEquipInfo( equip );
	}
	addDirty( EQUIP_SLOT_XUNZHANG );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(),inPacket->getProc(),pCfg->EquipId);
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int8_t CExtEquip::getGemSlot( int8_t nGemType ) const
{
	switch ( nGemType )
	{
	case GEM_TYPE_RED:		return GEM_SLOT_RED;
	case GEM_TYPE_GREEN:	return GEM_SLOT_GREEN;
	case GEM_TYPE_BLUE:		return GEM_SLOT_BLUE;
	default: break;
	}
	return -1;
}

bool CExtEquip::isGemSlotOpen( int8_t nGemSlot )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	if ( m_pPlayer->getRecord( PR_GEM_SLOT_RECORD ) > nGemSlot )
	{
		return true;
	}

	return false;
}

void CExtEquip::checkGemSlotOpen()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int32_t nGemRecord = m_pPlayer->getRecord( PR_GEM_SLOT_RECORD );
	if ( nGemRecord >= GEM_SLOT_NUM )
	{
		return;
	}

	int32_t nMinStar = 99999;
	MemEquip equip;

	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].srcId <= 0 )
		{
			nMinStar = 0;
			break;
		}
		equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
		if ( equip.star < nMinStar )
		{
			nMinStar = equip.star;
		}
	}

	int32_t nOpenLevel = -1;
	for ( int32_t j = 0; j < GEM_SLOT_NUM; ++j )
	{
		if ( nMinStar < GemOpenNeedStarLevel[j] )
		{
			break;
		}
		nOpenLevel = j;
	}

	if ( nOpenLevel >= nGemRecord )
	{
		m_pPlayer->updateRecord( PR_GEM_SLOT_RECORD, nOpenLevel+1 );
	}
}

void CExtEquip::checkEquipGoalStarLevel()
{
	m_nEquipGoalStarLevel = 99999;
	MemEquip equip;

	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].srcId <= 0 )
		{
			m_nEquipGoalStarLevel = 0;
			break;
		}

		equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
		if ( equip.star < m_nEquipGoalStarLevel )
		{
			m_nEquipGoalStarLevel = equip.star;
		}
	}
}

void CExtEquip::checkEquipSuit()
{
	m_mEquipSuit.clear();
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].srcId <= 0 )
		{
			continue;
		}

		const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[i].itemId );
		if ( NULL == pEquip )
		{
			continue;
		}

		int32_t nSuitId = pEquip->m_nSuitId;
		if ( nSuitId <= 0 )
		{
			continue;
		}
		EquipSuitMap::iterator iter = m_mEquipSuit.find( nSuitId );
		if ( iter != m_mEquipSuit.end() )
		{
			iter->second += 1;
		}
		else
		{
			m_mEquipSuit[nSuitId] = 1;
		}
	}
}

void CExtEquip::checkEquipGoalGemLevel()
{
	m_nEquipGoalGemLevel = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		for ( int32_t j = 0; j < GEM_SLOT_NUM; ++j )
		{
			if ( m_vMemGem[i][j] <= 0 )
			{
				continue;
			}

			const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( m_vMemGem[i][j] );
			if ( NULL == pGem )
			{
				continue;
			}

			if ( pGem->m_nQuality == IQ_GOLD )
			{
				m_nEquipGoalGemLevel += pGem->m_nGemLevel;
			}
		}
	}
}

const MemChrBag& CExtEquip::GetEquipSlot( int8_t nSlot ) const
{
	return m_vMemEquip[nSlot];
}

int32_t CExtEquip::GetMaxEquipedStar() const
{
	int32_t nMaxStar = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 || curEquip.itemClass != IC_EQUIP )
		{
			continue;
		}

		MemEquip equip = EQUIP_MANAGER.GetMemEquip( curEquip.srcId );
		if ( equip.base != curEquip.itemId )
		{
			continue;
		}

		if ( equip.star > nMaxStar )
		{
			nMaxStar = equip.star;
		}
	}
	return nMaxStar;
}

void CExtEquip::PackageEquipInfo( Answer::NetPacket* packet ) const
{
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}

	int32_t equipCount = 0;
	int32_t oldBengin = packet->getWOffset();
	packet->writeInt8( equipCount );
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 || curEquip.itemClass != IC_EQUIP )
		{
			continue;
		}

		MemEquip equip = EQUIP_MANAGER.GetMemEquip( curEquip.srcId );
		if ( equip.base != curEquip.itemId )
		{
			continue;
		}

		packet->writeInt64( equip.id );
		packet->writeInt8( i );
		packet->writeInt32( equip.base );
		packet->writeInt32( equip.star );
		packet->writeInt32( equip.starLucky );
		packet->writeInt8( curEquip.bind );
		packet->writeInt32( curEquip.endTime );
		packet->writeInt32( equip.UpGradeLucky );
		packet->writeInt32( equip.UpQuality );
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++ )
		{
			packet->writeInt32( equip.GemHole[i] );
		}
		++equipCount;
	}
	int oldwoffset = packet->getWOffset();
	packet->setWOffset( oldBengin );
	packet->writeInt8( equipCount );
	packet->setWOffset( oldwoffset );
}

void CExtEquip::PackageGemInfo( Answer::NetPacket* packet ) const
{
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}

	int32_t gemCount = 0;
	int32_t oldBengin = packet->getWOffset();
	packet->writeInt8( gemCount );
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		for ( int8_t j = 0; j < GEM_SLOT_NUM; ++j )
		{
			int32_t nGemId = m_vMemGem[i][j];
			if ( nGemId <= 0 )
			{
				continue;
			}

			packet->writeInt8( i );
			packet->writeInt8( j );
			packet->writeInt32( nGemId );
			++gemCount;
		}
	}
	int oldwoffset = packet->getWOffset();
	packet->setWOffset( oldBengin );
	packet->writeInt8( gemCount );
	packet->setWOffset( oldwoffset );
}

void CExtEquip::SendEquipInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_EQUIP_INFO );
	if (NULL == packet)
	{
		return;
	}

	int32_t equipCount = 0;
	int32_t oldBengin = packet->getWOffset();
	packet->writeInt8( equipCount );
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const MemChrBag& tSlot = m_vMemEquip[i];
		packet->writeInt8( i );
		packet->writeInt32( tSlot.itemId );
		packet->writeInt8( tSlot.bind );
		packet->writeInt32( tSlot.endTime );
		packet->writeInt64( tSlot.srcId );

		++equipCount;
	}
	int oldwoffset = packet->getWOffset();
	packet->setWOffset( oldBengin );
	packet->writeInt8( equipCount );
	packet->setWOffset( oldwoffset );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtEquip::SendGemInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_GEM_INFO );
	if (NULL == packet)
	{
		return;
	}

	PackageGemInfo( packet );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtEquip::SendGemInfo( int8_t nPos, int8_t nSlot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM || nSlot < 0 || nSlot >= GEM_SLOT_NUM )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_GEM_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( 1 );
	packet->writeInt8( nPos );
	packet->writeInt8( nSlot );
	packet->writeInt32( m_vMemGem[nPos][nSlot] );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtEquip::AddCharAttr()
{
	addEquipAttr();
	addGemAttr();
	AddStrengthenAttr();
	addPosLevelAttr();
	addShenYaoPosAttr();
	//addSuitAttr();
}

float CExtEquip::GetUpStarAttrRate( int8_t Star )
{
	float QualityRate = 0.00f;
	switch( Star )
	{
	case 1:
		{
			QualityRate =  0.075f ;
			break;
		}
	case 2:
		{
			QualityRate =  0.15f;
			break;
		}
	case 3:
		{
			QualityRate = 0.225f;
			break;
		}
	case 4:
		{
			QualityRate = 0.30f;
			break;
		}
	case 5:
		{
			QualityRate = 0.375f;
			break;
		}
	case 6:
		{
			QualityRate = 0.45f;
			break;
		}
	case 7:
		{
			QualityRate = 0.525f;
			break;
		}
	case 8:
		{
			QualityRate = 0.60f;
			break;
		}
	case 9:
		{
			QualityRate = 0.75f;
			break;
		}
	case 10:
		{
			QualityRate = 0.90f;
			break;
		}
	case 11:
		{
			QualityRate = 1.125f;
			break;
		}
	case 12:
		{
			QualityRate = 1.50f;
			break;
		}
	default: return 0.0f;
	}
	return QualityRate;
}

void CExtEquip::addEquipAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 || curEquip.itemClass != IC_EQUIP )
		{
			continue;
		}

		MemEquip equip = EQUIP_MANAGER.GetMemEquip( curEquip.srcId );
		if ( equip.base != curEquip.itemId )
		{
			continue;
		}

		const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( equip.base );
		if ( NULL == pCfgEquip )
		{
			continue;
		}

		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
		for ( int32_t j = 0; j < MAX_EQUIP_BASE_ATTR_COUNT; ++j )
		{
			if ( pCfgEquip->m_vAttr[j].addon > 0 )
			{
				m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( pCfgEquip->m_vAttr[j].index ), pCfgEquip->m_vAttr[j].addon );

				if ( equip.star > 0 )
				{
					float Rate = GetUpStarAttrRate( equip.star );
					m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( pCfgEquip->m_StarAttr[j].index ), static_cast<int32_t>(pCfgEquip->m_StarAttr[j].addon * Rate) );
				}
			}
		}

		// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
		if ( equip.addAttr > 0 )
		{
			int32_t nAddCount = EQUIP_MANAGER.GetAddAttrCount( pCfgEquip->m_nQuality );
			if ( nAddCount > 0 )
			{
				const CfgEquipAddAttr* pCfgEquipAddAttr = CFG_DATA.GetEquipTable().GetEquipAddAttr( pCfgEquip->m_nLevel );
				if ( pCfgEquipAddAttr != NULL )
				{
					int32_t	nAttrValue = pCfgEquipAddAttr->GetAttrValue( equip.addAttr ) * nAddCount;
					if ( nAttrValue > 0 )
					{
						m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( equip.addAttr ), nAttrValue );
					}
				}
			}
		}
	}
}

void CExtEquip::addGemAttr()
{
 	if ( NULL == m_pPlayer )
 	{
 		return;
 	}

	int32_t Dammage = GetGemAddEffectTypeRate( GEM_TYPE_DAMMAGE );
	int32_t Attack  = GetGemAddEffectTypeRate( GEM_TYPE_ATTACK );
	m_pPlayer->AddAttrValue(CObjAttrs::ATTR_DMG_ADD_PEC,Attack );
	m_pPlayer->AddAttrValue(CObjAttrs::ATTR_DMG_RDC_PEC,Dammage );
}

void CExtEquip::addSuitAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	// ÃÂÃÂÃÂÃÂ¿ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ°
	const CfgEquipGoal* pGoalStar = CFG_DATA.GetEquipTable().GetEquipGoal( EQUIP_GOAL_STAR, m_nEquipGoalStarLevel );
	if ( pGoalStar != NULL )
	{
		for ( int32_t i = 0; i < MAX_EQUIP_ADD_ATTR_COUNT; ++i )
		{
			if ( pGoalStar->m_vAddAttr[i].addon > 0 )
			{
				m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( pGoalStar->m_vAddAttr[i].index ), pGoalStar->m_vAddAttr[i].addon );
			}
		}
	}
	// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ¯ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ°
	const CfgEquipGoal* pGoalGem = CFG_DATA.GetEquipTable().GetEquipGoal( EQUIP_GOAL_GEM, m_nEquipGoalGemLevel );
	if ( pGoalGem != NULL )
	{
		for ( int32_t i = 0; i < MAX_EQUIP_ADD_ATTR_COUNT; ++i )
		{
			if ( pGoalGem->m_vAddAttr[i].addon > 0 )
			{
				m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( pGoalGem->m_vAddAttr[i].index ), pGoalGem->m_vAddAttr[i].addon );
			}
		}
	}
	// ÃÂÃÂÃÂÃÂ°ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ°
	EquipSuitMap::iterator iter = m_mEquipSuit.begin();
	EquipSuitMap::iterator eiter = m_mEquipSuit.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nSuitId = iter->first;
		int32_t nSuitCount = iter->second;
		const CfgEquipSuit* pSuit = CFG_DATA.GetEquipTable().GetEquipSuit( nSuitId );
		if ( NULL == pSuit )
		{
			continue;
		}

		AttrAddonList addList = pSuit->GetAddAttr( nSuitCount );
		AttrAddonList::iterator addIter = addList.begin();
		for ( ; addIter != addList.end(); ++addIter )
		{
			if ( addIter->addon > 0 )
			{
				m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( addIter->index ), addIter->addon );
			}
		}
	}
}

bool CExtEquip::onEquipExchange( int32_t nBagSlot, int8_t nEquipSlot )
{
	if ( nEquipSlot < 0 || nEquipSlot > EQUIP_SLOT_TOTAL_NUM )
	{
		return false;
	}

	if ( !m_pPlayer->m_extCharBag.IsSlotValid( nBagSlot ) )
	{
		return false;
	}

	MemChrBag bagItem = m_pPlayer->getBagSlotData( nBagSlot );
	if ( bagItem.itemId > 0 )
	{
		if ( !checkDressEquip( nBagSlot, nEquipSlot ) )
		{
			return false;
		}
		//bagItem.bind = IBS_BIND;
	}

	m_pPlayer->GetBag().SetSlotData( nBagSlot, m_vMemEquip[nEquipSlot] );
	m_vMemEquip[nEquipSlot] = bagItem;

	if ( nEquipSlot == EQUIP_SLOT_WEAPON || nEquipSlot == EQUIP_SLOT_CLOTH )
	{
		m_pPlayer->setSyncStatusFlag();
		m_pPlayer->setSyncToTeamFlag();
		if ( nEquipSlot == EQUIP_SLOT_WEAPON )
		{
			m_pPlayer->sendUpdateSocialPlayerInfo( PII_WEAPON, bagItem.itemId );
		}
		else if ( nEquipSlot == EQUIP_SLOT_CLOTH )
		{
			m_pPlayer->sendUpdateSocialPlayerInfo( PII_CLOTH, bagItem.itemId );
		}
	}

	addDirty( nEquipSlot );
	checkEquipGoalStarLevel();
	checkEquipSuit();
	m_pPlayer->recalcAttr();
	m_pPlayer->GetTask().updateTaskCount( TC_DRESS_EQUIP );
	m_pPlayer->GetTask().updateTaskCount( TC_EQUIP_STAR_COUNT );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_DRESS_EQUIP );
	return true;
}

bool CExtEquip::checkDressEquip( int32_t nBagSlot, int8_t nEquipSlot ) const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	const MemChrBag& bagItem = m_pPlayer->GetBag().GetSlotData( nBagSlot );
	if ( bagItem.srcId <= 0 || bagItem.itemClass != IC_EQUIP )
	{
		return false;
	}

	const CfgEquip *pCfgEquip = CFG_DATA.getEquip( bagItem.itemId );
	if ( NULL == pCfgEquip )
	{
		return false;
	}

	if ( pCfgEquip->m_nLevel > m_pPlayer->getLevel() )
	{
		return false;
	}

	if ( pCfgEquip->m_nSoulLevel > m_pPlayer->GetSoulLevel() )
	{
		return false;
	}

	if ( pCfgEquip->m_nJob != 0 && pCfgEquip->m_nJob != m_pPlayer->getJob() )
	{
		return false;
	}

	if ( !checkEquipPlace( pCfgEquip->m_nType, nEquipSlot ) )
	{
		return false;
	}
	return true;
}

bool CExtEquip::checkEquipPlace( int8_t nEquipType, int8_t nEquipSlot ) const
{
	switch ( nEquipType )
	{
	case ET_WEAPON:				return nEquipSlot == EQUIP_SLOT_WEAPON;
	case ET_NECK:				return nEquipSlot == EQUIP_SLOT_NECK;
	case ET_HAND:				return nEquipSlot == EQUIP_SLOT_HAND;
	case ET_CLOSE:				return nEquipSlot == EQUIP_SLOT_CLOTH;
	case ET_HEAD:				return nEquipSlot == EQUIP_SLOT_HEAD;
	case ET_SHOES:				return nEquipSlot == EQUIP_SLOT_SHOES;
	case ET_XUNZHANG:			return nEquipSlot == EQUIP_SLOT_XUNZHANG;
	case ET_BELT:				return nEquipSlot == EQUIP_SLOT_BELT;
	case ET_RING:				return nEquipSlot == EQUIP_SLOT_RING;
	default: break;
	}
	return false;
}

void CExtEquip::addDirty( int32_t nSlot )
{
	Int32List::iterator iter = std::find( m_lstDirty.begin(), m_lstDirty.end(), nSlot );
	if ( iter != m_lstDirty.end() )
	{
		return;
	}
	m_lstDirty.push_back( nSlot );
}

void CExtEquip::checkDirty()
{
	if ( sendDirty() )
	{
		clearDirty();
	}
}

bool CExtEquip::sendDirty()
{
	if ( NULL == m_pPlayer || m_lstDirty.empty() )
	{
		return false;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_BAG_DIRTY );
	if (NULL == packet)
	{
		return false;
	}
	packet->writeInt8( CBT_EQUIP );

	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	Int32List::iterator iter = m_lstDirty.begin();
	Int32List::iterator eiter = m_lstDirty.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nSlot = *iter;
		const MemChrBag& tSlot = GetEquipSlot( nSlot );
		packet->writeInt32( nSlot );
		packet->writeInt32( tSlot.itemId );
		packet->writeInt8( tSlot.itemClass );
		packet->writeInt32( tSlot.itemCount );
		packet->writeInt8( tSlot.bind );
		packet->writeInt32( tSlot.endTime );
		packet->writeInt64( tSlot.srcId );
		++nCount;
	}

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt32( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);

	return true;
}

void CExtEquip::clearDirty()
{
	m_lstDirty.clear();
}

int32_t	CExtEquip::OnNewEquipAddGem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t	nBagType		= inPacket->readInt8();
	int32_t	nEquipPos		= inPacket->readInt32();
	int8_t  nEquipHolePos	= inPacket->readInt8();
	int32_t nPos			= inPacket->readInt32();
	if ( nEquipHolePos < 0 || nEquipHolePos >= EQUIP_GEM_COUNT )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag ItemEquip = {};
	if ( nBagType == CBT_EQUIP )
	{
		if ( nEquipPos < 0 || nEquipPos >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		ItemEquip = m_vMemEquip[nEquipPos];
	}
	else if ( nBagType == CBT_BAG )
	{
		if ( nPos == nEquipPos )
		{
			return ERR_SYETEM_ERR;
		}
		ItemEquip = m_pPlayer->getBagSlotData( nEquipPos );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	MemChrBag CostItem = {};
	CostItem = m_pPlayer->getBagSlotData( nPos );

	if ( ItemEquip.itemClass != IC_EQUIP || ItemEquip.itemId <= 0 || ItemEquip.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( CostItem.itemClass != IC_GEM || CostItem.itemId <= 0 || CostItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip equip = EQUIP_MANAGER.GetMemEquip( ItemEquip.srcId );
	if ( equip.base != ItemEquip.itemId )
	{
		return ERR_SYETEM_ERR;
	}
	if ( equip.GemHole[nEquipHolePos] < 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( equip.GemHole[nEquipHolePos] > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( CostItem.itemId );
	if ( NULL == pGem )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip(ItemEquip.itemId);
	if ( NULL == pEquip )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanAddGem( static_cast<NEW_GEM_TYPE>(pGem->m_nType), pEquip->m_nType ) )
	{
		return ERR_SYETEM_ERR;
	}
	CostItem.itemCount -= 1;
	m_pPlayer->GetBag().SetSlotData( nPos , CostItem, IDCR_GEM_TO_EQUIP ); 
	equip.GemHole[nEquipHolePos] = CostItem.itemId;
	++equip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( equip );
	if ( nBagType == CBT_EQUIP )
	{
		if ( CostItem.bind == IBS_BIND )
		{
			m_vMemEquip[nEquipPos].bind = IBS_BIND;
		}
		m_pPlayer->recalcAttr();
		m_pPlayer->GetCharPet().RecalPetsAttr();
	}
	else
	{
		if ( CostItem.bind == IBS_BIND )
		{
			ItemEquip.bind = IBS_BIND;
		}
		m_pPlayer->GetBag().SetSlotData( nEquipPos, ItemEquip );
	}
	if ( pGem->m_nGemLevel >= XIANG_QIAN_GONG_GAO_GEM_LEVEL )
	{
		EquipAddGemGongGao( equip.base ,pGem->m_nId, equip.id );
	}
//	m_pPlayer->GetBag().ForceSendDirty();
	m_pPlayer->sendEquipInfo( equip );	
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), CostItem.itemId );
	return ERR_OK;
}

int32_t	CExtEquip::OnNewEquipRemoveGem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t	nBagType		= inPacket->readInt8();
	int32_t	nEquipPos		= inPacket->readInt32();
	int8_t	nHoleIndex		= inPacket->readInt8();
	if ( nHoleIndex < 0 || nHoleIndex >= EQUIP_GEM_COUNT )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag ItemEquip = {};
	if ( nBagType == CBT_EQUIP )
	{
		if ( nEquipPos < 0 || nEquipPos >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		ItemEquip = m_vMemEquip[nEquipPos];
	}
	else if ( nBagType == CBT_BAG )
	{
		ItemEquip = m_pPlayer->getBagSlotData( nEquipPos );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( ItemEquip.itemClass != IC_EQUIP || ItemEquip.itemId <= 0 || ItemEquip.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	MemEquip equip = EQUIP_MANAGER.GetMemEquip( ItemEquip.srcId );
	if ( equip.base != ItemEquip.itemId )
	{
		return ERR_SYETEM_ERR;
	}
	if ( equip.GemHole[nHoleIndex] <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	else
	{
		MemChrBag GemItem = {};
		GemItem.itemClass	= IC_GEM;
		GemItem.itemId		= equip.GemHole[nHoleIndex];
		GemItem.itemCount	= 1;
		GemItem.bind		= 1;
		if ( !m_pPlayer->GetBag().AddItem( GemItem,IACR_GEM_TO_BAG ) )
		{
			return ERR_SYETEM_ERR;
		}
		equip.GemHole[nHoleIndex] = 0;
	}
	++equip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( equip );
	MemEquipVector vEquip;
	vEquip.reserve( 1 );
	vEquip.push_back( equip );
	m_pPlayer->sendEquipInfo( vEquip );	
	if ( nBagType == CBT_EQUIP )
	{
		m_pPlayer->recalcAttr();
		m_pPlayer->GetCharPet().RecalPetsAttr();
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t	CExtEquip::OnNewEquipOpenHole( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t		nOpenIndex = inPacket->readInt8();
	int8_t		nBagType   = inPacket->readInt8();
	int32_t		nPos	   = inPacket->readInt32();
	if ( nOpenIndex < 0 || nOpenIndex >= EQUIP_GEM_COUNT )
	{
		return ERR_SYETEM_ERR;
	}
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket,vSlot );
	
	MemChrBag BagItem = {};
	if ( nBagType == CBT_EQUIP )
	{
		if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM )
		{
			return ERR_SYETEM_ERR;
		}
		BagItem = m_vMemEquip[nPos];
	}
	else if ( nBagType == CBT_BAG )
	{
		BagItem = m_pPlayer->getBagSlotData( nPos );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}

	if ( BagItem.itemClass != IC_EQUIP || BagItem.itemId <= 0 || BagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	MemEquip equip = EQUIP_MANAGER.GetMemEquip( BagItem.srcId );
	if ( equip.base != BagItem.itemId )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t BindCount		= 0;
	int32_t UnBindCount		= 0;
	if ( equip.GemHole[nOpenIndex] >= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	else
	{
		ItemData CostItem = {};
		CostItem.m_nClass = IC_NORMAL;
		CostItem.m_nCount = 1;
		switch( nOpenIndex )
		{
		case 0:
			{
				CostItem.m_nId	  = ISI_OPEN_FIRST_GEM_HOLE;
				break;
			}
		case 1:
			{
				CostItem.m_nId	  = ISI_OPEN_SECOND_GEM_HOLE;
				break;
			}
		case 2:
			{
				CostItem.m_nId	  = ISI_OPEN_THIRD_GEM_HOLE;
				break;
			}
		default: return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->GetBag().RemoveItem( CostItem, IDCR_EQUIP_OPEN_GEM_HOLE, BindCount, UnBindCount ) )
		{
			return ERR_SYETEM_ERR;
		}
		equip.GemHole[nOpenIndex] = 0;
		++equip.nFlag;
		EQUIP_MANAGER.UpdateMemEquip( equip );
		m_pPlayer->sendEquipInfo( equip );	
	}
	if ( nBagType == CBT_EQUIP )
	{
		if ( BindCount > 0 )
		{
			m_vMemEquip[nPos].bind = IBS_BIND;
		}
		addDirty( nPos );
	}
	else
	{
		if ( BindCount > 0 )
		{
			BagItem.bind = IBS_BIND;
		}
		m_pPlayer->GetBag().SetSlotData( nPos, BagItem );
	}
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	EquipOpenGemHoelGongGao( equip.base, nOpenIndex, equip.id );
	return ERR_OK;
}

bool CExtEquip::CanAddGem( NEW_GEM_TYPE GemType, int8_t EquipType )
{
	switch( GemType )
	{
	case GEM_TYPE_BATTLE:
		{
			if ( EquipType == ET_WEAPON || EquipType == ET_NECK || EquipType == ET_HAND || EquipType == ET_XUNZHANG )
			{
				return true;
			}
			break;
		}
	case GEM_TYPE_DAMMAGE:
		{
			if ( EquipType == ET_HEAD || EquipType == ET_CLOSE || EquipType == ET_XUNZHANG )
			{
				return true;
			}
			break;
		}
	case GEM_TYPE_EXP:
		{
			if ( EquipType == ET_NECK || EquipType == ET_HAND || EquipType == ET_BELT || EquipType == ET_XUNZHANG )
			{
				return true;
			}
			break;
		}
	case GEM_TYPE_ATTACK:
		{
			if ( EquipType == ET_RING || EquipType == ET_SHOES || EquipType == ET_XUNZHANG )
			{
				return true;
			}
			break;
		}
	default: break;
	}
	return false;
}

int32_t CExtEquip::GetGemAddEffectTypeRate( NEW_GEM_TYPE GemType )
{
	int32_t RateValue = 0;
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 || curEquip.itemClass != IC_EQUIP )
		{
			continue;
		}

		MemEquip equip = EQUIP_MANAGER.GetMemEquip( curEquip.srcId );
		if ( equip.base != curEquip.itemId )
		{
			continue;
		}
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++ )
		{
			const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( equip.GemHole[i] );
			if ( NULL != pGem )
			{
				if ( pGem->m_nType == GemType )
				{
					RateValue += pGem->m_AddRate;
				}
			}
		}
	}
	return RateValue;
}

void CExtEquip::EquipUpQualityOpenGemHole( MemEquip& Equip, int8_t HoleIndex )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( UP_QUALITY_OPEN_HOLE ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt64( Equip.id );
	packet->writeInt32( Equip.base );
	packet->writeInt8( HoleIndex );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::CombiGongGao( int32_t ItemId , int8_t ItemClass )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( ITEM_COMBI ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt32( ItemId );
	packet->writeInt8( ItemClass );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::EquipUpStarGongGao( MemEquip& Equip )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( UP_EQUIP_STAR ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt64( Equip.id );
	packet->writeInt32( Equip.base );
	packet->writeInt8( Equip.star );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::EquipUpQualityGongGao( int32_t NewBaseId, int32_t OldBaseId, EquipId_t EquipId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( UP_EQUIP_QUALITY ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt64( EquipId );
	packet->writeInt32( NewBaseId );
	packet->writeInt32( OldBaseId );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::EquipUpGradeGongGao( int32_t NewBaseId, int32_t OldBaseId , EquipId_t EquipId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( UP_EQUIP_GRADE ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt64( EquipId );
	packet->writeInt32( NewBaseId );
	packet->writeInt32( OldBaseId );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::EquipAddGemGongGao( int32_t EquipBaseId ,int32_t GemId, EquipId_t EquipId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( XIANG_QIAN_GEM ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt64( EquipId );
	packet->writeInt32( EquipBaseId );
	packet->writeInt32( GemId );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::EquipOpenGemHoelGongGao( int32_t EquipBaseId, int8_t HoleIndex, EquipId_t EquipId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( OPEN_GEM_HOLE ) );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt64( EquipId );
	packet->writeInt32( EquipBaseId );
	packet->writeInt8( HoleIndex );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CExtEquip::GetDropEquip( Player *pKiller, int32_t DropCount, int32_t DropRate, MemChrBagVector &DropItemVt, int32_t Mid  )
{
// 	if ( NULL == pKiller ) // ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂªÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½
// 	{
// 		return;
// 	}
	std::vector<int32_t> SlotVt;
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( i == EQUIP_SLOT_XUNZHANG )
		{
			continue;
		}
		MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 || curEquip.itemClass != IC_EQUIP )
		{
			continue;
		}
		SlotVt.push_back( i );
	}
	if ( SlotVt.size() <= 0 )
	{
		return;
	}
	if ( static_cast<int32_t>(SlotVt.size()) > DropCount )
	{
		for ( int32_t i = 0; i < DropCount; ++i )
		{
			int32_t nRand = RANDOM.generate(0,100);
			if ( nRand < DropRate )
			{
				std::random_shuffle(SlotVt.begin(),SlotVt.end());
				std::vector<int32_t>::iterator it = SlotVt.begin();

				MemEquip equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[*it].srcId );
				if ( equip.base !=  m_vMemEquip[*it].itemId )
				{
					continue;
				}
//				if ( m_vMemEquip[*it].bind == IBS_BIND )
//				{
					DropEquipInfo EquipInfo;
					EquipInfo.CharId			= m_pPlayer->getCid();	
					EquipInfo.CharName			= m_pPlayer->getName();	
					if ( pKiller == NULL )
					{
						EquipInfo.KillerId			= 0;	
						EquipInfo.KillerName		= "";
						EquipInfo.Mid				= Mid;
					}
					else
					{
						EquipInfo.KillerId			= pKiller->getCid();	
						EquipInfo.KillerName		= pKiller->getName();	
					}
					
					EquipInfo.CanGetLastTime	= m_pPlayer->getNow() + EQUIP_RANSOM_TIME;
					EquipInfo.itemId			= m_vMemEquip[*it].itemId;	
					EquipInfo.itemClass			= m_vMemEquip[*it].itemClass;
					EquipInfo.itemCount			= m_vMemEquip[*it].itemCount;
					EquipInfo.bind				= m_vMemEquip[*it].bind;
					EquipInfo.endTime			= m_vMemEquip[*it].endTime;
					EquipInfo.srcId				= m_vMemEquip[*it].srcId;
					EQUIP_RANSOM.AddRansom(EquipInfo);
//				}
// 				else
// 				{
// 					equip.owner	= 0;
// 					++equip.nFlag;
// 					EQUIP_MANAGER.UpdateMemEquip(equip);
// 					DropItemVt.push_back(m_vMemEquip[*it]);
// 				}
				
				MemChrBag ItemTmp = {};
				m_vMemEquip[*it] = ItemTmp;
				addDirty(*it);
				SlotVt.erase( it );
			}
		}
	}
	else
	{
		std::vector<int32_t>::iterator it = SlotVt.begin();
		for ( ; it != SlotVt.end(); ++it )
		{
			int32_t nRand = RANDOM.generate(0,100);
			if ( nRand < DropRate )
			{
				MemEquip equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[*it].srcId );
				if ( equip.base !=  m_vMemEquip[*it].itemId )
				{
					continue;
				}
			//	if ( m_vMemEquip[*it].bind == IBS_BIND )
			//	{
					DropEquipInfo EquipInfo;
					EquipInfo.CharId			= m_pPlayer->getCid();	
					EquipInfo.CharName			= m_pPlayer->getName();	
					if ( pKiller == NULL )
					{
						EquipInfo.KillerId			= 0;	
						EquipInfo.KillerName		= "";
						EquipInfo.Mid				= Mid;
					}
					else
					{
						EquipInfo.KillerId			= pKiller->getCid();	
						EquipInfo.KillerName		= pKiller->getName();	
					}
					EquipInfo.CanGetLastTime	= m_pPlayer->getNow() + EQUIP_RANSOM_TIME;
					EquipInfo.itemId			= m_vMemEquip[*it].itemId;	
					EquipInfo.itemClass			= m_vMemEquip[*it].itemClass;
					EquipInfo.itemCount			= m_vMemEquip[*it].itemCount;
					EquipInfo.bind				= m_vMemEquip[*it].bind;
					EquipInfo.endTime			= m_vMemEquip[*it].endTime;
					EquipInfo.srcId				= m_vMemEquip[*it].srcId;
					EQUIP_RANSOM.AddRansom(EquipInfo);
// 				}
// 				else
// 				{
// 					DropItemVt.push_back(m_vMemEquip[*it]);
// 					equip.owner	= 0;
// 					++equip.nFlag;
// 					EQUIP_MANAGER.UpdateMemEquip(equip);
// 				}
				MemChrBag ItemTmp = {};
				m_vMemEquip[*it] = ItemTmp;
				addDirty(*it);
			}
		}
	}
}

int32_t CExtEquip::GetSuitEquipCount()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	int32_t Level		= m_pPlayer->getLevel();
	int32_t SoulLevel   = m_pPlayer->GetSoulLevel();
	int32_t SuitLevel		= 0;
	int32_t SuitSoulLevel	= 0;

	if ( Level  <= MAX_SUIT_EQUIP )
	{
		for ( int32_t i = 30; i <= 300; i = i + 30 )
		{
			if ( Level < i )
			{
				SuitLevel = i - 30;
				if ( SuitLevel <= 0 )
				{
					SuitLevel = 1;
				}
				break;
			}
		}
	}
	else
	{
		for ( int32_t j = 30; j <= 300; j = j + 30 )
		{
			if ( SoulLevel < j )
			{
				SuitSoulLevel = j - 30;
				break;
			}
		}
	}

	if (  Level > MAX_SUIT_EQUIP )
	{
		if ( SuitSoulLevel == 0 )
		{
			SuitLevel = MAX_SUIT_EQUIP;
		}
	}

	int32_t SuitEquipCount = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const CfgEquip *pCfgEquip = CFG_DATA.getEquip( m_vMemEquip[i].itemId );
		if ( NULL == pCfgEquip )
		{
			continue;;
		}
		if ( SuitLevel > 0 )
		{
			if ( pCfgEquip->m_nLevel == SuitLevel )
			{
				SuitEquipCount++;
			}
		}
		else
		{
			if ( pCfgEquip->m_nSoulLevel == SuitSoulLevel )
			{
				SuitEquipCount++;
			}
		}
	}
	return SuitEquipCount;
}
int32_t CExtEquip::GetLowestStar()
{
	int32_t LowesetStar = EQUIP_MAX_STAT;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		MemEquip Equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
		if ( Equip.base !=  m_vMemEquip[i].itemId )
		{
			return 0;
		}
		if ( Equip.star < LowesetStar )
		{
			LowesetStar = Equip.star;
		}
	}
	return LowesetStar;
}

int32_t CExtEquip::GetEquipAllCount()
{
	int32_t Count = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].itemId > 0 && m_vMemEquip[i].srcId > 0)
		{
			MemEquip Equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
			if ( Equip.base !=  m_vMemEquip[i].itemId )
			{
				continue;
			}
			Count++;
		}
	}
	return Count;
}

int32_t CExtEquip::GetEquipBaseBattle()
{
	int32_t AddBattle = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].itemId <=0 )
		{
			continue;
		}
		const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[i].itemId );
		if ( NULL == pCfgEquip )
		{
			continue;
		}
		AddBattle += pCfgEquip->m_Battle;
	}
	return AddBattle;
}

int32_t CExtEquip::GetEquipAllStar( int32_t& Battle )
{
	int32_t AllStar = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].itemId <= 0 || m_vMemEquip[i].srcId <= 0)
		{
			continue;
		}
		MemEquip Equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
		if ( Equip.base !=  m_vMemEquip[i].itemId )
		{
			continue;
		}
		AllStar += Equip.star;
		switch ( Equip.star )
		{
		case 1:
			Battle += 2;
			break;
		case 2:
			Battle += 4;
			break;
		case 3:
			Battle += 6;
			break;
		case 4:
			Battle += 8;
			break;
		case 5:
			Battle += 11;
			break;
		case 6:
			Battle += 14;
			break;
		case 7:
			Battle += 17;
			break;
		case 8:
			Battle += 22;
			break;
		case 9:
			Battle += 27;
			break;
		case 10:
			Battle += 35;
			break;
		case 11:
			Battle += 50;
			break;
		case 12:
			Battle += 80;
			break;
		default:
			break;
		}
	}
	return AllStar;
}

void CExtEquip::GetEquipInfo( int32_t& HoleCount, int32_t& BattleGemCount, int32_t& GemCount, int32_t& EquipQualityBattle, int32_t& GemLevelBattle  )
{
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[i].itemId );
		if ( NULL == pCfgEquip )
		{
			continue;
		}
		switch ( pCfgEquip->m_nQuality )
		{	
		case IQ_GREEN:	// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·
			{
				EquipQualityBattle += 1;
				break;
			}
		case IQ_BLUE:	// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·
			{
				EquipQualityBattle += 2;
				break;
			}
		case IQ_PURPLE:	// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·
			{
				EquipQualityBattle += 3;
				break;
			}
		case IQ_GOLD:	// ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·
			{
				EquipQualityBattle += 4;
				break;
			}
		default:
			break;
		}
		MemEquip Equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
		if ( Equip.base !=  m_vMemEquip[i].itemId )
		{
			continue;
		}
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++ )
		{
			if ( Equip.GemHole[i] >= 0 )
			{
				HoleCount++;
			}
			const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( Equip.GemHole[i] );
			if ( NULL != pGem )
			{
				GemCount++;
				if ( pGem->m_nType == GEM_TYPE_BATTLE )
				{
					BattleGemCount++;
				}
				switch( pGem->m_nGemLevel )
				{
				case 1:
					GemLevelBattle += 1;
					break;
				case 2:
					GemLevelBattle += 2;
					break;
				case 3:
					GemLevelBattle += 3;
					break;
				case 4:
					GemLevelBattle += 4;
					break;
				case 5:
					GemLevelBattle += 5;
					break;
				case 6:
					GemLevelBattle += 6;
					break;
				case 7:
					GemLevelBattle += 7;
					break;
				case 8:
					GemLevelBattle += 8;
					break;
				case 9:
					GemLevelBattle += 9;
					break;
				case 10:
					GemLevelBattle += 11;
					break;
				}
			}
		}
	}
}

int32_t CExtEquip::HaveLevelEquipCount( int32_t Level )
{
	int32_t Count = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[i].itemId );
		if ( NULL == pCfgEquip )
		{
			continue;
		}
		if ( pCfgEquip->m_nLevel >= Level )
		{
			Count++;
		}
	}
	return Count;
}

int32_t CExtEquip::HaveStarEquipCount( int32_t Star )
{
	int32_t Count = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		MemEquip Equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[i].srcId );
		if ( Equip.base !=  m_vMemEquip[i].itemId )
		{
			return 0;
		}
		if ( Equip.star >= Star )
		{
			Count++;
		}
	}
	return Count;
}

// ========== ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ°ÃÂÃÂ¦ÃÂÃÂ±ÃÂÃÂ¾ CExtEquip ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂÃÂÃÂ·ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ ==========

void CExtEquip::loadGemString( const std::string& strGem )
{
	if ( strGem.empty() )
	{
		return;
	}
	StringVector vStr = StringUtility::split( strGem, "|" );
	for ( size_t i = 0; i + 3 < vStr.size(); i += 4 )
	{
		int8_t nPos = (int8_t)atoi( vStr[i].c_str() );
		int8_t nSlot = (int8_t)atoi( vStr[i+1].c_str() );
		int32_t nGemId = atoi( vStr[i+2].c_str() );
		if ( nPos >= 0 && nPos < EQUIP_SLOT_TOTAL_NUM && nSlot >= 0 && nSlot < GEM_SLOT_NUM )
		{
			m_vMemGem[nPos][nSlot] = nGemId;
		}
	}
}

void CExtEquip::loadPosLevelString( const std::string& strPos )
{
	if ( strPos.empty() )
	{
		return;
	}
	StringVector vStr = StringUtility::split( strPos, "|" );
	for ( size_t i = 0; i + 2 < vStr.size(); i += 3 )
	{
		int8_t nPos = (int8_t)atoi( vStr[i].c_str() );
		int32_t nLevel = atoi( vStr[i+1].c_str() );
		if ( nPos >= 0 && nPos < EQUIP_SLOT_TOTAL_NUM )
		{
			m_vMemPosLevel[nPos] = nLevel;
		}
	}
}

void CExtEquip::LoadStrengthenString( const std::string& strStrengthen )
{
	if ( strStrengthen.empty() )
	{
		return;
	}
	StringVector vStr = StringUtility::split( strStrengthen, "|" );
	for ( size_t i = 0; i + 2 < vStr.size(); i += 3 )
	{
		int8_t nPos = (int8_t)atoi( vStr[i].c_str() );
		int32_t nLevel = atoi( vStr[i+1].c_str() );
		if ( nPos >= 0 && nPos < EQUIP_SLOT_TOTAL_NUM )
		{
			m_vMemStrengthen[nPos] = nLevel;
		}
	}
}

void CExtEquip::LoadShenYaoString( const std::string& strShenYao )
{
	if ( strShenYao.empty() )
	{
		return;
	}
	StringVector vStr = StringUtility::split( strShenYao, "|" );
	for ( size_t i = 0; i + 2 < vStr.size(); i += 3 )
	{
		int8_t nIdx = (int8_t)atoi( vStr[i].c_str() );
		int32_t nLevel = atoi( vStr[i+1].c_str() );
		if ( nIdx >= 0 && nIdx < 3 )
		{
			m_vShenYaoEquipPos[nIdx] = nLevel;
		}
	}
}

std::string CExtEquip::saveGemString() const
{
	std::stringstream ss;
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		for ( int8_t j = 0; j < GEM_SLOT_NUM; ++j )
		{
			if ( m_vMemGem[i][j] > 0 )
			{
				ss << "|" << (int32_t)i << "|" << (int32_t)j << "|" << m_vMemGem[i][j] << "|" << 0;
			}
		}
	}
	return ss.str();
}

std::string CExtEquip::savePosLevelString() const
{
	std::stringstream ss;
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemPosLevel[i] > 0 )
		{
			ss << "|" << (int32_t)i << "|" << m_vMemPosLevel[i] << "|" << 0;
		}
	}
	return ss.str();
}

std::string CExtEquip::saveStrengthenString() const
{
	std::stringstream ss;
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemStrengthen[i] > 0 )
		{
			ss << "|" << (int32_t)i << "|" << m_vMemStrengthen[i] << "|" << 0;
		}
	}
	return ss.str();
}

std::string CExtEquip::saveShenYaoString() const
{
	std::stringstream ss;
	for ( int8_t i = 0; i < 3; ++i )
	{
		if ( m_vShenYaoEquipPos[i] > 0 )
		{
			ss << "|" << (int32_t)i << "|" << m_vShenYaoEquipPos[i] << "|" << 0;
		}
	}
	return ss.str();
}

int32_t CExtEquip::GetEquipAllGemLevel() const
{
	int32_t nTotal = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		for ( int32_t j = 0; j < GEM_SLOT_NUM; ++j )
		{
			if ( m_vMemGem[i][j] > 0 )
			{
				const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( m_vMemGem[i][j] );
				if ( pGem != NULL )
				{
					nTotal += pGem->m_nGemLevel;
				}
			}
		}
	}
	return nTotal;
}

int32_t CExtEquip::GetEquipAllUpPosLevel() const
{
	int32_t nTotal = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		nTotal += m_vMemPosLevel[i];
	}
	return nTotal;
}

int32_t CExtEquip::GetEquipSlotPlace( int8_t nSlot ) const
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return -1;
	}
	return m_vMemEquip[nSlot].srcId > 0 ? nSlot : -1;
}

int32_t CExtEquip::GetEquipStar( int8_t nSlot ) const
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return 0;
	}
	const MemChrBag& curEquip = m_vMemEquip[nSlot];
	if ( curEquip.srcId <= 0 )
	{
		return 0;
	}
	MemEquip equip = EQUIP_MANAGER.GetMemEquip( curEquip.srcId );
	if ( equip.base != curEquip.itemId )
	{
		return 0;
	}
	return equip.star;
}

int32_t CExtEquip::GetEquipSuitId( int8_t nSlot ) const
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return 0;
	}
	const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[nSlot].itemId );
	if ( pEquip == NULL )
	{
		return 0;
	}
	return pEquip->m_nSuitId;
}

int32_t CExtEquip::GetEquipType( int8_t nSlot ) const
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return -1;
	}
	const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[nSlot].itemId );
	if ( pEquip == NULL )
	{
		return -1;
	}
	return pEquip->m_nType;
}

int32_t CExtEquip::GetGemOpenLevel() const
{
	int32_t nMinStar = 99999;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 )
		{
			return 0;
		}
		MemEquip equip = EQUIP_MANAGER.GetMemEquip( curEquip.srcId );
		if ( equip.base != curEquip.itemId || equip.star < nMinStar )
		{
			nMinStar = equip.star;
		}
	}
	return nMinStar;
}

int32_t CExtEquip::GetGongMingSuitId() const
{
	return 0;
}

int32_t CExtEquip::CheckGongMingSuitBuff() const
{
	return 0;
}

int32_t CExtEquip::GetMaxPolishLevel() const
{
	return 0;
}

int32_t CExtEquip::GetMaxRefiningLevel() const
{
	return 0;
}

int32_t CExtEquip::GetMoFuSuitLevel( int32_t nSuitId ) const
{
	const CfgMoFuSuit* pCfg = CFG_DATA.GetMoFuSuit( nSuitId );
	if ( NULL == pCfg )
	{
		return 0;
	}

	return 0;
}

int32_t CExtEquip::GetQualityCount( int8_t nQuality ) const
{
	int32_t nCount = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		const MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId <= 0 )
		{
			continue;
		}
		const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip( curEquip.itemId );
		if ( pEquip != NULL && pEquip->m_nQuality == nQuality )
		{
			nCount++;
		}
	}
	return nCount;
}

int32_t CExtEquip::getStrenGthenLevel( int8_t nSlot ) const
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return 0;
	}
	return m_vMemStrengthen[nSlot];
}

int32_t CExtEquip::GetTeJieValue( int32_t nSlot ) const
{
	return 0;
}

int32_t CExtEquip::GetWeaponBless() const
{
	return 0;
}

int32_t CExtEquip::GetWingEquipCount3SuitId() const
{
	return 0;
}

int32_t CExtEquip::GetWingEquipCount6SuitId() const
{
	return 0;
}

int32_t CExtEquip::GetCount6SuitId() const
{
	int32_t nCount = 0;
	EquipSuitMap::const_iterator iter = m_mEquipSuit.begin();
	for ( ; iter != m_mEquipSuit.end(); ++iter )
	{
		if ( iter->second >= 6 )
		{
			nCount++;
		}
	}
	return nCount;
}

int32_t CExtEquip::GetCount12SuitId() const
{
	int32_t nCount = 0;
	EquipSuitMap::const_iterator iter = m_mEquipSuit.begin();
	for ( ; iter != m_mEquipSuit.end(); ++iter )
	{
		if ( iter->second >= 12 )
		{
			nCount++;
		}
	}
	return nCount;
}

int32_t CExtEquip::GetAddGemCount() const
{
	int32_t nCount = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		for ( int32_t j = 0; j < GEM_SLOT_NUM; ++j )
		{
			if ( m_vMemGem[i][j] > 0 )
			{
				nCount++;
			}
		}
	}
	return nCount;
}

int32_t CExtEquip::HaveQualityGradeEquipCount( int32_t nQuality, int32_t nGrade ) const
{
	int32_t nCount = 0;
	for ( int32_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemEquip[i].srcId <= 0 )
		{
			continue;
		}
		const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip( m_vMemEquip[i].itemId );
		if ( pEquip != NULL && pEquip->m_nQuality == nQuality && pEquip->m_nGrade >= nGrade )
		{
			nCount++;
		}
	}
	return nCount;
}

int32_t CExtEquip::GetGongMingBuffBattle() const
{
	return 0;
}

bool CExtEquip::IsAllPosLevel() const
{
	return false;
}

bool CExtEquip::IsAllPosTop() const
{
	return false;
}

int32_t CExtEquip::SetWeaponBless( int32_t nVal )
{
	return 0;
}

void CExtEquip::checkGongMingSuit()
{
}

int32_t CExtEquip::CheckSuitId( int32_t nSuitId ) const
{
	EquipSuitMap::const_iterator iter = m_mEquipSuit.find( nSuitId );
	if ( iter != m_mEquipSuit.end() )
	{
		return iter->second;
	}
	return 0;
}

void CExtEquip::clearGemInfo()
{
	bzero( m_vMemGem, sizeof( m_vMemGem ) );
}

void CExtEquip::broadcastItemCombi( int32_t nItemId, int8_t nItemClass )
{
	CombiGongGao( nItemId, nItemClass );
}

void CExtEquip::broadcastGemLevelUp( int8_t nEquipSlot, int8_t nHolePos, int32_t nGemId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_EQUIP_UP_STAR );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt8( XIANG_QIAN_GEM );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_vMemEquip[nEquipSlot].srcId );
	packet->writeInt32( m_vMemEquip[nEquipSlot].itemId );
	packet->writeInt32( nGemId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
}

std::vector<int32_t> CExtEquip::getCanDropEquipSlots() const
{
	std::vector<int32_t> vSlots;
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( i == EQUIP_SLOT_XUNZHANG )
		{
			continue;
		}
		const MemChrBag& curEquip = m_vMemEquip[i];
		if ( curEquip.srcId > 0 && curEquip.itemClass == IC_EQUIP )
		{
			vSlots.push_back( i );
		}
	}
	return vSlots;
}

void CExtEquip::SendPosLevelInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_EQUIP_POS_LEVEL_INFO );
	if ( NULL == packet )
	{
		return;
	}
	int32_t nOldOffset = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( nCount );
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemPosLevel[i] > 0 )
		{
			packet->writeInt8( i );
			packet->writeInt32( m_vMemPosLevel[i] );
			nCount++;
		}
	}
	int32_t nNewOffset = packet->getWOffset();
	packet->setWOffset( nOldOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( nNewOffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtEquip::SendShenYaoPosLevelInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SHENYAO_POS_LEVEL_INFO );
	if ( NULL == packet )
	{
		return;
	}
	for ( int8_t i = 0; i < 3; ++i )
	{
		packet->writeInt8( i );
		packet->writeInt32( m_vShenYaoEquipPos[i] );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtEquip::SendStrenGthenInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_EQUIP_STRENGTHEN_INFO );
	if ( NULL == packet )
	{
		return;
	}
	int32_t nOldOffset = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( nCount );
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		if ( m_vMemStrengthen[i] > 0 )
		{
			packet->writeInt8( i );
			packet->writeInt32( m_vMemStrengthen[i] );
			nCount++;
		}
	}
	int32_t nNewOffset = packet->getWOffset();
	packet->setWOffset( nOldOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( nNewOffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtEquip::PackageShenYaoPosLevelUp( Answer::NetPacket* packet ) const
{
	if ( NULL == packet )
	{
		return;
	}
	for ( int8_t i = 0; i < 3; ++i )
	{
		packet->writeInt8( i );
		packet->writeInt32( m_vShenYaoEquipPos[i] );
	}
}

void CExtEquip::updateEquipGem( int8_t nSlot, int32_t nGemId, int8_t nHoleIndex )
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return;
	}
	if ( nHoleIndex < 0 || nHoleIndex >= EQUIP_GEM_COUNT )
	{
		return;
	}
	MemEquip equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[nSlot].srcId );
	if ( equip.base != m_vMemEquip[nSlot].itemId )
	{
		return;
	}
	equip.GemHole[nHoleIndex] = nGemId;
	++equip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( equip );
}

void CExtEquip::updateEquipStar( int8_t nSlot, int32_t nStar )
{
	if ( nSlot < 0 || nSlot >= EQUIP_SLOT_TOTAL_NUM )
	{
		return;
	}
	MemEquip equip = EQUIP_MANAGER.GetMemEquip( m_vMemEquip[nSlot].srcId );
	if ( equip.base != m_vMemEquip[nSlot].itemId )
	{
		return;
	}
	equip.star = nStar;
	++equip.nFlag;
	EQUIP_MANAGER.UpdateMemEquip( equip );
	addDirty( nSlot );
	checkEquipGoalStarLevel();
	m_pPlayer->recalcAttr();
}

void CExtEquip::AddStrengthenAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		int32_t nLevel = m_vMemStrengthen[i];
		if ( nLevel <= 0 )
		{
			continue;
		}
		const CfgEquipStrengthen* pCfg = CFG_DATA.GetEquipStrengthen( i, nLevel );
		if ( NULL == pCfg )
		{
			continue;
		}
		for ( int32_t j = 0; j < MAX_EQUIP_ADD_ATTR_COUNT; ++j )
		{
			if ( pCfg->m_vAddAttr[j].addon > 0 )
			{
				m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_vAddAttr[j].index, pCfg->m_vAddAttr[j].addon );
			}
		}
	}
}

void CExtEquip::addPosLevelAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int8_t i = 0; i < EQUIP_SLOT_TOTAL_NUM; ++i )
	{
		int32_t nLevel = m_vMemPosLevel[i];
		if ( nLevel <= 0 )
		{
			continue;
		}
		const CfgEquipUpPos* pCfg = CFG_DATA.GetEquipUpPos( i, nLevel );
		if ( NULL == pCfg )
		{
			continue;
		}
		for ( int32_t j = 0; j < MAX_EQUIP_ADD_ATTR_COUNT; ++j )
		{
			if ( pCfg->m_vAddAttr[j].addon > 0 )
			{
				m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_vAddAttr[j].index, pCfg->m_vAddAttr[j].addon );
			}
		}
	}
}

void CExtEquip::addShenYaoPosAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int8_t i = 0; i < 3; ++i )
	{
		int32_t nLevel = m_vShenYaoEquipPos[i];
		if ( nLevel <= 0 )
		{
			continue;
		}
		const CfgShenYaoEquip* pCfg = CFG_DATA.GetShenYaoEquipTable().GetShenYaoEquip( i, nLevel );
		if ( NULL == pCfg )
		{
			continue;
		}
		for ( int32_t j = 0; j < MAX_EQUIP_ADD_ATTR_COUNT; ++j )
		{
			if ( pCfg->m_vAddAttr[j].addon > 0 )
			{
				m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_vAddAttr[j].index, pCfg->m_vAddAttr[j].addon );
			}
		}
	}
}

int32_t CExtEquip::onBackEquip( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( m_pPlayer->getMapId() == 50001 )
	{
		return ERR_INVALID_DATA;
	}

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );
	int32_t nCount = 0;
	std::map<int32_t, int32_t> mCurrMap;
	std::vector<int32_t> vRemoveSlot;

	for ( int32_t i = 0; i < MAX_BAG_SLOT_NUM; ++i )
	{
		MemChrBag bagItem = m_pPlayer->GetBag().GetSlotData( i );
		if ( bagItem.itemClass != IC_EQUIP || bagItem.itemId <= 0 )
		{
			continue;
		}
		const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( bagItem.itemId );
		if ( NULL == pCfgEquip )
		{
			continue;
		}
		if ( pCfgEquip->m_BackType >= 0 && pCfgEquip->m_BackValue > 0 )
		{
			mCurrMap[pCfgEquip->m_BackType] += pCfgEquip->m_BackValue * bagItem.itemCount;
			vRemoveSlot.push_back( i );
			nCount++;
		}
	}

	if ( nCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	for ( size_t i = 0; i < vRemoveSlot.size(); ++i )
	{
		m_pPlayer->GetBag().CleanSlot( vRemoveSlot[i], IDCR_DISCARD );
	}

	float fRate = 1.0f;
	for ( std::map<int32_t, int32_t>::iterator it = mCurrMap.begin(); it != mCurrMap.end(); ++it )
	{
		int32_t nValue = (int32_t)(it->second * fRate);
		if ( nValue > 0 )
		{
			m_pPlayer->AddCurrency( (CURRENCY_TYPE)it->first, nValue, GCR_BACK_EQUIP );
		}
	}

	m_pPlayer->GetTask().updateTaskCount( 0 );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nCount );
	return ERR_OK;
}

int32_t CExtEquip::onEquipStrenGthen( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nPos = inPacket->readInt32();
	if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM )
	{
		return ERR_INVALID_DATA;
	}

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	int32_t nCurLevel = m_vMemStrengthen[nPos];
	const CfgEquipStrengthen* pCfg = CFG_DATA.GetEquipStrengthen( nPos, nCurLevel + 1 );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().RemoveItem( pCfg->m_CostItem, IDCR_EQUIP_STRENGTHEN ) )
	{
		return ERR_INVALID_DATA;
	}

	m_vMemStrengthen[nPos]++;
	m_pPlayer->recalcAttr();

	if ( pCfg->m_nGongGaoId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( NULL != packet )
		{
			packet->writeInt32( pCfg->m_nGongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( nPos );
			packet->writeInt32( m_vMemStrengthen[nPos] );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
		}
	}

	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nPos );
	return ERR_OK;
}

int32_t CExtEquip::onEquipUpPhase( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t nBagType = inPacket->readInt8();
	int32_t nPos = inPacket->readInt32();


	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onEquipUpPos( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nPos = inPacket->readInt32();
	int8_t nAutoBuy = inPacket->readInt8();
	int8_t nBaoHu = inPacket->readInt8();

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	if ( nPos < 0 || nPos >= EQUIP_SLOT_TOTAL_NUM )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCurLevel = m_vMemPosLevel[nPos];
	const CfgEquipUpPos* pCfg = CFG_DATA.GetEquipUpPos( nPos, nCurLevel + 1 );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getLevel() < pCfg->m_nNeedLevel )
	{
		return ERR_INVALID_DATA;
	}

	int32_t BindCount = 0;
	int32_t UnBindCount = 0;

	if ( nAutoBuy > 0 )
	{
		int32_t nBuyCount = 0;
		ItemData costItem = pCfg->m_CostItem;
		int32_t nItemCount = m_pPlayer->GetBag().GetItemCount( vSlot, costItem.m_nClass, costItem.m_nId );
		if ( nItemCount < costItem.m_nCount )
		{
			nBuyCount = costItem.m_nCount - nItemCount;
			costItem.m_nCount = nItemCount;
		}
		int32_t nCostGold = 0;
		if ( nBuyCount > 0 )
		{
			CfgGameShop* pShop = CFG_DATA.GetGameShopItem( costItem.m_nClass, costItem.m_nId );
			if ( NULL == pShop )
			{
				return ERR_INVALID_DATA;
			}
			nCostGold = nBuyCount * pShop->Price;
			if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nCostGold )
			{
				return ERR_INVALID_DATA;
			}
		}
		if ( costItem.m_nCount > 0 && !m_pPlayer->GetBag().RemoveItem( costItem, IDCR_EQUIP_UP_POS, BindCount, UnBindCount ) )
		{
			return ERR_INVALID_DATA;
		}
		if ( nCostGold > 0 )
		{
			m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_EQUIP_UP_POS_AUTO_BUY );
		}
	}
	else
	{
		if ( !m_pPlayer->GetBag().RemoveItem( pCfg->m_CostItem, IDCR_EQUIP_UP_POS, BindCount, UnBindCount ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	bool bSuccess = false;
	int32_t nRand = RANDOM.generate( 1, pCfg->m_nTotalRate );
	if ( nRand <= pCfg->m_nRate )
	{
		bSuccess = true;
	}

	if ( bSuccess )
	{
		m_vMemPosLevel[nPos]++;
		m_pPlayer->recalcAttr();
		if ( pCfg->m_nGongGaoId > 0 )
		{
			NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
			if ( NULL != packet )
			{
				packet->writeInt32( pCfg->m_nGongGaoId );
				packet->writeUTF8( m_pPlayer->getName() );
				packet->writeInt64( m_pPlayer->getCid() );
				packet->writeInt32( nPos );
				packet->writeInt32( m_vMemPosLevel[nPos] );
				packet->setSize( packet->getWOffset() );
				GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
			}
		}
		m_pPlayer->GetTask().updateTaskCount( 0 /* TC_EQUIP_UP_POS */ );
		m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( 0 /* HYDT_EQUIP_POS_UP */ );
		GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	}
	else
	{
		if ( nBaoHu <= 0 && m_vMemPosLevel[nPos] > 0 )
		{
			m_vMemPosLevel[nPos]--;
		}
		m_pPlayer->recalcAttr();
		GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_INVALID_DATA );
	}

	return ERR_OK;
}


// ========== å®åçè£å¤ç³»ç»æ¹æ³ ==========

int32_t CExtEquip::onGemLevelUp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	int32_t nGemSlot = inPacket->readInt32();
	int32_t nBagSlot = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS || nGemSlot < 0 || nGemSlot >= MAX_GEM_SLOT )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nCurGemId = m_vMemGem[nEquipPos][nGemSlot];
	if ( nCurGemId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgGemLevelUp* pCfgGemLevelUp = CFG_DATA.GetGemLevelUpTable().GetGemLevelUp( nCurGemId );
	if ( NULL == pCfgGemLevelUp )
	{
		return ERR_SYETEM_ERR;
	}
	// Check and deduct cost items
	if ( pCfgGemLevelUp->nNeedItemId > 0 )
	{
		Int32Vector vSlot;
		m_pPlayer->queryBagInfoByItemId( pCfgGemLevelUp->nNeedItemId, pCfgGemLevelUp->nNeedItemCount, vSlot );
		if ( vSlot.empty() )
		{
			return ERR_SYETEM_ERR;
		}
		ItemData itemData = {};
		itemData.m_nId = pCfgGemLevelUp->nNeedItemId;
		itemData.m_nClass = IC_NORMAL;
		itemData.m_nCount = pCfgGemLevelUp->nNeedItemCount;
		if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, IDCR_EQUIP_GEM_LEVEL_UP ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Check and deduct money cost
	if ( pCfgGemLevelUp->nCostMoney > 0 )
	{
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfgGemLevelUp->nCostMoney, MCR_EQUIP_GEM_LEVEL_UP ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Upgrade gem
	m_vMemGem[nEquipPos][nGemSlot] = pCfgGemLevelUp->nNextGemId;
	updateEquipGem( nEquipPos, m_vMemGem[nEquipPos][nGemSlot], nGemSlot );
	SendGemInfo( nEquipPos, (int8_t)nGemSlot );
	m_pPlayer->recalcAttr();
	// Broadcast if needed
	if ( pCfgGemLevelUp->nBroadId > 0 )
	{
		broadcastGemLevelUp( nEquipPos, nGemSlot, pCfgGemLevelUp->nNextGemId );
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onGemOpenHole( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	int32_t nBagSlot = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS )
	{
		return ERR_SYETEM_ERR;
	}
	// Find first free gem slot
	int32_t nHoleIndex = -1;
	for ( int32_t i = 0; i < MAX_GEM_SLOT; ++i )
	{
		if ( m_vMemGem[nEquipPos][i] <= 0 )
		{
			nHoleIndex = i;
			break;
		}
	}
	if ( nHoleIndex < 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// Use item from bag slot as cost for opening hole
	MemChrBag costItem = m_pPlayer->getBagSlotData( nBagSlot );
	if ( costItem.itemId > 0 && costItem.itemCount > 0 )
	{
		ItemData itemData = {};
		itemData.m_nId = costItem.itemId;
		itemData.m_nClass = costItem.itemClass;
		itemData.m_nCount = 1;
		Int32Vector vSlot( 1, nBagSlot );
		if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, IDCR_EQUIP_OPEN_GEM_HOLE ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Mark hole as open (slot is now available for gem insertion)
	m_vMemGem[nEquipPos][nHoleIndex] = 0;
	SendGemInfo( nEquipPos, (int8_t)nHoleIndex );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onGemRemove( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	int32_t nGemSlot = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS || nGemSlot < 0 || nGemSlot >= MAX_GEM_SLOT )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nGemId = m_vMemGem[nEquipPos][nGemSlot];
	if ( nGemId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// Return gem to bag
	MemChrBag gemBag = {};
	gemBag.itemId = nGemId;
	gemBag.itemClass = IC_GEM;
	gemBag.itemCount = 1;
	gemBag.bind = IBS_BIND;
	if ( !m_pPlayer->GetBag().AddItem( gemBag, (ITEM_ADD_REASON)42 ) /* IACR_FROM_GEM */ )
	{
		return ERR_SYETEM_ERR;
	}
	// Clear gem slot
	m_vMemGem[nEquipPos][nGemSlot] = 0;
	updateEquipGem( nEquipPos, m_vMemGem[nEquipPos][nGemSlot], nGemSlot );
	SendGemInfo( nEquipPos, (int8_t)nGemSlot );
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onMoFuDuiHuan( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nMoFuId = inPacket->readInt32();
	int32_t nEquipPos = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgMoFu* pCfgMoFu = CFG_DATA.GetMoFuTable().GetMoFu( nMoFuId );
	if ( NULL == pCfgMoFu )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfgMoFu->nCostGold, GCR_MOFU_DUIHUAN ) )
	{
		return ERR_SYETEM_ERR;
	}
	// Apply mofu to equipment
	m_vMemMoFu[nEquipPos] = nMoFuId;
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onMoFuHuiShou( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_vMemMoFu[nEquipPos] <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// Return some resources
	const CfgMoFu* pCfgMoFu = CFG_DATA.GetMoFuTable().GetMoFu( m_vMemMoFu[nEquipPos] );
	if ( NULL != pCfgMoFu && pCfgMoFu->nRecycleItemId > 0 )
	{
		MemChrBag recycleBag = {};
		recycleBag.itemId = pCfgMoFu->nRecycleItemId;
		recycleBag.itemClass = IC_NORMAL;
		recycleBag.itemCount = pCfgMoFu->nRecycleItemCount;
		recycleBag.bind = IBS_BIND;
	}
	m_vMemMoFu[nEquipPos] = 0;
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onRelieveBind( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS )
	{
		return ERR_SYETEM_ERR;
	}
	// Gold cost for unbinding: based on equipment grade
	int32_t nCostGold = 50;
	const MemChrBag& equipSlot = GetEquipSlot( (int8_t)nEquipPos );
	if ( equipSlot.itemId > 0 )
	{
		const CfgEquip* pCfg = CFG_DATA.GetEquipTable().GetEquip( equipSlot.itemId );
		if ( pCfg != NULL && pCfg->m_Grade > 0 )
			nCostGold = 50 * pCfg->m_Grade;
	}
	if ( nCostGold > 0 )
	{
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_RELIEVE_BIND ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Unbind equipped item
	m_vMemEquip[nEquipPos].bind = IBS_UNBIND;
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onShenYaoPosLevelUp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nPos = inPacket->readInt32();
	if ( nPos < 0 || nPos >= MAX_SHENYAO_POS )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nCurLevel = m_vShenYaoEquipPos[nPos];
	const CfgShenYaoEquip* pCfg = CFG_DATA.GetShenYaoEquipTable().GetShenYaoEquip( nPos, nCurLevel + 1 );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nCostGold, GCR_SHENYAO_UP ) )
	{
		return ERR_SYETEM_ERR;
	}
	m_vShenYaoEquipPos[nPos]++;
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::OnXinMoEquipHuiShou( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS )
	{
		return ERR_SYETEM_ERR;
	}
	// Clear all enhancements on this equipment position and return resources
	m_vMemStrengthen[nEquipPos] = 0;
	m_vMemPosLevel[nEquipPos] = 0;
	m_vMemMoFu[nEquipPos] = 0;
	for ( int32_t i = 0; i < MAX_GEM_SLOT; ++i )
	{
		m_vMemGem[nEquipPos][i] = 0;
	}
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtEquip::onGemAdd( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipPos = inPacket->readInt32();
	int32_t nBagSlot = inPacket->readInt32();
	if ( nEquipPos < 0 || nEquipPos >= MAX_EQUIP_POS )
	{
		return ERR_SYETEM_ERR;
	}
	// Get gem from bag
	MemChrBag bagItem = m_pPlayer->getBagSlotData( nBagSlot );
	if ( bagItem.itemId <= 0 || bagItem.itemClass != IC_GEM || bagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( bagItem.itemId );
	if ( NULL == pGem )
	{
		return ERR_SYETEM_ERR;
	}
	// Find a free gem slot
	int32_t nGemSlot = -1;
	for ( int32_t i = 0; i < MAX_GEM_SLOT; ++i )
	{
		if ( m_vMemGem[nEquipPos][i] <= 0 )
		{
			nGemSlot = i;
			break;
		}
	}
	if ( nGemSlot < 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// Remove gem from bag
	ItemData costItem = {};
	costItem.m_nId = bagItem.itemId;
	costItem.m_nClass = bagItem.itemClass;
	costItem.m_nCount = 1;
	Int32Vector vSlot( 1, nBagSlot );
	if ( !m_pPlayer->GetBag().RemoveItem( vSlot, costItem, IDCR_GEM_TO_EQUIP ) )
	{
		return ERR_SYETEM_ERR;
	}
	// Insert gem
	m_vMemGem[nEquipPos][nGemSlot] = bagItem.itemId;
	updateEquipGem( nEquipPos, bagItem.itemId, (int8_t)nGemSlot );
	checkEquipGoalGemLevel();
	SendGemInfo( nEquipPos, (int8_t)nGemSlot );
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}
