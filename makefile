# Variables
CXX=clang++
CPPFLAGS=-Wall -O2 --std=c++17
OUTPUT_DIR=build
OBJ_DAY1=src/day1.o
TEST_INPUT=

# Suffix Rules
.SUFFIXES: .o .cpp

# Build
day1: $(OBJ_DAY1)
	$(CXX) $(CPPFLAGS) $(OBJ_DAY1) -o $(OUTPUT_DIR)/day1


# Test
test-day1: $(TEST_INPUT) day1
	build/day1 < $(TEST_INPUT)
	
