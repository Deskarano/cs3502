#include "logger.h"

#include "../utils/base_conversions.h"
#include "../cpu/types/instr_types.h"

#include <iostream>

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

void logger::log_cpu_fetch(unsigned int pcb_id, unsigned int pc, char *fetch)
{
    if(LOG_CPU_FETCH)
    {
        std::cout << "--cpu-status (cpu_fetch): PCB " << pcb_id
                  << " fetched instruction at 0x" << dec_to_hex(pc) << ": ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << fetch[i];
        }
        std::cout << "\n";
    }
}

void logger::log_cpu_decode(char *fetch, void *instruction)
{
    if(LOG_CPU_DECODE)
    {
        std::cout << "--cpu-status (decode): decoded instruction ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << fetch[i];
        }
        std::cout << " to ";
        print_instr((instr *) instruction);
    }
}

void logger::log_cpu_execute(unsigned int pc, void *instruction, int reg[16])
{
    if(LOG_CPU_EXECUTE)
    {
        switch(((instr *) instruction)->op)
        {
            case RD:
            {
                auto args = (io_args *) ((instr *) instruction)->args;
                if(args->reg2 == 0)
                {
                    std::cout << "--cpu-status (execute RD @ 0x" << dec_to_hex(pc) << "): read val "
                              << reg[args->reg1]
                              << " from addr 0x" << dec_to_hex(args->addr)
                              << " to reg " << args->reg1 << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute RD @ 0x" << dec_to_hex(pc) << "): read val " << reg[args->reg1]
                              << " from addr in reg " << args->reg2
                              << " = 0x" << dec_to_hex(reg[args->reg2])
                              << " to reg " << args->reg1 << "\n";
                }

                break;
            }

            case WR:
            {
                auto args = (io_args *) ((instr *) instruction)->args;
                if(args->reg2 == 0)
                {
                    std::cout << "--cpu-status (execute WR @ 0x" << dec_to_hex(pc) << "): wrote val in reg "
                              << args->reg1 << " = " << reg[args->reg1]
                              << " to addr 0x" << dec_to_hex(args->addr) << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute WR @ 0x" << dec_to_hex(pc) << "): wrote val in reg "
                              << args->reg1 << " = " << reg[args->reg1]
                              << " to addr in reg " << args->reg2
                              << " = 0x" << dec_to_hex(reg[args->reg2]) << "\n";
                }

                break;
            }

            case ST:
            {
                auto args = (i_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute ST @ 0x" << dec_to_hex(pc) << "): wrote val in reg " << args->breg
                          << " = " << reg[args->breg]
                          << " to addr in reg " << args->dreg
                          << " = 0x" << dec_to_hex(reg[args->dreg]) << "\n";

                break;
            }

            case LW:
            {
                auto args = (i_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute LW @ 0x" << dec_to_hex(pc) << "): read " << reg[args->dreg]
                          << " from addr in reg " << args->breg
                          << " = " << reg[args->breg]
                          << " + offset " << args->addr
                          << " = 0x" << dec_to_hex(reg[args->breg] + args->addr)
                          << " to reg " << args->dreg << "\n";

                break;
            }

            case MOV:
            {
                auto args = (r_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute MOV @ 0x" << dec_to_hex(pc) << "): moved reg" << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << "\n";

                break;
            }

            case ADD:
            {
                auto args = (r_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute ADD @ 0x" << dec_to_hex(pc) << "): added reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " <<args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";

                break;
            }

            case SUB:
            {
                //not implemented. instruction is never used
                break;
            }

            case MUL:
            {
                //not implemented. instruction is never used
                break;
            }

            case DIV:
            {
                auto args = (r_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute DIV @ 0x" << dec_to_hex(pc) << "): divided reg " << args->sreg1
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

                std::cout << "--cpu-status (execute AND @ 0x" << dec_to_hex(pc) << "): and'd reg " << args->sreg1
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

                std::cout << "--cpu-status (execute OR @ 0x" << dec_to_hex(pc) << "): or'd reg " << args->sreg1
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

                std::cout << "--cpu-status (execute MOVI @ 0x" << dec_to_hex(pc) << "): moved val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";

                break;
            }

            case ADDI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute ADDI @ 0x" << dec_to_hex(pc) << "): added val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";

                break;
            }

            case MULI:
            {
                //not implemented. instruction is never used
                break;
            }

            case DIVI:
            {
                //not implemented. instruction is never used
                break;
            }

            case LDI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute LDI @ 0x" << dec_to_hex(pc) << "): moved addr 0x"
                          << dec_to_hex(args->addr)
                          << " to reg " << args->dreg
                          << "\n";

                break;
            }

            case SLT:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                if(reg[args->sreg1] < reg[args->sreg2])
                {
                    std::cout << "--cpu_status (execute SLT @ 0x" << dec_to_hex(pc) << "): set reg " << args->dreg
                              << " to val 1 "
                              << "since reg " << args->sreg1 << " = " << reg[args->sreg1]
                              << " < reg " << args->sreg2 << " = " << reg[args->sreg2]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu_status (execute SLT @ 0x" << dec_to_hex(pc) << "): set reg " << args->dreg
                              << " to val 0 "
                              << "since reg " << args->sreg1 << " = " << reg[args->sreg1]
                              << " >= reg " << args->sreg2 << " = " << reg[args->sreg2]
                              << "\n";
                }

                break;
            }

            case SLTI:
            {
                //not implemented. instruction is never used
                break;
            }

            case HLT:
            {
                //TODO: implement this. pass PCB to execute()?
                break;
            }

            case NOP:
            {
                break;
            }

            case JMP:
            {
                auto args = (j_args *) ((instr *) instruction)->args;

                std::cout << "--cpu-status (execute JMP @ 0x" << dec_to_hex(pc) << "): jumped to addr 0x" << args->addr
                          << "\n";

                break;
            }

            case BEQ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] == reg[args->dreg])
                {
                    std::cout << "--cpu-status (execute BEQ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x"
                              << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " == reg " << args->dreg << " = " << reg[args->dreg]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute BEQ @ 0x" << dec_to_hex(pc) << "): did not branch\n";
                }

                break;
            }

            case BNE:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] != reg[args->dreg])
                {
                    std::cout << "--cpu-status (execute BNE @ 0x" << dec_to_hex(pc) << "): branched to addr 0x"
                              << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " != reg " << args->dreg << " = " << reg[args->dreg]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute BNE @ 0x" << dec_to_hex(pc) << "): did not branch\n";
                }

                break;
            }

            case BEZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] == 0)
                {
                    std::cout << "--cpu-status (execute BEZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x"
                              << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " == 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute BEZ @ 0x" << dec_to_hex(pc) << "): did not branch\n";
                }

                break;
            }

            case BNZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] != 0)
                {
                    std::cout << "--cpu-status (execute BNZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x"
                              << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " != 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute BNZ @ 0x" << dec_to_hex(pc) << "): did not branch\n";
                }

                break;
            }

            case BGZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] > 0)
                {
                    std::cout << "--cpu-status (execute BGZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x"
                              << args->addr
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " > 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute BGZ @ 0x" << dec_to_hex(pc) << "): did not branch\n";
                }

                break;
            }

            case BLZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] < 0)
                {
                    std::cout << "--cpu-status (execute BLZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x"
                              << args->addr
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " < 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (execute BLZ @ 0x" << dec_to_hex(pc) << "): did not branch\n";
                }

                break;
            }

            case INVALID:
            {
                std::cout << "--cpu-error (execute): invalid instruction\n";
                return;
            }
        }
    }
}

void logger::log_cpu_start(unsigned int pcb_id)
{
    if(LOG_CPU_START)
    {
        std::cout << "--cpu-status (start): executing PCB " << pcb_id << "\n";
    }
}

void logger::log_cpu_stop(unsigned int pcb_id)
{
    if(LOG_CPU_STOP)
    {
        std::cout << "--cpu-status (stop): stopping PCB " << pcb_id << "\n";
    }
}

void logger::log_cpu_set_pcb(unsigned int pcb_id)
{
    if(LOG_CPU_SET_PCB)
    {
        std::cout << "--cpu-status (set_pcb): loading PCB " << pcb_id << "\n";
    }
}

void logger::log_cpu_save_pcb(unsigned int pcb_id)
{
    if(LOG_CPU_SAVE_PCB)
    {
        std::cout << "--cpu-status (save_pcb): saving PCB " << pcb_id << "\n";
    }
}

void logger::log_cpu_control_init(unsigned int num_cores)
{
    if(LOG_CPU_CONTROL_INIT)
    {
        std::cout << "--cpu_control-status (init): initialized " << num_cores << " cores\n";
    }
}

void logger::log_cpu_control_dispatch(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_CONTROL_DISPATCH)
    {
        std::cout << "--cpu_control-status (dispatch_to_core): dispatching PCB "
                  << pcb_id << " to core " << core_id << "\n";
    }
}

void logger::log_disk_init(unsigned int num_words)
{
    if(LOG_DISK_INIT)
    {
        std::cout << "--disk-status (init): initalized disk with " << num_words << " words\n";
    }
}

void logger::log_disk_write_word(unsigned int addr, char val[8])
{
    if(LOG_DISK_WRITE_WORD)
    {
        std::cout << "--disk-status (write_word): wrote val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " to addr 0x" << dec_to_hex(addr);
    }
}

void logger::log_disk_read_word(unsigned int addr, char val[8])
{
    if(LOG_DISK_READ_WORD)
    {
        std::cout << "--disk-status (read_word): read val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " from addr 0x" << dec_to_hex(addr);
    }
}
