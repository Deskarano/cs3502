#include "disk.h"
#include "../log/log_status.h"

unsigned int disk::num_words = 0;
char *disk::data = nullptr;

void disk::init(unsigned int num_words)
{
    log_status::log_disk_init(num_words);
    disk::num_words = num_words;
    disk::data = new char[num_words * 8];
}

void disk::write_word(unsigned int addr, const char val[8])
{
    log_status::log_disk_write_word(addr, val);
    for(int i = 0; i < 8; i++)
    {
        data[2 * addr + i] = val[i];
    }
}

char *disk::read_word(unsigned int addr)
{
    auto result = new char[8];
    for(int i = 0; i < 8; i++)
    {
        result[i] = data[2 * addr + i];
    }

    log_status::log_disk_read_word(addr, result);
    return result;
}
