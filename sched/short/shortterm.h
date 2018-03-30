#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../../pcb/pcb.h"
#include "../sched_types.h"

struct shortterm
{
public:
    static void dispatch_new_processes();

    static void receive_pcb(pcb *next_pcb);
    static void set_scheduling_algorithm(sched_algorithm sa);
};

#endif //CS3502_SHORT_TERM_H
