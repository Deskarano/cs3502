#ifndef CS3502_LONGTERM_H
#define CS3502_LONGTERM_H

struct longterm
{
public:
    static void create_pcb(std::string *job_section, std::string *data_section, unsigned int base_disk_address);

    static void schedule_fcfs();
    static void schedule_priority();

    static int pcbs_left_ram();
    static int pcbs_left_total();
};


#endif //CS3502_LONGTERM_H
