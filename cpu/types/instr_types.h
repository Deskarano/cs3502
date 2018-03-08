#ifndef CS3502_INSTR_TYPES_H
#define CS3502_INSTR_TYPES_H

#include "../../utils/base_conversions.h"

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

void print_instr(instr *instruction)
{
    switch(instruction->op)
    {
        case RD:
        {
            auto args = (io_args *) instruction->args;
            std::cout << "RD reg1=" << args->reg1
                      << " reg2=" << args->reg2
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case WR:
        {
            auto args = (io_args *) instruction->args;
            std::cout << "WR reg1=" << args->reg1
                     << " reg2=" << args->reg2
                     << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case ST:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "ST breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case LW:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "LW breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case MOV:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "MOV sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case ADD:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "ADD sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case SUB:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "SUB sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case MUL:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "MUL sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case DIV:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "DIV sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case AND:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "AND sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case OR:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "OR sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case MOVI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "MOVI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case ADDI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "ADDI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case MULI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "MULI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case DIVI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "DIVI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case LDI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "LDI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case SLT:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "SLT sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case SLTI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "SLTI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case HLT:
        {
            std::cout << "HLT\n";
            break;
        }

        case NOP:
        {
            std::cout << "NOP\n";
            break;
        }

        case JMP:
        {
            auto args = (j_args *) instruction->args;
            std::cout << "JMP addr=0x" << dec_to_hex(args->addr) << "\n";
        }

        case BEQ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BEQ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BNE:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BNE breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BEZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BEZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BNZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BNZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BGZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BGZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BLZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BLZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case INVALID:
        {
            std::cout << "INVALID\n";
            break;
        }
    }
}
#endif //CS3502_INSTR_TYPES_H
