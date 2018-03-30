#ifndef CS3502_LONGTERM_H
#define CS3502_LONGTERM_H

#include "../../pcb/pcb.h"
#include "../sched_types.h"

struct longterm
{
public:
    static void create_pcb(unsigned int ID, unsigned int priority, unsigned int code_size,
                           unsigned int input_size, unsigned int output_size, unsigned int temp_size,
                           unsigned int base_disk_address);
    static void writeback_finished_pcb(pcb *pcb);

    static void schedule();
    static void set_scheduling_algorithm(sched_algorithm sa);

    static int pcbs_left_ram();
    static int pcbs_left_total();
};


#endif //CS3502_LONGTERM_H
