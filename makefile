# Variables
CXX=clang++
CPPFLAGS=-Wall -O2 --std=c++17 -Iinclude

# Suffix Rules
.SUFFIXES: .o .cpp

# Build
day1-part1: src/day1-part1.o
	$(CXX) $(CPPFLAGS) -o build/day1-part1 src/day1-part1.o 

day1-part2: src/day1-part2.o
	$(CXX) $(CPPFLAGS) -o build/day1-part2 src/day1-part2.o 

day1: day1-part1 day1-part2

day2: src/day2.o
	$(CXX) $(CPPFLAGS) -o build/day2 src/day2.o 

all: day1

clean:
	rm src/*.o
	rm build/*