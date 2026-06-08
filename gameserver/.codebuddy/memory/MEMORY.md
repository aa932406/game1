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

### ~~任务 B1：EquipBack~~ — ✅ 已完成
### ~~任务 B2：FamilyManager~~ — ✅ 已完成
### ~~任务 B3：Openbeta~~ — ✅ 已完成
### ~~任务 B4：ItemEffect~~ — ✅ 已完成
### ~~任务 B5：Player.cpp/h~~ — ✅ 已完成（2019逻辑完善）

### ~~任务 B6：Vip.cpp/h~~ — ✅ 已完成（2019逻辑完善）

### Vip.cpp/h 2019完善详情
- 从48行空壳扩展到~1260行完整实现
- 43个方法全部对照反编译源 CVip.cpp 实现：
  - VIP等级/经验：GetVipLevel(从VipExp计算), GetVipExp(record 1020), AddVipExp(升级回调+广播)
  - VIP卡系统：OnBuyVipCard(3种卡+续费), OnBuyAllVipCard(一键三卡), OnGetVipCardGift(每日奖励)
  - VIP卡时间：AddVipTime(3种卡到期时间), GetVipFlg(判断卡是否有效), GetVipType(当前卡类型)
  - Club系统：OnEnterClub(加入+广播), OnBuyDropTimes(购买掉落次数), SendClubInfo, GetClubDrop(概率掉落+装备+邮件)
  - LuckyDrop系统：GetLuckDropType(双类型掉落), GetDropVipLevel, AddDropTimes, SendLuckDrop
  - VIP属性：AddVipAttr(卡属性+等级属性), GetExpRate, GetOpenBagRate, GetVipEquipBackRate, GetTreasureTimes, GetCycleTowerTimes, GetStorePage
  - VIP特权：CanFreeFlying, CanSiteRevive, HaveVipPrivilege, CanAuction, UseVipTiYanCard
  - 持久化：OnLoadFromDB/OnSaveToDB, OnLoadVipEndTime/OnSaveVipEndTime(3卡时间用:分隔), LoadDropString/SaveDropString
  - 网络发送：SendVipInfo(0x2CD9), SendClubInfo(0x2CF7), BuyGongGao(0x2CD6), SendLuckDrop(0x2CDA)
  - 定时检查：OnUpdate(60秒), CheckVipEnd(到期邮件), OnDaySwitch(重置Club次数)
- 新增成员：m_PlatinumVipEndTime/m_DiamVipEndTime/m_StarVipEndTime(3种VIP卡到期), m_Club/m_ClubDropTimes/m_BuyTimes/m_nVip7Time/m_nVip10Time
- CfgData.h扩展：VipCfg+7字段(Luck1/Luck2/ClubBuyTimes/EquipBackRate/TreasureTimes/CycleTower/StorePage), VipCardCfg+3字段(VipLevel/ReNeedGold/Money/TianShuJinHua/WeiWang)
- 新增结构：SpecialItemDrop, LuckDrop, LuckDropTable类(AddLuckDrop/GetLuckRate/GetItem), CVipClubLuckyDrop+lRateItemList
- DataStructs.h新增枚举：GCR_VIP_BUY_DROP_TIMES(2103), MCR_VIP_CARD(2104), ICR_VIP_GIFT/ICR_CLUB_DROP/ICR_LUCK_DROP
- EquipManager.h新增CreateMemEquip重载(2019多参数版)
- Player.h新增GetCSpecialEquip()/GetPlayerFaBaoPtr()声明
- CVipClub.h新增GetClubLevel()方法

### 任务 A：CfgData 反编译风格函数重写 — **完成 LODWORD/HIDWORD 清理**
- 原始86个反编译Init函数 + 35+个getter函数
- 机械清理已完成：IDA寄存器注释、显式operator调用、构造/析构调用等
- Batch 2完成：_M_node(0)、_Rb_tree_iterator(0)、_List_iterator(0)全部清除
- LODWORD/HIDWORD：33→0（全部清除）
- 完整重写的复杂函数：InitGameTable, fetchItem, RandXiangYaoTaskId, GetSuperBuff/Get37wanSuperBuff
- fetchActivity反编译版删除（707行），干净版已存在于3017-3344行
- 22406行（从24743减少2337行）

### 任务 C：调用端 connid 签名更新 — **部分完成**
- EquipManager.cpp: CreateMemEquip 修复 connid 参数传递
- PetManager.h/cpp: AddPet/DelPet/UpdatePet 增加 connid 参数，添加兼容重载
- 更新所有调用点（CharPet.cpp 7处，CharInsidePet.cpp 1处）
- Vip.cpp/ShiZhuang.cpp/EquipBack.cpp: 8处 OnSendSysMail 调用更新为 connid 感知
- 遗留问题：FamilyWar.cpp 中3处 OnSendSysMail 调用传递邮件ID而非玩家ID（疑似bug）
- GameService.cpp: onNewMinuteCome 调用保持 connid=0（系统级别定时器）

### 任务 E：未实现函数补全 — **进行中**（2026-06-08）
- Player.cpp: 1415→2523行（+1108行），实现核心getter/Unit虚函数/PK系统/背包/记录/canAttackTarget
- Player.h: 新增成员 m_Battle/m_nCamp/m_nGuaJi/m_needRecalAttr/m_BeiGongAttr/SetNeedSyncAround/canAttackTarget
- CharSkill.cpp: addSkillBuffTo完整实现、canAttackTarget委托checkSkillTarget、召唤逻辑实现
- DungeonBuff.cpp: effect()/interval() 恢复注释掉的buff效果逻辑
- FightChecker.cpp: UpdateFightState() 恢复并适配2019多连接
- CharTeamDungeon.cpp: onSocialTeamDungeonCost完整实现
- Shared.h: SysUser新增gold_pay字段
- 确认：GongMing/GuardPrivilege/YunYingHD DB持久化通过OperateLimit自动完成，空实现正确
- 遗留：Player约50+复杂方法未实现、Vip::SendVipGiftIcon/Curse::OnCurseLevelUp未实现

### 任务 D：编译错误修复（优先级：最终阶段）
- 统一修复缺少头文件、API名称不匹配、类型转换等问题

---

## CfgData Init函数状态
- 全部247个已声明 Init 函数均已实现
- 其中112个干净版本 + 93个反编译版本（功能可用，可渐进重写）+ 42个新增
- 已清理22个重复定义（保留2019干净版/首出现版）
- 新增26个配置结构体 + 19个成员变量
