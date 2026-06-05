#!/usr/bin/env python3
"""Merge generated implementations into FestivalDoubleEleven.cpp"""
import re

cpp_path = "gameserver/FestivalDoubleEleven.cpp"
gen_path = "gameserver/generated/festival_missing_body.cpp"

with open(cpp_path, 'r') as f:
    cpp = f.read()
with open(gen_path, 'r') as f:
    gen = f.read()

# Split generated file into individual methods by their signature
# Each method starts with "void CFestivalDoubleEleven::" or "int32_t CFestivalDoubleEleven::" etc.
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

print(f"Generated methods: {list(gen_methods.keys())}")

# Now replace each TODO stub in the cpp file
replacements = []
# Pattern: void CFestivalDoubleEleven::MethodName(..) { // TODO ... }
# Or: int32_t CFestivalDoubleEleven::MethodName(..) { // TODO ... }
for name, body in gen_methods.items():
    # Find the old TODO stub
    pattern = re.compile(
        r'(void|int32_t|bool)\s+CFestivalDoubleEleven::' + re.escape(name) + r'\s*\([^)]*\)\s*\n\s*\{\s*\n\s*// TODO[^}]*\}',
        re.DOTALL
    )
    match = pattern.search(cpp)
    if match:
        old = match.group(0)
        replacements.append((old, body + '\n'))
        print(f"  Will replace: {name}")
    else:
        # Check if method already has a real implementation (not TODO)
        existing = re.search(
            r'(void|int32_t|bool)\s+CFestivalDoubleEleven::' + re.escape(name) + r'\s*\(',
            cpp
        )
        if existing:
            print(f"  SKIP (already has impl or different signature): {name}")
        else:
            print(f"  APPEND (not found in cpp at all): {name}")

# Apply replacements in reverse order to preserve line numbers
for old, new in reversed(replacements):
    cpp = cpp.replace(old, new, 1)

# Write back
with open(cpp_path, 'w') as f:
    f.write(cpp)

print(f"\nReplaced {len(replacements)} TODO stubs")
