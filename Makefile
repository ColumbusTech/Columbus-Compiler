TARGET = ColumbusCompiler
CC = g++
SRC = ./*.cpp
INCL = -I./

all:
	$(CC) $(SRC) -o $(TARGET) $(INCL) -std=c++14






