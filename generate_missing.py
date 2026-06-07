#!/usr/bin/env python3
"""
Generate missing class implementations for the gameserver project.
Reads decompiled source and produces cleaned C++ code.
"""
import os, re

DEC_DIR = "/home/gameserver/decompiled_backup"
PROJ_DIR = "/home/gameserver/gameserver"

###############################################################################
# 1. Item Effect classes - append to ItemEffect.h and ItemEffect.cpp
###############################################################################

ITEM_EFFECT_CLASSES = {
    "AddStarVipTime": {"members": ["int32_t Value;"], "parent": "ItemEffect",
        "effect_body": """\tCVip* pVip = launcher.GetPlayerVip();
\tif (!pVip->HaveVipPrivilege())
\t\treturn 10002;
\tpVip->AddVipTime(2, Value);
\tpVip->SendVipInfo();
\treturn 0;""",
        "parse_body": """\tValue = atoi(strEffect.c_str());
\treturn Value > 0;"""},

    "BackCityPaper": {"members": ["int32_t m_MapId;", "int32_t m_X;", "int32_t m_Y;"], "parent": "ItemEffect",
        "effect_body": """\t// TODO: implement BackCityPaper::effect - teleport player
\treturn 0;""",
        "parse_body": """\tStringVector params;
\tAnswer::StringUtility::split(params, strEffect, ":");
\tif (params.size() >= 3)
\t{
\t\tm_MapId = atoi(params[0].c_str());
\t\tm_X = atoi(params[1].c_str());
\t\tm_Y = atoi(params[2].c_str());
\t\treturn true;
\t}
\treturn false;"""},

    "BlessWater1": {"members": [], "parent": "ItemEffect",
        "effect_body": """\t// BlessWater1: bless weapon (+1 bless level)
\tCExtEquip* pEquip = launcher.GetEquip();
\tconst MemChrBag& slot = pEquip->GetEquipSlot(0);
\tif (slot.itemId <= 0)
\t\treturn 10002;
\tint32_t nBless = pEquip->GetWeaponBless();
\tCfgData* pCfg = CFG_DATA;
\tconst CfgEquipBlessTable* pTable = pCfg->GetEquipBlessTable();
\tif (!pTable->GetInfo(nBless + 1))
\t\treturn 10002;
\tconst CfgEquipBless* pCfgBless = pTable->GetInfo(nBless);
\tif (!pCfgBless)
\t\treturn 10002;
\tint8_t nEffect = pCfgBless->RandomEffect();
\tif (nEffect == 1)
\t{
\t\t++nBless;
\t\tpEquip->SetWeaponBless(nBless);
\t\tpCfgBless = pTable->GetInfo(nBless);
\t\tif (pCfgBless && pCfgBless->nBroad > 0)
\t\t{
\t\t\t// broadcast bless upgrade
\t\t}
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\treturn true;"""},

    "BlessWater2": {"members": [], "parent": "ItemEffect",
        "effect_body": """\t// BlessWater2: bless armor
\tCExtEquip* pEquip = launcher.GetEquip();
\tconst MemChrBag& slot = pEquip->GetEquipSlot(1);
\tif (slot.itemId <= 0)
\t\treturn 10002;
\tint32_t nBless = pEquip->GetArmorBless();
\tCfgData* pCfg = CFG_DATA;
\tconst CfgEquipBlessTable* pTable = pCfg->GetEquipBlessTable();
\tif (!pTable->GetInfo(nBless + 1))
\t\treturn 10002;
\tconst CfgEquipBless* pCfgBless = pTable->GetInfo(nBless);
\tif (!pCfgBless)
\t\treturn 10002;
\tint8_t nEffect = pCfgBless->RandomEffect();
\tif (nEffect == 1)
\t{
\t\t++nBless;
\t\tpEquip->SetArmorBless(nBless);
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\treturn true;"""},

    "ChongZhiGift": {"members": ["int32_t m_Index;"], "parent": "ItemEffect",
        "effect_body": """\tCYunYingHD* pYunYing = launcher.GetYunYingHD();
\tif (pYunYing)
\t\treturn pYunYing->OnChongZhiGift(m_Index);
\treturn 10002;""",
        "parse_body": """\tm_Index = atoi(strEffect.c_str());
\treturn m_Index > 0;"""},

    "EquipBox": {"members": ["int32_t m_BoxId;"], "parent": "ItemEffect",
        "effect_body": """\tCExtEquip* pEquip = launcher.GetEquip();
\tif (pEquip)
\t\treturn pEquip->OpenEquipBox(m_BoxId);
\treturn 10002;""",
        "parse_body": """\tm_BoxId = atoi(strEffect.c_str());
\treturn m_BoxId > 0;"""},

    "FamilyMemberCard": {"members": ["int32_t m_Days;"], "parent": "ItemEffect",
        "effect_body": """\tCExtCharFamily* pFamily = launcher.GetCharFamily();
\tif (pFamily)
\t\treturn pFamily->AddFamilyMemberCard(m_Days);
\treturn 10002;""",
        "parse_body": """\tm_Days = atoi(strEffect.c_str());
\treturn m_Days > 0;"""},

    "GoblinItem": {"members": ["int32_t m_GoblinId;"], "parent": "ItemEffect",
        "effect_body": """\tCGoblin* pGoblin = launcher.GetGoblin();
\tif (pGoblin)
\t\treturn pGoblin->OnUseGoblinItem(m_GoblinId);
\treturn 10002;""",
        "parse_body": """\tm_GoblinId = atoi(strEffect.c_str());
\treturn m_GoblinId > 0;"""},

    "GoldEgg": {"members": ["int32_t m_ActId;"], "parent": "ItemEffect",
        "effect_body": """\tCfgData* pCfg = CFG_DATA;
\tconst CfgGoldEgg* pGoldEgg = pCfg->GetCfgGoldEgg(m_ActId);
\tif (!pGoldEgg)
\t\treturn 10002;
\t// TODO: implement GoldEgg effect
\treturn 0;""",
        "parse_body": """\tm_ActId = atoi(strEffect.c_str());
\treturn m_ActId > 0;"""},

    "GongMingZhi": {"members": ["int32_t m_Count;"], "parent": "ItemEffect",
        "effect_body": """\tCGongMing* pGongMing = launcher.GetGongMing();
\tif (pGongMing)
\t\treturn pGongMing->AddGongMingZhi(m_Count);
\treturn 10002;""",
        "parse_body": """\tm_Count = atoi(strEffect.c_str());
\treturn m_Count > 0;"""},

    "ItemAddBuff": {"members": ["int32_t m_itemid;", "CfgBuff* m_cfgBuff;"], "parent": "ItemEffect",
        "effect_body": """\tif (m_cfgBuff)
\t\tlauncher.AddBuff(*m_cfgBuff, 0);
\treturn 0;""",
        "parse_body": """\tm_itemid = id;
\tm_cfgBuff = CFG_DATA->GetCfgBuff(atoi(strEffect.c_str()));
\treturn m_cfgBuff != NULL;"""},

    "ItemCombiPoint": {"members": ["int32_t m_Points;"], "parent": "ItemEffect",
        "effect_body": """\tCMagicBox* pBox = launcher.GetMagicBox();
\tif (pBox)
\t\treturn pBox->AddCombiPoints(m_Points);
\treturn 10002;""",
        "parse_body": """\tm_Points = atoi(strEffect.c_str());
\treturn m_Points > 0;"""},

    "ItemCombiScroll": {"members": ["int32_t m_ScrollId;"], "parent": "ItemEffect",
        "effect_body": """\tCMagicBox* pBox = launcher.GetMagicBox();
\tif (pBox)
\t\treturn pBox->UseCombiScroll(m_ScrollId);
\treturn 10002;""",
        "parse_body": """\tm_ScrollId = atoi(strEffect.c_str());
\treturn m_ScrollId > 0;"""},

    "OreItem": {"members": ["int32_t m_nId;", "int32_t m_Exp;"], "parent": "ItemEffect",
        "effect_body": """\tint32_t val = count * m_Exp;
\tCExtCharFamily* pFamily = launcher.GetCharFamily();
\tif (!pFamily->AddMedRes(val))
\t\treturn 2;
\treturn 0;""",
        "parse_body": """\tm_nId = id;
\tm_Exp = atoi(strEffect.c_str());
\treturn m_Exp > 0;"""},

    "PetAtkSpd": {"members": ["int32_t Value;"], "parent": "ItemEffect",
        "effect_body": """\tif (launcher.getRecord(1154) > 0)
\t\treturn 2;
\tlauncher.updateRecord(1154, Value);
\tlauncher.RecalcAttr();
\treturn 0;""",
        "parse_body": """\tValue = atoi(strEffect.c_str());
\treturn Value > 0;"""},

    "PetShiHua": {"members": ["int32_t Value;"], "parent": "ItemEffect",
        "effect_body": """\tif (launcher.getRecord(1153) > 0)
\t\treturn 2;
\tlauncher.updateRecord(1153, Value);
\tlauncher.RecalcAttr();
\tlauncher.SetNeedSyncAround();
\tlauncher.SetNeedSync();
\treturn 0;""",
        "parse_body": """\tValue = atoi(strEffect.c_str());
\treturn Value > 0;"""},

    "RandomBuff": {"members": ["std::list<randBuff> m_buffs;", "int32_t m_nSumRate;"], "parent": "ItemEffect",
        "extra_pub": "struct randBuff { int32_t nRate; CfgBuff* m_cfgBuff; };",
        "effect_body": """\tMap* pMap = launcher.getMap();
\tif (pMap)
\t{
\t\tCActivityMap* pActMap = dynamic_cast<CActivityMap*>(pMap);
\t\tif (pActMap)
\t\t{
\t\t\tCActivity* pAct = pActMap->GetActivity();
\t\t\tCPeerlessWar* pPW = pAct ? dynamic_cast<CPeerlessWar*>(pAct) : NULL;
\t\t\tif (pPW && pPW->IsRuning())
\t\t\t{
\t\t\t\tint32_t nRand = Answer::Singleton<Answer::Random>::instance()->generate(0, m_nSumRate);
\t\t\t\tfor (auto it = m_buffs.begin(); it != m_buffs.end(); ++it)
\t\t\t\t{
\t\t\t\t\tif (it->nRate >= nRand && it->m_cfgBuff)
\t\t\t\t\t{
\t\t\t\t\t\tlauncher.AddBuff(*it->m_cfgBuff, 0);
\t\t\t\t\t\tbreak;
\t\t\t\t\t}
\t\t\t\t}
\t\t\t}
\t\t}
\t}
\treturn 0;""",
        "parse_body": """\t// parse "rate1:buffid1,rate2:buffid2"
\tm_nSumRate = 0;
\tStringVector entries;
\tAnswer::StringUtility::split(entries, strEffect, ",");
\tfor (auto& e : entries)
\t{
\t\tStringVector kv;
\t\tAnswer::StringUtility::split(kv, e, ":");
\t\tif (kv.size() >= 2)
\t\t{
\t\t\trandBuff rb;
\t\t\trb.nRate = atoi(kv[0].c_str());
\t\t\trb.m_cfgBuff = CFG_DATA->GetCfgBuff(atoi(kv[1].c_str()));
\t\t\tm_nSumRate += rb.nRate;
\t\t\tm_buffs.push_back(rb);
\t\t}
\t}
\treturn m_nSumRate > 0;"""},

    "RandomPosPaper": {"members": ["int32_t m_MapId;"], "parent": "ItemEffect",
        "effect_body": """\t// TODO: implement RandomPosPaper - random teleport
\treturn 0;""",
        "parse_body": """\tm_MapId = atoi(strEffect.c_str());
\treturn m_MapId > 0;"""},

    "RechargeCard": {"members": ["int32_t m_Gold;"], "parent": "ItemEffect",
        "effect_body": """\tCurrency* pCur = launcher.GetCurrency();
\tif (pCur)
\t{
\t\tpCur->AddGold(m_Gold);
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\tm_Gold = atoi(strEffect.c_str());
\treturn m_Gold > 0;"""},

    "RechargeValueCard": {"members": ["int32_t m_Value;"], "parent": "ItemEffect",
        "effect_body": """\tCurrency* pCur = launcher.GetCurrency();
\tif (pCur)
\t{
\t\tpCur->AddCash(m_Value);
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\tm_Value = atoi(strEffect.c_str());
\treturn m_Value > 0;"""},

    "ShouChongItem": {"members": ["int32_t m_Index;"], "parent": "ItemEffect",
        "effect_body": """\t// TODO: implement ShouChongItem - first charge item
\treturn 0;""",
        "parse_body": """\tm_Index = atoi(strEffect.c_str());
\treturn m_Index > 0;"""},

    "SkillBook": {"members": ["int32_t m_SkillId;"], "parent": "ItemEffect",
        "effect_body": """\tCExtCharSkill* pSkill = launcher.GetCharSkill();
\tif (pSkill)
\t\treturn pSkill->LearnSkill(m_SkillId);
\treturn 10002;""",
        "parse_body": """\tm_SkillId = atoi(strEffect.c_str());
\treturn m_SkillId > 0;"""},

    "SkillPointBook": {"members": ["int32_t m_Points;"], "parent": "ItemEffect",
        "effect_body": """\tCExtCharSkill* pSkill = launcher.GetCharSkill();
\tif (pSkill)
\t{
\t\tpSkill->AddSkillPoint(m_Points);
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\tm_Points = atoi(strEffect.c_str());
\treturn m_Points > 0;"""},

    "SummonBoss": {"members": ["int32_t m_BossId;"], "parent": "ItemEffect",
        "effect_body": """\t// TODO: implement SummonBoss - summon world boss
\treturn 0;""",
        "parse_body": """\tm_BossId = atoi(strEffect.c_str());
\treturn m_BossId > 0;"""},

    "SuperCurse": {"members": ["int32_t m_itemid;", "CfgBuff* m_cfgBuff;"], "parent": "ItemEffect",
        "effect_body": """\tif (m_cfgBuff)
\t\ttarget.AddBuff(*m_cfgBuff, 0);
\treturn 0;""",
        "parse_body": """\tm_itemid = id;
\tm_cfgBuff = CFG_DATA->GetCfgBuff(atoi(strEffect.c_str()));
\treturn m_cfgBuff != NULL;"""},

    "TitleCard": {"members": ["int32_t m_TitleId;"], "parent": "ItemEffect",
        "effect_body": """\tCExtCharTitle* pTitle = launcher.GetCharTitle();
\tif (pTitle)
\t\treturn pTitle->AddTitle(m_TitleId);
\treturn 10002;""",
        "parse_body": """\tm_TitleId = atoi(strEffect.c_str());
\treturn m_TitleId > 0;"""},

    "UseCurrGift": {"members": ["int32_t m_Type;", "int32_t m_Count;"], "parent": "ItemEffect",
        "effect_body": """\tCurrency* pCur = launcher.GetCurrency();
\tif (pCur)
\t{
\t\tpCur->AddCurrency(m_Type, m_Count);
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\tStringVector params;
\tAnswer::StringUtility::split(params, strEffect, ":");
\tif (params.size() >= 2)
\t{
\t\tm_Type = atoi(params[0].c_str());
\t\tm_Count = atoi(params[1].c_str());
\t\treturn m_Count > 0;
\t}
\treturn false;"""},

    "UseItemGift": {"members": ["CfgItemGiftVector m_gifts;"], "parent": "ItemEffect",
        "effect_body": """\tstd::vector<MemChrBag> items;
\tfor (auto& gift : m_gifts)
\t{
\t\tMemChrBag item;
\t\titem.itemId = gift.itemId;
\t\titem.count = gift.count;
\t\titem.bind = gift.bind;
\t\titems.push_back(item);
\t}
\tif (!items.empty())
\t{
\t\tBag* pBag = launcher.GetBag();
\t\tif (pBag && pBag->AddItemsAndMingGe(items, ICR_ITEM_USE))
\t\t\treturn 0;
\t\treturn 10016;
\t}
\treturn 10002;""",
        "parse_body": """\t// parse gift items from config string
\treturn CfgData::ParseItemGiftVector(m_gifts, strEffect);"""},

    "VipDrop": {"members": ["int32_t m_DropId;"], "parent": "ItemEffect",
        "effect_body": """\t// TODO: implement VipDrop - vip drop reward
\treturn 0;""",
        "parse_body": """\tm_DropId = atoi(strEffect.c_str());
\treturn m_DropId > 0;"""},

    "WingLevelUp": {"members": ["int32_t m_Level;"], "parent": "ItemEffect",
        "effect_body": """\tCExtCharWing* pWing = launcher.GetCharWing();
\tif (pWing)
\t\treturn pWing->LevelUp(m_Level);
\treturn 10002;""",
        "parse_body": """\tm_Level = atoi(strEffect.c_str());
\treturn m_Level > 0;"""},

    "XinMoExp": {"members": ["int32_t m_Exp;"], "parent": "ItemEffect",
        "effect_body": """\tCXinMo* pXinMo = launcher.GetXinMo();
\tif (pXinMo)
\t{
\t\tpXinMo->AddExp(m_Exp);
\t\treturn 0;
\t}
\treturn 10002;""",
        "parse_body": """\tm_Exp = atoi(strEffect.c_str());
\treturn m_Exp > 0;"""},
}

###############################################################################
# Generate ItemEffect.h additions
###############################################################################
def gen_item_effect_h():
    lines = []
    for cls, info in ITEM_EFFECT_CLASSES.items():
        lines.append(f"")
        if "extra_pub" in info:
            lines.append(f"class {cls}")
            lines.append(f"\t: public {info['parent']}")
            lines.append(f"{{")
            lines.append(f"public:")
            lines.append(f"\t{cls}();")
            lines.append(f"\tvirtual ~{cls}();")
            lines.append(f"")
            lines.append(f"public:")
            lines.append(f"\tvirtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);")
            lines.append(f"\tvirtual bool parseEffect(int32_t id, const std::string &strEffect);")
            lines.append(f"")
            lines.append(f"public:")
            lines.append(f"\t{info['extra_pub']}")
            lines.append(f"")
            lines.append(f"private:")
        else:
            lines.append(f"class {cls}")
            lines.append(f"\t: public {info['parent']}")
            lines.append(f"{{")
            lines.append(f"public:")
            lines.append(f"\t{cls}();")
            lines.append(f"\tvirtual ~{cls}();")
            lines.append(f"")
            lines.append(f"public:")
            lines.append(f"\tvirtual int32_t effect(Player &launcher, Unit &target,int32_t count = 0);")
            lines.append(f"\tvirtual bool parseEffect(int32_t id, const std::string &strEffect);")
            lines.append(f"")
            lines.append(f"private:")
        for m in info["members"]:
            lines.append(f"\t{m}")
        lines.append(f"}};")
    return "\n".join(lines)

###############################################################################
# Generate ItemEffect.cpp additions
###############################################################################
def gen_item_effect_cpp():
    lines = []
    for cls, info in ITEM_EFFECT_CLASSES.items():
        # Constructor
        lines.append(f"")
        lines.append(f"{cls}::{cls}()")
        init_list = []
        for m in info["members"]:
            match = re.match(r'(\w+)\s+(\w+);', m)
            if match:
                t, n = match.groups()
                if t == "int32_t" or t == "int8_t" or t == "int16_t":
                    init_list.append(f"{n}(0)")
                elif t == "CfgBuff*":
                    init_list.append(f"{n}(NULL)")
        if init_list:
            lines.append(f"\t: {', '.join(init_list)}")
        lines.append(f"{{")
        lines.append(f"")
        lines.append(f"}}")
        lines.append(f"")
        
        # Destructor
        lines.append(f"{cls}::~{cls}()")
        lines.append(f"{{")
        lines.append(f"")
        lines.append(f"}}")
        lines.append(f"")
        
        # effect
        lines.append(f"int32_t {cls}::effect(Player &launcher, Unit &target,int32_t count)")
        lines.append(f"{{")
        lines.append(info["effect_body"])
        lines.append(f"}}")
        lines.append(f"")
        
        # parseEffect
        lines.append(f"bool {cls}::parseEffect(int32_t id, const std::string &strEffect)")
        lines.append(f"{{")
        lines.append(info["parse_body"])
        lines.append(f"}}")
    return "\n".join(lines)

###############################################################################
# Generate DB Data classes
###############################################################################
DB_DATA_CLASSES = {
    "BossKilledRewardData": {
        "members": ["std::string RewardString;"],
        "table": "mem_chr_boss_killed",
        "fields": [("reward_info", "RewardString", "string")],
    },
    "CFaBaoData": {
        "members": ["int32_t m_FaBao[4];", "int32_t m_FaBaoRes[4];"],
        "table": "mem_chr_fabao",
        "fields": [("FaBaoLevel", "RewardString", "string")],
    },
    "CGoblinData": {
        "members": ["std::string strData;"],
        "table": "mem_chr_goblin",
        "fields": [("data", "strData", "string")],
    },
    "CHuoYueDuData": {
        "members": ["int32_t nHuoYueDu;", "int32_t nTodayHuoYueDu;", "int32_t nLastTime;", "std::string strRewards;"],
        "table": "mem_chr_huoyuedu",
        "fields": [("huoyuedu", "nHuoYueDu", "int32"), ("today_huoyuedu", "nTodayHuoYueDu", "int32"), ("last_time", "nLastTime", "int32"), ("rewards", "strRewards", "string")],
    },
    "CJueWeiData": {
        "members": ["int32_t nJueWeiLevel;", "int32_t nJueWeiExp;", "std::string strRewards;"],
        "table": "mem_chr_juewei",
        "fields": [("level", "nJueWeiLevel", "int32"), ("exp", "nJueWeiExp", "int32"), ("rewards", "strRewards", "string")],
    },
    "CMonthlyChouJiangData": {
        "members": ["int32_t nFreeCount;", "int32_t nTotalCount;", "int32_t nLastFreeTime;", "std::string strRewards;"],
        "table": "mem_chr_monthly_choujiang",
        "fields": [("free_count", "nFreeCount", "int32"), ("total_count", "nTotalCount", "int32"), ("last_free_time", "nLastFreeTime", "int32"), ("rewards", "strRewards", "string")],
    },
    "CSevenDayData": {
        "members": ["int32_t nDayIndex;", "std::string strRewards;"],
        "table": "mem_chr_seven_day",
        "fields": [("day_index", "nDayIndex", "int32"), ("rewards", "strRewards", "string")],
    },
    "CShiZhuangData": {
        "members": ["int32_t nShiZhuangId;", "int32_t nLevel;", "std::string strData;"],
        "table": "mem_chr_shizhuang",
        "fields": [("shizhuang_id", "nShiZhuangId", "int32"), ("level", "nLevel", "int32"), ("data", "strData", "string")],
    },
    "CVplanData": {
        "members": ["int32_t nVplanId;", "int32_t nLevel;", "int32_t nExp;", "std::string strRewards;"],
        "table": "mem_chr_vplan",
        "fields": [("vplan_id", "nVplanId", "int32"), ("level", "nLevel", "int32"), ("exp", "nExp", "int32"), ("rewards", "strRewards", "string")],
    },
    "CharFamilyDBData": {
        "members": ["int32_t nContribution;", "int32_t nTotalContribution;", "std::string strData;"],
        "table": "mem_chr_family",
        "fields": [("contribution", "nContribution", "int32"), ("total_contribution", "nTotalContribution", "int32"), ("data", "strData", "string")],
    },
    "CharWingDBData": {
        "members": ["int32_t nWingId;", "int32_t nLevel;", "std::string strData;"],
        "table": "mem_chr_wing",
        "fields": [("wing_id", "nWingId", "int32"), ("level", "nLevel", "int32"), ("data", "strData", "string")],
    },
    "CharWishDBData": {
        "members": ["std::string strWishes;"],
        "table": "mem_chr_wish",
        "fields": [("wishes", "strWishes", "string")],
    },
    "ChouJiangData": {
        "members": ["int32_t nFreeCount;", "int32_t nLastFreeTime;", "std::string strRewards;"],
        "table": "mem_chr_choujiang",
        "fields": [("free_count", "nFreeCount", "int32"), ("last_free_time", "nLastFreeTime", "int32"), ("rewards", "strRewards", "string")],
    },
    "CurrencyDBData": {
        "members": ["int64_t vCurrency[12];"],
        "table": "mem_char_currency",
        "fields": [],
    },
    "DailyActivityData": {
        "members": ["int32_t nTodayActive;", "int32_t nTotalActive;", "std::string strRewards;"],
        "table": "mem_chr_daily_activity",
        "fields": [("today_active", "nTodayActive", "int32"), ("total_active", "nTotalActive", "int32"), ("rewards", "strRewards", "string")],
    },
    "EquipRongHeData": {
        "members": ["std::string strData;"],
        "table": "mem_chr_equip_ronghe",
        "fields": [("data", "strData", "string")],
    },
    "ExchangeDBData": {
        "members": ["int32_t nCount;", "std::string strData;"],
        "table": "mem_chr_exchange",
        "fields": [("count", "nCount", "int32"), ("data", "strData", "string")],
    },
    "MagicBoxDBData": {
        "members": ["int32_t nCombiPoints;", "int32_t nLastReviveTime;", "std::string strActiveScrolls;", "std::string strSuccessIds;"],
        "table": "mem_char_magic_box",
        "fields": [("combi_points", "nCombiPoints", "int32"), ("revive_time", "nLastReviveTime", "int32"), ("active_scrolls", "strActiveScrolls", "string"), ("success_ids", "strSuccessIds", "string")],
    },
    "MailDBData": {
        "members": ["int32_t nMailId;", "int32_t nType;", "int32_t nTime;", "std::string strSender;", "std::string strTitle;", "std::string strContent;", "std::string strItems;"],
        "table": "mem_chr_mail",
        "fields": [("mail_id", "nMailId", "int32"), ("type", "nType", "int32"), ("time", "nTime", "int32"), ("sender", "strSender", "string"), ("title", "strTitle", "string"), ("content", "strContent", "string"), ("items", "strItems", "string")],
    },
    "MemAttrData": {
        "members": ["int32_t nAttr[32];"],
        "table": "mem_chr_attr",
        "fields": [],
    },
    "MemCharacterData": {
        "members": ["int32_t nLevel;", "int32_t nExp;", "int32_t nJob;"],
        "table": "mem_character",
        "fields": [("level", "nLevel", "int32"), ("exp", "nExp", "int32"), ("job", "nJob", "int32")],
    },
    "MemChrActionData": {
        "members": ["int32_t nActionId;", "int32_t nCount;", "int32_t nLastTime;"],
        "table": "mem_chr_action",
        "fields": [("action_id", "nActionId", "int32"), ("count", "nCount", "int32"), ("last_time", "nLastTime", "int32")],
    },
    "MemChrAutoFightData": {
        "members": ["int32_t nEnabled;", "int32_t nEndTime;"],
        "table": "mem_chr_auto_fight",
        "fields": [("enabled", "nEnabled", "int32"), ("end_time", "nEndTime", "int32")],
    },
    "MemChrBagData": {
        "members": ["std::vector<MemChrBag> items;"],
        "table": "mem_chr_bag",
        "fields": [],
    },
    "MemChrBuffData": {
        "members": ["std::string strBuffs;"],
        "table": "mem_chr_buff",
        "fields": [("buffs", "strBuffs", "string")],
    },
    "MemChrDepotData": {
        "members": ["std::string strDepot;"],
        "table": "mem_chr_depot",
        "fields": [("depot", "strDepot", "string")],
    },
    "MemChrEquipData": {
        "members": ["std::string strEquips;"],
        "table": "mem_chr_equip",
        "fields": [("equips", "strEquips", "string")],
    },
    "MemChrGemData": {
        "members": ["std::string strGems;"],
        "table": "mem_chr_gem",
        "fields": [("gems", "strGems", "string")],
    },
    "MemChrSkillData": {
        "members": ["std::string strSkills;"],
        "table": "mem_chr_skill",
        "fields": [("skills", "strSkills", "string")],
    },
    "MemChrSystemSettingData": {
        "members": ["std::string strSettings;"],
        "table": "mem_chr_system_setting",
        "fields": [("settings", "strSettings", "string")],
    },
    "MemChrTaskCycleData": {
        "members": ["int32_t nCycle;", "std::string strTasks;"],
        "table": "mem_chr_task_cycle",
        "fields": [("cycle", "nCycle", "int32"), ("tasks", "strTasks", "string")],
    },
    "MemChrTaskData": {
        "members": ["std::string strTasks;"],
        "table": "mem_chr_task",
        "fields": [("tasks", "strTasks", "string")],
    },
    "MoneyRewardTaskData": {
        "members": ["int32_t nTaskId;", "int32_t nStatus;", "int32_t nCount;"],
        "table": "mem_chr_money_reward_task",
        "fields": [("task_id", "nTaskId", "int32"), ("status", "nStatus", "int32"), ("count", "nCount", "int32")],
    },
    "MysteryShopDBData": {
        "members": ["int32_t nShopId;", "std::string strData;"],
        "table": "mem_chr_mystery_shop",
        "fields": [("shop_id", "nShopId", "int32"), ("data", "strData", "string")],
    },
    "NationalDayData": {
        "members": ["std::string strData;"],
        "table": "mem_chr_national_day",
        "fields": [("data", "strData", "string")],
    },
    "OperateLimitDBData": {
        "members": ["int32_t nType;", "int32_t nCount;", "int32_t nLastTime;"],
        "table": "mem_chr_operate_limit",
        "fields": [("type", "nType", "int32"), ("count", "nCount", "int32"), ("last_time", "nLastTime", "int32")],
    },
    "PetDBData": {
        "members": ["int32_t nPetId;", "int32_t nLevel;", "int32_t nExp;", "std::string strData;"],
        "table": "mem_chr_pet",
        "fields": [("pet_id", "nPetId", "int32"), ("level", "nLevel", "int32"), ("exp", "nExp", "int32"), ("data", "strData", "string")],
    },
    "PortalDBData": {
        "members": ["int32_t nPortalId;", "std::string strData;"],
        "table": "mem_chr_portal",
        "fields": [("portal_id", "nPortalId", "int32"), ("data", "strData", "string")],
    },
    "ScoreShopData": {
        "members": ["int32_t nShopId;", "std::string strData;"],
        "table": "mem_chr_score_shop",
        "fields": [("shop_id", "nShopId", "int32"), ("data", "strData", "string")],
    },
    "ShangChengData": {
        "members": ["std::string strData;"],
        "table": "mem_chr_shangcheng",
        "fields": [("data", "strData", "string")],
    },
    "SysUserData": {
        "members": ["int64_t nUid;", "int32_t nSid;", "std::string strData;"],
        "table": "sys_user",
        "fields": [("uid", "nUid", "int64"), ("sid", "nSid", "int32"), ("data", "strData", "string")],
    },
    "SysUserPreventWallowData": {
        "members": ["struct { int64_t uid; int32_t sid; char name[64]; char identitycard[32]; int32_t isGrowUp; } data;"],
        "table": "sys_user_prevent_wallow",
        "fields": [],
    },
    "TouZiData": {
        "members": ["int32_t nTouZiId;", "int32_t nLevel;", "std::string strData;"],
        "table": "mem_chr_touzi",
        "fields": [("touzi_id", "nTouZiId", "int32"), ("level", "nLevel", "int32"), ("data", "strData", "string")],
    },
    "VipData": {
        "members": ["int32_t nVipLevel;", "int32_t nVipExp;", "int32_t nVipTime;", "std::string strData;"],
        "table": "mem_chr_vip",
        "fields": [("vip_level", "nVipLevel", "int32"), ("vip_exp", "nVipExp", "int32"), ("vip_time", "nVipTime", "int32"), ("data", "strData", "string")],
    },
    "WorshipDBData": {
        "members": ["int32_t nCount;", "int32_t nLastTime;", "std::string strData;"],
        "table": "mem_chr_worship",
        "fields": [("count", "nCount", "int32"), ("last_time", "nLastTime", "int32"), ("data", "strData", "string")],
    },
    "WuHunShopDBData": {
        "members": ["int32_t nShopId;", "std::string strData;"],
        "table": "mem_chr_wuhun_shop",
        "fields": [("shop_id", "nShopId", "int32"), ("data", "strData", "string")],
    },
    "XinMoDBData": {
        "members": ["int32_t nXinMoId;", "int32_t nLevel;", "int32_t nExp;", "std::string strData;"],
        "table": "mem_chr_xinmo",
        "fields": [("xinmo_id", "nXinMoId", "int32"), ("level", "nLevel", "int32"), ("exp", "nExp", "int32"), ("data", "strData", "string")],
    },
}

def gen_dbdata_h():
    lines = []
    for cls, info in DB_DATA_CLASSES.items():
        lines.append(f"")
        lines.append(f"class {cls}")
        lines.append(f"{{")
        lines.append(f"public:")
        lines.append(f"\t{cls}();")
        lines.append(f"\t~{cls}();")
        lines.append(f"")
        lines.append(f"\tvoid CleanUp();")
        lines.append(f"\tvoid SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid);")
        lines.append(f"\tbool LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid);")
        lines.append(f"\tvoid PackageData(Answer::NetPacket* packet);")
        lines.append(f"\tvoid UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid);")
        lines.append(f"")
        lines.append(f"public:")
        for m in info["members"]:
            lines.append(f"\t{m}")
        lines.append(f"}};")
    return "\n".join(lines)

def gen_dbdata_cpp():
    lines = []
    for cls, info in DB_DATA_CLASSES.items():
        table = info["table"]
        fields = info["fields"]
        
        # Constructor
        lines.append(f"")
        lines.append(f"{cls}::{cls}()")
        lines.append(f"{{")
        lines.append(f"\tCleanUp();")
        lines.append(f"}}")
        lines.append(f"")
        
        # Destructor
        lines.append(f"{cls}::~{cls}()")
        lines.append(f"{{")
        lines.append(f"}}")
        lines.append(f"")
        
        # CleanUp
        lines.append(f"void {cls}::CleanUp()")
        lines.append(f"{{")
        for m in info["members"]:
            match = re.match(r'(std::string|int32_t|int64_t|char)\s+(\w+)', m)
            if match:
                t, n = match.groups()
                if t == "std::string":
                    lines.append(f"\t{n}.clear();")
                elif t == "int32_t" or t == "int64_t":
                    lines.append(f"\t{n} = 0;")
            elif '[' in m:
                arr_match = re.match(r'(\w+)\s+(\w+)\[', m)
                if arr_match:
                    t, n = arr_match.groups()
                    lines.append(f"\tbzero({n}, sizeof({n}));")
        lines.append(f"}}")
        lines.append(f"")
        
        # SaveToSqlString
        lines.append(f"void {cls}::SaveToSqlString(SqlStringList* sqls, char (*szSQL)[4096], CharId_t nCid)")
        lines.append(f"{{")
        lines.append(f"\tbzero(szSQL, 0x1000);")
        if fields:
            col_list = ",".join(f"`{f[0]}`" for f in fields)
            val_list = ",".join(f"'%s'" if f[2] == "string" else "%lld" for f in fields)
            upd_list = ",".join(f"`{f[0]}`='%s'" if f[2] == "string" else f"`{f[0]}`=%lld" for f in fields)
            arg_list = ",".join(f"{f[1]}.c_str()" if f[2] == "string" else f"(long long){f[1]}" for f in fields)
            upd_arg = ",".join(f"{f[1]}.c_str()" if f[2] == "string" else f"(long long){f[1]}" for f in fields)
            lines.append(f"\tsnprintf((char*)szSQL, 0xFFF, \"INSERT INTO `{table}` (`cid`,{col_list}) VALUES (%lld,{val_list}) ON DUPLICATE KEY UPDATE {upd_list}\",")
            lines.append(f"\t\t(long long)nCid, {arg_list}, {upd_arg});")
        else:
            lines.append(f"\tsnprintf((char*)szSQL, 0xFFF, \"INSERT INTO `{table}` (`cid`) VALUES (%lld) ON DUPLICATE KEY UPDATE `cid`=%lld\",")
            lines.append(f"\t\t(long long)nCid, (long long)nCid);")
        lines.append(f"\tsqls->push_back(std::string((char*)szSQL));")
        lines.append(f"}}")
        lines.append(f"")
        
        # LoadFromDB
        lines.append(f"bool {cls}::LoadFromDB(Answer::MySqlDBGuard* db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid)")
        lines.append(f"{{")
        lines.append(f"\tbzero(szSQL, 0x1000);")
        lines.append(f"\tsnprintf((char*)szSQL, 0xFFF, \"SELECT * FROM `{table}` WHERE `cid`=%lld\", (long long)nCid);")
        lines.append(f"\tAnswer::MySqlQuery result(db->query((const char*)szSQL));")
        lines.append(f"\tif (!result.eof())")
        lines.append(f"\t{{")
        for f in fields:
            col, member, ftype = f
            if ftype == "string":
                lines.append(f"\t\t{member} = result.getStringValue(\"{col}\", \"\");")
            elif ftype == "int32":
                lines.append(f"\t\t{member} = result.getIntValue(\"{col}\", 0);")
            elif ftype == "int64":
                lines.append(f"\t\t{member} = result.getInt64Value(\"{col}\", 0);")
        lines.append(f"\t}}")
        lines.append(f"\treturn true;")
        lines.append(f"}}")
        lines.append(f"")
        
        # PackageData
        lines.append(f"void {cls}::PackageData(Answer::NetPacket* packet)")
        lines.append(f"{{")
        lines.append(f"\tif (!packet) return;")
        for m in info["members"]:
            match = re.match(r'std::string\s+(\w+)', m)
            if match:
                n = match.group(1)
                lines.append(f"\tpacket->writeUTF8({n});")
            else:
                arr_match = re.match(r'(int32_t|int64_t)\s+(\w+)\[(\d+)\]', m)
                if arr_match:
                    t, n, size = arr_match.groups()
                    lines.append(f"\tfor (int i = 0; i < {size}; i++) packet->write{(t.replace('int32_t','Int32').replace('int64_t','Int64'))}({n}[i]);")
                else:
                    s_match = re.match(r'(int32_t|int64_t)\s+(\w+)', m)
                    if s_match:
                        t, n = s_match.groups()
                        lines.append(f"\tpacket->write{(t.replace('int32_t','Int32').replace('int64_t','Int64'))}({n});")
        lines.append(f"}}")
        lines.append(f"")
        
        # UnPackageData
        lines.append(f"void {cls}::UnPackageData(Answer::NetPacket* inPacket, CharId_t nCid)")
        lines.append(f"{{")
        lines.append(f"\tif (!inPacket) return;")
        for m in info["members"]:
            match = re.match(r'std::string\s+(\w+)', m)
            if match:
                n = match.group(1)
                lines.append(f"\t{{ std::string tmp; inPacket->readUTF8(tmp); {n} = tmp; }}")
            else:
                arr_match = re.match(r'(int32_t|int64_t)\s+(\w+)\[(\d+)\]', m)
                if arr_match:
                    t, n, size = arr_match.groups()
                    fn = "readInt32" if t == "int32_t" else "readInt64"
                    lines.append(f"\tfor (int i = 0; i < {size}; i++) {n}[i] = inPacket->{fn}();")
                else:
                    s_match = re.match(r'(int32_t|int64_t)\s+(\w+)', m)
                    if s_match:
                        t, n = s_match.groups()
                        fn = "readInt32" if t == "int32_t" else "readInt64"
                        lines.append(f"\t{n} = inPacket->{fn}();")
        lines.append(f"}}")
    return "\n".join(lines)

###############################################################################
# Main - write all generated code
###############################################################################
if __name__ == "__main__":
    # Write ItemEffect.h additions
    ie_h = gen_item_effect_h()
    ie_cpp = gen_item_effect_cpp()
    db_h = gen_dbdata_h()
    db_cpp = gen_dbdata_cpp()
    
    print(f"Generated ItemEffect.h additions: {len(ie_h)} chars")
    print(f"Generated ItemEffect.cpp additions: {len(ie_cpp)} chars")
    print(f"Generated DBData.h: {len(db_h)} chars")
    print(f"Generated DBData.cpp: {len(db_cpp)} chars")
    
    # Write to files
    with open("/tmp/ie_h_additions.txt", "w") as f:
        f.write(ie_h)
    with open("/tmp/ie_cpp_additions.txt", "w") as f:
        f.write(ie_cpp)
    with open("/tmp/db_h_additions.txt", "w") as f:
        f.write(db_h)
    with open("/tmp/db_cpp_additions.txt", "w") as f:
        f.write(db_cpp)
    
    print("\nFiles written to /tmp/")
