//
// Created by drew on 2/17/2018.
//

#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../../pcb/pcb_control.h"
#include "../../pcb/pcb.h"
#include "../../pcb/pcb_control.cpp"
#include "../../pcb/pcb_node.h"


enum sched_algo
{
    FCFS,           //first come first serve
    PRI,            //priority
    SJF,            //shortest job first
    SRT,            //shortest remaining time
    RR              //round-robin
};

static class shortterm
{
public:
    static void dispatch_processes();
    static void receive_pcb(pcb *next_pcb);
    static void set_scheduling_algorithm(sched_algo sa);
private:
    static sched_algo scheduling_algorithm = FCFS;
    static int queue_length;                                //store the length of the queue
    static pcb_node *head_ptr;
    static pcb_node *tail_ptr;

    static pcb* remove_first_process();                     //return pointer to first process and remove from queue

    //removed when making one static class
    /*
    //used to find the correct pcb when short-term scheduling
    pcb *sched_firstComeFirstServe(pcb_node *head_ptr);
    pcb *sched_highestPriority(pcb_node *head_ptr);
    pcb *sched_shortestJob(pcb_node *head_ptr);
    pcb *sched_shortestRemaining(pcb_node *head_ptr);
    pcb *sched_roundRobin(pcb_node *head_ptr);
     *
     *
    //set to 4 for now, one for each core
    const int num_queues = 4;
    static pcb_node *ready_queue_heads[num_cores];      //store the head pointers for each queue
    */
};

#endif //CS3502_SHORT_TERM_H
