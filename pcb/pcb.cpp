#include "pcb.h"

#include "../storage/page_manager.h"

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

    this->base_disk_address = base_disk_address;

    this->table = new page_table(this->get_total_size(), this->base_disk_address, this->ID);
}