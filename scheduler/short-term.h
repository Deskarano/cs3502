//
// Created by drew on 2/17/2018.
//

#ifndef CS3502_SHORT_TERM_H
#define CS3502_SHORT_TERM_H

#include "../pcb/pcb_control.h"
#include "../pcb/pcb.h"
#include "../pcb/pcb_control.cpp"



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
    shortterm(sched_algo sa = FCFS);
    pcb* get_next_process(int queue_index = 0);
    void add_pcb_to_ready(pcb* new_pcb, int queue_index = 0);
    void remove_pcb_from_ready(int pcb_id, int queue_index = 0);
    static void set_scheduling_algorithm(sched_algo sa);
private:
    //used to find the correct pcb when short-term scheduling
    pcb *sched_firstComeFirstServe(pcb_node *head_ptr);
    pcb *sched_highestPriority(pcb_node *head_ptr);
    pcb *sched_shortestJob(pcb_node *head_ptr);
    pcb *sched_shortestRemaining(pcb_node *head_ptr);
    pcb *sched_roundRobin(pcb_node *head_ptr);

    static sched_algo scheduling_algorithm = FCFS;

    //set to 4 for now, one for each core
    const int num_queues = 4;
    static pcb_node *ready_queue_heads[num_cores];      //store the head pointers for each queue
    static int get_queue_length(pcb_node *head_ptr);    //get the length of the queue
};

#endif //CS3502_SHORT_TERM_H
