UNAME_S=$(shell uname -s)

LIB_EXT=dll
LIB_PREFIX=
CMAKE_CONFIG=cmake -S . -B ./build
CMAKE_GENERATOR=-G "MinGW Makefiles"
CMAKE_MAKE=cmake --build ./build
ifeq ($(UNAME_S), Linux)
	LIB_EXT=so
	LIB_PREFIX=lib
	CMAKE_GENERATOR=
	CMAKE_MAKE=cd build && make
endif

CC=gcc
CFLAGS=-g -Wvarargs -Wall -Werror -D_DEBUG -DSOGE_EXPORT -D_CRT_SECURE_NO_WARNINGS
LDFLAGS=-shared ../vendor/glfw/build/src/libglfw3.a ../vendor/glad/src/glad.o ../vendor/log/src/log.o
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
	cd ../vendor/glfw && $(CMAKE_CONFIG) $(CMAKE_GENERATOR) -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF && $(CMAKE_MAKE)
	cd ../vendor/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c -fPIC
	cd ../vendor/log && $(CC) -o src/log.o -Isrc -c src/log.c -fPIC -DLOG_USE_COLOR

dirs:
	mkdir -p ../bin

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<  $(INCLUDES)

clean:
	$(RM) -rf $(OBJ) $(BIN)
	$(RM) -rf ../vendor/glfw/build
	$(RM) ../vendor/glad/src/glad.o
	$(RM) ../vendor/log/src/log.o

