#ifndef CS3502_LOGGER_H
#define CS3502_LOGGER_H

#define LOG_CPU_FETCH               true
#define LOG_CPU_DECODE              true
#define LOG_CPU_EXECUTE             true
#define LOG_CPU_START               true
#define LOG_CPU_STOP                true
#define LOG_CPU_SET_PCB             true
#define LOG_CPU_SAVE_PCB            true

#define LOG_CPU_CONTROL_INIT        true
#define LOG_CPU_CONTROL_DISPATCH    true

#define LOG_DISK_INIT               true
#define LOG_DISK_WRITE_WORD         true
#define LOG_DISK_READ_WORD          true

struct logger
{
public:
    static void log_cpu_fetch(unsigned int pcb_id, unsigned int pc, char *fetch);
    static void log_cpu_decode(char *fetch, void *instr);
    static void log_cpu_execute(unsigned int pc, void *instruction, int reg[16]);
    static void log_cpu_start(unsigned int pcb_id);
    static void log_cpu_stop(unsigned int pcb_id);
    static void log_cpu_set_pcb(unsigned int pcb_id);
    static void log_cpu_save_pcb(unsigned int pcb_id);

    static void log_cpu_control_init(unsigned int num_cores);
    static void log_cpu_control_dispatch(unsigned int core_id, unsigned int pcb_id);

    static void log_disk_init(unsigned int num_words);
    static void log_disk_write_word(unsigned int addr, char val[8]);
    static void log_disk_read_word(unsigned int addr, char val[8]);
};


#endif //CS3502_LOGGER_H
