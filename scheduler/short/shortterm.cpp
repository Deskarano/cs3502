#include "shortterm.h"
#include "../../ram/ram.h"
#include "../../pcb/pcb.h"
#include "../../pcb/pcb_control.h"
#include "../../pcb/pcb_node.h"
#include "../../cpu/cpu_control.h"
#include "../../cpu/cpu.h"
#include "../long/longterm.h"
#include <iostream>



using namespace std;

//set scheduling algorithm
void shortterm::set_scheduling_algorithm(sched_algo sa) {
    shortterm::scheduling_algorithm = sa;
}

//take a PCB and add it to appropriate point in linked list
void shortterm::receive_pcb(pcb *next_pcb) {
    //if list is empty
    if(queue_length == 0)
    {
        queue_length = 1;
        head_ptr = new pcb_node(next_pcb);
        tail_ptr = head_ptr;
        return;
    }

    //error if head is null
    if(head_ptr == nullptr)
    {
        cout << "--shortterm-error (receive_pcb): head_ptr is null and queue_length is " << queue_length << "\n";
    }

    //added one to queue
    queue_length++;

    pcb_node *newnode = new pcb_node(next_pcb);
    switch(shortterm::scheduling_algorithm)
    {
        //add to end
        case FCFS:
            tail_ptr->next = newnode;
            tail_ptr = tail_ptr->next;
            break;
        //add at first spot where *current is greater
        case PRI:
            //if less than head
            if(newnode->pcb->get_priority() < head_ptr->pcb->get_priority())
            {
                newnode->next = head_ptr;
                head_ptr = newnode;
                return;
            }
            pcb_node *current = head_ptr->next;
            pcb_node *previous = head_ptr;
            while(current != nullptr)
            {
                //if less, add here in linked list
                if(newnode->pcb->get_priority() < current->pcb->get_priority())
                {
                    newnode->next = current;
                    previous->next = newnode;
                    return;
                }
                current = current->next;
                previous = previous->next;
            }

            //if greater than tail
            tail_ptr->next = newnode;
            tail_ptr = newnode;
            break;
        //only implement in next phase if needed or extra time
        /*
        case SJF:
            break;
        case SRT:
            break;
        case RR:
            break;*/
    }
}

//look at CPU cores and give it a process if open
void shortterm::dispatch_processes() {
    cpu_state current_state;
    unsigned int num_cores = cpu_control::get_num_cores();

    //error, no cores
    if(num_cores == 0)
    {
        cout << "--shortterm-error (dispatch_processes): Trying to dispatch to zero cores\n";
        return;
    }

    //iterate through cores
    for(int i = 0; i < num_cores; i++)
    {
        current_state = cpu_control::get_core_state(i);
        switch(current_state)
        {
            //CPU needs to get back to work
            case CPU_IDLE:
                pcb *next_process = remove_first_process();
                cpu_control::dispatch_to_core(i, remove_first_process());
                break;
            //TODO: when working with preemption
            case CPU_FULL:
                break;
        }
    }
}

//return the pointer to first pcb and remove from queue
pcb* shortterm::remove_first_process()
{
    //decrease queue length
    queue_length--;

    //return header point pcb and delete head pointer
    pcb* ret = head_ptr->pcb;
    pcb_node *del = head_ptr;

    //if only one in list
    if(head_ptr == tail_ptr)
    {
        queue_length = 0;
        head_ptr = nullptr;
        tail_ptr = nullptr;
        delete del;
        return ret;
    }
    //more than one in list, move head pointer due to removing
    else
        head_ptr = head_ptr->next;

    //delete head and return the pointer to pcb
    delete del;
    return ret;
}



//ALL REMOVED WHEN MADE INTO STATIC CLASS
/*
 *
 *
 *
//CONSTRUCTOR
shortterm::shortterm(sched_algo sa = FCFS) {
    shortterm::scheduling_algorithm = sa;
    for(int i = 0; i < num_cores; i++)
    {
        ready_queue_heads[i] = nullptr;
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
        case SRT:
            return sched_shortestRemaining(ready_queue_heads[queue_index]);
        case RR:
            return sched_roundRobin(ready_queue_heads[queue_index]);
    }
}

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
 */