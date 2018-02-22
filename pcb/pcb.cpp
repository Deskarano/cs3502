#include "pcb.h"

pcb::pcb(unsigned int ID, unsigned int priority, unsigned int code_size)
{
    this->ID = ID;
    this->priority = priority;
    this->state = NEW;

    this->pc = 0;
    for(int i = 0; i < 16; i++)
    {
        reg[i] = 0;
    }

    this->code_size = code_size;
}

void pcb::set_data_section(unsigned int input_size, unsigned int output_size, unsigned int temp_size)
{
    this->input_size = input_size;
    this->output_size = output_size;
    this->temp_size = temp_size;
}