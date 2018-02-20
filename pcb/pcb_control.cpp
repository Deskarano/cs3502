#include "pcb_control.h"
#include "../utils/base_conversions.h"

static pcb *pcb_data[30];
static int pcb_count = 0;

void pcb_control::create_pcb(std::string *job_section)
{
    unsigned int ID, priority, code_size;

    unsigned long next_space = job_section->find(' ');
    job_section->erase(0, next_space);
    next_space = job_section->find(' ');

    job_section->erase(0, next_space);
    next_space = job_section->find(' ');
    ID = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    job_section->erase(0, next_space);
    next_space = job_section->find(' ');
    code_size = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    job_section->erase(0, next_space);
    next_space = job_section->find(' ');
    priority = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    pcb_data[pcb_count] = new pcb(ID, priority, code_size);
}

void pcb_control::update_pcb(unsigned int ID, std::string *data_section)
{
    unsigned int input_size, output_size, temp_size;

    unsigned long next_space = data_section->find(' ');
    data_section->erase(0, next_space);
    next_space = data_section->find(' ');

    data_section->erase(0, next_space);
    next_space = data_section->find(' ');
    input_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    data_section->erase(0, next_space);
    next_space = data_section->find(' ');
    output_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    data_section->erase(0, next_space);
    next_space = data_section->find(' ');
    temp_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    get_pcb(ID)->set_data_section(input_size, output_size, temp_size);
}


pcb *pcb_control::get_pcb(unsigned int ID)
{

}