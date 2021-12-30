UNAME_S=$(shell uname -s)

CC=clang
CFLAGS=-g -D_DEBUG -DSOGE_IMPORT
LDFLAGS=-L../bin/ -lsoge
INCLUDES=-Isrc -I../engine/src

ifeq ($(UNAME_S), Linux)
	LDFLAGS+=-Wl,-rpath=./
endif

SRC=$(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ=$(SRC:.c=.o)
BIN=../bin/game

.PHONY: all clean

all: dirs engine $(BIN)

dirs:
	mkdir -p ../bin
	mkdir -p ../bin/logs

engine:
	cd ../$@ && make

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<  $(INCLUDES)

clean:
	cd ../engine && make clean
	$(RM) -rf $(OBJ) ../bin