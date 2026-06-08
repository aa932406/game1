#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "CfgData.h"
#include "GameService.h"
#include "DBService.h"

// 比较谓词函数
bool GreaterItem(const Item* a, const Item* b)
{
    if (!a || !b) return false;
    return a->GetItemId() > b->GetItemId();
}

bool GreaterBagItem(const Item* a, const Item* b)
{
    if (!a || !b) return false;
    return a->GetItemId() > b->GetItemId();
}

// 比较函数
int comp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

// 法宝类型检查
bool IsFaBaoType(int nItemClass)
{
    // 法宝类型通常在某个范围内，这里假设1-100是法宝类型
    return nItemClass >= 1 && nItemClass <= 100;
}

// 守护类型检查
bool IsShouHunType(int nItemClass)
{
    // 守护类型通常在另一个范围内，这里假设101-200是守护类型
    return nItemClass >= 101 && nItemClass <= 200;
}

// 翅膀装备槽位检查
bool IsWingEquipSlot(int nSlot)
{
    // 翅膀装备通常在特定槽位，这里假设槽位10是翅膀槽
    return nSlot == 10;
}

// 魔符槽位检查
bool IsMoFuSlot(int nSlot)
{
    // 魔符槽位通常在特定槽位，这里假设槽位11是魔符槽
    return nSlot == 11;
}

// VIP装备槽位检查
bool IsVipEquipSlot(int nSlot)
{
    // VIP装备槽位通常在特定槽位，这里假设槽位12是VIP装备槽
    return nSlot == 12;
}

// 星脉槽位检查
bool isXingMaiSlot(int nSlot)
{
    // 星脉槽位通常在特定槽位，这里假设槽位13是星脉槽
    return nSlot == 13;
}

// 获取日志物品前端
int GetLogItemFront(int nItemId)
{
    // 根据物品ID获取前端显示信息，这里返回物品ID的前缀
    return nItemId / 1000;
}

// 获取每日战斗次数
int GetDayBattle()
{
    // 获取每日战斗次数，这里返回一个默认值
    return 10;
}

// 获取用户索引
int getUserIndex()
{
    // 获取用户索引，这里返回一个默认值
    return 0;
}

// 获取服务器版本
const char* GetServerVersion()
{
    // 返回服务器版本字符串
    return "1.0.0";
}

// 已存在的函数实现
int sortInt(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

bool IsGoblinType(int nItemClass)
{
    // 小鬼类型检查，假设201-300是小鬼类型
    return nItemClass >= 201 && nItemClass <= 300;
}

int GetWeekDay()
{
    // 获取星期几，这里返回一个默认值
    return 1;
}

int roundInt(double d)
{
    // 四舍五入
    return (int)(d + 0.5);
}

bool IsInvalidSlot(int nSlot)
{
    // 无效槽位检查，假设0-15是有效槽位
    return nSlot < 0 || nSlot > 15;
}