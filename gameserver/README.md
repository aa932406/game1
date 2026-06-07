# GameServer

> C++ 游戏服务端 — 支持多连接网关架构、跨服战斗、世界Boss等核心玩法

## 架构

```
                          ┌─────────────────────────────────────────┐
                          │            Game Server (Main)           │
                          │                                         │
  ┌──────────┐  ×1~100   │  ┌─────────────────────────────────┐    │
  │   Gate   │◄──────────►│  │        GameService              │    │
  │  Server  │  MutiConn  │  │  ┌───────────────────────────┐  │    │
  └──────────┘            │  │  │ m_users[MAX_GATE×MAX_CONN] │  │    │
                          │  │  │ broadcast / sendPacket     │  │    │
                          │  │  │ ~40 new functions          │  │    │
                          │  │  └───────────────────────────┘  │    │
                          │  └─────────────────────────────────┘    │
                          │                    │                    │
                          │                    ▼                    │
                          │  ┌─────────────────────────────────┐    │
  ┌──────────┐  ×1~N     │  │         DBService               │    │
  │ Database │◄──────────►│  │  MutiConn<DBService> × N        │    │
  │          │  MutiConn  │  │  28 message handlers            │    │
  └──────────┘            │  │  insert/update/delete × connid  │    │
                          │  └─────────────────────────────────┘    │
                          │                                         │
                          │  ┌─────────────────────────────────┐    │
                          │  │          CfgData                │    │
                          │  │  247+ Init functions            │    │
                          │  │  7800+ lines header             │    │
                          │  └─────────────────────────────────┘    │
                          └─────────────────────────────────────────┘
```

## 模块总览

### 核心服务

| 模块 | 文件 | 说明 |
|------|------|------|
| 主入口 | `Main.cpp` | 服务启动、信号处理 |
| 游戏服务 | `GameService.h/cpp` | 多Gate连接管理、消息分发、玩家会话 |
| 数据库服务 | `DBService.h/cpp` | 多连接DB架构、28种消息处理 |
| 多连接模板 | `MutiConn.h` | `MutiConn<T>` TcpClient子类，支持多连接转发 |
| 配置数据 | `CfgData.h/cpp` | 247个Init函数，24000+行配置加载 |
| 数据结构 | `DataStructs.h` | 公共结构体定义 |
| DB数据操作 | `DBData.h/cpp` | DB读写封装 |

### 玩家与角色

| 模块 | 文件 | 说明 |
|------|------|------|
| 玩家 | `Player.h/cpp` | 角色属性、装备、技能、状态 |
| 用户 | `User.h/cpp` | 账号连接、认证 |
| 技能 | `Skill.h/cpp` | 技能系统 |
| 称号 | `CharTitle.h/cpp` | 称号系统 |
| 翅膀 | `CharWing.h/cpp` | 翅膀系统 |
| 法宝 | `FaBao.h/cpp` | 法宝系统 |
| 武魂 | `CharWuHun.h/cpp` | 武魂系统 |
| 坐骑 | `CharCarrier.h/cpp` | 坐骑系统 |
| 宠物 | `CharPet.h/cpp` / `ObjPet.h/cpp` | 宠物出战/实体 |
| 灵魂 | `CharSoul.h/cpp` | 灵魂系统 |

### 装备与物品

| 模块 | 文件 | 说明 |
|------|------|------|
| 装备管理 | `EquipManager.h/cpp` | ID缓存、多连接感知、装备广播 |
| 装备找回 | `EquipBack.h/cpp` | 装备找回系统 |
| 装备赎回 | `EquipRansom.h/cpp` | 装备赎回 |
| 特殊装备 | `SpecialEquip.h/cpp` | 特殊装备 |
| 背包 | `Bag.h/cpp` | 物品背包管理 |
| 道具效果 | `ItemEffect.h/cpp` | 8+子类道具效果（灵珠/进化/祝福水等） |
| 道具辅助 | `ItemHelper.h/cpp` | 道具辅助工具 |
| 道具Buff | `ItemBuff.h/cpp` | 道具Buff |
| 仓库 | `ChrDepot.h/cpp` | 角色仓库 |
| 商城 | `ShangCheng.h/cpp` | 商城系统 |

### 宠物系统

| 模块 | 文件 | 说明 |
|------|------|------|
| 宠物管理 | `PetManager.h/cpp` | ID缓存、排名缓存、多连接感知 |
| 宠物 | `Pet.h/cpp` | 宠物数据 |
| 宠物蛋 | `PetEgg.h/cpp` | 宠物蛋孵化 |

### 战斗与地图

| 模块 | 文件 | 说明 |
|------|------|------|
| 世界Boss | `WorldBoss.h/cpp` | DB持久化、Boss升级、掉落记录、遗迹Boss |
| 怪物 | `Monster.h/cpp` | 怪物生成与AI |
| 地图 | `Map.h/cpp` | 地图管理 |
| 地图管理 | `MapManager.h/cpp` | 多地图实例管理 |
| 战斗 | `Fighting.h/cpp` | 战斗计算 |
| 战斗检查 | `FightChecker.h/cpp` | 战斗规则校验 |
| 副本 | `Dungeon.h/cpp` | 副本系统 |
| 怪物副本 | `MonsterDungeon.h/cpp` | 怪物副本 |
| 怪物Buff | `MonsterBuff.h/cpp` | 怪物Buff |
| 陷阱 | `Trap.h/cpp` | 陷阱系统 |
| 路径 | `PathFinder.h/cpp` | A*寻路 |
| 地图格 | `Tile.h/cpp` | 地图格子 |

### 活动系统

| 模块 | 文件 | 说明 |
|------|------|------|
| 活动 | `Activity.h/cpp` | 活动基类 |
| 活动管理 | `ActivityManager.h/cpp` | 活动调度 |
| 活动地图 | `ActivityMap.h/cpp` | 活动地图 |
| 世界Boss活动 | `ActivityWorldBoss.h/cpp` | 世界Boss活动 |
| 开服活动 | `KaiFuHuoDong.h/cpp` | 开服活动 |
| 开服Boss | `KaiFuBoss.h/cpp` | 开服Boss |
| 节日活动 | `FestivalActivity.h/cpp` | 节日活动 |
| 双十一 | `FestivalDoubleEleven.h/cpp` | 双十一活动 |
| 国庆活动 | `NationalDayHd.h/cpp` | 国庆活动 |
| 每日活动 | `DailyActivity.h/cpp` | 每日活动 |
| 七日任务 | `SevenDayTask.h/cpp` | 七日任务 |
| 活跃度 | `HuoYueDu.h/cpp` | 活跃度系统 |
| 运营活动 | `YunYingHD.h/cpp` / `ZongHeYunYingHD.h/cpp` | 运营活动/综合运营活动 |

### 社交与公会

| 模块 | 文件 | 说明 |
|------|------|------|
| 家族 | `FamilyManager.h/cpp` | 家族管理 |
| 家族战 | `FamilyWar.h/cpp` | 家族战 |
| 家族之光 | `FamilyLight.h/cpp` | 家族之光 |
| 城战 | `CityWar.h/cpp` | 城战 |
| 阵营战 | `CampWar.h/cpp` | 阵营战 |
| 公会领地 | `CTerritory.h/cpp` | 领地战 |
| 领地战 | `TerritoryWar.h/cpp` | 领地争夺 |
| 跨服 | `UniteServer.h/cpp` | 跨服通信 |
| 好友经验 | `FriendExpReward.h/cpp` | 好友经验奖励 |

### 任务与成就

| 模块 | 文件 | 说明 |
|------|------|------|
| 任务 | `Task.h/cpp` | 主线/支线任务 |
| 循环任务 | `TaskCycle.h/cpp` | 循环任务 |
| 成就 | `Achievement.h/cpp` | 成就系统 |

### 经济系统

| 模块 | 文件 | 说明 |
|------|------|------|
| 货币 | `Currency.h/cpp` | 货币管理 |
| 交易 | `Trade.h/cpp` | 玩家交易 |
| 拍卖 | `CharAuction.h/cpp` | 拍卖行 |
| 黑市 | `BlackMarket.h/cpp` | 黑市 |
| 神秘商店 | `CharMysteryShop.h/cpp` | 神秘商店 |
| 抽奖 | `ChouJiang.h/cpp` | 抽奖系统 |
| 翻牌 | `FlopDraw.h/cpp` | 翻牌抽奖 |
| 充值 | `CKiaFuRecharge.h/cpp` | 充值系统 |
| VIP | `Vip.h/cpp` | VIP系统 |
| VIP挂机 | `VipGuaJi.h/cpp` | VIP挂机 |
| VIP俱乐部 | `CVipClub.h/cpp` | VIP俱乐部 |
| 积分商店 | `ScoreShop.h/cpp` | 积分商店 |
| 捐赠 | `QiFu.h/cpp` | 祈福捐赠 |
| 投资 | `TouZi.h/cpp` | 投资系统 |

### 扩展系统

| 模块 | 文件 | 说明 |
|------|------|------|
| 心魔 | `CXinMo.h/cpp` | 心魔系统 |
| 星脉 | `CXingMai.h/cpp` | 星脉系统 |
| 融合 | `RongHe.h/cpp` | 融合系统 |
| 熔炼 | `RongLian.h/cpp` | 熔炼系统 |
| 共鸣 | `GongMing.h/cpp` | 共鸣系统 |
| 诅咒 | `Curse.h/cpp` | 诅咒系统 |
| 守护特权 | `GuardPrivilege.h/cpp` | 守护特权 |
| 神威 | `ShenWei.h/cpp` | 神威系统 |
| 天灵 | `TianLing.h/cpp` | 天灵系统 |
| 等级精炼 | `LevelRefining.h/cpp` | 等级精炼 |
| 时装 | `ShiZhuang.h/cpp` | 时装系统 |
| 光环 | `FamilyLight.h/cpp` | 家族光环 |
| 魔灵入侵 | `MoLingRuQin.h/cpp` | 魔灵入侵 |
| 妖后 | `SpiderQueen.h/cpp` | 妖后Boss |
| 跨服塔 | `CrossTower.h/cpp` | 跨服爬塔 |
| 无双战 | `PeerlessWar.h/cpp` | 无双战 |
| 终极挑战 | `UltimateChallenge.h/cpp` | 终极挑战 |
| 小助手 | `CLittleHelper.h/cpp` | 小助手系统 |
| 经验球 | `ExpBall.h/cpp` | 经验球 |
| 邮件 | `PlayerMail.h/cpp` | 邮件系统 |
| NPC | `Npc.h/cpp` | NPC系统 |
| 掉落 | `DropItem.h/cpp` | 掉落系统 |
| 精灵 | `Goblin.h/cpp` | 精灵系统 |
| 机器人 | `PlayerRobot.h/cpp` | 挂机AI |

### Buff与效果

| 模块 | 文件 | 说明 |
|------|------|------|
| Buff | `Buff.h/cpp` | 增益/减益效果 |
| 技能Buff | `SkillBuff.h/cpp` | 技能产生Buff |
| 持久Buff | `PersistBuff.h/cpp` | 持久化Buff |
| 副本Buff | `DungeonBuff.h/cpp` | 副本Buff加成 |

### 工具与辅助

| 模块 | 文件 | 说明 |
|------|------|------|
| 日志 | `GameLogs.h/cpp` | 游戏日志系统 |
| DBC文件 | `CDBCFile.h/cpp` | DBC配置文件读取 |
| HTTP请求 | `CHttpRequest.h/cpp` | HTTP客户端 |
| URL服务 | `URLService.h/cpp` | URL短链服务 |
| 腾讯接口 | `Tencent.h/cpp` | 腾讯平台对接 |
| GM后台 | `GMBackstage.h/cpp` | GM管理后台 |
| 定时器 | `Timer.h/cpp` | 定时器系统 |
| 计时 | `DaTiHD.h/cpp` | 答题活动 |

## 2019 版本升级

### 多连接架构重构

原始架构为单连接模式，2019版重构为多连接网关架构：

**GameService**
- 从单连接改为 `MutiConn<GameService>` 多连接管理
- `m_users[MAX_GATE_CONNS × MAX_CONNECTION]` 支持最多100个Gate
- 新增 `GetConn(connid)` / `GetAutoConnId()` / `sendPacket(connid)` 等多连接感知函数
- 新增广播：`broadcastActivityState` / `broadcastToFamily` / `FamilyBroadcast`
- 新增 Drop 控制、Chat 验证、城战称号等 ~40个新函数

**DBService**
- 从继承 `TcpService` 改为管理多个 `MutiConn<DBService>` 连接
- 所有函数增加 `int8_t connid` 参数
- `onNetPacket` 从 13 个 case 扩展到 28 个 case

**ID 缓存机制**
- `ServerNewId` / `PetNewId` 结构体：`{nNextId, nMaxId}` 批量缓存ID范围
- `m_mNewId` map + `m_IdLock` 读写锁
- `getEquipId` / `getPetId` 不再每次查DB，改为批量缓存
- `getEquipIdFromDB` / `getPetIdFromDB` 区分跨服模式（line==9 → serverId=0）

### 升级进度

| 模块 | 状态 | 说明 |
|------|------|------|
| DBService | ✅ 完成 | 多连接架构，28种消息 |
| GameService | ✅ 完成 | 多Gate连接，~40新函数 |
| EquipManager | ✅ 完成 | ID缓存，多连接感知，装备广播 |
| PetManager | ✅ 完成 | ID缓存，排名缓存，多连接感知 |
| WorldBoss | ✅ 完成 | DB持久化，Boss升级，掉落记录，遗迹Boss |
| Monster | ✅ 完成 | 新增 OnLevelUp |
| EquipBack | ⏳ 待做 | 装备找回 |
| FamilyManager | ⏳ 待做 | 家族系统 |
| CfgData 93函数 | ⏳ 待做 | 反编译风格 → 干净版重写 |

### 新增协议

协议码定义在 `../share/PDUDefine.h`，2019新增：

| 协议 | 码值 | 说明 |
|------|------|------|
| `SM_SEND_DROP_RECORD` | 11990 | 掉落记录 |
| `SM_SEND_RUINS_BOSS_INFO` | 11991 | 遗迹Boss信息 |
| `SM_SEND_RUINS_BOSS_CHANGE` | 11992 | 遗迹Boss变化 |

## 编译

**依赖**
- C++11 或更高
- Linux 平台
- 共享头文件：`../share/`（含 `PDUDefine.h` 等协议定义）

**配置**
- 服务配置：`ServerConfig/Config/`
- 数据表：`ServerConfig/Tables/`

## 项目规模

| 指标 | 数值 |
|------|------|
| 源文件 | 187 对 (.h + .cpp) |
| 总代码行 | ~164,000 行 |
| CfgData.cpp | 24,685 行 |
| CfgData.h | 7,889 行 |
| 配置Init函数 | 247 个 |
