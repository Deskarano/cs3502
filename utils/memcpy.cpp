#include "memcpy.h"

#include "../storage/disk/disk.h"
#include "../storage/ram/ram.h"

void disk_to_ram(unsigned int disk_addr, unsigned int ram_addr, unsigned int num_words, unsigned int requester)
{
    for(int i = 0; i < num_words; i++)
    {
        char *val = disk::read_word(disk_addr + 4 * i);
        ram::write_word(ram_addr + 4 * i, val, requester);
    }
}

void ram_to_disk(unsigned int ram_addr, unsigned int disk_addr, unsigned int num_words, unsigned int requester)
{
    for(int i = 0; i < num_words; i++)
    {
        char *val = ram::read_word(ram_addr + 4 * i, requester);
        disk::write_word(disk_addr + 4 * i, val);
    }
}