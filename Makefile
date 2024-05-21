CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
DEPS = sokoban.hpp
PROGRAM = Sokoban
OBJECTS = sokoban.o main.o

.PHONY: all clean

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

sokoban.o: sokoban.cpp
	$(CC) $(CFLAGS) -c sokoban.cpp

sokoban: sokoban.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

main: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp