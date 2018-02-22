//
// Created by drew on 2/17/2018.
//

#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../pcb/pcb_control.h"
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
    shortterm(sched_algo sa);
    pcb* get_next_process(sched_algo sa);
    static void set_scheduling_algorithm(sched_algo sa);
private:
    static sched_algo scheduling_algorithm;
};

#endif //CS3502_SHORT_TERM_H
