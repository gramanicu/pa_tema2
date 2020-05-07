# Copyright 2020 Grama Nicolae

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -g -O3 -std=c++17

build: p1 p2 p3 p4

p1: src/p1.cpp
	$(CC) -std=c++17 src/p1.cpp -o p1 $(CFLAGS)

p2: src/p2.cpp
	$(CC) -std=c++17 src/p2.cpp -o p2 $(CFLAGS)

p3: src/p3.cpp
	$(CC) -std=c++17 src/p3.cpp -o p3 $(CFLAGS)

p4: src/p4.cpp
	$(CC) -std=c++17 src/bonus.cpp -o p4 $(CFLAGS)

run-p1:
	./p1
run-p2:
	./p2
run-p3:
	./p3
run-p4:
	./p4

clean:
	rm -f p1 p2 p3 p4

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file */*.cpp
	clang-format -i -style=file */*.hpp
