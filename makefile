# Variables
CXX = g++
CXXFLAGS = -g -Werror -Wextra -Wall
SRC_DIR = src
TEST_DIR = test
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
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/echecs.cpp -o $(EXECUTABLE_SRC)

# Exécution avec l'entrée depuis berger.txt
run_berger:
	clear
	cat $(TEST_DIR)/perso/berger.txt | ./$(EXECUTABLE_SRC)

# Exécution
run: compile
	clear
	./$(EXECUTABLE_SRC)

# Compilation et exécution des tests
test_1: compile
	clear
	cd $(TEST_DIR) && ./test-level.sh 1 && cd ..

test_2: compile
	clear
	cd $(TEST_DIR) && ./test-level.sh 2 && cd ..

# Nettoyage
clean:
	rm -f $(EXECUTABLE_SRC)
