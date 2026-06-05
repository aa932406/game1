void CFestivalDoubleEleven::initCfgData()
{
    Answer::Inifile ini;
    ini.parse("./ServerConfig/Tables/FestivalDoubleEleven.cfg");

    // CONFIG section
    m_nHotSign = ini.getIntValue("CONFIG", "hot_sign");
    m_nVersion = ini.getIntValue("CONFIG", "version");
    m_nStartDay = Answer::DayTime::StringToIntTime(ini.getStrValue("CONFIG", "start_time"));
    m_nEndDay = ini.getIntValue("CONFIG", "end_day");
    m_nIcon = ini.getIntValue("CONFIG", "icon");
    m_nIconHideDay = ini.getIntValue("CONFIG", "icon_hide_day");
    m_nGameStartDay = ini.getIntValue("CONFIG", "game_start_day");
    m_nUniteStartDay = ini.getIntValue("CONFIG", "unite_start_day");
    m_nDropGroup = ini.getIntValue("CONFIG", "drop_group");

    initOpenList(ini.getStrValue("CONFIG", "open"));

    m_nDay = (Answer::DayTime::dayzero(Answer::DayTime::now()) - Answer::DayTime::dayzero(m_nStartDay)) / 86400;

    // Sub-activity sections

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_LAND))
    {
        m_vStartDay[1] = ini.getIntValue("LAND", "start_day");
        m_vEndDay[1] = ini.getIntValue("LAND", "end_day");
            m_vLandGift.resize(m_nEndDay);
            for (int32_t i = 0; i < m_nEndDay; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "gift%d", i + 1);
                m_vLandGift[i] = CItemHelper::parseItemVectorString(ini.getStrValue("LAND", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE))
    {
        m_vStartDay[2] = ini.getIntValue("DAILY_RECHARGE", "start_day");
        m_vEndDay[2] = ini.getIntValue("DAILY_RECHARGE", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DRAW))
    {
        m_vStartDay[3] = ini.getIntValue("LUCKY_DRAW", "start_day");
        m_vEndDay[3] = ini.getIntValue("LUCKY_DRAW", "end_day");
            m_nDrawLoopTimes = ini.getIntValue("LUCKY_DRAW", "loop_times");
            {
                std::string strItem = ini.getStrValue("LUCKY_DRAW", "loop_reward");
                m_vDrawLoopReward = CItemHelper::parseItemVectorString(strItem);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK))
    {
        m_vStartDay[4] = ini.getIntValue("LUCKY_DRAW_RANK", "start_day");
        m_vEndDay[4] = ini.getIntValue("LUCKY_DRAW_RANK", "end_day");
            m_nDrawRankSize = ini.getIntValue("LUCKY_DRAW_RANK", "rank_size");
            m_nDrawRankLimit = ini.getIntValue("LUCKY_DRAW_RANK", "rank_limit");
            m_vDrawRankMail.resize(m_nDrawRankSize, 0);
            m_vDrawRankReward.resize(m_nDrawRankSize);
            for (int32_t i = 0; i < m_nDrawRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
                m_vDrawRankMail[i] = ini.getIntValue("LUCKY_DRAW_RANK", szCol);
        
                bzero(szCol, sizeof(szCol));
                snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
                m_vDrawRankReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("LUCKY_DRAW_RANK", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_EXCHANGE))
    {
        m_vStartDay[5] = ini.getIntValue("EXCHANGE", "start_day");
        m_vEndDay[5] = ini.getIntValue("EXCHANGE", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_WORLD_BOSS))
    {
        m_vStartDay[6] = ini.getIntValue("WORLD_BOSS", "start_day");
        m_vEndDay[6] = ini.getIntValue("WORLD_BOSS", "end_day");
            m_nWorldBossIcon = ini.getIntValue("WORLD_BOSS", "icon");
            m_nWorldBossStartBroadcast = ini.getIntValue("WORLD_BOSS", "start_broadcast");
            m_nWorldBossEndBroadcast = ini.getIntValue("WORLD_BOSS", "end_broadcast");
            m_nWorldBossKillBroadcast = ini.getIntValue("WORLD_BOSS", "kill_broadcast");
            int32_t nCount = ini.getIntValue("WORLD_BOSS", "count");
            m_vWorldBossMinute.resize(nCount, TimeArea());
            for (int32_t i = 0; i < nCount; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "start_minute%d", i + 1);
                m_vWorldBossMinute[i].nStartTime = ini.getIntValue("WORLD_BOSS", szCol);
        
                bzero(szCol, sizeof(szCol));
                snprintf(szCol, sizeof(szCol), "end_minute%d", i + 1);
                m_vWorldBossMinute[i].nEndTime = ini.getIntValue("WORLD_BOSS", szCol);
            }
            m_MapId = ini.getIntValue("WORLD_BOSS", "mapid");
            m_X = ini.getIntValue("WORLD_BOSS", "x");
            m_Y = ini.getIntValue("WORLD_BOSS", "y");
            m_Mid = ini.getIntValue("WORLD_BOSS", "mid");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM))
    {
        m_vStartDay[7] = ini.getIntValue("HUO_YUE_DU_SUM", "start_day");
        m_vEndDay[7] = ini.getIntValue("HUO_YUE_DU_SUM", "end_day");
            m_nHuoYueDuSumSize = ini.getIntValue("HUO_YUE_DU_SUM", "size");
            m_vHuoYueDuSumLimit.resize(m_nHuoYueDuSumSize, 0);
            for (int32_t i = 0; i < m_nHuoYueDuSumSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "value%d", i + 1);
                m_vHuoYueDuSumLimit[i] = ini.getIntValue("HUO_YUE_DU_SUM", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP))
    {
        m_vStartDay[8] = ini.getIntValue("DAILY_LIMIT_SHOP", "start_day");
        m_vEndDay[8] = ini.getIntValue("DAILY_LIMIT_SHOP", "end_day");
            {
                std::string strItem = ini.getStrValue("DAILY_LIMIT_SHOP", "item");
                m_vDailyLimitShopItem = CItemHelper::parseItemVectorString(strItem);
            }
            m_nDailyLimitShopCostType = ini.getIntValue("DAILY_LIMIT_SHOP", "cost_type");
            m_nDailyLimitShopCostValue = ini.getIntValue("DAILY_LIMIT_SHOP", "cost_value");
            m_nDailyLimitShopLimit = ini.getIntValue("DAILY_LIMIT_SHOP", "limit");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM))
    {
        m_vStartDay[9] = ini.getIntValue("LAND_SUM", "start_day");
        m_vEndDay[9] = ini.getIntValue("LAND_SUM", "end_day");
            m_vLandSumGift.resize(m_nEndDay);
            for (int32_t i = 0; i < m_nEndDay; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "gift%d", i + 1);
                m_vLandSumGift[i] = CItemHelper::parseItemVectorString(ini.getStrValue("LAND_SUM", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME))
    {
        m_vStartDay[10] = ini.getIntValue("DAILY_ONLINE", "start_day");
        m_vEndDay[10] = ini.getIntValue("DAILY_ONLINE", "end_day");
            m_nOnlineStartMinute = ini.getIntValue("DAILY_ONLINE", "start_time");
            m_nOnlineEndMinute = ini.getIntValue("DAILY_ONLINE", "end_time");
            m_nOnlineTimeArea = ini.getIntValue("DAILY_ONLINE", "dis_time");
            {
                std::string strItem = ini.getStrValue("DAILY_ONLINE", "reward");
                m_vOnlineReward = CItemHelper::parseItemVectorString(strItem);
            }
            m_nMaxCount = ini.getIntValue("DAILY_ONLINE", "max_count");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BEST_WISH))
    {
        m_vStartDay[11] = ini.getIntValue("BEST_WISH", "start_day");
        m_vEndDay[11] = ini.getIntValue("BEST_WISH", "end_day");
            m_nWishRecharge = ini.getIntValue("BEST_WISH", "recharge");
            {
                std::string strItem = ini.getStrValue("BEST_WISH", "reward");
                m_vWishReward = CItemHelper::parseItemVectorString(strItem);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK))
    {
        m_vStartDay[12] = ini.getIntValue("XIAO_FEI_RANK", "start_day");
        m_vEndDay[12] = ini.getIntValue("XIAO_FEI_RANK", "end_day");
            m_nXiaoFeiRankSize = ini.getIntValue("XIAO_FEI_RANK", "size");
            m_vXiaoFeiRankLimit.resize(m_nXiaoFeiRankSize, 0);
            for (int32_t i = 0; i < m_nXiaoFeiRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vXiaoFeiRankLimit[i] = ini.getIntValue("XIAO_FEI_RANK", szCol);
            }
            m_vXiaoFeiRankReward.resize(m_nXiaoFeiRankSize);
            for (int32_t i = 0; i < m_nXiaoFeiRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
                m_vXiaoFeiRankReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("XIAO_FEI_RANK", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW))
    {
        m_vStartDay[13] = ini.getIntValue("XIAO_FEI_DRAW", "start_day");
        m_vEndDay[13] = ini.getIntValue("XIAO_FEI_DRAW", "end_day");
            m_nXiaoFeiDrawSize = ini.getIntValue("XIAO_FEI_DRAW", "size");
            m_nXiaoFeiDrawValue = ini.getIntValue("XIAO_FEI_DRAW", "need_value");
            m_vScoreLimit.resize(m_nXiaoFeiDrawSize, 0);
            for (int32_t i = 0; i < m_nXiaoFeiDrawSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vScoreLimit[i] = ini.getIntValue("XIAO_FEI_DRAW", szCol);
            }
            m_vBossScoreReward.resize(m_nXiaoFeiDrawSize);
            for (int32_t i = 0; i < m_nXiaoFeiDrawSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
                m_vBossScoreReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("XIAO_FEI_DRAW", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE))
    {
        m_vStartDay[14] = ini.getIntValue("MO_YU_SHI_JIE", "start_day");
        m_vEndDay[14] = ini.getIntValue("MO_YU_SHI_JIE", "end_day");
            m_nMoYuShiJieDropSize = ini.getIntValue("MO_YU_SHI_JIE", "drop_size");
            m_vMoYuShiJieDrop.resize(m_nMoYuShiJieDropSize, 0);
            for (int32_t i = 0; i < m_nMoYuShiJieDropSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "drop%d", i + 1);
                m_vMoYuShiJieDrop[i] = ini.getIntValue("MO_YU_SHI_JIE", szCol);
            }
            m_nChouJiangCount = ini.getIntValue("MO_YU_SHI_JIE", "count");
            m_nChouJiangType = ini.getIntValue("MO_YU_SHI_JIE", "chou_jiang_type");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE_2))
    {
        m_vStartDay[15] = ini.getIntValue("DAILY_RECHARGE_2", "start_day");
        m_vEndDay[15] = ini.getIntValue("DAILY_RECHARGE_2", "end_day");
            m_nDailyRechargeDrawSize = ini.getIntValue("DAILY_RECHARGE_2", "size");
            m_nDailyRechargeDrawLimit = ini.getIntValue("DAILY_RECHARGE_2", "limit");
            m_vDailyRechargeLimit.resize(m_nDailyRechargeDrawSize, 0);
            for (int32_t i = 0; i < m_nDailyRechargeDrawSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vDailyRechargeLimit[i] = ini.getIntValue("DAILY_RECHARGE_2", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK))
    {
        m_vStartDay[16] = ini.getIntValue("XIAO_FEI_SUM_RANK", "start_day");
        m_vEndDay[16] = ini.getIntValue("XIAO_FEI_SUM_RANK", "end_day");
            m_nXiaoFeiSumRankSize = ini.getIntValue("XIAO_FEI_SUM_RANK", "size");
            m_nXiaoFeiSumRankLimit = ini.getIntValue("XIAO_FEI_SUM_RANK", "limit");
            m_vXiaoFeiSumRankMail.resize(m_nXiaoFeiSumRankSize, 0);
            m_vXiaoFeiSumRankReward.resize(m_nXiaoFeiSumRankSize);
            for (int32_t i = 0; i < m_nXiaoFeiSumRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "mail%d", i + 1);
                m_vXiaoFeiSumRankMail[i] = ini.getIntValue("XIAO_FEI_SUM_RANK", szCol);
        
                bzero(szCol, sizeof(szCol));
                snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
                m_vXiaoFeiSumRankReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("XIAO_FEI_SUM_RANK", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_GIFT_SHOP))
    {
        m_vStartDay[17] = ini.getIntValue("GIFT_SHOP", "start_day");
        m_vEndDay[17] = ini.getIntValue("GIFT_SHOP", "end_day");
            m_nGiftShopSize = ini.getIntValue("GIFT_SHOP", "size");
            m_vGiftShopGoods.resize(m_nGiftShopSize);
            for (int32_t i = 0; i < m_nGiftShopSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
                m_vGiftShopGoods[i] = CItemHelper::parseShopGoodsString(ini.getStrValue("GIFT_SHOP", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG))
    {
        m_vStartDay[18] = ini.getIntValue("CHOU_JIANG", "start_day");
        m_vEndDay[18] = ini.getIntValue("CHOU_JIANG", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK))
    {
        m_vStartDay[19] = ini.getIntValue("FA_BAO_BACK", "start_day");
        m_vEndDay[19] = ini.getIntValue("FA_BAO_BACK", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP))
    {
        m_vStartDay[20] = ini.getIntValue("MYSTERY_SHOP", "start_day");
        m_vEndDay[20] = ini.getIntValue("MYSTERY_SHOP", "end_day");
            m_nMysteryShopRefreshBroad = ini.getIntValue("MYSTERY_SHOP", "refresh_broadcast");
            {
                std::string strItem = ini.getStrValue("MYSTERY_SHOP", "refresh_cost");
                ItemData itemData = CItemHelper::parseItemDataString(strItem);
                m_sMysteryShopRefreshCost.m_nId = itemData.m_nId;
                m_sMysteryShopRefreshCost.m_nClass = itemData.m_nClass;
                m_sMysteryShopRefreshCost.m_nCount = itemData.m_nCount;
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_GIFT))
    {
        m_vStartDay[21] = ini.getIntValue("RECHARGE_SUM_GIFT", "start_day");
        m_vEndDay[21] = ini.getIntValue("RECHARGE_SUM_GIFT", "end_day");
            m_nRechargeSumSize = ini.getIntValue("RECHARGE_SUM_GIFT", "size");
            m_vRechargeSumLimit.resize(m_nRechargeSumSize, 0);
            for (int32_t i = 0; i < m_nRechargeSumSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vRechargeSumLimit[i] = ini.getIntValue("RECHARGE_SUM_GIFT", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT))
    {
        m_vStartDay[22] = ini.getIntValue("XIAO_FEI_SUM_GIFT", "start_day");
        m_vEndDay[22] = ini.getIntValue("XIAO_FEI_SUM_GIFT", "end_day");
            m_nXiaoFeiSumSize = ini.getIntValue("XIAO_FEI_SUM_GIFT", "size");
            m_vXiaoFeiSumLimit.resize(m_nXiaoFeiSumSize, 0);
            for (int32_t i = 0; i < m_nXiaoFeiSumSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vXiaoFeiSumLimit[i] = ini.getIntValue("XIAO_FEI_SUM_GIFT", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BUY_PET_GIFT))
    {
        m_vStartDay[23] = ini.getIntValue("BUY_PET_GIFT", "start_day");
        m_vEndDay[23] = ini.getIntValue("BUY_PET_GIFT", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI))
    {
        m_vStartDay[24] = ini.getIntValue("DA_TI", "start_day");
        m_vEndDay[24] = ini.getIntValue("DA_TI", "end_day");
            m_nDaTiRankSize = ini.getIntValue("DA_TI", "size");
            m_vDaTiRankMail.resize(m_nDaTiRankSize, 0);
            m_vDaTiRankReward.resize(m_nDaTiRankSize);
            for (int32_t i = 0; i < m_nDaTiRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
                m_vDaTiRankMail[i] = ini.getIntValue("DA_TI", szCol);
        
                bzero(szCol, sizeof(szCol));
                snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
                m_vDaTiRankReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("DA_TI", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP_2))
    {
        m_vStartDay[25] = ini.getIntValue("DAILY_LIMIT_SHOP_2", "start_day");
        m_vEndDay[25] = ini.getIntValue("DAILY_LIMIT_SHOP_2", "end_day");
            m_nDailyLimitShop2Size = ini.getIntValue("DAILY_LIMIT_SHOP_2", "size");
            m_vDailyLimitShop2Goods.resize(m_nDailyLimitShop2Size);
            for (int32_t i = 0; i < m_nDailyLimitShop2Size; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
                m_vDailyLimitShop2Goods[i] = CItemHelper::parseShopGoodsString(ini.getStrValue("DAILY_LIMIT_SHOP_2", szCol));
            }
            m_vDailyLimitShop2Broadcast.resize(m_nDailyLimitShop2Size, 0);
            for (int32_t i = 0; i < m_nDailyLimitShop2Size; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
                m_vDailyLimitShop2Broadcast[i] = ini.getIntValue("DAILY_LIMIT_SHOP_2", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK))
    {
        m_vStartDay[26] = ini.getIntValue("EQUIP_UPSTAR_BACK", "start_day");
        m_vEndDay[26] = ini.getIntValue("EQUIP_UPSTAR_BACK", "end_day");
            m_nEquipUpStarBackId = ini.getIntValue("EQUIP_UPSTAR_BACK", "id");
            m_nNeedValue = ini.getIntValue("EQUIP_UPSTAR_BACK", "need_value");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_DRAW))
    {
        m_vStartDay[27] = ini.getIntValue("RECHARGE_DRAW", "start_day");
        m_vEndDay[27] = ini.getIntValue("RECHARGE_DRAW", "end_day");
            m_nRechargeDrawSize = ini.getIntValue("RECHARGE_DRAW", "size");
            m_nRechargeDrawValue = ini.getIntValue("RECHARGE_DRAW", "need_value");
            m_vScoreLimit.resize(m_nRechargeDrawSize, 0);
            for (int32_t i = 0; i < m_nRechargeDrawSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vScoreLimit[i] = ini.getIntValue("RECHARGE_DRAW", szCol);
            }
            m_vBossScoreReward.resize(m_nRechargeDrawSize);
            for (int32_t i = 0; i < m_nRechargeDrawSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
                m_vBossScoreReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("RECHARGE_DRAW", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BUY_GIFT))
    {
        m_vStartDay[28] = ini.getIntValue("BUY_GIFT", "start_day");
        m_vEndDay[28] = ini.getIntValue("BUY_GIFT", "end_day");
            m_nBuyGiftSize = ini.getIntValue("BUY_GIFT", "size");
            m_vBuyGiftPrice.resize(m_nBuyGiftSize, 0);
            for (int32_t i = 0; i < m_nBuyGiftSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "price%d", i + 1);
                m_vBuyGiftPrice[i] = ini.getIntValue("BUY_GIFT", szCol);
            }
            m_vBuyGiftBroadcast.resize(m_nBuyGiftSize, 0);
            for (int32_t i = 0; i < m_nBuyGiftSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
                m_vBuyGiftBroadcast[i] = ini.getIntValue("BUY_GIFT", szCol);
            }
            m_vBuyGiftItem.resize(m_nBuyGiftSize);
            for (int32_t i = 0; i < m_nBuyGiftSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "item%d", i + 1);
                m_vBuyGiftItem[i] = CItemHelper::parseItemVectorString(ini.getStrValue("BUY_GIFT", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK))
    {
        m_vStartDay[29] = ini.getIntValue("RECHARGE_BACK", "start_day");
        m_vEndDay[29] = ini.getIntValue("RECHARGE_BACK", "end_day");
            m_nRechargeBackSize = ini.getIntValue("RECHARGE_BACK", "size");
            m_vRechargeBackLimit.resize(m_nRechargeBackSize, 0);
            for (int32_t i = 0; i < m_nRechargeBackSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vRechargeBackLimit[i] = ini.getIntValue("RECHARGE_BACK", szCol);
            }
            m_vRechargeBackValue.resize(m_nRechargeBackSize, 0);
            for (int32_t i = 0; i < m_nRechargeBackSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "value%d", i + 1);
                m_vRechargeBackValue[i] = ini.getIntValue("RECHARGE_BACK", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE))
    {
        m_vStartDay[30] = ini.getIntValue("BOSS_SCORE", "start_day");
        m_vEndDay[30] = ini.getIntValue("BOSS_SCORE", "end_day");
            m_nScoreSize = ini.getIntValue("BOSS_SCORE", "size");
            m_vScoreLimit.resize(m_nScoreSize, 0);
            for (int32_t i = 0; i < m_nScoreSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vScoreLimit[i] = ini.getIntValue("BOSS_SCORE", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM))
    {
        m_vStartDay[31] = ini.getIntValue("PET_ILLUSION_ITEM", "start_day");
        m_vEndDay[31] = ini.getIntValue("PET_ILLUSION_ITEM", "end_day");
            m_nPetIllusionItemSize = ini.getIntValue("PET_ILLUSION_ITEM", "size");
            m_vPetIllusionItemLimit.resize(m_nPetIllusionItemSize, 0);
            for (int32_t i = 0; i < m_nPetIllusionItemSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vPetIllusionItemLimit[i] = ini.getIntValue("PET_ILLUSION_ITEM", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK))
    {
        m_vStartDay[32] = ini.getIntValue("RECHARGE_SUM_RANK", "start_day");
        m_vEndDay[32] = ini.getIntValue("RECHARGE_SUM_RANK", "end_day");
            m_nRechargeSumRankSize = ini.getIntValue("RECHARGE_SUM_RANK", "size");
            m_vRechargeSumRankMail.resize(m_nRechargeSumRankSize, 0);
            m_vRechargeSumRankReward.resize(m_nRechargeSumRankSize);
            for (int32_t i = 0; i < m_nRechargeSumRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
                m_vRechargeSumRankMail[i] = ini.getIntValue("RECHARGE_SUM_RANK", szCol);
        
                bzero(szCol, sizeof(szCol));
                snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
                m_vRechargeSumRankReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("RECHARGE_SUM_RANK", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK))
    {
        m_vStartDay[33] = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", "start_day");
        m_vEndDay[33] = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", "end_day");
            m_nCrossRechargeSumRankSize = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", "size");
            m_vCrossRechargeSumRankLimit.resize(m_nCrossRechargeSumRankSize, 0);
            for (int32_t i = 0; i < m_nCrossRechargeSumRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vCrossRechargeSumRankLimit[i] = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK))
    {
        m_vStartDay[34] = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", "start_day");
        m_vEndDay[34] = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", "end_day");
            m_nCrossXiaoFeiSumRankSize = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", "size");
            m_vCrossXiaoFeiSumRankLimit.resize(m_nCrossXiaoFeiSumRankSize, 0);
            for (int32_t i = 0; i < m_nCrossXiaoFeiSumRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vCrossXiaoFeiSumRankLimit[i] = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_PET_EQUIP_CHOU_JIANG))
    {
        m_vStartDay[35] = ini.getIntValue("PET_EQUIP_CHOU_JIANG", "start_day");
        m_vEndDay[35] = ini.getIntValue("PET_EQUIP_CHOU_JIANG", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_CHOU_JIANG_RANK))
    {
        m_vStartDay[36] = ini.getIntValue("CROSS_CHOU_JIANG_RANK", "start_day");
        m_vEndDay[36] = ini.getIntValue("CROSS_CHOU_JIANG_RANK", "end_day");
            m_nCrossChouJiangRankSize = ini.getIntValue("CROSS_CHOU_JIANG_RANK", "size");
            m_vCrossChouJiangRankLimit.resize(m_nCrossChouJiangRankSize, 0);
            for (int32_t i = 0; i < m_nCrossChouJiangRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vCrossChouJiangRankLimit[i] = ini.getIntValue("CROSS_CHOU_JIANG_RANK", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_QING_YI))
    {
        m_vStartDay[37] = ini.getIntValue("QING_YI_PEI", "start_day");
        m_vEndDay[37] = ini.getIntValue("QING_YI_PEI", "end_day");
            m_nEquipQingYiSize = ini.getIntValue("QING_YI_PEI", "size");
            m_vEquipQingYiLimit.resize(m_nEquipQingYiSize, 0);
            for (int32_t i = 0; i < m_nEquipQingYiSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vEquipQingYiLimit[i] = ini.getIntValue("QING_YI_PEI", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI))
    {
        m_vStartDay[38] = ini.getIntValue("FRIEND_QING_YI", "start_day");
        m_vEndDay[38] = ini.getIntValue("FRIEND_QING_YI", "end_day");
            m_nFriendQingYiSize = ini.getIntValue("FRIEND_QING_YI", "size");
            m_vFriendQingYiLimit.resize(m_nFriendQingYiSize, 0);
            for (int32_t i = 0; i < m_nFriendQingYiSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vFriendQingYiLimit[i] = ini.getIntValue("FRIEND_QING_YI", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_SCORE_SHOP))
    {
        m_vStartDay[39] = ini.getIntValue("SCORE_SHOP", "start_day");
        m_vEndDay[39] = ini.getIntValue("SCORE_SHOP", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK))
    {
        m_vStartDay[40] = ini.getIntValue("BOSS_SCORE_RANK", "start_day");
        m_vEndDay[40] = ini.getIntValue("BOSS_SCORE_RANK", "end_day");
            m_nBossScoreRankSize = ini.getIntValue("BOSS_SCORE_RANK", "size");
            m_nBossScoreRate = ini.getIntValue("BOSS_SCORE_RANK", "rate");
            m_vBossScoreRankMail.resize(m_nBossScoreRankSize, 0);
            m_vBossScoreRankReward.resize(m_nBossScoreRankSize);
            for (int32_t i = 0; i < m_nBossScoreRankSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
                m_vBossScoreRankMail[i] = ini.getIntValue("BOSS_SCORE_RANK", szCol);
        
                bzero(szCol, sizeof(szCol));
                snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
                m_vBossScoreRankReward[i] = CItemHelper::parseItemVectorString(ini.getStrValue("BOSS_SCORE_RANK", szCol));
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW))
    {
        m_vStartDay[41] = ini.getIntValue("BOSS_SCORE_DRAW", "start_day");
        m_vEndDay[41] = ini.getIntValue("BOSS_SCORE_DRAW", "end_day");
            m_nRewardSize = ini.getIntValue("BOSS_SCORE_DRAW", "size");
            m_vBossScoreiLimit.resize(m_nRewardSize, 0);
            for (int32_t i = 0; i < m_nRewardSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
                m_vBossScoreiLimit[i] = ini.getIntValue("BOSS_SCORE_DRAW", szCol);
            }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_GOU_WU_CHE))
    {
        m_vStartDay[42] = ini.getIntValue("GOU_WU_CHE", "start_day");
        m_vEndDay[42] = ini.getIntValue("GOU_WU_CHE", "end_day");
            m_nGouWuCheSize = ini.getIntValue("GOU_WU_CHE", "size");
            m_vGouWuCheItem.resize(m_nGouWuCheSize);
            for (int32_t i = 0; i < m_nGouWuCheSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "item%d", i + 1);
                m_vGouWuCheItem[i] = CItemHelper::parseItemVectorString(ini.getStrValue("GOU_WU_CHE", szCol));
            }
            m_vGouWuCheGiftPrice.resize(m_nGouWuCheSize, 0);
            for (int32_t i = 0; i < m_nGouWuCheSize; ++i)
            {
                char szCol[64] = {0};
                snprintf(szCol, sizeof(szCol), "price%d", i + 1);
                m_vGouWuCheGiftPrice[i] = ini.getIntValue("GOU_WU_CHE", szCol);
            }
    }

}