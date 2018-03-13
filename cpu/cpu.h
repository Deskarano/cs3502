#ifndef CS3502_CPU_H
#define CS3502_CPU_H

#include "types/cpu_types.h"
#include "../pcb/pcb.h"

#include <thread>

class cpu
{
public:
    cpu();

    void start();
    void stop();

    void set_pcb(pcb *new_pcb);
    void save_pcb();

    pcb *get_pcb() { return current_pcb; }
    cpu_state get_state() { return state; }

private:
    std::thread cpu_thread;
    void cpu_main_thread();

    pcb *current_pcb;
    cpu_state state;

    unsigned int pc;
    int reg[16];
};

#endif //CS3502_CPU_H