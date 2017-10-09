
all: ./main

./main: ./main.cpp
	g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty

.PHONY: all
