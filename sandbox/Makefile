UNAME_S=$(shell uname -s)

CC=gcc
CFLAGS=-g -DVALLY_DEBUG -O3
LDFLAGS=-L../bin/ -lvally -mwindows
INCLUDES=-Isrc -I../include

ifeq ($(UNAME_S), Linux)
	LDFLAGS+=-Wl,-rpath=./
else
	LDFLAGS+=-static-libgcc
endif

SRC=$(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ=$(SRC:.c=.o)
BIN=bin/game

.PHONY: all clean

all: dirs engine $(BIN)

dirs:
	mkdir -p ../bin
	mkdir -p ../bin/logs

engine:
	cd .. && make
	cp -a ../bin/. bin

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<  $(INCLUDES)

clean:
	$(RM) -rf $(OBJ) bin