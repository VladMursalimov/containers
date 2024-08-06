# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Ilist

# Путь к библиотеке и объектным файлам
LIB_DIR = lib
OBJ_DIR = obj

# Имена файлов
LIB_NAME = containers.a
SRC_DIR = list
SRC_FILES = $(SRC_DIR)/list.cpp $(SRC_DIR)/list_tests.cpp $(SRC_DIR)/main.cpp
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_EXEC = test_exec
MAIN_EXEC = main_exec

# Цели makefile
.PHONY: all build test style main clean

all: clean build test

# Стадия build - компиляция библиотеки
build: $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/$(LIB_NAME): $(OBJ_DIR)/list.o
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/list.o: $(SRC_DIR)/list.cpp $(SRC_DIR)/list.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Стадия test - компиляция и запуск тестов
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(OBJ_DIR)/list_tests.o $(LIB_DIR)/$(LIB_NAME)
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o $@

$(OBJ_DIR)/list_tests.o: $(SRC_DIR)/list_tests.cpp $(SRC_DIR)/list.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Стадия main - компиляция и запуск main.cpp
main: $(MAIN_EXEC)
	./$(MAIN_EXEC)

$(MAIN_EXEC): $(OBJ_DIR)/main.o $(LIB_DIR)/$(LIB_NAME)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/list.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Стадия style - форматирование кода
style:
	clang-format -i $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h

# Очистка скомпилированных файлов
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TEST_EXEC) $(MAIN_EXEC)
