#include "cpu_control.h"
#include "cpu.h"

#include <iostream>

unsigned int cpu_control::num_cores = 0;
static cpu *cores = nullptr;

void cpu_control::init(unsigned int num_cores)
{
    cpu_control::num_cores = num_cores;
    cores = new cpu[num_cores];
}

cpu_state cpu_control::get_core_state(unsigned int core_id)
{
    if(core_id < num_cores)
    {
        return cores[core_id].get_state();
    }
    else
    {
        std::cout << "--cpu_control-error (get_core_state): core_id out of range\n";
        return NULL;
    }
}

void cpu_control::dispatch_to_core(unsigned int core_id, pcb *new_pcb)
{
    if(get_core_state(core_id) == FULL)
    {
        cores[core_id].stop();
        cores[core_id].save_pcb();
    }

    cores[core_id].set_pcb(new_pcb);
    cores[core_id].start();
}