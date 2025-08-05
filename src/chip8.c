#include "../include/chip8.h"
#include <stdlib.h>
#include <string.h>

Chip8 *createChip8(uint16_t *instr, int len) {
    Chip8 *cpu = malloc(sizeof(Chip8));
    memset(cpu->Disp, 0, sizeof(cpu->Disp));
    memset(cpu->Input, 0, sizeof(cpu->Input));
    memset(cpu->Mem, 0, sizeof(cpu->Mem));
    memset(cpu->V, 0, sizeof(cpu->V));
    cpu->I = 0x0000;
    cpu->PC = 0x200;
    cpu->SP = 0x50;
    cpu->DT = 0x00;
    cpu->ST = 0x00;
    uint8_t sprites[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10,
        0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10,
        0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0,
        0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0,
        0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
        0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80,
        0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80};
    for (int i = 0; i < sizeof(sprites); i++) {
        cpu->Mem[i] = sprites[i];
    }
    for (int i = 0, j = cpu->PC; i < len && j < sizeof(cpu->Mem); i++, j += 2) {
        uint8_t most = instr[i] >> 8;
        uint8_t least = instr[i] & 0x00FF;
        cpu->Mem[j] = most;
        cpu->Mem[j + 1] = least;
    }
    return cpu;
}

void destroyChip8(Chip8 *cpu) { free(cpu); }

void CLS(Chip8 *cpu) { memset(cpu->Disp, 0, sizeof(cpu->Disp)); }

void RET(Chip8 *cpu) {
    cpu->PC = (uint16_t)cpu->Mem[cpu->SP - 2] << 8;
    cpu->PC |= (uint16_t)cpu->Mem[cpu->SP - 1];
    cpu->SP -= 2;
}

void JP(Chip8 *cpu, uint16_t addr) { cpu->PC = addr & 0x0FFF; }

void CALL(Chip8 *cpu, uint16_t addr) {
    cpu->SP += 2;
    cpu->Mem[cpu->SP - 1] = (uint8_t)cpu->PC;
    cpu->Mem[cpu->SP - 2] = (uint8_t)(cpu->PC >> 8);
    cpu->PC = addr & 0x0FFF;
}

void SE_IMM(Chip8 *cpu, int x, uint8_t byte) {
    if (cpu->V[x] == byte) {
        cpu->PC += 2;
    }
}

void SNE_IMM(Chip8 *cpu, int x, uint8_t byte) {
    if (cpu->V[x] != byte) {
        cpu->PC += 2;
    }
}

void SE(Chip8 *cpu, int x, int y) {
    if (cpu->V[x] == cpu->V[y]) {
        cpu->PC += 2;
    }
}

void LD_IMM(Chip8 *cpu, int x, uint8_t byte) { cpu->V[x] = byte; }

void ADD_IMM(Chip8 *cpu, int x, uint8_t byte) { cpu->V[x] += byte; }

void LD(Chip8 *cpu, int x, int y) { cpu->V[x] = cpu->V[y]; }

void OR(Chip8 *cpu, int x, int y) { cpu->V[x] |= cpu->V[y]; }

void AND(Chip8 *cpu, int x, int y) { cpu->V[x] &= cpu->V[y]; }

void XOR(Chip8 *cpu, int x, int y) { cpu->V[x] ^= cpu->V[y]; }

void ADD(Chip8 *cpu, int x, int y) {
    uint16_t temp = cpu->V[x] + cpu->V[y];
    if (temp > UINT8_MAX) {
        cpu->V[15] = 1;
    } else {
        cpu->V[15] = 0;
    }
    cpu->V[x] = (uint8_t)temp;
}

void SUB(Chip8 *cpu, int x, int y) {
    if (cpu->V[x] > cpu->V[y]) {
        cpu->V[15] = 1;
    } else {
        cpu->V[15] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHR(Chip8 *cpu, int x) {
    cpu->V[15] = cpu->V[x] & 0b1;
    cpu->V[x] >>= 1;
}

void SUBN(Chip8 *cpu, int x, int y) {
    if (cpu->V[y] > cpu->V[x]) {
        cpu->V[15] = 1;
    } else {
        cpu->V[15] = 0;
    }
    cpu->V[x] = cpu->V[y] - cpu->V[x];
}

void SHL(Chip8 *cpu, int x) {
    cpu->V[15] = cpu->V[x] >> 7;
    cpu->V[x] <<= 1;
}

void SNE(Chip8 *cpu, int x, int y) {
    if (cpu->V[x] != cpu->V[y]) {
        cpu->PC += 2;
    }
}

void LD_I(Chip8 *cpu, uint16_t addr) { cpu->I = addr & 0x0FFF; }

void JP_V0(Chip8 *cpu, uint16_t addr) { cpu->PC = (addr & 0x0FFF) + cpu->V[0]; }

void RND(Chip8 *cpu, int x, uint8_t byte) {
    cpu->V[x] = (uint8_t)(rand() % 256) & byte;
}
