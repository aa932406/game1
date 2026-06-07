#include "stdafx.h"

#include "ActivityManager.h"
#include "Buff.h"
#include "CfgData.h"
#include "GameService.h"
#include "ItemBuff.h"
#include "ItemEffect.h"
#include "Map.h"
#include "MapManager.h"
#include "MonsterActivity.h"
#include "PersistBuff.h"
#include "Player.h"
#include "EquipManager.h"
#include "PoolManager.h"
#include "DBService.h"
#include "FamilyWar.h"
#include "ActivityMap.h"
#include "FamilyLight.h"

using namespace Answer;

ItemEffect::ItemEffect()
{

}

ItemEffect::~ItemEffect()
{

}

//int32_t ItemEffect::effect(ViceGeneral* pVicegeneral, Unit &target)
//{
//	 return 0;
//}

ChiXuHuiXue::ChiXuHuiXue()
	: m_itemid(0), m_cfgBuff(NULL)
{

}

ChiXuHuiXue::~ChiXuHuiXue()
{

}

int32_t ChiXuHuiXue::effect(Player &launcher, Unit &target,int32_t count)
{
	if ( launcher.HasBuffState( CObjState::OBS_YUNXUAN ) )
	{
		return ERR_INVALID_DATA;
	}

	ChiXuHuiXueBuff *pBuff = new ChiXuHuiXueBuff(launcher, *m_cfgBuff);
	if ( NULL == pBuff )
	{
		return ERR_SYETEM_ERR;
	}
	pBuff->init( m_itemid );
	launcher.addBuff( pBuff );
	return ERR_OK;
}

bool ChiXuHuiXue::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	m_cfgBuff = CFG_DATA.getBuff(atoi(strEffect.c_str()));
	return m_cfgBuff != NULL;
}



ChiXuHuiMo::ChiXuHuiMo()
{

}

ChiXuHuiMo::~ChiXuHuiMo()
{

}

int32_t ChiXuHuiMo::effect(Player &launcher, Unit &target,int32_t count)
{
	if ( launcher.HasBuffState( CObjState::OBS_YUNXUAN ) )
	{
		return ERR_INVALID_DATA;
	}

	ChiXuHuiMoBuff *pBuff = new ChiXuHuiMoBuff(launcher, *m_cfgBuff);
	if ( NULL == pBuff )
	{
		return ERR_SYETEM_ERR;
	}
	pBuff->init( m_itemid );
	launcher.addBuff( pBuff );
	return ERR_OK;
}

bool ChiXuHuiMo::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	m_cfgBuff = CFG_DATA.getBuff(atoi(strEffect.c_str()));
	return m_cfgBuff != NULL;
}

FamilyWarPetRevive::FamilyWarPetRevive()
{
}

FamilyWarPetRevive::~FamilyWarPetRevive()
{
}

int32_t FamilyWarPetRevive::effect(Player &launcher, Unit &target,int32_t count)
{
	CActivityMap* pMap = dynamic_cast<CActivityMap*>( launcher.getMap() );
	if ( pMap != NULL )
	{
		CFamilyWar* pAct = dynamic_cast<CFamilyWar*>( pMap->GetActivity() );
		if ( pAct != NULL && pAct->IsRuning() )
		{
			launcher.GetCharPet().ReviveAllPet();
			return ERR_OK;
		}
	}
	return ERR_INVALID_DATA;
}

bool FamilyWarPetRevive::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}

FamilyLightWine::FamilyLightWine()
{
}

FamilyLightWine::~FamilyLightWine()
{
}

int32_t FamilyLightWine::effect(Player &launcher, Unit &target,int32_t count)
{
	for( int32_t i = 0; i < count; ++i )
	{
		PersistBuff *persistBuff = new PersistBuff( launcher, *m_cfgBuff );
		if (NULL == persistBuff)
		{
			return ERR_INVALID_DATA;
		}
		persistBuff->init( m_itemid, 0 );
		launcher.addBuff( persistBuff );
	}
	CActivityMap* pMap = dynamic_cast<CActivityMap*>( launcher.getMap() );
	if ( pMap != NULL )
	{
		CFamilyLight* pAct = dynamic_cast<CFamilyLight*>( pMap->GetActivity() );
		if ( pAct != NULL  )
		{
			if ( pAct->IsRuning() )
			{
				pAct->DrinkWine( &launcher, count );
			}
		}
	}
	return ERR_OK;
}

bool FamilyLightWine::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	m_cfgBuff = CFG_DATA.getBuff(atoi(strEffect.c_str()));
	return m_cfgBuff != NULL;
	return true;
}

ShunJianHuiXue::ShunJianHuiXue()
	: m_addon(0)
{

}

ShunJianHuiXue::~ShunJianHuiXue()
{

}

int32_t ShunJianHuiXue::effect(Player &launcher, Unit &target,int32_t count)
{
	if ( launcher.HasBuffState( CObjState::OBS_YUNXUAN ) )
	{
		return ERR_INVALID_DATA;
	}

	launcher.AddHP(m_addon);
	return ERR_OK;
}

//int32_t ShunJianHuiXue::effect(ViceGeneral*pVicegeneral,Unit &target)
//{
//	if (NULL == pVicegeneral)
//	{
//		return ERR_INVALID_DATA;
//	}
//	if ( pVicegeneral->HasBuffState( CObjState::OBS_YUNXUAN ) )
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	pVicegeneral->AddHp(m_addon);
//	return ERR_OK;
//	  
//}

bool ShunJianHuiXue::parseEffect(int32_t id, const std::string &strEffect)
{
	m_addon = atoi(strEffect.c_str());
	return m_addon > 0;
}

LiQuan::LiQuan()
	: m_addon(0)
{

}

LiQuan::~LiQuan()
{

}

int32_t LiQuan::effect(Player &launcher, Unit &target,int32_t count)
{
	int32_t result = count == 0?m_addon:m_addon*count;
	launcher.AddCurrency( CURRENCY_CASH, result,GCR_USE_LIQUAN );
	return ERR_OK;
}

bool LiQuan::parseEffect(int32_t id, const std::string &strEffect)
{
	m_addon = atoi(strEffect.c_str());
	return m_addon > 0;
}


ItemGold::ItemGold()
	:m_addon(0)
{

}

ItemGold::~ItemGold()
{

}

int32_t ItemGold::effect(Player &launcher, Unit &target,int32_t count )
{
	int32_t result = count == 0?m_addon:m_addon*count;
	launcher.AddCurrency( CURRENCY_GOLD, result,GCR_USE_LIQUAN );
	return ERR_OK;
}

bool ItemGold::parseEffect(int32_t id, const std::string &strEffect)
{
	m_addon = atoi(strEffect.c_str());
	return m_addon > 0;
}


ItemVipCard::ItemVipCard()
{

}

ItemVipCard::~ItemVipCard()
{

}

int32_t ItemVipCard::effect(Player &launcher, Unit &target,int32_t count)
{
	if ( !launcher.GetPlayerVip().UseVipTiYanCard() )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

bool ItemVipCard::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}


LiBao::LiBao()
	: m_month(0), m_record(0)
{

}

LiBao::~LiBao()
{

}

int32_t LiBao::effect(Player &launcher, Unit &target,int32_t count)
{
	if (m_gifts.empty())
	{
		return ERR_INVALID_DATA;
	}

	MemChrBagVector items;
	std::list<int32_t> Eggs;
	std::list<CfgPetGift*> PetGifts;
	for (CfgItemGiftVector::iterator it = m_gifts.begin(); it != m_gifts.end(); ++it)
	{
		MemChrBag item = {};
		item.itemId = it->item;
		item.itemClass = it->type;
		item.itemCount = it->count;
		item.bind	   = it->bind;
		if ( item.itemClass == IC_PET_EGG )
		{
			const CfgPetEgg* pPetEgg = CFG_DATA.GetPetEggTable().GetEgg(item.itemId);
			if ( pPetEgg == NULL )
			{
				continue;
			}
			Eggs.push_back(item.itemId);
		}
		else if ( item.itemClass == IC_PET )
		{
			CfgPetGift*	pCfgPetGift = CFG_DATA.GetPetCfg( item.itemId );
			if ( NULL == pCfgPetGift )
			{
				 continue;
			}
			PetGifts.push_back( pCfgPetGift );
		}
		else
		{
// 			CfgItem *pCfgItem = CFG_DATA.getItem(item.itemId);
// 			if (pCfgItem == NULL)
// 			{
// 				continue;
// 			}

			if (it->job == 0 || it->job == launcher.getJob())
			{
				items.push_back(item);
			}
		}
	}
	if ( launcher.GetCharPet().GetFreePetFenceCount() < static_cast<int32_t>( PetGifts.size() ) )
	{
		launcher.TiShiInfo( PET_BAG_NOT_ENOUGH );
		return ERR_BAG_IS_FULL;
	}

	if ( launcher.GetCharPet().GetEggBagAddHatchBagFreeCount() < static_cast<int32_t>( Eggs.size() ) )
	{
		launcher.TiShiInfo( PET_EGG_BAG_NOT_ENOUGH );
		return ERR_BAG_IS_FULL;
	}
	if ( launcher.GetBag().GetFreeSlotCount() < static_cast<int32_t>( items.size() ) )
	{
		launcher.TiShiInfo( BAG_SLOT_NOT_ENOUGH );
		return ERR_BAG_IS_FULL;
	}
	if ( PetGifts.size() > 0 )
	{
		std::list<CfgPetGift*>::iterator it = PetGifts.begin();
		for ( ; it != PetGifts.end(); ++it )
		{
			if ( NULL == *it )
			{
				continue;
			}
			launcher.GetCharPet().AddPetFromGift( *it );
		}
	}
	if ( Eggs.size() > 0 )
	{
		launcher.GetCharPet().AddEggs( Eggs );
	}

	if ( items.size() > 0 )
	{
		launcher.GetBag().AddItem( items, IACR_LIBAO );
	}
	return ERR_OK;
}

bool LiBao::parseEffect(int32_t id, const std::string &strEffect)
{
	CfgItemGiftVector *pGift = CFG_DATA.getItemGift(id);
	if (pGift != NULL)
	{
		m_gifts = *pGift;
		return true;
	}
	else
	{
		return false;
	}
}

CAutoPetGift::CAutoPetGift()
{

}

CAutoPetGift::~CAutoPetGift()
{

}

int32_t CAutoPetGift::effect(Player &launcher, Unit &target,int32_t count )
{
	if (m_gifts.empty())
	{
		return ERR_INVALID_DATA;
	}

	std::list<CfgPetGift*> PetGifts;
	for (CfgItemGiftVector::iterator it = m_gifts.begin(); it != m_gifts.end(); ++it)
	{
		MemChrBag item = {};
		item.itemId = it->item;
		item.itemClass = it->type;
		item.itemCount = it->count;
		item.bind	   = it->bind;
		if ( item.itemClass == IC_PET )
		{
			CfgPetGift*	pCfgPetGift = CFG_DATA.GetPetCfg( item.itemId );
			if ( NULL == pCfgPetGift )
			{
				continue;
			}
			PetGifts.push_back( pCfgPetGift );
		}
	}
	if ( launcher.GetCharPet().GetFreePetFenceCount() < static_cast<int32_t>( PetGifts.size() ) )
	{
		launcher.TiShiInfo(PET_EGG_BAG_NOT_ENOUGH);
		return ERR_BAG_IS_FULL;
	}
	if ( PetGifts.size() > 0 )
	{
		std::list<CfgPetGift*>::iterator it = PetGifts.begin();
		for ( ; it != PetGifts.end(); ++it )
		{
			if ( NULL == *it )
			{
				continue;
			}
			launcher.GetCharPet().AddPetFromGift( *it );
		}
	}
	return ERR_OK;
}

bool CAutoPetGift::parseEffect(int32_t id, const std::string &strEffect)
{
	CfgItemGiftVector *pGift = CFG_DATA.getPetGift(id);
	if (pGift != NULL)
	{
		m_gifts = *pGift;
		return true;
	}
	else
	{
		return false;
	}
}

MoneyGain::MoneyGain()
	: m_CurrecyType(0), m_CurrecyCount(0), m_id(0)
{

}

MoneyGain::~MoneyGain()
{

}

int32_t MoneyGain::effect(Player &launcher, Unit &target,int32_t count)
{
	int64_t addon = m_CurrecyCount;
	if (count > 0)
		addon *= count;

	if (!launcher.AddCurrency((CURRENCY_TYPE)m_CurrecyType, addon, CURRENCY_CHANGE_REASON::MCR_MONEY_GAIN_ITEM, m_id))
		return 2;

	return 0;
}

bool MoneyGain::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params = StringUtility::split(strEffect, ":");
	if (params.size() == 2)
	{
		m_CurrecyType = atoi(params[0].c_str());
		m_CurrecyCount = atoi(params[1].c_str());
		m_id = id;
		return m_CurrecyCount > 0;
	}

	return false;
}
}


CurrencyRes::CurrencyRes()
{
	m_CurrecyType		= -1;
	m_CurrecyCount	= 0;
}

CurrencyRes::~CurrencyRes()
{

}

int32_t CurrencyRes::effect(Player &launcher, Unit &target,int32_t count)
{
	
	int32_t Addon = m_CurrecyCount;
	if (count > 0)
	{
		Addon = m_CurrecyCount * count;
	}
	if ( !launcher.AddCurrency( static_cast<CURRENCY_TYPE>(m_CurrecyType), Addon, MCR_MONEY_GAIN_ITEM, m_id ) )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK; 
}

bool CurrencyRes::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params = StringUtility::split(strEffect, ":");
	if (params.size() == 2)
	{
		m_CurrecyType			 = atoi(params[0].c_str());
		m_CurrecyCount			 = atoi(params[1].c_str());
		m_id					 = id;
		return m_CurrecyCount > 0;
	}
	return false;
}


Jingyandan::Jingyandan()
	: m_exp(0)
{

}

Jingyandan::~Jingyandan()
{

};

int32_t Jingyandan::effect(Player &launcher, Unit &target,int32_t count )
{
	  if (count)
	  {
		  launcher.addExp(m_exp*count);
	  }
	  else
	  {
		   launcher.addExp(m_exp);
	  }
      

	  return ERR_OK;
}

bool Jingyandan::parseEffect(int32_t id, const std::string &strEffect)
{
	m_exp = atoi(strEffect.c_str());
	return m_exp > 0;
}

FaBaoResourceItem::FaBaoResourceItem():m_Values(0), m_FaBaoResourceType(0)
{

}

FaBaoResourceItem::~FaBaoResourceItem()
{

}


int32_t FaBaoResourceItem::effect(Player &launcher, Unit &target,int32_t count )
{
	int32_t AddValues = 0;
	if (count > 0)
	{
		AddValues = m_Values * count;
	}
	if ( !launcher.GetPlayerFaBao().AddFaBaoRes(  static_cast<FaBaoResourceType>(m_FaBaoResourceType), AddValues ) )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

bool FaBaoResourceItem::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params = StringUtility::split(strEffect, ":");
	if (params.size() == 2)
	{
		m_Values			 = atoi(params[0].c_str());
		m_FaBaoResourceType	 = atoi(params[1].c_str());
		return m_Values > 0;
	}

	return false;
}


PetAddThird::PetAddThird()
{

}

PetAddThird::~PetAddThird()
{

}

int32_t PetAddThird::effect(Player &launcher, Unit &target, int32_t count)
{
	if ( launcher.GetOperateLimit().GetLimitCount( PR_OPEN_THIRED_FIGHT_PET ) != 2 )
	{
		return ERR_INVALID_DATA;
	}

	launcher.GetOperateLimit().AddLimitCount( PR_OPEN_THIRED_FIGHT_PET, 1 );
	launcher.GetAchievemnet().AddAchievement( AT_THREE_PET );
	return ERR_OK;
}

bool PetAddThird::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}

ItemPersistBuff::ItemPersistBuff()
	: m_itemid(0), m_cfgBuff(NULL)
{

}

ItemPersistBuff::~ItemPersistBuff()
{

}

int32_t ItemPersistBuff::effect(Player &launcher, Unit &target,int32_t count /* = 0 */)
{
	for( int32_t i = 0; i < count; ++i )
	{
		PersistBuff *persistBuff = new PersistBuff( launcher, *m_cfgBuff );
		if (NULL == persistBuff)
		{
			return ERR_INVALID_DATA;
		}
		persistBuff->init( m_itemid, 0 );
		launcher.addBuff( persistBuff );
	}
	return ERR_OK;
}

int32_t ItemPersistBuff::effect(Player &launcher, Unit &target)
{
	PersistBuff *persistBuff = new PersistBuff(launcher, *m_cfgBuff);
	if (NULL == persistBuff)
	{
		return ERR_INVALID_DATA;
	}
	persistBuff->init(m_itemid, 0);
	return launcher.addBuff(persistBuff);
}


UpLevel::UpLevel()
{
	m_AddLevel = 0;
}

UpLevel::~UpLevel()
{

}

int32_t UpLevel::effect(Player &launcher, Unit &target,int32_t count)
{
	int32_t maxLevel = launcher.GetMaxLevel();
	if ( launcher.getLevel() >= maxLevel )
	{
		return ERR_SYETEM_ERR;
	}
	if ( launcher.getLevel() <= m_Level )
	{
		if ( launcher.getLevel() + m_AddLevel > maxLevel )
		{
			launcher.SetLevel( maxLevel );
		}
		else
		{
			launcher.SetLevel( launcher.getLevel() + m_AddLevel );
		}
		launcher.SetLvelStartTime();
		launcher.LevelUped();
		return ERR_OK;
	}
	else
	{
		launcher.addExp( m_AddExp );
		return ERR_OK;
	}
}

bool UpLevel::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params = StringUtility::split(strEffect, ":");
	if (params.size() == 3 )
	{
		m_Level			 = atoi(params[0].c_str());
		m_AddLevel		 = atoi(params[1].c_str());
		m_AddExp		 = atoi(params[2].c_str());
		return m_Level > 0 && m_AddLevel > 0 && m_AddExp > 0 ;
	}
	return false;
}


JiuShuCard::JiuShuCard()
{
	m_addon = 0;
}

JiuShuCard::~JiuShuCard()
{

}

int32_t JiuShuCard::effect(Player &launcher, Unit &target,int32_t count )
{
	if ( launcher.SubPkValues( m_addon ) )
	{
		return ERR_OK;
	}
	return ERR_INVALID_DATA;
}

bool JiuShuCard::parseEffect(int32_t id, const std::string &strEffect)
{
	m_addon	 = atoi(strEffect.c_str());
	return m_addon > 0;
}

EnterDungeon::EnterDungeon()
:m_DungeonId(0)
{

}

EnterDungeon:: ~EnterDungeon()
{

}

int32_t EnterDungeon::effect(Player &launcher, Unit &target,int32_t count)
{
	if ( launcher.IsInStall() )
	{
		return ERR_INVALID_DATA;
	}
	if ( launcher.InDungeon() || launcher.InActivity() )
	{
		return ERR_INVALID_DATA;
	}

	CfgDungeon *pCfgDungeon = CFG_DATA.getDungeon(m_DungeonId);
	if ( pCfgDungeon == NULL )
	{
		return ERR_INVALID_DATA;
	}
	Dungeon* pDungeon = MAP_MANAGER.NewDungeon( m_DungeonId );
	if ( pCfgDungeon == NULL )
	{
		return ERR_INVALID_DATA;
	}
	pDungeon->start();
	launcher.setOldPosition();
	launcher.broadcastLeave();
	if ( NULL != launcher.getMap() )
	{
		launcher.getMap()->removePlayer(&launcher,false);
	}

	GAME_SERVICE.replySuccess(launcher.getGateIndex(), CM_ENTER_DUNGEON, pCfgDungeon->id);
	pDungeon->addPlayer(&launcher, pCfgDungeon->x, pCfgDungeon->y);	
	MAP_MANAGER.PostMsg( pDungeon->GetRunnerId(), GMC_ADD_DUNGEON, pDungeon );

	LogDungeon logDungeon = {};
	logDungeon.cid = launcher.getCid();
	logDungeon.did = pDungeon->getDungeonId();
	logDungeon.type = pDungeon->getDungeonType();
	logDungeon.level = launcher.getLevel();
	logDungeon.start_time = pDungeon->GetStartTime();

	DB_SERVICE.insertDungeon( logDungeon );
	return ERR_OK;
}

bool EnterDungeon::parseEffect(int32_t id, const std::string &strEffect)
{
	m_DungeonId = atoi(strEffect.c_str());
	return true;
}

bool ItemPersistBuff::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	m_cfgBuff = CFG_DATA.getBuff(atoi(strEffect.c_str()));
	return m_cfgBuff != NULL;
}

SuiJiLiBao::SuiJiLiBao()
{

}

SuiJiLiBao::~SuiJiLiBao()
{

}

int32_t SuiJiLiBao::effect(Player &launcher, Unit &target,int32_t count)
{
	if (m_gifts.empty())
	{
		return ERR_INVALID_DATA;
	}

	int32_t bagslot = launcher.getFirstFreeSlot();
	if ( bagslot < 0 )
	{
		return GAME_SERVICE.replyfailure(launcher.getGateIndex(), CM_USE_ITEM, ERR_DELAY_EXCHANGE_SLOT_NEED);
	}

	MemChrBagVector items;

	int32_t roll = RANDOM.generate(1, 1000);

	bool find = false;
	for (CfgItemGiftRandomVector::iterator it = m_gifts.begin(); it != m_gifts.end(); ++it)
	{
		if ( it->job != 0 && it->job != launcher.getJob() )
		{
			continue;
		}
		if (it->static_probability > 0)
		{
			if (RANDOM.generate(1, 1000) <= it->static_probability)
			{
				MemChrBag item = {};
				item.itemId = it->item;
				item.itemClass = it->type;
				item.itemCount = it->count;
				item.bind	   = it->bind;
				items.push_back(item);
			}
		}
		else if (it->sum_probability >= roll)
		{
			if (!find)
			{
				MemChrBag item = {};
				item.itemId = it->item;
				item.itemClass = it->type;
				item.itemCount = it->count;
				items.push_back(item);
				find = true;
			}
		}
		else
		{
			roll -= it->sum_probability;
		}
	}

	if (items.size() <= 0)
	{
		return ERR_INVALID_DATA;
	}

	if (launcher.GetBag().AddItem( items, IACR_SUIJILIBAO ))
	{
		//launcher.sendBagItemChange(&items, BT_NORMAL);
		return ERR_OK;
	}
	else
	{
		return ERR_BAG_IS_FULL;
	}
}

bool SuiJiLiBao::parseEffect(int32_t id, const std::string &strEffect)
{
	CfgItemGiftRandomVector *pCfg = CFG_DATA.getItemGiftRandom(id);
	if (pCfg != NULL)
	{
		m_gifts = *pCfg;
		return true;
	}
	else
	{
		return false;
	}
}

SuperExchange::SuperExchange()
{

}

SuperExchange::~SuperExchange()
{

}

int32_t SuperExchange::effect(Player &launcher, Unit &target,int32_t count)
{
	if (m_exchangeToItems.empty())
	{
		return ERR_INVALID_DATA;
	}
	if (count == 0)
	{
		count = 1;
	}

	for (SuperExchangeToItemVector::const_iterator it = m_exchangeToItems.begin(); it != m_exchangeToItems.end(); ++it)
	{
		switch (it->type)
		{
		case SET_EXP:
			launcher.addExp(it->value * count);
			break;
		case SET_MONEY:
			launcher.AddCurrency( CURRENCY_MONEY, it->value * count, MCR_SUPER_EXCHANGE, m_id );
			//launcher.sendMoneyChangeInfo(it->value * count, BT_NORMAL);
			break;
		//case SET_JUNGONG:
		//	launcher.addJungong(it->value * count, JCR_SUPER_EXCHANGE, BT_NORMAL);
		//	break;
		//case SET_JIANGXING:
		//	launcher.addJiangxing(it->value * count, IXCR_SUPER_EXCHANGE, BT_NORMAL);
		//	break;
		//case SET_WUHUN:
		//	launcher.addWuhuen(it->value * count, MCR_SUPER_EXCHANGE_ADD_WUHUN, BT_NORMAL);
		//	break;
		case SET_CASH:
			break;
		case SET_GOLD:
			launcher.AddCurrency( CURRENCY_CASH, it->value * count, GCR_SUPER_EXCHANGE );
			break;
		}
	}
	return ERR_OK;
}

bool SuperExchange::parseEffect(int32_t id, const std::string &strEffect)
{
	m_id = id;
	StringVector params = StringUtility::split(strEffect, "|");
	if (params.size() > 0)
	{
		for (StringVector::const_iterator it = params.begin(); it != params.end(); ++it)
		{
			StringVector subParams = StringUtility::split(*it, ":");
			if (subParams.size() == 2)
			{
				SuperExchangeToItem toItem = {};
				toItem.type = atoi(subParams[0].c_str());
				toItem.value = atoi(subParams[1].c_str());
				m_exchangeToItems.push_back(toItem);
			}
		}
		return true;
	}
	return false;
}


HunLiLevelUp::HunLiLevelUp()
{

}
HunLiLevelUp::~HunLiLevelUp()
{

}

int32_t HunLiLevelUp::effect(Player &launcher, Unit &target,int32_t count )
{
	if ( launcher.getLevel() < MAX_PLAYER_LEVEL )
	{
		launcher.SetLevel( launcher.getLevel() + 1 );
		launcher.SetLvelStartTime();
		launcher.LevelUped();
		return ERR_OK;
	}
	else
	{	
		int32_t nLevelUpNeedExp = CFG_DATA.GetSoulAttrTable().GetLevelExp( launcher.GetSoulLevel() );
		if ( nLevelUpNeedExp <= 0 )
		{
			return ERR_INVALID_DATA;
		}
		return launcher.GetCharSoul().AddLevel( 1 );
	}
}

bool HunLiLevelUp::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}


DaZheQuanEffect::DaZheQuanEffect()
	: m_Index(0)
{

}

DaZheQuanEffect::~DaZheQuanEffect()
{

}

int32_t DaZheQuanEffect::effect(Player &launcher, Unit &target,int32_t count)
{
	const DaZheQuan* pCfg = CFG_DATA.GetDaZheQuanCfg( m_Index );
	if ( NULL == pCfg || pCfg->nCurrencyValues <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( launcher.GetBag().GetFreeSlotCount() < (int32_t)pCfg->Items.size() )
	{
		return ERR_BAG_IS_FULL;
	}

	if ( !launcher.DecCurrency( (CURRENCY_TYPE)pCfg->nCurrencyType, pCfg->nCurrencyValues, GCR_DA_ZHE_QUAN, 0 ) )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !launcher.GetBag().AddItem( pCfg->Items, IACR_DA_ZHE_QUAN ) )
	{
		return ERR_SYETEM_ERR;
	}

	return ERR_OK;
}

bool DaZheQuanEffect::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Index = atoi( strEffect.c_str() );
	return m_Index > 0;
}


ItemEffectManager::ItemEffectManager()
{

}

ItemEffectManager::~ItemEffectManager()
{

}

void ItemEffectManager::init()
{
	CfgItemTable items(CFG_DATA.getAllItem());

	Answer::RwLockWrGuard lock(m_itemEffectsLock);

	m_itemEffects.clear();

	for (CfgItemTable::const_iterator it = items.begin(); it != items.end(); ++it)
	{
		ItemEffect *itemEffect = NULL;

		switch (it->second->type)
		{
		case IET_CHIXUHUIXUE: itemEffect = new ChiXuHuiXue; break;
		case IET_SHUNJIANHUIXUE: itemEffect = new ShunJianHuiXue; break;
		case IET_CHIXUHUIMO: itemEffect = new ChiXuHuiMo; break;
		case IET_JINGYANDAN:itemEffect = new Jingyandan;break;
		case IET_MONEY_GAIN: itemEffect = new MoneyGain; break;
		case IET_GIFT:itemEffect = new LiBao;break;
		case IET_LIQUAN:itemEffect = new LiQuan;break;
		case IET_SUIJILIBAO:itemEffect = new SuiJiLiBao;break;
		case IET_SUPER_EXCHANGE:itemEffect = new SuperExchange;break;
		case IET_MAXHP_DAOJU:itemEffect = new ItemPersistBuff;break;
		case IET_ATTACK_DAOJU:itemEffect = new ItemPersistBuff;break;
		case IET_VP_DAOJU:itemEffect = new ItemPersistBuff;break;
		case IET_MUTI_EXP:itemEffect = new ItemPersistBuff;break;
		case IET_EXPERIENCECARD:itemEffect = new ItemVipCard;break;
		case IET_SHU_GUANG_SUI_PIAN:
		case IET_DI_LONG_SUI_PIAN:
		case IET_FU_WEN_SUI_PIAN:
			{
				itemEffect   = new FaBaoResourceItem;
				break;
			}
		case IET_PET_ADD_THIRD:			itemEffect = new PetAddThird;			break;
		case IET_ENTER_DUNGEON:			itemEffect = new EnterDungeon;			break;
		case IET_YUANBAO:				itemEffect = new ItemGold;				break;
		case IET_FAMOLY_WAR_PET_REVIVE:	itemEffect = new FamilyWarPetRevive();	break;
		case IET_CURRENCY_RES:			itemEffect = new CurrencyRes;			break;
		case IET_FAMOLY_LIGHT_WINE:		itemEffect = new FamilyLightWine();		break;
		case IET_AUTO_PET_GIFT:			itemEffect = new CAutoPetGift;			break;
		case IET_LEVEL_UP:				itemEffect = new UpLevel;				break;
		case IET_JIU_SHU_CARD:			itemEffect = new JiuShuCard;			break;
		case IET_HUN_LI_UP:				itemEffect = new HunLiLevelUp;			break;
		case IET_DA_ZHE_QUAN:			itemEffect = new DaZheQuanEffect;				break;
		default: break;
		}

		if (itemEffect != NULL && itemEffect->parseEffect(it->second->id, it->second->effect))
		{
			m_itemEffects.insert(Int32ItemEffectMap::value_type(it->second->id, itemEffect));
		}
	}
}

int32_t ItemEffectManager::effect(int32_t itemid, Player &launcher, Unit &target,int32_t count)
{
	Answer::RwLockRdGuard lock(m_itemEffectsLock);

	Int32ItemEffectMap::iterator it = m_itemEffects.find(itemid);
	if (it == m_itemEffects.end())
	{
		return ERR_INVALID_DATA;
	}

	return it->second->effect(launcher, target,count);
}

//int32_t ItemEffectManager::effect(int32_t itemid, ViceGeneral *pVicegeneral, Unit &target)
//{
//	if (NULL == pVicegeneral)
//	{
//		return ERR_INVALID_DATA;
//	}
//	Answer::RwLockRdGuard lock(m_itemEffectsLock);
//
//	Int32ItemEffectMap::iterator it = m_itemEffects.find(itemid);
//	if (it == m_itemEffects.end())
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	return it->second->effect(pVicegeneral, target);
//}


AddStarVipTime::AddStarVipTime()
	: Value(0)
{

}

AddStarVipTime::~AddStarVipTime()
{

}

int32_t AddStarVipTime::effect(Player &launcher, Unit &target,int32_t count)
{
	CVip* pVip = launcher.GetPlayerVip();
	if (!pVip->HaveVipPrivilege())
		return 10002;
	pVip->AddVipTime(2, Value);
	pVip->SendVipInfo();
	return 0;
}

bool AddStarVipTime::parseEffect(int32_t id, const std::string &strEffect)
{
	Value = atoi(strEffect.c_str());
	return Value > 0;
}

BackCityPaper::BackCityPaper()
	: m_MapId(0), m_X(0), m_Y(0)
{

}

BackCityPaper::~BackCityPaper()
{

}

int32_t BackCityPaper::effect(Player &launcher, Unit &target,int32_t count)
{
	// TODO: implement BackCityPaper::effect - teleport player
	return 0;
}

bool BackCityPaper::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params;
	Answer::StringUtility::split(params, strEffect, ":");
	if (params.size() >= 3)
	{
		m_MapId = atoi(params[0].c_str());
		m_X = atoi(params[1].c_str());
		m_Y = atoi(params[2].c_str());
		return true;
	}
	return false;
}

BlessWater1::BlessWater1()
{

}

BlessWater1::~BlessWater1()
{

}

int32_t BlessWater1::effect(Player &launcher, Unit &target,int32_t count)
{
	// BlessWater1: bless weapon (+1 bless level)
	CExtEquip* pEquip = launcher.GetEquip();
	const MemChrBag& slot = pEquip->GetEquipSlot(0);
	if (slot.itemId <= 0)
		return 10002;
	int32_t nBless = pEquip->GetWeaponBless();
	CfgData* pCfg = CFG_DATA;
	const CfgEquipBlessTable* pTable = pCfg->GetEquipBlessTable();
	if (!pTable->GetInfo(nBless + 1))
		return 10002;
	const CfgEquipBless* pCfgBless = pTable->GetInfo(nBless);
	if (!pCfgBless)
		return 10002;
	int8_t nEffect = pCfgBless->RandomEffect();
	if (nEffect == 1)
	{
		++nBless;
		pEquip->SetWeaponBless(nBless);
		pCfgBless = pTable->GetInfo(nBless);
		if (pCfgBless && pCfgBless->nBroad > 0)
		{
			// broadcast bless upgrade
		}
		return 0;
	}
	return 10002;
}

bool BlessWater1::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}

BlessWater2::BlessWater2()
{

}

BlessWater2::~BlessWater2()
{

}

int32_t BlessWater2::effect(Player &launcher, Unit &target,int32_t count)
{
	// BlessWater2: bless armor
	CExtEquip* pEquip = launcher.GetEquip();
	const MemChrBag& slot = pEquip->GetEquipSlot(1);
	if (slot.itemId <= 0)
		return 10002;
	int32_t nBless = pEquip->GetArmorBless();
	CfgData* pCfg = CFG_DATA;
	const CfgEquipBlessTable* pTable = pCfg->GetEquipBlessTable();
	if (!pTable->GetInfo(nBless + 1))
		return 10002;
	const CfgEquipBless* pCfgBless = pTable->GetInfo(nBless);
	if (!pCfgBless)
		return 10002;
	int8_t nEffect = pCfgBless->RandomEffect();
	if (nEffect == 1)
	{
		++nBless;
		pEquip->SetArmorBless(nBless);
		return 0;
	}
	return 10002;
}

bool BlessWater2::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}

ChongZhiGift::ChongZhiGift()
	: nId(0), Value(0)
{

}

ChongZhiGift::~ChongZhiGift()
{

}

int32_t ChongZhiGift::effect(Player &launcher, Unit &target,int32_t count)
{
	if (count != 1)
		return 2;

	CfgData* pCfg = CFG_DATA;
	CfgItemGiftVector* pGift = pCfg->getItemGift(nId);
	if (!pGift)
		return 2;

	MemChrBagVector items;
	for (auto it = pGift->begin(); it != pGift->end(); ++it)
	{
		MemChrBag item;
		memset(&item, 0, sizeof(item));
		item.itemId = it->item;
		item.itemClass = it->type;
		item.itemCount = it->count;
		item.bind = it->bind;
		if (it->time > 0)
		{
			const CfgLimitTimeTable* pLimitTime = pCfg->GetLimitTimeTable();
			item.endTime = pLimitTime->GetLimitTime(it->time);
		}
		if (it->job != 0 && it->job != launcher.getJob())
			continue;
		items.push_back(item);
	}

	if (items.empty())
		return 10002;

	CExtCharBag* pBag = launcher.GetBag();
	if (pBag->GetFreeSlotCount() < (int32_t)items.size())
	{
		launcher.TiShiInfo(2048, 0);
		return 10016;
	}

	if (launcher.GetTodayPayGold() < Value)
	{
		launcher.TiShiInfo(24, 0);
		return 10016;
	}

	pBag = launcher.GetBag();
	if (!pBag->AddItem(items, ICR_LIBAO))
		return 10016;

	return 0;
}

bool ChongZhiGift::parseEffect(int32_t id, const std::string &strEffect)
{
	nId = id;
	Value = atoi(strEffect.c_str());
	return Value > 0;
}

EquipBox::EquipBox()
	: m_nItemId(0)
{

}

EquipBox::~EquipBox()
{

}

int32_t EquipBox::effect(Player &launcher, Unit &target,int32_t count)
{
	if (count <= 0)
		return 10002;

	CExtCharBag* pBag = launcher.GetBag();
	if (pBag->GetFreeSlotCount() <= 0)
		return 10002;

	CfgData* pCfg = CFG_DATA;
	const CfgEquipBoxTable* pEquipBoxTable = pCfg->GetEquipBoxTable();
	const CfgEquipBox* pCfgEquipBox = pEquipBoxTable->RandEquip(m_nItemId);
	if (!pCfgEquipBox)
		return 10002;

	int32_t nEquipId = pCfgEquipBox->vEquipId[launcher.getJob()];
	if (nEquipId <= 0)
		return 10002;

	int32_t nStar = 0;
	int32_t nRand = RANDOM.generate(1, 10000);
	for (auto it = pCfgEquipBox->lstStar.begin(); it != pCfgEquipBox->lstStar.end(); ++it)
	{
		if (it->nParam2 >= nRand)
		{
			nStar = it->nParam1;
			break;
		}
		nRand -= it->nParam2;
	}

	MemEquip equip;
	EQUIP_MGR->CreateMemEquip(equip, launcher.getConnId(), 221, nEquipId,
		launcher.getSid(), launcher.getCid(), launcher.getName(), 0, 0, nStar, 0, 0);

	if (equip.id > 0)
	{
		MemChrBag addItem;
		memset(&addItem, 0, sizeof(addItem));
		addItem.itemClass = 2;
		addItem.itemCount = 1;
		addItem.endTime = 0;
		addItem.srcId = 0;
		addItem.itemId = nEquipId;
		addItem.bind = pCfgEquipBox->nBind;
		addItem.srcId = equip.id;

		CExtCharBag* pBag2 = launcher.GetBag();
		if (!pBag2->AddItem(addItem, ICR_OPEN_EQUIP_BOX))
			return 10002;

		EQUIP_MGR->SendPlayerEquipInfo(&launcher, &equip);
		return 0;
	}

	return 10002;
}

bool EquipBox::parseEffect(int32_t id, const std::string &strEffect)
{
	m_nItemId = id;
	CfgData* pCfg = CFG_DATA;
	const CfgEquipBoxTable* pEquipBoxTable = pCfg->GetEquipBoxTable();
	return pEquipBoxTable->RandEquip(m_nItemId) != nullptr;
}

FamilyMemberCard::FamilyMemberCard()
	: m_Days(0)
{

}

FamilyMemberCard::~FamilyMemberCard()
{

}

int32_t FamilyMemberCard::effect(Player &launcher, Unit &target,int32_t count)
{
	CExtCharFamily* pFamily = launcher.GetCharFamily();
	if (pFamily)
		return pFamily->AddFamilyMemberCard(m_Days);
	return 10002;
}

bool FamilyMemberCard::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Days = atoi(strEffect.c_str());
	return m_Days > 0;
}

GoblinItem::GoblinItem()
	: m_GoblinId(0)
{

}

GoblinItem::~GoblinItem()
{

}

int32_t GoblinItem::effect(Player &launcher, Unit &target,int32_t count)
{
	CGoblin* pGoblin = launcher.GetGoblin();
	if (pGoblin)
		return pGoblin->OnUseGoblinItem(m_GoblinId);
	return 10002;
}

bool GoblinItem::parseEffect(int32_t id, const std::string &strEffect)
{
	m_GoblinId = atoi(strEffect.c_str());
	return m_GoblinId > 0;
}

GoldEgg::GoldEgg()
	: m_pCfgItem(nullptr)
{

}

GoldEgg::~GoldEgg()
{

}

int32_t GoldEgg::effect(Player &launcher, Unit &target,int32_t count)
{
	if (!m_pCfgItem || count != 1)
		return 10002;

	int32_t bagslot = launcher.getFirstFreeSlot();
	if (bagslot < 0)
	{
		return GAME_SERVICE->replyfailure(launcher.getConnId(), launcher.getGateIndex(), 0x59, 10054, 0);
	}

	int32_t v8 = m_pCfgItem->nGroupId + 6000;
	CExtOperateLimit* pLimit = launcher.GetOperateLimit();
	if (pLimit->GetLimitCount(v8) >= m_pCfgItem->nOpenTimes)
	{
		if (!launcher.DecCurrency(CURRENCY_GOLD, m_pCfgItem->nCostGold, CURRENCY_CHANGE_REASON::MCR_GOLD_EGG))
		{
			return GAME_SERVICE->replyfailure(launcher.getConnId(), launcher.getGateIndex(), 0x59, 10003, 0);
		}
	}
	else
	{
		pLimit->AddLimitCount(2019, v8, 1);
	}

	int32_t nNowTime = CTimer::GetNowTime();
	int32_t nStartDate = m_pCfgItem->nStartDate;
	int32_t nEndDate = m_pCfgItem->nEndDate;
	if (nStartDate > 0 && nNowTime < nStartDate)
		return 10002;
	if (nEndDate > 0 && nNowTime > nEndDate)
		return 10002;

	CfgGoldEggItemList tlst;
	int32_t nSumProbability = 0;
	bool bNormal = false;
	for (auto it = m_pCfgItem->lstItem.begin(); it != m_pCfgItem->lstItem.end(); ++it)
	{
		if (it->nJob != 0 && it->nJob != launcher.getJob())
			continue;
		if (it->nMinLevel > 0 && launcher.getLevel() < it->nMinLevel)
			continue;
		if (it->nMaxLevel > 0 && launcher.getLevel() > it->nMaxLevel)
			continue;
		nSumProbability += it->nProbability;
		tlst.push_back(*it);
	}

	if (tlst.empty() || nSumProbability <= 0)
		return 10002;

	int32_t nRand = RANDOM.generate(1, nSumProbability);
	MemChrBag item;
	memset(&item, 0, sizeof(item));
	int32_t nBroadcast = 0;
	for (auto it = tlst.begin(); it != tlst.end(); ++it)
	{
		if (it->nProbability >= nRand)
		{
			item.itemId = it->nItemId;
			item.itemClass = it->nItemClass;
			item.itemCount = it->nItemCount;
			item.bind = it->nBind;
			if (it->nLimitTime > 0)
			{
				const CfgLimitTimeTable* pLimitTime = CFG_DATA->GetLimitTimeTable();
				item.endTime = pLimitTime->GetLimitTime(it->nLimitTime);
			}
			nBroadcast = it->nBroadcast;
			break;
		}
		nRand -= it->nProbability;
	}

	if (nBroadcast > 0)
	{
		NetPacket* packet = GAME_SERVICE->popNetpacket(launcher.getConnId(), PACK_DISPATCH, 0x2CD6);
		if (packet)
		{
			packet->writeInt32(nBroadcast);
			packet->writeUTF8(launcher.getName());
			packet->writeInt64(launcher.getCid());
			packet->writeInt8(item.itemClass);
			packet->writeInt32(item.itemId);
			packet->setSize(packet->getWOffset());
			GAME_SERVICE->worldBroadcast(launcher.getConnId(), packet);
		}
	}

	CExtCharBag* pBag = launcher.GetBag();
	pBag->AddItem(item, ICR_GOLD_EGG_OPEN);
	return 0;
}

bool GoldEgg::parseEffect(int32_t id, const std::string &strEffect)
{
	CfgData* pCfg = CFG_DATA;
	const CfgGoldEggTable* pGoldEggTable = pCfg->GetGoldEggTable();
	m_pCfgItem = pGoldEggTable->GetGoldEgg(id);
	return m_pCfgItem != nullptr;
}

GongMingZhi::GongMingZhi()
	: m_Count(0)
{

}

GongMingZhi::~GongMingZhi()
{

}

int32_t GongMingZhi::effect(Player &launcher, Unit &target,int32_t count)
{
	CGongMing* pGongMing = launcher.GetGongMing();
	if (pGongMing)
		return pGongMing->AddGongMingZhi(m_Count);
	return 10002;
}

bool GongMingZhi::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Count = atoi(strEffect.c_str());
	return m_Count > 0;
}

ItemAddBuff::ItemAddBuff()
	: m_itemid(0)
{

}

ItemAddBuff::~ItemAddBuff()
{

}

int32_t ItemAddBuff::effect(Player &launcher, Unit &target,int32_t count)
{
	if (m_cfgBuff)
		launcher.AddBuff(*m_cfgBuff, 0);
	return 0;
}

bool ItemAddBuff::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	m_cfgBuff = CFG_DATA->GetCfgBuff(atoi(strEffect.c_str()));
	return m_cfgBuff != NULL;
}

ItemCombiPoint::ItemCombiPoint()
	: m_Points(0)
{

}

ItemCombiPoint::~ItemCombiPoint()
{

}

int32_t ItemCombiPoint::effect(Player &launcher, Unit &target,int32_t count)
{
	CMagicBox* pBox = launcher.GetMagicBox();
	if (pBox)
		return pBox->AddCombiPoints(m_Points);
	return 10002;
}

bool ItemCombiPoint::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Points = atoi(strEffect.c_str());
	return m_Points > 0;
}

ItemCombiScroll::ItemCombiScroll()
	: m_ScrollId(0)
{

}

ItemCombiScroll::~ItemCombiScroll()
{

}

int32_t ItemCombiScroll::effect(Player &launcher, Unit &target,int32_t count)
{
	CMagicBox* pBox = launcher.GetMagicBox();
	if (pBox)
		return pBox->UseCombiScroll(m_ScrollId);
	return 10002;
}

bool ItemCombiScroll::parseEffect(int32_t id, const std::string &strEffect)
{
	m_ScrollId = atoi(strEffect.c_str());
	return m_ScrollId > 0;
}

OreItem::OreItem()
	: m_nId(0), m_Exp(0)
{

}

OreItem::~OreItem()
{

}

int32_t OreItem::effect(Player &launcher, Unit &target,int32_t count)
{
	int32_t val = count * m_Exp;
	CExtCharFamily* pFamily = launcher.GetCharFamily();
	if (!pFamily->AddMedRes(val))
		return 2;
	return 0;
}

bool OreItem::parseEffect(int32_t id, const std::string &strEffect)
{
	m_nId = id;
	m_Exp = atoi(strEffect.c_str());
	return m_Exp > 0;
}

PetAtkSpd::PetAtkSpd()
	: Value(0)
{

}

PetAtkSpd::~PetAtkSpd()
{

}

int32_t PetAtkSpd::effect(Player &launcher, Unit &target,int32_t count)
{
	if (launcher.getRecord(1154) > 0)
		return 2;
	launcher.updateRecord(1154, Value);
	launcher.RecalcAttr();
	return 0;
}

bool PetAtkSpd::parseEffect(int32_t id, const std::string &strEffect)
{
	Value = atoi(strEffect.c_str());
	return Value > 0;
}

PetShiHua::PetShiHua()
	: Value(0)
{

}

PetShiHua::~PetShiHua()
{

}

int32_t PetShiHua::effect(Player &launcher, Unit &target,int32_t count)
{
	if (launcher.getRecord(1153) > 0)
		return 2;
	launcher.updateRecord(1153, Value);
	launcher.RecalcAttr();
	launcher.SetNeedSyncAround();
	launcher.SetNeedSync();
	return 0;
}

bool PetShiHua::parseEffect(int32_t id, const std::string &strEffect)
{
	Value = atoi(strEffect.c_str());
	return Value > 0;
}

RandomBuff::RandomBuff()
	: m_nSumRate(0)
{

}

RandomBuff::~RandomBuff()
{

}

int32_t RandomBuff::effect(Player &launcher, Unit &target,int32_t count)
{
	Map* pMap = launcher.getMap();
	if (pMap)
	{
		CActivityMap* pActMap = dynamic_cast<CActivityMap*>(pMap);
		if (pActMap)
		{
			CActivity* pAct = pActMap->GetActivity();
			CPeerlessWar* pPW = pAct ? dynamic_cast<CPeerlessWar*>(pAct) : NULL;
			if (pPW && pPW->IsRuning())
			{
				int32_t nRand = Answer::Singleton<Answer::Random>::instance()->generate(0, m_nSumRate);
				for (auto it = m_buffs.begin(); it != m_buffs.end(); ++it)
				{
					if (it->nRate >= nRand && it->m_cfgBuff)
					{
						launcher.AddBuff(*it->m_cfgBuff, 0);
						break;
					}
				}
			}
		}
	}
	return 0;
}

bool RandomBuff::parseEffect(int32_t id, const std::string &strEffect)
{
	// parse "rate1:buffid1,rate2:buffid2"
	m_nSumRate = 0;
	StringVector entries;
	Answer::StringUtility::split(entries, strEffect, ",");
	for (auto& e : entries)
	{
		StringVector kv;
		Answer::StringUtility::split(kv, e, ":");
		if (kv.size() >= 2)
		{
			randBuff rb;
			rb.nRate = atoi(kv[0].c_str());
			rb.m_cfgBuff = CFG_DATA->GetCfgBuff(atoi(kv[1].c_str()));
			m_nSumRate += rb.nRate;
			m_buffs.push_back(rb);
		}
	}
	return m_nSumRate > 0;
}

RandomPosPaper::RandomPosPaper()
	: m_MapId(0)
{

}

RandomPosPaper::~RandomPosPaper()
{

}

int32_t RandomPosPaper::effect(Player &launcher, Unit &target,int32_t count)
{
	// TODO: implement RandomPosPaper - random teleport
	return 0;
}

bool RandomPosPaper::parseEffect(int32_t id, const std::string &strEffect)
{
	m_MapId = atoi(strEffect.c_str());
	return m_MapId > 0;
}

RechargeCard::RechargeCard()
	: m_addon(0)
{

}

RechargeCard::~RechargeCard()
{

}

int32_t RechargeCard::effect(Player &launcher, Unit &target,int32_t count)
{
	if (count <= 0)
		return 10002;
	if (!launcher.UseRechargeCard(count * m_addon, 1))
		return 10002;
	return 0;
}

bool RechargeCard::parseEffect(int32_t id, const std::string &strEffect)
{
	m_addon = atoi(strEffect.c_str());
	return m_addon > 0;
}

RechargeValueCard::RechargeValueCard()
	: m_Value(0)
{

}

RechargeValueCard::~RechargeValueCard()
{

}

int32_t RechargeValueCard::effect(Player &launcher, Unit &target,int32_t count)
{
	Currency* pCur = launcher.GetCurrency();
	if (pCur)
	{
		pCur->AddCash(m_Value);
		return 0;
	}
	return 10002;
}

bool RechargeValueCard::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Value = atoi(strEffect.c_str());
	return m_Value > 0;
}

ShouChongItem::ShouChongItem()
	: m_Index(0)
{

}

ShouChongItem::~ShouChongItem()
{

}

int32_t ShouChongItem::effect(Player &launcher, Unit &target,int32_t count)
{
	// TODO: implement ShouChongItem - first charge item
	return 0;
}

bool ShouChongItem::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Index = atoi(strEffect.c_str());
	return m_Index > 0;
}

SkillBook::SkillBook()
	: m_itemid(0), m_SkillId(0)
{

}

SkillBook::~SkillBook()
{

}

int32_t SkillBook::effect(Player &launcher, Unit &target,int32_t count)
{
	CExtCharSkill* pSkill = launcher.GetCharSkill();
	if (pSkill)
		return pSkill->LearnSkill(m_SkillId);
	return 10002;
}

bool SkillBook::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	StringVector strParam = StringUtility::split(strEffect, "|");
	if (strParam.size() == 1)
	{
		m_SkillId = atoi(strParam[0].c_str());
		return m_SkillId > 0;
	}
	return false;
}

SkillPointBook::SkillPointBook()
	: m_itemid(0), m_SkillId(0), m_SkillPoints(0)
{

}

SkillPointBook::~SkillPointBook()
{

}

int32_t SkillPointBook::effect(Player &launcher, Unit &target,int32_t count)
{
	if (count <= 0)
		return 2;

	int32_t nPoints = m_SkillPoints * count;
	CExtCharSkill* pSkill = launcher.GetCharSkill();
	if (pSkill->AddSkillBookPoint(m_SkillId, nPoints))
		return 0;
	return 10002;
}

bool SkillPointBook::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	StringVector strParam = StringUtility::split(strEffect, "|");
	if (strParam.size() == 2)
	{
		m_SkillId = atoi(strParam[0].c_str());
		m_SkillPoints = atoi(strParam[1].c_str());
		return m_SkillId > 0 && m_SkillPoints > 0;
	}
	return false;
}

SummonBoss::SummonBoss()
	: m_BossId(0)
{

}

SummonBoss::~SummonBoss()
{

}

int32_t SummonBoss::effect(Player &launcher, Unit &target,int32_t count)
{
	// TODO: implement SummonBoss - summon world boss
	return 0;
}

bool SummonBoss::parseEffect(int32_t id, const std::string &strEffect)
{
	m_BossId = atoi(strEffect.c_str());
	return m_BossId > 0;
}

SuperCurse::SuperCurse()
	: m_itemid(0)
{

}

SuperCurse::~SuperCurse()
{

}

int32_t SuperCurse::effect(Player &launcher, Unit &target,int32_t count)
{
	if (m_cfgBuff)
		target.AddBuff(*m_cfgBuff, 0);
	return 0;
}

bool SuperCurse::parseEffect(int32_t id, const std::string &strEffect)
{
	m_itemid = id;
	m_cfgBuff = CFG_DATA->GetCfgBuff(atoi(strEffect.c_str()));
	return m_cfgBuff != NULL;
}

//////////////////////////////////////////////////////////////////////////
// YanHua
//////////////////////////////////////////////////////////////////////////
YanHua::YanHua()
	: nId(0), YanHuaValue(0), YanHuaType(0)
{
}

YanHua::~YanHua()
{
}

int32_t YanHua::effect(Player &launcher, Unit &target, int32_t count)
{
	// TODO: Full YanHua effect implementation - requires GameService, CfgData, COpenBeta integration
	// Core logic: get gift random config, roll for items, add to bag, broadcast yanHua
	return 0;
}

bool YanHua::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params;
	std::string delims(":");
	Answer::StringUtility::split(params, strEffect, delims, false);
	nId = id;
	if (params.size() == 2)
	{
		YanHuaValue = atoi(params[0].c_str());
		YanHuaType = atoi(params[1].c_str());
		return true;
	}
	return false;
}

TitleCard::TitleCard()
	: m_TitleId(0)
{

}

TitleCard::~TitleCard()
{

}

int32_t TitleCard::effect(Player &launcher, Unit &target,int32_t count)
{
	CExtCharTitle* pTitle = launcher.GetCharTitle();
	if (pTitle)
		return pTitle->AddTitle(m_TitleId);
	return 10002;
}

bool TitleCard::parseEffect(int32_t id, const std::string &strEffect)
{
	m_TitleId = atoi(strEffect.c_str());
	return m_TitleId > 0;
}

UseCurrGift::UseCurrGift()
	: m_Type(0), m_Count(0)
{

}

UseCurrGift::~UseCurrGift()
{

}

int32_t UseCurrGift::effect(Player &launcher, Unit &target,int32_t count)
{
	Currency* pCur = launcher.GetCurrency();
	if (pCur)
	{
		pCur->AddCurrency(m_Type, m_Count);
		return 0;
	}
	return 10002;
}

bool UseCurrGift::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params;
	Answer::StringUtility::split(params, strEffect, ":");
	if (params.size() >= 2)
	{
		m_Type = atoi(params[0].c_str());
		m_Count = atoi(params[1].c_str());
		return m_Count > 0;
	}
	return false;
}

UseItemGift::UseItemGift()
{

}

UseItemGift::~UseItemGift()
{

}

int32_t UseItemGift::effect(Player &launcher, Unit &target,int32_t count)
{
	std::vector<MemChrBag> items;
	for (auto& gift : m_gifts)
	{
		MemChrBag item;
		item.itemId = gift.itemId;
		item.count = gift.count;
		item.bind = gift.bind;
		items.push_back(item);
	}
	if (!items.empty())
	{
		Bag* pBag = launcher.GetBag();
		if (pBag && pBag->AddItemsAndMingGe(items, ICR_ITEM_USE))
			return 0;
		return 10016;
	}
	return 10002;
}

bool UseItemGift::parseEffect(int32_t id, const std::string &strEffect)
{
	// parse gift items from config string
	return CfgData::ParseItemGiftVector(m_gifts, strEffect);
}

VipDrop::VipDrop()
	: m_DropId(0)
{

}

VipDrop::~VipDrop()
{

}

int32_t VipDrop::effect(Player &launcher, Unit &target,int32_t count)
{
	// TODO: implement VipDrop - vip drop reward
	return 0;
}

bool VipDrop::parseEffect(int32_t id, const std::string &strEffect)
{
	m_DropId = atoi(strEffect.c_str());
	return m_DropId > 0;
}

WingLevelUp::WingLevelUp()
	: UseWingLevel(0), UpLevel(0), ItemId(0), ItemCount(0)
{

}

WingLevelUp::~WingLevelUp()
{

}

int32_t WingLevelUp::effect(Player &launcher, Unit &target,int32_t count)
{
	CExtCharWing* pWing = launcher.GetCharWing();
	if (pWing && pWing->LevelUp(UseWingLevel, UpLevel, ItemId, ItemCount))
		return 0;
	return 2;
}

bool WingLevelUp::parseEffect(int32_t id, const std::string &strEffect)
{
	StringVector params = StringUtility::split(strEffect, ":");
	if (params.size() == 4)
	{
		UseWingLevel = atoi(params[0].c_str());
		UpLevel = atoi(params[1].c_str());
		ItemId = atoi(params[2].c_str());
		ItemCount = atoi(params[3].c_str());
		return true;
	}
	return false;
}

XinMoExp::XinMoExp()
	: m_Exp(0)
{

}

XinMoExp::~XinMoExp()
{

}

int32_t XinMoExp::effect(Player &launcher, Unit &target,int32_t count)
{
	CXinMo* pXinMo = launcher.GetXinMo();
	if (pXinMo)
	{
		pXinMo->AddExp(m_Exp);
		return 0;
	}
	return 10002;
}

bool XinMoExp::parseEffect(int32_t id, const std::string &strEffect)
{
	m_Exp = atoi(strEffect.c_str());
	return m_Exp > 0;
}

LingZhu::LingZhu()
	: m_nId(0), m_Chip(0)
{

}

LingZhu::~LingZhu()
{

}

int32_t LingZhu::effect(Player &launcher, Unit &target,int32_t count)
{
	if (count <= 0)
		return 10002;

	int32_t exp = count * m_Chip;
	CKunExt* pKunExt = launcher.GetCKunExt();
	pKunExt->AddExp(exp);
	return 0;
}

bool LingZhu::parseEffect(int32_t id, const std::string &strEffect)
{
	m_nId = id;
	m_Chip = atoi(strEffect.c_str());
	return m_Chip > 0;
}

EquipJinHua::EquipJinHua()
	: MaxRate(0)
{

}

EquipJinHua::~EquipJinHua()
{

}

int32_t EquipJinHua::effect(Player &launcher, Unit &target,int32_t count)
{
	return 0;
}

bool EquipJinHua::parseEffect(int32_t id, const std::string &strEffect)
{
	return true;
}

int32_t EquipJinHua::GetParamRate()
{
	int32_t nRand = RANDOM.generate(1, MaxRate);
	for (auto it = Rate.begin(); it != Rate.end(); ++it)
	{
		if (it->nParam2 >= nRand)
			return it->nParam1;
		nRand -= it->nParam2;
	}
	return 0;
}