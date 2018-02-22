#ifndef CS3502_PCB_CONTROL_H
#define CS3502_PCB_CONTROL_H

#include <string>

#include "pcb.h"

struct pcb_control
{
public:
    static unsigned int create_pcb(std::string *job_section);
    static void update_pcb(unsigned int ID, std::string *data_section);

    static pcb *get_pcb(unsigned int ID);
    static void delete_pcb(unsigned int ID);

    static pcb *get_next_pcb();
    static pcb *get_highest_priority_pcb();
};

#endif //CS3502_PCB_CONTROL_H