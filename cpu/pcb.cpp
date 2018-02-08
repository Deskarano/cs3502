#include "pcb.h"

pcb::pcb(unsigned int priority, cpu_test_ram *ram, unsigned int base_address)
{
    this->pc = 0;
    for(int i = 0; i < 16; i++)
    {
        this->reg[i] = 0;
    }

    this->state = NEW;
    this->priority = priority;

    this->ram = ram;
    this->base_address = base_address;
}