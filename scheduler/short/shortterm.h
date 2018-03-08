//
// Created by drew on 2/17/2018.
//

#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../../pcb/pcb.h"
#include "../../pcb/pcb_node.h"


enum sched_algo
{
    FCFS,           //first come first serve
    PRI,            //priority
    SJF,            //shortest job first
    SRT,            //shortest remaining time
    RR              //round-robin
};

struct shortterm
{
public:
    static void dispatch_processes();
    static void receive_pcb(pcb *next_pcb);
    static void set_scheduling_algorithm(sched_algo sa);

private:
    static sched_algo scheduling_algorithm;
    static int queue_length;                                //store the length of the queue
    static pcb_node *head_ptr;
    static pcb_node *tail_ptr;

    static pcb* remove_first_process();                     //return pointer to first process and remove from queue
};

#endif //CS3502_SHORT_TERM_H
