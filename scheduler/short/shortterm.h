#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../../pcb/pcb.h"


enum sched_algo
{
    FCFS,           //first come first serve
    PRI             //priority
};

struct shortterm
{
public:
    static void dispatch_processes();
    static void receive_pcb(pcb *next_pcb);
    static void set_scheduling_algorithm(sched_algo sa);

private:
    static pcb* remove_first_process();                     //return pointer to first process and remove from queue
};

#endif //CS3502_SHORT_TERM_H
