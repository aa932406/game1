#!/usr/bin/env python3
"""
Improved extraction: convert IDA decompiler output to clean C++ code.
Transforms:
  CDBCFile::CDBCFile(&TabFile, 0)       -> CDBCFile TabFile(0)
  CDBCFile::OpenFromTXT(&TabFile, x)    -> TabFile.OpenFromTXT(x)
  CDBCFile::Search_Posistion(&T, i, c)  -> T.Search_Posistion(i, c)
  CDBCFile::GetRecordsNum(&TabFile)     -> TabFile.GetRecordsNum()
  CDBCFile::GetFieldsNum(&TabFile)      -> TabFile.GetFieldsNum()
  CDBCFile::~CDBCFile(&TabFile)         -> (removed, automatic)
  std::string::string(&s, ...)          -> s = ...
  std::vector<...>::vector(&v)          -> v.clear() (implicitly constructed)
  std::vector<...>::~vector(&v)         -> (removed, automatic)
  if ( !X )                             -> if ( X == false )
  m_Wan360RewardMap[index]              -> m_Wan360RewardMap[index]
  Answer::Logger::print(level, msg)     -> LOG_ERROR(msg)
  memset(&stu, 0, sizeof(stu)); ...     -> stu = {}
  Answer::DayTime::StringToIntTime(&s)  -> Answer::DayTime::StringToIntTime(s)
"""
import re
import os

DECOMPILED = 'gameserver/decompiled/CfgData.cpp'
OUTPUT_CPP = 'gameserver/cfgdata_new_methods.cpp'
CURRENT_CPP = 'gameserver/CfgData.cpp'

with open(DECOMPILED, 'r') as f:
    content = f.read()

with open(CURRENT_CPP, 'r') as f:
    current_content = f.read()

# Existing methods
existing_methods = set(re.findall(r'void CfgData::(\w+)\s*\(', current_content))

# Parse method blocks
method_pattern = re.compile(
    r'#{3,}\s*\n'
    r'(bool|void|int32_t|int64_t|int8_t|int16_t|uint32_t|float|double|const\s+\w+)\s+__cdecl\s+CfgData::(\w+)\s*'
    r'\(([^)]*)\)\s*\n'
    r'\{',
    re.MULTILINE
)

methods = []
for m in method_pattern.finditer(content):
    ret_type = m.group(1)
    name = m.group(2)
    params = m.group(3)
    start = m.start()
    
    # Find end of method
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
        methods.append({
            'name': name, 'ret_type': ret_type, 'params': params,
            'full_text': content[start:end],
        })

print(f"Found {len(methods)} total methods")

def clean_signature(name, params):
    """Clean function signature"""
    # Remove 'CfgData *const this' from params
    params = re.sub(r'CfgData\s*\*?\s*(?:const\s+)?this\s*,?\s*', '', params)
    params = params.strip()
    if params.endswith(','):
        params = params[:-1].strip()
    
    # Clean bool parameter notation
    params = params.replace('false', 'false').replace('true', 'true')
    
    # Simplify bool parameters
    params = re.sub(r'\bint32_t\s+(\w+)\b', r'int32_t \1', params)
    
    return f"void CfgData::{name}({params})"

def clean_body(name, text):
    """Clean the decompiled function body"""
    lines = text.split('\n')
    cleaned = []
    skip_next_brace = False
    
    for line in lines:
        # Remove __cdecl
        line = line.replace('__cdecl ', '')
        
        # Skip the original signature line
        if re.match(r'\s*(bool|void|int32_t|int64_t)\s+__cdecl\s+CfgData::', line):
            continue
        
        # Remove label/variable declarations (IDA-style)
        # Skip lines like:  Wan360Reward *v2; // rax
        if re.match(r'\s+\w+\s+\*?\w+;\s+//', line):
            continue
        
        # Handle if (!x) -> if (x == false)
        line = re.sub(r'if\s*\(\s*!(\w+)\)', r'if ( \1 == false )', line)
        
        # Handle if ( !x )
        line = re.sub(r'if\s*\(\s*!(\w+)\)', r'if ( \1 == false )', line)
        
        # Handle if ( !X() ) style
        line = re.sub(r'if\s*\(\s*!(\w+\([^)]*\))\s*\)', r'if ( \1 == false )', line)
        
        # CDBCFile::CDBCFile(&TabFile, 0) -> CDBCFile TabFile(0)
        # But only for declarations (not in function body)
        line = re.sub(r'CDBCFile::CDBCFile\((&\w+),\s*(\d+)\)', r'CDBCFile \1(\2)', line)
        # Fix: CDBCFile TabFile(0) where &TabFile is in the name
        line = re.sub(r'CDBCFile (&)(TabFile)', r'CDBCFile \2', line)
        
        # General constructor call cleanup
        # CDBCFile::CDBCFile(&var, param) -> var = CDBCFile(param) [if variable already declared]
        line = re.sub(r'(\w+)::(\1)\((&?\w+),\s*(\d+)\)', r'\3 = \1(\4)', line)
        
        # Remove destructor calls: Class::~Class(&var)
        if re.search(r'::~', line):
            continue
        
        # Convert Class::Method(&obj, ...) -> obj.Method(...)
        # CDBCFile::OpenFromTXT(&TabFile, ...) -> TabFile.OpenFromTXT(...)
        line = re.sub(r'(\w+)::(\w+)\(&(\w+)\b', r'\3.\2(', line)
        
        # Convert Class::Method(obj_ptr, ...) -> obj->Method(...)
        line = re.sub(r'(\w+)::(\w+)\((\w+)\b', r'\3.\2(', line)
        
        # Handle Answer::DayTime::StringToIntTime(&s) -> Answer::DayTime::StringToIntTime(s)
        line = re.sub(r'Answer::DayTime::StringToIntTime\(&(\w+)\)', r'Answer::DayTime::StringToIntTime(\1)', line)
        
        # std::string::string(&s, ...) -> s = ... (handled differently)
        # std::allocator stuff
        if 'std::allocator' in line:
            continue
        
        # memset(&stu, 0, sizeof(stu)) -> stu = {}
        if re.search(r'memset\s*\(', line):
            # Find the variable name
            m = re.search(r'memset\s*\(\s*&(\w+)', line)
            if m:
                var_name = m.group(1)
                if var_name in line:
                    # Skip memset line, the struct will be zero-initialized differently
                    continue
        
        # std::vector<...>::vector(&v) or similar - skip constructor calls for members
        # (member vectors are already constructed)
        if re.search(r'std::(vector|list|map|string)::\1\(&', line):
            continue
        if re.search(r'std::(vector|list|map|string)::~', line):
            continue
        
        # std::map<int,...>::operator[](&map, &key) -> map[key]
        line = re.sub(r'std::map<[^>]+>::operator\[\]\(&(\w+),([^)]+)\)', r'\1[\2]', line)
        
        # Fix: v2 = map[key]; -> keep as is but remove the operator= call
        # Wan360Reward::operator=(v2, &stu) -> *v2 = stu
        line = re.sub(r'(\w+)::operator=\((\w+),\s*&(\w+)\)', r'\2 = \3', line)
        line = re.sub(r'(\w+)::operator=\((\w+),\s*(\w+)\)', r'\2 = \3', line)
        
        # std::list<...>::push_back(&list, &item) -> list.push_back(item)
        line = re.sub(r'std::list<[^>]+>::push_back\(&(\w+),\s*&(\w+)\)', r'\1.push_back(\2)', line)
        line = re.sub(r'std::list<[^>]+>::push_back\(&(\w+),\s*(\w+)\)', r'\1.push_back(\2)', line)
        
        # CItemHelper::parseItemVectorString(&result, &str) -> CItemHelper::parseItemVectorString(result, str)
        line = re.sub(r'CItemHelper::parseItemVectorString\(&(\w+),\s*&(\w+)\)', r'CItemHelper::parseItemVectorString(\1, \2)', line)
        
        # std::vector<...>::operator=(&v1, &v2) -> v1 = v2
        line = re.sub(r'std::vector<[^>]+>::operator=\(&(\w+),\s*&(\w+)\)', r'\1 = \2', line)
        
        # Remove explicit this-> 
        line = line.replace('this->', '')
        
        # Fix CDBCFile objects - remove leading & from method calls on TabFile
        # TabFile.OpenFromTXT(..., &TabFile) -> TabFile.OpenFromTXT(...)
        
        # Handle Answer::Logger::print -> LOG_ERROR
        line = re.sub(r'Answer::Logger::print\(Answer::LogLevel::LOG_LEVEL_ERROR,\s*"([^"]+)"\)', r'LOG_ERROR("\1")', line)
        
        # Handle #include
        line = line.replace('#include', '// #include')
        
        # Clean up empty lines
        line = line.rstrip()
        cleaned.append(line)
    
    return '\n'.join(cleaned)

def get_useful_info(name, text):
    """Extract the TXT file path and struct mapping info from decompiled code"""
    info = {}
    
    # Find TXT file path
    txt_match = re.search(r'OpenFromTXT\([^,]+,\s*"([^"]+)"\)', text)
    if txt_match:
        info['txt_file'] = txt_match.group(1)
    
    # Find LOG_ERROR message
    log_match = re.search(r'LOG_ERROR\("([^"]+)"\)', text)
    if log_match:
        info['error_msg'] = log_match.group(1)
    
    # Find the first struct variable
    struct_match = re.search(r'\w+\s+(\w+);\s*//', text)
    if struct_match:
        info['struct_name'] = struct_match.group(1)
    
    return info

# Process missing Init* methods
missing_init = {m['name'] for m in methods if m['name'].startswith('Init')} - existing_methods

output_cpp = []
output_h = []
output_info = []

for name in sorted(missing_init):
    found = [m for m in methods if m['name'] == name]
    if found:
        method = found[0]
        sig = clean_signature(name, method['params'])
        body = clean_body(name, method['full_text'])
        
        # Extract info
        info = get_useful_info(name, method['full_text'])
        info['name'] = name
        output_info.append(info)
        
        # Find the actual body (after {)
        brace_pos = body.find('{')
        if brace_pos >= 0:
            result = f"\n{sig}\n{body[brace_pos:]}\n"
        else:
            result = f"\n{sig}\n{{\n    // TODO: implement\n}}\n"
        
        output_cpp.append(result)
        
        # Generate header declaration
        params = method['params']
        params = re.sub(r'CfgData\s*\*?\s*(?:const\s+)?this\s*,?\s*', '', params)
        params = params.strip()
        if params.endswith(','):
            params = params[:-1].strip()
        output_h.append(f"    void Init{name[4:] if name.startswith('Init') else name}({params});")
        
        txt = info.get('txt_file', 'UNKNOWN')
        print(f"  {name}: {txt}")
    else:
        print(f"  NOT FOUND: {name}")

# Write output
with open(OUTPUT_CPP, 'w') as f:
    f.write('// Auto-extracted from decompiled CfgData.cpp\n')
    f.write('// These are approximating the original source code.\n')
    f.write('// Compile errors expected - fix each method as needed.\n\n')
    f.write('#include "stdafx.h"\n')
    f.write('#include "CfgData.h"\n\n')
    for block in output_cpp:
        f.write(block)

with open('gameserver/cfgdata_new_decls.txt', 'w') as f:
    for decl in output_h:
        f.write(decl + '\n')

print(f"\n\n=== Summary ===")
print(f"Written {len(output_cpp)} method implementations to cfgdata_new_methods.cpp")
print(f"Written {len(output_h)} declarations to cfgdata_new_decls.txt")

# Print all TXT files referenced
print(f"\n=== TXT files loaded by new methods ===")
for info in sorted(output_info, key=lambda x: x.get('txt_file', '')):
    txt = info.get('txt_file', '?')
    name = info.get('name', '?')
    if txt != '?':
        print(f"  {txt} -> {name}")
