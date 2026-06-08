# 反编译覆盖率分析与补全计划

## 分析方法

对比 `decompiled_backup/`（405个文件）与 `gameserver/` 当前代码，按文件体积计算覆盖率。
注意：反编译源是 IDA 伪代码，同功能代码量约为干净版的 2-3 倍，因此 50% 覆盖率可能实际已覆盖 80%+ 的功能逻辑。

## 总体数据

| 指标 | 数值 |
|------|------|
| 反编译源总量 | 6.5 MB |
| 当前代码总量 | 65.0 MB |
| 整体体积比率 | 1003% |
| 已完全覆盖(>=80%) | 177 个文件 |
| 未完全覆盖(<80%) | 113 个文件 |
| 无对应文件 | 36 个 |

---

## 一、缺口最大的文件（Top 20，按缺口体积排序）

| # | 反编译文件 | 当前文件 | 覆盖率 | 缺口 | 阶段 |
|---|-----------|---------|--------|------|------|
| 1 | Player.cpp (535K) | Player.cpp (61K) | 12% | ~474K | R0 |
| 2 | CFestivalDoubleEleven.cpp (459K) | FestivalDoubleEleven.cpp (92K) | 20% | ~367K | R1 |
| 3 | Dungeon.cpp (230K) | Dungeon.cpp (46K) | 20% | ~185K | R1 |
| 4 | COpenBeta.cpp (124K) | OpenBeta.cpp (37K) | 30% | ~87K | R2 |
| 5 | GameService.cpp (142K) | GameService.cpp (58K) | 41% | ~84K | R2 |
| 6 | Monster.cpp (153K) | Monster.cpp (32K) | 21% | ~121K | R1 |
| 7 | CExtEquip.cpp (213K) | Equip.cpp (111K) | 52% | ~102K | R3 |
| 8 | Map.cpp (145K) | Map.cpp (66K) | 45% | ~79K | R3 |
| 9 | CGoblin.cpp (102K) | Goblin.cpp (25K) | 25% | ~77K | R2 |
| 10 | CVplan.cpp (83K) | Vplan.cpp (21K) | 25% | ~63K | R2 |
| 11 | CActivityMap.cpp (77K) | ActivityMap.cpp (22K) | 29% | ~56K | R2 |
| 12 | CUniteServer.cpp (80K) | UniteServer.cpp (24K) | 31% | ~56K | R2 |
| 13 | CExtCharBag.cpp (128K) | Bag.cpp (73K) | 57% | ~55K | R3 |
| 14 | CExtCharSkill.cpp (95K) | CharSkill.cpp (41K) | 44% | ~53K | R3 |
| 15 | CExtCharFamily.cpp (84K) | CharFamily.cpp (33K) | 39% | ~51K | R3 |
| 16 | CMoneyRewardTask.cpp (87K) | MoneyRewardTask.cpp (36K) | 42% | ~51K | R3 |
| 17 | CZongHeYunYingHD.cpp (63K) | ZongHeYunYingHD.cpp (18K) | 29% | ~45K | R2 |
| 18 | CYunYingHD.cpp (76K) | YunYingHD.cpp (32K) | 42% | ~44K | R3 |
| 19 | CFestivalActivity.cpp (57K) | FestivalActivity.cpp (16K) | 28% | ~41K | R2 |
| 20 | DailyActivity.cpp (81K) | DailyActivity.cpp (41K) | 52% | ~39K | R3 |

---

## 二、无对应文件的模块（36个，按体积排序）

| # | 反编译文件 | 体积 | 建议目标文件 | 说明 |
|---|-----------|------|-------------|------|
| 1 | CExtCharTencent.cpp | 63K | CharTencent.cpp | 腾讯平台集成 |
| 2 | CXinMo.cpp | 53K | XinMo.cpp | 心魔系统 |
| 3 | CDaTingReward.cpp | 42K | CDaTingReward.cpp | 答题奖励(命名问题) |
| 4 | CGoblinData.cpp | 41K | GoblinData.cpp | 哥布林数据 |
| 5 | CSuperTeHui.cpp | 19K | SuperTeHui.cpp | 超级特惠 |
| 6 | CWan360.cpp | 16K | Wan360.cpp | 360平台 |
| 7 | CMonthlyChouJiangData.cpp | 15K | MonthlyChouJiangData.cpp | 月抽奖数据 |
| 8 | CWuHunShop.cpp | 15K | WuHunShop.cpp | 武魂商店 |
| 9 | CShiZhuangData.cpp | 15K | ShiZhuangData.cpp | 时装数据 |
| 10 | CMingGeData.cpp | 14K | MingGeData.cpp | 名格数据 |
| 11 | CDropItemGroup.cpp | 12K | DropItemGroup.cpp | 掉落组 |
| 12 | CLittleHelperData.cpp | 11K | LittleHelperData.cpp | 小助手数据 |
| 13 | CTerritory.cpp | 10K | Territory.cpp | 领地战 |
| 14 | CHuoYueDuData.cpp | 10K | HuoYueDuData.cpp | 活跃度数据 |
| 15 | CSevenDayData.cpp | 9K | SevenDayData.cpp | 七天数据 |
| 16 | CRefreshMonster.cpp | 9K | RefreshMonster.cpp | 刷新怪物 |
| 17 | CXingMai.cpp | 9K | XingMai.cpp | 星脉系统 |
| 18 | CXinMaiMap.cpp | 9K | XinMaiMap.cpp | 心脉地图 |
| 19 | CTestServerReward.cpp | 8K | TestServerReward.cpp | 测试服奖励 |
| 20 | CHttpRequest.cpp | 8K | HttpRequest.cpp | HTTP请求 |
| 21 | ShiZhuangInfo.cpp | 7K | ShiZhuangInfo.cpp | 时装信息 |
| 22 | CFaBaoData.cpp | 7K | FaBaoData.cpp | 法宝数据 |
| 23 | CCardGroupBox.cpp | 5K | CardGroupBox.cpp | 卡牌组 |
| 24 | XinMoTable.cpp | 4K | XinMoTable.cpp | 心魔配置表 |
| 25 | CVplanData.cpp | 4K | VplanData.cpp | V计划数据 |
| 26 | WorldBossInfo.cpp | 4K | WorldBossInfo.cpp | 世界Boss信息 |
| 27 | CMingGeTable.cpp | 3K | MingGeTable.cpp | 名格配置表 |
| 28 | CSqiderQueen.cpp | 2K | SqiderQueen.cpp | 蜘蛛女王 |
| 29 | CDBCFile.cpp | 19K | DBCFile.cpp | DBC文件读取 |
| 30 | CKunData.cpp | 16K | KunData.cpp | 昆数据 |
| 31 | CShiZhuangData.cpp | 15K | ShiZhuangData.cpp | 时装数据 |
| 32 | CDropItemGroup.cpp | 12K | DropItemGroup.cpp | 掉落组 |
| 33 | CCardGroupBoxManager.cpp | 1K | CardGroupBoxManager.cpp | 卡牌组管理 |
| 34 | CDaZheQuan.cpp | 1K | DaZheQuan.cpp | 打折券 |
| 35 | CLibraryTable.cpp | 1K | LibraryTable.cpp | 图书馆表 |
| 36 | CRefreshMonster.cpp | 9K | RefreshMonster.cpp | 刷新怪物 |

---

## 三、覆盖率 30-50% 的文件（需重点补全）

| # | 反编译文件 | 当前文件 | 覆盖率 | 缺口 |
|---|-----------|---------|--------|------|
| 1 | CFunctionOpen.cpp | FunctionOpen.cpp | 14% | ~26K |
| 2 | CHuoYueDu.cpp | HuoYueDu.cpp | 25% | ~23K |
| 3 | CMoLingRuQin.cpp | MoLingRuQin.cpp | 27% | ~6K |
| 4 | CFriendExpReward.cpp | FriendExpReward.cpp | 30% | ~8K |
| 5 | CExtSystemMgr.cpp | ExtSystemMgr.cpp | 31% | ~5K |
| 6 | Trap.cpp | Trap.cpp | 31% | ~14K |
| 7 | CExtMagicBox.cpp | MagicBox.cpp | 32% | ~36K |
| 8 | CExtFlopDraw.cpp | FlopDraw.cpp | 32% | ~12K |
| 9 | CExtOperateLimit.cpp | OperateLimit.cpp | 32% | ~16K |
| 10 | CExtCurrency.cpp | Currency.cpp | 32% | ~23K |
| 11 | CExtCharWing.cpp | CharWing.cpp | 32% | ~16K |
| 12 | Skill.cpp | Skill.cpp | 32% | ~38K |
| 13 | Plant.cpp | Plant.cpp | 33% | ~18K |
| 14 | CRankMirror.cpp | RankMirror.cpp | 33% | ~11K |
| 15 | CBossKilledReward.cpp | BossKilledReward.cpp | 33% | ~16K |
| 16 | CShangCheng.cpp | ShangCheng.cpp | 34% | ~19K |
| 17 | CGMBackstate.cpp | GMBackstage.cpp | 34% | ~9K |
| 18 | CFamilyLight.cpp | FamilyLight.cpp | 35% | ~12K |
| 19 | CObjCarrier.cpp | ObjCarrier.cpp | 35% | ~4K |
| 20 | CEquipBack.cpp | EquipBack.cpp | 36% | ~29K |
| 21 | CActivityManager.cpp | ActivityManager.cpp | 36% | ~22K |
| 22 | CGuiGuDaoRen.cpp | GuiGuDaoRen.cpp | 36% | ~24K |
| 23 | CCityWar.cpp | CityWar.cpp | 36% | ~50K |
| 24 | CPlayerMail.cpp | PlayerMail.cpp | 37% | ~15K |
| 25 | ScoreShop.cpp | ScoreShop.cpp | 38% | ~8K |
| 26 | CMapRunner.cpp | MapRunner.cpp | 38% | ~9K |
| 27 | CTrade.cpp | Trade.cpp | 38% | ~38K |
| 28 | CTianJiangBaoXiang.cpp | TianJiangBaoXiang.cpp | 39% | ~9K |
| 29 | CExtCharFamily.cpp | CharFamily.cpp | 39% | ~51K |
| 30 | CRongHe.cpp | RongHe.cpp | 40% | ~19K |
| 31 | CExtCharWish.cpp | CharWish.cpp | 40% | ~8K |
| 32 | CExtCharExchange.cpp | CharExchange.cpp | 40% | ~7K |
| 33 | CDaTiHD.cpp | DaTiHD.cpp | 41% | ~7K |
| 34 | CExtCharTitle.cpp | CharTitle.cpp | 41% | ~21K |
| 35 | MapManager.cpp | MapManager.cpp | 41% | ~6K |
| 36 | GameService.cpp | GameService.cpp | 41% | ~84K |
| 37 | CChrDepot.cpp | ChrDepot.cpp | 41% | ~25K |
| 38 | CExtCharAuction.cpp | CharAuction.cpp | 42% | ~10K |
| 39 | CMoneyRewardTask.cpp | MoneyRewardTask.cpp | 42% | ~51K |
| 40 | CYunYingHD.cpp | YunYingHD.cpp | 42% | ~44K |
| 41 | CExtCharDraw.cpp | CharDraw.cpp | 43% | ~4K |
| 42 | URLService.cpp | URLService.cpp | 43% | ~2K |
| 43 | CExtCharSkill.cpp | CharSkill.cpp | 44% | ~53K |
| 44 | CMonthlyChouJiang.cpp | CMonthlyChouJiang.cpp | 45% | ~10K |
| 45 | CExtCharWorship.cpp | CharWorship.cpp | 45% | ~5K |
| 46 | Map.cpp | Map.cpp | 45% | ~79K |
| 47 | Unit.cpp | Unit.cpp | 46% | ~37K |
| 48 | CActivityWorldBoss.cpp | ActivityWorldBoss.cpp | 46% | ~15K |
| 49 | CRongLian.cpp | RongLian.cpp | 47% | ~1K |
| 50 | CTimer.cpp | Timer.cpp | 47% | ~4K |
| 51 | CVipClub.cpp | CVipClub.cpp | 47% | ~7K |
| 52 | CKaiFuBoss.cpp | KaiFuBoss.cpp | 48% | ~5K |
| 53 | CTianLing.cpp | TianLing.cpp | 48% | ~13K |
| 54 | CNationalDayHd.cpp | NationalDayHd.cpp | 48% | ~13K |
| 55 | CYaBiao.cpp | YaBiao.cpp | 48% | ~1K |
| 56 | CTreasureMap.cpp | TreasureMap.cpp | 48% | ~16K |
| 57 | CExtCharMysteryShop.cpp | CharMysteryShop.cpp | 49% | ~9K |
| 58 | COutLinkFestival.cpp | OutLinkFestival.cpp | 49% | ~5K |
| 59 | CVip.cpp | Vip.cpp | 49% | ~34K |
| 60 | CShenWei.cpp | ShenWei.cpp | 50% | ~2K |

---

## 四、补全任务计划

### R0 — Player.cpp 深度补全（最高优先级）

缺口 ~474K，反编译 535K vs 当前 61K。这是链接和运行的核心。

| 子任务 | 说明 | 预估新增 |
|--------|------|---------|
| R0-a | onNetPacket 处理器（onMove/onHit/onSwitchMap/onEnterDungeon/onUseItem/onUpgradeSkill 等 ~30个） | ~8000行 |
| R0-b | send* 信息发送器（sendBasicInfo/sendLoginInfo/sendChrInfo/sendSkillList/sendActionList 等 ~15个） | ~3000行 |
| R0-c | refresh() 主循环 + checkNetPackets/checkSyncStatus/checkDie/checkSaveToDB/minuteCheck | ~2000行 |
| R0-d | init() 初始化 + SaveDBData + InitExtSystems | ~1500行 |
| R0-e | OnXXX 扩展系统回调（OnKaiFuHuoDong/OnUniteServer/OnDoubleEleven 等 20+个） | ~2000行 |
| R0-f | 战斗/属性/升级（upgradeLevel/autoUpgradeLevel/recalcAttr/setBaseAttr完整版） | ~1500行 |
| R0-g | 其他缺失方法（verifyBagInfo完整版/checkPreventWallow完整版等） | ~1000行 |

**R0 合计：~19000 行**

### R1 — 大型模块深度补全（缺口 >100K）

| 子任务 | 文件 | 缺口 | 预估新增 |
|--------|------|------|---------|
| R1-1 | FestivalDoubleEleven.cpp | ~367K | ~8000行 |
| R1-2 | Dungeon.cpp | ~185K | ~4000行 |
| R1-3 | Monster.cpp | ~121K | ~2500行 |

**R1 合计：~14500 行**

### R2 — 中型模块补全（缺口 50-100K）

| 子任务 | 文件 | 缺口 | 预估新增 |
|--------|------|------|---------|
| R2-1 | OpenBeta.cpp | ~87K | ~2000行 |
| R2-2 | GameService.cpp | ~84K | ~2000行 |
| R2-3 | Goblin.cpp | ~77K | ~1800行 |
| R2-4 | Vplan.cpp | ~63K | ~1500行 |
| R2-5 | ActivityMap.cpp | ~56K | ~1300行 |
| R2-6 | UniteServer.cpp | ~56K | ~1300行 |
| R2-7 | ZongHeYunYingHD.cpp | ~45K | ~1000行 |
| R2-8 | FestivalActivity.cpp | ~41K | ~900行 |
| R2-9 | Skill.cpp | ~38K | ~800行 |
| R2-10 | CCityWar.cpp | ~50K | ~1200行 |
| R2-11 | CExtCharFamily.cpp | ~51K | ~1200行 |
| R2-12 | CMoneyRewardTask.cpp | ~51K | ~1200行 |

**R2 合计：~15800 行**

### R3 — 中小型模块补全（缺口 20-50K）

| 子任务 | 文件 | 缺口 | 预估新增 |
|--------|------|------|---------|
| R3-1 | Equip.cpp | ~102K | ~2500行 |
| R3-2 | Map.cpp | ~79K | ~1800行 |
| R3-3 | Bag.cpp | ~55K | ~1200行 |
| R3-4 | CharSkill.cpp | ~53K | ~1200行 |
| R3-5 | DailyActivity.cpp | ~39K | ~800行 |
| R3-6 | Trade.cpp | ~38K | ~800行 |
| R3-7 | MagicBox.cpp | ~36K | ~700行 |
| R3-8 | Vip.cpp | ~34K | ~700行 |
| R3-9 | Unit.cpp | ~37K | ~800行 |
| R3-10 | YunYingHD.cpp | ~44K | ~900行 |
| R3-11 | EquipBack.cpp | ~29K | ~600行 |
| R3-12 | Currency.cpp | ~23K | ~500行 |
| R3-13 | ActivityManager.cpp | ~22K | ~500行 |
| R3-14 | CharTitle.cpp | ~21K | ~400行 |
| R3-15 | RongHe.cpp | ~19K | ~400行 |
| R3-16 | ShangCheng.cpp | ~19K | ~400行 |
| R3-17 | ShiZhuang.cpp | ~18K | ~400行 |
| R3-18 | Plant.cpp | ~18K | ~400行 |
| R3-19 | WorldBoss.cpp | ~18K | ~400行 |
| R3-20 | CKunExt.cpp | ~19K | ~400行 |
| R3-21 | ObjPet.cpp | ~24K | ~500行 |
| R3-22 | GuiGuDaoRen.cpp | ~24K | ~500行 |
| R3-23 | ChrDepot.cpp | ~25K | ~500行 |
| R3-24 | PlayerMail.cpp | ~15K | ~300行 |
| R3-25 | CharWing.cpp | ~16K | ~300行 |
| R3-26 | OperateLimit.cpp | ~16K | ~300行 |
| R3-27 | TreasureMap.cpp | ~16K | ~300行 |
| R3-28 | Trap.cpp | ~14K | ~300行 |
| R3-29 | TianLing.cpp | ~13K | ~300行 |
| R3-30 | NationalDayHd.cpp | ~13K | ~300行 |
| R3-31 | FamilyLight.cpp | ~12K | ~300行 |
| R3-32 | FlopDraw.cpp | ~12K | ~300行 |
| R3-33 | RankMirror.cpp | ~11K | ~300行 |
| R3-34 | CharAuction.cpp | ~10K | ~200行 |
| R3-35 | CMonthlyChouJiang.cpp | ~10K | ~200行 |
| R3-36 | CharMysteryShop.cpp | ~9K | ~200行 |
| R3-37 | TianJiangBaoXiang.cpp | ~9K | ~200行 |
| R3-38 | FriendExpReward.cpp | ~8K | ~200行 |
| R3-39 | CharWish.cpp | ~8K | ~200行 |
| R3-40 | DaTiHD.cpp | ~7K | ~200行 |
| R3-41 | HuoYueDu.cpp | ~23K | ~500行 |
| R3-42 | FunctionOpen.cpp | ~26K | ~600行 |
| R3-43 | CharExchange.cpp | ~7K | ~200行 |
| R3-44 | CampWar.cpp | ~21K | ~400行 |
| R3-45 | ActivityWorldBoss.cpp | ~15K | ~300行 |
| R3-46 | SevenDayTask.cpp | ~8K | ~200行 |
| R3-47 | CMingGeExt.cpp | ~16K | ~300行 |
| R3-48 | BossKilledReward.cpp | ~16K | ~300行 |
| R3-49 | GMBackstage.cpp | ~9K | ~200行 |
| R3-50 | ScoreShop.cpp | ~8K | ~200行 |

**R3 合计：~21600 行**

### R4 — 小型模块补全（缺口 <10K）

| 子任务 | 文件 | 缺口 |
|--------|------|------|
| R4-1 | CharDraw.cpp | ~4K |
| R4-2 | CharWorship.cpp | ~5K |
| R4-3 | URLService.cpp | ~2K |
| R4-4 | RongLian.cpp | ~1K |
| R4-5 | Timer.cpp | ~4K |
| R4-6 | CVipClub.cpp | ~7K |
| R4-7 | KaiFuBoss.cpp | ~5K |
| R4-8 | YaBiao.cpp | ~1K |
| R4-9 | OutLinkFestival.cpp | ~5K |
| R4-10 | ShenWei.cpp | ~2K |
| R4-11 | CharPortal.cpp | ~6K |
| R4-12 | GuardPrivilege.cpp | ~6K |
| R4-13 | FamilyManager.cpp | ~9K |
| R4-14 | CharTeamDungeon.cpp | ~7K |
| R4-15 | PeerlessWar.cpp | ~15K |
| R4-16 | CharHallOfFame.cpp | ~9K |
| R4-17 | MonsterActivity.cpp | ~5K |
| R4-18 | QiFu.cpp | ~4K |
| R4-19 | CharWuHun.cpp | ~8K |
| R4-20 | Trailer.cpp | ~4K |
| R4-21 | FriendExpReward.cpp | ~3K |
| R4-22 | CharCarrier.cpp | ~2K |
| R4-23 | GongMing.cpp | ~3K |
| R4-24 | LevelRefining.cpp | ~3K |
| R4-25 | MonsterDungeon.cpp | ~3K |
| R4-26 | CharMysteryGift.cpp | ~3K |
| R4-27 | BlackMarket.cpp | ~5K |
| R4-28 | SpecialEquip.cpp | ~4K |
| R4-29 | UltimateChallenge.cpp | ~6K |
| R4-30 | TaskCycle.cpp | ~7K |
| R4-31 | CLittleHelper.cpp | ~5K |
| R4-32 | CharTeam.cpp | ~4K |
| R4-33 | ItemHelper.cpp | ~1K |
| R4-34 | EquipManager.cpp | ~5K |
| R4-35 | HorseRacing.cpp | ~5K |
| R4-36 | DBService.cpp | ~35K |
| R4-37 | TouZi.cpp | ~5K |
| R4-38 | FaBao.cpp | ~3K |
| R4-39 | MapRunner.cpp | ~9K |
| R4-40 | MapManager.cpp | ~6K |
| R4-41 | ObjCarrier.cpp | ~4K |
| R4-42 | ExtSystemMgr.cpp | ~5K |
| R4-43 | MoLingRuQin.cpp | ~6K |

**R4 合计：~200K → ~5000 行**

### R5 — 新增缺失文件（36个）

| 子任务 | 文件 | 体积 | 说明 |
|--------|------|------|------|
| R5-1 | CharTencent.cpp | 63K | 腾讯平台集成（黄钻/蓝钻/QQ/360/TGP） |
| R5-2 | XinMo.cpp | 53K | 心魔系统 |
| R5-3 | GoblinData.cpp | 41K | 哥布林数据管理 |
| R5-4 | SuperTeHui.cpp | 19K | 超级特惠活动 |
| R5-5 | DBCFile.cpp | 19K | DBC文件读取器 |
| R5-6 | Wan360.cpp | 16K | 360平台集成 |
| R5-7 | KunData.cpp | 16K | 昆数据管理 |
| R5-8 | WuHunShop.cpp | 15K | 武魂商店 |
| R5-9 | ShiZhuangData.cpp | 15K | 时装数据 |
| R5-10 | MingGeData.cpp | 14K | 名格数据 |
| R5-11 | DropItemGroup.cpp | 12K | 掉落物品组 |
| R5-12 | LittleHelperData.cpp | 11K | 小助手数据 |
| R5-13 | Territory.cpp | 10K | 领地战 |
| R5-14 | HuoYueDuData.cpp | 10K | 活跃度数据 |
| R5-15 | SevenDayData.cpp | 9K | 七天登录数据 |
| R5-16 | RefreshMonster.cpp | 9K | 刷新怪物 |
| R5-17 | XingMai.cpp | 9K | 星脉系统 |
| R5-18 | XinMaiMap.cpp | 9K | 心脉地图 |
| R5-19 | TestServerReward.cpp | 8K | 测试服奖励 |
| R5-20 | HttpRequest.cpp | 8K | HTTP请求 |
| R5-21 | ShiZhuangInfo.cpp | 7K | 时装信息 |
| R5-22 | FaBaoData.cpp | 7K | 法宝数据 |
| R5-23 | CardGroupBox.cpp | 5K | 卡牌组 |
| R5-24 | XinMoTable.cpp | 4K | 心魔配置表 |
| R5-25 | VplanData.cpp | 4K | V计划数据 |
| R5-26 | WorldBossInfo.cpp | 4K | 世界Boss信息 |
| R5-27 | MingGeTable.cpp | 3K | 名格配置表 |
| R5-28 | SqiderQueen.cpp | 2K | 蜘蛛女王 |
| R5-29 | CardGroupBoxManager.cpp | 1K | 卡牌组管理 |
| R5-30 | DaZheQuan.cpp | 1K | 打折券 |
| R5-31 | LibraryTable.cpp | 1K | 图书馆表 |
| R5-32 | MonthlyChouJiangData.cpp | 15K | 月抽奖数据 |
| R5-33 | CDaTingReward.cpp | 42K | 答题奖励(命名映射问题) |

**R5 合计：~400K → ~10000 行**

### R6 — 编译/链接验证

| 子任务 | 说明 |
|--------|------|
| R6-1 | 全量编译错误修复（缺少头文件、API名称不匹配、类型转换等） |
| R6-2 | 链接错误修复（未实现方法导致的链接错误） |
| R6-3 | 运行时验证（关键功能路径测试） |

---

## 五、执行顺序与工作量估算

```
阶段1: R0 (Player.cpp 深度补全) — ~19000行
  R0-a → R0-b → R0-c → R0-d → R0-e → R0-f → R0-g

阶段2: R1 (大型模块) — ~14500行
  R1-1 → R1-2 → R1-3

阶段3: R2 (中型模块) — ~15800行
  R2-1~R2-12 按依赖关系排序

阶段4: R3 (中小型模块) — ~21600行
  R3-1~R3-50 按缺口大小排序

阶段5: R4 (小型模块) — ~5000行
  R4-1~R4-43

阶段6: R5 (新增缺失文件) — ~10000行
  R5-1~R5-33

阶段7: R6 (编译/链接验证)
  R6-1 → R6-2 → R6-3
```

| 阶段 | 预估新增代码 | 文件数 |
|------|-------------|--------|
| R0 Player | ~19000行 | 1 |
| R1 大型 | ~14500行 | 3 |
| R2 中型 | ~15800行 | 12 |
| R3 中小型 | ~21600行 | 50 |
| R4 小型 | ~5000行 | 43 |
| R5 新增文件 | ~10000行 | 33 |
| R6 验证 | ~1000行 | — |
| **合计** | **~85900行** | **~142** |

---

## 六、注意事项

1. **反编译源体积膨胀系数**：IDA 伪代码比干净 C++ 大 2-3 倍，上述缺口行数已按 1/2.5 折算
2. **connid 改造**：所有新增代码必须遵循 2019 多连接架构（popNetpacket/sendPacketTo/replySuccess/worldBroadcast 加 connid）
3. **命名映射**：C 前缀去掉、CExtChar* → Char*、CExt* → 去掉 CExt
4. **不存在的 API**：AddPlatformLog/GetPassport/PLDT_SYSTEM 跳过
5. **GBK 编码文件**：share/ 目录下的 .h 文件需用 node.js 脚本修改
6. **聚合文件**：Cfg*Table → CfgData、ItemEffect 子类 → ItemEffect、DB 数据类 → DBData、日志类 → GameLogs