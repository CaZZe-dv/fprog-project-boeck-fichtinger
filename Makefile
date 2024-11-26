# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable
TARGET = program

# Source and header files
SRCS = main.cpp
HEADERS = RedBlackTree.h TextProcessor.h

# Default target
all: $(TARGET)

# Direct compilation into executable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up build artifacts
clean:
	rm -f $(TARGET)

# Phony targets (not real files)
.PHONY: all clean
