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

day3: src/day3.o
	$(CXX) $(CPPFLAGS) -o build/day3 src/day3.o

day4: src/day4.o
	$(CXX) $(CPPFLAGS) -o build/day4 src/day4.o

all: day1 day2 day3

clean:
	rm src/*.o
	rm build/*