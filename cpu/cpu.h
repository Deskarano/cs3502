#ifndef CS3502_CPU_H
#define CS3502_CPU_H

#include "types/cpu_types.h"
#include "types/instr_types.h"

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
    pcb *get_pcb()
    { return current_pcb; }

    void set_state(cpu_state state)
    { this->state = state; }

    cpu_state get_state()
    { return state; }

private:
    unsigned int core_id;

    std::thread *cpu_thread;
    bool page_fault;

    pcb *current_pcb;
    cpu_state state;

    unsigned int pc;
    int reg[16];

    void cpu_main_thread();
    void execute(instr *instruction);
    instr *decode(char *instruction);

    void handle_page_fault();
    char *read_or_page_fault(unsigned int addr);
    void write_or_page_fault(unsigned int addr, int val);
};

#endif //CS3502_CPU_H