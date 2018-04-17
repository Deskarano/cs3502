#include "page_table.h"
#include "../../storage/page_manager.h"

page_table::page_table(unsigned int num_words, unsigned int base_disk_address, unsigned int pcb_id)
{
    this->num_frames = (num_words / 4) + 1;
    this->pcb_id = pcb_id;
    this->base_disk_address = base_disk_address;

    this->entries = new unsigned int[this->num_frames];
    this->valid = new bool[this->num_frames];
    this->used = new unsigned int[this->num_frames];

    for(int i = 0; i <this-> num_frames; i++)
    {
        this->entries[i] = 0;
        this->valid[i] = false;
        this->used[i] = 0;
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
    used[frame_num] = 0;
}

unsigned int page_table::lookup_page(unsigned int logical_address)
{
    unsigned int frame_num = logical_address / 16;

    if(valid[frame_num])
    {
        used[frame_num]++;
        return 16 * entries[frame_num] + (logical_address - 16 * frame_num);
    }
    else
    {
        //release all frames that were not used since the last page fault
        for(unsigned int i = 0; i < num_frames; i++)
        {
            if(valid[i] && used[i] < 0)
            {
                page_manager::release_frame(this, 16 * i);
                valid[i] = false;
            }

            used[i]--;
        }

        return PAGE_FAULT;
    }
}