#!/usr/bin/env python3
"""
Extract missing CFestivalDoubleEleven methods from decompiled code (IDA format)
and generate clean C++ implementations.
"""
import re
import os

DECOMPILED_FILE = "gameserver/decompiled/CFestivalDoubleEleven.cpp"
CURRENT_CPP = "gameserver/FestivalDoubleEleven.cpp"
OUTPUT_FILE = "gameserver/generated/festival_missing_methods.cpp"

def read_file(path):
    with open(path, 'r', encoding='utf-8', errors='replace') as f:
        return f.read()

def get_implemented_methods(content):
    """Get set of method names already implemented in current .cpp"""
    methods = set()
    # Match: void CFestivalDoubleEleven::MethodName(
    for m in re.finditer(r'(?:void|int32_t|bool|int8_t|int64_t)\s+CFestivalDoubleEleven::(\w+)\s*\(', content):
        methods.add(m.group(1))
    return methods

def extract_method_blocks(content):
    """Extract all method blocks from decompiled file.
    Each block starts with ##### and has a method definition like:
    void __cdecl CFestivalDoubleEleven::MethodName(
    """
    blocks = []
    lines = content.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i]
        # Check for method start (##### separator followed by method def)
        if re.match(r'^#{3,}', line):
            # Look at next few lines for a method definition
            method_lines = []
            j = i + 1
            # Collect lines until next ##### or end of file
            while j < len(lines) and not re.match(r'^#{3,}', lines[j]):
                method_lines.append(lines[j])
                j += 1
            
            if method_lines:
                block_text = '\n'.join(method_lines)
                # Check if it has a CFestivalDoubleEleven method definition
                m = re.search(r'(?:void|int32_t|bool|int8_t|int64_t)\s+__cdecl\s+CFestivalDoubleEleven::(\w+)', block_text)
                if m:
                    method_name = m.group(1)
                    blocks.append({
                        'name': method_name,
                        'text': block_text,
                        'start_line': i + 1
                    })
            i = j
        else:
            i += 1
    return blocks

def convert_to_clean_cpp(method_block, method_name):
    """Convert IDA-style decompiled code to clean C++."""
    text = method_block['text']
    
    # Remove __cdecl calling convention
    text = re.sub(r'void\s+__cdecl\s+CFestivalDoubleEleven::', 'void CFestivalDoubleEleven::', text)
    text = re.sub(r'int32_t\s+__cdecl\s+CFestivalDoubleEleven::', 'int32_t CFestivalDoubleEleven::', text)
    text = re.sub(r'bool\s+__cdecl\s+CFestivalDoubleEleven::', 'bool CFestivalDoubleEleven::', text)
    text = re.sub(r'int8_t\s+__cdecl\s+CFestivalDoubleEleven::', 'int8_t CFestivalDoubleEleven::', text)
    text = re.sub(r'int64_t\s+__cdecl\s+CFestivalDoubleEleven::', 'int64_t CFestivalDoubleEleven::', text)
    
    # Remove explicit 'this' parameter: (CFestivalDoubleEleven *const this, ...) -> (...)
    text = re.sub(r'\(CFestivalDoubleEleven \*const this\)', '()', text)
    text = re.sub(r'\(CFestivalDoubleEleven \*const this, ', '(', text)
    
    # Remove this-> prefix
    text = re.sub(r'this->', '', text)
    
    # Remove (const std::string *const str) -> (const std::string& str)
    text = re.sub(r'const std::string \*const (\w+)', r'const std::string\& \1', text)
    
    # Remove *const from pointer parameters
    text = re.sub(r'(\w+ \*+)const ', r'\1 ', text)
    
    # Remove casts like (const std::string *const)&v195 -> v195
    text = re.sub(r'\(const std::string \*const\)&(\w+)', r'\1', text)
    
    # Fix: CFestivalDoubleEleven::methodName(this, args) -> methodName(args)
    text = re.sub(r'CFestivalDoubleEleven::(\w+)\(this([,)])', r'\1(\2', text)
    text = re.sub(r'CFestivalDoubleEleven::(\w+)\(this\)', r'\1()', text)
    
    # Fix Answer::Singleton calls
    text = re.sub(r'Answer::Singleton<([^>]+)>::instance\(\)', r'\1::instance()', text)
    
    # Remove _BYTE arrays used for allocator
    text = re.sub(r'_BYTE \w+\[\d+\];\n', '', text)
    text = re.sub(r'__int64 \w+;\n', '', text)
    
    # Clean up goto labels (lines starting with LABEL_)
    text = re.sub(r'^LABEL_\d+:.*$', '', text, flags=re.MULTILINE)
    
    # Clean up redundant variable declarations
    text = re.sub(r'^\s*(signed\s+)?(__)?(int64|int32|int16|int8)\s+\w+;\s*$', '', text, flags=re.MULTILINE)
    
    # Fix DayTime calls
    text = re.sub(r'Answer::DayTime::(\w+)', r'\1', text)
    
    # Clean up std::string temporary patterns
    # std::string::string(&tname, "xxx", &alloc) -> std::string tname("xxx")
    text = re.sub(r'std::string::string\(&(\w+), "([^"]+)", [^)]+\)', r'std::string \1("\2")', text)
    text = re.sub(r'std::string::operator=\(&(\w+), "([^"]+)"\)', r'\1 = "\2"', text)
    
    # Convert MySqlDBGuard usage
    text = re.sub(r'Answer::MySqlDBGuard::MySqlDBGuard\(&(\w+), (\w+)\)', r'Answer::MySqlDBGuard \1(\2)', text)
    text = re.sub(r'Answer::MySqlDBGuard::~MySqlDBGuard\(&(\w+)\)', r'', text)
    text = re.sub(r'Answer::MySqlQuery::MySqlQuery\(&(\w+), (\w+)\)', r'Answer::MySqlQuery \1(\2)', text)
    text = re.sub(r'Answer::MySqlQuery::~MySqlQuery\(&(\w+)\)', r'', text)
    
    # Simplify string usage
    text = re.sub(r'const char \*\)std::string::c_str\(&(\w+)\)', r'\1.c_str()', text)
    text = re.sub(r'std::string::c_str\(&(\w+)\)', r'\1.c_str()', text)
    
    # Fix snprintf with string
    text = re.sub(r'snprintf\((\w+), \d+, "([^"]*)", v[^)]+\)', r'snprintf(\1, sizeof(\1), "\2")', text)
    
    return text

def main():
    decompiled = read_file(DECOMPILED_FILE)
    current_cpp = read_file(CURRENT_CPP)
    
    implemented = get_implemented_methods(current_cpp)
    print(f"Already implemented methods ({len(implemented)}): {sorted(implemented)}")
    
    blocks = extract_method_blocks(decompiled)
    print(f"Found {len(blocks)} method blocks in decompiled file")
    
    # Filter out already-implemented methods
    missing = [b for b in blocks if b['name'] not in implemented]
    
    # Also filter out methods that are utility/helper (e.g., not declared in header)
    # and methods we already implemented manually (initCfgData, etc.)
    already_done = {'Init', 'initCfgData', 'initOpenList', 'HotUpdate', 'OnDaySwitch', 
                    'OnNewMinute', 'IsInTime', 'isOpen', 'IsOpen', 'needShowIcon',
                    'getIconState', 'GetIconState', 'GetWorldBossIconState',
                    'GetMoYuShiJieIconState', 'loadRankData', 'resetRankData',
                    'parseItemVectorString', 'parseShopGoodsString'}
    
    missing = [b for b in missing if b['name'] not in already_done]
    
    print(f"Missing methods ({len(missing)}):")
    for b in missing:
        print(f"  - {b['name']} (line {b['start_line']})")
    
    # Generate clean C++ code
    output_parts = []
    output_parts.append('// ============ Auto-generated missing method implementations ============\n')
    
    for block in missing:
        clean_code = convert_to_clean_cpp(block, block['name'])
        if clean_code.strip():
            output_parts.append(clean_code)
            output_parts.append('\n\n')
    
    result = ''.join(output_parts)
    
    os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        f.write(result)
    
    print(f"\nGenerated {OUTPUT_FILE} ({len(result)} chars)")

if __name__ == '__main__':
    main()
