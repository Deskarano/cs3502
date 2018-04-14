#ifndef CS3502_PAGE_TABLE_H
#define CS3502_PAGE_TABLE_H

#include "page_table_entry.h"

#define PAGE_FAULT 0xFFFFFFFF

class page_table
{
public:
    page_table();

    void add_page(unsigned int logical_address, unsigned int physical_address);
    unsigned int request_page(unsigned int logical_address);

private:
    page_table_entry *page_table_head;
};


#endif //CS3502_PAGE_TABLE_H
