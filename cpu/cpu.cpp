#include <iostream>

#include "cpu.h"
#include "types/instr_types.h"

#include "../ram/ram.h"
#include "../utils/base_conversions.h"

void execute(instr *instruction, unsigned int &pc, int reg[16], unsigned int base)
{
    switch(instruction->op)
    {
        case RD:
        {
            auto args = (io_args *) instruction->args;
            if(args->reg2 == 0)
            {
                reg[args->reg1] = hex_to_dec(ram::read_word(base + args->addr), 8);

                std::cout << "--cpu-status (execute RD @ 0x" << dec_to_hex(pc) << "): read " << reg[args->reg1]
                          << " from addr 0x" << dec_to_hex(args->addr)
                          << " to reg " << args->reg1 << "\n";
            }
            else
            {
                reg[args->reg1] = hex_to_dec(ram::read_word(base + (unsigned) reg[args->reg2]), 8);

                std::cout << "--cpu-status (execute RD @ 0x" << dec_to_hex(pc) << "): read " << reg[args->reg1]
                          << " from addr in reg " << args->reg2
                          << " = 0x" << dec_to_hex(reg[args->reg2])
                          << " to reg " << args->reg1 << "\n";
            }

            pc += 4;
            return;
        }

        case WR:
        {
            auto args = (io_args *) instruction->args;
            if(args->reg2 == 0)
            {
                ram::write_word(base + args->addr, dec_to_hex(reg[args->reg1]));

                std::cout << "--cpu-status (execute WR @ 0x" << dec_to_hex(pc) << "): wrote " << reg[args->reg1]
                          << " to addr 0x" << dec_to_hex(args->addr) << "\n";
            }
            else
            {
                ram::write_word(base + (unsigned) reg[args->reg2], dec_to_hex(reg[args->reg1]));

                std::cout << "--cpu-status (execute WR @ 0x" << dec_to_hex(pc) << "): wrote " << reg[args->reg1]
                          << " to addr in reg " << args->reg2
                          << " = 0x" << dec_to_hex(reg[args->reg2]) << "\n";
            }

            pc += 4;
            return;
        }

        case ST:
        {
            auto args = (i_args *) instruction->args;
            ram::write_word(base + (unsigned) reg[args->dreg], dec_to_hex(reg[args->breg]));

            std::cout << "--cpu-status (execute ST @ 0x" << dec_to_hex(pc) << "): wrote value in reg " << args->breg
                      << " = " << reg[args->breg]
                      << " to addr in " << args->dreg
                      << " = 0x" << dec_to_hex(reg[args->dreg]) << "\n";

            pc += 4;
            return;
        }

        case LW:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = hex_to_dec(ram::read_word(base + reg[args->breg] + args->addr), 8);

            std::cout << "--cpu-status (execute LW @ 0x" << dec_to_hex(pc) << "): read " << reg[args->dreg]
                      << " from addr in reg " << args->breg
                      << " = " << reg[args->breg]
                      << " + offset " << args->addr
                      << " = 0x" << dec_to_hex(reg[args->breg]) + args->addr
                      << " to reg " << args->dreg << "\n";

            pc += 4;
            return;
        }

        case MOV:
        {
            auto args = (r_args *) instruction->args;
            reg[args->sreg1] = reg[args->sreg2];

            std::cout << "--cpu-status (execute MOV @ 0x" << dec_to_hex(pc) << "): moved " << reg[args->sreg1]
                      << " from reg " << args->sreg2
                      << " to reg " << args->sreg1
                    << " = " << reg[args->dreg]
                      << "\n";

            pc += 4;
            return;
        }

        case ADD:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] + reg[args->sreg2];

            std::cout << "--cpu-status (execute ADD @ 0x" << dec_to_hex(pc) << "): added " << reg[args->sreg1]
                      << " from reg " << args->sreg1
                      << " and " << reg[args->sreg2]
                      << " from reg " << args->sreg2
                      << " to reg " << args->dreg
                      << " = " << reg[args->dreg]
                      << "\n";

            pc += 4;
            return;
        }

        case SUB:
        {
            //not implemented. instruction is never used
            pc += 4;
            return;
        }

        case MUL:
        {
            //not implemented. instruction is never used
            pc += 4;
            return;
        }

        case DIV:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] / reg[args->sreg2];

            std::cout << "--cpu-status (execute DIV @ 0x" << dec_to_hex(pc) << "): divided " << reg[args->sreg1]
                      << " from reg " << args->sreg1
                      << " and " << reg[args->sreg2]
                      << " from reg " << args->sreg2
                      << " to reg " << args->dreg
                      << " = " << reg[args->dreg]
                      << "\n";

            pc += 4;
            return;
        }

        case AND:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] & reg[args->sreg2];

            std::cout << "--cpu-status (execute AND @ 0x" << dec_to_hex(pc) << "): and'd " << reg[args->sreg1]
                      << " from reg " << args->sreg1
                      << " and " << reg[args->sreg2]
                      << " from reg " << args->sreg2
                      << " to reg " << args->dreg
                      << " = " << reg[args->dreg]
                      << "\n";

            pc += 4;
            return;
        }

        case OR:
        {
            auto args = (r_args *) instruction->args;
            reg[args->dreg] = reg[args->sreg1] | reg[args->sreg2];

            std::cout << "--cpu-status (execute OR @ 0x" << dec_to_hex(pc) << "): or'd " << reg[args->sreg1]
                      << " from reg " << args->sreg1
                      << " and " << reg[args->sreg2]
                      << " from reg " << args->sreg2
                      << " to reg " << args->dreg
                      << " = " << reg[args->dreg]
                      << "\n";

            pc += 4;
            return;
        }

        case MOVI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = args->addr;

            std::cout << "--cpu-status (execute MOVI @ 0x" << dec_to_hex(pc) << "): moved val " << args->addr
                      << " to reg " << args->dreg
                      << "\n";

            pc += 4;
            return;
        }

        case ADDI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] += args->addr;

            std::cout << "--cpu-status (execute ADDI @ 0x" << dec_to_hex(pc) << "): added val " << args->addr
                      << " to reg " << args->dreg
                      << " = " << reg[args->dreg]
                      << "\n";

            pc += 4;
            return;
        }

        case MULI:
        {
            //not implemented. instruction is never used
            pc += 4;
            return;
        }

        case DIVI:
        {
            //not implemented. instruction is never used
            pc += 4;
            return;
        }

        case LDI:
        {
            auto args = (i_args *) instruction->args;
            reg[args->dreg] = args->addr;

            std::cout << "--cpu-status (execute LDI @ 0x" << dec_to_hex(pc) << "): moved addr 0x" << dec_to_hex(args->addr)
                      << " to reg " << args->dreg
                      << "\n";

            pc += 4;
            return;
        }

        case SLT:
        {
            auto args = (r_args *) instruction->args;
            if(reg[args->sreg1] < reg[args->sreg2])
            {
                reg[args->dreg] = 1;

                std::cout << "--cpu_status (execute SLT @ 0x" << dec_to_hex(pc) << "): set reg " << args->dreg
                          << " to val 1 "
                          << "since reg " << args->sreg1 << " = " << reg[args->sreg1]
                          << " < reg " << args->sreg2 << " = " << reg[args->sreg2]
                          << "\n";
            }
            else
            {
                reg[args->dreg] = 0;

                std::cout << "--cpu_status (execute SLT @ 0x" << dec_to_hex(pc) << "): set reg " << args->dreg
                          << " to val 0 "
                          << "since reg " << args->sreg1 << " = " << reg[args->sreg1]
                          << " >= reg " << args->sreg2 << " = " << reg[args->sreg2]
                          << "\n";
            }

            pc += 4;
            return;
        }

        case SLTI:
        {
            //not implemented. instruction is never used
            pc += 4;
            return;
        }

        case HLT:
        {
            //TODO: implement this. pass PCB to execute()?
            return;
        }

        case NOP:
        {
            pc += 4;
            return;;
        }

        case JMP:
        {
            auto args = (j_args *) instruction->args;
            pc = args->addr;

            std::cout << "--cpu-status (execute JMP @ 0x" << dec_to_hex(pc) << "): jumped to addr 0x" << args->addr
                      << "\n";

            return;
        }

        case BEQ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] == reg[args->dreg])
            {
                pc = args->addr;

                std::cout << "--cpu-status (execute BEQ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x" << dec_to_hex(args->addr)
                          << " since reg " << args->breg << " = " << reg[args->breg]
                          << " == reg " << args->dreg << " = " << reg[args->dreg]
                          << "\n";
            }
            else
            {
                pc += 4;
            }

            return;
        }

        case BNE:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] != reg[args->dreg])
            {
                pc = args->addr;

                std::cout << "--cpu-status (execute BNE @ 0x" << dec_to_hex(pc) << "): branched to addr 0x" << dec_to_hex(args->addr)
                          << " since reg " << args->breg << " = " << reg[args->breg]
                          << " != reg " << args->dreg << " = " << reg[args->dreg]
                          << "\n";
            }
            else
            {
                pc += 4;
            }

            return;
        }

        case BEZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] == 0)
            {
                pc = args->addr;

                std::cout << "--cpu-status (execute BEZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x" << dec_to_hex(args->addr)
                          << " since reg " << args->breg << " = " << reg[args->breg]
                          << " == 0"
                          << "\n";
            }
            else
            {
                pc += 4;
            }

            return;
        }

        case BNZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] != 0)
            {
                pc = args->addr;

                std::cout << "--cpu-status (execute BNZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x" << dec_to_hex(args->addr)
                          << " since reg " << args->breg << " = " << reg[args->breg]
                          << " != 0"
                          << "\n";
            }
            else
            {
                pc += 4;
            }

            return;
        }

        case BGZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] > 0)
            {
                pc = args->addr;

                std::cout << "--cpu-status (execute BGZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x" << args->addr
                          << " since reg " << args->breg << " = " << reg[args->breg]
                          << " > 0"
                          << "\n";
            }
            else
            {
                pc += 4;
            }

            return;
        }

        case BLZ:
        {
            auto args = (i_args *) instruction->args;
            if(reg[args->breg] < 0)
            {
                pc = args->addr;

                std::cout << "--cpu-status (execute BLZ @ 0x" << dec_to_hex(pc) << "): branched to addr 0x" << args->addr
                          << " since reg " << args->breg << " = " << reg[args->breg]
                          << " < 0"
                          << "\n";
            }
            else
            {
                pc += 4;
            }

            return;
        }

        case INVALID:
        {
            std::cout << "--cpu-error (execute): invalid instruction\n";
            return;
        }
    }
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
    else result->op = INVALID;

    /*
    std::cout << "--cpu-status (decode): decoded instruction ";
    for(int i = 0; i < 8; i++)
    {
        std::cout << instruction[i];
    }
    std::cout << " to ";
    print_instr(result);
     */

    return result;
}

void cpu::cpu_main_thread()
{
    while(state == CPU_FULL)
    {
        char *fetch = ram::read_word(current_pcb->get_base_ram_address() + pc);

        /*
        std::cout << "--cpu-status (cpu_main_thread): PCB " << current_pcb->get_ID()
                  << " fetched instruction at 0x" << dec_to_hex(pc) << ": ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << fetch[i];
        }
        std::cout << "\n";
         */

        instr *instruction = decode(fetch);

        if(instruction->op == HLT)
        {
            current_pcb->set_state(PCB_DONE);

            stop();
            return;
        }
        else
        {
            execute(instruction, pc, reg, current_pcb->get_base_ram_address());
        }
    }
}

void cpu::start()
{
    std::cout << "--cpu-status (start): executing PCB " << current_pcb->get_ID() << "\n";
    state = CPU_FULL;
    cpu_thread = std::thread(cpu_main_thread, this);
    cpu_thread.join();
}

void cpu::stop()
{
    std::cout << "--cpu-status (stop): stopping PCB " << current_pcb->get_ID() << "\n";

    state = CPU_IDLE;
    //cpu_thread.join();

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
    std::cout << "--cpu-status (set_pcb): loading PCB " << new_pcb->get_ID() << "\n";
    this->current_pcb = new_pcb;

    this->pc = new_pcb->get_pc();
    copy_reg(current_pcb->get_reg(), this->reg);
}

void cpu::save_pcb()
{
    copy_reg(this->reg, current_pcb->get_reg());
    current_pcb->set_pc(this->pc);
}