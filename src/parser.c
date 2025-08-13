#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>

static inline int isLittleEndian() {
    uint16_t x = 0x0001;
    return *(uint8_t *)&x;
}

static void bigEndian(uint16_t *instr, size_t len) {
    for (int i = 0; i < len; i++) {
        instr[i] = (instr[i] << 8) | (instr[i] >> 8);
    }
}

Parser *parse(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    if (size % sizeof(uint16_t) != 0) {
        return NULL;
    }
    int len = size / sizeof(uint16_t);
    rewind(file);
    Parser *parser = malloc(sizeof(Parser));
    parser->instr = malloc(size);
    parser->len = len;
    if (fread(parser->instr, sizeof(uint16_t), len, file) != len) {
        freeParser(parser);
        return NULL;
    }
    if (isLittleEndian()) {
        bigEndian(parser->instr, parser->len);
    }
    return parser;
}

void freeParser(Parser *parser) {
    if (parser != NULL) {
        if (parser->instr != NULL) {
            free(parser->instr);
        }
        free(parser);
    }
}
