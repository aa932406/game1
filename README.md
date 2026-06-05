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

## 模块修复进度

从反编译代码 (`gameserver/decompiled/`) 中移植缺失模块到当前代码库。

### 已移植模块 (31/88)

| 模块 | 源文件 | 行数 | 说明 |
|------|--------|------|------|
| **GuardPrivilege** (护卫特权) | `GuardPrivilege.cpp/.h` | ~300 | 12 方法，含购买/DB回调/图标推送 |
| **SpecialEquip** (特殊装备) | `SpecialEquip.cpp/.h` | ~280 | 10 方法，含等级判定/激活/升级推送 |
| **BlackMarket** (黑市) | `BlackMarket.cpp/.h` | ~300 | 11 方法，含入场/购买/广播 |
| **TianLing** (天灵系统) | `TianLing.cpp/.h` | ~350 | 12 方法，3 子系统(天灵/战魂/日月) |
| **OutLinkFestival** (外部链接活动) | `OutLinkFestival.cpp/.h` | ~150 | 5 方法，全局服务，活动图标推送 |
| **KaiFuHuoDong** (开服活动) | `KaiFuHuoDong.cpp/.h` | ~2260 | 44 方法，源自 COpenBeta，含首杀/冲级/商城 |
| **UniteServer** (合服) | `UniteServer.cpp/.h` | ~1990 | 41 方法，含玩家迁移/家族合并/数据处理 |
| **Tencent** (腾讯平台) | `Tencent.cpp/.h` + `TencentTable.cpp/.h` | ~1850 | 55 方法 + 独立配置表系统(12张表)，原 CExtCharTencent |
| **CExtCharBag** (背包系统) | `Bag.cpp/.h` | ~3800 | 已完整实现(80+ 方法)，修复 OnDaySwitch + 缺失枚举值 |
| **CCityWar** (城战) | `CityWar.cpp/.h` | ~1200 | 42 方法，修复 3 处 sort() 缺比较器 Bug |
| **CCampWar** (阵营战) | `CampWar.cpp/.h` | ~852 | 28 方法，适配简化称号/阵营系统 |
| **CWorldBoss** (世界BOSS) | `WorldBoss.cpp/.h` | ~500 | 23 方法，扩展 KillerInfo + Top5 击杀者追踪 |
| **CExtCharCarrier** (护送) | `CharCarrier.cpp/.h` + `ObjCarrier.cpp/.h` | ~580 | 29 方法，含载具护送/到达/完成 |
| **CExtCharDraw** (抽卡) | `CharDraw.cpp/.h` | ~226 | 7 方法，含随机奖励/概率抽取 |
| **CExtCharExchange** (兑换) | `CharExchange.cpp/.h` | ~321 | 11 方法，含 DB 存取/兑换逻辑/记录管理 |
| **CExtCharMysteryGift** (神秘礼物) | `CharMysteryGift.cpp/.h` | ~273 | 15 方法，含领取礼包/广播/状态管理 |
| **CExtCharMysteryShop** (神秘商店) | `CharMysteryShop.cpp/.h` | ~526 | 15 方法，含商店查询/购买/刷新/加权随机商品/广播 |
| **CExtCharJueWei** (爵位) | `JueWei.cpp/.h` | ~510 | 16 方法，含爵位升级/属性加成/社交推送/公告 |
| **CExtCharPortal** (传送门) | `CharPortal.cpp/.h` | ~346 | 15 方法，含传送门交互/状态同步 |
| **CExtCharTitle** (称号) | `CharTitle.cpp/.h` | ~853 | 28 方法，含穿戴/卸下/幻化/属性加成/定时检查/隐藏恢复 |
| **CExtCharWing** (翅膀) | `CharWing.cpp/.h` | ~411 | 15 方法，含升级/幸运值/技能切换/属性加成/每日清空
| **CExtMagicBox** (魔盒) | `MagicBox.cpp/.h` | ~792 | 23 方法，含物品合成/饰品合成/装备合成/分解/合成点/卷轴激活/广播
| **CVplan** (V计划) | `Vplan.cpp/.h` | ~810 | 50+ 方法，含V计划核心/迅雷/YY语音/鲁大师/SG游戏/神武VIP 6子系统
| **CNationalDayHd** (国庆活动) | `NationalDayHd.cpp/.h` | ~537 | 20+ 方法，含任务追踪/等级系统/奖励系统，8种任务类型
| **CSevenDayTask** (七日任务) | `SevenDayTask.cpp/.h` | ~343 | 14 方法，含任务追踪/7天进度/奖励领取/图标推送
| **CDaZheQuan** (打折券) | ItemEffect handler | ~20 | 2 方法 (effect/parseEffect)，物品效果子系统
| **CRongLian** (熔炼活动) | `RongLian.cpp/.h` | ~18 | 3 方法 (析构/broadcastStart/sendPlayerScore)，CActivity子类
| **CYaBiao** (押镖) | `YaBiao.cpp/.h` | ~16 | 4 方法 (析构/ready/start/timeEnd)，CActivity子类
| **CShenWei** (神威) | `ShenWei.cpp/.h` | ~42 | 5 方法 (OnDaySwitch/AddCharAttr/GetRankAttr/GetShenWeiLevel)，CExtSystemBase子类
| **CRongHe** (融合) | `RongHe.cpp/.h` | ~130 | 15 方法 (OnRongLian/装备熔炼/拆卸/回收)，CExtSystemBase子类

### 数据层变更

| 文件 | 变更说明 |
|------|----------|
| `CfgData.h` | 添加 GuardPrivilege/SpecialEquip/BlackMarket/TianLing/OutLinkFestival/Carrier/Draw/Exchange/MysteryGift/MysteryShop/WishReward/MagicBox 配置结构体和成员 |
| `CfgData.cpp` | 完善配置解析方法 (Init*Table) 和 Get 方法；添加 InitMagicBoxTable 存根 |
| `DataStructs.h` | 添加 IACR_AUCTION_BUY/CANCEL/SELECT_ITEM, IDCR_SELECT_ITEM/DISCARD, GCR/GCC/MCR_AUTO_USE, GCR_MYSTERY_GIFT_BUY, GCR_MYSTERY_SHOP_REFRESH/BUY, IACR_MYSTERY_SHOP_BUY_GET, IDCR_MYSTERY_SHOP_BUY_COST |
| `share/DataStruct.h` | 添加 ExchangeRecord 结构体 + ExchangeDBData 类; 添加 MysteryShop 结构体 + MysteryShopDBData 类; 添加 MagicBoxDBData 类; 添加 CharWishInfo 结构体 + CharWishDBData 类 (SaveToSqlString/LoadFromDB/PackageData/UnPackageData) |
| `share/PDUDefine.h` | 添加 CM_MAGIC_BOX 协议 (725-729) 和 SM_MAGIC_BOX 协议 (11797-11799) 以及 CM_WISH 协议 (950-952) 和 SM_WISH 协议 (12040-12041) |
| `Player.h` | 集成 CharDraw/CharExchange/CharMysteryGift/CharMysteryShop/MagicBox/Wish/Vplan/NationalDayHd 模块声明 |

### 待移植模块 (剩余 ~52 个)

以下是从反编译代码中识别出的 `CExtSystemBase` 派生类模块：

| # | 模块 | 反编译文件 | 行数 | 说明 |
|---|------|-----------|------|------|
| 1 | BossKilledReward | `CBossKilledReward.cpp` | — | BOSS击杀奖励 |
| 2 | CardGroupBox | `CCardGroupBox.cpp` | — | 卡牌礼盒 |
| 3 | CardGroupBoxManager | `CCardGroupBoxManager.cpp` | — | 卡牌礼盒管理器 |
| 4 | CharWuHun | `CCharWuHun.cpp` | — | 武魂系统 |
| 5 | DaTingReward | `CDaTingReward.cpp` | — | 大厅奖励 |
| 7 | DropItemGroup | `CDropItemGroup.cpp` | — | 掉落组 |
| 8 | EquipBack | `CEquipBack.cpp` | — | 装备回购 |
| 9 | ExtCharAuction | `CExtCharAuction.cpp` | — | 拍卖行 |
| 10 | ExtCharFamily | `CExtCharFamily.cpp` | — | 军团 |
| 11 | ExtCharHallOfFame | `CExtCharHallOfFame.cpp` | — | 名人堂 |
| 12 | ExtCharPet | `CExtCharPet.cpp` | ~2,498 | 宠物 |
| 13 | ExtCharSkill | `CExtCharSkill.cpp` | ~2,498 | 技能 |
| 14 | ExtCharTeam | `CExtCharTeam.cpp` | — | 队伍 |
| 15 | ExtCharTeamDungeon | `CExtCharTeamDungeon.cpp` | — | 队伍副本 |
| 16 | ExtCharWish | `CExtCharWish.cpp` | — | 许愿 |
| 21 | ExtCharWorship | `CExtCharWorship.cpp` | — | 膜拜 |
| 22 | ExtChrTaskCycle | `CExtChrTaskCycle.cpp` | — | 循环任务 |
| 23 | ExtCurrency | `CExtCurrency.cpp` | — | 货币 |
| 24 | ExtEquip | `CExtEquip.cpp` | ~6,205 | 装备 |
| 25 | ExtFightChecker | `CExtFightChecker.cpp` | — | 战斗检测 |
| 26 | ExtFlopDraw | `CExtFlopDraw.cpp` | — | 翻牌抽奖 |
| 27 | ExtOperateLimit | `CExtOperateLimit.cpp` | — | 操作限制 |
| 28 | FestivalActivity | `CFestivalActivity.cpp` | ~1,372 | 节日活动 |
| 29 | FestivalDoubleEleven | `CFestivalDoubleEleven.cpp` | ~10,725 | **双十一活动（最大模块）** |
| 30 | FlopDraw | `CFlopDraw.cpp` | — | 翻牌抽奖 |
| 31 | GMBackstate | `CGMBackstate.cpp` | — | GM后台 |
| 32 | GuiGuDaoRen | `CGuiGuDaoRen.cpp` | — | 鬼谷道人 |
| 33 | HttpRequest | `CHttpRequest.cpp` | — | HTTP请求 |
| 34 | KiaFuRecharge | `CKiaFuRecharge.cpp` | — | 开服充值 |
| 35 | KunExt | `CKunExt.cpp` | — | 鲲系统 |
| 36 | LevelRefining | `CLevelRefining.cpp` | — | 装备精炼 |
| 37 | LittleHelper | `CLittleHelper.cpp` | — | 小助手 |
| 38 | MingGeExt | `CMingGeExt.cpp` | — | 命格 |
| 39 | MoneyRewardTask | `CMoneyRewardTask.cpp` | ~2,560 | 金币奖励任务 |
| 40 | MonthlyChouJiang | `CMonthlyChouJiang.cpp` | — | 月卡抽奖 |
| 42 | ObjAttrs | `CObjAttrs.cpp` | — | 对象属性 |
| 43 | ObjCarrier | `CObjCarrier.cpp` | — | 对象载具 |
| 44 | ObjState | `CObjState.cpp` | — | 对象状态 |
| 45 | RankMirror | `CRankMirror.cpp` | — | 排行榜镜像 |
| 46 | RefreshMonster | `CRefreshMonster.cpp` | — | 刷新怪物 |
| 51 | ShiZhuang | `CShiZhuang.cpp` | — | 时装 |
| 52 | SqiderQueen | `CSqiderQueen.cpp` | — | 蜘蛛女王 |
| 53 | SuperTeHui | `CSuperTeHui.cpp` | — | 超级特惠 |
| 54 | Territory | `CTerritory.cpp` | — | 领土战 |
| 55 | TestServerReward | `CTestServerReward.cpp` | — | 测试服奖励 |
| 56 | TreasureMap | `CTreasureMap.cpp` | — | 藏宝图 |
| 57 | VipClub | `CVipClub.cpp` | — | Vip俱乐部 |
| 59 | Wan360 | `CWan360.cpp` | — | 360平台 |
| 60 | WuHunShop | `CWuHunShop.cpp` | — | 武魂商店 |
| 61 | XinMaiMap | `CXinMaiMap.cpp` | — | 心法地图 |
| 62 | XinMo | `CXinMo.cpp` | — | 心魔 |
| 63 | XingMai | `CXingMai.cpp` | — | 星脉 |
| 65 | ActivityWorldBoss | `CActivityWorldBoss.cpp` | — | 世界BOSS活动 |
| 66 | PeerlessWar | `CPeerlessWar.cpp` | — | 绝世战 |

> **注意**: 以上列表来自 `gameserver/decompiled/` 目录扫描。部分模块可能已有部分实现。

## 配置表文件

`gameserver/ServerConfig/Tables/` 目录包含游戏配置表（TXT格式），当前已支持的配置表包括：
- 活动(Activity)、物品(Item)、怪物(Monster)、地图(Map)、技能(Skill) 等核心表
- GuardPrivilege(护卫特权)、SpecialEquip(特殊装备)、BlackMarket(黑市)、TianLing(天灵)、OutLinkFestival(外部活动) 等新模块表

所有配置表在 `gameserver/CfgData.cpp` 的 `init()` 函数中加载。
