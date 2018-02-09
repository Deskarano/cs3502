#ifndef CS3502_CPU_TEST_RAM_H
#define CS3502_CPU_TEST_RAM_H

struct cpu_test_ram
{
public:
    static void init(unsigned int num_bytes, unsigned char *data);

    static void write_byte(unsigned int addr, unsigned char val);
    static void write_word(unsigned int addr, unsigned int val);

    static unsigned char read_byte(unsigned int addr);
    static unsigned int read_word(unsigned int addr);

    static void dump_ram();

private:
    static unsigned int num_bytes;
    static unsigned char *data;
};

#endif //CS3502_CPU_TEST_RAM_H
