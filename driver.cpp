#include <iostream>
#include <fstream>
#include "disk/disk.h"

void load()
{
    std::ifstream program("programfile");
    std::string line;

    unsigned int addr = 0;

    if(program.is_open())
    {
        while(std::getline(program, line))
        {
            if(line[0] != '/')
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

}