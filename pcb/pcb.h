#ifndef CS3502_PCB_H
#define CS3502_PCB_H

#include "pcb_types.h"
#include "page_table/page_table.h"

#include <ctime>

class pcb
{
public:
    pcb(unsigned int ID, unsigned int priority,
        unsigned int code_size, unsigned int input_size,
        unsigned int output_size, unsigned int temp_size,
        unsigned int base_disk_address);

    unsigned int get_total_size()
    { return code_size + input_size + output_size + temp_size; }

    //setting the clock variables
    void set_clock_birth()
    { this->time_birth = clock(); };

    void set_clock_onram()
    { this->time_onram = clock(); };

    void set_clock_oncpu()
    {
        curTimesOnCpu++;
        this->times_oncpu[curTimesOnCpu] = clock();
        this->time_oncpu = clock();

    };

    void set_clock_offcpu()
    {
        this->times_offcpu[curTimesOnCpu] = clock();
        this->time_offcpu = clock();
    };

    void set_clock_death()
    { this->time_death = clock(); };

    //getting clock variables
    clock_t get_clock_birth()
    { return time_birth; };

    clock_t get_clock_onram()
    { return time_onram; };

    clock_t get_clock_oncpu()
    { return time_oncpu; };

    clock_t get_clock_offcpu()
    { return time_offcpu; };

    clock_t get_clock_death()
    { return time_death; };

    //IO operations
    void new_input_operation()
    { num_input++; };

    void new_output_operation()
    { num_output++; };

    unsigned int get_num_input()
    { return num_input; }

    unsigned int get_num_output()
    { return num_output; }

    unsigned int get_num_io_operations()
    { return num_input + num_output; }

    void start_fault_service()
    {
        time_start_service = clock();
    }

    void end_fault_service()
    {
        time_fault_service += (clock() - time_start_service);
    }

    void start_cpu_running()
    {
        time_start_cpu = clock();
    }

    void end_cpu_running()
    {
        time_cpu_running += (clock() - time_start_cpu);
    }

    void add_page() {num_pages++;}
    void add_page(unsigned int num) {num_pages += num;}
    void page_fault() {num_pageFault++;}

    clock_t get_running_time();
    unsigned int get_blocked_time();

    unsigned int get_num_pages() { return num_pages; }
    unsigned int get_num_faults() { return num_pageFault; }

    //sched-related info
    unsigned int ID;
    unsigned int priority;
    pcb_state state;

    //cpu-related info
    unsigned int pc;
    int reg[16];

    //memory-related info
    unsigned int base_disk_address;
    page_table *table;

    //size-related info
    unsigned int code_size;
    unsigned int input_size;
    unsigned int output_size;
    unsigned int temp_size;

    clock_t* times_oncpu;
    clock_t* times_offcpu;

    clock_t time_fault_service;
private:
    //summary info
    unsigned int num_input = 0;
    unsigned int num_output = 0;

    //time stamps of when things happened
    clock_t time_birth;
    clock_t time_onram;
    clock_t time_oncpu;
    clock_t time_offcpu;
    clock_t time_death;

    clock_t time_start_service;
    clock_t time_start_cpu;
    clock_t time_cpu_running;

    unsigned int curTimesOnCpu = -1;


    //page info
    unsigned int num_pages = 0;
    unsigned int num_pageFault = 0;
};


#endif //CS3502_PCB_H