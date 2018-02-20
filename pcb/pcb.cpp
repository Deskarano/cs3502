#include "pcb.h"

pcb::pcb(unsigned int priority, unsigned int base_address)
{
    this->pc = 0;
    for(int &i : this->reg)
    {
        i = 0;
    }

    this->state = NEW;
    this->priority = priority;

    this->base_address = base_address;
}