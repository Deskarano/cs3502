#include <iostream>

#include "longterm.h"
#include "../short/shortterm.h"

#include "../../pcb/pcb_node.h"

#include "../../ram/ram.h"

#include "../../utils/base_conversions.h"
#include "../../utils/memcpy.h"

#include "../../log/log_status.h"

static sched_algorithm algorithm;
static unsigned int num_total_pcbs = 0;
static unsigned int num_loaded_pcbs = 0;

static pcb_node *pcb_list_head = nullptr;

void add_pcb_to_list(pcb *pcb)
{
    if(pcb_list_head == nullptr)
    {
        pcb_list_head = new pcb_node(pcb);
    }
    else
    {
        pcb_node *current = pcb_list_head;
        while(current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new pcb_node(pcb);
    }
}

void longterm::create_pcb(unsigned int ID, unsigned int priority, unsigned int code_size,
                          unsigned int input_size, unsigned int output_size, unsigned int temp_size,
                          unsigned int base_disk_address)
{
    auto *new_pcb = new pcb(ID, priority, code_size, input_size, output_size, temp_size, base_disk_address);
    log_status::log_pcb_size(ID, code_size, input_size, output_size, temp_size, new_pcb->get_total_size());
    add_pcb_to_list(new_pcb);
    new_pcb->set_clock_birth(); //set the time of birth
    num_total_pcbs++;

    log_status::log_long_create_pcb(ID, base_disk_address);
    log_status::log_pcb_priority(ID, priority);
}

void longterm::writeback_finished_pcb(pcb *pcb)
{
    log_status::log_long_writeback_pcb(pcb->ID);

    ram_to_disk(pcb->base_ram_address, pcb->base_disk_address, pcb->get_total_size());
    pcb->set_clock_death(); //set time of death
    log_status::log_pcb_times(pcb->ID, pcb->get_clock_birth(), pcb->get_clock_oncpu(), pcb->get_clock_death());
    log_status::log_pcb_summary(pcb->ID, pcb->get_clock_birth(), pcb->get_clock_onram(), pcb->get_clock_oncpu(), pcb->get_clock_offcpu(), pcb->get_clock_oncpu() - pcb->get_clock_birth(), pcb->get_clock_offcpu() - pcb->get_clock_oncpu());
    log_status::log_pcb_io_operations(pcb->ID, pcb->get_num_input(), pcb->get_num_output(), pcb->get_num_io_operations());
    //end of pcb lifecycle
    delete pcb;

    num_loaded_pcbs--;
    num_total_pcbs--;
}

pcb *get_next_pcb()
{
    if(pcb_list_head != nullptr)
    {
        pcb_node *del = pcb_list_head;
        pcb *ret = del->value;

        pcb_list_head = del->next;

        delete del;
        return ret;
    }
    else
    {
        std::cout << "--pcb_control-error (get_next_pcb): PCB list is empty\n";
        return nullptr;
    }
}

pcb *get_highest_priority_pcb()
{
    if(pcb_list_head != nullptr)
    {
        pcb_node *current = pcb_list_head;
        pcb_node *del = current;

        //find the right pcb
        while(current->next != nullptr)
        {
            current = current->next;
            if(del->value->priority > current->value->priority)
            {
                del = current;
            }
        }

        if(del->value->priority > current->value->priority)
        {
            del = current;
        }

        pcb *ret = del->value;

        //and delete it
        if(del == pcb_list_head)
        {
            pcb_list_head = del->next;
        }
        else
        {
            current = pcb_list_head;
            while(current->next != del)
            {
                current = current->next;
            }

            current->next = del->next;
        }

        delete del;
        return ret;
    }
    else
    {
        std::cout << "--pcb_control-error (get_highest_priority_pcb): PCB list is empty\n";
        return nullptr;
    }
}

pcb *get_shortest_pcb()
{
    if(pcb_list_head != nullptr)
    {
        pcb_node *current = pcb_list_head;
        pcb_node *del = current;

        //find the right pcb
        while(current->next != nullptr)
        {
            current = current->next;
            if(del->value->get_total_size() > current->value->get_total_size())
            {
                del = current;
            }
        }

        if(del->value->get_total_size() > current->value->get_total_size())
        {
            del = current;
        }

        pcb *ret = del->value;

        //and delete it
        if(del == pcb_list_head)
        {
            pcb_list_head = del->next;
        }
        else
        {
            current = pcb_list_head;
            while(current->next != del)
            {
                current = current->next;
            }

            current->next = del->next;
        }

        delete del;
        return ret;
    }
    else
    {
        std::cout << "--pcb_control-error (get_shortest_pcb): PCB list is empty\n";
        return nullptr;
    }
}

void longterm::schedule()
{
    unsigned int base_addr = 0;
    pcb *current = nullptr;

    do
    {
        switch(algorithm)
        {
            case SCHED_FCFS:
            {
                current = get_next_pcb();
                log_status::log_long_schedule_fcfs(current->ID, base_addr);
                break;
            }

            case SCHED_PRI:
            {
                current = get_highest_priority_pcb();
                log_status::log_long_schedule_priority(current->ID, current->priority, base_addr);
                break;
            }

            case SCHED_SJF:
            {
                current = get_shortest_pcb();
                log_status::log_long_schedule_sjf(current->ID, current->get_total_size(), base_addr);
                break;
            }
        }

        current->base_ram_address = base_addr;

        disk_to_ram(current->base_disk_address,
                    base_addr,
                    current->get_total_size());

        shortterm::receive_pcb(current);
        num_loaded_pcbs++;

        base_addr += 4 * current->get_total_size();
    }
    while((num_total_pcbs - num_loaded_pcbs) > 0 && base_addr / 4 + current->get_total_size() < ram::size());
}

void longterm::set_scheduling_algorithm(sched_algorithm sa)
{
    algorithm = sa;
}

int longterm::pcbs_left_ram()
{
    return num_loaded_pcbs;
}

int longterm::pcbs_left_total()
{
    return num_total_pcbs;
}