#ifndef CS3502_CPU_CONTROL_H
#define CS3502_CPU_CONTROL_H

#include "types/cpu_types.h"
#include "pcb.h"

struct cpu_control
{
public:
    static void init(unsigned int num_cores);

    static cpu_state get_core_state(unsigned int core_id);
    static void dispatch_to_core(unsigned int core_id, pcb *pcb);

private:
    static unsigned int num_cores;
};

#endif //CS3502_CPU_CONTROL_H
