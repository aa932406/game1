#include "stdafx.h"
#include "TianLing.h"
#include "CfgData.h"
#include "FunctionOpen.h"
#include "CharSkill.h"
#include "GameService.h"
#include "DBService.h"
#include "Currency.h"
#include "Bag.h"
#include "Task.h"
#include "Timer.h"
#include "OperateLimit.h"

using namespace Answer;

void CTianLing::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 261 );
	procList.push_back( 259 );
	procList.push_back( 263 );
}

int32_t CTianLing::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case 261:
		return OnTianLingLevelUp( inPacket );
	case 263:
		return OnSunAndMoonLevelUp( inPacket );
	case 259:
		return OnZhanHunLevelUp( inPacket );
	}

	return ERR_INVALID_DATA;
}

void CTianLing::InitSystem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	// 天灵：功能175
	if ( m_pPlayer->GetPlayerFunctionOpen().IsOpened( 175 ) && m_pPlayer->getRecord( 1148 ) <= 0 )
	{
		m_pPlayer->updateRecord( 1148, 1 );
	}

	// 战魂：功能235
	if ( m_pPlayer->GetPlayerFunctionOpen().IsOpened( 235 ) && m_pPlayer->getRecord( 37501 ) <= 0 )
	{
		m_pPlayer->updateRecord( 37501, 1 );
	}

	// 日月：功能240
	if ( m_pPlayer->GetPlayerFunctionOpen().IsOpened( 240 ) )
	{
		if ( m_pPlayer->getRecord( 37506 ) <= 0 )
		{
			m_pPlayer->updateRecord( 37506, 1 );
		}

		int32_t CurLevel = m_pPlayer->getRecord( 37506 );
		const SunAndMoonCfg* CurCfg = CFG_DATA.GetSunAndMoonCfg( CurLevel );
		if ( CurCfg != NULL )
		{
			if ( CurCfg->nSunTelentId > 0 && CurCfg->nSunTelentLevel > 0 )
			{
				m_pPlayer->GetCharSkill().AddOtherSkill( CurCfg->nSunTelentId, CurCfg->nSunTelentLevel );
			}
			if ( CurCfg->nMoonTelentId > 0 && CurCfg->nMoonTelentLevel > 0 )
			{
				m_pPlayer->GetCharSkill().AddOtherSkill( CurCfg->nMoonTelentId, CurCfg->nMoonTelentLevel );
			}
		}
	}
}

void CTianLing::InitTianLing()
{
	if ( m_pPlayer != NULL )
	{
		m_pPlayer->updateRecord( 1148, 1 );
	}
}

void CTianLing::InitZhanHun()
{
	if ( m_pPlayer != NULL )
	{
		m_pPlayer->updateRecord( 37501, 1 );
	}
}

void CTianLing::InitSunAndMoon()
{
	if ( m_pPlayer == NULL )
	{
		return;
	}

	m_pPlayer->updateRecord( 37506, 1 );

	const SunAndMoonCfg* CurCfg = CFG_DATA.GetSunAndMoonCfg( 1 );
	if ( CurCfg != NULL )
	{
		if ( CurCfg->nSunTelentId > 0 && CurCfg->nSunTelentLevel > 0 )
		{
			m_pPlayer->GetCharSkill().AddOtherSkill( CurCfg->nSunTelentId, CurCfg->nSunTelentLevel );
		}
		if ( CurCfg->nMoonTelentId > 0 && CurCfg->nMoonTelentLevel > 0 )
		{
			m_pPlayer->GetCharSkill().AddOtherSkill( CurCfg->nMoonTelentId, CurCfg->nMoonTelentLevel );
		}
	}
}

void CTianLing::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	// 天灵属性
	int32_t CurLevel = m_pPlayer->getRecord( 1148 );
	const TianLingCfg* CurCfg = CFG_DATA.GetTianLingCfg( CurLevel );
	if ( CurCfg != NULL )
	{
		for ( std::list<AddAttribute>::const_iterator iter = CurCfg->AttrList.begin();
			iter != CurCfg->AttrList.end(); ++iter )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)iter->m_nAddAttrType, iter->m_nAddAttrValue );
		}
	}

	// 战魂属性
	int32_t CurLevel_ZhanHun = m_pPlayer->getRecord( 37501 );
	const ZhanHunCfg* CurCfg_ZhanHun = CFG_DATA.GetZhanHunCfg( CurLevel_ZhanHun );
	if ( CurCfg_ZhanHun != NULL )
	{
		for ( std::list<AddAttribute>::const_iterator iter = CurCfg_ZhanHun->lAddAttrs.begin();
			iter != CurCfg_ZhanHun->lAddAttrs.end(); ++iter )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)iter->m_nAddAttrType, iter->m_nAddAttrValue );
		}
	}

	// 日月属性
	int32_t CurLevel_SunAndMoon = m_pPlayer->getRecord( 37506 );
	const SunAndMoonCfg* CurCfg_SunAndMoon = CFG_DATA.GetSunAndMoonCfg( CurLevel_SunAndMoon );
	if ( CurCfg_SunAndMoon != NULL )
	{
		for ( std::list<AddAttribute>::const_iterator iter = CurCfg_SunAndMoon->lAttr.begin();
			iter != CurCfg_SunAndMoon->lAttr.end(); ++iter )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)iter->m_nAddAttrType, iter->m_nAddAttrValue );
		}
	}
}

int32_t CTianLing::OnTianLingLevelUp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t CurLevel = m_pPlayer->getRecord( 1148 );
	const TianLingCfg* CurCfg = CFG_DATA.GetTianLingCfg( CurLevel );
	const TianLingCfg* NextCfg = CFG_DATA.GetTianLingCfg( CurLevel + 1 );
	if ( NULL == CurCfg || NULL == NextCfg )
	{
		return ERR_INVALID_DATA;
	}

	// 检查金币
	if ( CurCfg->CostMoney > 0 && m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < CurCfg->CostMoney )
	{
		return ERR_INVALID_DATA;
	}

	// 检查活力
	if ( CurCfg->CostCoin > 0 && m_pPlayer->GetCurrency( CURRENCY_VIGOUR ) < CurCfg->CostCoin )
	{
		return ERR_INVALID_DATA;
	}

	// 扣除物品
	if ( !CurCfg->CostItems.empty() && !m_pPlayer->GetBag().removeCombiItem( CurCfg->CostItems, IDCR_NONE ) )
	{
		return ERR_INVALID_DATA;
	}

	// 扣除金币
	if ( CurCfg->CostMoney > 0 )
	{
		int32_t nCostMoney = CurCfg->CostMoney;
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( nCostMoney, MCR_TIAN_LING_LEVEL_UP, 0 ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	// 扣除活力
	if ( CurCfg->CostCoin > 0 )
	{
		if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, CurCfg->CostCoin, MCR_TIAN_LING_LEVEL_UP, 0 ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	m_pPlayer->updateRecord( 1148, CurLevel + 1 );

	// 更新任务计数
	m_pPlayer->GetTask().updateTaskCount( 37 );

	// 同步社交信息和七日任务
	// FaBao/Social sync: SendFaBaoInfo is private; called internally by CFaBao on upgrade
	// Seven day task: tracked via TianLing level-up event elsewhere

	m_pPlayer->RecalcAttr();

	// 世界广播
	if ( NextCfg->GongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet != NULL )
		{
			packet->writeInt32( NextCfg->GongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( CurLevel + 1 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	return ERR_OK;
}

int32_t CTianLing::OnZhanHunLevelUp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t CurLevel = m_pPlayer->getRecord( 37501 );
	const ZhanHunCfg* CurCfg = CFG_DATA.GetZhanHunCfg( CurLevel );
	const ZhanHunCfg* NextCfg = CFG_DATA.GetZhanHunCfg( CurLevel + 1 );
	if ( NULL == CurCfg || NULL == NextCfg )
	{
		return ERR_INVALID_DATA;
	}

	// 检查金币
	if ( CurCfg->nMoney > 0 && m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < CurCfg->nMoney )
	{
		return ERR_INVALID_DATA;
	}

	// 检查活力
	if ( CurCfg->nSyb > 0 && m_pPlayer->GetCurrency( CURRENCY_VIGOUR ) < CurCfg->nSyb )
	{
		return ERR_INVALID_DATA;
	}

	// 扣除金币
	if ( CurCfg->nMoney > 0 )
	{
		int32_t nCostMoney = CurCfg->nMoney;
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( nCostMoney, MCR_TIAN_LING_LEVEL_UP, 0 ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	// 扣除活力
	if ( CurCfg->nSyb > 0 )
	{
		if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, CurCfg->nSyb, MCR_TIAN_LING_LEVEL_UP, 0 ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	m_pPlayer->updateRecord( 37501, CurLevel + 1 );
	m_pPlayer->RecalcAttr();

	// 世界广播
	if ( NextCfg->nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet != NULL )
		{
			packet->writeInt32( NextCfg->nGongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( CurLevel + 1 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	return ERR_OK;
}

int32_t CTianLing::OnSunAndMoonLevelUp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nAutoBuy = inPacket->readInt8();
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	int32_t CurLevel = m_pPlayer->getRecord( 37506 );
	const SunAndMoonCfg* CurCfg = CFG_DATA.GetSunAndMoonCfg( CurLevel );
	const SunAndMoonCfg* NextCfg = CFG_DATA.GetSunAndMoonCfg( CurLevel + 1 );
	if ( NULL == CurCfg || NULL == NextCfg )
	{
		return ERR_INVALID_DATA;
	}

	bool bSuccess = false;
	int32_t nCostGold = 0;

	if ( nAutoBuy != 0 )
	{
		// 自动购买模式：计算已有物品，不足部分从商城购买
		ItemDataList costItemList = CurCfg->lConstItems;

		for ( ItemDataList::iterator iter = costItemList.begin(); iter != costItemList.end(); )
		{
			int32_t nBuyCount = 0;
			int32_t nItemCount = m_pPlayer->GetBag().GetItemCount( vSlot, iter->m_nClass, iter->m_nId );

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

		// 检查金币是否足够
		if ( nCostGold > 0 && m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nCostGold )
		{
			return ERR_INVALID_DATA;
		}

		// 扣除物品
		if ( !costItemList.empty() && !m_pPlayer->GetBag().removeCombiItem( costItemList, IDCR_SUN_AND_MOON_LEVEL_UP ) )
		{
			return ERR_INVALID_DATA;
		}

		// 扣除金币
		if ( nCostGold > 0 && !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_SUN_AND_MOON_LEVEL_UP, 0 ) )
		{
			return ERR_INVALID_DATA;
		}

		bSuccess = true;
	}
	else
	{
		// 普通模式：直接检查物品
		if ( !CurCfg->lConstItems.empty() && !m_pPlayer->GetBag().removeCombiItem( CurCfg->lConstItems, IDCR_SUN_AND_MOON_LEVEL_UP ) )
		{
			return ERR_INVALID_DATA;
		}
		bSuccess = true;
	}

	if ( !bSuccess )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 37506, CurLevel + 1 );

	// 移除旧技能
	if ( CurCfg->nSunTelentId > 0 && CurCfg->nSunTelentLevel > 0 )
	{
		m_pPlayer->GetCharSkill().removeSkillByTalent( CurCfg->nSunTelentId );
	}

	// 添加新技能
	if ( NextCfg->nSunTelentId > 0 && NextCfg->nSunTelentLevel > 0 )
	{
		m_pPlayer->GetCharSkill().AddOtherSkill( NextCfg->nSunTelentId, NextCfg->nSunTelentLevel );
	}

	// 移除旧技能
	if ( CurCfg->nMoonTelentId > 0 && CurCfg->nMoonTelentLevel > 0 )
	{
		m_pPlayer->GetCharSkill().removeSkillByTalent( CurCfg->nMoonTelentId );
	}

	// 添加新技能
	if ( NextCfg->nMoonTelentId > 0 && NextCfg->nMoonTelentLevel > 0 )
	{
		m_pPlayer->GetCharSkill().AddOtherSkill( NextCfg->nMoonTelentId, NextCfg->nMoonTelentLevel );
	}

	// 世界广播
	if ( NextCfg->nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet != NULL )
		{
			packet->writeInt32( NextCfg->nGongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( CurLevel + 1 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	m_pPlayer->RecalcAttr();
	return ERR_OK;
}

bool CTianLing::GetMonsterItem( MemChrBag item )
{
	if ( NULL == m_pPlayer || item.itemId <= 0 || item.itemClass <= 0 || item.itemCount <= 0 )
	{
		return false;
	}

	int32_t CurLevel = m_pPlayer->getRecord( 37506 );
	const SunAndMoonCfg* CurCfg = CFG_DATA.GetSunAndMoonCfg( CurLevel );
	if ( NULL == CurCfg )
	{
		return false;
	}

	if ( CurCfg->nGetItemTimes - m_pPlayer->getRecord( 2131 ) <= 0 )
	{
		m_pPlayer->TiShiInfo( 32, 0 );
		return false;
	}

	if ( m_pPlayer->GetBag().AddItem( item, IACR_NONE ) )
	{
		m_pPlayer->GetOperateLimit().AddLimitCount( 2131, 1 );
		return true;
	}
	else
	{
		m_pPlayer->TiShiInfo( 2048, 0 );
		return false;
	}
}
