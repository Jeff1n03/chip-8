#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>

static int valid(Parser *parser) {
    /* TODO */
    return 1;
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
    if (fread(parser->instr, sizeof(uint16_t), len, file) != len ||
        !valid(parser)) {
        freeParser(parser);
        return NULL;
    }
    return parser;
}

void freeParser(Parser *parser) {
    free(parser->instr);
    free(parser);
}
