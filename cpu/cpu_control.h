#ifndef CS3502_CPU_CONTROL_H
#define CS3502_CPU_CONTROL_H

#include "types/cpu_types.h"
#include "../pcb/pcb.h"

struct cpu_control
{
public:
    static void init(unsigned int num_cores);

    static unsigned int num_idle_cores();

    static void dispatch(pcb *pcb);
    static void clear_finished_cores();

    static unsigned int get_num_cores()
    { return num_cores; }
private:
    static unsigned int num_cores;
};

#endif //CS3502_CPU_CONTROL_H
