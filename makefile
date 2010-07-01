# vim:noet

CC=g++
CFLAGS=-Wall -lX11 -Isrc/include -c
LDFLAGS=-lX11
SOURCEDIR=src
OBJECTDIR=bin
SOURCES:=$(wildcard $(SOURCEDIR)/*.cpp $(SOURCEDIR)/Command/*.cpp)
OBJECTS=$(SOURCES:$(SOURCEDIR)%.cpp=$(OBJECTDIR)%.o)
SHELL = /bin/sh

.DEFAULT_GOAL := utile

utile: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS)
