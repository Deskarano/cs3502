#ifndef CS3502_RAM_H
#define CS3502_RAM_H

#include "../page_frame.h"

struct ram
{
public:
    static void init(unsigned int num_words);

    static void write_word(unsigned int addr, char val[8]);
    static char *read_word(unsigned int addr);

    static unsigned int size();

private:
    static unsigned int num_words;
    static page_frame *frames;
};

#endif //CS3502_RAM_H