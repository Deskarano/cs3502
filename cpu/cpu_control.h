#ifndef CS3502_CPU_CONTROL_H
#define CS3502_CPU_CONTROL_H

#include "types/cpu_types.h"

struct cpu_control
{
public:
    static void init(unsigned int num_cores);
    static cpu_state get_core_state(unsigned int core_id);

private:
    static unsigned int num_cores;
};

#endif //CS3502_CPU_CONTROL_H
