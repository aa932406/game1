# GameServer 2019版本更新 — 长期记忆

## 项目概况
- C++ 游戏服务器项目，路径 `/home/gameserver/gameserver/`
- 目标：更新到 2019-06-26 版本
- 反编译参考源：`/home/gameserver/decompiled_backup/` (405个文件)
- 反编译自 `gameserver.cc` (569,852行)，经 IDA/Ghidra 反编译后按类拆分
- 远程仓库：`origin` = aa932406/gameserver, `game1` = aa932406/game1

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

## 已完成模块

### DBService 2019架构
- 从继承TcpService改为管理多个MutiConn<DBService>连接
- 函数签名统一增加int8_t connid参数（默认=0兼容旧调用）
- onNetPacket扩展到28个case

### GameService 2019架构
- 从单连接改为管理多个MutiConn<GameService>连接（m_mConn map）
- onNetPacket(GameConn*, NetPacket*) — 非virtual重载，由MutiConn回调
- m_users扩展为[MAX_GATE_CONNS * MAX_CONNECTION] 支持100个gate连接
- 新增~40个函数：drop控制、chat验证、城战title、广播、跨服等

### EquipManager 2019装备系统
- ServerNewId ID缓存 + m_mNewId/m_IdLock
- UpdateMemEquip/DeleteMemEquip 增加 connid+nReason（保留旧签名兼容重载）
- SendPlayerEquipInfo 3个重载 + BroadcastEquipInfo
- getEquipId 缓存机制 + getEquipIdFromDB

### PetManager 2019宠物系统
- PetNewId ID缓存 + m_mNewId/m_IdLock
- m_mPetRank 排名缓存 + GetPetRankIndex
- OnUpdatePetRank/OnInitPetRank 简化
- getPetId 缓存机制 + getPetIdFromDB

### WorldBoss 2019世界Boss
- InitDBInfo/InitDropRecord/saveBossInfo DB持久化
- OnAddBoss/OnBossSummon/OnBossKilled 含等级调整
- adjustBossAttr 属性映射（vAttr→CfgMonster字段）
- DropRecord 掉落记录 + SendDropRecord
- SendRuinsBossInfo/UpdateRuinsBossInfo 遗迹Boss
- 新增协议码 SM_SEND_DROP_RECORD/SM_SEND_RUINS_BOSS_INFO/SM_SEND_RUINS_BOSS_CHANGE
- Monster::OnLevelUp 新增

### FamilyManager 部分完成
- Init(int32_t line) 跨服跳过
- FamilyInfo::CleanUp/IsDeclareWarFamily/UnPackageData 新增
- 仍需对照 CFamilyManager.cpp 完善更多方法

---

## 待做清单

### 任务 B1：EquipBack 装备找回系统（优先级：高）
- 反编译源 CEquipBack.cpp（1086行）vs 当前 EquipBack.cpp（610行）
- 需要对照反编译补充完整的2019逻辑
- 反编译源含 EquipBackRankCfg.cpp（17行）配置表

### 任务 B2：FamilyManager 家族系统（优先级：高）
- 反编译源 CFamilyManager.cpp（433行）vs 当前 FamilyManager.cpp（192行）
- Init/基础方法已更新，但大量业务方法仍缺失
- 需要对照反编译补充完整的2019逻辑

### 任务 B3：OpenBeta 公测活动（优先级：中）
- OpenBeta.cpp 有 20+ 个 TODO 空壳函数
- 需要对照 COpenBeta.cpp 反编译源完善

### 任务 B4：ItemEffect 剩余子类（优先级：中）
- 6个 TODO 子类：BackCityPaper, RandomPosPaper, ShouChongItem, SummonBoss, VipDrop 等
- 需要对照反编译源完善

### 任务 A：CfgData 93个反编译风格函数（优先级：低）
- 功能可用，代码质量差，含 IDA 伪代码标记
- 可渐进式重写

### 任务 C：调用端 connid 签名更新（优先级：中）
- DBService/GameService 函数签名增加 connid 后
- ~20+ 调用端文件需逐步更新为 connid 感知调用

### 任务 D：编译错误修复（优先级：最终阶段）
- 统一修复缺少头文件、API名称不匹配、类型转换等问题

---

## CfgData Init函数状态
- 全部247个已声明 Init 函数均已实现
- 其中112个干净版本 + 93个反编译版本（功能可用，可渐进重写）+ 42个新增
- 已清理22个重复定义（保留2019干净版/首出现版）
- 新增26个配置结构体 + 19个成员变量
