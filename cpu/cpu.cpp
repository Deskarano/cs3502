#include "cpu.h"

void copy_reg(const unsigned int from[16], unsigned int to[16])
{
    for(int i = 0; i < 16; i++)
    {
        to[i] = from[i];
    }
}

void execute(unsigned int instruction, unsigned int reg[16], unsigned int *pc)
{
    int op = (instruction >> 24) & 0b00111111;

    if(op == 0x00) //RD
    {
        int reg1 = (instruction >> 20) & 0b1111;
        int reg2 = (instruction >> 16) & 0b1111;
        int addr = instruction & 0b00000000000000001111111111111111;

        if(reg2 == 0){}
    }

    if(op == 0x01) //WR
    {

    }

    if(op == 0x02) //ST
    {

    }

    if(op == 0x03) //LW
    {

    }

    if(op == 0x04) //MOV
    {
        int sreg1 = (instruction >> 20) & 0b1111;
        int sreg2 = (instruction >> 16) & 0b1111;

        reg[sreg1] = reg[sreg2];
        return;
    }

    if(op == 0x05) //ADD
    {
        int sreg1 = (instruction >> 20) & 0b1111;
        int sreg2 = (instruction >> 16) & 0b1111;
        int dreg = (instruction >> 12) & 0b1111;

        reg[dreg] = reg[sreg1] + reg[sreg2];
        return;
    }

    if(op == 0x06) //SUB
    {
        //not implemented. instruction is never used
        return;
    }

    if(op == 0x07) //MUL
    {
        //not implemented. instruction is never used
        return;
    }

    if(op == 0x08) //DIV
    {
        int sreg1 = (instruction >> 20) & 0b1111;
        int sreg2 = (instruction >> 16) & 0b1111;
        int dreg = (instruction >> 12) & 0b1111;

        reg[dreg] = reg[sreg1] / reg[sreg2];
        return;
    }

    if(op == 0x09) //AND
    {
        int sreg1 = (instruction >> 20) & 0b1111;
        int sreg2 = (instruction >> 16) & 0b1111;
        int dreg = (instruction >> 12) & 0b1111;

        reg[dreg] = reg[sreg1] & reg[sreg2];
        return;
    }

    if(op == 0x0A) //OR
    {
        int sreg1 = (instruction >> 20) & 0b1111;
        int sreg2 = (instruction >> 16) & 0b1111;
        int dreg = (instruction >> 12) & 0b1111;

        reg[dreg] = reg[sreg1] | reg[sreg2];
        return;
    }

    if(op == 0x0B) //MOVI
    {
        int dreg = (instruction >> 16) & 0b1111;
        unsigned int val = (instruction) & 0b00000000000000001111111111111111;

        reg[dreg] = val;
        return;
    }

    if(op == 0x0C) //ADDI
    {
        int dreg = (instruction >> 16) & 0b1111;
        unsigned int val = (instruction) & 0b00000000000000001111111111111111;

        reg[dreg] += val;
        return;
    }

    if(op == 0x0D) //MULI
    {
        //not implemented. instruction is never used
        return;
    }

    if(op == 0x0E) //DIVI
    {
        //not implemented. instruction is never used
        return;
    }

    if(op == 0x0F) //LDI
    {
        int dreg = (instruction >> 16) & 0b1111;
        unsigned int val = (instruction) & 0b00000000000000001111111111111111;

        reg[dreg] = val;
        return;
    }

    if(op == 0x10) //SLT
    {
        int sreg1 = (instruction >> 20) & 0b1111;
        int sreg2 = (instruction >> 16) & 0b1111;
        int dreg = (instruction >> 12) & 0b1111;

        if(reg[sreg1] < reg[sreg2]) reg[dreg] = 1;
        else reg[dreg] = 0;
        return;
    }

    if(op == 0x11) //SLTI
    {
        //not implemented. instruction is never used
        return;
    }

    if(op == 0x12) //HLT
    {
        //TODO: implement this. pass PCB to execute()?
        return;
    }

    if(op == 0x13) //NOP
    {
        return;
    }

    if(op == 0x14) //JMP
    {
        unsigned int target_addr = instruction & 0b00000000111111111111111111111111;
        *pc = target_addr;

        return;
    }

    if(op == 0x15) //BEQ
    {
        int breg = (instruction >> 20) & 0b1111;
        int dreg = (instruction >> 16) & 0b1111;
        unsigned int addr = (instruction) & 0b00000000000000001111111111111111;

        if(reg[breg] == reg[dreg]) *pc = addr;
    }

    if(op == 0x16) //BNE
    {
        int breg = (instruction >> 20) & 0b1111;
        int dreg = (instruction >> 16) & 0b1111;
        unsigned int addr = (instruction) & 0b00000000000000001111111111111111;

        if(reg[breg] != reg[dreg]) *pc = addr;
    }

    if(op == 0x17) //BEZ
    {
        int breg = (instruction >> 20) & 0b1111;
        unsigned int addr = (instruction) & 0b00000000000000001111111111111111;

        if(reg[breg] == 0) *pc = addr;
    }

    if(op == 0x18) //BNZ
    {
        int breg = (instruction >> 20) & 0b1111;
        unsigned int addr = (instruction) & 0b00000000000000001111111111111111;

        if(reg[breg] != 0) *pc = addr;
    }

    if(op == 0x19) //BGZ
    {
        int breg = (instruction >> 20) & 0b1111;
        unsigned int addr = (instruction) & 0b00000000000000001111111111111111;

        if(reg[breg] > 0) *pc = addr;
    }

    if(op == 0x1A) //BLZ
    {
        int breg = (instruction >> 20) & 0b1111;
        unsigned int addr = (instruction) & 0b00000000000000001111111111111111;

        if(reg[breg] < 0) *pc = addr;
    }
}

void cpu::start()
{

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