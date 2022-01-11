# Makefile
#
# Copyright (c) 2022 Dmytro Zykov
#
# This file is a part of the vally project, and may only be used,
# modified and distributed under the terms of the MIT License, 
# LICENSE.md. By continuing to use, modify and distribute this file 
# you inidicate that you have read the license and accept it fully.

# Get OS name
UNAME_S=$(shell uname -s)

CMAKE_CONFIG=cmake -S . -B ./build

ifeq ($(UNAME_S), Linux)
	CMAKE_GENERATOR=
	CMAKE_MAKE=cd build && make
else
	CMAKE_GENERATOR=-G "MinGW Makefiles"
	CMAKE_MAKE=cmake --build ./build
endif

CC=gcc
CFLAGS=-g -Wvarargs -Wall -D_CRT_SECURE_NO_WARNINGS -fPIC -DVALLY_DEBUG -DVALLY_BUILD_DLL
LDFLAGS=-shared deps/glfw/build/src/libglfw3.a deps/glad/src/glad.o deps/log/src/log.o deps/cvec/src/cvec.o
ifeq ($(UNAME_S), Linux)
	LDFLAGS+=-ldl -lpthread -lm
else
	LDFLAGS+=-lglu32 -lopengl32 -luser32 -lgdi32 -lws2_32 -lkernel32 -static-libgcc
endif
INCLUDES=-Isrc -Iinclude -Ideps/glfw/include -Ideps/glad/include -Ideps/log/src -Ideps/cvec/src -Ideps/stb -Ideps/cglm/include

SRC=$(wildcard src/vally/**/*.c) $(wildcard src/vally/**/**/*.c) $(wildcard src/vally/**/**/**/*.c)
OBJ=$(SRC:.c=.o)

# platform dependant lib names
ifeq ($(UNAME_S), Linux)
	BIN=bin/libvally.so
else
	BIN=bin/vally.dll
endif

.PHONY: all libs clean

all: dirs libs $(BIN)

# Build all required libraries
libs:
	cd deps/glfw && $(CMAKE_CONFIG) $(CMAKE_GENERATOR) -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF && $(CMAKE_MAKE)
	cd deps/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c -fPIC
	cd deps/log && $(CC) -o src/log.o -Isrc -c src/log.c -fPIC -DLOG_USE_COLOR
	cd deps/cvec && $(CC) -o src/cvec.o -Isrc -c src/cvec.c -fPIC

dirs:
	mkdir -p bin

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	$(RM) -rf $(OBJ) $(BIN)
	$(RM) -rf deps/glfw/build
	$(RM) deps/glad/src/glad.o
	$(RM) deps/log/src/log.o
	$(RM) deps/cvec/src/cvec.o