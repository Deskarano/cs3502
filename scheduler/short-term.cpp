//
// Created by adam pellegrini on 2/1/2018.
//

#include "short-term.h"
#include "../ram/ram.h"
#include "../pcb/pcb_control.h"

//set the static
shortterm::shortterm(sched_algo sa) {
    shortterm::scheduling_algorithm = sa;
}

void shortterm::set_scheduling_algorithm(sched_algo sa) {
    shortterm::scheduling_algorithm = sa;
}

pcb* shortterm::get_next_process(sched_algo sa) {
    switch(sa)
    {
        case FCFS:
            return pcb_control::sched_firstComeFirstServe();
        case PRI:
            return pcb_control::sched_highestPriority();
        case SJF:
            return pcb_control::sched_shortestJob();
        case SRI:
            return pcb_control::sched_shortestRemaining();
        case RR:
            return pcb_control::sched_roundRobin();
    }
}