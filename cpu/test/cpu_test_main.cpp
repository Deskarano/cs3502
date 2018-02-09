#include <iostream>
#include <fstream>

#include "cpu_test_ram.h"
#include "../cpu.h"

int main()
{
    cpu_test_ram::init(1024, new unsigned char[1024]);
    unsigned int addr = 0;

    std::ifstream program ("programfile");
    std::string line;

    if(program.is_open())
    {
        while(std::getline(program, line))
        {
            if(line[0] != '/')
            {
                auto value = (unsigned) std::stoul(line, nullptr, 16);
                cpu_test_ram::write_word(addr, value);
                addr += 4;
            }
        }
    }
    else
    {
        std::cout << "unable to open file\n";
        return 1;
    }

    auto pcb1 = new pcb(0, 0);
    auto cpu1 = new cpu();

    cpu1->set_pcb(pcb1);
    cpu1->start();

    return 0;
}