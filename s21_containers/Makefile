# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Ilist -Iqueue -Istack -Ivector

# Путь к библиотеке и объектным файлам
LIB_DIR = lib
OBJ_DIR = obj

# Имена файлов
LIB_NAME = containers.a

# Директории с исходными файлами
LIST_DIR = list
QUEUE_DIR = queue
STACK_DIR = stack
VECTOR_DIR = vector

# Исходные файлы
LIST_SRC_FILES = $(wildcard $(LIST_DIR)/*.cpp)
QUEUE_SRC_FILES = $(wildcard $(QUEUE_DIR)/*.cpp)
STACK_SRC_FILES = $(wildcard $(STACK_DIR)/*.cpp)
VECTOR_SRC_FILES = $(wildcard $(VECTOR_DIR)/*.cpp)
TEST_SRC_FILE = tests.cpp

SRC_FILES = $(LIST_SRC_FILES) $(QUEUE_SRC_FILES) $(STACK_SRC_FILES) $(VECTOR_SRC_FILES) $(TEST_SRC_FILE)

# Объектные файлы
OBJ_FILES = $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)

# Тестовый исполняемый файл
TEST_EXEC = test_exec

# Основной исполняемый файл (если есть)
MAIN_EXEC = main_exec

# Цели makefile
.PHONY: all build test style main clean

all: clean build test

# Сборка библиотеки и всех объектных файлов
build: $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/$(LIB_NAME): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Сборка объектных файлов
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Тестирование
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o $@

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TEST_EXEC) $(MAIN_EXEC)

# Основная программа (при необходимости)
main: $(MAIN_EXEC)

style:
	clang-format -n */*.cpp */*.h --style=Google

$(MAIN_EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@
