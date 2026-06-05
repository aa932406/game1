#!/usr/bin/env python3
"""
Extract missing Init* methods from decompiled CfgData.cpp,
clean up IDA decompiler formatting, and append to current CfgData.cpp.
"""
import re
import os

DECOMPILED = 'gameserver/decompiled/CfgData.cpp'
OUTPUT_CPP = 'gameserver/cfgdata_new_methods.cpp'
OUTPUT_H = 'gameserver/cfgdata_new_decls.txt'
CURRENT_CPP = 'gameserver/CfgData.cpp'

# Read decompiled file
with open(DECOMPILED, 'r') as f:
    content = f.read()

# Read current CfgData.cpp to get existing method names
with open(CURRENT_CPP, 'r') as f:
    current_content = f.read()

# Find all existing method implementations
existing_methods = set(re.findall(r'void CfgData::(\w+)\s*\(', current_content))

print(f"Existing methods in current CfgData.cpp: {len(existing_methods)}")

# Parse decompiled file into method blocks
# Each method starts with ### line pattern and has void __cdecl CfgData::Name(...)
method_pattern = re.compile(
    r'#{3,}\s*\n'
    r'(bool|void|int32_t|int64_t|int8_t|int16_t|uint32_t|float|double|const\s+\w+)\s+__cdecl\s+CfgData::(\w+)\s*'
    r'\(([^)]*)\)\s*\n'
    r'\{',
    re.MULTILINE
)

# Find all method positions
methods = []
for m in method_pattern.finditer(content):
    ret_type = m.group(1)
    name = m.group(2)
    params = m.group(3)
    start = m.start()
    # Find the end of this method block (next ### or end of file)
    end_search = content.find('\n}\n\n', m.end())
    if end_search == -1:
        end_search = content.find('\n}\n', m.end())
    if end_search == -1:
        end_search = len(content)
    else:
        end_search = end_search + 2  # include }
    
    methods.append({
        'name': name,
        'ret_type': ret_type,
        'params': params,
        'start': start,
        'end': end_search,
        'full_text': content[start:end_search],
    })

print(f"Found {len(methods)} methods in decompiled file")

# Get the list of missing Init* methods from init() call
# Read the init() function from decompiled to see what's called
init_calls = set()
init_pattern = re.compile(r'CfgData::(\w+)\s*\(this[^)]*\)')
for m in init_pattern.finditer(content):
    init_calls.add(m.group(1))

# Filter to Init* methods only
init_methods = {m['name'] for m in methods if m['name'].startswith('Init')}
missing_init = init_methods - existing_methods

print(f"\nInit* methods in decompiled: {len(init_methods)}")
print(f"Init* methods missing: {len(missing_init)}")
print(f"Missing Init* methods:")

# Clean up function and add to output
def cleanup_method(method, method_text):
    """Clean up IDA decompiled code to work in normal C++"""
    # Remove __cdecl
    text = method_text.replace('__cdecl ', '')
    
    # Fix function signature: remove `CfgData *const this` from params
    params = method['params']
    # Remove leading 'CfgData *const this' or 'CfgData *this'
    params = re.sub(r'CfgData\s*\*?\s*(?:const\s+)?this\s*,?\s*', '', params)
    params = params.strip()
    if params.endswith(','):
        params = params[:-1].strip()
    
    # Build new signature
    sig = f"void CfgData::{method['name']}({params})"
    
    # Replace `this->` with empty (direct member access since it's a member function)
    # But be careful: some this-> might be in complex expressions
    # Actually, for member functions, we don't need this->
    # But the decompiler puts this-> everywhere
    lines = text.split('\n')
    new_lines = []
    for line in lines:
        # Skip the original signature line (we'll replace it)
        if 'void __cdecl CfgData::' in line or 'void CfgData::' in line:
            if method['name'] in line:
                continue
        # Fix line
        # Remove this->
        line = line.replace('this->', '')
        new_lines.append(line)
    
    # Rebuild
    body = '\n'.join(new_lines)
    # Find where the body starts (after original signature)
    body_start = body.find('{')
    if body_start == -1:
        body_start = 0
    
    result = f"\n{sig}\n{body[body_start:]}\n"
    return result

# Extract all missing Init methods
output_cpp = []
output_h = []

for name in sorted(missing_init):
    found = [m for m in methods if m['name'] == name]
    if found:
        method = found[0]
        cleaned = cleanup_method(method, method['full_text'])
        output_cpp.append(cleaned)
        # Generate header declaration
        params = method['params']
        params = re.sub(r'CfgData\s*\*?\s*(?:const\s+)?this\s*,?\s*', '', params)
        params = params.strip()
        if params.endswith(','):
            params = params[:-1].strip()
        output_h.append(f"    void Init{name[4:] if name.startswith('Init') else name}({params});")
        print(f"  EXTRACTED: {name}")
    else:
        print(f"  NOT FOUND in decompiled: {name}")

# Also check for non-Init methods that are missing
fetch_methods = {m['name'] for m in methods if m['name'].startswith('fetch')}
missing_fetch = fetch_methods - existing_methods
print(f"\nfetch* methods missing: {len(missing_fetch)}")
for name in sorted(missing_fetch):
    found = [m for m in methods if m['name'] == name]
    if found:
        method = found[0]
        cleaned = cleanup_method(method, method['full_text'])
        output_cpp.append(cleaned)
        print(f"  EXTRACTED: {name}")
    else:
        print(f"  NOT FOUND: {name}")

# Write output files
with open(OUTPUT_CPP, 'w') as f:
    f.write('// Auto-extracted from decompiled CfgData.cpp\n')
    f.write('// Missing method implementations\n')
    f.write('#include "stdafx.h"\n')
    f.write('#include "CfgData.h"\n\n')
    for block in output_cpp:
        f.write(block)

with open(OUTPUT_H, 'w') as f:
    for decl in output_h:
        f.write(decl + '\n')

print(f"\n\nWritten {len(output_cpp)} method implementations to {OUTPUT_CPP}")
print(f"Written {len(output_h)} declarations to {OUTPUT_H}")
