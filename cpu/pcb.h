#ifndef CS3502_PCB_H
#define CS3502_PCB_H

#include "test/cpu_test_ram.h"

enum pcb_state
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    DONE
};

class pcb
{
public:
    pcb(unsigned int priority, unsigned int base_address);

    unsigned int get_pc()
    {
        return pc;
    }

    unsigned int *get_reg()
    {
        return reg;
    }

private:
    //cpu-related info
    unsigned int pc;
    unsigned int reg[16];

    //scheduler-related info
    pcb_state state;
    unsigned int priority;

    //memory-related info
    unsigned int base_address;
};


#endif //CS3502_PCB_H