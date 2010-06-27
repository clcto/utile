# vim:noet

CC=g++
CFLAGS=-Wall -lX11 -Iinclude -c
LDFLAGS=-lX11
SOURCEDIR=./
OBJECTDIR=./bin/

.PHONY: all
all: utile

utile: main.o Config.o Frame.o Group.o SmartWindow.o
	$(CC) $(LDFLAGS) $(addprefix $(OBJECTDIR), $^) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $*.cpp -o bin/$*.o
