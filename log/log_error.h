#ifndef CS3502_LOG_ERROR_H
#define CS3502_LOG_ERROR_H

#define CPU_DECODE_INVALID              1
#define CPU_CACHE_WRITE_WORD_RANGE      1
#define CPU_CACHE_READ_WORD_RANGE       1

#define DISK_WRITE_WORD_RANGE           2
#define DISK_READ_WORD_RANGE            2

#define RAM_WRITE_WORD_OUT_OF_RANGE     3
#define RAM_READ_WORD_OUT_OF_RANGE      3

struct log_error
{
public:
    static void cpu_decode_invalid(char *instruction);
    static void cpu_cache_write_word_range(unsigned int addr);
    static void cpu_cache_read_word_range(unsigned int addr);

    static void disk_write_word_range(unsigned int addr);
    static void disk_read_word_range(unsigned int addr);

    static void ram_write_word_range(unsigned int addr);
    static void ram_read_word_range(unsigned int addr);
};


#endif //CS3502_LOG_ERROR_H
