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

### ~~任务 E：未实现函数补全~~ — ✅ 第一轮完成（2026-06-08）+ P0-e充值回调恢复
- Player.cpp: 1415→2751行（+1336行），实现核心getter/Unit虚函数/PK系统/背包/记录/canAttackTarget/switchMap/leaveDungeon/leaveActivity/safeRevive
- Player.h: 新增成员 m_Battle/m_nCamp/m_nGuaJi/m_needRecalAttr/m_BeiGongAttr/SetNeedSyncAround/canAttackTarget
- CharSkill.cpp: addSkillBuffTo完整实现、canAttackTarget委托checkSkillTarget、召唤逻辑实现
- DungeonBuff.cpp: effect()/interval() 恢复注释掉的buff效果逻辑
- FightChecker.cpp: UpdateFightState() 恢复并适配2019多连接
- CharTeamDungeon.cpp: onSocialTeamDungeonCost完整实现
- Vip.cpp: SendVipGiftIcon完整实现（SM_SEND_ONE_ICON 11459）
- Dungeon.cpp/h: GetBackMapId/StayPosition/GetBackPos + CfgDungeon新增字段
- IsFunctionOpen: 3处硬编码true改为条件检查，CanUseXP确认正确
- 确认：GongMing/GuardPrivilege/YunYingHD DB持久化通过OperateLimit自动完成，空实现正确

### P0-e 充值回调恢复详情（2026-06-08）
- PayedDispose: 恢复7处注释→CKiaFuRecharge::OnRecharge/CFestivalDoubleEleven::OnRecharge+AddRechargeRecord+SendIconState/CUniteServer::OnRecharge+SendIconState/CZongHeYunYingHD::OnRecharge/CKiaFuHuoDong::SendKaiFuHuoDongIcon
- OnKaiFuHuoDongOperator: 恢复CKiaFuHuoDong::KaiFuHuoDongOperator调用
- OnFestivalActivityOperator: 完整实现（反编译源答题/兑换/抽奖逻辑，Proc 683/684）
- OnUniteServerRequestInfo: 恢复CUniteServer::SendUniteServerInfo
- OnUniteServerGetRechargeGift: 完整实现（GetRechargeGift+replySuccess）
- OnDoubleElevenRequestInfo: 恢复CFestivalDoubleEleven::SendActivityInfo
- OnZHYYHDRequestInfo: 恢复CZongHeYunYingHD::SendActivityInfo
- OnZHYYHDGetRechargeDailyReward: 完整实现（GetRechargeDailyReward+replySuccess）
- OnZHYYHDGetRechargeTeamShopDailyReward: 完整实现（readInt32+GetRechargeTeamShopDailyReward+replySuccess）
- OnZHYYHDBuyOnceShopItem: 完整实现（readInt32+BuyOnceShopItem+replySuccess）
- OnGetKaiFuREcharge: 完整实现（switch nHdType: 1=OnGetRechargeSumReward, 2=GetLianRechargeReward, 4=OnGetXiaoFeiReward）
- OnGetKaiFuChouJiang: 完整实现（readInt32+OnGetChouJiangReward）
- 升级回调: 恢复CKiaFuHuoDong::OnLevelUp+m_extCharTencent.SendTGPIcon/SendBlueStoneIcon

### 任务 D：编译错误修复（优先级：最终阶段）
- 统一修复缺少头文件、API名称不匹配、类型转换等问题

---

## 第三阶段全量任务清单（2026-06-08 全审计）

> **审计结论**：除 Player.cpp 外，所有模块的 .h 声明与 .cpp 实现数量匹配。
> 差距主要体现在：Player 有~45个方法完全未实现（链接错误），其他模块实现偏简化（功能不完整但不会编译报错）。

---

### P0 — Player.cpp 核心补全（~45个方法未实现，将导致链接错误）

| ID | 任务 | 数量 | 说明 | 状态 |
|----|------|------|------|------|
| P0-a | Player 构造/析构/初始化 | 7 | `Player()`, `~Player()`, `init()`, `initNetPacketHandlers()`, `InitExtSystems()`, `SaveDBData()`, `enterDungeon(static)` | ✅ |
| P0-b | Player 网络包处理器 on*() | ~30 | onMove/onHit/onSwitchMap/onEnterDungeon/onUseItem/onUpgradeSkill/onReceiveTask/onTeleport 等全部 | ✅ |
| P0-c | Player 信息发送器 send*() | ~15 | sendBasicInfo/sendLoginInfo/sendChrInfo/sendEquipInfo/sendSkillList/sendGainInfo 等 | ✅ |
| P0-d | Player OnXXX空壳处理函数补全 | 20+ | OnKaiFuHuoDongOperator/OnUniteServerGetInfo/OnDoubleElevenRequestInfo/OnZHYYHD* 等 | ✅ |
| P0-e | Player 充值回调注释恢复 | 6+ | CKiaFuRecharge/CFestivalDoubleEleven/CUniteServer/CZongHeYunYingHD/CKiaFuHuoDong 注释掉的调用 | ✅ |
| P0-f | Player 其他缺失方法 | ~10 | verifyBagInfo/queryBagInfo/RecalcAttr/GetCurrency/AddCurrency/DecCurrency/moveToReviveRegion/doTeleport/防沉迷等 | ✅ |
| P0-g | Player 空壳函数实现 | 27 | setTaskCanSubmit/taskTalkWithNpc/onKillMonster/sendJungongChangeInfo/sendPvpInfo 等空体函数 | ✅ |

**P0 执行顺序**：P0-e(充值回调恢复) → P0-a(构造/初始化) → P0-b(网络包处理) → P0-c(信息发送) → P0-d(OnXXX补全) → P0-f(其他缺失) → P0-g(空壳补全)

---

### P1 — 体积差距 <30% 的模块（严重不足，需大幅补全）

| ID | 模块 | 当前 | 反编译 | 比例 | 状态 |
|----|------|------|--------|------|------|
| P1-1 | Buff.cpp | 0.6KB | 7.9KB | 8% | ✅ |
| P1-2 | CharCarrier.cpp | 1.9KB | 10KB | 19% | ✅ |
| P1-3 | CharWuHun.cpp | 9.5KB | 49KB | 19% | ✅ |
| P1-4 | CharWish.cpp | 5.4KB | 22KB | 24% | ✅ |
| P1-5 | CMonthlyChouJiang.cpp | 8KB | 34KB | 24% | ✅ |
| P1-6 | CrossTower.cpp | 14KB | 49KB | 29% | ✅ |
| P1-7 | CharPortal.cpp | 6KB | 20KB | 30% | ✅ |
| P1-8 | ChrDepot.cpp | 17KB | 55KB | 30% | ✅ |
| P1-9 | Curse.cpp | 2.4KB | 7.9KB | 31% | ✅ |
| P1-10 | CharWorship.cpp | 3.8KB | 12KB | 33% | ✅ |
| P1-11 | BossKilledReward.cpp | 7.6KB | 23KB | 33% | ✅ |
| P1-12 | CharMysteryShop.cpp | 8.6KB | 26KB | 33% | ✅ |
| P1-13 | Currency.cpp | 10KB | 39KB | 26% | ✅ |

### P2 — 体积差距 30%~50% 的模块（需补全）

| ID | 模块 | 当前 | 反编译 | 比例 | 状态 |
|----|------|------|--------|------|------|
| P2-1 | ActivityMap.cpp | 21KB | 76KB | 28% | ✅ |
| P2-2 | CityWar.cpp | 27KB | 76KB | 36% | ✅ |
| P2-3 | EquipBack.cpp | 16KB | 44KB | 35% | ✅ |
| P2-4 | ActivityManager.cpp | 12KB | 34KB | 36% | ✅ |
| P2-5 | CharFamily.cpp | 32KB | 89KB | 36% | ✅ |
| P2-6 | CharTitle.cpp | 14KB | 37KB | 37% | ✅ |
| P2-7 | CharExchange.cpp | 4.3KB | 11KB | 40% | ✅ |
| P2-8 | CharAuction.cpp | 6.5KB | 16KB | 41% | ✅ |
| P2-9 | CharDraw.cpp | 2.9KB | 7KB | 42% | ✅ |
| P2-10 | DailyActivity.cpp | 40KB | 99KB | 40% | ✅ |
| P2-11 | DropItem.cpp | 12KB | 25KB | 46% | ✅ |
| P2-12 | CharSkill.cpp | 40KB | 93KB | 43% | ✅ |
| P2-13 | CKiaFuRecharge.cpp | 16KB | 36KB | 45% | ✅ |
| P2-14 | ActivityWorldBoss.cpp | 12KB | 26KB | 45% | ✅ |
| P2-15 | CDaTingReward.cpp | 16KB | 42KB | 39% | ✅ |

### P3 — 体积差距 50%~70% 的模块（需适度补全）

| ID | 模块 | 当前 | 反编译 | 比例 | 状态 |
|----|------|------|--------|------|------|
| P3-1 | Bag.cpp | 70KB | 124KB | 56% | ✅ |
| P3-2 | CMingGeExt.cpp | 20KB | 36KB | 56% | ✅ |
| P3-3 | BlackMarket.cpp | 6.5KB | 11KB | 59% | ✅ |
| P3-4 | CKunExt.cpp | 28KB | 47KB | 60% | ✅ |
| P3-5 | CharTeam.cpp | 7.3KB | 12KB | 63% | ✅ |
| P3-6 | CLittleHelper.cpp | 7.6KB | 12KB | 63% | ✅ |
| P3-7 | Activity.cpp | 17KB | 33KB | 51% | ✅ |
| P3-8 | CampWar.cpp | 21KB | 42KB | 50% | ✅ |
| P3-9 | CharInsidePet.cpp | 28KB | 58KB | 49% | ✅ |
| P3-10 | CharTeamDungeon.cpp | 7.7KB | 15KB | 51% | ✅ |
| P3-11 | CharHallOfFame.cpp | 9.4KB | 18KB | 52% | ✅ |
| P3-12 | CharWing.cpp | 7.1KB | 25KB | 28%→P2 | ✅ |

### P4 — 大型模块深化（体积差距50%以下但绝对体量大）

| ID | 模块 | 当前 | 反编译 | 比例 | 状态 |
|----|------|------|--------|------|------|
| P4-1 | Map.cpp | — | 142KB+ | — | ✅ |
| P4-2 | UniteServer.cpp | — | 79KB | — | ✅ |
| P4-3 | OpenBeta.cpp | — | 122KB | — | ✅ |

### P5 — 其他零散任务

| ID | 任务 | 说明 | 状态 |
|----|------|------|------|
| P5-1 | Map.cpp IsXinMoMap/IsXinMoCun | type==1 && param==25/24 | ✅ |
| P5-2 | CfgData #if 0 禁用块 | 33个placeholder替换为正确类型 + 16个新struct/class定义 + #if 0→#if 1 | ✅ |
| P5-3 | CfgData 93函数重写 | 小#if 0块已有手写替代版本，无需重写 | ✅ |
| P5-4 | FamilyWar.cpp 补尾 | 1563行，无TODO/stub | ✅ |
| P5-5 | connid签名更新遗留 | 全量connid改造已完成（P0-P4+47个额外文件） | ✅ |

### P6 — 编译错误修复（最终阶段）

| ID | 任务 | 说明 | 状态 |
|----|------|------|------|
| P6-1 | 全量编译错误修复 | CfgData类型补全完成(27个新struct/class)，待全量编译验证 | ⏳ |
| P6-2 | 链接错误修复 | Player 25个未实现方法已补全(+563行)，Player.cpp 5595→6158行 | ✅ |

---

### 全局执行顺序

```
阶段1: P0 (Player.cpp — 链接错误 + 核心功能)
  P0-e → P0-a → P0-b → P0-c → P0-d → P0-f → P0-g

阶段2: P1 (体积<30% 的严重不足模块)
  P1-1~P1-13 按依赖关系排序

阶段3: P2 (体积30~50% 模块)
  P2-1~P2-15

阶段4: P3 (体积50~70% 模块)

阶段5: P4 (大型模块深化)

阶段6: P5 (零散) + P6 (编译/链接)
```

### 预估工作量

| 阶段 | 模块数 | 新增代码估算 |
|------|--------|-------------|
| P0 Player | 1文件7子任务 | ~5000行 |
| P1 严重不足 | 13模块 | ~800行/模块 ≈ 10000行 |
| P2 中等不足 | 15模块 | ~400行/模块 ≈ 6000行 |
| P3 适度补全 | 12模块 | ~200行/模块 ≈ 2400行 |
| P4 大型深化 | 3模块 | ~2000行/模块 ≈ 6000行 |
| P5+P6 | 零散 | ~1000行 |
| **合计** | — | **~24400行** |

---

## CfgData Init函数状态
- 全部247个已声明 Init 函数均已实现
- 其中112个干净版本 + 93个反编译版本（功能可用，可渐进重写）+ 42个新增
- 已清理22个重复定义（保留2019干净版/首出现版）
- 新增26个配置结构体 + 19个成员变量

---

## P1-1 Buff.cpp 补全详情（2026-06-08）

- Buff.cpp: 51→234行（+183行），从空壳变为完整基类实现
- Buff.h: 107→118行，新增成员和方法
- 新增方法：
  - `effect()` — Buff生效：属性修改(AddBuffAttrRatio/Value) + 速度特殊处理(AddSpeedBuffRatio) + 状态添加(9种special→CObjState)
  - `restore()` — Buff移除：属性还原(反向ratio/addon) + 速度还原(RemoveSpeedBuffRatio) + 状态移除
  - `interval()` — 周期触发：beneficial=HP回复，harmful=struckDamage伤害
  - `shieldDamage()` — 护盾吸收：nDamage<m_nShield部分吸收，否则破盾
  - `trigTime()` — 定时触发：检查interval间隔后调用interval()
  - `effectTimes()` — 效果次数：++m_nEffectTimes >= effectTimes
  - `expire()` — 扩展：增加m_nType==2(InDungeon)/==3(InActivity)判断
- 新增成员：m_launcher, m_lastIntervalTick, m_nShield, m_nEffectTimes, m_nType, m_bDeathClear, m_restore(vector)
- 构造函数扩展：新增launcher/nType/bClear参数，shieldValue/shieldRatio初始化
- CfgBuff扩展：groupid, attack_type, level, modify, hpValue, hpPecent, control, shieldValue, shieldRatio, effectType, effectTimes, canRemove, canRecover, battle
- CObjState扩展：OBS_SLEEP(9), OBS_SHIELD(10), OBS_PLYSIS(11), OBS_FROZEN(12)
- Unit.h/cpp扩展：AddSpeedBuffRatio/RemoveSpeedBuffRatio 方法
- 子类适配：SkillBuff/DungeonBuff/MonsterBuff 删除重复m_restore/m_launcher，改用基类vector

## P1-8 ChrDepot.cpp 补全详情（2026-06-08）

- ChrDepot.cpp: 767→1115行（+348行），ChrDepot.h: 61→76行（+15行）
- 新增方法：
  - `CanOperateDepot()` — 仓库操作权限检查：VIP标志(2)或地图50001 + 密码验证状态(getRecord(2))
  - `IsEnterSecondPasswordOperate()` — 二级密码操作权限：密码为空或getRecord(9)==1
  - `GetPageBySlot()` — 页码计算：Slot/56+1
  - `OpenSlotCostGold()` — 开格费用：10*((Slot-56)/5+1)
  - `CleanBag()` — 清理仓库装备：装备类(itemClass==2)删除MemEquip，普通道具清空
  - `OnNewSortDepot()` — 按页排序：读取Page，MinSlot=56*Page，MaxSlot=56*(Page+1)-1，范围内排序整理
  - `OnSetPassword()` — 设置一级密码：两次输入一致→m_Password=输入，updateRecord(2,1)
  - `OnEnterPassword()` — 验证一级密码：匹配→updateRecord(2,1)+replySuccess
  - `OnModifyPassword()` — 修改一级密码：旧密码匹配+两次新密码一致→m_Password更新
  - `OnCancelPassword()` — 取消一级密码：旧密码匹配→m_Password.clear()+SendDepotInfo
  - `OnSetSecondPassword()` — 设置二级密码：两次输入一致→m_SendPassword=输入，updateRecord(9,1)
  - `OnEnterSecondPassword()` — 验证二级密码：匹配→updateRecord(9,1)+replySuccess
  - `OnModifySecondPassword()` — 修改二级密码：旧密码匹配+两次新密码一致→m_SendPassword更新
  - `OnCancelSecondPassword()` — 取消二级密码：旧密码匹配→m_SendPassword.clear()+SendDepotInfo
- 新增成员：m_OpenCount(int32_t), m_Password(std::string), m_SendPassword(std::string)
- 架构变更：
  - GetDepotSize：FREE_DEPOT_SLOT+m_OpenCount（替代旧的m_DepotInfo.m_nOpenedSlots）
  - OnOpenDepotSlot：简化为OpenSlotCostGold费用计算+m_OpenCount累加（删除旧的计时开格逻辑）
  - OnUpdate：删除CheckOpenSlot()（新版无自动开格）
  - SendDepotInfo：写入GetDepotSize()-1 + 密码状态(2字节)（替代旧的3字段写入）
  - SendDepotCurrency：writeInt64替代writeInt32（64位货币值）
  - 所有网络包发送/接收改为connid版本（popNetpacket/sendPacketTo/replyfailure/replySuccess）
- 权限检查：OnGetDepotItem/OnSaveItemToDepot/OnGetDepotCurrency/OnSaveDepotCurrency/OnSortDepot/OnOpenDepotSlot 均添加 CanOperateDepot() 检查
- OnSaveItemToDepot：新增VIP页数限制（GetPageBySlot(DepotSlot) <= GetStorePage()）
- IsSlotValid：增加 Slot>=0 检查
- 协议码：CM_SET_DEPOT_PASSWORD(407), CM_ENTER_DEPOT_PASSWORD(408), CM_MODIFY_DEPOT_PASSWORD(409), CM_CANCEL_DEPOT_PASSWORD(410), CM_SET_DEPOT_SECOND_PASSWORD(503), CM_ENTER_DEPOT_SECOND_PASSWORD(504), CM_MODIFY_DEPOT_SECOND_PASSWORD(505), CM_CANCEL_DEPOT_SECOND_PASSWORD(506)
- DataStruct.h：MemChrDepotData新增OpneCount(int32_t)/Password(std::string)/SecondPassword(std::string)字段
- PDUDefine.h：添加8个仓库密码协议码
