#ifndef CS3502_CPU_CONTROL_H
#define CS3502_CPU_CONTROL_H

#include "cpu.h"

struct cpu_control
{
public:
    void init(unsigned int num_cores);
    cpu *get_core(unsigned int core_id);

private:
    unsigned int num_cores;
    cpu *cores;
};

#endif //CS3502_CPU_CONTROL_H
