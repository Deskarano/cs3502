#ifndef CS3502_SCHED_CONTROL_H
#define CS3502_SCHED_CONTROL_H

#include <string>
#include "sched_types.h"

struct sched_control
{
    static void set_algorithm(sched_algorithm algorithm);
    static void create_pcb(std::string *job_line, std::string *data_line, unsigned int base_disk_address);

    static bool pcbs_left();
    static void schedule_and_run();
};

#endif //CS3502_SCHED_CONTROL_H
