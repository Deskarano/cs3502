#include <bitset>
#include <iostream>
#include "cpu_test_ram.h"

cpu_test_ram::cpu_test_ram(unsigned int num_bytes)
{
    this->num_bytes = num_bytes;
    this->storage = new unsigned char[num_bytes];

    for(int i = 0; i < num_bytes; i++)
    {
        storage[i] = 0;
    }
}

void cpu_test_ram::write_byte(unsigned int addr, unsigned char val)
{
    if(addr < num_bytes)
    {
        storage[addr] = val;
    }
    else
    {
        std::cout << "--ram-error (write_byte): addr " << std::hex << addr << "out of range\n";
    }
}

void cpu_test_ram::write_word(unsigned int addr, unsigned int val)
{
    unsigned char val1 = (unsigned char) ((val >> 24) & 0b11111111);
    unsigned char val2 = (unsigned char) ((val >> 16) & 0b11111111);
    unsigned char val3 = (unsigned char) ((val >> 8) & 0b11111111);
    unsigned char val4 = (unsigned char) (val & 0b11111111);

    write_byte(addr, val1);
    write_byte(addr + 1, val2);
    write_byte(addr + 2, val3);
    write_byte(addr + 3, val4);
}

unsigned char cpu_test_ram::read_byte(unsigned int addr)
{
    if(addr < num_bytes)
    {
        return storage[addr];
    }
    else
    {
        std::cout << "--ram-error (read_byte): addr " << std::hex << addr << "out of range\n";
        return NULL;
    }
}

unsigned int cpu_test_ram::read_word(unsigned int addr)
{
    unsigned int val1 = read_byte(addr);
    unsigned int val2 = read_byte(addr + 1);
    unsigned int val3 = read_byte(addr + 2);
    unsigned int val4 = read_byte(addr + 3);

    return (val1 << 24) + (val2 << 16) + (val3 << 8) + val4;
}