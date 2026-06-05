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

### 已移植模块 (5/5)

| 模块 | 源文件 | 说明 |
|------|--------|------|
| **GuardPrivilege** (护卫特权) | `GuardPrivilege.cpp/.h` | 12 方法，基于 CExtSystemBase，含购买/DB回调/图标推送 |
| **SpecialEquip** (特殊装备) | `SpecialEquip.cpp/.h` | 10 方法，基于 CExtSystemBase，含等级判定/激活/升级推送 |
| **BlackMarket** (黑市) | `BlackMarket.cpp/.h` | 11 方法，基于 CExtSystemBase，含入场/购买/广播 |
| **TianLing** (天灵系统) | `TianLing.cpp/.h` | 12 方法，3 子系统(天灵/战魂/日月) |
| **OutLinkFestival** (外部链接活动) | `OutLinkFestival.cpp/.h` | 5 方法，独立全局服务，活动图标推送 |

### 数据层变更

| 文件 | 变更说明 |
|------|----------|
| `CfgData.h` | 添加 GuardPrivilege/SpecialEquip/BlackMarket/TianLing/OutLinkFestival 配置结构体和成员 |
| `CfgData.cpp` | 完善配置解析方法 (Init*Table) 和 Get 方法 |
| `DataStructs.h` | 添加 IACR/GCR/IDCR/MCR 枚举值 |
| `Shared.h` | 添加 PII_TIAN_LIN 枚举值 |

### 待移植模块 (剩余 ~70 个)

以下是从反编译代码中识别出的 `CExtSystemBase` 派生类模块，尚未移植到当前代码库：

| # | 模块 | 反编译文件 | 说明 |
|---|------|-----------|------|
| 1 | BossKilledReward | `CBossKilledReward.cpp` | BOSS击杀奖励 |
| 2 | CardGroupBox | `CCardGroupBox.cpp` | 卡牌礼盒 |
| 3 | CardGroupBoxManager | `CCardGroupBoxManager.cpp` | 卡牌礼盒管理器 |
| 4 | CharWuHun | `CCharWuHun.cpp` | 武魂系统 |
| 5 | DaTingReward | `CDaTingReward.cpp` | 大厅奖励 |
| 6 | DaZheQuan | `CDaZheQuan.cpp` | 打折券 |
| 7 | DropItemGroup | `CDropItemGroup.cpp` | 掉落组 |
| 8 | EquipBack | `CEquipBack.cpp` | 装备回购 |
| 9 | ExtCharAuction | `CExtCharAuction.cpp` | 拍卖行 |
| 10 | ExtCharBag | `CExtCharBag.cpp` | 背包（部分已存在） |
| 11 | ExtCharCarrier | `CExtCharCarrier.cpp` | 载具 |
| 12 | ExtCharDraw | `CExtCharDraw.cpp` | 抽奖 |
| 13 | ExtCharExchange | `CExtCharExchange.cpp` | 兑换 |
| 14 | ExtCharFamily | `CExtCharFamily.cpp` | 军团 |
| 15 | ExtCharHallOfFame | `CExtCharHallOfFame.cpp` | 名人堂 |
| 16 | ExtCharJueWei | `CExtCharJueWei.cpp` | 爵位 |
| 17 | ExtCharMysteryGift | `CExtCharMysteryGift.cpp` | 神秘礼物 |
| 18 | ExtCharMysteryShop | `CExtCharMysteryShop.cpp` | 神秘商店 |
| 19 | ExtCharPet | `CExtCharPet.cpp` | 宠物 |
| 20 | ExtCharPortal | `CExtCharPortal.cpp` | 传送门 |
| 21 | ExtCharSkill | `CExtCharSkill.cpp` | 技能 |
| 22 | ExtCharTeam | `CExtCharTeam.cpp` | 队伍 |
| 23 | ExtCharTeamDungeon | `CExtCharTeamDungeon.cpp` | 队伍副本 |
| 24 | ExtCharTencent | `CExtCharTencent.cpp` | 腾讯平台 |
| 25 | ExtCharTitle | `CExtCharTitle.cpp` | 称号 |
| 26 | ExtCharWing | `CExtCharWing.cpp` | 翅膀 |
| 27 | ExtCharWish | `CExtCharWish.cpp` | 许愿 |
| 28 | ExtCharWorship | `CExtCharWorship.cpp` | 膜拜 |
| 29 | ExtChrTaskCycle | `CExtChrTaskCycle.cpp` | 循环任务 |
| 30 | ExtCurrency | `CExtCurrency.cpp` | 货币 |
| 31 | ExtEquip | `CExtEquip.cpp` | 装备 |
| 32 | ExtFightChecker | `CExtFightChecker.cpp` | 战斗检测 |
| 33 | ExtFlopDraw | `CExtFlopDraw.cpp` | 翻牌抽奖 |
| 34 | ExtMagicBox | `CExtMagicBox.cpp` | 魔盒 |
| 35 | ExtOperateLimit | `CExtOperateLimit.cpp` | 操作限制 |
| 36 | FestivalActivity | `CFestivalActivity.cpp` | 节日活动 |
| 37 | FlopDraw | `CFlopDraw.cpp` | 翻牌抽奖 |
| 38 | GMBackstate | `CGMBackstate.cpp` | GM后台 |
| 39 | GuiGuDaoRen | `CGuiGuDaoRen.cpp` | 鬼谷道人 |
| 40 | HttpRequest | `CHttpRequest.cpp` | HTTP请求 |
| 41 | KiaFuRecharge | `CKiaFuRecharge.cpp` | 开服充值 |
| 42 | KunExt | `CKunExt.cpp` | 鲲系统 |
| 43 | LevelRefining | `CLevelRefining.cpp` | 装备精炼 |
| 44 | LittleHelper | `CLittleHelper.cpp` | 小助手 |
| 45 | MingGeExt | `CMingGeExt.cpp` | 命格 |
| 46 | MoneyRewardTask | `CMoneyRewardTask.cpp` | 金币奖励任务 |
| 47 | MonthlyChouJiang | `CMonthlyChouJiang.cpp` | 月卡抽奖 |
| 48 | NationalDayHd | `CNationalDayHd.cpp` | 国庆活动 |
| 49 | ObjAttrs | `CObjAttrs.cpp` | 对象属性 |
| 50 | ObjCarrier | `CObjCarrier.cpp` | 对象载具 |
| 51 | ObjState | `CObjState.cpp` | 对象状态 |
| 52 | OpenBeta | `COpenBeta.cpp` | 开服活动 |
| 53 | RankMirror | `CRankMirror.cpp` | 排行榜镜像 |
| 54 | RefreshMonster | `CRefreshMonster.cpp` | 刷新怪物 |
| 55 | RongHe | `CRongHe.cpp` | 融合 |
| 56 | RongLian | `CRongLian.cpp` | 熔炼 |
| 57 | SevenDayTask | `CSevenDayTask.cpp` | 七日任务 |
| 58 | ShenWei | `CShenWei.cpp` | 神威 |
| 59 | ShiZhuang | `CShiZhuang.cpp` | 时装 |
| 60 | SqiderQueen | `CSqiderQueen.cpp` | 蜘蛛女王 |
| 61 | SuperTeHui | `CSuperTeHui.cpp` | 超级特惠 |
| 62 | Territory | `CTerritory.cpp` | 领土战 |
| 63 | TestServerReward | `CTestServerReward.cpp` | 测试服奖励 |
| 64 | TreasureMap | `CTreasureMap.cpp` | 藏宝图 |
| 65 | UniteServer | `CUniteServer.cpp` | 合服 |
| 66 | VipClub | `CVipClub.cpp` | Vip俱乐部 |
| 67 | Vplan | `CVplan.cpp` | V计划 |
| 68 | Wan360 | `CWan360.cpp` | 360平台 |
| 69 | WuHunShop | `CWuHunShop.cpp` | 武魂商店 |
| 70 | XinMaiMap | `CXinMaiMap.cpp` | 心法地图 |
| 71 | XinMo | `CXinMo.cpp` | 心魔 |
| 72 | XingMai | `CXingMai.cpp` | 星脉 |
| 73 | YaBiao | `CYaBiao.cpp` | 押镖 |

> **注意**: 以上列表来自 `gameserver/decompiled/` 目录扫描。部分模块可能已有部分实现在现有 `.cpp/.h` 文件中，需要进一步确认。

## 配置表文件

`gameserver/ServerConfig/Tables/` 目录包含游戏配置表（TXT格式），当前已支持的配置表包括：
- 活动(Activity)、物品(Item)、怪物(Monster)、地图(Map)、技能(Skill) 等核心表
- GuardPrivilege(护卫特权)、SpecialEquip(特殊装备)、BlackMarket(黑市)、TianLing(天灵)、OutLinkFestival(外部活动) 等新模块表

所有配置表在 `gameserver/CfgData.cpp` 的 `init()` 函数中加载。
