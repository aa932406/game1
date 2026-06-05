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

### 已移植模块 (14/14)

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

### 数据层变更

| 文件 | 变更说明 |
|------|----------|
| `CfgData.h` | 添加 GuardPrivilege/SpecialEquip/BlackMarket/TianLing/OutLinkFestival 配置结构体和成员 |
| `CfgData.cpp` | 完善配置解析方法 (Init*Table) 和 Get 方法 |
| `DataStructs.h` | 添加 IACR_AUCTION_BUY/CANCEL/SELECT_ITEM, IDCR_SELECT_ITEM/DISCARD, GCR/GCC/MCR_AUTO_USE 枚举值 |
| `Shared.h` | 添加 PII_TIAN_LIN 枚举值 |

### 待移植模块 (剩余 ~60 个)

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
| 10 | ExtCharCarrier | `CExtCharCarrier.cpp` | — | 载具 |
| 11 | ExtCharDraw | `CExtCharDraw.cpp` | — | 抽奖 |
| 12 | ExtCharExchange | `CExtCharExchange.cpp` | — | 兑换 |
| 13 | ExtCharFamily | `CExtCharFamily.cpp` | — | 军团 |
| 14 | ExtCharHallOfFame | `CExtCharHallOfFame.cpp` | — | 名人堂 |
| 15 | ExtCharJueWei | `CExtCharJueWei.cpp` | — | 爵位 |
| 16 | ExtCharMysteryGift | `CExtCharMysteryGift.cpp` | — | 神秘礼物 |
| 17 | ExtCharMysteryShop | `CExtCharMysteryShop.cpp` | — | 神秘商店 |
| 18 | ExtCharPet | `CExtCharPet.cpp` | ~2,498 | 宠物 |
| 19 | ExtCharPortal | `CExtCharPortal.cpp` | — | 传送门 |
| 20 | ExtCharSkill | `CExtCharSkill.cpp` | ~2,498 | 技能 |
| 21 | ExtCharTeam | `CExtCharTeam.cpp` | — | 队伍 |
| 22 | ExtCharTeamDungeon | `CExtCharTeamDungeon.cpp` | — | 队伍副本 |
| 23 | ExtCharTitle | `CExtCharTitle.cpp` | — | 称号 |
| 24 | ExtCharWing | `CExtCharWing.cpp` | — | 翅膀 |
| 25 | ExtCharWish | `CExtCharWish.cpp` | — | 许愿 |
| 26 | ExtCharWorship | `CExtCharWorship.cpp` | — | 膜拜 |
| 27 | ExtChrTaskCycle | `CExtChrTaskCycle.cpp` | — | 循环任务 |
| 28 | ExtCurrency | `CExtCurrency.cpp` | — | 货币 |
| 29 | ExtEquip | `CExtEquip.cpp` | ~6,205 | 装备 |
| 30 | ExtFightChecker | `CExtFightChecker.cpp` | — | 战斗检测 |
| 31 | ExtFlopDraw | `CExtFlopDraw.cpp` | — | 翻牌抽奖 |
| 32 | ExtMagicBox | `CExtMagicBox.cpp` | — | 魔盒 |
| 33 | ExtOperateLimit | `CExtOperateLimit.cpp` | — | 操作限制 |
| 34 | FestivalActivity | `CFestivalActivity.cpp` | ~1,372 | 节日活动 |
| 35 | FestivalDoubleEleven | `CFestivalDoubleEleven.cpp` | ~10,725 | **双十一活动（最大模块）** |
| 36 | FlopDraw | `CFlopDraw.cpp` | — | 翻牌抽奖 |
| 37 | GMBackstate | `CGMBackstate.cpp` | — | GM后台 |
| 38 | GuiGuDaoRen | `CGuiGuDaoRen.cpp` | — | 鬼谷道人 |
| 39 | HttpRequest | `CHttpRequest.cpp` | — | HTTP请求 |
| 40 | KiaFuRecharge | `CKiaFuRecharge.cpp` | — | 开服充值 |
| 41 | KunExt | `CKunExt.cpp` | — | 鲲系统 |
| 42 | LevelRefining | `CLevelRefining.cpp` | — | 装备精炼 |
| 43 | LittleHelper | `CLittleHelper.cpp` | — | 小助手 |
| 44 | MingGeExt | `CMingGeExt.cpp` | — | 命格 |
| 45 | MoneyRewardTask | `CMoneyRewardTask.cpp` | ~2,560 | 金币奖励任务 |
| 46 | MonthlyChouJiang | `CMonthlyChouJiang.cpp` | — | 月卡抽奖 |
| 47 | NationalDayHd | `CNationalDayHd.cpp` | — | 国庆活动 |
| 48 | ObjAttrs | `CObjAttrs.cpp` | — | 对象属性 |
| 49 | ObjCarrier | `CObjCarrier.cpp` | — | 对象载具 |
| 50 | ObjState | `CObjState.cpp` | — | 对象状态 |
| 51 | RankMirror | `CRankMirror.cpp` | — | 排行榜镜像 |
| 52 | RefreshMonster | `CRefreshMonster.cpp` | — | 刷新怪物 |
| 53 | RongHe | `CRongHe.cpp` | — | 融合 |
| 54 | RongLian | `CRongLian.cpp` | — | 熔炼 |
| 55 | SevenDayTask | `CSevenDayTask.cpp` | — | 七日任务 |
| 56 | ShenWei | `CShenWei.cpp` | — | 神威 |
| 57 | ShiZhuang | `CShiZhuang.cpp` | — | 时装 |
| 58 | SqiderQueen | `CSqiderQueen.cpp` | — | 蜘蛛女王 |
| 59 | SuperTeHui | `CSuperTeHui.cpp` | — | 超级特惠 |
| 60 | Territory | `CTerritory.cpp` | — | 领土战 |
| 61 | TestServerReward | `CTestServerReward.cpp` | — | 测试服奖励 |
| 62 | TreasureMap | `CTreasureMap.cpp` | — | 藏宝图 |
| 63 | VipClub | `CVipClub.cpp` | — | Vip俱乐部 |
| 64 | Vplan | `CVplan.cpp` | ~2,418 | V计划 |
| 65 | Wan360 | `CWan360.cpp` | — | 360平台 |
| 66 | WuHunShop | `CWuHunShop.cpp` | — | 武魂商店 |
| 67 | XinMaiMap | `CXinMaiMap.cpp` | — | 心法地图 |
| 68 | XinMo | `CXinMo.cpp` | — | 心魔 |
| 69 | XingMai | `CXingMai.cpp` | — | 星脉 |
| 70 | YaBiao | `CYaBiao.cpp` | — | 押镖 |
| 71 | ActivityWorldBoss | `CActivityWorldBoss.cpp` | — | 世界BOSS活动 |
| 72 | PeerlessWar | `CPeerlessWar.cpp` | — | 绝世战 |

> **注意**: 以上列表来自 `gameserver/decompiled/` 目录扫描。部分模块可能已有部分实现。

## 配置表文件

`gameserver/ServerConfig/Tables/` 目录包含游戏配置表（TXT格式），当前已支持的配置表包括：
- 活动(Activity)、物品(Item)、怪物(Monster)、地图(Map)、技能(Skill) 等核心表
- GuardPrivilege(护卫特权)、SpecialEquip(特殊装备)、BlackMarket(黑市)、TianLing(天灵)、OutLinkFestival(外部活动) 等新模块表

所有配置表在 `gameserver/CfgData.cpp` 的 `init()` 函数中加载。
