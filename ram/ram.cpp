#include <iostream>
#include "ram.h"

unsigned int ram::num_bytes = 0;
unsigned char *ram::data = nullptr;

void ram::init(unsigned int num_bytes)
{
    ram::num_bytes = num_bytes;
    ram::data = new unsigned char[num_bytes];
}

void ram::write_byte(unsigned int addr, unsigned char val)
{
    if(addr < num_bytes)
    {
        data[addr] = val;
    }
    else
    {
        std::cout << "--ram-error (write_byte): address " << std::hex << addr << " is out of range\n";
    }
}

unsigned char ram::read_byte(unsigned int addr)
{
    if(addr < num_bytes)
    {
        return data[addr];
    }
    else
    {
        std::cout << "--ram-error (read_byte): address " << std::hex << addr << " is out of range"
        return 0;
    }
}

void ram::write_word(unsigned int addr, int val)
{
    auto val1 = (unsigned char) ((val >> 24) & 0b11111111);
    auto val2 = (unsigned char) ((val >> 16) & 0b11111111);
    auto val3 = (unsigned char) ((val >> 8) & 0b11111111);
    auto val4 = (unsigned char) (val & 0b11111111);

    write_byte(addr, val1);
    write_byte(addr + 1, val2);
    write_byte(addr + 2, val3);
    write_byte(addr + 3, val4);
}

int ram::read_word(unsigned int addr)
{
    int val1 = read_byte(addr);
    int val2 = read_byte(addr + 1);
    int val3 = read_byte(addr + 2);
    int val4 = read_byte(addr + 3);

    return (val1 << 24) + (val2 << 16) + (val3 << 8) + val4;
}