#include "sched_control.h"

#include "short/shortterm.h"
#include "long/longterm.h"

#include "../cpu/cpu_control.h"
#include "../utils/base_conversions.h"

void sched_control::set_algorithm(sched_algorithm algorithm)
{
    shortterm::set_scheduling_algorithm(algorithm);
    longterm::set_scheduling_algorithm(algorithm);
}

void sched_control::create_pcb(std::string *job_line, std::string *data_line, unsigned int base_disk_address)
{
    unsigned int ID, priority, code_size;

    unsigned int next_space = (int) job_line->find(' ');
    job_line->erase(0, next_space + 1);
    next_space = (int) job_line->find(' ');

    job_line->erase(0, next_space + 1);
    next_space = (int) job_line->find(' ');
    ID = hex_to_dec(job_line->substr(0, next_space).c_str(), next_space);

    job_line->erase(0, next_space + 1);
    next_space = (int) job_line->find(' ');
    code_size = hex_to_dec(job_line->substr(0, next_space).c_str(), next_space);

    job_line->erase(0, next_space + 1);
    priority = hex_to_dec(job_line->c_str(), (unsigned int) job_line->size());

    //analyze data_section
    unsigned int input_size, output_size, temp_size;

    next_space = (int) data_line->find(' ');
    data_line->erase(0, next_space + 1);
    next_space = (int) data_line->find(' ');

    data_line->erase(0, next_space + 1);
    next_space = (int) data_line->find(' ');
    input_size = hex_to_dec(data_line->substr(0, next_space).c_str(), next_space);

    data_line->erase(0, next_space + 1);
    next_space = (int) data_line->find(' ');
    output_size = hex_to_dec(data_line->substr(0, next_space).c_str(), next_space);

    data_line->erase(0, next_space + 1);
    temp_size = hex_to_dec(data_line->c_str(), (unsigned int) data_line->size());

    longterm::create_pcb(ID, priority, code_size,
                         input_size, output_size, temp_size,
                         base_disk_address);
}

bool sched_control::pcbs_left()
{
    return longterm::pcbs_left_total() > 0;
}

void sched_control::schedule_and_run()
{
    cpu_control::clear_finished_cores();

    if(longterm::pcbs_left_ram() == 0 && longterm::pcbs_left_total() > 0)
    {
        longterm::schedule();
    }

    shortterm::dispatch_new_processes();
}