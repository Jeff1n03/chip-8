#include "../include/chip8.h"
#include <stdlib.h>
#include <string.h>

#define ADDR_MASK 0x0FFF
#define NIBBLE_MASK 0x0F

Chip8 *createChip8(uint16_t *instr, size_t len) {
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

void destroyChip8(Chip8 *cpu) {
    if (cpu != NULL) {
        free(cpu);
    }
}

void SYS(Chip8 *cpu, uint16_t addr) {}

void CLS(Chip8 *cpu) { memset(cpu->Disp, 0, sizeof(cpu->Disp)); }

void RET(Chip8 *cpu) {
    cpu->PC = (uint16_t)cpu->Mem[cpu->SP - 2] << 8;
    cpu->PC |= (uint16_t)cpu->Mem[cpu->SP - 1];
    cpu->SP -= 2;
}

void JP(Chip8 *cpu, uint16_t addr) { cpu->PC = addr & ADDR_MASK; }

void CALL(Chip8 *cpu, uint16_t addr) {
    cpu->SP += 2;
    cpu->Mem[cpu->SP - 1] = (uint8_t)cpu->PC;
    cpu->Mem[cpu->SP - 2] = (uint8_t)(cpu->PC >> 8);
    cpu->PC = addr & ADDR_MASK;
}

void SE_IMM(Chip8 *cpu, uint8_t x, uint8_t byte) {
    if (cpu->V[x] == byte) {
        cpu->PC += 2;
    }
}

void SNE_IMM(Chip8 *cpu, uint8_t x, uint8_t byte) {
    if (cpu->V[x] != byte) {
        cpu->PC += 2;
    }
}

void SE(Chip8 *cpu, uint8_t x, uint8_t y) {
    if (cpu->V[x] == cpu->V[y]) {
        cpu->PC += 2;
    }
}

void LD_IMM(Chip8 *cpu, uint8_t x, uint8_t byte) { cpu->V[x] = byte; }

void ADD_IMM(Chip8 *cpu, uint8_t x, uint8_t byte) { cpu->V[x] += byte; }

void LD(Chip8 *cpu, uint8_t x, uint8_t y) { cpu->V[x] = cpu->V[y]; }

void OR(Chip8 *cpu, uint8_t x, uint8_t y) { cpu->V[x] |= cpu->V[y]; }

void AND(Chip8 *cpu, uint8_t x, uint8_t y) { cpu->V[x] &= cpu->V[y]; }

void XOR(Chip8 *cpu, uint8_t x, uint8_t y) { cpu->V[x] ^= cpu->V[y]; }

void ADD(Chip8 *cpu, uint8_t x, uint8_t y) {
    uint16_t temp = cpu->V[x] + cpu->V[y];
    if (temp > UINT8_MAX) {
        cpu->V[15] = 1;
    } else {
        cpu->V[15] = 0;
    }
    cpu->V[x] = (uint8_t)temp;
}

void SUB(Chip8 *cpu, uint8_t x, uint8_t y) {
    if (cpu->V[x] > cpu->V[y]) {
        cpu->V[15] = 1;
    } else {
        cpu->V[15] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHR(Chip8 *cpu, uint8_t x) {
    cpu->V[15] = cpu->V[x] & 0b1;
    cpu->V[x] >>= 1;
}

void SUBN(Chip8 *cpu, uint8_t x, uint8_t y) {
    if (cpu->V[y] > cpu->V[x]) {
        cpu->V[15] = 1;
    } else {
        cpu->V[15] = 0;
    }
    cpu->V[x] = cpu->V[y] - cpu->V[x];
}

void SHL(Chip8 *cpu, uint8_t x) {
    cpu->V[15] = cpu->V[x] >> 7;
    cpu->V[x] <<= 1;
}

void SNE(Chip8 *cpu, uint8_t x, uint8_t y) {
    if (cpu->V[x] != cpu->V[y]) {
        cpu->PC += 2;
    }
}

void LD_I(Chip8 *cpu, uint16_t addr) { cpu->I = addr & ADDR_MASK; }

void JP_V0(Chip8 *cpu, uint16_t addr) {
    cpu->PC = (addr & ADDR_MASK) + cpu->V[0];
}

void RND(Chip8 *cpu, uint8_t x, uint8_t byte) {
    cpu->V[x] = (uint8_t)(rand() % 256) & byte;
}

void DRW(Chip8 *cpu, uint8_t x, uint8_t y, uint8_t nibble) {
    cpu->V[15] = 0;
    for (int i = 0; i < (nibble & NIBBLE_MASK); i++) {
        for (int j = 0; j < 8; j++) {
            uint8_t bit = (cpu->Mem[cpu->I + i] >> (7 - j)) & 0x01;
            cpu->Disp[(cpu->V[y] + i) % Y][(cpu->V[x] + j) % X] ^= bit;
            if (bit && !cpu->Disp[(cpu->V[y] + i) % Y][(cpu->V[x] + j) % X]) {
                cpu->V[15] = 1;
            }
        }
    }
}

void SKP(Chip8 *cpu, uint8_t x) {
    if (cpu->Input[cpu->V[x]]) {
        cpu->PC += 2;
    }
}

void SKNP(Chip8 *cpu, uint8_t x) {
    if (!cpu->Input[cpu->V[x]]) {
        cpu->PC += 2;
    }
}

void LD_DT(Chip8 *cpu, uint8_t x) { cpu->V[x] = cpu->DT; }

bool LD_K(Chip8 *cpu, uint8_t x) {
    for (int i = 0; i < 16; i++) {
        if (cpu->Input[i]) {
            cpu->V[x] = i;
            return true;
        }
    }
    return false;
}

void LD_V_DT(Chip8 *cpu, uint8_t x) { cpu->DT = cpu->V[x]; }

void LD_V_ST(Chip8 *cpu, uint8_t x) { cpu->ST = cpu->V[x]; }

void ADD_I(Chip8 *cpu, uint8_t x) { cpu->I += cpu->V[x]; }

void LD_F(Chip8 *cpu, uint8_t x) { cpu->I = 5 * cpu->V[x]; }

void LD_B(Chip8 *cpu, uint8_t x) {
    cpu->Mem[cpu->I] = (uint8_t)(cpu->V[x] / 100);
    cpu->Mem[cpu->I + 1] = (uint8_t)((cpu->V[x] % 100) / 10);
    cpu->Mem[cpu->I + 2] = cpu->V[x] % 10;
}

void LD_V_I(Chip8 *cpu, uint8_t x) {
    for (int i = 0; i <= x; i++) {
        cpu->Mem[cpu->I + i] = cpu->V[i];
    }
}

void LD_I_V(Chip8 *cpu, uint8_t x) {
    for (int i = 0; i <= x; i++) {
        cpu->V[i] = cpu->Mem[cpu->I + i];
    }
}
