# GameServer - 游戏服务器

基于 C++ 的 MMORPG 游戏服务器项目。

## 构建

```bash
cd gameserver
make
```

依赖：pthread, libanswer (内置于 `libanswer/` 目录)

## 项目结构

| 目录 | 说明 |
|------|------|
| `gameserver/` | 游戏逻辑服务器 |
| `gameserver/decompiled/` | 反编译参考代码（用于模块移植） |
| `dbserver/` | 数据库服务器 |
| `gateserver/` | 网关服务器 |
| `globalserver/` | 全局服务器 |
| `robot/` | 机器人测试客户端 |
| `share/` | 共享头文件与数据结构 |
| `libanswer/` | 基础网络库 |
| `sqls/` | SQL 建表脚本 |

## 模块修复进度

从反编译代码 (`gameserver/decompiled/`) 中移植缺失模块到当前代码库。

### 已移植模块 (19/19)

| 模块 | 源文件 | 行数 | 说明 |
|------|--------|------|------|
| **GuardPrivilege** (护卫特权) | `GuardPrivilege.cpp/.h` | ~300 | 12 方法，含购买/DB回调/图标推送 |
| **SpecialEquip** (特殊装备) | `SpecialEquip.cpp/.h` | ~280 | 10 方法，含等级判定/激活/升级推送 |
| **BlackMarket** (黑市) | `BlackMarket.cpp/.h` | ~300 | 11 方法，含入场/购买/广播 |
| **TianLing** (天灵系统) | `TianLing.cpp/.h` | ~350 | 12 方法，3 子系统(天灵/战魂/日月) |
| **OutLinkFestival** (外部链接活动) | `OutLinkFestival.cpp/.h` | ~150 | 5 方法，全局服务，活动图标推送 |
| **KaiFuHuoDong** (开服活动) | `KaiFuHuoDong.cpp/.h` | ~2260 | 44 方法，源自 COpenBeta，含首杀/冲级/商城 |
| **UniteServer** (合服) | `UniteServer.cpp/.h` | ~1990 | 41 方法，含玩家迁移/家族合并/数据处理 |
| **Tencent** (腾讯平台) | `Tencent.cpp/.h` + `TencentTable.cpp/.h` | ~1850 | 55 方法 + 独立配置表系统(12张表)，原 CExtCharTencent |
| **CExtCharBag** (背包系统) | `Bag.cpp/.h` | ~3800 | 已完整实现(80+ 方法)，修复 OnDaySwitch + 缺失枚举值 |
| **CCityWar** (城战) | `CityWar.cpp/.h` | ~1200 | 42 方法，修复 3 处 sort() 缺比较器 Bug |
| **CCampWar** (阵营战) | `CampWar.cpp/.h` | ~852 | 28 方法，适配简化称号/阵营系统 |
| **CWorldBoss** (世界BOSS) | `WorldBoss.cpp/.h` | ~500 | 23 方法，扩展 KillerInfo + Top5 击杀者追踪 |
| **CExtCharCarrier** (护送) | `CharCarrier.cpp/.h` + `ObjCarrier.cpp/.h` | ~580 | 29 方法，含载具护送/到达/完成 |
| **CExtCharDraw** (抽卡) | `CharDraw.cpp/.h` | ~226 | 7 方法，含随机奖励/概率抽取 |
| **CExtCharExchange** (兑换) | `CharExchange.cpp/.h` | ~321 | 11 方法，含 DB 存取/兑换逻辑/记录管理 |
| **CExtCharMysteryGift** (神秘礼物) | `CharMysteryGift.cpp/.h` | ~273 | 15 方法，含领取礼包/广播/状态管理 |
| **CExtCharMysteryShop** (神秘商店) | `CharMysteryShop.cpp/.h` | ~526 | 15 方法，含商店查询/购买/刷新/加权随机商品/广播 |

### 数据层变更

| 文件 | 变更说明 |
|------|----------|
| `CfgData.h` | 添加 GuardPrivilege/SpecialEquip/BlackMarket/TianLing/OutLinkFestival/Carrier/Draw/Exchange/MysteryGift/MysteryShop 配置结构体和成员 |
| `CfgData.cpp` | 完善配置解析方法 (Init*Table) 和 Get 方法 |
| `DataStructs.h` | 添加 IACR_AUCTION_BUY/CANCEL/SELECT_ITEM, IDCR_SELECT_ITEM/DISCARD, GCR/GCC/MCR_AUTO_USE, GCR_MYSTERY_GIFT_BUY, GCR_MYSTERY_SHOP_REFRESH/BUY, IACR_MYSTERY_SHOP_BUY_GET, IDCR_MYSTERY_SHOP_BUY_COST |
| `share/DataStruct.h` | 添加 ExchangeRecord 结构体 + ExchangeDBData 类; 添加 MysteryShop 结构体 + MysteryShopDBData 类 (SaveToSqlString/LoadFromDB/PackageData/UnPackageData) |
| `Player.h` | 集成 CharDraw/CharExchange/CharMysteryGift/CharMysteryShop 模块声明 |

### 待移植模块 (剩余 ~67 个)

以下是从反编译代码中识别出的 `CExtSystemBase` 派生类模块：

| # | 模块 | 反编译文件 | 行数 | 说明 |
|---|------|-----------|------|------|
| 1 | BossKilledReward | `CBossKilledReward.cpp` | — | BOSS击杀奖励 |
| 2 | CardGroupBox | `CCardGroupBox.cpp` | — | 卡牌礼盒 |
| 3 | CardGroupBoxManager | `CCardGroupBoxManager.cpp` | — | 卡牌礼盒管理器 |
| 4 | CharWuHun | `CCharWuHun.cpp` | — | 武魂系统 |
| 5 | DaTingReward | `CDaTingReward.cpp` | — | 大厅奖励 |
| 6 | DaZheQuan | `CDaZheQuan.cpp` | — | 打折券 |
| 7 | DropItemGroup | `CDropItemGroup.cpp` | — | 掉落组 |
| 8 | EquipBack | `CEquipBack.cpp` | — | 装备回购 |
| 9 | ExtCharAuction | `CExtCharAuction.cpp` | — | 拍卖行 |
| 10 | ExtCharFamily | `CExtCharFamily.cpp` | — | 军团 |
| 11 | ExtCharHallOfFame | `CExtCharHallOfFame.cpp` | — | 名人堂 |
| 12 | ExtCharJueWei | `CExtCharJueWei.cpp` | — | 爵位 |
| 13 | ExtCharPet | `CExtCharPet.cpp` | ~2,498 | 宠物 |
| 14 | ExtCharPortal | `CExtCharPortal.cpp` | — | 传送门 |
| 15 | ExtCharSkill | `CExtCharSkill.cpp` | ~2,498 | 技能 |
| 16 | ExtCharTeam | `CExtCharTeam.cpp` | — | 队伍 |
| 17 | ExtCharTeamDungeon | `CExtCharTeamDungeon.cpp` | — | 队伍副本 |
| 18 | ExtCharTitle | `CExtCharTitle.cpp` | — | 称号 |
| 19 | ExtCharWing | `CExtCharWing.cpp` | — | 翅膀 |
| 20 | ExtCharWish | `CExtCharWish.cpp` | — | 许愿 |
| 21 | ExtCharWorship | `CExtCharWorship.cpp` | — | 膜拜 |
| 22 | ExtChrTaskCycle | `CExtChrTaskCycle.cpp` | — | 循环任务 |
| 23 | ExtCurrency | `CExtCurrency.cpp` | — | 货币 |
| 24 | ExtEquip | `CExtEquip.cpp` | ~6,205 | 装备 |
| 25 | ExtFightChecker | `CExtFightChecker.cpp` | — | 战斗检测 |
| 26 | ExtFlopDraw | `CExtFlopDraw.cpp` | — | 翻牌抽奖 |
| 27 | ExtMagicBox | `CExtMagicBox.cpp` | — | 魔盒 |
| 28 | ExtOperateLimit | `CExtOperateLimit.cpp` | — | 操作限制 |
| 29 | FestivalActivity | `CFestivalActivity.cpp` | ~1,372 | 节日活动 |
| 30 | FestivalDoubleEleven | `CFestivalDoubleEleven.cpp` | ~10,725 | **双十一活动（最大模块）** |
| 31 | FlopDraw | `CFlopDraw.cpp` | — | 翻牌抽奖 |
| 32 | GMBackstate | `CGMBackstate.cpp` | — | GM后台 |
| 33 | GuiGuDaoRen | `CGuiGuDaoRen.cpp` | — | 鬼谷道人 |
| 34 | HttpRequest | `CHttpRequest.cpp` | — | HTTP请求 |
| 35 | KiaFuRecharge | `CKiaFuRecharge.cpp` | — | 开服充值 |
| 36 | KunExt | `CKunExt.cpp` | — | 鲲系统 |
| 37 | LevelRefining | `CLevelRefining.cpp` | — | 装备精炼 |
| 38 | LittleHelper | `CLittleHelper.cpp` | — | 小助手 |
| 39 | MingGeExt | `CMingGeExt.cpp` | — | 命格 |
| 40 | MoneyRewardTask | `CMoneyRewardTask.cpp` | ~2,560 | 金币奖励任务 |
| 41 | MonthlyChouJiang | `CMonthlyChouJiang.cpp` | — | 月卡抽奖 |
| 42 | NationalDayHd | `CNationalDayHd.cpp` | — | 国庆活动 |
| 43 | ObjAttrs | `CObjAttrs.cpp` | — | 对象属性 |
| 44 | ObjCarrier | `CObjCarrier.cpp` | — | 对象载具 |
| 45 | ObjState | `CObjState.cpp` | — | 对象状态 |
| 46 | RankMirror | `CRankMirror.cpp` | — | 排行榜镜像 |
| 47 | RefreshMonster | `CRefreshMonster.cpp` | — | 刷新怪物 |
| 48 | RongHe | `CRongHe.cpp` | — | 融合 |
| 49 | RongLian | `CRongLian.cpp` | — | 熔炼 |
| 50 | SevenDayTask | `CSevenDayTask.cpp` | — | 七日任务 |
| 51 | ShenWei | `CShenWei.cpp` | — | 神威 |
| 52 | ShiZhuang | `CShiZhuang.cpp` | — | 时装 |
| 53 | SqiderQueen | `CSqiderQueen.cpp` | — | 蜘蛛女王 |
| 54 | SuperTeHui | `CSuperTeHui.cpp` | — | 超级特惠 |
| 55 | Territory | `CTerritory.cpp` | — | 领土战 |
| 56 | TestServerReward | `CTestServerReward.cpp` | — | 测试服奖励 |
| 57 | TreasureMap | `CTreasureMap.cpp` | — | 藏宝图 |
| 58 | VipClub | `CVipClub.cpp` | — | Vip俱乐部 |
| 59 | Vplan | `CVplan.cpp` | ~2,418 | V计划 |
| 60 | Wan360 | `CWan360.cpp` | — | 360平台 |
| 61 | WuHunShop | `CWuHunShop.cpp` | — | 武魂商店 |
| 62 | XinMaiMap | `CXinMaiMap.cpp` | — | 心法地图 |
| 63 | XinMo | `CXinMo.cpp` | — | 心魔 |
| 64 | XingMai | `CXingMai.cpp` | — | 星脉 |
| 65 | YaBiao | `CYaBiao.cpp` | — | 押镖 |
| 66 | ActivityWorldBoss | `CActivityWorldBoss.cpp` | — | 世界BOSS活动 |
| 67 | PeerlessWar | `CPeerlessWar.cpp` | — | 绝世战 |

> **注意**: 以上列表来自 `gameserver/decompiled/` 目录扫描。部分模块可能已有部分实现。

## 配置表文件

`gameserver/ServerConfig/Tables/` 目录包含游戏配置表（TXT格式），当前已支持的配置表包括：
- 活动(Activity)、物品(Item)、怪物(Monster)、地图(Map)、技能(Skill) 等核心表
- GuardPrivilege(护卫特权)、SpecialEquip(特殊装备)、BlackMarket(黑市)、TianLing(天灵)、OutLinkFestival(外部活动) 等新模块表

所有配置表在 `gameserver/CfgData.cpp` 的 `init()` 函数中加载。
