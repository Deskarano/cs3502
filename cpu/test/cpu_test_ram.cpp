#include <bitset>
#include <iostream>
#include "cpu_test_ram.h"

unsigned int cpu_test_ram::num_bytes = 0;
unsigned char *cpu_test_ram::data = nullptr;

void cpu_test_ram::init(unsigned int num_bytes, unsigned char *data)
{
    cpu_test_ram::num_bytes = num_bytes;
    cpu_test_ram::data = data;
}

void cpu_test_ram::write_byte(unsigned int addr, unsigned char val)
{
    data[addr] = val;
}

void cpu_test_ram::write_word(unsigned int addr, unsigned int val)
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

unsigned char cpu_test_ram::read_byte(unsigned int addr)
{
    return data[addr];
}

unsigned int cpu_test_ram::read_word(unsigned int addr)
{
    unsigned int val1 = read_byte(addr);
    unsigned int val2 = read_byte(addr + 1);
    unsigned int val3 = read_byte(addr + 2);
    unsigned int val4 = read_byte(addr + 3);

    return (val1 << 24) + (val2 << 16) + (val3 << 8) + val4;
}

void cpu_test_ram::dump_ram()
{
    for(int i = 0; i < num_bytes; i += 16)
    {
        std::cout << std::hex << i << ": ";
        for(int j = 0; j < 16; j += 4)
        {
            std::cout << std::hex << read_word(i + j) << " ";
        }
        std::cout << "\n";
    }
}