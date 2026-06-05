#!/usr/bin/env python3
"""Generate complete CFestivalDoubleEleven::initCfgData() from decompiled patterns"""

import re
import os

# ================================================================
# SECTION DEFINITIONS
# Each section is defined by the FAT type, section name, index in m_vStartDay/m_vEndDay,
# and a list of field loaders (type, member, key, etc.)
# ================================================================

SECTIONS = []

def section(fat_type, section_name, index, fields):
    SECTIONS.append((fat_type, section_name, index, fields))

# Helper field types:
# ("int", member, key) -> m_member = ini.getIntValue("SECTION", "key")
# ("str_to_member", member, key) -> m_member = Answer::DayTime::StringToIntTime(ini.getStrValue("SECTION", "key"))
# ("item_vec", member, key, count_member) -> load items from key1..keyN into member
# ("int_array", member, count_member, key_pattern) -> load ints from key1..keyN
# ("int_vec", vec_member, count_member, key_pattern) -> resize vec, fill from key1..keyN
# ("item_vec_array", vec_member, count_member, key_pattern) -> resize vec of vectors, fill from key1..keyN
# ("shop_goods", vec_member, count_member) -> load ShopGoods array
# ("broadcast", vec_member, count_member) -> load broadcast values
# ("rate_item", member, key) -> parse rate item
# ("parse_item", member, key) -> CItemHelper::parseItemVectorString

# LAND (index 1)
section("FAT_LAND", "LAND", 1, [
    ("int_array", "m_vLandGift", "m_nEndDay", "gift%d"),  # gift1..giftN via parseItemVectorString
])

# DAILY_RECHARGE (index 2) - just start/end day
section("FAT_DAILY_RECHARGE", "DAILY_RECHARGE", 2, [])

# DRAW (index 3)
section("FAT_DRAW", "LUCKY_DRAW", 3, [
    ("int", "m_nDrawLoopTimes", "loop_times"),
    ("parse_item_vec", "m_vDrawLoopReward", "loop_reward"),
])

# DRAW_RANK (index 4)
section("FAT_DRAW_RANK", "LUCKY_DRAW_RANK", 4, [
    ("int", "m_nDrawRankSize", "rank_size"),
    ("int", "m_nDrawRankLimit", "rank_limit"),
    ("rank_items", "m_vDrawRankMail", "m_vDrawRankReward", "m_nDrawRankSize", "rank_mail%d", "rank_reward%d"),
])

# EXCHANGE (index 5) - just start/end day
section("FAT_EXCHANGE", "EXCHANGE", 5, [])

# WORLD_BOSS (index 6)
section("FAT_WORLD_BOSS", "WORLD_BOSS", 6, [
    ("int", "m_nWorldBossIcon", "icon"),
    ("int", "m_nWorldBossStartBroadcast", "start_broadcast"),
    ("int", "m_nWorldBossEndBroadcast", "end_broadcast"),
    ("int", "m_nWorldBossKillBroadcast", "kill_broadcast"),
    ("time_area_array", "m_vWorldBossMinute", "count", "start_minute%d", "end_minute%d"),
    ("int", "m_MapId", "mapid"),
    ("int", "m_X", "x"),
    ("int", "m_Y", "y"),
    ("int", "m_Mid", "mid"),
])

# HUO_YUE_DU_SUM (index 7)
section("FAT_HUO_YUE_DU_SUM", "HUO_YUE_DU_SUM", 7, [
    ("int", "m_nHuoYueDuSumSize", "size"),
    ("reward_items", "m_vHuoYueDuSumLimit", "m_vHuoYueDuSumReward", "m_nHuoYueDuSumSize", "value%d", "reward%d"),
])

# DAILY_LIMIT_SHOP (index 8)
section("FAT_DAILY_LIMIT_SHOP", "DAILY_LIMIT_SHOP", 8, [
    ("parse_item_vec", "m_vDailyLimitShopItem", "item"),
    ("int", "m_nDailyLimitShopCostType", "cost_type"),
    ("int", "m_nDailyLimitShopCostValue", "cost_value"),
    ("int", "m_nDailyLimitShopLimit", "limit"),
])

# LAND_SUM (index 9)
section("FAT_LAND_SUM", "LAND_SUM", 9, [
    ("int_array_item", "m_vLandSumGift", "m_nEndDay", "gift%d"),
])

# ONLINE_TIME (index 10)
section("FAT_ONLINE_TIME", "DAILY_ONLINE", 10, [
    ("int", "m_nOnlineStartMinute", "start_time"),
    ("int", "m_nOnlineEndMinute", "end_time"),
    ("int", "m_nOnlineTimeArea", "dis_time"),  # * 60
    ("parse_item_vec", "m_vOnlineReward", "reward"),
    ("int", "m_nMaxCount", "max_count"),
])

# BEST_WISH (index 11)
section("FAT_BEST_WISH", "BEST_WISH", 11, [
    ("int", "m_nWishRecharge", "recharge"),
    ("parse_item_vec", "m_vWishReward", "reward"),
])

# DAILY_XIAO_FEI_RANK (index 12)
section("FAT_DAILY_XIAO_FEI_RANK", "XIAO_FEI_RANK", 12, [
    ("int", "m_nXiaoFeiRankSize", "size"),
    ("reward_items", "m_vXiaoFeiRankLimit", "m_vXiaoFeiRankMail", "m_nXiaoFeiRankSize", "limit%d", "mail%d"),
    ("reward_items_extra", "m_vXiaoFeiRankReward", "m_nXiaoFeiRankSize", "reward%d"),
])

# XIAO_FEI_DRAW (index 13)
section("FAT_XIAO_FEI_DRAW", "XIAO_FEI_DRAW", 13, [
    ("int", "m_nXiaoFeiDrawSize", "size"),
    ("int", "m_nXiaoFeiDrawValue", "need_value"),
    ("reward_items", "m_vScoreLimit", "m_vXiaoFeiSumBroadcast", "m_nXiaoFeiDrawSize", "limit%d", "broadcast%d"),
    ("reward_items_extra", "m_vBossScoreReward", "m_nXiaoFeiDrawSize", "reward%d"),
])

# MO_YU_SHI_JIE (index 14)
section("FAT_MO_YU_SHI_JIE", "MO_YU_SHI_JIE", 14, [
    ("int", "m_nMoYuShiJieDropSize", "drop_size"),
    ("int_array_simple", "m_vMoYuShiJieDrop", "m_nMoYuShiJieDropSize", "drop%d"),
    ("int", "m_nChouJiangCount", "count"),
    ("int", "m_nChouJiangType", "chou_jiang_type"),
])

# DAILY_RECHARGE_2 (index 15)
section("FAT_DAILY_RECHARGE_2", "DAILY_RECHARGE_2", 15, [
    ("int", "m_nDailyRechargeDrawSize", "size"),
    ("int", "m_nDailyRechargeDrawLimit", "limit"),
    ("reward_items", "m_vDailyRechargeLimit", "m_vDailyRechargeReward", "m_nDailyRechargeDrawSize", "limit%d", "reward%d"),
])

# XIAO_FEI_SUM_RANK (index 16)
section("FAT_XIAO_FEI_SUM_RANK", "XIAO_FEI_SUM_RANK", 16, [
    ("int", "m_nXiaoFeiSumRankSize", "size"),
    ("int", "m_nXiaoFeiSumRankLimit", "limit"),
    ("rank_items", "m_vXiaoFeiSumRankMail", "m_vXiaoFeiSumRankReward", "m_nXiaoFeiSumRankSize", "mail%d", "reward%d"),
])

# GIFT_SHOP (index 17)
section("FAT_GIFT_SHOP", "GIFT_SHOP", 17, [
    ("int", "m_nGiftShopSize", "size"),
    ("shop_goods", "m_vGiftShopGoods", "m_nGiftShopSize", "goods%d"),
])

# CHOU_JIANG (index 18)
section("FAT_CHOU_JIANG", "CHOU_JIANG", 18, [])

# FA_BAO_BACK (index 19)
section("FAT_FA_BAO_BACK", "FA_BAO_BACK", 19, [])

# MYSTERY_SHOP (index 20)
section("FAT_MYSTERY_SHOP", "MYSTERY_SHOP", 20, [
    ("int", "m_nMysteryShopRefreshBroad", "refresh_broadcast"),
    ("parse_item_data", "m_sMysteryShopRefreshCost", "refresh_cost"),
])

# RECHARGE_SUM_GIFT (index 21)
section("FAT_RECHARGE_SUM_GIFT", "RECHARGE_SUM_GIFT", 21, [
    ("int", "m_nRechargeSumSize", "size"),
    ("reward_items", "m_vRechargeSumLimit", "m_vRechargeSumReward", "m_nRechargeSumSize", "limit%d", "reward%d"),
])

# XIAO_FEI_SUM_GIFT (index 22)
section("FAT_XIAO_FEI_SUM_GIFT", "XIAO_FEI_SUM_GIFT", 22, [
    ("int", "m_nXiaoFeiSumSize", "size"),
    ("reward_items", "m_vXiaoFeiSumLimit", "m_vXiaoFeiSumReward", "m_nXiaoFeiSumSize", "limit%d", "reward%d"),
])

# BUY_PET_GIFT (index 23)
section("FAT_BUY_PET_GIFT", "BUY_PET_GIFT", 23, [])

# DA_TI (index 24)
section("FAT_DA_TI", "DA_TI", 24, [
    ("int", "m_nDaTiRankSize", "size"),
    ("rank_items", "m_vDaTiRankMail", "m_vDaTiRankReward", "m_nDaTiRankSize", "rank_mail%d", "rank_reward%d"),
])

# DAILY_LIMIT_SHOP_2 (index 25)
section("FAT_DAILY_LIMIT_SHOP_2", "DAILY_LIMIT_SHOP_2", 25, [
    ("int", "m_nDailyLimitShop2Size", "size"),
    ("shop_goods", "m_vDailyLimitShop2Goods", "m_nDailyLimitShop2Size", "goods%d"),
    ("int_array_simple", "m_vDailyLimitShop2Broadcast", "m_nDailyLimitShop2Size", "broadcast%d"),
])

# EQUIP_UPSTAR_BACK (index 26)
section("FAT_EQUIP_UPSTAR_BACK", "EQUIP_UPSTAR_BACK", 26, [
    ("int", "m_nEquipUpStarBackId", "id"),
    ("int", "m_nNeedValue", "need_value"),
])

# RECHARGE_DRAW (index 27)
section("FAT_RECHARGE_DRAW", "RECHARGE_DRAW", 27, [
    ("int", "m_nRechargeDrawSize", "size"),
    ("int", "m_nRechargeDrawValue", "need_value"),
    ("reward_items", "m_vScoreLimit", "m_vRechargeSumBroadcast", "m_nRechargeDrawSize", "limit%d", "broadcast%d"),
    ("reward_items_extra", "m_vBossScoreReward", "m_nRechargeDrawSize", "reward%d"),
])

# BUY_GIFT (index 28)
section("FAT_BUY_GIFT", "BUY_GIFT", 28, [
    ("int", "m_nBuyGiftSize", "size"),
    ("int_array_simple", "m_vBuyGiftPrice", "m_nBuyGiftSize", "price%d"),
    ("int_array_simple", "m_vBuyGiftBroadcast", "m_nBuyGiftSize", "broadcast%d"),
    ("parse_item_array", "m_vBuyGiftItem", "m_nBuyGiftSize", "item%d"),
])

# RECHARGE_BACK (index 29)
section("FAT_RECHARGE_BACK", "RECHARGE_BACK", 29, [
    ("int", "m_nRechargeBackSize", "size"),
    ("int_array_simple", "m_vRechargeBackLimit", "m_nRechargeBackSize", "limit%d"),
    ("int_array_simple", "m_vRechargeBackValue", "m_nRechargeBackSize", "value%d"),
])

# BOSS_SCORE (index 30)
section("FAT_BOSS_SCORE", "BOSS_SCORE", 30, [
    ("int", "m_nScoreSize", "size"),
    ("reward_items", "m_vScoreLimit", "m_vGetBossScoreMail", "m_nScoreSize", "limit%d", "mail%d"),
])

# PET_ILLUSION_ITEM (index 31)
section("FAT_PET_ILLUSION_ITEM", "PET_ILLUSION_ITEM", 31, [
    ("int", "m_nPetIllusionItemSize", "size"),
    ("reward_items", "m_vPetIllusionItemLimit", "m_vPetIllusionItemReward", "m_nPetIllusionItemSize", "limit%d", "reward%d"),
])

# RECHARGE_SUM_RANK (index 32)
section("FAT_RECHARGE_SUM_RANK", "RECHARGE_SUM_RANK", 32, [
    ("int", "m_nRechargeSumRankSize", "size"),
    ("rank_items", "m_vRechargeSumRankMail", "m_vRechargeSumRankReward", "m_nRechargeSumRankSize", "rank_mail%d", "rank_reward%d"),
])

# CROSS_RECHARGE_SUM_RANK (index 33)
section("FAT_CROSS_RECHARGE_SUM_RANK", "CROSS_RECHARGE_SUM_RANK", 33, [
    ("int", "m_nCrossRechargeSumRankSize", "size"),
    ("int_array_simple", "m_vCrossRechargeSumRankLimit", "m_nCrossRechargeSumRankSize", "limit%d"),
])

# CROSS_XIAO_FEI_SUM_RANK (index 34)
section("FAT_CROSS_XIAO_FEI_SUM_RANK", "CROSS_XIAO_FEI_SUM_RANK", 34, [
    ("int", "m_nCrossXiaoFeiSumRankSize", "size"),
    ("int_array_simple", "m_vCrossXiaoFeiSumRankLimit", "m_nCrossXiaoFeiSumRankSize", "limit%d"),
])

# PET_EQUIP_CHOU_JIANG (index 35)
section("FAT_PET_EQUIP_CHOU_JIANG", "PET_EQUIP_CHOU_JIANG", 35, [])

# CROSS_CHOU_JIANG_RANK (index 36)
section("FAT_CROSS_CHOU_JIANG_RANK", "CROSS_CHOU_JIANG_RANK", 36, [
    ("int", "m_nCrossChouJiangRankSize", "size"),
    ("int_array_simple", "m_vCrossChouJiangRankLimit", "m_nCrossChouJiangRankSize", "limit%d"),
])

# EQUIP_QING_YI (index 37)
section("FAT_EQUIP_QING_YI", "QING_YI_PEI", 37, [
    ("int", "m_nEquipQingYiSize", "size"),
    ("reward_items", "m_vEquipQingYiLimit", "m_vEquipQingYiReward", "m_nEquipQingYiSize", "limit%d", "reward%d"),
])

# FRIEND_QING_YI (index 38)
section("FAT_FRIEND_QING_YI", "FRIEND_QING_YI", 38, [
    ("int", "m_nFriendQingYiSize", "size"),
    ("reward_items", "m_vFriendQingYiLimit", "m_vFriendQingYiReward", "m_nFriendQingYiSize", "limit%d", "reward%d"),
])

# SCORE_SHOP (index 39)
section("FAT_SCORE_SHOP", "SCORE_SHOP", 39, [])

# BOSS_SCORE_RANK (index 40)
section("FAT_BOSS_SCORE_RANK", "BOSS_SCORE_RANK", 40, [
    ("int", "m_nBossScoreRankSize", "size"),
    ("int", "m_nBossScoreRate", "rate"),
    ("rank_items", "m_vBossScoreRankMail", "m_vBossScoreRankReward", "m_nBossScoreRankSize", "rank_mail%d", "rank_reward%d"),
])

# BOSS_SCORE_DRAW (index 41)
section("FAT_BOSS_SCORE_DRAW", "BOSS_SCORE_DRAW", 41, [
    ("int", "m_nRewardSize", "size"),
    ("reward_items", "m_vBossScoreiLimit", "m_vBossScoreDrawReward", "m_nRewardSize", "limit%d", "reward%d"),
])

# GOU_WU_CHE (index 42)
section("FAT_GOU_WU_CHE", "GOU_WU_CHE", 42, [
    ("int", "m_nGouWuCheSize", "size"),
    ("parse_item_array", "m_vGouWuCheItem", "m_nGouWuCheSize", "item%d"),
    ("int_array_simple", "m_vGouWuCheGiftPrice", "m_nGouWuCheSize", "price%d"),
])

# ================================================================
# CODE GENERATION
# ================================================================

def gen_int_field(section_name, field):
    member, key = field[1], field[2]
    return f"    {member} = ini.getIntValue(\"{section_name}\", \"{key}\");"

def gen_str_to_member(section_name, field):
    member, key = field[1], field[2]
    return f"    {member} = Answer::DayTime::StringToIntTime(ini.getStrValue(\"{section_name}\", \"{key}\"));"

def gen_int_array(section_name, field):
    vec_member, count_member, key_pattern = field[1], field[2], field[3]
    lines = []
    lines.append(f"    {vec_member}.resize({count_member});")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append(f"        char szCol[64] = {{0}};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{key_pattern}\", i + 1);")
    lines.append(f"        {vec_member}[i] = CItemHelper::parseItemVectorString(ini.getStrValue(\"{section_name}\", szCol));")
    lines.append("    }")
    return lines

def gen_int_array_simple(section_name, field):
    vec_member, count_member, key_pattern = field[1], field[2], field[3]
    lines = []
    lines.append(f"    {vec_member}.resize({count_member}, 0);")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append(f"        char szCol[64] = {{0}};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{key_pattern}\", i + 1);")
    lines.append(f"        {vec_member}[i] = ini.getIntValue(\"{section_name}\", szCol);")
    lines.append("    }")
    return lines

def gen_parse_item_vec(section_name, field):
    member, key = field[1], field[2]
    lines = []
    lines.append("    {")
    lines.append(f"        std::string strItem = ini.getStrValue(\"{section_name}\", \"{key}\");")
    lines.append(f"        {member} = CItemHelper::parseItemVectorString(strItem);")
    lines.append("    }")
    return lines

def gen_parse_item_array(section_name, field):
    vec_member, count_member, key_pattern = field[1], field[2], field[3]
    lines = []
    lines.append(f"    {vec_member}.resize({count_member});")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append(f"        char szCol[64] = {{0}};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{key_pattern}\", i + 1);")
    lines.append(f"        {vec_member}[i] = CItemHelper::parseItemVectorString(ini.getStrValue(\"{section_name}\", szCol));")
    lines.append("    }")
    return lines

def gen_reward_items(section_name, field):
    limit_vec, mail_vec, count_member, limit_key, mail_key = field[1], field[2], field[3], field[4], field[5]
    lines = []
    lines.append(f"    {limit_vec}.resize({count_member}, 0);")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append("        char szCol[64] = {0};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{limit_key}\", i + 1);")
    lines.append(f"        {limit_vec}[i] = ini.getIntValue(\"{section_name}\", szCol);")
    lines.append("    }")
    return lines

def gen_reward_items_extra(section_name, field):
    vec_member, count_member, key_pattern = field[1], field[2], field[3]
    lines = []
    lines.append(f"    {vec_member}.resize({count_member});")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append("        char szCol[64] = {0};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{key_pattern}\", i + 1);")
    lines.append(f"        {vec_member}[i] = CItemHelper::parseItemVectorString(ini.getStrValue(\"{section_name}\", szCol));")
    lines.append("    }")
    return lines

def gen_rank_items(section_name, field):
    mail_vec, reward_vec, count_member, mail_key, reward_key = field[1], field[2], field[3], field[4], field[5]
    lines = []
    lines.append(f"    {mail_vec}.resize({count_member}, 0);")
    lines.append(f"    {reward_vec}.resize({count_member});")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append("        char szCol[64] = {0};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{mail_key}\", i + 1);")
    lines.append(f"        {mail_vec}[i] = ini.getIntValue(\"{section_name}\", szCol);")
    lines.append("")
    lines.append("        bzero(szCol, sizeof(szCol));")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{reward_key}\", i + 1);")
    lines.append(f"        {reward_vec}[i] = CItemHelper::parseItemVectorString(ini.getStrValue(\"{section_name}\", szCol));")
    lines.append("    }")
    return lines

def gen_time_area_array(section_name, field):
    vec_member, count_member, start_key, end_key = field[1], field[2], field[3], field[4]
    lines = []
    lines.append(f"    int32_t nCount = ini.getIntValue(\"{section_name}\", \"{count_member}\");")
    lines.append(f"    {vec_member}.resize(nCount, TimeArea());")
    lines.append(f"    for (int32_t i = 0; i < nCount; ++i)")
    lines.append("    {")
    lines.append("        char szCol[64] = {0};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{start_key}\", i + 1);")
    lines.append(f"        {vec_member}[i].nStartTime = ini.getIntValue(\"{section_name}\", szCol);")
    lines.append("")
    lines.append("        bzero(szCol, sizeof(szCol));")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{end_key}\", i + 1);")
    lines.append(f"        {vec_member}[i].nEndTime = ini.getIntValue(\"{section_name}\", szCol);")
    lines.append("    }")
    return lines

def gen_shop_goods(section_name, field):
    vec_member, count_member, key_pattern = field[1], field[2], field[3]
    lines = []
    lines.append(f"    {vec_member}.resize({count_member});")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append("        char szCol[64] = {0};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{key_pattern}\", i + 1);")
    lines.append(f"        {vec_member}[i] = CItemHelper::parseShopGoodsString(ini.getStrValue(\"{section_name}\", szCol));")
    lines.append("    }")
    return lines

def gen_parse_item_data(section_name, field):
    member, key = field[1], field[2]
    lines = []
    lines.append("    {")
    lines.append(f"        std::string strItem = ini.getStrValue(\"{section_name}\", \"{key}\");")
    lines.append(f"        ItemData itemData = CItemHelper::parseItemDataString(strItem);")
    lines.append(f"        {member}.m_nId = itemData.m_nId;")
    lines.append(f"        {member}.m_nClass = itemData.m_nClass;")
    lines.append(f"        {member}.m_nCount = itemData.m_nCount;")
    lines.append("    }")
    return lines

def gen_int_array_item(section_name, field):
    """Special for LAND/SUMM which loads items from gift1..giftN"""
    vec_member, count_member, key_pattern = field[1], field[2], field[3]
    lines = []
    lines.append(f"    {vec_member}.resize({count_member});")
    lines.append(f"    for (int32_t i = 0; i < {count_member}; ++i)")
    lines.append("    {")
    lines.append("        char szCol[64] = {0};")
    lines.append(f"        snprintf(szCol, sizeof(szCol), \"{key_pattern}\", i + 1);")
    lines.append(f"        {vec_member}[i] = CItemHelper::parseItemVectorString(ini.getStrValue(\"{section_name}\", szCol));")
    lines.append("    }")
    return lines

# ================================================================
# Generate the complete code
# ================================================================

def gen_section(fat_type, section_name, index, fields):
    lines = []
    lines.append(f"    if (isOpen(FESTIVAL_ACTIVITY_TYPE::{fat_type}))")
    lines.append("    {")
    lines.append(f"        m_vStartDay[{index}] = ini.getIntValue(\"{section_name}\", \"start_day\");")
    lines.append(f"        m_vEndDay[{index}] = ini.getIntValue(\"{section_name}\", \"end_day\");")
    
    for field in fields:
        field_type = field[0]
        if field_type == "int":
            lines.append("        " + gen_int_field(section_name, field))
        elif field_type == "str_to_member":
            for l in gen_str_to_member(section_name, field):
                lines.append("        " + l)
        elif field_type == "int_array":
            for l in gen_int_array(section_name, field):
                lines.append("        " + l)
        elif field_type == "int_array_simple":
            for l in gen_int_array_simple(section_name, field):
                lines.append("        " + l)
        elif field_type == "parse_item_vec":
            for l in gen_parse_item_vec(section_name, field):
                lines.append("        " + l)
        elif field_type == "parse_item_array":
            for l in gen_parse_item_array(section_name, field):
                lines.append("        " + l)
        elif field_type == "reward_items":
            for l in gen_reward_items(section_name, field):
                lines.append("        " + l)
        elif field_type == "reward_items_extra":
            for l in gen_reward_items_extra(section_name, field):
                lines.append("        " + l)
        elif field_type == "rank_items":
            for l in gen_rank_items(section_name, field):
                lines.append("        " + l)
        elif field_type == "time_area_array":
            for l in gen_time_area_array(section_name, field):
                lines.append("        " + l)
        elif field_type == "shop_goods":
            for l in gen_shop_goods(section_name, field):
                lines.append("        " + l)
        elif field_type == "parse_item_data":
            for l in gen_parse_item_data(section_name, field):
                lines.append("        " + l)
        elif field_type == "int_array_item":
            for l in gen_int_array_item(section_name, field):
                lines.append("        " + l)
    
    lines.append("    }")
    return lines


# Generate the complete initCfgData()
result = []
result.append("void CFestivalDoubleEleven::initCfgData()")
result.append("{")
result.append("    Answer::Inifile ini;")
result.append("    ini.parse(\"./ServerConfig/Tables/FestivalDoubleEleven.cfg\");")
result.append("")
result.append("    // CONFIG section")
result.append("    m_nHotSign = ini.getIntValue(\"CONFIG\", \"hot_sign\");")
result.append("    m_nVersion = ini.getIntValue(\"CONFIG\", \"version\");")
result.append("    m_nStartDay = Answer::DayTime::StringToIntTime(ini.getStrValue(\"CONFIG\", \"start_time\"));")
result.append("    m_nEndDay = ini.getIntValue(\"CONFIG\", \"end_day\");")
result.append("    m_nIcon = ini.getIntValue(\"CONFIG\", \"icon\");")
result.append("    m_nIconHideDay = ini.getIntValue(\"CONFIG\", \"icon_hide_day\");")
result.append("    m_nGameStartDay = ini.getIntValue(\"CONFIG\", \"game_start_day\");")
result.append("    m_nUniteStartDay = ini.getIntValue(\"CONFIG\", \"unite_start_day\");")
result.append("    m_nDropGroup = ini.getIntValue(\"CONFIG\", \"drop_group\");")
result.append("")
result.append("    initOpenList(ini.getStrValue(\"CONFIG\", \"open\"));")
result.append("")
result.append("    m_nDay = (Answer::DayTime::dayzero(Answer::DayTime::now()) - Answer::DayTime::dayzero(m_nStartDay)) / 86400;")
result.append("")
result.append("    // Sub-activity sections")
result.append("")

for fat_type, section_name, index, fields in SECTIONS:
    for l in gen_section(fat_type, section_name, index, fields):
        result.append(l)
    result.append("")

result.append("}")

output = "\n".join(result)
print(output)

# Save to file
os.makedirs('gameserver/generated', exist_ok=True)
with open('gameserver/generated/init_cfgdata.cpp', 'w') as f:
    f.write(output)

print(f"\n\nGenerated {len(result)} lines")
print(f"Saved to gameserver/generated/init_cfgdata.cpp")
