#ifndef CS3502_PAGE_TABLE_ENTRY_H
#define CS3502_PAGE_TABLE_ENTRY_H


class page_table_entry
{
public:
    page_table_entry(unsigned int logical_address, unsigned int physical_address);

    page_table_entry *next;

    unsigned int logical_address;
    unsigned int physical_address;
};


#endif //CS3502_PAGE_TABLE_ENTRY_H
