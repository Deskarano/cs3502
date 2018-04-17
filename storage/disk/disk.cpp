#include "disk.h"

#include "../../log/log_status.h"
#include "../../log/log_error.h"

unsigned int disk::num_words = 0;
char *disk::data = nullptr;

void disk::init(unsigned int num_words)
{
    log_status::log_disk_init(num_words);
    disk::num_words = num_words;
    disk::data = new char[(num_words / 4) + 1];
}

void disk::write_word(unsigned int addr, const char val[8])
{
    if(addr / 4 < num_words)
    {
        log_status::log_disk_write_word(addr, val);

        for(int i = 0; i < 8; i++)
        {
            data[2 * addr + i] = val[i];
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
            result[i] = data[2 * addr + i];
        }

        log_status::log_disk_read_word(addr, result);
        return result;
    }
    else
    {
        log_error::disk_read_word_range(addr);
    }
}
