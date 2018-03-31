#ifndef CS3502_PAGE_TABLE_H
#define CS3502_PAGE_TABLE_H


class page_table
{
public:
    page_table();

    void add_page(unsigned int logical_address, unsigned int physical_address);
    unsigned int request_page(unsigned int logical_address);
};


#endif //CS3502_PAGE_TABLE_H
