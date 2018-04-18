#include "storage/disk/disk.h"
#include "storage/ram/ram.h"
#include "storage/page_manager.h"

#include "sched/sched_control.h"

#include "cpu/cpu_control.h"
#include "log/log_status.h"

#include <iostream>
#include <fstream>

void load(const std::string programfile)
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
                    while(addr % 16 != 0)
                    {
                        disk::write_word(addr, "00000000");
                        addr += 4;
                    }

                    base_disk_address = addr;
                }
                else if(line[3] == 'D')
                {
                    data_line = line;
                }
                else // line[3] == 'E'
                {
                    sched_control::create_pcb(&job_line, &data_line, base_disk_address);
                }
            }
            else
            {
                disk::write_word(addr, line.substr(2).c_str());
                addr += 4;
            }
        }
    }
    else
    {
        std::cout << "--loader-error: unable to open program file\n";
        exit(1);
    }
}

int main()
{
    disk::init(2048);
    ram::init(1024);

    cpu_control::init(4);
    page_manager::init();

    sched_control::set_algorithm(SCHED_FCFS);

    load("programfile");

    while(sched_control::pcbs_left())
    {
        sched_control::schedule_and_run();
    }

    std::cout << "finished successfully!\n";
}