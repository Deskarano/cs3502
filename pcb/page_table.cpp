#include "page_table.h"

class page_table_entry
{
public:
    page_table_entry(unsigned int logical_address, unsigned int physical_address)
    {
        this->logical_address = logical_address;
        this->physical_address = physical_address;
    }

    bool contains(unsigned int logical_address)
    {
        return (logical_address >= this->logical_address &&
                logical_address < this->logical_address + 4);
    }

    page_table_entry *next;
    unsigned int logical_address;
    unsigned int physical_address;
};

page_table::page_table()
{
    
}