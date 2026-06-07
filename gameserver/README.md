# GameServer - 游戏服务端

## 项目简介

基于 C++ 的游戏服务端程序，支持多连接网关架构、跨服战斗、世界Boss等核心玩法。

## 架构概览

```
┌─────────────┐     ┌──────────────────┐     ┌─────────────┐
│  Gate Server │ ×N  │   Game Service   │────│  DB Service  │
│  (网关服务)  │◄───►│   (游戏逻辑)     │    │  (数据库服务) │
└─────────────┘     └──────────────────┘     └─────────────┘
```

### 核心模块

| 模块 | 文件 | 说明 |
|------|------|------|
| 游戏服务 | `GameService.h/cpp` | 多连接网关架构，支持最多100个Gate连接 |
| 数据库服务 | `DBService.h/cpp` | 多连接DB架构，28种消息处理 |
| 配置数据 | `CfgData.h/cpp` | 247+ 配置初始化函数，7889行头文件 |
| 装备系统 | `EquipManager.h/cpp` | ID缓存、多连接感知、装备广播 |
| 宠物系统 | `PetManager.h/cpp` | ID缓存、排名缓存、多连接感知 |
| 世界Boss | `WorldBoss.h/cpp` | DB持久化、Boss升级、掉落记录、遗迹Boss |
| 装备找回 | `EquipBack.h/cpp` | 装备找回系统 |
| 家族系统 | `FamilyManager.h/cpp` | 家族管理 |
| Buff系统 | `Buff.h/cpp` | 增益/减益效果 |
| 活动系统 | `Activity.h/cpp` | 各类活动逻辑 |
| 背包系统 | `Bag.h/cpp` | 物品背包管理 |
| 怪物系统 | `Monster.h/cpp` | 怪物生成与AI |
| 道具效果 | `ItemEffect.h/cpp` | 8+子类道具效果处理 |

### 多连接架构（2019重构）

- **GameService**: 从单连接改为 `MutiConn<GameService>` 多连接管理，`m_users[MAX_GATE_CONNS * MAX_CONNECTION]` 支持多Gate
- **DBService**: 从继承 `TcpService` 改为管理多个 `MutiConn<DBService>` 连接
- **ID缓存机制**: `ServerNewId` / `PetNewId` 批量缓存ID范围，避免每次查DB
- **多连接感知发送**: 所有网络发送函数支持 `connid` + `gateIndex` 参数

## 编译依赖

- C++11 或更高
- Linux 平台
- 项目共享头文件: `../share/`

## 目录结构

```
gameserver/
├── Main.cpp              # 入口
├── GameService.h/cpp     # 游戏主服务
├── DBService.h/cpp       # 数据库服务
├── CfgData.h/cpp         # 配置数据（24000+行）
├── EquipManager.h/cpp    # 装备管理
├── PetManager.h/cpp      # 宠物管理
├── WorldBoss.h/cpp       # 世界Boss
├── Monster.h/cpp         # 怪物
├── Player.h/cpp          # 玩家
├── Map.h/cpp             # 地图
├── Buff.h/cpp            # Buff系统
├── Bag.h/cpp             # 背包
├── Activity*.h/cpp       # 活动相关
├── FamilyManager.h/cpp   # 家族
├── ItemEffect.h/cpp      # 道具效果
├── MutiConn.h            # 多连接模板
├── DataStructs.h         # 数据结构定义
├── DBData.h/cpp          # DB数据操作
└── ServerConfig/         # 配置文件
```

## 2019 版本升级进度

| 模块 | 状态 | 说明 |
|------|------|------|
| DBService | ✅ 完成 | 多连接架构，28种消息 |
| GameService | ✅ 完成 | 多Gate连接，~40新函数 |
| EquipManager | ✅ 完成 | ID缓存，多连接感知 |
| PetManager | ✅ 完成 | ID缓存，排名缓存 |
| WorldBoss | ✅ 完成 | DB持久化，Boss升级，遗迹Boss |
| EquipBack | ⏳ 待做 | 装备找回 |
| FamilyManager | ⏳ 待做 | 家族系统 |
| CfgData 93个函数 | ⏳ 待做 | 反编译风格→干净版重写 |

## 协议定义

网络协议码定义在 `../share/PDUDefine.h`，2019新增：
- `SM_SEND_DROP_RECORD` (11990) - 掉落记录
- `SM_SEND_RUINS_BOSS_INFO` (11991) - 遗迹Boss信息
- `SM_SEND_RUINS_BOSS_CHANGE` (11992) - 遗迹Boss变化
