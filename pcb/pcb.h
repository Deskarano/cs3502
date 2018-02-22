#ifndef CS3502_PCB_H
#define CS3502_PCB_H

#include "pcb_types.h"

class pcb
{
public:
    pcb(unsigned int ID, unsigned int priority, unsigned int code_size);

    void set_data_section(unsigned int input_size, unsigned int output_size, unsigned int temp_size);

    unsigned int get_ID()
    { return ID; }

    unsigned int get_priority()
    { return priority; }

    pcb_state get_state()
    { return state; }

    unsigned int *get_pc()
    { return &pc; }

    int *get_reg()
    { return reg; }

    //return size of code
    //TODO: Doesn't count loops, I/O
    unsigned int *get_code_size()
    { return code_size; }

    //return size of code minus the current program counter
    //TODO: Doesn't count loops, I/O
    unsigned int *get_code_size_remaining()
    { return code_size - pc; }

private:
    //scheduler-related info
    unsigned int ID;
    unsigned int priority;
    pcb_state state;

    //cpu-related info
    unsigned int pc;
    int reg[16];

    //memory-related info
    unsigned int base_disk_address;
    unsigned int base_ram_address;

    unsigned int code_size;
    unsigned int input_size;
    unsigned int output_size;
    unsigned int temp_size;
};


#endif //CS3502_PCB_H