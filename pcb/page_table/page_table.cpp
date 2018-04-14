#include "page_table.h"

page_table::page_table()
{
    page_table_head = nullptr;
}

void page_table::add_page(unsigned int logical_address, unsigned int physical_address)
{
    if(logical_address % 16 == 0 && physical_address % 16 == 0)
    {
        auto new_entry = new page_table_entry(logical_address, physical_address);

        if(page_table_head == nullptr)
        {
            page_table_head = new_entry;
        }
        else
        {
            page_table_entry *current = page_table_head;
            while(current->next != nullptr)
            {
                current = current->next;
            }

            current->next = new_entry;
        }
    }
    else
    {
        //TODO: put an error here
    }
}

unsigned int page_table::request_page(unsigned int logical_address)
{
    if(page_table_head == nullptr)
    {
        return PAGE_FAULT;
    }
    else
    {
        page_table_entry *current = page_table_head;

        while(current->next != nullptr)
        {
            if(logical_address >= current->logical_address &&
               logical_address < current->logical_address + 4)
            {
                return current->physical_address + (logical_address - current->logical_address);
            }

            current = current->next;
        }
    }

    return PAGE_FAULT;
}