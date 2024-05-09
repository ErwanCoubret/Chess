# Variables
CXX = g++
CXXFLAGS = -g -Werror -Wextra -Wall
SRC_DIR = src
TEST_DIR = test
CORE_DIR = core
EXECUTABLE = echecs
EXECUTABLE_SRC = $(SRC_DIR)/$(EXECUTABLE)
EXECUTABLE_TEST = $(EXECUTABLE_SRC)

# Phony targets
.PHONY: all clean test

# Default target
all: clean compile run

# Compilation
compile:
	clear
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/echecs.cpp -o $(EXECUTABLE_SRC) $(CORE_DIR)/*.cpp

# Exécution
run: compile
	./$(EXECUTABLE_SRC)

# Compilation et exécution des tests
test_1: compile
	cd $(TEST_DIR) && ./test-level.sh 1 && cd ..

test_2: compile
	cd $(TEST_DIR) && ./test-level.sh 2 && cd ..

test_3: compile
	cd $(TEST_DIR) && ./test-level.sh 3 && cd ..

test_4: compile
	cd $(TEST_DIR) && ./test-level.sh 4 && cd ..

tests: test_1 test_2 test_3

# Nettoyage
clean:
	rm -f $(EXECUTABLE_SRC)
