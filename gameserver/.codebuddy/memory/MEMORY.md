# GameServer 2019版本更新 — 长期记忆

## 项目概况
- C++ 游戏服务器项目，路径 `/home/gameserver/gameserver/`
- 目标：更新到 2019-06-26 版本
- 反编译参考源：`/home/gameserver/decompiled_backup/` (405个文件)
- 反编译自 `gameserver.cc` (569,852行)，经 IDA/Ghidra 反编译后按类拆分

## 命名映射规则
- `C` 前缀类 → 项目去掉前缀（`CActivity` → `Activity`）
- `CExtChar*` → 对应 Char*（`CExtCharBag` → `Bag`）
- `CExt*` → 对应去掉 CExt（`CExtEquip` → `Equip`）
- `Cfg*Table/Cfg*` → 嵌入 `CfgData.h/cpp`
- `ItemEffect` 子类 → 嵌入 `ItemEffect.h/cpp`
- DB 持久化类 → 嵌入 `DBData.h/cpp`
- 日志类 → 嵌入 `GameLogs.h/cpp`

## 聚合文件模式
- **CfgData.h/cpp** — 配置表结构 + Init 函数（24685/7889 行, 247个Init函数全部实现）
- **ItemEffect.h/cpp** — 所有物品效果子类（935/2369 行, 37个子类）
- **DBData.h/cpp** — 47+ DB数据类
- **GameLogs.h/cpp** — 12+ 日志类
- **DataStructs.h** — 公共数据结构
- **actStructs.h** — 活动相关结构
- **DBService.h/cpp** — 2019多连接架构，管理MutiConn<DBService>连接池，~30+新函数
- **MutiConn.h** — 多连接模板，继承TcpClient，按connid分发到父Service
- **GameService.h/cpp** — 2019多连接架构，管理MutiConn<GameService>连接池，~40+新函数

## DBService 2019架构 (2026-06-07更新)
- 从继承TcpService改为管理多个MutiConn<DBService>连接
- 函数签名统一增加int8_t connid参数（默认=0兼容旧调用）
- onNetPacket扩展到28个case
- 调用端~20+文件待更新签名

## GameService 2019架构 (2026-06-07更新)
- 从单连接改为管理多个MutiConn<GameService>连接（m_mConn map）
- onNetPacket(GameConn*, NetPacket*) — 非virtual重载，由MutiConn回调
- m_users扩展为[MAX_GATE_CONNS * MAX_CONNECTION] 支持100个gate连接
- 新增IndexMap, ChatValidate结构；Drop控制(m_dropControl); Chat验证(m_ChatValidateMap)
- 新增~40个函数：drop控制、chat验证、城战title、广播、跨服等
- broadcast/worldBroadcast改为IndexMap按connid分组发送
- 调用端（Player等）需逐步更新为connid感知

## CfgData Init函数状态 (2026-06-07更新)
- 全部247个已声明 Init 函数均已实现
- 其中112个干净版本 + 93个反编译版本（功能可用，可渐进重写）
- 已清理22个重复定义（保留2019干净版/首出现版）
- 新增26个配置结构体 + 19个成员变量
