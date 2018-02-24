#include "pcb_control.h"
#include "../utils/base_conversions.h"

#include <iostream>

class pcb_node
{
public:
    explicit pcb_node(pcb *new_pcb)
    {
        this->next = nullptr;
        this->pcb = new_pcb;
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

void pcb_control::create_pcb(std::string *job_section, std::string *data_section, unsigned int base_disk_address)
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

    auto new_pcb = new pcb(ID, priority, code_size, input_size, output_size, temp_size);
    new_pcb->set_base_disk_address(base_disk_address);

    if(pcb_list_head == nullptr)
    {
        pcb_list_head = new pcb_node(new_pcb);
    }
    else
    {
        pcb_node *current = pcb_list_head;
        while(current->get_next() != nullptr)
        {
            current = current->get_next();
        }

        current->set_next(new pcb_node(new_pcb));
    }
}

pcb *pcb_control::get_pcb(unsigned int ID)
{
    if(pcb_list_head != nullptr)
    {
        pcb_node *current = pcb_list_head;

    if(current->get_pcb()->get_ID() == ID)
    {
        return current->get_pcb();
    }

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

        std::cout << "--pcb_control-error (get_pcb): could not find PCB " << ID << "\n";
        return nullptr;
    }
    else
    {
        std::cout << "--pcb_control-error (get_pcb): PCB list is empty\n";
    }
}

pcb *pcb_control::get_next_pcb()
{
    if(pcb_list_head != nullptr)
    {
        pcb *result = pcb_list_head->get_pcb();
        pcb_list_head = pcb_list_head->get_next();

        return result;
    }
    else
    {
        std::cout << "--pcb_control-error (get_highest_priority_pcb): PCB list is empty\n";
        return nullptr;
    }
}

pcb *pcb_control::get_highest_priority_pcb()
{
    if(pcb_list_head != nullptr)
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
    else
    {
        std::cout << "--pcb_control-error (get_highest_priority_pcb): PCB list is empty\n";
        return nullptr;
    }
}

void pcb_control::delete_pcb(unsigned int ID)
{
    //case for empty list
    if(pcb_list_head == nullptr)
    {
        std::cout << "--pcb_control-error (delete_pcb): PCB list is empty\n";
        return;
    }

    //case where target is first element
    if(pcb_list_head->get_pcb()->get_ID() == ID)
    {
        pcb_node *del = pcb_list_head;
        pcb_list_head = del->get_next();

        delete del->get_pcb();
        delete del;
        return;
    }

    //case where target is middle element or last element
    pcb_node *current = pcb_list_head;

    while(current->get_next() != nullptr)
    {
        if(current->get_next()->get_pcb()->get_ID() == ID)
        {
            pcb_node *del = current->get_next();
            current->set_next(del->get_next());

            delete del->get_pcb();
            delete del;
            return;
        }

        current = current->get_next();
    }
}