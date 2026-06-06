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

## 模块移植进度

从反编译代码 (`gameserver/decompiled/`) 中移植缺失模块到当前代码库。

### 已移植模块 (43/88)

| # | 模块 | 源文件 | 说明 |
|---|------|--------|------|
| 1 | **GuardPrivilege** (护卫特权) | `GuardPrivilege.cpp/.h` | CExtSystemBase，购买/DB回调/图标推送 |
| 2 | **SpecialEquip** (特殊装备) | `SpecialEquip.cpp/.h` | CExtSystemBase，等级判定/激活/升级 |
| 3 | **BlackMarket** (黑市) | `BlackMarket.cpp/.h` | CExtSystemBase，入场/购买/广播 |
| 4 | **TianLing** (天灵系统) | `TianLing.cpp/.h` | CExtSystemBase，3 子系统 |
| 5 | **OutLinkFestival** (外部链接活动) | `OutLinkFestival.cpp/.h` | 全局单继，活动图标推送 |
| 6 | **KaiFuHuoDong** (开服活动) | `KaiFuHuoDong.cpp/.h` | CExtSystemBase，44 方法 |
| 7 | **UniteServer** (合服) | `UniteServer.cpp/.h` | 全局单继，41 方法 |
| 8 | **Tencent** (腾讯平台) | `Tencent.cpp/.h` + `TencentTable.cpp/.h` | CExtSystemBase，55 方法 |
| 9 | **CExtCharBag** (背包系统) | `Bag.cpp/.h` | CExtSystemBase，80+ 方法 |
| 10 | **CCityWar** (城战) | `CityWar.cpp/.h` | CActivity 子类，42 方法 |
| 11 | **CCampWar** (阵营战) | `CampWar.cpp/.h` | CActivity 子类，28 方法 |
| 12 | **CWorldBoss** (世界BOSS) | `WorldBoss.cpp/.h` | 全局单继，23 方法 |
| 13 | **CExtCharCarrier** (护送) | `CharCarrier.cpp/.h` + `ObjCarrier.cpp/.h` | CExtSystemBase，29 方法 |
| 14 | **CExtCharDraw** (抽卡) | `CharDraw.cpp/.h` | CExtSystemBase，7 方法 |
| 15 | **CExtCharExchange** (兑换) | `CharExchange.cpp/.h` | CExtSystemBase，11 方法 |
| 16 | **CExtCharMysteryGift** (神秘礼物) | `CharMysteryGift.cpp/.h` | CExtSystemBase，15 方法 |
| 17 | **CExtCharMysteryShop** (神秘商店) | `CharMysteryShop.cpp/.h` | CExtSystemBase，15 方法 |
| 18 | **CExtCharJueWei** (爵位) | `JueWei.cpp/.h` | CExtSystemBase，16 方法 |
| 19 | **CExtCharPortal** (传送门) | `CharPortal.cpp/.h` | CExtSystemBase，15 方法 |
| 20 | **CExtCharTitle** (称号) | `CharTitle.cpp/.h` | CExtSystemBase，28 方法 |
| 21 | **CExtCharWing** (翅膀) | `CharWing.cpp/.h` | CExtSystemBase，15 方法 |
| 22 | **CExtMagicBox** (魔盒) | `MagicBox.cpp/.h` | CExtSystemBase，23 方法 |
| 23 | **CVplan** (V计划) | `Vplan.cpp/.h` | CExtSystemBase，50+ 方法 |
| 24 | **CNationalDayHd** (国庆活动) | `NationalDayHd.cpp/.h` | CExtSystemBase，20+ 方法 |
| 25 | **CSevenDayTask** (七日任务) | `SevenDayTask.cpp/.h` | CExtSystemBase，14 方法 |
| 26 | **CDaZheQuan** (打折券) | — | ItemEffect 子类 |
| 27 | **CRongLian** (熔炼活动) | `RongLian.cpp/.h` | CActivity 子类 |
| 28 | **CYaBiao** (押镖) | `YaBiao.cpp/.h` | CActivity 子类 |
| 29 | **CShenWei** (神威) | `ShenWei.cpp/.h` | CExtSystemBase，5 方法 |
| 30 | **CRongHe** (融合) | `RongHe.cpp/.h` | CExtSystemBase，15 方法 |
| 31 | **CShiZhuang** (时装) | `ShiZhuang.cpp/.h` | CExtSystemBase，26 方法 |
| 32 | **CExtFlopDraw** (翻牌抽奖) | `FlopDraw.cpp/.h` | CExtSystemBase，11 方法 |
| 33 | **CCharWuHun** (武魂) | `CharWuHun.cpp/.h` | CExtSystemBase，12 方法 |
| 34 | **CBossKilledReward** (BOSS击杀奖励) | `BossKilledReward.cpp/.h` | CExtSystemBase，12 方法 |
| 35 | **CGuiGuDaoRen** (鬼谷道人) | `GuiGuDaoRen.cpp/.h` | 全局单继，19 方法 |
| 36 | **CLittleHelper** (小助手) | `CLittleHelper.cpp/.h` + `CLittleHelperData.cpp/.h` + `CharLittlerHelper.cpp/.h` + `LittleHelperCard.cpp/.h` | Entity+CExtSystemBase，30+ 方法 |
| 37 | **CMingGeExt** (命格) | `CMingGeExt.cpp/.h` + `CMingGeData.cpp/.h` + `CMingGeTable.cpp/.h` + `MingGeItem/Chip/Exp` | CExtSystemBase，30+ 方法（新建） |
| 38 | **CLevelRefining** (等级精炼) | `LevelRefining.cpp/.h` | CExtSystemBase，10 方法 |
| 39 | **CVipGuaJi** (VIP挂机) | `VipGuaJi.cpp/.h` | 全局单继，时间检查/图标状态 |
| 40 | **CActivityWorldBoss** (世界BOSS活动) | `ActivityWorldBoss.cpp/.h` | CActivity 子类，积分/排名/奖励 |
| 41 | **CPeerlessWar** (绝世战) | `PeerlessWar.cpp/.h` | CActivity 子类 |
| 42 | **CTrailer** (拖车) | `Trailer.cpp/.h` | Unit 子类，move/appendInfo/init |
| 43 | **CVip** (VIP系统) | `Vip.cpp/.h` | 核心系统，等级/特权 |

### 待移植模块 (18)

以下模块在反编译代码 (`gameserver/decompiled/`) 中存在完整实现，但尚未移植到当前代码库。

| # | 模块 | 反编译源 | 类名 | 行数 | 方法数 | 说明 |
|---|------|----------|------|------|--------|------|
| 1 | **TreasureMap** (宝藏图) | `CTreasureMap.cpp` | CTreasureMap | 801 | 14 | CExtSystemBase，藏宝图事件/奖励/特殊宝藏 |
| 2 | **KunExt** (鲲扩展) | `CKunExt.cpp` | CKunExt | 1466 | 30 | CExtSystemBase，鲲培养/进化/技能 |
| 3 | **XinMo** (心魔) | `CXinMo.cpp` | CXinMo | 1540 | 36 | 心魔系统，心魔战斗/培养 |
| 4 | **DaTingReward** (答题奖励) | `CDaTingReward.cpp` | CDaTingReward | 1179 | 31 | CExtSystemBase，答题活动/奖励发放 |
| 5 | **KiaFuRecharge** (开服充值) | `CKiaFuRecharge.cpp` | CKiaFuRecharge | 968 | 24 | 开服充值活动，档位/奖励 |
| 6 | **OpenBeta** (开服活动) | `COpenBeta.cpp` | COpenBeta | 3017 | 44 | 开服系列活动（部分已合并到 KaiFuHuoDong） |
| 7 | **SuperTeHui** (超级特惠) | `CSuperTeHui.cpp` | CSuperTeHui | 571 | 22 | 超级特惠活动，限时购买 |
| 8 | **Wan360** (360运营) | `CWan360.cpp` | CWan360 | 550 | 21 | 360平台运营活动 |
| 9 | **WuHunShop** (武魂商店) | `CWuHunShop.cpp` | CWuHunShop | 442 | 16 | 武魂相关商品购买/兑换 |
| 10 | **MonthlyChouJiang** (月抽奖) | `CMonthlyChouJiang.cpp` | CMonthlyChouJiang | 469 | 18 | 月度抽奖活动 |
| 11 | **XingMai** (星脉) | `CXingMai.cpp` | CXingMai | 268 | 10 | 星脉系统 |
| 12 | **XinMaiMap** (星脉地图) | `CXinMaiMap.cpp` | CXinMaiMap | 289 | 17 | 星脉地图系统 |
| 13 | **RefreshMonster** (刷新怪物) | `CRefreshMonster.cpp` | CRefreshMonster | 244 | 7 | CActivity 子类，定时刷怪活动 |
| 14 | **Territory** (领土) | `CTerritory.cpp` | CTerritory | 290 | 8 | 领土系统 |
| 15 | **TestServerReward** (测试服奖励) | `CTestServerReward.cpp` | CTestServerReward | 254 | 8 | 测试服奖励发放 |
| 16 | **VipClub** (VIP俱乐部) | `CVipClub.cpp` | CVipClub | 296 | 5 | VIP俱乐部特权 |
| 17 | **CardGroupBox** (卡牌礼盒) | `CCardGroupBox.cpp` | CCardGroupBox + CCardGroupBoxManager | 202 | 7 | 卡牌礼盒抽卡逻辑 |
| 18 | **HttpRequest** (HTTP请求) | `CHttpRequest.cpp` | CHttpRequest | 258 | 9 | HTTP请求工具类 |

### 原有的核心系统（非反编译移植）

| 模块 | 文件 | 说明 |
|------|------|------|
| Player | `Player.cpp/.h` | ~9000 行，玩家主类 |
| Map/MapManager | `Map.cpp/.h`, `MapManager.cpp/.h` | 地图系统 |
| Monster | `Monster.cpp/.h` | 怪物系统 |
| Skill | `Skill.cpp/.h` | 技能系统 |
| Buff | `Buff.cpp/.h`, `SkillBuff.cpp/.h` | Buff 系统 |
| Activity/ActivityManager | `Activity.cpp/.h`, `ActivityManager.cpp/.h` | 活动框架 |
| Entity/Unit | `Entity.h`, `Unit.h/cpp` | 实体基类 |
| Timer | `Timer.cpp/.h` | 定时器 |
| CfgData | `CfgData.cpp/.h` | 配置数据 |
| GameService | `GameService.cpp/.h` | 游戏服务 |
| DBService | `DBService.cpp/.h` | 数据库服务 |
| ItemHelper | `ItemHelper.cpp/.h` | 物品辅助 |
| DropItem | `DropItem.cpp/.h` | 掉落物 |
| PathFinder | `PathFinder.cpp/.h` | 寻路 |
| Trade | `Trade.cpp/.h` | 交易 |
| Mail | `PlayerMail.cpp/.h` | 邮件 |
| Dungeon | `Dungeon.cpp/.h` | 副本 |
| 等等... | 80+ 文件 | |

### 已知 TODO 项

| 文件 | 问题 | 严重程度 |
|------|------|----------|
| `cfgdata_new_stubs.cpp` | ~65 个 `Init*Table()` 配置表解析未实现（仅打开文件，未解析字段） | **中** |
| `GuiGuDaoRen.cpp` | DB 持久化未实现（3 处），BOSS 刷新未实现，公告未发送 | 中 |
| `RongHe.cpp` | 装备熔炼/拆卸/回收为空存根（返回 10002） | 中 |
| `ZongHeYunYingHD.cpp` | sendPacket API 不可用，DBService::OnSendSysMail 不可用 | 中 |
| `GuardPrivilege.cpp` | 平台检测存根，DBService 调用不可用 | 低 |
| `SevenDayTask.cpp` | 缺少跨模块调用（翅膀/爵位/装备等级） | 低 |
| `YunYingHD.cpp` | MobilePhoneGift/SuperMember/ZeroBuyPet 基础架构未移植 | 低 |
| `RankMirror.cpp` | Title 系统集成存根 | 低 |
| `KaiFuHuoDong.cpp` | 翅膀模块引用被硬编码为 0 | 低 |
| `CLittleHelper.cpp` | 掉落拾取功能为存根 | 低 |
| `CMingGeExt.cpp` | DB 持久化为空 | 低 |
| `Equip.cpp` | 魔符/解绑功能有 TODO | 低 |

### 已修复的编译问题

- 所有 `#if 0` 块已解除（最后 2 个在 `LittleHelperCard.cpp` 和 `CLittleHelperData.cpp`）
- 所有源文件编译通过，0 个错误
- 仅有 2 个预存在错误（`IDCR_DUNGEON` 和 `GetEVeryDayChongZhiIconState` 拼写错误），与移植工作无关

## 配置表文件

`gameserver/ServerConfig/Tables/` 目录包含游戏配置表（TXT格式），当前已支持的配置表包括：
- 活动(Activity)、物品(Item)、怪物(Monster)、地图(Map)、技能(Skill) 等核心表
- 各移植模块的专用配置表

部分配置表的解析在 `cfgdata_new_stubs.cpp` 中仍为存根（仅打开文件，未解析字段）。
