#ifndef CS3502_PAGE_MANAGER_H
#define CS3502_PAGE_MANAGER_H

#include "../pcb/page_table/page_table.h"

struct page_manager
{
    int write_word(page_table *table, unsigned int addr, unsigned int val);
    int read_word(page_table *table, unsigned int addr, char *target);
};


#endif //CS3502_PAGE_MANAGER_H
