#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
        uint8_t *instr;
        size_t len;
} Parser;

Parser *parse(char *filename);

void freeParser(Parser *parser);

#endif
