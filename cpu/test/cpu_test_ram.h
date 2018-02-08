#ifndef CS3502_CPU_TEST_RAM_H
#define CS3502_CPU_TEST_RAM_H


class cpu_test_ram
{
public:
    cpu_test_ram(unsigned int num_bytes);

    void write_byte(unsigned int addr, unsigned char val);
    void write_word(unsigned int addr, unsigned int val);

    unsigned char read_byte(unsigned int addr);
    unsigned int read_word(unsigned int addr);

private:
    unsigned int num_bytes;
    unsigned char *storage;
};


#endif //CS3502_CPU_TEST_RAM_H
