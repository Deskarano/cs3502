//
// Created by Othmane on 2/13/18.
//

#include "disk.h"
#include <iostream>

unsigned int disk::num_words = 0;
char *disk::data = nullptr;
unsigned int disk::used_memory = 0;

void disk::init(unsigned int num_words)
{
    disk::num_words = num_words;
    disk::data = new char[num_words * 8];

}

void disk::write_word(unsigned int addr, const char val[8])
{
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

    return result;
}

void disk::clear_disk()
{
    for(int i = 0; i < num_words; ++i)
        data[i] = '\0';
    used_memory = 0;
}

bool disk::is_full()
{
    return used_memory >= num_words;
}

bool disk::is_empty()
{
    return used_memory == 0;
}
