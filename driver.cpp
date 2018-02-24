#include <iostream>
#include <fstream>

#include "disk/disk.h"
#include "pcb/pcb_control.h"

void load(std::string programfile)
{
    std::ifstream program(programfile);
    std::string line;

    unsigned int addr = 0;

    std::string job_line;
    std::string data_line;
    unsigned int base_disk_address = 0;

    if(program.is_open())
    {
        while(std::getline(program, line))
        {
            if(line[0] == '/')
            {
                if(line[3] == 'J')
                {
                    job_line = line;
                    base_disk_address = addr;
                }
                else if(line[3] == 'D')
                {
                    data_line = line;
                }
                else // line[3] == 'E'
                {
                    pcb_control::create_pcb(&job_line, &data_line, base_disk_address);
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
        std::cout << "unable to open program file\n";
        exit(1);
    }
}

int main()
{
    disk::init(2048);
    load("programfile");

    for(int i = 30; i > 0; i--)
    {
        pcb *pcb = pcb_control::get_pcb(i);
        std::cout << "got pcb " << pcb->get_ID() << "\n";

        pcb_control::delete_pcb(i);
        std::cout << "deleted pcb " << i << "\n";
    }
}