#!/usr/bin/env python3
import subprocess, re, os

os.chdir('/home/gameserver/gameserver')

# Get all decompiled class names
result = subprocess.run(['ls', 'decompiled/'], capture_output=True, text=True)
decompiled_files = [f.replace('.cpp','') for f in result.stdout.split() if f.endswith('.cpp') and f != '_summary.txt']

# Get all classes implemented in CfgData.cpp
result = subprocess.run(['grep', '-oP', r'\w+(?=::)', 'CfgData.cpp'], capture_output=True, text=True)
cfgdata_impl = set(result.stdout.split())

# Get all classes implemented in ItemEffect.cpp  
result = subprocess.run(['grep', '-oP', r'\w+(?=::)', 'ItemEffect.cpp'], capture_output=True, text=True)
itemeffect_impl = set(result.stdout.split())

# Get all classes implemented in Player.cpp
result = subprocess.run(['grep', '-oP', r'\w+(?=::)', 'Player.cpp'], capture_output=True, text=True)
player_impl = set(result.stdout.split())

# Get all classes implemented in DBService.cpp
result = subprocess.run(['grep', '-oP', r'\w+(?=::)', 'DBService.cpp'], capture_output=True, text=True)
dbservice_impl = set(result.stdout.split())

# Get project file base names
result = subprocess.run(['bash', '-c', 'for f in *.cpp *.h; do echo "${f%.*}"; done | sort -u'], capture_output=True, text=True)
project_classes = set(result.stdout.split())

# Get classes from DataStructs.h
result = subprocess.run(['grep', '-oP', '(struct|class) \\w+', 'DataStructs.h'], capture_output=True, text=True)
datastructs_items = set(re.sub(r'(struct|class) ', '', line) for line in result.stdout.split('\n') if line.strip())

# All embedded implementations
all_embedded = cfgdata_impl | itemeffect_impl | player_impl | dbservice_impl | datastructs_items

# Name mapping
extra_mappings = {
    'CExtCharBag': 'Bag', 'CExtCharJueWei': 'JueWei', 'CExtCharTencent': 'Tencent',
    'CExtChrTaskCycle': 'TaskCycle', 'CGMBackstate': 'GMBackstage', 'CSqiderQueen': 'SpiderQueen',
    'ChrTask': 'Task', 'IMapEvent': 'MapEvent',
    'CDaZheQuan': 'DaZheQuanEffect', 'FaBaoRes': 'FaBaoResourceItem',
}

def map_name(name):
    candidates = [name]
    if name in extra_mappings:
        candidates.append(extra_mappings[name])
    if name.startswith('CExtChar'):
        candidates.append('Char' + name[8:])
    if name.startswith('CExt'):
        candidates.append(name[4:])
    if name.startswith('C') and len(name) > 1 and name[1].isupper():
        candidates.append(name[1:])
    return candidates

# Skip list
skip_classes = {
    '00_globals', '__gnu_cxx', 'std', 'tpoc',
    'MutiConn<DBService>', 'MutiConn<GameService>',
    'initLogger(const char *prefix, Answer',
}

# Categorize
file_matched = {}
embedded_in_cfgdata = {}
embedded_in_itemeffect = {}
embedded_in_player = {}
embedded_in_datastructs = {}
referenced_elsewhere = {}
not_found = []

for dc in decompiled_files:
    if dc in skip_classes:
        continue
    
    candidates = map_name(dc)
    
    # Check file match
    found = False
    for c in candidates:
        if c in project_classes:
            file_matched[dc] = c
            found = True
            break
    if found: continue
    
    # Check embedded in CfgData.cpp
    for c in candidates:
        if c in cfgdata_impl:
            embedded_in_cfgdata[dc] = c
            found = True
            break
    if found: continue
    
    # Check embedded in ItemEffect.cpp
    for c in candidates:
        if c in itemeffect_impl:
            embedded_in_itemeffect[dc] = c
            found = True
            break
    if found: continue
    
    # Check embedded in Player.cpp
    for c in candidates:
        if c in player_impl:
            embedded_in_player[dc] = c
            found = True
            break
    if found: continue
    
    # Check in DataStructs.h
    for c in candidates:
        if c in datastructs_items:
            embedded_in_datastructs[dc] = c
            found = True
            break
    if found: continue
    
    # Check if referenced anywhere in project (excluding decompiled dir)
    for c in candidates:
        result = subprocess.run(['bash', '-c', 
            f'grep -rl "\\b{c}\\b" *.cpp *.h 2>/dev/null | head -3'], 
            capture_output=True, text=True)
        files = [f for f in result.stdout.strip().split('\n') if f.strip()]
        if files:
            referenced_elsewhere[dc] = (c, files[:3])
            found = True
            break
    
    if not found:
        not_found.append(dc)

total_valid = len(decompiled_files) - len(skip_classes)
total_impl = (len(file_matched) + len(embedded_in_cfgdata) + len(embedded_in_itemeffect) + 
              len(embedded_in_player) + len(embedded_in_datastructs) + len(referenced_elsewhere))

print("=" * 75)
print("          反编译目录 vs 项目实现 - 完整对比报告")
print("=" * 75)
print(f"\n反编译类总数: {len(decompiled_files)} (排除辅助类后: {total_valid})")
print(f"\n--- 实现统计 ---")
print(f"  1. 独立文件实现:        {len(file_matched):>3} 个")
print(f"  2. 嵌入 CfgData.cpp:    {len(embedded_in_cfgdata):>3} 个")
print(f"  3. 嵌入 ItemEffect.cpp:  {len(embedded_in_itemeffect):>3} 个")
print(f"  4. 嵌入 Player.cpp:     {len(embedded_in_player):>3} 个")
print(f"  5. 嵌入 DataStructs.h:  {len(embedded_in_datastructs):>3} 个")
print(f"  6. 引用于其他文件:       {len(referenced_elsewhere):>3} 个")
print(f"  7. 完全未实现:          {len(not_found):>3} 个")
print(f"\n  总覆盖率: {total_impl}/{total_valid} = {total_impl/total_valid*100:.1f}%")

print(f"\n{'='*75}")
print(f"1. 独立文件实现 ({len(file_matched)} 个)")
print(f"{'='*75}")
for dc, pc in sorted(file_matched.items()):
    if dc != pc:
        print(f"  {dc} -> {pc}")

print(f"\n{'='*75}")
print(f"2. 嵌入 CfgData.cpp ({len(embedded_in_cfgdata)} 个)")
print(f"{'='*75}")
for dc, emb in sorted(embedded_in_cfgdata.items()):
    print(f"  {dc} -> {emb}")

print(f"\n{'='*75}")
print(f"3. 嵌入 ItemEffect.cpp ({len(embedded_in_itemeffect)} 个)")
print(f"{'='*75}")
for dc, emb in sorted(embedded_in_itemeffect.items()):
    print(f"  {dc} -> {emb}")

print(f"\n{'='*75}")
print(f"4. 嵌入 Player.cpp ({len(embedded_in_player)} 个)")
print(f"{'='*75}")
for dc, emb in sorted(embedded_in_player.items()):
    print(f"  {dc} -> {emb}")

print(f"\n{'='*75}")
print(f"5. 嵌入 DataStructs.h ({len(embedded_in_datastructs)} 个)")
print(f"{'='*75}")
for dc, emb in sorted(embedded_in_datastructs.items()):
    print(f"  {dc} -> {emb}")

print(f"\n{'='*75}")
print(f"6. 引用于其他文件 ({len(referenced_elsewhere)} 个)")
print(f"{'='*75}")
for dc, (c, files) in sorted(referenced_elsewhere.items()):
    print(f"  {dc} -> {c} (在 {', '.join(files)})")

print(f"\n{'='*75}")
print(f"7. 完全未实现 ({len(not_found)} 个)")
print(f"{'='*75}")

# Sub-categorize
log_cls = [c for c in not_found if '_log' in c or c.endswith('log')]
dbdata_cls = [c for c in not_found if 'DBData' in c or (c.endswith('Data') and not c.startswith('Cfg'))]
cfg_cls = [c for c in not_found if c.startswith('Cfg') or c.startswith('cfg')]
item_names = {'AddStarVipTime','BackCityPaper','BlessWater1','BlessWater2',
    'ChongZhiGift','EquipBox','GoblinItem','GoldEgg','GongMingZhi',
    'ItemAddBuff','ItemCombiPoint','ItemCombiScroll','JewelPavilion',
    'LingZhu','OreItem','PetAtkSpd','PetShiHua','RandomBuff','RandomPosPaper',
    'RechargeCard','RechargeValueCard','FamilyMemberCard','ShouChongItem',
    'SkillBook','SkillPointBook','SummonBoss','SuperCurse','TitleCard',
    'UseCurrGift','UseItemGift','VipDrop','WingLevelUp','XinMoExp','YanHua'}
item_cls = [c for c in not_found if c in item_names]
other_cls = [c for c in not_found if c not in log_cls and c not in dbdata_cls and c not in cfg_cls and c not in item_cls]

if log_cls:
    print(f"\n  --- 日志类 ({len(log_cls)} 个) ---")
    for c in sorted(log_cls): print(f"    {c}")
if dbdata_cls:
    print(f"\n  --- DB数据类 ({len(dbdata_cls)} 个) ---")
    for c in sorted(dbdata_cls): print(f"    {c}")
if cfg_cls:
    print(f"\n  --- 配置表类 ({len(cfg_cls)} 个) ---")
    for c in sorted(cfg_cls): print(f"    {c}")
if item_cls:
    print(f"\n  --- 物品效果类 ({len(item_cls)} 个) ---")
    for c in sorted(item_cls): print(f"    {c}")
if other_cls:
    print(f"\n  --- 其他 ({len(other_cls)} 个) ---")
    for c in sorted(other_cls): print(f"    {c}")
