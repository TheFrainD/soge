UNAME_S=$(shell uname -s)

LIB_EXT=dll
LIB_PREFIX=
CMAKE_COMMAND=cmake . -G "MinGW Makefiles" && cmake --build .
ifeq ($(UNAME_S), Linux)
	LIB_EXT=so
	LIB_PREFIX=lib
	CMAKE_COMMAND=cmake . && make
endif

CC=gcc
CFLAGS=-g -Wvarargs -Wall -Werror -D_DEBUG -DSOGE_EXPORT -D_CRT_SECURE_NO_WARNINGS
LDFLAGS=-shared ../vendor/glfw/src/libglfw3.a ../vendor/glad/src/glad.o ../vendor/log/src/log.o
ifeq ($(UNAME_S), Linux)
	LDFLAGS+=-ldl -lpthread -lm
else
	LDFLAGS+=-lglu32 -lopengl32 -luser32 -lgdi32 -lws2_32 -lkernel32 
endif
INCLUDES=-Isrc -I../vendor/glfw/include -I../vendor/glad/include -I../vendor/log/src

SRC=$(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ=$(SRC:.c=.o)
BIN=../bin/$(LIB_PREFIX)soge.$(LIB_EXT)

.PHONY: all libs clean

all: dirs libs $(BIN)

libs:
	cd ../vendor/glfw && $(CMAKE_COMMAND)
	cd ../vendor/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c -fPIC
	cd ../vendor/log && $(CC) -o src/log.o -Isrc -c src/log.c -fPIC 

dirs:
	mkdir -p ../bin

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<  $(INCLUDES)

clean:
	$(RM) -rf $(OBJ) $(BIN)

