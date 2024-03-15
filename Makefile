RAYLIB_PATH = ../../../raylib/src
PLATFORM = PLATFORM_DESKTOP

CC=gcc
CFLAGS=-Wall -Wextra -pedantic # for more warnings and checks
LDFLAGS=-lraylib -lm
OBJ_DIR=obj
BIN_DIR=bin
SOURECES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURECES))
EXECUTABLE=$(BIN_DIR)/only2digit

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
