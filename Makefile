# Set of C compiler to gcc
CC=gcc
CFLAGS= -Wall -Wconversion -fsanitize=address

all: src/main.c src/parser.c
	$(CC) $(CFLAGS) $^ -o gradethink

.PHONY: clean 
clean: 
	rm src/*.o gradethink >/dev/null 2>/dev/null || true