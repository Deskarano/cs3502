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
    return cores[core_id].get_state();
}

void cpu_control::dispatch_to_core(unsigned int core_id, pcb *new_pcb)
{
    std::cout << "--cpu_control-status (dispatch_to_core): dispatching PCB "
              << new_pcb->get_ID() << " to core " << core_id << "\n";

    if(get_core_state(core_id) == CPU_FULL)
    {
        cores[core_id].stop();
        cores[core_id].save_pcb();
    }

    cores[core_id].set_pcb(new_pcb);
    cores[core_id].start();
}