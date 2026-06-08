#include "stdafx.h"
#include "CharWing.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "CharSkill.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "Unit.h"
#include "Currency.h"
#include "DataStructs.h"

using namespace Answer;

void CExtCharWing::OnCleanUp()
{
	m_Level = 0;
	m_Luck = 0;
	m_LaseUpdateTick = 0;
	m_HuanHua = 0;
}

void CExtCharWing::OnLoadFromDB( const PlayerDBData* dbData )
{
	if ( NULL == dbData )
	{
		return;
	}

	m_Level = dbData->m_CharWingDBData.m_Level;
	m_Luck = dbData->m_CharWingDBData.m_Luck;
	m_HuanHua = dbData->m_CharWingDBData.m_HuanHua;

	if ( !m_HuanHua )
	{
		m_HuanHua = m_Level;
	}

	const WingCfg* pWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( m_Level );
	if ( pWingCfg != NULL && pWingCfg->SkillId > 0 && pWingCfg->SkillLevel > 0 )
	{
		m_pPlayer->GetCharSkill().AddOtherSkill( pWingCfg->SkillId, pWingCfg->SkillLevel );
	}
}

void CExtCharWing::OnSaveToDB( PlayerDBData* dbData )
{
	if ( NULL == dbData )
	{
		return;
	}

	dbData->m_CharWingDBData.m_Level = m_Level;
	dbData->m_CharWingDBData.m_Luck = m_Luck;
	dbData->m_CharWingDBData.m_HuanHua = m_HuanHua;
}

void CExtCharWing::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_WING_INFO );
	procList.push_back( CM_WING_UP_LEVEL );
	procList.push_back( CM_WING_HUAN_HUA );
}

int32_t CExtCharWing::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( !IsFunctionOpen() )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case CM_WING_INFO:		return onRequestInfo( inPacket );
	case CM_WING_UP_LEVEL:	return onWingUpLevel( inPacket );
	case CM_WING_HUAN_HUA:	return onWingHuanHua( inPacket );
	}

	return 0;
}

int32_t CExtCharWing::onRequestInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	SendWingInfo();
	return 0;
}

int32_t CExtCharWing::onWingHuanHua( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t Level = inPacket->readInt32();
	const WingCfg* pWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( Level );
	if ( NULL == pWingCfg )
	{
		return ERR_INVALID_DATA;
	}

	m_HuanHua = Level;
	return 0;
}

int32_t CExtCharWing::onWingUpLevel( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nAutoBuy = inPacket->readInt8();
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	const WingCfg* pWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( m_Level );
	if ( NULL == pWingCfg )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nNextLevel = m_Level + 1;
	const WingCfg* pNextWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( nNextLevel );
	if ( NULL == pNextWingCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( nAutoBuy )
	{
		ItemDataList costItemList = pWingCfg->ConstItems;
		int32_t nCostGold = 0;

		for ( ItemDataList::iterator iter = costItemList.begin(); iter != costItemList.end(); )
		{
			int32_t nItemCount = m_pPlayer->GetBag().GetItemCount( vSlot, iter->m_nClass, iter->m_nId );
			int32_t nBuyCount = 0;
			if ( iter->m_nCount > nItemCount )
			{
				nBuyCount = iter->m_nCount - nItemCount;
				iter->m_nCount = nItemCount;
			}

			if ( nBuyCount > 0 )
			{
				const CfgGameShop* pCfgGameShop = CFG_DATA.GetGameShopItem( iter->m_nClass, iter->m_nId );
				if ( NULL == pCfgGameShop )
				{
					return 2;
				}
				nCostGold += nBuyCount * pCfgGameShop->Price;
			}

			if ( iter->m_nCount > 0 )
			{
				++iter;
			}
			else
			{
				iter = costItemList.erase( iter );
			}
		}

		if ( nCostGold > 0 && m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nCostGold )
		{
			return ERR_INVALID_DATA;
		}

		if ( !costItemList.empty() && !m_pPlayer->GetBag().RemoveItem( vSlot, costItemList, IDCR_BAG_USE ) )
		{
			return ERR_INVALID_DATA;
		}

		if ( nCostGold > 0 && !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_EQUIP_UPSTAR_AUTOBUY, 0 ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	else
	{
		if ( !pWingCfg->ConstItems.empty() && !m_pPlayer->GetBag().RemoveItem( vSlot, pWingCfg->ConstItems, IDCR_BAG_USE ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	bool Success = false;
	if ( m_Luck >= pWingCfg->SuccessPoints )
	{
		Success = true;
	}
	else if ( m_Luck >= pWingCfg->StartPoints )
	{
		int32_t nRand = RANDOM.generate( 1, 10000 );
		if ( pWingCfg->Rate >= nRand )
		{
			Success = true;
		}
	}

	if ( Success )
	{
		if ( m_Level == m_HuanHua )
		{
			++m_HuanHua;
		}
		++m_Level;

		if ( pWingCfg->SkillId > 0 && pWingCfg->SkillLevel > 0 )
		{
			m_pPlayer->GetCharSkill().removeSkillByTalent( pWingCfg->SkillId );
		}

		if ( pNextWingCfg->SkillId > 0 && pNextWingCfg->SkillLevel > 0 )
		{
			m_pPlayer->GetCharSkill().AddOtherSkill( pNextWingCfg->SkillId, pNextWingCfg->SkillLevel );
		}

		m_pPlayer->recalcAttr();


	}
	else
	{
		m_Luck += pWingCfg->FailAddPoints;
		if ( m_Luck > pWingCfg->MaxPoints )
		{
			m_Luck = pWingCfg->MaxPoints;
		}
	}

	SendWingInfo();
	return 0;
}

bool CExtCharWing::LevelUp( int32_t UseWingLevel, int32_t UpLevel, int32_t ItemId, int32_t itemCount )
{
	if ( NULL == m_pPlayer || UseWingLevel <= 0 || UpLevel <= 0 || ItemId <= 0 || itemCount <= 0 )
	{
		return false;
	}

	if ( GetLevel() < UseWingLevel )
	{
		return false;
	}

	if ( GetLevel() == UseWingLevel )
	{
		int32_t nNewLevel = UpLevel + GetLevel();
		const WingCfg* pWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( nNewLevel );
		if ( NULL == pWingCfg )
		{
			return false;
		}

		if ( m_Level == m_HuanHua )
		{
			m_HuanHua += UpLevel;
		}
		m_Level += UpLevel;

		SendWingInfo();
		return true;
	}
	else
	{
		MemChrBag stu;
		memset( &stu, 0, sizeof(stu) );
		stu.itemClass = 1;
		stu.bind = 1;
		stu.itemId = ItemId;
		stu.itemCount = itemCount;
		return m_pPlayer->GetBag().AddItem( stu, IACR_NONE );
	}
}

void CExtCharWing::OnDaySwitch( int32_t nDiffDays )
{
	const WingCfg* pWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( m_Level );
	if ( pWingCfg != NULL && pWingCfg->IsClear > 0 )
	{
		ClearLuck();
	}
}

void CExtCharWing::ClearLuck()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	m_pPlayer->updateRecord( 1909, m_pPlayer->getNow() );
	m_Luck = 0;
	SendWingInfo();
}

void CExtCharWing::SendWingInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_WING_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_Level );
	packet->writeInt32( m_Luck );
	packet->writeInt32( m_HuanHua );
	packet->setSize( packet->getWOffset() );

	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtCharWing::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !IsFunctionOpen() )
	{
		return;
	}

	const WingCfg* pWingCfg = CFG_DATA.GetWingTable()->GetWingCfg( m_Level );
	if ( NULL == pWingCfg )
	{
		return;
	}

	for ( AttrAddonVector::const_iterator iter = pWingCfg->AddonVector.begin(); iter != pWingCfg->AddonVector.end(); ++iter )
	{
		m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)iter->index, iter->addon );
	}
}

bool CExtCharWing::IsFunctionOpen() const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 140 );
}
