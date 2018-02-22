//
// Created by drew on 2/17/2018.
//

#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../pcb/pcb.h"

enum sched_algo
{
    FCFS,           //first come first serve
    PRI,            //priority
    SJF,            //shortest job first
    SRT,            //shortest remaining time
    RR              //round-robin
};

class shortterm
{
public:
    void add_process(pcb* process);         //used to add a new process to queue
    void remove_process(pcb* process);

private:
    pcb* get_next_process(sched_algo sa);
};

#endif //CS3502_SHORT_TERM_H
