#include "ram.h"
#include "../log/log_status.h"

unsigned int ram::num_words = 0;
char *ram::data = nullptr;

void ram::init(unsigned int num_words)
{
    log_status::log_ram_init(num_words);
    ram::num_words = num_words;
    ram::data = new char[num_words * 8];
}

void ram::write_word(unsigned int addr, char val[8])
{
    log_status::log_ram_write_word(addr, val);
    for(int i = 0; i < 8; i++)
    {
        data[2 * addr + i] = val[i];
    }
}

char *ram::read_word(unsigned int addr)
{
    auto result = new char[8];

    for(int i = 0; i < 8; i++)
    {
        result[i] = data[2 * addr + i];
    }

    log_status::log_ram_read_word(addr, result);
    return result;
}