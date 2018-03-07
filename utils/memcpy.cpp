#include "memcpy.h"

#include "../disk/disk.h"
#include "../ram/ram.h"

void disk_to_ram(unsigned int disk_addr, unsigned int ram_addr, unsigned int num_words)
{
    for(int i = 0; i < num_words; i++)
    {
        char *val = disk::read_word(disk_addr + 4 * i);
        ram::write_word(ram_addr + 4 * i, val);
    }
}