#include "log_status.h"

#include "../utils/base_conversions.h"
#include "../utils/lock.h"

#include "../cpu/types/instr_types.h"

#include "../storage/ram/ram.h"
#include "../storage/disk/disk.h"
#include "../pcb/page_table/page_table.h"

#include <iostream>

static lock *print_lock = new lock;

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
    }
}

void log_status::log_cpu_control_init(unsigned int num_cores)
{
    if(LOG_CPU_CONTROL_INIT)
    {
        print_lock->wait();

        std::cout << "--cpu_control-status (init): initialized " << num_cores << " cores\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_control_dispatch(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_CONTROL_DISPATCH)
    {
        print_lock->wait();

        std::cout << "--cpu_control-status (dispatch_to_core): dispatching PCB "
                  << pcb_id << " to core " << core_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_control_clear(unsigned int core_id)
{
    if(LOG_CPU_CONTROL_CLEAR)
    {
        print_lock->wait();

        std::cout << "--cpu_control-status (clear_finished_cores): clearing finished core "
                  << core_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_fetch(unsigned int core_id, unsigned int pc)
{
    if(LOG_CPU_FETCH)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (cpu_fetch): "
                  << " fetching instruction at 0x" << dec_to_hex(pc)
                  << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_decode(unsigned int core_id, char *fetch, void *instruction)
{
    if(LOG_CPU_DECODE)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (decode): decoded instruction ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << fetch[i];
        }
        std::cout << " to ";
        print_instr((instr *) instruction);

        print_lock->notify();
    }
}

void log_status::log_cpu_execute(unsigned int core_id, void *instruction, int reg[16])
{
    if(LOG_CPU_EXECUTE)
    {
        print_lock->wait();

        switch(((instr *) instruction)->op)
        {
            case RD:
            {
                auto args = (io_args *) ((instr *) instruction)->args;
                if(args->reg2 == 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute RD):"
                              << " read from addr 0x" << dec_to_hex(args->addr)
                              << " to reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute RD):"
                              << " read from addr in reg " << args->reg2
                              << " = 0x" << dec_to_hex(reg[args->reg2])
                              << " to reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << "\n";
                }
                break;
            }

            case WR:
            {
                auto args = (io_args *) ((instr *) instruction)->args;
                if(args->reg2 == 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute WR):"
                              << " wrote val in reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << " to addr 0x" << dec_to_hex(args->addr)
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute WR):"
                              << " wrote val in reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << " to addr in reg " << args->reg2
                              << " = 0x" << dec_to_hex(reg[args->reg2])
                              << "\n";
                }
                break;
            }

            case ST:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute ST):"
                          << " wrote val in reg " << args->breg
                          << " = " << reg[args->breg]
                          << " to addr in reg " << args->dreg
                          << " = 0x" << dec_to_hex(reg[args->dreg]) << "\n";
                break;
            }

            case LW:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute LW):"
                          << " read from addr in reg " << args->breg
                          << " = " << reg[args->breg]
                          << " + offset " << args->addr
                          << " = 0x" << dec_to_hex(reg[args->breg] + args->addr)
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MOV:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MOV):"
                          << " moved reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << "\n";
                break;
            }

            case ADD:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute ADD):"
                          << " added reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case SUB:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute SUB):"
                          << " subtracted reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MUL:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MUL):"
                          << " multiplied reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case DIV:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute DIV):"
                          << " divided reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case AND:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute AND):"
                          << " and'd reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case OR:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute OR):"
                          << " or'd reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MOVI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MOVI):"
                          << " moved val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case ADDI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute ADDI):"
                          << " added val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MULI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MULI):"
                          << " multiplied val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case DIVI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute DIVI):"
                          << " divided val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case LDI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute LDI):"
                          << " moved addr 0x" << dec_to_hex(args->addr)
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";

                break;
            }

            case SLT:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                if(reg[args->sreg1] < reg[args->sreg2])
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute SLT):"
                              << " set reg " << args->dreg << " to val 1"
                              << " since reg " << args->sreg1 << " = " << reg[args->sreg1]
                              << " < reg " << args->sreg2 << " = " << reg[args->sreg2]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute SLT):"
                              << " set reg " << args->dreg << " to val 0"
                              << " since reg " << args->sreg1 << " = " << reg[args->sreg1]
                              << " >= reg " << args->sreg2 << " = " << reg[args->sreg2]
                              << "\n";
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
                std::cout << "--cpu-status (" << core_id << ") (execute HLT):"
                          << " reached program end\n";
                break;
            }

            case NOP:
            {
                std::cout << "--cpu-status (" << core_id << ") (execute NOP):"
                          << " doing nothing\n";
                break;
            }

            case JMP:
            {
                auto args = (j_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute JMP):"
                          << "jumped to addr 0x" << args->addr
                          << "\n";
                break;
            }

            case BEQ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] == reg[args->dreg])
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEQ):"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " == reg " << args->dreg << " = " << reg[args->dreg]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEQ):"
                              << " did not branch\n";
                }

                break;
            }

            case BNE:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] != reg[args->dreg])
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNE):"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " != reg " << args->dreg << " = " << reg[args->dreg]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNE):"
                              << " did not branch\n";
                }

                break;
            }

            case BEZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] == 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEZ):"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " == 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEZ):"
                              << " did not branch\n";
                }

                break;
            }

            case BNZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] != 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNZ):"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " != 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNZ):"
                              << " did not branch\n";
                }

                break;
            }

            case BGZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] > 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BGZ):"
                              << " branched to addr 0x" << args->addr
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " > 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BGZ):"
                              << " did not branch\n";
                }

                break;
            }

            case BLZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] < 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BLZ):"
                              << " branched to addr 0x" << args->addr
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " < 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BLZ):"
                              << " did not branch\n";
                }

                break;
            }
        }

        print_lock->notify();
    }
}

void log_status::log_cpu_start(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_START)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (start): executing PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_stop(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_STOP)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (stop): stopping PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_set_pcb(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_SET_PCB)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (set_pcb): loading PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_save_pcb(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_SAVE_PCB)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (save_pcb): saving PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_disk_init(unsigned int num_words)
{
    if(LOG_DISK_INIT)
    {
        print_lock->wait();

        std::cout << "--disk-status (init): initalized disk with " << num_words << " words\n";

        print_lock->notify();
    }
}

void log_status::log_disk_write_word(unsigned int addr, const char val[8])
{
    if(LOG_DISK_WRITE_WORD)
    {
        print_lock->wait();

        std::cout << "--disk-status (write_word): wrote val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " to addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_disk_read_word(unsigned int addr, char val[8])
{
    if(LOG_DISK_READ_WORD)
    {
        print_lock->wait();

        std::cout << "--disk-status (read_word): read val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " from addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_ram_init(unsigned int num_words)
{
    if(LOG_RAM_INIT)
    {
        print_lock->wait();

        std::cout << "--ram-status (init): initalized ram with " << num_words << " words\n";

        print_lock->notify();
    }
}

void log_status::log_ram_write_word(unsigned int addr, char val[8])
{
    if(LOG_RAM_WRITE_WORD)
    {
        print_lock->wait();

        std::cout << "--ram-status (write_word): wrote val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " to addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_ram_read_word(unsigned int addr, char val[8])
{
    if(LOG_RAM_READ_WORD)
    {
        print_lock->wait();

        std::cout << "--ram-status (read_word): read val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " from addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_pager_init()
{
    if(LOG_PAGER_INIT)
    {
        print_lock->wait();

        std::cout << "--pager-status (init): initialized page manager\n";

        print_lock->notify();
    }
}

void log_status::log_pager_lookup(unsigned int pcb_id, unsigned int addr, unsigned int result)
{
    if(LOG_PAGER_LOOKUP)
    {
        print_lock->wait();

        std::cout << "--pager-status (lookup): table lookup in PCB " << pcb_id
                  << " for logical addr 0x" << dec_to_hex(addr)
                  << " resulted in";

        if(result == PAGE_FAULT)
        {
            std::cout << " PAGE FAULT\n";
        }
        else
        {
            std::cout << " physical addr 0x" << dec_to_hex(result) << "\n";
        }

        print_lock->notify();
    }
}

void log_status::log_pager_init_frames(unsigned int pcb_id)
{
    if(LOG_PAGER_INIT_FRAMES)
    {
        print_lock->wait();

        std::cout << "--pager-status (init_frames): loading initial frames for PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_pager_receive_pcb(unsigned int pcb_id, unsigned int addr)
{
    if(LOG_PAGER_RECEIVE_PCB)
    {
        print_lock->wait();

        std::cout << "--pager-status (receive_pcb): received PCB " << pcb_id
                  << " with faulting addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_pager_load_update(unsigned int pcb_id, unsigned int log_addr, unsigned int phys_addr)
{
    if(LOG_PAGER_LOAD_UPDATE)
    {
        print_lock->wait();

        std::cout << "--pager_status (load_and_update):"
                  << " added entry in PCB " << pcb_id
                  << " for logical address 0x" << dec_to_hex(log_addr)
                  << ": 0x" << dec_to_hex(phys_addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_pager_release_frame(unsigned int pcb_id, unsigned int log_addr, unsigned int phys_addr)
{
    if(LOG_PAGER_RELEASE_FRAME)
    {
        print_lock->wait();

        std::cout << "--pager-status (release_frame):"
                  << " removed entry in PCB " << pcb_id
                  << " for logical address 0x" << dec_to_hex(log_addr)
                  << ": 0x" << dec_to_hex(phys_addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_pager_release_all_frames(unsigned int pcb_id)
{
    if(LOG_PAGER_RELEASE_ALL_FRAMES)
    {
        print_lock->wait();

        std::cout << "--pager-status (release_all_frames):"
                  << " releasing all frames from PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_short_receive_pcb(unsigned int pcb_id)
{
    if(LOG_SHORT_RECEIVE_PCB)
    {
        print_lock->wait();

        std::cout << "--shortterm-status (receive_pcb): received PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_create_pcb(unsigned int pcb_id, unsigned int base_disk_address)
{
    if(LOG_LONG_CREATE_PCB)
    {
        print_lock->wait();

        std::cout << "--longterm-status (create_pcb): created PCB " << pcb_id
                  << " at disk address 0x" << dec_to_hex(base_disk_address)
                  << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_schedule_fcfs(unsigned int pcb_id)
{
    if(LOG_LONG_SCHEDULE)
    {
        print_lock->wait();

        std::cout << "--longterm-status (schedule FCFS): loading PCB "
                  << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_schedule_priority(unsigned int pcb_id, unsigned int priority)
{
    if(LOG_LONG_SCHEDULE)
    {
        print_lock->wait();

        std::cout << "--longterm-status (schedule PRI): loading PCB "
                  << pcb_id << " (priority " << priority << ")\n";

        print_lock->notify();
    }
}

void log_status::log_long_schedule_sjf(unsigned int pcb_id, unsigned int total_size)
{
    if(LOG_LONG_SCHEDULE)
    {
        print_lock->wait();

        std::cout << "--longterm-status (schedule SJF): loading PCB "
                  << pcb_id << " (size " << total_size << ")\n";

        print_lock->notify();
    }
}

void log_status::log_long_writeback_pcb(unsigned int pcb_id)
{
    if(LOG_LONG_WRITEBACK_PCB)
    {
        print_lock->wait();

        std::cout << "--longterm-status (writeback_pcb): writing pcb "
                  << pcb_id << " back to disk\n";

        print_lock->notify();
    }
}

void log_status::log_pcb_size(unsigned int pcb_id, unsigned int size_code, unsigned int size_input, unsigned int size_output,
                              unsigned int size_temp, unsigned int size_total)
{
    if(LOG_PCB_SIZES)
    {
        print_lock->wait();

        std::cout << pcb_id << "," << size_code << "," << size_input << "," << size_output << "," << size_temp << ","
                  << size_total << "\n";

        print_lock->notify();
    }
}

void log_status::log_pcb_times(unsigned int pcb_id, clock_t time_toRAM, clock_t time_toCPU, clock_t time_offCPU)
{
    if(LOG_PCB_TIMES)
    {
        print_lock->wait();

        std::cout << "--pcb-times (pcb id: " << pcb_id << "):\t RAM - " << time_toRAM << "\t CPU - " << time_toCPU
                  << "\t COMPLETE - " << time_offCPU << "\n";

        print_lock->notify();
    }
}

void log_status::log_pcb_summary(unsigned int pcb_id, clock_t time_birth, clock_t time_ram, clock_t time_cpu,
                                 clock_t time_death, clock_t elapsed_waiting, clock_t elapsed_running)
{
    if(LOG_PCB_SUMMARY)
    {
        print_lock->wait();

        std::cout << pcb_id << "," << time_birth << "," << time_ram << "," << time_cpu << "," << time_death << ","
                  << elapsed_waiting << "," << elapsed_running << "\n";

        print_lock->notify();
    }
}

void log_status::log_pcb_priority(unsigned int pcb_id, unsigned int priority)
{
    if(LOG_PCB_PRIORITIES)
    {
        print_lock->wait();

        std::cout << pcb_id << "," << priority << "\n";

        print_lock->notify();
    }
}

void log_status::log_pcb_io_operations(unsigned int pcb_id, unsigned int num_input, unsigned int num_output,
                                       unsigned int num_total)
{
    if(LOG_PCB_IO)
    {
        print_lock->wait();

        std::cout << pcb_id << "," << num_input << "," << num_output << "," << num_total << "\n";

        print_lock->notify();
    }
}

void log_status::dump_ram()
{
    print_lock->wait();

    for(int i = 0; i < ram::size(); i += 4)
    {
        std::cout << "0x" << dec_to_hex(4 * i) << ": ";
        for(int j = 0; j < 4; j++)
        {
            char *val = ram::read_word(4 * (i + j));
            for(int k = 0; k < 8; k++)
            {
                std::cout << val[k];
            }
            std::cout << " ";
        }
    }

    print_lock->notify();
}

void log_status::dump_disk()
{
    print_lock->wait();

    for(int i = 0; i < disk::size(); i += 4)
    {
        //std::cout << "0x" << dec_to_hex(4 * i) << ": ";
        for(int j = 0; j < 4; j++)
        {
            char *val = disk::read_word(4 * (i + j));
            for(int k = 0; k < 8; k++)
            {
                std::cout << val[k];
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }

    print_lock->notify();
}