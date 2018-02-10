#include <iostream>
#include "cpu.h"
#include "cpu_types.h"

void copy_reg(const unsigned int from[16], unsigned int to[16])
{
    for(int i = 0; i < 16; i++)
    {
        to[i] = from[i];
    }
}

void execute(instr *instruction, unsigned int reg[16], unsigned int *pc)
{
    switch(instruction->op)
    {
        case RD:
        {
            auto args = (io_args *) instruction->args;
            if(args->reg2 == 0)
            {
                reg[args->reg1] = cpu_test_ram::read_word(args->addr);
            }
            else
            {
                reg[args->reg1] = cpu_test_ram::read_word(reg[args->reg2]);
            }

            *pc += 4;
            return;
        }

        case WR:
        {
            auto args = (io_args *) instruction->args;
            if(args->reg2 == 0)
            {
                cpu_test_ram::write_word(args->addr, reg[args->reg1]);
            }
            else
            {
                cpu_test_ram::write_word(reg[args->reg2], reg[args->reg1]);
            }

            *pc += 4;
            return;
        }

        case ST:
        {
            auto args = (i_args *) instruction->args;
            cpu_test_ram::write_word(reg[args->dreg], reg[args->breg]);

            *pc += 4;
            return;
        }

        case LW:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = cpu_test_ram::read_word(reg[args->breg] + args->addr);

            *pc += 4;
            return;
        }

        case MOV:
        {
            auto args = (r_args *) instruction->args;
            reg[args->sreg1] = reg[args->sreg2];

            *pc += 4;
            return;
        }

        case ADD:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] + reg[args->sreg2];

            *pc += 4;
            return;
        }

        case SUB:
        {
            //not implemented. instruction is never used
            *pc += 4;
            return;
        }

        case MUL:
        {
            //not implemented. instruction is never used
            *pc += 4;
            return;
        }

        case DIV:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] / reg[args->sreg2];

            *pc += 4;
            return;
        }

        case AND:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] & reg[args->sreg2];

            *pc += 4;
            return;
        }

        case OR:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] | reg[args->sreg2];

            *pc += 4;
            return;
        }

        case MOVI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = args->addr;

            *pc += 4;
            return;
        }

        case ADDI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] += args->addr;

            *pc += 4;
            return;
        }

        case MULI:
        {
            //not implemented. instruction is never used
            *pc += 4;
            return;
        }

        case DIVI:
        {
            //not implemented. instruction is never used
            *pc += 4;
            return;
        }

        case LDI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = args->addr;

            *pc += 4;
            return;
        }

        case SLT:
        {
            auto args = (r_args *) instruction->args;
            if(reg[args->sreg1] < reg[args->sreg2])
            {
                reg[args->dreg] = 1;
            }
            else
            {
                reg[args->dreg] = 0;
            }

            *pc += 4;
            return;
        }

        case SLTI:
        {
            //not implemented. instruction is never used
            *pc += 4;
            return;
        }

        case HLT:
        {
            //TODO: implement this. pass PCB to execute()?
            return;
        }

        case NOP:
        {
            *pc += 4;
            return;;
        }

        case JMP:
        {
            auto args = (j_args *) instruction->args;
            *pc = args->addr;

            return;
        }

        case BEQ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] == reg[args->dreg])
            {
                *pc = args->addr;
            }
            else
            {
                *pc += 4;
            }

            return;
        }

        case BNE:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] != reg[args->dreg])
            {
                *pc = args->addr;
            }
            else
            {
                *pc += 4;
            }

            return;
        }

        case BEZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] == 0)
            {
                *pc = args->addr;
            }
            else
            {
                *pc += 4;
            }

            return;
        }

        case BNZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] != 0)
            {
                *pc = args->addr;
            }
            else
            {
                *pc += 4;
            }

            return;
        }

        case BGZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] > 0)
            {
                *pc = args->addr;
            }
            else
            {
                *pc += 4;
            }

            return;
        }

        case BLZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] < 0)
            {
                *pc = args->addr;
            }
            else
            {
                *pc += 4;
            }

            return;
        }

        case INVALID:
        {

        }
    }
}

instr *decode(unsigned int instruction)
{
    auto result = new instr;
    int type = (instruction >> 30) & 0b11;

    if(type == 0b00)
    {
        result->type = R;

        auto args = new r_args;
        args->sreg1 = (instruction >> 20) & 0b1111;
        args->sreg2 = (instruction >> 16) & 0b1111;
        args->dreg = (instruction >> 12) & 0b1111;

        result->args = args;
    }
    else if(type == 0b01)
    {
        result->type = I;

        auto args = new i_args;
        args->breg = (instruction >> 20) & 0b1111;
        args->dreg = (instruction >> 16) & 0b1111;
        args->addr = instruction & 0b1111111111111111;

        result->args = args;
    }
    else if(type == 0b10)
    {
        result->type = J;

        auto args = new j_args;
        args->addr = instruction & 0b111111111111111111111111;

        result->args = args;
    }
    else
    {
        result->type = IO;

        auto args = new io_args;
        args->reg1 = (instruction >> 20) & 0b1111;
        args->reg2 = (instruction >> 16) & 0b1111;
        args->addr = instruction & 0b1111111111111111;

        result->args = args;
    }

    int op = (instruction >> 24) & 0b00111111;

    if(op == 0x00) result->op = RD;
    else if(op == 0x01) result->op = WR;
    else if(op == 0x02) result->op = ST;
    else if(op == 0x03) result->op = LW;
    else if(op == 0x04) result->op = MOV;
    else if(op == 0x05) result->op = ADD;
    else if(op == 0x06) result->op = SUB;
    else if(op == 0x07) result->op = MUL;
    else if(op == 0x08) result->op = DIV;
    else if(op == 0x09) result->op = AND;
    else if(op == 0x0A) result->op = OR;
    else if(op == 0x0B) result->op = MOVI;
    else if(op == 0x0C) result->op = ADDI;
    else if(op == 0x0D) result->op = MULI;
    else if(op == 0x0E) result->op = DIVI;
    else if(op == 0x0F) result->op = LDI;
    else if(op == 0x10) result->op = SLT;
    else if(op == 0x11) result->op = SLTI;
    else if(op == 0x12) result->op = HLT;
    else if(op == 0x13) result->op = NOP;
    else if(op == 0x14) result->op = JMP;
    else if(op == 0x15) result->op = BEQ;
    else if(op == 0x16) result->op = BNE;
    else if(op == 0x17) result->op = BEZ;
    else if(op == 0x18) result->op = BNZ;
    else if(op == 0x19) result->op = BGZ;
    else if(op == 0x1A) result->op = BLZ;
    else result->op = INVALID;

    return result;
}

void print_registers(unsigned int reg[16])
{
    for(int i = 0; i < 16; i++)
    {
        std::cout << "R" << i << ": " << reg[i] << "\n";
    }
}

void cpu::start()
{
    instr *instruction = decode(cpu_test_ram::read_word(pc));

    while(instruction->op != HLT)
    {
        execute(instruction, reg, &pc);
        instruction = decode(cpu_test_ram::read_word(pc));
    }
}

void cpu::stop()
{

}

void cpu::set_pcb(pcb *new_pcb)
{
    this->current_pcb = new_pcb;

    this->pc = new_pcb->get_pc();
    copy_reg(current_pcb->get_reg(), this->reg);
}

pcb *cpu::get_pcb()
{
    return current_pcb;
}

void cpu::save_pcb()
{
    copy_reg(this->reg, current_pcb->get_reg());
}