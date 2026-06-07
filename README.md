# GameServer

> C++ MMORPG 游戏服务器 — 2019 版本升级进行中

## 项目结构

```
/home/gameserver/
├── gameserver/          # 游戏逻辑服务器（主项目）
├── decompiled_backup/   # 反编译参考代码（405个文件，从 gameserver.cc 反编译）
├── lib/                 # 第三方库
├── libanswer/           # 基础网络框架库
├── mysql/               # MySQL 客户端库
├── pthread/             # POSIX 线程库
├── scripts/             # 运维脚本
├── share/               # 共享头文件（PDUDefine.h 等协议定义）
├── sqls/                # SQL 建表脚本
├── tests/               # 测试
└── zlib/                # 压缩库
```

## 编译

```bash
cd gameserver
make
```

依赖：pthread, libanswer, mysql, zlib

## 架构

```
                          ┌─────────────────────────────────────────┐
                          │            Game Server (Main)           │
                          │                                         │
  ┌──────────┐  ×1~100   │  ┌─────────────────────────────────┐    │
  │   Gate   │◄──────────►│  │        GameService              │    │
  │  Server  │  MutiConn  │  │  m_users[MAX_GATE×MAX_CONN]    │    │
  └──────────┘            │  │  broadcast / sendPacket(connid) │    │
                          │  │  ~40 new functions              │    │
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

## gameserver/ 模块总览

### 核心服务

| 模块 | 文件 | 说明 |
|------|------|------|
| 主入口 | `Main.cpp` | 服务启动、信号处理 |
| 游戏服务 | `GameService.h/cpp` | 多Gate连接管理、消息分发、玩家会话 |
| 数据库服务 | `DBService.h/cpp` | 多连接DB架构，28种消息处理 |
| 多连接模板 | `MutiConn.h` | `MutiConn<T>` TcpClient子类，按connid分发 |
| 配置数据 | `CfgData.h/cpp` | 247个Init函数，24000+行 |
| 数据结构 | `DataStructs.h` | 公共结构体定义 |
| DB数据操作 | `DBData.h/cpp` | 47+ DB数据类 |

### 玩家与角色

| 模块 | 文件 |
|------|------|
| 玩家 | `Player.h/cpp` |
| 技能 | `Skill.h/cpp` |
| 称号 | `CharTitle.h/cpp` |
| 翅膀 | `CharWing.h/cpp` |
| 法宝 | `FaBao.h/cpp` |
| 武魂 | `CharWuHun.h/cpp` |
| 坐骑 | `CharCarrier.h/cpp` |
| 宠物 | `CharPet.h/cpp` / `ObjPet.h/cpp` |
| 灵魂 | `CharSoul.h/cpp` |

### 装备与物品

| 模块 | 文件 |
|------|------|
| 装备管理 | `EquipManager.h/cpp` — ID缓存、多连接感知、装备广播 |
| 装备找回 | `EquipBack.h/cpp` |
| 背包 | `Bag.h/cpp` |
| 道具效果 | `ItemEffect.h/cpp` — 37个子类 |
| 仓库 | `ChrDepot.h/cpp` |
| 商城 | `ShangCheng.h/cpp` |

### 宠物系统

| 模块 | 文件 |
|------|------|
| 宠物管理 | `PetManager.h/cpp` — ID缓存、排名缓存、多连接感知 |
| 宠物 | `Pet.h/cpp` |
| 宠物蛋 | `PetEgg.h/cpp` |

### 战斗与地图

| 模块 | 文件 |
|------|------|
| 世界Boss | `WorldBoss.h/cpp` — DB持久化、Boss升级、掉落记录、遗迹Boss |
| 怪物 | `Monster.h/cpp` |
| 地图 | `Map.h/cpp` / `MapManager.h/cpp` |
| 战斗 | `Fighting.h/cpp` |
| 副本 | `Dungeon.h/cpp` |
| 寻路 | `PathFinder.h/cpp` |

### 社交与公会

| 模块 | 文件 |
|------|------|
| 家族 | `FamilyManager.h/cpp` |
| 家族战 | `FamilyWar.h/cpp` |
| 城战 | `CityWar.h/cpp` |
| 阵营战 | `CampWar.h/cpp` |
| 跨服 | `UniteServer.h/cpp` |

### 活动系统

| 模块 | 文件 |
|------|------|
| 活动框架 | `Activity.h/cpp` / `ActivityManager.h/cpp` |
| 开服活动 | `KaiFuHuoDong.h/cpp` / `KaiFuBoss.h/cpp` |
| 节日活动 | `FestivalActivity.h/cpp` / `FestivalDoubleEleven.h/cpp` |
| 每日活动 | `DailyActivity.h/cpp` / `HuoYueDu.h/cpp` |
| 运营活动 | `YunYingHD.h/cpp` / `ZongHeYunYingHD.h/cpp` |

### 经济系统

| 模块 | 文件 |
|------|------|
| 货币 | `Currency.h/cpp` |
| 交易 | `Trade.h/cpp` |
| 拍卖 | `CharAuction.h/cpp` |
| VIP | `Vip.h/cpp` / `CVipClub.h/cpp` |
| 充值 | `CKiaFuRecharge.h/cpp` |
| 商城 | `ShangCheng.h/cpp` / `CharMysteryShop.h/cpp` |

### 扩展系统

心魔(`CXinMo`) / 星脉(`CXingMai`) / 融合(`RongHe`) / 熔炼(`RongLian`) / 共鸣(`GongMing`) / 诅咒(`Curse`) / 神威(`ShenWei`) / 天灵(`TianLing`) / 等级精炼(`LevelRefining`) / 时装(`ShiZhuang`) / 魔灵入侵(`MoLingRuQin`) / 跨服塔(`CrossTower`) / 无双战(`PeerlessWar`) / 终极挑战(`UltimateChallenge`) / 公测活动(`OpenBeta`) 等 20+ 子系统

## 2019 版本升级

### 多连接架构重构

原始架构为单连接模式，2019版重构为多连接网关架构：

- **GameService**: `MutiConn<GameService>` 多连接管理，`m_users[MAX_GATE_CONNS × MAX_CONNECTION]`，~40新函数
- **DBService**: `MutiConn<DBService>` 多连接管理，28消息处理，connid参数
- **ID缓存**: `ServerNewId` / `PetNewId` 批量缓存ID范围
- **多连接感知**: 所有发送函数支持 connid + gateIndex

### 升级进度

| 模块 | 状态 | 说明 |
|------|------|------|
| DBService | ✅ 完成 | 多连接架构，28种消息 |
| GameService | ✅ 完成 | 多Gate连接，~40新函数 |
| EquipManager | ✅ 完成 | ID缓存，多连接感知，装备广播 |
| PetManager | ✅ 完成 | ID缓存，排名缓存，多连接感知 |
| WorldBoss | ✅ 完成 | DB持久化，Boss升级，掉落记录，遗迹Boss |
| Monster | ✅ 完成 | OnLevelUp |
| **EquipBack** | ⏳ **待做** | 装备找回（反编译1086行 vs 当前610行） |
| **FamilyManager** | ⏳ **待做** | 家族系统（反编译433行 vs 当前192行） |
| **OpenBeta** | ⏳ **待做** | 公测活动（20+空壳TODO） |
| **ItemEffect子类** | ⏳ **待做** | 6个TODO子类待完善 |
| **connid签名** | ⏳ **待做** | ~20+调用端文件需更新 |
| CfgData 93函数 | ⏳ 待做 | 反编译风格→干净版重写（优先级低） |

### 新增协议

| 协议 | 码值 | 说明 |
|------|------|------|
| `SM_SEND_DROP_RECORD` | 11990 | 掉落记录 |
| `SM_SEND_RUINS_BOSS_INFO` | 11991 | 遗迹Boss信息 |
| `SM_SEND_RUINS_BOSS_CHANGE` | 11992 | 遗迹Boss变化 |

## 项目规模

| 指标 | 数值 |
|------|------|
| gameserver/ 源文件 | 187 对 (.h + .cpp) |
| gameserver/ 总代码行 | ~164,000 |
| CfgData.cpp | 24,685 行 |
| CfgData.h | 7,889 行 |
| 配置Init函数 | 247 个 |
| 反编译参考 | 405 个文件 (decompiled_backup/) |

## 反编译参考

反编译源从 `gameserver.cc` (569,852行) 经 IDA/Ghidra 反编译后按类拆分：

- 命名映射：`C` 前缀 → 去掉（`CActivity` → `Activity`）
- 聚合文件：`Cfg*Table` → `CfgData`，`ItemEffect`子类 → `ItemEffect`，DB类 → `DBData`，日志类 → `GameLogs`
- 所有功能模块已移植完毕，待做项为 2019 新增逻辑的完善
