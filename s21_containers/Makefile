# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(GTEST_DIR)/include
AR = ar
ARFLAGS = rcs
TARGET = main
TEST_TARGET = run_tests
LIB_NAME = containers.a

# Directories
SRC_DIR = .
BUILD_DIR = build
GTEST_DIR = /usr/src/gtest

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Object files
LIB_OBJS = $(BUILD_DIR)/list.o
TEST_OBJS = $(BUILD_DIR)/tests.o
MAIN_OBJS = $(BUILD_DIR)/main.o

# Targets
.PHONY: all clean format library tests main

all: library tests main

library: $(LIB_NAME)

tests: $(TEST_TARGET)

main: $(TARGET)

$(TARGET): $(MAIN_OBJS) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJS) $(LIB_NAME)

$(TEST_TARGET): $(TEST_OBJS) $(LIB_NAME) $(GTEST_DIR)/gtest-all.o
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS) $(LIB_NAME) $(GTEST_DIR)/gtest-all.o -lpthread
	./$(TEST_TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_NAME): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

format:
	clang-format -i $(SRCS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(LIB_NAME) $(TEST_TARGET)

.PHONY: clean all format
