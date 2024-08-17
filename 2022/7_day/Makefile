#
# @file Makefile
#
#	AdventOfCode
#
# @author MivojBlazek
#

CXX=g++
CXXFLAGS= -std=c++23 -pedantic -Wall -Wextra

EXEC=main

all: part1

part1: mainPart1.cpp directory.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC)

part2: mainPart2.cpp directory.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC)
