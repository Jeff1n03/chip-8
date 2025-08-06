#ifndef CPU_H
#define CPU_H

#include <stddef.h>
#include <stdint.h>

#define Y 32
#define X 64

typedef struct {
        uint8_t Disp[Y][X];
        uint8_t Input[16];
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

void SE_IMM(Chip8 *cpu, int x, uint8_t byte);

void SNE_IMM(Chip8 *cpu, int x, uint8_t byte);

void SE(Chip8 *cpu, int x, int y);

void LD_IMM(Chip8 *cpu, int x, uint8_t byte);

void ADD_IMM(Chip8 *cpu, int x, uint8_t byte);

void LD(Chip8 *cpu, int x, int y);

void OR(Chip8 *cpu, int x, int y);

void AND(Chip8 *cpu, int x, int y);

void XOR(Chip8 *cpu, int x, int y);

void ADD(Chip8 *cpu, int x, int y);

void SUB(Chip8 *cpu, int x, int y);

void SHR(Chip8 *cpu, int x);

void SUBN(Chip8 *cpu, int x, int y);

void SHL(Chip8 *cpu, int x);

void SNE(Chip8 *cpu, int x, int y);

void LD_I(Chip8 *cpu, uint16_t addr);

void JP_V0(Chip8 *cpu, uint16_t addr);

void RND(Chip8 *cpu, int x, uint8_t byte);

void DRW(Chip8 *cpu, int x, int y, uint8_t nibble);

void SKP(Chip8 *cpu, int x);

void SKNP(Chip8 *cpu, int x);

void LD_DT(Chip8 *cpu, int x);

int LD_K(Chip8 *cpu, int x);

void LD_V_DT(Chip8 *cpu, int x);

void LD_V_ST(Chip8 *cpu, int x);

void ADD_I(Chip8 *cpu, int x);

void LD_F(Chip8 *cpu, int x);

void LD_B(Chip8 *cpu, int x);

#endif
