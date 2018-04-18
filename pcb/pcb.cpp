#include "pcb.h"

pcb::pcb(unsigned int ID, unsigned int priority,
         unsigned int code_size, unsigned int input_size,
         unsigned int output_size, unsigned int temp_size,
         unsigned int base_disk_address)
{
    this->ID = ID;
    this->priority = priority;
    this->state = PCB_NEW;

    this->pc = 0;
    for(int i = 0; i < 16; i++)
    {
        reg[i] = 0;
    }

    this->code_size = code_size;
    this->input_size = input_size;
    this->output_size = output_size;
    this->temp_size = temp_size;

    this->times_oncpu = new clock_t[100];
    for(int i = 0; i < 100; i++)
        times_oncpu[i] = 0;
    this->times_offcpu = new clock_t[100];
    for(int i = 0; i < 100; i++)
        times_offcpu[i] = 0;

    this->base_disk_address = base_disk_address;

    this->table = new page_table(this->get_total_size(), this->base_disk_address, this->ID);
}

unsigned int pcb::get_running_time() {
    unsigned int runningTime = 0;
    for(int i = 0; i < 100; i++)
    {
        runningTime += times_offcpu[i] - times_oncpu[i];
    }
    return runningTime;
}