#include "ram.h"
#include "../utils/base_conversions.h"

#include <iostream>

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
    //std::cout << "--ram-status (write_word): writing ";

    for(int i = 0; i < 8; i++)
    {
        //std::cout << val[i];
        data[2 * addr + i] = val[i];
    }

    //std::cout << " to addr 0x" << dec_to_hex(addr) << "\n";
}

char *ram::read_word(unsigned int addr)
{
    //std::cout << "--ram-status (read_word): reading ";
    auto result = new char[8];

    for(int i = 0; i < 8; i++)
    {
        result[i] = data[2 * addr + i];
        //std::cout << result[i];
    }

    //std::cout << " from addr 0x" << dec_to_hex(addr) << "\n";
    return result;
}

bool ram::is_full()
{
    return used_memory >= num_words;
}