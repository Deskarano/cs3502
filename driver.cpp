#include <iostream>
#include <fstream>

#include "disk/disk.h"
#include "pcb/pcb_control.h"

void load()
{
    std::ifstream program("programfile");
    std::string line;

    unsigned int addr = 0;
    unsigned int current_id;

    if(program.is_open())
    {
        while(std::getline(program, line))
        {
            if(line[0] == '/')
            {
                if(line[3] == 'J')
                {
                    current_id = pcb_control::create_pcb(&line);
                }
                else if(line[3] == 'D')
                {
                    pcb_control::update_pcb(current_id, &line);
                }
            }
            else
            {
                disk::write_word(addr, line.c_str());
                addr += 4;
            }
        }
    }
    else
    {
        std::cout << "unable to open file\n";
        exit(1);
    }
}

int main()
{
    disk::init(2048);
    load();

    pcb *next = pcb_control::get_highest_priority_pcb();
    std::cout << next->get_priority();
}