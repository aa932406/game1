#!/usr/bin/env python3
"""
Generate clean, compilable stub implementations for missing CfgData Init* methods.
Each method opens a TXT file, reads records, and stores data in a member variable.
"""
import re

DECOMPILED = 'gameserver/decompiled/CfgData.cpp'
OUTPUT_H = 'gameserver/cfgdata_new_decls.h'
OUTPUT_CPP = 'gameserver/cfgdata_new_stubs.cpp'

with open(DECOMPILED, 'r') as f:
    content = f.read()

# Parse all method blocks
method_pattern = re.compile(
    r'#{3,}\s*\n'
    r'(bool|void|int32_t|int64_t|int8_t|int16_t|uint32_t|float|double|const\s+\w+)\s+__cdecl\s+CfgData::(\w+)\s*'
    r'\(([^)]*)\)\s*\n'
    r'\{',
    re.MULTILINE
)

methods = []
for m in method_pattern.finditer(content):
    name = m.group(2)
    params = m.group(3)
    start = m.start()
    
    brace_count = 0
    in_brace = False
    end = start
    for i in range(m.end(), len(content)):
        c = content[i]
        if c == '{':
            brace_count += 1
            in_brace = True
        elif c == '}':
            brace_count -= 1
            if in_brace and brace_count == 0:
                end = i + 1
                break
    
    if end > start:
        text = content[start:end]
        methods.append({
            'name': name, 'params': params,
            'full_text': text,
        })

# Extract TXT file path, member variable, and field info from decompiled code
def extract_file_path(text):
    m = re.search(r'OpenFromTXT[^"]*"([^"]+)"', text)
    return m.group(1) if m else None

def extract_member_var(text, name):
    """Find the main member variable used for storing data"""
    # Look for std::map::operator[] or std::list::push_back patterns
    m = re.search(r'std::(map|list)<[^>]+>::operator\[\]\(&(\w+)', text)
    if m:
        return m.group(2)
    m = re.search(r'std::(map|list)<[^>]+>::push_back\(&(\w+)', text)
    if m:
        return m.group(2)
    # Look for m_ prefix member variables
    members = re.findall(r'&(m_\w+)', text)
    if members:
        return members[0]
    return 'm_' + name[4:] if name.startswith('Init') else 'm_' + name

def extract_struct_name(text):
    """Try to figure out the struct type from the decompiled code"""
    # Look for typical struct variable declarations
    m = re.search(r'(\w+)\s+(\w+);\s*//', text)
    if m:
        stype = m.group(1)
        if stype[0].isupper() and 'std::' not in stype and 'CDBCFile' not in stype:
            return stype
    
    # Look for compound initializer patterns
    patterns = [
        r'(\w+)\s+stu;',
        r'(\w+)\s+reward;',
        r'(\w+)\s+cfg;',
        r'(\w+)\s+info;',
        r'(\w+)\s+item;',
    ]
    for p in patterns:
        m = re.search(p, text)
        if m and m.group(1) not in ('CDBCFile', 'int32_t', 'int64_t', 'int8_t', 'char'):
            return m.group(1)
    
    return 'Cfg_' + name[4:] if name.startswith('Init') else 'Cfg_' + name

def extract_field_info(text):
    """Extract Search_Posistion calls to understand field structure"""
    fields = []
    for m in re.finditer(r'(\w+)\s*=\s*CDBCFile::Search_Posistion\(&(\w+),\s*(\w+),\s*(\d+)\)', text):
        dest = m.group(1)
        tab = m.group(2)
        col = m.group(4)
        fields.append((col, dest, tab))
    
    # Also look for the pattern after cleanup: Search_Posistion(i, 0)
    for m in re.finditer(r'(\w+)\.Search_Posistion\(\s*(\w+),\s*(\d+)\s*\)', text):
        dest = "?"
        col = m.group(3)
        fields.append((col, dest, m.group(1)))
    
    return fields

# Generate stub implementations for missing Init* methods only
existing_cpp = set()
try:
    with open('gameserver/CfgData.cpp', 'r') as f:
        e = f.read()
        existing_cpp = set(re.findall(r'void CfgData::(\w+)\s*\(', e))
except:
    pass

output_cpp = []
output_h = []

for method in sorted(methods, key=lambda m: m['name']):
    name = method['name']
    if name in existing_cpp:
        continue
    if not name.startswith('Init'):
        continue
    
    params = method['params']
    # Clean params
    params = re.sub(r'CfgData\s*\*?\s*(?:const\s+)?this\s*,?\s*', '', params)
    params = params.strip()
    if params.endswith(','):
        params = params[:-1].strip()
    
    txt_file = extract_file_path(method['full_text'])
    member_var = extract_member_var(method['full_text'], name)
    struct_name = extract_struct_name(method['full_text'])
    
    file_label = f"FILE_{name.upper()}"
    if txt_file:
        file_label = f"\"{txt_file}\""
    
    # Get field count to determine number of columns
    fields = extract_field_info(method['full_text'])
    max_col = 0
    for col, dest, _ in fields:
        try:
            c = int(col)
            if c > max_col:
                max_col = c
        except:
            pass
    
    # Generate implementation
    stub = f"""
void CfgData::{name}({params})
{{
    CDBCFile TabFile(0);
    bool ret = TabFile.OpenFromTXT({file_label});
    if (ret == false)
    {{
        LOG_ERROR("open {file_label} failed, please check!!!");
        return;
    }}

    int32_t iBaseTableCount = TabFile.GetRecordsNum();
    int32_t iBaseColumnCount = TabFile.GetFieldsNum();
    if (iBaseColumnCount <= 0)
    {{
        return;
    }}

    for (int32_t i = 0; i < iBaseTableCount; ++i)
    {{
        // TODO: parse and store record
        // Reference decompiled code for field mapping
        // {txt_file or 'no file'}
    }}
}}
"""
    output_cpp.append(stub)
    
    # Generate declaration for header
    output_h.append(f"    void {name}({params});")
    
    # Print info
    print(f"  {name}: {txt_file or 'no file'} -> {member_var}")

# Write files
with open(OUTPUT_CPP, 'w') as f:
    f.write('// Auto-generated stub implementations for missing CfgData Init* methods\n')
    f.write('#include "stdafx.h"\n#include "CfgData.h"\n\n')
    for s in output_cpp:
        f.write(s)

with open(OUTPUT_H, 'w') as f:
    for d in output_h:
        f.write(d + '\n')

print(f"\n\nGenerated {len(output_cpp)} stub implementations")
print(f"Generated {len(output_h)} declarations")
