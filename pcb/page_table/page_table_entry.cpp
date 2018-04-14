#include "page_table_entry.h"

page_table_entry::page_table_entry(unsigned int logical_address, unsigned int physical_address)
{
    this->logical_address = logical_address;
    this->physical_address = physical_address;
    this->next = nullptr;
}