# GameServer

> C++ MMORPG 游戏服务器 — 2019 版本升级已完成

## 项目结构

```
game1/
├── gameserver/          # 游戏逻辑服务器（主项目）
├── decompiled_backup/   # 反编译参考代码（405个文件，从 gameserver.cc 反编译）
├── libanswer/           # 基础网络框架库
├── share/               # 共享头文件（PDUDefine.h 等协议定义）
├── scripts/             # 运维脚本
├── sqls/                # SQL 建表脚本
└── MEMORY.md            # 长期项目记忆（详细进度记录）
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
                          │  └─────────────────────────────────┘    │
                          │                    │                    │
                          │                    ▼                    │
                          │  ┌─────────────────────────────────┐    │
  ┌──────────┐  ×1~N     │  │         DBService               │    │
  │ Database │◄──────────►│  │  MutiConn<DBService> × N        │    │
  │          │  MutiConn  │  │  28 message handlers            │    │
  └──────────┘            │  └─────────────────────────────────┘    │
                          │                                         │
                          │  ┌─────────────────────────────────┐    │
                          │  │          CfgData                │    │
                          │  │  247 Init functions             │    │
                          │  │  27 new struct/class types      │    │
                          │  └─────────────────────────────────┘    │
                          └─────────────────────────────────────────┘
```

## 2019 版本升级 — 完成总览

### 多连接架构重构

- **GameService**: `MutiConn<GameService>` 多连接管理，`m_users[MAX_GATE_CONNS × MAX_CONNECTION]`，~40新函数
- **DBService**: `MutiConn<DBService>` 多连接管理，28消息处理，connid参数
- **connid 全量改造**: ~250处 popNetpacket/sendPacketTo/replySuccess/worldBroadcast 调用已全部适配

### P0 — Player.cpp 核心补全 ✅

Player.cpp 从 2751 行增至 6158 行（+3407 行）：
- 构造/析构/初始化、网络包处理器 on*()、信息发送器 send*()
- 25 个未实现方法补全（setBaseAttr, doTeleport, sendPublicChat, appendInfo, RecalcAttr 等）
- OnXXX 空壳函数实现、充值回调恢复

### P1 — 严重不足模块（体积<30%）✅ 13/13

Buff, CharCarrier, CharWuHun, CharWish, CMonthlyChouJiang, CrossTower, CharPortal, ChrDepot, Currency, Curse, CharWorship, BossKilledReward, CharMysteryShop

### P2 — 中等不足模块（体积30~50%）✅ 15/15

ActivityMap, EquipBack, ActivityManager, CharFamily, CharTitle, CharExchange, CharAuction, CharDraw, DailyActivity, DropItem, CharSkill, CKiaFuRecharge, ActivityWorldBoss, CDaTingReward, CampWar

### P3 — 适度补全模块（体积50~70%）✅ 12/12

Bag, CMingGeExt, BlackMarket, CKunExt, CharTeam, CLittleHelper, Activity, CampWar, CharInsidePet, CharTeamDungeon, CharHallOfFame, CharWing

### P4 — 大型模块深化 ✅ 3/3

Map.cpp（connid改造30处）, UniteServer.cpp（connid改造11处+IsInMysteryShopTime）, OpenBeta.cpp（已完成）

### P5 — 零散任务 ✅ 全部完成

- Map.cpp IsXinMoMap/IsXinMoCun 实现（type==1 && param==25/24）
- CfgData 33个 placeholder 替换为正确类型 + 27个新 struct/class 定义
- CfgData #if 0 块启用（45个 Init 函数）
- FamilyWar.cpp 无 TODO/stub，已完整

### P6 — 编译/链接修复 ✅

- CfgData 类型补全完成（27个新 struct/class）
- Player 25个未实现方法补全（+563行）
- 新增枚举值：ICR_WISH(922), ICR_EXCHANGE(923), ICR_DRAW_GET_REWARD2(924)

### SendIconState 改造

手动发 SM_SEND_ONE_ICON 包的代码统一改为 `m_pPlayer->SendIconState(&icon)`

## 新增协议

| 协议 | 码值 | 说明 |
|------|------|------|
| `SM_SEND_DROP_RECORD` | 11990 | 掉落记录 |
| `SM_SEND_RUINS_BOSS_INFO` | 11991 | 遗迹Boss信息 |
| `SM_SEND_RUINS_BOSS_CHANGE` | 11992 | 遗迹Boss变化 |
| `SM_SEND_NOTICE_PARAM` | 11478 (0x2CD6) | 通知参数 |
| `SM_NOTIFY_ACTIVITY_PLAYER_SCORE` | 11812 (0x2E24) | 活动玩家分数 |
| `SM_NOTIFY_ACTIVITY_RESULT` | 11815 (0x2E27) | 活动结果 |

## 项目规模

| 指标 | 数值 |
|------|------|
| gameserver/ 源文件 | ~182 .cpp + 191 .h |
| gameserver/ 总源码 | ~18.5 MB |
| Player.cpp | 6,158 行 |
| CfgData.cpp | 22,400+ 行 |
| CfgData.h | 8,500+ 行（含27个新增类型） |
| 配置Init函数 | 247 个（全部实现） |
| 反编译参考 | 405 个文件 (decompiled_backup/) |
| 本次升级新增代码 | ~24,000+ 行 |

## 反编译参考

反编译源从 `gameserver.cc` (569,852行) 经 IDA/Ghidra 反编译后按类拆分：

- 命名映射：`C` 前缀 → 去掉（`CActivity` → `Activity`）
- 聚合文件：`Cfg*Table` → `CfgData`，`ItemEffect`子类 → `ItemEffect`，DB类 → `DBData`，日志类 → `GameLogs`
- 不存在的 API（AddPlatformLog, GetPassport, PLDT_SYSTEM）已跳过
