#include "page_table.h"

page_table::page_table(unsigned int num_words)
{
    entries = new unsigned int[(num_words / 4) + 1];
    valid = new bool[(num_words / 4) + 1];

    for(int i = 0; i < (num_words / 4) + 1; i++)
    {
        entries[i] = 0;
        valid[i] = false;
    }
}

page_table::~page_table()
{
    delete entries;
    delete valid;
}

void page_table::add_page(unsigned int frame_num, unsigned int page_num)
{
    entries[frame_num] = page_num;
    valid[frame_num] = true;
}

unsigned int page_table::lookup_page(unsigned int logical_address)
{
    unsigned int frame_num = logical_address / 16;

    if(valid[frame_num])
    {
        return 16 * entries[frame_num] + (logical_address - 16 * frame_num);
    }
    else
    {
        return PAGE_FAULT;
    }
}