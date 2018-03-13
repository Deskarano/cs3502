#ifndef CS3502_LOG_STATUS_H
#define CS3502_LOG_STATUS_H

#define LOG_CPU_FETCH               false
#define LOG_CPU_DECODE              false
#define LOG_CPU_EXECUTE             true

#define LOG_CPU_START               true
#define LOG_CPU_STOP                true
#define LOG_CPU_SET_PCB             true
#define LOG_CPU_SAVE_PCB            true

#define LOG_CPU_CONTROL_INIT        true
#define LOG_CPU_CONTROL_DISPATCH    true

#define LOG_DISK_INIT               true
#define LOG_DISK_WRITE_WORD         false
#define LOG_DISK_READ_WORD          false

#define LOG_RAM_INIT                true
#define LOG_RAM_WRITE_WORD          false
#define LOG_RAM_READ_WORD           false

#define LOG_LONG_CREATE_PCB         true
#define LOG_LONG_SCHEDULE_FCFS      true
#define LOG_LONG_SCHEDULE_PRIORITY  true

struct log_status
{
public:
    static void log_cpu_fetch(unsigned int core_id, unsigned int pcb_id, unsigned int pc);
    static void log_cpu_decode(unsigned int core_id, char *fetch, void *instr);
    static void log_cpu_execute(unsigned int core_id, void *instruction, int reg[16]);

    static void log_cpu_start(unsigned int core_id, unsigned int pcb_id);
    static void log_cpu_stop(unsigned int core_id, unsigned int pcb_id);
    static void log_cpu_set_pcb(unsigned int core_id, unsigned int pcb_id);
    static void log_cpu_save_pcb(unsigned int core_id, unsigned int pcb_id);

    static void log_cpu_control_init(unsigned int num_cores);
    static void log_cpu_control_dispatch(unsigned int core_id, unsigned int pcb_id);

    static void log_disk_init(unsigned int num_words);
    static void log_disk_write_word(unsigned int addr, const char val[8]);
    static void log_disk_read_word(unsigned int addr, char val[8]);

    static void log_ram_init(unsigned int num_words);
    static void log_ram_write_word(unsigned int addr, char val[8]);
    static void log_ram_read_word(unsigned int addr, char val[8]);

    static void log_long_create_pcb(unsigned int pcb_id, unsigned int base_disk_address);
    static void log_long_schedule_fcfs(unsigned int pcb_id, unsigned int base_ram_address);
    static void log_long_schedule_priority(unsigned int pcb_id, unsigned int priority, unsigned int base_ram_address);
};


#endif //CS3502_LOG_STATUS_H
