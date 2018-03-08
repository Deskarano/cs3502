#ifndef CS3502_LOGGER_H
#define CS3502_LOGGER_H

#define LOG_CPU_FETCH false
#define LOG_CPU_DECODE false
#define LOG_CPU_EXECUTE true

struct logger
{
public:
    static void log_cpu_fetch(unsigned int pcb_id, unsigned int pc, char *fetch);
    static void log_cpu_decode(char *fetch, void *instr);
    static void log_cpu_execute(unsigned int pc, void *instruction, int reg[16]);

};


#endif //CS3502_LOGGER_H
