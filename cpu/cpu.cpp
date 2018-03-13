#include "cpu.h"

#include "types/instr_types.h"
#include "../ram/ram.h"
#include "../utils/base_conversions.h"

#include "../log/log_status.h"
#include "../log/log_error.h"

void execute(instr *instruction, unsigned int &pc, int reg[16], unsigned int base)
{
    unsigned int new_pc = pc + 4;
    
    switch(instruction->op)
    {
        case RD:
        {
            auto args = (io_args *) instruction->args;
            if(args->reg2 == 0)
            {
                reg[args->reg1] = hex_to_dec(ram::read_word(base + args->addr), 8);
            }
            else
            {
                reg[args->reg1] = hex_to_dec(ram::read_word(base + (unsigned) reg[args->reg2]), 8);
            }

            break;
        }

        case WR:
        {
            auto args = (io_args *) instruction->args;
            if(args->reg2 == 0)
            {
                ram::write_word(base + args->addr, dec_to_hex(reg[args->reg1]));
            }
            else
            {
                ram::write_word(base + (unsigned) reg[args->reg2], dec_to_hex(reg[args->reg1]));
            }

            break;
        }

        case ST:
        {
            auto args = (i_args *) instruction->args;
            ram::write_word(base + (unsigned) reg[args->dreg], dec_to_hex(reg[args->breg]));

            break;
        }

        case LW:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = hex_to_dec(ram::read_word(base + reg[args->breg] + args->addr), 8);
            
            break;
        }

        case MOV:
        {
            auto args = (r_args *) instruction->args;
            reg[args->sreg1] = reg[args->sreg2];

            break;
        }

        case ADD:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] + reg[args->sreg2];

            break;
        }

        case SUB:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] - reg[args->sreg2];

            break;
        }

        case MUL:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] * reg[args->sreg2];

            break;
        }

        case DIV:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] / reg[args->sreg2];
            
            break;
        }

        case AND:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] & reg[args->sreg2];

            break;
        }

        case OR:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] | reg[args->sreg2];

            break;
        }

        case MOVI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = args->addr;

            break;
        }

        case ADDI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] += args->addr;

            break;
        }

        case MULI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] *= args->addr;

            break;
        }

        case DIVI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] /= args->addr;

            break;
        }

        case LDI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = args->addr;

            break;
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

            break;
        }

        case SLTI:
        {
            //TODO
            break;
        }

        case HLT:
        {
            break;
        }

        case NOP:
        {
            break;
        }

        case JMP:
        {
            auto args = (j_args *) instruction->args;
            new_pc = args->addr;

            break;
        }

        case BEQ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] == reg[args->dreg])
            {
                new_pc = args->addr;
            }

            break;
        }

        case BNE:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] != reg[args->dreg])
            {
                new_pc = args->addr;
            }

            break;
        }

        case BEZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] == 0)
            {
                new_pc = args->addr;
            }

            break;
        }

        case BNZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] != 0)
            {
                new_pc = args->addr;
            }

            break;
        }

        case BGZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] > 0)
            {
                new_pc = args->addr;
            }

            break;
        }

        case BLZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] < 0)
            {
                new_pc = args->addr;
            }

            break;
        }
    }

    log_status::log_cpu_execute(pc, instruction, reg);
    pc = new_pc;

    delete instruction->args;
    delete instruction;
}

instr *decode(char instruction[8])
{
    auto result = new instr;
    int type = hex_to_dec(instruction, 1) >> 2;

    if(type == 0b00)
    {
        auto args = new r_args;
        args->sreg1 = hex_to_dec(instruction + 2, 1);
        args->sreg2 = hex_to_dec(instruction + 3, 1);
        args->dreg = hex_to_dec(instruction + 4, 1);

        result->args = args;
    }
    else if(type == 0b01)
    {
        auto args = new i_args;
        args->breg = hex_to_dec(instruction + 2, 1);
        args->dreg = hex_to_dec(instruction + 3, 1);
        args->addr = hex_to_dec(instruction + 4, 4);

        result->args = args;
    }
    else if(type == 0b10)
    {
        auto args = new j_args;
        args->addr = hex_to_dec(instruction + 2, 6);

        result->args = args;
    }
    else
    {
        auto args = new io_args;
        args->reg1 = hex_to_dec(instruction + 2, 1);
        args->reg2 = hex_to_dec(instruction + 3, 1);
        args->addr = hex_to_dec(instruction + 4, 4);

        result->args = args;
    }

    int op = hex_to_dec(instruction, 2) & 0b00111111;

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
    else
    {
        log_error::cpu_decode_invalid(instruction);
    }

    log_status::log_cpu_decode(instruction, result);

    return result;
}

void cpu::cpu_main_thread()
{
    while(state == CPU_BUSY)
    {
        log_status::log_cpu_fetch(current_pcb->get_ID(), pc);

        char *fetch = ram::read_word(current_pcb->get_base_ram_address() + pc);
        instr *instruction = decode(fetch);

        if(instruction->op == HLT)
        {
            log_status::log_cpu_stop(current_pcb->get_ID());

            state = CPU_DONE;
            current_pcb->set_state(PCB_DONE);

            save_pcb();
        }
        else
        {
            execute(instruction, pc, reg, current_pcb->get_base_ram_address());
        }
    }
}

cpu::cpu()
{
    state = CPU_EMPTY;

    pc = 0;
    for(int i = 0; i < 16; i++)
    {
        reg[i] = 0;
    }
}

void cpu::start()
{
    log_status::log_cpu_start(current_pcb->get_ID());

    state = CPU_BUSY;
    current_pcb->set_state(PCB_RUNNING);

    cpu_thread = std::thread(cpu_main_thread, this);
}

void cpu::stop()
{
    log_status::log_cpu_stop(current_pcb->get_ID());

    state = CPU_IDLE;
    current_pcb->set_state(PCB_READY);

    cpu_thread.join();

    save_pcb();
}

void copy_reg(const int from[16], int to[16])
{
    for(int i = 0; i < 16; i++)
    {
        to[i] = from[i];
    }
}

void cpu::set_pcb(pcb *new_pcb)
{
    log_status::log_cpu_set_pcb(new_pcb->get_ID());

    this->current_pcb = new_pcb;
    this->pc = new_pcb->get_pc();
    copy_reg(current_pcb->get_reg(), this->reg);
}

void cpu::save_pcb()
{
    log_status::log_cpu_save_pcb(current_pcb->get_ID());

    current_pcb->set_pc(this->pc);
    copy_reg(this->reg, current_pcb->get_reg());
}