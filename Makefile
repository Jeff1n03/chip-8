CC := clang
CFLAGS := -std=c11 -Wall -g

all: bin/chip-8

bin/chip-8: build/main.o build/chip8.o
	$(CC) $(CFLAGS) $^ -o $@

build/main.o: src/main.c include/chip8.h
	$(CC) $(CFLAGS) -c $< -o $@

build/chip8.o: src/chip8.c include/chip8.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm build/* bin/*

.PHONY: all clean
