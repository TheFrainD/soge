UNAME_S = $(shell uname -s)

LIB_EXT=dll
ifeq ($(UNAME_S), Linux)
	LIB_EXT=so
endif

CC=gcc
CFLAGS=-g -Wvarargs -Wall -Werror -D_DEBUG -DSOGE_EXPORT -D_CRT_SECURE_NO_WARNINGS
LDFLAGS=-shared -lglu32 -lopengl32 -lglfw3 -lkernel32 -luser32 -lgdi32 -lws2_32 -lglad -llog -L../lib
INCLUDES=-I../include -Isrc

SRC=$(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ=$(SRC:.c=.o)
BIN=../bin/soge.$(LIB_EXT)

.PHONY: all clean

all: dirs $(BIN)

dirs:
	mkdir -p ../bin

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<  $(INCLUDES)

clean:
	$(RM) -rf $(OBJ) $(BIN)

