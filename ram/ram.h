#ifndef CS3502_RAM_H
#define CS3502_RAM_H

struct ram
{
public:
    static void init(unsigned int num_bytes);

    static void write_word(unsigned int addr, int val);
    static int read_word(unsigned int addr);

private:
    static void write_byte(unsigned int addr, unsigned char val);
    static unsigned char read_byte(unsigned int addr);

    static unsigned int num_bytes;
    static unsigned char *data;
};

#endif //CS3502_RAM_H