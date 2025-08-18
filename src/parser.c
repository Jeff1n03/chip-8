#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>

Parser *parse(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    Parser *parser = malloc(sizeof(Parser));
    fseek(file, 0, SEEK_END);
    parser->len = ftell(file);
    parser->instr = malloc(parser->len);
    rewind(file);
    size_t actualLen = fread(parser->instr, sizeof(uint8_t), parser->len, file);
    if (actualLen != parser->len) {
        freeParser(parser);
        return NULL;
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
