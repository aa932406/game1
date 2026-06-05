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
	: m_id(0), m_base(0), m_param(0), m_lower(0), m_upper(0)
{

}

MoneyGain::~MoneyGain()
{

}

int32_t MoneyGain::effect(Player &launcher, Unit &target,int32_t count)
{
	int32_t addon = static_cast<int32_t>((m_base + launcher.getLevel()*m_param + RANDOM.generate(m_lower, m_upper)) * launcher.benefitRatio());
	if (count > 0)
	{
		addon *= count;
	}

	launcher.AddCurrency( CURRENCY_MONEY, addon, MCR_MONEY_GAIN_ITEM, m_id );

	return ERR_OK;
}

bool MoneyGain::parseEffect(int32_t id, const std::string &strEffect)
{
	m_id = id;

	StringVector params = StringUtility::split(strEffect, ":");
	if (params.size() == 4)
	{
		m_base = atoi(params[0].c_str());
		m_param = atoi(params[1].c_str());
		m_lower = atoi(params[2].c_str());
		m_upper = atoi(params[3].c_str());

		return m_id > 0 && m_base >= 0 && m_param >= 0 && m_lower >= 0 && m_upper >= 0 && m_upper >= m_lower;
	}

	return false;
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

