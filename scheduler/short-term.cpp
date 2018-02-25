#include "short-term.h"
#include "../ram/ram.h"
#include "../pcb/pcb.h"
#include "../pcb/pcb_control.h"
#include <iostream>

//Othmane: this is for cout to work correctly ;) and I also added the include for iostream
using namespace std;

//CONSTRUCTOR
shortterm::shortterm(sched_algo sa = FCFS) {
    shortterm::scheduling_algorithm = sa;
    for(int i = 0; i < num_cores; i++)
    {
        ready_queue_heads[i] = nullptr;
    }
}

//set scheduling algorithm
void shortterm::set_scheduling_algorithm(sched_algo sa) {
    shortterm::scheduling_algorithm = sa;
}

//get next process from the certain READY queue
pcb* shortterm::get_next_process(int queue_index = 0) {
    if(queue_index >= num_queues || queue_index < 0) {
        cout << "Trying to pull from queue that doesn't exist... Queue #" << queue_index << " out of " << num_queues << "queues..." << endl;
        queue_index = 0;
    }

    switch(sa)
    {
        case FCFS:
            return sched_firstComeFirstServe(ready_queue_heads[queue_index]);
        case PRI:
            return sched_highestPriority(ready_queue_heads[queue_index]);
        case SJF:
            return sched_shortestJob(ready_queue_heads[queue_index]);
        case SRT: //Othmane: changed this from SRI to SRT guess it was just a typo
            return sched_shortestRemaining(ready_queue_heads[queue_index]);
        case RR:
            return sched_roundRobin(ready_queue_heads[queue_index]);
    }
}

//TODO: Could add to the queue in the correct placement taking into account the scheduling algorithm to help make it more efficient to grab the next PCB from ready
            //(could have different scheduling algorithm per queue)

//add PCB to a certain READY queue
void shortterm::add_pcb_to_ready(pcb *new_pcb, int queue_index = 0) {
    if(queue_index >= num_queues || queue_index < 0) {
        cout << "Trying to add to queue that doesn't exist... Queue #" << queue_index << " out of " << num_queues << "queues..." << endl;
        queue_index = 0;
    }

    //if the queue is empty, add as head
    if(ready_queue_heads[queue_index] == nullptr)
        ready_queue_heads[queue_index] = new pcb_node(new_pcb);
    else {
        //start at beginning of queue
        pcb_node *current = ready_queue_heads[queue_index];
        //iterate to end
        while (current->get_next() != nullptr) {
            current = current->get_next();
        }
        current->set_next(new pcb_node(new_pcb));
    }
}

//remove PCB from READY queue
void shortterm::remove_pcb_from_ready(int pcb_id, int queue_index = 0) {
    if(queue_index >= num_queues || queue_index < 0) {
        cout << "Trying to remove from queue that doesn't exist... Queue #" << queue_index << " out of " << num_queues << "queues..." << endl;
        queue_index = 0;
    }

    pcb_node *current = ready_queue_heads[queue_index];

    //if head, make the next pcb_node the head
    if(current->get_pcb()->get_ID() == pcb_id) {
        ready_queue_heads[queue_index] = current->get_next();
        return;
    }

    //iterate until you find it
    while(current->get_next() != nullptr)
    {
        //found it in next node
        if(current->get_next()->get_pcb()->get_ID() == pcb_id)
        {
            //set the current "next" to next->next
            current->set_next(current->get_next()->get_next());
            return;
        }
        current = current->get_next();
    }
}

//find first process in READY state based on queue head
pcb* shortterm::sched_firstComeFirstServe(pcb_node *head_ptr)
{
    //if head is null, return null
    if(*head_ptr == nullptr)
        return nullptr;

    //start at head
    pcb_node *current = head_ptr;

    return current -> get_pcb();

    /*if(current->get_pcb()->get_state() == READY)
    {
        return current->get_pcb();
    }

    //find the first pcb to be in the ready state
    while(current->get_next() != nullptr)
    {
        current = current->get_next();
        if(current->get_pcb()->get_state() == READY)
        {
            return current->get_pcb();
        }
    }

    if(current->get_pcb()->get_state() == READY)
    {
        return current->get_pcb();
    }

    //return null if nothing ready
    return nullptr;*/
}

//find process with highest priority in READY state based on queue head
pcb* shortterm::sched_highestPriority(pcb_node *head_ptr)
{
    //if head is null, return null
    if(*head_ptr == nullptr)
        return nullptr;

    //start at head
    pcb_node *current = head_ptr;
    pcb* result = nullptr;
    int highestprior = -1;

    //find the first pcb to be in the ready state
    while(current->get_next() != nullptr)
    {
        //set new highest priority
        if(current->get_pcb()->get_priority() > highestprior)
        {
            highestprior = current->get_pcb()->get_priority();
            result = current->get_pcb();
        }
        current = current->get_next();
    }

    //check final pcb_node
    if(current->get_pcb()->get_priority() > highestprior)
    {
        highestprior = current->get_pcb()->get_priority();
        result = current->get_pcb();
    }

    //return highest priority
    if(highestprior != -1)
        return result;

    //return null if nothing ready
    return nullptr;
}

//find process with shortest job length in READY state based on queue head
pcb* shortterm::sched_shortestJob(pcb_node *head_ptr)
{
    //if head is null, return null
    if(*head_ptr == nullptr)
        return nullptr;

    //start at head
    pcb_node *current = pcb_list_head;
    pcb* result = nullptr;
    int shortest = -1;

    //find the first pcb to be in the ready state
    while(current->get_next() != nullptr)
    {
        if(shortest == -1)
        {
            shortest = current->get_pcb()->get_code_size();
            result = current->get_pcb();
        }
            //set new shortest job
        else if(current->get_pcb()->get_code_size() < shortest)
        {
            shortest = current->get_pcb()->get_code_size();
            result = current->get_pcb();
        }
        current = current->get_next();
    }

    //check final pcb_node
    if(current->get_pcb()->get_code_size() < shortest)
    {
        shortest = current->get_pcb()->get_code_size();
        result = current->get_pcb();
    }

    //return shortest job
    if(shortest != -1)
        return result;

    //return null if nothing ready
    return nullptr;
}

//find process with shortest time remaining in READY state based on queue head
pcb* shortterm::sched_shortestRemaining(pcb_node *head_ptr)
{
    //if head is null, return null
    if(*head_ptr == nullptr)
        return nullptr;

    //start at head
    pcb_node *current = pcb_list_head;
    pcb* result = nullptr;
    int shortest = -1;

    //find the first pcb to be in the ready state
    while(current->get_next() != nullptr)
    {
        if(shortest == -1)
        {
            shortest = current->get_pcb()->get_code_size();
            result = current->get_pcb();
        }
            //set new shortest job remaining
        else if(current->get_pcb()->get_code_size() < shortest)
        {
            shortest = current->get_pcb()->get_code_size_remaining();
            result = current->get_pcb();
        }
        current = current->get_next();
    }

    //check final pcb_node
    if(current->get_pcb()->get_code_size() < shortest)
    {
        shortest = current->get_pcb()->get_code_size_remaining();
        result = current->get_pcb();
    }

    //return shortest job
    if(shortest != -1)
        return result;

    //return null if nothing ready
    return nullptr;
}

//find process in next roundrobin in READY state based on queue head
pcb* shortterm::sched_roundRobin(pcb_node *head_ptr)
{
    //if head is null, return null
    if(*head_ptr == nullptr)
        return nullptr;

    //TODO: Implement round robin scheduling if required
}

int shortterm::get_queue_length(pcb_node *head_ptr)
{
    //TODO: Could base this on code size, etc if we wanted
    pcb_node *current = head_ptr;
    if(current == nullptr)
    {
        return 0;
    }
    int result = 1;
    while(current ->get_next() != nullptr)
    {
        result++;
        current = current-> get_next();
    }
    return result;
}