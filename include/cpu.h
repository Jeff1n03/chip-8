#ifndef CPU_H
#define CPU_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
        uint8_t Disp[32][64];
        uint8_t Mem[4096];
        uint8_t V[16];
        uint16_t I;
        uint16_t PC;
        uint8_t SP;
        uint8_t DT;
        uint8_t ST;

} Chip8;

Chip8 *createChip8(uint16_t *instr, int len);

void destroyChip8(Chip8 *cpu);

void CLS(Chip8 *cpu);

void RET(Chip8 *cpu);

void JP(Chip8 *cpu, uint16_t addr);

void CALL(Chip8 *cpu, uint16_t addr);

#endif
