# (SPDX-License-Identifier: CC-BY-4.0)

.PHONY: build run clean

# Part A:
#
# mlkem-native source and header files
#
# If you are not concerned about minimizing for a specific backend,
# you can just include _all_ source files into your build.
MLKEM_NATIVE_SOURCE=$(wildcard          \
	mlkem_native/**/*.c	  	\
	mlkem_native/**/*.c		\
	mlkem_native/**/**/*.c		\
	mlkem_native/**/**/**/*.c	\
	mlkem_native/**/**/**/**/*.c)

INC=
INC+=-Imlkem_native/
INC+=-Imlkem_native/mlkem
INC+=-Imlkem_native/mlkem/native
INC+=-Imlkem_native/fips202
INC+=-Imlkem_native/fips202/native

# Part B:
#
# Random number generator
#
# !!! WARNING !!!
#
# The randombytes() implementation used here is for TESTING ONLY.
# You MUST NOT use this implementation outside of testing.
#
# !!! WARNING !!!
RNG_SOURCE=$(wildcard test_only_rng/*.c)

# Part C:
#
# Your application source code
APP_SOURCE=$(wildcard *.c)

ALL_SOURCE=$(MLKEM_NATIVE_SOURCE) $(RNG_SOURCE) $(APP_SOURCE)

BUILD_DIR=build
BIN=test_binary

CFLAGS=-DMLKEM_NATIVE_CONFIG_FILE="\"custom_config.h\""

BINARY_NAME_FULL=$(BUILD_DIR)/$(BIN)

$(BINARY_NAME_FULL): $(ALL_SOURCE)
	echo "$@"
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) $^ -o $@

all: run

build: $(BINARY_NAME_FULL)

run: $(BINARY_NAME_FULL)
	./$(BINARY_NAME_FULL)

clean:
	rm -rf $(BUILD_DIR)
