#include "disk.h"

#include "../../log/log_status.h"
#include "../../log/log_error.h"

unsigned int disk::num_words = 0;
page_frame *disk::pages = nullptr;

void disk::init(unsigned int num_words)
{
    log_status::log_disk_init(num_words);
    disk::num_words = num_words;
    disk::pages = new page_frame[(num_words / 4) + 1];
}

void disk::write_word(unsigned int addr, const char val[8])
{
    if(addr / 4 < num_words)
    {
        log_status::log_disk_write_word(addr, val);
        for(int i = 0; i < 8; i++)
        {
            unsigned int f = (2 * addr) / 32;
            unsigned int d = (2 * addr) % 32 + i;

            pages[f].data[d] = val[i];
        }
    }
    else
    {
        log_error::disk_write_word_range(addr);
    }
}

char *disk::read_word(unsigned int addr)
{
    if(addr / 4 < num_words)
    {
        auto result = new char[8];
        for(int i = 0; i < 8; i++)
        {
            unsigned int f = (2 * addr) / 32;
            unsigned int d = (2 * addr) % 32 + i;
            
            result[i] = pages[f].data[d];
        }

        log_status::log_disk_read_word(addr, result);
        return result;
    }
    else
    {
        log_error::disk_read_word_range(addr);
    }
}
