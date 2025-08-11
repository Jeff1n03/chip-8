#include "../include/cycle.h"
#include <stdio.h>

static inline uint8_t get_opcode(uint16_t instr) {
    return (uint8_t)(instr >> 12);
}

static inline uint16_t get_nnn(uint16_t instr) { return instr & 0x0FFF; }

static inline uint8_t get_n(uint16_t instr) { return ((uint8_t)instr) & 0x0F; }

static inline uint8_t get_x(uint16_t instr) {
    return (uint8_t)((instr & 0x0F00) >> 8);
}

static inline uint8_t get_y(uint16_t instr) {
    return (uint8_t)((instr & 0x00F0) >> 4);
}

static inline uint8_t get_kk(uint16_t instr) { return (uint8_t)instr; }

static uint16_t fetch_instr(Chip8 *cpu) {
    uint16_t instr = cpu->Mem[cpu->PC];
    instr = (instr << 8) | (uint16_t)cpu->Mem[cpu->PC + 1];
    return instr;
}

static void DNE(uint16_t instr) {
    fprintf(stderr, "Error: Undefined Instruction %u\n", instr);
}

static void opcode_0(Chip8 *cpu, uint16_t instr) {
    switch (instr) {
        case 0x00E0:
            CLS(cpu);
            break;
        case 0x00EE:
            RET(cpu);
            break;
        default:
            SYS(cpu, get_nnn(instr));
    }
}

static void opcode_5(Chip8 *cpu, uint16_t instr) {
    switch (get_n(instr)) {
        case 0x0:
            SE(cpu, get_x(instr), get_y(instr));
            break;
        default:
            DNE(instr);
    }
}

static void opcode_8(Chip8 *cpu, uint16_t instr) {
    switch (get_n(instr)) {
        case 0x0:
            LD(cpu, get_x(instr), get_y(instr));
            break;
        case 0x1:
            OR(cpu, get_x(instr), get_y(instr));
            break;
        case 0x2:
            AND(cpu, get_x(instr), get_y(instr));
            break;
        case 0x3:
            XOR(cpu, get_x(instr), get_y(instr));
            break;
        case 0x4:
            ADD(cpu, get_x(instr), get_y(instr));
            break;
        case 0x5:
            SUB(cpu, get_x(instr), get_y(instr));
            break;
        case 0x6:
            SHR(cpu, get_x(instr));
            break;
        case 0x7:
            SUBN(cpu, get_x(instr), get_y(instr));
            break;
        case 0xE:
            SHL(cpu, get_x(instr));
            break;
        default:
            DNE(instr);
    }
}

static void opcode_9(Chip8 *cpu, uint16_t instr) {
    switch (get_n(instr)) {
        case 0x0:
            SNE(cpu, get_x(instr), get_y(instr));
            break;
        default:
            DNE(instr);
    }
}

static void opcode_E(Chip8 *cpu, uint16_t instr) {
    switch (get_kk(instr)) {
        case 0x9E:
            SKP(cpu, get_x(instr));
            break;
        case 0xA1:
            SKNP(cpu, get_x(instr));
            break;
        default:
            DNE(instr);
    }
}

static void opcode_F(Chip8 *cpu, uint16_t instr) {
    // TODO
}

void cycle(Chip8 *cpu) {
    uint16_t instr = fetch_instr(cpu);
    switch (get_opcode(instr)) {
        case 0x0:
            opcode_0(cpu, instr);
            break;
        case 0x1:
            JP(cpu, get_nnn(instr));
            break;
        case 0x2:
            CALL(cpu, get_nnn(instr));
            break;
        case 0x3:
            SE_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x4:
            SNE_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x5:
            opcode_5(cpu, instr);
            break;
        case 0x6:
            LD_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x7:
            ADD_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x8:
            opcode_8(cpu, instr);
            break;
        case 0x9:
            opcode_9(cpu, instr);
            break;
        case 0xA:
            LD_I(cpu, get_nnn(instr));
            break;
        case 0xB:
            JP_V0(cpu, get_nnn(instr));
            break;
        case 0xC:
            RND(cpu, get_x(instr), get_kk(instr));
            break;
        case 0xD:
            DRW(cpu, get_x(instr), get_y(instr), get_n(instr));
            break;
        case 0xE:
            opcode_E(cpu, instr);
            break;
        case 0xF:
            opcode_F(cpu, instr);
            break;
    }
    cpu->PC += 2;
}
