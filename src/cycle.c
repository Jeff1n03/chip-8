#include "../include/cycle.h"

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

static void exec_op_0(Chip8 *cpu, uint16_t instr) {
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

static bool exec_op_5(Chip8 *cpu, uint16_t instr) {
    switch (get_n(instr)) {
        case 0x0:
            SE(cpu, get_x(instr), get_y(instr));
            break;
        default:
            return false;
    }
    return true;
}

static bool exec_op_8(Chip8 *cpu, uint16_t instr) {
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
            return false;
    }
    return true;
}

static bool exec_op_9(Chip8 *cpu, uint16_t instr) {
    switch (get_n(instr)) {
        case 0x0:
            SNE(cpu, get_x(instr), get_y(instr));
            break;
        default:
            return false;
    }
    return true;
}

static bool exec_op_E(Chip8 *cpu, uint16_t instr) {
    switch (get_kk(instr)) {
        case 0x9E:
            SKP(cpu, get_x(instr));
            break;
        case 0xA1:
            SKNP(cpu, get_x(instr));
            break;
        default:
            return false;
    }
    return true;
}

static bool exec_op_F(Chip8 *cpu, uint16_t instr) {
    bool cont = true;
    switch (get_kk(instr)) {
        case 0x07:
            LD_DT(cpu, get_x(instr));
            break;
        case 0x0A:
            cont = LD_K(cpu, get_x(instr));
            break;
        case 0x15:
            LD_V_DT(cpu, get_x(instr));
            break;
        case 0x18:
            LD_V_ST(cpu, get_x(instr));
            break;
        case 0x1E:
            ADD_I(cpu, get_x(instr));
            break;
        case 0x29:
            LD_F(cpu, get_x(instr));
            break;
        case 0x33:
            LD_B(cpu, get_x(instr));
            break;
        case 0x55:
            LD_V_I(cpu, get_x(instr));
            break;
        case 0x65:
            LD_I_V(cpu, get_x(instr));
            break;
        default:
            return false;
    }
    if (!cont) {
        cpu->PC -= 2;
    }
    return true;
}

bool cycle(Chip8 *cpu) {
    bool def = true;
    uint16_t instr = fetch_instr(cpu);
    switch (get_opcode(instr)) {
        case 0x0:
            exec_op_0(cpu, instr);
            break;
        case 0x1:
            JP(cpu, get_nnn(instr));
            cpu->PC -= 2;
            break;
        case 0x2:
            CALL(cpu, get_nnn(instr));
            cpu->PC -= 2;
            break;
        case 0x3:
            SE_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x4:
            SNE_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x5:
            def = exec_op_5(cpu, instr);
            break;
        case 0x6:
            LD_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x7:
            ADD_IMM(cpu, get_x(instr), get_kk(instr));
            break;
        case 0x8:
            def = exec_op_8(cpu, instr);
            break;
        case 0x9:
            def = exec_op_9(cpu, instr);
            break;
        case 0xA:
            LD_I(cpu, get_nnn(instr));
            break;
        case 0xB:
            JP_V0(cpu, get_nnn(instr));
            cpu->PC -= 2;
            break;
        case 0xC:
            RND(cpu, get_x(instr), get_kk(instr));
            break;
        case 0xD:
            DRW(cpu, get_x(instr), get_y(instr), get_n(instr));
            break;
        case 0xE:
            def = exec_op_E(cpu, instr);
            break;
        case 0xF:
            def = exec_op_F(cpu, instr);
            break;
    }
    cpu->PC += 2;
    return def;
}
