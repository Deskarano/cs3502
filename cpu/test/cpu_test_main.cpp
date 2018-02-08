#include <iostream>
#include <fstream>
#include <bitset>

#include "cpu_test_ram.h"
#include "../cpu.h"

int main()
{
    cpu_test_ram *ram = new cpu_test_ram(1024);
    unsigned int addr = 0;

    std::ifstream program ("programfile");
    std::string line = "";

    if(program.is_open())
    {
        while(std::getline(program, line))
        {
            if(line[0] != '/')
            {
                unsigned int value = (unsigned) std::stoul(line, nullptr, 16);
                ram->write_word(addr, value);
                addr += 4;
            }
        }
    }
    else
    {
        std::cout << "unable to open file\n";
    }

    pcb *pcb1 = new pcb(0, ram, 0);
    cpu *cpu1 = new cpu();

    cpu1->set_pcb(pcb1);
    cpu1->start();
}