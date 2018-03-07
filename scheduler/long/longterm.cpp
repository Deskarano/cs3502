#include <iostream>

#include "longterm.h"

#include "../../pcb/pcb.h"
#include "../../ram/ram.h"
#include "../../disk/disk.h"
#include "../../utils/base_conversions.h"

class pcb_node
{
public:
    explicit pcb_node(pcb *new_pcb)
    {
        this->next = nullptr;
        this->pcb = new_pcb;
    }

    pcb_node *next;
    pcb *pcb;
};

static pcb_node *pcb_list_head = nullptr;

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

    pcb *new_pcb = new pcb(ID, priority, code_size, input_size, output_size, temp_size);
    new_pcb->set_base_disk_address(base_disk_address);

    if(pcb_list_head == nullptr)
    {
        pcb_list_head = new pcb_node(new_pcb);
    }
    else
    {
        pcb_node *current = pcb_list_head;
        while(current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new pcb_node(new_pcb);
    }
}

pcb *get_next_pcb()
{
    if(pcb_list_head != nullptr)
    {
        pcb_node *del = pcb_list_head;
        pcb *ret = del->pcb;

        pcb_list_head = del->next;

        delete del;
        return ret;
    }
    else
    {
        std::cout << "--pcb_control-error (get_highest_priority_pcb): PCB list is empty\n";
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
            if(del->pcb->get_priority() > current->pcb->get_priority())
            {
                del = current;
            }
        }

        if(del->pcb->get_priority() > current->pcb()->get_priority())
        {
            del = current;
        }

        pcb *ret = del->pcb;

        //and delete it
        current = pcb_list_head;
        while(current->next != del)
        {
            current = current->next;
        }

        current->next = del->next;

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
    unsigned int addr = 0;
    pcb *current = get_next_pcb();

    while(addr + current->get_total_size() < ram::size())
    {

    }
}

void longterm::schedule_priority()
{

}