#ifndef CS3502_CPU_H
#define CS3502_CPU_H

#include "pcb.h"

class cpu
{
public:
    void start();
    void stop();

    void load_pcb(pcb new_pcb);
    void save_pcb();

private:
    pcb current_pcb;
    unsigned int reg[16];
};

#endif //CS3502_CPU_H