#include <iostream>
#include "shortterm.h"

#include "../../cpu/cpu_control.h"
#include "../../pcb/pcb_node.h"
#include "../../log/log_status.h"

static sched_algorithm algorithm;
static pcb_node *pcb_list_head;

void shortterm::set_scheduling_algorithm(sched_algorithm sa)
{
    algorithm = sa;
}

void push_to_ready_queue(pcb *pcb)
{
    if(pcb_list_head == nullptr)
    {
        pcb_list_head = new pcb_node(pcb);
    }
    else
    {
        pcb_node *current = pcb_list_head;

        switch(algorithm)
        {
            case SCHED_FCFS:
            {
                while(current->next != nullptr)
                {
                    current = current->next;
                }
            }

            case SCHED_PRI:
            {
                if(current->value->priority > pcb->priority)
                {
                    pcb_node *temp = current;
                    pcb_list_head = new pcb_node(pcb);
                    pcb_list_head->next = temp;

                    return;
                }

                while(current->next != nullptr)
                {
                    if(current->value->priority <= pcb->priority &&
                       current->next->value->priority >= pcb->priority)
                    {
                        break;
                    }

                    current = current->next;
                }

                break;
            }

            case SCHED_SJF:
            {
                if(current->value->get_total_size() > pcb->get_total_size())
                {
                    pcb_node *temp = current;
                    pcb_list_head = new pcb_node(pcb);
                    pcb_list_head->next = temp;

                    return;
                }

                while(current->next != nullptr)
                {
                    if(current->value->get_total_size() < pcb->get_total_size() &&
                       current->next->value->get_total_size() >= pcb->get_total_size())
                    {
                        break;
                    }

                    current = current->next;
                }

                break;
            }
        }

        pcb_node *temp = current->next;
        current->next = new pcb_node(pcb);
        current->next->next = temp;
    }
}

void shortterm::receive_pcb(pcb *next_pcb)
{
    log_status::log_short_receive_pcb(next_pcb->ID);
    next_pcb->set_clock_onram();
    push_to_ready_queue(next_pcb);
}

pcb *pop_from_ready_queue()
{
    if(pcb_list_head != nullptr)
    {
        pcb *ret = pcb_list_head->value;
        pcb_node *del = pcb_list_head;

        pcb_list_head = pcb_list_head->next;

        delete del;
        return ret;
    }
    else
    {
        return nullptr;
    }
}

void shortterm::dispatch_new_processes()
{
    unsigned int num_free_cores = cpu_control::num_idle_cores();

    for(unsigned int i = 0; i < num_free_cores; i++)
    {
        pcb *next_process = pop_from_ready_queue();
        if(next_process != nullptr)
        {
            cpu_control::dispatch(next_process);
        }
    }
}