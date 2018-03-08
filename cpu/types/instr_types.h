#ifndef CS3502_INSTR_TYPES_H
#define CS3502_INSTR_TYPES_H

#include "../../utils/base_conversions.h"

#include <iostream>

enum instr_op
{
    RD, WR, ST, LW,
    MOV, ADD, SUB, MUL, DIV, AND, OR,
    MOVI, ADDI, MULI, DIVI, LDI,
    SLT, SLTI,
    HLT, NOP, JMP,
    BEQ, BNE, BEZ, BNZ, BGZ, BLZ,
    INVALID
};

struct r_args
{
    unsigned int sreg1;
    unsigned int sreg2;
    unsigned int dreg;
};

struct i_args
{
    unsigned int breg;
    unsigned int dreg;
    unsigned int addr;
};

struct j_args
{
    unsigned int addr;
};

struct io_args
{
    unsigned int reg1;
    unsigned int reg2;
    unsigned int addr;
};

struct instr
{
    instr_op op;
    void *args;
};


#endif //CS3502_INSTR_TYPES_H
