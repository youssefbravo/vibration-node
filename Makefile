# Host (PC) build: unit tests for the portable C modules.
# Windows: use `mingw32-make` (from WinLibs). Linux/macOS: `make`.
#
#   mingw32-make test          build + run all tests
#   mingw32-make test-ringbuf  just the ring buffer
#   mingw32-make test-bitops   just the bit macros
#   mingw32-make -k test       keep going after the first failing suite
#   mingw32-make clean

ifeq ($(origin CC),default)
  CC := gcc
endif

CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -g \
          -Ilib/ringbuf -Ilib/bitops -Ivendor/unity

UNITY := vendor/unity/unity.c

ifeq ($(OS),Windows_NT)
  SHELL := cmd.exe
  EXE   := .exe
  MKDIR := if not exist build mkdir build
  RMDIR := if exist build rmdir /s /q build
  RUN    = build\$(1)$(EXE)
else
  EXE   :=
  MKDIR := mkdir -p build
  RMDIR := rm -rf build
  RUN    = ./build/$(1)
endif

RINGBUF_BIN := build/test_ringbuf$(EXE)
BITOPS_BIN  := build/test_bitops$(EXE)

.PHONY: all test test-ringbuf test-bitops clean

all: $(RINGBUF_BIN) $(BITOPS_BIN)

test: test-ringbuf test-bitops

test-ringbuf: $(RINGBUF_BIN)
	$(call RUN,test_ringbuf)

test-bitops: $(BITOPS_BIN)
	$(call RUN,test_bitops)

$(RINGBUF_BIN): test/test_ringbuf.c lib/ringbuf/ringbuf.c lib/ringbuf/ringbuf.h $(UNITY) | build
	$(CC) $(CFLAGS) -o $@ test/test_ringbuf.c lib/ringbuf/ringbuf.c $(UNITY)

$(BITOPS_BIN): test/test_bitops.c lib/bitops/bitops.h $(UNITY) | build
	$(CC) $(CFLAGS) -o $@ test/test_bitops.c $(UNITY)

build:
	$(MKDIR)

clean:
	$(RMDIR)
