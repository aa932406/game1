#pragma once

#include <map>
#include <string>

class Player;
class Unit;

class ItemEffect
{
public:
	ItemEffect();
	virtual ~ItemEffect();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0) = 0;
	//virtual int32_t effect(ViceGeneral* pVicegeneral, Unit &target);
	virtual bool parseEffect(int32_t id, const std::string &strEffect) = 0;
};

class ChiXuHuiXue
	: public ItemEffect
{
public:
	ChiXuHuiXue();
	virtual ~ChiXuHuiXue();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	CfgBuff *m_cfgBuff;
};

class ChiXuHuiMo
	: public ItemEffect
{
public:
	ChiXuHuiMo();
	virtual ~ChiXuHuiMo();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	CfgBuff *m_cfgBuff;
};

class FamilyWarPetRevive
	: public ItemEffect
{
public:
	FamilyWarPetRevive();
	virtual ~FamilyWarPetRevive();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
};

class FamilyLightWine
	: public ItemEffect
{
public:
	FamilyLightWine();
	virtual ~FamilyLightWine();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	CfgBuff *m_cfgBuff;
};

class ShunJianHuiXue
	: public ItemEffect
{
public:
	ShunJianHuiXue();
	virtual ~ShunJianHuiXue();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	//virtual int32_t effect(ViceGeneral*pVicegeneral,Unit &target);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_addon;
};

class JiuShuCard
: public ItemEffect
{
public:
	JiuShuCard();
	virtual ~JiuShuCard();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_addon;
};

class LiQuan
	:public ItemEffect
{
public:
	LiQuan();
	virtual ~LiQuan();
public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_addon;
};

class HunLiLevelUp
	:public ItemEffect
{
public:
	HunLiLevelUp();
	virtual ~HunLiLevelUp();
public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);
};

class ItemGold
	:public ItemEffect
{
public:
	ItemGold();
	virtual ~ItemGold();
public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_addon;
};
//vip体验卡
class ItemVipCard	
	:public ItemEffect
{
public:
	ItemVipCard();
	virtual ~ItemVipCard();
public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);
};

class LiBao
	: public ItemEffect
{
public:
	LiBao();
	virtual ~LiBao();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	CfgItemGiftVector m_gifts;
	int32_t m_month;
	int32_t m_record;
};
//自动使用的宠物礼包
class CAutoPetGift
	: public ItemEffect
{
public:
	CAutoPetGift();
	virtual ~CAutoPetGift();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	CfgItemGiftVector m_gifts;
};

class MoneyGain
	: public ItemEffect
{
public:
	MoneyGain();
	virtual ~MoneyGain();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_id;
	int32_t m_base;
	int32_t m_param;
	int32_t m_lower;
	int32_t m_upper;
};

class CurrencyRes
	: public ItemEffect
{
public:
	CurrencyRes();
	virtual ~CurrencyRes();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t	m_CurrecyType;
	int32_t m_CurrecyCount;
	int32_t m_id;
};

class UpLevel
	: public ItemEffect
{
public:
	UpLevel();
	virtual ~UpLevel();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Level;
	int32_t	m_AddLevel;
	int32_t	m_AddExp;
};

class FaBaoResourceItem
	: public ItemEffect
{
public:
	FaBaoResourceItem();
	virtual ~FaBaoResourceItem();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t		m_Values;
	int8_t		m_FaBaoResourceType;
};

class Jingyandan
	: public ItemEffect
{
public:
	Jingyandan();
	virtual ~Jingyandan();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t  m_exp;
};

class PetAddThird
	: public ItemEffect
{
public:
	PetAddThird();
	virtual ~PetAddThird();

public:
	virtual int32_t effect(Player &launcher, Unit &target, int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);
};

class ItemPersistBuff
	: public ItemEffect
{
public:
	ItemPersistBuff();
	virtual ~ItemPersistBuff();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual int32_t effect(Player &launcher, Unit &target);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	CfgBuff *m_cfgBuff;
};

class ExpGainWithEffect
	: public ItemEffect
{
public:
	ExpGainWithEffect();
	virtual ~ExpGainWithEffect();

public:
	virtual int32_t effect(Player &launcher, Unit &target);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_id;
	int32_t m_mapid;
	int32_t m_param_a;
	int32_t m_param_b;
	std::string m_effect;
};

class SuiJiLiBao
	: public ItemEffect
{
public:
	SuiJiLiBao();
	virtual ~SuiJiLiBao();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	//virtual int32_t effect(Player &launcher, Unit &target);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	CfgItemGiftRandomVector m_gifts;
};

class EnterDungeon
	: public ItemEffect
{
public:
	EnterDungeon();
	virtual ~EnterDungeon();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t  m_DungeonId;
};

class SuperExchange
	: public ItemEffect
{
public:
	SuperExchange();
	virtual ~SuperExchange();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	//virtual int32_t effect(Player &launcher, Unit &target);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_id;
	SuperExchangeToItemVector m_exchangeToItems;
};

class ItemEffectManager
{
public:
	ItemEffectManager();
	~ItemEffectManager();

public:
	void init();
	int32_t effect(int32_t itemid, Player &launcher, Unit &target,int32_t count = 0);
	//int32_t effect(int32_t itemid, ViceGeneral* pVicegeneral, Unit &target);

private:
	typedef std::map<int32_t, ItemEffect*> Int32ItemEffectMap;
	Int32ItemEffectMap m_itemEffects;
	Answer::RwLock m_itemEffectsLock;
};
#define ITEM_EFFECT Answer::Singleton<ItemEffectManager>::instance()

