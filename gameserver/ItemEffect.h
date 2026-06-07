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
//vip���鿨
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
//�Զ�ʹ�õĳ������
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
	int32_t m_CurrecyType;
	int32_t m_CurrecyCount;
	int32_t m_id;
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

class DaZheQuanEffect
	: public ItemEffect
{
public:
	DaZheQuanEffect();
	virtual ~DaZheQuanEffect();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Index;
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

class AddStarVipTime
	: public ItemEffect
{
public:
	AddStarVipTime();
	virtual ~AddStarVipTime();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t Value;
};

class BackCityPaper
	: public ItemEffect
{
public:
	BackCityPaper();
	virtual ~BackCityPaper();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_MapId;
	int32_t m_X;
	int32_t m_Y;
};

class BlessWater1
	: public ItemEffect
{
public:
	BlessWater1();
	virtual ~BlessWater1();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
};

class BlessWater2
	: public ItemEffect
{
public:
	BlessWater2();
	virtual ~BlessWater2();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
};

class ChongZhiGift
	: public ItemEffect
{
public:
	ChongZhiGift();
	virtual ~ChongZhiGift();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t nId;
	int32_t Value;
};

class EquipBox
	: public ItemEffect
{
public:
	EquipBox();
	virtual ~EquipBox();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_nItemId;
};

class FamilyMemberCard
	: public ItemEffect
{
public:
	FamilyMemberCard();
	virtual ~FamilyMemberCard();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Days;
};

class GoblinItem
	: public ItemEffect
{
public:
	GoblinItem();
	virtual ~GoblinItem();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_GoblinId;
};

class CfgGoldEgg;

class GoldEgg
	: public ItemEffect
{
public:
	GoldEgg();
	virtual ~GoldEgg();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	const CfgGoldEgg* m_pCfgItem;
};

class GongMingZhi
	: public ItemEffect
{
public:
	GongMingZhi();
	virtual ~GongMingZhi();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Count;
};

class ItemAddBuff
	: public ItemEffect
{
public:
	ItemAddBuff();
	virtual ~ItemAddBuff();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	CfgBuff* m_cfgBuff;
};

class ItemCombiPoint
	: public ItemEffect
{
public:
	ItemCombiPoint();
	virtual ~ItemCombiPoint();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Points;
};

class ItemCombiScroll
	: public ItemEffect
{
public:
	ItemCombiScroll();
	virtual ~ItemCombiScroll();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_ScrollId;
};

class OreItem
	: public ItemEffect
{
public:
	OreItem();
	virtual ~OreItem();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_nId;
	int32_t m_Exp;
};

class PetAtkSpd
	: public ItemEffect
{
public:
	PetAtkSpd();
	virtual ~PetAtkSpd();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t Value;
};

class PetShiHua
	: public ItemEffect
{
public:
	PetShiHua();
	virtual ~PetShiHua();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t Value;
};

class RandomBuff
	: public ItemEffect
{
public:
	struct randBuff { int32_t nRate; CfgBuff* m_cfgBuff; };
	RandomBuff();
	virtual ~RandomBuff();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	std::list<randBuff> m_buffs;
	int32_t m_nSumRate;
};

class RandomPosPaper
	: public ItemEffect
{
public:
	RandomPosPaper();
	virtual ~RandomPosPaper();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_MapId;
};

class RechargeCard
	: public ItemEffect
{
public:
	RechargeCard();
	virtual ~RechargeCard();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_addon;
};

class RechargeValueCard
	: public ItemEffect
{
public:
	RechargeValueCard();
	virtual ~RechargeValueCard();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Value;
};

class ShouChongItem
	: public ItemEffect
{
public:
	ShouChongItem();
	virtual ~ShouChongItem();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Index;
};

class SkillBook
	: public ItemEffect
{
public:
	SkillBook();
	virtual ~SkillBook();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	int32_t m_SkillId;
};

class SkillPointBook
	: public ItemEffect
{
public:
	SkillPointBook();
	virtual ~SkillPointBook();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	int32_t m_SkillId;
	int32_t m_SkillPoints;
};

class SummonBoss
	: public ItemEffect
{
public:
	SummonBoss();
	virtual ~SummonBoss();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_BossId;
};

class SuperCurse
	: public ItemEffect
{
public:
	SuperCurse();
	virtual ~SuperCurse();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_itemid;
	CfgBuff* m_cfgBuff;
};

class YanHua
	: public ItemEffect
{
public:
	YanHua();
	virtual ~YanHua();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t nId;
	int32_t YanHuaValue;
	int32_t YanHuaType;
};

class TitleCard
	: public ItemEffect
{
public:
	TitleCard();
	virtual ~TitleCard();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_TitleId;
};

class UseCurrGift
	: public ItemEffect
{
public:
	UseCurrGift();
	virtual ~UseCurrGift();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Type;
	int32_t m_Count;
};

class UseItemGift
	: public ItemEffect
{
public:
	UseItemGift();
	virtual ~UseItemGift();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	CfgItemGiftVector m_gifts;
};

class VipDrop
	: public ItemEffect
{
public:
	VipDrop();
	virtual ~VipDrop();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_DropId;
};

class WingLevelUp
	: public ItemEffect
{
public:
	WingLevelUp();
	virtual ~WingLevelUp();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t UseWingLevel;
	int32_t UpLevel;
	int32_t ItemId;
	int32_t ItemCount;
};

class LingZhu
	: public ItemEffect
{
public:
	LingZhu();
	virtual ~LingZhu();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_nId;
	int32_t m_Chip;
};

class EquipJinHua
	: public ItemEffect
{
public:
	EquipJinHua();
	virtual ~EquipJinHua();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);
	int32_t GetParamRate();

private:
	std::list<Param2> Rate;
	int32_t MaxRate;
};

class XinMoExp
	: public ItemEffect
{
public:
	XinMoExp();
	virtual ~XinMoExp();

public:
	virtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);
	virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
	int32_t m_Exp;
};

class ItemEffectManager
{
public:
	ItemEffectManager();
	~ItemEffectManager();

public:
	void init();
	int32_t effect(int32_t itemid, Player &launcher, Unit &target,int32_t count = 0);

private:
	typedef std::map<int32_t, ItemEffect*> Int32ItemEffectMap;
	Int32ItemEffectMap m_itemEffects;
	Answer::RwLock m_itemEffectsLock;
};
#define ITEM_EFFECT Answer::Singleton<ItemEffectManager>::instance()

