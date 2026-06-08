#pragma once

#include "stdafx.h"

// 比较谓词函数声明
bool GreaterItem(const Item* a, const Item* b);
bool GreaterBagItem(const Item* b, const Item* a);

// 比较函数声明
int comp(const void* a, const void* b);

// 类型检查函数声明
bool IsFaBaoType(int nItemClass);
bool IsShouHunType(int nItemClass);
bool IsWingEquipSlot(int nSlot);
bool IsMoFuSlot(int nSlot);
bool IsVipEquipSlot(int nSlot);
bool isXingMaiSlot(int nSlot);

// 工具函数声明
int GetLogItemFront(int nItemId);
int GetDayBattle();
int getUserIndex();
const char* GetServerVersion();

// 已存在的函数声明
int sortInt(const void* a, const void* b);
bool IsGoblinType(int nItemClass);
int GetWeekDay();
int roundInt(double d);
bool IsInvalidSlot(int nSlot);