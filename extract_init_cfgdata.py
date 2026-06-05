#!/usr/bin/env python3
"""Extract all sub-activity sections from decompiled CFestivalDoubleEleven::initCfgData()"""

import re
import os

with open('gameserver/decompiled/CFestivalDoubleEleven.cpp', 'r') as f:
    lines = f.readlines()

# Find initCfgData method boundaries
start_line = None
end_line = None
for i, line in enumerate(lines):
    if 'CFestivalDoubleEleven::initCfgData' in line:
        start_line = i
    if start_line and 'OnRecharge' in line and '__cdecl' in line:
        end_line = i
        break

if not start_line or not end_line:
    print("ERROR: Could not find initCfgData boundaries")
    exit(1)

print(f"initCfgData: lines {start_line+1} to {end_line+1}")

# Extract the CONFIG section (before first isOpen call)
config_lines = []
section_starts = []
for i in range(start_line, end_line):
    line = lines[i]
    if 'isOpen(thisa, FESTIVAL_ACTIVITY_TYPE::FAT_' in line:
        section_starts.append(i)
    if not section_starts:
        config_lines.append(line)

print(f"CONFIG section: {len(config_lines)} lines")
print(f"Number of sub-activity sections: {len(section_starts)}")

# Now let's extract key-value pairs from each section
# IDA pattern: Answer::Inifile::getIntValue(&ini, &sectionStr, &keyStr)
# We need to find the string literals used for section names and key names

def find_string_literal(lines, pos):
    """Find a string literal near position pos"""
    # Search backward for pattern: std::string::string(&var, "LITERAL", &alloc)
    for i in range(max(0, pos-5), pos):
        m = re.search(r'std::string::string\(&(\w+),\s*"([^"]+)"', lines[i])
        if m:
            return m.group(2)
    return None

def find_getint_calls(section_lines, section_name):
    """Extract getIntValue calls from a section"""
    calls = []
    i = 0
    while i < len(section_lines):
        line = section_lines[i]
        # Look for getIntValue calls
        if 'Answer::Inifile::getIntValue' in line:
            # The section name and key name should be nearby
            # Format: getIntValue(&ini, &sectionVar, &keyVar)
            m = re.search(r'Answer::Inifile::getIntValue\(&ini,\s*&(\w+),\s*&(\w+)\)', line)
            if m:
                section_var = m.group(1)
                key_var = m.group(2)
                # Find the string values for these variables
                section_str = None
                key_str = None
                for j in range(max(0, i-10), i):
                    sm = re.search(r'std::string::string\(&' + re.escape(section_var) + r',\s*"([^"]+)"', lines[i - (i-10) + j] if i > 0 else section_lines[j])
                    # This is getting complex, let me try a different approach
                    pass
                calls.append((section_var, key_var))
        i += 1
    return calls

# A simpler approach: directly search for string literals that are section names
print("\n=== Section names found in decompiled code ===")
section_names = set()
for i in range(start_line, end_line):
    m = re.search(r'std::string::string\(&\w+,\s*"([A-Z_]+)"', lines[i])
    if m:
        name = m.group(1)
        if name not in ('CONFIG', 'hot_sign', 'version', 'start_time', 'end_day', 'icon', 'icon_hide_day', 
                       'game_start_day', 'unite_start_day', 'drop_group', 'open', 'start_day', 'start_minute',
                       'end_minute', 'mapid', 'x', 'y', 'mid', 'count', 'loop_times', 'loop_reward',
                       'rank_size', 'rank_limit', 'rank_mail', 'rank_reward', 'gift', 'item', 'cost_type',
                       'cost_value', 'limit', 'value', 'reward', 'start_time', 'end_time', 'dis_time',
                       'max_count', 'recharge', 'mail', 'size', 'price', 'broadcast', 'limit_value',
                       'cost', 'expend', 'need_level', 'drop_group', 'rate', 'start_broadcast',
                       'end_broadcast', 'kill_broadcast', 'refresh_cost', 'refresh_broadcast',
                       'draw_cost', 'draw_count', 'chou_jiang_type'):
            section_names.add(name)

# Hmm, this is getting too complex. Let me take a more direct approach.
# I'll read the decompiled code, find all the meaningful string constants
# used with getIntValue/getStrValue calls, and reconstruct the sections manually.

# Let me just search for all string literals used as section names
print("\n=== All string literals used after CONFIG section ===")
all_strings = set()
for i in range(start_line + 200, end_line):  # skip CONFIG
    for m in re.finditer(r'std::string::string\(&\w+,\s*"([^"]+)"', lines[i]):
        all_strings.add(m.group(1))

for s in sorted(all_strings):
    if s.isupper() and len(s) > 2:
        print(f"  Section: {s}")
