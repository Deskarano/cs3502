#ifndef CS3502_RAM_H
#define CS3502_RAM_H

#include "../page_frame.h"

struct ram
{
public:
    static void init(unsigned int num_words);

    static void write_word(unsigned int addr, char val[8], unsigned int requester);
    static char *read_word(unsigned int addr, unsigned int requester);

    static void set_frame_owner(unsigned int addr, unsigned int owner);
    static unsigned int get_frame_owner(unsigned int addr);

    static unsigned int size();

private:
    static unsigned int num_words;
    static page_frame *frames;
    static unsigned int *frame_owners;
};

#endif //CS3502_RAM_H