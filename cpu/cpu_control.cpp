#include "cpu_control.h"

#include "cpu.h"
#include "../log/log_status.h"
#include "../sched/long/longterm.h"

unsigned int cpu_control::num_cores = 0;
static cpu *cores = nullptr;

void cpu_control::init(unsigned int num_cores)
{
    log_status::log_cpu_control_init(num_cores);

    cpu_control::num_cores = num_cores;
    cores = new cpu[num_cores];
}

unsigned int cpu_control::num_idle_cores()
{
    unsigned int count = 0;

    for(int i = 0; i < num_cores; i++)
    {
        if(cores[i].get_state() == CPU_IDLE) count++;
    }

    return count;
}

void cpu_control::dispatch(pcb *pcb)
{
    for(int i = 0; i < num_cores; i++)
    {
        if(cores[i].get_state() == CPU_IDLE)
        {
            log_status::log_cpu_control_dispatch(i, pcb->ID);

            cores[i].set_pcb(pcb);
            cores[i].start();

            break;
        }
    }
}

void cpu_control::clear_finished_cores()
{
    for(int i = 0; i < num_cores; i++)
    {
        if(cores[i].get_state() == CPU_DONE)
        {
            log_status::log_cpu_control_clear(i);

            cores[i].save_pcb();
            longterm::writeback_finished_pcb(cores[i].get_pcb());
            cores[i].set_state(CPU_IDLE);
        }
    }
}