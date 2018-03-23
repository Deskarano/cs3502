#ifndef CS3502_PCB_H
#define CS3502_PCB_H

#include "pcb_types.h"
#include <ctime>

class pcb
{
public:
    pcb(unsigned int ID, unsigned int priority,
        unsigned int code_size, unsigned int input_size,
        unsigned int output_size, unsigned int temp_size,
        unsigned int base_disk_address);

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

    unsigned int get_total_size()
    { return code_size + input_size + output_size + temp_size; }

    void set_state(pcb_state state)
    { this->state = state; }

    void set_pc(unsigned int pc)
    { this->pc = pc; }

    void set_base_ram_address(unsigned int base_ram_address)
    { this->base_ram_address = base_ram_address; }

    //setting the clock variables
    void set_clock_birth()  { this->time_birth = clock(); };
    void set_clock_onram()  { this->time_onram = clock(); };
    void set_clock_oncpu()  { this->time_oncpu = clock(); };
    void set_clock_offcpu() { this->time_offcpu = clock(); };
    void set_clock_death()  { this->time_death = clock(); };

    //giving clock variables
    clock_t get_clock_birth()   { return time_birth; };
    clock_t get_clock_onram()   { return time_onram; };
    clock_t get_clock_oncpu()   { return time_oncpu; };
    clock_t get_clock_offcpu()   { return time_offcpu; };
    clock_t get_clock_death()   { return time_death; };

    //IO operations
    void new_input_operation() { num_input++; };
    void new_output_operation() { num_output++; };
    unsigned int get_num_input() { return num_input; }
    unsigned int get_num_output() { return num_output; }
    unsigned int get_num_io_operations() { return num_input + num_output; }

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

    //summary info
    unsigned int num_input = 0;
    unsigned int num_output = 0;

    //time stamps of when things happened
    clock_t time_birth;
    clock_t time_onram;
    clock_t time_oncpu;
    clock_t time_offcpu;
    clock_t time_death;
};


#endif //CS3502_PCB_H