#ifndef CS3502_PCB_CONTROL_H
#define CS3502_PCB_CONTROL_H

#include <string>

#include "pcb.h"

struct pcb_control
{
public:
    static void create_pcb(std::string *job_section, std::string *data_section, unsigned int base_disk_address);

    static pcb *get_pcb(unsigned int ID);
    static pcb *get_highest_priority_pcb();
    static pcb *get_next_pcb();

    static void delete_pcb(unsigned int ID);
};

#endif //CS3502_PCB_CONTROL_H