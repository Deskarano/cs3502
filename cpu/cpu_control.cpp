#include "cpu_control.h"

#include <iostream>

unsigned int cpu_control::num_cores = 0;
cpu *cpu_control::cores = nullptr;

void cpu_control::init(unsigned int num_cores)
{
    cpu_control::num_cores = num_cores;
    cpu_control::cores = new cpu[num_cores];

    //TODO: initialize new cpu cores here?
}

cpu *cpu_control::get_core(unsigned int core_id)
{
    if(core_id < num_cores)
    {
        return &cores[core_id];
    }
    else
    {
        std::cout << "--cpu_control-error: core_id " << core_id << " is out of range\n";
        return nullptr;
    }
}