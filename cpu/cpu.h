#ifndef CS3502_CPU_H
#define CS3502_CPU_H

#include "types/cpu_types.h"

#include "pcb.h"

class cpu
{
public:
    void start();
    void stop();

    void set_pcb(pcb *new_pcb);
    void save_pcb();

    cpu_state get_state() { return state; }

private:
    pcb *current_pcb;
    cpu_state state;

    unsigned int pc;
    int reg[16];
};

#endif //CS3502_CPU_H