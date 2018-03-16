#include <iostream>

#include "longterm.h"
#include "../short/shortterm.h"

#include "../../pcb/pcb_node.h"

#include "../../ram/ram.h"

#include "../../utils/base_conversions.h"
#include "../../utils/memcpy.h"

#include "../../log/log_status.h"

unsigned int longterm::num_total_pcbs = 0;
unsigned int longterm::num_loaded_pcbs = 0;

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

void longterm::create_pcb(std::string *job_section, std::string *data_section, unsigned int base_disk_address)
{
    //analyze job_section
    unsigned int ID, priority, code_size;

    unsigned int next_space = (int) job_section->find(' ');
    job_section->erase(0, next_space + 1);
    next_space = (int) job_section->find(' ');

    job_section->erase(0, next_space + 1);
    next_space = (int) job_section->find(' ');
    ID = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    job_section->erase(0, next_space + 1);
    next_space = (int) job_section->find(' ');
    code_size = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    job_section->erase(0, next_space + 1);
    next_space = (int) job_section->find(' ');
    priority = hex_to_dec(job_section->substr(0, next_space).c_str(), (unsigned int) job_section->size() - 1);

    //analyze data_section
    unsigned int input_size, output_size, temp_size;

    next_space = (int) data_section->find(' ');
    data_section->erase(0, next_space + 1);
    next_space = (int) data_section->find(' ');

    data_section->erase(0, next_space + 1);
    next_space = (int) data_section->find(' ');
    input_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    data_section->erase(0, next_space + 1);
    next_space = (int) data_section->find(' ');
    output_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    data_section->erase(0, next_space + 1);
    next_space = (int) data_section->find(' ');
    temp_size = hex_to_dec(data_section->substr(0, next_space).c_str(), (unsigned int) data_section->size() - 1);

    auto *new_pcb = new pcb(ID, priority, code_size, input_size, output_size, temp_size, base_disk_address);
    add_pcb_to_list(new_pcb);
    new_pcb->set_clock_birth(); //set the time of birth
    num_total_pcbs++;

    log_status::log_long_create_pcb(ID, base_disk_address);
}

void longterm::writeback_finished_pcb(pcb *pcb)
{
    log_status::log_long_writeback_pcb(pcb->get_ID());

    ram_to_disk(pcb->get_base_ram_address(), pcb->get_base_disk_address(), pcb->get_total_size());
    pcb->set_clock_death(); //set time of death
    log_status::log_pcb_times(pcb->get_ID(), pcb->get_clock_birth(), pcb->get_clock_oncpu(), pcb->get_clock_death());
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
            if(del->value->get_priority() > current->value->get_priority())
            {
                del = current;
            }
        }

        if(del->value->get_priority() > current->value->get_priority())
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

void longterm::schedule_fcfs()
{
    unsigned int base_addr = 0;
    pcb *current;

    do
    {
        current = get_next_pcb();

        current->set_base_ram_address(base_addr);
        log_status::log_long_schedule_fcfs(current->get_ID(), base_addr);

        disk_to_ram(current->get_base_disk_address(),
                    base_addr,
                    current->get_total_size());

        shortterm::receive_pcb(current);
        num_loaded_pcbs++;

        base_addr += 4 * current->get_total_size();
    }
    while((num_total_pcbs - num_loaded_pcbs) > 0 && base_addr / 4 + current->get_total_size() < ram::size());
}

void longterm::schedule_priority()
{
    unsigned int base_addr = 0;
    pcb *current;

    do
    {
        current = get_highest_priority_pcb();

        current->set_base_ram_address(base_addr);
        log_status::log_long_schedule_priority(current->get_ID(), current->get_priority(), base_addr);

        disk_to_ram(current->get_base_disk_address(),
                    base_addr,
                    current->get_total_size());

        shortterm::receive_pcb(current);
        num_loaded_pcbs++;

        base_addr += 4 * current->get_total_size();
    }
    while((num_total_pcbs - num_loaded_pcbs) > 0 && base_addr / 4 + current->get_total_size() < ram::size());
}

int longterm::pcbs_left_ram()
{
    return num_loaded_pcbs;
}

int longterm::pcbs_left_total()
{
    return num_total_pcbs;
}