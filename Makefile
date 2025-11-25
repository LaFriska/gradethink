# Set of C compiler to gcc
CC=gcc
CFLAGS= -Wall -Wconversion -g -fsanitize=address

all: src/main.o src/parser.o src/structures.o src/display.o
	$(CC) $(CFLAGS) $^ -o gradethink

.PHONY: clean 
clean: 
	rm src/*.o gradethink >/dev/null 2>/dev/null || true