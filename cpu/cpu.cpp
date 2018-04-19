#include "cpu.h"

#include "../storage/page_manager.h"
#include "../utils/base_conversions.h"

#include "../log/log_status.h"
#include "../log/log_error.h"

#include <thread>
#include <iostream>

static unsigned int next_id = 0;

cpu::cpu()
{
    this->core_id = next_id++;
    state = CPU_IDLE;

    pc = 0;
    for(int i = 0; i < 16; i++)
    {
        reg[i] = 0;
    }
}

void cpu::start()
{
    log_status::log_cpu_start(core_id, current_pcb->ID);

    state = CPU_BUSY;
    page_fault = false;
    current_pcb->state = PCB_RUNNING;

    new std::thread(&cpu::cpu_main_thread, this);
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
    log_status::log_cpu_set_pcb(core_id, new_pcb->ID);

    this->current_pcb = new_pcb;
    this->pc = new_pcb->pc;
    copy_reg(current_pcb->reg, this->reg);

    page_fault = false;
}

void cpu::save_pcb()
{
    log_status::log_cpu_save_pcb(core_id, current_pcb->ID);

    current_pcb->pc = this->pc;
    copy_reg(this->reg, current_pcb->reg);
}

void cpu::cpu_main_thread()
{
    current_pcb->set_clock_oncpu();
    current_pcb->start_cpu_running();
    while(!page_fault)
    {
        log_status::log_cpu_fetch(core_id, pc);

        char *fetch = read_or_page_fault(pc);
        if(page_fault)
        {
            state = CPU_IDLE;
            current_pcb->set_clock_offcpu();
            current_pcb->end_cpu_running();
            return;
        }

        instr *instruction = decode(fetch);
        log_status::log_cpu_decode(core_id, fetch, instruction);

        delete fetch;

        if(instruction->op == HLT)
        {
            log_status::log_cpu_execute(core_id, instruction, reg);
            log_status::log_cpu_stop(core_id, current_pcb->ID);

            state = CPU_DONE;
            current_pcb->state = PCB_DONE;
            current_pcb->set_clock_offcpu();
            current_pcb->end_cpu_running();
            return;
        }
        else
        {
            execute(instruction);
            if(!page_fault)
            {
                log_status::log_cpu_execute(core_id, instruction, reg);
            }
            else
            {
                state = CPU_IDLE;
            }
        }

        delete instruction->args;
        delete instruction;
    }
    current_pcb->set_clock_offcpu();
    current_pcb->end_cpu_running();
}

instr *cpu::decode(char instruction[8])
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

    return result;
}

void cpu::handle_page_fault(unsigned int addr)
{
    save_pcb();

    current_pcb->state = PCB_WAITING;
    current_pcb->add_page();
    current_pcb->page_fault();
    page_fault = true;

    page_manager::receive_pcb(current_pcb, addr);
}

char *cpu::read_or_page_fault(unsigned int addr)
{
    char *read = new char[8];

    if(page_manager::read_word(current_pcb->table, addr, read) == PAGE_FAULT)
    {
        handle_page_fault(addr);

        delete read;
        return nullptr;
    }
    else
    {
        return read;
    }
}

void cpu::write_or_page_fault(unsigned int addr, int val)
{
    if(page_manager::write_word(current_pcb->table, addr, dec_to_hex(val)) == PAGE_FAULT)
    {
        handle_page_fault(addr);
    }
}

void cpu::execute(instr *instruction)
{
    unsigned int new_pc = pc + 4;

    switch(instruction->op)
    {
        case RD:
        {
            auto args = (io_args *) instruction->args;
            char *read;

            if(args->reg2 == 0)
            {
                read = read_or_page_fault(args->addr);
            }
            else
            {
                read = read_or_page_fault((unsigned) reg[args->reg2]);
            }

            if(page_fault)
            {
                return;
            }
            else
            {
                reg[args->reg1] = hex_to_dec(read, 8);
                delete read;
            }

            current_pcb->new_input_operation();
            break;
        }

        case WR:
        {
            auto args = (io_args *) instruction->args;

            if(args->reg2 == 0)
            {
                write_or_page_fault(args->addr, reg[args->reg1]);
            }
            else
            {
                write_or_page_fault((unsigned) reg[args->reg2], reg[args->reg1]);
            }

            if(page_fault) return;

            current_pcb->new_output_operation();
            break;
        }

        case ST:
        {
            auto args = (i_args *) instruction->args;

            write_or_page_fault((unsigned) reg[args->dreg], reg[args->breg]);
            if(page_fault) return;

            current_pcb->new_output_operation();
            break;
        }

        case LW:
        {
            auto args = (i_args *) instruction->args;

            char *read;

            read = read_or_page_fault(reg[args->breg] + args->addr);
            if(page_fault)
            {
                return;
            }
            else
            {
                reg[args->dreg] = hex_to_dec(read, 8);
                delete read;
            }

            current_pcb->new_input_operation();
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
            auto args = (i_args *) instruction->args;

            if(reg[args->breg < args->addr])
            {
                reg[args->dreg] = 1;
            }
            else
            {
                reg[args->dreg] = 0;
            }

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

    pc = new_pc;
}