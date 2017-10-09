
all: ./main

./main: ./main.cpp
	g++ ./main.cpp -o ./main -O2 -Wall -Wextra -Wshadow

.PHONY: all
