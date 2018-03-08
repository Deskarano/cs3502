#ifndef CS3502_PCB_H
#define CS3502_PCB_H

#include "pcb_types.h"

class pcb
{
public:
    pcb(unsigned int ID, unsigned int priority,
        unsigned int code_size, unsigned int input_size,
        unsigned int output_size, unsigned int temp_size);

    unsigned int get_ID()
    { return ID; }

    unsigned int get_priority()
    { return priority; }

    pcb_state get_state()
    { return state; }

    unsigned int get_pc()
    { return pc; }

    int *get_reg()
    { return reg; }

    unsigned int get_base_disk_address()
    { return base_disk_address; }

    unsigned int get_base_ram_address()
    { return base_ram_address; }

    void set_ID(unsigned int ID)
    { this->ID = ID; }

    void set_priority(unsigned int priority)
    { this->priority = priority; }

    void set_state(pcb_state state)
    { this->state = state; }

    void set_pc(unsigned int pc)
    { this->pc = pc; }

    void set_base_disk_address(unsigned int base_disk_address)
    { this->base_disk_address = base_disk_address; }

    void set_base_ram_address(unsigned int base_ram_address)
    { this->base_ram_address = base_ram_address; }

    void set_code_size(unsigned int code_size)
    { this->code_size = code_size; }

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

    //size-related info
    unsigned int code_size;
    unsigned int input_size;
    unsigned int output_size;
    unsigned int temp_size;
};


#endif //CS3502_PCB_H