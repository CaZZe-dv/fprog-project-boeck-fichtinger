# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable
TARGET = main_program
TEST_EXEC = test_program

# Source and header files
SRCS = main.cpp
TEST_SRCS = test.cpp
HEADERS = RedBlackTree.h TextProcessor.h

# Default target
all: $(TARGET)

# Direct compilation into executable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Compile and run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRCS)

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(TEST_EXEC)

# Phony targets (not real files)
.PHONY: all clean test
