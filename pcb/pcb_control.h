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
    static pcb *get_highest_priority_pcb();

    //used to find the correct pcb when short-term scheduling
    static pcb *sched_firstComeFirstServe();
    static pcb *sched_highestPriority();
    static pcb *sched_shortestJob();
    static pcb *sched_shortestRemaining();
    static pcb *sched_roundRobin();

    static void delete_pcb(unsigned int ID);
};

#endif //CS3502_PCB_CONTROL_H