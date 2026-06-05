#!/usr/bin/env python3
"""Append methods from generated file that are not yet in FestivalDoubleEleven.cpp"""
import re

cpp_path = "gameserver/FestivalDoubleEleven.cpp"
gen_path = "gameserver/generated/festival_missing_body.cpp"

with open(cpp_path, 'r') as f:
    cpp = f.read()
with open(gen_path, 'r') as f:
    gen = f.read()

# Get all method names already in cpp
existing_names = set(re.findall(r'^(?:void|int32_t|bool)\s+CFestivalDoubleEleven::(\w+)', cpp, re.MULTILINE))
print(f"Methods in cpp: {sorted(existing_names)}")

# Split generated file into individual methods
gen_methods = {}
current_name = None
current_body = []

for line in gen.split('\n'):
    m = re.match(r'^(void|int32_t|bool)\s+CFestivalDoubleEleven::(\w+)', line)
    if m:
        if current_name and current_body:
            gen_methods[current_name] = '\n'.join(current_body)
        current_name = m.group(2)
        current_body = [line]
    elif current_name:
        current_body.append(line)

if current_name and current_body:
    gen_methods[current_name] = '\n'.join(current_body)

# Find methods not yet in cpp
new_methods = []
for name in sorted(gen_methods.keys()):
    if name not in existing_names:
        new_methods.append(gen_methods[name])
        print(f"  APPEND: {name}")

if new_methods:
    with open(cpp_path, 'a') as f:
        f.write('\n\n// ============ Remaining missing implementations ============\n')
        for m in new_methods:
            f.write(m)
            f.write('\n\n')
    print(f"\nAppended {len(new_methods)} new methods")
else:
    print("No methods to append")
