CC := clang
CFLAGS := -std=c99 -Wall -g

all: bin/chip-8

bin/chip-8: build/main.o build/cpu.o
	$(CC) $(CFLAGS) $^ -o $@

build/main.o: src/main.c include/cpu.h
	$(CC) $(CFLAGS) -c $< -o $@

build/cpu.o: src/cpu.c include/cpu.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm build/* bin/*

.PHONY: all clean
