SHELL=/bin/bash
CXX = g++
CFLAGS = -g -O0 -Wall -std=c++11
TARGET = test_treasuremap

# Cross-compile for target gameserver architecture (uncomment if needed):
# CXX = x86_64-linux-gnu-g++

all: $(TARGET)
	./$(TARGET)

$(TARGET): test_treasuremap.cpp
	$(CXX) $(CFLAGS) -o $@ $<

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean
