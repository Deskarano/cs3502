#ifndef CS3502_CPU_H
#define CS3502_CPU_H

#include "types/cpu_types.h"
#include "../pcb/pcb.h"
#include "types/instr_types.h"

#include <thread>

#define CACHE_SIZE 74

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

    char cache_data[8 * CACHE_SIZE];
    bool cache_changed[CACHE_SIZE];

    std::thread *cpu_thread;

    pcb *current_pcb;
    cpu_state state;

    unsigned int pc;
    int reg[16];

    void write_word_to_cache(unsigned int addr, char *val);
    char *read_word_from_cache(unsigned int addr);

    void cpu_main_thread();
    void execute(instr *instruction);
    instr *decode(char *instruction);
};

#endif //CS3502_CPU_H