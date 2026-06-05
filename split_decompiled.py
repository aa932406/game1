#!/usr/bin/env python3
"""
Fast streaming split of decompiled gameserver.cc by class.
"""
import os
import sys

INPUT = "gameserver.cc"
OUTPUT_DIR = "gameserver/decompiled"
SEP = "#" * 37

os.makedirs(OUTPUT_DIR, exist_ok=True)

# State
current_class = "00_globals"  # default bucket for non-class code
current_methods = []
files = {}  # class_name -> file handle
counts = {}  # class_name -> method count
method_buf = []
in_method = False
line_num = 0

def flush_method():
    global in_method, method_buf, current_class, current_methods
    if not method_buf:
        return
    # Determine class from first line
    first = method_buf[0]
    # Look for " __cdecl ClassName::" pattern
    idx = first.find(" __cdecl ")
    if idx >= 0:
        rest = first[idx + 9:]  # after "__cdecl "
        # Find the "::"
        scope = rest.find("::")
        if scope >= 0:
            current_class = rest[:scope]
        else:
            current_class = "00_globals"
    else:
        current_class = "00_globals"
    
    # Write to appropriate file
    if current_class not in files:
        fpath = os.path.join(OUTPUT_DIR, f"{current_class}.cpp")
        files[current_class] = open(fpath, 'w', encoding='utf-8')
        files[current_class].write(f"// Decompiled: {current_class}\n// Source: {INPUT}\n\n")
        counts[current_class] = 0
    
    files[current_class].write(f"{SEP}\n")
    for line in method_buf:
        files[current_class].write(line.rstrip('\r\n') + '\n')
    files[current_class].write('\n')
    counts[current_class] = counts.get(current_class, 0) + 1
    method_buf = []

try:
    with open(INPUT, 'r', encoding='utf-8', errors='replace') as f:
        for line in f:
            line_num += 1
            stripped = line.rstrip('\r\n')
            
            if stripped == SEP:
                # Separator line - flush current method
                flush_method()
            else:
                method_buf.append(line)
            
            if line_num % 50000 == 0:
                print(f"  Progress: {line_num} lines...", file=sys.stderr)
    
    # Flush last method
    flush_method()

finally:
    # Close all files
    for fh in files.values():
        fh.close()

# Write summary
with open(os.path.join(OUTPUT_DIR, "_summary.txt"), 'w', encoding='utf-8') as sf:
    sf.write(f"Decompiled file split summary\n")
    sf.write(f"Source: {INPUT}\n")
    sf.write(f"Total classes: {len(counts)}\n")
    sf.write(f"Total methods: {sum(counts.values())}\n\n")
    sf.write(f"{'Class':<35} {'Methods':>8}\n")
    sf.write(f"{'-'*35} {'-'*8}\n")
    for cls in sorted(counts.keys(), key=lambda c: (-counts[c], c)):
        sf.write(f"{cls:<35} {counts[cls]:>8}\n")

print(f"\nDone! {len(counts)} classes, {sum(counts.values())} methods")
print(f"Output: {OUTPUT_DIR}/")
