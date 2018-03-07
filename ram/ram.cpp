#include <iostream>
#include "ram.h"

unsigned int ram::num_words = 0;
char *ram::data = nullptr;
unsigned int ram::used_memory = 0;

void ram::init(unsigned int num_words)
{
    ram::num_words = num_words;
    ram::data = new char[num_words * 8];
}

void ram::write_word(unsigned int addr, char val[8])
{
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

    return result;
}

bool ram::is_full()
{
    return used_memory >= num_words;
}