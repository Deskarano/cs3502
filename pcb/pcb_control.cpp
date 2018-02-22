#include "pcb_control.h"
#include "../utils/base_conversions.h"

#include <iostream>

class pcb_node
{
public:
    pcb_node(pcb *pcb)
    {
        this->next = nullptr;
        this->pcb = pcb;
    }

    pcb_node *get_next()
    { return next; }

    void set_next(pcb_node *next)
    { this->next = next; }

    pcb *get_pcb()
    { return pcb; }

private:
    pcb_node *next;
    pcb *pcb;
};

static pcb_node *pcb_list_head = nullptr;

unsigned int pcb_control::create_pcb(std::string *job_section)
{
    unsigned int ID, priority, code_size;

    unsigned long next_space = job_section->find(' ');
    job_section->erase(0, next_space + 1);
    next_space = job_section->find(' ');

    job_section->erase(0, next_space + 1);
    next_space = job_section->find(' ');
    ID = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    job_section->erase(0, next_space + 1);
    next_space = job_section->find(' ');
    code_size = hex_to_dec(job_section->substr(0, next_space).c_str(), next_space);

    job_section->erase(0, next_space + 1);
    next_space = job_section->find(' ');
    priority = hex_to_dec(job_section->substr(0, next_space).c_str(), job_section->size() - 1);

    if(pcb_list_head == nullptr)
    {
        pcb_list_head = new pcb_node(new pcb(ID, priority, code_size));
    }
    else
    {
        pcb_node *current = pcb_list_head;
        while(current->get_next() != nullptr)
        {
            current = current->get_next();
        }

        current->set_next(new pcb_node(new pcb(ID, priority, code_size)));
    }

    return ID;
}

void pcb_control::update_pcb(unsigned int ID, std::string *data_section)
{
    unsigned int input_size, output_size, temp_size;

    unsigned long next_space = data_section->find(' ');
    data_section->erase(0, next_space + 1);
    next_space = data_section->find(' ');

    data_section->erase(0, next_space + 1);
    next_space = data_section->find(' ');
    input_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    data_section->erase(0, next_space + 1);
    next_space = data_section->find(' ');
    output_size = hex_to_dec(data_section->substr(0, next_space).c_str(), next_space);

    data_section->erase(0, next_space + 1);
    next_space = data_section->find(' ');
    temp_size = hex_to_dec(data_section->substr(0, next_space).c_str(), data_section->size() - 1);

    get_pcb(ID)->set_data_section(input_size, output_size, temp_size);
}


pcb *pcb_control::get_pcb(unsigned int ID)
{
    pcb_node *current = pcb_list_head;

    while(current->get_next() != nullptr)
    {
        current = current->get_next();
        if(current->get_pcb()->get_ID() == ID)
        {
            return current->get_pcb();
        }
    }

    if(current->get_pcb()->get_ID() == ID)
    {
        return current->get_pcb();
    }

    return nullptr;
}

pcb *pcb_control::get_highest_priority_pcb()
{
    pcb_node *current = pcb_list_head;
    pcb *result = current->get_pcb();

    while(current->get_next() != nullptr)
    {
        current = current->get_next();
        if(result->get_priority() > current->get_pcb()->get_priority())
        {
            result = current->get_pcb();
        }
    }

    if(result->get_priority() > current->get_pcb()->get_priority())
    {
        result = current->get_pcb();
    }

    return result;
}

void pcb_control::delete_pcb(unsigned int ID)
{

}