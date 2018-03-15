#include "log_error.h"
#include "../utils/base_conversions.h"

#include <iostream>

void log_error::cpu_decode_invalid(char *instruction)
{
    std::cout << "--cpu-error (decode): instruction ";
    for(int i = 0; i < 8; i++)
    {
        std::cout << instruction[i];
    }
    std::cout << " has invalid opcode\n";
    exit(CPU_DECODE_INVALID);
}

void log_error::disk_write_word_out_of_range(unsigned int addr)
{
    std::cout << "--disk_error (write_word): address 0x" << dec_to_hex(addr) << " is out of range\n";
    exit(DISK_WRITE_WORD_OUT_OF_RANGE);
}

void log_error::disk_read_word_out_of_range(unsigned int addr)
{
    std::cout << "--disk_error (read_word): address 0x" << dec_to_hex(addr) << " is out of range\n";
    exit(DISK_READ_WORD_OUT_OF_RANGE);
}

void log_error::ram_write_word_out_of_range(unsigned int addr)
{
    std::cout << "--disk_error (write_word): address 0x" << dec_to_hex(addr) << " is out of range\n";
    exit(RAM_WRITE_WORD_OUT_OF_RANGE);
}

void log_error::ram_read_word_out_of_range(unsigned int addr)
{
    std::cout << "--disk_error (read_word): address 0x" << dec_to_hex(addr) << " is out of range\n";
    exit(RAM_READ_WORD_OUT_OF_RANGE);
}
