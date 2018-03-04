//
// Created by zachs on 3/4/2018.
//

#include "loader.h";
#include "iostream";
#include "../ram/ram.h";

void Loader::Loader()
{}

void Loader::~Loader()
{}

void Loader::loadProgram(std::ifstream program)
{
    std::string line;

    ram::init(1024, new usigned char[1024]);
    usigned int addr = 0;

    if(program.is_open())
    {
        while(std::getline(program, line))
        {
            if(line[0] != '/')
            {
                auto value = (usigned char) std::stoul(line, nullptr, 16);
                ram::write_word((usigned int) addr, value);
                addr += 4;
            }
        }
    }
    else
    {
        std::cout << "Unable to open file\n";
    }
}