CC := clang
CFLAGS := -std=c11 -Wall -g $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2)

all: bin/chip-8

bin/chip-8: build/main.o build/chip8.o build/parser.o build/cycle.o build/video.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

build/main.o: src/main.c include/parser.h include/video.h include/cycle.h include/chip8.h 
	$(CC) $(CFLAGS) -c $< -o $@

build/chip8.o: src/chip8.c include/chip8.h
	$(CC) $(CFLAGS) -c $< -o $@

build/parser.o: src/parser.c include/parser.h
	$(CC) $(CFLAGS) -c $< -o $@

build/cycle.o: src/cycle.c include/cycle.h include/chip8.h
	$(CC) $(CFLAGS) -c $< -o $@

build/video.o: src/video.c include/video.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm build/* bin/*

.PHONY: all clean
