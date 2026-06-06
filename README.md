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

### 已移植模块 (59/88)

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
| 44 | **CTreasureMap** (宝藏图) | `TreasureMap.cpp/.h` | CExtSystemBase，14 方法，藏宝图事件/奖励/特殊宝藏 |
| 45 | **CKunExt** (鲲扩展) | `CKunExt.cpp/.h` | CExtSystemBase，30 方法，灵珠/丹田/套装/炼化 |
| 46 | **CXinMo** (心魔系统) | `CXinMo.cpp/.h` | CExtSystemBase，36 方法，七情/装备进化/心情系统 |
| 47 | **CDaTingReward** (答题奖励) | `CDaTingReward.cpp/.h` | CExtSystemBase，31 方法，平台答题奖励系统 |
| 48 | **CKiaFuRecharge** (开服充值) | `CKiaFuRecharge.cpp/.h` | 24 方法，开服充值活动（累计充值/连充/抽奖/消费） |
| 49 | **CMonthlyChouJiang** (月抽奖) | `CMonthlyChouJiang.cpp/.h` | CExtSystemBase，18 方法，月度抽奖/充值积分/随机奖励 |
| 50 | **CXingMai** (星脉) | `CXingMai.cpp/.h` | CExtSystemBase，10 方法，星脉升级/星脉槽激活/BOSS积分系统 |
| 51 | **CWan360** (360运营) | `CWan360.cpp/.h` | CExtSystemBase，21 方法，360加速球/游戏App/搜狗皮肤/微信/急速奖励 |
| 52 | **CXinMaiMap** (星脉地图) | `CXinMaiMap.cpp/.h` | CActivity，17 方法，星脉地图活动/BOSS/复活/采集 |
| 53 | **CWuHunShop** (武魂商店) | `CWuHunShop.cpp/.h` | CExtSystemBase，16 方法，武魂商店购买/刷新/随机刷新 |
| 54 | **CRefreshMonster** (刷新怪物) | `CRefreshMonster.cpp/.h` | CActivity，7 方法，定时刷怪活动/公告广播 |
| 55 | **CTerritory** (领土) | `CTerritory.cpp/.h` | Map 子类，8 方法，家族领土地图/BOSS/怪物管理 |
| 56 | **CTestServerReward** (测试服奖励) | `CTestServerReward.cpp/.h` | CExtSystemBase，8 方法，测试服奖励领取系统 |
| 57 | **CVipClub** (VIP俱乐部) | `CVipClub.cpp/.h` | 全局单例，5 方法，VIP俱乐部成员管理/等级计算/荣誉墙 |
| 58 | **CCardGroupBox** (卡牌礼盒) | `CCardGroupBox.cpp/.h` | CCardGroupBox(5方法)+CCardGroupBoxManager(2方法)，卡牌礼盒随机抽卡/洗牌 |
| 59 | **CHttpRequest** (HTTP请求) | `CHttpRequest.cpp/.h` | Answer::Thread 子类，9 方法，HTTP GET 请求/线程队列/URL编码/DNS解析 |

### 待移植模块 (0)
所有 16 个反编译待移植模块已全部完成。

## 已修复的 TODO 项

### ✅ GuiGuDaoRen.cpp — 鬼谷道人系统

| 修复项 | 状态 | 说明 |
|-------|------|------|
| BOSS 刷新 (OnBackItem) | ✅ 已实现 | POOL_MANAGER.pop<Monster> + init + SetLifeTime + Map::addMonster |
| 物品回收DB存根 (UpdateBackItemCount) | ✅ 注释改进 | 引用反编译代码中的 DBService::SaveGuiGuDaoRenData |
| 装备回收DB存根 (UpdateEquipCount) | ✅ 注释改进 | 引用反编译代码中的 DBService::SaveBackEquipCount |
| 排行榜DB存根 (UpdateRankDate) | ✅ 注释改进 | 引用反编译代码中的 DBService::SaveBackEQuipRank |
| 每日重置公告 (OnNewMinute) | ✅ 已实现 | SM_SEND_NOTICE_PARAM + worldBroadcast (GongGao 541/542) |
| 排行榜邮件奖励 (OnNewMinute) | ✅ 已实现 | DB_SERVICE.OnSendSysMail 发放排名称号 |
| MapManager::ResetMapMonster | ✅ 已实现 | 遍历所有地图，重置怪物复活时间表 |
| 融合统计DB (UpdateRongHeCount) | ✅ 已实现 | MySqlDBGuard 直接 SQL (sys_server_config) |
| 融合记录DB (SaveRecordToDB) | ✅ 已实现 | MySqlDBGuard TRUNCATE + INSERT INTO |

### ✅ Monster — SetLifeTime 方法

- 新增 `Monster::SetLifeTime(int32_t nReviveTime)` 设置怪物复活/消失时间

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
| `ZongHeYunYingHD.cpp` | sendPacket API 不可用，DBService::OnSendSysMail 不可用 | ✅ 已修复 |
| `GuardPrivilege.cpp` | 平台检测存根，DBService 调用不可用 | ✅ 已修复 |
| `SevenDayTask.cpp` | 缺少跨模块调用（翅膀/爵位/装备等级） | 低 |
| `YunYingHD.cpp` | MobilePhoneGift/SuperMember/ZeroBuyPet 基础架构未移植 | ✅ 已修复（CFG类型已添加，部分逻辑已实现） |
| `RankMirror.cpp` | Title 系统集成存根 | ✅ 已修复 |
| `KaiFuHuoDong.cpp` | 翅膀模块引用被硬编码为 0 | ✅ 已修复 |
| `CLittleHelper.cpp` | 掉落拾取功能为存根 | ✅ 已修复 |
| `SevenDayTask.cpp` | 缺少跨模块调用（翅膀/爵位/装备等级） | ✅ 已修复 |
| `CMingGeExt.cpp` | DB 持久化为空（CMingGeData 独立管理持久化，注释已澄清） | ✅ 已修复 |
| `Equip.cpp` | 魔符/解绑功能有 TODO | ✅ 已修复 |

### 已修复的编译问题

- 所有 `#if 0` 块已解除（最后 2 个在 `LittleHelperCard.cpp` 和 `CLittleHelperData.cpp`）
- 所有源文件编译通过，0 个错误
- 仅有 2 个预存在错误（`IDCR_DUNGEON` 和 `GetEVeryDayChongZhiIconState` 拼写错误），与移植工作无关

## 配置表文件

`gameserver/ServerConfig/Tables/` 目录包含游戏配置表（TXT格式），当前已支持的配置表包括：
- 活动(Activity)、物品(Item)、怪物(Monster)、地图(Map)、技能(Skill) 等核心表
- 各移植模块的专用配置表

部分配置表的解析在 `cfgdata_new_stubs.cpp` 中仍为存根（仅打开文件，未解析字段）。
